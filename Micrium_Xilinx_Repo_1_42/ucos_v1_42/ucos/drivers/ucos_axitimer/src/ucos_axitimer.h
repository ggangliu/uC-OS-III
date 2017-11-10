/*
*********************************************************************************************************
*
*                                    MICRIUM BOARD SUPPORT PACKAGE
*
*                         (c) Copyright 2014-2015; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*
*               This BSP is provided in source form to registered licensees ONLY.  It is
*               illegal to distribute this source code to any third party unless you receive
*               written permission by an authorized Micrium representative.  Knowledge of
*               the source code may NOT be used to develop a similar product.
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
*                                    MICRIUM BOARD SUPPORT PACKAGE
*                                              AXI TIMER
*
* Filename      : ucos_axitimer.h
* Version       : V1.42
* Programmer(s) : JBL
*********************************************************************************************************
*/

#ifndef  UCOS_AXITIMER_PRESENT
#define  UCOS_AXITIMER_PRESENT


/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#include  <lib_def.h>
#include  <cpu.h>

#include  <ucos_bsp.h>


/*
*********************************************************************************************************
*                                        REGISTER DEFINITIONS
*********************************************************************************************************
*/

typedef struct axitimer {
    CPU_REG32 TCSR0;                                            /* Timer 0 Control and Status Register                  */
    CPU_REG32 TLR0;                                             /* Timer 0 Load Register                                */
    CPU_REG32 TCR0;                                             /* Timer 0 Counter Register                             */
    CPU_REG32 RESERVED1[1];                                     /* Reserved                                             */
    CPU_REG32 TCSR1;                                            /* Timer 1 Control and Status Register                  */
    CPU_REG32 TLR1;                                             /* Timer 1 Load Register                                */
    CPU_REG32 TCR1;                                             /* timer 1 Counter Register                             */
    CPU_REG32 RESERVED2[1];                                     /* Reserved                                             */
} AXITIMER, *AXITIMER_PTR;


#define AXITIMER_BIT_TCSR_MDT   DEF_BIT_00
#define AXITIMER_BIT_TCSR_UDT   DEF_BIT_01
#define AXITIMER_BIT_TCSR_GENT  DEF_BIT_02
#define AXITIMER_BIT_TCSR_CAPT  DEF_BIT_03
#define AXITIMER_BIT_TCSR_ARHT  DEF_BIT_04
#define AXITIMER_BIT_TCSR_LOAD  DEF_BIT_05
#define AXITIMER_BIT_TCSR_ENIT  DEF_BIT_06
#define AXITIMER_BIT_TCSR_ENT   DEF_BIT_07
#define AXITIMER_BIT_TCSR_TINT  DEF_BIT_08
#define AXITIMER_BIT_TCSR_PWMA  DEF_BIT_09
#define AXITIMER_BIT_TCSR_ENALL DEF_BIT_10
#define AXITIMER_BIT_TCSR_CASC  DEF_BIT_11


#define AXITIMER_OPT_MODE           DEF_BIT_00
#define AXITIMER_OPT_DOWN           DEF_BIT_01
#define AXITIMER_OPT_GEN            DEF_BIT_02
#define AXITIMER_OPT_CAPTURE        DEF_BIT_03
#define AXITIMER_OPT_AUTO_RELOAD    DEF_BIT_04
#define AXITIMER_OPT_INT            DEF_BIT_06
#define AXITIMER_OPT_PWM            DEF_BIT_09
#define AXITIMER_OPT_CASC           DEF_BIT_11
#define AXITIMER_OPT_MASK           0xA5F


/*
*********************************************************************************************************
*                                        STRUCTURE DEFINITIONS
*********************************************************************************************************
*/

typedef struct {
    CPU_INT32U DeviceId;
    CPU_INT32U BaseAddress;
    CPU_INT32U TmrFreq;
    CPU_INT32U IntSource;
} UCOS_AXITIMER_Config;

typedef struct ucos_axitimer {
    CPU_INT32U   DeviceId;
    AXITIMER_PTR AXITimer;
    CPU_INT32U   TmrFreq;
    void (*Tmr0Callback)(struct ucos_axitimer *handle, CPU_INT32U tmr_nbr);
    void (*Tmr1Callback)(struct ucos_axitimer *handle, CPU_INT32U tmr_nbr);
} UCOS_AXITIMER;

typedef UCOS_AXITIMER *AXITIMER_HANDLE;

typedef void (*AXITIMER_CALLBACK_FNCT_PTR)(AXITIMER_HANDLE handle, CPU_INT32U tmr_nbr);


/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

AXITIMER_HANDLE AXITimer_Init (CPU_INT32U      device_id);

CPU_BOOLEAN AXITimer_Start (AXITIMER_HANDLE handle,
                            CPU_INT32U      tmr_nbr);

CPU_BOOLEAN AXITimer_Stop (AXITIMER_HANDLE handle,
                           CPU_INT32U      tmr_nbr);

CPU_BOOLEAN AXITimer_OptSet (AXITIMER_HANDLE handle,
                             CPU_INT32U      tmr_nbr,
                             CPU_INT32U      opt);

CPU_BOOLEAN AXITimer_OptClr (AXITIMER_HANDLE handle,
                             CPU_INT32U      tmr_nbr,
                             CPU_INT32U      opt);

CPU_BOOLEAN AXITimer_IntClr (AXITIMER_HANDLE handle,
                             CPU_INT32U      tmr_nbr);

CPU_BOOLEAN AXITimer_LoadSet (AXITIMER_HANDLE handle,
                              CPU_INT32U      tmr_nbr,
                              CPU_INT32U      cnt_load_val);

CPU_INT32U AXITimer_FreqGet (AXITIMER_HANDLE handle);

CPU_BOOLEAN AXITimer_CallbackSet (AXITIMER_HANDLE            handle,
                                  CPU_INT32U                 tmr_nbr,
                                  AXITIMER_CALLBACK_FNCT_PTR call_back);

void AXITimer_IntHandler (void       *p_int_arg,
                          CPU_INT32U  cpu_id);

#endif /* UCOS_AXITIMER_PRESENT */
