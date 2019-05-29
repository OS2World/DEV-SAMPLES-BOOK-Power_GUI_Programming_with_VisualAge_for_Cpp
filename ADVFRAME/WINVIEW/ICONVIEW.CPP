//************************************************************
// Advanced Frame - Window Viewer Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include "iconview.hpp"
#include "winview.h"


IconView::IconView ( HWindowObject& object )
  : HWindowObjectView( clientWindow(),
                       object,
                       "Child View" ),
    handler( )
{
  handler.handleEventsFor(
    (IContainerControl*)( this->client() ) );
  populate();
}

IconView &IconView::populate ( )
{
  IContainerControl
   *cnr = (IContainerControl*)( client() );
  HWindow::ChildCursor cursor( object()->hWindow() );
  for ( cursor.setToFirst();
        cursor.isValid();
        cursor.setToNext() )
    {
    HWindowObject* child =
      new HWindowObject( cursor.hWindow(), APP_ICON_ID, cnr);
    cnr->addObject( child );
    }
  cnr -> arrangeIconView();
  return *this;
}

IContainerControl* IconView::clientWindow ( )
{
  IContainerControl* p =
     new IContainerControl( IC_FRAME_CLIENT_ID,
                            IWindow::objectWindow(),
                            IWindow::objectWindow(),
                            IRectangle(),
                            IContainerControl::defaultStyle() |
                            IContainerControl::noSharedObjects );
  p -> setDeleteObjectsOnClose( true );
  p -> showIconView();
  p -> setAutoDeleteObject( true );
  return p;
}
