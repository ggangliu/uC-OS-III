/*
*********************************************************************************************************
*
*                                    MICRIUM BOARD SUPPORT PACKAGE
*
*                        (c) Copyright 2014-2015; Micrium, Inc.; Weston, FL
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
*                                       uC/USB-Device INIT CODE
*
* Filename      : ucos_usbd_init.c
* Version       : V1.42
* Programmer(s) : JBL
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#include <app_cfg.h>
#include <cpu.h>
#include <ucos_bsp.h>
#include <ucos_int.h>
#include <xparameters.h>
#include <KAL/kal.h>

#if ((APP_USBD_ENABLED == DEF_ENABLED) && (UCOS_USB_TYPE == UCOS_USB_TYPE_DEVICE))
#include  <Source/usbd_core.h>
#include  "usbd_dev_cfg.h"

CPU_BOOLEAN UCOS_USBD_Init (void)
{
    CPU_INT08U   dev_nbr;
    USBD_ERR     usbd_err;

#if (UCOS_START_DEBUG_TRACE == DEF_ENABLED)
    UCOS_Print("UCOS - Initializing uC/USB-Device.\r\n");
#endif

    USBD_Init(&usbd_err);
    if (usbd_err != USBD_ERR_NONE) {
#if (UCOS_START_DEBUG_TRACE == DEF_ENABLED)
        UCOS_Printf("UCOS - Error initializing uC/USB-Device. USBD_Init() returned error code %d\r\n", usbd_err);
#endif
        return (DEF_FAIL);
    }

    return (DEF_OK);
}

#endif /* #if (APP_USBD_ENABLED == DEF_ENABLED) */
