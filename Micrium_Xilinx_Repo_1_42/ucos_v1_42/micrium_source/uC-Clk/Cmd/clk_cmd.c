/*
*********************************************************************************************************
*                                               uC/Clk
*                                             Clock module
*
*                      (c) Copyright 2004-2014; Micrium, Inc.; Weston, FL
*
*          All rights reserved.  Protected by international copyright laws.
*
*          uC/Clk is provided in source form to registered licensees ONLY.  It is
*          illegal to distribute this source code to any third party unless you receive
*          written permission by an authorized Micrium representative.  Knowledge of
*          the source code may NOT be used to develop a similar product.
*
*          Please help us continue to provide the Embedded community with the finest
*          software available.  Your honesty is greatly appreciated.
*
*          You can find our product's user manual, API reference, release notes and
*          more information at: https://doc.micrium.com
*
*          You can contact us at: www.micrium.com
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                          CLOCK / CALENDAR
*
* Filename      : clk_cmd.c
* Version       : V3.10.00
* Programmer(s) : AL
*                 AOP
*********************************************************************************************************
* Note(s)       : (1) Assumes the following versions (or more recent) of software modules are included in
*                     the project build :
*
*                     (a) uC/CPU    V1.30
*                     (b) uC/OS-II  V2.90 or
*                         uC/OS-III V3.03
*                     (c) uC/Shell  V1.03
*********************************************************************************************************
*/


/*
*********************************************************************************************************
                                             INCLUDE FILES
*********************************************************************************************************
*/

#define  MICRIUM_SOURCE
#define  CLK_CMD_MODULE

#include  "clk_cmd.h"
#include  "../Source/clk.h"

#include  <Source/shell.h>


/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/

#define  CLK_CMD_ARG_BEGIN                                     ASCII_CHAR_HYPHEN_MINUS
#define  CLK_CMD_ARG_TIME_TYPE                                 ASCII_CHAR_LATIN_LOWER_T

#define  CLK_CMD_NBR_MIN_PER_HR                                60u
#define  CLK_CMD_NBR_SEC_PER_MIN                               60u


/*
*********************************************************************************************************
*                                           LOCAL CONSTANTS
*********************************************************************************************************
*/

#define  CLK_CMD_TBL_NAME                                    ("clk")

#define  CLK_CMD_NAME_HELP                                   ("clk_help")
#define  CLK_CMD_NAME_SET                                    ("clk_set")
#define  CLK_CMD_NAME_GET                                    ("clk_get")

#define  CLK_CMD_HELP                                        ("help")
#define  CLK_CMD_HELP_SHORT                                  ("h")

#define  CLK_CMD_FORMAT_DATETIME                             ("datetime")
#define  CLK_CMD_FORMAT_NTP                                  ("ntp")
#define  CLK_CMD_FORMAT_UNIX                                 ("unix")

#define  CLK_CMD_FORMAT_DATETIME_SHORT                       ("d")
#define  CLK_CMD_FORMAT_NTP_SHORT                            ("n")
#define  CLK_CMD_FORMAT_UNIX_SHORT                           ("u")


#define  CLK_CMD_OUTPUT_CMD_LIST                             ("Command List: ")
#define  CLK_CMD_OUTPUT_ERR                                  ("Error: ")
#define  CLK_CMD_OUTPUT_SUCCESS                              ("Completed successfully")
#define  CLK_CMD_OUTPUT_TABULATION                           ("\t")

#define  CLK_CMD_OUTPUT_ERR_CMD_ARG_INVALID                  ("Invalid Arguments")
#define  CLK_CMD_OUTPUT_ERR_CMD_NOT_IMPLEMENTED              ("This command is not yet implemented")
#define  CLK_CMD_OUTPUT_ERR_CONV_DISABLED                    ("CLK_CFG_STR_CONV_EN is not enabled. Formatting not available.")
#define  CLK_CMD_OUTPUT_ERR_CMD_INTERNAL_ERR                 ("Clk Internal Error. Date & Time cannot be converted.")

#define  CLK_CMD_HELP_SET                                    ("usage: clk_set [VALUE] {FORMAT}\r\n")

#define  CLK_CMD_HELP_GET                                    ("usage: clk_get {FORMAT}\r\n")

#define  CLK_CMD_HELP_VALUE                                  ("where VALUE is:\r\n"                                                 \
                                                              "  YYYY-MM-DD {HH:MM:SS {UTC+/-HH:MM}}      for DATETIME format.\r\n" \
                                                              "  a 32-bit integer greater than 946684799  for UNIX     format.\r\n" \
                                                              "  a 32-bit integer greater than 3155673599 for NTP      format.\r\n")

#define  CLK_CMD_HELP_FORMAT                                 ("where FORMAT is:\r\n"                                                        \
                                                              "\r\n"                                                                        \
                                                              "  -d, --datetime   DATETIME format.\r\n"                                     \
                                                              "  -u, --unix       UNIX     format.\r\n"                                     \
                                                              "  -n, --ntp        NTP      format.\r\n\r\n"                                 \
                                                              "  if FORMAT is not provided, VALUE is assumed to be in DATETIME format.\r\n")


