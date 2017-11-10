#########################################################################################################
#                                           MICRIUM XSDK REPOSITORY
#                             (c) Copyright 2014-2015; Micrium, Inc.; Weston, FL
#
#               All rights reserved.  Protected by international copyright laws.
#########################################################################################################

source ../../../bsp/data/ucos_tcl_utils.tcl
source ../../../bsp/data/xil_tcl_utils.tcl

proc generate {drv_handle} {
    ucos_log_put "TRACE" "Generating ucos_scutimer."
    
    xdefine_zynq_include_file $drv_handle "xparameters.h" "UCOS_SCUC" "NUM_INSTANCES" "DEVICE_ID" "C_S_AXI_BASEADDR" "C_S_AXI_HIGHADDR"
}

