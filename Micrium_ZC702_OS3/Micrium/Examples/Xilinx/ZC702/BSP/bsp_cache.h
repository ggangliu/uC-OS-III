/*
*********************************************************************************************************
*
*                                    MICRIUM BOARD SUPPORT PACKAGE
*
*                          (c) Copyright 2003-2013; Micrium, Inc.; Weston, FL
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
*                                       Cache utility functions
*                                ZYNQ-7000 EPP & ZC702 Evaluation Kit
*
* Filename      : bsp_cache.h
* Version       : V1.00
* Programmer(s) : JBL
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               MODULE
*
* Note(s) : (1) This BSP header file is protected from multiple pre-processor inclusion through
*               use of the BSP present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef  BSP_CACHE_PRESENT                                      /* See Note #1.                                         */
#define  BSP_CACHE_PRESENT


/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

void  BSP_DCacheInvalidateAll     (void);

void  BSP_BranchPredictorEn       (void);

void  BSP_L2C310Config            (void);

void  BSP_CachesEn                (void);

void  BSP_SCUEn                   (void);

void  BSP_DCache_InvalidateRange  (void       *p_mem,
                                   CPU_SIZE_T  range);

void  BSP_DCache_FlushRange       (void       *p_mem,
                                   CPU_SIZE_T  range);


#endif /* BSP_CACHE_PRESENT  */
