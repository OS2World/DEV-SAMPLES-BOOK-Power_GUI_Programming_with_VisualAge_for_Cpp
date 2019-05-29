//************************************************************
// Button Controls  - Push Button Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <iframe.hpp>
#include <ipushbut.hpp>
#include <igraphbt.hpp>
#include <imcelcv.hpp>
#include <isetcv.hpp>
#include <iapp.hpp>
#include <icconst.h>
#include <isysmenu.hpp>
#include "pushbut.h"


void main()
{
// Create a frame window with a multi-cell canvas
// in the client area.
IFrameWindow
  frame ("Push Button Example");
IMultiCellCanvas
  client(IC_FRAME_CLIENT_ID, &frame, &frame);

// Create a set canvas to hold the push buttons.
ISetCanvas
  buttons(ID_BUTTONS, &client, &client);

// Create the push buttons in the set canvas.
IPushButton
  ok(ID_OK, &buttons, &buttons),
  cancel(ISystemMenu::idClose, &buttons, &buttons);

IGraphicPushButton
  bitmap(ID_BITMAPBUTTON, &buttons, &buttons,
         ISystemBitmapHandle(ISystemBitmapHandle::program)),
  icon(ID_ICONBUTTON, &buttons, &buttons,
         ISystemPointerHandle(ISystemPointerHandle::folder));
IPushButton
  help(ID_HELP, &buttons, &buttons, IRectangle(),
       IPushButton::defaultStyle() | IPushButton::noPointerFocus);

// Indicate that the bitmap button should base its size on
// the size of the bitmap.
bitmap.enableSizeToGraphic();

// Set default button to "OK" and make this
// button the first of the group.
ok
  .enableDefault()
  .setText("OK")
  .enableTabStop()
  .enableGroup();

// Make the Cancel button a "Close" system command so
// the application closes when it is pressed.  Note
// that we created the button with the id
// ISystemMenu::idClose.
cancel
  .enableSystemCommand()
  .setText("Cancel");


// Make the Help button show help when pressed (in
// this application, we haven't defined any help
// to display).
help
  .enableHelp()
  .setText("Help");

// Add the controls to the multicell canvas.
client
 .addToCell(&buttons, 2, 6, 3, 1);

// Allow for some growth in the canvas.
client
 .setRowHeight   (1, 20, true);

// Put the canvas in the client and show the window.
frame
  .setClient(&client)
  .setFocus()
  .show();
IApplication::current().run();

}
