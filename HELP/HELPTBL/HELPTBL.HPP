#ifndef _HELPTBL_
#define _HELPTBL_
//***********************************************************
// Using Help - Help Tables                                  
//                                                           
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.                                      
//***********************************************************
#include <ientryfd.hpp>
#include <iframe.hpp>
#include <imcelcv.hpp>
#include <ipushbut.hpp>
#include <iselhdr.hpp>
#include <istattxt.hpp>
#include <ititle.hpp>

#include "helptbl.h"

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
private:
  TestWindow ( const TestWindow& );
TestWindow
 &operator=  ( const TestWindow& );
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
}; // TestWindow

class PrimaryWindow : public TestWindow {
public:
  PrimaryWindow ( )
    : TestWindow ( ID_PRIMARY2 )
  {
    ITitle( this, "Another Primary Window" );
  }
private:
  PrimaryWindow ( const PrimaryWindow& );
PrimaryWindow
 &operator=     ( const PrimaryWindow& );
}; // PrimaryWindow

class SecondaryWindow : public TestWindow {
public:
  SecondaryWindow ( unsigned long id,
                    IWindow*      owner )
    : TestWindow ( id, 0, owner )
  {
    ITitle( this,
            id == ID_SECONDARY_MODELESS ?
               "Modeless Secondary Window" :
               "Modal Secondary Window" );
  }
private:
  SecondaryWindow ( const SecondaryWindow& );
SecondaryWindow
 &operator=       ( const SecondaryWindow& );
}; // SecondaryWindow

#endif // _HELPTBL_
