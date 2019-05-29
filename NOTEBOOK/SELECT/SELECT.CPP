//************************************************************
// Notebook Control - Delayed Page Loading
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <inotebk.hpp>
#include <ipagehdr.hpp>
#include <iframe.hpp>
#include <iapp.hpp>
#include <ihandle.hpp>
#include <ifont.hpp>
#include <ipoint.hpp>
#include <icolor.hpp>
#include "select.h"

// The page handler for capturing page select
// events (used to delay dialog creation).
class PageSelectHandler : public IPageHandler {
protected:
virtual Boolean
  select ( IPageSelectEvent &event );
};

void main ( )
{
  // Create the frame and the notebook.
  IFrameWindow frame ("Delayed Addition of Pages");
  INotebook    notebook (ID_NOTEBOOK, &frame, &frame);

  // Make the page parts the same color as the dialog.
  notebook
    .setPageBackgroundColor(
              IGUIColor(IGUIColor::dialogBgnd))
    .setMajorTabBackgroundColor(
              IGUIColor(IGUIColor::dialogBgnd));

  // Declare a page settings object.
  INotebook::PageSettings pageData(
           INotebook::PageSettings::statusTextOn |
           INotebook::PageSettings::majorTab |
           INotebook::PageSettings::autoPageSize);


  // Set up page 1 with text, a major tab, and a dialog.
  // User data is 0 because we load the dialog here.
  pageData
    .setTabText("Page 1")
    .setStatusText("Page 1")
    .setUserData(0);

  // Create the dialog for the top page
  // and add the page to the notebook.
  IFrameWindow dialog1(ID_DIALOG1, &notebook, &notebook);
  notebook.addLastPage( pageData, &dialog1);

  // Set up page 2 with text, a major tab, and a dialog.
  // We store the dialog ID in user data and use it
  // later to load the dialog.
  pageData
    .setTabText("Page 2")
    .setStatusText("Page 2 - no window yet")
    .setUserData(ID_DIALOG2);

  // Add page 2 to the notebook without a dialog.
  notebook.addLastPage( pageData);

  // Repeat the above for page 3.
  pageData
    .setTabText("Page 3")
    .setStatusText("Page 3 - no window yet")
    .setUserData(ID_DIALOG3);
  notebook.addLastPage( pageData);

  // Size the tabs to fit the text.
  IFont noteFont(&notebook);
  ISize tabSize(ISize(noteFont.minTextWidth("no_window Page_3"),
                      noteFont.maxCharHeight()) + ISize(6,6));
  notebook
    .setMajorTabSize(tabSize)
    .setMinorTabSize(tabSize);

  // Create and energize a page handler to capture "select"
  // events so we can add the missing dialogs.
  PageSelectHandler pageHandler;
  pageHandler.handleEventsFor(&frame);

  // Put the notebook in the client and show the frame.
  frame
    .setClient(&notebook)
    .show();
  dialog1.setFocus();

  // Run the application.
  IApplication::current().run();
}


Boolean PageSelectHandler::select  ( IPageSelectEvent  &event )
{
  IPageHandle selectedPage = event.pageHandle();
  INotebook* notebook = event.notebook();
  INotebook::PageSettings pageData =
                event.notebook()->pageSettings(selectedPage);
  unsigned long dialogId = pageData.userData();

  // If we have a dialog ID in user data, the frame needs to
  // be created.
  if (dialogId != 0) {
    IFrameWindow* dialog = new IFrameWindow(
                                    dialogId,
                                    notebook,
                                    notebook);

    // Size the dialog to the size of the page.
    (*dialog).sizeTo((*notebook).pageSize());

    // Put the page on the notebook, and set user data to
    // zero to indicate that we've added the page window.
    IString statusText
              = pageData.tabText() + " has been added";
    (*notebook)
       .setStatusText( selectedPage, statusText ) 
       .setWindow( selectedPage, dialog)
       .setUserData(selectedPage, 0);
  }
  else
  {    // Page window already loaded.
      (*notebook)
         .setStatusText(selectedPage, pageData.tabText());
  }
  return false;
}
