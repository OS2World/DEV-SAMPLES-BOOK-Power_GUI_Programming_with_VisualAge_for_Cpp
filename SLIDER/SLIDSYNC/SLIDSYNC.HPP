#ifndef _SLIDSYNC_
#define _SLIDSYNC_
//*********************************************************
// Sliders - Slider Arm Handler Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//*********************************************************
#include <icslider.hpp>
#include <iframe.hpp>
#include <imcelcv.hpp>
#include <isldahdr.hpp>
#include <islider.hpp>
#include <istattxt.hpp>

class ArmHandler : public ISliderArmHandler {
protected:
virtual Boolean
  positionChanged ( IControlEvent& event )
  {
    return this->valueChange( event );
  }
virtual Boolean
  moving          ( IControlEvent& event )
  {
    return this->valueChange( event );
  }
virtual Boolean
  valueChange     ( IControlEvent& event ) = 0;
}; // ArmHandler

class SynchronizedSliders : public IFrameWindow {
public:
  SynchronizedSliders ( );

SynchronizedSliders
 &setValue ( unsigned long value );

private:
  SynchronizedSliders ( const SynchronizedSliders& );
SynchronizedSliders
 &operator=           ( const SynchronizedSliders& );
IMultiCellCanvas
  canvasClient;
IStaticText
  progressIndicatorLabel;
IProgressIndicator
  progressIndicator;
IStaticText
  sliderLabel;
ISlider
  slider;
IStaticText
  circularSliderLabel;
ICircularSlider
  circularSlider;

class LinearSliderArmHandler : public ArmHandler {
  public:
    LinearSliderArmHandler ( SynchronizedSliders* window );
  LinearSliderArmHandler
   &handleEventsFor ( ISlider* slider );
  protected:
  virtual Boolean
    valueChange ( IControlEvent& event );
  private:
  SynchronizedSliders
   *sliderWindow;
  LinearSliderArmHandler
   &handleEventsFor ( IWindow* )
    {
      return *this; 
    }
  }; // SynchronizedSliders::LinearSliderArmHandler

class CircularSliderArmHandler : public ArmHandler{
  public:
    CircularSliderArmHandler ( SynchronizedSliders* window );
  CircularSliderArmHandler
   &handleEventsFor ( ICircularSlider* circularSlider );
  protected:
  virtual Boolean
    valueChange ( IControlEvent& event );
  private:
  SynchronizedSliders
   *sliderWindow;
  CircularSliderArmHandler
   &handleEventsFor ( IWindow* )
    {
      return *this; 
    }
  }; // SynchronizedSliders::CircularSliderArmHandler

LinearSliderArmHandler
  linearSliderArmHandler;
CircularSliderArmHandler
  circularSliderArmHandler;
}; // SynchronizedSliders

#endif // _SLIDSYNC_
