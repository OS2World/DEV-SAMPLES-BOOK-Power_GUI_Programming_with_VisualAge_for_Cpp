#ifndef _XCANVAS_
#define _XCANVAS_
//*********************************************************
// Canvas - Complex Canvas Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//*********************************************************
#include <ibmpctl.hpp>
#include <icheckbx.hpp>
#include <ientryfd.hpp>
#include <iframe.hpp>
#include <igraphbt.hpp>
#include <ilistbox.hpp>
#include <imcelcv.hpp>
#include <irect.hpp>
#include <isetcv.hpp>
#include <isplitcv.hpp>
#include <istattxt.hpp>
#include <ivport.hpp>

#include "pushbtns.hpp"

//======================= Color Buttons ========================
class ColorButtons : public ISetCanvas {
public:
  ColorButtons ( unsigned long id,
                 IWindow* parentAndOwner );
private:
  ColorButtons ( const ColorButtons& );
ColorButtons
 &operator=    ( const ColorButtons& );
IGraphicPushButton
  red,
  green,
  blue,
  cyan,
  pink;
}; // ColorButtons

//==================== ComplexCanvasWindow =====================
class ComplexCanvasWindow : public IVBase {
public:
  ComplexCanvasWindow ( );
private:
  ComplexCanvasWindow ( const ComplexCanvasWindow& );
ComplexCanvasWindow
 &operator=           ( const ComplexCanvasWindow& );
IFrameWindow
  frame;
IMultiCellCanvas
  clientCanvas;
IStaticText
  headingText,
  topSeparator;
IMultiCellCanvas
  level1;
ISplitCanvas
  horizSplit,
  vertSplit;
IBitmapControl
  sizedBmp1,
  sizedBmp2;
IViewPort
  bmpScroller;
IBitmapControl
  actualSizeBmp;
IStaticText
  centerSeparator;
IViewPort
  dlgScroller;
IMultiCellCanvas
  level2;
IStaticText
  prompt;
IEntryField
  entry;
ICheckBox
  choice1,
  choice2;
IStaticText
  listHeading;
IListBox
  list;
IStaticText
  rightSeparator;
ColorButtons
  colorButtons;
MyStandardPushButtons
  pushButtons;
}; // ComplexClient

#endif  // _XCANVAS_
