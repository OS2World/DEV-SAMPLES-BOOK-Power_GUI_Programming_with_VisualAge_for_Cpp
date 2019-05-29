/***************************************************************
* FILE NAME: broken.cpp                                        *
*                                                              *
* DESCRIPTION:                                                 *
*   Sample program demonstrating problems with reference-      *
*   counting of IThreadFn objects.                             *
*                                                              *
* COPYRIGHT:                                                   *
*   Licensed Materials - Property of Solution Frameworks       *
*   Copyright (C) 1996, Solution Frameworks                    *
*   All Rights Reserved                                        *
***************************************************************/
#include <iostream.h>

#include <ithread.hpp>
#include <istring.hpp>

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

  IThreadMemberFn<MyClass>
    // Here's an IThreadFn object on the stack (seems reasonable).
    memberFn1( myObject, MyClass::foo ),
    // Here's an IThreadFn object allocated on the heap.
   *memberFn2( new IThreadMemberFn<MyClass>( myObject, MyClass::foo ) );

  IThread
    thread1, thread2;

  thread1.start( &memberFn1 ),
  thread2.start( memberFn2 );

#ifdef IC_PM
  IThread::current().waitForAllThreads();
#else
  IThread::current().sleep(1000);
#endif

  // We have to delete the object we allocated, right?
  delete memberFn2;
  }
