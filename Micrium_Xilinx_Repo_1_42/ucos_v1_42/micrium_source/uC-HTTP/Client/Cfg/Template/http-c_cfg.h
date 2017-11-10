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
*                                   HTTP CLIENT CONFIGURATION FILE
*
*                                              TEMPLATE
*
* Filename      : http-c_cfg.h
* Version       : V3.00.01
* Programmer(s) : MM
*                 AL
*********************************************************************************************************
* Note(s)       : (1) Assumes the following versions (or more recent) of software modules are included in
*                     the project build :
*
*                       (a) uC/CPU    V1.29.02
*                       (b) uC/LIB    V1.38.00
*                       (c) uC/Common V1.00.00
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
*                                           INCLUDE FILES
*********************************************************************************************************
*********************************************************************************************************
*/

#include  <Common/http.h>
#include  <Client/Source/http-c_type.h>


/*
*********************************************************************************************************
*********************************************************************************************************
*                                               MODULE
*********************************************************************************************************
*********************************************************************************************************
*/

#ifndef  HTTPc_CFG_MODULE_PRESENT
#define  HTTPc_CFG_MODULE_PRESENT


/*
*********************************************************************************************************
*********************************************************************************************************
*                                      COMPILE-TIME CONFIGURATION
*********************************************************************************************************
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                   HTTP ARGUMENT CHECK CONFIGURATION
*
* Note(s) : (1) Configure HTTPc_CFG_ARG_CHK_EXT_EN to enable/disable the HTTP client external argument
*               check feature :
*
*               (a) When ENABLED,  ALL arguments received from any port interface provided by the developer
*                   are checked/validated.
*
*               (b) When DISABLED, NO  arguments received from any port interface provided by the developer
*                   are checked/validated.
*********************************************************************************************************
*/

#define  HTTPc_CFG_ARG_CHK_EXT_EN                 DEF_ENABLED   /* See Note #1.                                         */


/*
*********************************************************************************************************
*                                    HTTP CLIENT TASK CONFIGURATION
*
* Note(s) : (1) Configure HTTPc_CFG_MODE_ASYNC_TASK_EN to enable/disable HTTP client task.
*               (a) DEF_DISABLED : No HTTP client task will be created to process the HTTP requests.
*                                  The Blocking HTTPc API will be enabled.
*
*               (b) DEF_ENABLED  : An HTTP client task will be created to process all the HTTP requests.
*                                  The Non-Blocking HTTPc API will be enabled. Therefore, multiple
*                                  connections can be handle by the task simultaneously.
*
*           (2) Configure HTTPc_CFG_MODE_BLOCK_EN to enable/disable the blocking option when the
*               asynchronous HTTPc Task is enabled.
*********************************************************************************************************
*/

#define  HTTPc_CFG_MODE_ASYNC_TASK_EN           DEF_ENABLED     /* See Note #1.                                         */

#define  HTTPc_CFG_MODE_BLOCK_EN                DEF_ENABLED     /* See Note #2.                                         */


/*
*********************************************************************************************************
*                              HTTP CLIENT PERSISTENT CONNECTION CONFIGURATION
*
* Note(s) : (1) Configure HTTPc_CFG_PERSISTENT_EN to enable/disable Persistent Connection support.
*********************************************************************************************************
*/

#define  HTTPc_CFG_PERSISTENT_EN                DEF_ENABLED     /* See Note #1.                                         */


/*
*********************************************************************************************************
*                                HTTP CLIENT CHUNKED TRANSFER CONFIGURATION
*
* Note(s) : (1) Configure HTTPc_CFG_CHUNK_TX_EN to enable/disable Chunked Transfer support in Transmission.
*
*           (2) Chunked Transfer in Reception is always enabled.
*********************************************************************************************************
*/

#define  HTTPc_CFG_CHUNK_TX_EN                  DEF_ENABLED     /* See Note #1.                                         */


/*
*********************************************************************************************************
*                                 HTTP CLIENT QUERY STRING CONFIGURATION
*
* Note(s) : (1) Configure HTTPc_CFG_QUERY_STR_EN to enable/disable Query String support in URL.
*********************************************************************************************************
*/

#define  HTTPc_CFG_QUERY_STR_EN                 DEF_ENABLED     /* See Note #1.                                         */


/*
*********************************************************************************************************
*                                HTTP CLIENT HEADER FIELD CONFIGURATION
*
* Note(s) : (1) Configure HTTPc_CFG_HDR_RX_EN to enable/disable header field processing in reception
*               (i.e for headers received in the HTTP response.
*
*           (2) Configure HTTPc_CFG_HDR_TX_EN to enable/disable header field processing in transmission
*               (i.e for headers to include in the HTTP request.
*********************************************************************************************************
*/

#define  HTTPc_CFG_HDR_RX_EN                    DEF_ENABLED     /* Configure Header feature in RX (see Note #1):        */


#define  HTTPc_CFG_HDR_TX_EN                    DEF_ENABLED     /* Configure Header feature in TX (see Note #2):        */


/*
*********************************************************************************************************
*                                     HTTP CLIENT FORM CONFIGURATION
*
* Note(s) : (1) Configure HTTPc_CFG_FORM_EN to enable/disable HTTP form creation source code.
*********************************************************************************************************
*/

#define  HTTPc_CFG_FORM_EN                      DEF_ENABLED     /* See Note #1.                                         */


/*
*********************************************************************************************************
*                                   HTTP CLIENT USER DATA CONFIGURATION
*
* Note(s) : (1) Configure HTTPc_CFG_USER_DATA_EN         to enable/disable user data pointer in HTTPc_CONN
*                                                        and HTTPc_REQ structure.
*********************************************************************************************************
*/

#define  HTTPc_CFG_USER_DATA_EN                 DEF_ENABLED     /* See Note #1.                                         */


/*
*********************************************************************************************************
*                                   HTTP CLIENT WEBSOCKET CONFIGURATION
*
* Note(s) : (1) Configure HTTPc_CFG_WEBSOCKET_EN        to enable/disable the Websocket feature.
*********************************************************************************************************
*/

#define  HTTPc_CFG_WEBSOCKET_EN                 DEF_ENABLED     /* See Note #1.                                         */


/*
*********************************************************************************************************
*********************************************************************************************************
*                                      RUN-TIME CONFIGURATION
*********************************************************************************************************
*********************************************************************************************************
*/

extern  const  HTTP_TASK_CFG   HTTPc_TaskCfg;
extern  const  HTTPc_CFG       HTTPc_Cfg;


/* =============================================== END =============================================== */
#endif  /* HTTPc_CFG_MODULE_PRESENT */
