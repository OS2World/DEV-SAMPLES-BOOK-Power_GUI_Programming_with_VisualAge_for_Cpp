//*********************************************************
// Canvas - IViewPort that Scrolls a Bitmap
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//*********************************************************
#include <ibmpctl.hpp>
#include <iexcept.hpp>
#include <ivport.hpp>
#include "vportcmd.hpp"
#include "vportbmp.h"

ScrollViewCmdHandler::ScrollViewCmdHandler ( IViewPort *viewPort )
  : clViewPort( viewPort )
{
  IASSERTPARM( viewPort != 0 )
}

IBase::Boolean
  ScrollViewCmdHandler::command ( ICommandEvent &event )
{
  Boolean
    dontPassOn = false;
  switch ( event.commandId() )
  {
     // Process commands to scroll a view port.
     case ID_SCROLL_TO_TOP:
     {
        ( *clViewPort )
         .scrollViewVerticallyTo( 0 );
        dontPassOn = true;
        break;
     }
     case ID_SCROLL_TO_VERT_MIDDLE:
     {
        IRectangle
          viewWindow( IPoint(), clViewPort->viewWindowSize() ),
          visibleView( clViewPort->viewWindowDrawRectangle() );
        visibleView
         .centerAt( viewWindow.center() );
        ( *clViewPort )
         .scrollViewVerticallyTo( visibleView.bottom() );
        dontPassOn = true;
        break;
     }
     case ID_SCROLL_TO_BOTTOM:
     {
        unsigned long
          viewHeight = clViewPort->viewWindowSize().height(),
          visible = clViewPort->viewWindowDrawRectangle().height();
        ( *clViewPort )
         .scrollViewVerticallyTo( viewHeight - visible );
        dontPassOn = true;
        break;
     }
     case ID_SCROLL_TO_LEFT:
     {
        clViewPort->scrollViewHorizontallyTo( 0 );
        dontPassOn = true;
        break;
     }
     case ID_SCROLL_TO_MIDDLE:
     {
        IRectangle
          viewWindow( IPoint(), clViewPort->viewWindowSize() ),
          visibleView( clViewPort->viewWindowDrawRectangle() );
        visibleView
         .centerAt( viewWindow.center() );
        ( *clViewPort )
         .scrollViewHorizontallyTo( visibleView.left() );
        dontPassOn = true;
        break;
     }
     case ID_SCROLL_TO_RIGHT:
     {
        unsigned long
          viewWidth = clViewPort->viewWindowSize().width(),
          visible = clViewPort->viewWindowDrawRectangle().width();
        ( *clViewPort )
         .scrollViewHorizontallyTo( viewWidth - visible );
        dontPassOn = true;
        break;
     }
     default:
        break;
  }
  return dontPassOn;
}

SizeBitmapCmdHandler::SizeBitmapCmdHandler
                        ( IBitmapControl *bitmap,
                          IViewPort      *viewPort )
  : clBitmap( bitmap ),
    clViewPort( viewPort )
{
  IASSERTPARM( bitmap != 0 )
}

IBase::Boolean
  SizeBitmapCmdHandler::command ( ICommandEvent &event )
{
  Boolean
    dontPassOn = false;
  unsigned long
    mult = 1,
    div  = 1;
  switch ( event.commandId() )
  {
     // Process commands to resize a bitmap control.
     case ID_DOUBLE_SIZE:
       mult = 2;
       break;
     case ID_HALVE_SIZE:
       div = 2;
       break;
     default:
       break;
  }

  if ( mult != 1  ||  div != 1 )
  {
     // The view port is sizing the bitmap to its minimum size,
     // so change the minimum size and the view port will
     // automatically change its size to match.
     ( *clBitmap )
      .setMinimumSize( clBitmap->minimumSize() * mult / div );
     dontPassOn = false;
  }
  return dontPassOn;
}

NewBitmapCmdHandler::NewBitmapCmdHandler ( IBitmapControl *bitmap )
  : clBitmap( bitmap )
{
  IASSERTPARM( bitmap != 0 )
}

IBase::Boolean
  NewBitmapCmdHandler::command ( ICommandEvent &event )
{
  Boolean
    dontPassOn = false;
  switch ( event.commandId() )
  {
     // Process commands to show a new bitmap.
     case ID_FOUNTAIN_BMP:
     case ID_KIDS_BMP:
     case ID_OLDBOOK_BMP:
       ( *clBitmap )
        .setBitmap( event.commandId() )
        .resetMinimumSize();
       dontPassOn = true;
       break;
     default:
       break;
  }
  return dontPassOn;
}
