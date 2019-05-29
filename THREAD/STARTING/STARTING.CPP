/***************************************************************
* FILE NAME: starting.cpp                                      *
*                                                              *
* DESCRIPTION:                                                 *
*   This file contains a sample program that demonstrates      *
*   all the ways in which you can start threads using IThread. *                              
*                                                              *
* COPYRIGHT:                                                   *
*   Licensed Materials - Property of Solution Frameworks       *
*   Copyright (C) 1996, Solution Frameworks                    *
*   All Rights Reserved                                        *
***************************************************************/
#ifdef __OS2__
#define INCL_DOSPROCESS
#include <os2.h>
#else
#include <windows.h>
#include "wrapper.hpp"
#endif

#include <ithread.hpp>
#include <iframe.hpp>
#include <ipushbut.hpp>
#include <imsgbox.hpp>
#include <istring.hpp>
#include <icmdhdr.hpp>

static const IMessageBox::Style
  mbStyle = IMessageBox::moveable | IMessageBox::okButton;

/*--------------------- compatibleWithOS -----------------------
| This function is compatible with the operating               |
| system functions DosCreateThread (on OS/2) or                |
| CreateThread (on Windows).                                   |
--------------------------------------------------------------*/
#ifdef IC_PM
void _System compatibleWithOS( unsigned long arg ) {
#define RETURN return
#else
unsigned long _stdcall compatibleWithOS( void *arg ) {
#define RETURN return 0
#endif

  const char
   *text = (const char *)arg;

  IMessageBox
    msgBox( IWindow::desktopWindow() );

  IString
    title = IString( "compatibleWithOS on thread " ) +
              IThread::current().id().asString();

  msgBox
    .setTitle( title )
    .show( text, mbStyle );

  RETURN;
}

/*------------------ compatibleWithCLibrary --------------------
| This function is compatible with the C library function      |
| _beginthread .                                               |
---------------------------------------------------------------*/
void _Optlink compatibleWithCLibrary( void *arg ) {
  const char
   *text = (const char *)arg;

  IMessageBox
    msgBox( IWindow::desktopWindow() );

  IString
    title = IString( "compatibleWithCLibrary on thread " ) +
              IThread::current().id().asString();

  msgBox
    .setTitle( title )
    .show( text, mbStyle );
}

enum { createThread = 1,
       beginthread, 
       createThreadUsingIThreadStart,
       createThreadUsingIThreadCtor,
       beginThreadUsingIThreadStart,
       beginThreadUsingIThreadCtor };

/*---------------------- ThreadStarter -------------------------
| This class is a command handler that handles the starting of |
| threads using any of the six different methods.              |
--------------------------------------------------------------*/
class ThreadStarter : public ICommandHandler {
public:
virtual Boolean
  command ( ICommandEvent &event ) {
    switch ( event.commandId() ) {
      case createThread:
        #ifdef IC_PM
          TID
            tid;
          DosCreateThread( &tid, 
                           compatibleWithOS,
                           (unsigned long)"Started via DosCreateThread",
                           0,
                           0x4000 );
        #else
          DWORD
            tid;
          CreateThread( 0, 
                        0x4000, 
                        compatibleWithOS,
                        (void *)"Started via CreateThread",
                        0,
                        &tid );
        #endif
        break;
      case beginthread:
        _beginthread( compatibleWithCLibrary,
                      0,
                      0x4000,
                      (void *)"Started via _beginthread" );
        break;
      case createThreadUsingIThreadStart:
        {
        IThread
          newThread;
        #ifdef IC_PM
          newThread.start( compatibleWithOS, 
                           (unsigned long)"Started via IThread::start" );
        #else
          newThread.start( WrapperFor< compatibleWithOS >(),
                           (void *)"Started via IThread::start" );
        #endif
        }
        break;
      case createThreadUsingIThreadCtor:
        {
        #ifdef IC_PM
          IThread
            newThread( compatibleWithOS,
                       (unsigned long)"Started via IThread ctor" );
        #else
          IThread
            newThread( WrapperFor< compatibleWithOS >(),
                       (void *)"Started via IThread ctor" );
        #endif
        }
        break;
      case beginThreadUsingIThreadStart:
        {
        IThread
          newThread;
        newThread.start( compatibleWithCLibrary,
                         (void*)"Started via IThread::start" );
        }
        break;
      case beginThreadUsingIThreadCtor:
        {
        IThread
          newThread( compatibleWithCLibrary,
                     (void*)"Started via IThread ctor" );
        }
        break;
    }
    return false;
  }
}; // ThreadStarter

void main() {
  IFrameWindow
    frame( "Starting Threads" );

  IPushButton
    button1( createThread, &frame, &frame ),
    button2( beginthread, &frame, &frame ),
    button3( createThreadUsingIThreadStart, &frame, &frame ),
    button4( createThreadUsingIThreadCtor, &frame, &frame ),
    button5( beginThreadUsingIThreadStart, &frame, &frame ),
    button6( beginThreadUsingIThreadCtor, &frame, &frame );

  #ifdef IC_PM
    button1.setText( "compatibleWithOS via DosCreateThread" );
  #else
    button1.setText( "compatibleWithOS via CreateThread" );
  #endif
  button2.setText( "compatibleWithCLibrary via _beginthread" );
  button3.setText( "compatibleWithOS via IThread::start" );
  button4.setText( "compatibleWithOS via IThread ctor" );
  button5.setText( "compatibleWithCLibrary via IThread::start" );
  button6.setText( "compatibleWithCLibrary via IThread ctor" );

  frame
    .addExtension( &button1, IFrameWindow::aboveClient, 0.17 )
    .addExtension( &button2, IFrameWindow::aboveClient, 0.20 )
    .addExtension( &button3, IFrameWindow::aboveClient, 0.25 )
    .addExtension( &button4, IFrameWindow::aboveClient, 0.33 )
    .addExtension( &button5, IFrameWindow::aboveClient, 0.5 )
    .addExtension( &button6, IFrameWindow::aboveClient, 0.99 )
    .moveSizeTo  ( frame.rect().scaleBy( 0.5 ) )
    .setFocus();

  ThreadStarter
    handler;

  handler.handleEventsFor( &frame );

  frame.showModally();
}
