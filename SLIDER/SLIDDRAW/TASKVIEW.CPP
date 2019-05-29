//*********************************************************
// Sliders - Progress Indicator Custom Painting Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//*********************************************************
#include <icconst.h>
#include <icolor.hpp>
#include <igbitmap.hpp>
#include <igbundle.hpp>
#include <iglist.hpp>
#include <igrafctx.hpp>
#include <igrect.hpp>
#include <ipoint.hpp>
#include <irect.hpp>
#include <irefcnt.hpp>
#include <istring.hpp>
#include <ithread.hpp>
#include "taskview.hpp"

// Status View definition.
TaskStatusView :: TaskStatusView ( const char* title )
  : IFrameWindow( title ),
    canvas( IC_FRAME_CLIENT_ID, this, this ),
    indicatorTitle( 100, &canvas, &canvas ),
    taskIndicator( 200, &canvas, &canvas,
                   IRectangle(), 101 ),
    taskTimer(),
    drawHandler()
{
  // Make the canvas the client window, and set controls into it.
  this->setClient( &canvas );
  canvas
   .addToCell( &indicatorTitle, 2, 2 )
   .addToCell( &taskIndicator,  2, 4 );
  unsigned long
    defaultRowHeight = IMultiCellCanvas::defaultCell().height(),
    defaultColumnWidth = IMultiCellCanvas::defaultCell().width();
  canvas
   .setRowHeight( 1, defaultRowHeight, true )
   .setRowHeight( 3, defaultRowHeight, true )
   .setRowHeight( 5, defaultRowHeight, true )
   .setColumnWidth( 2, 0, true )
   .setColumnWidth( 3, defaultColumnWidth );
  canvas
   .setForegroundColor( IColor( IColor::blue ) )
   .setBackgroundColor( IColor( IColor::cyan ) );

  // Allow for custom painting of the progress indicator.
  taskIndicator
   .enableDrawItem();
  drawHandler
   .handleEventsFor( &taskIndicator );

  // Fix-up to allow color changes up the owner chain to properly
  // percolate down, since we will be painting the background.
  taskIndicator
   .resetBackgroundColor();   // Shouldn't be necessary!

  // Set the size of the progress indicator shaft.
  taskIndicator
   .setShaftBreadth( 50 )
   .setMinimumSize( ISize( 200, 200 ) );

  // Set the length and text for the indicator's ticks.
  taskIndicator
   .setTickLength( 2 );
  for ( int i = 0; i <= 100; i += 5 )
  {
     if ( i % 10 )
     {         // Not multiple of 10.
        taskIndicator
         .setTickLength( i, 5 );
     }
     else
     {         // Multiple of 10.
        taskIndicator
         .setTickLength( i, 10 )
         .setTickText( i, IString( i ) );
     }
  }

  // Set up the static text control.
  indicatorTitle
   .setText( "Percentage of Task Completed" )
   .setAlignment( IStaticText::centerCenter );

  // Start the timer to simulate a running task.
  taskTimer
   .setInterval( 500 )          // .5 seconds.
   .start( new ITimerMemberFn< TaskStatusView >
                  ( *this, TaskStatusView::taskPortionComplete ) );
}

//  Move the indicator arm when the timer expires.
void TaskStatusView::taskPortionComplete ( unsigned long )
{
  #define PERCENT  15
  unsigned long
    currentPercent = taskIndicator.armTickOffset();
  if ( currentPercent < 100 )
  {
     unsigned long
       newPercent = currentPercent + PERCENT;
     if ( newPercent > 100 )
     {
        newPercent = 100;
     }
     taskIndicator.moveArmToTick( newPercent );
  }
}

// Function to properly paint the background color of a
// progress indicator.
IBase::Boolean
  DrawHandler::drawBackground ( IDrawItemEvent& event )
{
  IGraphicContext
    gc( event.itemPresSpaceHandle() );
  IGraphicBundle
    bundle( gc );
  bundle
   .setDrawOperation( IGraphicBundle::fill )
   .setBackgroundMixMode( IGraphicBundle::backOverPaint )
   .setFillColor( event.controlWindow()->backgroundColor() );
  IGRectangle
    background( event.itemRect() );
  background
   .setGraphicBundle( bundle )
   .drawOn( gc );
  return true;
}

// Function to paint the ribbon strip of the progress indicator.
IBase::Boolean
  DrawHandler::drawRibbonStrip ( IDrawItemEvent& event )
{
  // Draw the ribbon strip using information from the draw
  // item event.
  IGraphicContext
    gc( event.itemPresSpaceHandle() );
  IGraphicBundle
    bundle( gc );
  bundle
   .setDrawOperation( IGraphicBundle::fill )
   .setBackgroundMixMode( IGraphicBundle::backOverPaint )
   .setFillPattern( IGraphicBundle::forewardDiag2 )
   .setFillColor( IColor( IColor::blue ) );
  IGRectangle
    ribbon( event.itemRect() );
  ribbon
   .setGraphicBundle( bundle )
   .drawOn( gc );
  return true;
}

// Function to paint the shaft of the progress indicator.
IBase::Boolean DrawHandler::drawShaft ( IDrawItemEvent& event )
{
  // Draw the shaft using information from the draw item event.
  IGraphicContext
    gc( event.itemPresSpaceHandle() );
  IGraphicBundle
    bundle( gc );
  bundle
   .setDrawOperation( IGraphicBundle::fill )
   .setBackgroundMixMode( IGraphicBundle::backOverPaint )
   .setFillColor( IColor( IColor::yellow ) );
  IGRectangle
    shaft( event.itemRect() );
  shaft
   .setGraphicBundle( bundle )
   .drawOn( gc );
  return true;
}
