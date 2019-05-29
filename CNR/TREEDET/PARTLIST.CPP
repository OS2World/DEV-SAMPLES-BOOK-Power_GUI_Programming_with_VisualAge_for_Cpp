//************************************************************
// Container - Combined Tree and Details View
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
extern "C" {
   #define INCL_WINWINDOWMGR
   #define INCL_WINSTDCNR
   #define INCL_WINSYS
   #include <os2.h>
}

#include <iframe.hpp>
#include <icnrctl.hpp>
#include <icnrcol.hpp>
#include <isplitcv.hpp>
#include <imcelcv.hpp>
#include <istattxt.hpp>
#include <iscroll.hpp>
#include <itrace.hpp>
#include <isizehdr.hpp>
#include "partlist.hpp"
#include "partlist.h"
#include "partobj.hpp"
#include "treedetc.hpp"
#include "treedeth.hpp"
#include <malloc.h>

// A resize handler to hide the tree view scroll bar
class ScrollBarResizeHandler : public IResizeHandler
{
protected:
virtual Boolean
  windowResize ( IResizeEvent& event )
  {
     if (event.newSize() != ISize(0,0))
        event.window()->sizeTo(ISize(0,0));
     return true;
  }
};

PartsList :: ~PartsList ( )
{
  IFUNCTRACE_DEVELOP()
  // Note we rely on Auto Delete to clean up the
  // objects for windows contained herein.
  delete treeHandler;
  delete colorHandler;
}

