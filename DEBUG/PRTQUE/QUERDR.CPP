//************************************************************
// Problem Determination  - Trace Queue Browser
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <ibase.hpp>
#ifdef IC_PM
  #define INCL_DOSQUEUES
  #define INCL_DOSPROCESS
  #include <os2.h>
#else
  #include <windows.h>
#endif

#include <iexcept.hpp>
#include <icnrobj.hpp>
#include <ihandle.hpp>
#include <ithread.hpp>
#include "querdr.hpp"
#include "trbrowse.h"

#if (IC_MAJOR_VERSION < 320)
  #define IBaseErrorInfo IErrorInfo
#endif

#define     BUFFERSIZE      999

#ifdef IC_PM
const char     QUEUE_PATH[] = "\\QUEUES\\";
#else
const char     QUEUE_PATH[]   = "\\\\.\\mailslot\\";
#endif

// Set up the queue for reading.
QueueReader::QueueReader ( const char*           queueName,
                           const IWindowHandle&  targetWindow)
               : target   (targetWindow),
                 qHandle  ( 0 ),
                 queueData( 0 )
{
  fqueueName = IString(QUEUE_PATH) + IString(queueName);
#ifdef IC_PM
  unsigned long rc = DosCreateQueue(
                       &qHandle,
                       QUE_FIFO | QUE_CONVERT_ADDRESS,
                       fqueueName);
  if (rc!=0)
    ITHROWSYSTEMERROR(rc, "DosCreateQueue",
                      IBaseErrorInfo::accessError,
                      IException::recoverable );
#else
  qHandle = (unsigned long)
    CreateMailslot(
      fqueueName,                      /* identifier                      */
      BUFFERSIZE,                      /* maximum message size            */
      MAILSLOT_WAIT_FOREVER,           /* no time-out for read operations */
      (LPSECURITY_ATTRIBUTES) NULL);   /* no security attributes     */
  if ( qHandle == (unsigned long)INVALID_HANDLE_VALUE )
    ITHROWGUIERROR2("CreateMailSlot",
                   IBaseErrorInfo::accessError,
                   IException::recoverable );

  queueData = (char *)GlobalAlloc( GPTR, BUFFERSIZE+1 );
#endif
}

// Delete the queue.
QueueReader::~QueueReader ( )
{
#ifdef IC_PM
  DosCloseQueue(queueHandle());
  if (queueData)
    DosFreeMem(queueData);
#else
  CloseHandle( (HANDLE)queueHandle() );
  if (queueData)
     GlobalFree((HGLOBAL)queueData );
#endif
}

// Our Thread function that reads the queue.
void QueueReader::run ( )
{
  IContainerObject* pobj;
  unsigned long   dataLength;

#ifdef IC_PM
  unsigned long   rc;
  REQUESTDATA     request;
  BYTE            priority = 0;

  request.pid = IThread::current().id();
#endif

  while(1)
    {
    dataLength = 0;
#ifdef IC_PM
    rc = DosReadQueue (queueHandle(),
                       &request,
                       &dataLength,
                       (void**)&queueData,
                       0,
                       0,
                       &priority,
                       0);
    if(rc!=0)
      ITHROWSYSTEMERROR(rc, "DosReadQueue",
                        IBaseErrorInfo::accessError,
                        IException::recoverable );
#else
    ReadFile( (HANDLE)queueHandle(),
              queueData,
              BUFFERSIZE,
              &dataLength,
              (LPOVERLAPPED)NULL );
    queueData[dataLength] = '\0';
#endif

    // Create an object and post a request to the main
    // thread to add it to the container.
    pobj = new IContainerObject(queueData);

#ifdef IC_PM
    DosFreeMem(queueData);
    queueData = 0;
#endif
    Boolean loop = true;
    while(loop)
       {
       try
         {
         loop = false;
         targetHandle().postEvent(ADD_OBJECT, pobj);
         }
       catch (IException& )
         {
         // If we can't post (message queue full?),
         // wait a bit and try again.
         loop = true;
#ifdef IC_PM
         DosSleep(100);
#endif
         }
       }  // while posting
    } // while
}
