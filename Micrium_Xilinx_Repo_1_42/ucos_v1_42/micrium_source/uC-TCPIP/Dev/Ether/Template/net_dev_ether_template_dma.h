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
*                                        NETWORK DEVICE DRIVER
*
*                                        ETHERNET DMA TEMPLATE
*
* Filename      : net_dev_ether_template_dma.h
* Version       : V3.03.01.00
* Programmer(s) : EHS
*                 FGK
*********************************************************************************************************
* Note(s)       : (1) Assumes uC/TCP-IP V2.20.00 (or more recent version) is included in the project build.
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*********************************************************************************************************
*                                               MODULE
*********************************************************************************************************
*********************************************************************************************************
*/

#ifndef  NET_DEV_TEMPLATE_ETHER_DMA_MODULE_PRESENT
#define  NET_DEV_TEMPLATE_ETHER_DMA_MODULE_PRESENT

#include  <IF/net_if_ether.h>
#ifdef   NET_IF_ETHER_MODULE_EN

/*
*********************************************************************************************************
*********************************************************************************************************
*                                          GLOBAL VARIABLES
*********************************************************************************************************
*********************************************************************************************************
*/

extern  const  NET_DEV_API_ETHER  NetDev_API_TemplateEtherDMA;


/*
*********************************************************************************************************
*********************************************************************************************************
*                                        CONFIGURATION ERRORS
*********************************************************************************************************
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*********************************************************************************************************
*/
#endif  /* NET_IF_ETHER_MODULE_EN                       */
#endif  /* NET_DEV_TEMPLATE_ETHER_DMA_MODULE_PRESENT */

