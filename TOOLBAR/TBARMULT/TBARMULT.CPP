//************************************************************
// Tool Bars  - Tool Bar Container With Multiple Tool Bars 
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
  frame ("Tool Bar Container Example");

// Create an MLE for the client area.
IMultiLineEdit
  mle(IC_FRAME_CLIENT_ID, &frame, &frame);

// Create a number of tool bars to the left of the client.
IToolBar
  leftOfClient11(0x01, &frame, IToolBar::leftOfClient),
  leftOfClient12(0x01, &frame, IToolBar::leftOfClient, true),
  leftOfClient21(0x01, &frame, IToolBar::leftOfClient),
  leftOfClient22(0x01, &frame, IToolBar::leftOfClient, true);


// Create some library-supplied tool bar buttons.
IToolBarButton
  cutButton       (IC_ID_CUT,        &leftOfClient11, &leftOfClient11),
  copyButton      (IC_ID_COPY,       &leftOfClient11, &leftOfClient11),
  pasteButton     (IC_ID_PASTE,      &leftOfClient11, &leftOfClient11),
  openButton      (IC_ID_OPEN,       &leftOfClient12, &leftOfClient12),
  saveButton      (IC_ID_SAVE,       &leftOfClient12, &leftOfClient12),
  settingsButton  (IC_ID_SETTINGS,   &leftOfClient12, &leftOfClient12),
  copyToButton    (IC_ID_COPYTO,     &leftOfClient12, &leftOfClient12),
  printButton     (IC_ID_PRINT,      &leftOfClient21, &leftOfClient21),
  locateButton    (IC_ID_LOCATE,     &leftOfClient21, &leftOfClient21),
  helpButton      (IC_ID_HELP,       &leftOfClient21, &leftOfClient21), 
  boldButton      (IC_ID_BOLD,       &leftOfClient22, &leftOfClient22),
  italicButton    (IC_ID_ITALIC,     &leftOfClient22, &leftOfClient22),
  underscoreButton(IC_ID_UNDERSCORE, &leftOfClient22, &leftOfClient22);

// Add the buttons to the tool bar.
leftOfClient11
  .addAsLast ( &cutButton )
  .addAsLast ( &copyButton )
  .addAsLast ( &pasteButton );
leftOfClient12
  .addAsLast ( &openButton)
  .addAsLast ( &saveButton )
  .addAsLast ( &settingsButton )
  .addAsLast ( &copyToButton );
leftOfClient21
  .addAsLast ( &printButton) 
  .addAsLast ( &locateButton )
  .addAsLast ( &helpButton );
leftOfClient22
  .addAsLast ( &italicButton)
  .addAsLast ( &underscoreButton )
  .addAsLast ( &boldButton );

frame
  .setClient (&mle)
  .setFocus()
  .show();
IApplication::current().run();

}


