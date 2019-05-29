#ifndef _USEREVT_
#define _USEREVT_
/***************************************************************
* FILE NAME: userevt.hpp                                       *
*                                                              *
* DESCRIPTION:                                                 *
*   This file contains the declaration(s) of the class(es):    *
*     UserEvent   - Portable user-defined event class.         *
*     UserHandler - Handler for UserEvents.                    *
*                                                              *
* COPYRIGHT:                                                   *
*   Licensed Materials - Property of Solution Frameworks       *
*   Copyright (C) 1996, Solution Frameworks                    *
*   All Rights Reserved                                        *
***************************************************************/
#ifndef _IEVENT_
  #include <ievent.hpp>
#endif
#ifndef _IHANDLER_
  #include <ihandler.hpp>
#endif

/*------------------------ UserEvent ---------------------------
| Objects of this class represent "user-defined" events (i.e., |
| WM_USER events).                                             |
|                                                              |
| You can provide these attributes when you construct a        |
| UserEvent:                                                   |
|   o an ID (which is ultimately added to WM_USER)             |                
|   o event parameter 1                                        |                
|   o event parameter 2                                        |                
|                                                              |                
| Within a handler, you construct the UserEvent from the       |
| IEvent received in your dispatchHandlerEvent function.       |                                
|                                                              |
| See UserHandler, below.                                      |
--------------------------------------------------------------*/
class UserEvent : public IEvent {
public:
  UserEvent ( unsigned int            id  = 0,
              const IEventParameter1 &mp1 = 0,
              const IEventParameter2 &mp2 = 0 );

  UserEvent ( const IEvent &genericEvent );

  ~UserEvent ( );

/*----------------------- userEventId --------------------------
| This function returns the user-defined event id for this     |
| event object.  Typically, you call this from within your     |
| UserHandler-derived classes' handleUserEvent override to     |
| determine the particular user-defined event that has         |
| occurred.                                                    |       
--------------------------------------------------------------*/
unsigned long
  userEventId ( ) const;

/*---------------------- postTo/sendTo -------------------------
| You use these functions to post or send the user-defined     |
| event object to a given window handle.                       |
--------------------------------------------------------------*/
void
  postTo ( const IWindow       &window ) const,
  postTo ( const IWindowHandle &window ) const;

unsigned long
  sendTo ( const IWindow       &window ) const,
  sendTo ( const IWindowHandle &window ) const;

/*-------------------------- baseId ----------------------------
| This function returns the "base" id for all user-defined     |
| events.  Essentially, it is a portable alias for "WM_USER."  |
--------------------------------------------------------------*/
static unsigned long
  baseId ( );
}; // class UserEvent

/*----------------------- UserHandler --------------------------
| This is the abstract base class for handlers of user-defined |
| events.  You create handlers for such events by deriving     |
| from this class and overriding the handleUserEvent function. |
|                                                              |
| The base class provides support for intercepting a range     |
| of user-defined event identifiers.  You provide the range
| of identifiers to the constructor.  These identifiers are    |
| added to UserEvent::baseId() to determine the event          |
| identifiers that get handled.  The default is to handle      |
| just UserEvent::baseId().                                    |
--------------------------------------------------------------*/
class UserHandler : public IHandler {

protected:
  UserHandler ( unsigned long id = 0 );
  UserHandler ( unsigned long low, unsigned long high );

  ~UserHandler ( );

virtual Boolean
  handleUserEvent( UserEvent &event ) = 0;


virtual Boolean
  dispatchHandlerEvent ( IEvent &event );

private:
unsigned long
  low,
  high;
}; // class UserHandler

#endif // _USEREVT_
