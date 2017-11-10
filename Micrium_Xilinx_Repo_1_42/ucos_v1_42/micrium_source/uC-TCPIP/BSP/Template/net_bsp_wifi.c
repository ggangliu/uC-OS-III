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
*                            NETWORK BOARD SUPPORT PACKAGE (BSP) FUNCTIONS
*
*                                              TEMPLATE
*
* Filename      : net_bsp_wifi.c
* Version       : V3.03.01
* Programmer(s) : ITJ
*                 AA
*********************************************************************************************************
* Note(s)       : (1) To provide the required Board Support Package functionality, insert the appropriate
*                     board-specific code to perform the stated actions wherever 'TODO' comments are found.
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*********************************************************************************************************
*/

#define    NET_BSP_MODULE
#include  <IF/net_if_wifi.h>

#ifdef  NET_IF_WIFI_MODULE_EN

/*
*********************************************************************************************************
*                                  NETWORK DEVICE INTERFACE NUMBERS
*
* Note(s) : (1) (a) Each network device maps to a unique network interface number.
*
*               (b) Instances of network devices' interface number SHOULD be named using the following
*                   convention :
*
*                       <Board><Device>[Number]_IF_Nbr
*
*                           where
*                                   <Board>         Development board name
*                                   <Device>        Network device name (or type)
*                                   [Number]        Network device number for each specific instance
*                                                       of device (optional if the development board
*                                                       does NOT support multiple instances of the
*                                                       specific device)
*
*                   For example, the network device interface number variable for the #2 MACB Ethernet
*                   controller on an Atmel AT91SAM92xx should be named 'AT91SAM92xx_MACB_2_IF_Nbr'.
*
*               (c) Network device interface number variables SHOULD be initialized to 'NET_IF_NBR_NONE'.
*********************************************************************************************************
*/

static  NET_IF_NBR  WiFi_SPI_IF_Nbr = NET_IF_NBR_NONE;


/*
*********************************************************************************************************
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                               NETWORK DEVICE BSP FUNCTION PROTOTYPES
*
* Note(s) : (1) Device driver BSP functions may be arbitrarily named.  However, it is recommended that
*               device BSP functions be named using the suggested names/conventions provided below.
*
*               (a) (1) Network device BSP functions SHOULD be named using the following convention :
*
*                           NetDev_[Device]<Function>[Number]()
*
*                               where
*                                   (A) [Device]        Network device name or type (optional if the
*                                                           development board does NOT support multiple
*                                                           devices)
*                                   (B) <Function>      Network device BSP function
*                                   (C) [Number]        Network device number for each specific instance
*                                                           of device (optional if the development board
*                                                           does NOT support multiple instances of the
*                                                           specific device)
*
*                       For example, the NetDev_CfgClk() function for the #2 MACB Ethernet controller
*                       on an Atmel AT91SAM92xx should be named NetDev_MACB_CfgClk2().
*
*                   (2) BSP-level device ISR handlers SHOULD be named using the following convention :
*
*                           NetDev_[Device]ISR_Handler[Type][Number]()
*
*                               where
*                                   (A) [Device]        Network device name or type (optional if the
*                                                           development board does NOT support multiple
*                                                           devices)
*                                   (B) [Type]          Network device interrupt type (optional if
*                                                           interrupt type is generic or unknown)
*                                   (C) [Number]        Network device number for each specific instance
*                                                           of device (optional if the development board
*                                                           does NOT support multiple instances of the
*                                                           specific device)
*
*               (b) All BSP function prototypes SHOULD be located within the development board's network
*                   BSP C source file ('net_bsp.c') & be declared as static functions to prevent name
*                   clashes with other network protocol suite BSP functions/files.
*********************************************************************************************************
*/

                                                                /* ----------- WIFI BSP FUNCTION PROTOTYPES ----------- */
static  void        NetDev_WiFi_Start         (NET_IF                          *p_if,
                                               NET_ERR                         *p_err);

static  void        NetDev_WiFi_Stop          (NET_IF                          *p_if,
                                               NET_ERR                         *p_err);

static  void        NetDev_WiFi_CfgGPIO       (NET_IF                          *p_if,
                                               NET_ERR                         *p_err);

static  void        NetDev_WiFi_CfgIntCtrl    (NET_IF                          *p_if,
                                               NET_ERR                         *p_err);

