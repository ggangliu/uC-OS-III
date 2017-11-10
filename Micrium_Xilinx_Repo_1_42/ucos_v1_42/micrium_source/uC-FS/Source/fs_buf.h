/*
*********************************************************************************************************
*                                             uC/FS V4
*                                     The Embedded File System
*
*                         (c) Copyright 2008-2014; Micrium, Inc.; Weston, FL
*
*                  All rights reserved.  Protected by international copyright laws.
*
*                  uC/FS is provided in source form to registered licensees ONLY.  It is
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
*                                    FILE SYSTEM BUFFER MANAGEMENT
*
* Filename      : fs_buf.h
* Version       : v4.07.00
* Programmer(s) : BAN
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                               MODULE
*********************************************************************************************************
*/

#ifndef  FS_BUF_H
#define  FS_BUF_H


/*
*********************************************************************************************************
*                                          INCLUDE FILES
*********************************************************************************************************
*/

#include  <cpu.h>
#include  "fs_cfg_fs.h"
#include  "fs_err.h"
#include  "fs_type.h"


/*
*********************************************************************************************************
*                                               EXTERNS
*********************************************************************************************************
*/

#ifdef   FS_BUF_MODULE
#define  FS_BUF_EXT
#else
#define  FS_BUF_EXT  extern
#endif


/*
*********************************************************************************************************
*                                               DEFINES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                         BUFFER FLAG DEFINES
*********************************************************************************************************
*/

#define  FS_BUF_STATE_NONE                                0u
#define  FS_BUF_STATE_USED                                1u
#define  FS_BUF_STATE_DIRTY                               2u


/*
*********************************************************************************************************
*                                               MACRO'S
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             DATA TYPES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                    FILE SYSTEM BUFFER DATA TYPE
*********************************************************************************************************
*/

struct  fs_buf {
    FS_SEC_SIZE   Size;                                         /* Size cfg'd @ init.                                   */

    FS_STATE      State;                                        /* Buf state.                                           */
    FS_SEC_NBR    Start;                                        /* Sec nbr.                                             */
    FS_FLAGS      SecType;                                      /* Sector type.                                         */
    void         *DataPtr;                                      /* Ptr to buf data.                                     */
    FS_VOL       *VolPtr;                                       /* Ptr to vol.                                          */
};


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

void     FSBuf_ModuleInit(FS_QTY        buf_cnt,                /* Initialize buffer module.                            */
                          CPU_SIZE_T    buf_size,
                          FS_ERR       *p_err);


FS_BUF  *FSBuf_Get       (FS_VOL       *p_vol);                 /* Allocate & initialize a buffer.                      */

void     FSBuf_Free      (FS_BUF       *p_buf);                 /* Free a buffer.                                       */


void     FSBuf_Flush     (FS_BUF       *p_buf,                  /* Flush buffer.                                        */
                          FS_ERR       *p_err);

#if (FS_CFG_RD_ONLY_EN == DEF_DISABLED)
void     FSBuf_MarkDirty (FS_BUF       *p_buf,                  /* Mark buffer as dirty.                                */
                          FS_ERR       *p_err);
#endif

void     FSBuf_Set       (FS_BUF       *p_buf,                  /* Set buffer sector.                                   */
                          FS_SEC_NBR    start,
                          FS_FLAGS      sec_type,
                          CPU_BOOLEAN   rd,
                          FS_ERR       *p_err);


/*
*********************************************************************************************************
*                                        CONFIGURATION ERRORS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif
