#########################################################################################################
#                                           MICRIUM XSDK REPOSITORY
#                             (c) Copyright 2014-2015; Micrium, Inc.; Weston, FL
#
#               All rights reserved.  Protected by international copyright laws.
#########################################################################################################

source ../../../bsp/data/ucos_tcl_utils.tcl
source ../../../bsp/data/xil_tcl_utils.tcl

source "xil_ttcps.tcl"

proc generate {drv_handle} {
    ucos_log_put "TRACE" "Generating ucos_ttcps."
    
    xdefine_include_file $drv_handle "xparameters.h" "UCOS_TTCPS" "NUM_INSTANCES" "DEVICE_ID" "C_S_AXI_BASEADDR" "C_TTC_CLK_FREQ_HZ" "C_TTC_CLK_CLKSRC"
    xdefine_config_file $drv_handle "ucos_ttcps_g.c" "UCOS_TTCPS"  "DEVICE_ID" "C_S_AXI_BASEADDR" "C_TTC_CLK_FREQ_HZ"
}
