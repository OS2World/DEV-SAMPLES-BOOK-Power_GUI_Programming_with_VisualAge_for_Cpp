//************************************************************
// Container Control - Text View                              
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <iframe.hpp>
#include <icnrctl.hpp>
#include <iapp.hpp>

void main ()
{

IFrameWindow cnrFrame("Container Text View");

IContainerControl cnr(0x101,        
                      &cnrFrame,    
                      &cnrFrame);

// Put container in client area
cnrFrame.setClient(&cnr);

// Create the objects
// Note: Windows doesn't support new line characters.
#ifdef IC_PM
  IContainerObject* obj1 = new 
               IContainerObject("Object 1 \n  Line 1 \n  Line 2 ");
  IContainerObject* obj2 = new 
               IContainerObject("Object 2 \n  Line 1 \n  Line 2 ");
#else
  IContainerObject* obj1 = new IContainerObject("Object 1");
  IContainerObject* obj2 = new IContainerObject("Object 2");
#endif

// Add the objects to the container
cnr.addObject(obj1);
cnr.addObject(obj2);

// Flowed Text view
cnr.showFlowedTextView();

cnrFrame.sizeTo(ISize(280,200));
cnrFrame.show();
cnrFrame.setFocus();


IApplication::current().run();
}
