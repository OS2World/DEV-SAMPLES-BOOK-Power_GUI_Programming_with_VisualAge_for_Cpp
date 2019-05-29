//*********************************************************
// Canvas - ISetCanvas Deck Operations
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//*********************************************************
#include <iapp.hpp>
#include <iframe.hpp>
#include <ivport.hpp>
#include <icconst.h>

#include "deckcv.hpp"
#include "setdecks.h"

void main ( )
{
  IFrameWindow
    frame( ID_DECKS_FRAME,
           IFrameWindow::classDefaultStyle
             | IFrameWindow::accelerator
             | IFrameWindow::menuBar );

  // Create the IViewPort client window.
  IViewPort
    client( IC_FRAME_CLIENT_ID, &frame, &frame );

  // Create the scrollable ISetCanvas.
  DeckCanvas
    deckCanvas( ID_DECK_CANVAS, &client, &client );
  deckCanvas
   .setChildCount( 5 )
   .setDeckCount( 2 );

  // Show the window now.
  frame
   .setClient( &client )
   .setFocus()
   .show();

  IApplication::current().run();
}

