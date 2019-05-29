//*********************************************************
// Direct Manipulation - Drag Information Viewer
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//*********************************************************
#include <ibase.hpp>
#include <iframe.hpp>
#include <imle.hpp>
#include <idmrendr.hpp>
#include <idmhndlr.hpp>
#include <idmevent.hpp>
#include <idmprov.hpp>
#include <idmimage.hpp>
#include <idmcomm.hpp>
#include <itrace.hpp>
#include "dragview.hpp"
#include "dragview.h"

/*------------------------------------------------------------------------------
| main                                                                         |
------------------------------------------------------------------------------*/
int main()
  {
  // Create the frame window.
  IFrameWindow
    frame( "Drag Information Viewer", WND_MAIN );

  // Create the MLE.
  IMultiLineEdit
    mle( 1000, &frame, &frame, IRectangle(),
         IMultiLineEdit::defaultStyle()  &
         ~IMultiLineEdit::wordWrap       |
         IMultiLineEdit::horizontalScroll );

  // Replace default target renderer with the viewer target renderer.
  DragViewTargetRenderer
    targetRenderer;
  IDMRenderer::setDefaultTargetRenderer( targetRenderer );

  // Enable the MLE as a target.
  IDMHandler::enableDropOn( &mle );

  // Construct and set the item provider for the drag viewer item.
  IDMItemProviderFor< DragViewItem >
    itemProvider;

  mle.setItemProvider( &itemProvider );

  frame
    .setClient( &mle )
    .sizeTo( ISize(350, 300) )
    .setFocus()
    .show();

  IApplication::current().run();
  return 0;
  }


DragViewItem::DragViewItem( const IDMItem::Handle& item )
    : IDMItem( item )
  {
  IMODTRACE_DEVELOP( "DragViewItem::DragViewItem" );
  }


DragViewItem :: ~DragViewItem()
  {
  IMODTRACE_DEVELOP( "DragViewItem::~DragViewItem" );
  }


Boolean DragViewItem :: targetDrop( IDMTargetDropEvent& event )
  {
  IMODTRACE_DEVELOP( "DragViewItem::targetDrop" );

  // Determine via the rendering mechanism if this item represents
  // an Open Class Library object.
  if ( rmfs().includes( IDM::rmLibrary ) )
    displayIOCItem( event );
  else
    displayItem( event );

  return(true);
  }


DragViewItem& DragViewItem::displayIOCItem( IDMTargetDropEvent& event )
  {
  IDMTargetOperation::Handle
    pTgtOperH = IDMTargetOperation::targetOperation();
  IMultiLineEdit
   *pMLE = (IMultiLineEdit *)pTgtOperH->targetWindow();
   IString
     operation,
     imageStyle;

  if ( pTgtOperH->operation() == IDMOperation::drag )
    operation = "drag";
  else if ( pTgtOperH->operation() == IDMOperation::move )
    operation = "move";
  else if ( pTgtOperH->operation() == IDMOperation::copy )
    operation = "copy";
  else if ( pTgtOperH->operation() == IDMOperation::link )
    operation = "link";
  else
    operation = "unknown";

  if ( image().style() & IDMImage::bmp )
    imageStyle = "Bitmap";
  else if ( image().style() & IDMImage::ptr )
    imageStyle = "Icon";
  else if ( image().style() & IDMImage::polygon )
    imageStyle = "Polygon";
  else
    imageStyle = "Unknown";

  pMLE->add( "******  Open Class Library Drag  ******" )
       .add( "\r\n  Target Operation" )
       .add( IString( "\r\n    >> operation = " + operation ) )
       .add( "\r\n  Target Item" )
       .add( IString( "\r\n    >> Source window = " +
                             sourceWindowHandle().asString().d2x() ) )
       .add( IString( "\r\n    >> Directory = " + containerName() ) )
       .add( IString( "\r\n    >> File name = " + sourceName() ) )
       .add( IString( "\r\n    >> Target name (suggested) = " + targetName() ) )
       .add( IString( "\r\n    >> Types = " + types() ) )
       .add( IString( "\r\n    >> RMFs = " + rmfs() ) )
       .add( IString( "\r\n    >> object = " +
                             IString( (unsigned long)object() ).d2x() ) )
       .add( IString( "\r\n    >> contents = " + contents() ) )
       .add( "\r\n  Drag Image" )
       .add( IString( "\r\n    >> style = " + imageStyle ) )
       .add( "\r\n  Target Drop Event" )
       .add( IString( "\r\n    >> target info = " +
                             IString( event.targetInfo() ) ) )
       .add( IString( "\r\n    >> drop position = " +
                             event.dropPosition().asString() ) )
       .add( "\r\n---------------------------------------" )
       .add( "\r\n\r\n" );

  return( *this );
  }


