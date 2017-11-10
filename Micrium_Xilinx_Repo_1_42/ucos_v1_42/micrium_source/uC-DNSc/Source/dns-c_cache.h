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
*                                       DNS CLIENT CACHE MODULE
*
* Filename      : dns-c_cache.h
* Version       : V2.00.01
* Programmer(s) : AA
*********************************************************************************************************
* Note(s)       : (1) Assumes the following versions (or more recent) of software modules are included
*                     in the project build :
*
*                     (a) uC/LIB    V1.37.00
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*********************************************************************************************************
*                                               MODULE
*
* Note(s) : (1) This header file is protected from multiple pre-processor inclusion through use of the
*               pre-processor macro definition.
*********************************************************************************************************
*********************************************************************************************************
*/

#ifndef  DNSc_CACHE_PRESENT                                     /* See Note #1.                                         */
#define  DNSc_CACHE_PRESENT


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

typedef  struct  DNSc_cache_item  DNSc_CACHE_ITEM;

struct DNSc_cache_item {
    DNSc_HOST_OBJ    *HostPtr;
    DNSc_CACHE_ITEM  *NextPtr;
};


/*
*********************************************************************************************************
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*********************************************************************************************************
*/

void            DNScCache_Init          (const  DNSc_CFG       *p_cfg,
                                                DNSc_ERR       *p_err);

void            DNScCache_Clr           (       DNSc_ERR       *p_err);

void            DNScCache_HostInsert    (       DNSc_HOST_OBJ  *p_host,
                                                DNSc_ERR       *p_err);

void            DNScCache_HostRemove    (       DNSc_HOST_OBJ  *p_host);

void            DNScCache_HostSrchRemove(       CPU_CHAR       *p_host_name,
                                                DNSc_ERR       *p_err);

DNSc_STATUS     DNScCache_Srch          (       CPU_CHAR       *p_host_name,
                                                DNSc_ADDR_OBJ  *p_addrs,
                                                CPU_INT08U      addr_nbr_max,
                                                CPU_INT08U     *p_addr_nbr_rtn,
                                                DNSc_FLAGS      flags,
                                                DNSc_ERR       *p_err);

DNSc_HOST_OBJ  *DNScCache_HostObjGet    (       CPU_CHAR       *p_host_name,
                                                DNSc_FLAGS      flags,
                                                DNSc_REQ_CFG   *p_cfg,
                                                DNSc_ERR       *p_err);

void            DNScCache_HostObjFree   (       DNSc_HOST_OBJ  *p_host);

void            DNScCache_HostAddrInsert(const  DNSc_CFG       *p_cfg,
                                                DNSc_HOST_OBJ  *p_host,
                                                DNSc_ADDR_OBJ  *p_addr,
                                                DNSc_ERR       *p_err);

DNSc_ADDR_OBJ  *DNScCache_AddrObjGet    (       DNSc_ERR       *p_err);

void            DNScCache_AddrObjFree   (       DNSc_ADDR_OBJ  *p_addr);

void            DNScCache_AddrObjSet    (       DNSc_ADDR_OBJ  *p_addr,
                                                CPU_CHAR       *p_str_addr,
                                                DNSc_ERR       *p_err);

DNSc_STATUS     DNScCache_ResolveHost   (const  DNSc_CFG       *p_cfg,
                                                DNSc_HOST_OBJ  *p_host,
                                                DNSc_ERR       *p_err);

CPU_INT16U      DNScCache_ResolveAll    (const  DNSc_CFG       *p_cfg,
                                                DNSc_ERR       *p_err);

#endif /* DNSc_CACHE_PRESENT */
