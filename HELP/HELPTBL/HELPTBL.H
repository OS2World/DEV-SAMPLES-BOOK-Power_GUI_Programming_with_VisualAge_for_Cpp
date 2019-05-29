/************************************************************
/ Using Help - Help Tables
/
/ Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
/ Copyright (c) 1997 John Wiley & Sons, Inc.
/ All Rights Reserved.
************************************************************/
#include <icconst.h>
#include "hlppanel.h"

#ifdef IC_PM
  // Define special window identifiers not originally
  // included in VisualAge for C++ V3.0.
  #ifndef IC_ID_CLOSE
    #define IC_ID_CLOSE  0x8004
  #endif
#endif

// Window identifiers.
#define ID_PRIMARY                   1000
#define ID_LISTBOX                   1001
#define ID_PRIMARY2                  2000
#define ID_SECONDARY_MODELESS        3000
#define ID_SECONDARY_MODAL           4000

// Generic window identifiers.
#define ID_CLIENT                    IC_FRAME_CLIENT_ID
#define ID_DUMMY                     1
#define ID_ENTRY1                    500
#define ID_ENTRY2                    501
#define ID_HELP_BUTTON               502

// Menu bar identifiers.
#define ID_MENUBAR                   100
#define ID_FILE                      101
#define ID_CHOICE1                   102
#define ID_CHOICE2                   103
#define ID_CLOSE                     IC_ID_CLOSE

// Help table and subtable identifiers.
#define ID_HELPTABLE                 1000
#define SUBTABLE_PRIMARY             1
#define SUBTABLE_PRIMARY2            2
#define SUBTABLE_SEC_MODELESS        3
#define SUBTABLE_SEC_MODAL           4
