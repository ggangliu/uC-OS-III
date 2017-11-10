#########################################################################################################
#                                           MICRIUM XSDK REPOSITORY
#                          (c) Copyright 2014-2015; Micrium, Inc.; Weston, FL
#
#               All rights reserved.  Protected by international copyright laws.
#########################################################################################################

proc swapp_get_name {} {
    return "Micrium TELNET Server example project.";
}

proc swapp_get_description {} {
    return "Basic TELNET server and minimal shell demonstration.";
}

proc swapp_is_supported_hw {} {
    return 1;
}

proc swapp_is_supported_sw {} {
    return 1;
}

proc swapp_generate {} {

}

proc swapp_get_linker_constraints {} {
    return "";
}

proc swapp_get_supported_processors {} {
    return "microblaze ps7_cortexa9 psu_cortexr5 psu_cortexa53";
}

proc swapp_get_supported_os {} {
    return "ucos";
}
