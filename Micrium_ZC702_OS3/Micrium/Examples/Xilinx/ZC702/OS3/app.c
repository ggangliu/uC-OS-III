/*
*********************************************************************************************************
*                                            EXAMPLE CODE
*
*                          (c) Copyright 2009-2014; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*
*               Please feel free to use any application code labeled as 'EXAMPLE CODE' in
*               your application products.  Example code may be used as is, in whole or in
*               part, or may be used as a reference only.
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
*                                          APPLICATION CODE
*
*                                            ZYNQ 7000 EPP
*                                               on the
*                                       ZC702 development board
*
* Filename      : app.c
* Version       : V1.00
* Programmer(s) : DC
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include  <app_cfg.h>
#include  <lib_mem.h>

#include  <bsp.h>
#include  <bsp_int.h>
#include  <bsp_os.h>
#include  <bsp_cache.h>
#include  <bsp_ser.h>

#include  <cpu.h>
#include  <cpu_core.h>

#include  <os.h>

/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/

OS_TCB        AppTaskStartTCB;
CPU_STK       AppTaskStartStk[APP_CFG_START_TASK_STK_SIZE];



/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static  void  AppTaskStart  (void *p_arg);

/*
*********************************************************************************************************
*                                               main()
*
* Description : Entry point for C code.
*
* Arguments   : none.
*
* Returns     : none.
*********************************************************************************************************
*/


int main(int argc, const char* argv[])
{
    OS_ERR  os_err;

    															/* ---------------- CACHE INIT & CONFIG --------------- */
                                                                /* Scatter Loading is Complete. Cache can be Activated. */
    BSP_BranchPredictorEn();                                    /* Enable Branch Prediction.                            */
    BSP_L2C310Config();                                         /* Configure the L2 Cache Controller.                   */
    BSP_CachesEn();                                             /* Enable L1 I&D Caches + L2 Unified Cache.             */


    CPU_Init();                                                 /* Initialize the uC/CPU Services.                      */
    Mem_Init();                                                 /* Initialize the Memory Management Services.           */

    OSInit(&os_err);                                            /* Initialize Micrium's uC/OS-III Kernel.               */

    OSTaskCreate(&AppTaskStartTCB,                              /* Create the Start Task                                */
                 "App Task Start",
                  AppTaskStart,
                  0u,
                  APP_CFG_TASK_START_PRIO,
                 &AppTaskStartStk[0u],
                 (APP_CFG_START_TASK_STK_SIZE / 10u),
                  APP_CFG_START_TASK_STK_SIZE,
                  0u,
                  0u,
                  0u,
                 (OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 &os_err);

    OSStart(&os_err);                                           /* Start Multitasking (I.E. give control to uC/OS-III.  */

    while (DEF_ON) {
    };                                                          /* Should Never get here.                               */
}


/*
*********************************************************************************************************
*                                           App_TaskStart()
*
* Description : Startup task example code.
*
* Arguments   : p_arg       Argument passed by 'OSTaskCreate()'.
*
* Returns     : none.
*
* Created by  : main().
*
* Notes       : (1) The ticker MUST be initialised AFTER multitasking has started.
*********************************************************************************************************
*/

static  void  AppTaskStart (void *p_arg)
{
    OS_ERR             os_err;


    BSP_Init();                                                 /* Initialize BSP Service(s).                           */
    BSP_OS_TmrTickInit();                                       /* Configure and Enable OS tick interrupt.              */

    BSP_Ser_Init();                                             /* Init serial port.                                    */

#if (OS_CFG_STAT_TASK_EN == DEF_ENABLED)
    OSStatTaskCPUUsageInit (&os_err);
#endif

    while (DEF_ON) {

        BSP_LED_Toggle(0u);

        OSTimeDlyHMSM(0u, 0u, 0u, 500u,
                      OS_OPT_TIME_HMSM_STRICT, &os_err);
    }

}
