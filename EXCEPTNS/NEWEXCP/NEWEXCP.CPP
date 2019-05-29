//************************************************************
// Error Handling - New Exception Class
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <iexcbase.hpp>
#include <itrace.hpp>
#include "custexcp.hpp"

void main()
{
  IFUNCTRACE_RUNTIME();
  ITrace::enableTrace();
  ITrace::writeToStandardOutput();
  CustomException exc("Hey dude!  Bet you thought this was a real program!",
                      -1);
  ITHROW(exc);
}
