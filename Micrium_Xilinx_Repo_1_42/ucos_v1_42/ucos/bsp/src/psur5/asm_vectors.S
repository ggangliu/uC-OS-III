@
@********************************************************************************************************
@                                  EXCEPTION VECTORS AND RESET HANDLER
@
@ File      : asm_vectors.S
@ For       : Cortex A9 on the Zynq-7000 EPP
@ Toolchain : GNU
@ Version   : 1.20
@********************************************************************************************************
@

#include  <xparameters.h>

.org 0
.text

.globl Reset_Handler
.globl Vectors
.globl _vector_table
.globl  MMUTable
.globl _boot
.globl Init_MPU

.globl OS_CPU_ARM_ExceptUndefInstrHndlr
.globl OS_CPU_ARM_ExceptSwiHndlr
.globl OS_CPU_ARM_ExceptPrefetchAbortHndlr
.globl OS_CPU_ARM_ExceptDataAbortHndlr
.globl OS_CPU_ARM_ExceptIrqHndlr
.globl OS_CPU_ARM_ExceptFiqHndlr

                                  /* Mode, correspords to bits 0-5 in CPSR */
.equ MODE_BITS,    0x1F           /* Bit mask for mode bits in CPSR */
.equ USR_MODE,     0x10           /* User mode */
.equ FIQ_MODE,     0x11           /* Fast Interrupt Request mode */
.equ IRQ_MODE,     0x12           /* Interrupt Request mode */
.equ SVC_MODE,     0x13           /* Supervisor mode */
.equ ABT_MODE,     0x17           /* Abort mode */
.equ UND_MODE,     0x1B           /* Undefined Instruction mode */
.equ SYS_MODE,     0x1F           /* System mode */

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

.equ CPU_ARM_REG_SCU_CTRL,             0xF8F00000
.equ CPU_ARM_REG_SCU_INV,              0xF8F0000C


.equ CPU_ARM_L2C_REG1_CTRL,            0xF8F02100
.equ CPU_ARM_L2C_REG1_AUX_CTRL,        0xF8F02104
.equ CPU_ARM_L2C_REG1_TAG_RAM_CTRL,    0xF8F02108
.equ CPU_ARM_L2C_REG1_DATA_RAM_CTRL,   0xF8F0210C

.equ CPU_ARM_L2C_REG7_CACHE_SYNC,      0xF8F02730
.equ CPU_ARM_L2C_REG7_CACHE_INV_PA,    0xF8F02770
.equ CPU_ARM_L2C_REG7_CACHE_INV_WAY,   0xF8F0277C
.equ CPU_ARM_L2C_REG7_CACHE_CLEAN_PA,  0xF8F027B0


                               @ Level 1 page table descriptor templates
.equ TTB_ENTRY_SUPERSEC_FAULT, 0x50006
.equ TTB_ENTRY_SUPERSEC_DEV,   0x50C06
.equ TTB_ENTRY_SUPERSEC_NORM,  0x55C06

.equ AUX_C1_FW,  0x0001
.equ AUX_C1_SMP, 0x0040


