//************************************************************
// Tool Bars  - Tool Bar Group Example
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
  frame ("Tool Bar Group Example");

// Create an MLE for the client area.
IMultiLineEdit
  mle(IC_FRAME_CLIENT_ID, &frame, &frame);

// Create a Tool Bar above the client by default.
IToolBar
  aboveClient(0x01, &frame);

// Create some library supplied tool bar buttons.
IToolBarButton
  cutButton       (IC_ID_CUT,        &aboveClient, &aboveClient),
  copyButton      (IC_ID_COPY,       &aboveClient, &aboveClient),
  pasteButton     (IC_ID_PASTE,      &aboveClient, &aboveClient),
  openButton      (IC_ID_OPEN,       &aboveClient, &aboveClient),
  saveButton      (IC_ID_SAVE,       &aboveClient, &aboveClient),
  printButton     (IC_ID_PRINT,      &aboveClient, &aboveClient),
  locateButton    (IC_ID_LOCATE,     &aboveClient, &aboveClient),
  helpButton      (IC_ID_HELP,       &aboveClient, &aboveClient), 
  boldButton      (IC_ID_BOLD,       &aboveClient, &aboveClient),
  italicButton    (IC_ID_ITALIC,     &aboveClient, &aboveClient),
  underscoreButton(IC_ID_UNDERSCORE, &aboveClient, &aboveClient),
  settingsButton  (IC_ID_SETTINGS,   &aboveClient, &aboveClient),
  copyToButton    (IC_ID_COPYTO,     &aboveClient, &aboveClient);

// Add the buttons to the tool bar.
aboveClient
  .addAsLast ( &cutButton )
  .addAsLast ( &copyButton )
  .addAsLast ( &pasteButton )
  .addAsLast ( &openButton, true )
  .addAsLast ( &saveButton )
  .addAsLast ( &settingsButton )
  .addAsLast ( &copyToButton )
  .addAsLast ( &printButton, true )
  .addAsLast ( &locateButton )
  .addAsLast ( &helpButton )
  .addAsLast ( &italicButton, true )
  .addAsLast ( &underscoreButton )
  .addAsLast ( &boldButton );

aboveClient.setGroupPad(20);

frame
  .setClient (&mle)
  .setFocus()
  .show();
IApplication::current().run();

}


