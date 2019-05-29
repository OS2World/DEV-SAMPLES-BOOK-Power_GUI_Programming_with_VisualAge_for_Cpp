//*********************************************************
// Frame Window Basics - Showing a Modal Frame Window
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//*********************************************************
#include <iframe.hpp>

void main ( ) 
{
  IFrameWindow
    mainWindow( "Modal Frame Window" );

  // Give the frame window the input focus.
  mainWindow.setFocus();

  // Process events.
  mainWindow.showModally();
}
