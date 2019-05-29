#ifndef _POPUPHDR_
#define _POPUPHDR_
//*********************************************************
// Reusable Handlers - Simple Command Handler
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//*********************************************************
#include <icnrmhdr.hpp>
#include <ipopmenu.hpp>
#include "cmdhdrs.h"

class PopupMenuHandler : public ICnrMenuHandler {
protected:
virtual Boolean
  makePopUpMenu ( IMenuEvent& event )
  {
    IPopUpMenu* popUp =
      new IPopUpMenu( ID_POPUP, event.dispatchingWindow() );
    popUp->setAutoDeleteObject();
    popUp->show( event.mousePosition() );
    return true;
  }
}; // PopupMenuHandler

#endif // _POPUPHDR_
