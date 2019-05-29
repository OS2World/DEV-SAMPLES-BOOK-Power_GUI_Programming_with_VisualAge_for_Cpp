#ifndef _PURITEM_
#define _PURITEM_
/************************************************************
/ Tour of the UICL - Shopping List Example Program
/
/ Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
/ Copyright (c) 1997 John Wiley & Sons, Inc. 
/ All Rights Reserved.
************************************************************/
#include <icnrobj.hpp>
#include <istring.hpp>
#include "shopping.h"

class IContainerControl;

// Align classes on four-byte boundaries.
#pragma pack(4)

//======================= PurchaseItem ========================
// An item you can add to a shopping list.
class PurchaseItem : public IContainerObject {
public:
  PurchaseItem    ( const IString& name,
                    const IString& quantity = "1",
                    const IString& manufacturer = IString(),
                    double price = 0,
                    const IString& notes = IString() );
  PurchaseItem    ( const PurchaseItem& purchaseItem );
 ~PurchaseItem    ( );

PurchaseItem
 &setName         ( const IString& name ),
 &setQuantity     ( const IString& quantity ),
 &setManufacturer ( const IString& manufacturer ),
 &setPrice        ( double price ),
 &setNotes        ( const IString& notes ),
 &addNotes        ( const IString& moreNotes );

IString
  name            ( ) const,
  quantity        ( ) const,
  manufacturer    ( ) const,
  notes           ( ) const;

double
  price           ( ) const;

virtual void
  handleOpen      ( IContainerControl* container );

virtual IContainerObject
 *objectCopy      ( );

private:
IString
  fQuantity,
  fManufacturer,
  fNotes;
double
  fPrice;
};  // class PurchaseItem

// Resume default compiler packing.
#pragma pack()

#endif // _PURITEM_
