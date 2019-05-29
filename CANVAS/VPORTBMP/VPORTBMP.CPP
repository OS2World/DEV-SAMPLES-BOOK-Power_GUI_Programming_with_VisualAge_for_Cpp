//*********************************************************
// Canvas - IViewPort that Scrolls a Bitmap
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//*********************************************************
#include <iapp.hpp>
#include <icconst.h>
#include <ibmpctl.hpp>
#include <iframe.hpp>
#include <iscroll.hpp>
#include <ivport.hpp>
#include "vportcmd.hpp"
#include "vportbmp.h"

void main ( )
{
  // Create the frame window and its client view port.
  IFrameWindow
    frame( IFrameWindow::classDefaultStyle
             | IFrameWindow::menuBar );
  IViewPort
    vport( IC_FRAME_CLIENT_ID, &frame, &frame, IRectangle(),
           IViewPort::classDefaultStyle
             & ~IViewPort::asNeededHorizontalScrollBar
             & ~IViewPort::asNeededVerticalScrollBar
             | IViewPort::alwaysHorizontalScrollBar
             | IViewPort::alwaysVerticalScrollBar
             | IViewPort::noViewWindowFill );

  // Set up the bitmap for the view port to scroll.  We make it
  // the view window by making it the child window of the view
  // port.  By not sizing the view window, the view port sizes
  // it to its minimum size.
  IBitmapControl
    bmp( 1, &vport, &vport, ID_DEFAULT_BMP );

  // Double the amount of a "line" scroll and increase by half
  // the width of the scroll bars.
  unsigned long
    scrollIncrement =
           vport.verticalScrollBar()->minScrollIncrement() * 2;
  ( *( vport.verticalScrollBar() ) )
    .setMinScrollIncrement( scrollIncrement )
    .sizeTo( ISize( IScrollBar::systemScrollBarWidth( true )
                                                * 3 / 2, 0 ) );
  ( *( vport.horizontalScrollBar() ) )
    .setMinScrollIncrement( scrollIncrement )
    .sizeTo( ISize( 0,
                    IScrollBar::systemScrollBarWidth( false )
                                                   * 3 / 2 ) );

  // Add command handlers for the menu bar choices.
  NewBitmapCmdHandler
    cmdHdr1( &bmp );
  cmdHdr1
   .handleEventsFor( &vport );
  SizeBitmapCmdHandler
    cmdHdr2( &bmp, &vport );
  cmdHdr2
   .handleEventsFor( &vport );
  ScrollViewCmdHandler
    cmdHdr3( &vport );
  cmdHdr3
   .handleEventsFor( &vport );

  // Show it all now.
  frame
   .setFocus()
   .show();

  IApplication::current().run();
}
