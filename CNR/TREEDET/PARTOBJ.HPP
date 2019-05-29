#ifndef _PARTOBJ_
#define _PARTOBJ_
//************************************************************
// Container - Combined Tree and Details View
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <icnrobj.hpp>
#include <istring.hpp>
#include <stddef.h>

class ExecutablePart : public IContainerObject
{
public:
  ExecutablePart   ( IString  partName,
                     Boolean  isTraceAble = true,
                     Boolean  isEnabledPart = false,
                     Boolean  willGenerateTrace = true,
                     Boolean  hasTrigger = false);

ExecutablePart
 &setTraceAble     ( Boolean traceAble      = true),
 &setEnabledPart   ( Boolean enabled        = true),
 &setGenerateTrace ( Boolean generateTrace  = true),
 &setTrigger       ( Boolean triggerOn      = true);

Boolean
 isTraceAble       ( ) const,
 isEnabledPart     ( ) const,
 willGenerateTrace ( ) const,
 hasTrigger        ( ) const;

// Column Creation.
enum Column 
{ kNameColumn,
  kTraceableColumn, 
  kEnabledPartColumn, 
  kGeneratesTraceColumn,
  kContainsTriggerColumn
};
static IContainerColumn
 *createAndOrphanColumnFor ( IContainerControl& container,
                             Column             column);
static void
  createAllColumnsFor      ( IContainerControl&  container);

static void
  setHeadingText           ( const IString& headingText, 
                             Column         column);
static IString
  headingText              ( Column         column);

private:

IString
  fTraceable,
  fEnabledPart,
  fGeneratesTrace,
  fContainsTrigger;
static IString
  fgNameHeading,
  fgTraceableHeading,
  fgEnabledPartHeading,
  fgGeneratesTraceHeading,
  fgContainsTriggerHeading;
};


#endif // _PARTOBJ_
