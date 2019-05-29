//*********************************************************
// Sliders - Circular Slider Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//*********************************************************
#include <iapp.hpp>
#include <icolor.hpp>
#include <irect.hpp>
#include <icconst.h>
#include "cslider.hpp"

#define ID_BRIGHTNESS_CSLIDER  101
#define ID_REDGREEN_CSLIDER   102

void main ( )
{
  // Create a window with two circular sliders.
  ColorWindow
    colorWindow;

  // Give the window the input focus and show it.
  colorWindow
   .setFocus()
   .show();

  IApplication::current().run();
}

ColorWindow::ColorWindow ( )
  : IFrameWindow( "Circular Slider Example" ),
    canvasClient( IC_FRAME_CLIENT_ID, this, this ),
    colorWindow( 10, &canvasClient, &canvasClient ),
    sliderCanvas( 20, &canvasClient, &canvasClient ),
    brightnessSlider( ID_BRIGHTNESS_CSLIDER,
                      &sliderCanvas, &sliderCanvas, IRectangle(),
                      ICircularSlider::buttons
                       | ICircularSlider::displayValue
                       | ICircularSlider::jumpToPointer
                       | ICircularSlider::label
                       | ICircularSlider::midpoint
                       | ICircularSlider::proportionalTicks
                       | IControl::tabStop
                       | IWindow::visible ),
    redGreenSlider( ID_REDGREEN_CSLIDER,
                    &sliderCanvas, &sliderCanvas, IRectangle(),
                    ICircularSlider::circularArm
                     | ICircularSlider::jumpToPointer
                     | ICircularSlider::label
                     | ICircularSlider::noTicks
                     | IControl::tabStop
                     | IWindow::visible ),
    fArmHandler( this ),
    fRed( 0 ),
    fGreen( 0 ),
    fBlue( 0 ),
    fBrightness( 0 )
{
  canvasClient
   .setOrientation( ISplitCanvas::horizontalSplit )
   .setSplitWindowPercentage( &colorWindow,  70 )
   .setSplitWindowPercentage( &sliderCanvas, 30 );

  // Set up the circular sliders.
  brightnessSlider
   .setBackgroundColor( sliderCanvas.backgroundColor() )
   .setMinimumSize( ISize( 50, 50 ) );
  brightnessSlider
   .setArmRange( IRange( 0, 100 ) )
   .setTickSpacing( 1 )
   .setText( "Brightness" );

  redGreenSlider
   .setBackgroundColor( sliderCanvas.backgroundColor() )
   .setMinimumSize( ISize( 50, 50 ) );
  redGreenSlider
   .setArmRange( IRange( 0, 255 ) )
   .setTickSpacing( 10 )
   .setText( "Red    Green" );

  // Define the positioning rules for controls on the multicell
  // canvas.
  sliderCanvas
   .addToCell( &brightnessSlider, 2, 2 )
   .addToCell( &redGreenSlider,   4, 2 );
  sliderCanvas
   .setColumnWidth( 1, 10, true )
   .setColumnWidth( 2, 10, true )
   .setColumnWidth( 3, 10, true )
   .setColumnWidth( 4, 10, true )
   .setColumnWidth( 5, 10, true )
   .setRowHeight( 1, 10 )
   .setRowHeight( 2, 10, true )
   .setRowHeight( 3, 10 );

  fArmHandler
   .handleEventsFor( &brightnessSlider )
   .handleEventsFor( &redGreenSlider );

  (*this)
   .setGreen( 255 )
   .setBrightness( 100 );

  (*this)
   .setClient( &canvasClient );
}

ColorWindow&
  ColorWindow::setRed ( unsigned char red )
{
  this->setGreen( 255 - red );
  return *this;
}

ColorWindow&
  ColorWindow::setGreen ( unsigned char green )
{
  redGreenSlider.setValue( green );
#ifdef IC_PM
  // Compensate for slider arm handler not being called.
  this->updateColor( (unsigned char)( 255 - green ),
                     green,
                     0 );
#endif
  return *this;
}

ColorWindow&
  ColorWindow::setBlue ( unsigned char blue )
{
  fBlue = blue;
  return *this;
}

ColorWindow&
  ColorWindow::setBrightness ( unsigned long brightness )
{
  if ( brightness > 100 )
  {
     brightness = 100;
  }
  brightnessSlider.setValue( brightness );
#ifdef IC_PM
  // Compensate for slider arm handler not being called.
  this->updateBrightness( brightness );
#endif
  return *this;
}

ColorWindow&
  ColorWindow::updateColor ( unsigned char red,
                             unsigned char green,
                             unsigned char blue )
{
  fRed = red;
  fGreen = green;
  fBlue = blue;
  return this->showColorAndBrightness();
}

ColorWindow&
  ColorWindow::updateBrightness ( unsigned long brightness )
{
  fBrightness = ( brightness > 100 ) ? 100 : brightness;
  return this->showColorAndBrightness();
}

ColorWindow&
  ColorWindow::showColorAndBrightness ( )
{
  unsigned char
    red   = fRed,
    green = fGreen,
    blue  = fBlue;

  if ( red )
  {
     red = (unsigned char)( red * fBrightness / 100 );
  }
  if ( green )
  {
     green = (unsigned char)( green * fBrightness / 100 );
  }
  if ( blue )
  {
     blue = (unsigned char)( blue * fBrightness / 100 );
  }

  colorWindow
   .setBackgroundColor( IColor( red, green, blue ) );
  return *this;
}

ColorWindow::ArmHandler::ArmHandler ( ColorWindow* window )
  : ISliderArmHandler( ),
    colorWindow( window )
{ }

IBase::Boolean
  ColorWindow::ArmHandler::valueChange ( IControlEvent& event )
{
  ICircularSlider
   *cslider = (ICircularSlider*)event.controlWindow();
  if ( cslider->id() == ID_BRIGHTNESS_CSLIDER )
  {
     colorWindow->updateBrightness( cslider->value() );
  }
  else if ( cslider->id() == ID_REDGREEN_CSLIDER )
  {
     unsigned char
       green = (unsigned char)( cslider->value() );
     colorWindow->updateColor( (unsigned char)( 255 - green ),
                               green,
                               0 );
  }
  return false;
}
