#ifndef _CSLIDER_
#define _CSLIDER_
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
#include <isplitcv.hpp>
#include <istattxt.hpp>

class ColorWindow : public IFrameWindow {
public:
  ColorWindow ( );

ColorWindow
 &setRed        ( unsigned char = 0 ),
 &setGreen      ( unsigned char = 255 ),
 &setBlue       ( unsigned char = 0 ),
 &setBrightness ( unsigned long = 100 );

protected:
ColorWindow
 &updateColor            ( unsigned char red,
                           unsigned char green,
                           unsigned char blue ),
 &updateBrightness       ( unsigned long ),
 &showColorAndBrightness ( );

private:
  ColorWindow ( const ColorWindow& );
ColorWindow
 &operator=   ( const ColorWindow& );
ISplitCanvas
  canvasClient;
IStaticText
  colorWindow;
IMultiCellCanvas
  sliderCanvas;
ICircularSlider
  brightnessSlider,
  redGreenSlider;

class ArmHandler : public ISliderArmHandler{
  public:
    ArmHandler      ( ColorWindow* window );
  protected:
  virtual Boolean
    positionChanged ( IControlEvent& event )
    { return this->valueChange( event ); }
  virtual Boolean
    moving          ( IControlEvent& event )
    { return this->valueChange( event ); }
  virtual Boolean
    valueChange ( IControlEvent& event );
  private:
  ColorWindow
   *colorWindow;
  }; // ColorWindow::ArmHandler

friend
  class ArmHandler;
ArmHandler
  fArmHandler;
unsigned char
  fRed,
  fGreen,
  fBlue;
unsigned long
  fBrightness;
}; // ColorWindow

#endif // _CSLIDER_
