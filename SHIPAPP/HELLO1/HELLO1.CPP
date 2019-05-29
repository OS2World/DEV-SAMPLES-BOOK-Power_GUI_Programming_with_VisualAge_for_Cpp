#include <ibase.hpp>
#include <iapp.hpp>
#include <istattxt.hpp>
#include <iframe.hpp>
#include <icoordsy.hpp>
#include <istring.hpp>

#ifdef IC_PM
#include <icsperf.h>    // Include prototype for PerfStop()
#else
#include <iperf.h>      // Include prototype for PerfStop()
#endif

// Define a static object.
IString appName("Hello World - Version 1");

int main()
{
  ICoordinateSystem::setApplicationOrientation(
          ICoordinateSystem::originLowerLeft );
  IFrameWindow mainWindow (appName);
  IStaticText hello(IC_FRAME_CLIENT_ID, &mainWindow, &mainWindow);
  hello.setText("Hello World");
  hello.setAlignment(IStaticText::centerCenter);
  mainWindow.setClient(&hello);

  mainWindow.sizeTo(ISize(400,300));
  mainWindow.setFocus();
  mainWindow.show();

  // We shut down tracing now.
  PerfStop();

  IApplication::current().run();
  return 0;
} /* end main() */
