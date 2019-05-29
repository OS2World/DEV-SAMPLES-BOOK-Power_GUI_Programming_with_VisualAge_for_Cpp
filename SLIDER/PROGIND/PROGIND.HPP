#ifndef _PROGIND_
#define _PROGIND_
//*********************************************************
// Sliders - Progress Indicator Example                 
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//*********************************************************
#include <icmdhdr.hpp>
#include <iframe.hpp>
#include <imcelcv.hpp>
#include <ipushbut.hpp>
#include <islider.hpp>
#include <istattxt.hpp>
#include <ithread.hpp>
#include <itimer.hpp>

class PrimaryWindow : public IFrameWindow {
public:
  PrimaryWindow ( );
PrimaryWindow
 &startTask          ( ),
 &setPercentComplete ( unsigned long percent ),
 &cleanupTask        ( );
private:
  PrimaryWindow ( const PrimaryWindow& );
PrimaryWindow
 &operator=     ( const PrimaryWindow& );
IMultiCellCanvas
  canvas;
IStaticText
  instructions;
IPushButton
  startButton;
class StartThreadHdr : public ICommandHandler {
  public:
    StartThreadHdr ( PrimaryWindow& window );
  protected:
  virtual Boolean
    command ( ICommandEvent& event );
  private:
    StartThreadHdr ( const StartThreadHdr& );
  StartThreadHdr
   &operator=      ( const StartThreadHdr& );
  PrimaryWindow
   &primaryWindow;
  }; // PrimaryWindow::StartThreadHdr
StartThreadHdr
  cmdHdr;
IWindowHandle
  progressWindowHandle;
}; // PrimaryWindow

class LongRunningTask : public IThreadFn {
public:
  LongRunningTask ( PrimaryWindow& primary );
void
  stop            ( );
protected:
virtual void
  run             ( );
void
  portionComplete ( unsigned long );
private:
  LongRunningTask ( LongRunningTask& );
LongRunningTask
 &operator=       ( LongRunningTask& );
PrimaryWindow
 &primaryWindow;
ITimer
  timer;
unsigned long
  count,
  percentComplete;
}; // LongRunningTask

class ProgressWindow : public IFrameWindow {
public:
  ProgressWindow ( IWindow*         owner,
                   const char*      title,
                   LongRunningTask* task );
ProgressWindow
 &setPercentDone ( unsigned long percent );
private:
  ProgressWindow ( const ProgressWindow& );
ProgressWindow
 &operator=      ( const ProgressWindow& );
IMultiCellCanvas
  canvasClient;
IProgressIndicator
  progressIndicator;
IStaticText
  label;
IPushButton
  stopButton;

class StopCmdHandler : public ICommandHandler {
  public:
    StopCmdHandler ( LongRunningTask* task );
  protected:
  virtual Boolean
    command ( ICommandEvent& event );
  private:
  LongRunningTask
   *runningTask;
  }; // ProgressWindow::StopCmdHandler

StopCmdHandler
  stopCmdHandler;
}; // ProgressWindow

#endif // _PROGIND_
