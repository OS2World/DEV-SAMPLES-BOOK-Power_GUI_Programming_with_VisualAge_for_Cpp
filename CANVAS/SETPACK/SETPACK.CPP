//*********************************************************
// Canvas - ISetCanvas Pack Options
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//*********************************************************
#include <iapp.hpp>
#include "packcv.hpp"

void main ( )
{
  PackAlignTest
    window;
  window
   .setFocus()
   .show();
  IApplication::current().run();
}
