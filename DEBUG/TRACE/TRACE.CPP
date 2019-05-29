//************************************************************
// Problem Determination - Simple Trace Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <itrace.hpp>
#include <istring.hpp>

int foo(unsigned long count);

void main()
{
   IMODTRACE_DEVELOP("main");
   foo(10);
}

int foo(unsigned long count)
{
  IFUNCTRACE_DEVELOP();
  ITRACE_DEVELOP(IString("The count is ")+IString(count).d2x());
  return 0;
}
