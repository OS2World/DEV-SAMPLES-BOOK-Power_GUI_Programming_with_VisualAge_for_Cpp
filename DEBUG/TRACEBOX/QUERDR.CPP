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
  #ifndef WIN32_LEAN_AND_MEAN
    #define WIN32_LEAN_AND_MEAN
  #endif
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
const char     QUITMESSAGE[]  = "QuIt";
const unsigned QUITMESSAGELEN = 4;
#endif

// Set up the queue for reading.
QueueReader::QueueReader ( const char*           queueName,
                           const IWindowHandle&  targetWindow)
               : target(targetWindow),
                 qHandle (0),
                 queueData( 0 ),
                 fenabled ( true ),
                 finputFilter( ),
                 ffilterLock( ),
                 fqueueLock( ),
                 fRunning( false )
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

  // Make first entry the queue name.
  if (isEnabled())
    {
    IContainerObject* pobj = new IContainerObject(IString("Queue: ") + fqueueName);
    targetHandle().postEvent(ADD_OBJECT, pobj);
    }
}

// Delete the queue.
QueueReader::~QueueReader ( )
{
#ifdef IC_PM
  DosCloseQueue(queueHandle());
  if (queueData)
    DosFreeMem(queueData);
#else
  DWORD written;
  HANDLE queue = CreateFile( fqueueName,
                             GENERIC_WRITE,
                             FILE_SHARE_READ,
                             (LPSECURITY_ATTRIBUTES)NULL,
                             OPEN_EXISTING,
                             FILE_ATTRIBUTE_NORMAL,
                             (HANDLE)NULL );
  if (queue &&
      WriteFile(  queue,
                  QUITMESSAGE,
                  QUITMESSAGELEN,
                  &written,
                  NULL ))
     {
     CloseHandle( queue );
     IResourceLock lock(fqueueLock);
     CloseHandle( (HANDLE)queueHandle() );
     if (queueData)
        GlobalFree((HGLOBAL)queueData );
     }
  else
     {
     ITHROWGUIERROR2("WriteFile",
                    IBaseErrorInfo::accessError,
                    IException::recoverable );
     }
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

  // If already started just return.
  if (fRunning)
     return;
  else
     fRunning = true;

  {  // Establish scope for fqueueLock.

    //Lock the queue.
    IResourceLock lock( fqueueLock );

    while(fRunning)
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
      if ((dataLength == QUITMESSAGELEN) &&
          (strcmp(queueData, QUITMESSAGE) == 0) )
        fRunning = false;

#endif

      // Create an object and post a request to the main
      // thread to add it to the container.
      if ( isEnabled() && isIncluded(queueData) && fRunning )
        pobj = new IContainerObject(queueData);
      else
        pobj = 0;

#ifdef IC_PM
      DosFreeMem(queueData);
      queueData = 0;
#endif
      Boolean loop = pobj ? true : false;
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
  }  // scope of fqueueLock
}

/*------------------------------------------------------------------------------
| IBase::Boolean QueueReader::isIncluded                                       |
------------------------------------------------------------------------------*/
IBase::Boolean QueueReader::isIncluded ( const char* string ) const
{
   IString           inputString(string);
   IResourceLock     lock( ((QueueReader*)this)->filterLock() );
   Boolean           result = true;
   FilterSet::Cursor cursor( ((QueueReader*)this)->inputFilterSet() );
   for (cursor.setToFirst(); (result && cursor.isValid()); cursor.setToNext() )
      {
      if ( inputString.indexOf( cursor.element() ) )
         result = false;
      }
   return ( ((QueueReader*)this)->inputFilterSet().isExcludeList ) ?
           result : !result ;
}
