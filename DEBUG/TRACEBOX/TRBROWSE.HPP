#ifndef _TRBROWSE_
#define _TRBROWSE_
//************************************************************
// Problem Determination  - Trace Queue Browser
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <iframe.hpp>
#include <icmdhdr.hpp>
#include <icnrctl.hpp>
#include <imenubar.hpp>
#include <ithread.hpp>
#include <ihandler.hpp>
#include "querdr.hpp"

class TraceBrowser;


// Handler to process Queue requests.
class TraceBrowserHandler : public IHandler {
public:
/*------------------------------- Constructors -------------------------------*/
  TraceBrowserHandler ( TraceBrowser& browser)
       : browserWindow(browser) {}

protected:
/*---------------------------- Event Dispatching -----------------------------*/
virtual Boolean
  dispatchHandlerEvent ( IEvent &event );

private:
  TraceBrowser
   &browserWindow;
  TraceBrowserHandler (const TraceBrowserHandler&);
  TraceBrowserHandler operator= (const TraceBrowserHandler&);
};

// Command handler for Trace Browser.
class TraceCommandHandler :  public ICommandHandler {
public:
/*------------------------------- Constructors -------------------------------*/
  TraceCommandHandler ( TraceBrowser& browser)
       : browserWindow(browser) {}

protected:
/*----------------------------- Event Processing -----------------------------*/
virtual Boolean
  command       ( ICommandEvent& event );

private:
  TraceBrowser
   &browserWindow;
  TraceCommandHandler           (const TraceCommandHandler&);
  TraceCommandHandler operator= (const TraceCommandHandler&);
};

// Main window
class TraceBrowser : public IFrameWindow {
public:

/*------------------------------- Constructors -------------------------------*/
 TraceBrowser   ( const IString& queueName  );

/*------------------------------- Components ---------------------------------*/
IContainerControl
 &container     ( )  { return cnrWin;}
QueueReader
 &queueReader   ( )  { return reader;}
IThread
 &readerThread  ( )  { return thread; }

/*------------------------------- Enable Queue -------------------------------*/
TraceBrowser
 &enableReader  ( Boolean enable=true );
Boolean
 isReaderEnabled ( ) const;

/*------------------------------- AutoScroll ---------------------------------*/
Boolean
 isAutoScroll      ( ) const { return fautoScroll; };
TraceBrowser
  &enableAutoScroll( Boolean enable=true );

/*------------------------------- Message Status -----------------------------*/
TraceBrowser
  &setWaitCursor( Boolean wait = true );

Boolean
  isMessageWaiting() const;

private:
TraceBrowserHandler
  queueHandler;
TraceCommandHandler
  commandHandler;
IContainerControl
  cnrWin;
QueueReader
  reader;
IThread
  thread;
IMenuBar
  menuBar;
Boolean
  fautoScroll,
  fwaitCursor;
TraceBrowser            (const TraceBrowser& );
TraceBrowser& operator= (const TraceBrowser& );
};
#endif  // _TRBROWSE_
