/************************************************************
/ Tour of the UICL - Shopping List Example Program
/
/ Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
/ Copyright (c) 1997 John Wiley & Sons, Inc. 
/ All Rights Reserved.
************************************************************/
#include <ibase.hpp>
#ifdef IC_PM
  #define INCL_WINWORKPLACE   // For WinLoadFileIcon, WinFreeFileIcon.
  #include <os2.h>
#else
  #include <windows.h>
#endif

#include <icnrctl.hpp>
#include <iexcept.hpp>
#include <ihandle.hpp>

#include "puritem.hpp"
#include "puritemv.hpp"
#include "shopping.h"


//======================= PurchaseItem ========================

PurchaseItem :: PurchaseItem ( const IString& name,
                               const IString& quantity,
                               const IString& manufacturer,
                               double price,
                               const IString& notes )
  : IContainerObject( name,
                      ISystemPointerHandle
                        ( ISystemPointerHandle::question )),
    fManufacturer( manufacturer ),
    fNotes( notes ),
    fQuantity( quantity ),
    fPrice( price )
{
  IASSERTPARM( name != IString() )
}

PurchaseItem :: PurchaseItem ( const PurchaseItem& purchaseItem )
  : IContainerObject( purchaseItem ),
    fManufacturer( purchaseItem.manufacturer() ),
    fNotes( purchaseItem.notes() ),
    fQuantity( purchaseItem.quantity() ),
    fPrice( purchaseItem.price() )
{        // Copy constructor for drag and drop.
}

PurchaseItem :: ~PurchaseItem ( )
{
}

PurchaseItem& PurchaseItem :: setName ( const IString& name )
{
  IASSERTPARM( name != IString() )

  setIconText( name );
  return *this;
}

PurchaseItem&
  PurchaseItem :: addNotes ( const IString& moreNotes )
{
  if (fNotes.length())
  {
     fNotes += "\r\n";
  }
  fNotes += moreNotes;
  return *this;
}


PurchaseItem&
  PurchaseItem :: setManufacturer
                     ( const IString& manufacturer )
{
  fManufacturer = manufacturer;
  return *this;
}

PurchaseItem&
  PurchaseItem :: setQuantity ( const IString& quantity )
{
  fQuantity = quantity;
  return *this;
}

PurchaseItem& PurchaseItem :: setPrice ( double price )
{
  fPrice = price;
  return *this;
}

PurchaseItem& PurchaseItem :: setNotes ( const IString& notes )
{
  fNotes = notes;
  return *this;
}

IString PurchaseItem :: name ( ) const
{
  return this->iconText();
}

IString PurchaseItem :: manufacturer ( ) const
{
  return fManufacturer;
}

IString PurchaseItem :: quantity ( ) const
{
  return fQuantity;
}

IString PurchaseItem :: notes ( ) const
{
  return fNotes;
}


double PurchaseItem :: price ( ) const
{
  return fPrice;
}

void
  PurchaseItem :: handleOpen ( IContainerControl* container )
{
  // User has opened a PurchaseItem object.
  // Create a secondary window with a settings view.
  PurchaseItemView* secondary =
    new PurchaseItemView( *this,
                          ID_PURCHASEITEMVIEW,
                          container->parent() );
  secondary->setAutoDeleteObject();
  (*secondary)
   .setFocus()
   .show();
//  temporary until bug in ICnrCtl::setEmphasis is fixed
#ifdef IC_PM
  this->IContainerObject::handleOpen( container );
#endif
}

IContainerObject* PurchaseItem :: objectCopy ( )
{
  // Copy the object, for copy via drag and drop.
  PurchaseItem *copy = new PurchaseItem( *this );
  return (IContainerObject *)copy;
}
