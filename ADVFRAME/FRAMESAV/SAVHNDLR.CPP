//************************************************************
// Advanced Frame - Frame Save Handler
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#define INCL_WIN
#include <os2.h>
#include <iframe.hpp>
#include <ihandler.hpp>
#include <istring.hpp>
#include "savhndlr.hpp"

// Construct the handler with a frame window and
// application name.
SaveHandler::SaveHandler ( IFrameWindow&  frame,
                           const IString& appName )
   : appName( appName )
  {
  IHandler::handleEventsFor( &frame );

  // Get frame window's saved position and reset it.
  WinRestoreWindowPos( appName,
                      "POSITION",
                      frame.handle() );
  }

// Override this function to implement your frame's save logic.
Boolean SaveHandler::saved( IEvent& event )
  {
  // Save frame's position.
  WinStoreWindowPos( appName,
                     "POSITION",
                     event.handle() );
  return false;
  }

// Overridden to look for WM_SAVEAPPLICATION.
Boolean SaveHandler::dispatchHandlerEvent( IEvent& event )
  {
  if ( event.eventId() == WM_SAVEAPPLICATION )
    return saved( event );
  else
    return false;
  }

// Overridden to avoid attachment to nonframe windows.
IHandler& SaveHandler::handleEventsFor( IWindow* p )
  {
  return IHandler::handleEventsFor( p );
  }
