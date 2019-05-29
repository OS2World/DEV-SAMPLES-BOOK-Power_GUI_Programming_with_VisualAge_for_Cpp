/***************************************************************
* FILE NAME: service.cpp                                       *
*                                                              *
* DESCRIPTION:                                                 *
*   This file contains the implementation of                   *
*   classes/functions declared in service.hpp.                 *
*                                                              *
* COPYRIGHT:                                                   *
*   Licensed Materials - Property of Solution Frameworks       *
*   Copyright (C) 1996, Solution Frameworks                    *
*   All Rights Reserved                                        *
***************************************************************/
#include "service.hpp"

#ifndef _ITHREAD_
  #include <ithread.hpp>
#endif
#ifndef _IOBJWIN_
  #include <iobjwin.hpp>
#endif
#ifndef _USEREVT_
  #include "userevt.hpp"
#endif
#ifndef _SIGNAL_
  #include "signal.hpp"
#endif

struct ServiceThreadData {
  ServiceThreadData ( ) {
    objWin = 0;
  }
IThread
  thread;
IObjectWindow
 *objWin;
Signal
  signal;
ServiceThreadData ( const ServiceThreadData& );
operator = ( const ServiceThreadData& );
}; // ServiceThreadData

/*--------------- ServiceThread::ServiceThread -----------------
| The constructor allocates this object's implementation data. |
| It then starts the secondary thread and waits for that       |
| thread to become "ready."                                    |
--------------------------------------------------------------*/
ServiceThread :: ServiceThread ( )
  : data( new ServiceThreadData ) {
  data->thread.start( (IThread::OptlinkFnPtr)ServiceThread::run, 
                      data );
  data->signal.wait();
}

/*-------------- ServiceThread::~ServiceThread -----------------
| The destructor posts a WM_QUIT to the secondary thread       |
| (using IThread::stopProcessingMsgs).  It does *not* delete   |
| the object's data as the secondary thread is still using it. |
| The service thread will delete this object's data when it    |
| terminates.                                                  |
--------------------------------------------------------------*/
ServiceThread :: ~ServiceThread ( ) {
  data->thread.stopProcessingMsgs();
}

/*---------------- ServiceThread::postRequest ------------------
| A user-defined event is posted to the object window on the   |
| service thread.  We pass the address (effectively) of the    |
| IThreadFn object.                                            |
--------------------------------------------------------------*/
void ServiceThread :: postRequest 
                      ( const IReference<IThreadFn> &request ) {
  (*request).addRef();
  UserEvent( 0, (void*)(IThreadFn*)request )
    .postTo( data->objWin->handle() );
}

/*---------------------- ServiceHandler ------------------------
| This class handles user-defined events posted to the service |
| thread's object window.                                      |
|                                                              |
| It simply invokes the run() function against the IThreadFn   |
| referenced by mp1.                                           |
--------------------------------------------------------------*/
struct ServiceHandler : public UserHandler {
  ServiceHandler ( IObjectWindow *objWin ) {
    handleEventsFor( objWin );
  }

virtual Boolean
  dispatchHandlerEvent ( IEvent &event ) {
    return UserHandler::dispatchHandlerEvent( event );
  }

virtual Boolean
  handleUserEvent ( UserEvent &event ) {
    IThreadFn
     *request = (IThreadFn*)(void*)event.parameter1();
 
    request->run();

    request->removeRef();

    return true;
  }
}; // ServiceHandler

/*-------------------- ServiceThread::run ----------------------
| This static member function executes on the service thread.  |
| It is passed the ServiceThreadData as input.  We create an   |
| object window, post the signal (to tell the thread that      |
| created this service thread that it's now ready), and        |
| process user-defined events that come in to that object      |
| window.                                                      |
|                                                              |
| When the owner cancels this thread (by posting a WM_QUIT,    |
| most likely via IThread::stopProcessingMsgs), we delete      |
| the argument ServiceThreadData.                              |
--------------------------------------------------------------*/
void ServiceThread :: run ( void *arg ) {
  ServiceThreadData
    *data = (ServiceThreadData*)arg;

  data->objWin = new IObjectWindow;
  data->objWin->setAutoDeleteObject( true );

  data->signal.signal();

  ServiceHandler
    handler( data->objWin );

  IThread::current().processMsgs();

  delete data;
}
