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
*                                     L2C310 L2 CACHE CONTROLLER
*
* Filename      : ucos_l2cachec.h
* Version       : V1.42
* Programmer(s) : JBL
*********************************************************************************************************
*/

#ifndef  UCOS_L2CACHEC_PRESENT
#define  UCOS_L2CACHEC_PRESENT


/*
*********************************************************************************************************
*                                               DEFINES
*********************************************************************************************************
*/

#define  L2CACHEC_REG            ((L2CACHEC_PTR)(XPAR_PS7_L2CACHEC_0_BASEADDR))

/*
*********************************************************************************************************
*                                        REGISTER DEFINITIONS
*********************************************************************************************************
*/


                                                                /* ---------------- L2C310 REGISTERS ------------------ */
typedef  struct  l2cachec {
    CPU_REG32  REG0_ID;                                         /* Cache ID Register.                                   */
    CPU_REG32  REG0_TYPE;                                       /* Cache Type Register.                                 */
    CPU_REG32  RESERVED1[0x3E];                                 /* Reserved.                                            */
    CPU_REG32  REG1_CTRL;                                       /* Cache Control Register.                              */
    CPU_REG32  REG1_AUX_CTRL;                                   /* Cache Auxiliary Control Register.                    */
    CPU_REG32  REG1_TAG_RAM_CTRL;                               /* Tag RAM Control.                                     */
    CPU_REG32  REG1_DATA_RAM_CTRL;                              /* Data RAM Control.                                    */
    CPU_REG32  RESERVED2[0x3C];                                 /* Reserved.                                            */
    CPU_REG32  REG2_EVCNT_CTRL;                                 /* Event Counter Control Register.                      */
    CPU_REG32  REG2_EVCNT1_CFG;                                 /* Event Counter 1 Configuration Register.              */
    CPU_REG32  REG2_EVCNT0_CFG;                                 /* Event Counter 0 Configuration Register.              */
    CPU_REG32  REG2_EVCNT1;                                     /* Event Counter 1 Register.                            */
    CPU_REG32  REG2_EVCNT0;                                     /* Event Counter 0 Register.                            */
    CPU_REG32  REG2_INT_MASK;                                   /* Interrupt Mask Register.                             */
    CPU_REG32  REG2_INT_MASKED_STATUS;                          /* Masked Interrupt Status Register.                    */
    CPU_REG32  REG2_INT_RAW_STATUS;                             /* Raw Interrupt Status Register.                       */
    CPU_REG32  REG2_INT_CLR;                                    /* Interrupt Clear Register.                            */
    CPU_REG32  RESERVED3[0x143];                                /* Reserved.                                            */
    CPU_REG32  REG7_CACHE_SYNC;                                 /* Cache SYNC.                                          */
    CPU_REG32  RESERVED4[0xF];                                  /* Reserved.                                            */
    CPU_REG32  REG7_INV_PA;                                     /* Invalidate PA.                                       */
    CPU_REG32  REG7_INV_WAY;                                    /* Invalidate Way.                                      */
    CPU_REG32  RESERVED5[0xE];                                  /* Reserved.                                            */
    CPU_REG32  REG7_CLEAN_PA;                                   /* Clean PA.                                            */
    CPU_REG32  REG7_CLEAN_INDEX;                                /* Clean Index.                                         */
    CPU_REG32  REG7_CLEAN_WAY;                                  /* Clean Way.                                           */
    CPU_REG32  RESERVED6[0xD];                                  /* Reserved.                                            */
    CPU_REG32  REG7_CLEAN_INV_PA;                               /* Clean Invalidate PA.                                 */
    CPU_REG32  REG7_CLEAN_INV_INDEX;                            /* Clean Invalidate Index.                              */
    CPU_REG32  REG7_CLEAN_INV_WAY;                              /* Clean Invalidate Way.                                */
    CPU_REG32  RESERVED7[0x41];                                 /* Reserved.                                            */
    CPU_REG32  REG7_D_LOCKDOWN0;                                /* Data Lockdown X.                                     */
    CPU_REG32  REG7_I_LOCKDOWN0;                                /* Instruction Lockdown X.                              */
    CPU_REG32  REG7_D_LOCKDOWN1;                                /* Data Lockdown X.                                     */
    CPU_REG32  REG7_I_LOCKDOWN1;                                /* Instruction Lockdown X.                              */
    CPU_REG32  REG7_D_LOCKDOWN2;                                /* Data Lockdown X.                                     */
    CPU_REG32  REG7_I_LOCKDOWN2;                                /* Instruction Lockdown X.                              */
    CPU_REG32  REG7_D_LOCKDOWN3;                                /* Data Lockdown X.                                     */
    CPU_REG32  REG7_I_LOCKDOWN3;                                /* Instruction Lockdown X.                              */
    CPU_REG32  REG7_D_LOCKDOWN4;                                /* Data Lockdown X.                                     */
    CPU_REG32  REG7_I_LOCKDOWN4;                                /* Instruction Lockdown X.                              */
    CPU_REG32  REG7_D_LOCKDOWN5;                                /* Data Lockdown X.                                     */
    CPU_REG32  REG7_I_LOCKDOWN5;                                /* Instruction Lockdown X.                              */
    CPU_REG32  REG7_D_LOCKDOWN6;                                /* Data Lockdown X.                                     */
    CPU_REG32  REG7_I_LOCKDOWN6;                                /* Instruction Lockdown X.                              */
    CPU_REG32  REG7_D_LOCKDOWN7;                                /* Data Lockdown X.                                     */
    CPU_REG32  REG7_I_LOCKDOWN7;                                /* Instruction Lockdown X.                              */
    CPU_REG32  RESERVED8[0x4];                                  /* Reserved.                                            */
    CPU_REG32  REG9_LOCK_LINE_EN;                               /* Lockdown by Line Enable Register.                    */
    CPU_REG32  REG9_UNLOCK_WAY;                                 /* Cache Lockdown by Way.                               */
    CPU_REG32  RESERVED9[0xAA];                                 /* Reserved.                                            */
    CPU_REG32  REG12_ADDR_FILTER_START;                         /* Address filtering start.                             */
    CPU_REG32  REG12_ADDR_FILTER_END;                           /* Address filtering end.                               */
    CPU_REG32  RESERVED10[0xCE];                                /* Reserved.                                            */
    CPU_REG32  REG15_DEBUG_CTRL;                                /* Debug Control Register.                              */
    CPU_REG32  RESERVED11[0x7];                                 /* Reserved.                                            */
    CPU_REG32  REG15_PREFETCH_CTRL;                             /* Prefetch Control Register.                           */
    CPU_REG32  RESERVED12[0x7];                                 /* Reserved.                                            */
    CPU_REG32  REG15_POWER_CTRL;                                /* Power Control Register.                              */
} L2CACHEC, *L2CACHEC_PTR;


                                                                /* -------------- CACHE CONTROL REGISTER -------------- */
