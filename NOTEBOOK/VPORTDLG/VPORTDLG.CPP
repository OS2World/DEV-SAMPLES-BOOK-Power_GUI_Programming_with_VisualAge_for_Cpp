//************************************************************
// Notebook Control - Adding Notebook Windows to a Viewport
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
#include <ivport.hpp>
#include <icolor.hpp>
#include <icconst.h>
#include "deferacc.hpp"
#include "vportdlg.h"

void main()
{
  // Create the frame, notebook, and view port.
  IFrameWindow frame ("ViewPort Notebook");
  INotebook    notebook (IC_FRAME_CLIENT_ID, &frame, &frame);
  IViewPort    viewport (0x102, &notebook, &notebook);

  // Set the window and the page to the
  // color of a dialog background.
  viewport.setBackgroundColor(
              IGUIColor(IGUIColor::dialogBgnd));
  notebook
    .setPageBackgroundColor(
              IGUIColor(IGUIColor::dialogBgnd))
    .setMajorTabBackgroundColor(
              IGUIColor(IGUIColor::dialogBgnd));

  // Create a dialog on the view port
  IFrameWindow dialog1(ID_DIALOG1, &viewport, &viewport);
  DeferAccelerators accelHdr;
  accelHdr.handleEventsFor(&dialog1);

  // Declare a page settings with text, major tab, and
  // a dialog.
  INotebook::PageSettings pageData =
                 INotebook::PageSettings (
                         "dialog1",
                         "Page 1",
                         INotebook::PageSettings::autoPageSize |
                         INotebook::PageSettings::statusTextOn |
                         INotebook::PageSettings::majorTab);
  notebook.addLastPage( pageData, &viewport);

  // Make sure the tabs are big enough.
  IFont noteFont(&notebook);
  ISize tabSize(ISize(noteFont.minTextWidth("Page_1"),
                noteFont.maxCharHeight()) + ISize(6,6));
  notebook.setMajorTabSize(tabSize);

  // Set the client and show the window.
  frame
    .setClient(&notebook)
    .show();
  IApplication::current().run();
}

