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
*                                   NETWORK FILE SYSTEM PORT LAYER
*
*                                             uC/FS V4.xx
*
* Filename      : net_fs_v4.h
* Version       : V3.03.01.00
* Programmer(s) : FBJ
*                 SL
*                 BAN
*                 AA
*********************************************************************************************************
* Note(s)       : (1) Assumes the following versions (or more recent) of software modules are included in
*                     the project build :
*
*                     (a) uC/FS  V4.03
*                     (b) uC/Clk V3.09          if uC/FS V4.04 (or more recent) is included
*
*                 (2) Should be compatible with the following TCP/IP application versions (or more recent):
*
*                     (a) uC/FTPc  V1.93.01
*                     (b) uC/FTPs  V1.95.02
*                     (c) uC/HTTPs V1.98.00
*                     (d) uC/TFTPc V1.92.01
*                     (e) uC/TFTPs V1.91.02
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                               MODULE
*********************************************************************************************************
*/

#ifndef  NET_FS_V4_MODULE_PRESENT
#define  NET_FS_V4_MODULE_PRESENT


/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include  <FS/net_fs.h>
#include  <fs_inc.h>


/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/

#define  NET_FS_FILE_BUF_EN     DEF_ENABLED


/*
*********************************************************************************************************
*                                          GLOBAL VARIABLES
*********************************************************************************************************
*/

extern  const  NET_FS_API  NetFS_API_FS_V4;


/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                        CONFIGURATION ERRORS
*********************************************************************************************************
*/

#if (FS_CFG_WORKING_DIR_EN != DEF_ENABLED )
    #error  "FS_CFG_WORKING_DIR_EN      illegally #define'd in 'fs_cfg.h'"
    #error  "                           [MUST be  DEF_ENABLED]           "
#endif


                                                                /* ---------------- NET_FS_FILE_BUF_EN ---------------- */
#ifndef  NET_FS_FILE_BUF_EN
#error  "NET_FS_FILE_BUF_EN                           not #define'd in 'net_fs_v4.h'            "
#error  "                                       [MUST be  DEF_DISABLED]                         "
#error  "                                       [     ||  DEF_ENABLED ]                         "

#elif  ((NET_FS_FILE_BUF_EN != DEF_DISABLED) && \
        (NET_FS_FILE_BUF_EN != DEF_ENABLED ))
#error  "NET_FS_FILE_BUF_EN                     illegally #define'd in 'net_fs_v4.h'            "
#error  "                                       [MUST be  DEF_DISABLED]                         "
#error  "                                       [     ||  DEF_ENABLED ]                         "
#endif


/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif                                                          /* End of net fs V4 module include.                     */


