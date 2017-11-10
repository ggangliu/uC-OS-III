/*
*********************************************************************************************************
*                                            uC/USB-Device
*                                       The Embedded USB Stack
*
*                         (c) Copyright 2004-2015; Micrium, Inc.; Weston, FL
*
*                  All rights reserved.  Protected by international copyright laws.
*
*                  uC/USB-Device is provided in source form to registered licensees ONLY.  It is
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
*                                         USB DEVICE DRIVER
*
*                                         XILINX  ZYNQ-7000
*
* File          : usbd_drv_zynq.c
* Version       : V4.04.00.00
* Programmer(s) : FGK
*                 FT
*                 JPB
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#define    MICRIUM_SOURCE
#include  <Source/usbd_core.h>
#include  <lib_mem.h>
#include  "usbd_drv_zynq.h"
#include  <cpu_cache.h>


/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/

                                                                /* ---------- USB DEVICE REGISTER BIT DEFINES --------- */
#define  USBD_ZYNQ_DEV_ADDR_USBADDRA             DEF_BIT_24     /* Device Address Advance                               */
                                                                /* Device Address Mask                                  */
#define  USBD_ZYNQ_DEV_ADDR_USBADDR_MASK         DEF_BIT_FIELD_32(7, 25)

#define  USBD_ZYNQ_PORTSC1_HSP                   DEF_BIT_09     /* High-Speed port                                      */
#define  USBD_ZYNQ_PORTSC1_FPR                   DEF_BIT_06     /* Force port resume.                                   */


                                                                /* ------ USB INTERRUPT AND STATUS REGISTER BITS ------ */
#define  USBD_ZYNQ_USBSTS_NAKI                   DEF_BIT_16     /* NAK Interrupt Bit.                                   */
#define  USBD_ZYNQ_USBSTS_AS                     DEF_BIT_15     /* Asynchronous Schedule Status.                        */
#define  USBD_ZYNQ_USBSTS_PS                     DEF_BIT_14     /* Periodic Schedule Status.                            */
#define  USBD_ZYNQ_USBSTS_RCL                    DEF_BIT_13     /* Reclamation.                                         */
#define  USBD_ZYNQ_USBSTS_HCH                    DEF_BIT_12     /* HCHaIted.                                            */
#define  USBD_ZYNQ_USBSTS_ULPI                   DEF_BIT_10     /* ULPI Interrupt.                                      */
#define  USBD_ZYNQ_USBSTS_SLI                    DEF_BIT_08     /* DCSuspend.                                           */
#define  USBD_ZYNQ_USBSTS_SRI                    DEF_BIT_07     /* SOF Received.                                        */
#define  USBD_ZYNQ_USBSTS_URI                    DEF_BIT_06     /* USB Reset Received.                                  */
#define  USBD_ZYNQ_USBSTS_AAI                    DEF_BIT_05     /* Interrupt on Async Advance.                          */
#define  USBD_ZYNQ_USBSTS_SEI                    DEF_BIT_04     /* System Error.                                        */
#define  USBD_ZYNQ_USBSTS_FRI                    DEF_BIT_03     /* Frame List Rollover.                                 */
#define  USBD_ZYNQ_USBSTS_PCI                    DEF_BIT_02     /* Port Change Detect.                                  */
#define  USBD_ZYNQ_USBSTS_UEI                    DEF_BIT_01     /* USB Error Interrupt.                                 */
#define  USBD_ZYNQ_USBSTS_UI                     DEF_BIT_00     /* USB Interrupt.                                       */

                                                                /* ------ USB INTERRUPT REGISTER (USBINTR) BITS ------- */
#define  USBD_ZYNQ_USBSTS_NAKE                   DEF_BIT_16     /* NAK Interrupt enable                                 */
#define  USBD_ZYNQ_USBSTS_ULPIE                  DEF_BIT_10     /* ULPI enable                                          */
#define  USBD_ZYNQ_USBSTS_SLE                    DEF_BIT_08     /* Sleep enable                                         */
#define  USBD_ZYNQ_USBSTS_SRE                    DEF_BIT_07     /* SOF received enable                                  */
#define  USBD_ZYNQ_USBSTS_URE                    DEF_BIT_06     /* USB reset enable                                     */
#define  USBD_ZYNQ_USBSTS_AAE                    DEF_BIT_05     /* Interrupt on Async Advance enable                    */
#define  USBD_ZYNQ_USBSTS_SEE                    DEF_BIT_04     /* System Error enable                                  */
#define  USBD_ZYNQ_USBSTS_FRE                    DEF_BIT_03     /* Frame List Rollover enable                           */
#define  USBD_ZYNQ_USBSTS_PCE                    DEF_BIT_02     /* Port Change Detect enable                            */
#define  USBD_ZYNQ_USBSTS_UEE                    DEF_BIT_01     /* USB Error Interrupt enable                           */
#define  USBD_ZYNQ_USBSTS_UE                     DEF_BIT_00     /* USB Interrupt enable                                 */

                                                                /* ------------ USB INTERRUPT ENABLE BITS ------------- */
#define  USBD_ZYNQ_USB_INT_NAK                   DEF_BIT_16     /* NAK Interrupt enable                                 */
#define  USBD_ZYNQ_USB_INT_ULP                   DEF_BIT_10     /* ULPI enable                                          */
#define  USBD_ZYNQ_USB_INT_SL                    DEF_BIT_08     /* Sleep enable                                         */
#define  USBD_ZYNQ_USB_INT_SR                    DEF_BIT_07     /* SOF received enable                                  */
#define  USBD_ZYNQ_USB_INT_UR                    DEF_BIT_06     /* USB reset enable                                     */
#define  USBD_ZYNQ_USB_INT_AA                    DEF_BIT_05     /* Interrupt on Async Advance enable                    */
#define  USBD_ZYNQ_USB_INT_SE                    DEF_BIT_04     /* System Error enable                                  */
#define  USBD_ZYNQ_USB_INT_FR                    DEF_BIT_03     /* Frame List Rollover enable                           */
#define  USBD_ZYNQ_USB_INT_PC                    DEF_BIT_02     /* Port Change Detect enable                            */
#define  USBD_ZYNQ_USB_INT_UE                    DEF_BIT_01     /* USB Error Interrupt enable                           */
#define  USBD_ZYNQ_USB_INT_U                     DEF_BIT_00     /* USB Interrupt enable                                 */

#define  USBD_ZYNQ_USB_INT_BUS                  (USBD_ZYNQ_USB_INT_PC | \
                                                 USBD_ZYNQ_USB_INT_UR | \
                                                 USBD_ZYNQ_USB_INT_SL)


                                                                /* --------- USB COMMAND REGISTER BIT DEFINES --------- */
                                                                /* Interrupt Threshold Control and max rates            */
#define  USBD_ZYNQ_USBCMD_ITC_MASK               DEF_BIT_FIELD_32(8, 16)
#define  USBD_ZYNQ_USBCMD_ITC_MICRO_FRAME_1      DEF_BIT_MASK(0x01,  16)
#define  USBD_ZYNQ_USBCMD_ITC_MICRO_FRAME_2      DEF_BIT_MASK(0x02,  16)
#define  USBD_ZYNQ_USBCMD_ITC_MICRO_FRAME_3      DEF_BIT_MASK(0x04,  16)
#define  USBD_ZYNQ_USBCMD_ITC_MICRO_FRAME_8      DEF_BIT_MASK(0x08,  16)
#define  USBD_ZYNQ_USBCMD_ITC_MICRO_FRAME_16     DEF_BIT_MASK(0x10,  16)
#define  USBD_ZYNQ_USBCMD_ITC_MICRO_FRAME_32     DEF_BIT_MASK(0x20,  16)
#define  USBD_ZYNQ_USBCMD_ITC_MICRO_FRAME_40     DEF_BIT_MASK(0x40,  16)

                                                                /* Frame List size                                      */
#define  USBD_ZYNQ_USBCMD_FS_MASK                DEF_BIT_FIELD(2, 14)
#define  USBD_ZYNQ_USBCMD_ATDTW                  DEF_BIT_14     /* Add dTD TripWire                                     */

#define  USBD_ZYNQ_USBCMD_SUTW                   DEF_BIT_13     /* Setup Tripwire                                       */
#define  USBD_ZYNQ_USBCMD_ASPE                   DEF_BIT_11     /* Asynchronous schedule park mode enable               */
                                                                /* Asynchronous schedule park mode count                */
#define  USBD_ZYNQ_USBCMD_ASP_MASK               DEF_BIT_FIELD(2, 8)
#define  USBD_ZYNQ_USBCMD_LR                     DEF_BIT_07     /* Light Host/Device controller reset                   */
#define  USBD_ZYNQ_USBCMD_IAA                    DEF_BIT_06     /* Interrupt on Async Advance Doorbell                  */
#define  USBD_ZYNQ_USBCMD_ASE                    DEF_BIT_05     /* Asynchronous schedule enable                         */
#define  USBD_ZYNQ_USBCMD_PSE                    DEF_BIT_04     /* Periodic schedule enable                             */

                                                                /* Frame List Size mask                                 */
#define  USBD_ZYNQ_USBCMD_FS_SIZE_MASK           DEF_BIT_FIELD(3, 2)
#define  USBD_ZYNQ_USBCMD_RST                    DEF_BIT_01     /* Controller Reset                                     */
#define  USBD_ZYNQ_USBCMD_RUN                    DEF_BIT_00     /* Run/Stop                                             */

                                                                /* ------ USB DEVICE ADDRESS REGISTER BIT DEFINES ----- */
                                                                /* Device Address mask                                  */
#define  USBD_ZYNQ_DEV_ADDR_USBADR_MASK          DEF_BIT_FIELD(6, 25)
#define  USBD_ZYNQ_DEV_ADDR_USBADRA              DEF_BIT_24     /* Device Address Advance.                              */

                                                                /* ---- ENDPOINT LIST ADDRESS REGISTER BIT DEFINES ---- */
#define  USBD_ZYNQ_EP_LIST_ADDR_MASK             DEF_BIT_FIELD(21, 11)

                                                                /* ----------- USB MODE REGISTER BIT DEFINES ---------- */
#define  USBD_ZYNQ_USBMODE_SDIS                  DEF_BIT_04     /* Stream Disable Mode                                  */
#define  USBD_ZYNQ_USBMODE_SLOM                  DEF_BIT_03     /* Setup lockout mode                                   */
#define  USBD_ZYNQ_USBMODE_ES                    DEF_BIT_02     /* Endianness selection                                 */
                                                                /* Controller Mode mask                                 */

#define  USBD_ZYNQ_USBMODE_CM_MASK               DEF_BIT_FILED(2,0)
                                                                /* Idle   mode                                          */
#define  USBD_ZYNQ_USBMODE_CM_IDLE               DEF_BIT_NONE
#define  USBD_ZYNQ_USBMODE_CM_DEV                DEF_BIT_01     /* Device mode                                          */
                                                                /* Host   mode                                          */
#define  USBD_ZYNQ_USBMODE_CM_HOST              (DEF_BIT_01 | DEF_BIT_02)

                                                                /* ------- ENDPOINT CONTROL 1-11 REGISTER BITS -------- */
#define  USBD_ZYNQ_ENDPTCTRL_TX_CFG_MASK         DEF_BIT_FIELD_32(8, 16)
#define  USBD_ZYNQ_ENDPTCTRL_TX_EN               DEF_BIT_23     /* Tx endpoint enable                                   */
#define  USBD_ZYNQ_ENDPTCTRL_TX_TOGGLE_RST       DEF_BIT_22     /* Data Toggle reset                                    */
#define  USBD_ZYNQ_ENDPTCTRL_TX_TOGGLE_DIS       DEF_BIT_21     /* Data Toggle inhibit                                  */
                                                                /* Tx endpoint type mask                                */
#define  USBD_ZYNQ_ENDPTCTRL_TX_TYPE_MASK        DEF_BIT_FIELD_32(2, 18)
                                                                /* Tx endpoint type control                             */
#define  USBD_ZYNQ_ENDPTCTRL_TX_TYPE_CTRL        DEF_BIT_NONE
#define  USBD_ZYNQ_ENDPTCTRL_TX_TYPE_ISOC        DEF_BIT_18     /* Tx endpoint type isochronous                         */
#define  USBD_ZYNQ_ENDPTCTRL_TX_TYPE_BULK        DEF_BIT_19     /* Tx endpoint type bulk                                */
                                                                /* Tx endpoint type interrupt                           */
#define  USBD_ZYNQ_ENDPTCTRL_TX_TYPE_INT        (DEF_BIT_18 | DEF_BIT_19)
#define  USBD_ZYNQ_ENDPTCTRL_TX_DATA_SRC         DEF_BIT_17     /* Tx endpoint data source                              */
#define  USBD_ZYNQ_ENDPTCTRL_TX_STALL            DEF_BIT_16     /* Tx endpoint stall                                    */

#define  USBD_ZYNQ_ENDPTCTRL_RX_CFG_MASK         DEF_BIT_FIELD_32(8, 0)
#define  USBD_ZYNQ_ENDPTCTRL_RX_EN               DEF_BIT_07     /* Rx endpoint enable                                   */
#define  USBD_ZYNQ_ENDPTCTRL_RX_TOGGLE_RST       DEF_BIT_06     /* Rx Data Toggle reset                                 */
#define  USBD_ZYNQ_ENDPTCTRL_RX_TOGGLE_DIS       DEF_BIT_05     /* Rx Data Toggle inhibit                               */
                                                                /* Rx endpoint type mask                                */
#define  USBD_ZYNQ_ENDPTCTRL_RX_TYPE_MASK        DEF_BIT_FIELD_32(2, 2)
                                                                /* Tx endpoint type control                             */
#define  USBD_ZYNQ_ENDPTCTRL_RX_TYPE_CTRL        DEF_BIT_NONE
#define  USBD_ZYNQ_ENDPTCTRL_RX_TYPE_ISOC        DEF_BIT_02     /* Tx endpoint type isochronous                         */
#define  USBD_ZYNQ_ENDPTCTRL_RX_TYPE_BULK        DEF_BIT_03     /* Tx endpoint type bulk                                */
                                                                /* Tx endpoint type interrupt                          */
