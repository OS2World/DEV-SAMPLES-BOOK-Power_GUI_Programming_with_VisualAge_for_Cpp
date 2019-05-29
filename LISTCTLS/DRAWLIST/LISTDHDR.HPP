#ifndef _LISTDHDR_
#define _LISTDHDR_
/************************************************************
/ List Controls - List Box Custom Drawing
/
/ Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
/ Copyright (c) 1997 John Wiley & Sons, Inc.
/ All Rights Reserved.
************************************************************/
#include <ihandle.hpp>
#include <ilbdihdr.hpp>
#include <istring.hpp>

class IGBitmap;
// This is the handler to draw the item.  The handler
// is preloaded with the amount to indent each
// item, and containes the bitmaps necessary
// to indicate whether an item is expanded or
// collapsed.  The handler processes all requests
// for drawing by routing them to the private
// function drawListItem with an indication of whether
// selection needs to be drawn.
class DrawHandler : public IListBoxDrawItemHandler {
public:
  DrawHandler ( unsigned long indentBits=18 );

protected:
virtual Boolean
  setItemSize   ( IListBoxSizeItemEvent& event ),
  drawItem      ( IListBoxDrawItemEvent& event ),
  selectItem    ( IListBoxDrawItemEvent& event ),
  deselectItem  ( IListBoxDrawItemEvent& event ),
  drawListItem  ( IListBoxDrawItemEvent& event,
                  Boolean                selected);

private:
unsigned long
  fIndent,
  fBitmapIndent,
  fMaxCharHeight,
  fInternalLeading,
  fExternalLeading;
ISystemBitmapHandle
  fExpandHandle,
  fCollapseHandle;
IGBitmap
 *fExpandBitmap,
 *fCollapseBitmap;
};

#endif // _LISTDHDR_
