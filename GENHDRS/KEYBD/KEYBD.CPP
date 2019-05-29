//*********************************************************
// Reusable Handlers - Keyboard Handler
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//*********************************************************
#include <iapp.hpp>
#include <icombobx.hpp>
#include <ientryfd.hpp>
#include <iframe.hpp>
#include <imle.hpp>
#include <ipushbut.hpp>

#include "hexkeybd.hpp"
#include "uckeybd.hpp"
#include "keybd.h"

void main ( )
{
  IFrameWindow
    frame( ID_KEYBD_DIALOG );

  // Provide a wrapper for the relevant dialog controls.
  IEntryField
    anyEntry( ID_ANY_ENTRY, &frame ),
    upperEntry( ID_UPPERCASE_ENTRY, &frame ),
    hexEntry( ID_HEX_ENTRY, &frame ),
    upperHexEntry( ID_UPPERCASE_HEX_ENTRY, &frame );
  IComboBox
    upperHexCombo( ID_UPPERCASE_HEX_COMBO, &frame );
  IEntryField
    comboEntry( ID_COMBOBOX_EF, &upperHexCombo );
                   // ID_COMBOBOX_EF is platform specific.
  IMultiLineEdit
    upperHexMLE( ID_UPPERCASE_HEX_MLE, &frame );

#ifndef IC_PM
  IPushButton
    ok( ID_CLOSE, &frame );
  ok
   .enableSystemCommand();  // For the Close system command.
#endif

  // Construct and attach the keyboard handlers.
  UppercaseKeyboardHandler
    upperKeyboardHandler;
  upperKeyboardHandler
   .handleEventsFor( &upperEntry )
   .handleEventsFor( &upperHexEntry )
   .handleEventsFor( &comboEntry )
   .handleEventsFor( &upperHexMLE );

  HexKeyboardHandler
    hexKeyboardHandler;
  hexKeyboardHandler
   .handleEventsFor( &hexEntry )
   .handleEventsFor( &upperHexEntry )
   .handleEventsFor( &comboEntry )
   .handleEventsFor( &upperHexMLE );

  // Show the window now.
  anyEntry
   .setFocus();
  frame
   .show();

  IApplication::current().run();
}
