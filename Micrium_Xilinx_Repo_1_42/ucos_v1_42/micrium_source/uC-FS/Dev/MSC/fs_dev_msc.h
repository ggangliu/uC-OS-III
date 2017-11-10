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
*                                     USB HOST MASS STORAGE CLASS
*                                           for uC/USB-Host
*
* Filename      : fs_dev_msc.h
* Version       : v4.07.00.00
* Programmer(s) : BAN
*********************************************************************************************************
* Note(s)       : (1) Assumes uC/USB-Host V3.10, 3.30 or 3.40 is included in the project build.
*
*                     (a) Since version 3.40 of uC/USB-Host, USB_VERSION has been renamed to USBH_VERSION.
*
*                 (2) REQUIREs the following uC/USB features :
*
*                     (a) Host stack.
*
*                     (b) Host Mass Storage Class (MSC) driver.
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               MODULE
*********************************************************************************************************
*/

#ifndef  FS_DEV_MSC_PRESENT
#define  FS_DEV_MSC_PRESENT


/*
*********************************************************************************************************
*                                               EXTERNS
*********************************************************************************************************
*/

#ifdef   FS_DEV_MSC_MODULE
#define  FS_DEV_MSC_EXT
#else
#define  FS_DEV_MSC_EXT  extern
#endif


/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include  "../../Source/fs_dev.h"
#include  <Class/MSC/usbh_msc.h>


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

extern          const  FS_DEV_API  FSDev_MSC;


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

FS_QTY  FSDev_MSC_DevOpen (USBH_MSC_DEV  *p_msc_dev,
                           FS_ERR        *p_err);

void    FSDev_MSC_DevClose(USBH_MSC_DEV  *p_msc_dev);


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

#endif                                                          /* End of MSC module include.                           */
