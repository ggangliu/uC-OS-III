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
*                                    USB DEVICE CONFIGURATION FILE
*
*                                              TEMPLATE
*
* File          : usbd_dev_cfg.h
* Version       : V4.05.00
* Programmer(s) : FGK
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                               MODULE
*
* Note(s) : (1) This USB device configuration header file is protected from multiple pre-processor
*               inclusion through use of the USB device configuration module present pre-processor
*               macro definition.
*********************************************************************************************************
*/

#ifndef  USBD_DEV_CFG_MODULE_PRESENT                            /* See Note #1.                                         */
#define  USBD_DEV_CFG_MODULE_PRESENT


/*
*********************************************************************************************************
*                                      USB DEVICE CONFIGURATION
*********************************************************************************************************
*/

extern  const USBD_DEV_CFG  USBD_DevCfg_Template;


/*
*********************************************************************************************************
*                                   USB DEVICE DRIVER CONFIGURATION
*********************************************************************************************************
*/

extern  const USBD_DRV_CFG  USBD_DrvCfg_Template;


/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif
