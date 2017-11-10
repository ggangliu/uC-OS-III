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
*                                         uC/TCPIP INIT CODE
*
* Filename      : ucos_telnet-s_init.c
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

#if (APP_TELNETS_ENABLED == DEF_ENABLED)
#include <Source/telnet-s.h>
#include <Cmd/telnet-s_shell.h>
#endif

#if (APP_TELNETS_ENABLED == DEF_ENABLED)
CPU_BOOLEAN UCOS_TELNETs_Init (void)
{
    NET_SOCK_ADDR_FAMILY ip_type = AF_INET;
    CPU_BOOLEAN ok;


#if (UCOS_START_DEBUG_TRACE == DEF_ENABLED)
    UCOS_Print("UCOS - Initializing uC/TELNETs.\r\n");
#endif

    TELNETsShell_Init("DUT", "micrium");

    ok = TELNETs_Init(NET_SOCK_ADDR_FAMILY_IP_V4, DEF_NULL);

    if (ok == DEF_OK)
        return (DEF_OK);
    else
        return (DEF_FAIL);
}

#endif /* #if (APP_TELNETS_ENABLED == DEF_ENABLED) */
