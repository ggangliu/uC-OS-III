/*
*********************************************************************************************************
*                                       EXAMPLE CODE
*
*               This file is provided as an example on how to use Micrium products.
*
*               Please feel free to use any application code labeled as 'EXAMPLE CODE' in
*               your application products.  Example code may be used as is, in whole or in
*               part, or may be used as a reference only. This file can be modified as
*               required to meet the end-product requirements.
*
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*
*               You can contact us at www.micrium.com.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                 USB HOST APPLICATION INITIALIZATION
*
*
* Filename      : app_usbh.c
* Version       : V3.41.01
* Programmer(s) : JFD
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#define   APP_USBH_MODULE

#include  <ucos_bsp.h>
#include  "app_usbh.h"

/*
*********************************************************************************************************
*                                              LOCAL DEFINES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                         LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                        LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                       LOCAL CONFIGURATION ERRORS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            App_USBH_Init()
*
* Description : Initialize USB Host Stack and additional demos.
*
* Argument(s) : None.
*
* Return(s)   : DEF_OK      if successfull.
*               DEF_FAIL    otherwise.
*
* Caller(s)   : Application.
*
* Note(s)     : None.
*********************************************************************************************************
*/

CPU_BOOLEAN  App_USBH_Init (void)
{
    USBH_ERR    err;

    UCOS_Printf("... Initiliazing HOST Mass Storage class ...\r\n");
    err = App_USBH_MSC_Init();\

    if (err != USBH_ERR_NONE) {
    	UCOS_Printf("...could not initialize HOST Mass Storage Class w/err = %d\r\n\r\n", err);
        return (DEF_FAIL);
    }


    return (DEF_OK);
}
