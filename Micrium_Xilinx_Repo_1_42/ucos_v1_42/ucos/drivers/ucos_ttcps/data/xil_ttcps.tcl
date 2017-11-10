##############################################################################
#
# (c) Copyright 2012-14 Xilinx, Inc. All rights reserved.
#
# This file contains confidential and proprietary information of Xilinx, Inc.
# and is protected under U.S. and international copyright and other
# intellectual property laws.
#
# DISCLAIMER
# This disclaimer is not a license and does not grant any rights to the
# materials distributed herewith. Except as otherwise provided in a valid
# license issued to you by Xilinx, and to the maximum extent permitted by
# applicable law: (1) THESE MATERIALS ARE MADE AVAILABLE "AS IS" AND WITH ALL
# FAULTS, AND XILINX HEREBY DISCLAIMS ALL WARRANTIES AND CONDITIONS, EXPRESS,
# IMPLIED, OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF
# MERCHANTABILITY, NON-INFRINGEMENT, OR FITNESS FOR ANY PARTICULAR PURPOSE;
# and (2) Xilinx shall not be liable (whether in contract or tort, including
# negligence, or under any other theory of liability) for any loss or damage
# of any kind or nature related to, arising under or in connection with these
# materials, including for any direct, or any indirect, special, incidental,
# or consequential loss or damage (including loss of data, profits, goodwill,
# or any type of loss or damage suffered as a result of any action brought by
# a third party) even if such damage or loss was reasonably foreseeable or
# Xilinx had been advised of the possibility of the same.
#
# CRITICAL APPLICATIONS
# Xilinx products are not designed or intended to be fail-safe, or for use in
# any application requiring fail-safe performance, such as life-support or
# safety devices or systems, Class III medical devices, nuclear facilities,
# applications related to the deployment of airbags, or any other applications
# that could lead to death, personal injury, or severe property or
# environmental damage (individually and collectively, "Critical
# Applications"). Customer assumes the sole risk and liability of any use of
# Xilinx products in Critical Applications, subject only to applicable laws
# and regulations governing limitations on product liability.
#
# THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS PART OF THIS FILE
# AT ALL TIMES.
#
##############################################################################

namespace import ::hsm::utils::*

proc xdefine_include_file {drv_handle file_name drv_string args} {
    # Open include file
    set file_handle [open_include_file $file_name]

    # Get all peripherals connected to this driver
    set periphs [get_common_driver_ips $drv_handle] 

    # Handle special cases
    set arg "NUM_INSTANCES"
    set posn [lsearch -exact $args $arg]
    if {$posn > -1} {
    puts $file_handle "/* Definitions for driver [string toupper [get_property NAME $drv_handle]] */"
    # Define NUM_INSTANCES
    puts $file_handle "#define [get_driver_param_name $drv_string $arg] [expr [llength $periphs] * 3]"
    set args [lreplace $args $posn $posn]
    }
    # Check if it is a driver parameter

    lappend newargs 
    foreach arg $args {
    set value [get_property CONFIG.$arg $drv_handle]
    if {[llength $value] == 0} {
        lappend newargs $arg
    } else {
        puts $file_handle "#define [get_driver_param_name $drv_string $arg] [get_property CONFIG.$arg $drv_handle]"
    }
    }
    set args $newargs

    # Print all parameters for all peripherals
    set device_id 0
    foreach periph $periphs {
    puts $file_handle ""
    puts $file_handle "/* Definitions for peripheral [string toupper [get_property NAME $periph]] */"
    for {set x 0} {$x<3} {incr x} {
        foreach arg $args {
        if {[string compare -nocase "DEVICE_ID" $arg] == 0} {
            set value [expr $device_id * 3 + $x]
        } elseif {[string compare -nocase "C_TTC_CLK_CLKSRC" $arg] == 0} {
                    set value [get_param_value $periph [format "C_TTC_CLK%d_CLKSRC" $x]]
        } elseif {[string compare -nocase "C_TTC_CLK_FREQ_HZ" $arg] == 0} {
                    set value [get_param_value $periph [format "C_TTC_CLK%d_FREQ_HZ" $x]]
                } else {
            set value [get_param_value $periph $arg]
        }
        if {[llength $value] == 0} {
            set value 0
        }
        set value [format_addr_string $value $arg]
        if {[string match C_* $arg]} {
            set arg_name [string range $arg 2 end]
        } else {
            set arg_name $arg
        }
        set arg_name [format "XPAR_%s_%d_%s" [string toupper [string range [get_property NAME $periph] 0 end-2]] [expr $device_id * 3 + $x] $arg_name]
        regsub "S_AXI_" $arg_name "" arg_name
        if {[string compare -nocase "C_S_AXI_BASEADDR" $arg] == 0} {
            puts $file_handle "#define $arg_name [string toupper [format 0x%08x [expr $value + $x * 4]]]"
        } else {
            puts $file_handle "#define $arg_name $value"
        }
        }
    }
    incr device_id
    puts $file_handle ""
    }       
    puts $file_handle "\n/******************************************************************/\n"
    close $file_handle
}


