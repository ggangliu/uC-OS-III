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
* Filename      : bsp_ser.c
* Version       : V1.00
* Programmer(s) : JBL
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#include  <stdint.h>
#include  <string.h>
#include  <stdarg.h>
#include  <stdio.h>

#include  <cpu.h>
#include  <lib_def.h>

#include  <bsp.h>
#include  <bsp_os.h>
#include  <bsp_ser.h>
#include  <bsp_int.h>


/*
*********************************************************************************************************
*                                             LOCAL DEFINES
*********************************************************************************************************
*/

#define  BSP_UART1_REG         ((ZYNQ_REG_UART_PTR)(0xE0001000u))


typedef  struct  zynq_reg_uart {
    CPU_REG32  CTRL;                                            /* UART Control Register                                */
    CPU_REG32  MODE;                                            /* UART Mode Register                                   */
    CPU_REG32  INTR_EN;                                         /* Interrupt Enable Register                            */
    CPU_REG32  INTR_DIS;                                        /* Interrupt Disable Register                           */
    CPU_REG32  INTR_MASK;                                       /* Interrupt Mask Register                              */
    CPU_REG32  INTR_STAT;                                       /* Channel Interrupt Status Register                    */
    CPU_REG32  BAUD;                                            /* Baud Rate Generator Register                         */
    CPU_REG32  RX_TIMEOUT;                                      /* Receiver Timeout Register                            */
    CPU_REG32  RX_FIFO_LVL;                                     /* Receiver FIFO Trigger Level Register                 */
    CPU_REG32  MODEM_CTRL;                                      /* Modem Control Register                               */
    CPU_REG32  MODEM_STAT;                                      /* Modem Status Register                                */
    CPU_REG32  CHAN_STAT;                                       /* Channel Status Register                              */
    CPU_REG32  TX_RX_FIFO;                                      /* Transmit an Receive FIFO                             */
    CPU_REG32  BAUD_DIV;                                        /* Baud Rate Divider Register                           */
    CPU_REG32  FLOW_DLY;                                        /* Flow Control Delay Register                          */
    CPU_REG32  TX_FIFO_LVL;                                     /* Transmit FIFO Trigger Level Register                 */
} ZYNQ_REG_UART, *ZYNQ_REG_UART_PTR;


                                                                /* ------- UART CONTROL REGISTER BIT DEFINITION ------- */
#define  ZYNQ_BIT_UART_CTRL_STPBRK  (DEF_BIT_08)                /* Stop transmitter break.                              */
#define  ZYNQ_BIT_UART_CTRL_STTBRK  (DEF_BIT_07)                /* Start transmitter break.                             */
#define  ZYNQ_BIT_UART_CTRL_RSTTO   (DEF_BIT_06)                /* Restart receiver timeout counter.                    */
#define  ZYNQ_BIT_UART_CTRL_TXDIS   (DEF_BIT_05)                /* Transmit disable.                                    */
#define  ZYNQ_BIT_UART_CTRL_TXEN    (DEF_BIT_04)                /* Transmit enable.                                     */
#define  ZYNQ_BIT_UART_CTRL_RXDIS   (DEF_BIT_03)                /* Receive disable.                                     */
#define  ZYNQ_BIT_UART_CTRL_RXEN    (DEF_BIT_02)                /* Receive enable.                                      */
#define  ZYNQ_BIT_UART_CTRL_TXRES   (DEF_BIT_01)                /* TX software reset.                                   */
#define  ZYNQ_BIT_UART_CTRL_RXRES   (DEF_BIT_00)                /* RX software reset.                                   */


                                                                /* -------- UART MODE REGISTER BIT DEFINITION --------- */
#define  ZYNQ_BIT_UART_MODE_CHMODE_MSK  (DEF_BIT_FIELD(8, 2))   /* Channel mode.                                        */
#define  ZYNQ_BIT_UART_MODE_CHMODE(mode) (DEF_BIT_MASK(mode, 2) & ZYNQ_BIT_UART_MODE_CHMODE_MSK)
#define  ZYNQ_BIT_UART_MODE_NBSTOP_MSK  (DEF_BIT_FIELD(6, 2))   /* Number of stop bits.                                 */
#define  ZYNQ_BIT_UART_MODE_NBSTOP(nbr) (DEF_BIT_MASK(nbr, 2) & ZYNQ_BIT_UART_MODE_NBSTOP_MSK)
#define  ZYNQ_BIT_UART_MODE_PAR_MSK     (DEF_BIT_FIELD(3, 3))   /* Parity type select.                                  */
#define  ZYNQ_BIT_UART_MODE_PAR(par)    (DEF_BIT_MASK(par, 3) & ZYNQ_BIT_UART_MODE_PAR_MSK)
#define  ZYNQ_BIT_UART_MODE_CHRL_MSK    (DEF_BIT_FIELD(1, 2))   /* Character length.                                    */
#define  ZYNQ_BIT_UART_MODE_CHRL(len)   (DEF_BIT_MASK(len, 2) & ZYNQ_BIT_UART_MODE_CHRL_MSK)
#define  ZYNQ_BIT_UART_MODE_CLKS        (DEF_BIT_00)            /* Clock source select.                                 */


                                                                /* ------ CHANNEL STATUS REGISTER BIT DEFINITION ------ */
