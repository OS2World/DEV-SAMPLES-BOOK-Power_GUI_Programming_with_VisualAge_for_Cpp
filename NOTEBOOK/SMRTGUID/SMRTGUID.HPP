#ifndef _SMRTGUID_
#define _SMRTGUID_
//************************************************************
// Notebook Control - Smart Guide Notebook
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <istring.hpp>
#include <ibitflag.hpp>
#include <irect.hpp>

class IWindow;
class IFrameWindow;
class INotebook;
class IMultiCellCanvas;
class IPageSelectEvent;
class IPageHandle;
class IPushButton;
class IHelpWindow;
class SmartGuideList;
class SmartGuidePageHandler;
class SmartGuideCommandHandler;
class SmartChoiceSelectHandler;
class SmartChoiceList;
class SmartPageInfoList;
class SmartTree;
class SmartPageInfo;

//  SmartPage is an abstract base class that defines the protocol
//  for pages in a SmartGuide.  This includes help for the
//  page (not implemented), text for the notebook tab,
//  the protocol to specify the size of the view for the page,
//  and the protocol to create the view of the page.
//
class SmartPage   {

public:
/*------------------------------- Constructors -----------------------*/
SmartPage ( )
  : fTabText(""),
    fHelpId (0)
  { }
virtual
 ~SmartPage ( )
  { }

/*----------------------------- Panel Creation -----------------------*/
virtual ISize
  minimumSize    ( ) const;

virtual IWindow*
  createAndOrphanPage ( IWindow*          parent,
                        IWindow*          owner,
                        const IRectangle& initialRect) = 0;

/*------------------------- Navigation and Choice --------------------*/
// The following function is called by the SmartGuide when
// navigating to the next page in the notebook.  All Choices are
// zero based.  The zero returned here causes traversal to
// the first leg of the node.  Multi-choice smart pages overide this to
// pick other legs.
virtual unsigned long
  currentChoice  ( )  const { return 0; }

// The following function is called by SmartGuide to determine
// if it is ok to enable the "Done" button.
virtual Boolean
  isOKToClose    ( IString& closeErrorIfFalse ) const;

/*----------------------------- Panel Text ---------------------------*/
virtual SmartPage
 &setTabText     ( const IString& tabText);

virtual IString
  tabText        ( ) const;


/*------------------------------ Displaying Help ---------------------*/
// The following functions store and retrieve a help identifier
// for the page.
virtual SmartPage
 &setHelpId      ( unsigned long helpId);

virtual unsigned long
  helpId         ( ) const;

private:
/*------------------------------ Hidden Members ----------------------*/
  SmartPage ( const SmartPage& );
SmartPage
 &operator=   ( const SmartPage& );

IString
 fTabText;
unsigned long
 fHelpId;

}; // SmartPage




// TextSmartPage is a SmartPage that adds a label
// and non-editable text to the page.
//
class TextSmartPage : public SmartPage
{
typedef SmartPage
  Inherited;
public:
/*------------------------------- Constructors -----------------------*/
  TextSmartPage ( )
   :  fPageLabel ( "" ),
      fPageText  ( "" )
    {}

/*----------------------------- Panel Creation -----------------------*/
virtual ISize
  minimumSize     ( ) const;

virtual IWindow*
  createAndOrphanPage ( IWindow*          parent,
                        IWindow*          owner,
                        const IRectangle& initialRect);

/*----------------------------- Panel Text ---------------------------*/
virtual TextSmartPage
 &setPageLabel   ( const IString& pageLabel),
 &setPageText    ( const IString& pageText),
 &setPageTextFile( const IString& pageTextFile);

virtual IString
  pageLabel      ( ) const,
  pageText       ( ) const,
  pageTextFile   ( ) const;

private:
/*------------------------------ Hidden Members ----------------------*/
  TextSmartPage ( const TextSmartPage& );
TextSmartPage
 &operator=   ( const TextSmartPage& );
IString
 fPageLabel,
 fPageText,
 fPageTextFile;
IMultiCellCanvas
 *fMultiCellCanvas;
};

// SingleChoiceSmartPage is a SmartPage that adds
// the ability for the page to display multiple
// choices and overrides "currentChoice" to
// enable the SmartGuide to pick different paths.
//
class SingleChoiceSmartPage : public TextSmartPage
{
typedef TextSmartPage
  Inherited;
public:


/*------------------------------- Constructors -----------------------*/
  SingleChoiceSmartPage  ( )
   : fSmartChoiceList  ( 0 ),
     fNumberOfChoices  ( 0 ),
     fSelectedChoice   ( 0 ),
     fSelectHandler    ( 0 ),
     fSelectionWindow  ( 0 )
    {}

/*----------------------------- Panel Creation -----------------------*/
virtual ISize
  minimumSize     ( ) const;

virtual IWindow*
  createAndOrphanPage ( IWindow*          parent,
                        IWindow*          owner,
                        const IRectangle& initialRect);

/*------------------------- Navigation and Choice --------------------*/
virtual SingleChoiceSmartPage
 &addChoice ( const IString&  choiceText,
              unsigned long   helpId = 0 );

virtual SingleChoiceSmartPage
 &setSelectedChoice   ( unsigned long choiceIndex);

virtual unsigned long
  currentChoice       ( ) const;

virtual IString
  choiceTextAtIndex   ( unsigned long index);

unsigned long
  numberOfChoices     ( ) const;

virtual Boolean
  isOKToClose    ( IString& closeErrorIfFalse ) const;

/*------------------------------ Displaying Help ---------------------*/
// Override the following function to return a choice sensitive
// help id. You specify the help id on the constructor.
virtual unsigned long
  helpId    ( ) const;

private:
/*------------------------------ Hidden Members ----------------------*/
  SingleChoiceSmartPage ( const SingleChoiceSmartPage& );
SingleChoiceSmartPage
 &operator=   ( const SingleChoiceSmartPage& );

SmartChoiceList
 *fSmartChoiceList;
unsigned long
  fNumberOfChoices;
unsigned long
  fSelectedChoice;
SmartChoiceSelectHandler
 *fSelectHandler;
IWindow
 *fSelectionWindow;
};

