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
* Filename      : bench.c
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

#include  <cpu.h>
#include  <ucos_bsp.h>
#include  <lib_mem.h>
#include  <Source/os.h>
#include  <os_cfg_app.h>

#include  "bench.h"


/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

void  bench_ctxsw               (void);
void  bench_sempost             (void);
void  bench_sempend             (void);
void  bench_sempost_noctxsw     (void);
void  bench_sempend_noctxsw     (void);
void  bench_tasksempost         (void);
void  bench_tasksempend         (void);
void  bench_tasksempost_noctxsw (void);
void  bench_tasksempend_noctxsw (void);
void  bench_qpost               (void);
void  bench_qpend               (void);
void  bench_qpost_noctxsw       (void);
void  bench_qpend_noctxsw       (void);
void  bench_taskqpost           (void);
void  bench_taskqpend           (void);
void  bench_taskqpost_noctxsw   (void);
void  bench_taskqpend_noctxsw   (void);
void  bench_flagpost            (void);
void  bench_flagpend            (void);
void  bench_flagpost_noctxsw    (void);
void  bench_flagpend_noctxsw    (void);
void  bench_isrctxsw            (void);
void  bench_isrresp             (void);
void  bench_isrrecovery         (void);
void  bench_isrsempost          (void);
void  bench_memcpy              (void);
void  bench_memcpy_libc         (void);
void  bench_memcpy_ocram_src    (void);
void  bench_memcpy_ocram_src_libc (void);
void  bench_memcpy_ocram_dest   (void);
void  bench_memcpy_ocram_dest_libc (void);

/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/

CPU_FNCT_VOID BenchTestList[] = {
    bench_ctxsw,
    bench_sempost,
    bench_sempend,
    bench_sempost_noctxsw,
    bench_sempend_noctxsw,
#ifndef HWOS_OS_VERSION
    bench_tasksempost,
    bench_tasksempend,
    bench_tasksempost_noctxsw,
    bench_tasksempend_noctxsw,
#endif
    bench_qpost,
    bench_qpend,
    bench_qpost_noctxsw,
    bench_qpend_noctxsw,
#ifndef HWOS_OS_VERSION
    bench_taskqpost,
    bench_taskqpend,
    bench_taskqpost_noctxsw,
    bench_taskqpend_noctxsw,
#endif
    bench_flagpost,
    bench_flagpend,
    bench_flagpost_noctxsw,
    bench_flagpend_noctxsw,
    bench_isrctxsw,
    bench_isrresp,
    bench_isrrecovery,
    bench_isrsempost,
    bench_memcpy,
    bench_memcpy_libc,
    bench_memcpy_ocram_src,
    bench_memcpy_ocram_src_libc,
    bench_memcpy_ocram_dest,
    bench_memcpy_ocram_dest_libc,
    DEF_NULL,
};


/*
*********************************************************************************************************
*                                             BenchRun()
*
* Description : Run the listed benchmarks.
*
* Arguments   : none.
*
* Returns     : none.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BenchRun (void)
{
    CPU_FNCT_VOID *p_bench_test;


    p_bench_test = &BenchTestList[0];

    while(*p_bench_test != DEF_NULL) {
        (*p_bench_test)();

        p_bench_test++;
    }
}


