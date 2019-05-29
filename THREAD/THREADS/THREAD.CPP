/***************************************************************
* FILE NAME: thread.cpp                                        *
*                                                              *
* DESCRIPTION:                                                 *
*   This file contains the implementation of                   *
*   classes/functions declared in thread.hpp.                  *
*                                                              *
* COPYRIGHT:                                                   *
*   Licensed Materials - Property of Solution Frameworks       *
*   Copyright (C) 1996, Solution Frameworks                    *
*   All Rights Reserved                                        *
***************************************************************/
#include <iframe.hpp>
#include <istattxt.hpp>
#include <itime.hpp>
#include <icnr.hpp>
#include <ithread.hpp>
#include <ipopmenu.hpp>
#include <icmdevt.hpp>
#include <ireslock.hpp>
#include <icritsec.hpp>
#include <istparse.hpp>
#include <istattxt.hpp>
#include <itimer.hpp>

#include "signal.hpp"

#include "threads.h"

#include "thread.hpp"

// Flag bits.
static const unsigned long
  isWaitingForPrivateResource = 1,
  isWaitingForSharedResource  = 2,
  isWaitingForPrivateSignal   = 4,
  isWaitingForSharedSignal    = 8,
  isWaiting                   = 15,
  isSuspended                 = 16,
  hasPrivateResource          = 32,
  hasSharedResource           = 64,
  isPrimary                   = 128;

// Style for secondary frames.
static IFrameWindow::Style
  frameStyle = IFrameWindow::titleBar 
                 | IFrameWindow::sizingBorder;

// Hidden data members.
struct ThreadData {
// Minimal constructor.
  ThreadData( IContainerControl &cnr )
    : frame      ( title(), IC_DEFAULT_FRAME_ID, frameStyle ),
      status     ( 1, &frame, &frame ),
      counter    ( 2, &frame, &frame ),
      rate       ( 3, &frame, &frame ),
      container  ( cnr ),
      flags      ( 0 ),
      nextAction ( 0 ),
      count      ( 0 ),
      thread     ( 0 ) {

    status.setAlignment( IStaticText::centerCenter );
    counter.setAlignment( IStaticText::centerCenter );
    rate.setAlignment( IStaticText::centerCenter );
    frame.setOwner( cnr.parent() );
    frame.setClient( &counter );
    frame.addExtension( &status, IFrameWindow::aboveClient, 25 );
    frame.addExtension( &rate, IFrameWindow::aboveClient, 25 );
    // Position each thread's window at origin of main window,
    // offset a little for each thread.
    IPoint
      nextPos = cnr.parent()->rect().bottomLeft()
                  + IPoint( 30, -30 ) * nextThreadNum;
    frame.moveSizeTo( frame.rect().scaleBy( 0.5, 0.25  )
                                  .centerAt( nextPos ) );
    frame.setDestroyOnClose( false );
    frame.show();

    nextThreadNum++;
  }
  ~ThreadData ( ) {
    delete thread;
  }
// Returns the "name" of the next thread.
static IString
  name ( ) {
    return IString( "Thread " ) + IString( nextThreadNum );
  }
// Returns the title of the next thread's frame window.
static IString
  title ( ) {
    return IString( "Process " ) 
           + 
           IApplication::current().id().asString()
           +
           IString( ", " )
           +
           name();
  }
// Data members.
IContainerControl
 *cnr;
IFrameWindow
  frame;
IStaticText
 status,
 counter,
 rate;
IContainerControl
 &container;
unsigned long
  flags;
unsigned long
  nextAction,
  count;
ITime
  startTime;
IThread
 *thread;

static unsigned
  nextThreadNum;

ThreadData ( const ThreadData& );
operator = ( const ThreadData& );
}; // ThreadData

unsigned
  ThreadData::nextThreadNum = 1;

/*----------------- Thread ContainerColumns --------------------
| These static members are attached to container controls when |
| you call addColumnsTo.                                       |
--------------------------------------------------------------*/
IContainerColumn
  Thread::iconColumn         ( IContainerColumn::isIcon ),
  Thread::nameColumn         ( IContainerColumn::isIconViewText ),
  Thread::threadIdColumn     ( offsetof( Thread, threadId ) ),
  Thread::statusColumn       ( offsetof( Thread, status ) ),
  Thread::priorityClassColumn( offsetof( Thread, priorityClass ) ),
  Thread::priorityLevelColumn( offsetof( Thread, priorityLevel ) );

