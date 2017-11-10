/*
*********************************************************************************************************
*                                               uC/HTTP
*                                      Hypertext Transfer Protocol
*
*                         (c) Copyright 2004-2015; Micrium, Inc.; Weston, FL
*
*                  All rights reserved.  Protected by international copyright laws.
*
*                  uC/HTTP is provided in source form to registered licensees ONLY.  It is
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
*                                             HTTP CLIENT
*
* Filename      : http-c_type.h
* Version       : V3.00.01
* Programmer(s) : MM
*                 AL
*********************************************************************************************************
* Note(s)       : (1) Assumes the following versions (or more recent) of software modules are included in
*                     the project build :
*
*                       (a) uC/CPU    V1.29.02
*                       (b) uC/LIB    V1.38.00
*                       (c) uC/Common V1.01.00
*                       (d) uC/TCP-IP V3.03.00
*
*
*                 (2) For additional details on the features available with uC/HTTPc, the API, the
*                     installation, etc. Please refer to the uC/HTTPc documentation available at
*                     https://doc.micrium.com/HTTPc.
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*********************************************************************************************************
*                                               MODULE
*
* Note(s) : (1) This main network protocol suite header file is protected from multiple pre-processor
*               inclusion through use of the HTTPc module present pre-processor macro definition.
*********************************************************************************************************
*********************************************************************************************************
*/

#ifndef  HTTPc_TYPE_MODULE_PRESENT                              /* See Note #1.                                         */
#define  HTTPc_TYPE_MODULE_PRESENT

/*
*********************************************************************************************************
*********************************************************************************************************
*                                         HTTPc INCLUDE FILES
*********************************************************************************************************
*********************************************************************************************************
*/

#include  <cpu.h>
#include  <Source/net_type.h>


/*
*********************************************************************************************************
*********************************************************************************************************
*                                              DATA TYPES
*********************************************************************************************************
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                       CONFIGURATION DATA TYPE
*********************************************************************************************************
*/

typedef  struct  httpc_cfg {

/*
*--------------------------------------------------------------------------------------------------------
*                                      TASK CONFIGURATION
*--------------------------------------------------------------------------------------------------------
*/

    CPU_INT08U                 TaskDly_ms;                      /* Task Delay in milliseconds.                          */


/*
*--------------------------------------------------------------------------------------------------------
*                                   CONNECTION CONFIGURATION
*--------------------------------------------------------------------------------------------------------
*/
    CPU_INT08U                 MsgQ_Size;                       /* Message Queue Size.                                  */
    CPU_INT16U                 ConnConnectTimeout_ms;           /* Connection Connect Timeout.                          */
    CPU_INT16U                 ConnInactivityTimeout_s;         /* Connection Inactivitu Timeout.                       */


} HTTPc_CFG;


/*
*********************************************************************************************************
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*********************************************************************************************************
*/

#endif  /* HTTPc_TYPE_MODULE_PRESENT  */
