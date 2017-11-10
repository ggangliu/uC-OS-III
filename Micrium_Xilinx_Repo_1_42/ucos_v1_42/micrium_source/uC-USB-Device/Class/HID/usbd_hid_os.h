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
*                                USB HID CLASS OPERATING SYSTEM LAYER
*
* File          : usbd_hid_os.h
* Version       : V4.05.00
* Programmer(s) : FGK
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               MODULE
*********************************************************************************************************
*/

#ifndef  USBD_HID_OS_MODULE_PRESENT
#define  USBD_HID_OS_MODULE_PRESENT


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

void  USBD_HID_OS_Init               (USBD_ERR    *p_err);


void  USBD_HID_OS_InputLock          (CPU_INT08U   class_nbr,
                                      USBD_ERR    *p_err);

void  USBD_HID_OS_InputUnlock        (CPU_INT08U   class_nbr);

void  USBD_HID_OS_InputDataPend      (CPU_INT08U   class_nbr,
                                      CPU_INT16U   timeout_ms,
                                      USBD_ERR    *p_err);

void  USBD_HID_OS_InputDataPendAbort (CPU_INT08U   class_nbr);

void  USBD_HID_OS_InputDataPost      (CPU_INT08U   class_nbr);


void  USBD_HID_OS_OutputLock         (CPU_INT08U   class_nbr,
                                      USBD_ERR    *p_err);

void  USBD_HID_OS_OutputUnlock       (CPU_INT08U   class_nbr);

void  USBD_HID_OS_OutputDataPendAbort(CPU_INT08U   class_nbr);

void  USBD_HID_OS_OutputDataPend     (CPU_INT08U   class_nbr,
                                      CPU_INT16U   timeout_ms,
                                      USBD_ERR    *p_err);

void  USBD_HID_OS_OutputDataPost     (CPU_INT08U   class_nbr);


void  USBD_HID_OS_TxLock             (CPU_INT08U   class_nbr,
                                      USBD_ERR    *p_err);

void  USBD_HID_OS_TxUnlock           (CPU_INT08U   class_nbr);


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
