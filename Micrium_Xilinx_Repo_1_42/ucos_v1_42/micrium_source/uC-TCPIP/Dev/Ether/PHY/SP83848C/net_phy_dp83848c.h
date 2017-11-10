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
*                                        NETWORK PHYSICAL LAYER
*
*                                        DP83848C ETHERNET PHY
*
* Filename      : net_phy_dp83848c.h
* Version       : V3.03.01.00
* Programmer(s) : ahfai
*********************************************************************************************************
* Note(s)       : (1) Assumes uC/TCP-IP V2.05 (or more recent version) is included in the project build.
*
*                 (2) The (R)MII interface port is assumed to be part of the host EMAC.  Therefore, (R)MII
*                     reads/writes MUST be performed through the network device API interface via calls to
*                     function pointers 'Phy_RegRd()' & 'Phy_RegWr()'.
*
*                 (3) Interrupt support is Phy specific, therefore the generic Phy driver does NOT support
*                     interrupts.  However, interrupt support is easily added to the generic Phy driver &
*                     thus the ISR handler has been prototyped and & populated within the function pointer
*                     structure for example purposes.
*
*                 (4) Does NOT support 1000Mbps Phy.
*********************************************************************************************************
*/



/*
*********************************************************************************************************
*                                               MODULE
*********************************************************************************************************
*/

#ifndef  NET_PHY_DP83848C_MODULE_PRESENT
#define  NET_PHY_DP83848C_MODULE_PRESENT


#include  <IF/net_if.h>
#include  <IF/net_if_ether.h>
#ifdef  NET_IF_ETHER_MODULE_EN


/*
*********************************************************************************************************
*                                          GLOBAL VARIABLES
*********************************************************************************************************
*/

extern  const  NET_PHY_API_ETHER   NetPhy_API_DP83848C;


#endif  /* NET_PHY_DP83848C_MODULE_PRESENT  */
#endif  /* NET_IF_ETHER_MODULE_EN           */

