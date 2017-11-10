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
*                                      Cortex-A9 Post Main Init
*
* Filename      : ucos_impl.c
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

#include  <xparameters.h>

void UCOS_LowLevelInit (void)
{
#if 0
#if (UCOS_ZYNQ_CONFIG_CACHES == DEF_ENABLED)
    /* Init L1 Caches. */
    CPU_CortexA9_BranchPredictEn();
#if (UCOS_ZYNQ_ENABLE_OPTIMS == DEF_ENABLED)
    CPU_CortexA9_L1PrefetchEn();
    CPU_CortexA9_L2PrefetchEn();
    CPU_CortexA9_FLZEn();
#endif

#if (UCOS_ZYNQ_ENABLE_CACHES == DEF_ENABLED)
    CPU_CortexA9_L1DCacheEn();
    CPU_CortexA9_L1ICacheEn();
#endif

    /* Init L2 Caches. */
#if (UCOS_AMP_MASTER == DEF_ENABLED)
#if (UCOS_ZYNQ_CONFIG_CACHES == DEF_ENABLED)
#if (UCOS_ZYNQ_ENABLE_OPTIMS == DEF_ENABLED)
    L2CacheC_AuxCtrlSet(0x72060801);
    L2CacheC_PrefetchCtrlSet(0x71000001);
#else
    L2CacheC_AuxCtrlSet(0x02060000);
#endif
    L2CacheC_TagRamLatencySet(1u, 1u, 1u);
    L2CacheC_DataRamLatencySet(1u, 2u, 1u);
#endif

#if (UCOS_ZYNQ_ENABLE_CACHES == DEF_ENABLED)
    L2CacheC_En();
#endif
#endif /* #if (UCOS_ZYNQ_CONFIG_CACHES == DEF_ENABLED) */
#endif /* #if (UCOS_AMP_MASTER == DEF_ENABLED) */
#endif
}