PartsList :: PartsList ( )
                : IFrameWindow(EX_PARTLIST_FRAME ),
                  colorChanged(false)
{
  IFUNCTRACE_DEVELOP()
  // Create a frame window with a split canvas client
  //            left  side = Multi-Cell Canvas
  //            right side = Multi-Cell Canvas
  // There is also a static text field on top
  // of the Tree view scroll Bar
  //
  //  --------------------------------------------
  //  |          |  ||   Empty Row for Pad       |
  //  |          |S ||---------------------------|
  //  |          |t ||                           |
  //  |          |a ||                           |
  //  |          |t ||                           |
  //  |  Tree    |i ||     Details               |
  //  |  Cnr     |c ||       Cnr                 |
  //  |          |  ||                           |
  //  |          |T ||                           |
  //  |          |e ||                           |
  //  |          |x ||                           |
  //  |          |t ||                           |
  //  --------------------------------------------
  //

  // Create a split canvas as a client
  canvas = new ISplitCanvas (EX_PARTLIST_CANVAS,
                              this, this);
  this->setClient(canvas);

  // Create a MultiCell canvas for both the left window (to
  // contain the tree) and the right (to contain the
  // details view)
  leftMCell  = new IMultiCellCanvas(EX_PARTLIST_LEFTCANVAS,
                              canvas, this);
  rightMCell = new IMultiCellCanvas(EX_PARTLIST_RIGHTCANVAS,
                              canvas, this);

  // Create the tree and a Static Text field for the
  // left canvas.  The static text is used to overlay
  // the tree view scroll bar (the container and
  // the static text field share a column)
  treeCnr        = new DetailsTreeContainer(EX_PARTLIST_TREE,
                                         leftMCell, this);


  // Add the cells to the left canvas
  (*leftMCell)
    .addToCell(treeCnr, 1, 1, 2, 2)      
    .setColumnWidth(2, IScrollBar::systemScrollBarWidth())  
    .setColumnWidth(1, 50, true)
    .setRowHeight(1, 10, true)   
    .setRowHeight(2, IScrollBar::systemScrollBarWidth());


  // Create the details container and put it into row 2
  // with some pad for alignment,
  detailsCnr  = new IContainerControl(EX_PARTLIST_DETAILS,
                                      rightMCell, this);
  (*rightMCell)
    .addToCell(detailsCnr, 1, 2)
    .setRowHeight(1,6)
    .setRowHeight(2,30, true)
    .setColumnWidth(1, 10, true);

  // Wrapper the Tree view scroll bar, turn off updating for it,
  // and add a handler to keep its size at ISize(0,0).
  treeScroll = new IScrollBar(CID_VSCROLL, treeCnr);
  treeScroll->disableUpdate();
  treeScroll->sizeTo(ISize(0,0));
  ScrollBarResizeHandler* resizeHandler = new ScrollBarResizeHandler();
  resizeHandler->handleEventsFor(treeScroll);


  // Notify the DetailsTreeContainer of it's details view
  treeCnr->setDetailsContainer(detailsCnr);

  // Set the appropriate views
  treeCnr->showTreeTextView();
  detailsCnr->showDetailsView();


  // We show a details title and
  // and set the line spacing. 
  treeCnr->showTitle();
  treeCnr->setTitle("Object");         // RDL
  treeCnr->setLineSpacing(3);          // RDL
  detailsCnr->setLineSpacing(3);       // RDL

  // Create the handlers for syncing changes
  // Note: handleEventsFor is done in the constructor.
  // 1) Font
  treeHandler = new DetailsTreeHandler(treeCnr);

  // 2) Color
  colorHandler = new ColorChangeHandler(this);


#ifdef IC_DEVELOP
// For testing, add the iconViewText column
  IContainerColumn* pcol;
  pcol = new IContainerColumn(IContainerColumn::isIconViewText);
  pcol->setHeadingText( "Test Column");
  pcol->showSeparators(IContainerColumn::horizontalSeparator);
  pcol->justifyData(IContainerColumn::bottom, IContainerColumn::left);
  detailsCnr->addColumn(pcol);
  detailsCnr->setDetailsViewSplit(pcol);
  detailsCnr->showSplitBar();
#endif
  // Setup the headings for the columns.
  ExecutablePart::setHeadingText(
       IApplication::current().userResourceLibrary().loadString(EX_COLUMN_TRACEABLE),
       ExecutablePart::kTraceableColumn);
  ExecutablePart::setHeadingText(
       IApplication::current().userResourceLibrary().loadString(EX_COLUMN_ENABLED),
       ExecutablePart::kEnabledPartColumn);      
  ExecutablePart::setHeadingText(
       IApplication::current().userResourceLibrary().loadString(EX_COLUMN_GENTRACE),
       ExecutablePart::kGeneratesTraceColumn);   
  ExecutablePart::setHeadingText(
       IApplication::current().userResourceLibrary().loadString(EX_COLUMN_TRIGGER),
       ExecutablePart::kContainsTriggerColumn);  

  // Create the columns.
  ExecutablePart::createAllColumnsFor(*detailsCnr); 


  // add some objects
  loadObjects ();

  // Auto Delete our objects when the PM Window gets destroyed
  canvas->setAutoDeleteObject();
  leftMCell->setAutoDeleteObject();
  rightMCell->setAutoDeleteObject();
  treeScroll->setAutoDeleteObject();
  treeCnr->setAutoDeleteObject();
  treeCnr->setDeleteObjectsOnClose();
  detailsCnr->setAutoDeleteObject();
  detailsCnr->setDeleteColumnsOnClose();
  detailsCnr->setDeleteObjectsOnClose();

detailsCnr->refresh();

}

PartsList& PartsList :: open ( )
{
  if ( isMinimized() )
    restore();
  setFocus();
  show();
  return *this;
}



