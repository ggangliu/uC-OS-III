/*
*********************************************************************************************************
*                                       APPLICATION CONFIGURATION
*
*                             (c) Copyright 2014, Micrium, Inc., Weston, FL
*                                          All Rights Reserved
*
*                                            ZYNQ 7000 EPP
*                                               on the
*                                       ZC702 development board
*
*
* File          : app_cfg.h
* Version       : V1.00
* Programmer(s) : DC
*********************************************************************************************************
*/

#ifndef  __APP_CFG_H__
#define  __APP_CFG_H__


#include  <cpu.h>
#include  <stdio.h>


/*
*********************************************************************************************************
*                                       ADDITIONAL uC/MODULE ENABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            START TASK
*********************************************************************************************************
*/

#define  APP_CFG_TASK_START_PRIO                        5u
#define  APP_CFG_START_TASK_STK_SIZE                  256u


/*
*********************************************************************************************************
*                                             TRACING
*********************************************************************************************************
*/

#ifndef  TRACE_LEVEL_OFF
#define  TRACE_LEVEL_OFF                                0u
#endif

#ifndef  TRACE_LEVEL_INFO
#define  TRACE_LEVEL_INFO                               1u
#endif

#ifndef  TRACE_LEVEL_DBG
#define  TRACE_LEVEL_DBG                                2u
#endif

#define  APP_CFG_TRACE_LEVEL                            TRACE_LEVEL_INFO
#define  APP_CFG_TRACE                                  printf

#define  APP_TRACE_INFO(x)    ((APP_CFG_TRACE_LEVEL >= TRACE_LEVEL_INFO) ? (void)(APP_CFG_TRACE x) : (void)0)
#define  APP_TRACE_DBG(x)     ((APP_CFG_TRACE_LEVEL >= TRACE_LEVEL_DBG)  ? (void)(APP_CFG_TRACE x) : (void)0)


#endif /* __APP_CFG_H__ */
