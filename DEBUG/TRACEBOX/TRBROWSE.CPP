//************************************************************
// Problem Determination  - Trace Queue Browser
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <ibase.hpp>
#ifdef IC_WIN
  #ifndef WIN32_LEAN_AND_MEAN
    #define WIN32_LEAN_AND_MEAN
  #endif
  #include <windows.h>
#endif

#include <icmdevt.hpp>
#include <iclipbrd.hpp>
#include <ifont.hpp>
#include <imsgbox.hpp>
#include "trbrowse.hpp"
#include "filtdlg.hpp"
#include "trbrowse.h"

// set of strings to include
FilterSet      fsIncludedSet;

class MyContainerFilter : public IContainerControl::FilterFn {
/**************************************************************************
* Class:   MyContainerFilter                                              *
*                                                                         *
* Purpose: filter out objects not matching fsIncludedSet.                 *
*                                                                         *
**************************************************************************/
public:
/*------------------------ Object Filtering -------------------------------*/
virtual Boolean
  isMemberOf  ( IContainerObject* object,
                IContainerControl* container) const;
};


/*------------------------------------------------------------------------------
| TraceBrowser::TraceBrowser                                                   |
------------------------------------------------------------------------------*/
TraceBrowser::TraceBrowser ( const IString& queueName )
       : IFrameWindow  (WND_MAIN,
                        IFrameWindow::defaultStyle() |
                        IFrameWindow::minimizedIcon),
         queueHandler  (*this),
         commandHandler(*this),
         cnrWin        (IC_FRAME_CLIENT_ID, this, this, IRectangle(),
                        IContainerControl::defaultStyle() |
                        IContainerControl::noSharedObjects ),
         reader        (queueName, this->handle()),
         thread        (),
         menuBar       (WND_MAIN, this),
         fautoScroll   (false),
         fwaitCursor   (false)
{
  // Attach handlers to our frame.
  queueHandler.handleEventsFor(this);
  commandHandler.handleEventsFor(this);

  // Change the font & show text view with extended selection.
  IFont font("Courier", 8);
  container()
    .showTextView()
    .setExtendedSelection()
    .setFont(font);

  // Make the container the client and start the queue
  (*this)
    .setClient(&container())
    .postEvent(START_QUEUE);
}

/*------------------------------------------------------------------------------
| TraceBrowser::enableReader                                                   |
------------------------------------------------------------------------------*/
TraceBrowser&  TraceBrowser::enableReader( Boolean enable )
{
  queueReader().enable( enable );
  if ( queueReader().isEnabled() )
     menuBar.setText(MI_START, STOP_TEXT);
  else
     menuBar.setText(MI_START, START_TEXT);
  return *this;
}

/*------------------------------------------------------------------------------
| IBase::Boolean TraceBrowser::isReaderEnabled                                 |
------------------------------------------------------------------------------*/
IBase::Boolean TraceBrowser::isReaderEnabled( ) const
{
   return ((TraceBrowser*)this)->queueReader().isEnabled() ;
}

/*------------------------------------------------------------------------------
| IBase::Boolean TraceBrowser::isMessageWaiting                                |
------------------------------------------------------------------------------*/
IBase::Boolean TraceBrowser::isMessageWaiting() const
{
   Boolean result = false;
   // Check for any pending messages in the user range
#ifdef __WINDOWS__
   MSG msg;
   result = PeekMessage( &msg,
                         this->handle(),
                         USER_MESSAGE_START, USER_MESSAGE_END,
                         PM_NOREMOVE );
#endif
   return result;
}

/*------------------------------------------------------------------------------
| IBase::Boolean TraceBrowser::setWaitCursor                                   |
------------------------------------------------------------------------------*/
TraceBrowser& TraceBrowser::setWaitCursor( Boolean wait )
{
  if (wait && !fwaitCursor)
    {
    this->setMousePointer( ISystemPointerHandle(
                               ISystemPointerHandle::wait ) );
    fwaitCursor = true;
    }
  else if (!wait && fwaitCursor)
    {
    this->setMousePointer( IPointerHandle( 0 ) );
    fwaitCursor = false;
    }
  return *this;
}

/*------------------------------------------------------------------------------
| TraceBrowser::enableAutoScroll                                               |
------------------------------------------------------------------------------*/
TraceBrowser&  TraceBrowser::enableAutoScroll( Boolean enable )
{
   fautoScroll=enable;
   menuBar.checkItem( MI_AUTOSCROLL, fautoScroll );
   return *this;
}