#define  USBD_ZYNQ_ENDPTCTRL_RX_TYPE_INT        (DEF_BIT_02 | DEF_BIT_03)
#define  USBD_ZYNQ_ENDPTCTRL_RX_DATA_SRC         DEF_BIT_01     /* Tx endpoint data source                              */
#define  USBD_ZYNQ_ENDPTCTRL_RX_STALL            DEF_BIT_00     /* Tx endpoint stall                                    */

#define  USBD_ZYNQ_ENDPTCOMPLETE_TX_MASK         DEF_BIT_FIELD_32(4, 16)
#define  USBD_ZYNQ_ENDPTCOMPLETE_RX_MASK         DEF_BIT_FIELD_32(4, 0)

#define  USBD_ZYNQ_ENDPTxxxx_TX_MASK             DEF_BIT_FIELD_32(4, 16)
#define  USBD_ZYNQ_ENDPTxxxx_RX_MASK             DEF_BIT_FIELD_32(4,  0)

                                                                /* -- ENDPOINT QUEUE HEAD EP CAPABILITIES BIT DEFINES - */
                                                                /* Number of packets executed per transaction.          */
#define  USBD_ZYNQ_dQH_EP_CAP_MULT_MASK          DEF_BIT_FIELD_32(2, 30)
#define  USBD_ZYNQ_dQH_EP_CAP_MULT_N             DEF_BIT_MASK(0, 30)
#define  USBD_ZYNQ_dQH_EP_CAP_MULT_1             DEF_BIT_MASK(1, 30)
#define  USBD_ZYNQ_dQH_EP_CAP_MULT_2             DEF_BIT_MASK(2, 30)
#define  USBD_ZYNQ_dQH_EP_CAP_MULT_3             DEF_BIT_MASK(3, 30)

#define  USBD_ZYNQ_dQH_EP_CAP_ZLTS               DEF_BIT_29     /* Zero Length Termination Select                       */
                                                                /* EP maximum packet length mask (1024 max)             */
#define  USBD_ZYNQ_dQH_EP_CAP_MAX_LEN_MASK       DEF_BIT_FIELD_32(11, 16)
#define  USBD_ZYNQ_dQH_EP_CAP_IOS                DEF_BIT_15     /* Interrupt on setup                                   */

                                                                /* ----- ENDPOINT TRANSFER DESCRIPTOR BIT DEFINES ----- */

                                                                /* ------------ dTD_NEXT FIELD  BIT DEFINES ----------- */
                                                                /* Next transfer element pointer mask                   */
#define  USBD_ZYNQ_dTD_dTD_NEXT_MASK             DEF_BIT_FIELD_32(27, 5)
#define  USBD_ZYNQ_dTD_dTD_NEXT_TERMINATE        DEF_BIT_00     /* End of transfer list indicator                       */

                                                                /* -------------- TOKEN FIELD BIT DEFINES ------------- */
#define  USBD_ZYNQ_dTD_TOKEN_TOTAL_BYTES_MASK    DEF_BIT_FIELD_32(15, 16)
                                                                /* Interrupt on complete                                */
#define  USBD_ZYNQ_dTD_TOKEN_IOC                 DEF_BIT_15
                                                                /* Multiplier override mask                             */
#define  USBD_ZYNQ_dTD_TOKEN_MUL_OVER_MASK       DEF_BIT_FIELD_32(2, 10)
                                                                /* Status mask                                          */
                                                                /* Maximum number of bytes                              */
#define  USBD_ZYNQ_dTD_TOKEN_TOTAL_BYTE_MAX      0x00004000
                                                                /* Page size 4K                                         */
#define  USBD_ZYNQ_dTD_TOKEN_PAGE_SIZE           0x00001000

#define  USBD_ZYNQ_dTD_TOKEN_STATUS_MASK         DEF_BIT_FIELD_32(8, 0)
#define  USBD_ZYNQ_dTD_TOKEN_STATUS_ACTIVE       DEF_BIT_07
#define  USBD_ZYNQ_dTD_TOKEN_STATUS_HALTED       DEF_BIT_06
#define  USBD_ZYNQ_dTD_TOKEN_STATUS_DATA_ERR     DEF_BIT_05
#define  USBD_ZYNQ_dTD_TOKEN_STATUS_TRAN_ERR     DEF_BIT_03

#define  USBD_ZYNQ_dTD_TOKEN_STATUS_ANY         (USBD_ZYNQ_dTD_TOKEN_STATUS_ACTIVE   | \
                                                 USBD_ZYNQ_dTD_TOKEN_STATUS_HALTED   | \
                                                 USBD_ZYNQ_dTD_TOKEN_STATUS_DATA_ERR | \
                                                 USBD_ZYNQ_dTD_TOKEN_STATUS_TRAN_ERR)

#define  USBD_ZYNQ_dTD_BUF_PTR_MASK              DEF_BIT_FIELD(20, 12)


                                                                /* ------------- USB CONTROLLER CONSTRAINS ------------ */
#define  USBD_ZYNQ_USB_REG_BASE_ADDR              0xE0002000    /* USB0 Controller Base Address (system.xml:ps7_usb_0). */

#define  USBD_ZYNQ_REG_TO                         0x0000FFFF
#define  USBD_ZYNQ_MAX_RETRIES                           100
#define  USBD_ZYNQ_dTD_LST_INSERT_NBR_TRIES_MAX          100
#define  USBD_ZYNQ_EP_NBR_MAX                             12

#define  USBD_ZYNQ_ALIGN_OCTECTS_dQH             ( 2u * (1024u))
#define  USBD_ZYNQ_ALIGN_OCTECTS_dTD             (64u * (   1u))
#define  USBD_ZYNQ_ALIGN_OCTECTS_BUF             ( 1u * (   1u))


/*
*********************************************************************************************************
*                                           LOCAL CONSTANTS
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                            LOCAL MACROS
*********************************************************************************************************
*/


#define  USBD_ZYNQ_EP_GET_LOG_NBR(ep_addr)                   ((ep_addr) & 0x0F)

#define  USBD_ZYNQ_EP_OUT_LOG_TO_PHY_NBR(ep_log_nbr)         ((ep_log_nbr) << 1)
#define  USBD_ZYNQ_EP_IN_LOG_TO_PHY_NBR(ep_log_nbr)          (USBD_ZYNQ_EP_OUT_LOG_TO_PHY_NBR(ep_log_nbr) + 1)

#define  USBD_ZYNQ_EP_PHY_TO_LOG_NBR(ep_phy_nbr)             ((ep_phy_nbr) >> 1)

#define  USBD_ZYNQ_ENDPTxxx_GET_TX_BITS(ep_log_nbr)          (DEF_BIT32(ep_log_nbr) << 16)
#define  USBD_ZYNQ_ENDPTxxx_GET_RX_BITS(ep_log_nbr)           DEF_BIT32(ep_log_nbr)

#define  USBD_ZYNQ_ENDPTxxx_GET_TX_NBR(ep_reg)               (((ep_reg) & USBD_ZYNQ_ENDPTxxxx_TX_MASK) >> 16)
#define  USBD_ZYNQ_ENDPTxxx_GET_RX_NBR(ep_reg)                ((ep_reg) & USBD_ZYNQ_ENDPTxxxx_RX_MASK)


#define  USBD_ZYNQ_ENDPTxxx_BIT_WR(ep_reg, ep_phy_nbr)       {    if (USBD_ZYNQ_EP_PHY_NBR_IS_OUT(ep_phy_nbr)) {                                                               \
                                                                       (ep_reg) = USBD_ZYNQ_ENDPTxxx_GET_RX_BITS(USBD_ZYNQ_EP_PHY_TO_LOG_NBR(ep_phy_nbr));                     \
                                                                  } else {                                                                                                     \
                                                                       (ep_reg) = USBD_ZYNQ_ENDPTxxx_GET_TX_BITS(USBD_ZYNQ_EP_PHY_TO_LOG_NBR(ep_phy_nbr));                     \
                                                                  }                                                                                                            \
                                                             }

#define  USBD_ZYNQ_ENDPTxxx_IS_BIT_SET(ep_reg, ep_phy_nbr)   (USBD_ZYNQ_EP_PHY_NBR_IS_OUT(ep_phy_nbr) ? (DEF_BIT_IS_SET(USBD_ZYNQ_ENDPTxxx_GET_RX_NBR(ep_reg),                 \
                                                                                                                       (DEF_BIT32(USBD_ZYNQ_EP_PHY_TO_LOG_NBR(ep_phy_nbr)))))  \
                                                                                                      : (DEF_BIT_IS_SET(USBD_ZYNQ_ENDPTxxx_GET_TX_NBR(ep_reg),                 \
                                                                                                                       (DEF_BIT32(USBD_ZYNQ_EP_PHY_TO_LOG_NBR(ep_phy_nbr))))))

#define  USBD_ZYNQ_EP_PHY_NBR_IS_OUT(ep_phy_nbr)              DEF_BIT_IS_CLR((ep_phy_nbr), DEF_BIT_00)
#define  USBD_ZYNQ_EP_PHY_NBR_IS_IN(ep_phy_nbr)               DEF_BIT_IS_SET((ep_phy_nbr), DEF_BIT_00)


/*
*********************************************************************************************************
*                                          LOCAL DATA TYPES
*
* Note(s) : (1) The USB device controller in the Zynq-7000 includes a simple descriptor model to enable the
*               controller to quickly respond to host requests.
*               Each of the 12 endpoints has two device Queue Heads (dQH); one for IN and the other for OUT
*               transfer types. There are a total of 24 device dQH's.
*               An endpoint data transfer is defined with one dQH and one or more linked list of device
*               Transfer Descriptors (dTD).
*           (2) The endpoint's device Queue Head (dQH) is where all transfers are managed. The dQH is a 48 byte
*               data structure, but must be aligned on 64-byte boundaries. The remaining 16 bytes will be used
*               to store the device Transfer Descriptor (dTD) link list information.
*
*                                          0            1                 N
*        --     +-----------+  Current  +-----+      +-----+           +-----+
*         |     |           |---------->| dTD |----->| dTD |--- .... ->| dTD |----|
*      48 Bytes |   dQH     |           +-----+      +-----+           +-----+
*         |     |           |      Next    |             |                |
*         |     |           |--------------|-------------|                |
*        --     +-----------+              |                              |
*         |     |  Head     |--------------|                              |
*         |     +-----------+                                             |
*         |     |  Tail     |---------------------------------------------|
*      16 Bytes +-----------+
*         |     | #Entries  |-----> Number of elements of the dTD's link list
*         |     |-----------|
*         |     | #dTD Rdy  |-----> Number of completed dTDs
*        --     ------------+
*
*
*           (3) The size of the dTD is 28 bytes. The dTD must be be aligned to 8-DWord boundaries.
*               the remaining 36 bytes are used to store extra information.
*
*        -    --   +---------------+      +------+               +-----+
*        |     |   |   dTD_Next    |----->| dTD  |----- ... ---->| dTD |
*        |     |   +---------------+      +------+               +-----+
*        |    dTD  |     Token     |
*        |     |   +---------------+         +---------+
*     dTD_EXT  |   | BufPtrs[0..4] |----| |->|xxxxxxxxx| 0       - BufPtr[0]   : Always points to the first byte in the data
*        |    --   +---------------+    | |  +---------+                         buffer that is available
*        |         |   BufAddr     |----|-|  |xxxxxxxxx| 1
*        -         +---------------+    |    +---------+
*                                       |    |xxxxxxxxx| 2        - BufAddr    : Always points to the beginning of the data buffer.
*                                       |    +---------+
*                                       |    |    .    |            +--------+
*                                       |    |    .    |            |xxxxxxxx| = Used block
*                                       |    |    .    |            +--------+
*                                       |    +---------+
*                                       |--->|         | n - 1      +--------+
*                                            +---------+            |        | = Free block
*                                            |         |  n         +--------+
*                                            +---------+
*
*           (4) For more information see the Xilinx Zynq-7000 Technical Reference Manual
*               (ug585-Zynq-7000-TRM.pdf)
*********************************************************************************************************
*/

