//*********************************************************
// Frame Window Basics - Minimize/Maximize Handler Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//*********************************************************
#include <ibase.hpp>

#ifdef IC_PM
  #define INCL_WINWINDOWMGR    // For WinShowWindow.
  #include <os2.h>
#else
  #include <windows.h>
#endif

#include <ihandle.hpp>
#include <iwindow.hpp>
#include "chdhider.hpp"

IBase::Boolean ChildHider::minimized ( IEvent& event )
{
  this->showChildren( event.window(), false );
  return false;
}

IBase::Boolean ChildHider::maximized ( IEvent& event )
{
  this->showChildren( event.window(), true );
  return false;
}

IBase::Boolean ChildHider::restored ( IEvent& event )
{
  this->showChildren( event.window(), true );
  return false;
}

void ChildHider::showChildren ( IWindow* parent,
                                Boolean  show )
{
  IWindow::ChildCursor
    cursor( *parent );
  for ( cursor.setToFirst();
        cursor.isValid();
        cursor.setToNext() )
  {
    IWindowHandle
      child = parent->childAt( cursor );

    // Show or hide the child window.
    // Note: We use a system API here to support
    //       non-IWindow windows.
#ifdef IC_PM
    WinShowWindow( child, show );
#else
    ShowWindow( child, show ? SW_SHOW : SW_HIDE );
#endif
  }
}
