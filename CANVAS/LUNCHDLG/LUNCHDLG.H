/**********************************************************
/ Lunch dialog - Sample Dialog Template
/
/ Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
/ Copyright (c) 1997 John Wiley & Sons, Inc.
/ All Rights Reserved.
**********************************************************/
#include <icconst.h>

#ifdef IC_PM
  // Define special window identifiers not originally
  // included in VisualAge for C++ V3.0.
  #ifndef IC_ID_OK
    #define IC_ID_OK     1
  #endif
  #ifndef IC_ID_CLOSE
    #define IC_ID_CLOSE  0x8004
  #endif
  #ifndef IC_ID_HELP
    #define IC_ID_HELP   0x7008
  #endif
#endif

#define ID_LUNCH_DIALOG   100
#define ID_LUNCH_TEXT     101
#define ID_FOOD           102
#define ID_HAMBURGER      103
#define ID_CHEESEBURGER   104
#define ID_HOTDOG         105
#define ID_PIZZA          106
#define ID_BEVERAGE       107
#define ID_MILK           108
#define ID_SOFTDRINK      109
#define ID_JUICE          110
#define ID_WATER          111
#define ID_SIDEORDERS     112
#define ID_SALAD          113
#define ID_FRIES          114
#define ID_REQUESTPROMPT  115
#define ID_REQUEST        116
#define ID_OK             IC_ID_OK
#define ID_CANCEL         IC_ID_CLOSE
#define ID_HELP           IC_ID_HELP
