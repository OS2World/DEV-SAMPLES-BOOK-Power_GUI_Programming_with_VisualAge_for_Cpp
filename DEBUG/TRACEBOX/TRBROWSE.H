#ifndef _TRACEBOX_H_
#define _TRACEBOX_H_
/************************************************************
/ Problem Determination  - Trace Queue Browser
/
/ Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
/ Copyright (c) 1997 John Wiley & Sons, Inc. 
/ All Rights Reserved.
************************************************************/

/************************************************************
 Window and menu item IDs
************************************************************/
#define WND_MAIN       100

#define  MI_FILE        2000
#define  MI_EXIT        2001
#define  MI_SELECTED    2010
#define  MI_CUT         2011
#define  MI_COPY        2012
#define  MI_CLEAR       2013
#define  MI_SELECTALL   2014
#define  MI_DESELECTALL 2015
#define  MI_VIEW        2020
#define  MI_INCLUDE     2021
#define  MI_INCLUDEALL  2022
#define  MI_INPUTFILTER 2023
#define  MI_AUTOSCROLL  2024
#define  MI_START       2030
#define  MI_HELP        2040
#define  MI_ABOUT       2041

/************************************************************
 String IDs
************************************************************/
#define  ABOUT_TEXT     2000
#define  START_TEXT     2001
#define  STOP_TEXT      2002



/************************************************************
 Message definitions
 Note: 0x1000 is WM_USER
************************************************************/

#define USER_MESSAGE_START 0x1100
#define ADD_OBJECT         USER_MESSAGE_START
#define START_QUEUE        USER_MESSAGE_START + 1
#define DELETE_ALL         USER_MESSAGE_START + 2
#define USER_MESSAGE_END   USER_MESSAGE_START + 2

#endif
