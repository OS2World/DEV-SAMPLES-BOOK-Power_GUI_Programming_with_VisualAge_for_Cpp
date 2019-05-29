//************************************************************
// Container Control - Dates and Times as CDATE/CTIME         
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <iframe.hpp>
#include <ictlevt.hpp>
#include <iexcept.hpp>
#include <stddef.h>
#include "developr.h"
#include "developr.hpp"

DeveloperList :: DeveloperList ( const char* title)
                   : IFrameWindow (title, DEVELOPER_WINDOW),
                     cnrctl( DEVELOPER_CONTAINER, this, this)
 
{

// Put the container in the client area.
setClient(&container());

Developer::createAllColumnsFor(cnrctl);

// Create and add the objects to the container.
Developer* developer;
CDATE bDate(27,6,1953);
CTIME qTime(3);

developer = new Developer("Joe Programmer",
                          ID_DEVELOPER,
                          "12345,6789",
                          "38");
container().addObject(developer);
container().enableDataUpdate(developer);

container().setDeleteColumnsOnClose();
container().setDeleteObjectsOnClose();
container().showSplitBar();
}

IContainerControl& DeveloperList :: container( ) { 
  return cnrctl;
}

void Developer::createAllColumnsFor ( IContainerControl&  container)
{
 IContainerColumn* newColumn;

 newColumn = createAndOrphanColumnFor( container, Developer::kIconColumn);
 newColumn = createAndOrphanColumnFor( container, Developer::kNameColumn);
 container.setDetailsViewSplit(newColumn, 125);
 newColumn = createAndOrphanColumnFor( container, Developer::kCompuServeIdColumn);
 newColumn = createAndOrphanColumnFor( container, Developer::kAgeColumn);
 newColumn = createAndOrphanColumnFor( container, Developer::kBirthDateColumn);
 newColumn = createAndOrphanColumnFor( container, Developer::kQuittingTimeColumn);

 container.setDeleteColumnsOnClose();
}


IContainerColumn* Developer::createAndOrphanColumnFor ( 
                             IContainerControl& container,
                             Column             columnType)
{
  // Set up a default column.
  IContainerColumn* newColumn = 0;
  IString headingText;
  Boolean editable = false;
  const unsigned long invalidOffset = (unsigned long)-1;
  unsigned long offset = invalidOffset;
  IContainerColumn::HeadingStyle headingStyle = IContainerColumn::defaultHeadingStyle();
  IContainerColumn::DataStyle dataStyle = IContainerColumn::defaultDataStyle();

  if (columnType == Developer::kNameColumn)
  {
    newColumn = new IContainerColumn(IContainerColumn::isIconViewText,
                                     headingStyle,
                                     dataStyle);
    headingText = "Name";
    editable = true;
  }
  else if (columnType == Developer::kIconColumn)
  {
    newColumn = new IContainerColumn(IContainerColumn::isIcon,
                                     headingStyle,
                                     dataStyle);
    headingText = "Role";
  }
  else if (columnType == Developer::kCompuServeIdColumn)
  {
    offset = offsetof(Developer, fCompuServeId);
    headingText = "CompuServe Id";
    editable = true;
  }
  else if (columnType == Developer::kAgeColumn)
  {
    offset = offsetof(Developer, fAge);
    headingText = "Age";
    editable = true;
  }
  else if (columnType == Developer::kBirthDateColumn)
  {
    offset = offsetof(Developer, fBirthDate);
    dataStyle = IContainerColumn::date;
    headingText = "Birth Date";
  }
  else if (columnType == Developer::kQuittingTimeColumn)
  {
    offset = offsetof(Developer, fQuittingTime);
    dataStyle = IContainerColumn::time;
    headingText = "Quitting Time";
  }
  
  if (newColumn == 0 && offset < invalidOffset )
    newColumn = new IContainerColumn(offset,
                                     headingStyle,
                                     dataStyle);

  // Ensure that a new column has been created.
  IASSERTSTATE(newColumn != 0)

  newColumn->setHeadingText(headingText);

  if (editable == true) 
    newColumn->enableDataUpdate();

  // Add the column to the container.
  container.addColumn( newColumn);

  return newColumn;
}
