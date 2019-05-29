//************************************************************
// Packaging and Performance - Using Static Object Functions 
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <ireslib.hpp>
#include "appstat.hpp"

// Define static instance of AppStatics.
AppStatics appStatics;

// Initialize AppStatics object pointer
IDynamicLinkLibrary* AppStatics::engDLL = 0;

// Destructor to close the DLL.
AppStatics::~AppStatics ( )
{
  if(engDLL != 0)
    delete engDLL;
}

// Static accessor for the DLL.
IDynamicLinkLibrary& AppStatics :: englishDLL( )
{
   if(!engDLL)
     engDLL = new IDynamicLinkLibrary("myeng");
   return *engDLL;
}

