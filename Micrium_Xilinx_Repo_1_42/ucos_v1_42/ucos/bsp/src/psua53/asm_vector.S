
#include  <xparameters.h>

.org 0
.text

.global _vector_table
.global _exit

.Lsbss_start:
    .quad   __sbss_start

.Lsbss_end:
    .quad   __sbss_end

.Lbss_start:
    .quad   __bss_start__

.Lbss_end:
    .quad   __bss_end__

.set EL3_stack,     __el3_stack
.set EL2_stack,     __el2_stack
.set EL1_stack,     __el1_stack
.set EL0_stack,     __el0_stack
.set L0Table,   MMUTableL0
.set L1Table,   MMUTableL1
.set L2Table,   MMUTableL2
.set ucos_vector_table_base,   ucos_vector_table

.align 12
_vector_table:
    .set    VBAR, _vector_table
    .org    VBAR
    B Reset_Handler
    //.org (VBAR + 0x00 + 0)
ucos_vector_table:
    //B .      // Current EL 32bits: Synchronous
    .org (VBAR + 0x80 + 0)
    B .      //                    IRQ/vIRQ
    .org (VBAR + 0x100 + 0)
    B .      //                    FIQ/vFIQ
    .org (VBAR + 0x180 + 0)
    B .      //                    Error/vError
    .org (VBAR + 0x200 + 0)
    MRS x0, ESR_EL3
    B .      // Current EL 64bits: Synchronous
    .org (VBAR + 0x280 + 0)
    B OS_CPU_ARM_ExceptIrqHndlr  // IRQ/vIRQ
    .org (VBAR + 0x300 + 0)
    B .      //                    FIQ/vFIQ
    .org (VBAR + 0x380 + 0)
    B .      //                    Error/vError


Reset_Handler:

    MRS  x4, CurrentEL               // Fetch current EL
    LSR  x4, x4, #2

    CMP  x4, #3
    B.NE skip_el3
    MOV x1, #0
    BIC x1, x1, #(0x1 << 12)         // Disable instruction cache
    BIC x1, x1, #(0x1 << 2)          // Disable data cache
    BIC x1, x1, #(0x1 << 0)          // Disable MMU
    BIC x0, x0, x1
    MSR SCTLR_EL3, x1
    DSB SY
    ISB


    MOV x1, #0
    BIC x1, x1, #(0x1 << 12)         // Disable instruction cache
    BIC x1, x1, #(0x1 << 2)          // Disable data cache
    BIC x1, x1, #(0x1 << 0)          // Disable MMU
    BIC x0, x0, x1
    MSR SCTLR_EL2, x1
    DSB SY
    ISB

skip_el3:


    MOV x1, #0
    BIC x1, x1, #(0x1 << 12)         // Disable instruction cache
    BIC x1, x1, #(0x1 << 2)          // Disable data cache
    BIC x1, x1, #(0x1 << 0)          // Disable MMU
    BIC x0, x0, x1
    MSR SCTLR_EL1, x1
    DSB SY
    ISB


    MRS  x4, CurrentEL           // Fetch current EL
    LSR  x4, x4, #2
    CMP  x4, #3
    B.NE skip_el3_cfg

    MOV w0, #0
    ORR w0, w0, #0x800           // ST=1 : Enable secure EL1 access to CNTPS_XXX_EL1
    ORR w0, w0, #0x400           // RW=1 : Next lower level is AArch64


    ORR w0, w0, #0x008          // EA=1 : Aborts routed to EL3
    ORR w0, w0, #0x004          // FIQ=1: Physical FIQ routed to EL3
    ORR w0, w0, #0x002          // IRQ=1: Physical IRQ routed to EL3

    // Uncomment to run EL1 in non-secure state
    //ORR w0, w0, #0x001          // NS=1 : Non-secure EL0 & EL1
    MSR SCR_EL3, x0

    LDR x0, =ucos_vector_table_base   // x0 = 0x80000800
    MSR VBAR_EL3, x0             // EL3 sets vector base address

    MRS x0, CPTR_EL3
    MOV w1, #0x400 // Don't trap to EL3 on SIMD access from EL0,1,2
    BIC w0, w0, w1
    MSR CPTR_EL3, x0
skip_el3_cfg:

    LDR x0, =ucos_vector_table_base   // x0 = 0x80000800
    MSR VBAR_EL1, x0             // EL1 sets vector base address


    LDR x0, =EL3_stack
    MOV SP, x0

    MRS x0, CPACR_EL1
    LDR x1, =0x300000 // Don't trap to EL1 on SIMD access from EL0,1
    ORR  w0, w0, w1
    MSR CPACR_EL1, x0


    /*configure cpu auxiliary control register EL1 */
#if (UCOS_XEN_GUEST == DEF_DISABLED)
    ldr x0,=0x80CA000       // L1 Data prefetch control - 5, Enable device split throttle, 2 independent data prefetch streams
    msr S3_1_C15_C2_0, x0   //CPUACTLR_EL1

    /*Enable hardware coherency between cores*/
    mrs      x0, S3_1_c15_c2_1      //Read EL1 CPU Extended Control Register
    orr      x0, x0, #(1 << 6)      //Set the SMPEN bit
    msr      S3_1_c15_c2_1, x0      //Write EL1 CPU Extended Control Register
    isb
#endif

    tlbi    ALLE3
    ic      IALLU                   //; Invalidate I cache to PoU
    bl  invalidate_dcaches
    dsb  sy
    isb

