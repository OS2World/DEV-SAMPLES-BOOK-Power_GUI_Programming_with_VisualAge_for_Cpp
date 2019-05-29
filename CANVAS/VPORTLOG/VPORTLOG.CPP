//*********************************************************
// Canvas - IViewPort with Logically-sized View Window
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//*********************************************************
#include <iapp.hpp>
#include <icconst.h>
#include <icolor.hpp>
#include <icoordsy.hpp>
#include <ifont.hpp>
#include <iframe.hpp>
#include <igbundle.hpp>
#include <igline.hpp>
#include <iglist.hpp>
#include <igrect.hpp>
#include <igstring.hpp>
#include <ipoint.hpp>
#include <iscroll.hpp>
#include <istring.hpp>

#include "vportlog.hpp"

// #define ORIGIN_UPPER_LEFT  1    // Comment out to use lower left.

#define NUMBER_COLORS  8
static IColor::Color colorEnums[ NUMBER_COLORS ] =
  { IColor::blue, IColor::darkGreen, IColor::red,
    IColor::darkCyan, IColor::pink, IColor::darkRed,
    IColor::brown, IColor::black };

//=================== LogicalSizeViewPort =====================

LogicalSizeViewPort::LogicalSizeViewPort
                       ( unsigned long windowId,
                          IWindow* parentAndOwner,
                          unsigned long scale,
                          Boolean  specialScrolling )
  : IViewPort( windowId, parentAndOwner,
               parentAndOwner, IRectangle(),
               IViewPort::classDefaultStyle
                 | IViewPort::noViewWindowFill ),
    clViewWindow( windowId, this, this ),
    clGraphicList( new IGList() ),
    clCustomScrolling( false )
{
  // Physically size the view window to the size of the
  // screen, and leave it positioned at (0, 0).
  ISize
    desktopSize = IWindow::desktopWindow()->size();
  clViewWindow
   .setBackgroundColor( IColor::black )
   .sizeTo( desktopSize );

  // Logically size the view window using the scaling factor.
  ISize
    logicalSize( 0x4000 * scale, 0x8000 * scale );
  if ( scale == 0 )
  {                     // <32K logical sizes.
     logicalSize = ISize( 0x4000, 0x7FFF );
  }
  this->setViewWindowSize( logicalSize );

  // Increase the "line" scroll amounts by four times.
  IScrollBar
   *horz = this->horizontalScrollBar(),
   *vert = this->verticalScrollBar();
  (*horz)
   .setMinScrollIncrement( horz->minScrollIncrement() * 4 );
  (*vert)
   .setMinScrollIncrement( vert->minScrollIncrement() * 4 );

  // Also change the page scroll amounts?
  if ( specialScrolling )
  {           // Set a flag to be used in setupScrollBars.
     clCustomScrolling = true;
  }
} // LogicalSizeViewPort ctor

LogicalSizeViewPort::~LogicalSizeViewPort ( )
{
  this->cleanUpGraphicList();
  delete clGraphicList;
}

LogicalSizeViewPort& LogicalSizeViewPort::setupScrollBars ( )
{
  this->IViewPort::setupScrollBars();

  // Modify the page scrolling amounts if necessary.  We do this
  // here because IViewPort::setupScrollBars resets the page
  // scroll amounts to their default values in logical size
  // units when the logical view window size exceeds 32K.
  // Otherwise, the scroll bars would do page scrolling using
  // scaled values instead of logical values.
  if ( clCustomScrolling )
  {
     IScrollBar
      *horz = this->horizontalScrollBar(),
      *vert = this->verticalScrollBar();
     (*horz)
      .setPageScrollIncrement
           ( horz->pageScrollIncrement() / 2 );
     (*vert)
      .setPageScrollIncrement
           ( vert->pageScrollIncrement() / 2 );
  }

  return *this;
}

LogicalSizeViewPort& LogicalSizeViewPort::positionViewWindow
                            ( const IWindowHandle& viewWindow,
                              const IRectangle& viewRectangle )
{
  // Do not call IViewPort::positionViewWindow, which scrolls
  // the window.

  // Prepare the view window so it appears to scroll when it
  // paints; then force it to paint.
  this->buildGraphicList();
  clViewWindow
   .refresh();

  return *this;
}

