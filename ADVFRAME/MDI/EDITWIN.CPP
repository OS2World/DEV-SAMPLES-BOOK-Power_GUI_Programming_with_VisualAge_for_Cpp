//************************************************************
// Advanced Frame - MDI Frame Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <ifiledlg.hpp>
#include "editwin.hpp"
#include "mdi.h"

MainWindow :: MainWindow ( )
  : frame( WND_MAIN, 0, 0,
           MI_WINDOWS, MI_FIRSTCHILD,
           IFrameWindow::nextShellRect(),
           IFrameWindow::defaultStyle() |
           IFrameWindow::menuBar | IFrameWindow::minimizedIcon,
           "Simple Viewer" ),
    menu( &frame, IMenuBar::wrapper ),
    handler( *this )
{
  menu.disableItem( MI_CLOSE );
  handler.handleEventsFor( &frame );
  frame.setFocus().show();
}

MainWindow& MainWindow::openChild( )
{
  IFileDialog dialog( 0, &frame );
  if (dialog.pressedOK())
     {
     EditWindow* win = new EditWindow( frame, dialog.fileName() );
     win->open();
     menu.enableItem( MI_CLOSE );
     }
  return *this;
}

MainWindow& MainWindow::closeChild( )
{
  MDIWindow* child = frame.activeChild();
  if (child)
    child->close();
  if ( !frame.activeChild() )
    menu.disableItem( MI_CLOSE );
  return *this;
}

MainWindow& MainWindow::restoreChild( )
{
  MDIWindow* child = frame.activeChild();
  if (child)
    child->restore();
  return *this;
}

MainWindow& MainWindow::minimizeChild( )
{
  MDIWindow* child = frame.activeChild();
  if (child)
    child->minimize();
  return *this;
}

MainWindow& MainWindow::activateChild( unsigned long childId )
{
  frame.activateChild( childId );
  return *this;
}

MainWindow& MainWindow::arrange( )
{
   frame.arrange();
   return *this;
}

MainWindow& MainWindow::cascade( )
{
   frame.cascade();
   return *this;
}

MainWindow& MainWindow::tile( Boolean horizontal )
{
   frame.tile(horizontal);
   return *this;
}

MainWindow& MainWindow::close( )
{
   frame.close();
   return *this;
}

EditWindow :: EditWindow ( MDIWindow&     parent,
                           const IString& filename )
   : MDIWindow( MI_FIRSTCHILD, &parent,
           IRectangle(IPoint(10,10),
                      parent.size()).scaleBy( 0.8, 0.8 ),
           IFrameWindow::defaultStyle() |
           IFrameWindow::minimizedIcon ),
    fname( filename ),
    title( this ),
    fclient(IC_FRAME_CLIENT_ID, this, this )
{
  setAutoDeleteObject( true );
  title.setText( fname );
  try
    {
    fclient.importFromFile( fname );
    }
  catch (IAccessError& )
    {
    // Catch exception if new file.
    }
  setClient( &fclient );
}

EditWindow& EditWindow::open( )
{
   this->setFocus();
   this->show();
   return *this;
}

EditWindow& EditWindow::close( )
{
   MDIWindow::close();
   return *this;
}


CommandHandler::CommandHandler( MainWindow& frame ) :
  fframe( frame )
{ }

IBase::Boolean CommandHandler::command( ICommandEvent& event )
{
   switch (event.commandId())
      {
      case MI_EXIT     :
         fframe.close();
         break;
      case MI_OPEN :
         fframe.openChild();
         break;
      case MI_CLOSE :
      case IC_ID_CLOSE :
         fframe.closeChild();
         break;
      case IC_ID_RESTORE :
         fframe.restoreChild();
         break;
      case IC_ID_MINIMIZE :
         fframe.minimizeChild();
         break;
      case MI_CASCADE :
         fframe.cascade();
         break;
      case MI_TILEH :
         fframe.tile( true );
         break;
      case MI_TILEV :
         fframe.tile( false );
         break;
      case MI_ARRANGE :
         fframe.arrange( );
         break;
      default:
         fframe.activateChild( event.commandId() );
      }
   return false;
}

