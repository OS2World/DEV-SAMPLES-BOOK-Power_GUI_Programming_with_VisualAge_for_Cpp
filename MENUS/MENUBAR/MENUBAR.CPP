//************************************************************
// Menus - Using an IMenuBar
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <iapp.hpp>
#include <iframe.hpp>
#include <imenubar.hpp>
#include "menubar.h"

void main()
{
// Create a frame window with a menubar from a resource.
IFrameWindow
  frame( "IMenuBar Example" );

// Add the Menubar from a resource file
IMenuBar
  menuBar( MAIN_MENU, &frame );

#ifdef IC_WIN
// For windows, bitmap is not automatically loaded
// into the menu, so load it now.
menuBar.setBitmap( MI_BITMAP, MI_BITMAP );
#endif

// Change the cascade to a conditional cascade.
menuBar.setConditionalCascade( MI_CASCADE, MI_CASCADE1 );

// Set the focus and show the application.
frame
  .setFocus()
  .show();
IApplication::current().run();
}

