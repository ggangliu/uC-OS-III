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
*                                        USB DEVICE VENDOR CLASS
*
* File          : usbd_vendor.h
* Version       : V4.05.00
* Programmer(s) : CM
*                 FGK
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               MODULE
*********************************************************************************************************
*/

#ifndef  USBD_VENDOR_MODULE_PRESENT
#define  USBD_VENDOR_MODULE_PRESENT


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

#ifdef   USBD_VENDOR_MODULE
#define  USBD_VENDOR_EXT
#else
#define  USBD_VENDOR_EXT  extern
#endif


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

                                                                /* App callback used for vendor-specific req.           */
typedef  CPU_BOOLEAN  (*USBD_VENDOR_REQ_FNCT)  (       CPU_INT08U       class_nbr,
                                                       CPU_INT08U       dev_nbr,
                                                const  USBD_SETUP_REQ  *p_setup_req);

                                                                /* App callback used for async comm.                    */
typedef  void         (*USBD_VENDOR_ASYNC_FNCT)(       CPU_INT08U       class_nbr,
                                                       void            *p_buf,
                                                       CPU_INT32U       buf_len,
                                                       CPU_INT32U       xfer_len,
                                                       void            *p_callback_arg,
                                                       USBD_ERR         err);


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


void         USBD_Vendor_Init             (       USBD_ERR                *p_err);

CPU_INT08U   USBD_Vendor_Add              (       CPU_BOOLEAN              intr_en,
                                                  CPU_INT16U               interval,
                                                  USBD_VENDOR_REQ_FNCT     req_callback,
                                                  USBD_ERR                *p_err);

void         USBD_Vendor_CfgAdd           (       CPU_INT08U               class_nbr,
                                                  CPU_INT08U               dev_nbr,
                                                  CPU_INT08U               cfg_nbr,
                                                  USBD_ERR                *p_err);

CPU_BOOLEAN  USBD_Vendor_IsConn           (       CPU_INT08U               class_nbr);

#if (USBD_CFG_MS_OS_DESC_EN == DEF_ENABLED)
void         USBD_Vendor_MS_ExtPropertyAdd(       CPU_INT08U               class_nbr,
                                                  CPU_INT08U               property_type,
                                           const  CPU_INT08U              *p_property_name,
                                                  CPU_INT16U               property_name_len,
                                           const  CPU_INT08U              *p_property,
                                                  CPU_INT32U               property_len,
                                                  USBD_ERR                *p_err);
#endif

CPU_INT32U   USBD_Vendor_Rd               (       CPU_INT08U               class_nbr,
                                                  void                    *p_buf,
                                                  CPU_INT32U               buf_len,
                                                  CPU_INT16U               timeout,
                                                  USBD_ERR                *p_err);

CPU_INT32U   USBD_Vendor_Wr               (       CPU_INT08U               class_nbr,
                                                  void                    *p_buf,
                                                  CPU_INT32U               buf_len,
                                                  CPU_INT16U               timeout,
                                                  CPU_BOOLEAN              end,
                                                  USBD_ERR                *p_err);

void         USBD_Vendor_RdAsync          (       CPU_INT08U               class_nbr,
                                                  void                    *p_buf,
                                                  CPU_INT32U               buf_len,
                                                  USBD_VENDOR_ASYNC_FNCT   async_fnct,
                                                  void                    *p_async_arg,
                                                  USBD_ERR                *p_err);

void         USBD_Vendor_WrAsync          (       CPU_INT08U               class_nbr,
                                                  void                    *p_buf,
                                                  CPU_INT32U               buf_len,
                                                  USBD_VENDOR_ASYNC_FNCT   async_fnct,
                                                  void                    *p_async_arg,
                                                  CPU_BOOLEAN              end,
                                                  USBD_ERR                *p_err);

CPU_INT32U   USBD_Vendor_IntrRd           (       CPU_INT08U               class_nbr,
                                                  void                    *p_buf,
                                                  CPU_INT32U               buf_len,
                                                  CPU_INT16U               timeout,
                                                  USBD_ERR                *p_err);

CPU_INT32U   USBD_Vendor_IntrWr           (       CPU_INT08U               class_nbr,
                                                  void                     *p_buf,
                                                  CPU_INT32U               buf_len,
                                                  CPU_INT16U               timeout,
                                                  CPU_BOOLEAN              end,
                                                  USBD_ERR                *p_err);

void         USBD_Vendor_IntrRdAsync      (       CPU_INT08U               class_nbr,
                                                  void                    *p_buf,
                                                  CPU_INT32U               buf_len,
                                                  USBD_VENDOR_ASYNC_FNCT   async_fnct,
                                                  void                    *p_async_arg,
                                                  USBD_ERR                *p_err);

void         USBD_Vendor_IntrWrAsync      (       CPU_INT08U               class_nbr,
                                                  void                    *p_buf,
                                                  CPU_INT32U               buf_len,
                                                  USBD_VENDOR_ASYNC_FNCT   async_fnct,
                                                  void                    *p_async_arg,
                                                  CPU_BOOLEAN              end,
                                                  USBD_ERR                *p_err);


/*
*********************************************************************************************************
*                                        CONFIGURATION ERRORS
*********************************************************************************************************
*/

#ifndef  USBD_VENDOR_CFG_MAX_NBR_DEV
#error  "USBD_VENDOR_CFG_MAX_NBR_DEV not #define'd in 'usbd_cfg.h' [MUST be >= 1]"
#endif

#if     (USBD_VENDOR_CFG_MAX_NBR_DEV < 1u)
#error  "USBD_VENDOR_CFG_MAX_NBR_DEV illegally #define'd in 'usbd_cfg.h' [MUST be >= 1]"
#endif

#ifndef  USBD_VENDOR_CFG_MAX_NBR_CFG
#error  "USBD_VENDOR_CFG_MAX_NBR_CFG not #define'd in 'usbd_cfg.h' [MUST be >= 1]"
#endif

#if     (USBD_VENDOR_CFG_MAX_NBR_CFG < 1u)
#error  "USBD_VENDOR_CFG_MAX_NBR_CFG illegally #define'd in 'usbd_cfg.h' [MUST be >= 1]"
#endif

#if (USBD_CFG_MS_OS_DESC_EN == DEF_ENABLED)
#ifndef  USBD_VENDOR_CFG_MAX_NBR_MS_EXT_PROPERTY
#error  "USBD_VENDOR_CFG_MAX_NBR_MS_EXT_PROPERTY not #define'd in 'usbd_cfg.h' [MUST be >= 1]"
#endif

#if     (USBD_VENDOR_CFG_MAX_NBR_MS_EXT_PROPERTY < 1u)
#error  "USBD_VENDOR_CFG_MAX_NBR_MS_EXT_PROPERTY illegally #define'd in 'usbd_cfg.h' [MUST be >= 1]"
#endif
#endif


/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif
