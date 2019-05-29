/************************************************************
/ Tool Bar - Tool Bar Fly-over Help Example   
/
/ Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
/ Copyright (c) 1997 John Wiley & Sons, Inc. 
/ All Rights Reserved.
************************************************************/
#include <iframe.hpp>
#include <ipushbut.hpp>
#include <iinfoa.hpp>
#include <iflytext.hpp>
#include <iflyhhdr.hpp>
#include <icanvas.hpp>
#include <itbar.hpp>
#include <itbarbut.hpp>
#include "flytbar.h"

void main( )
{

  // Create the frame, a canvas for the client, and
  // the tool bar.
  IFrameWindow frame("Tool Bar Fly-over Help");
  ICanvas client (IC_FRAME_CLIENT_ID, &frame, &frame);
  frame.setClient(&client);
  

  // Create the fly-over text for short text and an info area 
  // for the long text.
  IFlyText flyText(ID_FLYTEXT, &frame);
  IInfoArea infoArea(&frame);

  // Create the fly-over help handler for our own resources
  // and attach it to the frame.
  IFlyOverHelpHandler flyHandler( &flyText, &infoArea);
  flyHandler.handleEventsFor(&frame);

  // Set the string table offsets for our resources.
  flyHandler.setFlyTextStringTableOffset(FLYTEXT_OFFSET);
  flyHandler.setLongStringTableOffset( LONGTEXT_OFFSET);


  // Create a tool bar for edit controls.
  IToolBar editToolBar (ID_EDITTOOLBAR, &frame);

  // Create the edit buttons from IOC-supplied tool bar 
  // buttons and add them to the tool bar.
  IToolBarButton cut(IC_ID_CUT, &editToolBar, &editToolBar);
  IToolBarButton copy(IC_ID_COPY, &editToolBar, &editToolBar);
  IToolBarButton paste(IC_ID_PASTE, &editToolBar, &editToolBar);
  editToolBar
    .addAsLast(&cut)
    .addAsLast(&copy)
    .addAsLast(&paste);

  // Create a special application tool bar.
  IToolBar launchToolBar (ID_LAUNCHTOOLBAR, &editToolBar, true);

  // Create a few tool bar buttons of our own and add
  // them to the tool bar.
  IToolBarButton launchBrowser (
             ID_LAUNCHWEB, &launchToolBar, &launchToolBar);
  launchToolBar.addAsLast (&launchBrowser);

  // Show the window and start the application.
  frame
   .setFocus()
   .show();

  IApplication::current().run();
}
