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
* Version       : V1.42
* Programmer(s) : JBL
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#include <lib_def.h>
#include <cpu.h>

#include <xparameters.h>

#include <ucos_bsp.h>
#include <os.h>


#include "ucos_osii_bsp.h"

#if (UCOS_SYSTICK_DRIVER == UCOS_SYSTICK_AXITIMER)
#include  <ucos_axitimer.h>
#endif /* #if (UCOS_SYSTICK_DRIVER == UCOS_SYSTICK_AXITIMER) */


#if (UCOS_SYSTICK_DRIVER == UCOS_SYSTICK_AXITIMER)
static AXITIMER_HANDLE TmrHandle;
#endif /* #if (UCOS_SYSTICK_DRIVER == UCOS_SYSTICK_AXITIMER) */

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

#if (UCOS_SYSTICK_DRIVER == UCOS_SYSTICK_AXITIMER)
static void  UCOS_TmrTickHandler(AXITIMER_HANDLE handle,
                                 CPU_INT32U      tmr_nbr)
{
    OSTimeTick();
}
#elif (UCOS_SYSTICK_DRIVER == UCOS_SYSTICK_INT)
static void  UCOS_TmrTickHandler(void       *p_int_arg,
                                 CPU_INT32U  cpu_id)
{
    OSTimeTick();
}
#endif


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

void UCOS_TmrTickInit(CPU_INT32U tick_rate)
{
    CPU_INT32U tmr_freq;

#if (UCOS_SYSTICK_DRIVER == UCOS_SYSTICK_AXITIMER)
    TmrHandle = AXITimer_Init(UCOS_SYSTICK_DEVICE_ID);

    tmr_freq = AXITimer_FreqGet(TmrHandle);
    AXITimer_LoadSet(TmrHandle, 0, tmr_freq / tick_rate );

    AXITimer_OptSet(TmrHandle, 0, AXITIMER_BIT_TCSR_ENIT | AXITIMER_BIT_TCSR_ARHT | AXITIMER_BIT_TCSR_UDT);

    AXITimer_Start(TmrHandle, 0);

    AXITimer_CallbackSet(TmrHandle, 0, UCOS_TmrTickHandler);
#elif (UCOS_SYSTICK_DRIVER == UCOS_SYSTICK_INT)
    UCOS_IntVectSet(UCOS_SYSTICK_DEVICE_INT_SRC,
                    0u,
                    0u,
                    UCOS_TmrTickHandler,
                    DEF_NULL);

    UCOS_IntSrcEn(UCOS_SYSTICK_DEVICE_INT_SRC);
#endif

}

