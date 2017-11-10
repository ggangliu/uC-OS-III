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
* Filename      : ucos_dev_cfg.h
* Version       : V1.42
* Programmer(s) : JBL
*********************************************************************************************************
*/

#include  <Source/usbd_core.h>

#include  <ucos_bsp.h>
#include  <xparameters.h>

#if (UCOS_USB_DRIVER == UCOS_USB_USBPS)
#include  "usbd_bsp_ps7_usb.h"

USBD_DRV_CFG  UCOS_USBD_DrvCfg_PS7 = {
#if (UCOS_USB_DEVICE_ID == 1)
        XPAR_UCOS_USBPS_1_BASEADDR,
#else
        XPAR_UCOS_USBPS_0_BASEADDR,
#endif
        0,
        0,
        USBD_DEV_SPD_HIGH,
        USBD_DrvEP_InfoTbl_PS7_USB
    };
#endif
