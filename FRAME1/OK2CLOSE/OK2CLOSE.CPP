//*********************************************************
// Frame Window Closing - Confirm Frame Closing
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc.
// All Rights Reserved.
//*********************************************************
#include <icmdhdr.hpp>
#include <iframe.hpp>
#include <imsgbox.hpp>
#include <istattxt.hpp>
#include <isysmenu.hpp>
#include <ithread.hpp>

class CloseHandler : public ICommandHandler {
public:
// Use this function to attach this handler to your frame.
virtual CloseHandler
 &handleClosingOf( IFrameWindow& frame )
  {
    this->ICommandHandler::handleEventsFor( &frame );
    return *this;
  }
// Override this function to insert your own "close" logic.
virtual Boolean
  systemCommand ( ICommandEvent& event )
  {
    Boolean
      stopProcessingEvent = false;
    if ( event.commandId() == ISystemMenu::idClose )
    {
       IFrameWindow
        *frame = (IFrameWindow*)( event.dispatchingWindow() );
       IMessageBox
         prompt( frame );
       const char
        *text = "Press Cancel to keep the window open. "
                "Press OK to let it close.";
       IMessageBox::Response
         rc = prompt.show( text,
                           IMessageBox::okCancelButton
                             | IMessageBox::informationIcon
                             | IMessageBox::moveable );
       if ( rc == IMessageBox::cancel )
       {
          stopProcessingEvent = true;
       }
    }
    return stopProcessingEvent;
  }
private:
virtual IHandler
 &handleEventsFor( IWindow* window )
  {
    return this->ICommandHandler::handleEventsFor( window );
  }
}; // CloseHandler

void main ( )
{
  IFrameWindow
    frame( "Confirm on Close" );
  IStaticText
    client( IC_FRAME_CLIENT_ID, &frame, &frame );
  client
   .setAlignment( IStaticText::centerCenter )
   .setText( "Press Alt+F4 to close this window." );
  frame
   .setClient( &client );

  CloseHandler
    closeHandler;
  closeHandler
   .handleClosingOf( frame );

  frame
   .setFocus()
   .show();

  IThread::current().processMsgs();
}
