//************************************************************
// Static Controls - Static Text on a Canvas
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <ifont.hpp>
#include <iframe.hpp>
#include <iapp.hpp>
#include <imcelcv.hpp>
#include <iradiobt.hpp>
#include <iselhdr.hpp>
#include <istattxt.hpp>
#include <istring.hpp>
#include <icconst.h>

// Objects of this class support writing their text across
// multiple lines when they are made a child window of a 
// multicell or set canvas.  The text is wrapped to fit in a 
// percentage of the parent window's width. Because this class
// relies on the function IFont::texLines, it does not support
// double-byte characters.
class MultiLineStaticText : public IStaticText {
public:
  MultiLineStaticText ( unsigned long id,
                        IWindow* parent,
                        IWindow* owner,
                        IStaticText::Style style =
                          IStaticText::defaultStyle() )
    : IStaticText( id, parent, owner, IRectangle(), style ),
      parentFraction( 0.5 )
  { 
    this->disableMinimumSizeCaching();
    this->setAlignment( IStaticText::topLeftWrapped ); 
  }
virtual MultiLineStaticText
 &setFraction         ( double fraction )
  {
    parentFraction = (fraction > 1) ? 1 : fraction;
    return *this;
  }
virtual double
  fraction            ( ) const
  { return parentFraction; }
protected:
virtual ISize
  calcMinimumSize     ( ) const
  {
    unsigned long recommendedWidth =
      (unsigned long)(this->parent()->size().width() * this->fraction());

    // Get the current font information to see what size the 
    // text needs to be.
    IFont font( this ); 
    unsigned long minWidth = font.minTextWidth( this->text() );

    // At least show the longest word.
    if (recommendedWidth < minWidth)
       recommendedWidth = minWidth;

    unsigned long lines =
       font.textLines( this->text(), recommendedWidth );

    return ISize( recommendedWidth,
                  lines * font.maxCharHeight() );
  }
private:
double
  parentFraction;
MultiLineStaticText ( const MultiLineStaticText&);
MultiLineStaticText& operator= ( const MultiLineStaticText&);
};

// This class is used to dynamically change the text of a
// static text control to help illustrate the benefits of
// using the IStaticText::setLimit function.
class HumptyDumptySelectHandler : public ISelectHandler {
public:
  HumptyDumptySelectHandler ( IStaticText* outputArea )
  { output = outputArea; }
protected:
virtual Boolean
  selected      ( IControlEvent& event )
  {
    char* text = " ";
    switch ( event.controlWindow()->id() )
    {
       case 1:
         text = "Humpty Dumpty sat on a wall.";
         break;
       case 2:
         text = "Humpty Dumpty had a great fall.";
         break;
       case 3:
         text = "All the King's horses and all the King's men,";
         break;
       case 4:
         text = "Couldn't put Humpty together again.";
         break;
       default:
         break;
    }
    if (output)
    {
       output->setText( text );
    }
    return false;
  }
private:
IStaticText
 *output;
};

void main ( )
{
  IFrameWindow frame( "Static Text and Canvas Example" );
  IMultiCellCanvas client( IC_FRAME_CLIENT_ID, &frame, &frame );
  frame.setClient( &client );

  // Create child windows.
  IStaticText
    output   ( 10, &client, &client ),
    separator( 11, &client, &client );
  output.setLimit( 45 );
  separator
   .setFillColor( IColor::black )
   .setMinimumSize( ISize( 10, 2 ) );

  IMultiCellCanvas
    headings( 14, &client, &client );
  MultiLineStaticText
    heading1( 12, &headings, &headings ),
    heading2( 13, &headings, &headings );
  heading1
   .setFraction( 0.4 )
   .setText( "Select a radio button from the group below." );
  heading2
   .setFraction( 0.4 )
   .setText( "This text consists of several words and may"
               + IString( " wrap across several lines." ));

  headings
   .addToCell( &heading1,  1, 1 )
   .addToCell( &heading2,  3, 1 );
  headings
   .setColumnWidth( 1, 10, true )
   .setColumnWidth( 2, 10, true )
   .setColumnWidth( 3, 10, true );

  IRadioButton
    none  ( 0, &client, &client ),
    first ( 1, &client, &client ),
    second( 2, &client, &client ),
    third ( 3, &client, &client ),
    fourth( 4, &client, &client );
  none
   .setText( "None" )
   .enableTabStop()
   .enableGroup();
  first.setText( "First" );
  second.setText( "Second" );
  third.setText( "Third" );
  fourth.setText( "Fourth" );

  client
   .addToCell( &headings,  2, 2, 2 )
   .addToCell( &none,      2, 4 )
   .addToCell( &first,     2, 6 )
   .addToCell( &second,    2, 8 )
   .addToCell( &third,     2, 10 )
   .addToCell( &fourth,    2, 12 )
   .addToCell( &separator, 2, 14, 2 )
   .addToCell( &output,    2, 15, 2 );
  client
   .setColumnWidth( 3, 0, true )
   .setColumnWidth( 4,
                    IMultiCellCanvas::defaultCell().width() );

  unsigned long defaultHeight =
                  IMultiCellCanvas::defaultCell().height();
  client
   .setRowHeight( 1,  defaultHeight, true )
   .setRowHeight( 3,  defaultHeight, true )
   .setRowHeight( 13, defaultHeight, true )
   .setRowHeight( 16, defaultHeight, true );

  HumptyDumptySelectHandler selHdr( &output );
  selHdr.handleEventsFor( &client );

  // Size and show the window now.
  frame
   .moveSizeToClient( IRectangle( IPoint( 50, 50 ),
                                  client.minimumSize() ))
   .setFocus()
   .show();

  IApplication::current().run();
}
