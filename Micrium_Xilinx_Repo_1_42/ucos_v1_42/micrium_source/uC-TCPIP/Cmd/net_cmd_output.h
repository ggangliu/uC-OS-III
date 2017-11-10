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
*                               NETWORK SHELL COMMAND OUTPUT UTILITIES
*
* Filename      : net_cmd_output.h
* Version       : V3.03.01
* Programmer(s) : AA
*********************************************************************************************************
* Note(s)       : (1) Assumes the following versions (or more recent) of software modules are included in
*                     the project build :
*
*                     (a) uC/TCP-IP V3.01.00
*                     (b) uC/OS-II  V2.90.00 or
*                         uC/OS-III V3.03.01
*                     (c) uC/Shell  V1.03.01
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               MODULE
*********************************************************************************************************
*/

#ifndef  NET_CMD_OUTPUT_MODULE_PRESENT
#define  NET_CMD_OUTPUT_MODULE_PRESENT


/*
*********************************************************************************************************
*                                            INCLUDE FILES
*
* Note(s) : (1) The following common software files are located in the following directories :
*
*               (a) \<Custom Library Directory>\lib*.*
*
*               (b) (1) \<CPU-Compiler Directory>\cpu_def.h
*
*                   (2) \<CPU-Compiler Directory>\<cpu>\<compiler>\cpu*.*
*
*                   where
*                   <Custom Library Directory>      directory path for custom   library      software
*                   <CPU-Compiler Directory>        directory path for common   CPU-compiler software
*                   <cpu>                           directory name for specific processor (CPU)
*                   <compiler>                      directory name for specific compiler
*
*           (2)
*
*           (3) NO compiler-supplied standard library functions SHOULD be used.
*********************************************************************************************************
*/

#include <cpu.h>
#include <Source/shell.h>
#include "../Source/net_err.h"


typedef  enum  net_cmd_output_fmt {
    NET_CMD_OUTPUT_FMT_STRING,
    NET_CMD_OUTPUT_FMT_HEX
} NET_CMD_OUTPUT_FMT;


/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/
CPU_INT16S  NetCmd_OutputBeginning     (SHELL_OUT_FNCT       out_fnct,
                                        SHELL_CMD_PARAM     *p_cmd_param);

CPU_INT16S  NetCmd_OutputEnd           (SHELL_OUT_FNCT       out_fnct,
                                        SHELL_CMD_PARAM     *p_cmd_param);

CPU_INT16S  NetCmd_OutputCmdTbl        (SHELL_CMD           *p_cmd_tbl,
                                        SHELL_OUT_FNCT       out_fnct,
                                        SHELL_CMD_PARAM     *p_cmd_param);

CPU_INT16S  NetCmd_OutputNotImplemented(SHELL_OUT_FNCT       out_fnct,
                                        SHELL_CMD_PARAM     *p_cmd_param);

CPU_INT16S  NetCmd_OutputCmdArgInvalid (SHELL_OUT_FNCT       out_fnct,
                                        SHELL_CMD_PARAM     *p_cmd_param);

CPU_INT16S  NetCmd_OutputError         (CPU_CHAR            *p_error,
                                        SHELL_OUT_FNCT       out_fnct,
                                        SHELL_CMD_PARAM     *p_cmd_param);

CPU_INT16S  NetCmd_OutputErrorNetNbr   (NET_ERR              err,
                                        SHELL_OUT_FNCT       out_fnct,
                                        SHELL_CMD_PARAM     *p_cmd_param);

CPU_INT16S  NetCmd_OutputSuccess       (SHELL_OUT_FNCT       out_fnct,
                                        SHELL_CMD_PARAM     *p_cmd_param);

CPU_INT16S  NetCmd_OutputInt32U        (CPU_INT32U           nbr,
                                        SHELL_OUT_FNCT       out_fnct,
                                        SHELL_CMD_PARAM     *p_cmd_param);

CPU_INT16S  NetCmd_OutputSockID        (CPU_INT16S           sock_id,
                                        SHELL_OUT_FNCT       out_fnct,
                                        SHELL_CMD_PARAM     *p_cmd_param);


CPU_INT16S  NetCmd_OutputMsg           (CPU_CHAR            *p_msg,
                                        CPU_BOOLEAN          new_line_start,
                                        CPU_BOOLEAN          new_line_end,
                                        CPU_BOOLEAN          tab_start,
                                        SHELL_OUT_FNCT       out_fnct,
                                        SHELL_CMD_PARAM     *p_cmd_param);

CPU_INT16S  NetCmd_OutputData          (CPU_INT08U          *p_buf,
                                        CPU_INT16U           len,
                                        NET_CMD_OUTPUT_FMT   out_fmt,
                                        SHELL_OUT_FNCT       out_fnct,
                                        SHELL_CMD_PARAM     *p_cmd_param);


/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif
