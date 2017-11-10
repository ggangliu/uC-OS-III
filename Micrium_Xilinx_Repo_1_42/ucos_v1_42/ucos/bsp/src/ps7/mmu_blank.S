

/* Blank MMU Table. */
    .globl  MMUTable

    .section .mmu_tbl,"a"

MMUTable:
    .rept   4096
    .word   0
    .endr
    
    
    .end