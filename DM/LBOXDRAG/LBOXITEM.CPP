//************************************************************
// Direct Manipulation - List Box Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
extern "C"
  {
#ifdef __OS2__
  #define INCL_WINSYS
  #include <os2.h>
#endif
#ifdef __WINDOWS__
  #include <windows.h>
#endif
  }

#include <ilistbox.hpp>
#include <istring.hpp>
#include <ipoint.hpp>
#include <ifont.hpp>
#include <idmimage.hpp>
#include <idmevent.hpp>
#include <ihandle.hpp>
#include <itrace.hpp>
#include <igline.hpp>
#include <igpyline.hpp>
#include <igrafctx.hpp>
#include <icolor.hpp>
#include <itrace.hpp>
#include <igrect.hpp>
#include <icoordsy.hpp>

#include "lboxitem.hpp"

static const unsigned
  nil = 0xffffffffu;

ListBoxItem :: ListBoxItem ( IDMSourceOperation* srcOp,
                             IListBox*           srcLB,
                             unsigned            index )
  : IDMItem( srcOp,
             IDM::text,
             IDMItem:: moveable | IDMItem::copyable,
             none )
  {
  IMODTRACE_DEVELOP("ListBoxItem::ListBoxItem");

  // Item contents is the list-box's item text.
  this -> setContents( srcLB->itemText( index ) );
  // Item object is the item index.
  ITRACE_DEVELOP("Selected text is " + srcLB->itemText(index) );

  this -> setObject( (void*)index );
  // Try to use rfText.
  IString
    name = this -> generateSourceName(),
    rfs   = rfForThisProcess();
  if ( name.length() )
    { // Text fits; use rfText.
    this -> setSourceName( name );
    rfs += IString( "," ) + IDM::rfText;
    }
  else
    { // Text doesn't fit; use rfSharedMem instead.
    rfs += IString( "," ) + IDM::rfSharedMem;
    this -> setRequiresPreparation();
    }
  ITRACE_DEVELOP( "Rmfs is " + rfs );

  // Set up the RMFs we support.
  this -> setRMFs( rmfsFrom( IDM::rmLibrary, rfs ) );

#ifdef IC_PM
  // We support dropping on the shredder in OS/2.
  this -> addRMF( IDM::rmDiscard, IDM::rfUnknown );
#endif

  // Use text icon when a user drags the item.
  ISystemPointerHandle
    icon( ISystemPointerHandle::text );
  IDMImage
    image( icon );
  this -> setImage( image );
  }

ListBoxItem :: ListBoxItem ( const IDMItem::Handle& dragItem )
  : IDMItem( dragItem )
  {
  IMODTRACE_DEVELOP("ListBoxItem::ListBoxItem(Handle)");
  // We only support copy and move.
  this -> enableLink( false );
  }

ListBoxItem :: ~ListBoxItem ( )
  {
  IMODTRACE_DEVELOP("ListBoxItem::~ListBoxItem");
  }

Boolean ListBoxItem :: generateSourceItems( IDMSourceOperation* srcOp )
  {
  IMODTRACE_DEVELOP("ListBoxItem::generateSourceItems");
  Boolean
    result = false;
  IListBox
   *srcLB = (IListBox*)( srcOp->sourceWindow() );
  // Get index of dragged item:
  unsigned
    index = sourceIndex( srcLB, srcOp->position() );
  if ( index != nil )
    { // User not dragging from white space; add appropriate item.
    srcOp -> addItem( new ListBoxItem( srcOp, srcLB, index ) );
    srcOp -> setImageStyle( IDM::stack3AndFade );
    result = true;
    }
  return result;
  }

Boolean ListBoxItem :: targetDrop ( IDMTargetDropEvent& event )
  {
  IMODTRACE_DEVELOP("ListBoxItem::targetDrop");
  IListBox
   *tgtLB = (IListBox*)( event.window() );

  // Turn off target emphasis.
  ListBoxItemProvider
   *provider = (ListBoxItemProvider*)( tgtLB->itemProvider() );
  provider -> drawEmphasis( tgtLB, event, TgtLocation( after, nil ) );

  // Calculate where the object is dropped.
  TgtLocation
    dropLoc = targetLocation( tgtLB, event.dropPosition() );
  // Add or replace the list item, based on drop location.
  switch ( dropLoc.type )
    {
    case before:
      tgtLB -> add( dropLoc.index, contents() );
      break;
    case on:
      tgtLB -> setItemText( dropLoc.index, contents() );
      break;
    case after:
      tgtLB -> add( dropLoc.index + 1, contents() );
      break;
    }
  // If source and target are the same and the item is moved
  // forward, update source index.
  IDMTargetOperation::Handle
    tgtOp = IDMTargetOperation::targetOperation();
  if ( tgtOp->sourceWindow() == event.window()
       &&
       tgtOp->operation() == IDMOperation::move )
    {
    IDMItem::Handle
      srcItem = IDMItem::sourceItemFor( tgtOp->item( 1 ) );
    unsigned
      srcIndex = (unsigned)( srcItem->object() );
    if ( dropLoc.type != on
         &&
         dropLoc.index < srcIndex )
      srcItem->setObject( (void*)( srcIndex + 1 ) );
    }

  return true;
  }

