#########################################################################################################
#                                           MICRIUM XSDK REPOSITORY
#                           (c) Copyright 2014-2015; Micrium, Inc.; Weston, FL
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
INCLUDES=-I./. -I${INCLUDEDIR}

OUTS = *.o

include ../../../include/Makefile_def.inc

LIBSOURCES:=bench.c \
            bench_ctxsw.c \
            bench_flagpend.c \
            bench_flagpend_noctxsw.c \
            bench_flagpost.c \
            bench_flagpost_noctxsw.c \
            bench_global.c \
            bench_isrctxsw.c \
            bench_isrrecovery.c \
            bench_isrresp.c \
            bench_isrsempost.c \
            bench_memcpy.c \
            bench_memcpy_libc.c \
            bench_memcpy_ocram_dest.c \
            bench_memcpy_ocram_dest_libc.c \
            bench_memcpy_ocram_src.c \
            bench_memcpy_ocram_src_libc.c \
            bench_qpend.c \
            bench_qpend_noctxsw.c \
            bench_qpost.c \
            bench_qpost_noctxsw.c \
            bench_sempend.c \
            bench_sempend_noctxsw.c \
            bench_sempost.c \
            bench_sempost_noctxsw.c \
            bench_taskqpend.c \
            bench_taskqpend_noctxsw.c \
            bench_taskqpost.c \
            bench_taskqpost_noctxsw.c \
            bench_tasksempend.c \
            bench_tasksempend_noctxsw.c \
            bench_tasksempost.c \
            bench_tasksempost_noctxsw.c \
            app_bench.c


INCLUDEFILES:=bench.h \
              bench_cfg.h

OBJECTS = $(addsuffix .o, $(basename ${LIBSOURCES}))

libs: banner ucos_final_libs clean

%.o: %.c
	${COMPILER} $(CC_FLAGS) $(ECC_FLAGS) $(INCLUDES) -o $@ $<

%.o: %.s
	${COMPILER} $(CC_FLAGS) $(ECC_FLAGS) $(INCLUDES) -o $@ $<

banner:
	echo "Compiling uC/OS perfomance benchmarks"
	
ucos_final_libs: ${OBJECTS}
	$(ARCHIVER) -r ${RELEASEDIR}/${LIB} ${OBJECTS}

.PHONY: include
include:
	${CP} ${INCLUDEFILES} ${INCLUDEDIR}


clean:
	rm -rf ${OBJECTS}

