#ifndef _TREEVIEW_
#define _TREEVIEW_
//************************************************************
// Advanced Frame - Window Viewer Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <iframe.hpp>
#include <ititle.hpp>
#include <icmdhdr.hpp>
#include <icnrctl.hpp>
#include <icnrhdr.hpp>
#include <imenubar.hpp>
#include "hwinobj.hpp"

class HWindow;
class TreeView;

class CommandHandler : public ICommandHandler {
public:
  CommandHandler( TreeView& view );
virtual Boolean
  command( ICommandEvent& event );
private:
  TreeView& fview;
CommandHandler( const CommandHandler& );
CommandHandler& operator= ( const CommandHandler& );
};

class TreeView : public IVBase {
public:
  TreeView ( HWindow &hwindow );
virtual TreeView
 &open     ( );
virtual TreeView
 &close    ( );
virtual TreeView
 &refreshView ( );
const IContainerControl
 &container( ) const;

protected:
virtual TreeView
 &populate ( );
virtual TreeView
 &populateChildren( HWindowObject* root );

private:
HWindow
 &hwindow;
IFrameWindow
  frame;
ITitle
  title;
IContainerControl
  client;
ICnrHandler
  handler;
IMenuBar
  fmenu;
CommandHandler
  fcommandHandler;
MenuHandler
  fmenuHandler;
TreeView ( const TreeView& );
TreeView& operator=( const TreeView& );
};

#endif // _TREEVIEW_
