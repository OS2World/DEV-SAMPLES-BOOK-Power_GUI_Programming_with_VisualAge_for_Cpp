//************************************************************
// Menus - Custom Drawing Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <iframe.hpp>
#include <istattxt.hpp>
#include <iapp.hpp>
#include <ifont.hpp>
#include <imenubar.hpp>
#include <imnitem.hpp>
#include <imndihdr.hpp>
#include <icmdhdr.hpp>
#include <irect.hpp>
#include <istring.hpp>
#include <igrafctx.hpp>
#include <igstring.hpp>
#include "drawmenu.h"

// Menu handler to capture Draw Item requests.
class MenuDrawHandler : public IMenuDrawItemHandler
{
public:
  MenuDrawHandler ()
      : font("Tms Rmn", 24) {}

protected:
virtual Boolean
  setSize       ( IMenuDrawItemEvent& event,
                  ISize&              newSize ),
  draw          ( IMenuDrawItemEvent& event,
                  DrawFlag&           flag ),
  highlight     ( IMenuDrawItemEvent& event ),
  unhighlight   ( IMenuDrawItemEvent& event ),
  drawText      ( IMenuDrawItemEvent& event,
                  Boolean             highlight );

private:
IFont
  font;
};

// Command handler to capture menu commands.
class CommandHandler : public ICommandHandler
{
public:
  CommandHandler ( IStaticText& status)
            : aStatus(status)  {}

protected:
virtual Boolean
  command    ( ICommandEvent& event );

private:
IStaticText
 &aStatus;
CommandHandler& operator=(const CommandHandler&);
};

void main()
{
IFrameWindow
  frame ("Custom Menu Drawing Example");

// Add the Menubar from a resource file.
IMenuBar
  menuBar(MAIN_MENU, &frame);
#ifdef IC_WIN
menuBar.setBitmap(MI_BITMAP, MI_BITMAP);
#endif

// Change a menu item to the drawItem style.
IMenuItem drawItem = menuBar.menuItem(MI_DRAWITEM);
drawItem.setDrawItem();
menuBar.setItem(drawItem);

// Create a status area in the client and a
// command handler to write in it.  Add the
// command handler to the frame to handle
// menu commands.
IStaticText
  statusArea(ID_STATUS, &frame, &frame);
CommandHandler
  commandHandler(statusArea);
commandHandler
  .handleEventsFor(&frame);

// Add a MenuDrawHandler to the frame
MenuDrawHandler
  drawHandler;
drawHandler
  .handleEventsFor(&frame);

// Set the focus and show the app
frame
  .setClient(&statusArea)
  .setFocus()
  .show();
IApplication::current().run();
}


IBase::Boolean MenuDrawHandler::setSize(IMenuDrawItemEvent& event,
                                        ISize& newSize)
{
  // Since we don't know the text contents, default menu item width large
  // enough for 5 Ws and height to character height plus side padding
  newSize.setWidth( font.textWidth("WWWWW") )
         .setHeight(font.maxCharHeight()+5);
  return true;
}

IBase::Boolean MenuDrawHandler::highlight(IMenuDrawItemEvent& event)
{
  return drawText(event,true);
}

IBase::Boolean MenuDrawHandler::unhighlight(IMenuDrawItemEvent& event)
{
  return drawText(event,false);
}

IBase::Boolean MenuDrawHandler::draw(IMenuDrawItemEvent& event,
                                     DrawFlag& flag)
{
  return drawText(event,false);
}

IBase::Boolean MenuDrawHandler::drawText(IMenuDrawItemEvent& event,
                                         Boolean             highlight )
{
  // This routine assumes that all drawing is for text items whose
  // text is contained in a STRINGTABLE resource with an id the
  // same as the item id.
  IString str = IApplication::current().userResourceLibrary()
                   .loadString(event.itemId());
  str = " "+str;    // Add pad to left of item text

  // Get the point to draw at and wrapper the graphic context for drawing use
  IPoint point( event.itemRect().minXMinY() );
  point.setY(point.y() + 2);                         // Vertically center
  IGraphicContext gc(event.itemPresSpaceHandle());

  // If we should highlight this, change color to red
  if (highlight)
    gc.setPenColor( IColor::red );

  // otherwise use default menu text color
  else
    gc.setPenColor(IGUIColor(IGUIColor::menuText));

  // Create a graphic string, starting at point with text and font desired
  IGString text( str, point, font );
  text.drawOn(gc);

  return true;
}


IBase::Boolean CommandHandler::command( ICommandEvent& event )
{
  switch(event.commandId())
  {
    default:
    {
      try {
       aStatus.setText(event.commandId());
      } catch (...) {}
      return true;
    }
  }
}

