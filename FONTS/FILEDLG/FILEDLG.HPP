//************************************************************
// Views - Using the File Dialog
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <icmdhdr.hpp>
#include <iframe.hpp>
#include <imle.hpp>

class MyCommandHandler : public ICommandHandler
{
public:
  MyCommandHandler ( IFrameWindow* myFrame,
                     IMultiLineEdit* myMLE )
   : mle(myMLE),
     frame(myFrame) {};

virtual Boolean
  command( ICommandEvent& cmdEvent );

private:
IFrameWindow
 *frame;
IMultiLineEdit
 *mle;
};

