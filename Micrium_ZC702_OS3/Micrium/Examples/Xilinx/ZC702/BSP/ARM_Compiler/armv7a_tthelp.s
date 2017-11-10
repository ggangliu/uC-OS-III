;
;********************************************************************************************************
;                                        MMU UTILITY FUNCTIONS
;
; File      : armv7a_tthelp.s
; For       : Cortex A
; Toolchain : ARMCC
;
; Notes : none.
;********************************************************************************************************
;

;********************************************************************************************************
;                                           MACROS AND DEFINIITIONS
;********************************************************************************************************


    PRESERVE8

    AREA  armv7a_tthelp,CODE,READONLY

    ENTRY


;********************************************************************************************************
;                                       ARMv7Attbl_SuperSecMap
;
; Description : Map a section of memory using 16MiB supersections.
;
; Prototypes  : void  ARMv7Attbl_Map_SuperSec  (void       *ttbl_base,
;                                               CPU_INT32U  template,
;                                               CPU_DATA   *start,
;                                               CPU_DATA    range);
;
; Argument(s) : *ttbl_base    Start address of the mmu translation table.
;
;                template     Template of the supersection mapping.
;
;               *start        Start address of the region to map.
;
;                range        Size of the region to map.
;
; Note(s)     : None.
;********************************************************************************************************

    EXPORT ARMv7Attbl_SuperSecMap

ARMv7Attbl_SuperSecMap FUNCTION
    LSR     r12, r2, #18 ; Calculate start position in the page table
    ADD     r0, r0, r12  ; r0 = TTLB_BASE + Start
    ADD     r3, r3, r2   ; r3 = Start + Range

ARMv7Attbl_Map_SuperSec_Loop1
    MOV     r12, #0xFF000000
    BIC     r1, r1, r12 ; Clear upper byte for the PA
    ADD     r1, r1, r2 ; r1 = TTB_TEMPLATE + Addr
    MOV     r12, #16
ARMv7Attbl_Map_SuperSec_Loop2 ; Store 16 copies of the table entry
    STR     r1, [r0], #4
    SUBS    r12, r12, #1
    BNE     ARMv7Attbl_Map_SuperSec_Loop2
    ADD     r2, r2, #0x1000000 ; Move forward 16 MiB
    CMP     r2, r3
    BNE     ARMv7Attbl_Map_SuperSec_Loop1

    BX      lr

    ENDFUNC




;********************************************************************************************************
;                                       ARMv7Attbl_SuperSecMapAt
;
; Description : Map a single section of memory using 16MiB supersections at a specific location.
;
; Prototypes  : void  ARMv7Attbl_Map_SuperSec  (void       *ttbl_base,
;                                               CPU_INT32U  template,
;                                               CPU_DATA   *virt,
;                                               CPU_DATA   *phys;
;
; Argument(s) : *ttbl_base    Start address of the mmu translation table.
;
;                template     Template of the supersection mapping.
;
;                *virt        Start address (Virtual) of the region to map.
;
;                *phys        Start address (Physical) of the region to map.
;
; Note(s)     : None.
;********************************************************************************************************
    EXPORT ARMv7Attbl_SuperSecMapAt

ARMv7Attbl_SuperSecMapAt FUNCTION
    LSR     r12, r2, #18 ; Calculate start position in the page table
    ADD     r0, r0, r12  ; r0 = TTLB_BASE + Start

    MOV     r12, #0xFF000000
    BIC     r1, r1, r12 ; Clear upper byte for the PA
    ADD     r1, r1, r3 ; r1 = TTB_TEMPLATE + Addr
    MOV     r12, #16
ARMv7Attbl_Map_SuperSecAt_Loop ; Store 16 copies of the table entry
    STR     r1, [r0], #4
    SUBS    r12, r12, #1
    BNE     ARMv7Attbl_Map_SuperSecAt_Loop

    BX      lr

    ENDFUNC


    END
