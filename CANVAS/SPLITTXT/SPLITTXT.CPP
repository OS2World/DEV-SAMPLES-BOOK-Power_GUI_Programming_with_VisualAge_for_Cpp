//*********************************************************
// Canvas - ISplitCanvas with Static Text Child Windows
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//*********************************************************
#include <iapp.hpp>
#include <ibmpctl.hpp>
#include <iframe.hpp>
#include <isplitcv.hpp>
#include <istattxt.hpp>
#include <icconst.h>

void main ( )
{
  IFrameWindow
    frame( "Split Canvas Example" );
  ISplitCanvas
    client( IC_FRAME_CLIENT_ID, &frame, &frame );

  // Create five child windows.
  IStaticText
    st1( 1, &client, &client ),
    st2( 2, &client, &client );
  IBitmapControl
    bmp( 3, &client, &client, ISystemBitmapHandle::folder );
  IStaticText
    st4( 4, &client, &client ),
    st5( 5, &client, &client );
  st1
   .setText( "First" )
   .setAlignment( IStaticText::centerCenter );
  st2
   .setText( "Second" )
   .setAlignment( IStaticText::centerCenter );
  st4
   .setText( "Fourth" )
   .setAlignment( IStaticText::centerCenter );
  st5
   .setText( "Fifth" )
   .setAlignment( IStaticText::centerCenter );

  // Size and show the window now.
  frame
   .setClient( &client )
   .setFocus()
   .show();

  IApplication::current().run();
}