/*
*********************************************************************************************************
*                                             DATA TYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                    CLOCK COMMAND TIME DATA TYPE
*********************************************************************************************************
*/

typedef enum {
    CLK_CMD_TIME_TYPE_NONE     = 0x00,
    CLK_CMD_TIME_TYPE_DATETIME = 0x30,
    CLK_CMD_TIME_TYPE_NTP      = 0x31,
    CLK_CMD_TIME_TYPE_UNIX     = 0x32
} CLK_CMD_TIME_TYPE;


/*
*********************************************************************************************************
*                                  CLOCK COMMAND ARGUMENT DATA TYPE
*********************************************************************************************************
*/

typedef  struct clk_cmd_arg {
    CLK_CMD_TIME_TYPE  TimeType;
    CPU_CHAR          *DatePtr;
    CPU_CHAR          *TimePtr;
    CPU_CHAR          *OffsetPtr;
} CLK_CMD_ARG;


/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static  CPU_INT16S   ClkCmd_Help        (       CPU_INT16U        argc,
                                                CPU_CHAR         *p_argv[],
                                                SHELL_OUT_FNCT    out_fnct,
                                                SHELL_CMD_PARAM  *p_cmd_param);

static  CPU_INT16S   ClkCmd_Set         (       CPU_INT16U        argc,
                                                CPU_CHAR         *p_argv[],
                                                SHELL_OUT_FNCT    out_fnct,
                                                SHELL_CMD_PARAM  *p_cmd_param);

static  CPU_INT16S   ClkCmd_Get         (       CPU_INT16U        argc,
                                                CPU_CHAR         *p_argv[],
                                                SHELL_OUT_FNCT    out_fnct,
                                                SHELL_CMD_PARAM  *p_cmd_param);

static  CLK_CMD_ARG  ClkCmd_CmdArgParse (       CPU_INT16U        argc,
                                                CPU_CHAR         *p_argv[],
                                                CLK_CMD_ERR      *p_err);

static  CPU_INT16S   ClkCmd_OutputCmdTbl(       SHELL_CMD        *p_cmd_tbl,
                                                SHELL_OUT_FNCT    out_fnct,
                                                SHELL_CMD_PARAM  *p_cmd_param);

static  CPU_INT16S   ClkCmd_OutputError (       CPU_CHAR         *p_error,
                                                SHELL_OUT_FNCT    out_fnct,
                                                SHELL_CMD_PARAM  *p_cmd_param);

static  CPU_INT16S   ClkCmd_OutputMsg   (const  CPU_CHAR         *p_msg,
                                                CPU_BOOLEAN       new_line_start,
                                                CPU_BOOLEAN       new_line_end,
                                                CPU_BOOLEAN       tab_start,
                                                SHELL_OUT_FNCT    out_fnct,
                                                SHELL_CMD_PARAM  *p_cmd_param);


/*
*********************************************************************************************************
*                                            LOCAL TABLES
*********************************************************************************************************
*/

static  SHELL_CMD ClkCmdTbl[] =
{
    {CLK_CMD_NAME_HELP, ClkCmd_Help},
    {CLK_CMD_NAME_SET,  ClkCmd_Set},
    {CLK_CMD_NAME_GET,  ClkCmd_Get},
    {0,                 0}
};


/*
*********************************************************************************************************
*                                                MACRO
*********************************************************************************************************
*/

#define  CLK_CMD_OUT_MSG_CHK(out_val, cur_out_cnt, exit_fail_label)     do {                                           \
                                                                            switch (out_val) {                         \
                                                                                case SHELL_OUT_RTN_CODE_CONN_CLOSED:   \
                                                                                case SHELL_OUT_ERR:                    \
                                                                                     out_val = SHELL_EXEC_ERR;         \
                                                                                     goto exit_fail_label;             \
                                                                                                                       \
                                                                                                                       \
                                                                                default:                               \
                                                                                     cur_out_cnt += out_val;           \
                                                                                     break;                            \
                                                                            }                                          \
                                                                        } while(0)


/*
*********************************************************************************************************
*                                            ClkCmd_Init()
*
* Description : Add Clk commands to uC/Shell.
*
* Argument(s) : p_err   Pointer to an error code which will be returned to your application:
*
*                           CLK_CMD_ERR_NONE            No error.
*
*                           CLK_CMD_ERR_SHELL_INIT      Command table not added to uC-Shell
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
*               This function is a Clock module application programming interface (API) function &
*               MAY be called by application function(s).
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  ClkCmd_Init (CLK_CMD_ERR  *p_err)
{
    SHELL_ERR  shell_err;


#if (CLK_CFG_ARG_CHK_EN == DEF_ENABLED)                         /* ----------------- VALIDATE ERR PTR ----------------- */
    if (p_err == DEF_NULL) {                                    /* Validate err ptr.                                    */
        CPU_SW_EXCEPTION(;);
    }