// SmartGuide contains all smart pages and controls:
// 1) Telling a page to create its windows
// 2) Navigation through the pages of the guide
// 3) Cancel and Close requests
//
class SmartGuide
{
public:
class Cursor;


/*------------------------------- Constructors -----------------------*/
  SmartGuide    ( const IString&  guideName);



/*------------------------- Navigation and Choice --------------------*/
unsigned long
  addPage  ( SmartPage*     smartPage,
             unsigned long  referencePageHandle=0);
virtual Boolean
  isOKToClose    ( IString& closeErrorIfFalse );

/*----------------------------- Panel Creation -----------------------*/
virtual SmartGuide
 &show           ( ),
 &refreshPages   ( );

virtual ISize
  newPageSize    ( ) const;

/*------------------------------ Displaying Help ---------------------*/
virtual SmartGuide
 &setHelpWindow     ( IHelpWindow& helpWindow );


/*------------------------------ Cursor Functions --------------------*/
enum IterationOrder
{
   selectedOrder,
   topDown,
   bottomUp
};

SmartPage
 *pageAtLocation ( Cursor& cursor) const;

  class Cursor {
  public :
  /*------------------------------- Constructors -----------------------*/
    Cursor  ( SmartGuide&                 smartGuide,
              SmartGuide::IterationOrder  order =
                                           SmartGuide::selectedOrder);

  virtual
    ~Cursor ( );

  /*------------------------------ Page Iteration ----------------------*/
  virtual Boolean
    setToFirst    ( ),
    setToNext     ( ),
    setToPrevious ( ),
    setToLast     ( ),
    isValid       ( ) const;

  void
    setCurrent ( unsigned long smartPageHandle );

  private:
  /*----------------------------- Hidden Members -----------------------*/
  Cursor       ( const Cursor& cursor );
  Cursor
   &operator=  ( const Cursor& cursor );

  /*--------------------------------- Private --------------------------*/
  void
   *fTreeCursor;
  SmartGuide
   &fSmartGuide;
  SmartGuide::IterationOrder
    fOrder;
  friend class SmartGuide;
  };


/*------------------------------ Debug Functions ---------------------*/
virtual IString
  asString       ( ) const,
  asDebugInfo    ( ) const;

protected:
/*------------------------------ Callback Functions ------------------*/
virtual Boolean
  handlePageSelect  ( IPageSelectEvent& event ),
  handleBack        ( ),
  handleNext        ( ),
  handleCancel      ( ),
  handleDone        ( ),   // Open can of worms at the moment
  handleHelp        ( ),
  handleRefresh     ( );


SmartPageInfo
 *pageInfoAtLocation ( Cursor& cursor) const,
 *pageInfoWithHandle ( const IPageHandle& pageHandle) const;



private:
/*----------------------------- Hidden Members -------------------------*/
SmartGuide       ( const SmartGuide& );
SmartGuide
 &operator=  ( const SmartGuide&);

/*--------------------------------- Private ----------------------------*/
// Consider moving the following to a private data class.
IString
  fGuideName;
SmartTree
 *fSmartTree;
SmartPageInfoList
 *fPageInfoList;
SmartPageInfo
 *fCurrentPageInfo;
IFrameWindow
 *fFrameWindow;
INotebook
 *fNotebook;
IPushButton
 *fBackButton,
 *fNextButton,
 *fCancelButton,
 *fDoneButton,
 *fHelpButton;
SmartGuidePageHandler
 *fPageHandler;
SmartGuideCommandHandler
 *fCommandHandler;
ISize
 fLastPageSize;
IHelpWindow
 *fHelpWindow;
friend class SmartGuidePageHandler;
friend class SmartGuideCommandHandler;
friend class Cursor;
};

// Constants for Panels
#define WID_TEXTCANVAS    100
#define WID_TEXTLABEL     101
#define WID_TEXTTEXT      102
#define WID_SELECTRADIO   103  // 5 numbers Required
#define WID_CLIENTCANVAS  110
#define WID_SELECTLISTBOX 111
#define WID_SELECTCANVAS  112

#define WID_BUTTONS 200
#define WID_BACK    201
#define WID_NEXT    202
#define WID_HELP    203
#define WID_CANCEL  204
#define WID_DONE    205
#define CID_REFRESH 206

#endif // _SMRTGUID_
