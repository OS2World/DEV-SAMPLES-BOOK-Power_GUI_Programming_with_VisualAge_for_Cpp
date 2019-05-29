//*********************************************************
// Using Help - Help Menu Choices
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc.
// All Rights Reserved.
//*********************************************************
#include <iapp.hpp>
#include <icoordsy.hpp>
#include <ihelp.hpp>
#include <ititle.hpp>

#include "helpmenu.hpp"
#include "hcmdhdr.hpp"
#include "hkeyshdr.hpp"
#include "helpmenu.h"

#ifdef IC_PM
  #ifdef IPF_COMPATIBLE
    #undef IPF_COMPATIBLE
  #endif
#endif

static HelpCommandHandler
  helpCommandHdr;
static KeysHelpHandler
  keysHelpHdr;

void main ( )
{
  ICoordinateSystem::setApplicationOrientation
          ( ICoordinateSystem::originUpperLeft );

  // Create a primary window with a help menu.
  HelpMenuWindow
    primary( ID_PRIMARY, 0 );

  // Create the help window and associate it with the primary window.
  IHelpWindow::Settings
    settings;
  settings
   .setTitle( "Help Menu Choices - Help" )
   .setLibraries( "HELPMENU.HLP" )
   .setHelpTable( ID_HELPTABLE );
#ifdef IPF_COMPATIBLE
  IHelpWindow
    help( settings, &primary,
          IHelpWindow::classDefaultStyle
           | IHelpWindow::ipfCompatible );
#else
  IHelpWindow
    help( settings, &primary );
#endif

  // Attach static help-specific handlers to the associated window.
  helpCommandHdr
   .handleEventsFor( &primary );
  keysHelpHdr
   .handleEventsFor( &primary );

  primary
   .setFocus()
   .show();

  IApplication::current().run();
}

IBase::Boolean
  CommandHandler::command ( ICommandEvent& event )
{
  Boolean
    dontPassOn = false;
  if ( event.commandId() == ID_SECONDARY_PB )
  {
     // Create a modeless secondary window.
     HelpMenuWindow
      *frame = new HelpMenuWindow( ID_SECONDARY,
                                   event.dispatchingWindow() );
     frame->setAutoDeleteObject();
     IHelpWindow
      *help = IHelpWindow::helpWindow( frame );
     help->setAssociatedWindow( frame );

     // Attach static help-specific handlers to the associated window.
     helpCommandHdr
      .handleEventsFor( frame );
     keysHelpHdr
      .handleEventsFor( frame );

     (*frame)
      .setFocus()
      .show();

     dontPassOn = true;
  }
  else if ( event.commandId() == ID_EXIT_PB )
  {
     // Dismiss the frame window.
     IFrameWindow
      *frame = (IFrameWindow*)event.dispatchingWindow();
     frame->close();
     dontPassOn = true;
  }

  return dontPassOn;
}

HelpMenuWindow::HelpMenuWindow ( unsigned long id,
                                 IWindow*      owner )
  : IFrameWindow( id, 0, owner ),
    menuBar( ID_MENUBAR, this ),
    canvasClient( ID_CLIENT, this, this ),
    heading ( ID_HEADING, &canvasClient, &canvasClient ),
    showSecondaryPB( owner ?
                       0 :
                       new IPushButton( ID_SECONDARY_PB,
                                        &canvasClient,
                                        &canvasClient ) ),
    exitPB( ID_EXIT_PB, &canvasClient, &canvasClient ),
    cmdHandler()
{
  ITitle( this, "Help Menu Choices" );

  heading
   .setText( "Select an item from the Help menu." );
  if ( showSecondaryPB )
  {
     (*showSecondaryPB)
      .enableDefault()
      .setText( "Show secondary window" )
      .enableTabStop()
      .enableGroup();
  }
  exitPB
   .setText( "Exit" );
  if ( ! showSecondaryPB )
  {
     exitPB
      .enableDefault()
      .enableTabStop()
      .enableGroup();
  }

  cmdHandler
   .handleEventsFor( this );

  unsigned long
    lastColumn( 4 );
  if ( showSecondaryPB )
  {
     canvasClient
      .addToCell( &heading,        2, 2, 4 )
      .addToCell( showSecondaryPB, 2, 4 )
      .addToCell( &exitPB,         4, 4 );
     lastColumn = 6;
  }
  else
  {
     canvasClient
      .addToCell( &heading,        2, 2, 2 )
      .addToCell( &exitPB,         2, 4 );
  }
  canvasClient
   .setColumnWidth( lastColumn - 1, 0, true )
   .setColumnWidth( lastColumn,
                    IMultiCellCanvas::defaultCell().width() )
   .setRowHeight( 3, IMultiCellCanvas::defaultCell().height(), true )
   .setRowHeight( 5, IMultiCellCanvas::defaultCell().height() );

  (*this)
   .setClient( &canvasClient );
}

HelpMenuWindow::~HelpMenuWindow ( )
{
  if ( showSecondaryPB )
  {
     delete showSecondaryPB;
  }
}