Boolean ListBoxItem :: sourceEnd ( IDMSourceEndEvent& event )
  {
  IMODTRACE_DEVELOP("ListBoxItem::sourceEnd");
  // If the move is completed and not sent to the shredder,
  // delete the source item.
  if ( event.wasTargetSuccessful()
       &&
       (unsigned long)( object() ) != nil
       &&
       event.dragItem()->sourceOperation()->operation() != IDMOperation::copy )
    {
    unsigned
      index = (unsigned)( this->object() );
    ( (IListBox*)( event.window() ) ) -> remove( index );
    }
  return true;
  }

#ifdef IC_PM
Boolean ListBoxItem :: sourceDiscard ( IDMSourceDiscardEvent& event )
  {
  IListBox
   *srcLB = (IListBox*)( event.window() );

  // Get index of the dragged item.
  unsigned
    index = (unsigned)( this->object() );

  // Delete that item.
  srcLB->remove( index );

  // Mark deleted so sourceEnd doesn't delete it again.
  setObject( (void*)nil );

  return true;
  }
#endif //IC_PM

unsigned ListBoxItem :: sourceIndex ( IListBox* pLB,
                                      const IPoint& pt )
  {
  IMODTRACE_DEVELOP("ListBoxItems::sourceIndex");

  // If there are no items, indicate no match.
  if ( pLB->isEmpty() )
    return nil;

  // Calculate index of dragged item:
  unsigned
    dy, i, row, index;

  if ( ICoordinateSystem::applicationOrientation() ==
           ICoordinateSystem::originUpperLeft )
    dy = pt.y();
  else
    dy = pLB->rect().height() - pt.y();

  i  = itemHeight(pLB);
  row = dy / i;
  index = pLB->top() + row;

  ITRACE_DEVELOP("Source index is " + IString(index) + " row is " +
    IString(row) + " item height is " +  IString(i) + " dy " +
    IString(dy) + " " + pLB->rect().asString() + pt.asString());

  // Indicate if dragging below the last item.
  if ( index >= pLB->count() )
    index = nil;

  return index;
  }

ListBoxItem::TgtLocation
  ListBoxItem :: targetLocation ( IListBox* pLB, const IPoint& pt )
  {
  // Target position is in desktop coordinates.
  // We must map this to listbox window coordinates.
  IPoint
    lbPt = IWindow::mapPoint( pt,
                              IWindow::desktopWindow()->handle(),
                              pLB->handle() );
#ifdef IC_WIN
  // fix for mapping problem on windows.
  lbPt += IPoint(1,1);
#endif

  // Get index of target item:
  unsigned
    index = sourceIndex( pLB, lbPt );
  LocType
    type = on;
  if ( index != nil )
    { // Drop at item, see if before or after:
     unsigned dy;
      if ( ICoordinateSystem::applicationOrientation() ==
              ICoordinateSystem::originUpperLeft )
       dy = lbPt.y();
     else
       dy = pLB->rect().height() - lbPt.y();
    unsigned
      i   = itemHeight(pLB),
      rem = dy % i;
    if ( rem < i/4 )
      type = before;
    else if ( rem > 3*i/4 )
      type = after;
    }
  else
    { // Drop off end.
    type = after;
    index = pLB->count() - 1;
    }
  return TgtLocation( type, index );
  }

unsigned ListBoxItem :: itemHeight( IListBox* pLB )
  {
  // Get item height presuming standard use
  // based on current font.  Note that this
  // may be wrong if the listbox is owner-draw
  // or if setHeight() is called.
  IFont
    font( pLB );
  unsigned
    result = font.maxCharHeight() + font.externalLeading();
  // Don't return 0 since that would cause divide-by-zero error.
  if ( !result )
    result++;
  return result;
  }

unsigned ListBoxItem :: verticalScrollWidth( IListBox* pLB )
  {
  // Get the vertical scroll bar's width.  For the OS/2 list box,
  // the vertical scrollbar is always visible.  For the Windows
  // list box, it is only visible when needed:  when the number of
  // items exceed the viewing area.  Note that the LBS_DISABLENOSCROLL
  // style can be included to always display the vertical scroll bar, but
  // the Open Class Library does not expose this style.
  unsigned
    result;
#ifdef IC_PM
    result = WinQuerySysValue( HWND_DESKTOP, SV_CXVSCROLL ) + 1;
#endif //IC_PM
#ifdef IC_WIN
    unsigned
      totalItemHeight = ListBoxItem::itemHeight( pLB ) * pLB->count(),
      hscrollHeight = ListBoxItem::horizontalScrollHeight( );

    if ( totalItemHeight >= (pLB->rect().top() - hscrollHeight) )
      {
        result = GetSystemMetrics( SM_CXVSCROLL ) +
                 GetSystemMetrics( SM_CXFRAME );
      }
      else
        result = GetSystemMetrics( SM_CXFRAME );
#endif //IC_WIN

  return result;
  }

