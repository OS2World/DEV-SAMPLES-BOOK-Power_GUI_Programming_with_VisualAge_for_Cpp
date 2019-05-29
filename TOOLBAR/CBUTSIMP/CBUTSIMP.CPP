//************************************************************
// Tool Bars  - Simple Custom Button Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <iframe.hpp>
#include <ianimbut.hpp>
#include <isetcv.hpp>
#include <iapp.hpp>
#include <icconst.h>

void main()
{
IFrameWindow
  frame ("Simple Custom Button Example");

// Create a set canvas for the client area.
ISetCanvas
  client(IC_FRAME_CLIENT_ID, &frame, &frame);

// Create the custom button as a latchable button.
ICustomButton
  customButton(11, &client, &client);

customButton.enableLatching();
customButton.setText("This is a \n latchable \n custom button!");

// Put the canvas in the client area and show the application.
frame
  .setClient(&client)
  .setFocus()
  .show();
IApplication::current().run();

}
