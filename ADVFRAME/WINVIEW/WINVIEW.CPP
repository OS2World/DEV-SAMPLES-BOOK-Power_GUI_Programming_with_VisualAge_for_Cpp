//************************************************************
// Advanced Frame - Window Viewer Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <iwindow.hpp>

#include "treeview.hpp"
#include "hwindow.hpp"

int main (  )
{
  HWindow hwindow ( IWindow::desktopWindow()->handle() );
  TreeView
    view( hwindow );
  view.open();
  IApplication::current().run();
  return 0;
}
