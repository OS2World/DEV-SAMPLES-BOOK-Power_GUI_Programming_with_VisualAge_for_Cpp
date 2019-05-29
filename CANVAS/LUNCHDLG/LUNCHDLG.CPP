//*********************************************************
// Lunch dialog - Sample Dialog Template
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc.
// All Rights Reserved.
//*********************************************************
#include <iframe.hpp>
#include <iapp.hpp>
#include <ipushbut.hpp>
#include <iradiobt.hpp>
#include "lunchdlg.h"

void main ( )
{
  IFrameWindow
    lunch( ID_LUNCH_DIALOG );

  // Initialize the dialog controls.
  IRadioButton
    hamburger( ID_HAMBURGER, &lunch );
  hamburger
   .select()
   .setFocus();
  IRadioButton
    milk( ID_MILK, &lunch );
  milk
   .select();

  lunch
   .show();

  IApplication::current().run();
}
