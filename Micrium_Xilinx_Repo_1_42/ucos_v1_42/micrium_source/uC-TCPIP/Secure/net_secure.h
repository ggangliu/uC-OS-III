/*
*********************************************************************************************************
*                                             uC/TCP-IP
*                                      The Embedded TCP/IP Suite
*
*                         (c) Copyright 2004-2015; Micrium, Inc.; Weston, FL
*
*                  All rights reserved.  Protected by international copyright laws.
*
*                  uC/TCP-IP is provided in source form to registered licensees ONLY.  It is
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
*                                     NETWORK SECURITY PORT LAYER
*
*                                               uC/TCPIP
*
* Filename      : net_secure.h
* Version       : V3.03.01
* Programmer(s) : SL
*********************************************************************************************************
* Note(s)       : (1) Assumes the following versions (or more recent) of software modules are included in
*                     the project build :
*
*                     (a) Network Security Module (e.g. Mocana nanoSSL)
*                     (b) uC/Clk V3.09
*
*                     See also 'net.h  Note #1'.
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               MODULE
*
* Note(s) : (1) Network Security Manager module available ONLY for certain connection types :
*
*               (a) IPv4 Sockets
*                   (1) TCP/Stream Sockets
*
*           (2) The following secure-module-present configuration value MUST be pre-#define'd in
*               'net_cfg_net.h' PRIOR to all other network modules that require Network Security Layer
*               configuration (see 'net_cfg_net.h  NETWORK SECURITY MANAGER CONFIGURATION  Note #2b') :
*
*                   NET_SECURE_MODULE_PRESENT
*********************************************************************************************************
*/

#include "../Source/net_cfg_net.h"
#include "../Source/net_sock.h"



#ifndef  NET_SECURITY_MODULE_PRESENT
#define  NET_SECURITY_MODULE_PRESENT


/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               EXTERNS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               DEFINES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             DATA TYPES
*********************************************************************************************************
*/

typedef enum net_secure_cert_fmt {
    NET_SECURE_CERT_FMT_NONE = NET_SOCK_SECURE_CERT_KEY_FMT_NONE,
    NET_SECURE_CERT_FMT_PEM  = NET_SOCK_SECURE_CERT_KEY_FMT_PEM,
    NET_SECURE_CERT_FMT_DER  = NET_SOCK_SECURE_CERT_KEY_FMT_DER,
} NET_SECURE_CERT_FMT;


/*
*********************************************************************************************************
*                                          GLOBAL VARIABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/
#ifdef   NET_SECURE_MODULE_EN
                                                                            /* -------------- INIT FNCTS -------------- */
void                NetSecure_Init                  (       NET_ERR                       *p_err);

void                NetSecure_InitSession           (       NET_SOCK                      *p_sock,
                                                            NET_ERR                       *p_err);


                                                                            /* ------------ SOCK CFG FNCTS ------------ */
CPU_BOOLEAN         NetSecure_SockServerCertKeyBuf  (       NET_SOCK                      *p_sock,
                                                     const  void                          *p_buf_cert,
                                                            CPU_SIZE_T                     buf_cert_size,
                                                     const  void                          *p_buf_key,
                                                            CPU_SIZE_T                     buf_key_size,
                                                            NET_SOCK_SECURE_CERT_KEY_FMT   fmt,
                                                            CPU_BOOLEAN                    cert_chain,
                                                            NET_ERR                       *p_err);

#if 0
CPU_BOOLEAN         NetSecure_SockServerCertKeyFiles(       NET_SOCK                      *p_sock,
                                                     const  void                          *pfilename_cert,
                                                     const  void                          *pfilename_key,
                                                            NET_SECURE_CERT_FMT            fmt,
                                                            CPU_BOOLEAN                    cert_chain,
                                                            NET_ERR                       *p_err);
#endif


CPU_BOOLEAN         NetSecure_ClientCommonNameSet   (       NET_SOCK                      *p_sock,
                                                            CPU_CHAR                      *p_common_name,
                                                            NET_ERR                       *p_err);

CPU_BOOLEAN         NetSecure_ClientTrustCallBackSet(       NET_SOCK                      *p_sock,
                                                            NET_SOCK_SECURE_TRUST_FNCT     p_callback_fnct,
                                                            NET_ERR                       *p_err);



                                                                            /* ----------- SOCK HANDLER FNCTS --------- */
void                NetSecure_SockClose             (       NET_SOCK                      *p_sock,
                                                            NET_ERR                       *p_err);

