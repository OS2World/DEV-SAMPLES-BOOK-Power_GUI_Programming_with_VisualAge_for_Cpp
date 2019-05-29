#ifndef _MYEXTNS_
#define _MYEXTNS_
//************************************************************
// Advanced Frame - Frame Extension Drawing Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <iframext.hpp>
#include <icolor.hpp>

class MyExtension : public IFrameExtension {
public:
  MyExtension( IWindow *control,
               IFrameWindow::Location loc);
  MyExtension( IWindow *control,
               IFrameWindow::Location loc,
               double size );
  MyExtension( IWindow *control,
               IFrameWindow::Location loc,
               int size );
virtual unsigned long
  separatorWidth ( ) const;

virtual void
  drawSeparator ( const IPresSpaceHandle &hps );

virtual MyExtension
 &setSeparatorWidth ( unsigned long width ),
 &setSeparatorColor ( const IColor& newColor );

private:
unsigned long
  width;
IColor
  color;
MyExtension ( const MyExtension&);
MyExtension
 &operator= ( const MyExtension&);
};

#endif // _MYEXTNS_