#endif

    Shell_CmdTblAdd((CPU_CHAR *)CLK_CMD_TBL_NAME,
                    ClkCmdTbl,
                    &shell_err);

    if (shell_err == SHELL_ERR_NONE) {
        *p_err = CLK_CMD_ERR_NONE;
    } else {
        *p_err = CLK_CMD_ERR_SHELL_INIT;
    }
}


/*
*********************************************************************************************************
*                                            ClkCmd_Help()
*
* Description : Output the available commands.
*
* Argument(s) : argc            Count of the arguments supplied.
*
*               p_argv          Array of pointers to the strings which are those arguments.
*
*               out_fnct        Callback to a respond to the requester.
*
*               p_cmd_param     Pointer to additional information to pass to the command.
*
* Return(s)   : The number of positive data octets transmitted, if NO errors
*
*               SHELL_OUT_RTN_CODE_CONN_CLOSED,                 if implemented connection closed
*
*               SHELL_OUT_ERR,                                  otherwise
*
* Caller(s)   : Shell_Exec().
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  CPU_INT16S  ClkCmd_Help (CPU_INT16U        argc,
                                 CPU_CHAR         *p_argv[],
                                 SHELL_OUT_FNCT    out_fnct,
                                 SHELL_CMD_PARAM  *p_cmd_param)
{
    CPU_INT16S  ret_val;


    (void)argc;                                                 /* Prevent 'variable unused' compiler warning.          */
    (void)p_argv;                                               /* Prevent 'variable unused' compiler warning.          */

    ret_val = ClkCmd_OutputCmdTbl(ClkCmdTbl,
                                  out_fnct,
                                  p_cmd_param);

    return (ret_val);
}


