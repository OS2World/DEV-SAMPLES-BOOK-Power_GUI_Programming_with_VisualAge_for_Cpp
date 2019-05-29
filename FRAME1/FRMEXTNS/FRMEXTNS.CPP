//*********************************************************
// Frame Window Basics - Frame Extension Sampler
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//*********************************************************
#include <iframe.hpp>
#include <imenubar.hpp>
#include <istattxt.hpp>

void main ( )
{
  // Create a frame window and add a menu bar.
  IFrameWindow
    frame( "Title Bar" );
  IMenuBar
    menuBar( &frame );

  menuBar
#ifdef IC_PM
   .addText( 10, "~File" )
   .addText( 11, "~Edit" )
   .addText( 12, "~View" );
#else
   .addText( 10, "&File" )
   .addText( 11, "&Edit" )
   .addText( 12, "&View" );
#endif

  // Create some static text controls.
  IStaticText
    text1( 0, &frame, &frame ),
    text2( 0, &frame, &frame ),
    text3( 0, &frame, &frame ),
    text4( 0, &frame, &frame );
#ifdef IC_PM
  IStaticText
    text5( 0, &frame, &frame ),
    text6( 0, &frame, &frame ),
    text7( 0, &frame, &frame ),
    text8( 0, &frame, &frame );
#endif

  IStaticText::Alignment
    alignment = IStaticText::centerCenter;
  text1.setAlignment( alignment ).setText( "aboveClient" );
  text2.setAlignment( alignment ).setText( "belowClient" );
  text3.setAlignment( alignment ).setText( " leftOfClient " );
  text4.setAlignment( alignment ).setText( "rightOfClient" );
#ifdef IC_PM
  text5.setAlignment( alignment ).setText( "leftOfTitleBar" );
  text6.setAlignment( alignment )
       .setText( " rightOfTitleBar " );
  text7.setAlignment( alignment ).setText( " leftOfMenuBar " );
  text8.setAlignment( alignment ).setText( " rightOfMenuBar " );
#endif

  const unsigned long
    fixed = 150;
  const IFrameWindow::SeparatorType
    none = IFrameWindow::none,
    thin = IFrameWindow::thinLine,
    thick = IFrameWindow::thickLine;

  // Add the static text controls as frame extensions.
  frame
   .addExtension( &text1, IFrameWindow::aboveClient,
                  0.25, thick )
   .addExtension( &text2, IFrameWindow::belowClient,
                  thick )
   .addExtension( &text3, IFrameWindow::leftOfClient,
                  thin )
   .addExtension( &text4, IFrameWindow::rightOfClient,
                  fixed, thin )
#ifdef IC_PM
   .addExtension( &text5, IFrameWindow::leftOfTitleBar,
                  fixed, thick )
   .addExtension( &text6, IFrameWindow::rightOfTitleBar,
                  thin )
   .addExtension( &text7, IFrameWindow::leftOfMenuBar,
                  thick )
   .addExtension( &text8, IFrameWindow::rightOfMenuBar,
                  none )
#endif
   .setFocus ( );

  frame
   .showModally();
}
