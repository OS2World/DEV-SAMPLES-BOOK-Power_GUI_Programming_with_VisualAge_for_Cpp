//*********************************************************
// Canvas - IMultiCellCanvas with Combination Boxes
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//*********************************************************
#include <iapp.hpp>
#include <icombobx.hpp>
#include <iframe.hpp>
#include <imcelcv.hpp>
#include <iradiobt.hpp>
#include <istring.hpp>
#include <icconst.h>

void main ( )
{
  IFrameWindow
    frame( "Multicell Canvas with Combination Boxes" );
  IMultiCellCanvas
    client( IC_FRAME_CLIENT_ID, &frame, &frame );

  // Create a combination box without a drop-down list box that
  // does not overlap any sibling windows.  Also create one with
  // a drop-down list box that overlaps some radio buttons.
  IComboBox
    simpleCombo( 1, &client, &client ),
    dropDownCombo( 2, &client, &client, IRectangle(),
                   IComboBox::classDefaultStyle
                    & ~IBaseComboBox::simpleType
                    | IBaseComboBox::dropDownType );
  simpleCombo
   .enableTabStop();
  dropDownCombo
   .setMinimumRows( 8 )
   .enableTabStop();

  // Fill the combination boxes with some items.
  simpleCombo
   .addAsFirst( "Simple-type combination box" );
  simpleCombo
   .addAsLast( "Second item" );
  simpleCombo
   .addAsLast( "Third item" );
  simpleCombo
   .setText( simpleCombo.itemText( 0 ) );
  dropDownCombo
   .addAsFirst( "Drop-down type combination box" );
  dropDownCombo
   .addAsLast( "Second item" );
  dropDownCombo
   .addAsLast( "Third item" );
  dropDownCombo
   .addAsLast( "Fourth item" );
  dropDownCombo
   .addAsLast( "Fifth item" );
  dropDownCombo
   .addAsLast( "Sixth item" );
  dropDownCombo
   .addAsLast( "Seventh item" );
  dropDownCombo
   .addAsLast( "Eighth item" );
  dropDownCombo
   .setText( dropDownCombo.itemText( 0 ) );

  // Create radio buttons below the drop-down combination box.
  IRadioButton
    left1( 3, &client, &client ),
    left2( 4, &client, &client );
  left1
   .setText( "Button 1" )
   .enableTabStop()
   .enableGroup();
  left2
   .setText( "Button 2" );

  // Create radio buttons to the right of the combination boxes.
  IRadioButton
    right1( 5,  &client, &client ),
    right2( 6,  &client, &client ),
    right3( 7,  &client, &client ),
    right4( 8,  &client, &client ),
    right5( 9,  &client, &client ),
    right6( 10, &client, &client );
  right1
   .setText( "Button A" )
   .enableTabStop()
   .enableGroup();
  right2
   .setText( "Button B" );
  right3
   .setText( "Button C" );
  right4
   .setText( "Button D" );
  right5
   .setText( "Button E" );
  right6
   .setText( "Button F" );

  // Position the child windows in the canvas.  Note that we place
  // the drop-down combination box in a single row.  We control the
  // height of its list box using its setMinimumRows function.
  client
   .addToCell( &simpleCombo,   2, 2, 1, 5 )
   .addToCell( &dropDownCombo, 2, 8 )
   .addToCell( &left1,         2, 10 )
   .addToCell( &left2,         2, 12 )
   .addToCell( &right1,        4, 2 )
   .addToCell( &right2,        4, 4 )
   .addToCell( &right3,        4, 6 )
   .addToCell( &right4,        4, 8 )
   .addToCell( &right5,        4, 10 )
   .addToCell( &right6,        4, 12 );

  // Grow the canvas vertically between the radio buttons;
  // grow the combination boxes horizontally.
  client
   .setRowHeight( 1,  10, true )
   .setRowHeight( 3,  10, true )
   .setRowHeight( 5,  10, true )
   .setRowHeight( 7,  10, true )
   .setRowHeight( 9,  10, true )
   .setRowHeight( 11, 10, true )
   .setRowHeight( 13, 10, true )
   .setColumnWidth( 2, 10, true );

  // Size and show the window now.
  frame
   .setClient( &client )
   .moveSizeToClient( IRectangle( IPoint( 100, 200 ),
                                  client.minimumSize() ) )
   .setFocus()
   .show();

  IApplication::current().run();
}
