//*********************************************************
// Canvas - Simple IMultiCellCanvas Example
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
  IFrameWindow
    frame( "Multicell Canvas Example" );
  IMultiCellCanvas
    client( IC_FRAME_CLIENT_ID, &frame, &frame );

  // Create three color squares using ICanvas objects.
  // Do not let the squares get smaller than 20x20 pels.
  ICanvas
    red  ( 1, &client, &client ),
    green( 2, &client, &client ),
    blue ( 3, &client, &client );
  red
   .setBackgroundColor( IColor::red )
   .setMinimumSize( ISize( 20, 20 ) );
  green
   .setBackgroundColor( IColor::green )
   .setMinimumSize( ISize( 20, 20 ) );
  blue
   .setBackgroundColor( IColor::blue )
   .setMinimumSize( ISize( 20, 20 ) );

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

  // Use expandable rows and columns so that the squares always
  // fill the canvas.  Set the overlap amount to be 25% of the
  // child windows' width and height via the ratios we pass to
  // setColumnWidth and setRowHeight.
  ISize
    defaultCellSize = IMultiCellCanvas::defaultCell();
  client
   .setColumnWidth( 2, 3, true )
   .setColumnWidth( 3, 1, true )
   .setColumnWidth( 4, 2, true )
   .setColumnWidth( 5, 1, true )
   .setColumnWidth( 6, 3, true )
   .setColumnWidth( 7, defaultCellSize.width() )
   .setRowHeight( 2, 3, true )
   .setRowHeight( 3, 1, true )
   .setRowHeight( 4, 3, true )
   .setRowHeight( 7, defaultCellSize.height() );

  // Size and show the window now.
  frame
   .setClient( &client )
   .setFocus()
   .show();

  IApplication::current().run();
}
