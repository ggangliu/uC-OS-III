/*
*********************************************************************************************************
*                                               uC/Clk
*                                             Clock module
*
*                      (c) Copyright 2004-2014; Micrium, Inc.; Weston, FL
*
*          All rights reserved.  Protected by international copyright laws.
*
*          uC/Clk is provided in source form to registered licensees ONLY.  It is
*          illegal to distribute this source code to any third party unless you receive
*          written permission by an authorized Micrium representative.  Knowledge of
*          the source code may NOT be used to develop a similar product.
*
*          Please help us continue to provide the Embedded community with the finest
*          software available.  Your honesty is greatly appreciated.
*
*          You can find our product's user manual, API reference, release notes and
*          more information at: https://doc.micrium.com
*
*          You can contact us at: www.micrium.com
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                         CLK CMD SOURCE CODE
*
* Filename      : clk_type.h
* Version       : V3.10.00
* Programmer(s) : AA
*                 AOP
*********************************************************************************************************
* Note(s)       : none.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                               MODULE
*********************************************************************************************************
*/

#ifndef  CLK_TYPE_MODULE_PRESENT
#define  CLK_TYPE_MODULE_PRESENT


/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include  <cpu.h>


/*
*********************************************************************************************************
*                                             DATA TYPES
*
* Note(s): (1) When the Stack pointer is defined as null pointer (DEF_NULL), the task's stack should be
*              automatically allocated on the heap of uC/LIB.
*********************************************************************************************************
*/

typedef  struct  clk_task_cfg {
    CPU_INT32U   Prio;                                          /* Task priority.                                       */
    CPU_INT32U   StkSizeBytes;                                  /* Size of the stack.                                   */
    void        *StkPtr;                                        /* Pointer to base of the stack (see Note #1).          */
} CLK_TASK_CFG;


#endif  /* CLK_TYPE_MODULE_PRESENT */
