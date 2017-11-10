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
*                                    HTTP CLIENT TASK MODULE
*
* Filename      : http-c_task.h
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
*                                         HTTPc INCLUDE FILES
*********************************************************************************************************
*********************************************************************************************************
*/

#include  <cpu.h>                                               /* CPU Configuration              (see Note #2b)        */
#include  <cpu_core.h>                                          /* CPU Core Library               (see Note #2a)        */

#include  <lib_def.h>                                           /* Standard        Defines        (see Note #3a)        */
#include  <lib_str.h>                                           /* Standard String Library        (see Note #3a)        */
#include  <lib_ascii.h>                                         /* Standard ASCII  Library        (see Note #3a)        */

#include  <http-c_cfg.h>
#include  "../../Common/http.h"
#include  "http-c_mem.h"


/*
*********************************************************************************************************
*********************************************************************************************************
*                                               MODULE
*
* Note(s) : (1) This main network protocol suite header file is protected from multiple pre-processor
*               inclusion through use of the HTTPc module present pre-processor macro definition.
*
*           (2) The following HTTPc-Task-module configuration value MUST be pre-#define'd in
*               'http-c.h' PRIOR to all other HTTPc modules that require the Task Layer configuration:
*
*                   HTTPc_TASK_MODULE_EN
*********************************************************************************************************
*********************************************************************************************************
*/

#ifndef  HTTPc_TASK_MODULE_PRESENT                              /* See Note #1.                                         */
#define  HTTPc_TASK_MODULE_PRESENT

#ifdef   HTTPc_TASK_MODULE_EN                                   /* See Note #2.                                         */


/*
*********************************************************************************************************
*********************************************************************************************************
*                                          FUNCTION PROTOTYPES
*********************************************************************************************************
*********************************************************************************************************
*/

void         HTTPcTask_Init                     (const  HTTPc_CFG          *p_cfg,
                                                 const  HTTP_TASK_CFG   *p_task_cfg,
                                                        HTTPc_ERR          *p_err);

void         HTTPcTask                          (       void               *p_data);

void         HTTPcTask_SetDly                   (       CPU_INT08U          dly_ms,
                                                        HTTPc_ERR          *p_err);
void         HTTPcTask_MsgQueue                 (       HTTPc_MSG_TYPE      type,
                                                        void               *p_data,
                                                        HTTPc_ERR          *p_err);

void         HTTPcTask_ConnAdd                  (       HTTPc_CONN         *p_conn);

void         HTTPcTask_ConnRemove               (       HTTPc_CONN         *p_conn);

#ifdef HTTPc_SIGNAL_TASK_MODULE_EN
void         HTTPcTask_ConnConnectSignalCreate  (       HTTPc_CONN         *p_conn,
                                                        HTTPc_ERR          *p_err);

void         HTTPcTask_ConnConnectSignalDel     (       HTTPc_CONN         *p_conn,
                                                        HTTPc_ERR          *p_err);

void         HTTPcTask_ConnCloseSignalCreate    (       HTTPc_CONN         *p_conn,
                                                        HTTPc_ERR          *p_err);

void         HTTPcTask_ConnCloseSignalDel       (       HTTPc_CONN         *p_conn,
                                                        HTTPc_ERR          *p_err);

void         HTTPcTask_TransDoneSignalCreate    (       HTTPc_CONN         *p_conn,
                                                        HTTPc_ERR          *p_err);

void         HTTPcTask_TransDoneSignalDel       (       HTTPc_CONN         *p_conn,
                                                        HTTPc_ERR          *p_err);

void         HTTPcTask_ConnConnectSignal        (       HTTPc_CONN         *p_conn,
                                                        HTTPc_ERR          *p_err);

void         HTTPcTask_ConnCloseSignal          (       HTTPc_CONN         *p_conn,
                                                        HTTPc_ERR          *p_err);

void         HTTPcTask_TransDoneSignal          (       HTTPc_CONN         *p_conn,
                                                        HTTPc_ERR          *p_err);

void         HTTPcTask_ConnConnectSignalWait    (       HTTPc_CONN         *p_conn,
                                                        HTTPc_ERR          *p_err);

void         HTTPcTask_ConnCloseSignalWait      (       HTTPc_CONN         *p_conn,
                                                        HTTPc_ERR          *p_err);

void         HTTPcTask_TransDoneSignalWait      (       HTTPc_CONN         *p_conn,
                                                        HTTPc_ERR          *p_err);

void         HTTPcTask_Wake                     (       HTTPc_CONN         *p_conn,
                                                        HTTPc_ERR          *p_err);
#endif


/*
*********************************************************************************************************
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*********************************************************************************************************
*/

#endif  /* HTTPc_TASK_MODULE_EN       */
#endif  /* HTTPc_TASK_MODULE_PRESENT  */
