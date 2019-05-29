//************************************************************
// Container Control - Dynamic Creation Of Objects
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************

#include <iapp.hpp>
#include <iframe.hpp>
#include <icnrctl.hpp>
#include <icnrcol.hpp>
#include "table.hpp"

void main( )
{

IFrameWindow cnrFrame("Dynamic Creation of Objects");

IContainerControl cnr(0x101,
                      &cnrFrame,
                      &cnrFrame);

// Size the frame & put container in client area
cnrFrame
  .setClient(&cnr)
  .sizeTo(ISize(450,200));


// Create a TableObject with 3 fields.
TableObject::setFieldCount(3);
TableObject* pobject = new TableObject;
pobject->setFieldText("John Doe", 0);
pobject->setFieldText("Anywhere USA", 1);
pobject->setFieldText("Hacker", 2);
pobject->enableDataUpdate();
cnr.addObject(pobject);

// Setup the text for the column headings.
TableObject::setHeadingText("Name", 0);
TableObject::setHeadingText("Address", 1);
TableObject::setHeadingText("Occupation", 2);

// Create and add the columns to the container.
pobject->createAllColumnsFor(cnr);

// Show the details view
cnr.showDetailsView();

// Set the focus and show the window
cnrFrame
 .setFocus()
 .show();

IApplication::current().run();
}


