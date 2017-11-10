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
*                                CORTEX A GENERIC INTERRUPT CONTROLLER
*
* Filename      : bsp_int.c
* Version       : V1.00
* Programmer(s) : JBL
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#include  <cpu.h>
#include  <lib_def.h>

#include  <bsp.h>
#include  <bsp_int.h>

/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/

#define  BSP_INT_GIC_DIST_REG         ((ARM_REG_GIC_DIST_PTR)(ARM_PRIV_PERIPH_BASE + 0x1000u))
#define  BSP_INT_GIC_IF_REG           ((ARM_REG_GIC_IF_PTR)(ARM_PRIV_PERIPH_BASE + 0x100u))


/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/

static  BSP_INT_FNCT_PTR BSP_IntVectTbl[ARM_GIC_INT_SRC_CNT];   /* Interrupt vector table.                              */

                                                                /* ------------ GIC DISTRIBUTOR INTERFACE ------------- */
typedef  struct  arm_reg_gic_dist {
    CPU_REG32  ICDDCR;                                          /* Distributor Control Register.                        */
    CPU_REG32  ICDICTR;                                         /* Interrupt Controller Type Register.                  */
    CPU_REG32  ICDIIDR;                                         /* Distributor Implementer Identification Register.     */
    CPU_REG32  RSVD1[29];                                       /* Reserved.                                            */
    CPU_REG32  ICDISRn[32];                                     /* Interrupt Security Registers.                        */
    CPU_REG32  ICDISERn[32];                                    /* Interrupt Set-Enable Registers.                      */
    CPU_REG32  ICDICERn[32];                                    /* Interrupt Clear-Enable Registers.                    */
    CPU_REG32  ICDISPRn[32];                                    /* Interrupt Set-Pending Registers.                     */
    CPU_REG32  ICDICPRn[32];                                    /* Interrupt Clear-Pending Registers.                   */
    CPU_REG32  ICDABRn[32];                                     /* Active Bit Registers.                                */
    CPU_REG32  RSVD2[32];                                       /* Reserved.                                            */
    CPU_REG32  ICDIPRn[255];                                    /* Interrupt Priority Registers.                        */
    CPU_REG32  RSVD3[1];                                        /* Reserved.                                            */
    CPU_REG32  ICDIPTRn[255];                                   /* Interrupt Processor Target Registers.                */
    CPU_REG32  RSVD4[1];                                        /* Reserved.                                            */
    CPU_REG32  ICDICFRn[64];                                    /* Interrupt Configuration Registers.                   */
    CPU_REG32  RSVD5[128];                                      /* Reserved.                                            */
    CPU_REG32  ICDSGIR;                                         /* Software Generate Interrupt Register.                */
    CPU_REG32  RSVD6[51];                                       /* Reserved.                                            */
} ARM_REG_GIC_DIST, *ARM_REG_GIC_DIST_PTR;


                                                                /* ---------------- GIC CPU INTERFACE ----------------- */
typedef  struct  arm_reg_gic_if {
    CPU_REG32  ICCICR;                                          /* CPU Interface Control Register.                      */
    CPU_REG32  ICCPMR;                                          /* Interrupt Priority Mask Register.                    */
    CPU_REG32  ICCBPR;                                          /* Binary Point Register.                               */
    CPU_REG32  ICCIAR;                                          /* Interrupt Acknowledge Register.                      */
    CPU_REG32  ICCEOIR;                                         /* End Interrupt Register.                              */
    CPU_REG32  ICCRPR;                                          /* Running Priority Register.                           */
    CPU_REG32  ICCHPIR;                                         /* Highest Pending Interrupt Register.                  */
    CPU_REG32  ICCABPR;                                         /* Aliased Binary Point Register.                       */
    CPU_REG32  RSVD[55];                                        /* Reserved.                                            */
    CPU_REG32  ICCIIDR;                                         /* CPU Interface Identification Register.               */
} ARM_REG_GIC_IF, *ARM_REG_GIC_IF_PTR;


                                                                /* ----------- DISTRIBUTOR CONTROL REGISTER ----------- */
#define  ARM_BIT_GIC_DIST_ICDDCR_EN            DEF_BIT_00       /* Global GIC enable.                                   */



                                                                /* ---------- CPU INTERFACE CONTROL REGISTER ---------- */
#define  ARM_BIT_GIC_IF_ICCICR_ENS             DEF_BIT_00       /* Enable secure interrupts.                            */
#define  ARM_BIT_GIC_IF_ICCICR_ENNS            DEF_BIT_01       /* Enable non-secure interrupts.                        */
#define  ARM_BIT_GIC_IF_ICCICR_ACKCTL          DEF_BIT_02       /* Secure ack of NS interrupts.                         */



