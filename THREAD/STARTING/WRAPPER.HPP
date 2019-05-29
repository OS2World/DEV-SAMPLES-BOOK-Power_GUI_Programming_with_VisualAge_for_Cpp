#ifndef _WRAPPER_
#define _WRAPPER_
/***************************************************************
* FILE NAME: wrapper.hpp                                       *
*                                                              *
* DESCRIPTION:                                                 *
*   This file contains the declaration(s) of the class(es):    *
*     WrapperFor - Template class to "wrapper" functions       *
*                  compatible with Windows' CreateThread API.  *                               
*                                                              *
* COPYRIGHT:                                                   *
*   Licensed Materials - Property of Solution Frameworks       *
*   Copyright (C) 1996, Solution Frameworks                    *
*   All Rights Reserved                                        *
***************************************************************/

/*------------------------ WrapperFor --------------------------
| This is a class template that is used to generate            |
| "wrappers" for functions compatible with Windows'            |
| CreateThread API.                                            |
|                                                              |
| The template argument is the name of the function you        |
| wish to wrapper.  Note that the template argument is         |
| *not* a type name!                                           |
|                                                              |
| The class does two things:                                   |
|   1 - Implements a static member function that calls         |
|       the template argument.  This function has _Optlink     |
|       linkage and is thus compatible with IThread::start.    |
|   2 - Provides an operator that permits an object of this    |
|       class to be converted to a function pointer            |
|       compatible with IThread.  The returned function        |
|       address is that of the static member function          |
|       described above.  This operator permits an object of   |
|       this class to be passed to IThread::start (or an       |
|       IThread constructor).                                  |
|                                                              |
| You use this class template like so:                         |
|                                                              |
|    // Function we want to run on a thread:                   |
|    unsigned long _stdcall winFunction ( void * );            |
|                                                              |
|    // How to use this class template to run it:              |
|    IThread t( WrapperFor<winFunction>(), arg );              |
--------------------------------------------------------------*/
template < unsigned long (_stdcall *WinFunction)( void * ) >
struct WrapperFor {
static void
  wrapper( void *p ) {
    WinFunction( p );
  }
  operator IThread::OptlinkFnPtr () const {
    return (IThread::OptlinkFnPtr)wrapper;
  }
}; // WrapperFor<>

#endif // _WRAPPER_
