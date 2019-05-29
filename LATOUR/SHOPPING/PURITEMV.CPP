/************************************************************
/ Tour of the UICL - Shopping List Example Program
/
/ Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
/ Copyright (c) 1997 John Wiley & Sons, Inc. 
/ All Rights Reserved.
************************************************************/
#include <ibase.hpp>
#ifdef IC_PM
  #define INCL_WINSTDFILE   // For DID_xxx file dialog IDs.
  #include <os2.h>
#else
  #include <windows.h>
#endif

#include <ifont.hpp>
#include <ifiledlg.hpp>
#include <ilistbox.hpp>
#include <imsgbox.hpp>
#include <ireslib.hpp>
#include <isysmenu.hpp>
#include <ititle.hpp>
#include <ibmpctl.hpp>
#include <imcelcv.hpp>
#include <ipushbut.hpp>
#include <igbitmap.hpp>

#include "puritem.hpp"
#include "puritemv.hpp"
#include "shopping.h"


//===================== PurchaseItemView ======================

PurchaseItemView :: PurchaseItemView
                         ( PurchaseItem& purchaseItem,
                           unsigned long windowId,
                           IWindow* owner )
  : IFrameWindow ( windowId, 0, owner, IRectangle(),
                   IFrameWindow::defaultStyle()
                    | IFrameWindow::dialogBackground ),
    fPurchaseItem( purchaseItem ),
    fNotebook( ID_PURCHASEITEMBOOK, this, this ),
    fCmdHandler( this, purchaseItem ),
    fPage1( ID_PURCHASEITEMPAGE1, &fNotebook, &fNotebook ),
    fPage2( ID_PURCHASEITEMPAGE2, &fNotebook, &fNotebook ),
    fNamePrompt( ID_NAMEPROMPT, &fPage1, &fPage1 ),
    fName( ID_NAME, &fPage1, &fPage1 ),
    fQuantityPrompt( ID_QUANTITYPROMPT, &fPage1, &fPage1 ),
    fQuantity( ID_QUANTITY, &fPage1, &fPage1 ),
    fManufacturerPrompt( ID_MANUFACTURERPROMPT,
                          &fPage1, &fPage1 ),
    fManufacturer( ID_MANUFACTURER, &fPage1, &fPage1 ),
    fPricePrompt( ID_PRICEPROMPT, &fPage1, &fPage1 ),
    fPrice( ID_PRICE, &fPage1, &fPage1 ),
    fNotesPrompt( ID_NOTESPROMPT, &fPage1, &fPage1 ),
    fNotes( ID_NOTES, &fPage1, &fPage1, IRectangle(),
             IMultiLineEdit::classDefaultStyle |
             IMultiLineEdit::ignoreTab ),
    fBitmapButton( ID_BITMAPBUTTON, &fPage2, &fPage2),
    fBookBitmap( ID_POWERBITMAP, &fPage2, &fPage2,
                  IResourceId( ID_THEBOOKBITMAP ) )
{
  ITitle title( this, fPurchaseItem.name(),
                "Shopping List Settings View" );
  if (owner)
  {                     // Not a primary window.
     this->removeFromWindowList();  // Remove from switch list.
  }
  this->setClient( &fNotebook );

  IColor background =
    fNotebook.backgroundColor( );
  fNotebook
   .setMinorTabSize( ISize( 0, 0 ) )
   .setBinding( INotebook::spiral )
   .setPageBackgroundColor( background )
   .setMajorTabBackgroundColor( background );

  // Set up first page of the notebook.
  this->initializePage1();

  // Set up second page of the notebook.
  this->initializePage2();

  // Add the pages to the notebook.
  INotebook::PageSettings
    pageInfo( "1st", 0,
              INotebook::PageSettings::autoPageSize
               | INotebook::PageSettings::majorTab );
  fNotebook.addFirstPage( pageInfo, &fPage1 );
  pageInfo.setTabText( "2nd" );
  fNotebook.addLastPage( pageInfo, &fPage2 );

  // Size the frame window.
  IRectangle rectFrame =
    this->frameRectFor( IRectangle( IPoint( 0, 0 ),
                                    fNotebook.minimumSize() ));
  this->sizeTo( rectFrame.size() );
}

