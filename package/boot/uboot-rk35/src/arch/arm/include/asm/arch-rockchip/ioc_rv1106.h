/*
 * (C) Copyright 2022 Rockchip Electronics Co., Ltd.
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */
#ifndef _ASM_ARCH_IOC_RV1106_H
#define _ASM_ARCH_IOC_RV1106_H

#include <common.h>

struct rv1106_gpio0_ioc {
	unsigned int gpio0a_iomux_sel_l;
	unsigned int gpio0a_iomux_sel_h;
	unsigned int reserved0[(0x0010 - 0x0004) / 4 - 1];
	unsigned int gpio0a_ds0;
	unsigned int gpio0a_ds1;
	unsigned int gpio0a_ds2;
	unsigned int gpio0a_ds3;
	unsigned int reserved1[(0x0030 - 0x001c) / 4 - 1];
	unsigned int gpio0a_ie;
	unsigned int reserved2[(0x0038 - 0x0030) / 4 - 1];
	unsigned int gpio0a_p;
	unsigned int reserved3[(0x0040 - 0x0038) / 4 - 1];
	unsigned int gpio0a_sus;
	unsigned int reserved4[(0x0048 - 0x0040) / 4 - 1];
	unsigned int gpio0a_sl;
	unsigned int reserved5[(0x0058 - 0x0048) / 4 - 1];
	unsigned int gpio0a_ie_smt;
	unsigned int reserved6[(0x0068 - 0x0058) / 4 - 1];
	unsigned int gpio0a_od;
};
check_member(rv1106_gpio0_ioc, gpio0a_od, 0x0068);

struct rv1106_gpio1_ioc {
	unsigned int gpio1a_iomux_sel_l;
	unsigned int gpio1a_iomux_sel_h;
	unsigned int gpio1b_iomux_sel_l;
	unsigned int reserved0[(0x0010 - 0x0008) / 4 - 1];
	unsigned int gpio1c_iomux_sel_l;
	unsigned int gpio1c_iomux_sel_h;
	unsigned int gpio1d_iomux_sel_l;
	unsigned int reserved1[(0x0080 - 0x0018) / 4 - 1];
	unsigned int gpio1a_ds0;
	unsigned int gpio1a_ds1;
	unsigned int gpio1a_ds2;
	unsigned int reserved2[(0x0090 - 0x0088) / 4 - 1];
	unsigned int gpio1b_ds0;
	unsigned int gpio1b_ds1;
	unsigned int reserved3[(0x00a0 - 0x0094) / 4 - 1];
	unsigned int gpio1c_ds0;
	unsigned int gpio1c_ds1;
	unsigned int gpio1c_ds2;
	unsigned int gpio1c_ds3;
	unsigned int gpio1d_ds0;
	unsigned int gpio1d_ds1;
	unsigned int reserved4[(0x0180 - 0x00b4) / 4 - 1];
	unsigned int gpio1a_ie;
	unsigned int gpio1b_ie;
	unsigned int gpio1c_ie;
	unsigned int gpio1d_ie;
	unsigned int reserved5[(0x01c0 - 0x018c) / 4 - 1];
	unsigned int gpio1a_p;
	unsigned int gpio1b_p;
	unsigned int gpio1c_p;
	unsigned int gpio1d_p;
	unsigned int reserved6[(0x0200 - 0x01cc) / 4 - 1];
	unsigned int gpio1a_sus;
	unsigned int gpio1b_sus;
	unsigned int gpio1c_sus;
	unsigned int gpio1d_sus;
	unsigned int reserved7[(0x0240 - 0x020c) / 4 - 1];
	unsigned int gpio1a_sl;
	unsigned int gpio1b_sl;
	unsigned int gpio1c_sl;
	unsigned int gpio1d_sl;
	unsigned int reserved8[(0x0280 - 0x024c) / 4 - 1];
	unsigned int gpio1a_ie_smt;
	unsigned int gpio1b_ie_smt;
	unsigned int gpio1c_ie_smt;
	unsigned int gpio1d_ie_smt;
	unsigned int reserved9[(0x02c0 - 0x028c) / 4 - 1];
	unsigned int gpio1a_od;
	unsigned int gpio1b_od;
	unsigned int gpio1c_od;
	unsigned int gpio1d_od;
	unsigned int reserved10[(0x02f4 - 0x02cc) / 4 - 1];
	unsigned int force_jtag_uart;
};
check_member(rv1106_gpio1_ioc, force_jtag_uart, 0x02f4);

struct rv1106_gpio2_ioc {
	unsigned int reserved0[(0x0020 - 0x0000) / 4];
	unsigned int gpio2a_iomux_sel_l;
	unsigned int gpio2a_iomux_sel_h;
	unsigned int gpio2b_iomux_sel_l;
	unsigned int reserved1[(0x00c0 - 0x0028) / 4 - 1];
	unsigned int gpio2a_ds0;
	unsigned int gpio2a_ds1;
	unsigned int gpio2a_ds2;
	unsigned int gpio2a_ds3;
	unsigned int gpio2b_ds0;
	unsigned int reserved2[(0x0190 - 0x00d0) / 4 - 1];
	unsigned int gpio2a_ie;
	unsigned int gpio2b_ie;
	unsigned int reserved3[(0x01d0 - 0x0194) / 4 - 1];
	unsigned int gpio2a_p;
	unsigned int gpio2b_p;
	unsigned int reserved4[(0x0210 - 0x01d4) / 4 - 1];
	unsigned int gpio2a_sus;
	unsigned int gpio2b_sus;
	unsigned int reserved5[(0x0250 - 0x0214) / 4 - 1];
	unsigned int gpio2a_sl;
	unsigned int gpio2b_sl;
	unsigned int reserved6[(0x0290 - 0x0254) / 4 - 1];
	unsigned int gpio2a_ie_smt;
	unsigned int gpio2b_ie_smt;
	unsigned int reserved7[(0x02d0 - 0x0294) / 4 - 1];
	unsigned int gpio2a_od;
	unsigned int gpio2b_od;
};
check_member(rv1106_gpio2_ioc, gpio2b_od, 0x02d4);