/*
*********************************************************************************************************
*                                            ClkCmd_Set()
*
* Description : Set the current date and time.
*
* Argument(s) : argc            Count of the arguments supplied.
*
*               p_argv          Array of pointers to the strings which are those arguments.
*
*               out_fnct        Callback to a respond to the requester.
*
*               p_cmd_param     Pointer to additional information to pass to the command.
*
* Return(s)   : The number of positive data octets transmitted, if NO errors
*
*               SHELL_OUT_RTN_CODE_CONN_CLOSED,                 if implemented connection closed
*
*               SHELL_OUT_ERR,                                  otherwise
*
* Caller(s)   : Shell_Exec().
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  CPU_INT16S  ClkCmd_Set (CPU_INT16U        argc,
                                CPU_CHAR         *p_argv[],
                                SHELL_OUT_FNCT    out_fnct,
                                SHELL_CMD_PARAM  *p_cmd_param)
{
#if  (CLK_CFG_STR_CONV_EN == DEF_ENABLED)
    CPU_CHAR       date_time_str[CLK_STR_FMT_MAX_LEN];
#endif
#if  (CLK_CFG_NTP_EN == DEF_ENABLED)
    CPU_INT32U     ts_ntp_toset;
#endif
#if  (CLK_CFG_UNIX_EN == DEF_ENABLED)
    CLK_TS_SEC     ts_unix_toset;
#endif
    CPU_INT16S     ret_val                            = 0u;
    CPU_INT16S     byte_out_cnt                       = 0u;
    CLK_YR         yr                                 = 0u;
    CLK_MONTH      month                              = 0u;
    CLK_DAY        day                                = 0u;
    CLK_HR         hr                                 = 0u;
    CLK_MIN        min                                = 0u;
    CLK_SEC        sec                                = 0u;
    CLK_TZ_SEC     tz_sec                             = 0u;
    CPU_SIZE_T     off_len                            = 0u;
    CPU_INT08S     off_hr                             = 0u;
    CPU_INT08S     off_min                            = 0u;
    CPU_CHAR      *p_next;
    CPU_CHAR      *p_next_tmp;
    CLK_CMD_ARG    cmd_arg;
    CLK_DATE_TIME  date_time;
    CPU_INT32U     off_ix;
    CLK_TS_SEC     ts_sec;
    CPU_BOOLEAN    success;
    CLK_CMD_ERR    err;


    cmd_arg = ClkCmd_CmdArgParse(argc,
                                 p_argv,
                                 &err);
    switch (err) {
        case CLK_CMD_ERR_NONE:
             break;


        case CLK_CMD_ERR_CMD_ARG_INVALID:
             ret_val = ClkCmd_OutputError((CPU_CHAR *)CLK_CMD_OUTPUT_ERR_CMD_ARG_INVALID,
                                          out_fnct,
                                          p_cmd_param);

             CLK_CMD_OUT_MSG_CHK(ret_val, byte_out_cnt, exit_fail);
             goto exit_ok;


        case CLK_CMD_ERR_CMD_ARG_NO_ARGS:
        case CLK_CMD_ERR_HELP:
        default:
             ret_val = ClkCmd_OutputMsg(CLK_CMD_HELP_SET,
                                        DEF_YES,
                                        DEF_YES,
                                        DEF_NO,
                                        out_fnct,
                                        p_cmd_param);

             CLK_CMD_OUT_MSG_CHK(ret_val, byte_out_cnt, exit_fail);

             ret_val = ClkCmd_OutputMsg(CLK_CMD_HELP_VALUE,
                                        DEF_YES,
                                        DEF_YES,
                                        DEF_NO,
                                        out_fnct,
                                        p_cmd_param);

             CLK_CMD_OUT_MSG_CHK(ret_val, byte_out_cnt, exit_fail);

             ret_val = ClkCmd_OutputMsg(CLK_CMD_HELP_FORMAT,
                                        DEF_YES,
                                        DEF_YES,
                                        DEF_NO,
                                        out_fnct,
                                        p_cmd_param);

             CLK_CMD_OUT_MSG_CHK(ret_val, byte_out_cnt, exit_fail);
             goto exit_ok;
    }

    switch (cmd_arg.TimeType) {
        case CLK_CMD_TIME_TYPE_NONE:
        case CLK_CMD_TIME_TYPE_DATETIME:
                                                                /* Parsing date.                                        */
             if (cmd_arg.DatePtr != DEF_NULL) {
                 yr    = (CLK_YR)   Str_ParseNbr_Int32U((const  CPU_CHAR *)cmd_arg.DatePtr,
                                                        &p_next,
                                                        10u);

                 month = (CLK_MONTH)Str_ParseNbr_Int32U((const  CPU_CHAR *)&p_next[1],
                                                        &p_next_tmp,
                                                        10u);

                 day   = (CLK_DAY)  Str_ParseNbr_Int32U((const  CPU_CHAR *)&p_next_tmp[1],
                                                        DEF_NULL,
                                                        10u);
             } else {
                 goto arg_invalid;
             }

                                                                /* Parsing time. (optional)                             */
             if (cmd_arg.TimePtr != DEF_NULL) {
                 hr  = (CLK_HR) Str_ParseNbr_Int32U((const  CPU_CHAR *)cmd_arg.TimePtr,
                                                    &p_next,
                                                    10u);

                 min = (CLK_MIN)Str_ParseNbr_Int32U((const  CPU_CHAR *)&p_next[1],
                                                    &p_next_tmp,
                                                    10u);

                 sec = (CLK_SEC)Str_ParseNbr_Int32U((const  CPU_CHAR *)&p_next_tmp[1],
                                                    DEF_NULL,
                                                    10u);

                                                                /* Parsing timezone. (optional).                        */
                 if (cmd_arg.OffsetPtr != DEF_NULL) {
                     off_len = Str_Len(cmd_arg.OffsetPtr);

                     for (off_ix = 0u ; off_ix < off_len ; off_ix++) {
                         if ((cmd_arg.OffsetPtr[off_ix] == ASCII_CHAR_HYPHEN_MINUS) ||
                             (cmd_arg.OffsetPtr[off_ix] == ASCII_CHAR_PLUS_SIGN)) {

                             off_hr  = (CPU_INT08S)Str_ParseNbr_Int32S((const  CPU_CHAR *)&cmd_arg.OffsetPtr[off_ix],
                                                                       &p_next,
                                                                       10u);

                             off_min = (CPU_INT08S)Str_ParseNbr_Int32S((const  CPU_CHAR *)&p_next[1],
                                                                       DEF_NULL,
                                                                       10u);
                             break;
                         }
                     }

                     tz_sec = (CLK_TZ_SEC)((off_hr * (CPU_INT08S)CLK_CMD_NBR_MIN_PER_HR + off_min) *
                                                     (CPU_INT08S)CLK_CMD_NBR_SEC_PER_MIN);
                 }
             }

             success = Clk_DateTimeMake(&date_time,             /* Make a datetime struct.                              */
                                        yr,
                                        month,
                                        day,
                                        hr,
                                        min,
                                        sec,
                                        tz_sec);

             if (success == DEF_FAIL) {
                 goto arg_invalid;
             }
                                                                /* Converting datetime to timestamp.                    */
             success = Clk_DateTimeToTS(&ts_sec,
                                        &date_time);

             if (success == DEF_FAIL) {
                 goto arg_invalid;
             }
                                                                /* Setting clock to timestamp.                          */
             success = Clk_SetTS(ts_sec);

             if (success == DEF_FAIL) {
                 goto arg_invalid;
             }
             break;

#if  (CLK_CFG_NTP_EN == DEF_ENABLED)
        case CLK_CMD_TIME_TYPE_NTP:
             ts_ntp_toset = Str_ParseNbr_Int32U(cmd_arg.DatePtr,
                                                DEF_NULL,
                                                10u);
             success      = Clk_SetTS_NTP(ts_ntp_toset);

             if (success == DEF_FAIL) {
                 goto arg_invalid;
             }
             break;
#endif


#if  (CLK_CFG_UNIX_EN == DEF_ENABLED)
        case CLK_CMD_TIME_TYPE_UNIX:
             ts_unix_toset = (CLK_TS_SEC)Str_ParseNbr_Int32U(cmd_arg.DatePtr,
                                                             DEF_NULL,
                                                             10u);
             success       = Clk_SetTS_Unix(ts_unix_toset);

             if(success == DEF_FAIL) {
                 goto arg_invalid;
             }
             break;
