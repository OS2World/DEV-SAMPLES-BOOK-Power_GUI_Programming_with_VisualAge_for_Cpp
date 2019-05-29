//************************************************************
// Packaging and Performance - Using Static Object Functions 
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <iostream.h>
#include <istring.hpp>
#include "appstat.hpp"
#include "mytext.h"

void main ( )
{
  IString str = AppStatics::englishDLL().loadString(MY_TEXT);

  cout << "The resource text is [" << str << "]" << endl;
}
