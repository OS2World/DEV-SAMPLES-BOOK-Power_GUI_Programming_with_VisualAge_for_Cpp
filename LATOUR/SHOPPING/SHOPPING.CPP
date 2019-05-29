
/************************************************************
/ Tour of the UICL - Shopping List Example Program
/
/ Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
/ Copyright (c) 1997 John Wiley & Sons, Inc.
/ All Rights Reserved.
************************************************************/
#include <iapp.hpp>
#include <icmdhdr.hpp>
#include <icnrctl.hpp>
#include <icnrhdr.hpp>
#include <idmsrch.hpp>
#include <idmtgth.hpp>
#include <iflytext.hpp>
#include <iflyhhdr.hpp>
#include <iframe.hpp>
#include <imsgbox.hpp>
#include <isplitcv.hpp>
#include <istattxt.hpp>
#include <itbar.hpp>
#include <itbarbut.hpp>

#include "puritem.hpp"
#include "shopping.h"


/********************************************************
/ ToolBarHandler class - Handle tool bar buttons
********************************************************/

class ToolBarHandler : public ICommandHandler {
public:
virtual IBase::Boolean
  command ( ICommandEvent& event );
};

IBase::Boolean ToolBarHandler::command( ICommandEvent& event)
{
   switch (event.commandId())
   {
     case IC_ID_OPEN:
     case IC_ID_SAVE:
     case IC_ID_CUT:
     case IC_ID_COPY:
     case IC_ID_PASTE:
     {
        IMessageBox message( IWindow::desktopWindow() );
        message.setTitle( "Informational Message Box" );
        message.show( "This capability is not implemented in this example.",
                      IMessageBox::information );
        break;
     }
   }
   return true;
}

//=========================== Main ============================

void main ( )
{
  // Create the primary window with the two container views.
  IFrameWindow primary( "Shopping List", ID_SHOPPINGLIST );
  ISplitCanvas splitWindow( ID_LISTCLIENT, &primary, &primary );
  splitWindow.setOrientation( ISplitCanvas::horizontalSplit );
  primary.setClient( &splitWindow );

  // Add a tool bar to the primary window.
  IToolBar toolBar( ID_TOOLBAR, &primary );
  IToolBarButton
    openButton( IC_ID_OPEN, &toolBar, &toolBar ),
    saveButton( IC_ID_SAVE, &toolBar, &toolBar ),
    cutButton( IC_ID_CUT, &toolBar, &toolBar ),
    copyButton( IC_ID_COPY, &toolBar, &toolBar ),
    pasteButton( IC_ID_PASTE, &toolBar, &toolBar );
  toolBar
   .addAsLast( &openButton, true )
   .addAsLast( &saveButton )
   .addAsLast( &cutButton, true )
   .addAsLast( &copyButton )
   .addAsLast( &pasteButton )
   .disableDragDrop( );

  // Add fly-over help to the tool bar.
  IFlyText flyText( ID_FLYTEXT, &primary );
  IFlyOverHelpHandler flyHandler( &flyText );
  flyHandler
   .setDefaultText( "\0" )
   .setResourceLibrary( 0 )
   .handleEventsFor( &toolBar );
  ToolBarHandler commandHandler;
  commandHandler
   .handleEventsFor( &primary )
   .handleEventsFor( &toolBar );

  // Create the buy list and not-needed list containers.
  IContainerControl
    buyList( ID_BUYLIST, &splitWindow, &splitWindow ),
    dontBuyList( ID_DONTBUYLIST, &splitWindow, &splitWindow );

  // Set up the two containers.
  buyList
   .setTitle( "Items to buy" )
   .showTitle()
   .showTitleSeparator()
   .showIconView()
   .arrangeIconView()
   .setDeleteObjectsOnClose()
   .enableTabStop();
  dontBuyList
   .setTitle( "Unneeded items" )
   .showTitle()
   .showTitleSeparator()
   .showIconView()
   .arrangeIconView()
   .setDeleteObjectsOnClose()
   .enableTabStop();

  // Get default processing for an "open" event.
  ICnrHandler cnrHandler;
  cnrHandler
   .handleEventsFor( &buyList )
   .handleEventsFor( &dontBuyList );

  // Support drag and drop of purchase items.
  IDMHandler::enableDragDropFor( &buyList );
  IDMHandler::enableDragDropFor( &dontBuyList );

  // Create some purchase items.
  PurchaseItem* p1 = new PurchaseItem( "Apple juice" );
  p1->setNotes( "Kids won't drink anything else." );
  PurchaseItem* p2 = new PurchaseItem( "Diskettes" );
  (*p2)
   .setQuantity( "1 box of 10 diskettes" )
   .addNotes( "3.5 inch, double-sided, high-density." )
   .addNotes( "Prefer preformatted." );
  PurchaseItem* p3 =
      new PurchaseItem( "Milk", "2 gallons", "Any", 3.75,
                        "Skim" );
  PurchaseItem* p4 = new PurchaseItem( "Fruit snacks" );
  p4->setNotes( "These are for the kids." );
  PurchaseItem* p5 =
      new PurchaseItem( "Eggs", "1 dozen", 0, 1.50,
                        "Extra large size." );
  p5->addNotes( "Be sure none are cracked." );
  IString bookName;
  #ifdef IC_PM
     bookName = "Power GUI Programming \n with  \n VisualAge for C++";
  #else
     bookName = "Power GUI Programming with VisualAge for C++";
  #endif
  PurchaseItem* p6 =
      new PurchaseItem( bookName, "100",
                        "John Wiley & Sons, Inc.", 49.95,
                        "Updated for Windows release." );
  (*p6)
   .addNotes( "Love the book!" )
   .setIcon( ID_THEBOOKICON );

  // Fill the split windows.
  dontBuyList
   .addObject( p1 )
   .addObject( p2 )
   .addObject( p3 )
   .addObject( p4 )
   .addObject( p5 );
  buyList.addObject( p6 );

  // Give the buy list the input focus and
  // show the window.
  buyList.setFocus();
  primary.show();

  // Start event processing.
  IApplication::current().run();
}
