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
*                                      FILE SYSTEM DEVICE DRIVER
*
*                                          NOR FLASH DEVICES
*                              AMD-COMPATIBLE NOR PHYSICAL-LAYER DRIVER
*
* Filename      : fs_dev_nor_amd_1x08.h
* Version       : v4.07.00.00
* Programmer(s) : BAN
*********************************************************************************************************
* Note(s)       : (1) Supports CFI NOR flash implementing AMD command set, including :
*
*                     (a) Most AMD & Spansion devices.
*                     (b) Most ST/Numonyx M29 devices.
*                     (c) #### List tested devices.
*
*                 (2) Fast programming command "write to buffer & program", supported by many flash
*                     implementing AMD command set, is used in this driver if the "Maximum number of bytes
*                     in a multi-byte write" (in the CFI device geometry definition) is non-zero.
*
*                     (a) Some flash implementing AMD command set have non-zero multi-byte write size but
*                         do NOT support the "write to buffer & program" command.  Often, these devices
*                         will support alternate fast programming methods (e.g., "quadruple byte program"
*                         or "octuple byte program").  This driver MUST be modified for those devices, to
*                         ignore the multi-byte write size in the CFI information (see 'FSDev_NOR_PHY_Open()
*                         Note #2'.
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               MODULE
*********************************************************************************************************
*/

#ifndef  FS_DEV_NOR_AMD_1X08_PRESENT
#define  FS_DEV_NOR_AMD_1X08_PRESENT


/*
*********************************************************************************************************
*                                               EXTERNS
*********************************************************************************************************
*/

#ifdef   FS_DEV_NOR_AMD_1X08_MODULE
#define  FS_DEV_NOR_AMD_1X08_EXT
#else
#define  FS_DEV_NOR_AMD_1X08_EXT  extern
#endif


/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include  "../../../Source/fs_dev.h"
#include  "../fs_dev_nor.h"


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


/*
*********************************************************************************************************
*                                        CONFIGURATION ERRORS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif                                                          /* End of NOR AMD module include.                       */
