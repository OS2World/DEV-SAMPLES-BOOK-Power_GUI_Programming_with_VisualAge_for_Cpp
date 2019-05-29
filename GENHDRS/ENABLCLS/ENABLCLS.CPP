//*********************************************************
// Reusable Commands - Disable the Close Command
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//*********************************************************
#include <iapp.hpp>
#include <icmdhdr.hpp>
#include <iframe.hpp>
#include <imnitem.hpp>
#include <imsgbox.hpp>
#include <ipushbut.hpp>
#include <isetcv.hpp>
#include <istattxt.hpp>
#include <isysmenu.hpp>
#include <icconst.h>

#ifdef IC_PM
  // Define the system command identifier not originally
  // included in VisualAge for C++ for OS/2, V3.0.
  #ifndef IC_ID_CLOSE
    #define IC_ID_CLOSE  0x8004
  #endif
#endif

#define ID_TOGGLE_CLOSE  100

class CloseTestWindow : public IFrameWindow {
public:
  CloseTestWindow ( );
protected:
Boolean
  processCommand ( ICommandEvent& event );
private:
  CloseTestWindow ( const CloseTestWindow& );
CloseTestWindow
 &operator=       ( const CloseTestWindow& );
IStaticText
  instructions;
ISetCanvas
  buttons;
IPushButton
  closeButton,
  enableDisableButton;
ISystemMenu
  systemMenu;
ICommandConnectionTo< CloseTestWindow >
  cmdConnection;
static const IString
  closeInstructions,
  cannotCloseInstructions,
  enableCloseString,
  disableCloseString;
}; // CloseTestWindow

void main ( )
{
  CloseTestWindow
    frame;
  frame
   .setFocus()
   .show();
  IApplication::current().run();
}

const IString
  CloseTestWindow::closeInstructions( "You can close the window."
                     "  However, try disabling the Close command." ),
  CloseTestWindow::cannotCloseInstructions( "You cannot close the"
                     " window until you enable the Close command." ),
  CloseTestWindow::enableCloseString( "Enable the Close Command" ),
  CloseTestWindow::disableCloseString( "Disable the Close Command" );

CloseTestWindow::CloseTestWindow ( )
  : IFrameWindow( "Disabling the Close System Command" ),
    instructions( IC_FRAME_CLIENT_ID, this, this ),
    buttons( 1, this, this ),
    closeButton( IC_ID_CLOSE, &buttons, &buttons ),
    enableDisableButton( ID_TOGGLE_CLOSE, &buttons, &buttons ),
    systemMenu( this ),
    cmdConnection( *this, CloseTestWindow::processCommand )
{
  instructions
   .setText( closeInstructions );
  closeButton
   .enableSystemCommand()
   .enableDefault()
   .setText( "Close the Window" )
   .enableTabStop()
   .enableGroup();
  enableDisableButton
   .setText( disableCloseString );
  cmdConnection
   .handleEventsFor( this );

  (*this)
   .setClient( &instructions )
   .addExtension( &buttons, IFrameWindow::belowClient );
}

// This is the function that the ICommandConnectionTo<> object calls.
IBase::Boolean
  CloseTestWindow::processCommand ( ICommandEvent& event )
{
  Boolean
    stopProcessingEvent = false;
  switch ( event.commandId() )
  {
    case IC_ID_CLOSE:
    {    // Assume this is a system command.
       IMessageBox
         msgBox( this );
       const char
        *text;

       // When the Close system menu item is disabled, our command
       // handler usually is not called to process this system
       // command.  However, it is called when a user presses an
       // accelerator key for the Close command (Alt+F4)--even
       // though the system eventually ignores this request.  So
       // we must check if the system menu choice is disabled before
       // processing the Close command.
       if ( systemMenu.isItemEnabled( IC_ID_CLOSE ) )
       {      // Close is enabled.
          text = "The window is closing.  Select OK to continue.";
       }
       else
       {
          text = "The Close command is disabled.  You must enable"
                 " it to close the window.";
       }

       msgBox
        .show( text,
               IMessageBox::okButton
                 | IMessageBox::informationIcon
                 | IMessageBox::moveable );
       break;
    }
    case ID_TOGGLE_CLOSE:
    {    // Assume that this is an application command.
       // Toggle the enabled state of Close on the system menu.
       Boolean
         enableClose = ! systemMenu.isItemEnabled( IC_ID_CLOSE );
                   // Negate the current state.
       systemMenu
        .enableItem( IC_ID_CLOSE, enableClose );

       // Toggle the enabled state of the Close button.
       closeButton
        .enable( enableClose );
       instructions
        .setText( enableClose ? closeInstructions :
                                cannotCloseInstructions );
       enableDisableButton
        .setText( enableClose ? disableCloseString :
                                enableCloseString );

       stopProcessingEvent = true;
       break;
    }
    default:
       break;
  }
  return stopProcessingEvent;
}
