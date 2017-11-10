/*
*********************************************************************************************************
*                                        uC/OS-III Benchmarks
*
*                          (c) Copyright 2009-2014; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*
*               Please feel free to use any application code labeled as 'EXAMPLE CODE' in
*               your application products.  Example code may be used as is, in whole or in
*               part, or may be used as a reference only.
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
*                                        uC/OS-III Benchmarks
*
*                                           Renesas RIN32M3
*                                               on the
*
*                                             R-IN32M3-EC
*                                          Evaluation Board
*
* Filename      : bench_global.c
* Version       : V1.00
* Programmer(s) : JBL
*********************************************************************************************************
* Note(s)       : none.
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include  <stdio.h>

#include  <cpu.h>
#include  <lib_mem.h>

#include  "bench.h"


OS_TCB   Task1TCB;
CPU_STK  Task1Stk[4096];

OS_TCB   Task2TCB;
CPU_STK  Task2Stk[4096];
