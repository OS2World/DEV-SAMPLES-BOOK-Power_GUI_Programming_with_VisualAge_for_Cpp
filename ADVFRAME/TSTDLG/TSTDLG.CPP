//************************************************************
// Advanced Frame - Dialog Window Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <ibase.hpp>
#ifdef IC_PM
  #define INCL_WIN
  #include <os2.h>
#else
  #include <windows.h>
#endif

#include <istattxt.hpp>
#include <ithread.hpp>

#include "dialog.hpp"
#include "dlghndlr.hpp"

class MyDialogHandler : public DialogHandler {
public:
virtual Boolean
  initialize( DialogInitEvent& initEvent )
    {
    IStaticText
      text( IWindow::handleWithParent(1,  initEvent.handle() ) );
    text.setText( (char*)( initEvent.createParameters() ) );
    return false;
    }
};

#ifdef IC_PM
static void * _System myDlgProc( unsigned long  hwnd,
                                 unsigned long  eventId,
                                 void*          parm1,
                                 void*          parm2 )
  {
  if ( eventId == WM_INITDLG )
    {
    IStaticText
      text( IWindow::handleWithParent(1,  hwnd ) );
    text.setText( (char*)parm2 );
    }
  return WinDefDlgProc( hwnd, eventId, parm1, parm2 );
  }

#else
static void* CALLBACK  myDlgProc( void*          hwnd,
                                  unsigned long  eventId,
                                  void*          parm1,
                                  void*          parm2 )
  {
  if ( eventId == WM_INITDIALOG )
    {
    IStaticText
      text( IWindow::handleWithParent(1,  hwnd ) );
    text.setText( (char*)parm2 );
    }
  return 0;
  }


#endif

void main()
  {
  MyDialogHandler
    myHandler;
  DialogWindow
   dlg1( IC_DEFAULT_FRAME_ID,
         IWindow::desktopWindow(),
         myHandler,
         "myHandler" );
  DialogWindow
    dlg2( IC_DEFAULT_FRAME_ID,
          IWindow::desktopWindow(),
          myDlgProc,
          "myDlgProc" );
  dlg1.show();
  dlg2.show().setFocus();
  IApplication::current().run();
  }

