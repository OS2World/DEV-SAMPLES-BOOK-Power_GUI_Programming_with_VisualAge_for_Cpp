//*********************************************************
// Frame Window Basics - Minimize/Maximize Handler Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//*********************************************************
#include <ibase.hpp>

#ifdef IC_PM
  #define INCL_WIN
  #include <os2.h>
#else
  #include <windows.h>
#endif

#include <iframe.hpp>
#include <iswp.hpp>

#include "minmaxh.hpp"

MinMaxHandler
 &MinMaxHandler::handleEventsFor ( IFrameWindow* frame )
{
  this->IHandler::handleEventsFor( frame );
  return *this;
}

IBase::Boolean
  MinMaxHandler::dispatchHandlerEvent ( IEvent& event )
{
  Boolean
    result = false;
  switch ( event.eventId() )
  {
#ifdef IC_PM
     case WM_ADJUSTFRAMEPOS:
     {
       ISWP
        *swp = (ISWP*)(char*)( event.parameter1() );
       if ( swp->flags() & SWP_MINIMIZE )
          result = this->minimized( event );
       else if ( swp->flags() & SWP_MAXIMIZE )
          result = this->maximized( event );
       else if ( swp->flags() & SWP_RESTORE )
          result = this->restored( event );
       break;
     }
#else
     case WM_WINDOWPOSCHANGING:
     {
       PWINDOWPOS
         windowPos( (PWINDOWPOS)(char*)
                      event.parameter2().asUnsignedLong() );
       if ( !( ( windowPos->flags & SWP_NOSIZE )  &&
               ( windowPos->flags & SWP_NOMOVE ) ) )
       {
          unsigned long
            style( GetWindowLong( event.dispatchingWindow()->handle(),
                                  GWL_STYLE ) );
          if ( style & WS_MINIMIZE )
             result = this->minimized( event );
          else if ( style & WS_MAXIMIZE )
             result = this->maximized( event );
          else
             result = this->restored( event );
       }
       break;
     }
#endif
     default:
       break;
  }
  return result;
}

IBase::Boolean MinMaxHandler::minimized ( IEvent& event )
{
  return false;
}

IBase::Boolean MinMaxHandler::maximized ( IEvent& event )
{
  return false;
}

IBase::Boolean MinMaxHandler::restored ( IEvent& event )
{
  return false;
}

IHandler& MinMaxHandler::handleEventsFor ( IWindow* window )
{
  return this->IHandler::handleEventsFor( window );
}

