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
#include <istring.hpp>

// Retrieves messages from queue, creates objects from them,
// and sends to main window.
class QueueReader {
public:
QueueReader  ( const char*          queueName,
               const IWindowHandle& receiver);
~QueueReader ( );

void
  run           ( );
unsigned long
 queueHandle    ( ) const { return qHandle;}
IWindowHandle
 targetHandle   ( ) const { return target;}

private:
IWindowHandle
  target;
unsigned long
  qHandle;
char
  *queueData;
IString
  fqueueName;

QueueReader    (const QueueReader&);
QueueReader
  &operator=   (const QueueReader&);
};
#endif  // _QUERDR_
