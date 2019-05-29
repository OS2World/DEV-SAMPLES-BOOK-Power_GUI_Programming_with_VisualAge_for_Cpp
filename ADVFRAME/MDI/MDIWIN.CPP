//************************************************************
// Advanced Frame - MDI Frame Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <windows.h>
#include <icmdhdr.hpp>
#include <icoordsy.hpp>
#include <iexcept.hpp>
#include <imenubar.hpp>
#include <isysmenu.hpp>
#include <ithread.hpp>
#include "mdiwin.hpp"

class CmdHandler : public ICommandHandler {
public:
  CmdHandler();
virtual Boolean
  systemCommand ( ICommandEvent& event );
static CmdHandler
  *defaultHandler();
private:
 static CmdHandler
   *defaultHdr;
};

CmdHandler* CmdHandler::defaultHdr = 0;

CmdHandler::CmdHandler()
  : ICommandHandler()
{ }

IBase::Boolean CmdHandler::systemCommand( ICommandEvent& event )
{
  Boolean handled = false;
  if ((event.commandId() & 0xFFF0 ) == SC_CLOSE )
    {
    MDIWindow* mdichild = (MDIWindow*)event.window();
    if (mdichild)
      {
      mdichild->close();
      handled = true;
      }
    }
  return handled;
}

CmdHandler* CmdHandler::defaultHandler( )
{
  if (!CmdHandler::defaultHdr)
    CmdHandler::defaultHdr = new CmdHandler;
  return CmdHandler::defaultHdr;
}

MDIWindow::MDIWindow( const IResourceId&         resId,
                      IWindow*                   parent ,
                      IWindow*                   owner ,
                      unsigned long              windowMenuId,
                      unsigned long              childMenuId,
                      const IRectangle&          initRect,
                      const IFrameWindow::Style& style,
                      const char*                title  ) :
  IFrameWindow ( IFrameWindow::deferCreation ),
  fclient      ( 0 ),
  fchildId     ( childMenuId )
{
   // Use MDIWindow::initialize instead of the one in IFrameWindow.
   this->initialize( resId, style, parent,
                     owner, initRect, title );

   // Create the MDI client window.
   IMenuBar menu( this, IMenuBar::wrapper );
   CLIENTCREATESTRUCT ccs;
   ccs.hWindowMenu = menu.menuItem( windowMenuId ).submenuHandle();
   ccs.idFirstChild = (unsigned int)fchildId;
   IWindowHandle hwnd =
     IWindow::create( IC_FRAME_CLIENT_ID,
                      0,
                      WS_CHILD | WS_CLIPCHILDREN | WS_VSCROLL |
                      WS_HSCROLL | WS_VISIBLE ,
                      "MDICLIENT",
                      this->handle(),
                      this->handle(),
                      IRectangle(0,0,0,0),
                      &ccs,
                      0,
                      defaultOrdering(),
                      0 );
   fclient = new IWindow( hwnd );
   fclient->setAutoDeleteObject( true );
}

MDIWindow::MDIWindow( const IResourceId&         resId,
                      MDIWindow*                 parent,
                      const IRectangle&          initRect,
                      const IFrameWindow::Style& style,
                      const char*                title) :
  IFrameWindow ( IFrameWindow::deferCreation ),
  fclient  ( 0 ),
  fchildId ( 0 )
{
   IASSERTPARM( (parent != 0) && (parent->client() != 0) );
   // Use MDIWindow::initialize instead of the one in IFrameWindow.
   this->initialize( resId, style, parent->client(),
                     parent->client(), initRect, title );
   CmdHandler::defaultHandler()->handleEventsFor( this );
}

MDIWindow& MDIWindow::setClient    ( IWindow* newClient )
{
  if (fclient == 0)
     IFrameWindow::setClient( newClient );
  return *this;
}

MDIWindow &MDIWindow::close ( )
  {
  IWindow* mdiClient = fclient ? 0 : this->parent();
  if (mdiClient)
     mdiClient->sendEvent( WM_MDIDESTROY,
                           IEventParameter1(this->handle()) );
  else
     IFrameWindow::close();
  return *this;
  }

MDIWindow &MDIWindow::maximize ( )
{
  IWindow* mdiClient = fclient ? 0 : this->parent();
  // Ignore the request if there is no maximize button.
  if ((this->style() & WS_MAXIMIZEBOX ) && (mdiClient) )
     mdiClient->sendEvent( WM_MDIMAXIMIZE,
                           IEventParameter1(this->handle()) );
  else
     IFrameWindow::maximize();
  return *this;
}

MDIWindow &MDIWindow::restore ( )
{
  IWindow* mdiClient = fclient ? 0 : this->parent();
  if (mdiClient)
     mdiClient->sendEvent( WM_MDIRESTORE,
                           IEventParameter1(this->handle()) );
  else
     IFrameWindow::restore();
  return *this;
}

