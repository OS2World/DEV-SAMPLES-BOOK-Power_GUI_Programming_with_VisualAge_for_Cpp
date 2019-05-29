/***************************************************************
* FILE NAME: threads.cpp                                       *
*                                                              *
* DESCRIPTION:                                                 *
*   Comprehensive IThread demonstration program.               *
*                                                              *
* COPYRIGHT:                                                   *
*   Licensed Materials - Property of Solution Frameworks       *
*   Copyright (C) 1996, Solution Frameworks                    *
*   All Rights Reserved                                        *
***************************************************************/
#include <iframe.hpp>
#include <icnr.hpp>
#include <ithread.hpp>
#include <icnrmhdr.hpp>
#include <ipopmenu.hpp>
#include <istattxt.hpp>
#include <istparse.hpp>
#include <isubmenu.hpp>
#include <itimer.hpp>

#include "threads.h"

#include "thread.hpp"

#include "cmdroutr.hpp"

/*-------------------- ThreadsMenuHandler ----------------------
| This derived ICnrMenuHandler class handles popup menu        |
| requests on the main window.  If the popup is over empty     |
| space, it puts up the new/exit menu.  Otherwise, it          |
| requests a popup menu from the selected Thread object.       |                         
--------------------------------------------------------------*/
class ThreadsMenuHandler : public ICnrMenuHandler {
public:
  ThreadsMenuHandler ( IContainerControl &cnr ) 
    : ICnrMenuHandler(),
      cnr( cnr ),
      pThreadObj(0),
      router( cnr, *this, handleCommand ) {
    this->handleEventsFor( &cnr );
  }
protected:
virtual Boolean
  makePopUpMenu ( IMenuEvent &event ) {
    Boolean
      result = false;

    pThreadObj = (Thread*)( this->popupMenuObject() );

    if ( pThreadObj ) {
      result = pThreadObj->makePopUpMenu( event );
    } else {
      IPopUpMenu
       *pMenu = new IPopUpMenu( THREADS_POPUP, &cnr );
      pMenu->setAutoDeleteObject();
      pMenu->show( event.mousePosition() );
      result = true;
    }

    return result;
  }

private:
Boolean
  handleCommand( ICommandEvent &cmd ) {
    Boolean
      result = false;

    switch ( cmd.commandId() ) {
      case THREADS_NEW:
        {
        new Thread( cnr );
        result = true;
        }
        break;

      case THREADS_EXIT:
        IThread::current().stopProcessingMsgs();
        result = true;
        break;

      default:
        // Pass command to the selected Thread.
        if ( pThreadObj ) {
          result = pThreadObj->handleCommand( cmd );
          cnr.refresh();
        }
        break;
    }
    return result;
  }
IContainerControl
 &cnr;
Thread
 *pThreadObj;
CommandRouter<ThreadsMenuHandler>
  router;
ThreadsMenuHandler ( const ThreadsMenuHandler& );
operator = ( const ThreadsMenuHandler& );
}; // ThreadsMenuHandler

/*--------------------------- main -----------------------------
| Create the main window with container control and attach our |
| menu handler.  We create the first Thread object for the     |
| primary thread and go.                                       |
--------------------------------------------------------------*/
void main() {
  IFrameWindow
    frame( "IThread Sample Program, Process "
           +
           IApplication::current().id().asString() );

  IRectangle
    initRect = IFrameWindow::nextShellRect().scaleBy( 0.66, 0.5 );

  IContainerControl
    client( 0, &frame, &frame );

  ThreadsMenuHandler
    menuHandler( client );

  frame
    .setClient( &client )
    .setIcon( THREAD1 )
    .moveSizeTo( initRect )
    .setFocus()
    .show();

  new Thread( client, true );

  Thread::addColumnsTo( client );

  client
    .showDetailsView()
    .showDetailsViewTitles()
    .refresh();

  IThread::current().processMsgs();

  // Destroy all the Threads.
  client.deleteAllObjects();
}
