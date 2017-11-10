/*
*********************************************************************************************************
*
*                                    MICRIUM BOARD SUPPORT PACKAGE
*
*                       (c) Copyright 2014-2015; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*
*               This BSP is provided in source form to registered licensees ONLY.  It is
*               illegal to distribute this source code to any third party unless you receive
*               written permission by an authorized Micrium representative.  Knowledge of
*               the source code may NOT be used to develop a similar product.
*
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*
*               You can contact us at www.micrium.com.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                    MICRIUM BOARD SUPPORT PACKAGE
*
* Filename      : usbd_storage.h
* Version       : V1.42
* Programmer(s) : JBL
*********************************************************************************************************
*/

#include <xparameters.h>
#include <ucos_bsp.h>

#if (UCOS_USBD_STORAGE_DRV == UCOS_USBD_STORAGE_DRV_FS)
#include "Class/MSC/Storage/uC-FS/V4/usbd_storage.h"
#else
#include "Class/MSC/Storage/RAMDisk/usbd_storage.h"
#endif