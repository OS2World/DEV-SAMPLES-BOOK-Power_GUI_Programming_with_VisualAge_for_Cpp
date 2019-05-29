//*********************************************************
// Sliders - Progress Indicator Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//*********************************************************
#include <iapp.hpp>
#include <ipoint.hpp>
#include <irect.hpp>
#include <irefcnt.hpp>
#include <istring.hpp>
#include <icconst.h>
#include "progind.hpp"

#define ID_START_TASK_CMD  200
#define ID_STOP_CMD        300

void main ( )
{
  // Create the primary window.
  PrimaryWindow
    mainWindow;

  // Give the window the input focus and show it.
  mainWindow
   .setFocus()
   .show();

  IApplication::current().run();
}

PrimaryWindow::PrimaryWindow ( )
  : IFrameWindow( "Progress Indicator Example" ),
    canvas( IC_FRAME_CLIENT_ID, this, this ),
    instructions( 100, &canvas, &canvas ),
    startButton( ID_START_TASK_CMD, &canvas, &canvas ),
    cmdHdr( *this ),
    progressWindowHandle( 0 )
{
  this->setClient( &canvas );
  cmdHdr.handleEventsFor( this );

  instructions
   .setText( "Select the Start task button to display the progress indicator." );
  startButton
   .enableDefault()
   .setText( "Start task" )
   .enableTabStop()
   .enableGroup();

  // Define the rules for positioning controls on the multicell
  // canvas and adding white space when growing the canvas.
  canvas
   .addToCell( &instructions, 2, 2 )
   .addToCell( &startButton,  2, 4 );
  canvas
   .setRowHeight( 2, 1, true )
   .setRowHeight( 5, IMultiCellCanvas::defaultCell().height() )
   .setColumnWidth( 2, 1, true )
   .setColumnWidth( 3, IMultiCellCanvas::defaultCell().width() );
}

PrimaryWindow& PrimaryWindow::startTask ( )
{
  startButton
   .disable();

  // Start a thread representing a time-consuming operation.
  LongRunningTask
   *task = new LongRunningTask( *this );
  IThread
    taskThread( task, true );

  // Create and show the window with the progress indicator.
  ProgressWindow
   *progressWindow = new ProgressWindow( this,
                                         "Status of a Long-Running Task",
                                         task );
  progressWindowHandle = progressWindow->handle();
  (*progressWindow)
   .setAutoDeleteObject();
  (*progressWindow)
   .setDestroyOnClose()
   .setFocus()
   .show();

  return *this;
}

PrimaryWindow&
  PrimaryWindow::setPercentComplete ( unsigned long percent )
{
  unsigned long
    newPercent = percent;
  if ( newPercent > 100 )
  {
     newPercent = 100;
  }

  // Update the progress indicator if we have one.
  ProgressWindow
   *progressWindow = 0;
  if ( progressWindowHandle  &&  progressWindowHandle.isValid() )
  {
     progressWindow = (ProgressWindow*)
               IWindow::windowWithHandle( progressWindowHandle );
     if ( progressWindow )
     {
        (*progressWindow)
         .setPercentDone( newPercent );
     }
     else
     {
        progressWindowHandle = 0;
     }
  }
  else
  {
     progressWindowHandle = 0;
  }

  if ( newPercent == 100 )
  {       // The long-running task is finished.
     this->cleanupTask();
  }
  return *this;
}

PrimaryWindow& PrimaryWindow::cleanupTask ( )
{
  // Update the progress indicator if we have one.
  ProgressWindow
   *progressWindow = 0;
  if ( progressWindowHandle  &&  progressWindowHandle.isValid() )
  {
     progressWindow = (ProgressWindow*)
               IWindow::windowWithHandle( progressWindowHandle );
     if ( progressWindow )
     {
        progressWindow->close();
        progressWindowHandle = 0;
     }
     else
     {
        progressWindowHandle = 0;
     }
  }
  else
  {
     progressWindowHandle = 0;
  }
  startButton
   .enable();

  return *this;
}

PrimaryWindow::StartThreadHdr::StartThreadHdr ( PrimaryWindow& window )
  : ICommandHandler( ),
    primaryWindow( window )
{ }

IBase::Boolean
  PrimaryWindow::StartThreadHdr::command ( ICommandEvent& event )
{
  Boolean stopProcessing = false;
  if ( event.commandId() == ID_START_TASK_CMD )
  {
     primaryWindow.startTask();
     stopProcessing = true;
  }
  return stopProcessing;
}

LongRunningTask::LongRunningTask ( PrimaryWindow& primary )
  : IThreadFn( ),
    primaryWindow( primary ),
    timer( ),
    count( 0 ),
    percentComplete( 0 )
{ }

void LongRunningTask::run ( )
{
  // Start a timer to substitute for a real time-consuming task.
  // Have this object's portionComplete function called every
  // .5 seconds.
  timer
   .setInterval( 500 )
   .start( new ITimerMemberFn< LongRunningTask >
                  ( *this, LongRunningTask::portionComplete ) );

  // Let the thread execute for as long as the timer is running.
  // The processMsgs call will end when the timer stops and no
  // primary windows exist on this thread.
  IThread::current().processMsgs();
}

