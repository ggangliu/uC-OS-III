/*
*********************************************************************************************************
*                                               uC/DNSc
*                                     Domain Name Server (client)
*
*                         (c) Copyright 2004-2014; Micrium, Inc.; Weston, FL
*
*                  All rights reserved.  Protected by international copyright laws.
*
*                  uC/DNSc is provided in source form to registered licensees ONLY.  It is
*                  illegal to distribute this source code to any third party unless you receive
*                  written permission by an authorized Micrium representative.  Knowledge of
*                  the source code may NOT be used to develop a similar product.
*
*                  Please help us continue to provide the Embedded community with the finest
*                  software available.  Your honesty is greatly appreciated.
*
*                  You can find our product's user manual, API reference, release notes and
*                  more information at: https://doc.micrium.com
*
*                  You can contact us at: http://www.micrium.com
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                           uC/DNSc TEST CODE
*
* Filename      : dns-c_cmd.h
* Version       : V2.00.01
* Programmer(s) : AA
*********************************************************************************************************
* Note(s)       : none.
*********************************************************************************************************
*/

#ifndef  DNSc_CMD_MODULE_PRESENT
#define  DNSc_CMD_MODULE_PRESENT

/*
*********************************************************************************************************
*********************************************************************************************************
*                                             DATA TYPES
*********************************************************************************************************
*********************************************************************************************************
*/

typedef enum dnsc_test_err {
    DNSc_CMD_ERR_NONE             = 0,                         /* No errors.                                           */

    DNSc_CMD_ERR_INIT             = 10u,

    DNSc_CMD_ERR_SHELL_INIT       = 11u,                       /* Command table not added to uC-Shell.                 */

} DNSc_CMD_ERR;


/*
*********************************************************************************************************
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*********************************************************************************************************
*/

void  DNScCmd_Init (DNSc_CMD_ERR  *p_err);



#endif                                                          /* End of template module include.      */

