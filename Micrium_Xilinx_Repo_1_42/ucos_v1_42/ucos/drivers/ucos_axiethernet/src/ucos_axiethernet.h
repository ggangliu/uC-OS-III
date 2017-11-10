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
*                                             AXI ETHERNET
*
* Filename      : ucos_axiethernet.h
* Version       : V1.42
* Programmer(s) : JBL
*********************************************************************************************************
*/

#ifndef  UCOS_AXIETHERNET_PRESENT
#define  UCOS_AXIETHERNET_PRESENT


/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#include <lib_def.h>
#include <cpu.h>

/*
*********************************************************************************************************
*                                        STRUCTURE DEFINITIONS
*********************************************************************************************************
*/

typedef struct {
    CPU_INT32U  DeviceId;
    CPU_INT32U  BaseAddress;
    CPU_INT32U  EmacType;
    CPU_INT32U  TxCSum;
    CPU_INT32U  RxCSum;
    CPU_INT32U  PhyType;
    CPU_INT32U  TXVlanTran;
    CPU_INT32U  RXVlanTran;
    CPU_INT32U  TXVlanTag;
    CPU_INT32U  RXVlanTag;
    CPU_INT32U  TXVlanStrip;
    CPU_INT32U  RXVlanStrip;
    CPU_INT32U  MCastExt;
    CPU_INT32U  Stats;
    CPU_INT32U  AVB;
    CPU_INT32U  SGMIIOverLVDS;
    CPU_INT32U  Intr;
    CPU_INT32U  ConnType;
    CPU_INT32U  ConnAddr;
    CPU_INT32U  PhyAddr;
    CPU_INT32U  RXIntr;
    CPU_INT32U  TCIntr;
} UCOS_AXIETHERNET_Config;


#endif /* UCOS_AXIETHERNET_PRESENT */
