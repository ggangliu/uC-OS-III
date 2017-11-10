/*
*********************************************************************************************************
*                                             uC/FS V4
*                                     The Embedded File System
*
*                          (c) Copyright 2014-2014; Micrium, Inc.; Weston, FL
*
*              All rights reserved.  Protected by international copyright laws.
*
*              uC/PRODUCT is provided in source form to registered licensees ONLY.  It is
*              illegal to distribute this source code to any third party unless you receive
*              written permission by an authorized Micrium representative.  Knowledge of
*              the source code may NOT be used to develop a similar product.
*
*              Please help us continue to provide the Embedded community with the finest
*              software available.  Your honesty is greatly appreciated.
*
*              You can find our product's user manual, API reference, release notes and
*              more information at https://doc.micrium.com.
*              You can contact us at www.micrium.com.
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*
*                                      FILE SYSTEM DEVICE DRIVER
*
*                                          NOR FLASH DEVICES
*                             MICRON N25Q SERIAL NOR PHYSICAL-LAYER DRIVER
*
* Filename      : fs_dev_nor_n25q.h
* Version       : v4.07.00.00
* Programmer(s) : ED
*                 EJ
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               MODULE
*********************************************************************************************************
*/

#ifndef  FS_DEV_NOR_N25Q_PRESENT
#define  FS_DEV_NOR_N25Q_PRESENT


/*
*********************************************************************************************************
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*********************************************************************************************************
*/

#include  "../fs_dev_nor.h"
#include  "CmdIf/fs_dev_nor_cmd_if.h"


/*
*********************************************************************************************************
*********************************************************************************************************
*                                             DATA TYPES
*********************************************************************************************************
*********************************************************************************************************
*/

typedef struct fs_dev_nor_phy_n25q_cfg {
    FS_DEV_NOR_CMD_IF_API  *CmdIfPtr;                           /* Ptr to cmd if API structure.                         */
    void                   *CmdIfCfgPtr;                        /* Ptr to cmd if cfg structure.                         */

    CPU_BOOLEAN             QuadIOModeEn;                       /* DEF_ENABLED: quad mode, DEF_DISABLED: 1-bit mode.    */
    CPU_INT08U              DummyCycleCnt;                      /* Nbr of cycles to insert before fast rds. Effect ...  */
                                                                /* on max dev freq.                                     */
} FS_DEV_NOR_PHY_N25Q_CFG;


/*
*********************************************************************************************************
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*********************************************************************************************************
*/

#endif                                                          /* End of Micron N25Q module include.      */
