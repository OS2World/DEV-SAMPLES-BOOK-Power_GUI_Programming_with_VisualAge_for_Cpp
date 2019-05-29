//*********************************************************
// Getting Started - Using Platform-Specific Code
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//*********************************************************
#include <ibase.hpp>    // For IC_WIN or IC_PM.

#ifdef IC_PM
#define INCL_WINDIALOGS
#include <os2.h>
#else
#include <windows.h>
#endif

#include <imsgbox.hpp>
#include <istring.hpp>
#include <iwindow.hpp>

void main ( )
{
  // Call a platform-specific API and display a
  // platform-specific message.
#ifdef IC_PM
  WinAlarm( IWindow::desktopWindow()->handle(), WA_NOTE );
  IString 
    msg( "This is an OS/2 application." );
#else
  Beep( 100, 100 );
  IString 
    msg( "This is a Windows application." );
#endif

  IMessageBox
    msgBox( 0 );
  msgBox
   .setTitle( "Which Platform?" )
   .show( msg,
          IMessageBox::informationIcon
           | IMessageBox::okButton
           | IMessageBox::moveable );
}
