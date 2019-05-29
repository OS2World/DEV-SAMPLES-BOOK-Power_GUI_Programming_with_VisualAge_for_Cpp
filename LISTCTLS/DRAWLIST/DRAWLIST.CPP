/************************************************************
/ List Controls - List Box Custom Drawing
/
/ Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
/ Copyright (c) 1997 John Wiley & Sons, Inc.
/ All Rights Reserved.
************************************************************/
#include <iframe.hpp>
#include <iapp.hpp>
#include <ilistbox.hpp>
#include <istring.hpp>
#include <icolor.hpp>
#include <icconst.h>
#include "listdhdr.hpp"
#include "listitem.hpp"

void main()
{
  IFrameWindow frame("List box Custom Drawing");
  DrawHandler listHandler;

  // Attach to the list box owner so that we get the
  // setSize event during the creation of the list box.
  listHandler.handleEventsFor(&frame);

  // Create a client area list box.
  IListBox list(IC_FRAME_CLIENT_ID, &frame, &frame, IRectangle(),
                IListBox::defaultStyle() | IWindow::saveBits
                 | IListBox::drawItem);

  // Make the background of the list box white.
  list.setBackgroundColor(IColor::white);

  // Dummy up the data for each class in the
  // hierarchy.
  ListItem items[]
     =  {ListItem("IBase",                  0, true,  false),
        ListItem("IVBase",                  1, true,  false),
        ListItem("INotifier",               2, true,  false),
        ListItem("IStandardNotifier",       3, true,  true),
        ListItem("IWindow",                 3, true,  false),
        ListItem("IControl",                4, true,  false),
        ListItem("IBaseListBox",            5, true,  false),
        ListItem("ICollectionViewListBox",  6, false, false),
        ListItem("IListBox",                6, false, false),
        ListItem("IBaseSpinButton",         5, true,  false),
        ListItem("INumericSpinButton",      6, false, false),
        ListItem("ITextSpinButton",         6, false, false),
        ListItem("ICanvas",                 5, true,  true),
        ListItem("IContainerControl",       5, false, false),
        ListItem("INotebook",               5, false, false),
        ListItem("IScrollBar",              5, false, false),
        ListItem("ITextControl",            5, true, false),
        ListItem("IButton",                 6,true, false),
        ListItem("IPushButton",             7,true, false),
        ListItem("IGraphicPushButton",      8,false, false),
        ListItem("ISettingButton",          7,true, false),
        ListItem("I3StateCheckBox",         8,false, false),
        ListItem("ICheckBox",               8,false, false),
        ListItem("IRadioButton",            8,false, false),
        ListItem("IEntryField",             6,true, false),
        ListItem("IBaseComboBox",           7, true,  false),
        ListItem("ICollectionViewComboBox", 8, false, false),
        ListItem("IComboBox",               8, false, false),
        ListItem("IGroupBox",               6,false, false),
        ListItem("IMultiLineEdit",          6,false, false),
        ListItem("IStaticText",             6,true, false),
        ListItem("IBitmapControl",          7,false, true),
        ListItem("IInfoArea",               7,false, false),
        ListItem("ITitle",                  6,false, false),
        ListItem("IFrameWindow",      4,true, false),
        ListItem("IFileDialog",       5,false, false),
        ListItem("IFontDialog",       5,false, false),
        ListItem("IHelpWindow",       4,false, false),
        ListItem("IMenu",             4,true, false),
        ListItem("IMenuBar",          5,false, false),
        ListItem("IPopUpMenu",        5,false, false),
        ListItem("ISubmenu",          5,false, false),
        ListItem("ISystemMenu",       5,false, false),
        ListItem("IObjectWindow",     4,false, false)};

  // Add the items to the list box by creating an
  // IString from the item data address.
  for(int i=0; i< sizeof(items)/sizeof(ListItem); i++)
  {
    list.add(i, IString((unsigned long)&items[i]));
  }

  // Put the list box in the client and show the application.
  frame
    .setClient(&list)
    .setFocus()
    .show();

  IApplication::current().run();
}

