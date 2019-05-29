//*********************************************************
// Sliders - Linear Slider Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//*********************************************************
#include <ipoint.hpp>
#include <irect.hpp>
#include <istring.hpp>
#include <icconst.h>
#include "tempview.hpp"

#define ID_SLIDER      101
#define ID_TEMPERATURE 102

// Primary application class definition.
TemperatureView :: TemperatureView ( const char* viewName )
  : IFrameWindow( viewName ),
    canvasClient( IC_FRAME_CLIENT_ID, this, this ),
    farenheitSlider( ID_SLIDER, &canvasClient, &canvasClient,
                     IRectangle(), 29, 0,
                     ( ISlider::classDefaultStyle
                        & ~IProgressIndicator::alignCentered )
                       | IProgressIndicator::alignBottom ),
    temperatureText( ID_TEMPERATURE, &canvasClient, &canvasClient ),
    temperatureHandler( &temperatureText )
{
  // Add the slider-arm handler to the slider.
  temperatureHandler
   .handleEventsFor( &farenheitSlider );

  // Place the slider and status text in the client window.
  (*this)
   .setClient( &canvasClient );
  canvasClient
   .addToCell( &farenheitSlider, 2, 2 )
   .addToCell( &temperatureText, 2, 4 );
  canvasClient
   .setColumnWidth( 2, 1, true )
   .setColumnWidth( 3, IMultiCellCanvas::defaultCell().width() )
   .setRowHeight( 2, 1, true )
   .setRowHeight( 4, 1, true )
   .setRowHeight( 5, IMultiCellCanvas::defaultCell().height() );

  // Set the alignment and text for the static text controls.
  temperatureText
   .setAlignment( IStaticText::centerCenter )
   .setLimit( 20 )
   .setText( "Temperature is 0" );

  // Set the length and text for the slider's ticks.
  // The slider has 29 ticks that represent temperatures
  // from -40 to 240 (the ticks are at 10 degree intervals).
  farenheitSlider
   .setMinimumSize( ISize( 700, 80 ) );
  farenheitSlider
   .setTickLength( 10 );
  for ( int i = 0; i < 29; i += 2 )
  {
     farenheitSlider
      .setTickText( i, IString( ( i * 10 ) - 40 ) );
  }

  // Force the canvas to size the slider, and size the frame
  // window around the client so the slider does not resize.
  ISize
    clientMinimumSize( canvasClient.minimumSize() );
  (*this)
   .moveSizeToClient( IRectangle( IPoint( 50, 50 ),
                                  clientMinimumSize ) );

  // Translate degrees to pixel offsets from tick 0.
  // The total number of pixels spans 280 degrees (-40 to 240).
  unsigned long
    totalPixels = farenheitSlider.armRange() - 1;
  unsigned long
    pixelsToFreezing = (32 + 40) * totalPixels / 280 + 1,
    pixelsToBoiling = (212 + 40) * totalPixels / 280 + 1;

  // Add detents for freezing and boiling temperatures using
  // the above pixel offsets.
  farenheitSlider
   .addDetent( pixelsToFreezing );
  farenheitSlider
   .addDetent( pixelsToBoiling );

  // Move the slider arm to temperature 0 (tick 4).
  farenheitSlider
   .moveArmToTick( 4 );
}

// Handle changes to the slider control.
IBase::Boolean
  TemperatureHandler::valueChange ( IControlEvent& event )
{
  ISlider *slider = (ISlider*)event.controlWindow();

  // We need to deal with pixel offsets instead of ticks because
  // we have only 29 ticks but need to appear to support 281.
  // support 281.
  unsigned long
    totalPixels = slider->armRange() - 1,
    armOffset = slider->armPixelOffset();
  long
    temperature = 0;
  if ( totalPixels )
  {
     temperature = armOffset * ( 281 - 1 ) / totalPixels - 40;
  }
  temperatureText->setText( IString( "Temperature is " )
                              + IString( temperature ) );
  return true;
}
