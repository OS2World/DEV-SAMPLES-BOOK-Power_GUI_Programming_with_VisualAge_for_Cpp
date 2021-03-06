//************************************************************
// Container Control - Mini-icon Container
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************

#include <iframe.hpp>
#include <icnrctl.hpp>
#include <iapp.hpp>
// #include "cnrmini.hpp"
#include "minicnr.h"

void main ()
{

IFrameWindow cnrFrame("Mini-Icon Container");
cnrFrame.sizeTo(ISize(200,200));

IContainerControl cnr(0x101,
                      &cnrFrame,
                      &cnrFrame);

// Put container in client area.
cnrFrame.setClient(&cnr);

// Create an object.
IContainerObject* folder = new
            IContainerObject(IString("Folder "),
            ICON_FOLDER);
cnr.addObject(folder);

cnr.arrangeIconView();

// Show Icon view.
cnr.showIconView();
cnr.showMiniIcons();

cnrFrame.show();
cnrFrame.setFocus();

IApplication::current().run();
}
