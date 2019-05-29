#ifndef _DEVMODEL_
#define _DEVMODEL_
//************************************************************
// Container Control - Help in the Container                    
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <icnrobj.hpp>
#include <istring.hpp>

class Developer : public IContainerObject
{
public:
 Developer    ( const IString& name,
                const IString& compuServeId,
                unsigned long  age);

IString
  name                  ( ) const,
  address               ( ) const,
  age                   ( ) const;

Developer
 &setHelpId            ( unsigned long helpId);

virtual unsigned long
  helpId               ( ) const;


// Column support
enum Column 
{ kNameColumn, 
  kCompuServeIdColumn,
  kAgeColumn
};
static IContainerColumn
 *createAndOrphanColumnFor ( IContainerControl& container,
                             Column             column);
static void
  createAllColumnsFor      ( IContainerControl&  container);

private:
IString
  fCompuServeId,
  fAge;
unsigned long
  fHelpId;
};
#endif // _DEVMODEL_
