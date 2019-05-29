//************************************************************
// Tool Bars  - Custom Button Example
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
  frame ("Tool Bar Location Example");

// Create an MLE for the client area.
IMultiLineEdit
  mle(IC_FRAME_CLIENT_ID, &frame, &frame);

// Create a Tool Bar above the client by default.
IToolBar
  aboveClient(0x01, &frame);

// Create tool bars in the other frame extension areas.
IToolBar
  leftOfClient (0x02, &frame, IToolBar::leftOfClient),
  rightOfClient(0x03, &frame, IToolBar::rightOfClient),
  belowClient  (0x04, &frame, IToolBar::belowClient),
  floating1    (0x05, &frame, IToolBar::floating),
  floating2    (0x06, &frame, IToolBar::floating);

// Create some library supplied tool bar buttons.
IToolBarButton
  cutButton1      (IC_ID_CUT,        &aboveClient, &aboveClient),
  copyButton1     (IC_ID_COPY,       &aboveClient, &aboveClient),
  pasteButton1    (IC_ID_PASTE,      &aboveClient, &aboveClient),
  cutButton2      (IC_ID_CUT,        &leftOfClient, &leftOfClient),
  copyButton2     (IC_ID_COPY,       &leftOfClient, &leftOfClient),
  pasteButton2    (IC_ID_PASTE,      &leftOfClient, &leftOfClient),
  cutButton3      (IC_ID_CUT,        &rightOfClient, &rightOfClient),
  copyButton3     (IC_ID_COPY,       &rightOfClient, &rightOfClient),
  pasteButton3    (IC_ID_PASTE,      &rightOfClient, &rightOfClient),
  cutButton4      (IC_ID_CUT,        &belowClient, &belowClient),
  copyButton4     (IC_ID_COPY,       &belowClient, &belowClient),
  pasteButton4    (IC_ID_PASTE,      &belowClient, &belowClient),
  cutButton5      (IC_ID_CUT,        &floating1, &floating1),
  copyButton5     (IC_ID_COPY,       &floating1, &floating1),
  pasteButton5    (IC_ID_PASTE,      &floating1, &floating1),
  cutButton6      (IC_ID_CUT,        &floating2, &floating2),
  copyButton6     (IC_ID_COPY,       &floating2, &floating2),
  pasteButton6    (IC_ID_PASTE,      &floating2, &floating2);

// Add the buttons to the respective tool bars.
aboveClient
  .addAsLast ( &cutButton1 )
  .addAsLast ( &copyButton1 )
  .addAsLast ( &pasteButton1 );
belowClient  
  .addAsLast ( &cutButton2 )
  .addAsLast ( &copyButton2 )
  .addAsLast ( &pasteButton2 );
leftOfClient
  .addAsLast ( &cutButton3 )
  .addAsLast ( &copyButton3 )
  .addAsLast ( &pasteButton3 );
rightOfClient
  .addAsLast ( &cutButton4 )
  .addAsLast ( &copyButton4 )
  .addAsLast ( &pasteButton4 );
floating1
  .addAsLast ( &cutButton5 )
  .addAsLast ( &copyButton5 )
  .addAsLast ( &pasteButton5 );
floating2
  .addAsLast ( &cutButton6 )
  .addAsLast ( &copyButton6 )
  .addAsLast ( &pasteButton6 );


frame
  .setClient (&mle)
  .setFocus()
  .show();
IApplication::current().run();

}


