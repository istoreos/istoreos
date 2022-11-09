/*
 * Helper for work with variadic macros
 *
 * 2017 Marek Behun, CZ.NIC, marek.behun@nic.cz
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __VARIADIC_MACRO_H__
#define __VARIADIC_MACRO_H__

#define _VM_GET_NTH_ARG(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, \
	_14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, \
	_28, _29, _30, _31, _32, N, ...) N

#define _VM_HELP_0(_call, ...)
#define _VM_HELP_1(_call, x, ...) _call(x)
#define _VM_HELP_2(_call, x, ...) _call(x) _VM_HELP_1(_call, __VA_ARGS__)
#define _VM_HELP_3(_call, x, ...) _call(x) _VM_HELP_2(_call, __VA_ARGS__)
#define _VM_HELP_4(_call, x, ...) _call(x) _VM_HELP_3(_call, __VA_ARGS__)
#define _VM_HELP_5(_call, x, ...) _call(x) _VM_HELP_4(_call, __VA_ARGS__)
#define _VM_HELP_6(_call, x, ...) _call(x) _VM_HELP_5(_call, __VA_ARGS__)
#define _VM_HELP_7(_call, x, ...) _call(x) _VM_HELP_6(_call, __VA_ARGS__)
#define _VM_HELP_8(_call, x, ...) _call(x) _VM_HELP_7(_call, __VA_ARGS__)
#define _VM_HELP_9(_call, x, ...) _call(x) _VM_HELP_8(_call, __VA_ARGS__)
#define _VM_HELP_10(_call, x, ...) _call(x) _VM_HELP_9(_call, __VA_ARGS__)
#define _VM_HELP_11(_call, x, ...) _call(x) _VM_HELP_10(_call, __VA_ARGS__)
#define _VM_HELP_12(_call, x, ...) _call(x) _VM_HELP_11(_call, __VA_ARGS__)
#define _VM_HELP_13(_call, x, ...) _call(x) _VM_HELP_12(_call, __VA_ARGS__)
#define _VM_HELP_14(_call, x, ...) _call(x) _VM_HELP_13(_call, __VA_ARGS__)
#define _VM_HELP_15(_call, x, ...) _call(x) _VM_HELP_14(_call, __VA_ARGS__)
#define _VM_HELP_16(_call, x, ...) _call(x) _VM_HELP_15(_call, __VA_ARGS__)
#define _VM_HELP_17(_call, x, ...) _call(x) _VM_HELP_16(_call, __VA_ARGS__)
#define _VM_HELP_18(_call, x, ...) _call(x) _VM_HELP_17(_call, __VA_ARGS__)
#define _VM_HELP_19(_call, x, ...) _call(x) _VM_HELP_18(_call, __VA_ARGS__)
#define _VM_HELP_20(_call, x, ...) _call(x) _VM_HELP_19(_call, __VA_ARGS__)
#define _VM_HELP_21(_call, x, ...) _call(x) _VM_HELP_20(_call, __VA_ARGS__)
#define _VM_HELP_22(_call, x, ...) _call(x) _VM_HELP_21(_call, __VA_ARGS__)
#define _VM_HELP_23(_call, x, ...) _call(x) _VM_HELP_22(_call, __VA_ARGS__)
#define _VM_HELP_24(_call, x, ...) _call(x) _VM_HELP_23(_call, __VA_ARGS__)
#define _VM_HELP_25(_call, x, ...) _call(x) _VM_HELP_24(_call, __VA_ARGS__)
#define _VM_HELP_26(_call, x, ...) _call(x) _VM_HELP_25(_call, __VA_ARGS__)
#define _VM_HELP_27(_call, x, ...) _call(x) _VM_HELP_26(_call, __VA_ARGS__)
#define _VM_HELP_28(_call, x, ...) _call(x) _VM_HELP_27(_call, __VA_ARGS__)
#define _VM_HELP_29(_call, x, ...) _call(x) _VM_HELP_28(_call, __VA_ARGS__)
#define _VM_HELP_30(_call, x, ...) _call(x) _VM_HELP_29(_call, __VA_ARGS__)
#define _VM_HELP_31(_call, x, ...) _call(x) _VM_HELP_30(_call, __VA_ARGS__)

#define CALL_MACRO_FOR_EACH(x, ...)					 \
	_VM_GET_NTH_ARG("", ##__VA_ARGS__, _VM_HELP_31, _VM_HELP_30,	 \
	_VM_HELP_29, _VM_HELP_28, _VM_HELP_27, _VM_HELP_26, _VM_HELP_25, \
	_VM_HELP_24, _VM_HELP_23, _VM_HELP_22, _VM_HELP_21, _VM_HELP_20, \
	_VM_HELP_19, _VM_HELP_18, _VM_HELP_17, _VM_HELP_16, _VM_HELP_15, \
	_VM_HELP_14, _VM_HELP_13, _VM_HELP_12, _VM_HELP_11, _VM_HELP_10, \
	_VM_HELP_9, _VM_HELP_8, _VM_HELP_7, _VM_HELP_6, _VM_HELP_5,	 \
	_VM_HELP_4, _VM_HELP_3, _VM_HELP_2, _VM_HELP_1,			 \
	_VM_HELP_0)(x, __VA_ARGS__)

#endif /* __VARIADIC_MACRO_H__ */
