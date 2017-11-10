/*
*********************************************************************************************************
*                                               uC/Clk
*                                             Clock module
*
*                      (c) Copyright 2004-2014; Micrium, Inc.; Weston, FL
*
*          All rights reserved.  Protected by international copyright laws.
*
*          uC/Clk is provided in source form to registered licensees ONLY.  It is
*          illegal to distribute this source code to any third party unless you receive
*          written permission by an authorized Micrium representative.  Knowledge of
*          the source code may NOT be used to develop a similar product.
*
*          Please help us continue to provide the Embedded community with the finest
*          software available.  Your honesty is greatly appreciated.
*
*          You can find our product's user manual, API reference, release notes and
*          more information at: https://doc.micrium.com
*
*          You can contact us at: www.micrium.com
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                          CLOCK / CALENDAR
*
* Filename      : clk_cmd.h
* Version       : V3.10.00
* Programmer(s) : AL
*                 AOP
*********************************************************************************************************
* Note(s)       : (1) Assumes the following versions (or more recent) of software modules are included in
*                     the project build :
*
*                     (a) uC/CPU    V1.30
*                     (b) uC/OS-II  V2.90 or
*                         uC/OS-III V3.03
*                     (c) uC/Shell  V1.03
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               MODULE
*********************************************************************************************************
*/

#ifndef  CLK_CMD_MODULE_PRESENT
#define  CLK_CMD_MODULE_PRESENT


/*
*********************************************************************************************************
*                                               DEFINES
*********************************************************************************************************
*/

typedef enum clk_cmd_err {
    CLK_CMD_ERR_NONE                       =   0,               /* No errors.                                           */
    CLK_CMD_ERR_HELP                       =   1,               /* Help requested by user.                              */

    CLK_CMD_ERR_MODULE_INIT                =  10,
    CLK_CMD_ERR_SHELL_INIT                 =  11,               /* Command table not added to uC-Shell.                 */
    CLK_CMD_ERR_SIGNALTASK_INIT            =  12,

    CLK_CMD_ERR_CMD_ARG_INVALID            =  30,
    CLK_CMD_ERR_CMD_ARG_NOT_IMPLEMENTED    =  31,
    CLK_CMD_ERR_CMD_ARG_NO_ARGS            =  32,

    CLK_CMD_ERR_PARSER_ARG_VALUE_INVALID   =  40

} CLK_CMD_ERR;


/*
*********************************************************************************************************
*                                             DATA TYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

void  ClkCmd_Init(CLK_CMD_ERR  *p_err);


/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif                                                          /* End of network test module include.                  */
