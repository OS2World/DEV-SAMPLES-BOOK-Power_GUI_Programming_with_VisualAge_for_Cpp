/**********************************************************
/ Using Help - Help Menu Choices
/
/ Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
/ Copyright (c) 1997 John Wiley & Sons, Inc.
/ All Rights Reserved.
**********************************************************/
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
#define ID_CLIENT                    IC_FRAME_CLIENT_ID
#define ID_HEADING                   1001
#define ID_SECONDARY_PB              1002
#define ID_EXIT_PB                   1003
#define ID_SECONDARY                 2000

// Menu bar identifiers.
#define ID_MENUBAR                   ID_PRIMARY
#define ID_FILE                      101
#define ID_CLOSE                     IC_ID_CLOSE
#define ID_HELP                      200
#define ID_USINGHELP                 201
#define ID_PRODUCTINFO               202
#define ID_HELPCONTENTS              203

// Help table and subtable identifiers.
#define ID_HELPTABLE                 3000
#define SUBTABLE_PRIMARY             1
#define SUBTABLE_SECONDARY           2
