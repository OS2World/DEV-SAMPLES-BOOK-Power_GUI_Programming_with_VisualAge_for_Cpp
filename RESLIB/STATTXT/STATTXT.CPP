//************************************************************
// Using Resources - Switching Resources Dynamically
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <iframe.hpp>
#include <iapp.hpp>
#include <istattxt.hpp>
#include "mytext.h"

void main()
{
   // Store the location of our resources from MYENG.DLL
   // in the application framework.
   IApplication::current()
     .setUserResourceLibrary("myeng");

   // Create a frame and a text field for the client.
   IFrameWindow frame("Text from a Resource File");
   IStaticText text(100, &frame, &frame);

   // Align and add the text from a resource.
   text
     .setAlignment(IStaticText::centerCenter)
     .setText(MY_TEXT);

   // Put the text in the client and show the window.
   frame
     .setClient(&text)
     .setFocus()
     .show();

   // Run the application.
   IApplication::current().run();
}
