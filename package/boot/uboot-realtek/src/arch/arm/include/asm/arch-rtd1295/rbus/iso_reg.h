/**************************************************************
// Spec Version                  : 0.1.4
// Parser Version                : DVR_Parser_6.11(120105)
// CModelGen Version             : 5.1 2012.01.05
// Naming Rule                   :  Module_Register_Name
// Naming Rule                   : Module_Register_Name
// Parse Option                  : Only Parse _op1
// Parse Address Region          : All Address Region 
// Decode bit number             : 12 bits
// Firmware Header Generate Date : 2015/7/3 10:28:8
***************************************************************/


#ifndef _ISO_REG_H_INCLUDED_
#define _ISO_REG_H_INCLUDED_
#ifdef  _ISO_USE_STRUCT
typedef struct 
{
unsigned int     i2c1_req_int:1;
unsigned int     porb_av_cen_int:1;
unsigned int     porb_dv_cen_int:1;
unsigned int     reserved_0:4;
unsigned int     usb_int:1;
unsigned int     etn_int:1;
unsigned int     cbus_int:1;
unsigned int     iso_misc_int:1;
unsigned int     gpioda_int:1;
unsigned int     gpioa_int:1;
unsigned int     reserved_1:5;
unsigned int     rtc_alarm_int:1;
unsigned int     rtc_hsec_int:1;
unsigned int     i2c1_int:1;
unsigned int     reserved_2:1;
unsigned int     tc4_int:1;
unsigned int     i2c0_int:1;
unsigned int     wdog_nmi_int:1;
unsigned int     reserved_3:1;
unsigned int     irda_int:1;
unsigned int     reserved_4:2;
unsigned int     ur0_int:1;
unsigned int     tc3_int:1;
unsigned int     write_data:1;
}ISO_ISR;

typedef struct 
{
unsigned int     i2c1_req_int:1;
unsigned int     porb_av_cen_int:1;
unsigned int     porb_dv_cen_int:1;
unsigned int     reserved_0:8;
unsigned int     gpioda_int:1;
unsigned int     gpioa_int:1;
unsigned int     reserved_1:5;
unsigned int     rtc_alarm_int:1;
unsigned int     rtc_hsec_int:1;
unsigned int     reserved_2:2;
unsigned int     tc4_int:1;
unsigned int     reserved_3:1;
unsigned int     wdog_nmi_int:1;
unsigned int     reserved_4:1;
unsigned int     irda_int:1;
unsigned int     reserved_5:3;
unsigned int     tc3_int:1;
unsigned int     write_data:1;
}ISO_UMSK_ISR;

typedef struct 
{
unsigned int     int30_a:1;
unsigned int     int29_a:1;
unsigned int     int28_a:1;
unsigned int     int27_a:1;
unsigned int     int26_a:1;
unsigned int     int25_a:1;
unsigned int     int24_a:1;
unsigned int     int23_a:1;
unsigned int     int22_a:1;
unsigned int     int21_a:1;
unsigned int     int20_a:1;
unsigned int     int19_a:1;
unsigned int     int18_a:1;
unsigned int     int17_a:1;
unsigned int     int16_a:1;
unsigned int     int15_a:1;
unsigned int     int14_a:1;
unsigned int     int13_a:1;
unsigned int     int12_a:1;
unsigned int     int11_a:1;
unsigned int     int10_a:1;
unsigned int     int9_a:1;
unsigned int     int8_a:1;
unsigned int     int7_a:1;
unsigned int     int6_a:1;
unsigned int     int5_a:1;
unsigned int     int4_a:1;
unsigned int     int3_a:1;
unsigned int     int2_a:1;
unsigned int     int1_a:1;
unsigned int     int0_a:1;
unsigned int     write_data:1;
}ISO_UMSK_ISR_GPA0;

typedef struct 
{
unsigned int     int30_da:1;
unsigned int     int29_da:1;
unsigned int     int28_da:1;
unsigned int     int27_da:1;
unsigned int     int26_da:1;
unsigned int     int25_da:1;
unsigned int     int24_da:1;
unsigned int     int23_da:1;
unsigned int     int22_da:1;
unsigned int     int21_da:1;
unsigned int     int20_da:1;
unsigned int     int19_da:1;
unsigned int     int18_da:1;
unsigned int     int17_da:1;
unsigned int     int16_da:1;
unsigned int     int15_da:1;
unsigned int     int14_da:1;
unsigned int     int13_da:1;
unsigned int     int12_da:1;
unsigned int     int11_da:1;
unsigned int     int10_da:1;
unsigned int     int9_da:1;
unsigned int     int8_da:1;
unsigned int     int7_da:1;
unsigned int     int6_da:1;
unsigned int     int5_da:1;
unsigned int     int4_da:1;
unsigned int     int3_da:1;
unsigned int     int2_da:1;
unsigned int     int1_da:1;
unsigned int     int0_da:1;
unsigned int     write_data:1;
}ISO_UMSK_ISR_GPDA0;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     int34_a:1;
unsigned int     int33_a:1;
unsigned int     int32_a:1;
unsigned int     int31_a:1;
unsigned int     write_data:1;
}ISO_UMSK_ISR_GPA1;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     int34_da:1;
unsigned int     int33_da:1;
unsigned int     int32_da:1;
unsigned int     int31_da:1;
unsigned int     write_data:1;
}ISO_UMSK_ISR_GPDA1;

typedef struct 
{
unsigned int     gp_int:31;
unsigned int     reserved_0:1;
}ISO_FAST_INT_EN_0;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     gp_int:4;
unsigned int     reserved_1:1;
}ISO_FAST_INT_EN_1;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     gpioda_int:1;
unsigned int     gpioa_int:1;
unsigned int     write_data:1;
}ISO_FAST_ISR;

typedef struct 
{
unsigned int     dmy:32;
}ISO_RESERVED_USE_3;

typedef struct 
{
unsigned int     reserved_0:20;
unsigned int     write_en2:1;
unsigned int     reserved_1:2;
unsigned int     sel:5;
unsigned int     write_en1:1;
unsigned int     reserved_2:2;
unsigned int     enable:1;
}ISO_REG_DBG;

typedef struct 
{
unsigned int     write_en5:1;
unsigned int     standby_dbg_sel:7;
unsigned int     write_en4:1;
unsigned int     reserved_0:2;
unsigned int     standby_dbg_en:1;
unsigned int     write_en3:1;
unsigned int     reserved_1:3;
unsigned int     sel1:4;
unsigned int     write_en2:1;
unsigned int     reserved_2:3;
unsigned int     sel0:4;
unsigned int     write_en1:1;
unsigned int     reserved_3:2;
unsigned int     enable:1;
}ISO_DBG;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     testmode:1;
unsigned int     boot_sel:1;
unsigned int     bound_opt:14;
}ISO_CHIP_INFO1;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     pow_latch:26;
}ISO_CHIP_INFO2;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     pow_latch_ori:26;
}ISO_CHIP_INFO3;

typedef struct 
{
unsigned int     reserved_0:14;
unsigned int     write_en9:1;
unsigned int     iso_rst_wd_mask:1;
unsigned int     write_en8:1;
unsigned int     dc_phy_cke_pd:1;
unsigned int     write_en7:1;
unsigned int     iso_mis_clk_en:1;
unsigned int     write_en6:1;
unsigned int     iso_rbus_sel:1;
unsigned int     write_en5:1;
unsigned int     iso_rst_mask:1;
unsigned int     write_en4:1;
unsigned int     clk_osc_on_en:1;
unsigned int     write_en3:1;
unsigned int     crt_sw_rstn:1;
unsigned int     write_en2:1;
unsigned int     iso_clk_sel:1;
unsigned int     write_en1:1;
unsigned int     ejtag_en:1;
}ISO_CTRL;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     hsec_sync:1;
unsigned int     hsec_int_en:1;
unsigned int     alarm_int_en:1;
}ISO_RTC;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     bi_bypass:1;
unsigned int     iso_ctrl_en1:1;
unsigned int     iso_ctrl_en0:1;
}ISO_CELL;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     top_vdd_on:1;
unsigned int     scpu_vdd_on:1;
}ISO_POWER;

typedef struct 
{
unsigned int     i2c1_req:1;
unsigned int     porb_av_cen:1;
unsigned int     porb_dv_cen:1;
unsigned int     reserved_0:6;
unsigned int     reserved_1:1;
unsigned int     reserved_2:1;
unsigned int     gpioda:1;
unsigned int     gpioa:1;
unsigned int     reserved_3:5;
unsigned int     rtc_alarm:1;
unsigned int     rtc_hsec:1;
unsigned int     i2c1:1;
unsigned int     reserved_4:1;
unsigned int     reserved_5:1;
unsigned int     i2c0:1;
unsigned int     reserved_6:2;
unsigned int     irda:1;
unsigned int     reserved_7:2;
unsigned int     ur0:1;
unsigned int     reserved_8:2;
}ISO_SCPU_INT_EN;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     dcp_ctrl3:1;
unsigned int     dcp_ctrl2:1;
unsigned int     dcp_ctrl1:1;
unsigned int     dcp_ctrl0:1;
}ISO_USB;

typedef struct 
{
unsigned int     i2c1_req:1;
unsigned int     reserved_0:8;
unsigned int     reserved_1:1;
unsigned int     reserved_2:1;
unsigned int     gpioda:1;
unsigned int     gpioa:1;
unsigned int     reserved_3:5;
unsigned int     rtc_alarm:1;
unsigned int     rtc_hsec:1;
unsigned int     i2c1:1;
unsigned int     reserved_4:1;
unsigned int     reserved_5:1;
unsigned int     i2c0:1;
unsigned int     reserved_6:2;
unsigned int     irda:1;
unsigned int     reserved_7:2;
unsigned int     ur0:1;
unsigned int     reserved_8:2;
}ISO_ACPU_INT_EN;

typedef struct 
{
unsigned int     acpu_boot_info:32;
}ISO_CPU_ST1;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     acpu_boot_info_valid:1;
}ISO_CPU_ST1V;

typedef struct 
{
unsigned int     rvd31:1;
unsigned int     rvd30:1;
unsigned int     rvd29:1;
unsigned int     rvd28:1;
unsigned int     rvd27:1;
unsigned int     rvd26:1;
unsigned int     rvd25:1;
unsigned int     rvd24:1;
unsigned int     rvd23:1;
unsigned int     rvd22:1;
unsigned int     rvd21:1;
unsigned int     rvd20:1;
unsigned int     rvd19:1;
unsigned int     rvd18:1;
unsigned int     rvd17:1;
unsigned int     rvd16:1;
unsigned int     rvd15:1;
unsigned int     rvd14:1;
unsigned int     rvd13:1;
unsigned int     rvd12:1;
unsigned int     rvd11:1;
unsigned int     rvd10:1;
unsigned int     rvd9:1;
unsigned int     rvd8:1;
unsigned int     rvd7:1;
unsigned int     rvd6:1;
unsigned int     rvd5:1;
unsigned int     rvd4:1;
unsigned int     rvd3:1;
unsigned int     rvd2:1;
unsigned int     rvd1:1;
unsigned int     rvd0:1;
}ISO_DUMMY1;

typedef struct 
{
unsigned int     rvd31:1;
unsigned int     rvd30:1;
unsigned int     rvd29:1;
unsigned int     rvd28:1;
unsigned int     rvd27:1;
unsigned int     rvd26:1;
unsigned int     rvd25:1;
unsigned int     rvd24:1;
unsigned int     rvd23:1;
unsigned int     rvd22:1;
unsigned int     rvd21:1;
unsigned int     rvd20:1;
unsigned int     rvd19:1;
unsigned int     rvd18:1;
unsigned int     rvd17:1;
unsigned int     rvd16:1;
unsigned int     rvd15:1;
unsigned int     rvd14:1;
unsigned int     rvd13:1;
unsigned int     rvd12:1;
unsigned int     rvd11:1;
unsigned int     rvd10:1;
unsigned int     rvd9:1;
unsigned int     rvd8:1;
unsigned int     rvd7:1;
unsigned int     rvd6:1;
unsigned int     rvd5:1;
unsigned int     rvd4:1;
unsigned int     rvd3:1;
unsigned int     rvd2:1;
unsigned int     rvd1:1;
unsigned int     rvd0:1;
}ISO_DUMMY2;

typedef struct 
{
unsigned int     reserved_0:20;
unsigned int     sel_xtal25m_cen_l:1;
unsigned int     en_pll_27m_tiehalf_cen:1;
unsigned int     pow_ldo_27m_pll_cen:1;
unsigned int     pow_pll_27m_en_cen:1;
unsigned int     reserved_1:2;
unsigned int     gphy_mdio_outside_ctrl_en:1;
unsigned int     etn_gphy_switch_nat:1;
unsigned int     reserved_2:1;
unsigned int     etn_efuse_default:1;
unsigned int     powercut_ana_d2a_isolate_b:1;
unsigned int     powercut_ana_a2d_isolate_b:1;
}ISO_POWERCUT_ETN;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     etn_bpsgphy_mode:1;
unsigned int     etn_ocd_mode:1;
}ISO_ETN_TESTIO;

typedef struct 
{
unsigned int     dmy:32;
}ISO_RESERVED_USE_0;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     timer:1;
unsigned int     reserved_1:1;
unsigned int     ir_main:1;
unsigned int     ir_tx:1;
unsigned int     ir_raw:1;
}ISO_LPI;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     cnt_wait_pwr:16;
}ISO_WD;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     plletn_wdout:1;
}ISO_PLL_WDOUT;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     plletn_oeb:1;
unsigned int     plletn_rstb:1;
unsigned int     plletn_o:4;
unsigned int     plletn_m:7;
unsigned int     plletn_ldo_pow:1;
unsigned int     plletn_pow:1;
unsigned int     plletn_ldo_sel:2;
unsigned int     plletn_wdmode:2;
unsigned int     plletn_n:2;
unsigned int     plletn_lf_rs:2;
unsigned int     plletn_lf_cp:2;
unsigned int     plletn_ip:3;
}ISO_PLL_ETN;

typedef struct 
{
unsigned int     dmy:32;
}ISO_RESERVED_USE_1;

typedef struct 
{
unsigned int     dmy:32;
}ISO_RESERVED_USE_2;

typedef struct 
{
unsigned int     dmy1:20;
unsigned int     reserved_0:3;
unsigned int     en:1;
unsigned int     reserved_1:3;
unsigned int     sel:5;
}ISO_I2C1_SDA_DEL;

typedef struct 
{
unsigned int     dmy1:20;
unsigned int     reserved_0:3;
unsigned int     en:1;
unsigned int     reserved_1:3;
unsigned int     sel:5;
}ISO_I2C0_SDA_DEL;

typedef struct 
{
unsigned int     reserved_0:18;
unsigned int     rstn_cbus:1;
unsigned int     rstn_i2c_1:1;
unsigned int     rstn_i2c_0:1;
unsigned int     rstn_gphy:1;
unsigned int     rstn_gmac:1;
unsigned int     rstn_ur0:1;
unsigned int     rstn_efuse:1;
unsigned int     rstn_cbusrx:1;
unsigned int     rstn_cbustx:1;
unsigned int     rstn_dp:1;
unsigned int     rstn_cec1:1;
unsigned int     rstn_cec0:1;
unsigned int     rstn_ir:1;
unsigned int     reserved_1:1;
}ISO_SOFT_RESET;

typedef struct 
{
unsigned int     reserved_0:19;
unsigned int     clk_en_etn_sys:1;
unsigned int     clk_en_etn_250m:1;
unsigned int     clk_en_i2c1:1;
unsigned int     clk_en_i2c0:1;
unsigned int     clk_en_misc_ur0:1;
unsigned int     clk_en_misc_ir:1;
unsigned int     clk_en_cbus_osc:1;
unsigned int     clk_en_cbus_sys:1;
unsigned int     clk_en_cbustx_sys:1;
unsigned int     clk_en_cbusrx_sys:1;
unsigned int     clk_en_misc_cec0:1;
unsigned int     reserved_1:1;
unsigned int     clk_en_misc_mix:1;
}ISO_CLOCK_ENABLE;

typedef struct 
{
unsigned int     reserved_0:7;
unsigned int     rd_only_0_en:1;
unsigned int     reserved_1:2;
unsigned int     blk_protect_0_wpro_en:1;
unsigned int     reserved_2:2;
unsigned int     blk_protect_0_en:1;
unsigned int     reserved_3:8;
unsigned int     protect_0_wpro_en:1;
unsigned int     reserved_4:8;
unsigned int     protect_0_en:1;
}ISO_DC_0;

typedef struct 
{
unsigned int     mem_saddr0:22;
unsigned int     reserved_0:10;
}ISO_DC_1;

typedef struct 
{
unsigned int     mem_eaddr0:22;
unsigned int     reserved_0:10;
}ISO_DC_2;

typedef struct 
{
unsigned int     blk_saddr0:22;
unsigned int     reserved_0:10;
}ISO_DC_3;

typedef struct 
{
unsigned int     blk_eaddr0:22;
unsigned int     reserved_0:10;
}ISO_DC_4;

typedef struct 
{
unsigned int     ro_saddr0:22;
unsigned int     reserved_0:10;
}ISO_DC_5;

typedef struct 
{
unsigned int     ro_eaddr0:22;
unsigned int     reserved_0:10;
}ISO_DC_6;

typedef struct 
{
unsigned int     reserved_0:7;
unsigned int     md_tee_protect_en:1;
unsigned int     reserved_1:7;
unsigned int     cp_tee_protect_en:1;
unsigned int     reserved_2:7;
unsigned int     vo_protect_en:1;
unsigned int     reserved_3:5;
unsigned int     tp_tee_protect_en:1;
unsigned int     cr_tee_protect_en:1;
unsigned int     nf_tee_protect_en:1;
}ISO_DC_7;

typedef struct 
{
unsigned int     reserved_0:7;
unsigned int     scpu_tee_protect_en:1;
unsigned int     reserved_1:7;
unsigned int     acpu_protect_en:1;
unsigned int     reserved_2:7;
unsigned int     video_protect_en:1;
unsigned int     reserved_3:7;
unsigned int     audio_protect_en:1;
}ISO_DC_8;

typedef struct 
{
unsigned int     reserved_0:17;
unsigned int     scpu_tee_blk_protect_en:1;
unsigned int     reserved_1:1;
unsigned int     acpu_blk_protect_en:1;
unsigned int     reserved_2:1;
unsigned int     video_blk_protect_en:1;
unsigned int     reserved_3:1;
unsigned int     audio_blk_protect_en:1;
unsigned int     reserved_4:1;
unsigned int     md_tee_blk_protect_en:1;
unsigned int     reserved_5:1;
unsigned int     cp_tee_blk_protect_en:1;
unsigned int     tp_tee_blk_protect_en:1;
unsigned int     vo_blk_protect_en:1;
unsigned int     cr_tee_blk_protect_en:1;
unsigned int     nf_tee_blk_protect_en:1;
}ISO_DC_9;

typedef struct 
{
unsigned int     reserved_0:3;
unsigned int     scpu_tee_ro_protect_en:1;
unsigned int     reserved_1:3;
unsigned int     acpu_ro_protect_en:1;
unsigned int     reserved_2:3;
unsigned int     video_ro_protect_en:1;
unsigned int     reserved_3:3;
unsigned int     audio_ro_protect_en:1;
unsigned int     reserved_4:3;
unsigned int     md_tee_ro_protect_en:1;
unsigned int     reserved_5:3;
unsigned int     cp_tee_ro_protect_en:1;
unsigned int     reserved_6:3;
unsigned int     vo_ro_protect_en:1;
unsigned int     reserved_7:1;
unsigned int     tp_tee_ro_protect_en:1;
unsigned int     cr_tee_ro_protect_en:1;
unsigned int     nf_tee_ro_protect_en:1;
}ISO_DC_A;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     xtal_pad_drv:2;
}ISO_PLL_XTAL_CTRL;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     int_option:1;
}ISO_HDMI_RX;

typedef struct 
{
unsigned int     reserved_0:18;
unsigned int     reg_reserve:2;
unsigned int     reg_tc_emb:3;
unsigned int     reg_fref_sel:1;
unsigned int     s_emb:7;
unsigned int     rstb_emb:1;
}ISO_PLL_ETN_OSC;

typedef struct 
{
unsigned int     int_30:1;
unsigned int     int_29:1;
unsigned int     int_28:1;
unsigned int     int_27:1;
unsigned int     int_26:1;
unsigned int     int_25:1;
unsigned int     int_24:1;
unsigned int     int_23:1;
unsigned int     int_22:1;
unsigned int     int_21:1;
unsigned int     int_20:1;
unsigned int     int_19:1;
unsigned int     int_18:1;
unsigned int     int_17:1;
unsigned int     int_16:1;
unsigned int     int_15:1;
unsigned int     int_14:1;
unsigned int     int_13:1;
unsigned int     int_12:1;
unsigned int     int_11:1;
unsigned int     int_10:1;
unsigned int     int_9:1;
unsigned int     int_8:1;
unsigned int     int_7:1;
unsigned int     int_6:1;
unsigned int     int_5:1;
unsigned int     int_4:1;
unsigned int     int_3:1;
unsigned int     int_2:1;
unsigned int     int_1:1;
unsigned int     int_0:1;
unsigned int     write_data:1;
}ISO_FAST_ISR_GPIO0_A;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     int_34:1;
unsigned int     int_33:1;
unsigned int     int_32:1;
unsigned int     int_31:1;
unsigned int     write_data:1;
}ISO_FAST_ISR_GPIO1_A;

typedef struct 
{
unsigned int     int_30:1;
unsigned int     int_29:1;
unsigned int     int_28:1;
unsigned int     int_27:1;
unsigned int     int_26:1;
unsigned int     int_25:1;
unsigned int     int_24:1;
unsigned int     int_23:1;
unsigned int     int_22:1;
unsigned int     int_21:1;
unsigned int     int_20:1;
unsigned int     int_19:1;
unsigned int     int_18:1;
unsigned int     int_17:1;
unsigned int     int_16:1;
unsigned int     int_15:1;
unsigned int     int_14:1;
unsigned int     int_13:1;
unsigned int     int_12:1;
unsigned int     int_11:1;
unsigned int     int_10:1;
unsigned int     int_9:1;
unsigned int     int_8:1;
unsigned int     int_7:1;
unsigned int     int_6:1;
unsigned int     int_5:1;
unsigned int     int_4:1;
unsigned int     int_3:1;
unsigned int     int_2:1;
unsigned int     int_1:1;
unsigned int     int_0:1;
unsigned int     write_data:1;
}ISO_FAST_ISR_GPIO0_DA;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     int_34:1;
unsigned int     int_33:1;
unsigned int     int_32:1;
unsigned int     int_31:1;
unsigned int     write_data:1;
}ISO_FAST_ISR_GPIO1_DA;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     int_en:1;
unsigned int     en:1;
}ISO_I2C1_REQ_CTRL;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     val:16;
}ISO_I2C1_REQ_START;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     val:16;
}ISO_I2C1_REQ_SCL_LCNT;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     val:16;
}ISO_I2C1_REQ_STOP;

typedef struct 
{
unsigned int     reserved_0:26;
unsigned int     dv_cen_int_en:1;
unsigned int     dv_cen_ha:1;
unsigned int     reserved_1:2;
unsigned int     av_cen_int_en:1;
unsigned int     av_cen_ha:1;
}ISO_POR_CTRL;

typedef struct 
{
unsigned int     reserved_0:7;
unsigned int     reg_iso_por:1;
unsigned int     reserved_1:2;
unsigned int     reg_gpu_por:2;
unsigned int     reserved_2:2;
unsigned int     reg_scpu_mem_por:2;
unsigned int     reserved_3:2;
unsigned int     reg_scpu_por:2;
unsigned int     reserved_4:2;
unsigned int     reg_dvth_por:2;
unsigned int     reserved_5:2;
unsigned int     reg_avth_por:2;
unsigned int     reserved_6:2;
unsigned int     reg_d10_por:2;
}ISO_POR_VTH;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     porb_dv_cen_l:1;
unsigned int     reserved_1:3;
unsigned int     porb_av_cen_l:1;
}ISO_POR_DATAI;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     write_en2:1;
unsigned int     dv_cen:3;
unsigned int     write_en1:1;
unsigned int     av_cen:3;
}ISO_POR_DEB;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     ve_fo_block_nwc:1;
unsigned int     tp_block_nwc:1;
unsigned int     usb2sram_ctrl:1;
unsigned int     ve_encode_block_nwc:1;
unsigned int     ve_block_nwc:1;
unsigned int     vo_block_nwc:1;
unsigned int     dc_mem_port_lock:1;
unsigned int     secure_rbus:1;
}ISO_SB2_0;

typedef struct 
{
unsigned int     reserved_0:17;
unsigned int     reg_emb_i_sel:1;
unsigned int     reg_emb_cap_sel:2;
unsigned int     reg_bg_rbgloop2:3;
unsigned int     reg_bg_rbg:3;
unsigned int     reg_bg_rbg2:2;
unsigned int     reg_bg_envbgup:1;
unsigned int     reg_ck_dummy:1;
unsigned int     reg_bg_dummy:1;
unsigned int     reg_en_emb:1;
}ISO_MBIAS;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     reg_por15n_1:1;
unsigned int     reg_por15n_0:1;
unsigned int     reg_pwdpad15n_1:1;
unsigned int     reg_pwdpad15n_0:1;
}ISO_DDR_IO_CTRL;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     reg_pwdpad3_disp:1;
}ISO_DISP_IO_CTRL;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     iso_sb3_req_mask_reg:1;
}ISO_SB3_CTRL;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     tmux_dbg_sel:7;
}ISO_ISO_TMUX_DBG;

typedef struct 
{
unsigned int     dummy:32;
}ISO_ISO_MODE_REG;

typedef struct 
{
unsigned int     l2h_delay_cycle:32;
}ISO_USB0_SRAM_PWR0;

typedef struct 
{
unsigned int     h2l_delay_cycle:32;
}ISO_USB0_SRAM_PWR1;

typedef struct 
{
unsigned int     sd_reg:32;
}ISO_USB0_SRAM_PWR2;

typedef struct 
{
unsigned int     mux_reg:32;
}ISO_USB0_SRAM_PWR3;

typedef struct 
{
unsigned int     ctrl:32;
}ISO_USB0_SRAM_PWR4;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     ve3_sram_int_mask:1;
unsigned int     reserved_1:1;
unsigned int     ve3_sram_int:1;
unsigned int     reserved_2:1;
unsigned int     write_data:1;
}ISO_USB0_SRAM_PWR5;

typedef struct 
{
unsigned int     last_delay_cycle:32;
}ISO_USB0_SRAM_PWR6;

typedef struct 
{
unsigned int     pg_switch_info:32;
}ISO_USB0_SRAM_PWR7;

typedef struct 
{
unsigned int     l2h_delay_cycle:32;
}ISO_USB1_SRAM_PWR0;

typedef struct 
{
unsigned int     h2l_delay_cycle:32;
}ISO_USB1_SRAM_PWR1;

typedef struct 
{
unsigned int     sd_reg:32;
}ISO_USB1_SRAM_PWR2;

typedef struct 
{
unsigned int     mux_reg:32;
}ISO_USB1_SRAM_PWR3;

typedef struct 
{
unsigned int     ctrl:32;
}ISO_USB1_SRAM_PWR4;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     ve3_sram_int_mask:1;
unsigned int     reserved_1:1;
unsigned int     ve3_sram_int:1;
unsigned int     reserved_2:1;
unsigned int     write_data:1;
}ISO_USB1_SRAM_PWR5;

typedef struct 
{
unsigned int     last_delay_cycle:32;
}ISO_USB1_SRAM_PWR6;

typedef struct 
{
unsigned int     pg_switch_info:32;
}ISO_USB1_SRAM_PWR7;

typedef struct 
{
unsigned int     iso_usb_u2phy_hst_dcp_en_3:1;
unsigned int     iso_usb_u2phy_hst_dcp_en_2:1;
unsigned int     iso_usb_u2phy_hst_dcp_en_1:1;
unsigned int     iso_usb_u2phy_hst_dcp_en_0:1;
unsigned int     iso_usb_u2phy_lf_pd_r_en_3:1;
unsigned int     iso_usb_u2phy_lf_pd_r_en_2:1;
unsigned int     iso_usb_u2phy_lf_pd_r_en_1:1;
unsigned int     iso_usb_u2phy_lf_pd_r_en_0:1;
unsigned int     iso_usb_u2phy_reg_ldo_pw_3:1;
unsigned int     iso_usb_u2phy_reg_ldo_pw_2:1;
unsigned int     iso_usb_u2phy_reg_ldo_pw_1:1;
unsigned int     iso_usb_u2phy_reg_ldo_pw_0:1;
unsigned int     iso_usb_u2phy_by_paa_on_3:1;
unsigned int     iso_usb_u2phy_by_paa_on_2:1;
unsigned int     iso_usb_u2phy_by_paa_on_1:1;
unsigned int     iso_usb_u2phy_by_paa_on_0:1;
unsigned int     reserved_0:6;
unsigned int     iso_usb_p3_isoctrl_en:1;
unsigned int     iso_usb_p012_isoctrl_en:1;
unsigned int     reserved_1:1;
unsigned int     iso_usb_u2phy_pg_en:1;
unsigned int     iso_usb_u3phy_p1_pg_en:1;
unsigned int     iso_usb_u3phy_p0_pg_en:1;
unsigned int     reserved_2:2;
unsigned int     iso_usb_p3_pg_en:1;
unsigned int     iso_usb_p012_pg_en:1;
}ISO_USB_CTRL;

typedef struct 
{
unsigned int     reserved_0:26;
unsigned int     so_etn_sram_ls_gap:2;
unsigned int     so_etn_clk_en_gap:2;
unsigned int     so_etn_pwr_ctrl_sw_rst:1;
unsigned int     iso_etn_pwr_ctrl_en:1;
}ISO_ETN_DBUS_CTRL;

typedef struct 
{
unsigned int     iso_etn_drom_golden:32;
}ISO_ETN_BIST_DROM_GOLDEN;

typedef struct 
{
unsigned int     iso_etn_irom_golden:32;
}ISO_ETN_BIST_IROM_GOLDEN;

typedef struct 
{
unsigned int     iso_etn_ftr_rom_golden:32;
}ISO_ETN_BIST_FTR_ROM_GOLDEN;

typedef struct 
{
unsigned int     reserved_0:10;
unsigned int     osc_count_limit:12;
unsigned int     reserved_1:7;
unsigned int     xtal_off:1;
unsigned int     dco_sel:1;
unsigned int     cal_enable:1;
}ISO_DCO_0;

typedef struct 
{
unsigned int     reserved_0:7;
unsigned int     dco_count_latch:12;
unsigned int     xtal_count_latch:12;
unsigned int     dco_cal_done:1;
}ISO_DCO_1;

typedef struct 
{
unsigned int     gpdir:32;
}ISO_GPDIR;

typedef struct 
{
unsigned int     gpdato:32;
}ISO_GPDATO;

typedef struct 
{
unsigned int     gpdati:32;
}ISO_GPDATI;

typedef struct 
{
unsigned int     gp:32;
}ISO_GPIE;

typedef struct 
{
unsigned int     gpha:32;
}ISO_GPDP;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     write_en1:1;
unsigned int     clk1:3;
}ISO_GPDEB;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     gpdir_1:3;
}ISO_GPDIR_1;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     gpdato_1:3;
}ISO_GPDATO_1;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     gpdati_1:3;
}ISO_GPDATI_1;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     gp_1:3;
}ISO_GPIE_1;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     gpha_1:3;
}ISO_GPDP_1;

typedef struct 
{
unsigned int     i2c_scl_0_smt:1;
unsigned int     i2c_scl_0_e2:1;
unsigned int     i2c_scl_0_pud_en:1;
unsigned int     i2c_scl_0_pud_sel:1;
unsigned int     i2c_sda_0_smt:1;
unsigned int     i2c_sda_0_e2:1;
unsigned int     i2c_sda_0_pud_en:1;
unsigned int     i2c_sda_0_pud_sel:1;
unsigned int     iso_gpio_7_smt:1;
unsigned int     iso_gpio_7_e2:1;
unsigned int     iso_gpio_7_pud_en:1;
unsigned int     iso_gpio_7_pud_sel:1;
unsigned int     iso_gpio_5_smt:1;
unsigned int     iso_gpio_5_e2:1;
unsigned int     iso_gpio_5_pud_en:1;
unsigned int     iso_gpio_5_pud_sel:1;
unsigned int     iso_gpio_4_smt:1;
unsigned int     iso_gpio_4_e2:1;
unsigned int     iso_gpio_4_pud_en:1;
unsigned int     iso_gpio_4_pud_sel:1;
unsigned int     ir_rx_smt:1;
unsigned int     ir_rx_e2:1;
unsigned int     ir_rx_pud_en:1;
unsigned int     ir_rx_pud_sel:1;
unsigned int     iso_gpio_3_smt:1;
unsigned int     iso_gpio_3_e2:1;
unsigned int     iso_gpio_3_pud_en:1;
unsigned int     iso_gpio_3_pud_sel:1;
unsigned int     iso_gpio_2_smt:1;
unsigned int     iso_gpio_2_e2:1;
unsigned int     iso_gpio_2_pud_en:1;
unsigned int     iso_gpio_2_pud_sel:1;
}ISO_PFUNC0;

typedef struct 
{
unsigned int     etn_led_rxtx_smt:1;
unsigned int     etn_led_rxtx_e2:1;
unsigned int     etn_led_rxtx_pud_en:1;
unsigned int     etn_led_rxtx_pud_sel:1;
unsigned int     etn_led_link_smt:1;
unsigned int     etn_led_link_e2:1;
unsigned int     etn_led_link_pud_en:1;
unsigned int     etn_led_link_pud_sel:1;
unsigned int     ur0_tx_smt:1;
unsigned int     ur0_tx_e2:1;
unsigned int     ur0_tx_pud_en:1;
unsigned int     ur0_tx_pud_sel:1;
unsigned int     ur0_rx_smt:1;
unsigned int     ur0_rx_e2:1;
unsigned int     ur0_rx_pud_en:1;
unsigned int     ur0_rx_pud_sel:1;
unsigned int     ur1_cts_n_smt:1;
unsigned int     ur1_cts_n_e2:1;
unsigned int     ur1_cts_n_pud_en:1;
unsigned int     ur1_cts_n_pud_sel:1;
unsigned int     ur1_rts_n_smt:1;
unsigned int     ur1_rts_n_e2:1;
unsigned int     ur1_rts_n_pud_en:1;
unsigned int     ur1_rts_n_pud_sel:1;
unsigned int     ur1_tx_smt:1;
unsigned int     ur1_tx_e2:1;
unsigned int     ur1_tx_pud_en:1;
unsigned int     ur1_tx_pud_sel:1;
unsigned int     ur1_rx_smt:1;
unsigned int     ur1_rx_e2:1;
unsigned int     ur1_rx_pud_en:1;
unsigned int     ur1_rx_pud_sel:1;
}ISO_PFUNC1;

typedef struct 
{
unsigned int     i2c_scl_1_smt:1;
unsigned int     i2c_scl_1_e2:1;
unsigned int     i2c_scl_1_pud_en:1;
unsigned int     i2c_scl_1_pud_sel:1;
unsigned int     i2c_sda_1_smt:1;
unsigned int     i2c_sda_1_e2:1;
unsigned int     i2c_sda_1_pud_en:1;
unsigned int     i2c_sda_1_pud_sel:1;
unsigned int     ir_tx_smt:1;
unsigned int     ir_tx_e2:1;
unsigned int     ir_tx_pud_en:1;
unsigned int     ir_tx_pud_sel:1;
unsigned int     i2c_scl_6_smt:1;
unsigned int     i2c_scl_6_e2:1;
unsigned int     i2c_scl_6_pud_en:1;
unsigned int     i2c_scl_6_pud_sel:1;
unsigned int     i2c_sda_6_smt:1;
unsigned int     i2c_sda_6_e2:1;
unsigned int     i2c_sda_6_pud_en:1;
unsigned int     i2c_sda_6_pud_sel:1;
unsigned int     boot_sel_pud_en:1;
unsigned int     boot_sel_pud_sel:1;
unsigned int     testmode_pud_en:1;
unsigned int     testmode_pud_sel:1;
unsigned int     standby1_smt:1;
unsigned int     standby1_e2:1;
unsigned int     standby1_pud_en:1;
unsigned int     standby1_pud_sel:1;
unsigned int     standby_smt:1;
unsigned int     standby_e2:1;
unsigned int     standby_pud_en:1;
unsigned int     standby_pud_sel:1;
}ISO_PFUNC2;

typedef struct 
{
unsigned int     nat_led_3_smt:1;
unsigned int     nat_led_3_e2:1;
unsigned int     nat_led_3_pud_en:1;
unsigned int     nat_led_3_pud_sel:1;
unsigned int     nat_led_2_smt:1;
unsigned int     nat_led_2_e2:1;
unsigned int     nat_led_2_pud_en:1;
unsigned int     nat_led_2_pud_sel:1;
unsigned int     nat_led_1_smt:1;
unsigned int     nat_led_1_e2:1;
unsigned int     nat_led_1_pud_en:1;
unsigned int     nat_led_1_pud_sel:1;
unsigned int     nat_led_0_smt:1;
unsigned int     nat_led_0_e2:1;
unsigned int     nat_led_0_pud_en:1;
unsigned int     nat_led_0_pud_sel:1;
unsigned int     hdmi_hpd_smt:1;
unsigned int     hdmi_hpd_e2:1;
unsigned int     hdmi_hpd_pud_en:1;
unsigned int     hdmi_hpd_pud_sel:1;
unsigned int     reset_n_pud_en:1;
unsigned int     reset_n_pud_sel:1;
unsigned int     reserved_0:2;
unsigned int     boption12_en:1;
unsigned int     boption12_sel:1;
unsigned int     boption11_en:1;
unsigned int     boption11_sel:1;
unsigned int     boption10_en:1;
unsigned int     boption10_sel:1;
unsigned int     boption2_en:1;
unsigned int     boption2_sel:1;
}ISO_PFUNC3;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     etn_led_rxtx:2;
unsigned int     etn_led_link:2;
unsigned int     i2c_sda_0:2;
unsigned int     i2c_scl_0:2;
unsigned int     ur1_rts_n:2;
unsigned int     ur1_cts_n:2;
unsigned int     ur1_tx:2;
unsigned int     ur1_rx:2;
unsigned int     ur0_tx:2;
unsigned int     ur0_rx:2;
unsigned int     ir_tx:2;
unsigned int     ir_rx:2;
unsigned int     iso_gpio_7:2;
unsigned int     iso_gpio_5:2;
unsigned int     iso_gpio_4:2;
}ISO_MUXPAD0;

typedef struct 
{
unsigned int     ur2_loc:2;
unsigned int     ejtag_avcpu_loc:2;
unsigned int     pwm_01_open_drain_en_loc1:1;
unsigned int     pwm_23_open_drain_en_loc1:1;
unsigned int     pwm_01_open_drain_en_loc0:1;
unsigned int     pwm_23_open_drain_en_loc0:1;
unsigned int     nat_led_3:2;
unsigned int     nat_led_2:2;
unsigned int     nat_led_1:2;
unsigned int     nat_led_0:2;
unsigned int     i2c_sda_1:2;
unsigned int     i2c_scl_1:2;
unsigned int     iso_gpio_3:3;
unsigned int     iso_gpio_2:3;
unsigned int     hdmi_hpd:2;
unsigned int     i2c_sda_6:2;
unsigned int     i2c_scl_6:2;
}ISO_MUXPAD1;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     boot_sel_smt:1;
unsigned int     testmode_smt:1;
unsigned int     reset_n_smt:1;
unsigned int     reserved_1:1;
unsigned int     boption12_smt:1;
unsigned int     boption11_smt:1;
unsigned int     boption10_smt:1;
unsigned int     boption2_smt:1;
unsigned int     iso_gpio_25_smt:1;
unsigned int     iso_gpio_25_e2:1;
unsigned int     iso_gpio_25_pud_en:1;
unsigned int     iso_gpio_25_pud_sel:1;
unsigned int     iso_gpio_24_smt:1;
unsigned int     iso_gpio_24_e2:1;
unsigned int     iso_gpio_24_pud_en:1;
unsigned int     iso_gpio_24_pud_sel:1;
unsigned int     iso_gpio_23_smt:1;
unsigned int     iso_gpio_23_e2:1;
unsigned int     iso_gpio_23_pud_en:1;
unsigned int     iso_gpio_23_pud_sel:1;
unsigned int     iso_gpio_22_smt:1;
unsigned int     iso_gpio_22_e2:1;
unsigned int     iso_gpio_22_pud_en:1;
unsigned int     iso_gpio_22_pud_sel:1;
unsigned int     iso_gpio_21_smt:1;
unsigned int     iso_gpio_21_e2:1;
unsigned int     iso_gpio_21_pud_en:1;
unsigned int     iso_gpio_21_pud_sel:1;
}ISO_PFUNC4;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     i2c_tg_enable:1;
unsigned int     reserved_1:1;
unsigned int     iso_gpio_34:2;
unsigned int     iso_gpio_33:2;
unsigned int     iso_gpio_25:2;
unsigned int     iso_gpio_24:2;
unsigned int     iso_gpio_23:2;
unsigned int     iso_gpio_22:2;
unsigned int     iso_gpio_21:2;
}ISO_MUXPAD2;

typedef struct 
{
unsigned int     reserved_0:20;
unsigned int     wd_rset_smt:1;
unsigned int     wd_rset_e2:1;
unsigned int     wd_rset_pud_en:1;
unsigned int     wd_rset_pud_sel:1;
unsigned int     iso_gpio_34_smt:1;
unsigned int     iso_gpio_34_e2:1;
unsigned int     iso_gpio_34_pud_en:1;
unsigned int     iso_gpio_34_pud_sel:1;
unsigned int     iso_gpio_33_smt:1;
unsigned int     iso_gpio_33_e2:1;
unsigned int     iso_gpio_33_pud_en:1;
unsigned int     iso_gpio_33_pud_sel:1;
}ISO_PFUNC5;

typedef struct 
{
unsigned int     irrbl:8;
unsigned int     irrml:8;
unsigned int     irrdzl:8;
unsigned int     irrdol:8;
}ISO_IR_PSR;

typedef struct 
{
unsigned int     reserved_0:10;
unsigned int     irrdl:6;
unsigned int     irrrl:8;
unsigned int     irrsl:8;
}ISO_IR_PER;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     irfd:16;
}ISO_IR_SF;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     iriotcdp:16;
}ISO_IR_DPIR;

typedef struct 
{
unsigned int     irsr:1;
unsigned int     reserved_0:5;
unsigned int     rcmm_en:1;
unsigned int     toshiba_en:1;
unsigned int     irednm:1;
unsigned int     reserved_1:1;
unsigned int     iredn:6;
unsigned int     reserved_2:1;
unsigned int     raw_fifo_ov:1;
unsigned int     raw_fifo_val:1;
unsigned int     raw_en:1;
unsigned int     mlae:1;
unsigned int     irie:1;
unsigned int     irres:1;
unsigned int     irue:1;
unsigned int     ircm:1;
unsigned int     irbme:1;
unsigned int     irdpm:1;
unsigned int     irdn:5;
}ISO_IR_CR;

typedef struct 
{
unsigned int     irrp:32;
}ISO_IR_RP;

typedef struct 
{
unsigned int     reserved_0:26;
unsigned int     slen_big:1;
unsigned int     blen_big:1;
unsigned int     raw_fifo_ov:1;
unsigned int     raw_fifo_val:1;
unsigned int     irrf:1;
unsigned int     irdvf:1;
}ISO_IR_SR;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     write_en2:1;
unsigned int     stop_sample:1;
unsigned int     stop_time:16;
unsigned int     reserved_1:1;
unsigned int     write_en1:1;
unsigned int     fifo_thr:6;
}ISO_IR_RAW_CTRL;

typedef struct 
{
unsigned int     dat:32;
}ISO_IR_RAW_FF;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     cnt:16;
}ISO_IR_RAW_SAMPLE_TIME;

typedef struct 
{
unsigned int     reserved_0:26;
unsigned int     val:6;
}ISO_IR_RAW_WL;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     len:8;
unsigned int     clk:16;
}ISO_IR_RAW_DEB;

typedef struct 
{
unsigned int     irrbl:8;
unsigned int     irrml:8;
unsigned int     irrdzl:8;
unsigned int     irrdol:8;
}ISO_IR_PSR_UP;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     irrrl:8;
unsigned int     irrsl:8;
}ISO_IR_PER_UP;

typedef struct 
{
unsigned int     reserved_0:23;
unsigned int     rc6_en:1;
unsigned int     irtr:8;
}ISO_IR_CTRL_RC6;

typedef struct 
{
unsigned int     irrp:32;
}ISO_IR_RP2;

typedef struct 
{
unsigned int     irtx_en:1;
unsigned int     reserved_0:20;
unsigned int     iact_lvl:1;
unsigned int     modulation:1;
unsigned int     endian:1;
unsigned int     dummy:2;
unsigned int     fifoout_inv:1;
unsigned int     irtxout_inv:1;
unsigned int     reserved_1:3;
unsigned int     start:1;
}ISO_IRTX_CFG;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     irtx_fd:16;
}ISO_IRTX_TIM;

typedef struct 
{
unsigned int     reserved_0:12;
unsigned int     pwm_clksrc_div:4;
unsigned int     pwm_clk_duty:8;
unsigned int     pwm_clk_div:8;
}ISO_IRTX_PWM_SETTING;

typedef struct 
{
unsigned int     reserved_0:18;
unsigned int     data_thr:6;
unsigned int     reserved_1:5;
unsigned int     fin_en:1;
unsigned int     emp_en:1;
unsigned int     req_en:1;
}ISO_IRTX_INT_EN;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     fin_flag:1;
unsigned int     emp_flag:1;
unsigned int     req_flag:1;
}ISO_IRTX_INT_ST;

typedef struct 
{
unsigned int     fifo_rst:1;
unsigned int     reserved_0:19;
unsigned int     valid_len:4;
unsigned int     wrp:4;
unsigned int     rdp:4;
}ISO_IRTX_FIFO_ST;

typedef struct 
{
unsigned int     data:32;
}ISO_IRTX_FIFO;

typedef struct 
{
unsigned int     len_11:8;
unsigned int     len_10:8;
unsigned int     len_01:8;
unsigned int     len_00:8;
}ISO_IRRCMM_TIMING;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     dec_by_min_max:1;
}ISO_IR_CR1;

typedef struct 
{
unsigned int     rcmm_ap_max:8;
unsigned int     rcmm_ap_min:8;
unsigned int     rcmm_kb_max:8;
unsigned int     rcmm_kb_min:8;
}ISO_IRRCMM_APKB;

typedef struct 
{
unsigned int     rcmm_apoint:1;
unsigned int     rcmm_kboard:1;
unsigned int     remote_cnt_lead_high:14;
unsigned int     remote_cnt_lead_low:16;
}ISO_IRRXRCLFIFO;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     set:1;
}ISO_DRM_ST;

typedef struct 
{
unsigned int     val:32;
}ISO_DRM_SECURE_CLK;

typedef struct 
{
unsigned int     val:32;
}ISO_DRM_ELAPSED;

typedef struct 
{
unsigned int     val:32;
}ISO_COLD_RST;

typedef struct 
{
unsigned int     val:32;
}ISO_COLD_RST1;

typedef struct 
{
unsigned int     val:32;
}ISO_COLD_RST2;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     clk_div_en:1;
unsigned int     clk_sel:1;
}ISO_DRM_CTRL;

typedef struct 
{
unsigned int     init:32;
}ISO_DRM_CLK_DIV;

typedef struct 
{
unsigned int     tc3tvr:32;
}ISO_TC3TVR;

typedef struct 
{
unsigned int     tc3cvr:32;
}ISO_TC3CVR;

typedef struct 
{
unsigned int     tc3en:1;
unsigned int     tc3mode:1;
unsigned int     tc3pause:1;
unsigned int     rvda:5;
unsigned int     reserved_0:24;
}ISO_TC3CR;

typedef struct 
{
unsigned int     tc3ie:1;
unsigned int     reserved_0:31;
}ISO_TC3ICR;

typedef struct 
{
unsigned int     tc4tvr:32;
}ISO_TC4TVR;

typedef struct 
{
unsigned int     tc4cvr:32;
}ISO_TC4CVR;

typedef struct 
{
unsigned int     tc4en:1;
unsigned int     tc4mode:1;
unsigned int     tc4pause:1;
unsigned int     rvda:5;
unsigned int     reserved_0:24;
}ISO_TC4CR;

typedef struct 
{
unsigned int     tc4ie:1;
unsigned int     reserved_0:31;
}ISO_TC4ICR;

typedef struct 
{
unsigned int     dat:32;
}ISO_NORST;

typedef struct 
{
unsigned int     val:32;
}ISO_COLD_RST3;

typedef struct 
{
unsigned int     val:32;
}ISO_COLD_RST4;

typedef struct 
{
unsigned int     val:32;
}ISO_COLD_RST5;

typedef struct 
{
unsigned int     val:32;
}ISO_COLD_RST6;

typedef struct 
{
unsigned int     val:32;
}ISO_COLD_RST7;

typedef struct 
{
unsigned int     val:32;
}ISO_COLD_RST8;

typedef struct 
{
unsigned int     val:32;
}ISO_COLD_RST9;

typedef struct 
{
unsigned int     val:32;
}ISO_COLD_RST10;

typedef struct 
{
unsigned int     wd_int_en:1;
unsigned int     reserved_0:15;
unsigned int     nmic:4;
unsigned int     wdc:4;
unsigned int     wden:8;
}ISO_TCWCR;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     wdclr:1;
}ISO_TCWTR;

typedef struct 
{
unsigned int     sel:32;
}ISO_TCWNMI;

typedef struct 
{
unsigned int     sel:32;
}ISO_TCWOV;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     set:1;
}ISO_DRM_ST_SWC;

typedef struct 
{
unsigned int     val:32;
}ISO_DRM_SECURE_CLK_SWC;

typedef struct 
{
unsigned int     val:32;
}ISO_DRM_ELAPSED_SWC;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     clk_div_en:1;
unsigned int     clk_sel:1;
}ISO_DRM_CTRL_SWC;

typedef struct 
{
unsigned int     init:32;
}ISO_DRM_CLK_DIV_SWC;

typedef struct 
{
unsigned int     val:32;
}ISO_COLD_RST_SWC;

typedef struct 
{
unsigned int     val:32;
}ISO_COLD_RST1_SWC;

typedef struct 
{
unsigned int     val:32;
}ISO_COLD_RST2_SWC;

typedef struct 
{
unsigned int     val:32;
}ISO_COLD_RST3_SWC;

typedef struct 
{
unsigned int     dat:32;
}ISO_NORST_SWC;

typedef struct 
{
unsigned int     dat:32;
}ISO_NORST1_SWC;

typedef struct 
{
unsigned int     dat:32;
}ISO_NORST2_SWC;

typedef struct 
{
unsigned int     sel:32;
}ISO_TCWOV_RSTB_CNT;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     dmy:1;
unsigned int     oe:1;
}ISO_TCWOV_RSTB_PAD;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     scpu_boot_info_valid:1;
}ISO_CPU_ST2V;

typedef struct 
{
unsigned int     scpu_boot_info:32;
}ISO_CPU_ST2;

typedef struct 
{
unsigned int     reserved_0:18;
unsigned int     write_enable3:1;
unsigned int     sel1:5;
unsigned int     write_enable2:1;
unsigned int     sel0:5;
unsigned int     write_enable1:1;
unsigned int     enable:1;
}ISO_ACPU_DBG;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     analogy_mode_in:1;
}ISO_ANLG;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     dll:8;
}ISO_U0RBR_THR_DLL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     dlh:8;
}ISO_U0IER_DLH;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     fifo16:2;
unsigned int     reserved_1:2;
unsigned int     iid:4;
}ISO_U0IIR_FCR;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     dlab:1;
unsigned int     brk:1;
unsigned int     reserved_1:1;
unsigned int     eps:1;
unsigned int     pen:1;
unsigned int     stb:1;
unsigned int     wls:2;
}ISO_U0LCR;

typedef struct 
{
unsigned int     reserved_0:26;
unsigned int     afce:1;
unsigned int     loop:1;
unsigned int     reserved_1:2;
unsigned int     rts:1;
unsigned int     dtr:1;
}ISO_U0MCR;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     rfe:1;
unsigned int     temt:1;
unsigned int     thre:1;
unsigned int     bi:1;
unsigned int     fe:1;
unsigned int     pe:1;
unsigned int     oe:1;
unsigned int     dr:1;
}ISO_U0LSR;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     dcd:1;
unsigned int     ri:1;
unsigned int     dsr:1;
unsigned int     cts:1;
unsigned int     ddcd:1;
unsigned int     teri:1;
unsigned int     ddsr:1;
unsigned int     dcts:1;
}ISO_U0MSR;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     scr:8;
}ISO_U0SCR;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     rbd:8;
}ISO_U0SRBR;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     far:1;
}ISO_U0FAR;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     far:8;
}ISO_U0TFR;

typedef struct 
{
unsigned int     reserved_0:22;
unsigned int     rffe:1;
unsigned int     rfpf:1;
unsigned int     rfwd:8;
}ISO_U0RFW;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     rff:1;
unsigned int     rfne:1;
unsigned int     tfe:1;
unsigned int     tfnf:1;
unsigned int     busy:1;
}ISO_U0USR;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     tfl:8;
}ISO_U0TFL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     rfl:8;
}ISO_U0RFL;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     xfr:1;
unsigned int     rfr:1;
unsigned int     ur:1;
}ISO_U0SRR;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     sbcr:1;
}ISO_U0SBCR;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     sdmam:1;
}ISO_U0SDMAM;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     sfe:1;
}ISO_U0SFE;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     srt:2;
}ISO_U0SRT;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     stet:2;
}ISO_U0STET;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     htx:1;
}ISO_U0HTX;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     dmasa:1;
}ISO_U0DMASA;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     fifo_mode:8;
unsigned int     reserved_1:2;
unsigned int     dma_extra:1;
unsigned int     uart_add_encoded_params:1;
unsigned int     shadow:1;
unsigned int     fifo_stat:1;
unsigned int     fifo_access:1;
unsigned int     additional_feat:1;
unsigned int     sir_lp_mode:1;
unsigned int     sir_mode:1;
unsigned int     thre_mode:1;
unsigned int     afce_mode:1;
unsigned int     reserved_2:2;
unsigned int     apb_data_width:2;
}ISO_U0CPR;

typedef struct 
{
unsigned int     ucv:32;
}ISO_U0UCV;

typedef struct 
{
unsigned int     ctr:32;
}ISO_U0CTR;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     ic_slave_disable:1;
unsigned int     ic_restart_en:1;
unsigned int     ic_10bitaddr_master:1;
unsigned int     ic_10bitaddr_slave:1;
unsigned int     speed:2;
unsigned int     master_mode:1;
}ISO_IC0_CON;

typedef struct 
{
unsigned int     reserved_0:19;
unsigned int     ic_10bitaddr_master:1;
unsigned int     special:1;
unsigned int     gc_or_start:1;
unsigned int     ic_tar:10;
}ISO_IC0_TAR;

typedef struct 
{
unsigned int     reserved_0:22;
unsigned int     ic_sar:10;
}ISO_IC0_SAR;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     ic_hs_mar:3;
}ISO_IC0_HS_MADDR;

typedef struct 
{
unsigned int     reserved_0:21;
unsigned int     restart:1;
unsigned int     stop:1;
unsigned int     cmd:1;
unsigned int     dat:8;
}ISO_IC0_DATA_CMD;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     ic_ss_scl_hcnt:16;
}ISO_IC0_SS_SCL_HCNT;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     ic_ss_scl_lcnt:16;
}ISO_IC0_SS_SCL_LCNT;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     ic_fs_scl_hcnt:16;
}ISO_IC0_FS_SCL_HCNT;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     ic_fs_scl_lcnt:16;
}ISO_IC0_FS_SCL_LCNT;

typedef struct 
{
unsigned int     reserved_0:20;
unsigned int     r_gen_call:1;
unsigned int     r_start_det:1;
unsigned int     r_stop_det:1;
unsigned int     r_activity:1;
unsigned int     r_rx_done:1;
unsigned int     r_tx_abrt:1;
unsigned int     r_rd_req:1;
unsigned int     r_tx_empty:1;
unsigned int     r_tx_over:1;
unsigned int     r_rx_full:1;
unsigned int     r_rx_over:1;
unsigned int     r_rx_under:1;
}ISO_IC0_INTR_STAT;

typedef struct 
{
unsigned int     reserved_0:20;
unsigned int     m_gen_call:1;
unsigned int     m_start_det:1;
unsigned int     m_stop_det:1;
unsigned int     m_activity:1;
unsigned int     m_rx_done:1;
unsigned int     m_tx_abrt:1;
unsigned int     m_rd_req:1;
unsigned int     m_tx_empty:1;
unsigned int     m_tx_over:1;
unsigned int     m_rx_full:1;
unsigned int     m_rx_over:1;
unsigned int     m_rx_under:1;
}ISO_IC0_INTR_MASK;

typedef struct 
{
unsigned int     reserved_0:20;
unsigned int     gen_call:1;
unsigned int     start_det:1;
unsigned int     stop_det:1;
unsigned int     activity:1;
unsigned int     rx_done:1;
unsigned int     tx_abrt:1;
unsigned int     rd_req:1;
unsigned int     tx_empty:1;
unsigned int     tx_over:1;
unsigned int     rx_full:1;
unsigned int     rx_over:1;
unsigned int     rx_under:1;
}ISO_IC0_RAW_INTR_STAT;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     rx_tl:8;
}ISO_IC0_RX_TL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     tx_tl:8;
}ISO_IC0_TX_TL;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_intr:1;
}ISO_IC0_CLR_INTR;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_rx_under:1;
}ISO_IC0_CLR_RX_UNDER;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_rx_over:1;
}ISO_IC0_CLR_RX_OVER;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_tx_over:1;
}ISO_IC0_CLR_TX_OVER;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_rd_req:1;
}ISO_IC0_CLR_RD_REQ;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_tx_abrt:1;
}ISO_IC0_CLR_TX_ABRT;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_rx_done:1;
}ISO_IC0_CLR_RX_DONE;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_activity:1;
}ISO_IC0_CLR_ACTIVITY;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_stop_det:1;
}ISO_IC0_CLR_STOP_DET;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_start_det:1;
}ISO_IC0_CLR_START_DET;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_gen_call:1;
}ISO_IC0_CLR_GEN_CALL;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     enable:1;
}ISO_IC0_ENABLE;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     slv_activity:1;
unsigned int     mst_activity:1;
unsigned int     rff:1;
unsigned int     rfne:1;
unsigned int     tfe:1;
unsigned int     tfnf:1;
unsigned int     activity:1;
}ISO_IC0_STATUS;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     txflr:4;
}ISO_IC0_TXFLR;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     rxflr:4;
}ISO_IC0_RXFLR;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     ic_sda_hold:16;
}ISO_IC0_SDA_HOLD;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     abrt_slvrd_intx:1;
unsigned int     abrt_slv_arblost:1;
unsigned int     abrt_slvflush_txfifo:1;
unsigned int     arb_lost:1;
unsigned int     arb_master_dis:1;
unsigned int     abrt_10b_rd_norstrt:1;
unsigned int     abrt_sbyte_norstrt:1;
unsigned int     abrt_hs_norstrt:1;
unsigned int     abrt_sbyte_ackdet:1;
unsigned int     abrt_hs_ackdet:1;
unsigned int     abrt_gcall_read:1;
unsigned int     abrt_gcall_noack:1;
unsigned int     abrt_txdata_noack:1;
unsigned int     abrt_10addr2_noack:1;
unsigned int     abrt_10addr1_noack:1;
unsigned int     abrt_7b_addr_noack:1;
}ISO_IC0_TX_ABRT_SOURCE;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     nack:1;
}ISO_IC0_SLV_DATA_NACK_ONLY;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     tdmae:1;
unsigned int     rdmae:1;
}ISO_IC0_DMA_CR;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     dmatdl:3;
}ISO_IC0_DMA_TDLR;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     dmardl:4;
}ISO_IC0_DMA_RDLR;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     sda_setup:8;
}ISO_IC0_SDA_SETUP;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     ack_gen_call:1;
}ISO_IC0_ACK_GENERAL_CALL;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     slv_rx_data_lost:1;
unsigned int     slv_disabled_whi:1;
unsigned int     ic_en:1;
}ISO_IC0_ENABLE_STATUS;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     tx_buffer_depth:8;
unsigned int     rx_buffer_depth:8;
unsigned int     add_encoded_params:1;
unsigned int     has_dma:1;
unsigned int     intr_io:1;
unsigned int     hc_count_values:1;
unsigned int     max_speed_mode:2;
unsigned int     apb_data_width:2;
}ISO_IC0_COMP_PARAM_1;

typedef struct 
{
unsigned int     ic_comp_version:32;
}ISO_IC0_COMP_VERSION;

typedef struct 
{
unsigned int     ic_comp_type:32;
}ISO_IC0_COMP_TYPE;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     ic_slave_disable:1;
unsigned int     ic_restart_en:1;
unsigned int     ic_10bitaddr_master:1;
unsigned int     ic_10bitaddr_slave:1;
unsigned int     speed:2;
unsigned int     master_mode:1;
}ISO_IC1_CON;

typedef struct 
{
unsigned int     reserved_0:19;
unsigned int     ic_10bitaddr_master:1;
unsigned int     special:1;
unsigned int     gc_or_start:1;
unsigned int     ic_tar:10;
}ISO_IC1_TAR;

typedef struct 
{
unsigned int     reserved_0:22;
unsigned int     ic_sar:10;
}ISO_IC1_SAR;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     ic_hs_mar:3;
}ISO_IC1_HS_MADDR;

typedef struct 
{
unsigned int     reserved_0:21;
unsigned int     restart:1;
unsigned int     stop:1;
unsigned int     cmd:1;
unsigned int     dat:8;
}ISO_IC1_DATA_CMD;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     ic_ss_scl_hcnt:16;
}ISO_IC1_SS_SCL_HCNT;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     ic_ss_scl_lcnt:16;
}ISO_IC1_SS_SCL_LCNT;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     ic_fs_scl_hcnt:16;
}ISO_IC1_FS_SCL_HCNT;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     ic_fs_scl_lcnt:16;
}ISO_IC1_FS_SCL_LCNT;

typedef struct 
{
unsigned int     reserved_0:20;
unsigned int     r_gen_call:1;
unsigned int     r_start_det:1;
unsigned int     r_stop_det:1;
unsigned int     r_activity:1;
unsigned int     r_rx_done:1;
unsigned int     r_tx_abrt:1;
unsigned int     r_rd_req:1;
unsigned int     r_tx_empty:1;
unsigned int     r_tx_over:1;
unsigned int     r_rx_full:1;
unsigned int     r_rx_over:1;
unsigned int     r_rx_under:1;
}ISO_IC1_INTR_STAT;

typedef struct 
{
unsigned int     reserved_0:20;
unsigned int     m_gen_call:1;
unsigned int     m_start_det:1;
unsigned int     m_stop_det:1;
unsigned int     m_activity:1;
unsigned int     m_rx_done:1;
unsigned int     m_tx_abrt:1;
unsigned int     m_rd_req:1;
unsigned int     m_tx_empty:1;
unsigned int     m_tx_over:1;
unsigned int     m_rx_full:1;
unsigned int     m_rx_over:1;
unsigned int     m_rx_under:1;
}ISO_IC1_INTR_MASK;

typedef struct 
{
unsigned int     reserved_0:20;
unsigned int     gen_call:1;
unsigned int     start_det:1;
unsigned int     stop_det:1;
unsigned int     activity:1;
unsigned int     rx_done:1;
unsigned int     tx_abrt:1;
unsigned int     rd_req:1;
unsigned int     tx_empty:1;
unsigned int     tx_over:1;
unsigned int     rx_full:1;
unsigned int     rx_over:1;
unsigned int     rx_under:1;
}ISO_IC1_RAW_INTR_STAT;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     rx_tl:8;
}ISO_IC1_RX_TL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     tx_tl:8;
}ISO_IC1_TX_TL;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_intr:1;
}ISO_IC1_CLR_INTR;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_rx_under:1;
}ISO_IC1_CLR_RX_UNDER;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_rx_over:1;
}ISO_IC1_CLR_RX_OVER;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_tx_over:1;
}ISO_IC1_CLR_TX_OVER;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_rd_req:1;
}ISO_IC1_CLR_RD_REQ;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_tx_abrt:1;
}ISO_IC1_CLR_TX_ABRT;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_rx_done:1;
}ISO_IC1_CLR_RX_DONE;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_activity:1;
}ISO_IC1_CLR_ACTIVITY;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_stop_det:1;
}ISO_IC1_CLR_STOP_DET;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_start_det:1;
}ISO_IC1_CLR_START_DET;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_gen_call:1;
}ISO_IC1_CLR_GEN_CALL;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     enable:1;
}ISO_IC1_ENABLE;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     slv_activity:1;
unsigned int     mst_activity:1;
unsigned int     rff:1;
unsigned int     rfne:1;
unsigned int     tfe:1;
unsigned int     tfnf:1;
unsigned int     activity:1;
}ISO_IC1_STATUS;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     txflr:4;
}ISO_IC1_TXFLR;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     rxflr:4;
}ISO_IC1_RXFLR;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     ic_sda_hold:16;
}ISO_IC1_SDA_HOLD;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     abrt_slvrd_intx:1;
unsigned int     abrt_slv_arblost:1;
unsigned int     abrt_slvflush_txfifo:1;
unsigned int     arb_lost:1;
unsigned int     arb_master_dis:1;
unsigned int     abrt_10b_rd_norstrt:1;
unsigned int     abrt_sbyte_norstrt:1;
unsigned int     abrt_hs_norstrt:1;
unsigned int     abrt_sbyte_ackdet:1;
unsigned int     abrt_hs_ackdet:1;
unsigned int     abrt_gcall_read:1;
unsigned int     abrt_gcall_noack:1;
unsigned int     abrt_txdata_noack:1;
unsigned int     abrt_10addr2_noack:1;
unsigned int     abrt_10addr1_noack:1;
unsigned int     abrt_7b_addr_noack:1;
}ISO_IC1_TX_ABRT_SOURCE;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     nack:1;
}ISO_IC1_SLV_DATA_NACK_ONLY;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     tdmae:1;
unsigned int     rdmae:1;
}ISO_IC1_DMA_CR;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     dmatdl:3;
}ISO_IC1_DMA_TDLR;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     dmardl:4;
}ISO_IC1_DMA_RDLR;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     sda_setup:8;
}ISO_IC1_SDA_SETUP;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     ack_gen_call:1;
}ISO_IC1_ACK_GENERAL_CALL;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     slv_rx_data_lost:1;
unsigned int     slv_disabled_whi:1;
unsigned int     ic_en:1;
}ISO_IC1_ENABLE_STATUS;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     tx_buffer_depth:8;
unsigned int     rx_buffer_depth:8;
unsigned int     add_encoded_params:1;
unsigned int     has_dma:1;
unsigned int     intr_io:1;
unsigned int     hc_count_values:1;
unsigned int     max_speed_mode:2;
unsigned int     apb_data_width:2;
}ISO_IC1_COMP_PARAM_1;

typedef struct 
{
unsigned int     ic_comp_version:32;
}ISO_IC1_COMP_VERSION;

typedef struct 
{
unsigned int     ic_comp_type:32;
}ISO_IC1_COMP_TYPE;

typedef struct 
{
unsigned int     3:8;
unsigned int     2:8;
unsigned int     1:8;
unsigned int     0:8;
}ISO_PWM_OCD;

typedef struct 
{
unsigned int     3:8;
unsigned int     2:8;
unsigned int     1:8;
unsigned int     0:8;
}ISO_PWM_CD;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     3:4;
unsigned int     2:4;
unsigned int     1:4;
unsigned int     0:4;
}ISO_PWM_CSD;

#endif

#define ISO_ISR                                                                      0x98007000
#define ISO_ISR_reg_addr                                                             "0x98007000"
#define ISO_ISR_reg                                                                  0x98007000
#define set_ISO_ISR_reg(data)   (*((volatile unsigned int*) ISO_ISR_reg)=data)
#define get_ISO_ISR_reg   (*((volatile unsigned int*) ISO_ISR_reg))
#define ISO_ISR_inst_adr                                                             "0x0000"
#define ISO_ISR_inst                                                                 0x0000
#define ISO_ISR_i2c1_req_int_shift                                                   (31)
#define ISO_ISR_i2c1_req_int_mask                                                    (0x80000000)
#define ISO_ISR_i2c1_req_int(data)                                                   (0x80000000&((data)<<31))
#define ISO_ISR_i2c1_req_int_src(data)                                               ((0x80000000&(data))>>31)
#define ISO_ISR_get_i2c1_req_int(data)                                               ((0x80000000&(data))>>31)
#define ISO_ISR_porb_av_cen_int_shift                                                (30)
#define ISO_ISR_porb_av_cen_int_mask                                                 (0x40000000)
#define ISO_ISR_porb_av_cen_int(data)                                                (0x40000000&((data)<<30))
#define ISO_ISR_porb_av_cen_int_src(data)                                            ((0x40000000&(data))>>30)
#define ISO_ISR_get_porb_av_cen_int(data)                                            ((0x40000000&(data))>>30)
#define ISO_ISR_porb_dv_cen_int_shift                                                (29)
#define ISO_ISR_porb_dv_cen_int_mask                                                 (0x20000000)
#define ISO_ISR_porb_dv_cen_int(data)                                                (0x20000000&((data)<<29))
#define ISO_ISR_porb_dv_cen_int_src(data)                                            ((0x20000000&(data))>>29)
#define ISO_ISR_get_porb_dv_cen_int(data)                                            ((0x20000000&(data))>>29)
#define ISO_ISR_usb_int_shift                                                        (24)
#define ISO_ISR_usb_int_mask                                                         (0x01000000)
#define ISO_ISR_usb_int(data)                                                        (0x01000000&((data)<<24))
#define ISO_ISR_usb_int_src(data)                                                    ((0x01000000&(data))>>24)
#define ISO_ISR_get_usb_int(data)                                                    ((0x01000000&(data))>>24)
#define ISO_ISR_etn_int_shift                                                        (23)
#define ISO_ISR_etn_int_mask                                                         (0x00800000)
#define ISO_ISR_etn_int(data)                                                        (0x00800000&((data)<<23))
#define ISO_ISR_etn_int_src(data)                                                    ((0x00800000&(data))>>23)
#define ISO_ISR_get_etn_int(data)                                                    ((0x00800000&(data))>>23)
#define ISO_ISR_cbus_int_shift                                                       (22)
#define ISO_ISR_cbus_int_mask                                                        (0x00400000)
#define ISO_ISR_cbus_int(data)                                                       (0x00400000&((data)<<22))
#define ISO_ISR_cbus_int_src(data)                                                   ((0x00400000&(data))>>22)
#define ISO_ISR_get_cbus_int(data)                                                   ((0x00400000&(data))>>22)
#define ISO_ISR_iso_misc_int_shift                                                   (21)
#define ISO_ISR_iso_misc_int_mask                                                    (0x00200000)
#define ISO_ISR_iso_misc_int(data)                                                   (0x00200000&((data)<<21))
#define ISO_ISR_iso_misc_int_src(data)                                               ((0x00200000&(data))>>21)
#define ISO_ISR_get_iso_misc_int(data)                                               ((0x00200000&(data))>>21)
#define ISO_ISR_gpioda_int_shift                                                     (20)
#define ISO_ISR_gpioda_int_mask                                                      (0x00100000)
#define ISO_ISR_gpioda_int(data)                                                     (0x00100000&((data)<<20))
#define ISO_ISR_gpioda_int_src(data)                                                 ((0x00100000&(data))>>20)
#define ISO_ISR_get_gpioda_int(data)                                                 ((0x00100000&(data))>>20)
#define ISO_ISR_gpioa_int_shift                                                      (19)
#define ISO_ISR_gpioa_int_mask                                                       (0x00080000)
#define ISO_ISR_gpioa_int(data)                                                      (0x00080000&((data)<<19))
#define ISO_ISR_gpioa_int_src(data)                                                  ((0x00080000&(data))>>19)
#define ISO_ISR_get_gpioa_int(data)                                                  ((0x00080000&(data))>>19)
#define ISO_ISR_rtc_alarm_int_shift                                                  (13)
#define ISO_ISR_rtc_alarm_int_mask                                                   (0x00002000)
#define ISO_ISR_rtc_alarm_int(data)                                                  (0x00002000&((data)<<13))
#define ISO_ISR_rtc_alarm_int_src(data)                                              ((0x00002000&(data))>>13)
#define ISO_ISR_get_rtc_alarm_int(data)                                              ((0x00002000&(data))>>13)
#define ISO_ISR_rtc_hsec_int_shift                                                   (12)
#define ISO_ISR_rtc_hsec_int_mask                                                    (0x00001000)
#define ISO_ISR_rtc_hsec_int(data)                                                   (0x00001000&((data)<<12))
#define ISO_ISR_rtc_hsec_int_src(data)                                               ((0x00001000&(data))>>12)
#define ISO_ISR_get_rtc_hsec_int(data)                                               ((0x00001000&(data))>>12)
#define ISO_ISR_i2c1_int_shift                                                       (11)
#define ISO_ISR_i2c1_int_mask                                                        (0x00000800)
#define ISO_ISR_i2c1_int(data)                                                       (0x00000800&((data)<<11))
#define ISO_ISR_i2c1_int_src(data)                                                   ((0x00000800&(data))>>11)
#define ISO_ISR_get_i2c1_int(data)                                                   ((0x00000800&(data))>>11)
#define ISO_ISR_tc4_int_shift                                                        (9)
#define ISO_ISR_tc4_int_mask                                                         (0x00000200)
#define ISO_ISR_tc4_int(data)                                                        (0x00000200&((data)<<9))
#define ISO_ISR_tc4_int_src(data)                                                    ((0x00000200&(data))>>9)
#define ISO_ISR_get_tc4_int(data)                                                    ((0x00000200&(data))>>9)
#define ISO_ISR_i2c0_int_shift                                                       (8)
#define ISO_ISR_i2c0_int_mask                                                        (0x00000100)
#define ISO_ISR_i2c0_int(data)                                                       (0x00000100&((data)<<8))
#define ISO_ISR_i2c0_int_src(data)                                                   ((0x00000100&(data))>>8)
#define ISO_ISR_get_i2c0_int(data)                                                   ((0x00000100&(data))>>8)
#define ISO_ISR_wdog_nmi_int_shift                                                   (7)
#define ISO_ISR_wdog_nmi_int_mask                                                    (0x00000080)
#define ISO_ISR_wdog_nmi_int(data)                                                   (0x00000080&((data)<<7))
#define ISO_ISR_wdog_nmi_int_src(data)                                               ((0x00000080&(data))>>7)
#define ISO_ISR_get_wdog_nmi_int(data)                                               ((0x00000080&(data))>>7)
#define ISO_ISR_irda_int_shift                                                       (5)
#define ISO_ISR_irda_int_mask                                                        (0x00000020)
#define ISO_ISR_irda_int(data)                                                       (0x00000020&((data)<<5))
#define ISO_ISR_irda_int_src(data)                                                   ((0x00000020&(data))>>5)
#define ISO_ISR_get_irda_int(data)                                                   ((0x00000020&(data))>>5)
#define ISO_ISR_ur0_int_shift                                                        (2)
#define ISO_ISR_ur0_int_mask                                                         (0x00000004)
#define ISO_ISR_ur0_int(data)                                                        (0x00000004&((data)<<2))
#define ISO_ISR_ur0_int_src(data)                                                    ((0x00000004&(data))>>2)
#define ISO_ISR_get_ur0_int(data)                                                    ((0x00000004&(data))>>2)
#define ISO_ISR_tc3_int_shift                                                        (1)
#define ISO_ISR_tc3_int_mask                                                         (0x00000002)
#define ISO_ISR_tc3_int(data)                                                        (0x00000002&((data)<<1))
#define ISO_ISR_tc3_int_src(data)                                                    ((0x00000002&(data))>>1)
#define ISO_ISR_get_tc3_int(data)                                                    ((0x00000002&(data))>>1)
#define ISO_ISR_write_data_shift                                                     (0)
#define ISO_ISR_write_data_mask                                                      (0x00000001)
#define ISO_ISR_write_data(data)                                                     (0x00000001&((data)<<0))
#define ISO_ISR_write_data_src(data)                                                 ((0x00000001&(data))>>0)
#define ISO_ISR_get_write_data(data)                                                 ((0x00000001&(data))>>0)


#define ISO_UMSK_ISR                                                                 0x98007004
#define ISO_UMSK_ISR_reg_addr                                                        "0x98007004"
#define ISO_UMSK_ISR_reg                                                             0x98007004
#define set_ISO_UMSK_ISR_reg(data)   (*((volatile unsigned int*) ISO_UMSK_ISR_reg)=data)
#define get_ISO_UMSK_ISR_reg   (*((volatile unsigned int*) ISO_UMSK_ISR_reg))
#define ISO_UMSK_ISR_inst_adr                                                        "0x0001"
#define ISO_UMSK_ISR_inst                                                            0x0001
#define ISO_UMSK_ISR_i2c1_req_int_shift                                              (31)
#define ISO_UMSK_ISR_i2c1_req_int_mask                                               (0x80000000)
#define ISO_UMSK_ISR_i2c1_req_int(data)                                              (0x80000000&((data)<<31))
#define ISO_UMSK_ISR_i2c1_req_int_src(data)                                          ((0x80000000&(data))>>31)
#define ISO_UMSK_ISR_get_i2c1_req_int(data)                                          ((0x80000000&(data))>>31)
#define ISO_UMSK_ISR_porb_av_cen_int_shift                                           (30)
#define ISO_UMSK_ISR_porb_av_cen_int_mask                                            (0x40000000)
#define ISO_UMSK_ISR_porb_av_cen_int(data)                                           (0x40000000&((data)<<30))
#define ISO_UMSK_ISR_porb_av_cen_int_src(data)                                       ((0x40000000&(data))>>30)
#define ISO_UMSK_ISR_get_porb_av_cen_int(data)                                       ((0x40000000&(data))>>30)
#define ISO_UMSK_ISR_porb_dv_cen_int_shift                                           (29)
#define ISO_UMSK_ISR_porb_dv_cen_int_mask                                            (0x20000000)
#define ISO_UMSK_ISR_porb_dv_cen_int(data)                                           (0x20000000&((data)<<29))
#define ISO_UMSK_ISR_porb_dv_cen_int_src(data)                                       ((0x20000000&(data))>>29)
#define ISO_UMSK_ISR_get_porb_dv_cen_int(data)                                       ((0x20000000&(data))>>29)
#define ISO_UMSK_ISR_gpioda_int_shift                                                (20)
#define ISO_UMSK_ISR_gpioda_int_mask                                                 (0x00100000)
#define ISO_UMSK_ISR_gpioda_int(data)                                                (0x00100000&((data)<<20))
#define ISO_UMSK_ISR_gpioda_int_src(data)                                            ((0x00100000&(data))>>20)
#define ISO_UMSK_ISR_get_gpioda_int(data)                                            ((0x00100000&(data))>>20)
#define ISO_UMSK_ISR_gpioa_int_shift                                                 (19)
#define ISO_UMSK_ISR_gpioa_int_mask                                                  (0x00080000)
#define ISO_UMSK_ISR_gpioa_int(data)                                                 (0x00080000&((data)<<19))
#define ISO_UMSK_ISR_gpioa_int_src(data)                                             ((0x00080000&(data))>>19)
#define ISO_UMSK_ISR_get_gpioa_int(data)                                             ((0x00080000&(data))>>19)
#define ISO_UMSK_ISR_rtc_alarm_int_shift                                             (13)
#define ISO_UMSK_ISR_rtc_alarm_int_mask                                              (0x00002000)
#define ISO_UMSK_ISR_rtc_alarm_int(data)                                             (0x00002000&((data)<<13))
#define ISO_UMSK_ISR_rtc_alarm_int_src(data)                                         ((0x00002000&(data))>>13)
#define ISO_UMSK_ISR_get_rtc_alarm_int(data)                                         ((0x00002000&(data))>>13)
#define ISO_UMSK_ISR_rtc_hsec_int_shift                                              (12)
#define ISO_UMSK_ISR_rtc_hsec_int_mask                                               (0x00001000)
#define ISO_UMSK_ISR_rtc_hsec_int(data)                                              (0x00001000&((data)<<12))
#define ISO_UMSK_ISR_rtc_hsec_int_src(data)                                          ((0x00001000&(data))>>12)
#define ISO_UMSK_ISR_get_rtc_hsec_int(data)                                          ((0x00001000&(data))>>12)
#define ISO_UMSK_ISR_tc4_int_shift                                                   (9)
#define ISO_UMSK_ISR_tc4_int_mask                                                    (0x00000200)
#define ISO_UMSK_ISR_tc4_int(data)                                                   (0x00000200&((data)<<9))
#define ISO_UMSK_ISR_tc4_int_src(data)                                               ((0x00000200&(data))>>9)
#define ISO_UMSK_ISR_get_tc4_int(data)                                               ((0x00000200&(data))>>9)
#define ISO_UMSK_ISR_wdog_nmi_int_shift                                              (7)
#define ISO_UMSK_ISR_wdog_nmi_int_mask                                               (0x00000080)
#define ISO_UMSK_ISR_wdog_nmi_int(data)                                              (0x00000080&((data)<<7))
#define ISO_UMSK_ISR_wdog_nmi_int_src(data)                                          ((0x00000080&(data))>>7)
#define ISO_UMSK_ISR_get_wdog_nmi_int(data)                                          ((0x00000080&(data))>>7)
#define ISO_UMSK_ISR_irda_int_shift                                                  (5)
#define ISO_UMSK_ISR_irda_int_mask                                                   (0x00000020)
#define ISO_UMSK_ISR_irda_int(data)                                                  (0x00000020&((data)<<5))
#define ISO_UMSK_ISR_irda_int_src(data)                                              ((0x00000020&(data))>>5)
#define ISO_UMSK_ISR_get_irda_int(data)                                              ((0x00000020&(data))>>5)
#define ISO_UMSK_ISR_tc3_int_shift                                                   (1)
#define ISO_UMSK_ISR_tc3_int_mask                                                    (0x00000002)
#define ISO_UMSK_ISR_tc3_int(data)                                                   (0x00000002&((data)<<1))
#define ISO_UMSK_ISR_tc3_int_src(data)                                               ((0x00000002&(data))>>1)
#define ISO_UMSK_ISR_get_tc3_int(data)                                               ((0x00000002&(data))>>1)
#define ISO_UMSK_ISR_write_data_shift                                                (0)
#define ISO_UMSK_ISR_write_data_mask                                                 (0x00000001)
#define ISO_UMSK_ISR_write_data(data)                                                (0x00000001&((data)<<0))
#define ISO_UMSK_ISR_write_data_src(data)                                            ((0x00000001&(data))>>0)
#define ISO_UMSK_ISR_get_write_data(data)                                            ((0x00000001&(data))>>0)


#define ISO_UMSK_ISR_GPA0                                                            0x98007008
#define ISO_UMSK_ISR_GPA0_reg_addr                                                   "0x98007008"
#define ISO_UMSK_ISR_GPA0_reg                                                        0x98007008
#define set_ISO_UMSK_ISR_GPA0_reg(data)   (*((volatile unsigned int*) ISO_UMSK_ISR_GPA0_reg)=data)
#define get_ISO_UMSK_ISR_GPA0_reg   (*((volatile unsigned int*) ISO_UMSK_ISR_GPA0_reg))
#define ISO_UMSK_ISR_GPA0_inst_adr                                                   "0x0002"
#define ISO_UMSK_ISR_GPA0_inst                                                       0x0002
#define ISO_UMSK_ISR_GPA0_int30_a_shift                                              (31)
#define ISO_UMSK_ISR_GPA0_int30_a_mask                                               (0x80000000)
#define ISO_UMSK_ISR_GPA0_int30_a(data)                                              (0x80000000&((data)<<31))
#define ISO_UMSK_ISR_GPA0_int30_a_src(data)                                          ((0x80000000&(data))>>31)
#define ISO_UMSK_ISR_GPA0_get_int30_a(data)                                          ((0x80000000&(data))>>31)
#define ISO_UMSK_ISR_GPA0_int29_a_shift                                              (30)
#define ISO_UMSK_ISR_GPA0_int29_a_mask                                               (0x40000000)
#define ISO_UMSK_ISR_GPA0_int29_a(data)                                              (0x40000000&((data)<<30))
#define ISO_UMSK_ISR_GPA0_int29_a_src(data)                                          ((0x40000000&(data))>>30)
#define ISO_UMSK_ISR_GPA0_get_int29_a(data)                                          ((0x40000000&(data))>>30)
#define ISO_UMSK_ISR_GPA0_int28_a_shift                                              (29)
#define ISO_UMSK_ISR_GPA0_int28_a_mask                                               (0x20000000)
#define ISO_UMSK_ISR_GPA0_int28_a(data)                                              (0x20000000&((data)<<29))
#define ISO_UMSK_ISR_GPA0_int28_a_src(data)                                          ((0x20000000&(data))>>29)
#define ISO_UMSK_ISR_GPA0_get_int28_a(data)                                          ((0x20000000&(data))>>29)
#define ISO_UMSK_ISR_GPA0_int27_a_shift                                              (28)
#define ISO_UMSK_ISR_GPA0_int27_a_mask                                               (0x10000000)
#define ISO_UMSK_ISR_GPA0_int27_a(data)                                              (0x10000000&((data)<<28))
#define ISO_UMSK_ISR_GPA0_int27_a_src(data)                                          ((0x10000000&(data))>>28)
#define ISO_UMSK_ISR_GPA0_get_int27_a(data)                                          ((0x10000000&(data))>>28)
#define ISO_UMSK_ISR_GPA0_int26_a_shift                                              (27)
#define ISO_UMSK_ISR_GPA0_int26_a_mask                                               (0x08000000)
#define ISO_UMSK_ISR_GPA0_int26_a(data)                                              (0x08000000&((data)<<27))
#define ISO_UMSK_ISR_GPA0_int26_a_src(data)                                          ((0x08000000&(data))>>27)
#define ISO_UMSK_ISR_GPA0_get_int26_a(data)                                          ((0x08000000&(data))>>27)
#define ISO_UMSK_ISR_GPA0_int25_a_shift                                              (26)
#define ISO_UMSK_ISR_GPA0_int25_a_mask                                               (0x04000000)
#define ISO_UMSK_ISR_GPA0_int25_a(data)                                              (0x04000000&((data)<<26))
#define ISO_UMSK_ISR_GPA0_int25_a_src(data)                                          ((0x04000000&(data))>>26)
#define ISO_UMSK_ISR_GPA0_get_int25_a(data)                                          ((0x04000000&(data))>>26)
#define ISO_UMSK_ISR_GPA0_int24_a_shift                                              (25)
#define ISO_UMSK_ISR_GPA0_int24_a_mask                                               (0x02000000)
#define ISO_UMSK_ISR_GPA0_int24_a(data)                                              (0x02000000&((data)<<25))
#define ISO_UMSK_ISR_GPA0_int24_a_src(data)                                          ((0x02000000&(data))>>25)
#define ISO_UMSK_ISR_GPA0_get_int24_a(data)                                          ((0x02000000&(data))>>25)
#define ISO_UMSK_ISR_GPA0_int23_a_shift                                              (24)
#define ISO_UMSK_ISR_GPA0_int23_a_mask                                               (0x01000000)
#define ISO_UMSK_ISR_GPA0_int23_a(data)                                              (0x01000000&((data)<<24))
#define ISO_UMSK_ISR_GPA0_int23_a_src(data)                                          ((0x01000000&(data))>>24)
#define ISO_UMSK_ISR_GPA0_get_int23_a(data)                                          ((0x01000000&(data))>>24)
#define ISO_UMSK_ISR_GPA0_int22_a_shift                                              (23)
#define ISO_UMSK_ISR_GPA0_int22_a_mask                                               (0x00800000)
#define ISO_UMSK_ISR_GPA0_int22_a(data)                                              (0x00800000&((data)<<23))
#define ISO_UMSK_ISR_GPA0_int22_a_src(data)                                          ((0x00800000&(data))>>23)
#define ISO_UMSK_ISR_GPA0_get_int22_a(data)                                          ((0x00800000&(data))>>23)
#define ISO_UMSK_ISR_GPA0_int21_a_shift                                              (22)
#define ISO_UMSK_ISR_GPA0_int21_a_mask                                               (0x00400000)
#define ISO_UMSK_ISR_GPA0_int21_a(data)                                              (0x00400000&((data)<<22))
#define ISO_UMSK_ISR_GPA0_int21_a_src(data)                                          ((0x00400000&(data))>>22)
#define ISO_UMSK_ISR_GPA0_get_int21_a(data)                                          ((0x00400000&(data))>>22)
#define ISO_UMSK_ISR_GPA0_int20_a_shift                                              (21)
#define ISO_UMSK_ISR_GPA0_int20_a_mask                                               (0x00200000)
#define ISO_UMSK_ISR_GPA0_int20_a(data)                                              (0x00200000&((data)<<21))
#define ISO_UMSK_ISR_GPA0_int20_a_src(data)                                          ((0x00200000&(data))>>21)
#define ISO_UMSK_ISR_GPA0_get_int20_a(data)                                          ((0x00200000&(data))>>21)
#define ISO_UMSK_ISR_GPA0_int19_a_shift                                              (20)
#define ISO_UMSK_ISR_GPA0_int19_a_mask                                               (0x00100000)
#define ISO_UMSK_ISR_GPA0_int19_a(data)                                              (0x00100000&((data)<<20))
#define ISO_UMSK_ISR_GPA0_int19_a_src(data)                                          ((0x00100000&(data))>>20)
#define ISO_UMSK_ISR_GPA0_get_int19_a(data)                                          ((0x00100000&(data))>>20)
#define ISO_UMSK_ISR_GPA0_int18_a_shift                                              (19)
#define ISO_UMSK_ISR_GPA0_int18_a_mask                                               (0x00080000)
#define ISO_UMSK_ISR_GPA0_int18_a(data)                                              (0x00080000&((data)<<19))
#define ISO_UMSK_ISR_GPA0_int18_a_src(data)                                          ((0x00080000&(data))>>19)
#define ISO_UMSK_ISR_GPA0_get_int18_a(data)                                          ((0x00080000&(data))>>19)
#define ISO_UMSK_ISR_GPA0_int17_a_shift                                              (18)
#define ISO_UMSK_ISR_GPA0_int17_a_mask                                               (0x00040000)
#define ISO_UMSK_ISR_GPA0_int17_a(data)                                              (0x00040000&((data)<<18))
#define ISO_UMSK_ISR_GPA0_int17_a_src(data)                                          ((0x00040000&(data))>>18)
#define ISO_UMSK_ISR_GPA0_get_int17_a(data)                                          ((0x00040000&(data))>>18)
#define ISO_UMSK_ISR_GPA0_int16_a_shift                                              (17)
#define ISO_UMSK_ISR_GPA0_int16_a_mask                                               (0x00020000)
#define ISO_UMSK_ISR_GPA0_int16_a(data)                                              (0x00020000&((data)<<17))
#define ISO_UMSK_ISR_GPA0_int16_a_src(data)                                          ((0x00020000&(data))>>17)
#define ISO_UMSK_ISR_GPA0_get_int16_a(data)                                          ((0x00020000&(data))>>17)
#define ISO_UMSK_ISR_GPA0_int15_a_shift                                              (16)
#define ISO_UMSK_ISR_GPA0_int15_a_mask                                               (0x00010000)
#define ISO_UMSK_ISR_GPA0_int15_a(data)                                              (0x00010000&((data)<<16))
#define ISO_UMSK_ISR_GPA0_int15_a_src(data)                                          ((0x00010000&(data))>>16)
#define ISO_UMSK_ISR_GPA0_get_int15_a(data)                                          ((0x00010000&(data))>>16)
#define ISO_UMSK_ISR_GPA0_int14_a_shift                                              (15)
#define ISO_UMSK_ISR_GPA0_int14_a_mask                                               (0x00008000)
#define ISO_UMSK_ISR_GPA0_int14_a(data)                                              (0x00008000&((data)<<15))
#define ISO_UMSK_ISR_GPA0_int14_a_src(data)                                          ((0x00008000&(data))>>15)
#define ISO_UMSK_ISR_GPA0_get_int14_a(data)                                          ((0x00008000&(data))>>15)
#define ISO_UMSK_ISR_GPA0_int13_a_shift                                              (14)
#define ISO_UMSK_ISR_GPA0_int13_a_mask                                               (0x00004000)
#define ISO_UMSK_ISR_GPA0_int13_a(data)                                              (0x00004000&((data)<<14))
#define ISO_UMSK_ISR_GPA0_int13_a_src(data)                                          ((0x00004000&(data))>>14)
#define ISO_UMSK_ISR_GPA0_get_int13_a(data)                                          ((0x00004000&(data))>>14)
#define ISO_UMSK_ISR_GPA0_int12_a_shift                                              (13)
#define ISO_UMSK_ISR_GPA0_int12_a_mask                                               (0x00002000)
#define ISO_UMSK_ISR_GPA0_int12_a(data)                                              (0x00002000&((data)<<13))
#define ISO_UMSK_ISR_GPA0_int12_a_src(data)                                          ((0x00002000&(data))>>13)
#define ISO_UMSK_ISR_GPA0_get_int12_a(data)                                          ((0x00002000&(data))>>13)
#define ISO_UMSK_ISR_GPA0_int11_a_shift                                              (12)
#define ISO_UMSK_ISR_GPA0_int11_a_mask                                               (0x00001000)
#define ISO_UMSK_ISR_GPA0_int11_a(data)                                              (0x00001000&((data)<<12))
#define ISO_UMSK_ISR_GPA0_int11_a_src(data)                                          ((0x00001000&(data))>>12)
#define ISO_UMSK_ISR_GPA0_get_int11_a(data)                                          ((0x00001000&(data))>>12)
#define ISO_UMSK_ISR_GPA0_int10_a_shift                                              (11)
#define ISO_UMSK_ISR_GPA0_int10_a_mask                                               (0x00000800)
#define ISO_UMSK_ISR_GPA0_int10_a(data)                                              (0x00000800&((data)<<11))
#define ISO_UMSK_ISR_GPA0_int10_a_src(data)                                          ((0x00000800&(data))>>11)
#define ISO_UMSK_ISR_GPA0_get_int10_a(data)                                          ((0x00000800&(data))>>11)
#define ISO_UMSK_ISR_GPA0_int9_a_shift                                               (10)
#define ISO_UMSK_ISR_GPA0_int9_a_mask                                                (0x00000400)
#define ISO_UMSK_ISR_GPA0_int9_a(data)                                               (0x00000400&((data)<<10))
#define ISO_UMSK_ISR_GPA0_int9_a_src(data)                                           ((0x00000400&(data))>>10)
#define ISO_UMSK_ISR_GPA0_get_int9_a(data)                                           ((0x00000400&(data))>>10)
#define ISO_UMSK_ISR_GPA0_int8_a_shift                                               (9)
#define ISO_UMSK_ISR_GPA0_int8_a_mask                                                (0x00000200)
#define ISO_UMSK_ISR_GPA0_int8_a(data)                                               (0x00000200&((data)<<9))
#define ISO_UMSK_ISR_GPA0_int8_a_src(data)                                           ((0x00000200&(data))>>9)
#define ISO_UMSK_ISR_GPA0_get_int8_a(data)                                           ((0x00000200&(data))>>9)
#define ISO_UMSK_ISR_GPA0_int7_a_shift                                               (8)
#define ISO_UMSK_ISR_GPA0_int7_a_mask                                                (0x00000100)
#define ISO_UMSK_ISR_GPA0_int7_a(data)                                               (0x00000100&((data)<<8))
#define ISO_UMSK_ISR_GPA0_int7_a_src(data)                                           ((0x00000100&(data))>>8)
#define ISO_UMSK_ISR_GPA0_get_int7_a(data)                                           ((0x00000100&(data))>>8)
#define ISO_UMSK_ISR_GPA0_int6_a_shift                                               (7)
#define ISO_UMSK_ISR_GPA0_int6_a_mask                                                (0x00000080)
#define ISO_UMSK_ISR_GPA0_int6_a(data)                                               (0x00000080&((data)<<7))
#define ISO_UMSK_ISR_GPA0_int6_a_src(data)                                           ((0x00000080&(data))>>7)
#define ISO_UMSK_ISR_GPA0_get_int6_a(data)                                           ((0x00000080&(data))>>7)
#define ISO_UMSK_ISR_GPA0_int5_a_shift                                               (6)
#define ISO_UMSK_ISR_GPA0_int5_a_mask                                                (0x00000040)
#define ISO_UMSK_ISR_GPA0_int5_a(data)                                               (0x00000040&((data)<<6))
#define ISO_UMSK_ISR_GPA0_int5_a_src(data)                                           ((0x00000040&(data))>>6)
#define ISO_UMSK_ISR_GPA0_get_int5_a(data)                                           ((0x00000040&(data))>>6)
#define ISO_UMSK_ISR_GPA0_int4_a_shift                                               (5)
#define ISO_UMSK_ISR_GPA0_int4_a_mask                                                (0x00000020)
#define ISO_UMSK_ISR_GPA0_int4_a(data)                                               (0x00000020&((data)<<5))
#define ISO_UMSK_ISR_GPA0_int4_a_src(data)                                           ((0x00000020&(data))>>5)
#define ISO_UMSK_ISR_GPA0_get_int4_a(data)                                           ((0x00000020&(data))>>5)
#define ISO_UMSK_ISR_GPA0_int3_a_shift                                               (4)
#define ISO_UMSK_ISR_GPA0_int3_a_mask                                                (0x00000010)
#define ISO_UMSK_ISR_GPA0_int3_a(data)                                               (0x00000010&((data)<<4))
#define ISO_UMSK_ISR_GPA0_int3_a_src(data)                                           ((0x00000010&(data))>>4)
#define ISO_UMSK_ISR_GPA0_get_int3_a(data)                                           ((0x00000010&(data))>>4)
#define ISO_UMSK_ISR_GPA0_int2_a_shift                                               (3)
#define ISO_UMSK_ISR_GPA0_int2_a_mask                                                (0x00000008)
#define ISO_UMSK_ISR_GPA0_int2_a(data)                                               (0x00000008&((data)<<3))
#define ISO_UMSK_ISR_GPA0_int2_a_src(data)                                           ((0x00000008&(data))>>3)
#define ISO_UMSK_ISR_GPA0_get_int2_a(data)                                           ((0x00000008&(data))>>3)
#define ISO_UMSK_ISR_GPA0_int1_a_shift                                               (2)
#define ISO_UMSK_ISR_GPA0_int1_a_mask                                                (0x00000004)
#define ISO_UMSK_ISR_GPA0_int1_a(data)                                               (0x00000004&((data)<<2))
#define ISO_UMSK_ISR_GPA0_int1_a_src(data)                                           ((0x00000004&(data))>>2)
#define ISO_UMSK_ISR_GPA0_get_int1_a(data)                                           ((0x00000004&(data))>>2)
#define ISO_UMSK_ISR_GPA0_int0_a_shift                                               (1)
#define ISO_UMSK_ISR_GPA0_int0_a_mask                                                (0x00000002)
#define ISO_UMSK_ISR_GPA0_int0_a(data)                                               (0x00000002&((data)<<1))
#define ISO_UMSK_ISR_GPA0_int0_a_src(data)                                           ((0x00000002&(data))>>1)
#define ISO_UMSK_ISR_GPA0_get_int0_a(data)                                           ((0x00000002&(data))>>1)
#define ISO_UMSK_ISR_GPA0_write_data_shift                                           (0)
#define ISO_UMSK_ISR_GPA0_write_data_mask                                            (0x00000001)
#define ISO_UMSK_ISR_GPA0_write_data(data)                                           (0x00000001&((data)<<0))
#define ISO_UMSK_ISR_GPA0_write_data_src(data)                                       ((0x00000001&(data))>>0)
#define ISO_UMSK_ISR_GPA0_get_write_data(data)                                       ((0x00000001&(data))>>0)


#define ISO_UMSK_ISR_GPDA0                                                           0x9800700C
#define ISO_UMSK_ISR_GPDA0_reg_addr                                                  "0x9800700C"
#define ISO_UMSK_ISR_GPDA0_reg                                                       0x9800700C
#define set_ISO_UMSK_ISR_GPDA0_reg(data)   (*((volatile unsigned int*) ISO_UMSK_ISR_GPDA0_reg)=data)
#define get_ISO_UMSK_ISR_GPDA0_reg   (*((volatile unsigned int*) ISO_UMSK_ISR_GPDA0_reg))
#define ISO_UMSK_ISR_GPDA0_inst_adr                                                  "0x0003"
#define ISO_UMSK_ISR_GPDA0_inst                                                      0x0003
#define ISO_UMSK_ISR_GPDA0_int30_da_shift                                            (31)
#define ISO_UMSK_ISR_GPDA0_int30_da_mask                                             (0x80000000)
#define ISO_UMSK_ISR_GPDA0_int30_da(data)                                            (0x80000000&((data)<<31))
#define ISO_UMSK_ISR_GPDA0_int30_da_src(data)                                        ((0x80000000&(data))>>31)
#define ISO_UMSK_ISR_GPDA0_get_int30_da(data)                                        ((0x80000000&(data))>>31)
#define ISO_UMSK_ISR_GPDA0_int29_da_shift                                            (30)
#define ISO_UMSK_ISR_GPDA0_int29_da_mask                                             (0x40000000)
#define ISO_UMSK_ISR_GPDA0_int29_da(data)                                            (0x40000000&((data)<<30))
#define ISO_UMSK_ISR_GPDA0_int29_da_src(data)                                        ((0x40000000&(data))>>30)
#define ISO_UMSK_ISR_GPDA0_get_int29_da(data)                                        ((0x40000000&(data))>>30)
#define ISO_UMSK_ISR_GPDA0_int28_da_shift                                            (29)
#define ISO_UMSK_ISR_GPDA0_int28_da_mask                                             (0x20000000)
#define ISO_UMSK_ISR_GPDA0_int28_da(data)                                            (0x20000000&((data)<<29))
#define ISO_UMSK_ISR_GPDA0_int28_da_src(data)                                        ((0x20000000&(data))>>29)
#define ISO_UMSK_ISR_GPDA0_get_int28_da(data)                                        ((0x20000000&(data))>>29)
#define ISO_UMSK_ISR_GPDA0_int27_da_shift                                            (28)
#define ISO_UMSK_ISR_GPDA0_int27_da_mask                                             (0x10000000)
#define ISO_UMSK_ISR_GPDA0_int27_da(data)                                            (0x10000000&((data)<<28))
#define ISO_UMSK_ISR_GPDA0_int27_da_src(data)                                        ((0x10000000&(data))>>28)
#define ISO_UMSK_ISR_GPDA0_get_int27_da(data)                                        ((0x10000000&(data))>>28)
#define ISO_UMSK_ISR_GPDA0_int26_da_shift                                            (27)
#define ISO_UMSK_ISR_GPDA0_int26_da_mask                                             (0x08000000)
#define ISO_UMSK_ISR_GPDA0_int26_da(data)                                            (0x08000000&((data)<<27))
#define ISO_UMSK_ISR_GPDA0_int26_da_src(data)                                        ((0x08000000&(data))>>27)
#define ISO_UMSK_ISR_GPDA0_get_int26_da(data)                                        ((0x08000000&(data))>>27)
#define ISO_UMSK_ISR_GPDA0_int25_da_shift                                            (26)
#define ISO_UMSK_ISR_GPDA0_int25_da_mask                                             (0x04000000)
#define ISO_UMSK_ISR_GPDA0_int25_da(data)                                            (0x04000000&((data)<<26))
#define ISO_UMSK_ISR_GPDA0_int25_da_src(data)                                        ((0x04000000&(data))>>26)
#define ISO_UMSK_ISR_GPDA0_get_int25_da(data)                                        ((0x04000000&(data))>>26)
#define ISO_UMSK_ISR_GPDA0_int24_da_shift                                            (25)
#define ISO_UMSK_ISR_GPDA0_int24_da_mask                                             (0x02000000)
#define ISO_UMSK_ISR_GPDA0_int24_da(data)                                            (0x02000000&((data)<<25))
#define ISO_UMSK_ISR_GPDA0_int24_da_src(data)                                        ((0x02000000&(data))>>25)
#define ISO_UMSK_ISR_GPDA0_get_int24_da(data)                                        ((0x02000000&(data))>>25)
#define ISO_UMSK_ISR_GPDA0_int23_da_shift                                            (24)
#define ISO_UMSK_ISR_GPDA0_int23_da_mask                                             (0x01000000)
#define ISO_UMSK_ISR_GPDA0_int23_da(data)                                            (0x01000000&((data)<<24))
#define ISO_UMSK_ISR_GPDA0_int23_da_src(data)                                        ((0x01000000&(data))>>24)
#define ISO_UMSK_ISR_GPDA0_get_int23_da(data)                                        ((0x01000000&(data))>>24)
#define ISO_UMSK_ISR_GPDA0_int22_da_shift                                            (23)
#define ISO_UMSK_ISR_GPDA0_int22_da_mask                                             (0x00800000)
#define ISO_UMSK_ISR_GPDA0_int22_da(data)                                            (0x00800000&((data)<<23))
#define ISO_UMSK_ISR_GPDA0_int22_da_src(data)                                        ((0x00800000&(data))>>23)
#define ISO_UMSK_ISR_GPDA0_get_int22_da(data)                                        ((0x00800000&(data))>>23)
#define ISO_UMSK_ISR_GPDA0_int21_da_shift                                            (22)
#define ISO_UMSK_ISR_GPDA0_int21_da_mask                                             (0x00400000)
#define ISO_UMSK_ISR_GPDA0_int21_da(data)                                            (0x00400000&((data)<<22))
#define ISO_UMSK_ISR_GPDA0_int21_da_src(data)                                        ((0x00400000&(data))>>22)
#define ISO_UMSK_ISR_GPDA0_get_int21_da(data)                                        ((0x00400000&(data))>>22)
#define ISO_UMSK_ISR_GPDA0_int20_da_shift                                            (21)
#define ISO_UMSK_ISR_GPDA0_int20_da_mask                                             (0x00200000)
#define ISO_UMSK_ISR_GPDA0_int20_da(data)                                            (0x00200000&((data)<<21))
#define ISO_UMSK_ISR_GPDA0_int20_da_src(data)                                        ((0x00200000&(data))>>21)
#define ISO_UMSK_ISR_GPDA0_get_int20_da(data)                                        ((0x00200000&(data))>>21)
#define ISO_UMSK_ISR_GPDA0_int19_da_shift                                            (20)
#define ISO_UMSK_ISR_GPDA0_int19_da_mask                                             (0x00100000)
#define ISO_UMSK_ISR_GPDA0_int19_da(data)                                            (0x00100000&((data)<<20))
#define ISO_UMSK_ISR_GPDA0_int19_da_src(data)                                        ((0x00100000&(data))>>20)
#define ISO_UMSK_ISR_GPDA0_get_int19_da(data)                                        ((0x00100000&(data))>>20)
#define ISO_UMSK_ISR_GPDA0_int18_da_shift                                            (19)
#define ISO_UMSK_ISR_GPDA0_int18_da_mask                                             (0x00080000)
#define ISO_UMSK_ISR_GPDA0_int18_da(data)                                            (0x00080000&((data)<<19))
#define ISO_UMSK_ISR_GPDA0_int18_da_src(data)                                        ((0x00080000&(data))>>19)
#define ISO_UMSK_ISR_GPDA0_get_int18_da(data)                                        ((0x00080000&(data))>>19)
#define ISO_UMSK_ISR_GPDA0_int17_da_shift                                            (18)
#define ISO_UMSK_ISR_GPDA0_int17_da_mask                                             (0x00040000)
#define ISO_UMSK_ISR_GPDA0_int17_da(data)                                            (0x00040000&((data)<<18))
#define ISO_UMSK_ISR_GPDA0_int17_da_src(data)                                        ((0x00040000&(data))>>18)
#define ISO_UMSK_ISR_GPDA0_get_int17_da(data)                                        ((0x00040000&(data))>>18)
#define ISO_UMSK_ISR_GPDA0_int16_da_shift                                            (17)
#define ISO_UMSK_ISR_GPDA0_int16_da_mask                                             (0x00020000)
#define ISO_UMSK_ISR_GPDA0_int16_da(data)                                            (0x00020000&((data)<<17))
#define ISO_UMSK_ISR_GPDA0_int16_da_src(data)                                        ((0x00020000&(data))>>17)
#define ISO_UMSK_ISR_GPDA0_get_int16_da(data)                                        ((0x00020000&(data))>>17)
#define ISO_UMSK_ISR_GPDA0_int15_da_shift                                            (16)
#define ISO_UMSK_ISR_GPDA0_int15_da_mask                                             (0x00010000)
#define ISO_UMSK_ISR_GPDA0_int15_da(data)                                            (0x00010000&((data)<<16))
#define ISO_UMSK_ISR_GPDA0_int15_da_src(data)                                        ((0x00010000&(data))>>16)
#define ISO_UMSK_ISR_GPDA0_get_int15_da(data)                                        ((0x00010000&(data))>>16)
#define ISO_UMSK_ISR_GPDA0_int14_da_shift                                            (15)
#define ISO_UMSK_ISR_GPDA0_int14_da_mask                                             (0x00008000)
#define ISO_UMSK_ISR_GPDA0_int14_da(data)                                            (0x00008000&((data)<<15))
#define ISO_UMSK_ISR_GPDA0_int14_da_src(data)                                        ((0x00008000&(data))>>15)
#define ISO_UMSK_ISR_GPDA0_get_int14_da(data)                                        ((0x00008000&(data))>>15)
#define ISO_UMSK_ISR_GPDA0_int13_da_shift                                            (14)
#define ISO_UMSK_ISR_GPDA0_int13_da_mask                                             (0x00004000)
#define ISO_UMSK_ISR_GPDA0_int13_da(data)                                            (0x00004000&((data)<<14))
#define ISO_UMSK_ISR_GPDA0_int13_da_src(data)                                        ((0x00004000&(data))>>14)
#define ISO_UMSK_ISR_GPDA0_get_int13_da(data)                                        ((0x00004000&(data))>>14)
#define ISO_UMSK_ISR_GPDA0_int12_da_shift                                            (13)
#define ISO_UMSK_ISR_GPDA0_int12_da_mask                                             (0x00002000)
#define ISO_UMSK_ISR_GPDA0_int12_da(data)                                            (0x00002000&((data)<<13))
#define ISO_UMSK_ISR_GPDA0_int12_da_src(data)                                        ((0x00002000&(data))>>13)
#define ISO_UMSK_ISR_GPDA0_get_int12_da(data)                                        ((0x00002000&(data))>>13)
#define ISO_UMSK_ISR_GPDA0_int11_da_shift                                            (12)
#define ISO_UMSK_ISR_GPDA0_int11_da_mask                                             (0x00001000)
#define ISO_UMSK_ISR_GPDA0_int11_da(data)                                            (0x00001000&((data)<<12))
#define ISO_UMSK_ISR_GPDA0_int11_da_src(data)                                        ((0x00001000&(data))>>12)
#define ISO_UMSK_ISR_GPDA0_get_int11_da(data)                                        ((0x00001000&(data))>>12)
#define ISO_UMSK_ISR_GPDA0_int10_da_shift                                            (11)
#define ISO_UMSK_ISR_GPDA0_int10_da_mask                                             (0x00000800)
#define ISO_UMSK_ISR_GPDA0_int10_da(data)                                            (0x00000800&((data)<<11))
#define ISO_UMSK_ISR_GPDA0_int10_da_src(data)                                        ((0x00000800&(data))>>11)
#define ISO_UMSK_ISR_GPDA0_get_int10_da(data)                                        ((0x00000800&(data))>>11)
#define ISO_UMSK_ISR_GPDA0_int9_da_shift                                             (10)
#define ISO_UMSK_ISR_GPDA0_int9_da_mask                                              (0x00000400)
#define ISO_UMSK_ISR_GPDA0_int9_da(data)                                             (0x00000400&((data)<<10))
#define ISO_UMSK_ISR_GPDA0_int9_da_src(data)                                         ((0x00000400&(data))>>10)
#define ISO_UMSK_ISR_GPDA0_get_int9_da(data)                                         ((0x00000400&(data))>>10)
#define ISO_UMSK_ISR_GPDA0_int8_da_shift                                             (9)
#define ISO_UMSK_ISR_GPDA0_int8_da_mask                                              (0x00000200)
#define ISO_UMSK_ISR_GPDA0_int8_da(data)                                             (0x00000200&((data)<<9))
#define ISO_UMSK_ISR_GPDA0_int8_da_src(data)                                         ((0x00000200&(data))>>9)
#define ISO_UMSK_ISR_GPDA0_get_int8_da(data)                                         ((0x00000200&(data))>>9)
#define ISO_UMSK_ISR_GPDA0_int7_da_shift                                             (8)
#define ISO_UMSK_ISR_GPDA0_int7_da_mask                                              (0x00000100)
#define ISO_UMSK_ISR_GPDA0_int7_da(data)                                             (0x00000100&((data)<<8))
#define ISO_UMSK_ISR_GPDA0_int7_da_src(data)                                         ((0x00000100&(data))>>8)
#define ISO_UMSK_ISR_GPDA0_get_int7_da(data)                                         ((0x00000100&(data))>>8)
#define ISO_UMSK_ISR_GPDA0_int6_da_shift                                             (7)
#define ISO_UMSK_ISR_GPDA0_int6_da_mask                                              (0x00000080)
#define ISO_UMSK_ISR_GPDA0_int6_da(data)                                             (0x00000080&((data)<<7))
#define ISO_UMSK_ISR_GPDA0_int6_da_src(data)                                         ((0x00000080&(data))>>7)
#define ISO_UMSK_ISR_GPDA0_get_int6_da(data)                                         ((0x00000080&(data))>>7)
#define ISO_UMSK_ISR_GPDA0_int5_da_shift                                             (6)
#define ISO_UMSK_ISR_GPDA0_int5_da_mask                                              (0x00000040)
#define ISO_UMSK_ISR_GPDA0_int5_da(data)                                             (0x00000040&((data)<<6))
#define ISO_UMSK_ISR_GPDA0_int5_da_src(data)                                         ((0x00000040&(data))>>6)
#define ISO_UMSK_ISR_GPDA0_get_int5_da(data)                                         ((0x00000040&(data))>>6)
#define ISO_UMSK_ISR_GPDA0_int4_da_shift                                             (5)
#define ISO_UMSK_ISR_GPDA0_int4_da_mask                                              (0x00000020)
#define ISO_UMSK_ISR_GPDA0_int4_da(data)                                             (0x00000020&((data)<<5))
#define ISO_UMSK_ISR_GPDA0_int4_da_src(data)                                         ((0x00000020&(data))>>5)
#define ISO_UMSK_ISR_GPDA0_get_int4_da(data)                                         ((0x00000020&(data))>>5)
#define ISO_UMSK_ISR_GPDA0_int3_da_shift                                             (4)
#define ISO_UMSK_ISR_GPDA0_int3_da_mask                                              (0x00000010)
#define ISO_UMSK_ISR_GPDA0_int3_da(data)                                             (0x00000010&((data)<<4))
#define ISO_UMSK_ISR_GPDA0_int3_da_src(data)                                         ((0x00000010&(data))>>4)
#define ISO_UMSK_ISR_GPDA0_get_int3_da(data)                                         ((0x00000010&(data))>>4)
#define ISO_UMSK_ISR_GPDA0_int2_da_shift                                             (3)
#define ISO_UMSK_ISR_GPDA0_int2_da_mask                                              (0x00000008)
#define ISO_UMSK_ISR_GPDA0_int2_da(data)                                             (0x00000008&((data)<<3))
#define ISO_UMSK_ISR_GPDA0_int2_da_src(data)                                         ((0x00000008&(data))>>3)
#define ISO_UMSK_ISR_GPDA0_get_int2_da(data)                                         ((0x00000008&(data))>>3)
#define ISO_UMSK_ISR_GPDA0_int1_da_shift                                             (2)
#define ISO_UMSK_ISR_GPDA0_int1_da_mask                                              (0x00000004)
#define ISO_UMSK_ISR_GPDA0_int1_da(data)                                             (0x00000004&((data)<<2))
#define ISO_UMSK_ISR_GPDA0_int1_da_src(data)                                         ((0x00000004&(data))>>2)
#define ISO_UMSK_ISR_GPDA0_get_int1_da(data)                                         ((0x00000004&(data))>>2)
#define ISO_UMSK_ISR_GPDA0_int0_da_shift                                             (1)
#define ISO_UMSK_ISR_GPDA0_int0_da_mask                                              (0x00000002)
#define ISO_UMSK_ISR_GPDA0_int0_da(data)                                             (0x00000002&((data)<<1))
#define ISO_UMSK_ISR_GPDA0_int0_da_src(data)                                         ((0x00000002&(data))>>1)
#define ISO_UMSK_ISR_GPDA0_get_int0_da(data)                                         ((0x00000002&(data))>>1)
#define ISO_UMSK_ISR_GPDA0_write_data_shift                                          (0)
#define ISO_UMSK_ISR_GPDA0_write_data_mask                                           (0x00000001)
#define ISO_UMSK_ISR_GPDA0_write_data(data)                                          (0x00000001&((data)<<0))
#define ISO_UMSK_ISR_GPDA0_write_data_src(data)                                      ((0x00000001&(data))>>0)
#define ISO_UMSK_ISR_GPDA0_get_write_data(data)                                      ((0x00000001&(data))>>0)


#define ISO_UMSK_ISR_GPA1                                                            0x980070E0
#define ISO_UMSK_ISR_GPA1_reg_addr                                                   "0x980070E0"
#define ISO_UMSK_ISR_GPA1_reg                                                        0x980070E0
#define set_ISO_UMSK_ISR_GPA1_reg(data)   (*((volatile unsigned int*) ISO_UMSK_ISR_GPA1_reg)=data)
#define get_ISO_UMSK_ISR_GPA1_reg   (*((volatile unsigned int*) ISO_UMSK_ISR_GPA1_reg))
#define ISO_UMSK_ISR_GPA1_inst_adr                                                   "0x0038"
#define ISO_UMSK_ISR_GPA1_inst                                                       0x0038
#define ISO_UMSK_ISR_GPA1_int34_a_shift                                              (4)
#define ISO_UMSK_ISR_GPA1_int34_a_mask                                               (0x00000010)
#define ISO_UMSK_ISR_GPA1_int34_a(data)                                              (0x00000010&((data)<<4))
#define ISO_UMSK_ISR_GPA1_int34_a_src(data)                                          ((0x00000010&(data))>>4)
#define ISO_UMSK_ISR_GPA1_get_int34_a(data)                                          ((0x00000010&(data))>>4)
#define ISO_UMSK_ISR_GPA1_int33_a_shift                                              (3)
#define ISO_UMSK_ISR_GPA1_int33_a_mask                                               (0x00000008)
#define ISO_UMSK_ISR_GPA1_int33_a(data)                                              (0x00000008&((data)<<3))
#define ISO_UMSK_ISR_GPA1_int33_a_src(data)                                          ((0x00000008&(data))>>3)
#define ISO_UMSK_ISR_GPA1_get_int33_a(data)                                          ((0x00000008&(data))>>3)
#define ISO_UMSK_ISR_GPA1_int32_a_shift                                              (2)
#define ISO_UMSK_ISR_GPA1_int32_a_mask                                               (0x00000004)
#define ISO_UMSK_ISR_GPA1_int32_a(data)                                              (0x00000004&((data)<<2))
#define ISO_UMSK_ISR_GPA1_int32_a_src(data)                                          ((0x00000004&(data))>>2)
#define ISO_UMSK_ISR_GPA1_get_int32_a(data)                                          ((0x00000004&(data))>>2)
#define ISO_UMSK_ISR_GPA1_int31_a_shift                                              (1)
#define ISO_UMSK_ISR_GPA1_int31_a_mask                                               (0x00000002)
#define ISO_UMSK_ISR_GPA1_int31_a(data)                                              (0x00000002&((data)<<1))
#define ISO_UMSK_ISR_GPA1_int31_a_src(data)                                          ((0x00000002&(data))>>1)
#define ISO_UMSK_ISR_GPA1_get_int31_a(data)                                          ((0x00000002&(data))>>1)
#define ISO_UMSK_ISR_GPA1_write_data_shift                                           (0)
#define ISO_UMSK_ISR_GPA1_write_data_mask                                            (0x00000001)
#define ISO_UMSK_ISR_GPA1_write_data(data)                                           (0x00000001&((data)<<0))
#define ISO_UMSK_ISR_GPA1_write_data_src(data)                                       ((0x00000001&(data))>>0)
#define ISO_UMSK_ISR_GPA1_get_write_data(data)                                       ((0x00000001&(data))>>0)


#define ISO_UMSK_ISR_GPDA1                                                           0x980070E4
#define ISO_UMSK_ISR_GPDA1_reg_addr                                                  "0x980070E4"
#define ISO_UMSK_ISR_GPDA1_reg                                                       0x980070E4
#define set_ISO_UMSK_ISR_GPDA1_reg(data)   (*((volatile unsigned int*) ISO_UMSK_ISR_GPDA1_reg)=data)
#define get_ISO_UMSK_ISR_GPDA1_reg   (*((volatile unsigned int*) ISO_UMSK_ISR_GPDA1_reg))
#define ISO_UMSK_ISR_GPDA1_inst_adr                                                  "0x0039"
#define ISO_UMSK_ISR_GPDA1_inst                                                      0x0039
#define ISO_UMSK_ISR_GPDA1_int34_da_shift                                            (4)
#define ISO_UMSK_ISR_GPDA1_int34_da_mask                                             (0x00000010)
#define ISO_UMSK_ISR_GPDA1_int34_da(data)                                            (0x00000010&((data)<<4))
#define ISO_UMSK_ISR_GPDA1_int34_da_src(data)                                        ((0x00000010&(data))>>4)
#define ISO_UMSK_ISR_GPDA1_get_int34_da(data)                                        ((0x00000010&(data))>>4)
#define ISO_UMSK_ISR_GPDA1_int33_da_shift                                            (3)
#define ISO_UMSK_ISR_GPDA1_int33_da_mask                                             (0x00000008)
#define ISO_UMSK_ISR_GPDA1_int33_da(data)                                            (0x00000008&((data)<<3))
#define ISO_UMSK_ISR_GPDA1_int33_da_src(data)                                        ((0x00000008&(data))>>3)
#define ISO_UMSK_ISR_GPDA1_get_int33_da(data)                                        ((0x00000008&(data))>>3)
#define ISO_UMSK_ISR_GPDA1_int32_da_shift                                            (2)
#define ISO_UMSK_ISR_GPDA1_int32_da_mask                                             (0x00000004)
#define ISO_UMSK_ISR_GPDA1_int32_da(data)                                            (0x00000004&((data)<<2))
#define ISO_UMSK_ISR_GPDA1_int32_da_src(data)                                        ((0x00000004&(data))>>2)
#define ISO_UMSK_ISR_GPDA1_get_int32_da(data)                                        ((0x00000004&(data))>>2)
#define ISO_UMSK_ISR_GPDA1_int31_da_shift                                            (1)
#define ISO_UMSK_ISR_GPDA1_int31_da_mask                                             (0x00000002)
#define ISO_UMSK_ISR_GPDA1_int31_da(data)                                            (0x00000002&((data)<<1))
#define ISO_UMSK_ISR_GPDA1_int31_da_src(data)                                        ((0x00000002&(data))>>1)
#define ISO_UMSK_ISR_GPDA1_get_int31_da(data)                                        ((0x00000002&(data))>>1)
#define ISO_UMSK_ISR_GPDA1_write_data_shift                                          (0)
#define ISO_UMSK_ISR_GPDA1_write_data_mask                                           (0x00000001)
#define ISO_UMSK_ISR_GPDA1_write_data(data)                                          (0x00000001&((data)<<0))
#define ISO_UMSK_ISR_GPDA1_write_data_src(data)                                      ((0x00000001&(data))>>0)
#define ISO_UMSK_ISR_GPDA1_get_write_data(data)                                      ((0x00000001&(data))>>0)


#define ISO_FAST_INT_EN_0                                                            0x98007010
#define ISO_FAST_INT_EN_0_reg_addr                                                   "0x98007010"
#define ISO_FAST_INT_EN_0_reg                                                        0x98007010
#define set_ISO_FAST_INT_EN_0_reg(data)   (*((volatile unsigned int*) ISO_FAST_INT_EN_0_reg)=data)
#define get_ISO_FAST_INT_EN_0_reg   (*((volatile unsigned int*) ISO_FAST_INT_EN_0_reg))
#define ISO_FAST_INT_EN_0_inst_adr                                                   "0x0004"
#define ISO_FAST_INT_EN_0_inst                                                       0x0004
#define ISO_FAST_INT_EN_0_gp_int_shift                                               (1)
#define ISO_FAST_INT_EN_0_gp_int_mask                                                (0xFFFFFFFE)
#define ISO_FAST_INT_EN_0_gp_int(data)                                               (0xFFFFFFFE&((data)<<1))
#define ISO_FAST_INT_EN_0_gp_int_src(data)                                           ((0xFFFFFFFE&(data))>>1)
#define ISO_FAST_INT_EN_0_get_gp_int(data)                                           ((0xFFFFFFFE&(data))>>1)


#define ISO_FAST_INT_EN_1                                                            0x98007014
#define ISO_FAST_INT_EN_1_reg_addr                                                   "0x98007014"
#define ISO_FAST_INT_EN_1_reg                                                        0x98007014
#define set_ISO_FAST_INT_EN_1_reg(data)   (*((volatile unsigned int*) ISO_FAST_INT_EN_1_reg)=data)
#define get_ISO_FAST_INT_EN_1_reg   (*((volatile unsigned int*) ISO_FAST_INT_EN_1_reg))
#define ISO_FAST_INT_EN_1_inst_adr                                                   "0x0005"
#define ISO_FAST_INT_EN_1_inst                                                       0x0005
#define ISO_FAST_INT_EN_1_gp_int_shift                                               (1)
#define ISO_FAST_INT_EN_1_gp_int_mask                                                (0x0000001E)
#define ISO_FAST_INT_EN_1_gp_int(data)                                               (0x0000001E&((data)<<1))
#define ISO_FAST_INT_EN_1_gp_int_src(data)                                           ((0x0000001E&(data))>>1)
#define ISO_FAST_INT_EN_1_get_gp_int(data)                                           ((0x0000001E&(data))>>1)


#define ISO_FAST_ISR                                                                 0x98007018
#define ISO_FAST_ISR_reg_addr                                                        "0x98007018"
#define ISO_FAST_ISR_reg                                                             0x98007018
#define set_ISO_FAST_ISR_reg(data)   (*((volatile unsigned int*) ISO_FAST_ISR_reg)=data)
#define get_ISO_FAST_ISR_reg   (*((volatile unsigned int*) ISO_FAST_ISR_reg))
#define ISO_FAST_ISR_inst_adr                                                        "0x0006"
#define ISO_FAST_ISR_inst                                                            0x0006
#define ISO_FAST_ISR_gpioda_int_shift                                                (2)
#define ISO_FAST_ISR_gpioda_int_mask                                                 (0x00000004)
#define ISO_FAST_ISR_gpioda_int(data)                                                (0x00000004&((data)<<2))
#define ISO_FAST_ISR_gpioda_int_src(data)                                            ((0x00000004&(data))>>2)
#define ISO_FAST_ISR_get_gpioda_int(data)                                            ((0x00000004&(data))>>2)
#define ISO_FAST_ISR_gpioa_int_shift                                                 (1)
#define ISO_FAST_ISR_gpioa_int_mask                                                  (0x00000002)
#define ISO_FAST_ISR_gpioa_int(data)                                                 (0x00000002&((data)<<1))
#define ISO_FAST_ISR_gpioa_int_src(data)                                             ((0x00000002&(data))>>1)
#define ISO_FAST_ISR_get_gpioa_int(data)                                             ((0x00000002&(data))>>1)
#define ISO_FAST_ISR_write_data_shift                                                (0)
#define ISO_FAST_ISR_write_data_mask                                                 (0x00000001)
#define ISO_FAST_ISR_write_data(data)                                                (0x00000001&((data)<<0))
#define ISO_FAST_ISR_write_data_src(data)                                            ((0x00000001&(data))>>0)
#define ISO_FAST_ISR_get_write_data(data)                                            ((0x00000001&(data))>>0)


#define ISO_RESERVED_USE_3                                                           0x9800701C
#define ISO_RESERVED_USE_3_reg_addr                                                  "0x9800701C"
#define ISO_RESERVED_USE_3_reg                                                       0x9800701C
#define set_ISO_RESERVED_USE_3_reg(data)   (*((volatile unsigned int*) ISO_RESERVED_USE_3_reg)=data)
#define get_ISO_RESERVED_USE_3_reg   (*((volatile unsigned int*) ISO_RESERVED_USE_3_reg))
#define ISO_RESERVED_USE_3_inst_adr                                                  "0x0007"
#define ISO_RESERVED_USE_3_inst                                                      0x0007
#define ISO_RESERVED_USE_3_dmy_shift                                                 (0)
#define ISO_RESERVED_USE_3_dmy_mask                                                  (0xFFFFFFFF)
#define ISO_RESERVED_USE_3_dmy(data)                                                 (0xFFFFFFFF&((data)<<0))
#define ISO_RESERVED_USE_3_dmy_src(data)                                             ((0xFFFFFFFF&(data))>>0)
#define ISO_RESERVED_USE_3_get_dmy(data)                                             ((0xFFFFFFFF&(data))>>0)


#define ISO_REG_DBG                                                                  0x98007020
#define ISO_REG_DBG_reg_addr                                                         "0x98007020"
#define ISO_REG_DBG_reg                                                              0x98007020
#define set_ISO_REG_DBG_reg(data)   (*((volatile unsigned int*) ISO_REG_DBG_reg)=data)
#define get_ISO_REG_DBG_reg   (*((volatile unsigned int*) ISO_REG_DBG_reg))
#define ISO_REG_DBG_inst_adr                                                         "0x0008"
#define ISO_REG_DBG_inst                                                             0x0008
#define ISO_REG_DBG_write_en2_shift                                                  (11)
#define ISO_REG_DBG_write_en2_mask                                                   (0x00000800)
#define ISO_REG_DBG_write_en2(data)                                                  (0x00000800&((data)<<11))
#define ISO_REG_DBG_write_en2_src(data)                                              ((0x00000800&(data))>>11)
#define ISO_REG_DBG_get_write_en2(data)                                              ((0x00000800&(data))>>11)
#define ISO_REG_DBG_sel_shift                                                        (4)
#define ISO_REG_DBG_sel_mask                                                         (0x000001F0)
#define ISO_REG_DBG_sel(data)                                                        (0x000001F0&((data)<<4))
#define ISO_REG_DBG_sel_src(data)                                                    ((0x000001F0&(data))>>4)
#define ISO_REG_DBG_get_sel(data)                                                    ((0x000001F0&(data))>>4)
#define ISO_REG_DBG_write_en1_shift                                                  (3)
#define ISO_REG_DBG_write_en1_mask                                                   (0x00000008)
#define ISO_REG_DBG_write_en1(data)                                                  (0x00000008&((data)<<3))
#define ISO_REG_DBG_write_en1_src(data)                                              ((0x00000008&(data))>>3)
#define ISO_REG_DBG_get_write_en1(data)                                              ((0x00000008&(data))>>3)
#define ISO_REG_DBG_enable_shift                                                     (0)
#define ISO_REG_DBG_enable_mask                                                      (0x00000001)
#define ISO_REG_DBG_enable(data)                                                     (0x00000001&((data)<<0))
#define ISO_REG_DBG_enable_src(data)                                                 ((0x00000001&(data))>>0)
#define ISO_REG_DBG_get_enable(data)                                                 ((0x00000001&(data))>>0)


#define ISO_DBG                                                                      0x98007024
#define ISO_DBG_reg_addr                                                             "0x98007024"
#define ISO_DBG_reg                                                                  0x98007024
#define set_ISO_DBG_reg(data)   (*((volatile unsigned int*) ISO_DBG_reg)=data)
#define get_ISO_DBG_reg   (*((volatile unsigned int*) ISO_DBG_reg))
#define ISO_DBG_inst_adr                                                             "0x0009"
#define ISO_DBG_inst                                                                 0x0009
#define ISO_DBG_write_en5_shift                                                      (31)
#define ISO_DBG_write_en5_mask                                                       (0x80000000)
#define ISO_DBG_write_en5(data)                                                      (0x80000000&((data)<<31))
#define ISO_DBG_write_en5_src(data)                                                  ((0x80000000&(data))>>31)
#define ISO_DBG_get_write_en5(data)                                                  ((0x80000000&(data))>>31)
#define ISO_DBG_standby_dbg_sel_shift                                                (24)
#define ISO_DBG_standby_dbg_sel_mask                                                 (0x7F000000)
#define ISO_DBG_standby_dbg_sel(data)                                                (0x7F000000&((data)<<24))
#define ISO_DBG_standby_dbg_sel_src(data)                                            ((0x7F000000&(data))>>24)
#define ISO_DBG_get_standby_dbg_sel(data)                                            ((0x7F000000&(data))>>24)
#define ISO_DBG_write_en4_shift                                                      (23)
#define ISO_DBG_write_en4_mask                                                       (0x00800000)
#define ISO_DBG_write_en4(data)                                                      (0x00800000&((data)<<23))
#define ISO_DBG_write_en4_src(data)                                                  ((0x00800000&(data))>>23)
#define ISO_DBG_get_write_en4(data)                                                  ((0x00800000&(data))>>23)
#define ISO_DBG_standby_dbg_en_shift                                                 (20)
#define ISO_DBG_standby_dbg_en_mask                                                  (0x00100000)
#define ISO_DBG_standby_dbg_en(data)                                                 (0x00100000&((data)<<20))
#define ISO_DBG_standby_dbg_en_src(data)                                             ((0x00100000&(data))>>20)
#define ISO_DBG_get_standby_dbg_en(data)                                             ((0x00100000&(data))>>20)
#define ISO_DBG_write_en3_shift                                                      (19)
#define ISO_DBG_write_en3_mask                                                       (0x00080000)
#define ISO_DBG_write_en3(data)                                                      (0x00080000&((data)<<19))
#define ISO_DBG_write_en3_src(data)                                                  ((0x00080000&(data))>>19)
#define ISO_DBG_get_write_en3(data)                                                  ((0x00080000&(data))>>19)
#define ISO_DBG_sel1_shift                                                           (12)
#define ISO_DBG_sel1_mask                                                            (0x0000F000)
#define ISO_DBG_sel1(data)                                                           (0x0000F000&((data)<<12))
#define ISO_DBG_sel1_src(data)                                                       ((0x0000F000&(data))>>12)
#define ISO_DBG_get_sel1(data)                                                       ((0x0000F000&(data))>>12)
#define ISO_DBG_write_en2_shift                                                      (11)
#define ISO_DBG_write_en2_mask                                                       (0x00000800)
#define ISO_DBG_write_en2(data)                                                      (0x00000800&((data)<<11))
#define ISO_DBG_write_en2_src(data)                                                  ((0x00000800&(data))>>11)
#define ISO_DBG_get_write_en2(data)                                                  ((0x00000800&(data))>>11)
#define ISO_DBG_sel0_shift                                                           (4)
#define ISO_DBG_sel0_mask                                                            (0x000000F0)
#define ISO_DBG_sel0(data)                                                           (0x000000F0&((data)<<4))
#define ISO_DBG_sel0_src(data)                                                       ((0x000000F0&(data))>>4)
#define ISO_DBG_get_sel0(data)                                                       ((0x000000F0&(data))>>4)
#define ISO_DBG_write_en1_shift                                                      (3)
#define ISO_DBG_write_en1_mask                                                       (0x00000008)
#define ISO_DBG_write_en1(data)                                                      (0x00000008&((data)<<3))
#define ISO_DBG_write_en1_src(data)                                                  ((0x00000008&(data))>>3)
#define ISO_DBG_get_write_en1(data)                                                  ((0x00000008&(data))>>3)
#define ISO_DBG_enable_shift                                                         (0)
#define ISO_DBG_enable_mask                                                          (0x00000001)
#define ISO_DBG_enable(data)                                                         (0x00000001&((data)<<0))
#define ISO_DBG_enable_src(data)                                                     ((0x00000001&(data))>>0)
#define ISO_DBG_get_enable(data)                                                     ((0x00000001&(data))>>0)


#define ISO_CHIP_INFO1                                                               0x98007028
#define ISO_CHIP_INFO1_reg_addr                                                      "0x98007028"
#define ISO_CHIP_INFO1_reg                                                           0x98007028
#define set_ISO_CHIP_INFO1_reg(data)   (*((volatile unsigned int*) ISO_CHIP_INFO1_reg)=data)
#define get_ISO_CHIP_INFO1_reg   (*((volatile unsigned int*) ISO_CHIP_INFO1_reg))
#define ISO_CHIP_INFO1_inst_adr                                                      "0x000A"
#define ISO_CHIP_INFO1_inst                                                          0x000A
#define ISO_CHIP_INFO1_testmode_shift                                                (15)
#define ISO_CHIP_INFO1_testmode_mask                                                 (0x00008000)
#define ISO_CHIP_INFO1_testmode(data)                                                (0x00008000&((data)<<15))
#define ISO_CHIP_INFO1_testmode_src(data)                                            ((0x00008000&(data))>>15)
#define ISO_CHIP_INFO1_get_testmode(data)                                            ((0x00008000&(data))>>15)
#define ISO_CHIP_INFO1_boot_sel_shift                                                (14)
#define ISO_CHIP_INFO1_boot_sel_mask                                                 (0x00004000)
#define ISO_CHIP_INFO1_boot_sel(data)                                                (0x00004000&((data)<<14))
#define ISO_CHIP_INFO1_boot_sel_src(data)                                            ((0x00004000&(data))>>14)
#define ISO_CHIP_INFO1_get_boot_sel(data)                                            ((0x00004000&(data))>>14)
#define ISO_CHIP_INFO1_bound_opt_shift                                               (0)
#define ISO_CHIP_INFO1_bound_opt_mask                                                (0x00003FFF)
#define ISO_CHIP_INFO1_bound_opt(data)                                               (0x00003FFF&((data)<<0))
#define ISO_CHIP_INFO1_bound_opt_src(data)                                           ((0x00003FFF&(data))>>0)
#define ISO_CHIP_INFO1_get_bound_opt(data)                                           ((0x00003FFF&(data))>>0)


#define ISO_CHIP_INFO2                                                               0x9800702C
#define ISO_CHIP_INFO2_reg_addr                                                      "0x9800702C"
#define ISO_CHIP_INFO2_reg                                                           0x9800702C
#define set_ISO_CHIP_INFO2_reg(data)   (*((volatile unsigned int*) ISO_CHIP_INFO2_reg)=data)
#define get_ISO_CHIP_INFO2_reg   (*((volatile unsigned int*) ISO_CHIP_INFO2_reg))
#define ISO_CHIP_INFO2_inst_adr                                                      "0x000B"
#define ISO_CHIP_INFO2_inst                                                          0x000B
#define ISO_CHIP_INFO2_pow_latch_shift                                               (0)
#define ISO_CHIP_INFO2_pow_latch_mask                                                (0x03FFFFFF)
#define ISO_CHIP_INFO2_pow_latch(data)                                               (0x03FFFFFF&((data)<<0))
#define ISO_CHIP_INFO2_pow_latch_src(data)                                           ((0x03FFFFFF&(data))>>0)
#define ISO_CHIP_INFO2_get_pow_latch(data)                                           ((0x03FFFFFF&(data))>>0)


#define ISO_CHIP_INFO3                                                               0x98007340
#define ISO_CHIP_INFO3_reg_addr                                                      "0x98007340"
#define ISO_CHIP_INFO3_reg                                                           0x98007340
#define set_ISO_CHIP_INFO3_reg(data)   (*((volatile unsigned int*) ISO_CHIP_INFO3_reg)=data)
#define get_ISO_CHIP_INFO3_reg   (*((volatile unsigned int*) ISO_CHIP_INFO3_reg))
#define ISO_CHIP_INFO3_inst_adr                                                      "0x00D0"
#define ISO_CHIP_INFO3_inst                                                          0x00D0
#define ISO_CHIP_INFO3_pow_latch_ori_shift                                           (0)
#define ISO_CHIP_INFO3_pow_latch_ori_mask                                            (0x03FFFFFF)
#define ISO_CHIP_INFO3_pow_latch_ori(data)                                           (0x03FFFFFF&((data)<<0))
#define ISO_CHIP_INFO3_pow_latch_ori_src(data)                                       ((0x03FFFFFF&(data))>>0)
#define ISO_CHIP_INFO3_get_pow_latch_ori(data)                                       ((0x03FFFFFF&(data))>>0)


#define ISO_CTRL                                                                     0x98007030
#define ISO_CTRL_reg_addr                                                            "0x98007030"
#define ISO_CTRL_reg                                                                 0x98007030
#define set_ISO_CTRL_reg(data)   (*((volatile unsigned int*) ISO_CTRL_reg)=data)
#define get_ISO_CTRL_reg   (*((volatile unsigned int*) ISO_CTRL_reg))
#define ISO_CTRL_inst_adr                                                            "0x000C"
#define ISO_CTRL_inst                                                                0x000C
#define ISO_CTRL_write_en9_shift                                                     (17)
#define ISO_CTRL_write_en9_mask                                                      (0x00020000)
#define ISO_CTRL_write_en9(data)                                                     (0x00020000&((data)<<17))
#define ISO_CTRL_write_en9_src(data)                                                 ((0x00020000&(data))>>17)
#define ISO_CTRL_get_write_en9(data)                                                 ((0x00020000&(data))>>17)
#define ISO_CTRL_iso_rst_wd_mask_shift                                               (16)
#define ISO_CTRL_iso_rst_wd_mask_mask                                                (0x00010000)
#define ISO_CTRL_iso_rst_wd_mask(data)                                               (0x00010000&((data)<<16))
#define ISO_CTRL_iso_rst_wd_mask_src(data)                                           ((0x00010000&(data))>>16)
#define ISO_CTRL_get_iso_rst_wd_mask(data)                                           ((0x00010000&(data))>>16)
#define ISO_CTRL_write_en8_shift                                                     (15)
#define ISO_CTRL_write_en8_mask                                                      (0x00008000)
#define ISO_CTRL_write_en8(data)                                                     (0x00008000&((data)<<15))
#define ISO_CTRL_write_en8_src(data)                                                 ((0x00008000&(data))>>15)
#define ISO_CTRL_get_write_en8(data)                                                 ((0x00008000&(data))>>15)
#define ISO_CTRL_dc_phy_cke_pd_shift                                                 (14)
#define ISO_CTRL_dc_phy_cke_pd_mask                                                  (0x00004000)
#define ISO_CTRL_dc_phy_cke_pd(data)                                                 (0x00004000&((data)<<14))
#define ISO_CTRL_dc_phy_cke_pd_src(data)                                             ((0x00004000&(data))>>14)
#define ISO_CTRL_get_dc_phy_cke_pd(data)                                             ((0x00004000&(data))>>14)
#define ISO_CTRL_write_en7_shift                                                     (13)
#define ISO_CTRL_write_en7_mask                                                      (0x00002000)
#define ISO_CTRL_write_en7(data)                                                     (0x00002000&((data)<<13))
#define ISO_CTRL_write_en7_src(data)                                                 ((0x00002000&(data))>>13)
#define ISO_CTRL_get_write_en7(data)                                                 ((0x00002000&(data))>>13)
#define ISO_CTRL_iso_mis_clk_en_shift                                                (12)
#define ISO_CTRL_iso_mis_clk_en_mask                                                 (0x00001000)
#define ISO_CTRL_iso_mis_clk_en(data)                                                (0x00001000&((data)<<12))
#define ISO_CTRL_iso_mis_clk_en_src(data)                                            ((0x00001000&(data))>>12)
#define ISO_CTRL_get_iso_mis_clk_en(data)                                            ((0x00001000&(data))>>12)
#define ISO_CTRL_write_en6_shift                                                     (11)
#define ISO_CTRL_write_en6_mask                                                      (0x00000800)
#define ISO_CTRL_write_en6(data)                                                     (0x00000800&((data)<<11))
#define ISO_CTRL_write_en6_src(data)                                                 ((0x00000800&(data))>>11)
#define ISO_CTRL_get_write_en6(data)                                                 ((0x00000800&(data))>>11)
#define ISO_CTRL_iso_rbus_sel_shift                                                  (10)
#define ISO_CTRL_iso_rbus_sel_mask                                                   (0x00000400)
#define ISO_CTRL_iso_rbus_sel(data)                                                  (0x00000400&((data)<<10))
#define ISO_CTRL_iso_rbus_sel_src(data)                                              ((0x00000400&(data))>>10)
#define ISO_CTRL_get_iso_rbus_sel(data)                                              ((0x00000400&(data))>>10)
#define ISO_CTRL_write_en5_shift                                                     (9)
#define ISO_CTRL_write_en5_mask                                                      (0x00000200)
#define ISO_CTRL_write_en5(data)                                                     (0x00000200&((data)<<9))
#define ISO_CTRL_write_en5_src(data)                                                 ((0x00000200&(data))>>9)
#define ISO_CTRL_get_write_en5(data)                                                 ((0x00000200&(data))>>9)
#define ISO_CTRL_iso_rst_mask_shift                                                  (8)
#define ISO_CTRL_iso_rst_mask_mask                                                   (0x00000100)
#define ISO_CTRL_iso_rst_mask(data)                                                  (0x00000100&((data)<<8))
#define ISO_CTRL_iso_rst_mask_src(data)                                              ((0x00000100&(data))>>8)
#define ISO_CTRL_get_iso_rst_mask(data)                                              ((0x00000100&(data))>>8)
#define ISO_CTRL_write_en4_shift                                                     (7)
#define ISO_CTRL_write_en4_mask                                                      (0x00000080)
#define ISO_CTRL_write_en4(data)                                                     (0x00000080&((data)<<7))
#define ISO_CTRL_write_en4_src(data)                                                 ((0x00000080&(data))>>7)
#define ISO_CTRL_get_write_en4(data)                                                 ((0x00000080&(data))>>7)
#define ISO_CTRL_clk_osc_on_en_shift                                                 (6)
#define ISO_CTRL_clk_osc_on_en_mask                                                  (0x00000040)
#define ISO_CTRL_clk_osc_on_en(data)                                                 (0x00000040&((data)<<6))
#define ISO_CTRL_clk_osc_on_en_src(data)                                             ((0x00000040&(data))>>6)
#define ISO_CTRL_get_clk_osc_on_en(data)                                             ((0x00000040&(data))>>6)
#define ISO_CTRL_write_en3_shift                                                     (5)
#define ISO_CTRL_write_en3_mask                                                      (0x00000020)
#define ISO_CTRL_write_en3(data)                                                     (0x00000020&((data)<<5))
#define ISO_CTRL_write_en3_src(data)                                                 ((0x00000020&(data))>>5)
#define ISO_CTRL_get_write_en3(data)                                                 ((0x00000020&(data))>>5)
#define ISO_CTRL_crt_sw_rstn_shift                                                   (4)
#define ISO_CTRL_crt_sw_rstn_mask                                                    (0x00000010)
#define ISO_CTRL_crt_sw_rstn(data)                                                   (0x00000010&((data)<<4))
#define ISO_CTRL_crt_sw_rstn_src(data)                                               ((0x00000010&(data))>>4)
#define ISO_CTRL_get_crt_sw_rstn(data)                                               ((0x00000010&(data))>>4)
#define ISO_CTRL_write_en2_shift                                                     (3)
#define ISO_CTRL_write_en2_mask                                                      (0x00000008)
#define ISO_CTRL_write_en2(data)                                                     (0x00000008&((data)<<3))
#define ISO_CTRL_write_en2_src(data)                                                 ((0x00000008&(data))>>3)
#define ISO_CTRL_get_write_en2(data)                                                 ((0x00000008&(data))>>3)
#define ISO_CTRL_iso_clk_sel_shift                                                   (2)
#define ISO_CTRL_iso_clk_sel_mask                                                    (0x00000004)
#define ISO_CTRL_iso_clk_sel(data)                                                   (0x00000004&((data)<<2))
#define ISO_CTRL_iso_clk_sel_src(data)                                               ((0x00000004&(data))>>2)
#define ISO_CTRL_get_iso_clk_sel(data)                                               ((0x00000004&(data))>>2)
#define ISO_CTRL_write_en1_shift                                                     (1)
#define ISO_CTRL_write_en1_mask                                                      (0x00000002)
#define ISO_CTRL_write_en1(data)                                                     (0x00000002&((data)<<1))
#define ISO_CTRL_write_en1_src(data)                                                 ((0x00000002&(data))>>1)
#define ISO_CTRL_get_write_en1(data)                                                 ((0x00000002&(data))>>1)
#define ISO_CTRL_ejtag_en_shift                                                      (0)
#define ISO_CTRL_ejtag_en_mask                                                       (0x00000001)
#define ISO_CTRL_ejtag_en(data)                                                      (0x00000001&((data)<<0))
#define ISO_CTRL_ejtag_en_src(data)                                                  ((0x00000001&(data))>>0)
#define ISO_CTRL_get_ejtag_en(data)                                                  ((0x00000001&(data))>>0)


#define ISO_RTC                                                                      0x98007034
#define ISO_RTC_reg_addr                                                             "0x98007034"
#define ISO_RTC_reg                                                                  0x98007034
#define set_ISO_RTC_reg(data)   (*((volatile unsigned int*) ISO_RTC_reg)=data)
#define get_ISO_RTC_reg   (*((volatile unsigned int*) ISO_RTC_reg))
#define ISO_RTC_inst_adr                                                             "0x000D"
#define ISO_RTC_inst                                                                 0x000D
#define ISO_RTC_hsec_sync_shift                                                      (2)
#define ISO_RTC_hsec_sync_mask                                                       (0x00000004)
#define ISO_RTC_hsec_sync(data)                                                      (0x00000004&((data)<<2))
#define ISO_RTC_hsec_sync_src(data)                                                  ((0x00000004&(data))>>2)
#define ISO_RTC_get_hsec_sync(data)                                                  ((0x00000004&(data))>>2)
#define ISO_RTC_hsec_int_en_shift                                                    (1)
#define ISO_RTC_hsec_int_en_mask                                                     (0x00000002)
#define ISO_RTC_hsec_int_en(data)                                                    (0x00000002&((data)<<1))
#define ISO_RTC_hsec_int_en_src(data)                                                ((0x00000002&(data))>>1)
#define ISO_RTC_get_hsec_int_en(data)                                                ((0x00000002&(data))>>1)
#define ISO_RTC_alarm_int_en_shift                                                   (0)
#define ISO_RTC_alarm_int_en_mask                                                    (0x00000001)
#define ISO_RTC_alarm_int_en(data)                                                   (0x00000001&((data)<<0))
#define ISO_RTC_alarm_int_en_src(data)                                               ((0x00000001&(data))>>0)
#define ISO_RTC_get_alarm_int_en(data)                                               ((0x00000001&(data))>>0)


#define ISO_CELL                                                                     0x98007038
#define ISO_CELL_reg_addr                                                            "0x98007038"
#define ISO_CELL_reg                                                                 0x98007038
#define set_ISO_CELL_reg(data)   (*((volatile unsigned int*) ISO_CELL_reg)=data)
#define get_ISO_CELL_reg   (*((volatile unsigned int*) ISO_CELL_reg))
#define ISO_CELL_inst_adr                                                            "0x000E"
#define ISO_CELL_inst                                                                0x000E
#define ISO_CELL_bi_bypass_shift                                                     (2)
#define ISO_CELL_bi_bypass_mask                                                      (0x00000004)
#define ISO_CELL_bi_bypass(data)                                                     (0x00000004&((data)<<2))
#define ISO_CELL_bi_bypass_src(data)                                                 ((0x00000004&(data))>>2)
#define ISO_CELL_get_bi_bypass(data)                                                 ((0x00000004&(data))>>2)
#define ISO_CELL_iso_ctrl_en1_shift                                                  (1)
#define ISO_CELL_iso_ctrl_en1_mask                                                   (0x00000002)
#define ISO_CELL_iso_ctrl_en1(data)                                                  (0x00000002&((data)<<1))
#define ISO_CELL_iso_ctrl_en1_src(data)                                              ((0x00000002&(data))>>1)
#define ISO_CELL_get_iso_ctrl_en1(data)                                              ((0x00000002&(data))>>1)
#define ISO_CELL_iso_ctrl_en0_shift                                                  (0)
#define ISO_CELL_iso_ctrl_en0_mask                                                   (0x00000001)
#define ISO_CELL_iso_ctrl_en0(data)                                                  (0x00000001&((data)<<0))
#define ISO_CELL_iso_ctrl_en0_src(data)                                              ((0x00000001&(data))>>0)
#define ISO_CELL_get_iso_ctrl_en0(data)                                              ((0x00000001&(data))>>0)


#define ISO_POWER                                                                    0x9800703C
#define ISO_POWER_reg_addr                                                           "0x9800703C"
#define ISO_POWER_reg                                                                0x9800703C
#define set_ISO_POWER_reg(data)   (*((volatile unsigned int*) ISO_POWER_reg)=data)
#define get_ISO_POWER_reg   (*((volatile unsigned int*) ISO_POWER_reg))
#define ISO_POWER_inst_adr                                                           "0x000F"
#define ISO_POWER_inst                                                               0x000F
#define ISO_POWER_top_vdd_on_shift                                                   (1)
#define ISO_POWER_top_vdd_on_mask                                                    (0x00000002)
#define ISO_POWER_top_vdd_on(data)                                                   (0x00000002&((data)<<1))
#define ISO_POWER_top_vdd_on_src(data)                                               ((0x00000002&(data))>>1)
#define ISO_POWER_get_top_vdd_on(data)                                               ((0x00000002&(data))>>1)
#define ISO_POWER_scpu_vdd_on_shift                                                  (0)
#define ISO_POWER_scpu_vdd_on_mask                                                   (0x00000001)
#define ISO_POWER_scpu_vdd_on(data)                                                  (0x00000001&((data)<<0))
#define ISO_POWER_scpu_vdd_on_src(data)                                              ((0x00000001&(data))>>0)
#define ISO_POWER_get_scpu_vdd_on(data)                                              ((0x00000001&(data))>>0)


#define ISO_SCPU_INT_EN                                                              0x98007040
#define ISO_SCPU_INT_EN_reg_addr                                                     "0x98007040"
#define ISO_SCPU_INT_EN_reg                                                          0x98007040
#define set_ISO_SCPU_INT_EN_reg(data)   (*((volatile unsigned int*) ISO_SCPU_INT_EN_reg)=data)
#define get_ISO_SCPU_INT_EN_reg   (*((volatile unsigned int*) ISO_SCPU_INT_EN_reg))
#define ISO_SCPU_INT_EN_inst_adr                                                     "0x0010"
#define ISO_SCPU_INT_EN_inst                                                         0x0010
#define ISO_SCPU_INT_EN_i2c1_req_shift                                               (31)
#define ISO_SCPU_INT_EN_i2c1_req_mask                                                (0x80000000)
#define ISO_SCPU_INT_EN_i2c1_req(data)                                               (0x80000000&((data)<<31))
#define ISO_SCPU_INT_EN_i2c1_req_src(data)                                           ((0x80000000&(data))>>31)
#define ISO_SCPU_INT_EN_get_i2c1_req(data)                                           ((0x80000000&(data))>>31)
#define ISO_SCPU_INT_EN_porb_av_cen_shift                                            (30)
#define ISO_SCPU_INT_EN_porb_av_cen_mask                                             (0x40000000)
#define ISO_SCPU_INT_EN_porb_av_cen(data)                                            (0x40000000&((data)<<30))
#define ISO_SCPU_INT_EN_porb_av_cen_src(data)                                        ((0x40000000&(data))>>30)
#define ISO_SCPU_INT_EN_get_porb_av_cen(data)                                        ((0x40000000&(data))>>30)
#define ISO_SCPU_INT_EN_porb_dv_cen_shift                                            (29)
#define ISO_SCPU_INT_EN_porb_dv_cen_mask                                             (0x20000000)
#define ISO_SCPU_INT_EN_porb_dv_cen(data)                                            (0x20000000&((data)<<29))
#define ISO_SCPU_INT_EN_porb_dv_cen_src(data)                                        ((0x20000000&(data))>>29)
#define ISO_SCPU_INT_EN_get_porb_dv_cen(data)                                        ((0x20000000&(data))>>29)
#define ISO_SCPU_INT_EN_gpioda_shift                                                 (20)
#define ISO_SCPU_INT_EN_gpioda_mask                                                  (0x00100000)
#define ISO_SCPU_INT_EN_gpioda(data)                                                 (0x00100000&((data)<<20))
#define ISO_SCPU_INT_EN_gpioda_src(data)                                             ((0x00100000&(data))>>20)
#define ISO_SCPU_INT_EN_get_gpioda(data)                                             ((0x00100000&(data))>>20)
#define ISO_SCPU_INT_EN_gpioa_shift                                                  (19)
#define ISO_SCPU_INT_EN_gpioa_mask                                                   (0x00080000)
#define ISO_SCPU_INT_EN_gpioa(data)                                                  (0x00080000&((data)<<19))
#define ISO_SCPU_INT_EN_gpioa_src(data)                                              ((0x00080000&(data))>>19)
#define ISO_SCPU_INT_EN_get_gpioa(data)                                              ((0x00080000&(data))>>19)
#define ISO_SCPU_INT_EN_rtc_alarm_shift                                              (13)
#define ISO_SCPU_INT_EN_rtc_alarm_mask                                               (0x00002000)
#define ISO_SCPU_INT_EN_rtc_alarm(data)                                              (0x00002000&((data)<<13))
#define ISO_SCPU_INT_EN_rtc_alarm_src(data)                                          ((0x00002000&(data))>>13)
#define ISO_SCPU_INT_EN_get_rtc_alarm(data)                                          ((0x00002000&(data))>>13)
#define ISO_SCPU_INT_EN_rtc_hsec_shift                                               (12)
#define ISO_SCPU_INT_EN_rtc_hsec_mask                                                (0x00001000)
#define ISO_SCPU_INT_EN_rtc_hsec(data)                                               (0x00001000&((data)<<12))
#define ISO_SCPU_INT_EN_rtc_hsec_src(data)                                           ((0x00001000&(data))>>12)
#define ISO_SCPU_INT_EN_get_rtc_hsec(data)                                           ((0x00001000&(data))>>12)
#define ISO_SCPU_INT_EN_i2c1_shift                                                   (11)
#define ISO_SCPU_INT_EN_i2c1_mask                                                    (0x00000800)
#define ISO_SCPU_INT_EN_i2c1(data)                                                   (0x00000800&((data)<<11))
#define ISO_SCPU_INT_EN_i2c1_src(data)                                               ((0x00000800&(data))>>11)
#define ISO_SCPU_INT_EN_get_i2c1(data)                                               ((0x00000800&(data))>>11)
#define ISO_SCPU_INT_EN_i2c0_shift                                                   (8)
#define ISO_SCPU_INT_EN_i2c0_mask                                                    (0x00000100)
#define ISO_SCPU_INT_EN_i2c0(data)                                                   (0x00000100&((data)<<8))
#define ISO_SCPU_INT_EN_i2c0_src(data)                                               ((0x00000100&(data))>>8)
#define ISO_SCPU_INT_EN_get_i2c0(data)                                               ((0x00000100&(data))>>8)
#define ISO_SCPU_INT_EN_irda_shift                                                   (5)
#define ISO_SCPU_INT_EN_irda_mask                                                    (0x00000020)
#define ISO_SCPU_INT_EN_irda(data)                                                   (0x00000020&((data)<<5))
#define ISO_SCPU_INT_EN_irda_src(data)                                               ((0x00000020&(data))>>5)
#define ISO_SCPU_INT_EN_get_irda(data)                                               ((0x00000020&(data))>>5)
#define ISO_SCPU_INT_EN_ur0_shift                                                    (2)
#define ISO_SCPU_INT_EN_ur0_mask                                                     (0x00000004)
#define ISO_SCPU_INT_EN_ur0(data)                                                    (0x00000004&((data)<<2))
#define ISO_SCPU_INT_EN_ur0_src(data)                                                ((0x00000004&(data))>>2)
#define ISO_SCPU_INT_EN_get_ur0(data)                                                ((0x00000004&(data))>>2)


#define ISO_USB                                                                      0x98007044
#define ISO_USB_reg_addr                                                             "0x98007044"
#define ISO_USB_reg                                                                  0x98007044
#define set_ISO_USB_reg(data)   (*((volatile unsigned int*) ISO_USB_reg)=data)
#define get_ISO_USB_reg   (*((volatile unsigned int*) ISO_USB_reg))
#define ISO_USB_inst_adr                                                             "0x0011"
#define ISO_USB_inst                                                                 0x0011
#define ISO_USB_dcp_ctrl3_shift                                                      (3)
#define ISO_USB_dcp_ctrl3_mask                                                       (0x00000008)
#define ISO_USB_dcp_ctrl3(data)                                                      (0x00000008&((data)<<3))
#define ISO_USB_dcp_ctrl3_src(data)                                                  ((0x00000008&(data))>>3)
#define ISO_USB_get_dcp_ctrl3(data)                                                  ((0x00000008&(data))>>3)
#define ISO_USB_dcp_ctrl2_shift                                                      (2)
#define ISO_USB_dcp_ctrl2_mask                                                       (0x00000004)
#define ISO_USB_dcp_ctrl2(data)                                                      (0x00000004&((data)<<2))
#define ISO_USB_dcp_ctrl2_src(data)                                                  ((0x00000004&(data))>>2)
#define ISO_USB_get_dcp_ctrl2(data)                                                  ((0x00000004&(data))>>2)
#define ISO_USB_dcp_ctrl1_shift                                                      (1)
#define ISO_USB_dcp_ctrl1_mask                                                       (0x00000002)
#define ISO_USB_dcp_ctrl1(data)                                                      (0x00000002&((data)<<1))
#define ISO_USB_dcp_ctrl1_src(data)                                                  ((0x00000002&(data))>>1)
#define ISO_USB_get_dcp_ctrl1(data)                                                  ((0x00000002&(data))>>1)
#define ISO_USB_dcp_ctrl0_shift                                                      (0)
#define ISO_USB_dcp_ctrl0_mask                                                       (0x00000001)
#define ISO_USB_dcp_ctrl0(data)                                                      (0x00000001&((data)<<0))
#define ISO_USB_dcp_ctrl0_src(data)                                                  ((0x00000001&(data))>>0)
#define ISO_USB_get_dcp_ctrl0(data)                                                  ((0x00000001&(data))>>0)


#define ISO_ACPU_INT_EN                                                              0x98007048
#define ISO_ACPU_INT_EN_reg_addr                                                     "0x98007048"
#define ISO_ACPU_INT_EN_reg                                                          0x98007048
#define set_ISO_ACPU_INT_EN_reg(data)   (*((volatile unsigned int*) ISO_ACPU_INT_EN_reg)=data)
#define get_ISO_ACPU_INT_EN_reg   (*((volatile unsigned int*) ISO_ACPU_INT_EN_reg))
#define ISO_ACPU_INT_EN_inst_adr                                                     "0x0012"
#define ISO_ACPU_INT_EN_inst                                                         0x0012
#define ISO_ACPU_INT_EN_i2c1_req_shift                                               (31)
#define ISO_ACPU_INT_EN_i2c1_req_mask                                                (0x80000000)
#define ISO_ACPU_INT_EN_i2c1_req(data)                                               (0x80000000&((data)<<31))
#define ISO_ACPU_INT_EN_i2c1_req_src(data)                                           ((0x80000000&(data))>>31)
#define ISO_ACPU_INT_EN_get_i2c1_req(data)                                           ((0x80000000&(data))>>31)
#define ISO_ACPU_INT_EN_gpioda_shift                                                 (20)
#define ISO_ACPU_INT_EN_gpioda_mask                                                  (0x00100000)
#define ISO_ACPU_INT_EN_gpioda(data)                                                 (0x00100000&((data)<<20))
#define ISO_ACPU_INT_EN_gpioda_src(data)                                             ((0x00100000&(data))>>20)
#define ISO_ACPU_INT_EN_get_gpioda(data)                                             ((0x00100000&(data))>>20)
#define ISO_ACPU_INT_EN_gpioa_shift                                                  (19)
#define ISO_ACPU_INT_EN_gpioa_mask                                                   (0x00080000)
#define ISO_ACPU_INT_EN_gpioa(data)                                                  (0x00080000&((data)<<19))
#define ISO_ACPU_INT_EN_gpioa_src(data)                                              ((0x00080000&(data))>>19)
#define ISO_ACPU_INT_EN_get_gpioa(data)                                              ((0x00080000&(data))>>19)
#define ISO_ACPU_INT_EN_rtc_alarm_shift                                              (13)
#define ISO_ACPU_INT_EN_rtc_alarm_mask                                               (0x00002000)
#define ISO_ACPU_INT_EN_rtc_alarm(data)                                              (0x00002000&((data)<<13))
#define ISO_ACPU_INT_EN_rtc_alarm_src(data)                                          ((0x00002000&(data))>>13)
#define ISO_ACPU_INT_EN_get_rtc_alarm(data)                                          ((0x00002000&(data))>>13)
#define ISO_ACPU_INT_EN_rtc_hsec_shift                                               (12)
#define ISO_ACPU_INT_EN_rtc_hsec_mask                                                (0x00001000)
#define ISO_ACPU_INT_EN_rtc_hsec(data)                                               (0x00001000&((data)<<12))
#define ISO_ACPU_INT_EN_rtc_hsec_src(data)                                           ((0x00001000&(data))>>12)
#define ISO_ACPU_INT_EN_get_rtc_hsec(data)                                           ((0x00001000&(data))>>12)
#define ISO_ACPU_INT_EN_i2c1_shift                                                   (11)
#define ISO_ACPU_INT_EN_i2c1_mask                                                    (0x00000800)
#define ISO_ACPU_INT_EN_i2c1(data)                                                   (0x00000800&((data)<<11))
#define ISO_ACPU_INT_EN_i2c1_src(data)                                               ((0x00000800&(data))>>11)
#define ISO_ACPU_INT_EN_get_i2c1(data)                                               ((0x00000800&(data))>>11)
#define ISO_ACPU_INT_EN_i2c0_shift                                                   (8)
#define ISO_ACPU_INT_EN_i2c0_mask                                                    (0x00000100)
#define ISO_ACPU_INT_EN_i2c0(data)                                                   (0x00000100&((data)<<8))
#define ISO_ACPU_INT_EN_i2c0_src(data)                                               ((0x00000100&(data))>>8)
#define ISO_ACPU_INT_EN_get_i2c0(data)                                               ((0x00000100&(data))>>8)
#define ISO_ACPU_INT_EN_irda_shift                                                   (5)
#define ISO_ACPU_INT_EN_irda_mask                                                    (0x00000020)
#define ISO_ACPU_INT_EN_irda(data)                                                   (0x00000020&((data)<<5))
#define ISO_ACPU_INT_EN_irda_src(data)                                               ((0x00000020&(data))>>5)
#define ISO_ACPU_INT_EN_get_irda(data)                                               ((0x00000020&(data))>>5)
#define ISO_ACPU_INT_EN_ur0_shift                                                    (2)
#define ISO_ACPU_INT_EN_ur0_mask                                                     (0x00000004)
#define ISO_ACPU_INT_EN_ur0(data)                                                    (0x00000004&((data)<<2))
#define ISO_ACPU_INT_EN_ur0_src(data)                                                ((0x00000004&(data))>>2)
#define ISO_ACPU_INT_EN_get_ur0(data)                                                ((0x00000004&(data))>>2)


#define ISO_CPU_ST1                                                                  0x9800704C
#define ISO_CPU_ST1_reg_addr                                                         "0x9800704C"
#define ISO_CPU_ST1_reg                                                              0x9800704C
#define set_ISO_CPU_ST1_reg(data)   (*((volatile unsigned int*) ISO_CPU_ST1_reg)=data)
#define get_ISO_CPU_ST1_reg   (*((volatile unsigned int*) ISO_CPU_ST1_reg))
#define ISO_CPU_ST1_inst_adr                                                         "0x0013"
#define ISO_CPU_ST1_inst                                                             0x0013
#define ISO_CPU_ST1_acpu_boot_info_shift                                             (0)
#define ISO_CPU_ST1_acpu_boot_info_mask                                              (0xFFFFFFFF)
#define ISO_CPU_ST1_acpu_boot_info(data)                                             (0xFFFFFFFF&((data)<<0))
#define ISO_CPU_ST1_acpu_boot_info_src(data)                                         ((0xFFFFFFFF&(data))>>0)
#define ISO_CPU_ST1_get_acpu_boot_info(data)                                         ((0xFFFFFFFF&(data))>>0)


#define ISO_CPU_ST1V                                                                 0x98007050
#define ISO_CPU_ST1V_reg_addr                                                        "0x98007050"
#define ISO_CPU_ST1V_reg                                                             0x98007050
#define set_ISO_CPU_ST1V_reg(data)   (*((volatile unsigned int*) ISO_CPU_ST1V_reg)=data)
#define get_ISO_CPU_ST1V_reg   (*((volatile unsigned int*) ISO_CPU_ST1V_reg))
#define ISO_CPU_ST1V_inst_adr                                                        "0x0014"
#define ISO_CPU_ST1V_inst                                                            0x0014
#define ISO_CPU_ST1V_acpu_boot_info_valid_shift                                      (0)
#define ISO_CPU_ST1V_acpu_boot_info_valid_mask                                       (0x00000001)
#define ISO_CPU_ST1V_acpu_boot_info_valid(data)                                      (0x00000001&((data)<<0))
#define ISO_CPU_ST1V_acpu_boot_info_valid_src(data)                                  ((0x00000001&(data))>>0)
#define ISO_CPU_ST1V_get_acpu_boot_info_valid(data)                                  ((0x00000001&(data))>>0)


#define ISO_DUMMY1                                                                   0x98007054
#define ISO_DUMMY1_reg_addr                                                          "0x98007054"
#define ISO_DUMMY1_reg                                                               0x98007054
#define set_ISO_DUMMY1_reg(data)   (*((volatile unsigned int*) ISO_DUMMY1_reg)=data)
#define get_ISO_DUMMY1_reg   (*((volatile unsigned int*) ISO_DUMMY1_reg))
#define ISO_DUMMY1_inst_adr                                                          "0x0015"
#define ISO_DUMMY1_inst                                                              0x0015
#define ISO_DUMMY1_rvd31_shift                                                       (31)
#define ISO_DUMMY1_rvd31_mask                                                        (0x80000000)
#define ISO_DUMMY1_rvd31(data)                                                       (0x80000000&((data)<<31))
#define ISO_DUMMY1_rvd31_src(data)                                                   ((0x80000000&(data))>>31)
#define ISO_DUMMY1_get_rvd31(data)                                                   ((0x80000000&(data))>>31)
#define ISO_DUMMY1_rvd30_shift                                                       (30)
#define ISO_DUMMY1_rvd30_mask                                                        (0x40000000)
#define ISO_DUMMY1_rvd30(data)                                                       (0x40000000&((data)<<30))
#define ISO_DUMMY1_rvd30_src(data)                                                   ((0x40000000&(data))>>30)
#define ISO_DUMMY1_get_rvd30(data)                                                   ((0x40000000&(data))>>30)
#define ISO_DUMMY1_rvd29_shift                                                       (29)
#define ISO_DUMMY1_rvd29_mask                                                        (0x20000000)
#define ISO_DUMMY1_rvd29(data)                                                       (0x20000000&((data)<<29))
#define ISO_DUMMY1_rvd29_src(data)                                                   ((0x20000000&(data))>>29)
#define ISO_DUMMY1_get_rvd29(data)                                                   ((0x20000000&(data))>>29)
#define ISO_DUMMY1_rvd28_shift                                                       (28)
#define ISO_DUMMY1_rvd28_mask                                                        (0x10000000)
#define ISO_DUMMY1_rvd28(data)                                                       (0x10000000&((data)<<28))
#define ISO_DUMMY1_rvd28_src(data)                                                   ((0x10000000&(data))>>28)
#define ISO_DUMMY1_get_rvd28(data)                                                   ((0x10000000&(data))>>28)
#define ISO_DUMMY1_rvd27_shift                                                       (27)
#define ISO_DUMMY1_rvd27_mask                                                        (0x08000000)
#define ISO_DUMMY1_rvd27(data)                                                       (0x08000000&((data)<<27))
#define ISO_DUMMY1_rvd27_src(data)                                                   ((0x08000000&(data))>>27)
#define ISO_DUMMY1_get_rvd27(data)                                                   ((0x08000000&(data))>>27)
#define ISO_DUMMY1_rvd26_shift                                                       (26)
#define ISO_DUMMY1_rvd26_mask                                                        (0x04000000)
#define ISO_DUMMY1_rvd26(data)                                                       (0x04000000&((data)<<26))
#define ISO_DUMMY1_rvd26_src(data)                                                   ((0x04000000&(data))>>26)
#define ISO_DUMMY1_get_rvd26(data)                                                   ((0x04000000&(data))>>26)
#define ISO_DUMMY1_rvd25_shift                                                       (25)
#define ISO_DUMMY1_rvd25_mask                                                        (0x02000000)
#define ISO_DUMMY1_rvd25(data)                                                       (0x02000000&((data)<<25))
#define ISO_DUMMY1_rvd25_src(data)                                                   ((0x02000000&(data))>>25)
#define ISO_DUMMY1_get_rvd25(data)                                                   ((0x02000000&(data))>>25)
#define ISO_DUMMY1_rvd24_shift                                                       (24)
#define ISO_DUMMY1_rvd24_mask                                                        (0x01000000)
#define ISO_DUMMY1_rvd24(data)                                                       (0x01000000&((data)<<24))
#define ISO_DUMMY1_rvd24_src(data)                                                   ((0x01000000&(data))>>24)
#define ISO_DUMMY1_get_rvd24(data)                                                   ((0x01000000&(data))>>24)
#define ISO_DUMMY1_rvd23_shift                                                       (23)
#define ISO_DUMMY1_rvd23_mask                                                        (0x00800000)
#define ISO_DUMMY1_rvd23(data)                                                       (0x00800000&((data)<<23))
#define ISO_DUMMY1_rvd23_src(data)                                                   ((0x00800000&(data))>>23)
#define ISO_DUMMY1_get_rvd23(data)                                                   ((0x00800000&(data))>>23)
#define ISO_DUMMY1_rvd22_shift                                                       (22)
#define ISO_DUMMY1_rvd22_mask                                                        (0x00400000)
#define ISO_DUMMY1_rvd22(data)                                                       (0x00400000&((data)<<22))
#define ISO_DUMMY1_rvd22_src(data)                                                   ((0x00400000&(data))>>22)
#define ISO_DUMMY1_get_rvd22(data)                                                   ((0x00400000&(data))>>22)
#define ISO_DUMMY1_rvd21_shift                                                       (21)
#define ISO_DUMMY1_rvd21_mask                                                        (0x00200000)
#define ISO_DUMMY1_rvd21(data)                                                       (0x00200000&((data)<<21))
#define ISO_DUMMY1_rvd21_src(data)                                                   ((0x00200000&(data))>>21)
#define ISO_DUMMY1_get_rvd21(data)                                                   ((0x00200000&(data))>>21)
#define ISO_DUMMY1_rvd20_shift                                                       (20)
#define ISO_DUMMY1_rvd20_mask                                                        (0x00100000)
#define ISO_DUMMY1_rvd20(data)                                                       (0x00100000&((data)<<20))
#define ISO_DUMMY1_rvd20_src(data)                                                   ((0x00100000&(data))>>20)
#define ISO_DUMMY1_get_rvd20(data)                                                   ((0x00100000&(data))>>20)
#define ISO_DUMMY1_rvd19_shift                                                       (19)
#define ISO_DUMMY1_rvd19_mask                                                        (0x00080000)
#define ISO_DUMMY1_rvd19(data)                                                       (0x00080000&((data)<<19))
#define ISO_DUMMY1_rvd19_src(data)                                                   ((0x00080000&(data))>>19)
#define ISO_DUMMY1_get_rvd19(data)                                                   ((0x00080000&(data))>>19)
#define ISO_DUMMY1_rvd18_shift                                                       (18)
#define ISO_DUMMY1_rvd18_mask                                                        (0x00040000)
#define ISO_DUMMY1_rvd18(data)                                                       (0x00040000&((data)<<18))
#define ISO_DUMMY1_rvd18_src(data)                                                   ((0x00040000&(data))>>18)
#define ISO_DUMMY1_get_rvd18(data)                                                   ((0x00040000&(data))>>18)
#define ISO_DUMMY1_rvd17_shift                                                       (17)
#define ISO_DUMMY1_rvd17_mask                                                        (0x00020000)
#define ISO_DUMMY1_rvd17(data)                                                       (0x00020000&((data)<<17))
#define ISO_DUMMY1_rvd17_src(data)                                                   ((0x00020000&(data))>>17)
#define ISO_DUMMY1_get_rvd17(data)                                                   ((0x00020000&(data))>>17)
#define ISO_DUMMY1_rvd16_shift                                                       (16)
#define ISO_DUMMY1_rvd16_mask                                                        (0x00010000)
#define ISO_DUMMY1_rvd16(data)                                                       (0x00010000&((data)<<16))
#define ISO_DUMMY1_rvd16_src(data)                                                   ((0x00010000&(data))>>16)
#define ISO_DUMMY1_get_rvd16(data)                                                   ((0x00010000&(data))>>16)
#define ISO_DUMMY1_rvd15_shift                                                       (15)
#define ISO_DUMMY1_rvd15_mask                                                        (0x00008000)
#define ISO_DUMMY1_rvd15(data)                                                       (0x00008000&((data)<<15))
#define ISO_DUMMY1_rvd15_src(data)                                                   ((0x00008000&(data))>>15)
#define ISO_DUMMY1_get_rvd15(data)                                                   ((0x00008000&(data))>>15)
#define ISO_DUMMY1_rvd14_shift                                                       (14)
#define ISO_DUMMY1_rvd14_mask                                                        (0x00004000)
#define ISO_DUMMY1_rvd14(data)                                                       (0x00004000&((data)<<14))
#define ISO_DUMMY1_rvd14_src(data)                                                   ((0x00004000&(data))>>14)
#define ISO_DUMMY1_get_rvd14(data)                                                   ((0x00004000&(data))>>14)
#define ISO_DUMMY1_rvd13_shift                                                       (13)
#define ISO_DUMMY1_rvd13_mask                                                        (0x00002000)
#define ISO_DUMMY1_rvd13(data)                                                       (0x00002000&((data)<<13))
#define ISO_DUMMY1_rvd13_src(data)                                                   ((0x00002000&(data))>>13)
#define ISO_DUMMY1_get_rvd13(data)                                                   ((0x00002000&(data))>>13)
#define ISO_DUMMY1_rvd12_shift                                                       (12)
#define ISO_DUMMY1_rvd12_mask                                                        (0x00001000)
#define ISO_DUMMY1_rvd12(data)                                                       (0x00001000&((data)<<12))
#define ISO_DUMMY1_rvd12_src(data)                                                   ((0x00001000&(data))>>12)
#define ISO_DUMMY1_get_rvd12(data)                                                   ((0x00001000&(data))>>12)
#define ISO_DUMMY1_rvd11_shift                                                       (11)
#define ISO_DUMMY1_rvd11_mask                                                        (0x00000800)
#define ISO_DUMMY1_rvd11(data)                                                       (0x00000800&((data)<<11))
#define ISO_DUMMY1_rvd11_src(data)                                                   ((0x00000800&(data))>>11)
#define ISO_DUMMY1_get_rvd11(data)                                                   ((0x00000800&(data))>>11)
#define ISO_DUMMY1_rvd10_shift                                                       (10)
#define ISO_DUMMY1_rvd10_mask                                                        (0x00000400)
#define ISO_DUMMY1_rvd10(data)                                                       (0x00000400&((data)<<10))
#define ISO_DUMMY1_rvd10_src(data)                                                   ((0x00000400&(data))>>10)
#define ISO_DUMMY1_get_rvd10(data)                                                   ((0x00000400&(data))>>10)
#define ISO_DUMMY1_rvd9_shift                                                        (9)
#define ISO_DUMMY1_rvd9_mask                                                         (0x00000200)
#define ISO_DUMMY1_rvd9(data)                                                        (0x00000200&((data)<<9))
#define ISO_DUMMY1_rvd9_src(data)                                                    ((0x00000200&(data))>>9)
#define ISO_DUMMY1_get_rvd9(data)                                                    ((0x00000200&(data))>>9)
#define ISO_DUMMY1_rvd8_shift                                                        (8)
#define ISO_DUMMY1_rvd8_mask                                                         (0x00000100)
#define ISO_DUMMY1_rvd8(data)                                                        (0x00000100&((data)<<8))
#define ISO_DUMMY1_rvd8_src(data)                                                    ((0x00000100&(data))>>8)
#define ISO_DUMMY1_get_rvd8(data)                                                    ((0x00000100&(data))>>8)
#define ISO_DUMMY1_rvd7_shift                                                        (7)
#define ISO_DUMMY1_rvd7_mask                                                         (0x00000080)
#define ISO_DUMMY1_rvd7(data)                                                        (0x00000080&((data)<<7))
#define ISO_DUMMY1_rvd7_src(data)                                                    ((0x00000080&(data))>>7)
#define ISO_DUMMY1_get_rvd7(data)                                                    ((0x00000080&(data))>>7)
#define ISO_DUMMY1_rvd6_shift                                                        (6)
#define ISO_DUMMY1_rvd6_mask                                                         (0x00000040)
#define ISO_DUMMY1_rvd6(data)                                                        (0x00000040&((data)<<6))
#define ISO_DUMMY1_rvd6_src(data)                                                    ((0x00000040&(data))>>6)
#define ISO_DUMMY1_get_rvd6(data)                                                    ((0x00000040&(data))>>6)
#define ISO_DUMMY1_rvd5_shift                                                        (5)
#define ISO_DUMMY1_rvd5_mask                                                         (0x00000020)
#define ISO_DUMMY1_rvd5(data)                                                        (0x00000020&((data)<<5))
#define ISO_DUMMY1_rvd5_src(data)                                                    ((0x00000020&(data))>>5)
#define ISO_DUMMY1_get_rvd5(data)                                                    ((0x00000020&(data))>>5)
#define ISO_DUMMY1_rvd4_shift                                                        (4)
#define ISO_DUMMY1_rvd4_mask                                                         (0x00000010)
#define ISO_DUMMY1_rvd4(data)                                                        (0x00000010&((data)<<4))
#define ISO_DUMMY1_rvd4_src(data)                                                    ((0x00000010&(data))>>4)
#define ISO_DUMMY1_get_rvd4(data)                                                    ((0x00000010&(data))>>4)
#define ISO_DUMMY1_rvd3_shift                                                        (3)
#define ISO_DUMMY1_rvd3_mask                                                         (0x00000008)
#define ISO_DUMMY1_rvd3(data)                                                        (0x00000008&((data)<<3))
#define ISO_DUMMY1_rvd3_src(data)                                                    ((0x00000008&(data))>>3)
#define ISO_DUMMY1_get_rvd3(data)                                                    ((0x00000008&(data))>>3)
#define ISO_DUMMY1_rvd2_shift                                                        (2)
#define ISO_DUMMY1_rvd2_mask                                                         (0x00000004)
#define ISO_DUMMY1_rvd2(data)                                                        (0x00000004&((data)<<2))
#define ISO_DUMMY1_rvd2_src(data)                                                    ((0x00000004&(data))>>2)
#define ISO_DUMMY1_get_rvd2(data)                                                    ((0x00000004&(data))>>2)
#define ISO_DUMMY1_rvd1_shift                                                        (1)
#define ISO_DUMMY1_rvd1_mask                                                         (0x00000002)
#define ISO_DUMMY1_rvd1(data)                                                        (0x00000002&((data)<<1))
#define ISO_DUMMY1_rvd1_src(data)                                                    ((0x00000002&(data))>>1)
#define ISO_DUMMY1_get_rvd1(data)                                                    ((0x00000002&(data))>>1)
#define ISO_DUMMY1_rvd0_shift                                                        (0)
#define ISO_DUMMY1_rvd0_mask                                                         (0x00000001)
#define ISO_DUMMY1_rvd0(data)                                                        (0x00000001&((data)<<0))
#define ISO_DUMMY1_rvd0_src(data)                                                    ((0x00000001&(data))>>0)
#define ISO_DUMMY1_get_rvd0(data)                                                    ((0x00000001&(data))>>0)


#define ISO_DUMMY2                                                                   0x98007058
#define ISO_DUMMY2_reg_addr                                                          "0x98007058"
#define ISO_DUMMY2_reg                                                               0x98007058
#define set_ISO_DUMMY2_reg(data)   (*((volatile unsigned int*) ISO_DUMMY2_reg)=data)
#define get_ISO_DUMMY2_reg   (*((volatile unsigned int*) ISO_DUMMY2_reg))
#define ISO_DUMMY2_inst_adr                                                          "0x0016"
#define ISO_DUMMY2_inst                                                              0x0016
#define ISO_DUMMY2_rvd31_shift                                                       (31)
#define ISO_DUMMY2_rvd31_mask                                                        (0x80000000)
#define ISO_DUMMY2_rvd31(data)                                                       (0x80000000&((data)<<31))
#define ISO_DUMMY2_rvd31_src(data)                                                   ((0x80000000&(data))>>31)
#define ISO_DUMMY2_get_rvd31(data)                                                   ((0x80000000&(data))>>31)
#define ISO_DUMMY2_rvd30_shift                                                       (30)
#define ISO_DUMMY2_rvd30_mask                                                        (0x40000000)
#define ISO_DUMMY2_rvd30(data)                                                       (0x40000000&((data)<<30))
#define ISO_DUMMY2_rvd30_src(data)                                                   ((0x40000000&(data))>>30)
#define ISO_DUMMY2_get_rvd30(data)                                                   ((0x40000000&(data))>>30)
#define ISO_DUMMY2_rvd29_shift                                                       (29)
#define ISO_DUMMY2_rvd29_mask                                                        (0x20000000)
#define ISO_DUMMY2_rvd29(data)                                                       (0x20000000&((data)<<29))
#define ISO_DUMMY2_rvd29_src(data)                                                   ((0x20000000&(data))>>29)
#define ISO_DUMMY2_get_rvd29(data)                                                   ((0x20000000&(data))>>29)
#define ISO_DUMMY2_rvd28_shift                                                       (28)
#define ISO_DUMMY2_rvd28_mask                                                        (0x10000000)
#define ISO_DUMMY2_rvd28(data)                                                       (0x10000000&((data)<<28))
#define ISO_DUMMY2_rvd28_src(data)                                                   ((0x10000000&(data))>>28)
#define ISO_DUMMY2_get_rvd28(data)                                                   ((0x10000000&(data))>>28)
#define ISO_DUMMY2_rvd27_shift                                                       (27)
#define ISO_DUMMY2_rvd27_mask                                                        (0x08000000)
#define ISO_DUMMY2_rvd27(data)                                                       (0x08000000&((data)<<27))
#define ISO_DUMMY2_rvd27_src(data)                                                   ((0x08000000&(data))>>27)
#define ISO_DUMMY2_get_rvd27(data)                                                   ((0x08000000&(data))>>27)
#define ISO_DUMMY2_rvd26_shift                                                       (26)
#define ISO_DUMMY2_rvd26_mask                                                        (0x04000000)
#define ISO_DUMMY2_rvd26(data)                                                       (0x04000000&((data)<<26))
#define ISO_DUMMY2_rvd26_src(data)                                                   ((0x04000000&(data))>>26)
#define ISO_DUMMY2_get_rvd26(data)                                                   ((0x04000000&(data))>>26)
#define ISO_DUMMY2_rvd25_shift                                                       (25)
#define ISO_DUMMY2_rvd25_mask                                                        (0x02000000)
#define ISO_DUMMY2_rvd25(data)                                                       (0x02000000&((data)<<25))
#define ISO_DUMMY2_rvd25_src(data)                                                   ((0x02000000&(data))>>25)
#define ISO_DUMMY2_get_rvd25(data)                                                   ((0x02000000&(data))>>25)
#define ISO_DUMMY2_rvd24_shift                                                       (24)
#define ISO_DUMMY2_rvd24_mask                                                        (0x01000000)
#define ISO_DUMMY2_rvd24(data)                                                       (0x01000000&((data)<<24))
#define ISO_DUMMY2_rvd24_src(data)                                                   ((0x01000000&(data))>>24)
#define ISO_DUMMY2_get_rvd24(data)                                                   ((0x01000000&(data))>>24)
#define ISO_DUMMY2_rvd23_shift                                                       (23)
#define ISO_DUMMY2_rvd23_mask                                                        (0x00800000)
#define ISO_DUMMY2_rvd23(data)                                                       (0x00800000&((data)<<23))
#define ISO_DUMMY2_rvd23_src(data)                                                   ((0x00800000&(data))>>23)
#define ISO_DUMMY2_get_rvd23(data)                                                   ((0x00800000&(data))>>23)
#define ISO_DUMMY2_rvd22_shift                                                       (22)
#define ISO_DUMMY2_rvd22_mask                                                        (0x00400000)
#define ISO_DUMMY2_rvd22(data)                                                       (0x00400000&((data)<<22))
#define ISO_DUMMY2_rvd22_src(data)                                                   ((0x00400000&(data))>>22)
#define ISO_DUMMY2_get_rvd22(data)                                                   ((0x00400000&(data))>>22)
#define ISO_DUMMY2_rvd21_shift                                                       (21)
#define ISO_DUMMY2_rvd21_mask                                                        (0x00200000)
#define ISO_DUMMY2_rvd21(data)                                                       (0x00200000&((data)<<21))
#define ISO_DUMMY2_rvd21_src(data)                                                   ((0x00200000&(data))>>21)
#define ISO_DUMMY2_get_rvd21(data)                                                   ((0x00200000&(data))>>21)
#define ISO_DUMMY2_rvd20_shift                                                       (20)
#define ISO_DUMMY2_rvd20_mask                                                        (0x00100000)
#define ISO_DUMMY2_rvd20(data)                                                       (0x00100000&((data)<<20))
#define ISO_DUMMY2_rvd20_src(data)                                                   ((0x00100000&(data))>>20)
#define ISO_DUMMY2_get_rvd20(data)                                                   ((0x00100000&(data))>>20)
#define ISO_DUMMY2_rvd19_shift                                                       (19)
#define ISO_DUMMY2_rvd19_mask                                                        (0x00080000)
#define ISO_DUMMY2_rvd19(data)                                                       (0x00080000&((data)<<19))
#define ISO_DUMMY2_rvd19_src(data)                                                   ((0x00080000&(data))>>19)
#define ISO_DUMMY2_get_rvd19(data)                                                   ((0x00080000&(data))>>19)
#define ISO_DUMMY2_rvd18_shift                                                       (18)
#define ISO_DUMMY2_rvd18_mask                                                        (0x00040000)
#define ISO_DUMMY2_rvd18(data)                                                       (0x00040000&((data)<<18))
#define ISO_DUMMY2_rvd18_src(data)                                                   ((0x00040000&(data))>>18)
#define ISO_DUMMY2_get_rvd18(data)                                                   ((0x00040000&(data))>>18)
#define ISO_DUMMY2_rvd17_shift                                                       (17)
#define ISO_DUMMY2_rvd17_mask                                                        (0x00020000)
#define ISO_DUMMY2_rvd17(data)                                                       (0x00020000&((data)<<17))
#define ISO_DUMMY2_rvd17_src(data)                                                   ((0x00020000&(data))>>17)
#define ISO_DUMMY2_get_rvd17(data)                                                   ((0x00020000&(data))>>17)
#define ISO_DUMMY2_rvd16_shift                                                       (16)
#define ISO_DUMMY2_rvd16_mask                                                        (0x00010000)
#define ISO_DUMMY2_rvd16(data)                                                       (0x00010000&((data)<<16))
#define ISO_DUMMY2_rvd16_src(data)                                                   ((0x00010000&(data))>>16)
#define ISO_DUMMY2_get_rvd16(data)                                                   ((0x00010000&(data))>>16)
#define ISO_DUMMY2_rvd15_shift                                                       (15)
#define ISO_DUMMY2_rvd15_mask                                                        (0x00008000)
#define ISO_DUMMY2_rvd15(data)                                                       (0x00008000&((data)<<15))
#define ISO_DUMMY2_rvd15_src(data)                                                   ((0x00008000&(data))>>15)
#define ISO_DUMMY2_get_rvd15(data)                                                   ((0x00008000&(data))>>15)
#define ISO_DUMMY2_rvd14_shift                                                       (14)
#define ISO_DUMMY2_rvd14_mask                                                        (0x00004000)
#define ISO_DUMMY2_rvd14(data)                                                       (0x00004000&((data)<<14))
#define ISO_DUMMY2_rvd14_src(data)                                                   ((0x00004000&(data))>>14)
#define ISO_DUMMY2_get_rvd14(data)                                                   ((0x00004000&(data))>>14)
#define ISO_DUMMY2_rvd13_shift                                                       (13)
#define ISO_DUMMY2_rvd13_mask                                                        (0x00002000)
#define ISO_DUMMY2_rvd13(data)                                                       (0x00002000&((data)<<13))
#define ISO_DUMMY2_rvd13_src(data)                                                   ((0x00002000&(data))>>13)
#define ISO_DUMMY2_get_rvd13(data)                                                   ((0x00002000&(data))>>13)
#define ISO_DUMMY2_rvd12_shift                                                       (12)
#define ISO_DUMMY2_rvd12_mask                                                        (0x00001000)
#define ISO_DUMMY2_rvd12(data)                                                       (0x00001000&((data)<<12))
#define ISO_DUMMY2_rvd12_src(data)                                                   ((0x00001000&(data))>>12)
#define ISO_DUMMY2_get_rvd12(data)                                                   ((0x00001000&(data))>>12)
#define ISO_DUMMY2_rvd11_shift                                                       (11)
#define ISO_DUMMY2_rvd11_mask                                                        (0x00000800)
#define ISO_DUMMY2_rvd11(data)                                                       (0x00000800&((data)<<11))
#define ISO_DUMMY2_rvd11_src(data)                                                   ((0x00000800&(data))>>11)
#define ISO_DUMMY2_get_rvd11(data)                                                   ((0x00000800&(data))>>11)
#define ISO_DUMMY2_rvd10_shift                                                       (10)
#define ISO_DUMMY2_rvd10_mask                                                        (0x00000400)
#define ISO_DUMMY2_rvd10(data)                                                       (0x00000400&((data)<<10))
#define ISO_DUMMY2_rvd10_src(data)                                                   ((0x00000400&(data))>>10)
#define ISO_DUMMY2_get_rvd10(data)                                                   ((0x00000400&(data))>>10)
#define ISO_DUMMY2_rvd9_shift                                                        (9)
#define ISO_DUMMY2_rvd9_mask                                                         (0x00000200)
#define ISO_DUMMY2_rvd9(data)                                                        (0x00000200&((data)<<9))
#define ISO_DUMMY2_rvd9_src(data)                                                    ((0x00000200&(data))>>9)
#define ISO_DUMMY2_get_rvd9(data)                                                    ((0x00000200&(data))>>9)
#define ISO_DUMMY2_rvd8_shift                                                        (8)
#define ISO_DUMMY2_rvd8_mask                                                         (0x00000100)
#define ISO_DUMMY2_rvd8(data)                                                        (0x00000100&((data)<<8))
#define ISO_DUMMY2_rvd8_src(data)                                                    ((0x00000100&(data))>>8)
#define ISO_DUMMY2_get_rvd8(data)                                                    ((0x00000100&(data))>>8)
#define ISO_DUMMY2_rvd7_shift                                                        (7)
#define ISO_DUMMY2_rvd7_mask                                                         (0x00000080)
#define ISO_DUMMY2_rvd7(data)                                                        (0x00000080&((data)<<7))
#define ISO_DUMMY2_rvd7_src(data)                                                    ((0x00000080&(data))>>7)
#define ISO_DUMMY2_get_rvd7(data)                                                    ((0x00000080&(data))>>7)
#define ISO_DUMMY2_rvd6_shift                                                        (6)
#define ISO_DUMMY2_rvd6_mask                                                         (0x00000040)
#define ISO_DUMMY2_rvd6(data)                                                        (0x00000040&((data)<<6))
#define ISO_DUMMY2_rvd6_src(data)                                                    ((0x00000040&(data))>>6)
#define ISO_DUMMY2_get_rvd6(data)                                                    ((0x00000040&(data))>>6)
#define ISO_DUMMY2_rvd5_shift                                                        (5)
#define ISO_DUMMY2_rvd5_mask                                                         (0x00000020)
#define ISO_DUMMY2_rvd5(data)                                                        (0x00000020&((data)<<5))
#define ISO_DUMMY2_rvd5_src(data)                                                    ((0x00000020&(data))>>5)
#define ISO_DUMMY2_get_rvd5(data)                                                    ((0x00000020&(data))>>5)
#define ISO_DUMMY2_rvd4_shift                                                        (4)
#define ISO_DUMMY2_rvd4_mask                                                         (0x00000010)
#define ISO_DUMMY2_rvd4(data)                                                        (0x00000010&((data)<<4))
#define ISO_DUMMY2_rvd4_src(data)                                                    ((0x00000010&(data))>>4)
#define ISO_DUMMY2_get_rvd4(data)                                                    ((0x00000010&(data))>>4)
#define ISO_DUMMY2_rvd3_shift                                                        (3)
#define ISO_DUMMY2_rvd3_mask                                                         (0x00000008)
#define ISO_DUMMY2_rvd3(data)                                                        (0x00000008&((data)<<3))
#define ISO_DUMMY2_rvd3_src(data)                                                    ((0x00000008&(data))>>3)
#define ISO_DUMMY2_get_rvd3(data)                                                    ((0x00000008&(data))>>3)
#define ISO_DUMMY2_rvd2_shift                                                        (2)
#define ISO_DUMMY2_rvd2_mask                                                         (0x00000004)
#define ISO_DUMMY2_rvd2(data)                                                        (0x00000004&((data)<<2))
#define ISO_DUMMY2_rvd2_src(data)                                                    ((0x00000004&(data))>>2)
#define ISO_DUMMY2_get_rvd2(data)                                                    ((0x00000004&(data))>>2)
#define ISO_DUMMY2_rvd1_shift                                                        (1)
#define ISO_DUMMY2_rvd1_mask                                                         (0x00000002)
#define ISO_DUMMY2_rvd1(data)                                                        (0x00000002&((data)<<1))
#define ISO_DUMMY2_rvd1_src(data)                                                    ((0x00000002&(data))>>1)
#define ISO_DUMMY2_get_rvd1(data)                                                    ((0x00000002&(data))>>1)
#define ISO_DUMMY2_rvd0_shift                                                        (0)
#define ISO_DUMMY2_rvd0_mask                                                         (0x00000001)
#define ISO_DUMMY2_rvd0(data)                                                        (0x00000001&((data)<<0))
#define ISO_DUMMY2_rvd0_src(data)                                                    ((0x00000001&(data))>>0)
#define ISO_DUMMY2_get_rvd0(data)                                                    ((0x00000001&(data))>>0)


#define ISO_POWERCUT_ETN                                                             0x9800705C
#define ISO_POWERCUT_ETN_reg_addr                                                    "0x9800705C"
#define ISO_POWERCUT_ETN_reg                                                         0x9800705C
#define set_ISO_POWERCUT_ETN_reg(data)   (*((volatile unsigned int*) ISO_POWERCUT_ETN_reg)=data)
#define get_ISO_POWERCUT_ETN_reg   (*((volatile unsigned int*) ISO_POWERCUT_ETN_reg))
#define ISO_POWERCUT_ETN_inst_adr                                                    "0x0017"
#define ISO_POWERCUT_ETN_inst                                                        0x0017
#define ISO_POWERCUT_ETN_sel_xtal25m_cen_l_shift                                     (11)
#define ISO_POWERCUT_ETN_sel_xtal25m_cen_l_mask                                      (0x00000800)
#define ISO_POWERCUT_ETN_sel_xtal25m_cen_l(data)                                     (0x00000800&((data)<<11))
#define ISO_POWERCUT_ETN_sel_xtal25m_cen_l_src(data)                                 ((0x00000800&(data))>>11)
#define ISO_POWERCUT_ETN_get_sel_xtal25m_cen_l(data)                                 ((0x00000800&(data))>>11)
#define ISO_POWERCUT_ETN_en_pll_27m_tiehalf_cen_shift                                (10)
#define ISO_POWERCUT_ETN_en_pll_27m_tiehalf_cen_mask                                 (0x00000400)
#define ISO_POWERCUT_ETN_en_pll_27m_tiehalf_cen(data)                                (0x00000400&((data)<<10))
#define ISO_POWERCUT_ETN_en_pll_27m_tiehalf_cen_src(data)                            ((0x00000400&(data))>>10)
#define ISO_POWERCUT_ETN_get_en_pll_27m_tiehalf_cen(data)                            ((0x00000400&(data))>>10)
#define ISO_POWERCUT_ETN_pow_ldo_27m_pll_cen_shift                                   (9)
#define ISO_POWERCUT_ETN_pow_ldo_27m_pll_cen_mask                                    (0x00000200)
#define ISO_POWERCUT_ETN_pow_ldo_27m_pll_cen(data)                                   (0x00000200&((data)<<9))
#define ISO_POWERCUT_ETN_pow_ldo_27m_pll_cen_src(data)                               ((0x00000200&(data))>>9)
#define ISO_POWERCUT_ETN_get_pow_ldo_27m_pll_cen(data)                               ((0x00000200&(data))>>9)
#define ISO_POWERCUT_ETN_pow_pll_27m_en_cen_shift                                    (8)
#define ISO_POWERCUT_ETN_pow_pll_27m_en_cen_mask                                     (0x00000100)
#define ISO_POWERCUT_ETN_pow_pll_27m_en_cen(data)                                    (0x00000100&((data)<<8))
#define ISO_POWERCUT_ETN_pow_pll_27m_en_cen_src(data)                                ((0x00000100&(data))>>8)
#define ISO_POWERCUT_ETN_get_pow_pll_27m_en_cen(data)                                ((0x00000100&(data))>>8)
#define ISO_POWERCUT_ETN_gphy_mdio_outside_ctrl_en_shift                             (5)
#define ISO_POWERCUT_ETN_gphy_mdio_outside_ctrl_en_mask                              (0x00000020)
#define ISO_POWERCUT_ETN_gphy_mdio_outside_ctrl_en(data)                             (0x00000020&((data)<<5))
#define ISO_POWERCUT_ETN_gphy_mdio_outside_ctrl_en_src(data)                         ((0x00000020&(data))>>5)
#define ISO_POWERCUT_ETN_get_gphy_mdio_outside_ctrl_en(data)                         ((0x00000020&(data))>>5)
#define ISO_POWERCUT_ETN_etn_gphy_switch_nat_shift                                   (4)
#define ISO_POWERCUT_ETN_etn_gphy_switch_nat_mask                                    (0x00000010)
#define ISO_POWERCUT_ETN_etn_gphy_switch_nat(data)                                   (0x00000010&((data)<<4))
#define ISO_POWERCUT_ETN_etn_gphy_switch_nat_src(data)                               ((0x00000010&(data))>>4)
#define ISO_POWERCUT_ETN_get_etn_gphy_switch_nat(data)                               ((0x00000010&(data))>>4)
#define ISO_POWERCUT_ETN_etn_efuse_default_shift                                     (2)
#define ISO_POWERCUT_ETN_etn_efuse_default_mask                                      (0x00000004)
#define ISO_POWERCUT_ETN_etn_efuse_default(data)                                     (0x00000004&((data)<<2))
#define ISO_POWERCUT_ETN_etn_efuse_default_src(data)                                 ((0x00000004&(data))>>2)
#define ISO_POWERCUT_ETN_get_etn_efuse_default(data)                                 ((0x00000004&(data))>>2)
#define ISO_POWERCUT_ETN_powercut_ana_d2a_isolate_b_shift                            (1)
#define ISO_POWERCUT_ETN_powercut_ana_d2a_isolate_b_mask                             (0x00000002)
#define ISO_POWERCUT_ETN_powercut_ana_d2a_isolate_b(data)                            (0x00000002&((data)<<1))
#define ISO_POWERCUT_ETN_powercut_ana_d2a_isolate_b_src(data)                        ((0x00000002&(data))>>1)
#define ISO_POWERCUT_ETN_get_powercut_ana_d2a_isolate_b(data)                        ((0x00000002&(data))>>1)
#define ISO_POWERCUT_ETN_powercut_ana_a2d_isolate_b_shift                            (0)
#define ISO_POWERCUT_ETN_powercut_ana_a2d_isolate_b_mask                             (0x00000001)
#define ISO_POWERCUT_ETN_powercut_ana_a2d_isolate_b(data)                            (0x00000001&((data)<<0))
#define ISO_POWERCUT_ETN_powercut_ana_a2d_isolate_b_src(data)                        ((0x00000001&(data))>>0)
#define ISO_POWERCUT_ETN_get_powercut_ana_a2d_isolate_b(data)                        ((0x00000001&(data))>>0)


#define ISO_ETN_TESTIO                                                               0x98007060
#define ISO_ETN_TESTIO_reg_addr                                                      "0x98007060"
#define ISO_ETN_TESTIO_reg                                                           0x98007060
#define set_ISO_ETN_TESTIO_reg(data)   (*((volatile unsigned int*) ISO_ETN_TESTIO_reg)=data)
#define get_ISO_ETN_TESTIO_reg   (*((volatile unsigned int*) ISO_ETN_TESTIO_reg))
#define ISO_ETN_TESTIO_inst_adr                                                      "0x0018"
#define ISO_ETN_TESTIO_inst                                                          0x0018
#define ISO_ETN_TESTIO_etn_bpsgphy_mode_shift                                        (1)
#define ISO_ETN_TESTIO_etn_bpsgphy_mode_mask                                         (0x00000002)
#define ISO_ETN_TESTIO_etn_bpsgphy_mode(data)                                        (0x00000002&((data)<<1))
#define ISO_ETN_TESTIO_etn_bpsgphy_mode_src(data)                                    ((0x00000002&(data))>>1)
#define ISO_ETN_TESTIO_get_etn_bpsgphy_mode(data)                                    ((0x00000002&(data))>>1)
#define ISO_ETN_TESTIO_etn_ocd_mode_shift                                            (0)
#define ISO_ETN_TESTIO_etn_ocd_mode_mask                                             (0x00000001)
#define ISO_ETN_TESTIO_etn_ocd_mode(data)                                            (0x00000001&((data)<<0))
#define ISO_ETN_TESTIO_etn_ocd_mode_src(data)                                        ((0x00000001&(data))>>0)
#define ISO_ETN_TESTIO_get_etn_ocd_mode(data)                                        ((0x00000001&(data))>>0)


#define ISO_RESERVED_USE_0                                                           0x98007064
#define ISO_RESERVED_USE_0_reg_addr                                                  "0x98007064"
#define ISO_RESERVED_USE_0_reg                                                       0x98007064
#define set_ISO_RESERVED_USE_0_reg(data)   (*((volatile unsigned int*) ISO_RESERVED_USE_0_reg)=data)
#define get_ISO_RESERVED_USE_0_reg   (*((volatile unsigned int*) ISO_RESERVED_USE_0_reg))
#define ISO_RESERVED_USE_0_inst_adr                                                  "0x0019"
#define ISO_RESERVED_USE_0_inst                                                      0x0019
#define ISO_RESERVED_USE_0_dmy_shift                                                 (0)
#define ISO_RESERVED_USE_0_dmy_mask                                                  (0xFFFFFFFF)
#define ISO_RESERVED_USE_0_dmy(data)                                                 (0xFFFFFFFF&((data)<<0))
#define ISO_RESERVED_USE_0_dmy_src(data)                                             ((0xFFFFFFFF&(data))>>0)
#define ISO_RESERVED_USE_0_get_dmy(data)                                             ((0xFFFFFFFF&(data))>>0)


#define ISO_LPI                                                                      0x98007068
#define ISO_LPI_reg_addr                                                             "0x98007068"
#define ISO_LPI_reg                                                                  0x98007068
#define set_ISO_LPI_reg(data)   (*((volatile unsigned int*) ISO_LPI_reg)=data)
#define get_ISO_LPI_reg   (*((volatile unsigned int*) ISO_LPI_reg))
#define ISO_LPI_inst_adr                                                             "0x001A"
#define ISO_LPI_inst                                                                 0x001A
#define ISO_LPI_timer_shift                                                          (4)
#define ISO_LPI_timer_mask                                                           (0x00000010)
#define ISO_LPI_timer(data)                                                          (0x00000010&((data)<<4))
#define ISO_LPI_timer_src(data)                                                      ((0x00000010&(data))>>4)
#define ISO_LPI_get_timer(data)                                                      ((0x00000010&(data))>>4)
#define ISO_LPI_ir_main_shift                                                        (2)
#define ISO_LPI_ir_main_mask                                                         (0x00000004)
#define ISO_LPI_ir_main(data)                                                        (0x00000004&((data)<<2))
#define ISO_LPI_ir_main_src(data)                                                    ((0x00000004&(data))>>2)
#define ISO_LPI_get_ir_main(data)                                                    ((0x00000004&(data))>>2)
#define ISO_LPI_ir_tx_shift                                                          (1)
#define ISO_LPI_ir_tx_mask                                                           (0x00000002)
#define ISO_LPI_ir_tx(data)                                                          (0x00000002&((data)<<1))
#define ISO_LPI_ir_tx_src(data)                                                      ((0x00000002&(data))>>1)
#define ISO_LPI_get_ir_tx(data)                                                      ((0x00000002&(data))>>1)
#define ISO_LPI_ir_raw_shift                                                         (0)
#define ISO_LPI_ir_raw_mask                                                          (0x00000001)
#define ISO_LPI_ir_raw(data)                                                         (0x00000001&((data)<<0))
#define ISO_LPI_ir_raw_src(data)                                                     ((0x00000001&(data))>>0)
#define ISO_LPI_get_ir_raw(data)                                                     ((0x00000001&(data))>>0)


#define ISO_WD                                                                       0x9800706C
#define ISO_WD_reg_addr                                                              "0x9800706C"
#define ISO_WD_reg                                                                   0x9800706C
#define set_ISO_WD_reg(data)   (*((volatile unsigned int*) ISO_WD_reg)=data)
#define get_ISO_WD_reg   (*((volatile unsigned int*) ISO_WD_reg))
#define ISO_WD_inst_adr                                                              "0x001B"
#define ISO_WD_inst                                                                  0x001B
#define ISO_WD_cnt_wait_pwr_shift                                                    (0)
#define ISO_WD_cnt_wait_pwr_mask                                                     (0x0000FFFF)
#define ISO_WD_cnt_wait_pwr(data)                                                    (0x0000FFFF&((data)<<0))
#define ISO_WD_cnt_wait_pwr_src(data)                                                ((0x0000FFFF&(data))>>0)
#define ISO_WD_get_cnt_wait_pwr(data)                                                ((0x0000FFFF&(data))>>0)


#define ISO_PLL_WDOUT                                                                0x98007070
#define ISO_PLL_WDOUT_reg_addr                                                       "0x98007070"
#define ISO_PLL_WDOUT_reg                                                            0x98007070
#define set_ISO_PLL_WDOUT_reg(data)   (*((volatile unsigned int*) ISO_PLL_WDOUT_reg)=data)
#define get_ISO_PLL_WDOUT_reg   (*((volatile unsigned int*) ISO_PLL_WDOUT_reg))
#define ISO_PLL_WDOUT_inst_adr                                                       "0x001C"
#define ISO_PLL_WDOUT_inst                                                           0x001C
#define ISO_PLL_WDOUT_plletn_wdout_shift                                             (0)
#define ISO_PLL_WDOUT_plletn_wdout_mask                                              (0x00000001)
#define ISO_PLL_WDOUT_plletn_wdout(data)                                             (0x00000001&((data)<<0))
#define ISO_PLL_WDOUT_plletn_wdout_src(data)                                         ((0x00000001&(data))>>0)
#define ISO_PLL_WDOUT_get_plletn_wdout(data)                                         ((0x00000001&(data))>>0)


#define ISO_PLL_ETN                                                                  0x98007074
#define ISO_PLL_ETN_reg_addr                                                         "0x98007074"
#define ISO_PLL_ETN_reg                                                              0x98007074
#define set_ISO_PLL_ETN_reg(data)   (*((volatile unsigned int*) ISO_PLL_ETN_reg)=data)
#define get_ISO_PLL_ETN_reg   (*((volatile unsigned int*) ISO_PLL_ETN_reg))
#define ISO_PLL_ETN_inst_adr                                                         "0x001D"
#define ISO_PLL_ETN_inst                                                             0x001D
#define ISO_PLL_ETN_plletn_oeb_shift                                                 (27)
#define ISO_PLL_ETN_plletn_oeb_mask                                                  (0x08000000)
#define ISO_PLL_ETN_plletn_oeb(data)                                                 (0x08000000&((data)<<27))
#define ISO_PLL_ETN_plletn_oeb_src(data)                                             ((0x08000000&(data))>>27)
#define ISO_PLL_ETN_get_plletn_oeb(data)                                             ((0x08000000&(data))>>27)
#define ISO_PLL_ETN_plletn_rstb_shift                                                (26)
#define ISO_PLL_ETN_plletn_rstb_mask                                                 (0x04000000)
#define ISO_PLL_ETN_plletn_rstb(data)                                                (0x04000000&((data)<<26))
#define ISO_PLL_ETN_plletn_rstb_src(data)                                            ((0x04000000&(data))>>26)
#define ISO_PLL_ETN_get_plletn_rstb(data)                                            ((0x04000000&(data))>>26)
#define ISO_PLL_ETN_plletn_o_shift                                                   (22)
#define ISO_PLL_ETN_plletn_o_mask                                                    (0x03C00000)
#define ISO_PLL_ETN_plletn_o(data)                                                   (0x03C00000&((data)<<22))
#define ISO_PLL_ETN_plletn_o_src(data)                                               ((0x03C00000&(data))>>22)
#define ISO_PLL_ETN_get_plletn_o(data)                                               ((0x03C00000&(data))>>22)
#define ISO_PLL_ETN_plletn_m_shift                                                   (15)
#define ISO_PLL_ETN_plletn_m_mask                                                    (0x003F8000)
#define ISO_PLL_ETN_plletn_m(data)                                                   (0x003F8000&((data)<<15))
#define ISO_PLL_ETN_plletn_m_src(data)                                               ((0x003F8000&(data))>>15)
#define ISO_PLL_ETN_get_plletn_m(data)                                               ((0x003F8000&(data))>>15)
#define ISO_PLL_ETN_plletn_ldo_pow_shift                                             (14)
#define ISO_PLL_ETN_plletn_ldo_pow_mask                                              (0x00004000)
#define ISO_PLL_ETN_plletn_ldo_pow(data)                                             (0x00004000&((data)<<14))
#define ISO_PLL_ETN_plletn_ldo_pow_src(data)                                         ((0x00004000&(data))>>14)
#define ISO_PLL_ETN_get_plletn_ldo_pow(data)                                         ((0x00004000&(data))>>14)
#define ISO_PLL_ETN_plletn_pow_shift                                                 (13)
#define ISO_PLL_ETN_plletn_pow_mask                                                  (0x00002000)
#define ISO_PLL_ETN_plletn_pow(data)                                                 (0x00002000&((data)<<13))
#define ISO_PLL_ETN_plletn_pow_src(data)                                             ((0x00002000&(data))>>13)
#define ISO_PLL_ETN_get_plletn_pow(data)                                             ((0x00002000&(data))>>13)
#define ISO_PLL_ETN_plletn_ldo_sel_shift                                             (11)
#define ISO_PLL_ETN_plletn_ldo_sel_mask                                              (0x00001800)
#define ISO_PLL_ETN_plletn_ldo_sel(data)                                             (0x00001800&((data)<<11))
#define ISO_PLL_ETN_plletn_ldo_sel_src(data)                                         ((0x00001800&(data))>>11)
#define ISO_PLL_ETN_get_plletn_ldo_sel(data)                                         ((0x00001800&(data))>>11)
#define ISO_PLL_ETN_plletn_wdmode_shift                                              (9)
#define ISO_PLL_ETN_plletn_wdmode_mask                                               (0x00000600)
#define ISO_PLL_ETN_plletn_wdmode(data)                                              (0x00000600&((data)<<9))
#define ISO_PLL_ETN_plletn_wdmode_src(data)                                          ((0x00000600&(data))>>9)
#define ISO_PLL_ETN_get_plletn_wdmode(data)                                          ((0x00000600&(data))>>9)
#define ISO_PLL_ETN_plletn_n_shift                                                   (7)
#define ISO_PLL_ETN_plletn_n_mask                                                    (0x00000180)
#define ISO_PLL_ETN_plletn_n(data)                                                   (0x00000180&((data)<<7))
#define ISO_PLL_ETN_plletn_n_src(data)                                               ((0x00000180&(data))>>7)
#define ISO_PLL_ETN_get_plletn_n(data)                                               ((0x00000180&(data))>>7)
#define ISO_PLL_ETN_plletn_lf_rs_shift                                               (5)
#define ISO_PLL_ETN_plletn_lf_rs_mask                                                (0x00000060)
#define ISO_PLL_ETN_plletn_lf_rs(data)                                               (0x00000060&((data)<<5))
#define ISO_PLL_ETN_plletn_lf_rs_src(data)                                           ((0x00000060&(data))>>5)
#define ISO_PLL_ETN_get_plletn_lf_rs(data)                                           ((0x00000060&(data))>>5)
#define ISO_PLL_ETN_plletn_lf_cp_shift                                               (3)
#define ISO_PLL_ETN_plletn_lf_cp_mask                                                (0x00000018)
#define ISO_PLL_ETN_plletn_lf_cp(data)                                               (0x00000018&((data)<<3))
#define ISO_PLL_ETN_plletn_lf_cp_src(data)                                           ((0x00000018&(data))>>3)
#define ISO_PLL_ETN_get_plletn_lf_cp(data)                                           ((0x00000018&(data))>>3)
#define ISO_PLL_ETN_plletn_ip_shift                                                  (0)
#define ISO_PLL_ETN_plletn_ip_mask                                                   (0x00000007)
#define ISO_PLL_ETN_plletn_ip(data)                                                  (0x00000007&((data)<<0))
#define ISO_PLL_ETN_plletn_ip_src(data)                                              ((0x00000007&(data))>>0)
#define ISO_PLL_ETN_get_plletn_ip(data)                                              ((0x00000007&(data))>>0)


#define ISO_RESERVED_USE_1                                                           0x98007078
#define ISO_RESERVED_USE_1_reg_addr                                                  "0x98007078"
#define ISO_RESERVED_USE_1_reg                                                       0x98007078
#define set_ISO_RESERVED_USE_1_reg(data)   (*((volatile unsigned int*) ISO_RESERVED_USE_1_reg)=data)
#define get_ISO_RESERVED_USE_1_reg   (*((volatile unsigned int*) ISO_RESERVED_USE_1_reg))
#define ISO_RESERVED_USE_1_inst_adr                                                  "0x001E"
#define ISO_RESERVED_USE_1_inst                                                      0x001E
#define ISO_RESERVED_USE_1_dmy_shift                                                 (0)
#define ISO_RESERVED_USE_1_dmy_mask                                                  (0xFFFFFFFF)
#define ISO_RESERVED_USE_1_dmy(data)                                                 (0xFFFFFFFF&((data)<<0))
#define ISO_RESERVED_USE_1_dmy_src(data)                                             ((0xFFFFFFFF&(data))>>0)
#define ISO_RESERVED_USE_1_get_dmy(data)                                             ((0xFFFFFFFF&(data))>>0)


#define ISO_RESERVED_USE_2                                                           0x9800707C
#define ISO_RESERVED_USE_2_reg_addr                                                  "0x9800707C"
#define ISO_RESERVED_USE_2_reg                                                       0x9800707C
#define set_ISO_RESERVED_USE_2_reg(data)   (*((volatile unsigned int*) ISO_RESERVED_USE_2_reg)=data)
#define get_ISO_RESERVED_USE_2_reg   (*((volatile unsigned int*) ISO_RESERVED_USE_2_reg))
#define ISO_RESERVED_USE_2_inst_adr                                                  "0x001F"
#define ISO_RESERVED_USE_2_inst                                                      0x001F
#define ISO_RESERVED_USE_2_dmy_shift                                                 (0)
#define ISO_RESERVED_USE_2_dmy_mask                                                  (0xFFFFFFFF)
#define ISO_RESERVED_USE_2_dmy(data)                                                 (0xFFFFFFFF&((data)<<0))
#define ISO_RESERVED_USE_2_dmy_src(data)                                             ((0xFFFFFFFF&(data))>>0)
#define ISO_RESERVED_USE_2_get_dmy(data)                                             ((0xFFFFFFFF&(data))>>0)


#define ISO_I2C1_SDA_DEL                                                             0x98007080
#define ISO_I2C1_SDA_DEL_reg_addr                                                    "0x98007080"
#define ISO_I2C1_SDA_DEL_reg                                                         0x98007080
#define set_ISO_I2C1_SDA_DEL_reg(data)   (*((volatile unsigned int*) ISO_I2C1_SDA_DEL_reg)=data)
#define get_ISO_I2C1_SDA_DEL_reg   (*((volatile unsigned int*) ISO_I2C1_SDA_DEL_reg))
#define ISO_I2C1_SDA_DEL_inst_adr                                                    "0x0020"
#define ISO_I2C1_SDA_DEL_inst                                                        0x0020
#define ISO_I2C1_SDA_DEL_dmy1_shift                                                  (12)
#define ISO_I2C1_SDA_DEL_dmy1_mask                                                   (0xFFFFF000)
#define ISO_I2C1_SDA_DEL_dmy1(data)                                                  (0xFFFFF000&((data)<<12))
#define ISO_I2C1_SDA_DEL_dmy1_src(data)                                              ((0xFFFFF000&(data))>>12)
#define ISO_I2C1_SDA_DEL_get_dmy1(data)                                              ((0xFFFFF000&(data))>>12)
#define ISO_I2C1_SDA_DEL_en_shift                                                    (8)
#define ISO_I2C1_SDA_DEL_en_mask                                                     (0x00000100)
#define ISO_I2C1_SDA_DEL_en(data)                                                    (0x00000100&((data)<<8))
#define ISO_I2C1_SDA_DEL_en_src(data)                                                ((0x00000100&(data))>>8)
#define ISO_I2C1_SDA_DEL_get_en(data)                                                ((0x00000100&(data))>>8)
#define ISO_I2C1_SDA_DEL_sel_shift                                                   (0)
#define ISO_I2C1_SDA_DEL_sel_mask                                                    (0x0000001F)
#define ISO_I2C1_SDA_DEL_sel(data)                                                   (0x0000001F&((data)<<0))
#define ISO_I2C1_SDA_DEL_sel_src(data)                                               ((0x0000001F&(data))>>0)
#define ISO_I2C1_SDA_DEL_get_sel(data)                                               ((0x0000001F&(data))>>0)


#define ISO_I2C0_SDA_DEL                                                             0x98007084
#define ISO_I2C0_SDA_DEL_reg_addr                                                    "0x98007084"
#define ISO_I2C0_SDA_DEL_reg                                                         0x98007084
#define set_ISO_I2C0_SDA_DEL_reg(data)   (*((volatile unsigned int*) ISO_I2C0_SDA_DEL_reg)=data)
#define get_ISO_I2C0_SDA_DEL_reg   (*((volatile unsigned int*) ISO_I2C0_SDA_DEL_reg))
#define ISO_I2C0_SDA_DEL_inst_adr                                                    "0x0021"
#define ISO_I2C0_SDA_DEL_inst                                                        0x0021
#define ISO_I2C0_SDA_DEL_dmy1_shift                                                  (12)
#define ISO_I2C0_SDA_DEL_dmy1_mask                                                   (0xFFFFF000)
#define ISO_I2C0_SDA_DEL_dmy1(data)                                                  (0xFFFFF000&((data)<<12))
#define ISO_I2C0_SDA_DEL_dmy1_src(data)                                              ((0xFFFFF000&(data))>>12)
#define ISO_I2C0_SDA_DEL_get_dmy1(data)                                              ((0xFFFFF000&(data))>>12)
#define ISO_I2C0_SDA_DEL_en_shift                                                    (8)
#define ISO_I2C0_SDA_DEL_en_mask                                                     (0x00000100)
#define ISO_I2C0_SDA_DEL_en(data)                                                    (0x00000100&((data)<<8))
#define ISO_I2C0_SDA_DEL_en_src(data)                                                ((0x00000100&(data))>>8)
#define ISO_I2C0_SDA_DEL_get_en(data)                                                ((0x00000100&(data))>>8)
#define ISO_I2C0_SDA_DEL_sel_shift                                                   (0)
#define ISO_I2C0_SDA_DEL_sel_mask                                                    (0x0000001F)
#define ISO_I2C0_SDA_DEL_sel(data)                                                   (0x0000001F&((data)<<0))
#define ISO_I2C0_SDA_DEL_sel_src(data)                                               ((0x0000001F&(data))>>0)
#define ISO_I2C0_SDA_DEL_get_sel(data)                                               ((0x0000001F&(data))>>0)


#define ISO_SOFT_RESET                                                               0x98007088
#define ISO_SOFT_RESET_reg_addr                                                      "0x98007088"
#define ISO_SOFT_RESET_reg                                                           0x98007088
#define set_ISO_SOFT_RESET_reg(data)   (*((volatile unsigned int*) ISO_SOFT_RESET_reg)=data)
#define get_ISO_SOFT_RESET_reg   (*((volatile unsigned int*) ISO_SOFT_RESET_reg))
#define ISO_SOFT_RESET_inst_adr                                                      "0x0022"
#define ISO_SOFT_RESET_inst                                                          0x0022
#define ISO_SOFT_RESET_rstn_cbus_shift                                               (13)
#define ISO_SOFT_RESET_rstn_cbus_mask                                                (0x00002000)
#define ISO_SOFT_RESET_rstn_cbus(data)                                               (0x00002000&((data)<<13))
#define ISO_SOFT_RESET_rstn_cbus_src(data)                                           ((0x00002000&(data))>>13)
#define ISO_SOFT_RESET_get_rstn_cbus(data)                                           ((0x00002000&(data))>>13)
#define ISO_SOFT_RESET_rstn_i2c_1_shift                                              (12)
#define ISO_SOFT_RESET_rstn_i2c_1_mask                                               (0x00001000)
#define ISO_SOFT_RESET_rstn_i2c_1(data)                                              (0x00001000&((data)<<12))
#define ISO_SOFT_RESET_rstn_i2c_1_src(data)                                          ((0x00001000&(data))>>12)
#define ISO_SOFT_RESET_get_rstn_i2c_1(data)                                          ((0x00001000&(data))>>12)
#define ISO_SOFT_RESET_rstn_i2c_0_shift                                              (11)
#define ISO_SOFT_RESET_rstn_i2c_0_mask                                               (0x00000800)
#define ISO_SOFT_RESET_rstn_i2c_0(data)                                              (0x00000800&((data)<<11))
#define ISO_SOFT_RESET_rstn_i2c_0_src(data)                                          ((0x00000800&(data))>>11)
#define ISO_SOFT_RESET_get_rstn_i2c_0(data)                                          ((0x00000800&(data))>>11)
#define ISO_SOFT_RESET_rstn_gphy_shift                                               (10)
#define ISO_SOFT_RESET_rstn_gphy_mask                                                (0x00000400)
#define ISO_SOFT_RESET_rstn_gphy(data)                                               (0x00000400&((data)<<10))
#define ISO_SOFT_RESET_rstn_gphy_src(data)                                           ((0x00000400&(data))>>10)
#define ISO_SOFT_RESET_get_rstn_gphy(data)                                           ((0x00000400&(data))>>10)
#define ISO_SOFT_RESET_rstn_gmac_shift                                               (9)
#define ISO_SOFT_RESET_rstn_gmac_mask                                                (0x00000200)
#define ISO_SOFT_RESET_rstn_gmac(data)                                               (0x00000200&((data)<<9))
#define ISO_SOFT_RESET_rstn_gmac_src(data)                                           ((0x00000200&(data))>>9)
#define ISO_SOFT_RESET_get_rstn_gmac(data)                                           ((0x00000200&(data))>>9)
#define ISO_SOFT_RESET_rstn_ur0_shift                                                (8)
#define ISO_SOFT_RESET_rstn_ur0_mask                                                 (0x00000100)
#define ISO_SOFT_RESET_rstn_ur0(data)                                                (0x00000100&((data)<<8))
#define ISO_SOFT_RESET_rstn_ur0_src(data)                                            ((0x00000100&(data))>>8)
#define ISO_SOFT_RESET_get_rstn_ur0(data)                                            ((0x00000100&(data))>>8)
#define ISO_SOFT_RESET_rstn_efuse_shift                                              (7)
#define ISO_SOFT_RESET_rstn_efuse_mask                                               (0x00000080)
#define ISO_SOFT_RESET_rstn_efuse(data)                                              (0x00000080&((data)<<7))
#define ISO_SOFT_RESET_rstn_efuse_src(data)                                          ((0x00000080&(data))>>7)
#define ISO_SOFT_RESET_get_rstn_efuse(data)                                          ((0x00000080&(data))>>7)
#define ISO_SOFT_RESET_rstn_cbusrx_shift                                             (6)
#define ISO_SOFT_RESET_rstn_cbusrx_mask                                              (0x00000040)
#define ISO_SOFT_RESET_rstn_cbusrx(data)                                             (0x00000040&((data)<<6))
#define ISO_SOFT_RESET_rstn_cbusrx_src(data)                                         ((0x00000040&(data))>>6)
#define ISO_SOFT_RESET_get_rstn_cbusrx(data)                                         ((0x00000040&(data))>>6)
#define ISO_SOFT_RESET_rstn_cbustx_shift                                             (5)
#define ISO_SOFT_RESET_rstn_cbustx_mask                                              (0x00000020)
#define ISO_SOFT_RESET_rstn_cbustx(data)                                             (0x00000020&((data)<<5))
#define ISO_SOFT_RESET_rstn_cbustx_src(data)                                         ((0x00000020&(data))>>5)
#define ISO_SOFT_RESET_get_rstn_cbustx(data)                                         ((0x00000020&(data))>>5)
#define ISO_SOFT_RESET_rstn_dp_shift                                                 (4)
#define ISO_SOFT_RESET_rstn_dp_mask                                                  (0x00000010)
#define ISO_SOFT_RESET_rstn_dp(data)                                                 (0x00000010&((data)<<4))
#define ISO_SOFT_RESET_rstn_dp_src(data)                                             ((0x00000010&(data))>>4)
#define ISO_SOFT_RESET_get_rstn_dp(data)                                             ((0x00000010&(data))>>4)
#define ISO_SOFT_RESET_rstn_cec1_shift                                               (3)
#define ISO_SOFT_RESET_rstn_cec1_mask                                                (0x00000008)
#define ISO_SOFT_RESET_rstn_cec1(data)                                               (0x00000008&((data)<<3))
#define ISO_SOFT_RESET_rstn_cec1_src(data)                                           ((0x00000008&(data))>>3)
#define ISO_SOFT_RESET_get_rstn_cec1(data)                                           ((0x00000008&(data))>>3)
#define ISO_SOFT_RESET_rstn_cec0_shift                                               (2)
#define ISO_SOFT_RESET_rstn_cec0_mask                                                (0x00000004)
#define ISO_SOFT_RESET_rstn_cec0(data)                                               (0x00000004&((data)<<2))
#define ISO_SOFT_RESET_rstn_cec0_src(data)                                           ((0x00000004&(data))>>2)
#define ISO_SOFT_RESET_get_rstn_cec0(data)                                           ((0x00000004&(data))>>2)
#define ISO_SOFT_RESET_rstn_ir_shift                                                 (1)
#define ISO_SOFT_RESET_rstn_ir_mask                                                  (0x00000002)
#define ISO_SOFT_RESET_rstn_ir(data)                                                 (0x00000002&((data)<<1))
#define ISO_SOFT_RESET_rstn_ir_src(data)                                             ((0x00000002&(data))>>1)
#define ISO_SOFT_RESET_get_rstn_ir(data)                                             ((0x00000002&(data))>>1)


#define ISO_CLOCK_ENABLE                                                             0x9800708C
#define ISO_CLOCK_ENABLE_reg_addr                                                    "0x9800708C"
#define ISO_CLOCK_ENABLE_reg                                                         0x9800708C
#define set_ISO_CLOCK_ENABLE_reg(data)   (*((volatile unsigned int*) ISO_CLOCK_ENABLE_reg)=data)
#define get_ISO_CLOCK_ENABLE_reg   (*((volatile unsigned int*) ISO_CLOCK_ENABLE_reg))
#define ISO_CLOCK_ENABLE_inst_adr                                                    "0x0023"
#define ISO_CLOCK_ENABLE_inst                                                        0x0023
#define ISO_CLOCK_ENABLE_clk_en_etn_sys_shift                                        (12)
#define ISO_CLOCK_ENABLE_clk_en_etn_sys_mask                                         (0x00001000)
#define ISO_CLOCK_ENABLE_clk_en_etn_sys(data)                                        (0x00001000&((data)<<12))
#define ISO_CLOCK_ENABLE_clk_en_etn_sys_src(data)                                    ((0x00001000&(data))>>12)
#define ISO_CLOCK_ENABLE_get_clk_en_etn_sys(data)                                    ((0x00001000&(data))>>12)
#define ISO_CLOCK_ENABLE_clk_en_etn_250m_shift                                       (11)
#define ISO_CLOCK_ENABLE_clk_en_etn_250m_mask                                        (0x00000800)
#define ISO_CLOCK_ENABLE_clk_en_etn_250m(data)                                       (0x00000800&((data)<<11))
#define ISO_CLOCK_ENABLE_clk_en_etn_250m_src(data)                                   ((0x00000800&(data))>>11)
#define ISO_CLOCK_ENABLE_get_clk_en_etn_250m(data)                                   ((0x00000800&(data))>>11)
#define ISO_CLOCK_ENABLE_clk_en_i2c1_shift                                           (10)
#define ISO_CLOCK_ENABLE_clk_en_i2c1_mask                                            (0x00000400)
#define ISO_CLOCK_ENABLE_clk_en_i2c1(data)                                           (0x00000400&((data)<<10))
#define ISO_CLOCK_ENABLE_clk_en_i2c1_src(data)                                       ((0x00000400&(data))>>10)
#define ISO_CLOCK_ENABLE_get_clk_en_i2c1(data)                                       ((0x00000400&(data))>>10)
#define ISO_CLOCK_ENABLE_clk_en_i2c0_shift                                           (9)
#define ISO_CLOCK_ENABLE_clk_en_i2c0_mask                                            (0x00000200)
#define ISO_CLOCK_ENABLE_clk_en_i2c0(data)                                           (0x00000200&((data)<<9))
#define ISO_CLOCK_ENABLE_clk_en_i2c0_src(data)                                       ((0x00000200&(data))>>9)
#define ISO_CLOCK_ENABLE_get_clk_en_i2c0(data)                                       ((0x00000200&(data))>>9)
#define ISO_CLOCK_ENABLE_clk_en_misc_ur0_shift                                       (8)
#define ISO_CLOCK_ENABLE_clk_en_misc_ur0_mask                                        (0x00000100)
#define ISO_CLOCK_ENABLE_clk_en_misc_ur0(data)                                       (0x00000100&((data)<<8))
#define ISO_CLOCK_ENABLE_clk_en_misc_ur0_src(data)                                   ((0x00000100&(data))>>8)
#define ISO_CLOCK_ENABLE_get_clk_en_misc_ur0(data)                                   ((0x00000100&(data))>>8)
#define ISO_CLOCK_ENABLE_clk_en_misc_ir_shift                                        (7)
#define ISO_CLOCK_ENABLE_clk_en_misc_ir_mask                                         (0x00000080)
#define ISO_CLOCK_ENABLE_clk_en_misc_ir(data)                                        (0x00000080&((data)<<7))
#define ISO_CLOCK_ENABLE_clk_en_misc_ir_src(data)                                    ((0x00000080&(data))>>7)
#define ISO_CLOCK_ENABLE_get_clk_en_misc_ir(data)                                    ((0x00000080&(data))>>7)
#define ISO_CLOCK_ENABLE_clk_en_cbus_osc_shift                                       (6)
#define ISO_CLOCK_ENABLE_clk_en_cbus_osc_mask                                        (0x00000040)
#define ISO_CLOCK_ENABLE_clk_en_cbus_osc(data)                                       (0x00000040&((data)<<6))
#define ISO_CLOCK_ENABLE_clk_en_cbus_osc_src(data)                                   ((0x00000040&(data))>>6)
#define ISO_CLOCK_ENABLE_get_clk_en_cbus_osc(data)                                   ((0x00000040&(data))>>6)
#define ISO_CLOCK_ENABLE_clk_en_cbus_sys_shift                                       (5)
#define ISO_CLOCK_ENABLE_clk_en_cbus_sys_mask                                        (0x00000020)
#define ISO_CLOCK_ENABLE_clk_en_cbus_sys(data)                                       (0x00000020&((data)<<5))
#define ISO_CLOCK_ENABLE_clk_en_cbus_sys_src(data)                                   ((0x00000020&(data))>>5)
#define ISO_CLOCK_ENABLE_get_clk_en_cbus_sys(data)                                   ((0x00000020&(data))>>5)
#define ISO_CLOCK_ENABLE_clk_en_cbustx_sys_shift                                     (4)
#define ISO_CLOCK_ENABLE_clk_en_cbustx_sys_mask                                      (0x00000010)
#define ISO_CLOCK_ENABLE_clk_en_cbustx_sys(data)                                     (0x00000010&((data)<<4))
#define ISO_CLOCK_ENABLE_clk_en_cbustx_sys_src(data)                                 ((0x00000010&(data))>>4)
#define ISO_CLOCK_ENABLE_get_clk_en_cbustx_sys(data)                                 ((0x00000010&(data))>>4)
#define ISO_CLOCK_ENABLE_clk_en_cbusrx_sys_shift                                     (3)
#define ISO_CLOCK_ENABLE_clk_en_cbusrx_sys_mask                                      (0x00000008)
#define ISO_CLOCK_ENABLE_clk_en_cbusrx_sys(data)                                     (0x00000008&((data)<<3))
#define ISO_CLOCK_ENABLE_clk_en_cbusrx_sys_src(data)                                 ((0x00000008&(data))>>3)
#define ISO_CLOCK_ENABLE_get_clk_en_cbusrx_sys(data)                                 ((0x00000008&(data))>>3)
#define ISO_CLOCK_ENABLE_clk_en_misc_cec0_shift                                      (2)
#define ISO_CLOCK_ENABLE_clk_en_misc_cec0_mask                                       (0x00000004)
#define ISO_CLOCK_ENABLE_clk_en_misc_cec0(data)                                      (0x00000004&((data)<<2))
#define ISO_CLOCK_ENABLE_clk_en_misc_cec0_src(data)                                  ((0x00000004&(data))>>2)
#define ISO_CLOCK_ENABLE_get_clk_en_misc_cec0(data)                                  ((0x00000004&(data))>>2)
#define ISO_CLOCK_ENABLE_clk_en_misc_mix_shift                                       (0)
#define ISO_CLOCK_ENABLE_clk_en_misc_mix_mask                                        (0x00000001)
#define ISO_CLOCK_ENABLE_clk_en_misc_mix(data)                                       (0x00000001&((data)<<0))
#define ISO_CLOCK_ENABLE_clk_en_misc_mix_src(data)                                   ((0x00000001&(data))>>0)
#define ISO_CLOCK_ENABLE_get_clk_en_misc_mix(data)                                   ((0x00000001&(data))>>0)


#define ISO_DC_0                                                                     0x98007090
#define ISO_DC_0_reg_addr                                                            "0x98007090"
#define ISO_DC_0_reg                                                                 0x98007090
#define set_ISO_DC_0_reg(data)   (*((volatile unsigned int*) ISO_DC_0_reg)=data)
#define get_ISO_DC_0_reg   (*((volatile unsigned int*) ISO_DC_0_reg))
#define ISO_DC_0_inst_adr                                                            "0x0024"
#define ISO_DC_0_inst                                                                0x0024
#define ISO_DC_0_rd_only_0_en_shift                                                  (24)
#define ISO_DC_0_rd_only_0_en_mask                                                   (0x01000000)
#define ISO_DC_0_rd_only_0_en(data)                                                  (0x01000000&((data)<<24))
#define ISO_DC_0_rd_only_0_en_src(data)                                              ((0x01000000&(data))>>24)
#define ISO_DC_0_get_rd_only_0_en(data)                                              ((0x01000000&(data))>>24)
#define ISO_DC_0_blk_protect_0_wpro_en_shift                                         (21)
#define ISO_DC_0_blk_protect_0_wpro_en_mask                                          (0x00200000)
#define ISO_DC_0_blk_protect_0_wpro_en(data)                                         (0x00200000&((data)<<21))
#define ISO_DC_0_blk_protect_0_wpro_en_src(data)                                     ((0x00200000&(data))>>21)
#define ISO_DC_0_get_blk_protect_0_wpro_en(data)                                     ((0x00200000&(data))>>21)
#define ISO_DC_0_blk_protect_0_en_shift                                              (18)
#define ISO_DC_0_blk_protect_0_en_mask                                               (0x00040000)
#define ISO_DC_0_blk_protect_0_en(data)                                              (0x00040000&((data)<<18))
#define ISO_DC_0_blk_protect_0_en_src(data)                                          ((0x00040000&(data))>>18)
#define ISO_DC_0_get_blk_protect_0_en(data)                                          ((0x00040000&(data))>>18)
#define ISO_DC_0_protect_0_wpro_en_shift                                             (9)
#define ISO_DC_0_protect_0_wpro_en_mask                                              (0x00000200)
#define ISO_DC_0_protect_0_wpro_en(data)                                             (0x00000200&((data)<<9))
#define ISO_DC_0_protect_0_wpro_en_src(data)                                         ((0x00000200&(data))>>9)
#define ISO_DC_0_get_protect_0_wpro_en(data)                                         ((0x00000200&(data))>>9)
#define ISO_DC_0_protect_0_en_shift                                                  (0)
#define ISO_DC_0_protect_0_en_mask                                                   (0x00000001)
#define ISO_DC_0_protect_0_en(data)                                                  (0x00000001&((data)<<0))
#define ISO_DC_0_protect_0_en_src(data)                                              ((0x00000001&(data))>>0)
#define ISO_DC_0_get_protect_0_en(data)                                              ((0x00000001&(data))>>0)


#define ISO_DC_1                                                                     0x98007094
#define ISO_DC_1_reg_addr                                                            "0x98007094"
#define ISO_DC_1_reg                                                                 0x98007094
#define set_ISO_DC_1_reg(data)   (*((volatile unsigned int*) ISO_DC_1_reg)=data)
#define get_ISO_DC_1_reg   (*((volatile unsigned int*) ISO_DC_1_reg))
#define ISO_DC_1_inst_adr                                                            "0x0025"
#define ISO_DC_1_inst                                                                0x0025
#define ISO_DC_1_mem_saddr0_shift                                                    (10)
#define ISO_DC_1_mem_saddr0_mask                                                     (0xFFFFFC00)
#define ISO_DC_1_mem_saddr0(data)                                                    (0xFFFFFC00&((data)<<10))
#define ISO_DC_1_mem_saddr0_src(data)                                                ((0xFFFFFC00&(data))>>10)
#define ISO_DC_1_get_mem_saddr0(data)                                                ((0xFFFFFC00&(data))>>10)


#define ISO_DC_2                                                                     0x98007098
#define ISO_DC_2_reg_addr                                                            "0x98007098"
#define ISO_DC_2_reg                                                                 0x98007098
#define set_ISO_DC_2_reg(data)   (*((volatile unsigned int*) ISO_DC_2_reg)=data)
#define get_ISO_DC_2_reg   (*((volatile unsigned int*) ISO_DC_2_reg))
#define ISO_DC_2_inst_adr                                                            "0x0026"
#define ISO_DC_2_inst                                                                0x0026
#define ISO_DC_2_mem_eaddr0_shift                                                    (10)
#define ISO_DC_2_mem_eaddr0_mask                                                     (0xFFFFFC00)
#define ISO_DC_2_mem_eaddr0(data)                                                    (0xFFFFFC00&((data)<<10))
#define ISO_DC_2_mem_eaddr0_src(data)                                                ((0xFFFFFC00&(data))>>10)
#define ISO_DC_2_get_mem_eaddr0(data)                                                ((0xFFFFFC00&(data))>>10)


#define ISO_DC_3                                                                     0x9800709C
#define ISO_DC_3_reg_addr                                                            "0x9800709C"
#define ISO_DC_3_reg                                                                 0x9800709C
#define set_ISO_DC_3_reg(data)   (*((volatile unsigned int*) ISO_DC_3_reg)=data)
#define get_ISO_DC_3_reg   (*((volatile unsigned int*) ISO_DC_3_reg))
#define ISO_DC_3_inst_adr                                                            "0x0027"
#define ISO_DC_3_inst                                                                0x0027
#define ISO_DC_3_blk_saddr0_shift                                                    (10)
#define ISO_DC_3_blk_saddr0_mask                                                     (0xFFFFFC00)
#define ISO_DC_3_blk_saddr0(data)                                                    (0xFFFFFC00&((data)<<10))
#define ISO_DC_3_blk_saddr0_src(data)                                                ((0xFFFFFC00&(data))>>10)
#define ISO_DC_3_get_blk_saddr0(data)                                                ((0xFFFFFC00&(data))>>10)


#define ISO_DC_4                                                                     0x980070A0
#define ISO_DC_4_reg_addr                                                            "0x980070A0"
#define ISO_DC_4_reg                                                                 0x980070A0
#define set_ISO_DC_4_reg(data)   (*((volatile unsigned int*) ISO_DC_4_reg)=data)
#define get_ISO_DC_4_reg   (*((volatile unsigned int*) ISO_DC_4_reg))
#define ISO_DC_4_inst_adr                                                            "0x0028"
#define ISO_DC_4_inst                                                                0x0028
#define ISO_DC_4_blk_eaddr0_shift                                                    (10)
#define ISO_DC_4_blk_eaddr0_mask                                                     (0xFFFFFC00)
#define ISO_DC_4_blk_eaddr0(data)                                                    (0xFFFFFC00&((data)<<10))
#define ISO_DC_4_blk_eaddr0_src(data)                                                ((0xFFFFFC00&(data))>>10)
#define ISO_DC_4_get_blk_eaddr0(data)                                                ((0xFFFFFC00&(data))>>10)


#define ISO_DC_5                                                                     0x980070A4
#define ISO_DC_5_reg_addr                                                            "0x980070A4"
#define ISO_DC_5_reg                                                                 0x980070A4
#define set_ISO_DC_5_reg(data)   (*((volatile unsigned int*) ISO_DC_5_reg)=data)
#define get_ISO_DC_5_reg   (*((volatile unsigned int*) ISO_DC_5_reg))
#define ISO_DC_5_inst_adr                                                            "0x0029"
#define ISO_DC_5_inst                                                                0x0029
#define ISO_DC_5_ro_saddr0_shift                                                     (10)
#define ISO_DC_5_ro_saddr0_mask                                                      (0xFFFFFC00)
#define ISO_DC_5_ro_saddr0(data)                                                     (0xFFFFFC00&((data)<<10))
#define ISO_DC_5_ro_saddr0_src(data)                                                 ((0xFFFFFC00&(data))>>10)
#define ISO_DC_5_get_ro_saddr0(data)                                                 ((0xFFFFFC00&(data))>>10)


#define ISO_DC_6                                                                     0x980070A8
#define ISO_DC_6_reg_addr                                                            "0x980070A8"
#define ISO_DC_6_reg                                                                 0x980070A8
#define set_ISO_DC_6_reg(data)   (*((volatile unsigned int*) ISO_DC_6_reg)=data)
#define get_ISO_DC_6_reg   (*((volatile unsigned int*) ISO_DC_6_reg))
#define ISO_DC_6_inst_adr                                                            "0x002A"
#define ISO_DC_6_inst                                                                0x002A
#define ISO_DC_6_ro_eaddr0_shift                                                     (10)
#define ISO_DC_6_ro_eaddr0_mask                                                      (0xFFFFFC00)
#define ISO_DC_6_ro_eaddr0(data)                                                     (0xFFFFFC00&((data)<<10))
#define ISO_DC_6_ro_eaddr0_src(data)                                                 ((0xFFFFFC00&(data))>>10)
#define ISO_DC_6_get_ro_eaddr0(data)                                                 ((0xFFFFFC00&(data))>>10)


#define ISO_DC_7                                                                     0x980070AC
#define ISO_DC_7_reg_addr                                                            "0x980070AC"
#define ISO_DC_7_reg                                                                 0x980070AC
#define set_ISO_DC_7_reg(data)   (*((volatile unsigned int*) ISO_DC_7_reg)=data)
#define get_ISO_DC_7_reg   (*((volatile unsigned int*) ISO_DC_7_reg))
#define ISO_DC_7_inst_adr                                                            "0x002B"
#define ISO_DC_7_inst                                                                0x002B
#define ISO_DC_7_md_tee_protect_en_shift                                             (24)
#define ISO_DC_7_md_tee_protect_en_mask                                              (0x01000000)
#define ISO_DC_7_md_tee_protect_en(data)                                             (0x01000000&((data)<<24))
#define ISO_DC_7_md_tee_protect_en_src(data)                                         ((0x01000000&(data))>>24)
#define ISO_DC_7_get_md_tee_protect_en(data)                                         ((0x01000000&(data))>>24)
#define ISO_DC_7_cp_tee_protect_en_shift                                             (16)
#define ISO_DC_7_cp_tee_protect_en_mask                                              (0x00010000)
#define ISO_DC_7_cp_tee_protect_en(data)                                             (0x00010000&((data)<<16))
#define ISO_DC_7_cp_tee_protect_en_src(data)                                         ((0x00010000&(data))>>16)
#define ISO_DC_7_get_cp_tee_protect_en(data)                                         ((0x00010000&(data))>>16)
#define ISO_DC_7_vo_protect_en_shift                                                 (8)
#define ISO_DC_7_vo_protect_en_mask                                                  (0x00000100)
#define ISO_DC_7_vo_protect_en(data)                                                 (0x00000100&((data)<<8))
#define ISO_DC_7_vo_protect_en_src(data)                                             ((0x00000100&(data))>>8)
#define ISO_DC_7_get_vo_protect_en(data)                                             ((0x00000100&(data))>>8)
#define ISO_DC_7_tp_tee_protect_en_shift                                             (2)
#define ISO_DC_7_tp_tee_protect_en_mask                                              (0x00000004)
#define ISO_DC_7_tp_tee_protect_en(data)                                             (0x00000004&((data)<<2))
#define ISO_DC_7_tp_tee_protect_en_src(data)                                         ((0x00000004&(data))>>2)
#define ISO_DC_7_get_tp_tee_protect_en(data)                                         ((0x00000004&(data))>>2)
#define ISO_DC_7_cr_tee_protect_en_shift                                             (1)
#define ISO_DC_7_cr_tee_protect_en_mask                                              (0x00000002)
#define ISO_DC_7_cr_tee_protect_en(data)                                             (0x00000002&((data)<<1))
#define ISO_DC_7_cr_tee_protect_en_src(data)                                         ((0x00000002&(data))>>1)
#define ISO_DC_7_get_cr_tee_protect_en(data)                                         ((0x00000002&(data))>>1)
#define ISO_DC_7_nf_tee_protect_en_shift                                             (0)
#define ISO_DC_7_nf_tee_protect_en_mask                                              (0x00000001)
#define ISO_DC_7_nf_tee_protect_en(data)                                             (0x00000001&((data)<<0))
#define ISO_DC_7_nf_tee_protect_en_src(data)                                         ((0x00000001&(data))>>0)
#define ISO_DC_7_get_nf_tee_protect_en(data)                                         ((0x00000001&(data))>>0)


#define ISO_DC_8                                                                     0x980070B0
#define ISO_DC_8_reg_addr                                                            "0x980070B0"
#define ISO_DC_8_reg                                                                 0x980070B0
#define set_ISO_DC_8_reg(data)   (*((volatile unsigned int*) ISO_DC_8_reg)=data)
#define get_ISO_DC_8_reg   (*((volatile unsigned int*) ISO_DC_8_reg))
#define ISO_DC_8_inst_adr                                                            "0x002C"
#define ISO_DC_8_inst                                                                0x002C
#define ISO_DC_8_scpu_tee_protect_en_shift                                           (24)
#define ISO_DC_8_scpu_tee_protect_en_mask                                            (0x01000000)
#define ISO_DC_8_scpu_tee_protect_en(data)                                           (0x01000000&((data)<<24))
#define ISO_DC_8_scpu_tee_protect_en_src(data)                                       ((0x01000000&(data))>>24)
#define ISO_DC_8_get_scpu_tee_protect_en(data)                                       ((0x01000000&(data))>>24)
#define ISO_DC_8_acpu_protect_en_shift                                               (16)
#define ISO_DC_8_acpu_protect_en_mask                                                (0x00010000)
#define ISO_DC_8_acpu_protect_en(data)                                               (0x00010000&((data)<<16))
#define ISO_DC_8_acpu_protect_en_src(data)                                           ((0x00010000&(data))>>16)
#define ISO_DC_8_get_acpu_protect_en(data)                                           ((0x00010000&(data))>>16)
#define ISO_DC_8_video_protect_en_shift                                              (8)
#define ISO_DC_8_video_protect_en_mask                                               (0x00000100)
#define ISO_DC_8_video_protect_en(data)                                              (0x00000100&((data)<<8))
#define ISO_DC_8_video_protect_en_src(data)                                          ((0x00000100&(data))>>8)
#define ISO_DC_8_get_video_protect_en(data)                                          ((0x00000100&(data))>>8)
#define ISO_DC_8_audio_protect_en_shift                                              (0)
#define ISO_DC_8_audio_protect_en_mask                                               (0x00000001)
#define ISO_DC_8_audio_protect_en(data)                                              (0x00000001&((data)<<0))
#define ISO_DC_8_audio_protect_en_src(data)                                          ((0x00000001&(data))>>0)
#define ISO_DC_8_get_audio_protect_en(data)                                          ((0x00000001&(data))>>0)


#define ISO_DC_9                                                                     0x980070B4
#define ISO_DC_9_reg_addr                                                            "0x980070B4"
#define ISO_DC_9_reg                                                                 0x980070B4
#define set_ISO_DC_9_reg(data)   (*((volatile unsigned int*) ISO_DC_9_reg)=data)
#define get_ISO_DC_9_reg   (*((volatile unsigned int*) ISO_DC_9_reg))
#define ISO_DC_9_inst_adr                                                            "0x002D"
#define ISO_DC_9_inst                                                                0x002D
#define ISO_DC_9_scpu_tee_blk_protect_en_shift                                       (14)
#define ISO_DC_9_scpu_tee_blk_protect_en_mask                                        (0x00004000)
#define ISO_DC_9_scpu_tee_blk_protect_en(data)                                       (0x00004000&((data)<<14))
#define ISO_DC_9_scpu_tee_blk_protect_en_src(data)                                   ((0x00004000&(data))>>14)
#define ISO_DC_9_get_scpu_tee_blk_protect_en(data)                                   ((0x00004000&(data))>>14)
#define ISO_DC_9_acpu_blk_protect_en_shift                                           (12)
#define ISO_DC_9_acpu_blk_protect_en_mask                                            (0x00001000)
#define ISO_DC_9_acpu_blk_protect_en(data)                                           (0x00001000&((data)<<12))
#define ISO_DC_9_acpu_blk_protect_en_src(data)                                       ((0x00001000&(data))>>12)
#define ISO_DC_9_get_acpu_blk_protect_en(data)                                       ((0x00001000&(data))>>12)
#define ISO_DC_9_video_blk_protect_en_shift                                          (10)
#define ISO_DC_9_video_blk_protect_en_mask                                           (0x00000400)
#define ISO_DC_9_video_blk_protect_en(data)                                          (0x00000400&((data)<<10))
#define ISO_DC_9_video_blk_protect_en_src(data)                                      ((0x00000400&(data))>>10)
#define ISO_DC_9_get_video_blk_protect_en(data)                                      ((0x00000400&(data))>>10)
#define ISO_DC_9_audio_blk_protect_en_shift                                          (8)
#define ISO_DC_9_audio_blk_protect_en_mask                                           (0x00000100)
#define ISO_DC_9_audio_blk_protect_en(data)                                          (0x00000100&((data)<<8))
#define ISO_DC_9_audio_blk_protect_en_src(data)                                      ((0x00000100&(data))>>8)
#define ISO_DC_9_get_audio_blk_protect_en(data)                                      ((0x00000100&(data))>>8)
#define ISO_DC_9_md_tee_blk_protect_en_shift                                         (6)
#define ISO_DC_9_md_tee_blk_protect_en_mask                                          (0x00000040)
#define ISO_DC_9_md_tee_blk_protect_en(data)                                         (0x00000040&((data)<<6))
#define ISO_DC_9_md_tee_blk_protect_en_src(data)                                     ((0x00000040&(data))>>6)
#define ISO_DC_9_get_md_tee_blk_protect_en(data)                                     ((0x00000040&(data))>>6)
#define ISO_DC_9_cp_tee_blk_protect_en_shift                                         (4)
#define ISO_DC_9_cp_tee_blk_protect_en_mask                                          (0x00000010)
#define ISO_DC_9_cp_tee_blk_protect_en(data)                                         (0x00000010&((data)<<4))
#define ISO_DC_9_cp_tee_blk_protect_en_src(data)                                     ((0x00000010&(data))>>4)
#define ISO_DC_9_get_cp_tee_blk_protect_en(data)                                     ((0x00000010&(data))>>4)
#define ISO_DC_9_tp_tee_blk_protect_en_shift                                         (3)
#define ISO_DC_9_tp_tee_blk_protect_en_mask                                          (0x00000008)
#define ISO_DC_9_tp_tee_blk_protect_en(data)                                         (0x00000008&((data)<<3))
#define ISO_DC_9_tp_tee_blk_protect_en_src(data)                                     ((0x00000008&(data))>>3)
#define ISO_DC_9_get_tp_tee_blk_protect_en(data)                                     ((0x00000008&(data))>>3)
#define ISO_DC_9_vo_blk_protect_en_shift                                             (2)
#define ISO_DC_9_vo_blk_protect_en_mask                                              (0x00000004)
#define ISO_DC_9_vo_blk_protect_en(data)                                             (0x00000004&((data)<<2))
#define ISO_DC_9_vo_blk_protect_en_src(data)                                         ((0x00000004&(data))>>2)
#define ISO_DC_9_get_vo_blk_protect_en(data)                                         ((0x00000004&(data))>>2)
#define ISO_DC_9_cr_tee_blk_protect_en_shift                                         (1)
#define ISO_DC_9_cr_tee_blk_protect_en_mask                                          (0x00000002)
#define ISO_DC_9_cr_tee_blk_protect_en(data)                                         (0x00000002&((data)<<1))
#define ISO_DC_9_cr_tee_blk_protect_en_src(data)                                     ((0x00000002&(data))>>1)
#define ISO_DC_9_get_cr_tee_blk_protect_en(data)                                     ((0x00000002&(data))>>1)
#define ISO_DC_9_nf_tee_blk_protect_en_shift                                         (0)
#define ISO_DC_9_nf_tee_blk_protect_en_mask                                          (0x00000001)
#define ISO_DC_9_nf_tee_blk_protect_en(data)                                         (0x00000001&((data)<<0))
#define ISO_DC_9_nf_tee_blk_protect_en_src(data)                                     ((0x00000001&(data))>>0)
#define ISO_DC_9_get_nf_tee_blk_protect_en(data)                                     ((0x00000001&(data))>>0)


#define ISO_DC_A                                                                     0x980070B8
#define ISO_DC_A_reg_addr                                                            "0x980070B8"
#define ISO_DC_A_reg                                                                 0x980070B8
#define set_ISO_DC_A_reg(data)   (*((volatile unsigned int*) ISO_DC_A_reg)=data)
#define get_ISO_DC_A_reg   (*((volatile unsigned int*) ISO_DC_A_reg))
#define ISO_DC_A_inst_adr                                                            "0x002E"
#define ISO_DC_A_inst                                                                0x002E
#define ISO_DC_A_scpu_tee_ro_protect_en_shift                                        (28)
#define ISO_DC_A_scpu_tee_ro_protect_en_mask                                         (0x10000000)
#define ISO_DC_A_scpu_tee_ro_protect_en(data)                                        (0x10000000&((data)<<28))
#define ISO_DC_A_scpu_tee_ro_protect_en_src(data)                                    ((0x10000000&(data))>>28)
#define ISO_DC_A_get_scpu_tee_ro_protect_en(data)                                    ((0x10000000&(data))>>28)
#define ISO_DC_A_acpu_ro_protect_en_shift                                            (24)
#define ISO_DC_A_acpu_ro_protect_en_mask                                             (0x01000000)
#define ISO_DC_A_acpu_ro_protect_en(data)                                            (0x01000000&((data)<<24))
#define ISO_DC_A_acpu_ro_protect_en_src(data)                                        ((0x01000000&(data))>>24)
#define ISO_DC_A_get_acpu_ro_protect_en(data)                                        ((0x01000000&(data))>>24)
#define ISO_DC_A_video_ro_protect_en_shift                                           (20)
#define ISO_DC_A_video_ro_protect_en_mask                                            (0x00100000)
#define ISO_DC_A_video_ro_protect_en(data)                                           (0x00100000&((data)<<20))
#define ISO_DC_A_video_ro_protect_en_src(data)                                       ((0x00100000&(data))>>20)
#define ISO_DC_A_get_video_ro_protect_en(data)                                       ((0x00100000&(data))>>20)
#define ISO_DC_A_audio_ro_protect_en_shift                                           (16)
#define ISO_DC_A_audio_ro_protect_en_mask                                            (0x00010000)
#define ISO_DC_A_audio_ro_protect_en(data)                                           (0x00010000&((data)<<16))
#define ISO_DC_A_audio_ro_protect_en_src(data)                                       ((0x00010000&(data))>>16)
#define ISO_DC_A_get_audio_ro_protect_en(data)                                       ((0x00010000&(data))>>16)
#define ISO_DC_A_md_tee_ro_protect_en_shift                                          (12)
#define ISO_DC_A_md_tee_ro_protect_en_mask                                           (0x00001000)
#define ISO_DC_A_md_tee_ro_protect_en(data)                                          (0x00001000&((data)<<12))
#define ISO_DC_A_md_tee_ro_protect_en_src(data)                                      ((0x00001000&(data))>>12)
#define ISO_DC_A_get_md_tee_ro_protect_en(data)                                      ((0x00001000&(data))>>12)
#define ISO_DC_A_cp_tee_ro_protect_en_shift                                          (8)
#define ISO_DC_A_cp_tee_ro_protect_en_mask                                           (0x00000100)
#define ISO_DC_A_cp_tee_ro_protect_en(data)                                          (0x00000100&((data)<<8))
#define ISO_DC_A_cp_tee_ro_protect_en_src(data)                                      ((0x00000100&(data))>>8)
#define ISO_DC_A_get_cp_tee_ro_protect_en(data)                                      ((0x00000100&(data))>>8)
#define ISO_DC_A_vo_ro_protect_en_shift                                              (4)
#define ISO_DC_A_vo_ro_protect_en_mask                                               (0x00000010)
#define ISO_DC_A_vo_ro_protect_en(data)                                              (0x00000010&((data)<<4))
#define ISO_DC_A_vo_ro_protect_en_src(data)                                          ((0x00000010&(data))>>4)
#define ISO_DC_A_get_vo_ro_protect_en(data)                                          ((0x00000010&(data))>>4)
#define ISO_DC_A_tp_tee_ro_protect_en_shift                                          (2)
#define ISO_DC_A_tp_tee_ro_protect_en_mask                                           (0x00000004)
#define ISO_DC_A_tp_tee_ro_protect_en(data)                                          (0x00000004&((data)<<2))
#define ISO_DC_A_tp_tee_ro_protect_en_src(data)                                      ((0x00000004&(data))>>2)
#define ISO_DC_A_get_tp_tee_ro_protect_en(data)                                      ((0x00000004&(data))>>2)
#define ISO_DC_A_cr_tee_ro_protect_en_shift                                          (1)
#define ISO_DC_A_cr_tee_ro_protect_en_mask                                           (0x00000002)
#define ISO_DC_A_cr_tee_ro_protect_en(data)                                          (0x00000002&((data)<<1))
#define ISO_DC_A_cr_tee_ro_protect_en_src(data)                                      ((0x00000002&(data))>>1)
#define ISO_DC_A_get_cr_tee_ro_protect_en(data)                                      ((0x00000002&(data))>>1)
#define ISO_DC_A_nf_tee_ro_protect_en_shift                                          (0)
#define ISO_DC_A_nf_tee_ro_protect_en_mask                                           (0x00000001)
#define ISO_DC_A_nf_tee_ro_protect_en(data)                                          (0x00000001&((data)<<0))
#define ISO_DC_A_nf_tee_ro_protect_en_src(data)                                      ((0x00000001&(data))>>0)
#define ISO_DC_A_get_nf_tee_ro_protect_en(data)                                      ((0x00000001&(data))>>0)


#define ISO_PLL_XTAL_CTRL                                                            0x980070BC
#define ISO_PLL_XTAL_CTRL_reg_addr                                                   "0x980070BC"
#define ISO_PLL_XTAL_CTRL_reg                                                        0x980070BC
#define set_ISO_PLL_XTAL_CTRL_reg(data)   (*((volatile unsigned int*) ISO_PLL_XTAL_CTRL_reg)=data)
#define get_ISO_PLL_XTAL_CTRL_reg   (*((volatile unsigned int*) ISO_PLL_XTAL_CTRL_reg))
#define ISO_PLL_XTAL_CTRL_inst_adr                                                   "0x002F"
#define ISO_PLL_XTAL_CTRL_inst                                                       0x002F
#define ISO_PLL_XTAL_CTRL_xtal_pad_drv_shift                                         (0)
#define ISO_PLL_XTAL_CTRL_xtal_pad_drv_mask                                          (0x00000003)
#define ISO_PLL_XTAL_CTRL_xtal_pad_drv(data)                                         (0x00000003&((data)<<0))
#define ISO_PLL_XTAL_CTRL_xtal_pad_drv_src(data)                                     ((0x00000003&(data))>>0)
#define ISO_PLL_XTAL_CTRL_get_xtal_pad_drv(data)                                     ((0x00000003&(data))>>0)


#define ISO_HDMI_RX                                                                  0x980070C4
#define ISO_HDMI_RX_reg_addr                                                         "0x980070C4"
#define ISO_HDMI_RX_reg                                                              0x980070C4
#define set_ISO_HDMI_RX_reg(data)   (*((volatile unsigned int*) ISO_HDMI_RX_reg)=data)
#define get_ISO_HDMI_RX_reg   (*((volatile unsigned int*) ISO_HDMI_RX_reg))
#define ISO_HDMI_RX_inst_adr                                                         "0x0031"
#define ISO_HDMI_RX_inst                                                             0x0031
#define ISO_HDMI_RX_int_option_shift                                                 (0)
#define ISO_HDMI_RX_int_option_mask                                                  (0x00000001)
#define ISO_HDMI_RX_int_option(data)                                                 (0x00000001&((data)<<0))
#define ISO_HDMI_RX_int_option_src(data)                                             ((0x00000001&(data))>>0)
#define ISO_HDMI_RX_get_int_option(data)                                             ((0x00000001&(data))>>0)


#define ISO_PLL_ETN_OSC                                                              0x980070CC
#define ISO_PLL_ETN_OSC_reg_addr                                                     "0x980070CC"
#define ISO_PLL_ETN_OSC_reg                                                          0x980070CC
#define set_ISO_PLL_ETN_OSC_reg(data)   (*((volatile unsigned int*) ISO_PLL_ETN_OSC_reg)=data)
#define get_ISO_PLL_ETN_OSC_reg   (*((volatile unsigned int*) ISO_PLL_ETN_OSC_reg))
#define ISO_PLL_ETN_OSC_inst_adr                                                     "0x0033"
#define ISO_PLL_ETN_OSC_inst                                                         0x0033
#define ISO_PLL_ETN_OSC_reg_reserve_shift                                            (12)
#define ISO_PLL_ETN_OSC_reg_reserve_mask                                             (0x00003000)
#define ISO_PLL_ETN_OSC_reg_reserve(data)                                            (0x00003000&((data)<<12))
#define ISO_PLL_ETN_OSC_reg_reserve_src(data)                                        ((0x00003000&(data))>>12)
#define ISO_PLL_ETN_OSC_get_reg_reserve(data)                                        ((0x00003000&(data))>>12)
#define ISO_PLL_ETN_OSC_reg_tc_emb_shift                                             (9)
#define ISO_PLL_ETN_OSC_reg_tc_emb_mask                                              (0x00000E00)
#define ISO_PLL_ETN_OSC_reg_tc_emb(data)                                             (0x00000E00&((data)<<9))
#define ISO_PLL_ETN_OSC_reg_tc_emb_src(data)                                         ((0x00000E00&(data))>>9)
#define ISO_PLL_ETN_OSC_get_reg_tc_emb(data)                                         ((0x00000E00&(data))>>9)
#define ISO_PLL_ETN_OSC_reg_fref_sel_shift                                           (8)
#define ISO_PLL_ETN_OSC_reg_fref_sel_mask                                            (0x00000100)
#define ISO_PLL_ETN_OSC_reg_fref_sel(data)                                           (0x00000100&((data)<<8))
#define ISO_PLL_ETN_OSC_reg_fref_sel_src(data)                                       ((0x00000100&(data))>>8)
#define ISO_PLL_ETN_OSC_get_reg_fref_sel(data)                                       ((0x00000100&(data))>>8)
#define ISO_PLL_ETN_OSC_s_emb_shift                                                  (1)
#define ISO_PLL_ETN_OSC_s_emb_mask                                                   (0x000000FE)
#define ISO_PLL_ETN_OSC_s_emb(data)                                                  (0x000000FE&((data)<<1))
#define ISO_PLL_ETN_OSC_s_emb_src(data)                                              ((0x000000FE&(data))>>1)
#define ISO_PLL_ETN_OSC_get_s_emb(data)                                              ((0x000000FE&(data))>>1)
#define ISO_PLL_ETN_OSC_rstb_emb_shift                                               (0)
#define ISO_PLL_ETN_OSC_rstb_emb_mask                                                (0x00000001)
#define ISO_PLL_ETN_OSC_rstb_emb(data)                                               (0x00000001&((data)<<0))
#define ISO_PLL_ETN_OSC_rstb_emb_src(data)                                           ((0x00000001&(data))>>0)
#define ISO_PLL_ETN_OSC_get_rstb_emb(data)                                           ((0x00000001&(data))>>0)


#define ISO_FAST_ISR_GPIO0_A                                                         0x980070E8
#define ISO_FAST_ISR_GPIO0_A_reg_addr                                                "0x980070E8"
#define ISO_FAST_ISR_GPIO0_A_reg                                                     0x980070E8
#define set_ISO_FAST_ISR_GPIO0_A_reg(data)   (*((volatile unsigned int*) ISO_FAST_ISR_GPIO0_A_reg)=data)
#define get_ISO_FAST_ISR_GPIO0_A_reg   (*((volatile unsigned int*) ISO_FAST_ISR_GPIO0_A_reg))
#define ISO_FAST_ISR_GPIO0_A_inst_adr                                                "0x003A"
#define ISO_FAST_ISR_GPIO0_A_inst                                                    0x003A
#define ISO_FAST_ISR_GPIO0_A_int_30_shift                                            (31)
#define ISO_FAST_ISR_GPIO0_A_int_30_mask                                             (0x80000000)
#define ISO_FAST_ISR_GPIO0_A_int_30(data)                                            (0x80000000&((data)<<31))
#define ISO_FAST_ISR_GPIO0_A_int_30_src(data)                                        ((0x80000000&(data))>>31)
#define ISO_FAST_ISR_GPIO0_A_get_int_30(data)                                        ((0x80000000&(data))>>31)
#define ISO_FAST_ISR_GPIO0_A_int_29_shift                                            (30)
#define ISO_FAST_ISR_GPIO0_A_int_29_mask                                             (0x40000000)
#define ISO_FAST_ISR_GPIO0_A_int_29(data)                                            (0x40000000&((data)<<30))
#define ISO_FAST_ISR_GPIO0_A_int_29_src(data)                                        ((0x40000000&(data))>>30)
#define ISO_FAST_ISR_GPIO0_A_get_int_29(data)                                        ((0x40000000&(data))>>30)
#define ISO_FAST_ISR_GPIO0_A_int_28_shift                                            (29)
#define ISO_FAST_ISR_GPIO0_A_int_28_mask                                             (0x20000000)
#define ISO_FAST_ISR_GPIO0_A_int_28(data)                                            (0x20000000&((data)<<29))
#define ISO_FAST_ISR_GPIO0_A_int_28_src(data)                                        ((0x20000000&(data))>>29)
#define ISO_FAST_ISR_GPIO0_A_get_int_28(data)                                        ((0x20000000&(data))>>29)
#define ISO_FAST_ISR_GPIO0_A_int_27_shift                                            (28)
#define ISO_FAST_ISR_GPIO0_A_int_27_mask                                             (0x10000000)
#define ISO_FAST_ISR_GPIO0_A_int_27(data)                                            (0x10000000&((data)<<28))
#define ISO_FAST_ISR_GPIO0_A_int_27_src(data)                                        ((0x10000000&(data))>>28)
#define ISO_FAST_ISR_GPIO0_A_get_int_27(data)                                        ((0x10000000&(data))>>28)
#define ISO_FAST_ISR_GPIO0_A_int_26_shift                                            (27)
#define ISO_FAST_ISR_GPIO0_A_int_26_mask                                             (0x08000000)
#define ISO_FAST_ISR_GPIO0_A_int_26(data)                                            (0x08000000&((data)<<27))
#define ISO_FAST_ISR_GPIO0_A_int_26_src(data)                                        ((0x08000000&(data))>>27)
#define ISO_FAST_ISR_GPIO0_A_get_int_26(data)                                        ((0x08000000&(data))>>27)
#define ISO_FAST_ISR_GPIO0_A_int_25_shift                                            (26)
#define ISO_FAST_ISR_GPIO0_A_int_25_mask                                             (0x04000000)
#define ISO_FAST_ISR_GPIO0_A_int_25(data)                                            (0x04000000&((data)<<26))
#define ISO_FAST_ISR_GPIO0_A_int_25_src(data)                                        ((0x04000000&(data))>>26)
#define ISO_FAST_ISR_GPIO0_A_get_int_25(data)                                        ((0x04000000&(data))>>26)
#define ISO_FAST_ISR_GPIO0_A_int_24_shift                                            (25)
#define ISO_FAST_ISR_GPIO0_A_int_24_mask                                             (0x02000000)
#define ISO_FAST_ISR_GPIO0_A_int_24(data)                                            (0x02000000&((data)<<25))
#define ISO_FAST_ISR_GPIO0_A_int_24_src(data)                                        ((0x02000000&(data))>>25)
#define ISO_FAST_ISR_GPIO0_A_get_int_24(data)                                        ((0x02000000&(data))>>25)
#define ISO_FAST_ISR_GPIO0_A_int_23_shift                                            (24)
#define ISO_FAST_ISR_GPIO0_A_int_23_mask                                             (0x01000000)
#define ISO_FAST_ISR_GPIO0_A_int_23(data)                                            (0x01000000&((data)<<24))
#define ISO_FAST_ISR_GPIO0_A_int_23_src(data)                                        ((0x01000000&(data))>>24)
#define ISO_FAST_ISR_GPIO0_A_get_int_23(data)                                        ((0x01000000&(data))>>24)
#define ISO_FAST_ISR_GPIO0_A_int_22_shift                                            (23)
#define ISO_FAST_ISR_GPIO0_A_int_22_mask                                             (0x00800000)
#define ISO_FAST_ISR_GPIO0_A_int_22(data)                                            (0x00800000&((data)<<23))
#define ISO_FAST_ISR_GPIO0_A_int_22_src(data)                                        ((0x00800000&(data))>>23)
#define ISO_FAST_ISR_GPIO0_A_get_int_22(data)                                        ((0x00800000&(data))>>23)
#define ISO_FAST_ISR_GPIO0_A_int_21_shift                                            (22)
#define ISO_FAST_ISR_GPIO0_A_int_21_mask                                             (0x00400000)
#define ISO_FAST_ISR_GPIO0_A_int_21(data)                                            (0x00400000&((data)<<22))
#define ISO_FAST_ISR_GPIO0_A_int_21_src(data)                                        ((0x00400000&(data))>>22)
#define ISO_FAST_ISR_GPIO0_A_get_int_21(data)                                        ((0x00400000&(data))>>22)
#define ISO_FAST_ISR_GPIO0_A_int_20_shift                                            (21)
#define ISO_FAST_ISR_GPIO0_A_int_20_mask                                             (0x00200000)
#define ISO_FAST_ISR_GPIO0_A_int_20(data)                                            (0x00200000&((data)<<21))
#define ISO_FAST_ISR_GPIO0_A_int_20_src(data)                                        ((0x00200000&(data))>>21)
#define ISO_FAST_ISR_GPIO0_A_get_int_20(data)                                        ((0x00200000&(data))>>21)
#define ISO_FAST_ISR_GPIO0_A_int_19_shift                                            (20)
#define ISO_FAST_ISR_GPIO0_A_int_19_mask                                             (0x00100000)
#define ISO_FAST_ISR_GPIO0_A_int_19(data)                                            (0x00100000&((data)<<20))
#define ISO_FAST_ISR_GPIO0_A_int_19_src(data)                                        ((0x00100000&(data))>>20)
#define ISO_FAST_ISR_GPIO0_A_get_int_19(data)                                        ((0x00100000&(data))>>20)
#define ISO_FAST_ISR_GPIO0_A_int_18_shift                                            (19)
#define ISO_FAST_ISR_GPIO0_A_int_18_mask                                             (0x00080000)
#define ISO_FAST_ISR_GPIO0_A_int_18(data)                                            (0x00080000&((data)<<19))
#define ISO_FAST_ISR_GPIO0_A_int_18_src(data)                                        ((0x00080000&(data))>>19)
#define ISO_FAST_ISR_GPIO0_A_get_int_18(data)                                        ((0x00080000&(data))>>19)
#define ISO_FAST_ISR_GPIO0_A_int_17_shift                                            (18)
#define ISO_FAST_ISR_GPIO0_A_int_17_mask                                             (0x00040000)
#define ISO_FAST_ISR_GPIO0_A_int_17(data)                                            (0x00040000&((data)<<18))
#define ISO_FAST_ISR_GPIO0_A_int_17_src(data)                                        ((0x00040000&(data))>>18)
#define ISO_FAST_ISR_GPIO0_A_get_int_17(data)                                        ((0x00040000&(data))>>18)
#define ISO_FAST_ISR_GPIO0_A_int_16_shift                                            (17)
#define ISO_FAST_ISR_GPIO0_A_int_16_mask                                             (0x00020000)
#define ISO_FAST_ISR_GPIO0_A_int_16(data)                                            (0x00020000&((data)<<17))
#define ISO_FAST_ISR_GPIO0_A_int_16_src(data)                                        ((0x00020000&(data))>>17)
#define ISO_FAST_ISR_GPIO0_A_get_int_16(data)                                        ((0x00020000&(data))>>17)
#define ISO_FAST_ISR_GPIO0_A_int_15_shift                                            (16)
#define ISO_FAST_ISR_GPIO0_A_int_15_mask                                             (0x00010000)
#define ISO_FAST_ISR_GPIO0_A_int_15(data)                                            (0x00010000&((data)<<16))
#define ISO_FAST_ISR_GPIO0_A_int_15_src(data)                                        ((0x00010000&(data))>>16)
#define ISO_FAST_ISR_GPIO0_A_get_int_15(data)                                        ((0x00010000&(data))>>16)
#define ISO_FAST_ISR_GPIO0_A_int_14_shift                                            (15)
#define ISO_FAST_ISR_GPIO0_A_int_14_mask                                             (0x00008000)
#define ISO_FAST_ISR_GPIO0_A_int_14(data)                                            (0x00008000&((data)<<15))
#define ISO_FAST_ISR_GPIO0_A_int_14_src(data)                                        ((0x00008000&(data))>>15)
#define ISO_FAST_ISR_GPIO0_A_get_int_14(data)                                        ((0x00008000&(data))>>15)
#define ISO_FAST_ISR_GPIO0_A_int_13_shift                                            (14)
#define ISO_FAST_ISR_GPIO0_A_int_13_mask                                             (0x00004000)
#define ISO_FAST_ISR_GPIO0_A_int_13(data)                                            (0x00004000&((data)<<14))
#define ISO_FAST_ISR_GPIO0_A_int_13_src(data)                                        ((0x00004000&(data))>>14)
#define ISO_FAST_ISR_GPIO0_A_get_int_13(data)                                        ((0x00004000&(data))>>14)
#define ISO_FAST_ISR_GPIO0_A_int_12_shift                                            (13)
#define ISO_FAST_ISR_GPIO0_A_int_12_mask                                             (0x00002000)
#define ISO_FAST_ISR_GPIO0_A_int_12(data)                                            (0x00002000&((data)<<13))
#define ISO_FAST_ISR_GPIO0_A_int_12_src(data)                                        ((0x00002000&(data))>>13)
#define ISO_FAST_ISR_GPIO0_A_get_int_12(data)                                        ((0x00002000&(data))>>13)
#define ISO_FAST_ISR_GPIO0_A_int_11_shift                                            (12)
#define ISO_FAST_ISR_GPIO0_A_int_11_mask                                             (0x00001000)
#define ISO_FAST_ISR_GPIO0_A_int_11(data)                                            (0x00001000&((data)<<12))
#define ISO_FAST_ISR_GPIO0_A_int_11_src(data)                                        ((0x00001000&(data))>>12)
#define ISO_FAST_ISR_GPIO0_A_get_int_11(data)                                        ((0x00001000&(data))>>12)
#define ISO_FAST_ISR_GPIO0_A_int_10_shift                                            (11)
#define ISO_FAST_ISR_GPIO0_A_int_10_mask                                             (0x00000800)
#define ISO_FAST_ISR_GPIO0_A_int_10(data)                                            (0x00000800&((data)<<11))
#define ISO_FAST_ISR_GPIO0_A_int_10_src(data)                                        ((0x00000800&(data))>>11)
#define ISO_FAST_ISR_GPIO0_A_get_int_10(data)                                        ((0x00000800&(data))>>11)
#define ISO_FAST_ISR_GPIO0_A_int_9_shift                                             (10)
#define ISO_FAST_ISR_GPIO0_A_int_9_mask                                              (0x00000400)
#define ISO_FAST_ISR_GPIO0_A_int_9(data)                                             (0x00000400&((data)<<10))
#define ISO_FAST_ISR_GPIO0_A_int_9_src(data)                                         ((0x00000400&(data))>>10)
#define ISO_FAST_ISR_GPIO0_A_get_int_9(data)                                         ((0x00000400&(data))>>10)
#define ISO_FAST_ISR_GPIO0_A_int_8_shift                                             (9)
#define ISO_FAST_ISR_GPIO0_A_int_8_mask                                              (0x00000200)
#define ISO_FAST_ISR_GPIO0_A_int_8(data)                                             (0x00000200&((data)<<9))
#define ISO_FAST_ISR_GPIO0_A_int_8_src(data)                                         ((0x00000200&(data))>>9)
#define ISO_FAST_ISR_GPIO0_A_get_int_8(data)                                         ((0x00000200&(data))>>9)
#define ISO_FAST_ISR_GPIO0_A_int_7_shift                                             (8)
#define ISO_FAST_ISR_GPIO0_A_int_7_mask                                              (0x00000100)
#define ISO_FAST_ISR_GPIO0_A_int_7(data)                                             (0x00000100&((data)<<8))
#define ISO_FAST_ISR_GPIO0_A_int_7_src(data)                                         ((0x00000100&(data))>>8)
#define ISO_FAST_ISR_GPIO0_A_get_int_7(data)                                         ((0x00000100&(data))>>8)
#define ISO_FAST_ISR_GPIO0_A_int_6_shift                                             (7)
#define ISO_FAST_ISR_GPIO0_A_int_6_mask                                              (0x00000080)
#define ISO_FAST_ISR_GPIO0_A_int_6(data)                                             (0x00000080&((data)<<7))
#define ISO_FAST_ISR_GPIO0_A_int_6_src(data)                                         ((0x00000080&(data))>>7)
#define ISO_FAST_ISR_GPIO0_A_get_int_6(data)                                         ((0x00000080&(data))>>7)
#define ISO_FAST_ISR_GPIO0_A_int_5_shift                                             (6)
#define ISO_FAST_ISR_GPIO0_A_int_5_mask                                              (0x00000040)
#define ISO_FAST_ISR_GPIO0_A_int_5(data)                                             (0x00000040&((data)<<6))
#define ISO_FAST_ISR_GPIO0_A_int_5_src(data)                                         ((0x00000040&(data))>>6)
#define ISO_FAST_ISR_GPIO0_A_get_int_5(data)                                         ((0x00000040&(data))>>6)
#define ISO_FAST_ISR_GPIO0_A_int_4_shift                                             (5)
#define ISO_FAST_ISR_GPIO0_A_int_4_mask                                              (0x00000020)
#define ISO_FAST_ISR_GPIO0_A_int_4(data)                                             (0x00000020&((data)<<5))
#define ISO_FAST_ISR_GPIO0_A_int_4_src(data)                                         ((0x00000020&(data))>>5)
#define ISO_FAST_ISR_GPIO0_A_get_int_4(data)                                         ((0x00000020&(data))>>5)
#define ISO_FAST_ISR_GPIO0_A_int_3_shift                                             (4)
#define ISO_FAST_ISR_GPIO0_A_int_3_mask                                              (0x00000010)
#define ISO_FAST_ISR_GPIO0_A_int_3(data)                                             (0x00000010&((data)<<4))
#define ISO_FAST_ISR_GPIO0_A_int_3_src(data)                                         ((0x00000010&(data))>>4)
#define ISO_FAST_ISR_GPIO0_A_get_int_3(data)                                         ((0x00000010&(data))>>4)
#define ISO_FAST_ISR_GPIO0_A_int_2_shift                                             (3)
#define ISO_FAST_ISR_GPIO0_A_int_2_mask                                              (0x00000008)
#define ISO_FAST_ISR_GPIO0_A_int_2(data)                                             (0x00000008&((data)<<3))
#define ISO_FAST_ISR_GPIO0_A_int_2_src(data)                                         ((0x00000008&(data))>>3)
#define ISO_FAST_ISR_GPIO0_A_get_int_2(data)                                         ((0x00000008&(data))>>3)
#define ISO_FAST_ISR_GPIO0_A_int_1_shift                                             (2)
#define ISO_FAST_ISR_GPIO0_A_int_1_mask                                              (0x00000004)
#define ISO_FAST_ISR_GPIO0_A_int_1(data)                                             (0x00000004&((data)<<2))
#define ISO_FAST_ISR_GPIO0_A_int_1_src(data)                                         ((0x00000004&(data))>>2)
#define ISO_FAST_ISR_GPIO0_A_get_int_1(data)                                         ((0x00000004&(data))>>2)
#define ISO_FAST_ISR_GPIO0_A_int_0_shift                                             (1)
#define ISO_FAST_ISR_GPIO0_A_int_0_mask                                              (0x00000002)
#define ISO_FAST_ISR_GPIO0_A_int_0(data)                                             (0x00000002&((data)<<1))
#define ISO_FAST_ISR_GPIO0_A_int_0_src(data)                                         ((0x00000002&(data))>>1)
#define ISO_FAST_ISR_GPIO0_A_get_int_0(data)                                         ((0x00000002&(data))>>1)
#define ISO_FAST_ISR_GPIO0_A_write_data_shift                                        (0)
#define ISO_FAST_ISR_GPIO0_A_write_data_mask                                         (0x00000001)
#define ISO_FAST_ISR_GPIO0_A_write_data(data)                                        (0x00000001&((data)<<0))
#define ISO_FAST_ISR_GPIO0_A_write_data_src(data)                                    ((0x00000001&(data))>>0)
#define ISO_FAST_ISR_GPIO0_A_get_write_data(data)                                    ((0x00000001&(data))>>0)


#define ISO_FAST_ISR_GPIO1_A                                                         0x980070EC
#define ISO_FAST_ISR_GPIO1_A_reg_addr                                                "0x980070EC"
#define ISO_FAST_ISR_GPIO1_A_reg                                                     0x980070EC
#define set_ISO_FAST_ISR_GPIO1_A_reg(data)   (*((volatile unsigned int*) ISO_FAST_ISR_GPIO1_A_reg)=data)
#define get_ISO_FAST_ISR_GPIO1_A_reg   (*((volatile unsigned int*) ISO_FAST_ISR_GPIO1_A_reg))
#define ISO_FAST_ISR_GPIO1_A_inst_adr                                                "0x003B"
#define ISO_FAST_ISR_GPIO1_A_inst                                                    0x003B
#define ISO_FAST_ISR_GPIO1_A_int_34_shift                                            (4)
#define ISO_FAST_ISR_GPIO1_A_int_34_mask                                             (0x00000010)
#define ISO_FAST_ISR_GPIO1_A_int_34(data)                                            (0x00000010&((data)<<4))
#define ISO_FAST_ISR_GPIO1_A_int_34_src(data)                                        ((0x00000010&(data))>>4)
#define ISO_FAST_ISR_GPIO1_A_get_int_34(data)                                        ((0x00000010&(data))>>4)
#define ISO_FAST_ISR_GPIO1_A_int_33_shift                                            (3)
#define ISO_FAST_ISR_GPIO1_A_int_33_mask                                             (0x00000008)
#define ISO_FAST_ISR_GPIO1_A_int_33(data)                                            (0x00000008&((data)<<3))
#define ISO_FAST_ISR_GPIO1_A_int_33_src(data)                                        ((0x00000008&(data))>>3)
#define ISO_FAST_ISR_GPIO1_A_get_int_33(data)                                        ((0x00000008&(data))>>3)
#define ISO_FAST_ISR_GPIO1_A_int_32_shift                                            (2)
#define ISO_FAST_ISR_GPIO1_A_int_32_mask                                             (0x00000004)
#define ISO_FAST_ISR_GPIO1_A_int_32(data)                                            (0x00000004&((data)<<2))
#define ISO_FAST_ISR_GPIO1_A_int_32_src(data)                                        ((0x00000004&(data))>>2)
#define ISO_FAST_ISR_GPIO1_A_get_int_32(data)                                        ((0x00000004&(data))>>2)
#define ISO_FAST_ISR_GPIO1_A_int_31_shift                                            (1)
#define ISO_FAST_ISR_GPIO1_A_int_31_mask                                             (0x00000002)
#define ISO_FAST_ISR_GPIO1_A_int_31(data)                                            (0x00000002&((data)<<1))
#define ISO_FAST_ISR_GPIO1_A_int_31_src(data)                                        ((0x00000002&(data))>>1)
#define ISO_FAST_ISR_GPIO1_A_get_int_31(data)                                        ((0x00000002&(data))>>1)
#define ISO_FAST_ISR_GPIO1_A_write_data_shift                                        (0)
#define ISO_FAST_ISR_GPIO1_A_write_data_mask                                         (0x00000001)
#define ISO_FAST_ISR_GPIO1_A_write_data(data)                                        (0x00000001&((data)<<0))
#define ISO_FAST_ISR_GPIO1_A_write_data_src(data)                                    ((0x00000001&(data))>>0)
#define ISO_FAST_ISR_GPIO1_A_get_write_data(data)                                    ((0x00000001&(data))>>0)


#define ISO_FAST_ISR_GPIO0_DA                                                        0x980070F8
#define ISO_FAST_ISR_GPIO0_DA_reg_addr                                               "0x980070F8"
#define ISO_FAST_ISR_GPIO0_DA_reg                                                    0x980070F8
#define set_ISO_FAST_ISR_GPIO0_DA_reg(data)   (*((volatile unsigned int*) ISO_FAST_ISR_GPIO0_DA_reg)=data)
#define get_ISO_FAST_ISR_GPIO0_DA_reg   (*((volatile unsigned int*) ISO_FAST_ISR_GPIO0_DA_reg))
#define ISO_FAST_ISR_GPIO0_DA_inst_adr                                               "0x003E"
#define ISO_FAST_ISR_GPIO0_DA_inst                                                   0x003E
#define ISO_FAST_ISR_GPIO0_DA_int_30_shift                                           (31)
#define ISO_FAST_ISR_GPIO0_DA_int_30_mask                                            (0x80000000)
#define ISO_FAST_ISR_GPIO0_DA_int_30(data)                                           (0x80000000&((data)<<31))
#define ISO_FAST_ISR_GPIO0_DA_int_30_src(data)                                       ((0x80000000&(data))>>31)
#define ISO_FAST_ISR_GPIO0_DA_get_int_30(data)                                       ((0x80000000&(data))>>31)
#define ISO_FAST_ISR_GPIO0_DA_int_29_shift                                           (30)
#define ISO_FAST_ISR_GPIO0_DA_int_29_mask                                            (0x40000000)
#define ISO_FAST_ISR_GPIO0_DA_int_29(data)                                           (0x40000000&((data)<<30))
#define ISO_FAST_ISR_GPIO0_DA_int_29_src(data)                                       ((0x40000000&(data))>>30)
#define ISO_FAST_ISR_GPIO0_DA_get_int_29(data)                                       ((0x40000000&(data))>>30)
#define ISO_FAST_ISR_GPIO0_DA_int_28_shift                                           (29)
#define ISO_FAST_ISR_GPIO0_DA_int_28_mask                                            (0x20000000)
#define ISO_FAST_ISR_GPIO0_DA_int_28(data)                                           (0x20000000&((data)<<29))
#define ISO_FAST_ISR_GPIO0_DA_int_28_src(data)                                       ((0x20000000&(data))>>29)
#define ISO_FAST_ISR_GPIO0_DA_get_int_28(data)                                       ((0x20000000&(data))>>29)
#define ISO_FAST_ISR_GPIO0_DA_int_27_shift                                           (28)
#define ISO_FAST_ISR_GPIO0_DA_int_27_mask                                            (0x10000000)
#define ISO_FAST_ISR_GPIO0_DA_int_27(data)                                           (0x10000000&((data)<<28))
#define ISO_FAST_ISR_GPIO0_DA_int_27_src(data)                                       ((0x10000000&(data))>>28)
#define ISO_FAST_ISR_GPIO0_DA_get_int_27(data)                                       ((0x10000000&(data))>>28)
#define ISO_FAST_ISR_GPIO0_DA_int_26_shift                                           (27)
#define ISO_FAST_ISR_GPIO0_DA_int_26_mask                                            (0x08000000)
#define ISO_FAST_ISR_GPIO0_DA_int_26(data)                                           (0x08000000&((data)<<27))
#define ISO_FAST_ISR_GPIO0_DA_int_26_src(data)                                       ((0x08000000&(data))>>27)
#define ISO_FAST_ISR_GPIO0_DA_get_int_26(data)                                       ((0x08000000&(data))>>27)
#define ISO_FAST_ISR_GPIO0_DA_int_25_shift                                           (26)
#define ISO_FAST_ISR_GPIO0_DA_int_25_mask                                            (0x04000000)
#define ISO_FAST_ISR_GPIO0_DA_int_25(data)                                           (0x04000000&((data)<<26))
#define ISO_FAST_ISR_GPIO0_DA_int_25_src(data)                                       ((0x04000000&(data))>>26)
#define ISO_FAST_ISR_GPIO0_DA_get_int_25(data)                                       ((0x04000000&(data))>>26)
#define ISO_FAST_ISR_GPIO0_DA_int_24_shift                                           (25)
#define ISO_FAST_ISR_GPIO0_DA_int_24_mask                                            (0x02000000)
#define ISO_FAST_ISR_GPIO0_DA_int_24(data)                                           (0x02000000&((data)<<25))
#define ISO_FAST_ISR_GPIO0_DA_int_24_src(data)                                       ((0x02000000&(data))>>25)
#define ISO_FAST_ISR_GPIO0_DA_get_int_24(data)                                       ((0x02000000&(data))>>25)
#define ISO_FAST_ISR_GPIO0_DA_int_23_shift                                           (24)
#define ISO_FAST_ISR_GPIO0_DA_int_23_mask                                            (0x01000000)
#define ISO_FAST_ISR_GPIO0_DA_int_23(data)                                           (0x01000000&((data)<<24))
#define ISO_FAST_ISR_GPIO0_DA_int_23_src(data)                                       ((0x01000000&(data))>>24)
#define ISO_FAST_ISR_GPIO0_DA_get_int_23(data)                                       ((0x01000000&(data))>>24)
#define ISO_FAST_ISR_GPIO0_DA_int_22_shift                                           (23)
#define ISO_FAST_ISR_GPIO0_DA_int_22_mask                                            (0x00800000)
#define ISO_FAST_ISR_GPIO0_DA_int_22(data)                                           (0x00800000&((data)<<23))
#define ISO_FAST_ISR_GPIO0_DA_int_22_src(data)                                       ((0x00800000&(data))>>23)
#define ISO_FAST_ISR_GPIO0_DA_get_int_22(data)                                       ((0x00800000&(data))>>23)
#define ISO_FAST_ISR_GPIO0_DA_int_21_shift                                           (22)
#define ISO_FAST_ISR_GPIO0_DA_int_21_mask                                            (0x00400000)
#define ISO_FAST_ISR_GPIO0_DA_int_21(data)                                           (0x00400000&((data)<<22))
#define ISO_FAST_ISR_GPIO0_DA_int_21_src(data)                                       ((0x00400000&(data))>>22)
#define ISO_FAST_ISR_GPIO0_DA_get_int_21(data)                                       ((0x00400000&(data))>>22)
#define ISO_FAST_ISR_GPIO0_DA_int_20_shift                                           (21)
#define ISO_FAST_ISR_GPIO0_DA_int_20_mask                                            (0x00200000)
#define ISO_FAST_ISR_GPIO0_DA_int_20(data)                                           (0x00200000&((data)<<21))
#define ISO_FAST_ISR_GPIO0_DA_int_20_src(data)                                       ((0x00200000&(data))>>21)
#define ISO_FAST_ISR_GPIO0_DA_get_int_20(data)                                       ((0x00200000&(data))>>21)
#define ISO_FAST_ISR_GPIO0_DA_int_19_shift                                           (20)
#define ISO_FAST_ISR_GPIO0_DA_int_19_mask                                            (0x00100000)
#define ISO_FAST_ISR_GPIO0_DA_int_19(data)                                           (0x00100000&((data)<<20))
#define ISO_FAST_ISR_GPIO0_DA_int_19_src(data)                                       ((0x00100000&(data))>>20)
#define ISO_FAST_ISR_GPIO0_DA_get_int_19(data)                                       ((0x00100000&(data))>>20)
#define ISO_FAST_ISR_GPIO0_DA_int_18_shift                                           (19)
#define ISO_FAST_ISR_GPIO0_DA_int_18_mask                                            (0x00080000)
#define ISO_FAST_ISR_GPIO0_DA_int_18(data)                                           (0x00080000&((data)<<19))
#define ISO_FAST_ISR_GPIO0_DA_int_18_src(data)                                       ((0x00080000&(data))>>19)
#define ISO_FAST_ISR_GPIO0_DA_get_int_18(data)                                       ((0x00080000&(data))>>19)
#define ISO_FAST_ISR_GPIO0_DA_int_17_shift                                           (18)
#define ISO_FAST_ISR_GPIO0_DA_int_17_mask                                            (0x00040000)
#define ISO_FAST_ISR_GPIO0_DA_int_17(data)                                           (0x00040000&((data)<<18))
#define ISO_FAST_ISR_GPIO0_DA_int_17_src(data)                                       ((0x00040000&(data))>>18)
#define ISO_FAST_ISR_GPIO0_DA_get_int_17(data)                                       ((0x00040000&(data))>>18)
#define ISO_FAST_ISR_GPIO0_DA_int_16_shift                                           (17)
#define ISO_FAST_ISR_GPIO0_DA_int_16_mask                                            (0x00020000)
#define ISO_FAST_ISR_GPIO0_DA_int_16(data)                                           (0x00020000&((data)<<17))
#define ISO_FAST_ISR_GPIO0_DA_int_16_src(data)                                       ((0x00020000&(data))>>17)
#define ISO_FAST_ISR_GPIO0_DA_get_int_16(data)                                       ((0x00020000&(data))>>17)
#define ISO_FAST_ISR_GPIO0_DA_int_15_shift                                           (16)
#define ISO_FAST_ISR_GPIO0_DA_int_15_mask                                            (0x00010000)
#define ISO_FAST_ISR_GPIO0_DA_int_15(data)                                           (0x00010000&((data)<<16))
#define ISO_FAST_ISR_GPIO0_DA_int_15_src(data)                                       ((0x00010000&(data))>>16)
#define ISO_FAST_ISR_GPIO0_DA_get_int_15(data)                                       ((0x00010000&(data))>>16)
#define ISO_FAST_ISR_GPIO0_DA_int_14_shift                                           (15)
#define ISO_FAST_ISR_GPIO0_DA_int_14_mask                                            (0x00008000)
#define ISO_FAST_ISR_GPIO0_DA_int_14(data)                                           (0x00008000&((data)<<15))
#define ISO_FAST_ISR_GPIO0_DA_int_14_src(data)                                       ((0x00008000&(data))>>15)
#define ISO_FAST_ISR_GPIO0_DA_get_int_14(data)                                       ((0x00008000&(data))>>15)
#define ISO_FAST_ISR_GPIO0_DA_int_13_shift                                           (14)
#define ISO_FAST_ISR_GPIO0_DA_int_13_mask                                            (0x00004000)
#define ISO_FAST_ISR_GPIO0_DA_int_13(data)                                           (0x00004000&((data)<<14))
#define ISO_FAST_ISR_GPIO0_DA_int_13_src(data)                                       ((0x00004000&(data))>>14)
#define ISO_FAST_ISR_GPIO0_DA_get_int_13(data)                                       ((0x00004000&(data))>>14)
#define ISO_FAST_ISR_GPIO0_DA_int_12_shift                                           (13)
#define ISO_FAST_ISR_GPIO0_DA_int_12_mask                                            (0x00002000)
#define ISO_FAST_ISR_GPIO0_DA_int_12(data)                                           (0x00002000&((data)<<13))
#define ISO_FAST_ISR_GPIO0_DA_int_12_src(data)                                       ((0x00002000&(data))>>13)
#define ISO_FAST_ISR_GPIO0_DA_get_int_12(data)                                       ((0x00002000&(data))>>13)
#define ISO_FAST_ISR_GPIO0_DA_int_11_shift                                           (12)
#define ISO_FAST_ISR_GPIO0_DA_int_11_mask                                            (0x00001000)
#define ISO_FAST_ISR_GPIO0_DA_int_11(data)                                           (0x00001000&((data)<<12))
#define ISO_FAST_ISR_GPIO0_DA_int_11_src(data)                                       ((0x00001000&(data))>>12)
#define ISO_FAST_ISR_GPIO0_DA_get_int_11(data)                                       ((0x00001000&(data))>>12)
#define ISO_FAST_ISR_GPIO0_DA_int_10_shift                                           (11)
#define ISO_FAST_ISR_GPIO0_DA_int_10_mask                                            (0x00000800)
#define ISO_FAST_ISR_GPIO0_DA_int_10(data)                                           (0x00000800&((data)<<11))
#define ISO_FAST_ISR_GPIO0_DA_int_10_src(data)                                       ((0x00000800&(data))>>11)
#define ISO_FAST_ISR_GPIO0_DA_get_int_10(data)                                       ((0x00000800&(data))>>11)
#define ISO_FAST_ISR_GPIO0_DA_int_9_shift                                            (10)
#define ISO_FAST_ISR_GPIO0_DA_int_9_mask                                             (0x00000400)
#define ISO_FAST_ISR_GPIO0_DA_int_9(data)                                            (0x00000400&((data)<<10))
#define ISO_FAST_ISR_GPIO0_DA_int_9_src(data)                                        ((0x00000400&(data))>>10)
#define ISO_FAST_ISR_GPIO0_DA_get_int_9(data)                                        ((0x00000400&(data))>>10)
#define ISO_FAST_ISR_GPIO0_DA_int_8_shift                                            (9)
#define ISO_FAST_ISR_GPIO0_DA_int_8_mask                                             (0x00000200)
#define ISO_FAST_ISR_GPIO0_DA_int_8(data)                                            (0x00000200&((data)<<9))
#define ISO_FAST_ISR_GPIO0_DA_int_8_src(data)                                        ((0x00000200&(data))>>9)
#define ISO_FAST_ISR_GPIO0_DA_get_int_8(data)                                        ((0x00000200&(data))>>9)
#define ISO_FAST_ISR_GPIO0_DA_int_7_shift                                            (8)
#define ISO_FAST_ISR_GPIO0_DA_int_7_mask                                             (0x00000100)
#define ISO_FAST_ISR_GPIO0_DA_int_7(data)                                            (0x00000100&((data)<<8))
#define ISO_FAST_ISR_GPIO0_DA_int_7_src(data)                                        ((0x00000100&(data))>>8)
#define ISO_FAST_ISR_GPIO0_DA_get_int_7(data)                                        ((0x00000100&(data))>>8)
#define ISO_FAST_ISR_GPIO0_DA_int_6_shift                                            (7)
#define ISO_FAST_ISR_GPIO0_DA_int_6_mask                                             (0x00000080)
#define ISO_FAST_ISR_GPIO0_DA_int_6(data)                                            (0x00000080&((data)<<7))
#define ISO_FAST_ISR_GPIO0_DA_int_6_src(data)                                        ((0x00000080&(data))>>7)
#define ISO_FAST_ISR_GPIO0_DA_get_int_6(data)                                        ((0x00000080&(data))>>7)
#define ISO_FAST_ISR_GPIO0_DA_int_5_shift                                            (6)
#define ISO_FAST_ISR_GPIO0_DA_int_5_mask                                             (0x00000040)
#define ISO_FAST_ISR_GPIO0_DA_int_5(data)                                            (0x00000040&((data)<<6))
#define ISO_FAST_ISR_GPIO0_DA_int_5_src(data)                                        ((0x00000040&(data))>>6)
#define ISO_FAST_ISR_GPIO0_DA_get_int_5(data)                                        ((0x00000040&(data))>>6)
#define ISO_FAST_ISR_GPIO0_DA_int_4_shift                                            (5)
#define ISO_FAST_ISR_GPIO0_DA_int_4_mask                                             (0x00000020)
#define ISO_FAST_ISR_GPIO0_DA_int_4(data)                                            (0x00000020&((data)<<5))
#define ISO_FAST_ISR_GPIO0_DA_int_4_src(data)                                        ((0x00000020&(data))>>5)
#define ISO_FAST_ISR_GPIO0_DA_get_int_4(data)                                        ((0x00000020&(data))>>5)
#define ISO_FAST_ISR_GPIO0_DA_int_3_shift                                            (4)
#define ISO_FAST_ISR_GPIO0_DA_int_3_mask                                             (0x00000010)
#define ISO_FAST_ISR_GPIO0_DA_int_3(data)                                            (0x00000010&((data)<<4))
#define ISO_FAST_ISR_GPIO0_DA_int_3_src(data)                                        ((0x00000010&(data))>>4)
#define ISO_FAST_ISR_GPIO0_DA_get_int_3(data)                                        ((0x00000010&(data))>>4)
#define ISO_FAST_ISR_GPIO0_DA_int_2_shift                                            (3)
#define ISO_FAST_ISR_GPIO0_DA_int_2_mask                                             (0x00000008)
#define ISO_FAST_ISR_GPIO0_DA_int_2(data)                                            (0x00000008&((data)<<3))
#define ISO_FAST_ISR_GPIO0_DA_int_2_src(data)                                        ((0x00000008&(data))>>3)
#define ISO_FAST_ISR_GPIO0_DA_get_int_2(data)                                        ((0x00000008&(data))>>3)
#define ISO_FAST_ISR_GPIO0_DA_int_1_shift                                            (2)
#define ISO_FAST_ISR_GPIO0_DA_int_1_mask                                             (0x00000004)
#define ISO_FAST_ISR_GPIO0_DA_int_1(data)                                            (0x00000004&((data)<<2))
#define ISO_FAST_ISR_GPIO0_DA_int_1_src(data)                                        ((0x00000004&(data))>>2)
#define ISO_FAST_ISR_GPIO0_DA_get_int_1(data)                                        ((0x00000004&(data))>>2)
#define ISO_FAST_ISR_GPIO0_DA_int_0_shift                                            (1)
#define ISO_FAST_ISR_GPIO0_DA_int_0_mask                                             (0x00000002)
#define ISO_FAST_ISR_GPIO0_DA_int_0(data)                                            (0x00000002&((data)<<1))
#define ISO_FAST_ISR_GPIO0_DA_int_0_src(data)                                        ((0x00000002&(data))>>1)
#define ISO_FAST_ISR_GPIO0_DA_get_int_0(data)                                        ((0x00000002&(data))>>1)
#define ISO_FAST_ISR_GPIO0_DA_write_data_shift                                       (0)
#define ISO_FAST_ISR_GPIO0_DA_write_data_mask                                        (0x00000001)
#define ISO_FAST_ISR_GPIO0_DA_write_data(data)                                       (0x00000001&((data)<<0))
#define ISO_FAST_ISR_GPIO0_DA_write_data_src(data)                                   ((0x00000001&(data))>>0)
#define ISO_FAST_ISR_GPIO0_DA_get_write_data(data)                                   ((0x00000001&(data))>>0)


#define ISO_FAST_ISR_GPIO1_DA                                                        0x980070FC
#define ISO_FAST_ISR_GPIO1_DA_reg_addr                                               "0x980070FC"
#define ISO_FAST_ISR_GPIO1_DA_reg                                                    0x980070FC
#define set_ISO_FAST_ISR_GPIO1_DA_reg(data)   (*((volatile unsigned int*) ISO_FAST_ISR_GPIO1_DA_reg)=data)
#define get_ISO_FAST_ISR_GPIO1_DA_reg   (*((volatile unsigned int*) ISO_FAST_ISR_GPIO1_DA_reg))
#define ISO_FAST_ISR_GPIO1_DA_inst_adr                                               "0x003F"
#define ISO_FAST_ISR_GPIO1_DA_inst                                                   0x003F
#define ISO_FAST_ISR_GPIO1_DA_int_34_shift                                           (4)
#define ISO_FAST_ISR_GPIO1_DA_int_34_mask                                            (0x00000010)
#define ISO_FAST_ISR_GPIO1_DA_int_34(data)                                           (0x00000010&((data)<<4))
#define ISO_FAST_ISR_GPIO1_DA_int_34_src(data)                                       ((0x00000010&(data))>>4)
#define ISO_FAST_ISR_GPIO1_DA_get_int_34(data)                                       ((0x00000010&(data))>>4)
#define ISO_FAST_ISR_GPIO1_DA_int_33_shift                                           (3)
#define ISO_FAST_ISR_GPIO1_DA_int_33_mask                                            (0x00000008)
#define ISO_FAST_ISR_GPIO1_DA_int_33(data)                                           (0x00000008&((data)<<3))
#define ISO_FAST_ISR_GPIO1_DA_int_33_src(data)                                       ((0x00000008&(data))>>3)
#define ISO_FAST_ISR_GPIO1_DA_get_int_33(data)                                       ((0x00000008&(data))>>3)
#define ISO_FAST_ISR_GPIO1_DA_int_32_shift                                           (2)
#define ISO_FAST_ISR_GPIO1_DA_int_32_mask                                            (0x00000004)
#define ISO_FAST_ISR_GPIO1_DA_int_32(data)                                           (0x00000004&((data)<<2))
#define ISO_FAST_ISR_GPIO1_DA_int_32_src(data)                                       ((0x00000004&(data))>>2)
#define ISO_FAST_ISR_GPIO1_DA_get_int_32(data)                                       ((0x00000004&(data))>>2)
#define ISO_FAST_ISR_GPIO1_DA_int_31_shift                                           (1)
#define ISO_FAST_ISR_GPIO1_DA_int_31_mask                                            (0x00000002)
#define ISO_FAST_ISR_GPIO1_DA_int_31(data)                                           (0x00000002&((data)<<1))
#define ISO_FAST_ISR_GPIO1_DA_int_31_src(data)                                       ((0x00000002&(data))>>1)
#define ISO_FAST_ISR_GPIO1_DA_get_int_31(data)                                       ((0x00000002&(data))>>1)
#define ISO_FAST_ISR_GPIO1_DA_write_data_shift                                       (0)
#define ISO_FAST_ISR_GPIO1_DA_write_data_mask                                        (0x00000001)
#define ISO_FAST_ISR_GPIO1_DA_write_data(data)                                       (0x00000001&((data)<<0))
#define ISO_FAST_ISR_GPIO1_DA_write_data_src(data)                                   ((0x00000001&(data))>>0)
#define ISO_FAST_ISR_GPIO1_DA_get_write_data(data)                                   ((0x00000001&(data))>>0)


#define ISO_I2C1_REQ_CTRL                                                            0x98007200
#define ISO_I2C1_REQ_CTRL_reg_addr                                                   "0x98007200"
#define ISO_I2C1_REQ_CTRL_reg                                                        0x98007200
#define set_ISO_I2C1_REQ_CTRL_reg(data)   (*((volatile unsigned int*) ISO_I2C1_REQ_CTRL_reg)=data)
#define get_ISO_I2C1_REQ_CTRL_reg   (*((volatile unsigned int*) ISO_I2C1_REQ_CTRL_reg))
#define ISO_I2C1_REQ_CTRL_inst_adr                                                   "0x0080"
#define ISO_I2C1_REQ_CTRL_inst                                                       0x0080
#define ISO_I2C1_REQ_CTRL_int_en_shift                                               (1)
#define ISO_I2C1_REQ_CTRL_int_en_mask                                                (0x00000002)
#define ISO_I2C1_REQ_CTRL_int_en(data)                                               (0x00000002&((data)<<1))
#define ISO_I2C1_REQ_CTRL_int_en_src(data)                                           ((0x00000002&(data))>>1)
#define ISO_I2C1_REQ_CTRL_get_int_en(data)                                           ((0x00000002&(data))>>1)
#define ISO_I2C1_REQ_CTRL_en_shift                                                   (0)
#define ISO_I2C1_REQ_CTRL_en_mask                                                    (0x00000001)
#define ISO_I2C1_REQ_CTRL_en(data)                                                   (0x00000001&((data)<<0))
#define ISO_I2C1_REQ_CTRL_en_src(data)                                               ((0x00000001&(data))>>0)
#define ISO_I2C1_REQ_CTRL_get_en(data)                                               ((0x00000001&(data))>>0)


#define ISO_I2C1_REQ_START                                                           0x98007204
#define ISO_I2C1_REQ_START_reg_addr                                                  "0x98007204"
#define ISO_I2C1_REQ_START_reg                                                       0x98007204
#define set_ISO_I2C1_REQ_START_reg(data)   (*((volatile unsigned int*) ISO_I2C1_REQ_START_reg)=data)
#define get_ISO_I2C1_REQ_START_reg   (*((volatile unsigned int*) ISO_I2C1_REQ_START_reg))
#define ISO_I2C1_REQ_START_inst_adr                                                  "0x0081"
#define ISO_I2C1_REQ_START_inst                                                      0x0081
#define ISO_I2C1_REQ_START_val_shift                                                 (0)
#define ISO_I2C1_REQ_START_val_mask                                                  (0x0000FFFF)
#define ISO_I2C1_REQ_START_val(data)                                                 (0x0000FFFF&((data)<<0))
#define ISO_I2C1_REQ_START_val_src(data)                                             ((0x0000FFFF&(data))>>0)
#define ISO_I2C1_REQ_START_get_val(data)                                             ((0x0000FFFF&(data))>>0)


#define ISO_I2C1_REQ_SCL_LCNT                                                        0x98007208
#define ISO_I2C1_REQ_SCL_LCNT_reg_addr                                               "0x98007208"
#define ISO_I2C1_REQ_SCL_LCNT_reg                                                    0x98007208
#define set_ISO_I2C1_REQ_SCL_LCNT_reg(data)   (*((volatile unsigned int*) ISO_I2C1_REQ_SCL_LCNT_reg)=data)
#define get_ISO_I2C1_REQ_SCL_LCNT_reg   (*((volatile unsigned int*) ISO_I2C1_REQ_SCL_LCNT_reg))
#define ISO_I2C1_REQ_SCL_LCNT_inst_adr                                               "0x0082"
#define ISO_I2C1_REQ_SCL_LCNT_inst                                                   0x0082
#define ISO_I2C1_REQ_SCL_LCNT_val_shift                                              (0)
#define ISO_I2C1_REQ_SCL_LCNT_val_mask                                               (0x0000FFFF)
#define ISO_I2C1_REQ_SCL_LCNT_val(data)                                              (0x0000FFFF&((data)<<0))
#define ISO_I2C1_REQ_SCL_LCNT_val_src(data)                                          ((0x0000FFFF&(data))>>0)
#define ISO_I2C1_REQ_SCL_LCNT_get_val(data)                                          ((0x0000FFFF&(data))>>0)


#define ISO_I2C1_REQ_STOP                                                            0x9800720C
#define ISO_I2C1_REQ_STOP_reg_addr                                                   "0x9800720C"
#define ISO_I2C1_REQ_STOP_reg                                                        0x9800720C
#define set_ISO_I2C1_REQ_STOP_reg(data)   (*((volatile unsigned int*) ISO_I2C1_REQ_STOP_reg)=data)
#define get_ISO_I2C1_REQ_STOP_reg   (*((volatile unsigned int*) ISO_I2C1_REQ_STOP_reg))
#define ISO_I2C1_REQ_STOP_inst_adr                                                   "0x0083"
#define ISO_I2C1_REQ_STOP_inst                                                       0x0083
#define ISO_I2C1_REQ_STOP_val_shift                                                  (0)
#define ISO_I2C1_REQ_STOP_val_mask                                                   (0x0000FFFF)
#define ISO_I2C1_REQ_STOP_val(data)                                                  (0x0000FFFF&((data)<<0))
#define ISO_I2C1_REQ_STOP_val_src(data)                                              ((0x0000FFFF&(data))>>0)
#define ISO_I2C1_REQ_STOP_get_val(data)                                              ((0x0000FFFF&(data))>>0)


#define ISO_POR_CTRL                                                                 0x98007210
#define ISO_POR_CTRL_reg_addr                                                        "0x98007210"
#define ISO_POR_CTRL_reg                                                             0x98007210
#define set_ISO_POR_CTRL_reg(data)   (*((volatile unsigned int*) ISO_POR_CTRL_reg)=data)
#define get_ISO_POR_CTRL_reg   (*((volatile unsigned int*) ISO_POR_CTRL_reg))
#define ISO_POR_CTRL_inst_adr                                                        "0x0084"
#define ISO_POR_CTRL_inst                                                            0x0084
#define ISO_POR_CTRL_dv_cen_int_en_shift                                             (5)
#define ISO_POR_CTRL_dv_cen_int_en_mask                                              (0x00000020)
#define ISO_POR_CTRL_dv_cen_int_en(data)                                             (0x00000020&((data)<<5))
#define ISO_POR_CTRL_dv_cen_int_en_src(data)                                         ((0x00000020&(data))>>5)
#define ISO_POR_CTRL_get_dv_cen_int_en(data)                                         ((0x00000020&(data))>>5)
#define ISO_POR_CTRL_dv_cen_ha_shift                                                 (4)
#define ISO_POR_CTRL_dv_cen_ha_mask                                                  (0x00000010)
#define ISO_POR_CTRL_dv_cen_ha(data)                                                 (0x00000010&((data)<<4))
#define ISO_POR_CTRL_dv_cen_ha_src(data)                                             ((0x00000010&(data))>>4)
#define ISO_POR_CTRL_get_dv_cen_ha(data)                                             ((0x00000010&(data))>>4)
#define ISO_POR_CTRL_av_cen_int_en_shift                                             (1)
#define ISO_POR_CTRL_av_cen_int_en_mask                                              (0x00000002)
#define ISO_POR_CTRL_av_cen_int_en(data)                                             (0x00000002&((data)<<1))
#define ISO_POR_CTRL_av_cen_int_en_src(data)                                         ((0x00000002&(data))>>1)
#define ISO_POR_CTRL_get_av_cen_int_en(data)                                         ((0x00000002&(data))>>1)
#define ISO_POR_CTRL_av_cen_ha_shift                                                 (0)
#define ISO_POR_CTRL_av_cen_ha_mask                                                  (0x00000001)
#define ISO_POR_CTRL_av_cen_ha(data)                                                 (0x00000001&((data)<<0))
#define ISO_POR_CTRL_av_cen_ha_src(data)                                             ((0x00000001&(data))>>0)
#define ISO_POR_CTRL_get_av_cen_ha(data)                                             ((0x00000001&(data))>>0)


#define ISO_POR_VTH                                                                  0x98007214
#define ISO_POR_VTH_reg_addr                                                         "0x98007214"
#define ISO_POR_VTH_reg                                                              0x98007214
#define set_ISO_POR_VTH_reg(data)   (*((volatile unsigned int*) ISO_POR_VTH_reg)=data)
#define get_ISO_POR_VTH_reg   (*((volatile unsigned int*) ISO_POR_VTH_reg))
#define ISO_POR_VTH_inst_adr                                                         "0x0085"
#define ISO_POR_VTH_inst                                                             0x0085
#define ISO_POR_VTH_reg_iso_por_shift                                                (24)
#define ISO_POR_VTH_reg_iso_por_mask                                                 (0x01000000)
#define ISO_POR_VTH_reg_iso_por(data)                                                (0x01000000&((data)<<24))
#define ISO_POR_VTH_reg_iso_por_src(data)                                            ((0x01000000&(data))>>24)
#define ISO_POR_VTH_get_reg_iso_por(data)                                            ((0x01000000&(data))>>24)
#define ISO_POR_VTH_reg_gpu_por_shift                                                (20)
#define ISO_POR_VTH_reg_gpu_por_mask                                                 (0x00300000)
#define ISO_POR_VTH_reg_gpu_por(data)                                                (0x00300000&((data)<<20))
#define ISO_POR_VTH_reg_gpu_por_src(data)                                            ((0x00300000&(data))>>20)
#define ISO_POR_VTH_get_reg_gpu_por(data)                                            ((0x00300000&(data))>>20)
#define ISO_POR_VTH_reg_scpu_mem_por_shift                                           (16)
#define ISO_POR_VTH_reg_scpu_mem_por_mask                                            (0x00030000)
#define ISO_POR_VTH_reg_scpu_mem_por(data)                                           (0x00030000&((data)<<16))
#define ISO_POR_VTH_reg_scpu_mem_por_src(data)                                       ((0x00030000&(data))>>16)
#define ISO_POR_VTH_get_reg_scpu_mem_por(data)                                       ((0x00030000&(data))>>16)
#define ISO_POR_VTH_reg_scpu_por_shift                                               (12)
#define ISO_POR_VTH_reg_scpu_por_mask                                                (0x00003000)
#define ISO_POR_VTH_reg_scpu_por(data)                                               (0x00003000&((data)<<12))
#define ISO_POR_VTH_reg_scpu_por_src(data)                                           ((0x00003000&(data))>>12)
#define ISO_POR_VTH_get_reg_scpu_por(data)                                           ((0x00003000&(data))>>12)
#define ISO_POR_VTH_reg_dvth_por_shift                                               (8)
#define ISO_POR_VTH_reg_dvth_por_mask                                                (0x00000300)
#define ISO_POR_VTH_reg_dvth_por(data)                                               (0x00000300&((data)<<8))
#define ISO_POR_VTH_reg_dvth_por_src(data)                                           ((0x00000300&(data))>>8)
#define ISO_POR_VTH_get_reg_dvth_por(data)                                           ((0x00000300&(data))>>8)
#define ISO_POR_VTH_reg_avth_por_shift                                               (4)
#define ISO_POR_VTH_reg_avth_por_mask                                                (0x00000030)
#define ISO_POR_VTH_reg_avth_por(data)                                               (0x00000030&((data)<<4))
#define ISO_POR_VTH_reg_avth_por_src(data)                                           ((0x00000030&(data))>>4)
#define ISO_POR_VTH_get_reg_avth_por(data)                                           ((0x00000030&(data))>>4)
#define ISO_POR_VTH_reg_d10_por_shift                                                (0)
#define ISO_POR_VTH_reg_d10_por_mask                                                 (0x00000003)
#define ISO_POR_VTH_reg_d10_por(data)                                                (0x00000003&((data)<<0))
#define ISO_POR_VTH_reg_d10_por_src(data)                                            ((0x00000003&(data))>>0)
#define ISO_POR_VTH_get_reg_d10_por(data)                                            ((0x00000003&(data))>>0)


#define ISO_POR_DATAI                                                                0x98007218
#define ISO_POR_DATAI_reg_addr                                                       "0x98007218"
#define ISO_POR_DATAI_reg                                                            0x98007218
#define set_ISO_POR_DATAI_reg(data)   (*((volatile unsigned int*) ISO_POR_DATAI_reg)=data)
#define get_ISO_POR_DATAI_reg   (*((volatile unsigned int*) ISO_POR_DATAI_reg))
#define ISO_POR_DATAI_inst_adr                                                       "0x0086"
#define ISO_POR_DATAI_inst                                                           0x0086
#define ISO_POR_DATAI_porb_dv_cen_l_shift                                            (4)
#define ISO_POR_DATAI_porb_dv_cen_l_mask                                             (0x00000010)
#define ISO_POR_DATAI_porb_dv_cen_l(data)                                            (0x00000010&((data)<<4))
#define ISO_POR_DATAI_porb_dv_cen_l_src(data)                                        ((0x00000010&(data))>>4)
#define ISO_POR_DATAI_get_porb_dv_cen_l(data)                                        ((0x00000010&(data))>>4)
#define ISO_POR_DATAI_porb_av_cen_l_shift                                            (0)
#define ISO_POR_DATAI_porb_av_cen_l_mask                                             (0x00000001)
#define ISO_POR_DATAI_porb_av_cen_l(data)                                            (0x00000001&((data)<<0))
#define ISO_POR_DATAI_porb_av_cen_l_src(data)                                        ((0x00000001&(data))>>0)
#define ISO_POR_DATAI_get_porb_av_cen_l(data)                                        ((0x00000001&(data))>>0)


#define ISO_POR_DEB                                                                  0x9800721C
#define ISO_POR_DEB_reg_addr                                                         "0x9800721C"
#define ISO_POR_DEB_reg                                                              0x9800721C
#define set_ISO_POR_DEB_reg(data)   (*((volatile unsigned int*) ISO_POR_DEB_reg)=data)
#define get_ISO_POR_DEB_reg   (*((volatile unsigned int*) ISO_POR_DEB_reg))
#define ISO_POR_DEB_inst_adr                                                         "0x0087"
#define ISO_POR_DEB_inst                                                             0x0087
#define ISO_POR_DEB_write_en2_shift                                                  (7)
#define ISO_POR_DEB_write_en2_mask                                                   (0x00000080)
#define ISO_POR_DEB_write_en2(data)                                                  (0x00000080&((data)<<7))
#define ISO_POR_DEB_write_en2_src(data)                                              ((0x00000080&(data))>>7)
#define ISO_POR_DEB_get_write_en2(data)                                              ((0x00000080&(data))>>7)
#define ISO_POR_DEB_dv_cen_shift                                                     (4)
#define ISO_POR_DEB_dv_cen_mask                                                      (0x00000070)
#define ISO_POR_DEB_dv_cen(data)                                                     (0x00000070&((data)<<4))
#define ISO_POR_DEB_dv_cen_src(data)                                                 ((0x00000070&(data))>>4)
#define ISO_POR_DEB_get_dv_cen(data)                                                 ((0x00000070&(data))>>4)
#define ISO_POR_DEB_write_en1_shift                                                  (3)
#define ISO_POR_DEB_write_en1_mask                                                   (0x00000008)
#define ISO_POR_DEB_write_en1(data)                                                  (0x00000008&((data)<<3))
#define ISO_POR_DEB_write_en1_src(data)                                              ((0x00000008&(data))>>3)
#define ISO_POR_DEB_get_write_en1(data)                                              ((0x00000008&(data))>>3)
#define ISO_POR_DEB_av_cen_shift                                                     (0)
#define ISO_POR_DEB_av_cen_mask                                                      (0x00000007)
#define ISO_POR_DEB_av_cen(data)                                                     (0x00000007&((data)<<0))
#define ISO_POR_DEB_av_cen_src(data)                                                 ((0x00000007&(data))>>0)
#define ISO_POR_DEB_get_av_cen(data)                                                 ((0x00000007&(data))>>0)


#define ISO_SB2_0                                                                    0x98007F00
#define ISO_SB2_0_reg_addr                                                           "0x98007F00"
#define ISO_SB2_0_reg                                                                0x98007F00
#define set_ISO_SB2_0_reg(data)   (*((volatile unsigned int*) ISO_SB2_0_reg)=data)
#define get_ISO_SB2_0_reg   (*((volatile unsigned int*) ISO_SB2_0_reg))
#define ISO_SB2_0_inst_adr                                                           "0x00C0"
#define ISO_SB2_0_inst                                                               0x00C0
#define ISO_SB2_0_ve_fo_block_nwc_shift                                              (7)
#define ISO_SB2_0_ve_fo_block_nwc_mask                                               (0x00000080)
#define ISO_SB2_0_ve_fo_block_nwc(data)                                              (0x00000080&((data)<<7))
#define ISO_SB2_0_ve_fo_block_nwc_src(data)                                          ((0x00000080&(data))>>7)
#define ISO_SB2_0_get_ve_fo_block_nwc(data)                                          ((0x00000080&(data))>>7)
#define ISO_SB2_0_tp_block_nwc_shift                                                 (6)
#define ISO_SB2_0_tp_block_nwc_mask                                                  (0x00000040)
#define ISO_SB2_0_tp_block_nwc(data)                                                 (0x00000040&((data)<<6))
#define ISO_SB2_0_tp_block_nwc_src(data)                                             ((0x00000040&(data))>>6)
#define ISO_SB2_0_get_tp_block_nwc(data)                                             ((0x00000040&(data))>>6)
#define ISO_SB2_0_usb2sram_ctrl_shift                                                (5)
#define ISO_SB2_0_usb2sram_ctrl_mask                                                 (0x00000020)
#define ISO_SB2_0_usb2sram_ctrl(data)                                                (0x00000020&((data)<<5))
#define ISO_SB2_0_usb2sram_ctrl_src(data)                                            ((0x00000020&(data))>>5)
#define ISO_SB2_0_get_usb2sram_ctrl(data)                                            ((0x00000020&(data))>>5)
#define ISO_SB2_0_ve_encode_block_nwc_shift                                          (4)
#define ISO_SB2_0_ve_encode_block_nwc_mask                                           (0x00000010)
#define ISO_SB2_0_ve_encode_block_nwc(data)                                          (0x00000010&((data)<<4))
#define ISO_SB2_0_ve_encode_block_nwc_src(data)                                      ((0x00000010&(data))>>4)
#define ISO_SB2_0_get_ve_encode_block_nwc(data)                                      ((0x00000010&(data))>>4)
#define ISO_SB2_0_ve_block_nwc_shift                                                 (3)
#define ISO_SB2_0_ve_block_nwc_mask                                                  (0x00000008)
#define ISO_SB2_0_ve_block_nwc(data)                                                 (0x00000008&((data)<<3))
#define ISO_SB2_0_ve_block_nwc_src(data)                                             ((0x00000008&(data))>>3)
#define ISO_SB2_0_get_ve_block_nwc(data)                                             ((0x00000008&(data))>>3)
#define ISO_SB2_0_vo_block_nwc_shift                                                 (2)
#define ISO_SB2_0_vo_block_nwc_mask                                                  (0x00000004)
#define ISO_SB2_0_vo_block_nwc(data)                                                 (0x00000004&((data)<<2))
#define ISO_SB2_0_vo_block_nwc_src(data)                                             ((0x00000004&(data))>>2)
#define ISO_SB2_0_get_vo_block_nwc(data)                                             ((0x00000004&(data))>>2)
#define ISO_SB2_0_dc_mem_port_lock_shift                                             (1)
#define ISO_SB2_0_dc_mem_port_lock_mask                                              (0x00000002)
#define ISO_SB2_0_dc_mem_port_lock(data)                                             (0x00000002&((data)<<1))
#define ISO_SB2_0_dc_mem_port_lock_src(data)                                         ((0x00000002&(data))>>1)
#define ISO_SB2_0_get_dc_mem_port_lock(data)                                         ((0x00000002&(data))>>1)
#define ISO_SB2_0_secure_rbus_shift                                                  (0)
#define ISO_SB2_0_secure_rbus_mask                                                   (0x00000001)
#define ISO_SB2_0_secure_rbus(data)                                                  (0x00000001&((data)<<0))
#define ISO_SB2_0_secure_rbus_src(data)                                              ((0x00000001&(data))>>0)
#define ISO_SB2_0_get_secure_rbus(data)                                              ((0x00000001&(data))>>0)


#define ISO_MBIAS                                                                    0x98007F04
#define ISO_MBIAS_reg_addr                                                           "0x98007F04"
#define ISO_MBIAS_reg                                                                0x98007F04
#define set_ISO_MBIAS_reg(data)   (*((volatile unsigned int*) ISO_MBIAS_reg)=data)
#define get_ISO_MBIAS_reg   (*((volatile unsigned int*) ISO_MBIAS_reg))
#define ISO_MBIAS_inst_adr                                                           "0x00C1"
#define ISO_MBIAS_inst                                                               0x00C1
#define ISO_MBIAS_reg_emb_i_sel_shift                                                (14)
#define ISO_MBIAS_reg_emb_i_sel_mask                                                 (0x00004000)
#define ISO_MBIAS_reg_emb_i_sel(data)                                                (0x00004000&((data)<<14))
#define ISO_MBIAS_reg_emb_i_sel_src(data)                                            ((0x00004000&(data))>>14)
#define ISO_MBIAS_get_reg_emb_i_sel(data)                                            ((0x00004000&(data))>>14)
#define ISO_MBIAS_reg_emb_cap_sel_shift                                              (12)
#define ISO_MBIAS_reg_emb_cap_sel_mask                                               (0x00003000)
#define ISO_MBIAS_reg_emb_cap_sel(data)                                              (0x00003000&((data)<<12))
#define ISO_MBIAS_reg_emb_cap_sel_src(data)                                          ((0x00003000&(data))>>12)
#define ISO_MBIAS_get_reg_emb_cap_sel(data)                                          ((0x00003000&(data))>>12)
#define ISO_MBIAS_reg_bg_rbgloop2_shift                                              (9)
#define ISO_MBIAS_reg_bg_rbgloop2_mask                                               (0x00000E00)
#define ISO_MBIAS_reg_bg_rbgloop2(data)                                              (0x00000E00&((data)<<9))
#define ISO_MBIAS_reg_bg_rbgloop2_src(data)                                          ((0x00000E00&(data))>>9)
#define ISO_MBIAS_get_reg_bg_rbgloop2(data)                                          ((0x00000E00&(data))>>9)
#define ISO_MBIAS_reg_bg_rbg_shift                                                   (6)
#define ISO_MBIAS_reg_bg_rbg_mask                                                    (0x000001C0)
#define ISO_MBIAS_reg_bg_rbg(data)                                                   (0x000001C0&((data)<<6))
#define ISO_MBIAS_reg_bg_rbg_src(data)                                               ((0x000001C0&(data))>>6)
#define ISO_MBIAS_get_reg_bg_rbg(data)                                               ((0x000001C0&(data))>>6)
#define ISO_MBIAS_reg_bg_rbg2_shift                                                  (4)
#define ISO_MBIAS_reg_bg_rbg2_mask                                                   (0x00000030)
#define ISO_MBIAS_reg_bg_rbg2(data)                                                  (0x00000030&((data)<<4))
#define ISO_MBIAS_reg_bg_rbg2_src(data)                                              ((0x00000030&(data))>>4)
#define ISO_MBIAS_get_reg_bg_rbg2(data)                                              ((0x00000030&(data))>>4)
#define ISO_MBIAS_reg_bg_envbgup_shift                                               (3)
#define ISO_MBIAS_reg_bg_envbgup_mask                                                (0x00000008)
#define ISO_MBIAS_reg_bg_envbgup(data)                                               (0x00000008&((data)<<3))
#define ISO_MBIAS_reg_bg_envbgup_src(data)                                           ((0x00000008&(data))>>3)
#define ISO_MBIAS_get_reg_bg_envbgup(data)                                           ((0x00000008&(data))>>3)
#define ISO_MBIAS_reg_ck_dummy_shift                                                 (2)
#define ISO_MBIAS_reg_ck_dummy_mask                                                  (0x00000004)
#define ISO_MBIAS_reg_ck_dummy(data)                                                 (0x00000004&((data)<<2))
#define ISO_MBIAS_reg_ck_dummy_src(data)                                             ((0x00000004&(data))>>2)
#define ISO_MBIAS_get_reg_ck_dummy(data)                                             ((0x00000004&(data))>>2)
#define ISO_MBIAS_reg_bg_dummy_shift                                                 (1)
#define ISO_MBIAS_reg_bg_dummy_mask                                                  (0x00000002)
#define ISO_MBIAS_reg_bg_dummy(data)                                                 (0x00000002&((data)<<1))
#define ISO_MBIAS_reg_bg_dummy_src(data)                                             ((0x00000002&(data))>>1)
#define ISO_MBIAS_get_reg_bg_dummy(data)                                             ((0x00000002&(data))>>1)
#define ISO_MBIAS_reg_en_emb_shift                                                   (0)
#define ISO_MBIAS_reg_en_emb_mask                                                    (0x00000001)
#define ISO_MBIAS_reg_en_emb(data)                                                   (0x00000001&((data)<<0))
#define ISO_MBIAS_reg_en_emb_src(data)                                               ((0x00000001&(data))>>0)
#define ISO_MBIAS_get_reg_en_emb(data)                                               ((0x00000001&(data))>>0)


#define ISO_DDR_IO_CTRL                                                              0x98007F08
#define ISO_DDR_IO_CTRL_reg_addr                                                     "0x98007F08"
#define ISO_DDR_IO_CTRL_reg                                                          0x98007F08
#define set_ISO_DDR_IO_CTRL_reg(data)   (*((volatile unsigned int*) ISO_DDR_IO_CTRL_reg)=data)
#define get_ISO_DDR_IO_CTRL_reg   (*((volatile unsigned int*) ISO_DDR_IO_CTRL_reg))
#define ISO_DDR_IO_CTRL_inst_adr                                                     "0x00C2"
#define ISO_DDR_IO_CTRL_inst                                                         0x00C2
#define ISO_DDR_IO_CTRL_reg_por15n_1_shift                                           (3)
#define ISO_DDR_IO_CTRL_reg_por15n_1_mask                                            (0x00000008)
#define ISO_DDR_IO_CTRL_reg_por15n_1(data)                                           (0x00000008&((data)<<3))
#define ISO_DDR_IO_CTRL_reg_por15n_1_src(data)                                       ((0x00000008&(data))>>3)
#define ISO_DDR_IO_CTRL_get_reg_por15n_1(data)                                       ((0x00000008&(data))>>3)
#define ISO_DDR_IO_CTRL_reg_por15n_0_shift                                           (2)
#define ISO_DDR_IO_CTRL_reg_por15n_0_mask                                            (0x00000004)
#define ISO_DDR_IO_CTRL_reg_por15n_0(data)                                           (0x00000004&((data)<<2))
#define ISO_DDR_IO_CTRL_reg_por15n_0_src(data)                                       ((0x00000004&(data))>>2)
#define ISO_DDR_IO_CTRL_get_reg_por15n_0(data)                                       ((0x00000004&(data))>>2)
#define ISO_DDR_IO_CTRL_reg_pwdpad15n_1_shift                                        (1)
#define ISO_DDR_IO_CTRL_reg_pwdpad15n_1_mask                                         (0x00000002)
#define ISO_DDR_IO_CTRL_reg_pwdpad15n_1(data)                                        (0x00000002&((data)<<1))
#define ISO_DDR_IO_CTRL_reg_pwdpad15n_1_src(data)                                    ((0x00000002&(data))>>1)
#define ISO_DDR_IO_CTRL_get_reg_pwdpad15n_1(data)                                    ((0x00000002&(data))>>1)
#define ISO_DDR_IO_CTRL_reg_pwdpad15n_0_shift                                        (0)
#define ISO_DDR_IO_CTRL_reg_pwdpad15n_0_mask                                         (0x00000001)
#define ISO_DDR_IO_CTRL_reg_pwdpad15n_0(data)                                        (0x00000001&((data)<<0))
#define ISO_DDR_IO_CTRL_reg_pwdpad15n_0_src(data)                                    ((0x00000001&(data))>>0)
#define ISO_DDR_IO_CTRL_get_reg_pwdpad15n_0(data)                                    ((0x00000001&(data))>>0)


#define ISO_DISP_IO_CTRL                                                             0x98007F0C
#define ISO_DISP_IO_CTRL_reg_addr                                                    "0x98007F0C"
#define ISO_DISP_IO_CTRL_reg                                                         0x98007F0C
#define set_ISO_DISP_IO_CTRL_reg(data)   (*((volatile unsigned int*) ISO_DISP_IO_CTRL_reg)=data)
#define get_ISO_DISP_IO_CTRL_reg   (*((volatile unsigned int*) ISO_DISP_IO_CTRL_reg))
#define ISO_DISP_IO_CTRL_inst_adr                                                    "0x00C3"
#define ISO_DISP_IO_CTRL_inst                                                        0x00C3
#define ISO_DISP_IO_CTRL_reg_pwdpad3_disp_shift                                      (0)
#define ISO_DISP_IO_CTRL_reg_pwdpad3_disp_mask                                       (0x00000001)
#define ISO_DISP_IO_CTRL_reg_pwdpad3_disp(data)                                      (0x00000001&((data)<<0))
#define ISO_DISP_IO_CTRL_reg_pwdpad3_disp_src(data)                                  ((0x00000001&(data))>>0)
#define ISO_DISP_IO_CTRL_get_reg_pwdpad3_disp(data)                                  ((0x00000001&(data))>>0)


#define ISO_SB3_CTRL                                                                 0x98007f10
#define ISO_SB3_CTRL_reg_addr                                                        "0x98007F10"
#define ISO_SB3_CTRL_reg                                                             0x98007F10
#define set_ISO_SB3_CTRL_reg(data)   (*((volatile unsigned int*) ISO_SB3_CTRL_reg)=data)
#define get_ISO_SB3_CTRL_reg   (*((volatile unsigned int*) ISO_SB3_CTRL_reg))
#define ISO_SB3_CTRL_inst_adr                                                        "0x00C4"
#define ISO_SB3_CTRL_inst                                                            0x00C4
#define ISO_SB3_CTRL_iso_sb3_req_mask_reg_shift                                      (0)
#define ISO_SB3_CTRL_iso_sb3_req_mask_reg_mask                                       (0x00000001)
#define ISO_SB3_CTRL_iso_sb3_req_mask_reg(data)                                      (0x00000001&((data)<<0))
#define ISO_SB3_CTRL_iso_sb3_req_mask_reg_src(data)                                  ((0x00000001&(data))>>0)
#define ISO_SB3_CTRL_get_iso_sb3_req_mask_reg(data)                                  ((0x00000001&(data))>>0)


#define ISO_ISO_TMUX_DBG                                                             0x98007f14
#define ISO_ISO_TMUX_DBG_reg_addr                                                    "0x98007F14"
#define ISO_ISO_TMUX_DBG_reg                                                         0x98007F14
#define set_ISO_ISO_TMUX_DBG_reg(data)   (*((volatile unsigned int*) ISO_ISO_TMUX_DBG_reg)=data)
#define get_ISO_ISO_TMUX_DBG_reg   (*((volatile unsigned int*) ISO_ISO_TMUX_DBG_reg))
#define ISO_ISO_TMUX_DBG_inst_adr                                                    "0x00C5"
#define ISO_ISO_TMUX_DBG_inst                                                        0x00C5
#define ISO_ISO_TMUX_DBG_tmux_dbg_sel_shift                                          (0)
#define ISO_ISO_TMUX_DBG_tmux_dbg_sel_mask                                           (0x0000007F)
#define ISO_ISO_TMUX_DBG_tmux_dbg_sel(data)                                          (0x0000007F&((data)<<0))
#define ISO_ISO_TMUX_DBG_tmux_dbg_sel_src(data)                                      ((0x0000007F&(data))>>0)
#define ISO_ISO_TMUX_DBG_get_tmux_dbg_sel(data)                                      ((0x0000007F&(data))>>0)


#define ISO_ISO_MODE_REG_0                                                           0x98007F20
#define ISO_ISO_MODE_REG_1                                                           0x98007F24
#define ISO_ISO_MODE_REG_2                                                           0x98007F28
#define ISO_ISO_MODE_REG_3                                                           0x98007F2C
#define ISO_ISO_MODE_REG_4                                                           0x98007F30
#define ISO_ISO_MODE_REG_5                                                           0x98007F34
#define ISO_ISO_MODE_REG_6                                                           0x98007F38
#define ISO_ISO_MODE_REG_7                                                           0x98007F3C
#define ISO_ISO_MODE_REG_8                                                           0x98007F40
#define ISO_ISO_MODE_REG_9                                                           0x98007F44
#define ISO_ISO_MODE_REG_10                                                           0x98007F48
#define ISO_ISO_MODE_REG_11                                                           0x98007F4C
#define ISO_ISO_MODE_REG_12                                                           0x98007F50
#define ISO_ISO_MODE_REG_13                                                           0x98007F54
#define ISO_ISO_MODE_REG_14                                                           0x98007F58
#define ISO_ISO_MODE_REG_15                                                           0x98007F5C
#define ISO_ISO_MODE_REG_16                                                           0x98007F60
#define ISO_ISO_MODE_REG_17                                                           0x98007F64
#define ISO_ISO_MODE_REG_18                                                           0x98007F68
#define ISO_ISO_MODE_REG_19                                                           0x98007F6C
#define ISO_ISO_MODE_REG_0_reg_addr                                                  "0x98007F20"
#define ISO_ISO_MODE_REG_1_reg_addr                                                  "0x98007F24"
#define ISO_ISO_MODE_REG_2_reg_addr                                                  "0x98007F28"
#define ISO_ISO_MODE_REG_3_reg_addr                                                  "0x98007F2C"
#define ISO_ISO_MODE_REG_4_reg_addr                                                  "0x98007F30"
#define ISO_ISO_MODE_REG_5_reg_addr                                                  "0x98007F34"
#define ISO_ISO_MODE_REG_6_reg_addr                                                  "0x98007F38"
#define ISO_ISO_MODE_REG_7_reg_addr                                                  "0x98007F3C"
#define ISO_ISO_MODE_REG_8_reg_addr                                                  "0x98007F40"
#define ISO_ISO_MODE_REG_9_reg_addr                                                  "0x98007F44"
#define ISO_ISO_MODE_REG_10_reg_addr                                                  "0x98007F48"
#define ISO_ISO_MODE_REG_11_reg_addr                                                  "0x98007F4C"
#define ISO_ISO_MODE_REG_12_reg_addr                                                  "0x98007F50"
#define ISO_ISO_MODE_REG_13_reg_addr                                                  "0x98007F54"
#define ISO_ISO_MODE_REG_14_reg_addr                                                  "0x98007F58"
#define ISO_ISO_MODE_REG_15_reg_addr                                                  "0x98007F5C"
#define ISO_ISO_MODE_REG_16_reg_addr                                                  "0x98007F60"
#define ISO_ISO_MODE_REG_17_reg_addr                                                  "0x98007F64"
#define ISO_ISO_MODE_REG_18_reg_addr                                                  "0x98007F68"
#define ISO_ISO_MODE_REG_19_reg_addr                                                  "0x98007F6C"
#define ISO_ISO_MODE_REG_0_reg                                                       0x98007F20
#define ISO_ISO_MODE_REG_1_reg                                                       0x98007F24
#define ISO_ISO_MODE_REG_2_reg                                                       0x98007F28
#define ISO_ISO_MODE_REG_3_reg                                                       0x98007F2C
#define ISO_ISO_MODE_REG_4_reg                                                       0x98007F30
#define ISO_ISO_MODE_REG_5_reg                                                       0x98007F34
#define ISO_ISO_MODE_REG_6_reg                                                       0x98007F38
#define ISO_ISO_MODE_REG_7_reg                                                       0x98007F3C
#define ISO_ISO_MODE_REG_8_reg                                                       0x98007F40
#define ISO_ISO_MODE_REG_9_reg                                                       0x98007F44
#define ISO_ISO_MODE_REG_10_reg                                                       0x98007F48
#define ISO_ISO_MODE_REG_11_reg                                                       0x98007F4C
#define ISO_ISO_MODE_REG_12_reg                                                       0x98007F50
#define ISO_ISO_MODE_REG_13_reg                                                       0x98007F54
#define ISO_ISO_MODE_REG_14_reg                                                       0x98007F58
#define ISO_ISO_MODE_REG_15_reg                                                       0x98007F5C
#define ISO_ISO_MODE_REG_16_reg                                                       0x98007F60
#define ISO_ISO_MODE_REG_17_reg                                                       0x98007F64
#define ISO_ISO_MODE_REG_18_reg                                                       0x98007F68
#define ISO_ISO_MODE_REG_19_reg                                                       0x98007F6C
#define set_ISO_ISO_MODE_REG_0_reg(data)   (*((volatile unsigned int*) ISO_ISO_MODE_REG_0_reg)=data)
#define set_ISO_ISO_MODE_REG_1_reg(data)   (*((volatile unsigned int*) ISO_ISO_MODE_REG_1_reg)=data)
#define set_ISO_ISO_MODE_REG_2_reg(data)   (*((volatile unsigned int*) ISO_ISO_MODE_REG_2_reg)=data)
#define set_ISO_ISO_MODE_REG_3_reg(data)   (*((volatile unsigned int*) ISO_ISO_MODE_REG_3_reg)=data)
#define set_ISO_ISO_MODE_REG_4_reg(data)   (*((volatile unsigned int*) ISO_ISO_MODE_REG_4_reg)=data)
#define set_ISO_ISO_MODE_REG_5_reg(data)   (*((volatile unsigned int*) ISO_ISO_MODE_REG_5_reg)=data)
#define set_ISO_ISO_MODE_REG_6_reg(data)   (*((volatile unsigned int*) ISO_ISO_MODE_REG_6_reg)=data)
#define set_ISO_ISO_MODE_REG_7_reg(data)   (*((volatile unsigned int*) ISO_ISO_MODE_REG_7_reg)=data)
#define set_ISO_ISO_MODE_REG_8_reg(data)   (*((volatile unsigned int*) ISO_ISO_MODE_REG_8_reg)=data)
#define set_ISO_ISO_MODE_REG_9_reg(data)   (*((volatile unsigned int*) ISO_ISO_MODE_REG_9_reg)=data)
#define set_ISO_ISO_MODE_REG_10_reg(data)   (*((volatile unsigned int*) ISO_ISO_MODE_REG_10_reg)=data)
#define set_ISO_ISO_MODE_REG_11_reg(data)   (*((volatile unsigned int*) ISO_ISO_MODE_REG_11_reg)=data)
#define set_ISO_ISO_MODE_REG_12_reg(data)   (*((volatile unsigned int*) ISO_ISO_MODE_REG_12_reg)=data)
#define set_ISO_ISO_MODE_REG_13_reg(data)   (*((volatile unsigned int*) ISO_ISO_MODE_REG_13_reg)=data)
#define set_ISO_ISO_MODE_REG_14_reg(data)   (*((volatile unsigned int*) ISO_ISO_MODE_REG_14_reg)=data)
#define set_ISO_ISO_MODE_REG_15_reg(data)   (*((volatile unsigned int*) ISO_ISO_MODE_REG_15_reg)=data)
#define set_ISO_ISO_MODE_REG_16_reg(data)   (*((volatile unsigned int*) ISO_ISO_MODE_REG_16_reg)=data)
#define set_ISO_ISO_MODE_REG_17_reg(data)   (*((volatile unsigned int*) ISO_ISO_MODE_REG_17_reg)=data)
#define set_ISO_ISO_MODE_REG_18_reg(data)   (*((volatile unsigned int*) ISO_ISO_MODE_REG_18_reg)=data)
#define set_ISO_ISO_MODE_REG_19_reg(data)   (*((volatile unsigned int*) ISO_ISO_MODE_REG_19_reg)=data)
#define get_ISO_ISO_MODE_REG_0_reg   (*((volatile unsigned int*) ISO_ISO_MODE_REG_0_reg))
#define get_ISO_ISO_MODE_REG_1_reg   (*((volatile unsigned int*) ISO_ISO_MODE_REG_1_reg))
#define get_ISO_ISO_MODE_REG_2_reg   (*((volatile unsigned int*) ISO_ISO_MODE_REG_2_reg))
#define get_ISO_ISO_MODE_REG_3_reg   (*((volatile unsigned int*) ISO_ISO_MODE_REG_3_reg))
#define get_ISO_ISO_MODE_REG_4_reg   (*((volatile unsigned int*) ISO_ISO_MODE_REG_4_reg))
#define get_ISO_ISO_MODE_REG_5_reg   (*((volatile unsigned int*) ISO_ISO_MODE_REG_5_reg))
#define get_ISO_ISO_MODE_REG_6_reg   (*((volatile unsigned int*) ISO_ISO_MODE_REG_6_reg))
#define get_ISO_ISO_MODE_REG_7_reg   (*((volatile unsigned int*) ISO_ISO_MODE_REG_7_reg))
#define get_ISO_ISO_MODE_REG_8_reg   (*((volatile unsigned int*) ISO_ISO_MODE_REG_8_reg))
#define get_ISO_ISO_MODE_REG_9_reg   (*((volatile unsigned int*) ISO_ISO_MODE_REG_9_reg))
#define get_ISO_ISO_MODE_REG_10_reg   (*((volatile unsigned int*) ISO_ISO_MODE_REG_10_reg))
#define get_ISO_ISO_MODE_REG_11_reg   (*((volatile unsigned int*) ISO_ISO_MODE_REG_11_reg))
#define get_ISO_ISO_MODE_REG_12_reg   (*((volatile unsigned int*) ISO_ISO_MODE_REG_12_reg))
#define get_ISO_ISO_MODE_REG_13_reg   (*((volatile unsigned int*) ISO_ISO_MODE_REG_13_reg))
#define get_ISO_ISO_MODE_REG_14_reg   (*((volatile unsigned int*) ISO_ISO_MODE_REG_14_reg))
#define get_ISO_ISO_MODE_REG_15_reg   (*((volatile unsigned int*) ISO_ISO_MODE_REG_15_reg))
#define get_ISO_ISO_MODE_REG_16_reg   (*((volatile unsigned int*) ISO_ISO_MODE_REG_16_reg))
#define get_ISO_ISO_MODE_REG_17_reg   (*((volatile unsigned int*) ISO_ISO_MODE_REG_17_reg))
#define get_ISO_ISO_MODE_REG_18_reg   (*((volatile unsigned int*) ISO_ISO_MODE_REG_18_reg))
#define get_ISO_ISO_MODE_REG_19_reg   (*((volatile unsigned int*) ISO_ISO_MODE_REG_19_reg))
#define ISO_ISO_MODE_REG_0_inst_adr                                                  "0x00C8"
#define ISO_ISO_MODE_REG_1_inst_adr                                                  "0x00C9"
#define ISO_ISO_MODE_REG_2_inst_adr                                                  "0x00CA"
#define ISO_ISO_MODE_REG_3_inst_adr                                                  "0x00CB"
#define ISO_ISO_MODE_REG_4_inst_adr                                                  "0x00CC"
#define ISO_ISO_MODE_REG_5_inst_adr                                                  "0x00CD"
#define ISO_ISO_MODE_REG_6_inst_adr                                                  "0x00CE"
#define ISO_ISO_MODE_REG_7_inst_adr                                                  "0x00CF"
#define ISO_ISO_MODE_REG_8_inst_adr                                                  "0x00D0"
#define ISO_ISO_MODE_REG_9_inst_adr                                                  "0x00D1"
#define ISO_ISO_MODE_REG_10_inst_adr                                                  "0x00D2"
#define ISO_ISO_MODE_REG_11_inst_adr                                                  "0x00D3"
#define ISO_ISO_MODE_REG_12_inst_adr                                                  "0x00D4"
#define ISO_ISO_MODE_REG_13_inst_adr                                                  "0x00D5"
#define ISO_ISO_MODE_REG_14_inst_adr                                                  "0x00D6"
#define ISO_ISO_MODE_REG_15_inst_adr                                                  "0x00D7"
#define ISO_ISO_MODE_REG_16_inst_adr                                                  "0x00D8"
#define ISO_ISO_MODE_REG_17_inst_adr                                                  "0x00D9"
#define ISO_ISO_MODE_REG_18_inst_adr                                                  "0x00DA"
#define ISO_ISO_MODE_REG_19_inst_adr                                                  "0x00DB"
#define ISO_ISO_MODE_REG_0_inst                                                      0x00C8
#define ISO_ISO_MODE_REG_1_inst                                                      0x00C9
#define ISO_ISO_MODE_REG_2_inst                                                      0x00CA
#define ISO_ISO_MODE_REG_3_inst                                                      0x00CB
#define ISO_ISO_MODE_REG_4_inst                                                      0x00CC
#define ISO_ISO_MODE_REG_5_inst                                                      0x00CD
#define ISO_ISO_MODE_REG_6_inst                                                      0x00CE
#define ISO_ISO_MODE_REG_7_inst                                                      0x00CF
#define ISO_ISO_MODE_REG_8_inst                                                      0x00D0
#define ISO_ISO_MODE_REG_9_inst                                                      0x00D1
#define ISO_ISO_MODE_REG_10_inst                                                      0x00D2
#define ISO_ISO_MODE_REG_11_inst                                                      0x00D3
#define ISO_ISO_MODE_REG_12_inst                                                      0x00D4
#define ISO_ISO_MODE_REG_13_inst                                                      0x00D5
#define ISO_ISO_MODE_REG_14_inst                                                      0x00D6
#define ISO_ISO_MODE_REG_15_inst                                                      0x00D7
#define ISO_ISO_MODE_REG_16_inst                                                      0x00D8
#define ISO_ISO_MODE_REG_17_inst                                                      0x00D9
#define ISO_ISO_MODE_REG_18_inst                                                      0x00DA
#define ISO_ISO_MODE_REG_19_inst                                                      0x00DB
#define ISO_ISO_MODE_REG_dummy_shift                                                 (0)
#define ISO_ISO_MODE_REG_dummy_mask                                                  (0xFFFFFFFF)
#define ISO_ISO_MODE_REG_dummy(data)                                                 (0xFFFFFFFF&((data)<<0))
#define ISO_ISO_MODE_REG_dummy_src(data)                                             ((0xFFFFFFFF&(data))>>0)
#define ISO_ISO_MODE_REG_get_dummy(data)                                             ((0xFFFFFFFF&(data))>>0)


#define ISO_USB0_SRAM_PWR0                                                           0x98007f70
#define ISO_USB0_SRAM_PWR0_reg_addr                                                  "0x98007F70"
#define ISO_USB0_SRAM_PWR0_reg                                                       0x98007F70
#define set_ISO_USB0_SRAM_PWR0_reg(data)   (*((volatile unsigned int*) ISO_USB0_SRAM_PWR0_reg)=data)
#define get_ISO_USB0_SRAM_PWR0_reg   (*((volatile unsigned int*) ISO_USB0_SRAM_PWR0_reg))
#define ISO_USB0_SRAM_PWR0_inst_adr                                                  "0x00DC"
#define ISO_USB0_SRAM_PWR0_inst                                                      0x00DC
#define ISO_USB0_SRAM_PWR0_l2h_delay_cycle_shift                                     (0)
#define ISO_USB0_SRAM_PWR0_l2h_delay_cycle_mask                                      (0xFFFFFFFF)
#define ISO_USB0_SRAM_PWR0_l2h_delay_cycle(data)                                     (0xFFFFFFFF&((data)<<0))
#define ISO_USB0_SRAM_PWR0_l2h_delay_cycle_src(data)                                 ((0xFFFFFFFF&(data))>>0)
#define ISO_USB0_SRAM_PWR0_get_l2h_delay_cycle(data)                                 ((0xFFFFFFFF&(data))>>0)


#define ISO_USB0_SRAM_PWR1                                                           0x98007f74
#define ISO_USB0_SRAM_PWR1_reg_addr                                                  "0x98007F74"
#define ISO_USB0_SRAM_PWR1_reg                                                       0x98007F74
#define set_ISO_USB0_SRAM_PWR1_reg(data)   (*((volatile unsigned int*) ISO_USB0_SRAM_PWR1_reg)=data)
#define get_ISO_USB0_SRAM_PWR1_reg   (*((volatile unsigned int*) ISO_USB0_SRAM_PWR1_reg))
#define ISO_USB0_SRAM_PWR1_inst_adr                                                  "0x00DD"
#define ISO_USB0_SRAM_PWR1_inst                                                      0x00DD
#define ISO_USB0_SRAM_PWR1_h2l_delay_cycle_shift                                     (0)
#define ISO_USB0_SRAM_PWR1_h2l_delay_cycle_mask                                      (0xFFFFFFFF)
#define ISO_USB0_SRAM_PWR1_h2l_delay_cycle(data)                                     (0xFFFFFFFF&((data)<<0))
#define ISO_USB0_SRAM_PWR1_h2l_delay_cycle_src(data)                                 ((0xFFFFFFFF&(data))>>0)
#define ISO_USB0_SRAM_PWR1_get_h2l_delay_cycle(data)                                 ((0xFFFFFFFF&(data))>>0)


#define ISO_USB0_SRAM_PWR2                                                           0x98007f78
#define ISO_USB0_SRAM_PWR2_reg_addr                                                  "0x98007F78"
#define ISO_USB0_SRAM_PWR2_reg                                                       0x98007F78
#define set_ISO_USB0_SRAM_PWR2_reg(data)   (*((volatile unsigned int*) ISO_USB0_SRAM_PWR2_reg)=data)
#define get_ISO_USB0_SRAM_PWR2_reg   (*((volatile unsigned int*) ISO_USB0_SRAM_PWR2_reg))
#define ISO_USB0_SRAM_PWR2_inst_adr                                                  "0x00DE"
#define ISO_USB0_SRAM_PWR2_inst                                                      0x00DE
#define ISO_USB0_SRAM_PWR2_sd_reg_shift                                              (0)
#define ISO_USB0_SRAM_PWR2_sd_reg_mask                                               (0xFFFFFFFF)
#define ISO_USB0_SRAM_PWR2_sd_reg(data)                                              (0xFFFFFFFF&((data)<<0))
#define ISO_USB0_SRAM_PWR2_sd_reg_src(data)                                          ((0xFFFFFFFF&(data))>>0)
#define ISO_USB0_SRAM_PWR2_get_sd_reg(data)                                          ((0xFFFFFFFF&(data))>>0)


#define ISO_USB0_SRAM_PWR3                                                           0x98007f7c
#define ISO_USB0_SRAM_PWR3_reg_addr                                                  "0x98007F7C"
#define ISO_USB0_SRAM_PWR3_reg                                                       0x98007F7C
#define set_ISO_USB0_SRAM_PWR3_reg(data)   (*((volatile unsigned int*) ISO_USB0_SRAM_PWR3_reg)=data)
#define get_ISO_USB0_SRAM_PWR3_reg   (*((volatile unsigned int*) ISO_USB0_SRAM_PWR3_reg))
#define ISO_USB0_SRAM_PWR3_inst_adr                                                  "0x00DF"
#define ISO_USB0_SRAM_PWR3_inst                                                      0x00DF
#define ISO_USB0_SRAM_PWR3_mux_reg_shift                                             (0)
#define ISO_USB0_SRAM_PWR3_mux_reg_mask                                              (0xFFFFFFFF)
#define ISO_USB0_SRAM_PWR3_mux_reg(data)                                             (0xFFFFFFFF&((data)<<0))
#define ISO_USB0_SRAM_PWR3_mux_reg_src(data)                                         ((0xFFFFFFFF&(data))>>0)
#define ISO_USB0_SRAM_PWR3_get_mux_reg(data)                                         ((0xFFFFFFFF&(data))>>0)


#define ISO_USB0_SRAM_PWR4                                                           0x98007f80
#define ISO_USB0_SRAM_PWR4_reg_addr                                                  "0x98007F80"
#define ISO_USB0_SRAM_PWR4_reg                                                       0x98007F80
#define set_ISO_USB0_SRAM_PWR4_reg(data)   (*((volatile unsigned int*) ISO_USB0_SRAM_PWR4_reg)=data)
#define get_ISO_USB0_SRAM_PWR4_reg   (*((volatile unsigned int*) ISO_USB0_SRAM_PWR4_reg))
#define ISO_USB0_SRAM_PWR4_inst_adr                                                  "0x00E0"
#define ISO_USB0_SRAM_PWR4_inst                                                      0x00E0
#define ISO_USB0_SRAM_PWR4_ctrl_shift                                                (0)
#define ISO_USB0_SRAM_PWR4_ctrl_mask                                                 (0xFFFFFFFF)
#define ISO_USB0_SRAM_PWR4_ctrl(data)                                                (0xFFFFFFFF&((data)<<0))
#define ISO_USB0_SRAM_PWR4_ctrl_src(data)                                            ((0xFFFFFFFF&(data))>>0)
#define ISO_USB0_SRAM_PWR4_get_ctrl(data)                                            ((0xFFFFFFFF&(data))>>0)


#if 0
#define ISO_USB0_SRAM_PWR5                                                           0x98007f84
#define ISO_USB0_SRAM_PWR5_reg_addr                                                  "0x98007F84"
#define ISO_USB0_SRAM_PWR5_reg                                                       0x98007F84
#define set_ISO_USB0_SRAM_PWR5_reg(data)   (*((volatile unsigned int*) ISO_USB0_SRAM_PWR5_reg)=data)
#define get_ISO_USB0_SRAM_PWR5_reg   (*((volatile unsigned int*) ISO_USB0_SRAM_PWR5_reg))
#define ISO_USB0_SRAM_PWR5_inst_adr                                                  "0x00E1"
#define ISO_USB0_SRAM_PWR5_inst                                                      0x00E1
#define ISO_USB0_SRAM_PWR5_ve3_sram_int_mask_shift                                   (4)
#define ISO_USB0_SRAM_PWR5_ve3_sram_int_mask_mask                                    (0x00000010)
#define ISO_USB0_SRAM_PWR5_ve3_sram_int_mask(data)                                   (0x00000010&((data)<<4))
#define ISO_USB0_SRAM_PWR5_ve3_sram_int_mask_src(data)                               ((0x00000010&(data))>>4)
#define ISO_USB0_SRAM_PWR5_get_ve3_sram_int_mask(data)                               ((0x00000010&(data))>>4)
#define ISO_USB0_SRAM_PWR5_ve3_sram_int_shift                                        (2)
#define ISO_USB0_SRAM_PWR5_ve3_sram_int_mask                                         (0x00000004)
#define ISO_USB0_SRAM_PWR5_ve3_sram_int(data)                                        (0x00000004&((data)<<2))
#define ISO_USB0_SRAM_PWR5_ve3_sram_int_src(data)                                    ((0x00000004&(data))>>2)
#define ISO_USB0_SRAM_PWR5_get_ve3_sram_int(data)                                    ((0x00000004&(data))>>2)
#define ISO_USB0_SRAM_PWR5_write_data_shift                                          (0)
#define ISO_USB0_SRAM_PWR5_write_data_mask                                           (0x00000001)
#define ISO_USB0_SRAM_PWR5_write_data(data)                                          (0x00000001&((data)<<0))
#define ISO_USB0_SRAM_PWR5_write_data_src(data)                                      ((0x00000001&(data))>>0)
#define ISO_USB0_SRAM_PWR5_get_write_data(data)                                      ((0x00000001&(data))>>0)
#endif


#define ISO_USB0_SRAM_PWR6                                                           0x98007f88
#define ISO_USB0_SRAM_PWR6_reg_addr                                                  "0x98007F88"
#define ISO_USB0_SRAM_PWR6_reg                                                       0x98007F88
#define set_ISO_USB0_SRAM_PWR6_reg(data)   (*((volatile unsigned int*) ISO_USB0_SRAM_PWR6_reg)=data)
#define get_ISO_USB0_SRAM_PWR6_reg   (*((volatile unsigned int*) ISO_USB0_SRAM_PWR6_reg))
#define ISO_USB0_SRAM_PWR6_inst_adr                                                  "0x00E2"
#define ISO_USB0_SRAM_PWR6_inst                                                      0x00E2
#define ISO_USB0_SRAM_PWR6_last_delay_cycle_shift                                    (0)
#define ISO_USB0_SRAM_PWR6_last_delay_cycle_mask                                     (0xFFFFFFFF)
#define ISO_USB0_SRAM_PWR6_last_delay_cycle(data)                                    (0xFFFFFFFF&((data)<<0))
#define ISO_USB0_SRAM_PWR6_last_delay_cycle_src(data)                                ((0xFFFFFFFF&(data))>>0)
#define ISO_USB0_SRAM_PWR6_get_last_delay_cycle(data)                                ((0xFFFFFFFF&(data))>>0)


#define ISO_USB0_SRAM_PWR7                                                           0x98007f8c
#define ISO_USB0_SRAM_PWR7_reg_addr                                                  "0x98007F8C"
#define ISO_USB0_SRAM_PWR7_reg                                                       0x98007F8C
#define set_ISO_USB0_SRAM_PWR7_reg(data)   (*((volatile unsigned int*) ISO_USB0_SRAM_PWR7_reg)=data)
#define get_ISO_USB0_SRAM_PWR7_reg   (*((volatile unsigned int*) ISO_USB0_SRAM_PWR7_reg))
#define ISO_USB0_SRAM_PWR7_inst_adr                                                  "0x00E3"
#define ISO_USB0_SRAM_PWR7_inst                                                      0x00E3
#define ISO_USB0_SRAM_PWR7_pg_switch_info_shift                                      (0)
#define ISO_USB0_SRAM_PWR7_pg_switch_info_mask                                       (0xFFFFFFFF)
#define ISO_USB0_SRAM_PWR7_pg_switch_info(data)                                      (0xFFFFFFFF&((data)<<0))
#define ISO_USB0_SRAM_PWR7_pg_switch_info_src(data)                                  ((0xFFFFFFFF&(data))>>0)
#define ISO_USB0_SRAM_PWR7_get_pg_switch_info(data)                                  ((0xFFFFFFFF&(data))>>0)


#define ISO_USB1_SRAM_PWR0                                                           0x98007f90
#define ISO_USB1_SRAM_PWR0_reg_addr                                                  "0x98007F90"
#define ISO_USB1_SRAM_PWR0_reg                                                       0x98007F90
#define set_ISO_USB1_SRAM_PWR0_reg(data)   (*((volatile unsigned int*) ISO_USB1_SRAM_PWR0_reg)=data)
#define get_ISO_USB1_SRAM_PWR0_reg   (*((volatile unsigned int*) ISO_USB1_SRAM_PWR0_reg))
#define ISO_USB1_SRAM_PWR0_inst_adr                                                  "0x00E4"
#define ISO_USB1_SRAM_PWR0_inst                                                      0x00E4
#define ISO_USB1_SRAM_PWR0_l2h_delay_cycle_shift                                     (0)
#define ISO_USB1_SRAM_PWR0_l2h_delay_cycle_mask                                      (0xFFFFFFFF)
#define ISO_USB1_SRAM_PWR0_l2h_delay_cycle(data)                                     (0xFFFFFFFF&((data)<<0))
#define ISO_USB1_SRAM_PWR0_l2h_delay_cycle_src(data)                                 ((0xFFFFFFFF&(data))>>0)
#define ISO_USB1_SRAM_PWR0_get_l2h_delay_cycle(data)                                 ((0xFFFFFFFF&(data))>>0)


#define ISO_USB1_SRAM_PWR1                                                           0x98007f94
#define ISO_USB1_SRAM_PWR1_reg_addr                                                  "0x98007F94"
#define ISO_USB1_SRAM_PWR1_reg                                                       0x98007F94
#define set_ISO_USB1_SRAM_PWR1_reg(data)   (*((volatile unsigned int*) ISO_USB1_SRAM_PWR1_reg)=data)
#define get_ISO_USB1_SRAM_PWR1_reg   (*((volatile unsigned int*) ISO_USB1_SRAM_PWR1_reg))
#define ISO_USB1_SRAM_PWR1_inst_adr                                                  "0x00E5"
#define ISO_USB1_SRAM_PWR1_inst                                                      0x00E5
#define ISO_USB1_SRAM_PWR1_h2l_delay_cycle_shift                                     (0)
#define ISO_USB1_SRAM_PWR1_h2l_delay_cycle_mask                                      (0xFFFFFFFF)
#define ISO_USB1_SRAM_PWR1_h2l_delay_cycle(data)                                     (0xFFFFFFFF&((data)<<0))
#define ISO_USB1_SRAM_PWR1_h2l_delay_cycle_src(data)                                 ((0xFFFFFFFF&(data))>>0)
#define ISO_USB1_SRAM_PWR1_get_h2l_delay_cycle(data)                                 ((0xFFFFFFFF&(data))>>0)


#define ISO_USB1_SRAM_PWR2                                                           0x98007f98
#define ISO_USB1_SRAM_PWR2_reg_addr                                                  "0x98007F98"
#define ISO_USB1_SRAM_PWR2_reg                                                       0x98007F98
#define set_ISO_USB1_SRAM_PWR2_reg(data)   (*((volatile unsigned int*) ISO_USB1_SRAM_PWR2_reg)=data)
#define get_ISO_USB1_SRAM_PWR2_reg   (*((volatile unsigned int*) ISO_USB1_SRAM_PWR2_reg))
#define ISO_USB1_SRAM_PWR2_inst_adr                                                  "0x00E6"
#define ISO_USB1_SRAM_PWR2_inst                                                      0x00E6
#define ISO_USB1_SRAM_PWR2_sd_reg_shift                                              (0)
#define ISO_USB1_SRAM_PWR2_sd_reg_mask                                               (0xFFFFFFFF)
#define ISO_USB1_SRAM_PWR2_sd_reg(data)                                              (0xFFFFFFFF&((data)<<0))
#define ISO_USB1_SRAM_PWR2_sd_reg_src(data)                                          ((0xFFFFFFFF&(data))>>0)
#define ISO_USB1_SRAM_PWR2_get_sd_reg(data)                                          ((0xFFFFFFFF&(data))>>0)


#define ISO_USB1_SRAM_PWR3                                                           0x98007f9c
#define ISO_USB1_SRAM_PWR3_reg_addr                                                  "0x98007F9C"
#define ISO_USB1_SRAM_PWR3_reg                                                       0x98007F9C
#define set_ISO_USB1_SRAM_PWR3_reg(data)   (*((volatile unsigned int*) ISO_USB1_SRAM_PWR3_reg)=data)
#define get_ISO_USB1_SRAM_PWR3_reg   (*((volatile unsigned int*) ISO_USB1_SRAM_PWR3_reg))
#define ISO_USB1_SRAM_PWR3_inst_adr                                                  "0x00E7"
#define ISO_USB1_SRAM_PWR3_inst                                                      0x00E7
#define ISO_USB1_SRAM_PWR3_mux_reg_shift                                             (0)
#define ISO_USB1_SRAM_PWR3_mux_reg_mask                                              (0xFFFFFFFF)
#define ISO_USB1_SRAM_PWR3_mux_reg(data)                                             (0xFFFFFFFF&((data)<<0))
#define ISO_USB1_SRAM_PWR3_mux_reg_src(data)                                         ((0xFFFFFFFF&(data))>>0)
#define ISO_USB1_SRAM_PWR3_get_mux_reg(data)                                         ((0xFFFFFFFF&(data))>>0)


#define ISO_USB1_SRAM_PWR4                                                           0x98007fa0
#define ISO_USB1_SRAM_PWR4_reg_addr                                                  "0x98007FA0"
#define ISO_USB1_SRAM_PWR4_reg                                                       0x98007FA0
#define set_ISO_USB1_SRAM_PWR4_reg(data)   (*((volatile unsigned int*) ISO_USB1_SRAM_PWR4_reg)=data)
#define get_ISO_USB1_SRAM_PWR4_reg   (*((volatile unsigned int*) ISO_USB1_SRAM_PWR4_reg))
#define ISO_USB1_SRAM_PWR4_inst_adr                                                  "0x00E8"
#define ISO_USB1_SRAM_PWR4_inst                                                      0x00E8
#define ISO_USB1_SRAM_PWR4_ctrl_shift                                                (0)
#define ISO_USB1_SRAM_PWR4_ctrl_mask                                                 (0xFFFFFFFF)
#define ISO_USB1_SRAM_PWR4_ctrl(data)                                                (0xFFFFFFFF&((data)<<0))
#define ISO_USB1_SRAM_PWR4_ctrl_src(data)                                            ((0xFFFFFFFF&(data))>>0)
#define ISO_USB1_SRAM_PWR4_get_ctrl(data)                                            ((0xFFFFFFFF&(data))>>0)


#if 0
#define ISO_USB1_SRAM_PWR5                                                           0x98007fa4
#define ISO_USB1_SRAM_PWR5_reg_addr                                                  "0x98007FA4"
#define ISO_USB1_SRAM_PWR5_reg                                                       0x98007FA4
#define set_ISO_USB1_SRAM_PWR5_reg(data)   (*((volatile unsigned int*) ISO_USB1_SRAM_PWR5_reg)=data)
#define get_ISO_USB1_SRAM_PWR5_reg   (*((volatile unsigned int*) ISO_USB1_SRAM_PWR5_reg))
#define ISO_USB1_SRAM_PWR5_inst_adr                                                  "0x00E9"
#define ISO_USB1_SRAM_PWR5_inst                                                      0x00E9
#define ISO_USB1_SRAM_PWR5_ve3_sram_int_mask_shift                                   (4)
#define ISO_USB1_SRAM_PWR5_ve3_sram_int_mask_mask                                    (0x00000010)
#define ISO_USB1_SRAM_PWR5_ve3_sram_int_mask(data)                                   (0x00000010&((data)<<4))
#define ISO_USB1_SRAM_PWR5_ve3_sram_int_mask_src(data)                               ((0x00000010&(data))>>4)
#define ISO_USB1_SRAM_PWR5_get_ve3_sram_int_mask(data)                               ((0x00000010&(data))>>4)
#define ISO_USB1_SRAM_PWR5_ve3_sram_int_shift                                        (2)
#define ISO_USB1_SRAM_PWR5_ve3_sram_int_mask                                         (0x00000004)
#define ISO_USB1_SRAM_PWR5_ve3_sram_int(data)                                        (0x00000004&((data)<<2))
#define ISO_USB1_SRAM_PWR5_ve3_sram_int_src(data)                                    ((0x00000004&(data))>>2)
#define ISO_USB1_SRAM_PWR5_get_ve3_sram_int(data)                                    ((0x00000004&(data))>>2)
#define ISO_USB1_SRAM_PWR5_write_data_shift                                          (0)
#define ISO_USB1_SRAM_PWR5_write_data_mask                                           (0x00000001)
#define ISO_USB1_SRAM_PWR5_write_data(data)                                          (0x00000001&((data)<<0))
#define ISO_USB1_SRAM_PWR5_write_data_src(data)                                      ((0x00000001&(data))>>0)
#define ISO_USB1_SRAM_PWR5_get_write_data(data)                                      ((0x00000001&(data))>>0)
#endif


#define ISO_USB1_SRAM_PWR6                                                           0x98007fa8
#define ISO_USB1_SRAM_PWR6_reg_addr                                                  "0x98007FA8"
#define ISO_USB1_SRAM_PWR6_reg                                                       0x98007FA8
#define set_ISO_USB1_SRAM_PWR6_reg(data)   (*((volatile unsigned int*) ISO_USB1_SRAM_PWR6_reg)=data)
#define get_ISO_USB1_SRAM_PWR6_reg   (*((volatile unsigned int*) ISO_USB1_SRAM_PWR6_reg))
#define ISO_USB1_SRAM_PWR6_inst_adr                                                  "0x00EA"
#define ISO_USB1_SRAM_PWR6_inst                                                      0x00EA
#define ISO_USB1_SRAM_PWR6_last_delay_cycle_shift                                    (0)
#define ISO_USB1_SRAM_PWR6_last_delay_cycle_mask                                     (0xFFFFFFFF)
#define ISO_USB1_SRAM_PWR6_last_delay_cycle(data)                                    (0xFFFFFFFF&((data)<<0))
#define ISO_USB1_SRAM_PWR6_last_delay_cycle_src(data)                                ((0xFFFFFFFF&(data))>>0)
#define ISO_USB1_SRAM_PWR6_get_last_delay_cycle(data)                                ((0xFFFFFFFF&(data))>>0)


#define ISO_USB1_SRAM_PWR7                                                           0x98007fac
#define ISO_USB1_SRAM_PWR7_reg_addr                                                  "0x98007FAC"
#define ISO_USB1_SRAM_PWR7_reg                                                       0x98007FAC
#define set_ISO_USB1_SRAM_PWR7_reg(data)   (*((volatile unsigned int*) ISO_USB1_SRAM_PWR7_reg)=data)
#define get_ISO_USB1_SRAM_PWR7_reg   (*((volatile unsigned int*) ISO_USB1_SRAM_PWR7_reg))
#define ISO_USB1_SRAM_PWR7_inst_adr                                                  "0x00EB"
#define ISO_USB1_SRAM_PWR7_inst                                                      0x00EB
#define ISO_USB1_SRAM_PWR7_pg_switch_info_shift                                      (0)
#define ISO_USB1_SRAM_PWR7_pg_switch_info_mask                                       (0xFFFFFFFF)
#define ISO_USB1_SRAM_PWR7_pg_switch_info(data)                                      (0xFFFFFFFF&((data)<<0))
#define ISO_USB1_SRAM_PWR7_pg_switch_info_src(data)                                  ((0xFFFFFFFF&(data))>>0)
#define ISO_USB1_SRAM_PWR7_get_pg_switch_info(data)                                  ((0xFFFFFFFF&(data))>>0)


#define ISO_USB_CTRL                                                                 0x98007FB0
#define ISO_USB_CTRL_reg_addr                                                        "0x98007FB0"
#define ISO_USB_CTRL_reg                                                             0x98007FB0
#define set_ISO_USB_CTRL_reg(data)   (*((volatile unsigned int*) ISO_USB_CTRL_reg)=data)
#define get_ISO_USB_CTRL_reg   (*((volatile unsigned int*) ISO_USB_CTRL_reg))
#define ISO_USB_CTRL_inst_adr                                                        "0x00EC"
#define ISO_USB_CTRL_inst                                                            0x00EC
#define ISO_USB_CTRL_iso_usb_u2phy_hst_dcp_en_3_shift                                (31)
#define ISO_USB_CTRL_iso_usb_u2phy_hst_dcp_en_3_mask                                 (0x80000000)
#define ISO_USB_CTRL_iso_usb_u2phy_hst_dcp_en_3(data)                                (0x80000000&((data)<<31))
#define ISO_USB_CTRL_iso_usb_u2phy_hst_dcp_en_3_src(data)                            ((0x80000000&(data))>>31)
#define ISO_USB_CTRL_get_iso_usb_u2phy_hst_dcp_en_3(data)                            ((0x80000000&(data))>>31)
#define ISO_USB_CTRL_iso_usb_u2phy_hst_dcp_en_2_shift                                (30)
#define ISO_USB_CTRL_iso_usb_u2phy_hst_dcp_en_2_mask                                 (0x40000000)
#define ISO_USB_CTRL_iso_usb_u2phy_hst_dcp_en_2(data)                                (0x40000000&((data)<<30))
#define ISO_USB_CTRL_iso_usb_u2phy_hst_dcp_en_2_src(data)                            ((0x40000000&(data))>>30)
#define ISO_USB_CTRL_get_iso_usb_u2phy_hst_dcp_en_2(data)                            ((0x40000000&(data))>>30)
#define ISO_USB_CTRL_iso_usb_u2phy_hst_dcp_en_1_shift                                (29)
#define ISO_USB_CTRL_iso_usb_u2phy_hst_dcp_en_1_mask                                 (0x20000000)
#define ISO_USB_CTRL_iso_usb_u2phy_hst_dcp_en_1(data)                                (0x20000000&((data)<<29))
#define ISO_USB_CTRL_iso_usb_u2phy_hst_dcp_en_1_src(data)                            ((0x20000000&(data))>>29)
#define ISO_USB_CTRL_get_iso_usb_u2phy_hst_dcp_en_1(data)                            ((0x20000000&(data))>>29)
#define ISO_USB_CTRL_iso_usb_u2phy_hst_dcp_en_0_shift                                (28)
#define ISO_USB_CTRL_iso_usb_u2phy_hst_dcp_en_0_mask                                 (0x10000000)
#define ISO_USB_CTRL_iso_usb_u2phy_hst_dcp_en_0(data)                                (0x10000000&((data)<<28))
#define ISO_USB_CTRL_iso_usb_u2phy_hst_dcp_en_0_src(data)                            ((0x10000000&(data))>>28)
#define ISO_USB_CTRL_get_iso_usb_u2phy_hst_dcp_en_0(data)                            ((0x10000000&(data))>>28)
#define ISO_USB_CTRL_iso_usb_u2phy_lf_pd_r_en_3_shift                                (27)
#define ISO_USB_CTRL_iso_usb_u2phy_lf_pd_r_en_3_mask                                 (0x08000000)
#define ISO_USB_CTRL_iso_usb_u2phy_lf_pd_r_en_3(data)                                (0x08000000&((data)<<27))
#define ISO_USB_CTRL_iso_usb_u2phy_lf_pd_r_en_3_src(data)                            ((0x08000000&(data))>>27)
#define ISO_USB_CTRL_get_iso_usb_u2phy_lf_pd_r_en_3(data)                            ((0x08000000&(data))>>27)
#define ISO_USB_CTRL_iso_usb_u2phy_lf_pd_r_en_2_shift                                (26)
#define ISO_USB_CTRL_iso_usb_u2phy_lf_pd_r_en_2_mask                                 (0x04000000)
#define ISO_USB_CTRL_iso_usb_u2phy_lf_pd_r_en_2(data)                                (0x04000000&((data)<<26))
#define ISO_USB_CTRL_iso_usb_u2phy_lf_pd_r_en_2_src(data)                            ((0x04000000&(data))>>26)
#define ISO_USB_CTRL_get_iso_usb_u2phy_lf_pd_r_en_2(data)                            ((0x04000000&(data))>>26)
#define ISO_USB_CTRL_iso_usb_u2phy_lf_pd_r_en_1_shift                                (25)
#define ISO_USB_CTRL_iso_usb_u2phy_lf_pd_r_en_1_mask                                 (0x02000000)
#define ISO_USB_CTRL_iso_usb_u2phy_lf_pd_r_en_1(data)                                (0x02000000&((data)<<25))
#define ISO_USB_CTRL_iso_usb_u2phy_lf_pd_r_en_1_src(data)                            ((0x02000000&(data))>>25)
#define ISO_USB_CTRL_get_iso_usb_u2phy_lf_pd_r_en_1(data)                            ((0x02000000&(data))>>25)
#define ISO_USB_CTRL_iso_usb_u2phy_lf_pd_r_en_0_shift                                (24)
#define ISO_USB_CTRL_iso_usb_u2phy_lf_pd_r_en_0_mask                                 (0x01000000)
#define ISO_USB_CTRL_iso_usb_u2phy_lf_pd_r_en_0(data)                                (0x01000000&((data)<<24))
#define ISO_USB_CTRL_iso_usb_u2phy_lf_pd_r_en_0_src(data)                            ((0x01000000&(data))>>24)
#define ISO_USB_CTRL_get_iso_usb_u2phy_lf_pd_r_en_0(data)                            ((0x01000000&(data))>>24)
#define ISO_USB_CTRL_iso_usb_u2phy_reg_ldo_pw_3_shift                                (23)
#define ISO_USB_CTRL_iso_usb_u2phy_reg_ldo_pw_3_mask                                 (0x00800000)
#define ISO_USB_CTRL_iso_usb_u2phy_reg_ldo_pw_3(data)                                (0x00800000&((data)<<23))
#define ISO_USB_CTRL_iso_usb_u2phy_reg_ldo_pw_3_src(data)                            ((0x00800000&(data))>>23)
#define ISO_USB_CTRL_get_iso_usb_u2phy_reg_ldo_pw_3(data)                            ((0x00800000&(data))>>23)
#define ISO_USB_CTRL_iso_usb_u2phy_reg_ldo_pw_2_shift                                (22)
#define ISO_USB_CTRL_iso_usb_u2phy_reg_ldo_pw_2_mask                                 (0x00400000)
#define ISO_USB_CTRL_iso_usb_u2phy_reg_ldo_pw_2(data)                                (0x00400000&((data)<<22))
#define ISO_USB_CTRL_iso_usb_u2phy_reg_ldo_pw_2_src(data)                            ((0x00400000&(data))>>22)
#define ISO_USB_CTRL_get_iso_usb_u2phy_reg_ldo_pw_2(data)                            ((0x00400000&(data))>>22)
#define ISO_USB_CTRL_iso_usb_u2phy_reg_ldo_pw_1_shift                                (21)
#define ISO_USB_CTRL_iso_usb_u2phy_reg_ldo_pw_1_mask                                 (0x00200000)
#define ISO_USB_CTRL_iso_usb_u2phy_reg_ldo_pw_1(data)                                (0x00200000&((data)<<21))
#define ISO_USB_CTRL_iso_usb_u2phy_reg_ldo_pw_1_src(data)                            ((0x00200000&(data))>>21)
#define ISO_USB_CTRL_get_iso_usb_u2phy_reg_ldo_pw_1(data)                            ((0x00200000&(data))>>21)
#define ISO_USB_CTRL_iso_usb_u2phy_reg_ldo_pw_0_shift                                (20)
#define ISO_USB_CTRL_iso_usb_u2phy_reg_ldo_pw_0_mask                                 (0x00100000)
#define ISO_USB_CTRL_iso_usb_u2phy_reg_ldo_pw_0(data)                                (0x00100000&((data)<<20))
#define ISO_USB_CTRL_iso_usb_u2phy_reg_ldo_pw_0_src(data)                            ((0x00100000&(data))>>20)
#define ISO_USB_CTRL_get_iso_usb_u2phy_reg_ldo_pw_0(data)                            ((0x00100000&(data))>>20)
#define ISO_USB_CTRL_iso_usb_u2phy_by_paa_on_3_shift                                 (19)
#define ISO_USB_CTRL_iso_usb_u2phy_by_paa_on_3_mask                                  (0x00080000)
#define ISO_USB_CTRL_iso_usb_u2phy_by_paa_on_3(data)                                 (0x00080000&((data)<<19))
#define ISO_USB_CTRL_iso_usb_u2phy_by_paa_on_3_src(data)                             ((0x00080000&(data))>>19)
#define ISO_USB_CTRL_get_iso_usb_u2phy_by_paa_on_3(data)                             ((0x00080000&(data))>>19)
#define ISO_USB_CTRL_iso_usb_u2phy_by_paa_on_2_shift                                 (18)
#define ISO_USB_CTRL_iso_usb_u2phy_by_paa_on_2_mask                                  (0x00040000)
#define ISO_USB_CTRL_iso_usb_u2phy_by_paa_on_2(data)                                 (0x00040000&((data)<<18))
#define ISO_USB_CTRL_iso_usb_u2phy_by_paa_on_2_src(data)                             ((0x00040000&(data))>>18)
#define ISO_USB_CTRL_get_iso_usb_u2phy_by_paa_on_2(data)                             ((0x00040000&(data))>>18)
#define ISO_USB_CTRL_iso_usb_u2phy_by_paa_on_1_shift                                 (17)
#define ISO_USB_CTRL_iso_usb_u2phy_by_paa_on_1_mask                                  (0x00020000)
#define ISO_USB_CTRL_iso_usb_u2phy_by_paa_on_1(data)                                 (0x00020000&((data)<<17))
#define ISO_USB_CTRL_iso_usb_u2phy_by_paa_on_1_src(data)                             ((0x00020000&(data))>>17)
#define ISO_USB_CTRL_get_iso_usb_u2phy_by_paa_on_1(data)                             ((0x00020000&(data))>>17)
#define ISO_USB_CTRL_iso_usb_u2phy_by_paa_on_0_shift                                 (16)
#define ISO_USB_CTRL_iso_usb_u2phy_by_paa_on_0_mask                                  (0x00010000)
#define ISO_USB_CTRL_iso_usb_u2phy_by_paa_on_0(data)                                 (0x00010000&((data)<<16))
#define ISO_USB_CTRL_iso_usb_u2phy_by_paa_on_0_src(data)                             ((0x00010000&(data))>>16)
#define ISO_USB_CTRL_get_iso_usb_u2phy_by_paa_on_0(data)                             ((0x00010000&(data))>>16)
#define ISO_USB_CTRL_iso_usb_p3_isoctrl_en_shift                                     (9)
#define ISO_USB_CTRL_iso_usb_p3_isoctrl_en_mask                                      (0x00000200)
#define ISO_USB_CTRL_iso_usb_p3_isoctrl_en(data)                                     (0x00000200&((data)<<9))
#define ISO_USB_CTRL_iso_usb_p3_isoctrl_en_src(data)                                 ((0x00000200&(data))>>9)
#define ISO_USB_CTRL_get_iso_usb_p3_isoctrl_en(data)                                 ((0x00000200&(data))>>9)
#define ISO_USB_CTRL_iso_usb_p012_isoctrl_en_shift                                   (8)
#define ISO_USB_CTRL_iso_usb_p012_isoctrl_en_mask                                    (0x00000100)
#define ISO_USB_CTRL_iso_usb_p012_isoctrl_en(data)                                   (0x00000100&((data)<<8))
#define ISO_USB_CTRL_iso_usb_p012_isoctrl_en_src(data)                               ((0x00000100&(data))>>8)
#define ISO_USB_CTRL_get_iso_usb_p012_isoctrl_en(data)                               ((0x00000100&(data))>>8)
#define ISO_USB_CTRL_iso_usb_u2phy_pg_en_shift                                       (6)
#define ISO_USB_CTRL_iso_usb_u2phy_pg_en_mask                                        (0x00000040)
#define ISO_USB_CTRL_iso_usb_u2phy_pg_en(data)                                       (0x00000040&((data)<<6))
#define ISO_USB_CTRL_iso_usb_u2phy_pg_en_src(data)                                   ((0x00000040&(data))>>6)
#define ISO_USB_CTRL_get_iso_usb_u2phy_pg_en(data)                                   ((0x00000040&(data))>>6)
#define ISO_USB_CTRL_iso_usb_u3phy_p1_pg_en_shift                                    (5)
#define ISO_USB_CTRL_iso_usb_u3phy_p1_pg_en_mask                                     (0x00000020)
#define ISO_USB_CTRL_iso_usb_u3phy_p1_pg_en(data)                                    (0x00000020&((data)<<5))
#define ISO_USB_CTRL_iso_usb_u3phy_p1_pg_en_src(data)                                ((0x00000020&(data))>>5)
#define ISO_USB_CTRL_get_iso_usb_u3phy_p1_pg_en(data)                                ((0x00000020&(data))>>5)
#define ISO_USB_CTRL_iso_usb_u3phy_p0_pg_en_shift                                    (4)
#define ISO_USB_CTRL_iso_usb_u3phy_p0_pg_en_mask                                     (0x00000010)
#define ISO_USB_CTRL_iso_usb_u3phy_p0_pg_en(data)                                    (0x00000010&((data)<<4))
#define ISO_USB_CTRL_iso_usb_u3phy_p0_pg_en_src(data)                                ((0x00000010&(data))>>4)
#define ISO_USB_CTRL_get_iso_usb_u3phy_p0_pg_en(data)                                ((0x00000010&(data))>>4)
#define ISO_USB_CTRL_iso_usb_p3_pg_en_shift                                          (1)
#define ISO_USB_CTRL_iso_usb_p3_pg_en_mask                                           (0x00000002)
#define ISO_USB_CTRL_iso_usb_p3_pg_en(data)                                          (0x00000002&((data)<<1))
#define ISO_USB_CTRL_iso_usb_p3_pg_en_src(data)                                      ((0x00000002&(data))>>1)
#define ISO_USB_CTRL_get_iso_usb_p3_pg_en(data)                                      ((0x00000002&(data))>>1)
#define ISO_USB_CTRL_iso_usb_p012_pg_en_shift                                        (0)
#define ISO_USB_CTRL_iso_usb_p012_pg_en_mask                                         (0x00000001)
#define ISO_USB_CTRL_iso_usb_p012_pg_en(data)                                        (0x00000001&((data)<<0))
#define ISO_USB_CTRL_iso_usb_p012_pg_en_src(data)                                    ((0x00000001&(data))>>0)
#define ISO_USB_CTRL_get_iso_usb_p012_pg_en(data)                                    ((0x00000001&(data))>>0)


#define ISO_ETN_DBUS_CTRL                                                            0x98007FC0
#define ISO_ETN_DBUS_CTRL_reg_addr                                                   "0x98007FC0"
#define ISO_ETN_DBUS_CTRL_reg                                                        0x98007FC0
#define set_ISO_ETN_DBUS_CTRL_reg(data)   (*((volatile unsigned int*) ISO_ETN_DBUS_CTRL_reg)=data)
#define get_ISO_ETN_DBUS_CTRL_reg   (*((volatile unsigned int*) ISO_ETN_DBUS_CTRL_reg))
#define ISO_ETN_DBUS_CTRL_inst_adr                                                   "0x00F0"
#define ISO_ETN_DBUS_CTRL_inst                                                       0x00F0
#define ISO_ETN_DBUS_CTRL_so_etn_sram_ls_gap_shift                                   (4)
#define ISO_ETN_DBUS_CTRL_so_etn_sram_ls_gap_mask                                    (0x00000030)
#define ISO_ETN_DBUS_CTRL_so_etn_sram_ls_gap(data)                                   (0x00000030&((data)<<4))
#define ISO_ETN_DBUS_CTRL_so_etn_sram_ls_gap_src(data)                               ((0x00000030&(data))>>4)
#define ISO_ETN_DBUS_CTRL_get_so_etn_sram_ls_gap(data)                               ((0x00000030&(data))>>4)
#define ISO_ETN_DBUS_CTRL_so_etn_clk_en_gap_shift                                    (2)
#define ISO_ETN_DBUS_CTRL_so_etn_clk_en_gap_mask                                     (0x0000000C)
#define ISO_ETN_DBUS_CTRL_so_etn_clk_en_gap(data)                                    (0x0000000C&((data)<<2))
#define ISO_ETN_DBUS_CTRL_so_etn_clk_en_gap_src(data)                                ((0x0000000C&(data))>>2)
#define ISO_ETN_DBUS_CTRL_get_so_etn_clk_en_gap(data)                                ((0x0000000C&(data))>>2)
#define ISO_ETN_DBUS_CTRL_so_etn_pwr_ctrl_sw_rst_shift                               (1)
#define ISO_ETN_DBUS_CTRL_so_etn_pwr_ctrl_sw_rst_mask                                (0x00000002)
#define ISO_ETN_DBUS_CTRL_so_etn_pwr_ctrl_sw_rst(data)                               (0x00000002&((data)<<1))
#define ISO_ETN_DBUS_CTRL_so_etn_pwr_ctrl_sw_rst_src(data)                           ((0x00000002&(data))>>1)
#define ISO_ETN_DBUS_CTRL_get_so_etn_pwr_ctrl_sw_rst(data)                           ((0x00000002&(data))>>1)
#define ISO_ETN_DBUS_CTRL_iso_etn_pwr_ctrl_en_shift                                  (0)
#define ISO_ETN_DBUS_CTRL_iso_etn_pwr_ctrl_en_mask                                   (0x00000001)
#define ISO_ETN_DBUS_CTRL_iso_etn_pwr_ctrl_en(data)                                  (0x00000001&((data)<<0))
#define ISO_ETN_DBUS_CTRL_iso_etn_pwr_ctrl_en_src(data)                              ((0x00000001&(data))>>0)
#define ISO_ETN_DBUS_CTRL_get_iso_etn_pwr_ctrl_en(data)                              ((0x00000001&(data))>>0)


#define ISO_ETN_BIST_DROM_GOLDEN                                                     0x98007FC4
#define ISO_ETN_BIST_DROM_GOLDEN_reg_addr                                            "0x98007FC4"
#define ISO_ETN_BIST_DROM_GOLDEN_reg                                                 0x98007FC4
#define set_ISO_ETN_BIST_DROM_GOLDEN_reg(data)   (*((volatile unsigned int*) ISO_ETN_BIST_DROM_GOLDEN_reg)=data)
#define get_ISO_ETN_BIST_DROM_GOLDEN_reg   (*((volatile unsigned int*) ISO_ETN_BIST_DROM_GOLDEN_reg))
#define ISO_ETN_BIST_DROM_GOLDEN_inst_adr                                            "0x00F1"
#define ISO_ETN_BIST_DROM_GOLDEN_inst                                                0x00F1
#define ISO_ETN_BIST_DROM_GOLDEN_iso_etn_drom_golden_shift                           (0)
#define ISO_ETN_BIST_DROM_GOLDEN_iso_etn_drom_golden_mask                            (0xFFFFFFFF)
#define ISO_ETN_BIST_DROM_GOLDEN_iso_etn_drom_golden(data)                           (0xFFFFFFFF&((data)<<0))
#define ISO_ETN_BIST_DROM_GOLDEN_iso_etn_drom_golden_src(data)                       ((0xFFFFFFFF&(data))>>0)
#define ISO_ETN_BIST_DROM_GOLDEN_get_iso_etn_drom_golden(data)                       ((0xFFFFFFFF&(data))>>0)


#define ISO_ETN_BIST_IROM_GOLDEN                                                     0x98007FC8
#define ISO_ETN_BIST_IROM_GOLDEN_reg_addr                                            "0x98007FC8"
#define ISO_ETN_BIST_IROM_GOLDEN_reg                                                 0x98007FC8
#define set_ISO_ETN_BIST_IROM_GOLDEN_reg(data)   (*((volatile unsigned int*) ISO_ETN_BIST_IROM_GOLDEN_reg)=data)
#define get_ISO_ETN_BIST_IROM_GOLDEN_reg   (*((volatile unsigned int*) ISO_ETN_BIST_IROM_GOLDEN_reg))
#define ISO_ETN_BIST_IROM_GOLDEN_inst_adr                                            "0x00F2"
#define ISO_ETN_BIST_IROM_GOLDEN_inst                                                0x00F2
#define ISO_ETN_BIST_IROM_GOLDEN_iso_etn_irom_golden_shift                           (0)
#define ISO_ETN_BIST_IROM_GOLDEN_iso_etn_irom_golden_mask                            (0xFFFFFFFF)
#define ISO_ETN_BIST_IROM_GOLDEN_iso_etn_irom_golden(data)                           (0xFFFFFFFF&((data)<<0))
#define ISO_ETN_BIST_IROM_GOLDEN_iso_etn_irom_golden_src(data)                       ((0xFFFFFFFF&(data))>>0)
#define ISO_ETN_BIST_IROM_GOLDEN_get_iso_etn_irom_golden(data)                       ((0xFFFFFFFF&(data))>>0)


#define ISO_ETN_BIST_FTR_ROM_GOLDEN                                                  0x98007FCC
#define ISO_ETN_BIST_FTR_ROM_GOLDEN_reg_addr                                         "0x98007FCC"
#define ISO_ETN_BIST_FTR_ROM_GOLDEN_reg                                              0x98007FCC
#define set_ISO_ETN_BIST_FTR_ROM_GOLDEN_reg(data)   (*((volatile unsigned int*) ISO_ETN_BIST_FTR_ROM_GOLDEN_reg)=data)
#define get_ISO_ETN_BIST_FTR_ROM_GOLDEN_reg   (*((volatile unsigned int*) ISO_ETN_BIST_FTR_ROM_GOLDEN_reg))
#define ISO_ETN_BIST_FTR_ROM_GOLDEN_inst_adr                                         "0x00F3"
#define ISO_ETN_BIST_FTR_ROM_GOLDEN_inst                                             0x00F3
#define ISO_ETN_BIST_FTR_ROM_GOLDEN_iso_etn_ftr_rom_golden_shift                     (0)
#define ISO_ETN_BIST_FTR_ROM_GOLDEN_iso_etn_ftr_rom_golden_mask                      (0xFFFFFFFF)
#define ISO_ETN_BIST_FTR_ROM_GOLDEN_iso_etn_ftr_rom_golden(data)                     (0xFFFFFFFF&((data)<<0))
#define ISO_ETN_BIST_FTR_ROM_GOLDEN_iso_etn_ftr_rom_golden_src(data)                 ((0xFFFFFFFF&(data))>>0)
#define ISO_ETN_BIST_FTR_ROM_GOLDEN_get_iso_etn_ftr_rom_golden(data)                 ((0xFFFFFFFF&(data))>>0)


#define ISO_DCO_0                                                                    0x980070F0
#define ISO_DCO_0_reg_addr                                                           "0x980070F0"
#define ISO_DCO_0_reg                                                                0x980070F0
#define set_ISO_DCO_0_reg(data)   (*((volatile unsigned int*) ISO_DCO_0_reg)=data)
#define get_ISO_DCO_0_reg   (*((volatile unsigned int*) ISO_DCO_0_reg))
#define ISO_DCO_0_inst_adr                                                           "0x003C"
#define ISO_DCO_0_inst                                                               0x003C
#define ISO_DCO_0_osc_count_limit_shift                                              (10)
#define ISO_DCO_0_osc_count_limit_mask                                               (0x003FFC00)
#define ISO_DCO_0_osc_count_limit(data)                                              (0x003FFC00&((data)<<10))
#define ISO_DCO_0_osc_count_limit_src(data)                                          ((0x003FFC00&(data))>>10)
#define ISO_DCO_0_get_osc_count_limit(data)                                          ((0x003FFC00&(data))>>10)
#define ISO_DCO_0_xtal_off_shift                                                     (2)
#define ISO_DCO_0_xtal_off_mask                                                      (0x00000004)
#define ISO_DCO_0_xtal_off(data)                                                     (0x00000004&((data)<<2))
#define ISO_DCO_0_xtal_off_src(data)                                                 ((0x00000004&(data))>>2)
#define ISO_DCO_0_get_xtal_off(data)                                                 ((0x00000004&(data))>>2)
#define ISO_DCO_0_dco_sel_shift                                                      (1)
#define ISO_DCO_0_dco_sel_mask                                                       (0x00000002)
#define ISO_DCO_0_dco_sel(data)                                                      (0x00000002&((data)<<1))
#define ISO_DCO_0_dco_sel_src(data)                                                  ((0x00000002&(data))>>1)
#define ISO_DCO_0_get_dco_sel(data)                                                  ((0x00000002&(data))>>1)
#define ISO_DCO_0_cal_enable_shift                                                   (0)
#define ISO_DCO_0_cal_enable_mask                                                    (0x00000001)
#define ISO_DCO_0_cal_enable(data)                                                   (0x00000001&((data)<<0))
#define ISO_DCO_0_cal_enable_src(data)                                               ((0x00000001&(data))>>0)
#define ISO_DCO_0_get_cal_enable(data)                                               ((0x00000001&(data))>>0)


#define ISO_DCO_1                                                                    0x980070F4
#define ISO_DCO_1_reg_addr                                                           "0x980070F4"
#define ISO_DCO_1_reg                                                                0x980070F4
#define set_ISO_DCO_1_reg(data)   (*((volatile unsigned int*) ISO_DCO_1_reg)=data)
#define get_ISO_DCO_1_reg   (*((volatile unsigned int*) ISO_DCO_1_reg))
#define ISO_DCO_1_inst_adr                                                           "0x003D"
#define ISO_DCO_1_inst                                                               0x003D
#define ISO_DCO_1_dco_count_latch_shift                                              (13)
#define ISO_DCO_1_dco_count_latch_mask                                               (0x01FFE000)
#define ISO_DCO_1_dco_count_latch(data)                                              (0x01FFE000&((data)<<13))
#define ISO_DCO_1_dco_count_latch_src(data)                                          ((0x01FFE000&(data))>>13)
#define ISO_DCO_1_get_dco_count_latch(data)                                          ((0x01FFE000&(data))>>13)
#define ISO_DCO_1_xtal_count_latch_shift                                             (1)
#define ISO_DCO_1_xtal_count_latch_mask                                              (0x00001FFE)
#define ISO_DCO_1_xtal_count_latch(data)                                             (0x00001FFE&((data)<<1))
#define ISO_DCO_1_xtal_count_latch_src(data)                                         ((0x00001FFE&(data))>>1)
#define ISO_DCO_1_get_xtal_count_latch(data)                                         ((0x00001FFE&(data))>>1)
#define ISO_DCO_1_dco_cal_done_shift                                                 (0)
#define ISO_DCO_1_dco_cal_done_mask                                                  (0x00000001)
#define ISO_DCO_1_dco_cal_done(data)                                                 (0x00000001&((data)<<0))
#define ISO_DCO_1_dco_cal_done_src(data)                                             ((0x00000001&(data))>>0)
#define ISO_DCO_1_get_dco_cal_done(data)                                             ((0x00000001&(data))>>0)


#define ISO_GPDIR                                                                    0x98007100
#define ISO_GPDIR_reg_addr                                                           "0x98007100"
#define ISO_GPDIR_reg                                                                0x98007100
#define set_ISO_GPDIR_reg(data)   (*((volatile unsigned int*) ISO_GPDIR_reg)=data)
#define get_ISO_GPDIR_reg   (*((volatile unsigned int*) ISO_GPDIR_reg))
#define ISO_GPDIR_inst_adr                                                           "0x0040"
#define ISO_GPDIR_inst                                                               0x0040
#define ISO_GPDIR_gpdir_shift                                                        (0)
#define ISO_GPDIR_gpdir_mask                                                         (0xFFFFFFFF)
#define ISO_GPDIR_gpdir(data)                                                        (0xFFFFFFFF&((data)<<0))
#define ISO_GPDIR_gpdir_src(data)                                                    ((0xFFFFFFFF&(data))>>0)
#define ISO_GPDIR_get_gpdir(data)                                                    ((0xFFFFFFFF&(data))>>0)


#define ISO_GPDATO                                                                   0x98007104
#define ISO_GPDATO_reg_addr                                                          "0x98007104"
#define ISO_GPDATO_reg                                                               0x98007104
#define set_ISO_GPDATO_reg(data)   (*((volatile unsigned int*) ISO_GPDATO_reg)=data)
#define get_ISO_GPDATO_reg   (*((volatile unsigned int*) ISO_GPDATO_reg))
#define ISO_GPDATO_inst_adr                                                          "0x0041"
#define ISO_GPDATO_inst                                                              0x0041
#define ISO_GPDATO_gpdato_shift                                                      (0)
#define ISO_GPDATO_gpdato_mask                                                       (0xFFFFFFFF)
#define ISO_GPDATO_gpdato(data)                                                      (0xFFFFFFFF&((data)<<0))
#define ISO_GPDATO_gpdato_src(data)                                                  ((0xFFFFFFFF&(data))>>0)
#define ISO_GPDATO_get_gpdato(data)                                                  ((0xFFFFFFFF&(data))>>0)


#define ISO_GPDATI                                                                   0x98007108
#define ISO_GPDATI_reg_addr                                                          "0x98007108"
#define ISO_GPDATI_reg                                                               0x98007108
#define set_ISO_GPDATI_reg(data)   (*((volatile unsigned int*) ISO_GPDATI_reg)=data)
#define get_ISO_GPDATI_reg   (*((volatile unsigned int*) ISO_GPDATI_reg))
#define ISO_GPDATI_inst_adr                                                          "0x0042"
#define ISO_GPDATI_inst                                                              0x0042
#define ISO_GPDATI_gpdati_shift                                                      (0)
#define ISO_GPDATI_gpdati_mask                                                       (0xFFFFFFFF)
#define ISO_GPDATI_gpdati(data)                                                      (0xFFFFFFFF&((data)<<0))
#define ISO_GPDATI_gpdati_src(data)                                                  ((0xFFFFFFFF&(data))>>0)
#define ISO_GPDATI_get_gpdati(data)                                                  ((0xFFFFFFFF&(data))>>0)


#define ISO_GPIE                                                                     0x9800710C
#define ISO_GPIE_reg_addr                                                            "0x9800710C"
#define ISO_GPIE_reg                                                                 0x9800710C
#define set_ISO_GPIE_reg(data)   (*((volatile unsigned int*) ISO_GPIE_reg)=data)
#define get_ISO_GPIE_reg   (*((volatile unsigned int*) ISO_GPIE_reg))
#define ISO_GPIE_inst_adr                                                            "0x0043"
#define ISO_GPIE_inst                                                                0x0043
#define ISO_GPIE_gp_shift                                                            (0)
#define ISO_GPIE_gp_mask                                                             (0xFFFFFFFF)
#define ISO_GPIE_gp(data)                                                            (0xFFFFFFFF&((data)<<0))
#define ISO_GPIE_gp_src(data)                                                        ((0xFFFFFFFF&(data))>>0)
#define ISO_GPIE_get_gp(data)                                                        ((0xFFFFFFFF&(data))>>0)


#define ISO_GPDP                                                                     0x98007110
#define ISO_GPDP_reg_addr                                                            "0x98007110"
#define ISO_GPDP_reg                                                                 0x98007110
#define set_ISO_GPDP_reg(data)   (*((volatile unsigned int*) ISO_GPDP_reg)=data)
#define get_ISO_GPDP_reg   (*((volatile unsigned int*) ISO_GPDP_reg))
#define ISO_GPDP_inst_adr                                                            "0x0044"
#define ISO_GPDP_inst                                                                0x0044
#define ISO_GPDP_gpha_shift                                                          (0)
#define ISO_GPDP_gpha_mask                                                           (0xFFFFFFFF)
#define ISO_GPDP_gpha(data)                                                          (0xFFFFFFFF&((data)<<0))
#define ISO_GPDP_gpha_src(data)                                                      ((0xFFFFFFFF&(data))>>0)
#define ISO_GPDP_get_gpha(data)                                                      ((0xFFFFFFFF&(data))>>0)


#define ISO_GPDEB                                                                    0x98007114
#define ISO_GPDEB_reg_addr                                                           "0x98007114"
#define ISO_GPDEB_reg                                                                0x98007114
#define set_ISO_GPDEB_reg(data)   (*((volatile unsigned int*) ISO_GPDEB_reg)=data)
#define get_ISO_GPDEB_reg   (*((volatile unsigned int*) ISO_GPDEB_reg))
#define ISO_GPDEB_inst_adr                                                           "0x0045"
#define ISO_GPDEB_inst                                                               0x0045
#define ISO_GPDEB_write_en1_shift                                                    (3)
#define ISO_GPDEB_write_en1_mask                                                     (0x00000008)
#define ISO_GPDEB_write_en1(data)                                                    (0x00000008&((data)<<3))
#define ISO_GPDEB_write_en1_src(data)                                                ((0x00000008&(data))>>3)
#define ISO_GPDEB_get_write_en1(data)                                                ((0x00000008&(data))>>3)
#define ISO_GPDEB_clk1_shift                                                         (0)
#define ISO_GPDEB_clk1_mask                                                          (0x00000007)
#define ISO_GPDEB_clk1(data)                                                         (0x00000007&((data)<<0))
#define ISO_GPDEB_clk1_src(data)                                                     ((0x00000007&(data))>>0)
#define ISO_GPDEB_get_clk1(data)                                                     ((0x00000007&(data))>>0)


#define ISO_GPDIR_1                                                                  0x98007118
#define ISO_GPDIR_1_reg_addr                                                         "0x98007118"
#define ISO_GPDIR_1_reg                                                              0x98007118
#define set_ISO_GPDIR_1_reg(data)   (*((volatile unsigned int*) ISO_GPDIR_1_reg)=data)
#define get_ISO_GPDIR_1_reg   (*((volatile unsigned int*) ISO_GPDIR_1_reg))
#define ISO_GPDIR_1_inst_adr                                                         "0x0046"
#define ISO_GPDIR_1_inst                                                             0x0046
#define ISO_GPDIR_1_gpdir_1_shift                                                    (0)
#define ISO_GPDIR_1_gpdir_1_mask                                                     (0x00000007)
#define ISO_GPDIR_1_gpdir_1(data)                                                    (0x00000007&((data)<<0))
#define ISO_GPDIR_1_gpdir_1_src(data)                                                ((0x00000007&(data))>>0)
#define ISO_GPDIR_1_get_gpdir_1(data)                                                ((0x00000007&(data))>>0)


#define ISO_GPDATO_1                                                                 0x9800711C
#define ISO_GPDATO_1_reg_addr                                                        "0x9800711C"
#define ISO_GPDATO_1_reg                                                             0x9800711C
#define set_ISO_GPDATO_1_reg(data)   (*((volatile unsigned int*) ISO_GPDATO_1_reg)=data)
#define get_ISO_GPDATO_1_reg   (*((volatile unsigned int*) ISO_GPDATO_1_reg))
#define ISO_GPDATO_1_inst_adr                                                        "0x0047"
#define ISO_GPDATO_1_inst                                                            0x0047
#define ISO_GPDATO_1_gpdato_1_shift                                                  (0)
#define ISO_GPDATO_1_gpdato_1_mask                                                   (0x00000007)
#define ISO_GPDATO_1_gpdato_1(data)                                                  (0x00000007&((data)<<0))
#define ISO_GPDATO_1_gpdato_1_src(data)                                              ((0x00000007&(data))>>0)
#define ISO_GPDATO_1_get_gpdato_1(data)                                              ((0x00000007&(data))>>0)


#define ISO_GPDATI_1                                                                 0x98007120
#define ISO_GPDATI_1_reg_addr                                                        "0x98007120"
#define ISO_GPDATI_1_reg                                                             0x98007120
#define set_ISO_GPDATI_1_reg(data)   (*((volatile unsigned int*) ISO_GPDATI_1_reg)=data)
#define get_ISO_GPDATI_1_reg   (*((volatile unsigned int*) ISO_GPDATI_1_reg))
#define ISO_GPDATI_1_inst_adr                                                        "0x0048"
#define ISO_GPDATI_1_inst                                                            0x0048
#define ISO_GPDATI_1_gpdati_1_shift                                                  (0)
#define ISO_GPDATI_1_gpdati_1_mask                                                   (0x00000007)
#define ISO_GPDATI_1_gpdati_1(data)                                                  (0x00000007&((data)<<0))
#define ISO_GPDATI_1_gpdati_1_src(data)                                              ((0x00000007&(data))>>0)
#define ISO_GPDATI_1_get_gpdati_1(data)                                              ((0x00000007&(data))>>0)


#define ISO_GPIE_1                                                                   0x98007124
#define ISO_GPIE_1_reg_addr                                                          "0x98007124"
#define ISO_GPIE_1_reg                                                               0x98007124
#define set_ISO_GPIE_1_reg(data)   (*((volatile unsigned int*) ISO_GPIE_1_reg)=data)
#define get_ISO_GPIE_1_reg   (*((volatile unsigned int*) ISO_GPIE_1_reg))
#define ISO_GPIE_1_inst_adr                                                          "0x0049"
#define ISO_GPIE_1_inst                                                              0x0049
#define ISO_GPIE_1_gp_1_shift                                                        (0)
#define ISO_GPIE_1_gp_1_mask                                                         (0x00000007)
#define ISO_GPIE_1_gp_1(data)                                                        (0x00000007&((data)<<0))
#define ISO_GPIE_1_gp_1_src(data)                                                    ((0x00000007&(data))>>0)
#define ISO_GPIE_1_get_gp_1(data)                                                    ((0x00000007&(data))>>0)


#define ISO_GPDP_1                                                                   0x98007128
#define ISO_GPDP_1_reg_addr                                                          "0x98007128"
#define ISO_GPDP_1_reg                                                               0x98007128
#define set_ISO_GPDP_1_reg(data)   (*((volatile unsigned int*) ISO_GPDP_1_reg)=data)
#define get_ISO_GPDP_1_reg   (*((volatile unsigned int*) ISO_GPDP_1_reg))
#define ISO_GPDP_1_inst_adr                                                          "0x004A"
#define ISO_GPDP_1_inst                                                              0x004A
#define ISO_GPDP_1_gpha_1_shift                                                      (0)
#define ISO_GPDP_1_gpha_1_mask                                                       (0x00000007)
#define ISO_GPDP_1_gpha_1(data)                                                      (0x00000007&((data)<<0))
#define ISO_GPDP_1_gpha_1_src(data)                                                  ((0x00000007&(data))>>0)
#define ISO_GPDP_1_get_gpha_1(data)                                                  ((0x00000007&(data))>>0)


#define ISO_PFUNC0                                                                   0x98007300
#define ISO_PFUNC0_reg_addr                                                          "0x98007300"
#define ISO_PFUNC0_reg                                                               0x98007300
#define set_ISO_PFUNC0_reg(data)   (*((volatile unsigned int*) ISO_PFUNC0_reg)=data)
#define get_ISO_PFUNC0_reg   (*((volatile unsigned int*) ISO_PFUNC0_reg))
#define ISO_PFUNC0_inst_adr                                                          "0x00C0"
#define ISO_PFUNC0_inst                                                              0x00C0
#define ISO_PFUNC0_i2c_scl_0_smt_shift                                               (31)
#define ISO_PFUNC0_i2c_scl_0_smt_mask                                                (0x80000000)
#define ISO_PFUNC0_i2c_scl_0_smt(data)                                               (0x80000000&((data)<<31))
#define ISO_PFUNC0_i2c_scl_0_smt_src(data)                                           ((0x80000000&(data))>>31)
#define ISO_PFUNC0_get_i2c_scl_0_smt(data)                                           ((0x80000000&(data))>>31)
#define ISO_PFUNC0_i2c_scl_0_e2_shift                                                (30)
#define ISO_PFUNC0_i2c_scl_0_e2_mask                                                 (0x40000000)
#define ISO_PFUNC0_i2c_scl_0_e2(data)                                                (0x40000000&((data)<<30))
#define ISO_PFUNC0_i2c_scl_0_e2_src(data)                                            ((0x40000000&(data))>>30)
#define ISO_PFUNC0_get_i2c_scl_0_e2(data)                                            ((0x40000000&(data))>>30)
#define ISO_PFUNC0_i2c_scl_0_pud_en_shift                                            (29)
#define ISO_PFUNC0_i2c_scl_0_pud_en_mask                                             (0x20000000)
#define ISO_PFUNC0_i2c_scl_0_pud_en(data)                                            (0x20000000&((data)<<29))
#define ISO_PFUNC0_i2c_scl_0_pud_en_src(data)                                        ((0x20000000&(data))>>29)
#define ISO_PFUNC0_get_i2c_scl_0_pud_en(data)                                        ((0x20000000&(data))>>29)
#define ISO_PFUNC0_i2c_scl_0_pud_sel_shift                                           (28)
#define ISO_PFUNC0_i2c_scl_0_pud_sel_mask                                            (0x10000000)
#define ISO_PFUNC0_i2c_scl_0_pud_sel(data)                                           (0x10000000&((data)<<28))
#define ISO_PFUNC0_i2c_scl_0_pud_sel_src(data)                                       ((0x10000000&(data))>>28)
#define ISO_PFUNC0_get_i2c_scl_0_pud_sel(data)                                       ((0x10000000&(data))>>28)
#define ISO_PFUNC0_i2c_sda_0_smt_shift                                               (27)
#define ISO_PFUNC0_i2c_sda_0_smt_mask                                                (0x08000000)
#define ISO_PFUNC0_i2c_sda_0_smt(data)                                               (0x08000000&((data)<<27))
#define ISO_PFUNC0_i2c_sda_0_smt_src(data)                                           ((0x08000000&(data))>>27)
#define ISO_PFUNC0_get_i2c_sda_0_smt(data)                                           ((0x08000000&(data))>>27)
#define ISO_PFUNC0_i2c_sda_0_e2_shift                                                (26)
#define ISO_PFUNC0_i2c_sda_0_e2_mask                                                 (0x04000000)
#define ISO_PFUNC0_i2c_sda_0_e2(data)                                                (0x04000000&((data)<<26))
#define ISO_PFUNC0_i2c_sda_0_e2_src(data)                                            ((0x04000000&(data))>>26)
#define ISO_PFUNC0_get_i2c_sda_0_e2(data)                                            ((0x04000000&(data))>>26)
#define ISO_PFUNC0_i2c_sda_0_pud_en_shift                                            (25)
#define ISO_PFUNC0_i2c_sda_0_pud_en_mask                                             (0x02000000)
#define ISO_PFUNC0_i2c_sda_0_pud_en(data)                                            (0x02000000&((data)<<25))
#define ISO_PFUNC0_i2c_sda_0_pud_en_src(data)                                        ((0x02000000&(data))>>25)
#define ISO_PFUNC0_get_i2c_sda_0_pud_en(data)                                        ((0x02000000&(data))>>25)
#define ISO_PFUNC0_i2c_sda_0_pud_sel_shift                                           (24)
#define ISO_PFUNC0_i2c_sda_0_pud_sel_mask                                            (0x01000000)
#define ISO_PFUNC0_i2c_sda_0_pud_sel(data)                                           (0x01000000&((data)<<24))
#define ISO_PFUNC0_i2c_sda_0_pud_sel_src(data)                                       ((0x01000000&(data))>>24)
#define ISO_PFUNC0_get_i2c_sda_0_pud_sel(data)                                       ((0x01000000&(data))>>24)
#define ISO_PFUNC0_iso_gpio_7_smt_shift                                              (23)
#define ISO_PFUNC0_iso_gpio_7_smt_mask                                               (0x00800000)
#define ISO_PFUNC0_iso_gpio_7_smt(data)                                              (0x00800000&((data)<<23))
#define ISO_PFUNC0_iso_gpio_7_smt_src(data)                                          ((0x00800000&(data))>>23)
#define ISO_PFUNC0_get_iso_gpio_7_smt(data)                                          ((0x00800000&(data))>>23)
#define ISO_PFUNC0_iso_gpio_7_e2_shift                                               (22)
#define ISO_PFUNC0_iso_gpio_7_e2_mask                                                (0x00400000)
#define ISO_PFUNC0_iso_gpio_7_e2(data)                                               (0x00400000&((data)<<22))
#define ISO_PFUNC0_iso_gpio_7_e2_src(data)                                           ((0x00400000&(data))>>22)
#define ISO_PFUNC0_get_iso_gpio_7_e2(data)                                           ((0x00400000&(data))>>22)
#define ISO_PFUNC0_iso_gpio_7_pud_en_shift                                           (21)
#define ISO_PFUNC0_iso_gpio_7_pud_en_mask                                            (0x00200000)
#define ISO_PFUNC0_iso_gpio_7_pud_en(data)                                           (0x00200000&((data)<<21))
#define ISO_PFUNC0_iso_gpio_7_pud_en_src(data)                                       ((0x00200000&(data))>>21)
#define ISO_PFUNC0_get_iso_gpio_7_pud_en(data)                                       ((0x00200000&(data))>>21)
#define ISO_PFUNC0_iso_gpio_7_pud_sel_shift                                          (20)
#define ISO_PFUNC0_iso_gpio_7_pud_sel_mask                                           (0x00100000)
#define ISO_PFUNC0_iso_gpio_7_pud_sel(data)                                          (0x00100000&((data)<<20))
#define ISO_PFUNC0_iso_gpio_7_pud_sel_src(data)                                      ((0x00100000&(data))>>20)
#define ISO_PFUNC0_get_iso_gpio_7_pud_sel(data)                                      ((0x00100000&(data))>>20)
#define ISO_PFUNC0_iso_gpio_5_smt_shift                                              (19)
#define ISO_PFUNC0_iso_gpio_5_smt_mask                                               (0x00080000)
#define ISO_PFUNC0_iso_gpio_5_smt(data)                                              (0x00080000&((data)<<19))
#define ISO_PFUNC0_iso_gpio_5_smt_src(data)                                          ((0x00080000&(data))>>19)
#define ISO_PFUNC0_get_iso_gpio_5_smt(data)                                          ((0x00080000&(data))>>19)
#define ISO_PFUNC0_iso_gpio_5_e2_shift                                               (18)
#define ISO_PFUNC0_iso_gpio_5_e2_mask                                                (0x00040000)
#define ISO_PFUNC0_iso_gpio_5_e2(data)                                               (0x00040000&((data)<<18))
#define ISO_PFUNC0_iso_gpio_5_e2_src(data)                                           ((0x00040000&(data))>>18)
#define ISO_PFUNC0_get_iso_gpio_5_e2(data)                                           ((0x00040000&(data))>>18)
#define ISO_PFUNC0_iso_gpio_5_pud_en_shift                                           (17)
#define ISO_PFUNC0_iso_gpio_5_pud_en_mask                                            (0x00020000)
#define ISO_PFUNC0_iso_gpio_5_pud_en(data)                                           (0x00020000&((data)<<17))
#define ISO_PFUNC0_iso_gpio_5_pud_en_src(data)                                       ((0x00020000&(data))>>17)
#define ISO_PFUNC0_get_iso_gpio_5_pud_en(data)                                       ((0x00020000&(data))>>17)
#define ISO_PFUNC0_iso_gpio_5_pud_sel_shift                                          (16)
#define ISO_PFUNC0_iso_gpio_5_pud_sel_mask                                           (0x00010000)
#define ISO_PFUNC0_iso_gpio_5_pud_sel(data)                                          (0x00010000&((data)<<16))
#define ISO_PFUNC0_iso_gpio_5_pud_sel_src(data)                                      ((0x00010000&(data))>>16)
#define ISO_PFUNC0_get_iso_gpio_5_pud_sel(data)                                      ((0x00010000&(data))>>16)
#define ISO_PFUNC0_iso_gpio_4_smt_shift                                              (15)
#define ISO_PFUNC0_iso_gpio_4_smt_mask                                               (0x00008000)
#define ISO_PFUNC0_iso_gpio_4_smt(data)                                              (0x00008000&((data)<<15))
#define ISO_PFUNC0_iso_gpio_4_smt_src(data)                                          ((0x00008000&(data))>>15)
#define ISO_PFUNC0_get_iso_gpio_4_smt(data)                                          ((0x00008000&(data))>>15)
#define ISO_PFUNC0_iso_gpio_4_e2_shift                                               (14)
#define ISO_PFUNC0_iso_gpio_4_e2_mask                                                (0x00004000)
#define ISO_PFUNC0_iso_gpio_4_e2(data)                                               (0x00004000&((data)<<14))
#define ISO_PFUNC0_iso_gpio_4_e2_src(data)                                           ((0x00004000&(data))>>14)
#define ISO_PFUNC0_get_iso_gpio_4_e2(data)                                           ((0x00004000&(data))>>14)
#define ISO_PFUNC0_iso_gpio_4_pud_en_shift                                           (13)
#define ISO_PFUNC0_iso_gpio_4_pud_en_mask                                            (0x00002000)
#define ISO_PFUNC0_iso_gpio_4_pud_en(data)                                           (0x00002000&((data)<<13))
#define ISO_PFUNC0_iso_gpio_4_pud_en_src(data)                                       ((0x00002000&(data))>>13)
#define ISO_PFUNC0_get_iso_gpio_4_pud_en(data)                                       ((0x00002000&(data))>>13)
#define ISO_PFUNC0_iso_gpio_4_pud_sel_shift                                          (12)
#define ISO_PFUNC0_iso_gpio_4_pud_sel_mask                                           (0x00001000)
#define ISO_PFUNC0_iso_gpio_4_pud_sel(data)                                          (0x00001000&((data)<<12))
#define ISO_PFUNC0_iso_gpio_4_pud_sel_src(data)                                      ((0x00001000&(data))>>12)
#define ISO_PFUNC0_get_iso_gpio_4_pud_sel(data)                                      ((0x00001000&(data))>>12)
#define ISO_PFUNC0_ir_rx_smt_shift                                                   (11)
#define ISO_PFUNC0_ir_rx_smt_mask                                                    (0x00000800)
#define ISO_PFUNC0_ir_rx_smt(data)                                                   (0x00000800&((data)<<11))
#define ISO_PFUNC0_ir_rx_smt_src(data)                                               ((0x00000800&(data))>>11)
#define ISO_PFUNC0_get_ir_rx_smt(data)                                               ((0x00000800&(data))>>11)
#define ISO_PFUNC0_ir_rx_e2_shift                                                    (10)
#define ISO_PFUNC0_ir_rx_e2_mask                                                     (0x00000400)
#define ISO_PFUNC0_ir_rx_e2(data)                                                    (0x00000400&((data)<<10))
#define ISO_PFUNC0_ir_rx_e2_src(data)                                                ((0x00000400&(data))>>10)
#define ISO_PFUNC0_get_ir_rx_e2(data)                                                ((0x00000400&(data))>>10)
#define ISO_PFUNC0_ir_rx_pud_en_shift                                                (9)
#define ISO_PFUNC0_ir_rx_pud_en_mask                                                 (0x00000200)
#define ISO_PFUNC0_ir_rx_pud_en(data)                                                (0x00000200&((data)<<9))
#define ISO_PFUNC0_ir_rx_pud_en_src(data)                                            ((0x00000200&(data))>>9)
#define ISO_PFUNC0_get_ir_rx_pud_en(data)                                            ((0x00000200&(data))>>9)
#define ISO_PFUNC0_ir_rx_pud_sel_shift                                               (8)
#define ISO_PFUNC0_ir_rx_pud_sel_mask                                                (0x00000100)
#define ISO_PFUNC0_ir_rx_pud_sel(data)                                               (0x00000100&((data)<<8))
#define ISO_PFUNC0_ir_rx_pud_sel_src(data)                                           ((0x00000100&(data))>>8)
#define ISO_PFUNC0_get_ir_rx_pud_sel(data)                                           ((0x00000100&(data))>>8)
#define ISO_PFUNC0_iso_gpio_3_smt_shift                                              (7)
#define ISO_PFUNC0_iso_gpio_3_smt_mask                                               (0x00000080)
#define ISO_PFUNC0_iso_gpio_3_smt(data)                                              (0x00000080&((data)<<7))
#define ISO_PFUNC0_iso_gpio_3_smt_src(data)                                          ((0x00000080&(data))>>7)
#define ISO_PFUNC0_get_iso_gpio_3_smt(data)                                          ((0x00000080&(data))>>7)
#define ISO_PFUNC0_iso_gpio_3_e2_shift                                               (6)
#define ISO_PFUNC0_iso_gpio_3_e2_mask                                                (0x00000040)
#define ISO_PFUNC0_iso_gpio_3_e2(data)                                               (0x00000040&((data)<<6))
#define ISO_PFUNC0_iso_gpio_3_e2_src(data)                                           ((0x00000040&(data))>>6)
#define ISO_PFUNC0_get_iso_gpio_3_e2(data)                                           ((0x00000040&(data))>>6)
#define ISO_PFUNC0_iso_gpio_3_pud_en_shift                                           (5)
#define ISO_PFUNC0_iso_gpio_3_pud_en_mask                                            (0x00000020)
#define ISO_PFUNC0_iso_gpio_3_pud_en(data)                                           (0x00000020&((data)<<5))
#define ISO_PFUNC0_iso_gpio_3_pud_en_src(data)                                       ((0x00000020&(data))>>5)
#define ISO_PFUNC0_get_iso_gpio_3_pud_en(data)                                       ((0x00000020&(data))>>5)
#define ISO_PFUNC0_iso_gpio_3_pud_sel_shift                                          (4)
#define ISO_PFUNC0_iso_gpio_3_pud_sel_mask                                           (0x00000010)
#define ISO_PFUNC0_iso_gpio_3_pud_sel(data)                                          (0x00000010&((data)<<4))
#define ISO_PFUNC0_iso_gpio_3_pud_sel_src(data)                                      ((0x00000010&(data))>>4)
#define ISO_PFUNC0_get_iso_gpio_3_pud_sel(data)                                      ((0x00000010&(data))>>4)
#define ISO_PFUNC0_iso_gpio_2_smt_shift                                              (3)
#define ISO_PFUNC0_iso_gpio_2_smt_mask                                               (0x00000008)
#define ISO_PFUNC0_iso_gpio_2_smt(data)                                              (0x00000008&((data)<<3))
#define ISO_PFUNC0_iso_gpio_2_smt_src(data)                                          ((0x00000008&(data))>>3)
#define ISO_PFUNC0_get_iso_gpio_2_smt(data)                                          ((0x00000008&(data))>>3)
#define ISO_PFUNC0_iso_gpio_2_e2_shift                                               (2)
#define ISO_PFUNC0_iso_gpio_2_e2_mask                                                (0x00000004)
#define ISO_PFUNC0_iso_gpio_2_e2(data)                                               (0x00000004&((data)<<2))
#define ISO_PFUNC0_iso_gpio_2_e2_src(data)                                           ((0x00000004&(data))>>2)
#define ISO_PFUNC0_get_iso_gpio_2_e2(data)                                           ((0x00000004&(data))>>2)
#define ISO_PFUNC0_iso_gpio_2_pud_en_shift                                           (1)
#define ISO_PFUNC0_iso_gpio_2_pud_en_mask                                            (0x00000002)
#define ISO_PFUNC0_iso_gpio_2_pud_en(data)                                           (0x00000002&((data)<<1))
#define ISO_PFUNC0_iso_gpio_2_pud_en_src(data)                                       ((0x00000002&(data))>>1)
#define ISO_PFUNC0_get_iso_gpio_2_pud_en(data)                                       ((0x00000002&(data))>>1)
#define ISO_PFUNC0_iso_gpio_2_pud_sel_shift                                          (0)
#define ISO_PFUNC0_iso_gpio_2_pud_sel_mask                                           (0x00000001)
#define ISO_PFUNC0_iso_gpio_2_pud_sel(data)                                          (0x00000001&((data)<<0))
#define ISO_PFUNC0_iso_gpio_2_pud_sel_src(data)                                      ((0x00000001&(data))>>0)
#define ISO_PFUNC0_get_iso_gpio_2_pud_sel(data)                                      ((0x00000001&(data))>>0)


#define ISO_PFUNC1                                                                   0x98007304
#define ISO_PFUNC1_reg_addr                                                          "0x98007304"
#define ISO_PFUNC1_reg                                                               0x98007304
#define set_ISO_PFUNC1_reg(data)   (*((volatile unsigned int*) ISO_PFUNC1_reg)=data)
#define get_ISO_PFUNC1_reg   (*((volatile unsigned int*) ISO_PFUNC1_reg))
#define ISO_PFUNC1_inst_adr                                                          "0x00C1"
#define ISO_PFUNC1_inst                                                              0x00C1
#define ISO_PFUNC1_etn_led_rxtx_smt_shift                                            (31)
#define ISO_PFUNC1_etn_led_rxtx_smt_mask                                             (0x80000000)
#define ISO_PFUNC1_etn_led_rxtx_smt(data)                                            (0x80000000&((data)<<31))
#define ISO_PFUNC1_etn_led_rxtx_smt_src(data)                                        ((0x80000000&(data))>>31)
#define ISO_PFUNC1_get_etn_led_rxtx_smt(data)                                        ((0x80000000&(data))>>31)
#define ISO_PFUNC1_etn_led_rxtx_e2_shift                                             (30)
#define ISO_PFUNC1_etn_led_rxtx_e2_mask                                              (0x40000000)
#define ISO_PFUNC1_etn_led_rxtx_e2(data)                                             (0x40000000&((data)<<30))
#define ISO_PFUNC1_etn_led_rxtx_e2_src(data)                                         ((0x40000000&(data))>>30)
#define ISO_PFUNC1_get_etn_led_rxtx_e2(data)                                         ((0x40000000&(data))>>30)
#define ISO_PFUNC1_etn_led_rxtx_pud_en_shift                                         (29)
#define ISO_PFUNC1_etn_led_rxtx_pud_en_mask                                          (0x20000000)
#define ISO_PFUNC1_etn_led_rxtx_pud_en(data)                                         (0x20000000&((data)<<29))
#define ISO_PFUNC1_etn_led_rxtx_pud_en_src(data)                                     ((0x20000000&(data))>>29)
#define ISO_PFUNC1_get_etn_led_rxtx_pud_en(data)                                     ((0x20000000&(data))>>29)
#define ISO_PFUNC1_etn_led_rxtx_pud_sel_shift                                        (28)
#define ISO_PFUNC1_etn_led_rxtx_pud_sel_mask                                         (0x10000000)
#define ISO_PFUNC1_etn_led_rxtx_pud_sel(data)                                        (0x10000000&((data)<<28))
#define ISO_PFUNC1_etn_led_rxtx_pud_sel_src(data)                                    ((0x10000000&(data))>>28)
#define ISO_PFUNC1_get_etn_led_rxtx_pud_sel(data)                                    ((0x10000000&(data))>>28)
#define ISO_PFUNC1_etn_led_link_smt_shift                                            (27)
#define ISO_PFUNC1_etn_led_link_smt_mask                                             (0x08000000)
#define ISO_PFUNC1_etn_led_link_smt(data)                                            (0x08000000&((data)<<27))
#define ISO_PFUNC1_etn_led_link_smt_src(data)                                        ((0x08000000&(data))>>27)
#define ISO_PFUNC1_get_etn_led_link_smt(data)                                        ((0x08000000&(data))>>27)
#define ISO_PFUNC1_etn_led_link_e2_shift                                             (26)
#define ISO_PFUNC1_etn_led_link_e2_mask                                              (0x04000000)
#define ISO_PFUNC1_etn_led_link_e2(data)                                             (0x04000000&((data)<<26))
#define ISO_PFUNC1_etn_led_link_e2_src(data)                                         ((0x04000000&(data))>>26)
#define ISO_PFUNC1_get_etn_led_link_e2(data)                                         ((0x04000000&(data))>>26)
#define ISO_PFUNC1_etn_led_link_pud_en_shift                                         (25)
#define ISO_PFUNC1_etn_led_link_pud_en_mask                                          (0x02000000)
#define ISO_PFUNC1_etn_led_link_pud_en(data)                                         (0x02000000&((data)<<25))
#define ISO_PFUNC1_etn_led_link_pud_en_src(data)                                     ((0x02000000&(data))>>25)
#define ISO_PFUNC1_get_etn_led_link_pud_en(data)                                     ((0x02000000&(data))>>25)
#define ISO_PFUNC1_etn_led_link_pud_sel_shift                                        (24)
#define ISO_PFUNC1_etn_led_link_pud_sel_mask                                         (0x01000000)
#define ISO_PFUNC1_etn_led_link_pud_sel(data)                                        (0x01000000&((data)<<24))
#define ISO_PFUNC1_etn_led_link_pud_sel_src(data)                                    ((0x01000000&(data))>>24)
#define ISO_PFUNC1_get_etn_led_link_pud_sel(data)                                    ((0x01000000&(data))>>24)
#define ISO_PFUNC1_ur0_tx_smt_shift                                                  (23)
#define ISO_PFUNC1_ur0_tx_smt_mask                                                   (0x00800000)
#define ISO_PFUNC1_ur0_tx_smt(data)                                                  (0x00800000&((data)<<23))
#define ISO_PFUNC1_ur0_tx_smt_src(data)                                              ((0x00800000&(data))>>23)
#define ISO_PFUNC1_get_ur0_tx_smt(data)                                              ((0x00800000&(data))>>23)
#define ISO_PFUNC1_ur0_tx_e2_shift                                                   (22)
#define ISO_PFUNC1_ur0_tx_e2_mask                                                    (0x00400000)
#define ISO_PFUNC1_ur0_tx_e2(data)                                                   (0x00400000&((data)<<22))
#define ISO_PFUNC1_ur0_tx_e2_src(data)                                               ((0x00400000&(data))>>22)
#define ISO_PFUNC1_get_ur0_tx_e2(data)                                               ((0x00400000&(data))>>22)
#define ISO_PFUNC1_ur0_tx_pud_en_shift                                               (21)
#define ISO_PFUNC1_ur0_tx_pud_en_mask                                                (0x00200000)
#define ISO_PFUNC1_ur0_tx_pud_en(data)                                               (0x00200000&((data)<<21))
#define ISO_PFUNC1_ur0_tx_pud_en_src(data)                                           ((0x00200000&(data))>>21)
#define ISO_PFUNC1_get_ur0_tx_pud_en(data)                                           ((0x00200000&(data))>>21)
#define ISO_PFUNC1_ur0_tx_pud_sel_shift                                              (20)
#define ISO_PFUNC1_ur0_tx_pud_sel_mask                                               (0x00100000)
#define ISO_PFUNC1_ur0_tx_pud_sel(data)                                              (0x00100000&((data)<<20))
#define ISO_PFUNC1_ur0_tx_pud_sel_src(data)                                          ((0x00100000&(data))>>20)
#define ISO_PFUNC1_get_ur0_tx_pud_sel(data)                                          ((0x00100000&(data))>>20)
#define ISO_PFUNC1_ur0_rx_smt_shift                                                  (19)
#define ISO_PFUNC1_ur0_rx_smt_mask                                                   (0x00080000)
#define ISO_PFUNC1_ur0_rx_smt(data)                                                  (0x00080000&((data)<<19))
#define ISO_PFUNC1_ur0_rx_smt_src(data)                                              ((0x00080000&(data))>>19)
#define ISO_PFUNC1_get_ur0_rx_smt(data)                                              ((0x00080000&(data))>>19)
#define ISO_PFUNC1_ur0_rx_e2_shift                                                   (18)
#define ISO_PFUNC1_ur0_rx_e2_mask                                                    (0x00040000)
#define ISO_PFUNC1_ur0_rx_e2(data)                                                   (0x00040000&((data)<<18))
#define ISO_PFUNC1_ur0_rx_e2_src(data)                                               ((0x00040000&(data))>>18)
#define ISO_PFUNC1_get_ur0_rx_e2(data)                                               ((0x00040000&(data))>>18)
#define ISO_PFUNC1_ur0_rx_pud_en_shift                                               (17)
#define ISO_PFUNC1_ur0_rx_pud_en_mask                                                (0x00020000)
#define ISO_PFUNC1_ur0_rx_pud_en(data)                                               (0x00020000&((data)<<17))
#define ISO_PFUNC1_ur0_rx_pud_en_src(data)                                           ((0x00020000&(data))>>17)
#define ISO_PFUNC1_get_ur0_rx_pud_en(data)                                           ((0x00020000&(data))>>17)
#define ISO_PFUNC1_ur0_rx_pud_sel_shift                                              (16)
#define ISO_PFUNC1_ur0_rx_pud_sel_mask                                               (0x00010000)
#define ISO_PFUNC1_ur0_rx_pud_sel(data)                                              (0x00010000&((data)<<16))
#define ISO_PFUNC1_ur0_rx_pud_sel_src(data)                                          ((0x00010000&(data))>>16)
#define ISO_PFUNC1_get_ur0_rx_pud_sel(data)                                          ((0x00010000&(data))>>16)
#define ISO_PFUNC1_ur1_cts_n_smt_shift                                               (15)
#define ISO_PFUNC1_ur1_cts_n_smt_mask                                                (0x00008000)
#define ISO_PFUNC1_ur1_cts_n_smt(data)                                               (0x00008000&((data)<<15))
#define ISO_PFUNC1_ur1_cts_n_smt_src(data)                                           ((0x00008000&(data))>>15)
#define ISO_PFUNC1_get_ur1_cts_n_smt(data)                                           ((0x00008000&(data))>>15)
#define ISO_PFUNC1_ur1_cts_n_e2_shift                                                (14)
#define ISO_PFUNC1_ur1_cts_n_e2_mask                                                 (0x00004000)
#define ISO_PFUNC1_ur1_cts_n_e2(data)                                                (0x00004000&((data)<<14))
#define ISO_PFUNC1_ur1_cts_n_e2_src(data)                                            ((0x00004000&(data))>>14)
#define ISO_PFUNC1_get_ur1_cts_n_e2(data)                                            ((0x00004000&(data))>>14)
#define ISO_PFUNC1_ur1_cts_n_pud_en_shift                                            (13)
#define ISO_PFUNC1_ur1_cts_n_pud_en_mask                                             (0x00002000)
#define ISO_PFUNC1_ur1_cts_n_pud_en(data)                                            (0x00002000&((data)<<13))
#define ISO_PFUNC1_ur1_cts_n_pud_en_src(data)                                        ((0x00002000&(data))>>13)
#define ISO_PFUNC1_get_ur1_cts_n_pud_en(data)                                        ((0x00002000&(data))>>13)
#define ISO_PFUNC1_ur1_cts_n_pud_sel_shift                                           (12)
#define ISO_PFUNC1_ur1_cts_n_pud_sel_mask                                            (0x00001000)
#define ISO_PFUNC1_ur1_cts_n_pud_sel(data)                                           (0x00001000&((data)<<12))
#define ISO_PFUNC1_ur1_cts_n_pud_sel_src(data)                                       ((0x00001000&(data))>>12)
#define ISO_PFUNC1_get_ur1_cts_n_pud_sel(data)                                       ((0x00001000&(data))>>12)
#define ISO_PFUNC1_ur1_rts_n_smt_shift                                               (11)
#define ISO_PFUNC1_ur1_rts_n_smt_mask                                                (0x00000800)
#define ISO_PFUNC1_ur1_rts_n_smt(data)                                               (0x00000800&((data)<<11))
#define ISO_PFUNC1_ur1_rts_n_smt_src(data)                                           ((0x00000800&(data))>>11)
#define ISO_PFUNC1_get_ur1_rts_n_smt(data)                                           ((0x00000800&(data))>>11)
#define ISO_PFUNC1_ur1_rts_n_e2_shift                                                (10)
#define ISO_PFUNC1_ur1_rts_n_e2_mask                                                 (0x00000400)
#define ISO_PFUNC1_ur1_rts_n_e2(data)                                                (0x00000400&((data)<<10))
#define ISO_PFUNC1_ur1_rts_n_e2_src(data)                                            ((0x00000400&(data))>>10)
#define ISO_PFUNC1_get_ur1_rts_n_e2(data)                                            ((0x00000400&(data))>>10)
#define ISO_PFUNC1_ur1_rts_n_pud_en_shift                                            (9)
#define ISO_PFUNC1_ur1_rts_n_pud_en_mask                                             (0x00000200)
#define ISO_PFUNC1_ur1_rts_n_pud_en(data)                                            (0x00000200&((data)<<9))
#define ISO_PFUNC1_ur1_rts_n_pud_en_src(data)                                        ((0x00000200&(data))>>9)
#define ISO_PFUNC1_get_ur1_rts_n_pud_en(data)                                        ((0x00000200&(data))>>9)
#define ISO_PFUNC1_ur1_rts_n_pud_sel_shift                                           (8)
#define ISO_PFUNC1_ur1_rts_n_pud_sel_mask                                            (0x00000100)
#define ISO_PFUNC1_ur1_rts_n_pud_sel(data)                                           (0x00000100&((data)<<8))
#define ISO_PFUNC1_ur1_rts_n_pud_sel_src(data)                                       ((0x00000100&(data))>>8)
#define ISO_PFUNC1_get_ur1_rts_n_pud_sel(data)                                       ((0x00000100&(data))>>8)
#define ISO_PFUNC1_ur1_tx_smt_shift                                                  (7)
#define ISO_PFUNC1_ur1_tx_smt_mask                                                   (0x00000080)
#define ISO_PFUNC1_ur1_tx_smt(data)                                                  (0x00000080&((data)<<7))
#define ISO_PFUNC1_ur1_tx_smt_src(data)                                              ((0x00000080&(data))>>7)
#define ISO_PFUNC1_get_ur1_tx_smt(data)                                              ((0x00000080&(data))>>7)
#define ISO_PFUNC1_ur1_tx_e2_shift                                                   (6)
#define ISO_PFUNC1_ur1_tx_e2_mask                                                    (0x00000040)
#define ISO_PFUNC1_ur1_tx_e2(data)                                                   (0x00000040&((data)<<6))
#define ISO_PFUNC1_ur1_tx_e2_src(data)                                               ((0x00000040&(data))>>6)
#define ISO_PFUNC1_get_ur1_tx_e2(data)                                               ((0x00000040&(data))>>6)
#define ISO_PFUNC1_ur1_tx_pud_en_shift                                               (5)
#define ISO_PFUNC1_ur1_tx_pud_en_mask                                                (0x00000020)
#define ISO_PFUNC1_ur1_tx_pud_en(data)                                               (0x00000020&((data)<<5))
#define ISO_PFUNC1_ur1_tx_pud_en_src(data)                                           ((0x00000020&(data))>>5)
#define ISO_PFUNC1_get_ur1_tx_pud_en(data)                                           ((0x00000020&(data))>>5)
#define ISO_PFUNC1_ur1_tx_pud_sel_shift                                              (4)
#define ISO_PFUNC1_ur1_tx_pud_sel_mask                                               (0x00000010)
#define ISO_PFUNC1_ur1_tx_pud_sel(data)                                              (0x00000010&((data)<<4))
#define ISO_PFUNC1_ur1_tx_pud_sel_src(data)                                          ((0x00000010&(data))>>4)
#define ISO_PFUNC1_get_ur1_tx_pud_sel(data)                                          ((0x00000010&(data))>>4)
#define ISO_PFUNC1_ur1_rx_smt_shift                                                  (3)
#define ISO_PFUNC1_ur1_rx_smt_mask                                                   (0x00000008)
#define ISO_PFUNC1_ur1_rx_smt(data)                                                  (0x00000008&((data)<<3))
#define ISO_PFUNC1_ur1_rx_smt_src(data)                                              ((0x00000008&(data))>>3)
#define ISO_PFUNC1_get_ur1_rx_smt(data)                                              ((0x00000008&(data))>>3)
#define ISO_PFUNC1_ur1_rx_e2_shift                                                   (2)
#define ISO_PFUNC1_ur1_rx_e2_mask                                                    (0x00000004)
#define ISO_PFUNC1_ur1_rx_e2(data)                                                   (0x00000004&((data)<<2))
#define ISO_PFUNC1_ur1_rx_e2_src(data)                                               ((0x00000004&(data))>>2)
#define ISO_PFUNC1_get_ur1_rx_e2(data)                                               ((0x00000004&(data))>>2)
#define ISO_PFUNC1_ur1_rx_pud_en_shift                                               (1)
#define ISO_PFUNC1_ur1_rx_pud_en_mask                                                (0x00000002)
#define ISO_PFUNC1_ur1_rx_pud_en(data)                                               (0x00000002&((data)<<1))
#define ISO_PFUNC1_ur1_rx_pud_en_src(data)                                           ((0x00000002&(data))>>1)
#define ISO_PFUNC1_get_ur1_rx_pud_en(data)                                           ((0x00000002&(data))>>1)
#define ISO_PFUNC1_ur1_rx_pud_sel_shift                                              (0)
#define ISO_PFUNC1_ur1_rx_pud_sel_mask                                               (0x00000001)
#define ISO_PFUNC1_ur1_rx_pud_sel(data)                                              (0x00000001&((data)<<0))
#define ISO_PFUNC1_ur1_rx_pud_sel_src(data)                                          ((0x00000001&(data))>>0)
#define ISO_PFUNC1_get_ur1_rx_pud_sel(data)                                          ((0x00000001&(data))>>0)


#define ISO_PFUNC2                                                                   0x98007308
#define ISO_PFUNC2_reg_addr                                                          "0x98007308"
#define ISO_PFUNC2_reg                                                               0x98007308
#define set_ISO_PFUNC2_reg(data)   (*((volatile unsigned int*) ISO_PFUNC2_reg)=data)
#define get_ISO_PFUNC2_reg   (*((volatile unsigned int*) ISO_PFUNC2_reg))
#define ISO_PFUNC2_inst_adr                                                          "0x00C2"
#define ISO_PFUNC2_inst                                                              0x00C2
#define ISO_PFUNC2_i2c_scl_1_smt_shift                                               (31)
#define ISO_PFUNC2_i2c_scl_1_smt_mask                                                (0x80000000)
#define ISO_PFUNC2_i2c_scl_1_smt(data)                                               (0x80000000&((data)<<31))
#define ISO_PFUNC2_i2c_scl_1_smt_src(data)                                           ((0x80000000&(data))>>31)
#define ISO_PFUNC2_get_i2c_scl_1_smt(data)                                           ((0x80000000&(data))>>31)
#define ISO_PFUNC2_i2c_scl_1_e2_shift                                                (30)
#define ISO_PFUNC2_i2c_scl_1_e2_mask                                                 (0x40000000)
#define ISO_PFUNC2_i2c_scl_1_e2(data)                                                (0x40000000&((data)<<30))
#define ISO_PFUNC2_i2c_scl_1_e2_src(data)                                            ((0x40000000&(data))>>30)
#define ISO_PFUNC2_get_i2c_scl_1_e2(data)                                            ((0x40000000&(data))>>30)
#define ISO_PFUNC2_i2c_scl_1_pud_en_shift                                            (29)
#define ISO_PFUNC2_i2c_scl_1_pud_en_mask                                             (0x20000000)
#define ISO_PFUNC2_i2c_scl_1_pud_en(data)                                            (0x20000000&((data)<<29))
#define ISO_PFUNC2_i2c_scl_1_pud_en_src(data)                                        ((0x20000000&(data))>>29)
#define ISO_PFUNC2_get_i2c_scl_1_pud_en(data)                                        ((0x20000000&(data))>>29)
#define ISO_PFUNC2_i2c_scl_1_pud_sel_shift                                           (28)
#define ISO_PFUNC2_i2c_scl_1_pud_sel_mask                                            (0x10000000)
#define ISO_PFUNC2_i2c_scl_1_pud_sel(data)                                           (0x10000000&((data)<<28))
#define ISO_PFUNC2_i2c_scl_1_pud_sel_src(data)                                       ((0x10000000&(data))>>28)
#define ISO_PFUNC2_get_i2c_scl_1_pud_sel(data)                                       ((0x10000000&(data))>>28)
#define ISO_PFUNC2_i2c_sda_1_smt_shift                                               (27)
#define ISO_PFUNC2_i2c_sda_1_smt_mask                                                (0x08000000)
#define ISO_PFUNC2_i2c_sda_1_smt(data)                                               (0x08000000&((data)<<27))
#define ISO_PFUNC2_i2c_sda_1_smt_src(data)                                           ((0x08000000&(data))>>27)
#define ISO_PFUNC2_get_i2c_sda_1_smt(data)                                           ((0x08000000&(data))>>27)
#define ISO_PFUNC2_i2c_sda_1_e2_shift                                                (26)
#define ISO_PFUNC2_i2c_sda_1_e2_mask                                                 (0x04000000)
#define ISO_PFUNC2_i2c_sda_1_e2(data)                                                (0x04000000&((data)<<26))
#define ISO_PFUNC2_i2c_sda_1_e2_src(data)                                            ((0x04000000&(data))>>26)
#define ISO_PFUNC2_get_i2c_sda_1_e2(data)                                            ((0x04000000&(data))>>26)
#define ISO_PFUNC2_i2c_sda_1_pud_en_shift                                            (25)
#define ISO_PFUNC2_i2c_sda_1_pud_en_mask                                             (0x02000000)
#define ISO_PFUNC2_i2c_sda_1_pud_en(data)                                            (0x02000000&((data)<<25))
#define ISO_PFUNC2_i2c_sda_1_pud_en_src(data)                                        ((0x02000000&(data))>>25)
#define ISO_PFUNC2_get_i2c_sda_1_pud_en(data)                                        ((0x02000000&(data))>>25)
#define ISO_PFUNC2_i2c_sda_1_pud_sel_shift                                           (24)
#define ISO_PFUNC2_i2c_sda_1_pud_sel_mask                                            (0x01000000)
#define ISO_PFUNC2_i2c_sda_1_pud_sel(data)                                           (0x01000000&((data)<<24))
#define ISO_PFUNC2_i2c_sda_1_pud_sel_src(data)                                       ((0x01000000&(data))>>24)
#define ISO_PFUNC2_get_i2c_sda_1_pud_sel(data)                                       ((0x01000000&(data))>>24)
#define ISO_PFUNC2_ir_tx_smt_shift                                                   (23)
#define ISO_PFUNC2_ir_tx_smt_mask                                                    (0x00800000)
#define ISO_PFUNC2_ir_tx_smt(data)                                                   (0x00800000&((data)<<23))
#define ISO_PFUNC2_ir_tx_smt_src(data)                                               ((0x00800000&(data))>>23)
#define ISO_PFUNC2_get_ir_tx_smt(data)                                               ((0x00800000&(data))>>23)
#define ISO_PFUNC2_ir_tx_e2_shift                                                    (22)
#define ISO_PFUNC2_ir_tx_e2_mask                                                     (0x00400000)
#define ISO_PFUNC2_ir_tx_e2(data)                                                    (0x00400000&((data)<<22))
#define ISO_PFUNC2_ir_tx_e2_src(data)                                                ((0x00400000&(data))>>22)
#define ISO_PFUNC2_get_ir_tx_e2(data)                                                ((0x00400000&(data))>>22)
#define ISO_PFUNC2_ir_tx_pud_en_shift                                                (21)
#define ISO_PFUNC2_ir_tx_pud_en_mask                                                 (0x00200000)
#define ISO_PFUNC2_ir_tx_pud_en(data)                                                (0x00200000&((data)<<21))
#define ISO_PFUNC2_ir_tx_pud_en_src(data)                                            ((0x00200000&(data))>>21)
#define ISO_PFUNC2_get_ir_tx_pud_en(data)                                            ((0x00200000&(data))>>21)
#define ISO_PFUNC2_ir_tx_pud_sel_shift                                               (20)
#define ISO_PFUNC2_ir_tx_pud_sel_mask                                                (0x00100000)
#define ISO_PFUNC2_ir_tx_pud_sel(data)                                               (0x00100000&((data)<<20))
#define ISO_PFUNC2_ir_tx_pud_sel_src(data)                                           ((0x00100000&(data))>>20)
#define ISO_PFUNC2_get_ir_tx_pud_sel(data)                                           ((0x00100000&(data))>>20)
#define ISO_PFUNC2_i2c_scl_6_smt_shift                                               (19)
#define ISO_PFUNC2_i2c_scl_6_smt_mask                                                (0x00080000)
#define ISO_PFUNC2_i2c_scl_6_smt(data)                                               (0x00080000&((data)<<19))
#define ISO_PFUNC2_i2c_scl_6_smt_src(data)                                           ((0x00080000&(data))>>19)
#define ISO_PFUNC2_get_i2c_scl_6_smt(data)                                           ((0x00080000&(data))>>19)
#define ISO_PFUNC2_i2c_scl_6_e2_shift                                                (18)
#define ISO_PFUNC2_i2c_scl_6_e2_mask                                                 (0x00040000)
#define ISO_PFUNC2_i2c_scl_6_e2(data)                                                (0x00040000&((data)<<18))
#define ISO_PFUNC2_i2c_scl_6_e2_src(data)                                            ((0x00040000&(data))>>18)
#define ISO_PFUNC2_get_i2c_scl_6_e2(data)                                            ((0x00040000&(data))>>18)
#define ISO_PFUNC2_i2c_scl_6_pud_en_shift                                            (17)
#define ISO_PFUNC2_i2c_scl_6_pud_en_mask                                             (0x00020000)
#define ISO_PFUNC2_i2c_scl_6_pud_en(data)                                            (0x00020000&((data)<<17))
#define ISO_PFUNC2_i2c_scl_6_pud_en_src(data)                                        ((0x00020000&(data))>>17)
#define ISO_PFUNC2_get_i2c_scl_6_pud_en(data)                                        ((0x00020000&(data))>>17)
#define ISO_PFUNC2_i2c_scl_6_pud_sel_shift                                           (16)
#define ISO_PFUNC2_i2c_scl_6_pud_sel_mask                                            (0x00010000)
#define ISO_PFUNC2_i2c_scl_6_pud_sel(data)                                           (0x00010000&((data)<<16))
#define ISO_PFUNC2_i2c_scl_6_pud_sel_src(data)                                       ((0x00010000&(data))>>16)
#define ISO_PFUNC2_get_i2c_scl_6_pud_sel(data)                                       ((0x00010000&(data))>>16)
#define ISO_PFUNC2_i2c_sda_6_smt_shift                                               (15)
#define ISO_PFUNC2_i2c_sda_6_smt_mask                                                (0x00008000)
#define ISO_PFUNC2_i2c_sda_6_smt(data)                                               (0x00008000&((data)<<15))
#define ISO_PFUNC2_i2c_sda_6_smt_src(data)                                           ((0x00008000&(data))>>15)
#define ISO_PFUNC2_get_i2c_sda_6_smt(data)                                           ((0x00008000&(data))>>15)
#define ISO_PFUNC2_i2c_sda_6_e2_shift                                                (14)
#define ISO_PFUNC2_i2c_sda_6_e2_mask                                                 (0x00004000)
#define ISO_PFUNC2_i2c_sda_6_e2(data)                                                (0x00004000&((data)<<14))
#define ISO_PFUNC2_i2c_sda_6_e2_src(data)                                            ((0x00004000&(data))>>14)
#define ISO_PFUNC2_get_i2c_sda_6_e2(data)                                            ((0x00004000&(data))>>14)
#define ISO_PFUNC2_i2c_sda_6_pud_en_shift                                            (13)
#define ISO_PFUNC2_i2c_sda_6_pud_en_mask                                             (0x00002000)
#define ISO_PFUNC2_i2c_sda_6_pud_en(data)                                            (0x00002000&((data)<<13))
#define ISO_PFUNC2_i2c_sda_6_pud_en_src(data)                                        ((0x00002000&(data))>>13)
#define ISO_PFUNC2_get_i2c_sda_6_pud_en(data)                                        ((0x00002000&(data))>>13)
#define ISO_PFUNC2_i2c_sda_6_pud_sel_shift                                           (12)
#define ISO_PFUNC2_i2c_sda_6_pud_sel_mask                                            (0x00001000)
#define ISO_PFUNC2_i2c_sda_6_pud_sel(data)                                           (0x00001000&((data)<<12))
#define ISO_PFUNC2_i2c_sda_6_pud_sel_src(data)                                       ((0x00001000&(data))>>12)
#define ISO_PFUNC2_get_i2c_sda_6_pud_sel(data)                                       ((0x00001000&(data))>>12)
#define ISO_PFUNC2_boot_sel_pud_en_shift                                             (11)
#define ISO_PFUNC2_boot_sel_pud_en_mask                                              (0x00000800)
#define ISO_PFUNC2_boot_sel_pud_en(data)                                             (0x00000800&((data)<<11))
#define ISO_PFUNC2_boot_sel_pud_en_src(data)                                         ((0x00000800&(data))>>11)
#define ISO_PFUNC2_get_boot_sel_pud_en(data)                                         ((0x00000800&(data))>>11)
#define ISO_PFUNC2_boot_sel_pud_sel_shift                                            (10)
#define ISO_PFUNC2_boot_sel_pud_sel_mask                                             (0x00000400)
#define ISO_PFUNC2_boot_sel_pud_sel(data)                                            (0x00000400&((data)<<10))
#define ISO_PFUNC2_boot_sel_pud_sel_src(data)                                        ((0x00000400&(data))>>10)
#define ISO_PFUNC2_get_boot_sel_pud_sel(data)                                        ((0x00000400&(data))>>10)
#define ISO_PFUNC2_testmode_pud_en_shift                                             (9)
#define ISO_PFUNC2_testmode_pud_en_mask                                              (0x00000200)
#define ISO_PFUNC2_testmode_pud_en(data)                                             (0x00000200&((data)<<9))
#define ISO_PFUNC2_testmode_pud_en_src(data)                                         ((0x00000200&(data))>>9)
#define ISO_PFUNC2_get_testmode_pud_en(data)                                         ((0x00000200&(data))>>9)
#define ISO_PFUNC2_testmode_pud_sel_shift                                            (8)
#define ISO_PFUNC2_testmode_pud_sel_mask                                             (0x00000100)
#define ISO_PFUNC2_testmode_pud_sel(data)                                            (0x00000100&((data)<<8))
#define ISO_PFUNC2_testmode_pud_sel_src(data)                                        ((0x00000100&(data))>>8)
#define ISO_PFUNC2_get_testmode_pud_sel(data)                                        ((0x00000100&(data))>>8)
#define ISO_PFUNC2_standby1_smt_shift                                                (7)
#define ISO_PFUNC2_standby1_smt_mask                                                 (0x00000080)
#define ISO_PFUNC2_standby1_smt(data)                                                (0x00000080&((data)<<7))
#define ISO_PFUNC2_standby1_smt_src(data)                                            ((0x00000080&(data))>>7)
#define ISO_PFUNC2_get_standby1_smt(data)                                            ((0x00000080&(data))>>7)
#define ISO_PFUNC2_standby1_e2_shift                                                 (6)
#define ISO_PFUNC2_standby1_e2_mask                                                  (0x00000040)
#define ISO_PFUNC2_standby1_e2(data)                                                 (0x00000040&((data)<<6))
#define ISO_PFUNC2_standby1_e2_src(data)                                             ((0x00000040&(data))>>6)
#define ISO_PFUNC2_get_standby1_e2(data)                                             ((0x00000040&(data))>>6)
#define ISO_PFUNC2_standby1_pud_en_shift                                             (5)
#define ISO_PFUNC2_standby1_pud_en_mask                                              (0x00000020)
#define ISO_PFUNC2_standby1_pud_en(data)                                             (0x00000020&((data)<<5))
#define ISO_PFUNC2_standby1_pud_en_src(data)                                         ((0x00000020&(data))>>5)
#define ISO_PFUNC2_get_standby1_pud_en(data)                                         ((0x00000020&(data))>>5)
#define ISO_PFUNC2_standby1_pud_sel_shift                                            (4)
#define ISO_PFUNC2_standby1_pud_sel_mask                                             (0x00000010)
#define ISO_PFUNC2_standby1_pud_sel(data)                                            (0x00000010&((data)<<4))
#define ISO_PFUNC2_standby1_pud_sel_src(data)                                        ((0x00000010&(data))>>4)
#define ISO_PFUNC2_get_standby1_pud_sel(data)                                        ((0x00000010&(data))>>4)
#define ISO_PFUNC2_standby_smt_shift                                                 (3)
#define ISO_PFUNC2_standby_smt_mask                                                  (0x00000008)
#define ISO_PFUNC2_standby_smt(data)                                                 (0x00000008&((data)<<3))
#define ISO_PFUNC2_standby_smt_src(data)                                             ((0x00000008&(data))>>3)
#define ISO_PFUNC2_get_standby_smt(data)                                             ((0x00000008&(data))>>3)
#define ISO_PFUNC2_standby_e2_shift                                                  (2)
#define ISO_PFUNC2_standby_e2_mask                                                   (0x00000004)
#define ISO_PFUNC2_standby_e2(data)                                                  (0x00000004&((data)<<2))
#define ISO_PFUNC2_standby_e2_src(data)                                              ((0x00000004&(data))>>2)
#define ISO_PFUNC2_get_standby_e2(data)                                              ((0x00000004&(data))>>2)
#define ISO_PFUNC2_standby_pud_en_shift                                              (1)
#define ISO_PFUNC2_standby_pud_en_mask                                               (0x00000002)
#define ISO_PFUNC2_standby_pud_en(data)                                              (0x00000002&((data)<<1))
#define ISO_PFUNC2_standby_pud_en_src(data)                                          ((0x00000002&(data))>>1)
#define ISO_PFUNC2_get_standby_pud_en(data)                                          ((0x00000002&(data))>>1)
#define ISO_PFUNC2_standby_pud_sel_shift                                             (0)
#define ISO_PFUNC2_standby_pud_sel_mask                                              (0x00000001)
#define ISO_PFUNC2_standby_pud_sel(data)                                             (0x00000001&((data)<<0))
#define ISO_PFUNC2_standby_pud_sel_src(data)                                         ((0x00000001&(data))>>0)
#define ISO_PFUNC2_get_standby_pud_sel(data)                                         ((0x00000001&(data))>>0)


#define ISO_PFUNC3                                                                   0x9800730C
#define ISO_PFUNC3_reg_addr                                                          "0x9800730C"
#define ISO_PFUNC3_reg                                                               0x9800730C
#define set_ISO_PFUNC3_reg(data)   (*((volatile unsigned int*) ISO_PFUNC3_reg)=data)
#define get_ISO_PFUNC3_reg   (*((volatile unsigned int*) ISO_PFUNC3_reg))
#define ISO_PFUNC3_inst_adr                                                          "0x00C3"
#define ISO_PFUNC3_inst                                                              0x00C3
#define ISO_PFUNC3_nat_led_3_smt_shift                                               (31)
#define ISO_PFUNC3_nat_led_3_smt_mask                                                (0x80000000)
#define ISO_PFUNC3_nat_led_3_smt(data)                                               (0x80000000&((data)<<31))
#define ISO_PFUNC3_nat_led_3_smt_src(data)                                           ((0x80000000&(data))>>31)
#define ISO_PFUNC3_get_nat_led_3_smt(data)                                           ((0x80000000&(data))>>31)
#define ISO_PFUNC3_nat_led_3_e2_shift                                                (30)
#define ISO_PFUNC3_nat_led_3_e2_mask                                                 (0x40000000)
#define ISO_PFUNC3_nat_led_3_e2(data)                                                (0x40000000&((data)<<30))
#define ISO_PFUNC3_nat_led_3_e2_src(data)                                            ((0x40000000&(data))>>30)
#define ISO_PFUNC3_get_nat_led_3_e2(data)                                            ((0x40000000&(data))>>30)
#define ISO_PFUNC3_nat_led_3_pud_en_shift                                            (29)
#define ISO_PFUNC3_nat_led_3_pud_en_mask                                             (0x20000000)
#define ISO_PFUNC3_nat_led_3_pud_en(data)                                            (0x20000000&((data)<<29))
#define ISO_PFUNC3_nat_led_3_pud_en_src(data)                                        ((0x20000000&(data))>>29)
#define ISO_PFUNC3_get_nat_led_3_pud_en(data)                                        ((0x20000000&(data))>>29)
#define ISO_PFUNC3_nat_led_3_pud_sel_shift                                           (28)
#define ISO_PFUNC3_nat_led_3_pud_sel_mask                                            (0x10000000)
#define ISO_PFUNC3_nat_led_3_pud_sel(data)                                           (0x10000000&((data)<<28))
#define ISO_PFUNC3_nat_led_3_pud_sel_src(data)                                       ((0x10000000&(data))>>28)
#define ISO_PFUNC3_get_nat_led_3_pud_sel(data)                                       ((0x10000000&(data))>>28)
#define ISO_PFUNC3_nat_led_2_smt_shift                                               (27)
#define ISO_PFUNC3_nat_led_2_smt_mask                                                (0x08000000)
#define ISO_PFUNC3_nat_led_2_smt(data)                                               (0x08000000&((data)<<27))
#define ISO_PFUNC3_nat_led_2_smt_src(data)                                           ((0x08000000&(data))>>27)
#define ISO_PFUNC3_get_nat_led_2_smt(data)                                           ((0x08000000&(data))>>27)
#define ISO_PFUNC3_nat_led_2_e2_shift                                                (26)
#define ISO_PFUNC3_nat_led_2_e2_mask                                                 (0x04000000)
#define ISO_PFUNC3_nat_led_2_e2(data)                                                (0x04000000&((data)<<26))
#define ISO_PFUNC3_nat_led_2_e2_src(data)                                            ((0x04000000&(data))>>26)
#define ISO_PFUNC3_get_nat_led_2_e2(data)                                            ((0x04000000&(data))>>26)
#define ISO_PFUNC3_nat_led_2_pud_en_shift                                            (25)
#define ISO_PFUNC3_nat_led_2_pud_en_mask                                             (0x02000000)
#define ISO_PFUNC3_nat_led_2_pud_en(data)                                            (0x02000000&((data)<<25))
#define ISO_PFUNC3_nat_led_2_pud_en_src(data)                                        ((0x02000000&(data))>>25)
#define ISO_PFUNC3_get_nat_led_2_pud_en(data)                                        ((0x02000000&(data))>>25)
#define ISO_PFUNC3_nat_led_2_pud_sel_shift                                           (24)
#define ISO_PFUNC3_nat_led_2_pud_sel_mask                                            (0x01000000)
#define ISO_PFUNC3_nat_led_2_pud_sel(data)                                           (0x01000000&((data)<<24))
#define ISO_PFUNC3_nat_led_2_pud_sel_src(data)                                       ((0x01000000&(data))>>24)
#define ISO_PFUNC3_get_nat_led_2_pud_sel(data)                                       ((0x01000000&(data))>>24)
#define ISO_PFUNC3_nat_led_1_smt_shift                                               (23)
#define ISO_PFUNC3_nat_led_1_smt_mask                                                (0x00800000)
#define ISO_PFUNC3_nat_led_1_smt(data)                                               (0x00800000&((data)<<23))
#define ISO_PFUNC3_nat_led_1_smt_src(data)                                           ((0x00800000&(data))>>23)
#define ISO_PFUNC3_get_nat_led_1_smt(data)                                           ((0x00800000&(data))>>23)
#define ISO_PFUNC3_nat_led_1_e2_shift                                                (22)
#define ISO_PFUNC3_nat_led_1_e2_mask                                                 (0x00400000)
#define ISO_PFUNC3_nat_led_1_e2(data)                                                (0x00400000&((data)<<22))
#define ISO_PFUNC3_nat_led_1_e2_src(data)                                            ((0x00400000&(data))>>22)
#define ISO_PFUNC3_get_nat_led_1_e2(data)                                            ((0x00400000&(data))>>22)
#define ISO_PFUNC3_nat_led_1_pud_en_shift                                            (21)
#define ISO_PFUNC3_nat_led_1_pud_en_mask                                             (0x00200000)
#define ISO_PFUNC3_nat_led_1_pud_en(data)                                            (0x00200000&((data)<<21))
#define ISO_PFUNC3_nat_led_1_pud_en_src(data)                                        ((0x00200000&(data))>>21)
#define ISO_PFUNC3_get_nat_led_1_pud_en(data)                                        ((0x00200000&(data))>>21)
#define ISO_PFUNC3_nat_led_1_pud_sel_shift                                           (20)
#define ISO_PFUNC3_nat_led_1_pud_sel_mask                                            (0x00100000)
#define ISO_PFUNC3_nat_led_1_pud_sel(data)                                           (0x00100000&((data)<<20))
#define ISO_PFUNC3_nat_led_1_pud_sel_src(data)                                       ((0x00100000&(data))>>20)
#define ISO_PFUNC3_get_nat_led_1_pud_sel(data)                                       ((0x00100000&(data))>>20)
#define ISO_PFUNC3_nat_led_0_smt_shift                                               (19)
#define ISO_PFUNC3_nat_led_0_smt_mask                                                (0x00080000)
#define ISO_PFUNC3_nat_led_0_smt(data)                                               (0x00080000&((data)<<19))
#define ISO_PFUNC3_nat_led_0_smt_src(data)                                           ((0x00080000&(data))>>19)
#define ISO_PFUNC3_get_nat_led_0_smt(data)                                           ((0x00080000&(data))>>19)
#define ISO_PFUNC3_nat_led_0_e2_shift                                                (18)
#define ISO_PFUNC3_nat_led_0_e2_mask                                                 (0x00040000)
#define ISO_PFUNC3_nat_led_0_e2(data)                                                (0x00040000&((data)<<18))
#define ISO_PFUNC3_nat_led_0_e2_src(data)                                            ((0x00040000&(data))>>18)
#define ISO_PFUNC3_get_nat_led_0_e2(data)                                            ((0x00040000&(data))>>18)
#define ISO_PFUNC3_nat_led_0_pud_en_shift                                            (17)
#define ISO_PFUNC3_nat_led_0_pud_en_mask                                             (0x00020000)
#define ISO_PFUNC3_nat_led_0_pud_en(data)                                            (0x00020000&((data)<<17))
#define ISO_PFUNC3_nat_led_0_pud_en_src(data)                                        ((0x00020000&(data))>>17)
#define ISO_PFUNC3_get_nat_led_0_pud_en(data)                                        ((0x00020000&(data))>>17)
#define ISO_PFUNC3_nat_led_0_pud_sel_shift                                           (16)
#define ISO_PFUNC3_nat_led_0_pud_sel_mask                                            (0x00010000)
#define ISO_PFUNC3_nat_led_0_pud_sel(data)                                           (0x00010000&((data)<<16))
#define ISO_PFUNC3_nat_led_0_pud_sel_src(data)                                       ((0x00010000&(data))>>16)
#define ISO_PFUNC3_get_nat_led_0_pud_sel(data)                                       ((0x00010000&(data))>>16)
#define ISO_PFUNC3_hdmi_hpd_smt_shift                                                (15)
#define ISO_PFUNC3_hdmi_hpd_smt_mask                                                 (0x00008000)
#define ISO_PFUNC3_hdmi_hpd_smt(data)                                                (0x00008000&((data)<<15))
#define ISO_PFUNC3_hdmi_hpd_smt_src(data)                                            ((0x00008000&(data))>>15)
#define ISO_PFUNC3_get_hdmi_hpd_smt(data)                                            ((0x00008000&(data))>>15)
#define ISO_PFUNC3_hdmi_hpd_e2_shift                                                 (14)
#define ISO_PFUNC3_hdmi_hpd_e2_mask                                                  (0x00004000)
#define ISO_PFUNC3_hdmi_hpd_e2(data)                                                 (0x00004000&((data)<<14))
#define ISO_PFUNC3_hdmi_hpd_e2_src(data)                                             ((0x00004000&(data))>>14)
#define ISO_PFUNC3_get_hdmi_hpd_e2(data)                                             ((0x00004000&(data))>>14)
#define ISO_PFUNC3_hdmi_hpd_pud_en_shift                                             (13)
#define ISO_PFUNC3_hdmi_hpd_pud_en_mask                                              (0x00002000)
#define ISO_PFUNC3_hdmi_hpd_pud_en(data)                                             (0x00002000&((data)<<13))
#define ISO_PFUNC3_hdmi_hpd_pud_en_src(data)                                         ((0x00002000&(data))>>13)
#define ISO_PFUNC3_get_hdmi_hpd_pud_en(data)                                         ((0x00002000&(data))>>13)
#define ISO_PFUNC3_hdmi_hpd_pud_sel_shift                                            (12)
#define ISO_PFUNC3_hdmi_hpd_pud_sel_mask                                             (0x00001000)
#define ISO_PFUNC3_hdmi_hpd_pud_sel(data)                                            (0x00001000&((data)<<12))
#define ISO_PFUNC3_hdmi_hpd_pud_sel_src(data)                                        ((0x00001000&(data))>>12)
#define ISO_PFUNC3_get_hdmi_hpd_pud_sel(data)                                        ((0x00001000&(data))>>12)
#define ISO_PFUNC3_reset_n_pud_en_shift                                              (11)
#define ISO_PFUNC3_reset_n_pud_en_mask                                               (0x00000800)
#define ISO_PFUNC3_reset_n_pud_en(data)                                              (0x00000800&((data)<<11))
#define ISO_PFUNC3_reset_n_pud_en_src(data)                                          ((0x00000800&(data))>>11)
#define ISO_PFUNC3_get_reset_n_pud_en(data)                                          ((0x00000800&(data))>>11)
#define ISO_PFUNC3_reset_n_pud_sel_shift                                             (10)
#define ISO_PFUNC3_reset_n_pud_sel_mask                                              (0x00000400)
#define ISO_PFUNC3_reset_n_pud_sel(data)                                             (0x00000400&((data)<<10))
#define ISO_PFUNC3_reset_n_pud_sel_src(data)                                         ((0x00000400&(data))>>10)
#define ISO_PFUNC3_get_reset_n_pud_sel(data)                                         ((0x00000400&(data))>>10)
#define ISO_PFUNC3_boption12_en_shift                                                (7)
#define ISO_PFUNC3_boption12_en_mask                                                 (0x00000080)
#define ISO_PFUNC3_boption12_en(data)                                                (0x00000080&((data)<<7))
#define ISO_PFUNC3_boption12_en_src(data)                                            ((0x00000080&(data))>>7)
#define ISO_PFUNC3_get_boption12_en(data)                                            ((0x00000080&(data))>>7)
#define ISO_PFUNC3_boption12_sel_shift                                               (6)
#define ISO_PFUNC3_boption12_sel_mask                                                (0x00000040)
#define ISO_PFUNC3_boption12_sel(data)                                               (0x00000040&((data)<<6))
#define ISO_PFUNC3_boption12_sel_src(data)                                           ((0x00000040&(data))>>6)
#define ISO_PFUNC3_get_boption12_sel(data)                                           ((0x00000040&(data))>>6)
#define ISO_PFUNC3_boption11_en_shift                                                (5)
#define ISO_PFUNC3_boption11_en_mask                                                 (0x00000020)
#define ISO_PFUNC3_boption11_en(data)                                                (0x00000020&((data)<<5))
#define ISO_PFUNC3_boption11_en_src(data)                                            ((0x00000020&(data))>>5)
#define ISO_PFUNC3_get_boption11_en(data)                                            ((0x00000020&(data))>>5)
#define ISO_PFUNC3_boption11_sel_shift                                               (4)
#define ISO_PFUNC3_boption11_sel_mask                                                (0x00000010)
#define ISO_PFUNC3_boption11_sel(data)                                               (0x00000010&((data)<<4))
#define ISO_PFUNC3_boption11_sel_src(data)                                           ((0x00000010&(data))>>4)
#define ISO_PFUNC3_get_boption11_sel(data)                                           ((0x00000010&(data))>>4)
#define ISO_PFUNC3_boption10_en_shift                                                (3)
#define ISO_PFUNC3_boption10_en_mask                                                 (0x00000008)
#define ISO_PFUNC3_boption10_en(data)                                                (0x00000008&((data)<<3))
#define ISO_PFUNC3_boption10_en_src(data)                                            ((0x00000008&(data))>>3)
#define ISO_PFUNC3_get_boption10_en(data)                                            ((0x00000008&(data))>>3)
#define ISO_PFUNC3_boption10_sel_shift                                               (2)
#define ISO_PFUNC3_boption10_sel_mask                                                (0x00000004)
#define ISO_PFUNC3_boption10_sel(data)                                               (0x00000004&((data)<<2))
#define ISO_PFUNC3_boption10_sel_src(data)                                           ((0x00000004&(data))>>2)
#define ISO_PFUNC3_get_boption10_sel(data)                                           ((0x00000004&(data))>>2)
#define ISO_PFUNC3_boption2_en_shift                                                 (1)
#define ISO_PFUNC3_boption2_en_mask                                                  (0x00000002)
#define ISO_PFUNC3_boption2_en(data)                                                 (0x00000002&((data)<<1))
#define ISO_PFUNC3_boption2_en_src(data)                                             ((0x00000002&(data))>>1)
#define ISO_PFUNC3_get_boption2_en(data)                                             ((0x00000002&(data))>>1)
#define ISO_PFUNC3_boption2_sel_shift                                                (0)
#define ISO_PFUNC3_boption2_sel_mask                                                 (0x00000001)
#define ISO_PFUNC3_boption2_sel(data)                                                (0x00000001&((data)<<0))
#define ISO_PFUNC3_boption2_sel_src(data)                                            ((0x00000001&(data))>>0)
#define ISO_PFUNC3_get_boption2_sel(data)                                            ((0x00000001&(data))>>0)


#define ISO_MUXPAD0                                                                  0x98007310
#define ISO_MUXPAD0_reg_addr                                                         "0x98007310"
#define ISO_MUXPAD0_reg                                                              0x98007310
#define set_ISO_MUXPAD0_reg(data)   (*((volatile unsigned int*) ISO_MUXPAD0_reg)=data)
#define get_ISO_MUXPAD0_reg   (*((volatile unsigned int*) ISO_MUXPAD0_reg))
#define ISO_MUXPAD0_inst_adr                                                         "0x00C4"
#define ISO_MUXPAD0_inst                                                             0x00C4
#define ISO_MUXPAD0_etn_led_rxtx_shift                                               (28)
#define ISO_MUXPAD0_etn_led_rxtx_mask                                                (0x30000000)
#define ISO_MUXPAD0_etn_led_rxtx(data)                                               (0x30000000&((data)<<28))
#define ISO_MUXPAD0_etn_led_rxtx_src(data)                                           ((0x30000000&(data))>>28)
#define ISO_MUXPAD0_get_etn_led_rxtx(data)                                           ((0x30000000&(data))>>28)
#define ISO_MUXPAD0_etn_led_link_shift                                               (26)
#define ISO_MUXPAD0_etn_led_link_mask                                                (0x0C000000)
#define ISO_MUXPAD0_etn_led_link(data)                                               (0x0C000000&((data)<<26))
#define ISO_MUXPAD0_etn_led_link_src(data)                                           ((0x0C000000&(data))>>26)
#define ISO_MUXPAD0_get_etn_led_link(data)                                           ((0x0C000000&(data))>>26)
#define ISO_MUXPAD0_i2c_sda_0_shift                                                  (24)
#define ISO_MUXPAD0_i2c_sda_0_mask                                                   (0x03000000)
#define ISO_MUXPAD0_i2c_sda_0(data)                                                  (0x03000000&((data)<<24))
#define ISO_MUXPAD0_i2c_sda_0_src(data)                                              ((0x03000000&(data))>>24)
#define ISO_MUXPAD0_get_i2c_sda_0(data)                                              ((0x03000000&(data))>>24)
#define ISO_MUXPAD0_i2c_scl_0_shift                                                  (22)
#define ISO_MUXPAD0_i2c_scl_0_mask                                                   (0x00C00000)
#define ISO_MUXPAD0_i2c_scl_0(data)                                                  (0x00C00000&((data)<<22))
#define ISO_MUXPAD0_i2c_scl_0_src(data)                                              ((0x00C00000&(data))>>22)
#define ISO_MUXPAD0_get_i2c_scl_0(data)                                              ((0x00C00000&(data))>>22)
#define ISO_MUXPAD0_ur1_rts_n_shift                                                  (20)
#define ISO_MUXPAD0_ur1_rts_n_mask                                                   (0x00300000)
#define ISO_MUXPAD0_ur1_rts_n(data)                                                  (0x00300000&((data)<<20))
#define ISO_MUXPAD0_ur1_rts_n_src(data)                                              ((0x00300000&(data))>>20)
#define ISO_MUXPAD0_get_ur1_rts_n(data)                                              ((0x00300000&(data))>>20)
#define ISO_MUXPAD0_ur1_cts_n_shift                                                  (18)
#define ISO_MUXPAD0_ur1_cts_n_mask                                                   (0x000C0000)
#define ISO_MUXPAD0_ur1_cts_n(data)                                                  (0x000C0000&((data)<<18))
#define ISO_MUXPAD0_ur1_cts_n_src(data)                                              ((0x000C0000&(data))>>18)
#define ISO_MUXPAD0_get_ur1_cts_n(data)                                              ((0x000C0000&(data))>>18)
#define ISO_MUXPAD0_ur1_tx_shift                                                     (16)
#define ISO_MUXPAD0_ur1_tx_mask                                                      (0x00030000)
#define ISO_MUXPAD0_ur1_tx(data)                                                     (0x00030000&((data)<<16))
#define ISO_MUXPAD0_ur1_tx_src(data)                                                 ((0x00030000&(data))>>16)
#define ISO_MUXPAD0_get_ur1_tx(data)                                                 ((0x00030000&(data))>>16)
#define ISO_MUXPAD0_ur1_rx_shift                                                     (14)
#define ISO_MUXPAD0_ur1_rx_mask                                                      (0x0000C000)
#define ISO_MUXPAD0_ur1_rx(data)                                                     (0x0000C000&((data)<<14))
#define ISO_MUXPAD0_ur1_rx_src(data)                                                 ((0x0000C000&(data))>>14)
#define ISO_MUXPAD0_get_ur1_rx(data)                                                 ((0x0000C000&(data))>>14)
#define ISO_MUXPAD0_ur0_tx_shift                                                     (12)
#define ISO_MUXPAD0_ur0_tx_mask                                                      (0x00003000)
#define ISO_MUXPAD0_ur0_tx(data)                                                     (0x00003000&((data)<<12))
#define ISO_MUXPAD0_ur0_tx_src(data)                                                 ((0x00003000&(data))>>12)
#define ISO_MUXPAD0_get_ur0_tx(data)                                                 ((0x00003000&(data))>>12)
#define ISO_MUXPAD0_ur0_rx_shift                                                     (10)
#define ISO_MUXPAD0_ur0_rx_mask                                                      (0x00000C00)
#define ISO_MUXPAD0_ur0_rx(data)                                                     (0x00000C00&((data)<<10))
#define ISO_MUXPAD0_ur0_rx_src(data)                                                 ((0x00000C00&(data))>>10)
#define ISO_MUXPAD0_get_ur0_rx(data)                                                 ((0x00000C00&(data))>>10)
#define ISO_MUXPAD0_ir_tx_shift                                                      (8)
#define ISO_MUXPAD0_ir_tx_mask                                                       (0x00000300)
#define ISO_MUXPAD0_ir_tx(data)                                                      (0x00000300&((data)<<8))
#define ISO_MUXPAD0_ir_tx_src(data)                                                  ((0x00000300&(data))>>8)
#define ISO_MUXPAD0_get_ir_tx(data)                                                  ((0x00000300&(data))>>8)
#define ISO_MUXPAD0_ir_rx_shift                                                      (6)
#define ISO_MUXPAD0_ir_rx_mask                                                       (0x000000C0)
#define ISO_MUXPAD0_ir_rx(data)                                                      (0x000000C0&((data)<<6))
#define ISO_MUXPAD0_ir_rx_src(data)                                                  ((0x000000C0&(data))>>6)
#define ISO_MUXPAD0_get_ir_rx(data)                                                  ((0x000000C0&(data))>>6)
#define ISO_MUXPAD0_iso_gpio_7_shift                                                 (4)
#define ISO_MUXPAD0_iso_gpio_7_mask                                                  (0x00000030)
#define ISO_MUXPAD0_iso_gpio_7(data)                                                 (0x00000030&((data)<<4))
#define ISO_MUXPAD0_iso_gpio_7_src(data)                                             ((0x00000030&(data))>>4)
#define ISO_MUXPAD0_get_iso_gpio_7(data)                                             ((0x00000030&(data))>>4)
#define ISO_MUXPAD0_iso_gpio_5_shift                                                 (2)
#define ISO_MUXPAD0_iso_gpio_5_mask                                                  (0x0000000C)
#define ISO_MUXPAD0_iso_gpio_5(data)                                                 (0x0000000C&((data)<<2))
#define ISO_MUXPAD0_iso_gpio_5_src(data)                                             ((0x0000000C&(data))>>2)
#define ISO_MUXPAD0_get_iso_gpio_5(data)                                             ((0x0000000C&(data))>>2)
#define ISO_MUXPAD0_iso_gpio_4_shift                                                 (0)
#define ISO_MUXPAD0_iso_gpio_4_mask                                                  (0x00000003)
#define ISO_MUXPAD0_iso_gpio_4(data)                                                 (0x00000003&((data)<<0))
#define ISO_MUXPAD0_iso_gpio_4_src(data)                                             ((0x00000003&(data))>>0)
#define ISO_MUXPAD0_get_iso_gpio_4(data)                                             ((0x00000003&(data))>>0)


#define ISO_MUXPAD1                                                                  0x98007314
#define ISO_MUXPAD1_reg_addr                                                         "0x98007314"
#define ISO_MUXPAD1_reg                                                              0x98007314
#define set_ISO_MUXPAD1_reg(data)   (*((volatile unsigned int*) ISO_MUXPAD1_reg)=data)
#define get_ISO_MUXPAD1_reg   (*((volatile unsigned int*) ISO_MUXPAD1_reg))
#define ISO_MUXPAD1_inst_adr                                                         "0x00C5"
#define ISO_MUXPAD1_inst                                                             0x00C5
#define ISO_MUXPAD1_ur2_loc_shift                                                    (30)
#define ISO_MUXPAD1_ur2_loc_mask                                                     (0xC0000000)
#define ISO_MUXPAD1_ur2_loc(data)                                                    (0xC0000000&((data)<<30))
#define ISO_MUXPAD1_ur2_loc_src(data)                                                ((0xC0000000&(data))>>30)
#define ISO_MUXPAD1_get_ur2_loc(data)                                                ((0xC0000000&(data))>>30)
#define ISO_MUXPAD1_ejtag_avcpu_loc_shift                                            (28)
#define ISO_MUXPAD1_ejtag_avcpu_loc_mask                                             (0x30000000)
#define ISO_MUXPAD1_ejtag_avcpu_loc(data)                                            (0x30000000&((data)<<28))
#define ISO_MUXPAD1_ejtag_avcpu_loc_src(data)                                        ((0x30000000&(data))>>28)
#define ISO_MUXPAD1_get_ejtag_avcpu_loc(data)                                        ((0x30000000&(data))>>28)
#define ISO_MUXPAD1_pwm_01_open_drain_en_loc1_shift                                  (27)
#define ISO_MUXPAD1_pwm_01_open_drain_en_loc1_mask                                   (0x08000000)
#define ISO_MUXPAD1_pwm_01_open_drain_en_loc1(data)                                  (0x08000000&((data)<<27))
#define ISO_MUXPAD1_pwm_01_open_drain_en_loc1_src(data)                              ((0x08000000&(data))>>27)
#define ISO_MUXPAD1_get_pwm_01_open_drain_en_loc1(data)                              ((0x08000000&(data))>>27)
#define ISO_MUXPAD1_pwm_23_open_drain_en_loc1_shift                                  (26)
#define ISO_MUXPAD1_pwm_23_open_drain_en_loc1_mask                                   (0x04000000)
#define ISO_MUXPAD1_pwm_23_open_drain_en_loc1(data)                                  (0x04000000&((data)<<26))
#define ISO_MUXPAD1_pwm_23_open_drain_en_loc1_src(data)                              ((0x04000000&(data))>>26)
#define ISO_MUXPAD1_get_pwm_23_open_drain_en_loc1(data)                              ((0x04000000&(data))>>26)
#define ISO_MUXPAD1_pwm_01_open_drain_en_loc0_shift                                  (25)
#define ISO_MUXPAD1_pwm_01_open_drain_en_loc0_mask                                   (0x02000000)
#define ISO_MUXPAD1_pwm_01_open_drain_en_loc0(data)                                  (0x02000000&((data)<<25))
#define ISO_MUXPAD1_pwm_01_open_drain_en_loc0_src(data)                              ((0x02000000&(data))>>25)
#define ISO_MUXPAD1_get_pwm_01_open_drain_en_loc0(data)                              ((0x02000000&(data))>>25)
#define ISO_MUXPAD1_pwm_23_open_drain_en_loc0_shift                                  (24)
#define ISO_MUXPAD1_pwm_23_open_drain_en_loc0_mask                                   (0x01000000)
#define ISO_MUXPAD1_pwm_23_open_drain_en_loc0(data)                                  (0x01000000&((data)<<24))
#define ISO_MUXPAD1_pwm_23_open_drain_en_loc0_src(data)                              ((0x01000000&(data))>>24)
#define ISO_MUXPAD1_get_pwm_23_open_drain_en_loc0(data)                              ((0x01000000&(data))>>24)
#define ISO_MUXPAD1_nat_led_3_shift                                                  (22)
#define ISO_MUXPAD1_nat_led_3_mask                                                   (0x00C00000)
#define ISO_MUXPAD1_nat_led_3(data)                                                  (0x00C00000&((data)<<22))
#define ISO_MUXPAD1_nat_led_3_src(data)                                              ((0x00C00000&(data))>>22)
#define ISO_MUXPAD1_get_nat_led_3(data)                                              ((0x00C00000&(data))>>22)
#define ISO_MUXPAD1_nat_led_2_shift                                                  (20)
#define ISO_MUXPAD1_nat_led_2_mask                                                   (0x00300000)
#define ISO_MUXPAD1_nat_led_2(data)                                                  (0x00300000&((data)<<20))
#define ISO_MUXPAD1_nat_led_2_src(data)                                              ((0x00300000&(data))>>20)
#define ISO_MUXPAD1_get_nat_led_2(data)                                              ((0x00300000&(data))>>20)
#define ISO_MUXPAD1_nat_led_1_shift                                                  (18)
#define ISO_MUXPAD1_nat_led_1_mask                                                   (0x000C0000)
#define ISO_MUXPAD1_nat_led_1(data)                                                  (0x000C0000&((data)<<18))
#define ISO_MUXPAD1_nat_led_1_src(data)                                              ((0x000C0000&(data))>>18)
#define ISO_MUXPAD1_get_nat_led_1(data)                                              ((0x000C0000&(data))>>18)
#define ISO_MUXPAD1_nat_led_0_shift                                                  (16)
#define ISO_MUXPAD1_nat_led_0_mask                                                   (0x00030000)
#define ISO_MUXPAD1_nat_led_0(data)                                                  (0x00030000&((data)<<16))
#define ISO_MUXPAD1_nat_led_0_src(data)                                              ((0x00030000&(data))>>16)
#define ISO_MUXPAD1_get_nat_led_0(data)                                              ((0x00030000&(data))>>16)
#define ISO_MUXPAD1_i2c_sda_1_shift                                                  (14)
#define ISO_MUXPAD1_i2c_sda_1_mask                                                   (0x0000C000)
#define ISO_MUXPAD1_i2c_sda_1(data)                                                  (0x0000C000&((data)<<14))
#define ISO_MUXPAD1_i2c_sda_1_src(data)                                              ((0x0000C000&(data))>>14)
#define ISO_MUXPAD1_get_i2c_sda_1(data)                                              ((0x0000C000&(data))>>14)
#define ISO_MUXPAD1_i2c_scl_1_shift                                                  (12)
#define ISO_MUXPAD1_i2c_scl_1_mask                                                   (0x00003000)
#define ISO_MUXPAD1_i2c_scl_1(data)                                                  (0x00003000&((data)<<12))
#define ISO_MUXPAD1_i2c_scl_1_src(data)                                              ((0x00003000&(data))>>12)
#define ISO_MUXPAD1_get_i2c_scl_1(data)                                              ((0x00003000&(data))>>12)
#define ISO_MUXPAD1_iso_gpio_3_shift                                                 (9)
#define ISO_MUXPAD1_iso_gpio_3_mask                                                  (0x00000E00)
#define ISO_MUXPAD1_iso_gpio_3(data)                                                 (0x00000E00&((data)<<9))
#define ISO_MUXPAD1_iso_gpio_3_src(data)                                             ((0x00000E00&(data))>>9)
#define ISO_MUXPAD1_get_iso_gpio_3(data)                                             ((0x00000E00&(data))>>9)
#define ISO_MUXPAD1_iso_gpio_2_shift                                                 (6)
#define ISO_MUXPAD1_iso_gpio_2_mask                                                  (0x000001C0)
#define ISO_MUXPAD1_iso_gpio_2(data)                                                 (0x000001C0&((data)<<6))
#define ISO_MUXPAD1_iso_gpio_2_src(data)                                             ((0x000001C0&(data))>>6)
#define ISO_MUXPAD1_get_iso_gpio_2(data)                                             ((0x000001C0&(data))>>6)
#define ISO_MUXPAD1_hdmi_hpd_shift                                                   (4)
#define ISO_MUXPAD1_hdmi_hpd_mask                                                    (0x00000030)
#define ISO_MUXPAD1_hdmi_hpd(data)                                                   (0x00000030&((data)<<4))
#define ISO_MUXPAD1_hdmi_hpd_src(data)                                               ((0x00000030&(data))>>4)
#define ISO_MUXPAD1_get_hdmi_hpd(data)                                               ((0x00000030&(data))>>4)
#define ISO_MUXPAD1_i2c_sda_6_shift                                                  (2)
#define ISO_MUXPAD1_i2c_sda_6_mask                                                   (0x0000000C)
#define ISO_MUXPAD1_i2c_sda_6(data)                                                  (0x0000000C&((data)<<2))
#define ISO_MUXPAD1_i2c_sda_6_src(data)                                              ((0x0000000C&(data))>>2)
#define ISO_MUXPAD1_get_i2c_sda_6(data)                                              ((0x0000000C&(data))>>2)
#define ISO_MUXPAD1_i2c_scl_6_shift                                                  (0)
#define ISO_MUXPAD1_i2c_scl_6_mask                                                   (0x00000003)
#define ISO_MUXPAD1_i2c_scl_6(data)                                                  (0x00000003&((data)<<0))
#define ISO_MUXPAD1_i2c_scl_6_src(data)                                              ((0x00000003&(data))>>0)
#define ISO_MUXPAD1_get_i2c_scl_6(data)                                              ((0x00000003&(data))>>0)


#define ISO_PFUNC4                                                                   0x98007318
#define ISO_PFUNC4_reg_addr                                                          "0x98007318"
#define ISO_PFUNC4_reg                                                               0x98007318
#define set_ISO_PFUNC4_reg(data)   (*((volatile unsigned int*) ISO_PFUNC4_reg)=data)
#define get_ISO_PFUNC4_reg   (*((volatile unsigned int*) ISO_PFUNC4_reg))
#define ISO_PFUNC4_inst_adr                                                          "0x00C6"
#define ISO_PFUNC4_inst                                                              0x00C6
#define ISO_PFUNC4_boot_sel_smt_shift                                                (27)
#define ISO_PFUNC4_boot_sel_smt_mask                                                 (0x08000000)
#define ISO_PFUNC4_boot_sel_smt(data)                                                (0x08000000&((data)<<27))
#define ISO_PFUNC4_boot_sel_smt_src(data)                                            ((0x08000000&(data))>>27)
#define ISO_PFUNC4_get_boot_sel_smt(data)                                            ((0x08000000&(data))>>27)
#define ISO_PFUNC4_testmode_smt_shift                                                (26)
#define ISO_PFUNC4_testmode_smt_mask                                                 (0x04000000)
#define ISO_PFUNC4_testmode_smt(data)                                                (0x04000000&((data)<<26))
#define ISO_PFUNC4_testmode_smt_src(data)                                            ((0x04000000&(data))>>26)
#define ISO_PFUNC4_get_testmode_smt(data)                                            ((0x04000000&(data))>>26)
#define ISO_PFUNC4_reset_n_smt_shift                                                 (25)
#define ISO_PFUNC4_reset_n_smt_mask                                                  (0x02000000)
#define ISO_PFUNC4_reset_n_smt(data)                                                 (0x02000000&((data)<<25))
#define ISO_PFUNC4_reset_n_smt_src(data)                                             ((0x02000000&(data))>>25)
#define ISO_PFUNC4_get_reset_n_smt(data)                                             ((0x02000000&(data))>>25)
#define ISO_PFUNC4_boption12_smt_shift                                               (23)
#define ISO_PFUNC4_boption12_smt_mask                                                (0x00800000)
#define ISO_PFUNC4_boption12_smt(data)                                               (0x00800000&((data)<<23))
#define ISO_PFUNC4_boption12_smt_src(data)                                           ((0x00800000&(data))>>23)
#define ISO_PFUNC4_get_boption12_smt(data)                                           ((0x00800000&(data))>>23)
#define ISO_PFUNC4_boption11_smt_shift                                               (22)
#define ISO_PFUNC4_boption11_smt_mask                                                (0x00400000)
#define ISO_PFUNC4_boption11_smt(data)                                               (0x00400000&((data)<<22))
#define ISO_PFUNC4_boption11_smt_src(data)                                           ((0x00400000&(data))>>22)
#define ISO_PFUNC4_get_boption11_smt(data)                                           ((0x00400000&(data))>>22)
#define ISO_PFUNC4_boption10_smt_shift                                               (21)
#define ISO_PFUNC4_boption10_smt_mask                                                (0x00200000)
#define ISO_PFUNC4_boption10_smt(data)                                               (0x00200000&((data)<<21))
#define ISO_PFUNC4_boption10_smt_src(data)                                           ((0x00200000&(data))>>21)
#define ISO_PFUNC4_get_boption10_smt(data)                                           ((0x00200000&(data))>>21)
#define ISO_PFUNC4_boption2_smt_shift                                                (20)
#define ISO_PFUNC4_boption2_smt_mask                                                 (0x00100000)
#define ISO_PFUNC4_boption2_smt(data)                                                (0x00100000&((data)<<20))
#define ISO_PFUNC4_boption2_smt_src(data)                                            ((0x00100000&(data))>>20)
#define ISO_PFUNC4_get_boption2_smt(data)                                            ((0x00100000&(data))>>20)
#define ISO_PFUNC4_iso_gpio_25_smt_shift                                             (19)
#define ISO_PFUNC4_iso_gpio_25_smt_mask                                              (0x00080000)
#define ISO_PFUNC4_iso_gpio_25_smt(data)                                             (0x00080000&((data)<<19))
#define ISO_PFUNC4_iso_gpio_25_smt_src(data)                                         ((0x00080000&(data))>>19)
#define ISO_PFUNC4_get_iso_gpio_25_smt(data)                                         ((0x00080000&(data))>>19)
#define ISO_PFUNC4_iso_gpio_25_e2_shift                                              (18)
#define ISO_PFUNC4_iso_gpio_25_e2_mask                                               (0x00040000)
#define ISO_PFUNC4_iso_gpio_25_e2(data)                                              (0x00040000&((data)<<18))
#define ISO_PFUNC4_iso_gpio_25_e2_src(data)                                          ((0x00040000&(data))>>18)
#define ISO_PFUNC4_get_iso_gpio_25_e2(data)                                          ((0x00040000&(data))>>18)
#define ISO_PFUNC4_iso_gpio_25_pud_en_shift                                          (17)
#define ISO_PFUNC4_iso_gpio_25_pud_en_mask                                           (0x00020000)
#define ISO_PFUNC4_iso_gpio_25_pud_en(data)                                          (0x00020000&((data)<<17))
#define ISO_PFUNC4_iso_gpio_25_pud_en_src(data)                                      ((0x00020000&(data))>>17)
#define ISO_PFUNC4_get_iso_gpio_25_pud_en(data)                                      ((0x00020000&(data))>>17)
#define ISO_PFUNC4_iso_gpio_25_pud_sel_shift                                         (16)
#define ISO_PFUNC4_iso_gpio_25_pud_sel_mask                                          (0x00010000)
#define ISO_PFUNC4_iso_gpio_25_pud_sel(data)                                         (0x00010000&((data)<<16))
#define ISO_PFUNC4_iso_gpio_25_pud_sel_src(data)                                     ((0x00010000&(data))>>16)
#define ISO_PFUNC4_get_iso_gpio_25_pud_sel(data)                                     ((0x00010000&(data))>>16)
#define ISO_PFUNC4_iso_gpio_24_smt_shift                                             (15)
#define ISO_PFUNC4_iso_gpio_24_smt_mask                                              (0x00008000)
#define ISO_PFUNC4_iso_gpio_24_smt(data)                                             (0x00008000&((data)<<15))
#define ISO_PFUNC4_iso_gpio_24_smt_src(data)                                         ((0x00008000&(data))>>15)
#define ISO_PFUNC4_get_iso_gpio_24_smt(data)                                         ((0x00008000&(data))>>15)
#define ISO_PFUNC4_iso_gpio_24_e2_shift                                              (14)
#define ISO_PFUNC4_iso_gpio_24_e2_mask                                               (0x00004000)
#define ISO_PFUNC4_iso_gpio_24_e2(data)                                              (0x00004000&((data)<<14))
#define ISO_PFUNC4_iso_gpio_24_e2_src(data)                                          ((0x00004000&(data))>>14)
#define ISO_PFUNC4_get_iso_gpio_24_e2(data)                                          ((0x00004000&(data))>>14)
#define ISO_PFUNC4_iso_gpio_24_pud_en_shift                                          (13)
#define ISO_PFUNC4_iso_gpio_24_pud_en_mask                                           (0x00002000)
#define ISO_PFUNC4_iso_gpio_24_pud_en(data)                                          (0x00002000&((data)<<13))
#define ISO_PFUNC4_iso_gpio_24_pud_en_src(data)                                      ((0x00002000&(data))>>13)
#define ISO_PFUNC4_get_iso_gpio_24_pud_en(data)                                      ((0x00002000&(data))>>13)
#define ISO_PFUNC4_iso_gpio_24_pud_sel_shift                                         (12)
#define ISO_PFUNC4_iso_gpio_24_pud_sel_mask                                          (0x00001000)
#define ISO_PFUNC4_iso_gpio_24_pud_sel(data)                                         (0x00001000&((data)<<12))
#define ISO_PFUNC4_iso_gpio_24_pud_sel_src(data)                                     ((0x00001000&(data))>>12)
#define ISO_PFUNC4_get_iso_gpio_24_pud_sel(data)                                     ((0x00001000&(data))>>12)
#define ISO_PFUNC4_iso_gpio_23_smt_shift                                             (11)
#define ISO_PFUNC4_iso_gpio_23_smt_mask                                              (0x00000800)
#define ISO_PFUNC4_iso_gpio_23_smt(data)                                             (0x00000800&((data)<<11))
#define ISO_PFUNC4_iso_gpio_23_smt_src(data)                                         ((0x00000800&(data))>>11)
#define ISO_PFUNC4_get_iso_gpio_23_smt(data)                                         ((0x00000800&(data))>>11)
#define ISO_PFUNC4_iso_gpio_23_e2_shift                                              (10)
#define ISO_PFUNC4_iso_gpio_23_e2_mask                                               (0x00000400)
#define ISO_PFUNC4_iso_gpio_23_e2(data)                                              (0x00000400&((data)<<10))
#define ISO_PFUNC4_iso_gpio_23_e2_src(data)                                          ((0x00000400&(data))>>10)
#define ISO_PFUNC4_get_iso_gpio_23_e2(data)                                          ((0x00000400&(data))>>10)
#define ISO_PFUNC4_iso_gpio_23_pud_en_shift                                          (9)
#define ISO_PFUNC4_iso_gpio_23_pud_en_mask                                           (0x00000200)
#define ISO_PFUNC4_iso_gpio_23_pud_en(data)                                          (0x00000200&((data)<<9))
#define ISO_PFUNC4_iso_gpio_23_pud_en_src(data)                                      ((0x00000200&(data))>>9)
#define ISO_PFUNC4_get_iso_gpio_23_pud_en(data)                                      ((0x00000200&(data))>>9)
#define ISO_PFUNC4_iso_gpio_23_pud_sel_shift                                         (8)
#define ISO_PFUNC4_iso_gpio_23_pud_sel_mask                                          (0x00000100)
#define ISO_PFUNC4_iso_gpio_23_pud_sel(data)                                         (0x00000100&((data)<<8))
#define ISO_PFUNC4_iso_gpio_23_pud_sel_src(data)                                     ((0x00000100&(data))>>8)
#define ISO_PFUNC4_get_iso_gpio_23_pud_sel(data)                                     ((0x00000100&(data))>>8)
#define ISO_PFUNC4_iso_gpio_22_smt_shift                                             (7)
#define ISO_PFUNC4_iso_gpio_22_smt_mask                                              (0x00000080)
#define ISO_PFUNC4_iso_gpio_22_smt(data)                                             (0x00000080&((data)<<7))
#define ISO_PFUNC4_iso_gpio_22_smt_src(data)                                         ((0x00000080&(data))>>7)
#define ISO_PFUNC4_get_iso_gpio_22_smt(data)                                         ((0x00000080&(data))>>7)
#define ISO_PFUNC4_iso_gpio_22_e2_shift                                              (6)
#define ISO_PFUNC4_iso_gpio_22_e2_mask                                               (0x00000040)
#define ISO_PFUNC4_iso_gpio_22_e2(data)                                              (0x00000040&((data)<<6))
#define ISO_PFUNC4_iso_gpio_22_e2_src(data)                                          ((0x00000040&(data))>>6)
#define ISO_PFUNC4_get_iso_gpio_22_e2(data)                                          ((0x00000040&(data))>>6)
#define ISO_PFUNC4_iso_gpio_22_pud_en_shift                                          (5)
#define ISO_PFUNC4_iso_gpio_22_pud_en_mask                                           (0x00000020)
#define ISO_PFUNC4_iso_gpio_22_pud_en(data)                                          (0x00000020&((data)<<5))
#define ISO_PFUNC4_iso_gpio_22_pud_en_src(data)                                      ((0x00000020&(data))>>5)
#define ISO_PFUNC4_get_iso_gpio_22_pud_en(data)                                      ((0x00000020&(data))>>5)
#define ISO_PFUNC4_iso_gpio_22_pud_sel_shift                                         (4)
#define ISO_PFUNC4_iso_gpio_22_pud_sel_mask                                          (0x00000010)
#define ISO_PFUNC4_iso_gpio_22_pud_sel(data)                                         (0x00000010&((data)<<4))
#define ISO_PFUNC4_iso_gpio_22_pud_sel_src(data)                                     ((0x00000010&(data))>>4)
#define ISO_PFUNC4_get_iso_gpio_22_pud_sel(data)                                     ((0x00000010&(data))>>4)
#define ISO_PFUNC4_iso_gpio_21_smt_shift                                             (3)
#define ISO_PFUNC4_iso_gpio_21_smt_mask                                              (0x00000008)
#define ISO_PFUNC4_iso_gpio_21_smt(data)                                             (0x00000008&((data)<<3))
#define ISO_PFUNC4_iso_gpio_21_smt_src(data)                                         ((0x00000008&(data))>>3)
#define ISO_PFUNC4_get_iso_gpio_21_smt(data)                                         ((0x00000008&(data))>>3)
#define ISO_PFUNC4_iso_gpio_21_e2_shift                                              (2)
#define ISO_PFUNC4_iso_gpio_21_e2_mask                                               (0x00000004)
#define ISO_PFUNC4_iso_gpio_21_e2(data)                                              (0x00000004&((data)<<2))
#define ISO_PFUNC4_iso_gpio_21_e2_src(data)                                          ((0x00000004&(data))>>2)
#define ISO_PFUNC4_get_iso_gpio_21_e2(data)                                          ((0x00000004&(data))>>2)
#define ISO_PFUNC4_iso_gpio_21_pud_en_shift                                          (1)
#define ISO_PFUNC4_iso_gpio_21_pud_en_mask                                           (0x00000002)
#define ISO_PFUNC4_iso_gpio_21_pud_en(data)                                          (0x00000002&((data)<<1))
#define ISO_PFUNC4_iso_gpio_21_pud_en_src(data)                                      ((0x00000002&(data))>>1)
#define ISO_PFUNC4_get_iso_gpio_21_pud_en(data)                                      ((0x00000002&(data))>>1)
#define ISO_PFUNC4_iso_gpio_21_pud_sel_shift                                         (0)
#define ISO_PFUNC4_iso_gpio_21_pud_sel_mask                                          (0x00000001)
#define ISO_PFUNC4_iso_gpio_21_pud_sel(data)                                         (0x00000001&((data)<<0))
#define ISO_PFUNC4_iso_gpio_21_pud_sel_src(data)                                     ((0x00000001&(data))>>0)
#define ISO_PFUNC4_get_iso_gpio_21_pud_sel(data)                                     ((0x00000001&(data))>>0)


#define ISO_MUXPAD2                                                                  0x9800731C
#define ISO_MUXPAD2_reg_addr                                                         "0x9800731C"
#define ISO_MUXPAD2_reg                                                              0x9800731C
#define set_ISO_MUXPAD2_reg(data)   (*((volatile unsigned int*) ISO_MUXPAD2_reg)=data)
#define get_ISO_MUXPAD2_reg   (*((volatile unsigned int*) ISO_MUXPAD2_reg))
#define ISO_MUXPAD2_inst_adr                                                         "0x00C7"
#define ISO_MUXPAD2_inst                                                             0x00C7
#define ISO_MUXPAD2_i2c_tg_enable_shift                                              (15)
#define ISO_MUXPAD2_i2c_tg_enable_mask                                               (0x00008000)
#define ISO_MUXPAD2_i2c_tg_enable(data)                                              (0x00008000&((data)<<15))
#define ISO_MUXPAD2_i2c_tg_enable_src(data)                                          ((0x00008000&(data))>>15)
#define ISO_MUXPAD2_get_i2c_tg_enable(data)                                          ((0x00008000&(data))>>15)
#define ISO_MUXPAD2_iso_gpio_34_shift                                                (12)
#define ISO_MUXPAD2_iso_gpio_34_mask                                                 (0x00003000)
#define ISO_MUXPAD2_iso_gpio_34(data)                                                (0x00003000&((data)<<12))
#define ISO_MUXPAD2_iso_gpio_34_src(data)                                            ((0x00003000&(data))>>12)
#define ISO_MUXPAD2_get_iso_gpio_34(data)                                            ((0x00003000&(data))>>12)
#define ISO_MUXPAD2_iso_gpio_33_shift                                                (10)
#define ISO_MUXPAD2_iso_gpio_33_mask                                                 (0x00000C00)
#define ISO_MUXPAD2_iso_gpio_33(data)                                                (0x00000C00&((data)<<10))
#define ISO_MUXPAD2_iso_gpio_33_src(data)                                            ((0x00000C00&(data))>>10)
#define ISO_MUXPAD2_get_iso_gpio_33(data)                                            ((0x00000C00&(data))>>10)
#define ISO_MUXPAD2_iso_gpio_25_shift                                                (8)
#define ISO_MUXPAD2_iso_gpio_25_mask                                                 (0x00000300)
#define ISO_MUXPAD2_iso_gpio_25(data)                                                (0x00000300&((data)<<8))
#define ISO_MUXPAD2_iso_gpio_25_src(data)                                            ((0x00000300&(data))>>8)
#define ISO_MUXPAD2_get_iso_gpio_25(data)                                            ((0x00000300&(data))>>8)
#define ISO_MUXPAD2_iso_gpio_24_shift                                                (6)
#define ISO_MUXPAD2_iso_gpio_24_mask                                                 (0x000000C0)
#define ISO_MUXPAD2_iso_gpio_24(data)                                                (0x000000C0&((data)<<6))
#define ISO_MUXPAD2_iso_gpio_24_src(data)                                            ((0x000000C0&(data))>>6)
#define ISO_MUXPAD2_get_iso_gpio_24(data)                                            ((0x000000C0&(data))>>6)
#define ISO_MUXPAD2_iso_gpio_23_shift                                                (4)
#define ISO_MUXPAD2_iso_gpio_23_mask                                                 (0x00000030)
#define ISO_MUXPAD2_iso_gpio_23(data)                                                (0x00000030&((data)<<4))
#define ISO_MUXPAD2_iso_gpio_23_src(data)                                            ((0x00000030&(data))>>4)
#define ISO_MUXPAD2_get_iso_gpio_23(data)                                            ((0x00000030&(data))>>4)
#define ISO_MUXPAD2_iso_gpio_22_shift                                                (2)
#define ISO_MUXPAD2_iso_gpio_22_mask                                                 (0x0000000C)
#define ISO_MUXPAD2_iso_gpio_22(data)                                                (0x0000000C&((data)<<2))
#define ISO_MUXPAD2_iso_gpio_22_src(data)                                            ((0x0000000C&(data))>>2)
#define ISO_MUXPAD2_get_iso_gpio_22(data)                                            ((0x0000000C&(data))>>2)
#define ISO_MUXPAD2_iso_gpio_21_shift                                                (0)
#define ISO_MUXPAD2_iso_gpio_21_mask                                                 (0x00000003)
#define ISO_MUXPAD2_iso_gpio_21(data)                                                (0x00000003&((data)<<0))
#define ISO_MUXPAD2_iso_gpio_21_src(data)                                            ((0x00000003&(data))>>0)
#define ISO_MUXPAD2_get_iso_gpio_21(data)                                            ((0x00000003&(data))>>0)


#define ISO_PFUNC5                                                                   0x98007320
#define ISO_PFUNC5_reg_addr                                                          "0x98007320"
#define ISO_PFUNC5_reg                                                               0x98007320
#define set_ISO_PFUNC5_reg(data)   (*((volatile unsigned int*) ISO_PFUNC5_reg)=data)
#define get_ISO_PFUNC5_reg   (*((volatile unsigned int*) ISO_PFUNC5_reg))
#define ISO_PFUNC5_inst_adr                                                          "0x00C8"
#define ISO_PFUNC5_inst                                                              0x00C8
#define ISO_PFUNC5_wd_rset_smt_shift                                                 (11)
#define ISO_PFUNC5_wd_rset_smt_mask                                                  (0x00000800)
#define ISO_PFUNC5_wd_rset_smt(data)                                                 (0x00000800&((data)<<11))
#define ISO_PFUNC5_wd_rset_smt_src(data)                                             ((0x00000800&(data))>>11)
#define ISO_PFUNC5_get_wd_rset_smt(data)                                             ((0x00000800&(data))>>11)
#define ISO_PFUNC5_wd_rset_e2_shift                                                  (10)
#define ISO_PFUNC5_wd_rset_e2_mask                                                   (0x00000400)
#define ISO_PFUNC5_wd_rset_e2(data)                                                  (0x00000400&((data)<<10))
#define ISO_PFUNC5_wd_rset_e2_src(data)                                              ((0x00000400&(data))>>10)
#define ISO_PFUNC5_get_wd_rset_e2(data)                                              ((0x00000400&(data))>>10)
#define ISO_PFUNC5_wd_rset_pud_en_shift                                              (9)
#define ISO_PFUNC5_wd_rset_pud_en_mask                                               (0x00000200)
#define ISO_PFUNC5_wd_rset_pud_en(data)                                              (0x00000200&((data)<<9))
#define ISO_PFUNC5_wd_rset_pud_en_src(data)                                          ((0x00000200&(data))>>9)
#define ISO_PFUNC5_get_wd_rset_pud_en(data)                                          ((0x00000200&(data))>>9)
#define ISO_PFUNC5_wd_rset_pud_sel_shift                                             (8)
#define ISO_PFUNC5_wd_rset_pud_sel_mask                                              (0x00000100)
#define ISO_PFUNC5_wd_rset_pud_sel(data)                                             (0x00000100&((data)<<8))
#define ISO_PFUNC5_wd_rset_pud_sel_src(data)                                         ((0x00000100&(data))>>8)
#define ISO_PFUNC5_get_wd_rset_pud_sel(data)                                         ((0x00000100&(data))>>8)
#define ISO_PFUNC5_iso_gpio_34_smt_shift                                             (7)
#define ISO_PFUNC5_iso_gpio_34_smt_mask                                              (0x00000080)
#define ISO_PFUNC5_iso_gpio_34_smt(data)                                             (0x00000080&((data)<<7))
#define ISO_PFUNC5_iso_gpio_34_smt_src(data)                                         ((0x00000080&(data))>>7)
#define ISO_PFUNC5_get_iso_gpio_34_smt(data)                                         ((0x00000080&(data))>>7)
#define ISO_PFUNC5_iso_gpio_34_e2_shift                                              (6)
#define ISO_PFUNC5_iso_gpio_34_e2_mask                                               (0x00000040)
#define ISO_PFUNC5_iso_gpio_34_e2(data)                                              (0x00000040&((data)<<6))
#define ISO_PFUNC5_iso_gpio_34_e2_src(data)                                          ((0x00000040&(data))>>6)
#define ISO_PFUNC5_get_iso_gpio_34_e2(data)                                          ((0x00000040&(data))>>6)
#define ISO_PFUNC5_iso_gpio_34_pud_en_shift                                          (5)
#define ISO_PFUNC5_iso_gpio_34_pud_en_mask                                           (0x00000020)
#define ISO_PFUNC5_iso_gpio_34_pud_en(data)                                          (0x00000020&((data)<<5))
#define ISO_PFUNC5_iso_gpio_34_pud_en_src(data)                                      ((0x00000020&(data))>>5)
#define ISO_PFUNC5_get_iso_gpio_34_pud_en(data)                                      ((0x00000020&(data))>>5)
#define ISO_PFUNC5_iso_gpio_34_pud_sel_shift                                         (4)
#define ISO_PFUNC5_iso_gpio_34_pud_sel_mask                                          (0x00000010)
#define ISO_PFUNC5_iso_gpio_34_pud_sel(data)                                         (0x00000010&((data)<<4))
#define ISO_PFUNC5_iso_gpio_34_pud_sel_src(data)                                     ((0x00000010&(data))>>4)
#define ISO_PFUNC5_get_iso_gpio_34_pud_sel(data)                                     ((0x00000010&(data))>>4)
#define ISO_PFUNC5_iso_gpio_33_smt_shift                                             (3)
#define ISO_PFUNC5_iso_gpio_33_smt_mask                                              (0x00000008)
#define ISO_PFUNC5_iso_gpio_33_smt(data)                                             (0x00000008&((data)<<3))
#define ISO_PFUNC5_iso_gpio_33_smt_src(data)                                         ((0x00000008&(data))>>3)
#define ISO_PFUNC5_get_iso_gpio_33_smt(data)                                         ((0x00000008&(data))>>3)
#define ISO_PFUNC5_iso_gpio_33_e2_shift                                              (2)
#define ISO_PFUNC5_iso_gpio_33_e2_mask                                               (0x00000004)
#define ISO_PFUNC5_iso_gpio_33_e2(data)                                              (0x00000004&((data)<<2))
#define ISO_PFUNC5_iso_gpio_33_e2_src(data)                                          ((0x00000004&(data))>>2)
#define ISO_PFUNC5_get_iso_gpio_33_e2(data)                                          ((0x00000004&(data))>>2)
#define ISO_PFUNC5_iso_gpio_33_pud_en_shift                                          (1)
#define ISO_PFUNC5_iso_gpio_33_pud_en_mask                                           (0x00000002)
#define ISO_PFUNC5_iso_gpio_33_pud_en(data)                                          (0x00000002&((data)<<1))
#define ISO_PFUNC5_iso_gpio_33_pud_en_src(data)                                      ((0x00000002&(data))>>1)
#define ISO_PFUNC5_get_iso_gpio_33_pud_en(data)                                      ((0x00000002&(data))>>1)
#define ISO_PFUNC5_iso_gpio_33_pud_sel_shift                                         (0)
#define ISO_PFUNC5_iso_gpio_33_pud_sel_mask                                          (0x00000001)
#define ISO_PFUNC5_iso_gpio_33_pud_sel(data)                                         (0x00000001&((data)<<0))
#define ISO_PFUNC5_iso_gpio_33_pud_sel_src(data)                                     ((0x00000001&(data))>>0)
#define ISO_PFUNC5_get_iso_gpio_33_pud_sel(data)                                     ((0x00000001&(data))>>0)


#define ISO_IR_PSR                                                                   0x98007400
#define ISO_IR_PSR_reg_addr                                                          "0x98007400"
#define ISO_IR_PSR_reg                                                               0x98007400
#define set_ISO_IR_PSR_reg(data)   (*((volatile unsigned int*) ISO_IR_PSR_reg)=data)
#define get_ISO_IR_PSR_reg   (*((volatile unsigned int*) ISO_IR_PSR_reg))
#define ISO_IR_PSR_inst_adr                                                          "0x0000"
#define ISO_IR_PSR_inst                                                              0x0000
#define ISO_IR_PSR_irrbl_shift                                                       (24)
#define ISO_IR_PSR_irrbl_mask                                                        (0xFF000000)
#define ISO_IR_PSR_irrbl(data)                                                       (0xFF000000&((data)<<24))
#define ISO_IR_PSR_irrbl_src(data)                                                   ((0xFF000000&(data))>>24)
#define ISO_IR_PSR_get_irrbl(data)                                                   ((0xFF000000&(data))>>24)
#define ISO_IR_PSR_irrml_shift                                                       (16)
#define ISO_IR_PSR_irrml_mask                                                        (0x00FF0000)
#define ISO_IR_PSR_irrml(data)                                                       (0x00FF0000&((data)<<16))
#define ISO_IR_PSR_irrml_src(data)                                                   ((0x00FF0000&(data))>>16)
#define ISO_IR_PSR_get_irrml(data)                                                   ((0x00FF0000&(data))>>16)
#define ISO_IR_PSR_irrdzl_shift                                                      (8)
#define ISO_IR_PSR_irrdzl_mask                                                       (0x0000FF00)
#define ISO_IR_PSR_irrdzl(data)                                                      (0x0000FF00&((data)<<8))
#define ISO_IR_PSR_irrdzl_src(data)                                                  ((0x0000FF00&(data))>>8)
#define ISO_IR_PSR_get_irrdzl(data)                                                  ((0x0000FF00&(data))>>8)
#define ISO_IR_PSR_irrdol_shift                                                      (0)
#define ISO_IR_PSR_irrdol_mask                                                       (0x000000FF)
#define ISO_IR_PSR_irrdol(data)                                                      (0x000000FF&((data)<<0))
#define ISO_IR_PSR_irrdol_src(data)                                                  ((0x000000FF&(data))>>0)
#define ISO_IR_PSR_get_irrdol(data)                                                  ((0x000000FF&(data))>>0)


#define ISO_IR_PER                                                                   0x98007404
#define ISO_IR_PER_reg_addr                                                          "0x98007404"
#define ISO_IR_PER_reg                                                               0x98007404
#define set_ISO_IR_PER_reg(data)   (*((volatile unsigned int*) ISO_IR_PER_reg)=data)
#define get_ISO_IR_PER_reg   (*((volatile unsigned int*) ISO_IR_PER_reg))
#define ISO_IR_PER_inst_adr                                                          "0x0001"
#define ISO_IR_PER_inst                                                              0x0001
#define ISO_IR_PER_irrdl_shift                                                       (16)
#define ISO_IR_PER_irrdl_mask                                                        (0x003F0000)
#define ISO_IR_PER_irrdl(data)                                                       (0x003F0000&((data)<<16))
#define ISO_IR_PER_irrdl_src(data)                                                   ((0x003F0000&(data))>>16)
#define ISO_IR_PER_get_irrdl(data)                                                   ((0x003F0000&(data))>>16)
#define ISO_IR_PER_irrrl_shift                                                       (8)
#define ISO_IR_PER_irrrl_mask                                                        (0x0000FF00)
#define ISO_IR_PER_irrrl(data)                                                       (0x0000FF00&((data)<<8))
#define ISO_IR_PER_irrrl_src(data)                                                   ((0x0000FF00&(data))>>8)
#define ISO_IR_PER_get_irrrl(data)                                                   ((0x0000FF00&(data))>>8)
#define ISO_IR_PER_irrsl_shift                                                       (0)
#define ISO_IR_PER_irrsl_mask                                                        (0x000000FF)
#define ISO_IR_PER_irrsl(data)                                                       (0x000000FF&((data)<<0))
#define ISO_IR_PER_irrsl_src(data)                                                   ((0x000000FF&(data))>>0)
#define ISO_IR_PER_get_irrsl(data)                                                   ((0x000000FF&(data))>>0)


#define ISO_IR_SF                                                                    0x98007408
#define ISO_IR_SF_reg_addr                                                           "0x98007408"
#define ISO_IR_SF_reg                                                                0x98007408
#define set_ISO_IR_SF_reg(data)   (*((volatile unsigned int*) ISO_IR_SF_reg)=data)
#define get_ISO_IR_SF_reg   (*((volatile unsigned int*) ISO_IR_SF_reg))
#define ISO_IR_SF_inst_adr                                                           "0x0002"
#define ISO_IR_SF_inst                                                               0x0002
#define ISO_IR_SF_irfd_shift                                                         (0)
#define ISO_IR_SF_irfd_mask                                                          (0x0000FFFF)
#define ISO_IR_SF_irfd(data)                                                         (0x0000FFFF&((data)<<0))
#define ISO_IR_SF_irfd_src(data)                                                     ((0x0000FFFF&(data))>>0)
#define ISO_IR_SF_get_irfd(data)                                                     ((0x0000FFFF&(data))>>0)


#define ISO_IR_DPIR                                                                  0x9800740C
#define ISO_IR_DPIR_reg_addr                                                         "0x9800740C"
#define ISO_IR_DPIR_reg                                                              0x9800740C
#define set_ISO_IR_DPIR_reg(data)   (*((volatile unsigned int*) ISO_IR_DPIR_reg)=data)
#define get_ISO_IR_DPIR_reg   (*((volatile unsigned int*) ISO_IR_DPIR_reg))
#define ISO_IR_DPIR_inst_adr                                                         "0x0003"
#define ISO_IR_DPIR_inst                                                             0x0003
#define ISO_IR_DPIR_iriotcdp_shift                                                   (0)
#define ISO_IR_DPIR_iriotcdp_mask                                                    (0x0000FFFF)
#define ISO_IR_DPIR_iriotcdp(data)                                                   (0x0000FFFF&((data)<<0))
#define ISO_IR_DPIR_iriotcdp_src(data)                                               ((0x0000FFFF&(data))>>0)
#define ISO_IR_DPIR_get_iriotcdp(data)                                               ((0x0000FFFF&(data))>>0)


#define ISO_IR_CR                                                                    0x98007410
#define ISO_IR_CR_reg_addr                                                           "0x98007410"
#define ISO_IR_CR_reg                                                                0x98007410
#define set_ISO_IR_CR_reg(data)   (*((volatile unsigned int*) ISO_IR_CR_reg)=data)
#define get_ISO_IR_CR_reg   (*((volatile unsigned int*) ISO_IR_CR_reg))
#define ISO_IR_CR_inst_adr                                                           "0x0004"
#define ISO_IR_CR_inst                                                               0x0004
#define ISO_IR_CR_irsr_shift                                                         (31)
#define ISO_IR_CR_irsr_mask                                                          (0x80000000)
#define ISO_IR_CR_irsr(data)                                                         (0x80000000&((data)<<31))
#define ISO_IR_CR_irsr_src(data)                                                     ((0x80000000&(data))>>31)
#define ISO_IR_CR_get_irsr(data)                                                     ((0x80000000&(data))>>31)
#define ISO_IR_CR_rcmm_en_shift                                                      (25)
#define ISO_IR_CR_rcmm_en_mask                                                       (0x02000000)
#define ISO_IR_CR_rcmm_en(data)                                                      (0x02000000&((data)<<25))
#define ISO_IR_CR_rcmm_en_src(data)                                                  ((0x02000000&(data))>>25)
#define ISO_IR_CR_get_rcmm_en(data)                                                  ((0x02000000&(data))>>25)
#define ISO_IR_CR_toshiba_en_shift                                                   (24)
#define ISO_IR_CR_toshiba_en_mask                                                    (0x01000000)
#define ISO_IR_CR_toshiba_en(data)                                                   (0x01000000&((data)<<24))
#define ISO_IR_CR_toshiba_en_src(data)                                               ((0x01000000&(data))>>24)
#define ISO_IR_CR_get_toshiba_en(data)                                               ((0x01000000&(data))>>24)
#define ISO_IR_CR_irednm_shift                                                       (23)
#define ISO_IR_CR_irednm_mask                                                        (0x00800000)
#define ISO_IR_CR_irednm(data)                                                       (0x00800000&((data)<<23))
#define ISO_IR_CR_irednm_src(data)                                                   ((0x00800000&(data))>>23)
#define ISO_IR_CR_get_irednm(data)                                                   ((0x00800000&(data))>>23)
#define ISO_IR_CR_iredn_shift                                                        (16)
#define ISO_IR_CR_iredn_mask                                                         (0x003F0000)
#define ISO_IR_CR_iredn(data)                                                        (0x003F0000&((data)<<16))
#define ISO_IR_CR_iredn_src(data)                                                    ((0x003F0000&(data))>>16)
#define ISO_IR_CR_get_iredn(data)                                                    ((0x003F0000&(data))>>16)
#define ISO_IR_CR_raw_fifo_ov_shift                                                  (14)
#define ISO_IR_CR_raw_fifo_ov_mask                                                   (0x00004000)
#define ISO_IR_CR_raw_fifo_ov(data)                                                  (0x00004000&((data)<<14))
#define ISO_IR_CR_raw_fifo_ov_src(data)                                              ((0x00004000&(data))>>14)
#define ISO_IR_CR_get_raw_fifo_ov(data)                                              ((0x00004000&(data))>>14)
#define ISO_IR_CR_raw_fifo_val_shift                                                 (13)
#define ISO_IR_CR_raw_fifo_val_mask                                                  (0x00002000)
#define ISO_IR_CR_raw_fifo_val(data)                                                 (0x00002000&((data)<<13))
#define ISO_IR_CR_raw_fifo_val_src(data)                                             ((0x00002000&(data))>>13)
#define ISO_IR_CR_get_raw_fifo_val(data)                                             ((0x00002000&(data))>>13)
#define ISO_IR_CR_raw_en_shift                                                       (12)
#define ISO_IR_CR_raw_en_mask                                                        (0x00001000)
#define ISO_IR_CR_raw_en(data)                                                       (0x00001000&((data)<<12))
#define ISO_IR_CR_raw_en_src(data)                                                   ((0x00001000&(data))>>12)
#define ISO_IR_CR_get_raw_en(data)                                                   ((0x00001000&(data))>>12)
#define ISO_IR_CR_mlae_shift                                                         (11)
#define ISO_IR_CR_mlae_mask                                                          (0x00000800)
#define ISO_IR_CR_mlae(data)                                                         (0x00000800&((data)<<11))
#define ISO_IR_CR_mlae_src(data)                                                     ((0x00000800&(data))>>11)
#define ISO_IR_CR_get_mlae(data)                                                     ((0x00000800&(data))>>11)
#define ISO_IR_CR_irie_shift                                                         (10)
#define ISO_IR_CR_irie_mask                                                          (0x00000400)
#define ISO_IR_CR_irie(data)                                                         (0x00000400&((data)<<10))
#define ISO_IR_CR_irie_src(data)                                                     ((0x00000400&(data))>>10)
#define ISO_IR_CR_get_irie(data)                                                     ((0x00000400&(data))>>10)
#define ISO_IR_CR_irres_shift                                                        (9)
#define ISO_IR_CR_irres_mask                                                         (0x00000200)
#define ISO_IR_CR_irres(data)                                                        (0x00000200&((data)<<9))
#define ISO_IR_CR_irres_src(data)                                                    ((0x00000200&(data))>>9)
#define ISO_IR_CR_get_irres(data)                                                    ((0x00000200&(data))>>9)
#define ISO_IR_CR_irue_shift                                                         (8)
#define ISO_IR_CR_irue_mask                                                          (0x00000100)
#define ISO_IR_CR_irue(data)                                                         (0x00000100&((data)<<8))
#define ISO_IR_CR_irue_src(data)                                                     ((0x00000100&(data))>>8)
#define ISO_IR_CR_get_irue(data)                                                     ((0x00000100&(data))>>8)
#define ISO_IR_CR_ircm_shift                                                         (7)
#define ISO_IR_CR_ircm_mask                                                          (0x00000080)
#define ISO_IR_CR_ircm(data)                                                         (0x00000080&((data)<<7))
#define ISO_IR_CR_ircm_src(data)                                                     ((0x00000080&(data))>>7)
#define ISO_IR_CR_get_ircm(data)                                                     ((0x00000080&(data))>>7)
#define ISO_IR_CR_irbme_shift                                                        (6)
#define ISO_IR_CR_irbme_mask                                                         (0x00000040)
#define ISO_IR_CR_irbme(data)                                                        (0x00000040&((data)<<6))
#define ISO_IR_CR_irbme_src(data)                                                    ((0x00000040&(data))>>6)
#define ISO_IR_CR_get_irbme(data)                                                    ((0x00000040&(data))>>6)
#define ISO_IR_CR_irdpm_shift                                                        (5)
#define ISO_IR_CR_irdpm_mask                                                         (0x00000020)
#define ISO_IR_CR_irdpm(data)                                                        (0x00000020&((data)<<5))
#define ISO_IR_CR_irdpm_src(data)                                                    ((0x00000020&(data))>>5)
#define ISO_IR_CR_get_irdpm(data)                                                    ((0x00000020&(data))>>5)
#define ISO_IR_CR_irdn_shift                                                         (0)
#define ISO_IR_CR_irdn_mask                                                          (0x0000001F)
#define ISO_IR_CR_irdn(data)                                                         (0x0000001F&((data)<<0))
#define ISO_IR_CR_irdn_src(data)                                                     ((0x0000001F&(data))>>0)
#define ISO_IR_CR_get_irdn(data)                                                     ((0x0000001F&(data))>>0)


#define ISO_IR_RP                                                                    0x98007414
#define ISO_IR_RP_reg_addr                                                           "0x98007414"
#define ISO_IR_RP_reg                                                                0x98007414
#define set_ISO_IR_RP_reg(data)   (*((volatile unsigned int*) ISO_IR_RP_reg)=data)
#define get_ISO_IR_RP_reg   (*((volatile unsigned int*) ISO_IR_RP_reg))
#define ISO_IR_RP_inst_adr                                                           "0x0005"
#define ISO_IR_RP_inst                                                               0x0005
#define ISO_IR_RP_irrp_shift                                                         (0)
#define ISO_IR_RP_irrp_mask                                                          (0xFFFFFFFF)
#define ISO_IR_RP_irrp(data)                                                         (0xFFFFFFFF&((data)<<0))
#define ISO_IR_RP_irrp_src(data)                                                     ((0xFFFFFFFF&(data))>>0)
#define ISO_IR_RP_get_irrp(data)                                                     ((0xFFFFFFFF&(data))>>0)


#define ISO_IR_SR                                                                    0x98007418
#define ISO_IR_SR_reg_addr                                                           "0x98007418"
#define ISO_IR_SR_reg                                                                0x98007418
#define set_ISO_IR_SR_reg(data)   (*((volatile unsigned int*) ISO_IR_SR_reg)=data)
#define get_ISO_IR_SR_reg   (*((volatile unsigned int*) ISO_IR_SR_reg))
#define ISO_IR_SR_inst_adr                                                           "0x0006"
#define ISO_IR_SR_inst                                                               0x0006
#define ISO_IR_SR_slen_big_shift                                                     (5)
#define ISO_IR_SR_slen_big_mask                                                      (0x00000020)
#define ISO_IR_SR_slen_big(data)                                                     (0x00000020&((data)<<5))
#define ISO_IR_SR_slen_big_src(data)                                                 ((0x00000020&(data))>>5)
#define ISO_IR_SR_get_slen_big(data)                                                 ((0x00000020&(data))>>5)
#define ISO_IR_SR_blen_big_shift                                                     (4)
#define ISO_IR_SR_blen_big_mask                                                      (0x00000010)
#define ISO_IR_SR_blen_big(data)                                                     (0x00000010&((data)<<4))
#define ISO_IR_SR_blen_big_src(data)                                                 ((0x00000010&(data))>>4)
#define ISO_IR_SR_get_blen_big(data)                                                 ((0x00000010&(data))>>4)
#define ISO_IR_SR_raw_fifo_ov_shift                                                  (3)
#define ISO_IR_SR_raw_fifo_ov_mask                                                   (0x00000008)
#define ISO_IR_SR_raw_fifo_ov(data)                                                  (0x00000008&((data)<<3))
#define ISO_IR_SR_raw_fifo_ov_src(data)                                              ((0x00000008&(data))>>3)
#define ISO_IR_SR_get_raw_fifo_ov(data)                                              ((0x00000008&(data))>>3)
#define ISO_IR_SR_raw_fifo_val_shift                                                 (2)
#define ISO_IR_SR_raw_fifo_val_mask                                                  (0x00000004)
#define ISO_IR_SR_raw_fifo_val(data)                                                 (0x00000004&((data)<<2))
#define ISO_IR_SR_raw_fifo_val_src(data)                                             ((0x00000004&(data))>>2)
#define ISO_IR_SR_get_raw_fifo_val(data)                                             ((0x00000004&(data))>>2)
#define ISO_IR_SR_irrf_shift                                                         (1)
#define ISO_IR_SR_irrf_mask                                                          (0x00000002)
#define ISO_IR_SR_irrf(data)                                                         (0x00000002&((data)<<1))
#define ISO_IR_SR_irrf_src(data)                                                     ((0x00000002&(data))>>1)
#define ISO_IR_SR_get_irrf(data)                                                     ((0x00000002&(data))>>1)
#define ISO_IR_SR_irdvf_shift                                                        (0)
#define ISO_IR_SR_irdvf_mask                                                         (0x00000001)
#define ISO_IR_SR_irdvf(data)                                                        (0x00000001&((data)<<0))
#define ISO_IR_SR_irdvf_src(data)                                                    ((0x00000001&(data))>>0)
#define ISO_IR_SR_get_irdvf(data)                                                    ((0x00000001&(data))>>0)


#define ISO_IR_RAW_CTRL                                                              0x9800741C
#define ISO_IR_RAW_CTRL_reg_addr                                                     "0x9800741C"
#define ISO_IR_RAW_CTRL_reg                                                          0x9800741C
#define set_ISO_IR_RAW_CTRL_reg(data)   (*((volatile unsigned int*) ISO_IR_RAW_CTRL_reg)=data)
#define get_ISO_IR_RAW_CTRL_reg   (*((volatile unsigned int*) ISO_IR_RAW_CTRL_reg))
#define ISO_IR_RAW_CTRL_inst_adr                                                     "0x0007"
#define ISO_IR_RAW_CTRL_inst                                                         0x0007
#define ISO_IR_RAW_CTRL_write_en2_shift                                              (25)
#define ISO_IR_RAW_CTRL_write_en2_mask                                               (0x02000000)
#define ISO_IR_RAW_CTRL_write_en2(data)                                              (0x02000000&((data)<<25))
#define ISO_IR_RAW_CTRL_write_en2_src(data)                                          ((0x02000000&(data))>>25)
#define ISO_IR_RAW_CTRL_get_write_en2(data)                                          ((0x02000000&(data))>>25)
#define ISO_IR_RAW_CTRL_stop_sample_shift                                            (24)
#define ISO_IR_RAW_CTRL_stop_sample_mask                                             (0x01000000)
#define ISO_IR_RAW_CTRL_stop_sample(data)                                            (0x01000000&((data)<<24))
#define ISO_IR_RAW_CTRL_stop_sample_src(data)                                        ((0x01000000&(data))>>24)
#define ISO_IR_RAW_CTRL_get_stop_sample(data)                                        ((0x01000000&(data))>>24)
#define ISO_IR_RAW_CTRL_stop_time_shift                                              (8)
#define ISO_IR_RAW_CTRL_stop_time_mask                                               (0x00FFFF00)
#define ISO_IR_RAW_CTRL_stop_time(data)                                              (0x00FFFF00&((data)<<8))
#define ISO_IR_RAW_CTRL_stop_time_src(data)                                          ((0x00FFFF00&(data))>>8)
#define ISO_IR_RAW_CTRL_get_stop_time(data)                                          ((0x00FFFF00&(data))>>8)
#define ISO_IR_RAW_CTRL_write_en1_shift                                              (6)
#define ISO_IR_RAW_CTRL_write_en1_mask                                               (0x00000040)
#define ISO_IR_RAW_CTRL_write_en1(data)                                              (0x00000040&((data)<<6))
#define ISO_IR_RAW_CTRL_write_en1_src(data)                                          ((0x00000040&(data))>>6)
#define ISO_IR_RAW_CTRL_get_write_en1(data)                                          ((0x00000040&(data))>>6)
#define ISO_IR_RAW_CTRL_fifo_thr_shift                                               (0)
#define ISO_IR_RAW_CTRL_fifo_thr_mask                                                (0x0000003F)
#define ISO_IR_RAW_CTRL_fifo_thr(data)                                               (0x0000003F&((data)<<0))
#define ISO_IR_RAW_CTRL_fifo_thr_src(data)                                           ((0x0000003F&(data))>>0)
#define ISO_IR_RAW_CTRL_get_fifo_thr(data)                                           ((0x0000003F&(data))>>0)


#define ISO_IR_RAW_FF                                                                0x98007420
#define ISO_IR_RAW_FF_reg_addr                                                       "0x98007420"
#define ISO_IR_RAW_FF_reg                                                            0x98007420
#define set_ISO_IR_RAW_FF_reg(data)   (*((volatile unsigned int*) ISO_IR_RAW_FF_reg)=data)
#define get_ISO_IR_RAW_FF_reg   (*((volatile unsigned int*) ISO_IR_RAW_FF_reg))
#define ISO_IR_RAW_FF_inst_adr                                                       "0x0008"
#define ISO_IR_RAW_FF_inst                                                           0x0008
#define ISO_IR_RAW_FF_dat_shift                                                      (0)
#define ISO_IR_RAW_FF_dat_mask                                                       (0xFFFFFFFF)
#define ISO_IR_RAW_FF_dat(data)                                                      (0xFFFFFFFF&((data)<<0))
#define ISO_IR_RAW_FF_dat_src(data)                                                  ((0xFFFFFFFF&(data))>>0)
#define ISO_IR_RAW_FF_get_dat(data)                                                  ((0xFFFFFFFF&(data))>>0)


#define ISO_IR_RAW_SAMPLE_TIME                                                       0x98007424
#define ISO_IR_RAW_SAMPLE_TIME_reg_addr                                              "0x98007424"
#define ISO_IR_RAW_SAMPLE_TIME_reg                                                   0x98007424
#define set_ISO_IR_RAW_SAMPLE_TIME_reg(data)   (*((volatile unsigned int*) ISO_IR_RAW_SAMPLE_TIME_reg)=data)
#define get_ISO_IR_RAW_SAMPLE_TIME_reg   (*((volatile unsigned int*) ISO_IR_RAW_SAMPLE_TIME_reg))
#define ISO_IR_RAW_SAMPLE_TIME_inst_adr                                              "0x0009"
#define ISO_IR_RAW_SAMPLE_TIME_inst                                                  0x0009
#define ISO_IR_RAW_SAMPLE_TIME_cnt_shift                                             (0)
#define ISO_IR_RAW_SAMPLE_TIME_cnt_mask                                              (0x0000FFFF)
#define ISO_IR_RAW_SAMPLE_TIME_cnt(data)                                             (0x0000FFFF&((data)<<0))
#define ISO_IR_RAW_SAMPLE_TIME_cnt_src(data)                                         ((0x0000FFFF&(data))>>0)
#define ISO_IR_RAW_SAMPLE_TIME_get_cnt(data)                                         ((0x0000FFFF&(data))>>0)


#define ISO_IR_RAW_WL                                                                0x98007428
#define ISO_IR_RAW_WL_reg_addr                                                       "0x98007428"
#define ISO_IR_RAW_WL_reg                                                            0x98007428
#define set_ISO_IR_RAW_WL_reg(data)   (*((volatile unsigned int*) ISO_IR_RAW_WL_reg)=data)
#define get_ISO_IR_RAW_WL_reg   (*((volatile unsigned int*) ISO_IR_RAW_WL_reg))
#define ISO_IR_RAW_WL_inst_adr                                                       "0x000A"
#define ISO_IR_RAW_WL_inst                                                           0x000A
#define ISO_IR_RAW_WL_val_shift                                                      (0)
#define ISO_IR_RAW_WL_val_mask                                                       (0x0000003F)
#define ISO_IR_RAW_WL_val(data)                                                      (0x0000003F&((data)<<0))
#define ISO_IR_RAW_WL_val_src(data)                                                  ((0x0000003F&(data))>>0)
#define ISO_IR_RAW_WL_get_val(data)                                                  ((0x0000003F&(data))>>0)


#define ISO_IR_RAW_DEB                                                               0x9800742C
#define ISO_IR_RAW_DEB_reg_addr                                                      "0x9800742C"
#define ISO_IR_RAW_DEB_reg                                                           0x9800742C
#define set_ISO_IR_RAW_DEB_reg(data)   (*((volatile unsigned int*) ISO_IR_RAW_DEB_reg)=data)
#define get_ISO_IR_RAW_DEB_reg   (*((volatile unsigned int*) ISO_IR_RAW_DEB_reg))
#define ISO_IR_RAW_DEB_inst_adr                                                      "0x000B"
#define ISO_IR_RAW_DEB_inst                                                          0x000B
#define ISO_IR_RAW_DEB_len_shift                                                     (16)
#define ISO_IR_RAW_DEB_len_mask                                                      (0x00FF0000)
#define ISO_IR_RAW_DEB_len(data)                                                     (0x00FF0000&((data)<<16))
#define ISO_IR_RAW_DEB_len_src(data)                                                 ((0x00FF0000&(data))>>16)
#define ISO_IR_RAW_DEB_get_len(data)                                                 ((0x00FF0000&(data))>>16)
#define ISO_IR_RAW_DEB_clk_shift                                                     (0)
#define ISO_IR_RAW_DEB_clk_mask                                                      (0x0000FFFF)
#define ISO_IR_RAW_DEB_clk(data)                                                     (0x0000FFFF&((data)<<0))
#define ISO_IR_RAW_DEB_clk_src(data)                                                 ((0x0000FFFF&(data))>>0)
#define ISO_IR_RAW_DEB_get_clk(data)                                                 ((0x0000FFFF&(data))>>0)


#define ISO_IR_PSR_UP                                                                0x98007430
#define ISO_IR_PSR_UP_reg_addr                                                       "0x98007430"
#define ISO_IR_PSR_UP_reg                                                            0x98007430
#define set_ISO_IR_PSR_UP_reg(data)   (*((volatile unsigned int*) ISO_IR_PSR_UP_reg)=data)
#define get_ISO_IR_PSR_UP_reg   (*((volatile unsigned int*) ISO_IR_PSR_UP_reg))
#define ISO_IR_PSR_UP_inst_adr                                                       "0x000C"
#define ISO_IR_PSR_UP_inst                                                           0x000C
#define ISO_IR_PSR_UP_irrbl_shift                                                    (24)
#define ISO_IR_PSR_UP_irrbl_mask                                                     (0xFF000000)
#define ISO_IR_PSR_UP_irrbl(data)                                                    (0xFF000000&((data)<<24))
#define ISO_IR_PSR_UP_irrbl_src(data)                                                ((0xFF000000&(data))>>24)
#define ISO_IR_PSR_UP_get_irrbl(data)                                                ((0xFF000000&(data))>>24)
#define ISO_IR_PSR_UP_irrml_shift                                                    (16)
#define ISO_IR_PSR_UP_irrml_mask                                                     (0x00FF0000)
#define ISO_IR_PSR_UP_irrml(data)                                                    (0x00FF0000&((data)<<16))
#define ISO_IR_PSR_UP_irrml_src(data)                                                ((0x00FF0000&(data))>>16)
#define ISO_IR_PSR_UP_get_irrml(data)                                                ((0x00FF0000&(data))>>16)
#define ISO_IR_PSR_UP_irrdzl_shift                                                   (8)
#define ISO_IR_PSR_UP_irrdzl_mask                                                    (0x0000FF00)
#define ISO_IR_PSR_UP_irrdzl(data)                                                   (0x0000FF00&((data)<<8))
#define ISO_IR_PSR_UP_irrdzl_src(data)                                               ((0x0000FF00&(data))>>8)
#define ISO_IR_PSR_UP_get_irrdzl(data)                                               ((0x0000FF00&(data))>>8)
#define ISO_IR_PSR_UP_irrdol_shift                                                   (0)
#define ISO_IR_PSR_UP_irrdol_mask                                                    (0x000000FF)
#define ISO_IR_PSR_UP_irrdol(data)                                                   (0x000000FF&((data)<<0))
#define ISO_IR_PSR_UP_irrdol_src(data)                                               ((0x000000FF&(data))>>0)
#define ISO_IR_PSR_UP_get_irrdol(data)                                               ((0x000000FF&(data))>>0)


#define ISO_IR_PER_UP                                                                0x98007434
#define ISO_IR_PER_UP_reg_addr                                                       "0x98007434"
#define ISO_IR_PER_UP_reg                                                            0x98007434
#define set_ISO_IR_PER_UP_reg(data)   (*((volatile unsigned int*) ISO_IR_PER_UP_reg)=data)
#define get_ISO_IR_PER_UP_reg   (*((volatile unsigned int*) ISO_IR_PER_UP_reg))
#define ISO_IR_PER_UP_inst_adr                                                       "0x000D"
#define ISO_IR_PER_UP_inst                                                           0x000D
#define ISO_IR_PER_UP_irrrl_shift                                                    (8)
#define ISO_IR_PER_UP_irrrl_mask                                                     (0x0000FF00)
#define ISO_IR_PER_UP_irrrl(data)                                                    (0x0000FF00&((data)<<8))
#define ISO_IR_PER_UP_irrrl_src(data)                                                ((0x0000FF00&(data))>>8)
#define ISO_IR_PER_UP_get_irrrl(data)                                                ((0x0000FF00&(data))>>8)
#define ISO_IR_PER_UP_irrsl_shift                                                    (0)
#define ISO_IR_PER_UP_irrsl_mask                                                     (0x000000FF)
#define ISO_IR_PER_UP_irrsl(data)                                                    (0x000000FF&((data)<<0))
#define ISO_IR_PER_UP_irrsl_src(data)                                                ((0x000000FF&(data))>>0)
#define ISO_IR_PER_UP_get_irrsl(data)                                                ((0x000000FF&(data))>>0)


#define ISO_IR_CTRL_RC6                                                              0x98007438
#define ISO_IR_CTRL_RC6_reg_addr                                                     "0x98007438"
#define ISO_IR_CTRL_RC6_reg                                                          0x98007438
#define set_ISO_IR_CTRL_RC6_reg(data)   (*((volatile unsigned int*) ISO_IR_CTRL_RC6_reg)=data)
#define get_ISO_IR_CTRL_RC6_reg   (*((volatile unsigned int*) ISO_IR_CTRL_RC6_reg))
#define ISO_IR_CTRL_RC6_inst_adr                                                     "0x000E"
#define ISO_IR_CTRL_RC6_inst                                                         0x000E
#define ISO_IR_CTRL_RC6_rc6_en_shift                                                 (8)
#define ISO_IR_CTRL_RC6_rc6_en_mask                                                  (0x00000100)
#define ISO_IR_CTRL_RC6_rc6_en(data)                                                 (0x00000100&((data)<<8))
#define ISO_IR_CTRL_RC6_rc6_en_src(data)                                             ((0x00000100&(data))>>8)
#define ISO_IR_CTRL_RC6_get_rc6_en(data)                                             ((0x00000100&(data))>>8)
#define ISO_IR_CTRL_RC6_irtr_shift                                                   (0)
#define ISO_IR_CTRL_RC6_irtr_mask                                                    (0x000000FF)
#define ISO_IR_CTRL_RC6_irtr(data)                                                   (0x000000FF&((data)<<0))
#define ISO_IR_CTRL_RC6_irtr_src(data)                                               ((0x000000FF&(data))>>0)
#define ISO_IR_CTRL_RC6_get_irtr(data)                                               ((0x000000FF&(data))>>0)


#define ISO_IR_RP2                                                                   0x9800743C
#define ISO_IR_RP2_reg_addr                                                          "0x9800743C"
#define ISO_IR_RP2_reg                                                               0x9800743C
#define set_ISO_IR_RP2_reg(data)   (*((volatile unsigned int*) ISO_IR_RP2_reg)=data)
#define get_ISO_IR_RP2_reg   (*((volatile unsigned int*) ISO_IR_RP2_reg))
#define ISO_IR_RP2_inst_adr                                                          "0x000F"
#define ISO_IR_RP2_inst                                                              0x000F
#define ISO_IR_RP2_irrp_shift                                                        (0)
#define ISO_IR_RP2_irrp_mask                                                         (0xFFFFFFFF)
#define ISO_IR_RP2_irrp(data)                                                        (0xFFFFFFFF&((data)<<0))
#define ISO_IR_RP2_irrp_src(data)                                                    ((0xFFFFFFFF&(data))>>0)
#define ISO_IR_RP2_get_irrp(data)                                                    ((0xFFFFFFFF&(data))>>0)


#define ISO_IRTX_CFG                                                                 0x98007440
#define ISO_IRTX_CFG_reg_addr                                                        "0x98007440"
#define ISO_IRTX_CFG_reg                                                             0x98007440
#define set_ISO_IRTX_CFG_reg(data)   (*((volatile unsigned int*) ISO_IRTX_CFG_reg)=data)
#define get_ISO_IRTX_CFG_reg   (*((volatile unsigned int*) ISO_IRTX_CFG_reg))
#define ISO_IRTX_CFG_inst_adr                                                        "0x0010"
#define ISO_IRTX_CFG_inst                                                            0x0010
#define ISO_IRTX_CFG_irtx_en_shift                                                   (31)
#define ISO_IRTX_CFG_irtx_en_mask                                                    (0x80000000)
#define ISO_IRTX_CFG_irtx_en(data)                                                   (0x80000000&((data)<<31))
#define ISO_IRTX_CFG_irtx_en_src(data)                                               ((0x80000000&(data))>>31)
#define ISO_IRTX_CFG_get_irtx_en(data)                                               ((0x80000000&(data))>>31)
#define ISO_IRTX_CFG_iact_lvl_shift                                                  (10)
#define ISO_IRTX_CFG_iact_lvl_mask                                                   (0x00000400)
#define ISO_IRTX_CFG_iact_lvl(data)                                                  (0x00000400&((data)<<10))
#define ISO_IRTX_CFG_iact_lvl_src(data)                                              ((0x00000400&(data))>>10)
#define ISO_IRTX_CFG_get_iact_lvl(data)                                              ((0x00000400&(data))>>10)
#define ISO_IRTX_CFG_modulation_shift                                                (9)
#define ISO_IRTX_CFG_modulation_mask                                                 (0x00000200)
#define ISO_IRTX_CFG_modulation(data)                                                (0x00000200&((data)<<9))
#define ISO_IRTX_CFG_modulation_src(data)                                            ((0x00000200&(data))>>9)
#define ISO_IRTX_CFG_get_modulation(data)                                            ((0x00000200&(data))>>9)
#define ISO_IRTX_CFG_endian_shift                                                    (8)
#define ISO_IRTX_CFG_endian_mask                                                     (0x00000100)
#define ISO_IRTX_CFG_endian(data)                                                    (0x00000100&((data)<<8))
#define ISO_IRTX_CFG_endian_src(data)                                                ((0x00000100&(data))>>8)
#define ISO_IRTX_CFG_get_endian(data)                                                ((0x00000100&(data))>>8)
#define ISO_IRTX_CFG_dummy_shift                                                     (6)
#define ISO_IRTX_CFG_dummy_mask                                                      (0x000000C0)
#define ISO_IRTX_CFG_dummy(data)                                                     (0x000000C0&((data)<<6))
#define ISO_IRTX_CFG_dummy_src(data)                                                 ((0x000000C0&(data))>>6)
#define ISO_IRTX_CFG_get_dummy(data)                                                 ((0x000000C0&(data))>>6)
#define ISO_IRTX_CFG_fifoout_inv_shift                                               (5)
#define ISO_IRTX_CFG_fifoout_inv_mask                                                (0x00000020)
#define ISO_IRTX_CFG_fifoout_inv(data)                                               (0x00000020&((data)<<5))
#define ISO_IRTX_CFG_fifoout_inv_src(data)                                           ((0x00000020&(data))>>5)
#define ISO_IRTX_CFG_get_fifoout_inv(data)                                           ((0x00000020&(data))>>5)
#define ISO_IRTX_CFG_irtxout_inv_shift                                               (4)
#define ISO_IRTX_CFG_irtxout_inv_mask                                                (0x00000010)
#define ISO_IRTX_CFG_irtxout_inv(data)                                               (0x00000010&((data)<<4))
#define ISO_IRTX_CFG_irtxout_inv_src(data)                                           ((0x00000010&(data))>>4)
#define ISO_IRTX_CFG_get_irtxout_inv(data)                                           ((0x00000010&(data))>>4)
#define ISO_IRTX_CFG_start_shift                                                     (0)
#define ISO_IRTX_CFG_start_mask                                                      (0x00000001)
#define ISO_IRTX_CFG_start(data)                                                     (0x00000001&((data)<<0))
#define ISO_IRTX_CFG_start_src(data)                                                 ((0x00000001&(data))>>0)
#define ISO_IRTX_CFG_get_start(data)                                                 ((0x00000001&(data))>>0)


#define ISO_IRTX_TIM                                                                 0x98007444
#define ISO_IRTX_TIM_reg_addr                                                        "0x98007444"
#define ISO_IRTX_TIM_reg                                                             0x98007444
#define set_ISO_IRTX_TIM_reg(data)   (*((volatile unsigned int*) ISO_IRTX_TIM_reg)=data)
#define get_ISO_IRTX_TIM_reg   (*((volatile unsigned int*) ISO_IRTX_TIM_reg))
#define ISO_IRTX_TIM_inst_adr                                                        "0x0011"
#define ISO_IRTX_TIM_inst                                                            0x0011
#define ISO_IRTX_TIM_irtx_fd_shift                                                   (0)
#define ISO_IRTX_TIM_irtx_fd_mask                                                    (0x0000FFFF)
#define ISO_IRTX_TIM_irtx_fd(data)                                                   (0x0000FFFF&((data)<<0))
#define ISO_IRTX_TIM_irtx_fd_src(data)                                               ((0x0000FFFF&(data))>>0)
#define ISO_IRTX_TIM_get_irtx_fd(data)                                               ((0x0000FFFF&(data))>>0)


#define ISO_IRTX_PWM_SETTING                                                         0x98007448
#define ISO_IRTX_PWM_SETTING_reg_addr                                                "0x98007448"
#define ISO_IRTX_PWM_SETTING_reg                                                     0x98007448
#define set_ISO_IRTX_PWM_SETTING_reg(data)   (*((volatile unsigned int*) ISO_IRTX_PWM_SETTING_reg)=data)
#define get_ISO_IRTX_PWM_SETTING_reg   (*((volatile unsigned int*) ISO_IRTX_PWM_SETTING_reg))
#define ISO_IRTX_PWM_SETTING_inst_adr                                                "0x0012"
#define ISO_IRTX_PWM_SETTING_inst                                                    0x0012
#define ISO_IRTX_PWM_SETTING_pwm_clksrc_div_shift                                    (16)
#define ISO_IRTX_PWM_SETTING_pwm_clksrc_div_mask                                     (0x000F0000)
#define ISO_IRTX_PWM_SETTING_pwm_clksrc_div(data)                                    (0x000F0000&((data)<<16))
#define ISO_IRTX_PWM_SETTING_pwm_clksrc_div_src(data)                                ((0x000F0000&(data))>>16)
#define ISO_IRTX_PWM_SETTING_get_pwm_clksrc_div(data)                                ((0x000F0000&(data))>>16)
#define ISO_IRTX_PWM_SETTING_pwm_clk_duty_shift                                      (8)
#define ISO_IRTX_PWM_SETTING_pwm_clk_duty_mask                                       (0x0000FF00)
#define ISO_IRTX_PWM_SETTING_pwm_clk_duty(data)                                      (0x0000FF00&((data)<<8))
#define ISO_IRTX_PWM_SETTING_pwm_clk_duty_src(data)                                  ((0x0000FF00&(data))>>8)
#define ISO_IRTX_PWM_SETTING_get_pwm_clk_duty(data)                                  ((0x0000FF00&(data))>>8)
#define ISO_IRTX_PWM_SETTING_pwm_clk_div_shift                                       (0)
#define ISO_IRTX_PWM_SETTING_pwm_clk_div_mask                                        (0x000000FF)
#define ISO_IRTX_PWM_SETTING_pwm_clk_div(data)                                       (0x000000FF&((data)<<0))
#define ISO_IRTX_PWM_SETTING_pwm_clk_div_src(data)                                   ((0x000000FF&(data))>>0)
#define ISO_IRTX_PWM_SETTING_get_pwm_clk_div(data)                                   ((0x000000FF&(data))>>0)


#define ISO_IRTX_INT_EN                                                              0x9800744C
#define ISO_IRTX_INT_EN_reg_addr                                                     "0x9800744C"
#define ISO_IRTX_INT_EN_reg                                                          0x9800744C
#define set_ISO_IRTX_INT_EN_reg(data)   (*((volatile unsigned int*) ISO_IRTX_INT_EN_reg)=data)
#define get_ISO_IRTX_INT_EN_reg   (*((volatile unsigned int*) ISO_IRTX_INT_EN_reg))
#define ISO_IRTX_INT_EN_inst_adr                                                     "0x0013"
#define ISO_IRTX_INT_EN_inst                                                         0x0013
#define ISO_IRTX_INT_EN_data_thr_shift                                               (8)
#define ISO_IRTX_INT_EN_data_thr_mask                                                (0x00003F00)
#define ISO_IRTX_INT_EN_data_thr(data)                                               (0x00003F00&((data)<<8))
#define ISO_IRTX_INT_EN_data_thr_src(data)                                           ((0x00003F00&(data))>>8)
#define ISO_IRTX_INT_EN_get_data_thr(data)                                           ((0x00003F00&(data))>>8)
#define ISO_IRTX_INT_EN_fin_en_shift                                                 (2)
#define ISO_IRTX_INT_EN_fin_en_mask                                                  (0x00000004)
#define ISO_IRTX_INT_EN_fin_en(data)                                                 (0x00000004&((data)<<2))
#define ISO_IRTX_INT_EN_fin_en_src(data)                                             ((0x00000004&(data))>>2)
#define ISO_IRTX_INT_EN_get_fin_en(data)                                             ((0x00000004&(data))>>2)
#define ISO_IRTX_INT_EN_emp_en_shift                                                 (1)
#define ISO_IRTX_INT_EN_emp_en_mask                                                  (0x00000002)
#define ISO_IRTX_INT_EN_emp_en(data)                                                 (0x00000002&((data)<<1))
#define ISO_IRTX_INT_EN_emp_en_src(data)                                             ((0x00000002&(data))>>1)
#define ISO_IRTX_INT_EN_get_emp_en(data)                                             ((0x00000002&(data))>>1)
#define ISO_IRTX_INT_EN_req_en_shift                                                 (0)
#define ISO_IRTX_INT_EN_req_en_mask                                                  (0x00000001)
#define ISO_IRTX_INT_EN_req_en(data)                                                 (0x00000001&((data)<<0))
#define ISO_IRTX_INT_EN_req_en_src(data)                                             ((0x00000001&(data))>>0)
#define ISO_IRTX_INT_EN_get_req_en(data)                                             ((0x00000001&(data))>>0)


#define ISO_IRTX_INT_ST                                                              0x98007450
#define ISO_IRTX_INT_ST_reg_addr                                                     "0x98007450"
#define ISO_IRTX_INT_ST_reg                                                          0x98007450
#define set_ISO_IRTX_INT_ST_reg(data)   (*((volatile unsigned int*) ISO_IRTX_INT_ST_reg)=data)
#define get_ISO_IRTX_INT_ST_reg   (*((volatile unsigned int*) ISO_IRTX_INT_ST_reg))
#define ISO_IRTX_INT_ST_inst_adr                                                     "0x0014"
#define ISO_IRTX_INT_ST_inst                                                         0x0014
#define ISO_IRTX_INT_ST_fin_flag_shift                                               (2)
#define ISO_IRTX_INT_ST_fin_flag_mask                                                (0x00000004)
#define ISO_IRTX_INT_ST_fin_flag(data)                                               (0x00000004&((data)<<2))
#define ISO_IRTX_INT_ST_fin_flag_src(data)                                           ((0x00000004&(data))>>2)
#define ISO_IRTX_INT_ST_get_fin_flag(data)                                           ((0x00000004&(data))>>2)
#define ISO_IRTX_INT_ST_emp_flag_shift                                               (1)
#define ISO_IRTX_INT_ST_emp_flag_mask                                                (0x00000002)
#define ISO_IRTX_INT_ST_emp_flag(data)                                               (0x00000002&((data)<<1))
#define ISO_IRTX_INT_ST_emp_flag_src(data)                                           ((0x00000002&(data))>>1)
#define ISO_IRTX_INT_ST_get_emp_flag(data)                                           ((0x00000002&(data))>>1)
#define ISO_IRTX_INT_ST_req_flag_shift                                               (0)
#define ISO_IRTX_INT_ST_req_flag_mask                                                (0x00000001)
#define ISO_IRTX_INT_ST_req_flag(data)                                               (0x00000001&((data)<<0))
#define ISO_IRTX_INT_ST_req_flag_src(data)                                           ((0x00000001&(data))>>0)
#define ISO_IRTX_INT_ST_get_req_flag(data)                                           ((0x00000001&(data))>>0)


#define ISO_IRTX_FIFO_ST                                                             0x98007454
#define ISO_IRTX_FIFO_ST_reg_addr                                                    "0x98007454"
#define ISO_IRTX_FIFO_ST_reg                                                         0x98007454
#define set_ISO_IRTX_FIFO_ST_reg(data)   (*((volatile unsigned int*) ISO_IRTX_FIFO_ST_reg)=data)
#define get_ISO_IRTX_FIFO_ST_reg   (*((volatile unsigned int*) ISO_IRTX_FIFO_ST_reg))
#define ISO_IRTX_FIFO_ST_inst_adr                                                    "0x0015"
#define ISO_IRTX_FIFO_ST_inst                                                        0x0015
#define ISO_IRTX_FIFO_ST_fifo_rst_shift                                              (31)
#define ISO_IRTX_FIFO_ST_fifo_rst_mask                                               (0x80000000)
#define ISO_IRTX_FIFO_ST_fifo_rst(data)                                              (0x80000000&((data)<<31))
#define ISO_IRTX_FIFO_ST_fifo_rst_src(data)                                          ((0x80000000&(data))>>31)
#define ISO_IRTX_FIFO_ST_get_fifo_rst(data)                                          ((0x80000000&(data))>>31)
#define ISO_IRTX_FIFO_ST_valid_len_shift                                             (8)
#define ISO_IRTX_FIFO_ST_valid_len_mask                                              (0x00000F00)
#define ISO_IRTX_FIFO_ST_valid_len(data)                                             (0x00000F00&((data)<<8))
#define ISO_IRTX_FIFO_ST_valid_len_src(data)                                         ((0x00000F00&(data))>>8)
#define ISO_IRTX_FIFO_ST_get_valid_len(data)                                         ((0x00000F00&(data))>>8)
#define ISO_IRTX_FIFO_ST_wrp_shift                                                   (4)
#define ISO_IRTX_FIFO_ST_wrp_mask                                                    (0x000000F0)
#define ISO_IRTX_FIFO_ST_wrp(data)                                                   (0x000000F0&((data)<<4))
#define ISO_IRTX_FIFO_ST_wrp_src(data)                                               ((0x000000F0&(data))>>4)
#define ISO_IRTX_FIFO_ST_get_wrp(data)                                               ((0x000000F0&(data))>>4)
#define ISO_IRTX_FIFO_ST_rdp_shift                                                   (0)
#define ISO_IRTX_FIFO_ST_rdp_mask                                                    (0x0000000F)
#define ISO_IRTX_FIFO_ST_rdp(data)                                                   (0x0000000F&((data)<<0))
#define ISO_IRTX_FIFO_ST_rdp_src(data)                                               ((0x0000000F&(data))>>0)
#define ISO_IRTX_FIFO_ST_get_rdp(data)                                               ((0x0000000F&(data))>>0)


#define ISO_IRTX_FIFO                                                                0x98007458
#define ISO_IRTX_FIFO_reg_addr                                                       "0x98007458"
#define ISO_IRTX_FIFO_reg                                                            0x98007458
#define set_ISO_IRTX_FIFO_reg(data)   (*((volatile unsigned int*) ISO_IRTX_FIFO_reg)=data)
#define get_ISO_IRTX_FIFO_reg   (*((volatile unsigned int*) ISO_IRTX_FIFO_reg))
#define ISO_IRTX_FIFO_inst_adr                                                       "0x0016"
#define ISO_IRTX_FIFO_inst                                                           0x0016
#define ISO_IRTX_FIFO_data_shift                                                     (0)
#define ISO_IRTX_FIFO_data_mask                                                      (0xFFFFFFFF)
#define ISO_IRTX_FIFO_data(data)                                                     (0xFFFFFFFF&((data)<<0))
#define ISO_IRTX_FIFO_data_src(data)                                                 ((0xFFFFFFFF&(data))>>0)
#define ISO_IRTX_FIFO_get_data(data)                                                 ((0xFFFFFFFF&(data))>>0)


#define ISO_IRRCMM_TIMING                                                            0x98007460
#define ISO_IRRCMM_TIMING_reg_addr                                                   "0x98007460"
#define ISO_IRRCMM_TIMING_reg                                                        0x98007460
#define set_ISO_IRRCMM_TIMING_reg(data)   (*((volatile unsigned int*) ISO_IRRCMM_TIMING_reg)=data)
#define get_ISO_IRRCMM_TIMING_reg   (*((volatile unsigned int*) ISO_IRRCMM_TIMING_reg))
#define ISO_IRRCMM_TIMING_inst_adr                                                   "0x0018"
#define ISO_IRRCMM_TIMING_inst                                                       0x0018
#define ISO_IRRCMM_TIMING_len_11_shift                                               (24)
#define ISO_IRRCMM_TIMING_len_11_mask                                                (0xFF000000)
#define ISO_IRRCMM_TIMING_len_11(data)                                               (0xFF000000&((data)<<24))
#define ISO_IRRCMM_TIMING_len_11_src(data)                                           ((0xFF000000&(data))>>24)
#define ISO_IRRCMM_TIMING_get_len_11(data)                                           ((0xFF000000&(data))>>24)
#define ISO_IRRCMM_TIMING_len_10_shift                                               (16)
#define ISO_IRRCMM_TIMING_len_10_mask                                                (0x00FF0000)
#define ISO_IRRCMM_TIMING_len_10(data)                                               (0x00FF0000&((data)<<16))
#define ISO_IRRCMM_TIMING_len_10_src(data)                                           ((0x00FF0000&(data))>>16)
#define ISO_IRRCMM_TIMING_get_len_10(data)                                           ((0x00FF0000&(data))>>16)
#define ISO_IRRCMM_TIMING_len_01_shift                                               (8)
#define ISO_IRRCMM_TIMING_len_01_mask                                                (0x0000FF00)
#define ISO_IRRCMM_TIMING_len_01(data)                                               (0x0000FF00&((data)<<8))
#define ISO_IRRCMM_TIMING_len_01_src(data)                                           ((0x0000FF00&(data))>>8)
#define ISO_IRRCMM_TIMING_get_len_01(data)                                           ((0x0000FF00&(data))>>8)
#define ISO_IRRCMM_TIMING_len_00_shift                                               (0)
#define ISO_IRRCMM_TIMING_len_00_mask                                                (0x000000FF)
#define ISO_IRRCMM_TIMING_len_00(data)                                               (0x000000FF&((data)<<0))
#define ISO_IRRCMM_TIMING_len_00_src(data)                                           ((0x000000FF&(data))>>0)
#define ISO_IRRCMM_TIMING_get_len_00(data)                                           ((0x000000FF&(data))>>0)


#define ISO_IR_CR1                                                                   0x98007464
#define ISO_IR_CR1_reg_addr                                                          "0x98007464"
#define ISO_IR_CR1_reg                                                               0x98007464
#define set_ISO_IR_CR1_reg(data)   (*((volatile unsigned int*) ISO_IR_CR1_reg)=data)
#define get_ISO_IR_CR1_reg   (*((volatile unsigned int*) ISO_IR_CR1_reg))
#define ISO_IR_CR1_inst_adr                                                          "0x0019"
#define ISO_IR_CR1_inst                                                              0x0019
#define ISO_IR_CR1_dec_by_min_max_shift                                              (0)
#define ISO_IR_CR1_dec_by_min_max_mask                                               (0x00000001)
#define ISO_IR_CR1_dec_by_min_max(data)                                              (0x00000001&((data)<<0))
#define ISO_IR_CR1_dec_by_min_max_src(data)                                          ((0x00000001&(data))>>0)
#define ISO_IR_CR1_get_dec_by_min_max(data)                                          ((0x00000001&(data))>>0)


#define ISO_IRRCMM_APKB                                                              0x98007468
#define ISO_IRRCMM_APKB_reg_addr                                                     "0x98007468"
#define ISO_IRRCMM_APKB_reg                                                          0x98007468
#define set_ISO_IRRCMM_APKB_reg(data)   (*((volatile unsigned int*) ISO_IRRCMM_APKB_reg)=data)
#define get_ISO_IRRCMM_APKB_reg   (*((volatile unsigned int*) ISO_IRRCMM_APKB_reg))
#define ISO_IRRCMM_APKB_inst_adr                                                     "0x001A"
#define ISO_IRRCMM_APKB_inst                                                         0x001A
#define ISO_IRRCMM_APKB_rcmm_ap_max_shift                                            (24)
#define ISO_IRRCMM_APKB_rcmm_ap_max_mask                                             (0xFF000000)
#define ISO_IRRCMM_APKB_rcmm_ap_max(data)                                            (0xFF000000&((data)<<24))
#define ISO_IRRCMM_APKB_rcmm_ap_max_src(data)                                        ((0xFF000000&(data))>>24)
#define ISO_IRRCMM_APKB_get_rcmm_ap_max(data)                                        ((0xFF000000&(data))>>24)
#define ISO_IRRCMM_APKB_rcmm_ap_min_shift                                            (16)
#define ISO_IRRCMM_APKB_rcmm_ap_min_mask                                             (0x00FF0000)
#define ISO_IRRCMM_APKB_rcmm_ap_min(data)                                            (0x00FF0000&((data)<<16))
#define ISO_IRRCMM_APKB_rcmm_ap_min_src(data)                                        ((0x00FF0000&(data))>>16)
#define ISO_IRRCMM_APKB_get_rcmm_ap_min(data)                                        ((0x00FF0000&(data))>>16)
#define ISO_IRRCMM_APKB_rcmm_kb_max_shift                                            (8)
#define ISO_IRRCMM_APKB_rcmm_kb_max_mask                                             (0x0000FF00)
#define ISO_IRRCMM_APKB_rcmm_kb_max(data)                                            (0x0000FF00&((data)<<8))
#define ISO_IRRCMM_APKB_rcmm_kb_max_src(data)                                        ((0x0000FF00&(data))>>8)
#define ISO_IRRCMM_APKB_get_rcmm_kb_max(data)                                        ((0x0000FF00&(data))>>8)
#define ISO_IRRCMM_APKB_rcmm_kb_min_shift                                            (0)
#define ISO_IRRCMM_APKB_rcmm_kb_min_mask                                             (0x000000FF)
#define ISO_IRRCMM_APKB_rcmm_kb_min(data)                                            (0x000000FF&((data)<<0))
#define ISO_IRRCMM_APKB_rcmm_kb_min_src(data)                                        ((0x000000FF&(data))>>0)
#define ISO_IRRCMM_APKB_get_rcmm_kb_min(data)                                        ((0x000000FF&(data))>>0)


#define ISO_IRRXRCLFIFO                                                              0x9800746C
#define ISO_IRRXRCLFIFO_reg_addr                                                     "0x9800746C"
#define ISO_IRRXRCLFIFO_reg                                                          0x9800746C
#define set_ISO_IRRXRCLFIFO_reg(data)   (*((volatile unsigned int*) ISO_IRRXRCLFIFO_reg)=data)
#define get_ISO_IRRXRCLFIFO_reg   (*((volatile unsigned int*) ISO_IRRXRCLFIFO_reg))
#define ISO_IRRXRCLFIFO_inst_adr                                                     "0x001B"
#define ISO_IRRXRCLFIFO_inst                                                         0x001B
#define ISO_IRRXRCLFIFO_rcmm_apoint_shift                                            (31)
#define ISO_IRRXRCLFIFO_rcmm_apoint_mask                                             (0x80000000)
#define ISO_IRRXRCLFIFO_rcmm_apoint(data)                                            (0x80000000&((data)<<31))
#define ISO_IRRXRCLFIFO_rcmm_apoint_src(data)                                        ((0x80000000&(data))>>31)
#define ISO_IRRXRCLFIFO_get_rcmm_apoint(data)                                        ((0x80000000&(data))>>31)
#define ISO_IRRXRCLFIFO_rcmm_kboard_shift                                            (30)
#define ISO_IRRXRCLFIFO_rcmm_kboard_mask                                             (0x40000000)
#define ISO_IRRXRCLFIFO_rcmm_kboard(data)                                            (0x40000000&((data)<<30))
#define ISO_IRRXRCLFIFO_rcmm_kboard_src(data)                                        ((0x40000000&(data))>>30)
#define ISO_IRRXRCLFIFO_get_rcmm_kboard(data)                                        ((0x40000000&(data))>>30)
#define ISO_IRRXRCLFIFO_remote_cnt_lead_high_shift                                   (16)
#define ISO_IRRXRCLFIFO_remote_cnt_lead_high_mask                                    (0x3FFF0000)
#define ISO_IRRXRCLFIFO_remote_cnt_lead_high(data)                                   (0x3FFF0000&((data)<<16))
#define ISO_IRRXRCLFIFO_remote_cnt_lead_high_src(data)                               ((0x3FFF0000&(data))>>16)
#define ISO_IRRXRCLFIFO_get_remote_cnt_lead_high(data)                               ((0x3FFF0000&(data))>>16)
#define ISO_IRRXRCLFIFO_remote_cnt_lead_low_shift                                    (0)
#define ISO_IRRXRCLFIFO_remote_cnt_lead_low_mask                                     (0x0000FFFF)
#define ISO_IRRXRCLFIFO_remote_cnt_lead_low(data)                                    (0x0000FFFF&((data)<<0))
#define ISO_IRRXRCLFIFO_remote_cnt_lead_low_src(data)                                ((0x0000FFFF&(data))>>0)
#define ISO_IRRXRCLFIFO_get_remote_cnt_lead_low(data)                                ((0x0000FFFF&(data))>>0)


#define ISO_DRM_ST                                                                   0x98007600
#define ISO_DRM_ST_reg_addr                                                          "0x98007600"
#define ISO_DRM_ST_reg                                                               0x98007600
#define set_ISO_DRM_ST_reg(data)   (*((volatile unsigned int*) ISO_DRM_ST_reg)=data)
#define get_ISO_DRM_ST_reg   (*((volatile unsigned int*) ISO_DRM_ST_reg))
#define ISO_DRM_ST_inst_adr                                                          "0x0080"
#define ISO_DRM_ST_inst                                                              0x0080
#define ISO_DRM_ST_set_shift                                                         (0)
#define ISO_DRM_ST_set_mask                                                          (0x00000001)
#define ISO_DRM_ST_set(data)                                                         (0x00000001&((data)<<0))
#define ISO_DRM_ST_set_src(data)                                                     ((0x00000001&(data))>>0)
#define ISO_DRM_ST_get_set(data)                                                     ((0x00000001&(data))>>0)


#define ISO_DRM_SECURE_CLK                                                           0x98007604
#define ISO_DRM_SECURE_CLK_reg_addr                                                  "0x98007604"
#define ISO_DRM_SECURE_CLK_reg                                                       0x98007604
#define set_ISO_DRM_SECURE_CLK_reg(data)   (*((volatile unsigned int*) ISO_DRM_SECURE_CLK_reg)=data)
#define get_ISO_DRM_SECURE_CLK_reg   (*((volatile unsigned int*) ISO_DRM_SECURE_CLK_reg))
#define ISO_DRM_SECURE_CLK_inst_adr                                                  "0x0081"
#define ISO_DRM_SECURE_CLK_inst                                                      0x0081
#define ISO_DRM_SECURE_CLK_val_shift                                                 (0)
#define ISO_DRM_SECURE_CLK_val_mask                                                  (0xFFFFFFFF)
#define ISO_DRM_SECURE_CLK_val(data)                                                 (0xFFFFFFFF&((data)<<0))
#define ISO_DRM_SECURE_CLK_val_src(data)                                             ((0xFFFFFFFF&(data))>>0)
#define ISO_DRM_SECURE_CLK_get_val(data)                                             ((0xFFFFFFFF&(data))>>0)


#define ISO_DRM_ELAPSED                                                              0x98007608
#define ISO_DRM_ELAPSED_reg_addr                                                     "0x98007608"
#define ISO_DRM_ELAPSED_reg                                                          0x98007608
#define set_ISO_DRM_ELAPSED_reg(data)   (*((volatile unsigned int*) ISO_DRM_ELAPSED_reg)=data)
#define get_ISO_DRM_ELAPSED_reg   (*((volatile unsigned int*) ISO_DRM_ELAPSED_reg))
#define ISO_DRM_ELAPSED_inst_adr                                                     "0x0082"
#define ISO_DRM_ELAPSED_inst                                                         0x0082
#define ISO_DRM_ELAPSED_val_shift                                                    (0)
#define ISO_DRM_ELAPSED_val_mask                                                     (0xFFFFFFFF)
#define ISO_DRM_ELAPSED_val(data)                                                    (0xFFFFFFFF&((data)<<0))
#define ISO_DRM_ELAPSED_val_src(data)                                                ((0xFFFFFFFF&(data))>>0)
#define ISO_DRM_ELAPSED_get_val(data)                                                ((0xFFFFFFFF&(data))>>0)


#define ISO_COLD_RST                                                                 0x9800760C
#define ISO_COLD_RST_reg_addr                                                        "0x9800760C"
#define ISO_COLD_RST_reg                                                             0x9800760C
#define set_ISO_COLD_RST_reg(data)   (*((volatile unsigned int*) ISO_COLD_RST_reg)=data)
#define get_ISO_COLD_RST_reg   (*((volatile unsigned int*) ISO_COLD_RST_reg))
#define ISO_COLD_RST_inst_adr                                                        "0x0083"
#define ISO_COLD_RST_inst                                                            0x0083
#define ISO_COLD_RST_val_shift                                                       (0)
#define ISO_COLD_RST_val_mask                                                        (0xFFFFFFFF)
#define ISO_COLD_RST_val(data)                                                       (0xFFFFFFFF&((data)<<0))
#define ISO_COLD_RST_val_src(data)                                                   ((0xFFFFFFFF&(data))>>0)
#define ISO_COLD_RST_get_val(data)                                                   ((0xFFFFFFFF&(data))>>0)


#define ISO_COLD_RST1                                                                0x98007610
#define ISO_COLD_RST1_reg_addr                                                       "0x98007610"
#define ISO_COLD_RST1_reg                                                            0x98007610
#define set_ISO_COLD_RST1_reg(data)   (*((volatile unsigned int*) ISO_COLD_RST1_reg)=data)
#define get_ISO_COLD_RST1_reg   (*((volatile unsigned int*) ISO_COLD_RST1_reg))
#define ISO_COLD_RST1_inst_adr                                                       "0x0084"
#define ISO_COLD_RST1_inst                                                           0x0084
#define ISO_COLD_RST1_val_shift                                                      (0)
#define ISO_COLD_RST1_val_mask                                                       (0xFFFFFFFF)
#define ISO_COLD_RST1_val(data)                                                      (0xFFFFFFFF&((data)<<0))
#define ISO_COLD_RST1_val_src(data)                                                  ((0xFFFFFFFF&(data))>>0)
#define ISO_COLD_RST1_get_val(data)                                                  ((0xFFFFFFFF&(data))>>0)


#define ISO_COLD_RST2                                                                0x98007614
#define ISO_COLD_RST2_reg_addr                                                       "0x98007614"
#define ISO_COLD_RST2_reg                                                            0x98007614
#define set_ISO_COLD_RST2_reg(data)   (*((volatile unsigned int*) ISO_COLD_RST2_reg)=data)
#define get_ISO_COLD_RST2_reg   (*((volatile unsigned int*) ISO_COLD_RST2_reg))
#define ISO_COLD_RST2_inst_adr                                                       "0x0085"
#define ISO_COLD_RST2_inst                                                           0x0085
#define ISO_COLD_RST2_val_shift                                                      (0)
#define ISO_COLD_RST2_val_mask                                                       (0xFFFFFFFF)
#define ISO_COLD_RST2_val(data)                                                      (0xFFFFFFFF&((data)<<0))
#define ISO_COLD_RST2_val_src(data)                                                  ((0xFFFFFFFF&(data))>>0)
#define ISO_COLD_RST2_get_val(data)                                                  ((0xFFFFFFFF&(data))>>0)


#define ISO_DRM_CTRL                                                                 0x98007618
#define ISO_DRM_CTRL_reg_addr                                                        "0x98007618"
#define ISO_DRM_CTRL_reg                                                             0x98007618
#define set_ISO_DRM_CTRL_reg(data)   (*((volatile unsigned int*) ISO_DRM_CTRL_reg)=data)
#define get_ISO_DRM_CTRL_reg   (*((volatile unsigned int*) ISO_DRM_CTRL_reg))
#define ISO_DRM_CTRL_inst_adr                                                        "0x0086"
#define ISO_DRM_CTRL_inst                                                            0x0086
#define ISO_DRM_CTRL_clk_div_en_shift                                                (1)
#define ISO_DRM_CTRL_clk_div_en_mask                                                 (0x00000002)
#define ISO_DRM_CTRL_clk_div_en(data)                                                (0x00000002&((data)<<1))
#define ISO_DRM_CTRL_clk_div_en_src(data)                                            ((0x00000002&(data))>>1)
#define ISO_DRM_CTRL_get_clk_div_en(data)                                            ((0x00000002&(data))>>1)
#define ISO_DRM_CTRL_clk_sel_shift                                                   (0)
#define ISO_DRM_CTRL_clk_sel_mask                                                    (0x00000001)
#define ISO_DRM_CTRL_clk_sel(data)                                                   (0x00000001&((data)<<0))
#define ISO_DRM_CTRL_clk_sel_src(data)                                               ((0x00000001&(data))>>0)
#define ISO_DRM_CTRL_get_clk_sel(data)                                               ((0x00000001&(data))>>0)


#define ISO_DRM_CLK_DIV                                                              0x9800761c
#define ISO_DRM_CLK_DIV_reg_addr                                                     "0x9800761C"
#define ISO_DRM_CLK_DIV_reg                                                          0x9800761C
#define set_ISO_DRM_CLK_DIV_reg(data)   (*((volatile unsigned int*) ISO_DRM_CLK_DIV_reg)=data)
#define get_ISO_DRM_CLK_DIV_reg   (*((volatile unsigned int*) ISO_DRM_CLK_DIV_reg))
#define ISO_DRM_CLK_DIV_inst_adr                                                     "0x0087"
#define ISO_DRM_CLK_DIV_inst                                                         0x0087
#define ISO_DRM_CLK_DIV_init_shift                                                   (0)
#define ISO_DRM_CLK_DIV_init_mask                                                    (0xFFFFFFFF)
#define ISO_DRM_CLK_DIV_init(data)                                                   (0xFFFFFFFF&((data)<<0))
#define ISO_DRM_CLK_DIV_init_src(data)                                               ((0xFFFFFFFF&(data))>>0)
#define ISO_DRM_CLK_DIV_get_init(data)                                               ((0xFFFFFFFF&(data))>>0)


#define ISO_TC3TVR                                                                   0x98007620
#define ISO_TC3TVR_reg_addr                                                          "0x98007620"
#define ISO_TC3TVR_reg                                                               0x98007620
#define set_ISO_TC3TVR_reg(data)   (*((volatile unsigned int*) ISO_TC3TVR_reg)=data)
#define get_ISO_TC3TVR_reg   (*((volatile unsigned int*) ISO_TC3TVR_reg))
#define ISO_TC3TVR_inst_adr                                                          "0x0088"
#define ISO_TC3TVR_inst                                                              0x0088
#define ISO_TC3TVR_tc3tvr_shift                                                      (0)
#define ISO_TC3TVR_tc3tvr_mask                                                       (0xFFFFFFFF)
#define ISO_TC3TVR_tc3tvr(data)                                                      (0xFFFFFFFF&((data)<<0))
#define ISO_TC3TVR_tc3tvr_src(data)                                                  ((0xFFFFFFFF&(data))>>0)
#define ISO_TC3TVR_get_tc3tvr(data)                                                  ((0xFFFFFFFF&(data))>>0)


#define ISO_TC3CVR                                                                   0x98007624
#define ISO_TC3CVR_reg_addr                                                          "0x98007624"
#define ISO_TC3CVR_reg                                                               0x98007624
#define set_ISO_TC3CVR_reg(data)   (*((volatile unsigned int*) ISO_TC3CVR_reg)=data)
#define get_ISO_TC3CVR_reg   (*((volatile unsigned int*) ISO_TC3CVR_reg))
#define ISO_TC3CVR_inst_adr                                                          "0x0089"
#define ISO_TC3CVR_inst                                                              0x0089
#define ISO_TC3CVR_tc3cvr_shift                                                      (0)
#define ISO_TC3CVR_tc3cvr_mask                                                       (0xFFFFFFFF)
#define ISO_TC3CVR_tc3cvr(data)                                                      (0xFFFFFFFF&((data)<<0))
#define ISO_TC3CVR_tc3cvr_src(data)                                                  ((0xFFFFFFFF&(data))>>0)
#define ISO_TC3CVR_get_tc3cvr(data)                                                  ((0xFFFFFFFF&(data))>>0)


#define ISO_TC3CR                                                                    0x98007628
#define ISO_TC3CR_reg_addr                                                           "0x98007628"
#define ISO_TC3CR_reg                                                                0x98007628
#define set_ISO_TC3CR_reg(data)   (*((volatile unsigned int*) ISO_TC3CR_reg)=data)
#define get_ISO_TC3CR_reg   (*((volatile unsigned int*) ISO_TC3CR_reg))
#define ISO_TC3CR_inst_adr                                                           "0x008A"
#define ISO_TC3CR_inst                                                               0x008A
#define ISO_TC3CR_tc3en_shift                                                        (31)
#define ISO_TC3CR_tc3en_mask                                                         (0x80000000)
#define ISO_TC3CR_tc3en(data)                                                        (0x80000000&((data)<<31))
#define ISO_TC3CR_tc3en_src(data)                                                    ((0x80000000&(data))>>31)
#define ISO_TC3CR_get_tc3en(data)                                                    ((0x80000000&(data))>>31)
#define ISO_TC3CR_tc3mode_shift                                                      (30)
#define ISO_TC3CR_tc3mode_mask                                                       (0x40000000)
#define ISO_TC3CR_tc3mode(data)                                                      (0x40000000&((data)<<30))
#define ISO_TC3CR_tc3mode_src(data)                                                  ((0x40000000&(data))>>30)
#define ISO_TC3CR_get_tc3mode(data)                                                  ((0x40000000&(data))>>30)
#define ISO_TC3CR_tc3pause_shift                                                     (29)
#define ISO_TC3CR_tc3pause_mask                                                      (0x20000000)
#define ISO_TC3CR_tc3pause(data)                                                     (0x20000000&((data)<<29))
#define ISO_TC3CR_tc3pause_src(data)                                                 ((0x20000000&(data))>>29)
#define ISO_TC3CR_get_tc3pause(data)                                                 ((0x20000000&(data))>>29)
#define ISO_TC3CR_rvda_shift                                                         (24)
#define ISO_TC3CR_rvda_mask                                                          (0x1F000000)
#define ISO_TC3CR_rvda(data)                                                         (0x1F000000&((data)<<24))
#define ISO_TC3CR_rvda_src(data)                                                     ((0x1F000000&(data))>>24)
#define ISO_TC3CR_get_rvda(data)                                                     ((0x1F000000&(data))>>24)


#define ISO_TC3ICR                                                                   0x9800762C
#define ISO_TC3ICR_reg_addr                                                          "0x9800762C"
#define ISO_TC3ICR_reg                                                               0x9800762C
#define set_ISO_TC3ICR_reg(data)   (*((volatile unsigned int*) ISO_TC3ICR_reg)=data)
#define get_ISO_TC3ICR_reg   (*((volatile unsigned int*) ISO_TC3ICR_reg))
#define ISO_TC3ICR_inst_adr                                                          "0x008B"
#define ISO_TC3ICR_inst                                                              0x008B
#define ISO_TC3ICR_tc3ie_shift                                                       (31)
#define ISO_TC3ICR_tc3ie_mask                                                        (0x80000000)
#define ISO_TC3ICR_tc3ie(data)                                                       (0x80000000&((data)<<31))
#define ISO_TC3ICR_tc3ie_src(data)                                                   ((0x80000000&(data))>>31)
#define ISO_TC3ICR_get_tc3ie(data)                                                   ((0x80000000&(data))>>31)


#define ISO_TC4TVR                                                                   0x98007630
#define ISO_TC4TVR_reg_addr                                                          "0x98007630"
#define ISO_TC4TVR_reg                                                               0x98007630
#define set_ISO_TC4TVR_reg(data)   (*((volatile unsigned int*) ISO_TC4TVR_reg)=data)
#define get_ISO_TC4TVR_reg   (*((volatile unsigned int*) ISO_TC4TVR_reg))
#define ISO_TC4TVR_inst_adr                                                          "0x008C"
#define ISO_TC4TVR_inst                                                              0x008C
#define ISO_TC4TVR_tc4tvr_shift                                                      (0)
#define ISO_TC4TVR_tc4tvr_mask                                                       (0xFFFFFFFF)
#define ISO_TC4TVR_tc4tvr(data)                                                      (0xFFFFFFFF&((data)<<0))
#define ISO_TC4TVR_tc4tvr_src(data)                                                  ((0xFFFFFFFF&(data))>>0)
#define ISO_TC4TVR_get_tc4tvr(data)                                                  ((0xFFFFFFFF&(data))>>0)


#define ISO_TC4CVR                                                                   0x98007634
#define ISO_TC4CVR_reg_addr                                                          "0x98007634"
#define ISO_TC4CVR_reg                                                               0x98007634
#define set_ISO_TC4CVR_reg(data)   (*((volatile unsigned int*) ISO_TC4CVR_reg)=data)
#define get_ISO_TC4CVR_reg   (*((volatile unsigned int*) ISO_TC4CVR_reg))
#define ISO_TC4CVR_inst_adr                                                          "0x008D"
#define ISO_TC4CVR_inst                                                              0x008D
#define ISO_TC4CVR_tc4cvr_shift                                                      (0)
#define ISO_TC4CVR_tc4cvr_mask                                                       (0xFFFFFFFF)
#define ISO_TC4CVR_tc4cvr(data)                                                      (0xFFFFFFFF&((data)<<0))
#define ISO_TC4CVR_tc4cvr_src(data)                                                  ((0xFFFFFFFF&(data))>>0)
#define ISO_TC4CVR_get_tc4cvr(data)                                                  ((0xFFFFFFFF&(data))>>0)


#define ISO_TC4CR                                                                    0x98007638
#define ISO_TC4CR_reg_addr                                                           "0x98007638"
#define ISO_TC4CR_reg                                                                0x98007638
#define set_ISO_TC4CR_reg(data)   (*((volatile unsigned int*) ISO_TC4CR_reg)=data)
#define get_ISO_TC4CR_reg   (*((volatile unsigned int*) ISO_TC4CR_reg))
#define ISO_TC4CR_inst_adr                                                           "0x008E"
#define ISO_TC4CR_inst                                                               0x008E
#define ISO_TC4CR_tc4en_shift                                                        (31)
#define ISO_TC4CR_tc4en_mask                                                         (0x80000000)
#define ISO_TC4CR_tc4en(data)                                                        (0x80000000&((data)<<31))
#define ISO_TC4CR_tc4en_src(data)                                                    ((0x80000000&(data))>>31)
#define ISO_TC4CR_get_tc4en(data)                                                    ((0x80000000&(data))>>31)
#define ISO_TC4CR_tc4mode_shift                                                      (30)
#define ISO_TC4CR_tc4mode_mask                                                       (0x40000000)
#define ISO_TC4CR_tc4mode(data)                                                      (0x40000000&((data)<<30))
#define ISO_TC4CR_tc4mode_src(data)                                                  ((0x40000000&(data))>>30)
#define ISO_TC4CR_get_tc4mode(data)                                                  ((0x40000000&(data))>>30)
#define ISO_TC4CR_tc4pause_shift                                                     (29)
#define ISO_TC4CR_tc4pause_mask                                                      (0x20000000)
#define ISO_TC4CR_tc4pause(data)                                                     (0x20000000&((data)<<29))
#define ISO_TC4CR_tc4pause_src(data)                                                 ((0x20000000&(data))>>29)
#define ISO_TC4CR_get_tc4pause(data)                                                 ((0x20000000&(data))>>29)
#define ISO_TC4CR_rvda_shift                                                         (24)
#define ISO_TC4CR_rvda_mask                                                          (0x1F000000)
#define ISO_TC4CR_rvda(data)                                                         (0x1F000000&((data)<<24))
#define ISO_TC4CR_rvda_src(data)                                                     ((0x1F000000&(data))>>24)
#define ISO_TC4CR_get_rvda(data)                                                     ((0x1F000000&(data))>>24)


#define ISO_TC4ICR                                                                   0x9800763C
#define ISO_TC4ICR_reg_addr                                                          "0x9800763C"
#define ISO_TC4ICR_reg                                                               0x9800763C
#define set_ISO_TC4ICR_reg(data)   (*((volatile unsigned int*) ISO_TC4ICR_reg)=data)
#define get_ISO_TC4ICR_reg   (*((volatile unsigned int*) ISO_TC4ICR_reg))
#define ISO_TC4ICR_inst_adr                                                          "0x008F"
#define ISO_TC4ICR_inst                                                              0x008F
#define ISO_TC4ICR_tc4ie_shift                                                       (31)
#define ISO_TC4ICR_tc4ie_mask                                                        (0x80000000)
#define ISO_TC4ICR_tc4ie(data)                                                       (0x80000000&((data)<<31))
#define ISO_TC4ICR_tc4ie_src(data)                                                   ((0x80000000&(data))>>31)
#define ISO_TC4ICR_get_tc4ie(data)                                                   ((0x80000000&(data))>>31)


#define ISO_NORST_0                                                                  0x98007640
#define ISO_NORST_1                                                                  0x98007644
#define ISO_NORST_2                                                                  0x98007648
#define ISO_NORST_3                                                                  0x9800764C
#define ISO_NORST_4                                                                  0x98007650
#define ISO_NORST_5                                                                  0x98007654
#define ISO_NORST_6                                                                  0x98007658
#define ISO_NORST_7                                                                  0x9800765C
#define ISO_NORST_0_reg_addr                                                         "0x98007640"
#define ISO_NORST_1_reg_addr                                                         "0x98007644"
#define ISO_NORST_2_reg_addr                                                         "0x98007648"
#define ISO_NORST_3_reg_addr                                                         "0x9800764C"
#define ISO_NORST_4_reg_addr                                                         "0x98007650"
#define ISO_NORST_5_reg_addr                                                         "0x98007654"
#define ISO_NORST_6_reg_addr                                                         "0x98007658"
#define ISO_NORST_7_reg_addr                                                         "0x9800765C"
#define ISO_NORST_0_reg                                                              0x98007640
#define ISO_NORST_1_reg                                                              0x98007644
#define ISO_NORST_2_reg                                                              0x98007648
#define ISO_NORST_3_reg                                                              0x9800764C
#define ISO_NORST_4_reg                                                              0x98007650
#define ISO_NORST_5_reg                                                              0x98007654
#define ISO_NORST_6_reg                                                              0x98007658
#define ISO_NORST_7_reg                                                              0x9800765C
#define set_ISO_NORST_0_reg(data)   (*((volatile unsigned int*) ISO_NORST_0_reg)=data)
#define set_ISO_NORST_1_reg(data)   (*((volatile unsigned int*) ISO_NORST_1_reg)=data)
#define set_ISO_NORST_2_reg(data)   (*((volatile unsigned int*) ISO_NORST_2_reg)=data)
#define set_ISO_NORST_3_reg(data)   (*((volatile unsigned int*) ISO_NORST_3_reg)=data)
#define set_ISO_NORST_4_reg(data)   (*((volatile unsigned int*) ISO_NORST_4_reg)=data)
#define set_ISO_NORST_5_reg(data)   (*((volatile unsigned int*) ISO_NORST_5_reg)=data)
#define set_ISO_NORST_6_reg(data)   (*((volatile unsigned int*) ISO_NORST_6_reg)=data)
#define set_ISO_NORST_7_reg(data)   (*((volatile unsigned int*) ISO_NORST_7_reg)=data)
#define get_ISO_NORST_0_reg   (*((volatile unsigned int*) ISO_NORST_0_reg))
#define get_ISO_NORST_1_reg   (*((volatile unsigned int*) ISO_NORST_1_reg))
#define get_ISO_NORST_2_reg   (*((volatile unsigned int*) ISO_NORST_2_reg))
#define get_ISO_NORST_3_reg   (*((volatile unsigned int*) ISO_NORST_3_reg))
#define get_ISO_NORST_4_reg   (*((volatile unsigned int*) ISO_NORST_4_reg))
#define get_ISO_NORST_5_reg   (*((volatile unsigned int*) ISO_NORST_5_reg))
#define get_ISO_NORST_6_reg   (*((volatile unsigned int*) ISO_NORST_6_reg))
#define get_ISO_NORST_7_reg   (*((volatile unsigned int*) ISO_NORST_7_reg))
#define ISO_NORST_0_inst_adr                                                         "0x0090"
#define ISO_NORST_1_inst_adr                                                         "0x0091"
#define ISO_NORST_2_inst_adr                                                         "0x0092"
#define ISO_NORST_3_inst_adr                                                         "0x0093"
#define ISO_NORST_4_inst_adr                                                         "0x0094"
#define ISO_NORST_5_inst_adr                                                         "0x0095"
#define ISO_NORST_6_inst_adr                                                         "0x0096"
#define ISO_NORST_7_inst_adr                                                         "0x0097"
#define ISO_NORST_0_inst                                                             0x0090
#define ISO_NORST_1_inst                                                             0x0091
#define ISO_NORST_2_inst                                                             0x0092
#define ISO_NORST_3_inst                                                             0x0093
#define ISO_NORST_4_inst                                                             0x0094
#define ISO_NORST_5_inst                                                             0x0095
#define ISO_NORST_6_inst                                                             0x0096
#define ISO_NORST_7_inst                                                             0x0097
#define ISO_NORST_dat_shift                                                          (0)
#define ISO_NORST_dat_mask                                                           (0xFFFFFFFF)
#define ISO_NORST_dat(data)                                                          (0xFFFFFFFF&((data)<<0))
#define ISO_NORST_dat_src(data)                                                      ((0xFFFFFFFF&(data))>>0)
#define ISO_NORST_get_dat(data)                                                      ((0xFFFFFFFF&(data))>>0)


#define ISO_COLD_RST3                                                                0x98007660
#define ISO_COLD_RST3_reg_addr                                                       "0x98007660"
#define ISO_COLD_RST3_reg                                                            0x98007660
#define set_ISO_COLD_RST3_reg(data)   (*((volatile unsigned int*) ISO_COLD_RST3_reg)=data)
#define get_ISO_COLD_RST3_reg   (*((volatile unsigned int*) ISO_COLD_RST3_reg))
#define ISO_COLD_RST3_inst_adr                                                       "0x0098"
#define ISO_COLD_RST3_inst                                                           0x0098
#define ISO_COLD_RST3_val_shift                                                      (0)
#define ISO_COLD_RST3_val_mask                                                       (0xFFFFFFFF)
#define ISO_COLD_RST3_val(data)                                                      (0xFFFFFFFF&((data)<<0))
#define ISO_COLD_RST3_val_src(data)                                                  ((0xFFFFFFFF&(data))>>0)
#define ISO_COLD_RST3_get_val(data)                                                  ((0xFFFFFFFF&(data))>>0)


#define ISO_COLD_RST4                                                                0x98007664
#define ISO_COLD_RST4_reg_addr                                                       "0x98007664"
#define ISO_COLD_RST4_reg                                                            0x98007664
#define set_ISO_COLD_RST4_reg(data)   (*((volatile unsigned int*) ISO_COLD_RST4_reg)=data)
#define get_ISO_COLD_RST4_reg   (*((volatile unsigned int*) ISO_COLD_RST4_reg))
#define ISO_COLD_RST4_inst_adr                                                       "0x0099"
#define ISO_COLD_RST4_inst                                                           0x0099
#define ISO_COLD_RST4_val_shift                                                      (0)
#define ISO_COLD_RST4_val_mask                                                       (0xFFFFFFFF)
#define ISO_COLD_RST4_val(data)                                                      (0xFFFFFFFF&((data)<<0))
#define ISO_COLD_RST4_val_src(data)                                                  ((0xFFFFFFFF&(data))>>0)
#define ISO_COLD_RST4_get_val(data)                                                  ((0xFFFFFFFF&(data))>>0)


#define ISO_COLD_RST5                                                                0x98007668
#define ISO_COLD_RST5_reg_addr                                                       "0x98007668"
#define ISO_COLD_RST5_reg                                                            0x98007668
#define set_ISO_COLD_RST5_reg(data)   (*((volatile unsigned int*) ISO_COLD_RST5_reg)=data)
#define get_ISO_COLD_RST5_reg   (*((volatile unsigned int*) ISO_COLD_RST5_reg))
#define ISO_COLD_RST5_inst_adr                                                       "0x009A"
#define ISO_COLD_RST5_inst                                                           0x009A
#define ISO_COLD_RST5_val_shift                                                      (0)
#define ISO_COLD_RST5_val_mask                                                       (0xFFFFFFFF)
#define ISO_COLD_RST5_val(data)                                                      (0xFFFFFFFF&((data)<<0))
#define ISO_COLD_RST5_val_src(data)                                                  ((0xFFFFFFFF&(data))>>0)
#define ISO_COLD_RST5_get_val(data)                                                  ((0xFFFFFFFF&(data))>>0)


#define ISO_COLD_RST6                                                                0x9800766C
#define ISO_COLD_RST6_reg_addr                                                       "0x9800766C"
#define ISO_COLD_RST6_reg                                                            0x9800766C
#define set_ISO_COLD_RST6_reg(data)   (*((volatile unsigned int*) ISO_COLD_RST6_reg)=data)
#define get_ISO_COLD_RST6_reg   (*((volatile unsigned int*) ISO_COLD_RST6_reg))
#define ISO_COLD_RST6_inst_adr                                                       "0x009B"
#define ISO_COLD_RST6_inst                                                           0x009B
#define ISO_COLD_RST6_val_shift                                                      (0)
#define ISO_COLD_RST6_val_mask                                                       (0xFFFFFFFF)
#define ISO_COLD_RST6_val(data)                                                      (0xFFFFFFFF&((data)<<0))
#define ISO_COLD_RST6_val_src(data)                                                  ((0xFFFFFFFF&(data))>>0)
#define ISO_COLD_RST6_get_val(data)                                                  ((0xFFFFFFFF&(data))>>0)


#define ISO_COLD_RST7                                                                0x98007670
#define ISO_COLD_RST7_reg_addr                                                       "0x98007670"
#define ISO_COLD_RST7_reg                                                            0x98007670
#define set_ISO_COLD_RST7_reg(data)   (*((volatile unsigned int*) ISO_COLD_RST7_reg)=data)
#define get_ISO_COLD_RST7_reg   (*((volatile unsigned int*) ISO_COLD_RST7_reg))
#define ISO_COLD_RST7_inst_adr                                                       "0x009C"
#define ISO_COLD_RST7_inst                                                           0x009C
#define ISO_COLD_RST7_val_shift                                                      (0)
#define ISO_COLD_RST7_val_mask                                                       (0xFFFFFFFF)
#define ISO_COLD_RST7_val(data)                                                      (0xFFFFFFFF&((data)<<0))
#define ISO_COLD_RST7_val_src(data)                                                  ((0xFFFFFFFF&(data))>>0)
#define ISO_COLD_RST7_get_val(data)                                                  ((0xFFFFFFFF&(data))>>0)


#define ISO_COLD_RST8                                                                0x98007674
#define ISO_COLD_RST8_reg_addr                                                       "0x98007674"
#define ISO_COLD_RST8_reg                                                            0x98007674
#define set_ISO_COLD_RST8_reg(data)   (*((volatile unsigned int*) ISO_COLD_RST8_reg)=data)
#define get_ISO_COLD_RST8_reg   (*((volatile unsigned int*) ISO_COLD_RST8_reg))
#define ISO_COLD_RST8_inst_adr                                                       "0x009D"
#define ISO_COLD_RST8_inst                                                           0x009D
#define ISO_COLD_RST8_val_shift                                                      (0)
#define ISO_COLD_RST8_val_mask                                                       (0xFFFFFFFF)
#define ISO_COLD_RST8_val(data)                                                      (0xFFFFFFFF&((data)<<0))
#define ISO_COLD_RST8_val_src(data)                                                  ((0xFFFFFFFF&(data))>>0)
#define ISO_COLD_RST8_get_val(data)                                                  ((0xFFFFFFFF&(data))>>0)


#define ISO_COLD_RST9                                                                0x98007678
#define ISO_COLD_RST9_reg_addr                                                       "0x98007678"
#define ISO_COLD_RST9_reg                                                            0x98007678
#define set_ISO_COLD_RST9_reg(data)   (*((volatile unsigned int*) ISO_COLD_RST9_reg)=data)
#define get_ISO_COLD_RST9_reg   (*((volatile unsigned int*) ISO_COLD_RST9_reg))
#define ISO_COLD_RST9_inst_adr                                                       "0x009E"
#define ISO_COLD_RST9_inst                                                           0x009E
#define ISO_COLD_RST9_val_shift                                                      (0)
#define ISO_COLD_RST9_val_mask                                                       (0xFFFFFFFF)
#define ISO_COLD_RST9_val(data)                                                      (0xFFFFFFFF&((data)<<0))
#define ISO_COLD_RST9_val_src(data)                                                  ((0xFFFFFFFF&(data))>>0)
#define ISO_COLD_RST9_get_val(data)                                                  ((0xFFFFFFFF&(data))>>0)


#define ISO_COLD_RST10                                                               0x9800767C
#define ISO_COLD_RST10_reg_addr                                                      "0x9800767C"
#define ISO_COLD_RST10_reg                                                           0x9800767C
#define set_ISO_COLD_RST10_reg(data)   (*((volatile unsigned int*) ISO_COLD_RST10_reg)=data)
#define get_ISO_COLD_RST10_reg   (*((volatile unsigned int*) ISO_COLD_RST10_reg))
#define ISO_COLD_RST10_inst_adr                                                      "0x009F"
#define ISO_COLD_RST10_inst                                                          0x009F
#define ISO_COLD_RST10_val_shift                                                     (0)
#define ISO_COLD_RST10_val_mask                                                      (0xFFFFFFFF)
#define ISO_COLD_RST10_val(data)                                                     (0xFFFFFFFF&((data)<<0))
#define ISO_COLD_RST10_val_src(data)                                                 ((0xFFFFFFFF&(data))>>0)
#define ISO_COLD_RST10_get_val(data)                                                 ((0xFFFFFFFF&(data))>>0)


#define ISO_TCWCR                                                                    0x98007680
#define ISO_TCWCR_reg_addr                                                           "0x98007680"
#define ISO_TCWCR_reg                                                                0x98007680
#define set_ISO_TCWCR_reg(data)   (*((volatile unsigned int*) ISO_TCWCR_reg)=data)
#define get_ISO_TCWCR_reg   (*((volatile unsigned int*) ISO_TCWCR_reg))
#define ISO_TCWCR_inst_adr                                                           "0x00A0"
#define ISO_TCWCR_inst                                                               0x00A0
#define ISO_TCWCR_wd_int_en_shift                                                    (31)
#define ISO_TCWCR_wd_int_en_mask                                                     (0x80000000)
#define ISO_TCWCR_wd_int_en(data)                                                    (0x80000000&((data)<<31))
#define ISO_TCWCR_wd_int_en_src(data)                                                ((0x80000000&(data))>>31)
#define ISO_TCWCR_get_wd_int_en(data)                                                ((0x80000000&(data))>>31)
#define ISO_TCWCR_nmic_shift                                                         (12)
#define ISO_TCWCR_nmic_mask                                                          (0x0000F000)
#define ISO_TCWCR_nmic(data)                                                         (0x0000F000&((data)<<12))
#define ISO_TCWCR_nmic_src(data)                                                     ((0x0000F000&(data))>>12)
#define ISO_TCWCR_get_nmic(data)                                                     ((0x0000F000&(data))>>12)
#define ISO_TCWCR_wdc_shift                                                          (8)
#define ISO_TCWCR_wdc_mask                                                           (0x00000F00)
#define ISO_TCWCR_wdc(data)                                                          (0x00000F00&((data)<<8))
#define ISO_TCWCR_wdc_src(data)                                                      ((0x00000F00&(data))>>8)
#define ISO_TCWCR_get_wdc(data)                                                      ((0x00000F00&(data))>>8)
#define ISO_TCWCR_wden_shift                                                         (0)
#define ISO_TCWCR_wden_mask                                                          (0x000000FF)
#define ISO_TCWCR_wden(data)                                                         (0x000000FF&((data)<<0))
#define ISO_TCWCR_wden_src(data)                                                     ((0x000000FF&(data))>>0)
#define ISO_TCWCR_get_wden(data)                                                     ((0x000000FF&(data))>>0)


#define ISO_TCWTR                                                                    0x98007684
#define ISO_TCWTR_reg_addr                                                           "0x98007684"
#define ISO_TCWTR_reg                                                                0x98007684
#define set_ISO_TCWTR_reg(data)   (*((volatile unsigned int*) ISO_TCWTR_reg)=data)
#define get_ISO_TCWTR_reg   (*((volatile unsigned int*) ISO_TCWTR_reg))
#define ISO_TCWTR_inst_adr                                                           "0x00A1"
#define ISO_TCWTR_inst                                                               0x00A1
#define ISO_TCWTR_wdclr_shift                                                        (0)
#define ISO_TCWTR_wdclr_mask                                                         (0x00000001)
#define ISO_TCWTR_wdclr(data)                                                        (0x00000001&((data)<<0))
#define ISO_TCWTR_wdclr_src(data)                                                    ((0x00000001&(data))>>0)
#define ISO_TCWTR_get_wdclr(data)                                                    ((0x00000001&(data))>>0)


#define ISO_TCWNMI                                                                   0x98007688
#define ISO_TCWNMI_reg_addr                                                          "0x98007688"
#define ISO_TCWNMI_reg                                                               0x98007688
#define set_ISO_TCWNMI_reg(data)   (*((volatile unsigned int*) ISO_TCWNMI_reg)=data)
#define get_ISO_TCWNMI_reg   (*((volatile unsigned int*) ISO_TCWNMI_reg))
#define ISO_TCWNMI_inst_adr                                                          "0x00A2"
#define ISO_TCWNMI_inst                                                              0x00A2
#define ISO_TCWNMI_sel_shift                                                         (0)
#define ISO_TCWNMI_sel_mask                                                          (0xFFFFFFFF)
#define ISO_TCWNMI_sel(data)                                                         (0xFFFFFFFF&((data)<<0))
#define ISO_TCWNMI_sel_src(data)                                                     ((0xFFFFFFFF&(data))>>0)
#define ISO_TCWNMI_get_sel(data)                                                     ((0xFFFFFFFF&(data))>>0)


#define ISO_TCWOV                                                                    0x9800768C
#define ISO_TCWOV_reg_addr                                                           "0x9800768C"
#define ISO_TCWOV_reg                                                                0x9800768C
#define set_ISO_TCWOV_reg(data)   (*((volatile unsigned int*) ISO_TCWOV_reg)=data)
#define get_ISO_TCWOV_reg   (*((volatile unsigned int*) ISO_TCWOV_reg))
#define ISO_TCWOV_inst_adr                                                           "0x00A3"
#define ISO_TCWOV_inst                                                               0x00A3
#define ISO_TCWOV_sel_shift                                                          (0)
#define ISO_TCWOV_sel_mask                                                           (0xFFFFFFFF)
#define ISO_TCWOV_sel(data)                                                          (0xFFFFFFFF&((data)<<0))
#define ISO_TCWOV_sel_src(data)                                                      ((0xFFFFFFFF&(data))>>0)
#define ISO_TCWOV_get_sel(data)                                                      ((0xFFFFFFFF&(data))>>0)


#define ISO_DRM_ST_SWC                                                               0x98007690
#define ISO_DRM_ST_SWC_reg_addr                                                      "0x98007690"
#define ISO_DRM_ST_SWC_reg                                                           0x98007690
#define set_ISO_DRM_ST_SWC_reg(data)   (*((volatile unsigned int*) ISO_DRM_ST_SWC_reg)=data)
#define get_ISO_DRM_ST_SWC_reg   (*((volatile unsigned int*) ISO_DRM_ST_SWC_reg))
#define ISO_DRM_ST_SWC_inst_adr                                                      "0x00A4"
#define ISO_DRM_ST_SWC_inst                                                          0x00A4
#define ISO_DRM_ST_SWC_set_shift                                                     (0)
#define ISO_DRM_ST_SWC_set_mask                                                      (0x00000001)
#define ISO_DRM_ST_SWC_set(data)                                                     (0x00000001&((data)<<0))
#define ISO_DRM_ST_SWC_set_src(data)                                                 ((0x00000001&(data))>>0)
#define ISO_DRM_ST_SWC_get_set(data)                                                 ((0x00000001&(data))>>0)


#define ISO_DRM_SECURE_CLK_SWC                                                       0x98007694
#define ISO_DRM_SECURE_CLK_SWC_reg_addr                                              "0x98007694"
#define ISO_DRM_SECURE_CLK_SWC_reg                                                   0x98007694
#define set_ISO_DRM_SECURE_CLK_SWC_reg(data)   (*((volatile unsigned int*) ISO_DRM_SECURE_CLK_SWC_reg)=data)
#define get_ISO_DRM_SECURE_CLK_SWC_reg   (*((volatile unsigned int*) ISO_DRM_SECURE_CLK_SWC_reg))
#define ISO_DRM_SECURE_CLK_SWC_inst_adr                                              "0x00A5"
#define ISO_DRM_SECURE_CLK_SWC_inst                                                  0x00A5
#define ISO_DRM_SECURE_CLK_SWC_val_shift                                             (0)
#define ISO_DRM_SECURE_CLK_SWC_val_mask                                              (0xFFFFFFFF)
#define ISO_DRM_SECURE_CLK_SWC_val(data)                                             (0xFFFFFFFF&((data)<<0))
#define ISO_DRM_SECURE_CLK_SWC_val_src(data)                                         ((0xFFFFFFFF&(data))>>0)
#define ISO_DRM_SECURE_CLK_SWC_get_val(data)                                         ((0xFFFFFFFF&(data))>>0)


#define ISO_DRM_ELAPSED_SWC                                                          0x98007698
#define ISO_DRM_ELAPSED_SWC_reg_addr                                                 "0x98007698"
#define ISO_DRM_ELAPSED_SWC_reg                                                      0x98007698
#define set_ISO_DRM_ELAPSED_SWC_reg(data)   (*((volatile unsigned int*) ISO_DRM_ELAPSED_SWC_reg)=data)
#define get_ISO_DRM_ELAPSED_SWC_reg   (*((volatile unsigned int*) ISO_DRM_ELAPSED_SWC_reg))
#define ISO_DRM_ELAPSED_SWC_inst_adr                                                 "0x00A6"
#define ISO_DRM_ELAPSED_SWC_inst                                                     0x00A6
#define ISO_DRM_ELAPSED_SWC_val_shift                                                (0)
#define ISO_DRM_ELAPSED_SWC_val_mask                                                 (0xFFFFFFFF)
#define ISO_DRM_ELAPSED_SWC_val(data)                                                (0xFFFFFFFF&((data)<<0))
#define ISO_DRM_ELAPSED_SWC_val_src(data)                                            ((0xFFFFFFFF&(data))>>0)
#define ISO_DRM_ELAPSED_SWC_get_val(data)                                            ((0xFFFFFFFF&(data))>>0)


#define ISO_DRM_CTRL_SWC                                                             0x9800769C
#define ISO_DRM_CTRL_SWC_reg_addr                                                    "0x9800769C"
#define ISO_DRM_CTRL_SWC_reg                                                         0x9800769C
#define set_ISO_DRM_CTRL_SWC_reg(data)   (*((volatile unsigned int*) ISO_DRM_CTRL_SWC_reg)=data)
#define get_ISO_DRM_CTRL_SWC_reg   (*((volatile unsigned int*) ISO_DRM_CTRL_SWC_reg))
#define ISO_DRM_CTRL_SWC_inst_adr                                                    "0x00A7"
#define ISO_DRM_CTRL_SWC_inst                                                        0x00A7
#define ISO_DRM_CTRL_SWC_clk_div_en_shift                                            (1)
#define ISO_DRM_CTRL_SWC_clk_div_en_mask                                             (0x00000002)
#define ISO_DRM_CTRL_SWC_clk_div_en(data)                                            (0x00000002&((data)<<1))
#define ISO_DRM_CTRL_SWC_clk_div_en_src(data)                                        ((0x00000002&(data))>>1)
#define ISO_DRM_CTRL_SWC_get_clk_div_en(data)                                        ((0x00000002&(data))>>1)
#define ISO_DRM_CTRL_SWC_clk_sel_shift                                               (0)
#define ISO_DRM_CTRL_SWC_clk_sel_mask                                                (0x00000001)
#define ISO_DRM_CTRL_SWC_clk_sel(data)                                               (0x00000001&((data)<<0))
#define ISO_DRM_CTRL_SWC_clk_sel_src(data)                                           ((0x00000001&(data))>>0)
#define ISO_DRM_CTRL_SWC_get_clk_sel(data)                                           ((0x00000001&(data))>>0)


#define ISO_DRM_CLK_DIV_SWC                                                          0x980076A0
#define ISO_DRM_CLK_DIV_SWC_reg_addr                                                 "0x980076A0"
#define ISO_DRM_CLK_DIV_SWC_reg                                                      0x980076A0
#define set_ISO_DRM_CLK_DIV_SWC_reg(data)   (*((volatile unsigned int*) ISO_DRM_CLK_DIV_SWC_reg)=data)
#define get_ISO_DRM_CLK_DIV_SWC_reg   (*((volatile unsigned int*) ISO_DRM_CLK_DIV_SWC_reg))
#define ISO_DRM_CLK_DIV_SWC_inst_adr                                                 "0x00A8"
#define ISO_DRM_CLK_DIV_SWC_inst                                                     0x00A8
#define ISO_DRM_CLK_DIV_SWC_init_shift                                               (0)
#define ISO_DRM_CLK_DIV_SWC_init_mask                                                (0xFFFFFFFF)
#define ISO_DRM_CLK_DIV_SWC_init(data)                                               (0xFFFFFFFF&((data)<<0))
#define ISO_DRM_CLK_DIV_SWC_init_src(data)                                           ((0xFFFFFFFF&(data))>>0)
#define ISO_DRM_CLK_DIV_SWC_get_init(data)                                           ((0xFFFFFFFF&(data))>>0)


#define ISO_COLD_RST_SWC                                                             0x980076A4
#define ISO_COLD_RST_SWC_reg_addr                                                    "0x980076A4"
#define ISO_COLD_RST_SWC_reg                                                         0x980076A4
#define set_ISO_COLD_RST_SWC_reg(data)   (*((volatile unsigned int*) ISO_COLD_RST_SWC_reg)=data)
#define get_ISO_COLD_RST_SWC_reg   (*((volatile unsigned int*) ISO_COLD_RST_SWC_reg))
#define ISO_COLD_RST_SWC_inst_adr                                                    "0x00A9"
#define ISO_COLD_RST_SWC_inst                                                        0x00A9
#define ISO_COLD_RST_SWC_val_shift                                                   (0)
#define ISO_COLD_RST_SWC_val_mask                                                    (0xFFFFFFFF)
#define ISO_COLD_RST_SWC_val(data)                                                   (0xFFFFFFFF&((data)<<0))
#define ISO_COLD_RST_SWC_val_src(data)                                               ((0xFFFFFFFF&(data))>>0)
#define ISO_COLD_RST_SWC_get_val(data)                                               ((0xFFFFFFFF&(data))>>0)


#define ISO_COLD_RST1_SWC                                                            0x980076A8
#define ISO_COLD_RST1_SWC_reg_addr                                                   "0x980076A8"
#define ISO_COLD_RST1_SWC_reg                                                        0x980076A8
#define set_ISO_COLD_RST1_SWC_reg(data)   (*((volatile unsigned int*) ISO_COLD_RST1_SWC_reg)=data)
#define get_ISO_COLD_RST1_SWC_reg   (*((volatile unsigned int*) ISO_COLD_RST1_SWC_reg))
#define ISO_COLD_RST1_SWC_inst_adr                                                   "0x00AA"
#define ISO_COLD_RST1_SWC_inst                                                       0x00AA
#define ISO_COLD_RST1_SWC_val_shift                                                  (0)
#define ISO_COLD_RST1_SWC_val_mask                                                   (0xFFFFFFFF)
#define ISO_COLD_RST1_SWC_val(data)                                                  (0xFFFFFFFF&((data)<<0))
#define ISO_COLD_RST1_SWC_val_src(data)                                              ((0xFFFFFFFF&(data))>>0)
#define ISO_COLD_RST1_SWC_get_val(data)                                              ((0xFFFFFFFF&(data))>>0)


#define ISO_COLD_RST2_SWC                                                            0x980076AC
#define ISO_COLD_RST2_SWC_reg_addr                                                   "0x980076AC"
#define ISO_COLD_RST2_SWC_reg                                                        0x980076AC
#define set_ISO_COLD_RST2_SWC_reg(data)   (*((volatile unsigned int*) ISO_COLD_RST2_SWC_reg)=data)
#define get_ISO_COLD_RST2_SWC_reg   (*((volatile unsigned int*) ISO_COLD_RST2_SWC_reg))
#define ISO_COLD_RST2_SWC_inst_adr                                                   "0x00AB"
#define ISO_COLD_RST2_SWC_inst                                                       0x00AB
#define ISO_COLD_RST2_SWC_val_shift                                                  (0)
#define ISO_COLD_RST2_SWC_val_mask                                                   (0xFFFFFFFF)
#define ISO_COLD_RST2_SWC_val(data)                                                  (0xFFFFFFFF&((data)<<0))
#define ISO_COLD_RST2_SWC_val_src(data)                                              ((0xFFFFFFFF&(data))>>0)
#define ISO_COLD_RST2_SWC_get_val(data)                                              ((0xFFFFFFFF&(data))>>0)


#define ISO_COLD_RST3_SWC                                                            0x980076B0
#define ISO_COLD_RST3_SWC_reg_addr                                                   "0x980076B0"
#define ISO_COLD_RST3_SWC_reg                                                        0x980076B0
#define set_ISO_COLD_RST3_SWC_reg(data)   (*((volatile unsigned int*) ISO_COLD_RST3_SWC_reg)=data)
#define get_ISO_COLD_RST3_SWC_reg   (*((volatile unsigned int*) ISO_COLD_RST3_SWC_reg))
#define ISO_COLD_RST3_SWC_inst_adr                                                   "0x00AC"
#define ISO_COLD_RST3_SWC_inst                                                       0x00AC
#define ISO_COLD_RST3_SWC_val_shift                                                  (0)
#define ISO_COLD_RST3_SWC_val_mask                                                   (0xFFFFFFFF)
#define ISO_COLD_RST3_SWC_val(data)                                                  (0xFFFFFFFF&((data)<<0))
#define ISO_COLD_RST3_SWC_val_src(data)                                              ((0xFFFFFFFF&(data))>>0)
#define ISO_COLD_RST3_SWC_get_val(data)                                              ((0xFFFFFFFF&(data))>>0)


#define ISO_NORST_SWC                                                                0x980076B4
#define ISO_NORST_SWC_reg_addr                                                       "0x980076B4"
#define ISO_NORST_SWC_reg                                                            0x980076B4
#define set_ISO_NORST_SWC_reg(data)   (*((volatile unsigned int*) ISO_NORST_SWC_reg)=data)
#define get_ISO_NORST_SWC_reg   (*((volatile unsigned int*) ISO_NORST_SWC_reg))
#define ISO_NORST_SWC_inst_adr                                                       "0x00AD"
#define ISO_NORST_SWC_inst                                                           0x00AD
#define ISO_NORST_SWC_dat_shift                                                      (0)
#define ISO_NORST_SWC_dat_mask                                                       (0xFFFFFFFF)
#define ISO_NORST_SWC_dat(data)                                                      (0xFFFFFFFF&((data)<<0))
#define ISO_NORST_SWC_dat_src(data)                                                  ((0xFFFFFFFF&(data))>>0)
#define ISO_NORST_SWC_get_dat(data)                                                  ((0xFFFFFFFF&(data))>>0)


#define ISO_NORST1_SWC                                                               0x980076B8
#define ISO_NORST1_SWC_reg_addr                                                      "0x980076B8"
#define ISO_NORST1_SWC_reg                                                           0x980076B8
#define set_ISO_NORST1_SWC_reg(data)   (*((volatile unsigned int*) ISO_NORST1_SWC_reg)=data)
#define get_ISO_NORST1_SWC_reg   (*((volatile unsigned int*) ISO_NORST1_SWC_reg))
#define ISO_NORST1_SWC_inst_adr                                                      "0x00AE"
#define ISO_NORST1_SWC_inst                                                          0x00AE
#define ISO_NORST1_SWC_dat_shift                                                     (0)
#define ISO_NORST1_SWC_dat_mask                                                      (0xFFFFFFFF)
#define ISO_NORST1_SWC_dat(data)                                                     (0xFFFFFFFF&((data)<<0))
#define ISO_NORST1_SWC_dat_src(data)                                                 ((0xFFFFFFFF&(data))>>0)
#define ISO_NORST1_SWC_get_dat(data)                                                 ((0xFFFFFFFF&(data))>>0)


#define ISO_NORST2_SWC                                                               0x980076BC
#define ISO_NORST2_SWC_reg_addr                                                      "0x980076BC"
#define ISO_NORST2_SWC_reg                                                           0x980076BC
#define set_ISO_NORST2_SWC_reg(data)   (*((volatile unsigned int*) ISO_NORST2_SWC_reg)=data)
#define get_ISO_NORST2_SWC_reg   (*((volatile unsigned int*) ISO_NORST2_SWC_reg))
#define ISO_NORST2_SWC_inst_adr                                                      "0x00AF"
#define ISO_NORST2_SWC_inst                                                          0x00AF
#define ISO_NORST2_SWC_dat_shift                                                     (0)
#define ISO_NORST2_SWC_dat_mask                                                      (0xFFFFFFFF)
#define ISO_NORST2_SWC_dat(data)                                                     (0xFFFFFFFF&((data)<<0))
#define ISO_NORST2_SWC_dat_src(data)                                                 ((0xFFFFFFFF&(data))>>0)
#define ISO_NORST2_SWC_get_dat(data)                                                 ((0xFFFFFFFF&(data))>>0)


#define ISO_TCWOV_RSTB_CNT                                                           0x980076C0
#define ISO_TCWOV_RSTB_CNT_reg_addr                                                  "0x980076C0"
#define ISO_TCWOV_RSTB_CNT_reg                                                       0x980076C0
#define set_ISO_TCWOV_RSTB_CNT_reg(data)   (*((volatile unsigned int*) ISO_TCWOV_RSTB_CNT_reg)=data)
#define get_ISO_TCWOV_RSTB_CNT_reg   (*((volatile unsigned int*) ISO_TCWOV_RSTB_CNT_reg))
#define ISO_TCWOV_RSTB_CNT_inst_adr                                                  "0x00B0"
#define ISO_TCWOV_RSTB_CNT_inst                                                      0x00B0
#define ISO_TCWOV_RSTB_CNT_sel_shift                                                 (0)
#define ISO_TCWOV_RSTB_CNT_sel_mask                                                  (0xFFFFFFFF)
#define ISO_TCWOV_RSTB_CNT_sel(data)                                                 (0xFFFFFFFF&((data)<<0))
#define ISO_TCWOV_RSTB_CNT_sel_src(data)                                             ((0xFFFFFFFF&(data))>>0)
#define ISO_TCWOV_RSTB_CNT_get_sel(data)                                             ((0xFFFFFFFF&(data))>>0)


#define ISO_TCWOV_RSTB_PAD                                                           0x980076C4
#define ISO_TCWOV_RSTB_PAD_reg_addr                                                  "0x980076C4"
#define ISO_TCWOV_RSTB_PAD_reg                                                       0x980076C4
#define set_ISO_TCWOV_RSTB_PAD_reg(data)   (*((volatile unsigned int*) ISO_TCWOV_RSTB_PAD_reg)=data)
#define get_ISO_TCWOV_RSTB_PAD_reg   (*((volatile unsigned int*) ISO_TCWOV_RSTB_PAD_reg))
#define ISO_TCWOV_RSTB_PAD_inst_adr                                                  "0x00B1"
#define ISO_TCWOV_RSTB_PAD_inst                                                      0x00B1
#define ISO_TCWOV_RSTB_PAD_dmy_shift                                                 (1)
#define ISO_TCWOV_RSTB_PAD_dmy_mask                                                  (0x00000002)
#define ISO_TCWOV_RSTB_PAD_dmy(data)                                                 (0x00000002&((data)<<1))
#define ISO_TCWOV_RSTB_PAD_dmy_src(data)                                             ((0x00000002&(data))>>1)
#define ISO_TCWOV_RSTB_PAD_get_dmy(data)                                             ((0x00000002&(data))>>1)
#define ISO_TCWOV_RSTB_PAD_oe_shift                                                  (0)
#define ISO_TCWOV_RSTB_PAD_oe_mask                                                   (0x00000001)
#define ISO_TCWOV_RSTB_PAD_oe(data)                                                  (0x00000001&((data)<<0))
#define ISO_TCWOV_RSTB_PAD_oe_src(data)                                              ((0x00000001&(data))>>0)
#define ISO_TCWOV_RSTB_PAD_get_oe(data)                                              ((0x00000001&(data))>>0)


#define ISO_CPU_ST2V                                                                 0x98007738
#define ISO_CPU_ST2V_reg_addr                                                        "0x98007738"
#define ISO_CPU_ST2V_reg                                                             0x98007738
#define set_ISO_CPU_ST2V_reg(data)   (*((volatile unsigned int*) ISO_CPU_ST2V_reg)=data)
#define get_ISO_CPU_ST2V_reg   (*((volatile unsigned int*) ISO_CPU_ST2V_reg))
#define ISO_CPU_ST2V_inst_adr                                                        "0x00CE"
#define ISO_CPU_ST2V_inst                                                            0x00CE
#define ISO_CPU_ST2V_scpu_boot_info_valid_shift                                      (0)
#define ISO_CPU_ST2V_scpu_boot_info_valid_mask                                       (0x00000001)
#define ISO_CPU_ST2V_scpu_boot_info_valid(data)                                      (0x00000001&((data)<<0))
#define ISO_CPU_ST2V_scpu_boot_info_valid_src(data)                                  ((0x00000001&(data))>>0)
#define ISO_CPU_ST2V_get_scpu_boot_info_valid(data)                                  ((0x00000001&(data))>>0)


#define ISO_CPU_ST2                                                                  0x9800773C
#define ISO_CPU_ST2_reg_addr                                                         "0x9800773C"
#define ISO_CPU_ST2_reg                                                              0x9800773C
#define set_ISO_CPU_ST2_reg(data)   (*((volatile unsigned int*) ISO_CPU_ST2_reg)=data)
#define get_ISO_CPU_ST2_reg   (*((volatile unsigned int*) ISO_CPU_ST2_reg))
#define ISO_CPU_ST2_inst_adr                                                         "0x00CF"
#define ISO_CPU_ST2_inst                                                             0x00CF
#define ISO_CPU_ST2_scpu_boot_info_shift                                             (0)
#define ISO_CPU_ST2_scpu_boot_info_mask                                              (0xFFFFFFFF)
#define ISO_CPU_ST2_scpu_boot_info(data)                                             (0xFFFFFFFF&((data)<<0))
#define ISO_CPU_ST2_scpu_boot_info_src(data)                                         ((0xFFFFFFFF&(data))>>0)
#define ISO_CPU_ST2_get_scpu_boot_info(data)                                         ((0xFFFFFFFF&(data))>>0)


#define ISO_ACPU_DBG                                                                 0x98007740
#define ISO_ACPU_DBG_reg_addr                                                        "0x98007740"
#define ISO_ACPU_DBG_reg                                                             0x98007740
#define set_ISO_ACPU_DBG_reg(data)   (*((volatile unsigned int*) ISO_ACPU_DBG_reg)=data)
#define get_ISO_ACPU_DBG_reg   (*((volatile unsigned int*) ISO_ACPU_DBG_reg))
#define ISO_ACPU_DBG_inst_adr                                                        "0x00D0"
#define ISO_ACPU_DBG_inst                                                            0x00D0
#define ISO_ACPU_DBG_write_enable3_shift                                             (13)
#define ISO_ACPU_DBG_write_enable3_mask                                              (0x00002000)
#define ISO_ACPU_DBG_write_enable3(data)                                             (0x00002000&((data)<<13))
#define ISO_ACPU_DBG_write_enable3_src(data)                                         ((0x00002000&(data))>>13)
#define ISO_ACPU_DBG_get_write_enable3(data)                                         ((0x00002000&(data))>>13)
#define ISO_ACPU_DBG_sel1_shift                                                      (8)
#define ISO_ACPU_DBG_sel1_mask                                                       (0x00001F00)
#define ISO_ACPU_DBG_sel1(data)                                                      (0x00001F00&((data)<<8))
#define ISO_ACPU_DBG_sel1_src(data)                                                  ((0x00001F00&(data))>>8)
#define ISO_ACPU_DBG_get_sel1(data)                                                  ((0x00001F00&(data))>>8)
#define ISO_ACPU_DBG_write_enable2_shift                                             (7)
#define ISO_ACPU_DBG_write_enable2_mask                                              (0x00000080)
#define ISO_ACPU_DBG_write_enable2(data)                                             (0x00000080&((data)<<7))
#define ISO_ACPU_DBG_write_enable2_src(data)                                         ((0x00000080&(data))>>7)
#define ISO_ACPU_DBG_get_write_enable2(data)                                         ((0x00000080&(data))>>7)
#define ISO_ACPU_DBG_sel0_shift                                                      (2)
#define ISO_ACPU_DBG_sel0_mask                                                       (0x0000007C)
#define ISO_ACPU_DBG_sel0(data)                                                      (0x0000007C&((data)<<2))
#define ISO_ACPU_DBG_sel0_src(data)                                                  ((0x0000007C&(data))>>2)
#define ISO_ACPU_DBG_get_sel0(data)                                                  ((0x0000007C&(data))>>2)
#define ISO_ACPU_DBG_write_enable1_shift                                             (1)
#define ISO_ACPU_DBG_write_enable1_mask                                              (0x00000002)
#define ISO_ACPU_DBG_write_enable1(data)                                             (0x00000002&((data)<<1))
#define ISO_ACPU_DBG_write_enable1_src(data)                                         ((0x00000002&(data))>>1)
#define ISO_ACPU_DBG_get_write_enable1(data)                                         ((0x00000002&(data))>>1)
#define ISO_ACPU_DBG_enable_shift                                                    (0)
#define ISO_ACPU_DBG_enable_mask                                                     (0x00000001)
#define ISO_ACPU_DBG_enable(data)                                                    (0x00000001&((data)<<0))
#define ISO_ACPU_DBG_enable_src(data)                                                ((0x00000001&(data))>>0)
#define ISO_ACPU_DBG_get_enable(data)                                                ((0x00000001&(data))>>0)


#define ISO_ANLG                                                                     0x98007744
#define ISO_ANLG_reg_addr                                                            "0x98007744"
#define ISO_ANLG_reg                                                                 0x98007744
#define set_ISO_ANLG_reg(data)   (*((volatile unsigned int*) ISO_ANLG_reg)=data)
#define get_ISO_ANLG_reg   (*((volatile unsigned int*) ISO_ANLG_reg))
#define ISO_ANLG_inst_adr                                                            "0x00D1"
#define ISO_ANLG_inst                                                                0x00D1
#define ISO_ANLG_analogy_mode_in_shift                                               (0)
#define ISO_ANLG_analogy_mode_in_mask                                                (0x00000001)
#define ISO_ANLG_analogy_mode_in(data)                                               (0x00000001&((data)<<0))
#define ISO_ANLG_analogy_mode_in_src(data)                                           ((0x00000001&(data))>>0)
#define ISO_ANLG_get_analogy_mode_in(data)                                           ((0x00000001&(data))>>0)


#define ISO_U0RBR_THR_DLL                                                            0x98007800
#define ISO_U0RBR_THR_DLL_reg_addr                                                   "0x98007800"
#define ISO_U0RBR_THR_DLL_reg                                                        0x98007800
#define set_ISO_U0RBR_THR_DLL_reg(data)   (*((volatile unsigned int*) ISO_U0RBR_THR_DLL_reg)=data)
#define get_ISO_U0RBR_THR_DLL_reg   (*((volatile unsigned int*) ISO_U0RBR_THR_DLL_reg))
#define ISO_U0RBR_THR_DLL_inst_adr                                                   "0x0000"
#define ISO_U0RBR_THR_DLL_inst                                                       0x0000
#define ISO_U0RBR_THR_DLL_dll_shift                                                  (0)
#define ISO_U0RBR_THR_DLL_dll_mask                                                   (0x000000FF)
#define ISO_U0RBR_THR_DLL_dll(data)                                                  (0x000000FF&((data)<<0))
#define ISO_U0RBR_THR_DLL_dll_src(data)                                              ((0x000000FF&(data))>>0)
#define ISO_U0RBR_THR_DLL_get_dll(data)                                              ((0x000000FF&(data))>>0)


#define ISO_U0IER_DLH                                                                0x98007804
#define ISO_U0IER_DLH_reg_addr                                                       "0x98007804"
#define ISO_U0IER_DLH_reg                                                            0x98007804
#define set_ISO_U0IER_DLH_reg(data)   (*((volatile unsigned int*) ISO_U0IER_DLH_reg)=data)
#define get_ISO_U0IER_DLH_reg   (*((volatile unsigned int*) ISO_U0IER_DLH_reg))
#define ISO_U0IER_DLH_inst_adr                                                       "0x0001"
#define ISO_U0IER_DLH_inst                                                           0x0001
#define ISO_U0IER_DLH_dlh_shift                                                      (0)
#define ISO_U0IER_DLH_dlh_mask                                                       (0x000000FF)
#define ISO_U0IER_DLH_dlh(data)                                                      (0x000000FF&((data)<<0))
#define ISO_U0IER_DLH_dlh_src(data)                                                  ((0x000000FF&(data))>>0)
#define ISO_U0IER_DLH_get_dlh(data)                                                  ((0x000000FF&(data))>>0)


#define ISO_U0IIR_FCR                                                                0x98007808
#define ISO_U0IIR_FCR_reg_addr                                                       "0x98007808"
#define ISO_U0IIR_FCR_reg                                                            0x98007808
#define set_ISO_U0IIR_FCR_reg(data)   (*((volatile unsigned int*) ISO_U0IIR_FCR_reg)=data)
#define get_ISO_U0IIR_FCR_reg   (*((volatile unsigned int*) ISO_U0IIR_FCR_reg))
#define ISO_U0IIR_FCR_inst_adr                                                       "0x0002"
#define ISO_U0IIR_FCR_inst                                                           0x0002
#define ISO_U0IIR_FCR_fifo16_shift                                                   (6)
#define ISO_U0IIR_FCR_fifo16_mask                                                    (0x000000C0)
#define ISO_U0IIR_FCR_fifo16(data)                                                   (0x000000C0&((data)<<6))
#define ISO_U0IIR_FCR_fifo16_src(data)                                               ((0x000000C0&(data))>>6)
#define ISO_U0IIR_FCR_get_fifo16(data)                                               ((0x000000C0&(data))>>6)
#define ISO_U0IIR_FCR_iid_shift                                                      (0)
#define ISO_U0IIR_FCR_iid_mask                                                       (0x0000000F)
#define ISO_U0IIR_FCR_iid(data)                                                      (0x0000000F&((data)<<0))
#define ISO_U0IIR_FCR_iid_src(data)                                                  ((0x0000000F&(data))>>0)
#define ISO_U0IIR_FCR_get_iid(data)                                                  ((0x0000000F&(data))>>0)


#define ISO_U0LCR                                                                    0x9800780C
#define ISO_U0LCR_reg_addr                                                           "0x9800780C"
#define ISO_U0LCR_reg                                                                0x9800780C
#define set_ISO_U0LCR_reg(data)   (*((volatile unsigned int*) ISO_U0LCR_reg)=data)
#define get_ISO_U0LCR_reg   (*((volatile unsigned int*) ISO_U0LCR_reg))
#define ISO_U0LCR_inst_adr                                                           "0x0003"
#define ISO_U0LCR_inst                                                               0x0003
#define ISO_U0LCR_dlab_shift                                                         (7)
#define ISO_U0LCR_dlab_mask                                                          (0x00000080)
#define ISO_U0LCR_dlab(data)                                                         (0x00000080&((data)<<7))
#define ISO_U0LCR_dlab_src(data)                                                     ((0x00000080&(data))>>7)
#define ISO_U0LCR_get_dlab(data)                                                     ((0x00000080&(data))>>7)
#define ISO_U0LCR_brk_shift                                                          (6)
#define ISO_U0LCR_brk_mask                                                           (0x00000040)
#define ISO_U0LCR_brk(data)                                                          (0x00000040&((data)<<6))
#define ISO_U0LCR_brk_src(data)                                                      ((0x00000040&(data))>>6)
#define ISO_U0LCR_get_brk(data)                                                      ((0x00000040&(data))>>6)
#define ISO_U0LCR_eps_shift                                                          (4)
#define ISO_U0LCR_eps_mask                                                           (0x00000010)
#define ISO_U0LCR_eps(data)                                                          (0x00000010&((data)<<4))
#define ISO_U0LCR_eps_src(data)                                                      ((0x00000010&(data))>>4)
#define ISO_U0LCR_get_eps(data)                                                      ((0x00000010&(data))>>4)
#define ISO_U0LCR_pen_shift                                                          (3)
#define ISO_U0LCR_pen_mask                                                           (0x00000008)
#define ISO_U0LCR_pen(data)                                                          (0x00000008&((data)<<3))
#define ISO_U0LCR_pen_src(data)                                                      ((0x00000008&(data))>>3)
#define ISO_U0LCR_get_pen(data)                                                      ((0x00000008&(data))>>3)
#define ISO_U0LCR_stb_shift                                                          (2)
#define ISO_U0LCR_stb_mask                                                           (0x00000004)
#define ISO_U0LCR_stb(data)                                                          (0x00000004&((data)<<2))
#define ISO_U0LCR_stb_src(data)                                                      ((0x00000004&(data))>>2)
#define ISO_U0LCR_get_stb(data)                                                      ((0x00000004&(data))>>2)
#define ISO_U0LCR_wls_shift                                                          (0)
#define ISO_U0LCR_wls_mask                                                           (0x00000003)
#define ISO_U0LCR_wls(data)                                                          (0x00000003&((data)<<0))
#define ISO_U0LCR_wls_src(data)                                                      ((0x00000003&(data))>>0)
#define ISO_U0LCR_get_wls(data)                                                      ((0x00000003&(data))>>0)


#define ISO_U0MCR                                                                    0x98007810
#define ISO_U0MCR_reg_addr                                                           "0x98007810"
#define ISO_U0MCR_reg                                                                0x98007810
#define set_ISO_U0MCR_reg(data)   (*((volatile unsigned int*) ISO_U0MCR_reg)=data)
#define get_ISO_U0MCR_reg   (*((volatile unsigned int*) ISO_U0MCR_reg))
#define ISO_U0MCR_inst_adr                                                           "0x0004"
#define ISO_U0MCR_inst                                                               0x0004
#define ISO_U0MCR_afce_shift                                                         (5)
#define ISO_U0MCR_afce_mask                                                          (0x00000020)
#define ISO_U0MCR_afce(data)                                                         (0x00000020&((data)<<5))
#define ISO_U0MCR_afce_src(data)                                                     ((0x00000020&(data))>>5)
#define ISO_U0MCR_get_afce(data)                                                     ((0x00000020&(data))>>5)
#define ISO_U0MCR_loop_shift                                                         (4)
#define ISO_U0MCR_loop_mask                                                          (0x00000010)
#define ISO_U0MCR_loop(data)                                                         (0x00000010&((data)<<4))
#define ISO_U0MCR_loop_src(data)                                                     ((0x00000010&(data))>>4)
#define ISO_U0MCR_get_loop(data)                                                     ((0x00000010&(data))>>4)
#define ISO_U0MCR_rts_shift                                                          (1)
#define ISO_U0MCR_rts_mask                                                           (0x00000002)
#define ISO_U0MCR_rts(data)                                                          (0x00000002&((data)<<1))
#define ISO_U0MCR_rts_src(data)                                                      ((0x00000002&(data))>>1)
#define ISO_U0MCR_get_rts(data)                                                      ((0x00000002&(data))>>1)
#define ISO_U0MCR_dtr_shift                                                          (0)
#define ISO_U0MCR_dtr_mask                                                           (0x00000001)
#define ISO_U0MCR_dtr(data)                                                          (0x00000001&((data)<<0))
#define ISO_U0MCR_dtr_src(data)                                                      ((0x00000001&(data))>>0)
#define ISO_U0MCR_get_dtr(data)                                                      ((0x00000001&(data))>>0)


#define ISO_U0LSR                                                                    0x98007814
#define ISO_U0LSR_reg_addr                                                           "0x98007814"
#define ISO_U0LSR_reg                                                                0x98007814
#define set_ISO_U0LSR_reg(data)   (*((volatile unsigned int*) ISO_U0LSR_reg)=data)
#define get_ISO_U0LSR_reg   (*((volatile unsigned int*) ISO_U0LSR_reg))
#define ISO_U0LSR_inst_adr                                                           "0x0005"
#define ISO_U0LSR_inst                                                               0x0005
#define ISO_U0LSR_rfe_shift                                                          (7)
#define ISO_U0LSR_rfe_mask                                                           (0x00000080)
#define ISO_U0LSR_rfe(data)                                                          (0x00000080&((data)<<7))
#define ISO_U0LSR_rfe_src(data)                                                      ((0x00000080&(data))>>7)
#define ISO_U0LSR_get_rfe(data)                                                      ((0x00000080&(data))>>7)
#define ISO_U0LSR_temt_shift                                                         (6)
#define ISO_U0LSR_temt_mask                                                          (0x00000040)
#define ISO_U0LSR_temt(data)                                                         (0x00000040&((data)<<6))
#define ISO_U0LSR_temt_src(data)                                                     ((0x00000040&(data))>>6)
#define ISO_U0LSR_get_temt(data)                                                     ((0x00000040&(data))>>6)
#define ISO_U0LSR_thre_shift                                                         (5)
#define ISO_U0LSR_thre_mask                                                          (0x00000020)
#define ISO_U0LSR_thre(data)                                                         (0x00000020&((data)<<5))
#define ISO_U0LSR_thre_src(data)                                                     ((0x00000020&(data))>>5)
#define ISO_U0LSR_get_thre(data)                                                     ((0x00000020&(data))>>5)
#define ISO_U0LSR_bi_shift                                                           (4)
#define ISO_U0LSR_bi_mask                                                            (0x00000010)
#define ISO_U0LSR_bi(data)                                                           (0x00000010&((data)<<4))
#define ISO_U0LSR_bi_src(data)                                                       ((0x00000010&(data))>>4)
#define ISO_U0LSR_get_bi(data)                                                       ((0x00000010&(data))>>4)
#define ISO_U0LSR_fe_shift                                                           (3)
#define ISO_U0LSR_fe_mask                                                            (0x00000008)
#define ISO_U0LSR_fe(data)                                                           (0x00000008&((data)<<3))
#define ISO_U0LSR_fe_src(data)                                                       ((0x00000008&(data))>>3)
#define ISO_U0LSR_get_fe(data)                                                       ((0x00000008&(data))>>3)
#define ISO_U0LSR_pe_shift                                                           (2)
#define ISO_U0LSR_pe_mask                                                            (0x00000004)
#define ISO_U0LSR_pe(data)                                                           (0x00000004&((data)<<2))
#define ISO_U0LSR_pe_src(data)                                                       ((0x00000004&(data))>>2)
#define ISO_U0LSR_get_pe(data)                                                       ((0x00000004&(data))>>2)
#define ISO_U0LSR_oe_shift                                                           (1)
#define ISO_U0LSR_oe_mask                                                            (0x00000002)
#define ISO_U0LSR_oe(data)                                                           (0x00000002&((data)<<1))
#define ISO_U0LSR_oe_src(data)                                                       ((0x00000002&(data))>>1)
#define ISO_U0LSR_get_oe(data)                                                       ((0x00000002&(data))>>1)
#define ISO_U0LSR_dr_shift                                                           (0)
#define ISO_U0LSR_dr_mask                                                            (0x00000001)
#define ISO_U0LSR_dr(data)                                                           (0x00000001&((data)<<0))
#define ISO_U0LSR_dr_src(data)                                                       ((0x00000001&(data))>>0)
#define ISO_U0LSR_get_dr(data)                                                       ((0x00000001&(data))>>0)


#define ISO_U0MSR                                                                    0x98007818
#define ISO_U0MSR_reg_addr                                                           "0x98007818"
#define ISO_U0MSR_reg                                                                0x98007818
#define set_ISO_U0MSR_reg(data)   (*((volatile unsigned int*) ISO_U0MSR_reg)=data)
#define get_ISO_U0MSR_reg   (*((volatile unsigned int*) ISO_U0MSR_reg))
#define ISO_U0MSR_inst_adr                                                           "0x0006"
#define ISO_U0MSR_inst                                                               0x0006
#define ISO_U0MSR_dcd_shift                                                          (7)
#define ISO_U0MSR_dcd_mask                                                           (0x00000080)
#define ISO_U0MSR_dcd(data)                                                          (0x00000080&((data)<<7))
#define ISO_U0MSR_dcd_src(data)                                                      ((0x00000080&(data))>>7)
#define ISO_U0MSR_get_dcd(data)                                                      ((0x00000080&(data))>>7)
#define ISO_U0MSR_ri_shift                                                           (6)
#define ISO_U0MSR_ri_mask                                                            (0x00000040)
#define ISO_U0MSR_ri(data)                                                           (0x00000040&((data)<<6))
#define ISO_U0MSR_ri_src(data)                                                       ((0x00000040&(data))>>6)
#define ISO_U0MSR_get_ri(data)                                                       ((0x00000040&(data))>>6)
#define ISO_U0MSR_dsr_shift                                                          (5)
#define ISO_U0MSR_dsr_mask                                                           (0x00000020)
#define ISO_U0MSR_dsr(data)                                                          (0x00000020&((data)<<5))
#define ISO_U0MSR_dsr_src(data)                                                      ((0x00000020&(data))>>5)
#define ISO_U0MSR_get_dsr(data)                                                      ((0x00000020&(data))>>5)
#define ISO_U0MSR_cts_shift                                                          (4)
#define ISO_U0MSR_cts_mask                                                           (0x00000010)
#define ISO_U0MSR_cts(data)                                                          (0x00000010&((data)<<4))
#define ISO_U0MSR_cts_src(data)                                                      ((0x00000010&(data))>>4)
#define ISO_U0MSR_get_cts(data)                                                      ((0x00000010&(data))>>4)
#define ISO_U0MSR_ddcd_shift                                                         (3)
#define ISO_U0MSR_ddcd_mask                                                          (0x00000008)
#define ISO_U0MSR_ddcd(data)                                                         (0x00000008&((data)<<3))
#define ISO_U0MSR_ddcd_src(data)                                                     ((0x00000008&(data))>>3)
#define ISO_U0MSR_get_ddcd(data)                                                     ((0x00000008&(data))>>3)
#define ISO_U0MSR_teri_shift                                                         (2)
#define ISO_U0MSR_teri_mask                                                          (0x00000004)
#define ISO_U0MSR_teri(data)                                                         (0x00000004&((data)<<2))
#define ISO_U0MSR_teri_src(data)                                                     ((0x00000004&(data))>>2)
#define ISO_U0MSR_get_teri(data)                                                     ((0x00000004&(data))>>2)
#define ISO_U0MSR_ddsr_shift                                                         (1)
#define ISO_U0MSR_ddsr_mask                                                          (0x00000002)
#define ISO_U0MSR_ddsr(data)                                                         (0x00000002&((data)<<1))
#define ISO_U0MSR_ddsr_src(data)                                                     ((0x00000002&(data))>>1)
#define ISO_U0MSR_get_ddsr(data)                                                     ((0x00000002&(data))>>1)
#define ISO_U0MSR_dcts_shift                                                         (0)
#define ISO_U0MSR_dcts_mask                                                          (0x00000001)
#define ISO_U0MSR_dcts(data)                                                         (0x00000001&((data)<<0))
#define ISO_U0MSR_dcts_src(data)                                                     ((0x00000001&(data))>>0)
#define ISO_U0MSR_get_dcts(data)                                                     ((0x00000001&(data))>>0)


#define ISO_U0SCR                                                                    0x9800781C
#define ISO_U0SCR_reg_addr                                                           "0x9800781C"
#define ISO_U0SCR_reg                                                                0x9800781C
#define set_ISO_U0SCR_reg(data)   (*((volatile unsigned int*) ISO_U0SCR_reg)=data)
#define get_ISO_U0SCR_reg   (*((volatile unsigned int*) ISO_U0SCR_reg))
#define ISO_U0SCR_inst_adr                                                           "0x0007"
#define ISO_U0SCR_inst                                                               0x0007
#define ISO_U0SCR_scr_shift                                                          (0)
#define ISO_U0SCR_scr_mask                                                           (0x000000FF)
#define ISO_U0SCR_scr(data)                                                          (0x000000FF&((data)<<0))
#define ISO_U0SCR_scr_src(data)                                                      ((0x000000FF&(data))>>0)
#define ISO_U0SCR_get_scr(data)                                                      ((0x000000FF&(data))>>0)


#define ISO_U0SRBR_0                                                                 0x98007830
#define ISO_U0SRBR_1                                                                 0x98007834
#define ISO_U0SRBR_2                                                                 0x98007838
#define ISO_U0SRBR_3                                                                 0x9800783C
#define ISO_U0SRBR_4                                                                 0x98007840
#define ISO_U0SRBR_5                                                                 0x98007844
#define ISO_U0SRBR_6                                                                 0x98007848
#define ISO_U0SRBR_7                                                                 0x9800784C
#define ISO_U0SRBR_8                                                                 0x98007850
#define ISO_U0SRBR_9                                                                 0x98007854
#define ISO_U0SRBR_10                                                                 0x98007858
#define ISO_U0SRBR_11                                                                 0x9800785C
#define ISO_U0SRBR_12                                                                 0x98007860
#define ISO_U0SRBR_13                                                                 0x98007864
#define ISO_U0SRBR_14                                                                 0x98007868
#define ISO_U0SRBR_15                                                                 0x9800786C
#define ISO_U0SRBR_0_reg_addr                                                        "0x98007830"
#define ISO_U0SRBR_1_reg_addr                                                        "0x98007834"
#define ISO_U0SRBR_2_reg_addr                                                        "0x98007838"
#define ISO_U0SRBR_3_reg_addr                                                        "0x9800783C"
#define ISO_U0SRBR_4_reg_addr                                                        "0x98007840"
#define ISO_U0SRBR_5_reg_addr                                                        "0x98007844"
#define ISO_U0SRBR_6_reg_addr                                                        "0x98007848"
#define ISO_U0SRBR_7_reg_addr                                                        "0x9800784C"
#define ISO_U0SRBR_8_reg_addr                                                        "0x98007850"
#define ISO_U0SRBR_9_reg_addr                                                        "0x98007854"
#define ISO_U0SRBR_10_reg_addr                                                        "0x98007858"
#define ISO_U0SRBR_11_reg_addr                                                        "0x9800785C"
#define ISO_U0SRBR_12_reg_addr                                                        "0x98007860"
#define ISO_U0SRBR_13_reg_addr                                                        "0x98007864"
#define ISO_U0SRBR_14_reg_addr                                                        "0x98007868"
#define ISO_U0SRBR_15_reg_addr                                                        "0x9800786C"
#define ISO_U0SRBR_0_reg                                                             0x98007830
#define ISO_U0SRBR_1_reg                                                             0x98007834
#define ISO_U0SRBR_2_reg                                                             0x98007838
#define ISO_U0SRBR_3_reg                                                             0x9800783C
#define ISO_U0SRBR_4_reg                                                             0x98007840
#define ISO_U0SRBR_5_reg                                                             0x98007844
#define ISO_U0SRBR_6_reg                                                             0x98007848
#define ISO_U0SRBR_7_reg                                                             0x9800784C
#define ISO_U0SRBR_8_reg                                                             0x98007850
#define ISO_U0SRBR_9_reg                                                             0x98007854
#define ISO_U0SRBR_10_reg                                                             0x98007858
#define ISO_U0SRBR_11_reg                                                             0x9800785C
#define ISO_U0SRBR_12_reg                                                             0x98007860
#define ISO_U0SRBR_13_reg                                                             0x98007864
#define ISO_U0SRBR_14_reg                                                             0x98007868
#define ISO_U0SRBR_15_reg                                                             0x9800786C
#define set_ISO_U0SRBR_0_reg(data)   (*((volatile unsigned int*) ISO_U0SRBR_0_reg)=data)
#define set_ISO_U0SRBR_1_reg(data)   (*((volatile unsigned int*) ISO_U0SRBR_1_reg)=data)
#define set_ISO_U0SRBR_2_reg(data)   (*((volatile unsigned int*) ISO_U0SRBR_2_reg)=data)
#define set_ISO_U0SRBR_3_reg(data)   (*((volatile unsigned int*) ISO_U0SRBR_3_reg)=data)
#define set_ISO_U0SRBR_4_reg(data)   (*((volatile unsigned int*) ISO_U0SRBR_4_reg)=data)
#define set_ISO_U0SRBR_5_reg(data)   (*((volatile unsigned int*) ISO_U0SRBR_5_reg)=data)
#define set_ISO_U0SRBR_6_reg(data)   (*((volatile unsigned int*) ISO_U0SRBR_6_reg)=data)
#define set_ISO_U0SRBR_7_reg(data)   (*((volatile unsigned int*) ISO_U0SRBR_7_reg)=data)
#define set_ISO_U0SRBR_8_reg(data)   (*((volatile unsigned int*) ISO_U0SRBR_8_reg)=data)
#define set_ISO_U0SRBR_9_reg(data)   (*((volatile unsigned int*) ISO_U0SRBR_9_reg)=data)
#define set_ISO_U0SRBR_10_reg(data)   (*((volatile unsigned int*) ISO_U0SRBR_10_reg)=data)
#define set_ISO_U0SRBR_11_reg(data)   (*((volatile unsigned int*) ISO_U0SRBR_11_reg)=data)
#define set_ISO_U0SRBR_12_reg(data)   (*((volatile unsigned int*) ISO_U0SRBR_12_reg)=data)
#define set_ISO_U0SRBR_13_reg(data)   (*((volatile unsigned int*) ISO_U0SRBR_13_reg)=data)
#define set_ISO_U0SRBR_14_reg(data)   (*((volatile unsigned int*) ISO_U0SRBR_14_reg)=data)
#define set_ISO_U0SRBR_15_reg(data)   (*((volatile unsigned int*) ISO_U0SRBR_15_reg)=data)
#define get_ISO_U0SRBR_0_reg   (*((volatile unsigned int*) ISO_U0SRBR_0_reg))
#define get_ISO_U0SRBR_1_reg   (*((volatile unsigned int*) ISO_U0SRBR_1_reg))
#define get_ISO_U0SRBR_2_reg   (*((volatile unsigned int*) ISO_U0SRBR_2_reg))
#define get_ISO_U0SRBR_3_reg   (*((volatile unsigned int*) ISO_U0SRBR_3_reg))
#define get_ISO_U0SRBR_4_reg   (*((volatile unsigned int*) ISO_U0SRBR_4_reg))
#define get_ISO_U0SRBR_5_reg   (*((volatile unsigned int*) ISO_U0SRBR_5_reg))
#define get_ISO_U0SRBR_6_reg   (*((volatile unsigned int*) ISO_U0SRBR_6_reg))
#define get_ISO_U0SRBR_7_reg   (*((volatile unsigned int*) ISO_U0SRBR_7_reg))
#define get_ISO_U0SRBR_8_reg   (*((volatile unsigned int*) ISO_U0SRBR_8_reg))
#define get_ISO_U0SRBR_9_reg   (*((volatile unsigned int*) ISO_U0SRBR_9_reg))
#define get_ISO_U0SRBR_10_reg   (*((volatile unsigned int*) ISO_U0SRBR_10_reg))
#define get_ISO_U0SRBR_11_reg   (*((volatile unsigned int*) ISO_U0SRBR_11_reg))
#define get_ISO_U0SRBR_12_reg   (*((volatile unsigned int*) ISO_U0SRBR_12_reg))
#define get_ISO_U0SRBR_13_reg   (*((volatile unsigned int*) ISO_U0SRBR_13_reg))
#define get_ISO_U0SRBR_14_reg   (*((volatile unsigned int*) ISO_U0SRBR_14_reg))
#define get_ISO_U0SRBR_15_reg   (*((volatile unsigned int*) ISO_U0SRBR_15_reg))
#define ISO_U0SRBR_0_inst_adr                                                        "0x000C"
#define ISO_U0SRBR_1_inst_adr                                                        "0x000D"
#define ISO_U0SRBR_2_inst_adr                                                        "0x000E"
#define ISO_U0SRBR_3_inst_adr                                                        "0x000F"
#define ISO_U0SRBR_4_inst_adr                                                        "0x0010"
#define ISO_U0SRBR_5_inst_adr                                                        "0x0011"
#define ISO_U0SRBR_6_inst_adr                                                        "0x0012"
#define ISO_U0SRBR_7_inst_adr                                                        "0x0013"
#define ISO_U0SRBR_8_inst_adr                                                        "0x0014"
#define ISO_U0SRBR_9_inst_adr                                                        "0x0015"
#define ISO_U0SRBR_10_inst_adr                                                        "0x0016"
#define ISO_U0SRBR_11_inst_adr                                                        "0x0017"
#define ISO_U0SRBR_12_inst_adr                                                        "0x0018"
#define ISO_U0SRBR_13_inst_adr                                                        "0x0019"
#define ISO_U0SRBR_14_inst_adr                                                        "0x001A"
#define ISO_U0SRBR_15_inst_adr                                                        "0x001B"
#define ISO_U0SRBR_0_inst                                                            0x000C
#define ISO_U0SRBR_1_inst                                                            0x000D
#define ISO_U0SRBR_2_inst                                                            0x000E
#define ISO_U0SRBR_3_inst                                                            0x000F
#define ISO_U0SRBR_4_inst                                                            0x0010
#define ISO_U0SRBR_5_inst                                                            0x0011
#define ISO_U0SRBR_6_inst                                                            0x0012
#define ISO_U0SRBR_7_inst                                                            0x0013
#define ISO_U0SRBR_8_inst                                                            0x0014
#define ISO_U0SRBR_9_inst                                                            0x0015
#define ISO_U0SRBR_10_inst                                                            0x0016
#define ISO_U0SRBR_11_inst                                                            0x0017
#define ISO_U0SRBR_12_inst                                                            0x0018
#define ISO_U0SRBR_13_inst                                                            0x0019
#define ISO_U0SRBR_14_inst                                                            0x001A
#define ISO_U0SRBR_15_inst                                                            0x001B
#define ISO_U0SRBR_rbd_shift                                                         (0)
#define ISO_U0SRBR_rbd_mask                                                          (0x000000FF)
#define ISO_U0SRBR_rbd(data)                                                         (0x000000FF&((data)<<0))
#define ISO_U0SRBR_rbd_src(data)                                                     ((0x000000FF&(data))>>0)
#define ISO_U0SRBR_get_rbd(data)                                                     ((0x000000FF&(data))>>0)


#define ISO_U0FAR                                                                    0x98007870
#define ISO_U0FAR_reg_addr                                                           "0x98007870"
#define ISO_U0FAR_reg                                                                0x98007870
#define set_ISO_U0FAR_reg(data)   (*((volatile unsigned int*) ISO_U0FAR_reg)=data)
#define get_ISO_U0FAR_reg   (*((volatile unsigned int*) ISO_U0FAR_reg))
#define ISO_U0FAR_inst_adr                                                           "0x001C"
#define ISO_U0FAR_inst                                                               0x001C
#define ISO_U0FAR_far_shift                                                          (0)
#define ISO_U0FAR_far_mask                                                           (0x00000001)
#define ISO_U0FAR_far(data)                                                          (0x00000001&((data)<<0))
#define ISO_U0FAR_far_src(data)                                                      ((0x00000001&(data))>>0)
#define ISO_U0FAR_get_far(data)                                                      ((0x00000001&(data))>>0)


#define ISO_U0TFR                                                                    0x98007874
#define ISO_U0TFR_reg_addr                                                           "0x98007874"
#define ISO_U0TFR_reg                                                                0x98007874
#define set_ISO_U0TFR_reg(data)   (*((volatile unsigned int*) ISO_U0TFR_reg)=data)
#define get_ISO_U0TFR_reg   (*((volatile unsigned int*) ISO_U0TFR_reg))
#define ISO_U0TFR_inst_adr                                                           "0x001D"
#define ISO_U0TFR_inst                                                               0x001D
#define ISO_U0TFR_far_shift                                                          (0)
#define ISO_U0TFR_far_mask                                                           (0x000000FF)
#define ISO_U0TFR_far(data)                                                          (0x000000FF&((data)<<0))
#define ISO_U0TFR_far_src(data)                                                      ((0x000000FF&(data))>>0)
#define ISO_U0TFR_get_far(data)                                                      ((0x000000FF&(data))>>0)


#define ISO_U0RFW                                                                    0x98007878
#define ISO_U0RFW_reg_addr                                                           "0x98007878"
#define ISO_U0RFW_reg                                                                0x98007878
#define set_ISO_U0RFW_reg(data)   (*((volatile unsigned int*) ISO_U0RFW_reg)=data)
#define get_ISO_U0RFW_reg   (*((volatile unsigned int*) ISO_U0RFW_reg))
#define ISO_U0RFW_inst_adr                                                           "0x001E"
#define ISO_U0RFW_inst                                                               0x001E
#define ISO_U0RFW_rffe_shift                                                         (9)
#define ISO_U0RFW_rffe_mask                                                          (0x00000200)
#define ISO_U0RFW_rffe(data)                                                         (0x00000200&((data)<<9))
#define ISO_U0RFW_rffe_src(data)                                                     ((0x00000200&(data))>>9)
#define ISO_U0RFW_get_rffe(data)                                                     ((0x00000200&(data))>>9)
#define ISO_U0RFW_rfpf_shift                                                         (8)
#define ISO_U0RFW_rfpf_mask                                                          (0x00000100)
#define ISO_U0RFW_rfpf(data)                                                         (0x00000100&((data)<<8))
#define ISO_U0RFW_rfpf_src(data)                                                     ((0x00000100&(data))>>8)
#define ISO_U0RFW_get_rfpf(data)                                                     ((0x00000100&(data))>>8)
#define ISO_U0RFW_rfwd_shift                                                         (0)
#define ISO_U0RFW_rfwd_mask                                                          (0x000000FF)
#define ISO_U0RFW_rfwd(data)                                                         (0x000000FF&((data)<<0))
#define ISO_U0RFW_rfwd_src(data)                                                     ((0x000000FF&(data))>>0)
#define ISO_U0RFW_get_rfwd(data)                                                     ((0x000000FF&(data))>>0)


#define ISO_U0USR                                                                    0x9800787C
#define ISO_U0USR_reg_addr                                                           "0x9800787C"
#define ISO_U0USR_reg                                                                0x9800787C
#define set_ISO_U0USR_reg(data)   (*((volatile unsigned int*) ISO_U0USR_reg)=data)
#define get_ISO_U0USR_reg   (*((volatile unsigned int*) ISO_U0USR_reg))
#define ISO_U0USR_inst_adr                                                           "0x001F"
#define ISO_U0USR_inst                                                               0x001F
#define ISO_U0USR_rff_shift                                                          (4)
#define ISO_U0USR_rff_mask                                                           (0x00000010)
#define ISO_U0USR_rff(data)                                                          (0x00000010&((data)<<4))
#define ISO_U0USR_rff_src(data)                                                      ((0x00000010&(data))>>4)
#define ISO_U0USR_get_rff(data)                                                      ((0x00000010&(data))>>4)
#define ISO_U0USR_rfne_shift                                                         (3)
#define ISO_U0USR_rfne_mask                                                          (0x00000008)
#define ISO_U0USR_rfne(data)                                                         (0x00000008&((data)<<3))
#define ISO_U0USR_rfne_src(data)                                                     ((0x00000008&(data))>>3)
#define ISO_U0USR_get_rfne(data)                                                     ((0x00000008&(data))>>3)
#define ISO_U0USR_tfe_shift                                                          (2)
#define ISO_U0USR_tfe_mask                                                           (0x00000004)
#define ISO_U0USR_tfe(data)                                                          (0x00000004&((data)<<2))
#define ISO_U0USR_tfe_src(data)                                                      ((0x00000004&(data))>>2)
#define ISO_U0USR_get_tfe(data)                                                      ((0x00000004&(data))>>2)
#define ISO_U0USR_tfnf_shift                                                         (1)
#define ISO_U0USR_tfnf_mask                                                          (0x00000002)
#define ISO_U0USR_tfnf(data)                                                         (0x00000002&((data)<<1))
#define ISO_U0USR_tfnf_src(data)                                                     ((0x00000002&(data))>>1)
#define ISO_U0USR_get_tfnf(data)                                                     ((0x00000002&(data))>>1)
#define ISO_U0USR_busy_shift                                                         (0)
#define ISO_U0USR_busy_mask                                                          (0x00000001)
#define ISO_U0USR_busy(data)                                                         (0x00000001&((data)<<0))
#define ISO_U0USR_busy_src(data)                                                     ((0x00000001&(data))>>0)
#define ISO_U0USR_get_busy(data)                                                     ((0x00000001&(data))>>0)


#define ISO_U0TFL                                                                    0x98007880
#define ISO_U0TFL_reg_addr                                                           "0x98007880"
#define ISO_U0TFL_reg                                                                0x98007880
#define set_ISO_U0TFL_reg(data)   (*((volatile unsigned int*) ISO_U0TFL_reg)=data)
#define get_ISO_U0TFL_reg   (*((volatile unsigned int*) ISO_U0TFL_reg))
#define ISO_U0TFL_inst_adr                                                           "0x0020"
#define ISO_U0TFL_inst                                                               0x0020
#define ISO_U0TFL_tfl_shift                                                          (0)
#define ISO_U0TFL_tfl_mask                                                           (0x000000FF)
#define ISO_U0TFL_tfl(data)                                                          (0x000000FF&((data)<<0))
#define ISO_U0TFL_tfl_src(data)                                                      ((0x000000FF&(data))>>0)
#define ISO_U0TFL_get_tfl(data)                                                      ((0x000000FF&(data))>>0)


#define ISO_U0RFL                                                                    0x98007884
#define ISO_U0RFL_reg_addr                                                           "0x98007884"
#define ISO_U0RFL_reg                                                                0x98007884
#define set_ISO_U0RFL_reg(data)   (*((volatile unsigned int*) ISO_U0RFL_reg)=data)
#define get_ISO_U0RFL_reg   (*((volatile unsigned int*) ISO_U0RFL_reg))
#define ISO_U0RFL_inst_adr                                                           "0x0021"
#define ISO_U0RFL_inst                                                               0x0021
#define ISO_U0RFL_rfl_shift                                                          (0)
#define ISO_U0RFL_rfl_mask                                                           (0x000000FF)
#define ISO_U0RFL_rfl(data)                                                          (0x000000FF&((data)<<0))
#define ISO_U0RFL_rfl_src(data)                                                      ((0x000000FF&(data))>>0)
#define ISO_U0RFL_get_rfl(data)                                                      ((0x000000FF&(data))>>0)


#define ISO_U0SRR                                                                    0x98007888
#define ISO_U0SRR_reg_addr                                                           "0x98007888"
#define ISO_U0SRR_reg                                                                0x98007888
#define set_ISO_U0SRR_reg(data)   (*((volatile unsigned int*) ISO_U0SRR_reg)=data)
#define get_ISO_U0SRR_reg   (*((volatile unsigned int*) ISO_U0SRR_reg))
#define ISO_U0SRR_inst_adr                                                           "0x0022"
#define ISO_U0SRR_inst                                                               0x0022
#define ISO_U0SRR_xfr_shift                                                          (2)
#define ISO_U0SRR_xfr_mask                                                           (0x00000004)
#define ISO_U0SRR_xfr(data)                                                          (0x00000004&((data)<<2))
#define ISO_U0SRR_xfr_src(data)                                                      ((0x00000004&(data))>>2)
#define ISO_U0SRR_get_xfr(data)                                                      ((0x00000004&(data))>>2)
#define ISO_U0SRR_rfr_shift                                                          (1)
#define ISO_U0SRR_rfr_mask                                                           (0x00000002)
#define ISO_U0SRR_rfr(data)                                                          (0x00000002&((data)<<1))
#define ISO_U0SRR_rfr_src(data)                                                      ((0x00000002&(data))>>1)
#define ISO_U0SRR_get_rfr(data)                                                      ((0x00000002&(data))>>1)
#define ISO_U0SRR_ur_shift                                                           (0)
#define ISO_U0SRR_ur_mask                                                            (0x00000001)
#define ISO_U0SRR_ur(data)                                                           (0x00000001&((data)<<0))
#define ISO_U0SRR_ur_src(data)                                                       ((0x00000001&(data))>>0)
#define ISO_U0SRR_get_ur(data)                                                       ((0x00000001&(data))>>0)


#define ISO_U0SBCR                                                                   0x98007890
#define ISO_U0SBCR_reg_addr                                                          "0x98007890"
#define ISO_U0SBCR_reg                                                               0x98007890
#define set_ISO_U0SBCR_reg(data)   (*((volatile unsigned int*) ISO_U0SBCR_reg)=data)
#define get_ISO_U0SBCR_reg   (*((volatile unsigned int*) ISO_U0SBCR_reg))
#define ISO_U0SBCR_inst_adr                                                          "0x0024"
#define ISO_U0SBCR_inst                                                              0x0024
#define ISO_U0SBCR_sbcr_shift                                                        (0)
#define ISO_U0SBCR_sbcr_mask                                                         (0x00000001)
#define ISO_U0SBCR_sbcr(data)                                                        (0x00000001&((data)<<0))
#define ISO_U0SBCR_sbcr_src(data)                                                    ((0x00000001&(data))>>0)
#define ISO_U0SBCR_get_sbcr(data)                                                    ((0x00000001&(data))>>0)


#define ISO_U0SDMAM                                                                  0x98007894
#define ISO_U0SDMAM_reg_addr                                                         "0x98007894"
#define ISO_U0SDMAM_reg                                                              0x98007894
#define set_ISO_U0SDMAM_reg(data)   (*((volatile unsigned int*) ISO_U0SDMAM_reg)=data)
#define get_ISO_U0SDMAM_reg   (*((volatile unsigned int*) ISO_U0SDMAM_reg))
#define ISO_U0SDMAM_inst_adr                                                         "0x0025"
#define ISO_U0SDMAM_inst                                                             0x0025
#define ISO_U0SDMAM_sdmam_shift                                                      (0)
#define ISO_U0SDMAM_sdmam_mask                                                       (0x00000001)
#define ISO_U0SDMAM_sdmam(data)                                                      (0x00000001&((data)<<0))
#define ISO_U0SDMAM_sdmam_src(data)                                                  ((0x00000001&(data))>>0)
#define ISO_U0SDMAM_get_sdmam(data)                                                  ((0x00000001&(data))>>0)


#define ISO_U0SFE                                                                    0x98007898
#define ISO_U0SFE_reg_addr                                                           "0x98007898"
#define ISO_U0SFE_reg                                                                0x98007898
#define set_ISO_U0SFE_reg(data)   (*((volatile unsigned int*) ISO_U0SFE_reg)=data)
#define get_ISO_U0SFE_reg   (*((volatile unsigned int*) ISO_U0SFE_reg))
#define ISO_U0SFE_inst_adr                                                           "0x0026"
#define ISO_U0SFE_inst                                                               0x0026
#define ISO_U0SFE_sfe_shift                                                          (0)
#define ISO_U0SFE_sfe_mask                                                           (0x00000001)
#define ISO_U0SFE_sfe(data)                                                          (0x00000001&((data)<<0))
#define ISO_U0SFE_sfe_src(data)                                                      ((0x00000001&(data))>>0)
#define ISO_U0SFE_get_sfe(data)                                                      ((0x00000001&(data))>>0)


#define ISO_U0SRT                                                                    0x9800789C
#define ISO_U0SRT_reg_addr                                                           "0x9800789C"
#define ISO_U0SRT_reg                                                                0x9800789C
#define set_ISO_U0SRT_reg(data)   (*((volatile unsigned int*) ISO_U0SRT_reg)=data)
#define get_ISO_U0SRT_reg   (*((volatile unsigned int*) ISO_U0SRT_reg))
#define ISO_U0SRT_inst_adr                                                           "0x0027"
#define ISO_U0SRT_inst                                                               0x0027
#define ISO_U0SRT_srt_shift                                                          (0)
#define ISO_U0SRT_srt_mask                                                           (0x00000003)
#define ISO_U0SRT_srt(data)                                                          (0x00000003&((data)<<0))
#define ISO_U0SRT_srt_src(data)                                                      ((0x00000003&(data))>>0)
#define ISO_U0SRT_get_srt(data)                                                      ((0x00000003&(data))>>0)


#define ISO_U0STET                                                                   0x980078A0
#define ISO_U0STET_reg_addr                                                          "0x980078A0"
#define ISO_U0STET_reg                                                               0x980078A0
#define set_ISO_U0STET_reg(data)   (*((volatile unsigned int*) ISO_U0STET_reg)=data)
#define get_ISO_U0STET_reg   (*((volatile unsigned int*) ISO_U0STET_reg))
#define ISO_U0STET_inst_adr                                                          "0x0028"
#define ISO_U0STET_inst                                                              0x0028
#define ISO_U0STET_stet_shift                                                        (0)
#define ISO_U0STET_stet_mask                                                         (0x00000003)
#define ISO_U0STET_stet(data)                                                        (0x00000003&((data)<<0))
#define ISO_U0STET_stet_src(data)                                                    ((0x00000003&(data))>>0)
#define ISO_U0STET_get_stet(data)                                                    ((0x00000003&(data))>>0)


#define ISO_U0HTX                                                                    0x980078A4
#define ISO_U0HTX_reg_addr                                                           "0x980078A4"
#define ISO_U0HTX_reg                                                                0x980078A4
#define set_ISO_U0HTX_reg(data)   (*((volatile unsigned int*) ISO_U0HTX_reg)=data)
#define get_ISO_U0HTX_reg   (*((volatile unsigned int*) ISO_U0HTX_reg))
#define ISO_U0HTX_inst_adr                                                           "0x0029"
#define ISO_U0HTX_inst                                                               0x0029
#define ISO_U0HTX_htx_shift                                                          (0)
#define ISO_U0HTX_htx_mask                                                           (0x00000001)
#define ISO_U0HTX_htx(data)                                                          (0x00000001&((data)<<0))
#define ISO_U0HTX_htx_src(data)                                                      ((0x00000001&(data))>>0)
#define ISO_U0HTX_get_htx(data)                                                      ((0x00000001&(data))>>0)


#define ISO_U0DMASA                                                                  0x980078A8
#define ISO_U0DMASA_reg_addr                                                         "0x980078A8"
#define ISO_U0DMASA_reg                                                              0x980078A8
#define set_ISO_U0DMASA_reg(data)   (*((volatile unsigned int*) ISO_U0DMASA_reg)=data)
#define get_ISO_U0DMASA_reg   (*((volatile unsigned int*) ISO_U0DMASA_reg))
#define ISO_U0DMASA_inst_adr                                                         "0x002A"
#define ISO_U0DMASA_inst                                                             0x002A
#define ISO_U0DMASA_dmasa_shift                                                      (0)
#define ISO_U0DMASA_dmasa_mask                                                       (0x00000001)
#define ISO_U0DMASA_dmasa(data)                                                      (0x00000001&((data)<<0))
#define ISO_U0DMASA_dmasa_src(data)                                                  ((0x00000001&(data))>>0)
#define ISO_U0DMASA_get_dmasa(data)                                                  ((0x00000001&(data))>>0)


#define ISO_U0CPR                                                                    0x980078F4
#define ISO_U0CPR_reg_addr                                                           "0x980078F4"
#define ISO_U0CPR_reg                                                                0x980078F4
#define set_ISO_U0CPR_reg(data)   (*((volatile unsigned int*) ISO_U0CPR_reg)=data)
#define get_ISO_U0CPR_reg   (*((volatile unsigned int*) ISO_U0CPR_reg))
#define ISO_U0CPR_inst_adr                                                           "0x003D"
#define ISO_U0CPR_inst                                                               0x003D
#define ISO_U0CPR_fifo_mode_shift                                                    (16)
#define ISO_U0CPR_fifo_mode_mask                                                     (0x00FF0000)
#define ISO_U0CPR_fifo_mode(data)                                                    (0x00FF0000&((data)<<16))
#define ISO_U0CPR_fifo_mode_src(data)                                                ((0x00FF0000&(data))>>16)
#define ISO_U0CPR_get_fifo_mode(data)                                                ((0x00FF0000&(data))>>16)
#define ISO_U0CPR_dma_extra_shift                                                    (13)
#define ISO_U0CPR_dma_extra_mask                                                     (0x00002000)
#define ISO_U0CPR_dma_extra(data)                                                    (0x00002000&((data)<<13))
#define ISO_U0CPR_dma_extra_src(data)                                                ((0x00002000&(data))>>13)
#define ISO_U0CPR_get_dma_extra(data)                                                ((0x00002000&(data))>>13)
#define ISO_U0CPR_uart_add_encoded_params_shift                                      (12)
#define ISO_U0CPR_uart_add_encoded_params_mask                                       (0x00001000)
#define ISO_U0CPR_uart_add_encoded_params(data)                                      (0x00001000&((data)<<12))
#define ISO_U0CPR_uart_add_encoded_params_src(data)                                  ((0x00001000&(data))>>12)
#define ISO_U0CPR_get_uart_add_encoded_params(data)                                  ((0x00001000&(data))>>12)
#define ISO_U0CPR_shadow_shift                                                       (11)
#define ISO_U0CPR_shadow_mask                                                        (0x00000800)
#define ISO_U0CPR_shadow(data)                                                       (0x00000800&((data)<<11))
#define ISO_U0CPR_shadow_src(data)                                                   ((0x00000800&(data))>>11)
#define ISO_U0CPR_get_shadow(data)                                                   ((0x00000800&(data))>>11)
#define ISO_U0CPR_fifo_stat_shift                                                    (10)
#define ISO_U0CPR_fifo_stat_mask                                                     (0x00000400)
#define ISO_U0CPR_fifo_stat(data)                                                    (0x00000400&((data)<<10))
#define ISO_U0CPR_fifo_stat_src(data)                                                ((0x00000400&(data))>>10)
#define ISO_U0CPR_get_fifo_stat(data)                                                ((0x00000400&(data))>>10)
#define ISO_U0CPR_fifo_access_shift                                                  (9)
#define ISO_U0CPR_fifo_access_mask                                                   (0x00000200)
#define ISO_U0CPR_fifo_access(data)                                                  (0x00000200&((data)<<9))
#define ISO_U0CPR_fifo_access_src(data)                                              ((0x00000200&(data))>>9)
#define ISO_U0CPR_get_fifo_access(data)                                              ((0x00000200&(data))>>9)
#define ISO_U0CPR_additional_feat_shift                                              (8)
#define ISO_U0CPR_additional_feat_mask                                               (0x00000100)
#define ISO_U0CPR_additional_feat(data)                                              (0x00000100&((data)<<8))
#define ISO_U0CPR_additional_feat_src(data)                                          ((0x00000100&(data))>>8)
#define ISO_U0CPR_get_additional_feat(data)                                          ((0x00000100&(data))>>8)
#define ISO_U0CPR_sir_lp_mode_shift                                                  (7)
#define ISO_U0CPR_sir_lp_mode_mask                                                   (0x00000080)
#define ISO_U0CPR_sir_lp_mode(data)                                                  (0x00000080&((data)<<7))
#define ISO_U0CPR_sir_lp_mode_src(data)                                              ((0x00000080&(data))>>7)
#define ISO_U0CPR_get_sir_lp_mode(data)                                              ((0x00000080&(data))>>7)
#define ISO_U0CPR_sir_mode_shift                                                     (6)
#define ISO_U0CPR_sir_mode_mask                                                      (0x00000040)
#define ISO_U0CPR_sir_mode(data)                                                     (0x00000040&((data)<<6))
#define ISO_U0CPR_sir_mode_src(data)                                                 ((0x00000040&(data))>>6)
#define ISO_U0CPR_get_sir_mode(data)                                                 ((0x00000040&(data))>>6)
#define ISO_U0CPR_thre_mode_shift                                                    (5)
#define ISO_U0CPR_thre_mode_mask                                                     (0x00000020)
#define ISO_U0CPR_thre_mode(data)                                                    (0x00000020&((data)<<5))
#define ISO_U0CPR_thre_mode_src(data)                                                ((0x00000020&(data))>>5)
#define ISO_U0CPR_get_thre_mode(data)                                                ((0x00000020&(data))>>5)
#define ISO_U0CPR_afce_mode_shift                                                    (4)
#define ISO_U0CPR_afce_mode_mask                                                     (0x00000010)
#define ISO_U0CPR_afce_mode(data)                                                    (0x00000010&((data)<<4))
#define ISO_U0CPR_afce_mode_src(data)                                                ((0x00000010&(data))>>4)
#define ISO_U0CPR_get_afce_mode(data)                                                ((0x00000010&(data))>>4)
#define ISO_U0CPR_apb_data_width_shift                                               (0)
#define ISO_U0CPR_apb_data_width_mask                                                (0x00000003)
#define ISO_U0CPR_apb_data_width(data)                                               (0x00000003&((data)<<0))
#define ISO_U0CPR_apb_data_width_src(data)                                           ((0x00000003&(data))>>0)
#define ISO_U0CPR_get_apb_data_width(data)                                           ((0x00000003&(data))>>0)


#define ISO_U0UCV                                                                    0x980078F8
#define ISO_U0UCV_reg_addr                                                           "0x980078F8"
#define ISO_U0UCV_reg                                                                0x980078F8
#define set_ISO_U0UCV_reg(data)   (*((volatile unsigned int*) ISO_U0UCV_reg)=data)
#define get_ISO_U0UCV_reg   (*((volatile unsigned int*) ISO_U0UCV_reg))
#define ISO_U0UCV_inst_adr                                                           "0x003E"
#define ISO_U0UCV_inst                                                               0x003E
#define ISO_U0UCV_ucv_shift                                                          (0)
#define ISO_U0UCV_ucv_mask                                                           (0xFFFFFFFF)
#define ISO_U0UCV_ucv(data)                                                          (0xFFFFFFFF&((data)<<0))
#define ISO_U0UCV_ucv_src(data)                                                      ((0xFFFFFFFF&(data))>>0)
#define ISO_U0UCV_get_ucv(data)                                                      ((0xFFFFFFFF&(data))>>0)


#define ISO_U0CTR                                                                    0x980078FC
#define ISO_U0CTR_reg_addr                                                           "0x980078FC"
#define ISO_U0CTR_reg                                                                0x980078FC
#define set_ISO_U0CTR_reg(data)   (*((volatile unsigned int*) ISO_U0CTR_reg)=data)
#define get_ISO_U0CTR_reg   (*((volatile unsigned int*) ISO_U0CTR_reg))
#define ISO_U0CTR_inst_adr                                                           "0x003F"
#define ISO_U0CTR_inst                                                               0x003F
#define ISO_U0CTR_ctr_shift                                                          (0)
#define ISO_U0CTR_ctr_mask                                                           (0xFFFFFFFF)
#define ISO_U0CTR_ctr(data)                                                          (0xFFFFFFFF&((data)<<0))
#define ISO_U0CTR_ctr_src(data)                                                      ((0xFFFFFFFF&(data))>>0)
#define ISO_U0CTR_get_ctr(data)                                                      ((0xFFFFFFFF&(data))>>0)


#define ISO_IC0_CON                                                                  0x98007D00
#define ISO_IC0_CON_reg_addr                                                         "0x98007D00"
#define ISO_IC0_CON_reg                                                              0x98007D00
#define set_ISO_IC0_CON_reg(data)   (*((volatile unsigned int*) ISO_IC0_CON_reg)=data)
#define get_ISO_IC0_CON_reg   (*((volatile unsigned int*) ISO_IC0_CON_reg))
#define ISO_IC0_CON_inst_adr                                                         "0x0040"
#define ISO_IC0_CON_inst                                                             0x0040
#define ISO_IC0_CON_ic_slave_disable_shift                                           (6)
#define ISO_IC0_CON_ic_slave_disable_mask                                            (0x00000040)
#define ISO_IC0_CON_ic_slave_disable(data)                                           (0x00000040&((data)<<6))
#define ISO_IC0_CON_ic_slave_disable_src(data)                                       ((0x00000040&(data))>>6)
#define ISO_IC0_CON_get_ic_slave_disable(data)                                       ((0x00000040&(data))>>6)
#define ISO_IC0_CON_ic_restart_en_shift                                              (5)
#define ISO_IC0_CON_ic_restart_en_mask                                               (0x00000020)
#define ISO_IC0_CON_ic_restart_en(data)                                              (0x00000020&((data)<<5))
#define ISO_IC0_CON_ic_restart_en_src(data)                                          ((0x00000020&(data))>>5)
#define ISO_IC0_CON_get_ic_restart_en(data)                                          ((0x00000020&(data))>>5)
#define ISO_IC0_CON_ic_10bitaddr_master_shift                                        (4)
#define ISO_IC0_CON_ic_10bitaddr_master_mask                                         (0x00000010)
#define ISO_IC0_CON_ic_10bitaddr_master(data)                                        (0x00000010&((data)<<4))
#define ISO_IC0_CON_ic_10bitaddr_master_src(data)                                    ((0x00000010&(data))>>4)
#define ISO_IC0_CON_get_ic_10bitaddr_master(data)                                    ((0x00000010&(data))>>4)
#define ISO_IC0_CON_ic_10bitaddr_slave_shift                                         (3)
#define ISO_IC0_CON_ic_10bitaddr_slave_mask                                          (0x00000008)
#define ISO_IC0_CON_ic_10bitaddr_slave(data)                                         (0x00000008&((data)<<3))
#define ISO_IC0_CON_ic_10bitaddr_slave_src(data)                                     ((0x00000008&(data))>>3)
#define ISO_IC0_CON_get_ic_10bitaddr_slave(data)                                     ((0x00000008&(data))>>3)
#define ISO_IC0_CON_speed_shift                                                      (1)
#define ISO_IC0_CON_speed_mask                                                       (0x00000006)
#define ISO_IC0_CON_speed(data)                                                      (0x00000006&((data)<<1))
#define ISO_IC0_CON_speed_src(data)                                                  ((0x00000006&(data))>>1)
#define ISO_IC0_CON_get_speed(data)                                                  ((0x00000006&(data))>>1)
#define ISO_IC0_CON_master_mode_shift                                                (0)
#define ISO_IC0_CON_master_mode_mask                                                 (0x00000001)
#define ISO_IC0_CON_master_mode(data)                                                (0x00000001&((data)<<0))
#define ISO_IC0_CON_master_mode_src(data)                                            ((0x00000001&(data))>>0)
#define ISO_IC0_CON_get_master_mode(data)                                            ((0x00000001&(data))>>0)


#define ISO_IC0_TAR                                                                  0x98007D04
#define ISO_IC0_TAR_reg_addr                                                         "0x98007D04"
#define ISO_IC0_TAR_reg                                                              0x98007D04
#define set_ISO_IC0_TAR_reg(data)   (*((volatile unsigned int*) ISO_IC0_TAR_reg)=data)
#define get_ISO_IC0_TAR_reg   (*((volatile unsigned int*) ISO_IC0_TAR_reg))
#define ISO_IC0_TAR_inst_adr                                                         "0x0041"
#define ISO_IC0_TAR_inst                                                             0x0041
#define ISO_IC0_TAR_ic_10bitaddr_master_shift                                        (12)
#define ISO_IC0_TAR_ic_10bitaddr_master_mask                                         (0x00001000)
#define ISO_IC0_TAR_ic_10bitaddr_master(data)                                        (0x00001000&((data)<<12))
#define ISO_IC0_TAR_ic_10bitaddr_master_src(data)                                    ((0x00001000&(data))>>12)
#define ISO_IC0_TAR_get_ic_10bitaddr_master(data)                                    ((0x00001000&(data))>>12)
#define ISO_IC0_TAR_special_shift                                                    (11)
#define ISO_IC0_TAR_special_mask                                                     (0x00000800)
#define ISO_IC0_TAR_special(data)                                                    (0x00000800&((data)<<11))
#define ISO_IC0_TAR_special_src(data)                                                ((0x00000800&(data))>>11)
#define ISO_IC0_TAR_get_special(data)                                                ((0x00000800&(data))>>11)
#define ISO_IC0_TAR_gc_or_start_shift                                                (10)
#define ISO_IC0_TAR_gc_or_start_mask                                                 (0x00000400)
#define ISO_IC0_TAR_gc_or_start(data)                                                (0x00000400&((data)<<10))
#define ISO_IC0_TAR_gc_or_start_src(data)                                            ((0x00000400&(data))>>10)
#define ISO_IC0_TAR_get_gc_or_start(data)                                            ((0x00000400&(data))>>10)
#define ISO_IC0_TAR_ic_tar_shift                                                     (0)
#define ISO_IC0_TAR_ic_tar_mask                                                      (0x000003FF)
#define ISO_IC0_TAR_ic_tar(data)                                                     (0x000003FF&((data)<<0))
#define ISO_IC0_TAR_ic_tar_src(data)                                                 ((0x000003FF&(data))>>0)
#define ISO_IC0_TAR_get_ic_tar(data)                                                 ((0x000003FF&(data))>>0)


#define ISO_IC0_SAR                                                                  0x98007D08
#define ISO_IC0_SAR_reg_addr                                                         "0x98007D08"
#define ISO_IC0_SAR_reg                                                              0x98007D08
#define set_ISO_IC0_SAR_reg(data)   (*((volatile unsigned int*) ISO_IC0_SAR_reg)=data)
#define get_ISO_IC0_SAR_reg   (*((volatile unsigned int*) ISO_IC0_SAR_reg))
#define ISO_IC0_SAR_inst_adr                                                         "0x0042"
#define ISO_IC0_SAR_inst                                                             0x0042
#define ISO_IC0_SAR_ic_sar_shift                                                     (0)
#define ISO_IC0_SAR_ic_sar_mask                                                      (0x000003FF)
#define ISO_IC0_SAR_ic_sar(data)                                                     (0x000003FF&((data)<<0))
#define ISO_IC0_SAR_ic_sar_src(data)                                                 ((0x000003FF&(data))>>0)
#define ISO_IC0_SAR_get_ic_sar(data)                                                 ((0x000003FF&(data))>>0)


#define ISO_IC0_HS_MADDR                                                             0x98007D0C
#define ISO_IC0_HS_MADDR_reg_addr                                                    "0x98007D0C"
#define ISO_IC0_HS_MADDR_reg                                                         0x98007D0C
#define set_ISO_IC0_HS_MADDR_reg(data)   (*((volatile unsigned int*) ISO_IC0_HS_MADDR_reg)=data)
#define get_ISO_IC0_HS_MADDR_reg   (*((volatile unsigned int*) ISO_IC0_HS_MADDR_reg))
#define ISO_IC0_HS_MADDR_inst_adr                                                    "0x0043"
#define ISO_IC0_HS_MADDR_inst                                                        0x0043
#define ISO_IC0_HS_MADDR_ic_hs_mar_shift                                             (0)
#define ISO_IC0_HS_MADDR_ic_hs_mar_mask                                              (0x00000007)
#define ISO_IC0_HS_MADDR_ic_hs_mar(data)                                             (0x00000007&((data)<<0))
#define ISO_IC0_HS_MADDR_ic_hs_mar_src(data)                                         ((0x00000007&(data))>>0)
#define ISO_IC0_HS_MADDR_get_ic_hs_mar(data)                                         ((0x00000007&(data))>>0)


#define ISO_IC0_DATA_CMD                                                             0x98007D10
#define ISO_IC0_DATA_CMD_reg_addr                                                    "0x98007D10"
#define ISO_IC0_DATA_CMD_reg                                                         0x98007D10
#define set_ISO_IC0_DATA_CMD_reg(data)   (*((volatile unsigned int*) ISO_IC0_DATA_CMD_reg)=data)
#define get_ISO_IC0_DATA_CMD_reg   (*((volatile unsigned int*) ISO_IC0_DATA_CMD_reg))
#define ISO_IC0_DATA_CMD_inst_adr                                                    "0x0044"
#define ISO_IC0_DATA_CMD_inst                                                        0x0044
#define ISO_IC0_DATA_CMD_restart_shift                                               (10)
#define ISO_IC0_DATA_CMD_restart_mask                                                (0x00000400)
#define ISO_IC0_DATA_CMD_restart(data)                                               (0x00000400&((data)<<10))
#define ISO_IC0_DATA_CMD_restart_src(data)                                           ((0x00000400&(data))>>10)
#define ISO_IC0_DATA_CMD_get_restart(data)                                           ((0x00000400&(data))>>10)
#define ISO_IC0_DATA_CMD_stop_shift                                                  (9)
#define ISO_IC0_DATA_CMD_stop_mask                                                   (0x00000200)
#define ISO_IC0_DATA_CMD_stop(data)                                                  (0x00000200&((data)<<9))
#define ISO_IC0_DATA_CMD_stop_src(data)                                              ((0x00000200&(data))>>9)
#define ISO_IC0_DATA_CMD_get_stop(data)                                              ((0x00000200&(data))>>9)
#define ISO_IC0_DATA_CMD_cmd_shift                                                   (8)
#define ISO_IC0_DATA_CMD_cmd_mask                                                    (0x00000100)
#define ISO_IC0_DATA_CMD_cmd(data)                                                   (0x00000100&((data)<<8))
#define ISO_IC0_DATA_CMD_cmd_src(data)                                               ((0x00000100&(data))>>8)
#define ISO_IC0_DATA_CMD_get_cmd(data)                                               ((0x00000100&(data))>>8)
#define ISO_IC0_DATA_CMD_dat_shift                                                   (0)
#define ISO_IC0_DATA_CMD_dat_mask                                                    (0x000000FF)
#define ISO_IC0_DATA_CMD_dat(data)                                                   (0x000000FF&((data)<<0))
#define ISO_IC0_DATA_CMD_dat_src(data)                                               ((0x000000FF&(data))>>0)
#define ISO_IC0_DATA_CMD_get_dat(data)                                               ((0x000000FF&(data))>>0)


#define ISO_IC0_SS_SCL_HCNT                                                          0x98007D14
#define ISO_IC0_SS_SCL_HCNT_reg_addr                                                 "0x98007D14"
#define ISO_IC0_SS_SCL_HCNT_reg                                                      0x98007D14
#define set_ISO_IC0_SS_SCL_HCNT_reg(data)   (*((volatile unsigned int*) ISO_IC0_SS_SCL_HCNT_reg)=data)
#define get_ISO_IC0_SS_SCL_HCNT_reg   (*((volatile unsigned int*) ISO_IC0_SS_SCL_HCNT_reg))
#define ISO_IC0_SS_SCL_HCNT_inst_adr                                                 "0x0045"
#define ISO_IC0_SS_SCL_HCNT_inst                                                     0x0045
#define ISO_IC0_SS_SCL_HCNT_ic_ss_scl_hcnt_shift                                     (0)
#define ISO_IC0_SS_SCL_HCNT_ic_ss_scl_hcnt_mask                                      (0x0000FFFF)
#define ISO_IC0_SS_SCL_HCNT_ic_ss_scl_hcnt(data)                                     (0x0000FFFF&((data)<<0))
#define ISO_IC0_SS_SCL_HCNT_ic_ss_scl_hcnt_src(data)                                 ((0x0000FFFF&(data))>>0)
#define ISO_IC0_SS_SCL_HCNT_get_ic_ss_scl_hcnt(data)                                 ((0x0000FFFF&(data))>>0)


#define ISO_IC0_SS_SCL_LCNT                                                          0x98007D18
#define ISO_IC0_SS_SCL_LCNT_reg_addr                                                 "0x98007D18"
#define ISO_IC0_SS_SCL_LCNT_reg                                                      0x98007D18
#define set_ISO_IC0_SS_SCL_LCNT_reg(data)   (*((volatile unsigned int*) ISO_IC0_SS_SCL_LCNT_reg)=data)
#define get_ISO_IC0_SS_SCL_LCNT_reg   (*((volatile unsigned int*) ISO_IC0_SS_SCL_LCNT_reg))
#define ISO_IC0_SS_SCL_LCNT_inst_adr                                                 "0x0046"
#define ISO_IC0_SS_SCL_LCNT_inst                                                     0x0046
#define ISO_IC0_SS_SCL_LCNT_ic_ss_scl_lcnt_shift                                     (0)
#define ISO_IC0_SS_SCL_LCNT_ic_ss_scl_lcnt_mask                                      (0x0000FFFF)
#define ISO_IC0_SS_SCL_LCNT_ic_ss_scl_lcnt(data)                                     (0x0000FFFF&((data)<<0))
#define ISO_IC0_SS_SCL_LCNT_ic_ss_scl_lcnt_src(data)                                 ((0x0000FFFF&(data))>>0)
#define ISO_IC0_SS_SCL_LCNT_get_ic_ss_scl_lcnt(data)                                 ((0x0000FFFF&(data))>>0)


#define ISO_IC0_FS_SCL_HCNT                                                          0x98007D1C
#define ISO_IC0_FS_SCL_HCNT_reg_addr                                                 "0x98007D1C"
#define ISO_IC0_FS_SCL_HCNT_reg                                                      0x98007D1C
#define set_ISO_IC0_FS_SCL_HCNT_reg(data)   (*((volatile unsigned int*) ISO_IC0_FS_SCL_HCNT_reg)=data)
#define get_ISO_IC0_FS_SCL_HCNT_reg   (*((volatile unsigned int*) ISO_IC0_FS_SCL_HCNT_reg))
#define ISO_IC0_FS_SCL_HCNT_inst_adr                                                 "0x0047"
#define ISO_IC0_FS_SCL_HCNT_inst                                                     0x0047
#define ISO_IC0_FS_SCL_HCNT_ic_fs_scl_hcnt_shift                                     (0)
#define ISO_IC0_FS_SCL_HCNT_ic_fs_scl_hcnt_mask                                      (0x0000FFFF)
#define ISO_IC0_FS_SCL_HCNT_ic_fs_scl_hcnt(data)                                     (0x0000FFFF&((data)<<0))
#define ISO_IC0_FS_SCL_HCNT_ic_fs_scl_hcnt_src(data)                                 ((0x0000FFFF&(data))>>0)
#define ISO_IC0_FS_SCL_HCNT_get_ic_fs_scl_hcnt(data)                                 ((0x0000FFFF&(data))>>0)


#define ISO_IC0_FS_SCL_LCNT                                                          0x98007D20
#define ISO_IC0_FS_SCL_LCNT_reg_addr                                                 "0x98007D20"
#define ISO_IC0_FS_SCL_LCNT_reg                                                      0x98007D20
#define set_ISO_IC0_FS_SCL_LCNT_reg(data)   (*((volatile unsigned int*) ISO_IC0_FS_SCL_LCNT_reg)=data)
#define get_ISO_IC0_FS_SCL_LCNT_reg   (*((volatile unsigned int*) ISO_IC0_FS_SCL_LCNT_reg))
#define ISO_IC0_FS_SCL_LCNT_inst_adr                                                 "0x0048"
#define ISO_IC0_FS_SCL_LCNT_inst                                                     0x0048
#define ISO_IC0_FS_SCL_LCNT_ic_fs_scl_lcnt_shift                                     (0)
#define ISO_IC0_FS_SCL_LCNT_ic_fs_scl_lcnt_mask                                      (0x0000FFFF)
#define ISO_IC0_FS_SCL_LCNT_ic_fs_scl_lcnt(data)                                     (0x0000FFFF&((data)<<0))
#define ISO_IC0_FS_SCL_LCNT_ic_fs_scl_lcnt_src(data)                                 ((0x0000FFFF&(data))>>0)
#define ISO_IC0_FS_SCL_LCNT_get_ic_fs_scl_lcnt(data)                                 ((0x0000FFFF&(data))>>0)


#define ISO_IC0_INTR_STAT                                                            0x98007D2C
#define ISO_IC0_INTR_STAT_reg_addr                                                   "0x98007D2C"
#define ISO_IC0_INTR_STAT_reg                                                        0x98007D2C
#define set_ISO_IC0_INTR_STAT_reg(data)   (*((volatile unsigned int*) ISO_IC0_INTR_STAT_reg)=data)
#define get_ISO_IC0_INTR_STAT_reg   (*((volatile unsigned int*) ISO_IC0_INTR_STAT_reg))
#define ISO_IC0_INTR_STAT_inst_adr                                                   "0x004B"
#define ISO_IC0_INTR_STAT_inst                                                       0x004B
#define ISO_IC0_INTR_STAT_r_gen_call_shift                                           (11)
#define ISO_IC0_INTR_STAT_r_gen_call_mask                                            (0x00000800)
#define ISO_IC0_INTR_STAT_r_gen_call(data)                                           (0x00000800&((data)<<11))
#define ISO_IC0_INTR_STAT_r_gen_call_src(data)                                       ((0x00000800&(data))>>11)
#define ISO_IC0_INTR_STAT_get_r_gen_call(data)                                       ((0x00000800&(data))>>11)
#define ISO_IC0_INTR_STAT_r_start_det_shift                                          (10)
#define ISO_IC0_INTR_STAT_r_start_det_mask                                           (0x00000400)
#define ISO_IC0_INTR_STAT_r_start_det(data)                                          (0x00000400&((data)<<10))
#define ISO_IC0_INTR_STAT_r_start_det_src(data)                                      ((0x00000400&(data))>>10)
#define ISO_IC0_INTR_STAT_get_r_start_det(data)                                      ((0x00000400&(data))>>10)
#define ISO_IC0_INTR_STAT_r_stop_det_shift                                           (9)
#define ISO_IC0_INTR_STAT_r_stop_det_mask                                            (0x00000200)
#define ISO_IC0_INTR_STAT_r_stop_det(data)                                           (0x00000200&((data)<<9))
#define ISO_IC0_INTR_STAT_r_stop_det_src(data)                                       ((0x00000200&(data))>>9)
#define ISO_IC0_INTR_STAT_get_r_stop_det(data)                                       ((0x00000200&(data))>>9)
#define ISO_IC0_INTR_STAT_r_activity_shift                                           (8)
#define ISO_IC0_INTR_STAT_r_activity_mask                                            (0x00000100)
#define ISO_IC0_INTR_STAT_r_activity(data)                                           (0x00000100&((data)<<8))
#define ISO_IC0_INTR_STAT_r_activity_src(data)                                       ((0x00000100&(data))>>8)
#define ISO_IC0_INTR_STAT_get_r_activity(data)                                       ((0x00000100&(data))>>8)
#define ISO_IC0_INTR_STAT_r_rx_done_shift                                            (7)
#define ISO_IC0_INTR_STAT_r_rx_done_mask                                             (0x00000080)
#define ISO_IC0_INTR_STAT_r_rx_done(data)                                            (0x00000080&((data)<<7))
#define ISO_IC0_INTR_STAT_r_rx_done_src(data)                                        ((0x00000080&(data))>>7)
#define ISO_IC0_INTR_STAT_get_r_rx_done(data)                                        ((0x00000080&(data))>>7)
#define ISO_IC0_INTR_STAT_r_tx_abrt_shift                                            (6)
#define ISO_IC0_INTR_STAT_r_tx_abrt_mask                                             (0x00000040)
#define ISO_IC0_INTR_STAT_r_tx_abrt(data)                                            (0x00000040&((data)<<6))
#define ISO_IC0_INTR_STAT_r_tx_abrt_src(data)                                        ((0x00000040&(data))>>6)
#define ISO_IC0_INTR_STAT_get_r_tx_abrt(data)                                        ((0x00000040&(data))>>6)
#define ISO_IC0_INTR_STAT_r_rd_req_shift                                             (5)
#define ISO_IC0_INTR_STAT_r_rd_req_mask                                              (0x00000020)
#define ISO_IC0_INTR_STAT_r_rd_req(data)                                             (0x00000020&((data)<<5))
#define ISO_IC0_INTR_STAT_r_rd_req_src(data)                                         ((0x00000020&(data))>>5)
#define ISO_IC0_INTR_STAT_get_r_rd_req(data)                                         ((0x00000020&(data))>>5)
#define ISO_IC0_INTR_STAT_r_tx_empty_shift                                           (4)
#define ISO_IC0_INTR_STAT_r_tx_empty_mask                                            (0x00000010)
#define ISO_IC0_INTR_STAT_r_tx_empty(data)                                           (0x00000010&((data)<<4))
#define ISO_IC0_INTR_STAT_r_tx_empty_src(data)                                       ((0x00000010&(data))>>4)
#define ISO_IC0_INTR_STAT_get_r_tx_empty(data)                                       ((0x00000010&(data))>>4)
#define ISO_IC0_INTR_STAT_r_tx_over_shift                                            (3)
#define ISO_IC0_INTR_STAT_r_tx_over_mask                                             (0x00000008)
#define ISO_IC0_INTR_STAT_r_tx_over(data)                                            (0x00000008&((data)<<3))
#define ISO_IC0_INTR_STAT_r_tx_over_src(data)                                        ((0x00000008&(data))>>3)
#define ISO_IC0_INTR_STAT_get_r_tx_over(data)                                        ((0x00000008&(data))>>3)
#define ISO_IC0_INTR_STAT_r_rx_full_shift                                            (2)
#define ISO_IC0_INTR_STAT_r_rx_full_mask                                             (0x00000004)
#define ISO_IC0_INTR_STAT_r_rx_full(data)                                            (0x00000004&((data)<<2))
#define ISO_IC0_INTR_STAT_r_rx_full_src(data)                                        ((0x00000004&(data))>>2)
#define ISO_IC0_INTR_STAT_get_r_rx_full(data)                                        ((0x00000004&(data))>>2)
#define ISO_IC0_INTR_STAT_r_rx_over_shift                                            (1)
#define ISO_IC0_INTR_STAT_r_rx_over_mask                                             (0x00000002)
#define ISO_IC0_INTR_STAT_r_rx_over(data)                                            (0x00000002&((data)<<1))
#define ISO_IC0_INTR_STAT_r_rx_over_src(data)                                        ((0x00000002&(data))>>1)
#define ISO_IC0_INTR_STAT_get_r_rx_over(data)                                        ((0x00000002&(data))>>1)
#define ISO_IC0_INTR_STAT_r_rx_under_shift                                           (0)
#define ISO_IC0_INTR_STAT_r_rx_under_mask                                            (0x00000001)
#define ISO_IC0_INTR_STAT_r_rx_under(data)                                           (0x00000001&((data)<<0))
#define ISO_IC0_INTR_STAT_r_rx_under_src(data)                                       ((0x00000001&(data))>>0)
#define ISO_IC0_INTR_STAT_get_r_rx_under(data)                                       ((0x00000001&(data))>>0)


#define ISO_IC0_INTR_MASK                                                            0x98007D30
#define ISO_IC0_INTR_MASK_reg_addr                                                   "0x98007D30"
#define ISO_IC0_INTR_MASK_reg                                                        0x98007D30
#define set_ISO_IC0_INTR_MASK_reg(data)   (*((volatile unsigned int*) ISO_IC0_INTR_MASK_reg)=data)
#define get_ISO_IC0_INTR_MASK_reg   (*((volatile unsigned int*) ISO_IC0_INTR_MASK_reg))
#define ISO_IC0_INTR_MASK_inst_adr                                                   "0x004C"
#define ISO_IC0_INTR_MASK_inst                                                       0x004C
#define ISO_IC0_INTR_MASK_m_gen_call_shift                                           (11)
#define ISO_IC0_INTR_MASK_m_gen_call_mask                                            (0x00000800)
#define ISO_IC0_INTR_MASK_m_gen_call(data)                                           (0x00000800&((data)<<11))
#define ISO_IC0_INTR_MASK_m_gen_call_src(data)                                       ((0x00000800&(data))>>11)
#define ISO_IC0_INTR_MASK_get_m_gen_call(data)                                       ((0x00000800&(data))>>11)
#define ISO_IC0_INTR_MASK_m_start_det_shift                                          (10)
#define ISO_IC0_INTR_MASK_m_start_det_mask                                           (0x00000400)
#define ISO_IC0_INTR_MASK_m_start_det(data)                                          (0x00000400&((data)<<10))
#define ISO_IC0_INTR_MASK_m_start_det_src(data)                                      ((0x00000400&(data))>>10)
#define ISO_IC0_INTR_MASK_get_m_start_det(data)                                      ((0x00000400&(data))>>10)
#define ISO_IC0_INTR_MASK_m_stop_det_shift                                           (9)
#define ISO_IC0_INTR_MASK_m_stop_det_mask                                            (0x00000200)
#define ISO_IC0_INTR_MASK_m_stop_det(data)                                           (0x00000200&((data)<<9))
#define ISO_IC0_INTR_MASK_m_stop_det_src(data)                                       ((0x00000200&(data))>>9)
#define ISO_IC0_INTR_MASK_get_m_stop_det(data)                                       ((0x00000200&(data))>>9)
#define ISO_IC0_INTR_MASK_m_activity_shift                                           (8)
#define ISO_IC0_INTR_MASK_m_activity_mask                                            (0x00000100)
#define ISO_IC0_INTR_MASK_m_activity(data)                                           (0x00000100&((data)<<8))
#define ISO_IC0_INTR_MASK_m_activity_src(data)                                       ((0x00000100&(data))>>8)
#define ISO_IC0_INTR_MASK_get_m_activity(data)                                       ((0x00000100&(data))>>8)
#define ISO_IC0_INTR_MASK_m_rx_done_shift                                            (7)
#define ISO_IC0_INTR_MASK_m_rx_done_mask                                             (0x00000080)
#define ISO_IC0_INTR_MASK_m_rx_done(data)                                            (0x00000080&((data)<<7))
#define ISO_IC0_INTR_MASK_m_rx_done_src(data)                                        ((0x00000080&(data))>>7)
#define ISO_IC0_INTR_MASK_get_m_rx_done(data)                                        ((0x00000080&(data))>>7)
#define ISO_IC0_INTR_MASK_m_tx_abrt_shift                                            (6)
#define ISO_IC0_INTR_MASK_m_tx_abrt_mask                                             (0x00000040)
#define ISO_IC0_INTR_MASK_m_tx_abrt(data)                                            (0x00000040&((data)<<6))
#define ISO_IC0_INTR_MASK_m_tx_abrt_src(data)                                        ((0x00000040&(data))>>6)
#define ISO_IC0_INTR_MASK_get_m_tx_abrt(data)                                        ((0x00000040&(data))>>6)
#define ISO_IC0_INTR_MASK_m_rd_req_shift                                             (5)
#define ISO_IC0_INTR_MASK_m_rd_req_mask                                              (0x00000020)
#define ISO_IC0_INTR_MASK_m_rd_req(data)                                             (0x00000020&((data)<<5))
#define ISO_IC0_INTR_MASK_m_rd_req_src(data)                                         ((0x00000020&(data))>>5)
#define ISO_IC0_INTR_MASK_get_m_rd_req(data)                                         ((0x00000020&(data))>>5)
#define ISO_IC0_INTR_MASK_m_tx_empty_shift                                           (4)
#define ISO_IC0_INTR_MASK_m_tx_empty_mask                                            (0x00000010)
#define ISO_IC0_INTR_MASK_m_tx_empty(data)                                           (0x00000010&((data)<<4))
#define ISO_IC0_INTR_MASK_m_tx_empty_src(data)                                       ((0x00000010&(data))>>4)
#define ISO_IC0_INTR_MASK_get_m_tx_empty(data)                                       ((0x00000010&(data))>>4)
#define ISO_IC0_INTR_MASK_m_tx_over_shift                                            (3)
#define ISO_IC0_INTR_MASK_m_tx_over_mask                                             (0x00000008)
#define ISO_IC0_INTR_MASK_m_tx_over(data)                                            (0x00000008&((data)<<3))
#define ISO_IC0_INTR_MASK_m_tx_over_src(data)                                        ((0x00000008&(data))>>3)
#define ISO_IC0_INTR_MASK_get_m_tx_over(data)                                        ((0x00000008&(data))>>3)
#define ISO_IC0_INTR_MASK_m_rx_full_shift                                            (2)
#define ISO_IC0_INTR_MASK_m_rx_full_mask                                             (0x00000004)
#define ISO_IC0_INTR_MASK_m_rx_full(data)                                            (0x00000004&((data)<<2))
#define ISO_IC0_INTR_MASK_m_rx_full_src(data)                                        ((0x00000004&(data))>>2)
#define ISO_IC0_INTR_MASK_get_m_rx_full(data)                                        ((0x00000004&(data))>>2)
#define ISO_IC0_INTR_MASK_m_rx_over_shift                                            (1)
#define ISO_IC0_INTR_MASK_m_rx_over_mask                                             (0x00000002)
#define ISO_IC0_INTR_MASK_m_rx_over(data)                                            (0x00000002&((data)<<1))
#define ISO_IC0_INTR_MASK_m_rx_over_src(data)                                        ((0x00000002&(data))>>1)
#define ISO_IC0_INTR_MASK_get_m_rx_over(data)                                        ((0x00000002&(data))>>1)
#define ISO_IC0_INTR_MASK_m_rx_under_shift                                           (0)
#define ISO_IC0_INTR_MASK_m_rx_under_mask                                            (0x00000001)
#define ISO_IC0_INTR_MASK_m_rx_under(data)                                           (0x00000001&((data)<<0))
#define ISO_IC0_INTR_MASK_m_rx_under_src(data)                                       ((0x00000001&(data))>>0)
#define ISO_IC0_INTR_MASK_get_m_rx_under(data)                                       ((0x00000001&(data))>>0)


#define ISO_IC0_RAW_INTR_STAT                                                        0x98007D34
#define ISO_IC0_RAW_INTR_STAT_reg_addr                                               "0x98007D34"
#define ISO_IC0_RAW_INTR_STAT_reg                                                    0x98007D34
#define set_ISO_IC0_RAW_INTR_STAT_reg(data)   (*((volatile unsigned int*) ISO_IC0_RAW_INTR_STAT_reg)=data)
#define get_ISO_IC0_RAW_INTR_STAT_reg   (*((volatile unsigned int*) ISO_IC0_RAW_INTR_STAT_reg))
#define ISO_IC0_RAW_INTR_STAT_inst_adr                                               "0x004D"
#define ISO_IC0_RAW_INTR_STAT_inst                                                   0x004D
#define ISO_IC0_RAW_INTR_STAT_gen_call_shift                                         (11)
#define ISO_IC0_RAW_INTR_STAT_gen_call_mask                                          (0x00000800)
#define ISO_IC0_RAW_INTR_STAT_gen_call(data)                                         (0x00000800&((data)<<11))
#define ISO_IC0_RAW_INTR_STAT_gen_call_src(data)                                     ((0x00000800&(data))>>11)
#define ISO_IC0_RAW_INTR_STAT_get_gen_call(data)                                     ((0x00000800&(data))>>11)
#define ISO_IC0_RAW_INTR_STAT_start_det_shift                                        (10)
#define ISO_IC0_RAW_INTR_STAT_start_det_mask                                         (0x00000400)
#define ISO_IC0_RAW_INTR_STAT_start_det(data)                                        (0x00000400&((data)<<10))
#define ISO_IC0_RAW_INTR_STAT_start_det_src(data)                                    ((0x00000400&(data))>>10)
#define ISO_IC0_RAW_INTR_STAT_get_start_det(data)                                    ((0x00000400&(data))>>10)
#define ISO_IC0_RAW_INTR_STAT_stop_det_shift                                         (9)
#define ISO_IC0_RAW_INTR_STAT_stop_det_mask                                          (0x00000200)
#define ISO_IC0_RAW_INTR_STAT_stop_det(data)                                         (0x00000200&((data)<<9))
#define ISO_IC0_RAW_INTR_STAT_stop_det_src(data)                                     ((0x00000200&(data))>>9)
#define ISO_IC0_RAW_INTR_STAT_get_stop_det(data)                                     ((0x00000200&(data))>>9)
#define ISO_IC0_RAW_INTR_STAT_activity_shift                                         (8)
#define ISO_IC0_RAW_INTR_STAT_activity_mask                                          (0x00000100)
#define ISO_IC0_RAW_INTR_STAT_activity(data)                                         (0x00000100&((data)<<8))
#define ISO_IC0_RAW_INTR_STAT_activity_src(data)                                     ((0x00000100&(data))>>8)
#define ISO_IC0_RAW_INTR_STAT_get_activity(data)                                     ((0x00000100&(data))>>8)
#define ISO_IC0_RAW_INTR_STAT_rx_done_shift                                          (7)
#define ISO_IC0_RAW_INTR_STAT_rx_done_mask                                           (0x00000080)
#define ISO_IC0_RAW_INTR_STAT_rx_done(data)                                          (0x00000080&((data)<<7))
#define ISO_IC0_RAW_INTR_STAT_rx_done_src(data)                                      ((0x00000080&(data))>>7)
#define ISO_IC0_RAW_INTR_STAT_get_rx_done(data)                                      ((0x00000080&(data))>>7)
#define ISO_IC0_RAW_INTR_STAT_tx_abrt_shift                                          (6)
#define ISO_IC0_RAW_INTR_STAT_tx_abrt_mask                                           (0x00000040)
#define ISO_IC0_RAW_INTR_STAT_tx_abrt(data)                                          (0x00000040&((data)<<6))
#define ISO_IC0_RAW_INTR_STAT_tx_abrt_src(data)                                      ((0x00000040&(data))>>6)
#define ISO_IC0_RAW_INTR_STAT_get_tx_abrt(data)                                      ((0x00000040&(data))>>6)
#define ISO_IC0_RAW_INTR_STAT_rd_req_shift                                           (5)
#define ISO_IC0_RAW_INTR_STAT_rd_req_mask                                            (0x00000020)
#define ISO_IC0_RAW_INTR_STAT_rd_req(data)                                           (0x00000020&((data)<<5))
#define ISO_IC0_RAW_INTR_STAT_rd_req_src(data)                                       ((0x00000020&(data))>>5)
#define ISO_IC0_RAW_INTR_STAT_get_rd_req(data)                                       ((0x00000020&(data))>>5)
#define ISO_IC0_RAW_INTR_STAT_tx_empty_shift                                         (4)
#define ISO_IC0_RAW_INTR_STAT_tx_empty_mask                                          (0x00000010)
#define ISO_IC0_RAW_INTR_STAT_tx_empty(data)                                         (0x00000010&((data)<<4))
#define ISO_IC0_RAW_INTR_STAT_tx_empty_src(data)                                     ((0x00000010&(data))>>4)
#define ISO_IC0_RAW_INTR_STAT_get_tx_empty(data)                                     ((0x00000010&(data))>>4)
#define ISO_IC0_RAW_INTR_STAT_tx_over_shift                                          (3)
#define ISO_IC0_RAW_INTR_STAT_tx_over_mask                                           (0x00000008)
#define ISO_IC0_RAW_INTR_STAT_tx_over(data)                                          (0x00000008&((data)<<3))
#define ISO_IC0_RAW_INTR_STAT_tx_over_src(data)                                      ((0x00000008&(data))>>3)
#define ISO_IC0_RAW_INTR_STAT_get_tx_over(data)                                      ((0x00000008&(data))>>3)
#define ISO_IC0_RAW_INTR_STAT_rx_full_shift                                          (2)
#define ISO_IC0_RAW_INTR_STAT_rx_full_mask                                           (0x00000004)
#define ISO_IC0_RAW_INTR_STAT_rx_full(data)                                          (0x00000004&((data)<<2))
#define ISO_IC0_RAW_INTR_STAT_rx_full_src(data)                                      ((0x00000004&(data))>>2)
#define ISO_IC0_RAW_INTR_STAT_get_rx_full(data)                                      ((0x00000004&(data))>>2)
#define ISO_IC0_RAW_INTR_STAT_rx_over_shift                                          (1)
#define ISO_IC0_RAW_INTR_STAT_rx_over_mask                                           (0x00000002)
#define ISO_IC0_RAW_INTR_STAT_rx_over(data)                                          (0x00000002&((data)<<1))
#define ISO_IC0_RAW_INTR_STAT_rx_over_src(data)                                      ((0x00000002&(data))>>1)
#define ISO_IC0_RAW_INTR_STAT_get_rx_over(data)                                      ((0x00000002&(data))>>1)
#define ISO_IC0_RAW_INTR_STAT_rx_under_shift                                         (0)
#define ISO_IC0_RAW_INTR_STAT_rx_under_mask                                          (0x00000001)
#define ISO_IC0_RAW_INTR_STAT_rx_under(data)                                         (0x00000001&((data)<<0))
#define ISO_IC0_RAW_INTR_STAT_rx_under_src(data)                                     ((0x00000001&(data))>>0)
#define ISO_IC0_RAW_INTR_STAT_get_rx_under(data)                                     ((0x00000001&(data))>>0)


#define ISO_IC0_RX_TL                                                                0x98007D38
#define ISO_IC0_RX_TL_reg_addr                                                       "0x98007D38"
#define ISO_IC0_RX_TL_reg                                                            0x98007D38
#define set_ISO_IC0_RX_TL_reg(data)   (*((volatile unsigned int*) ISO_IC0_RX_TL_reg)=data)
#define get_ISO_IC0_RX_TL_reg   (*((volatile unsigned int*) ISO_IC0_RX_TL_reg))
#define ISO_IC0_RX_TL_inst_adr                                                       "0x004E"
#define ISO_IC0_RX_TL_inst                                                           0x004E
#define ISO_IC0_RX_TL_rx_tl_shift                                                    (0)
#define ISO_IC0_RX_TL_rx_tl_mask                                                     (0x000000FF)
#define ISO_IC0_RX_TL_rx_tl(data)                                                    (0x000000FF&((data)<<0))
#define ISO_IC0_RX_TL_rx_tl_src(data)                                                ((0x000000FF&(data))>>0)
#define ISO_IC0_RX_TL_get_rx_tl(data)                                                ((0x000000FF&(data))>>0)


#define ISO_IC0_TX_TL                                                                0x98007D3C
#define ISO_IC0_TX_TL_reg_addr                                                       "0x98007D3C"
#define ISO_IC0_TX_TL_reg                                                            0x98007D3C
#define set_ISO_IC0_TX_TL_reg(data)   (*((volatile unsigned int*) ISO_IC0_TX_TL_reg)=data)
#define get_ISO_IC0_TX_TL_reg   (*((volatile unsigned int*) ISO_IC0_TX_TL_reg))
#define ISO_IC0_TX_TL_inst_adr                                                       "0x004F"
#define ISO_IC0_TX_TL_inst                                                           0x004F
#define ISO_IC0_TX_TL_tx_tl_shift                                                    (0)
#define ISO_IC0_TX_TL_tx_tl_mask                                                     (0x000000FF)
#define ISO_IC0_TX_TL_tx_tl(data)                                                    (0x000000FF&((data)<<0))
#define ISO_IC0_TX_TL_tx_tl_src(data)                                                ((0x000000FF&(data))>>0)
#define ISO_IC0_TX_TL_get_tx_tl(data)                                                ((0x000000FF&(data))>>0)


#define ISO_IC0_CLR_INTR                                                             0x98007D40
#define ISO_IC0_CLR_INTR_reg_addr                                                    "0x98007D40"
#define ISO_IC0_CLR_INTR_reg                                                         0x98007D40
#define set_ISO_IC0_CLR_INTR_reg(data)   (*((volatile unsigned int*) ISO_IC0_CLR_INTR_reg)=data)
#define get_ISO_IC0_CLR_INTR_reg   (*((volatile unsigned int*) ISO_IC0_CLR_INTR_reg))
#define ISO_IC0_CLR_INTR_inst_adr                                                    "0x0050"
#define ISO_IC0_CLR_INTR_inst                                                        0x0050
#define ISO_IC0_CLR_INTR_clr_intr_shift                                              (0)
#define ISO_IC0_CLR_INTR_clr_intr_mask                                               (0x00000001)
#define ISO_IC0_CLR_INTR_clr_intr(data)                                              (0x00000001&((data)<<0))
#define ISO_IC0_CLR_INTR_clr_intr_src(data)                                          ((0x00000001&(data))>>0)
#define ISO_IC0_CLR_INTR_get_clr_intr(data)                                          ((0x00000001&(data))>>0)


#define ISO_IC0_CLR_RX_UNDER                                                         0x98007D44
#define ISO_IC0_CLR_RX_UNDER_reg_addr                                                "0x98007D44"
#define ISO_IC0_CLR_RX_UNDER_reg                                                     0x98007D44
#define set_ISO_IC0_CLR_RX_UNDER_reg(data)   (*((volatile unsigned int*) ISO_IC0_CLR_RX_UNDER_reg)=data)
#define get_ISO_IC0_CLR_RX_UNDER_reg   (*((volatile unsigned int*) ISO_IC0_CLR_RX_UNDER_reg))
#define ISO_IC0_CLR_RX_UNDER_inst_adr                                                "0x0051"
#define ISO_IC0_CLR_RX_UNDER_inst                                                    0x0051
#define ISO_IC0_CLR_RX_UNDER_clr_rx_under_shift                                      (0)
#define ISO_IC0_CLR_RX_UNDER_clr_rx_under_mask                                       (0x00000001)
#define ISO_IC0_CLR_RX_UNDER_clr_rx_under(data)                                      (0x00000001&((data)<<0))
#define ISO_IC0_CLR_RX_UNDER_clr_rx_under_src(data)                                  ((0x00000001&(data))>>0)
#define ISO_IC0_CLR_RX_UNDER_get_clr_rx_under(data)                                  ((0x00000001&(data))>>0)


#define ISO_IC0_CLR_RX_OVER                                                          0x98007D48
#define ISO_IC0_CLR_RX_OVER_reg_addr                                                 "0x98007D48"
#define ISO_IC0_CLR_RX_OVER_reg                                                      0x98007D48
#define set_ISO_IC0_CLR_RX_OVER_reg(data)   (*((volatile unsigned int*) ISO_IC0_CLR_RX_OVER_reg)=data)
#define get_ISO_IC0_CLR_RX_OVER_reg   (*((volatile unsigned int*) ISO_IC0_CLR_RX_OVER_reg))
#define ISO_IC0_CLR_RX_OVER_inst_adr                                                 "0x0052"
#define ISO_IC0_CLR_RX_OVER_inst                                                     0x0052
#define ISO_IC0_CLR_RX_OVER_clr_rx_over_shift                                        (0)
#define ISO_IC0_CLR_RX_OVER_clr_rx_over_mask                                         (0x00000001)
#define ISO_IC0_CLR_RX_OVER_clr_rx_over(data)                                        (0x00000001&((data)<<0))
#define ISO_IC0_CLR_RX_OVER_clr_rx_over_src(data)                                    ((0x00000001&(data))>>0)
#define ISO_IC0_CLR_RX_OVER_get_clr_rx_over(data)                                    ((0x00000001&(data))>>0)


#define ISO_IC0_CLR_TX_OVER                                                          0x98007D4C
#define ISO_IC0_CLR_TX_OVER_reg_addr                                                 "0x98007D4C"
#define ISO_IC0_CLR_TX_OVER_reg                                                      0x98007D4C
#define set_ISO_IC0_CLR_TX_OVER_reg(data)   (*((volatile unsigned int*) ISO_IC0_CLR_TX_OVER_reg)=data)
#define get_ISO_IC0_CLR_TX_OVER_reg   (*((volatile unsigned int*) ISO_IC0_CLR_TX_OVER_reg))
#define ISO_IC0_CLR_TX_OVER_inst_adr                                                 "0x0053"
#define ISO_IC0_CLR_TX_OVER_inst                                                     0x0053
#define ISO_IC0_CLR_TX_OVER_clr_tx_over_shift                                        (0)
#define ISO_IC0_CLR_TX_OVER_clr_tx_over_mask                                         (0x00000001)
#define ISO_IC0_CLR_TX_OVER_clr_tx_over(data)                                        (0x00000001&((data)<<0))
#define ISO_IC0_CLR_TX_OVER_clr_tx_over_src(data)                                    ((0x00000001&(data))>>0)
#define ISO_IC0_CLR_TX_OVER_get_clr_tx_over(data)                                    ((0x00000001&(data))>>0)


#define ISO_IC0_CLR_RD_REQ                                                           0x98007D50
#define ISO_IC0_CLR_RD_REQ_reg_addr                                                  "0x98007D50"
#define ISO_IC0_CLR_RD_REQ_reg                                                       0x98007D50
#define set_ISO_IC0_CLR_RD_REQ_reg(data)   (*((volatile unsigned int*) ISO_IC0_CLR_RD_REQ_reg)=data)
#define get_ISO_IC0_CLR_RD_REQ_reg   (*((volatile unsigned int*) ISO_IC0_CLR_RD_REQ_reg))
#define ISO_IC0_CLR_RD_REQ_inst_adr                                                  "0x0054"
#define ISO_IC0_CLR_RD_REQ_inst                                                      0x0054
#define ISO_IC0_CLR_RD_REQ_clr_rd_req_shift                                          (0)
#define ISO_IC0_CLR_RD_REQ_clr_rd_req_mask                                           (0x00000001)
#define ISO_IC0_CLR_RD_REQ_clr_rd_req(data)                                          (0x00000001&((data)<<0))
#define ISO_IC0_CLR_RD_REQ_clr_rd_req_src(data)                                      ((0x00000001&(data))>>0)
#define ISO_IC0_CLR_RD_REQ_get_clr_rd_req(data)                                      ((0x00000001&(data))>>0)


#define ISO_IC0_CLR_TX_ABRT                                                          0x98007D54
#define ISO_IC0_CLR_TX_ABRT_reg_addr                                                 "0x98007D54"
#define ISO_IC0_CLR_TX_ABRT_reg                                                      0x98007D54
#define set_ISO_IC0_CLR_TX_ABRT_reg(data)   (*((volatile unsigned int*) ISO_IC0_CLR_TX_ABRT_reg)=data)
#define get_ISO_IC0_CLR_TX_ABRT_reg   (*((volatile unsigned int*) ISO_IC0_CLR_TX_ABRT_reg))
#define ISO_IC0_CLR_TX_ABRT_inst_adr                                                 "0x0055"
#define ISO_IC0_CLR_TX_ABRT_inst                                                     0x0055
#define ISO_IC0_CLR_TX_ABRT_clr_tx_abrt_shift                                        (0)
#define ISO_IC0_CLR_TX_ABRT_clr_tx_abrt_mask                                         (0x00000001)
#define ISO_IC0_CLR_TX_ABRT_clr_tx_abrt(data)                                        (0x00000001&((data)<<0))
#define ISO_IC0_CLR_TX_ABRT_clr_tx_abrt_src(data)                                    ((0x00000001&(data))>>0)
#define ISO_IC0_CLR_TX_ABRT_get_clr_tx_abrt(data)                                    ((0x00000001&(data))>>0)


#define ISO_IC0_CLR_RX_DONE                                                          0x98007D58
#define ISO_IC0_CLR_RX_DONE_reg_addr                                                 "0x98007D58"
#define ISO_IC0_CLR_RX_DONE_reg                                                      0x98007D58
#define set_ISO_IC0_CLR_RX_DONE_reg(data)   (*((volatile unsigned int*) ISO_IC0_CLR_RX_DONE_reg)=data)
#define get_ISO_IC0_CLR_RX_DONE_reg   (*((volatile unsigned int*) ISO_IC0_CLR_RX_DONE_reg))
#define ISO_IC0_CLR_RX_DONE_inst_adr                                                 "0x0056"
#define ISO_IC0_CLR_RX_DONE_inst                                                     0x0056
#define ISO_IC0_CLR_RX_DONE_clr_rx_done_shift                                        (0)
#define ISO_IC0_CLR_RX_DONE_clr_rx_done_mask                                         (0x00000001)
#define ISO_IC0_CLR_RX_DONE_clr_rx_done(data)                                        (0x00000001&((data)<<0))
#define ISO_IC0_CLR_RX_DONE_clr_rx_done_src(data)                                    ((0x00000001&(data))>>0)
#define ISO_IC0_CLR_RX_DONE_get_clr_rx_done(data)                                    ((0x00000001&(data))>>0)


#define ISO_IC0_CLR_ACTIVITY                                                         0x98007D5C
#define ISO_IC0_CLR_ACTIVITY_reg_addr                                                "0x98007D5C"
#define ISO_IC0_CLR_ACTIVITY_reg                                                     0x98007D5C
#define set_ISO_IC0_CLR_ACTIVITY_reg(data)   (*((volatile unsigned int*) ISO_IC0_CLR_ACTIVITY_reg)=data)
#define get_ISO_IC0_CLR_ACTIVITY_reg   (*((volatile unsigned int*) ISO_IC0_CLR_ACTIVITY_reg))
#define ISO_IC0_CLR_ACTIVITY_inst_adr                                                "0x0057"
#define ISO_IC0_CLR_ACTIVITY_inst                                                    0x0057
#define ISO_IC0_CLR_ACTIVITY_clr_activity_shift                                      (0)
#define ISO_IC0_CLR_ACTIVITY_clr_activity_mask                                       (0x00000001)
#define ISO_IC0_CLR_ACTIVITY_clr_activity(data)                                      (0x00000001&((data)<<0))
#define ISO_IC0_CLR_ACTIVITY_clr_activity_src(data)                                  ((0x00000001&(data))>>0)
#define ISO_IC0_CLR_ACTIVITY_get_clr_activity(data)                                  ((0x00000001&(data))>>0)


#define ISO_IC0_CLR_STOP_DET                                                         0x98007D60
#define ISO_IC0_CLR_STOP_DET_reg_addr                                                "0x98007D60"
#define ISO_IC0_CLR_STOP_DET_reg                                                     0x98007D60
#define set_ISO_IC0_CLR_STOP_DET_reg(data)   (*((volatile unsigned int*) ISO_IC0_CLR_STOP_DET_reg)=data)
#define get_ISO_IC0_CLR_STOP_DET_reg   (*((volatile unsigned int*) ISO_IC0_CLR_STOP_DET_reg))
#define ISO_IC0_CLR_STOP_DET_inst_adr                                                "0x0058"
#define ISO_IC0_CLR_STOP_DET_inst                                                    0x0058
#define ISO_IC0_CLR_STOP_DET_clr_stop_det_shift                                      (0)
#define ISO_IC0_CLR_STOP_DET_clr_stop_det_mask                                       (0x00000001)
#define ISO_IC0_CLR_STOP_DET_clr_stop_det(data)                                      (0x00000001&((data)<<0))
#define ISO_IC0_CLR_STOP_DET_clr_stop_det_src(data)                                  ((0x00000001&(data))>>0)
#define ISO_IC0_CLR_STOP_DET_get_clr_stop_det(data)                                  ((0x00000001&(data))>>0)


#define ISO_IC0_CLR_START_DET                                                        0x98007D64
#define ISO_IC0_CLR_START_DET_reg_addr                                               "0x98007D64"
#define ISO_IC0_CLR_START_DET_reg                                                    0x98007D64
#define set_ISO_IC0_CLR_START_DET_reg(data)   (*((volatile unsigned int*) ISO_IC0_CLR_START_DET_reg)=data)
#define get_ISO_IC0_CLR_START_DET_reg   (*((volatile unsigned int*) ISO_IC0_CLR_START_DET_reg))
#define ISO_IC0_CLR_START_DET_inst_adr                                               "0x0059"
#define ISO_IC0_CLR_START_DET_inst                                                   0x0059
#define ISO_IC0_CLR_START_DET_clr_start_det_shift                                    (0)
#define ISO_IC0_CLR_START_DET_clr_start_det_mask                                     (0x00000001)
#define ISO_IC0_CLR_START_DET_clr_start_det(data)                                    (0x00000001&((data)<<0))
#define ISO_IC0_CLR_START_DET_clr_start_det_src(data)                                ((0x00000001&(data))>>0)
#define ISO_IC0_CLR_START_DET_get_clr_start_det(data)                                ((0x00000001&(data))>>0)


#define ISO_IC0_CLR_GEN_CALL                                                         0x98007D68
#define ISO_IC0_CLR_GEN_CALL_reg_addr                                                "0x98007D68"
#define ISO_IC0_CLR_GEN_CALL_reg                                                     0x98007D68
#define set_ISO_IC0_CLR_GEN_CALL_reg(data)   (*((volatile unsigned int*) ISO_IC0_CLR_GEN_CALL_reg)=data)
#define get_ISO_IC0_CLR_GEN_CALL_reg   (*((volatile unsigned int*) ISO_IC0_CLR_GEN_CALL_reg))
#define ISO_IC0_CLR_GEN_CALL_inst_adr                                                "0x005A"
#define ISO_IC0_CLR_GEN_CALL_inst                                                    0x005A
#define ISO_IC0_CLR_GEN_CALL_clr_gen_call_shift                                      (0)
#define ISO_IC0_CLR_GEN_CALL_clr_gen_call_mask                                       (0x00000001)
#define ISO_IC0_CLR_GEN_CALL_clr_gen_call(data)                                      (0x00000001&((data)<<0))
#define ISO_IC0_CLR_GEN_CALL_clr_gen_call_src(data)                                  ((0x00000001&(data))>>0)
#define ISO_IC0_CLR_GEN_CALL_get_clr_gen_call(data)                                  ((0x00000001&(data))>>0)


#define ISO_IC0_ENABLE                                                               0x98007D6C
#define ISO_IC0_ENABLE_reg_addr                                                      "0x98007D6C"
#define ISO_IC0_ENABLE_reg                                                           0x98007D6C
#define set_ISO_IC0_ENABLE_reg(data)   (*((volatile unsigned int*) ISO_IC0_ENABLE_reg)=data)
#define get_ISO_IC0_ENABLE_reg   (*((volatile unsigned int*) ISO_IC0_ENABLE_reg))
#define ISO_IC0_ENABLE_inst_adr                                                      "0x005B"
#define ISO_IC0_ENABLE_inst                                                          0x005B
#define ISO_IC0_ENABLE_enable_shift                                                  (0)
#define ISO_IC0_ENABLE_enable_mask                                                   (0x00000001)
#define ISO_IC0_ENABLE_enable(data)                                                  (0x00000001&((data)<<0))
#define ISO_IC0_ENABLE_enable_src(data)                                              ((0x00000001&(data))>>0)
#define ISO_IC0_ENABLE_get_enable(data)                                              ((0x00000001&(data))>>0)


#define ISO_IC0_STATUS                                                               0x98007D70
#define ISO_IC0_STATUS_reg_addr                                                      "0x98007D70"
#define ISO_IC0_STATUS_reg                                                           0x98007D70
#define set_ISO_IC0_STATUS_reg(data)   (*((volatile unsigned int*) ISO_IC0_STATUS_reg)=data)
#define get_ISO_IC0_STATUS_reg   (*((volatile unsigned int*) ISO_IC0_STATUS_reg))
#define ISO_IC0_STATUS_inst_adr                                                      "0x005C"
#define ISO_IC0_STATUS_inst                                                          0x005C
#define ISO_IC0_STATUS_slv_activity_shift                                            (6)
#define ISO_IC0_STATUS_slv_activity_mask                                             (0x00000040)
#define ISO_IC0_STATUS_slv_activity(data)                                            (0x00000040&((data)<<6))
#define ISO_IC0_STATUS_slv_activity_src(data)                                        ((0x00000040&(data))>>6)
#define ISO_IC0_STATUS_get_slv_activity(data)                                        ((0x00000040&(data))>>6)
#define ISO_IC0_STATUS_mst_activity_shift                                            (5)
#define ISO_IC0_STATUS_mst_activity_mask                                             (0x00000020)
#define ISO_IC0_STATUS_mst_activity(data)                                            (0x00000020&((data)<<5))
#define ISO_IC0_STATUS_mst_activity_src(data)                                        ((0x00000020&(data))>>5)
#define ISO_IC0_STATUS_get_mst_activity(data)                                        ((0x00000020&(data))>>5)
#define ISO_IC0_STATUS_rff_shift                                                     (4)
#define ISO_IC0_STATUS_rff_mask                                                      (0x00000010)
#define ISO_IC0_STATUS_rff(data)                                                     (0x00000010&((data)<<4))
#define ISO_IC0_STATUS_rff_src(data)                                                 ((0x00000010&(data))>>4)
#define ISO_IC0_STATUS_get_rff(data)                                                 ((0x00000010&(data))>>4)
#define ISO_IC0_STATUS_rfne_shift                                                    (3)
#define ISO_IC0_STATUS_rfne_mask                                                     (0x00000008)
#define ISO_IC0_STATUS_rfne(data)                                                    (0x00000008&((data)<<3))
#define ISO_IC0_STATUS_rfne_src(data)                                                ((0x00000008&(data))>>3)
#define ISO_IC0_STATUS_get_rfne(data)                                                ((0x00000008&(data))>>3)
#define ISO_IC0_STATUS_tfe_shift                                                     (2)
#define ISO_IC0_STATUS_tfe_mask                                                      (0x00000004)
#define ISO_IC0_STATUS_tfe(data)                                                     (0x00000004&((data)<<2))
#define ISO_IC0_STATUS_tfe_src(data)                                                 ((0x00000004&(data))>>2)
#define ISO_IC0_STATUS_get_tfe(data)                                                 ((0x00000004&(data))>>2)
#define ISO_IC0_STATUS_tfnf_shift                                                    (1)
#define ISO_IC0_STATUS_tfnf_mask                                                     (0x00000002)
#define ISO_IC0_STATUS_tfnf(data)                                                    (0x00000002&((data)<<1))
#define ISO_IC0_STATUS_tfnf_src(data)                                                ((0x00000002&(data))>>1)
#define ISO_IC0_STATUS_get_tfnf(data)                                                ((0x00000002&(data))>>1)
#define ISO_IC0_STATUS_activity_shift                                                (0)
#define ISO_IC0_STATUS_activity_mask                                                 (0x00000001)
#define ISO_IC0_STATUS_activity(data)                                                (0x00000001&((data)<<0))
#define ISO_IC0_STATUS_activity_src(data)                                            ((0x00000001&(data))>>0)
#define ISO_IC0_STATUS_get_activity(data)                                            ((0x00000001&(data))>>0)


#define ISO_IC0_TXFLR                                                                0x98007D74
#define ISO_IC0_TXFLR_reg_addr                                                       "0x98007D74"
#define ISO_IC0_TXFLR_reg                                                            0x98007D74
#define set_ISO_IC0_TXFLR_reg(data)   (*((volatile unsigned int*) ISO_IC0_TXFLR_reg)=data)
#define get_ISO_IC0_TXFLR_reg   (*((volatile unsigned int*) ISO_IC0_TXFLR_reg))
#define ISO_IC0_TXFLR_inst_adr                                                       "0x005D"
#define ISO_IC0_TXFLR_inst                                                           0x005D
#define ISO_IC0_TXFLR_txflr_shift                                                    (0)
#define ISO_IC0_TXFLR_txflr_mask                                                     (0x0000000F)
#define ISO_IC0_TXFLR_txflr(data)                                                    (0x0000000F&((data)<<0))
#define ISO_IC0_TXFLR_txflr_src(data)                                                ((0x0000000F&(data))>>0)
#define ISO_IC0_TXFLR_get_txflr(data)                                                ((0x0000000F&(data))>>0)


#define ISO_IC0_RXFLR                                                                0x98007D78
#define ISO_IC0_RXFLR_reg_addr                                                       "0x98007D78"
#define ISO_IC0_RXFLR_reg                                                            0x98007D78
#define set_ISO_IC0_RXFLR_reg(data)   (*((volatile unsigned int*) ISO_IC0_RXFLR_reg)=data)
#define get_ISO_IC0_RXFLR_reg   (*((volatile unsigned int*) ISO_IC0_RXFLR_reg))
#define ISO_IC0_RXFLR_inst_adr                                                       "0x005E"
#define ISO_IC0_RXFLR_inst                                                           0x005E
#define ISO_IC0_RXFLR_rxflr_shift                                                    (0)
#define ISO_IC0_RXFLR_rxflr_mask                                                     (0x0000000F)
#define ISO_IC0_RXFLR_rxflr(data)                                                    (0x0000000F&((data)<<0))
#define ISO_IC0_RXFLR_rxflr_src(data)                                                ((0x0000000F&(data))>>0)
#define ISO_IC0_RXFLR_get_rxflr(data)                                                ((0x0000000F&(data))>>0)


#define ISO_IC0_SDA_HOLD                                                             0x98007D7C
#define ISO_IC0_SDA_HOLD_reg_addr                                                    "0x98007D7C"
#define ISO_IC0_SDA_HOLD_reg                                                         0x98007D7C
#define set_ISO_IC0_SDA_HOLD_reg(data)   (*((volatile unsigned int*) ISO_IC0_SDA_HOLD_reg)=data)
#define get_ISO_IC0_SDA_HOLD_reg   (*((volatile unsigned int*) ISO_IC0_SDA_HOLD_reg))
#define ISO_IC0_SDA_HOLD_inst_adr                                                    "0x005F"
#define ISO_IC0_SDA_HOLD_inst                                                        0x005F
#define ISO_IC0_SDA_HOLD_ic_sda_hold_shift                                           (0)
#define ISO_IC0_SDA_HOLD_ic_sda_hold_mask                                            (0x0000FFFF)
#define ISO_IC0_SDA_HOLD_ic_sda_hold(data)                                           (0x0000FFFF&((data)<<0))
#define ISO_IC0_SDA_HOLD_ic_sda_hold_src(data)                                       ((0x0000FFFF&(data))>>0)
#define ISO_IC0_SDA_HOLD_get_ic_sda_hold(data)                                       ((0x0000FFFF&(data))>>0)


#define ISO_IC0_TX_ABRT_SOURCE                                                       0x98007D80
#define ISO_IC0_TX_ABRT_SOURCE_reg_addr                                              "0x98007D80"
#define ISO_IC0_TX_ABRT_SOURCE_reg                                                   0x98007D80
#define set_ISO_IC0_TX_ABRT_SOURCE_reg(data)   (*((volatile unsigned int*) ISO_IC0_TX_ABRT_SOURCE_reg)=data)
#define get_ISO_IC0_TX_ABRT_SOURCE_reg   (*((volatile unsigned int*) ISO_IC0_TX_ABRT_SOURCE_reg))
#define ISO_IC0_TX_ABRT_SOURCE_inst_adr                                              "0x0060"
#define ISO_IC0_TX_ABRT_SOURCE_inst                                                  0x0060
#define ISO_IC0_TX_ABRT_SOURCE_abrt_slvrd_intx_shift                                 (15)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_slvrd_intx_mask                                  (0x00008000)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_slvrd_intx(data)                                 (0x00008000&((data)<<15))
#define ISO_IC0_TX_ABRT_SOURCE_abrt_slvrd_intx_src(data)                             ((0x00008000&(data))>>15)
#define ISO_IC0_TX_ABRT_SOURCE_get_abrt_slvrd_intx(data)                             ((0x00008000&(data))>>15)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_slv_arblost_shift                                (14)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_slv_arblost_mask                                 (0x00004000)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_slv_arblost(data)                                (0x00004000&((data)<<14))
#define ISO_IC0_TX_ABRT_SOURCE_abrt_slv_arblost_src(data)                            ((0x00004000&(data))>>14)
#define ISO_IC0_TX_ABRT_SOURCE_get_abrt_slv_arblost(data)                            ((0x00004000&(data))>>14)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_slvflush_txfifo_shift                            (13)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_slvflush_txfifo_mask                             (0x00002000)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_slvflush_txfifo(data)                            (0x00002000&((data)<<13))
#define ISO_IC0_TX_ABRT_SOURCE_abrt_slvflush_txfifo_src(data)                        ((0x00002000&(data))>>13)
#define ISO_IC0_TX_ABRT_SOURCE_get_abrt_slvflush_txfifo(data)                        ((0x00002000&(data))>>13)
#define ISO_IC0_TX_ABRT_SOURCE_arb_lost_shift                                        (12)
#define ISO_IC0_TX_ABRT_SOURCE_arb_lost_mask                                         (0x00001000)
#define ISO_IC0_TX_ABRT_SOURCE_arb_lost(data)                                        (0x00001000&((data)<<12))
#define ISO_IC0_TX_ABRT_SOURCE_arb_lost_src(data)                                    ((0x00001000&(data))>>12)
#define ISO_IC0_TX_ABRT_SOURCE_get_arb_lost(data)                                    ((0x00001000&(data))>>12)
#define ISO_IC0_TX_ABRT_SOURCE_arb_master_dis_shift                                  (11)
#define ISO_IC0_TX_ABRT_SOURCE_arb_master_dis_mask                                   (0x00000800)
#define ISO_IC0_TX_ABRT_SOURCE_arb_master_dis(data)                                  (0x00000800&((data)<<11))
#define ISO_IC0_TX_ABRT_SOURCE_arb_master_dis_src(data)                              ((0x00000800&(data))>>11)
#define ISO_IC0_TX_ABRT_SOURCE_get_arb_master_dis(data)                              ((0x00000800&(data))>>11)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_10b_rd_norstrt_shift                             (10)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_10b_rd_norstrt_mask                              (0x00000400)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_10b_rd_norstrt(data)                             (0x00000400&((data)<<10))
#define ISO_IC0_TX_ABRT_SOURCE_abrt_10b_rd_norstrt_src(data)                         ((0x00000400&(data))>>10)
#define ISO_IC0_TX_ABRT_SOURCE_get_abrt_10b_rd_norstrt(data)                         ((0x00000400&(data))>>10)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_sbyte_norstrt_shift                              (9)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_sbyte_norstrt_mask                               (0x00000200)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_sbyte_norstrt(data)                              (0x00000200&((data)<<9))
#define ISO_IC0_TX_ABRT_SOURCE_abrt_sbyte_norstrt_src(data)                          ((0x00000200&(data))>>9)
#define ISO_IC0_TX_ABRT_SOURCE_get_abrt_sbyte_norstrt(data)                          ((0x00000200&(data))>>9)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_hs_norstrt_shift                                 (8)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_hs_norstrt_mask                                  (0x00000100)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_hs_norstrt(data)                                 (0x00000100&((data)<<8))
#define ISO_IC0_TX_ABRT_SOURCE_abrt_hs_norstrt_src(data)                             ((0x00000100&(data))>>8)
#define ISO_IC0_TX_ABRT_SOURCE_get_abrt_hs_norstrt(data)                             ((0x00000100&(data))>>8)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_sbyte_ackdet_shift                               (7)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_sbyte_ackdet_mask                                (0x00000080)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_sbyte_ackdet(data)                               (0x00000080&((data)<<7))
#define ISO_IC0_TX_ABRT_SOURCE_abrt_sbyte_ackdet_src(data)                           ((0x00000080&(data))>>7)
#define ISO_IC0_TX_ABRT_SOURCE_get_abrt_sbyte_ackdet(data)                           ((0x00000080&(data))>>7)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_hs_ackdet_shift                                  (6)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_hs_ackdet_mask                                   (0x00000040)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_hs_ackdet(data)                                  (0x00000040&((data)<<6))
#define ISO_IC0_TX_ABRT_SOURCE_abrt_hs_ackdet_src(data)                              ((0x00000040&(data))>>6)
#define ISO_IC0_TX_ABRT_SOURCE_get_abrt_hs_ackdet(data)                              ((0x00000040&(data))>>6)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_gcall_read_shift                                 (5)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_gcall_read_mask                                  (0x00000020)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_gcall_read(data)                                 (0x00000020&((data)<<5))
#define ISO_IC0_TX_ABRT_SOURCE_abrt_gcall_read_src(data)                             ((0x00000020&(data))>>5)
#define ISO_IC0_TX_ABRT_SOURCE_get_abrt_gcall_read(data)                             ((0x00000020&(data))>>5)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_gcall_noack_shift                                (4)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_gcall_noack_mask                                 (0x00000010)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_gcall_noack(data)                                (0x00000010&((data)<<4))
#define ISO_IC0_TX_ABRT_SOURCE_abrt_gcall_noack_src(data)                            ((0x00000010&(data))>>4)
#define ISO_IC0_TX_ABRT_SOURCE_get_abrt_gcall_noack(data)                            ((0x00000010&(data))>>4)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_txdata_noack_shift                               (3)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_txdata_noack_mask                                (0x00000008)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_txdata_noack(data)                               (0x00000008&((data)<<3))
#define ISO_IC0_TX_ABRT_SOURCE_abrt_txdata_noack_src(data)                           ((0x00000008&(data))>>3)
#define ISO_IC0_TX_ABRT_SOURCE_get_abrt_txdata_noack(data)                           ((0x00000008&(data))>>3)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_10addr2_noack_shift                              (2)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_10addr2_noack_mask                               (0x00000004)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_10addr2_noack(data)                              (0x00000004&((data)<<2))
#define ISO_IC0_TX_ABRT_SOURCE_abrt_10addr2_noack_src(data)                          ((0x00000004&(data))>>2)
#define ISO_IC0_TX_ABRT_SOURCE_get_abrt_10addr2_noack(data)                          ((0x00000004&(data))>>2)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_10addr1_noack_shift                              (1)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_10addr1_noack_mask                               (0x00000002)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_10addr1_noack(data)                              (0x00000002&((data)<<1))
#define ISO_IC0_TX_ABRT_SOURCE_abrt_10addr1_noack_src(data)                          ((0x00000002&(data))>>1)
#define ISO_IC0_TX_ABRT_SOURCE_get_abrt_10addr1_noack(data)                          ((0x00000002&(data))>>1)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_7b_addr_noack_shift                              (0)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_7b_addr_noack_mask                               (0x00000001)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_7b_addr_noack(data)                              (0x00000001&((data)<<0))
#define ISO_IC0_TX_ABRT_SOURCE_abrt_7b_addr_noack_src(data)                          ((0x00000001&(data))>>0)
#define ISO_IC0_TX_ABRT_SOURCE_get_abrt_7b_addr_noack(data)                          ((0x00000001&(data))>>0)


#define ISO_IC0_SLV_DATA_NACK_ONLY                                                   0x98007D84
#define ISO_IC0_SLV_DATA_NACK_ONLY_reg_addr                                          "0x98007D84"
#define ISO_IC0_SLV_DATA_NACK_ONLY_reg                                               0x98007D84
#define set_ISO_IC0_SLV_DATA_NACK_ONLY_reg(data)   (*((volatile unsigned int*) ISO_IC0_SLV_DATA_NACK_ONLY_reg)=data)
#define get_ISO_IC0_SLV_DATA_NACK_ONLY_reg   (*((volatile unsigned int*) ISO_IC0_SLV_DATA_NACK_ONLY_reg))
#define ISO_IC0_SLV_DATA_NACK_ONLY_inst_adr                                          "0x0061"
#define ISO_IC0_SLV_DATA_NACK_ONLY_inst                                              0x0061
#define ISO_IC0_SLV_DATA_NACK_ONLY_nack_shift                                        (0)
#define ISO_IC0_SLV_DATA_NACK_ONLY_nack_mask                                         (0x00000001)
#define ISO_IC0_SLV_DATA_NACK_ONLY_nack(data)                                        (0x00000001&((data)<<0))
#define ISO_IC0_SLV_DATA_NACK_ONLY_nack_src(data)                                    ((0x00000001&(data))>>0)
#define ISO_IC0_SLV_DATA_NACK_ONLY_get_nack(data)                                    ((0x00000001&(data))>>0)


#define ISO_IC0_DMA_CR                                                               0x98007D88
#define ISO_IC0_DMA_CR_reg_addr                                                      "0x98007D88"
#define ISO_IC0_DMA_CR_reg                                                           0x98007D88
#define set_ISO_IC0_DMA_CR_reg(data)   (*((volatile unsigned int*) ISO_IC0_DMA_CR_reg)=data)
#define get_ISO_IC0_DMA_CR_reg   (*((volatile unsigned int*) ISO_IC0_DMA_CR_reg))
#define ISO_IC0_DMA_CR_inst_adr                                                      "0x0062"
#define ISO_IC0_DMA_CR_inst                                                          0x0062
#define ISO_IC0_DMA_CR_tdmae_shift                                                   (1)
#define ISO_IC0_DMA_CR_tdmae_mask                                                    (0x00000002)
#define ISO_IC0_DMA_CR_tdmae(data)                                                   (0x00000002&((data)<<1))
#define ISO_IC0_DMA_CR_tdmae_src(data)                                               ((0x00000002&(data))>>1)
#define ISO_IC0_DMA_CR_get_tdmae(data)                                               ((0x00000002&(data))>>1)
#define ISO_IC0_DMA_CR_rdmae_shift                                                   (0)
#define ISO_IC0_DMA_CR_rdmae_mask                                                    (0x00000001)
#define ISO_IC0_DMA_CR_rdmae(data)                                                   (0x00000001&((data)<<0))
#define ISO_IC0_DMA_CR_rdmae_src(data)                                               ((0x00000001&(data))>>0)
#define ISO_IC0_DMA_CR_get_rdmae(data)                                               ((0x00000001&(data))>>0)


#define ISO_IC0_DMA_TDLR                                                             0x98007D8C
#define ISO_IC0_DMA_TDLR_reg_addr                                                    "0x98007D8C"
#define ISO_IC0_DMA_TDLR_reg                                                         0x98007D8C
#define set_ISO_IC0_DMA_TDLR_reg(data)   (*((volatile unsigned int*) ISO_IC0_DMA_TDLR_reg)=data)
#define get_ISO_IC0_DMA_TDLR_reg   (*((volatile unsigned int*) ISO_IC0_DMA_TDLR_reg))
#define ISO_IC0_DMA_TDLR_inst_adr                                                    "0x0063"
#define ISO_IC0_DMA_TDLR_inst                                                        0x0063
#define ISO_IC0_DMA_TDLR_dmatdl_shift                                                (0)
#define ISO_IC0_DMA_TDLR_dmatdl_mask                                                 (0x00000007)
#define ISO_IC0_DMA_TDLR_dmatdl(data)                                                (0x00000007&((data)<<0))
#define ISO_IC0_DMA_TDLR_dmatdl_src(data)                                            ((0x00000007&(data))>>0)
#define ISO_IC0_DMA_TDLR_get_dmatdl(data)                                            ((0x00000007&(data))>>0)


#define ISO_IC0_DMA_RDLR                                                             0x98007D90
#define ISO_IC0_DMA_RDLR_reg_addr                                                    "0x98007D90"
#define ISO_IC0_DMA_RDLR_reg                                                         0x98007D90
#define set_ISO_IC0_DMA_RDLR_reg(data)   (*((volatile unsigned int*) ISO_IC0_DMA_RDLR_reg)=data)
#define get_ISO_IC0_DMA_RDLR_reg   (*((volatile unsigned int*) ISO_IC0_DMA_RDLR_reg))
#define ISO_IC0_DMA_RDLR_inst_adr                                                    "0x0064"
#define ISO_IC0_DMA_RDLR_inst                                                        0x0064
#define ISO_IC0_DMA_RDLR_dmardl_shift                                                (0)
#define ISO_IC0_DMA_RDLR_dmardl_mask                                                 (0x0000000F)
#define ISO_IC0_DMA_RDLR_dmardl(data)                                                (0x0000000F&((data)<<0))
#define ISO_IC0_DMA_RDLR_dmardl_src(data)                                            ((0x0000000F&(data))>>0)
#define ISO_IC0_DMA_RDLR_get_dmardl(data)                                            ((0x0000000F&(data))>>0)


#define ISO_IC0_SDA_SETUP                                                            0x98007D94
#define ISO_IC0_SDA_SETUP_reg_addr                                                   "0x98007D94"
#define ISO_IC0_SDA_SETUP_reg                                                        0x98007D94
#define set_ISO_IC0_SDA_SETUP_reg(data)   (*((volatile unsigned int*) ISO_IC0_SDA_SETUP_reg)=data)
#define get_ISO_IC0_SDA_SETUP_reg   (*((volatile unsigned int*) ISO_IC0_SDA_SETUP_reg))
#define ISO_IC0_SDA_SETUP_inst_adr                                                   "0x0065"
#define ISO_IC0_SDA_SETUP_inst                                                       0x0065
#define ISO_IC0_SDA_SETUP_sda_setup_shift                                            (0)
#define ISO_IC0_SDA_SETUP_sda_setup_mask                                             (0x000000FF)
#define ISO_IC0_SDA_SETUP_sda_setup(data)                                            (0x000000FF&((data)<<0))
#define ISO_IC0_SDA_SETUP_sda_setup_src(data)                                        ((0x000000FF&(data))>>0)
#define ISO_IC0_SDA_SETUP_get_sda_setup(data)                                        ((0x000000FF&(data))>>0)


#define ISO_IC0_ACK_GENERAL_CALL                                                     0x98007D98
#define ISO_IC0_ACK_GENERAL_CALL_reg_addr                                            "0x98007D98"
#define ISO_IC0_ACK_GENERAL_CALL_reg                                                 0x98007D98
#define set_ISO_IC0_ACK_GENERAL_CALL_reg(data)   (*((volatile unsigned int*) ISO_IC0_ACK_GENERAL_CALL_reg)=data)
#define get_ISO_IC0_ACK_GENERAL_CALL_reg   (*((volatile unsigned int*) ISO_IC0_ACK_GENERAL_CALL_reg))
#define ISO_IC0_ACK_GENERAL_CALL_inst_adr                                            "0x0066"
#define ISO_IC0_ACK_GENERAL_CALL_inst                                                0x0066
#define ISO_IC0_ACK_GENERAL_CALL_ack_gen_call_shift                                  (0)
#define ISO_IC0_ACK_GENERAL_CALL_ack_gen_call_mask                                   (0x00000001)
#define ISO_IC0_ACK_GENERAL_CALL_ack_gen_call(data)                                  (0x00000001&((data)<<0))
#define ISO_IC0_ACK_GENERAL_CALL_ack_gen_call_src(data)                              ((0x00000001&(data))>>0)
#define ISO_IC0_ACK_GENERAL_CALL_get_ack_gen_call(data)                              ((0x00000001&(data))>>0)


#define ISO_IC0_ENABLE_STATUS                                                        0x98007D9C
#define ISO_IC0_ENABLE_STATUS_reg_addr                                               "0x98007D9C"
#define ISO_IC0_ENABLE_STATUS_reg                                                    0x98007D9C
#define set_ISO_IC0_ENABLE_STATUS_reg(data)   (*((volatile unsigned int*) ISO_IC0_ENABLE_STATUS_reg)=data)
#define get_ISO_IC0_ENABLE_STATUS_reg   (*((volatile unsigned int*) ISO_IC0_ENABLE_STATUS_reg))
#define ISO_IC0_ENABLE_STATUS_inst_adr                                               "0x0067"
#define ISO_IC0_ENABLE_STATUS_inst                                                   0x0067
#define ISO_IC0_ENABLE_STATUS_slv_rx_data_lost_shift                                 (2)
#define ISO_IC0_ENABLE_STATUS_slv_rx_data_lost_mask                                  (0x00000004)
#define ISO_IC0_ENABLE_STATUS_slv_rx_data_lost(data)                                 (0x00000004&((data)<<2))
#define ISO_IC0_ENABLE_STATUS_slv_rx_data_lost_src(data)                             ((0x00000004&(data))>>2)
#define ISO_IC0_ENABLE_STATUS_get_slv_rx_data_lost(data)                             ((0x00000004&(data))>>2)
#define ISO_IC0_ENABLE_STATUS_slv_disabled_whi_shift                                 (1)
#define ISO_IC0_ENABLE_STATUS_slv_disabled_whi_mask                                  (0x00000002)
#define ISO_IC0_ENABLE_STATUS_slv_disabled_whi(data)                                 (0x00000002&((data)<<1))
#define ISO_IC0_ENABLE_STATUS_slv_disabled_whi_src(data)                             ((0x00000002&(data))>>1)
#define ISO_IC0_ENABLE_STATUS_get_slv_disabled_whi(data)                             ((0x00000002&(data))>>1)
#define ISO_IC0_ENABLE_STATUS_ic_en_shift                                            (0)
#define ISO_IC0_ENABLE_STATUS_ic_en_mask                                             (0x00000001)
#define ISO_IC0_ENABLE_STATUS_ic_en(data)                                            (0x00000001&((data)<<0))
#define ISO_IC0_ENABLE_STATUS_ic_en_src(data)                                        ((0x00000001&(data))>>0)
#define ISO_IC0_ENABLE_STATUS_get_ic_en(data)                                        ((0x00000001&(data))>>0)


#define ISO_IC0_COMP_PARAM_1                                                         0x98007DF4
#define ISO_IC0_COMP_PARAM_1_reg_addr                                                "0x98007DF4"
#define ISO_IC0_COMP_PARAM_1_reg                                                     0x98007DF4
#define set_ISO_IC0_COMP_PARAM_1_reg(data)   (*((volatile unsigned int*) ISO_IC0_COMP_PARAM_1_reg)=data)
#define get_ISO_IC0_COMP_PARAM_1_reg   (*((volatile unsigned int*) ISO_IC0_COMP_PARAM_1_reg))
#define ISO_IC0_COMP_PARAM_1_inst_adr                                                "0x007D"
#define ISO_IC0_COMP_PARAM_1_inst                                                    0x007D
#define ISO_IC0_COMP_PARAM_1_tx_buffer_depth_shift                                   (16)
#define ISO_IC0_COMP_PARAM_1_tx_buffer_depth_mask                                    (0x00FF0000)
#define ISO_IC0_COMP_PARAM_1_tx_buffer_depth(data)                                   (0x00FF0000&((data)<<16))
#define ISO_IC0_COMP_PARAM_1_tx_buffer_depth_src(data)                               ((0x00FF0000&(data))>>16)
#define ISO_IC0_COMP_PARAM_1_get_tx_buffer_depth(data)                               ((0x00FF0000&(data))>>16)
#define ISO_IC0_COMP_PARAM_1_rx_buffer_depth_shift                                   (8)
#define ISO_IC0_COMP_PARAM_1_rx_buffer_depth_mask                                    (0x0000FF00)
#define ISO_IC0_COMP_PARAM_1_rx_buffer_depth(data)                                   (0x0000FF00&((data)<<8))
#define ISO_IC0_COMP_PARAM_1_rx_buffer_depth_src(data)                               ((0x0000FF00&(data))>>8)
#define ISO_IC0_COMP_PARAM_1_get_rx_buffer_depth(data)                               ((0x0000FF00&(data))>>8)
#define ISO_IC0_COMP_PARAM_1_add_encoded_params_shift                                (7)
#define ISO_IC0_COMP_PARAM_1_add_encoded_params_mask                                 (0x00000080)
#define ISO_IC0_COMP_PARAM_1_add_encoded_params(data)                                (0x00000080&((data)<<7))
#define ISO_IC0_COMP_PARAM_1_add_encoded_params_src(data)                            ((0x00000080&(data))>>7)
#define ISO_IC0_COMP_PARAM_1_get_add_encoded_params(data)                            ((0x00000080&(data))>>7)
#define ISO_IC0_COMP_PARAM_1_has_dma_shift                                           (6)
#define ISO_IC0_COMP_PARAM_1_has_dma_mask                                            (0x00000040)
#define ISO_IC0_COMP_PARAM_1_has_dma(data)                                           (0x00000040&((data)<<6))
#define ISO_IC0_COMP_PARAM_1_has_dma_src(data)                                       ((0x00000040&(data))>>6)
#define ISO_IC0_COMP_PARAM_1_get_has_dma(data)                                       ((0x00000040&(data))>>6)
#define ISO_IC0_COMP_PARAM_1_intr_io_shift                                           (5)
#define ISO_IC0_COMP_PARAM_1_intr_io_mask                                            (0x00000020)
#define ISO_IC0_COMP_PARAM_1_intr_io(data)                                           (0x00000020&((data)<<5))
#define ISO_IC0_COMP_PARAM_1_intr_io_src(data)                                       ((0x00000020&(data))>>5)
#define ISO_IC0_COMP_PARAM_1_get_intr_io(data)                                       ((0x00000020&(data))>>5)
#define ISO_IC0_COMP_PARAM_1_hc_count_values_shift                                   (4)
#define ISO_IC0_COMP_PARAM_1_hc_count_values_mask                                    (0x00000010)
#define ISO_IC0_COMP_PARAM_1_hc_count_values(data)                                   (0x00000010&((data)<<4))
#define ISO_IC0_COMP_PARAM_1_hc_count_values_src(data)                               ((0x00000010&(data))>>4)
#define ISO_IC0_COMP_PARAM_1_get_hc_count_values(data)                               ((0x00000010&(data))>>4)
#define ISO_IC0_COMP_PARAM_1_max_speed_mode_shift                                    (2)
#define ISO_IC0_COMP_PARAM_1_max_speed_mode_mask                                     (0x0000000C)
#define ISO_IC0_COMP_PARAM_1_max_speed_mode(data)                                    (0x0000000C&((data)<<2))
#define ISO_IC0_COMP_PARAM_1_max_speed_mode_src(data)                                ((0x0000000C&(data))>>2)
#define ISO_IC0_COMP_PARAM_1_get_max_speed_mode(data)                                ((0x0000000C&(data))>>2)
#define ISO_IC0_COMP_PARAM_1_apb_data_width_shift                                    (0)
#define ISO_IC0_COMP_PARAM_1_apb_data_width_mask                                     (0x00000003)
#define ISO_IC0_COMP_PARAM_1_apb_data_width(data)                                    (0x00000003&((data)<<0))
#define ISO_IC0_COMP_PARAM_1_apb_data_width_src(data)                                ((0x00000003&(data))>>0)
#define ISO_IC0_COMP_PARAM_1_get_apb_data_width(data)                                ((0x00000003&(data))>>0)


#define ISO_IC0_COMP_VERSION                                                         0x98007DF8
#define ISO_IC0_COMP_VERSION_reg_addr                                                "0x98007DF8"
#define ISO_IC0_COMP_VERSION_reg                                                     0x98007DF8
#define set_ISO_IC0_COMP_VERSION_reg(data)   (*((volatile unsigned int*) ISO_IC0_COMP_VERSION_reg)=data)
#define get_ISO_IC0_COMP_VERSION_reg   (*((volatile unsigned int*) ISO_IC0_COMP_VERSION_reg))
#define ISO_IC0_COMP_VERSION_inst_adr                                                "0x007E"
#define ISO_IC0_COMP_VERSION_inst                                                    0x007E
#define ISO_IC0_COMP_VERSION_ic_comp_version_shift                                   (0)
#define ISO_IC0_COMP_VERSION_ic_comp_version_mask                                    (0xFFFFFFFF)
#define ISO_IC0_COMP_VERSION_ic_comp_version(data)                                   (0xFFFFFFFF&((data)<<0))
#define ISO_IC0_COMP_VERSION_ic_comp_version_src(data)                               ((0xFFFFFFFF&(data))>>0)
#define ISO_IC0_COMP_VERSION_get_ic_comp_version(data)                               ((0xFFFFFFFF&(data))>>0)


#define ISO_IC0_COMP_TYPE                                                            0x98007DFC
#define ISO_IC0_COMP_TYPE_reg_addr                                                   "0x98007DFC"
#define ISO_IC0_COMP_TYPE_reg                                                        0x98007DFC
#define set_ISO_IC0_COMP_TYPE_reg(data)   (*((volatile unsigned int*) ISO_IC0_COMP_TYPE_reg)=data)
#define get_ISO_IC0_COMP_TYPE_reg   (*((volatile unsigned int*) ISO_IC0_COMP_TYPE_reg))
#define ISO_IC0_COMP_TYPE_inst_adr                                                   "0x007F"
#define ISO_IC0_COMP_TYPE_inst                                                       0x007F
#define ISO_IC0_COMP_TYPE_ic_comp_type_shift                                         (0)
#define ISO_IC0_COMP_TYPE_ic_comp_type_mask                                          (0xFFFFFFFF)
#define ISO_IC0_COMP_TYPE_ic_comp_type(data)                                         (0xFFFFFFFF&((data)<<0))
#define ISO_IC0_COMP_TYPE_ic_comp_type_src(data)                                     ((0xFFFFFFFF&(data))>>0)
#define ISO_IC0_COMP_TYPE_get_ic_comp_type(data)                                     ((0xFFFFFFFF&(data))>>0)


#define ISO_IC1_CON                                                                  0x98007C00
#define ISO_IC1_CON_reg_addr                                                         "0x98007C00"
#define ISO_IC1_CON_reg                                                              0x98007C00
#define set_ISO_IC1_CON_reg(data)   (*((volatile unsigned int*) ISO_IC1_CON_reg)=data)
#define get_ISO_IC1_CON_reg   (*((volatile unsigned int*) ISO_IC1_CON_reg))
#define ISO_IC1_CON_inst_adr                                                         "0x0000"
#define ISO_IC1_CON_inst                                                             0x0000
#define ISO_IC1_CON_ic_slave_disable_shift                                           (6)
#define ISO_IC1_CON_ic_slave_disable_mask                                            (0x00000040)
#define ISO_IC1_CON_ic_slave_disable(data)                                           (0x00000040&((data)<<6))
#define ISO_IC1_CON_ic_slave_disable_src(data)                                       ((0x00000040&(data))>>6)
#define ISO_IC1_CON_get_ic_slave_disable(data)                                       ((0x00000040&(data))>>6)
#define ISO_IC1_CON_ic_restart_en_shift                                              (5)
#define ISO_IC1_CON_ic_restart_en_mask                                               (0x00000020)
#define ISO_IC1_CON_ic_restart_en(data)                                              (0x00000020&((data)<<5))
#define ISO_IC1_CON_ic_restart_en_src(data)                                          ((0x00000020&(data))>>5)
#define ISO_IC1_CON_get_ic_restart_en(data)                                          ((0x00000020&(data))>>5)
#define ISO_IC1_CON_ic_10bitaddr_master_shift                                        (4)
#define ISO_IC1_CON_ic_10bitaddr_master_mask                                         (0x00000010)
#define ISO_IC1_CON_ic_10bitaddr_master(data)                                        (0x00000010&((data)<<4))
#define ISO_IC1_CON_ic_10bitaddr_master_src(data)                                    ((0x00000010&(data))>>4)
#define ISO_IC1_CON_get_ic_10bitaddr_master(data)                                    ((0x00000010&(data))>>4)
#define ISO_IC1_CON_ic_10bitaddr_slave_shift                                         (3)
#define ISO_IC1_CON_ic_10bitaddr_slave_mask                                          (0x00000008)
#define ISO_IC1_CON_ic_10bitaddr_slave(data)                                         (0x00000008&((data)<<3))
#define ISO_IC1_CON_ic_10bitaddr_slave_src(data)                                     ((0x00000008&(data))>>3)
#define ISO_IC1_CON_get_ic_10bitaddr_slave(data)                                     ((0x00000008&(data))>>3)
#define ISO_IC1_CON_speed_shift                                                      (1)
#define ISO_IC1_CON_speed_mask                                                       (0x00000006)
#define ISO_IC1_CON_speed(data)                                                      (0x00000006&((data)<<1))
#define ISO_IC1_CON_speed_src(data)                                                  ((0x00000006&(data))>>1)
#define ISO_IC1_CON_get_speed(data)                                                  ((0x00000006&(data))>>1)
#define ISO_IC1_CON_master_mode_shift                                                (0)
#define ISO_IC1_CON_master_mode_mask                                                 (0x00000001)
#define ISO_IC1_CON_master_mode(data)                                                (0x00000001&((data)<<0))
#define ISO_IC1_CON_master_mode_src(data)                                            ((0x00000001&(data))>>0)
#define ISO_IC1_CON_get_master_mode(data)                                            ((0x00000001&(data))>>0)


#define ISO_IC1_TAR                                                                  0x98007C04
#define ISO_IC1_TAR_reg_addr                                                         "0x98007C04"
#define ISO_IC1_TAR_reg                                                              0x98007C04
#define set_ISO_IC1_TAR_reg(data)   (*((volatile unsigned int*) ISO_IC1_TAR_reg)=data)
#define get_ISO_IC1_TAR_reg   (*((volatile unsigned int*) ISO_IC1_TAR_reg))
#define ISO_IC1_TAR_inst_adr                                                         "0x0001"
#define ISO_IC1_TAR_inst                                                             0x0001
#define ISO_IC1_TAR_ic_10bitaddr_master_shift                                        (12)
#define ISO_IC1_TAR_ic_10bitaddr_master_mask                                         (0x00001000)
#define ISO_IC1_TAR_ic_10bitaddr_master(data)                                        (0x00001000&((data)<<12))
#define ISO_IC1_TAR_ic_10bitaddr_master_src(data)                                    ((0x00001000&(data))>>12)
#define ISO_IC1_TAR_get_ic_10bitaddr_master(data)                                    ((0x00001000&(data))>>12)
#define ISO_IC1_TAR_special_shift                                                    (11)
#define ISO_IC1_TAR_special_mask                                                     (0x00000800)
#define ISO_IC1_TAR_special(data)                                                    (0x00000800&((data)<<11))
#define ISO_IC1_TAR_special_src(data)                                                ((0x00000800&(data))>>11)
#define ISO_IC1_TAR_get_special(data)                                                ((0x00000800&(data))>>11)
#define ISO_IC1_TAR_gc_or_start_shift                                                (10)
#define ISO_IC1_TAR_gc_or_start_mask                                                 (0x00000400)
#define ISO_IC1_TAR_gc_or_start(data)                                                (0x00000400&((data)<<10))
#define ISO_IC1_TAR_gc_or_start_src(data)                                            ((0x00000400&(data))>>10)
#define ISO_IC1_TAR_get_gc_or_start(data)                                            ((0x00000400&(data))>>10)
#define ISO_IC1_TAR_ic_tar_shift                                                     (0)
#define ISO_IC1_TAR_ic_tar_mask                                                      (0x000003FF)
#define ISO_IC1_TAR_ic_tar(data)                                                     (0x000003FF&((data)<<0))
#define ISO_IC1_TAR_ic_tar_src(data)                                                 ((0x000003FF&(data))>>0)
#define ISO_IC1_TAR_get_ic_tar(data)                                                 ((0x000003FF&(data))>>0)


#define ISO_IC1_SAR                                                                  0x98007C08
#define ISO_IC1_SAR_reg_addr                                                         "0x98007C08"
#define ISO_IC1_SAR_reg                                                              0x98007C08
#define set_ISO_IC1_SAR_reg(data)   (*((volatile unsigned int*) ISO_IC1_SAR_reg)=data)
#define get_ISO_IC1_SAR_reg   (*((volatile unsigned int*) ISO_IC1_SAR_reg))
#define ISO_IC1_SAR_inst_adr                                                         "0x0002"
#define ISO_IC1_SAR_inst                                                             0x0002
#define ISO_IC1_SAR_ic_sar_shift                                                     (0)
#define ISO_IC1_SAR_ic_sar_mask                                                      (0x000003FF)
#define ISO_IC1_SAR_ic_sar(data)                                                     (0x000003FF&((data)<<0))
#define ISO_IC1_SAR_ic_sar_src(data)                                                 ((0x000003FF&(data))>>0)
#define ISO_IC1_SAR_get_ic_sar(data)                                                 ((0x000003FF&(data))>>0)


#define ISO_IC1_HS_MADDR                                                             0x98007C0C
#define ISO_IC1_HS_MADDR_reg_addr                                                    "0x98007C0C"
#define ISO_IC1_HS_MADDR_reg                                                         0x98007C0C
#define set_ISO_IC1_HS_MADDR_reg(data)   (*((volatile unsigned int*) ISO_IC1_HS_MADDR_reg)=data)
#define get_ISO_IC1_HS_MADDR_reg   (*((volatile unsigned int*) ISO_IC1_HS_MADDR_reg))
#define ISO_IC1_HS_MADDR_inst_adr                                                    "0x0003"
#define ISO_IC1_HS_MADDR_inst                                                        0x0003
#define ISO_IC1_HS_MADDR_ic_hs_mar_shift                                             (0)
#define ISO_IC1_HS_MADDR_ic_hs_mar_mask                                              (0x00000007)
#define ISO_IC1_HS_MADDR_ic_hs_mar(data)                                             (0x00000007&((data)<<0))
#define ISO_IC1_HS_MADDR_ic_hs_mar_src(data)                                         ((0x00000007&(data))>>0)
#define ISO_IC1_HS_MADDR_get_ic_hs_mar(data)                                         ((0x00000007&(data))>>0)


#define ISO_IC1_DATA_CMD                                                             0x98007C10
#define ISO_IC1_DATA_CMD_reg_addr                                                    "0x98007C10"
#define ISO_IC1_DATA_CMD_reg                                                         0x98007C10
#define set_ISO_IC1_DATA_CMD_reg(data)   (*((volatile unsigned int*) ISO_IC1_DATA_CMD_reg)=data)
#define get_ISO_IC1_DATA_CMD_reg   (*((volatile unsigned int*) ISO_IC1_DATA_CMD_reg))
#define ISO_IC1_DATA_CMD_inst_adr                                                    "0x0004"
#define ISO_IC1_DATA_CMD_inst                                                        0x0004
#define ISO_IC1_DATA_CMD_restart_shift                                               (10)
#define ISO_IC1_DATA_CMD_restart_mask                                                (0x00000400)
#define ISO_IC1_DATA_CMD_restart(data)                                               (0x00000400&((data)<<10))
#define ISO_IC1_DATA_CMD_restart_src(data)                                           ((0x00000400&(data))>>10)
#define ISO_IC1_DATA_CMD_get_restart(data)                                           ((0x00000400&(data))>>10)
#define ISO_IC1_DATA_CMD_stop_shift                                                  (9)
#define ISO_IC1_DATA_CMD_stop_mask                                                   (0x00000200)
#define ISO_IC1_DATA_CMD_stop(data)                                                  (0x00000200&((data)<<9))
#define ISO_IC1_DATA_CMD_stop_src(data)                                              ((0x00000200&(data))>>9)
#define ISO_IC1_DATA_CMD_get_stop(data)                                              ((0x00000200&(data))>>9)
#define ISO_IC1_DATA_CMD_cmd_shift                                                   (8)
#define ISO_IC1_DATA_CMD_cmd_mask                                                    (0x00000100)
#define ISO_IC1_DATA_CMD_cmd(data)                                                   (0x00000100&((data)<<8))
#define ISO_IC1_DATA_CMD_cmd_src(data)                                               ((0x00000100&(data))>>8)
#define ISO_IC1_DATA_CMD_get_cmd(data)                                               ((0x00000100&(data))>>8)
#define ISO_IC1_DATA_CMD_dat_shift                                                   (0)
#define ISO_IC1_DATA_CMD_dat_mask                                                    (0x000000FF)
#define ISO_IC1_DATA_CMD_dat(data)                                                   (0x000000FF&((data)<<0))
#define ISO_IC1_DATA_CMD_dat_src(data)                                               ((0x000000FF&(data))>>0)
#define ISO_IC1_DATA_CMD_get_dat(data)                                               ((0x000000FF&(data))>>0)


#define ISO_IC1_SS_SCL_HCNT                                                          0x98007C14
#define ISO_IC1_SS_SCL_HCNT_reg_addr                                                 "0x98007C14"
#define ISO_IC1_SS_SCL_HCNT_reg                                                      0x98007C14
#define set_ISO_IC1_SS_SCL_HCNT_reg(data)   (*((volatile unsigned int*) ISO_IC1_SS_SCL_HCNT_reg)=data)
#define get_ISO_IC1_SS_SCL_HCNT_reg   (*((volatile unsigned int*) ISO_IC1_SS_SCL_HCNT_reg))
#define ISO_IC1_SS_SCL_HCNT_inst_adr                                                 "0x0005"
#define ISO_IC1_SS_SCL_HCNT_inst                                                     0x0005
#define ISO_IC1_SS_SCL_HCNT_ic_ss_scl_hcnt_shift                                     (0)
#define ISO_IC1_SS_SCL_HCNT_ic_ss_scl_hcnt_mask                                      (0x0000FFFF)
#define ISO_IC1_SS_SCL_HCNT_ic_ss_scl_hcnt(data)                                     (0x0000FFFF&((data)<<0))
#define ISO_IC1_SS_SCL_HCNT_ic_ss_scl_hcnt_src(data)                                 ((0x0000FFFF&(data))>>0)
#define ISO_IC1_SS_SCL_HCNT_get_ic_ss_scl_hcnt(data)                                 ((0x0000FFFF&(data))>>0)


#define ISO_IC1_SS_SCL_LCNT                                                          0x98007C18
#define ISO_IC1_SS_SCL_LCNT_reg_addr                                                 "0x98007C18"
#define ISO_IC1_SS_SCL_LCNT_reg                                                      0x98007C18
#define set_ISO_IC1_SS_SCL_LCNT_reg(data)   (*((volatile unsigned int*) ISO_IC1_SS_SCL_LCNT_reg)=data)
#define get_ISO_IC1_SS_SCL_LCNT_reg   (*((volatile unsigned int*) ISO_IC1_SS_SCL_LCNT_reg))
#define ISO_IC1_SS_SCL_LCNT_inst_adr                                                 "0x0006"
#define ISO_IC1_SS_SCL_LCNT_inst                                                     0x0006
#define ISO_IC1_SS_SCL_LCNT_ic_ss_scl_lcnt_shift                                     (0)
#define ISO_IC1_SS_SCL_LCNT_ic_ss_scl_lcnt_mask                                      (0x0000FFFF)
#define ISO_IC1_SS_SCL_LCNT_ic_ss_scl_lcnt(data)                                     (0x0000FFFF&((data)<<0))
#define ISO_IC1_SS_SCL_LCNT_ic_ss_scl_lcnt_src(data)                                 ((0x0000FFFF&(data))>>0)
#define ISO_IC1_SS_SCL_LCNT_get_ic_ss_scl_lcnt(data)                                 ((0x0000FFFF&(data))>>0)


#define ISO_IC1_FS_SCL_HCNT                                                          0x98007C1C
#define ISO_IC1_FS_SCL_HCNT_reg_addr                                                 "0x98007C1C"
#define ISO_IC1_FS_SCL_HCNT_reg                                                      0x98007C1C
#define set_ISO_IC1_FS_SCL_HCNT_reg(data)   (*((volatile unsigned int*) ISO_IC1_FS_SCL_HCNT_reg)=data)
#define get_ISO_IC1_FS_SCL_HCNT_reg   (*((volatile unsigned int*) ISO_IC1_FS_SCL_HCNT_reg))
#define ISO_IC1_FS_SCL_HCNT_inst_adr                                                 "0x0007"
#define ISO_IC1_FS_SCL_HCNT_inst                                                     0x0007
#define ISO_IC1_FS_SCL_HCNT_ic_fs_scl_hcnt_shift                                     (0)
#define ISO_IC1_FS_SCL_HCNT_ic_fs_scl_hcnt_mask                                      (0x0000FFFF)
#define ISO_IC1_FS_SCL_HCNT_ic_fs_scl_hcnt(data)                                     (0x0000FFFF&((data)<<0))
#define ISO_IC1_FS_SCL_HCNT_ic_fs_scl_hcnt_src(data)                                 ((0x0000FFFF&(data))>>0)
#define ISO_IC1_FS_SCL_HCNT_get_ic_fs_scl_hcnt(data)                                 ((0x0000FFFF&(data))>>0)


#define ISO_IC1_FS_SCL_LCNT                                                          0x98007C20
#define ISO_IC1_FS_SCL_LCNT_reg_addr                                                 "0x98007C20"
#define ISO_IC1_FS_SCL_LCNT_reg                                                      0x98007C20
#define set_ISO_IC1_FS_SCL_LCNT_reg(data)   (*((volatile unsigned int*) ISO_IC1_FS_SCL_LCNT_reg)=data)
#define get_ISO_IC1_FS_SCL_LCNT_reg   (*((volatile unsigned int*) ISO_IC1_FS_SCL_LCNT_reg))
#define ISO_IC1_FS_SCL_LCNT_inst_adr                                                 "0x0008"
#define ISO_IC1_FS_SCL_LCNT_inst                                                     0x0008
#define ISO_IC1_FS_SCL_LCNT_ic_fs_scl_lcnt_shift                                     (0)
#define ISO_IC1_FS_SCL_LCNT_ic_fs_scl_lcnt_mask                                      (0x0000FFFF)
#define ISO_IC1_FS_SCL_LCNT_ic_fs_scl_lcnt(data)                                     (0x0000FFFF&((data)<<0))
#define ISO_IC1_FS_SCL_LCNT_ic_fs_scl_lcnt_src(data)                                 ((0x0000FFFF&(data))>>0)
#define ISO_IC1_FS_SCL_LCNT_get_ic_fs_scl_lcnt(data)                                 ((0x0000FFFF&(data))>>0)


#define ISO_IC1_INTR_STAT                                                            0x98007C2C
#define ISO_IC1_INTR_STAT_reg_addr                                                   "0x98007C2C"
#define ISO_IC1_INTR_STAT_reg                                                        0x98007C2C
#define set_ISO_IC1_INTR_STAT_reg(data)   (*((volatile unsigned int*) ISO_IC1_INTR_STAT_reg)=data)
#define get_ISO_IC1_INTR_STAT_reg   (*((volatile unsigned int*) ISO_IC1_INTR_STAT_reg))
#define ISO_IC1_INTR_STAT_inst_adr                                                   "0x000B"
#define ISO_IC1_INTR_STAT_inst                                                       0x000B
#define ISO_IC1_INTR_STAT_r_gen_call_shift                                           (11)
#define ISO_IC1_INTR_STAT_r_gen_call_mask                                            (0x00000800)
#define ISO_IC1_INTR_STAT_r_gen_call(data)                                           (0x00000800&((data)<<11))
#define ISO_IC1_INTR_STAT_r_gen_call_src(data)                                       ((0x00000800&(data))>>11)
#define ISO_IC1_INTR_STAT_get_r_gen_call(data)                                       ((0x00000800&(data))>>11)
#define ISO_IC1_INTR_STAT_r_start_det_shift                                          (10)
#define ISO_IC1_INTR_STAT_r_start_det_mask                                           (0x00000400)
#define ISO_IC1_INTR_STAT_r_start_det(data)                                          (0x00000400&((data)<<10))
#define ISO_IC1_INTR_STAT_r_start_det_src(data)                                      ((0x00000400&(data))>>10)
#define ISO_IC1_INTR_STAT_get_r_start_det(data)                                      ((0x00000400&(data))>>10)
#define ISO_IC1_INTR_STAT_r_stop_det_shift                                           (9)
#define ISO_IC1_INTR_STAT_r_stop_det_mask                                            (0x00000200)
#define ISO_IC1_INTR_STAT_r_stop_det(data)                                           (0x00000200&((data)<<9))
#define ISO_IC1_INTR_STAT_r_stop_det_src(data)                                       ((0x00000200&(data))>>9)
#define ISO_IC1_INTR_STAT_get_r_stop_det(data)                                       ((0x00000200&(data))>>9)
#define ISO_IC1_INTR_STAT_r_activity_shift                                           (8)
#define ISO_IC1_INTR_STAT_r_activity_mask                                            (0x00000100)
#define ISO_IC1_INTR_STAT_r_activity(data)                                           (0x00000100&((data)<<8))
#define ISO_IC1_INTR_STAT_r_activity_src(data)                                       ((0x00000100&(data))>>8)
#define ISO_IC1_INTR_STAT_get_r_activity(data)                                       ((0x00000100&(data))>>8)
#define ISO_IC1_INTR_STAT_r_rx_done_shift                                            (7)
#define ISO_IC1_INTR_STAT_r_rx_done_mask                                             (0x00000080)
#define ISO_IC1_INTR_STAT_r_rx_done(data)                                            (0x00000080&((data)<<7))
#define ISO_IC1_INTR_STAT_r_rx_done_src(data)                                        ((0x00000080&(data))>>7)
#define ISO_IC1_INTR_STAT_get_r_rx_done(data)                                        ((0x00000080&(data))>>7)
#define ISO_IC1_INTR_STAT_r_tx_abrt_shift                                            (6)
#define ISO_IC1_INTR_STAT_r_tx_abrt_mask                                             (0x00000040)
#define ISO_IC1_INTR_STAT_r_tx_abrt(data)                                            (0x00000040&((data)<<6))
#define ISO_IC1_INTR_STAT_r_tx_abrt_src(data)                                        ((0x00000040&(data))>>6)
#define ISO_IC1_INTR_STAT_get_r_tx_abrt(data)                                        ((0x00000040&(data))>>6)
#define ISO_IC1_INTR_STAT_r_rd_req_shift                                             (5)
#define ISO_IC1_INTR_STAT_r_rd_req_mask                                              (0x00000020)
#define ISO_IC1_INTR_STAT_r_rd_req(data)                                             (0x00000020&((data)<<5))
#define ISO_IC1_INTR_STAT_r_rd_req_src(data)                                         ((0x00000020&(data))>>5)
#define ISO_IC1_INTR_STAT_get_r_rd_req(data)                                         ((0x00000020&(data))>>5)
#define ISO_IC1_INTR_STAT_r_tx_empty_shift                                           (4)
#define ISO_IC1_INTR_STAT_r_tx_empty_mask                                            (0x00000010)
#define ISO_IC1_INTR_STAT_r_tx_empty(data)                                           (0x00000010&((data)<<4))
#define ISO_IC1_INTR_STAT_r_tx_empty_src(data)                                       ((0x00000010&(data))>>4)
#define ISO_IC1_INTR_STAT_get_r_tx_empty(data)                                       ((0x00000010&(data))>>4)
#define ISO_IC1_INTR_STAT_r_tx_over_shift                                            (3)
#define ISO_IC1_INTR_STAT_r_tx_over_mask                                             (0x00000008)
#define ISO_IC1_INTR_STAT_r_tx_over(data)                                            (0x00000008&((data)<<3))
#define ISO_IC1_INTR_STAT_r_tx_over_src(data)                                        ((0x00000008&(data))>>3)
#define ISO_IC1_INTR_STAT_get_r_tx_over(data)                                        ((0x00000008&(data))>>3)
#define ISO_IC1_INTR_STAT_r_rx_full_shift                                            (2)
#define ISO_IC1_INTR_STAT_r_rx_full_mask                                             (0x00000004)
#define ISO_IC1_INTR_STAT_r_rx_full(data)                                            (0x00000004&((data)<<2))
#define ISO_IC1_INTR_STAT_r_rx_full_src(data)                                        ((0x00000004&(data))>>2)
#define ISO_IC1_INTR_STAT_get_r_rx_full(data)                                        ((0x00000004&(data))>>2)
#define ISO_IC1_INTR_STAT_r_rx_over_shift                                            (1)
#define ISO_IC1_INTR_STAT_r_rx_over_mask                                             (0x00000002)
#define ISO_IC1_INTR_STAT_r_rx_over(data)                                            (0x00000002&((data)<<1))
#define ISO_IC1_INTR_STAT_r_rx_over_src(data)                                        ((0x00000002&(data))>>1)
#define ISO_IC1_INTR_STAT_get_r_rx_over(data)                                        ((0x00000002&(data))>>1)
#define ISO_IC1_INTR_STAT_r_rx_under_shift                                           (0)
#define ISO_IC1_INTR_STAT_r_rx_under_mask                                            (0x00000001)
#define ISO_IC1_INTR_STAT_r_rx_under(data)                                           (0x00000001&((data)<<0))
#define ISO_IC1_INTR_STAT_r_rx_under_src(data)                                       ((0x00000001&(data))>>0)
#define ISO_IC1_INTR_STAT_get_r_rx_under(data)                                       ((0x00000001&(data))>>0)


#define ISO_IC1_INTR_MASK                                                            0x98007C30
#define ISO_IC1_INTR_MASK_reg_addr                                                   "0x98007C30"
#define ISO_IC1_INTR_MASK_reg                                                        0x98007C30
#define set_ISO_IC1_INTR_MASK_reg(data)   (*((volatile unsigned int*) ISO_IC1_INTR_MASK_reg)=data)
#define get_ISO_IC1_INTR_MASK_reg   (*((volatile unsigned int*) ISO_IC1_INTR_MASK_reg))
#define ISO_IC1_INTR_MASK_inst_adr                                                   "0x000C"
#define ISO_IC1_INTR_MASK_inst                                                       0x000C
#define ISO_IC1_INTR_MASK_m_gen_call_shift                                           (11)
#define ISO_IC1_INTR_MASK_m_gen_call_mask                                            (0x00000800)
#define ISO_IC1_INTR_MASK_m_gen_call(data)                                           (0x00000800&((data)<<11))
#define ISO_IC1_INTR_MASK_m_gen_call_src(data)                                       ((0x00000800&(data))>>11)
#define ISO_IC1_INTR_MASK_get_m_gen_call(data)                                       ((0x00000800&(data))>>11)
#define ISO_IC1_INTR_MASK_m_start_det_shift                                          (10)
#define ISO_IC1_INTR_MASK_m_start_det_mask                                           (0x00000400)
#define ISO_IC1_INTR_MASK_m_start_det(data)                                          (0x00000400&((data)<<10))
#define ISO_IC1_INTR_MASK_m_start_det_src(data)                                      ((0x00000400&(data))>>10)
#define ISO_IC1_INTR_MASK_get_m_start_det(data)                                      ((0x00000400&(data))>>10)
#define ISO_IC1_INTR_MASK_m_stop_det_shift                                           (9)
#define ISO_IC1_INTR_MASK_m_stop_det_mask                                            (0x00000200)
#define ISO_IC1_INTR_MASK_m_stop_det(data)                                           (0x00000200&((data)<<9))
#define ISO_IC1_INTR_MASK_m_stop_det_src(data)                                       ((0x00000200&(data))>>9)
#define ISO_IC1_INTR_MASK_get_m_stop_det(data)                                       ((0x00000200&(data))>>9)
#define ISO_IC1_INTR_MASK_m_activity_shift                                           (8)
#define ISO_IC1_INTR_MASK_m_activity_mask                                            (0x00000100)
#define ISO_IC1_INTR_MASK_m_activity(data)                                           (0x00000100&((data)<<8))
#define ISO_IC1_INTR_MASK_m_activity_src(data)                                       ((0x00000100&(data))>>8)
#define ISO_IC1_INTR_MASK_get_m_activity(data)                                       ((0x00000100&(data))>>8)
#define ISO_IC1_INTR_MASK_m_rx_done_shift                                            (7)
#define ISO_IC1_INTR_MASK_m_rx_done_mask                                             (0x00000080)
#define ISO_IC1_INTR_MASK_m_rx_done(data)                                            (0x00000080&((data)<<7))
#define ISO_IC1_INTR_MASK_m_rx_done_src(data)                                        ((0x00000080&(data))>>7)
#define ISO_IC1_INTR_MASK_get_m_rx_done(data)                                        ((0x00000080&(data))>>7)
#define ISO_IC1_INTR_MASK_m_tx_abrt_shift                                            (6)
#define ISO_IC1_INTR_MASK_m_tx_abrt_mask                                             (0x00000040)
#define ISO_IC1_INTR_MASK_m_tx_abrt(data)                                            (0x00000040&((data)<<6))
#define ISO_IC1_INTR_MASK_m_tx_abrt_src(data)                                        ((0x00000040&(data))>>6)
#define ISO_IC1_INTR_MASK_get_m_tx_abrt(data)                                        ((0x00000040&(data))>>6)
#define ISO_IC1_INTR_MASK_m_rd_req_shift                                             (5)
#define ISO_IC1_INTR_MASK_m_rd_req_mask                                              (0x00000020)
#define ISO_IC1_INTR_MASK_m_rd_req(data)                                             (0x00000020&((data)<<5))
#define ISO_IC1_INTR_MASK_m_rd_req_src(data)                                         ((0x00000020&(data))>>5)
#define ISO_IC1_INTR_MASK_get_m_rd_req(data)                                         ((0x00000020&(data))>>5)
#define ISO_IC1_INTR_MASK_m_tx_empty_shift                                           (4)
#define ISO_IC1_INTR_MASK_m_tx_empty_mask                                            (0x00000010)
#define ISO_IC1_INTR_MASK_m_tx_empty(data)                                           (0x00000010&((data)<<4))
#define ISO_IC1_INTR_MASK_m_tx_empty_src(data)                                       ((0x00000010&(data))>>4)
#define ISO_IC1_INTR_MASK_get_m_tx_empty(data)                                       ((0x00000010&(data))>>4)
#define ISO_IC1_INTR_MASK_m_tx_over_shift                                            (3)
#define ISO_IC1_INTR_MASK_m_tx_over_mask                                             (0x00000008)
#define ISO_IC1_INTR_MASK_m_tx_over(data)                                            (0x00000008&((data)<<3))
#define ISO_IC1_INTR_MASK_m_tx_over_src(data)                                        ((0x00000008&(data))>>3)
#define ISO_IC1_INTR_MASK_get_m_tx_over(data)                                        ((0x00000008&(data))>>3)
#define ISO_IC1_INTR_MASK_m_rx_full_shift                                            (2)
#define ISO_IC1_INTR_MASK_m_rx_full_mask                                             (0x00000004)
#define ISO_IC1_INTR_MASK_m_rx_full(data)                                            (0x00000004&((data)<<2))
#define ISO_IC1_INTR_MASK_m_rx_full_src(data)                                        ((0x00000004&(data))>>2)
#define ISO_IC1_INTR_MASK_get_m_rx_full(data)                                        ((0x00000004&(data))>>2)
#define ISO_IC1_INTR_MASK_m_rx_over_shift                                            (1)
#define ISO_IC1_INTR_MASK_m_rx_over_mask                                             (0x00000002)
#define ISO_IC1_INTR_MASK_m_rx_over(data)                                            (0x00000002&((data)<<1))
#define ISO_IC1_INTR_MASK_m_rx_over_src(data)                                        ((0x00000002&(data))>>1)
#define ISO_IC1_INTR_MASK_get_m_rx_over(data)                                        ((0x00000002&(data))>>1)
#define ISO_IC1_INTR_MASK_m_rx_under_shift                                           (0)
#define ISO_IC1_INTR_MASK_m_rx_under_mask                                            (0x00000001)
#define ISO_IC1_INTR_MASK_m_rx_under(data)                                           (0x00000001&((data)<<0))
#define ISO_IC1_INTR_MASK_m_rx_under_src(data)                                       ((0x00000001&(data))>>0)
#define ISO_IC1_INTR_MASK_get_m_rx_under(data)                                       ((0x00000001&(data))>>0)


#define ISO_IC1_RAW_INTR_STAT                                                        0x98007C34
#define ISO_IC1_RAW_INTR_STAT_reg_addr                                               "0x98007C34"
#define ISO_IC1_RAW_INTR_STAT_reg                                                    0x98007C34
#define set_ISO_IC1_RAW_INTR_STAT_reg(data)   (*((volatile unsigned int*) ISO_IC1_RAW_INTR_STAT_reg)=data)
#define get_ISO_IC1_RAW_INTR_STAT_reg   (*((volatile unsigned int*) ISO_IC1_RAW_INTR_STAT_reg))
#define ISO_IC1_RAW_INTR_STAT_inst_adr                                               "0x000D"
#define ISO_IC1_RAW_INTR_STAT_inst                                                   0x000D
#define ISO_IC1_RAW_INTR_STAT_gen_call_shift                                         (11)
#define ISO_IC1_RAW_INTR_STAT_gen_call_mask                                          (0x00000800)
#define ISO_IC1_RAW_INTR_STAT_gen_call(data)                                         (0x00000800&((data)<<11))
#define ISO_IC1_RAW_INTR_STAT_gen_call_src(data)                                     ((0x00000800&(data))>>11)
#define ISO_IC1_RAW_INTR_STAT_get_gen_call(data)                                     ((0x00000800&(data))>>11)
#define ISO_IC1_RAW_INTR_STAT_start_det_shift                                        (10)
#define ISO_IC1_RAW_INTR_STAT_start_det_mask                                         (0x00000400)
#define ISO_IC1_RAW_INTR_STAT_start_det(data)                                        (0x00000400&((data)<<10))
#define ISO_IC1_RAW_INTR_STAT_start_det_src(data)                                    ((0x00000400&(data))>>10)
#define ISO_IC1_RAW_INTR_STAT_get_start_det(data)                                    ((0x00000400&(data))>>10)
#define ISO_IC1_RAW_INTR_STAT_stop_det_shift                                         (9)
#define ISO_IC1_RAW_INTR_STAT_stop_det_mask                                          (0x00000200)
#define ISO_IC1_RAW_INTR_STAT_stop_det(data)                                         (0x00000200&((data)<<9))
#define ISO_IC1_RAW_INTR_STAT_stop_det_src(data)                                     ((0x00000200&(data))>>9)
#define ISO_IC1_RAW_INTR_STAT_get_stop_det(data)                                     ((0x00000200&(data))>>9)
#define ISO_IC1_RAW_INTR_STAT_activity_shift                                         (8)
#define ISO_IC1_RAW_INTR_STAT_activity_mask                                          (0x00000100)
#define ISO_IC1_RAW_INTR_STAT_activity(data)                                         (0x00000100&((data)<<8))
#define ISO_IC1_RAW_INTR_STAT_activity_src(data)                                     ((0x00000100&(data))>>8)
#define ISO_IC1_RAW_INTR_STAT_get_activity(data)                                     ((0x00000100&(data))>>8)
#define ISO_IC1_RAW_INTR_STAT_rx_done_shift                                          (7)
#define ISO_IC1_RAW_INTR_STAT_rx_done_mask                                           (0x00000080)
#define ISO_IC1_RAW_INTR_STAT_rx_done(data)                                          (0x00000080&((data)<<7))
#define ISO_IC1_RAW_INTR_STAT_rx_done_src(data)                                      ((0x00000080&(data))>>7)
#define ISO_IC1_RAW_INTR_STAT_get_rx_done(data)                                      ((0x00000080&(data))>>7)
#define ISO_IC1_RAW_INTR_STAT_tx_abrt_shift                                          (6)
#define ISO_IC1_RAW_INTR_STAT_tx_abrt_mask                                           (0x00000040)
#define ISO_IC1_RAW_INTR_STAT_tx_abrt(data)                                          (0x00000040&((data)<<6))
#define ISO_IC1_RAW_INTR_STAT_tx_abrt_src(data)                                      ((0x00000040&(data))>>6)
#define ISO_IC1_RAW_INTR_STAT_get_tx_abrt(data)                                      ((0x00000040&(data))>>6)
#define ISO_IC1_RAW_INTR_STAT_rd_req_shift                                           (5)
#define ISO_IC1_RAW_INTR_STAT_rd_req_mask                                            (0x00000020)
#define ISO_IC1_RAW_INTR_STAT_rd_req(data)                                           (0x00000020&((data)<<5))
#define ISO_IC1_RAW_INTR_STAT_rd_req_src(data)                                       ((0x00000020&(data))>>5)
#define ISO_IC1_RAW_INTR_STAT_get_rd_req(data)                                       ((0x00000020&(data))>>5)
#define ISO_IC1_RAW_INTR_STAT_tx_empty_shift                                         (4)
#define ISO_IC1_RAW_INTR_STAT_tx_empty_mask                                          (0x00000010)
#define ISO_IC1_RAW_INTR_STAT_tx_empty(data)                                         (0x00000010&((data)<<4))
#define ISO_IC1_RAW_INTR_STAT_tx_empty_src(data)                                     ((0x00000010&(data))>>4)
#define ISO_IC1_RAW_INTR_STAT_get_tx_empty(data)                                     ((0x00000010&(data))>>4)
#define ISO_IC1_RAW_INTR_STAT_tx_over_shift                                          (3)
#define ISO_IC1_RAW_INTR_STAT_tx_over_mask                                           (0x00000008)
#define ISO_IC1_RAW_INTR_STAT_tx_over(data)                                          (0x00000008&((data)<<3))
#define ISO_IC1_RAW_INTR_STAT_tx_over_src(data)                                      ((0x00000008&(data))>>3)
#define ISO_IC1_RAW_INTR_STAT_get_tx_over(data)                                      ((0x00000008&(data))>>3)
#define ISO_IC1_RAW_INTR_STAT_rx_full_shift                                          (2)
#define ISO_IC1_RAW_INTR_STAT_rx_full_mask                                           (0x00000004)
#define ISO_IC1_RAW_INTR_STAT_rx_full(data)                                          (0x00000004&((data)<<2))
#define ISO_IC1_RAW_INTR_STAT_rx_full_src(data)                                      ((0x00000004&(data))>>2)
#define ISO_IC1_RAW_INTR_STAT_get_rx_full(data)                                      ((0x00000004&(data))>>2)
#define ISO_IC1_RAW_INTR_STAT_rx_over_shift                                          (1)
#define ISO_IC1_RAW_INTR_STAT_rx_over_mask                                           (0x00000002)
#define ISO_IC1_RAW_INTR_STAT_rx_over(data)                                          (0x00000002&((data)<<1))
#define ISO_IC1_RAW_INTR_STAT_rx_over_src(data)                                      ((0x00000002&(data))>>1)
#define ISO_IC1_RAW_INTR_STAT_get_rx_over(data)                                      ((0x00000002&(data))>>1)
#define ISO_IC1_RAW_INTR_STAT_rx_under_shift                                         (0)
#define ISO_IC1_RAW_INTR_STAT_rx_under_mask                                          (0x00000001)
#define ISO_IC1_RAW_INTR_STAT_rx_under(data)                                         (0x00000001&((data)<<0))
#define ISO_IC1_RAW_INTR_STAT_rx_under_src(data)                                     ((0x00000001&(data))>>0)
#define ISO_IC1_RAW_INTR_STAT_get_rx_under(data)                                     ((0x00000001&(data))>>0)


#define ISO_IC1_RX_TL                                                                0x98007C38
#define ISO_IC1_RX_TL_reg_addr                                                       "0x98007C38"
#define ISO_IC1_RX_TL_reg                                                            0x98007C38
#define set_ISO_IC1_RX_TL_reg(data)   (*((volatile unsigned int*) ISO_IC1_RX_TL_reg)=data)
#define get_ISO_IC1_RX_TL_reg   (*((volatile unsigned int*) ISO_IC1_RX_TL_reg))
#define ISO_IC1_RX_TL_inst_adr                                                       "0x000E"
#define ISO_IC1_RX_TL_inst                                                           0x000E
#define ISO_IC1_RX_TL_rx_tl_shift                                                    (0)
#define ISO_IC1_RX_TL_rx_tl_mask                                                     (0x000000FF)
#define ISO_IC1_RX_TL_rx_tl(data)                                                    (0x000000FF&((data)<<0))
#define ISO_IC1_RX_TL_rx_tl_src(data)                                                ((0x000000FF&(data))>>0)
#define ISO_IC1_RX_TL_get_rx_tl(data)                                                ((0x000000FF&(data))>>0)


#define ISO_IC1_TX_TL                                                                0x98007C3C
#define ISO_IC1_TX_TL_reg_addr                                                       "0x98007C3C"
#define ISO_IC1_TX_TL_reg                                                            0x98007C3C
#define set_ISO_IC1_TX_TL_reg(data)   (*((volatile unsigned int*) ISO_IC1_TX_TL_reg)=data)
#define get_ISO_IC1_TX_TL_reg   (*((volatile unsigned int*) ISO_IC1_TX_TL_reg))
#define ISO_IC1_TX_TL_inst_adr                                                       "0x000F"
#define ISO_IC1_TX_TL_inst                                                           0x000F
#define ISO_IC1_TX_TL_tx_tl_shift                                                    (0)
#define ISO_IC1_TX_TL_tx_tl_mask                                                     (0x000000FF)
#define ISO_IC1_TX_TL_tx_tl(data)                                                    (0x000000FF&((data)<<0))
#define ISO_IC1_TX_TL_tx_tl_src(data)                                                ((0x000000FF&(data))>>0)
#define ISO_IC1_TX_TL_get_tx_tl(data)                                                ((0x000000FF&(data))>>0)


#define ISO_IC1_CLR_INTR                                                             0x98007C40
#define ISO_IC1_CLR_INTR_reg_addr                                                    "0x98007C40"
#define ISO_IC1_CLR_INTR_reg                                                         0x98007C40
#define set_ISO_IC1_CLR_INTR_reg(data)   (*((volatile unsigned int*) ISO_IC1_CLR_INTR_reg)=data)
#define get_ISO_IC1_CLR_INTR_reg   (*((volatile unsigned int*) ISO_IC1_CLR_INTR_reg))
#define ISO_IC1_CLR_INTR_inst_adr                                                    "0x0010"
#define ISO_IC1_CLR_INTR_inst                                                        0x0010
#define ISO_IC1_CLR_INTR_clr_intr_shift                                              (0)
#define ISO_IC1_CLR_INTR_clr_intr_mask                                               (0x00000001)
#define ISO_IC1_CLR_INTR_clr_intr(data)                                              (0x00000001&((data)<<0))
#define ISO_IC1_CLR_INTR_clr_intr_src(data)                                          ((0x00000001&(data))>>0)
#define ISO_IC1_CLR_INTR_get_clr_intr(data)                                          ((0x00000001&(data))>>0)


#define ISO_IC1_CLR_RX_UNDER                                                         0x98007C44
#define ISO_IC1_CLR_RX_UNDER_reg_addr                                                "0x98007C44"
#define ISO_IC1_CLR_RX_UNDER_reg                                                     0x98007C44
#define set_ISO_IC1_CLR_RX_UNDER_reg(data)   (*((volatile unsigned int*) ISO_IC1_CLR_RX_UNDER_reg)=data)
#define get_ISO_IC1_CLR_RX_UNDER_reg   (*((volatile unsigned int*) ISO_IC1_CLR_RX_UNDER_reg))
#define ISO_IC1_CLR_RX_UNDER_inst_adr                                                "0x0011"
#define ISO_IC1_CLR_RX_UNDER_inst                                                    0x0011
#define ISO_IC1_CLR_RX_UNDER_clr_rx_under_shift                                      (0)
#define ISO_IC1_CLR_RX_UNDER_clr_rx_under_mask                                       (0x00000001)
#define ISO_IC1_CLR_RX_UNDER_clr_rx_under(data)                                      (0x00000001&((data)<<0))
#define ISO_IC1_CLR_RX_UNDER_clr_rx_under_src(data)                                  ((0x00000001&(data))>>0)
#define ISO_IC1_CLR_RX_UNDER_get_clr_rx_under(data)                                  ((0x00000001&(data))>>0)


#define ISO_IC1_CLR_RX_OVER                                                          0x98007C48
#define ISO_IC1_CLR_RX_OVER_reg_addr                                                 "0x98007C48"
#define ISO_IC1_CLR_RX_OVER_reg                                                      0x98007C48
#define set_ISO_IC1_CLR_RX_OVER_reg(data)   (*((volatile unsigned int*) ISO_IC1_CLR_RX_OVER_reg)=data)
#define get_ISO_IC1_CLR_RX_OVER_reg   (*((volatile unsigned int*) ISO_IC1_CLR_RX_OVER_reg))
#define ISO_IC1_CLR_RX_OVER_inst_adr                                                 "0x0012"
#define ISO_IC1_CLR_RX_OVER_inst                                                     0x0012
#define ISO_IC1_CLR_RX_OVER_clr_rx_over_shift                                        (0)
#define ISO_IC1_CLR_RX_OVER_clr_rx_over_mask                                         (0x00000001)
#define ISO_IC1_CLR_RX_OVER_clr_rx_over(data)                                        (0x00000001&((data)<<0))
#define ISO_IC1_CLR_RX_OVER_clr_rx_over_src(data)                                    ((0x00000001&(data))>>0)
#define ISO_IC1_CLR_RX_OVER_get_clr_rx_over(data)                                    ((0x00000001&(data))>>0)


#define ISO_IC1_CLR_TX_OVER                                                          0x98007C4C
#define ISO_IC1_CLR_TX_OVER_reg_addr                                                 "0x98007C4C"
#define ISO_IC1_CLR_TX_OVER_reg                                                      0x98007C4C
#define set_ISO_IC1_CLR_TX_OVER_reg(data)   (*((volatile unsigned int*) ISO_IC1_CLR_TX_OVER_reg)=data)
#define get_ISO_IC1_CLR_TX_OVER_reg   (*((volatile unsigned int*) ISO_IC1_CLR_TX_OVER_reg))
#define ISO_IC1_CLR_TX_OVER_inst_adr                                                 "0x0013"
#define ISO_IC1_CLR_TX_OVER_inst                                                     0x0013
#define ISO_IC1_CLR_TX_OVER_clr_tx_over_shift                                        (0)
#define ISO_IC1_CLR_TX_OVER_clr_tx_over_mask                                         (0x00000001)
#define ISO_IC1_CLR_TX_OVER_clr_tx_over(data)                                        (0x00000001&((data)<<0))
#define ISO_IC1_CLR_TX_OVER_clr_tx_over_src(data)                                    ((0x00000001&(data))>>0)
#define ISO_IC1_CLR_TX_OVER_get_clr_tx_over(data)                                    ((0x00000001&(data))>>0)


#define ISO_IC1_CLR_RD_REQ                                                           0x98007C50
#define ISO_IC1_CLR_RD_REQ_reg_addr                                                  "0x98007C50"
#define ISO_IC1_CLR_RD_REQ_reg                                                       0x98007C50
#define set_ISO_IC1_CLR_RD_REQ_reg(data)   (*((volatile unsigned int*) ISO_IC1_CLR_RD_REQ_reg)=data)
#define get_ISO_IC1_CLR_RD_REQ_reg   (*((volatile unsigned int*) ISO_IC1_CLR_RD_REQ_reg))
#define ISO_IC1_CLR_RD_REQ_inst_adr                                                  "0x0014"
#define ISO_IC1_CLR_RD_REQ_inst                                                      0x0014
#define ISO_IC1_CLR_RD_REQ_clr_rd_req_shift                                          (0)
#define ISO_IC1_CLR_RD_REQ_clr_rd_req_mask                                           (0x00000001)
#define ISO_IC1_CLR_RD_REQ_clr_rd_req(data)                                          (0x00000001&((data)<<0))
#define ISO_IC1_CLR_RD_REQ_clr_rd_req_src(data)                                      ((0x00000001&(data))>>0)
#define ISO_IC1_CLR_RD_REQ_get_clr_rd_req(data)                                      ((0x00000001&(data))>>0)


#define ISO_IC1_CLR_TX_ABRT                                                          0x98007C54
#define ISO_IC1_CLR_TX_ABRT_reg_addr                                                 "0x98007C54"
#define ISO_IC1_CLR_TX_ABRT_reg                                                      0x98007C54
#define set_ISO_IC1_CLR_TX_ABRT_reg(data)   (*((volatile unsigned int*) ISO_IC1_CLR_TX_ABRT_reg)=data)
#define get_ISO_IC1_CLR_TX_ABRT_reg   (*((volatile unsigned int*) ISO_IC1_CLR_TX_ABRT_reg))
#define ISO_IC1_CLR_TX_ABRT_inst_adr                                                 "0x0015"
#define ISO_IC1_CLR_TX_ABRT_inst                                                     0x0015
#define ISO_IC1_CLR_TX_ABRT_clr_tx_abrt_shift                                        (0)
#define ISO_IC1_CLR_TX_ABRT_clr_tx_abrt_mask                                         (0x00000001)
#define ISO_IC1_CLR_TX_ABRT_clr_tx_abrt(data)                                        (0x00000001&((data)<<0))
#define ISO_IC1_CLR_TX_ABRT_clr_tx_abrt_src(data)                                    ((0x00000001&(data))>>0)
#define ISO_IC1_CLR_TX_ABRT_get_clr_tx_abrt(data)                                    ((0x00000001&(data))>>0)


#define ISO_IC1_CLR_RX_DONE                                                          0x98007C58
#define ISO_IC1_CLR_RX_DONE_reg_addr                                                 "0x98007C58"
#define ISO_IC1_CLR_RX_DONE_reg                                                      0x98007C58
#define set_ISO_IC1_CLR_RX_DONE_reg(data)   (*((volatile unsigned int*) ISO_IC1_CLR_RX_DONE_reg)=data)
#define get_ISO_IC1_CLR_RX_DONE_reg   (*((volatile unsigned int*) ISO_IC1_CLR_RX_DONE_reg))
#define ISO_IC1_CLR_RX_DONE_inst_adr                                                 "0x0016"
#define ISO_IC1_CLR_RX_DONE_inst                                                     0x0016
#define ISO_IC1_CLR_RX_DONE_clr_rx_done_shift                                        (0)
#define ISO_IC1_CLR_RX_DONE_clr_rx_done_mask                                         (0x00000001)
#define ISO_IC1_CLR_RX_DONE_clr_rx_done(data)                                        (0x00000001&((data)<<0))
#define ISO_IC1_CLR_RX_DONE_clr_rx_done_src(data)                                    ((0x00000001&(data))>>0)
#define ISO_IC1_CLR_RX_DONE_get_clr_rx_done(data)                                    ((0x00000001&(data))>>0)


#define ISO_IC1_CLR_ACTIVITY                                                         0x98007C5C
#define ISO_IC1_CLR_ACTIVITY_reg_addr                                                "0x98007C5C"
#define ISO_IC1_CLR_ACTIVITY_reg                                                     0x98007C5C
#define set_ISO_IC1_CLR_ACTIVITY_reg(data)   (*((volatile unsigned int*) ISO_IC1_CLR_ACTIVITY_reg)=data)
#define get_ISO_IC1_CLR_ACTIVITY_reg   (*((volatile unsigned int*) ISO_IC1_CLR_ACTIVITY_reg))
#define ISO_IC1_CLR_ACTIVITY_inst_adr                                                "0x0017"
#define ISO_IC1_CLR_ACTIVITY_inst                                                    0x0017
#define ISO_IC1_CLR_ACTIVITY_clr_activity_shift                                      (0)
#define ISO_IC1_CLR_ACTIVITY_clr_activity_mask                                       (0x00000001)
#define ISO_IC1_CLR_ACTIVITY_clr_activity(data)                                      (0x00000001&((data)<<0))
#define ISO_IC1_CLR_ACTIVITY_clr_activity_src(data)                                  ((0x00000001&(data))>>0)
#define ISO_IC1_CLR_ACTIVITY_get_clr_activity(data)                                  ((0x00000001&(data))>>0)


#define ISO_IC1_CLR_STOP_DET                                                         0x98007C60
#define ISO_IC1_CLR_STOP_DET_reg_addr                                                "0x98007C60"
#define ISO_IC1_CLR_STOP_DET_reg                                                     0x98007C60
#define set_ISO_IC1_CLR_STOP_DET_reg(data)   (*((volatile unsigned int*) ISO_IC1_CLR_STOP_DET_reg)=data)
#define get_ISO_IC1_CLR_STOP_DET_reg   (*((volatile unsigned int*) ISO_IC1_CLR_STOP_DET_reg))
#define ISO_IC1_CLR_STOP_DET_inst_adr                                                "0x0018"
#define ISO_IC1_CLR_STOP_DET_inst                                                    0x0018
#define ISO_IC1_CLR_STOP_DET_clr_stop_det_shift                                      (0)
#define ISO_IC1_CLR_STOP_DET_clr_stop_det_mask                                       (0x00000001)
#define ISO_IC1_CLR_STOP_DET_clr_stop_det(data)                                      (0x00000001&((data)<<0))
#define ISO_IC1_CLR_STOP_DET_clr_stop_det_src(data)                                  ((0x00000001&(data))>>0)
#define ISO_IC1_CLR_STOP_DET_get_clr_stop_det(data)                                  ((0x00000001&(data))>>0)


#define ISO_IC1_CLR_START_DET                                                        0x98007C64
#define ISO_IC1_CLR_START_DET_reg_addr                                               "0x98007C64"
#define ISO_IC1_CLR_START_DET_reg                                                    0x98007C64
#define set_ISO_IC1_CLR_START_DET_reg(data)   (*((volatile unsigned int*) ISO_IC1_CLR_START_DET_reg)=data)
#define get_ISO_IC1_CLR_START_DET_reg   (*((volatile unsigned int*) ISO_IC1_CLR_START_DET_reg))
#define ISO_IC1_CLR_START_DET_inst_adr                                               "0x0019"
#define ISO_IC1_CLR_START_DET_inst                                                   0x0019
#define ISO_IC1_CLR_START_DET_clr_start_det_shift                                    (0)
#define ISO_IC1_CLR_START_DET_clr_start_det_mask                                     (0x00000001)
#define ISO_IC1_CLR_START_DET_clr_start_det(data)                                    (0x00000001&((data)<<0))
#define ISO_IC1_CLR_START_DET_clr_start_det_src(data)                                ((0x00000001&(data))>>0)
#define ISO_IC1_CLR_START_DET_get_clr_start_det(data)                                ((0x00000001&(data))>>0)


#define ISO_IC1_CLR_GEN_CALL                                                         0x98007C68
#define ISO_IC1_CLR_GEN_CALL_reg_addr                                                "0x98007C68"
#define ISO_IC1_CLR_GEN_CALL_reg                                                     0x98007C68
#define set_ISO_IC1_CLR_GEN_CALL_reg(data)   (*((volatile unsigned int*) ISO_IC1_CLR_GEN_CALL_reg)=data)
#define get_ISO_IC1_CLR_GEN_CALL_reg   (*((volatile unsigned int*) ISO_IC1_CLR_GEN_CALL_reg))
#define ISO_IC1_CLR_GEN_CALL_inst_adr                                                "0x001A"
#define ISO_IC1_CLR_GEN_CALL_inst                                                    0x001A
#define ISO_IC1_CLR_GEN_CALL_clr_gen_call_shift                                      (0)
#define ISO_IC1_CLR_GEN_CALL_clr_gen_call_mask                                       (0x00000001)
#define ISO_IC1_CLR_GEN_CALL_clr_gen_call(data)                                      (0x00000001&((data)<<0))
#define ISO_IC1_CLR_GEN_CALL_clr_gen_call_src(data)                                  ((0x00000001&(data))>>0)
#define ISO_IC1_CLR_GEN_CALL_get_clr_gen_call(data)                                  ((0x00000001&(data))>>0)


#define ISO_IC1_ENABLE                                                               0x98007C6C
#define ISO_IC1_ENABLE_reg_addr                                                      "0x98007C6C"
#define ISO_IC1_ENABLE_reg                                                           0x98007C6C
#define set_ISO_IC1_ENABLE_reg(data)   (*((volatile unsigned int*) ISO_IC1_ENABLE_reg)=data)
#define get_ISO_IC1_ENABLE_reg   (*((volatile unsigned int*) ISO_IC1_ENABLE_reg))
#define ISO_IC1_ENABLE_inst_adr                                                      "0x001B"
#define ISO_IC1_ENABLE_inst                                                          0x001B
#define ISO_IC1_ENABLE_enable_shift                                                  (0)
#define ISO_IC1_ENABLE_enable_mask                                                   (0x00000001)
#define ISO_IC1_ENABLE_enable(data)                                                  (0x00000001&((data)<<0))
#define ISO_IC1_ENABLE_enable_src(data)                                              ((0x00000001&(data))>>0)
#define ISO_IC1_ENABLE_get_enable(data)                                              ((0x00000001&(data))>>0)


#define ISO_IC1_STATUS                                                               0x98007C70
#define ISO_IC1_STATUS_reg_addr                                                      "0x98007C70"
#define ISO_IC1_STATUS_reg                                                           0x98007C70
#define set_ISO_IC1_STATUS_reg(data)   (*((volatile unsigned int*) ISO_IC1_STATUS_reg)=data)
#define get_ISO_IC1_STATUS_reg   (*((volatile unsigned int*) ISO_IC1_STATUS_reg))
#define ISO_IC1_STATUS_inst_adr                                                      "0x001C"
#define ISO_IC1_STATUS_inst                                                          0x001C
#define ISO_IC1_STATUS_slv_activity_shift                                            (6)
#define ISO_IC1_STATUS_slv_activity_mask                                             (0x00000040)
#define ISO_IC1_STATUS_slv_activity(data)                                            (0x00000040&((data)<<6))
#define ISO_IC1_STATUS_slv_activity_src(data)                                        ((0x00000040&(data))>>6)
#define ISO_IC1_STATUS_get_slv_activity(data)                                        ((0x00000040&(data))>>6)
#define ISO_IC1_STATUS_mst_activity_shift                                            (5)
#define ISO_IC1_STATUS_mst_activity_mask                                             (0x00000020)
#define ISO_IC1_STATUS_mst_activity(data)                                            (0x00000020&((data)<<5))
#define ISO_IC1_STATUS_mst_activity_src(data)                                        ((0x00000020&(data))>>5)
#define ISO_IC1_STATUS_get_mst_activity(data)                                        ((0x00000020&(data))>>5)
#define ISO_IC1_STATUS_rff_shift                                                     (4)
#define ISO_IC1_STATUS_rff_mask                                                      (0x00000010)
#define ISO_IC1_STATUS_rff(data)                                                     (0x00000010&((data)<<4))
#define ISO_IC1_STATUS_rff_src(data)                                                 ((0x00000010&(data))>>4)
#define ISO_IC1_STATUS_get_rff(data)                                                 ((0x00000010&(data))>>4)
#define ISO_IC1_STATUS_rfne_shift                                                    (3)
#define ISO_IC1_STATUS_rfne_mask                                                     (0x00000008)
#define ISO_IC1_STATUS_rfne(data)                                                    (0x00000008&((data)<<3))
#define ISO_IC1_STATUS_rfne_src(data)                                                ((0x00000008&(data))>>3)
#define ISO_IC1_STATUS_get_rfne(data)                                                ((0x00000008&(data))>>3)
#define ISO_IC1_STATUS_tfe_shift                                                     (2)
#define ISO_IC1_STATUS_tfe_mask                                                      (0x00000004)
#define ISO_IC1_STATUS_tfe(data)                                                     (0x00000004&((data)<<2))
#define ISO_IC1_STATUS_tfe_src(data)                                                 ((0x00000004&(data))>>2)
#define ISO_IC1_STATUS_get_tfe(data)                                                 ((0x00000004&(data))>>2)
#define ISO_IC1_STATUS_tfnf_shift                                                    (1)
#define ISO_IC1_STATUS_tfnf_mask                                                     (0x00000002)
#define ISO_IC1_STATUS_tfnf(data)                                                    (0x00000002&((data)<<1))
#define ISO_IC1_STATUS_tfnf_src(data)                                                ((0x00000002&(data))>>1)
#define ISO_IC1_STATUS_get_tfnf(data)                                                ((0x00000002&(data))>>1)
#define ISO_IC1_STATUS_activity_shift                                                (0)
#define ISO_IC1_STATUS_activity_mask                                                 (0x00000001)
#define ISO_IC1_STATUS_activity(data)                                                (0x00000001&((data)<<0))
#define ISO_IC1_STATUS_activity_src(data)                                            ((0x00000001&(data))>>0)
#define ISO_IC1_STATUS_get_activity(data)                                            ((0x00000001&(data))>>0)


#define ISO_IC1_TXFLR                                                                0x98007C74
#define ISO_IC1_TXFLR_reg_addr                                                       "0x98007C74"
#define ISO_IC1_TXFLR_reg                                                            0x98007C74
#define set_ISO_IC1_TXFLR_reg(data)   (*((volatile unsigned int*) ISO_IC1_TXFLR_reg)=data)
#define get_ISO_IC1_TXFLR_reg   (*((volatile unsigned int*) ISO_IC1_TXFLR_reg))
#define ISO_IC1_TXFLR_inst_adr                                                       "0x001D"
#define ISO_IC1_TXFLR_inst                                                           0x001D
#define ISO_IC1_TXFLR_txflr_shift                                                    (0)
#define ISO_IC1_TXFLR_txflr_mask                                                     (0x0000000F)
#define ISO_IC1_TXFLR_txflr(data)                                                    (0x0000000F&((data)<<0))
#define ISO_IC1_TXFLR_txflr_src(data)                                                ((0x0000000F&(data))>>0)
#define ISO_IC1_TXFLR_get_txflr(data)                                                ((0x0000000F&(data))>>0)


#define ISO_IC1_RXFLR                                                                0x98007C78
#define ISO_IC1_RXFLR_reg_addr                                                       "0x98007C78"
#define ISO_IC1_RXFLR_reg                                                            0x98007C78
#define set_ISO_IC1_RXFLR_reg(data)   (*((volatile unsigned int*) ISO_IC1_RXFLR_reg)=data)
#define get_ISO_IC1_RXFLR_reg   (*((volatile unsigned int*) ISO_IC1_RXFLR_reg))
#define ISO_IC1_RXFLR_inst_adr                                                       "0x001E"
#define ISO_IC1_RXFLR_inst                                                           0x001E
#define ISO_IC1_RXFLR_rxflr_shift                                                    (0)
#define ISO_IC1_RXFLR_rxflr_mask                                                     (0x0000000F)
#define ISO_IC1_RXFLR_rxflr(data)                                                    (0x0000000F&((data)<<0))
#define ISO_IC1_RXFLR_rxflr_src(data)                                                ((0x0000000F&(data))>>0)
#define ISO_IC1_RXFLR_get_rxflr(data)                                                ((0x0000000F&(data))>>0)


#define ISO_IC1_SDA_HOLD                                                             0x98007C7C
#define ISO_IC1_SDA_HOLD_reg_addr                                                    "0x98007C7C"
#define ISO_IC1_SDA_HOLD_reg                                                         0x98007C7C
#define set_ISO_IC1_SDA_HOLD_reg(data)   (*((volatile unsigned int*) ISO_IC1_SDA_HOLD_reg)=data)
#define get_ISO_IC1_SDA_HOLD_reg   (*((volatile unsigned int*) ISO_IC1_SDA_HOLD_reg))
#define ISO_IC1_SDA_HOLD_inst_adr                                                    "0x001F"
#define ISO_IC1_SDA_HOLD_inst                                                        0x001F
#define ISO_IC1_SDA_HOLD_ic_sda_hold_shift                                           (0)
#define ISO_IC1_SDA_HOLD_ic_sda_hold_mask                                            (0x0000FFFF)
#define ISO_IC1_SDA_HOLD_ic_sda_hold(data)                                           (0x0000FFFF&((data)<<0))
#define ISO_IC1_SDA_HOLD_ic_sda_hold_src(data)                                       ((0x0000FFFF&(data))>>0)
#define ISO_IC1_SDA_HOLD_get_ic_sda_hold(data)                                       ((0x0000FFFF&(data))>>0)


#define ISO_IC1_TX_ABRT_SOURCE                                                       0x98007C80
#define ISO_IC1_TX_ABRT_SOURCE_reg_addr                                              "0x98007C80"
#define ISO_IC1_TX_ABRT_SOURCE_reg                                                   0x98007C80
#define set_ISO_IC1_TX_ABRT_SOURCE_reg(data)   (*((volatile unsigned int*) ISO_IC1_TX_ABRT_SOURCE_reg)=data)
#define get_ISO_IC1_TX_ABRT_SOURCE_reg   (*((volatile unsigned int*) ISO_IC1_TX_ABRT_SOURCE_reg))
#define ISO_IC1_TX_ABRT_SOURCE_inst_adr                                              "0x0020"
#define ISO_IC1_TX_ABRT_SOURCE_inst                                                  0x0020
#define ISO_IC1_TX_ABRT_SOURCE_abrt_slvrd_intx_shift                                 (15)
#define ISO_IC1_TX_ABRT_SOURCE_abrt_slvrd_intx_mask                                  (0x00008000)
#define ISO_IC1_TX_ABRT_SOURCE_abrt_slvrd_intx(data)                                 (0x00008000&((data)<<15))
#define ISO_IC1_TX_ABRT_SOURCE_abrt_slvrd_intx_src(data)                             ((0x00008000&(data))>>15)
#define ISO_IC1_TX_ABRT_SOURCE_get_abrt_slvrd_intx(data)                             ((0x00008000&(data))>>15)
#define ISO_IC1_TX_ABRT_SOURCE_abrt_slv_arblost_shift                                (14)
#define ISO_IC1_TX_ABRT_SOURCE_abrt_slv_arblost_mask                                 (0x00004000)
#define ISO_IC1_TX_ABRT_SOURCE_abrt_slv_arblost(data)                                (0x00004000&((data)<<14))
#define ISO_IC1_TX_ABRT_SOURCE_abrt_slv_arblost_src(data)                            ((0x00004000&(data))>>14)
#define ISO_IC1_TX_ABRT_SOURCE_get_abrt_slv_arblost(data)                            ((0x00004000&(data))>>14)
#define ISO_IC1_TX_ABRT_SOURCE_abrt_slvflush_txfifo_shift                            (13)
#define ISO_IC1_TX_ABRT_SOURCE_abrt_slvflush_txfifo_mask                             (0x00002000)
#define ISO_IC1_TX_ABRT_SOURCE_abrt_slvflush_txfifo(data)                            (0x00002000&((data)<<13))
#define ISO_IC1_TX_ABRT_SOURCE_abrt_slvflush_txfifo_src(data)                        ((0x00002000&(data))>>13)
#define ISO_IC1_TX_ABRT_SOURCE_get_abrt_slvflush_txfifo(data)                        ((0x00002000&(data))>>13)
#define ISO_IC1_TX_ABRT_SOURCE_arb_lost_shift                                        (12)
#define ISO_IC1_TX_ABRT_SOURCE_arb_lost_mask                                         (0x00001000)
#define ISO_IC1_TX_ABRT_SOURCE_arb_lost(data)                                        (0x00001000&((data)<<12))
#define ISO_IC1_TX_ABRT_SOURCE_arb_lost_src(data)                                    ((0x00001000&(data))>>12)
#define ISO_IC1_TX_ABRT_SOURCE_get_arb_lost(data)                                    ((0x00001000&(data))>>12)
#define ISO_IC1_TX_ABRT_SOURCE_arb_master_dis_shift                                  (11)
#define ISO_IC1_TX_ABRT_SOURCE_arb_master_dis_mask                                   (0x00000800)
#define ISO_IC1_TX_ABRT_SOURCE_arb_master_dis(data)                                  (0x00000800&((data)<<11))
#define ISO_IC1_TX_ABRT_SOURCE_arb_master_dis_src(data)                              ((0x00000800&(data))>>11)
#define ISO_IC1_TX_ABRT_SOURCE_get_arb_master_dis(data)                              ((0x00000800&(data))>>11)
#define ISO_IC1_TX_ABRT_SOURCE_abrt_10b_rd_norstrt_shift                             (10)
#define ISO_IC1_TX_ABRT_SOURCE_abrt_10b_rd_norstrt_mask                              (0x00000400)
#define ISO_IC1_TX_ABRT_SOURCE_abrt_10b_rd_norstrt(data)                             (0x00000400&((data)<<10))
#define ISO_IC1_TX_ABRT_SOURCE_abrt_10b_rd_norstrt_src(data)                         ((0x00000400&(data))>>10)
#define ISO_IC1_TX_ABRT_SOURCE_get_abrt_10b_rd_norstrt(data)                         ((0x00000400&(data))>>10)
#define ISO_IC1_TX_ABRT_SOURCE_abrt_sbyte_norstrt_shift                              (9)
#define ISO_IC1_TX_ABRT_SOURCE_abrt_sbyte_norstrt_mask                               (0x00000200)
#define ISO_IC1_TX_ABRT_SOURCE_abrt_sbyte_norstrt(data)                              (0x00000200&((data)<<9))
#define ISO_IC1_TX_ABRT_SOURCE_abrt_sbyte_norstrt_src(data)                          ((0x00000200&(data))>>9)
#define ISO_IC1_TX_ABRT_SOURCE_get_abrt_sbyte_norstrt(data)                          ((0x00000200&(data))>>9)
#define ISO_IC1_TX_ABRT_SOURCE_abrt_hs_norstrt_shift                                 (8)
#define ISO_IC1_TX_ABRT_SOURCE_abrt_hs_norstrt_mask                                  (0x00000100)
#define ISO_IC1_TX_ABRT_SOURCE_abrt_hs_norstrt(data)                                 (0x00000100&((data)<<8))
#define ISO_IC1_TX_ABRT_SOURCE_abrt_hs_norstrt_src(data)                             ((0x00000100&(data))>>8)
#define ISO_IC1_TX_ABRT_SOURCE_get_abrt_hs_norstrt(data)                             ((0x00000100&(data))>>8)
#define ISO_IC1_TX_ABRT_SOURCE_abrt_sbyte_ackdet_shift                               (7)
#define ISO_IC1_TX_ABRT_SOURCE_abrt_sbyte_ackdet_mask                                (0x00000080)
#define ISO_IC1_TX_ABRT_SOURCE_abrt_sbyte_ackdet(data)                               (0x00000080&((data)<<7))
#define ISO_IC1_TX_ABRT_SOURCE_abrt_sbyte_ackdet_src(data)                           ((0x00000080&(data))>>7)
#define ISO_IC1_TX_ABRT_SOURCE_get_abrt_sbyte_ackdet(data)                           ((0x00000080&(data))>>7)
#define ISO_IC1_TX_ABRT_SOURCE_abrt_hs_ackdet_shift                                  (6)
#define ISO_IC1_TX_ABRT_SOURCE_abrt_hs_ackdet_mask                                   (0x00000040)
#define ISO_IC1_TX_ABRT_SOURCE_abrt_hs_ackdet(data)                                  (0x00000040&((data)<<6))
#define ISO_IC1_TX_ABRT_SOURCE_abrt_hs_ackdet_src(data)                              ((0x00000040&(data))>>6)
#define ISO_IC1_TX_ABRT_SOURCE_get_abrt_hs_ackdet(data)                              ((0x00000040&(data))>>6)
#define ISO_IC1_TX_ABRT_SOURCE_abrt_gcall_read_shift                                 (5)
#define ISO_IC1_TX_ABRT_SOURCE_abrt_gcall_read_mask                                  (0x00000020)
#define ISO_IC1_TX_ABRT_SOURCE_abrt_gcall_read(data)                                 (0x00000020&((data)<<5))
#define ISO_IC1_TX_ABRT_SOURCE_abrt_gcall_read_src(data)                             ((0x00000020&(data))>>5)
#define ISO_IC1_TX_ABRT_SOURCE_get_abrt_gcall_read(data)                             ((0x00000020&(data))>>5)
#define ISO_IC1_TX_ABRT_SOURCE_abrt_gcall_noack_shift                                (4)
#define ISO_IC1_TX_ABRT_SOURCE_abrt_gcall_noack_mask                                 (0x00000010)
#define ISO_IC1_TX_ABRT_SOURCE_abrt_gcall_noack(data)                                (0x00000010&((data)<<4))
#define ISO_IC1_TX_ABRT_SOURCE_abrt_gcall_noack_src(data)                            ((0x00000010&(data))>>4)
#define ISO_IC1_TX_ABRT_SOURCE_get_abrt_gcall_noack(data)                            ((0x00000010&(data))>>4)
#define ISO_IC1_TX_ABRT_SOURCE_abrt_txdata_noack_shift                               (3)
#define ISO_IC1_TX_ABRT_SOURCE_abrt_txdata_noack_mask                                (0x00000008)
#define ISO_IC1_TX_ABRT_SOURCE_abrt_txdata_noack(data)                               (0x00000008&((data)<<3))
#define ISO_IC1_TX_ABRT_SOURCE_abrt_txdata_noack_src(data)                           ((0x00000008&(data))>>3)
#define ISO_IC1_TX_ABRT_SOURCE_get_abrt_txdata_noack(data)                           ((0x00000008&(data))>>3)
#define ISO_IC1_TX_ABRT_SOURCE_abrt_10addr2_noack_shift                              (2)
#define ISO_IC1_TX_ABRT_SOURCE_abrt_10addr2_noack_mask                               (0x00000004)
#define ISO_IC1_TX_ABRT_SOURCE_abrt_10addr2_noack(data)                              (0x00000004&((data)<<2))
#define ISO_IC1_TX_ABRT_SOURCE_abrt_10addr2_noack_src(data)                          ((0x00000004&(data))>>2)
#define ISO_IC1_TX_ABRT_SOURCE_get_abrt_10addr2_noack(data)                          ((0x00000004&(data))>>2)
#define ISO_IC1_TX_ABRT_SOURCE_abrt_10addr1_noack_shift                              (1)
#define ISO_IC1_TX_ABRT_SOURCE_abrt_10addr1_noack_mask                               (0x00000002)
#define ISO_IC1_TX_ABRT_SOURCE_abrt_10addr1_noack(data)                              (0x00000002&((data)<<1))
#define ISO_IC1_TX_ABRT_SOURCE_abrt_10addr1_noack_src(data)                          ((0x00000002&(data))>>1)
#define ISO_IC1_TX_ABRT_SOURCE_get_abrt_10addr1_noack(data)                          ((0x00000002&(data))>>1)
#define ISO_IC1_TX_ABRT_SOURCE_abrt_7b_addr_noack_shift                              (0)
#define ISO_IC1_TX_ABRT_SOURCE_abrt_7b_addr_noack_mask                               (0x00000001)
#define ISO_IC1_TX_ABRT_SOURCE_abrt_7b_addr_noack(data)                              (0x00000001&((data)<<0))
#define ISO_IC1_TX_ABRT_SOURCE_abrt_7b_addr_noack_src(data)                          ((0x00000001&(data))>>0)
#define ISO_IC1_TX_ABRT_SOURCE_get_abrt_7b_addr_noack(data)                          ((0x00000001&(data))>>0)


#define ISO_IC1_SLV_DATA_NACK_ONLY                                                   0x98007C84
#define ISO_IC1_SLV_DATA_NACK_ONLY_reg_addr                                          "0x98007C84"
#define ISO_IC1_SLV_DATA_NACK_ONLY_reg                                               0x98007C84
#define set_ISO_IC1_SLV_DATA_NACK_ONLY_reg(data)   (*((volatile unsigned int*) ISO_IC1_SLV_DATA_NACK_ONLY_reg)=data)
#define get_ISO_IC1_SLV_DATA_NACK_ONLY_reg   (*((volatile unsigned int*) ISO_IC1_SLV_DATA_NACK_ONLY_reg))
#define ISO_IC1_SLV_DATA_NACK_ONLY_inst_adr                                          "0x0021"
#define ISO_IC1_SLV_DATA_NACK_ONLY_inst                                              0x0021
#define ISO_IC1_SLV_DATA_NACK_ONLY_nack_shift                                        (0)
#define ISO_IC1_SLV_DATA_NACK_ONLY_nack_mask                                         (0x00000001)
#define ISO_IC1_SLV_DATA_NACK_ONLY_nack(data)                                        (0x00000001&((data)<<0))
#define ISO_IC1_SLV_DATA_NACK_ONLY_nack_src(data)                                    ((0x00000001&(data))>>0)
#define ISO_IC1_SLV_DATA_NACK_ONLY_get_nack(data)                                    ((0x00000001&(data))>>0)


#define ISO_IC1_DMA_CR                                                               0x98007C88
#define ISO_IC1_DMA_CR_reg_addr                                                      "0x98007C88"
#define ISO_IC1_DMA_CR_reg                                                           0x98007C88
#define set_ISO_IC1_DMA_CR_reg(data)   (*((volatile unsigned int*) ISO_IC1_DMA_CR_reg)=data)
#define get_ISO_IC1_DMA_CR_reg   (*((volatile unsigned int*) ISO_IC1_DMA_CR_reg))
#define ISO_IC1_DMA_CR_inst_adr                                                      "0x0022"
#define ISO_IC1_DMA_CR_inst                                                          0x0022
#define ISO_IC1_DMA_CR_tdmae_shift                                                   (1)
#define ISO_IC1_DMA_CR_tdmae_mask                                                    (0x00000002)
#define ISO_IC1_DMA_CR_tdmae(data)                                                   (0x00000002&((data)<<1))
#define ISO_IC1_DMA_CR_tdmae_src(data)                                               ((0x00000002&(data))>>1)
#define ISO_IC1_DMA_CR_get_tdmae(data)                                               ((0x00000002&(data))>>1)
#define ISO_IC1_DMA_CR_rdmae_shift                                                   (0)
#define ISO_IC1_DMA_CR_rdmae_mask                                                    (0x00000001)
#define ISO_IC1_DMA_CR_rdmae(data)                                                   (0x00000001&((data)<<0))
#define ISO_IC1_DMA_CR_rdmae_src(data)                                               ((0x00000001&(data))>>0)
#define ISO_IC1_DMA_CR_get_rdmae(data)                                               ((0x00000001&(data))>>0)


#define ISO_IC1_DMA_TDLR                                                             0x98007C8C
#define ISO_IC1_DMA_TDLR_reg_addr                                                    "0x98007C8C"
#define ISO_IC1_DMA_TDLR_reg                                                         0x98007C8C
#define set_ISO_IC1_DMA_TDLR_reg(data)   (*((volatile unsigned int*) ISO_IC1_DMA_TDLR_reg)=data)
#define get_ISO_IC1_DMA_TDLR_reg   (*((volatile unsigned int*) ISO_IC1_DMA_TDLR_reg))
#define ISO_IC1_DMA_TDLR_inst_adr                                                    "0x0023"
#define ISO_IC1_DMA_TDLR_inst                                                        0x0023
#define ISO_IC1_DMA_TDLR_dmatdl_shift                                                (0)
#define ISO_IC1_DMA_TDLR_dmatdl_mask                                                 (0x00000007)
#define ISO_IC1_DMA_TDLR_dmatdl(data)                                                (0x00000007&((data)<<0))
#define ISO_IC1_DMA_TDLR_dmatdl_src(data)                                            ((0x00000007&(data))>>0)
#define ISO_IC1_DMA_TDLR_get_dmatdl(data)                                            ((0x00000007&(data))>>0)


#define ISO_IC1_DMA_RDLR                                                             0x98007C90
#define ISO_IC1_DMA_RDLR_reg_addr                                                    "0x98007C90"
#define ISO_IC1_DMA_RDLR_reg                                                         0x98007C90
#define set_ISO_IC1_DMA_RDLR_reg(data)   (*((volatile unsigned int*) ISO_IC1_DMA_RDLR_reg)=data)
#define get_ISO_IC1_DMA_RDLR_reg   (*((volatile unsigned int*) ISO_IC1_DMA_RDLR_reg))
#define ISO_IC1_DMA_RDLR_inst_adr                                                    "0x0024"
#define ISO_IC1_DMA_RDLR_inst                                                        0x0024
#define ISO_IC1_DMA_RDLR_dmardl_shift                                                (0)
#define ISO_IC1_DMA_RDLR_dmardl_mask                                                 (0x0000000F)
#define ISO_IC1_DMA_RDLR_dmardl(data)                                                (0x0000000F&((data)<<0))
#define ISO_IC1_DMA_RDLR_dmardl_src(data)                                            ((0x0000000F&(data))>>0)
#define ISO_IC1_DMA_RDLR_get_dmardl(data)                                            ((0x0000000F&(data))>>0)


#define ISO_IC1_SDA_SETUP                                                            0x98007C94
#define ISO_IC1_SDA_SETUP_reg_addr                                                   "0x98007C94"
#define ISO_IC1_SDA_SETUP_reg                                                        0x98007C94
#define set_ISO_IC1_SDA_SETUP_reg(data)   (*((volatile unsigned int*) ISO_IC1_SDA_SETUP_reg)=data)
#define get_ISO_IC1_SDA_SETUP_reg   (*((volatile unsigned int*) ISO_IC1_SDA_SETUP_reg))
#define ISO_IC1_SDA_SETUP_inst_adr                                                   "0x0025"
#define ISO_IC1_SDA_SETUP_inst                                                       0x0025
#define ISO_IC1_SDA_SETUP_sda_setup_shift                                            (0)
#define ISO_IC1_SDA_SETUP_sda_setup_mask                                             (0x000000FF)
#define ISO_IC1_SDA_SETUP_sda_setup(data)                                            (0x000000FF&((data)<<0))
#define ISO_IC1_SDA_SETUP_sda_setup_src(data)                                        ((0x000000FF&(data))>>0)
#define ISO_IC1_SDA_SETUP_get_sda_setup(data)                                        ((0x000000FF&(data))>>0)


#define ISO_IC1_ACK_GENERAL_CALL                                                     0x98007C98
#define ISO_IC1_ACK_GENERAL_CALL_reg_addr                                            "0x98007C98"
#define ISO_IC1_ACK_GENERAL_CALL_reg                                                 0x98007C98
#define set_ISO_IC1_ACK_GENERAL_CALL_reg(data)   (*((volatile unsigned int*) ISO_IC1_ACK_GENERAL_CALL_reg)=data)
#define get_ISO_IC1_ACK_GENERAL_CALL_reg   (*((volatile unsigned int*) ISO_IC1_ACK_GENERAL_CALL_reg))
#define ISO_IC1_ACK_GENERAL_CALL_inst_adr                                            "0x0026"
#define ISO_IC1_ACK_GENERAL_CALL_inst                                                0x0026
#define ISO_IC1_ACK_GENERAL_CALL_ack_gen_call_shift                                  (0)
#define ISO_IC1_ACK_GENERAL_CALL_ack_gen_call_mask                                   (0x00000001)
#define ISO_IC1_ACK_GENERAL_CALL_ack_gen_call(data)                                  (0x00000001&((data)<<0))
#define ISO_IC1_ACK_GENERAL_CALL_ack_gen_call_src(data)                              ((0x00000001&(data))>>0)
#define ISO_IC1_ACK_GENERAL_CALL_get_ack_gen_call(data)                              ((0x00000001&(data))>>0)


#define ISO_IC1_ENABLE_STATUS                                                        0x98007C9C
#define ISO_IC1_ENABLE_STATUS_reg_addr                                               "0x98007C9C"
#define ISO_IC1_ENABLE_STATUS_reg                                                    0x98007C9C
#define set_ISO_IC1_ENABLE_STATUS_reg(data)   (*((volatile unsigned int*) ISO_IC1_ENABLE_STATUS_reg)=data)
#define get_ISO_IC1_ENABLE_STATUS_reg   (*((volatile unsigned int*) ISO_IC1_ENABLE_STATUS_reg))
#define ISO_IC1_ENABLE_STATUS_inst_adr                                               "0x0027"
#define ISO_IC1_ENABLE_STATUS_inst                                                   0x0027
#define ISO_IC1_ENABLE_STATUS_slv_rx_data_lost_shift                                 (2)
#define ISO_IC1_ENABLE_STATUS_slv_rx_data_lost_mask                                  (0x00000004)
#define ISO_IC1_ENABLE_STATUS_slv_rx_data_lost(data)                                 (0x00000004&((data)<<2))
#define ISO_IC1_ENABLE_STATUS_slv_rx_data_lost_src(data)                             ((0x00000004&(data))>>2)
#define ISO_IC1_ENABLE_STATUS_get_slv_rx_data_lost(data)                             ((0x00000004&(data))>>2)
#define ISO_IC1_ENABLE_STATUS_slv_disabled_whi_shift                                 (1)
#define ISO_IC1_ENABLE_STATUS_slv_disabled_whi_mask                                  (0x00000002)
#define ISO_IC1_ENABLE_STATUS_slv_disabled_whi(data)                                 (0x00000002&((data)<<1))
#define ISO_IC1_ENABLE_STATUS_slv_disabled_whi_src(data)                             ((0x00000002&(data))>>1)
#define ISO_IC1_ENABLE_STATUS_get_slv_disabled_whi(data)                             ((0x00000002&(data))>>1)
#define ISO_IC1_ENABLE_STATUS_ic_en_shift                                            (0)
#define ISO_IC1_ENABLE_STATUS_ic_en_mask                                             (0x00000001)
#define ISO_IC1_ENABLE_STATUS_ic_en(data)                                            (0x00000001&((data)<<0))
#define ISO_IC1_ENABLE_STATUS_ic_en_src(data)                                        ((0x00000001&(data))>>0)
#define ISO_IC1_ENABLE_STATUS_get_ic_en(data)                                        ((0x00000001&(data))>>0)


#define ISO_IC1_COMP_PARAM_1                                                         0x98007CF4
#define ISO_IC1_COMP_PARAM_1_reg_addr                                                "0x98007CF4"
#define ISO_IC1_COMP_PARAM_1_reg                                                     0x98007CF4
#define set_ISO_IC1_COMP_PARAM_1_reg(data)   (*((volatile unsigned int*) ISO_IC1_COMP_PARAM_1_reg)=data)
#define get_ISO_IC1_COMP_PARAM_1_reg   (*((volatile unsigned int*) ISO_IC1_COMP_PARAM_1_reg))
#define ISO_IC1_COMP_PARAM_1_inst_adr                                                "0x003D"
#define ISO_IC1_COMP_PARAM_1_inst                                                    0x003D
#define ISO_IC1_COMP_PARAM_1_tx_buffer_depth_shift                                   (16)
#define ISO_IC1_COMP_PARAM_1_tx_buffer_depth_mask                                    (0x00FF0000)
#define ISO_IC1_COMP_PARAM_1_tx_buffer_depth(data)                                   (0x00FF0000&((data)<<16))
#define ISO_IC1_COMP_PARAM_1_tx_buffer_depth_src(data)                               ((0x00FF0000&(data))>>16)
#define ISO_IC1_COMP_PARAM_1_get_tx_buffer_depth(data)                               ((0x00FF0000&(data))>>16)
#define ISO_IC1_COMP_PARAM_1_rx_buffer_depth_shift                                   (8)
#define ISO_IC1_COMP_PARAM_1_rx_buffer_depth_mask                                    (0x0000FF00)
#define ISO_IC1_COMP_PARAM_1_rx_buffer_depth(data)                                   (0x0000FF00&((data)<<8))
#define ISO_IC1_COMP_PARAM_1_rx_buffer_depth_src(data)                               ((0x0000FF00&(data))>>8)
#define ISO_IC1_COMP_PARAM_1_get_rx_buffer_depth(data)                               ((0x0000FF00&(data))>>8)
#define ISO_IC1_COMP_PARAM_1_add_encoded_params_shift                                (7)
#define ISO_IC1_COMP_PARAM_1_add_encoded_params_mask                                 (0x00000080)
#define ISO_IC1_COMP_PARAM_1_add_encoded_params(data)                                (0x00000080&((data)<<7))
#define ISO_IC1_COMP_PARAM_1_add_encoded_params_src(data)                            ((0x00000080&(data))>>7)
#define ISO_IC1_COMP_PARAM_1_get_add_encoded_params(data)                            ((0x00000080&(data))>>7)
#define ISO_IC1_COMP_PARAM_1_has_dma_shift                                           (6)
#define ISO_IC1_COMP_PARAM_1_has_dma_mask                                            (0x00000040)
#define ISO_IC1_COMP_PARAM_1_has_dma(data)                                           (0x00000040&((data)<<6))
#define ISO_IC1_COMP_PARAM_1_has_dma_src(data)                                       ((0x00000040&(data))>>6)
#define ISO_IC1_COMP_PARAM_1_get_has_dma(data)                                       ((0x00000040&(data))>>6)
#define ISO_IC1_COMP_PARAM_1_intr_io_shift                                           (5)
#define ISO_IC1_COMP_PARAM_1_intr_io_mask                                            (0x00000020)
#define ISO_IC1_COMP_PARAM_1_intr_io(data)                                           (0x00000020&((data)<<5))
#define ISO_IC1_COMP_PARAM_1_intr_io_src(data)                                       ((0x00000020&(data))>>5)
#define ISO_IC1_COMP_PARAM_1_get_intr_io(data)                                       ((0x00000020&(data))>>5)
#define ISO_IC1_COMP_PARAM_1_hc_count_values_shift                                   (4)
#define ISO_IC1_COMP_PARAM_1_hc_count_values_mask                                    (0x00000010)
#define ISO_IC1_COMP_PARAM_1_hc_count_values(data)                                   (0x00000010&((data)<<4))
#define ISO_IC1_COMP_PARAM_1_hc_count_values_src(data)                               ((0x00000010&(data))>>4)
#define ISO_IC1_COMP_PARAM_1_get_hc_count_values(data)                               ((0x00000010&(data))>>4)
#define ISO_IC1_COMP_PARAM_1_max_speed_mode_shift                                    (2)
#define ISO_IC1_COMP_PARAM_1_max_speed_mode_mask                                     (0x0000000C)
#define ISO_IC1_COMP_PARAM_1_max_speed_mode(data)                                    (0x0000000C&((data)<<2))
#define ISO_IC1_COMP_PARAM_1_max_speed_mode_src(data)                                ((0x0000000C&(data))>>2)
#define ISO_IC1_COMP_PARAM_1_get_max_speed_mode(data)                                ((0x0000000C&(data))>>2)
#define ISO_IC1_COMP_PARAM_1_apb_data_width_shift                                    (0)
#define ISO_IC1_COMP_PARAM_1_apb_data_width_mask                                     (0x00000003)
#define ISO_IC1_COMP_PARAM_1_apb_data_width(data)                                    (0x00000003&((data)<<0))
#define ISO_IC1_COMP_PARAM_1_apb_data_width_src(data)                                ((0x00000003&(data))>>0)
#define ISO_IC1_COMP_PARAM_1_get_apb_data_width(data)                                ((0x00000003&(data))>>0)


#define ISO_IC1_COMP_VERSION                                                         0x98007CF8
#define ISO_IC1_COMP_VERSION_reg_addr                                                "0x98007CF8"
#define ISO_IC1_COMP_VERSION_reg                                                     0x98007CF8
#define set_ISO_IC1_COMP_VERSION_reg(data)   (*((volatile unsigned int*) ISO_IC1_COMP_VERSION_reg)=data)
#define get_ISO_IC1_COMP_VERSION_reg   (*((volatile unsigned int*) ISO_IC1_COMP_VERSION_reg))
#define ISO_IC1_COMP_VERSION_inst_adr                                                "0x003E"
#define ISO_IC1_COMP_VERSION_inst                                                    0x003E
#define ISO_IC1_COMP_VERSION_ic_comp_version_shift                                   (0)
#define ISO_IC1_COMP_VERSION_ic_comp_version_mask                                    (0xFFFFFFFF)
#define ISO_IC1_COMP_VERSION_ic_comp_version(data)                                   (0xFFFFFFFF&((data)<<0))
#define ISO_IC1_COMP_VERSION_ic_comp_version_src(data)                               ((0xFFFFFFFF&(data))>>0)
#define ISO_IC1_COMP_VERSION_get_ic_comp_version(data)                               ((0xFFFFFFFF&(data))>>0)


#define ISO_IC1_COMP_TYPE                                                            0x98007CFC
#define ISO_IC1_COMP_TYPE_reg_addr                                                   "0x98007CFC"
#define ISO_IC1_COMP_TYPE_reg                                                        0x98007CFC
#define set_ISO_IC1_COMP_TYPE_reg(data)   (*((volatile unsigned int*) ISO_IC1_COMP_TYPE_reg)=data)
#define get_ISO_IC1_COMP_TYPE_reg   (*((volatile unsigned int*) ISO_IC1_COMP_TYPE_reg))
#define ISO_IC1_COMP_TYPE_inst_adr                                                   "0x003F"
#define ISO_IC1_COMP_TYPE_inst                                                       0x003F
#define ISO_IC1_COMP_TYPE_ic_comp_type_shift                                         (0)
#define ISO_IC1_COMP_TYPE_ic_comp_type_mask                                          (0xFFFFFFFF)
#define ISO_IC1_COMP_TYPE_ic_comp_type(data)                                         (0xFFFFFFFF&((data)<<0))
#define ISO_IC1_COMP_TYPE_ic_comp_type_src(data)                                     ((0xFFFFFFFF&(data))>>0)
#define ISO_IC1_COMP_TYPE_get_ic_comp_type(data)                                     ((0xFFFFFFFF&(data))>>0)


#define ISO_PWM_OCD                                                                  0x980070D0
#define ISO_PWM_OCD_reg_addr                                                         "0x980070D0"
#define ISO_PWM_OCD_reg                                                              0x980070D0
#define set_ISO_PWM_OCD_reg(data)   (*((volatile unsigned int*) ISO_PWM_OCD_reg)=data)
#define get_ISO_PWM_OCD_reg   (*((volatile unsigned int*) ISO_PWM_OCD_reg))
#define ISO_PWM_OCD_inst_adr                                                         "0x0034"
#define ISO_PWM_OCD_inst                                                             0x0034
#define ISO_PWM_OCD_3_shift                                                          (24)
#define ISO_PWM_OCD_3_mask                                                           (0xFF000000)
#define ISO_PWM_OCD_3(data)                                                          (0xFF000000&((data)<<24))
#define ISO_PWM_OCD_3_src(data)                                                      ((0xFF000000&(data))>>24)
#define ISO_PWM_OCD_get_3(data)                                                      ((0xFF000000&(data))>>24)
#define ISO_PWM_OCD_2_shift                                                          (16)
#define ISO_PWM_OCD_2_mask                                                           (0x00FF0000)
#define ISO_PWM_OCD_2(data)                                                          (0x00FF0000&((data)<<16))
#define ISO_PWM_OCD_2_src(data)                                                      ((0x00FF0000&(data))>>16)
#define ISO_PWM_OCD_get_2(data)                                                      ((0x00FF0000&(data))>>16)
#define ISO_PWM_OCD_1_shift                                                          (8)
#define ISO_PWM_OCD_1_mask                                                           (0x0000FF00)
#define ISO_PWM_OCD_1(data)                                                          (0x0000FF00&((data)<<8))
#define ISO_PWM_OCD_1_src(data)                                                      ((0x0000FF00&(data))>>8)
#define ISO_PWM_OCD_get_1(data)                                                      ((0x0000FF00&(data))>>8)
#define ISO_PWM_OCD_0_shift                                                          (0)
#define ISO_PWM_OCD_0_mask                                                           (0x000000FF)
#define ISO_PWM_OCD_0(data)                                                          (0x000000FF&((data)<<0))
#define ISO_PWM_OCD_0_src(data)                                                      ((0x000000FF&(data))>>0)
#define ISO_PWM_OCD_get_0(data)                                                      ((0x000000FF&(data))>>0)


#define ISO_PWM_CD                                                                   0x980070D4
#define ISO_PWM_CD_reg_addr                                                          "0x980070D4"
#define ISO_PWM_CD_reg                                                               0x980070D4
#define set_ISO_PWM_CD_reg(data)   (*((volatile unsigned int*) ISO_PWM_CD_reg)=data)
#define get_ISO_PWM_CD_reg   (*((volatile unsigned int*) ISO_PWM_CD_reg))
#define ISO_PWM_CD_inst_adr                                                          "0x0035"
#define ISO_PWM_CD_inst                                                              0x0035
#define ISO_PWM_CD_3_shift                                                           (24)
#define ISO_PWM_CD_3_mask                                                            (0xFF000000)
#define ISO_PWM_CD_3(data)                                                           (0xFF000000&((data)<<24))
#define ISO_PWM_CD_3_src(data)                                                       ((0xFF000000&(data))>>24)
#define ISO_PWM_CD_get_3(data)                                                       ((0xFF000000&(data))>>24)
#define ISO_PWM_CD_2_shift                                                           (16)
#define ISO_PWM_CD_2_mask                                                            (0x00FF0000)
#define ISO_PWM_CD_2(data)                                                           (0x00FF0000&((data)<<16))
#define ISO_PWM_CD_2_src(data)                                                       ((0x00FF0000&(data))>>16)
#define ISO_PWM_CD_get_2(data)                                                       ((0x00FF0000&(data))>>16)
#define ISO_PWM_CD_1_shift                                                           (8)
#define ISO_PWM_CD_1_mask                                                            (0x0000FF00)
#define ISO_PWM_CD_1(data)                                                           (0x0000FF00&((data)<<8))
#define ISO_PWM_CD_1_src(data)                                                       ((0x0000FF00&(data))>>8)
#define ISO_PWM_CD_get_1(data)                                                       ((0x0000FF00&(data))>>8)
#define ISO_PWM_CD_0_shift                                                           (0)
#define ISO_PWM_CD_0_mask                                                            (0x000000FF)
#define ISO_PWM_CD_0(data)                                                           (0x000000FF&((data)<<0))
#define ISO_PWM_CD_0_src(data)                                                       ((0x000000FF&(data))>>0)
#define ISO_PWM_CD_get_0(data)                                                       ((0x000000FF&(data))>>0)


#define ISO_PWM_CSD                                                                  0x980070D8
#define ISO_PWM_CSD_reg_addr                                                         "0x980070D8"
#define ISO_PWM_CSD_reg                                                              0x980070D8
#define set_ISO_PWM_CSD_reg(data)   (*((volatile unsigned int*) ISO_PWM_CSD_reg)=data)
#define get_ISO_PWM_CSD_reg   (*((volatile unsigned int*) ISO_PWM_CSD_reg))
#define ISO_PWM_CSD_inst_adr                                                         "0x0036"
#define ISO_PWM_CSD_inst                                                             0x0036
#define ISO_PWM_CSD_3_shift                                                          (12)
#define ISO_PWM_CSD_3_mask                                                           (0x0000F000)
#define ISO_PWM_CSD_3(data)                                                          (0x0000F000&((data)<<12))
#define ISO_PWM_CSD_3_src(data)                                                      ((0x0000F000&(data))>>12)
#define ISO_PWM_CSD_get_3(data)                                                      ((0x0000F000&(data))>>12)
#define ISO_PWM_CSD_2_shift                                                          (8)
#define ISO_PWM_CSD_2_mask                                                           (0x00000F00)
#define ISO_PWM_CSD_2(data)                                                          (0x00000F00&((data)<<8))
#define ISO_PWM_CSD_2_src(data)                                                      ((0x00000F00&(data))>>8)
#define ISO_PWM_CSD_get_2(data)                                                      ((0x00000F00&(data))>>8)
#define ISO_PWM_CSD_1_shift                                                          (4)
#define ISO_PWM_CSD_1_mask                                                           (0x000000F0)
#define ISO_PWM_CSD_1(data)                                                          (0x000000F0&((data)<<4))
#define ISO_PWM_CSD_1_src(data)                                                      ((0x000000F0&(data))>>4)
#define ISO_PWM_CSD_get_1(data)                                                      ((0x000000F0&(data))>>4)
#define ISO_PWM_CSD_0_shift                                                          (0)
#define ISO_PWM_CSD_0_mask                                                           (0x0000000F)
#define ISO_PWM_CSD_0(data)                                                          (0x0000000F&((data)<<0))
#define ISO_PWM_CSD_0_src(data)                                                      ((0x0000000F&(data))>>0)
#define ISO_PWM_CSD_get_0(data)                                                      ((0x0000000F&(data))>>0)


#endif
