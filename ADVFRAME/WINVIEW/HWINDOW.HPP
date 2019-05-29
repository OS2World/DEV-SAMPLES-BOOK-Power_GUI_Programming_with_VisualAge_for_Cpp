#ifndef _HWINDOW_
#define _HWINDOW_
//************************************************************
// Advanced Frame - Window Viewer Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <istring.hpp>
#include <ihandle.hpp>

class HWindow : public IWindowHandle {
public:
  HWindow ( IHandle::Value handle=0 );

IString
  asHexString ( ) const;
IString
  id          ( ) const;
IString
  text        ( ) const;
IString
  rectangle   ( ) const;
IString
  windowClass ( ) const;
IString
  style       ( ) const;

Boolean
  isValid     ( ) const;

class ChildCursor : public IVBase {
public:
  ChildCursor ( const HWindow& parent );
virtual
 ~ChildCursor ( );

virtual Boolean
  setToFirst ( ),
  setToNext  ( ),
  isValid    ( ) const;

virtual void
  invalidate ( );

virtual HWindow
  hWindow    ( ) const;

private:
  ChildCursor ( const ChildCursor& cursor );
ChildCursor
 &operator =  ( const ChildCursor& cursor );

IWindowHandle
  hwnd,
  hwndParent;
}; // HWindow::ChildCursor

};


#endif // _HWINDOW_