#ifdef IC_WIN
unsigned ListBoxItem :: horizontalScrollHeight( )
  {
  // Get the horizontal scroll bar's height for Windows.
  return( GetSystemMetrics( SM_CYHSCROLL ) +
          GetSystemMetrics( SM_CYFRAME ) - 3 );

  }
#endif //IC_WIN

ListBoxItem::TgtLocation :: TgtLocation ( LocType type,
                                          unsigned index )
  : type( type ),
    index( index )
  {
  }

Boolean ListBoxItem::TgtLocation ::
  operator == ( const TgtLocation& loc ) const
  {
  if ( index == loc.index )
    return type == loc.type;
  else if ( index == loc.index-1 )
    return ( type == after && loc.type == before );
  else if ( index == loc.index+1 )
    return ( type == before && loc.type == after );
  else
    return false;
  }

ListBoxItemProvider :: ListBoxItemProvider ( IListBox* listBox )
  {
  if ( listBox )
    this -> provideItemsFor( listBox );
  }

ListBoxItemProvider
 &ListBoxItemProvider :: provideItemsFor( IListBox* listBox )
  {
  listBox -> setItemProvider( this );
  return *this;
  }


typedef ListBoxItem::TgtLocation TgtLocation;

static TgtLocation
  lastTarget( ListBoxItem::after, nil );


static void draw ( IGraphicContext&   gc,
                   IListBox*          lb,
                   const TgtLocation& target )
  {
  if ( target.index != nil )
    {
    // First, get offset from top of listbox:
    unsigned
      offset = target.index - lb->top() + 1,
      height = ListBoxItem::itemHeight( lb );

    // Next, adjust it if before this item:
    if ( target.type == ListBoxItem::before )
      offset--;

    // Calculate that item's rectangle's bottom, taking into account
    // the platform's coordinate system:
    unsigned
      bottom;
    if ( ICoordinateSystem::applicationOrientation()
         == ICoordinateSystem::originUpperLeft )
      {
      bottom = height * offset;
      }
    else
      {
      bottom = lb->rect().height() - height * offset;
      // Decrease bottom by 2 pels to align the emphasis.
      bottom -= 2;
      }

    // Get the width of the vertical scroll bar.
    unsigned
      vscrollWidth =
        ListBoxItem::verticalScrollWidth( lb );
#ifdef IC_WIN
    // Get the height of the horizontal scroll bar.
    unsigned
      hscrollHeight =
        ListBoxItem::horizontalScrollHeight( );
#endif

    // Draw line or box:
    IPoint
      origin( 0, bottom );
    if ( target.type == ListBoxItem::on )
      {
      IPoint
        topRight;
      if ( ICoordinateSystem::applicationOrientation()
           == ICoordinateSystem::originUpperLeft )
        {
        topRight = IPoint( lb->rect().width(), bottom - height + 2 );
        }
      else
        {
        topRight = IPoint( lb->rect().width(), bottom + height );
        }

      // Adjust the origin so the left side of the box is visible.
        origin+= IPoint( 1, 0 );

      // Adjust the end point if the vertical scroll bar is visible.
      topRight -= IPoint( vscrollWidth, 1 );

#ifdef IC_WIN
      // Do not draw emphasis over the horizontal scroll bar.
      IPoint
        bottomLeft( origin.x(),
                    lb->rect().top() - hscrollHeight - 1 );
      if ( origin.y() >= bottomLeft.y() )
        {
        IGPolyline myLine( IPointArray(4) );
        myLine.setPoint( 0, bottomLeft );
        myLine.setPoint( 1, IPoint( origin.x(), topRight.y() ) );
        myLine.setPoint( 2, topRight );
        myLine.setPoint( 3, IPoint( topRight.x(), bottomLeft.y() ) );
        myLine.drawOn( gc );
        return;
        }
#endif //IC_WIN

      IRectangle theBox( origin, topRight );
      IGRectangle myBox( theBox  );
      myBox.drawOn( gc );
      }
    else
      {
#ifdef IC_WIN
      // Do not draw emphasis over the horizontal scroll bar.
      if ( bottom >= (lb->rect().top() - hscrollHeight - 1) )
        return;
#endif //IC_WIN

      // Adjust the end point if the vertical scroll bar is visible.
      IPoint
          end( lb->rect().width() - vscrollWidth + 1, bottom );
      IGPolyline myLine( IPointArray(2) );
      myLine.setPoint( 0, origin );
      myLine.setPoint( 1, end );
      myLine.drawOn( gc );
      }
    }
  }

