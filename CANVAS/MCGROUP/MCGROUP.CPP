//*********************************************************
// Canvas - IMultiCellCanvas with Smarter Group Boxes
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//*********************************************************
#include <iapp.hpp>
#include <icheckbx.hpp>
#include <ientryfd.hpp>
#include <iframe.hpp>
#include <imcelcv.hpp>
#include <iradiobt.hpp>
#include <istattxt.hpp>
#include <icconst.h>

#include "mcgroup.hpp"       // For GroupBoxForMultiCell.
#include "pushbtns.hpp"      // For MyStandardPushButtons.
#include "mcgroup.h"

void main ( )
{
  IFrameWindow
    frame( "Lunch",
           ID_LUNCH_DIALOG,
           IFrameWindow::classDefaultStyle
             & ~IFrameWindow::maximizeButton
             & ~IFrameWindow::minimizeButton
             | IFrameWindow::dialogBackground );

  // Create the client window.
  IMultiCellCanvas
    client( IC_FRAME_CLIENT_ID, &frame, &frame );

  // Create the heading text.
  IStaticText
    headingText( ID_LUNCH_TEXT, &client, &client );
  headingText
   .setText( "Select your lunch preferences:" );

  // Create the "Food" group box and its choices.
  GroupBoxForMultiCell
    food( ID_FOOD, &client );
  food
   .setText( "Food" );
  IRadioButton
    hamburger   ( ID_HAMBURGER,    &client, &client ),
    cheeseburger( ID_CHEESEBURGER, &client, &client ),
    hotdog      ( ID_HOTDOG,       &client, &client ),
    pizza       ( ID_PIZZA,        &client, &client );
  hamburger
#ifdef IC_PM
   .setText      ( "~Hamburger" )
#else
   .setText      ( "&Hamburger" )
#endif
   .enableTabStop()
   .enableGroup  ();
#ifdef IC_PM
  cheeseburger.setText( "~Cheeseburger" );
  hotdog.setText( "Hot ~dog" );
  pizza.setText( "~Pizza" );
#else
  cheeseburger.setText( "&Cheeseburger" );
  hotdog.setText( "Hot &dog" );
  pizza.setText( "&Pizza" );
#endif

  // Create the "Beverage" group box and its radio buttons.
  GroupBoxForMultiCell
    beverage( ID_BEVERAGE, &client );
  beverage
   .setText( "Beverage" );
  IRadioButton
    milk     ( ID_MILK,      &client, &client ),
    softDrink( ID_SOFTDRINK, &client, &client ),
    juice    ( ID_JUICE,     &client, &client ),
    water    ( ID_WATER,     &client, &client );
  milk
#ifdef IC_PM
   .setText      ( "~Milk" )
#else
   .setText      ( "&Milk" )
#endif
   .enableTabStop()
   .enableGroup  ();
#ifdef IC_PM
  softDrink
   .setText( "~Soft drink" );
  juice
   .setText( "~Juice" );
  water
   .setText( "~Water" );
#else
  softDrink
   .setText( "&Soft drink" );
  juice
   .setText( "&Juice" );
  water
   .setText( "&Water" );
#endif

  // Create the "Side orders" group box and its choices.
  GroupBoxForMultiCell
    sideOrders( ID_SIDEORDERS, &client );
  sideOrders
   .setText( "Side orders" );
  IMultiCellCanvas
    checkBoxes ( 1, &client, &client ),
    requestPair( 2, &client, &client );
  ICheckBox
    salad( ID_SALAD, &checkBoxes, &checkBoxes ),
    fries( ID_FRIES, &checkBoxes, &checkBoxes );
  salad
#ifdef IC_PM
   .setText      ( "Sa~lad" )
#else
   .setText      ( "Sa&lad" )
#endif
   .enableTabStop()
   .enableGroup  ();
  fries
#ifdef IC_PM
   .setText      ( "~French fries" )
#else
   .setText      ( "&French fries" )
#endif
   .enableTabStop()
   .enableGroup  ();
  IStaticText
    requestPrompt( ID_REQUESTPROMPT,
                   &requestPair, &requestPair );
  requestPrompt
   .setAlignment( IStaticText::centerLeft )
   .setText( "Other" );
  IEntryField
    request(ID_REQUEST, &requestPair, &requestPair );
  request
   .enableTabStop()
   .enableGroup();

  // Create the push buttons.
  MyStandardPushButtons
    pushButtons( 4, &client );

  // Position and size child windows of the multicell canvases
  // by assigning them to cells.
  ISize
    defaultCell = IMultiCellCanvas::defaultCell();
  client
   .addToCell( &headingText,   2,  2,  14 )
   .addToCell( &food,          3,  5,  5,  10 )
   .addToCell( &hamburger,     5,  7 )
   .addToCell( &cheeseburger,  5,  9 )
   .addToCell( &hotdog,        5,  11 )
   .addToCell( &pizza,         5,  13 )
   .addToCell( &beverage,      9,  5,  6,  10 )
   .addToCell( &milk,          11, 7 )
   .addToCell( &softDrink,     11, 9 )
   .addToCell( &juice,         11, 11 )
   .addToCell( &water,         11, 13 )
   .addToCell( &sideOrders,    3,  17, 12, 6 )
   .addToCell( &checkBoxes,    5,  19, 8 )
   .addToCell( &requestPair,   5,  21, 8 )
   .addToCell( &pushButtons,   2,  25, 14 );
  client
   .setColumnWidth( 6,  defaultCell.width(), true )
   .setColumnWidth( 12, defaultCell.width(), true )
   .setColumnWidth( 16, defaultCell.width() )
   .setRowHeight  ( 1,  defaultCell.height(), true )
   .setRowHeight  ( 3,  defaultCell.height(), true )
   .setRowHeight  ( 16, defaultCell.height(), true )
   .setRowHeight  ( 23, defaultCell.height(), true )
   .setRowHeight  ( 26, defaultCell.height(), true );

  // Tell GroupBoxForMultiCell objects where they are positioned
  // in the multicell canvas.
  food
   .setMultiCellRow( 5 );
  beverage
   .setMultiCellRow( 5 );
  sideOrders
   .setMultiCellRow( 17 );

  checkBoxes
   .addToCell( &salad,         1,  1 )
   .addToCell( &fries,         3,  1 );
  checkBoxes
   .setColumnWidth( 2, defaultCell.width(), true )
   .setColumnWidth( 4, defaultCell.width(), true );

  requestPair
   .addToCell( &requestPrompt, 1,  1 )
   .addToCell( &request,       3,  1 );
  requestPair
   .setColumnWidth( 3, 0, true );

  // Select the default choices.
  hamburger
   .select();
  milk
   .select();

  // Size and position the frame window.
  IRectangle
    clientRect( IPoint( 50, 50 ),
                client.minimumSize() );
  frame
   .setClient( &client )
   .moveSizeToClient( clientRect );

  // Show the dialog now.
  frame
   .setFocus()
   .show();

  IApplication::current().run();
}
