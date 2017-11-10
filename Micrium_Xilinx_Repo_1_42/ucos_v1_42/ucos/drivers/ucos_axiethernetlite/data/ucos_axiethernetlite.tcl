#########################################################################################################
#                                           MICRIUM XSDK REPOSITORY
#                           (c) Copyright 2014-2015; Micrium, Inc.; Weston, FL
#
#               All rights reserved.  Protected by international copyright laws.
#########################################################################################################

source ../../../bsp/data/ucos_tcl_utils.tcl
source ../../../bsp/data/xil_tcl_utils.tcl

namespace import ::hsm::utils::*

proc generate {drv_handle} {
    ucos_log_put "TRACE" "Generating ucos_axiethernetlite."
    
    xdefine_include_file $drv_handle "xparameters.h" "UCOS_AXIETHERNETLITE" "NUM_INSTANCES" "DEVICE_ID" "C_BASEADDR" "C_HIGHADDR" "C_TX_PING_PONG" "C_RX_PING_PONG"
    
    ucos_define_intr_sources $drv_handle "UCOS_AXIETHERNETLITE"
    
    xdefine_config_file_intr $drv_handle "ucos_axiethernetlite_g.c" "UCOS_AXIETHERNETLITE"  "DEVICE_ID" "C_BASEADDR" "C_TX_PING_PONG" "C_RX_PING_PONG"
}
