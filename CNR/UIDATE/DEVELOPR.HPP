#ifndef _DEVELOPR_
#define _DEVELOPR_
//************************************************************
// Container Control - Dates and Times as IDate/ITime        
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <iframe.hpp>
#include <icnrctl.hpp>
#include <icnrcol.hpp>
#include <icnrobj.hpp>
#include <idate.hpp>
#include <itime.hpp>

class Developer : public IContainerObject
{
  public:
  Developer   ( IString       name,
                unsigned long iconId,
                IString       compuServeId = IString("?"),
                IString       age = IString("?"),
                const IDate&  birthDate =IDate(),
                const ITime&  quittingTime=ITime())
     : IContainerObject(name, iconId),
       fCompuServeId(compuServeId),
       fAge(age),
       fBirthDate(birthDate.asString()),
       fQuittingTime(quittingTime.asString())
 {}
// Column Creation.
enum Column 
{ kNameColumn, 
  kIconColumn, 
  kCompuServeIdColumn,
  kAgeColumn,
  kBirthDateColumn,
  kQuittingTimeColumn
};
static IContainerColumn
 *createAndOrphanColumnFor ( IContainerControl& container,
                             Column             column);
static void
  createAllColumnsFor      ( IContainerControl&  container);

private:

IString
  fCompuServeId,
  fAge,
  fBirthDate,
  fQuittingTime;

};


class DeveloperList : public IFrameWindow {
public:

  DeveloperList ( const char* title);

IContainerControl
 &container        ( );

private:
IContainerControl
  cnrctl;
DeveloperList& operator=(const DeveloperList&);
DeveloperList(const DeveloperList&);
};

#endif // _DEVELOPR_
