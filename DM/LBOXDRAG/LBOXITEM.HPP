#ifndef _LBOXITEM_
#define _LBOXITEM_
//************************************************************
// Direct Manipulation - List Box Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************

#include <idmitem.hpp>
#include <idmprov.hpp>

class IListBox;
class IDMSourceOperation;
class IDMSourceDiscardEvent;
class IDMTargetDropEvent;
class IDMTargetEvent;
class IPoint;

class ListBoxItem : public IDMItem {
typedef IDMItem
  Inherited;
/*******************************************************************************
* Objects of this class represent items being dragged from or dropped on       *
* a listbox during direct manipulation (drag/drop).                            *
*******************************************************************************/
public:
/*------------------------- Constructors/Destructor ----------------------------
| This class provides two constructors:                                        |
|   o One that gets called to construct items being dragged from a             |
|     list box.                                                                |
|   o One that gets called to construct items when the user drags              |
|     something over a list box.                                               |
|                                                                              |
| The static function generateSourceItems is called by the template class      |
| IDMItemProviderFor<ListBoxItem>; it invokes the source constructor.          |
------------------------------------------------------------------------------*/
  ListBoxItem ( IDMSourceOperation*    srcOp,
                IListBox*              srcLB,
                unsigned               index );
  ListBoxItem ( const IDMItem::Handle& dragItem );

virtual
  ~ListBoxItem ( );

static Boolean
  generateSourceItems( IDMSourceOperation* srcOp );

/*------------------------------ Implementation --------------------------------
| These functions provide utilities used to implement this class:              |
|   LocType                - Enumeration of location types (before, on, after) |
|   TgtLocation            - Nested class representing a drop location.        |
|   sourceIndex            - Returns index of item at source drag position.    |
|   itemHeight             - Returns height of items in the listbox.           |
|   horizontalScrollHeight - Returns height of the horizontal scroll bar.      |
|   verticalScrollWidth    - Returns width of the vertical scroll bar.         |
|   targetLocation         - Returns TgtLocation at dragover/drop point.       |
------------------------------------------------------------------------------*/
enum LocType
  {
  before,
  on,
  after
  };

struct TgtLocation {
  TgtLocation ( LocType type, unsigned index );
Boolean
  operator == ( const TgtLocation& loc ) const;
LocType
  type;
unsigned
  index;
};

static TgtLocation
  targetLocation ( IListBox* pLB, const IPoint& pt );

static unsigned
  sourceIndex            ( IListBox* pLB, const IPoint& pt ),
  itemHeight             ( IListBox* pLB ),
#ifdef IC_WIN
  horizontalScrollHeight ( ),
#endif
  verticalScrollWidth    ( IListBox* pLB );

/*-------------------------------- Overrides -----------------------------------
| These functions are overridden in this class to tailor drag/drop for         |
| the list box:                                                                |
|   targetDrop    - Handles dropping on the list box.                          |
|   sourceEnd     - Handles completion of operation (deletion if move).        |
|   sourceDiscard - Handles dropping on the shredder (OS/2 only).              |
------------------------------------------------------------------------------*/
virtual Boolean
  sourceEnd     ( IDMSourceEndEvent&     event ),
#ifdef IC_PM
  sourceDiscard ( IDMSourceDiscardEvent& event ),
#endif
  targetDrop    ( IDMTargetDropEvent&    event );

}; // class ListBoxItem

class ListBoxItemProvider : public IDMItemProviderFor<ListBoxItem> {
typedef IDMItemProviderFor<ListBoxItem>
  Inherited;
/*******************************************************************************
* Objects of this class are attached to listboxes in order to provide          *
* drag/drop support (using ListBoxItems).                                      *
*******************************************************************************/
public:
/*------------------------- Constructors/Destructor ----------------------------
| The constructor takes an optional list box (which will autoamtically         |
| be attached to).                                                             |
------------------------------------------------------------------------------*/
  ListBoxItemProvider ( IListBox* listBox = 0 );

/*-------------------------------- Attaching -----------------------------------
| This function ensures we attach only to listbox controls.                    |
------------------------------------------------------------------------------*/
virtual ListBoxItemProvider
 &provideItemsFor( IListBox* listBox );

/*----------------------------- Target Emphasis --------------------------------
| drawEmphasis - Draws target emphasis.                                        |
------------------------------------------------------------------------------*/
virtual ListBoxItemProvider
 &drawEmphasis ( IListBox*                       listBox,
                 IDMTargetEvent&                 event,
                 const ListBoxItem::TgtLocation& target );

/*-------------------------------- Overrides -----------------------------------
| This class overrides these functions:                                        |
|   provideLeaveSupport  - Removes target emphasis.                            |
|   provideEnterSupport  - Draws target emphasis and checks operation.         |
------------------------------------------------------------------------------*/
virtual Boolean
  provideLeaveSupport( IDMTargetLeaveEvent& event ),
  provideEnterSupport( IDMTargetEnterEvent& event );

private:
// Make operator private to prevent attaching to wrong control.
ListBoxItemProvider
 *operator & ();
};

#endif // _LBOXITEM_
