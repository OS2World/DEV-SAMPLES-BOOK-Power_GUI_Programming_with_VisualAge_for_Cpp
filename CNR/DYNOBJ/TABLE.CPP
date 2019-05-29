//************************************************************
// Container Control - Dynamic Creation Of Objects
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <ipoint.hpp>
#include <istring.hpp>
#include <iexcept.hpp>
#include <icnrcol.hpp>
#include <icnrctl.hpp>
#include <new.h>
#include "table.hpp"

unsigned long TableObject::fgFieldCount = 0;
IString* TableObject__headingList = 0;

// Primary Constructor
TableObject::TableObject( )
             : IContainerObject(0)
{
  IASSERTSTATE(TableObject::fgFieldCount != 0)
   // Call global operator new using placement syntax.
   // This does not allocate any storage, but
   // the constructor gets called.
   for(unsigned long s=1; s<fgFieldCount; s++)
   {
        new(&fFieldArray[s]) IString();
   }
}

// Copy Constructor
TableObject::TableObject(TableObject& oldObject)
                  : IContainerObject (oldObject)
{
   fgFieldCount = oldObject.fgFieldCount;
   unsigned long s;
   // Call global operator new using placement syntax.
   for(s=1; s<fgFieldCount; s++)
   {
       new (this->fFieldArray+s) IString(oldObject.fFieldArray[s]);
   }

}

// The objectCopy functions is required to support
// direct manipulation copy operations.
IContainerObject* TableObject::objectCopy()
{
   TableObject* pObject = new TableObject(*this);
   return (IContainerObject*)pObject;
}

// Operator new for variable number of fields.
void* TableObject :: operator new(size_t        size)
{
  void* tableObject = IContainerObject::operator new( size +
                     (size_t)fgFieldCount*sizeof(IString));
  return(tableObject);
}

// Destructor
TableObject::~TableObject()
{
   // Because the first field is handled by destruction
   // of the IString array, we delete from the
   // second IString. Note that we are explicitly
   // calling the destructor because we don't want any
   // storage freed.
   unsigned long s;
   for(s=1; s<this->fgFieldCount; s++)
  {
      this->fFieldArray[s].~IString();
  }
}


// Sets new text into a field at the specified index.
TableObject& TableObject::setFieldText(const IString& strText,
                                  unsigned long fieldIndex)
{
  IASSERTPARM(fieldIndex < fgFieldCount)
  if (fieldIndex < fgFieldCount)
  {
    fFieldArray[fieldIndex] = strText;
  }
  return *this;
}

// Returns the text at a field index.
IString TableObject::fieldText( unsigned long fieldIndex) const
{
  return this->fFieldArray[fieldIndex];
}


void TableObject::setFieldCount( unsigned long fieldCount)
{
  fgFieldCount = fieldCount;
}

unsigned long TableObject::fieldCount ( )
{
   return fgFieldCount;
}

void TableObject::setHeadingText( const IString& headingText,
                                  unsigned long  headingIndex)
{
  // For simplicity, we only support 50 Headings
  if (TableObject__headingList == 0) 
    TableObject__headingList = new IString[50];

  TableObject__headingList[headingIndex] = headingText;
}

IString TableObject::headingText ( unsigned long  headingIndex)
{
   return TableObject__headingList[headingIndex];
}


void TableObject::createAllColumnsFor ( IContainerControl&  container)
{

  for (unsigned long s=0; s<fgFieldCount; s++ ) {
    createAndOrphanColumnFor( container, s);
  }

  container.setDeleteColumnsOnClose();
}


IContainerColumn* TableObject::createAndOrphanColumnFor ( 
                             IContainerControl& container,
                             unsigned long      fieldNumber)
{
  // Set up a default column.
  unsigned long offset = offsetof(TableObject,fFieldArray[0])
     + fieldNumber*(sizeof(IString));

  IContainerColumn*  newColumn = new IContainerColumn(offset);

  // Ensure that a new column has been created.
  IASSERTSTATE(newColumn != 0)

  // Put the text in the heading and make it editable.
  newColumn->setHeadingText(headingText(fieldNumber));
  newColumn->enableDataUpdate();

  // Add the column to the container.
  container.addColumn( newColumn);

  return newColumn;
}

