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
*                                              AXI TIMER
*
* Filename      : ucos_axitimer.c
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
#include <ucos_axitimer.h>

#include <ucos_bsp.h>
#include <ucos_int.h>


extern UCOS_AXITIMER_Config UCOS_AXITIMER_ConfigTable[];

static UCOS_AXITIMER UCOS_AXITIMER_Table[XPAR_UCOS_AXITIMER_NUM_INSTANCES];


/*
*********************************************************************************************************
*********************************************************************************************************
**                                         GLOBAL FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            AXITimer_Init()
*
* Description : Initialize an AXI Timer.
*
* Argument(s) : device_id  ID of the timer to init.
*
* Return(s)   : Handle to the AXI Timer instance or DEF_NULL if
*               the devide id is invalid.
*
* Note(s)     : Should be called before accessing any other functionalities of this peripheral.
*
*********************************************************************************************************
*/

AXITIMER_HANDLE AXITimer_Init (CPU_INT32U device_id)
{
    AXITIMER_HANDLE handle;
    AXITIMER_PTR    tmr;
    CPU_INT32U      int_source;
    CPU_SR_ALLOC();


    if (device_id > XPAR_UCOS_AXITIMER_NUM_INSTANCES) {
        return DEF_NULL;
    }

    handle = (AXITIMER_HANDLE)&UCOS_AXITIMER_Table[device_id];

    handle->DeviceId = UCOS_AXITIMER_ConfigTable[device_id].DeviceId;
    tmr = (AXITIMER_PTR)UCOS_AXITIMER_ConfigTable[device_id].BaseAddress;
    handle->AXITimer = tmr;
    handle->TmrFreq = UCOS_AXITIMER_ConfigTable[device_id].TmrFreq;

    handle->Tmr0Callback = DEF_NULL;
    handle->Tmr1Callback = DEF_NULL;

    int_source = UCOS_AXITIMER_ConfigTable[device_id].IntSource;

    if (int_source != UCOS_INT_SOURCE_NONE) {
        UCOS_IntVectSet(int_source,
                        0u,
                        0u,
                        AXITimer_IntHandler,
                        (void *)handle);

        UCOS_IntSrcEn(int_source);
    }


    CPU_CRITICAL_ENTER(); /* Reset the timers. */
    tmr->TCSR0 = AXITIMER_BIT_TCSR_TINT | AXITIMER_BIT_TCSR_LOAD;
    tmr->TCSR0 = 0;

    tmr->TCSR1 = AXITIMER_BIT_TCSR_TINT | AXITIMER_BIT_TCSR_LOAD;
    tmr->TCSR1 = 0;
    CPU_CRITICAL_EXIT();

    return (handle);
}


/*
*********************************************************************************************************
*                                            AXITimer_Start()
*
* Description : Start a Timer.
*
* Argument(s) : handle   Handle to the interrupt controller instance.
*               tmr_nbr  Index of the AXI timer to access.
*
* Return(s)   : DEF_OK     Operation successful.
*               DEF_FAIL   Operation failed.
*
* Note(s)     : none.
*
*********************************************************************************************************
*/

CPU_BOOLEAN AXITimer_Start (AXITIMER_HANDLE handle, CPU_INT32U tmr_nbr)
{
    AXITIMER_PTR tmr;
    CPU_SR_ALLOC();


    tmr = handle->AXITimer;

    CPU_CRITICAL_ENTER();
    if (tmr_nbr == 0) {
        tmr->TCSR0 |= AXITIMER_BIT_TCSR_TINT | AXITIMER_BIT_TCSR_LOAD;
        tmr->TCSR0  = (AXITIMER_BIT_TCSR_ENT | tmr->TCSR0) & ~(AXITIMER_BIT_TCSR_TINT | AXITIMER_BIT_TCSR_LOAD);
    }
    else if (tmr_nbr == 1) {
        tmr->TCSR1 |= AXITIMER_BIT_TCSR_TINT | AXITIMER_BIT_TCSR_LOAD;
        tmr->TCSR1  = (AXITIMER_BIT_TCSR_ENT | tmr->TCSR1) & ~(AXITIMER_BIT_TCSR_TINT | AXITIMER_BIT_TCSR_LOAD);
    } else {
        CPU_CRITICAL_EXIT();
        return (DEF_FAIL);
    }
    CPU_CRITICAL_EXIT();

    return (DEF_OK);
}


/*
*********************************************************************************************************
*                                            AXITimer_Stop()
*
* Description : Stop a Timer.
*
* Argument(s) : handle   Handle to the interrupt controller instance.
*               tmr_nbr  Index of the AXI timer to access.
*
* Return(s)   : DEF_OK     Operation successful.
*               DEF_FAIL   Operation failed.
*
* Note(s)     : none.
*
*********************************************************************************************************
*/

