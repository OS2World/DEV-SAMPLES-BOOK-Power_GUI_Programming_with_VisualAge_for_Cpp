#ifndef _HELPID_
#define _HELPID_
//************************************************************
// Using Help - Runtime Setting of Help Panels               
//                                                           
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.                                      
//************************************************************
#include <ientryfd.hpp>
#include <iframe.hpp>
#include <imcelcv.hpp>
#include <ipushbut.hpp>
#include <iselhdr.hpp>
#include <istattxt.hpp>
#include <isysmenu.hpp>
#include <ititle.hpp>

#include "helpid.h"

class ListBoxSelectHandler : public ISelectHandler {
protected:
virtual Boolean
  enter ( IControlEvent& event );
}; // ListBoxSelectHandler

class TestWindow : public IFrameWindow {
public:
  TestWindow ( unsigned long id,
               IWindow*      parent = 0,
               IWindow*      owner = 0 )
    : IFrameWindow ( id, parent, owner ),
      canvasClient( ID_CLIENT, this, this ),
      prompt1 ( ID_DUMMY, &canvasClient, &canvasClient ),
      prompt2 ( ID_DUMMY, &canvasClient, &canvasClient ),
      entry1 ( ID_ENTRY1, &canvasClient, &canvasClient ),
      entry2 ( ID_ENTRY2, &canvasClient, &canvasClient ),
      helpButton ( ID_HELP_BUTTON, &canvasClient, &canvasClient )
  {
    prompt1
     .setText( "Has contextual help" );
    prompt2
     .setText( "No contextual help" );
    entry1
     .enableTabStop()
     .enableGroup();
    entry2
     .enableTabStop()
     .enableGroup();
    helpButton
     .enableHelp()
     .disableMouseClickFocus()
     .setText( "Help" )
     .enableTabStop()
     .enableGroup();

    canvasClient
     .addToCell( &prompt1,    2, 2 )
     .addToCell( &prompt2,    2, 4 )
     .addToCell( &entry1,     4, 2 )
     .addToCell( &entry2,     4, 4 )
     .addToCell( &helpButton, 2, 6, 3 );
    canvasClient
     .setColumnWidth( 5, 10 )
     .setRowHeight( 7, 10 );

    (*this)
     .moveSizeToClient( IRectangle( this->rect().minXMinY(),
                                    ISize( canvasClient.minimumSize() ) ) )
     .setFocus();
  }
protected:
IMultiCellCanvas
  canvasClient;
IStaticText
  prompt1,
  prompt2;
IEntryField
  entry1,
  entry2;
IPushButton
  helpButton;
private:
  TestWindow ( const TestWindow& );
TestWindow
 &operator=  ( const TestWindow& );
}; // TestWindow

class PrimaryWindow : public TestWindow {
public:
  PrimaryWindow ( )
    : TestWindow ( ID_PRIMARY2 ),
      systemMenu ( this )
  {
    ITitle( this, "Another Primary Window" );

    // Assign contextual and general help.
    ( *this )
     .setHelpId( PANEL_PRIMARY2 );
    entry1
     .setHelpId( PANEL_ENTRY1_PRIMARY2 );
    helpButton
     .setHelpId( PANEL_HELP_BUTTON_PRIMARY2 );
    systemMenu
     .setItemHelpId( ID_CLOSE, PANEL_CLOSE );
  }
private:
  PrimaryWindow ( const PrimaryWindow& );
PrimaryWindow
 &operator=     ( const PrimaryWindow& );
ISystemMenu
  systemMenu;
}; // PrimaryWindow

class SecondaryWindow : public TestWindow {
public:
  SecondaryWindow ( unsigned long id,
                    IWindow*      owner )
    : TestWindow ( id, 0, owner ),
      systemMenu ( this )
  {
    ITitle( this,
            id == ID_SECONDARY_MODELESS ?
               "Modeless Secondary Window" :
               "Modal Secondary Window" );

    // Assign contextual and general help depending on the
    // window type.
    if ( id == ID_SECONDARY_MODELESS )
    {
       ( *this )
        .setHelpId( PANEL_SEC_MODELESS );
       entry1
        .setHelpId( PANEL_ENTRY1_SEC_MODELESS );
       helpButton
        .setHelpId( PANEL_HELP_BUTTON_SEC_MODELESS );
    }
    else
    {
       ( *this )
        .setHelpId( PANEL_SEC_MODAL );
       entry1
        .setHelpId( PANEL_ENTRY1_SEC_MODAL );
       helpButton
        .setHelpId( PANEL_HELP_BUTTON_SEC_MODAL );
    }
    systemMenu
     .setItemHelpId( ID_CLOSE, PANEL_CLOSE );
  }
private:
  SecondaryWindow ( const SecondaryWindow& );
SecondaryWindow
 &operator=       ( const SecondaryWindow& );
ISystemMenu
  systemMenu;
}; // SecondaryWindow

#endif // _HELPID_
