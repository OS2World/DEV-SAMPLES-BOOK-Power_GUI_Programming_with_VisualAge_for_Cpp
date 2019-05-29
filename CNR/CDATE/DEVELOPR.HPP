#ifndef _DEVELOPR_
#define _DEVELOPR_
//************************************************************
// Container Control - Dates and Times as CDATE/CTIME         
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <iframe.hpp>
#include <icnrctl.hpp>
#include <icnrcol.hpp>
#include <icnrobj.hpp>

#pragma pack(4)
struct CDATE    
{
   CDATE(unsigned char  aDay = 10,
         unsigned char  aMonth =1,
         unsigned short aYear  =1950)
      : day(aDay),
        month(aMonth),
        year(aYear) {}

   unsigned char   day;   
   unsigned char   month; 
   unsigned short  year;  
};

struct CTIME
{
   CTIME(unsigned char anHour = 17,
         unsigned char aMinute = 0,
         unsigned char aSecond = 0)
      : hours(anHour),
        minutes(aMinute),
        seconds(aSecond) {}

   unsigned char   hours; 
   unsigned char   minutes; 
   unsigned char   seconds; 
   unsigned char   ucReserved;  
};
#pragma pack()

class Developer : public IContainerObject
{
  public:
  Developer   ( IString       name,
                unsigned long iconId,
                IString       compuServeId = IString("?"),
                IString       age = IString("?"),
                const CDATE&  birthDate =CDATE(),
                const CTIME&  quittingTime=CTIME())
     : IContainerObject(name, iconId),
       fCompuServeId(compuServeId),
       fAge(age),
       fBirthDate(birthDate),
       fQuittingTime(quittingTime)
 
 {}

// Column functions
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
  fAge;
CDATE
  fBirthDate;
CTIME
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