typedef  struct usbd_zynq_usb_reg {
                                                                /* ------ IDENTIFICATION CONFIGURATION CONSTANTS ------ */
    CPU_REG32          ID;                                      /* R   0x000 Identification register                    */
    CPU_REG32          HWGENERAL;                               /* R   0x004 General hardware parameters                */
    CPU_REG32          HWHOST;                                  /* R   0x008 Host hardware parameters                   */
    CPU_REG32          HWDEVICE;                                /* R   0x00C Device hardware parameters                 */
    CPU_REG32          HWTXBUF;                                 /* R   0x010 TX Buffer hardware parameters              */
    CPU_REG32          HWRXBUF;                                 /* R   0x014 RX Buffer hardware parameters              */
    CPU_REG32          RESERVED0[26];                           /* Reserved bits.                                       */
                                                                /* ------------ GENERAL PURPOSE TIMERS ---------------  */
    CPU_REG32          GPTIMER0LD;                              /* R/W 0x080 General-purpose timer 0 load value         */
    CPU_REG32          GPTIMER0CTRL;                            /* R/W 0x084 General-purpose timer 0 control            */
    CPU_REG32          GPTIMER1LD;                              /* R/W 0x088 General-purpose timer 1 load value         */
    CPU_REG32          GPTIMER1CTRL;                            /* R/W 0x08C General-purpose timer 1 control            */
                                                                /* --------------- AXI INTERCONNECT ------------------- */
    CPU_REG32          SBUSCFG;                                 /* R/W 0x090 DMA Master AHB burst mode                  */
    CPU_REG32          RESERVED1[27];                           /* Reserved bits.                                       */
                                                                /* -------- CONTROLLER CAPABILITIES CONSTANTS --------- */
    CPU_REG16          CAPLENGTH;                               /* R   0x100 Capability register length                 */
    CPU_REG16          HCIVERSION;                              /* R   0x102 Host interface version number              */
    CPU_REG32          HCSPARAMS;                               /* R   0x104 Host controller structural parameters      */
    CPU_REG32          HCCPARAMS;                               /* R   0x108 Host controller capability parameters      */
    CPU_REG32          RESERVED2[5];                            /* Reserved bits.                                       */
    CPU_REG32          DCIVERSION;                              /* R   0x120 Device controller capability parameters    */
    CPU_REG32          DCCPARAMS;                               /* R   0x124 Device controller capability parameters    */
    CPU_REG32          RESERVED3[6];                            /* Reserved bits.                                       */
                                                                /* -------- INTERRUPTS AND ENDPOINT POINTERS ---------- */
    CPU_REG32          USBCMD;                                  /* R/W 0x140 USB command                                */
    CPU_REG32          USBSTS;                                  /* R/W 0x144 USB status                                 */
    CPU_REG32          USBINTR;                                 /* R/W 0x148 USB interrupt enable                       */
    CPU_REG32          FRINDEX;                                 /* R/W 0x14C USB frame index                            */
    CPU_REG32          RESERVED4;                               /* Reserved bits.                                       */
    CPU_REG32          DEV_ADDR;                                /* R/W 0x154 USB Device Address                         */
    CPU_REG32          EP_LST_ADDR;                             /* R/W 0x158 Next asynchronous list addr/addr of  ...   */
                                                                /*           ... of endpoint list in memory             */
    CPU_REG32          TTCTRL;                                  /* R/W 0x15C Asynchronous buffer stat for embedded TT   */
                                                                /* ------------------ MISCELLANEOUS ------------------- */
    CPU_REG32          BURSTSIZE;                               /* R/W 0x160 Programmable burst size                    */
    CPU_REG32          TXFILLTUNING;                            /* R/W 0x164 Host transmit pre-buffer packet tuning     */
    CPU_REG32          TXTTFILLTUNING;                          /* R/W 0x168 Host TT tx pre-buffer packet tuning        */
    CPU_REG32          IC_USB;                                  /* R/W 0x16C Low and fast speed control                 */
    CPU_REG32          ULPI_VIEWPORT;                           /* R/W 0x170 ULPI viewport.                             */
    CPU_REG32          RESERVED5;                               /* Reserved bits.                                       */
                                                                /* ---------------- ENDPOINT CONTROL ------------------ */
    CPU_REG32          ENDPTNAK;                                /* R/W 0x178 Endpoint NAK                               */
    CPU_REG32          ENDPTNAKEN;                              /* R/W 0x17C Endpoint NAK Enable                        */
    CPU_REG32          CONFIGFLAG;                              /* R   0x180 Configured flag register                   */
    CPU_REG32          PORTSC1;                                 /* R/W 0x184 Port status/control 1                      */
    CPU_REG32          RESERVED6[7];                            /* Reserved bits.                                       */
                                                                /* ------------------ MODE CONTROL -------------------- */
    CPU_REG32          OTGSC;                                   /* R/W 0x1A4 OTG status and control                     */
    CPU_REG32          USBMODE;                                 /* R/W 0x1A8 USB device mode                            */
                                                                /* -------- ENDPOINT CONFIGURATION AND CONTROL -------- */
    CPU_REG32          ENDPTSETUPSTAT;                          /* R/W 0x1AC Endpoint setup status                      */
    CPU_REG32          ENDPTPRIME;                              /* R/W 0x1B0 Endpoint initialization                    */
    CPU_REG32          ENDPTFLUSH;                              /* R/W 0x1B4 Endpoint de-initialization                 */
    CPU_REG32          ENDPTSTATUS;                             /* R   0x1B8 Endpoint status                            */
    CPU_REG32          ENDPTCOMPLETE;                           /* R/W 0x1BC Endpoint complete                          */
    CPU_REG32          ENDPTCTRLx[USBD_ZYNQ_EP_NBR_MAX];        /*           Endpoint control registers                 */
}  USBD_ZYNQ_REG;

                                                                /* --- ENDPOINT TRANSFER DESCRIPTOR (dTD) DATA TYPE --- */
typedef  struct  usbd_zynq_dtd {
    CPU_REG32          dTD_NextPtr;                             /* Next Link Pointer                                    */
    CPU_REG32          Token;                                   /* DTD token                                            */
    CPU_REG32          BufPtrs[5];                              /* Buffer pointer (Page n, n = [0..4])                  */
} USBD_ZYNQ_dTD;

                                                                /* -------------- dTD EXTENDED DATA TYPE -------------- */
typedef  struct  usbd_zynq_dtd_ext {
    CPU_REG32          dTD_NextPtr;                             /* Next Link Pointer                                    */
    CPU_REG32          Token;                                   /* DTD token                                            */
    CPU_REG32          BufPtrs[5];                              /* Buffer pointer (Page n, n = [0..4])                  */
    CPU_INT32U         BufAddr;                                 /* Buffer address                                       */
    CPU_INT32U         BufLen;                                  /* Buffer length                                        */
} USBD_ZYNQ_dTD_EXT;

                                                                /* -------- ENDPOINT QUEUE HEAD (dQH) DATA TYPE ------- */
typedef  struct  usbd_zynq_dqh {
    CPU_REG32          EpCap;                                   /* Endpoint capabilities                                */
    CPU_REG32          dTD_CurrPtr;                             /* Current dTD pointer                                  */
    USBD_ZYNQ_dTD      OverArea;                                /* Overlay Area                                         */
    CPU_INT32U         Reserved0;
    CPU_REG32          SetupBuf[2];                             /* Setup buffer                                         */
                                                                /* ------------------ dTD's LINK LIST ----------------- */
    USBD_ZYNQ_dTD_EXT *dTD_LstHeadPtr;                          /* dTD's link list head pointer                         */
    USBD_ZYNQ_dTD_EXT *dTD_LstTailPtr;                          /* dTD's link list tail pointer                         */
    CPU_REG32          dTD_LstNbrEntries;                       /* dTD's link list number of entries                    */
    CPU_INT32U         Unused;                                  /* Unused space                                         */
} USBD_ZYNQ_dQH;


typedef  struct  usbd_drv_data {
    MEM_POOL           dQH_MemPool;
    USBD_ZYNQ_dQH     *dQH_Tbl;
    MEM_POOL           dTD_MemPool;
} USBD_DRV_DATA;


/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/



/*
*********************************************************************************************************
*                             USB DEVICE CONTROLLER DRIVER API PROTOTYPES
*********************************************************************************************************
*/

static  void         USBD_DrvInit       (USBD_DRV     *p_drv,
                                         USBD_ERR     *p_err);

static  void         USBD_DrvStart      (USBD_DRV     *p_drv,
                                         USBD_ERR     *p_err);

static  void         USBD_DrvStop       (USBD_DRV     *p_drv);

static  CPU_BOOLEAN  USBD_DrvAddrSet    (USBD_DRV     *p_drv,
                                         CPU_INT08U    dev_addr);

static  void         USBD_DrvAddrEn     (USBD_DRV     *p_drv,
                                         CPU_INT08U    dev_addr);

static  CPU_BOOLEAN  USBD_DrvCfgSet     (USBD_DRV     *p_drv,
                                         CPU_INT08U    cfg_val);

static  void         USBD_DrvCfgClr     (USBD_DRV     *p_drv,
                                         CPU_INT08U    cfg_val);

static  CPU_INT16U   USBD_DrvGetFrameNbr(USBD_DRV     *p_drv);

static  void         USBD_DrvEP_Open    (USBD_DRV     *p_drv,
                                         CPU_INT08U    ep_addr,
                                         CPU_INT08U    ep_type,
                                         CPU_INT16U    max_pkt_size,
                                         CPU_INT08U    transaction_frame,
                                         USBD_ERR     *p_err);

static  void         USBD_DrvEP_Close   (USBD_DRV     *p_drv,
                                         CPU_INT08U    ep_addr);

static  CPU_INT32U   USBD_DrvEP_RxStart (USBD_DRV     *p_drv,
                                         CPU_INT08U    ep_addr,
                                         CPU_INT08U   *p_buf,
                                         CPU_INT32U    buf_len,
                                         USBD_ERR     *p_err);

static  CPU_INT32U   USBD_DrvEP_Rx      (USBD_DRV     *p_drv,
                                         CPU_INT08U    ep_addr,
                                         CPU_INT08U   *p_buf,
                                         CPU_INT32U    buf_len,
                                         USBD_ERR     *p_err);

static  void         USBD_DrvEP_RxZLP   (USBD_DRV     *p_drv,
                                         CPU_INT08U    ep_addr,
                                         USBD_ERR     *p_err);

static  CPU_INT32U   USBD_DrvEP_Tx      (USBD_DRV     *p_drv,
                                         CPU_INT08U    ep_addr,
                                         CPU_INT08U   *p_buf,
                                         CPU_INT32U    buf_len,
                                         USBD_ERR     *p_err);

static  void         USBD_DrvEP_TxStart (USBD_DRV     *p_drv,
                                         CPU_INT08U    ep_addr,
                                         CPU_INT08U   *p_buf,
                                         CPU_INT32U    buf_len,
                                         USBD_ERR     *p_err);


static  void         USBD_DrvEP_TxZLP   (USBD_DRV     *p_drv,
                                         CPU_INT08U    ep_addr,
                                         USBD_ERR     *p_err);

static  CPU_BOOLEAN  USBD_DrvEP_Abort   (USBD_DRV     *p_drv,
                                         CPU_INT08U    ep_addr);

static  CPU_BOOLEAN  USBD_DrvEP_Stall   (USBD_DRV     *p_drv,
                                         CPU_INT08U    ep_addr,
                                         CPU_BOOLEAN   state);

static  void         USBD_DrvISR_Handler(USBD_DRV     *p_drv);


/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/
                                                                /* ------------- dTD's LINK LIST FUNCTIONS ------------ */
static  CPU_BOOLEAN  USBD_Zynq_dTD_LstInsert(USBD_DRV    *p_drv,
                                             CPU_INT08U   ep_phy_nbr,
                                             CPU_INT08U  *p_data,
                                             CPU_INT16U   len);

static  CPU_BOOLEAN  USBD_Zynq_dTD_LstRd    (USBD_DRV    *p_drv,
                                             CPU_INT08U   ep_phy_nbr,
                                             CPU_INT16U   data_len,
                                             CPU_INT16U  *p_xfer_len,
                                             CPU_INT16U  *p_len_rem);

static  CPU_BOOLEAN  USBD_Zynq_dTD_LstRemove(USBD_DRV    *p_drv,
                                             CPU_INT08U   ep_phy_nbr);

static  CPU_BOOLEAN  USBD_Zynq_dTD_LstEmpty (USBD_DRV    *p_drv,
                                             CPU_INT08U   ep_phy_nbr);

static  void         USBD_Zynq_SetupProcess (USBD_DRV    *p_drv,
                                             CPU_INT08U   ep_log_nbr);

static  void         USBD_Zynq_SoftRst      (USBD_DRV    *p_drv);


/*
*********************************************************************************************************
*                                     LOCAL CONFIGURATION ERRORS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                  USB DEVICE CONTROLLER DRIVER API
*********************************************************************************************************
*/

USBD_DRV_API  USBD_DrvAPI_Zynq = { USBD_DrvInit,
                                   USBD_DrvStart,
                                   USBD_DrvStop,
                                   USBD_DrvAddrSet,
                                   USBD_DrvAddrEn,
                                   USBD_DrvCfgSet,
                                   USBD_DrvCfgClr,
                                   USBD_DrvGetFrameNbr,
                                   USBD_DrvEP_Open,
                                   USBD_DrvEP_Close,
                                   USBD_DrvEP_RxStart,
                                   USBD_DrvEP_Rx,
                                   USBD_DrvEP_RxZLP,
                                   USBD_DrvEP_Tx,
                                   USBD_DrvEP_TxStart,
                                   USBD_DrvEP_TxZLP,
                                   USBD_DrvEP_Abort,
                                   USBD_DrvEP_Stall,
                                   USBD_DrvISR_Handler,
};


/*
*********************************************************************************************************
*********************************************************************************************************
*                                     DRIVER INTERFACE FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                           USBD_DrvInit()
*
* Description : Initialize the device.
*
* Argument(s) : p_drv       Pointer to device driver structure.
*
*               p_err       Pointer to variable that will receive the return error code from this function :
*
*                               USBD_ERR_NONE       Device successfully initialized.
*                               USBD_ERR_ALLOC      Memory allocation failed.
*
* Return(s)   : none.
*
* Caller(s)   : USBD_DevInit() via 'p_drv_api->Init()'.
*
* Note(s)     : (1) Since the CPU frequency could be higher than OTG module clock, a timeout is needed
*                   to reset the OTG controller successfully.
*********************************************************************************************************
*/

static  void  USBD_DrvInit (USBD_DRV  *p_drv,
                            USBD_ERR  *p_err)
{
    USBD_DRV_BSP_API  *p_bsp_api;
    USBD_DRV_DATA     *p_drv_data;
    USBD_ZYNQ_REG     *p_reg;
    CPU_INT08U         ep_phy_nbr_max;
    CPU_SIZE_T         reqd_octets;
    CPU_INT16U         reg_to;
    LIB_ERR            err_lib;

                                                                /* Allocate driver internal data.                       */
    p_drv->DataPtr = Mem_HeapAlloc(sizeof(USBD_DRV_DATA),
                                   sizeof(CPU_DATA),
                                  &reqd_octets,
                                  &err_lib);
    if (p_drv->DataPtr == (void *)0) {
       *p_err = USBD_ERR_ALLOC;
        return;
    }

    ep_phy_nbr_max = USBD_EP_MaxPhyNbrGet(p_drv->DevNbr);       /* Get max phy EP used by the stack.                    */

    if (ep_phy_nbr_max == USBD_EP_PHY_NONE) {
        *p_err = USBD_ERR_FAIL;
         return;
    }
    ep_phy_nbr_max++;
    p_drv_data = (USBD_DRV_DATA  *)p_drv->DataPtr;

    Mem_PoolCreate(        &p_drv_data->dQH_MemPool,            /* Create EP Queue Head memory pool ...                 */
                   (void  *)0,
                            0u,
                            1u,
                           (sizeof(USBD_ZYNQ_dQH) * ep_phy_nbr_max),
                            USBD_ZYNQ_ALIGN_OCTECTS_dQH,
                           &reqd_octets,
                           &err_lib);
    if (err_lib != LIB_MEM_ERR_NONE) {
       *p_err = USBD_ERR_ALLOC;
        return;
    }


    Mem_PoolCreate(        &p_drv_data->dTD_MemPool,           /* Create EP device transfer descriptor memory pool.    */
                   (void  *)0,
                            0u,
                            ep_phy_nbr_max * 1u,
                           (sizeof(USBD_ZYNQ_dTD_EXT)),
                            USBD_ZYNQ_ALIGN_OCTECTS_dTD,
                           &reqd_octets,
                           &err_lib);
    if (err_lib != LIB_MEM_ERR_NONE) {
       *p_err = USBD_ERR_ALLOC;
        return;
    }

    p_drv_data->dQH_Tbl = (USBD_ZYNQ_dQH *)Mem_PoolBlkGet(&p_drv_data->dQH_MemPool,
                                                          (sizeof(USBD_ZYNQ_dQH) * (ep_phy_nbr_max)),
                                                          &err_lib);
    if (err_lib != LIB_MEM_ERR_NONE) {
       *p_err = USBD_ERR_ALLOC;
        return;
    }

    Mem_Clr((void  *) p_drv_data->dQH_Tbl,
                     (sizeof(USBD_ZYNQ_dQH) * (ep_phy_nbr_max)));

    p_bsp_api = p_drv->BSP_API_Ptr;                             /* Get driver BSP API reference.                        */

    p_bsp_api->Init(p_drv);                                     /* Call board/chip specific device controller ...       */
                                                                /* ... initialization function.                         */

    p_reg         = (USBD_ZYNQ_REG *)(p_drv->CfgPtr->BaseAddr);
                                                                /* Reset controller (see Note #1)                       */
    p_reg->USBCMD = USBD_ZYNQ_USBCMD_RST;

    reg_to = USBD_ZYNQ_REG_TO;
    while (reg_to > 0) {
        reg_to--;
    }

    p_reg->USBMODE = USBD_ZYNQ_USBMODE_CM_DEV;                  /* Set device mode                                      */


    p_reg->USBINTR     = DEF_BIT_NONE;                          /* Disable all interrupts                               */
    p_reg->EP_LST_ADDR = (CPU_INT32U)p_drv_data->dQH_Tbl;

    DEF_BIT_SET(p_reg->USBMODE, USBD_ZYNQ_USBMODE_SLOM);        /* Disable setup lockout                                */
    DEF_BIT_CLR(p_reg->USBMODE, USBD_ZYNQ_USBMODE_SDIS);        /* Stream disable mode                                  */

    USBD_Zynq_SoftRst(p_drv);                                   /* Perform software reset                               */

    DEF_BIT_CLR(p_reg->USBCMD, USBD_ZYNQ_USBCMD_ITC_MASK);

   *p_err = USBD_ERR_NONE;
}


