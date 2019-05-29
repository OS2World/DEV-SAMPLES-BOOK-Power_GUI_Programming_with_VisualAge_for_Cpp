//************************************************************
// Frame Window Basics - Information Area for the System Menu
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc.
// All Rights Reserved.
//************************************************************
#include <iframe.hpp>
#include <iinfoa.hpp>
#include <istattxt.hpp>
#include <ithread.hpp>
#include <icconst.h>

void main ( )
{
  IFrameWindow
    frame( "Information Area for System Menu" );
  IStaticText
    client( IC_FRAME_CLIENT_ID, &frame, &frame );
  client
   .setAlignment( IStaticText::topLeftWrapped )
   .setText( "Select the system menu to see informational "
             "text for the system menu choices." );

  IInfoArea
    informationArea( &frame );

  frame
   .setClient( &client )
   .setFocus()
   .show();

  IThread::current().processMsgs();
}
