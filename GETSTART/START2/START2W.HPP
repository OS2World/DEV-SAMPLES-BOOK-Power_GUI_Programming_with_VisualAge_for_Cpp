#ifndef _START2W_
#define _START2W_
//*********************************************************
// Getting Started - Simple Program, Version 2
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//*********************************************************
#include <iframe.hpp>
#include <imle.hpp>
#include "start2ch.hpp"      // For CutCopyPasteHandler.

class CodeWindow : public IFrameWindow {
public:
  CodeWindow ( const char* title );
virtual Boolean
  cut   ( ),
  copy  ( ),
  paste ( );

private:
// Disallow copy and assignment.
  CodeWindow ( const CodeWindow& );
CodeWindow
 &operator=  ( const CodeWindow& );

IMultiLineEdit
  mle;
CutCopyPasteHandler
  cmdHandler;
}; // CodeWindow

#endif  // _START2W_
