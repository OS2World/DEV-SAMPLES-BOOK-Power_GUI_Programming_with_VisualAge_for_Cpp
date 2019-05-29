//************************************************************
// Container Control - Dates and Times as IDate/ITime        
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <iapp.hpp>
#include "developr.hpp"


void main ()
{

DeveloperList developers("Developer List");

// Details view
developers.container()
  .showDetailsView()
  .setFocus();

developers
  .show();

IApplication::current().run();
}
