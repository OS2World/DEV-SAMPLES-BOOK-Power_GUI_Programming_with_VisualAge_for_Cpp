//************************************************************
// Tool Bars  - Custom Button Handler Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <igraphic.hpp>
#include <igelipse.hpp>
#include "graphbut.hpp"



// GraphicButton Constructor
GraphicButton::GraphicButton (unsigned long identifier,
                         IWindow*      parent,
                         IWindow*      owner,
                         const ISize&   graphicSize,
                         IGraphic*       upGraphic,
                         IGraphic*       downGraphic)
     : ICustomButton(identifier, parent, owner),
       fUpGraphic (upGraphic),
       fDownGraphic (downGraphic),
       fGraphicButtonHandler(new GraphicButtonHandler()),
       fGraphicSize(graphicSize)
{

// Attach the graphic button's handler.
fGraphicButtonHandler->handleEventsFor(this);

// Create the default graphics, if necessary.
IGraphicBundle bundle;
if (fUpGraphic == 0)
{
  fUpGraphic = (IGraphic*)new IGEllipse(IRectangle(IPoint(0,0), fGraphicSize));
  bundle.setFillColor(IColor::red);
  fUpGraphic->setGraphicBundle(bundle);
}
if (fDownGraphic == 0)
{
  fDownGraphic = (IGraphic*)new IGEllipse(IRectangle(IPoint(0,0), fGraphicSize));
  bundle.setFillColor(IColor::green);
  fDownGraphic->setGraphicBundle(bundle);
}

}

// GraphicButton Destructor
GraphicButton::~GraphicButton ( )
{
   delete fUpGraphic;
   delete fDownGraphic;
   delete fGraphicButtonHandler;

}

// Return the unlatched graphic.
IGraphic* GraphicButton::upGraphic ( ) const
{
  return fUpGraphic;
}

// Return the latched graphic.
IGraphic* GraphicButton::downGraphic ( ) const
{
  return fDownGraphic;
}


//  Calculate the size of the graphic button (including
// the base button and the graphic).
ISize GraphicButton::calcMinimumSize ( ) const
{
  IGraphicContext gc(this->handle());
  ISize buttonSize = ICustomButton::calcMinimumSize();
  unsigned long 
    upGraphicHeight = fUpGraphic->boundingRect(gc).size().height();
  unsigned long 
    downGraphicHeight = fDownGraphic->boundingRect(gc).size().height();
  if (upGraphicHeight > downGraphicHeight)
    buttonSize += ISize(0, upGraphicHeight);
  else
    buttonSize += ISize(0, downGraphicHeight);
  return buttonSize;
}

// Draw the foreground of the button.
void GraphicButtonHandler::drawForeground (ICustomButtonDrawEvent& event)
{
  // Store the graphic context.
  IGraphicContext& gc = event.graphicContext();

  // Determine and set the recoordination height so that the
  // code is portable.  (We draw in Windows coordinates here.)
  GraphicButton* graphicButton = (GraphicButton*)event.customButton();
  IRectangle drawingRect = event.drawingArea();
#ifndef IC_PM // Remove #ifndef when PM supports this.
  gc.setRecoordinationHeight(graphicButton->size().height());
#endif

  // Determine which graphic to draw.
  IGraphic* graphic;
  if (event.drawUp() == true)
    graphic = graphicButton->upGraphic();
  else
    graphic = graphicButton->downGraphic();

  // Determine the size of the graphic.
  IPoint graphicPos;
  ISize  graphicSize;
  graphicSize = graphic->boundingRect(gc).size();

  // Center graphic horizontally.
  graphicPos.setX(drawingRect.minX()+((drawingRect.width()-graphicSize.width())/2));
  graphicPos.setY(drawingRect.minY()+2);

  // Draw the graphic.
  graphic->translateBy(graphicPos);
  graphic->drawOn(gc);
  graphic->translateBy(-graphicPos);

  // Update the drawing area so that it only includes the
  // space below our graphic (where we want the text drawn).
  drawingRect.sizeTo(
         ISize(drawingRect.width(),
               drawingRect.height()-graphicSize.height()));
  drawingRect.moveBy(ISize(0,graphicSize.height()));
  event.setDrawingArea(drawingRect);

  // Call our inherited class to draw the text. 
  Inherited::drawForeground(event);
}
