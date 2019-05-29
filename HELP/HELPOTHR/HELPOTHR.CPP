//*********************************************************
// Using Help - Help for Special Cases
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc.
// All Rights Reserved.
//*********************************************************
#include <ibase.hpp>         // For IC_PM or IC_WIN.
#ifdef IC_PM
  #define INCL_WINWINDOWMGR  // For WinQueryActiveWindow.
  #include <os2.h>
#endif

#include <iapp.hpp>
#include <icnrctl.hpp>
#include <icnrhdr.hpp>
#include <idmcnrit.hpp>
#include <idmsrch.hpp>
#include <idmevent.hpp>
#include <ifiledlg.hpp>
#include <iframe.hpp>
#include <ihelp.hpp>
#include <ipushbut.hpp>
#include <isetcv.hpp>
#include <icconst.h>

#include "helpothr.hpp"
#include "childhlp.hpp"
#include "helpothr.h"

#ifdef IC_PM
  #ifdef IPF_COMPATIBLE
    #undef IPF_COMPATIBLE
  #endif
#endif

#ifdef IC_PM
  static ChildHelpHandler childHelpHdr;
#endif

void main ( )
{
  // Create a primary window with a container.
  IFrameWindow
    primary( "Help Example for Special Cases", ID_PRIMARY );
  IContainerControl
    client( ID_CLIENT, &primary, &primary );
  client
   .setTitle( "This example shows help for a container, notebook, "
              "file dialog, and drag and drop." )
   .showTitle()
   .showTitleSeparator()
   .showIconView()
   .arrangeIconView()
   .setDeleteObjectsOnClose()
   .enableTabStop();
  primary.setClient( &client );

  // Get default processing for an "open" and "help" event.
  ICnrHandler
    cnrHandler;
  cnrHandler
   .handleEventsFor( &client );

  // Support drag and drop of container objects.
  IDMHandler::enableDragDropFor( &client );
  CnrDragHelpProvider
    provider;
  client
   .setItemProvider( &provider );

  ISystemPointerHandle
    icon( ISystemPointerHandle::information );
  CnrObject
   *cnrObject = new CnrObject();
  (*cnrObject)
   .setIcon( icon )
   .setIconText( "Object 1" );
  client
   .addObject( cnrObject );

  // Add a push button for displaying a file dialog and the command
  // handler that processes the push button.
  ISetCanvas
    buttons( 1, &primary, &primary );
  IPushButton
    showFileDialog( ID_SHOWFILEDLG, &buttons, &buttons );
  showFileDialog
   .enableDefault()
   .setText( "Show file dialog" )
   .enableTabStop()
   .enableGroup();
  primary
   .addExtension( &buttons, IFrameWindow::belowClient );
  ShowFileDialogCmdHdr
    cmdHdr;
  cmdHdr
   .handleEventsFor( &primary );

  // Create the help window and associate it with the primary window.
  IHelpWindow::Settings
    settings;
  settings
   .setTitle( "Help Example for Special Cases - Help" )
   .setLibraries( "HELPOTHR.HLP" )
   .setHelpTable( ID_HELPTABLE );
#ifdef IPF_COMPATIBLE
  IHelpWindow
    help( settings, &primary,
          IHelpWindow::classDefaultStyle
           | IHelpWindow::ipfCompatible );
#else
  IHelpWindow
    help( settings, &primary );
#endif

  primary
   .setFocus()
   .show();

  IApplication::current().run();
}

void CnrObject::handleOpen ( IContainerControl* container )
{
  ObjectView* frame =
     new ObjectView( ID_SECONDARY, 0, container->parent() );
  frame->setAutoDeleteObject();
  IHelpWindow
   *help = IHelpWindow::helpWindow( frame );
  help->setAssociatedWindow( frame );
  (*frame)
   .setFocus()
   .show();
}

unsigned long CnrObject::helpId ( ) const
{
  // Return the help panel identifier for a container object.
  return PANEL_CONTAINER;
}

IContainerObject* CnrObject::objectCopy ( )
{
  // Copy the object to support copying via drag and drop.
  CnrObject* copy = new CnrObject( *this );
  return (IContainerObject *)copy;
}

