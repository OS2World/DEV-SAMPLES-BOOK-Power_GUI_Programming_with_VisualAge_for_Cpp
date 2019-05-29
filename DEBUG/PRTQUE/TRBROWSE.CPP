//************************************************************
// Problem Determination  - Trace Queue Browser
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <ifont.hpp>
#include "trbrowse.hpp"
#include "trbrowse.h"

TraceBrowser::TraceBrowser ( const IString& queueName )
       : IFrameWindow("Trace Browser"),
         queueHandler(*this),
         cnrWin        (IC_FRAME_CLIENT_ID, this, this, IRectangle(),
                        IContainerControl::defaultStyle() |
                        IContainerControl::noSharedObjects ),
         reader      (queueName, this->handle()),
         thread      ( )
{
  // Attach handler to our frame.
  queueHandler.handleEventsFor(this);

  // Change the font & show text view with extended selection.
  IFont font("Courier", 8);
  container()
    .showTextView()
    .setExtendedSelection()
    .setFont(font);

  // Make the container the client and start the queue.
  (*this)
    .setClient(&container())
    .postEvent(START_QUEUE);
}

IBase::Boolean  TraceBrowserHandler::dispatchHandlerEvent ( IEvent& event )
{
  switch (event.eventId())
  {
     case ADD_OBJECT:
     {
       browserWindow.container()
         .addObject((IContainerObject*)(void*)event.parameter1());
       return true;
     }
     case START_QUEUE:
     {
       // Start Reader in a separate Thread.
       browserWindow.readerThread()
          .start(new IThreadMemberFn<QueueReader>
                 (browserWindow.queueReader(),
                  QueueReader::run));
       return true;
     }
     default:
        break;
  } // endswitch
  return false;
}
