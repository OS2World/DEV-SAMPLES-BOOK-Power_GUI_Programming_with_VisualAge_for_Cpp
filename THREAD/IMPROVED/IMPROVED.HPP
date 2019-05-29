#ifndef _IMPROVED_
#define _IMPROVED_
/***************************************************************
* FILE NAME: improved.hpp                                      *
*                                                              *
* DESCRIPTION:                                                 *
*   This file contains the declaration(s) of the class(es):    *
*     ImprovedThreadFn - Improved version of IThreadFn         *
*     ImprovedThread   - Improved thread class that knows how  *
*                        to start ImprovedThreadFn objects     *
*                                                              *
* COPYRIGHT:                                                   *
*   Licensed Materials - Property of Solution Frameworks       *
*   Copyright (C) 1996, Solution Frameworks                    *
*   All Rights Reserved                                        *
***************************************************************/
#include <ithread.hpp>

/*--------------------- ImprovedThreadFn -----------------------
| The trick is that objects of this class can make copies      |                
| of themselves.  The improved thread class uses copies        |                
| rather than muck with reference counting the original.       |                
| We use private inheritance to ensure that these objects      |                
| don't get used accidentally with plain IThreads.             |                
--------------------------------------------------------------*/
class ImprovedThreadFn : private IThreadFn {
public:
// Default constructor.
  ImprovedThreadFn ( ) {
  }
// Pure virtual function to self-replicate.
virtual ImprovedThreadFn
 *copy ( ) const = 0;
// Promote inherited use count value.
public: IThreadFn::useCount;
// Let ImprovedThread use objects as IThreadFns.
friend class ImprovedThread;
private:
// Prohibit copies via other means.
ImprovedThreadFn( const ImprovedThreadFn& );
operator = ( const ImprovedThreadFn& );
};

/*-------------------- ThreadableMemberOf ----------------------
| This class template is used to generate "improved" function  |
| objects that can be used to start member functions on        |
| threads.  You use it just like IThreadMemberFn.              |
--------------------------------------------------------------*/
template < class T >
class ThreadableMemberOf : public ImprovedThreadFn {
public:
  ThreadableMemberOf ( T &object, void (T::*member)() )
    : obj( object ), mem( member )
    {
    }
virtual ThreadableMemberOf<T>
 *copy ( ) const
    {
    return new ThreadableMemberOf<T>( obj, mem );
    }
virtual void
  run ( )
    {
    (obj.*mem)();
    }
private:
T
 &obj;
typedef void (T::*ptrToMember)();
ptrToMember
  mem;
ThreadableMemberOf ( const ThreadableMemberOf<T> & );
operator = ( const ThreadableMemberOf<T> & );
};

/*------------------------ ImprovedThread ----------------------
| Improved thread class that handles reference-counted         |
| IThreadFn objects more elegantly.                            |
--------------------------------------------------------------*/
class ImprovedThread : public IThread {
public:
  ImprovedThread ( const ImprovedThreadFn *fnObject )
    : IThread( IReference<IThreadFn>( fnObject->copy() ) )
    {
    }
  ImprovedThread ( const ImprovedThreadFn &fnObject )
    : IThread( IReference<IThreadFn>( fnObject.copy() ) )
    {
    }
};

/*--------------------------- threadFn -------------------------
| Template function that serves as an IThreadMemberFn          |
| generator.                                                   |
|                                                              |
| Use this function in place of the more verbose               |
| "new IThreadMemberFn<YourClass>( object, YourClass::foo )."  |
--------------------------------------------------------------*/
template < class T >
IThreadMemberFn<T> *threadFn( T &obj, void (T::*mem)(void) ) {
  return new IThreadMemberFn<T>( obj, mem );
}

#endif // _IMPROVED_
