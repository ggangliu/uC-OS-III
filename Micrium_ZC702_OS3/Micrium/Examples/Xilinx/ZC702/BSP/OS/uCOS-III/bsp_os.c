/*
*********************************************************************************************************
*
*                                    MICRIUM BOARD SUPPORT PACKAGE
*
*                          (c) Copyright 2003-2014; Micrium, Inc.; Weston, FL
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
*                                  CORTEX A9 OS BOARD SUPORT PACKAGE
*
* Filename      : bsp_os.c
* Version       : V1.00
* Programmer(s) : JBL
*                 DC
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#include  <lib_def.h>
#include  <cpu.h>

#include  <os_cpu.h>

#include  <bsp.h>
#include  <bsp_os.h>
#include  <bsp_int.h>



/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/

#define  ARM_PTMR_REG_PTLR     (*((CPU_REG32 *)(ARM_PRIV_PERIPH_BASE + 0x0600))) /* Private timer load register.            */
#define  ARM_PTMR_REG_PTCTRR   (*((CPU_REG32 *)(ARM_PRIV_PERIPH_BASE + 0x0604))) /* Private timer counter register.         */
#define  ARM_PTMR_REG_PTCTLR   (*((CPU_REG32 *)(ARM_PRIV_PERIPH_BASE + 0x0608))) /* Private timer control register.         */
#define  ARM_PTMR_REG_PTISR    (*((CPU_REG32 *)(ARM_PRIV_PERIPH_BASE + 0x060C))) /* Private timer interrupt status register.*/




/*
*********************************************************************************************************
*                                      BSP_OS_SemCreate()
*
* Description : Creates a sempahore to lock/unlock
*
* Argument(s) : p_sem        Pointer to a BSP_OS_SEM structure
*
*               sem_val      Initial value of the semaphore.
*
*               p_sem_name   Pointer to the semaphore name.
*
* Return(s)   : DEF_OK       if the semaphore was created.
*               DEF_FAIL     if the sempahore could not be created.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*
*********************************************************************************************************
*/

CPU_BOOLEAN  BSP_OS_SemCreate (BSP_OS_SEM       *p_sem,
                               BSP_OS_SEM_VAL    sem_val,
                               CPU_CHAR         *p_sem_name)
{
    OS_ERR     err;


    OSSemCreate((OS_SEM    *)p_sem,
                (CPU_CHAR  *)p_sem_name,
                (OS_SEM_CTR )sem_val,
                (OS_ERR    *)&err);

    if (err != OS_ERR_NONE) {
        return (DEF_FAIL);
    }

    return (DEF_OK);
}


/*
*********************************************************************************************************
*                                     BSP_OS_SemWait()
*
* Description : Wait on a semaphore to become available
*
* Argument(s) : sem          sempahore handler
*
*               dly_ms       delay in miliseconds to wait on the semaphore
*
* Return(s)   : DEF_OK       if the semaphore was acquire
*               DEF_FAIL     if the sempahore could not be acquire
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

CPU_BOOLEAN  BSP_OS_SemWait (BSP_OS_SEM  *p_sem,
                             CPU_INT32U   dly_ms)
{
    OS_ERR      err;
    CPU_INT32U  dly_ticks;


    dly_ticks  = ((dly_ms * DEF_TIME_NBR_mS_PER_SEC) / OSCfg_TickRate_Hz);

    OSSemPend((OS_SEM *)p_sem,
              (OS_TICK )dly_ticks,
              (OS_OPT  )OS_OPT_PEND_BLOCKING,
              (CPU_TS  )0,
              (OS_ERR *)&err);

    if (err != OS_ERR_NONE) {
       return (DEF_FAIL);
    }

    return (DEF_OK);
}


/*
*********************************************************************************************************
*                                      BSP_OS_SemPost()
*
* Description : Post a semaphore
*
* Argument(s) : sem          Semaphore handler
*
* Return(s)   : DEF_OK     if the semaphore was posted.
*               DEF_FAIL      if the sempahore could not be posted.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

CPU_BOOLEAN  BSP_OS_SemPost (BSP_OS_SEM *p_sem)
{
    OS_ERR  err;


    OSSemPost((OS_SEM *)p_sem,
              (OS_OPT  )OS_OPT_POST_1,
              (OS_ERR *)&err);

    if (err != OS_ERR_NONE) {
        return (DEF_FAIL);
    }

    return (DEF_OK);
}


/*
*********************************************************************************************************
*                                       BSP_OS_TmrTickHandler()
*
* Description : Interrupt handler for the tick timer
*
* Argument(s) : cpu_id     Source core id
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_OS_TmrTickHandler(CPU_INT32U cpu_id)
{
    ARM_PTMR_REG_PTISR = 0x01u;                                 /* Clear the interrupt.                                 */

    OSTimeTick();
}


