#########################################################################################################
#                                           MICRIUM XSDK REPOSITORY
#                            (c) Copyright 2014-2015; Micrium, Inc.; Weston, FL
#
#               All rights reserved.  Protected by international copyright laws.
#########################################################################################################

COMPILER=
ARCHIVER=
CP=cp
COMPILER_FLAGS=
EXTRA_COMPILER_FLAGS=
LIB=libucos.a

CC_FLAGS = $(COMPILER_FLAGS)
ECC_FLAGS = $(EXTRA_COMPILER_FLAGS)

RELEASEDIR=../../../lib
INCLUDEDIR=../../../include
INCLUDES=-I./. -I./uCOS-II/Source -I${INCLUDEDIR}

OUTS = *.o

include Makefile.inc

LIBSOURCES:=uCOS-II/Source/os_core.c \
            uCOS-II/Source/os_dbg_r.c \
            uCOS-II/Source/os_flag.c \
            uCOS-II/Source/os_mbox.c \
            uCOS-II/Source/os_mem.c \
            uCOS-II/Source/os_mutex.c \
            uCOS-II/Source/os_q.c \
            uCOS-II/Source/os_sem.c \
            uCOS-II/Source/os_task.c \
            uCOS-II/Source/os_time.c \
            uCOS-II/Source/os_tmr.c

LIBSOURCES += $(ARCH_LIBSOURCES)
            
            
INCLUDEFILES:=os_cfg.h
              
INCLUDEFILES += $(ARCH_INCLUDEFILES)
            
            
OBJECTS =	$(addsuffix .o, $(basename ${LIBSOURCES}))

libs: banner ucos_osii_libs clean

%.o: %.c
	${COMPILER} $(CC_FLAGS) $(ECC_FLAGS) $(INCLUDES) -o $@ $<

%.o: %.S
	${COMPILER} $(CC_FLAGS) $(ECC_FLAGS) $(INCLUDES) -o $@ $<

banner:
	echo "Compiling uC/OS-II"

ucos_osii_libs: ${OBJECTS}
	$(ARCHIVER) -r ${RELEASEDIR}/${LIB} ${OBJECTS}

.PHONY: include
include:
	${CP} ${INCLUDEFILES} ${INCLUDEDIR}
	${CP} uCOS-II/Source/os.h ${INCLUDEDIR}/Source
	${CP} uCOS-II/Source/ucos_ii.h ${INCLUDEDIR}/Source

clean:
	rm -rf ${OBJECTS}

