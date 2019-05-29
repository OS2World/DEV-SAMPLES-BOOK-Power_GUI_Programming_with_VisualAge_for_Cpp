//*********************************************************
// Canvas - Lunch Dialog Using ISetCanvas
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//*********************************************************
#include <iapp.hpp>
#include <icheckbx.hpp>
#include <ientryfd.hpp>
#include <iframe.hpp>
#include <iradiobt.hpp>
#include <isetcv.hpp>
#include <istattxt.hpp>
#include <icconst.h>

#include "pushbtns.hpp"      // For MyStandardPushButtons.
#include "setlunch.h"

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
  ISetCanvas
    client( IC_FRAME_CLIENT_ID, &frame, &frame );
  client
   .setDeckOrientation( ISetCanvas::vertical );

  // Create the heading text.
  IStaticText
    headingText( ID_LUNCH_TEXT, &client, &client );
  headingText
   .setText( ID_LUNCH_TEXT );

  // Create canvases for additional formatting and the
  // "Food" group box and its choices.
  ISetCanvas
    choices( 1, &client, &client ),
    columns( 2, &choices, &choices ),
    food   ( ID_FOOD, &columns, &columns );
  choices
   .setDeckOrientation( ISetCanvas::vertical )
   .setPackType       ( ISetCanvas::even );
  columns
   .setMargin  ( ISize() )
   .setPackType( ISetCanvas::expanded );
  food
   .setDeckOrientation( ISetCanvas::vertical )
   .setText           ( ID_FOOD );

  // Create the "Food" radio buttons.
  IRadioButton
    hamburger   ( ID_HAMBURGER,    &food, &food ),
    cheeseburger( ID_CHEESEBURGER, &food, &food ),
    hotdog      ( ID_HOTDOG,       &food, &food ),
    pizza       ( ID_PIZZA,        &food, &food );
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
  ISetCanvas
    beverage( ID_BEVERAGE, &columns, &columns );
  beverage
   .setDeckOrientation( ISetCanvas::vertical )
   .setText           ( ID_BEVERAGE );
  IRadioButton
    milk     ( ID_MILK,      &beverage, &beverage ),
    softDrink( ID_SOFTDRINK, &beverage, &beverage ),
    juice    ( ID_JUICE,     &beverage, &beverage ),
    water    ( ID_WATER,     &beverage, &beverage );
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
  ISetCanvas
    sideOrders( ID_SIDEORDERS, &choices, &choices );
  sideOrders
   .setDeckCount( 2 )
   .setAlignment( ISetCanvas::centerCenter )
   .setText     ( ID_SIDEORDERS );
  ICheckBox
    salad( ID_SALAD, &sideOrders, &sideOrders ),
    fries( ID_FRIES, &sideOrders, &sideOrders );
  salad
   .setText      ( ID_SALAD )
   .enableTabStop()
   .enableGroup  ();
  fries
   .setText      ( ID_FRIES )
   .enableTabStop()
   .enableGroup  ();
  IStaticText
    requestPrompt( ID_REQUESTPROMPT, &sideOrders, &sideOrders );
  requestPrompt
   .setText( ID_REQUESTPROMPT );
  IEntryField
    request(ID_REQUEST, &sideOrders, &sideOrders );
  request
   .enableTabStop()
   .enableGroup();

  // Create the push buttons.
  MyStandardPushButtons
    pushButtons( 4, &client );

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
