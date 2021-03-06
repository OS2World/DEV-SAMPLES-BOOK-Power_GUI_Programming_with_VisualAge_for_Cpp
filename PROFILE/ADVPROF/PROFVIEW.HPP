#ifndef _PROFVIEW_
#define _PROFVIEW_
//************************************************************
// GUI Profile Viewer Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <iframe.hpp>
#include <ititle.hpp>
#include <icnrctl.hpp>
#include <icnrhdr.hpp>

class EnhancedProfile;

class ProfileView : public IVBase {
public:
  ProfileView ( EnhancedProfile &profile );

virtual ProfileView
 &open     ( );

protected:
virtual ProfileView
 &populate ( );

private:
EnhancedProfile
 &profile;
IFrameWindow
  frame;
ITitle
  title;
IContainerControl
  client;
ICnrHandler
  handler;
ProfileView ( const ProfileView& );
ProfileView& operator=( const ProfileView& );
}; // class ProfileView

#endif // _PROFVIEW_
