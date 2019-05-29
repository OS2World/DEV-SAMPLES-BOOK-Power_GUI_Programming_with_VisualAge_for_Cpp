//*********************************************************
// Using Help - Help for Special Cases
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc.
// All Rights Reserved.
//*********************************************************
#include <ibase.hpp>    // For IC_WIN or IC_PM.
#ifdef IC_PM            // ChildHelpHandler is OS/2-only.

#define INCL_WINMESSAGEMGR  // For WM_HELP.
#include <os2.h>

#include <iexcept.hpp>
#include <ihelp.hpp>
#include <iframe.hpp>
#include <icconst.h>
#include "childhlp.hpp"

#if IC_MAJOR_VERSION <= 310
  #define IBaseErrorInfo IErrorInfo
#endif

IBase::Boolean
  ChildHelpHandler::dispatchHandlerEvent ( IEvent& event )
{
  unsigned long
    activeWindow = true;
  switch ( event.eventId() )
  {
     case WM_ACTIVATE:
        // The frame window is gaining or losing activation.
        activeWindow = event.parameter1().number1();
        // Fall into the WM_HELP case.
     case WM_HELP:
        // Add this In case help is initialized or this handler
        // is attached after the frame window is activated.
        this->setActiveWindow( event, activeWindow );
        break;
     default:
        break;
  }
  return false;
}

ChildHelpHandler&
  ChildHelpHandler::setActiveWindow ( IEvent& event,
                                      Boolean active )
{
  IHelpWindow
   *help = IHelpWindow::helpWindow( event.window() );
  if ( help )
  {
     IFrameWindow
      *frame = 0;
     if ( active )
     {
        frame = (IFrameWindow*)event.window();
     }                  // Use parent window instead? $HT!
     help->setActiveWindow( frame, frame );
  }
  return *this;
}

ChildHelpHandler&
  ChildHelpHandler::handleEventsFor ( IFrameWindow* child )
{                  // Overloaded version for better type safety.
  IASSERTPARM( child != 0 );
  IHandler::handleEventsFor( child );
  return *this;
}

ChildHelpHandler&
  ChildHelpHandler::stopHandlingEventsFor ( IFrameWindow* child )
{                  // Overloaded version for better type safety.
  IASSERTPARM( child != 0 );
  IHandler::stopHandlingEventsFor( child );
  return *this;
}

IHandler&
  ChildHelpHandler::handleEventsFor ( IWindow*  )
{           // Private to hide version in IHandler.
  ITHROWLIBRARYERROR( IC_MEMBER_ACCESS_ERROR,
                      IBaseErrorInfo::invalidRequest,
                      IException::recoverable );
  return *this;
}

IHandler&
  ChildHelpHandler::stopHandlingEventsFor ( IWindow* )
{
  // Private to hide version in IHandler.
  ITHROWLIBRARYERROR( IC_MEMBER_ACCESS_ERROR,
                      IBaseErrorInfo::invalidRequest,
                      IException::recoverable );
  return *this;
}

#endif
