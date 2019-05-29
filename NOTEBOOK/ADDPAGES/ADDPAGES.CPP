//************************************************************
// Notebook Control - Adding Dialog Pages
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <inotebk.hpp>
#include <iframe.hpp>
#include <iapp.hpp>
#include <ihandle.hpp>
#include <ifont.hpp>
#include <ipoint.hpp>
#include <icconst.h>
#include "addpages.h"

void main()
{
  IFrameWindow frame ("Adding Notebook Pages");
  INotebook    notebook (IC_FRAME_CLIENT_ID, &frame, &frame);

  // Dialog1 & Dialog3
  IFrameWindow
    dialog1(ID_DIALOG1, &notebook, &notebook),
    dialog3(ID_DIALOG3, &notebook, &notebook);

  // Use one of the system bitmaps for the tab.
  ISystemBitmapHandle page1Bitmap(ISystemBitmapHandle::drive);

  // Declare a page settings.
  INotebook::PageSettings pageData;

  // Add Page 1 to the notebook with a bitmap, major tab,
  // and dialog1.
  pageData = INotebook::PageSettings (
                         page1Bitmap,
                         "Page 1",
                         INotebook::PageSettings::statusTextOn |
                         INotebook::PageSettings::majorTab);
  notebook.addLastPage( pageData, &dialog1);

  // Add Page 2 to the notebook with text and major tab,
  // but no window.
  pageData = INotebook::PageSettings (
                         "no window",
                         "Page 2",
                         INotebook::PageSettings::statusTextOn |
                         INotebook::PageSettings::majorTab);
  notebook.addLastPage( pageData);

  // Add Page 3 to the notebook with text, minor tab,
  // and dialog3.
  pageData = INotebook::PageSettings (
                         "dialog3",
                         "Page 3",
                         INotebook::PageSettings::statusTextOn |
                         INotebook::PageSettings::minorTab);
  notebook.addLastPage( pageData, &dialog3);


  // Size the tabs to fit the text.
  IFont noteFont(&notebook);
  ISize tabSize(ISize(noteFont.minTextWidth("no_window Page_3"),
                noteFont.maxCharHeight()) + ISize(6,6));
  notebook
    .setMajorTabSize(tabSize)
    .setMinorTabSize(tabSize);

  // Show the application and process messages.
  frame
    .setClient(&notebook)
    .show();
  IApplication::current().run();
}