// Load Some Executable Parts into the container
PartsList& PartsList :: loadObjects ( )
{
  ExecutablePart *partExe, *partObj, *partFunc;

  partExe = new ExecutablePart("CPPOOU3.DLL");
  treeContainer().addObject(partExe);
    partObj = new ExecutablePart("IWINDOW2.OBJ");
    treeContainer().addObject(partObj, partExe);
      partFunc = new ExecutablePart("IWindow::show");
      treeContainer().addObject(partFunc, partObj);
      partFunc = new ExecutablePart("IWindow::hide");
      treeContainer().addObject(partFunc, partObj);
      partFunc = new ExecutablePart("IWindow::enableUpdate");
      treeContainer().addObject(partFunc, partObj);
    partObj = new ExecutablePart("ICNROBJ0.OBJ");
    treeContainer().addObject(partObj, partExe);
      partFunc = new ExecutablePart("IContainerObject::enableDataUpdate");
      treeContainer().addObject(partFunc, partObj);
      partFunc = new ExecutablePart("IContainerObject::setIcon");
      treeContainer().addObject(partFunc, partObj);
      partFunc = new ExecutablePart("IContainerObject::setIconText");
      treeContainer().addObject(partFunc, partObj);
  partExe = new ExecutablePart("CPPOM30.DLL");
  treeContainer().addObject(partExe);
    partObj = new ExecutablePart("CTORDTOR.OBJ");
    treeContainer().addObject(partObj, partExe);
      partFunc = new ExecutablePart("__ctdtused");
      treeContainer().addObject(partFunc, partObj);
      partFunc = new ExecutablePart("__ctordtorTerm");
      treeContainer().addObject(partFunc, partObj);
  partExe = new ExecutablePart("CPPOOB3.DLL");
  treeContainer().addObject(partExe);
    partObj = new ExecutablePart("IEXCBASE.OBJ");
    treeContainer().addObject(partObj, partExe);
      partFunc = new ExecutablePart("IOutOfWindowResource::~IOutOfWindowResource");
      treeContainer().addObject(partFunc, partObj);
      partFunc = new ExecutablePart("IException::terminate");
      treeContainer().addObject(partFunc, partObj);
    partObj = new ExecutablePart("IMSGTEXT.OBJ");
    treeContainer().addObject(partObj, partExe);
      partFunc = new ExecutablePart("IMessageText::setDefaultText");
      treeContainer().addObject(partFunc, partObj);
 
  return *this;
}

IContainerControl& PartsList :: otherContainer (
                  const IContainerControl& opposite)
{
  if (&opposite == treeCnr)
     return *detailsCnr;
  else
     return *treeCnr;
}


ColorChangeHandler :: ColorChangeHandler ( PartsList* partsList)
{
  IFUNCTRACE_DEVELOP()
  this->partsList = partsList;
  handleEventsFor(&partsList->leftMultiCell());
  handleEventsFor(&partsList->rightMultiCell());
//  handleEventsFor(&partsList->treeScrollHide());
  handleEventsFor(&partsList->treeContainer());
  handleEventsFor(&partsList->detailsContainer());
}



Boolean ColorChangeHandler :: dispatchHandlerEvent ( IEvent& evt)
{
   if(evt.eventId() == WM_PRESPARAMCHANGED)
   {
      if(evt.parameter1() == PP_BACKGROUNDCOLOR )
         return backgroundColorChanged(evt);
   }


  return false;
}

Boolean ColorChangeHandler :: backgroundColorChanged(IEvent& evt)
{
  // We need to keep track of the top level entry to this
  // function so that we avoid a ping-pong affect that could 
  // occur when the notification is received more then once. 
  Boolean fNested = partsList->colorChangeStarted();
  partsList->setColorChangeStarted(true);


  if(!fNested) {
       IWindow* receiver=evt.window();
       // The following will change with new color scheme
       IColor color(IColor::white);

       // Determine the color of the changed window.
       if (receiver==&partsList->leftMultiCell() 
           || receiver == &partsList->rightMultiCell())
          color = ((IMultiCellCanvas*)receiver)->color();
       else if (receiver==&partsList->treeContainer()
           || receiver==&partsList->detailsContainer())
          color = ((IContainerControl*)receiver)->color(IContainerControl::background);
       else if (receiver==&partsList->treeScrollHide())
          color = partsList->treeScrollHide().color(IStaticText::background);

       // Apply the new color to the other windows in the SplitCanvas
          partsList->rightMultiCell().setColor(color);
       if(receiver!=&partsList->rightMultiCell())
          partsList->rightMultiCell().setColor(color);
       if(receiver!=&partsList->leftMultiCell())
          partsList->leftMultiCell().setColor(color);
       if(receiver!=&partsList->splitCanvas())
          partsList->splitCanvas().setColor(ISplitCanvas::splitBarMiddle, color);
       if(receiver!=&partsList->treeContainer())
          partsList->treeContainer().setColor(IContainerControl::background, color);
       if(receiver!=&partsList->detailsContainer())
          partsList->detailsContainer().setColor(IContainerControl::background, color);
       if(receiver!=&partsList->treeScrollHide())
          partsList->treeScrollHide().setColor(IStaticText::background, color);
       partsList->setColorChangeStarted(false);
  }

  return false;
}

