//************************************************************
// Notebook Control - Smart Guide Notebook - Smart Page           
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <istring.hpp>
#include "smrtguid.hpp"


SmartPage& SmartPage::setTabText ( const IString& tabText)
{ fTabText = tabText; return *this; }

IString SmartPage::tabText ( ) const
{ return fTabText; }

ISize SmartPage::minimumSize ( ) const
{ return ISize(0,0); }

Boolean SmartPage::isOKToClose ( IString& closeErrorIfFalse ) const
{ return true; }

SmartPage& SmartPage::setHelpId ( unsigned long helpId)
{ fHelpId = helpId; return *this;}

unsigned long SmartPage::helpId ( ) const
{ return fHelpId; }

