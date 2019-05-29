//************************************************************
// Tool Bars  - Custom Button Handler Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <icustbut.hpp>
#include <icustbhd.hpp>
#include <istring.hpp>
#include <ipoint.hpp>

class IGraphic;
class GraphicButtonHandler;

// Define our graphic button as a custom button
// that stores a graphic to display.
class GraphicButton : public ICustomButton
{
typedef ICustomButton
  Inherited;
public:
   GraphicButton (unsigned long identifier,
                         IWindow*      parent,
                         IWindow*      owner,
                         const ISize&  graphicSize =
                                                ISize(40,40),
                         IGraphic*      upGraphicToAdopt = 0,
                         IGraphic*      downGraphicToAdopt = 0);
virtual 
  ~GraphicButton ( );


IGraphic
 *upGraphic       ( ) const,
 *downGraphic     ( ) const;


virtual ISize
  calcMinimumSize ( ) const;

private:
IGraphic
 *fUpGraphic,
 *fDownGraphic;

GraphicButtonHandler
 *fGraphicButtonHandler;

ISize
  fGraphicSize;

IString
  fUpText,
  fDownText;

 GraphicButton ( const GraphicButton&);
 GraphicButton& operator = (const GraphicButton&);
};

// Define a draw handler so that we can
// take over drawing the foreground.
class GraphicButtonHandler : public ICustomButtonDrawHandler
{
typedef ICustomButtonDrawHandler
  Inherited;
protected:
virtual void
  drawForeground (ICustomButtonDrawEvent& event);

};
