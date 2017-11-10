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
*                                        INTERRUPT MANAGEMENT
*
* Filename      : ucos_int.h
* Version       : V1.42
* Programmer(s) : JBL
*********************************************************************************************************
*/

#ifndef  UCOS_INT_PRESENT
#define  UCOS_INT_PRESENT

#include  <lib_def.h>
#include  <cpu.h>
#include  <ucos_int_impl.h>


/*
*********************************************************************************************************
*                                               DEFINES
*********************************************************************************************************
*/

typedef  void  (*UCOS_INT_FNCT_PTR)(void *, CPU_INT32U);

typedef  CPU_INT32U  UCOS_INT_TYPE;
#define  UCOS_INT_TYPE_LEVEL 0
#define  UCOS_INT_TYPE_EDGE 1


/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

CPU_BOOLEAN UCOS_IntInit (void);

CPU_BOOLEAN UCOS_IntSrcEn (CPU_INT32U int_id);

CPU_BOOLEAN UCOS_IntSrcDis (CPU_INT32U int_id);

CPU_BOOLEAN UCOS_IntPrioSet (CPU_INT32U int_id, CPU_INT32U int_prio);

CPU_BOOLEAN UCOS_IntTargetSet (CPU_INT32U int_id, CPU_INT32U int_target_list);

CPU_BOOLEAN UCOS_IntTypeSet (CPU_INT32U int_id, UCOS_INT_TYPE type);

CPU_BOOLEAN UCOS_IntVectSet (CPU_INT32U         int_id,
                             CPU_INT32U         int_prio,
                             CPU_INT08U         int_target_list,
                             UCOS_INT_FNCT_PTR  int_fnct,
                             void              *p_int_arg);

void BSP_IntHandler (void);


#endif /* UCOS_INT_PRESENT */
