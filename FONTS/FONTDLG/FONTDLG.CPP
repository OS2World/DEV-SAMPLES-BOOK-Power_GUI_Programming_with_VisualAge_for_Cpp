//************************************************************
// Views - Using the Font Dialog
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <iapp.hpp>
#include <icolor.hpp>
#include <ifont.hpp>
#include <ifontdlg.hpp>
#include <igrafctx.hpp>
#include <iglist.hpp>
#include <igstring.hpp>
#include <ipoint.hpp>
#include <istring.hpp>
#include "fontdlg.hpp"
#include "fontdlg.h"

// Specific font names vary between operating systems,
// complicating the issue of writing portable applications.
// Avoid hardcoding the names in the code as follows:
#ifdef IC_PM
#define OS_FONT_1   "Helvetica"
#else  // Windows
#define OS_FONT_1   "Arial"
#endif

IColor colArray[8] = { IColor::blue, IColor::red, IColor::green, IColor::black,
                       IColor::cyan, IColor::yellow, IColor::pink, IColor::darkGray };
IPoint ptArray[16] = { IPoint(0,4), IPoint(1,3), IPoint(2,2), IPoint(3,1),
                       IPoint(4,0), IPoint(3,-1), IPoint(2,-2), IPoint(1,-3),
                       IPoint(0,-4), IPoint(-1,-3), IPoint(-2,-2), IPoint(-3,-1),
                       IPoint(-4,0), IPoint(-3,1), IPoint(-2,2), IPoint(-1,3) };

void main()
{
  // Create the font dialog example window.
  FontDialogExample aFrame( "Using the Font Dialog" );

  // Show the example window and run the application.
  aFrame
    .setFocus()
    .show();
  IApplication::current().run();
}


/*------------------------------------------------------------------------------
| FontDialogExample                                                            |
|   Construct the frame, initial font and drawing area and attach              |
|   the command handler.  Size the frame to match the client area.             |
------------------------------------------------------------------------------*/
FontDialogExample::FontDialogExample( char* title )
  : IFrameWindow( title, MAIN_WINDOW,
     IFrameWindow::defaultStyle() | IFrameWindow::menuBar ),
    currentFont( OS_FONT_1, 14, false, true ),
    currentArea( IC_FRAME_CLIENT_ID, this, this, currentFont )
{
  this->setClient( &currentArea );
  handleEventsFor( this );
  this->moveSizeToClient( currentArea.rect() );
}


/*------------------------------------------------------------------------------
| FontDialogExample::updateDemo                                                |
|   Update the font drawing area with the new font.                            |
------------------------------------------------------------------------------*/
FontDialogExample& FontDialogExample::updateDemo( IFont& newFont )
{
  currentArea.disableUpdate();
  currentArea.refreshList( newFont );
  currentArea.enableUpdate();
  this->moveSizeToClient( currentArea.rect() );

  return *this;
}


/*------------------------------------------------------------------------------
| FontDialogExample::command                                                   |
|   Handle menu commands.                                                      |
------------------------------------------------------------------------------*/
IBase::Boolean FontDialogExample::command( ICommandEvent& cmdEvent )
{
  switch ( cmdEvent.commandId() )
  {
    case MI_FONTDLG:
    {
#if (IC_MAJOR_VERSION > 310)
      // Create a font dialog handler, passing the frame
      // window for use during modeless processing.
      MyDlgHandler applyHandler( this );
#endif
      // Initialize a settings object with the current font.
      IFontDialog::Settings settings( &currentFont );

      // Set the preview text, title and initial position.
      settings.setPreviewText( "PowerGUI is COOL!" );
      settings.setTitle( "Select a New Font" );
      settings.setPosition( IPoint( 450, 2 ) );

      // Create a modeless dialog, containing an apply button
      // and only list vector fonts.  Attach the font dialog
      // handler created above to handle the apply button.
      IFontDialog fntDlg( IWindow::desktopWindow(), this,
#if (IC_MAJOR_VERSION > 310)
                          &applyHandler,
                          IFontDialog::modeless |
#endif
                          IFontDialog::applyButton |
                          IFontDialog::vectorOnly, settings );

      // Check if a user selected a font and if so, update
      // the drawing area using the new font.
      if (fntDlg.pressedOK())
        this->updateDemo( currentFont );

      return (true);
    }

    case MI_EXIT:
      this->close();
      return(true);
  }

  return(false);
}


/*------------------------------------------------------------------------------
| FontDrawingArea - Construct an IDrawing canvas and paint the pattern         |
|                   in the middle, adding all graphic strings to the list.     |
------------------------------------------------------------------------------*/
FontDrawingArea::FontDrawingArea( unsigned long windowId, IWindow* parent,
                                  IWindow* owner, IFont& initialFont )
  : IDrawingCanvas( windowId, parent, owner, IRectangle(),
                    IDrawingCanvas::defaultStyle() | IWindow::clipSiblings )
{
  refreshList( initialFont );
}


/*------------------------------------------------------------------------------
| ~FontDrawingArea - Destroy the IDrawing canvas and free all of the graphic   |
|                    strings in the list and the list itself.                  |
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
  }
  delete graphicList();
}


/*------------------------------------------------------------------------------
| FontDrawingArea::refreshList                                                 |
|   Create the graphic strings with the correct font, angles, colors and       |
|   add them to the graphic list for drawing by the handler.                   |
------------------------------------------------------------------------------*/
FontDrawingArea& FontDrawingArea::refreshList( IFont& newFont )
{
  // Delete any graphic objects in the drawing canvas.
  if ( graphicList() )
  {
    IGList::Cursor graphicsCursor( *graphicList() );
    for ( graphicsCursor.setToFirst();
          graphicsCursor.isValid();
          graphicsCursor.setToNext() )
    {
      IGraphic* graphic(&(graphicList()->graphicAt(graphicsCursor)));
      delete graphic;
    }
    delete graphicList();
  }

  // Initialize string with a catchy phrase.
  IString str( "PowerGUI Programming is COOL!" );

  // Get the graphic context of the canvas for drawing.
  IGraphicContext gc( this->handle() );

  // Create a graphic bundle for setting colors.
  IGraphicBundle gb(gc);

  // Create a graphic list for saving graphic strings.
  this->setGraphicList( new IGList() );

  IFont font( newFont );

  // Calculate the size of the displayed string in this font
  // and size the window accordingly, adding a buffer each way.
  unsigned long strSize = font.textWidth( str );
  IRectangle drawRect( IPoint( 20, 40 ),
                       ISize( 2*strSize+30, 2*strSize+30 ));
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
  return *this;
}

#if (IC_MAJOR_VERSION > 310)
/*------------------------------------------------------------------------------
| MyDlgHandler::modelessApply                                                  |
|   Handle the press of the apply button for the modeless font dialog.         |
------------------------------------------------------------------------------*/
IBase::Boolean MyDlgHandler::modelessApply( IFontDialog* modelessDialog,
                                            IFont*       appliedFont )
{
  fhwnd->updateDemo( *appliedFont );
  return true;
}
#endif
