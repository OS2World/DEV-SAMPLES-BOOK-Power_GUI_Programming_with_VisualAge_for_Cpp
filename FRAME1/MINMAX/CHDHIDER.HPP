#ifndef _CHDHIDER_
#define _CHDHIDER_
//*********************************************************
// Frame Window Basics - Minimize/Maximize Handler Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//*********************************************************
#include "minmaxh.hpp"

class ChildHider : public MinMaxHandler {
protected:
virtual Boolean
  minimized ( IEvent& event ),
  maximized ( IEvent& event ),
  restored  ( IEvent& event );

void
  showChildren ( IWindow* parent,
                 Boolean  show = true );
}; // ChildHider

#endif // _CHDHIDER_
