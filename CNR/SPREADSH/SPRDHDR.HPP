#ifndef _SPRDHDR_
#define _SPRDHDR_
//************************************************************
// Container Control - Spreadsheet Behavior
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <icmdhdr.hpp>
#include <icnrctl.hpp>
#include <iaccel.hpp>
#include "spreadsh.h"

class CnrSpreadSheetHandler : public ICommandHandler {
public:
 CnrSpreadSheetHandler ( IContainerControl& container);

IContainerControl
 &container        ( );

protected:
virtual Boolean 
  command(ICommandEvent& commandEvent);

private:
IContainerControl
 &cnrctl;
IAccelerator
  accel;
CnrSpreadSheetHandler(const CnrSpreadSheetHandler&);
CnrSpreadSheetHandler& operator=(const CnrSpreadSheetHandler&);
};

#endif // SPRDHDR_
