#########################################################################################################
#                                           MICRIUM XSDK REPOSITORY
#                             (c) Copyright 2014-2015; Micrium, Inc.; Weston, FL
#
#               All rights reserved.  Protected by international copyright laws.
#########################################################################################################

source ../../../bsp/data/ucos_tcl_utils.tcl
source ../../../bsp/data/xil_tcl_utils.tcl

proc generate {ucos_handle} {
    ucos_log_put "TRACE" "Generating ucos_usbd."
    
    set ucos_src_base [ucos_get_source_base]
    set usbd_src_base [ucos_get_product_source_base usbd]
    
    if {[llength $usbd_src_base] == 0} {
        set source_avail 0
        set usbd_src_base $ucos_src_base
    }
   
    file copy -force "$usbd_src_base/uC-USB-Device/Cfg/Template/usbd_cfg.h" "./src"
    
    file copy -force "$usbd_src_base/uC-USB-Device" "./src/uC-USB-Device"
    
    file mkdir "../../include/Source"
    file mkdir "../../include/Class/Audio"
    file mkdir "../../include/Class/CDC"
    file mkdir "../../include/Class/CDC/ACM"
    file mkdir "../../include/Class/CDC-EEM"
    file mkdir "../../include/Class/HID"
    file mkdir "../../include/Class/MSC"
    file mkdir "../../include/Class/PHDC"
    file mkdir "../../include/Class/Vendor"
    file mkdir "../../include/Class/MSC"
    file mkdir "../../include/Class/MSC/Storage"
    file mkdir "../../include/Class/MSC/Storage/uC-FS"
    file mkdir "../../include/Class/MSC/Storage/uC-FS/V4"
    file mkdir "../../include/Class/MSC/Storage/RAMDisk"
    file mkdir "../../include/Drivers/synopsys_otg_hs"
    
    set msc_storage_drv [get_property CONFIG.USBD_MDC_CFG_STORAGE_DRIVER $ucos_handle]
    if {$msc_storage_drv == "auto"} {
       if {[llength [get_libs -filter "NAME==ucos_fs"]] != 0} {
           set msc_storage_drv uC_FS_V4
       } else {
           set msc_storage_drv RAMDisk
       }
    }
    
    set file_handle [open "./src/Makefile_def_usbd.inc" w]
    set config_file [open_include_file "xparameters.h"]
    if {$msc_storage_drv == "uC_FS_V4"} {
        puts $file_handle "UCOS_USBD_STORAGE_DRV = UCFS"
        puts $config_file "#define UCOS_USBD_STORAGE_DRV UCOS_USBD_STORAGE_DRV_FS"
    } else {
        puts $file_handle "UCOS_USBD_STORAGE_DRV = RAMDISK"
        puts $config_file "#define UCOS_USBD_STORAGE_DRV UCOS_USBD_STORAGE_DRV_RAM"
    }
    
    set_define "./src/usbd_cfg.h" "USBD_CFG_OPTIMIZE_SPD"       [expr ([get_property CONFIG.USBD_CFG_OPTIMIZE_SPD           $ucos_handle] == true)?"DEF_ENABLED":"DEF_DISABLED"]
    set_define "./src/usbd_cfg.h" "USBD_CFG_MAX_NBR_DEV"        [format "%u" [get_property CONFIG.USBD_CFG_MAX_NBR_DEV      $ucos_handle]]
    set_define "./src/usbd_cfg.h" "USBD_CFG_BUF_ALIGN_OCTETS"   [format "%u" [get_property CONFIG.USBD_CFG_BUF_ALIGN_OCTETS $ucos_handle]]
    set_define "./src/usbd_cfg.h" "USBD_CFG_ERR_ARG_CHK_EXT_EN" [expr ([get_property CONFIG.USBD_CFG_ERR_ARG_CHK_EXT_EN     $ucos_handle] == true)?"DEF_ENABLED":"DEF_DISABLED"]

    set_define "./src/usbd_cfg.h" "USBD_CFG_MS_OS_DESC_EN" [expr ([get_property CONFIG.USBD_CFG_MS_OS_DESC_EN     $ucos_handle] == true)?"DEF_ENABLED":"DEF_DISABLED"]
         
    set_define "./src/usbd_cfg.h" "USBD_CFG_MAX_NBR_CFG" [format "%u" [get_property CONFIG.USBD_CFG_MAX_NBR_CFG $ucos_handle]]
    set_define "./src/usbd_cfg.h" "USBD_CFG_EP_ISOC_EN"  [expr ([get_property CONFIG.USBD_CFG_EP_ISOC_EN        $ucos_handle] == true)?"DEF_ENABLED":"DEF_DISABLED"]
    set_define "./src/usbd_cfg.h" "USBD_CFG_HS_EN"       [expr ([get_property CONFIG.USBD_CFG_HS_EN             $ucos_handle] == true)?"DEF_ENABLED":"DEF_DISABLED"]
    
    set_define "./src/usbd_cfg.h" "USBD_CFG_MAX_NBR_IF"        [format "%u" [get_property CONFIG.USBD_CFG_MAX_NBR_IF        $ucos_handle]]
    set_define "./src/usbd_cfg.h" "USBD_CFG_MAX_NBR_IF_ALT"    [format "%u" [get_property CONFIG.USBD_CFG_MAX_NBR_IF_ALT    $ucos_handle]]
    set_define "./src/usbd_cfg.h" "USBD_CFG_MAX_NBR_IF_GRP"    [format "%u" [get_property CONFIG.USBD_CFG_MAX_NBR_IF_GRP    $ucos_handle]]
    set_define "./src/usbd_cfg.h" "USBD_CFG_MAX_NBR_EP_DESC"   [format "%u" [get_property CONFIG.USBD_CFG_MAX_NBR_EP_DESC   $ucos_handle]]
    set_define "./src/usbd_cfg.h" "USBD_CFG_MAX_NBR_EP_OPEN"   [format "%u" [get_property CONFIG.USBD_CFG_MAX_NBR_EP_OPEN   $ucos_handle]]
    set_define "./src/usbd_cfg.h" "USBD_CFG_MAX_NBR_URB_EXTRA" [format "%u" [get_property CONFIG.USBD_CFG_MAX_NBR_URB_EXTRA $ucos_handle]]
    
    set_define "./src/usbd_cfg.h" "USBD_CFG_MAX_NBR_STR" [format "%u" [get_property CONFIG.USBD_CFG_MAX_NBR_STR $ucos_handle]]
    
    set_define "./src/usbd_cfg.h" "USBD_CFG_DBG_TRACE_EN"         [expr ([get_property CONFIG.USBD_CFG_DBG_TRACE_EN               $ucos_handle] == true)?"DEF_ENABLED":"DEF_DISABLED"]
    set_define "./src/usbd_cfg.h" "USBD_CFG_DBG_TRACE_NBR_EVENTS" [format "%u" [get_property CONFIG.USBD_CFG_DBG_TRACE_NBR_EVENTS $ucos_handle]]
    set_define "./src/usbd_cfg.h" "USBD_CFG_DBG_STATS_EN"         [expr ([get_property CONFIG.USBD_CFG_DBG_STATS_EN               $ucos_handle] == true)?"DEF_ENABLED":"DEF_DISABLED"]
    #Counter type
    
    set_define "./src/usbd_cfg.h" "USBD_AUDIO_CFG_PLAYBACK_EN"          [expr ([get_property CONFIG.USBD_AUDIO_CFG_PLAYBACK_EN             $ucos_handle] == true)?"DEF_ENABLED":"DEF_DISABLED"]
    set_define "./src/usbd_cfg.h" "USBD_AUDIO_CFG_RECORD_EN"            [expr ([get_property CONFIG.USBD_AUDIO_CFG_RECORD_EN               $ucos_handle] == true)?"DEF_ENABLED":"DEF_DISABLED"]
    set_define "./src/usbd_cfg.h" "USBD_AUDIO_CFG_FU_MAX_CTRL"          [expr ([get_property CONFIG.USBD_AUDIO_CFG_FU_MAX_CTRL             $ucos_handle] == true)?"DEF_ENABLED":"DEF_DISABLED"]
    set_define "./src/usbd_cfg.h" "USBD_AUDIO_CFG_MAX_NBR_AIC"          [format "%u" [get_property CONFIG.USBD_AUDIO_CFG_MAX_NBR_AIC       $ucos_handle]]
    set_define "./src/usbd_cfg.h" "USBD_AUDIO_CFG_MAX_NBR_CFG"          [format "%u" [get_property CONFIG.USBD_AUDIO_CFG_MAX_NBR_CFG       $ucos_handle]]
    set_define "./src/usbd_cfg.h" "USBD_AUDIO_CFG_MAX_NBR_IT"           [format "%u" [get_property CONFIG.USBD_AUDIO_CFG_MAX_NBR_IT        $ucos_handle]]
    set_define "./src/usbd_cfg.h" "USBD_AUDIO_CFG_MAX_NBR_OT"           [format "%u" [get_property CONFIG.USBD_AUDIO_CFG_MAX_NBR_OT        $ucos_handle]]
    set_define "./src/usbd_cfg.h" "USBD_AUDIO_CFG_MAX_NBR_FU"           [format "%u" [get_property CONFIG.USBD_AUDIO_CFG_MAX_NBR_FU        $ucos_handle]]
    set_define "./src/usbd_cfg.h" "USBD_AUDIO_CFG_MAX_NBR_MU"           [format "%u" [get_property CONFIG.USBD_AUDIO_CFG_MAX_NBR_MU        $ucos_handle]]
    set_define "./src/usbd_cfg.h" "USBD_AUDIO_CFG_MAX_NBR_SU"           [format "%u" [get_property CONFIG.USBD_AUDIO_CFG_MAX_NBR_SU        $ucos_handle]]
    set_define "./src/usbd_cfg.h" "USBD_AUDIO_CFG_MAX_NBR_AS_IF"        [format "%u" [get_property CONFIG.USBD_AUDIO_CFG_MAX_NBR_AS_IF     $ucos_handle]]
    set_define "./src/usbd_cfg.h" "USBD_AUDIO_CFG_MAX_NBR_IF_ALT"       [format "%u" [get_property CONFIG.USBD_AUDIO_CFG_MAX_NBR_IF_ALT    $ucos_handle]]
    set_define "./src/usbd_cfg.h" "USBD_AUDIO_CFG_CLASS_REQ_MAX_LEN"    [format "%u" [get_property CONFIG.USBD_AUDIO_CFG_CLASS_REQ_MAX_LEN $ucos_handle]]
    set_define "./src/usbd_cfg.h" "USBD_AUDIO_CFG_BUF_ALIGN_OCTETS"     [format "%u" [get_property CONFIG.USBD_AUDIO_CFG_BUF_ALIGN_OCTETS  $ucos_handle]]
    set_define "./src/usbd_cfg.h" "USBD_AUDIO_CFG_PLAYBACK_FEEDBACK_EN" [expr ([get_property CONFIG.USBD_AUDIO_CFG_PLAYBACK_FEEDBACK_EN    $ucos_handle] == true)?"DEF_ENABLED":"DEF_DISABLED"]
    set_define "./src/usbd_cfg.h" "USBD_AUDIO_CFG_PLAYBACK_CORR_EN"     [expr ([get_property CONFIG.USBD_AUDIO_CFG_PLAYBACK_CORR_EN        $ucos_handle] == true)?"DEF_ENABLED":"DEF_DISABLED"]
    set_define "./src/usbd_cfg.h" "USBD_AUDIO_CFG_RECORD_CORR_EN"       [expr ([get_property CONFIG.USBD_AUDIO_CFG_RECORD_CORR_EN          $ucos_handle] == true)?"DEF_ENABLED":"DEF_DISABLED"]
    set_define "./src/usbd_cfg.h" "USBD_AUDIO_CFG_STAT_EN"              [expr ([get_property CONFIG.USBD_AUDIO_CFG_STAT_EN                 $ucos_handle] == true)?"DEF_ENABLED":"DEF_DISABLED"]
    
    set_define "./src/usbd_cfg.h" "USBD_CDC_CFG_MAX_NBR_DEV"     [format "%u" [get_property CONFIG.USBD_CDC_CFG_MAX_NBR_DEV     $ucos_handle]]
    set_define "./src/usbd_cfg.h" "USBD_CDC_CFG_MAX_NBR_CFG"     [format "%u" [get_property CONFIG.USBD_CDC_CFG_MAX_NBR_CFG     $ucos_handle]]
    set_define "./src/usbd_cfg.h" "USBD_CDC_CFG_MAX_NBR_DATA_IF" [format "%u" [get_property CONFIG.USBD_CDC_CFG_MAX_NBR_DATA_IF $ucos_handle]]
    
    set_define "./src/usbd_cfg.h" "USBD_ACM_SERIAL_CFG_MAX_NBR_DEV" [format "%u" [get_property CONFIG.USBD_ACM_SERIAL_CFG_MAX_NBR_DEV $ucos_handle]]
    
    set_define "./src/usbd_cfg.h" "USBD_CDC_EEM_CFG_MAX_NBR_DEV"  [format "%u" [get_property CONFIG.USBD_CDC_EEM_CFG_MAX_NBR_DEV  $ucos_handle]]
    set_define "./src/usbd_cfg.h" "USBD_CDC_EEM_CFG_MAX_NBR_CFG"  [format "%u" [get_property CONFIG.USBD_CDC_EEM_CFG_MAX_NBR_CFG  $ucos_handle]]
    set_define "./src/usbd_cfg.h" "USBD_CDC_EEM_CFG_RX_BUF_LEN"   [format "%u" [get_property CONFIG.USBD_CDC_EEM_CFG_RX_BUF_LEN   $ucos_handle]]
    set_define "./src/usbd_cfg.h" "USBD_CDC_EEM_CFG_ECHO_BUF_LEN" [format "%u" [get_property CONFIG.USBD_CDC_EEM_CFG_ECHO_BUF_LEN $ucos_handle]]
    
    set_define "./src/usbd_cfg.h" "USBD_HID_CFG_MAX_NBR_DEV"            [format "%u" [get_property CONFIG.USBD_HID_CFG_MAX_NBR_DEV            $ucos_handle]]
    set_define "./src/usbd_cfg.h" "USBD_HID_CFG_MAX_NBR_CFG"            [format "%u" [get_property CONFIG.USBD_HID_CFG_MAX_NBR_CFG            $ucos_handle]]
    set_define "./src/usbd_cfg.h" "USBD_HID_CFG_MAX_NBR_REPORT_ID"      [format "%u" [get_property CONFIG.USBD_HID_CFG_MAX_NBR_REPORT_ID      $ucos_handle]]
    set_define "./src/usbd_cfg.h" "USBD_HID_CFG_MAX_NBR_REPORT_PUSHPOP" [format "%u" [get_property CONFIG.USBD_HID_CFG_MAX_NBR_REPORT_PUSHPOP $ucos_handle]]
    
    set_define "./src/usbd_cfg.h" "USBD_MSC_CFG_MAX_NBR_DEV"        [format "%u" [get_property CONFIG.USBD_MSC_CFG_MAX_NBR_DEV     $ucos_handle]]
    set_define "./src/usbd_cfg.h" "USBD_MSC_CFG_MAX_NBR_CFG"        [format "%u" [get_property CONFIG.USBD_MSC_CFG_MAX_NBR_CFG     $ucos_handle]]
    set_define "./src/usbd_cfg.h" "USBD_MSC_CFG_MAX_LUN"            [format "%u" [get_property CONFIG.USBD_MSC_CFG_MAX_LUN         $ucos_handle]]
    set_define "./src/usbd_cfg.h" "USBD_MSC_CFG_DATA_LEN"           [format "%u" [get_property CONFIG.USBD_MSC_CFG_DATA_LEN        $ucos_handle]]
    set_define "./src/usbd_cfg.h" "USBD_MSC_CFG_FS_REFRESH_TASK_EN" [expr ([get_property CONFIG.USBD_MSC_CFG_FS_REFRESH_TASK_EN    $ucos_handle] == true)?"DEF_ENABLED":"DEF_DISABLED"]
    set_define "./src/usbd_cfg.h" "USBD_MSC_CFG_DEV_POLL_DLY_mS"    [format "%u" [get_property CONFIG.USBD_MSC_CFG_DEV_POLL_DLY_mS $ucos_handle]]
    
    set_define "./src/usbd_cfg.h" "USBD_PHDC_CFG_MAX_NBR_DEV"         [format "%u" [get_property CONFIG.USBD_PHDC_CFG_MAX_NBR_DEV         $ucos_handle]]
    set_define "./src/usbd_cfg.h" "USBD_PHDC_CFG_MAX_NBR_CFG"         [format "%u" [get_property CONFIG.USBD_PHDC_CFG_MAX_NBR_CFG         $ucos_handle]]
    set_define "./src/usbd_cfg.h" "USBD_PHDC_CFG_DATA_OPAQUE_MAX_LEN" [format "%u" [get_property CONFIG.USBD_PHDC_CFG_DATA_OPAQUE_MAX_LEN $ucos_handle]]
    set_define "./src/usbd_cfg.h" "USBD_PHDC_OS_CFG_SCHED_EN"         [expr ([get_property CONFIG.USBD_PHDC_OS_CFG_SCHED_EN               $ucos_handle] == true)?"DEF_ENABLED":"DEF_DISABLED"]
    
    set_define "./src/usbd_cfg.h" "USBD_VENDOR_CFG_MAX_NBR_DEV"             [format "%u" [get_property CONFIG.USBD_VENDOR_CFG_MAX_NBR_DEV             $ucos_handle]]
    set_define "./src/usbd_cfg.h" "USBD_VENDOR_CFG_MAX_NBR_CFG"             [format "%u" [get_property CONFIG.USBD_VENDOR_CFG_MAX_NBR_CFG             $ucos_handle]]
    set_define "./src/usbd_cfg.h" "USBD_VENDOR_CFG_MAX_NBR_MS_EXT_PROPERTY" [format "%u" [get_property CONFIG.USBD_VENDOR_CFG_MAX_NBR_MS_EXT_PROPERTY $ucos_handle]]
    
    
    set config_file [open_include_file "xparameters.h"]
    set core_prio [get_property CONFIG.USBD_OS_CFG_CORE_TASK_PRIO $ucos_handle]
    set core_stack [get_property CONFIG.USBD_OS_CFG_CORE_TASK_STK_SIZE $ucos_handle]
    set trace_prio [get_property CONFIG.USBD_OS_CFG_TRACE_TASK_PRIO $ucos_handle]
    set trace_stack [get_property CONFIG.USBD_OS_CFG_TRACE_TASK_STK_SIZE $ucos_handle]
    set hid_prio [get_property CONFIG.USBD_HID_OS_CFG_TMR_TASK_PRIO $ucos_handle]
    set hid_stack [get_property CONFIG.USBD_HID_OS_CFG_TMR_TASK_STK_SIZE $ucos_handle]
    set phdc_prio [get_property CONFIG.USBD_PHDC_OS_CFG_SCHED_TASK_PRIO $ucos_handle]
    set phdc_stack [get_property CONFIG.USBD_PHDC_OS_CFG_SCHED_TASK_STK_SIZE $ucos_handle]
    set msc_prio [get_property CONFIG.USBD_MSC_OS_CFG_TASK_PRIO $ucos_handle]
    set msc_stack [get_property CONFIG.USBD_MSC_OS_CFG_TASK_STK_SIZE $ucos_handle]
    set ref_prio [get_property CONFIG.USBD_MSC_OS_CFG_REFRESH_TASK_PRIO $ucos_handle]
    set ref_stack [get_property CONFIG.USBD_MSC_OS_CFG_REFRESH_TASK_STK_SIZE $ucos_handle]
    set ref_dly [get_property CONFIG.USBD_MSC_CFG_DEV_POLL_DLY_mS $ucos_handle]
    
    puts $config_file "#define USBD_OS_CFG_CORE_TASK_PRIO $core_prio"
    puts $config_file "#define USBD_OS_CFG_CORE_TASK_STK_SIZE $core_stack"
    puts $config_file "#define USBD_OS_CFG_TRACE_TASK_PRIO $trace_prio"
    puts $config_file "#define USBD_OS_CFG_TRACE_TASK_STK_SIZE $trace_stack"
    puts $config_file "#define USBD_HID_OS_CFG_TMR_TASK_PRIO $hid_prio"
    puts $config_file "#define USBD_HID_OS_CFG_TMR_TASK_STK_SIZE $hid_stack"
    puts $config_file "#define USBD_PHDC_OS_CFG_SCHED_TASK_PRIO $phdc_prio"
    puts $config_file "#define USBD_PHDC_OS_CFG_SCHED_TASK_STK_SIZE $phdc_stack"
    puts $config_file "#define USBD_MSC_OS_CFG_TASK_PRIO $msc_prio"
    puts $config_file "#define USBD_MSC_OS_CFG_TASK_STK_SIZE $msc_stack"
    puts $config_file "#define USBD_MSC_OS_CFG_REFRESH_TASK_PRIO $ref_prio"
    puts $config_file "#define USBD_MSC_OS_CFG_REFRESH_TASK_STK_SIZE $ref_stack"
    puts $config_file "#define USBD_MSC_CFG_DEV_POLL_DLY_mS $ref_dly"
    
    
    set ramdisk_blk_size [get_property CONFIG.USBD_RAMDISK_CFG_BLK_SIZE $ucos_handle]
    set ramdisk_blk_cnt [get_property CONFIG.USBD_RAMDISK_CFG_NBR_BLKS $ucos_handle]
    set ramdisk_unit_cnt [get_property CONFIG.USBD_RAMDISK_CFG_NBR_UNITS $ucos_handle]
    set ramdisk_base_addr [get_property CONFIG.USBD_RAMDISK_CFG_BASE_ADDR $ucos_handle]
    
    puts $config_file "#define USBD_RAMDISK_CFG_BLK_SIZE $ramdisk_blk_size"
    puts $config_file "#define USBD_RAMDISK_CFG_NBR_BLKS $ramdisk_blk_cnt"
    puts $config_file "#define USBD_RAMDISK_CFG_NBR_UNITS $ramdisk_unit_cnt"
    puts $config_file "#define USBD_RAMDISK_CFG_BASE_ADDR $ramdisk_base_addr"
    
}
