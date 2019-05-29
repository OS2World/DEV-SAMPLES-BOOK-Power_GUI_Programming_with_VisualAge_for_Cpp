//*********************************************************
// Frame Window Basics - Loading a Dialog Template
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//*********************************************************
#include <iapp.hpp>
#include <icmdhdr.hpp>
#include <iframe.hpp>
#include <imenubar.hpp>
#include "dialog.h"

class PrimaryCmdHandler : public ICommandHandler {
protected:
virtual Boolean
  command ( ICommandEvent& event );
}; // PrimaryCmdHandler

class DialogCmdHandler : public ICommandHandler {
protected:
virtual Boolean
  command ( ICommandEvent& event );
}; // DialogCmdHandler

class DialogFrameWindow : public IFrameWindow {
public:
  DialogFrameWindow ( unsigned long identifier,
                      IWindow*      owner );
 ~DialogFrameWindow ( );

private:
  DialogFrameWindow ( const DialogFrameWindow& );
DialogFrameWindow
 &operator=         ( const DialogFrameWindow& );
DialogCmdHandler
  cmdHandler;
}; // DialogFrameWindow

void main ( )
{
  // Create a primary frame window.
  IFrameWindow
    primary( "Primary Frame That Loads a Dialog Template" );

  // Create a menu bar and add a choice to open a dialog.
  IMenuBar 
    menuBar( &primary );
  menuBar
#ifdef IC_PM
   .addText( ID_FILE, "~File" )
#else
   .addText( ID_FILE, "&File" )
#endif
   .addSubmenu( ID_FILE )
   .addText( ID_DIALOG_CMD, "Hello...", ID_FILE );

  // Create the command handler for the primary window.
  PrimaryCmdHandler
    cmdHandler;
  cmdHandler
   .handleEventsFor( &primary );

  // Set the focus and show the frame window.
  primary
   .setFocus()
   .show();

  IApplication::current().run();
}

IBase::Boolean
  PrimaryCmdHandler::command ( ICommandEvent& event )
{
  Boolean
    stopProcessingEvent = false;
  // Check for the "Hello..." menu choice.
  if ( event.commandId() == ID_DIALOG_CMD )
  {
     DialogFrameWindow *dialog = 
       new DialogFrameWindow( ID_DIALOG,
                              event.dispatchingWindow() );
     (*dialog)
      .setAutoDeleteObject()
      .setFocus()
      .show();
     stopProcessingEvent = true;
  }
  return stopProcessingEvent;
}

IBase::Boolean
  DialogCmdHandler::command ( ICommandEvent& event )
{
  Boolean
    stopProcessingEvent = false;
  if ( event.commandId() == ID_OK )
  {
     DialogFrameWindow *dialog = 
       (DialogFrameWindow*)( event.dispatchingWindow() );
     (*dialog)
      .setResult( event.commandId() )
      .close();
     stopProcessingEvent = true;
  }
  return stopProcessingEvent;
}

DialogFrameWindow::DialogFrameWindow ( unsigned long identifer,
                                       IWindow*      owner )
 : IFrameWindow( identifer, owner ),
   cmdHandler( )
{
   cmdHandler
    .handleEventsFor( this );
}

DialogFrameWindow::~DialogFrameWindow ( )
{
   cmdHandler
    .stopHandlingEventsFor( this );
}
