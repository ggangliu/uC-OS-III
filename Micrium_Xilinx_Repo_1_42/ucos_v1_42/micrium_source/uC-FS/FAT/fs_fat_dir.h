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
*                                     FILE SYSTEM FAT MANAGEMENT
*
*                                          DIRECTORY ACCESS
*
* Filename      : fs_fat_dir.h
* Version       : v4.07.00
* Programmer(s) : BAN
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               MODULE
*
* Note(s) : (1) See 'fs_fat.h  MODULE'.
*
*           (2) See 'fs_dir.h  MODULE'.
*********************************************************************************************************
*/

#ifndef  FS_FAT_DIR_H
#define  FS_FAT_DIR_H

#ifdef   FS_FAT_MODULE_PRESENT                                  /* See Note #1.                                         */
#ifdef   FS_DIR_MODULE_PRESENT                                  /* See Note #2.                                         */


/*
*********************************************************************************************************
*                                          INCLUDE FILES
*********************************************************************************************************
*/

#include  <cpu.h>
#include  "../Source/fs_cfg_fs.h"
#include  "../Source/fs_dir.h"
#include  "../Source/fs_err.h"
#include  "../Source/fs_type.h"


/*
*********************************************************************************************************
*                                               EXTERNS
*********************************************************************************************************
*/

#ifdef   FS_FAT_DIR_MODULE
#define  FS_FAT_DIR_EXT
#else
#define  FS_FAT_DIR_EXT  extern
#endif


/*
*********************************************************************************************************
*                                               DEFINES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             DATA TYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                          GLOBAL VARIABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               MACRO'S
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

void  FS_FAT_DirModuleInit(FS_QTY        dir_cnt,               /* Init FAT dir module.                                 */
                           FS_ERR       *p_err);

/*
*********************************************************************************************************
*                                  SYSTEM DRIVER FUNCTION PROTOTYPES
*********************************************************************************************************
*/

void  FS_FAT_DirClose     (FS_DIR        *p_dir);               /* Close a directory.                                   */

void  FS_FAT_DirOpen      (FS_DIR        *p_dir,                /* Open a directory.                                    */
                           CPU_CHAR      *name_dir,
                           FS_ERR        *p_err);

void  FS_FAT_DirRd        (FS_DIR        *p_dir,                /* Read a  directory entry.                             */
                           FS_DIR_ENTRY  *p_dir_entry,
                           FS_ERR        *p_err);


/*
*********************************************************************************************************
*                                        CONFIGURATION ERRORS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             MODULE END
*
* Note(s) : (1) See 'MODULE  Note #1'.
*
*           (2) See 'MODULE  Note #2'.
*********************************************************************************************************
*/

#endif                                                          /* End of directory module include (see Note #2).       */
#endif                                                          /* End of FAT       module include (see Note #1).       */
#endif
