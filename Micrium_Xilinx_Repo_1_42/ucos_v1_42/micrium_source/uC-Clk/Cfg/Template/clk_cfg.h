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
*                                 CLOCK / CALENDAR CONFIGURATION FILE
*
*                                              TEMPLATE
*
* Filename      : clk_cfg.h
* Version       : V3.10.00
* Programmer(s) : JDH
*                 JJL
*                 SR
*                 AA
*                 AL
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                                 MODULE
* Note(s) : (1) This configuration header file is protected from multiple pre-processor inclusion.
*********************************************************************************************************
*/

#ifndef CLK_CFG_H
#define CLK_CFG_H


/*
*********************************************************************************************************
*                                           TASKS PRIORITIES
*
* Notes: (1) Task priority configuration:
*
*           (a) If the clock timestamp is NOT an externally-maintained the Clock OS port must be
*               included in the project and the following task priority should be defined:
*
*                      CLK_TASK_PRIO
*
*               The task priority can be defined either in this configuration file 'clk_cfg.h' or in a
*               global OS tasks tasks configuration header file that must be included in 'clk_cfg.h'.
*********************************************************************************************************
*/


#ifndef  CLK_TASK_PRIO                                          /* See Note #1.                                         */
#define  CLK_TASK_PRIO                                    20
#endif


/*
*********************************************************************************************************
*                                              STACK SIZES
*                             Size of the task stacks (# of OS_STK entries)
* Notes: (1) Size of the task stacks configuration:
*
*           (a) If the clock timestamp is NOT externally-maintained the Clock OS port must be
*               included in the project and the following stack size should be defined:
*
*                      CLK_TASK_STK_SIZE
*
*               The Size of the task stacks can be defined either in this configuration file 'clk_cfg.h' or
*               in a global OS tasks configuration header file that must be included in 'clk_cfg.h'.
*********************************************************************************************************
*/

#ifndef  CLK_TASK_STK_SIZE                                      /* See Note #1.                                         */
#define  CLK_TASK_STK_SIZE                              1024
#endif


/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#include  <Source/clk_type.h>


/*
*********************************************************************************************************
*                                          CLOCK CONFIGURATION
*
* Note(s) : (1) Configure CLK_CFG_EXT_EN to enable/disable an externally-maintained clock :
*
*               (a) When ENABLED,  clock is maintained externally via hardware or another application
*                      (see also 'clk.h  Note #4').
*               (b) When DISABLED, clock is maintained internally via software
*                      (see also 'clk.h  Note #3').
*
*           (2) (a) Configure CLK_CFG_SIGNAL_EN to enable/disable signaling of the internally-maintained
*                   software clock :
*
*                   (1) When ENABLED,  clock is signaled by application calls to Clk_SignalClk().
*                   (2) When DISABLED, clock is signaled by OS-dependent timing features.
*
*               (b) CLK_CFG_SIGNAL_EN configuration is required only if CLK_CFG_EXT_EN is disabled.
*
*               See also 'clk.h  Note #3b'.
*
*           (3) (a) Configure CLK_CFG_SIGNAL_FREQ_HZ to the number of times the application will signal
*                   the clock every second.
*
*               (b) CLK_CFG_SIGNAL_FREQ_HZ configuration is required only if CLK_CFG_SIGNAL_EN is enabled.
*
*           (4) (a) Time zone is based on Coordinated Universal Time (UTC) & has valid values :
*
*                   (1) Between +|- 12 hours (+|- 43200 seconds)
*                   (2) Multiples of 15 minutes
*
*               (b) Time zone offset MUST be set in seconds.
*
*               (c) Default values CAN be changed real-time by using an appropriate function.
*********************************************************************************************************
*/

                                                                /* Configure argument check feature :                   */
#define  CLK_CFG_ARG_CHK_EN                     DEF_ENABLED
                                                                /*   DEF_DISABLED   Argument checks DISABLED            */
                                                                /*   DEF_ENABLED    Argument checks ENABLED             */


                                                                /* Configure Clock string conversion features :         */
