/**********************************************************
/ Using Help - Help for Special Cases
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
  #ifndef IC_FILE_DIALOG
    #define IC_FILE_DIALOG  256
  #endif
#endif

// Window identifiers.
#define ID_PRIMARY                   1000
#define ID_SHOWFILEDLG               1001
#define ID_SECONDARY                 2000
#define ID_PAGE1                     2010
#define ID_ENTRY1                    2011
#define ID_ENTRY2                    2012
#define ID_ENTRY3                    2013
#define ID_PAGE2                     2020
#define ID_ENTRYA                    2021
#define ID_ENTRYB                    2022
#define ID_ENTRYC                    ID_ENTRY3
#define ID_PAGE3                     2030
#define ID_ENTRYX                    2031
#define ID_ENTRYY                    2032
#define ID_DIALOG                    3000
#define ID_DIALOG_ENTRY1             3001
#define ID_DIALOG_ENTRY2             3002

// Generic window identifiers.
#define ID_DUMMY                     1
#define ID_CLIENT                    IC_FRAME_CLIENT_ID

// Help table and subtable identifiers.
#define ID_HELPTABLE                 1000
#define SUBTABLE_PRIMARY             1
#define SUBTABLE_SECONDARY           2
#define SUBTABLE_PAGE3               3
#define SUBTABLE_DIALOG              4
#define SUBTABLE_FILEDIALOG          5