void LongRunningTask::portionComplete ( unsigned long )
{
  count++;
  unsigned long
    percent( 0 );
  switch ( count % 5 )
  {    // Generate a pseudo-random value to represent how
       // much of the task has completed.
     case 0:
       percent = 4;
       break;
     case 1:
       percent = 8;
       break;
     case 2:
       percent = 3;
       break;
     case 3:
       percent = 6;
       break;
     case 4:
     default:
       percent = 5;
       break;
  }

  percentComplete += percent;
  if ( percentComplete >= 100 )
  {
     percentComplete = 100;
  }
  primaryWindow
   .setPercentComplete( percentComplete );

  if ( percentComplete == 100 )
  {      // End this thread by stopping the timer.
     timer
      .stop();
  }
}

void LongRunningTask::stop ( )
{
  // Stop the timer, which is our long-running task.
  timer
   .stop();
  primaryWindow
   .cleanupTask();
}

ProgressWindow::ProgressWindow ( IWindow*         owner,
                                 const char*      title,
                                 LongRunningTask* task )
  : IFrameWindow( 1000, 0, owner, IRectangle(),
                  IFrameWindow::classDefaultStyle,
                  title ),
    canvasClient( IC_FRAME_CLIENT_ID, this, this ),
    progressIndicator( 100, &canvasClient, &canvasClient,
                       IRectangle(), 5, 0,
                       ( IProgressIndicator::defaultStyle()
                           & ~IProgressIndicator::alignCentered )
                         | IProgressIndicator::alignBottom ),
    label( 200, &canvasClient, &canvasClient ),
    stopButton( ID_STOP_CMD, &canvasClient, &canvasClient ),
    stopCmdHandler( task )
{
  stopCmdHandler
   .handleEventsFor( this );

  progressIndicator
   .setShaftBreadth( progressIndicator.shaftSize().height() * 3 / 2 );

  // Set the length of the tick marks and define the tick text for
  // the progress indicator.  We minimize the number of ticks to
  // avoid sizing problems and to avoid clipping or overlapping
  // the tick text.
  progressIndicator
   .setTickLength( 10 );
  for ( int i = 0; i <= 4; i++ )
  {
      progressIndicator
       .setTickText( i, IString( i * 25 ) );
              // Label ticks with "0," "25," "50," "75," "100."
  }

  // Replace the minimum size of the progress indicator because
  // IProgressIndicator does not return a reliable one.
  progressIndicator
   .setMinimumSize( ISize( 350, 70 ) );

  label
   .setAlignment( IStaticText::centerCenter )
   .setText( "Percentage complete" );

  stopButton
   .enableDefault()
#ifdef IC_WIN
   .setText( "&Stop" )
#else
   .setText( "~Stop" )
#endif
   .enableTabStop()
   .enableGroup();

  // Define the rules for positioning controls on the multicell
  // canvas and adding white space when growing the canvas.
  canvasClient
   .addToCell( &progressIndicator, 2, 2, 2 )
   .addToCell( &label,             2, 4, 2 )
   .addToCell( &stopButton,        2, 6 )
   .setRowHeight( 1, IMultiCellCanvas::defaultCell().height(), true )
   .setRowHeight( 5, IMultiCellCanvas::defaultCell().height(), true )
   .setRowHeight( 7, IMultiCellCanvas::defaultCell().height() )
   .setColumnWidth( 3, 0, true )
   .setColumnWidth( 4, IMultiCellCanvas::defaultCell().width() );

  // Size the frame window and center it on the screen.
  ISize
    clientSize( canvasClient.minimumSize() );
  (*this)
   .setClient( &canvasClient )
   .moveSizeToClient( IRectangle( IPoint(), clientSize ) );
  IRectangle
    frameRect = this->rect();
  frameRect
   .centerAt( IWindow::desktopWindow()->rect().center() );
  this->moveTo( frameRect.minXMinY() );
}

ProgressWindow& ProgressWindow::setPercentDone ( unsigned long percent )
{
  // Some basic error checking.
  unsigned long
    percentToUse = percent;
  if ( percentToUse > 100 )
  {
     percentToUse = 100;
  }

  // We need to deal with pixel offsets instead of ticks because we
  // only have five ticks but need to appear that we support 101.
  unsigned long
    totalPixels = progressIndicator.armRange() - 1,
    newArmOffset = totalPixels * percentToUse / 100;
  progressIndicator
   .moveArmToPixel( newArmOffset );

  return *this;
}

ProgressWindow::StopCmdHandler::StopCmdHandler ( LongRunningTask* task )
  : ICommandHandler( ),
    runningTask( task )
{ }

IBase::Boolean
  ProgressWindow::StopCmdHandler::command ( ICommandEvent& event )
{
  Boolean
    stopProcessing = false;
  if ( event.commandId() == ID_STOP_CMD )
  {
     runningTask->stop();
     stopProcessing = true;
  }
  return stopProcessing;
}
