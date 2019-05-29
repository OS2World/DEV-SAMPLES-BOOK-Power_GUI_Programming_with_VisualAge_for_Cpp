//*********************************************************
// Canvas - ISplitCanvas with "Problem" Child Windows
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//*********************************************************
#include <iapp.hpp>
#include <icolor.hpp>
#include <iframe.hpp>
#include <igroupbx.hpp>
#include <ihandle.hpp>
#include <iiconctl.hpp>
#include <imcelcv.hpp>
#include <imle.hpp>
#include <isplitcv.hpp>
#include <istring.hpp>
#include <icconst.h>

#define FIX_PROBLEMS  1   // Comment this out to experiment.

#ifndef FIX_PROBLEMS
  #define fix1  client
  #define fix2  client
  #define fix3  client
  #define fix4  client
#endif

void main ( )
{
  IFrameWindow
    frame( "Split Canvas with \"Problem\" Children" );
  ISplitCanvas
    client( IC_FRAME_CLIENT_ID, &frame, &frame );
  client
#ifdef IC_WIN
   .setSplitBarMiddleColor( IColor::activeFrameBorder );
#else
   .setSplitBarMiddleColor(
            IGUIColor( IGUIColor::activeFrameBorder ) );
#endif

  // Create the information text above the split canvas.
  IMultiLineEdit
    mle( 1, &frame, &frame );
  mle
   .disableDataUpdate()
   .setText( "The group box, frame windows, and icon control "
             "are \"problem\" child windows." );

  // Create the first problem child of the split canvas.
#ifdef FIX_PROBLEMS
  IMultiCellCanvas
    fix1( 2, &client, &client );
#endif
  IGroupBox
    problem1( 3, &fix1, &fix1 );
  problem1
   .setText( "Group Box" );
#ifdef FIX_PROBLEMS
  problem1
   .setMinimumSize( ISize( 1, 1 ) );
  fix1
   .addToCell( &problem1, 1, 1 )
   .setRowHeight( 1, 0, true )
   .setColumnWidth( 1, 0, true );
#endif

  // Create the second problem child of the split canvas.
  // Note that a frame window without a title bar only causes
  // problems on the OS/2 operating system.
#ifdef FIX_PROBLEMS
  IMultiCellCanvas
    fix2( 4, &client, &client );
#endif
  IFrameWindow
    problem2( 5, &fix2, &fix2, IRectangle(),
              IFrameWindow::dialogBorder
               | IWindow::visible );
  IStaticText
    st1( IC_FRAME_CLIENT_ID, &problem2, &problem2 );
  st1
   .setText( "Child frame 1" )
   .setAlignment( IStaticText::centerCenter );
  problem2
   .setClient( &st1 );
#ifdef FIX_PROBLEMS
  problem2
   .setMinimumSize( ISize( 1, 1 ) );
  fix2
   .addToCell( &problem2, 1, 1 )
   .setRowHeight( 1, 0, true )
   .setColumnWidth( 1, 0, true );
#endif

  // Create the third problem child of the split canvas.
  // Note that a frame window without a title bar only causes
  // problems on the OS/2 operating system.
#ifdef FIX_PROBLEMS
  IMultiCellCanvas
    fix3( 6, &client, &client );
#endif
  IFrameWindow
    problem3( 7, &fix3, &fix3, IRectangle(),
              IFrameWindow::dialogBorder
               | IWindow::visible );
  IStaticText
    st2( IC_FRAME_CLIENT_ID, &problem3, &problem3 );
  st2
   .setText( "Child frame 2" )
   .setAlignment( IStaticText::centerCenter );
  problem3
   .setClient( &st2 );
#ifdef FIX_PROBLEMS
  problem3
   .setMinimumSize( ISize( 1, 1 ) );
  fix3
   .addToCell( &problem3, 1, 1 )
   .setRowHeight( 1, 0, true )
   .setColumnWidth( 1, 0, true );
#endif

  // Create the fourth problem child of the split canvas.
#ifdef FIX_PROBLEMS
  IMultiCellCanvas
    fix4( 8, &client, &client );
#endif
  IIconControl
    problem4( 9, &fix4, &fix4,
              ISystemPointerHandle::question );
#ifdef FIX_PROBLEMS
  problem4
   .setMinimumSize( ISize( 1, 1 ) );
  fix4
   .addToCell( &problem4, 1, 1 )
   .setRowHeight( 1, 0, true )
   .setColumnWidth( 1, 0, true )
   .setBackgroundColor( IColor::cyan );
#endif

  // Size and show the window now.
  frame
   .setClient( &client )
   .addExtension( &mle, IFrameWindow::aboveClient )
   .setFocus()
   .show();

  IApplication::current().run();
}
