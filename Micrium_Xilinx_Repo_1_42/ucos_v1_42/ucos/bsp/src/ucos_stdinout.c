/*
*********************************************************************************************************
*
*                                    MICRIUM BOARD SUPPORT PACKAGE
*
*                        (c) Copyright 2014-2015; Micrium, Inc.; Weston, FL
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
*                                          STDIN and STDOUT
*
* Filename      : ucos_stdinout.c
* Version       : V1.42
* Programmer(s) : JBL
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#include  <app_cfg.h>
#include  <cpu_core.h>
#include  <cpu.h>
#include  <ucos_bsp.h>
#include  "ucos_int.h"
#include  <xparameters.h>

#if (UCOS_STDOUT_DRIVER == UCOS_UART_PS7_UART)
#include  <ucos_uartps.h>
#endif /* #if (UCOS_STDOUT_DRIVER == UCOS_UART_PS7_UART) */

#if (UCOS_STDOUT_DRIVER == UCOS_UART_AXI_UART_LITE)
#include  <ucos_axiuartlite.h>
#endif /* #if (UCOS_STDOUT_DRIVER == UCOS_UART_AXI_UART_LITE) */


#if (UCOS_STDOUT_DRIVER == UCOS_UART_PS7_UART)
UARTPS_HANDLE  STDOUT_Handle;
#endif /* #if (UCOS_STDOUT_DRIVER == UCOS_UART_PS7_UART) */

#if (UCOS_STDOUT_DRIVER == UCOS_UART_AXI_UART_LITE)
AXIUARTLITE_HANDLE STDOUT_Handle;
#endif /* #if (UCOS_STDOUT_DRIVER == UCOS_UART_AXI_UART_LITE) */

void outbyte (char c);


void UCOS_StdInOutInit()
{
#if (UCOS_STDOUT_DRIVER == UCOS_UART_PS7_UART)
    STDOUT_Handle = UARTPS_Init(UCOS_STDOUT_DEVICE_ID);
#endif /* #if (UCOS_STDOUT_DRIVER == UCOS_UART_PS7_UART) */

#if (UCOS_STDOUT_DRIVER == UCOS_UART_AXI_UART_LITE)
    STDOUT_Handle = AXIUARTLite_Init(UCOS_STDOUT_DEVICE_ID);
#endif /* #if (UCOS_STDOUT_DRIVER == UCOS_UART_AXI_UART_LITE) */

}


void  UCOS_Print (const CPU_CHAR *p_string)
{
#if (UCOS_STDOUT_DRIVER == UCOS_UART_PS7_UART)
    UARTPS_WrStr(STDOUT_Handle, p_string);
#endif /* #if (UCOS_STDOUT_DRIVER == UCOS_UART_PS7_UART) */

#if (UCOS_STDOUT_DRIVER == UCOS_UART_AXI_UART_LITE)
    AXIUARTLite_WrStr(STDOUT_Handle, p_string);
#endif /* #if (UCOS_STDOUT_DRIVER == UCOS_UART_AXI_UART_LITE) */
}


CPU_INT32U UCOS_Read (CPU_CHAR *buf, CPU_INT32U cnt)
{
    CPU_INT32U i = 0;

#if (UCOS_STDOUT_DRIVER == UCOS_UART_PS7_UART)
    for (i = 0; i < cnt; i++) {
        *(buf + i) = UARTPS_RdByte(STDOUT_Handle);
        if ((*(buf + i) == '\n' || *(buf + i) == '\r'))
        {
            i++;
            break;
        }
    }
#endif /* #if (UCOS_STDOUT_DRIVER == UCOS_UART_PS7_UART) */

#if (UCOS_STDOUT_DRIVER == UCOS_UART_AXI_UART_LITE)
    for (i = 0; i < cnt; i++) {
        *(buf + i) = AXIUARTLite_RdByte(STDOUT_Handle);
        if ((*(buf + i) == '\n' || *(buf + i) == '\r'))
        {
            i++;
            break;
        }
    }
#endif /* #if (UCOS_STDOUT_DRIVER == UCOS_UART_AXI_UART_LITE) */

    return i;
}


void outbyte (char c)
{
#if (UCOS_STDOUT_DRIVER == UCOS_UART_PS7_UART)
    UARTPS_WrByte(STDOUT_Handle, c);
#endif /* #if (UCOS_STDOUT_DRIVER == UCOS_UART_PS7_UART) */

#if (UCOS_STDOUT_DRIVER == UCOS_UART_AXI_UART_LITE)
    AXIUARTLite_WrByte(STDOUT_Handle, c);
#endif /* #if (UCOS_STDOUT_DRIVER == UCOS_UART_AXI_UART_LITE) */
}
