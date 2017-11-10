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
* Filename      : ucos_osiii_bsp.c
* Version       : V1.42
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

#include  "ucos_osiii_bsp.h"
#include  <ucos_int.h>
#include  <os.h>
#include  <os_cfg_app.h>

#if (XPAR_CPU_ID == 0)
#define SCUTMR_CLK_FREQ  (XPAR_PS7_CORTEXA9_0_CPU_CLK_FREQ_HZ / 2)
#else
#define SCUTMR_CLK_FREQ  (XPAR_PS7_CORTEXA9_1_CPU_CLK_FREQ_HZ / 2)
#endif


#define  ARM_PTMR_REG_PTLR     (*((CPU_REG32 *)(XPAR_PS7_SCUTIMER_0_BASEADDR + 0x0000))) /* Private timer load register.            */
#define  ARM_PTMR_REG_PTCTRR   (*((CPU_REG32 *)(XPAR_PS7_SCUTIMER_0_BASEADDR + 0x0004))) /* Private timer counter register.         */
#define  ARM_PTMR_REG_PTCTLR   (*((CPU_REG32 *)(XPAR_PS7_SCUTIMER_0_BASEADDR + 0x0008))) /* Private timer control register.         */
#define  ARM_PTMR_REG_PTISR    (*((CPU_REG32 *)(XPAR_PS7_SCUTIMER_0_BASEADDR + 0x000C))) /* Private timer interrupt status register.*/

#define  ARM_GTMR_REG_GTCRL   (*((CPU_REG32 *)(XPAR_PS7_SCUC_0_BASEADDR + 0x0200))) /* Global timer counter register (Low). */
#define  ARM_GTMR_REG_GTCRH   (*((CPU_REG32 *)(XPAR_PS7_SCUC_0_BASEADDR + 0x0204))) /* Global timer counter register (High).*/
#define  ARM_GTMR_REG_GTCR    (*((CPU_REG32 *)(XPAR_PS7_SCUC_0_BASEADDR + 0x0208))) /* Global timer control register.       */
#define  ARM_GTMR_REG_GTCVL   (*((CPU_REG32 *)(XPAR_PS7_SCUC_0_BASEADDR + 0x0210))) /* Global timer compare value (low)     */
#define  ARM_GTMR_REG_GTCVH   (*((CPU_REG32 *)(XPAR_PS7_SCUC_0_BASEADDR + 0x0214))) /* Global timer compare value (high)    */

#define  ARM_GTMR_FREQ  (XPAR_CPU_CORTEXA9_0_CPU_CLK_FREQ_HZ / 2)

#if (OS_CFG_DYN_TICK_EN == DEF_ENABLED)
CPU_INT64U last_tick;
#endif

#if (OS_CFG_DYN_TICK_EN == DEF_ENABLED)
static CPU_INT64U  UCOS_TS_TmrRd (void)
{
    CPU_INT64U  ts_tmr_cnts;
    CPU_INT32U  ts_tmr_low;
    CPU_INT32U  ts_tmr_high_a;
    CPU_INT32U  ts_tmr_high_b;

    ts_tmr_high_b = ARM_GTMR_REG_GTCRH;

    do {
        ts_tmr_high_a = ts_tmr_high_b;
        ts_tmr_low    = ARM_GTMR_REG_GTCRL;
        ts_tmr_high_b = ARM_GTMR_REG_GTCRH;
    } while (ts_tmr_high_a != ts_tmr_high_b);

    ts_tmr_cnts  = ts_tmr_high_a;
    ts_tmr_cnts  = ts_tmr_cnts << 32u;
    ts_tmr_cnts += ts_tmr_low;

    return (ts_tmr_cnts);
}
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
    CPU_INT64U  ts;
    ARM_PTMR_REG_PTISR = 0x01u;                                 /* Clear the interrupt.                                 */

#if (OS_CFG_DYN_TICK_EN == DEF_DISABLED)
    OSTimeTick();
#else
    ARM_GTMR_REG_GTCR &= ~DEF_BIT_01;
    ts = UCOS_TS_TmrRd();
    OSTimeDynTick((ts / (ARM_GTMR_FREQ  / OS_CFG_TICK_RATE_HZ)) - last_tick);
    last_tick = (ts / (ARM_GTMR_FREQ  / OS_CFG_TICK_RATE_HZ));
#endif
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
    CPU_INT32U tmr_cnt;

#if (OS_CFG_DYN_TICK_EN == DEF_DISABLED)
    ARM_PTMR_REG_PTCTLR = 0x0006u;

    tmr_cnt = SCUTMR_CLK_FREQ / tick_rate;

    ARM_PTMR_REG_PTLR = tmr_cnt;

    ARM_PTMR_REG_PTISR = 0x01u;

    UCOS_IntVectSet (29u,
                     0u,
                     0u,
                     UCOS_TmrTickHandler,
                     DEF_NULL);

    UCOS_IntSrcEn (29u);

    ARM_PTMR_REG_PTCTLR |= 0x01;
#else
    UCOS_IntVectSet (27u,
                     0u,
                     0u,
                     UCOS_TmrTickHandler,
                     DEF_NULL);

    UCOS_IntSrcEn (27u);

    ARM_GTMR_REG_GTCR = DEF_BIT_00 | DEF_BIT_02;
#endif
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
