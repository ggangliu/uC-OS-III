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
*                                         OpenAMP INIT CODE
*
* Filename      : ucos_openamp_init.c
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

#if (APP_OPENAMP_ENABLED == DEF_ENABLED)
#include  <include/open_amp.h>
#include  <include/openamp_micrium_core.h>
#endif

#if (APP_OPENAMP_ENABLED == DEF_ENABLED)
CPU_BOOLEAN UCOS_OpenAMP_Init (void)
{
    OPENAMP_TASK_INFO task_cfg;
    RTOS_ERR openamp_err;

    task_cfg.Prio = 10;
    task_cfg.StkPtr = DEF_NULL;
    task_cfg.StkSize = 2048;
    
#if (UCOS_START_DEBUG_TRACE == DEF_ENABLED)
    UCOS_Print("UCOS - Initializing OpenAMP.\r\n");
#endif

    OpenAMP_Init(DEF_NULL, &task_cfg, &openamp_err);
    
    if (openamp_err != RTOS_ERR_NONE) {
#if (UCOS_START_DEBUG_TRACE == DEF_ENABLED)
        UCOS_Printf("UCOS - Error initializing OpenAMP. Error code %d\r\n", openamp_err);
#endif
        return (DEF_FAIL);
    }

    return (DEF_OK);
}

#endif /* #if (APP_OPENAMP_ENABLED == DEF_ENABLED) */
