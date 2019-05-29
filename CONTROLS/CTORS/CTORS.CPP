//************************************************************
// Controls - Constructor and color example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <iapp.hpp>
#include <icolor.hpp>
#include <icombobx.hpp>
#include <ientryfd.hpp>
#include <iframe.hpp>
#include <ihandle.hpp>
#include <imcelcv.hpp>
#include <ispintxt.hpp>
#include <istattxt.hpp>
#include <icconst.h>

#ifdef IC_PM
  #define ID_COMBOBOX_EF  0x029B  // CBID_EDIT from pmwin.h.
#else // IC_WIN
  #define ID_COMBOBOX_EF  0x03E9
#endif

void main ( )
{
  // Create a frame window with a spin button and combo
  // box on a multicell canvas client window.
  IFrameWindow
    frame( "Control Constructor and Color Example" );
  IMultiCellCanvas
    client( IC_FRAME_CLIENT_ID, &frame, &frame );

  // Set up the spin button and its text label.
  IStaticText
    spinText( 100, &client, &client );
  spinText
   .setAlignment( IStaticText::centerLeft )
   .setText( "Spin button with a cyan entry field" );

  ITextSpinButton
    spin( 110, &client, &client, IRectangle(),
          ITextSpinButton::classDefaultStyle
           | IControl::tabStop
           | IControl::group );
  spin
   .addAsFirst( "First entry" )
   .addAsLast( "Second entry" )
   .addAsLast( "Third entry" );

  // Set up the combo box and its text label.
  IStaticText
    comboText( 200, &client, &client );
  comboText
   .setAlignment( IStaticText::centerLeft )
   .setText( "Combo box with an orange entry field" );

  IComboBox
    combo( 210, &client, &client, IRectangle(),
           ( IComboBox::classDefaultStyle
               & ~IComboBox::simpleType )
             | IComboBox::dropDownType
             | IControl::tabStop
             | IControl::group );
  combo
   .addAsFirst( "First entry" );
  combo
   .addAsLast ( "Second entry" );
  combo
   .addAsLast ( "Third entry" );

  // Construct an IEntryField for the existing window, the
  // child window of the spin button.  Find it based on its
  // window identifier after first checking for an existing
  // IWindow object.
  IEntryField
   *spinEF = (IEntryField*)
                IWindow::windowWithParent( spin.id(), &spin );
  if ( ! spinEF )
  {  // No existing window object.
     // Construct a new one.
     spinEF = new IEntryField( spin.id(), &spin );
     spinEF->setAutoDeleteObject( true );
  }

  if ( spinEF )
  {  // Now change its background color.
     // Note: For a window to retain a color change on the
     // Windows operating system, Open Class Library requires
     // that an IWindow object exist for the window for as long
     // as the color change is needed.  As a result, we keep
     // the IEntryField wrapper until the edit control is
     // destroyed.  We let Open Class Library manage the
     // deletion of the IEntryField* for us.
     // For the OS/2 operating system, we could simply delete
     // the IEntryField* immediately after changing the edit
     // control's color.
     spinEF->setBackgroundColor( IColor::cyan );
  }

  // Construct an IEntryField for the existing window, the
  // child entry field of the combo box.  Find it based on its
  // window handle after first checking for an existing
  // IWindow object.
  IEntryField
   *comboEF = 0;
  IWindowHandle comboEFHwnd =
    IWindow::handleWithParent( ID_COMBOBOX_EF, combo.handle() );
  if ( comboEFHwnd )
  {
     // Note: In the Windows operating system, CBS_DROPDOWNLIST
     // type combo boxes do not have a child entry field.
     comboEF = (IEntryField*)
                  IWindow::windowWithHandle( comboEFHwnd );
     if ( ! comboEF )
     {  // No existing window object.
        // Construct a new one.
        comboEF = new IEntryField( comboEFHwnd );
        comboEF->setAutoDeleteObject( true );
     }
  }                // Else use the existing window object.

  if ( comboEF )
  {  // Now change its background color.
     // Note: For a window to retain a color change on the
     // Windows operating system, Open Class Library requires
     // that an IWindow object exist for the window for as long
     // as the color change is needed.  As a result, we keep
     // the IEntryField wrapper until the edit control is
     // destroyed.  We let Open Class Library manage the
     // deletion of the IEntryField* for us.
     // For the OS/2 operating system, we could simply delete
     // the IEntryField* immediately after changing the edit
     // control's color.
     comboEF->setBackgroundColor( IColor( 255, 127, 0 ) );
  }

  // Finish building the window and show it.
  client
   .addToCell( &spinText,  2, 2 )
   .addToCell( &spin,      4, 2 )
   .addToCell( &comboText, 2, 4 )
   .addToCell( &combo,     4, 4 )
   .setColumnWidth( 5, IMultiCellCanvas::defaultCell().width() )
   .setRowHeight( 5, IMultiCellCanvas::defaultCell().height() );
  frame
   .setClient( &client )
   .moveSizeToClient( IRectangle( IPoint( 50, 100 ),
                                  client.minimumSize() ) )
   .setFocus()
   .show();

  // Start event processing.
  IApplication::current().run();
}
