#ifndef _TASKVIEW_
#define _TASKVIEW_
//*********************************************************
// Sliders - Progress Indicator Custom Painting Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//*********************************************************
#include <iframe.hpp>
#include <imcelcv.hpp>
#include <islider.hpp>
#include <islidhdr.hpp>
#include <istattxt.hpp>
#include <itimer.hpp>   

// Handle custom drawing of a progress indicator.
class DrawHandler : public ISliderDrawHandler {
public:
virtual Boolean
  drawBackground  ( IDrawItemEvent& event ),
  drawRibbonStrip ( IDrawItemEvent& event ),
  drawShaft       ( IDrawItemEvent& event );
}; // DrawHandler

// The primary window.
class TaskStatusView : public IFrameWindow {
public:
  TaskStatusView ( const char* title );

void
  taskPortionComplete ( unsigned long );

private:
  TaskStatusView ( const TaskStatusView& );
TaskStatusView
 &operator=      ( const TaskStatusView& );

IMultiCellCanvas
  canvas;
IStaticText
  indicatorTitle;
IProgressIndicator
  taskIndicator;
ITimer
  taskTimer;
DrawHandler
  drawHandler;
}; // TaskStatusView

#endif // _TASKVIEW_
