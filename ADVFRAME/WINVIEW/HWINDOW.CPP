//************************************************************
// Advanced Frame - Window Viewer Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <ibase.hpp>
#ifdef IC_PM
   #define INCL_WINATOM
   #define INCL_WINWINDOWMGR
   #include <os2.h>
#else
   #include <windows.h>
#endif

#include <iostream.h>
#include <fstream.h>
#include <ctype.h>
#include <irect.hpp>
#include <iwindow.hpp>
#include "hwindow.hpp"

HWindow::HWindow ( IHandle::Value handle )
  : IWindowHandle( handle )
  {
  }

IString  HWindow::asHexString ( ) const
{
   IString result(this->asUnsigned());
   result.d2x().rightJustify(8,'0');
   return result;
}

IString  HWindow::id         ( ) const
{
   unsigned short usId(0);
   if (this->isValid())
      {
#ifdef IC_PM
      usId = WinQueryWindowUShort( *this, QWS_ID );
#else
      if (GetWindowLong( *this, GWL_STYLE ) & WS_CHILD)
         usId = (unsigned short)GetWindowLong( *this, GWL_ID  ) ;
#endif
      }
   IString result(usId);
   result.d2x();
   return IString(usId) + IString(" 0x") + result;
}

IString  HWindow::text       ( ) const
{
   IString result;
   if (this->isValid())
      {
#ifdef IC_PM
      unsigned long bufLen = WinQueryWindowTextLength( *this ) + 1;
      char*         buf    = new char[bufLen];
      WinQueryWindowText( *this, bufLen, buf );
#else
      unsigned long bufLen = GetWindowTextLength( *this ) + 1;
      char*         buf    = new char[bufLen];
      GetWindowText( *this, buf, (int)bufLen );
#endif
      result = IString(buf);
      delete [] buf;
      }
   return result;
}

IString  HWindow::rectangle  ( ) const
{
   IRectangle rect;
   if (this->isValid())
      {
#ifdef IC_PM
      SWP  swp;
      WinQueryWindowPos( *this, &swp );
      rect = IRectangle(swp.x, swp.y,
                        swp.x + swp.cx, swp.y + swp.cy);
#else
      RECT   wrect;
      GetWindowRect( *this, &wrect );
      IWindowHandle  parentHwnd = GetParent( *this );

      // If the window is a popup, use the desktop as the
      // parent because:
      //    1) By default this window has no parent
      //    2) A query for the parent always returns
      //       the owner window.
      if ( GetWindowLong( *this, GWL_STYLE) & WS_POPUP )
        parentHwnd = IWindow::desktopWindow()->handle();
      MapWindowPoints( HWND_DESKTOP, parentHwnd,
                       (POINT*)&wrect, 2);
      rect = IRectangle(wrect);
#endif
      }
   return IString("(") +
          IString(rect.minX()) + IString(",") +
          IString(rect.minY()) + IString(",") +
          IString(rect.maxX()) + IString(",") +
          IString(rect.maxY()) + IString(") ") +
          IString(rect.width()) + IString("x") +
          IString(rect.height());
}

IString  HWindow::windowClass( ) const
{
   IString result;
   if (this->isValid())
      {
      // For simplicity, we only get the first 16 characters of
      // the class name string.
      char buffer[17];
#ifdef IC_PM
      unsigned int len =
         (unsigned int)WinQueryClassName( *this, 17, buffer);
      buffer[len] = '\0';
      char*  atom = 0;
      if (buffer[0] == '#')
         {
         IString strvalue(&buffer[1], len-1);
         unsigned short value =
            (unsigned short)strvalue.asUnsigned();
         atom = MAKEINTATOM(value) ;
         }
      if      (atom == WC_FRAME)
        result = "WC_FRAME";
      else if (atom == WC_COMBOBOX      )
        result = "WC_COMBOBOX";
      else if (atom == WC_BUTTON        )
        result = "WC_BUTTON";
      else if (atom == WC_MENU          )
        result = "WC_MENU";
      else if (atom == WC_STATIC        )
        result = "WC_STATIC";
      else if (atom == WC_ENTRYFIELD    )
        result = "WC_ENTRYFIELD";
      else if (atom == WC_LISTBOX       )
        result = "WC_LISTBOX";
      else if (atom == WC_SCROLLBAR     )
        result = "WC_SCROLLBAR";
      else if (atom == WC_TITLEBAR      )
        result = "WC_TITLEBAR";
      else if (atom == WC_MLE           )
        result = "WC_MLE";
      else if (atom == WC_SPINBUTTON    )
        result = "WC_SPINBUTTON";
      else if (atom == WC_CONTAINER     )
        result = "WC_CONTAINER";
      else if (atom == WC_SLIDER        )
        result = "WC_SLIDER";
      else if (atom == WC_VALUESET      )
        result = "WC_VALUESET";
      else if (atom == WC_NOTEBOOK      )
        result = "WC_NOTEBOOK";
      else if (atom == WC_CIRCULARSLIDER)
        result = "WC_CIRCULARSLIDER";
      else
        result = IString(buffer);
#else
      int len = GetClassName( *this, buffer, 17);
      if (len)
         result = IString(buffer);
#endif
      }
   return result;
}

IString  HWindow::style      ( ) const
{
   unsigned long ulStyle(0), ulExtStyle(0);
   if (this->isValid())
      {
#ifdef IC_PM
      ulStyle = WinQueryWindowULong(*this, QWL_STYLE);
#else
      ulStyle = (unsigned long)GetWindowLong( *this, GWL_STYLE );
      ulExtStyle = (unsigned long)GetWindowLong( *this,
                                                 GWL_EXSTYLE );
#endif
      }
   IString result = IString(ulStyle);
   result.d2x().rightJustify(8,'0');
   if (ulExtStyle != 0)
      {
      IString ext( ulExtStyle );
      ext.d2x().rightJustify(8,'0');
      result += IString(",") + ext;
      }
   return result;
}

IBase::Boolean HWindow::isValid    ( ) const
{
#ifdef IC_PM
   // This is faster than getting thread and using WinIsWindow.
   return WinQueryAnchorBlock( *this ) ? true : false;
#else
   return IsWindow( *this ) ? true : false;
#endif
}

HWindow::ChildCursor::ChildCursor ( const HWindow& parent )
  : hwnd       ( 0 ),
    hwndParent ( (IHandle::Value)parent )
{
}

HWindow::ChildCursor::~ChildCursor ( )
{
}

Boolean HWindow::ChildCursor::setToFirst ( )
{
#ifdef IC_PM
  this->hwnd = WinQueryWindow( this->hwndParent, QW_TOP );
#else
  this->hwnd = GetWindow( this->hwndParent, GW_CHILD);
#endif
  return this->isValid();
}

Boolean HWindow::ChildCursor::setToNext ( )
{
  if ( !this->hwnd )
     return setToFirst();
  else
     {
#ifdef IC_PM
     this->hwnd = WinQueryWindow( this->hwnd, QW_NEXT );
#else
     this->hwnd = GetWindow( this->hwnd, GW_HWNDNEXT ) ;
#endif
     }
  return this->isValid();
}

Boolean HWindow::ChildCursor::isValid ( ) const
{
  return this->hwnd != 0;
}

void HWindow::ChildCursor::invalidate ( )
{
  this->hwnd = 0;
}

HWindow HWindow::ChildCursor::hWindow ( ) const
{
  return HWindow(this->hwnd);
}


