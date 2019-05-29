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
#include <icnrctl.hpp>
#include <ithread.hpp>
#include <ihandler.hpp>
#include "querdr.hpp"

class TraceBrowser;

// Handler to process Queue requests.
class TraceBrowserHandler : public IHandler{
public:
  TraceBrowserHandler ( TraceBrowser& browser)
       : browserWindow(browser) {}
protected:
virtual Boolean
  dispatchHandlerEvent ( IEvent &event );
private:
TraceBrowser
 &browserWindow;
TraceBrowserHandler (const TraceBrowserHandler&);
TraceBrowserHandler operator= (const TraceBrowserHandler&);
};

// Main window
class TraceBrowser : public IFrameWindow {
public:

 TraceBrowser   ( const IString& queueName  );

IContainerControl
 &container     ( )   { return cnrWin;}
QueueReader
 &queueReader   ( )   { return reader;}
IThread
 &readerThread  ( )   { return thread;}

private:
TraceBrowserHandler
  queueHandler;
IContainerControl
  cnrWin;
QueueReader
  reader;
IThread
  thread;
TraceBrowser (const TraceBrowser& );
TraceBrowser& operator= (const TraceBrowser& );
};
#endif  // _TRBROWSE_
