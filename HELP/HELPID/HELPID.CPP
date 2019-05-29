//************************************************************
// Using Help - Runtime Setting of Help Panels               
//                                                           
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.                                      
//************************************************************/
#include <iapp.hpp>
#include <icoordsy.hpp>
#include <iframe.hpp>
#include <ihelp.hpp>
#include <ilistbox.hpp>
#include <imcelcv.hpp>
#include <imenubar.hpp>
#include <istattxt.hpp>

#include "helpid.hpp"
#include "helpid.h"

#ifdef IC_PM
  #ifdef IPF_COMPATIBLE
    #undef IPF_COMPATIBLE
  #endif
#endif

void main ( )
{
  ICoordinateSystem::setApplicationOrientation
          ( ICoordinateSystem::originUpperLeft );

  // Create a primary window with a list box.
  IFrameWindow
    primary( "Runtime Setting of Help Panels", ID_PRIMARY );
  IMenuBar
    menubar( &primary );
  menubar
   .setMenu( ID_MENUBAR );

  IMultiCellCanvas
    client( ID_CLIENT, &primary, &primary );
  IStaticText
    heading( ID_DUMMY, &client, &client );
  heading
   .setText( "Select a type of window to create." );
  IListBox
    list( ID_LISTBOX, &client, &client );
  list
   .addAsLast( "Primary" );
  list
   .addAsLast( "Secondary (modeless)" );
  list
   .addAsLast( "Secondary (modal)" );
  list
   .select( 0 )
   .enableTabStop()
   .enableGroup();

  // Create handler that processes an "open" event.
  ListBoxSelectHandler
    selHandler;
  selHandler
   .handleEventsFor( &client );

  client
   .addToCell( &heading, 2, 2 )
   .addToCell( &list,    2, 4 );
  client
   .setColumnWidth( 2, 1, true )
   .setColumnWidth( 3, IMultiCellCanvas::defaultCell().width() )
   .setRowHeight( 4, 1, true )
   .setRowHeight( 5, IMultiCellCanvas::defaultCell().height() );

  // Create the help window and associate it with the primary window.
  IHelpWindow::Settings
    settings;
  settings
   .setTitle( "Runtime Setting of Help Panels - Help" )
   .setLibraries( "HELPID.HLP" );
#ifdef IPF_COMPATIBLE
  IHelpWindow
    help( settings, &primary,
          IHelpWindow::classDefaultStyle
           | IHelpWindow::ipfCompatible );
#else
  IHelpWindow
    help( settings, &primary );
#endif

  // Assign contextual and general help.
  list
   .setHelpId( PANEL_LISTBOX );
  primary
   .setHelpId( PANEL_PRIMARY );
  menubar
   .setItemHelpId( ID_FILE,    PANEL_FILE )
   .setItemHelpId( ID_CHOICE1, PANEL_CHOICE1 )
   .setItemHelpId( ID_CHOICE2, PANEL_CHOICE2 )
   .setItemHelpId( ID_CLOSE,   PANEL_CLOSE );

  primary
   .setClient( &client )
   .setFocus()
   .show();

  IApplication::current().run();
}

IBase::Boolean
  ListBoxSelectHandler::enter ( IControlEvent& event )
{
  Boolean
    dontPassOn = false;
  if ( event.controlId() == ID_LISTBOX )
  {
     long
       selection = ((IListBox*)event.controlWindow())->selection();
     switch ( selection )
     {
       case 0:     // Display another primary window.
       {
         PrimaryWindow
          *frame = new PrimaryWindow;
         frame->setAutoDeleteObject();
         IHelpWindow
          *help = IHelpWindow::helpWindow( event.dispatchingWindow() );
         help->setAssociatedWindow( frame );
         frame->show();
         break;
       }
       case 1:     // Display a modeless secondary window.
       {
         SecondaryWindow
          *frame = new SecondaryWindow( ID_SECONDARY_MODELESS,
                                        event.dispatchingWindow() );
         frame->setAutoDeleteObject();
         IHelpWindow
          *help = IHelpWindow::helpWindow( frame );
         help->setAssociatedWindow( frame );
         frame->show();
         break;
       }
       case 2:     // Display a modal secondary window.
       {
         SecondaryWindow
           frame( ID_SECONDARY_MODAL, event.dispatchingWindow() );
         IHelpWindow
          *help = IHelpWindow::helpWindow( &frame );
         help->setAssociatedWindow( &frame );
         frame.showModally();
         break;
       }
     }
     dontPassOn = true;
  }

  return dontPassOn;
}
