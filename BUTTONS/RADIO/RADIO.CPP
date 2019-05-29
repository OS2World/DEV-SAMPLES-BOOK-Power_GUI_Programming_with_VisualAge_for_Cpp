//************************************************************
// Button Controls - Radio Button Select Handler                 
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <iframe.hpp>
#include <iradiobt.hpp>
#include <imcelcv.hpp>
#include <istattxt.hpp>
#include <icombobx.hpp>
#include <ipushbut.hpp>
#include <isetcv.hpp>
#include <iapp.hpp>
#include <iselhdr.hpp>
#include <icconst.h>
#include "radio.h"

// Declare the radio button select handler
class SelectHandler : public ISelectHandler
{
public:
  SelectHandler ( ISetCanvas& canvas)
      : _canvas(canvas)  {}

protected:
virtual Boolean
  selected   ( IControlEvent& event );

private:
ISetCanvas
 &_canvas;
SelectHandler& operator=(const SelectHandler&);
};

void main()
{
IFrameWindow
  frame ("Radio Button Select Handler Example");
IMultiCellCanvas 
  client(IC_FRAME_CLIENT_ID, &frame, &frame);

// Set 1 for radio buttons; set 2 for bitmap name.
ISetCanvas 
  set1(ID_SET1, &client, &client),
  set2(ID_SET2, &client, &client);

// Add the set 1 buttons
IRadioButton
  image(ID_IMAGE, &set1, &set1),
  color(ID_COLOR, &set1, &set1);
IPushButton
  changeColor(ID_CHANGECOLOR, &set1, &set2);

set1.setText("Background type");
set2.setText("Image");

// Add text to the buttons.  Note that
// mnemonics are platform-sensitive.
#ifdef IC_PM
  image.setText("~Image");
  color.setText("C~olor");
  changeColor.setText("C~hange Color...");
#else
  image.setText("&Image");
  color.setText("C&olor");
  changeColor.setText("C&hange Color...");
#endif

// Add the set 2 text and combination box.
IStaticText
  fileLeader (ID_FILESTATIC, &set2, &set2);
IComboBox
  fileName   (ID_FILENAME, &set2, &set2, IRectangle(0,0,0,0),
              IComboBox::dropDownType | IWindow::visible);

fileLeader.setText("File:");
fileName.setText("os2.bmp");

// Enable tab stops.
image.enableTabStop();
fileName.enableTabStop();

// Select the color choice.
image.select();

// Add the sets to the client canvas.
client
 .addToCell(&set1, 2, 2)
 .addToCell(&set2, 2, 3);

// Allow for some growth in the canvas.
client
 .setRowHeight   (4, 10, true);

// Create and add select handler.
SelectHandler selectHandler(set2);
selectHandler.handleEventsFor(&set1);

// Put the canvas in the client and show the application.
frame
  .setClient(&client)
  .setFocus()
  .show();

IApplication::current().run();
}

IBase::Boolean SelectHandler::selected ( IControlEvent& event )
{

   switch(event.controlId())
   {
     case ID_IMAGE :
     case ID_COLOR :
     {
        // Test to see if we should enable or disable
        Boolean enable =  (event.controlId() == ID_IMAGE);

        // If image button is selected, Enable the canvas and  
        // its children; otherwise, disable the canvas and its 
        // children.  Although disabling the canvas disables
        // the children, they don't look disabled unless 
        // we explicitly disable them.
        IRadioButton* button = 
                       (IRadioButton*)event.controlWindow();
        if (button && button->isSelected())
        {
          _canvas.enable(enable);
          IWindow::ChildCursor cursor(_canvas);
          for(cursor.setToFirst(); 
              cursor.isValid(); 
              cursor.setToNext())
          {
             IWindow* child = IWindow::windowWithHandle(
                               _canvas.childAt(cursor));
             child->enable(enable);
          }
        }
        break;
     }
   }
   return false;
}
