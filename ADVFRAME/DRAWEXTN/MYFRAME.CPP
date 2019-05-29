//************************************************************
// Advanced Frame - Frame Extension Drawing Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <istring.hpp>

#include "myframe.hpp"
#include "myextns.hpp"

static IString
  colorText("white blue red pink green cyan "
            "yellow black darkGray darkBlue darkRed "
            "darkPink darkGreen darkCyan brown paleGray" );

ColorList::ColorList ( IWindow *owner )
    : IListBox( 0, owner, owner )
  {
  for ( int i = 1; i <= colorText.numWords(); i++ )
     addAsLast( colorText.word( i ) );
  }

IColor ColorList:: selectedColor ( ) const
  {
  IString
    selected( itemText( selection() ) );
  return IColor(
     (IColor::Color) (colorText.wordIndexOfPhrase(selected) - 1));
  }

MyFrame::MyFrame ( )
    : IFrameWindow( "Extended Extension Test" ),
      colorList( this ),
      extSize( 1, this, this ),
      instructions( IC_FRAME_CLIENT_ID, this, this ),
      drawButton( 2, this, this ),
      handler( *this )
  {
  instructions.setAlignment( IStaticText::topLeftWrapped );
  instructions.setText( "Select a color and/or\n"
                        "enter a new separator width,\n"
                        "and press Redraw to apply changes" );
  setClient( &instructions );
  drawButton.setText( "Redraw" );
  extSize.setText( "5" );
  colorList.select( 0 );
  addMyExtension( new MyExtension( &drawButton,
                                    belowClient ) );
  addMyExtension( new MyExtension( &colorList,
                                   aboveClient, 0.5 ) );
  addMyExtension( new MyExtension( &extSize,
                                   aboveClient ) );
  update();
  }

IFrameWindow& MyFrame::update ( )
  {
  IFrameExtensions
   *exts = extensions();
  unsigned long
    newWidth = extSize.text().asUnsigned();
  IColor
    newColor = colorList.selectedColor();
  for ( int i = 1; exts && i <= exts->numberOfElements(); i++ )
    {
    MyExtension
     *p = (MyExtension*)( exts->elementAtPosition(i) );
    p -> setSeparatorWidth( newWidth );
    p -> setSeparatorColor( newColor );
    }

  return IFrameWindow::update();
  }

MyFrame &MyFrame :: forceUpdate ( )
  {
  // Resize extension to force update.
  if ( this->isAnExtension( &drawButton ) )
    useExtensionMinimumSize( &drawButton );
  this -> update();
  return *this;
  }

MyFrame&  MyFrame::addMyExtension( MyExtension *pExt )
  {
  // Get frame extensions.
  IFrameExtensions
   *exts = this->extensions();

  // If no previous extensions, allocate collection.
  if ( !exts )
    this->setExtensions( exts = new IFrameExtensions );

  // Add argument extension to collection.
  exts -> addAsLast( pExt );

  // Update the frame.
  forceUpdate();
  return *this;
  }

MyHandler :: MyHandler ( MyFrame &frame )
  : frame( frame )
  {
  handleEventsFor( &frame );
  }

Boolean MyHandler :: command ( ICommandEvent &event )
  {
  frame.forceUpdate().refresh();
  return true;
  }
