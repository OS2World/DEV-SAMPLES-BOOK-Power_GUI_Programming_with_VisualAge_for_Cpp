//************************************************************
// Data Types - Using IStringParser
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//
// DESCRIPTION:
//   This program searches the current directory for the oldest and newest
//   files and reports findings to stdout.
//
//   Usage:   stparse2
//
//************************************************************
#include <idate.hpp>
#include <itime.hpp>
#include <istring.hpp>
#include <istparse.hpp>
#include <iostream.h>
#include <stdlib.h>
#include <fstream.h>

int main ()
{
   // List a directory and redirect it to a file.
#ifdef IC_PM
   int rc = system ("dir /N > dir.out");
#endif
#ifdef IC_WIN
   int rc = system ("dir > dir.out");
#endif
   if (!rc)
   {
     // Create an input stream.
     ifstream input( "dir.out" );
     if ( !input )
     {
        cerr << "Error opening file.\a" << endl;
        return 0;
     }

     // Create variables to hold parsing tokens.
     IString line,
             pattern1 = IString( 0, 1,
                                "bytes", IString("bytes").length(),
                                 0, 1,
                                 '*' ),
             pattern2 = IString( 0, 1,
                                "<DIR>", IString("<DIR>").length(),
                                 0, 1,
                                 '*' ),
             month, day, year,
             hour, minutes, AMPM,
             date,
             time,
             size,
             sizeEAs,
             filename,
             oldestFilename,
             newestFilename;
     IDate oldestDate, newestDate(1,1), theDate;
     ITime oldestTime, newestTime(0,0), theTime;

     // Skip the first five lines of the output that contain nonpertinent
     // information.
     for (int i=0; i<5; i++)
        IString::lineFrom (input);

     // Read lines and look for the oldest and newest files.
     while ( input )
     {
       // Get a line.
       line = IString::lineFrom( input );

       // If the line is the summary information at the bottom,
       // quit the loop.
       if (line.isLike (pattern1))
          break;

       // Only process the line if it contains information for a file,
       // not a directory.
       if (!line.isLike (pattern2))
       {
          // Parse the line into its tokens.
          // OS/2 has an EA size field; Windows does not.
#ifdef IC_PM
          line >> date >> time >> size >> sizeEAs >> filename;
#endif
#ifdef IC_WIN
          line >> date >> time >> size >> filename;
#endif
          // Strip leading or trailing white space from the file name.
          filename.strip();
          // Our output file will always be the newest, so exclude it.
          if (filename != "DIR.OUT")
          {
             // Parse the date and create an IDate object.  Hardcode the
             // default separators.  A more robust solution would query
             // them from the system.
#ifdef IC_PM
             date >> month >> '-' >> day >> '-' >> year;
#endif
#ifdef IC_WIN
             date >> month >> '/' >> day >> '/' >> year;
#endif
             IDate theDate (IDate::Month(month.asInt()), day.asInt(),
                year.asInt()+1900);
   
             // Parse the time and create an ITime object.
             time >> hour >> ":" >> 1 >> minutes >> 2 >> AMPM;
             ITime theTime (((AMPM == "a") ||
                             (AMPM == "A")) ?
                             hour.asInt() : hour.asInt() + 12,
                             minutes.asInt());
   
             // Check to see if the date of the current file is older
             // than the oldest or newer than the newest.  If so, reset
             // the variables.
             if ((theDate < oldestDate) ||
                ((theDate == oldestDate) && (theTime < oldestTime)))
             {
                oldestDate = theDate;
                oldestFilename = filename;
                oldestTime = theTime;
             }
             else if ((theDate > newestDate) ||
                ((theDate == newestDate) && (theTime > newestTime)))
             {
                newestDate = theDate;
                newestFilename = filename;
                newestTime = theTime;
             }
          }
       }
     }

     // Report our findings.
     cout << "Oldest file is " << oldestFilename << " with date " <<
          oldestDate.asString() << " and time " << oldestTime.asString() <<
          endl;
     cout << "Newest file is " << newestFilename << " with date " <<
          newestDate.asString() << " and time " << newestTime.asString() <<
          endl;
   }
   else
      cout << "Dir command could not be completed." << endl;
   return 0;
}