/*
*********************************************************************************************************
*                                           USBD_DrvStart()
*
* Description : Start device operation :
*
*                   (1) Enable device controller bus state interrupts.
*                   (2) Call board/chip specific connect function.
*
* Argument(s) : p_drv       Pointer to device driver structure.
*
*               p_err       Pointer to variable that will receive the return error code from this function :
*
*                               USBD_ERR_NONE    Device successfully connected.
*
* Return(s)   : none.
*
* Caller(s)   : USBD_DevStart() via 'p_drv_api->Start()'.
*
* Note(s)     : Typically, the start function activates the pull-down on the D- pin to simulate
*               attachment to host. Some MCUs/MPUs have an internal pull-down that is activated by a
*               device controller register; for others, this may be a GPIO pin. Additionally, interrupts
*               for reset and suspend are activated.
*********************************************************************************************************
*/

static  void  USBD_DrvStart (USBD_DRV  *p_drv,
                             USBD_ERR  *p_err)
{
    USBD_DRV_BSP_API  *p_bsp_api;
    USBD_ZYNQ_REG     *p_reg;


    p_bsp_api = p_drv->BSP_API_Ptr;                             /* Get driver BSP API reference.                        */
    p_reg     = (USBD_ZYNQ_REG *)(p_drv->CfgPtr->BaseAddr);

    p_reg->USBINTR = USBD_ZYNQ_USB_INT_UR                       /* Enable the Reset and Suspend interrupt               */
                   | USBD_ZYNQ_USB_INT_SL;
                                                                /* Set the RUN bit                                      */
#if 0
    DEF_BIT_SET(p_reg->PORTSC1, DEF_BIT_24);                    /* Force FS. Debugging purposes only.                   */
#endif

    DEF_BIT_SET(p_reg->USBCMD,  USBD_ZYNQ_USBCMD_RUN);

    p_bsp_api->Conn();                                          /* Call board/chip specific connect function.           */

   *p_err = USBD_ERR_NONE;
}


/*
*********************************************************************************************************
*                                           USBD_DrvStop()
*
* Description : Stop device operation.
*
* Argument(s) : p_drv       Pointer to device driver structure.
*
* Return(s)   : none.
*
* Caller(s)   : USBD_DevStop() via 'p_drv_api->Stop()'.
*
* Note(s)     : Typically, the stop function performs the following operations:
*               (1) Clear and disable USB interrupts.
*               (2) Disconnect from the USB host (e.g, reset the pull-down on the D- pin).
*********************************************************************************************************
*/

static  void  USBD_DrvStop (USBD_DRV  *p_drv)
{
    USBD_DRV_BSP_API  *p_bsp_api;
    USBD_ZYNQ_REG     *p_reg;


    p_bsp_api = p_drv->BSP_API_Ptr;                             /* Get driver BSP API reference.                        */
    p_reg     = (USBD_ZYNQ_REG *)(p_drv->CfgPtr->BaseAddr);

    p_reg->USBINTR = DEF_BIT_NONE;

    p_bsp_api->Disconn();
                                                                /* Clear the RUN bit                                    */
    DEF_BIT_CLR(p_reg->USBCMD,  USBD_ZYNQ_USBCMD_RUN);
}


/*
*********************************************************************************************************
*                                          USBD_DrvAddrSet()
*
* Description : Assign an address to device.
*
* Argument(s) : p_drv       Pointer to device driver structure.
*
*               dev_addr    Device address assigned by the host.
*
* Return(s)   : DEF_OK,   if NO error(s).
*
*               DEF_FAIL, otherwise.
*
* Caller(s)   : USBD_StdReqDev() via 'p_drv_api->AddrSet()'.
*
* Note(s)     : (1) For device controllers that have hardware assistance to enable the device address after
*                   the status stage has completed, the assignment of the device address can also be
*                   combined with enabling the device address mode.
*
*               (2) For device controllers that change the device address immediately, without waiting the
*                   status phase to complete, see USBD_DrvAddrEn().
*********************************************************************************************************
*/

static  CPU_BOOLEAN  USBD_DrvAddrSet (USBD_DRV    *p_drv,
                                      CPU_INT08U   dev_addr)
{
    USBD_ZYNQ_REG  *p_reg;


    p_reg           = (USBD_ZYNQ_REG *)(p_drv->CfgPtr->BaseAddr);
    p_reg->DEV_ADDR = ((dev_addr << 25) & USBD_ZYNQ_DEV_ADDR_USBADDR_MASK) |
                                          USBD_ZYNQ_DEV_ADDR_USBADDRA;

    return (DEF_OK);
}


/*
*********************************************************************************************************
*                                          USBD_DrvAddrEn()
*
* Description : Enable address on device.
*
* Argument(s) : p_drv       Pointer to device driver structure.
*
*               dev_addr    Device address assigned by the host.
*
* Return(s)   : none.
*
* Caller(s)   : USBD_StdReqHandler() via 'p_drv_api->AddrEn()'.
*
* Note(s)     : (1) For device controllers that have hardware assistance to enable the device address after
*                   the status stage has completed, no operation needs to be performed.
*
*               (2) For device controllers that change the device address immediately, without waiting the
*                   status phase to complete, the device address must be set and enabled.
*********************************************************************************************************
*/

static  void  USBD_DrvAddrEn (USBD_DRV    *p_drv,
                              CPU_INT08U   dev_addr)
{
    (void)p_drv;
    (void)dev_addr;
}


/*
*********************************************************************************************************
*                                          USBD_DrvCfgSet()
*
* Description : Bring device into configured state.
*
* Argument(s) : p_drv       Pointer to device driver structure.
*
*               cfg_val     Configuration value.
*
* Return(s)   : DEF_OK,   if NO error(s).
*
*               DEF_FAIL, otherwise.
*
* Caller(s)   : USBD_CfgOpen() via 'p_drv_api->CfgSet()'.
*
* Note(s)     : Typically, the set configuration function sets the device as configured. For some
*               controllers, this may not be necessary.
*********************************************************************************************************
*/

static  CPU_BOOLEAN  USBD_DrvCfgSet (USBD_DRV    *p_drv,
                                     CPU_INT08U   cfg_val)
{
    (void)p_drv;
    (void)cfg_val;

    return (DEF_OK);
}


/*
*********************************************************************************************************
*                                          USBD_DrvCfgClr()
*
* Description : Bring device into de-configured state.
*
* Argument(s) : p_drv       Pointer to device driver structure.
*
*               cfg_val     Configuration value.
*
* Return(s)   : none.
*
* Caller(s)   : USBD_CfgClose() via 'p_drv_api->CfgClr()'.
*
* Note(s)     : (1) Typically, the clear configuration function sets the device as not being configured.
*                   For some controllers, this may not be necessary.
*
*               (2) This functions in invoked after a bus reset or before the status stage of some
*                   SET_CONFIGURATION requests.
*********************************************************************************************************
*/

static  void  USBD_DrvCfgClr (USBD_DRV    *p_drv,
                              CPU_INT08U   cfg_val)
{
    (void)p_drv;
    (void)cfg_val;
}


/*
*********************************************************************************************************
*                                        USBD_DrvGetFrameNbr()
*
* Description : Retrieve current frame number.
*
* Argument(s) : p_drv       Pointer to device driver structure.
*
* Return(s)   : Frame number.
*
* Caller(s)   : USBD_EP_Open() via 'p_drv_api->GetFrameNbr()'.
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  CPU_INT16U  USBD_DrvGetFrameNbr (USBD_DRV  *p_drv)
{
    CPU_INT16U      frame_nbr;
    USBD_ZYNQ_REG  *p_reg;


    p_reg = (USBD_ZYNQ_REG *)(p_drv->CfgPtr->BaseAddr);

    frame_nbr = (p_reg->FRINDEX >> 3u);


    return (frame_nbr);
}


/*
*********************************************************************************************************
*                                          USBD_DrvEP_Open()
*
* Description : Open and configure a device endpoint, given its characteristics (e.g., endpoint type,
*               endpoint address, maximum packet size, etc).
*
* Argument(s) : p_drv               Pointer to device driver structure.
*
*               ep_addr             Endpoint address.
*
*               ep_type             Endpoint type :
*
*                                       USBD_EP_TYPE_CTRL,
*                                       USBD_EP_TYPE_ISOC,
*                                       USBD_EP_TYPE_BULK,
*                                       USBD_EP_TYPE_INTR.
*
*               max_pkt_size        Maximum packet size.
*
*               transaction_frame   Endpoint transactions per frame.
*
*               p_err       Pointer to variable that will receive the return error code from this function :
*
*                               USBD_ERR_NONE               Endpoint successfully opened.
*                               USBD_ERR_EP_INVALID_ADDR    Invalid endpoint address.
*
* Return(s)   : none.
*
* Caller(s)   : USBD_EP_Open() via 'p_drv_api->EP_Open()',
*               USBD_CtrlOpen().
*
* Note(s)     : (1) Typically, the endpoint open function performs the following operations:
*
*                   (a) Validate endpoint address, type and maximum packet size.
*                   (b) Configure endpoint information in the device controller. This may include not
*                       only assigning the type and maximum packet size, but also making certain that
*                       the endpoint is successfully configured (or realized or mapped). For some
*                       device controllers, this may not be necessary.
*
*               (2) If the endpoint address is valid, then the endpoint open function should validate
*                   the attributes allowed by the hardware endpoint :
*
*                   (a) The maximum packet size 'max_pkt_size' should be validated to match hardware
*                       capabilities.
*********************************************************************************************************
*/

