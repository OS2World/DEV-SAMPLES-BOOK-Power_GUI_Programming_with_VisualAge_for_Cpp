//************************************************************
// Tool Bars  - Tool Bar With Decks Example
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
  frame ("Tool Bar With Decks Example");

// Create an MLE for the client area.
IMultiLineEdit
  mle(IC_FRAME_CLIENT_ID, &frame, &frame);

// Create a tool bar to the left of the client window.
IToolBar
  leftOfClient(0x01, &frame, IToolBar::leftOfClient);

// Create some library-supplied tool bar buttons.
IToolBarButton
  cutButton       (IC_ID_CUT,        &leftOfClient, &leftOfClient),
  copyButton      (IC_ID_COPY,       &leftOfClient, &leftOfClient),
  pasteButton     (IC_ID_PASTE,      &leftOfClient, &leftOfClient),
  openButton      (IC_ID_OPEN,       &leftOfClient, &leftOfClient),
  saveButton      (IC_ID_SAVE,       &leftOfClient, &leftOfClient),
  printButton     (IC_ID_PRINT,      &leftOfClient, &leftOfClient),
  locateButton    (IC_ID_LOCATE,     &leftOfClient, &leftOfClient),
  helpButton      (IC_ID_HELP,       &leftOfClient, &leftOfClient), 
  boldButton      (IC_ID_BOLD,       &leftOfClient, &leftOfClient),
  italicButton    (IC_ID_ITALIC,     &leftOfClient, &leftOfClient),
  underscoreButton(IC_ID_UNDERSCORE, &leftOfClient, &leftOfClient),
  settingsButton  (IC_ID_SETTINGS,   &leftOfClient, &leftOfClient),
  copyToButton    (IC_ID_COPYTO,     &leftOfClient, &leftOfClient);

// Add the buttons to the tool bar.
leftOfClient
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

leftOfClient.setDeckCount(2);

frame
  .setClient (&mle)
  .setFocus()
  .show();
IApplication::current().run();

}


