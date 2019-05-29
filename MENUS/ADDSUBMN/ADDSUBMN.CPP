//************************************************************
// Menus - Loading a Resource Submenu
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <iapp.hpp>
#include <icmdhdr.hpp>
#include <iframe.hpp>
#include <imenubar.hpp>
#include <imenuhdr.hpp>
#include <ipopmenu.hpp>
#include <istattxt.hpp>
#include "addsubmn.h"

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
CommandHandler& operator=( const CommandHandler&);
};

void main()
{
IFrameWindow
  frame ("Loading a Resource Submenu Example");

// Add the Menubar from a resource file.
IMenuBar
  menuBar(MAIN_MENU, &frame);
menuBar.setBitmap(MI_BITMAP, MI_BITMAP);

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
  // Create an empty pop-up menu
  IPopUpMenu* popUp = new IPopUpMenu( event.window(), POPUP_MENU );

  // Load the Edit and Example submenus from a resource.
  (*popUp)
    .addText(MI_EDIT, MI_EDIT)
    .addSubmenu(MI_EDIT,    EDIT_MENU)
    .addText(MI_EXAMPLE, MI_EXAMPLE)
    .addSubmenu(MI_EXAMPLE, EXAMPLE_MENU)
    .setBitmap(MI_BITMAP, MI_BITMAP)
    .setAutoDeleteObject();

  // Show the pop-up menu.
  (*popUp)
    .show(event.mousePosition());
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
    {
       aStatus.setText(event.commandId());
       return true;
    }

  }
return false;
}


