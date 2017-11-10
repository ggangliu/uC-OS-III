ARCH_LIBSOURCES:=uC-CPU/MicroBlaze/GNU/cpu_a.S \
                 uC-CPU/MicroBlaze/GNU/cpu_c.c \
                 mb/cpu_bsp.c \
                 mb/cache/mb_flush_dcache_range.S \
                 mb/cache/mb_invalidate_dcache_range.S \
                 mb/cache/mb_dcache_init.c

ARCH_INCLUDEFILES:=${UCOS_SRC_BASE}/uC-CPU/MicroBlaze/GNU/cpu.h
