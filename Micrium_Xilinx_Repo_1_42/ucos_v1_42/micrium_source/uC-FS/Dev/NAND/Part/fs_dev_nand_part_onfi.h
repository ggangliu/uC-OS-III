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
*                                         FILE SYSTEM DEVICE DRIVER
*
*                                          NAND FLASH ONFI DEVICES
*
* Filename      : fs_dev_nand_part_onfi.h
* Version       : v4.07.00.00
* Programmer(s) : FBJ
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                               MODULE
*********************************************************************************************************
*/

#ifndef  FS_NAND_ONFI_MODULE_PRESENT
#define  FS_NAND_ONFI_MODULE_PRESENT


/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include  "../fs_dev_nand.h"


/*
*********************************************************************************************************
*                                               EXTERNS
*********************************************************************************************************
*/

#ifdef   FS_NAND_ONFI_MODULE
#define  FS_NAND_ONFI_EXT
#else
#define  FS_NAND_ONFI_EXT  extern
#endif


/*
*********************************************************************************************************
*                                        DEFAULT CONFIGURATION
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               DEFINES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                              DATA TYPES
*********************************************************************************************************
*/


/*
**********************************************************************************************************
*                          NAND FLASH DEVICE ONFI PART CONFIGURATION DATA TYPE
**********************************************************************************************************
*/

#define  FS_NAND_PART_ONFI_CFG_FIELDS \
    FS_NAND_PART_ONFI_CFG_FIELD(FS_NAND_FREE_SPARE_DATA, *FreeSpareMap, DEF_NULL /* Pointer to the map of available bytes in spare area. */)

#define  FS_NAND_PART_ONFI_CFG_FIELD(type, name, dflt_val)  type name;
typedef  struct  fs_nand_part_onfi_cfg {
    FS_NAND_PART_ONFI_CFG_FIELDS
} FS_NAND_PART_ONFI_CFG;
#undef   FS_NAND_PART_ONFI_CFG_FIELD

extern  const  FS_NAND_PART_ONFI_CFG  FS_NAND_PartONFI_DfltCfg;


/*
*********************************************************************************************************
*                                          GLOBAL VARIABLES
*********************************************************************************************************
*/

extern  const       FS_NAND_PART_API  FS_NAND_PartONFI;
FS_NAND_ONFI_EXT    FS_CTR            FS_NAND_PartONFI_UnitCtr;


/*
*********************************************************************************************************
*                                               MACROS
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

#endif

