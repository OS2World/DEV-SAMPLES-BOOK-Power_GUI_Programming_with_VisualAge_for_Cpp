#ifndef _SIGNAL_
#define _SIGNAL_
/***************************************************************
* FILE NAME: signal.hpp                                        *
*                                                              *
* DESCRIPTION:                                                 *
*   This file contains the declaration(s) of the class(es):    *
*     Signal - Portable event semaphore class.                 *
*                                                              *
* COPYRIGHT:                                                   *
*   Licensed Materials - Property of Solution Frameworks       *
*   Copyright (C) 1996, Solution Frameworks                    *
*   All Rights Reserved                                        *
***************************************************************/
#ifndef __IVBASE__
  #include <ivbase.hpp>
#endif

#ifndef _IHANDLE_
  #include <ihandle.hpp>
#endif

/*----------------------- SignalHandle -------------------------
| Objects of this class are simple wrappers for OS/2's HEV or  |
| Windows' event HANDLE.                                       |
--------------------------------------------------------------*/
class SignalHandle : public IHandle {
public:
  SignalHandle ( Value hev = 0 )
    : IHandle( hev ) {
    }
};

/*-------------------------- Signal ----------------------------
| Objects of this class represent "signals" that application   |
| threads can post and wait on.  They correspond to operating  |
| system event semaphores.                                     |
|                                                              |
| Signals can be in either of two states:                      |
|   signalled - The signal has been set and subsequent wait    |
|               requests will not block.                       |
|   reset     - The signal has not been set; subsequent wait   |
|               requests will block until the signal is posted.|
|                                                              |
| Signals have 3 other attributes that are fixed at the time   |
| they are constructed:                                        |
|   name          - Arbitrary identifier for the signal; named |
|                   signals can be shared between processes.   |
|   initial state - The signal can initially be signalled or   |
|                   reset; the default is reset.               |
--------------------------------------------------------------*/
class Signal : public IVBase {
typedef IVBase
  Inherited;
public:
/*----------------- Constructors/Destructor --------------------
| There are two constructors (with default arguments) that     |
| permit a Signal to be constructed from any combination of    |
| an initial state and/or name.                                |       
--------------------------------------------------------------*/
  Signal ( Boolean     signalled = false,
           const char *name      = 0 );
  Signal ( const char *name, 
           Boolean     signalled = false );
  ~Signal ( );

/*------------------------ Signalling --------------------------
| You can manipulate Signals using these member functions:     |
|   reset  - Reset so that subsequent wait requests block.     |
|   signal - Set so tht subsequent wait requests don't block.  |
|   wait   - Wait for the event to be signalled.               |
--------------------------------------------------------------*/
virtual Signal
 &reset  ( ),
 &signal ( ),
 &wait   ( unsigned long timeout = 0xfffffffful );

private:
void
  initialize( Boolean, const char * );

SignalHandle
  handle;

  Signal    ( const Signal & );
  operator= ( const Signal & );
};

#endif // __SIGNAL__
