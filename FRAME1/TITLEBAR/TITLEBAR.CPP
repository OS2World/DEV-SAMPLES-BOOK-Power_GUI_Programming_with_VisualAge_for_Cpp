//*********************************************************
// Frame Window Basics - Accessing the Title Bar
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//*********************************************************
#include <iframe.hpp>
#include <ithread.hpp>
#include <ititle.hpp>

void main ( )
{
  IFrameWindow
    frame( "Original Title Bar Text" );

  // Now replace the existing title bar text.
  ITitle
    title( &frame, "yourapp.ini", "Icon View", 1 );
  
  frame
   .setFocus()
   .show();

  IThread::current().processMsgs();
} 
