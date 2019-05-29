//*********************************************************
// Sliders - Synchronized Slider Controls
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//*********************************************************
#include <iapp.hpp>
#include <ipoint.hpp>
#include <irect.hpp>
#include <istring.hpp>
#include <icconst.h>
#include "slidsync.hpp"

#define ID_PROGIND     101
#define ID_SLIDER      102
#define ID_CSLIDER     103
#define ID_DUMMY       0

#define LAST_TICK      10
#define MIDDLE_TICK    ( LAST_TICK / 2 )
#define TICK_COUNT     ( LAST_TICK + 1 )
#define INITIAL_VALUE  3

void main ( )
{
#ifdef IC_WIN
#ifdef PM_COMPATIBLE
  IProgressIndicator::setDefaultStyle( IProgressIndicator::defaultStyle()
                                        | IProgressIndicator::pmCompatible );
  ISlider::setDefaultStyle( ISlider::defaultStyle()
                             | IProgressIndicator::pmCompatible );
#endif
#endif

  // Create a window with a progress indicator, linear slider, and
  // circular slider synchronized with the ISliderArmHandler class.
  SynchronizedSliders
    sliderWindow;

  // Give the window an initial value and input focus, and show it.
  sliderWindow
   .setValue( INITIAL_VALUE )
   .setFocus()
   .show();

  IApplication::current().run();
}

SynchronizedSliders::SynchronizedSliders ( )
  : IFrameWindow( "Synchronized Slider Controls" ),
    canvasClient( IC_FRAME_CLIENT_ID, this, this ),
    progressIndicatorLabel( ID_DUMMY, &canvasClient, &canvasClient ),
    progressIndicator( ID_PROGIND, &canvasClient, &canvasClient,
                       IRectangle(), TICK_COUNT, 0,
                       ( IProgressIndicator::defaultStyle()
                           & ~IProgressIndicator::alignCentered )
                         | IProgressIndicator::alignBottom ),
    sliderLabel( ID_DUMMY, &canvasClient, &canvasClient ),
    slider( ID_SLIDER, &canvasClient, &canvasClient,
            IRectangle(), TICK_COUNT, 0,
            ( ISlider::defaultStyle()
              & ~IProgressIndicator::alignCentered )
             | IProgressIndicator::alignBottom ),
    circularSliderLabel( ID_DUMMY, &canvasClient, &canvasClient ),
    circularSlider( ID_CSLIDER, &canvasClient, &canvasClient ),
    linearSliderArmHandler( this ),
    circularSliderArmHandler( this )
{
  // Set up the progress indicator.
  progressIndicatorLabel
   .setText( "Progress indicator" );
  progressIndicator
   .setBackgroundColor( canvasClient.backgroundColor() )
   .setMinimumSize( ISize( 100, 60 ) );
  progressIndicator
   .setTickLength( 10 )
   .setTickText( 0,  "0" )
   .setTickText( MIDDLE_TICK, IString( MIDDLE_TICK ) )
   .setTickText( LAST_TICK, IString( LAST_TICK ) );

  // Set up the linear slider.
  sliderLabel
   .setText( "Linear slider" );
  slider
   .setBackgroundColor( canvasClient.backgroundColor() )
   .setMinimumSize( ISize( 100, 60 ) );
  slider
   .setTickLength( 10 )
   .setTickText( 0,  "0" )
   .setTickText( MIDDLE_TICK, IString( MIDDLE_TICK ) )
   .setTickText( LAST_TICK, IString( LAST_TICK ) )
   .enableTabStop()
   .enableGroup();

  // Set up the circular slider.
  circularSliderLabel
   .setText( "Circular slider" );
  circularSlider
   .setBackgroundColor( canvasClient.backgroundColor() )
   .setMinimumSize( ISize( 150, 150 ) );
  circularSlider
   .setArmRange( IRange( 0, LAST_TICK ) )
   .setTickSpacing( 1 )
   .enableTabStop()
   .enableGroup();

  // Define the positioning rules for controls on the multicell
  // canvas.
  canvasClient
   .addToCell( &progressIndicatorLabel, 2, 2,  2 )
   .addToCell( &progressIndicator,      3, 4     )
   .addToCell( &sliderLabel,            2, 6,  2 )
   .addToCell( &slider,                 3, 8     )
   .addToCell( &circularSliderLabel,    2, 10, 2 )
   .addToCell( &circularSlider,         3, 12    );
  unsigned long
    defaultCellHeight = IMultiCellCanvas::defaultCell().height();
  canvasClient
   .setRowHeight( 1,  defaultCellHeight * 2 )
   .setRowHeight( 5,  defaultCellHeight * 2 )
   .setRowHeight( 9,  defaultCellHeight * 2 )
   .setRowHeight( 12, 1, true )
   .setRowHeight( 13, defaultCellHeight )
   .setColumnWidth( 3, 1, true )
   .setColumnWidth( 4, IMultiCellCanvas::defaultCell().width() );

  // Before moving their arms, we need to size the progress indicator
  // and linear slider.  We can do this by forcing their parent
  // multicell canvas to to run its layout routine by requesting its
  // minimum size.
  ISize
    clientSize( canvasClient.minimumSize() );
  (*this)
   .setValue( INITIAL_VALUE );

  linearSliderArmHandler
   .handleEventsFor( &slider );
  circularSliderArmHandler
   .handleEventsFor( &circularSlider );

  (*this)
   .setClient( &canvasClient )
   .moveSizeToClient( IRectangle( IPoint( 100, 50 ),
                                  ISize( clientSize.scaleBy( 2, 1 ) ) ) );
}

SynchronizedSliders&
  SynchronizedSliders::setValue ( unsigned long value )
{
  if ( progressIndicator.armTickOffset() != value )
  {
     progressIndicator
      .moveArmToTick( value );
  }
  if ( slider.armTickOffset() != value )
  {
     slider
      .moveArmToTick( value );
  }
  if ( circularSlider.value() != value )
  {
     circularSlider
      .setValue( value );
  }
  return *this;
}

SynchronizedSliders::
  LinearSliderArmHandler::LinearSliderArmHandler
                            ( SynchronizedSliders* window )
  : ArmHandler( ),
    sliderWindow( window )
{ }

SynchronizedSliders::LinearSliderArmHandler&
  SynchronizedSliders::LinearSliderArmHandler::handleEventsFor
                                             ( ISlider* slider )
{
  this->IHandler::handleEventsFor( slider );
  return *this;
}

IBase::Boolean
  SynchronizedSliders::LinearSliderArmHandler::valueChange
                                        ( IControlEvent& event )
{
  // Down-cast is safe here, because this handler can
  // only be attached to an ISlider.
  ISlider
   *slider = (ISlider*)event.dispatchingWindow();
  sliderWindow->setValue( slider->armTickOffset() );
  return false;
}

SynchronizedSliders::
  CircularSliderArmHandler::CircularSliderArmHandler
                                 ( SynchronizedSliders* window )
  : ArmHandler( ),
    sliderWindow( window )
{ }

SynchronizedSliders::CircularSliderArmHandler&
  SynchronizedSliders::CircularSliderArmHandler::handleEventsFor
                             ( ICircularSlider* circularSlider )
{
  this->IHandler::handleEventsFor( circularSlider );
  return *this;
}

IBase::Boolean
  SynchronizedSliders::CircularSliderArmHandler::valueChange
                                        ( IControlEvent& event )
{
  // Down-cast is safe here, because this handler can
  // only be attached to an ICircularSlider.
  ICircularSlider
   *cslider = (ICircularSlider*)event.dispatchingWindow();
  sliderWindow->setValue( cslider->value() );
  return false;
}
