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
*                                 FILE SYSTEM OPERATING SYSTEM LAYER
*
*                                          Micrium uC/OS-II
*
* Filename      : fs_os.h
* Version       : v4.07.00
* Programmer(s) : FBJ
*                 BAN
*********************************************************************************************************
* Note(s)       : (1) Assumes uC/OS-II V2.89 is included in the project build.
*
*                 (2) REQUIREs the following uC/OS-II features to be ENABLED :
*
*                         ------- FEATURE --------    ---------- MINIMUM CONFIGURATION FOR FS/OS PORT ----------
*
*                     (a) OS Events                   OS_MAX_EVENTS >= FS_OS_NBR_EVENTS (see this 'fs_os.h
*                                                                                             OS OBJECT DEFINES')
*
*                     (b) Semaphores                                   FS_OS_NBR_SEM    (see Note #2a)
*                         (1) OS_SEM_EN                   Enabled
*
*                     (c) Task registers
*                         (1) OS_TASK_REG_TBL_SIZE        >= 2 (if working directory functionality enabled)
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                          INCLUDE GUARD
*********************************************************************************************************
*/

#ifndef  FS_OS_H
#define  FS_OS_H


/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include  <Source/ucos_ii.h>                                       /* See this 'fs_os.h  Note #1'.                         */


/*
*********************************************************************************************************
*                                               EXTERNS
*********************************************************************************************************
*/

#ifdef   FS_OS_MODULE
#define  FS_OS_EXT
#else
#define  FS_OS_EXT  extern
#endif


/*
*********************************************************************************************************
*                                               DEFINES
*********************************************************************************************************
*/

#define  FS_OS_PRESENT


/*
*********************************************************************************************************
*                                     OS TASK/OBJECT NAME DEFINES
*********************************************************************************************************
*/

                                                                /* -------------------- OBJ NAMES --------------------- */
#define  FS_LOCK_NAME                       "FS Global Lock"
#define  FS_DEV_LOCK_NAME                   "FS Device Lock"
#define  FS_DEV_ACCESS_LOCK_NAME            "FS Device Access Lock"
#define  FS_FILE_LOCK_NAME                  "FS File Lock"


/*
*********************************************************************************************************
*                                             DATA TYPES
*********************************************************************************************************
*/

typedef  OS_EVENT  *FS_OS_SEM;


/*
*********************************************************************************************************
*                                          GLOBAL VARIABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

#if (FS_CFG_WORKING_DIR_EN == DEF_ENABLED)
void  FS_OS_WorkingDirFree(OS_TCB  *p_tcb);
#endif

CPU_BOOLEAN  FS_OS_SemCreate(FS_OS_SEM  *p_sem,
                             CPU_INT16U  cnt);

CPU_BOOLEAN  FS_OS_SemDel   (FS_OS_SEM  *p_sem);

CPU_BOOLEAN  FS_OS_SemPend  (FS_OS_SEM  *p_sem,
                             CPU_INT32U  timeout);

CPU_BOOLEAN  FS_OS_SemPost  (FS_OS_SEM  *p_sem);

/*
*********************************************************************************************************
*                                        CONFIGURATION ERRORS
*********************************************************************************************************
*/

#if     (OS_VERSION < 29207u)
#error  "OS_VERSION             illegal uC/OS-II version            "
#error  "                       [MUST be >= V2.92.07]               "
#endif



#if     (OS_SEM_EN < 1u)
#error  "OS_SEM_EN              illegally #define'd in 'os_cfg.h'   "
#error  "                       [MUST be  > 0]                      "
#endif



#if     (FS_CFG_FILE_LOCK_EN == DEF_ENABLED)

#if     (OS_SEM_ACCEPT_EN < 1u)
#error  "OS_SEM_ACCEPT_EN       illegally #define'd in 'os_cfg.h'   "
#error  "                       [MUST be  > 0]                      "
#endif

#endif


/*
*********************************************************************************************************
*                                          MODULE END
*********************************************************************************************************
*/

#endif
