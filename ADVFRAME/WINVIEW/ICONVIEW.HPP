#ifndef _ICONVIEW_
#define _ICONVIEW_
//************************************************************
// Advanced Frame - Window Viewer Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <icnrhdr.hpp>
#include "hwinobj.hpp"


class IconView : public HWindowObjectView {
public:
  IconView ( HWindowObject& object );

protected:
virtual IconView
 &populate ( );
static IContainerControl
 *clientWindow ( );

private:
ICnrHandler
  handler;
IconView(const IconView&);
IconView operator=(const IconView&);
};

#endif // _ICONVIEW_
