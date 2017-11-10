/*
*********************************************************************************************************
*
*                                    MICRIUM BOARD SUPPORT PACKAGE
*
*                          (c) Copyright 2003-2013; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*
*               This BSP is provided in source form to registered licensees ONLY.  It is
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
*                                    MICRIUM BOARD SUPPORT PACKAGE
*                                ZYNQ-7000 EPP & ZC702 Evaluation Kit
*
* Filename      : bsp.h
* Version       : V1.00
* Programmer(s) : JBL
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               MODULE
*********************************************************************************************************
*/

#ifndef  BSP_PRESENT
#define  BSP_PRESENT


/*
*********************************************************************************************************
*                                               DEFINES
*********************************************************************************************************
*/

//#define DYN_TICK

#define  ZYNQ_APU_FREQ         (666666666U)                     /* Core frequency.                                      */
#define  ZYNQ_PERIPH_FREQ      (333333333U)                     /* Private peripherals freq.                            */
//#define  ZYNQ_APU_FREQ         (1000000000U)                     /* Core frequency.                                      */
//#define  ZYNQ_PERIPH_FREQ      ( 500000000U)                     /* Private peripherals freq.                            */

#define  ARM_PRIV_PERIPH_BASE  (0xF8F00000)                     /* CPU private peripheral base address.                 */
#define  ARM_GIC_INT_SRC_CNT   (256u)


#define  ZYNQ_SLCR_LOCK_KEY    (0x767Bu)                        /* SLCR lock key.                                       */
#define  ZYNQ_SLCR_UNLOCK_KEY  (0xDF0Du)                        /* SLCR unlock key.                                     */


#define  ZYNQ_SLCR_REG         ((ZYNQ_REG_SLCR_PTR)(0xF8000000))

                                                                /* System Level Control Registers                       */
