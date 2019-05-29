//************************************************************
// Advanced Frame - Window Viewer Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <ipopmenu.hpp>
#include "hwinobj.hpp"
#include "iconview.hpp"
#include "infoview.hpp"
#include "winview.h"

HWindowObject::HWindowObject( const HWindow&     hwindow,
                              unsigned long      iconId,
                              IContainerControl* cnr )
  : IContainerObject( IString(), iconId ),
    objCnr( cnr ),
    ficonView( 0 ),
    finfoView( 0 ),
    fhwindow( hwindow )
{
   IString wintext = hwindow.text();
   if ( wintext.length() > 20 )
      wintext.remove(21);
   wintext = hwindow.asHexString() + IString(" \"") + wintext +
             IString("\"");
   this->setIconText( wintext );
}

HWindowObject::~HWindowObject()
{
  if (ficonView)
     ficonView->invalidateObject();
  if (finfoView)
     finfoView->invalidateObject();
}

HWindowObject& HWindowObject::openIconView( )
{
   this->iconView().open();
   return *this;
}

HWindowObject& HWindowObject::openInfoView( )
{
   this->infoView().open();
   return *this;
}

// This function is called by the container handler
// when the object is double-clicked.  Open the icon
// view if it is available; otherwise, open the
// information view.
void HWindowObject::handleOpen ( IContainerControl* )
{
   if (this->isIconViewAvailable() )
     this->iconView().open();
   else
     this->infoView().open();
}

HWindowObjectView& HWindowObject::iconView ( )
{
  if ( !ficonView )
    {
    ficonView = this -> newIconView();
    }
  return *ficonView;
}

HWindowObjectView& HWindowObject::infoView ( )
{
  if ( !finfoView )
    {
    finfoView = this -> newInfoView();
    }
  return *finfoView;
}

// Icon view is available as long as the object has children.
Boolean HWindowObject::isIconViewAvailable( ) const
{
  IContainerControl::ObjectCursor cursor( *(this->container()),
                                           this);
  return cursor.setToFirst() ;
}

// This function allocates a new icon view.
HWindowObjectView* HWindowObject::newIconView ( )
{
  HWindowObjectView* view = new IconView( *this );
  return view;
}

// This function allocates a new info view.
HWindowObjectView* HWindowObject::newInfoView ( )
{
  HWindowObjectView* view = new InfoView( *this );
  return view;
}

HWindowObject& HWindowObject::viewClosed( HWindowObjectView* view )
{
  if (view == this->finfoView)
     this->finfoView = 0;
  if (view == this->ficonView)
     this->ficonView = 0;
  return *this;
}

IContainerControl* HWindowObject::container ( ) const
{
  return objCnr;
}

const HWindow& HWindowObject::hWindow( ) const
{
  return fhwindow;
}

HWindowObjectView& HWindowObjectView::open ( )
{
  if ( isMinimized() )
    restore();
  setFocus();
  show();
  return *this;
}

HWindowObjectView::HWindowObjectView ( IWindow*       client,
                                       HWindowObject& object,
                                       const IString& viewName )
  : IFrameWindow( 0, 0, object.container()->parent(),
                  nextShellRect().scaleBy( 0.5, 0.5 ),
                  classDefaultStyle | noMoveWithOwner ),
    viewTitle( this ),
    viewObj( &object )
{
  viewTitle.setObjectText( object.iconText() );
  viewTitle.setViewText( viewName );
  setIcon( object.icon() );
  setClient( client );
  client->setOwner( this );
  setAutoDeleteObject( true );
}

HWindowObjectView::~HWindowObjectView ( )
{
  if ( viewObj )
    viewObj -> viewClosed( this );
}

HWindowObject* HWindowObjectView::object ( ) const
{
  return viewObj;
}

HWindowObjectView& HWindowObjectView::invalidateObject ( )
{
  viewTitle.setObjectText("<invalid>");
  viewObj = 0;
  return *this;
}

MenuHandler::MenuHandler( ) :
  ICnrMenuHandler( )
{ }

IBase::Boolean   MenuHandler::makePopUpMenu( IMenuEvent& event )
{
  Boolean result = false;
  IContainerControl* pcnr =
     (IContainerControl*)(event.dispatchingWindow());
  IContainerObject* pobj = popupMenuObject();
  if (pcnr && pobj)
    {
    pcnr->setCursor( pobj );
    IPopUpMenu* popup = new IPopUpMenu(POPUP_MENU, pcnr);
    popup->setAutoDeleteObject();
    popup->show(event.mousePosition());
    result = true;
    }
  return result;
}

