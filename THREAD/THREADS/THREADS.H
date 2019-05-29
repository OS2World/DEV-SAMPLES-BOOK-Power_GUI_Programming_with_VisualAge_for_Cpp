/*******************************************************************************
* FILE NAME: threads.h                                                         *
*                                                                              *
* DESCRIPTION:                                                                 *
*                                                                              *
* COPYRIGHT:                                                                   *
*   Licensed Materials - Property of Solution Frameworks                       *
*   Copyright (C) 1996, Solution Frameworks                                    *
*   All Rights Reserved                                                        *
*******************************************************************************/
#ifdef WINDOWSx
#define THREADS       "1000"

#define THREADS_POPUP "1100"
#define THREADS_NEW   "1101"
#define THREADS_EXIT  "1102"

#define THREAD_POPUP    "1200"
#define THREAD_SUSPEND  "1201"
#define THREAD_RESUME   "1201"
#define THREAD_STOP     "1202"
#define THREAD_BOOST    "1203"
#define THREAD_REDUCE   "1204"
#define THREAD_IDLE     "1205"
#define THREAD_REGULAR  "1206"
#define THREAD_TIMECRIT "1207"
#define THREAD_FORE     "1208"

#define THREAD1 "2000"
#else
#define THREADS       1000

#define THREADS_POPUP 1100
#define THREADS_NEW   1101
#define THREADS_EXIT  1102
 
#define THREAD_POPUP         1200
#define THREAD_SHOW          1201
#define THREAD_SUSPEND       1202
#define THREAD_RESUME        1202
#define THREAD_STOP          1203
#define THREAD_CRITSEC       1204
#define THREAD_GETPRIVATE    1205
#define THREAD_RELPRIVATE    1206
#define THREAD_GETSHARED     1207
#define THREAD_RELSHARED     1208
#define THREAD_RESETPRIVATE  1209
#define THREAD_SIGNALPRIVATE 1210
#define THREAD_WAITPRIVATE   1211
#define THREAD_RESETSHARED   1212
#define THREAD_SIGNALSHARED  1213
#define THREAD_WAITSHARED    1214
#define THREAD_BOOST         1215
#define THREAD_REDUCE        1216
#define THREAD_IDLE          1217
#define THREAD_REGULAR       1218
#define THREAD_TIMECRIT      1219
#define THREAD_FORE          1220
                             
#define THREAD1 2000
#endif
