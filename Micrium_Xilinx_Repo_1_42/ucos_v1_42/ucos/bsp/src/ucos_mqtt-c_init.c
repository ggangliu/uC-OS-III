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
*                                          uC/MQTT INIT CODE
*
* Filename      : ucos_mqtt-c_init.c
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

#if (APP_TCPIP_ENABLED == DEF_ENABLED)
#include  <IP/IPv4/net_ipv4.h>
#include  <Source/net_type.h>
#include  <Source/net_ip.h>


#if (APP_MQTTC_ENABLED == DEF_ENABLED)
#include  <Client/Source/mqtt-c.h>
#endif


#if (APP_MQTTC_ENABLED == DEF_ENABLED)

const  NET_TASK_CFG  MQTTc_TaskCfg = {                          /* Cfg for MQTTc internal task.                         */
    MQTTc_OS_CFG_TASK_PRIO,                                     /* MQTTc internal task prio.                            */
    MQTTc_OS_CFG_TASK_STK_SIZE,                                 /* MQTTc internal task stack size.                      */
    DEF_NULL                                                    /* Ptr to start of MQTTc internal stack.                */
};


const  MQTTc_CFG MQTTc_Cfg = {
    MQTTc_CFG_MSG_QTY,
    MQTTc_CFG_INACTIVITY_TIMEOUT,
    MQTTc_CFG_INTERNAL_TASK_DLY
};

CPU_BOOLEAN UCOS_MQTTc_Init (void)
{
    MQTTc_ERR  err_mqttc;


#if (UCOS_START_DEBUG_TRACE == DEF_ENABLED)
    UCOS_Print("UCOS - Initializing uC/MQTT.\r\n");
#endif

    MQTTc_Init(&MQTTc_Cfg,
               &MQTTc_TaskCfg,
                DEF_NULL,
               &err_mqttc);

    if (err_mqttc != MQTTc_ERR_NONE) {
#if (UCOS_START_DEBUG_TRACE == DEF_ENABLED)
        UCOS_Printf("UCOS - Error initializing uC/MQTTc. Error code %d\r\n", err_mqttc);
#endif
        return (DEF_FAIL);
    }

    return (DEF_OK);
}

#endif /* #if (APP_MQTTC_ENABLED == DEF_ENABLED) */
#endif /* #if (APP_TCPIP_ENABLED == DEF_ENABLED) */
