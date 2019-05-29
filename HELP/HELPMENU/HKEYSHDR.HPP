#ifndef _HKEYSHDR_
#define _HKEYSHDR_
//*********************************************************
// Using Help - Help Menu Choices
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc.
// All Rights Reserved.
//*********************************************************
#include <ihelphdr.hpp>
#include "helpmenu.h"   // For PANEL_KEYS_HELP.

class KeysHelpHandler : public IHelpHandler {
protected:
virtual Boolean
  keysHelpId ( IEvent& event )
  {
    event
     .setResult( PANEL_KEYS_HELP );
    return true;
  }
}; // KeysHelpHandler

#endif // _HKEYSHDR_
