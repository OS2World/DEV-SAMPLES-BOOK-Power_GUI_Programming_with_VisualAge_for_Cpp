//************************************************************
// Basic Profile Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <iprofile.hpp>
#include <iostream.h>

int main()
{

#ifdef IC_PM
   IProfile  profile ( "Jennware.ini" );
#else
   IProfile  profile ( "Jenn's Software" );
#endif

   profile.addOrReplaceElementWithKey ("Bitmap",
                                       "horse.bmp",
                                       "Visual Jenn" );

   profile.addOrReplaceElementWithKey ("User count",
                                       61368,
                                       "Visual Jenn" );

   cout << "The key value pairs are:  " << endl;

   IProfile::Cursor cursor (profile, "Visual Jenn");
   for (cursor.setToFirst();
        cursor.isValid();
        cursor.setToNext())
   {
       IString keyName = profile.applicationOrKeyAt (cursor);

       cout << keyName << ":  ";

       if (keyName == "User count")
          cout << profile.integerWithKey (keyName,"Visual Jenn") << endl;
       else
          cout << profile.elementWithKey (keyName,"Visual Jenn") << endl;
   }


}
