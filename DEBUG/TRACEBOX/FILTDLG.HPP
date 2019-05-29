#ifndef _FILTDLG_
#define _FILTDLG_
//************************************************************
// Problem Determination  - Trace Queue Browser
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************

#include <iframe.hpp>
#include <ientryfd.hpp>
#include <icheckbx.hpp>
#include <ilistbox.hpp>
#include <imcelcv.hpp>
#include <ipushbut.hpp>
#include <iset.h>
#include <isetcv.hpp>
#include <istattxt.hpp>
#include <istring.hpp>

class FilterSet : public ISet<IString> {
public:
   FilterSet( ) : isExcludeList(true) {}
   Boolean isExcludeList;
};

class FilterCommandHandler;
class FilterEditHandler;
class FilterSelectHandler;

class FilterDialog  : public IFrameWindow {
public:
  FilterDialog( FilterSet& filterset, IWindow* owner );
  ~FilterDialog( );

private:
  FilterSet&         ffilterset;
  IMultiCellCanvas   fcanvas;
  ICheckBox          fisExclude;
  IStaticText        flabel;
  IEntryField        fentry;
  IListBox           flist;
  ISetCanvas         fbuttons1;
  IPushButton        fadd;
  IPushButton        fremove;
  ISetCanvas         fbuttons2;
  IPushButton        fok;
  IPushButton        fcancel;
  FilterCommandHandler* fcmdhdr;
  FilterSelectHandler*  fselhdr;
  FilterEditHandler*    fedithdr;

  friend class FilterCommandHandler;
  friend class FilterEditHandler;
  friend class FilterSelectHandler;

  FilterDialog                (const FilterDialog&);
  FilterDialog     operator=  (const FilterDialog&);
};

#endif
