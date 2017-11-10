/*
*********************************************************************************************************
*                                            uC/USB-Device
*                                       The Embedded USB Stack
*
*                         (c) Copyright 2004-2015; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*
*               uC/USB is provided in source form to registered licensees ONLY.  It is
*               illegal to distribute this source code to any third party unless you receive
*               written permission by an authorized Micrium representative.  Knowledge of
*               the source code may NOT be used to develop a similar product.
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
*                                  USB DEVICE DRIVER BOARD-SPECIFIC FUNCTIONS
*                                       XILINX ZYNQ-7000 ZC702 EVAL KIT
*
* File          : usbd_bsp_zc702.c
* Version       : V4.01.01.00
* Programmer(s) : FT
*                 FGK
*                 JPB
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include  <cpu.h>
#include  <ucos_bsp.h>
#include  <Source/usbd_core.h>


/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/

#define  USBD0_INTR_ID                     (53U)


/*
*********************************************************************************************************
*                                          REGISTER DEFINES
*********************************************************************************************************
*/

#define USBD_ZC702_GPIO_BASE_ADDRESS       (CPU_ADDR   )(0xE000A000)
                                                                /* GPIO Bank0 MIO: Output Data register.                */
#define USBD_ZC702_GPIO_DATA_0_REG       (*(CPU_REG32 *)(USBD_ZC702_GPIO_BASE_ADDRESS + 0x00000040u))
                                                                /* GPIO Bank0 MIO: Direction mode register.             */
#define USBD_ZC702_GPIO_DIRM_0_REG       (*(CPU_REG32 *)(USBD_ZC702_GPIO_BASE_ADDRESS + 0x00000204u))
                                                                /* GPIO Bank0 MIO: Output enable register.              */
#define USBD_ZC702_GPIO_OEN_0_REG        (*(CPU_REG32 *)(USBD_ZC702_GPIO_BASE_ADDRESS + 0x00000208u))

#define USBD_ZC702_GPIO_ON_MASK          DEF_BIT_07
#define USBD_ZC702_GPIO_OFF_MASK         DEF_BIT_NONE


/*
*********************************************************************************************************
*                                           LOCAL CONSTANTS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            LOCAL TABLES
*
* Note(s) : (1) The USB device controller hardware in the Zynq-7000 is configured to support
*               up to 12 endpoints.
*           (2) The USB device controller driver can enable, disable and configure endpoint
*               types up to the maximum selected during synthesis.
*           (3) Each endpoint direction is essentially independent and can be configured with
*               differing behavior in each direction.
*               For example, the driver can configure endpoint 1 IN to be a bulk endpoint and
*               endpoint 1 OUT to be an isochronous endpoint.
*********************************************************************************************************
*/

