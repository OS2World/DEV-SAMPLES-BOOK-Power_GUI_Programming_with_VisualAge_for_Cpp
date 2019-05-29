#ifndef _CHILDHLP_
#define _CHILDHLP_
//*********************************************************
// Using Help - Help for Special Cases
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc.
// All Rights Reserved.
//*********************************************************
#include <ihandler.hpp>

class IFrameWindow;

#pragma pack(4)

class ChildHelpHandler : public IHandler {
public:
virtual ChildHelpHandler
 &handleEventsFor       ( IFrameWindow* child ),
 &stopHandlingEventsFor ( IFrameWindow* child );
protected:
virtual Boolean
  dispatchHandlerEvent  ( IEvent& event );
ChildHelpHandler
 &setActiveWindow       ( IEvent& event,
                          Boolean active = true );
private:
virtual IHandler
 &handleEventsFor       ( IWindow* window  ),
 &stopHandlingEventsFor ( IWindow* window  );
}; // ChildHelpHandler

#pragma pack()

#endif // _CHILDHLP_
