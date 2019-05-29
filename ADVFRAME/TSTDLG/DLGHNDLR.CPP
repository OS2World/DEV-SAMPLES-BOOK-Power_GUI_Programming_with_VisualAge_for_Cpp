//************************************************************
// Advanced Frame - Dialog Window Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************

#include "dlghndlr.hpp"

DialogInitEvent::DialogInitEvent ( const IEvent& event )
  : IEvent( event )
  {
  }

IWindowHandle DialogInitEvent::defaultFocusWindow ( ) const
  {
  return IWindowHandle( parameter1() );
  }

void *DialogInitEvent::createParameters ( ) const
  {
  return parameter2();
  }

DialogInitEvent& DialogInitEvent :: setFocusChanged( )
  {
  setResult( true );
  return *this;
  }

Boolean DialogHandler::initialize( DialogInitEvent& initEvent )
  {
  return false;
  }

Boolean DialogHandler::dispatchHandlerEvent( IEvent& event )
  {
  return false;
  }