static  void  USBD_DrvEP_Open (USBD_DRV    *p_drv,
                               CPU_INT08U   ep_addr,
                               CPU_INT08U   ep_type,
                               CPU_INT16U   max_pkt_size,
                               CPU_INT08U   transaction_frame,
                               USBD_ERR    *p_err)
{
    USBD_ZYNQ_dQH     *p_dqh;
    USBD_ZYNQ_REG     *p_reg;
    USBD_DRV_DATA     *p_drv_data;
    CPU_BOOLEAN        ep_dir;
    CPU_INT08U         ep_log_nbr;
    CPU_INT08U         ep_phy_nbr;
    CPU_INT32U         reg_val;
    CPU_SR_ALLOC();


    (void)transaction_frame;

    ep_dir     = USBD_EP_IS_IN(ep_addr);                        /* Get EP direction.                                    */
    ep_log_nbr = USBD_EP_ADDR_TO_LOG(ep_addr);                  /* Get EP logical  number.                              */
    ep_phy_nbr = USBD_EP_ADDR_TO_PHY(ep_addr);                  /* Get EP physical number.                              */

    p_reg      = (USBD_ZYNQ_REG *)(p_drv->CfgPtr->BaseAddr);
    p_drv_data = (USBD_DRV_DATA *)(p_drv->DataPtr);

    p_dqh      = &p_drv_data->dQH_Tbl[ep_phy_nbr];
                                                                /* ---------------- ARGUMENTS CHECKING ---------------- */
    if ((ep_log_nbr == 0) &&
        (ep_type    != USBD_EP_TYPE_CTRL)) {
       *p_err = USBD_ERR_EP_INVALID_ADDR;
        return;
    }

                                                                /* -------------- ENDPOINT CONFIGURATION -------------- */
                                                                /* Prepare locally the EP cfg.                          */
    reg_val = USBD_ZYNQ_ENDPTCTRL_TX_EN |                       /* Enable EP Tx (i.e. IN direction).                    */
              USBD_ZYNQ_ENDPTCTRL_RX_EN;                        /* Enable EP Rx (i.e. OUT direction).                   */

    switch (ep_type) {                                          /* Set the EP Tx and Rx type.                           */
        case USBD_EP_TYPE_CTRL:
             DEF_BIT_SET(reg_val, USBD_ZYNQ_ENDPTCTRL_TX_TYPE_CTRL |
                                  USBD_ZYNQ_ENDPTCTRL_RX_TYPE_CTRL);
             break;

        case USBD_EP_TYPE_ISOC:
             DEF_BIT_SET(reg_val, USBD_ZYNQ_ENDPTCTRL_TX_TYPE_ISOC |
                                  USBD_ZYNQ_ENDPTCTRL_RX_TYPE_ISOC);
                                                                /* Reset Tx & Rx data toggle.                           */
             DEF_BIT_SET(reg_val, USBD_ZYNQ_ENDPTCTRL_TX_TOGGLE_RST);
             DEF_BIT_SET(reg_val, USBD_ZYNQ_ENDPTCTRL_RX_TOGGLE_RST);
             break;

        case USBD_EP_TYPE_INTR:
             DEF_BIT_SET(reg_val, USBD_ZYNQ_ENDPTCTRL_TX_TYPE_INT |
                                  USBD_ZYNQ_ENDPTCTRL_RX_TYPE_INT);
                                                                /* Reset Tx & Rx data toggle.                           */
             DEF_BIT_SET(reg_val, USBD_ZYNQ_ENDPTCTRL_TX_TOGGLE_RST);
             DEF_BIT_SET(reg_val, USBD_ZYNQ_ENDPTCTRL_RX_TOGGLE_RST);
             break;

        case USBD_EP_TYPE_BULK:
             DEF_BIT_SET(reg_val, USBD_ZYNQ_ENDPTCTRL_TX_TYPE_BULK |
                                  USBD_ZYNQ_ENDPTCTRL_RX_TYPE_BULK);
                                                                /* Reset Tx & Rx data toggle.                           */
             DEF_BIT_SET(reg_val, USBD_ZYNQ_ENDPTCTRL_TX_TOGGLE_RST);
             DEF_BIT_SET(reg_val, USBD_ZYNQ_ENDPTCTRL_RX_TOGGLE_RST);
             break;

        default:                                                /* 'default' case intentionally empty.                  */
             break;
    }

    CPU_CRITICAL_ENTER();
    if (ep_dir == DEF_FALSE) {                                  /* OUT Endpoints                                        */
                                                                /* Reset reg upper half to keep only Rx related bits.   */
        reg_val &= USBD_ZYNQ_ENDPTCTRL_RX_CFG_MASK;
        DEF_BIT_CLR(p_reg->ENDPTCTRLx[ep_log_nbr], USBD_ZYNQ_ENDPTCTRL_RX_CFG_MASK);
    } else {                                                    /* IN Endpoints                                         */
                                                                /* Reset reg lower half to keep only Tx related bits.   */
        reg_val &= USBD_ZYNQ_ENDPTCTRL_TX_CFG_MASK;
        DEF_BIT_CLR(p_reg->ENDPTCTRLx[ep_log_nbr], USBD_ZYNQ_ENDPTCTRL_TX_CFG_MASK);
    }

    DEF_BIT_SET(p_reg->ENDPTCTRLx[ep_log_nbr], reg_val);        /* Apply the local EP cfg to EP ctrl register.          */

                                                                /* --------- ENDPOINT QUEUE HEAD CONFIGURATION -------- */
    reg_val = (max_pkt_size << 16) & USBD_ZYNQ_dQH_EP_CAP_MAX_LEN_MASK;

    if ((ep_type == USBD_EP_TYPE_CTRL) &&
        (ep_dir  == DEF_FALSE)) {
        DEF_BIT_SET(reg_val, USBD_ZYNQ_dQH_EP_CAP_IOS);
        DEF_BIT_SET(p_reg->ENDPTSETUPSTAT, DEF_BIT32(ep_log_nbr));
    }

    if ((ep_type == USBD_EP_TYPE_CTRL) ||
        (ep_type == USBD_EP_TYPE_BULK)) {
        DEF_BIT_SET(reg_val, USBD_ZYNQ_dQH_EP_CAP_ZLTS);
    }

    CPU_DCACHE_RANGE_FLUSH(p_dqh, sizeof(USBD_ZYNQ_dQH));   /* Invalidate (clear) the cached RAM block, so that the */
                                                                /* next CPU read will be from RAM again.                */
    p_dqh->EpCap = reg_val;

    if (ep_dir == DEF_TRUE) {
        p_dqh->OverArea.dTD_NextPtr = USBD_ZYNQ_dTD_dTD_NEXT_TERMINATE;
    }

    CPU_DCACHE_RANGE_INV(p_dqh, sizeof(USBD_ZYNQ_dQH));        /* Write cached memory block back to RAM.               */

    CPU_CRITICAL_EXIT();

    *p_err = USBD_ERR_NONE;
}


/*
*********************************************************************************************************
*                                         USBD_DrvEP_Close()
*
* Description : Close a device endpoint, and uninitialize/clear endpoint configuration in hardware.
*
* Argument(s) : p_drv       Pointer to device driver structure.
*
*               ep_addr     Endpoint address.
*
* Return(s)   : none.
*
* Caller(s)   : USBD_EP_Close() via 'p_drv_api->EP_Close()',
*               USBD_CtrlOpen().
*
* Note(s)     : Typically, the endpoint close function clears the endpoint information in the device
*               controller. For some controllers, this may not be necessary.
*********************************************************************************************************
*/

static  void  USBD_DrvEP_Close (USBD_DRV    *p_drv,
                                CPU_INT08U   ep_addr)
{
    CPU_INT08U  ep_phy_nbr;


    ep_phy_nbr = USBD_EP_ADDR_TO_PHY(ep_addr);
    (void)USBD_Zynq_dTD_LstEmpty(p_drv, ep_phy_nbr);
}


/*
*********************************************************************************************************
*                                        USBD_DrvEP_RxStart()
*
* Description : Configure endpoint with buffer to receive data.
*
* Argument(s) : p_drv       Pointer to device driver structure.
*
*               ep_addr     Endpoint address.
*
*               p_buf       Pointer to data buffer.
*
*               buf_len     Length of the buffer.
*
*               p_err       Pointer to variable that will receive the return error code from this function :
*
*                               USBD_ERR_NONE   Receive successfully configured.
*                               USBD_ERR_RX     Generic Rx error.
*
* Return(s)   : none.
*
* Caller(s)   : USBD_EP_Rx() via 'p_drv_api->EP_Rx()',
*               USBD_EP_Process().
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  CPU_INT32U  USBD_DrvEP_RxStart (USBD_DRV    *p_drv,
                                        CPU_INT08U   ep_addr,
                                        CPU_INT08U  *p_buf,
                                        CPU_INT32U   buf_len,
                                        USBD_ERR    *p_err)
{
    USBD_ZYNQ_REG     *p_reg;
    CPU_INT08U         ep_phy_nbr;
    CPU_INT32U         ep_pkt_len;
    CPU_BOOLEAN        valid;


                                                                /* ----------------- ARGUMENT CHECKING ---------------- */
    ep_phy_nbr = USBD_EP_ADDR_TO_PHY(ep_addr);
    p_reg      = (USBD_ZYNQ_REG *)(p_drv->CfgPtr->BaseAddr);

    DEF_BIT_CLR(p_reg->USBINTR, USBD_ZYNQ_USB_INT_U);           /* Disable interrupts.                                  */

                                                                /* Force one transaction.                               */
    ep_pkt_len =  DEF_MIN(buf_len,
                          USBD_ZYNQ_dTD_TOKEN_TOTAL_BYTE_MAX);

    CPU_DCACHE_RANGE_FLUSH(p_buf, buf_len);                 /* Invalidate (clear) the cached RAM block, so that the */
                                                                /* next CPU read will be from RAM again.                */

                                                                /* Case 1: one transaction                              */
    if (buf_len <= USBD_ZYNQ_dTD_TOKEN_TOTAL_BYTE_MAX) {

        valid = USBD_Zynq_dTD_LstInsert(            p_drv,
                                                    ep_phy_nbr,
                                                    p_buf,
                                        (CPU_INT16U)ep_pkt_len);
    }

    DEF_BIT_SET(p_reg->USBINTR, USBD_ZYNQ_USB_INT_U);           /* Enable interrupts.                                   */

    if (valid == DEF_FAIL) {
       *p_err = USBD_ERR_RX;
    } else {
       *p_err = USBD_ERR_NONE;
    }

    return (ep_pkt_len);
}


/*
*********************************************************************************************************
*                                           USBD_DrvEP_Rx()
*
* Description : Receive the specified amount of data from device endpoint.
*
* Argument(s) : p_drv       Pointer to device driver structure.
*
*               ep_addr     Endpoint address.
*
*               p_buf       Pointer to data buffer.
*
*               buf_len     Length of the buffer.
*
*               p_err       Pointer to variable that will receive the return error code from this function :
*
*                               USBD_ERR_NONE   Data successfully received.
*                               USBD_ERR_RX     Generic Rx error.
*
* Return(s)   : Number of octets received, if NO error(s).
*
*               0,                         otherwise.
*
* Caller(s)   : USBD_EP_Rx() via 'p_drv_api->EP_Rx()',
*               USBD_EP_Process().
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  CPU_INT32U  USBD_DrvEP_Rx (USBD_DRV    *p_drv,
                                   CPU_INT08U   ep_addr,
                                   CPU_INT08U  *p_buf,
                                   CPU_INT32U   buf_len,
                                   USBD_ERR    *p_err)
{
    USBD_ZYNQ_REG  *p_reg;
    CPU_INT08U      ep_phy_nbr;
    CPU_INT16U      len_rem;
    CPU_INT16U      xfer_len;
    CPU_INT16U      tot_xfer_len;
    CPU_BOOLEAN     xfer;


    (void)p_buf;

    ep_phy_nbr   = USBD_EP_ADDR_TO_PHY(ep_addr);
    p_reg        = (USBD_ZYNQ_REG *)(p_drv->CfgPtr->BaseAddr);
    xfer         = DEF_FAIL;
    tot_xfer_len = 0u;
    xfer_len     = 0u;

    DEF_BIT_CLR(p_reg->USBINTR, USBD_ZYNQ_USB_INT_U);           /* Disable interrupts.                                  */

    CPU_DCACHE_RANGE_FLUSH(p_buf, buf_len);                 /* Invalidate (clear) the cached RAM block, so that the */
                                                                /* next CPU read will be from RAM again.                */

    if (buf_len <= USBD_ZYNQ_dTD_TOKEN_TOTAL_BYTE_MAX) {        /* Case 1: one transaction.                             */
                                                                /* Read data from the first dTD in the link list.       */
        xfer = USBD_Zynq_dTD_LstRd(             p_drv,
                                                ep_phy_nbr,
                                   (CPU_INT16U) buf_len,
                                               &xfer_len,
                                               &len_rem);

        USBD_Zynq_dTD_LstRemove(p_drv, ep_phy_nbr);
        tot_xfer_len = xfer_len;
    } else {
        ;                                                       /* !!!! Multiple transaction not implemented yet.       */
    }

    DEF_BIT_SET(p_reg->USBINTR, USBD_ZYNQ_USB_INT_U);           /* Enable interrupts                                    */

    if (xfer == DEF_FAIL) {
        *p_err = USBD_ERR_RX;
    } else {
        *p_err = USBD_ERR_NONE;
    }

    return (tot_xfer_len);
}


/*
*********************************************************************************************************
*                                         USBD_DrvEP_RxZLP()
*
* Description : Receive zero-length packet from endpoint.
*
* Argument(s) : p_drv       Pointer to device driver structure.
*
*               ep_addr     Endpoint address.
*
*               p_err       Pointer to variable that will receive the return error code from this function :
*
*                               USBD_ERR_NONE   Zero-length packet successfully received.
*                               USBD_ERR_RX     Generic Rx error.
*
* Return(s)   : none.
*
* Caller(s)   : USBD_EP_RxZLP() via 'p_drv_api->EP_RxZLP()'.
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  void  USBD_DrvEP_RxZLP (USBD_DRV    *p_drv,
                                CPU_INT08U   ep_addr,
                                USBD_ERR    *p_err)
{
    CPU_INT08U   ep_phy_nbr;
    CPU_BOOLEAN  valid;


    ep_phy_nbr = USBD_EP_ADDR_TO_PHY(ep_addr);
    valid      = USBD_Zynq_dTD_LstInsert(              p_drv,
                                                       ep_phy_nbr,
                                         (CPU_INT08U *)0,
                                                       0u);
    if (valid != DEF_OK) {
       *p_err = USBD_ERR_RX;
    } else {
       *p_err = USBD_ERR_NONE;
    }
}


/*
*********************************************************************************************************
*                                           USBD_DrvEP_Tx()
*
* Description : Configure endpoint with buffer to transmit data.
*
* Argument(s) : p_drv       Pointer to device driver structure.
*
*               ep_addr     Endpoint address.
*
*               p_buf       Pointer to buffer of data that will be transmitted.
*
*               buf_len     Number of octets to transmit.
*
*               p_err       Pointer to variable that will receive the return error code from this function :
*
*                               USBD_ERR_NONE   Transmit successfully configured.
*                               USBD_ERR_TX     Generic Tx error.
*
* Return(s)   : Number of octets transmitted, if NO error(s).
*
*               0,                            otherwise.
*
* Caller(s)   : USBD_EP_Tx() via 'p_drv_api->EP_Tx()',
*               USBD_EP_Process().
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  CPU_INT32U  USBD_DrvEP_Tx (USBD_DRV    *p_drv,
                                   CPU_INT08U   ep_addr,
                                   CPU_INT08U  *p_buf,
                                   CPU_INT32U   buf_len,
                                   USBD_ERR    *p_err)
{
    (void)p_drv;
    (void)ep_addr;
    (void)p_buf;

    buf_len = DEF_MIN(buf_len, USBD_ZYNQ_dTD_TOKEN_TOTAL_BYTE_MAX);
   *p_err   = USBD_ERR_NONE;

    return (buf_len);
}

/*
*********************************************************************************************************
*                                        USBD_DrvEP_TxStart()
*
* Description : Transmit the specified amount of data to device endpoint.
*
* Argument(s) : p_drv       Pointer to device driver structure.
*
*               ep_addr     Endpoint address.
*
*               p_buf       Pointer to buffer of data that will be transmitted.
*
*               buf_len     Number of octets to transmit.
*
*               p_err       Pointer to variable that will receive the return error code from this function :
*
*                               USBD_ERR_NONE   Data successfully transmitted.
*                               USBD_ERR_TX     Generic Tx error.
*
* Return(s)   : none.
*
* Caller(s)   : USBD_EP_Tx() via 'p_drv_api->EP_TxStart()',
*               USBD_EP_Process().
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  void  USBD_DrvEP_TxStart (USBD_DRV    *p_drv,
                                  CPU_INT08U   ep_addr,
                                  CPU_INT08U  *p_buf,
                                  CPU_INT32U   buf_len,
                                  USBD_ERR    *p_err)
{
    USBD_ZYNQ_REG  *p_reg;
    CPU_INT08U      ep_phy_nbr;
    CPU_BOOLEAN     valid;


    p_reg      = (USBD_ZYNQ_REG *)(p_drv->CfgPtr->BaseAddr);
    ep_phy_nbr = USBD_EP_ADDR_TO_PHY(ep_addr);

    buf_len = DEF_MIN(buf_len, USBD_ZYNQ_dTD_TOKEN_TOTAL_BYTE_MAX);

    DEF_BIT_CLR(p_reg->USBINTR, USBD_ZYNQ_USB_INT_U);           /* Disable interrupts.                                  */

    CPU_DCACHE_RANGE_INV(p_buf, buf_len);                      /* Write the cached memory block back to RAM, before    */
                                                                /* initiating the DMA transfer.                         */

    valid = USBD_Zynq_dTD_LstInsert(            p_drv,
                                                ep_phy_nbr,
                                                p_buf,
                                    (CPU_INT16U)buf_len);

    DEF_BIT_SET(p_reg->USBINTR, USBD_ZYNQ_USB_INT_U);           /* Enable interrupts.                                   */

    if (valid == DEF_FAIL) {
       *p_err = USBD_ERR_TX;
    } else {
       *p_err = USBD_ERR_NONE;
    }
}


