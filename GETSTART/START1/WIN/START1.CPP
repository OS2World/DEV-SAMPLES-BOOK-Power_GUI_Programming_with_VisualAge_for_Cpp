//*********************************************************
// Getting Started - Simple Program, Version 1
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//*********************************************************
#include <iapp.hpp>
#include <iframe.hpp>
#include <imle.hpp>
#include <icconst.h>

void main ( )
{
  // Create a primary window that contains an MLE.
  IFrameWindow
    primary( "Getting Started - Version 1" );
  IMultiLineEdit
    mle( IC_FRAME_CLIENT_ID, &primary, &primary,
         IRectangle(),
         ( IMultiLineEdit::classDefaultStyle
            | IMultiLineEdit::horizontalScroll )
           & ~IMultiLineEdit::wordWrap );
  primary.setClient( &mle );

  // Read this source file into the MLE, and position the
  // cursor at the top of the file.
  mle.importFromFile( __FILE__ );
  mle.setCursorLinePosition( 0 );

  // Set the input focus, and show the window.
  primary.setFocus();
  primary.show();

  // Start event processing.
  IApplication::current().run();
}
