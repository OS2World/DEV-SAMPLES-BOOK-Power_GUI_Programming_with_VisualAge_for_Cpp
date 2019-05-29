//************************************************************
// Container - Combined Tree and Details View
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <icnrcol.hpp>
#include <icnrctl.hpp>
#include <iexcept.hpp>
#include <iapp.hpp>
#include "partobj.hpp"

const IString fgNoYes[2] = {"Yes", "No"};
IString ExecutablePart::fgNameHeading("Name");
IString ExecutablePart::fgTraceableHeading("Traceable");
IString ExecutablePart::fgEnabledPartHeading("Enabled");
IString ExecutablePart::fgGeneratesTraceHeading("Generates Trace");
IString ExecutablePart::fgContainsTriggerHeading("Contains Trigger");

ExecutablePart ::  ExecutablePart   ( IString       name,
                                      Boolean  isTraceAble,
                                      Boolean  isEnabledPart,
                                      Boolean  willGenerateTrace,
                                      Boolean  hasTrigger)
                         : IContainerObject(name),
                           fTraceable(""),
                           fEnabledPart(""),
                           fGeneratesTrace(""),
                           fContainsTrigger("")
 
{
setTraceAble(isTraceAble);
setEnabledPart(isEnabledPart);
setGenerateTrace(willGenerateTrace);
setTrigger(hasTrigger);
enableDataUpdate();
}

ExecutablePart& ExecutablePart :: setTraceAble     ( Boolean traceAble )
{
   this->fTraceable = fgNoYes[traceAble];
   return *this;
}

ExecutablePart& ExecutablePart :: setEnabledPart   ( Boolean enabledPart )
{
   this->fEnabledPart = fgNoYes[enabledPart];
   return *this;
}

ExecutablePart& ExecutablePart :: setGenerateTrace ( Boolean generateTrace )
{
   this->fGeneratesTrace = fgNoYes[generateTrace];
   return *this;
}

ExecutablePart& ExecutablePart :: setTrigger       ( Boolean containsTrigger)
{
   this->fContainsTrigger = fgNoYes[containsTrigger];
   return *this;
}

Boolean ExecutablePart :: isTraceAble ( ) const
{
  if (this->fTraceable == fgNoYes[true])
     return true;
  else
     return false;
}

Boolean ExecutablePart :: isEnabledPart ( ) const
{
  if (this->fEnabledPart == fgNoYes[true])
     return true;
  else
     return false;
}

Boolean ExecutablePart :: willGenerateTrace ( ) const
{
  if (this->fGeneratesTrace == fgNoYes[true])
     return true;
  else
     return false;
}

Boolean ExecutablePart :: hasTrigger ( ) const
{
  if (this->fContainsTrigger == fgNoYes[true])
     return true;
  else
     return false;
}

void ExecutablePart::setHeadingText( const IString& headingText, 
                                      Column         column)
{
  switch (column) {
    case   ExecutablePart::kNameColumn              :
      fgNameHeading = headingText;
      break;
    case   ExecutablePart::kTraceableColumn         :
      fgTraceableHeading = headingText;
      break;
    case    ExecutablePart::kEnabledPartColumn      :
      fgEnabledPartHeading = headingText;
      break;
    case    ExecutablePart::kGeneratesTraceColumn   :
      fgGeneratesTraceHeading = headingText;
      break;
    case    ExecutablePart::kContainsTriggerColumn  :
      fgContainsTriggerHeading = headingText;
      break;
    default:
      break;
  } /* endswitch */
}
IString ExecutablePart::headingText( Column         column)
{
  IString heading;
  switch (column) {
    case    ExecutablePart::kNameColumn            :
      heading = fgNameHeading;
      break;
    case    ExecutablePart::kTraceableColumn       :
      heading = fgTraceableHeading;
      break;
    case    ExecutablePart::kEnabledPartColumn     :
      heading = fgEnabledPartHeading;
      break;
    case    ExecutablePart::kGeneratesTraceColumn  :
      heading = fgGeneratesTraceHeading;
      break;
    case    ExecutablePart::kContainsTriggerColumn :
      heading = fgContainsTriggerHeading;
      break;
    default:
      break;
  } /* endswitch */

  return heading;
}


void ExecutablePart::createAllColumnsFor ( IContainerControl&  container)
{
 createAndOrphanColumnFor( container, kNameColumn);
 createAndOrphanColumnFor( container, kTraceableColumn);
 createAndOrphanColumnFor( container, kEnabledPartColumn);
 createAndOrphanColumnFor( container, kGeneratesTraceColumn);
 createAndOrphanColumnFor( container, kContainsTriggerColumn);

 container.setDeleteColumnsOnClose();
}

IContainerColumn* ExecutablePart::createAndOrphanColumnFor ( 
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

  if (columnType == ExecutablePart::kNameColumn)
  {
    newColumn = new IContainerColumn(IContainerColumn::isIconViewText,
                                     headingStyle,
                                     dataStyle);
    headingText = fgNameHeading;
    editable = true;
  }
  else if (columnType == ExecutablePart::kTraceableColumn)
  {
    offset = offsetof(ExecutablePart, fTraceable);
    headingText = fgTraceableHeading;
    editable = true;
  }
  else if (columnType == ExecutablePart::kEnabledPartColumn)
  {
    offset = offsetof(ExecutablePart, fEnabledPart);
    headingText = fgEnabledPartHeading;
    editable = true;
  }
  else if (columnType == ExecutablePart::kGeneratesTraceColumn)
  {
    offset = offsetof(ExecutablePart, fGeneratesTrace);
    headingText = fgGeneratesTraceHeading;
    editable = true;
  }
  else if (columnType == ExecutablePart::kContainsTriggerColumn)
  {
    offset = offsetof(ExecutablePart, fContainsTrigger);
    headingText = fgContainsTriggerHeading;
    editable = true;
  }
  
  if (newColumn == 0 && offset < invalidOffset )
    newColumn = new IContainerColumn(offset,
                                     headingStyle,
                                     dataStyle);
  newColumn->showSeparators(IContainerColumn::horizontalSeparator);

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