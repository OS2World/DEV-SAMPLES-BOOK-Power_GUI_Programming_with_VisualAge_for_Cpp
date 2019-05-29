//************************************************************
// Container Control - Pop Up Menu Example 
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <iframe.hpp>
#include <icnrctl.hpp>
#include <icnrcol.hpp>
#include <icnrobj.hpp>
#include <icnrmhdr.hpp>
#include <ipopmenu.hpp>
#include <ictlevt.hpp>
#include <iapp.hpp>
#include <itrace.hpp>
#include <iexcept.hpp>
#include <stddef.h>
#include "popup.h"

class Developer : public IContainerObject
{
  public:
  Developer   ( IString       name,
                unsigned long iconId,
                IString       compuServeId,
                unsigned long age)
     : IContainerObject(name, iconId),
       fCompuServeId(compuServeId),
       fAge(age)
 
 {}

// Column functions
enum Column 
{ kNameColumn, 
  kIconColumn, 
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
  fCompuServeId;
unsigned long
  fAge;
};


class DeveloperMenuHandler : public ICnrMenuHandler
{

protected:

virtual Boolean
 makePopUpMenu(IMenuEvent& mnEvt);

};

void main ()
{

// Create a frame with a container as the client.
IFrameWindow cnrFrame("Container Pop-up Menu Example");
IContainerControl cnr(0x101,        
                      &cnrFrame,    
                      &cnrFrame);
cnrFrame.setClient(&cnr);

// Create the columns for the details view.
Developer::createAllColumnsFor(cnr);

// Create and add the objects to the container.
Developer* developer;
developer = new Developer("Joe South", 
                          ICON_FOLDER,  
                          "12345,6789",
                          38);
cnr.addObject(developer);
developer = new Developer("Silly Sally",
                          ICON_FOLDER,  
                          "98765,4321",
                          40);
cnr.addObject(developer);


//Create a container MenuHandler.
DeveloperMenuHandler* pmenu = new DeveloperMenuHandler();
pmenu->handleEventsFor(&cnr);

// Show the details view.
cnr.showDetailsView();

cnrFrame.show();
cnrFrame.setFocus();

IApplication::current().run();
}


void Developer::createAllColumnsFor ( IContainerControl&  container)
{
 IContainerColumn* newColumn;

 newColumn = createAndOrphanColumnFor( container, Developer::kIconColumn);
 newColumn = createAndOrphanColumnFor( container, Developer::kNameColumn);
 container.setDetailsViewSplit(newColumn, 125);
 newColumn = createAndOrphanColumnFor( container, Developer::kCompuServeIdColumn);
 newColumn = createAndOrphanColumnFor( container, Developer::kAgeColumn);

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
    dataStyle = IContainerColumn::number
                | IContainerColumn::centeredVertically
                | IContainerColumn::alignRight;
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



Boolean DeveloperMenuHandler :: makePopUpMenu(IMenuEvent& menuEvent)
{
  // If on an object, create a menu for the object
  // Support should be added to have a container window
  // Menu if we aren't over an object

  IContainerControl* container;
  container = (IContainerControl*)(menuEvent.window());

  if(popupMenuObject()) {
    IPopUpMenu* ppumn = new IPopUpMenu(POPUP_MENU, container);
    ppumn->setAutoDeleteObject();
    ppumn->show(menuEvent.mousePosition());
    return true;
  }
  return false;
}
