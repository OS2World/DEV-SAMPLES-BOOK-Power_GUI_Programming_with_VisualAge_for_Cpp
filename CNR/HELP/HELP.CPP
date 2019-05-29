//************************************************************
// Container Control - Help in the Container
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <iapp.hpp>
#include "devview.hpp"

void main()
{
  DeveloperView developers;
 
  developers
    .setFocus()
    .show();

  IApplication::current().run();
}
