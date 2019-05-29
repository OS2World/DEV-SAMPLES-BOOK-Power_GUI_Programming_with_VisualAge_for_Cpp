//************************************************************
// Container Control - Help in the Container
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <stddef.h>
#include <icnrctl.hpp>
#include <icnrcol.hpp>
#include <iexcept.hpp>
#include "devmodel.hpp"

Developer::Developer   ( const IString&      name,
                         const IString&      compuServeId,
                         unsigned long age)
     : IContainerObject(name),
       fCompuServeId(compuServeId),
       fAge(age)

{}

IString Developer:: name ( ) const
{ 
  return iconText();
}

IString Developer:: address ( ) const
{ 
  return fCompuServeId;
}

IString Developer:: age ( ) const
{ 
  return fAge;
}


Developer& Developer::setHelpId ( unsigned long helpId)
{ 
  fHelpId = helpId;
  return *this;
}


unsigned long Developer::helpId ( ) const
{ 
  return fHelpId;
}



void Developer::createAllColumnsFor ( IContainerControl&  container)
{
 createAndOrphanColumnFor( container, Developer::kNameColumn);
 createAndOrphanColumnFor( container, Developer::kCompuServeIdColumn);
 createAndOrphanColumnFor( container, Developer::kAgeColumn);

 container.setDeleteColumnsOnClose();
}


IContainerColumn* Developer::createAndOrphanColumnFor ( 
                             IContainerControl& container,
                             Column             columnType)
{
  // Setup a default Column.
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
    headingText = "Developer Name";
    editable = true;
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
  
  if (newColumn == 0 && offset < invalidOffset )
    newColumn = new IContainerColumn(offset,
                                     headingStyle,
                                     dataStyle);

  // Insure that a new column has been created.
  IASSERTSTATE(newColumn != 0)

  newColumn->setHeadingText(headingText);

  if (editable == true) 
    newColumn->enableDataUpdate();

  // Add the column to the container.
  container.addColumn( newColumn);

  return newColumn;
}



