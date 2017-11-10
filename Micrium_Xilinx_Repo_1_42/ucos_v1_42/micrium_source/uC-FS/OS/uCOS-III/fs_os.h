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
*                                          Micrium uC/OS-III
*
* Filename      : fs_os.h
* Version       : v4.07.00
* Programmer(s) : FBJ
*                 BAN
*********************************************************************************************************
* Note(s)       : (1) Assumes uC/OS-III V3.03.01 is included in the project build.
*
*                 (2) REQUIREs the following uC/OS-III features to be ENABLED :
*
*                         ------- FEATURE --------    ---------- MINIMUM CONFIGURATION FOR FS/OS PORT ----------
*
*                     (a) Semaphores
*                         (1) OS_CFG_SEM_EN               Enabled
*
*                     (b) Task registers
*                         (1) OS_CFG_TASK_REG_TBL_SIZE    >= 2 (if working directory functionality enabled)
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

#include  <Source/os.h>                                         /* See this 'fs_os.h  Note #1'.                         */


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


typedef  OS_SEM  FS_OS_SEM;


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

#if     (OS_VERSION < 30300u)
#error  "OS_VERSION                 illegal uC/OS-III version           "
#error  "                           [MUST be >= V3.03.00]               "
#endif

#if     (OS_CFG_SEM_EN < 1u)
#error  "OS_CFG_SEM_EN              illegally #define'd in 'os_cfg.h'   "
#error  "                           [MUST be  > 0]                      "
#endif

#if     (OS_CFG_SEM_DEL_EN < 1u)
#error  "OS_CFG_SEM_DEL_EN          illegally #define'd in 'os_cfg.h'   "
#error  "                           [MUST be  > 0]                      "
#endif


/*
*********************************************************************************************************
*                                          MODULE END
*********************************************************************************************************
*/

#endif

