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
*                                     HTTP CLIENT MEMORY LIBRARY
*
* Filename      : http-c_mem.h
* Version       : V3.00.01
* Programmer(s) : AL
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
*               inclusion through use of the HTTP memory module present pre-processor macro definition.
*********************************************************************************************************
*********************************************************************************************************
*/

#ifndef  HTTPc_MEM_PRESENT                                          /* See Note #1.                                         */
#define  HTTPc_MEM_PRESENT


/*
*********************************************************************************************************
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*********************************************************************************************************
*/

#include  "http-c.h"
#ifdef  HTTPc_WEBSOCK_MODULE_EN
#include  "http-c_websock.h"
#endif


/*
*********************************************************************************************************
*********************************************************************************************************
*                                             DATA TYPES
*********************************************************************************************************
*********************************************************************************************************
*/

typedef enum {
    HTTPc_MSG_TYPE_CONN_OPEN,
    HTTPc_MSG_TYPE_CONN_CLOSE,
    HTTPc_MSG_TYPE_REQ,
    HTTPc_MSG_TYPE_WEBSOCK_MSG,
} HTTPc_MSG_TYPE;

typedef struct httpc_task_msg {
    HTTPc_MSG_TYPE  Type;
    void           *DataPtr;
} HTTPc_TASK_MSG;


/*
*********************************************************************************************************
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*********************************************************************************************************
*/

void               HTTPc_Mem_TaskMsgPoolInit    (const  HTTPc_CFG           *p_cfg,
                                                        MEM_SEG             *p_seg,
                                                        HTTPc_ERR           *p_err);

HTTPc_TASK_MSG    *HTTPc_Mem_TaskMsgGet         (void);

void               HTTPc_Mem_TaskMsgRelease     (HTTPc_TASK_MSG      *p_msg);


#ifdef  HTTPc_WEBSOCK_MODULE_EN
void               HTTPc_Mem_WebSockReqPoolInit (const HTTPc_CFG           *p_cfg,
                                                       MEM_SEG             *p_seg,
                                                       HTTPc_ERR           *p_err);

HTTPc_WEBSOCK_REQ *HTTPc_Mem_WebSockReqGet      (void);

void               HTTPc_Mem_WebSockReqRelease  (HTTPc_WEBSOCK_REQ   *p_ws_req);
#endif


/*
*********************************************************************************************************
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*********************************************************************************************************
*/

#endif                                                          /* End of HTTPc memory module include.                  */