/*
*********************************************************************************************************
*                                         USBD_DrvEP_TxZLP()
*
* Description : Transmit zero-length packet from endpoint.
*
* Argument(s) : p_drv       Pointer to device driver structure.
*
*               ep_addr     Endpoint address.
*
*               p_err       Pointer to variable that will receive the return error code from this function :
*
*                               USBD_ERR_NONE   Zero-length packet successfully transmitted.
*                               USBD_ERR_TX     Generic Tx error.
*
* Return(s)   : none.
*
* Caller(s)   : USBD_EP_Tx() via 'p_drv_api->EP_TxZLP()',
*               USBD_EP_TxZLP(),
*               USBD_EP_Process().
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  void  USBD_DrvEP_TxZLP (USBD_DRV    *p_drv,
                                CPU_INT08U   ep_addr,
                                USBD_ERR    *p_err)
{
    CPU_INT08U   ep_phy_nbr;
    CPU_BOOLEAN  valid;


    ep_phy_nbr = USBD_EP_ADDR_TO_PHY(ep_addr);
    valid      = USBD_Zynq_dTD_LstInsert(              p_drv,
                                                       ep_phy_nbr,
                                         (CPU_INT08U *)0,
                                                       0u);
    if (valid != DEF_OK) {
       *p_err = USBD_ERR_TX;
    } else {
       *p_err = USBD_ERR_NONE;
    }
}


/*
*********************************************************************************************************
*                                         USBD_DrvEP_Abort()
*
* Description : Abort any pending transfer on endpoint.
*
* Argument(s) : p_drv       Pointer to device driver structure.
*
*               ep_addr     Endpoint Address.
*
* Return(s)   : DEF_OK,   if NO error(s).
*
*               DEF_FAIL, otherwise.
*
* Caller(s)   : USBD_URB_Abort() via 'p_drv_api->EP_Abort()'.
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  CPU_BOOLEAN  USBD_DrvEP_Abort (USBD_DRV    *p_drv,
                                       CPU_INT08U   ep_addr)
{
    USBD_ZYNQ_REG     *p_reg;
    USBD_DRV_DATA     *p_drv_data;
    CPU_INT32U         ix;
    CPU_INT32U         entries;
    CPU_BOOLEAN        ok;
    CPU_INT08U         ep_phy_nbr;
    CPU_INT08U         ep_log_nbr;
    CPU_INT32U         ep_flush;
    CPU_BOOLEAN        flush_done;
    CPU_INT32U         nbr_retries;
    CPU_INT32U         reg_to;


    ep_log_nbr = USBD_EP_ADDR_TO_LOG(ep_addr);
    p_reg      = (USBD_ZYNQ_REG *)(p_drv->CfgPtr->BaseAddr);
    p_drv_data = (USBD_DRV_DATA *)p_drv->DataPtr;
    ok         = DEF_OK;
    ep_phy_nbr = USBD_EP_ADDR_TO_PHY(ep_addr);

    CPU_DCACHE_RANGE_FLUSH(&(p_drv_data->dQH_Tbl[ep_phy_nbr].dTD_LstNbrEntries), sizeof(CPU_REG32));

    entries    = p_drv_data->dQH_Tbl[ep_phy_nbr].dTD_LstNbrEntries;


    if (USBD_EP_IS_IN(ep_addr)) {
        ep_flush = USBD_ZYNQ_ENDPTxxx_GET_TX_BITS(ep_log_nbr);
    } else {
        ep_flush = USBD_ZYNQ_ENDPTxxx_GET_RX_BITS(ep_log_nbr);
    }

    nbr_retries = USBD_ZYNQ_MAX_RETRIES;
    flush_done  = DEF_FALSE;

    while ((flush_done  == DEF_FALSE) &&
           (nbr_retries >  0u)) {

        p_reg->ENDPTFLUSH = ep_flush;

        reg_to = USBD_ZYNQ_REG_TO;
        while (((p_reg->ENDPTFLUSH & ep_flush) != 0u) &&
               (reg_to                          > 0u)) {
            reg_to--;
        }

        flush_done = DEF_BIT_IS_CLR(p_reg->ENDPTSTATUS, ep_flush);
        nbr_retries--;
    }

    for (ix = 0; ix < entries; ix++) {
        ok = USBD_Zynq_dTD_LstRemove(p_drv, ep_phy_nbr);
        if (ok == DEF_FAIL) {
            break;
        }
    }

    if (nbr_retries == 0u) {
        return (DEF_FAIL);
    } else {
        return (DEF_OK);
    }
}


/*
*********************************************************************************************************
*                                         USBD_DrvEP_Stall()
*
* Description : Set or clear stall condition on endpoint.
*
* Argument(s) : p_drv       Pointer to device driver structure.
*
*               ep_addr     Endpoint address.
*
*               state       Endpoint stall state.
*
* Return(s)   : DEF_OK,   if NO error(s).
*
*               DEF_FAIL, otherwise.
*
* Caller(s)   : USBD_EP_Stall() via 'p_drv_api->EP_Stall()',
*               USBD_CtrlStall().
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  CPU_BOOLEAN  USBD_DrvEP_Stall (USBD_DRV     *p_drv,
                                       CPU_INT08U    ep_addr,
                                       CPU_BOOLEAN   state)
{
    USBD_ZYNQ_REG  *p_reg;
    CPU_INT08U      ep_log_nbr;


    p_reg      = (USBD_ZYNQ_REG *)(p_drv->CfgPtr->BaseAddr);
    ep_log_nbr = USBD_ZYNQ_EP_GET_LOG_NBR(ep_addr);

    if (state == DEF_SET) {
        if (USBD_EP_IS_IN(ep_addr)) {
            DEF_BIT_SET(p_reg->ENDPTCTRLx[ep_log_nbr], USBD_ZYNQ_ENDPTCTRL_TX_STALL);
        } else {
            DEF_BIT_SET(p_reg->ENDPTCTRLx[ep_log_nbr], USBD_ZYNQ_ENDPTCTRL_RX_STALL);
        }
    } else {
        if (ep_log_nbr > 0) {
            if (USBD_EP_IS_IN(ep_addr)) {
                DEF_BIT_CLR(p_reg->ENDPTCTRLx[ep_log_nbr], USBD_ZYNQ_ENDPTCTRL_TX_STALL);
                DEF_BIT_SET(p_reg->ENDPTCTRLx[ep_log_nbr], USBD_ZYNQ_ENDPTCTRL_TX_TOGGLE_RST);
            } else {
                DEF_BIT_CLR(p_reg->ENDPTCTRLx[ep_log_nbr], USBD_ZYNQ_ENDPTCTRL_RX_STALL);
                DEF_BIT_SET(p_reg->ENDPTCTRLx[ep_log_nbr], USBD_ZYNQ_ENDPTCTRL_RX_TOGGLE_RST);
            }
        }
    }

    return (DEF_OK);
}


/*
*********************************************************************************************************
*                                        USBD_DrvISR_Handler()
*
* Description : USB device Interrupt Service Routine (ISR) handler.
*
* Argument(s) : p_drv       Pointer to device driver structure.
*
* Return(s)   : none.
*
* Caller(s)   : This is an ISR.
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  void  USBD_DrvISR_Handler (USBD_DRV  *p_drv)
{
    USBD_ZYNQ_REG     *p_reg;
    USBD_DRV_DATA     *p_drv_data;
    USBD_ZYNQ_dTD_EXT *p_dtd;
    CPU_INT32U         ep_complete;
    CPU_INT32U         ep_setup;
    CPU_INT08U         ep_log_nbr;
    CPU_INT08U         ep_phy_nbr;
    CPU_INT32U         int_status;
    CPU_INT32U         int_en;


    p_drv_data   = (USBD_DRV_DATA *) p_drv->DataPtr;
    p_reg        = (USBD_ZYNQ_REG *)(p_drv->CfgPtr->BaseAddr);

    int_status  = p_reg->USBSTS;
    int_en      = p_reg->USBINTR;
    int_status &= int_en;

    if (int_status != DEF_BIT_NONE) {
                                                                /* ------------- HIGH-FREQUENCY INTERRUPTS ------------ */
        if (DEF_BIT_IS_SET(int_status, USBD_ZYNQ_USB_INT_U)) {
            p_reg->USBSTS = USBD_ZYNQ_USB_INT_U;

            ep_setup = p_reg->ENDPTSETUPSTAT;                   /* (1) Process all setup transactions                   */
            while (ep_setup != DEF_BIT_NONE) {
                ep_log_nbr = (CPU_INT08U)(31u - CPU_CntLeadZeros32(ep_setup));
                USBD_Zynq_SetupProcess(p_drv,
                                       ep_log_nbr);
                ep_setup = p_reg->ENDPTSETUPSTAT;
            }

                                                                /* (2) Process all IN/OUT  transactions                 */
            ep_complete = p_reg->ENDPTCOMPLETE;
            p_reg->ENDPTCOMPLETE = ep_complete;

            while (ep_complete != DEF_BIT_NONE) {
                if (DEF_BIT_IS_SET_ANY(ep_complete, USBD_ZYNQ_ENDPTCOMPLETE_TX_MASK)) {
                    ep_log_nbr = (CPU_INT08U)(31u - CPU_CntLeadZeros32(USBD_ZYNQ_ENDPTxxx_GET_TX_NBR(ep_complete)));
                    ep_phy_nbr = USBD_ZYNQ_EP_IN_LOG_TO_PHY_NBR(ep_log_nbr);

                    ep_complete &= ~USBD_ZYNQ_ENDPTxxx_GET_TX_BITS(ep_log_nbr);
                    p_dtd        =  p_drv_data->dQH_Tbl[ep_phy_nbr].dTD_LstHeadPtr;

                    CPU_DCACHE_RANGE_FLUSH(p_dtd, sizeof(USBD_ZYNQ_dTD_EXT));

                    if (DEF_BIT_IS_CLR(p_dtd->Token, USBD_ZYNQ_dTD_TOKEN_STATUS_ACTIVE)) {
#if 0
                        buf_len =   p_dtd->BufLen  -
                                  ((p_dtd->Token & USBD_ZYNQ_dTD_TOKEN_TOTAL_BYTES_MASK) >> 16);
#endif
                        USBD_EP_TxCmpl(p_drv, ep_log_nbr);
                    } else {
#if 0
                                                                /* !!!! Transmit with error.                            */
                        USBD_EP_TxCmpl(p_drv, ep_log_nbr, 0u);
#endif
                    }

                    USBD_Zynq_dTD_LstRemove(p_drv, ep_phy_nbr);
                }

                if (DEF_BIT_IS_SET_ANY(ep_complete, USBD_ZYNQ_ENDPTCOMPLETE_RX_MASK)) {
                    ep_log_nbr = (CPU_INT08U)(31u - CPU_CntLeadZeros32(USBD_ZYNQ_ENDPTxxx_GET_RX_NBR(ep_complete)));
                    ep_phy_nbr = USBD_ZYNQ_EP_OUT_LOG_TO_PHY_NBR(ep_log_nbr);

                    ep_complete &= ~USBD_ZYNQ_ENDPTxxx_GET_RX_BITS(ep_log_nbr);
                    p_dtd        =  p_drv_data->dQH_Tbl[ep_phy_nbr].dTD_LstHeadPtr;

                    CPU_DCACHE_RANGE_FLUSH(p_dtd, sizeof(USBD_ZYNQ_dTD_EXT));

                    if (DEF_BIT_IS_CLR(p_dtd->Token, USBD_ZYNQ_dTD_TOKEN_STATUS_ACTIVE)) {
                        USBD_EP_RxCmpl(p_drv, ep_log_nbr);
                    }
                }
            }
        }

        if (DEF_BIT_IS_SET(int_status, USBD_ZYNQ_USB_INT_UE)) {
            p_reg->USBSTS = USBD_ZYNQ_USB_INT_UE;
        }
                                                                /* ------------- LOW-FREQUENCY INTERRUPTS ------------- */
                                                                /* (3) Process the bus change interrupts                */
        if (DEF_BIT_IS_SET_ANY(int_status, USBD_ZYNQ_USB_INT_BUS)) {

                                                                /* ---------------- USB RESET INTERRUPT --------------- */
            if (DEF_BIT_IS_SET(int_status, USBD_ZYNQ_USB_INT_UR)) {

                USBD_Zynq_SoftRst(p_drv);                       /* Perform a soft reset                                 */

                USBD_EventReset(p_drv);                         /* Notify bus reset.                                    */

                p_reg->USBSTS  = USBD_ZYNQ_USB_INT_UR;          /* Clear the interrupt                                  */
                p_reg->USBINTR = USBD_ZYNQ_USB_INT_SL
                               | USBD_ZYNQ_USB_INT_UR
                               | USBD_ZYNQ_USB_INT_PC
                               | USBD_ZYNQ_USB_INT_U
                               | USBD_ZYNQ_USB_INT_UE;
            }
                                                                /* --------------- USB SUSPEND INTERRUPT -------------- */
            if (DEF_BIT_IS_SET(int_status, USBD_ZYNQ_USB_INT_SL)) {

                USBD_EventSuspend(p_drv);

                p_reg->USBSTS  = USBD_ZYNQ_USB_INT_SL;          /* Clear the suspend interrupt                          */
                p_reg->USBINTR = USBD_ZYNQ_USB_INT_UR           /* Enable the Reset and Port change interrupt           */
                               | USBD_ZYNQ_USB_INT_U
                               | USBD_ZYNQ_USB_INT_PC
                               | USBD_ZYNQ_USB_INT_UE;
            }
                                                                /* ------------- USB PORT CHANGE INTERRUPT ------------ */
            if (DEF_BIT_IS_SET(int_status, USBD_ZYNQ_USB_INT_PC)) {
                                                                /* Detect the speed of the device                       */
                if (DEF_BIT_IS_SET(p_reg->PORTSC1, USBD_ZYNQ_PORTSC1_HSP)) {
                    USBD_EventHS(p_drv);                        /* Notify high-speed event.                             */

                }
                                                                /* Clear the Port change interrupt                      */
                p_reg->USBSTS = USBD_ZYNQ_USB_INT_PC;
            }
        }
    }
}


