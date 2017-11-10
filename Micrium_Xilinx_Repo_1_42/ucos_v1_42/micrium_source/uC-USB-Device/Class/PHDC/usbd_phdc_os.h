/*
*********************************************************************************************************
*                                            uC/USB-Device
*                                       The Embedded USB Stack
*
*                         (c) Copyright 2004-2013; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*
*               uC/USB is provided in source form to registered licensees ONLY.  It is
*               illegal to distribute this source code to any third party unless you receive
*               written permission by an authorized Micrium representative.  Knowledge of
*               the source code may NOT be used to develop a similar product.
*
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*
*               You can find our product's user manual, API reference, release notes and
*               more information at https://doc.micrium.com.
*               You can contact us at www.micrium.com.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                USB PHDC CLASS OPERATING SYSTEM LAYER
*
* File          : usbd_phdc_os.h
* Version       : V4.05.00
* Programmer(s) : JFD
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               MODULE
*********************************************************************************************************
*/

#ifndef  USBD_PHDC_OS_MODULE_PRESENT
#define  USBD_PHDC_OS_MODULE_PRESENT


/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include  "../../Source/usbd_core.h"


/*
*********************************************************************************************************
*                                               EXTERNS
*********************************************************************************************************
*/


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

void  USBD_PHDC_OS_Init        ( USBD_ERR   *p_err);

void  USBD_PHDC_OS_RdLock      (CPU_INT08U   class_nbr,
                                CPU_INT16U   timeout,
                                USBD_ERR    *p_err);

void  USBD_PHDC_OS_RdUnlock    (CPU_INT08U   class_nbr);


void  USBD_PHDC_OS_WrBulkLock  (CPU_INT08U   class_nbr,
                                CPU_INT08U   prio,
                                CPU_INT16U   timeout,
                                USBD_ERR    *p_err);

void  USBD_PHDC_OS_WrBulkUnlock(CPU_INT08U   class_nbr);

void  USBD_PHDC_OS_WrIntrLock  (CPU_INT08U   class_nbr,
                                CPU_INT16U   timeout,
                                USBD_ERR    *p_err);

void  USBD_PHDC_OS_WrIntrUnlock(CPU_INT08U   class_nbr);

void  USBD_PHDC_OS_Reset       (CPU_INT08U   class_nbr);


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
