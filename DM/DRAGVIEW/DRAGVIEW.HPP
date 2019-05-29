//*********************************************************
// Direct Manipulation - Drag Information Viewer
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//*********************************************************
#include <idmitem.hpp>
#include <idmtgtrn.hpp>

class DragViewItem : public IDMItem {
typedef IDMItem
  Inherited;
public:

/*------------------------------- Constructors -------------------------------*/
  DragViewItem  ( const IDMItem::Handle& dragItem );

virtual
  ~DragViewItem ( );


/*------------------------------ Drop Processing -----------------------------*/
virtual Boolean
  targetDrop ( IDMTargetDropEvent& event );

DragViewItem
 &displayIOCItem ( IDMTargetDropEvent& event ),
 &displayItem    ( IDMTargetDropEvent& event );

}; // DragViewItem


class DragViewTargetRenderer: public IDMTargetRenderer {
typedef IDMTargetRenderer
  Inherited;
public:
/*------------------------------- Constructors -------------------------------*/
  DragViewTargetRenderer  ( );

virtual
  ~DragViewTargetRenderer ( );

/*--------------------------------- Rendering --------------------------------*/
IDM::DropIndicator
  canRender         ( const IDMItem::Handle& );

DragViewTargetRenderer
 &targetRender      ( IDMTargetDropEvent&    event,
                      const IDMItem::Handle& dragItem );
}; // DragViewTargetRenderer

