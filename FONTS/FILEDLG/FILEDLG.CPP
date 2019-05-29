//************************************************************
// Views - Using the File Dialog
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <iapp.hpp>
#include <ifiledlg.hpp>
#include <imsgbox.hpp>
#include <istring.hpp>
#include "filedlg.hpp"
#include "filedlg.h"

void main()
{
  // Create a primary window that contains a read-only MLE.
  IFrameWindow primary( "Using the File Dialog", MAIN_WINDOW,
      IFrameWindow::defaultStyle() | IFrameWindow::menuBar );
  IMultiLineEdit
    mle( IC_FRAME_CLIENT_ID, &primary, &primary,
         IRectangle(),
         (IMultiLineEdit::classDefaultStyle
           | IMultiLineEdit::horizontalScroll
           | IMultiLineEdit::readOnly )
          & ~IMultiLineEdit::wordWrap );
  primary.setClient( &mle );

  // Create a command handler for the menu bar.
  MyCommandHandler cmdHandler( &primary, &mle );
  cmdHandler.handleEventsFor( &primary );

  // Set the input focus, and show the window.
  primary
    .setFocus()
    .show();

  // Start event processing.
  IApplication::current().run();
}


/*------------------------------------------------------------------------------
| MyCommandHandler::command                                                    |
|   Handle menu commands.                                                      |
------------------------------------------------------------------------------*/
IBase::Boolean MyCommandHandler::command( ICommandEvent& cmdEvent )
{
  switch ( cmdEvent.commandId() )
  {
    case MI_OPENDLG:      // Open dialog processing.
    {
      // Initialize a dialog settings object.
      IFileDialog::Settings settings;

      // Set the initial file name, title and position.
      settings.setFileName( __FILE__ );
      settings.setOKButtonText( "Open" );
      settings.setTitle( "Select File to View" );
      settings.setPosition( IPoint( 50, 50 ) );

      // Create a file dialog using the default styles.
      IFileDialog fileDlg( IWindow::desktopWindow(),
                           frame, settings );

      // Check if a file name was selected.
      if (fileDlg.pressedOK())
      {
        // Empty any contents of the MLE.
        mle->removeAll();

        // Retrieve the file name selected.
        IString selectedFile = fileDlg.fileName();

        // Read the contents of the file into the MLE
        // and scroll to the top of the file.
        mle->importFromFile( selectedFile );
        mle->setCursorLinePosition( 0 );
      }
      return (true);
    }

    case MI_SAVEASDLG:    // Save As dialog processing.
    {
      // Initialize a dialog settings object.
      IFileDialog::Settings settings;

      // Set the initial file name, title and position.
      settings.setFileName( "TEMPFILE" );
      settings.setTitle( "Select File Name to Save As" );
      settings.setPosition( IPoint( 50, 50 ) );

      // Make this dialog a Save As dialog.
      settings.setSaveAsDialog();

      // Create a file dialog using the default styles.
      IFileDialog fileDlg( IWindow::desktopWindow(),
                           frame, settings );

      // Check if a file name was selected.
      if (fileDlg.pressedOK())
      {
        // Retrieve the file name selected.
        IString selectedFile = fileDlg.fileName();

        // Double check with the user before overwriting file.
        IMessageBox msgBox( frame );
        IMessageBox::Response reply =
          msgBox.show( "Are you sure you want to overwrite this file?",
             IMessageBox::okCancelButton | IMessageBox::queryIcon);

        // If user concurs, then overwrite the file.
        if (reply == IMessageBox::ok)
        {
          // Write the contents of the MLE to the file.
          mle->exportToFile( selectedFile );
        }
      }
      return (true);
    }

    case MI_EXIT:
      frame->close();
      return(true);
  }

  return(false);
}
