//************************************************************
// Advanced Frame - Frame Save Handler
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <iframe.hpp>
#include "savhndlr.hpp"

int main()
  {
  IFrameWindow
    frame( "Position Save Test" );
  SaveHandler
    handler( frame, "savhndlr.exe" );
  frame.setFocus().show();
  IApplication::current().run();
  }