/*
*********************************************************************************************************
*********************************************************************************************************
*                                           LOCAL FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                    USBD_Zynq_dTD_LstInsert()
*
* Description : Insert a new dTD at the end of the link list.
*               (1) Get a dTD from the memory pool.
*               (2) Build the transfer descriptor.
*               (3) Insert the dTD at the end of the link list
*
* Argument(s) : p_drv       Pointer to device driver structure.
*
*               ep_phy_nbr  Endpoint logical number.
*
*               p_data      Pointer to the data buffer; ignored for OUT endpoints.
*
*               len         Transfer length.
*
* Return(s)   : DEF_OK,   if NO error(s).
*
*               DEF_FAIL, otherwise.
*
* Caller(s)   : Various.
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  CPU_BOOLEAN   USBD_Zynq_dTD_LstInsert (USBD_DRV    *p_drv,
                                               CPU_INT08U   ep_phy_nbr,
                                               CPU_INT08U  *p_data,
                                               CPU_INT16U   len)
{
    USBD_ZYNQ_REG      *p_reg;
    USBD_DRV_DATA      *p_drv_data;
    USBD_ZYNQ_dTD_EXT  *p_dtd;
    USBD_ZYNQ_dTD_EXT  *p_dtd_last;
    USBD_ZYNQ_dQH      *p_dqh;
    CPU_INT08U          i;
    CPU_INT08U          insert_nbr_tries;
    CPU_BOOLEAN         insert_complete;
    CPU_INT32U          ep_status;
    CPU_INT08U         *p_buf_page;
    CPU_BOOLEAN         rtn_flag;
    CPU_INT32U          dtd_totbytes;
    CPU_INT32U          rem;
    CPU_INT32U          buf_page_max;
    CPU_INT32U          buf_page;
    LIB_ERR             err_lib;
    CPU_SR_ALLOC();


    p_drv_data    = (USBD_DRV_DATA *)p_drv->DataPtr;
    p_reg         = (USBD_ZYNQ_REG *)(p_drv->CfgPtr->BaseAddr);
    p_dqh         = &p_drv_data->dQH_Tbl[ep_phy_nbr];

    CPU_DCACHE_RANGE_FLUSH(p_dqh, sizeof(USBD_ZYNQ_dQH));   /* Invalidate (clear) the cached RAM block, so that the */
                                                                /* next CPU read will be from RAM again.                */

    p_dtd_last    = p_dqh->dTD_LstTailPtr;
                                                                /* (1) Get a dTD from the memory pool                   */
    p_dtd         = (USBD_ZYNQ_dTD_EXT *)Mem_PoolBlkGet(            &p_drv_data->dTD_MemPool,
                                                        (CPU_SIZE_T) sizeof(USBD_ZYNQ_dTD_EXT),
                                                                    &err_lib);

    if (err_lib != LIB_MEM_ERR_NONE) {
        return (DEF_FAIL);
    }

                                                                /* See Page 386 of the Zynq-7000 TRM for more info.     */

    Mem_Clr((void     *)p_dtd,                                  /* ... Initialize the dTD to 0x00                       */
            (CPU_SIZE_T)sizeof(USBD_ZYNQ_dTD_EXT));

                                                                /* (2) Build the transfer descriptor                    */
    p_dtd->dTD_NextPtr = USBD_ZYNQ_dTD_dTD_NEXT_TERMINATE;      /* ... Set the terminate bit to 1                       */
                                                                /* ... Fill in the total transfer len.                  */
    p_dtd->Token       = ((len << 16) & USBD_ZYNQ_dTD_TOKEN_TOTAL_BYTES_MASK)
                       | USBD_ZYNQ_dTD_TOKEN_IOC
                       | USBD_ZYNQ_dTD_TOKEN_STATUS_ACTIVE;

    p_buf_page = p_data;
    rtn_flag   = DEF_FALSE;
                                                                /* Init Buffer Pointer (Page 0) + Current Offset        */
    p_dtd->BufPtrs[0] = (CPU_INT32U)p_buf_page;

    buf_page_max = (((CPU_INT32U)p_buf_page + 0x1000u) & 0xFFFFF000u) - (CPU_INT32U)p_buf_page;
    buf_page     = (p_data + len) - p_buf_page;
    dtd_totbytes = DEF_MIN(buf_page, buf_page_max);

                                                                /* Init Buffer Pointer List if buffer spans more ...    */
                                                                /* ... than one physical page (see Note #3).            */
    for (i = 1u; i <= 4u; i++) {                                /* Init Buffer Pointer (Page 1 to 4)                    */
                                                                /* Find the next closest 4K-page boundary ahead.        */
        p_buf_page = (CPU_INT08U *)(((CPU_INT32U)p_buf_page + 0x1000u) & 0xFFFFF000u);

        if (p_buf_page < (p_data + len)) {                      /* If buffer spans a new 4K-page boundary.              */
                                                                /* Set page ptr to ref start of the subsequent 4K page. */
            p_dtd->BufPtrs[i]  = (CPU_INT32U)p_buf_page;
            dtd_totbytes      += DEF_MIN(((p_data + len) - p_buf_page), 0x1000);
        } else {                                                /* All the transfer size has been described...          */
            rtn_flag = DEF_TRUE;
            break;                                              /* ... quit the loop.                                   */
        }
    }

    p_dtd->BufAddr = (CPU_INT32U)p_data;                        /* Save the buffer address                              */
    p_dtd->BufLen  =  len;

    CPU_DCACHE_RANGE_INV(p_dtd, sizeof(USBD_ZYNQ_dTD_EXT));    /* Write cached memory block back to RAM.               */

    CPU_CRITICAL_ENTER();

    CPU_DCACHE_RANGE_FLUSH(p_dqh, sizeof(USBD_ZYNQ_dQH));   /* Invalidate (clear) the cached RAM block, so that the */
                                                                /* next CPU read will be from RAM again.                */

                                                                /* (3) Insert the dTD at the end of the link list       */
                                                                /* ... Case 1: Link list is empty                       */
    if (p_dqh->dTD_LstNbrEntries == 0) {

        p_dqh->dTD_LstHeadPtr = p_dtd;
        p_dqh->dTD_LstTailPtr = p_dtd;
        p_dqh->dTD_LstNbrEntries++;

                                                                /* (a) Write dQH next pointer and dQH terminate ...     */
                                                                /* ... bit to '0' as a single operation                 */
        p_dqh->OverArea.dTD_NextPtr = (CPU_INT32U)p_dtd;

                                                                /* (b) Clear the Status bits                            */
        DEF_BIT_CLR(p_dqh->OverArea.Token, USBD_ZYNQ_dTD_TOKEN_STATUS_MASK);

        CPU_DCACHE_RANGE_INV(p_dqh, sizeof(USBD_ZYNQ_dQH));    /* Write cached memory block back to RAM.               */

                                                                /* (c) Prime the endpoint                               */
        USBD_ZYNQ_ENDPTxxx_BIT_WR(p_reg->ENDPTPRIME, ep_phy_nbr);

    } else {
                                                                /* ... Case 2: Link list is not empty                   */
                                                                /*  (a) Add dTD to end of linked list                   */
        p_dqh->dTD_LstTailPtr->dTD_NextPtr = (CPU_INT32U)p_dtd;
        p_dqh->dTD_LstTailPtr              = p_dtd;
        p_dqh->dTD_LstNbrEntries++;

        CPU_DCACHE_RANGE_INV(p_dqh, sizeof(USBD_ZYNQ_dQH));    /* Write cached memory block back to RAM.               */

                                                                /*  (b) Read correct prime bit. IF '1' DONE.            */

        if (USBD_ZYNQ_ENDPTxxx_IS_BIT_SET(p_reg->ENDPTPRIME, ep_phy_nbr)) {
            CPU_CRITICAL_EXIT();
            return (DEF_OK);
        }

        insert_nbr_tries = USBD_ZYNQ_dTD_LST_INSERT_NBR_TRIES_MAX;
        insert_complete  = DEF_FALSE;
        ep_status        = DEF_BIT_NONE;

        while ((insert_complete  == DEF_FALSE) &&
               (insert_nbr_tries >  0)) {
                                                                /* (c) Set ATDTW bit in USBCMD register to '1'          */
            DEF_BIT_SET(p_reg->USBCMD, USBD_ZYNQ_USBCMD_ATDTW);

            ep_status = p_reg->ENDPTSTATUS;                     /* (d) Read correct status bits in ENDPSTATUS           */

                                                                /* (e) Read ATDTW bit in USBCMD register ...            */
            if (DEF_BIT_IS_SET(p_reg->USBCMD, USBD_ZYNQ_USBCMD_ATDTW)) {
                insert_complete = DEF_TRUE;                     /* ... If '1' continue to (f)                           */
            } else {
                insert_nbr_tries--;                             /* ... If '0' goto (c)                                  */
            }
        }

        if (insert_complete == DEF_FALSE) {

            Mem_PoolBlkFree(         &p_drv_data->dTD_MemPool,
                            (void  *) p_dtd,
                                     &err_lib);

            p_dqh->dTD_LstTailPtr              = p_dtd_last;
            p_dqh->dTD_LstTailPtr->dTD_NextPtr = USBD_ZYNQ_dTD_dTD_NEXT_TERMINATE;
            p_dqh->dTD_LstNbrEntries--;

            CPU_DCACHE_RANGE_INV(p_dqh, sizeof(USBD_ZYNQ_dQH));

            CPU_CRITICAL_EXIT();
            return (DEF_FAIL);
        }

        insert_complete = DEF_TRUE;
                                                                /* (f) Set ATDTW bit in USBCMD register to '0'          */
        DEF_BIT_CLR(p_reg->USBCMD, USBD_ZYNQ_USBCMD_ATDTW);

        if (USBD_ZYNQ_ENDPTxxx_IS_BIT_SET(ep_status, ep_phy_nbr)) {
            CPU_CRITICAL_EXIT();
            return (DEF_OK);                                    /* (g) If status bit read in (d) is '1' DONE            */
        } else {
                                                                /* (h) If status bit read in (d) is '0' goto Case 1     */
            p_dqh->OverArea.dTD_NextPtr = (CPU_INT32U)p_dqh->dTD_LstHeadPtr;

            DEF_BIT_CLR(p_dqh->OverArea.Token, USBD_ZYNQ_dTD_TOKEN_STATUS_MASK);

            CPU_DCACHE_RANGE_INV(p_dqh, sizeof(USBD_ZYNQ_dQH));

            USBD_ZYNQ_ENDPTxxx_BIT_WR(p_reg->ENDPTPRIME, ep_phy_nbr);
        }
    }

    CPU_CRITICAL_EXIT();

    return (DEF_OK);
}

/*
*********************************************************************************************************
*                                      USBD_Zynq_dTD_LstRd()
*
* Description : Read current dTD data buffer.
*
* Argument(s) : p_drv       Pointer to device driver structure.
*
*               ep_phy_nbr  Endpoint physical number.
*
*               data_len    Data buffer length.
*
*               p_xfer_len  Pointer to variable that will receive transfer length.
*
*               p_len_rem   Pointer to variable that will receive the remaining length.
*
* Return(s)   : DEF_OK,   if NO error(s).
*
*               DEF_FAIL, otherwise.
*
* Caller(s)   : Various.
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  CPU_BOOLEAN  USBD_Zynq_dTD_LstRd (USBD_DRV    *p_drv,
                                          CPU_INT08U   ep_phy_nbr,
                                          CPU_INT16U   data_len,
                                          CPU_INT16U  *p_xfer_len,
                                          CPU_INT16U  *p_len_rem)
{
    CPU_INT16U      ep_buf_len;
    CPU_INT32U      ep_token;
    USBD_ZYNQ_dQH  *p_dqh;
    USBD_DRV_DATA  *p_drv_data;

    CPU_SR_ALLOC();


    p_drv_data = (USBD_DRV_DATA  *)p_drv->DataPtr;
    p_dqh      = &p_drv_data->dQH_Tbl[ep_phy_nbr];
    ep_token   =  p_dqh->dTD_LstHeadPtr->Token;

    CPU_DCACHE_RANGE_FLUSH(p_dqh, sizeof(USBD_ZYNQ_dQH));   /* Invalidate (clear) the cached RAM block, so that the */
                                                                /* next CPU read will be from RAM again.                */

                                                                /* Chk for err.                                         */
    if (DEF_BIT_IS_SET_ANY(ep_token, USBD_ZYNQ_dTD_TOKEN_STATUS_ANY)) {
        return (DEF_FAIL);
    }

                                                                /* Calc rx'd len.                                       */
    ep_buf_len = (CPU_INT16U)(p_dqh->dTD_LstHeadPtr->BufLen -
                            ((p_dqh->dTD_LstHeadPtr->Token  & USBD_ZYNQ_dTD_TOKEN_TOTAL_BYTES_MASK) >> 16));

   *p_len_rem  = (CPU_INT16U)0;
   *p_xfer_len =  ep_buf_len;

    CPU_CRITICAL_ENTER();
    if (ep_buf_len != 0) {
                                                                /* Chk rem data to read.                                */
        if (ep_buf_len > data_len) {
                                                                /* Update size & pointer to memory buffer.              */
            p_dqh->dTD_LstHeadPtr->Token = ((p_dqh->dTD_LstHeadPtr->Token) & USBD_ZYNQ_dTD_TOKEN_TOTAL_BYTES_MASK)
                                         + ((ep_buf_len << 16)             & USBD_ZYNQ_dTD_TOKEN_TOTAL_BYTES_MASK);
           *p_len_rem = ep_buf_len - data_len;
        }
    }

    CPU_DCACHE_RANGE_INV(p_dqh, sizeof(USBD_ZYNQ_dQH));        /* Write cached memory block back to RAM.               */

    CPU_CRITICAL_EXIT();

    return (DEF_OK);
}


