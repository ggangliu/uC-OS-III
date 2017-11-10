#########################################################################################################
#                                           MICRIUM XSDK REPOSITORY
#                         (c) Copyright 2014-2015; Micrium, Inc.; Weston, FL
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

LIBSOURCES:=ucos_startup.c \
            ucos_tcpip_init.c \
            ucos_stdinout.c \
            ucos_printf.c \
            mb/ucos_impl.c \
            mb/ucos_int_impl.c


INCLUDEFILES:=app_cfg.h \
              ucos_bsp.h \
              ucos_int.h \
              mb/ucos_int_impl.h
              

OBJECTS =	$(addsuffix .o, $(basename ${LIBSOURCES}))

libs: banner ucos_ucos_libs clean

%.o: %.c
	${COMPILER} $(CC_FLAGS) $(ECC_FLAGS) $(INCLUDES) -o $@ $<

%.o: %.s
	${COMPILER} $(CC_FLAGS) $(ECC_FLAGS) $(INCLUDES) -o $@ $<

banner:
	echo "Compiling uC/OS"

ucos_ucos_libs: ${OBJECTS}
	$(ARCHIVER) -r ${RELEASEDIR}/${LIB} ${OBJECTS}

.PHONY: include
include:
	${CP} ${INCLUDEFILES} ${INCLUDEDIR}

clean:
	rm -rf ${OBJECTS}

