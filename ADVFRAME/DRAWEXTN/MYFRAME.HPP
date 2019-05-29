#ifndef _MYFRAME_
#define _MYFRAME_
//************************************************************
// Advanced Frame - Frame Extension Drawing Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <icmdhdr.hpp>
#include <icolor.hpp>
#include <ientryfd.hpp>
#include <iframe.hpp>
#include <iframext.hpp>
#include <ilistbox.hpp>
#include <ipushbut.hpp>
#include <istattxt.hpp>

class MyFrame;
class MyExtension;

class ColorList : public IListBox {
public:
  ColorList ( IWindow *owner );
IColor
  selectedColor ( ) const;
private:
ColorList (const ColorList&);
ColorList& operator= (const ColorList&);
};


class MyHandler : public ICommandHandler {
public:
  MyHandler ( MyFrame &frame );
protected:
virtual Boolean
  command ( ICommandEvent &event );
private:
MyFrame
 &frame;
MyHandler(const MyHandler&);
MyHandler& operator=(const MyHandler&);
};

class MyFrame : public IFrameWindow {
public:
  MyFrame ( );

virtual IFrameWindow
 &update ( );

virtual MyFrame
 &forceUpdate ( );

private:
MyFrame
 &addMyExtension( MyExtension *pExt );

ColorList
  colorList;
IEntryField
  extSize;
IStaticText
  instructions;
IPushButton
  drawButton;
MyHandler
  handler;
MyFrame ( const MyFrame& );
MyFrame& operator= ( const MyFrame& );
};

#endif // _MYFRAME_
