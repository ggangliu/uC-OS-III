/*
*********************************************************************************************************
*
*                                    MICRIUM BOARD SUPPORT PACKAGE
*
*                          (c) Copyright 2003-2015; Micrium, Inc.; Weston, FL
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
*                                CORTEX A GENERIC INTERRUPT CONTROLLER
*
* Filename      : bsp_int.h
* Version       : V1.42
* Programmer(s) : JBL
*********************************************************************************************************
*/

#ifndef  UCOS_SCUGIC_PRESENT
#define  UCOS_SCUGIC_PRESENT

#include  <ucos_bsp.h>
#include  <xparameters.h>

/*
*********************************************************************************************************
*                                               DEFINES
*********************************************************************************************************
*/

#if (UCOS_CPU_TYPE == UCOS_CPU_TYPE_PS7)
#define  SCUGIC_DIST_REG         ((SCUGIC_DIST_PTR)(XPAR_PS7_SCUGIC_0_DIST_BASEADDR))
#define  SCUGIC_IF_REG           ((SCUGIC_IF_PTR)(XPAR_PS7_SCUGIC_0_BASEADDR))
#define  SCUGIC_INT_SRC_CNT         94u
#elif (UCOS_CPU_TYPE == UCOS_CPU_TYPE_PSUA53)
#if (UCOS_XEN_GUEST == DEF_ENABLED)
#define  SCUGIC_DIST_REG         ((SCUGIC_DIST_PTR)(0x03001000u))
#define  SCUGIC_IF_REG           ((SCUGIC_IF_PTR)(0x03002000u))
#else
#define  SCUGIC_DIST_REG         ((SCUGIC_DIST_PTR)(XPAR_PSU_ACPU_GIC_DIST_BASEADDR))
#define  SCUGIC_IF_REG           ((SCUGIC_IF_PTR)(XPAR_PSU_ACPU_GIC_BASEADDR))
#endif
#define  SCUGIC_INT_SRC_CNT        164u
#else
#define  SCUGIC_DIST_REG         ((SCUGIC_DIST_PTR)(0xF9000000u))
#define  SCUGIC_IF_REG           ((SCUGIC_IF_PTR)(0xF9001000u))
#define  SCUGIC_INT_SRC_CNT        164u
#endif


/*
*********************************************************************************************************
*                                        REGISTER DEFINITIONS
*********************************************************************************************************
*/


                                                                /* ------------ GIC DISTRIBUTOR INTERFACE ------------- */
typedef  struct  scugic_dist {
    CPU_REG32  ICDDCR;                                          /* Distributor Control Register.                        */
    CPU_REG32  ICDICTR;                                         /* Interrupt Controller Type Register.                  */
    CPU_REG32  ICDIIDR;                                         /* Distributor Implementer Identification Register.     */
    CPU_REG32  RSVD1[29];                                       /* Reserved.                                            */
    CPU_REG32  ICDISRn[32];                                     /* Interrupt Security Registers.                        */
    CPU_REG32  ICDISERn[32];                                    /* Interrupt Set-Enable Registers.                      */
    CPU_REG32  ICDICERn[32];                                    /* Interrupt Clear-Enable Registers.                    */
    CPU_REG32  ICDISPRn[32];                                    /* Interrupt Set-Pending Registers.                     */
    CPU_REG32  ICDICPRn[32];                                    /* Interrupt Clear-Pending Registers.                   */
    CPU_REG32  ICDABRn[32];                                     /* Active Bit Registers.                                */
    CPU_REG32  RSVD2[32];                                       /* Reserved.                                            */
    CPU_REG32  ICDIPRn[255];                                    /* Interrupt Priority Registers.                        */
    CPU_REG32  RSVD3[1];                                        /* Reserved.                                            */
    CPU_REG32  ICDIPTRn[255];                                   /* Interrupt Processor Target Registers.                */
    CPU_REG32  RSVD4[1];                                        /* Reserved.                                            */
    CPU_REG32  ICDICFRn[64];                                    /* Interrupt Configuration Registers.                   */
    CPU_REG32  RSVD5[128];                                      /* Reserved.                                            */
    CPU_REG32  ICDSGIR;                                         /* Software Generate Interrupt Register.                */
    CPU_REG32  RSVD6[51];                                       /* Reserved.                                            */
} SCUGIC_DIST, *SCUGIC_DIST_PTR;


                                                                /* ---------------- GIC CPU INTERFACE ----------------- */
typedef  struct  scugic_if {
    CPU_REG32  ICCICR;                                          /* CPU Interface Control Register.                      */
    CPU_REG32  ICCPMR;                                          /* Interrupt Priority Mask Register.                    */
    CPU_REG32  ICCBPR;                                          /* Binary Point Register.                               */
    CPU_REG32  ICCIAR;                                          /* Interrupt Acknowledge Register.                      */
    CPU_REG32  ICCEOIR;                                         /* End Interrupt Register.                              */
    CPU_REG32  ICCRPR;                                          /* Running Priority Register.                           */
    CPU_REG32  ICCHPIR;                                         /* Highest Pending Interrupt Register.                  */
    CPU_REG32  ICCABPR;                                         /* Aliased Binary Point Register.                       */
    CPU_REG32  RSVD[55];                                        /* Reserved.                                            */
    CPU_REG32  ICCIIDR;                                         /* CPU Interface Identification Register.               */
} SCUFIC_IF, *SCUGIC_IF_PTR;


                                                                /* ----------- DISTRIBUTOR CONTROL REGISTER ----------- */
#define  SCUGIC_DIST_ICDDCR_EN            DEF_BIT_00            /* Global GIC enable.                                   */



                                                                /* ---------- CPU INTERFACE CONTROL REGISTER ---------- */
#define  SCUGIC_IF_ICCICR_ENS             DEF_BIT_00            /* Enable secure interrupts.                            */
#define  SCUGIC_IF_ICCICR_ENNS            DEF_BIT_01            /* Enable non-secure interrupts.                        */
#define  SCUGIC_IF_ICCICR_ACKCTL          DEF_BIT_02            /* Secure ack of NS interrupts.                         */


/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

void        SCUGIC_Init        (void);

void        SCUGIC_SrcEn       (CPU_INT32U        int_id);

void        SCUGIC_SrcDis      (CPU_INT32U        int_id);

void        SCUGIC_PrioMaskSet (CPU_INT32U        prio);

void        SCUGIC_PrioSet     (CPU_INT32U        int_id,
                                CPU_INT32U        prio);

void        SCUGIC_TargetSet   (CPU_INT32U        int_id,
                                CPU_INT08U        int_target_list);

void        SCUGIC_TypeSet     (CPU_INT32U        int_id,
                                CPU_BOOLEAN       type);

void        SCUGIC_Handler     (void);

void        SCUGIC_SGITrig     (CPU_INT32U        int_sgi,
                                CPU_INT32U        int_target_list);


#endif /* UCOS_SCUGIC_PRESENT */
