//*********************************************************
// Frame Window Basics - Dismissing a Window
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//*********************************************************
#include <icmdhdr.hpp>
#include <iframe.hpp>
#include <ipushbut.hpp>
#include <istattxt.hpp>
#include <istring.hpp>
#include <icconst.h>

#ifdef IC_PM
  // Define the system command identifier not originally
  // included in VisualAge for C++ for OS/2, V3.0.
  #ifndef IC_ID_CLOSE
    #define IC_ID_CLOSE  0x8004
  #endif
#endif

#define AGAIN_CMD  100

class CmdHandler : public ICommandHandler {
public:
  CmdHandler ( IFrameWindow& frame )
    : frame( frame )
  {
    this->handleEventsFor( &frame );
  }
protected:
virtual Boolean
  command ( ICommandEvent& event )
  {
    Boolean
      stopProcessingEvent = false;
    if ( event.commandId() == AGAIN_CMD )
    {
       frame.dismiss( event.commandId() );
       stopProcessingEvent = true;
    }
    return stopProcessingEvent;
  }
private:
CmdHandler
 &operator= ( CmdHandler& );
IFrameWindow
 &frame;
}; // CmdHandler

void main ( )
{
  IFrameWindow
    frameWindow( "Using IFrameWindow::dismiss" );
  IStaticText
    text( IC_FRAME_CLIENT_ID, &frameWindow, &frameWindow );
  frameWindow
   .setClient( &text );

  IPushButton
    againButton( AGAIN_CMD, &frameWindow, &frameWindow );
  againButton
   .setText( "Show the window again." );
  frameWindow
   .addExtension( &againButton,
                  IFrameWindow::belowClient );

  CmdHandler
    handler( frameWindow );

  // Keep displaying the frame window until the user has
  // closed it via some means other than the "Again"
  // push button (for example, pressing Alt+F4).
  frameWindow
   .setResult( AGAIN_CMD);
  for ( int i = 1; frameWindow.result() == AGAIN_CMD; i++ )
  {
     text.setText( "Display Number " + IString( i ) );
     frameWindow.setResult( IC_ID_CLOSE );
     frameWindow.setFocus();
     frameWindow.showModally();
  }
}
