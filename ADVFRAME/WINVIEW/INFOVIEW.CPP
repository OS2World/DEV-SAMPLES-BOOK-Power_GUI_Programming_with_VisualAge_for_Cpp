//************************************************************
// Advanced Frame - Profile Viewer Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <imle.hpp>
#include <ifont.hpp>
#include "infoview.hpp"
#include "hwinobj.hpp"
#include "winview.h"


InfoView::InfoView ( HWindowObject& object )
  : HWindowObjectView( clientWindow(),
                       object,
                       "Information View" )
  {
  populate();
  }

InfoView &InfoView::populate ( )
  {
  IMultiLineEdit
   *mle = (IMultiLineEdit*)( client() );
  (*mle)
    .addLineAsLast( "Handle:   " +
                    object()->hWindow().asHexString() )
    .addLineAsLast( "Id:       " +
                    object()->hWindow().id() )
    .addLineAsLast( "Style:    " +
                    object()->hWindow().style() )
    .addLineAsLast( "Rectangle:" +
                    object()->hWindow().rectangle() )
    .addLineAsLast( "Class:    " +
                    object()->hWindow().windowClass() )
    .addLineAsLast( "Text:     " +
                    object()->hWindow().text() );
  return *this;
  }

IMultiLineEdit* InfoView::clientWindow ( )
  {
  IMultiLineEdit
   *p = new IMultiLineEdit( IC_FRAME_CLIENT_ID,
                            IWindow::objectWindow(),
                            IWindow::objectWindow(),
                            IRectangle(),
                            IMultiLineEdit::classDefaultStyle |
                            IMultiLineEdit::readOnly );
#ifdef IC_PM
  IFont
    font( "System Monospaced", 12 );
#else
  IFont
    font( "Fixedsys",          12 );
#endif
  (*p)
    .setFont( font )
    .setAutoDeleteObject( true );
  return p;
  }