/*------------------------------------------------------------------------------
| IBase::Boolean TraceCommandHandler::command                                  |
------------------------------------------------------------------------------*/
IBase::Boolean TraceCommandHandler::command ( ICommandEvent& event )
{
   Boolean result = true;
   switch ( event.commandId() )
      {
      //    MI_FILE
      case  MI_EXIT        :
         browserWindow.close();
         break;

      //    MI_SELECTED
      case  MI_CUT         :
      case  MI_COPY        :
         {
         // Empty the clipboard to establish ownership
         IClipboard clipboard(event.window()->handle());
         clipboard.empty();

         // Find the cursored object in the container.
         IContainerControl& container = browserWindow.container();
         IContainerObject* cursoredObject = container.cursoredObject();

         // If the cursored object is selected, loop through all other
         // selected objects and store the objects in our set.
         if (container.isSelected(cursoredObject))
           {
           IString objectsAsText("");
           IContainerControl::ObjectCursor cursor(container,
                                                  IContainerObject::selected);
           for (cursor.setToFirst(); cursor.isValid(); cursor.setToNext())
             {
             IContainerObject* selectedObject = container.objectAt(cursor);
             objectsAsText = objectsAsText +  selectedObject->iconText();
             }

           // Put the data on the clipboard.
           clipboard.setText(objectsAsText);

           // If this is a Cut,  delete selected objects
           if (event.commandId() == MI_CUT)
             {
             container.deleteSelectedObjects();
             }
           }
         else
           {
           // cursored object not selected.  Put the cursored object
           // on clipboard.
           clipboard.setText( cursoredObject->iconText() );

           // If this is a Cut request delete the cursored object.
           if (event.commandId() == MI_CUT)
             {
             container.removeObject(cursoredObject);
             delete cursoredObject;
             }
           }
         }
         break;

      case  MI_CLEAR       :
         {
         browserWindow.postEvent( DELETE_ALL );
         }
         break;

      case  MI_SELECTALL   :
         {
         IContainerControl::ObjectCursor oc( browserWindow.container() );
         for (oc.setToFirst(); oc.isValid(); oc.setToNext())
            {
            browserWindow.container().setSelected( oc.current() );
            }
         }
         break;
      case  MI_DESELECTALL :
         {
         IContainerControl::ObjectCursor oc( browserWindow.container() );
         for (oc.setToFirst(); oc.isValid(); oc.setToNext())
            {
            browserWindow.container().removeSelected( oc.current() );
            }
         }
         break;


      //    MI_VIEW
      case  MI_INCLUDE     :
         {
         // disable tracing
         Boolean wasEnabled = browserWindow.isReaderEnabled();
         if (wasEnabled)
            browserWindow.enableReader( false );
         // filter some objects
         FilterDialog   dialog( fsIncludedSet, &browserWindow );
         dialog.showModally();

         MyContainerFilter filterfn;
         browserWindow.container().filter( filterfn );
         // re-enable tracing
         if (wasEnabled)
            browserWindow.enableReader( true );
         }
         break;

      case  MI_INCLUDEALL  :
         {
         // restore all objects
         browserWindow.container().filter( );
         }
         break;

      case  MI_INPUTFILTER   :
         {
         // disable tracing and lock the filter list
         Boolean wasEnabled = browserWindow.isReaderEnabled();
         if (wasEnabled)
            browserWindow.enableReader( false );
         IResourceLock lock( browserWindow.queueReader().filterLock() );
         // show the dialog
         FilterDialog   dialog( browserWindow.queueReader().inputFilterSet(),
                                &browserWindow );
         dialog.showModally();
         // re-enable tracing.  Lock freed on exit of block.
         if (wasEnabled)
            browserWindow.enableReader( true );
         }
         break;

      case  MI_AUTOSCROLL  :
         // toggle autoscroll
         browserWindow.enableAutoScroll( !browserWindow.isAutoScroll() );
         break;


      //    MI_START
      case  MI_START:
         // Toggle the enabled state of the queue
         browserWindow.enableReader( !browserWindow.isReaderEnabled() );
         break;

      //    MI_HELP
      case  MI_ABOUT       :
         {
         IMessageBox msgbox( &browserWindow );
         msgbox.show( ABOUT_TEXT, IMessageBox::information );
         }
         break;
      default:
         result = false;
      }

   return result;
}

/*------------------------------------------------------------------------------
| TraceBrowserHandler::dispatchHandlerEvent                                    |
------------------------------------------------------------------------------*/
IBase::Boolean  TraceBrowserHandler::dispatchHandlerEvent ( IEvent & event )
{
  switch (event.eventId())
  {
     case ADD_OBJECT:
     {
       browserWindow.container()
         .addObject((IContainerObject*)(void*)event.parameter1());

       if ( !browserWindow.isMessageWaiting() &&
            browserWindow.isAutoScroll() )
          browserWindow.container()
             .scrollToObject((IContainerObject*)(void*)event.parameter1());
       return true;
     }
     case START_QUEUE:
     {
       // Start Reader in a separate thread.
       browserWindow.readerThread()
          .start(new IThreadMemberFn<QueueReader>
                 (browserWindow.queueReader(),
                  QueueReader::run));
       return true;
     }
     case DELETE_ALL :
       // Delete all objects.
       browserWindow.container()
          .setRefreshOff()
          .deleteAllObjects()
          .setRefreshOn()
          .refresh();
       break;

     default:
        break;
  } // endswitch
  return false;
}


/*------------------------------------------------------------------------------
| IBase::Boolean  MyContainerFilter::isMemberOf                                |
------------------------------------------------------------------------------*/
IBase::Boolean  MyContainerFilter::isMemberOf  ( IContainerObject* object,
                                                 IContainerControl* container) const
{
   Boolean result = true;
   FilterSet::Cursor cursor( fsIncludedSet );
   for (cursor.setToFirst(); (result && cursor.isValid()); cursor.setToNext() )
      {
      if ( object->iconText().indexOf( cursor.element() ) )
         result = false;
      }
   return fsIncludedSet.isExcludeList ? result : !result ;
}
