#ifndef _PACKCV_
#define _PACKCV_
//*********************************************************
// Canvas - ISetCanvas Pack Options
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//*********************************************************
#include <icmdhdr.hpp>
#include <iframe.hpp>
#include <iiconctl.hpp>
#include <ioutlbox.hpp>
#include <ipoint.hpp>
#include <irect.hpp>
#include <isetcv.hpp>
#include <itbar.hpp>
#include <itbarbut.hpp>

#include "packcv.h"

class PackCanvas : public ISetCanvas {
public:
  PackCanvas ( unsigned long id,
               IWindow* parentAndOwner,
               ISetCanvas::PackType pack );
private:
  PackCanvas ( const PackCanvas& );
PackCanvas
 &operator=  ( const PackCanvas& );
IOutlineBox
  first,
  second,
  third,
  fourth,
  fifth,
  sixth;
}; // PackCanvas

class PackAlignTest : public IFrameWindow {
public:
  PackAlignTest      ( );
PackAlignTest
 &alignGrandChildren ( ISetCanvas::Alignment align );
private:
  PackAlignTest ( const PackAlignTest& );
PackAlignTest
 &operator=     ( const PackAlignTest& );

class CmdHandler : public ICommandHandler {
  public:
    CmdHandler ( PackAlignTest* window )
      : clWindow( window )
    { }
  protected:
  virtual Boolean
    command    ( ICommandEvent& event );
  private:
  PackAlignTest
   *clWindow;
  }; // PackAlignTest::CmdHandler

ISetCanvas
  packClient;
PackCanvas
  tight,
  even,
  expanded;
CmdHandler
  cmdHdr;
IToolBar
  toolBar;
IToolBarButton
  topLeft,
  topCenter,
  topRight,
  centerLeft,
  centerCenter,
  centerRight,
  bottomLeft,
  bottomCenter,
  bottomRight;
}; // PackAlignTest

#endif // _PACKCV_
