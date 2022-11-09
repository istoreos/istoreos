#ifdef USE_HOSTCC
#include "../scripts/dtc/libfdt/libfdt_env.h"
#else
/*
 * This position of the include guard is intentional.
 * Using the same guard name as that of scripts/dtc/libfdt/libfdt_env.h
 * prevents it from being included.
 */
#ifndef _LIBFDT_ENV_H
#define _LIBFDT_ENV_H

#include <linux/string.h>

#include <asm/byteorder.h>

typedef __be16 fdt16_t;
typedef __be32 fdt32_t;
typedef __be64 fdt64_t;

#define fdt32_to_cpu(x) be32_to_cpu(x)
#define cpu_to_fdt32(x) cpu_to_be32(x)
#define fdt64_to_cpu(x) be64_to_cpu(x)
#define cpu_to_fdt64(x) cpu_to_be64(x)

/* U-Boot: for strtoul in fdt_overlay.c */
#include <vsprintf.h>

#define strtoul(cp, endp, base)	simple_strtoul(cp, endp, base)

#endif /* _LIBFDT_ENV_H */
#endif
