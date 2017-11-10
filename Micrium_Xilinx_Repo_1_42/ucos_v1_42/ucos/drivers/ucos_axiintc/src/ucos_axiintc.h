/*
*********************************************************************************************************
*
*                                    MICRIUM BOARD SUPPORT PACKAGE
*
*                          (c) Copyright 2014-2015; Micrium, Inc.; Weston, FL
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
*                                      AXI INTERRUPT CONTROLLER
*
* Filename      : ucos_axiintc.h
* Version       : V1.42
* Programmer(s) : JBL
*********************************************************************************************************
*/

#ifndef  UCOS_AXIINTC_PRESENT
#define  UCOS_AXIINTC_PRESENT


/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#include  <lib_def.h>
#include  <cpu.h>


/*
*********************************************************************************************************
*                                        REGISTER DEFINITIONS
*********************************************************************************************************
*/

typedef struct axiintc {
    CPU_REG32  ISR;                                             /* Interrupt Status Register                            */
    CPU_REG32  IPR;                                             /* Interrupt Pending Register                           */
    CPU_REG32  IER;                                             /* Interrupt Enable Register                            */
    CPU_REG32  IAR;                                             /* Interrupt Acknowledge Register                       */
    CPU_REG32  SIE;                                             /* Set Interrupt Enable                                 */
    CPU_REG32  CIE;                                             /* Cleare Interrupt Enabled                             */
    CPU_REG32  IVR;                                             /* Interrupt Vector Register                            */
    CPU_REG32  MER;                                             /* Master Enable Register                               */
    CPU_REG32  IMR;                                             /* Interrupt Mode Register                              */
    CPU_REG32  ILR;                                             /* Interrupt Level Register                             */
} AXIINTC, *AXIINTC_PTR;


#define  AXIINTC_BIT_MER_ME  DEF_BIT_00                         /* Master IRQ Enable                                    */
#define  AXIINTC_BIT_MER_HIE DEF_BIT_01                         /* Hardware Interrupt Enable                            */


/*
*********************************************************************************************************
*                                        STRUCTURE DEFINITIONS
*********************************************************************************************************
*/

typedef struct {
    CPU_INT32U DeviceId;
    CPU_INT32U BaseAddress;
    CPU_INT32U IntrKind;
    CPU_INT32U HasFast;
    CPU_INT32U IVARReset;
    CPU_INT32U IntCnt;
    CPU_INT32U IntType;
} UCOS_AXIINTC_Config;

typedef struct {
    CPU_INT32U    DeviceId;
    AXIINTC_PTR   AXIIntC;
} UCOS_AXIINTC;

typedef UCOS_AXIINTC *AXIINTC_HANDLE;


/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

AXIINTC_HANDLE  AXIIntCInit     (CPU_INT32U     DeviceId);

CPU_BOOLEAN     AXIIntCIntEnSet (AXIINTC_HANDLE Handle,
                                 CPU_INT32U     Int);

CPU_BOOLEAN     AXIIntCIntEnClr (AXIINTC_HANDLE Handle,
                                 CPU_INT32U     Int);

#endif /* UCOS_AXIINTC_PRESENT */
