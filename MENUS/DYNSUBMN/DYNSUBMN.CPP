//************************************************************
// Menus - Dynamic Submenu Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <iapp.hpp>
#include <icmdhdr.hpp>
#include <iframe.hpp>
#include <imenuhdr.hpp>
#include <imle.hpp>
#include <isubmenu.hpp>
#include "dynsubmn.h"

// Menu handler to dynamically modify a drop-down menu.
class MenuHandler : public IMenuHandler
{
public:
  MenuHandler (IMultiLineEdit& editWnd)
    : editWindow(editWnd) {}
protected:
virtual Boolean
  menuShowing   ( IMenuEvent& menuEvent,
                  ISubmenu&   submenuAboutToShow );
private:
IMultiLineEdit
 &editWindow;
MenuHandler& operator=(const MenuHandler&);
};

// Command handler to capture menu commands.
class CommandHandler : public ICommandHandler
{
public:
  CommandHandler ( IMultiLineEdit& status)
            : aStatus(status) {}

protected:
virtual Boolean
  command              ( ICommandEvent& event );

private:
IMultiLineEdit
 &aStatus;
CommandHandler& operator=(const CommandHandler&);
};

void main()
{
// Create a frame window with a menubar
// loaded from a resource file.
IFrameWindow
  frame ("Dynamic Submenu Example", MAIN_MENU,
         IFrameWindow::defaultStyle() | IFrameWindow::menuBar );

// Create an edit area in the client
// and a command handler to write in it.
IMultiLineEdit
  editArea(ID_EDIT, &frame, &frame);
CommandHandler
  commandHandler(editArea);

// Add the command handler to the frame so
// that it handles the menu messages sent.
commandHandler
  .handleEventsFor(&frame);

// Add a menu handler to dynamically alter the edit submenu.
MenuHandler
  editMenuHandler(editArea);
editMenuHandler.handleEventsFor(&frame);

// Set the focus and show the application.
editArea.setFocus();
frame
  .setClient(&editArea)
  .show();
IApplication::current().run();
}

IBase::Boolean MenuHandler::menuShowing( IMenuEvent& event,
                                         ISubmenu&   submenu )
{
  // Enable and disable the appropriate "Edit flags".
  Boolean modified = false;
  if (submenu.id() == MI_EDIT)
  {
     if (!editWindow.hasSelectedText())
     {
        submenu.disableItem(MI_COPY);
        submenu.disableItem(MI_CUT);
        modified = true;
     }
     if (!editWindow.isWriteable())
     {
        submenu.disableItem(MI_CUT);
        submenu.disableItem(MI_PASTE);
        submenu.disableItem(MI_READONLY);
        modified = true;
     }
     else
     {
        submenu.disableItem(MI_READWRITE);
        modified = true;
     }

     if (!editWindow.clipboardHasTextFormat())
     {
        submenu.disableItem(MI_PASTE);
        modified = true;
     }
  }
  return modified;
}


IBase::Boolean CommandHandler::command( ICommandEvent& event )
{
  switch(event.commandId())
  {
    case MI_CUT           :
    {
      aStatus.cut();
      return true;
    }

    case MI_COPY          :
    {
      aStatus.copy();
      return true;
    }

    case MI_PASTE         :
    {
      aStatus.paste();
      return true;
    }

    case MI_READONLY   :
    {
      aStatus.disableDataUpdate();
      return true;
    }

    case MI_READWRITE   :
    {
      aStatus.enableDataUpdate();
      return true;
    }

    case MI_FILE          :
    case MI_NEW           :
    case MI_OPEN          :
    case MI_SAVE          :
    case MI_SAVEAS        :
    case MI_EDIT          :
    case MI_UNDO          :
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