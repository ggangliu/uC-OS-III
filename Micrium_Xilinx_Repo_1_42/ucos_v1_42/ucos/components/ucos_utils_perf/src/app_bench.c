/*
*********************************************************************************************************
*                                            EXAMPLE CODE
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
*                                     BENCHMARK APPLICATION CODE
*
*                                           Renesas RIN32M3
*                                               on the
*
*                                             R-IN32M3-EC
*                                          Evaluation Board
*
* Filename      : app_bench.c
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
#include  <os_cfg_app.h>
#include  <ucos_bsp.h>
#include  <ucos_int.h>


#include  "bench.h"
#include  <ucos_scugic.h>


/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/

void    *BenchSGIFunc;


/*
*********************************************************************************************************
*                                             BenchResInit()
*
* Description : Initialize a benchmark result.
*
* Arguments   : none.
*
* Returns     : none.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void BenchResInit(BENCH_RES *res)
{
    res->BenchName = "";
    res->TotalTime = 0u;
    res->IterCnt = 0u;
    res->Avg = 0u;
    res->Max = 0u;
    res->Min = -1u;
}


/*
*********************************************************************************************************
*                                          BenchResUpdate()
*
* Description : Update a benchmark result.
*
* Arguments   : none.
*
* Returns     : none.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void BenchResUpdate(BENCH_RES *res, BENCH_TS_TMR iter_time)
{
    res->TotalTime += iter_time;
    res->IterCnt++;

    if(iter_time > res->Max) {
        res->Max = iter_time;
    }

    if(iter_time < res->Min) {
        res->Min = iter_time;
    }
}


/*
*********************************************************************************************************
*                                            BenchResFin()
*
* Description : Finalize a benchmark result.
*
* Arguments   : none.
*
* Returns     : none.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void BenchResFin(BENCH_RES *res)
{
    res->Avg = res->TotalTime / res->IterCnt;
}


/*
*********************************************************************************************************
*                                            BenchResPrint()
*
* Description : Print/Save a benchmark result.
*
* Arguments   : none.
*
* Returns     : none.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void BenchResPrint(BENCH_RES *res)
{
    UCOS_Printf("--------------------------------------------------------------\r\n");
    UCOS_Printf("%s:\r\n", res->BenchName);
    UCOS_Printf("Iteration: %d Average: %d Max: %d Min %d\r\n", res->IterCnt, (CPU_INT32U)res->Avg * 2, (CPU_INT32U)res->Max * 2, (CPU_INT32U)res->Min * 2);
}


/*
*********************************************************************************************************
*                                            BenchSGITrig()
*
* Description : Trigger a software generated interrupt.
*
* Arguments   : none.
*
* Returns     : none.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BenchSGITrig()
{
	SCUGIC_SGITrig(1, DEF_BIT_00);
}


/*
*********************************************************************************************************
*                                            BenchSGIReg()
*
* Description : Dynamically register an SGI handler.
*
* Arguments   : none.
*
* Returns     : none.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BenchSGIReg (void * func)
{
    BenchSGIFunc = func;
    UCOS_IntVectSet(1, 0, DEF_BIT_00, BenchSGIHandler, DEF_NULL);
    UCOS_IntSrcEn(1);
}


/*
*********************************************************************************************************
*                                          BenchSGIHandler()
*
* Description : Generic SGI handler.
*
* Arguments   : none.
*
* Returns     : none.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BenchSGIHandler(void *p_arg, CPU_INT32U cpu_id)
{
    OSIntNestingCtr++;

    (*((void (*)(void))BenchSGIFunc))();

    OSIntExit();
}
