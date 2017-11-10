/*
*********************************************************************************************************
*                                               uC/Clk
*                                          Clock / Calendar
*
*                      (c) Copyright 2004-2014; Micrium, Inc.; Weston, FL
*
*          All rights reserved.  Protected by international copyright laws.
*
*          uC/Clk is provided in source form to registered licensees ONLY.  It is
*          illegal to distribute this source code to any third party unless you receive
*          written permission by an authorized Micrium representative.  Knowledge of
*          the source code may NOT be used to develop a similar product.
*
*          Please help us continue to provide the Embedded community with the finest
*          software available.  Your honesty is greatly appreciated.
*
*          You can find our product's user manual, API reference, release notes and
*          more information at: https://doc.micrium.com
*
*          You can contact us at: www.micrium.com
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
**                                     CLOCK CONFIGURATION FILE
*
*                                          TEMPLATE-EXAMPLE
*
* Filename      : clk_cfg.c
* Version       : V3.10.00
* Programmer(s) : AL
*                 AOP
*********************************************************************************************************
*/

#define    MICRIUM_SOURCE
#define    CLK_CFG_MODULE


/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include  <clk_cfg.h>
#include  <Source/clk_type.h>
#include  <app_cfg.h>
#include  <lib_def.h>


/*
*********************************************************************************************************
*                                     EXAMPLE TASKS CONFIGURATION
*
* Notes: (1) (a) Task priorities can be defined either in this configuration file 'clk_cfg.c' or in a global
*                OS tasks priorities configuration header file which must be included in 'clk_cfg.c' and
*                used within task's configuration structures:
*
*                   in app_cfg.h:
*                       #define  CLK_TASK_PRIO           30u
*                       #define  CLK_TASK_STK_SIZE      512u
*
*                   in clk_cfg.c:
*                       #include  <app_cfg.h>
*
*                       CLK_TASK_CFG  ClkTaskCfg        = {
*                                                             CLK_TASK_PRIO,
*                                                             CLK_TASK_STK_SIZE,
*                                                             DEF_NULL,
*                                                         };
*
*        (2)  The only guaranteed method of determining the required task stack sizes is to calculate the maximum
*             stack usage for each task. Obviously, the maximum stack usage for a task is the total stack usage
*             along the task's most-stack-greedy function path plus the (maximum) stack usage for interrupts.
*             Note that the most-stack-greedy function path is not necessarily the longest or deepest function path.
*             Micrium cannot provide any recommended stack size values since it's specific to each compiler and
*             processor.
*
*             Although Micrium does NOT officially recommend any specific tools to calculate task/function stack usage.
*             However Wikipedia maintains a list of static code analysis tools for various languages including C:
*
*                 http://en.wikipedia.org/wiki/List_of_tools_for_static_code_analysis
*
*        (3)  When the stack pointer is defined as null (DEF_NULL), the task's stack is allocated automatically on the
*             heap of uC/LIB. If for some reason you would like to allocate the stack somewhere else and by yourself,
*             you can just specify the memory location of the stack to use.
*********************************************************************************************************
*/

#if (CLK_CFG_EXT_EN == DEF_DISABLED)
const  CLK_TASK_CFG  ClkTaskCfg = {
        CLK_TASK_PRIO,                                          /* CLK task priority                    (see Note #1).   */
        CLK_TASK_STK_SIZE,                                      /* CLK task stack size in bytes         (see Note #2).   */
        DEF_NULL                                                /* CLK task stack pointer               (See Note #3).   */
};
#endif
