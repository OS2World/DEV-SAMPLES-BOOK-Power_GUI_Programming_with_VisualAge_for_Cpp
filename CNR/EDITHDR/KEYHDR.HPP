#ifndef _KEYHDR_
#define _KEYHDR_
//************************************************************
// Container - Keyboard Handler for MLE
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <ikeyhdr.hpp>
#include <istring.hpp>

class KeyboardHandler : public IKeyboardHandler {
protected:
virtual Boolean
  characterKeyPress ( IKeyboardEvent& event )
  {
    // Reject any 'A' characters.
    IString strChar = event.mixedCharacter();
    if (strChar.isSBCS()  &&  strChar == 'A')
    {
       event.setResult(true);
       return true;
    }
    return false;
  }
};

#endif // _KEYHDR_

