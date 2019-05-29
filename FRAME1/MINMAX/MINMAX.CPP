//*********************************************************
// Frame Window Basics - Minimize/Maximize Handler Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//*********************************************************
#include <iapp.hpp>
#include <iframe.hpp>
#include <icconst.h>
#include "chdhider.hpp"

void main ( )
{
  // Create a frame window from a dialog.
  IFrameWindow
    frame( IC_DEFAULT_FRAME_ID );
  frame
   .setIcon( IC_DEFAULT_FRAME_ID );

  // Create and attach the ChildHider handler.
  // This handler fixes the problem of dialogs not hiding
  // their child controls when minimized on the OS/2
  // desktop.  As a result, a dialog control can paint over
  // the dialog's minimized icon.
  // To see this problem, comment out the handleEventsFor
  // function and rebuild the program.  Then run the program
  // on the OS/2 operating system and minimize it to the
  // desktop.
  ChildHider
    hider;
  hider
   .handleEventsFor( &frame );

  // Set the input focus and show the frame window.
  frame
   .setFocus()
   .show();

  IApplication::current().run();
}