/*
*********************************************************************************************************
*********************************************************************************************************
**                                         GLOBAL FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            BSP_Int_Init()
*
* Description : Initialise interrupts.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : BSP_Init().
*
* Note(s)     : none.
*
*********************************************************************************************************
*/

void BSP_Int_Init (void)
{

                                                                /* Enable the GIC.                                      */
    BSP_INT_GIC_DIST_REG->ICDDCR |= ARM_BIT_GIC_DIST_ICDDCR_EN | ARM_BIT_GIC_IF_ICCICR_ACKCTL;

                                                                /* Enable the GIC interface.                            */
    BSP_INT_GIC_IF_REG->ICCICR |= (ARM_BIT_GIC_IF_ICCICR_ENS | ARM_BIT_GIC_IF_ICCICR_ENNS);

    CPU_IntEn();

    BSP_IntPrioMaskSet(0xFFu);
}


/*
*********************************************************************************************************
*                                            BSP_IntSrcEn()
*
* Description : Enable interrupt source int_id.
*
* Argument(s) : int_id		Interrupt to enable.
*
* Return(s)   : none.
*
* Caller(s)   : BSP_OS_TmrTickInit().
*
* Note(s)     : none.
*
*********************************************************************************************************
*/

void  BSP_IntSrcEn (CPU_INT32U int_id)
{
    CPU_INT32U  reg_off;
    CPU_INT32U  reg_bit;


    if(int_id >= ARM_GIC_INT_SRC_CNT) {
        return;
    }

    CPU_MB();

    reg_off = int_id >> 5u;                                     /* Calculate the register offset.                       */

    reg_bit = int_id & 0x1F;                                    /* Mask bit ID.                                         */

    BSP_INT_GIC_DIST_REG->ICDISERn[reg_off] = 1u << reg_bit;

    CPU_MB();
}


/*
*********************************************************************************************************
*                                            BSP_IntSrcDis()
*
* Description : Disable interrupt source int_id.
*
* Argument(s) : int_id  	Interrupt to disable.
*
* Return(s)   : none.
*
* Caller(s)   : none.
*
* Note(s)     : none.
*
*********************************************************************************************************
*/

void  BSP_IntSrcDis (CPU_INT32U int_id)
{
    CPU_INT32U  reg_off;
    CPU_INT32U  reg_bit;

    if(int_id >= ARM_GIC_INT_SRC_CNT) {
        return;
    }

    CPU_MB();

    reg_off = int_id >> 5u;                                     /* Calculate the register offset.                       */

    reg_bit = int_id & 0x1F;                                    /* Mask bit ID.                                         */

    BSP_INT_GIC_DIST_REG->ICDICERn[reg_off] = 1u << reg_bit;

    CPU_MB();
}


/*
*********************************************************************************************************
*                                         BSP_IntPrioMaskSet()
*
* Description : Set CPU's interrupt priority mask.
*
* Argument(s) : prio    	Priority mask.
*
* Return(s)   : none.
*
* Caller(s)   : none.
*
* Note(s)     : none.
*
*********************************************************************************************************
*/

void  BSP_IntPrioMaskSet (CPU_INT32U prio)
{
    if(prio < 256) {
        CPU_MB();
        BSP_INT_GIC_IF_REG->ICCPMR = prio;
        CPU_MB();
    }
}


/*
*********************************************************************************************************
*                                           BSP_IntPrioSet()
*
* Description : Set interrupt priority.
*
* Argument(s) : int_id  Interrupt id.
*
*               prio    Interrupt priority.
*
* Return(s)   : none.
*
* Caller(s)   : none.
*
* Note(s)     : none.
*
*********************************************************************************************************
*/

void  BSP_IntPrioSet (CPU_INT32U  int_id,
                      CPU_INT32U  prio)
{
    CPU_INT32U  reg_off;
    CPU_INT32U  reg_byte;
    CPU_INT32U  temp_reg;
    CPU_SR_ALLOC();

    if(int_id >= ARM_GIC_INT_SRC_CNT) {
        return;
    }

    if(prio >= 256) {
        return;
    }

    CPU_CRITICAL_ENTER();

    reg_off = int_id >> 2u;
    reg_byte = int_id & 0x03;

    temp_reg = BSP_INT_GIC_DIST_REG->ICDIPRn[reg_off];
    temp_reg = temp_reg & ~(0xFF << (reg_byte * 8u));
    temp_reg = temp_reg | ((prio & 0x1Fu) << (reg_byte * 8u));

    BSP_INT_GIC_DIST_REG->ICDIPRn[reg_off] = temp_reg;

    CPU_CRITICAL_EXIT();
}


