//************************************************************
// Notebook Control - Smart Guide Notebook
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc.
// All Rights Reserved.
//************************************************************
#include <iframe.hpp>
#include <inotebk.hpp>
#include <ipagehdr.hpp>
#include <isetcv.hpp>
#include <ipushbut.hpp>
#include <ifont.hpp>
#include <iexcept.hpp>
#include <icmdhdr.hpp>
#include <ihelp.hpp>
#include <iseq.h>
#include "smrtguid.hpp"

class SmartPageInfo;

// SmartTree holds a collection of SmartPageInfo objects in graph
// layout with a single root.  A SmartPageInfo object
// maintains the information for a single node of the tree. The
// primary piece of information is the SmartPage* for
// the node of the tree.  If the SmartPageInfo represents a page
// already added to the notebook, it also contains the IPageHandle
// for the notebook page and the IWindow* for the window displayed
// on the page.  Finally the SmartPageInfo stores the number of
// child nodes to facilitate traversal.
#ifdef IC_PM
   #include <itree.h>
   class SmartTree : public ITree<SmartPageInfo*, 25>
   {
   public:
      SmartTree ( ) {}
   };
#else
   #include <imwt.h>
   class SmartTree : public IMultiwayTree<25, SmartPageInfo*>
   {
   public:
      SmartTree ( ) {}
   };
#endif

class SmartPageInfoList : public ISequence<SmartPageInfo*>
{
public:
  SmartPageInfoList () : ISequence<SmartPageInfo*>(10) {}

};


class SmartPageInfo
{
public:
   SmartPageInfo ( SmartPage* smartPage,
                   IWindow*   pageWindow=0)
      : fSmartPage (smartPage),
        fPageWindow (pageWindow),
        fPageHandle (),
        fChildCount (0)
    {}
SmartPage
 *smartPage     ( )  { return fSmartPage; }

void
  setPageWindow ( IWindow* pageWindow) { fPageWindow = pageWindow; }

IWindow
 *pageWindow    ( )  { return fPageWindow; }

void
  setPageHandle ( const IPageHandle& pageHandle )
  { fPageHandle = pageHandle; }
IPageHandle
  pageHandle    ( )  { return fPageHandle; }

void
  incrementChildCount ( ) { fChildCount++; }

unsigned long
  childCount          ( ) const { return fChildCount; }


private:
SmartPage
 *fSmartPage;
IWindow
 *fPageWindow;
IPageHandle
  fPageHandle;
unsigned long
  fChildCount;
};


///
///   SmartGuide::Cursor functions
///
///   The Cursor supports cursoring the objects of the Tree:
///     1) in their selected order.  In affect, it returns
///        those pages that should be displayed in the notebook.
///     2) by descending the tree in bottomUp order (See the
///        collection class description of IPostOrder for
///        details)
///     3) by descending the tree in topDown order ( See the
///        collection class description of IPreOrder for
///        details)
///   SmartGuide cursoring is implemented using the cursor
///   for the SmartTree
///
SmartGuide::Cursor::Cursor ( SmartGuide&           smartGuide,
                            SmartGuide::IterationOrder  order)
          : fTreeCursor( new SmartTree::Cursor(*(smartGuide.fSmartTree))),
            fSmartGuide ( smartGuide),
            fOrder ( order )
{

}

SmartGuide::Cursor::~Cursor ( )
{
   delete (SmartTree::Cursor*)fTreeCursor;
}

Boolean SmartGuide::Cursor::setToFirst( )
{
   Boolean nodeFound;
   ITreeIterationOrder treeOrder = IPreorder;
   if (fOrder == bottomUp)
     treeOrder = IPostorder;

   if (fOrder == selectedOrder)
     nodeFound = fSmartGuide.fSmartTree->setToRoot(
                                           *(SmartTree::Cursor*)fTreeCursor);
   else
     nodeFound = fSmartGuide.fSmartTree->setToFirst(
                                           *(SmartTree::Cursor*)fTreeCursor, treeOrder);
   return nodeFound;
}

