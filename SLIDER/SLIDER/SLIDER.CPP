//*********************************************************
// Sliders - Linear Slider Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//*********************************************************
#include <iapp.hpp>
#include "tempview.hpp"

void main ( )
{
  // Create the temperature view window.
  TemperatureView
    mainWindow( "Farenheit Temperature Slider" );

  //  Give the window the focus and show it.
  mainWindow
   .setFocus()
   .show();

  IApplication::current().run();
} 
