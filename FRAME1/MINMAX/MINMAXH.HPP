#ifndef _MINMAXH_
#define _MINMAXH_
//*********************************************************
// Frame Window Basics - Minimize/Maximize Handler Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//*********************************************************
#ifndef _IHANDLER_
  #include <ihandler.hpp>
#endif

class IFrameWindow;

class MinMaxHandler : public IHandler {
public:
// Use this function to attach the handler to your frame.
virtual MinMaxHandler
 &handleEventsFor ( IFrameWindow* frame );

protected:
// Override these to handle min/max/restore of the frame.
virtual Boolean
  minimized ( IEvent& event ),
  maximized ( IEvent& event ),
  restored  ( IEvent& event );

virtual Boolean
  dispatchHandlerEvent ( IEvent& event );

private:
IHandler
 &handleEventsFor ( IWindow* );
}; // MinMaxHandler

#endif // _MINMAXH_
