//************************************************************
// Menus - Accessing the System Menu
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <iapp.hpp>
#include <iframe.hpp>
#include <imnitem.hpp>
#include <isysmenu.hpp>

#define MI_WINDOW 0x100

void main()
{
IFrameWindow
  frame ("System Menu Example");

// Wrapper the System menu.
ISystemMenu
  systemMenu(&frame);

// We want the "Window" Submenu to be first in the list
// This is accomplished by creating a menu item and
// setting its index to zero.  We then call addSubmenu
// to change from a normal menu item to a submenu.
IMenuItem windowSubmenu(MI_WINDOW);
windowSubmenu
  .setIndex(0)

// Because we are not using a resource file, we need to handle
// the special case difference of the mnemonic on Windows.
#ifdef IC_WIN
  .setText("&Window");
#else
  .setText("~Window");
#endif

systemMenu
  .addItem(windowSubmenu, ISystemMenu::idPulldown)
  .addSubmenu(MI_WINDOW);

// Move some of the system menu items under
// the submenu we just added.
unsigned long itemsToMove[] =
    {ISystemMenu::idRestore, ISystemMenu::idMove,
     ISystemMenu::idSize, ISystemMenu::idMinimize,
     ISystemMenu::idMaximize, ISystemMenu::idHide};
for (int i=0; i<sizeof(itemsToMove)/sizeof(unsigned long); i++)
{
  // 1) Save the menu item data.
  // 2) Change the items index to add it last.
  // 3) Delete the old menu item.
  // 4) Add the menu item under the "Window" submenu.
  IMenuItem systemItem = systemMenu.menuItem(itemsToMove[i]);
  systemItem.setIndex((unsigned long)-1);
  systemMenu
    .deleteItem(itemsToMove[i])
    .addItem(systemItem, MI_WINDOW);
}

// Add an icon, set the focus, show the frame
// ... and run the application.
frame
  .setIcon(ISystemPointerHandle(ISystemPointerHandle::folder))
  .setFocus()
  .show();
IApplication::current().run();
}