static  void        NetDev_WiFi_IntCtrl       (NET_IF                          *p_if,
                                               CPU_BOOLEAN                      en,
                                               NET_ERR                         *p_err);

static  void        NetDev_WiFi_SPI_Init      (NET_IF                          *p_if,
                                               NET_ERR                         *p_err);

static  void        NetDev_WiFi_SPI_Lock      (NET_IF                          *p_if,
                                               NET_ERR                         *p_err);

static  void        NetDev_WiFi_SPI_Unlock    (NET_IF                          *p_if);

static  void        NetDev_WiFi_SPI_WrRd      (NET_IF                          *p_if,
                                               CPU_INT08U                      *p_buf_wr,
                                               CPU_INT08U                      *p_buf_rd,
                                               CPU_INT16U                       len,
                                               NET_ERR                         *p_err);

static  void        NetDev_WiFi_SPI_ChipSelEn (NET_IF                          *p_if,
                                               NET_ERR                         *p_err);

static  void        NetDev_WiFi_SPI_ChipSelDis(NET_IF                          *p_if);

static  void        NetDev_WiFi_SPI_Cfg       (NET_IF                          *p_if,
                                               NET_DEV_CFG_SPI_CLK_FREQ         freq,
                                               NET_DEV_CFG_SPI_CLK_POL          pol,
                                               NET_DEV_CFG_SPI_CLK_PHASE        phase,
                                               NET_DEV_CFG_SPI_XFER_UNIT_LEN    xfer_unit_len,
                                               NET_DEV_CFG_SPI_XFER_SHIFT_DIR   xfer_shift_dir,
                                               NET_ERR                         *p_err);

        void        NetDev_WiFi_ISR_Handler   (void);


/*
*********************************************************************************************************
*********************************************************************************************************
*                                            LOCAL TABLES
*********************************************************************************************************
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                    NETWORK DEVICE BSP INTERFACE
*
* Note(s) : (1) Device board-support package (BSP) interface structures are used by the device driver to
*               call specific devices' BSP functions via function pointer instead of by name.  This enables
*               the network protocol suite to compile & operate with multiple instances of multiple devices
*               & drivers.
*
*           (2) In most cases, the BSP interface structure provided below SHOULD suffice for most devices'
*               BSP functions exactly as is with the exception that BSP interface structures' names MUST be
*               unique & SHOULD clearly identify the development board, device name, & possibly the specific
*               device number (if the development board supports multiple instances of any given device).
*
*               (a) BSP interface structures SHOULD be named using the following convention :
*
*                       NetDev_BSP_<Board><Device>[Number]{}
*
*                           where
*                               (1) <Board>         Development board name
*                               (2) <Device>        Network device name (or type)
*                               (3) [Number]        Network device number for each specific instance
*                                                       of device (optional if the development board
*                                                       does NOT support multiple instances of the
*                                                       specific device)
*
*                   For example, the BSP interface structure for the #2 MACB Ethernet controller on
*                   an Atmel AT91SAM92xx should be named NetDev_BSP_AT91SAM92xx_MACB_2{}.
*
*               (b) The BSP interface structure MUST also be externally declared in the development
*                   board's network BSP header file ('net_bsp.h') with the exact same name & type.
*********************************************************************************************************
*/

const  NET_DEV_BSP_WIFI_SPI  NetDev_BSP_WiFi       = {                                  /* WIRELESS #3's  SPI BSP fnct ptrs :     */
                                                        &NetDev_WiFi_Start,             /* Start Device (Power up).               */
                                                        &NetDev_WiFi_Stop,              /* Stop  Device (Power down).             */
                                                        &NetDev_WiFi_CfgGPIO,           /* Cfg   GPIO.                            */
                                                        &NetDev_WiFi_CfgIntCtrl,        /* Cfg   external int.                    */
                                                        &NetDev_WiFi_IntCtrl,           /* Ctrl  external int.                    */
                                                        &NetDev_WiFi_SPI_Init,          /* Init         SPI.                      */
                                                        &NetDev_WiFi_SPI_Lock,          /* Acquire      SPI lock.                 */
                                                        &NetDev_WiFi_SPI_Unlock,        /* Release      SPI lock.                 */
                                                        &NetDev_WiFi_SPI_WrRd,          /* Wr and Rd to SPI.                      */
                                                        &NetDev_WiFi_SPI_ChipSelEn,     /* En           SPI chip sel.             */
                                                        &NetDev_WiFi_SPI_ChipSelDis,    /* Dis          SPI chip sel.             */
                                                        &NetDev_WiFi_SPI_Cfg,           /* Cfg          SPI controller.           */
                                                      };