#if ((ZYNQ_MPSOC_A53_CONFIG_MMU == DEF_ENABLED) && (UCOS_XEN_GUEST == DEF_DISABLED))

    ldr      x1, =L0Table       //; Get address of level 0 for TTBR0_EL1
    msr      TTBR0_EL3, x1      //; Set TTBR0_EL3 (NOTE: There is no TTBR1 at EL1)


    /**********************************************
    * Set up memory attributes
    * This equates to:
    * 0 = b01000100 = Normal, Inner/Outer Non-Cacheable
    * 1 = b11111111 = Normal, Inner/Outer WB/WA/RA
    * 2 = b00000000 = Device-nGnRnE
    * 3 = b00000100 = Device-nGnRE
    * 4 = b10111011 = Normal, Inner/Outer WT/WA/RA
    **********************************************/
    ldr      x1, =0x000000BB0400FF44
    msr      MAIR_EL3, x1

        /**********************************************
        * Set up TCR_EL3
    * Physical Address Size PS =  010 -> 40bits 1TB
    * Granual Size TG0 = 00 -> 4KB
        * size offset of the memory region T0SZ = 24 -> (region size 2^(64-24) = 2^40)
        ***************************************************/
        ldr     x1,=0x80823518
        msr     TCR_EL3, x1
        isb

#endif /* #if ((ZYNQ_MPSOC_A53_CONFIG_MMU == DEF_ENABLED) && (UCOS_XEN_GUEST == DEF_DISABLED))  */



#if (UCOS_XEN_GUEST == DEF_ENABLED)

#endif /* #if (UCOS_XEN_GUEST == DEF_ENABLED) */

    /* Enable SError Exception for asynchronous abort */
    mrs  x1, DAIF
    bic  x1, x1, #(0x1<<8)
    msr  DAIF, x1

    /* Configure SCTLR_EL3 */
    mov      x1, #0             //Most of the SCTLR_EL3 bits are unknown at reset
    orr      x1, x1, #(1 << 3)  //Enable SP alignment check
#if ((ZYNQ_MPSOC_A53_ENABLE_CACHES == DEF_ENABLED) && (ZYNQ_MPSOC_A53_CONFIG_CACHES == DEF_ENABLED))
    orr      x1, x1, #(1 << 2)  //Enable D caches
    orr      x1, x1, #(1 << 12) //Enable I cache
#endif
#if ((ZYNQ_MPSOC_A53_ENABLE_MMU == DEF_ENABLED) && (ZYNQ_MPSOC_A53_CONFIG_MMU == DEF_ENABLED))
    orr      x1, x1, #(1 << 0)  //Enable MMU
#endif
    msr      SCTLR_EL3, x1
    dsb  sy
    isb


    mov x0, #0

    /* clear sbss */
    ldr     w1,.Lsbss_start     /* calculate beginning of the SBSS */
    ldr w2,.Lsbss_end       /* calculate end of the SBSS */
    uxtw    x1, w1          /*zero extension to w1 register*/
    uxtw    x2, w2          /*zero extension to w2 register*/

.Lloop_sbss:
    cmp x1,x2
    bge .Lenclsbss      /* If no SBSS, no clearing required */
    str x0, [x1], #4
    b   .Lloop_sbss

.Lenclsbss:
    /* clear bss */
    ldr w1,.Lbss_start      /* calculate beginning of the BSS */
    ldr w2,.Lbss_end        /* calculate end of the BSS */
    uxtw    x1, w1          /*zero extension to w1 register*/
    uxtw    x2, w2          /*zero extension to w2 register*/

.Lloop_bss:
    cmp x1,x2
    bge .Lenclbss       /* If no BSS, no clearing required */
    str x0, [x1], #4
    b   .Lloop_bss

.Lenclbss:

    bl __libc_init_array

    BL main

_exit:
    B .

Parking:
    B .

    invalidate_dcaches:

    dmb     ISH
    mrs     x0, CLIDR_EL1          //; x0 = CLIDR
    ubfx    w2, w0, #24, #3        //; w2 = CLIDR.LoC
    cmp     w2, #0                 //; LoC is 0?
    b.eq    invalidateCaches_end   //; No cleaning required and enable MMU
    mov     w1, #0                 //; w1 = level iterator

invalidateCaches_flush_level:
    add     w3, w1, w1, lsl #1     //; w3 = w1 * 3 (right-shift for cache type)
    lsr     w3, w0, w3             //; w3 = w0 >> w3
    ubfx    w3, w3, #0, #3         //; w3 = cache type of this level
    cmp     w3, #2                 //; No cache at this level?
    b.lt    invalidateCaches_next_level

    lsl     w4, w1, #1
    msr     CSSELR_EL1, x4         //; Select current cache level in CSSELR
    isb                            //; ISB required to reflect new CSIDR
    mrs     x4, CCSIDR_EL1         //; w4 = CSIDR

    ubfx    w3, w4, #0, #3
    add     w3, w3, #2             //; w3 = log2(line size)
    ubfx    w5, w4, #13, #15
    ubfx    w4, w4, #3, #10        //; w4 = Way number
    clz     w6, w4                 //; w6 = 32 - log2(number of ways)

invalidateCaches_flush_set:
    mov     w8, w4                 //; w8 = Way number
invalidateCaches_flush_way:
    lsl     w7, w1, #1             //; Fill level field
    lsl     w9, w5, w3
    orr     w7, w7, w9             //; Fill index field
    lsl     w9, w8, w6
    orr     w7, w7, w9             //; Fill way field
    dc      CISW, x7               //; Invalidate by set/way to point of coherency
    subs    w8, w8, #1             //; Decrement way
    b.ge    invalidateCaches_flush_way
    subs    w5, w5, #1             //; Descrement set
    b.ge    invalidateCaches_flush_set

invalidateCaches_next_level:
    add     w1, w1, #1             //; Next level
    cmp     w2, w1
    b.gt    invalidateCaches_flush_level

invalidateCaches_end:
    ret


.end
