/***************************************************************
* FILE NAME: signal.cpp                                        *
*                                                              *
* DESCRIPTION:                                                 *
*   This file contains the implementation of                   *
*   classes/functions declared in signal.hpp.                  *
*                                                              *
* COPYRIGHT:                                                   *
*   Licensed Materials - Property of Solution Frameworks       *
*   Copyright (C) 1996, Solution Frameworks                    *
*   All Rights Reserved                                        *
***************************************************************/
#ifdef __OS2__
#define INCL_DOSSEMAPHORES
#define INCL_DOSERRORS
#include <os2.h>

#include <istring.hpp>
#else
#include <windows.h>
#endif

#include "signal.hpp"

#ifndef _IEXCEPT_
  #include <iexcept.hpp>
#endif

/*---------------------- Signal::Signal ------------------------
| The construcstors initialize the handle to zero and invoke   |
| the initialize member function (see below).                  |
--------------------------------------------------------------*/
Signal :: Signal ( Boolean     signalled,
                   const char *name ) 
  : handle( 0 ) {
    initialize( signalled, name );
  }

Signal :: Signal ( const char *name, 
                   Boolean     signalled )
  : handle( 0 ) {
    initialize( signalled, name );
  }

/*--------------------- Signal::~Signal ------------------------
| Under OS/2:                                                  |
|   Close the event semaphore using DosCloseEventSem.          |
| Under Windows:                                               |
|   Close the event semaphore using CloseHandle.               |
--------------------------------------------------------------*/
Signal :: ~Signal ( ) {
  #ifdef __OS2__
    unsigned long
      rc = DosCloseEventSem( handle );
    if ( rc != 0 )
      ITHROWSYSTEMERROR( rc, 
                         "DosCloseEventSem",
                         IErrorInfo::accessError,
                         IException::recoverable );
  #else
    if ( !CloseHandle( handle ) )
      ITHROWSYSTEMERROR( 1,
                         "CloseHandle",
                         IBaseErrorInfo::accessError,
                         IException::recoverable );
  #endif
  }

/*---------------------- Signal::reset -------------------------
| Under OS/2:                                                  |                
|   Reset the event semaphore using DosResetEventSem.          |
| Under Windows:                                               |                
|   Reset the event semaphore using ResetEvent.                |
--------------------------------------------------------------*/
Signal &Signal :: reset ( ) {
  #ifdef __OS2__
    unsigned long
      ct,
      rc = DosResetEventSem( handle, &ct );
    if ( rc != 0 )
      ITHROWSYSTEMERROR( rc,
                         "DosResetEventSem",
                         IErrorInfo::accessError,
                         IException::recoverable );
  #else
    if ( !ResetEvent( handle ) )
      ITHROWSYSTEMERROR( 1,
                         "ResetEvent",
                         IBaseErrorInfo::accessError,
                         IException::recoverable );
  #endif

  return *this;
}

/*---------------------- Signal::signal ------------------------
| Under OS/2:                                                  |
|   Post the event semaphore via DosPostEventSem.              |
| Under Windows:                                               |
|   Post the event semaphore via SetEvent.                     |
--------------------------------------------------------------*/
Signal &Signal :: signal ( )
  {
  #ifdef __OS2__
    unsigned long
      rc = DosPostEventSem( handle );
    if ( rc != 0 )
      ITHROWSYSTEMERROR( rc, 
                         "DosPostEventSem",
                         IErrorInfo::accessError,
                         IException::recoverable );
  #else
    if ( !SetEvent( handle ) )
      ITHROWSYSTEMERROR( 1,
                         "SetEvent",
                         IBaseErrorInfo::accessError,
                         IException::recoverable );
  #endif

  return *this;
  }

/*----------------------- Signal::wait -------------------------
| Under OS/2:                                                  |
|   Wait for the event semaphore using DosWaitEventSem.        |
| Under Windows:                                               |
|   Wait for the event semaphore using WaitForSinglObject.     |
--------------------------------------------------------------*/
Signal &Signal :: wait ( unsigned long timeout )
  {
  #ifdef __OS2__
    unsigned long
      rc = DosWaitEventSem( handle, timeout );
    if ( rc != 0 )
      ITHROWSYSTEMERROR( rc, 
                         "DosWaitEventSem",
                         IErrorInfo::accessError,
                         IException::recoverable );
  #else
    int
      rc = WaitForSingleObject( handle, timeout );
    if ( rc != WAIT_OBJECT_0 )
      ITHROWSYSTEMERROR( rc,
                         "WaitForSingleObject",
                         IBaseErrorInfo::accessError,
                         IException::recoverable );
  #endif

  return *this;
  }

/*-------------------- Signal::initialize ----------------------
| Initialize the event sempaphore object.                      |
|                                                              |
| Under OS/2:                                                  |
|   If a name is provided and it doesn't have the \SEM32\      |
|   prefix, insert the prefix.  Then create the event          |
|   semaphore using DosCreateEventSem.  If the creation        |
|   fails because it already existed, then open it using       |
|   DosOpenEventSem.                                           |
| Under Windows:                                               |
|   Just create the event semaphore using CreateEvent.         |
--------------------------------------------------------------*/
void Signal :: initialize ( Boolean initState, const char *name ) {
  Boolean
    shared = ( name != 0 );
  #ifdef __OS2__
    HEV
      hev = 0;
    IString
      sigName = name;
    if ( name && !IString( "\\SEM32\\" ).isAbbreviationFor( sigName ) ) {
      // Make sure name has proper prefix.
      sigName.insert( "\\SEM32\\", 0 );
    }
    unsigned long
      rc = DosCreateEventSem( name ? (const char*)sigName 
                                   : ( const char*)0,
                              &hev,
                              shared ? DC_SEM_SHARED : 0,
                              initState ? 1 : 0 );
    if ( rc == NO_ERROR ) {
      handle = hev;
    } else {
      if ( rc == ERROR_DUPLICATE_NAME ) {
        // Try to open it, then.
        rc = DosOpenEventSem( sigName, &hev );

        if ( rc == NO_ERROR ) {
          handle = hev;
        } else {
          ITHROWSYSTEMERROR( rc,
                             "DosOpenEventSem",
                             IErrorInfo::accessError,
                             IException::recoverable );
        }
      } else {
        ITHROWSYSTEMERROR( rc,
                           "DosCreateEventSem",
                           IErrorInfo::accessError,
                           IException::recoverable );
      }
    }
  #else
    HANDLE
      hev = 0;
    hev = CreateEvent( 0, TRUE, FALSE, name );
    if ( hev ) {
      handle = hev;
    } else {
      ITHROWSYSTEMERROR( 0,
                         "CreateEvent",
                         IBaseErrorInfo::accessError,
                         IException::recoverable );
    }
  #endif
}
