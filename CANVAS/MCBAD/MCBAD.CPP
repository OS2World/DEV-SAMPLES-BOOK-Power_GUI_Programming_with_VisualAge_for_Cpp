//*********************************************************
// Canvas - Multicell Canvas without Expandable Rows/Columns
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//*********************************************************
#include <iapp.hpp>
#include <icolor.hpp>
#include <iframe.hpp>
#include <imcelcv.hpp>
#include <ipushbut.hpp>
#include <isysmenu.hpp>
#include <icconst.h>

void main ( )
{
  // This example is almost identical to the canvas\mcsimple
  // example.  However, this version uses no expandable rows or
  // columns.  As a result, the IMultiCellCanvas grows the
  // starting column/row of the child windows that occupy more
  // than one column/row.  The child windows are not positioned
  // or sized to overlap by even amounts.  See the
  // canvas\mcsimple example to see how expandable rows and
  // columns improve the results.

  IFrameWindow
    frame( "Multicell Canvas without Expandable "
           "Rows and Columns" );
  IMultiCellCanvas
    client( IC_FRAME_CLIENT_ID, &frame, &frame );

  // Create three color squares using ICanvas objects.
  ICanvas
    red  ( 1, &client, &client ),
    green( 2, &client, &client ),
    blue ( 3, &client, &client );
  red
   .setBackgroundColor( IColor::red ) 
   .setMinimumSize( ISize( 200, 200 ) );
  green
   .setBackgroundColor( IColor::green )
   .setMinimumSize( ISize( 200, 200 ) );
  blue
   .setBackgroundColor( IColor::blue )
   .setMinimumSize( ISize( 200, 200 ) );

  // Create a push button.
  IPushButton
    ok( ISystemMenu::idClose, &client, &client );
  ok
   .enableDefault()
   .enableSystemCommand()  // For ISystemMenu::idClose.
   .setText( "OK" )
   .enableTabStop()
   .enableGroup();

  // Position child windows in the canvas.
  client
   .addToCell( &red,   2, 2, 2, 2 )
   .addToCell( &green, 3, 3, 3, 2 )
   .addToCell( &blue,  5, 2, 2, 2 )
   .addToCell( &ok,    2, 6, 5 );

  // Missing from this example are calls to setColumnWidth and
  // setRowHeight to designate expandable columns and rows.
  // The canvas causes starting columns (2 and 3) and rows
  // (2 and 3) to grow beyond their default sizes of 10.  The
  // resulting window differs significantly in appearance from
  // the canvas\mcsimple example.
  ISize
    defaultCellSize = IMultiCellCanvas::defaultCell();
  client
   .setColumnWidth( 7, defaultCellSize.width() )
   .setRowHeight( 7, defaultCellSize.height() );

  // Size and show the window now.
  frame
   .setClient( &client )
   .setFocus()
   .show();

  IApplication::current().run();
}
