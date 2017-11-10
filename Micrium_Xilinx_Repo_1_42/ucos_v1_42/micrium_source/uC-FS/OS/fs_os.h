#include  <fs_cfg.h>

#ifdef  FS_CFG_OS_PORT
    #define   FS_OS_PORT_INCLUDE_FILE3(full_path)  #full_path
    #define   FS_OS_PORT_INCLUDE_FILE2(port)       FS_OS_PORT_INCLUDE_FILE3(port/fs_os.h)
    #define   FS_OS_PORT_INCLUDE_FILE              FS_OS_PORT_INCLUDE_FILE2(FS_CFG_OS_PORT)
    #include  FS_OS_PORT_INCLUDE_FILE
#else
    #include  <fs_os.h>  /* Include 'fs_os.h' that is in root of an include path. */
#endif

