#ifndef _TABLE_
#define _TABLE_
//************************************************************
// Container Control - Dynamic Creation Of Objects
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <icnrobj.hpp>
#include <istring.hpp>

class IContainerColumn;
class IContainerControl;

class TableObject : public IContainerObject
{
public:
  TableObject      ( );
  TableObject      ( TableObject&  objectToCopy);
    ~TableObject   ( );

void
 *operator new     ( size_t        size);

IContainerObject
 *objectCopy       ( );

TableObject
 &setFieldText     ( const IString& fieldText,
                     unsigned long  fieldIndex);
IString
  fieldText        ( unsigned long fieldIndex) const;

static void
  setFieldCount    ( unsigned long fieldCount);
static unsigned long
  fieldCount       ( );

static void
  setHeadingText   ( const IString& headingText,
                     unsigned long  headingIndex);
static IString
  headingText      ( unsigned long  headingIndex);


IContainerColumn
 *createAndOrphanColumnFor ( IContainerControl& container,
                             unsigned long      fieldNumber);
void
  createAllColumnsFor      ( IContainerControl&  container);


private:

static unsigned long
  fgFieldCount;
IString
  fFieldArray[1];
};

#endif // _TABLE_