/*
*********************************************************************************************************
*                                          BSP_IntTargetSet()
*
* Description : Set interrupt target.
*
* Argument(s) : int_id              Interrupt id.
*
*               int_target_list     Interrupt CPU target list.
*
* Return(s)   : none.
*
* Caller(s)   : none.
*
* Note(s)     : none.
*
*********************************************************************************************************
*/

void  BSP_IntTargetSet (CPU_INT32U  int_id,
                        CPU_INT08U  int_target_list)
{
    CPU_INT32U  reg_off;
    CPU_INT32U  reg_byte;
    CPU_INT32U  temp_reg;
    CPU_SR_ALLOC();


    if(int_id >= ARM_GIC_INT_SRC_CNT) {
        return;
    }

    CPU_CRITICAL_ENTER();

    reg_off = int_id >> 2u;
    reg_byte = int_id & 0x03;

    temp_reg = BSP_INT_GIC_DIST_REG->ICDIPTRn[reg_off];
    temp_reg = temp_reg & ~(0xFF << (reg_byte * 8u));
    temp_reg = temp_reg | ((int_target_list & 0x1Fu) << (reg_byte * 8u));

    BSP_INT_GIC_DIST_REG->ICDIPTRn[reg_off] = temp_reg;

    CPU_CRITICAL_EXIT();
}


/*
*********************************************************************************************************
*                                           BSP_IntVectSet()
*
* Description : Configure interrupt vector.
*
* Argument(s) : int_id              Interrupt ID.
*
*               int_prio            Interrupt priority.
*
*               int_type            Interrupt type.
*
*               int_target_list     Interrupt CPU target list
*
*               int_fnct            ISR function pointer.
*
* Return(s)   : Interrupt configuration result.
*                                DEF_YES                   Interrupt successfully set.
*                                OS_ERR_OBJ_PTR_NULL       Error setting interrupt.
*
* Caller(s)   : Application.
*
*
* Note(s)     : none.
*
*********************************************************************************************************
*/

CPU_BOOLEAN  BSP_IntVectSet (CPU_INT32U       int_id,
                             CPU_INT32U       int_prio,
                             CPU_INT08U       int_target_list,
                             BSP_INT_FNCT_PTR int_fnct)
{

    CPU_SR_ALLOC();


    if(int_prio > 255u) {
        return DEF_NO;
    }

    if(int_id >= ARM_GIC_INT_SRC_CNT) {
        return DEF_NO;
    }

    if(int_target_list > 255u) {
        return DEF_NO;
    }


    CPU_CRITICAL_ENTER();                                       /* Prevent partially configured interrupts.             */

    BSP_IntPrioSet(int_id,
    		       int_prio);

    BSP_IntTargetSet(int_id,
                     int_target_list);

    BSP_IntVectTbl[int_id] = int_fnct;

    CPU_CRITICAL_EXIT();


    return (DEF_OK);
}


/*
*********************************************************************************************************
*                                           BSP_IntHandler()
*
* Description : Generic interrupt handler.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : OS_CPU_ExceptHndlr().
*
* Note(s)     : none.
*
*********************************************************************************************************
*/

void  BSP_IntHandler (void)
{
    CPU_INT32U        int_ack;
    CPU_INT32U        int_id;
    CPU_INT32U        int_cpu;
    BSP_INT_FNCT_PTR  p_isr;


    int_ack = BSP_INT_GIC_IF_REG->ICCIAR;                       /* Acknowledge the interrupt.                           */

    int_id = int_ack & DEF_BIT_FIELD(10u, 0u);                  /* Mask away the CPUID.                                 */

    if(int_id == 1023u) {                                       /* Spurious interrupt.                                  */
        return;
    }

    int_cpu = (int_ack & DEF_BIT_FIELD(12u, 2u)) >> 10u;        /* Extract the interrupt source.                        */

    p_isr = BSP_IntVectTbl[int_id];                             /* Fetch ISR handler.                                   */

    if(p_isr != DEF_NULL) {
        (*p_isr)(int_cpu);                                      /* Call ISR handler.                                    */
    }

    CPU_MB();                                                   /* Memory barrier before ending the interrupt.          */

    BSP_INT_GIC_IF_REG->ICCEOIR = int_id;
}


/*
*********************************************************************************************************
*                                            BSP_SGITrig()
*
* Description : Trigger software generated interrupt.
*
* Argument(s) : int_sgi             SGI ID.
*
*               int_target_list     Interrupt CPU target list
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*
*********************************************************************************************************
*/

void  BSP_SGITrig  (CPU_INT32U  int_sgi, CPU_INT32U int_target_list)
{
    CPU_MB();
    BSP_INT_GIC_DIST_REG->ICDSGIR = ((int_target_list & 0xFF) << 16u) | int_sgi;
    CPU_MB();
}
