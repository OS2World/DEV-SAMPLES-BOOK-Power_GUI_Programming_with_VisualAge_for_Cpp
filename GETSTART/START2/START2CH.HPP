#ifndef _START2CH_
#define _START2CH_
//*********************************************************
// Getting Started - Simple Program, Version 2
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//*********************************************************
#include <icmdhdr.hpp>

class CutCopyPasteHandler : public ICommandHandler {
protected:
virtual Boolean
  command ( ICommandEvent& event );
}; // CutCopyPasteHandler

#endif  // _START2CH_
