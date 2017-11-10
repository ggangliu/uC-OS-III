/*
*********************************************************************************************************
*
*                                    MICRIUM BOARD SUPPORT PACKAGE
*
*                          (c) Copyright 2003-2013; Micrium, Inc.; Weston, FL
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
*                                       SERIAL (UART) INTERFACE
*                         Cadence Universal Asynchronous Receiver Transmitter
*                                               on the
*                                ZYNQ-7000 EPP & ZC702 Evaluation Kit
*
* Filename      : bsp_ser.h
* Version       : V1.00
* Programmer(s) : JBL
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               MODULE
*
* Note(s) : (1) This BSP serial header file is protected from multiple pre-processor inclusion through
*               use of the BSP serial present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef  BSP_SER_PRESENT                                        /* See Note #1.                                         */
#define  BSP_SER_PRESENT


/*
*********************************************************************************************************
*                                               DEFINES
*********************************************************************************************************
*/

#define  BSP_SER_PRINTF_STR_BUF_SIZE             1024u          /* Maximum string length.                               */


/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

void        BSP_Ser_Init        (void);

CPU_INT08U  BSP_Ser_RdByte      (void);

void        BSP_Ser_RdStr       (CPU_CHAR    *p_str,
                                 CPU_INT16U   len);

void        BSP_Ser_WrByte      (CPU_INT08U   c);

void        BSP_Ser_WrStr       (CPU_CHAR    *p_str);

void        BSP_Ser_Printf      (CPU_CHAR    *format,
                                 ...);

void        BSP_Ser_ISR_Handler (CPU_INT32U cpu_id);


#endif /* BSP_SER_PRESENT */
