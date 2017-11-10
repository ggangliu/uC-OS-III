#########################################################################################################
#                                           MICRIUM XSDK REPOSITORY
#                             (c) Copyright 2014-2015; Micrium, Inc.; Weston, FL
#
#               All rights reserved.  Protected by international copyright laws.
#########################################################################################################

source ../../../bsp/data/ucos_tcl_utils.tcl
source ../../../bsp/data/xil_tcl_utils.tcl

namespace import ::hsm::utils::*

proc generate {drv_handle} {
    ucos_log_put "TRACE" "Generating ucos_emacps."
    
    xdefine_zynq_include_file $drv_handle "xparameters.h" "UCOS_EMACPS" "NUM_INSTANCES" "DEVICE_ID" "C_BASEADDR" "C_HIGHADDR" "CLOCK_FREQ_HZ"
    
    ucos_define_intr_sources $drv_handle "UCOS_EMACPS"
    
    xdefine_zynq_config_file_intr $drv_handle "ucos_emacps_g.c" "UCOS_EMACPS"  "DEVICE_ID" "C_BASEADDR" "CLOCK_FREQ_HZ"
    
    xdefine_zynq_canonical_xpars $drv_handle "xparameters.h" "UCOS_EMACPS" "NUM_INSTANCES" "DEVICE_ID" "C_BASEADDR" "C_HIGHADDR" "CLOCK_FREQ_HZ"
}
