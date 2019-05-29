#ifndef _HCMDHDR_
#define _HCMDHDR_
//*********************************************************
// Using Help - Help Menu Choices
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc.
// All Rights Reserved.
//*********************************************************
#include <icmdhdr.hpp>
#include <ihelp.hpp>
#include <imsgbox.hpp>
#include <istring.hpp>
#include "helpmenu.h"

class HelpCommandHandler : public ICommandHandler {
protected:
virtual Boolean
  command  ( ICommandEvent& event )
  {
    Boolean
      dontPassOn = false;
    switch ( event.commandId() )
    {
       case ID_USINGHELP:
       {      // A user has selected the "Using help"
              // (or "How to use help") choice.
         IHelpWindow
          *help = IHelpWindow::helpWindow( event.window() );
         help->show( IHelpWindow::using );
         dontPassOn = true;
         break;
       }
       case ID_HELPCONTENTS:
       {      // A user has selected the "Contents" choice.
         IHelpWindow
          *help = IHelpWindow::helpWindow( event.window() );
         help->show( IHelpWindow::contents );
         dontPassOn = true;
         break;
       }
       case ID_PRODUCTINFO:
       {      // A user has selected the "Product Information" choice.
         IMessageBox
           msg( event.dispatchingWindow() );
         msg
          .setTitle( "About This Example" )
          .show( "This is the help menu example program from "
                   "\"Power GUI Programming with VisualAge for C++.\"",
                 IMessageBox::noIcon | IMessageBox::moveable,
                 PANEL_PRODUCT_INFO_MSG );
         dontPassOn = true;
         break;
       }
       default:
         break;
    }
    return dontPassOn;
  }
}; // HelpCommandHandler

#endif // _HCMDHDR_