/*
*********************************************************************************************************
*********************************************************************************************************
*                                     LOCAL CONFIGURATION ERRORS
*********************************************************************************************************
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*********************************************************************************************************
*                            NETWORK WIRELESS SPI DEVICE DRIVER FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/

/*
*******************************************************************************************************
*                                         NetDev_WiFi_Start()
*
* Description : Start (power up) interface's/device's.
*
* Argument(s) : p_if        Pointer to interface to start the hardware.
*               ----        Argument validated in NetIF_Add().
*
*               p_err        Pointer to variable that will receive the return error code from this function :
*
*                               NET_DEV_ERR_NONE                Device     successfully started.
*                               NET_DEV_ERR_FAULT               Device NOT successfully started.
*
* Return(s)   : none.
*
* Caller(s)   : Device driver via 'p_dev_bsp->Start()'.
*
*               This function is an INTERNAL network protocol suite function & SHOULD NOT be called by
*               application function(s).
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  void  NetDev_WiFi_Start (NET_IF   *p_if,
                                 NET_ERR  *p_err)
{
    /* TODO Insert code to start (power up) wireless spi device.   */

   *p_err = NET_DEV_ERR_NONE;
}


/*
*********************************************************************************************************
*                                         NetDev_WiFi_Stop()
*
* Description : Stop (power down) interface's/device's.
*
* Argument(s) : p_if    Pointer to interface to start the hardware.
*               ----    Argument validated in NetIF_Add().
*
*               p_err        Pointer to variable that will receive the return error code from this function :
*
*                               NET_DEV_ERR_NONE                Device     successfully stopped.
*                               NET_DEV_ERR_FAULT               Device NOT successfully stopped.
*
* Return(s)   : none.
*
* Caller(s)   : Device driver via 'p_dev_bsp->Stop()'.
*
*               This function is an INTERNAL network protocol suite function & SHOULD NOT be called by
*               application function(s)
*
* Note(s)     : none.
*********************************************************************************************************
*/
static  void  NetDev_WiFi_Stop (NET_IF   *p_if,
                                NET_ERR  *p_err)
{
    /* TODO Insert code to stop (power down) wireless spi device.   */

   *p_err = NET_DEV_ERR_NONE;
}


/*
*********************************************************************************************************
*                                         NetDev_WiFi_CfgGPIO()
*
* Description : Configure general-purpose I/O (GPIO) for the specified interface/device. (SPI, External Interrupt,
*               Power, Reset, etc.)
*
* Argument(s) : p_if        Pointer to interface to start the hardware.
*               ----        Argument validated in NetIF_Add().
*
*               p_err        Pointer to variable that will receive the return error code from this function :
*
*                               NET_DEV_ERR_NONE                Device GPIO     successfully configured.
*                               NET_DEV_ERR_FAULT               Device GPIO NOT successfully configured.
*
* Return(s)   : none.
*
* Caller(s)   : Device driver via 'p_dev_bsp->Stop()'.
*
*               This function is an INTERNAL network protocol suite function & SHOULD NOT be called by
*               application function(s)
*
* Note(s)     : none.
*********************************************************************************************************
*/
static  void  NetDev_WiFi_CfgGPIO (NET_IF   *p_if,
                                   NET_ERR  *p_err)
{
    /* TODO Insert code to configure each network interface's/device's GPIO.  */

   *p_err = NET_DEV_ERR_NONE;
}


/*
*********************************************************************************************************
*                                      NetDev_WiFi_CfgIntCtrl()
*
* Description : Configure interrupts &/or interrupt controller for the specified interface/device.
*
* Argument(s) : p_if        Pointer to interface to start the hardware.
*               ----        Argument validated in NetIF_Add().
*
*               p_err        Pointer to variable that will receive the return error code from this function :
*
*                               NET_DEV_ERR_NONE                Device interrupt(s)     successfully configured.
*                               NET_DEV_ERR_FAULT               Device interrupt(s) NOT successfully configured.
*
* Return(s)   : none.
*
* Caller(s)   : Device driver via 'p_dev_bsp->CfgIntCtrl()'.
*
*               This function is an INTERNAL network protocol suite function & SHOULD NOT be called by
*               application function(s)
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  void  NetDev_WiFi_CfgIntCtrl (NET_IF   *p_if,
                                      NET_ERR  *p_err)
{
    WiFi_SPI_IF_Nbr = p_if->Nbr;

    /* TODO Insert code to configure each network interface's/device's interrupt(s)/controller. */

   *p_err = NET_DEV_ERR_NONE;
}


