#ifndef _HWINOBJ_
#define _HWINOBJ_
//************************************************************
// Advanced Frame - Window Viewer Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <iframe.hpp>
#include <icnrctl.hpp>
#include <icnrmhdr.hpp>
#include <ititle.hpp>
#include "hwindow.hpp"

class IString;
class HWindowObjectView;

class HWindowObject : public IContainerObject {
public:
  HWindowObject ( const HWindow&     hwindow,
                  unsigned long      iconId,
                  IContainerControl* cnr );
virtual
  ~HWindowObject();

virtual void
 handleOpen( IContainerControl* cnr );
virtual HWindowObject
 &openIconView( );
virtual Boolean
 isIconViewAvailable( ) const;
virtual HWindowObject
 &openInfoView( );
virtual HWindowObjectView
 &infoView ( );
virtual HWindowObjectView
 &iconView ( );
virtual HWindowObject
 &viewClosed ( HWindowObjectView* view );
virtual IContainerControl
 *container ( ) const;
const HWindow
 &hWindow( ) const;


protected:
virtual HWindowObjectView
 *newIconView ( );
virtual HWindowObjectView
 *newInfoView ( );

private:
IContainerControl
 *objCnr;
HWindowObjectView
 *ficonView;
HWindowObjectView
 *finfoView;
HWindow
 fhwindow;
};

class HWindowObjectView : protected IFrameWindow {
public:
  ~HWindowObjectView ( );
virtual HWindowObjectView
 &open ( );
virtual HWindowObjectView
 &invalidateObject ( );
protected:
  HWindowObjectView ( IWindow*       client,
                      HWindowObject& object,
                      const IString& viewName );
HWindowObject
 *object ( ) const;
private:
ITitle
  viewTitle;
HWindowObject
 *viewObj;
HWindowObjectView ( const HWindowObjectView& );
HWindowObjectView& operator=( const HWindowObjectView&);
};

class MenuHandler : public ICnrMenuHandler {
public:
  MenuHandler(  );
protected:
virtual Boolean
  makePopUpMenu( IMenuEvent& event );
};


#endif // _HWINOBJ_