#define  L2CACHEC_BIT_CTRL_EN            DEF_BIT_00             /* L2 Cache Enable.                                     */

                                                                /* -------- AUXILLIARY CACHE CONTROL REGISTER --------- */
#define  L2CACHEC_BIT_AUX_CTRL_FLZ       DEF_BIT_00             /* Full Line of Zero Enable.                            */
#define  L2CACHEC_BIT_AUX_CTRL_HPSODEV   DEF_BIT_10             /* High priority SO and Dev Enable.                     */
#define  L2CACHEC_BIT_AUX_CTRL_STB_DEV_LIMIT DEF_BIT_11         /* Store Buffer Device Limitation.                      */
#define  L2CACHEC_BIT_AUX_CTRL_PARITY    DEF_BIT_21             /* Parity Enable.                                       */
#define  L2CACHEC_BIT_AUX_CTRL_DPREFETCH DEF_BIT_28             /* Data Prefetch Enable.                                */
#define  L2CACHEC_BIT_AUX_CTRL_IPREFETCH DEF_BIT_29             /* Instruction Prefetch Enable.                         */
#define  L2CACHEC_BIT_AUX_CTRL_EBRESP    DEF_BIT_30             /* Early BRESP Enable.                                  */

/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/


void L2CacheC_En (void);

void L2CacheC_AuxCtrlSet (CPU_INT32U aux_val);

void L2CacheC_PrefetchCtrlSet (CPU_INT32U prefetch_val);

void L2CacheC_TagRamLatencySet (CPU_INT32U setup_latency,
                                CPU_INT32U read_latency,
                                CPU_INT32U write_latency);

void L2CacheC_DataRamLatencySet (CPU_INT32U setup_latency,
                                 CPU_INT32U read_latency,
                                 CPU_INT32U write_latency);

#endif /* UCOS_L2CACHEC_PRESENT */
