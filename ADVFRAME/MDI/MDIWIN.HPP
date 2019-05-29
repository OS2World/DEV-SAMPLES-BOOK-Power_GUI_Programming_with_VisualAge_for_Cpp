#ifndef _MDIWIN_
#define _MDIWIN_
//************************************************************
// Advanced Frame - MDI Frame Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************

#include <iframe.hpp>

class MDIWindow : public IFrameWindow {
public:
 MDIWindow( const IResourceId&         resId,
           IWindow*                   parent,
           IWindow*                   owner ,
           unsigned long              windowMenuId,
           unsigned long              childMenuId,
           const IRectangle&          initRect,
           const IFrameWindow::Style& style = defaultStyle(),
           const char*                title = 0 );
 MDIWindow( const IResourceId&         resId,
            MDIWindow*                 parent,
            const IRectangle&          initRect,
            const IFrameWindow::Style& style = defaultStyle(),
            const char*                title = 0 );

virtual MDIWindow
 &setClient    ( IWindow* newClient );

virtual MDIWindow
 &close          ( ),
 &maximize       ( ),
 &restore        ( );

virtual MDIWindow
 *activeChild( ) const;

virtual MDIWindow
 &activateChild( unsigned long childId ),
 &arrange        ( ),
 &cascade        ( ),
 &tile           ( Boolean horizontal=true );

protected:
MDIWindow
 &initialize      ( const IResourceId& resId,
                    const Style&       style,
                    IWindow*           parent   = 0,
                    IWindow*           owner    = 0,
                    const IRectangle&  initRect = IRectangle(),
                    const char*        title    = 0 );
unsigned long
  registerFrameClass ( const Style& style,
                       const IResourceId& resId ,
                       Boolean isChild );

private:
 IWindow
  *fclient;
 unsigned long
   fchildId;
 MDIWindow( const MDIWindow& );
 MDIWindow& operator=( const MDIWindow& );
};

#endif