PurchaseItemView& PurchaseItemView :: initializePage1 ( )
{
  // Locate controls on the multicell canvas.
  fPage1
   .addToCell( &fNamePrompt,         2, 2 )
   .addToCell( &fName,               4, 2 )
   .addToCell( &fQuantityPrompt,     2, 4 )
   .addToCell( &fQuantity,           4, 4 )
   .addToCell( &fManufacturerPrompt, 2, 6 )
   .addToCell( &fManufacturer,       4, 6 )
   .addToCell( &fPricePrompt,        2, 8 )
   .addToCell( &fPrice,              4, 8 )
   .addToCell( &fNotesPrompt,        2, 10 )
   .addToCell( &fNotes,              4, 10, 1, 2 );

  // Allow MLE control to expand vertically with the window.
  fPage1.setRowHeight( 11, 0, true );

  // Allow MLE and entry fields to expand horizontally.
  fPage1.setColumnWidth( 4, 0, true );

  // Create bottom and right margins.
  ISize defaultCell = IMultiCellCanvas::defaultCell();
  fPage1
   .setRowHeight( 12, defaultCell.height() )
   .setColumnWidth( 5, defaultCell.width() );

  // Set up the child controls.
  fNamePrompt.setText( "Name" );
  fName
   .setLimit(60)
   .setText( fPurchaseItem.name() )
   .enableTabStop()
   .enableGroup();
  fQuantityPrompt.setText( "Quantity" );
  fQuantity
   .setText( fPurchaseItem.quantity() )
   .enableTabStop()
   .enableGroup();
  fManufacturerPrompt.setText( "Manufacturer" );
  fManufacturer
   .setText( fPurchaseItem.manufacturer() )
   .enableTabStop()
   .enableGroup();
  fPricePrompt.setText( "Price" );
  fPrice
   .setText( IString( fPurchaseItem.price() ))
   .enableTabStop()
   .enableGroup();
  fNotesPrompt.setText( "Notes" );
  fNotes
   .setText( fPurchaseItem.notes() )
   .enableTabStop()
   .enableGroup();
  ISize maxSize = IFont( &fNotes ).maxSize();
  fNotes.setMinimumSize( maxSize * 3 );

  return *this;
}

PurchaseItemView& PurchaseItemView :: initializePage2 ( )
{
  fPage2
    .addToCell( &fBookBitmap,   2, 2 )
    .addToCell( &fBitmapButton, 2, 4 )
    .setColumnWidth( 1, 0, true)
    .setColumnWidth( 3, 0, true)
    .setRowHeight( 1, 0, true)
    .setRowHeight( 3, 0, true)
    .setRowHeight( 5, 0, true);

  fBitmapButton
   .setText("Change Bitmap")
   .enableTabStop()
   .enableGroup();


  fPage2.sizeTo( fBookBitmap.displaySize() );

  return *this;
}

IBase::Boolean PurchaseItemView :: validated ( )
{
  Boolean valid = true;
  if (fName.text().strip() == IString())
  {
     IPageHandle page = fNotebook.firstPage();
     fNotebook.turnToPage( page );
     fName.setFocus();
     IMessageBox msg( this );
     msg.show( "You must specify a name.",
               IMessageBox::okButton
                | IMessageBox::errorIcon
                | IMessageBox::moveable );
     valid = false;
  }
  return valid;
}

PurchaseItemView& PurchaseItemView :: updateDataObject ( )
{
  fPurchaseItem
   .setName( fName.text().strip() )
   .setQuantity( fQuantity.text().strip() )
   .setManufacturer( fManufacturer.text().strip() )
   .setPrice( fPrice.text().asDouble() )
   .setNotes( fNotes.text().strip() );
// temporary until problem with cnr emphasis is fixed
#ifdef IC_PM
   fPurchaseItem.setClosed();
#endif
  return *this;
}

PurchaseItemView&
  PurchaseItemView :: updateBitmap ( const IString& fileName )
{
  IString upperFileName = IString::upperCase(fileName);
  if (fileName != IString() && upperFileName.includes(".BMP"))
  {
     IGBitmap bitmap(fileName);
     IBitmapHandle bitmapHandle = bitmap.handle();
     fBookBitmap.setBitmap (bitmapHandle);
  }
  return *this;
}

//================ PurchaseItemView::Handler ==================

PurchaseItemView::CmdHandler :: CmdHandler ( PurchaseItemView* frame,
                                             PurchaseItem& purchaseItem )
            : fPurchaseItemView(frame), fPurchaseItem(purchaseItem)
{
  handleEventsFor( frame->client() );
}

IBase::Boolean PurchaseItemView::CmdHandler :: systemCommand
                                          ( ICommandEvent& event )
{
  Boolean stopProcessing = false;
  if (event.commandId() == ISystemMenu::idClose)
  {                // View is being closed.
     if (fPurchaseItemView->validated())
     {             // Save any changes.
        fPurchaseItemView->updateDataObject();
     }
     else
     {             // Error, don't close the window.
        stopProcessing = true;
     }
  }

  return stopProcessing;
}

IBase::Boolean PurchaseItemView::CmdHandler :: command
                                          ( ICommandEvent& event )
{
  Boolean stopProcessing = false;
  if (event.commandId() == ID_BITMAPBUTTON)
  {
     // set up the file dialog as a child of the desktop.
     IFileDialog::Settings settings;
     settings.setFileName( "*.bmp" );

     IFileDialog fileDlg( 0, fPurchaseItemView, settings );
     if ( fileDlg.pressedOK() )
     {
        fPurchaseItemView->updateBitmap(fileDlg.fileName());
     }
     stopProcessing = true;
  }

  return stopProcessing;
}
