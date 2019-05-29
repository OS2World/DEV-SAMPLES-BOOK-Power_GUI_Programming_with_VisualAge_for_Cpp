//************************************************************
// Problem Determination - Simple Catch Dialog
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <iframe.hpp>
#include <istattxt.hpp>
#include <istring.hpp>
#include <iexcbase.hpp>
#include <imsgbox.hpp>

void main( )
{
try {
    IFrameWindow frame(100);
    IStaticText txt(101, 0, 0); // Cause an assertion exception
    frame.setFocus().show();
    IApplication::current().run();
  }
  catch(IException& exc) {
    IMessageBox abortIt(IWindow::desktopWindow());
    abortIt.setTitle("Exception Caught");
    abortIt.show(exc.text(), IMessageBox::okButton);
  }
}

