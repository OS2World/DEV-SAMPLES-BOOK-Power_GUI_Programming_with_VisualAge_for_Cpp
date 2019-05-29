//*********************************************************
// Reusable Commands - Processing Mouse Pointer Movement
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc.
// All Rights Reserved.
//*********************************************************
#include <iapp.hpp>
#include <icoordsy.hpp>
#include <idrawcv.hpp>
#include <iframe.hpp>
#include <igbundle.hpp>
#include <igelipse.hpp>
#include <iglist.hpp>
#include <igpyline.hpp>
#include <igrafctx.hpp>
#include <igrect.hpp>
#include <ihandle.hpp>
#include <imoushdr.hpp>
#include <iptarray.hpp>
#include <istattxt.hpp>
#include <ivport.hpp>
#include <icconst.h>

#define ID_CIRCLE     1
#define ID_SQUARE     2
#define ID_RECTANGLE  3
#define ID_TRIANGLE   4
#define ID_ELLIPSE    5
#define ID_PENTAGON   6

class ShapeWindow : public IFrameWindow {
public:
  ShapeWindow ( );
 ~ShapeWindow ( );
protected:
Boolean
  processMouseMovement ( IMouseEvent& event );
private:
  ShapeWindow ( const ShapeWindow& );
ShapeWindow
 &operator=   ( const ShapeWindow& );
IStaticText
  instructions;
IViewPort
  viewPort;
IDrawingCanvas
  shapeArea;
IGraphicContext
 *gc;
IGList
  graphicList;
IMouseConnectionTo< ShapeWindow >
  mouseConnection;
}; // ShapeWindow

void main ( )
{
  ICoordinateSystem::setApplicationOrientation
                        ( ICoordinateSystem::originLowerLeft );

  ShapeWindow
    frame;
  frame
   .setFocus()
   .show();
  IApplication::current().run();
}

ShapeWindow::ShapeWindow ( )
  : IFrameWindow( "Mouse Movement Example"),
    instructions( 1, this, this ),
    viewPort( IC_FRAME_CLIENT_ID, this, this ),
    shapeArea( 1, &viewPort, &viewPort ),
    gc( 0 ),
    graphicList(),
    mouseConnection( *this, 0, ShapeWindow::processMouseMovement, 0 )
{
  instructions
   .setText( "Move the mouse pointer over a shape." );
  mouseConnection
   .handleEventsFor( &shapeArea );

  // Create a graphic context for the shapeArea window.  We do
  // this once to avoid a performance hit during mouse-movement
  // processing.
  gc = new IGraphicContext( shapeArea.presSpace() );
  shapeArea
   .setGraphicContext( gc );

  // Set up the shapes to draw in the shapeArea window.
  IGraphicBundle
    bundle;
  bundle
   .setBackgroundMixMode( IGraphicBundle::backOverPaint )
   .setDrawOperation( IGraphicBundle::fillAndFrame )
   .setPenWidth( 3 )
   .setPenJoiningStyle( IGraphicBundle::miter )
   .setPenColor( IColor::black )
   .setFillColor( IColor::green );

  // Create a circle.
  IGEllipse
   *circle = new IGEllipse( IPoint( 110, 110 ), 90 );
  (*circle)
   .setGraphicBundle( bundle )
   .setId( ID_CIRCLE );

  // Create a rectangle.
  IGRectangle
   *rectangle = new IGRectangle( IRectangle( IPoint( 170, 20 ),
                                             ISize( 170, 100 ) ) );
  bundle
   .setFillColor( IColor::red );
  (*rectangle)
   .setGraphicBundle( bundle )
   .setId( ID_RECTANGLE );

  // Create a square.
  IGRectangle
   *square = new IGRectangle( IRectangle( IPoint( 15, 190 ),
                                          ISize( 160, 160 ) ) );
  bundle
   .setFillColor( IColor::yellow );
  (*square)
   .setGraphicBundle( bundle )
   .setId( ID_SQUARE );

  // Create a triangle.
  IPoint trianglePoints[] =
    { IPoint( 320, 150 ), IPoint( 230, 370 ), IPoint( 360, 350 ) };
  IGPolygon
   *triangle = new IGPolygon( IPointArray( 3, trianglePoints ) );
  bundle
   .setFillColor( IColor::pink );
  (*triangle)
   .setGraphicBundle( bundle )
   .setId( ID_TRIANGLE );

  // Create an ellipse.
  IGEllipse
   *ellipse = new IGEllipse( IPoint( 200, 320 ), 60, 30 );
  bundle
   .setFillColor( IColor::blue );
  (*ellipse)
   .setGraphicBundle( bundle )
   .setId( ID_ELLIPSE );

  // Create a pentagon.
  IPoint pentagonPoints[] =
    { IPoint( 160, 200 ), IPoint( 220, 140 ), IPoint( 280, 200 ),
      IPoint( 260, 270 ), IPoint( 180, 270 ) };
  IGPolygon
   *pentagon = new IGPolygon( IPointArray( 5, pentagonPoints ) );
  bundle
   .setFillColor( IColor::cyan );
  (*pentagon)
   .setGraphicBundle( bundle )
   .setId( ID_PENTAGON );

  // Add all shapes to the list that the drawing canvas uses.
  graphicList
   .addAsLast( *square )
   .addAsLast( *circle )
   .addAsLast( *rectangle )
   .addAsLast( *triangle )
   .addAsLast( *ellipse )
   .addAsLast( *pentagon );
  shapeArea
   .setGraphicList( &graphicList );

  (*this)
   .setClient( &viewPort )
   .addExtension( &instructions, IFrameWindow::belowClient );
}

ShapeWindow::~ShapeWindow ( )
{
  // Clean up the graphic list that the shapeArea window uses.
  unsigned long
    count = graphicList.numberOfGraphics();
  while ( count-- )
  {
    IGraphic
     *graphic = graphicList.firstGraphic();
    graphicList
     .removeFirst();
    delete graphic;
  }

  // Clean up the graphic context that the shapeArea window uses.
  if ( shapeArea.isValid() )
  {
     shapeArea
      .releasePresSpace( gc->handle() );
  }
#ifdef IC_PM
  else
  {
     IWindow::desktopWindow()->releasePresSpace( gc->handle() );
  }
#endif
  delete gc;
}

// This is the function that the IMouseConnectionTo<> object calls.
IBase::Boolean ShapeWindow::processMouseMovement ( IMouseEvent& event )
{
  if ( event.windowUnderPointer() ==
         event.dispatchingWindow()->handle() )
  {      // The mouse pointer is over the drawing canvas.
     IGraphic
      *graphicUnderMousePointer =
          graphicList.topGraphicUnderPoint( event.mousePosition(), *gc );
     char
      *infoText = "Move the mouse pointer over a shape.";

     // Test if the mouse pointer is over a shape.
     if ( graphicUnderMousePointer )
     {        // Now figure out which shape.
        switch ( graphicUnderMousePointer->id() )
        {
          case ID_CIRCLE:
            infoText = "Circle";
            break;
          case ID_SQUARE:
            infoText = "Square";
            break;
          case ID_RECTANGLE:
            infoText = "Rectangle";
            break;
          case ID_TRIANGLE:
            infoText = "Triangle";
            break;
          case ID_ELLIPSE:
            infoText = "Ellipse";
            break;
          case ID_PENTAGON:
            infoText = "Pentagon";
            break;
          default:
            break;
        }
     }

     instructions
      .setText( infoText );
  }
  return false;
}
