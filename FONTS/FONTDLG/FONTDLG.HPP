//************************************************************
// Views - Using the Font Dialog
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <icmdhdr.hpp>
#include <idrawcv.hpp>
#include <iframe.hpp>
#include <ifont.hpp>
#include <ifontdlg.hpp>
#include <ifonthdr.hpp>

class FontDrawingArea : public IDrawingCanvas
{
public:
  FontDrawingArea ( unsigned long windowId,
                    IWindow* parent,
                    IWindow* owner,
                    IFont& initialFont );
virtual
 ~FontDrawingArea ( );

FontDrawingArea
 &refreshList     ( IFont& newFont );

private:
  FontDrawingArea ( const FontDrawingArea& fda );
FontDrawingArea
 &operator=       ( const FontDrawingArea& fda );
};


class FontDialogExample : public IFrameWindow,
                          public ICommandHandler
{
public:
  FontDialogExample( char* title );

FontDialogExample&
  updateDemo       ( IFont& newFont );

protected:
virtual Boolean
  command(ICommandEvent& cmdEvent);

private:
IFont
  currentFont;

FontDrawingArea
  currentArea;

  FontDialogExample ( const FontDialogExample& fde );
FontDialogExample
 &operator=         ( const FontDialogExample& fde );
};

#if (IC_MAJOR_VERSION > 310)
class MyDlgHandler : public IFontDialogHandler
{
public:
  MyDlgHandler    ( FontDialogExample* hwnd ) : fhwnd(hwnd) {};

virtual Boolean
  modelessApply   ( IFontDialog* modelessDialog,
                    IFont*       appliedFont );
private:
FontDialogExample
 *fhwnd;
};
#endif