/*---------------------- Thread::Thread ------------------------
| The constructor requires the container control that the      |
| thread is to be added to and a flag used to designate the    |
| primary thread.                                              |                      
--------------------------------------------------------------*/
Thread :: Thread ( IContainerControl &cnr, Boolean primary )
  : IContainerObject ( ThreadData::name(), 
                       primary ? THREAD1 : THREADS ) {
  // Create hidden data members.
  data = new ThreadData( cnr );
  // Start thread of execution (if necessary).
  if ( primary ) {
    data->flags |= isPrimary;
    data->thread = new IThread( IThread::current() );
    ITimer
      timer( new ITimerMemberFn0<Thread>( *this, Thread::timerTick ) );
  } else {
    data->thread = new IThread( (IThread::OptlinkFnPtr)run, this );
    // Secondary threads run at idle time (by default).
    data->thread->setPriority( IApplication::idleTime, 15 );
  }
  // Refresh container column data.
  this->threadId = data->thread->id().asString();
  this->refreshInfo();
  // Add container object to container and refresh it.
  cnr.addObject( this ).refresh();
}

/*--------------------- Thread::~Thread ------------------------
| The destructor resumes the thread if it's suspended (to      |
| ensure it cleans up properly).  If the thread is other       |
| than the primary thread, it is stopped.                      |
--------------------------------------------------------------*/
Thread :: ~Thread ( ) {
  // Resume any suspended threads.
  if ( data->flags & isSuspended ) {
    data->thread->resume();
  }
  // Kill secondary threads.
  if ( !( data->flags & isPrimary ) ) {
    data->thread->stop();
  }
  delete data;
}

/*------------------- Thread::refreshInfo ----------------------
| Set the container object fields to reflect the current       |
| status of this thread.                                       |                      
--------------------------------------------------------------*/
void Thread :: refreshInfo ( ) {
  if ( data->thread->isStarted() ) {
    if ( data->flags & isSuspended ) {
      this->status = "suspended";
    } else if ( data->flags & isWaiting ) {
      this->status = "waiting";
    } else {
      this->status = "running";
    }
    this->priorityClass = data->thread->priorityClass();
    this->priorityLevel = data->thread->priorityLevel();
  } else {
    this->status = "stopped";
  }
  IString
    statusLine = status;
  if ( statusLine == "waiting" ) {
    if ( data->flags & isWaitingForPrivateResource ) {
      statusLine += " for private resource...";
    } else if ( data->flags & isWaitingForSharedResource ) {
      statusLine += " for shared resource...";
    } else if ( data->flags & isWaitingForPrivateSignal ) {
      statusLine += " for private signal...";
    } else if ( data->flags & isWaitingForSharedSignal ) {
      statusLine += " for shared signal...";
    }
  }
  data->status.setText( statusLine );
}

/*------------------- Thread::addColumnsTo ---------------------
| Create this object's container columns (if necessary) and    |
| add those columns to the details view of the argument        |
| container.                                                   |
--------------------------------------------------------------*/
void Thread :: addColumnsTo ( IContainerControl &cnr ) {
  static Boolean
    doneAlready = false;

  if ( !doneAlready ) {
    iconColumn.showSeparators();
    nameColumn.showSeparators().setHeadingText( "Name" );
    threadIdColumn.showSeparators().setHeadingText( "Id" );
    statusColumn.showSeparators().setHeadingText( "Status" );
    priorityClassColumn.showSeparators().setHeadingText( "Class" );
    priorityLevelColumn.showSeparators().setHeadingText( "Level" );
    doneAlready = true;
  }

  cnr
    .addColumn( &iconColumn )
    .addColumn( &nameColumn )
    .addColumn( &threadIdColumn )
    .addColumn( &statusColumn )
    .addColumn( &priorityClassColumn )
    .addColumn( &priorityLevelColumn );
}

