//************************************************************
// Direct Manipulation - Spin Button Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <ispintxt.hpp>
#include <ientryfd.hpp>
#include <itrace.hpp>
#include "spinitem.hpp"


// Construct IDMItem with type=text, operations=copyable.
SpinButtonItem::SpinButtonItem ( IDMSourceOperation* srcOp )
      : IDMItem( srcOp, IDM::text, IDMItem::copyable | IDMItem::moveable )
  {
  // Support intraprocess drag and drop only.
  this -> addRMF( IDMItem::rmfFrom( IDM::rmLibrary,
                                    IDMItem::rfForThisProcess() ) );
  // Set item contents to selected spin button text.
  IEntryField
    *pEF = (IEntryField*)( srcOp->sourceWindow() );
  ITRACE_DEVELOP( pEF->selectedText() );

  this->setContents( pEF->selectedText() );
  }


Boolean SpinButtonItem::generateSourceItems ( IDMSourceOperation* srcOp )
  {
  // Source item is object of this class.
  IDMItem::Handle
    item( new SpinButtonItem( srcOp ) );
  // Add it to the source operation.
  srcOp -> addItem( item );

  // Indicate an item is available to drag.
  return true;
  }

Boolean SpinButtonItem::targetDrop ( IDMTargetDropEvent& event )
  {
  // Add dropped text to the spin button.
  ITextSpinButton
   *pSpin = (ITextSpinButton*)( event.window()->parent() );
  pSpin -> addAsLast( this->contents() );
  pSpin -> spinTo( this->contents() );
  return true;
  }

unsigned long
    SpinButtonItem::supportedOperationsFor ( const IString& selectedRMF ) const
  {
  // Permit copying only.
  return IDMItem::copyable;
  }

