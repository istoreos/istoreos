/*
 * (C) Copyright 2021 Rockchip Electronics Co., Ltd.
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */
#ifndef _ASM_ARCH_GRF_RK3588_H
#define _ASM_ARCH_GRF_RK3588_H

#include <common.h>

struct rk3588_sys_grf {
	uint32_t wdt_con0;                       /* Address Offset: 0x0000 */
	uint32_t reserved0004[3];                /* Address Offset: 0x0004 */
	uint32_t uart_con0;                      /* Address Offset: 0x0010 */
	uint32_t uart_con1;                      /* Address Offset: 0x0014 */
	uint32_t reserved0018[42];               /* Address Offset: 0x0018 */
	uint32_t gic_con0;                       /* Address Offset: 0x00C0 */
	uint32_t reserved00c4[79];               /* Address Offset: 0x00C4 */
	uint32_t memcfg_con0;                    /* Address Offset: 0x0200 */
	uint32_t memcfg_con1;                    /* Address Offset: 0x0204 */
	uint32_t memcfg_con2;                    /* Address Offset: 0x0208 */
	uint32_t memcfg_con3;                    /* Address Offset: 0x020C */
	uint32_t memcfg_con4;                    /* Address Offset: 0x0210 */
	uint32_t memcfg_con5;                    /* Address Offset: 0x0214 */
	uint32_t memcfg_con6;                    /* Address Offset: 0x0218 */
	uint32_t memcfg_con7;                    /* Address Offset: 0x021C */
	uint32_t memcfg_con8;                    /* Address Offset: 0x0220 */
	uint32_t memcfg_con9;                    /* Address Offset: 0x0224 */
	uint32_t memcfg_con10;                   /* Address Offset: 0x0228 */
	uint32_t memcfg_con11;                   /* Address Offset: 0x022C */
	uint32_t memcfg_con12;                   /* Address Offset: 0x0230 */
	uint32_t memcfg_con13;                   /* Address Offset: 0x0234 */
	uint32_t memcfg_con14;                   /* Address Offset: 0x0238 */
	uint32_t memcfg_con15;                   /* Address Offset: 0x023C */
	uint32_t memcfg_con16;                   /* Address Offset: 0x0240 */
	uint32_t memcfg_con17;                   /* Address Offset: 0x0244 */
	uint32_t memcfg_con18;                   /* Address Offset: 0x0248 */
	uint32_t memcfg_con19;                   /* Address Offset: 0x024C */
	uint32_t memcfg_con20;                   /* Address Offset: 0x0250 */
	uint32_t memcfg_con21;                   /* Address Offset: 0x0254 */
	uint32_t memcfg_con22;                   /* Address Offset: 0x0258 */
	uint32_t memcfg_con23;                   /* Address Offset: 0x025C */
	uint32_t memcfg_con24;                   /* Address Offset: 0x0260 */
	uint32_t reserved0264;                   /* Address Offset: 0x0264 */
	uint32_t memcfg_con26;                   /* Address Offset: 0x0268 */
	uint32_t memcfg_con27;                   /* Address Offset: 0x026C */
	uint32_t memcfg_con28;                   /* Address Offset: 0x0270 */
	uint32_t memcfg_con29;                   /* Address Offset: 0x0274 */
	uint32_t memcfg_con30;                   /* Address Offset: 0x0278 */
	uint32_t memcfg_con31;                   /* Address Offset: 0x027C */
	uint32_t reserved0280[33];               /* Address Offset: 0x0280 */
	uint32_t soc_con1;                       /* Address Offset: 0x0304 */
	uint32_t soc_con2;                       /* Address Offset: 0x0308 */
	uint32_t soc_con3;                       /* Address Offset: 0x030C */
	uint32_t reserved0310[2];                /* Address Offset: 0x0310 */
	uint32_t soc_con6;                       /* Address Offset: 0x0318 */
	uint32_t soc_con7;                       /* Address Offset: 0x031C */
	uint32_t soc_con8;                       /* Address Offset: 0x0320 */
	uint32_t soc_con9;                       /* Address Offset: 0x0324 */
	uint32_t soc_con10;                      /* Address Offset: 0x0328 */
	uint32_t soc_con11;                      /* Address Offset: 0x032C */
	uint32_t soc_con12;                      /* Address Offset: 0x0330 */
	uint32_t soc_con13;                      /* Address Offset: 0x0334 */
	uint32_t reserved0338[18];               /* Address Offset: 0x0338 */
	uint32_t soc_status0;                    /* Address Offset: 0x0380 */
	uint32_t soc_status1;                    /* Address Offset: 0x0384 */
	uint32_t soc_status2;                    /* Address Offset: 0x0388 */
	uint32_t soc_status3;                    /* Address Offset: 0x038C */
	uint32_t reserved0390[92];               /* Address Offset: 0x0390 */
	uint32_t otp_key08;                      /* Address Offset: 0x0500 */
	uint32_t otp_key0d;                      /* Address Offset: 0x0504 */
	uint32_t otp_key0e;                      /* Address Offset: 0x0508 */
	uint32_t reserved050c[61];               /* Address Offset: 0x050C */
	uint32_t chip_id;                        /* Address Offset: 0x0600 */
};
check_member(rk3588_sys_grf, chip_id, 0x0600);

