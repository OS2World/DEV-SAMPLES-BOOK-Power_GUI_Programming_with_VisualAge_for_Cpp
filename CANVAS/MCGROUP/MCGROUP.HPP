#ifndef _MCGROUP_
#define _MCGROUP_
//*********************************************************
// Canvas - IMultiCellCanvas with Smarter Group Boxes
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//*********************************************************
#include <ifont.hpp>
#include <igroupbx.hpp>
#include <imcelcv.hpp>

class GroupBoxForMultiCell : public IGroupBox {
public:
  GroupBoxForMultiCell ( unsigned long     windowId,
                         IMultiCellCanvas* parentAndOwner,
                         unsigned long     row = 0 )
    : IGroupBox( windowId, parentAndOwner, parentAndOwner ),
      fRow( row )
  { }
GroupBoxForMultiCell
 &setMultiCellRow ( unsigned long row )
  {
    fRow = row;
    return this->setRowHeight();
  }

protected:
virtual GroupBoxForMultiCell
 &setLayoutDistorted ( unsigned long flagsOn,
                       unsigned long flagsOff )
  {
    if ( flagsOn & IWindow::fontChanged )
    {
       this->setRowHeight();
    }
    this->IGroupBox::setLayoutDistorted( flagsOn, flagsOff );
    return *this;
  }

private:
  GroupBoxForMultiCell ( const GroupBoxForMultiCell& );
GroupBoxForMultiCell
 &operator=            ( const GroupBoxForMultiCell& );
GroupBoxForMultiCell
 &setRowHeight ( )
  {
    if ( fRow )
    {
      IFont
        font( this );
      IMultiCellCanvas
       *canvas = (IMultiCellCanvas*)( this->parent() );
      ( *canvas)
       .setRowHeight( fRow, font.maxCharHeight() );
    }
    return *this;
  }
unsigned long
 fRow;
}; // GroupBoxForMultiCell

#endif // _MCGROUP_
