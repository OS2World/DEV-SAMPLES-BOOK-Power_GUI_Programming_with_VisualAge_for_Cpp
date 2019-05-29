//*********************************************************
// Canvas - Simple ICanvas Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//*********************************************************
#include <iapp.hpp>
#include <icanvas.hpp>
#include <icolor.hpp>
#include <icoordsy.hpp>
#include <iframe.hpp>
#include <ipushbut.hpp>
#include <isysmenu.hpp>
#include <icconst.h>

#define MARGIN         15
#define COLOR_SIZE     100
#define COLOR_OVERLAP  25
#define BUTTON_PAD     20
#define BUTTON_HEIGHT  35

void main ( )
{
  // Position windows relative to the upper left as the
  // Windows operating system does.
  ICoordinateSystem::setApplicationOrientation
    ( ICoordinateSystem::originUpperLeft );

  IFrameWindow
    frame( "Base Canvas Example" );
  ICanvas
    client( IC_FRAME_CLIENT_ID, &frame, &frame );

  // Create three color squares using ICanvas objects,
  // specifying their position and size.
  ISize
    colorSize( COLOR_SIZE, COLOR_SIZE );
  ICanvas
    red  ( 1, &client, &client,
           IRectangle( IPoint( MARGIN, MARGIN ), colorSize ) ),
    green( 2, &client, &client,
           IRectangle( IPoint( MARGIN + COLOR_SIZE - COLOR_OVERLAP,
                               MARGIN + COLOR_SIZE - COLOR_OVERLAP ),
                       colorSize ) ),
    blue ( 3, &client, &client,
           IRectangle( IPoint( MARGIN + 2 * COLOR_SIZE
                                      - 2 * COLOR_OVERLAP,
                               MARGIN ),
                       colorSize ) );
  red
   .setBackgroundColor( IColor::red );
  green
   .setBackgroundColor( IColor::green );
  blue
   .setBackgroundColor( IColor::blue );

  // Create a push button, specifying its postion and size.
  IPushButton
    ok( ISystemMenu::idClose, &client, &client,
        IRectangle( IPoint( MARGIN,
                            MARGIN + 2 * COLOR_SIZE
                                   - COLOR_OVERLAP + BUTTON_PAD ),
                    ISize( 3 * COLOR_SIZE - 2 * COLOR_OVERLAP,
                           BUTTON_HEIGHT ) ) );
  ok
   .enableDefault()
   .enableSystemCommand()  // For ISystemMenu::idClose.
   .setText( "OK" )
   .enableTabStop()
   .enableGroup();

  // Size and show the window now.
  ISize
    clientSize( client.minimumSize() + ISize( MARGIN, MARGIN ) );
  frame
   .setClient( &client )
   .moveSizeToClient( IRectangle( IPoint( 100, 100 ), clientSize ) )
   .setFocus()
   .show();

  IApplication::current().run();
}
