//************************************************************

// Direct Manipulation - List Box Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <iframe.hpp>
#include <ilistbox.hpp>
#include <ientryfd.hpp>
#include <idmhndlr.hpp>
#include <idmprov.hpp>
#include <icoordsy.hpp>

#include "lboxitem.hpp"

void main()
  {
  IFrameWindow
    frame( "List Box Drag Drop Sample" );

  IListBox
    client( 0, &frame, &frame, IRectangle()
#ifdef IC_WIN
    ,IListBox::defaultStyle() & ~IListBox::border3D
#endif
    );
  ListBoxItemProvider
    provider( &client );
  IDMHandler::enableDragDropFor( &client );
  client.addAsLast( "Drag an item as text" );
  client.addAsLast( "Drag to shredder to delete (OS/2 only)" );
  client.addAsLast( "Drop on item to replace text" );
  client.addAsLast( "Drop off end to add item" );

  IEntryField
    ef( 0xef, &frame, &frame );
  IDMHandler::enableDragDropFor( &ef );
  ef.setLimit( 1024 );
  ef.setText( "Drag text from here to list box" );

  frame.setClient( &client );
  frame.addExtension( &ef, frame.belowClient, 30 );
  frame.setFocus();
  frame.moveSizeTo( frame.rect().scaleBy( 0.5, 1.0 ) );
  frame.showModally();
  }
