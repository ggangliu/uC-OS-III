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
*
* Filename      : app_cfg.h
* Version       : V1.42
* Programmer(s) : JBL
*********************************************************************************************************
*/

#ifndef  UCOS_APP_CFG_PRESENT
#define  UCOS_APP_CFG_PRESENT

#include  <lib_def.h>

#include  <xparameters.h>

#define  APP_CPU_ENABLED DEF_DISABLED

#define  APP_LIB_ENABLED DEF_DISABLED

#define  APP_COMMON_ENABLED DEF_DISABLED

#define  APP_SHELL_ENABLED DEF_DISABLED

#define  APP_CLK_ENABLED DEF_DISABLED

#define  APP_OSIII_ENABLED DEF_DISABLED

#define  APP_OSII_ENABLED  DEF_DISABLED

#define  APP_TCPIP_ENABLED  DEF_DISABLED

#define  APP_TCPIP_EXP_ENABLED  DEF_DISABLED

#define  APP_DHCPC_ENABLED  DEF_DISABLED

#define  APP_DNSC_ENABLED  DEF_DISABLED

#define  APP_HTTPC_ENABLED  DEF_DISABLED

#define  APP_MQTTC_ENABLED  DEF_DISABLED

#define  APP_TELNETS_ENABLED  DEF_DISABLED

#define  APP_IPERF_ENABLED  DEF_DISABLED

#define  APP_FS_ENABLED  DEF_DISABLED

#define  APP_USBD_ENABLED  DEF_DISABLED

#define  APP_USBH_ENABLED  DEF_DISABLED

#define  APP_OPENAMP_ENABLED  DEF_DISABLED

#define OS_TASK_TMR_PRIO 3

#endif /* #ifndef  UCOS_APP_CFG_PRESENT */

