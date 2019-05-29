//************************************************************
// Notebook Control - Smart Guide Notebook            
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <iapp.hpp>
#include <iostream.h>
#include "smrtguid.hpp"


void main ( )
{
  SmartGuide smartGuide("PowerGui SmartGuide Sample");
  TextSmartPage  introPage;
  introPage
   .setPageLabel("What is a Smart Guide?")
   .setPageTextFile("smrtpag1.txt")
   .setTabText("Introduction");

  SingleChoiceSmartPage  logFile;
  logFile
   .addChoice("Yes")
   .addChoice("No")
   .setSelectedChoice(0)
   .setPageLabel("Specify whether you want to keep a log file.")
   .setPageTextFile("smrtpag2.txt")
   .setTabText("Logging");

  SingleChoiceSmartPage  logFileLocation;
  logFileLocation
   .addChoice("Current Path")
   .addChoice("Root directory")
   .setSelectedChoice(0)
   .setPageLabel("Choose a log file location.")
   .setPageTextFile("smrtpag3.txt")
   .setTabText("Log File Location");

  TextSmartPage  submitPage;
  submitPage
   .setPageLabel("Press \"Done\" to Finish.")
   .setPageText("")
   .setTabText("Submit");

  TextSmartPage  donePage;
  donePage
   .setPageLabel("SmartGuide Complete.")
   .setPageText("Ok. Thanks.")
   .setTabText("Done");


  unsigned long introHandle, logFileHandle, logFileLocationHandle,
        submit1Handle, submit2Handle, done1Handle, done2Handle;

  // 1=introHandle    2=logFileHandle  3=logFileLocationHandle
  // 4=submit1Handle  5=done1Handle                  
  // 6=submit2Handle  7=done2Handle
  //      intro 1
  //    logFile 2 
  //           / \ 
  // logFileL 3   6 submit
  //  submit  4   7 done
  //  done    5
  introHandle = smartGuide.addPage(&introPage);
  logFileHandle = smartGuide.addPage(&logFile, introHandle);
  logFileLocationHandle = smartGuide.addPage(&logFileLocation, logFileHandle);
  submit1Handle = smartGuide.addPage(&submitPage, logFileLocationHandle);
  done1Handle   = smartGuide.addPage(&donePage, submit1Handle);

  submit2Handle = smartGuide.addPage(&submitPage, logFileHandle);
  done2Handle   = smartGuide.addPage(&donePage, submit2Handle);

  cout << smartGuide.asDebugInfo();


  smartGuide.show();

  cout << smartGuide.asDebugInfo();

  IApplication::current().run();
}    