Boolean SmartGuide::Cursor::setToNext( )
{
   ITreeIterationOrder treeOrder = IPreorder;
   IBoolean nodeFound = false;
   if (fOrder == SmartGuide::bottomUp)
     treeOrder = IPostorder;
   if (fOrder == bottomUp || fOrder == topDown)
      nodeFound = fSmartGuide.fSmartTree->setToNext(*(SmartTree::Cursor*)fTreeCursor, treeOrder);
   else
   {
      SmartPageInfo* pageInfo = fSmartGuide.fSmartTree->elementAt(*(SmartTree::Cursor*)fTreeCursor);
      SmartPage* page = pageInfo->smartPage();

      // Tree indexes are one based, ours are 0 based.  If more than one
      // child, find the selected choice, otherwise go down only leg.
      unsigned long choice = 1;
      if (pageInfo->childCount() > 1)
        choice = page->currentChoice() + 1;
      nodeFound = fSmartGuide.fSmartTree->setToChild(choice, *(SmartTree::Cursor*)fTreeCursor);
   }
   return nodeFound;
}


Boolean SmartGuide::Cursor::setToPrevious( )
{
   ITreeIterationOrder treeOrder = IPreorder;
   Boolean nodeFound = false;
   if (fOrder == SmartGuide::bottomUp)
     treeOrder = IPostorder;
   if (fOrder == bottomUp || fOrder == topDown)
     nodeFound = fSmartGuide.fSmartTree->setToPrevious(*(SmartTree::Cursor*)fTreeCursor, treeOrder);
   else
     nodeFound = fSmartGuide.fSmartTree->setToParent(*(SmartTree::Cursor*)fTreeCursor);

   return nodeFound;
}


Boolean SmartGuide::Cursor::setToLast( )
{
   Boolean nodeFound = false;
   ITreeIterationOrder treeOrder = IPreorder;
   SmartTree* smartTree = fSmartGuide.fSmartTree;
   if (fOrder == SmartGuide::bottomUp)
     treeOrder = IPostorder;
   if (fOrder == bottomUp || fOrder == topDown)
     nodeFound = smartTree->setToLast(*(SmartTree::Cursor*)fTreeCursor, treeOrder);
   else
   {
      // For selected order, we need to chase down the selection
      // tree until we reach a leaf node.
      Boolean rootFound = smartTree->setToRoot(*(SmartTree::Cursor*)fTreeCursor);
      if (rootFound)
      {
        SmartPageInfo* pageInfo = smartTree->elementAt(*(SmartTree::Cursor*)fTreeCursor);
        for (;smartTree->isLeaf(*(SmartTree::Cursor*)fTreeCursor) == false;)
        {
          SmartPage* page = pageInfo->smartPage();
          unsigned long childIndex = page->currentChoice() + 1;
          nodeFound = smartTree->setToChild(childIndex,
                                           *(SmartTree::Cursor*)fTreeCursor);
        }
      } /* endif */
   }
   return nodeFound;
}


Boolean SmartGuide::Cursor::isValid( ) const
{

   return ((SmartTree::Cursor*)fTreeCursor)->isValid();
}

void SmartGuide::Cursor::setCurrent ( unsigned long smartPageHandle )
{
  SmartPageInfo* pageInfo = (SmartPageInfo*)smartPageHandle;
  Boolean smartPageFound = false;
  SmartTree* smartTree = fSmartGuide.fSmartTree;
  SmartTree::Cursor* cursor = (SmartTree::Cursor*)fTreeCursor;
  for ( smartTree->setToFirst( *cursor, IPreorder);
        cursor->isValid() && smartPageFound==false;
        smartTree->setToNext( *cursor, IPreorder))
  {
     SmartPageInfo* cursorPageInfo = smartTree->elementAt( *cursor);
     if (cursorPageInfo == pageInfo)
     {
        smartPageFound = true;
        return;
     }
  }
  IASSERTSTATE(smartPageFound==true)
}




///
///   SmartGuidePageHandler Definition
///
class SmartGuidePageHandler : public IPageHandler
{
public:
   SmartGuidePageHandler ( SmartGuide& smartGuide)
   : fSmartGuide(smartGuide)
   {}
protected:
virtual Boolean
  select  ( IPageSelectEvent& event )
{
  return fSmartGuide.handlePageSelect ( event);
}
/*------------------------------ Hidden Members ------------------------------*/
  SmartGuidePageHandler ( const SmartGuidePageHandler& );
SmartGuidePageHandler
 &operator=   ( const SmartGuidePageHandler& );
SmartGuide
 &fSmartGuide;
};


