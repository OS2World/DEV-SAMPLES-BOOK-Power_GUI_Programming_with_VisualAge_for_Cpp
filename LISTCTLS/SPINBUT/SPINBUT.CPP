/************************************************************
/ List Controls - Spin Button Date Control
/
/ Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
/ Copyright (c) 1997 John Wiley & Sons, Inc. 
/ All Rights Reserved.
************************************************************/
#include <iapp.hpp>
#include <iframe.hpp>
#include <icconst.h>
#include "datectrl.hpp"

void main()
{
IFrameWindow frame("Date Spin Button Example");
DateControl  date(IC_FRAME_CLIENT_ID, &frame, &frame);

// Put the control in the client area, give the frame
// the input focus, and show the frame.
frame
  .setClient(&date)
  .setFocus()
  .show();

IApplication::current().run();
}