/*
 *********************************************************************************************************
 *                                            BSP_OS_TmrTickInit()
 *
 * Description : Initialize uC/OS-III's tick source. Ticks per second will be obtained by the following
 *               Kernel #defines to keep synchronization between OS configuration and Clock timing.
 *                  OS2 - OS_TICKS_PER_SEC
 *                  OS3 - OSCfg_TickRate_Hz
 *
 * Argument(s) : none.
 *
 * Return(s)   : none.
 *
 * Caller(s)   : Application.
 *
 * Note(s)     : none.
 *********************************************************************************************************
 */

void BSP_OS_TmrTickInit (void)
{
    CPU_INT32U tmr_cnt;


    ARM_PTMR_REG_PTCTLR = 0x0006u;

    tmr_cnt = BSP_Periph_ClkFreq() / OSCfg_TickRate_Hz;

    ARM_PTMR_REG_PTLR = tmr_cnt;

    ARM_PTMR_REG_PTISR = 0x01u;

    BSP_IntVectSet (29u,
                    0u,
                    0u,
                    BSP_OS_TmrTickHandler);

    BSP_IntSrcEn(29u);

    ARM_PTMR_REG_PTCTLR |= 0x01;

}


/*
 *********************************************************************************************************
 *                                          OS_CPU_ExceptHndlr()
 *
 * Description : Handle any exceptions.
 *
 * Argument(s) : except_id     ARM exception type:
 *
 *                                  OS_CPU_ARM_EXCEPT_RESET             0x00
 *                                  OS_CPU_ARM_EXCEPT_UNDEF_INSTR       0x01
 *                                  OS_CPU_ARM_EXCEPT_SWI               0x02
 *                                  OS_CPU_ARM_EXCEPT_PREFETCH_ABORT    0x03
 *                                  OS_CPU_ARM_EXCEPT_DATA_ABORT        0x04
 *                                  OS_CPU_ARM_EXCEPT_ADDR_ABORT        0x05
 *                                  OS_CPU_ARM_EXCEPT_IRQ               0x06
 *                                  OS_CPU_ARM_EXCEPT_FIQ               0x07
 *
 * Return(s)   : none.
 *
 * Caller(s)   : OS_CPU_ARM_EXCEPT_HANDLER(), which is declared in os_cpu_a.s.
 *
 * Note(s)     : (1) Only OS_CPU_ARM_EXCEPT_FIQ and OS_CPU_ARM_EXCEPT_IRQ exceptions handler are implemented.
 *                   For the rest of the exception a infinite loop is implemented for debuging pruposes. This behavior
 *                   should be replaced with another behavior (reboot, etc).
 *********************************************************************************************************
 */

void OS_CPU_ExceptHndlr(CPU_INT32U except_id) {

    switch (except_id) {
    case OS_CPU_ARM_EXCEPT_FIQ:
        BSP_IntHandler();
        break;

    case OS_CPU_ARM_EXCEPT_IRQ:
        BSP_IntHandler();
        break;

    case OS_CPU_ARM_EXCEPT_RESET:
        /* $$$$ Insert code to handle a Reset exception               */

    case OS_CPU_ARM_EXCEPT_UNDEF_INSTR:
        /* $$$$ Insert code to handle a Undefine Instruction exception */

    case OS_CPU_ARM_EXCEPT_SWI:
        /* $$$$ Insert code to handle a Software exception             */

    case OS_CPU_ARM_EXCEPT_PREFETCH_ABORT:
        /* $$$$ Insert code to handle a Prefetch Abort exception       */

    case OS_CPU_ARM_EXCEPT_DATA_ABORT:
        /* $$$$ Insert code to handle a Data Abort exception           */

    case OS_CPU_ARM_EXCEPT_ADDR_ABORT:
        /* $$$$ Insert code to handle a Address Abort exception        */
    default:

        while (DEF_TRUE) { /* Infinite loop on other exceptions. (see note #1)          */
            CPU_WaitForEvent();
        }
    }
}
