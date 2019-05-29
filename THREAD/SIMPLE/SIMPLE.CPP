#include <iframe.hpp>
#include <istattxt.hpp>
#include <ipushbut.hpp>
#include <icmdhdr.hpp>
#include <ithread.hpp>
#include <istring.hpp>

enum { cmdThreaded, cmdNotThreaded, cmdDone };

static const char
 *prompt = "Press a button to perform action";

/*-------------------------- Action ----------------------------
| This simple class provides a single member function that     |
| sleeps for 15 one-second intervals, updating a static        |
| text window at each iteration.  At the end, a command        |
| event is posted to a frame window.                           |
--------------------------------------------------------------*/
class Action {
public:
  Action ( IFrameWindow &frame,
           IStaticText  &status )
    : frame( frame ),
      status( status )
    {
    }
virtual void
  performAction ( )
    {
    // Sleep for 15 seconds.
    for ( int i = 15; i; i-- )
      {
      status
        .setText( IString( i ) )
        .refresh( IWindow::paintAllImmediate );
      IThread::current().sleep( 1000 );
      }
    status
      .setText( "" )
      .refresh( IWindow::paintAllImmediate );
    // Tell frame the action is "done."
    frame.postEvent( IWindow::command, cmdDone );
    }
private:
IFrameWindow
 &frame;
IStaticText
 &status;
Action ( const Action & );
operator = ( const Action & );
};

/*------------------------ CmdHandler --------------------------
| This class is a simple command handler that processes        |
| 3 separate commands:                                         |
|   cmdNotThreaded - Invokes Action::performAction on the      |
|                    current thread of execution               |
|   cmdThreaded    - Runs Action::performAction on a           |
|                    separate thread                           |
|   cmdDone        - Handles completion of an action by        |
|                    refreshing the frame window               |
--------------------------------------------------------------*/
class CmdHandler : public ICommandHandler {
public:
  // Handler attaches to frame + text.
  CmdHandler ( IFrameWindow &frame,
               IStaticText  &text,
               IStaticText  &status )
    : action( frame, status ),
      frame( frame ),
      text( text )
    {
    handleEventsFor( &frame );
    }
protected:
virtual Boolean
  command ( ICommandEvent &event )
    {
    switch ( event.commandId() )
      {
      case cmdThreaded:
        {
        frame.disable();
        text.setText( "Performing action on separate thread" );
        IThread
          thread;
        thread.start( new IThreadMemberFn<Action>
                        ( action, Action::performAction ) );
        break;
        }
      case cmdNotThreaded:
        frame.disable();
        text.setText( "Performing action on current thread" );
        text.refresh( IWindow::paintAllImmediate );
        action.performAction();
        break;
      case cmdDone:
        frame.enable();
        text.setText( prompt );
        break;
      }
    return true;
    }
private:
Action
  action;
IFrameWindow
 &frame;
IStaticText
 &text;
CmdHandler( const CmdHandler & );
operator = ( const CmdHandler & );
};

void main()
  {
  // Create the main window.
  IFrameWindow
    frame( "Multi-Threading Demo" );
  // Use static text for client area and status window.
  IStaticText
    client( IC_FRAME_CLIENT_ID, &frame, &frame ),
    status( 0, &frame, &frame );
  // Create command handler to process button clicks.
  CmdHandler
    handler( frame, status, client );
  client.setAlignment( IStaticText::centerCenter );
  status.setText( prompt );
  // Create buttons to trigger actions.
  IPushButton
    button1( cmdThreaded, &frame, &frame ),
    button2( cmdNotThreaded, &frame, &frame );
  button1.setText( "On another thread" );
  button2.setText( "On current thread" );
  // Put status window above client, buttons below.
  frame.addExtension( &status, IFrameWindow::aboveClient );
  frame.addExtension( &button1, IFrameWindow::belowClient );
  frame.addExtension( &button2, IFrameWindow::belowClient );
  frame.setClient( &client );
  // Make frame window a more reasonable size.
  frame.moveSizeTo( frame.rect().scaleBy(.5) );
  // Show the main window.
  frame.setFocus();
  frame.show();          
  // Process window events till user closes the main window.
  IThread::current().processMsgs();
  }