// This function returns the active MDI child or 0 if there
// is none.
MDIWindow*  MDIWindow::activeChild( ) const
{
  MDIWindow* child = 0;
  if (fclient)
    child = (MDIWindow*) IWindow::windowWithHandle(
                (HANDLE)fclient->sendEvent( WM_MDIGETACTIVE ));
  return child;
}

MDIWindow&  MDIWindow::activateChild( unsigned long childId )
{
  if ((childId >= fchildId) && (fclient))
     {
     IWindow* child =
        IWindow::windowWithParent( childId, fclient );
     if (child)
        fclient->sendEvent( WM_MDIACTIVATE,
                            IEventParameter1(child->handle()) );
     }
  return *this;
}

MDIWindow&  MDIWindow::arrange        ( )
{
  IWindow* mdiClient = fclient ? fclient : this->parent();
  if (mdiClient)
     mdiClient->sendEvent( WM_MDIICONARRANGE );
  return *this;
}

MDIWindow&  MDIWindow::cascade        ( )
{
  IWindow* mdiClient = fclient ? fclient : this->parent();
  if (mdiClient)
     mdiClient->sendEvent( WM_MDICASCADE );
  return *this;
}

MDIWindow&  MDIWindow::tile           ( Boolean horizontal )
{
  IWindow* mdiClient = fclient ? fclient : this->parent();
  if (mdiClient)
     mdiClient->sendEvent( WM_MDITILE,
                           horizontal ? MDITILE_HORIZONTAL :
                                        MDITILE_VERTICAL);
  return *this;
}

MDIWindow& MDIWindow::initialize ( const IResourceId &resId,
                                 const Style       &style,
                                 IWindow           *parent,
                                 IWindow           *owner,
                                 const IRectangle  &initRect,
                                 const char        *title )
{
  // Save the extended style.
  setExtendedStyle(
     extendedStyle() | style.asExtendedUnsignedLong() );

  // Get styles and set up values for parent and owner windows.
  unsigned long
    frameStyle   = convertToGUIStyle( style ),
    exFrameStyle = convertToGUIStyle( style, true );
  IWindowHandle
    hParent = ( parent ) ? parent->handle() :
                           IWindow::desktopWindow()->handle(),
    hOwner  = ( owner )  ? owner->handle()  : IWindowHandle( 0 );
  Boolean
    isChild = ( hParent != IWindow::desktopWindow()->handle() );

  if ( isChild )
     frameStyle |= WS_CHILD;
  else
     frameStyle &= ~(unsigned long)WS_CHILD;

  // Try to get the title from the resource library.  If it
  // is not available, use whatever was provided.
  HANDLE   fcdata = resId.resourceLibrary().handle();
  if ( style & IFrameWindow::titleBar && !title )
     {
     IString titleString =
        resId.resourceLibrary().tryToLoadString( resId.id() );
     if ( titleString.length() )
        title = titleString;
     }
  else if ( !(style & IFrameWindow::titleBar) )
     {
     // The WS_OVERLAPPED style implies title bar.  Make it a
     // pop-up window if the title bar area is not needed for
     // buttons or the system menu.
     if (!(frameStyle &
           (WS_CHILD|WS_MINIMIZEBOX|WS_MAXIMIZEBOX|WS_SYSMENU)))
        frameStyle |= WS_POPUP;
     }

  IRectangle rect = ( style & IFrameWindow::shellPosition ) ?
                    IFrameWindow::nextShellRect() : initRect;

  // Create our window class for the frame if necessary.
  char* frameClass = (char*)
    registerFrameClass( style, resId, isChild );

  // Create the window.  For Windows 95 and Windows NT 4.0,
  // the WS_EX_MDICHILD extended style can be used with
  // IFrameWindow::create to create an MDI child window.
  // This style is not supported in Windows NT 3.51, so
  // we have to use a more complex approach to support
  // all operating systems.
  if (isChild)
     {
     // Use CreateMDIWindow to create the MDI child.
     RECT parentRect;
     GetClientRect(hParent, &parentRect);
     ISize parentSize = ISize(parentRect.right - parentRect.left,
                              parentRect.bottom - parentRect.top);
     rect = ICoordinateSystem::convertToNative( rect, parentSize);
     IWindowHandle hwnd = CreateMDIWindow(
                             frameClass,
                             (LPSTR)title,
                             frameStyle,
                             (int)rect.minX(),
                             (int)rect.minY(),
                             (int)rect.width(),
                             (int)rect.height(),
                             hParent,
                             GetModuleHandle(0),
                             0);
     // Complete the functions IFrameWindow::create
     // would have completed.
     this->start( hwnd );
     this->setOwner( owner );
     // CreateMDIWindow forces WS_VISIBLE to on. Undo this for now.
     this->hide();
     }
  else
     {
     // Use IFrameWindow::create so we get the resource and
     // menu handling functions it provides.
     this -> create( resId.id(),
                     title,
                     frameStyle & (unsigned long)~WS_VISIBLE,
                     frameClass,
                     hParent,
                     hOwner,
                     rect,
                     fcdata,
                     0,
                     defaultOrdering(),
                     exFrameStyle );
     }


  // If one or both of the minimize/maximize buttons is missing
  // and there is still a system menu, disable the corresponding
  // item in the system menu.  Disabling rather than removing is
  // the action recommended in the SDK.
  if (frameStyle & WS_SYSMENU)
     {
     if ( (frameStyle & (WS_MINIMIZEBOX | WS_MAXIMIZEBOX)) !=
          (WS_MINIMIZEBOX | WS_MAXIMIZEBOX) )
        {
        ISystemMenu sysMenu( this );
        if ( !(frameStyle & WS_MINIMIZEBOX) )
           sysMenu.disableItem( ISystemMenu::idMinimize );
        if ( !(frameStyle & WS_MAXIMIZEBOX) )
           sysMenu.disableItem( ISystemMenu::idMaximize );
        // Restore is left enabled when the
        // WS_EX_DLGMODALFRAME style is used
        if ((exFrameStyle & WS_EX_DLGMODALFRAME) &&
            ((frameStyle & (WS_MINIMIZEBOX | WS_MAXIMIZEBOX))==0))
           sysMenu.disableItem( ISystemMenu::idRestore );
        }
     }

  // Handle requests to minimize or maximize the window.
  if ( style & IFrameWindow::minimized )
     this -> minimize();
  else if ( style & IFrameWindow::maximized )
     this -> maximize();

  // Handle request to show the window.
  if ( style & IWindow::visible )
     this -> show();

  return *this;
  }


