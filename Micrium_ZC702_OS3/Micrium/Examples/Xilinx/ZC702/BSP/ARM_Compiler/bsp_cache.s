;
;********************************************************************************************************
;                                          CACHE UTILITY FUNCTIONS
;
; File      : bsp_cache.s
; For       : Cortex A9 on the Zynq-7000 EPP
; Toolchain : ARMCC
;
; Notes : none.
;********************************************************************************************************
;

;********************************************************************************************************
;                                           MACROS AND DEFINIITIONS
;********************************************************************************************************

                                ; MMU C1
CTRL_C1_M    EQU  0x0001
CTRL_C1_A    EQU  0x0002
CTRL_C1_C    EQU  0x0004
CTRL_C1_W    EQU  0x0008
CTRL_C1_S    EQU  0x0100
CTRL_C1_R    EQU  0x0200
CTRL_C1_Z    EQU  0x0800
CTRL_C1_I    EQU  0x1000
CTRL_C1_RR   EQU  0x4000


    PRESERVE8

    AREA  BSP_Cache,CODE,READONLY

    ENTRY


CPU_ARM_REG_SCU_CTRL             EQU  0xF8F00000
CPU_ARM_REG_SCU_INV              EQU  0xF8F0000C


CPU_ARM_L2C_REG1_CTRL            EQU  0xF8F02100
CPU_ARM_L2C_REG1_AUX_CTRL        EQU  0xF8F02104
CPU_ARM_L2C_REG1_TAG_RAM_CTRL    EQU  0xF8F02108
CPU_ARM_L2C_REG1_DATA_RAM_CTRL   EQU  0xF8F0210C

CPU_ARM_L2C_REG7_CACHE_SYNC      EQU  0xF8F02730
CPU_ARM_L2C_REG7_CACHE_INV_PA    EQU  0xF8F02770
CPU_ARM_L2C_REG7_CACHE_INV_WAY   EQU  0xF8F0277C
CPU_ARM_L2C_REG7_CACHE_CLEAN_PA  EQU  0xF8F027B0



;********************************************************************************************************
;                                      BSP_DCacheInvalidateAll()
;
; Description : Invalidate L1 & L2 data cache. Used during initialisation sequence.
;
; Prototypes  : void  BSP_DCacheInvalidateAll (void)
;
; Argument(s) : none.
;********************************************************************************************************

    EXPORT BSP_DCacheInvalidateAll

BSP_DCacheInvalidateAll FUNCTION

                                    ; Invalidate L1 data cache
  MOV     r0, #0x1FF                ; Load set index
BSP_DCacheInvalidateAll_loop_1
  MOV     r1, #0x00000003           ; Load number of ways
BSP_DCacheInvalidateAll_loop_2
  MOV     r2, r1, LSL #30
  ADD     r2, r2, r0, LSL #5
  MCR     p15, 0, r2, c7, c6, 2
  SUBS    r1, r1, #1
  BGE     BSP_DCacheInvalidateAll_loop_2
  SUBS    r0, r0, #1
  BGE     BSP_DCacheInvalidateAll_loop_1
  DSB

  BX      lr

    ENDFUNC


;********************************************************************************************************
;                                         BSP_L2C310Config()
;
; Description : Set tag and data RAM access latency. Used during initialisation sequence.
;
; Prototypes  : void  BSP_L2C310Config (void)
;
; Argument(s) : none.
;********************************************************************************************************

    EXPORT BSP_L2C310Config

BSP_L2C310Config FUNCTION

    MOV32   r0, #CPU_ARM_L2C_REG1_TAG_RAM_CTRL
    MOV     r1, #0x00000111
    ;MOV     r1, #0x00000000
    STR     r1, [r0]

    MOV32   r0, #CPU_ARM_L2C_REG1_DATA_RAM_CTRL
    MOV     r1, #0x00000121
    ;MOV     r1, #0x00000010
    STR     r1, [r0]

    MOV32   r0, CPU_ARM_L2C_REG1_AUX_CTRL
    MOV32   r1, #(0x02060000 :OR: 0x40000000 :OR: 0x10000000 :OR: 0x20000000 :OR: 0x1)
    STR     r1, [r0]

    DSB

    BX      lr

    ENDFUNC


;********************************************************************************************************
;                                           BSP_CachesEn()
;
; Description : Enable L1 Data and Instruction cache as well as the L2 unified cache.
;
; Prototypes  : void  BSP_L2C310Config (void)
;
; Argument(s) : None
;********************************************************************************************************

    EXPORT BSP_CachesEn

BSP_CachesEn FUNCTION

    MRC     p15, 0, r0, c1, c0, 1
    ORR     r0, r0, #0xE
    MCR     p15, 0, r0, c1, c0, 1

    MRC     p15, 0, r0, c1, c0, 0
    ORR     r0, r0, #CTRL_C1_C
    ORR     r0, r0, #CTRL_C1_I
    MCR     p15, 0, r0, c1, c0, 0
    DSB
    ISB

    MOV32   r0, #CPU_ARM_L2C_REG1_CTRL
    MOV     r1, #1
    STR     r1, [r0]

    DSB

    BX      lr

    ENDFUNC


