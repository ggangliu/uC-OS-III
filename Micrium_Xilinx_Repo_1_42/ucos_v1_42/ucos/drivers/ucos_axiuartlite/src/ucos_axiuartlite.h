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
*                                             AXI UARTLITE
*
* Filename      : ucos_axiuartlite.h
* Version       : V1.42
* Programmer(s) : JBL
*********************************************************************************************************
*/

#ifndef  UCOS_AXIUARTLITE_PRESENT
#define  UCOS_AXIUARTLITE_PRESENT


/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#include <lib_def.h>
#include <cpu.h>
#include <KAL/kal.h>


/*
*********************************************************************************************************
*                                        REGISTER DEFINITIONS
*********************************************************************************************************
*/

typedef struct axi_uartlite {
    CPU_REG32  RX;                                             /* RX FIFO                                               */
    CPU_REG32  TX;                                             /* TX FIFO                                               */
    CPU_REG32  STAT;                                           /* Status Register                                       */
    CPU_REG32  CTRL;                                           /* Control Register                                      */

} AXIUARTLITE, *AXIUARTLITE_PTR;


/* ------- UART CONTROL REGISTER BIT DEFINITION ------- */
#define  AXIUARTLITE_BIT_CTRL_TXRST  (DEF_BIT_00)              /* Reset TX FIFO                                         */
#define  AXIUARTLITE_BIT_CTRL_RXRST  (DEF_BIT_01)              /* Reset RX FIFO                                         */
#define  AXIUARTLITE_BIT_CTRL_INTEN  (DEF_BIT_04)              /* Enable Interrupts                                     */


/* ------- UART STATUS REGISTER BIT DEFINITION ------- */
#define  AXIUARTLITE_BIT_STAT_RXVALID   (DEF_BIT_00)           /* RX Valid                                              */
#define  AXIUARTLITE_BIT_STAT_RXFULL    (DEF_BIT_01)           /* RX FIFO Full                                          */
#define  AXIUARTLITE_BIT_STAT_TXEMPTY   (DEF_BIT_02)           /* TX FIFO Empty                                         */
#define  AXIUARTLITE_BIT_STAT_TXFULL    (DEF_BIT_03)           /* TX FIFO Full                                          */
#define  AXIUARTLITE_BIT_STAT_INTREN    (DEF_BIT_04)           /* Interrupts Enabled                                    */
#define  AXIUARTLITE_BIT_STAT_OVRUN     (DEF_BIT_05)           /* RX Overrun error                                      */
#define  AXIUARTLITE_BIT_STAT_FRAMEERR  (DEF_BIT_06)           /* RX Frame Error                                        */
#define  AXIUARTLITE_BIT_STAT_PARITYERR (DEF_BIT_07)           /* RX Parity Error                                       */

/*
*********************************************************************************************************
*                                        STRUCTURE DEFINITIONS
*********************************************************************************************************
*/


typedef struct {
    CPU_INT32U  DeviceId;
    CPU_INT32U  BaseAddress;
    CPU_INT32U  BaudRate;
    CPU_BOOLEAN UseParity;
    CPU_BOOLEAN OddParity;
    CPU_INT32U  DataBits;
    CPU_INT32U  IntSource;
} UCOS_AXIUARTLITE_Config;


typedef struct {
    CPU_INT32U      DeviceId;
    AXIUARTLITE_PTR UARTLite;
    CPU_INT32U      BaudRate;
    CPU_BOOLEAN     UseParity;
    CPU_BOOLEAN     OddParity;
    CPU_INT32U      DataBits;
    CPU_INT32U      IntReq;
    KAL_SEM_HANDLE  TxSem;
    KAL_SEM_HANDLE  RxSem;
    KAL_LOCK_HANDLE TxMutex;
    KAL_LOCK_HANDLE RxMutex;
    CPU_INT32U  IntSource;
} UCOS_AXIUARTLITE;

#define  AXIUARTLITE_INT_RX_REQ DEF_BIT_00
#define  AXIUARTLITE_INT_TX_REQ DEF_BIT_01

typedef UCOS_AXIUARTLITE *AXIUARTLITE_HANDLE;


/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

AXIUARTLITE_HANDLE AXIUARTLite_Init (CPU_INT32U device_id);

CPU_BOOLEAN AXIUARTLite_WrStr (AXIUARTLITE_HANDLE   handle,
                               const CPU_CHAR *p_str);

CPU_CHAR AXIUARTLite_RdByte (AXIUARTLITE_HANDLE handle);

void AXIUARTLite_IntHandler (void       *p_int_arg,
                             CPU_INT32U  cpu_id);

#endif /* UCOS_AXIUARTLITE_PRESENT */
