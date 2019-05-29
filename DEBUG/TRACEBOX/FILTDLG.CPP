//************************************************************
// Problem Determination  - Trace Queue Browser
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include "filtdlg.hpp"
#include "filtdlg.h"

#include <icmdhdr.hpp>
#include <iedithdr.hpp>
#include <ifont.hpp>
#include <iselhdr.hpp>


class FilterCommandHandler : public ICommandHandler {
public:
/*------------------------------- Constructors -------------------------------*/
  FilterCommandHandler ( FilterDialog& dialog )
      : fdialog( dialog ) { }

protected:
/*----------------------------- Event Processing -----------------------------*/
virtual Boolean
  command       ( ICommandEvent& event );

private:
  FilterDialog&   fdialog;

  FilterCommandHandler             ( const FilterCommandHandler&  );
  FilterCommandHandler& operator = ( const FilterCommandHandler&  );
};

class FilterSelectHandler : public ISelectHandler {
public:
/*------------------------------- Constructors -------------------------------*/
  FilterSelectHandler ( FilterDialog& dialog )
      : fdialog( dialog ) { }

protected:
/*----------------------------- Event Processing -----------------------------*/
virtual Boolean
  enter    ( IControlEvent& event ),
  selected ( IControlEvent& event );

private:
  FilterDialog&   fdialog;

  FilterSelectHandler             ( const FilterSelectHandler&  );
  FilterSelectHandler& operator = ( const FilterSelectHandler&  );
};

class FilterEditHandler : public IEditHandler {
public:
/*------------------------------- Constructors -------------------------------*/
  FilterEditHandler ( FilterDialog& dialog )
      : fdialog( dialog ) { }

protected:
/*----------------------------- Event Processing -----------------------------*/
virtual Boolean
  edit     ( IControlEvent& event );

private:
  FilterDialog&   fdialog;

  FilterEditHandler             ( const FilterEditHandler&  );
  FilterEditHandler& operator = ( const FilterEditHandler&  );
};


