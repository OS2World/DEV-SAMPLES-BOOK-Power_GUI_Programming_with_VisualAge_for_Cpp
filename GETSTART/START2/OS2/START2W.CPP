//*********************************************************
// Getting Started - Simple Program, Version 2
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//*********************************************************
#include <icconst.h>
#include "start2w.hpp"
#include "start2.h"

CodeWindow::CodeWindow ( const char* title )
  : IFrameWindow ( title,
                   ID_CODEWINDOW,
                   IFrameWindow::classDefaultStyle
                    | IFrameWindow::menuBar ),
    mle( IC_FRAME_CLIENT_ID, this, this,
         IRectangle(),
         ( IMultiLineEdit::classDefaultStyle
            | IMultiLineEdit::horizontalScroll )
           & ~IMultiLineEdit::wordWrap ),
    cmdHandler ( )
{
  // Make the MLE the client window.
  this->setClient( &mle );

  // Read this source file into the MLE, and position the
  // cursor at the top of the file.
  mle.importFromFile( __FILE__ );
  mle.setCursorLinePosition( 0 );

  // Attach the command handler that will process
  // selections from the menu bar,
  cmdHandler.handleEventsFor( this );
}

IBase::Boolean CodeWindow::cut ( )
{
  Boolean didCut = false;
  if ( mle.hasSelectedText() )
  {      // Cut selected text from the MLE to the
         // system clipboard.
     mle.cut();
     didCut = true;
  }
  return didCut;
}

IBase::Boolean CodeWindow::copy ( )
{
  Boolean didCopy = false;
  if ( mle.hasSelectedText() )
  {      // Copy selected text from the MLE to the
         // system clipboard.
     mle.copy();
     didCopy = true;
  }
  return didCopy;
}

IBase::Boolean CodeWindow::paste ( )
{
  Boolean didPaste = false;
  if ( mle.clipboardHasTextFormat() )
  {      // Paste text from the clipboard to the MLE.
     mle.paste();
     didPaste = true;
  }
  return didPaste;
}