#endif


        default:
            goto arg_invalid;
    }

    success = Clk_GetDateTime(&date_time);
    if(success == DEF_FAIL) {
        goto arg_invalid;
    }
#if (CLK_CFG_STR_CONV_EN == DEF_ENABLED)
    success = Clk_DateTimeToStr(&date_time,
                                CLK_STR_FMT_YYYY_MM_DD_HH_MM_SS_UTC,
                                date_time_str,
                                CLK_STR_FMT_MAX_LEN);

    if(success == DEF_FAIL) {
        goto arg_invalid;
    }

    ret_val = ClkCmd_OutputMsg(date_time_str,
                               DEF_YES,
                               DEF_YES,
                               DEF_NO,
                               out_fnct,
                               p_cmd_param);

    CLK_CMD_OUT_MSG_CHK(ret_val, byte_out_cnt, exit_fail);
    goto exit_ok;
#else
    goto conv_not_enabled;
#endif

#if  (CLK_CFG_STR_CONV_EN == DEF_DISABLED)
conv_not_enabled:
    ret_val = ClkCmd_OutputError((CPU_CHAR *)CLK_CMD_OUTPUT_ERR_CONV_DISABLED,
                                 out_fnct,
                                 p_cmd_param);

    CLK_CMD_OUT_MSG_CHK(ret_val, byte_out_cnt, exit_fail);
    goto exit_ok;
#endif

arg_invalid:
    ret_val = ClkCmd_OutputError((CPU_CHAR *)CLK_CMD_OUTPUT_ERR_CMD_ARG_INVALID,
                                 out_fnct,
                                 p_cmd_param);

    CLK_CMD_OUT_MSG_CHK(ret_val, byte_out_cnt, exit_fail);
    goto exit_ok;

exit_ok:
    ret_val = byte_out_cnt;


exit_fail:
    return (ret_val);
}


