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
* Filename      : bench_cfg.h
* Version       : V1.00
* Programmer(s) : JBL
*********************************************************************************************************
* Note(s)       : none.
*********************************************************************************************************
*/


typedef  CPU_INT64U  BENCH_TS_TMR;                              /* Benchmark timer typedef                              */

#define  BENCH_TS_GET() (CPU_TS_TmrRd())                        /* Benchmark timestamp source                           */


#define  BENCH_CFG_ITER_CNT 100u                                /* Number of iteration                                  */

#define  BENCH_CFG_WARMUP_ITER_CNT 10u                          /* Number of warm-up iterations                         */

#define  BENCH_CFG_MEMCPY_SRC 0x30000000                        /* Memory copy benchmark source address                 */

#define  BENCH_CFG_MEMCPY_DEST 0x38000000                       /* Memory copy benchmark destination address            */

#define  BENCH_CFG_MEMCPY_OCRAM_ADDR 0xFFFF0000                 /* Memory copy benchmark OCRAM address                  */

#define  BENCH_CFG_MEMCPY_OCRAM_SIZE 0x20000                    /* Memory copy benchmark OCRAM size                     */

#define  BENCH_CFG_MEMCPY_SIZE 0x2000000                        /* Memory copy benchmark size                           */

#define  BENCH_CFG_MEMCPY_WARMUP_ITER_CNT 2u                    /* Memory copy benchmark warmup iterations              */

#define  BENCH_CFG_MEMCPY_ITER_CNT 10u                          /* Memory copy benchmark iteration                      */
