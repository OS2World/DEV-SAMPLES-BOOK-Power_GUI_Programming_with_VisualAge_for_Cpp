#ifndef _CMDHDR2_
#define _CMDHDR2_
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
  #define INCL_WINWINDOWMGR  // For CMDSRC_OTHER.
  #include <os2.h>
  #define BEEP(frequency,duration) (DosBeep(frequency,duration))
#else
  #include <windows.h>       // For Beep.
  #define BEEP(frequency,duration) (Beep(frequency,duration))
#endif

#include <icmdhdr.hpp>
#include "cmdhdrs.h"

class TwoBeepCmdHandler : public ICommandHandler {
protected:
virtual Boolean
  command ( ICommandEvent& event )
  {
    Boolean dontPassOn = false;
    if ( event.commandId() == ID_TWO_BEEP_CMD )
    {
       // Issue the first beep; then send a command event to
       // invoke another command handler to do the second beep.
       BEEP( 200, 100 );
       event.window()
        ->sendEvent( IWindow::command,
#ifdef IC_PM
                     IEventParameter1( ID_ONE_BEEP_CMD ),
                     IEventParameter2( CMDSRC_OTHER, false ) );
#else
                     IEventParameter1( ID_ONE_BEEP_CMD, 3 ),
                     IEventParameter2( 0 ) );
#endif
       dontPassOn = true;
    }
    return dontPassOn;
  }
}; // TwoBeepCmdHandler

#endif // _CMDHDR2_