void                NetSecure_SockCloseNotify       (       NET_SOCK                      *p_sock,
                                                            NET_ERR                       *p_err);

void                NetSecure_SockConn              (       NET_SOCK                      *p_sock,
                                                            NET_ERR                       *p_err);

void                NetSecure_SockAccept            (       NET_SOCK                      *p_sock_listen,
                                                            NET_SOCK                      *p_sock_accept,
                                                            NET_ERR                       *p_err);


NET_SOCK_RTN_CODE   NetSecure_SockRxDataHandler     (       NET_SOCK                      *p_sock,
                                                            void                          *p_data_buf,
                                                            CPU_INT16U                     data_buf_len,
                                                            NET_ERR                       *p_err);

#if (NET_SOCK_CFG_SEL_EN == DEF_ENABLED)
CPU_BOOLEAN         NetSecure_SockRxIsDataPending   (       NET_SOCK                      *p_sock,
                                                            NET_ERR                       *p_err);
#endif


NET_SOCK_RTN_CODE   NetSecure_SockTxDataHandler     (       NET_SOCK                      *p_sock,
                                                            void                          *p_data_buf,
                                                            CPU_INT16U                     data_buf_len,
                                                            NET_ERR                       *p_err);

void                NetSecure_SockDNS_NameSet       (       NET_SOCK                      *p_sock,
                                                            CPU_CHAR                      *p_dns_name,
                                                            NET_ERR                       *p_err);


                                                                            /* -------------- MGMT FNCTS -------------- */
void               *NetSecure_BlkGet                (       CPU_INT08U                     type,
                                                            CPU_SIZE_T                     size,
                                                            NET_ERR                       *p_err);

void                NetSecure_BlkFree               (       CPU_INT08U                     type,
                                                            void                          *p_buf,
                                                            NET_ERR                       *p_err);


void                NetSecure_TraceOut              (       CPU_CHAR                      *p_msg);



                                                                            /* -------------- API FNCTS --------------- */
CPU_BOOLEAN         NetSecure_CA_CertIntall         (const  void                          *p_ca_cert,
                                                            CPU_INT32U                     ca_cert_len,
                                                            NET_SECURE_CERT_FMT            fmt,
                                                            NET_ERR                       *p_err);
#endif /* NET_SECURE_MODULE_EN */

/*
*********************************************************************************************************
*                                              TRACING
*********************************************************************************************************
*/

#if 0
#define  SSL_TRACE                                         printf
#endif

                                                           /* Trace level, default to TRACE_LEVEL_OFF              */
#ifndef  TRACE_LEVEL_OFF
#define  TRACE_LEVEL_OFF                                   0
#endif

#ifndef  TRACE_LEVEL_INFO
#define  TRACE_LEVEL_INFO                                  1
#endif

#ifndef  TRACE_LEVEL_DBG
#define  TRACE_LEVEL_DBG                                   2
#endif

#ifndef  SSL_TRACE_LEVEL
#define  SSL_TRACE_LEVEL                                   TRACE_LEVEL_OFF
#endif


#if ((defined(SSL_TRACE))       && \
     (defined(SSL_TRACE_LEVEL)) && \
     (SSL_TRACE_LEVEL >= TRACE_LEVEL_INFO))

    #if (SSL_TRACE_LEVEL >= TRACE_LEVEL_DBG)
        #define  SSL_TRACE_DBG(msg)          SSL_TRACE  msg
    #else
        #define  SSL_TRACE_DBG(msg)
    #endif

    #define  SSL_TRACE_INFO(msg)             SSL_TRACE  msg

#else
    #define  SSL_TRACE_DBG(msg)
    #define  SSL_TRACE_INFO(msg)
#endif


/*
*********************************************************************************************************
*                                        CONFIGURATION ERRORS
*********************************************************************************************************
*/

#ifndef  NET_SECURE_CFG_EN
#error  "NET_SECURE_CFG_EN                         not #define'd in 'net_cfg.h'"
#error  "                                    [MUST be  DEF_DISABLED]           "
#error  "                                    [     ||  DEF_ENABLED ]           "

#elif  ((NET_SECURE_CFG_EN != DEF_DISABLED) && \
        (NET_SECURE_CFG_EN != DEF_ENABLED ))
#error  "NET_SECURE_CFG_EN                   illegally #define'd in 'net_cfg.h'"
#error  "                                    [MUST be  DEF_DISABLED]           "
#error  "                                    [     ||  DEF_ENABLED ]           "



