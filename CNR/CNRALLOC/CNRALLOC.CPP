//************************************************************
// Container Control - ICnrAllocator example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <iframe.hpp>
#include <icnrctl.hpp>
#include <isplitcv.hpp>
#include <iapp.hpp>
#include <time.h>

void main ()
{

// Create the frame window with a split canvas in the
// client area.
IFrameWindow frameWindow("Container ICnrAllocator Example");
ISplitCanvas splitCanvas(0x101,
                         &frameWindow,
                         &frameWindow);
frameWindow.setClient(&splitCanvas);

// Create two containers to go into the split canvas.
IContainerControl::Style containerStyle = IContainerControl::classDefaultStyle
#ifdef CCLCNR
   | IContainerControl::pmCompatible
#endif
                                        | IContainerControl::noSharedObjects;
IContainerControl slowContainer(0x102,
                      &splitCanvas,
                      &splitCanvas,
                      IRectangle(),
                      containerStyle);
IContainerControl fastContainer(0x103,
                      &splitCanvas,
                      &splitCanvas,
                      IRectangle(),
                      containerStyle);

slowContainer
  .showFlowedTextView()
  .showTitle();

fastContainer
  .showFlowedTextView()
  .showTitle();

time_t startTime, endTime;
IContainerObject* object;

// Test 1: Start the timer and add 5000 objects
//         WITHOUT the allocator.
time(&startTime);
for(int i = 0; i<5000; i++)
{
   object = new IContainerObject("object");
   slowContainer.addObject(object);
}

// Stop the timer and change the text of the first
// object to indicate the elapsed time.
time(&endTime);
double totalTime = difftime(endTime, startTime);
IContainerObject* firstObject = slowContainer.objectAt(0);
firstObject->setIconText(IString(totalTime)+" seconds");
slowContainer
  .setTitle(IString("Non-ICnrAllocator Container ")+IString(totalTime)+" seconds");


// Test 2: Start the timer and add 5000 objects
//         WITH the allocator.
time(&startTime);
ICnrAllocator allocator( 5000, sizeof(IContainerObject));
for(int j = 0; j<5000; j++)
{
   object = new(allocator) IContainerObject("object");
}
fastContainer.addObjects(allocator);

// Stop the timer and change the text of the first
// object to indicate the elapsed time.
time(&endTime);
totalTime = difftime(endTime, startTime);
firstObject = fastContainer.objectAt(0);
firstObject->setIconText(IString(totalTime)+" seconds");

fastContainer
  .setTitle(IString("ICnrAllocator Container ")+IString(totalTime)+" seconds");


// Give focus to the frame and show it.
frameWindow.show();
frameWindow.setFocus();

IApplication::current().run();
}