/*
*********************************************************************************************************
*                                          NetDev_IntCtrl()
*
* Description : Enable or diable interface's/device's interrupt.
*
* Argument(s) : p_if    Pointer to interface to start the hardware.
*               ----    Argument validated in NetIF_Add().
*
*               en      Enable or diable the interrupt.
*
*               p_err        Pointer to variable that will receive the return error code from this function :
*
*                               NET_DEV_ERR_NONE                Device interrupt(s)     successfully enabled or disabled.
*                               NET_DEV_ERR_FAULT               Device interrupt(s) NOT successfully enabled or disabled.
*
* Return(s)   : none.
*
* Caller(s)   : Device driver via 'p_dev_bsp->IntCtrl()'.
*
*               This function is an INTERNAL network protocol suite function & SHOULD NOT be called by
*               application function(s)
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  void  NetDev_WiFi_IntCtrl (NET_IF       *p_if,
                                   CPU_BOOLEAN   en,
                                   NET_ERR      *p_err)
{
    if (en == DEF_YES) {
        /* TODO Insert code to enable  the interface's/device's interrupt(s).    */
    } else if (en == DEF_NO) {
        /* TODO Insert code to disable the interface's/device's interrupt(s).    */
    }

   *p_err = NET_DEV_ERR_NONE;
}


/*
*********************************************************************************************************
*                                       NetDev_WiFi_SPI_Init()
*
* Description : Initialize SPI controller.
*
* Argument(s) : p_if        Pointer to interface to start the hardware.
*               ----        Argument validated in NetIF_Add().
*
*               p_err        Pointer to variable that will receive the return error code from this function :
*
*                               NET_DEV_ERR_NONE                SPI controller     successfully initialized.
*                               NET_DEV_ERR_FAULT               SPI controller NOT successfully initialized.
*
* Return(s)   : none.
*
* Caller(s)   : Device driver via 'p_dev_bsp->SPI_Init()'.
*
*               This function is an INTERNAL network protocol suite function & SHOULD NOT be called by
*               application function(s)
*
* Note(s)     : (1) This function is called only when the wireless network interface is added.
*
*               (2) The CS (Chip Select) MUST be configured as a GPIO output; it could not be controlled
*                   by the CPU's SPI peripheral.  The functions 'NetDev_SPI_ChipSelEn()' and
*                  'NetDev_SPI_ChipSelDis()' should manually enable and disable the CS.
*********************************************************************************************************
*/

static  void  NetDev_WiFi_SPI_Init (NET_IF   *p_if,
                                    NET_ERR  *p_err)
{

    /* TODO Insert code to initialize SPI interface's/device's controller & lock.   */

   *p_err = NET_DEV_ERR_NONE;
}


/*
*********************************************************************************************************
*                                       NetDev_WiFi_SPI_Lock()
*
* Description : Acquire SPI lock.
*
* Argument(s) : p_if        Pointer to interface to start the hardware.
*               ----        Argument validated in NetIF_Add().
*
*               p_err        Pointer to variable that will receive the return error code from this function :
*
*                               NET_DEV_ERR_NONE                SPI lock     successfully acquired.
*                               NET_DEV_ERR_FAULT               SPI lock NOT successfully acquired.
*
* Return(s)   : none.
*
* Caller(s)   : Device driver via 'p_dev_bsp->SPI_Lock()'.
*
*               This function is an INTERNAL network protocol suite function & SHOULD NOT be called by
*               application function(s)
*
* Note(s)     : (1) This function will be called before the device driver begins to access the SPI.  The
*                   application should NOT use the same bus to access another device until the matching
*                   call to 'NetDev_SPI_Unlock()' has been made.
*********************************************************************************************************
*/

