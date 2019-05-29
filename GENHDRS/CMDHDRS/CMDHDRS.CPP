//*********************************************************
// Reusable Handlers - Simple Command Handler
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//*********************************************************
#include <iapp.hpp>
#include <icnrctl.hpp>
#include <iframe.hpp>
#include <icconst.h>
#include "cmdhdr1.hpp"
#include "cmdhdr2.hpp"
#include "popuphdr.hpp"

void main ( )
{
  // Create a frame window with a container client window.
  IFrameWindow
    frame( "Command Handlers" );
  IContainerControl
    client( IC_FRAME_CLIENT_ID, &frame, &frame );
  frame
   .setClient( &client );

  // Set up the container.
  client
   .setTitle( "Press mouse button 2 to display a pop-up menu." )
   .showTitle()
   .showTitleSeparator();

  // Add a container menu handler to display a pop-up menu.
  PopupMenuHandler
    popupHandler;
  popupHandler
   .handleEventsFor( &client );

  // Attach the command handlers.  These will process the
  // commands invoked when a user selects a choice from the
  // container's pop-up menu.  Note that we attach command
  // handlers to the container client window only after we
  // attach its container menu handler.  This ensures that the
  // container menu handler does not cause command handlers to
  // be bypassed.  You can attach either command handler to
  // the frame or client window.
  OneBeepCmdHandler
    oneBeepHandler;
  oneBeepHandler
   .handleEventsFor( &client );
  TwoBeepCmdHandler
    twoBeepHandler;
  twoBeepHandler
   .handleEventsFor( &frame );

  frame
   .setFocus()
   .show();
  IApplication::current().run();
}
