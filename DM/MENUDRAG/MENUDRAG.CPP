//************************************************************
// Direct Manipulation - Menu Drag Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <iframe.hpp>
#include <imenubar.hpp>
#include <ipushbut.hpp>
#include <istattxt.hpp>
#include <icconst.h>
#include <itrace.hpp>
#include <ifont.hpp>
#include <idmhndlr.hpp>
#include <idmmenit.hpp>
#include <idmprov.hpp>
#include "cmditem.hpp"

static const int
  numButtons  = 3,
  buttonWidth = 75;

void main()
  {
  // Create the frame and its components.
  IFrameWindow
    frame( "Menu Direct Manipulation Example" );
  IMenuBar
    menuBar( IC_DEFAULT_FRAME_ID, &frame );
  IStaticText
    text( 0, &frame, &frame );
  IPushButton
   *buttons[ numButtons ];

  // Create some buttons for dropping.
  IDMItemProviderFor< CommandItem >
    provider;
  for ( unsigned i = 0; i < numButtons; i++ )
    {
    IPushButton
     *p = new IPushButton( 0, &frame, &frame );
    p -> setText( "" );
    p -> disable();
    p -> setItemProvider( &provider );
    IDMHandler::enableDropOn( p );
    frame.addExtension( p,
                        IFrameWindow::rightOfMenuBar,
                        buttonWidth );
    buttons[ i ] = p;
    }

  // Enable drag for menu items.
  IDMHandler::enableDragFrom( &menuBar );

  // Create and attach the command handler.
  CmdHandler
    cmdHandler( text );
  cmdHandler.handleEventsFor( &frame );

  // Set up the alignment and font of the text.
  text
    .setAlignment( IStaticText::centerCenter )
    .setFont( IFont( "Times Roman", 72 ) );

  // Give the frame and icon, put the text in
  // the client window, and show the frame.
  frame.setFocus();
  frame
    .setIcon( IC_DEFAULT_FRAME_ID )
    .setClient( &text )
    .showModally();

  // Clean up the buttons.
  for ( i = 0; i < numButtons; i++ )
    delete buttons[ i ];
  }