static LRESULT CALLBACK MDIWindowProc( void*        hwnd,
                                      unsigned int eventId,
                                      WPARAM       parm1,
                                      LPARAM       parm2 )
{
  MDIWindow* frame = (MDIWindow*)IWindow::windowWithHandle( hwnd );
  if (frame)
     {
     return DefFrameProc( hwnd,
                          frame->clientHandle(),
                          eventId,
                          parm1,
                          parm2);
     }
  else
     {
     return CallWindowProc( (FARPROC)DefWindowProc,
                            hwnd,
                            eventId,
                            parm1,
                            parm2);
     }
}

unsigned long MDIWindow::registerFrameClass(
                            const Style& style,
                            const IResourceId& resId,
                            Boolean isChild )
{
  // Create a WNDCLASS structure for registering the new class.
  // We base this class on the WC_DIALOG class, but set up the
  // background brush, class style, and icon to match those
  // specified for the MDIWindow.  IFrameWindow uses the extra
  // window word.
  WNDCLASS
    wndclass;
  if (!GetClassInfo( 0, WC_DIALOG, &wndclass))
     ITHROWGUIERROR( "GetClassInfo" );
  if (style & IFrameWindow::dialogBackground )
    wndclass.hbrBackground = (HBRUSH)(COLOR_3DFACE + 1);
  else
    wndclass.hbrBackground = (HBRUSH)(COLOR_APPWORKSPACE + 1);
  wndclass.cbWndExtra = DLGWINDOWEXTRA + 4;
  wndclass.style =
     CS_DBLCLKS | CS_OWNDC | CS_VREDRAW | CS_HREDRAW ;
  if ( !( style & IFrameWindow::alignNoAdjust ) )
     wndclass.style |= CS_BYTEALIGNWINDOW;

  // If the minimizedIcon style is set, load the icon resource
  // and place it into the class structure. Otherwise, use the
  // default icon for dialogs.
  if ( style & IFrameWindow::minimizedIcon )
     {
     HINSTANCE
        hInstance = resId.resourceLibrary().handle();
     HICON
       hIcon;
     if ( !(hIcon = LoadIcon(
                      hInstance, MAKEINTRESOURCE( resId.id() ))))
        ITHROWGUIERROR( "LoadIcon" );
     else
        wndclass.hIcon = hIcon;
     }
  wndclass.lpszMenuName = 0;
  wndclass.hInstance = GetModuleHandle(0);

  // Here is the key difference between the MDIWindow window class
  // and the ones created by IFrameWindow.  We arrange for the
  // special MDI window procedures to be called.
  if (isChild)
    wndclass.lpfnWndProc = DefMDIChildProc;
  else
    wndclass.lpfnWndProc = (WNDPROC)MDIWindowProc;

  // Register a class whose name is ICL Frame_MDI + nnnn,
  // where nnnn is the ASCII string for the value of classID.
  // This results in each frame window having a unique class name
  // similar to ICL Frame_MDI1.
  ATOM
     frameClass = 0;
  static unsigned long
     classID = 0;
  do
     {
     IString newFrameClass =  IString("ICL Frame_MDI") +
                              IString(classID);
     classID++;
     wndclass.lpszClassName = newFrameClass;
     frameClass = RegisterClass( &wndclass );
     if (!frameClass)
        {
        // If the class exists, try again with the next ID value.
        // Otherwise, throw an exception.
        if (GetLastError() != ERROR_CLASS_ALREADY_EXISTS)
           ITHROWGUIERROR( "RegisterClass" );
        }   // if not registered
     }
  while (!frameClass);

  return MAKELONG( frameClass, 0 );
}
