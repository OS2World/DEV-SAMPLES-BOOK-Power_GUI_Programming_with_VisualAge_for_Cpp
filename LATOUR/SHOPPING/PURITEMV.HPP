#ifndef _PURITEMV_
#define _PURITEMV_
/************************************************************
/ Tour of the UICL - Shopping List Example Program
/
/ Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
/ Copyright (c) 1997 John Wiley & Sons, Inc. 
/ All Rights Reserved.
************************************************************/
#include <ibmpctl.hpp>
#include <icmdhdr.hpp>
#include <ientryfd.hpp>
#include <iframe.hpp>
#include <imcelcv.hpp>
#include <imle.hpp>
#include <inotebk.hpp>
#include <istattxt.hpp>
#include <istring.hpp>
#include <ipushbut.hpp>
#include "puritem.hpp"
#include "shopping.h"

// Align classes on four-byte boundaries.
#pragma pack(4)

//==================== PurchaseItemView =======================
// Settings view for a PurchaseItem object.
class PurchaseItemView : public IFrameWindow {
public:
  PurchaseItemView ( PurchaseItem& purchaseItem,
                     unsigned long windowId,
                     IWindow* owner = 0 );

Boolean
  validated        ( );

PurchaseItemView
 &updateDataObject ( ),
 &updateBitmap     ( const IString& fileName );

protected:
PurchaseItemView
 &initializePage1  ( ),
 &initializePage2  ( );

private:
  PurchaseItemView ( const PurchaseItemView& );
PurchaseItemView
 &operator=        ( const PurchaseItemView& );

  //======================= CmdHandler ======================
  // Process command actions for a PurchaseItem.
  class CmdHandler : public ICommandHandler {
  public:
    CmdHandler    ( PurchaseItemView*  frame,
                    PurchaseItem&      purchaseItem );
  protected:
  virtual Boolean
    command       ( ICommandEvent& event ),
    systemCommand ( ICommandEvent& event );

  private:
    CmdHandler   ( const CmdHandler& );
  CmdHandler
   &operator= ( const CmdHandler& );

  PurchaseItem
   &fPurchaseItem;
  PurchaseItemView
   *fPurchaseItemView;
  };  // class PurchaseItemView::CmdHandler

PurchaseItem
 &fPurchaseItem;
INotebook
  fNotebook;
CmdHandler
  fCmdHandler;
IMultiCellCanvas
  fPage1,
  fPage2;
IStaticText
  fNamePrompt,
  fQuantityPrompt,
  fManufacturerPrompt,
  fPricePrompt,
  fNotesPrompt;
IEntryField
  fName,
  fQuantity,
  fManufacturer,
  fPrice;
IMultiLineEdit
  fNotes;
IPushButton
  fBitmapButton;
IBitmapControl
  fBookBitmap;
};  // class PurchaseItemView

// Resume default compiler packing.
#pragma pack()

#endif // _PURITEMV_
