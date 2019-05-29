//*********************************************************
// Canvas - ISetCanvas Pack Options
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//*********************************************************
#include "packcv.hpp"
#include <icconst.h>
#include "packcv.h"

PackCanvas::PackCanvas ( unsigned long id,
                         IWindow* parentAndOwner,
                         ISetCanvas::PackType pack )
  : ISetCanvas( id, parentAndOwner, parentAndOwner ),
    first(  1, this, this),
    second( 2, this, this),
    third(  3, this, this),
    fourth( 4, this, this),
    fifth(  5, this, this),
    sixth(  6, this, this)
{
  (*this)
   .setPackType( pack )
   .setDeckCount( 2 );
  switch ( pack )
  {
    case ISetCanvas::tight:
       this->setText( "Pack tight" );
       break;
    case ISetCanvas::even:
       this->setText( "Pack even" );
       break;
    case ISetCanvas::expanded:
    default:
       this->setText( "Pack expanded" );
       break;
  }
  first
   .setMinimumSize( ISize( 30, 25 ) );
  second
   .setMinimumSize( ISize( 15, 40 ) );
  third
   .setMinimumSize( ISize( 35, 65 ) );
  fourth
   .setMinimumSize( ISize( 40, 35 ) );
  fifth
   .setMinimumSize( ISize( 30, 20 ) );
  sixth
   .setMinimumSize( ISize( 20, 60 ) );
}

PackAlignTest::PackAlignTest ( )
  : IFrameWindow( "ISetCanvas Pack Options" ),
    packClient( IC_FRAME_CLIENT_ID, this, this ),
    tight( 1, &packClient, ISetCanvas::tight ),
    even( 2, &packClient, ISetCanvas::even ),
    expanded( 3, &packClient, ISetCanvas::expanded ),
    cmdHdr( this ),
    toolBar( 0, this ),
    topLeft( ID_TOP_LEFT, &toolBar, &toolBar,
             IRectangle(),
             IToolBarButton::classDefaultStyle
              | IToolBarButton::autoLatch ),
    topCenter( ID_TOP_CENTER, &toolBar, &toolBar,
               IRectangle(),
               IToolBarButton::classDefaultStyle
                | IToolBarButton::autoLatch ),
    topRight( ID_TOP_RIGHT, &toolBar, &toolBar,
              IRectangle(),
              IToolBarButton::classDefaultStyle
               | IToolBarButton::autoLatch ),
    centerLeft( ID_CENTER_LEFT, &toolBar, &toolBar,
                IRectangle(),
                IToolBarButton::classDefaultStyle
                 | IToolBarButton::autoLatch ),
    centerCenter( ID_CENTER_CENTER, &toolBar, &toolBar,
                  IRectangle(),
                  IToolBarButton::classDefaultStyle
                   | IToolBarButton::autoLatch ),
    centerRight( ID_CENTER_RIGHT, &toolBar, &toolBar,
                 IRectangle(),
                 IToolBarButton::classDefaultStyle
                  | IToolBarButton::autoLatch ),
    bottomLeft( ID_BOTTOM_LEFT, &toolBar, &toolBar,
                IRectangle(),
                IToolBarButton::classDefaultStyle
                 | IToolBarButton::autoLatch ),
    bottomCenter( ID_BOTTOM_CENTER, &toolBar, &toolBar,
                  IRectangle(),
                  IToolBarButton::classDefaultStyle
                   | IToolBarButton::autoLatch ),
    bottomRight( ID_BOTTOM_RIGHT, &toolBar, &toolBar,
                 IRectangle(),
                 IToolBarButton::classDefaultStyle
                  | IToolBarButton::autoLatch )
{
  packClient
   .setDeckOrientation( ISetCanvas::horizontal );
  cmdHdr
   .handleEventsFor( this );

  // Set up the tool bar.
  toolBar
   .addAsFirst( &topLeft, true )
   .addAsLast( &topCenter )
   .addAsLast( &topRight )
   .addAsLast( &centerLeft )
   .addAsLast( &centerCenter )
   .addAsLast( &centerRight )
   .addAsLast( &bottomLeft )
   .addAsLast( &bottomCenter )
   .addAsLast( &bottomRight );

  // Set up the tool bar buttons.
  topLeft
   .setBitmap( ID_TOP_LEFT );
  topCenter
   .setBitmap( ID_TOP_CENTER );
  topRight
   .setBitmap( ID_TOP_RIGHT );
  centerLeft
   .setBitmap( ID_CENTER_LEFT );
  centerCenter
   .setBitmap( ID_CENTER_CENTER );
  centerRight
   .setBitmap( ID_CENTER_RIGHT );
  bottomLeft
   .setBitmap( ID_BOTTOM_LEFT );
  bottomCenter
   .setBitmap( ID_BOTTOM_CENTER );
  bottomRight
   .setBitmap( ID_BOTTOM_RIGHT );

  // Size and position the window now.
  (*this)
   .setClient( &packClient )
   .moveSizeToClient( IRectangle( IPoint( 50, 50 ),
                                  packClient.minimumSize() ) );
}

PackAlignTest& PackAlignTest::alignGrandChildren
                                ( ISetCanvas::Alignment align )
{
  tight
   .setAlignment( align );
  even
   .setAlignment( align );
  expanded
   .setAlignment( align );
  return *this;
}

IBase::Boolean PackAlignTest::CmdHandler::command
                                     ( ICommandEvent& event )
{
  Boolean
    dontPassOn = false;
  ISetCanvas::Alignment
    align = ISetCanvas::bottomRight;

  switch ( event.commandId() )
  {
     case ID_TOP_LEFT:
       align = ISetCanvas::topLeft;
       dontPassOn = true;
       break;
     case ID_TOP_CENTER:
       align = ISetCanvas::topCenter;
       dontPassOn = true;
       break;
     case ID_TOP_RIGHT:
       align = ISetCanvas::topRight;
       dontPassOn = true;
       break;
     case ID_CENTER_LEFT:
       align = ISetCanvas::centerLeft;
       dontPassOn = true;
       break;
     case ID_CENTER_CENTER:
       align = ISetCanvas::centerCenter;
       dontPassOn = true;
       break;
     case ID_CENTER_RIGHT:
       align = ISetCanvas::centerRight;
       dontPassOn = true;
       break;
     case ID_BOTTOM_LEFT:
       align = ISetCanvas::bottomLeft;
       dontPassOn = true;
       break;
     case ID_BOTTOM_CENTER:
       align = ISetCanvas::bottomCenter;
       dontPassOn = true;
       break;
     case ID_BOTTOM_RIGHT:
     default:
       dontPassOn = true;
       break;
  }

  if ( dontPassOn )
  {
     clWindow->alignGrandChildren( align );
  }
  return dontPassOn;
}
