/*
*********************************************************************************************************
*
*                                    MICRIUM BOARD SUPPORT PACKAGE
*
*                          (c) Copyright 2014-2015; Micrium, Inc.; Weston, FL
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
*                              AXI INTERRUPT CONTROLLER FOR THE MICROBLAZE
*
* Filename      : ucos_int_impl.c
* Version       : V1.42
* Programmer(s) : JBL
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#include  <app_cfg.h>
#include  <cpu_core.h>
#include  <cpu.h>
#include  <ucos_bsp.h>
#include  "ucos_int.h"
#include  <xparameters.h>

#if (UCOS_MB_INTC_TYPE == UCOS_MB_INTC_TYPE_AXIINTC)
#include  <ucos_axiintc.h>
#endif


/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/

#if (UCOS_MB_INTC_TYPE == UCOS_MB_INTC_TYPE_AXIINTC)
static  AXIINTC_HANDLE       IntCHandle;
#endif /* #if (UCOS_MB_INTC_TYPE == UCOS_MB_INTC_TYPE_AXIINTC) */

#if (UCOS_MB_INTC_TYPE == UCOS_MB_INTC_TYPE_AXIINTC)
static  UCOS_INT_FNCT_PTR    IntVectTbl[32];
static  void                *IntArgTbl[32];
#else /* #if (UCOS_MB_INTC_TYPE == UCOS_MB_INTC_TYPE_AXIINTC) */
static  UCOS_INT_FNCT_PTR    IntVectTbl[1];
static  void                *IntArgTbl[1];
#endif /* #if (UCOS_MB_INTC_TYPE == UCOS_MB_INTC_TYPE_AXIINTC) */


/*
*********************************************************************************************************
*********************************************************************************************************
**                                         GLOBAL FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            UCOS_IntInit()
*
* Description : Initialise UCOS BSP interrupts.
*
* Argument(s) : none.
*
* Return(s)   : DEF_OK     Operation successful.
*               DEF_FAIL   Operation failed.
*
* Note(s)     : Should be called only from the startup code. By default this is done inside the
*               UCOS_Startup() initialization routine.
*
*********************************************************************************************************
*/

CPU_BOOLEAN UCOS_IntInit (void)
{
#if (UCOS_MB_INTC_TYPE == UCOS_MB_INTC_TYPE_AXIINTC)
    IntCHandle = AXIIntCInit(0);
#endif

    return (DEF_OK);
}


/*
*********************************************************************************************************
*                                            UCOS_IntSrcEn()
*
* Description : Enable an interrupt source.
*
* Argument(s) : int_id     ID of the interrupt to enable.
*
* Return(s)   : DEF_OK     Operation successful.
*               DEF_FAIL   Operation failed.
*
* Note(s)     : none.
*
*********************************************************************************************************
*/

CPU_BOOLEAN UCOS_IntSrcEn (CPU_INT32U int_id)
{
#if (UCOS_MB_INTC_TYPE == UCOS_MB_INTC_TYPE_AXIINTC)
    return (AXIIntCIntEnSet(IntCHandle, int_id));
#else
    return (DEF_OK);
#endif
}


/*
*********************************************************************************************************
*                                            UCOS_IntSrcDis()
*
* Description : Disable an interrupt source.
*
* Argument(s) : int_id     ID of the interrupt to disable.
*
* Return(s)   : DEF_OK     Operation successful.
*               DEF_FAIL   Operation failed.
*
* Note(s)     : UCOS_IntSrcDis() won't clear a pending interrupt.
*
*********************************************************************************************************
*/

CPU_BOOLEAN UCOS_IntSrcDis (CPU_INT32U int_id)
{
#if (UCOS_MB_INTC_TYPE == UCOS_MB_INTC_TYPE_AXIINTC)
    return (AXIIntCIntEnClr(IntCHandle, int_id));
#else
    return (DEF_OK);
#endif
}


/*
*********************************************************************************************************
*                                            UCOS_IntVectSet()
*
* Description : Register an interrupt handler.
*
* Argument(s) : int_id     ID of the interrupt to register.
*               int_fnct   Handler to register.
*               p_int_arg  Argument given to the handler.
*
* Return(s)   : DEF_OK     Operation successful.
*               DEF_FAIL   Operation failed.
*
* Note(s)     : An interrupt handler has the following signature :
*
*               void Handler (void *p_int_arg, CPU_INT32U source_cpu)
*               {
*               }
*
*               On the MicroBlaze the second argument is always the current cpu, 0.
*
*********************************************************************************************************
*/

CPU_BOOLEAN UCOS_IntVectSet (CPU_INT32U         int_id,
                             CPU_INT32U         int_prio,
                             CPU_INT08U         int_target_list,
                             UCOS_INT_FNCT_PTR  int_fnct,
                             void              *p_int_arg)
{
    CPU_SR_ALLOC();

    CPU_CRITICAL_ENTER();
    IntVectTbl[int_id] = int_fnct;
    IntArgTbl[int_id] = p_int_arg;
    CPU_CRITICAL_EXIT();

    return (DEF_OK);
}


/*
*********************************************************************************************************
*                                            UCOS_IntTypeSet()
*
* Description : Configure the trigger type on an interrupt source.
*
* Argument(s) : int_id     ID of the interrupt to disable.
*               type       Interrupt type.
*                   UCOS_INT_TYPE_LEVEL - Level sensitivity
*                   UCOS_INT_TYPE_EDGE  - Edge sensitivity
*
* Return(s)   : DEF_OK     Operation successful.
*               DEF_FAIL   Operation failed.
*
* Note(s)     : The AXI interrupt sensitivity is fixed and cannot be changed at runtime.
*
*********************************************************************************************************
*/

CPU_BOOLEAN UCOS_IntTypeSet (CPU_INT32U int_id, UCOS_INT_TYPE type)
{
    return (DEF_OK);
}


/*
*********************************************************************************************************
*                                            BSP_IntHandler()
*
* Description : Global interrupt handler.
*
* Argument(s) : int_id     ID of the interrupt to enable.
*
* Return(s)   : DEF_OK     Operation successful.
*               DEF_FAIL   Operation failed.
*
* Note(s)     : none.
*
*********************************************************************************************************
*/

/* TODO - Handle the case where IPR isn't available. */
void BSP_IntHandler (void)
{
#if (UCOS_MB_INTC_TYPE == UCOS_MB_INTC_TYPE_AXIINTC)
    AXIINTC_PTR        intc;
    CPU_INT32U         int_id;
#endif
    UCOS_INT_FNCT_PTR  int_handler;
    void              *p_int_arg;

#if (UCOS_MB_INTC_TYPE == UCOS_MB_INTC_TYPE_AXIINTC)
    intc = IntCHandle->AXIIntC;

    int_id = CPU_CntTrailZeros(intc->IPR);                      /* Fetch the highest priority interrupt pending.        */

    int_handler = IntVectTbl[int_id];
    p_int_arg   = IntArgTbl[int_id];

    if (int_handler != DEF_NULL) {
        (int_handler)(p_int_arg, 0);
    }

    intc->IAR = (1 << int_id);                                  /* Acknowledge the interrupt.                           */
#else
    int_handler = IntVectTbl[0];
    p_int_arg   = IntArgTbl[0];

    (int_handler)(p_int_arg, 0);
#endif
}
