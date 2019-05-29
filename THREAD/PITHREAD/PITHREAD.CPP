/*******************************************************************************
* FILE NAME: pithread.cpp                                                      *
*                                                                              *
* DESCRIPTION:                                                                 *
*   IThread sample program demonstrating thread creation using an              *
*   interesting (albeit worthless) function.                                   *
*                                                                              *
* COPYRIGHT:                                                                   *
*   Licensed Materials - Property of Solution Frameworks                       *
*   Copyright (C) 1996, Solution Frameworks                                    *
*   All Rights Reserved                                                        *
*******************************************************************************/
#ifndef _ITHREAD_
  #include <ithread.hpp>
#endif
#ifndef _IFRAME_
  #include <iframe.hpp>
#endif
#ifndef _IMLE_
  #include <imle.hpp>
#endif
#ifndef _IMCELCV_
  #include <imcelcv.hpp>
#endif
#ifndef _IPUSHBUT_
  #include <ipushbut.hpp>
#endif
#ifndef _ISTATTXT_
  #include <istattxt.hpp>
#endif
#ifndef _IENTRYFD_
  #include <ientryfd.hpp>
#endif
#ifndef _ICMDHDR_
  #include <icmdhdr.hpp>
#endif
#ifndef _ISTRING_
  #include <istring.hpp>
#endif

#include "userevt.hpp"
#include "pi.hpp"

/*----------------------- PiOnAThread --------------------------
| This simple IThreadFn derivative calculates pi to some       |
| arbitrary number of digits.  The results are sent as a       |
| user-defined event to some window.                           |
--------------------------------------------------------------*/
class PiOnAThread : public IThreadFn {
public:
  PiOnAThread ( unsigned digits,
                const IWindowHandle &window )
    : arg( digits ),
      win( window )
    {
    }
virtual void
  run ( )
    {
    IString
      result = pi( arg );
    UserEvent( 0, (char*)result ).sendTo( win );
    }
private:
unsigned
  arg;
IWindowHandle
  win;
PiOnAThread( const PiOnAThread& );
operator = ( const PiOnAThread& );
};

/*---------------------- ResultHandler -------------------------
| This user-define event handler accepts the result string     |
| and adds this text to an MLE control.                        |
--------------------------------------------------------------*/
struct ResultHandler : public UserHandler {
  ResultHandler ( IMultiLineEdit &output )
    : UserHandler( 0 ), output( output ) {
    handleEventsFor( &output );
  }   
  ~ResultHandler ( ) {
    stopHandlingEventsFor( &output );
  }
virtual Boolean
  handleUserEvent ( UserEvent &event ) {
    output
      .addLineAsLast( (char*)event.parameter1() )
      .refresh();
    return false;
  }
private:
IMultiLineEdit
 &output;
ResultHandler ( const ResultHandler& );
operator = ( const ResultHandler& );
}; // ResultHandler

struct Controller : public ICommandHandler {
  Controller ( IFrameWindow   &frame,
               IPushButton    &button,
               IEntryField    &input,
               IMultiLineEdit &output )
    : frame( frame ),
      button( button ),
      input( input ), 
      output( output ),
      resultHandler( output ) {
    this->handleEventsFor( &frame );
  }
  ~Controller ( ) {
    stopHandlingEventsFor( &frame );
  }
virtual Boolean
  command ( ICommandEvent &event ) {
    Boolean
      result = false;
    if ( event.commandId() == button.id() ) {
      unsigned long
        numDigits( input.text().asUnsigned() );
      output
        .addLineAsLast( "Calculating pi to " 
                        + 
                        IString(numDigits) 
                        + 
                        " digits..." )
        .refresh();
      IThread
        calculatePi;
      calculatePi.start( new PiOnAThread(
                               (unsigned)input.text().asInt(),
                               output.handle() ) );
      result = true;
    }
    return result;
  }
private:
IFrameWindow
 &frame;
IPushButton
 &button;
IEntryField
 &input;
IMultiLineEdit
 &output;
ResultHandler
  resultHandler;
  Controller( const Controller & );
  operator= ( const Controller & );
}; // Controller

void main ( ) {
  IFrameWindow
    frame( "Pi Calculator" );
  IMultiLineEdit
    client( 0, &frame, &frame );
  frame.setClient( &client );

  IMultiCellCanvas
    canvas( 0, &frame, &frame );
  IPushButton
    start( 1, &canvas, &canvas );
  IStaticText
    prompt( 2, &canvas, &canvas );
  IEntryField
    input( 3, &canvas, &canvas );

  frame.addExtension( &canvas, IFrameWindow::aboveClient, 38 );

  canvas
    .setDefaultCell( ISize( 3, 2 ) );

  canvas
    .addToCell( &start, 2, 2, 1 )
    .addToCell( &prompt, 4, 2, 2 )
    .addToCell( &input, 7, 2, 3 )
    .setRowHeight( 1, 2 )
    .setRowHeight( 2, 34, true )
    .setRowHeight( 3, 2 )
    .setColumnWidth( 2, 100, true )
    .setColumnWidth( 4, 200, true )
    .setColumnWidth( 7, 300, true );

  start.setText( "Calculate" );

  prompt.setText( "Number of digits:" );
  prompt.setAlignment( IStaticText::centerRight );

  input.setText( "100" );

  Controller
    controller( frame, start, input, client );

  frame.setFocus();
  frame.showModally();
}
