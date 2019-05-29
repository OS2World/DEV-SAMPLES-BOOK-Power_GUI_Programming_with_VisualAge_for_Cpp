//*********************************************************
// Reusable Handlers - Paint Handler
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc.
// All Rights Reserved.
//*********************************************************
#include <iframe.hpp>
#include <igbundle.hpp>
#include <igline.hpp>
#include <igrafctx.hpp>
#include <igrect.hpp>
#include <igregion.hpp>
#include <ihandle.hpp>
#include <imcelcv.hpp>
#include <ipainhdr.hpp>
#include <ipushbut.hpp>
#include <istattxt.hpp>
#include <istring.hpp>

class InvertHalfPaintHandler : public IPaintHandler {
protected:
virtual Boolean
  paintWindow ( IPaintEvent& event );
}; // InvertHalfPaintHandler

IBase::Boolean
  InvertHalfPaintHandler::paintWindow ( IPaintEvent& event )
{
  // This paint handler paints the left half of a window by
  // inverting its contents.
  IWindow
   *windowToPaint = event.dispatchingWindow();
  IRectangle
    leftHalf( windowToPaint->rect()
               .moveTo( IPoint() )
               .scaleBy( 0.5, 1 ) );
  IRectangle
    paintArea( event.rect() & leftHalf );

  // First let the window paint its contents.
  (*windowToPaint)
   .dispatchRemainingHandlers( event, true );

  // See if any part of the left half needs painting.
  if ( paintArea.size() > ISize() )
  {      // Something needs painting.
     // Reset the clip region, in case the window cleared
     // it as part of its painting.
     IGraphicContext
       gc( event.presSpaceHandle() );
     IGRegion
       paintRegion( gc, paintArea );
     gc
      .setClipRegion( paintRegion );

     // Do the XOR paint now.
     IGraphicBundle
       bundle( gc );
     bundle
      .setDrawOperation( IGraphicBundle::fill )
      .setMixMode( IGraphicBundle::xor )
      .setFillColor( IColor::yellow );
     IGRectangle
       grect( paintArea );
     grect
      .setGraphicBundle( bundle );
     grect
      .drawOn( gc );
  }
  return true;
}

class XWindowPaintHandler : public IPaintHandler {
public:
protected:
virtual Boolean
  paintWindow ( IPaintEvent& event );
};  // XWindowPaintHandler

IBase::Boolean
  XWindowPaintHandler::paintWindow ( IPaintEvent& event )
{
  IWindow
   *windowToPaint = event.dispatchingWindow();

  // Save the clip region in case the window clears it
  // as part of its painting.
  IGraphicContext
    gc( event.presSpaceHandle() );
  IRegionHandle
    origClipRegion( gc.clipRegion() );

  // Let the window paint its contents.
  (*windowToPaint)
   .dispatchRemainingHandlers( event, true );

  // Reset the clip region in case the window cleared it
  // as part of its painting.
  gc
   .setClipRegion( origClipRegion );

  // Now draw the two diagonal red lines.
  IRectangle
    windowRect( windowToPaint->rect().moveTo( IPoint() ) );
  IGLine
    diag1( windowRect.bottomLeft(), windowRect.topRight() ),
    diag2( windowRect.bottomRight(), windowRect.topLeft() );
  IGraphicBundle
    bundle( gc );
  bundle
   .setMixMode( IGraphicBundle::overPaint )
   .setPenType( IGraphicBundle::solid )
   .setPenEndingStyle( IGraphicBundle::rounded )
   .setPenWidth( 2 )
   .setPenColor( IColor::red );
  diag1
   .setGraphicBundle( bundle )
   .drawOn( gc );
  diag2
   .setGraphicBundle( bundle )
   .drawOn( gc );

  return true;
}

void main ( )
{
  IFrameWindow
    frame( "Paint Handler Example" );

  // Create the client area.
  IMultiCellCanvas
    client( IC_FRAME_CLIENT_ID, &frame, &frame );
  frame
   .setClient( &client );

  IStaticText
    text1( 1, &client, &client ),
    text2( 2, &client, &client );
  text1
   .setText( "Standard static text" );
  text2
   .setText( "Static text with a paint handler" );

  IPushButton
    button1( 3, &client, &client ),
    button2( 4, &client, &client );
  button1
   .setText( "Standard push button" )
   .enableTabStop()
   .enableGroup();
  button2
   .setText( "Push button with a paint handler" )
   .enableTabStop();

  client
   .addToCell( &text1,   2, 2 )
   .addToCell( &text2,   2, 4 )
   .addToCell( &button1, 2, 6 )
   .addToCell( &button2, 2, 8 )
   .setColumnWidth( 2, 10, true )
   .setColumnWidth( 3, 10 )
   .setRowHeight( 2, 10, true )
   .setRowHeight( 4, 10, true )
   .setRowHeight( 6, 10, true )
   .setRowHeight( 8, 10, true )
   .setRowHeight( 9, 10 );

  // Construct and attach the paint handlers.
  InvertHalfPaintHandler
    invertPaintHandler;
  invertPaintHandler
   .handleEventsFor( &button2 );
  XWindowPaintHandler
    xWindowPaintHandler;
  xWindowPaintHandler
   .handleEventsFor( &text2 );

  // Show the window now.
  frame
   .moveSizeToClient( IRectangle( IPoint( 50, 50 ),
                                  ISize( client.minimumSize() ) ) )
   .setFocus()
   .show();

  IApplication::current().run();
}
