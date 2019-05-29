//************************************************************
// Container Control - Name View
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <iframe.hpp>
#include <icnrctl.hpp>
#include <iapp.hpp>
#include "nameview.h"

void main ()
{

// Create the frame window with the container in the
// client area.
IFrameWindow cnrFrame("Container Name View");
IContainerControl cnr(0x101,
                      &cnrFrame,
                      &cnrFrame);
cnrFrame.setClient(&cnr);


// Create the objects with text and an icon.
IContainerObject* obj1 = new
               IContainerObject("Object 1",  ICON_FOLDER);
IContainerObject* obj2 = new
               IContainerObject("Object 2", ICON_FOLDER);

// Add the objects to the container.
cnr.addObject(obj1);
cnr.addObject(obj2);

// Show the objects in the name view.
cnr.showNameView();

// Give focus to the frame and show it.
cnrFrame.show();
cnrFrame.setFocus();

IApplication::current().run();
}
