#ifndef _CMDHDR1_
#define _CMDHDR1_
//*********************************************************
// Reusable Handlers - Simple Command Handler
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//*********************************************************
#include <ibase.hpp>         // For IC_PM/IC_WIN.
#ifdef IC_PM
  #define INCL_DOSPROCESS    // For DosBeep.
  #include <os2.h>
  #define BEEP(frequency,duration) (DosBeep(frequency,duration))
#else
  #include <windows.h>       // For Beep.
  #define BEEP(frequency,duration) (Beep(frequency,duration))
#endif

#include <icmdhdr.hpp>
#include "cmdhdrs.h"

class OneBeepCmdHandler : public ICommandHandler {
protected:
virtual Boolean
  command ( ICommandEvent& event )
  {
    Boolean dontPassOn = false;
    if ( event.commandId() == ID_ONE_BEEP_CMD )
    {
       BEEP( 100, 100 );
       dontPassOn = true;
    }
    return dontPassOn;
  }
}; // OneBeepCmdHandler

#endif // _CMDHDR1_
