/************************************************************
/ List Controls - List Box Custom Drawing
/
/ Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
/ Copyright (c) 1997 John Wiley & Sons, Inc.
/ All Rights Reserved.
************************************************************/
#include <ilistbox.hpp>
#include <irect.hpp>
#include <ifont.hpp>
#include <icolor.hpp>
#include <igbitmap.hpp>
#include <igstring.hpp>
#include <igrafctx.hpp>
#include <igrect.hpp>
#include <igbundle.hpp>
#include <istring.hpp>
#include "listdhdr.hpp"
#include "listitem.hpp"

DrawHandler::DrawHandler ( unsigned long indentBits )
     :   fIndent( indentBits ),
         fBitmapIndent ( 0 ),
         fMaxCharHeight ( 0 ) ,
         fInternalLeading( 0 ) ,
         fExternalLeading( 0 ) ,
         fCollapseHandle (ISystemBitmapHandle::collapsedTree),
         fExpandHandle (ISystemBitmapHandle::expandedTree),
         fCollapseBitmap(new IGBitmap( fCollapseHandle) ),
         fExpandBitmap( new IGBitmap ( fExpandHandle) )
{
}



DrawHandler::setItemSize   ( IListBoxSizeItemEvent& event )
{
  if(fMaxCharHeight==0)
  {
    IListBox* list = (IListBox*)event.controlWindow();
    IFont font( list );
    fMaxCharHeight = font.maxCharHeight();
    fExternalLeading = font.externalLeading();
    fInternalLeading = font.internalLeading();
    unsigned long itemHeight = fMaxCharHeight+fExternalLeading+fInternalLeading;
    unsigned long bitmapHeight = 16;
    fCollapseBitmap->sizeTo(ISize(bitmapHeight,bitmapHeight));
    fExpandBitmap->sizeTo(ISize(bitmapHeight,bitmapHeight));
    fBitmapIndent = (itemHeight-bitmapHeight)/2;
  }
  event.setItemSize(ISize(0,fMaxCharHeight+fExternalLeading+fInternalLeading));
  return true;
}

// Handle selecting and item.
Boolean DrawHandler::selectItem ( IListBoxDrawItemEvent& event )
{
  // Draw with selection.
  event.setSelectionStateDrawn(true);
  return this->drawListItem( event, true);
}

// Handle deselecting an item.
Boolean DrawHandler::deselectItem ( IListBoxDrawItemEvent& event )
{
  // Draw without selection.
  event.setSelectionStateDrawn(true);
  return this->drawListItem( event, false );
}

// Handle the drawing of the list box items.
Boolean DrawHandler::drawItem ( IListBoxDrawItemEvent& event )
{
  if ( event.isSelected() )
  {
    event.setSelectionStateDrawn(true);
    return this->drawListItem( event, true );
  }
  else
    return this->drawListItem( event, false );


}

// Handle the drawing of the list box items.
Boolean DrawHandler::drawListItem ( IListBoxDrawItemEvent& event,
                                    Boolean selected)
{
  IListBox* list = (IListBox*)event.controlWindow();
  IRectangle rect = event.itemRect();

  // Fill the background.
  IColor
    background         = list->backgroundColor(),
    foreground         = list->foregroundColor(),
    selectedBackground = list->hiliteBackgroundColor(),
    selectedForeground = list->hiliteForegroundColor();

  IGraphicContext graphicContext(list->handle());
  IGraphicBundle bundle(graphicContext);

  if(!selected)
  {
    bundle.setFillColor(background);
    bundle.setPenColor(background);
    bundle.setBackgroundColor(background);
  }
  else
  {
    bundle.setFillColor(selectedBackground);
    bundle.setPenColor(selectedBackground);
    bundle.setBackgroundColor(selectedBackground);
  }
  IGRectangle graphicRectangle(rect);
  graphicRectangle.setGraphicBundle(bundle);
  graphicRectangle.drawOn(graphicContext);


  // Convert the item data from the list box item text.
  ListItem* data =
     (ListItem*)(list->itemText( event.itemId() ).asUnsigned());

  // Determine the indent for the class based on the
  // number of inherited classes.
  if ( data->inheritedClasses() != 0 )
  {
     ISize indentSize( data->inheritedClasses() * (fIndent+1), 0 );
     rect.moveBy( indentSize );
  }

  // Draw a bitmap based on the collapsed flag
  // if the class is not a leaf.
  if (data->children() )
  {
     IGBitmap* currentBitmap;
     if(data->collapsed())
       currentBitmap=fCollapseBitmap;
     else
       currentBitmap=fExpandBitmap;

     currentBitmap->moveTo(rect.minXMinY()+ISize(fBitmapIndent, fBitmapIndent));
     bundle.setPenColor(foreground);
     currentBitmap->setGraphicBundle(bundle);
     currentBitmap->drawOn(graphicContext);
  }


  // Setup the bundle for text
  if(selected)
  {
    bundle.setFillColor(selectedBackground);
    bundle.setPenColor(selectedForeground);
    bundle.setBackgroundColor(selectedBackground);
  }
  else
  {
    bundle.setFillColor(background);
    bundle.setPenColor(foreground);
    bundle.setBackgroundColor(background);
  }

  rect
   .moveBy( ISize(fCollapseBitmap->size().width()+fBitmapIndent + 3, 3) )
   .sizeTo( ISize( rect.size().width(),
                   fMaxCharHeight ));

  // Draw the text.
  IGString graphicString(data->text(), rect.minXMinY()+2);
  graphicString.setGraphicBundle(bundle);
  graphicString.drawOn(graphicContext);

  return true;
}
