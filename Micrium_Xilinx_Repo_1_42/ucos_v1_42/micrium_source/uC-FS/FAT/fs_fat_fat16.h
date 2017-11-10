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
*                                            FAT16 SUPPORT
*
* Filename      : fs_fat_fat16.h
* Version       : v4.07.00
* Programmer(s) : BAN
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               MODULE
*
* Note(s) : (1) The following FAT-module-present configuration value MUST be pre-#define'd in
*               'fs_cfg_fs.h' PRIOR to all other file system modules that require FAT FAT16 Layer
*               Configuration (see 'fs_cfg_fs.h  FAT LAYER CONFIGURATION  Note #2b') :
*
*                   FS_FAT_FAT16_MODULE_PRESENT
*********************************************************************************************************
*/

#ifndef  FS_FAT_FAT16_H
#define  FS_FAT_FAT16_H

#ifdef   FS_FAT_FAT16_MODULE_PRESENT                            /* See Note #1.                                         */


/*
*********************************************************************************************************
*                                          INCLUDE FILES
*********************************************************************************************************
*/

#include  <cpu.h>
#include  "../Source/fs_cfg_fs.h"
#include  "../Source/fs_err.h"
#include  "fs_fat_type.h"


/*
*********************************************************************************************************
*                                               EXTERNS
*********************************************************************************************************
*/

#ifdef   FS_FAT_FAT16_MODULE
#define  FS_FAT_FAT16_EXT
#else
#define  FS_FAT_FAT16_EXT  extern
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

extern  const  FS_FAT_TYPE_API  FS_FAT_FAT16_API;               /* FAT16 access API.                                    */


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
*********************************************************************************************************
*/

#endif                                                          /* End of FAT FAT16 module include (see Note #1).       */
#endif