#define  CLK_CFG_STR_CONV_EN                    DEF_ENABLED
                                                                /*   DEF_DISABLED   Clock string conversions DISABLED   */
                                                                /*   DEF_ENABLED    Clock string conversions ENABLED    */


                                                                /* Configure Clock NTP conversion features :            */
#define  CLK_CFG_NTP_EN                         DEF_ENABLED
                                                                /*   DEF_DISABLED   NTP conversions DISABLED            */
                                                                /*   DEF_ENABLED    NTP conversions ENABLED             */


                                                                /* Configure Clock Unix conversion features :           */
#define  CLK_CFG_UNIX_EN                        DEF_ENABLED
                                                                /*   DEF_DISABLED   Unix conversions DISABLED           */
                                                                /*   DEF_ENABLED    Unix conversions ENABLED            */


                                                                /* Configure External timestamp feature (see Note #1) : */
#define  CLK_CFG_EXT_EN                         DEF_DISABLED
                                                                /*   DEF_DISABLED   Software Clock maintained           */
                                                                /*   DEF_ENABLED    External Clock maintained           */


                                                                /* Configure Clock signal feature (see Note #2) :       */
#define  CLK_CFG_SIGNAL_EN                      DEF_DISABLED
                                                                /*   DEF_DISABLED   Task time delayed                   */
                                                                /*   DEF_ENABLED    Signaled via application call ...   */
                                                                /*                  ... to Clk_SignalClk()              */


#define  CLK_CFG_SIGNAL_FREQ_HZ                         1000u   /* Configure signal frequency  (see Note #3).           */

#define  CLK_CFG_TZ_DFLT_SEC                               0    /* Configure default time zone (see Note #4).           */


/*
*********************************************************************************************************
*                                        TASKS CONFIGURATION
*
* Note(s) : (1) (a) The clock and calender task configuration MUST be defined in application files,
*                   typically 'clk_cfg.c', & SHOULD be forward-declared with the exact same name &
*                   type in order to be used by the application during calls to Clk_Init().
*
*               (b) Since this task configuration structure is referenced ONLY by application files,
*                   there is NO required naming convention for this configuration structure.
*********************************************************************************************************
*/

#if (CLK_CFG_EXT_EN == DEF_DISABLED)
extern  const  CLK_TASK_CFG  ClkTaskCfg;
#endif


/*
*********************************************************************************************************
*                                     TRACE / DEBUG CONFIGURATION
*
* Note(s) : (1) By default Clk tracing is disabled. Clk tracing can be enabled by adding
*               the following #define:
*
*                   CLK_TRACE_LEVEL
*                   CLK_TRACE
*
*           (2) Configure CLK_TRACE_LEVEL with the desired output trace level :
*
*               (a) TRACE_LEVEL_OFF  will disable all output from Clk.
*
*               (b) TRACE_LEVEL_INFO will enable  minimum trace for important events.
*
*               (c) TRACE_LEVEL_DBG  will enable  general debugging trace and INFO trace.
*
*           (3) Configure CLK_TRACE to the 'printf' style function that will be used to output all the
*               tracing messages. If CLK_TRACE_LEVEL is configured to TRACE_LEVEL_OFF, there is no need
*               to configure CLK_TRACE.
*
*           (4) Configuration example:
*                   #ifndef  TRACE_LEVEL_OFF
*                   #define  TRACE_LEVEL_OFF                                   0
*                   #endif
*
*                   #ifndef  TRACE_LEVEL_INFO
*                   #define  TRACE_LEVEL_INFO                                  1
*                   #endif
*
*                   #ifndef  TRACE_LEVEL_DBG
*                   #define  TRACE_LEVEL_DBG                                   2
*                   #endif
*
*                   #define  CLK_TRACE_LEVEL                        TRACE_LEVEL_DBG
*                   #define  CLK_TRACE                              printf
*********************************************************************************************************
*/

#endif  /* CLK_CFG_H */
