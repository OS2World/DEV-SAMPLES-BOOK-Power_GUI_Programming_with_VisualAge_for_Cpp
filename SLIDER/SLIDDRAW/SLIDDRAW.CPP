//*********************************************************
// Sliders - Progress Indicator Custom Painting Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//*********************************************************
#include <iapp.hpp>
#include <islider.hpp>
#include "taskview.hpp"

void main ( )
{
#ifdef IC_WIN
  IProgressIndicator::setDefaultStyle( IProgressIndicator::defaultStyle()
                                        | IProgressIndicator::pmCompatible );
#endif

  // Create the status view window.
  TaskStatusView
    mainWindow( "Progress Indicator Custom Drawing");

  // Give the window the focus and show it.
  mainWindow
   .setFocus()
   .show();

  IApplication::current().run();
}
