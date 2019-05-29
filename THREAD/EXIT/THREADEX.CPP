/*******************************************************************************
* FILE NAME: threadex.cpp                                                      *
*                                                                              *
* DESCRIPTION:                                                                 *
*   This sample demonstrates effects of the various techniques of thread       *
*   termination.                                                               *
*                                                                              *
* COPYRIGHT:                                                                   *
*   Licensed Materials - Property of Solution Frameworks                       *
*   Copyright (C) 1996, Solution Frameworks                                    *
*   All Rights Reserved                                                        *
*******************************************************************************/
#ifdef __OS2__
  #define INCL_DOSPROCESS
  #include <os2.h>
  #define OSExit( rc ) DosExit( EXIT_THREAD, rc )
#else
  #include <windows.h>
  #define OSExit( rc ) ExitThread( rc )
#endif

#include <iostream.h>

#include <stdlib.h>

#include <ithread.hpp>

#include <istring.hpp>

struct ReportDestruction {
  ReportDestruction ( const char *id )
    : id( id ) {
    }
  ~ReportDestruction ( ) {
    cout << id << " destroyed." << endl;
  }
const char
 *id;
};

void _Optlink normalExit( void *p ) {
  ReportDestruction
    object( "Stack based object" );
  cout << IString( (char*)p ) 
       << " exiting normally via return" 
       << endl;
  return;
}

void _Optlink osExit( void *p ) {
  ReportDestruction
    object( "Stack based object" );
  cout << IString( (char*)p ) 
       << " exiting via OS \"exit\"" 
       << endl;
  OSExit( 0 );
}

void _Optlink cLibExit( void *p ) {
  ReportDestruction
    object( "Stack based object" );
  cout << IString( (char*)p )
       << " exiting via _endthread" 
       << endl;
  _endthread();
}

void _Optlink iThreadExit( void *p ) {
  ReportDestruction
    object( "Stack based object" );
  cout << IString( (char*)p )
       << " exiting via IThread::exit" 
       << endl;
  IThread::current().exit(0);
}

ReportDestruction
  staticObject( "Global Static" );

void main( int, char *argv[] ) {
  ReportDestruction
    object( "Stack based object on primary thread" );

  IThread
    thread2( normalExit, "Thread 2" );
  IThread::current().waitFor( thread2 );

  IThread
    thread3( osExit, "Thread 3" );
  IThread::current().waitFor( thread3 );

  IThread
    thread4( cLibExit, "Thread 4" );
  IThread::current().waitFor( thread4 );

  IThread
    thread5( iThreadExit, "Thread 5" );
  IThread::current().waitFor( thread5 );

  IString
    exitMode( argv[1] );

  if ( exitMode == "" ) {
    exitMode = "normal";
  }

  if ( exitMode == "os" ) {
    cout << "Exiting primary thread via OS \"exit\"" << endl;
    OSExit( 0 );
  } else if ( exitMode == "endthread" ) {
    cout << "Exiting primary thread via _endthread" << endl;
    _endthread();
  } else if ( exitMode == "ithread" ) {
    cout << "Exiting primary thread via IThread::exit" << endl;
    IThread::current().exit(0);
  } else /* "normal" */ {
    cout << "Exiting primary thread normally via return" << endl;
  }

  return;
}