#
# Create configuration C file as required by Xilinx  drivers
#
proc xdefine_config_file {drv_handle file_name drv_string args} {
    set filename [file join "src" $file_name] 
    file delete $filename
    set config_file [open $filename w]
    write_c_header $config_file "Driver configuration"    
    puts $config_file "#include \"xparameters.h\""
    puts $config_file "#include \"[string tolower $drv_string].h\""
    puts $config_file "\n/*"
    puts $config_file "* The configuration table for devices"
    puts $config_file "*/\n"
    puts $config_file [format "%s_Config %s_ConfigTable\[\] =" $drv_string $drv_string]
    puts $config_file "\{"
    set periphs [get_common_driver_ips $drv_handle]     
    set start_comma ""
    set device_id 0
    foreach periph $periphs {
    for {set x 0} {$x<3} {incr x} {
        puts $config_file [format "%s\t\{" $start_comma]
        set comma ""
        foreach arg $args {
        # Check if this is a driver parameter or a peripheral parameter
        set value [get_property CONFIG.$arg $drv_handle]
        if {[llength $value] == 0} {
            set local_value [get_property CONFIG.$arg $periph]
            # If a parameter isn't found locally (in the current
            # peripheral), we will (for some obscure and ancient reason)
            # look in peripherals connected via point to point links
            if { [string compare -nocase $local_value ""] == 0} { 
            set p2p_name [get_p2p_name $periph $arg]
            if { [string compare -nocase $p2p_name ""] == 0} {
                if {[string match C_* $arg]} {
                set arg_name [string range $arg 2 end]
                } else {
                set arg_name $arg
                }
                set arg_name [format "XPAR_%s_%d_%s" [string toupper [string range [get_property NAME $periph] 0 end-2]] [expr $device_id * 3 + $x] $arg_name]
                regsub "S_AXI_" $arg_name "" arg_name
                puts -nonewline $config_file [format "%s\t\t%s" $comma $arg_name]
            } else {
                regsub "S_AXI_" $p2p_name "" p2p_name
                puts -nonewline $config_file [format "%s\t\t%s" $comma $p2p_name]
            }
            } else {
            if {[string match C_* $arg]} {
                set arg_name [string range $arg 2 end]
            } else {
                set arg_name $arg
            }
            set arg_name [format "XPAR_%s_%d_%s" [string toupper [string range [get_property NAME $periph] 0 end-2]] [expr $device_id * 3 + $x] $arg_name]
            regsub "S_AXI_" $arg_name "" arg_name
            puts -nonewline $config_file [format "%s\t\t%s" $comma $arg_name]
            }
        } else {
            set arg_name [get_driver_param_name $drv_string $arg]
            regsub "S_AXI_" $arg_name "" arg_name
            puts -nonewline $config_file [format "%s\t\t%s" $comma $arg_name]
        }
        set comma ",\n"
        }
        puts -nonewline $config_file "\n\t\}"
        set start_comma ",\n"
    }
    incr device_id
    }
    puts $config_file "\n\};"

    puts $config_file "\n";

    close $config_file
}