struct rk3588_php_grf {
	uint32_t php_con0;                       /* Address Offset: 0x0000 */
	uint32_t php_con1;                       /* Address Offset: 0x0004 */
	uint32_t gmac_con0;                      /* Address Offset: 0x0008 */
	uint32_t reserved000c;                   /* Address Offset: 0x000C */
	uint32_t sata_con0;                      /* Address Offset: 0x0010 */
	uint32_t sata_con1;                      /* Address Offset: 0x0014 */
	uint32_t sata_con2;                      /* Address Offset: 0x0018 */
	uint32_t php_mmu_con0;                   /* Address Offset: 0x001C */
	uint32_t php_mmu_con1;                   /* Address Offset: 0x0020 */
	uint32_t php_mmu_con2;                   /* Address Offset: 0x0024 */
	uint32_t its_taddr0;                     /* Address Offset: 0x0028 */
	uint32_t its_taddr1;                     /* Address Offset: 0x002C */
	uint32_t pcie_mmu_pciemode;              /* Address Offset: 0x0030 */
	uint32_t pcie_mmu_con0;                  /* Address Offset: 0x0034 */
	uint32_t pcie_mmu_con1;                  /* Address Offset: 0x0038 */
	uint32_t pcie_mmu_con2;                  /* Address Offset: 0x003C */
	uint32_t mem_con0;                       /* Address Offset: 0x0040 */
	uint32_t php_st0;                        /* Address Offset: 0x0044 */
	uint32_t php_st1;                        /* Address Offset: 0x0048 */
	uint32_t php_st2;                        /* Address Offset: 0x004C */
	uint32_t php_st3;                        /* Address Offset: 0x0050 */
	uint32_t php_st4;                        /* Address Offset: 0x0054 */
	uint32_t mmu_pmu_ack;                    /* Address Offset: 0x0058 */
	uint32_t pcie_mmu_con6;                  /* Address Offset: 0x005C */
	uint32_t pcie_mmu_con7;                  /* Address Offset: 0x0060 */
	uint32_t mem_con5;                       /* Address Offset: 0x0064 */
	uint32_t mem_con10;                      /* Address Offset: 0x0068 */
	uint32_t reserved006c;                   /* Address Offset: 0x006C */
	uint32_t clk_con1;                       /* Address Offset: 0x0070 */
	uint32_t gmac0_sid_aw;                   /* Address Offset: 0x0074 */
	uint32_t gmac0_ssid_aw;                  /* Address Offset: 0x0078 */
	uint32_t gmac1_sid_aw;                   /* Address Offset: 0x007C */
	uint32_t gmac1_ssid_aw;                  /* Address Offset: 0x0080 */
	uint32_t sata0_sid_aw;                   /* Address Offset: 0x0084 */
	uint32_t sata0_ssid_aw;                  /* Address Offset: 0x0088 */
	uint32_t sata1_sid_aw;                   /* Address Offset: 0x008C */
	uint32_t sata1_ssid_aw;                  /* Address Offset: 0x0090 */
	uint32_t sata2_sid_aw;                   /* Address Offset: 0x0094 */
	uint32_t sata2_ssid_aw;                  /* Address Offset: 0x0098 */
	uint32_t gmac0_sid_ar;                   /* Address Offset: 0x009C */
	uint32_t gmac0_ssid_ar;                  /* Address Offset: 0x00A0 */
	uint32_t gmac1_sid_ar;                   /* Address Offset: 0x00A4 */
	uint32_t gmac1_ssid_ar;                  /* Address Offset: 0x00A8 */
	uint32_t sata0_sid_ar;                   /* Address Offset: 0x00AC */
	uint32_t sata0_ssid_ar;                  /* Address Offset: 0x00B0 */
	uint32_t sata1_sid_ar;                   /* Address Offset: 0x00B4 */
	uint32_t sata1_ssid_ar;                  /* Address Offset: 0x00B8 */
	uint32_t sata2_sid_ar;                   /* Address Offset: 0x00BC */
	uint32_t sata2_ssid_ar;                  /* Address Offset: 0x00C0 */
	uint32_t usb3otg_2_sid_ar;               /* Address Offset: 0x00C4 */
	uint32_t usb3otg_2_ssid_ar;              /* Address Offset: 0x00C8 */
	uint32_t usb3otg_2_sid_aw;               /* Address Offset: 0x00CC */
	uint32_t usb3otg_2_ssid_aw;              /* Address Offset: 0x00D0 */
	uint32_t gmac_con_pst;                   /* Address Offset: 0x00D4 */
	uint32_t gmac0_cmd;                      /* Address Offset: 0x00D8 */
	uint32_t gmac1_cmd;                      /* Address Offset: 0x00DC */
	uint32_t mem_con11;                      /* Address Offset: 0x00E0 */
	uint32_t usb3otg_2_con0;                 /* Address Offset: 0x00E4 */
	uint32_t usb3otg_2_con1;                 /* Address Offset: 0x00E8 */
	uint32_t usb3otg_2_intcon;               /* Address Offset: 0x00EC */
	uint32_t usb3otg_2_st_lat0;              /* Address Offset: 0x00F0 */
	uint32_t usb3otg_2_st_lat1;              /* Address Offset: 0x00F4 */
	uint32_t usb3otg_2_st_cb;                /* Address Offset: 0x00F8 */
	uint32_t usb3otg_2_st;                   /* Address Offset: 0x00FC */
	uint32_t pciesel_con;                    /* Address Offset: 0x0100 */
	uint32_t utmi_con;                       /* Address Offset: 0x0104 */
	uint32_t reserved0108;                   /* Address Offset: 0x0108 */
	uint32_t pcie4l_sid_aw;                  /* Address Offset: 0x010C */
	uint32_t pcie4l_sid_ar;                  /* Address Offset: 0x0110 */
	uint32_t pcie2l_sid_aw;                  /* Address Offset: 0x0114 */
	uint32_t pcie2l_sid_ar;                  /* Address Offset: 0x0118 */
	uint32_t pcie1l0_sid_aw;                 /* Address Offset: 0x011C */
	uint32_t pcie1l0_sid_ar;                 /* Address Offset: 0x0120 */
	uint32_t pcie1l1_sid_aw;                 /* Address Offset: 0x0124 */
	uint32_t pcie1l1_sid_ar;                 /* Address Offset: 0x0128 */
	uint32_t pcie1l2_sid_aw;                 /* Address Offset: 0x012C */
	uint32_t pcie1l2_sid_ar;                 /* Address Offset: 0x0130 */
	uint32_t reserved0134;                   /* Address Offset: 0x0134 */
	uint32_t pcie_ats;                       /* Address Offset: 0x0138 */
	uint32_t st_utmi;                        /* Address Offset: 0x013C */
	uint32_t reserved0140;                   /* Address Offset: 0x0140 */
	uint32_t pcie4l_ssid_aw;                 /* Address Offset: 0x0144 */
	uint32_t pcie4l_ssid_ar;                 /* Address Offset: 0x0148 */
	uint32_t pcie2l_ssid_aw;                 /* Address Offset: 0x014C */
	uint32_t pcie2l_ssid_ar;                 /* Address Offset: 0x0150 */
	uint32_t pcie1l0_ssid_aw;                /* Address Offset: 0x0154 */
	uint32_t pcie1l0_ssid_ar;                /* Address Offset: 0x0158 */
	uint32_t pcie1l1_ssid_aw;                /* Address Offset: 0x015C */
	uint32_t pcie1l1_ssid_ar;                /* Address Offset: 0x0160 */
	uint32_t pcie1l2_ssid_aw;                /* Address Offset: 0x0164 */
	uint32_t pcie1l2_ssid_ar;                /* Address Offset: 0x0168 */
	uint32_t pcie_ssid_v;                    /* Address Offset: 0x016C */
	uint32_t reserved0170;                   /* Address Offset: 0x0170 */
	uint32_t sata_pd_sel;                    /* Address Offset: 0x0174 */
	uint32_t pcie_mmu_irq_clr;               /* Address Offset: 0x0178 */
	uint32_t php_mmu_irq_clr;                /* Address Offset: 0x017C */
	uint32_t pcie_mmu_st;                    /* Address Offset: 0x0180 */
	uint32_t php_mmu_st;                     /* Address Offset: 0x0184 */
	uint32_t reserved0188;                   /* Address Offset: 0x0188 */
	uint32_t php_st0b;                       /* Address Offset: 0x018C */
};
check_member(rk3588_php_grf, php_st0b, 0x018c);

#endif
