#########################################################################################################
#                                           MICRIUM XSDK REPOSITORY
#                           (c) Copyright 2014-2015; Micrium, Inc.; Weston, FL
#
#               All rights reserved.  Protected by international copyright laws.
#########################################################################################################

source ../../../bsp/data/ucos_tcl_utils.tcl
source ../../../bsp/data/xil_tcl_utils.tcl

source ./axiethernet.tcl

namespace import ::hsm::utils::*

proc generate {drv_handle} {
    xdefine_axiethernet_include_file $drv_handle "xparameters.h" "UCOS_AXIETHERNET"
    
    xdefine_axiethernet_config_file  "ucos_axiethernet_g.c" "UCOS_AXIETHERNET"
}
