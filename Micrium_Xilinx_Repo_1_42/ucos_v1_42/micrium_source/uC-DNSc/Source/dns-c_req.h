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
*                                       DNS CLIENT REQ MODULE
*
* Filename      : dns-c_req.h
* Version       : V2.00.01
* Programmer(s) : AA
*********************************************************************************************************
* Note(s)       : (1) Assumes the following versions (or more recent) of software modules are included
*                     in the project build :
*
*                     (a) uC/TCPIP    V3.00.00
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*********************************************************************************************************
*                                               MODULE
*********************************************************************************************************
*********************************************************************************************************
*/

#ifndef  DNSc_REQ_PRESENT
#define  DNSc_REQ_PRESENT

/*
*********************************************************************************************************
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*********************************************************************************************************
*/

#include  "dns-c.h"


/*
*********************************************************************************************************
*********************************************************************************************************
*                                              DATA TYPES
*********************************************************************************************************
*********************************************************************************************************
*/

typedef  enum c_req_type {
    DNSc_REQ_TYPE_IPv4,
    DNSc_REQ_TYPE_IPv6,
} DNSc_REQ_TYPE;


/*
*********************************************************************************************************
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*********************************************************************************************************
*/

void         DNScReq_ServerInit(const  DNSc_CFG       *p_cfg,
                                       DNSc_ERR       *p_err);

void         DNScReq_ServerSet (       DNSc_ADDR_OBJ  *p_addr,
                                       DNSc_ERR       *p_err);

void         DNScReq_ServerGet (       DNSc_ADDR_OBJ  *p_addr,
                                       DNSc_ERR       *p_err);

NET_SOCK_ID  DNScReq_Init      (       DNSc_ADDR_OBJ  *p_server_addr,
                                       NET_PORT_NBR    server_port,
                                       DNSc_ERR       *p_err);

NET_IF_NBR   DNSc_ReqIF_Sel    (       NET_IF_NBR      if_nbr_last,
                                       NET_SOCK_ID     sock_id,
                                       DNSc_ERR       *p_err);

void         DNSc_ReqClose     (       NET_SOCK_ID     sock_id);

CPU_INT16U   DNScReq_TxReq     (       CPU_CHAR       *p_host_name,
                                       NET_SOCK_ID     sock_id,
                                       CPU_INT16U      query_id,
                                       DNSc_REQ_TYPE   req_type,
                                       DNSc_ERR       *p_err);

DNSc_STATUS  DNScReq_RxResp    (const  DNSc_CFG       *p_cfg,
                                       DNSc_HOST_OBJ  *p_host,
                                       NET_SOCK_ID     sock_id,
                                       CPU_INT16U      query_id,
                                       DNSc_ERR       *p_err);

#endif  /* DNSc_REQ_PRESENT */
