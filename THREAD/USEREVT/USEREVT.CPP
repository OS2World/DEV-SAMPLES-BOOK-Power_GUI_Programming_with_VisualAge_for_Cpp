/***************************************************************
* FILE NAME: userevt.cpp                                       *
*                                                              *
* DESCRIPTION:                                                 *
*   This file contains the implementation of                   *
*   classes/functions declared in userevt.hpp.                 *
*                                                              *
* COPYRIGHT:                                                   *
*   Licensed Materials - Property of Solution Frameworks       *
*   Copyright (C) 1996, Solution Frameworks                    *
*   All Rights Reserved                                        *
***************************************************************/
#ifdef __OS2__
#define INCL_PM
#include <os2.h>
#else
#include <windows.h>
#endif

#include <iwindow.hpp>

#include "userevt.hpp"

/*------------------- UserEvent::UserEvent ---------------------
| The constructors just pass the arguments to the base         |
| class's constructor.                                         |
--------------------------------------------------------------*/
UserEvent :: UserEvent ( unsigned int            id,
                         const IEventParameter1 &mp1,
                         const IEventParameter2 &mp2 ) 
  : IEvent( IWindowHandle( 0 ), baseId() + id, mp1, mp2 ) {
}

UserEvent :: UserEvent ( const IEvent &genericEvent )
  : IEvent( genericEvent ) {
}

UserEvent :: ~UserEvent ( ) {
}

/*------------------ UserEvent::userEventId --------------------
| Map the event identifier to the system-independent portion   |
| by subtracting the system-dependent base value.              |
--------------------------------------------------------------*/
unsigned long UserEvent :: userEventId ( ) const {
  return this->eventId() - baseId();
}

/*-------------------- UserEvent::postTo -----------------------
| Post the event to the argument window handle.                |
--------------------------------------------------------------*/
void UserEvent :: postTo ( const IWindow &window ) const {
  postTo( window.handle() );
}
void UserEvent :: postTo ( const IWindowHandle &window ) const {
  window.postEvent( eventId(), parameter1(), parameter2() );
}

/*-------------------- UserEvent::sendTo -----------------------
| Send the event to the argument window handle.                |
--------------------------------------------------------------*/
unsigned long 
  UserEvent :: sendTo ( const IWindow &window ) const {
  return sendTo( window.handle() );
}
unsigned long 
  UserEvent :: sendTo ( const IWindowHandle &window ) const {
  return window.sendEvent( eventId(), 
                           parameter1(), 
                           parameter2() );
}

/*-------------------- UserEvent::baseId -----------------------
| On OS/2, use WM_USER.                                        |
| On Windows, use WM_USER + 500 (Windows itself uses some in   |
| the range WM_USER to WM_USER+500).                           |
--------------------------------------------------------------*/
unsigned long UserEvent :: baseId ( ) {
  #ifdef __OS2__
    return WM_USER;
  #else
    return WM_USER + 500;
  #endif
}

/*----------------- UserHandler::UserHandler -------------------
| Set the handler's low/high event identifiers.                |
--------------------------------------------------------------*/
UserHandler :: UserHandler ( unsigned long id )
  : low( UserEvent::baseId() + id ),
    high( UserEvent::baseId() + id ) {
}

UserHandler :: UserHandler ( unsigned long low, unsigned long high )
  : low( UserEvent::baseId() + low ),
    high( UserEvent::baseId() + high ) {
}

UserHandler :: ~UserHandler ( ) {
}

/*--------------- UserHandler::handleUserEvent -----------------
| Default implementation simply returns false.  Derived        |
| class must override this function.                           |
--------------------------------------------------------------*/
Boolean UserHandler :: handleUserEvent( UserEvent &event ) {
  return false;
}

/*------------ UserHandler::dispatchHandlerEvent ---------------
| If the event identifier is in the range of interest to this  |
| handler, call the handleUserEvent member function.           |
--------------------------------------------------------------*/
Boolean UserHandler :: dispatchHandlerEvent ( IEvent &event ) {
  Boolean
    result = false;
  if ( event.eventId() >= low
       &&
       event.eventId() <= high ) {
    UserEvent
      userEvent( event );
    result = handleUserEvent( userEvent );
    event.setResult( userEvent.result() );
  }
  return result;
}
