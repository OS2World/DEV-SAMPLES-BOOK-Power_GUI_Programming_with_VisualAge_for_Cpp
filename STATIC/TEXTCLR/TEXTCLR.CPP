//************************************************************
// Static Controls - Static Text Color Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <icolor.hpp>
#include <iframe.hpp>
#include <iapp.hpp>
#include <istattxt.hpp>
#include <icconst.h>
#include <icoordsy.hpp>

void main ( )
{
  // Set the coordinate system to upper-left on all platforms.
  ICoordinateSystem::setApplicationOrientation(
       ICoordinateSystem::originUpperLeft);

  // Create the frame with a static text client.  
  IFrameWindow frame( "Static Text Color Example" );
  IStaticText client( IC_FRAME_CLIENT_ID, &frame, &frame );
  frame.setClient( &client );
  client.setFillColor( IColor::green );

  // Cyan block on the left.
  IStaticText left( 1, &frame, &frame );
  frame.addExtension( &left,
                      IFrameWindow::leftOfClient, 100 );
  left.setBackgroundColor( IColor::cyan );

  // Text on top.
  IStaticText top( 2, &frame, &frame );
  frame.addExtension( &top,
                      IFrameWindow::aboveClient, 30 );
  top.setFillColor( IColor::yellow )
     .setForegroundColor( IColor::blue )
     .setBackgroundColor( IColor::white );
  top.setText( "This is blue on white text." )
     .setAlignment( IStaticText::centerCenter );

  // Red horizontal separators.
  ISize screen( IWindow::desktopWindow()->size() ),
        separatorSize( screen.width(), 4 );
  IStaticText thinSeparator( 3, &client, &client );
  thinSeparator.setFillColor( IColor::red )
               .moveSizeTo( IRectangle( IPoint( 0, 10 ),
                                        separatorSize ));

  IStaticText medSeparator( 4, &client, &client );
  separatorSize.scaleBy( 1, 2 );  // Double the thickness.
  medSeparator.setFillColor( IColor::red )
              .moveSizeTo( IRectangle( IPoint( 0, 50 ),
                                       separatorSize ));

  IStaticText thickSeparator( 5, &client, &client );
  separatorSize.scaleBy( 1, 3 );  // Now triple the thickness.
  thickSeparator.setFillColor( IColor::red )
                .moveSizeTo( IRectangle( IPoint( 0, 110 ),
                                         separatorSize ));

  // Size and show the window now.
  frame.setFocus()
       .show();
  IApplication::current().run();
}