;********************************************************************************************************
;                                       BSP_BranchPredictorEn()
;
; Description : Enable branch prediction.
;
; Prototypes  : void  BSP_BranchPredictorEn (void)
;
; Argument(s) : None
;********************************************************************************************************

    EXPORT BSP_BranchPredictorEn

BSP_BranchPredictorEn FUNCTION

   MRC     p15, 0, r0, c1, c0, 0
   ORR     r0, r0, #CTRL_C1_Z
   MCR     p15, 0,r0, c1, c0, 0
   DSB

   BX      lr

    ENDFUNC


;********************************************************************************************************
;                                             BSP_SCUEn()
;
; Description : Enable the Snoop Control Unit (Globally).
;
; Prototypes  : void  BSP_SCUEn (void)
;
; Argument(s) : (1) SCU Tag ram should be invalidated before calling this function.
;********************************************************************************************************

    EXPORT BSP_SCUEn

BSP_SCUEn FUNCTION

    MOV32   r0, #CPU_ARM_REG_SCU_CTRL
    LDR     r1, [r0]
    ORR     r1, r1, #1
    STR     r1, [r0]
    DSB

    BX      lr

    ENDFUNC


;********************************************************************************************************
;                                       BSP_SCUInvalidateAll()
;
; Description : Invaliate SCU tag RAM.
;
; Prototypes  : void  BSP_SCUInvalidateAll (void)
;
; Argument(s) : None
;********************************************************************************************************

    EXPORT BSP_SCUInvalidateAll

BSP_SCUInvalidateAll FUNCTION

    AND     r0, r0, #0x03
    MOV     r0, r0, LSL #2
    AND     r1, r1, #0x0F
    MOV     r1, r1, LSL r0
    MOV32   r2, #CPU_ARM_REG_SCU_INV
    STR     r1, [r2]
    DSB

    BX      lr

    ENDFUNC


;********************************************************************************************************
;                                      INVALIDATE DATA CACHE RANGE
;
; Description : Invalidate a range of data cache by MVA.
;
; Prototypes  : void  BSP_DCache_InvalidateRange  (void       *p_mem,
;                                                  CPU_SIZE_T  range);
;
; Argument(s) : p_mem    Start address of the region to invalidate.
;
;               range    Size of the region to invalidate in bytes.
;
; Note(s)     : (1) p_mem value not aligned to 32 bytes will be truncated to the next lowest aligned
;                   address.
;
;               (2) range value not a multiple of 32 will be the next multiple of 32 that includes
;                   the start address and the end of the specified range.
;********************************************************************************************************

    EXPORT BSP_DCache_InvalidateRange

BSP_DCache_InvalidateRange FUNCTION
    MOV r3, r0
    ADD r1, r1, r0
    BIC r3, r3, #31

    MOV32  r2, #CPU_ARM_L2C_REG7_CACHE_INV_PA
Invalidate_RangeL2
    STR r3, [r2]
    ADD r3, r3, #32
    CMP r3, r1
    BLT Invalidate_RangeL2
    DSB

    MOV r3, r0
    BIC r3, r3, #31
Invalidate_RangeL1
    MCR p15,0, r3, c7, c6, 1
    ADD r3, r3, #32
    CMP r3, r1
    BLT Invalidate_RangeL1
    DSB
    BX LR

    ENDFUNC


;********************************************************************************************************
;                                       FLUSH DATA CACHE RANGE
;
; Description : Flush (clean) a range of data cache by MVA.
;
; Prototypes  : void  BSP_DCache_FlushRange  (void       *p_mem,
;                                             CPU_SIZE_T  range);
;
; Argument(s) : p_mem    Start address of the region to flush.
;
;               range    Size of the region to invalidate in bytes.
;
; Note(s)     : (1) p_mem value not aligned to 32 bytes will be truncated to the next lowest aligned
;                   address.
;
;               (2) range value not a multiple of 32 will be the next multiple of 32 that includes
;                   the start address and the end of the specified range.
;********************************************************************************************************

    EXPORT BSP_DCache_FlushRange

BSP_DCache_FlushRange FUNCTION
    DSB
    MOV r3, r0
    ADD r1, r1, r0
    BIC r3, r3, #31

Flush_RangeL1
    MCR p15, 0, r3, c7, c14, 1
    ADD r3, r3, #32
    CMP r3, r1
    BLT Flush_RangeL1
    DSB

    MOV r3, r0
    BIC r3, r3, #31
    MOV32  r2, #CPU_ARM_L2C_REG7_CACHE_CLEAN_PA
Flush_RangeL2
    STR r3, [r2]
    ADD r3, r3, #32
    CMP r3, r1
    BLT Flush_RangeL2
    DSB

    BX LR

    ENDFUNC


    END

