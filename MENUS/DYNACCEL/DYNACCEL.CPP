//*********************************************************
// Menus - Dynamic Accelerator Keys
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//*********************************************************
#include <iapp.hpp>
#include <icconst.h>
#include <icheckbx.hpp>
#include <icmdhdr.hpp>
#include <icolor.hpp>
#include <iframe.hpp>
#include <isetcv.hpp>
#include <istattxt.hpp>
#include "accelupd.hpp"

#define ID_RED     10
#define ID_GREEN   11
#define ID_CYAN    12
#define ID_PINK    13

#define CMD_RED    100
#define CMD_GREEN  101
#define CMD_CYAN   102
#define CMD_PINK   103

// This command handler changes the color of a window.
class ColorCmdHandler : public ICommandHandler {
public:
  ColorCmdHandler ( IWindow& colorWindow )
    : fColorWindow( colorWindow )
  { }
protected:
virtual Boolean
  command ( ICommandEvent& event )
  {
    Boolean
      stopProcessingEvent = false;
    switch ( event.commandId() )
    {
      case CMD_RED:
        fColorWindow
         .setForegroundColor( IColor::white )
         .setBackgroundColor( IColor::red );
        stopProcessingEvent = true;
        break;
      case CMD_GREEN:
        fColorWindow
         .setForegroundColor( IColor::white )
         .setBackgroundColor( IColor::green );
        stopProcessingEvent = true;
        break;
      case CMD_CYAN:
        fColorWindow
         .setForegroundColor( IColor::blue )
         .setBackgroundColor( IColor::cyan );
        stopProcessingEvent = true;
        break;
      case CMD_PINK:
        fColorWindow
         .setForegroundColor( IColor::blue )
         .setBackgroundColor( IColor::pink );
        stopProcessingEvent = true;
        break;
      default:
        break;
    }
    return stopProcessingEvent;
  }
private:
  ColorCmdHandler ( const ColorCmdHandler& );
ColorCmdHandler
 &operator=       ( const ColorCmdHandler& );
IWindow
 &fColorWindow;
}; // ColorCmdHandler

void main ( )
{
  // Create a frame window with a static text control that
  // changes color based on the press of accelerator keys.
  IFrameWindow
    frame( "Dynamic Accelerator Keys" );
  IStaticText
    testArea( IC_FRAME_CLIENT_ID, &frame, &frame );
  testArea
   .setAlignment( IStaticText::centerCenter )
   .setText( "Change this color by pressing an "
             "accelerator key" );

  ISetCanvas
    instructions( 1, &frame, &frame );
  instructions
   .setDeckOrientation( ISetCanvas::vertical );
  IStaticText
    instructions1( 2, &instructions, &instructions ),
    instructions2( 3, &instructions, &instructions );
  instructions1
   .setText( "Enable and disable accelerator keys by "
             "selecting check boxes." );
  instructions2
   .setText( "Press accelerator keys to change the color "
             "of the test area." );

  ISetCanvas
    accelChoices( 4, &frame, &frame );
  accelChoices
   .setDeckOrientation( ISetCanvas::vertical );
  ICheckBox
    redChoice( ID_RED, &accelChoices, &accelChoices ),
    greenChoice( ID_GREEN, &accelChoices, &accelChoices ),
    cyanChoice( ID_CYAN, &accelChoices, &accelChoices ),
    pinkChoice( ID_PINK, &accelChoices, &accelChoices );
  redChoice
   .setText( "Ctrl+R = Red" )
   .enableTabStop()
   .enableGroup();
  greenChoice
   .setText( "F5 = Green" );
  cyanChoice
   .setText( "Ctrl+\\ = Cyan" );
  pinkChoice
   .setText( "Ctrl+Shift+Alt+Home = Pink" );

  // Create a command handler to process the accelerator keys.
  ColorCmdHandler
    cmdHandler( testArea );
  cmdHandler
   .handleEventsFor( &frame );

  // Create a selection handler to add or remove accelerator
  // keys.
  AccelSelectHandler
    selHandler( frame );
  selHandler
   .handleEventsFor( &accelChoices );

  // Show the window.
  frame
   .setClient( &testArea )
   .addExtension( &instructions, IFrameWindow::aboveClient )
   .addExtension( &accelChoices, IFrameWindow::leftOfClient )
   .setFocus()
   .show();

  IApplication::current().run();
}
