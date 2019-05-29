//************************************************************
// Fonts - Using Advanced Font Functions
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <iapp.hpp>
#include <icolor.hpp>
#include <ifont.hpp>
#include <iframe.hpp>
#include <igrafctx.hpp>
#include <iglist.hpp>
#include <igstring.hpp>
#include <ipoint.hpp>
#include <istring.hpp>
#include "advfont.hpp"

// Specific font names vary between operating systems,
// complicating the issue of writing portable applications.
// Avoid hardcoding the names in the code as follows:
#ifdef IC_PM
#define OS_FONT_1   "Helvetica"
#else  // Windows
#define OS_FONT_1   "Arial"
#endif

IColor colArray[8] = { IColor::blue, IColor::red, IColor::green,
                       IColor::black, IColor::cyan, IColor::yellow,
                       IColor::pink, IColor::darkGray };
IPoint ptArray[16] = { IPoint(0,4), IPoint(1,3), IPoint(2,2),
                       IPoint(3,1), IPoint(4,0), IPoint(3,-1),
                       IPoint(2,-2), IPoint(1,-3), IPoint(0,-4),
                       IPoint(-1,-3), IPoint(-2,-2), IPoint(-3,-1),
                       IPoint(-4,0), IPoint(-3,1), IPoint(-2,2),
                       IPoint(-1,3) };

void main()
{
  // Create the frame and a canvas client to draw on.
  IFrameWindow aFrame( "Using Advanced Font Functions" );
  FontDrawingArea aClient( IC_FRAME_CLIENT_ID,
                           &aFrame, &aFrame );
  aFrame.setClient( &aClient );

  // Size and show the frame and run the application.
  aFrame
    .moveSizeToClient( aClient.rect() )
    .setFocus()
    .show();
  IApplication::current().run();
}


/*------------------------------------------------------------------------------
| FontDrawingArea - Construct an IDrawing canvas and paint the pattern         |
|                   in the middle, adding all graphic strings to the list.     |
------------------------------------------------------------------------------*/
FontDrawingArea::FontDrawingArea( unsigned long windowId, IWindow* parent,
                                  IWindow* owner, const IRectangle& initial )
  : IDrawingCanvas( windowId, parent, owner, initial,
                    IDrawingCanvas::defaultStyle() | IWindow::clipSiblings )
{
  // Initialize string with a catchy phrase.
  IString str( "PowerGUI Programming is COOL!" );

  // Get the graphic context of the canvas for drawing.
  IGraphicContext gc( this->handle() );

  // Create a graphic bundle for setting colors.
  IGraphicBundle gb(gc);

  // Create a graphic list for saving graphic strings.
  this->setGraphicList( new IGList() );

  // Create a font object, providing name and point size.
  IFont font( OS_FONT_1, 14, false, true );
  font.setBold();

  // Calculate the size of the displayed string in this font
  // and size the window accordingly, adding a buffer each way.
  unsigned long stringSize = font.textWidth( str );
  IRectangle drawRect( IPoint( 20, 30 ),
                       ISize( 2*stringSize+30, 2*stringSize+30 ));
  this->moveSizeTo( drawRect );

  // Get the center point of the font drawing area.
  IPoint point( drawRect.centerXCenterY() );
  point -= IPoint( 20, 20 );

  // Iterate through the list of angles and colors, changing the font
  // and graphic attributes and build a list of graphic strings drawn
  // at that angle with those colors.
  int i;
  for ( i=0; i<16; i++ )
  {
#ifdef IC_WIN
    font.setFontShear( ptArray[i] );
#endif
    font.setFontAngle( ptArray[i] );
    gb.setPenColor( colArray[i%8] );

    // Create a graphic string, starting at point
    // with text and font you want.
    IGString* text = new IGString( str, point, font );
    text->setGraphicBundle( gb );
    text->drawOn(gc);

    // Add the graphic string (with attributes) to the list.
    this->graphicList()->addAsLast( *text );
  }
}


/*------------------------------------------------------------------------------
| FontDrawingArea - Destroy the IDrawing canvas and free all of the graphic    |
|                   strings in the list and the list itself.                   |
------------------------------------------------------------------------------*/
FontDrawingArea::~FontDrawingArea( )
{
  // Delete all the graphic objects in the drawing canvas.
  IGList::Cursor graphicsCursor( *graphicList() );
  for ( graphicsCursor.setToFirst();
        graphicsCursor.isValid();
        graphicsCursor.setToNext() )
  {
    IGraphic* graphic(&(graphicList()->graphicAt(graphicsCursor)));
    delete graphic;
  } /* endfor */
  delete graphicList();
}


