//************************************************************
// Menus  - Defining a Menu Resource
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <iapp.hpp>
#include <iframe.hpp>
#include "menures.h"

void main()
{
// Create a frame window with a menubar from a resource.
IFrameWindow
  frame ("Menu Resource Example", MAIN_MENU,
         IFrameWindow::defaultStyle() | IFrameWindow::menuBar);

// Set the focus and show the application.
frame
  .setFocus()
  .show();
IApplication::current().run();
}

