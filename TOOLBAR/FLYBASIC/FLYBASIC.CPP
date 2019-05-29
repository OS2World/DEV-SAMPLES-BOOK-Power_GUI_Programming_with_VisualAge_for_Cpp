/************************************************************
/ Tool Bar - Basic Fly-over Help Example  
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
#include <icoordsy.hpp>   
#include <icanvas.hpp>
#include "flybasic.h"

void main( )
{
// Defect 7664
//  ICoordinateSystem::setApplicationOrientation(
//              ICoordinateSystem::originUpperLeft );
  IFrameWindow frame("Basic Fly-over Help");
  ICanvas client (IC_FRAME_CLIENT_ID, &frame, &frame);
  frame.setClient(&client);

  // Create the fly-over text for short text and an info area
  // for the long text.
  IFlyText flyText(ID_FLYTEXT, &frame);
  IInfoArea infoArea(&frame);

  // Create the fly-over help handler and attach it to
  // frame.
  IFlyOverHelpHandler flyHandler( &flyText, &infoArea);
  flyHandler.handleEventsFor(&frame);

  // Set the string table offsets.
  flyHandler.setFlyTextStringTableOffset(FLYTEXT_OFFSET);
  flyHandler.setLongStringTableOffset( LONGTEXT_OFFSET);

  // Create buttons that have fly-over and long text.  The
  // first buttons text comes from the application resource
  // file and the second buttons text is specified here.
  IPushButton resourceButton( ID_BUTTON1, &client, &client, 
                          IRectangle(20, 100, 120, 150));
  resourceButton.setText(ID_BUTTON1);

  IPushButton textButton (ID_BUTTON2, &client, &client,
                          IRectangle(140, 100, 240, 150));
  textButton.setText( "Stop");
  flyHandler.setHelpText( textButton.handle(), 
                          "Press to Stop",
                          "Press to stop the Web Browser.");

  // Show the window and start the application.
  frame
   .setFocus()
   .show();

  IApplication::current().run();

// Note: The info area does not display until the window is resized.
}
