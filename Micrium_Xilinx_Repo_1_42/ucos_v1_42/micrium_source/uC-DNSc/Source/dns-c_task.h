/*
*********************************************************************************************************
*                                               uC/DNSc
*                                     Domain Name Server (client)
*
*                         (c) Copyright 2004-2014; Micrium, Inc.; Weston, FL
*
*                  All rights reserved.  Protected by international copyright laws.
*
*                  uC/DNSc is provided in source form to registered licensees ONLY.  It is
*                  illegal to distribute this source code to any third party unless you receive
*                  written permission by an authorized Micrium representative.  Knowledge of
*                  the source code may NOT be used to develop a similar product.
*
*                  Please help us continue to provide the Embedded community with the finest
*                  software available.  Your honesty is greatly appreciated.
*
*                  You can find our product's user manual, API reference, release notes and
*                  more information at: https://doc.micrium.com
*
*                  You can contact us at: http://www.micrium.com
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                       DNS CLIENT TASK MODULE
*
* Filename      : dns-c_task.h
* Version       : V2.00.01
* Programmer(s) : AA
*********************************************************************************************************
* Note(s)       : (1) Assumes the following versions (or more recent) of software modules are included
*                     in the project build :
*
*                     (a) uC/Common-KAL V1.00.00
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*********************************************************************************************************
*                                               MODULE
*********************************************************************************************************
*********************************************************************************************************
*/

#ifndef  DNSc_KAL_PRESENT
#define  DNSc_TASK_PRESENT

/*
*********************************************************************************************************
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*********************************************************************************************************
*/

#include  "dns-c.h"
#include  "dns-c_type.h"


/*
*********************************************************************************************************
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*********************************************************************************************************
*/

void         DNScTask_Init       (const  DNSc_CFG       *p_cfg,
                                  const  DNSc_CFG_TASK  *p_task_cfg,
                                         DNSc_ERR       *p_err);

DNSc_STATUS  DNScTask_HostResolve(       DNSc_HOST_OBJ  *p_host,
                                         DNSc_FLAGS      flags,
                                         DNSc_REQ_CFG   *p_cfg,
                                         DNSc_ERR       *p_err);

#endif  /* DNSc_KAL_PRESENT */
