//*********************************************************
// Getting Started - Simple Program, Version 2
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//*********************************************************
#include "start2ch.hpp"
#include "start2w.hpp"
#include "start2.h"

IBase::Boolean 
  CutCopyPasteHandler::command ( ICommandEvent& event )
{
  Boolean stopProcessingEvent = false;
  CodeWindow* codeWindow =
                (CodeWindow*)event.dispatchingWindow();
  switch ( event.commandId() )
  {
    case CMD_CUT:
      codeWindow->cut();
      stopProcessingEvent = true;
      break;
    case CMD_COPY:
      codeWindow->copy();
      stopProcessingEvent = true;
      break;
    case CMD_PASTE:
      codeWindow->paste();
      stopProcessingEvent = true;
      break;
    default:
      break;
  }
  return stopProcessingEvent;
}
