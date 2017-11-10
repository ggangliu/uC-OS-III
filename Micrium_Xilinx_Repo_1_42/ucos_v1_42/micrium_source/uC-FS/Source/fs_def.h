/*
*********************************************************************************************************
*                                             uC/FS V4
*                                     The Embedded File System
*
*                         (c) Copyright 2008-2014; Micrium, Inc.; Weston, FL
*
*                  All rights reserved.  Protected by international copyright laws.
*
*                  uC/FS is provided in source form to registered licensees ONLY.  It is
*                  illegal to distribute this source code to any third party unless you receive
*                  written permission by an authorized Micrium representative.  Knowledge of
*                  the source code may NOT be used to develop a similar product.
*
*                  Please help us continue to provide the Embedded community with the finest
*                  software available.  Your honesty is greatly appreciated.
*
*                  You can find our product's user manual, API reference, release notes and
*                  more information at: https://doc.micrium.com
*
*                  You can contact us at: http://www.micrium.com
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                         FILE SYSTEM DEFINES
*
* Filename      : fs_def.h
* Version       : v4.07.00
* Programmer(s) : BAN
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                                 MODULE
*********************************************************************************************************
*/

#ifndef  FS_DEF_H
#define  FS_DEF_H

/*
*********************************************************************************************************
*                                         FILE SYSTEM DEFINES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                            BUILD DEFINES
*********************************************************************************************************
*/

#define  FS_BUILD_FULL                                     1u
#define  FS_BUILD_DEV_ONLY                                 2u

/*
*********************************************************************************************************
*                                        SYSTEM DRIVER DEFINES
*********************************************************************************************************
*/

#define  FS_SYS_DRV_SEL_FAT                                1u


/*
*********************************************************************************************************
*                                          TIME DEFINES
*********************************************************************************************************
*/

#define  FS_TIME_FMT              CLK_STR_FMT_DAY_MONTH_DD_HH_MM_SS_YYYY
#define  FS_TIME_STR_MIN_LEN      CLK_STR_FMT_DAY_MONTH_DD_HH_MM_SS_YYYY_LEN

#define  FS_TIME_TS_INVALID       ((CLK_TS_SEC)-1)

/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif                                                          /* End of fs_def.h include.                         */

