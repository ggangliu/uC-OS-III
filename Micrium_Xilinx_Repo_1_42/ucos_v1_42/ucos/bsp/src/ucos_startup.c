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
*                                            STARTUP CODE
*
* Filename      : ucos_startup.c
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

#if (APP_OSIII_ENABLED == DEF_ENABLED)
#include <Source/os.h>
#include <os_cfg_app.h>
#else
#include <Source/ucos_ii.h>
#include <os_cfg.h>
#endif /* (APP_OSIII_ENABLED == DEF_ENABLED) */

#if (APP_OSIII_ENABLED == DEF_ENABLED)
static OS_TCB StartupTaskTCB;
#endif

static CPU_STK StartupTaskStk[UCOS_START_TASK_STACK_SIZE];

static void StartupTask (void *p_arg);

void MainTask (void *p_arg);


/*
*********************************************************************************************************
*********************************************************************************************************
**                                         GLOBAL FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/

CPU_BOOLEAN UCOSStartup (CPU_FNCT_PTR initial_func)
{
#if (APP_OSIII_ENABLED == DEF_ENABLED)
    OS_ERR  os_err;
#endif

    UCOS_LowLevelInit();

    CPU_Init();
    Mem_Init();

#if (APP_OSIII_ENABLED == DEF_ENABLED)
    OSInit(&os_err);
#else
    OSInit();
#endif

#if (APP_OSIII_ENABLED == DEF_ENABLED)
    OSTaskCreate(&StartupTaskTCB,
                  "Main Task",
                  StartupTask,
                  (void *)initial_func,
                  UCOS_START_TASK_PRIO,
                 &StartupTaskStk[0],
                  0,
                  UCOS_START_TASK_STACK_SIZE,
                  0,
                  0,
                  DEF_NULL,
                 (OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 &os_err);
#else
    OSTaskCreateExt( StartupTask,
                    (void *)initial_func,
                    &StartupTaskStk[UCOS_START_TASK_STACK_SIZE - 1],
                    UCOS_START_TASK_PRIO,
                    UCOS_START_TASK_PRIO,
                    &StartupTaskStk[0],
                    UCOS_START_TASK_STACK_SIZE,
                     DEF_NULL,
                    (OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK));
#endif

#if (APP_OSIII_ENABLED == DEF_ENABLED)
    OSStart(&os_err);
#else
    OSStart();
#endif

    return DEF_OK;
}


static void StartupTask (void *p_arg)
{
    KAL_ERR kal_err;
    CPU_INT32U tick_rate;
#if (UCOS_START_DEBUG_TRACE == DEF_ENABLED)
    MEM_SEG_INFO seg_info;
    LIB_ERR lib_err;
#endif
#if (APP_OSIII_ENABLED == DEF_ENABLED)
    OS_ERR  os_err;
#endif

    UCOS_IntInit();                                             /* Initialize interrupt controller.                     */

#if (APP_OSIII_ENABLED == DEF_ENABLED)
    tick_rate = OS_CFG_TICK_RATE_HZ;
#endif

#if (APP_OSII_ENABLED == DEF_ENABLED)
    tick_rate = OS_TICKS_PER_SEC;
#endif

    UCOS_TmrTickInit(tick_rate);                                /* Configure and enable OS tick interrupt.              */

#if (APP_OSIII_ENABLED == DEF_ENABLED)
#if (OS_CFG_STAT_TASK_EN == DEF_ENABLED)
    OSStatTaskCPUUsageInit(&os_err);
#endif
#endif

    KAL_Init(DEF_NULL, &kal_err);

    UCOS_StdInOutInit();

#if (UCOS_START_DEBUG_TRACE == DEF_ENABLED)
    UCOS_Print("UCOS - uC/OS Init Started.\r\n");
    UCOS_Print("UCOS - STDIN/STDOUT Device Initialized.\r\n");
#endif

#if (APP_SHELL_ENABLED == DEF_ENABLED)
    UCOS_Shell_Init();
#endif

#if ((APP_FS_ENABLED == DEF_ENABLED) && (UCOS_CFG_INIT_FS == DEF_ENABLED))
    UCOS_FS_Init();
#endif

#if ((APP_TCPIP_ENABLED == DEF_ENABLED) && (UCOS_CFG_INIT_NET == DEF_ENABLED))
    UCOS_TCPIP_Init();
#endif /* (APP_TCPIP_ENABLED == DEF_ENABLED) */

#if ((APP_USBD_ENABLED == DEF_ENABLED) && (UCOS_CFG_INIT_USBD == DEF_ENABLED) && (UCOS_USB_TYPE == UCOS_USB_TYPE_DEVICE))
    UCOS_USBD_Init();
#endif /* #if (APP_USBD_ENABLED == DEF_ENABLED) */

#if ((APP_USBH_ENABLED == DEF_ENABLED) && (UCOS_CFG_INIT_USBH == DEF_ENABLED) && (UCOS_USB_TYPE == UCOS_USB_TYPE_HOST))
    UCOS_USBH_Init();
#endif /* #if (APP_USBH_ENABLED == DEF_ENABLED) */

#if ((APP_OPENAMP_ENABLED == DEF_ENABLED) && (UCOS_CFG_INIT_OPENAMP == DEF_ENABLED))
    UCOS_OpenAMP_Init();
#endif /* #if (APP_OPENAMP_ENABLED == DEF_ENABLED) */


#if (UCOS_START_DEBUG_TRACE == DEF_ENABLED)
    Mem_SegRemSizeGet(DEF_NULL, 4, &seg_info, &lib_err);

    UCOS_Printf ("UCOS - UCOS init done\r\n");
    UCOS_Printf ("UCOS - Total configured heap size. %d\r\n", seg_info.TotalSize);
    UCOS_Printf ("UCOS - Total used size after init. %d\r\n", seg_info.UsedSize);
#endif

    (*((CPU_FNCT_PTR)(p_arg)))(DEF_NULL);

}