LogicalSizeViewPort& LogicalSizeViewPort::buildGraphicList ( )
{
  this->cleanUpGraphicList();   // Empty previous contents.

  // Initialize drawing variables.
  unsigned long
    blockWidth  = 0x0100,           // 256
    verticalLabelSpacing = 0x0080,  // 128
    fontHeight = IFont( this ).maxCharHeight();
  IGraphicBundle
    colorBlockBundle,
    dividerBundle,
    offsetTextBundle;
  colorBlockBundle
   .setBackgroundMixMode( IGraphicBundle::backOverPaint )
   .setDrawOperation( IGraphicBundle::fill );
  dividerBundle
   .setPenColor( IColor::yellow )
   .setPenWidth( 1 );
  offsetTextBundle
   .setPenColor( IColor::yellow );

  // Figure out where we are so we can do width-dependent
  // painting of colors and horizontal offsets.  Because the
  // drawing canvas is only being logically scrolled, its size
  // and position do not change.  However, the view port tells
  // us where it considers the drawing canvas to be.  The
  // portion that it considers visible is what we store in
  // logicalVisibleRect.  What is actually visible is in
  // trueVisibleRect.
  IRectangle
    logicalVisibleRect = this->viewWindowDrawRectangle(),
    trueVisibleRect = logicalVisibleRect.movedTo( IPoint() );
  long
    x = logicalVisibleRect.minX();
  unsigned long
    xIndex = x / blockWidth;   // Which block of color?

  // Create the background blocks of color, their dividers, and
  // their their labels from left to right.
  while ( x < logicalVisibleRect.maxX() )
  {
    // Create a block of color that fills the entire height.
    IColor
      bgColor( colorEnums[ xIndex % NUMBER_COLORS ] );
    unsigned long
      x2 = (xIndex + 1) * blockWidth - 1;
    Boolean
      rightEdge = true;
    if ( x2 > logicalVisibleRect.maxX() )
    {         // Right edge of block is clipped.
       x2 = logicalVisibleRect.maxX();
       rightEdge = false;
    }
    IRectangle
      colorRect( IPoint( x - logicalVisibleRect.minX(),
                         trueVisibleRect.minY() ),
                 IPoint( x2 - logicalVisibleRect.minX(),
                         trueVisibleRect.maxY() ) );
    IGRectangle
     *colorBlock = new IGRectangle( colorRect );
    colorBlockBundle
     .setFillColor( bgColor );
    ( *colorBlock )
     .setGraphicBundle( colorBlockBundle );
    ( *clGraphicList )
     .addAsLast( *colorBlock );

    // Create a divider between this and the next block of color.
    if ( rightEdge )
    {                // Right edge is visible.
       IGLine
        *divider =
           new IGLine( IPoint( x2 - logicalVisibleRect.minX(),
                               trueVisibleRect.minY() ),
                       IPoint( x2 - logicalVisibleRect.minX(),
                               trueVisibleRect.maxY() ) );
       ( *divider )
        .setGraphicBundle( dividerBundle );
       ( *clGraphicList )
        .addAsLast( *divider );
    }

    // Create a label at the left edge of the color block for
    // the logical horizontal offset.
    if ( ! ( x % blockWidth ) )
    {         // The left edge of the color block is showing.
       IGString
        *offset =
           new IGString( IString( xIndex * blockWidth ),
#ifdef ORIGIN_UPPER_LEFT
                         IPoint( x - logicalVisibleRect.minX(),
                                 trueVisibleRect.maxY() -
                                   fontHeight ) );
#else
                         IPoint( x - logicalVisibleRect.minX(), 0 ) );
#endif
       ( *offset )
        .setGraphicBundle( offsetTextBundle );
       ( *clGraphicList )
        .addAsLast( *offset );
    }

    x = x2 + 1;
    xIndex++;
  }

  // Figure out where we are so we can do height-dependent
  // painting of the vertical offsets.
  long
#ifdef ORIGIN_UPPER_LEFT
    y = logicalVisibleRect.minY(),
#else
    y = this->viewWindowSize().height() - logicalVisibleRect.maxY(),
#endif
    yOffsetBase = y,
    logicalVisibleBottom = y + logicalVisibleRect.height(),
    yIndex = y / verticalLabelSpacing;

  // Create labels for identifying vertical offsets from top to
  // bottom.
  while ( y < logicalVisibleBottom )
  {
    unsigned long
      y2 = (yIndex + 1) * verticalLabelSpacing;
    if ( y2 - fontHeight < logicalVisibleBottom )
    {              // This vertical offset is visible.
       IGString
        *offset =
           new IGString( IString( y2 ),
                         IPoint( 10,
#ifdef ORIGIN_UPPER_LEFT
                                 y2 - yOffsetBase - fontHeight ) );
#else
                                 trueVisibleRect.minY() +
                                   trueVisibleRect.height() -
                                   ( y2 - yOffsetBase ) ) );
#endif
       offsetTextBundle
        .setPenColor( IColor::white );
       ( *offset )
        .setGraphicBundle( offsetTextBundle );
       ( *clGraphicList )
        .addAsLast( *offset );
    }

    y = y2 + 1;
    yIndex++;
  }

  clViewWindow
   .setGraphicList( clGraphicList );

  return *this;
} // LogicalSizeViewPort::buildGraphicList

LogicalSizeViewPort& LogicalSizeViewPort::cleanUpGraphicList ( )
{
  // Clean out the contents of the graphic list.
  unsigned long
    count = clGraphicList->numberOfGraphics();
  while ( count-- )
  {
    IGraphic
     *graphic = clGraphicList->firstGraphic();
    clGraphicList->removeFirst();
    delete graphic;
  }
  return *this;
}

//========================== Main =============================

void main( int argc, char *argv[] )
{
#ifdef ORIGIN_UPPER_LEFT
  ICoordinateSystem::setApplicationOrientation
                        ( ICoordinateSystem::originUpperLeft );
#else
  ICoordinateSystem::setApplicationOrientation
                        ( ICoordinateSystem::originLowerLeft );
#endif

  // This .exe take two optional command line arguments.
  // The first is a "scale" value, which specifies the multiples
  // of 0x4000 for width and 0x8000 for height that the view
  // port should logically size its view window.  A value of
  // zero means to use (0x4000, 0x7FFF), so that IViewPort does
  // not need to use special processing to emulate scrolling
  // beyond the limits of the scroll bar.  The default is to use
  // 0x4000 x 0x8000.
  // A second argument means that the default scroll amounts
  // should not be used.
  long
    scale = 1;
  Boolean
    specialScrolling = false;

  if ( argc > 1 )
  {                     // First argument is scale.
     scale = IString( argv[1] ).asInt();
     if ( scale < 0 )
     {                  // Valid values are 0 or greater.
        scale = 1;      // 1 is default.
     }
     if ( argc > 2 )
     {                  // Second command line argument.
        specialScrolling = true;
     }
  }

  // Create the frame window and its client view port.
  IFrameWindow
    frame( "View Port with Logically-Sized View Window" );
  LogicalSizeViewPort
    vport( IC_FRAME_CLIENT_ID, &frame,
           scale, specialScrolling );

  // Show it all now.
  frame
   .setFocus()
   .show();

  IApplication::current().run();
}
