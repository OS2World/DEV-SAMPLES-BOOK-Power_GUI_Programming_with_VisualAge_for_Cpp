#ifndef _QUERDR_
#define _QUERDR_
//************************************************************
// Problem Determination  - Trace Queue Browser
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <ihandle.hpp>
#include <ireslock.hpp>
#include "filtdlg.hpp"

class QueueReader {
/**************************************************************************
* Class:   QueueReader                                                    *
*                                                                         *
* Purpose: Retrieves messages from queue, creates objects from them,      *
*          and sends to main window.                                      *
*                                                                         *
**************************************************************************/
public:
QueueReader  ( const char*          queueName,
               const IWindowHandle& receiver);
~QueueReader ( );

void
  run           ( );
unsigned long
 queueHandle    ( ) const                 { return qHandle;}
IWindowHandle
 targetHandle   ( ) const                 { return target;}

Boolean
   isEnabled    ( ) const                 { return fenabled; }
QueueReader
  &enable       ( Boolean enable=true )   { fenabled = enable; return *this; }

FilterSet
  &inputFilterSet ( )                     { return finputFilter; }

IResource
  &filterLock ( )                         { return ffilterLock; }

Boolean
  isIncluded (  const char* string ) const;


private:
IWindowHandle
  target;
unsigned long
  qHandle;
char
  *queueData;
Boolean
  fenabled;
FilterSet
  finputFilter;
IPrivateResource
  ffilterLock,
  fqueueLock;
Boolean
  fRunning;
IString
  fqueueName;

QueueReader    (const QueueReader&);
QueueReader
  &operator=   (const QueueReader&);
};
#endif  // _QUERDR_
