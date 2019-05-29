#ifndef _VPORTCMD_
#define _VPORTCMD_
//*********************************************************
// Canvas - IViewPort that Scrolls a Bitmap
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//*********************************************************
#include <icmdhdr.hpp>

class IBitmapControl;
class IViewPort;

#pragma pack(4)

// This class processes commands to scroll a view port.
class ScrollViewCmdHandler : public ICommandHandler {
public:
  ScrollViewCmdHandler ( IViewPort *viewPort );
protected:
virtual Boolean
  command              ( ICommandEvent &event );
private:
IViewPort
 *clViewPort;
}; // class ScrollViewCmdHandler

// This class processes commands to size a view port.
class SizeBitmapCmdHandler : public ICommandHandler {
public:
  SizeBitmapCmdHandler ( IBitmapControl *bitmap,
                         IViewPort      *viewPort = 0 );
protected:
virtual Boolean
  command              ( ICommandEvent &event );
private:
IBitmapControl
 *clBitmap;
IViewPort
 *clViewPort;
}; // SizeBitmapCmdHandler

// This class processes commands to display a new bitmap.
class NewBitmapCmdHandler : public ICommandHandler {
public:
  NewBitmapCmdHandler ( IBitmapControl *bitmap );
protected:
virtual Boolean
  command             ( ICommandEvent &event );
private:
IBitmapControl
 *clBitmap;
}; // NewBitmapCmdHandler

#pragma pack()

#endif // _VPORTCMD_