struct rv1106_gpio3_ioc {
	unsigned int reserved0[(0x0040 - 0x0000) / 4];
        unsigned int gpio3a_iomux_sel_l;
	unsigned int gpio3a_iomux_sel_h;
	unsigned int gpio3b_iomux_sel_l;
	unsigned int gpio3b_iomux_sel_h;
	unsigned int gpio3c_iomux_sel_l;
	unsigned int gpio3c_iomux_sel_h;
	unsigned int gpio3d_iomux_sel_l;
	unsigned int reserved1[(0x0100 - 0x0058) / 4 - 1];
	unsigned int gpio3a_ds0;
	unsigned int gpio3a_ds1;
	unsigned int gpio3a_ds2;
	unsigned int gpio3a_ds3;
	unsigned int reserved2[(0x0128 - 0x010c) / 4 - 1];
	unsigned int gpio3c_ds2;
	unsigned int gpio3c_ds3;
	unsigned int gpio3d_ds0;
	unsigned int gpio3d_ds1;
	unsigned int reserved3[(0x01a0 - 0x0134) / 4 - 1];
	unsigned int gpio3a_ie;
	unsigned int reserved4[(0x01a8 - 0x01a0) / 4 - 1];
	unsigned int gpio3c_ie;
	unsigned int gpio3d_ie;
	unsigned int reserved5[(0x01e0 - 0x01ac) / 4 - 1];
	unsigned int gpio3a_p;
	unsigned int reserved6[(0x01e8 - 0x01e0) / 4 - 1];
	unsigned int gpio3c_p;
	unsigned int gpio3d_p;
	unsigned int reserved7[(0x0220 - 0x01ec) / 4 - 1];
	unsigned int gpio3a_sus;
	unsigned int reserved8[(0x0228 - 0x0220) / 4 - 1];
	unsigned int gpio3c_sus;
	unsigned int gpio3d_sus;
	unsigned int reserved9[(0x0260 - 0x022c) / 4 - 1];
	unsigned int gpio3a_sl;
	unsigned int reserved10[(0x0268 - 0x0260) / 4 - 1];
	unsigned int gpio3c_sl;
	unsigned int gpio3d_sl;
	unsigned int reserved11[(0x02a0 - 0x026c) / 4 - 1];
	unsigned int gpio3a_ie_smt;
	unsigned int reserved12[(0x02a8 - 0x02a0) / 4 - 1];
	unsigned int gpio3c_ie_smt;
	unsigned int gpio3d_ie_smt;
	unsigned int reserved13[(0x02e0 - 0x02ac) / 4 - 1];
	unsigned int gpio3a_od;
	unsigned int reserved14[(0x02e8 - 0x02e0) / 4 - 1];
	unsigned int gpio3c_od;
	unsigned int gpio3d_od;
	unsigned int reserved15[(0x02f4 - 0x02ec) / 4 - 1];
	unsigned int force_jtag_sdmmc;
};
check_member(rv1106_gpio3_ioc, force_jtag_sdmmc, 0x02f4);

struct rv1106_gpio4_ioc {
	unsigned int gpio4a_iomux_sel_l;
	unsigned int gpio4a_iomux_sel_h;
	unsigned int gpio4b_iomux_sel_l;
	unsigned int reserved0[(0x0010 - 0x0008) / 4 - 1];
	unsigned int gpio4c_iomux_sel_l;
	unsigned int reserved1[(0x0020 - 0x0010) / 4 - 1];
	unsigned int gpio4a_ds0;
	unsigned int gpio4a_ds1;
	unsigned int gpio4a_ds2;
	unsigned int gpio4a_ds3;
	unsigned int gpio4b_ds0;
	unsigned int reserved2[(0x0060 - 0x0030) / 4 - 1];
	unsigned int gpio4a_ie;
	unsigned int gpio4b_ie;
	unsigned int reserved3[(0x0070 - 0x0064) / 4 - 1];
	unsigned int gpio4a_p;
	unsigned int gpio4b_p;
	unsigned int reserved4[(0x0080 - 0x0074) / 4 - 1];
	unsigned int gpio4a_sus;
	unsigned int gpio4b_sus;
	unsigned int reserved5[(0x0090 - 0x0084) / 4 - 1];
	unsigned int gpio4a_sl;
	unsigned int gpio4b_sl;
	unsigned int reserved6[(0x00a0 - 0x0094) / 4 - 1];
	unsigned int gpio4a_ie_smt;
	unsigned int gpio4b_ie_smt;
	unsigned int reserved7[(0x00b0 - 0x00a4) / 4 - 1];
	unsigned int gpio4a_od;
	unsigned int gpio4b_od;
	unsigned int reserved8[(0x00c0 - 0x00b4) / 4 - 1];
	unsigned int saradc_io_con;
	unsigned int reserved9[(0x0200 - 0x00c0) / 4 - 1];
	unsigned int vccio3_vol_con;
};
check_member(rv1106_gpio4_ioc, vccio3_vol_con, 0x0200);

#endif
