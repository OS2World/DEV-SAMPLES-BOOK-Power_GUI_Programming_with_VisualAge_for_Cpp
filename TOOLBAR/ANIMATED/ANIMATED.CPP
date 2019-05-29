//************************************************************
// Tool Bars  - Animated Button Example
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
#include "animated.h"

void main()
{
IFrameWindow
  frame ("Animated Button Example");

// Create a set canvas for the client window.
ISetCanvas
  client(IC_FRAME_CLIENT_ID, &frame, &frame);

// Create the circular button as a latchable button
// and the various IOC-supplied buttons as nonlatchable.
//
IAnimatedButton
  circleButton(11, &client, &client, IRectangle(),
               IAnimatedButton::classDefaultStyle |
               IAnimatedButton::latchable),
  playButton(12, &client, &client),
  scanForwardButton(13, &client, &client),
  scanBackwardButton(14, &client, &client);

// Add the circle bitmaps to the circle button by indicating
// the resource identifier of the first bitmap and the number
// of bitmaps in the set.  Set the animation rate to .1 seconds
// and indicate that the button is animate when latched.
circleButton
  .setBitmaps (ID_CIRCLE1, 4)
  .setAnimationRate (100)
  .enableAnimateWhenLatched();

// Add the IOC-provided bitmaps to their respective buttons.
playButton
  .setBitmaps (IAnimatedButton::play)
  .setAnimationRate (500)
  .startAnimation();
scanForwardButton
  .setBitmaps (IAnimatedButton::scanForward)
  .setAnimationRate (500)
  .startAnimation();
scanBackwardButton
  .setBitmaps (IAnimatedButton::scanBackward)
  .setAnimationRate (500)
  .startAnimation();


// Put the canvas in the client area and show the application.
frame
  .setClient(&client)
  .setFocus()
  .show();
IApplication::current().run();

}
