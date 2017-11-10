#########################################################################################################
#                                           MICRIUM XSDK REPOSITORY
#                             (c) Copyright 2014-2015; Micrium, Inc.; Weston, FL
#
#               All rights reserved.  Protected by international copyright laws.
#########################################################################################################

source ../../../bsp/data/ucos_tcl_utils.tcl
source ../../../bsp/data/xil_tcl_utils.tcl

proc generate {ucos_handle} {

    ucos_log_put "TRACE" "Generating ucos_can."
    
    set ucos_src_base [ucos_get_source_base]
    set can_src_base [ucos_get_product_source_base can]

    set source_avail 1
    if {[llength $can_src_base] == 0} {
        set source_avail 0
        set can_src_base $ucos_src_base
    }

    file copy -force "$can_src_base/uC-CAN" "./src/uC-CAN"
    #file copy -force "$can_src_base/uC-CAN/Cfg/Template/can_cfg.h" "./src/can_cfg.h"
    #file copy -force "$can_src_base/uC-CAN/Cfg/Template/can_cfg.c" "./src/can_cfg.c"
     
}