#define  ZYNQ_BIT_UART_CSTAT_TNFUL       (DEF_BIT_14)           /* Transmit FIFO nearly full.                           */
#define  ZYNQ_BIT_UART_CSTAT_TTRIG       (DEF_BIT_13)           /* Transmit FIFO continuous status.                     */
#define  ZYNQ_BIT_UART_CSTAT_FDELT       (DEF_BIT_12)           /* Receive FIFO delay trigger continuous status.        */
#define  ZYNQ_BIT_UART_CSTAT_TACTIVE     (DEF_BIT_11)           /* Transmit state machine active status.                */
#define  ZYNQ_BIT_UART_CSTAT_RACTIVE     (DEF_BIT_10)           /* Receiver state machine active status.                */
#define  ZYNQ_BIT_UART_CSTAT_TFUL        (DEF_BIT_04)           /* Transmit FIFO full continuous status.                */
#define  ZYNQ_BIT_UART_CSTAT_TEMPTY      (DEF_BIT_03)           /* Transmit FIFO empty continuous status.               */
#define  ZYNQ_BIT_UART_CSTAT_RFUL        (DEF_BIT_02)           /* Receive FIFO full continuous status.                 */
#define  ZYNQ_BIT_UART_CSTAT_REMPTY      (DEF_BIT_01)           /* Receive FIFO empty continuous status.                */
#define  ZYNQ_BIT_UART_CSTAT_RTRIG       (DEF_BIT_00)           /* Receive FIFO trigger continuous status.              */

                                                                /* --------- INTERRUPT SOURCE BIT DEFINITION ---------- */
#define  ZYNQ_BIT_UART_INTR_TOVR         (DEF_BIT_12)           /* Transmitter FIFO overflow interrupt.                 */
#define  ZYNQ_BIT_UART_INTR_TNFUL        (DEF_BIT_11)           /* Transmitter FIFO nearly full interrupt.              */
#define  ZYNQ_BIT_UART_INTR_TTRIG        (DEF_BIT_10)           /* Transmitter FIFO trigger interrupt.                  */
#define  ZYNQ_BIT_UART_INTR_DMSI         (DEF_BIT_09)           /* Delta MODEM status indicator interrupt.              */
#define  ZYNQ_BIT_UART_INTR_TIMEOUT      (DEF_BIT_08)           /* Receiver timeout error interrupt.                    */
#define  ZYNQ_BIT_UART_INTR_PARE         (DEF_BIT_07)           /* Receiver parity error interrupt.                     */
#define  ZYNQ_BIT_UART_INTR_FRAME        (DEF_BIT_06)           /* Receiver framing error interrupt.                    */
#define  ZYNQ_BIT_UART_INTR_ROVR         (DEF_BIT_05)           /* Receiver overflow error interrupt.                   */
#define  ZYNQ_BIT_UART_INTR_TFUL         (DEF_BIT_04)           /* Transmitter FIFO full interrupt.                     */
#define  ZYNQ_BIT_UART_INTR_TEMPTY       (DEF_BIT_03)           /* Transmitter FIFO empty interrupt.                    */
#define  ZYNQ_BIT_UART_INTR_RFUL         (DEF_BIT_02)           /* Receiver FIFO full interrupt.                        */
#define  ZYNQ_BIT_UART_INTR_REMPTY       (DEF_BIT_01)           /* Receiver FIFO empty interrupt.                       */
#define  ZYNQ_BIT_UART_INTR_RTRIG        (DEF_BIT_00)           /* Receiver FIFO trigger interrupt.                     */




#define  ZYNQ_BIT_SLCR_UART_RST_1   (DEF_BIT_01)

#define  UART_REG_CLK  (50000000u)

#define  UART_INTR_ID  (82u)

