//*********************************************************
// Canvas - Lunch Dialog Using IMultiCellCanvas
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//*********************************************************
#include <iapp.hpp>
#include <icheckbx.hpp>
#include <ientryfd.hpp>
#include <iframe.hpp>
#include <igroupbx.hpp>
#include <imcelcv.hpp>
#include <iradiobt.hpp>
#include <istattxt.hpp>
#include <icconst.h>

#include "pushbtns.hpp"      // For MyStandardPushButtons.
#include "mclunch.h"

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
   .setText( ID_LUNCH_TEXT );

  // Create the "Food" group box and its choices.
  IGroupBox
    food( ID_FOOD, &client, &client );
  food
   .setText( ID_FOOD );
  IRadioButton
    hamburger   ( ID_HAMBURGER,    &client, &client ),
    cheeseburger( ID_CHEESEBURGER, &client, &client ),
    hotdog      ( ID_HOTDOG,       &client, &client ),
    pizza       ( ID_PIZZA,        &client, &client );
  hamburger
   .setText      ( ID_HAMBURGER )
   .enableTabStop()
   .enableGroup  ();
  cheeseburger
   .setText( ID_CHEESEBURGER );
  hotdog
   .setText( ID_HOTDOG );
  pizza
   .setText( ID_PIZZA );

  // Create the "Beverage" group box and its radio buttons.
  IGroupBox
    beverage( ID_BEVERAGE, &client, &client );
  beverage
   .setText( ID_BEVERAGE );
  IRadioButton
    milk     ( ID_MILK,      &client, &client ),
    softDrink( ID_SOFTDRINK, &client, &client ),
    juice    ( ID_JUICE,     &client, &client ),
    water    ( ID_WATER,     &client, &client );
  milk
   .setText      ( ID_MILK )
   .enableTabStop()
   .enableGroup  ();
  softDrink
   .setText( ID_SOFTDRINK );
  juice
   .setText( ID_JUICE );
  water
   .setText( ID_WATER );

  // Create the "Side orders" group box and its choices.
  IGroupBox
    sideOrders( ID_SIDEORDERS, &client, &client );
  sideOrders
   .setText( ID_SIDEORDERS );
  IMultiCellCanvas
    checkBoxes ( 1, &client, &client ),
    requestPair( 2, &client, &client );
  ICheckBox
    salad( ID_SALAD, &checkBoxes, &checkBoxes ),
    fries( ID_FRIES, &checkBoxes, &checkBoxes );
  salad
   .setText      ( ID_SALAD )
   .enableTabStop()
   .enableGroup  ();
  fries
   .setText      ( ID_FRIES )
   .enableTabStop()
   .enableGroup  ();
  IStaticText
    requestPrompt( ID_REQUESTPROMPT, &requestPair, &requestPair );
  requestPrompt
   .setAlignment( IStaticText::centerLeft )
   .setText     ( ID_REQUESTPROMPT );
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
    defaultCellSize = IMultiCellCanvas::defaultCell();
  client
   .addToCell( &headingText,   2,  2,  14 )
   .addToCell( &food,          3,  5,  5,  11 )
   .addToCell( &hamburger,     5,  8 )
   .addToCell( &cheeseburger,  5,  10 )
   .addToCell( &hotdog,        5,  12 )
   .addToCell( &pizza,         5,  14 )
   .addToCell( &beverage,      9,  5,  6,  11 )
   .addToCell( &milk,          11, 8 )
   .addToCell( &softDrink,     11, 10 )
   .addToCell( &juice,         11, 12 )
   .addToCell( &water,         11, 14 )
   .addToCell( &sideOrders,    3,  18, 12, 7 )
   .addToCell( &checkBoxes,    5,  21, 8 )
   .addToCell( &requestPair,   5,  23, 8 )
   .addToCell( &pushButtons,   2,  27, 14 );
  client
   .setColumnWidth( 6,  defaultCellSize.width(), true )
   .setColumnWidth( 12, defaultCellSize.width(), true )
   .setColumnWidth( 16, defaultCellSize.width() )
   .setRowHeight  ( 1,  defaultCellSize.height(), true )
   .setRowHeight  ( 3,  defaultCellSize.height(), true )
   .setRowHeight  ( 17, defaultCellSize.height(), true )
   .setRowHeight  ( 25, defaultCellSize.height(), true )
   .setRowHeight  ( 28, defaultCellSize.height(), true );

  checkBoxes
   .addToCell( &salad,         1,  1 )
   .addToCell( &fries,         3,  1 );
  checkBoxes
   .setColumnWidth( 2, defaultCellSize.width(), true )
   .setColumnWidth( 4, defaultCellSize.width(), true );

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
    clientRect( IPoint( 50, 50 ), client.minimumSize() );
  frame
   .setClient( &client )
   .moveSizeToClient( clientRect );

  // Show the dialog now.
  frame
   .setFocus()
   .show();

  IApplication::current().run();
}
