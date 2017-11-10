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
*                                Cortex-A9 (ps7) Interrupt Management
*
* Filename      : ucos_int_impl.c
* Version       : V1.20
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

#include  <ucos_scugic.h>

#include  <os_cpu.h>

#include  <ucos_int_ipi.h>


/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/

static  UCOS_INT_FNCT_PTR    IntVectTbl[128];
static  void                *IntArgTbl[128];

void UCOS_Int_FIQ_Handler (void) __attribute__ ((weak));

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

#if (UCOS_AMP_MASTER == DEF_ENABLED)                            /* Only the master core should enable the distributor.  */
                                                                /* Enable the GIC.                                      */
    SCUGIC_DIST_REG->ICDDCR |= SCUGIC_DIST_ICDDCR_EN;
#endif /* #if (UCOS_AMP_MASTER == DEF_ENABLED) */

                                                                /* Enable the GIC interface.                            */
    SCUGIC_IF_REG->ICCICR |= (SCUGIC_IF_ICCICR_ENS | SCUGIC_IF_ICCICR_ENNS | SCUGIC_IF_ICCICR_ACKCTL);

    CPU_IntEn();

    SCUGIC_PrioMaskSet(0xFFu);

    UCOS_IntIPIInit();

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
    CPU_INT32U  reg_off;
    CPU_INT32U  reg_bit;
    CPU_SR_ALLOC();


    if(int_id >= SCUGIC_INT_SRC_CNT) {
        return (DEF_NULL);
    }

    CPU_CRITICAL_ENTER();
    reg_off = int_id >> 5u;                                     /* Calculate the register offset.                       */

    reg_bit = int_id & 0x1F;                                    /* Mask bit ID.                                         */

    SCUGIC_DIST_REG->ICDISERn[reg_off] = 1u << reg_bit;
    CPU_CRITICAL_EXIT();

    return (DEF_OK);
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
    CPU_INT32U  reg_off;
    CPU_INT32U  reg_bit;
    CPU_SR_ALLOC();


    if(int_id >= SCUGIC_INT_SRC_CNT) {
        return (DEF_FAIL);
    }

    CPU_CRITICAL_ENTER();
    reg_off = int_id >> 5u;                                     /* Calculate the register offset.                       */

    reg_bit = int_id & 0x1F;                                    /* Mask bit ID.                                         */

    SCUGIC_DIST_REG->ICDICERn[reg_off] = 1u << reg_bit;
    CPU_CRITICAL_EXIT();

    return (DEF_FAIL);
}


/*
*********************************************************************************************************
*                                            UCOS_IntPrioSet()
*
* Description : Configure the priority of an interrupt source.
*
* Argument(s) : int_id     ID of the interrupt to disable.
*               int_prio   Interrupt priority.
*
* Return(s)   : DEF_OK     Operation successful.
*               DEF_FAIL   Operation failed.
*
* Note(s)     : none.
*
*********************************************************************************************************
*/

CPU_BOOLEAN UCOS_IntPrioSet (CPU_INT32U int_id, CPU_INT32U int_prio)
{

    if (int_prio > 255u) {
        return (DEF_FAIL);
    }

    SCUGIC_PrioSet(int_id, int_prio);

    return (DEF_OK);
}


/*
*********************************************************************************************************
*                                            UCOS_IntTargetSet()
*
* Description : Configure the target list of an interrupt source.
*
* Argument(s) : int_target_list     ID of the interrupt to disable.
*               int_prio   Interrupt priority.
*
* Return(s)   : DEF_OK     Operation successful.
*               DEF_FAIL   Operation failed.
*
* Note(s)     : none.
*
*********************************************************************************************************
*/

CPU_BOOLEAN UCOS_IntTargetSet (CPU_INT32U int_id, CPU_INT32U int_target_list)
{
    CPU_INT32U int_target;


    if (int_target_list > 0xF) {
        return (DEF_FAIL);
    }

    if (int_target_list == 0u) {
        int_target = 1 << XPAR_CPU_ID;
    } else {
        int_target = int_target_list;
    }

    SCUGIC_TargetSet(int_id, int_target);

    return (DEF_OK);
}


/*
*********************************************************************************************************
*                                            UCOS_IntVectSet()
*
* Description : Register an interrupt handler.
*
* Argument(s) : int_id           ID of the interrupt to register.
*               int_prio         Interrupt priority.
*               int_target_list  List of CPU that can be interrupted or 0 for the current CPU.
*               int_fnct         Handler to register.
*               p_int_arg        Argument given to the handler.
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
*********************************************************************************************************
*/