#elif   (NET_SECURE_CFG_EN == DEF_ENABLED)





#ifndef NET_SECURE_CFG_MAX_NBR_SOCK_SERVER
#error  "NET_SECURE_CFG_MAX_NBR_SOCK_SERVER        not #define'd in 'net_cfg.h' "
#error  "                                    [MUST be  >= 0                    ]"
#error  "                                    [     &&  <= NET_SOCK_CFG_NBR_SOCK]"

#elif  (NET_SECURE_CFG_MAX_NBR_SOCK_SERVER > 0)

#ifndef  NET_SECURE_CFG_MAX_CERT_LEN
#error  "NET_SECURE_CFG_MAX_CERT_LEN               not #define'd in 'net_cfg.h'"
#error  "                                    [MUST be  > 0]                    "

#elif   (DEF_CHK_VAL_MIN(NET_SECURE_CFG_MAX_CERT_LEN, 1) != DEF_OK)
#error  "NET_SECURE_CFG_MAX_CERT_LEN         illegally #define'd in 'net_cfg.h'"
#error  "                                    [MUST be  > 0]                    "
#endif

#ifndef  NET_SECURE_CFG_MAX_KEY_LEN
#error  "NET_SECURE_CFG_MAX_KEY_LEN                not #define'd in 'net_cfg.h'"
#error  "                                    [MUST be  > 0]                    "

#elif   (DEF_CHK_VAL_MIN(NET_SECURE_CFG_MAX_KEY_LEN, 1) != DEF_OK)
#error  "NET_SECURE_CFG_MAX_KEY_LEN          illegally #define'd in 'net_cfg.h'"
#error  "                                    [MUST be  > 0]                    "
#endif

#endif


#ifndef  NET_SECURE_CFG_MAX_NBR_SOCK_CLIENT
#error  "NET_SECURE_CFG_MAX_NBR_SOCK_CLIENT        not #define'd in 'net_cfg.h' "
#error  "                                    [MUST be  >= 0                    ]"
#error  "                                    [     &&  <= NET_TCP_CFG_NBR_CONN ]"

#elif  (NET_SECURE_CFG_MAX_NBR_SOCK_CLIENT > 0)

#ifndef  NET_SECURE_CFG_MAX_NBR_CA
#error  "NET_SECURE_CFG_MAX_NBR_CA                 not #define'd in 'net_cfg.h'"
#error  "                                    [MUST be  = 1]                    "

#elif   (NET_SECURE_CFG_MAX_NBR_CA != 1)
#error  "NET_SECURE_CFG_MAX_NBR_CA           illegally #define'd in 'net_cfg.h'"
#error  "                                    [MUST be  = 1]                    "
#endif


#ifndef  NET_SECURE_CFG_MAX_CA_CERT_LEN
#error  "NET_SECURE_CFG_MAX_CA_CERT_LEN            not #define'd in 'net_cfg.h'"
#error  "                                    [MUST be  > 0]                    "

#elif   (DEF_CHK_VAL_MIN(NET_SECURE_CFG_MAX_CA_CERT_LEN, 1) != DEF_OK)
#error  "NET_SECURE_CFG_MAX_CA_CERT_LEN      illegally #define'd in 'net_cfg.h'"
#error  "                                    [MUST be  > 0]                    "
#endif

#endif



#if (NET_SECURE_CFG_MAX_NBR_SOCK_SERVER + \
     NET_SECURE_CFG_MAX_NBR_SOCK_CLIENT > NET_SOCK_CFG_SOCK_NBR_TCP)
#error  "NET_SECURE_CFG_MAX_NBR_SOCK_SERVER and/or                              "
#error  "NET_SECURE_CFG_MAX_NBR_SOCK_CLIENT  illegally #define'd in 'net_cfg.h' "
#error  "NET_SECURE_CFG_MAX_NBR_SOCK_SERVER + NET_SECURE_CFG_MAX_NBR_SOCK_CLIENT"
#error  "                                    [MUST be  <= NET_TCP_CFG_NBR_CONN ]"
#endif


#ifndef  NET_SECURE_CFG_MAX_NBR_CA
#error  "NET_SECURE_CFG_MAX_NBR_CA                 not #define'd in 'net_cfg.h'"
#error  "                                    [MUST be   define'd in 'net_cfg.h]"
#endif


#endif


#endif  /* NET_SECURITY_MODULE_PRESENT */

