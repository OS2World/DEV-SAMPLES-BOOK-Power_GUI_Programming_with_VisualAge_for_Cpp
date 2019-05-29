/***************************************************************
* FILE NAME: fixed.cpp                                         *
*                                                              *
* DESCRIPTION:                                                 *
*   Sample program demonstrating how ImprovedThread and        *
*   ImprovedThreadFn classes solve problems demonstrated       *
*   in broken.cpp.                                             *
*                                                              *
* COPYRIGHT:                                                   *
*   Licensed Materials - Property of Solution Frameworks       *
*   Copyright (C) 1996, Solution Frameworks                    *
*   All Rights Reserved                                        *
***************************************************************/
#include <iostream.h>

#include <ithread.hpp>
#include <istring.hpp>

#include "improved.hpp"

struct MyClass {
void foo ( )
  {
  cout << "MyClass::foo called\n";
  }
};

void main()
  {
  MyClass
    myObject;

  //IThreadMemberFn<MyClass>
  ThreadableMemberOf<MyClass>
    // Here's an IThreadFn object on the stack (seems reasonable).
    memberFn1( myObject, MyClass::foo ),
    // Here's an IThreadFn object allocated on the heap.
   //*memberFn2( new IThreadMemberFn<MyClass>( myObject, MyClass::foo ) );
   *memberFn2( new ThreadableMemberOf<MyClass>( myObject, MyClass::foo ) );

  //IThread
  ImprovedThread
    thread1( &memberFn1 ),
    thread2( memberFn2 );

#ifdef IC_PM
  IThread::current().waitForAllThreads();
#else
  IThread::current().sleep(1000);
#endif

  // We have to delete the object we allocated, right?
  delete memberFn2;
  }
