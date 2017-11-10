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
*                         NAND DEVICE GENERIC CONTROLLER SOFTWARE ECC EXTENSION
*
* Filename      : fs_dev_nand_ctrlr_imx28_bch.h
* Version       : v4.07.00
* Programmer(s) : EJ
*                 
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                                 MODULE
*********************************************************************************************************
*/

#ifndef  FS_NAND_CGEN_BCH_MODULE_PRESENT
#define  FS_NAND_CGEN_BCH_MODULE_PRESENT


/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#include  "../fs_dev_nand_ctrlr_gen.h"


/*
*********************************************************************************************************
*                                                EXTERNS
*********************************************************************************************************
*/

#ifdef   FS_NAND_CGEN_BCH_MODULE
#define  FS_NAND_CGEN_BCH_EXT
#else
#define  FS_NAND_CGEN_BCH_EXT  extern
#endif


/*
*********************************************************************************************************
*                                         DEFAULT CONFIGURATION
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                                DEFINES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               DATA TYPES
*********************************************************************************************************
*/

#define  FS_NAND_CTRLR_GEN_BCH_CFG_FIELDS \
    FS_NAND_CTRLR_GEN_BCH_CFG_FIELD(       CPU_INT32U,  Ecc0,     2u) \
    FS_NAND_CTRLR_GEN_BCH_CFG_FIELD(       CPU_INT32U,  EccN,     2u) \
    FS_NAND_CTRLR_GEN_BCH_CFG_FIELD(       CPU_INT32U,  EccThres, 0u) \
    FS_NAND_CTRLR_GEN_BCH_CFG_FIELD(const  ECC_CALC,   *NextPtr, DEF_NULL)

#define FS_NAND_CTRLR_GEN_BCH_CFG_FIELD(type, name, dflt_val)  type name;
typedef  struct  {
    FS_NAND_CTRLR_GEN_BCH_CFG_FIELDS
} FS_NAND_CTRLR_GEN_BCH_CFG;
#undef  FS_NAND_CTRLR_GEN_BCH_CFG_FIELD

extern  const  FS_NAND_CTRLR_GEN_BCH_CFG  FS_NAND_CtrlrGen_BCH_DlftCfg;


/*
*********************************************************************************************************
*                                            GLOBAL VARIABLES
*********************************************************************************************************
*/

extern  FS_NAND_CTRLR_GEN_EXT  FS_NAND_CtrlrGen_BCH;

/*
*********************************************************************************************************
*                                                 MACROS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                          FUNCTION PROTOTYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                          CONFIGURATION ERRORS
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                               MODULE END
*********************************************************************************************************
*/

#endif

