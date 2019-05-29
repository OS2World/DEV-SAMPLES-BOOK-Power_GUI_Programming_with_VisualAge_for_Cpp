#ifndef _EDITWIN_
#define _EDITWIN_
//************************************************************
// Advanced Frame - MDI Frame Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <ititle.hpp>
#include <icmdhdr.hpp>
#include <imenubar.hpp>
#include <imle.hpp>
#include <istring.hpp>
#include "mdiwin.hpp"

class MainWindow;

class CommandHandler : public ICommandHandler {
public:
  CommandHandler( MainWindow& frame );
virtual Boolean
  command( ICommandEvent& event );
private:
  MainWindow& fframe;
CommandHandler( const CommandHandler& );
CommandHandler& operator= ( const CommandHandler& );
};

class EditWindow : protected MDIWindow {
public:
  EditWindow ( MDIWindow& parent, const IString& filename );
virtual EditWindow
 &open     ( );
virtual EditWindow
 &close    ( );

private:
IString
 fname;
ITitle
  title;
IMultiLineEdit
  fclient;
EditWindow ( const EditWindow& );
EditWindow& operator=( const EditWindow& );
};

class MainWindow : public IVBase {
public:
  MainWindow ( );

virtual MainWindow
 &openChild ( ),
 &closeChild ( ),
 &restoreChild( ),
 &minimizeChild( ),
 &activateChild( unsigned long childId );

virtual MainWindow
 &arrange        ( ),
 &cascade        ( ),
 &tile           ( Boolean horizontal=true ),
 &close          ( );

private:
MDIWindow
  frame;
IMenuBar
  menu;
CommandHandler
  handler;
MainWindow ( const MainWindow& );
MainWindow& operator=( const MainWindow& );
};

#endif // _EDITWIN_