/*
*********************************************************************************************************
*                                     USBD_Zynq_dTD_LstEmpty()
*
* Description : This function flush the dTD list. All the dTD and Rx buffers are returned to the memory pool.
*
* Argument(s) : p_drv       Pointer to device driver structure.
*
*               ep_phy_nbr  Endpoint physical number.
*
* Return(s)   : DEF_OK,   if NO error(s).
*
*               DEF_FAIL, otherwise.
*
* Caller(s)   : Various.
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  CPU_BOOLEAN  USBD_Zynq_dTD_LstEmpty (USBD_DRV    *p_drv,
                                             CPU_INT08U   ep_phy_nbr)
{
    USBD_DRV_DATA  *p_drv_data;
    CPU_INT32U      ix;
    CPU_INT32U      entries;
    CPU_BOOLEAN     ok;
    CPU_INT08U      ep_addr;


    p_drv_data = (USBD_DRV_DATA  *)p_drv->DataPtr;

    CPU_DCACHE_RANGE_FLUSH(&(p_drv_data->dQH_Tbl[ep_phy_nbr].dTD_LstNbrEntries), sizeof(CPU_REG32));

    entries    = p_drv_data->dQH_Tbl[ep_phy_nbr].dTD_LstNbrEntries;
    ok         = DEF_OK;

    for (ix = 0; ix < entries; ix++) {
        ok = USBD_Zynq_dTD_LstRemove(p_drv, ep_phy_nbr);
        if (ok == DEF_FAIL) {
            break;
        }
    }

    if (ep_phy_nbr % 2 == 0) {
        ep_addr = USBD_ZYNQ_EP_PHY_TO_LOG_NBR(ep_phy_nbr);
    } else {
        ep_addr = USBD_ZYNQ_EP_PHY_TO_LOG_NBR(ep_phy_nbr) |
                  USBD_EP_DIR_BIT;
    }

    if (entries > 0) {
        USBD_DrvEP_Abort(p_drv, ep_addr);
    }

    return (ok);
}


/*
*********************************************************************************************************
*                                    USBD_Zynq_dTD_LstRemove()
*
* Description : Remove a dTD form the link list.
*
* Argument(s) : p_drv       Pointer to device driver structure.
*
*               ep_phy_nbr  Endpoint physical number.
*
* Return(s)   : DEF_OK,   if NO error(s).
*
*               DEF_FAIL, otherwise.
*
* Caller(s)   : Various.
*
* Note(s)     : (1) The link list before the Remove function will look like:
*
*                           +-----+      +-----+          +-----+
*     dTD_LstHeadPtr -----> | dTD |----->| dTD |---....-->| dTD |---->
*                           +--|--+      +--|--+          +--|--+
*                              |            |                |
*                              V            V                V
*                          +--------+    +--------+       +--------+
*                          |  dTD   |    |  dTD   |       |  dTD   |
*                          | Buffer |    | Buffer |       | Buffer |
*                          +--------+    +--------+       +--------+
*                              0             1               N
*
*               after the USBD_Zynq_dTD_LstRemove is called the link list will look like:
*
*                      |--------------------|
*                      | |            |     V
*                      | |  +-----+   |  +-----+          +-----+
*     dTD_LstHeadPtr --| |  | dTD |---|->| dTD |---....-->| dTD |---->
*                        |  +--|--+   |  +--|--+          +--|--+
*                        |     |      |     |                |
*                        |     V      |     V                V
*                        | +--------+ |  +--------+       +--------+
*                        | |  dTD   | |  |  dTD   |       |  dTD   |
*                        | | Buffer | |  | Buffer |       | Buffer |
*                        | +--------+ |  +--------+       +--------+
*                        |     0'     |     0                N -1
*                        | return to  |
*                        | memory pool|
*
*                                    +-----------+   +----------+
*                p_ep_data --------->| EP Buffer | = |   dTD    |  ; *p_ep_trans_size = size of the dTD buffer.
*                                    |           |   |  Buffer  |
*                                    +-----------+   +----------+
*                                                          0'
*
*********************************************************************************************************
*/

static  CPU_BOOLEAN  USBD_Zynq_dTD_LstRemove (USBD_DRV    *p_drv,
                                              CPU_INT08U   ep_phy_nbr)
{
    USBD_DRV_DATA  *p_drv_data;
    USBD_ZYNQ_dQH  *p_dqh;
    LIB_ERR         err_lib;
    CPU_SR_ALLOC();


    p_drv_data = (USBD_DRV_DATA  *)p_drv->DataPtr;
    p_dqh      = &p_drv_data->dQH_Tbl[ep_phy_nbr];

    CPU_DCACHE_RANGE_FLUSH(p_dqh, sizeof(USBD_ZYNQ_dQH));   /* Invalidate (clear) the cached RAM block, so that the */
                                                                /* next CPU read will be from RAM again.                */

    Mem_PoolBlkFree(         &p_drv_data->dTD_MemPool,          /* Return the head dTD to the memory pool               */
                    (void  *) p_dqh->dTD_LstHeadPtr,
                             &err_lib);

    if (err_lib != LIB_MEM_ERR_NONE) {
        return (DEF_FAIL);
    }

    CPU_CRITICAL_ENTER();
    CPU_DCACHE_RANGE_FLUSH(p_dqh, sizeof(USBD_ZYNQ_dQH));   /* Invalidate (clear) the cached RAM block, so that the */
                                                                /* next CPU read will be from RAM again.                */
    if (p_dqh->dTD_LstNbrEntries == 1) {
        p_dqh->dTD_LstHeadPtr    = (USBD_ZYNQ_dTD_EXT *)USBD_ZYNQ_dTD_dTD_NEXT_TERMINATE;
        p_dqh->dTD_LstTailPtr    = (USBD_ZYNQ_dTD_EXT *)USBD_ZYNQ_dTD_dTD_NEXT_TERMINATE;
        p_dqh->dTD_LstNbrEntries = 0;
    } else {
        p_dqh->dTD_LstHeadPtr = (USBD_ZYNQ_dTD_EXT *)p_dqh->dTD_LstHeadPtr->dTD_NextPtr;
        p_dqh->dTD_LstNbrEntries--;
    }

    CPU_DCACHE_RANGE_INV(p_dqh, sizeof(USBD_ZYNQ_dQH));        /* Write cached memory block back to RAM.               */
    CPU_CRITICAL_EXIT();

    return (DEF_OK);
}

/*
*********************************************************************************************************
*                                     USBD_Zynq_SetupProcess()
*
* Description : Process setup request.
*
* Argument(s) : p_drv       Pointer to device driver structure.
*
*               ep_log_nbr  Endpoint logical number.
*
* Return(s)   : none.
*
* Caller(s)   : USBD_DrvISR_Handler().
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  void  USBD_Zynq_SetupProcess (USBD_DRV    *p_drv,
                                      CPU_INT08U   ep_log_nbr)
{
    USBD_DRV_DATA  *p_drv_data;
    USBD_ZYNQ_REG  *p_reg;
    USBD_ZYNQ_dQH  *p_dqh;
    CPU_INT08U      ep_phy_nbr;
    CPU_INT08U      hw_rev;
    CPU_INT32U      reg_to;
    CPU_INT32U      setup_pkt[2];
    CPU_BOOLEAN     sutw_set;


    ep_phy_nbr =  USBD_ZYNQ_EP_OUT_LOG_TO_PHY_NBR(ep_log_nbr);
    sutw_set   =  DEF_FALSE;
    reg_to     =  USBD_ZYNQ_REG_TO;
    p_drv_data = (USBD_DRV_DATA  *)p_drv->DataPtr;
    p_reg      = (USBD_ZYNQ_REG *)(p_drv->CfgPtr->BaseAddr);
    p_dqh      = &p_drv_data->dQH_Tbl[ep_phy_nbr];

    CPU_DCACHE_RANGE_FLUSH(p_dqh, sizeof(USBD_ZYNQ_dQH));   /* Invalidate (clear) the cached RAM block, so that the */
                                                                /* next CPU read will be from RAM again.                */

        p_reg->ENDPTSETUPSTAT = DEF_BIT32(ep_log_nbr);

        while ((sutw_set == DEF_FALSE) &&
               (reg_to   >  0)) {
                                                                /* (2) Write '1' to setup Tripwire                    */
            DEF_BIT_SET(p_reg->USBCMD, USBD_ZYNQ_USBCMD_SUTW);

            CPU_DCACHE_RANGE_FLUSH(p_dqh, sizeof(USBD_ZYNQ_dQH));

                                                                /* (3) Duplicate contents of dQH.SetupBuf             */
            setup_pkt[0] = p_dqh->SetupBuf[0];
            setup_pkt[1] = p_dqh->SetupBuf[1];

                                                                /* (4) Read Setup TripWire. If the bi is set ....    */
                                                                /*     ... continue otherwise go to (2)              */
            sutw_set = DEF_BIT_IS_SET(p_reg->USBCMD, USBD_ZYNQ_USBCMD_SUTW);
            reg_to--;
        }

        if (reg_to == 0) {
            return;
        }

        reg_to = USBD_ZYNQ_REG_TO;
                                                                /* (5) Write '0' to clear setup Tripwire             */
        DEF_BIT_CLR(p_reg->USBCMD, USBD_ZYNQ_USBCMD_SUTW);

        while ((DEF_BIT_IS_SET(p_reg->ENDPTSETUPSTAT, DEF_BIT32(ep_log_nbr))) &&
               (reg_to > 0)) {
            reg_to--;
        }

        if (reg_to == 0) {
            return;
        }

        USBD_Zynq_dTD_LstEmpty(p_drv, ep_phy_nbr);

        USBD_EventSetup(p_drv, (void *)&setup_pkt);
}


/*
*********************************************************************************************************
*                                       USBD_Zynq_SoftRst()
*
* Description : Perform a soft reset :
*                   (1) Initializes the dQH data structure for all endpoints.
*                   (2) Creates dTD link list for endpoint 0
*                   (3) Initializes the dTD data structure for all endpoints.
*                   (4) Disable all endpoints except endpoint 0
*                   (5) Clear all setup token semaphores by reading ENDPTSETUPSTAT register and writing
*                       the same value back to the ENDPTSETUPSTAT register.
*                   (6) Clear all endpoint complete status bits by reading the ENDPTCOMPLETE register
*                       and writing the same value back to the ENDPTCOMPLETE register.
*                   (7) Cancel all prime status by waiting until all bits in the ENDPRIME are 0 and the writing
*                       0xFFFFFFFF to ENDPTFLUSH.
*
* Argument(s) : p_drv       Pointer to device driver structure.
*
* Return(s)   : none.
*
* Caller(s)   : USBD_DrvISR_Handler()
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  void  USBD_Zynq_SoftRst (USBD_DRV  *p_drv)
{
    USBD_DRV_DATA  *p_drv_data;
    USBD_ZYNQ_REG  *p_reg;
    CPU_INT32U      reg_to;
    CPU_INT08U      ep_phy_nbr;
    CPU_INT08U      ep_phy_nbr_max;
    CPU_INT08U      ep_log_nbr;


    p_reg          = (USBD_ZYNQ_REG *)(p_drv->CfgPtr->BaseAddr);
    p_drv_data     = (USBD_DRV_DATA *)p_drv->DataPtr;
    ep_phy_nbr_max = USBD_EP_MaxNbrOpenGet(p_drv->DevNbr);

    if (ep_phy_nbr_max != USBD_EP_PHY_NONE) {
        for (ep_phy_nbr = 0; ep_phy_nbr < ep_phy_nbr_max; ep_phy_nbr++) {

            USBD_Zynq_dTD_LstEmpty(p_drv, ep_phy_nbr);

            p_drv_data->dQH_Tbl[ep_phy_nbr].EpCap                = 0;
            p_drv_data->dQH_Tbl[ep_phy_nbr].OverArea.dTD_NextPtr = USBD_ZYNQ_dTD_dTD_NEXT_TERMINATE;

            Mem_Clr((void     *)&p_drv_data->dQH_Tbl[ep_phy_nbr].OverArea.Token,
                    (CPU_SIZE_T)(sizeof(USBD_ZYNQ_dQH) - 2u));

            CPU_DCACHE_RANGE_INV(&(p_drv_data->dQH_Tbl[ep_phy_nbr]), sizeof(USBD_ZYNQ_dQH));

            ep_log_nbr = USBD_ZYNQ_EP_PHY_TO_LOG_NBR(ep_phy_nbr);
            if ((ep_log_nbr != 0) &&
                (DEF_BIT_IS_SET(p_reg->USBCMD,  USBD_ZYNQ_USBCMD_RUN))) {
                p_reg->ENDPTCTRLx[ep_log_nbr] = USBD_ZYNQ_ENDPTCTRL_TX_TOGGLE_RST |
                                                USBD_ZYNQ_ENDPTCTRL_RX_TOGGLE_RST;
            }
        }
    }

    (void)&(p_reg->ENDPTSETUPSTAT);
    (void)&(p_reg->ENDPTCOMPLETE);

    reg_to = USBD_ZYNQ_REG_TO;
    while ((p_reg->ENDPTPRIME != DEF_BIT_NONE) &&
           (reg_to            >  0)) {
        reg_to--;
    }

    p_reg->ENDPTFLUSH = USBD_ZYNQ_ENDPTxxxx_TX_MASK |
                        USBD_ZYNQ_ENDPTxxxx_RX_MASK;

    reg_to = USBD_ZYNQ_REG_TO;
    while ((p_reg->ENDPTSTATUS != DEF_BIT_NONE) &&
           (reg_to             >  0)) {
        p_reg->ENDPTFLUSH = USBD_ZYNQ_ENDPTxxxx_TX_MASK |
                            USBD_ZYNQ_ENDPTxxxx_RX_MASK;
        reg_to--;
    }

    if (DEF_BIT_IS_SET(p_reg->USBCMD,  USBD_ZYNQ_USBCMD_RUN)) {
        p_reg->DEV_ADDR = DEF_BIT_NONE;
    }
}
