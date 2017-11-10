/*
*********************************************************************************************************
*
*                                    MICRIUM BOARD SUPPORT PACKAGE
*
*                          (c) Copyright 2016; Micrium, Inc.; Weston, FL
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
*                                                SYSTICK
*
* Filename      : ucos_osii_bsp.c
* Version       : V1.01
* Programmer(s) : JBL
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#include  <lib_def.h>
#include  <cpu.h>

#include  <xparameters.h>

#include  "ucos_osii_bsp.h"
#include  <ucos_int.h>


/* TODO - Derive this from hardware configuration. */
#define CPU_CLK_TMR_FREQ 100000000UL

static CPU_INT64U TmrStepSize;

/*
*********************************************************************************************************
*                                       BSP_OS_TmrTickHandler()
*
* Description : Interrupt handler for the tick timer
*
* Argument(s) : cpu_id     Source core id
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  UCOS_TmrTickHandler(void *p_int_arg, CPU_INT32U cpu_id)
{
    CPU_INT64U tmr_cnt;


#if (UCOS_ZYNQ_MPSOC_A53_TICK_SECURE_EL3 == DEF_ENABLED)
    CPU_CP_GET(tmr_cnt, CNTPS_CVAL_EL1);
    tmr_cnt += TmrStepSize;
    CPU_CP_SET(tmr_cnt, CNTPS_CVAL_EL1);
#else
    CPU_CP_GET(tmr_cnt, CNTP_CVAL_EL0);
    tmr_cnt += TmrStepSize;
    CPU_CP_SET(tmr_cnt, CNTP_CVAL_EL0);
#endif

    OSTimeTick();
}


/*
 *********************************************************************************************************
 *                                            BSP_OS_TmrTickInit()
 *
 * Description : Initialize uC/OS-II's tick source
 *
 * Argument(s) : ticks_per_sec              Number of ticks per second.
 *
 * Return(s)   : none.
 *
 * Caller(s)   : Application.
 *
 * Note(s)     : none.
 *********************************************************************************************************
 */

void UCOS_TmrTickInit (CPU_INT32U tick_rate)
{

    TmrStepSize = CPU_CLK_TMR_FREQ / tick_rate;

#if (UCOS_ZYNQ_MPSOC_A53_TICK_SECURE_EL3 == DEF_ENABLED)
    UCOS_IntVectSet (29u,
                     0u,
                     0u,
                     UCOS_TmrTickHandler,
                     DEF_NULL);

    UCOS_IntSrcEn (29u);

    CPU_CP_SET(TmrStepSize, CNTPS_TVAL_EL1);
    CPU_CP_SET(0x1, CNTPS_CTL_EL1);
#else
    UCOS_IntVectSet (30u,
                     0u,
                     0u,
                     UCOS_TmrTickHandler,
                     DEF_NULL);

    UCOS_IntSrcEn (30u);

    CPU_CP_SET(TmrStepSize, CNTP_TVAL_EL0);
    CPU_CP_SET(0x1, CNTP_CTL_EL0);
#endif
}
