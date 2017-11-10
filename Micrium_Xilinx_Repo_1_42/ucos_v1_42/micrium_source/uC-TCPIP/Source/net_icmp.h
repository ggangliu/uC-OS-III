/*
*********************************************************************************************************
*                                             uC/TCP-IP
*                                      The Embedded TCP/IP Suite
*
*                         (c) Copyright 2004-2015; Micrium, Inc.; Weston, FL
*
*                  All rights reserved.  Protected by international copyright laws.
*
*                  uC/TCP-IP is provided in source form to registered licensees ONLY.  It is
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
*                                      NETWORK ICMP GENERIC LAYER
*                                 (INTERNET CONTROL MESSAGE PROTOCOL)
*
* Filename      : net_icmp.h
* Version       : V3.03.01
* Programmer(s) : AA
*********************************************************************************************************
* Note(s)       : none
*********************************************************************************************************
*/

#include  "net_cfg_net.h"
#include  "net_err.h"
#include  "net_ip.h"

/*
*********************************************************************************************************
*********************************************************************************************************
*                                               MODULE
*********************************************************************************************************
*********************************************************************************************************
*/

#ifndef  NET_ICMP_MODULE_PRESENT
#define  NET_ICMP_MODULE_PRESENT



/*
*********************************************************************************************************
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             PUBLIC API
*********************************************************************************************************
*/

CPU_BOOLEAN  NetICMP_TxEchoReq(CPU_INT08U       *p_addr_dest,
                               NET_IP_ADDR_LEN   addr_len,
                               CPU_INT32U        timeout_ms,
                               void             *p_data,
                               CPU_INT16U        data_len,
                               NET_ERR          *p_err);


/*
*********************************************************************************************************
*                                         INTERNAL FUNCTIONS
*********************************************************************************************************
*/


void  NetICMP_Init       (NET_ERR  *p_err);

void  NetICMP_LockAcquire(NET_ERR  *p_err);

void  NetICMP_LockRelease(void);

void  NetICMP_RxEchoReply(CPU_INT16U   id,
                          CPU_INT16U   seq,
                          CPU_INT08U  *p_data,
                          CPU_INT16U   data_len,
                          NET_ERR     *p_err);

#endif  /* NET_ICMP_MODULE_PRESENT */