/*------------------------------------------------------------------------------
| FilterDialog::FilterDialog                                                   |
------------------------------------------------------------------------------*/
FilterDialog::FilterDialog( FilterSet& filterset, IWindow* owner )
   :  IFrameWindow( IResourceId( FLTD_DIALOG ),
                    0, owner,
                    IRectangle(),
                    IFrameWindow::defaultStyle() |
                    IFrameWindow::dialogBorder |
                    IFrameWindow::dialogBackground ),
      ffilterset( filterset ),
      fcanvas   (FLTD_CANVAS, this, this),
      fisExclude(FLTD_EXCLUDE  ,  &fcanvas, &fcanvas,
                 IRectangle(),
                 ICheckBox::defaultStyle() | IControl::tabStop ),
      flabel    (FLTD_LABEL    ,  &fcanvas, &fcanvas),
      fentry    (FLTD_ENTRY    ,  &fcanvas, &fcanvas,
                 IRectangle(),
                 IEntryField::defaultStyle() | IControl::tabStop ),
      flist     (FLTD_LIST     ,  &fcanvas, &fcanvas, IRectangle(),
                 IListBox::defaultStyle() | IBaseListBox::multipleSelect ),
      fbuttons1 (FLTD_BUTTONS1 ,  &fcanvas, &fcanvas, IRectangle(),
                 (ISetCanvas::defaultStyle() &  ~ISetCanvas::packTight) |
                 ISetCanvas::packExpanded  ),
      fadd      (FLTD_ADD      ,  &fbuttons1, &fbuttons1,
                 IRectangle(),
                 IPushButton::defaultStyle() | IControl::tabStop ),
      fremove   (FLTD_REMOVE   ,  &fbuttons1, &fbuttons1,
                 IRectangle(),
                 IPushButton::defaultStyle() | IControl::tabStop ),
      fbuttons2 (FLTD_BUTTONS2 ,  this, this, IRectangle(),
                 (ISetCanvas::defaultStyle() &  ~ISetCanvas::packTight) |
                 ISetCanvas::packExpanded  ),
      fok       (FLTD_OK       ,  &fbuttons2, &fbuttons2,
                 IRectangle(),
                 IPushButton::defaultStyle() |
                 IPushButton::defaultButton | IControl::tabStop ),
      fcancel   (FLTD_CANCEL   ,  &fbuttons2, &fbuttons2,
                 IRectangle(),
                 IPushButton::defaultStyle() | IControl::tabStop ),
      fcmdhdr   (new FilterCommandHandler( *this )),
      fselhdr   (new FilterSelectHandler( *this )),
      fedithdr  (new FilterEditHandler( *this ))
{
   // set up handlers
   fcmdhdr->handleEventsFor( this );
//   fselhdr->handleEventsFor( &flist );
//   fedithdr->handleEventsFor( &fentry );
   fselhdr->handleEventsFor( &fcanvas );
   fedithdr->handleEventsFor( &fcanvas );

   // set up control text
   fisExclude.setText( IResourceId( FLTD_EXCLUDE ) );
   fisExclude.select( ffilterset.isExcludeList );
   if (ffilterset.isExcludeList)
      flabel.setText  ( IResourceId( FLTD_LABEL1 ) );
   else
      flabel.setText  ( IResourceId( FLTD_LABEL0 ) );
   fadd.setText    ( IResourceId( FLTD_ADD   ) );
   fremove.setText ( IResourceId( FLTD_REMOVE) );
   fok.setText     ( IResourceId( FLTD_OK    ) );
   fcancel.setText ( IResourceId( FLTD_CANCEL) );

   // load the listbox with elements from filter set
   FilterSet::Cursor cursor(ffilterset);
   for (cursor.setToFirst(); cursor.isValid(); cursor.setToNext() )
      {
      flist.addAscending( cursor.element() );
      }


   // set up listbox and entry field size
   flist.setMinimumRows(6);
   flist.setMinimumCharacters(40);
   fentry.setLimit( 999 );       // allow big entry field
   IFont  entryFont( &fentry );
   fentry.setMinimumSize(  ISize( entryFont.avgCharWidth() * 40,
                                  fentry.minimumSize().height() ) );

   // add controls to canvas
   //   1   2       3      4+       5
   //2    fisExclude     flist
   //3                     "
   //4    flabel           "
   //5    fentry           "
   //6+                    "
   //7    fbuttons1        "
   //8

   fcanvas.addToCell( &fisExclude,2, 2 );
   fcanvas.addToCell( &flabel,    2, 4 );
   fcanvas.addToCell( &fentry,    2, 5 );
   fcanvas.addToCell( &fbuttons1, 2, 7 );
   fcanvas.addToCell( &flist,     4, 2, 1, 6 );
   // setup canvas layout
   fcanvas.setRowHeight( 6, IMultiCellCanvas::defaultCell().height(), true );
   fcanvas.setColumnWidth( 4, IMultiCellCanvas::defaultCell().width(), true );
   // padding
   fcanvas.setRowHeight( 8, IMultiCellCanvas::defaultCell().height() );
   fcanvas.setColumnWidth( 5, IMultiCellCanvas::defaultCell().width() );

   // Put OK and cancel buttons at bottom
   addExtension(&fbuttons2, IFrameWindow::belowClient,
                 (unsigned long)fbuttons2.minimumSize().height());

   // disable add and remove for now
   fadd.disable();
   fremove.disable();

   // Size the dialog around the client canvas
   IRectangle  newrect( IPoint(0,0),  fcanvas.minimumSize() );
   newrect.centerAt( owner->rect().center() );
   moveSizeToClient( newrect );
}