CPU_BOOLEAN UCOS_IntVectSet (CPU_INT32U         int_id,
                             CPU_INT32U         int_prio,
                             CPU_INT08U         int_target_list,
                             UCOS_INT_FNCT_PTR  int_fnct,
                             void              *p_int_arg)
{
    CPU_INT32U int_target;
    CPU_SR_ALLOC();


    if (int_id >= SCUGIC_INT_SRC_CNT) {
        return (DEF_FAIL);
    }

    if (int_prio > 255u) {
        return (DEF_FAIL);
    }

    if (int_target_list > 0xF) {
        return (DEF_FAIL);
    }

    CPU_CRITICAL_ENTER();
    IntVectTbl[int_id] = int_fnct;
    IntArgTbl[int_id] = p_int_arg;

    if (int_target_list == 0u) {
        int_target = 1 << XPAR_CPU_ID;
    } else {
        int_target = int_target_list;
    }

    SCUGIC_TargetSet(int_id, int_target);
    SCUGIC_PrioSet(int_id, int_prio);
    CPU_CRITICAL_EXIT();

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

void UCOS_IntHandler (void)
{
    CPU_INT32U         int_ack;
    CPU_INT32U         int_id;
    CPU_INT32U         int_cpu;
    void               *p_int_arg;
    UCOS_INT_FNCT_PTR  p_isr;


    int_ack = SCUGIC_IF_REG->ICCIAR;                            /* Acknowledge the interrupt.                           */

    int_id = int_ack & DEF_BIT_FIELD(10u, 0u);                  /* Mask away the CPUID.                                 */

    if(int_id == 1023u) {                                       /* Spurious interrupt.                                  */
        return;
    }

    int_cpu = (int_ack & DEF_BIT_FIELD(12u, 2u)) >> 10u;        /* Extract the interrupt source.                        */

    p_isr = IntVectTbl[int_id];                                 /* Fetch ISR handler.                                   */
    p_int_arg = IntArgTbl[int_id];

    if(p_isr != DEF_NULL) {
        (*p_isr)(p_int_arg, int_cpu);                           /* Call ISR handler.                                    */
    }

    CPU_MB();                                                   /* Memory barrier before ack'ing the interrupt.         */

    SCUGIC_IF_REG->ICCEOIR = int_id;                            /* Acknowledge the interrupt.                           */
}


/*
 *********************************************************************************************************
 *                                          OS_CPU_ExceptHndlr()
 *
 * Description : Handle any exceptions.
 *
 * Argument(s) : except_id     ARM exception type:
 *
 *                                  OS_CPU_ARM_EXCEPT_RESET             0x00
 *                                  OS_CPU_ARM_EXCEPT_UNDEF_INSTR       0x01
 *                                  OS_CPU_ARM_EXCEPT_SWI               0x02
 *                                  OS_CPU_ARM_EXCEPT_PREFETCH_ABORT    0x03
 *                                  OS_CPU_ARM_EXCEPT_DATA_ABORT        0x04
 *                                  OS_CPU_ARM_EXCEPT_ADDR_ABORT        0x05
 *                                  OS_CPU_ARM_EXCEPT_IRQ               0x06
 *                                  OS_CPU_ARM_EXCEPT_FIQ               0x07
 *
 * Return(s)   : none.
 *
 * Caller(s)   : OS_CPU_ARM_EXCEPT_HANDLER(), which is declared in os_cpu_a.s.
 *
 * Note(s)     : (1) Only OS_CPU_ARM_EXCEPT_FIQ and OS_CPU_ARM_EXCEPT_IRQ exceptions handler are implemented.
 *                   For the rest of the exception a infinite loop is implemented for debuging pruposes. This behavior
 *                   should be replaced with another behavior (reboot, etc).
 *********************************************************************************************************
 */
/* TODO - Consider defining default fault handlers as weak symbols for convenience. */
void OS_CPU_ExceptHndlr(CPU_INT32U except_id) {

    switch (except_id) {
    case OS_CPU_ARM_EXCEPT_FIQ:
        UCOS_Int_FIQ_Handler();
        break;

    case OS_CPU_ARM_EXCEPT_IRQ:
        UCOS_IntHandler();
        break;

    case OS_CPU_ARM_EXCEPT_RESET:
    case OS_CPU_ARM_EXCEPT_UNDEF_INSTR:
    case OS_CPU_ARM_EXCEPT_SWI:
    case OS_CPU_ARM_EXCEPT_PREFETCH_ABORT:
    case OS_CPU_ARM_EXCEPT_DATA_ABORT:
    case OS_CPU_ARM_EXCEPT_ADDR_ABORT:
    default:

        while (DEF_TRUE) { /* Infinite loop on other exceptions. (see note #1)          */
            CPU_WaitForEvent();
        }
    }
}


/*
*********************************************************************************************************
*                                          UCOS_Int_FIQ_Handler()
*
* Description : Custom FIQ handler.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Note(s)     : none.
*
*********************************************************************************************************
*/

void UCOS_Int_FIQ_Handler (void)
{

}
