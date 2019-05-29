#ifndef _INFOVIEW_
#define _INFOVIEW_
//************************************************************
// Advanced Frame - Profile Viewer Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include "hwinobj.hpp"

class IMultiLineEdit;

class InfoView : public HWindowObjectView {
public:
  InfoView ( HWindowObject& object );
protected:
virtual InfoView
 &populate ( );
static IMultiLineEdit
 *clientWindow ( );
private:
InfoView ( const InfoView& );
InfoView& operator= ( const InfoView& );
};

#endif // _INFOVIEW_
