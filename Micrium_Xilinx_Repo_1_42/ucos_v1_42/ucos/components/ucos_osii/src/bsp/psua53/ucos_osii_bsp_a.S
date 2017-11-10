.text

.global PS8A53_OS_TmrTickHandler
.global PS8A53_OS_TmrTickInit

PS8A53_OS_TmrTickHandler:
    STP  x29, x30, [sp, #-16]!

    MRS x0, CNTP_CVAL_EL0
    LDR x1, =0x1FFFF
    ADD x0, x0, x1
    MSR CNTP_CVAL_EL0, x0

    .global OSTimeTick
    BL OSTimeTick

    LDP  x29, x30, [sp], #16
    RET


PS8A53_OS_TmrTickInit:
    STP  x29, x30, [sp, #-16]!
    LDR x0, =0x1FFFF
    MSR CNTP_CVAL_EL0, x0
    MRS x0, CNTP_CTL_EL0
    ORR x0, x0, #0x01
    MSR CNTP_CTL_EL0, x0

    .global UCOS_IntVectSet
    MOV x0, #30
    MOV x1, #0
    MOV x2, #1
    LDR x3, =UCOS_TmrTickHandler
    LDR x4, #0
    BL UCOS_IntVectSet

    .global UCOS_IntSrcEn
    MOV x0, #30
    BL UCOS_IntSrcEn

    LDP  x29, x30, [sp], #16
    RET

.end
