//************************************************************
// Notebook Control - Simple Notebook Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <inotebk.hpp>
#include <iframe.hpp>
#include <iapp.hpp>
#include <icconst.h>

void main()
{
  IFrameWindow frame ("Simple Notebook");
  INotebook notebook (IC_FRAME_CLIENT_ID, &frame, &frame);

  frame
    .setClient(&notebook)
    .setFocus()
    .show();
  IApplication::current().run();
}

