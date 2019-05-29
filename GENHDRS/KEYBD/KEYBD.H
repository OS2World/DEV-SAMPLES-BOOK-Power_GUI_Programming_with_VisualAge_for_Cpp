/**********************************************************
/ Keyboard handler example for character keys.
/
/ Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
/ Copyright (c) 1997 John Wiley & Sons, Inc.
/ All Rights Reserved.
**********************************************************/
#include <icconst.h>

#ifdef IC_PM
  // Define the identifier for the Close system command that was
  // not originally included in VisualAge for C++ for OS/2, V3.0.
  #ifndef IC_ID_CLOSE
    #define IC_ID_CLOSE  0x8004
  #endif
#endif

#define ID_KEYBD_DIALOG         100
#define ID_ANY_ENTRY            101
#define ID_UPPERCASE_ENTRY      102
#define ID_HEX_ENTRY            103
#define ID_UPPERCASE_HEX_ENTRY  104
#define ID_UPPERCASE_HEX_COMBO  105
#define ID_UPPERCASE_HEX_MLE    106
#define ID_CLOSE                IC_ID_CLOSE

#ifdef IC_PM
  #define ID_COMBOBOX_EF   0x029B  // CBID_EDIT from pmwin.h.
#else
  #define ID_COMBOBOX_EF   0x03E9
#endif
