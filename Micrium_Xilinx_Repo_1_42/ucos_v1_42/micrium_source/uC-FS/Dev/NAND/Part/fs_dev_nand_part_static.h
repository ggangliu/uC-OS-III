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
*                                         NAND FLASH DEVICES
*                                STATIC CONFIGURATION PART-LAYER DRIVER
*
* Filename      : fs_dev_nand_static.c
* Version       : v4.07.00.00
* Programmer(s) : EJ
*                 FBJ
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               MODULE
*********************************************************************************************************
*/

#ifndef  FS_NAND_STATIC_MODULE_PRESENT
#define  FS_NAND_STATIC_MODULE_PRESENT


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

#ifdef   FS_NAND_STATIC_MODULE
#define  FS_NAND_STATIC_EXT
#else
#define  FS_NAND_STATIC_EXT  extern
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
**********************************************************************************************************
*                       NAND FLASH DEVICE GENERIC CONTROLLER CONFIGURATION DATA TYPE
**********************************************************************************************************
*/


#define  FS_NAND_PART_STATIC_CFG_FIELDS                                                                                                                                          \
    FS_NAND_PART_STATIC_CFG_FIELD(FS_NAND_BLK_QTY         ,  BlkCnt          ,     0u                          /* Total number of blocks.                              */) \
    FS_NAND_PART_STATIC_CFG_FIELD(FS_NAND_PG_PER_BLK_QTY  ,  PgPerBlk        ,     0u                          /* Nbr of pgs per blk.                                  */) \
    FS_NAND_PART_STATIC_CFG_FIELD(FS_NAND_PG_SIZE         ,  PgSize          ,     0u                          /* Size (in octets) of each pg.                         */) \
    FS_NAND_PART_STATIC_CFG_FIELD(FS_NAND_PG_SIZE         ,  SpareSize       ,     0u                          /* Size (in octets) of spare area per pg.               */) \
    FS_NAND_PART_STATIC_CFG_FIELD(CPU_INT08U              ,  NbrPgmPerPg     ,     1u                          /* Nbr of program operation per page.                   */) \
    FS_NAND_PART_STATIC_CFG_FIELD(CPU_INT08U              ,  BusWidth        ,     8u                          /* Bus width of NAND dev.                               */) \
    FS_NAND_PART_STATIC_CFG_FIELD(CPU_INT08U              ,  ECC_NbrCorrBits ,   255u                          /* Nbr of bits of ECC correctability.                   */) \
    FS_NAND_PART_STATIC_CFG_FIELD(FS_NAND_PG_SIZE         ,  ECC_CodewordSize,     0u                          /* ECC codeword size in bytes.                          */) \
    FS_NAND_PART_STATIC_CFG_FIELD(FS_NAND_DEFECT_MARK_TYPE,  DefectMarkType  , DEFECT_SPARE_L_1_PG_1_OR_N_ALL_0/* Defect mark pos relative to spare area.              */) \
    FS_NAND_PART_STATIC_CFG_FIELD(FS_NAND_BLK_QTY         ,  MaxBadBlkCnt    , 65535u                          /* Max nbr of bad blk in dev.                           */) \
    FS_NAND_PART_STATIC_CFG_FIELD(CPU_INT32U              ,  MaxBlkErase     ,     1u                          /* Maximum number of erase operations per block.        */) \
    FS_NAND_PART_STATIC_CFG_FIELD(FS_NAND_FREE_SPARE_DATA , *FreeSpareMap    , DEF_NULL                        /* Pointer to the map of available bytes in spare area. */)


#define  FS_NAND_PART_STATIC_CFG_FIELD(type, name, dftl_val)  type name;
typedef struct fs_nand_part_static_cfg {
    FS_NAND_PART_STATIC_CFG_FIELDS
} FS_NAND_PART_STATIC_CFG;
#undef   FS_NAND_PART_STATIC_CFG_FIELD

extern  const  FS_NAND_PART_STATIC_CFG  FS_NAND_PartStatic_DfltCfg;

/*
*********************************************************************************************************
*                                              DATA TYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                          GLOBAL VARIABLES
*********************************************************************************************************
*/

extern  const        FS_NAND_PART_API  FS_NAND_PartStatic;
FS_NAND_STATIC_EXT   FS_CTR            FS_NAND_PartStatic_UnitCtr;


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