/*
*********************************************************************************************************
*                                         LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/

static  BSP_OS_SEM   BSP_SerTxWait;
static  BSP_OS_SEM   BSP_SerRxWait;
static  BSP_OS_SEM   BSP_SerLock;


/*
*********************************************************************************************************
*********************************************************************************************************
*                                            GLOBAL FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/

void  BSP_Ser_Init (void)
{
    CPU_INT32U  temp;

                                                                /* ----------------- INIT OS OBJECTS ------------------ */
    BSP_OS_SemCreate(&BSP_SerTxWait,   0, "Serial Tx Wait");
    BSP_OS_SemCreate(&BSP_SerRxWait,   0, "Serial Rx Wait");
    BSP_OS_SemCreate(&BSP_SerLock,     1, "Serial Lock");


                                                                /* Reset the UART.                                      */
    ZYNQ_SLCR_REG->UART_RST_CTRL |=  ZYNQ_BIT_SLCR_UART_RST_1;
    ZYNQ_SLCR_REG->UART_RST_CTRL &= ~ZYNQ_BIT_SLCR_UART_RST_1;


                                                                /* Configure MIO pins 48 & 49.                          */
    ZYNQ_SLCR_REG->SLCR_UNLOCK = ZYNQ_SLCR_UNLOCK_KEY;
    CPU_MB();
    ZYNQ_SLCR_REG->MIO_PIN_48 = ZYNQ_BIT_MIO_PULL_UP     |
                                ZYNQ_BIT_MIO_IO_TYPE(1u) |
                                ZYNQ_BIT_MIO_L3_SEL(7u);

    ZYNQ_SLCR_REG->MIO_PIN_49 = ZYNQ_BIT_MIO_PULL_UP     |
                                ZYNQ_BIT_MIO_IO_TYPE(1u) |
                                ZYNQ_BIT_MIO_L3_SEL(7u)  |
                                ZYNQ_BIT_MIO_TRI_ENABLE;
    CPU_MB();
    ZYNQ_SLCR_REG->SLCR_LOCK   = ZYNQ_SLCR_LOCK_KEY;

                                                                /* Configure mode and baud rate.                        */
    temp  = ZYNQ_BIT_UART_MODE_CHMODE(0u) |
            ZYNQ_BIT_UART_MODE_NBSTOP(0u) |
            ZYNQ_BIT_UART_MODE_PAR(4u)    |
            ZYNQ_BIT_UART_MODE_CHRL(0u);

    BSP_UART1_REG->MODE = temp;

    BSP_UART1_REG->BAUD_DIV = 6u;
    BSP_UART1_REG->BAUD     = 62u;

    BSP_UART1_REG->CTRL = ZYNQ_BIT_UART_CTRL_TXRES;
    while(DEF_BIT_IS_SET(BSP_UART1_REG->CTRL, ZYNQ_BIT_UART_CTRL_TXRES)) {
        ;
    }

    BSP_UART1_REG->CTRL = ZYNQ_BIT_UART_CTRL_RXRES;
    while(DEF_BIT_IS_SET(BSP_UART1_REG->CTRL, ZYNQ_BIT_UART_CTRL_RXRES)) {
        ;
    }


    BSP_UART1_REG->CTRL |=  ZYNQ_BIT_UART_CTRL_TXEN;
    BSP_UART1_REG->CTRL &= ~ZYNQ_BIT_UART_CTRL_TXDIS;

    BSP_UART1_REG->CTRL |=  ZYNQ_BIT_UART_CTRL_RXEN;
    BSP_UART1_REG->CTRL &= ~ZYNQ_BIT_UART_CTRL_RXDIS;


                                                                /* ISR handler setup.                                   */
    BSP_IntVectSet (UART_INTR_ID,
                    0u,
                    DEF_BIT_00,
                    BSP_Ser_ISR_Handler);

    BSP_IntSrcEn(UART_INTR_ID);

    BSP_UART1_REG->RX_FIFO_LVL = 1u;
}



/*
*********************************************************************************************************
*                                          BSP_Ser_WrByteUnlocked()
*
* Description : Writes a single byte to a serial port.
*
* Argument(s) : c           The character to output.
*
* Return(s)   : none.
*
* Caller(s)   : BSP_Ser_WrByte()
*               BSP_Ser_WrByteUnlocked()
*
* Note(s)     : (1) This function blocks until room is available in the UART for the byte to be sent.
*********************************************************************************************************
*/

void  BSP_Ser_WrByteUnlocked  (CPU_INT08U  c)
{
    BSP_UART1_REG->INTR_EN = ZYNQ_BIT_UART_INTR_TEMPTY;

    BSP_UART1_REG->TX_RX_FIFO = c;


    BSP_OS_SemWait(&BSP_SerTxWait, 0);
}


/*
*********************************************************************************************************
*                                                BSP_Ser_WrByte()
*
* Description : Writes a single byte to a serial port.
*
* Argument(s) : tx_byte     The character to output.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_Ser_WrByte(CPU_INT08U  c)
{
    BSP_OS_SemWait(&BSP_SerLock, 0);                            /* Obtain access to the serial interface              */

    BSP_Ser_WrByteUnlocked(c);

    BSP_OS_SemPost(&BSP_SerLock);                               /* Release access to the serial interface             */
}


