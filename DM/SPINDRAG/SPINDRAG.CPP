//************************************************************
// Direct Manipulation - Spin Button Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <iframe.hpp>
#include <imle.hpp>
#include <ispintxt.hpp>
#include <ientryfd.hpp>
#include <idmhndlr.hpp>
#include <idmprov.hpp>

#include "spinitem.hpp"

void main()
  {
#ifdef IC_PM
  IDM::debugSupport = true;
#endif
#ifdef IC_WIN
  IDMOperation::setDebugSupport();
#endif
  IFrameWindow
    frame( "Direct Manipulation Spin Button Example" );
  IMultiLineEdit
    edit( 0, &frame, &frame );
  ITextSpinButton
    spin( 123, &frame, &frame );
  IEntryField
    spinEF( 123, &spin );

  IDMItemProviderFor< SpinButtonItem >
    provider;

  IDMHandler::enableDragDropFor( &edit );
  spinEF.setItemProvider( &provider );
  IDMHandler::enableDragDropFor( &spinEF );

  frame
    .setClient( &edit )
    .addExtension( &spin, IFrameWindow::belowClient, 26 );
  edit
    .setFocus();
  frame
    .showModally();
  }
