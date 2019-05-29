//*********************************************************
// Getting Started - Simple Program, Version 2
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//*********************************************************
#include <iapp.hpp>
#include "start2w.hpp"

void main ( )
{
  // Create a primary window that contains an MLE.
  CodeWindow
    primary( "Getting Started - Version 2" );

  // Set the input focus, and show the window.
  primary
   .setFocus()
   .show();

  // Start event processing.
  IApplication::current().run();
}
