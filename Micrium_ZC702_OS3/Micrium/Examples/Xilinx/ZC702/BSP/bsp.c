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
*                                ZYNQ-7000 EPP & ZC702 Evaluation Kit
*
* Filename      : bsp.c
* Version       : V1.00
* Programmer(s) : JBL
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#include  <cpu.h>
#include  <lib_def.h>

#include  <bsp.h>
#include  <bsp_int.h>


/*
*********************************************************************************************************
*                                             LOCAL DEFINES
*********************************************************************************************************
*/

#define  ZYNQ_REG_MIO_PIN_08 (*((CPU_REG32 *)0xF8000720))
#define  ZYNQ_REG_MIO_PIN_10 (*((CPU_REG32 *)0xF8000728))

#define  ZYNQ_REG_GPIO_DATA0 (*((CPU_REG32 *)0xE000A040))
#define  ZYNQ_REG_GPIO_DIRM0 (*((CPU_REG32 *)0xE000A204))
#define  ZYNQ_REG_GPIO_OEN0  (*((CPU_REG32 *)0xE000A208))



/*
*********************************************************************************************************
*********************************************************************************************************
*                                            GLOBAL FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                              BSP_Init()
*
* Description : Initialise the BSP.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*
*********************************************************************************************************
*/

void  BSP_Init (void)
{

    BSP_Int_Init();

    BSP_LED_Init();

    return;
}


/*
*********************************************************************************************************
*                                           BSP_CPU_ClkFreq()
*
* Description : Return the CPU clock frequency.
*
* Argument(s) : none.
*
* Return(s)   : CPU clock frequency in Hz.
*
* Caller(s)   : Various.
*
* Note(s)     : Currently hard coded in this example.
*
*********************************************************************************************************
*/

CPU_INT32U  BSP_CPU_ClkFreq (void)
{
    return (ZYNQ_APU_FREQ);
}


/*
*********************************************************************************************************
*                                         BSP_Periph_ClkFreq()
*
* Description : Return the private peripheral clock frequency.
*
* Argument(s) : none.
*
* Return(s)   : Clock frequency in Hz.
*
* Caller(s)   : Various.
*
* Note(s)     : Currently hard coded in this example.
*
*********************************************************************************************************
*/

CPU_INT32U  BSP_Periph_ClkFreq (void)
{
    return (ZYNQ_PERIPH_FREQ);
}



/*
*********************************************************************************************************
*                                            BSP_LED_Init()
*
* Description : Initialise user LEDs.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : BSP_Init().
*
* Note(s)     : none.
*
*********************************************************************************************************
*/

void  BSP_LED_Init (void)
{

    ZYNQ_SLCR_REG->SLCR_UNLOCK = ZYNQ_SLCR_UNLOCK_KEY;
    CPU_MB();                                                   /* Memory barrier.                                      */
    ZYNQ_REG_MIO_PIN_10  = ZYNQ_BIT_MIO_PULL_UP |               /* Configure MIO pins.                                  */
                           ZYNQ_BIT_MIO_IO_TYPE(1u);
    CPU_MB();                                                   /* Memory barrier.                                      */
    ZYNQ_SLCR_REG->SLCR_LOCK   = ZYNQ_SLCR_LOCK_KEY;


    ZYNQ_REG_GPIO_DIRM0 |= DEF_BIT_10;
    ZYNQ_REG_GPIO_OEN0  |= DEF_BIT_10;
    ZYNQ_REG_GPIO_DATA0 |= DEF_BIT_10;


}


/*
*********************************************************************************************************
*                                             BSP_LED_On()
*
* Description : Turn ON a led.
*
* Argument(s) : led     led number.
*
* Return(s)   : none..
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*
*********************************************************************************************************
*/

void  BSP_LED_On   (CPU_INT32U led)
{
    ZYNQ_REG_GPIO_DATA0 |= DEF_BIT_10;
}


/*
*********************************************************************************************************
*                                             BSP_LED_Off()
*
* Description : Turn OFF a led.
*
* Argument(s) : led     led number.
*
* Return(s)   : none..
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*
*********************************************************************************************************
*/

void  BSP_LED_Off  (CPU_INT32U led)
{
    ZYNQ_REG_GPIO_DATA0 &= ~DEF_BIT_10;
}


/*
*********************************************************************************************************
*                                             BSP_LED_Toggle()
*
* Description : Toggle an led.
*
* Argument(s) : led     led number.
*
* Return(s)   : none..
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*
*********************************************************************************************************
*/

void  BSP_LED_Toggle  (CPU_INT32U led)
{
    ZYNQ_REG_GPIO_DATA0 ^= DEF_BIT_10;
}
