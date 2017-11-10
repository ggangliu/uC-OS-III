/*
*********************************************************************************************************
*                                                uC/CPU
*                                    CPU CONFIGURATION & PORT LAYER
*
*                          (c) Copyright 2004-2013; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*
*               uC/CPU is provided in source form to registered licensees ONLY.  It is
*               illegal to distribute this source code to any third party unless you receive
*               written permission by an authorized Micrium representative.  Knowledge of
*               the source code may NOT be used to develop a similar product.
*
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*
*               You can find our product's user manual, API reference, release notes and
*               more information at https://doc.micrium.com.
*               You can contact us at www.micrium.com.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                      CPU CACHE IMPLEMENTATION
*                    Generic ARMv7 L1 Cache and External L2C310 L2 Cache Controller
*
* Filename      : cpu_cache_armv7_generic_l1_l2c310_l2.c
* Version       : V1.30.0
* Programmer(s) : JBL
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/
#include <cpu.h>
#include "../../../cpu_cache.h"
#include <lib_def.h>

#ifndef CPU_CACHE_CFG_L2C310_BASE_ADDR
#error  "CPU_CFG.H, Missing CPU_CACHE_CFG_L2C310_BASE_ADDR: Base address of L2C310 Level 2 cache controller"
#endif


#ifdef __cplusplus
extern  "C" {
#endif

/*
*********************************************************************************************************
*                                        EXTERNAL DECLARATIONS
*********************************************************************************************************
*/

CPU_INT32U  CPU_DCache_LineSizeGet (void);


/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/

CPU_INT32U  CPU_Cache_Linesize;                                 /* Cache line size.                                     */
CPU_INT32U  CPU_Cache_PL310BaseAddr;                            /* PL310 L2 cache controller base addr.                 */


/*
*********************************************************************************************************
*                                         CPU_CacheMGMTInit()
*
* Description : Get CPU timestamp's timer frequency.
*
* Argument(s) : p_err       Pointer to variable that will receive the return error code from this function :
*
*                               CPU_ERR_NONE                    CPU timestamp's timer frequency successfully
*                                                                   returned.
*                               CPU_ERR_TS_FREQ_INVALID         CPU timestamp's timer frequency invalid &/or
*                                                                   NOT yet configured.
*
* Return(s)   : CPU timestamp's timer frequency (in Hertz), if NO error(s).
*
*               0,                                          otherwise.
*
* Caller(s)   : Application.
*
*               This function is a CPU module application programming interface (API) function & MAY be
*               called by application function(s).
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  CPU_Cache_Init(void)
{
    CPU_Cache_Linesize      = CPU_DCache_LineSizeGet();
    CPU_Cache_PL310BaseAddr = CPU_CACHE_CFG_L2C310_BASE_ADDR;
}

#ifdef __cplusplus
}
#endif
