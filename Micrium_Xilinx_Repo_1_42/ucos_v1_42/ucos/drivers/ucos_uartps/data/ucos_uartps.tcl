#########################################################################################################
#                                           MICRIUM XSDK REPOSITORY
#                           (c) Copyright 2014-2015; Micrium, Inc.; Weston, FL
#
#               All rights reserved.  Protected by international copyright laws.
#########################################################################################################

source ../../../bsp/data/ucos_tcl_utils.tcl
source ../../../bsp/data/xil_tcl_utils.tcl

proc generate {drv_handle} {
    ucos_log_put "TRACE" "Generating ucos_uartps."
    
    xdefine_zynq_include_file $drv_handle "xparameters.h" "UCOS_UARTPS" "NUM_INSTANCES" "DEVICE_ID" "C_S_AXI_BASEADDR" "C_S_AXI_HIGHADDR" "C_UART_CLK_FREQ_HZ" "C_HAS_MODEM"

    ucos_define_intr_sources $drv_handle "UCOS_UARTPS"

    xdefine_zynq_config_file_intr $drv_handle "ucos_uartps_g.c" "UCOS_UARTPS"  "DEVICE_ID" "C_S_AXI_BASEADDR" "C_UART_CLK_FREQ_HZ" "C_HAS_MODEM"

    xdefine_zynq_canonical_xpars $drv_handle "xparameters.h" "UCOS_UARTPS" "DEVICE_ID" "C_S_AXI_BASEADDR" "C_S_AXI_HIGHADDR" "C_UART_CLK_FREQ_HZ" "C_HAS_MODEM"
}