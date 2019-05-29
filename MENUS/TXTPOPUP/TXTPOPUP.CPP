//************************************************************
// Menus - Static Text Pop-up Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <iframe.hpp>
#include <istattxt.hpp>
#include <iapp.hpp>
#include <ipopmenu.hpp>
#include <imenuhdr.hpp>
#include <icmdhdr.hpp>
#include "txtpopup.h"

// Menu handler to capture pop-up menu requests.
class MenuHandler : public IMenuHandler
{
protected:
virtual Boolean
  makePopUpMenu(IMenuEvent& menuEvent);
};

// Command handler to capture menu commands.
class CommandHandler : public ICommandHandler
{
public:
  CommandHandler ( IStaticText& status)
            : aStatus(status) {}

protected:
virtual Boolean
  command              ( ICommandEvent& event );

private:
IStaticText
 &aStatus;
CommandHandler ( const CommandHandler&);
CommandHandler& operator=( const CommandHandler&);
};

void main()
{
// Create a frame window with a menubar and an
// accelerator table from a resource file.
IFrameWindow
  frame ("Pop-Up Menu Example", MAIN_MENU,
         IFrameWindow::defaultStyle()
                | IFrameWindow::menuBar
                | IFrameWindow::accelerator);

// Create a Status Area in the Client
// and a command handler to write in it.
IStaticText
  statusArea(ID_STATUS, &frame, &frame);
CommandHandler
  commandHandler(statusArea);

// Add the command handler to the frame to receive the
// menu commands and to the status area to receive any
// pop-up menu commands sent.
commandHandler
  .handleEventsFor(&frame)
  .handleEventsFor(&statusArea);

// Add a PopUp menu handler to the client status area..
MenuHandler
  textPopUpHandler;
textPopUpHandler.handleEventsFor(&statusArea);

// Set the focus and show the application.
frame
  .setClient(&statusArea)
  .setFocus()
  .show();
IApplication::current().run();
}

IBase::Boolean MenuHandler::makePopUpMenu(IMenuEvent& event)
{
  IPopUpMenu* popUp = new IPopUpMenu( POPUP_MENU,
                                      event.window() );
  (*popUp)
    .show(event.mousePosition())
    .setAutoDeleteObject();
  return true;
}


IBase::Boolean CommandHandler::command( ICommandEvent& event )
{
  switch(event.commandId())
  {
    case MI_FILE          :
    case MI_NEW           :
    case MI_OPEN          :
    case MI_SAVE          :
    case MI_SAVEAS        :
    case MI_EDIT          :
    case MI_UNDO          :
    case MI_CUT           :
    case MI_COPY          :
    case MI_PASTE         :
    case MI_EXAMPLE       :
    case MI_BITMAP        :
    case MI_HELP          :
    case MI_GENERAL_HELP  :
    case MI_CASCADE1      :
    case MI_CASCADE2      :
    case MI_CASCADE3      :
    {
       aStatus.setText(event.commandId());
       return true;
    }
  }
return false;
}