/*
*********************************************************************************************************
*                                       BSP_Ser_RdByteUnlocked()
*
* Description : Receive a single byte.
*
* Argument(s) : none.
*
* Return(s)   : The received byte.
*
* Caller(s)   : BSP_Ser_RdByte()
*               BSP_Ser_RdStr()
*
* Note(s)     : none.
*********************************************************************************************************
*/

CPU_INT08U  BSP_Ser_RdByteUnlocked  (void)
{
    CPU_INT08U  c;

    if(DEF_BIT_IS_SET(BSP_UART1_REG->CHAN_STAT, ZYNQ_BIT_UART_CSTAT_REMPTY)) {
        BSP_UART1_REG->INTR_EN = ZYNQ_BIT_UART_INTR_RTRIG;
        BSP_OS_SemWait(&BSP_SerRxWait, 0);
    }

    c = BSP_UART1_REG->TX_RX_FIFO;

    return (c);
}


/*
*********************************************************************************************************
*                                                BSP_Ser_RdByte()
*
* Description : Receive a single byte.
*
* Argument(s) : none.
*
* Return(s)   : The received byte.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) This functions blocks until a data is received.
*
*               (2) It can not be called from an ISR.
*********************************************************************************************************
*/

CPU_INT08U  BSP_Ser_RdByte (void)
{
    CPU_INT08U  rx_byte;


    BSP_OS_SemWait(&BSP_SerLock, 0);                            /* Obtain access to the serial interface.             */

    rx_byte = BSP_Ser_RdByteUnlocked();

    BSP_OS_SemPost(&BSP_SerLock);                               /* Release access to the serial interface.            */

    return (rx_byte);
}


/*
*********************************************************************************************************
*                                                BSP_Ser_WrStr()
*
* Description : Transmits a string.
*
* Argument(s) : p_str       Pointer to the string that will be transmitted.
*
* Caller(s)   : Application.
*
* Return(s)   : none.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_Ser_WrStr (CPU_CHAR  *p_str)
{
    CPU_BOOLEAN  err;


    if (p_str == DEF_NULL) {
        return;
    }


    err = BSP_OS_SemWait(&BSP_SerLock, 0);                      /* Obtain access to the serial interface              */
    if (err != DEF_OK ) {
        return;
    }

    while ((*p_str) != DEF_NULL) {
        BSP_Ser_WrByteUnlocked(*p_str++);
    }

    BSP_OS_SemPost(&BSP_SerLock);                               /* Release access to the serial interface             */
}


/*
*********************************************************************************************************
*                                         BSP_Ser_ISR_Handler()
*
* Description : Serial ISR.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : none.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_Ser_ISR_Handler (CPU_INT32U cpu_id)
{
    if (DEF_BIT_IS_SET(BSP_UART1_REG->INTR_MASK, ZYNQ_BIT_UART_INTR_RTRIG)) {
        BSP_UART1_REG->INTR_STAT = ZYNQ_BIT_UART_INTR_RTRIG;
        BSP_OS_SemPost(&BSP_SerRxWait);                         /* Post to the sempahore                                */
    }

    if (DEF_BIT_IS_SET(BSP_UART1_REG->INTR_MASK, ZYNQ_BIT_UART_INTR_TEMPTY)) {
        BSP_UART1_REG->INTR_STAT = ZYNQ_BIT_UART_INTR_TEMPTY;
        BSP_OS_SemPost(&BSP_SerTxWait);                         /* Post to the semaphore                                */
    }

    BSP_UART1_REG->INTR_DIS = 0xFFFFFFFF;                       /* Mask all interrupts.                                 */
}


/*
*********************************************************************************************************
*                                           BSP_Ser_Printf()
*
* Description : Print formatted data to the output serial port.
*
* Argument(s) : format      String that contains the text to be written.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) This function output a maximum of BSP_SER_PRINTF_STR_BUF_SIZE number of bytes to the
*                   serial port.  The calling function hence has to make sure the formatted string will
*                   be able fit into this string buffer or hence the output string will be truncated.
*********************************************************************************************************
*/

void  BSP_Ser_Printf (CPU_CHAR  *format, ...)
{
    CPU_CHAR  buf_str[BSP_SER_PRINTF_STR_BUF_SIZE + 1u];
    va_list   v_args;


    va_start(v_args, format);
   (void)vsnprintf((char       *)&buf_str[0],
                   (size_t      ) sizeof(buf_str),
                   (char const *) format,
                                  v_args);
    va_end(v_args);

    BSP_Ser_WrStr(buf_str);
}