/*
*********************************************************************************************************
*                                            ClkCmd_Get()
*
* Description : Manage a clock get command according to the specified format.
*
* Argument(s) : argc            Count of the arguments supplied.
*
*               p_argv          Array of pointers to the strings which are those arguments.
*
*               out_fnct        Callback to a respond to the requester.
*
*               p_cmd_param     Pointer to additional information to pass to the command.
*
* Return(s)   : The number of positive data octets transmitted, if NO errors
*
*               SHELL_OUT_RTN_CODE_CONN_CLOSED,                 if implemented connection closed
*
*               SHELL_OUT_ERR,                                  otherwise
*
* Caller(s)   : NetCmdTbl.
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  CPU_INT16S  ClkCmd_Get (CPU_INT16U        argc,
                                CPU_CHAR         *p_argv[],
                                SHELL_OUT_FNCT    out_fnct,
                                SHELL_CMD_PARAM  *p_cmd_param)
{
#if  (CLK_CFG_STR_CONV_EN == DEF_ENABLED)
    CPU_CHAR       date_time_str[CLK_STR_FMT_MAX_LEN];
#endif
#if  (CLK_CFG_UNIX_EN == DEF_ENABLED)
    CLK_TS_SEC     ts_unix_sec;
#endif
#if  (CLK_CFG_NTP_EN == DEF_ENABLED)
    CLK_TS_SEC     ts_ntp_sec;
#endif
#if ((CLK_CFG_UNIX_EN == DEF_ENABLED) || \
     (CLK_CFG_NTP_EN  == DEF_ENABLED))
    CPU_CHAR       ts_str[DEF_INT_32U_NBR_DIG_MAX + 1];
#endif
    CPU_INT16S     ret_val                             = 0u;
    CPU_INT16S     byte_out_cnt                        = 0u;
    CLK_CMD_ARG    cmd_arg;
    CLK_DATE_TIME  date_time;
    CPU_BOOLEAN    success;
    CLK_CMD_ERR    err;


    cmd_arg = ClkCmd_CmdArgParse(argc,
                                 p_argv,
                                 &err);

    switch (err) {
        case CLK_CMD_ERR_CMD_ARG_NO_ARGS:
        case CLK_CMD_ERR_NONE:
             break;


        case CLK_CMD_ERR_CMD_ARG_INVALID:
             ret_val = ClkCmd_OutputError((CPU_CHAR *)CLK_CMD_OUTPUT_ERR_CMD_ARG_INVALID,
                                          out_fnct,
                                          p_cmd_param);

             CLK_CMD_OUT_MSG_CHK(ret_val, byte_out_cnt, exit_fail);
             goto exit_ok;


        case CLK_CMD_ERR_HELP:
        default:
             ret_val = ClkCmd_OutputMsg(CLK_CMD_HELP_GET,
                                        DEF_YES,
                                        DEF_YES,
                                        DEF_NO,
                                        out_fnct,
                                        p_cmd_param);

             CLK_CMD_OUT_MSG_CHK(ret_val, byte_out_cnt, exit_fail);

             ret_val = ClkCmd_OutputMsg(CLK_CMD_HELP_FORMAT,
                                        DEF_YES,
                                        DEF_YES,
                                        DEF_NO,
                                        out_fnct,
                                        p_cmd_param);

             CLK_CMD_OUT_MSG_CHK(ret_val, byte_out_cnt, exit_fail);
             goto exit_ok;
    }

    switch(cmd_arg.TimeType){
        case CLK_CMD_TIME_TYPE_NONE:
        case CLK_CMD_TIME_TYPE_DATETIME:
             success = Clk_GetDateTime(&date_time);
             if(success == DEF_FAIL) {
                 goto date_time_invalid;
             }

#if (CLK_CFG_STR_CONV_EN == DEF_ENABLED)
             success = Clk_DateTimeToStr(&date_time,
                                         CLK_STR_FMT_YYYY_MM_DD_HH_MM_SS_UTC,
                                         date_time_str,
                                         CLK_STR_FMT_MAX_LEN);
             if(success == DEF_FAIL) {
                 goto date_time_invalid;
             }

             ret_val = ClkCmd_OutputMsg(date_time_str,
                                        DEF_YES,
                                        DEF_YES,
                                        DEF_NO,
                                        out_fnct,
                                        p_cmd_param);

             CLK_CMD_OUT_MSG_CHK(ret_val, byte_out_cnt, exit_fail);
             break;
#else
             goto conv_not_enabled;
#endif

#if  (CLK_CFG_NTP_EN == DEF_ENABLED)
        case CLK_CMD_TIME_TYPE_NTP:
             success = Clk_GetTS_NTP(&ts_ntp_sec);
             if(success == DEF_FAIL) {
                 goto date_time_invalid;
             }

             (void)Str_FmtNbr_Int32U(ts_ntp_sec,
                                     DEF_INT_32U_NBR_DIG_MAX,
                                     10u,
                                     '\0',
                                     DEF_NO,
                                     DEF_YES ,
                                     ts_str);

             ret_val = ClkCmd_OutputMsg(ts_str,
                                        DEF_YES,
                                        DEF_YES,
                                        DEF_NO,
                                        out_fnct,
                                        p_cmd_param);

             CLK_CMD_OUT_MSG_CHK(ret_val, byte_out_cnt, exit_fail);
             break;
#endif

#if  (CLK_CFG_UNIX_EN == DEF_ENABLED)
        case CLK_CMD_TIME_TYPE_UNIX:
             success = Clk_GetTS_Unix(&ts_unix_sec);
             if(success == DEF_FAIL) {
                 goto date_time_invalid;
             }

            (void)Str_FmtNbr_Int32U(ts_unix_sec,
                                    DEF_INT_32U_NBR_DIG_MAX,
                                    10u,
                                    '\0',
                                    DEF_NO,
                                    DEF_YES,
                                    ts_str);

             ret_val = ClkCmd_OutputMsg(ts_str,
                                        DEF_YES,
                                        DEF_YES,
                                        DEF_NO,
                                        out_fnct,
                                        p_cmd_param);

             CLK_CMD_OUT_MSG_CHK(ret_val, byte_out_cnt, exit_fail);
             break;
#endif

        default:
             ret_val = ClkCmd_OutputError((CPU_CHAR *)CLK_CMD_OUTPUT_ERR_CMD_ARG_INVALID,
                                          out_fnct,
                                          p_cmd_param);

             CLK_CMD_OUT_MSG_CHK(ret_val, byte_out_cnt, exit_fail);
    }
    goto exit_ok;

#if  (CLK_CFG_STR_CONV_EN == DEF_DISABLED)
conv_not_enabled:
        ret_val = ClkCmd_OutputError((CPU_CHAR *)CLK_CMD_OUTPUT_ERR_CONV_DISABLED,
                                     out_fnct,
                                     p_cmd_param);

        CLK_CMD_OUT_MSG_CHK(ret_val, byte_out_cnt, exit_fail);
        goto exit_ok;
#endif

date_time_invalid:
    ret_val = ClkCmd_OutputError((CPU_CHAR *)CLK_CMD_OUTPUT_ERR_CMD_INTERNAL_ERR,
                                 out_fnct,
                                 p_cmd_param);

    CLK_CMD_OUT_MSG_CHK(ret_val, byte_out_cnt, exit_fail);
    goto exit_ok;

exit_ok:
    ret_val = byte_out_cnt;


exit_fail:
    return (ret_val);
}


/*
*********************************************************************************************************
*                                        ClkCmd_CmdArgParse()
*
* Description : Parse and validate the argument for a clock test command.
*
* Argument(s) : argc    Count of the arguments supplied.
*
*               p_argv  Array of pointers to the strings which are those arguments.
*
*               p_err   Ppointer to an error code which will be returned to your application:
*
*                       CLK_CMD_ERR_NONE                        No error
*
*                       CLK_CMD_ERR_PARSER_ARG_VALUE_INVALID    Invalid arguments with the command
*                       CLK_CMD_ERR_CMD_ARG_INVALID             Too much arguments
*
* Return(s)   : CLK_CMD_ARG data structure filled with command arguments data
*
* Caller(s)   : ClkCmd_Get(),
*               ClkCmd_Set().
*
* Note(s)     : Expected command line:
*
*               clk_set
*               clk_get
*********************************************************************************************************
*/

