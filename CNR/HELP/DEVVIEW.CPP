//************************************************************
// Container Control - Help in the Container                    
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <ifont.hpp>
#include <iapp.hpp>
#include <icnrcol.hpp>
#include "devview.hpp"
#include "devview.h"
#include "devmodel.hpp"


DeveloperView::DeveloperView ( )
                   : IFrameWindow("Developers - Details View", ID_DETAILS_FRAME),
                     fContainer(ID_DETAILS_CNR, this, this),
                     fCnrHandler(),
                     fCnrEditHandler(),
                     fHelpWindow(HELP_TABLE, this)
{
  // Create the Columns for the details view.
  IContainerColumn
   *nameColumn,
   *compuServeIdColumn,
   *ageColumn;
  nameColumn = Developer::createAndOrphanColumnFor(
                              fContainer,
                              Developer::kNameColumn);
  compuServeIdColumn = Developer::createAndOrphanColumnFor(
                              fContainer,
                              Developer::kCompuServeIdColumn);
  ageColumn = Developer::createAndOrphanColumnFor(
                              fContainer,
                              Developer::kAgeColumn);
  
  // Create objects & add to cnr.
  Developer* developer1;
  Developer* developer2;
  developer1 = new Developer("John Smith",
                            "222222,3333",
                            38);
  fContainer.addObject(developer1);
  
  developer2 = new Developer("Bob Jones",
                            "33333,4444",
                            40);
  fContainer.addObject(developer2);
  
  // Add Help for objects and columns.
  nameColumn->setHelpId(HELPFOR_NAME);
  compuServeIdColumn->setHelpId(HELPFOR_ADDRESS);
  ageColumn->setHelpId(HELPFOR_AGE);
  developer1->setHelpId(HELPFOR_DEVELOPER);
  developer2->setHelpId(HELPFOR_DEVELOPER);
  
  // Set the Help Title and indicate the 
  // help libraries.
  fHelpWindow.setTitle("Help for Developer Details");
  fHelpWindow.addLibraries(IApplication::current().userResourceLibrary().
                             loadString(HELP_LIBRARIES));
  
  // Enable editing in objects.
  developer1->enableDataUpdate();
  developer2->enableDataUpdate();
  
  // Attach the handlers.
  fCnrHandler.handleEventsFor(&fContainer);
  fCnrEditHandler.handleEventsFor(&fContainer);
  
  // Switch to the Details view.
  fContainer.showDetailsView();
  
  // Put container in client area.
  setClient(&fContainer);
}

