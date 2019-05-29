#ifndef _SERVICE_
#define _SERVICE_
/***************************************************************
* FILE NAME: service.hpp                                       *
*                                                              *
* DESCRIPTION:                                                 *
*   This file contains the declaration(s) of the class(es):    *
*     ServiceThread - Long-running thread that you can post    *
*                     requests to.                             *
*                                                              *
* COPYRIGHT:                                                   *
*   Licensed Materials - Property of Solution Frameworks       *
*   Copyright (C) 1996, Solution Frameworks                    *
*   All Rights Reserved                                        *
***************************************************************/
#ifndef _ITHREAD_
  #include <ithread.hpp>
#endif

class ServiceThreadData;

class ServiceThread {
public:
/*----------------- Constructors/Destructor --------------------
| Note that the constructor automatically starts a secondary   |
| thread of execution and the destructor terminates that       |
| thread.                                                      |
--------------------------------------------------------------*/
  ServiceThread ( );
  ~ServiceThread ( );

/*--------------------- Request Handling -----------------------
| Use this function to post a request to the thread.           |
--------------------------------------------------------------*/
virtual void
  postRequest( const IReference<IThreadFn> &request );

private:
static void
  run ( void * );
ServiceThreadData
 *data;
}; // ServiceThread

#endif // _SERVICE_