.section .vectors, "a"
.align 8
_vector_table:
Vectors:
    LDR     PC, [PC,#24]
    LDR     PC, [PC,#24]
    LDR     PC, [PC,#24]
    LDR     PC, [PC,#24]
    LDR     PC, [PC,#24]
.word     0
    LDR     PC, [PC,#24]
    LDR     PC, [PC,#24]


.word    Reset_Handler
.word    OS_CPU_ARM_ExceptUndefInstrHndlr
.word    OS_CPU_ARM_ExceptSwiHndlr
.word    OS_CPU_ARM_ExceptPrefetchAbortHndlr
.word    OS_CPU_ARM_ExceptDataAbortHndlr
.word    0
.word    OS_CPU_ARM_ExceptIrqHndlr
.word    OS_CPU_ARM_ExceptFiqHndlr

.text

.global UCOS_ARMv7Attbl_SuperSecMap
UCOS_ARMv7Attbl_SuperSecMap:
    LSR     r12, r2, #18 @ Calculate start position in the page table
    ADD     r0, r0, r12  @ r0 = TTLB_BASE + Start
    ADD     r3, r3, r2   @ r3 = Start + Range

ARMv7Attbl_Map_SuperSec_Loop1:
    MOV     r12, #0xFF000000
    BIC     r1, r1, r12 @ Clear upper byte for the PA
    ADD     r1, r1, r2  @ r1 = TTB_TEMPLATE + Addr
    MOV     r12, #16
ARMv7Attbl_Map_SuperSec_Loop2: @ Store 16 copies of the table entry
    STR     r1, [r0], #4
    SUBS    r12, r12, #1
    BNE     ARMv7Attbl_Map_SuperSec_Loop2
    ADD     r2, r2, #0x1000000 @ Move forward 16 MiB
    CMP     r2, r3
    BNE     ARMv7Attbl_Map_SuperSec_Loop1

    BX      lr


.global UCOS_PS7_DCacheInvalidateAll
UCOS_PS7_DCacheInvalidateAll:
                                    @ Invalidate L1 data cache
  MOVW     r0, #0x1FF               @ Load set index
BSP_DCacheInvalidateAll_loop_1:
  MOV     r1, #0x00000003           @ Load number of ways
BSP_DCacheInvalidateAll_loop_2:
  MOV     r2, r1, LSL #30
  ADD     r2, r2, r0, LSL #5
  MCR     p15, 0, r2, c7, c6, 2
  SUBS    r1, r1, #1
  BGE     BSP_DCacheInvalidateAll_loop_2
  SUBS    r0, r0, #1
  BGE     BSP_DCacheInvalidateAll_loop_1
  DSB

#if (UCOS_AMP_MASTER == DEF_ENABLED) /* Only the master core should invalidate the L2 Data Cache */
                                    @ Invalidate L2 unified cache
  LDR     r0, =CPU_ARM_L2C_REG7_CACHE_INV_WAY
  LDR     r1, =0xFF
  STR     r1, [r0]
BSP_DCacheInvalidateAll_wait:
  LDR     r1, [r0]
  TST     r1, #0xFF
  BNE     BSP_DCacheInvalidateAll_wait
#endif /* #if (UCOS_AMP_MASTER == DEF_ENABLED) */
  DSB
  ISB

  BX      lr

.section .boot,"axS"
_boot:
Reset_Handler:
    CPSID   IF                                       @ Disable interrupts

    MRC     p15, 0, r0, c1, c0, 0                    @ Read control register
    BIC     r0, r0, #CTRL_C1_M                       @ Disable MMU
    BIC     r0, r0, #CTRL_C1_C                       @ Disable data cache
    BIC     r0, r0, #CTRL_C1_Z                       @ Disable branch prediction
    BIC     r0, r0, #CTRL_C1_I                       @ Disable instruction cache
    MCR     p15, 0, r0, c1, c0, 0                    @ Write control register

                                                     @ Disable TCM ECC checks
    MRC     p15, 0, r0, c1, c0, 1                    @ Read ACTLR
    BIC     r0, r0, #(0x1 << 27)                     @ Disable B1TCM ECC check
    BIC     r0, r0, #(0x1 << 26)                     @ Disable B0TCM ECC check
    BIC     r0, r0, #(0x1 << 25)                     @ Disable ATCM ECC check
    MCR     p15, 0, r0, c1, c0, 1                    @ Write ACTLR
    DSB                                              @ Complete all outstanding explicit memory operations

                                                     @ Invalidate caches
    MOV r0,#0                                        @ r0 = 0
    DSB
    MCR p15, 0, r0, c7, c5, 0                        @ invalidate icache
    MCR     p15, 0, r0, c15, c5, 0                   @ Invalidate entire data cache
    ISB


    MRC     p15, 0, r0, c1, c0, 0
    BIC     r0, r0, #CTRL_C1_V                       @ Disable high vector
    MCR     p15, 0, r0, c1, c0, 0

                                                     @ Configure the stacks
    BIC     r0, r0, #0x1F
    ORR     r0, r0, #ABT_MODE
    MSR     cpsr_c, r0
    LDR     r0, =__abort_stack
    MOV     sp, r0

    BIC     r0, r0, #0x1F
    ORR     r0, r0, #UND_MODE
    MSR     cpsr_c, r0
    LDR     r0, =__undef_stack
    MOV     sp, r0

    BIC     r0, r0, #0x1F
    ORR     r0, r0, #FIQ_MODE
    MSR     cpsr_c, r0
    LDR     r0, =__fiq_stack
    MOV     sp, r0

    BIC     r0, r0, #0x1F
    ORR     r0, r0, #IRQ_MODE
    MSR     cpsr_c, r0
    LDR     r0, =__irq_stack
    MOV     sp, r0

    BIC     r0, r0, #0x1F
    ORR     r0, r0, #SVC_MODE
    MSR     cpsr_c, r0
    LDR     r0, =__supervisor_stack
    MOV     sp, r0

    @MOV     r0, #0x0
    @MCR     p15, 0, r0, c7, c5, 6                    @ Invalidate branch predictor

    @MOV     r0, #0x0
    @MCR     p15, 0, r0, c8, c7, 0                    @ Invalidate TLB

    @MOV     r0, #0
    @MCR     p15, 0, r0, c7, c5, 0                    @ Invalidate instruction cache

#if 0
    BL UCOS_PS7_DCacheInvalidateAll
#endif

    @MRC     p15, 0, r0, c3, c0, 0
    @LDR     r0, =0x55555555
    @MCR     p15, 0, r0, c3, c0, 0

    MRC     p15, 0, r0, c1, c0, 2
    ORR     r0, r0, #(0xF << 20)
    MCR     p15, 0, r0, c1, c0, 2
    ISB

#if 0
                                                     @ Start the VFP and NEON engine
    MOV     r0, #0x40000000
    VMSR    FPEXC, r0
#endif


    MOV     r0, #0
    MOVW    R1, #:lower16:__sbss_start
    MOVT    R1, #:upper16:__sbss_start
    MOVW    R2, #:lower16:__sbss_end
    MOVT    R2, #:upper16:__sbss_end
.Lloop_sbss:
    CMP     r1,r2
    BGE     .Lenclsbss
    STR     r0, [r1], #4
    B       .Lloop_sbss

.Lenclsbss:
    MOVW    R1, #:lower16:__bss_start__
    MOVT    R1, #:upper16:__bss_start__
    MOVW    R2, #:lower16:__bss_end__
    MOVT    R2, #:upper16:__bss_end__

.Lloop_bss:
    CMP     r1,r2
    BGE     .Lenclbss
    STR     r0, [r1], #4
    B       .Lloop_bss

.Lenclbss:
    BL  Init_MPU                        /* Initialize MPU */

    BL __libc_init_array

    MRC     p15, 0, r0, c1, c0, 1       /* Read ACTLR*/
    BIC     r0, r0, #(0x1 << 17)        /* Clear RSDIS bit 17 to enable return stack*/
    BIC     r0, r0, #(0x1 << 16)        /* Clear BP bit 15 and BP bit 16:*/
    BIC     r0, r0, #(0x1 << 15)        /* Normal operation, BP is taken from the global history table.*/
    ORR     r0, r0, #(0x1 << 14)        /* Disable DBWR for errata 780125 */
    MCR     p15, 0, r0, c1, c0, 1       /* Write ACTLR*/

                                        /* Enable icache and dcache */
    MRC     p15,0,r1,c1,c0,0
    LDR     r0, =0x1005
    ORR     r1,r1,r0
    DSB
    MCR     p15,0,r1,c1,c0,0
    ISB

    MOV     r0, #0
    MOV     r1, #1
    LDR     r12, =main
    BX      r12

.end