USBD_DRV_EP_INFO  USBD_DrvEP_InfoTbl_ZC702[] = {
    {USBD_EP_INFO_TYPE_CTRL                                                   | USBD_EP_INFO_DIR_OUT,  0u,   64u},
    {USBD_EP_INFO_TYPE_CTRL                                                   | USBD_EP_INFO_DIR_IN,   0u,   64u},
    {USBD_EP_INFO_TYPE_ISOC | USBD_EP_INFO_TYPE_BULK | USBD_EP_INFO_TYPE_INTR | USBD_EP_INFO_DIR_OUT,  1u, 1024u},
    {USBD_EP_INFO_TYPE_ISOC | USBD_EP_INFO_TYPE_BULK | USBD_EP_INFO_TYPE_INTR | USBD_EP_INFO_DIR_IN,   1u, 1024u},
    {USBD_EP_INFO_TYPE_ISOC | USBD_EP_INFO_TYPE_BULK | USBD_EP_INFO_TYPE_INTR | USBD_EP_INFO_DIR_OUT,  2u, 1024u},
    {USBD_EP_INFO_TYPE_ISOC | USBD_EP_INFO_TYPE_BULK | USBD_EP_INFO_TYPE_INTR | USBD_EP_INFO_DIR_IN,   2u, 1024u},
    {USBD_EP_INFO_TYPE_ISOC | USBD_EP_INFO_TYPE_BULK | USBD_EP_INFO_TYPE_INTR | USBD_EP_INFO_DIR_OUT,  3u, 1024u},
    {USBD_EP_INFO_TYPE_ISOC | USBD_EP_INFO_TYPE_BULK | USBD_EP_INFO_TYPE_INTR | USBD_EP_INFO_DIR_IN,   3u, 1024u},
    {USBD_EP_INFO_TYPE_ISOC | USBD_EP_INFO_TYPE_BULK | USBD_EP_INFO_TYPE_INTR | USBD_EP_INFO_DIR_OUT,  4u, 1024u},
    {USBD_EP_INFO_TYPE_ISOC | USBD_EP_INFO_TYPE_BULK | USBD_EP_INFO_TYPE_INTR | USBD_EP_INFO_DIR_IN,   4u, 1024u},
    {USBD_EP_INFO_TYPE_ISOC | USBD_EP_INFO_TYPE_BULK | USBD_EP_INFO_TYPE_INTR | USBD_EP_INFO_DIR_OUT,  5u, 1024u},
    {USBD_EP_INFO_TYPE_ISOC | USBD_EP_INFO_TYPE_BULK | USBD_EP_INFO_TYPE_INTR | USBD_EP_INFO_DIR_IN,   5u, 1024u},
    {USBD_EP_INFO_TYPE_ISOC | USBD_EP_INFO_TYPE_BULK | USBD_EP_INFO_TYPE_INTR | USBD_EP_INFO_DIR_OUT,  6u, 1024u},
    {USBD_EP_INFO_TYPE_ISOC | USBD_EP_INFO_TYPE_BULK | USBD_EP_INFO_TYPE_INTR | USBD_EP_INFO_DIR_IN,   6u, 1024u},
    {USBD_EP_INFO_TYPE_ISOC | USBD_EP_INFO_TYPE_BULK | USBD_EP_INFO_TYPE_INTR | USBD_EP_INFO_DIR_OUT,  7u, 1024u},
    {USBD_EP_INFO_TYPE_ISOC | USBD_EP_INFO_TYPE_BULK | USBD_EP_INFO_TYPE_INTR | USBD_EP_INFO_DIR_IN,   7u, 1024u},
    {USBD_EP_INFO_TYPE_ISOC | USBD_EP_INFO_TYPE_BULK | USBD_EP_INFO_TYPE_INTR | USBD_EP_INFO_DIR_OUT,  8u, 1024u},
    {USBD_EP_INFO_TYPE_ISOC | USBD_EP_INFO_TYPE_BULK | USBD_EP_INFO_TYPE_INTR | USBD_EP_INFO_DIR_IN,   8u, 1024u},
    {USBD_EP_INFO_TYPE_ISOC | USBD_EP_INFO_TYPE_BULK | USBD_EP_INFO_TYPE_INTR | USBD_EP_INFO_DIR_OUT,  9u, 1024u},
    {USBD_EP_INFO_TYPE_ISOC | USBD_EP_INFO_TYPE_BULK | USBD_EP_INFO_TYPE_INTR | USBD_EP_INFO_DIR_IN,   9u, 1024u},
    {USBD_EP_INFO_TYPE_ISOC | USBD_EP_INFO_TYPE_BULK | USBD_EP_INFO_TYPE_INTR | USBD_EP_INFO_DIR_OUT, 10u, 1024u},
    {USBD_EP_INFO_TYPE_ISOC | USBD_EP_INFO_TYPE_BULK | USBD_EP_INFO_TYPE_INTR | USBD_EP_INFO_DIR_IN,  10u, 1024u},
    {USBD_EP_INFO_TYPE_ISOC | USBD_EP_INFO_TYPE_BULK | USBD_EP_INFO_TYPE_INTR | USBD_EP_INFO_DIR_OUT, 11u, 1024u},
    {USBD_EP_INFO_TYPE_ISOC | USBD_EP_INFO_TYPE_BULK | USBD_EP_INFO_TYPE_INTR | USBD_EP_INFO_DIR_IN,  11u, 1024u},
    {DEF_BIT_NONE                                                                                  ,   0u,    0u}
};


/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/

static  USBD_DRV  *USBD_ZC702_BSP_DrvPtr;


