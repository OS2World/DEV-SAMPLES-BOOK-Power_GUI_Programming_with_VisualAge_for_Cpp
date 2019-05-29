//************************************************************
// Advanced Frame - Frame Extension Drawing Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <icoordsy.hpp>
#include <igrafctx.hpp>
#include <igrect.hpp>
#include <irect.hpp>
#include "myextns.hpp"

MyExtension::MyExtension( IWindow *control,
                          IFrameWindow::Location loc )
    : IFrameExtension( control, loc, IFrameWindow::none ),
      width( 5 ),
      color( IColor::white )
    {
    }

MyExtension::MyExtension( IWindow *control,
               IFrameWindow::Location loc,
               double size )
    : IFrameExtension( control, loc, size, IFrameWindow::none ),
      width( 5 ),
      color( IColor::white )
    {
    }

MyExtension::MyExtension( IWindow *control,
               IFrameWindow::Location loc,
               int size )
    : IFrameExtension( control, loc, (unsigned long)size,
                       IFrameWindow::none ),
      width( 5 ),
      color( IColor::white )
    {
    }

unsigned long MyExtension:: separatorWidth ( ) const
  {
  return width;
  }
void MyExtension::drawSeparator ( const IPresSpaceHandle &hps )
  {
  IRectangle
    separator;
  Boolean isUpperLeft =
     (ICoordinateSystem::nativeOrientation() ==
      ICoordinateSystem::originUpperLeft );

  if ( location() == IFrameWindow::aboveClient)
     // Puts separator beneath control.
     separator = control()->nativeRect()
        .moveBy( IPair( 0, isUpperLeft ?
                           control()->size().height() : -width) );
  else
    // Puts separator above control.
    separator = control()->nativeRect()
       .moveBy( IPair( 0, isUpperLeft ?
                          -width : control()->size().height()) );

  separator.sizeTo( separator.size().setHeight( width-1 ) );
  // Draw the separator.   Don't draw it if width is 0.
  if (width != 0)
     {
     IGraphicContext gc(hps);
     gc.setFillColor(color);
     gc.setPenColor(color);
     gc.draw( IGRectangle( separator ) );
     }
  }

MyExtension& MyExtension::setSeparatorWidth ( unsigned long width )
  {
  this->width = width;
  return *this;
  }

MyExtension& MyExtension::setSeparatorColor (
                             const IColor& newColor )
{
  this->color = newColor;
  return *this;
}
