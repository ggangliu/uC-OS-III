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
*                                         uC/TCPIP INIT CODE
*
* Filename      : ucos_dhcp-c_init.c
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

#if (APP_SHELL_ENABLED == DEF_ENABLED)
#include <Source/shell.h>
#endif

#if (APP_SHELL_ENABLED == DEF_ENABLED)
CPU_BOOLEAN UCOS_Shell_Init (void)
{
    CPU_BOOLEAN err_shell;


#if (UCOS_START_DEBUG_TRACE == DEF_ENABLED)
    UCOS_Print("UCOS - Initializing uC/Shell.\r\n");
#endif

    err_shell = Shell_Init();

    if (err_shell != DEF_OK) {
        UCOS_Printf("UCOS - Error initializing uC/Shell.\r\n");
        return (DEF_FAIL);
    }

    return (DEF_OK);
}

#endif /* #if (APP_SHELL_ENABLED == DEF_ENABLED) */