///
///  Smart Guide Command Handler (one per
///  smart guide)
class SmartGuideCommandHandler : public ICommandHandler
{
public:
   SmartGuideCommandHandler ( SmartGuide& smartGuide)
    : fSmartGuide ( smartGuide ) {}
protected:
Boolean
  command ( ICommandEvent& );

private:
/*------------------------------ Hidden Members ------------------------------*/
  SmartGuideCommandHandler ( const SmartGuideCommandHandler& );
SmartGuideCommandHandler
 &operator=   ( const SmartGuideCommandHandler& );
SmartGuide
 &fSmartGuide;
};






///
///   SmartGuide functions
///
SmartGuide::SmartGuide ( const IString&  guideName)
             :  fGuideName(guideName),
                fSmartTree (new SmartTree),
                fPageInfoList(0),
                fCurrentPageInfo(0),
                fFrameWindow (0),
                fNotebook(0),
                fBackButton(0),
                fNextButton(0),
                fCancelButton(0),
                fDoneButton(0),
                fHelpButton(0),
                fPageHandler(0),
                fCommandHandler(0)
{
}

SmartGuide& SmartGuide::show ( )
{

   SmartPage* firstPage = 0;

   IASSERTSTATE(fSmartTree->numberOfElements() != 0)


   // Establish the minimum size for a page
   SmartGuide::Cursor cursor (*this, topDown);
   ISize minimumSize(0,0);
   unsigned long minimumTabLength = 0;
   IFont notebookFont(fNotebook);
   for(cursor.setToFirst();
       cursor.isValid();
       cursor.setToNext())
   {
      SmartPageInfo* smartPageInfo = pageInfoAtLocation(cursor);
      SmartPage* smartPage = smartPageInfo->smartPage();
      // Store the first page
      if (firstPage==0)
      {
         firstPage = smartPage;
         fCurrentPageInfo = smartPageInfo;
      }

      // Establish the minimum tab size.
      IString tabText = smartPage->tabText();
      tabText.change(" ", "_");
      unsigned long tabLength = notebookFont.minTextWidth(tabText);
      if (tabLength>minimumTabLength)
         minimumTabLength = tabLength;

      // Establish the minimum page size.
      ISize size = smartPage->minimumSize();
      if (size > minimumSize)
        minimumSize = size;
   }

   // Create the frame window.
   minimumSize += ISize(100, 100);
   fFrameWindow = new IFrameWindow( fGuideName);

   // Create the notebook in the client area.
   INotebook::Style style = INotebook::classDefaultStyle;
//   #ifndef IC_PM
//     style |= INotebook::pmCompatible;
//   #endif

   fNotebook = new INotebook(1, fFrameWindow, fFrameWindow,
                             IRectangle(), style);
   fFrameWindow->setClient(fNotebook);

   // Change the settings of the notebook.
   fNotebook->setOrientation(INotebook::backpagesRightTabsTop);
   fNotebook->setBinding(INotebook::spiral);
   fNotebook->setTabShape(INotebook::rounded);
   fNotebook->setTabTextAlignment(INotebook::center);

  // Build the notebook pages
  refreshPages();

  // Set the size of tabs in the notebook.
  fNotebook->setMajorTabSize(ISize(minimumTabLength+35,
                                   notebookFont.maxCharHeight()+8));

   // Setup push buttons in a canvas as frame extensions.
   ISetCanvas* buttons = new ISetCanvas( WID_BUTTONS,
                                         fFrameWindow,
                                         fFrameWindow);
   fFrameWindow->addExtension(buttons, IFrameWindow::belowClient);
   fBackButton = new IPushButton( WID_BACK,
                                  buttons,
                                  buttons);
   fNextButton = new IPushButton( WID_NEXT,
                                  buttons,
                                  buttons);
   fCancelButton = new IPushButton( WID_CANCEL,
                                  buttons,
                                  buttons);
   fDoneButton = new IPushButton( WID_DONE,
                                  buttons,
                                  buttons);
   fHelpButton = new IPushButton( WID_HELP,
                                              buttons,
                                              buttons);
   fBackButton->setText("<< Back");
   fBackButton->disable();
   fNextButton->setText("Next >>");

   fCancelButton->enableGroup();
   fCancelButton->setText("Cancel");
   fDoneButton->setText("Done");

   fHelpButton->enableGroup();
   fHelpButton->setText("Help");

   // Separate the buttons by group.
   buttons->setGroupPad(20);

  // Setup our Command Handler for the buttons (and CID_REFRESH
  // via the notebook.
  fCommandHandler = new SmartGuideCommandHandler(*this);
  fCommandHandler->handleEventsFor(fFrameWindow);
  fCommandHandler->handleEventsFor(fNotebook);

  // Setup our page handler for delayed addition of pages.
  fPageHandler = new SmartGuidePageHandler( *this);
  fPageHandler->handleEventsFor(fNotebook);

  // Give the notebook the focus and show the frame.
  fNotebook->setFocus();
  fFrameWindow->show();
  return *this;
}


