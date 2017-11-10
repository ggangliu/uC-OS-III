/*
*********************************************************************************************************
*
*                                    MICRIUM BOARD SUPPORT PACKAGE
*
*                        (c) Copyright 2014-2015; Micrium, Inc.; Weston, FL
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
*                                         uC/IPerf INIT CODE
*
* Filename      : ucos_iperf_init.c
* Version       : V1.42
* Programmer(s) : JBL
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#include <app_cfg.h>
#include <cpu.h>
#include <ucos_bsp.h>
#include <ucos_int.h>
#include <xparameters.h>
#include <KAL/kal.h>

#if (APP_IPERF_ENABLED == DEF_ENABLED)
#include <Source/iperf.h>
#endif

#if (APP_IPERF_ENABLED == DEF_ENABLED)
CPU_BOOLEAN UCOS_IPerf_Init (void)
{
    NET_SOCK_ADDR_FAMILY ip_type = AF_INET;
    CPU_BOOLEAN ok;
    IPERF_ERR err_iperf;


#if (UCOS_START_DEBUG_TRACE == DEF_ENABLED)
    UCOS_Print("UCOS - Initializing uC/IPerf.\r\n");
#endif

    IPerf_Init(&err_iperf);

    if (err_iperf != IPERF_ERR_NONE) {
        UCOS_Printf("UCOS - Error initializing uC/IPerf. Error code %d.\r\n", err_iperf);
        return (DEF_FAIL);
    }

    if (err_iperf == IPERF_ERR_NONE) {
        IPerfShell_Init(&err_iperf);
    }

    if (err_iperf != IPERF_ERR_NONE) {
        UCOS_Printf("UCOS - Error registering uC/IPerf shell commands. Error code %d.\r\n", err_iperf);
        return (DEF_FAIL);
    }

    return (DEF_OK);
}

#endif /* #if (APP_IPERF_ENABLED == DEF_ENABLED) */
