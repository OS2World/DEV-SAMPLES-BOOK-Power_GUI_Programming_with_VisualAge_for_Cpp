//************************************************************
// Edit Controls - Using an Edit Handler example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <iapp.hpp>
#include <icmdhdr.hpp>
#include <iedithdr.hpp>
#include <ientryfd.hpp>
#include <iframe.hpp>
#include <imcelcv.hpp>
#include <ipushbut.hpp>
#include <istattxt.hpp>
#include <istring.hpp>
#include "logon.h"

IString password;

// Command handler to capture menu commands.
class CommandHandler : public ICommandHandler
{
public:
  CommandHandler ( IFrameWindow* frame,
                   IStaticText* status )
            : aFrame(frame),
              aStatus(status) {}
protected:
virtual Boolean
  command              ( ICommandEvent& event );
private:
IFrameWindow
 *aFrame;
IStaticText
 *aStatus;
CommandHandler ( const CommandHandler&);
CommandHandler& operator= ( const CommandHandler&);
};

// Command handler to verify and dismiss logon panel.
class LogonHandler : public ICommandHandler
{
public:
  LogonHandler( IFrameWindow* frame,
                IStaticText* status )
            : frame(frame), status(status) {}
protected:
virtual Boolean
  command              ( ICommandEvent& cmd )
  {
    // Check password and display correct message.
    if (password == "Rules")
      status->setText(SI_LOGONPASSED);
    else
      status->setText(SI_LOGONFAILED);
    frame->dismiss( cmd.commandId() );
    return true;
  }
private:
IFrameWindow
 *frame;
IStaticText
 *status;
};

// Edit handler that checks password for alphabetic characters.
class PasswordHandler : public IEditHandler
{
public:
  PasswordHandler( IEntryField* ef, IPushButton* pb )
            : entryPW(ef), OkButton(pb) {}
protected:
virtual Boolean
  edit        ( IControlEvent& evt )
  {
    // Get the password contents on each update.
    password = entryPW->text();

    // If a non-alphabetic key is entered, disable the OK
    // push button so the dialog cannot be dismissed.
    if (!(password.isAlphabetic()))
      OkButton->disable();
    else
      OkButton->enable();
    return true;
  }
private:
IEntryField
 *entryPW;
IPushButton
 *OkButton;
};

// Logon frame window to prompt for logon id and password.
class LogonView : public IFrameWindow
{
public:
  LogonView ( unsigned long windowId,
              IWindow* owner,
              IStaticText* client );
private:
IMultiCellCanvas
  clClient;
IStaticText
  clLogonIdPrompt,
  clLogonPasswordPrompt;
IEntryField
  clLogonId,
  clLogonPassword;
IPushButton
  clOkButton;
LogonHandler
  logonHandler;
PasswordHandler
  pwHandler;
LogonView ( const LogonView&);
LogonView& operator= ( const LogonView&);
};

void main()
{
// Create a frame window with a menubar.
IFrameWindow
  frame( "Edit Control Example", MAIN_MENU,
         IFrameWindow::defaultStyle() | IFrameWindow::menuBar );

// Create a client text field for displaying login status.
// Create a command handler to handle the menu commands.
IStaticText
  statusArea(ID_STATUS, &frame, &frame);
CommandHandler
  commandHandler(&frame, &statusArea);
commandHandler
  .handleEventsFor(&frame);

// Set the focus and show the application.
frame
  .setClient(&statusArea)
  .setFocus()
  .show();
IApplication::current().run();
}

// Command override for menu commands.
Boolean CommandHandler::command( ICommandEvent& event )
{
  switch(event.commandId())
  {
    case MI_LOGON:
    {
      LogonView* logonPanel = new LogonView( ID_LOGON, aFrame,
                                             aStatus );
      logonPanel->setFocus();
      logonPanel->showModally();
      return true;
    }
#ifdef IC_WIN
    case IC_ID_CLOSE:
      aFrame->close();
      return(true);
#endif
  }
return false;
}

// LogonView constructor, which creates the logon prompting panel.
LogonView :: LogonView( unsigned long windowId, IWindow* owner,
                        IStaticText* client )
    : IFrameWindow ( windowId, 0, owner, IRectangle( 50, 50, 320, 200 ),
                     IFrameWindow::defaultStyle() |
                     IFrameWindow::dialogBackground ),
      clClient( IC_FRAME_CLIENT_ID, this, this ),
      clLogonIdPrompt( ID_LOGONIDPMT, &clClient, &clClient ),
      clLogonPasswordPrompt( ID_LOGONPWPMT, &clClient, &clClient ),
      clLogonId( ID_LOGONID, &clClient, &clClient ),
      clLogonPassword( ID_LOGONPW, &clClient, &clClient, IRectangle(),
                       IEntryField::defaultStyle() | IEntryField::unreadable ),
      clOkButton( ID_OKBUTTON, &clClient, &clClient, IRectangle(),
                  IPushButton::defaultStyle() | IPushButton::defaultButton ),
      logonHandler( this, client ),
      pwHandler( &clLogonPassword, &clOkButton )
{
  // Add the controls created above into the multicell canvas.
  clClient
   .addToCell( &clLogonIdPrompt,        2, 2 )
   .addToCell( &clLogonId,              4, 2 )
   .addToCell( &clLogonPasswordPrompt,  2, 4 )
   .addToCell( &clLogonPassword,        4, 4 )
   .addToCell( &clOkButton,             2, 6 )
   .setRowHeight( 7, IMultiCellCanvas::defaultCell().height() )
   .setColumnWidth( 5, IMultiCellCanvas::defaultCell().width() );

  // Initialize the text fields from the resource file.
  clLogonIdPrompt.setText( ID_LOGONIDPMT );
  clLogonPasswordPrompt.setText( ID_LOGONPWPMT );
  clLogonId
   .setLimit( 12 )
   .setText( ID_LOGONID )
   .enableTabStop();
  clOkButton.setText( ID_OKBUTTON );
  clOkButton.disable();
  clLogonPassword
   .setLimit( 12 )
   .enableTabStop();
  this->setClient( &clClient );
  setAutoDeleteObject( true );

  // Attach the handlers for verifying input.
  logonHandler.handleEventsFor( this );
  pwHandler.handleEventsFor( &clLogonPassword );
}

