#ifndef _VPORTLOG_
#define _VPORTLOG_
//*********************************************************
// Canvas - IViewPort with Logically-sized View Window
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//*********************************************************
#include <idrawcv.hpp>
#include <ivport.hpp>

class IGList;
class IRectangle;
class IWindowHandle;

#pragma pack(4)

// Appear to scroll a large view window.
class LogicalSizeViewPort : public IViewPort {
public:
  LogicalSizeViewPort ( unsigned long windowId,
                        IWindow* parentAndOwner,
                        unsigned long scale,
                        Boolean  specialScrolling );
virtual
 ~LogicalSizeViewPort ( );
protected:
virtual LogicalSizeViewPort
 &setupScrollBars     ( ),
 &positionViewWindow  ( const IWindowHandle& viewWindow,
                        const IRectangle& viewRectangle );
private:
  LogicalSizeViewPort ( const LogicalSizeViewPort& );
LogicalSizeViewPort
 &operator=           ( const LogicalSizeViewPort& );

LogicalSizeViewPort
 &buildGraphicList    ( ),
 &cleanUpGraphicList  ( );

IDrawingCanvas
  clViewWindow;
IGList
 *clGraphicList;
Boolean
  clCustomScrolling;
}; // LogicalSizeViewPort

#pragma pack()

#endif // _VPORTLOG_