static  CLK_CMD_ARG  ClkCmd_CmdArgParse (CPU_INT16U    argc,
                                         CPU_CHAR     *p_argv[],
                                         CLK_CMD_ERR  *p_err)
{
    CLK_CMD_ARG  cmd_args;
    CPU_INT16U   i;
    CPU_INT16U   arg_caught = 0u;


    cmd_args.TimeType  = CLK_CMD_TIME_TYPE_NONE;
    cmd_args.DatePtr   = DEF_NULL;
    cmd_args.TimePtr   = DEF_NULL;
    cmd_args.OffsetPtr = DEF_NULL;

    if (argc == 1) {
       *p_err = CLK_CMD_ERR_CMD_ARG_NO_ARGS;
        goto exit;
    }

    for (i = 1u; i < argc; i++) {
        if (*p_argv[i] == CLK_CMD_ARG_BEGIN) {
            if (*(p_argv[i] + 1) == CLK_CMD_ARG_BEGIN) {        /* --option type argument.                              */
                if (Str_Cmp(p_argv[i] + 2, CLK_CMD_FORMAT_DATETIME) == 0) {
                    cmd_args.TimeType = CLK_CMD_TIME_TYPE_DATETIME;
                } else if (Str_Cmp(p_argv[i] + 2, CLK_CMD_FORMAT_NTP) == 0) {
                    cmd_args.TimeType = CLK_CMD_TIME_TYPE_NTP;
                } else if (Str_Cmp(p_argv[i] + 2, CLK_CMD_FORMAT_UNIX) == 0) {
                    cmd_args.TimeType = CLK_CMD_TIME_TYPE_UNIX;
                } else if (Str_Cmp(p_argv[i] + 2, CLK_CMD_HELP) == 0) {
                   *p_err = CLK_CMD_ERR_HELP;
                    goto exit;
                } else {
                   *p_err = CLK_CMD_ERR_PARSER_ARG_VALUE_INVALID;
                    goto exit;
                }
            } else {                                            /* -o type argument.                                    */
                if (Str_Cmp(p_argv[i] + 1, CLK_CMD_FORMAT_DATETIME_SHORT) == 0) {
                    cmd_args.TimeType = CLK_CMD_TIME_TYPE_DATETIME;
                } else if (Str_Cmp(p_argv[i] + 1, CLK_CMD_FORMAT_NTP_SHORT) == 0) {
                    cmd_args.TimeType = CLK_CMD_TIME_TYPE_NTP;
                } else if (Str_Cmp(p_argv[i] + 1, CLK_CMD_FORMAT_UNIX_SHORT) == 0) {
                    cmd_args.TimeType = CLK_CMD_TIME_TYPE_UNIX;
                } else if (Str_Cmp(p_argv[i] + 1, CLK_CMD_HELP_SHORT) == 0) {
                   *p_err = CLK_CMD_ERR_HELP;
                    goto exit;
                } else {
                   *p_err = CLK_CMD_ERR_PARSER_ARG_VALUE_INVALID;
                    goto exit;
                }
            }
        } else {
            switch (arg_caught) {
                case 0:
                     cmd_args.DatePtr   = p_argv[i];
                     break;


                case 1:
                     cmd_args.TimePtr   = p_argv[i];
                     break;


                case 2:
                     cmd_args.OffsetPtr = p_argv[i];
                     break;


                default:
                     break;
            }

            arg_caught++;
        }
    }

   *p_err = CLK_CMD_ERR_NONE;

exit:
    return (cmd_args);
}


/*
*********************************************************************************************************
*                                        ClkCmd_OutputCmdTbl()
*
* Description : Format and output the clock test command table
*
* Argument(s) : p_cmd_tbl       is the pointer on the pointer table
*
*               out_fnct        is a callback to a respond to the requester.
*
*               p_cmd_param     is a pointer to additional information to pass to the command.
*
* Return(s)   : The number of positive data octets transmitted, if NO errors
*
*               SHELL_OUT_RTN_CODE_CONN_CLOSED,                 if implemented connection closed
*
*               SHELL_OUT_ERR,                                  otherwise
*
* Caller(s)   : ClkCmd_Help().
*
* Note(s)     : none.
*
*********************************************************************************************************
*/

static  CPU_INT16S  ClkCmd_OutputCmdTbl (SHELL_CMD        *p_cmd_tbl,
                                         SHELL_OUT_FNCT    out_fnct,
                                         SHELL_CMD_PARAM  *p_cmd_param)
{
    SHELL_CMD   *p_shell_cmd;
    CPU_INT16S   ret_val;


    ret_val = ClkCmd_OutputMsg(CLK_CMD_OUTPUT_CMD_LIST,
                               DEF_YES,
                               DEF_YES,
                               DEF_NO,
                               out_fnct,
                               p_cmd_param);
    switch (ret_val) {
        case SHELL_OUT_RTN_CODE_CONN_CLOSED:
        case SHELL_OUT_ERR:
             return (SHELL_EXEC_ERR);


        default:
             break;
    }

    p_shell_cmd = p_cmd_tbl;

    while (p_shell_cmd->Fnct != 0) {
        ret_val = ClkCmd_OutputMsg(p_shell_cmd->Name,
                                   DEF_NO,
                                   DEF_YES,
                                   DEF_YES,
                                   out_fnct,
                                   p_cmd_param);
        switch (ret_val) {
            case SHELL_OUT_RTN_CODE_CONN_CLOSED:
            case SHELL_OUT_ERR:
                 return (SHELL_EXEC_ERR);


            default:
                 break;
        }
        p_shell_cmd++;
    }


    return (ret_val);
}


