#ifndef _UCKEYBD_
#define _UCKEYBD_
//*********************************************************
// Reusable Handlers - Keyboard Handler
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//*********************************************************
#include <ikeyhdr.hpp>
#include <istring.hpp>
#include <iwindow.hpp>

// This keyboard handler example converts lowercase characters
// to uppercase as a user types.
class UppercaseKeyboardHandler : public IKeyboardHandler {
protected:
virtual Boolean
  characterKeyPress ( IKeyboardEvent& event )
  {
    Boolean dontPassOn = false;
    IString strChar = event.mixedCharacter();
    if ( strChar.isSBCS()  &&  strChar.isLowerCase() )
    {                // Single-byte 'a'-'z' is pressed.
       // Convert the character to uppercase by generating
       // another keyboard event with its uppercase character.
#ifdef IC_PM
       IEventParameter2 param2( strChar.upperCase()[0],
                                event.parameter2().number2() );
                     // Only change the character to uppercase.
       event.window()->sendEvent( IWindow::character,
                                  event.parameter1(),
                                  param2 );
#else
       IEventParameter1 param1( strChar.upperCase()[0] );
                     // Only change the character to uppercase.
       event.window()->sendEvent( IWindow::character,
                                  param1,
                                  event.parameter2() );
#endif
       dontPassOn = true;    // Don't pass on the original event.
    }
    return dontPassOn;
  }
}; // UppercaseKeyboardHandler
#endif // _UCKEYBD_