static  void  NetDev_WiFi_SPI_Lock (NET_IF   *p_if,
                                    NET_ERR  *p_err)
{
    /* TODO Insert code to lock the SPI controller.     */

   *p_err = NET_DEV_ERR_NONE;
}

/*
*********************************************************************************************************
*                                         NetDev_WiFi_SPI_Unlock()
*
* Description : Release SPI lock.
*
* Argument(s) : p_if    Pointer to interface to start the hardware.
*               ----    Argument validated in NetIF_Add().
*
* Return(s)   : none.
*
* Caller(s)   : Device driver via 'p_dev_bsp->SPI_Unlock()'.
*
*               This function is an INTERNAL network protocol suite function & SHOULD NOT be called by
*               application function(s)
*
* Note(s)     : (1) 'NetDev_SPI_Lock()' will be called before the device driver begins to access the SPI.
*                   The application should NOT use the same bus to access another device until the
*                   matching call to this function has been made.
*********************************************************************************************************
*/

static  void  NetDev_WiFi_SPI_Unlock (NET_IF  *p_if)
{
    /* TODO Insert code to unlock the SPI controller.   */
}


/*
*********************************************************************************************************
*                                      NetDev_WiFi_SPI_WrRd()
*
* Description : Write and read to SPI bus.
*
* Argument(s) : p_if        Pointer to interface to write and read from.
*               ----        Argument validated in NetIF_Add().
*
*               p_buf_wr    Pointer to buffer to write.
*               --------    Argument validated by caller(s).
*
*               p_buf_rd    Pointer to buffer for data read.
*               --------    Argument validated by caller(s).
*
*               wr_rd_len   Number of octets to write and read.
*
*               p_err       Pointer to variable that will receive the return error code from this function :
*
*                               NET_DEV_ERR_NONE                Network buffers     successfully wrote and read.
*                               NET_DEV_ERR_FAULT               Network buffers NOT successfully wrote and read.
*
* Return(s)   : none.
*
* Caller(s)   : Device driver via 'p_dev_bsp->SPI_WrRd()'.
*
*               This function is an INTERNAL network protocol suite function & SHOULD NOT be called by
*               application function(s).
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  void  NetDev_WiFi_SPI_WrRd (NET_IF      *p_if,
                                    CPU_INT08U  *p_buf_wr,
                                    CPU_INT08U  *p_buf_rd,
                                    CPU_INT16U   wr_rd_len,
                                    NET_ERR     *p_err)
{
    /* TODO Insert code to write and read on the SPI controller.    */

   *p_err = NET_DEV_ERR_NONE;
}


/*
*********************************************************************************************************
*                                     NetDev_WiFi_SPI_ChipSelEn()
*
* Description : Enable device chip select.
*
* Argument(s) : p_if    Pointer to interface to enable the chip select.
*               ----    Argument validated in NetIF_Add().
*
*               p_err        Pointer to variable that will receive the return error code from this function :
*
*                               NET_DEV_ERR_NONE                Device chip select     successfully enabled.
*                               NET_DEV_ERR_FAULT               Device chip select NOT successfully enabled.
*
* Return(s)   : none.
*
* Caller(s)   : Device driver via 'p_dev_bsp->SPI_ChipSelEn()'.
*
*               This function is an INTERNAL network protocol suite function & SHOULD NOT be called by
*               application function(s)
*
* Note(s)     : (1) 'NetDev_SPI_ChipSelEn()' will be called before the device driver begins to access
*                   the SPI.
*
*               (2) The chip select is typically 'active low'; to enable the card, the chip select pin
*                   should be cleared.
*********************************************************************************************************
*/

static  void  NetDev_WiFi_SPI_ChipSelEn (NET_IF   *p_if,
                                         NET_ERR  *p_err)
{
    /* TODO Insert code to enable the device chip select.    */
   *p_err = NET_DEV_ERR_NONE;
}


/*
*********************************************************************************************************
*                                    NetDev_WiFi_SPI_ChipSelDis()
*
* Description : Disable device chip select.
*
* Argument(s) : p_if    Pointer to interface to disable the chip select.
*               ----    Argument validated in NetIF_Add().
*
* Return(s)   : none.
*
* Caller(s)   : Device driver via 'p_dev_bsp->SPI_ChipSelDis()'.
*
*               This function is an INTERNAL network protocol suite function & SHOULD NOT be called by
*               application function(s)
*
* Note(s)     : (1) 'NetDev_SPI_ChipSelDis()' will be called when the device driver finished to access
*                   the SPI.
*
*               (1) The chip select is typically 'active low'; to disable the card, the chip select pin
*                   should be set.
*********************************************************************************************************
*/

