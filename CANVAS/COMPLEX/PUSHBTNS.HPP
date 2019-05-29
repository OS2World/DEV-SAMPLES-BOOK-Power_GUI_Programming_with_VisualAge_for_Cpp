#ifndef _PUSHBTNS_
#define _PUSHBTNS_
//*********************************************************
// Canvas - Complex Canvas Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//*********************************************************
#include <ipushbut.hpp>
#include <isetcv.hpp>
#include <icconst.h>

#ifdef IC_PM
  // Define special window identifiers not originally
  // included in VisualAge for C++ for OS/2, V3.0.
  #ifndef IC_ID_OK
    #define IC_ID_OK     1
  #endif
  #ifndef IC_ID_CLOSE
    #define IC_ID_CLOSE  0x8004
  #endif
#endif

class MyStandardPushButtons : public ISetCanvas {
public:
  MyStandardPushButtons ( unsigned long id,
                          IWindow*      parentAndOwner )
    : ISetCanvas( id, parentAndOwner, parentAndOwner ),
      ok( IC_ID_OK, this, this ),
      cancel( IC_ID_CLOSE, this, this ),
      help( IC_ID_HELP, this, this )
  {
    (*this)
     .setMargin( ISize() )
     .setPackType( ISetCanvas::expanded );
                   // Make all the buttons the same size.
    ok
     .enableDefault()
     .setText( "OK" )
     .enableTabStop()
     .enableGroup();
    cancel
     .enableSystemCommand()  // For the Close system command.
     .setText( "Cancel" );
    help
     .enableHelp()
     .disableMouseClickFocus()
     .setText( "Help" );
  }
private:
  MyStandardPushButtons ( const MyStandardPushButtons& );
MyStandardPushButtons
 &operator=             ( const MyStandardPushButtons& );
IPushButton
  ok,
  cancel,
  help;
}; // MyStandardPushButtons

#endif // _PUSHBTNS_
