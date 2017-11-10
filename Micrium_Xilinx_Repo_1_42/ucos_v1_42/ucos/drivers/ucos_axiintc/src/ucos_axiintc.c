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
* Filename      : ucos_axiintc.c
* Version       : V1.42
* Programmer(s) : JBL
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#include <xparameters.h>
#include <ucos_axiintc.h>

/*
*********************************************************************************************************
*                                       EXTERN DECLARATIONS
*********************************************************************************************************
*/

extern  UCOS_AXIINTC_Config  UCOS_AXIINTC_ConfigTable[];


/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/

static  AXIINTC  UCOS_AXIINTC_Table[XPAR_UCOS_AXIINTC_NUM_INSTANCES];


/*
*********************************************************************************************************
*********************************************************************************************************
**                                         GLOBAL FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            AXIIntCInit()
*
* Description : Initialize an AXI Interrupt Controller.
*
* Argument(s) : device_id  ID of the controller to init.
*
* Return(s)   : Handle to the AXI Interrupt Controller instance or DEF_NULL if
*               the devide id is invalid.
*
* Note(s)     : Should be called before accessing any other functionalities of this peripheral.
*
*********************************************************************************************************
*/

AXIINTC_HANDLE  AXIIntCInit (CPU_INT32U device_id)
{
    AXIINTC_HANDLE Handle;
    AXIINTC_PTR    IntC;
    CPU_SR_ALLOC();


    if (device_id > XPAR_UCOS_AXIINTC_NUM_INSTANCES) {
        return DEF_NULL;
    }

    Handle = (AXIINTC_HANDLE)&UCOS_AXIINTC_Table[device_id];

    Handle->DeviceId = UCOS_AXIINTC_ConfigTable[device_id].DeviceId;
    IntC = (AXIINTC_PTR)UCOS_AXIINTC_ConfigTable[device_id].BaseAddress;
    Handle->AXIIntC = IntC;

    CPU_CRITICAL_ENTER();
    IntC->MER = AXIINTC_BIT_MER_ME | AXIINTC_BIT_MER_HIE;       /* Enable hardware interrupts.                          */
    CPU_CRITICAL_EXIT();

    return (Handle);
}


/*
*********************************************************************************************************
*                                           AXIIntCIntEnSet()
*
* Description : Set a bit in the interrupt enable register.
*
* Argument(s) : handle   Handle to the interrupt controller instance.
*               int_id   ID of the interrupt to set.
*
* Return(s)   : DEF_OK     Operation successful.
*               DEF_FAIL   Operation failed.
*
* Note(s)     : none.
*
*********************************************************************************************************
*/

/* TODO - Handle case were the SIE register is not available. */
CPU_BOOLEAN  AXIIntCIntEnSet (AXIINTC_HANDLE handle, CPU_INT32U int_id)
{
    AXIINTC_PTR IntC;


    IntC = handle->AXIIntC;


    IntC->SIE = 1 << int_id;

    return (DEF_OK);
}


/*
*********************************************************************************************************
*                                           AXIIntCIntEnClr()
*
* Description : Clear a bit in the interrupt enable register.
*
* Argument(s) : handle   Handle to the interrupt controller instance.
*               int_id   ID of the interrupt to clear.
*
* Return(s)   : DEF_OK     Operation successful.
*               DEF_FAIL   Operation failed.
*
* Note(s)     : nonel.
*
*********************************************************************************************************
*/

/* TODO - Handle case where the CIE register is not available. */
CPU_BOOLEAN  AXIIntCIntEnClr (AXIINTC_HANDLE handle, CPU_INT32U int_id)
{
    AXIINTC_PTR IntC;


    IntC = handle->AXIIntC;


    IntC->CIE = 1 << int_id;

    return (DEF_OK);
}
