//************************************************************
// Problem Determination  - Trace Queue Browser
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <istring.hpp>
#include <ithread.hpp>
#include "trbrowse.hpp"

const unsigned PMQUEUE_SIZE = 2000;
IString        QUEUE_NAME("PRINTF32");       // base name of queue

/*------------------------------------------------------------------------------
| main                                                                         |
------------------------------------------------------------------------------*/
int main(int argc, char* argv[] )
{
#if (IC_MAJOR_VERSION >= 320)
   // The pmCompatible container works a little better than the listview
   // container, since it results in single column output.
   // The command line switch -LV can be used to force listview to be used.
   IContainerControl::setDefaultStyle(
      IContainerControl::defaultStyle() |
      IContainerControl::pmCompatible );
#endif
   while (argc > 1)
      {
      argc--;
      if ( IString(argv[argc]) == IString("-LV") )
         {
#if (IC_MAJOR_VERSION >= 320)
         IContainerControl::setDefaultStyle(
            IContainerControl::defaultStyle() &
            ~IContainerControl::pmCompatible );
#endif
         }
      else
         QUEUE_NAME = IString(argv[argc]);
      }

   // Note that we increase the size of the PM
   // message queue to try to avoid filling
   // it up.
   IThread::current().initializeGUI(PMQUEUE_SIZE);

   // Create the trace browser window
   TraceBrowser traceWindow (QUEUE_NAME);

   // Give the window the focus and show it.
   // focus (try to be non-intrusive).
   traceWindow
     .setFocus()
     .show();

   IThread::current().processMsgs();
   IThread::current().terminateGUI();

   return 0;
}