/*------------------------------------------------------------------------------
| FilterDialog::~FilterDialog                                                  |
------------------------------------------------------------------------------*/
FilterDialog::~FilterDialog( )
{
   fcmdhdr->stopHandlingEventsFor( this );
//   fselhdr->stopHandlingEventsFor( &flist );
//   fedithdr->stopHandlingEventsFor( &fentry );
   fselhdr->stopHandlingEventsFor( this );
   fedithdr->stopHandlingEventsFor( this );
   delete fselhdr;
   delete fcmdhdr;
   delete fedithdr;
}

/*------------------------------------------------------------------------------
| IBase::Boolean FilterCommandHandler::command                                 |
------------------------------------------------------------------------------*/
IBase::Boolean FilterCommandHandler::command       ( ICommandEvent& event )
{
   Boolean handled = true;
   switch ( event.commandId() )
      {
      case  FLTD_ADD     :
         // Add entry field contents to listbox
         if (fdialog.flist.locateText( fdialog.fentry.text() ) ==
             IBaseListBox::notFound )
            {
            fdialog.flist.addAscending( fdialog.fentry.text() );
            }
         fdialog.fentry.setText("");
         fdialog.fentry.setFocus();
         break;

      case  FLTD_REMOVE  :
         {
         // remove all selections
         IBaseListBox::Cursor cursor (fdialog.flist,
                                      IBaseListBox::Cursor::selectedItems );
         for (cursor.setToFirst(); cursor.isValid(); )
            {
            fdialog.flist.removeAt( cursor );
            }
         // disable remove till next selection
         fdialog.fremove.disable();
         }
         break;
      case  FLTD_OK      :
         {
         // copy listbox contents to collection
         IBaseListBox::Cursor cursor (fdialog.flist,
                                      IBaseListBox::Cursor::allItems );
         fdialog.ffilterset.removeAll();
         for (cursor.setToFirst(); cursor.isValid(); cursor.setToNext() )
            {
            fdialog.ffilterset.add( fdialog.flist.elementAt(cursor) );
            }
         }
         fdialog.dismiss();
         break;
      case  FLTD_CANCEL  :
         fdialog.dismiss();
         break;
      default:
         handled = false;
      }

   return handled;
}

/*------------------------------------------------------------------------------
| IBase::Boolean FilterSelectHandler::enter                                    |
------------------------------------------------------------------------------*/
IBase::Boolean FilterSelectHandler::enter    ( IControlEvent& event )
{

   return false;
}

/*------------------------------------------------------------------------------
| IBase::Boolean FilterSelectHandler::selected                                 |
------------------------------------------------------------------------------*/
IBase::Boolean FilterSelectHandler::selected ( IControlEvent& event )
{
   // make include/exclude match button
   Boolean excluded = fdialog.fisExclude.isSelected();
   if ((excluded && !fdialog.ffilterset.isExcludeList)  ||
       (!excluded && fdialog.ffilterset.isExcludeList) )
      {
      fdialog.ffilterset.isExcludeList = excluded;
      if (excluded)
         fdialog.flabel.setText  ( IResourceId( FLTD_LABEL1 ) );
      else
         fdialog.flabel.setText  ( IResourceId( FLTD_LABEL0 ) );
      }

   // enable/disable the remove button
   if (fdialog.flist.numberOfSelections() != 0)
      {
      fdialog.fremove.enable();
      }
   else
      {
      fdialog.fremove.disable();
      }
   return false;
}

/*------------------------------------------------------------------------------
| IBase::Boolean FilterEditHandler::edit                                       |
------------------------------------------------------------------------------*/
IBase::Boolean FilterEditHandler::edit ( IControlEvent& event )
{
   // if there is text in the entry field enable the add button
   if (fdialog.fentry.textLength() != 0)
      {
      if ( !fdialog.fadd.isEnabled() )
         {
         if (fdialog.fok.isDefault() )
            fdialog.fok.disableDefault();
         fdialog.fadd.enable();
         fdialog.fadd.enableDefault();
         }
      }
   else
      {
      fdialog.fadd.disable();
      fdialog.fadd.disableDefault();
      fdialog.fok.enableDefault();
      }
   return false;
}

