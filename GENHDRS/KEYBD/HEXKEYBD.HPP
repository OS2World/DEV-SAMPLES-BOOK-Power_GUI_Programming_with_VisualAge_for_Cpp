#ifndef _HEXKEYBD_
#define _HEXKEYBD_
//*********************************************************
// Reusable Handlers - Keyboard Handler
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//*********************************************************
#include <ibase.hpp>         // For IC_PM/IC_WIN.
#ifdef IC_PM
  #define INCL_WINDIALOGS    // For WinAlarm.
  #define INCL_WININPUT      // For KC_CHAR, VK_DELETE.
  #include <os2.h>
#else
  #include <windows.h>
#endif

#include <ikeyhdr.hpp>
#include <istring.hpp>
#include <iwindow.hpp>

// This keyboard handler restricts character input to
// hexadecimal digits (0-9, a-f, A-F).
class HexKeyboardHandler : public IKeyboardHandler {
protected:
virtual Boolean
  characterKeyPress ( IKeyboardEvent& event )
  {
    Boolean badKey = true;
    Boolean dontPassOn = true;

    IString strChar = event.mixedCharacter();
    if ( strChar.isSBCS() )
    {                        // The character is single-byte.
       if ( strChar.isHexDigits() )
       {                     // '0'-'9', 'A'-'F', 'a'-'f'.
          badKey = false;    // Valid hexadecimal digit.
          dontPassOn = false;  // Pass the event to the window.
       }
       else if ( strChar == " " )
       {                     // Space bar is pressed.
          badKey = false;    // Replace it with the Delete key.
#ifdef IC_PM
          IEventParameter1
            param1( event.parameter1().number1() & ~KC_CHAR,
                    event.parameter1().char3(), 0 );
          (*event.window())
           .sendEvent( IWindow::character,
                       param1,
                       IEventParameter2( 0, VK_DELETE ) );
               // Discard scan code and character data.
#else
          (*event.window())
           .sendEvent( IWindow::character,
                       IEventParameter1( 0, 1 ),
                       IEventParameter2( VK_DELETE ) );
               // Discard scan code and character data.
#endif
       }
       // Throw away any other character key.
    }                        // End single-byte input.

    if ( badKey )
    {
#ifdef IC_PM
       WinAlarm( IWindow::desktopWindow()->handle(),
                 WA_WARNING );
#else
       Beep( 100, 100 );
#endif
    }
    return dontPassOn;
  }
}; // HexKeyboardHandler
#endif // _HEXKEYBD_
