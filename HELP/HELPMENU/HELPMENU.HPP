#ifndef _HELPMENU_
#define _HELPMENU_
//*********************************************************
// Using Help - Help Menu Choices
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc.
// All Rights Reserved.
//*********************************************************
#include <icmdhdr.hpp>
#include <iframe.hpp>
#include <imcelcv.hpp>
#include <imenubar.hpp>
#include <ipushbut.hpp>
#include <istattxt.hpp>

#include "helpmenu.h"

class CommandHandler : public ICommandHandler {
protected:
virtual Boolean
  command ( ICommandEvent& event );
}; // CommandHandler

class HelpMenuWindow : public IFrameWindow {
public:
  HelpMenuWindow ( unsigned long id,
                   IWindow*      owner = 0 );
virtual
 ~HelpMenuWindow ( );

private:
  HelpMenuWindow ( const HelpMenuWindow& );
HelpMenuWindow
 &operator=      ( const HelpMenuWindow& );
IMenuBar
  menuBar;
IMultiCellCanvas
  canvasClient;
IStaticText
  heading;
IPushButton
 *showSecondaryPB,
  exitPB;
CommandHandler
  cmdHandler;
}; // HelpMenuWindow

#endif // _HELPMENU_
