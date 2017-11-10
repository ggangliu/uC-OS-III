@
@********************************************************************************************************
@                                   Cortex A9 Low Level Functions
@
@ File      : ucos_cpu_cortexa9.S
@ For       : Cortex A9 on the Zynq-7000 EPP
@ Toolchain : GNU
@ Version   : 1.42
@********************************************************************************************************
@

.equ CTRL_C1_M,  0x0001
.equ CTRL_C1_A,  0x0002
.equ CTRL_C1_C,  0x0004
.equ CTRL_C1_W,  0x0008
.equ CTRL_C1_S,  0x0100
.equ CTRL_C1_R,  0x0200
.equ CTRL_C1_Z,  0x0800
.equ CTRL_C1_I,  0x1000
.equ CTRL_C1_V,  0x2000
.equ CTRL_C1_RR, 0x4000



.global CPU_CortexA9_L1DCacheEn
CPU_CortexA9_L1DCacheEn:
    MRC     p15, 0, r0, c1, c0, 0
    ORR     r0, r0, #CTRL_C1_C
    MCR     p15, 0, r0, c1, c0, 0
    DSB
    ISB
    BX      lr

    .global CPU_CortexA9_L1ICacheEn
CPU_CortexA9_L1ICacheEn:
    MRC     p15, 0, r0, c1, c0, 0
    ORR     r0, r0, #CTRL_C1_I
    MCR     p15, 0, r0, c1, c0, 0
    DSB
    ISB
    BX      lr

    .global CPU_CortexA9_BranchPredictEn
CPU_CortexA9_BranchPredictEn:
    MRC     p15, 0, r0, c1, c0, 0
    ORR     r0, r0, #CTRL_C1_Z
    MCR     p15, 0,r0, c1, c0, 0
    DSB
    BX      lr

   .global CPU_CortexA9_L1PrefetchEn
CPU_CortexA9_L1PrefetchEn:
    MRC     p15, 0, r0, c1, c0, 1
    ORR     r0, r0, #0x4
    MCR     p15, 0, r0, c1, c0, 1
    DSB
    BX      lr

   .global CPU_CortexA9_L2PrefetchEn
CPU_CortexA9_L2PrefetchEn:
    MRC     p15, 0, r0, c1, c0, 1
    ORR     r0, r0, #0x2
    MCR     p15, 0, r0, c1, c0, 1
    DSB
    BX      lr

   .global CPU_CortexA9_FLZEn
CPU_CortexA9_FLZEn:
    MRC     p15, 0, r0, c1, c0, 1
    ORR     r0, r0, #0x8
    MCR     p15, 0, r0, c1, c0, 1
    DSB
    BX      lr
