//************************************************************
// Notebook Control - Smart Guide Notebook 
//
// Classes:  TextSmartPage 
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <irect.hpp>
#include <imcelcv.hpp>
#include <istattxt.hpp>
#include <istring.hpp>
#include <ifont.hpp>
#include <imle.hpp>
#include <icolor.hpp>
#include "smrtguid.hpp"

IWindow* TextSmartPage::createAndOrphanPage (
                                IWindow*          parent,
                                IWindow*          owner,
                                const IRectangle& initialRect)
{
   // Create the multicell to house all control in the page.
   IMultiCellCanvas::Style style(IMultiCellCanvas::classDefaultStyle);
   style = style &~ IWindow::visible;
   fMultiCellCanvas = new IMultiCellCanvas( WID_TEXTCANVAS,
                                            parent,
                                            owner,
                                            initialRect, 
                                            style);

   // Create a static for the label
   IStaticText* staticLabel = new IStaticText ( WID_TEXTLABEL,
                                                fMultiCellCanvas,
                                                fMultiCellCanvas);

   // Create a read-only MLE for the text.
   IMultiLineEdit::Style mleStyle = IWindow::visible
                                  | IMultiLineEdit::wordWrap
                                  | IMultiLineEdit::verticalScroll
                                  | IMultiLineEdit::readOnly;
   IMultiLineEdit* text     = new IMultiLineEdit( WID_TEXTTEXT,
                                                  fMultiCellCanvas,
                                                  fMultiCellCanvas,
                                                  IRectangle(),
                                                  mleStyle   );


   // Put the text in the Label, change the foreground to blue,
   // and request auto delete of the window.
   (*staticLabel)
     .setText             ( fPageLabel)
     .setForegroundColor  ( IColor::blue)
     .setAutoDeleteObject ( );

   // Call setMinimumSize to keep the label from determining the
   // minimum width of the window.
   IFont staticFont(staticLabel);
   unsigned long staticHeight = staticFont.maxCharHeight();
   unsigned long staticWidth = staticFont.avgCharWidth()*10;
   staticLabel->setMinimumSize (ISize(staticWidth, staticHeight));

   // Put the text in the MLE.
   if (fPageTextFile.length() != 0)
     text->importFromFile(fPageTextFile);
   else
     text->setText(fPageText);
   text->setTop(1);


   // Change the background of the text to white,
   // and request auto delete of control.
   (*text)
     .setBackgroundColor  ( IColor::white)
     .setAutoDeleteObject ( );

   // Add the cells to the canvas.
   (*fMultiCellCanvas)
     .addToCell      ( staticLabel, 1, 2, 2)
     .addToCell      ( text,        2, 4)
     .setRowHeight   ( 1, 2, false)
     .setRowHeight   ( 3, 5, false)
     .setRowHeight   ( 5, 3, false)
     .setColumnWidth ( 1, 5, false)
     .setColumnWidth ( 2, 5, true)
     .setColumnWidth ( 3, 5, false)
     .setAutoDeleteObject( );

  fMultiCellCanvas->setRowHeight(4, 2, true);
  fMultiCellCanvas->show();
  return fMultiCellCanvas;
}

TextSmartPage& TextSmartPage::setPageLabel   ( const IString& pageLabel)
{ fPageLabel = pageLabel; return *this; }

TextSmartPage& TextSmartPage::setPageText    ( const IString& pageText)
{ fPageText = pageText; return *this; }

TextSmartPage& TextSmartPage::setPageTextFile( const IString& pageTextFile)
{ fPageTextFile = pageTextFile; return *this; }

IString TextSmartPage::pageLabel      ( ) const
{ return fPageLabel; }

IString TextSmartPage::pageText       ( ) const
{ return fPageText; }

IString TextSmartPage::pageTextFile   ( ) const
{ return fPageTextFile; }


ISize TextSmartPage::minimumSize     ( ) const
{
   return ISize(300,100);

}


