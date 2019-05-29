/************************************************************
/ List Controls - Spin Button Date Control
/
/ Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
/ Copyright (c) 1997 John Wiley & Sons, Inc.
/ All Rights Reserved.
************************************************************/
#include <istring.hpp>
#include <ispintxt.hpp>
#include <ispinnum.hpp>
#include <ispinhdr.hpp>
#include "datectrl.hpp"

class DateSpinHandler : public ISpinHandler
{
public:
  DateSpinHandler ( ITextSpinButton& month,
                    INumericSpinButton& day,
                    INumericSpinButton& year )
       : _month(&month), _day(&day), _year(&year) {}

ITextSpinButton
 &month  (  )   { return *_month;}
INumericSpinButton
 &day    (  )   { return *_day;}
INumericSpinButton
 &year    (  )  { return *_year;}

protected:
virtual Boolean
  arrowUp              ( IControlEvent& event ),
  arrowDown            ( IControlEvent& event ),
  dayChanged           ( Boolean        forward ),
  monthChanged         ( Boolean        forward );

DateSpinHandler
 &updateMonth          ( Boolean forward );

unsigned long
  daysInMonth          ( ) const;

private:
ITextSpinButton
 *_month;
INumericSpinButton
 *_day,
 *_year;
};

ITextSpinButton& DateControl::month(  )
{ return *_month;}

INumericSpinButton& DateControl::day(  )
{ return *_day;}

INumericSpinButton& DateControl::year(  )
{ return *_year;}


DateControl::DateControl ( unsigned long id,
                           IWindow*      parent,
                           IWindow*      owner,
                           const IDate& aDate,
                           const IRange& aYearRange)
      : IMultiCellCanvas(id, parent, owner),
        _month     ( new ITextSpinButton(id + 4, this, this,
                       IRectangle(),
                       IBaseSpinButton::servant |
                       IBaseSpinButton::rightAlign |
                       IWindow::visible)),
        _day       ( new INumericSpinButton(id + 5, this, this,
                       IRectangle(),
                       IBaseSpinButton::servant |
                       IBaseSpinButton::rightAlign |
                       IWindow::visible)),
        _year      ( new INumericSpinButton(id + 6, this, this,
                       IRectangle(),
                       IBaseSpinButton::master |
                       IBaseSpinButton::rightAlign |
                       IWindow::visible)),
        _spinHandler(new DateSpinHandler(*_month, *_day, *_year))
{


(*this)
  .addToCell( _month,      2, 2)
  .addToCell( _day,        4, 2)
  .addToCell( _year,       6, 2)
  .setColumnWidth(1, 1, true)
  .setColumnWidth(3, 2, false)
  .setColumnWidth(5, 2, false)
  .setColumnWidth(7, 1, true)
  .setRowHeight  (1, 1, true)
  .setRowHeight  (3, 1, true);

year()
  .setRange(aYearRange)
  .setLimit(4);
year()
  .spinTo(aDate.year());

// Load the Month spin button
for (int i=1;
     i < 13;
     i++)
{
   month().addAsLast(IDate::monthName((IDate::Month)i));
}

month()
  .setMaster(year());
#ifdef IC_PM
// Disabled until setLimit fixed.
month()
  .setLimit(12);
#else
#if IC_MAJOR_VERSION > 320 || IC_MINOR_VERSION >= 3
month()
  .setLimit(12);
#endif
#endif
month()
  .setText(aDate.monthName());

day()
  .setRange(IRange(1,32))
  .setMaster(year())
  .setLimit(2);
day()
  .spinTo(aDate.dayOfMonth());

// Start the spin handler on the canvas
(*_spinHandler)
  .handleEventsFor(this);
}

IString DateControl::dateAsString ( ) const
{
  IString str= _month->text()+" "+IString(_day->value())+", "+
               IString(_year->value());
  return str;
}


IBase::Boolean DateSpinHandler::arrowUp( IControlEvent& event )
{
   IBaseSpinButton* spin = (IBaseSpinButton*)(event.controlWindow());
   if (spin)
   {
      if  (spin->handle()==day().handle())
         return dayChanged(true);
      else if  (spin->handle()==month().handle())
         return monthChanged(true);
   }
   return false;
}

IBase::Boolean DateSpinHandler::arrowDown( IControlEvent& event )
{
   IBaseSpinButton* spin = (IBaseSpinButton*)(event.controlWindow());
   if (spin)
   {
      if  (spin->handle()==day().handle())
         return dayChanged(false);
      else if  (spin->handle()==month().handle())
         return monthChanged(false);
   }
  return false;
}

// Handle a Month change - update the year if necessary
IBase::Boolean DateSpinHandler::monthChanged( Boolean forward)
{
  IString contents = month().text();
  if (forward  &&
      contents == IDate::monthName(IDate::January))
  {
     year().setValue(year().value() + 1);
  }
  else if (!forward)
  {
     if(day().value() > daysInMonth())
       day().setValue(daysInMonth());
     if(contents == IDate::monthName(IDate::December))
       year().setValue(year().value() - 1);
  }
  return true;

}

// Handle a day change - update the month if necessary
IBase::Boolean DateSpinHandler::dayChanged( Boolean forward)
{
  unsigned long contents = day().value();
  if ( forward  && contents > daysInMonth())
  {
     updateMonth(true);
     day().setValue(1);
     return true;
  }
  else if ( !forward &&
            contents == day().range().upperBound())
  {
    updateMonth(false);
    day().setValue(daysInMonth());
    return true;
  }
  return false;
}

// Roll the spin buttons month forward one month or
// backward one month
DateSpinHandler& DateSpinHandler::updateMonth ( Boolean forward)
{
  unsigned newMonth;
  for (unsigned i=1; i<13; i++)
  {
    if (month().text() == IDate::monthName((IDate::Month)i))
    {
      if(forward)
         newMonth = (i<12)? i+1 : 1;
      else
         newMonth = (i>1)? i-1 : 12;
      month().setText(IDate::monthName(IDate::Month(newMonth)));
      if(forward && newMonth == 1)
        year().setValue(year().value() + 1);
      if(!forward && newMonth == 12)
        year().setValue(year().value() - 1);

      break;
    }
  }
  return *this;
}

// Compute the days in the Spin Buttons month
unsigned long DateSpinHandler::daysInMonth ( ) const
{
  for (int i=1; i<13; i++)
  {
    if (((DateSpinHandler*)this)->month().text() ==
                   IDate::monthName((IDate::Month)i))
    {
       return IDate::daysInMonth((IDate::Month)i,
                   ((DateSpinHandler*)this)->year().value());
    }
  }
  return 0;
}
