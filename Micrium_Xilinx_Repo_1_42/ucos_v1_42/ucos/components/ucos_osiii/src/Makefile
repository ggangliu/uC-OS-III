#########################################################################################################
#                                           MICRIUM XSDK REPOSITORY
#                          (c) Copyright 2014-2015; Micrium, Inc.; Weston, FL
#
#               All rights reserved.  Protected by international copyright laws.
#########################################################################################################

COMPILER=
CP=cp
COMPILER_FLAGS=
EXTRA_COMPILER_FLAGS=
LIB=libucos.a

CC_FLAGS = $(COMPILER_FLAGS)
ECC_FLAGS = $(EXTRA_COMPILER_FLAGS)

RELEASEDIR=../../../lib
INCLUDEDIR=../../../include
INCLUDES=-I./. -I./uCOS-III/Source -I./uCOS-III -I./uCOS-III/Ports/ARM-Cortex-A/Generic/GNU -I${INCLUDEDIR}

OUTS = *.o

include ../../../include/Makefile_def.inc
include Makefile.inc

LIBSOURCES:=uCOS-III/Source/os_cfg_app.c \
            uCOS-III/Source/os_core.c \
            uCOS-III/Source/os_dbg.c \
            uCOS-III/Source/os_flag.c \
            uCOS-III/Source/os_int.c \
            uCOS-III/Source/os_mem.c \
            uCOS-III/Source/os_mon.c \
            uCOS-III/Source/os_msg.c \
            uCOS-III/Source/os_mutex.c \
            uCOS-III/Source/os_pend_multi.c \
            uCOS-III/Source/os_prio.c \
            uCOS-III/Source/os_q.c \
            uCOS-III/Source/os_sem.c \
            uCOS-III/Source/os_stat.c \
            uCOS-III/Source/os_task.c \
            uCOS-III/Source/os_tick.c \
            uCOS-III/Source/os_time.c \
            uCOS-III/Source/os_tmr.c \
            uCOS-III/Source/os_var.c

LIBSOURCES += $(ARCH_LIBSOURCES)

INCLUDEFILES:=os_cfg.h \
              os_cfg_app.h
              
INCLUDEFILES += $(ARCH_INCLUDEFILES)
              

OBJECTS =	$(addsuffix .o, $(basename ${LIBSOURCES}))

libs: banner ucos_osiii_libs clean

%.o: %.c
	${MKDIR} -p $(@D)
	${COMPILER} $(CC_FLAGS) $(ECC_FLAGS) $(INCLUDES) -o $@ $<
	

%.o: %.S
	${MKDIR} -p $(@D)
	${COMPILER} $(CC_FLAGS) $(ECC_FLAGS) $(INCLUDES) -o $@ $<

banner:
	echo "Compiling uC/OS-III"

ucos_osiii_libs: ${OBJECTS}
	$(ARCHIVER) -r ${RELEASEDIR}/${LIB} ${OBJECTS}

.PHONY: include
include:
	${CP} ${INCLUDEFILES} ${INCLUDEDIR}
	${CP} uCOS-III/Source/os.h ${INCLUDEDIR}/Source
	${CP} uCOS-III/Source/os_type.h ${INCLUDEDIR}/Source

clean:
	rm -rf ${OBJECTS}