ListBoxItemProvider
 &ListBoxItemProvider :: drawEmphasis ( IListBox*          listBox,
                                        IDMTargetEvent&    event,
                                        const TgtLocation& target )
  {
  // If the same target, it's already drawn.
  if ( target == lastTarget )
    return *this;

  // Get the graphic context and set the drawing attributes.
  IGraphicContext
    gc( event.presSpace() );

  gc.setMixMode( IGraphicBundle::xor );
  gc.setDrawOperation( IGraphicBundle::frame );
  gc.setPenColor( IColor::white );
  gc.setPenWidth( 1 );

  // "Undraw" current target emphasis.
  draw( gc, listBox, lastTarget );

  // Set new target and draw it.
  lastTarget = target;
  draw( gc , listBox, lastTarget );

  event.releasePresSpace();
  return *this;
  }

Boolean ListBoxItemProvider ::
  provideLeaveSupport ( IDMTargetLeaveEvent& event )
  {
  IListBox
   *listBox = (IListBox*)( event.window() );
  this -> drawEmphasis( listBox,
                        event,
                        TgtLocation( ListBoxItem::after, nil ) );
  return false;
  }

Boolean ListBoxItemProvider ::
  provideEnterSupport ( IDMTargetEnterEvent& event )

{
  IMODTRACE_DEVELOP("ListBoxItemProvider::provideEnterSupport");
  // Get default dragover result.
  Inherited::provideEnterSupport( event );

  IDMTargetOperation::Handle
    tgtOp = IDMTargetOperation::targetOperation();

  IListBox
   *lb = (IListBox*)( event.window() );

#ifdef IC_WIN
  // Do not allow drops over the scroll bars.
  // The scroll bars in Windows are not controls;
  // thus, we calculate the scroll rectangles and
  // test for hits over the scroll areas.

  // Target position is in desktop coordinates.
  // We must map this to listbox window coordinates.
  IPoint
    lbPt = IWindow::mapPoint( event.position(),
                              IWindow::desktopWindow()->handle(),
                              lb->handle() );
  // fix for mapping problem on windows.
  lbPt += IPoint(1,1);

  unsigned
    hscrollHeight = ListBoxItem::horizontalScrollHeight( ),
    vscrollWidth = ListBoxItem::verticalScrollWidth( lb );

  IRectangle hscrollRect( lb->rect().left(),
                          lb->rect().top() - hscrollHeight,
                          lb->rect().right(),
                          lb->rect().top() ),
             vscrollRect( lb->rect().right() - vscrollWidth + 3,
                          lb->rect().bottom(),
                          lb->rect().right(),
                          lb->rect().top() - hscrollHeight );
  if ( hscrollRect.contains( lbPt ) ||
       vscrollRect.contains( lbPt ) )
    {
    event.setDropIndicator( IDM::notOk );
    // Undraw any existing target emphasis.
    drawEmphasis( lb,
                  event,
                  TgtLocation( ListBoxItem::after, nil ) );
    return true;
    }
#endif //IC_WIN

  ListBoxItem::TgtLocation
    tgtLocation
      = ListBoxItem::targetLocation( lb, event.position() );

  if ( event.dropIndicator() == IDM::ok
       &&
       tgtOp->sourceWindow() == event.window() )
  { // If source equals target, prohibit dropping on same item.
    IDMItem::Handle
      srcItem = IDMItem::sourceItemFor( tgtOp->item( 1 ) );
    unsigned
      srcIndex = (unsigned)( srcItem->object() );

    // Disable conflicting drop on source window:
    unsigned long
      op = tgtOp->operation();
    if ( op == IDMOperation::drag )
      op = IDMOperation::move; // Default;

    if ( op == IDMOperation::copy )
    { // Can't copy to self.
      if ( (srcIndex == tgtLocation.index)
           &&
           tgtLocation.type == ListBoxItem::on )
        event.setDropIndicator( IDM::notOk );
    }
    else if ( op == IDMOperation::move )
    { // No sense moving to same place.
      if ( (srcIndex == tgtLocation.index)
           ||
           ( tgtLocation.type == ListBoxItem::before
             &&
             srcIndex == tgtLocation.index - 1 )
           ||
           ( tgtLocation.type == ListBoxItem::after
             &&
             srcIndex == tgtLocation.index + 1 ) )
      {
        event.setDropIndicator( IDM::notOk );
      }
    }
  }

  // Draw target emphasis:
  drawEmphasis( lb, event, tgtLocation );

  return true;
  }

ListBoxItemProvider *ListBoxItemProvider :: operator & ()
  {
  return this;
  }
