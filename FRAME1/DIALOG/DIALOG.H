/**********************************************************
/ Frame Window Basics - Loading a Dialog Template
/
/ Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
/ Copyright (c) 1997 John Wiley & Sons, Inc. 
/ All Rights Reserved.
**********************************************************/
#include <icconst.h>

/* Define values not in VisualAge C++ for OS/2, V3.0. */
#ifdef IC_PM

#ifndef IC_ID_OK
  #define IC_ID_OK     1
  #define IC_ID_CLOSE  0x8004    // SC_CLOSE
#endif
#endif

/* Window identifiers. */
#define ID_DIALOG      100
#define ID_OK          IC_ID_OK
#define ID_CLOSE       IC_ID_CLOSE

/* Menu identifiers. */
#define ID_FILE        200
#define ID_DIALOG_CMD  210
