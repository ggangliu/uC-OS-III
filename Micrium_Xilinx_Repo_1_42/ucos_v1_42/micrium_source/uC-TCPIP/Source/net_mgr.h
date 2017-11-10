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
*                                      NETWORK LAYER MANAGEMENT
*
* Filename      : net_mgr.h
* Version       : V3.03.01
* Programmer(s) : SR
*********************************************************************************************************
* Note(s)       : (1) Network layer manager MAY eventually maintain each interface's network address(s)
*                     & address configuration. #### NET-809
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*********************************************************************************************************
*/

#include  "net_cfg_net.h"
#include  "net_err.h"
#include  "../IF/net_if.h"

/*
*********************************************************************************************************
*********************************************************************************************************
*                                               MODULE
*********************************************************************************************************
*********************************************************************************************************
*/

#ifndef  NET_MGR_MODULE_PRESENT
#define  NET_MGR_MODULE_PRESENT

/*
*********************************************************************************************************
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                         INTERNAL FUNCTIONS
*********************************************************************************************************
*/

void         NetMgr_Init                     (NET_ERR            *p_err);


                                                                                    /* ------ NET MGR ADDR FNCTS ------ */
void         NetMgr_GetHostAddrProtocol      (NET_IF_NBR          if_nbr,
                                              NET_PROTOCOL_TYPE   protocol_type,
                                              CPU_INT08U         *p_addr_protocol_tbl,
                                              CPU_INT08U         *p_addr_protocol_tbl_qty,
                                              CPU_INT08U         *p_addr_protocol_len,
                                              NET_ERR            *p_err);

NET_IF_NBR   NetMgr_GetHostAddrProtocolIF_Nbr(NET_PROTOCOL_TYPE   protocol_type,
                                              CPU_INT08U         *p_addr_protocol,
                                              CPU_INT08U          addr_protocol_len,
                                              NET_ERR            *p_err);


CPU_BOOLEAN  NetMgr_IsValidAddrProtocol      (NET_PROTOCOL_TYPE   protocol_type,
                                              CPU_INT08U         *p_addr_protocol,
                                              CPU_INT08U          addr_protocol_len);

CPU_BOOLEAN  NetMgr_IsAddrsCfgdOnIF          (NET_IF_NBR          if_nbr,
                                              NET_ERR            *p_err);

CPU_BOOLEAN  NetMgr_IsAddrProtocolInit       (NET_PROTOCOL_TYPE   protocol_type,
                                              CPU_INT08U         *p_addr_protocol,
                                              CPU_INT08U          addr_protocol_len);

#ifdef  NET_MCAST_MODULE_EN
CPU_BOOLEAN  NetMgr_IsAddrProtocolMulticast  (NET_PROTOCOL_TYPE   protocol_type,
                                              CPU_INT08U         *p_addr_protocol,
                                              CPU_INT08U          addr_protocol_len);
#endif

#ifdef  NET_IPv4_MODULE_EN
CPU_BOOLEAN  NetMgr_IsAddrProtocolConflict   (NET_IF_NBR          if_nbr);
#endif

void         NetMgr_ChkAddrProtocolConflict  (NET_IF_NBR          if_nbr,
                                              NET_PROTOCOL_TYPE   protocol_type,
                                              CPU_INT08U         *p_addr_protocol,
                                              CPU_INT08U          addr_protocol_len,
                                              NET_ERR            *p_err);


/*
*********************************************************************************************************
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*********************************************************************************************************
*/

#endif  /* NET_MGR_MODULE_PRESENT */
