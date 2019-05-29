//************************************************************
// Advanced Frame - Window Viewer Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include "treeview.hpp"
#include "hwindow.hpp"
#include "hwinobj.hpp"
#include "winview.h"

TreeView::TreeView ( HWindow& hwindow )
  : hwindow( hwindow ),
    frame( WND_MAIN, 0, 0,
           IFrameWindow::nextShellRect().scaleBy( 0.5, 1.0 ),
           IFrameWindow::defaultStyle() |
           IFrameWindow::menuBar | IFrameWindow::minimizedIcon  ),
    title( &frame ),
    client(IC_FRAME_CLIENT_ID, &frame, &frame, IRectangle(),
           IContainerControl::defaultStyle() |
           IContainerControl::noSharedObjects ),
    fmenu( &frame, IMenuBar::wrapper ),
    fcommandHandler( *this ),
    fmenuHandler( )

{
  title.setObjectText( "WinView" );
  title.setViewText( "Tree View" );

  client.setDeleteObjectsOnClose( true );
  client.showTreeTextView();

  frame.setClient( &client );

  handler.handleEventsFor( &client );
  fcommandHandler.handleEventsFor( &frame );
  fmenuHandler.handleEventsFor( &client );
}

TreeView &TreeView::open ( )
{
  frame.setFocus();
  frame.show();
  populate();
  return *this;
}

TreeView&  TreeView::close    ( )
{
   frame.close();
   return *this;
}

const IContainerControl& TreeView::container( ) const
{
   return client;
}

TreeView& TreeView::refreshView ( )
{
   client.setRefreshOff();
   client.deleteAllObjects();
   populate();
   client.setRefreshOn();
   client.refresh();
   return *this;
}

TreeView& TreeView::populate ( )
{
  HWindowObject* root =
     new HWindowObject( hwindow, APP_ICON_ID, &client );
  client.addObject( root );
  populateChildren( root );
  client.expand( root );
  return *this;
}

TreeView& TreeView::populateChildren( HWindowObject* root )
{
  HWindow::ChildCursor cursor( root->hWindow() );
  for ( cursor.setToFirst();
        cursor.isValid();
        cursor.setToNext() )
    {
    HWindowObject* child =
       new HWindowObject( cursor.hWindow(), APP_ICON_ID, &client);
    client.addObject( child, root);
    populateChildren( child );
    }
  return *this;
}

CommandHandler::CommandHandler( TreeView& view ) :
  fview( view )
{ }

IBase::Boolean CommandHandler::command( ICommandEvent& event )
{
   Boolean handled = true;
   switch (event.commandId())
      {
      case MI_EXIT     :
         fview.close();
         break;
      case MI_OPENICON :
         {
         HWindowObject* object = (HWindowObject*)
            fview.container().cursoredObject();
         if (object)
            object->openIconView( );
         }
         break;
      case MI_OPENINFO :
         {
         HWindowObject* object = (HWindowObject*)
            fview.container().cursoredObject();
         if (object)
            object->openInfoView( );
         }
         break;
      case MI_REFRESH  :
         fview.refreshView( );
         break;
      default:
         handled = false;
      }
   return handled;
}