typedef  struct  zynq_reg_slcr {
    CPU_REG32  SCL;                                             /* Secure Configuration Lock.                           */
    CPU_REG32  SLCR_LOCK;                                       /* SLCR Write Protection Lock.                          */
    CPU_REG32  SLCR_UNLOCK;                                     /* SLCR Write Protection Unlock.                        */
    CPU_REG32  SLCR_LOCKSTA;                                    /* SLCR Write Protection Status.                        */
    CPU_REG32  RESERVED1[60];
    CPU_REG32  ARM_PLL_CTRL;                                    /* ARM PLL Control.                                     */
    CPU_REG32  DDR_PLL_CTRL;                                    /* DDR PLL Control.                                     */
    CPU_REG32  IO_PLL_CTRL;                                     /* IO PLL Control.                                      */
    CPU_REG32  PLL_STATUS;                                      /* PLL Status.                                          */
    CPU_REG32  ARM_PLL_CFG;                                     /* ARM PLL Configuration.                               */
    CPU_REG32  DDR_PLL_CFG;                                     /* DDR PLL Configuration.                               */
    CPU_REG32  IO_PLL_CFG;                                      /* IO PLL Configuration.                                */
    CPU_REG32  RESERVED2[1];
    CPU_REG32  ARM_CLK_CTRL;                                    /* ARM Clock Control.                                   */
    CPU_REG32  DDR_CLK_CTRL;                                    /* DDR Clock Control.                                   */
    CPU_REG32  DCI_CLK_CTRL;                                    /* DCI Clock Control.                                   */
    CPU_REG32  APER_CLK_CTRL;                                   /* AMBA Peripheral Clock Control.                       */
    CPU_REG32  USB0_CLK_CTRL;                                   /* USB 0 ULPI Clock Control.                            */
    CPU_REG32  USB1_CLK_CTRL;                                   /* USB 1 ULPI Clock Control.                            */
    CPU_REG32  GEM0_RCLK_CTRL;                                  /* GigE 0 Rx Clock and Rx Signals Select.               */
    CPU_REG32  GEM1_RCLK_CTRL;                                  /* GigE 1 Rx Clock and Rx Signals Select.               */
    CPU_REG32  GEM0_CLK_CTRL;                                   /* GigE 0 Ref Clock Control.                            */
    CPU_REG32  GEM1_CLK_CTRL;                                   /* GigE 1 Ref Clock Control.                            */
    CPU_REG32  SMC_CLK_CTRL;                                    /* SMC Ref Clock Control.                               */
    CPU_REG32  LQSPI_CLK_CTRL;                                  /* Quad SPI Ref Clock Control.                          */
    CPU_REG32  SDIO_CLK_CTRL;                                   /* SDIO Ref Clock Control.                              */
    CPU_REG32  UART_CLK_CTRL;                                   /* UART Ref Clock Control.                              */
    CPU_REG32  SPI_CLK_CTRL;                                    /* SPI Ref Clock Control.                               */
    CPU_REG32  CAN_CLK_CTRL;                                    /* CAN Ref Clock Control.                               */
    CPU_REG32  CAN_MIOCLK_CTRL;                                 /* CAN MIO Clock Control.                               */
    CPU_REG32  DBG_CLK_CTRL;                                    /* SoC Debug Clock Control.                             */
    CPU_REG32  PCAP_CLK_CTRL;                                   /* PCAP Clock Control.                                  */
    CPU_REG32  TOPSW_CLK_CTRL;                                  /* Central Interconnect Clock Control.                  */
    CPU_REG32  FPGA0_CLK_CTRL;                                  /* PL Clock 0 Output Control.                           */
    CPU_REG32  RESERVED3[3];
    CPU_REG32  FPGA1_CLK_CTRL;                                  /* PL Clock 1 Output Control.                           */
    CPU_REG32  RESERVED4[3];
    CPU_REG32  FPGA2_CLK_CTRL;                                  /* PL Clock 2 Output Control.                           */
    CPU_REG32  RESERVED5[3];
    CPU_REG32  FPGA3_CLK_CTRL;                                  /* PL Clock 3 Output Control.                           */
    CPU_REG32  RESERVED6[8];
    CPU_REG32  CLK_621_TRUE;                                    /* CPU Clock Ratio Mode Select.                         */
    CPU_REG32  RESERVED7[14];
    CPU_REG32  PSS_RST_CTRL;                                    /* PS Software Reset Control.                           */
    CPU_REG32  DDR_RST_CTRL;                                    /* DRR Software Reset Control.                          */
    CPU_REG32  TOPSW_RST_CTRL;                                  /* Central Interconnect Reset Control.                  */
    CPU_REG32  DMAC_RST_CTRL;                                   /* DMAC Software Reset Control.                         */
    CPU_REG32  USB_RST_CTRL;                                    /* USB Software Reset Control.                          */
    CPU_REG32  GEM_RST_CTRL;                                    /* Gigabit Ethernet SW Reset Control.                   */
    CPU_REG32  SDIO_RST_CTRL;                                   /* SDIO Software Reset Control.                         */
    CPU_REG32  SPI_RST_CTRL;                                    /* SPI Software Reset Control.                          */
    CPU_REG32  CAN_RST_CTRL;                                    /* CAN Software Reset Control.                          */
    CPU_REG32  I2C_RST_CTRL;                                    /* I2C Software Reset Control.                          */
    CPU_REG32  UART_RST_CTRL;                                   /* UART Software Reset Control.                         */
    CPU_REG32  GPIO_RST_CTRL;                                   /* GPIO Software Reset Control.                         */
    CPU_REG32  LQSPI_RST_CTRL;                                  /* Quad SPI Software Reset Control.                     */
    CPU_REG32  SMC_RST_CTRL;                                    /* SMC Software Reset Control.                          */
    CPU_REG32  OCM_RST_CTRL;                                    /* OMC Software Reset Control.                          */
    CPU_REG32  DEVCI_RST_CTRL;                                  /* Device Config Interface SW Reset Control.            */
    CPU_REG32  FPGA_RST_CTRL;                                   /* FPGA Software Reset Control.                         */
    CPU_REG32  A9_CPU_RST_CTRL;                                 /* CPU Reset and Clock Control.                         */
    CPU_REG32  RESERVED8[1];
    CPU_REG32  RS_AWDT_CTRL;                                    /* Watchdog Timer Reset Control.                        */
    CPU_REG32  RESERVED9[2];
    CPU_REG32  REBOOT_STATUS;                                   /* Reboot Status.                                       */
    CPU_REG32  BOOT_MODE;                                       /* Boot Mode Strapping Pins.                            */
    CPU_REG32  RESERVED10[40];
    CPU_REG32  APU_CTRL;                                        /* APU Control.                                         */
    CPU_REG32  WDT_CLK_SEL;                                     /* APU Watchdog Timer Clock Select.                     */
    CPU_REG32  RESERVED11[138];
    CPU_REG32  PSS_IDCODE;                                      /* PS IDCODE.                                           */
    CPU_REG32  RESERVED12[51];
    CPU_REG32  DDR_URGENT;                                      /* DDR Urgent Control.                                  */
    CPU_REG32  RESERVED13[2];
    CPU_REG32  DDR_CAL_START;                                   /* DDR Calibration Start Triggers.                      */
    CPU_REG32  RESERVED14[1];
    CPU_REG32  DDR_REF_START;                                   /* DDR Refresh Start Triggers.                          */
    CPU_REG32  DDR_CMD_STA;                                     /* DDR Command Store Status.                            */
    CPU_REG32  DDR_URGENT_SEL;                                  /* DDR Urgent Select.                                   */
    CPU_REG32  DDR_DFI_STATUS;                                  /* DDR DFI Status.                                      */
    CPU_REG32  RESERVED15[55];
    CPU_REG32  MIO_PIN_00;                                      /* MIO Pin 0 Control.                                   */
    CPU_REG32  MIO_PIN_01;                                      /* MIO Pin 1 Control.                                   */
    CPU_REG32  MIO_PIN_02;                                      /* MIO Pin 2 Control.                                   */
    CPU_REG32  MIO_PIN_03;                                      /* MIO Pin 3 Control.                                   */
    CPU_REG32  MIO_PIN_04;                                      /* MIO Pin 4 Control.                                   */
    CPU_REG32  MIO_PIN_05;                                      /* MIO Pin 5 Control.                                   */
    CPU_REG32  MIO_PIN_06;                                      /* MIO Pin 6 Control.                                   */
    CPU_REG32  MIO_PIN_07;                                      /* MIO Pin 7 Control.                                   */
    CPU_REG32  MIO_PIN_08;                                      /* MIO Pin 8 Control.                                   */
    CPU_REG32  MIO_PIN_09;                                      /* MIO Pin 9 Control.                                   */
    CPU_REG32  MIO_PIN_10;                                      /* MIO Pin 10 Control.                                  */
    CPU_REG32  MIO_PIN_11;                                      /* MIO Pin 11 Control.                                  */
    CPU_REG32  MIO_PIN_12;                                      /* MIO Pin 12 Control.                                  */
    CPU_REG32  MIO_PIN_13;                                      /* MIO Pin 13 Control.                                  */
    CPU_REG32  MIO_PIN_14;                                      /* MIO Pin 14 Control.                                  */
    CPU_REG32  MIO_PIN_15;                                      /* MIO Pin 15 Control.                                  */
    CPU_REG32  MIO_PIN_16;                                      /* MIO Pin 16 Control.                                  */
    CPU_REG32  MIO_PIN_17;                                      /* MIO Pin 17 Control.                                  */
    CPU_REG32  MIO_PIN_18;                                      /* MIO Pin 18 Control.                                  */
    CPU_REG32  MIO_PIN_19;                                      /* MIO Pin 19 Control.                                  */
    CPU_REG32  MIO_PIN_20;                                      /* MIO Pin 20 Control.                                  */
    CPU_REG32  MIO_PIN_21;                                      /* MIO Pin 21 Control.                                  */
    CPU_REG32  MIO_PIN_22;                                      /* MIO Pin 22 Control.                                  */
    CPU_REG32  MIO_PIN_23;                                      /* MIO Pin 23 Control.                                  */
    CPU_REG32  MIO_PIN_24;                                      /* MIO Pin 24 Control.                                  */
    CPU_REG32  MIO_PIN_25;                                      /* MIO Pin 25 Control.                                  */
    CPU_REG32  MIO_PIN_26;                                      /* MIO Pin 26 Control.                                  */
    CPU_REG32  MIO_PIN_27;                                      /* MIO Pin 27 Control.                                  */
    CPU_REG32  MIO_PIN_28;                                      /* MIO Pin 28 Control.                                  */
    CPU_REG32  MIO_PIN_29;                                      /* MIO Pin 29 Control.                                  */
    CPU_REG32  MIO_PIN_30;                                      /* MIO Pin 30 Control.                                  */
    CPU_REG32  MIO_PIN_31;                                      /* MIO Pin 31 Control.                                  */
    CPU_REG32  MIO_PIN_32;                                      /* MIO Pin 32 Control.                                  */
    CPU_REG32  MIO_PIN_33;                                      /* MIO Pin 33 Control.                                  */
    CPU_REG32  MIO_PIN_34;                                      /* MIO Pin 34 Control.                                  */
    CPU_REG32  MIO_PIN_35;                                      /* MIO Pin 35 Control.                                  */
    CPU_REG32  MIO_PIN_36;                                      /* MIO Pin 36 Control.                                  */
    CPU_REG32  MIO_PIN_37;                                      /* MIO Pin 37 Control.                                  */
    CPU_REG32  MIO_PIN_38;                                      /* MIO Pin 38 Control.                                  */
    CPU_REG32  MIO_PIN_39;                                      /* MIO Pin 39 Control.                                  */
    CPU_REG32  MIO_PIN_40;                                      /* MIO Pin 40 Control.                                  */
    CPU_REG32  MIO_PIN_41;                                      /* MIO Pin 41 Control.                                  */
    CPU_REG32  MIO_PIN_42;                                      /* MIO Pin 42 Control.                                  */
    CPU_REG32  MIO_PIN_43;                                      /* MIO Pin 43 Control.                                  */
    CPU_REG32  MIO_PIN_44;                                      /* MIO Pin 44 Control.                                  */
    CPU_REG32  MIO_PIN_45;                                      /* MIO Pin 45 Control.                                  */
    CPU_REG32  MIO_PIN_46;                                      /* MIO Pin 46 Control.                                  */
    CPU_REG32  MIO_PIN_47;                                      /* MIO Pin 47 Control.                                  */
    CPU_REG32  MIO_PIN_48;                                      /* MIO Pin 48 Control.                                  */
    CPU_REG32  MIO_PIN_49;                                      /* MIO Pin 49 Control.                                  */
    CPU_REG32  MIO_PIN_50;                                      /* MIO Pin 50 Control.                                  */
    CPU_REG32  MIO_PIN_51;                                      /* MIO Pin 51 Control.                                  */
    CPU_REG32  MIO_PIN_52;                                      /* MIO Pin 52 Control.                                  */
    CPU_REG32  MIO_PIN_53;                                      /* MIO Pin 53 Control.                                  */
    CPU_REG32  RESERVED16[11];
    CPU_REG32  MIO_LOOPBACK;                                    /* Loopback Function Within MIO.                        */
    CPU_REG32  RESERVED17[1];
    CPU_REG32  MIO_MST_TRI0;                                    /* MIO Pin Tri-state Enables 31:0.                      */
    CPU_REG32  MIO_MST_TRI1;                                    /* MIO Pin Tri-state Enables 53:32.                     */
    CPU_REG32  RESERVED18[7];
    CPU_REG32  SD0_WP_CD_SEL;                                   /* SDIO 0 WP CD Select.                                 */
    CPU_REG32  SD1_WP_CD_SEL;                                   /* SDIO 1 WP CD Select.                                 */
    CPU_REG32  RESERVED19[50];
    CPU_REG32  LVL_SHFTR_EN;                                    /* Level Shifters Enable.                               */
    CPU_REG32  RESERVED20[3];
    CPU_REG32  OCM_CFG;                                         /* OCM Address Mapping.                                 */
    CPU_REG32  RESERVED21[123];
    CPU_REG32  GPIOB_CTRL;                                      /* PS IO Buffer Control.                                */
    CPU_REG32  GPIOB_CFG_CMOS18;                                /* MIO GPIOB CMOS 1.8V Configuration.                   */
    CPU_REG32  GPIOB_CFG_CMOS25;                                /* MIO GPIOB CMOS 2.5V Configuration.                   */
    CPU_REG32  GPIOB_CFG_CMOS33;                                /* MIO GPIOB CMOS 3.3V Configuration.                   */
    CPU_REG32  GPIOB_CFG_LVTTL;                                 /* MIO GPIOB LVTTL Configuration.                       */
    CPU_REG32  GPIOB_CFG_HSTL;                                  /* MIO GPIOB HSTL Configuration.                        */
    CPU_REG32  GPIOB_DRVR_BIAS_CTRL;                            /* MIO GPIOB Driver Bias Control.                       */
    CPU_REG32  RESERVED22[9];
    CPU_REG32  DDRIOB_ADDR0;                                    /* DDR IOB Configuration for A[14:0], CKE and DRST_B.   */
    CPU_REG32  DDRIOB_ADDR1;                                    /* DDR IOB Configuration for BS[2:0], ODT, CS_B, WE_B, RAS_B and CAS_B. */
    CPU_REG32  DDRIOB_DATA0;                                    /* DDR IOB Configuration for Data 15:0.                 */
    CPU_REG32  DDRIOB_DATA1;                                    /* DDR IOB Configuration for Data 31:16.                */
    CPU_REG32  DDRIOB_DIFF0;                                    /* DDR IOB Configuration for DQS 1:0.                   */
    CPU_REG32  DDRIOB_DIFF1;                                    /* DDR IOB Configuration for DQS 3:2.                   */
    CPU_REG32  DDRIOB_CLOCK;                                    /* DDR IOB Configuration for Clock Output.              */
    CPU_REG32  DDRIOB_DRIVE_SLEW_ADDR;                          /* Drive and Slew control Address and Command.          */
    CPU_REG32  DDRIOB_DRIVE_SLEW_DATA;                          /* Drive and Slew control DQ.                           */
    CPU_REG32  DDRIOB_DRIVE_SLEW_DIFF;                          /* Drive and Slew control DQS.                          */
    CPU_REG32  DDRIOB_DRIVE_SLEW_CLOCK;                         /* Drive and Slew control Clock.                        */
    CPU_REG32  DDRIOB_DDR_CTRL;                                 /* DDR IOB Buffer Control.                              */
} ZYNQ_REG_SLCR, *ZYNQ_REG_SLCR_PTR;



