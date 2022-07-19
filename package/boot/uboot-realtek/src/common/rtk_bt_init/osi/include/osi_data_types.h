
#ifndef OSI_DATA_TYPES_H
#define OSI_DATA_TYPES_H

#include "osi_include_ext.h"

#ifndef bool
#define bool u8
#endif

#ifndef true
#define true    1
#endif

#ifndef false
#define false   0
#endif

#ifndef TRUE
#define TRUE   true
#endif

#ifndef FALSE
#define FALSE   false
#endif

typedef signed char s8;
typedef unsigned char u8;

typedef signed short s16;
typedef unsigned short u16;

typedef signed int s32;
typedef unsigned int u32;

typedef signed long long s64;
typedef unsigned long long u64;

typedef bool BOOLEAN;


#endif

