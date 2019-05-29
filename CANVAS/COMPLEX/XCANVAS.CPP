//*********************************************************
// Canvas - Complex Canvas Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc.
// All Rights Reserved.
//*********************************************************
#include <icolor.hpp>
#include <iscroll.hpp>
#include <istring.hpp>

#include "xcanvas.hpp"
#include "xcanvas.h"


//==================== ComplexCanvasWindow =====================

ComplexCanvasWindow :: ComplexCanvasWindow ( )
  : frame( "Multiple Canvas Window" ),
    clientCanvas( 1, &frame, &frame ),
    headingText( 2, &clientCanvas, &clientCanvas ),
    topSeparator( 3, &clientCanvas, &clientCanvas ),
    level1( 4, &clientCanvas, &clientCanvas ),
    horizSplit( 5, &level1, &level1 ),
    vertSplit( 6, &horizSplit, &horizSplit ),
    sizedBmp1( 7, &vertSplit, &vertSplit, ID_FOUNTAIN_BMP ),
    sizedBmp2( 8, &vertSplit, &vertSplit, ID_OLDBOOK_BMP ),
    bmpScroller( 9, &horizSplit, &horizSplit,
                 IRectangle(),
                 IViewPort::classDefaultStyle
                   & ~IViewPort::asNeededHorizontalScrollBar
                   & ~IViewPort::asNeededVerticalScrollBar
                   | IViewPort::alwaysHorizontalScrollBar
                   | IViewPort::alwaysVerticalScrollBar
                   | IViewPort::noViewWindowFill ),
    actualSizeBmp( 10, &bmpScroller, &bmpScroller, ID_KIDS_BMP ),
    centerSeparator( 11, &level1, &level1 ),
    dlgScroller( 11, &level1, &level1, IRectangle(),
                 IViewPort::classDefaultStyle
                   | IViewPort::expandableViewWindow ),
    level2( 12, &dlgScroller, &dlgScroller ),
    prompt( 13, &level2, &level2 ),
    entry( 14, &level2, &level2 ),
    choice1( 15, &level2, &level2 ),
    choice2( 16, &level2, &level2 ),
    listHeading( 17, &level2, &level2 ),
    list( 18, &level2, &level2 ),
    rightSeparator( 19, &level2, &level2 ),
    colorButtons( 20, &level2 ),
    pushButtons( 21, &level2 )
{
  headingText
   .setText( "This window combines several canvases." );
  topSeparator
   .setFillColor( IColor::black )
   .setMinimumSize( ISize( 1, 1 ));
  centerSeparator
   .setFillColor( IColor::black )
   .setMinimumSize( ISize( 1, 1 ));

  // Set up split canvases.
  horizSplit
   .setOrientation( ISplitCanvas::horizontalSplit )
   .setSplitWindowPercentage( &vertSplit, 33 )
   .setSplitWindowPercentage( &bmpScroller, 67 );
  horizSplit
   .setMinimumSize( ISize() );

  // Set up the dialog portion of the window.
  dlgScroller
   .setMinimumSize( ISize() );
  prompt.setText( "Enter some data below." );
  entry
   .setLimit( 15 )
   .enableTabStop()
   .enableGroup();
  choice1
#ifdef IC_PM
   .setText( "~First" )
#else
   .setText( "&First" )
#endif
   .enableTabStop()
   .enableGroup();
  choice2
#ifdef IC_PM
   .setText( "~Second" );
#else
   .setText( "&Second" );
#endif
  listHeading
   .setText( "Below is a list box." );
  list
   .enableTabStop()
   .enableGroup()
   .setMinimumSize( ISize( 50, 50 ));
  rightSeparator
   .setFillColor( IColor::black )
   .setMinimumSize( ISize( 1, 1 ));

  ISize
    defaultCellSize = IMultiCellCanvas::defaultCell();
  clientCanvas
   .addToCell( &headingText,     1, 2 )
   .addToCell( &topSeparator,    1, 3 )
   .addToCell( &level1,          1, 4 );
  clientCanvas
   .setColumnWidth( 1, 1, true )
   .setRowHeight( 4, 1, true );

  level1
   .addToCell( &horizSplit,      1, 1, 2 )
   .addToCell( &centerSeparator, 3, 1 )
   .addToCell( &dlgScroller,     4, 1, 2 );
  level1
   .setColumnWidth( 2, 1, true )  // Use 1:2 ratio.
   .setColumnWidth( 5, 2, true )
   .setRowHeight( 1, 1, true );

  level2
   .addToCell( &prompt,          2, 2,  5 )
   .addToCell( &entry,           2, 4,  5 )
   .addToCell( &choice1,         3, 6 )
   .addToCell( &choice2,         5, 6 )
   .addToCell( &listHeading,     2, 8,  5 )
   .addToCell( &list,            2, 10, 5 )
   .addToCell( &rightSeparator,  8, 1,  1, 11 )
   .addToCell( &colorButtons,    9, 1,  1, 11 );
  level2
   .setColumnWidth( 4, 1, true )
   .setColumnWidth( 6, 1, true )
   .setRowHeight( 10, 1, true )
   .setRowHeight( 11, defaultCellSize.height() );

  pushButtons
   .setMargin( defaultCellSize / 2 );
  frame
   .setClient( &clientCanvas )
   .addExtension( &pushButtons, IFrameWindow::belowClient )
   .setFocus()
   .show();
}

//======================= ColorButtons ========================

ColorButtons::ColorButtons ( unsigned long id,
                             IWindow* parentAndOwner )
  : ISetCanvas( id, parentAndOwner, parentAndOwner ),
    red( 1, this, this, ID_SCREEN_ICON ),
    green( 2, this, this, ID_SCREEN_ICON ),
    blue( 3, this, this, ID_SCREEN_ICON ),
    cyan( 4, this, this, ID_SCREEN_ICON ),
    pink( 5, this, this, ID_SCREEN_ICON )
{
  (*this)
   .setPackType( ISetCanvas::expanded )
   .setDeckOrientation( ISetCanvas::vertical );

  ISize
    colorSize( 40, 40 );
  red
   .enableTabStop()
   .enableGroup()
   .setBackgroundColor( IColor::red )
   .setMinimumSize( colorSize );
  green
   .setBackgroundColor( IColor::green )
   .setMinimumSize( colorSize );
  blue
   .setBackgroundColor( IColor::blue )
   .setMinimumSize( colorSize );
  cyan
   .setBackgroundColor( IColor::cyan )
   .setMinimumSize( colorSize );
  pink
   .setBackgroundColor( IColor::pink )
   .setMinimumSize( colorSize );
}
