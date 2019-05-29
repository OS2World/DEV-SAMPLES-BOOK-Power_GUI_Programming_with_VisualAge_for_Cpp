/***************************************************************
* FILE NAME: picalc.cpp                                        *
*                                                              *
* DESCRIPTION:                                                 *
*   Another thread sample; this time using a PiCalculator      *
*   object instead of a plain function.                        *
*                                                              *
* COPYRIGHT:                                                   *
*   Licensed Materials - Property of Solution Frameworks       *
*   Copyright (C) 1996, Solution Frameworks                    *
*   All Rights Reserved                                        *
***************************************************************/
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

/*----------------------- PiCalculator -------------------------
| Simple class with a member function to calculate pi to       |
| some number of digits and then send a user-defined event     |
| to a frame window, passing the result.                       |
--------------------------------------------------------------*/
class PiCalculator {
public: 
// Construct with an MLE to be updated with the results.
  PiCalculator( IMultiLineEdit &mle )
    : digits( 0 ), results( mle ) {
    }
// This function calculates pi and updates the result window.
void
  calculate ( )
    {
    IString  result = pi( digits );
    UserEvent( 0, (char*)result ).sendTo( results.handle() );
    }
// Use this function to set the number of digits to calculate.
void
  setDigits ( unsigned long numDigits ) {
    digits = numDigits;
  }
private:
unsigned long
  digits;
IMultiLineEdit 
 &results;
PiCalculator ( const PiCalculator& );
operator = ( const PiCalculator& );
};

/*---------------------- ResultHandler -------------------------
| Handler for user-defined event that occurs when a result     |
| has been calculated.  We simply add the result as the        |
| last line of the associated MLE.                             |
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

/*------------------------ Controller --------------------------
| This class is basically a command handler that ties          |
| together the various parts of our pi calculator user         |
| interface.                                                   |
|                                                              |
| It wires together a frame window, a button, and input and    |
| output controls.  When the button is pressed, it takes       |
| the input field and calculates pi to however many digits     |
| is specified.  The results are written to the output         |
| control (an MLE).                                            |
--------------------------------------------------------------*/
struct Controller : public ICommandHandler {
  Controller ( IFrameWindow   &frame,
               IPushButton    &button,
               IEntryField    &input,
               IMultiLineEdit &output )
    : frame( frame ),
      button( button ),
      input( input ), 
      output( output ),
      resultHandler( output ),
      calculator( output ) {
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
                        " digits..." );
      calculator.setDigits( numDigits );
      IThread
        calculatePi;

      calculatePi.start(
            new IThreadMemberFn<PiCalculator>( 
                             calculator,
                             PiCalculator::calculate ) );

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
PiCalculator
  calculator;
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
