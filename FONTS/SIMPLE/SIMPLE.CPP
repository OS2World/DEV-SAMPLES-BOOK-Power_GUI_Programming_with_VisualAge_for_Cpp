//************************************************************
// Fonts - Simple Font Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <iapp.hpp>
#include <ifont.hpp>
#include <iframe.hpp>
#include <imle.hpp>

void main()
{
  // Create the frame and edit area and make
  // the edit area the client of the frame.
  IFrameWindow aFrame( "Simple Font Example" );
  IMultiLineEdit myMLE( IC_FRAME_CLIENT_ID,
                        &aFrame, &aFrame );
  aFrame.setClient( &myMLE );

  // Set the text of the MLE.
  myMLE.setText( "abcdefgABCDEFG" );

  // Create a font object, providing a typeface name
  // and point size and apply it to the frame.
  IFont font( "Helvetica", 14 );
  aFrame.setFont( font );

  // Show the frame and run the application.
  aFrame
    .setFocus()
    .show();
  IApplication::current().run();
}

