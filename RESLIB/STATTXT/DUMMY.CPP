//************************************************************
// Using Resources - Switching Resources Dynamically
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
extern "C" {

void ADummyFunction()
{
}

#pragma export(isValid, "isValid", 1)

// Return true if "number" is less than 10.
int isValid( int number)
{
  if (number<10)
     return 1;
  else
     return 0;
}

}
