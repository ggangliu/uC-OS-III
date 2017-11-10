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
*                                    HTTP CLIENT CONNECTION MODULE
*
* Filename      : http-c_conn.h
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

#ifndef  HTTPc_CONN_MODULE_PRESENT                              /* See Note #1.                                         */
#define  HTTPc_CONN_MODULE_PRESENT


/*
*********************************************************************************************************
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*********************************************************************************************************
*/

#include  <cpu.h>
#include  <cpu_core.h>

#include  <lib_def.h>
#include  <lib_str.h>
#include  <lib_ascii.h>

#include  <http-c_cfg.h>
#include  "../../Common/http.h"
#include  "http-c.h"


/*
*********************************************************************************************************
*********************************************************************************************************
*                                          FUNCTION PROTOTYPES
*********************************************************************************************************
*********************************************************************************************************
*/

void          HTTPcConn_Process         (HTTPc_CONN  *p_conn);

void          HTTPcConn_Connect         (HTTPc_CONN  *p_conn,
                                         HTTPc_ERR   *p_err);

void          HTTPcConn_Close           (HTTPc_CONN  *p_conn,
                                         HTTPc_ERR   *p_err);

void          HTTPcConn_TransProcess    (HTTPc_CONN  *p_conn);

void          HTTPcConn_TransParamReset (HTTPc_CONN  *p_conn);

CPU_BOOLEAN   HTTPcConn_TransComplete   (HTTPc_CONN  *p_conn);

void          HTTPcConn_Add             (HTTPc_CONN  *p_conn);

void          HTTPcConn_Remove          (HTTPc_CONN  *p_conn);

void          HTTPcConn_ReqAdd          (HTTPc_REQ   *p_req,
                                         HTTPc_ERR   *p_err);

void          HTTPcConn_ReqRemove       (HTTPc_CONN  *p_conn);


/*
*********************************************************************************************************
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*********************************************************************************************************
*/

#endif  /* HTTPc_CONN_MODULE_PRESENT  */