CPU_BOOLEAN AXITimer_Stop (AXITIMER_HANDLE handle, CPU_INT32U tmr_nbr)
{
    AXITIMER_PTR tmr;
    CPU_SR_ALLOC();


    tmr = handle->AXITimer;

    CPU_CRITICAL_ENTER();
    if (tmr_nbr == 0) {
        tmr->TCSR0 &= ~AXITIMER_BIT_TCSR_ENT;
    }
    else if (tmr_nbr == 1) {
        tmr->TCSR1 &= ~AXITIMER_BIT_TCSR_ENT;
    } else {
        CPU_CRITICAL_EXIT();
        return (DEF_FAIL);
    }
    CPU_CRITICAL_EXIT();

    return (DEF_OK);
}


/*
*********************************************************************************************************
*                                            AXITimer_OptSet()
*
* Description : Configure (Set) the options of a timer.
*
* Argument(s) : handle   Handle to the interrupt controller instance.
*               opt      Options to set.
*
*                   Valid options are :
*                        AXITIMER_BIT_TCSR_MDT
*                        AXITIMER_BIT_TCSR_UDT
*                        AXITIMER_BIT_TCSR_GENT
*                        AXITIMER_BIT_TCSR_CAPT
*                        AXITIMER_BIT_TCSR_ARHT
*                        AXITIMER_BIT_TCSR_LOAD
*                        AXITIMER_BIT_TCSR_ENIT
*                        AXITIMER_BIT_TCSR_ENT
*                        AXITIMER_BIT_TCSR_TINT
*                        AXITIMER_BIT_TCSR_PWMA
*                        AXITIMER_BIT_TCSR_ENALL
*                        AXITIMER_BIT_TCSR_CASC
*
*               tmr_nbr  Index of the AXI timer to access.
*
* Return(s)   : DEF_OK     Operation successful.
*               DEF_FAIL   Operation failed.
*
* Note(s)     : This will only set the options specified. Already set options will be preserved.
*
*********************************************************************************************************
*/

CPU_BOOLEAN AXITimer_OptSet (AXITIMER_HANDLE handle, CPU_INT32U tmr_nbr, CPU_INT32U opt)
{
    AXITIMER_PTR tmr;
    CPU_SR_ALLOC();


    tmr = handle->AXITimer;

    CPU_CRITICAL_ENTER();
    if (tmr_nbr == 0) {
        tmr->TCSR0 |= opt & AXITIMER_OPT_MASK;
    }
    else if (tmr_nbr == 1) {
        tmr->TCSR1 |= opt & AXITIMER_OPT_MASK;
    } else {
        CPU_CRITICAL_EXIT();
        return (DEF_FAIL);
    }
    CPU_CRITICAL_EXIT();

    return (DEF_OK);
}


/*
*********************************************************************************************************
*                                            AXITimer_OptClr()
*
* Description : Configure (Clear) the options of a timer.
*
* Argument(s) : handle   Handle to the interrupt controller instance.
*               opt      Options to clear.
*
*                   Valid options are :
*                       AXITIMER_OPT_MODE
*                       AXITIMER_OPT_DOWN
*                       AXITIMER_OPT_GEN
*                       AXITIMER_OPT_CAPTURE
*                       AXITIMER_OPT_AUTO_RELOAD
*                       AXITIMER_OPT_INT
*                       AXITIMER_OPT_PWM
*
*               tmr_nbr  Index of the AXI timer to access.
*
* Return(s)   : DEF_OK     Operation successful.
*               DEF_FAIL   Operation failed.
*
* Note(s)     : This will only clear the options specified. Other set options will be preserved.
*
*********************************************************************************************************
*/
CPU_BOOLEAN AXITimer_OptClr (AXITIMER_HANDLE handle, CPU_INT32U tmr_nbr, CPU_INT32U opt)
{
    AXITIMER_PTR tmr;
    CPU_SR_ALLOC();


    tmr = handle->AXITimer;

    CPU_CRITICAL_ENTER();
    if (tmr_nbr == 0) {
        tmr->TCSR0 &= ~(opt & AXITIMER_OPT_MASK);
    } else if (tmr_nbr == 1) {
        tmr->TCSR1 &= ~(opt & AXITIMER_OPT_MASK);
    } else {
        CPU_CRITICAL_EXIT();
        return (DEF_FAIL);
    }
    CPU_CRITICAL_EXIT();

    return (DEF_OK);
}


/*
*********************************************************************************************************
*                                            AXITimer_CtrGet()
*
* Description : Read a timer current counter.
*
* Argument(s) : handle   Handle to the interrupt controller instance.
*               tmr_nbr  Index of the AXI timer to access.
*
* Return(s)   : Timer counter value.
*
* Note(s)     : none.
*
*********************************************************************************************************
*/

CPU_INT32U AXITimer_CtrGet (AXITIMER_HANDLE handle, CPU_INT32U tmr_nbr)
{
    AXITIMER_PTR tmr;
    CPU_INT32U ctr;


    tmr = handle->AXITimer;

    if (tmr_nbr == 0) {
        ctr = tmr->TCR0;
    } else if (tmr_nbr == 1) {
        ctr = tmr->TCR1;
    } else {
        ctr = 0;
    }

    return (ctr);
}