IBase::Boolean
  CnrDragHelpProvider::provideHelpFor ( IDMTargetHelpEvent& event )
{
  IHelpWindow
   *help = IHelpWindow::helpWindow( event.dispatchingWindow() );
  help->show( IResourceId( PANEL_DROP ));
  return true;
}

IBase::Boolean NotebookTabHelpHdr::help ( IPageHelpEvent& event )
{
  // Display help for a notebook tab.  Get a previously stored help
  // panel identifier from the user data of the page window.
  Boolean
    stopProcessingEvent = false;
  IPageHandle
    page = event.pageHandle();
  INotebook::PageSettings
    settings = event.notebook()->pageSettings( page );
  unsigned long
    panel = settings.userData();
  if ( panel )
  {
     event.helpWindow()->show( IResourceId( panel ) );
     stopProcessingEvent = true;
  }
  return stopProcessingEvent;
}

#ifdef IC_PM
// This function is called only when running in the OS/2
// operating system.  For Windows, we instead use the
// IWindow::setHelpId function for dynamically controlling the
// general help panel of a canvas page window at runtime.
IBase::Boolean
  DynamicPageHelpHdr::handleError ( IHelpErrorEvent& event )
{
  Boolean
    stopProcessingEvent = false;
  if ( event.error() == IHelpErrorEvent::invalidHelpWindow )
  {
     // The help system cannot find the help panel to display,
     // which in this case is PANEL_NONE, the general help
     // panel for the notebook's frame window.  Hooking this
     // error case allows us to dynamically display the
     // general help panel based on the top page window.
     unsigned long
       helpPanel = 0;
     IFrameWindow
      *frame = (IFrameWindow*)event.dispatchingWindow();
     INotebook
      *notebook = (INotebook*)frame->client();

     if ( WinQueryActiveWindow( IWindow::desktopWindow()->handle() )
                                                    != frame->handle() )
     {
        // Help for a notebook tab that has already been handled
        // via IPageHandler::help by displaying a help panel
        // (the help window is the active window now).  We need
        // this check to avoid showing two help panels for a tab.
     }
     else
     {
        // Help for a non-frame window notebook page window.
        IPageHandle
          page = notebook->topPage();
        IWindow
         *pageWindow = notebook->window( page );
        unsigned long
          id = pageWindow->id();

        if ( id == ID_PAGE1 )
        {
           helpPanel = PANEL_PAGE1;
        }
        else if ( id == ID_PAGE2 )
        {
           helpPanel = PANEL_PAGE2;
        }
     }

     if ( helpPanel )
     {
        IHelpWindow
         *help = IHelpWindow::helpWindow( frame );
        help->show( IResourceId( helpPanel ) );
        stopProcessingEvent = true;
     }
  }
  return stopProcessingEvent;
}
#endif

IBase::Boolean DynamicPageHelpHdr::subitemNotFound
                           ( IHelpSubitemNotFoundEvent& event )
{
  Boolean
    stopProcessingEvent = false;
  if ( event.isWindow() )
  {
     // The help system cannot find an entry in a help subtable for
     // the control with the input focus.  By omitting the entry,
     // we can hook this error case to dynamically display the
     // contextual help panel for the current control.  In our case,
     // we can display different help panels for two controls with
     // the same window identifier.
     unsigned long
       topicId = event.topicId(),
       subtopicId = event.subtopicId(),
       helpPanel = 0;
     if ( topicId == ID_PAGE1  &&  subtopicId == ID_ENTRY3 )
     {
        helpPanel = PANEL_ENTRY3;
     }
#ifdef IC_PM
     // For Windows, we can also use the IWindow::setHelpId function
     // for dynamically controlling the contextual help panel of a
     // control.  We call IWindow::setHelpId in place of using the
     // below code, which would have worked just as well, for the
     // ID_ENTRYC entry field.
     else if ( topicId == ID_PAGE2  &&  subtopicId == ID_ENTRYC )
     {
        helpPanel = PANEL_ENTRYC;
     }
#endif

     if ( helpPanel )
     {
        IFrameWindow
         *frame = (IFrameWindow*)event.dispatchingWindow();
        IHelpWindow
         *help = IHelpWindow::helpWindow( frame );
        help->show( IResourceId( helpPanel ) );
        event.setResult( true );
        stopProcessingEvent = true;
     }
  }
  return stopProcessingEvent;
}

