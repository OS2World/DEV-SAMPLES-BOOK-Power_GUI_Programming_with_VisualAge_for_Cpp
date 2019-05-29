#ifndef _ACCELUPD__
  #define _ACCELUPD__
//*********************************************************
// Menus - Dynamic Accelerator Keys
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//*********************************************************
#include <iselhdr.hpp>

class IWindow;

#define ID_RED     10
#define ID_GREEN   11
#define ID_CYAN    12
#define ID_PINK    13

#define CMD_RED    100
#define CMD_GREEN  101
#define CMD_CYAN   102
#define CMD_PINK   103

// This selection handler adds and removes accelerator
// keys.
class AccelSelectHandler : public ISelectHandler {
public:
  AccelSelectHandler ( IWindow& acceleratorWindow )
    : fAccelWindow( acceleratorWindow )
  { }
protected:
virtual Boolean
  selected           ( IControlEvent& event );
private:
  AccelSelectHandler ( const AccelSelectHandler& );
AccelSelectHandler
 &operator=          ( const AccelSelectHandler& );
IWindow
 &fAccelWindow;
}; // AccelSelectHandler

#endif