/*
*********************************************************************************************************
*                                     REGISTER BIT DEFINITIONS
*********************************************************************************************************
*/

                                                                /* -------------- MIO REG BIT DEFINITION -------------- */
#define  ZYNQ_BIT_MIO_DISABLE_RCVR    DEF_BIT_13                /* Disable HSTL Input Buffer.                           */
#define  ZYNQ_BIT_MIO_PULL_UP         DEF_BIT_12                /* Enable Pull-Up.                                      */
#define  ZYNQ_BIT_MIO_IO_TYPE_MSK (DEF_BIT_FIELD(3, 9))         /* IO Buffer Type.                                      */
#define  ZYNQ_BIT_MIO_IO_TYPE(cfg) (DEF_BIT_MASK(cfg, 9) & ZYNQ_BIT_MIO_IO_TYPE_MSK)
#define  ZYNQ_BIT_MIO_SPEED           DEF_BIT_08                /* IO Buffer Edge Rate.                                 */
#define  ZYNQ_BIT_MIO_L3_SEL_MSK (DEF_BIT_FIELD(3, 5))          /* Level 3 Mux Select.                                  */
#define  ZYNQ_BIT_MIO_L3_SEL(cfg) (DEF_BIT_MASK(cfg, 5) & ZYNQ_BIT_MIO_L3_SEL_MSK)
#define  ZYNQ_BIT_MIO_L2_SEL_MSK (DEF_BIT_FIELD(2, 3))          /* Level 2 Mux Select.                                  */
#define  ZYNQ_BIT_MIO_L2_SEL(cfg) (DEF_BIT_MASK(cfg, 3) & ZYNQ_BIT_MIO_L2_SEL_MSK)
#define  ZYNQ_BIT_MIO_L1_SEL          DEF_BIT_02                /* Level 1 Mux Select.                                  */
#define  ZYNQ_BIT_MIO_L0_SEL          DEF_BIT_01                /* Level 0 Mux Select.                                  */
#define  ZYNQ_BIT_MIO_TRI_ENABLE      DEF_BIT_00                /* Tri-State Enable.                                    */


/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/


void        BSP_Init           (void);

CPU_INT32U  BSP_CPU_ClkFreq    (void);

CPU_INT32U  BSP_Periph_ClkFreq (void);

void        BSP_LED_Init       (void);

void        BSP_LED_On         (CPU_INT32U led);

void        BSP_LED_Off        (CPU_INT32U led);

void        BSP_LED_Toggle     (CPU_INT32U led);



#endif  /* BSP_PRESENT */
