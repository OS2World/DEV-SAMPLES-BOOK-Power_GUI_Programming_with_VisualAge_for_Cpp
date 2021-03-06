//************************************************************
// Using Resources - Building a Resource DLL
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <iostream.h>
#include <istring.hpp>
#include <ireslib.hpp>
#include "mytext.h"

void main( )
{
  IDynamicLinkLibrary dllLib("myeng");
  IString str = dllLib.loadString(MY_TEXT);

  cout << "The resource text is [" << str << "]" << endl;
}