SmartGuide& SmartGuide::refreshPages  ( )
{
  // Note: This function assumes fCurrentPageInfo is pointing
  // at the "current" page in the SmartGuide.  This is typically
  // either the root page when the SmartGuide is first created, or
  // the page undergoing a selection change, and thus causing
  // the notebook to need rebuilding.
  IASSERTSTATE(fCurrentPageInfo!=0);


  // Store the current page info list and create a new one.
  SmartPageInfoList* currentPageInfoList = fPageInfoList;
  fPageInfoList = new SmartPageInfoList;


  // Build the new page info list by determining the newly selected path.
  SmartGuide::Cursor selectionCursor(*this, selectedOrder);
  for(selectionCursor.setToFirst();
      selectionCursor.isValid();
      selectionCursor.setToNext())
  {
     // Get the page information and add it to the page info list.
     SmartPageInfo* cursorPageInfo =
              pageInfoAtLocation( selectionCursor);
     fPageInfoList->addAsLast(cursorPageInfo);
  }



  // Compare the old and new page info lists to decide which pages
  // to remove and which pages to add to the notebook.
  IPageHandle pageHandle = 0;
  INotebook::PageSettings pageSettings(
          INotebook::PageSettings::majorTab
        | INotebook::PageSettings::autoPageSize);
  Boolean differenceFound = false;
  SmartPageInfoList::Cursor newListCursor (*fPageInfoList);
  SmartPageInfoList::Cursor* currentListCursor = 0;
  if(currentPageInfoList)
  {
    currentListCursor = new SmartPageInfoList::Cursor(*currentPageInfoList);
    currentListCursor->setToFirst();
  }
  else
    differenceFound = true;

  for(newListCursor.setToFirst();
      newListCursor.isValid();
      newListCursor.setToNext())
  {

    SmartPageInfo* newPageInfo = fPageInfoList->elementAt(newListCursor);
    SmartPage* newSmartPage = newPageInfo->smartPage();
    if(!differenceFound)
    {
       SmartPageInfo* currentPageInfo = currentPageInfoList->elementAt(*currentListCursor);
       if(currentPageInfo!=newPageInfo)
       {
          // Once we get a difference between the two lists, remove the
          // remaining pages from the notebook.
          differenceFound = true;
          for(; currentListCursor->isValid(); currentListCursor->setToNext())
          {
             currentPageInfo = currentPageInfoList->elementAt(*currentListCursor);
             fNotebook->removePage(currentPageInfo->pageHandle());
             currentPageInfo->setPageHandle(0);
          }
       }
       else
         currentListCursor->setToNext();
    }
    if(differenceFound)
    {
       // Create the Page Window if one doesn't exist for the current
       // page of the notebook.  This should only happen
       // for the root page of the notebook as all other pages are
       // created when the page is selected.
       pageSettings.setTabText(newSmartPage->tabText());
       if (newPageInfo==fCurrentPageInfo && fCurrentPageInfo->pageWindow()==0)
       {
         IWindow* firstWindow = fCurrentPageInfo->smartPage()->
                           createAndOrphanPage( fNotebook,
                                                fNotebook,
                                                IRectangle(IPoint(0,0),newPageSize()));
         fCurrentPageInfo->setPageWindow(firstWindow);
         pageHandle =  fNotebook->addLastPage(
                                  pageSettings, firstWindow);
       }
       else if (newPageInfo->pageWindow())
         pageHandle =  fNotebook->addLastPage(
                                  pageSettings, newPageInfo->pageWindow());
       else
         pageHandle = fNotebook->addLastPage(pageSettings);
       newPageInfo->setPageHandle( pageHandle);
    }
  }
  delete currentPageInfoList;
  currentPageInfoList = 0;

  return *this;
}


