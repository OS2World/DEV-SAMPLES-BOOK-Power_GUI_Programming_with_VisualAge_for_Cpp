#ifndef _HELPOTHR_
#define _HELPOTHR_
//*********************************************************
// Using Help - Help for Special Cases
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc.
// All Rights Reserved.
//*********************************************************
#include <icmdhdr.hpp>
#include <icnrobj.hpp>
#include <idmprov.hpp>
#include <ientryfd.hpp>
#include <iframe.hpp>
#include <ihelphdr.hpp>
#include <imcelcv.hpp>
#include <inotebk.hpp>
#include <ipagehdr.hpp>
#include <ititle.hpp>
#include <istattxt.hpp>
#include "helpothr.h"

// Align classes on four-byte boundaries.
#pragma pack(4)

class CnrObject : public IContainerObject {
public:
virtual void
  handleOpen ( IContainerControl* container );
virtual unsigned long
  helpId     ( ) const;
virtual IContainerObject
 *objectCopy ( );
}; // CnrObject

class CnrDragHelpProvider : public IDMItemProviderFor< IDMCnrItem > {
public:
virtual Boolean
  provideHelpFor ( IDMTargetHelpEvent& event );
}; // CnrDragHelpProvider

class NotebookTabHelpHdr : public IPageHandler {
protected:
virtual Boolean
  help ( IPageHelpEvent& event );
}; // NotebookTabHelpHdr

class DynamicPageHelpHdr : public IHelpHandler {
protected:
virtual Boolean
#ifdef IC_PM
  handleError     ( IHelpErrorEvent& event ),
#endif
  subitemNotFound ( IHelpSubitemNotFoundEvent& event );
}; // DynamicPageHelpHdr

class ObjectView : public IFrameWindow {
public:
  ObjectView ( unsigned long id,
               IWindow* parent = 0,
               IWindow* owner = 0 );
private:
  ObjectView ( const ObjectView& );
ObjectView
 &operator=  ( const ObjectView& );

INotebook
  notebook;
NotebookTabHelpHdr
  tabHelpHdr;
DynamicPageHelpHdr
  dynamicPageHelpHdr;
IMultiCellCanvas
  page1;
IStaticText
  heading1,
  prompt1,
  prompt2,
  prompt3;
IEntryField
  entry1,
  entry2,
  entry3;
IMultiCellCanvas
  page2;
IStaticText
  headingA,
  promptA,
  promptB,
  promptC;
IEntryField
  entryA,
  entryB,
  entryC;
IFrameWindow
  page3;
IMultiCellCanvas
  page3a;
IStaticText
  headingX,
  promptX,
  promptY;
IEntryField
  entryX,
  entryY;
IFrameWindow
  dialog;
}; // ObjectView

class ShowFileDialogCmdHdr : public ICommandHandler {
protected:
virtual Boolean
  command ( ICommandEvent& event );
}; // ShowFileDialogCmdHdr

#pragma pack()

#endif // _HELPOTHR_
