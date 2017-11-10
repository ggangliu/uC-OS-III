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
*                                                SYSTICK
*
* Filename      : ucos_osii_bsp.c
* Version       : V1.20
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
#include  <os.h>


typedef struct ttcps {
    CPU_REG32  ClkCtrl;
    CPU_REG32  RESERVED0[2];
    CPU_REG32  CtrCtrl;
    CPU_REG32  RESERVED1[2];
    CPU_REG32  CtrVal;
    CPU_REG32  RESERVED2[2];
    CPU_REG32  IntervalCtrVal;
    CPU_REG32  RESERVED3[2];
    CPU_REG32  Match1CtrVal;
    CPU_REG32  RESERVED4[2];
    CPU_REG32  Match2CtrVal;
    CPU_REG32  RESERVED5[2];
    CPU_REG32  Match3CtrVal;
    CPU_REG32  RESERVED6[2];
    CPU_REG32  IntStat;
    CPU_REG32  RESERVED7[2];
    CPU_REG32  IntEn;
    CPU_REG32  RESERVED8[2];
    CPU_REG32  EventCtrl;
    CPU_REG32  RESERVED9[2];
    CPU_REG32  EventReg;
    CPU_REG32  RESERVED10[2];
} TTCPS, *TTCPS_PTR;

#if (XPAR_CPU_ID == 0)
#define  TTC_TIMER_TICK           ((TTCPS_PTR)(0xFF110000))
#else
#define  TTC_TIMER_TICK           ((TTCPS_PTR)(0xFF120000))
#endif


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

    TTC_TIMER_TICK->IntStat;
    OSTimeTick();
}


/*
 *********************************************************************************************************
 *                                            BSP_OS_TmrTickInit()
 *
 * Description : Initialize uC/OS-III's tick source
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

#if (XPAR_CPU_ID == 0)
    UCOS_IntVectSet (68u,
                     0u,
                     0u,
                     UCOS_TmrTickHandler,
                     DEF_NULL);

    UCOS_IntSrcEn (68u);
#else
    UCOS_IntVectSet (68u,
                     0u,
                     DEF_BIT_01,
                     UCOS_TmrTickHandler,
                     DEF_NULL);

    UCOS_IntSrcEn (68u);
#endif

    TTC_TIMER_TICK->IntervalCtrVal = 100000000 / tick_rate;
    TTC_TIMER_TICK->IntEn |= DEF_BIT_00;
    TTC_TIMER_TICK->CtrCtrl |= DEF_BIT_01;
    TTC_TIMER_TICK->CtrCtrl &= ~DEF_BIT_00;
}

#if (OS_CFG_DYN_TICK_EN == DEF_ENABLED)
OS_TICK BSP_OS_TickGet (void)
{
    CPU_INT64U  ts;


    ts = UCOS_TS_TmrRd();

    return (ts / (ARM_GTMR_FREQ  / OS_CFG_TICK_RATE_HZ));
}
#endif

#if (OS_CFG_DYN_TICK_EN == DEF_ENABLED)
OS_TICK BSP_OS_TickNextSet (OS_TICK next)
{
    CPU_INT64U next_tick;
    CPU_INT64U next_ts;
    CPU_SR_ALLOC();

    next_tick = last_tick + next;
    next_ts = next_tick * (ARM_GTMR_FREQ  / OS_CFG_TICK_RATE_HZ);

    CPU_CRITICAL_ENTER();
    ARM_GTMR_REG_GTCR &= ~DEF_BIT_01;
    ARM_GTMR_REG_GTCVH = (CPU_INT32U)(next_ts >> 32);
    ARM_GTMR_REG_GTCVL = (CPU_INT32U)(next_ts);
    ARM_GTMR_REG_GTCR |=  DEF_BIT_01;
    CPU_CRITICAL_EXIT();
}
#endif