unsigned long SmartGuide::addPage ( SmartPage*    smartPage,
                                    unsigned long referencePageHandle)
{
  Boolean fPageAdded = false;
  SmartPageInfo* pageInfo = 0;
  SmartPageInfo* referencePageInfo = (SmartPageInfo*)referencePageHandle;

  // If no reference page, then add as the root
  if (referencePageHandle == 0) {
     pageInfo = new SmartPageInfo (smartPage);
     fSmartTree->addAsRoot(pageInfo);
  }
  // Else find the reference page and add the page as a
  // child.
  else
  {
     SmartTree::Cursor cursor (*fSmartTree);
     for (fSmartTree->setToFirst(cursor, IPreorder);
          cursor.isValid() && fPageAdded==false;
          fSmartTree->setToNext (cursor, IPreorder) )
     {
        SmartPageInfo* cursorPageInfo = fSmartTree->elementAt(cursor);
        if (cursorPageInfo == referencePageInfo)
        {
           pageInfo = new SmartPageInfo(smartPage);
           cursorPageInfo->incrementChildCount();
           fSmartTree->addAsChild( cursor,
                                   cursorPageInfo->childCount(),
                                   pageInfo);
           fPageAdded=true;
        } /* endif */
     } /* endfor */
  IASSERTSTATE(fPageAdded == true)
  }
  return (unsigned long)pageInfo;
}

Boolean SmartGuide::isOKToClose( IString& closeErrorIfFalse )
{
  // This is where you determine if each smart page in
  // in the current stack has enough information to
  // close.
  Boolean okToClose = true;
  SmartGuide::Cursor cursor(*this, selectedOrder);
  IString errorMessage("");
  for(cursor.setToFirst();
      cursor.isValid() && okToClose == true;
      cursor.setToNext())
  {
     SmartPage* smartPage = pageAtLocation(cursor);
     okToClose = smartPage->isOKToClose(closeErrorIfFalse);
     if(!okToClose)
     {
        fCurrentPageInfo = pageInfoAtLocation(cursor);
        break;
     }
  }
  return okToClose;
}


SmartPage* SmartGuide::pageAtLocation ( Cursor& cursor) const
{
   return pageInfoAtLocation(cursor)->smartPage();
}

SmartPageInfo* SmartGuide::pageInfoAtLocation ( Cursor& cursor) const
{
   return fSmartTree->elementAt(*(SmartTree::Cursor*)cursor.fTreeCursor);
}


SmartPageInfo* SmartGuide::pageInfoWithHandle ( const IPageHandle& pageHandle) const
{
   SmartGuide::Cursor cursor( *(SmartGuide*)this, selectedOrder);
   for(cursor.setToFirst();
       cursor.isValid();
       cursor.setToNext())
   {
     SmartPageInfo* cursorPageInfo = pageInfoAtLocation(cursor);
     if (cursorPageInfo->pageHandle() == pageHandle)
       return cursorPageInfo;
   }
   return 0;
}

IString SmartGuide::asString( ) const
{
  return fGuideName;
}
IString SmartGuide::asDebugInfo( ) const
{
  IString str("\nSelection path:");
  SmartGuide::Cursor cursor(*(SmartGuide*)this, selectedOrder);
  for(cursor.setToFirst();
      cursor.isValid();
      cursor.setToNext())
  {
     SmartPageInfo* pageInfo=pageInfoAtLocation(cursor);
     str += "\n  "+pageInfo->smartPage()->tabText()+"("
         +IString((unsigned long)pageInfo).d2x()
         + ") Selection: "
         + IString(pageInfo->smartPage()->currentChoice());
  }

  str += "\n\nTopDown Dump:";
  SmartGuide::Cursor cursor2(*(SmartGuide*)this, topDown);
  for(cursor2.setToFirst();
      cursor2.isValid();
      cursor2.setToNext())
  {
     SmartPageInfo* pageInfo=pageInfoAtLocation(cursor2);
     str += "\n  "+pageInfo->smartPage()->tabText()+"("
         +IString((unsigned long)pageInfo).d2x()
         + ") Selection: "
         + IString(pageInfo->smartPage()->currentChoice());
  }
  return str;
}


