//************************************************************
// Tool Bars  - Custom Button Handler Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <iframe.hpp>
#include <igraphic.hpp>
#include <igbitmap.hpp>
#include <igrect.hpp>
#include <iglist.hpp>
#include <isetcv.hpp>
#include <iapp.hpp>
#include <icoordsy.hpp>
#include <icconst.h>
#include "graphbut.hpp"

void main()
{
// Set the coordinate system to upper left on all platforms.
ICoordinateSystem::setApplicationOrientation(
      ICoordinateSystem::originUpperLeft);


IFrameWindow
  frame ("Custom Button Handler Example");

// Create a set canvas for the client area.
ISetCanvas
  client(IC_FRAME_CLIENT_ID, &frame, &frame);

// Create the graphic button with defaults.
GraphicButton
  graphicButton(11, &client, &client);

// Enable latching.
graphicButton.enableLatching();

graphicButton.setText("This is a \n custom button!");

// Put the canvas in the client area and run the application.
frame
  .setClient(&client)
  .setFocus()
  .show();
IApplication::current().run();

}
