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
*                                          NETWORK IGMP LAYER
*                                 (INTERNET GROUP MANAGEMENT PROTOCOL)
*
* Filename      : net_igmp.h
* Version       : V3.03.01
* Programmer(s) : SR
*********************************************************************************************************
* Note(s)       : (1) Internet Group Management Protocol ONLY required for network interfaces that require
*                     reception of IP class-D (multicast) packets (see RFC #1112, Section 3 'Levels of
*                     Conformance : Level 2').
*
*                     (a) IGMP is NOT required for the transmission of IP class-D (multicast) packets
*                         (see RFC #1112, Section 3 'Levels of Conformance : Level 1').
*
*                 (2) Supports Internet Group Management Protocol version 1, as described in RFC #1112
*                     with the following restrictions/constraints :
*
*                     (a) Only one socket may receive datagrams for a specific host group address & port
*                         number at any given time.
*
*                         See also 'net_sock.c  Note #1e'.
*
*                     (b) Since sockets do NOT automatically leave IGMP host groups when closed,
*                         it is the application's responsibility to leave each host group once it is
*                         no longer needed by the application.
*
*                     (c) Transmission of IGMP Query Messages NOT currently supported. #### NET-820
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*********************************************************************************************************
*/

#include  "../../Source/net_cfg_net.h"
#include  "../../Source/net_type.h"
#include  "../../Source/net_tmr.h"
#include  <lib_math.h>


/*
*********************************************************************************************************
*********************************************************************************************************
*                                               MODULE
*
* Note(s) : (1) IGMP Layer module is required only for IP multicast reception & IGMP group management
*               (see 'net_igmp.h  Note #1').
*
*           (2) The following IGMP-module-present configuration value MUST be pre-#define'd
*               in 'net_cfg_net.h' PRIOR to all other network modules that require IGMP Layer
*               configuration (see 'net_cfg_net.h  IGMP LAYER CONFIGURATION  Note #2b') :
*
*                   NET_IGMP_MODULE_EN
*********************************************************************************************************
*********************************************************************************************************
*/

#ifndef  NET_IGMP_MODULE_PRESENT
#define  NET_IGMP_MODULE_PRESENT


#ifdef   NET_IGMP_MODULE_EN                                /* See Note #2.                                         */


/*
*********************************************************************************************************
*********************************************************************************************************
*                                               EXTERNS
*********************************************************************************************************
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*********************************************************************************************************
*                                               DEFINES
*********************************************************************************************************
*********************************************************************************************************
*/

#define  NET_IGMP_HOST_GRP_NBR_MIN                         1
#define  NET_IGMP_HOST_GRP_NBR_MAX       DEF_INT_16U_MAX_VAL    /* See Note #1.                                         */



/*
*********************************************************************************************************
*********************************************************************************************************
*                                             DATA TYPES
*********************************************************************************************************
*********************************************************************************************************
*/



/*
*********************************************************************************************************
*********************************************************************************************************
*                                          GLOBAL VARIABLES
*********************************************************************************************************
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             PUBLIC API
*********************************************************************************************************
*/

                                                                    /* ------------- GRP MEMBERSHIP FNCTS ------------- */
CPU_BOOLEAN  NetIGMP_HostGrpJoin        (NET_IF_NBR      if_nbr,
                                         NET_IPv4_ADDR   addr_grp,
                                         NET_ERR        *p_err);

CPU_BOOLEAN  NetIGMP_HostGrpJoinHandler (NET_IF_NBR      if_nbr,
                                         NET_IPv4_ADDR   addr_grp,
                                         NET_ERR        *p_err);


CPU_BOOLEAN  NetIGMP_HostGrpLeave       (NET_IF_NBR      if_nbr,
                                         NET_IPv4_ADDR   addr_grp,
                                         NET_ERR        *p_err);

CPU_BOOLEAN  NetIGMP_HostGrpLeaveHandler(NET_IF_NBR      if_nbr,
                                         NET_IPv4_ADDR   addr_grp,
                                         NET_ERR        *p_err);


CPU_BOOLEAN  NetIGMP_IsGrpJoinedOnIF    (NET_IF_NBR      if_nbr,
                                         NET_IPv4_ADDR   addr_grp);


/*
*********************************************************************************************************
*                                         INTERNAL FUNCTIONS
*********************************************************************************************************
*/

void         NetIGMP_Init               (void);

                                                                    /* ------------------- RX FNCTS ------------------- */
void         NetIGMP_Rx                 (NET_BUF        *p_buf,
                                         NET_ERR        *p_err);


/*
*********************************************************************************************************
*********************************************************************************************************
*                                        CONFIGURATION ERRORS
*********************************************************************************************************
*********************************************************************************************************
*/

#ifndef  NET_MCAST_CFG_HOST_GRP_NBR_MAX
#error  "NET_MCAST_CFG_HOST_GRP_NBR_MAX        not #define'd in 'net_cfg.h'     "
#error  "                               [MUST be  >= NET_IGMP_HOST_GRP_NBR_MIN]"
#error  "                               [     &&  <= NET_IGMP_HOST_GRP_NBR_MAX]"

#elif   (DEF_CHK_VAL(NET_MCAST_CFG_HOST_GRP_NBR_MAX,      \
                     NET_IGMP_HOST_GRP_NBR_MIN,          \
                     NET_IGMP_HOST_GRP_NBR_MAX) != DEF_OK)
#error  "NET_MCAST_CFG_HOST_GRP_NBR_MAX  illegally #define'd in 'net_cfg.h'     "
#error  "                               [MUST be  >= NET_IGMP_HOST_GRP_NBR_MIN]"
#error  "                               [     &&  <= NET_IGMP_HOST_GRP_NBR_MAX]"
#endif


/*
*********************************************************************************************************
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*********************************************************************************************************
*/

#endif /* NET_IGMP_MODULE_EN      */
#endif /* NET_IGMP_MODULE_PRESENT */