ObjectView::ObjectView ( unsigned long id,
                         IWindow* parent,
                         IWindow* owner )
  : IFrameWindow ( id, parent, owner, IRectangle(),
                   IFrameWindow::defaultStyle()
                    | IFrameWindow::dialogBackground ),
    notebook ( ID_CLIENT, this, this ),
    page1 ( ID_PAGE1, &notebook, &notebook ),
    heading1 ( ID_DUMMY, &page1, &page1 ),
    prompt1  ( ID_DUMMY, &page1, &page1 ),
    prompt2  ( ID_DUMMY, &page1, &page1 ),
    prompt3  ( ID_DUMMY, &page1, &page1 ),
    entry1 ( ID_ENTRY1, &page1, &page1 ),
    entry2 ( ID_ENTRY2, &page1, &page1 ),
    entry3 ( ID_ENTRY3, &page1, &page1 ),
    page2 ( ID_PAGE2, &notebook, &notebook ),
    headingA ( ID_DUMMY, &page2, &page2 ),
    promptA  ( ID_DUMMY, &page2, &page2 ),
    promptB  ( ID_DUMMY, &page2, &page2 ),
    promptC  ( ID_DUMMY, &page2, &page2 ),
    entryA ( ID_ENTRYA, &page2, &page2 ),
    entryB ( ID_ENTRYB, &page2, &page2 ),
    entryC ( ID_ENTRYC, &page2, &page2 ),
    page3 ( ID_PAGE3, &notebook, &notebook, IRectangle(),
            IFrameWindow::dialogBackground ),
    page3a ( ID_CLIENT, &page3, &page3 ),
    headingX ( ID_DUMMY, &page3a, &page3a ),
    promptX  ( ID_DUMMY, &page3a, &page3a ),
    promptY  ( ID_DUMMY, &page3a, &page3a ),
    entryX ( ID_ENTRYX, &page3a, &page3a ),
    entryY ( ID_ENTRYY, &page3a, &page3a ),
    dialog ( ID_DIALOG, &notebook, &notebook )
{
  ITitle
    title( this, "Object1 - View" );
  this->setClient( &notebook );

  // Set-up the first page.
  heading1
   .setText( "This is a canvas page window." );
  prompt1
   .setText( "Has contextual help" );
  prompt2
   .setText( "No contextual help" );
  prompt3
   .setText( "Dynamic contextual help" );
  entry1
   .enableTabStop()
   .enableGroup();
  entry2
   .enableTabStop();
  entry3
   .enableTabStop();
  page1
   .addToCell( &heading1, 2, 2, 3 )
   .addToCell( &prompt1,  2, 4 )
   .addToCell( &prompt2,  2, 6 )
   .addToCell( &prompt3,  2, 8 )
   .addToCell( &entry1,   4, 4 )
   .addToCell( &entry2,   4, 6 )
   .addToCell( &entry3,   4, 8 );
  page1
   .setColumnWidth( 4, 1, true )
   .setColumnWidth( 7, IMultiCellCanvas::defaultCell().width() )
   .setRowHeight( 1, 20, true )
   .setRowHeight( 3, 20, true )
   .setRowHeight( 5, 20, true )
   .setRowHeight( 7, 20, true )
   .setRowHeight( 9, 20, true )
   .sizeTo( page1.minimumSize() );

  // Set-up the second page.
  headingA
   .setText( "This is another canvas page window." );
  promptA
   .setText( "Has contextual help" );
  promptB
   .setText( "No contextual help" );
  promptC
   .setText( "Dynamic contextual help" );
#ifdef IC_WIN
  // For OS/2, we use IHelpHandler virtual functions in place of
  // calls to IWindow::setHelpId for dynamically controlling the
  // contextual help panels of the entry fields and general help
  // panel of this canvas.
  entryA
   .setHelpId( PANEL_ENTRYA );
  entryC
   .setHelpId( PANEL_ENTRYC );
  page2
   .setHelpId( PANEL_PAGE2 );
#endif
  entryA
   .enableTabStop()
   .enableGroup();
  entryB.enableTabStop();
  entryC.enableTabStop();
  page2
   .addToCell( &headingA, 2, 2, 3 )
   .addToCell( &promptA,  2, 4 )
   .addToCell( &promptB,  2, 6 )
   .addToCell( &promptC,  2, 8 )
   .addToCell( &entryA,   4, 4 )
   .addToCell( &entryB,   4, 6 )
   .addToCell( &entryC,   4, 8 );
  page2
   .setColumnWidth( 4, 1, true )
   .setColumnWidth( 7, IMultiCellCanvas::defaultCell().width() )
   .setRowHeight( 1, 20, true )
   .setRowHeight( 3, 20, true )
   .setRowHeight( 5, 20, true )
   .setRowHeight( 7, 20, true )
   .setRowHeight( 9, 20, true )
   .sizeTo( page2.minimumSize() );

  // Set-up the third page.
#ifdef IC_PM
  childHelpHdr
   .handleEventsFor( &page3 );
#endif
  headingX
   .setText( "This is another canvas in a frame page window." );
  promptX
   .setText( "Has contextual help" );
  promptY
   .setText( "No contextual help" );
  entryX
   .enableTabStop()
   .enableGroup();
  entryY.enableTabStop();
  page3a
   .addToCell( &headingX, 2, 2, 3 )
   .addToCell( &promptX,  2, 4 )
   .addToCell( &promptY,  2, 6 )
   .addToCell( &entryX,   4, 4 )
   .addToCell( &entryY,   4, 6 );
  page3a
   .setColumnWidth( 4, 1, true )
   .setColumnWidth( 7, IMultiCellCanvas::defaultCell().width() )
   .setRowHeight( 1, 20, true )
   .setRowHeight( 3, 20, true )
   .setRowHeight( 5, 20, true )
   .setRowHeight( 7, 20, true )
   .sizeTo( page3a.minimumSize() );
  page3
   .setClient( &page3a );
  page3
   .setMinimumSize( page3.frameRectFor( page3a.rect() ).size() );

  // Set-up the fourth page.
#ifdef IC_PM
  childHelpHdr
   .handleEventsFor( &dialog );
#endif
  IColor background =
    notebook.backgroundColor();
  notebook
   .setMinorTabSize( ISize( ) )
   .setBinding( INotebook::spiral )
   .setPageBackgroundColor( background )
   .setMajorTabBackgroundColor( background );
  tabHelpHdr
   .handleEventsFor( &notebook );
  dynamicPageHelpHdr
   .handleEventsFor( this );

  // Add the pages to the notebook.
  // Store the help panel identifiers for the notebook tabs as
  // user data for the page.
  INotebook::PageSettings
    pageInfo( "1st", 0,
              INotebook::PageSettings::autoPageSize
               | INotebook::PageSettings::majorTab );
  pageInfo
   .setUserData( PANEL_PAGE1_TAB );
  notebook
   .addFirstPage( pageInfo, &page1 );
  pageInfo
   .setTabText( "2nd" )
   .setUserData( PANEL_PAGE2_TAB );
  notebook
   .addLastPage( pageInfo, &page2 );
  pageInfo
   .setTabText( "3rd" )
   .setUserData( PANEL_PAGE3_TAB );
  notebook
   .addLastPage( pageInfo, &page3 );
  pageInfo
   .setTabText( "4rth" )
   .setUserData( PANEL_DIALOG_TAB );
  notebook
   .addLastPage( pageInfo, &dialog );

  IPoint
    nextShellPoint = IFrameWindow::nextShellRect().bottomLeft();
  (*this)
   .moveSizeToClient( IRectangle( nextShellPoint,
                                  (ISize)notebook.minimumSize() ));
  notebook
   .setFocus();
}

IBase::Boolean ShowFileDialogCmdHdr::command ( ICommandEvent& event )
{
  Boolean
    stopProcessingEvent = false;
  if ( event.commandId() == ID_SHOWFILEDLG )
  {
     IFileDialog
       fileDialog( 0,
                   event.dispatchingWindow(),
                   IFileDialog::classDefaultStyle
                    | IFileDialog::helpButton );
  }
  return stopProcessingEvent;
}