Boolean SmartGuide::handleHelp     ( )
{
  // Not implemented.
  return true;
}

Boolean SmartGuide::handleBack     ( )
{
  SmartGuide::Cursor cursor(*this, selectedOrder);
  cursor.setCurrent((unsigned long)(void*)fCurrentPageInfo);
  cursor.setToPrevious();

  fCurrentPageInfo = pageInfoAtLocation(cursor);
  fNotebook->turnToPage(fCurrentPageInfo->pageHandle());

  return true;
}

Boolean SmartGuide::handleNext( )
{
  SmartGuide::Cursor cursor(*this, selectedOrder);
  cursor.setCurrent((unsigned long)(void*)fCurrentPageInfo);
  cursor.setToNext();
  IASSERTSTATE(cursor.isValid())

  fCurrentPageInfo = pageInfoAtLocation(cursor);
  fNotebook->turnToPage(fCurrentPageInfo->pageHandle());

  return true;
}

Boolean SmartGuide::handleCancel( )
{
  fFrameWindow->close();
  return true;
}

Boolean SmartGuide::handleDone ( )
{
  IString errorMessage("");
  if(isOKToClose(errorMessage))
    fFrameWindow->close();
  else
  {
    fNotebook->setStatusText(fCurrentPageInfo->pageHandle(),errorMessage);
    fNotebook->turnToPage(fCurrentPageInfo->pageHandle());
  }
  return true;
}


ISize SmartGuide::newPageSize ( ) const
{
  return fLastPageSize;
}

Boolean SmartGuide::handleRefresh ( )
{
  refreshPages();
  return true;
}

Boolean SmartGuide::handlePageSelect  ( IPageSelectEvent& event )
{
  IPageHandle selectedPage = event.pageHandle();

  INotebook* notebook = event.notebook();
  INotebook::PageSettings pageData =
                event.notebook()->pageSettings(selectedPage);
  fCurrentPageInfo = pageInfoWithHandle(selectedPage);
  SmartPage* smartPage = fCurrentPageInfo->smartPage();

  // Create the window if it doesn't already exist.
  if (fCurrentPageInfo->pageWindow() == 0)
  {
    IWindow* nextPage = smartPage->createAndOrphanPage(
                                        notebook,
                                        notebook,
                                        newPageSize());
    fCurrentPageInfo->setPageWindow(nextPage);

    // Size the window to the size of the page.
//    nextPage->sizeTo(notebook->pageSize());

    // Put the page on the notebook
    notebook->setWindow( selectedPage, nextPage);
    nextPage->show();
  }

  // Disable or enable Back/Next buttons
  IPageHandle firstPage = fNotebook->firstPage();
  IPageHandle lastPage = fNotebook->lastPage();
  if (firstPage==selectedPage)
    fBackButton->disable();
  else
    fBackButton->enable();
  if (lastPage==selectedPage)
    fNextButton->disable();
  else
    fNextButton->enable();

  return false;
}

SmartGuide& SmartGuide::setHelpWindow ( IHelpWindow& helpWindow)
{ fHelpWindow = &helpWindow; return *this; }


Boolean SmartGuideCommandHandler::command ( ICommandEvent& event)
{
   switch (event.commandId()) {
     case  WID_BACK :
        fSmartGuide.handleBack( );
        break;
     case  WID_NEXT :
        fSmartGuide.handleNext( );
        break;
     case  WID_CANCEL :
        fSmartGuide.handleCancel( );
        break;
     case  WID_DONE :
        fSmartGuide.handleDone( );
        break;
     case  WID_HELP :
        fSmartGuide.handleHelp( );
        break;
     case  CID_REFRESH :
        fSmartGuide.refreshPages( );
        break;
   } /* endswitch */
   return true;
}

