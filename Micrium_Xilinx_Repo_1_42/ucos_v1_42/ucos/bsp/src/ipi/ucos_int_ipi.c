/*
*********************************************************************************************************
*
*                                    MICRIUM BOARD SUPPORT PACKAGE
*
*                         (c) Copyright 2014-2015; Micrium, Inc.; Weston, FL
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
*                                         MPSoC IPI Interface
*
* Filename      : ucos_int_ipi.c
* Version       : V1.30
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

#include  <os_cpu.h>

#include  <xipipsu.h>

extern XIpiPsu_Config XIpiPsu_ConfigTable[];

XIpiPsu IPIInstance;

void UCOS_IntIPIHandler (void  *p_arg, CPU_INT32U  cpu_id);


CPU_BOOLEAN UCOS_IntIPIInit (void)
{
    XStatus status;


#if (UCOS_CPU_TYPE == UCOS_CPU_TYPE_PSUR5)
    status = XIpiPsu_CfgInitialize(&IPIInstance, &XIpiPsu_ConfigTable[0], 0xff310000);
#else
    status = XIpiPsu_CfgInitialize(&IPIInstance, &XIpiPsu_ConfigTable[0], XIpiPsu_ConfigTable[0].BaseAddress);
#endif

    if (status != XST_SUCCESS) {
        for(;;) {
                CPU_MB();
        }
    }

    UCOS_IntVectSet(65,
                    0,
                    (1 << XPAR_CPU_ID),
                    UCOS_IntIPIHandler,
                    DEF_NULL);

#if (UCOS_CPU_TYPE == UCOS_CPU_TYPE_PSUA53)
    UCOS_IntSrcEn(XPAR_PSU_IPI_0_INT_ID);
#else
    UCOS_IntSrcEn(XPAR_PSU_IPI_1_INT_ID);
#endif

    return (DEF_OK);
}

CPU_BOOLEAN UCOS_IntIPIEn (CPU_INT32U cpu_id)
{
    CPU_SR_ALLOC();

    XIpiPsu_InterruptEnable(&IPIInstance, 1 << cpu_id);

    return (DEF_OK);
}

CPU_BOOLEAN UCOS_IntIPIAck (CPU_INT32U cpu_id)
{
    CPU_SR_ALLOC();

    XIpiPsu_ClearInterruptStatus(&IPIInstance, 1 << cpu_id);

    return (DEF_OK);
}

CPU_BOOLEAN UCOS_IntIPITrig (CPU_INT32U cpu_id)
{
    XStatus status;


    status = XIpiPsu_TriggerIpi(&IPIInstance, 1 << cpu_id);

    if (status != XST_SUCCESS) {
        for(;;) {
                CPU_MB();
        }
    }

    return (DEF_OK);
}


void UCOS_IntIPIHandler (void  *p_arg, CPU_INT32U  cpu_id)
{
    for(;;) {
            CPU_MB();
    }
}
