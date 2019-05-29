//************************************************************
// Container Control - Spreadsheet Behavior
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <iapp.hpp>
#include <iframe.hpp>
#include <ipoint.hpp>
#include <icnrctl.hpp>
#include <icnrcol.hpp>
#include <icnrhdr.hpp>
#include <icnrehdr.hpp>
#include <new.h>
#include "table.hpp"
#include "sprdhdr.hpp"

void main()
{

IFrameWindow cnrFrame("Container SpreadSheet View");
cnrFrame.sizeTo(ISize(450,200));

IContainerControl cnr(0x101,
                      &cnrFrame,
                      &cnrFrame);

// Put container in client area
cnrFrame.setClient(&cnr);



// Create a bunch of Table Objects with columnCount fields
TableObject::setFieldCount(10);
int obj, col;
IString objectName;
TableObject* pobject = 0;
for (obj=0; obj<50;obj++ ) {
  pobject = new TableObject;
  cnr.addObject(pobject);
  for (col=0; col<TableObject::fieldCount(); col++ ) {
     pobject->setFieldText(IString("Obj: ") + IString(obj) +
                IString(" Col: ") + IString(col),col);
     pobject->enableDataUpdate();
     // Add the heading text when building the first object.
     if (obj==0) 
        pobject->setHeadingText(IString("Column ") + IString(col), col);
  } /* endfor */
} /* endfor */


// Create the container columns for all fields.
pobject->createAllColumnsFor(cnr);

cnr.setDeleteObjectsOnClose();

// Create Container EditHandler.
// Create a Default Handler for the Container Edit Field
// and energize it.
ICnrEditHandler* pcnrEdit = new ICnrEditHandler();
pcnrEdit->handleEventsFor(&cnr);

// Create the default ContainerHandler.
ICnrHandler* pcnrHandler = new ICnrHandler();
pcnrHandler->handleEventsFor(&cnr);

// Create Our Handler for Tabbing the Container.
CnrSpreadSheetHandler* psprdHandler= new CnrSpreadSheetHandler(cnr);
psprdHandler->handleEventsFor(&cnr);

// Show the details view.
cnr.showDetailsView();

cnrFrame.show();
cnrFrame.setFocus();

IApplication::current().run();
}