/*------------------ Thread::makePopUpMenu ---------------------
| Create a new pop up menu for this Thread.  We disable the    |    
| items that don't make sense.                                 |    
--------------------------------------------------------------*/
Boolean Thread :: makePopUpMenu ( IMenuEvent &event ) {
  Boolean
    result = false;

  IPopUpMenu
   *pMenu = new IPopUpMenu( THREAD_POPUP, event.window() );

  Boolean
    running    = data->thread->isStarted(),
    primary    = (Boolean)( data->flags & isPrimary ),
    suspended  = (Boolean)( data->flags & isSuspended ),
    waiting    = (Boolean)( data->flags & isWaiting ),
    blocked    = (Boolean)( suspended | waiting ),
    hasPrivate = (Boolean)( data->flags & hasPrivateResource ),
    hasShared  = (Boolean)( data->flags & hasSharedResource );

  // If suspended, change menu option to "Resume".
  if ( suspended ) {
    pMenu->setText( THREAD_SUSPEND, THREAD_RESUME );
  }

  pMenu->enableItem( THREAD_SHOW,
                     true );
  pMenu->enableItem( THREAD_SUSPEND,
                     running && !primary );
  pMenu->enableItem( THREAD_STOP,
                     running && !primary );
  pMenu->enableItem( THREAD_CRITSEC,
                     running && !blocked );
  pMenu->enableItem( THREAD_GETPRIVATE,
                     running && !primary && !blocked && !hasPrivate );
  pMenu->enableItem( THREAD_RELPRIVATE,
                     running && !blocked && hasPrivate );
  pMenu->enableItem( THREAD_GETSHARED,
                     running && !primary && !blocked && !hasShared );
  pMenu->enableItem( THREAD_RELSHARED,
                     running && !blocked && hasShared );
  pMenu->enableItem( THREAD_RESETPRIVATE,
                     running && !blocked );
  pMenu->enableItem( THREAD_SIGNALPRIVATE,
                     running && !blocked );
  pMenu->enableItem( THREAD_WAITPRIVATE,
                     running && !primary && !blocked );
  pMenu->enableItem( THREAD_RESETSHARED,
                     running && !blocked );
  pMenu->enableItem( THREAD_SIGNALSHARED,
                     running && !blocked );
  pMenu->enableItem( THREAD_WAITSHARED,
                     running && !primary && !blocked );
  pMenu->enableItem( THREAD_BOOST,
                     running );
  pMenu->enableItem( THREAD_REDUCE,
                     running );
  pMenu->enableItem( THREAD_IDLE,
                     running );
  pMenu->enableItem( THREAD_REGULAR,
                     running );
  pMenu->enableItem( THREAD_TIMECRIT,
                     running );
  pMenu->enableItem( THREAD_FORE,
                     running );

  pMenu->setAutoDeleteObject();
  pMenu->show( event.mousePosition() );
  result = true;

  return result;
}

/*------------------ Thread::handleCommand ---------------------
| Implement the specified action.  Note that we always execute |
| this function on the primary thread.  Actions that must be   |
| executed on the secondary thread are posted to that thread.  |
--------------------------------------------------------------*/
Boolean Thread :: handleCommand ( ICommandEvent &cmd ) {
  Boolean
    result = false;
  switch ( cmd.commandId() ) {
    case THREAD_SHOW:
      data->frame.setFocus();
      break;

    case THREAD_SUSPEND:
      if ( data->flags & isSuspended ) {
        data->thread->resume();
        data->flags = data->flags & ~isSuspended;
      } else {
        data->flags = (unsigned long)( data->flags | isSuspended );
        data->thread->suspend();
      }
      result = true;
      break;

    case THREAD_STOP:
      data->thread->stop();
      result = true;
      break;

    case THREAD_BOOST:
      data->thread->adjustPriority( +1 );
      result = true;
      break;

    case THREAD_REDUCE:
      data->thread->adjustPriority( -1 );
      result = true;
      break;

    case THREAD_IDLE:
      data->thread->setPriority( IApplication::idleTime, 15 );
      result = true;
      break;

    case THREAD_REGULAR:
      data->thread->setPriority( IApplication::regular, 15 );
      result = true;
      break;

    case THREAD_TIMECRIT:
      data->thread->setPriority( IApplication::timeCritical, 15 );
      result = true;
      break;

    case THREAD_FORE:
      data->thread->setPriority( IApplication::foregroundServer, 15 );
      result = true;
      break;

    // Each of these actions is "posted" by setting the thread's
    // "nextAction" data member.  This will be checked by the
    // thread the next time it polls.
    case THREAD_CRITSEC:
    case THREAD_GETPRIVATE:
    case THREAD_RELPRIVATE:
    case THREAD_GETSHARED:
    case THREAD_RELSHARED:
    case THREAD_RESETPRIVATE:
    case THREAD_SIGNALPRIVATE:
    case THREAD_WAITPRIVATE:
    case THREAD_RESETSHARED:
    case THREAD_SIGNALSHARED:
    case THREAD_WAITSHARED:
      data->nextAction = cmd.commandId();
      break;

    default:
      break;
  }
  this->refreshInfo();
  return result;
}