/*
*********************************************************************************************************
*                                         ClkCmd_OutputError()
*
* Description : Outputs error message.
*
* Argument(s) : p_error         Pointer to a string describing the error.
*
*               out_fnct        Callback to a respond to the requester.
*
*               p_cmd_param     Pointer to additional information to pass to the command.
*
* Return(s)   : The number of positive data octets transmitted, if NO errors:
*
*               SHELL_OUT_RTN_CODE_CONN_CLOSED,                 if implemented connection closed
*
*               SHELL_OUT_ERR,                                  otherwise.
*
* Caller(s)   : ClkCmd_OutputCmdArgInvalid(),
*               ClkCmd_OutputNotImplemented().
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  CPU_INT16S  ClkCmd_OutputError (CPU_CHAR         *p_error,
                                        SHELL_OUT_FNCT    out_fnct,
                                        SHELL_CMD_PARAM  *p_cmd_param)
{
    CPU_INT16S  ret_val;
    CPU_INT16S  byte_out_cnt = 0;


    ret_val = ClkCmd_OutputMsg(CLK_CMD_OUTPUT_ERR,
                               DEF_YES,
                               DEF_NO,
                               DEF_NO,
                               out_fnct,
                               p_cmd_param);

    CLK_CMD_OUT_MSG_CHK(ret_val, byte_out_cnt, exit_fail);

    ret_val = ClkCmd_OutputMsg(p_error,
                               DEF_NO,
                               DEF_YES,
                               DEF_NO,
                               out_fnct,
                               p_cmd_param);

    CLK_CMD_OUT_MSG_CHK(ret_val, byte_out_cnt, exit_fail);

    ret_val = byte_out_cnt;


exit_fail:
    return (ret_val);
}


/*
*********************************************************************************************************
*                                          ClkCmd_OutputMsg()
*
* Description : Format and output a message.
*
* Argument(s) : p_msg           Pointer of char on the string to format and output.
*
*               new_line_start  If DEF_YES, will add a new line character at the start.
*
*               new_line_end    If DEF_YES, will add a new line character at the end.
*
*               tab_start       If DEF_YES, will add a tab character at the start.
*
*               out_fnct        Callback to a respond to the requester.
*
*               p_cmd_param     Pointer to additional information to pass to the command.
*
* Return(s)   : The number of positive data octets transmitted, if NO errors
*
*               SHELL_OUT_RTN_CODE_CONN_CLOSED,                 if implemented connection closed,
*
*               SHELL_OUT_ERR,                                  otherwise.
*
* Caller(s)   : ClkCmd_Set(),
*               ClkCmd_Get(),
*               ClkCmd_OutputError(),
*               ClkCmd_OutputSuccess().
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  CPU_INT16S  ClkCmd_OutputMsg (const  CPU_CHAR         *p_msg,
                                             CPU_BOOLEAN       new_line_start,
                                             CPU_BOOLEAN       new_line_end,
                                             CPU_BOOLEAN       tab_start,
                                             SHELL_OUT_FNCT    out_fnct,
                                             SHELL_CMD_PARAM  *p_cmd_param)
{
    CPU_INT16U  output_len;
    CPU_INT16S  output;
    CPU_INT16S  byte_out_cnt = 0;


    if (new_line_start == DEF_YES) {
        output = out_fnct((CPU_CHAR *)STR_NEW_LINE,
                          STR_NEW_LINE_LEN,
                          p_cmd_param->pout_opt);

        CLK_CMD_OUT_MSG_CHK(output, byte_out_cnt, exit_fail);
    }

    if (tab_start == DEF_YES) {
        output = out_fnct((CPU_CHAR *)CLK_CMD_OUTPUT_TABULATION,
                          1,
                          p_cmd_param->pout_opt);

        CLK_CMD_OUT_MSG_CHK(output, byte_out_cnt, exit_fail);
    }

    output_len = (CPU_INT16U)Str_Len(p_msg);
    output     = out_fnct((CPU_CHAR *)p_msg,
                          output_len,
                          p_cmd_param->pout_opt);

    CLK_CMD_OUT_MSG_CHK(output, byte_out_cnt, exit_fail);

    if (new_line_end == DEF_YES) {
        output = out_fnct((CPU_CHAR *)STR_NEW_LINE,
                          STR_NEW_LINE_LEN,
                          p_cmd_param->pout_opt);

        CLK_CMD_OUT_MSG_CHK(output, byte_out_cnt, exit_fail);
    }

    output = byte_out_cnt;

exit_fail:
    return (output);
}
