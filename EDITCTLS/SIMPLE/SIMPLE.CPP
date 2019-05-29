//************************************************************
// Edit Controls - Simple Edit Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <iapp.hpp>
#include <ientryfd.hpp>
#include <iframe.hpp>
#include <imcelcv.hpp>
#include <imle.hpp>
#include <istring.hpp>

void main()
{
  // Create the frame, client canvas and edit controls.
  IFrameWindow aFrame( "Simple edit example" );
  IMultiCellCanvas aClient( 1000, &aFrame, &aFrame );
  IEntryField myEntryField( 1001, &aClient, &aClient );
  IMultiLineEdit myMLE( 1002, &aClient, &aClient );

  // Add the edit controls to the canvas.
  aClient
   .addToCell( &myEntryField, 2, 2 )
   .addToCell( &myMLE,        2, 4 );

  // Set the text of the entry field.
  myEntryField.setText( "Common Text Operations" );

  // Query the text of the entry field.
  IString text = myEntryField.text();

  // Find the length of the text in the entry field.
  int length = myEntryField.textLength();

  // Now apply the same functions to an MLE.
  myMLE.setText( "Common Text Operations" );
  text = myMLE.text();
  length = myMLE.textLength();

  aFrame
    .setClient( &aClient )
    .setFocus()
    .show();
  IApplication::current().run();
}