/*
*********************************************************************************************************
*                                            LOCAL MACRO'S
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static  void  USBD_BSP_ZC702_Init      (USBD_DRV  *p_drv);
static  void  USBD_BSP_ZC702_Conn      (void            );
static  void  USBD_BSP_ZC702_Disconn   (void            );
static  void  USBD_BSP_ZC702_IntHandler (CPU_INT32U source, void  *p_arg);

/*
*********************************************************************************************************
*                                   USB DEVICE DRIVER BSP INTERFACE
*********************************************************************************************************
*/
                                                                /* Board-/device-specific BSP fnct ptrs :   */
USBD_DRV_BSP_API  USBD_DrvBSP_ZC702 = {
    USBD_BSP_ZC702_Init,
    USBD_BSP_ZC702_Conn,
    USBD_BSP_ZC702_Disconn,
};

/*
*********************************************************************************************************
*                                     LOCAL CONFIGURATION ERRORS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*********************************************************************************************************
*                                           LOCAL FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                       USBD_BSP_ZC702_Init()
*
* Description : USB device controller board-specific initialization.
*
*                   (1) Enable    USB dev ctrl registers  and bus clock.
*                   (2) Configure USB dev ctrl interrupts.
*                   (3) Disable   USB dev transceiver Pull-up resistor in D+ line.
*                   (4) Disable   USB dev transceiver clock.
*
* Argument(s) : p_drv       Pointer to device driver structure.
*
* Return(s)   : none.
*
* Caller(s)   : Device controller driver init function via 'p_drv_api->Init()'
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  void  USBD_BSP_ZC702_Init (USBD_DRV  *p_drv)
{
    USBD_ZC702_BSP_DrvPtr = p_drv;

                                                                /* GPIO configuration.                                */
    DEF_BIT_SET(USBD_ZC702_GPIO_DIRM_0_REG, USBD_ZC702_GPIO_ON_MASK);
    DEF_BIT_SET(USBD_ZC702_GPIO_OEN_0_REG,  USBD_ZC702_GPIO_ON_MASK);
    DEF_BIT_SET(USBD_ZC702_GPIO_DATA_0_REG, USBD_ZC702_GPIO_ON_MASK);
    DEF_BIT_SET(USBD_ZC702_GPIO_DATA_0_REG, USBD_ZC702_GPIO_OFF_MASK);
    DEF_BIT_SET(USBD_ZC702_GPIO_DATA_0_REG, USBD_ZC702_GPIO_ON_MASK);

    CPU_MB();

    UCOS_IntVectSet (USBD0_INTR_ID,
                    0u,
                    DEF_BIT_00,
                    USBD_BSP_ZC702_IntHandler,
                    DEF_NULL);

    UCOS_IntSrcEn(USBD0_INTR_ID);
}


/*
*********************************************************************************************************
*                                       USBD_BSP_ZC702_Conn()
*
* Description : Connect pull-up on DP.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : Device controller driver start function via 'p_drv_api->Conn()'
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  void  USBD_BSP_ZC702_Conn (void)
{
    UCOS_IntSrcEn(USBD0_INTR_ID);
}


/*
*********************************************************************************************************
*                                     USBD_BSP_ZC702_Disconn()
*
* Description : Disconnect pull-up on DP.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : Device controller driver stop function via 'p_drv_api->Disconn()'
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  void  USBD_BSP_ZC702_Disconn (void)
{

}


/*
*********************************************************************************************************
*                                    USBD_BSP_ZC702_IntHandler()
*
* Description : This is the USB ISR handler for the USB Device port(UDP) interrupt
*
* Argument(s) : p_arg       Interrupt handler argument.
*
* Return(s)   : none.
*
* Caller(s)   : This is a ISR.
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  void  USBD_BSP_ZC702_IntHandler (CPU_INT32U source, void  *p_arg)
{
    USBD_DRV      *p_drv;
    USBD_DRV_API  *p_drv_api;


    p_drv     = USBD_ZC702_BSP_DrvPtr;
    p_drv_api = p_drv->API_Ptr;

    p_drv_api->ISR_Handler(p_drv);
}
