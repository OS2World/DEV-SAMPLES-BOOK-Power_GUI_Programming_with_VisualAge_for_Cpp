#ifndef _KEYVIEW_
#define _KEYVIEW_
//************************************************************
// GUI Profile Viewer Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include "profobj.hpp"
#include "enhprof.hpp"

class IMultiLineEdit;

class ProfileKeyObject : public ProfileObject {
public:
  ProfileKeyObject ( ProfileApplication &app,
                     const IString      &keyName,
                     IContainerControl  *cnr );
virtual ProfileObjectView
 *newView ( );
virtual ProfileKey
 &key ( );
private:
ProfileKey
  profKey;
};

class KeyView : public ProfileObjectView {
public:
  KeyView ( ProfileKeyObject &keyObj );
protected:
virtual KeyView
 &populate ( );
static IMultiLineEdit
 *clientWindow ( );
private:
ProfileKeyObject
 &keyObj;
KeyView ( const KeyView& );
KeyView& operator= ( const KeyView& );
};

#endif // _KEYVIEW_
