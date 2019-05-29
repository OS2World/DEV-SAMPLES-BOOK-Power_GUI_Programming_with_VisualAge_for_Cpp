//************************************************************
// Advanced Frame - Frame Extension Drawing Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include "myframe.hpp"

void main()
  {
  MyFrame
    frame;
  frame.setFocus();
  frame.update().show().refresh();
  IApplication::current().run();
  }