/*------------------ Thread::performAction ---------------------
| If the nextAction data member is non-zero, perform the       |    
| requested action.  Otherwise, just increment counter         |
| and update output fields.                                    |               
--------------------------------------------------------------*/
Boolean Thread :: performAction () {
  static IPrivateResource
    privateResource;
  static ISharedResource
    sharedResource( "MUTEX" );
  static Signal
    privateSignal,
    sharedSignal( "SIGNAL" );

  Boolean
    result = true;

  unsigned long
    action = data->nextAction;
  data->nextAction = 0;

  switch ( action ) {
    case THREAD_STOP:
      result = false;
      break;
    case THREAD_CRITSEC:
      {
      ICritSec
        criticalSection();
      IThread::current().sleep( 5000 );
      }
      break;
    case THREAD_GETPRIVATE:
      {
      data->flags |= isWaitingForPrivateResource;
      refreshInfo();
      Boolean
        gotIt = true;
      // Wait 60 seconds for the private resource.
      try { privateResource.lock( 60000 ); }
      catch ( ... ) {
        gotIt = false;
      }
      if ( gotIt ) {
        data->flags |= hasPrivateResource;
      }
      data->flags = data->flags & ~isWaitingForPrivateResource; 
      refreshInfo();
      }
      break;
    case THREAD_RELPRIVATE:
      {
      privateResource.unlock();
      data->flags = (Boolean)( data->flags & ~hasPrivateResource );
      }
      break;
    case THREAD_GETSHARED:
      {
      data->flags |= isWaitingForSharedResource;
      refreshInfo();
      Boolean
        gotIt = true;
      // Wait 60 seconds for shared resource.
      try { sharedResource.lock( 60000 ); }
      catch ( ... ) {
        gotIt = false;
      }
      if ( gotIt ) {
        data->flags |= hasSharedResource;
      }
      data->flags = (Boolean)( data->flags & ~isWaitingForSharedResource );
      refreshInfo();
      }
      break;
    case THREAD_RELSHARED:
      {
      sharedResource.unlock();
      data->flags = (Boolean)( data->flags & ~hasSharedResource );
      }
      break;
    case THREAD_RESETPRIVATE:
      {
      privateSignal.reset();
      }
      break;
    case THREAD_SIGNALPRIVATE:
      {
      privateSignal.signal();
      }
      break;
    case THREAD_WAITPRIVATE:
      {
      data->flags |= isWaitingForPrivateSignal;
      refreshInfo();
      try { privateSignal.wait( 60000 ); }
      catch ( ... ) {
      }
      data->flags = (Boolean)( data->flags & ~isWaitingForPrivateSignal );
      refreshInfo();
      }
      break;
    case THREAD_RESETSHARED:
      {
      sharedSignal.reset();
      }
      break;
    case THREAD_SIGNALSHARED:
      {
      sharedSignal.signal();
      }
      break;
    case THREAD_WAITSHARED:
      {
      data->flags |= isWaitingForSharedSignal;
      refreshInfo();
      try { sharedSignal.wait( 60000 ); }
      catch ( ... ) {
      }
      data->flags = (Boolean)( data->flags & ~isWaitingForSharedSignal );
      refreshInfo();
      }
      break;
    default:
      // Increment count and update text fields.
      {
      ITime
        now;
      double
        rate = (double) data->count / 
               (double)( ( now - data->startTime ).asSeconds() + 1 );
      IString
        whole,
        fraction;
      IString(rate) >> whole >> "." >> fraction;
      data->counter.setText( IString( ++data->count ) );
      data->rate.setText( IString( "Loops/second = " ) 
                           + whole 
                           + "."
                           + fraction.leftJustify( 5, '0' ) );
      }
      break;
  }
  return result;
}

/*-------------------- Thread::timerTick -----------------------
| This gets called on the primary thread.  We simply call      |
| performAction.                                               |
--------------------------------------------------------------*/
void Thread :: timerTick ( ) {
  performAction();
}

/*----------------------- Thread::run --------------------------
| This is the function we run on all secondary threads.  It is |
| passed a pointer to a Thread object as argument.  We simply  |
| spin calling performAction until the thread is stopped.      |
--------------------------------------------------------------*/
void Thread :: run ( void *arg ) {
  Thread
   *thread = (Thread*)arg;

  Boolean
    running = true;
  while ( running ) {
    try {
      running = thread->performAction();
    }
    catch ( ... ) {
      running = false;
    }
  }
  // Delete ThreadData?
}
