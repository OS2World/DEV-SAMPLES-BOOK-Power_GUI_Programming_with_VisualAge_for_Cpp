//************************************************************
// Container - Combined Tree and Details View
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <iapp.hpp>
#include "partlist.hpp"
#include <malloc.h>

void main ()
{
  // Create the view of EXE parts and 
  // open it.
  PartsList partsView;
  partsView
   .open();

  IApplication::current().run();
  _dump_allocated(10);
}

