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
*                                     CORTEX A9 SNOOP CONTROL UNIT
*
* Filename      : ucos_scuc.c
* Version       : V1.42
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

#include  <xparameters.h>
#include  <ucos_scuc.h>


/*
*********************************************************************************************************
*********************************************************************************************************
**                                         GLOBAL FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             SCUC_En()
*
* Description : Enable the snoop control unit.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Note(s)     : none.
*
*********************************************************************************************************
*/

void SCUC_En (void)
{
    SCUCREG->CTRL |= SCUC_BIT_CTRL_SCUEN;
}


/*
*********************************************************************************************************
*                                           SCUC_InvalidateAll()
*
* Description : Invalidate all for the current core.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Note(s)     : none.
*
*********************************************************************************************************
*/

void SCUC_InvalidateAll (void)
{
    SCUCREG->INVALL = 0xF << (XPAR_CPU_ID * 4);
}


/*
*********************************************************************************************************
*                                           SCUC_SpeculativeLineFillsEn()
*
* Description : Enable speculative line fills to L2.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Note(s)     : none.
*
*********************************************************************************************************
*/

void SCUC_SpeculativeLineFillsEn (void)
{
    SCUCREG->CTRL |= SCUC_BIT_CTRL_SPECLFEN;
}


/*
*********************************************************************************************************
*                                           SCUC_StandbyEn()
*
* Description : Enable standby operation.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Note(s)     : none.
*
*********************************************************************************************************
*/

void SCUC_StandbyEn (void)
{
    SCUCREG->CTRL |= SCUC_BIT_CTRL_STANDBYEN;
}


/*
*********************************************************************************************************
*                                           SCUC_ICStandbyEn()
*
* Description : Enable standby operation.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Note(s)     : none.
*
*********************************************************************************************************
*/

void SCUC_ICStandbyEn (void)
{
    SCUCREG->CTRL |= SCUC_BIT_CTRL_ICSTANDBYEN;
}


/*
*********************************************************************************************************
*                                           SCUC_DevicePort0En()
*
* Description : For all non-cacheable access to master port 0.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Note(s)     : none.
*
*********************************************************************************************************
*/

void SCUC_DevicePort0En (void)
{
    SCUCREG->CTRL |= SCUC_BIT_CTRL_FORCEP0EN;
}
