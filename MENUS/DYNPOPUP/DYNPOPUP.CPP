//************************************************************
// Menus  - Creating Pop-up Menus Dynamically
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
#include <imnitem.hpp>
#include <ipopmenu.hpp>
#include <isysmenu.hpp>
#include <istattxt.hpp>
#include "dynpopup.h"

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
CommandHandler& operator= ( const CommandHandler&);
};

void main()
{
IFrameWindow
  frame ("Dynamically-Created Pop-Up Menu Example");

// Add the menubar from a resource file.
IMenuBar
  menuBar(MAIN_MENU, &frame);
#ifdef IC_WIN
// For windows, bitmap is not automatically loaded into menu.
menuBar.setBitmap(MI_BITMAP, MI_BITMAP);
#endif

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

// Add a pop-up menu to the client status area.
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

IBase::Boolean MenuHandler :: makePopUpMenu(IMenuEvent& event)
{
  // Create the pop-up menu.
  IPopUpMenu * popUp;
  popUp=new IPopUpMenu(event.window(), POPUP_MENU);

  // Create menu items for "Close" and "Help".
  IMenuItem close(ISystemMenu::idClose,
                  IMenuItem::postSystemCommand);
  close.setText(ISystemMenu::idClose);
  IMenuItem help(MI_HELP, IMenuItem::postHelp);
  help.setText(MI_HELP);

  // Add the menu items to the pop-up menu.
  (*popUp)
    .addText(MI_EDIT,   MI_EDIT)
    .addSubmenu(MI_EDIT)
      .addText(MI_UNDO,  MI_UNDO, MI_EDIT)
      .addSeparator(MI_EDIT)
      .addText(MI_CUT,   MI_CUT,   MI_EDIT)
      .addText(MI_COPY,  MI_COPY,  MI_EDIT)
      .addText(MI_PASTE, MI_PASTE, MI_EDIT)
    .addText(MI_EXAMPLE, MI_EXAMPLE)
    .addSubmenu(MI_EXAMPLE)
      .addBitmap(MI_BITMAP, MI_BITMAP, MI_EXAMPLE)
      .addSeparator(MI_EXAMPLE)
      .addItem(close, MI_EXAMPLE)
      .addItem(help, MI_EXAMPLE)
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