/*
*********************************************************************************************************
*                                            AXITimer_LoadSet()
*
* Description : Set a time reload value.
*
* Argument(s) : handle        Handle to the interrupt controller instance.
*               cnt_load_val  Counter load value.
*               tmr_nbr       Index of the AXI timer to access.
*
* Return(s)   : DEF_OK     Operation successful.
*               DEF_FAIL   Operation failed.
*
* Note(s)     : none.
*
*********************************************************************************************************
*/

CPU_BOOLEAN AXITimer_LoadSet (AXITIMER_HANDLE handle, CPU_INT32U tmr_nbr, CPU_INT32U cnt_load_val)
{
    AXITIMER_PTR tmr;


    tmr = handle->AXITimer;

    if (tmr_nbr == 0) {
        tmr->TLR0 = cnt_load_val;
    } else if (tmr_nbr == 1) {
        tmr->TLR1 = cnt_load_val;
    } else {
        return (DEF_FAIL);
    }

    return (DEF_OK);
}


/*
*********************************************************************************************************
*                                            AXITimer_IntClr()
*
* Description : Clear a timer interrupt.
*
* Argument(s) : handle   Handle to the interrupt controller instance.
*               tmr_nbr  Index of the AXI timer to access.
*
* Return(s)   : DEF_OK     Operation successful.
*               DEF_FAIL   Operation failed.
*
* Note(s)     : none.
*
*********************************************************************************************************
*/

CPU_BOOLEAN AXITimer_IntClr (AXITIMER_HANDLE handle, CPU_INT32U tmr_nbr)
{
    AXITIMER_PTR tmr;
    CPU_SR_ALLOC();


    tmr = handle->AXITimer;

    CPU_CRITICAL_ENTER();
    if (tmr_nbr == 0) {
        tmr->TCSR0 = tmr->TCSR0;
    } else if (tmr_nbr == 1) {
        tmr->TCSR1 = tmr->TCSR1;
    } else {
        CPU_CRITICAL_EXIT();
        return (DEF_FAIL);
    }
    CPU_CRITICAL_EXIT();

    return (DEF_OK);
}


/*
*********************************************************************************************************
*                                          AXITimer_FreqGet()
*
* Description : Get the frequency of an AXI Timer instance.
*
* Argument(s) : handle   Handle to the interrupt controller instance.
*
* Return(s)   : Timer frequency or 0 if the frequency cannot be returned.
*
* Note(s)     : none.
*
*********************************************************************************************************
*/

CPU_INT32U AXITimer_FreqGet (AXITIMER_HANDLE handle)
{
    return (handle->TmrFreq);
}


/*
*********************************************************************************************************
*                                          AXITimer_CallbackSet()
*
* Description : Set the callback of an AXI Timer when an interrupt occurs.
*
* Argument(s) : handle    Handle to the interrupt controller instance.
*               tmr_nbr   Index of the AXI timer to access.
*               call_back Callback function or DEF_NULL to disable the callback.
*
* Return(s)   : DEF_OK     Operation successful.
*               DEF_FAIL   Operation failed.
*
* Note(s)     : The callback function has the following signature.
*                   void CallBackFnct (AXITIMER_HANDLE handle, CPU_INT32U tmr_nbr);
*
*               where "handle" is the handle to the timer instance and "tmr_nbr" the
*               timer index.
*
*********************************************************************************************************
*/

CPU_BOOLEAN AXITimer_CallbackSet (AXITIMER_HANDLE            handle,
                                  CPU_INT32U                 tmr_nbr,
                                  AXITIMER_CALLBACK_FNCT_PTR call_back)
{
    if (tmr_nbr == 0) {
        handle->Tmr0Callback = call_back;
    } else if (tmr_nbr == 1) {
        handle->Tmr1Callback = call_back;
    } else {
        return (DEF_FAIL);
    }

    return (DEF_OK);
}


/*
*********************************************************************************************************
*                                          AXITimer_IntHandler()
*
* Description : AXI Timer default interrupt handler.
*
* Argument(s) : p_int_arg   Handle to the interrupt controller instance.
*               cpu_id      Always 0.
*
* Return(s)   : none.
*
* Note(s)     : none.
*
*********************************************************************************************************
*/

void AXITimer_IntHandler (void       *p_int_arg,
                          CPU_INT32U  cpu_id)
{
    AXITIMER_HANDLE handle;
    AXITIMER_PTR    tmr;


    handle = (AXITIMER_HANDLE)p_int_arg;
    tmr = handle->AXITimer;

    if (((tmr->TCSR0 & AXITIMER_BIT_TCSR_TINT) != 0u) &&
         (tmr->TCSR0 & AXITIMER_BIT_TCSR_ENIT) != 0u) {
        tmr->TCSR0 = tmr->TCSR0;

        if (handle->Tmr0Callback != DEF_NULL) {
            (*handle->Tmr0Callback)(handle, 0u);
        }
    }

    if (((tmr->TCSR1 & AXITIMER_BIT_TCSR_TINT) != 0u) &&
         (tmr->TCSR1 & AXITIMER_BIT_TCSR_ENIT) != 0u) {
        tmr->TCSR1 = tmr->TCSR1;

        if (handle->Tmr1Callback != DEF_NULL) {
            (*handle->Tmr1Callback)(handle, 1u);
        }
    }
}