DragViewItem& DragViewItem::displayItem( IDMTargetDropEvent& event )
  {
  IDMTargetOperation::Handle
    pTgtOperH = IDMTargetOperation::targetOperation();
  IMultiLineEdit
   *pMLE = (IMultiLineEdit *)pTgtOperH->targetWindow();
   IString
     operation,
     imageStyle;

  if ( pTgtOperH->operation() == IDMOperation::drag )
    operation = "drag";
  else if ( pTgtOperH->operation() == IDMOperation::move )
    operation = "move";
  else if ( pTgtOperH->operation() == IDMOperation::copy )
    operation = "copy";
  else if ( pTgtOperH->operation() == IDMOperation::link )
    operation = "link";
  else
    operation = "unknown";

  if ( image().style() & IDMImage::bmp )
    imageStyle = "Bitmap";
  else if ( image().style() & IDMImage::ptr )
    imageStyle = "Icon";
  else if ( image().style() & IDMImage::polygon )
    imageStyle = "Polygon";
  else
    imageStyle = "Unknown";

  pMLE->add( "******  Desktop Drag  ******" )
       .add( "\r\n  Target Operation" )
       .add( IString( "\r\n    >> operation = " + operation ) )
       .add( "\r\n  Target Item" )
       .add( IString( "\r\n    >> Source window = " +
                             sourceWindowHandle().asString().d2x() ) )
       .add( IString( "\r\n    >> Directory = " + containerName() ) )
       .add( IString( "\r\n    >> File name = " + sourceName() ) )
       .add( IString( "\r\n    >> Target name (suggested) = " + targetName() ) )
       .add( IString( "\r\n    >> Types = " + types() ) )
       .add( IString( "\r\n    >> RMFs = " + rmfs() ) )
       .add( "\r\n  Drag Image" )
       .add( IString( "\r\n    >> style = " + imageStyle ) )
       .add( "\r\n  Target Drop Event" )
       .add( IString( "\r\n    >> target info = " +
                             IString( event.targetInfo() ) ) )
       .add( IString( "\r\n    >> drop position = " +
                             event.dropPosition().asString() ) )
       .add( "\r\n---------------------------------------" )
       .add( "\r\n\r\n" );

  return( *this );
  }


DragViewTargetRenderer::DragViewTargetRenderer( )
  {
  }


DragViewTargetRenderer::~DragViewTargetRenderer( )
  {
  }


IDM::DropIndicator DragViewTargetRenderer::
                   canRender( const IDMItem::Handle& )
  {
  return(IDM::ok);
  }


DragViewTargetRenderer& DragViewTargetRenderer::
                        targetRender( IDMTargetDropEvent&    event,
                                      const IDMItem::Handle& dragItem )
  {
  IMODTRACE_DEVELOP( "DragViewTargetRenderer::targetRender" );

  // Call targetDrop override for the drag viewer item.
  Boolean
    bRc = dragItem->targetDrop( event );

  // Indicate to the source that rendering of the item has completed.
  informSourceOfCompletion( dragItem, ((bRc) ? IDM::targetSuccessful
                                             : IDM::targetFailed) );

  return( *this );
  }
