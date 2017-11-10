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
* Filename      : bench.h
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

#include  <Source/os.h>

#include  "bench_cfg.h"

typedef struct bench_res {
    CPU_CHAR       *BenchName;
    BENCH_TS_TMR    TotalTime;
    BENCH_TS_TMR    Avg;
    BENCH_TS_TMR    Min;
    BENCH_TS_TMR    Max;
    CPU_INT32U      IterCnt;
} BENCH_RES;


void  BenchResInit       (BENCH_RES    *res);

void  BenchResUpdate     (BENCH_RES    *res,
                       BENCH_TS_TMR  iter_time);

void  BenchResFin   (BENCH_RES    *res);

void  BenchResPrint      (BENCH_RES    *res);

void  BenchSGITrig    (void);

void  BenchSGIReg     (void         * func);

void  BenchSGIHandler (void *p_arg, CPU_INT32U cpu_id);

void  BenchRun        (void);
