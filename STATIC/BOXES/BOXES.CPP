//************************************************************
// Static Controls - Group Box and Outline Box Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <icanvas.hpp>
#include <iframe.hpp>
#include <iapp.hpp>
#include <igroupbx.hpp>
#include <ioutlbox.hpp>
#include <iradiobt.hpp>
#include <istattxt.hpp>
#include <icconst.h>
#include <icoordsy.hpp>

void main ( )
{
  // Set the coordinate system to upper-left on all platforms.
  ICoordinateSystem::setApplicationOrientation(
      ICoordinateSystem::originUpperLeft);

  IFrameWindow frame( "Group Box and Outline Box Example" );
  ICanvas client( IC_FRAME_CLIENT_ID, &frame, &frame,
                  IRectangle( IPoint(), ISize( 390, 200 )));
  frame.setClient( &client );

  // Create a group box with radio buttons.
  IGroupBox group( 1, &client, &client,
                   IRectangle( IPoint( 30, 10),
                               ISize( 150, 170 )));
  group.setText( "Group box" );

  ISize buttonSize( 130, 30 );
  IRadioButton
    first ( 2, &client, &client,
            IRectangle( IPoint( 40, 40 ), buttonSize )),
    second( 3, &client, &client,
            IRectangle( IPoint( 40, 90 ), buttonSize )),
    third ( 4, &client, &client,
            IRectangle( IPoint( 40, 140 ), buttonSize ));
  first
   .setText( "First" )
   .enableTabStop()
   .enableGroup();
  second.setText( "Second" );
  third.setText( "Third" );

  // Create an outline box with text.
  IOutlineBox outline( 5, &client, &client,
                       IRectangle( IPoint( 210, 10 ),
                                   ISize( 150, 170 )));
  IStaticText text( 6, &client, &client,
                    IRectangle( IPoint( 220, 20 ),
                                ISize( 130, 150 )));
  text
   .setAlignment( IStaticText::topLeftWrapped )
   .setText( "Text in an outline box." );

  // Size and show the window now.
  frame
   .moveSizeToClient( IRectangle( IPoint( 50, 30 ),
                                  client.size() ))
   .setFocus()
   .show();
  IApplication::current().run();
}
