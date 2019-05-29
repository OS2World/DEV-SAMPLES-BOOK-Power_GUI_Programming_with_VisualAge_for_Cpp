/***************************************************************
* FILE NAME: easy.cpp                                          *
*                                                              *
* DESCRIPTION:                                                 *
*   Sample program demonstrating use of simplified             *
*   "threadFn" template function to generate an                *
*   IThreadMemberFn object.                                    *
*                                                              *
* COPYRIGHT:                                                   *
*   Licensed Materials - Property of Solution Frameworks       *
*   Copyright (C) 1996, Solution Frameworks                    *
*   All Rights Reserved                                        *
***************************************************************/
#include <iostream.h>

#include <istring.hpp>

#include "improved.hpp"

const char
  theHardWay[] = "using \"new IThreadMemberFn<MyClass>"
                          "( myObject, MyClass::foo )\"",
  theEasyWay[] = "using \"threadFn( myObject, MyClass::bar )\"";

// Here's a typicall C++ class.  It has two member functions
// that we'll run on a separate thread.
struct MyClass {
void foo ( ) {
  cout << "I was started " << theHardWay << endl;
}
void bar ( ) {
  cout << "I was started " << theEasyWay << endl;
}
};

void main()
  {
  // An object of that class.
  MyClass
    myObject;

  // Start MyClass::foo the hard way.
  IThread
    hard;

  hard.start( new IThreadMemberFn<MyClass>( myObject, MyClass::foo ) );

  // Start MyClass::bar the easy way.
  IThread
    easy;

  easy.start( threadFn( myObject, MyClass::bar ) );

#ifdef IC_PM
  IThread::current().waitForAllThreads();
#else
  IThread::current().sleep( 1000 );
#endif
  }
