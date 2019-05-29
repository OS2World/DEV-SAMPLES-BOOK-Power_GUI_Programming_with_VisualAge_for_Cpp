//*********************************************************
// Canvas - Nested Canvas Tabbing Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//*********************************************************
#include <iapp.hpp>
#include <icolor.hpp>
#include <icoordsy.hpp>
#include <ientryfd.hpp>
#include <iframe.hpp>
#include <imcelcv.hpp>
#include <ipushbut.hpp>
#include <isysmenu.hpp>
#include <icconst.h>

void main ( )
{
  // Position windows relative to the bottom-left, like the
  // OS/2 operating system does.
  ICoordinateSystem::setApplicationOrientation
    ( ICoordinateSystem::originLowerLeft );

  IFrameWindow
    frame( "Canvas Tabbing" );
  IMultiCellCanvas
    client( IC_FRAME_CLIENT_ID, &frame, &frame );

  // Create child windows of the client canvas.
  IEntryField
    ef1( 1, &client, &client );
  ef1
   .setLimit( 24 )
   .setText( "Has tab stop" )
   .enableTabStop()
   .enableGroup();

  IMultiCellCanvas
    childCanvas( 0, &client, &client );
  childCanvas
   .setBackgroundColor( IColor::cyan );

  // Create child windows of the child canvas.
  IEntryField
    ef2( 2, &childCanvas, &childCanvas ),
    ef3( 3, &childCanvas, &childCanvas );
  ef2
   .setLimit( 24 )
   .setText( "Has tab stop" )
   .enableTabStop()
   .enableGroup();
  ef3
   .setLimit( 24 )
   .setText( "Has tab stop" )
   .enableTabStop()
   .enableGroup();

  // Position the child windows of the child canvas.
  ISize
    cell( IMultiCellCanvas::defaultCell() );
  unsigned long
    defaultHeight = cell.height(),
    defaultWidth = cell.width();
  childCanvas
   .addToCell( &ef2, 2, 2 )
   .addToCell( &ef3, 2, 4 )
   .setRowHeight( 3, defaultHeight * 2 )
   .setRowHeight( 5, defaultHeight )
   .setColumnWidth( 1, defaultWidth * 2 )
   .setColumnWidth( 2, defaultWidth, true )
   .setColumnWidth( 3, defaultWidth * 2 );

  // Create another child window of the client canvas.
  IEntryField
    ef4( 4, &client, &client );
  ef4
   .setLimit( 24 )
   .setText( "Has tab stop" )
   .enableTabStop()
   .enableGroup();

  // Create a push button.
  IPushButton
    ok( ISystemMenu::idClose, &client, &client );
  ok
   .enableSystemCommand()  // For ISystemMenu::idClose.
   .enableDefault()
   .setText( "OK" )
   .enableTabStop()
   .enableGroup();

  // Position the child windows of the client canvas.
  client
   .addToCell( &ef1,         3, 2, 2 )
   .addToCell( &childCanvas, 2, 4, 4 )
   .addToCell( &ef4,         3, 6, 2 )
   .addToCell( &ok,          3, 8 )
   .setRowHeight( 1, defaultHeight * 3 / 2 )
   .setRowHeight( 3, defaultHeight )
   .setRowHeight( 5, defaultHeight )
   .setRowHeight( 7, defaultHeight * 2 )
   .setRowHeight( 9, defaultHeight * 3 / 2 )
   .setColumnWidth( 2, defaultWidth * 2 )
   .setColumnWidth( 3, 2 )
   .setColumnWidth( 4, 5, true )
   .setColumnWidth( 5, defaultWidth * 2 )
   .setColumnWidth( 6, defaultWidth );

  // Size and show the window now.
  frame
   .setClient( &client )
   .moveSizeToClient( IRectangle( IPoint( 100, 100 ),
                                  client.minimumSize() ) )
   .setFocus()
   .show();

  IApplication::current().run();
}
