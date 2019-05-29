//************************************************************
// Fonts - Using Common Font Functions
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <iapp.hpp>
#include <icheckbx.hpp>
#include <ientryfd.hpp>
#include <ifont.hpp>
#include <iframe.hpp>
#include <imcelcv.hpp>

// Specific font names vary between operating systems,
// complicating the issue of writing portable applications.
// Avoid embedding the names in the code and instead define
// them at the top of the code as we do here.
#ifdef IC_PM
#define OS_FONT_1   "Helvetica"
#define OS_FONT_2   "Courier"
#else  // Windows
#define OS_FONT_1   "Arial"
#define OS_FONT_2   "Courier New"
#endif

void main()
{
  // Create the frame, client canvas and client controls.
  IFrameWindow aFrame( "Using Common Font Functions" );
  IMultiCellCanvas aClient( IC_FRAME_CLIENT_ID,
                            &aFrame, &aFrame );
  IEntryField myEntryField( 1001, &aClient, &aClient );
  ICheckBox myCB1( 1002, &aClient, &aClient );
  ICheckBox myCB2( 1003, &aClient, &aClient );
  ICheckBox myCB3( 1004, &aClient, &aClient );
  aFrame.setClient( &aClient );

  // Add the controls to the canvas.
  aClient
   .addToCell( &myEntryField, 2, 2 )
   .addToCell( &myCB1,        2, 4 )
   .addToCell( &myCB2,        2, 5 )
   .addToCell( &myCB3,        2, 6 );

  // Set the text of the entry field.
  myEntryField.setText( "ABCDEFGabcdefg" );

  // Set the text of the checkboxes.
  myCB1.setText( "Choice 1" );
  myCB2.setText( "Choice 2" );
  myCB3.setText( "Choice 3" );

  // Create a font object, providing a typeface name
  // and point size and apply it to the frame.
  IFont font1( OS_FONT_1, 14 );
  aFrame.setFont( font1 );

  // Increase the point size; then, apply it to the entry field.
  font1.setPointSize( 24 );
  myEntryField.setFont( font1 );

  // Change the typeface name; decrease the point size,
  // and then apply it to check box 1.
  font1.setName( OS_FONT_2 ).setPointSize( 10 );
  myCB1.setFont( font1 );

  // Create a new font from check box 1.  Change the
  // font characteristics, and then apply it to check box 2.
  IFont font2( &myCB1 );
  font2.setBold().setItalic();
  myCB2.setFont( font2 );

  // Create a default font, and then apply it to check box 3.
  IFont font3;
  myCB3.setFont( font3 );

  // Show the frame and run the application.
  aFrame
    .setFocus()
    .show();
  IApplication::current().run();
}

