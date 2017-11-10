/*
*********************************************************************************************************
*                                            uC/USB-Device
*                                       The Embedded USB Stack
*
*                         (c) Copyright 2004-2014; Micrium, Inc.; Weston, FL
*
*                  All rights reserved.  Protected by international copyright laws.
*
*                  uC/USB-Device is provided in source form to registered licensees ONLY.  It is
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
*                                 USB DEVICE MSC CLASS STORAGE DRIVER
*
*                                              uC/FS V4
*
* File           : usbd_storage.h
* Version        : V4.05.00
* Programmer(s)  : PW
*                  JB
*                  CM
*********************************************************************************************************
*/


/*
**********************************************************************************************************
*                                                  MODULE
**********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                              INCLUDE FILES
*********************************************************************************************************
*/

#include  "../../../../../Source/usbd_core.h"
#include  "../../../usbd_scsi.h"
#include  <fs_cfg.h>


/*
*********************************************************************************************************
*                                                 EXTERNS
*********************************************************************************************************
*/

#ifdef   STORAGE_MODULE
#define  STORAGE_EXT
#else
#define  STORAGE_EXT  extern
#endif


/*
*********************************************************************************************************
*                                                 DEFINES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               DATA TYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            GLOBAL VARIABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                                 MACRO'S
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                           FUNCTION PROTOTYPES
*********************************************************************************************************
*/

void  USBD_StorageInit              (USBD_ERR          *p_err);

void  USBD_StorageAdd               (USBD_STORAGE_LUN  *p_storage_lun,
                                     USBD_ERR          *p_err);

void  USBD_StorageCapacityGet       (USBD_STORAGE_LUN  *p_storage_lun,
                                     CPU_INT64U        *p_nbr_blks,
                                     CPU_INT32U        *p_blk_size,
                                     USBD_ERR          *p_err);

void  USBD_StorageRd                (USBD_STORAGE_LUN  *p_storage_lun,
                                     CPU_INT64U         blk_addr,
                                     CPU_INT32U         nbr_blks,
                                     CPU_INT08U        *p_data_buf,
                                     USBD_ERR          *p_err);

void  USBD_StorageWr                (USBD_STORAGE_LUN  *p_storage_lun,
                                     CPU_INT64U         blk_addr,
                                     CPU_INT32U         nbr_blks,
                                     CPU_INT08U        *p_data_buf,
                                     USBD_ERR          *p_err);

void  USBD_StorageStatusGet         (USBD_STORAGE_LUN  *p_storage_lun,
                                     USBD_ERR          *p_err);

void  USBD_StorageLock              (USBD_STORAGE_LUN  *p_storage_lun,
                                     CPU_INT32U         timeout_ms,
                                     USBD_ERR          *p_err);

void  USBD_StorageUnlock            (USBD_STORAGE_LUN  *p_storage_lun,
                                     USBD_ERR          *p_err);

#if (USBD_MSC_CFG_FS_REFRESH_TASK_EN == DEF_ENABLED)
void  USBD_StorageRefreshTaskHandler(void *p_arg);
#endif


/*
*********************************************************************************************************
*                                          CONFIGURATION ERRORS
*********************************************************************************************************
*/

#ifndef  USBD_MSC_CFG_FS_REFRESH_TASK_EN
#error  "USBD_MSC_CFG_FS_REFRESH_TASK_EN not #defined'd in 'usbd_cfg.h' [MUST be DEF_ENABLED or DEF_DISABLED]"
#endif


/*
**********************************************************************************************************
*                                           MODULE END
**********************************************************************************************************
*/




