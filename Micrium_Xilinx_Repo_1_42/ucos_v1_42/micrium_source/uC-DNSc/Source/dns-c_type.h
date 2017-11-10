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
*                                     DNS CLIENT TYPE DEFINITION
*
* Filename      : dns-c_type.h
* Version       : V2.00.01
* Programmer(s) : AA
*********************************************************************************************************
* Note(s)       : None.
*********************************************************************************************************
*/

#ifndef DNSc_TYPE_PRESENT
#define DNSc_TYPE_PRESENT

#include  <cpu.h>
#include  <lib_def.h>
#include  <lib_mem.h>


/*
*********************************************************************************************************
*********************************************************************************************************
*                                           DNS CFG DATA TYPES
*********************************************************************************************************
*********************************************************************************************************
*/

typedef  struct  DNSc_cfg_task {
    CPU_INT32U  Prio;
    CPU_INT16U  StkSizeBytes;
    CPU_ADDR    StkPtr;
} DNSc_CFG_TASK;


typedef  struct DNSc_cfg {
    MEM_SEG        *MemSegPtr;

    CPU_CHAR       *ServerDfltPtr;
    CPU_INT16U      HostNameLenMax;

    CPU_INT08U      CacheEntriesMaxNbr;

    CPU_INT08U      AddrIPv4MaxPerHost;
    CPU_INT08U      AddrIPv6MaxPerHost;

    CPU_INT08U      TaskDly_ms;
    CPU_INT08U      ReqRetryNbrMax;
    CPU_INT16U      ReqRetryTimeout_ms;
} DNSc_CFG;


#endif

