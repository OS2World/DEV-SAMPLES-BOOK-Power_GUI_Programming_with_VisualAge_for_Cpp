#ifndef _TEMPVIEW_
#define _TEMPVIEW_
//*********************************************************
// Sliders - Linear Slider Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//*********************************************************
#include <iframe.hpp>
#include <imcelcv.hpp>
#include <isldahdr.hpp>
#include <islider.hpp>
#include <istattxt.hpp>

class TemperatureHandler : public ISliderArmHandler {
public:
  TemperatureHandler ( IStaticText* text )
    : ISliderArmHandler(),
      temperatureText( text )
  { }
protected:
virtual Boolean
  moving          ( IControlEvent& event )
  { return this->valueChange( event ); }
virtual Boolean
  positionChanged ( IControlEvent& event )
  { return this->valueChange( event ); }
virtual Boolean
  valueChange     ( IControlEvent& event );
private:
IStaticText
 *temperatureText;
}; // TemperatureHandler

class TemperatureView : public IFrameWindow {
public:
  TemperatureView ( const char* viewName );

private:
  TemperatureView ( const TemperatureView& );
TemperatureView
 &operator=       ( const TemperatureView& );

IMultiCellCanvas
  canvasClient;
ISlider
  farenheitSlider;
IStaticText
  temperatureText;
TemperatureHandler
  temperatureHandler;
}; // TemperatureView            

#endif // _TEMPVIEW_