static  void  NetDev_WiFi_SPI_ChipSelDis (NET_IF  *p_if)
{
    /* TODO Insert code to disable the device chip select.    */
}


/*
*********************************************************************************************************
*                                        NetDev_WiFi_SPI_Cfg()
*
* Description : Configure the SPI controller following the device configuration.
*
* Argument(s) : p_if            Pointer to interface to configure the spi.
*               ----            Argument validated in NetIF_Add().
*
*               freq            Clock frequency, in Hz.
*
*               pol             Clock polarity:
*                                   NET_DEV_SPI_CLK_POL_INACTIVE_LOW        The clk is low  when inactive.
*                                   NET_DEV_SPI_CLK_POL_INACTIVE_HIGH       The clk is high when inactive.
*
*               phase           Clock Phase:
*                                   NET_DEV_SPI_CLK_PHASE_FALLING_EDGE      Data is 'read'    on the leading   edge &
*                                                                                   'changed' on the following edge
*
*                                   NET_DEV_SPI_CLK_PHASE_RAISING_EDGE      Data is 'changed' on the following edge &
*                                                                                   'read'    on the leading   edge.
*
*               xfer_unit_len   Transfer unit length:
*                                   NET_DEV_SPI_XFER_UNIT_LEN_8_BITS        Unit length is  8 bits.
*                                   NET_DEV_SPI_XFER_UNIT_LEN_16_BITS       Unit length is 16 bits.
*                                   NET_DEV_SPI_XFER_UNIT_LEN_32_BITS       Unit length is 32 bits.
*                                   NET_DEV_SPI_XFER_UNIT_LEN_64_BITS       Unit length is 64 bits.
*
*               xfer_shift_dir  Transfer Shift direction:
*                                   NET_DEV_SPI_XFER_SHIFT_DIR_FIRST_MSB    MSB first.
*                                   NET_DEV_SPI_XFER_SHIFT_DIR_FIRST_LSB    LSB First
*
*               p_err        Pointer to variable that will receive the return error code from this function :
*
*                               NET_DEV_ERR_NONE                SPI controller     successfully configured.
*                               NET_DEV_ERR_FAULT               SPI controller NOT successfully configured.
*
* Return(s)   : none.
*
* Caller(s)   : Device driver via 'p_dev_bsp->SPI_SetCfg()'.
*
*               This function is an INTERNAL network protocol suite function & SHOULD NOT be called by
*               application function(s)
*
* Note(s)     : (1) 'NetDev_SPI_SetCfg()' will be called before the device driver begins to access
*                   the SPI and after 'NetDev_SPI_Lock()' has been called.
*
*               (2) The effective clock frequency MUST be no more than 'freq'.  If the frequency cannot be
*                   configured equal to 'freq', it should be configured less than 'freq'.
*********************************************************************************************************
*/

void  NetDev_WiFi_SPI_Cfg(NET_IF                          *p_if,
                          NET_DEV_CFG_SPI_CLK_FREQ         freq,
                          NET_DEV_CFG_SPI_CLK_POL          pol,
                          NET_DEV_CFG_SPI_CLK_PHASE        phase,
                          NET_DEV_CFG_SPI_XFER_UNIT_LEN    xfer_unit_len,
                          NET_DEV_CFG_SPI_XFER_SHIFT_DIR   xfer_shift_dir,
                          NET_ERR                         *p_err)
{

    /* TODO Insert code to configure correctly the SPI Bus.    */

   *p_err = NET_DEV_ERR_NONE;
}


/*
*********************************************************************************************************
*                                      NetDev_WiFi_ISR_Handler()
*
* Description : BSP-level ISR handler(s) for WiFi device interrupt.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : CPU &/or WiFi device interrupt.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  NetDev_WiFi_ISR_Handler (void)
{
    NET_ERR  err;


    NetIF_ISR_Handler(WiFi_SPI_IF_Nbr, NET_DEV_ISR_TYPE_UNKNOWN, &err);

    /* TODO Insert code to clear WiFi device interrupt(s), if necessary.    */
}

#endif /* NET_IF_WIFI_MODULE_EN */
