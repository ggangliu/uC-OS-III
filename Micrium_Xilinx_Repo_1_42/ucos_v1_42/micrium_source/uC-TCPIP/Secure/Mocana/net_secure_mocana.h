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
*                                            Mocana nanoSSL
*
* Filename      : net_secure_mocana.h
* Version       : V3.03.01
* Programmer(s) : SL
*********************************************************************************************************
* Note(s)       : (1) Assumes the following versions (or more recent) of software modules are included in
*                     the project build :
*
*                     (a) Mocana nanoSSl v5.5 or higher
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

#include "../net_secure.h"
#include "../../Source/net_cfg_net.h"


#ifndef  NET_SECURE_MOCANA_MODULE_PRESENT
#define  NET_SECURE_MOCANA_MODULE_PRESENT


/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/
                                                                /* Mocana includes.                                     */
#include  <common/mtypes.h>
#include  <common/moptions.h>
#include  <common/mtypes.h>
#include  <common/mdefs.h>
#include  <common/merrors.h>
#include  <common/mrtos.h>
#include  <common/mtcp.h>
#include  <common/mocana.h>
#include  <common/debug_console.h>
#include  <common/mstdlib.h>
#include  <crypto/hw_accel.h>
#include  <crypto/ca_mgmt.h>
#include  <common/sizedbuffer.h>
#include  <crypto/cert_store.h>
#include  <ssl/ssl.h>


/*
*********************************************************************************************************
*                                               DEFINES
*********************************************************************************************************
*/

#define  NET_SECURE_MEM_BLK_TYPE_MOCANA                 0u
#define  NET_SECURE_MEM_BLK_TYPE_SSL_SESSION            1u
#define  NET_SECURE_MEM_BLK_TYPE_SERVER_DESC            2u
#define  NET_SECURE_MEM_BLK_TYPE_CLIENT_DESC            3u



/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

CPU_BOOLEAN         NetSecure_CA_CertIntall(const  void                   *p_ca_cert,
                                                   CPU_INT32U              ca_cert_len,
                                                   NET_SECURE_CERT_FMT     fmt,
                                                   NET_ERR                *p_err);

CPU_BOOLEAN         NetSecure_DN_Print      (      CPU_CHAR               *p_buf,
                                                   CPU_INT32U              buf_len,
                                                   certDistinguishedName  *p_dn);


/*
*********************************************************************************************************
*                                        CONFIGURATION ERRORS
*********************************************************************************************************
*/



#endif  /* NET_SECURE_MOCANA_MODULE_PRESENT */

