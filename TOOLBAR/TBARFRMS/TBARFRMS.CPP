//************************************************************
// Tool Bars  - Tool Bar Floating Frames
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <iframe.hpp>
#include <itbar.hpp>
#include <itbarbut.hpp>
#include <imle.hpp>
#include <iapp.hpp>
#include <icconst.h>

void main()
{
IFrameWindow
  frame ("Tool Bar Floating Frames");

// Create an MLE for the client area.
IMultiLineEdit
  mle(IC_FRAME_CLIENT_ID, &frame, &frame);

// Create a Tool Bar above the client by default.
IToolBar
  aboveClient(0x01, &frame);

// Create some floating tool bars.
IToolBar
  floating1    (0x05, &frame, IToolBar::floating),
  floating2    (0x06, &frame, IToolBar::floating);

// Create some library supplied tool bar buttons.
IToolBarButton
  cutButton1      (IC_ID_CUT,        &floating1, &floating1),
  copyButton1     (IC_ID_COPY,       &floating1, &floating1),
  pasteButton1    (IC_ID_PASTE,      &floating1, &floating1),
  cutButton2      (IC_ID_CUT,        &floating2, &floating2),
  copyButton2     (IC_ID_COPY,       &floating2, &floating2),
  pasteButton2    (IC_ID_PASTE,      &floating2, &floating2),
  cutButton3      (IC_ID_CUT,        &aboveClient, &aboveClient),
  copyButton3     (IC_ID_COPY,       &aboveClient, &aboveClient), 
  pasteButton3    (IC_ID_PASTE,      &aboveClient, &aboveClient);

// Add the buttons to the respective tool bars.
floating1
  .addAsLast ( &cutButton1 )
  .addAsLast ( &copyButton1 )
  .addAsLast ( &pasteButton1 );
floating2
  .addAsLast ( &cutButton2 )
  .addAsLast ( &copyButton2 )
  .addAsLast ( &pasteButton2 );
aboveClient
  .addAsLast ( &cutButton3 )
  .addAsLast ( &copyButton3 )
  .addAsLast ( &pasteButton3 );


frame
  .setClient (&mle)
  .setFocus()
  .show();
IApplication::current().run();

}


