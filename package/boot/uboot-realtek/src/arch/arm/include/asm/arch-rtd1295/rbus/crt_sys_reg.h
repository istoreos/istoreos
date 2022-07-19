/**************************************************************
// Spec Version                  : 4.0.6
// Parser Version                : DVR_Parser_6.11(120105)
// CModelGen Version             : 5.1 2012.01.05
// Naming Rule                   :  Module_Register_Name
// Naming Rule                   : Module_Register_Name
// Parse Option                  : Only Parse _op1
// Parse Address Region          : All Address Region 
// Decode bit number             : 12 bits
// Firmware Header Generate Date : 2015/7/22 11:18:38
***************************************************************/


#ifndef _SYS_REG_H_INCLUDED_
#define _SYS_REG_H_INCLUDED_
#ifdef  _SYS_USE_STRUCT
typedef struct 
{
unsigned int     rstn_rsa:1;
unsigned int     rstn_mipi:1;
unsigned int     rstn_nf:1;
unsigned int     rstn_ae:1;
unsigned int     rstn_tp:1;
unsigned int     rstn_md:1;
unsigned int     rstn_cp:1;
unsigned int     rstn_dc_phy:1;
unsigned int     rstn_dcu:1;
unsigned int     rstn_se:1;
unsigned int     rstn_lvds:1;
unsigned int     rstn_vo:1;
unsigned int     rstn_tve:1;
unsigned int     rstn_gpu:1;
unsigned int     rstn_aio:1;
unsigned int     rstn_etn:1;
unsigned int     rstn_ve3:1;
unsigned int     rstn_ve2:1;
unsigned int     rstn_ve1:1;
unsigned int     rstn_hdmi:1;
unsigned int     sata_func_exist_0:1;
unsigned int     rstn_sata_phy_pow_0:1;
unsigned int     rstn_usb_phy1:1;
unsigned int     rstn_usb_phy0:1;
unsigned int     rstn_sata_phy_0:1;
unsigned int     rstn_usb:1;
unsigned int     rstn_sata_0:1;
unsigned int     rstn_usb3_p0_mdio:1;
unsigned int     rstn_gspi:1;
unsigned int     rstn_usb3_phy0_pow:1;
unsigned int     rstn_nat:1;
unsigned int     rstn_misc:1;
}SYS_SOFT_RESET1;

typedef struct 
{
unsigned int     rstn_sds_phy:1;
unsigned int     rstn_cbus_tx:1;
unsigned int     rstn_misc_sc:1;
unsigned int     rstn_ur1:1;
unsigned int     rstn_ur2:1;
unsigned int     rstn_i2c_1:1;
unsigned int     rstn_i2c_2:1;
unsigned int     rstn_i2c_3:1;
unsigned int     rstn_i2c_4:1;
unsigned int     rstn_pcie1_nonstich:1;
unsigned int     rstn_pcie1_power:1;
unsigned int     rstn_pcie1_core:1;
unsigned int     rstn_pcie1_stitch:1;
unsigned int     rstn_i2c_5:1;
unsigned int     rstn_pcie1:1;
unsigned int     rstn_pcie1_phy:1;
unsigned int     rstn_pcie0_nonstich:1;
unsigned int     rstn_pcie0_power:1;
unsigned int     rstn_pcie0_core:1;
unsigned int     rstn_sdio:1;
unsigned int     rstn_emmc:1;
unsigned int     rstn_cr:1;
unsigned int     rstn_pcr_cnt:1;
unsigned int     rstn_pcie0:1;
unsigned int     rstn_pcie0_phy:1;
unsigned int     rstn_pcie0_stitch:1;
unsigned int     rstn_usb3_p1_mdio:1;
unsigned int     rstn_usb3_phy1_pow:1;
unsigned int     rstn_usb_phy2:1;
unsigned int     rstn_usb_phy3:1;
unsigned int     rstn_jpeg:1;
unsigned int     rstn_acpu:1;
}SYS_SOFT_RESET2;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     rstn_sb2:1;
}SYS_SOFT_RESET3;

typedef struct 
{
unsigned int     clk_en_sd_ip:1;
unsigned int     clk_en_sdio:1;
unsigned int     clk_en_ve3:1;
unsigned int     clk_en_emmc_ip:1;
unsigned int     clk_en_mipi:1;
unsigned int     clk_en_sdio_ip:1;
unsigned int     clk_en_cr:1;
unsigned int     clk_en_emmc:1;
unsigned int     clk_en_nf:1;
unsigned int     clk_en_rsa:1;
unsigned int     clk_en_tp:1;
unsigned int     clk_en_md:1;
unsigned int     clk_en_cp:1;
unsigned int     clk_en_dcu:1;
unsigned int     clk_en_se:1;
unsigned int     clk_en_lvds:1;
unsigned int     clk_en_vo:1;
unsigned int     clk_en_tve:1;
unsigned int     clk_en_ve2:1;
unsigned int     clk_en_ve1:1;
unsigned int     clk_en_gpu:1;
unsigned int     clk_en_aio:1;
unsigned int     clk_en_etn:1;
unsigned int     clk_en_hdmi:1;
unsigned int     clk_en_sata_alive_0:1;
unsigned int     clk_en_iso_misc:1;
unsigned int     clk_en_pcr:1;
unsigned int     clk_en_usb:1;
unsigned int     clk_en_gspi:1;
unsigned int     clk_en_sata_0:1;
unsigned int     clk_en_pcie0:1;
unsigned int     clk_en_misc:1;
}SYS_CLOCK_ENABLE1;

typedef struct 
{
unsigned int     clk_en_dcphy_1:1;
unsigned int     clk_en_dcphy_0:1;
unsigned int     clk_en_fan:1;
unsigned int     clk_en_ur1:1;
unsigned int     clk_en_ur2:1;
unsigned int     clk_en_sata_alive_1:1;
unsigned int     clk_en_sata_1:1;
unsigned int     clk_en_hdmirx:1;
unsigned int     clk_en_aio_mclk:1;
unsigned int     clk_en_aio_i2s:1;
unsigned int     clk_en_aio_spdif:1;
unsigned int     clk_en_aio_hdmi:1;
unsigned int     clk_en_aio_da:1;
unsigned int     clk_en_aio_mod:1;
unsigned int     clk_en_aio_au_codec:1;
unsigned int     clk_en_misc_i2c_1:1;
unsigned int     clk_en_misc_i2c_2:1;
unsigned int     clk_en_misc_i2c_3:1;
unsigned int     clk_en_misc_i2c_4:1;
unsigned int     reserved_0:1;
unsigned int     reserved_1:1;
unsigned int     clk_en_misc_rtc:1;
unsigned int     reserved_2:2;
unsigned int     clk_en_cbus_tx:1;
unsigned int     clk_en_misc_sc:1;
unsigned int     clk_en_pcie1:1;
unsigned int     clk_en_acpu:1;
unsigned int     clk_en_jpeg:1;
unsigned int     clk_en_scpu:1;
unsigned int     clk_en_misc_i2c_5:1;
unsigned int     clk_en_nat:1;
}SYS_CLOCK_ENABLE2;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     reserved_group1_ck_en:1;
}SYS_GROUP1_CK_EN;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     scpu_sclk_sel:1;
unsigned int     sclk_sel_sysh:1;
unsigned int     sclk_sel:1;
}SYS_GROUP1_CK_SEL;

typedef struct 
{
unsigned int     reserved_0:19;
unsigned int     write_en5:1;
unsigned int     clk_tve_p_vo_clk_sel2:1;
unsigned int     write_en4:1;
unsigned int     clk_tve_p_vo_clk_sel:1;
unsigned int     write_en3:1;
unsigned int     hdmi_phy_ckinv:1;
unsigned int     write_en2:1;
unsigned int     reserved_1:2;
unsigned int     dac2_ckinv:1;
unsigned int     dac1_ckinv:1;
unsigned int     write_en1:1;
unsigned int     tveck_mix_sel:1;
}SYS_TVE_CK_SEL;

typedef struct 
{
unsigned int     reserved_0:20;
unsigned int     write_en2:1;
unsigned int     dac2_div:5;
unsigned int     write_en1:1;
unsigned int     dac1_div:5;
}SYS_DISP_PLL_DIV;

typedef struct 
{
unsigned int     reserved_0:5;
unsigned int     write_en11:1;
unsigned int     sel_prefifo_din:1;
unsigned int     write_en10:1;
unsigned int     sel_pllhdmi_mhl:1;
unsigned int     write_en9:1;
unsigned int     clk_lvds_sel:5;
unsigned int     write_en8:1;
unsigned int     sel_plldisp_clk2:1;
unsigned int     write_en7:1;
unsigned int     sel_pllhdmi_clk:1;
unsigned int     write_en6:1;
unsigned int     hdmi_pxl_repeat:1;
unsigned int     write_en5:1;
unsigned int     hdmi_phy_clk_sel:1;
unsigned int     write_en4:1;
unsigned int     hdmi_div:3;
unsigned int     write_en3:1;
unsigned int     tve_div:4;
}SYS_DISP_PLL_DIV2;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     nat_clk_sel:1;
unsigned int     dds_clk_sel:1;
}SYS_DDS_VIDEO_CK_SEL;

typedef struct 
{
unsigned int     reserved_0:26;
unsigned int     mipi_div:2;
unsigned int     vo_div:2;
unsigned int     reserved_1:1;
unsigned int     audio_use_sysclk:1;
}SYS_AUDIO_CLK_CTL;

typedef struct 
{
unsigned int     reserved_0:23;
unsigned int     scpu_freq_sel:2;
unsigned int     reserved_1:2;
unsigned int     acpu_freq_sel:2;
unsigned int     reserved_2:2;
unsigned int     bus_freq_sel:1;
}SYS_PLL_DIV;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     emmc_div_sel:2;
unsigned int     reserved_1:6;
unsigned int     cr_div_sel:2;
unsigned int     reserved_2:6;
unsigned int     sdio_div_sel:2;
unsigned int     reserved_3:4;
unsigned int     nf_div_sel:4;
}SYS_NF_CKSEL;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     nds_sc_div:3;
}SYS_NDS_SC_CKSEL;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     ref_bypass_mode_dcphy_1:1;
unsigned int     ref_bypass_mode_dcphy_0:1;
}SYS_DCPHY_CKSEL;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     clk_camera1_sel:2;
unsigned int     clk_camera0_sel:2;
}SYS_MISC_CKSEL;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     CLKTRC_SEL:2;
}SYS_SCPU_CKSEL;

typedef struct 
{
unsigned int     reserved_0:23;
unsigned int     clk_ve2_bpu_sel:3;
unsigned int     clk_ve3_sel:2;
unsigned int     clk_ve2_sel:2;
unsigned int     clk_ve1_sel:2;
}SYS_VE_CKSEL;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     rstn_disp:1;
unsigned int     rstn_pcie1_phy_mdio:1;
unsigned int     rstn_pcie0_phy_mdio:1;
unsigned int     rstn_hdmirx_wrap:1;
unsigned int     rstn_fan:1;
unsigned int     rstn_sata_1:1;
unsigned int     rstn_sata_phy_1:1;
unsigned int     sata_func_exist_1:1;
unsigned int     rstn_sata_phy_pow_1:1;
unsigned int     rstn_cbusrx:1;
unsigned int     rstn_hdmirx:1;
unsigned int     rstn_dcphy_ssc_dig:1;
unsigned int     rstn_dcphy_ldo:1;
unsigned int     rstn_dcphy_ptr:1;
unsigned int     rstn_dcphy_alert_rx:1;
unsigned int     rstn_dcphy_crt:1;
}SYS_SOFT_RESET4;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     mclk_sel:3;
unsigned int     fs:4;
unsigned int     clken:1;
}SYS_AIO_O_PCM_CK_CTL;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     fs:4;
unsigned int     clken:1;
}SYS_AIO_O_RAW_CK_CTL;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     fs:4;
unsigned int     clken:1;
}SYS_AIO_O_RAW2_CK_CTL;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     write_en2:1;
unsigned int     dds_rstn:1;
}SYS_APS_CTL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     mclk_sel:3;
unsigned int     fs:4;
unsigned int     clken:1;
}SYS_AIO_I_PCM_CK_CTL;

typedef struct 
{
unsigned int     reserved_0:11;
unsigned int     REG_LDO18V_SEL:2;
unsigned int     REG_LDO10V_SEL:2;
unsigned int     REG_TESTSEL_PLLA:1;
unsigned int     reserved_1:1;
unsigned int     REG_WD_SET_PLLA:1;
unsigned int     REG_WD_RST_PLLA:1;
unsigned int     REG_SEL_CCO_PLLA:1;
unsigned int     REG_SCPU_DBUG_EN_PLLA:1;
unsigned int     REG_LPF_RS_PLLA:3;
unsigned int     REG_LPF_CS_PLLA:2;
unsigned int     REG_ICP_PLLA:3;
unsigned int     REG_DIV_PREDIV_BPS_PLLA:1;
unsigned int     REG_DIV_PREDIV_SEL_PLLA:2;
}SYS_PLL_SCPU0;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     REG_OEB_PLLA:1;
unsigned int     SCPU_RSTB_PLLA:1;
unsigned int     SCPU_POW_PLLA:1;
}SYS_PLL_SCPU1;

typedef struct 
{
unsigned int     reserved_0:13;
unsigned int     REG_PLLACPU_PDIV:2;
unsigned int     REG_PLLACPU_LPF_RS:3;
unsigned int     REG_PLLACPU_LPF_CS:2;
unsigned int     REG_PLLACPU_ICP:3;
unsigned int     REG_PLLACPU_WDRST:1;
unsigned int     REG_PLLACPU_WDSET:1;
unsigned int     REG_PLLACPU_TESTSEL:1;
unsigned int     REG_PLLACPU_SEL_CCO:1;
unsigned int     REG_PLLACPU_PDIV_BPS:1;
unsigned int     REG_PLLACPU_DBUG_EN:1;
unsigned int     reserved_1:3;
}SYS_PLL_ACPU1;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     REG_PLLACPU_OEB:1;
unsigned int     REG_PLLACPU_RSTB:1;
unsigned int     REG_PLLACPU_POW:1;
}SYS_PLL_ACPU2;

typedef struct 
{
unsigned int     reserved_0:9;
unsigned int     REG_PLLVCPU_WDRST:1;
unsigned int     REG_PLLVCPU_WDSET:1;
unsigned int     REG_PLLVCPU_CS:2;
unsigned int     REG_PLLVCPU_O:2;
unsigned int     REG_PLLVCPU_RS:3;
unsigned int     REG_PLLVCPU_N:2;
unsigned int     REG_PLLVCPU_M:8;
unsigned int     REG_PLLVCPU_IP:3;
unsigned int     REG_PLLVCPU_TST:1;
}SYS_PLL_VE1_1;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     REG_PLLVCPU_OEB:1;
unsigned int     REG_PLLVCPU_RSTB:1;
unsigned int     REG_PLLVCPU_POW:1;
}SYS_PLL_VE1_2;

typedef struct 
{
unsigned int     reserved_0:7;
unsigned int     REG_PLLDDSA_WDMODE:2;
unsigned int     REG_PLLDDSA_RS:3;
unsigned int     REG_PLLDDSA_O:2;
unsigned int     REG_PLLDDSA_N:2;
unsigned int     REG_PLLDDSA_IP:4;
unsigned int     REG_PLLDDSA_CS:2;
unsigned int     REG_PLLDDSA_CP:2;
unsigned int     REG_PLLDDSA_VCORB:1;
unsigned int     REG_PLLDDSA_TST:1;
unsigned int     REG_PLLDDSA_PSTST:1;
unsigned int     reserved_1:5;
}SYS_PLL_DDSA1;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     REG_PLLDDSA_OEB:1;
unsigned int     REG_PLLDDSA_RSTB:1;
unsigned int     REG_PLLDDSA_POW:1;
}SYS_PLL_DDSA2;

typedef struct 
{
unsigned int     reserved_0:3;
unsigned int     write_en11:1;
unsigned int     psaud_1a_phase_sel:1;
unsigned int     psaud_2a_phase_sel:1;
unsigned int     write_en10:1;
unsigned int     pcr_a_smooth_en:1;
unsigned int     write_en9:1;
unsigned int     pcr_a_phase_sel:1;
unsigned int     write_en8:1;
unsigned int     pcr_a_ctl_en:1;
unsigned int     reserved_1:9;
unsigned int     write_en3:1;
unsigned int     REG_PSAUD1A_FUPDN:1;
unsigned int     REG_PSAUD1A_DIV:1;
unsigned int     write_en2:1;
unsigned int     REG_PSAUD1A_TST:1;
unsigned int     REG_PSAUD1A_PSEN:1;
unsigned int     write_en1:1;
unsigned int     REG_PSAUD2A_FUPDN:1;
unsigned int     REG_PSAUD2A_DIV:1;
unsigned int     REG_PSAUD2A_TST:1;
unsigned int     REG_PSAUD2A_PSEN:1;
}SYS_PLL_PSAUDA1;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     REG_PSAUD1A_OEB:1;
unsigned int     REG_PSAUD1A_RSTB:1;
unsigned int     REG_PSAUD2A_OEB:1;
unsigned int     REG_PSAUD2A_RSTB:1;
}SYS_PLL_PSAUDA2;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     reserved_pll_disp_hd1:1;
}SYS_PLL_DISP_HD1;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     reserved_pll_disp_hd2:1;
}SYS_PLL_DISP_HD2;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     REG_PLLTST_POW:1;
unsigned int     reserved_1:4;
}SYS_PLL1_TEST;

typedef struct 
{
unsigned int     reserved_0:5;
unsigned int     REG_PLLBUS_RESER:8;
unsigned int     REG_PLLBUS_PDIV:2;
unsigned int     REG_PLLBUS_LPF_RS:3;
unsigned int     REG_PLLBUS_LPF_CS:2;
unsigned int     REG_PLLBUS_ICP:3;
unsigned int     REG_PLLBUS_WDSET:1;
unsigned int     REG_PLLBUS_WDRST:1;
unsigned int     REG_PLLBUS_TESTSEL:1;
unsigned int     REG_PLLBUS_SEL_CCO:1;
unsigned int     REG_PLLBUS_PDIV_BPS:1;
unsigned int     REG_PLLBUS_DBUG_EN:1;
unsigned int     reserved_1:3;
}SYS_PLL_BUS1;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     REG_PLLBUS_OEB:1;
unsigned int     REG_PLLBUS_RSTB:1;
unsigned int     REG_PLLBUS_POW:1;
}SYS_PLL_BUS2;

typedef struct 
{
unsigned int     reserved_0:17;
unsigned int     REG_EDPPLL_WDO:1;
unsigned int     REG_PIXELPLL_WDO:1;
unsigned int     REG_PLLGPU_WDOUT:1;
unsigned int     reserved_1:1;
unsigned int     REG_PLLBUS_WDOUT_H:1;
unsigned int     reserved_2:1;
unsigned int     REG_PLLVODMA_WDOUT:1;
unsigned int     REG_PLLVCPU_WDOUT_2:1;
unsigned int     REG_PLLBUS_WDOUT:1;
unsigned int     reserved_3:1;
unsigned int     REG_PLLDDSB_WDOUT:1;
unsigned int     REG_PLLDDSA_WDOUT:1;
unsigned int     REG_PLLVCPU_WDOUT:1;
unsigned int     REG_PLLACPU_WDOUT:1;
unsigned int     reserved_4:1;
}SYS_PLL_WDOUT;

typedef struct 
{
unsigned int     reserved_0:7;
unsigned int     REG_PLLDDSB_WDMODE:2;
unsigned int     REG_PLLDDSB_RS:3;
unsigned int     REG_PLLDDSB_O:2;
unsigned int     REG_PLLDDSB_N:2;
unsigned int     REG_PLLDDSB_IP:4;
unsigned int     REG_PLLDDSB_CS:2;
unsigned int     REG_PLLDDSB_CP:2;
unsigned int     REG_PLLDDSB_VCORB:1;
unsigned int     REG_PLLDDSB_TST:1;
unsigned int     REG_PLLDDSB_PSTST:1;
unsigned int     reserved_1:5;
}SYS_PLL_DDSB1;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     REG_PLLDDSB_OEB:1;
unsigned int     REG_PLLDDSB_RSTB:1;
unsigned int     REG_PLLDDSB_POW:1;
}SYS_PLL_DDSB2;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     write_en10:1;
unsigned int     pcr_b_smooth_en:1;
unsigned int     write_en9:1;
unsigned int     pcr_b_phase_sel:1;
unsigned int     write_en8:1;
unsigned int     pcr_b_ctl_en:1;
unsigned int     reserved_1:9;
unsigned int     write_en3:1;
unsigned int     REG_PSAUD1B_FUPDN:1;
unsigned int     REG_PSAUD1B_DIV:1;
unsigned int     write_en2:1;
unsigned int     REG_PSAUD1B_TST:1;
unsigned int     REG_PSAUD1B_PSEN:1;
unsigned int     write_en1:1;
unsigned int     REG_PSAUD2B_FUPDN:1;
unsigned int     REG_PSAUD2B_DIV:1;
unsigned int     REG_PSAUD2B_TST:1;
unsigned int     REG_PSAUD2B_PSEN:1;
}SYS_PLL_PSAUDB1;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     REG_PSAUD1B_OEB:1;
unsigned int     REG_PSAUD1B_RSTB:1;
unsigned int     REG_PSAUD2B_OEB:1;
unsigned int     REG_PSAUD2B_RSTB:1;
}SYS_PLL_PSAUDB2;

typedef struct 
{
unsigned int     reserved_0:23;
unsigned int     PLLDISP_OEB:1;
unsigned int     PLLDISP_VCORSTB:1;
unsigned int     REG_PLL_MHL3_DIV_EN:1;
unsigned int     REG_PLLDISP_RSTB:1;
unsigned int     REG_PLLDISP_POW:1;
unsigned int     REG_TMDS_POW:1;
unsigned int     REG_PLL_RSTB:1;
unsigned int     REG_PLL_POW:1;
unsigned int     REG_HDMI_CK_EN:1;
}SYS_PLL_HDMI;

typedef struct 
{
unsigned int     reserved_0:9;
unsigned int     REG_ICO_PDIV2:3;
unsigned int     REG_TMDS_DIV:4;
unsigned int     REG_PLLDISP_N:2;
unsigned int     REG_PLLDISP_K:2;
unsigned int     REG_PIXEL_DIV:8;
unsigned int     REG_PLL_M2:2;
unsigned int     REG_PLL_M1:2;
}SYS_PLL_HDMI2;

typedef struct 
{
unsigned int     reserved_0:19;
unsigned int     phsel1:5;
unsigned int     phsel0:5;
unsigned int     phrstb_dly_sel:1;
unsigned int     phrt0:1;
unsigned int     bias_en:1;
}SYS_PLL_SDIO1;

typedef struct 
{
unsigned int     reserved_0:5;
unsigned int     en_cpnew:1;
unsigned int     ssc_div_ext_f:8;
unsigned int     ssc_div_f_sel:1;
unsigned int     ssc_8x_en:1;
unsigned int     ssc_depth:3;
unsigned int     sscpll_rs:3;
unsigned int     sscpll_icp:5;
unsigned int     sscpll_cs1:2;
unsigned int     reg_tune11:2;
unsigned int     sscldo_en:1;
}SYS_PLL_SDIO2;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     ssc_div_n:10;
unsigned int     reserved_1:1;
unsigned int     ssc_step_in:7;
unsigned int     ssc_tbase:8;
}SYS_PLL_SDIO3;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     ssc_pll_pow:1;
unsigned int     ssc_pll_rstb:1;
unsigned int     ssc_rstb:1;
}SYS_PLL_SDIO4;

typedef struct 
{
unsigned int     reserved_0:13;
unsigned int     REG_PLLBUS_PDIV_H:2;
unsigned int     REG_PLLBUS_LPF_RS_H:3;
unsigned int     REG_PLLBUS_LPF_CS_H:2;
unsigned int     REG_PLLBUS_ICP_H:3;
unsigned int     REG_PLLBUS_WDSET_H:1;
unsigned int     REG_PLLBUS_WDRST_H:1;
unsigned int     REG_PLLBUS_TESTSEL_H:1;
unsigned int     REG_PLLBUS_SEL_CCO_H:1;
unsigned int     REG_PLLBUS_PDIV_BPS_H:1;
unsigned int     REG_PLLBUS_DBUG_EN_H:1;
unsigned int     reserved_1:3;
}SYS_PLL_BUSH1;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     REG_PLLBUS_OEB_H:1;
unsigned int     REG_PLLBUS_RSTB_H:1;
unsigned int     REG_PLLBUS_POW_H:1;
}SYS_PLL_BUSH2;

typedef struct 
{
unsigned int     reserved_0:13;
unsigned int     REG_PLLGPU_PDIV:2;
unsigned int     REG_PLLGPU_LPF_RS:3;
unsigned int     REG_PLLGPU_LPF_CS:2;
unsigned int     REG_PLLGPU_ICP:3;
unsigned int     REG_PLLGPU_WDRST:1;
unsigned int     REG_PLLGPU_WDSET:1;
unsigned int     REG_PLLGPU_TESTSEL:1;
unsigned int     REG_PLLGPU_SEL_CCO:1;
unsigned int     REG_PLLGPU_PDIV_BPS:1;
unsigned int     REG_PLLGPU_DBUG_EN:1;
unsigned int     reserved_1:3;
}SYS_PLL_GPU1;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     REG_PLLGPU_OEB:1;
unsigned int     REG_PLLGPU_RSTB:1;
unsigned int     REG_PLLGPU_POW:1;
}SYS_PLL_GPU2;

typedef struct 
{
unsigned int     reserved_0:9;
unsigned int     REG_PLLVCPU_WDRST_2:1;
unsigned int     REG_PLLVCPU_WDSET_2:1;
unsigned int     REG_PLLVCPU_CS_2:2;
unsigned int     REG_PLLVCPU_O_2:2;
unsigned int     REG_PLLVCPU_RS_2:3;
unsigned int     REG_PLLVCPU_N_2:2;
unsigned int     REG_PLLVCPU_M_2:8;
unsigned int     REG_PLLVCPU_IP_2:3;
unsigned int     REG_PLLVCPU_TST_2:1;
}SYS_PLL_VE2_1;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     REG_PLLVCPU_OEB_2:1;
unsigned int     REG_PLLVCPU_RSTB_2:1;
unsigned int     REG_PLLVCPU_POW_2:1;
}SYS_PLL_VE2_2;

typedef struct 
{
unsigned int     reserved_0:17;
unsigned int     reg_sel3318:2;
unsigned int     phsel1:5;
unsigned int     phsel0:5;
unsigned int     phrstb_dly_sel:1;
unsigned int     phrt0:1;
unsigned int     bias_en:1;
}SYS_PLL_SD1;

typedef struct 
{
unsigned int     reserved_0:5;
unsigned int     en_cpnew:1;
unsigned int     ssc_div_ext_f:8;
unsigned int     ssc_div_f_sel:1;
unsigned int     ssc_8x_en:1;
unsigned int     ssc_depth:3;
unsigned int     sscpll_rs:3;
unsigned int     sscpll_icp:5;
unsigned int     sscpll_cs1:2;
unsigned int     reg_tune11:2;
unsigned int     sscldo_en:1;
}SYS_PLL_SD2;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     ssc_div_n:10;
unsigned int     reserved_1:1;
unsigned int     ssc_step_in:7;
unsigned int     ssc_tbase:8;
}SYS_PLL_SD3;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     ssc_pll_pow:1;
unsigned int     ssc_pll_rstb:1;
unsigned int     ssc_rstb:1;
}SYS_PLL_SD4;

typedef struct 
{
unsigned int     reserved_0:19;
unsigned int     phsel1:5;
unsigned int     phsel0:5;
unsigned int     phrstb_dly_sel:1;
unsigned int     phrt0:1;
unsigned int     bias_en:1;
}SYS_PLL_EMMC1;

typedef struct 
{
unsigned int     reserved_0:5;
unsigned int     en_cpnew:1;
unsigned int     ssc_div_ext_f:8;
unsigned int     ssc_div_f_sel:1;
unsigned int     ssc_8x_en:1;
unsigned int     ssc_depth:3;
unsigned int     sscpll_rs:3;
unsigned int     sscpll_icp:5;
unsigned int     sscpll_cs1:2;
unsigned int     reg_tune11:2;
unsigned int     sscldo_en:1;
}SYS_PLL_EMMC2;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     ssc_div_n:10;
unsigned int     reserved_1:1;
unsigned int     ssc_step_in:7;
unsigned int     ssc_tbase:8;
}SYS_PLL_EMMC3;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     ssc_pll_pow:1;
unsigned int     ssc_pll_rstb:1;
unsigned int     ssc_rstb:1;
}SYS_PLL_EMMC4;

typedef struct 
{
unsigned int     reserved_0:18;
unsigned int     REG_TEST_SEL:2;
unsigned int     POR_VSET:1;
unsigned int     REG_PLLDDSB_CKIN_SEL:1;
unsigned int     REG_PLLDISP_SEL:2;
unsigned int     REG_HDMITX_27M_SEL:2;
unsigned int     REG_PLLGPU_BYPASS_PI:1;
unsigned int     REG_PLLDDSB_BYPASS_PI:1;
unsigned int     REG_PLLDDSA_BYPASS_PI:1;
unsigned int     REG_PLLBUS_BYPASS_PI_H:1;
unsigned int     REG_PLLBUS_BYPASS_PI:1;
unsigned int     REG_PLLACPU_BYPASS_PI:1;
}SYS_PLL_OTHER;

typedef struct 
{
unsigned int     time_rdy_ckout:2;
unsigned int     time2_rst_width:2;
unsigned int     pcr_rst_n:1;
unsigned int     time0_ck:3;
unsigned int     f390k:2;
unsigned int     pll_en:1;
unsigned int     en_wdog:1;
unsigned int     ssc_ckinv:1;
unsigned int     fcode:11;
unsigned int     ncode:8;
}SYS_PLL_HDMI_SD1;

typedef struct 
{
unsigned int     bypass_pi:1;
unsigned int     en_pi_debug:1;
unsigned int     hs_oc_stop_diff:2;
unsigned int     reserved_0:2;
unsigned int     sel_oc_mode:2;
unsigned int     reserved_1:2;
unsigned int     oc_done_delay:6;
unsigned int     reserved_2:1;
unsigned int     pi_cur_sel:3;
unsigned int     oc_step_set:10;
unsigned int     sdm_order:1;
unsigned int     oc_en:1;
}SYS_PLL_HDMI_SD2;

typedef struct 
{
unsigned int     load_fcw:1;
unsigned int     reserved_0:3;
unsigned int     fmod:1;
unsigned int     fcode_debug:11;
unsigned int     ncode_debug:8;
unsigned int     reserved_1:6;
unsigned int     clkrdy:1;
unsigned int     oc_done:1;
}SYS_PLL_HDMI_SD3;

typedef struct 
{
unsigned int     reserved_0:12;
unsigned int     ssc_en:1;
unsigned int     fcode_ssc:11;
unsigned int     ncode_ssc:8;
}SYS_PLL_HDMI_SD4;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     RSTB_HDMITX:1;
unsigned int     gran_auto_rst:1;
unsigned int     dot_gran:3;
unsigned int     gran_est:19;
}SYS_PLL_HDMI_SD5;

typedef struct 
{
unsigned int     REG_PLL_RESERVED:8;
unsigned int     reserved_0:13;
unsigned int     REG_LDO2V_SEL:2;
unsigned int     REG_LDO2V_POW:1;
unsigned int     reserved_1:8;
}SYS_BG_CTL;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     POR_VDD_D10_OVER:1;
}SYS_POR_DET;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     REG_BYPASS_PI:1;
unsigned int     REG_P2S_LDO_SEL:2;
unsigned int     REG_P2S_MODE:2;
unsigned int     REG_TSPC_SEL:1;
unsigned int     REG_MHL_MODE:1;
unsigned int     REG_HDMI_MODE:1;
unsigned int     REG_HDMICK_SEL:1;
unsigned int     REG_PLL_TST_POW:1;
unsigned int     REG_PLL_LDO_V18_SEL:2;
unsigned int     REG_PLL_LDO_LV_SEL:2;
unsigned int     REG_TST_DIV:3;
unsigned int     REG_PLL_RS:3;
unsigned int     REG_PLL_WDSET:1;
unsigned int     REG_PLL_WDRST:1;
unsigned int     REG_PLL_VCOGAIN:1;
unsigned int     REG_PLL_EXT_LDO_LV:1;
unsigned int     REG_PLL_CKSEL:2;
unsigned int     REG_PLL_CS:2;
unsigned int     REG_PLL_CP:2;
}SYS_PLL_HDMI_LDO1;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     REG_TMDS_RSELCK:2;
unsigned int     REG_TMDS_RSELC:2;
unsigned int     REG_TMDS_RSELB:2;
unsigned int     REG_TMDS_RSELA:2;
unsigned int     REG_TMDS_CSELCK:2;
unsigned int     REG_TMDS_CSELC:2;
unsigned int     REG_TMDS_CSELB:2;
unsigned int     REG_TMDS_CSELA:2;
unsigned int     REG_TMDS_POWMHLCK_B:1;
unsigned int     REG_TMDS_POWMHLCK_A:1;
unsigned int     REG_TMDS_POWCK:1;
unsigned int     REG_TMDS_POWC:1;
unsigned int     REG_TMDS_POWB:1;
unsigned int     REG_TMDS_POWA:1;
unsigned int     REG_TMDS_EMCK:1;
unsigned int     REG_TMDS_EMC:1;
unsigned int     REG_TMDS_EMB:1;
unsigned int     REG_TMDS_EMA:1;
}SYS_PLL_HDMI_LDO2;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     REG_PLL_CKIN_SEL:2;
unsigned int     REG_PLL_TSPC_SEL:1;
unsigned int     REG_PCR_27M_SEL:1;
unsigned int     REG_TMDS_IDRVCK:3;
unsigned int     REG_TMDS_IDRVC:3;
unsigned int     REG_TMDS_IDRVB:3;
unsigned int     REG_TMDS_IDRVA:3;
unsigned int     REG_TMDS_SRMHLCK:2;
unsigned int     REG_TMDS_SRCK:2;
unsigned int     REG_TMDS_SRC:2;
unsigned int     REG_TMDS_SRB:2;
unsigned int     REG_TMDS_SRA:2;
}SYS_PLL_HDMI_LDO3;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     REG_PLLDISP_DDSEN:1;
unsigned int     REG_PLLDISP_CS:2;
unsigned int     REG_PLLDISP_CP:2;
unsigned int     REG_PLLDISP_C3:2;
unsigned int     REG_TEST_LDO_SEL:2;
unsigned int     REG_TESTSIG_SEL:2;
unsigned int     REG_PLL_IP:4;
unsigned int     REG_TMDS_IMHLCK:3;
unsigned int     REG_TMDS_IEMCK:3;
unsigned int     REG_TMDS_IEMC:3;
unsigned int     REG_TMDS_IEMB:3;
unsigned int     REG_TMDS_IEMA:3;
}SYS_PLL_HDMI_LDO4;

typedef struct 
{
unsigned int     REG_HDMITX_RESERVE:16;
unsigned int     REG_PLLDISP_LDOSEL:2;
unsigned int     REG_PLLDISP_SSC_ENL:1;
unsigned int     REG_PLLDISP_WDMODE:2;
unsigned int     REG_PLLDISP_RS:3;
unsigned int     REG_PLLDISP_R3:3;
unsigned int     REG_PLLDISP_PSTST:1;
unsigned int     REG_PLLDISP_IP:4;
}SYS_PLL_HDMI_LDO5;

typedef struct 
{
unsigned int     REG_EDPPLL_LDOPOW:1;
unsigned int     reserved_0:1;
unsigned int     REG_EDPPLL_LDOSEL:2;
unsigned int     REG_EDPPLL_LDOV10POW:1;
unsigned int     reserved_1:1;
unsigned int     REG_EDPPLL_LDOV10SEL:2;
unsigned int     reserved_2:2;
unsigned int     REG_EDPPLL_CS:2;
unsigned int     reserved_3:1;
unsigned int     REG_EDPPLL_RS:3;
unsigned int     REG_EDPPLL_CP:1;
unsigned int     REG_EDPPLL_IP:3;
unsigned int     REG_EDPPLL_DIV10X:1;
unsigned int     reserved_4:1;
unsigned int     REG_EDPPLL_WDRST:1;
unsigned int     REG_EDPPLL_WDSET:1;
unsigned int     REG_EDPPLL_N:2;
unsigned int     REG_EDPPLL_DIV_P:2;
unsigned int     REG_EDPPLL_TEST:1;
unsigned int     REG_EDPPLL_INCF:1;
unsigned int     REG_EDPPLL_PI_BPS:1;
unsigned int     REG_BIAS_POW:1;
}SYS_PLL_EDP1;

typedef struct 
{
unsigned int     reserved_0:22;
unsigned int     REG_EDPPLL_RESERVED:8;
unsigned int     REG_EDPPLL_RSTB:1;
unsigned int     REG_EDPPLL_POW:1;
}SYS_PLL_EDP2;

typedef struct 
{
unsigned int     REG_PIXELPLL_LDOPOW:1;
unsigned int     reserved_0:1;
unsigned int     REG_PIXELPLL_LDOSEL:2;
unsigned int     reserved_1:1;
unsigned int     REG_PIXELPLL_RS:3;
unsigned int     reserved_2:1;
unsigned int     REG_PIXELPLL_IP:3;
unsigned int     REG_PIXELPLL_CP:2;
unsigned int     REG_PIXELPLL_CS:2;
unsigned int     reserved_3:1;
unsigned int     REG_PIXELPLL_RSTB:1;
unsigned int     REG_PIXELPLL_WDRST:1;
unsigned int     REG_PIXELPLL_WDSET:1;
unsigned int     REG_PIXELPLL_BPSIN:1;
unsigned int     REG_PIXELPLL_N:3;
unsigned int     REG_PIXELPLL_VCORSTB:1;
unsigned int     reserved_4:1;
unsigned int     REG_PIXELPLL_O:2;
unsigned int     REG_PIXELPLL_TEST:1;
unsigned int     REG_PIXELPLL_FREEZE:1;
unsigned int     REG_PIXELPLL_BPSPI:1;
unsigned int     reserved_5:1;
}SYS_PLL_PIXEL1;

typedef struct 
{
unsigned int     reserved_0:19;
unsigned int     REG_PIXELPLL_RESER:4;
unsigned int     REG_PIXELPLL_RESERVED:8;
unsigned int     REG_PIXELPLL_POW:1;
}SYS_PLL_PIXEL2;

typedef struct 
{
unsigned int     reserved_0:9;
unsigned int     REG_PLLVODMA_WDRST:1;
unsigned int     REG_PLLVODMA_WDSET:1;
unsigned int     REG_PLLVODMA_CS:2;
unsigned int     REG_PLLVODMA_O:2;
unsigned int     REG_PLLVODMA_RS:3;
unsigned int     REG_PLLVODMA_N:2;
unsigned int     REG_PLLVODMA_M:8;
unsigned int     REG_PLLVODMA_IP:3;
unsigned int     REG_PLLVODMA_TST:1;
}SYS_PLL_VODMA1;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     REG_PLLVODMA_OEB:1;
unsigned int     REG_PLLVODMA_RSTB:1;
unsigned int     REG_PLLVODMA_POW:1;
}SYS_PLL_VODMA2;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     testmode:1;
unsigned int     nf_sel:1;
unsigned int     boot_sel:1;
}SYS_CHIP_INFO2;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     reserved_scpu_l2:1;
}SYS_SCPU_L2;

typedef struct 
{
unsigned int     scpu_boot_info:32;
}SYS_PWDN_CTRL;

typedef struct 
{
unsigned int     acpu_boot_info:32;
}SYS_PWDN_CTRL2;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     write_en2:1;
unsigned int     scpu_boot_info_valid:1;
unsigned int     write_en1:1;
unsigned int     scpu_sw_rst:1;
}SYS_PWDN_CTRL3;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     acpu_boot_info_valid:1;
}SYS_PWDN_CTRL4;

typedef struct 
{
unsigned int     reserved_0:26;
unsigned int     write_en3:1;
unsigned int     hdmirx_at_speed_pll_done:1;
unsigned int     write_en2:1;
unsigned int     dac_test:1;
unsigned int     write_en1:1;
unsigned int     scpu_config_done:1;
}SYS_AT_SPEED;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     reserved_ana_ctrl:1;
}SYS_ANA_CTRL;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     reserved_tp_demod_ctrl:1;
}SYS_TP_DEMOD_CTRL;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     reserved_phy_func:1;
}SYS_PHY_FUNC;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     analogy_mode_sel:4;
}SYS_ANLG;

typedef struct 
{
unsigned int     reserved_0:22;
unsigned int     REG_TEST_EN:1;
unsigned int     REG_PLLTST_EN:1;
unsigned int     REG_PLLTST_DIV32:1;
unsigned int     REG_PLLTST_DIV16:1;
unsigned int     REG_PLLTST_SEL:4;
unsigned int     REG_PLLTST_DIV:2;
}SYS_PLL_TEST1;

typedef struct 
{
unsigned int     reserved_0:21;
unsigned int     REG_VDDMUX_SEL:1;
unsigned int     REG_VDD_MUX1:4;
unsigned int     REG_VDD_MUX2:4;
unsigned int     REG_VDDMUX_EN:1;
unsigned int     REG_TEST_OUT_EN:1;
}SYS_LSADC_PG;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     scan_occ_chain_sel:1;
}SYS_SCAN_CTRL;

typedef struct 
{
unsigned int     L2H_DELAY_CYCLE:32;
}SYS_DISP_SRAM_PWR0;

typedef struct 
{
unsigned int     H2L_DELAY_CYCLE:32;
}SYS_DISP_SRAM_PWR1;

typedef struct 
{
unsigned int     SD_REG:32;
}SYS_DISP_SRAM_PWR2;

typedef struct 
{
unsigned int     MUX_REG:32;
}SYS_DISP_SRAM_PWR3;

typedef struct 
{
unsigned int     CTRL:32;
}SYS_DISP_SRAM_PWR4;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     disp_sram_int:1;
unsigned int     reserved_1:1;
unsigned int     write_data:1;
}SYS_DISP_SRAM_PWR5;

typedef struct 
{
unsigned int     last_delay_cycle:32;
}SYS_DISP_SRAM_PWR6;

typedef struct 
{
unsigned int     pg_switch_info:32;
}SYS_DISP_SRAM_PWR7;

typedef struct 
{
unsigned int     L2H_DELAY_CYCLE:32;
}SYS_VE1_SRAM_PWR0;

typedef struct 
{
unsigned int     H2L_DELAY_CYCLE:32;
}SYS_VE1_SRAM_PWR1;

typedef struct 
{
unsigned int     SD_REG:32;
}SYS_VE1_SRAM_PWR2;

typedef struct 
{
unsigned int     MUX_REG:32;
}SYS_VE1_SRAM_PWR3;

typedef struct 
{
unsigned int     CTRL:32;
}SYS_VE1_SRAM_PWR4;

typedef struct 
{
unsigned int     L2H_DELAY_CYCLE:32;
}SYS_GPU_SRAM_PWR0;

typedef struct 
{
unsigned int     H2L_DELAY_CYCLE:32;
}SYS_GPU_SRAM_PWR1;

typedef struct 
{
unsigned int     SD_REG:32;
}SYS_GPU_SRAM_PWR2;

typedef struct 
{
unsigned int     MUX_REG:32;
}SYS_GPU_SRAM_PWR3;

typedef struct 
{
unsigned int     CTRL:32;
}SYS_GPU_SRAM_PWR4;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     ve1_sram_int:1;
unsigned int     reserved_1:1;
unsigned int     write_data:1;
}SYS_VE1_SRAM_PWR5;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     gpu_sram_int:1;
unsigned int     reserved_1:1;
unsigned int     write_data:1;
}SYS_GPU_SRAM_PWR5;

typedef struct 
{
unsigned int     last_delay_cycle:32;
}SYS_VE1_SRAM_PWR6;

typedef struct 
{
unsigned int     last_delay_cycle:32;
}SYS_GPU_SRAM_PWR6;

typedef struct 
{
unsigned int     pg_switch_info:32;
}SYS_VE1_SRAM_PWR7;

typedef struct 
{
unsigned int     pg_switch_info:32;
}SYS_GPU_SRAM_PWR7;

typedef struct 
{
unsigned int     L2H_DELAY_CYCLE:32;
}SYS_VE2_SRAM_PWR0;

typedef struct 
{
unsigned int     H2L_DELAY_CYCLE:32;
}SYS_VE2_SRAM_PWR1;

typedef struct 
{
unsigned int     SD_REG:32;
}SYS_VE2_SRAM_PWR2;

typedef struct 
{
unsigned int     MUX_REG:32;
}SYS_VE2_SRAM_PWR3;

typedef struct 
{
unsigned int     CTRL:32;
}SYS_VE2_SRAM_PWR4;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     ve2_sram_int:1;
unsigned int     reserved_1:1;
unsigned int     write_data:1;
}SYS_VE2_SRAM_PWR5;

typedef struct 
{
unsigned int     last_delay_cycle:32;
}SYS_VE2_SRAM_PWR6;

typedef struct 
{
unsigned int     pg_switch_info:32;
}SYS_VE2_SRAM_PWR7;

typedef struct 
{
unsigned int     L2H_DELAY_CYCLE:32;
}SYS_VE3_SRAM_PWR0;

typedef struct 
{
unsigned int     H2L_DELAY_CYCLE:32;
}SYS_VE3_SRAM_PWR1;

typedef struct 
{
unsigned int     SD_REG:32;
}SYS_VE3_SRAM_PWR2;

typedef struct 
{
unsigned int     MUX_REG:32;
}SYS_VE3_SRAM_PWR3;

typedef struct 
{
unsigned int     CTRL:32;
}SYS_VE3_SRAM_PWR4;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     ve3_sram_int:1;
unsigned int     reserved_1:1;
unsigned int     write_data:1;
}SYS_VE3_SRAM_PWR5;

typedef struct 
{
unsigned int     last_delay_cycle:32;
}SYS_VE3_SRAM_PWR6;

typedef struct 
{
unsigned int     pg_switch_info:32;
}SYS_VE3_SRAM_PWR7;

typedef struct 
{
unsigned int     reserved_0:12;
unsigned int     nat_sram_int_mask:1;
unsigned int     iso_nat:1;
unsigned int     vetop_rm:4;
unsigned int     vetop_rme:1;
unsigned int     vetop_sd:1;
unsigned int     vetop_ds:1;
unsigned int     vetop_ls:1;
unsigned int     disp_sram_int_mask:1;
unsigned int     iso_disp:1;
unsigned int     ve3_sram_int_mask:1;
unsigned int     iso_ve3:1;
unsigned int     ve2_sram_int_mask:1;
unsigned int     iso_ve2:1;
unsigned int     ve1_sram_int_mask:1;
unsigned int     gpu_sram_int_mask:1;
unsigned int     iso_gpu:1;
unsigned int     iso_ve1:1;
}SYS_POWER_CTRL;

typedef struct 
{
unsigned int     reserved_0:17;
unsigned int     vprob_plltest_sel_loc1:5;
unsigned int     vprob_plltest_sel_loc0:5;
unsigned int     vprob_ea_loc1:1;
unsigned int     vprob_ea_loc0:1;
unsigned int     reserved_1:3;
}SYS_PLL_PROB;

typedef struct 
{
unsigned int     reserved_0:23;
unsigned int     crt_dbg_en:1;
unsigned int     crt_dbg_sel0:4;
unsigned int     crt_dbg_sel1:4;
}SYS_CRT_DEBUG;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     reserved_debug:1;
}SYS_DEBUG;

typedef struct 
{
unsigned int     rbus_protect:32;
}SYS_MBIST;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     dvsorting:1;
unsigned int     pcie1_bak_sel:1;
unsigned int     pcie0_bak_sel:1;
unsigned int     plldiv_sel:4;
}SYS_PLLDIV;

typedef struct 
{
unsigned int     L2H_DELAY_CYCLE:32;
}SYS_NAT_SRAM_PWR0;

typedef struct 
{
unsigned int     H2L_DELAY_CYCLE:32;
}SYS_NAT_SRAM_PWR1;

typedef struct 
{
unsigned int     SD_REG:32;
}SYS_NAT_SRAM_PWR2;

typedef struct 
{
unsigned int     MUX_REG:32;
}SYS_NAT_SRAM_PWR3;

typedef struct 
{
unsigned int     CTRL:32;
}SYS_NAT_SRAM_PWR4;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     nat_sram_int:1;
unsigned int     reserved_1:1;
unsigned int     write_data:1;
}SYS_NAT_SRAM_PWR5;

typedef struct 
{
unsigned int     last_delay_cycle:32;
}SYS_NAT_SRAM_PWR6;

typedef struct 
{
unsigned int     pg_switch_info:32;
}SYS_NAT_SRAM_PWR7;

typedef struct 
{
unsigned int     dmyreg0_rst0:32;
}SYS_DUMMY0;

typedef struct 
{
unsigned int     dmyreg1_rst0:32;
}SYS_DUMMY1;

typedef struct 
{
unsigned int     dmyreg2_rst1:32;
}SYS_DUMMY2;

typedef struct 
{
unsigned int     dmyreg3_rst1:32;
}SYS_DUMMY3;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     REG_CKSSC_INV_SCPU:1;
unsigned int     REG_GRAN_AUTO_RST_SCPU:1;
unsigned int     RSTB_SCPU:1;
unsigned int     EN_SSC_SCPU:1;
unsigned int     OC_EN_SCPU:1;
}SYS_PLL_SSC_DIG_SCPU0;

typedef struct 
{
unsigned int     reserved_0:13;
unsigned int     NCODE_T_SCPU:8;
unsigned int     FCODE_T_SCPU:11;
}SYS_PLL_SSC_DIG_SCPU1;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     REG_BYPASS_DIVN:1;
unsigned int     REG_OC_STEP_SET_SCPU:10;
unsigned int     REG_SEL_OC_MODE_SCPU:2;
unsigned int     REG_HS_OC_STOP_DIFF_SCPU:2;
unsigned int     REG_OC_DONE_DELAY_SCPU:6;
unsigned int     REG_PI_CUR_SEL_SCPU:2;
unsigned int     REG_BYPASS_PI_SCPU:1;
unsigned int     REG_SDM_ORDER_SCPU:1;
unsigned int     REG_EN_PI_DEBUG_SCPU:1;
unsigned int     reserved_1:2;
}SYS_PLL_SSC_DIG_SCPU2;

typedef struct 
{
unsigned int     reserved_0:13;
unsigned int     NCODE_SSC_SCPU:8;
unsigned int     FCODE_SSC_SCPU:11;
}SYS_PLL_SSC_DIG_SCPU3;

typedef struct 
{
unsigned int     reserved_0:13;
unsigned int     GRAN_EST_SCPU:19;
}SYS_PLL_SSC_DIG_SCPU4;

typedef struct 
{
unsigned int     reserved_0:13;
unsigned int     FCW_SSC_DEFAULT_SCPU:19;
}SYS_PLL_SSC_DIG_SCPU5;

typedef struct 
{
unsigned int     reserved_0:17;
unsigned int     LOOP_PI_ISEL_SCPU:2;
unsigned int     PHSEL_SCPU:5;
unsigned int     DIVN_SCPU:8;
}SYS_PLL_SSC_DIG_SCPU_DBG1;

typedef struct 
{
unsigned int     reserved_0:10;
unsigned int     load_FCW_SCPU:1;
unsigned int     OC_DONE_SCPU:1;
unsigned int     FMOD_SCPU:1;
unsigned int     NCODE_DEBUG_SCPU:8;
unsigned int     FCODE_DEBUG_SCPU:11;
}SYS_PLL_SSC_DIG_SCPU_DBG2;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     REG_CKSSC_INV_BUS:1;
unsigned int     REG_GRAN_AUTO_RST_BUS:1;
unsigned int     RSTB_BUS:1;
unsigned int     EN_SSC_BUS:1;
unsigned int     OC_EN_BUS:1;
}SYS_PLL_SSC_DIG_BUS0;

typedef struct 
{
unsigned int     reserved_0:13;
unsigned int     NCODE_T_BUS:8;
unsigned int     FCODE_T_BUS:11;
}SYS_PLL_SSC_DIG_BUS1;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     REG_BYPASS_DIVN:1;
unsigned int     REG_OC_STEP_SET_BUS:10;
unsigned int     REG_SEL_OC_MODE_BUS:2;
unsigned int     REG_HS_OC_STOP_DIFF_BUS:2;
unsigned int     REG_OC_DONE_DELAY_BUS:6;
unsigned int     REG_BYPASS_PI_BUS:1;
unsigned int     REG_SDM_ORDER_BUS:1;
unsigned int     REG_PI_CUR_SEL_BUS:3;
unsigned int     REG_EN_PI_DEBUG_BUS:1;
unsigned int     reserved_1:1;
}SYS_PLL_SSC_DIG_BUS2;

typedef struct 
{
unsigned int     reserved_0:13;
unsigned int     NCODE_SSC_BUS:8;
unsigned int     FCODE_SSC_BUS:11;
}SYS_PLL_SSC_DIG_BUS3;

typedef struct 
{
unsigned int     reserved_0:13;
unsigned int     GRAN_EST_BUS:19;
}SYS_PLL_SSC_DIG_BUS4;

typedef struct 
{
unsigned int     reserved_0:13;
unsigned int     FCW_SSC_DEFAULT_BUS:19;
}SYS_PLL_SSC_DIG_BUS5;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     LOOP_PI_ISEL_BUS:3;
unsigned int     PHSEL_BUS:5;
unsigned int     DIVN_BUS:8;
}SYS_PLL_SSC_DIG_BUS_DBG1;

typedef struct 
{
unsigned int     reserved_0:10;
unsigned int     load_FCW_BUS:1;
unsigned int     OC_DONE_BUS:1;
unsigned int     FMOD_BUS:1;
unsigned int     NCODE_DEBUG_BUS:8;
unsigned int     FCODE_DEBUG_BUS:11;
}SYS_PLL_SSC_DIG_BUS_DBG2;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     REG_CKSSC_INV_BUS_H:1;
unsigned int     REG_GRAN_AUTO_RST_BUS_H:1;
unsigned int     RSTB_BUS_H:1;
unsigned int     EN_SSC_BUS_H:1;
unsigned int     OC_EN_BUS_H:1;
}SYS_PLL_SSC_DIG_BUSH0;

typedef struct 
{
unsigned int     reserved_0:13;
unsigned int     NCODE_T_BUS_H:8;
unsigned int     FCODE_T_BUS_H:11;
}SYS_PLL_SSC_DIG_BUSH1;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     REG_BYPASS_DIVN:1;
unsigned int     REG_OC_STEP_SET_BUS_H:10;
unsigned int     REG_SEL_OC_MODE_BUS_H:2;
unsigned int     REG_HS_OC_STOP_DIFF_BUS_H:2;
unsigned int     REG_OC_DONE_DELAY_BUS_H:6;
unsigned int     REG_BYPASS_PI_BUS_H:1;
unsigned int     REG_SDM_ORDER_BUS_H:1;
unsigned int     REG_PI_CUR_SEL_BUS_H:3;
unsigned int     REG_EN_PI_DEBUG_BUS_H:1;
unsigned int     reserved_1:1;
}SYS_PLL_SSC_DIG_BUSH2;

typedef struct 
{
unsigned int     reserved_0:13;
unsigned int     NCODE_SSC_BUS_H:8;
unsigned int     FCODE_SSC_BUS_H:11;
}SYS_PLL_SSC_DIG_BUSH3;

typedef struct 
{
unsigned int     reserved_0:13;
unsigned int     GRAN_EST_BUS_H:19;
}SYS_PLL_SSC_DIG_BUSH4;

typedef struct 
{
unsigned int     reserved_0:13;
unsigned int     FCW_SSC_DEFAULT_BUS_H:19;
}SYS_PLL_SSC_DIG_BUSH5;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     LOOP_PI_ISEL_BUS_H:3;
unsigned int     PHSEL_BUS_H:5;
unsigned int     DIVN_BUS_H:8;
}SYS_PLL_SSC_DIG_BUSH_DBG1;

typedef struct 
{
unsigned int     reserved_0:10;
unsigned int     load_FCW_BUS_H:1;
unsigned int     OC_DONE_BUS_H:1;
unsigned int     FMOD_BUS_H:1;
unsigned int     NCODE_DEBUG_BUS_H:8;
unsigned int     FCODE_DEBUG_BUS_H:11;
}SYS_PLL_SSC_DIG_BUSH_DBG2;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     REG_CKSSC_INV_DDSA:1;
unsigned int     REG_GRAN_AUTO_RST_DDSA:1;
unsigned int     RSTB_DDSA:1;
unsigned int     EN_SSC_DDSA:1;
unsigned int     OC_EN_DDSA:1;
}SYS_PLL_SSC_DIG_DDSA0;

typedef struct 
{
unsigned int     reserved_0:10;
unsigned int     REG_PLLDDSA_ICO_PDIV2:3;
unsigned int     NCODE_T_DDSA:8;
unsigned int     FCODE_T_DDSA:11;
}SYS_PLL_SSC_DIG_DDSA1;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     REG_BYPASS_DIVN:1;
unsigned int     REG_OC_STEP_SET_DDSA:10;
unsigned int     REG_SEL_OC_MODE_DDSA:2;
unsigned int     REG_HS_OC_STOP_DIFF_DDSA:2;
unsigned int     REG_OC_DONE_DELAY_DDSA:6;
unsigned int     REG_BYPASS_PI_DDSA:1;
unsigned int     REG_SDM_ORDER_DDSA:1;
unsigned int     REG_PI_CUR_SEL_DDSA:3;
unsigned int     REG_EN_PI_DEBUG_DDSA:1;
unsigned int     reserved_1:1;
}SYS_PLL_SSC_DIG_DDSA2;

typedef struct 
{
unsigned int     reserved_0:13;
unsigned int     NCODE_SSC_DDSA:8;
unsigned int     FCODE_SSC_DDSA:11;
}SYS_PLL_SSC_DIG_DDSA3;

typedef struct 
{
unsigned int     reserved_0:13;
unsigned int     GRAN_EST_DDSA:19;
}SYS_PLL_SSC_DIG_DDSA4;

typedef struct 
{
unsigned int     reserved_0:13;
unsigned int     FCW_SSC_DEFAULT_DDSA:19;
}SYS_PLL_SSC_DIG_DDSA5;

typedef struct 
{
unsigned int     reserved_0:15;
unsigned int     LOOP_PI_ISEL_DDSA:3;
unsigned int     PHSEL_DDSA:6;
unsigned int     DIVN_DDSA:8;
}SYS_PLL_SSC_DIG_DDSA_DBG1;

typedef struct 
{
unsigned int     reserved_0:10;
unsigned int     load_FCW_DDSA:1;
unsigned int     OC_DONE_DDSA:1;
unsigned int     FMOD_DDSA:1;
unsigned int     NCODE_DEBUG_DDSA:8;
unsigned int     FCODE_DEBUG_DDSA:11;
}SYS_PLL_SSC_DIG_DDSA_DBG2;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     REG_CKSSC_INV_DDSB:1;
unsigned int     REG_GRAN_AUTO_RST_DDSB:1;
unsigned int     RSTB_DDSB:1;
unsigned int     EN_SSC_DDSB:1;
unsigned int     OC_EN_DDSB:1;
}SYS_PLL_SSC_DIG_DDSB0;

typedef struct 
{
unsigned int     reserved_0:10;
unsigned int     REG_PLLDDSB_ICO_PDIV2:3;
unsigned int     NCODE_T_DDSB:8;
unsigned int     FCODE_T_DDSB:11;
}SYS_PLL_SSC_DIG_DDSB1;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     REG_BYPASS_DIVN:1;
unsigned int     REG_OC_STEP_SET_DDSB:10;
unsigned int     REG_SEL_OC_MODE_DDSB:2;
unsigned int     REG_HS_OC_STOP_DIFF_DDSB:2;
unsigned int     REG_OC_DONE_DELAY_DDSB:6;
unsigned int     REG_BYPASS_PI_DDSB:1;
unsigned int     REG_SDM_ORDER_DDSB:1;
unsigned int     REG_PI_CUR_SEL_DDSB:3;
unsigned int     REG_EN_PI_DEBUG_DDSB:1;
unsigned int     reserved_1:1;
}SYS_PLL_SSC_DIG_DDSB2;

typedef struct 
{
unsigned int     reserved_0:13;
unsigned int     NCODE_SSC_DDSB:8;
unsigned int     FCODE_SSC_DDSB:11;
}SYS_PLL_SSC_DIG_DDSB3;

typedef struct 
{
unsigned int     reserved_0:13;
unsigned int     GRAN_EST_DDSB:19;
}SYS_PLL_SSC_DIG_DDSB4;

typedef struct 
{
unsigned int     reserved_0:13;
unsigned int     FCW_SSC_DEFAULT_DDSB:19;
}SYS_PLL_SSC_DIG_DDSB5;

typedef struct 
{
unsigned int     reserved_0:15;
unsigned int     LOOP_PI_ISEL_DDSB:3;
unsigned int     PHSEL_DDSB:6;
unsigned int     DIVN_DDSB:8;
}SYS_PLL_SSC_DIG_DDSB_DBG1;

typedef struct 
{
unsigned int     reserved_0:10;
unsigned int     load_FCW_DDSB:1;
unsigned int     OC_DONE_DDSB:1;
unsigned int     FMOD_DDSB:1;
unsigned int     NCODE_DEBUG_DDSB:8;
unsigned int     FCODE_DEBUG_DDSB:11;
}SYS_PLL_SSC_DIG_DDSB_DBG2;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     REG_CKSSC_INV_GPU:1;
unsigned int     REG_GRAN_AUTO_RST_GPU:1;
unsigned int     RSTB_GPU:1;
unsigned int     EN_SSC_GPU:1;
unsigned int     OC_EN_GPU:1;
}SYS_PLL_SSC_DIG_GPU0;

typedef struct 
{
unsigned int     reserved_0:13;
unsigned int     NCODE_T_GPU:8;
unsigned int     FCODE_T_GPU:11;
}SYS_PLL_SSC_DIG_GPU1;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     REG_BYPASS_DIVN:1;
unsigned int     REG_OC_STEP_SET_GPU:10;
unsigned int     REG_SEL_OC_MODE_GPU:2;
unsigned int     REG_HS_OC_STOP_DIFF_GPU:2;
unsigned int     REG_OC_DONE_DELAY_GPU:6;
unsigned int     REG_BYPASS_PI_GPU:1;
unsigned int     REG_SDM_ORDER_GPU:1;
unsigned int     REG_PI_CUR_SEL_GPU:3;
unsigned int     REG_EN_PI_DEBUG_GPU:1;
unsigned int     reserved_1:1;
}SYS_PLL_SSC_DIG_GPU2;

typedef struct 
{
unsigned int     reserved_0:13;
unsigned int     NCODE_SSC_GPU:8;
unsigned int     FCODE_SSC_GPU:11;
}SYS_PLL_SSC_DIG_GPU3;

typedef struct 
{
unsigned int     reserved_0:13;
unsigned int     GRAN_EST_GPU:19;
}SYS_PLL_SSC_DIG_GPU4;

typedef struct 
{
unsigned int     reserved_0:13;
unsigned int     FCW_SSC_DEFAULT_GPU:19;
}SYS_PLL_SSC_DIG_GPU5;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     LOOP_PI_ISEL_GPU:3;
unsigned int     PHSEL_GPU:5;
unsigned int     DIVN_GPU:8;
}SYS_PLL_SSC_DIG_GPU_DBG1;

typedef struct 
{
unsigned int     reserved_0:10;
unsigned int     load_FCW_GPU:1;
unsigned int     OC_DONE_GPU:1;
unsigned int     FMOD_GPU:1;
unsigned int     NCODE_DEBUG_GPU:8;
unsigned int     FCODE_DEBUG_GPU:11;
}SYS_PLL_SSC_DIG_GPU_DBG2;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     REG_CKSSC_INV_ACPU:1;
unsigned int     REG_GRAN_AUTO_RST_ACPU:1;
unsigned int     RSTB_ACPU:1;
unsigned int     EN_SSC_ACPU:1;
unsigned int     OC_EN_ACPU:1;
}SYS_PLL_SSC_DIG_ACPU0;

typedef struct 
{
unsigned int     reserved_0:13;
unsigned int     NCODE_T_ACPU:8;
unsigned int     FCODE_T_ACPU:11;
}SYS_PLL_SSC_DIG_ACPU1;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     REG_BYPASS_DIVN:1;
unsigned int     REG_OC_STEP_SET_ACPU:10;
unsigned int     REG_SEL_OC_MODE_ACPU:2;
unsigned int     REG_HS_OC_STOP_DIFF_ACPU:2;
unsigned int     REG_OC_DONE_DELAY_ACPU:6;
unsigned int     REG_BYPASS_PI_ACPU:1;
unsigned int     REG_SDM_ORDER_ACPU:1;
unsigned int     REG_PI_CUR_SEL_ACPU:3;
unsigned int     REG_EN_PI_DEBUG_ACPU:1;
unsigned int     reserved_1:1;
}SYS_PLL_SSC_DIG_ACPU2;

typedef struct 
{
unsigned int     reserved_0:13;
unsigned int     NCODE_SSC_ACPU:8;
unsigned int     FCODE_SSC_ACPU:11;
}SYS_PLL_SSC_DIG_ACPU3;

typedef struct 
{
unsigned int     reserved_0:13;
unsigned int     GRAN_EST_ACPU:19;
}SYS_PLL_SSC_DIG_ACPU4;

typedef struct 
{
unsigned int     reserved_0:13;
unsigned int     FCW_SSC_DEFAULT_ACPU:19;
}SYS_PLL_SSC_DIG_ACPU5;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     LOOP_PI_ISEL_ACPU:3;
unsigned int     PHSEL_ACPU:5;
unsigned int     DIVN_ACPU:8;
}SYS_PLL_SSC_DIG_ACPU_DBG1;

typedef struct 
{
unsigned int     reserved_0:10;
unsigned int     load_FCW_ACPU:1;
unsigned int     OC_DONE_ACPU:1;
unsigned int     FMOD_ACPU:1;
unsigned int     NCODE_DEBUG_ACPU:8;
unsigned int     FCODE_DEBUG_ACPU:11;
}SYS_PLL_SSC_DIG_ACPU_DBG2;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     REG_CKSSC_INV_EDP:1;
unsigned int     REG_GRAN_AUTO_RST_EDP:1;
unsigned int     RSTB_EDP:1;
unsigned int     EN_SSC_EDP:1;
unsigned int     OC_EN_EDP:1;
}SYS_PLL_SSC_DIG_EDP0;

typedef struct 
{
unsigned int     reserved_0:13;
unsigned int     NCODE_T_EDP:8;
unsigned int     FCODE_T_EDP:11;
}SYS_PLL_SSC_DIG_EDP1;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     REG_BYPASS_DIVN:1;
unsigned int     REG_OC_STEP_SET_EDP:10;
unsigned int     REG_SEL_OC_MODE_EDP:2;
unsigned int     REG_HS_OC_STOP_DIFF_EDP:2;
unsigned int     REG_OC_DONE_DELAY_EDP:6;
unsigned int     REG_PI_CUR_SEL_EDP:2;
unsigned int     REG_BYPASS_PI_EDP:1;
unsigned int     REG_SDM_ORDER_EDP:1;
unsigned int     REG_EN_PI_DEBUG_EDP:1;
unsigned int     reserved_1:2;
}SYS_PLL_SSC_DIG_EDP2;

typedef struct 
{
unsigned int     reserved_0:13;
unsigned int     NCODE_SSC_EDP:8;
unsigned int     FCODE_SSC_EDP:11;
}SYS_PLL_SSC_DIG_EDP3;

typedef struct 
{
unsigned int     reserved_0:13;
unsigned int     GRAN_EST_EDP:19;
}SYS_PLL_SSC_DIG_EDP4;

typedef struct 
{
unsigned int     reserved_0:13;
unsigned int     FCW_SSC_DEFAULT_EDP:19;
}SYS_PLL_SSC_DIG_EDP5;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     LOOP_PI_ISEL_EDP:2;
unsigned int     PHSEL_EDP:6;
unsigned int     DIVN_EDP:8;
}SYS_PLL_SSC_DIG_EDP_DBG1;

typedef struct 
{
unsigned int     reserved_0:10;
unsigned int     load_FCW_EDP:1;
unsigned int     OC_DONE_EDP:1;
unsigned int     FMOD_EDP:1;
unsigned int     NCODE_DEBUG_EDP:8;
unsigned int     FCODE_DEBUG_EDP:11;
}SYS_PLL_SSC_DIG_EDP_DBG2;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     REG_CKSSC_INV_PIXEL:1;
unsigned int     REG_GRAN_AUTO_RST_PIXEL:1;
unsigned int     RSTB_PIXEL:1;
unsigned int     EN_SSC_PIXEL:1;
unsigned int     OC_EN_PIXEL:1;
}SYS_PLL_SSC_DIG_PIXEL0;

typedef struct 
{
unsigned int     reserved_0:13;
unsigned int     NCODE_T_PIXEL:8;
unsigned int     FCODE_T_PIXEL:11;
}SYS_PLL_SSC_DIG_PIXEL1;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     REG_BYPASS_DIVN:1;
unsigned int     REG_OC_STEP_SET_PIXEL:10;
unsigned int     REG_SEL_OC_MODE_PIXEL:2;
unsigned int     REG_HS_OC_STOP_DIFF_PIXEL:2;
unsigned int     REG_OC_DONE_DELAY_PIXEL:6;
unsigned int     REG_PI_CUR_SEL_PIXEL:2;
unsigned int     REG_BYPASS_PI_PIXEL:1;
unsigned int     REG_SDM_ORDER_PIXEL:1;
unsigned int     REG_EN_PI_DEBUG_PIXEL:1;
unsigned int     reserved_1:2;
}SYS_PLL_SSC_DIG_PIXEL2;

typedef struct 
{
unsigned int     reserved_0:13;
unsigned int     NCODE_SSC_PIXEL:8;
unsigned int     FCODE_SSC_PIXEL:11;
}SYS_PLL_SSC_DIG_PIXEL3;

typedef struct 
{
unsigned int     reserved_0:13;
unsigned int     GRAN_EST_PIXEL:19;
}SYS_PLL_SSC_DIG_PIXEL4;

typedef struct 
{
unsigned int     reserved_0:13;
unsigned int     FCW_SSC_DEFAULT_PIXEL:19;
}SYS_PLL_SSC_DIG_PIXEL5;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     LOOP_PI_ISEL_PIXEL:2;
unsigned int     PHSEL_PIXEL:6;
unsigned int     DIVN_PIXEL:8;
}SYS_PLL_SSC_DIG_PIXEL_DBG1;

typedef struct 
{
unsigned int     reserved_0:10;
unsigned int     load_FCW_PIXEL:1;
unsigned int     OC_DONE_PIXEL:1;
unsigned int     FMOD_PIXEL:1;
unsigned int     NCODE_DEBUG_PIXEL:8;
unsigned int     FCODE_DEBUG_PIXEL:11;
}SYS_PLL_SSC_DIG_PIXEL_DBG2;

typedef struct 
{
unsigned int     reserved_0:12;
unsigned int     REG_BYPASS_DIVN:1;
unsigned int     FCW_SSC_DEFAULT_HDMITX:19;
}SYS_PLL_HDMI_SD6;

#endif

#define SYS_SOFT_RESET1                                                              0x98000000
#define SYS_SOFT_RESET1_reg_addr                                                     "0x98000000"
#define SYS_SOFT_RESET1_reg                                                          0x98000000
#define set_SYS_SOFT_RESET1_reg(data)   (*((volatile unsigned int*) SYS_SOFT_RESET1_reg)=data)
#define get_SYS_SOFT_RESET1_reg   (*((volatile unsigned int*) SYS_SOFT_RESET1_reg))
#define SYS_SOFT_RESET1_inst_adr                                                     "0x0000"
#define SYS_SOFT_RESET1_inst                                                         0x0000
#define SYS_SOFT_RESET1_rstn_rsa_shift                                               (31)
#define SYS_SOFT_RESET1_rstn_rsa_mask                                                (0x80000000)
#define SYS_SOFT_RESET1_rstn_rsa(data)                                               (0x80000000&((data)<<31))
#define SYS_SOFT_RESET1_rstn_rsa_src(data)                                           ((0x80000000&(data))>>31)
#define SYS_SOFT_RESET1_get_rstn_rsa(data)                                           ((0x80000000&(data))>>31)
#define SYS_SOFT_RESET1_rstn_mipi_shift                                              (30)
#define SYS_SOFT_RESET1_rstn_mipi_mask                                               (0x40000000)
#define SYS_SOFT_RESET1_rstn_mipi(data)                                              (0x40000000&((data)<<30))
#define SYS_SOFT_RESET1_rstn_mipi_src(data)                                          ((0x40000000&(data))>>30)
#define SYS_SOFT_RESET1_get_rstn_mipi(data)                                          ((0x40000000&(data))>>30)
#define SYS_SOFT_RESET1_rstn_nf_shift                                                (29)
#define SYS_SOFT_RESET1_rstn_nf_mask                                                 (0x20000000)
#define SYS_SOFT_RESET1_rstn_nf(data)                                                (0x20000000&((data)<<29))
#define SYS_SOFT_RESET1_rstn_nf_src(data)                                            ((0x20000000&(data))>>29)
#define SYS_SOFT_RESET1_get_rstn_nf(data)                                            ((0x20000000&(data))>>29)
#define SYS_SOFT_RESET1_rstn_ae_shift                                                (28)
#define SYS_SOFT_RESET1_rstn_ae_mask                                                 (0x10000000)
#define SYS_SOFT_RESET1_rstn_ae(data)                                                (0x10000000&((data)<<28))
#define SYS_SOFT_RESET1_rstn_ae_src(data)                                            ((0x10000000&(data))>>28)
#define SYS_SOFT_RESET1_get_rstn_ae(data)                                            ((0x10000000&(data))>>28)
#define SYS_SOFT_RESET1_rstn_tp_shift                                                (27)
#define SYS_SOFT_RESET1_rstn_tp_mask                                                 (0x08000000)
#define SYS_SOFT_RESET1_rstn_tp(data)                                                (0x08000000&((data)<<27))
#define SYS_SOFT_RESET1_rstn_tp_src(data)                                            ((0x08000000&(data))>>27)
#define SYS_SOFT_RESET1_get_rstn_tp(data)                                            ((0x08000000&(data))>>27)
#define SYS_SOFT_RESET1_rstn_md_shift                                                (26)
#define SYS_SOFT_RESET1_rstn_md_mask                                                 (0x04000000)
#define SYS_SOFT_RESET1_rstn_md(data)                                                (0x04000000&((data)<<26))
#define SYS_SOFT_RESET1_rstn_md_src(data)                                            ((0x04000000&(data))>>26)
#define SYS_SOFT_RESET1_get_rstn_md(data)                                            ((0x04000000&(data))>>26)
#define SYS_SOFT_RESET1_rstn_cp_shift                                                (25)
#define SYS_SOFT_RESET1_rstn_cp_mask                                                 (0x02000000)
#define SYS_SOFT_RESET1_rstn_cp(data)                                                (0x02000000&((data)<<25))
#define SYS_SOFT_RESET1_rstn_cp_src(data)                                            ((0x02000000&(data))>>25)
#define SYS_SOFT_RESET1_get_rstn_cp(data)                                            ((0x02000000&(data))>>25)
#define SYS_SOFT_RESET1_rstn_dc_phy_shift                                            (24)
#define SYS_SOFT_RESET1_rstn_dc_phy_mask                                             (0x01000000)
#define SYS_SOFT_RESET1_rstn_dc_phy(data)                                            (0x01000000&((data)<<24))
#define SYS_SOFT_RESET1_rstn_dc_phy_src(data)                                        ((0x01000000&(data))>>24)
#define SYS_SOFT_RESET1_get_rstn_dc_phy(data)                                        ((0x01000000&(data))>>24)
#define SYS_SOFT_RESET1_rstn_dcu_shift                                               (23)
#define SYS_SOFT_RESET1_rstn_dcu_mask                                                (0x00800000)
#define SYS_SOFT_RESET1_rstn_dcu(data)                                               (0x00800000&((data)<<23))
#define SYS_SOFT_RESET1_rstn_dcu_src(data)                                           ((0x00800000&(data))>>23)
#define SYS_SOFT_RESET1_get_rstn_dcu(data)                                           ((0x00800000&(data))>>23)
#define SYS_SOFT_RESET1_rstn_se_shift                                                (22)
#define SYS_SOFT_RESET1_rstn_se_mask                                                 (0x00400000)
#define SYS_SOFT_RESET1_rstn_se(data)                                                (0x00400000&((data)<<22))
#define SYS_SOFT_RESET1_rstn_se_src(data)                                            ((0x00400000&(data))>>22)
#define SYS_SOFT_RESET1_get_rstn_se(data)                                            ((0x00400000&(data))>>22)
#define SYS_SOFT_RESET1_rstn_lvds_shift                                              (21)
#define SYS_SOFT_RESET1_rstn_lvds_mask                                               (0x00200000)
#define SYS_SOFT_RESET1_rstn_lvds(data)                                              (0x00200000&((data)<<21))
#define SYS_SOFT_RESET1_rstn_lvds_src(data)                                          ((0x00200000&(data))>>21)
#define SYS_SOFT_RESET1_get_rstn_lvds(data)                                          ((0x00200000&(data))>>21)
#define SYS_SOFT_RESET1_rstn_vo_shift                                                (20)
#define SYS_SOFT_RESET1_rstn_vo_mask                                                 (0x00100000)
#define SYS_SOFT_RESET1_rstn_vo(data)                                                (0x00100000&((data)<<20))
#define SYS_SOFT_RESET1_rstn_vo_src(data)                                            ((0x00100000&(data))>>20)
#define SYS_SOFT_RESET1_get_rstn_vo(data)                                            ((0x00100000&(data))>>20)
#define SYS_SOFT_RESET1_rstn_tve_shift                                               (19)
#define SYS_SOFT_RESET1_rstn_tve_mask                                                (0x00080000)
#define SYS_SOFT_RESET1_rstn_tve(data)                                               (0x00080000&((data)<<19))
#define SYS_SOFT_RESET1_rstn_tve_src(data)                                           ((0x00080000&(data))>>19)
#define SYS_SOFT_RESET1_get_rstn_tve(data)                                           ((0x00080000&(data))>>19)
#define SYS_SOFT_RESET1_rstn_gpu_shift                                               (18)
#define SYS_SOFT_RESET1_rstn_gpu_mask                                                (0x00040000)
#define SYS_SOFT_RESET1_rstn_gpu(data)                                               (0x00040000&((data)<<18))
#define SYS_SOFT_RESET1_rstn_gpu_src(data)                                           ((0x00040000&(data))>>18)
#define SYS_SOFT_RESET1_get_rstn_gpu(data)                                           ((0x00040000&(data))>>18)
#define SYS_SOFT_RESET1_rstn_aio_shift                                               (17)
#define SYS_SOFT_RESET1_rstn_aio_mask                                                (0x00020000)
#define SYS_SOFT_RESET1_rstn_aio(data)                                               (0x00020000&((data)<<17))
#define SYS_SOFT_RESET1_rstn_aio_src(data)                                           ((0x00020000&(data))>>17)
#define SYS_SOFT_RESET1_get_rstn_aio(data)                                           ((0x00020000&(data))>>17)
#define SYS_SOFT_RESET1_rstn_etn_shift                                               (16)
#define SYS_SOFT_RESET1_rstn_etn_mask                                                (0x00010000)
#define SYS_SOFT_RESET1_rstn_etn(data)                                               (0x00010000&((data)<<16))
#define SYS_SOFT_RESET1_rstn_etn_src(data)                                           ((0x00010000&(data))>>16)
#define SYS_SOFT_RESET1_get_rstn_etn(data)                                           ((0x00010000&(data))>>16)
#define SYS_SOFT_RESET1_rstn_ve3_shift                                               (15)
#define SYS_SOFT_RESET1_rstn_ve3_mask                                                (0x00008000)
#define SYS_SOFT_RESET1_rstn_ve3(data)                                               (0x00008000&((data)<<15))
#define SYS_SOFT_RESET1_rstn_ve3_src(data)                                           ((0x00008000&(data))>>15)
#define SYS_SOFT_RESET1_get_rstn_ve3(data)                                           ((0x00008000&(data))>>15)
#define SYS_SOFT_RESET1_rstn_ve2_shift                                               (14)
#define SYS_SOFT_RESET1_rstn_ve2_mask                                                (0x00004000)
#define SYS_SOFT_RESET1_rstn_ve2(data)                                               (0x00004000&((data)<<14))
#define SYS_SOFT_RESET1_rstn_ve2_src(data)                                           ((0x00004000&(data))>>14)
#define SYS_SOFT_RESET1_get_rstn_ve2(data)                                           ((0x00004000&(data))>>14)
#define SYS_SOFT_RESET1_rstn_ve1_shift                                               (13)
#define SYS_SOFT_RESET1_rstn_ve1_mask                                                (0x00002000)
#define SYS_SOFT_RESET1_rstn_ve1(data)                                               (0x00002000&((data)<<13))
#define SYS_SOFT_RESET1_rstn_ve1_src(data)                                           ((0x00002000&(data))>>13)
#define SYS_SOFT_RESET1_get_rstn_ve1(data)                                           ((0x00002000&(data))>>13)
#define SYS_SOFT_RESET1_rstn_hdmi_shift                                              (12)
#define SYS_SOFT_RESET1_rstn_hdmi_mask                                               (0x00001000)
#define SYS_SOFT_RESET1_rstn_hdmi(data)                                              (0x00001000&((data)<<12))
#define SYS_SOFT_RESET1_rstn_hdmi_src(data)                                          ((0x00001000&(data))>>12)
#define SYS_SOFT_RESET1_get_rstn_hdmi(data)                                          ((0x00001000&(data))>>12)
#define SYS_SOFT_RESET1_sata_func_exist_0_shift                                      (11)
#define SYS_SOFT_RESET1_sata_func_exist_0_mask                                       (0x00000800)
#define SYS_SOFT_RESET1_sata_func_exist_0(data)                                      (0x00000800&((data)<<11))
#define SYS_SOFT_RESET1_sata_func_exist_0_src(data)                                  ((0x00000800&(data))>>11)
#define SYS_SOFT_RESET1_get_sata_func_exist_0(data)                                  ((0x00000800&(data))>>11)
#define SYS_SOFT_RESET1_rstn_sata_phy_pow_0_shift                                    (10)
#define SYS_SOFT_RESET1_rstn_sata_phy_pow_0_mask                                     (0x00000400)
#define SYS_SOFT_RESET1_rstn_sata_phy_pow_0(data)                                    (0x00000400&((data)<<10))
#define SYS_SOFT_RESET1_rstn_sata_phy_pow_0_src(data)                                ((0x00000400&(data))>>10)
#define SYS_SOFT_RESET1_get_rstn_sata_phy_pow_0(data)                                ((0x00000400&(data))>>10)
#define SYS_SOFT_RESET1_rstn_usb_phy1_shift                                          (9)
#define SYS_SOFT_RESET1_rstn_usb_phy1_mask                                           (0x00000200)
#define SYS_SOFT_RESET1_rstn_usb_phy1(data)                                          (0x00000200&((data)<<9))
#define SYS_SOFT_RESET1_rstn_usb_phy1_src(data)                                      ((0x00000200&(data))>>9)
#define SYS_SOFT_RESET1_get_rstn_usb_phy1(data)                                      ((0x00000200&(data))>>9)
#define SYS_SOFT_RESET1_rstn_usb_phy0_shift                                          (8)
#define SYS_SOFT_RESET1_rstn_usb_phy0_mask                                           (0x00000100)
#define SYS_SOFT_RESET1_rstn_usb_phy0(data)                                          (0x00000100&((data)<<8))
#define SYS_SOFT_RESET1_rstn_usb_phy0_src(data)                                      ((0x00000100&(data))>>8)
#define SYS_SOFT_RESET1_get_rstn_usb_phy0(data)                                      ((0x00000100&(data))>>8)
#define SYS_SOFT_RESET1_rstn_sata_phy_0_shift                                        (7)
#define SYS_SOFT_RESET1_rstn_sata_phy_0_mask                                         (0x00000080)
#define SYS_SOFT_RESET1_rstn_sata_phy_0(data)                                        (0x00000080&((data)<<7))
#define SYS_SOFT_RESET1_rstn_sata_phy_0_src(data)                                    ((0x00000080&(data))>>7)
#define SYS_SOFT_RESET1_get_rstn_sata_phy_0(data)                                    ((0x00000080&(data))>>7)
#define SYS_SOFT_RESET1_rstn_usb_shift                                               (6)
#define SYS_SOFT_RESET1_rstn_usb_mask                                                (0x00000040)
#define SYS_SOFT_RESET1_rstn_usb(data)                                               (0x00000040&((data)<<6))
#define SYS_SOFT_RESET1_rstn_usb_src(data)                                           ((0x00000040&(data))>>6)
#define SYS_SOFT_RESET1_get_rstn_usb(data)                                           ((0x00000040&(data))>>6)
#define SYS_SOFT_RESET1_rstn_sata_0_shift                                            (5)
#define SYS_SOFT_RESET1_rstn_sata_0_mask                                             (0x00000020)
#define SYS_SOFT_RESET1_rstn_sata_0(data)                                            (0x00000020&((data)<<5))
#define SYS_SOFT_RESET1_rstn_sata_0_src(data)                                        ((0x00000020&(data))>>5)
#define SYS_SOFT_RESET1_get_rstn_sata_0(data)                                        ((0x00000020&(data))>>5)
#define SYS_SOFT_RESET1_rstn_usb3_p0_mdio_shift                                      (4)
#define SYS_SOFT_RESET1_rstn_usb3_p0_mdio_mask                                       (0x00000010)
#define SYS_SOFT_RESET1_rstn_usb3_p0_mdio(data)                                      (0x00000010&((data)<<4))
#define SYS_SOFT_RESET1_rstn_usb3_p0_mdio_src(data)                                  ((0x00000010&(data))>>4)
#define SYS_SOFT_RESET1_get_rstn_usb3_p0_mdio(data)                                  ((0x00000010&(data))>>4)
#define SYS_SOFT_RESET1_rstn_gspi_shift                                              (3)
#define SYS_SOFT_RESET1_rstn_gspi_mask                                               (0x00000008)
#define SYS_SOFT_RESET1_rstn_gspi(data)                                              (0x00000008&((data)<<3))
#define SYS_SOFT_RESET1_rstn_gspi_src(data)                                          ((0x00000008&(data))>>3)
#define SYS_SOFT_RESET1_get_rstn_gspi(data)                                          ((0x00000008&(data))>>3)
#define SYS_SOFT_RESET1_rstn_usb3_phy0_pow_shift                                     (2)
#define SYS_SOFT_RESET1_rstn_usb3_phy0_pow_mask                                      (0x00000004)
#define SYS_SOFT_RESET1_rstn_usb3_phy0_pow(data)                                     (0x00000004&((data)<<2))
#define SYS_SOFT_RESET1_rstn_usb3_phy0_pow_src(data)                                 ((0x00000004&(data))>>2)
#define SYS_SOFT_RESET1_get_rstn_usb3_phy0_pow(data)                                 ((0x00000004&(data))>>2)
#define SYS_SOFT_RESET1_rstn_nat_shift                                               (1)
#define SYS_SOFT_RESET1_rstn_nat_mask                                                (0x00000002)
#define SYS_SOFT_RESET1_rstn_nat(data)                                               (0x00000002&((data)<<1))
#define SYS_SOFT_RESET1_rstn_nat_src(data)                                           ((0x00000002&(data))>>1)
#define SYS_SOFT_RESET1_get_rstn_nat(data)                                           ((0x00000002&(data))>>1)
#define SYS_SOFT_RESET1_rstn_misc_shift                                              (0)
#define SYS_SOFT_RESET1_rstn_misc_mask                                               (0x00000001)
#define SYS_SOFT_RESET1_rstn_misc(data)                                              (0x00000001&((data)<<0))
#define SYS_SOFT_RESET1_rstn_misc_src(data)                                          ((0x00000001&(data))>>0)
#define SYS_SOFT_RESET1_get_rstn_misc(data)                                          ((0x00000001&(data))>>0)


#define SYS_SOFT_RESET2                                                              0x98000004
#define SYS_SOFT_RESET2_reg_addr                                                     "0x98000004"
#define SYS_SOFT_RESET2_reg                                                          0x98000004
#define set_SYS_SOFT_RESET2_reg(data)   (*((volatile unsigned int*) SYS_SOFT_RESET2_reg)=data)
#define get_SYS_SOFT_RESET2_reg   (*((volatile unsigned int*) SYS_SOFT_RESET2_reg))
#define SYS_SOFT_RESET2_inst_adr                                                     "0x0001"
#define SYS_SOFT_RESET2_inst                                                         0x0001
#define SYS_SOFT_RESET2_rstn_sds_phy_shift                                           (31)
#define SYS_SOFT_RESET2_rstn_sds_phy_mask                                            (0x80000000)
#define SYS_SOFT_RESET2_rstn_sds_phy(data)                                           (0x80000000&((data)<<31))
#define SYS_SOFT_RESET2_rstn_sds_phy_src(data)                                       ((0x80000000&(data))>>31)
#define SYS_SOFT_RESET2_get_rstn_sds_phy(data)                                       ((0x80000000&(data))>>31)
#define SYS_SOFT_RESET2_rstn_cbus_tx_shift                                           (30)
#define SYS_SOFT_RESET2_rstn_cbus_tx_mask                                            (0x40000000)
#define SYS_SOFT_RESET2_rstn_cbus_tx(data)                                           (0x40000000&((data)<<30))
#define SYS_SOFT_RESET2_rstn_cbus_tx_src(data)                                       ((0x40000000&(data))>>30)
#define SYS_SOFT_RESET2_get_rstn_cbus_tx(data)                                       ((0x40000000&(data))>>30)
#define SYS_SOFT_RESET2_rstn_misc_sc_shift                                           (29)
#define SYS_SOFT_RESET2_rstn_misc_sc_mask                                            (0x20000000)
#define SYS_SOFT_RESET2_rstn_misc_sc(data)                                           (0x20000000&((data)<<29))
#define SYS_SOFT_RESET2_rstn_misc_sc_src(data)                                       ((0x20000000&(data))>>29)
#define SYS_SOFT_RESET2_get_rstn_misc_sc(data)                                       ((0x20000000&(data))>>29)
#define SYS_SOFT_RESET2_rstn_ur1_shift                                               (28)
#define SYS_SOFT_RESET2_rstn_ur1_mask                                                (0x10000000)
#define SYS_SOFT_RESET2_rstn_ur1(data)                                               (0x10000000&((data)<<28))
#define SYS_SOFT_RESET2_rstn_ur1_src(data)                                           ((0x10000000&(data))>>28)
#define SYS_SOFT_RESET2_get_rstn_ur1(data)                                           ((0x10000000&(data))>>28)
#define SYS_SOFT_RESET2_rstn_ur2_shift                                               (27)
#define SYS_SOFT_RESET2_rstn_ur2_mask                                                (0x08000000)
#define SYS_SOFT_RESET2_rstn_ur2(data)                                               (0x08000000&((data)<<27))
#define SYS_SOFT_RESET2_rstn_ur2_src(data)                                           ((0x08000000&(data))>>27)
#define SYS_SOFT_RESET2_get_rstn_ur2(data)                                           ((0x08000000&(data))>>27)
#define SYS_SOFT_RESET2_rstn_i2c_1_shift                                             (26)
#define SYS_SOFT_RESET2_rstn_i2c_1_mask                                              (0x04000000)
#define SYS_SOFT_RESET2_rstn_i2c_1(data)                                             (0x04000000&((data)<<26))
#define SYS_SOFT_RESET2_rstn_i2c_1_src(data)                                         ((0x04000000&(data))>>26)
#define SYS_SOFT_RESET2_get_rstn_i2c_1(data)                                         ((0x04000000&(data))>>26)
#define SYS_SOFT_RESET2_rstn_i2c_2_shift                                             (25)
#define SYS_SOFT_RESET2_rstn_i2c_2_mask                                              (0x02000000)
#define SYS_SOFT_RESET2_rstn_i2c_2(data)                                             (0x02000000&((data)<<25))
#define SYS_SOFT_RESET2_rstn_i2c_2_src(data)                                         ((0x02000000&(data))>>25)
#define SYS_SOFT_RESET2_get_rstn_i2c_2(data)                                         ((0x02000000&(data))>>25)
#define SYS_SOFT_RESET2_rstn_i2c_3_shift                                             (24)
#define SYS_SOFT_RESET2_rstn_i2c_3_mask                                              (0x01000000)
#define SYS_SOFT_RESET2_rstn_i2c_3(data)                                             (0x01000000&((data)<<24))
#define SYS_SOFT_RESET2_rstn_i2c_3_src(data)                                         ((0x01000000&(data))>>24)
#define SYS_SOFT_RESET2_get_rstn_i2c_3(data)                                         ((0x01000000&(data))>>24)
#define SYS_SOFT_RESET2_rstn_i2c_4_shift                                             (23)
#define SYS_SOFT_RESET2_rstn_i2c_4_mask                                              (0x00800000)
#define SYS_SOFT_RESET2_rstn_i2c_4(data)                                             (0x00800000&((data)<<23))
#define SYS_SOFT_RESET2_rstn_i2c_4_src(data)                                         ((0x00800000&(data))>>23)
#define SYS_SOFT_RESET2_get_rstn_i2c_4(data)                                         ((0x00800000&(data))>>23)
#define SYS_SOFT_RESET2_rstn_pcie1_nonstich_shift                                    (22)
#define SYS_SOFT_RESET2_rstn_pcie1_nonstich_mask                                     (0x00400000)
#define SYS_SOFT_RESET2_rstn_pcie1_nonstich(data)                                    (0x00400000&((data)<<22))
#define SYS_SOFT_RESET2_rstn_pcie1_nonstich_src(data)                                ((0x00400000&(data))>>22)
#define SYS_SOFT_RESET2_get_rstn_pcie1_nonstich(data)                                ((0x00400000&(data))>>22)
#define SYS_SOFT_RESET2_rstn_pcie1_power_shift                                       (21)
#define SYS_SOFT_RESET2_rstn_pcie1_power_mask                                        (0x00200000)
#define SYS_SOFT_RESET2_rstn_pcie1_power(data)                                       (0x00200000&((data)<<21))
#define SYS_SOFT_RESET2_rstn_pcie1_power_src(data)                                   ((0x00200000&(data))>>21)
#define SYS_SOFT_RESET2_get_rstn_pcie1_power(data)                                   ((0x00200000&(data))>>21)
#define SYS_SOFT_RESET2_rstn_pcie1_core_shift                                        (20)
#define SYS_SOFT_RESET2_rstn_pcie1_core_mask                                         (0x00100000)
#define SYS_SOFT_RESET2_rstn_pcie1_core(data)                                        (0x00100000&((data)<<20))
#define SYS_SOFT_RESET2_rstn_pcie1_core_src(data)                                    ((0x00100000&(data))>>20)
#define SYS_SOFT_RESET2_get_rstn_pcie1_core(data)                                    ((0x00100000&(data))>>20)
#define SYS_SOFT_RESET2_rstn_pcie1_stitch_shift                                      (19)
#define SYS_SOFT_RESET2_rstn_pcie1_stitch_mask                                       (0x00080000)
#define SYS_SOFT_RESET2_rstn_pcie1_stitch(data)                                      (0x00080000&((data)<<19))
#define SYS_SOFT_RESET2_rstn_pcie1_stitch_src(data)                                  ((0x00080000&(data))>>19)
#define SYS_SOFT_RESET2_get_rstn_pcie1_stitch(data)                                  ((0x00080000&(data))>>19)
#define SYS_SOFT_RESET2_rstn_i2c_5_shift                                             (18)
#define SYS_SOFT_RESET2_rstn_i2c_5_mask                                              (0x00040000)
#define SYS_SOFT_RESET2_rstn_i2c_5(data)                                             (0x00040000&((data)<<18))
#define SYS_SOFT_RESET2_rstn_i2c_5_src(data)                                         ((0x00040000&(data))>>18)
#define SYS_SOFT_RESET2_get_rstn_i2c_5(data)                                         ((0x00040000&(data))>>18)
#define SYS_SOFT_RESET2_rstn_pcie1_shift                                             (17)
#define SYS_SOFT_RESET2_rstn_pcie1_mask                                              (0x00020000)
#define SYS_SOFT_RESET2_rstn_pcie1(data)                                             (0x00020000&((data)<<17))
#define SYS_SOFT_RESET2_rstn_pcie1_src(data)                                         ((0x00020000&(data))>>17)
#define SYS_SOFT_RESET2_get_rstn_pcie1(data)                                         ((0x00020000&(data))>>17)
#define SYS_SOFT_RESET2_rstn_pcie1_phy_shift                                         (16)
#define SYS_SOFT_RESET2_rstn_pcie1_phy_mask                                          (0x00010000)
#define SYS_SOFT_RESET2_rstn_pcie1_phy(data)                                         (0x00010000&((data)<<16))
#define SYS_SOFT_RESET2_rstn_pcie1_phy_src(data)                                     ((0x00010000&(data))>>16)
#define SYS_SOFT_RESET2_get_rstn_pcie1_phy(data)                                     ((0x00010000&(data))>>16)
#define SYS_SOFT_RESET2_rstn_pcie0_nonstich_shift                                    (15)
#define SYS_SOFT_RESET2_rstn_pcie0_nonstich_mask                                     (0x00008000)
#define SYS_SOFT_RESET2_rstn_pcie0_nonstich(data)                                    (0x00008000&((data)<<15))
#define SYS_SOFT_RESET2_rstn_pcie0_nonstich_src(data)                                ((0x00008000&(data))>>15)
#define SYS_SOFT_RESET2_get_rstn_pcie0_nonstich(data)                                ((0x00008000&(data))>>15)
#define SYS_SOFT_RESET2_rstn_pcie0_power_shift                                       (14)
#define SYS_SOFT_RESET2_rstn_pcie0_power_mask                                        (0x00004000)
#define SYS_SOFT_RESET2_rstn_pcie0_power(data)                                       (0x00004000&((data)<<14))
#define SYS_SOFT_RESET2_rstn_pcie0_power_src(data)                                   ((0x00004000&(data))>>14)
#define SYS_SOFT_RESET2_get_rstn_pcie0_power(data)                                   ((0x00004000&(data))>>14)
#define SYS_SOFT_RESET2_rstn_pcie0_core_shift                                        (13)
#define SYS_SOFT_RESET2_rstn_pcie0_core_mask                                         (0x00002000)
#define SYS_SOFT_RESET2_rstn_pcie0_core(data)                                        (0x00002000&((data)<<13))
#define SYS_SOFT_RESET2_rstn_pcie0_core_src(data)                                    ((0x00002000&(data))>>13)
#define SYS_SOFT_RESET2_get_rstn_pcie0_core(data)                                    ((0x00002000&(data))>>13)
#define SYS_SOFT_RESET2_rstn_sdio_shift                                              (12)
#define SYS_SOFT_RESET2_rstn_sdio_mask                                               (0x00001000)
#define SYS_SOFT_RESET2_rstn_sdio(data)                                              (0x00001000&((data)<<12))
#define SYS_SOFT_RESET2_rstn_sdio_src(data)                                          ((0x00001000&(data))>>12)
#define SYS_SOFT_RESET2_get_rstn_sdio(data)                                          ((0x00001000&(data))>>12)
#define SYS_SOFT_RESET2_rstn_emmc_shift                                              (11)
#define SYS_SOFT_RESET2_rstn_emmc_mask                                               (0x00000800)
#define SYS_SOFT_RESET2_rstn_emmc(data)                                              (0x00000800&((data)<<11))
#define SYS_SOFT_RESET2_rstn_emmc_src(data)                                          ((0x00000800&(data))>>11)
#define SYS_SOFT_RESET2_get_rstn_emmc(data)                                          ((0x00000800&(data))>>11)
#define SYS_SOFT_RESET2_rstn_cr_shift                                                (10)
#define SYS_SOFT_RESET2_rstn_cr_mask                                                 (0x00000400)
#define SYS_SOFT_RESET2_rstn_cr(data)                                                (0x00000400&((data)<<10))
#define SYS_SOFT_RESET2_rstn_cr_src(data)                                            ((0x00000400&(data))>>10)
#define SYS_SOFT_RESET2_get_rstn_cr(data)                                            ((0x00000400&(data))>>10)
#define SYS_SOFT_RESET2_rstn_pcr_cnt_shift                                           (9)
#define SYS_SOFT_RESET2_rstn_pcr_cnt_mask                                            (0x00000200)
#define SYS_SOFT_RESET2_rstn_pcr_cnt(data)                                           (0x00000200&((data)<<9))
#define SYS_SOFT_RESET2_rstn_pcr_cnt_src(data)                                       ((0x00000200&(data))>>9)
#define SYS_SOFT_RESET2_get_rstn_pcr_cnt(data)                                       ((0x00000200&(data))>>9)
#define SYS_SOFT_RESET2_rstn_pcie0_shift                                             (8)
#define SYS_SOFT_RESET2_rstn_pcie0_mask                                              (0x00000100)
#define SYS_SOFT_RESET2_rstn_pcie0(data)                                             (0x00000100&((data)<<8))
#define SYS_SOFT_RESET2_rstn_pcie0_src(data)                                         ((0x00000100&(data))>>8)
#define SYS_SOFT_RESET2_get_rstn_pcie0(data)                                         ((0x00000100&(data))>>8)
#define SYS_SOFT_RESET2_rstn_pcie0_phy_shift                                         (7)
#define SYS_SOFT_RESET2_rstn_pcie0_phy_mask                                          (0x00000080)
#define SYS_SOFT_RESET2_rstn_pcie0_phy(data)                                         (0x00000080&((data)<<7))
#define SYS_SOFT_RESET2_rstn_pcie0_phy_src(data)                                     ((0x00000080&(data))>>7)
#define SYS_SOFT_RESET2_get_rstn_pcie0_phy(data)                                     ((0x00000080&(data))>>7)
#define SYS_SOFT_RESET2_rstn_pcie0_stitch_shift                                      (6)
#define SYS_SOFT_RESET2_rstn_pcie0_stitch_mask                                       (0x00000040)
#define SYS_SOFT_RESET2_rstn_pcie0_stitch(data)                                      (0x00000040&((data)<<6))
#define SYS_SOFT_RESET2_rstn_pcie0_stitch_src(data)                                  ((0x00000040&(data))>>6)
#define SYS_SOFT_RESET2_get_rstn_pcie0_stitch(data)                                  ((0x00000040&(data))>>6)
#define SYS_SOFT_RESET2_rstn_usb3_p1_mdio_shift                                      (5)
#define SYS_SOFT_RESET2_rstn_usb3_p1_mdio_mask                                       (0x00000020)
#define SYS_SOFT_RESET2_rstn_usb3_p1_mdio(data)                                      (0x00000020&((data)<<5))
#define SYS_SOFT_RESET2_rstn_usb3_p1_mdio_src(data)                                  ((0x00000020&(data))>>5)
#define SYS_SOFT_RESET2_get_rstn_usb3_p1_mdio(data)                                  ((0x00000020&(data))>>5)
#define SYS_SOFT_RESET2_rstn_usb3_phy1_pow_shift                                     (4)
#define SYS_SOFT_RESET2_rstn_usb3_phy1_pow_mask                                      (0x00000010)
#define SYS_SOFT_RESET2_rstn_usb3_phy1_pow(data)                                     (0x00000010&((data)<<4))
#define SYS_SOFT_RESET2_rstn_usb3_phy1_pow_src(data)                                 ((0x00000010&(data))>>4)
#define SYS_SOFT_RESET2_get_rstn_usb3_phy1_pow(data)                                 ((0x00000010&(data))>>4)
#define SYS_SOFT_RESET2_rstn_usb_phy2_shift                                          (3)
#define SYS_SOFT_RESET2_rstn_usb_phy2_mask                                           (0x00000008)
#define SYS_SOFT_RESET2_rstn_usb_phy2(data)                                          (0x00000008&((data)<<3))
#define SYS_SOFT_RESET2_rstn_usb_phy2_src(data)                                      ((0x00000008&(data))>>3)
#define SYS_SOFT_RESET2_get_rstn_usb_phy2(data)                                      ((0x00000008&(data))>>3)
#define SYS_SOFT_RESET2_rstn_usb_phy3_shift                                          (2)
#define SYS_SOFT_RESET2_rstn_usb_phy3_mask                                           (0x00000004)
#define SYS_SOFT_RESET2_rstn_usb_phy3(data)                                          (0x00000004&((data)<<2))
#define SYS_SOFT_RESET2_rstn_usb_phy3_src(data)                                      ((0x00000004&(data))>>2)
#define SYS_SOFT_RESET2_get_rstn_usb_phy3(data)                                      ((0x00000004&(data))>>2)
#define SYS_SOFT_RESET2_rstn_jpeg_shift                                              (1)
#define SYS_SOFT_RESET2_rstn_jpeg_mask                                               (0x00000002)
#define SYS_SOFT_RESET2_rstn_jpeg(data)                                              (0x00000002&((data)<<1))
#define SYS_SOFT_RESET2_rstn_jpeg_src(data)                                          ((0x00000002&(data))>>1)
#define SYS_SOFT_RESET2_get_rstn_jpeg(data)                                          ((0x00000002&(data))>>1)
#define SYS_SOFT_RESET2_rstn_acpu_shift                                              (0)
#define SYS_SOFT_RESET2_rstn_acpu_mask                                               (0x00000001)
#define SYS_SOFT_RESET2_rstn_acpu(data)                                              (0x00000001&((data)<<0))
#define SYS_SOFT_RESET2_rstn_acpu_src(data)                                          ((0x00000001&(data))>>0)
#define SYS_SOFT_RESET2_get_rstn_acpu(data)                                          ((0x00000001&(data))>>0)


#define SYS_SOFT_RESET3                                                              0x98000008
#define SYS_SOFT_RESET3_reg_addr                                                     "0x98000008"
#define SYS_SOFT_RESET3_reg                                                          0x98000008
#define set_SYS_SOFT_RESET3_reg(data)   (*((volatile unsigned int*) SYS_SOFT_RESET3_reg)=data)
#define get_SYS_SOFT_RESET3_reg   (*((volatile unsigned int*) SYS_SOFT_RESET3_reg))
#define SYS_SOFT_RESET3_inst_adr                                                     "0x0002"
#define SYS_SOFT_RESET3_inst                                                         0x0002
#define SYS_SOFT_RESET3_rstn_sb2_shift                                               (0)
#define SYS_SOFT_RESET3_rstn_sb2_mask                                                (0x00000001)
#define SYS_SOFT_RESET3_rstn_sb2(data)                                               (0x00000001&((data)<<0))
#define SYS_SOFT_RESET3_rstn_sb2_src(data)                                           ((0x00000001&(data))>>0)
#define SYS_SOFT_RESET3_get_rstn_sb2(data)                                           ((0x00000001&(data))>>0)


#define SYS_CLOCK_ENABLE1                                                            0x9800000C
#define SYS_CLOCK_ENABLE1_reg_addr                                                   "0x9800000C"
#define SYS_CLOCK_ENABLE1_reg                                                        0x9800000C
#define set_SYS_CLOCK_ENABLE1_reg(data)   (*((volatile unsigned int*) SYS_CLOCK_ENABLE1_reg)=data)
#define get_SYS_CLOCK_ENABLE1_reg   (*((volatile unsigned int*) SYS_CLOCK_ENABLE1_reg))
#define SYS_CLOCK_ENABLE1_inst_adr                                                   "0x0003"
#define SYS_CLOCK_ENABLE1_inst                                                       0x0003
#define SYS_CLOCK_ENABLE1_clk_en_sd_ip_shift                                         (31)
#define SYS_CLOCK_ENABLE1_clk_en_sd_ip_mask                                          (0x80000000)
#define SYS_CLOCK_ENABLE1_clk_en_sd_ip(data)                                         (0x80000000&((data)<<31))
#define SYS_CLOCK_ENABLE1_clk_en_sd_ip_src(data)                                     ((0x80000000&(data))>>31)
#define SYS_CLOCK_ENABLE1_get_clk_en_sd_ip(data)                                     ((0x80000000&(data))>>31)
#define SYS_CLOCK_ENABLE1_clk_en_sdio_shift                                          (30)
#define SYS_CLOCK_ENABLE1_clk_en_sdio_mask                                           (0x40000000)
#define SYS_CLOCK_ENABLE1_clk_en_sdio(data)                                          (0x40000000&((data)<<30))
#define SYS_CLOCK_ENABLE1_clk_en_sdio_src(data)                                      ((0x40000000&(data))>>30)
#define SYS_CLOCK_ENABLE1_get_clk_en_sdio(data)                                      ((0x40000000&(data))>>30)
#define SYS_CLOCK_ENABLE1_clk_en_ve3_shift                                           (29)
#define SYS_CLOCK_ENABLE1_clk_en_ve3_mask                                            (0x20000000)
#define SYS_CLOCK_ENABLE1_clk_en_ve3(data)                                           (0x20000000&((data)<<29))
#define SYS_CLOCK_ENABLE1_clk_en_ve3_src(data)                                       ((0x20000000&(data))>>29)
#define SYS_CLOCK_ENABLE1_get_clk_en_ve3(data)                                       ((0x20000000&(data))>>29)
#define SYS_CLOCK_ENABLE1_clk_en_emmc_ip_shift                                       (28)
#define SYS_CLOCK_ENABLE1_clk_en_emmc_ip_mask                                        (0x10000000)
#define SYS_CLOCK_ENABLE1_clk_en_emmc_ip(data)                                       (0x10000000&((data)<<28))
#define SYS_CLOCK_ENABLE1_clk_en_emmc_ip_src(data)                                   ((0x10000000&(data))>>28)
#define SYS_CLOCK_ENABLE1_get_clk_en_emmc_ip(data)                                   ((0x10000000&(data))>>28)
#define SYS_CLOCK_ENABLE1_clk_en_mipi_shift                                          (27)
#define SYS_CLOCK_ENABLE1_clk_en_mipi_mask                                           (0x08000000)
#define SYS_CLOCK_ENABLE1_clk_en_mipi(data)                                          (0x08000000&((data)<<27))
#define SYS_CLOCK_ENABLE1_clk_en_mipi_src(data)                                      ((0x08000000&(data))>>27)
#define SYS_CLOCK_ENABLE1_get_clk_en_mipi(data)                                      ((0x08000000&(data))>>27)
#define SYS_CLOCK_ENABLE1_clk_en_sdio_ip_shift                                       (26)
#define SYS_CLOCK_ENABLE1_clk_en_sdio_ip_mask                                        (0x04000000)
#define SYS_CLOCK_ENABLE1_clk_en_sdio_ip(data)                                       (0x04000000&((data)<<26))
#define SYS_CLOCK_ENABLE1_clk_en_sdio_ip_src(data)                                   ((0x04000000&(data))>>26)
#define SYS_CLOCK_ENABLE1_get_clk_en_sdio_ip(data)                                   ((0x04000000&(data))>>26)
#define SYS_CLOCK_ENABLE1_clk_en_cr_shift                                            (25)
#define SYS_CLOCK_ENABLE1_clk_en_cr_mask                                             (0x02000000)
#define SYS_CLOCK_ENABLE1_clk_en_cr(data)                                            (0x02000000&((data)<<25))
#define SYS_CLOCK_ENABLE1_clk_en_cr_src(data)                                        ((0x02000000&(data))>>25)
#define SYS_CLOCK_ENABLE1_get_clk_en_cr(data)                                        ((0x02000000&(data))>>25)
#define SYS_CLOCK_ENABLE1_clk_en_emmc_shift                                          (24)
#define SYS_CLOCK_ENABLE1_clk_en_emmc_mask                                           (0x01000000)
#define SYS_CLOCK_ENABLE1_clk_en_emmc(data)                                          (0x01000000&((data)<<24))
#define SYS_CLOCK_ENABLE1_clk_en_emmc_src(data)                                      ((0x01000000&(data))>>24)
#define SYS_CLOCK_ENABLE1_get_clk_en_emmc(data)                                      ((0x01000000&(data))>>24)
#define SYS_CLOCK_ENABLE1_clk_en_nf_shift                                            (23)
#define SYS_CLOCK_ENABLE1_clk_en_nf_mask                                             (0x00800000)
#define SYS_CLOCK_ENABLE1_clk_en_nf(data)                                            (0x00800000&((data)<<23))
#define SYS_CLOCK_ENABLE1_clk_en_nf_src(data)                                        ((0x00800000&(data))>>23)
#define SYS_CLOCK_ENABLE1_get_clk_en_nf(data)                                        ((0x00800000&(data))>>23)
#define SYS_CLOCK_ENABLE1_clk_en_rsa_shift                                           (22)
#define SYS_CLOCK_ENABLE1_clk_en_rsa_mask                                            (0x00400000)
#define SYS_CLOCK_ENABLE1_clk_en_rsa(data)                                           (0x00400000&((data)<<22))
#define SYS_CLOCK_ENABLE1_clk_en_rsa_src(data)                                       ((0x00400000&(data))>>22)
#define SYS_CLOCK_ENABLE1_get_clk_en_rsa(data)                                       ((0x00400000&(data))>>22)
#define SYS_CLOCK_ENABLE1_clk_en_tp_shift                                            (21)
#define SYS_CLOCK_ENABLE1_clk_en_tp_mask                                             (0x00200000)
#define SYS_CLOCK_ENABLE1_clk_en_tp(data)                                            (0x00200000&((data)<<21))
#define SYS_CLOCK_ENABLE1_clk_en_tp_src(data)                                        ((0x00200000&(data))>>21)
#define SYS_CLOCK_ENABLE1_get_clk_en_tp(data)                                        ((0x00200000&(data))>>21)
#define SYS_CLOCK_ENABLE1_clk_en_md_shift                                            (20)
#define SYS_CLOCK_ENABLE1_clk_en_md_mask                                             (0x00100000)
#define SYS_CLOCK_ENABLE1_clk_en_md(data)                                            (0x00100000&((data)<<20))
#define SYS_CLOCK_ENABLE1_clk_en_md_src(data)                                        ((0x00100000&(data))>>20)
#define SYS_CLOCK_ENABLE1_get_clk_en_md(data)                                        ((0x00100000&(data))>>20)
#define SYS_CLOCK_ENABLE1_clk_en_cp_shift                                            (19)
#define SYS_CLOCK_ENABLE1_clk_en_cp_mask                                             (0x00080000)
#define SYS_CLOCK_ENABLE1_clk_en_cp(data)                                            (0x00080000&((data)<<19))
#define SYS_CLOCK_ENABLE1_clk_en_cp_src(data)                                        ((0x00080000&(data))>>19)
#define SYS_CLOCK_ENABLE1_get_clk_en_cp(data)                                        ((0x00080000&(data))>>19)
#define SYS_CLOCK_ENABLE1_clk_en_dcu_shift                                           (18)
#define SYS_CLOCK_ENABLE1_clk_en_dcu_mask                                            (0x00040000)
#define SYS_CLOCK_ENABLE1_clk_en_dcu(data)                                           (0x00040000&((data)<<18))
#define SYS_CLOCK_ENABLE1_clk_en_dcu_src(data)                                       ((0x00040000&(data))>>18)
#define SYS_CLOCK_ENABLE1_get_clk_en_dcu(data)                                       ((0x00040000&(data))>>18)
#define SYS_CLOCK_ENABLE1_clk_en_se_shift                                            (17)
#define SYS_CLOCK_ENABLE1_clk_en_se_mask                                             (0x00020000)
#define SYS_CLOCK_ENABLE1_clk_en_se(data)                                            (0x00020000&((data)<<17))
#define SYS_CLOCK_ENABLE1_clk_en_se_src(data)                                        ((0x00020000&(data))>>17)
#define SYS_CLOCK_ENABLE1_get_clk_en_se(data)                                        ((0x00020000&(data))>>17)
#define SYS_CLOCK_ENABLE1_clk_en_lvds_shift                                          (16)
#define SYS_CLOCK_ENABLE1_clk_en_lvds_mask                                           (0x00010000)
#define SYS_CLOCK_ENABLE1_clk_en_lvds(data)                                          (0x00010000&((data)<<16))
#define SYS_CLOCK_ENABLE1_clk_en_lvds_src(data)                                      ((0x00010000&(data))>>16)
#define SYS_CLOCK_ENABLE1_get_clk_en_lvds(data)                                      ((0x00010000&(data))>>16)
#define SYS_CLOCK_ENABLE1_clk_en_vo_shift                                            (15)
#define SYS_CLOCK_ENABLE1_clk_en_vo_mask                                             (0x00008000)
#define SYS_CLOCK_ENABLE1_clk_en_vo(data)                                            (0x00008000&((data)<<15))
#define SYS_CLOCK_ENABLE1_clk_en_vo_src(data)                                        ((0x00008000&(data))>>15)
#define SYS_CLOCK_ENABLE1_get_clk_en_vo(data)                                        ((0x00008000&(data))>>15)
#define SYS_CLOCK_ENABLE1_clk_en_tve_shift                                           (14)
#define SYS_CLOCK_ENABLE1_clk_en_tve_mask                                            (0x00004000)
#define SYS_CLOCK_ENABLE1_clk_en_tve(data)                                           (0x00004000&((data)<<14))
#define SYS_CLOCK_ENABLE1_clk_en_tve_src(data)                                       ((0x00004000&(data))>>14)
#define SYS_CLOCK_ENABLE1_get_clk_en_tve(data)                                       ((0x00004000&(data))>>14)
#define SYS_CLOCK_ENABLE1_clk_en_ve2_shift                                           (13)
#define SYS_CLOCK_ENABLE1_clk_en_ve2_mask                                            (0x00002000)
#define SYS_CLOCK_ENABLE1_clk_en_ve2(data)                                           (0x00002000&((data)<<13))
#define SYS_CLOCK_ENABLE1_clk_en_ve2_src(data)                                       ((0x00002000&(data))>>13)
#define SYS_CLOCK_ENABLE1_get_clk_en_ve2(data)                                       ((0x00002000&(data))>>13)
#define SYS_CLOCK_ENABLE1_clk_en_ve1_shift                                           (12)
#define SYS_CLOCK_ENABLE1_clk_en_ve1_mask                                            (0x00001000)
#define SYS_CLOCK_ENABLE1_clk_en_ve1(data)                                           (0x00001000&((data)<<12))
#define SYS_CLOCK_ENABLE1_clk_en_ve1_src(data)                                       ((0x00001000&(data))>>12)
#define SYS_CLOCK_ENABLE1_get_clk_en_ve1(data)                                       ((0x00001000&(data))>>12)
#define SYS_CLOCK_ENABLE1_clk_en_gpu_shift                                           (11)
#define SYS_CLOCK_ENABLE1_clk_en_gpu_mask                                            (0x00000800)
#define SYS_CLOCK_ENABLE1_clk_en_gpu(data)                                           (0x00000800&((data)<<11))
#define SYS_CLOCK_ENABLE1_clk_en_gpu_src(data)                                       ((0x00000800&(data))>>11)
#define SYS_CLOCK_ENABLE1_get_clk_en_gpu(data)                                       ((0x00000800&(data))>>11)
#define SYS_CLOCK_ENABLE1_clk_en_aio_shift                                           (10)
#define SYS_CLOCK_ENABLE1_clk_en_aio_mask                                            (0x00000400)
#define SYS_CLOCK_ENABLE1_clk_en_aio(data)                                           (0x00000400&((data)<<10))
#define SYS_CLOCK_ENABLE1_clk_en_aio_src(data)                                       ((0x00000400&(data))>>10)
#define SYS_CLOCK_ENABLE1_get_clk_en_aio(data)                                       ((0x00000400&(data))>>10)
#define SYS_CLOCK_ENABLE1_clk_en_etn_shift                                           (9)
#define SYS_CLOCK_ENABLE1_clk_en_etn_mask                                            (0x00000200)
#define SYS_CLOCK_ENABLE1_clk_en_etn(data)                                           (0x00000200&((data)<<9))
#define SYS_CLOCK_ENABLE1_clk_en_etn_src(data)                                       ((0x00000200&(data))>>9)
#define SYS_CLOCK_ENABLE1_get_clk_en_etn(data)                                       ((0x00000200&(data))>>9)
#define SYS_CLOCK_ENABLE1_clk_en_hdmi_shift                                          (8)
#define SYS_CLOCK_ENABLE1_clk_en_hdmi_mask                                           (0x00000100)
#define SYS_CLOCK_ENABLE1_clk_en_hdmi(data)                                          (0x00000100&((data)<<8))
#define SYS_CLOCK_ENABLE1_clk_en_hdmi_src(data)                                      ((0x00000100&(data))>>8)
#define SYS_CLOCK_ENABLE1_get_clk_en_hdmi(data)                                      ((0x00000100&(data))>>8)
#define SYS_CLOCK_ENABLE1_clk_en_sata_alive_0_shift                                  (7)
#define SYS_CLOCK_ENABLE1_clk_en_sata_alive_0_mask                                   (0x00000080)
#define SYS_CLOCK_ENABLE1_clk_en_sata_alive_0(data)                                  (0x00000080&((data)<<7))
#define SYS_CLOCK_ENABLE1_clk_en_sata_alive_0_src(data)                              ((0x00000080&(data))>>7)
#define SYS_CLOCK_ENABLE1_get_clk_en_sata_alive_0(data)                              ((0x00000080&(data))>>7)
#define SYS_CLOCK_ENABLE1_clk_en_iso_misc_shift                                      (6)
#define SYS_CLOCK_ENABLE1_clk_en_iso_misc_mask                                       (0x00000040)
#define SYS_CLOCK_ENABLE1_clk_en_iso_misc(data)                                      (0x00000040&((data)<<6))
#define SYS_CLOCK_ENABLE1_clk_en_iso_misc_src(data)                                  ((0x00000040&(data))>>6)
#define SYS_CLOCK_ENABLE1_get_clk_en_iso_misc(data)                                  ((0x00000040&(data))>>6)
#define SYS_CLOCK_ENABLE1_clk_en_pcr_shift                                           (5)
#define SYS_CLOCK_ENABLE1_clk_en_pcr_mask                                            (0x00000020)
#define SYS_CLOCK_ENABLE1_clk_en_pcr(data)                                           (0x00000020&((data)<<5))
#define SYS_CLOCK_ENABLE1_clk_en_pcr_src(data)                                       ((0x00000020&(data))>>5)
#define SYS_CLOCK_ENABLE1_get_clk_en_pcr(data)                                       ((0x00000020&(data))>>5)
#define SYS_CLOCK_ENABLE1_clk_en_usb_shift                                           (4)
#define SYS_CLOCK_ENABLE1_clk_en_usb_mask                                            (0x00000010)
#define SYS_CLOCK_ENABLE1_clk_en_usb(data)                                           (0x00000010&((data)<<4))
#define SYS_CLOCK_ENABLE1_clk_en_usb_src(data)                                       ((0x00000010&(data))>>4)
#define SYS_CLOCK_ENABLE1_get_clk_en_usb(data)                                       ((0x00000010&(data))>>4)
#define SYS_CLOCK_ENABLE1_clk_en_gspi_shift                                          (3)
#define SYS_CLOCK_ENABLE1_clk_en_gspi_mask                                           (0x00000008)
#define SYS_CLOCK_ENABLE1_clk_en_gspi(data)                                          (0x00000008&((data)<<3))
#define SYS_CLOCK_ENABLE1_clk_en_gspi_src(data)                                      ((0x00000008&(data))>>3)
#define SYS_CLOCK_ENABLE1_get_clk_en_gspi(data)                                      ((0x00000008&(data))>>3)
#define SYS_CLOCK_ENABLE1_clk_en_sata_0_shift                                        (2)
#define SYS_CLOCK_ENABLE1_clk_en_sata_0_mask                                         (0x00000004)
#define SYS_CLOCK_ENABLE1_clk_en_sata_0(data)                                        (0x00000004&((data)<<2))
#define SYS_CLOCK_ENABLE1_clk_en_sata_0_src(data)                                    ((0x00000004&(data))>>2)
#define SYS_CLOCK_ENABLE1_get_clk_en_sata_0(data)                                    ((0x00000004&(data))>>2)
#define SYS_CLOCK_ENABLE1_clk_en_pcie0_shift                                         (1)
#define SYS_CLOCK_ENABLE1_clk_en_pcie0_mask                                          (0x00000002)
#define SYS_CLOCK_ENABLE1_clk_en_pcie0(data)                                         (0x00000002&((data)<<1))
#define SYS_CLOCK_ENABLE1_clk_en_pcie0_src(data)                                     ((0x00000002&(data))>>1)
#define SYS_CLOCK_ENABLE1_get_clk_en_pcie0(data)                                     ((0x00000002&(data))>>1)
#define SYS_CLOCK_ENABLE1_clk_en_misc_shift                                          (0)
#define SYS_CLOCK_ENABLE1_clk_en_misc_mask                                           (0x00000001)
#define SYS_CLOCK_ENABLE1_clk_en_misc(data)                                          (0x00000001&((data)<<0))
#define SYS_CLOCK_ENABLE1_clk_en_misc_src(data)                                      ((0x00000001&(data))>>0)
#define SYS_CLOCK_ENABLE1_get_clk_en_misc(data)                                      ((0x00000001&(data))>>0)


#define SYS_CLOCK_ENABLE2                                                            0x98000010
#define SYS_CLOCK_ENABLE2_reg_addr                                                   "0x98000010"
#define SYS_CLOCK_ENABLE2_reg                                                        0x98000010
#define set_SYS_CLOCK_ENABLE2_reg(data)   (*((volatile unsigned int*) SYS_CLOCK_ENABLE2_reg)=data)
#define get_SYS_CLOCK_ENABLE2_reg   (*((volatile unsigned int*) SYS_CLOCK_ENABLE2_reg))
#define SYS_CLOCK_ENABLE2_inst_adr                                                   "0x0004"
#define SYS_CLOCK_ENABLE2_inst                                                       0x0004
#define SYS_CLOCK_ENABLE2_clk_en_dcphy_1_shift                                       (31)
#define SYS_CLOCK_ENABLE2_clk_en_dcphy_1_mask                                        (0x80000000)
#define SYS_CLOCK_ENABLE2_clk_en_dcphy_1(data)                                       (0x80000000&((data)<<31))
#define SYS_CLOCK_ENABLE2_clk_en_dcphy_1_src(data)                                   ((0x80000000&(data))>>31)
#define SYS_CLOCK_ENABLE2_get_clk_en_dcphy_1(data)                                   ((0x80000000&(data))>>31)
#define SYS_CLOCK_ENABLE2_clk_en_dcphy_0_shift                                       (30)
#define SYS_CLOCK_ENABLE2_clk_en_dcphy_0_mask                                        (0x40000000)
#define SYS_CLOCK_ENABLE2_clk_en_dcphy_0(data)                                       (0x40000000&((data)<<30))
#define SYS_CLOCK_ENABLE2_clk_en_dcphy_0_src(data)                                   ((0x40000000&(data))>>30)
#define SYS_CLOCK_ENABLE2_get_clk_en_dcphy_0(data)                                   ((0x40000000&(data))>>30)
#define SYS_CLOCK_ENABLE2_clk_en_fan_shift                                           (29)
#define SYS_CLOCK_ENABLE2_clk_en_fan_mask                                            (0x20000000)
#define SYS_CLOCK_ENABLE2_clk_en_fan(data)                                           (0x20000000&((data)<<29))
#define SYS_CLOCK_ENABLE2_clk_en_fan_src(data)                                       ((0x20000000&(data))>>29)
#define SYS_CLOCK_ENABLE2_get_clk_en_fan(data)                                       ((0x20000000&(data))>>29)
#define SYS_CLOCK_ENABLE2_clk_en_ur1_shift                                           (28)
#define SYS_CLOCK_ENABLE2_clk_en_ur1_mask                                            (0x10000000)
#define SYS_CLOCK_ENABLE2_clk_en_ur1(data)                                           (0x10000000&((data)<<28))
#define SYS_CLOCK_ENABLE2_clk_en_ur1_src(data)                                       ((0x10000000&(data))>>28)
#define SYS_CLOCK_ENABLE2_get_clk_en_ur1(data)                                       ((0x10000000&(data))>>28)
#define SYS_CLOCK_ENABLE2_clk_en_ur2_shift                                           (27)
#define SYS_CLOCK_ENABLE2_clk_en_ur2_mask                                            (0x08000000)
#define SYS_CLOCK_ENABLE2_clk_en_ur2(data)                                           (0x08000000&((data)<<27))
#define SYS_CLOCK_ENABLE2_clk_en_ur2_src(data)                                       ((0x08000000&(data))>>27)
#define SYS_CLOCK_ENABLE2_get_clk_en_ur2(data)                                       ((0x08000000&(data))>>27)
#define SYS_CLOCK_ENABLE2_clk_en_sata_alive_1_shift                                  (26)
#define SYS_CLOCK_ENABLE2_clk_en_sata_alive_1_mask                                   (0x04000000)
#define SYS_CLOCK_ENABLE2_clk_en_sata_alive_1(data)                                  (0x04000000&((data)<<26))
#define SYS_CLOCK_ENABLE2_clk_en_sata_alive_1_src(data)                              ((0x04000000&(data))>>26)
#define SYS_CLOCK_ENABLE2_get_clk_en_sata_alive_1(data)                              ((0x04000000&(data))>>26)
#define SYS_CLOCK_ENABLE2_clk_en_sata_1_shift                                        (25)
#define SYS_CLOCK_ENABLE2_clk_en_sata_1_mask                                         (0x02000000)
#define SYS_CLOCK_ENABLE2_clk_en_sata_1(data)                                        (0x02000000&((data)<<25))
#define SYS_CLOCK_ENABLE2_clk_en_sata_1_src(data)                                    ((0x02000000&(data))>>25)
#define SYS_CLOCK_ENABLE2_get_clk_en_sata_1(data)                                    ((0x02000000&(data))>>25)
#define SYS_CLOCK_ENABLE2_clk_en_hdmirx_shift                                        (24)
#define SYS_CLOCK_ENABLE2_clk_en_hdmirx_mask                                         (0x01000000)
#define SYS_CLOCK_ENABLE2_clk_en_hdmirx(data)                                        (0x01000000&((data)<<24))
#define SYS_CLOCK_ENABLE2_clk_en_hdmirx_src(data)                                    ((0x01000000&(data))>>24)
#define SYS_CLOCK_ENABLE2_get_clk_en_hdmirx(data)                                    ((0x01000000&(data))>>24)
#define SYS_CLOCK_ENABLE2_clk_en_aio_mclk_shift                                      (23)
#define SYS_CLOCK_ENABLE2_clk_en_aio_mclk_mask                                       (0x00800000)
#define SYS_CLOCK_ENABLE2_clk_en_aio_mclk(data)                                      (0x00800000&((data)<<23))
#define SYS_CLOCK_ENABLE2_clk_en_aio_mclk_src(data)                                  ((0x00800000&(data))>>23)
#define SYS_CLOCK_ENABLE2_get_clk_en_aio_mclk(data)                                  ((0x00800000&(data))>>23)
#define SYS_CLOCK_ENABLE2_clk_en_aio_i2s_shift                                       (22)
#define SYS_CLOCK_ENABLE2_clk_en_aio_i2s_mask                                        (0x00400000)
#define SYS_CLOCK_ENABLE2_clk_en_aio_i2s(data)                                       (0x00400000&((data)<<22))
#define SYS_CLOCK_ENABLE2_clk_en_aio_i2s_src(data)                                   ((0x00400000&(data))>>22)
#define SYS_CLOCK_ENABLE2_get_clk_en_aio_i2s(data)                                   ((0x00400000&(data))>>22)
#define SYS_CLOCK_ENABLE2_clk_en_aio_spdif_shift                                     (21)
#define SYS_CLOCK_ENABLE2_clk_en_aio_spdif_mask                                      (0x00200000)
#define SYS_CLOCK_ENABLE2_clk_en_aio_spdif(data)                                     (0x00200000&((data)<<21))
#define SYS_CLOCK_ENABLE2_clk_en_aio_spdif_src(data)                                 ((0x00200000&(data))>>21)
#define SYS_CLOCK_ENABLE2_get_clk_en_aio_spdif(data)                                 ((0x00200000&(data))>>21)
#define SYS_CLOCK_ENABLE2_clk_en_aio_hdmi_shift                                      (20)
#define SYS_CLOCK_ENABLE2_clk_en_aio_hdmi_mask                                       (0x00100000)
#define SYS_CLOCK_ENABLE2_clk_en_aio_hdmi(data)                                      (0x00100000&((data)<<20))
#define SYS_CLOCK_ENABLE2_clk_en_aio_hdmi_src(data)                                  ((0x00100000&(data))>>20)
#define SYS_CLOCK_ENABLE2_get_clk_en_aio_hdmi(data)                                  ((0x00100000&(data))>>20)
#define SYS_CLOCK_ENABLE2_clk_en_aio_da_shift                                        (19)
#define SYS_CLOCK_ENABLE2_clk_en_aio_da_mask                                         (0x00080000)
#define SYS_CLOCK_ENABLE2_clk_en_aio_da(data)                                        (0x00080000&((data)<<19))
#define SYS_CLOCK_ENABLE2_clk_en_aio_da_src(data)                                    ((0x00080000&(data))>>19)
#define SYS_CLOCK_ENABLE2_get_clk_en_aio_da(data)                                    ((0x00080000&(data))>>19)
#define SYS_CLOCK_ENABLE2_clk_en_aio_mod_shift                                       (18)
#define SYS_CLOCK_ENABLE2_clk_en_aio_mod_mask                                        (0x00040000)
#define SYS_CLOCK_ENABLE2_clk_en_aio_mod(data)                                       (0x00040000&((data)<<18))
#define SYS_CLOCK_ENABLE2_clk_en_aio_mod_src(data)                                   ((0x00040000&(data))>>18)
#define SYS_CLOCK_ENABLE2_get_clk_en_aio_mod(data)                                   ((0x00040000&(data))>>18)
#define SYS_CLOCK_ENABLE2_clk_en_aio_au_codec_shift                                  (17)
#define SYS_CLOCK_ENABLE2_clk_en_aio_au_codec_mask                                   (0x00020000)
#define SYS_CLOCK_ENABLE2_clk_en_aio_au_codec(data)                                  (0x00020000&((data)<<17))
#define SYS_CLOCK_ENABLE2_clk_en_aio_au_codec_src(data)                              ((0x00020000&(data))>>17)
#define SYS_CLOCK_ENABLE2_get_clk_en_aio_au_codec(data)                              ((0x00020000&(data))>>17)
#define SYS_CLOCK_ENABLE2_clk_en_misc_i2c_1_shift                                    (16)
#define SYS_CLOCK_ENABLE2_clk_en_misc_i2c_1_mask                                     (0x00010000)
#define SYS_CLOCK_ENABLE2_clk_en_misc_i2c_1(data)                                    (0x00010000&((data)<<16))
#define SYS_CLOCK_ENABLE2_clk_en_misc_i2c_1_src(data)                                ((0x00010000&(data))>>16)
#define SYS_CLOCK_ENABLE2_get_clk_en_misc_i2c_1(data)                                ((0x00010000&(data))>>16)
#define SYS_CLOCK_ENABLE2_clk_en_misc_i2c_2_shift                                    (15)
#define SYS_CLOCK_ENABLE2_clk_en_misc_i2c_2_mask                                     (0x00008000)
#define SYS_CLOCK_ENABLE2_clk_en_misc_i2c_2(data)                                    (0x00008000&((data)<<15))
#define SYS_CLOCK_ENABLE2_clk_en_misc_i2c_2_src(data)                                ((0x00008000&(data))>>15)
#define SYS_CLOCK_ENABLE2_get_clk_en_misc_i2c_2(data)                                ((0x00008000&(data))>>15)
#define SYS_CLOCK_ENABLE2_clk_en_misc_i2c_3_shift                                    (14)
#define SYS_CLOCK_ENABLE2_clk_en_misc_i2c_3_mask                                     (0x00004000)
#define SYS_CLOCK_ENABLE2_clk_en_misc_i2c_3(data)                                    (0x00004000&((data)<<14))
#define SYS_CLOCK_ENABLE2_clk_en_misc_i2c_3_src(data)                                ((0x00004000&(data))>>14)
#define SYS_CLOCK_ENABLE2_get_clk_en_misc_i2c_3(data)                                ((0x00004000&(data))>>14)
#define SYS_CLOCK_ENABLE2_clk_en_misc_i2c_4_shift                                    (13)
#define SYS_CLOCK_ENABLE2_clk_en_misc_i2c_4_mask                                     (0x00002000)
#define SYS_CLOCK_ENABLE2_clk_en_misc_i2c_4(data)                                    (0x00002000&((data)<<13))
#define SYS_CLOCK_ENABLE2_clk_en_misc_i2c_4_src(data)                                ((0x00002000&(data))>>13)
#define SYS_CLOCK_ENABLE2_get_clk_en_misc_i2c_4(data)                                ((0x00002000&(data))>>13)
#define SYS_CLOCK_ENABLE2_clk_en_misc_rtc_shift                                      (10)
#define SYS_CLOCK_ENABLE2_clk_en_misc_rtc_mask                                       (0x00000400)
#define SYS_CLOCK_ENABLE2_clk_en_misc_rtc(data)                                      (0x00000400&((data)<<10))
#define SYS_CLOCK_ENABLE2_clk_en_misc_rtc_src(data)                                  ((0x00000400&(data))>>10)
#define SYS_CLOCK_ENABLE2_get_clk_en_misc_rtc(data)                                  ((0x00000400&(data))>>10)
#define SYS_CLOCK_ENABLE2_clk_en_cbus_tx_shift                                       (7)
#define SYS_CLOCK_ENABLE2_clk_en_cbus_tx_mask                                        (0x00000080)
#define SYS_CLOCK_ENABLE2_clk_en_cbus_tx(data)                                       (0x00000080&((data)<<7))
#define SYS_CLOCK_ENABLE2_clk_en_cbus_tx_src(data)                                   ((0x00000080&(data))>>7)
#define SYS_CLOCK_ENABLE2_get_clk_en_cbus_tx(data)                                   ((0x00000080&(data))>>7)
#define SYS_CLOCK_ENABLE2_clk_en_misc_sc_shift                                       (6)
#define SYS_CLOCK_ENABLE2_clk_en_misc_sc_mask                                        (0x00000040)
#define SYS_CLOCK_ENABLE2_clk_en_misc_sc(data)                                       (0x00000040&((data)<<6))
#define SYS_CLOCK_ENABLE2_clk_en_misc_sc_src(data)                                   ((0x00000040&(data))>>6)
#define SYS_CLOCK_ENABLE2_get_clk_en_misc_sc(data)                                   ((0x00000040&(data))>>6)
#define SYS_CLOCK_ENABLE2_clk_en_pcie1_shift                                         (5)
#define SYS_CLOCK_ENABLE2_clk_en_pcie1_mask                                          (0x00000020)
#define SYS_CLOCK_ENABLE2_clk_en_pcie1(data)                                         (0x00000020&((data)<<5))
#define SYS_CLOCK_ENABLE2_clk_en_pcie1_src(data)                                     ((0x00000020&(data))>>5)
#define SYS_CLOCK_ENABLE2_get_clk_en_pcie1(data)                                     ((0x00000020&(data))>>5)
#define SYS_CLOCK_ENABLE2_clk_en_acpu_shift                                          (4)
#define SYS_CLOCK_ENABLE2_clk_en_acpu_mask                                           (0x00000010)
#define SYS_CLOCK_ENABLE2_clk_en_acpu(data)                                          (0x00000010&((data)<<4))
#define SYS_CLOCK_ENABLE2_clk_en_acpu_src(data)                                      ((0x00000010&(data))>>4)
#define SYS_CLOCK_ENABLE2_get_clk_en_acpu(data)                                      ((0x00000010&(data))>>4)
#define SYS_CLOCK_ENABLE2_clk_en_jpeg_shift                                          (3)
#define SYS_CLOCK_ENABLE2_clk_en_jpeg_mask                                           (0x00000008)
#define SYS_CLOCK_ENABLE2_clk_en_jpeg(data)                                          (0x00000008&((data)<<3))
#define SYS_CLOCK_ENABLE2_clk_en_jpeg_src(data)                                      ((0x00000008&(data))>>3)
#define SYS_CLOCK_ENABLE2_get_clk_en_jpeg(data)                                      ((0x00000008&(data))>>3)
#define SYS_CLOCK_ENABLE2_clk_en_scpu_shift                                          (2)
#define SYS_CLOCK_ENABLE2_clk_en_scpu_mask                                           (0x00000004)
#define SYS_CLOCK_ENABLE2_clk_en_scpu(data)                                          (0x00000004&((data)<<2))
#define SYS_CLOCK_ENABLE2_clk_en_scpu_src(data)                                      ((0x00000004&(data))>>2)
#define SYS_CLOCK_ENABLE2_get_clk_en_scpu(data)                                      ((0x00000004&(data))>>2)
#define SYS_CLOCK_ENABLE2_clk_en_misc_i2c_5_shift                                    (1)
#define SYS_CLOCK_ENABLE2_clk_en_misc_i2c_5_mask                                     (0x00000002)
#define SYS_CLOCK_ENABLE2_clk_en_misc_i2c_5(data)                                    (0x00000002&((data)<<1))
#define SYS_CLOCK_ENABLE2_clk_en_misc_i2c_5_src(data)                                ((0x00000002&(data))>>1)
#define SYS_CLOCK_ENABLE2_get_clk_en_misc_i2c_5(data)                                ((0x00000002&(data))>>1)
#define SYS_CLOCK_ENABLE2_clk_en_nat_shift                                           (0)
#define SYS_CLOCK_ENABLE2_clk_en_nat_mask                                            (0x00000001)
#define SYS_CLOCK_ENABLE2_clk_en_nat(data)                                           (0x00000001&((data)<<0))
#define SYS_CLOCK_ENABLE2_clk_en_nat_src(data)                                       ((0x00000001&(data))>>0)
#define SYS_CLOCK_ENABLE2_get_clk_en_nat(data)                                       ((0x00000001&(data))>>0)


#define SYS_GROUP1_CK_EN                                                             0x98000014
#define SYS_GROUP1_CK_EN_reg_addr                                                    "0x98000014"
#define SYS_GROUP1_CK_EN_reg                                                         0x98000014
#define set_SYS_GROUP1_CK_EN_reg(data)   (*((volatile unsigned int*) SYS_GROUP1_CK_EN_reg)=data)
#define get_SYS_GROUP1_CK_EN_reg   (*((volatile unsigned int*) SYS_GROUP1_CK_EN_reg))
#define SYS_GROUP1_CK_EN_inst_adr                                                    "0x0005"
#define SYS_GROUP1_CK_EN_inst                                                        0x0005
#define SYS_GROUP1_CK_EN_reserved_group1_ck_en_shift                                 (0)
#define SYS_GROUP1_CK_EN_reserved_group1_ck_en_mask                                  (0x00000001)
#define SYS_GROUP1_CK_EN_reserved_group1_ck_en(data)                                 (0x00000001&((data)<<0))
#define SYS_GROUP1_CK_EN_reserved_group1_ck_en_src(data)                             ((0x00000001&(data))>>0)
#define SYS_GROUP1_CK_EN_get_reserved_group1_ck_en(data)                             ((0x00000001&(data))>>0)


#define SYS_GROUP1_CK_SEL                                                            0x98000018
#define SYS_GROUP1_CK_SEL_reg_addr                                                   "0x98000018"
#define SYS_GROUP1_CK_SEL_reg                                                        0x98000018
#define set_SYS_GROUP1_CK_SEL_reg(data)   (*((volatile unsigned int*) SYS_GROUP1_CK_SEL_reg)=data)
#define get_SYS_GROUP1_CK_SEL_reg   (*((volatile unsigned int*) SYS_GROUP1_CK_SEL_reg))
#define SYS_GROUP1_CK_SEL_inst_adr                                                   "0x0006"
#define SYS_GROUP1_CK_SEL_inst                                                       0x0006
#define SYS_GROUP1_CK_SEL_scpu_sclk_sel_shift                                        (2)
#define SYS_GROUP1_CK_SEL_scpu_sclk_sel_mask                                         (0x00000004)
#define SYS_GROUP1_CK_SEL_scpu_sclk_sel(data)                                        (0x00000004&((data)<<2))
#define SYS_GROUP1_CK_SEL_scpu_sclk_sel_src(data)                                    ((0x00000004&(data))>>2)
#define SYS_GROUP1_CK_SEL_get_scpu_sclk_sel(data)                                    ((0x00000004&(data))>>2)
#define SYS_GROUP1_CK_SEL_sclk_sel_sysh_shift                                        (1)
#define SYS_GROUP1_CK_SEL_sclk_sel_sysh_mask                                         (0x00000002)
#define SYS_GROUP1_CK_SEL_sclk_sel_sysh(data)                                        (0x00000002&((data)<<1))
#define SYS_GROUP1_CK_SEL_sclk_sel_sysh_src(data)                                    ((0x00000002&(data))>>1)
#define SYS_GROUP1_CK_SEL_get_sclk_sel_sysh(data)                                    ((0x00000002&(data))>>1)
#define SYS_GROUP1_CK_SEL_sclk_sel_shift                                             (0)
#define SYS_GROUP1_CK_SEL_sclk_sel_mask                                              (0x00000001)
#define SYS_GROUP1_CK_SEL_sclk_sel(data)                                             (0x00000001&((data)<<0))
#define SYS_GROUP1_CK_SEL_sclk_sel_src(data)                                         ((0x00000001&(data))>>0)
#define SYS_GROUP1_CK_SEL_get_sclk_sel(data)                                         ((0x00000001&(data))>>0)


#define SYS_TVE_CK_SEL                                                               0x9800001C
#define SYS_TVE_CK_SEL_reg_addr                                                      "0x9800001C"
#define SYS_TVE_CK_SEL_reg                                                           0x9800001C
#define set_SYS_TVE_CK_SEL_reg(data)   (*((volatile unsigned int*) SYS_TVE_CK_SEL_reg)=data)
#define get_SYS_TVE_CK_SEL_reg   (*((volatile unsigned int*) SYS_TVE_CK_SEL_reg))
#define SYS_TVE_CK_SEL_inst_adr                                                      "0x0007"
#define SYS_TVE_CK_SEL_inst                                                          0x0007
#define SYS_TVE_CK_SEL_write_en5_shift                                               (12)
#define SYS_TVE_CK_SEL_write_en5_mask                                                (0x00001000)
#define SYS_TVE_CK_SEL_write_en5(data)                                               (0x00001000&((data)<<12))
#define SYS_TVE_CK_SEL_write_en5_src(data)                                           ((0x00001000&(data))>>12)
#define SYS_TVE_CK_SEL_get_write_en5(data)                                           ((0x00001000&(data))>>12)
#define SYS_TVE_CK_SEL_clk_tve_p_vo_clk_sel2_shift                                   (11)
#define SYS_TVE_CK_SEL_clk_tve_p_vo_clk_sel2_mask                                    (0x00000800)
#define SYS_TVE_CK_SEL_clk_tve_p_vo_clk_sel2(data)                                   (0x00000800&((data)<<11))
#define SYS_TVE_CK_SEL_clk_tve_p_vo_clk_sel2_src(data)                               ((0x00000800&(data))>>11)
#define SYS_TVE_CK_SEL_get_clk_tve_p_vo_clk_sel2(data)                               ((0x00000800&(data))>>11)
#define SYS_TVE_CK_SEL_write_en4_shift                                               (10)
#define SYS_TVE_CK_SEL_write_en4_mask                                                (0x00000400)
#define SYS_TVE_CK_SEL_write_en4(data)                                               (0x00000400&((data)<<10))
#define SYS_TVE_CK_SEL_write_en4_src(data)                                           ((0x00000400&(data))>>10)
#define SYS_TVE_CK_SEL_get_write_en4(data)                                           ((0x00000400&(data))>>10)
#define SYS_TVE_CK_SEL_clk_tve_p_vo_clk_sel_shift                                    (9)
#define SYS_TVE_CK_SEL_clk_tve_p_vo_clk_sel_mask                                     (0x00000200)
#define SYS_TVE_CK_SEL_clk_tve_p_vo_clk_sel(data)                                    (0x00000200&((data)<<9))
#define SYS_TVE_CK_SEL_clk_tve_p_vo_clk_sel_src(data)                                ((0x00000200&(data))>>9)
#define SYS_TVE_CK_SEL_get_clk_tve_p_vo_clk_sel(data)                                ((0x00000200&(data))>>9)
#define SYS_TVE_CK_SEL_write_en3_shift                                               (8)
#define SYS_TVE_CK_SEL_write_en3_mask                                                (0x00000100)
#define SYS_TVE_CK_SEL_write_en3(data)                                               (0x00000100&((data)<<8))
#define SYS_TVE_CK_SEL_write_en3_src(data)                                           ((0x00000100&(data))>>8)
#define SYS_TVE_CK_SEL_get_write_en3(data)                                           ((0x00000100&(data))>>8)
#define SYS_TVE_CK_SEL_hdmi_phy_ckinv_shift                                          (7)
#define SYS_TVE_CK_SEL_hdmi_phy_ckinv_mask                                           (0x00000080)
#define SYS_TVE_CK_SEL_hdmi_phy_ckinv(data)                                          (0x00000080&((data)<<7))
#define SYS_TVE_CK_SEL_hdmi_phy_ckinv_src(data)                                      ((0x00000080&(data))>>7)
#define SYS_TVE_CK_SEL_get_hdmi_phy_ckinv(data)                                      ((0x00000080&(data))>>7)
#define SYS_TVE_CK_SEL_write_en2_shift                                               (6)
#define SYS_TVE_CK_SEL_write_en2_mask                                                (0x00000040)
#define SYS_TVE_CK_SEL_write_en2(data)                                               (0x00000040&((data)<<6))
#define SYS_TVE_CK_SEL_write_en2_src(data)                                           ((0x00000040&(data))>>6)
#define SYS_TVE_CK_SEL_get_write_en2(data)                                           ((0x00000040&(data))>>6)
#define SYS_TVE_CK_SEL_dac2_ckinv_shift                                              (3)
#define SYS_TVE_CK_SEL_dac2_ckinv_mask                                               (0x00000008)
#define SYS_TVE_CK_SEL_dac2_ckinv(data)                                              (0x00000008&((data)<<3))
#define SYS_TVE_CK_SEL_dac2_ckinv_src(data)                                          ((0x00000008&(data))>>3)
#define SYS_TVE_CK_SEL_get_dac2_ckinv(data)                                          ((0x00000008&(data))>>3)
#define SYS_TVE_CK_SEL_dac1_ckinv_shift                                              (2)
#define SYS_TVE_CK_SEL_dac1_ckinv_mask                                               (0x00000004)
#define SYS_TVE_CK_SEL_dac1_ckinv(data)                                              (0x00000004&((data)<<2))
#define SYS_TVE_CK_SEL_dac1_ckinv_src(data)                                          ((0x00000004&(data))>>2)
#define SYS_TVE_CK_SEL_get_dac1_ckinv(data)                                          ((0x00000004&(data))>>2)
#define SYS_TVE_CK_SEL_write_en1_shift                                               (1)
#define SYS_TVE_CK_SEL_write_en1_mask                                                (0x00000002)
#define SYS_TVE_CK_SEL_write_en1(data)                                               (0x00000002&((data)<<1))
#define SYS_TVE_CK_SEL_write_en1_src(data)                                           ((0x00000002&(data))>>1)
#define SYS_TVE_CK_SEL_get_write_en1(data)                                           ((0x00000002&(data))>>1)
#define SYS_TVE_CK_SEL_tveck_mix_sel_shift                                           (0)
#define SYS_TVE_CK_SEL_tveck_mix_sel_mask                                            (0x00000001)
#define SYS_TVE_CK_SEL_tveck_mix_sel(data)                                           (0x00000001&((data)<<0))
#define SYS_TVE_CK_SEL_tveck_mix_sel_src(data)                                       ((0x00000001&(data))>>0)
#define SYS_TVE_CK_SEL_get_tveck_mix_sel(data)                                       ((0x00000001&(data))>>0)


#define SYS_DISP_PLL_DIV                                                             0x98000020
#define SYS_DISP_PLL_DIV_reg_addr                                                    "0x98000020"
#define SYS_DISP_PLL_DIV_reg                                                         0x98000020
#define set_SYS_DISP_PLL_DIV_reg(data)   (*((volatile unsigned int*) SYS_DISP_PLL_DIV_reg)=data)
#define get_SYS_DISP_PLL_DIV_reg   (*((volatile unsigned int*) SYS_DISP_PLL_DIV_reg))
#define SYS_DISP_PLL_DIV_inst_adr                                                    "0x0008"
#define SYS_DISP_PLL_DIV_inst                                                        0x0008
#define SYS_DISP_PLL_DIV_write_en2_shift                                             (11)
#define SYS_DISP_PLL_DIV_write_en2_mask                                              (0x00000800)
#define SYS_DISP_PLL_DIV_write_en2(data)                                             (0x00000800&((data)<<11))
#define SYS_DISP_PLL_DIV_write_en2_src(data)                                         ((0x00000800&(data))>>11)
#define SYS_DISP_PLL_DIV_get_write_en2(data)                                         ((0x00000800&(data))>>11)
#define SYS_DISP_PLL_DIV_dac2_div_shift                                              (6)
#define SYS_DISP_PLL_DIV_dac2_div_mask                                               (0x000007C0)
#define SYS_DISP_PLL_DIV_dac2_div(data)                                              (0x000007C0&((data)<<6))
#define SYS_DISP_PLL_DIV_dac2_div_src(data)                                          ((0x000007C0&(data))>>6)
#define SYS_DISP_PLL_DIV_get_dac2_div(data)                                          ((0x000007C0&(data))>>6)
#define SYS_DISP_PLL_DIV_write_en1_shift                                             (5)
#define SYS_DISP_PLL_DIV_write_en1_mask                                              (0x00000020)
#define SYS_DISP_PLL_DIV_write_en1(data)                                             (0x00000020&((data)<<5))
#define SYS_DISP_PLL_DIV_write_en1_src(data)                                         ((0x00000020&(data))>>5)
#define SYS_DISP_PLL_DIV_get_write_en1(data)                                         ((0x00000020&(data))>>5)
#define SYS_DISP_PLL_DIV_dac1_div_shift                                              (0)
#define SYS_DISP_PLL_DIV_dac1_div_mask                                               (0x0000001F)
#define SYS_DISP_PLL_DIV_dac1_div(data)                                              (0x0000001F&((data)<<0))
#define SYS_DISP_PLL_DIV_dac1_div_src(data)                                          ((0x0000001F&(data))>>0)
#define SYS_DISP_PLL_DIV_get_dac1_div(data)                                          ((0x0000001F&(data))>>0)


#define SYS_DISP_PLL_DIV2                                                            0x98000024
#define SYS_DISP_PLL_DIV2_reg_addr                                                   "0x98000024"
#define SYS_DISP_PLL_DIV2_reg                                                        0x98000024
#define set_SYS_DISP_PLL_DIV2_reg(data)   (*((volatile unsigned int*) SYS_DISP_PLL_DIV2_reg)=data)
#define get_SYS_DISP_PLL_DIV2_reg   (*((volatile unsigned int*) SYS_DISP_PLL_DIV2_reg))
#define SYS_DISP_PLL_DIV2_inst_adr                                                   "0x0009"
#define SYS_DISP_PLL_DIV2_inst                                                       0x0009
#define SYS_DISP_PLL_DIV2_write_en11_shift                                           (26)
#define SYS_DISP_PLL_DIV2_write_en11_mask                                            (0x04000000)
#define SYS_DISP_PLL_DIV2_write_en11(data)                                           (0x04000000&((data)<<26))
#define SYS_DISP_PLL_DIV2_write_en11_src(data)                                       ((0x04000000&(data))>>26)
#define SYS_DISP_PLL_DIV2_get_write_en11(data)                                       ((0x04000000&(data))>>26)
#define SYS_DISP_PLL_DIV2_sel_prefifo_din_shift                                      (25)
#define SYS_DISP_PLL_DIV2_sel_prefifo_din_mask                                       (0x02000000)
#define SYS_DISP_PLL_DIV2_sel_prefifo_din(data)                                      (0x02000000&((data)<<25))
#define SYS_DISP_PLL_DIV2_sel_prefifo_din_src(data)                                  ((0x02000000&(data))>>25)
#define SYS_DISP_PLL_DIV2_get_sel_prefifo_din(data)                                  ((0x02000000&(data))>>25)
#define SYS_DISP_PLL_DIV2_write_en10_shift                                           (24)
#define SYS_DISP_PLL_DIV2_write_en10_mask                                            (0x01000000)
#define SYS_DISP_PLL_DIV2_write_en10(data)                                           (0x01000000&((data)<<24))
#define SYS_DISP_PLL_DIV2_write_en10_src(data)                                       ((0x01000000&(data))>>24)
#define SYS_DISP_PLL_DIV2_get_write_en10(data)                                       ((0x01000000&(data))>>24)
#define SYS_DISP_PLL_DIV2_sel_pllhdmi_mhl_shift                                      (23)
#define SYS_DISP_PLL_DIV2_sel_pllhdmi_mhl_mask                                       (0x00800000)
#define SYS_DISP_PLL_DIV2_sel_pllhdmi_mhl(data)                                      (0x00800000&((data)<<23))
#define SYS_DISP_PLL_DIV2_sel_pllhdmi_mhl_src(data)                                  ((0x00800000&(data))>>23)
#define SYS_DISP_PLL_DIV2_get_sel_pllhdmi_mhl(data)                                  ((0x00800000&(data))>>23)
#define SYS_DISP_PLL_DIV2_write_en9_shift                                            (22)
#define SYS_DISP_PLL_DIV2_write_en9_mask                                             (0x00400000)
#define SYS_DISP_PLL_DIV2_write_en9(data)                                            (0x00400000&((data)<<22))
#define SYS_DISP_PLL_DIV2_write_en9_src(data)                                        ((0x00400000&(data))>>22)
#define SYS_DISP_PLL_DIV2_get_write_en9(data)                                        ((0x00400000&(data))>>22)
#define SYS_DISP_PLL_DIV2_clk_lvds_sel_shift                                         (17)
#define SYS_DISP_PLL_DIV2_clk_lvds_sel_mask                                          (0x003E0000)
#define SYS_DISP_PLL_DIV2_clk_lvds_sel(data)                                         (0x003E0000&((data)<<17))
#define SYS_DISP_PLL_DIV2_clk_lvds_sel_src(data)                                     ((0x003E0000&(data))>>17)
#define SYS_DISP_PLL_DIV2_get_clk_lvds_sel(data)                                     ((0x003E0000&(data))>>17)
#define SYS_DISP_PLL_DIV2_write_en8_shift                                            (16)
#define SYS_DISP_PLL_DIV2_write_en8_mask                                             (0x00010000)
#define SYS_DISP_PLL_DIV2_write_en8(data)                                            (0x00010000&((data)<<16))
#define SYS_DISP_PLL_DIV2_write_en8_src(data)                                        ((0x00010000&(data))>>16)
#define SYS_DISP_PLL_DIV2_get_write_en8(data)                                        ((0x00010000&(data))>>16)
#define SYS_DISP_PLL_DIV2_sel_plldisp_clk2_shift                                     (15)
#define SYS_DISP_PLL_DIV2_sel_plldisp_clk2_mask                                      (0x00008000)
#define SYS_DISP_PLL_DIV2_sel_plldisp_clk2(data)                                     (0x00008000&((data)<<15))
#define SYS_DISP_PLL_DIV2_sel_plldisp_clk2_src(data)                                 ((0x00008000&(data))>>15)
#define SYS_DISP_PLL_DIV2_get_sel_plldisp_clk2(data)                                 ((0x00008000&(data))>>15)
#define SYS_DISP_PLL_DIV2_write_en7_shift                                            (14)
#define SYS_DISP_PLL_DIV2_write_en7_mask                                             (0x00004000)
#define SYS_DISP_PLL_DIV2_write_en7(data)                                            (0x00004000&((data)<<14))
#define SYS_DISP_PLL_DIV2_write_en7_src(data)                                        ((0x00004000&(data))>>14)
#define SYS_DISP_PLL_DIV2_get_write_en7(data)                                        ((0x00004000&(data))>>14)
#define SYS_DISP_PLL_DIV2_sel_pllhdmi_clk_shift                                      (13)
#define SYS_DISP_PLL_DIV2_sel_pllhdmi_clk_mask                                       (0x00002000)
#define SYS_DISP_PLL_DIV2_sel_pllhdmi_clk(data)                                      (0x00002000&((data)<<13))
#define SYS_DISP_PLL_DIV2_sel_pllhdmi_clk_src(data)                                  ((0x00002000&(data))>>13)
#define SYS_DISP_PLL_DIV2_get_sel_pllhdmi_clk(data)                                  ((0x00002000&(data))>>13)
#define SYS_DISP_PLL_DIV2_write_en6_shift                                            (12)
#define SYS_DISP_PLL_DIV2_write_en6_mask                                             (0x00001000)
#define SYS_DISP_PLL_DIV2_write_en6(data)                                            (0x00001000&((data)<<12))
#define SYS_DISP_PLL_DIV2_write_en6_src(data)                                        ((0x00001000&(data))>>12)
#define SYS_DISP_PLL_DIV2_get_write_en6(data)                                        ((0x00001000&(data))>>12)
#define SYS_DISP_PLL_DIV2_hdmi_pxl_repeat_shift                                      (11)
#define SYS_DISP_PLL_DIV2_hdmi_pxl_repeat_mask                                       (0x00000800)
#define SYS_DISP_PLL_DIV2_hdmi_pxl_repeat(data)                                      (0x00000800&((data)<<11))
#define SYS_DISP_PLL_DIV2_hdmi_pxl_repeat_src(data)                                  ((0x00000800&(data))>>11)
#define SYS_DISP_PLL_DIV2_get_hdmi_pxl_repeat(data)                                  ((0x00000800&(data))>>11)
#define SYS_DISP_PLL_DIV2_write_en5_shift                                            (10)
#define SYS_DISP_PLL_DIV2_write_en5_mask                                             (0x00000400)
#define SYS_DISP_PLL_DIV2_write_en5(data)                                            (0x00000400&((data)<<10))
#define SYS_DISP_PLL_DIV2_write_en5_src(data)                                        ((0x00000400&(data))>>10)
#define SYS_DISP_PLL_DIV2_get_write_en5(data)                                        ((0x00000400&(data))>>10)
#define SYS_DISP_PLL_DIV2_hdmi_phy_clk_sel_shift                                     (9)
#define SYS_DISP_PLL_DIV2_hdmi_phy_clk_sel_mask                                      (0x00000200)
#define SYS_DISP_PLL_DIV2_hdmi_phy_clk_sel(data)                                     (0x00000200&((data)<<9))
#define SYS_DISP_PLL_DIV2_hdmi_phy_clk_sel_src(data)                                 ((0x00000200&(data))>>9)
#define SYS_DISP_PLL_DIV2_get_hdmi_phy_clk_sel(data)                                 ((0x00000200&(data))>>9)
#define SYS_DISP_PLL_DIV2_write_en4_shift                                            (8)
#define SYS_DISP_PLL_DIV2_write_en4_mask                                             (0x00000100)
#define SYS_DISP_PLL_DIV2_write_en4(data)                                            (0x00000100&((data)<<8))
#define SYS_DISP_PLL_DIV2_write_en4_src(data)                                        ((0x00000100&(data))>>8)
#define SYS_DISP_PLL_DIV2_get_write_en4(data)                                        ((0x00000100&(data))>>8)
#define SYS_DISP_PLL_DIV2_hdmi_div_shift                                             (5)
#define SYS_DISP_PLL_DIV2_hdmi_div_mask                                              (0x000000E0)
#define SYS_DISP_PLL_DIV2_hdmi_div(data)                                             (0x000000E0&((data)<<5))
#define SYS_DISP_PLL_DIV2_hdmi_div_src(data)                                         ((0x000000E0&(data))>>5)
#define SYS_DISP_PLL_DIV2_get_hdmi_div(data)                                         ((0x000000E0&(data))>>5)
#define SYS_DISP_PLL_DIV2_write_en3_shift                                            (4)
#define SYS_DISP_PLL_DIV2_write_en3_mask                                             (0x00000010)
#define SYS_DISP_PLL_DIV2_write_en3(data)                                            (0x00000010&((data)<<4))
#define SYS_DISP_PLL_DIV2_write_en3_src(data)                                        ((0x00000010&(data))>>4)
#define SYS_DISP_PLL_DIV2_get_write_en3(data)                                        ((0x00000010&(data))>>4)
#define SYS_DISP_PLL_DIV2_tve_div_shift                                              (0)
#define SYS_DISP_PLL_DIV2_tve_div_mask                                               (0x0000000F)
#define SYS_DISP_PLL_DIV2_tve_div(data)                                              (0x0000000F&((data)<<0))
#define SYS_DISP_PLL_DIV2_tve_div_src(data)                                          ((0x0000000F&(data))>>0)
#define SYS_DISP_PLL_DIV2_get_tve_div(data)                                          ((0x0000000F&(data))>>0)


#define SYS_DDS_VIDEO_CK_SEL                                                         0x98000028
#define SYS_DDS_VIDEO_CK_SEL_reg_addr                                                "0x98000028"
#define SYS_DDS_VIDEO_CK_SEL_reg                                                     0x98000028
#define set_SYS_DDS_VIDEO_CK_SEL_reg(data)   (*((volatile unsigned int*) SYS_DDS_VIDEO_CK_SEL_reg)=data)
#define get_SYS_DDS_VIDEO_CK_SEL_reg   (*((volatile unsigned int*) SYS_DDS_VIDEO_CK_SEL_reg))
#define SYS_DDS_VIDEO_CK_SEL_inst_adr                                                "0x000A"
#define SYS_DDS_VIDEO_CK_SEL_inst                                                    0x000A
#define SYS_DDS_VIDEO_CK_SEL_nat_clk_sel_shift                                       (1)
#define SYS_DDS_VIDEO_CK_SEL_nat_clk_sel_mask                                        (0x00000002)
#define SYS_DDS_VIDEO_CK_SEL_nat_clk_sel(data)                                       (0x00000002&((data)<<1))
#define SYS_DDS_VIDEO_CK_SEL_nat_clk_sel_src(data)                                   ((0x00000002&(data))>>1)
#define SYS_DDS_VIDEO_CK_SEL_get_nat_clk_sel(data)                                   ((0x00000002&(data))>>1)
#define SYS_DDS_VIDEO_CK_SEL_dds_clk_sel_shift                                       (0)
#define SYS_DDS_VIDEO_CK_SEL_dds_clk_sel_mask                                        (0x00000001)
#define SYS_DDS_VIDEO_CK_SEL_dds_clk_sel(data)                                       (0x00000001&((data)<<0))
#define SYS_DDS_VIDEO_CK_SEL_dds_clk_sel_src(data)                                   ((0x00000001&(data))>>0)
#define SYS_DDS_VIDEO_CK_SEL_get_dds_clk_sel(data)                                   ((0x00000001&(data))>>0)


#define SYS_AUDIO_CLK_CTL                                                            0x9800002C
#define SYS_AUDIO_CLK_CTL_reg_addr                                                   "0x9800002C"
#define SYS_AUDIO_CLK_CTL_reg                                                        0x9800002C
#define set_SYS_AUDIO_CLK_CTL_reg(data)   (*((volatile unsigned int*) SYS_AUDIO_CLK_CTL_reg)=data)
#define get_SYS_AUDIO_CLK_CTL_reg   (*((volatile unsigned int*) SYS_AUDIO_CLK_CTL_reg))
#define SYS_AUDIO_CLK_CTL_inst_adr                                                   "0x000B"
#define SYS_AUDIO_CLK_CTL_inst                                                       0x000B
#define SYS_AUDIO_CLK_CTL_mipi_div_shift                                             (4)
#define SYS_AUDIO_CLK_CTL_mipi_div_mask                                              (0x00000030)
#define SYS_AUDIO_CLK_CTL_mipi_div(data)                                             (0x00000030&((data)<<4))
#define SYS_AUDIO_CLK_CTL_mipi_div_src(data)                                         ((0x00000030&(data))>>4)
#define SYS_AUDIO_CLK_CTL_get_mipi_div(data)                                         ((0x00000030&(data))>>4)
#define SYS_AUDIO_CLK_CTL_vo_div_shift                                               (2)
#define SYS_AUDIO_CLK_CTL_vo_div_mask                                                (0x0000000C)
#define SYS_AUDIO_CLK_CTL_vo_div(data)                                               (0x0000000C&((data)<<2))
#define SYS_AUDIO_CLK_CTL_vo_div_src(data)                                           ((0x0000000C&(data))>>2)
#define SYS_AUDIO_CLK_CTL_get_vo_div(data)                                           ((0x0000000C&(data))>>2)
#define SYS_AUDIO_CLK_CTL_audio_use_sysclk_shift                                     (0)
#define SYS_AUDIO_CLK_CTL_audio_use_sysclk_mask                                      (0x00000001)
#define SYS_AUDIO_CLK_CTL_audio_use_sysclk(data)                                     (0x00000001&((data)<<0))
#define SYS_AUDIO_CLK_CTL_audio_use_sysclk_src(data)                                 ((0x00000001&(data))>>0)
#define SYS_AUDIO_CLK_CTL_get_audio_use_sysclk(data)                                 ((0x00000001&(data))>>0)


#define SYS_PLL_DIV                                                                  0x98000030
#define SYS_PLL_DIV_reg_addr                                                         "0x98000030"
#define SYS_PLL_DIV_reg                                                              0x98000030
#define set_SYS_PLL_DIV_reg(data)   (*((volatile unsigned int*) SYS_PLL_DIV_reg)=data)
#define get_SYS_PLL_DIV_reg   (*((volatile unsigned int*) SYS_PLL_DIV_reg))
#define SYS_PLL_DIV_inst_adr                                                         "0x000C"
#define SYS_PLL_DIV_inst                                                             0x000C
#define SYS_PLL_DIV_scpu_freq_sel_shift                                              (7)
#define SYS_PLL_DIV_scpu_freq_sel_mask                                               (0x00000180)
#define SYS_PLL_DIV_scpu_freq_sel(data)                                              (0x00000180&((data)<<7))
#define SYS_PLL_DIV_scpu_freq_sel_src(data)                                          ((0x00000180&(data))>>7)
#define SYS_PLL_DIV_get_scpu_freq_sel(data)                                          ((0x00000180&(data))>>7)
#define SYS_PLL_DIV_acpu_freq_sel_shift                                              (3)
#define SYS_PLL_DIV_acpu_freq_sel_mask                                               (0x00000018)
#define SYS_PLL_DIV_acpu_freq_sel(data)                                              (0x00000018&((data)<<3))
#define SYS_PLL_DIV_acpu_freq_sel_src(data)                                          ((0x00000018&(data))>>3)
#define SYS_PLL_DIV_get_acpu_freq_sel(data)                                          ((0x00000018&(data))>>3)
#define SYS_PLL_DIV_bus_freq_sel_shift                                               (0)
#define SYS_PLL_DIV_bus_freq_sel_mask                                                (0x00000001)
#define SYS_PLL_DIV_bus_freq_sel(data)                                               (0x00000001&((data)<<0))
#define SYS_PLL_DIV_bus_freq_sel_src(data)                                           ((0x00000001&(data))>>0)
#define SYS_PLL_DIV_get_bus_freq_sel(data)                                           ((0x00000001&(data))>>0)


#define SYS_NF_CKSEL                                                                 0x98000038
#define SYS_NF_CKSEL_reg_addr                                                        "0x98000038"
#define SYS_NF_CKSEL_reg                                                             0x98000038
#define set_SYS_NF_CKSEL_reg(data)   (*((volatile unsigned int*) SYS_NF_CKSEL_reg)=data)
#define get_SYS_NF_CKSEL_reg   (*((volatile unsigned int*) SYS_NF_CKSEL_reg))
#define SYS_NF_CKSEL_inst_adr                                                        "0x000E"
#define SYS_NF_CKSEL_inst                                                            0x000E
#define SYS_NF_CKSEL_emmc_div_sel_shift                                              (24)
#define SYS_NF_CKSEL_emmc_div_sel_mask                                               (0x03000000)
#define SYS_NF_CKSEL_emmc_div_sel(data)                                              (0x03000000&((data)<<24))
#define SYS_NF_CKSEL_emmc_div_sel_src(data)                                          ((0x03000000&(data))>>24)
#define SYS_NF_CKSEL_get_emmc_div_sel(data)                                          ((0x03000000&(data))>>24)
#define SYS_NF_CKSEL_cr_div_sel_shift                                                (16)
#define SYS_NF_CKSEL_cr_div_sel_mask                                                 (0x00030000)
#define SYS_NF_CKSEL_cr_div_sel(data)                                                (0x00030000&((data)<<16))
#define SYS_NF_CKSEL_cr_div_sel_src(data)                                            ((0x00030000&(data))>>16)
#define SYS_NF_CKSEL_get_cr_div_sel(data)                                            ((0x00030000&(data))>>16)
#define SYS_NF_CKSEL_sdio_div_sel_shift                                              (8)
#define SYS_NF_CKSEL_sdio_div_sel_mask                                               (0x00000300)
#define SYS_NF_CKSEL_sdio_div_sel(data)                                              (0x00000300&((data)<<8))
#define SYS_NF_CKSEL_sdio_div_sel_src(data)                                          ((0x00000300&(data))>>8)
#define SYS_NF_CKSEL_get_sdio_div_sel(data)                                          ((0x00000300&(data))>>8)
#define SYS_NF_CKSEL_nf_div_sel_shift                                                (0)
#define SYS_NF_CKSEL_nf_div_sel_mask                                                 (0x0000000F)
#define SYS_NF_CKSEL_nf_div_sel(data)                                                (0x0000000F&((data)<<0))
#define SYS_NF_CKSEL_nf_div_sel_src(data)                                            ((0x0000000F&(data))>>0)
#define SYS_NF_CKSEL_get_nf_div_sel(data)                                            ((0x0000000F&(data))>>0)


#define SYS_NDS_SC_CKSEL                                                             0x9800003C
#define SYS_NDS_SC_CKSEL_reg_addr                                                    "0x9800003C"
#define SYS_NDS_SC_CKSEL_reg                                                         0x9800003C
#define set_SYS_NDS_SC_CKSEL_reg(data)   (*((volatile unsigned int*) SYS_NDS_SC_CKSEL_reg)=data)
#define get_SYS_NDS_SC_CKSEL_reg   (*((volatile unsigned int*) SYS_NDS_SC_CKSEL_reg))
#define SYS_NDS_SC_CKSEL_inst_adr                                                    "0x000F"
#define SYS_NDS_SC_CKSEL_inst                                                        0x000F
#define SYS_NDS_SC_CKSEL_nds_sc_div_shift                                            (0)
#define SYS_NDS_SC_CKSEL_nds_sc_div_mask                                             (0x00000007)
#define SYS_NDS_SC_CKSEL_nds_sc_div(data)                                            (0x00000007&((data)<<0))
#define SYS_NDS_SC_CKSEL_nds_sc_div_src(data)                                        ((0x00000007&(data))>>0)
#define SYS_NDS_SC_CKSEL_get_nds_sc_div(data)                                        ((0x00000007&(data))>>0)


#define SYS_DCPHY_CKSEL                                                              0x98000040
#define SYS_DCPHY_CKSEL_reg_addr                                                     "0x98000040"
#define SYS_DCPHY_CKSEL_reg                                                          0x98000040
#define set_SYS_DCPHY_CKSEL_reg(data)   (*((volatile unsigned int*) SYS_DCPHY_CKSEL_reg)=data)
#define get_SYS_DCPHY_CKSEL_reg   (*((volatile unsigned int*) SYS_DCPHY_CKSEL_reg))
#define SYS_DCPHY_CKSEL_inst_adr                                                     "0x0010"
#define SYS_DCPHY_CKSEL_inst                                                         0x0010
#define SYS_DCPHY_CKSEL_ref_bypass_mode_dcphy_1_shift                                (1)
#define SYS_DCPHY_CKSEL_ref_bypass_mode_dcphy_1_mask                                 (0x00000002)
#define SYS_DCPHY_CKSEL_ref_bypass_mode_dcphy_1(data)                                (0x00000002&((data)<<1))
#define SYS_DCPHY_CKSEL_ref_bypass_mode_dcphy_1_src(data)                            ((0x00000002&(data))>>1)
#define SYS_DCPHY_CKSEL_get_ref_bypass_mode_dcphy_1(data)                            ((0x00000002&(data))>>1)
#define SYS_DCPHY_CKSEL_ref_bypass_mode_dcphy_0_shift                                (0)
#define SYS_DCPHY_CKSEL_ref_bypass_mode_dcphy_0_mask                                 (0x00000001)
#define SYS_DCPHY_CKSEL_ref_bypass_mode_dcphy_0(data)                                (0x00000001&((data)<<0))
#define SYS_DCPHY_CKSEL_ref_bypass_mode_dcphy_0_src(data)                            ((0x00000001&(data))>>0)
#define SYS_DCPHY_CKSEL_get_ref_bypass_mode_dcphy_0(data)                            ((0x00000001&(data))>>0)


#define SYS_MISC_CKSEL                                                               0x98000044
#define SYS_MISC_CKSEL_reg_addr                                                      "0x98000044"
#define SYS_MISC_CKSEL_reg                                                           0x98000044
#define set_SYS_MISC_CKSEL_reg(data)   (*((volatile unsigned int*) SYS_MISC_CKSEL_reg)=data)
#define get_SYS_MISC_CKSEL_reg   (*((volatile unsigned int*) SYS_MISC_CKSEL_reg))
#define SYS_MISC_CKSEL_inst_adr                                                      "0x0011"
#define SYS_MISC_CKSEL_inst                                                          0x0011
#define SYS_MISC_CKSEL_clk_camera1_sel_shift                                         (2)
#define SYS_MISC_CKSEL_clk_camera1_sel_mask                                          (0x0000000C)
#define SYS_MISC_CKSEL_clk_camera1_sel(data)                                         (0x0000000C&((data)<<2))
#define SYS_MISC_CKSEL_clk_camera1_sel_src(data)                                     ((0x0000000C&(data))>>2)
#define SYS_MISC_CKSEL_get_clk_camera1_sel(data)                                     ((0x0000000C&(data))>>2)
#define SYS_MISC_CKSEL_clk_camera0_sel_shift                                         (0)
#define SYS_MISC_CKSEL_clk_camera0_sel_mask                                          (0x00000003)
#define SYS_MISC_CKSEL_clk_camera0_sel(data)                                         (0x00000003&((data)<<0))
#define SYS_MISC_CKSEL_clk_camera0_sel_src(data)                                     ((0x00000003&(data))>>0)
#define SYS_MISC_CKSEL_get_clk_camera0_sel(data)                                     ((0x00000003&(data))>>0)


#define SYS_SCPU_CKSEL                                                               0x98000048
#define SYS_SCPU_CKSEL_reg_addr                                                      "0x98000048"
#define SYS_SCPU_CKSEL_reg                                                           0x98000048
#define set_SYS_SCPU_CKSEL_reg(data)   (*((volatile unsigned int*) SYS_SCPU_CKSEL_reg)=data)
#define get_SYS_SCPU_CKSEL_reg   (*((volatile unsigned int*) SYS_SCPU_CKSEL_reg))
#define SYS_SCPU_CKSEL_inst_adr                                                      "0x0012"
#define SYS_SCPU_CKSEL_inst                                                          0x0012
#define SYS_SCPU_CKSEL_CLKTRC_SEL_shift                                              (0)
#define SYS_SCPU_CKSEL_CLKTRC_SEL_mask                                               (0x00000003)
#define SYS_SCPU_CKSEL_CLKTRC_SEL(data)                                              (0x00000003&((data)<<0))
#define SYS_SCPU_CKSEL_CLKTRC_SEL_src(data)                                          ((0x00000003&(data))>>0)
#define SYS_SCPU_CKSEL_get_CLKTRC_SEL(data)                                          ((0x00000003&(data))>>0)


#define SYS_VE_CKSEL                                                                 0x9800004C
#define SYS_VE_CKSEL_reg_addr                                                        "0x9800004C"
#define SYS_VE_CKSEL_reg                                                             0x9800004C
#define set_SYS_VE_CKSEL_reg(data)   (*((volatile unsigned int*) SYS_VE_CKSEL_reg)=data)
#define get_SYS_VE_CKSEL_reg   (*((volatile unsigned int*) SYS_VE_CKSEL_reg))
#define SYS_VE_CKSEL_inst_adr                                                        "0x0013"
#define SYS_VE_CKSEL_inst                                                            0x0013
#define SYS_VE_CKSEL_clk_ve2_bpu_sel_shift                                           (6)
#define SYS_VE_CKSEL_clk_ve2_bpu_sel_mask                                            (0x000001C0)
#define SYS_VE_CKSEL_clk_ve2_bpu_sel(data)                                           (0x000001C0&((data)<<6))
#define SYS_VE_CKSEL_clk_ve2_bpu_sel_src(data)                                       ((0x000001C0&(data))>>6)
#define SYS_VE_CKSEL_get_clk_ve2_bpu_sel(data)                                       ((0x000001C0&(data))>>6)
#define SYS_VE_CKSEL_clk_ve3_sel_shift                                               (4)
#define SYS_VE_CKSEL_clk_ve3_sel_mask                                                (0x00000030)
#define SYS_VE_CKSEL_clk_ve3_sel(data)                                               (0x00000030&((data)<<4))
#define SYS_VE_CKSEL_clk_ve3_sel_src(data)                                           ((0x00000030&(data))>>4)
#define SYS_VE_CKSEL_get_clk_ve3_sel(data)                                           ((0x00000030&(data))>>4)
#define SYS_VE_CKSEL_clk_ve2_sel_shift                                               (2)
#define SYS_VE_CKSEL_clk_ve2_sel_mask                                                (0x0000000C)
#define SYS_VE_CKSEL_clk_ve2_sel(data)                                               (0x0000000C&((data)<<2))
#define SYS_VE_CKSEL_clk_ve2_sel_src(data)                                           ((0x0000000C&(data))>>2)
#define SYS_VE_CKSEL_get_clk_ve2_sel(data)                                           ((0x0000000C&(data))>>2)
#define SYS_VE_CKSEL_clk_ve1_sel_shift                                               (0)
#define SYS_VE_CKSEL_clk_ve1_sel_mask                                                (0x00000003)
#define SYS_VE_CKSEL_clk_ve1_sel(data)                                               (0x00000003&((data)<<0))
#define SYS_VE_CKSEL_clk_ve1_sel_src(data)                                           ((0x00000003&(data))>>0)
#define SYS_VE_CKSEL_get_clk_ve1_sel(data)                                           ((0x00000003&(data))>>0)


#define SYS_SOFT_RESET4                                                              0x98000050
#define SYS_SOFT_RESET4_reg_addr                                                     "0x98000050"
#define SYS_SOFT_RESET4_reg                                                          0x98000050
#define set_SYS_SOFT_RESET4_reg(data)   (*((volatile unsigned int*) SYS_SOFT_RESET4_reg)=data)
#define get_SYS_SOFT_RESET4_reg   (*((volatile unsigned int*) SYS_SOFT_RESET4_reg))
#define SYS_SOFT_RESET4_inst_adr                                                     "0x0014"
#define SYS_SOFT_RESET4_inst                                                         0x0014
#define SYS_SOFT_RESET4_rstn_disp_shift                                              (15)
#define SYS_SOFT_RESET4_rstn_disp_mask                                               (0x00008000)
#define SYS_SOFT_RESET4_rstn_disp(data)                                              (0x00008000&((data)<<15))
#define SYS_SOFT_RESET4_rstn_disp_src(data)                                          ((0x00008000&(data))>>15)
#define SYS_SOFT_RESET4_get_rstn_disp(data)                                          ((0x00008000&(data))>>15)
#define SYS_SOFT_RESET4_rstn_pcie1_phy_mdio_shift                                    (14)
#define SYS_SOFT_RESET4_rstn_pcie1_phy_mdio_mask                                     (0x00004000)
#define SYS_SOFT_RESET4_rstn_pcie1_phy_mdio(data)                                    (0x00004000&((data)<<14))
#define SYS_SOFT_RESET4_rstn_pcie1_phy_mdio_src(data)                                ((0x00004000&(data))>>14)
#define SYS_SOFT_RESET4_get_rstn_pcie1_phy_mdio(data)                                ((0x00004000&(data))>>14)
#define SYS_SOFT_RESET4_rstn_pcie0_phy_mdio_shift                                    (13)
#define SYS_SOFT_RESET4_rstn_pcie0_phy_mdio_mask                                     (0x00002000)
#define SYS_SOFT_RESET4_rstn_pcie0_phy_mdio(data)                                    (0x00002000&((data)<<13))
#define SYS_SOFT_RESET4_rstn_pcie0_phy_mdio_src(data)                                ((0x00002000&(data))>>13)
#define SYS_SOFT_RESET4_get_rstn_pcie0_phy_mdio(data)                                ((0x00002000&(data))>>13)
#define SYS_SOFT_RESET4_rstn_hdmirx_wrap_shift                                       (12)
#define SYS_SOFT_RESET4_rstn_hdmirx_wrap_mask                                        (0x00001000)
#define SYS_SOFT_RESET4_rstn_hdmirx_wrap(data)                                       (0x00001000&((data)<<12))
#define SYS_SOFT_RESET4_rstn_hdmirx_wrap_src(data)                                   ((0x00001000&(data))>>12)
#define SYS_SOFT_RESET4_get_rstn_hdmirx_wrap(data)                                   ((0x00001000&(data))>>12)
#define SYS_SOFT_RESET4_rstn_fan_shift                                               (11)
#define SYS_SOFT_RESET4_rstn_fan_mask                                                (0x00000800)
#define SYS_SOFT_RESET4_rstn_fan(data)                                               (0x00000800&((data)<<11))
#define SYS_SOFT_RESET4_rstn_fan_src(data)                                           ((0x00000800&(data))>>11)
#define SYS_SOFT_RESET4_get_rstn_fan(data)                                           ((0x00000800&(data))>>11)
#define SYS_SOFT_RESET4_rstn_sata_1_shift                                            (10)
#define SYS_SOFT_RESET4_rstn_sata_1_mask                                             (0x00000400)
#define SYS_SOFT_RESET4_rstn_sata_1(data)                                            (0x00000400&((data)<<10))
#define SYS_SOFT_RESET4_rstn_sata_1_src(data)                                        ((0x00000400&(data))>>10)
#define SYS_SOFT_RESET4_get_rstn_sata_1(data)                                        ((0x00000400&(data))>>10)
#define SYS_SOFT_RESET4_rstn_sata_phy_1_shift                                        (9)
#define SYS_SOFT_RESET4_rstn_sata_phy_1_mask                                         (0x00000200)
#define SYS_SOFT_RESET4_rstn_sata_phy_1(data)                                        (0x00000200&((data)<<9))
#define SYS_SOFT_RESET4_rstn_sata_phy_1_src(data)                                    ((0x00000200&(data))>>9)
#define SYS_SOFT_RESET4_get_rstn_sata_phy_1(data)                                    ((0x00000200&(data))>>9)
#define SYS_SOFT_RESET4_sata_func_exist_1_shift                                      (8)
#define SYS_SOFT_RESET4_sata_func_exist_1_mask                                       (0x00000100)
#define SYS_SOFT_RESET4_sata_func_exist_1(data)                                      (0x00000100&((data)<<8))
#define SYS_SOFT_RESET4_sata_func_exist_1_src(data)                                  ((0x00000100&(data))>>8)
#define SYS_SOFT_RESET4_get_sata_func_exist_1(data)                                  ((0x00000100&(data))>>8)
#define SYS_SOFT_RESET4_rstn_sata_phy_pow_1_shift                                    (7)
#define SYS_SOFT_RESET4_rstn_sata_phy_pow_1_mask                                     (0x00000080)
#define SYS_SOFT_RESET4_rstn_sata_phy_pow_1(data)                                    (0x00000080&((data)<<7))
#define SYS_SOFT_RESET4_rstn_sata_phy_pow_1_src(data)                                ((0x00000080&(data))>>7)
#define SYS_SOFT_RESET4_get_rstn_sata_phy_pow_1(data)                                ((0x00000080&(data))>>7)
#define SYS_SOFT_RESET4_rstn_cbusrx_shift                                            (6)
#define SYS_SOFT_RESET4_rstn_cbusrx_mask                                             (0x00000040)
#define SYS_SOFT_RESET4_rstn_cbusrx(data)                                            (0x00000040&((data)<<6))
#define SYS_SOFT_RESET4_rstn_cbusrx_src(data)                                        ((0x00000040&(data))>>6)
#define SYS_SOFT_RESET4_get_rstn_cbusrx(data)                                        ((0x00000040&(data))>>6)
#define SYS_SOFT_RESET4_rstn_hdmirx_shift                                            (5)
#define SYS_SOFT_RESET4_rstn_hdmirx_mask                                             (0x00000020)
#define SYS_SOFT_RESET4_rstn_hdmirx(data)                                            (0x00000020&((data)<<5))
#define SYS_SOFT_RESET4_rstn_hdmirx_src(data)                                        ((0x00000020&(data))>>5)
#define SYS_SOFT_RESET4_get_rstn_hdmirx(data)                                        ((0x00000020&(data))>>5)
#define SYS_SOFT_RESET4_rstn_dcphy_ssc_dig_shift                                     (4)
#define SYS_SOFT_RESET4_rstn_dcphy_ssc_dig_mask                                      (0x00000010)
#define SYS_SOFT_RESET4_rstn_dcphy_ssc_dig(data)                                     (0x00000010&((data)<<4))
#define SYS_SOFT_RESET4_rstn_dcphy_ssc_dig_src(data)                                 ((0x00000010&(data))>>4)
#define SYS_SOFT_RESET4_get_rstn_dcphy_ssc_dig(data)                                 ((0x00000010&(data))>>4)
#define SYS_SOFT_RESET4_rstn_dcphy_ldo_shift                                         (3)
#define SYS_SOFT_RESET4_rstn_dcphy_ldo_mask                                          (0x00000008)
#define SYS_SOFT_RESET4_rstn_dcphy_ldo(data)                                         (0x00000008&((data)<<3))
#define SYS_SOFT_RESET4_rstn_dcphy_ldo_src(data)                                     ((0x00000008&(data))>>3)
#define SYS_SOFT_RESET4_get_rstn_dcphy_ldo(data)                                     ((0x00000008&(data))>>3)
#define SYS_SOFT_RESET4_rstn_dcphy_ptr_shift                                         (2)
#define SYS_SOFT_RESET4_rstn_dcphy_ptr_mask                                          (0x00000004)
#define SYS_SOFT_RESET4_rstn_dcphy_ptr(data)                                         (0x00000004&((data)<<2))
#define SYS_SOFT_RESET4_rstn_dcphy_ptr_src(data)                                     ((0x00000004&(data))>>2)
#define SYS_SOFT_RESET4_get_rstn_dcphy_ptr(data)                                     ((0x00000004&(data))>>2)
#define SYS_SOFT_RESET4_rstn_dcphy_alert_rx_shift                                    (1)
#define SYS_SOFT_RESET4_rstn_dcphy_alert_rx_mask                                     (0x00000002)
#define SYS_SOFT_RESET4_rstn_dcphy_alert_rx(data)                                    (0x00000002&((data)<<1))
#define SYS_SOFT_RESET4_rstn_dcphy_alert_rx_src(data)                                ((0x00000002&(data))>>1)
#define SYS_SOFT_RESET4_get_rstn_dcphy_alert_rx(data)                                ((0x00000002&(data))>>1)
#define SYS_SOFT_RESET4_rstn_dcphy_crt_shift                                         (0)
#define SYS_SOFT_RESET4_rstn_dcphy_crt_mask                                          (0x00000001)
#define SYS_SOFT_RESET4_rstn_dcphy_crt(data)                                         (0x00000001&((data)<<0))
#define SYS_SOFT_RESET4_rstn_dcphy_crt_src(data)                                     ((0x00000001&(data))>>0)
#define SYS_SOFT_RESET4_get_rstn_dcphy_crt(data)                                     ((0x00000001&(data))>>0)


#define SYS_AIO_O_PCM_CK_CTL                                                         0x98000070
#define SYS_AIO_O_PCM_CK_CTL_reg_addr                                                "0x98000070"
#define SYS_AIO_O_PCM_CK_CTL_reg                                                     0x98000070
#define set_SYS_AIO_O_PCM_CK_CTL_reg(data)   (*((volatile unsigned int*) SYS_AIO_O_PCM_CK_CTL_reg)=data)
#define get_SYS_AIO_O_PCM_CK_CTL_reg   (*((volatile unsigned int*) SYS_AIO_O_PCM_CK_CTL_reg))
#define SYS_AIO_O_PCM_CK_CTL_inst_adr                                                "0x001C"
#define SYS_AIO_O_PCM_CK_CTL_inst                                                    0x001C
#define SYS_AIO_O_PCM_CK_CTL_mclk_sel_shift                                          (5)
#define SYS_AIO_O_PCM_CK_CTL_mclk_sel_mask                                           (0x000000E0)
#define SYS_AIO_O_PCM_CK_CTL_mclk_sel(data)                                          (0x000000E0&((data)<<5))
#define SYS_AIO_O_PCM_CK_CTL_mclk_sel_src(data)                                      ((0x000000E0&(data))>>5)
#define SYS_AIO_O_PCM_CK_CTL_get_mclk_sel(data)                                      ((0x000000E0&(data))>>5)
#define SYS_AIO_O_PCM_CK_CTL_fs_shift                                                (1)
#define SYS_AIO_O_PCM_CK_CTL_fs_mask                                                 (0x0000001E)
#define SYS_AIO_O_PCM_CK_CTL_fs(data)                                                (0x0000001E&((data)<<1))
#define SYS_AIO_O_PCM_CK_CTL_fs_src(data)                                            ((0x0000001E&(data))>>1)
#define SYS_AIO_O_PCM_CK_CTL_get_fs(data)                                            ((0x0000001E&(data))>>1)
#define SYS_AIO_O_PCM_CK_CTL_clken_shift                                             (0)
#define SYS_AIO_O_PCM_CK_CTL_clken_mask                                              (0x00000001)
#define SYS_AIO_O_PCM_CK_CTL_clken(data)                                             (0x00000001&((data)<<0))
#define SYS_AIO_O_PCM_CK_CTL_clken_src(data)                                         ((0x00000001&(data))>>0)
#define SYS_AIO_O_PCM_CK_CTL_get_clken(data)                                         ((0x00000001&(data))>>0)


#define SYS_AIO_O_RAW_CK_CTL                                                         0x98000074
#define SYS_AIO_O_RAW_CK_CTL_reg_addr                                                "0x98000074"
#define SYS_AIO_O_RAW_CK_CTL_reg                                                     0x98000074
#define set_SYS_AIO_O_RAW_CK_CTL_reg(data)   (*((volatile unsigned int*) SYS_AIO_O_RAW_CK_CTL_reg)=data)
#define get_SYS_AIO_O_RAW_CK_CTL_reg   (*((volatile unsigned int*) SYS_AIO_O_RAW_CK_CTL_reg))
#define SYS_AIO_O_RAW_CK_CTL_inst_adr                                                "0x001D"
#define SYS_AIO_O_RAW_CK_CTL_inst                                                    0x001D
#define SYS_AIO_O_RAW_CK_CTL_fs_shift                                                (1)
#define SYS_AIO_O_RAW_CK_CTL_fs_mask                                                 (0x0000001E)
#define SYS_AIO_O_RAW_CK_CTL_fs(data)                                                (0x0000001E&((data)<<1))
#define SYS_AIO_O_RAW_CK_CTL_fs_src(data)                                            ((0x0000001E&(data))>>1)
#define SYS_AIO_O_RAW_CK_CTL_get_fs(data)                                            ((0x0000001E&(data))>>1)
#define SYS_AIO_O_RAW_CK_CTL_clken_shift                                             (0)
#define SYS_AIO_O_RAW_CK_CTL_clken_mask                                              (0x00000001)
#define SYS_AIO_O_RAW_CK_CTL_clken(data)                                             (0x00000001&((data)<<0))
#define SYS_AIO_O_RAW_CK_CTL_clken_src(data)                                         ((0x00000001&(data))>>0)
#define SYS_AIO_O_RAW_CK_CTL_get_clken(data)                                         ((0x00000001&(data))>>0)


#define SYS_AIO_O_RAW2_CK_CTL                                                        0x98000078
#define SYS_AIO_O_RAW2_CK_CTL_reg_addr                                               "0x98000078"
#define SYS_AIO_O_RAW2_CK_CTL_reg                                                    0x98000078
#define set_SYS_AIO_O_RAW2_CK_CTL_reg(data)   (*((volatile unsigned int*) SYS_AIO_O_RAW2_CK_CTL_reg)=data)
#define get_SYS_AIO_O_RAW2_CK_CTL_reg   (*((volatile unsigned int*) SYS_AIO_O_RAW2_CK_CTL_reg))
#define SYS_AIO_O_RAW2_CK_CTL_inst_adr                                               "0x001E"
#define SYS_AIO_O_RAW2_CK_CTL_inst                                                   0x001E
#define SYS_AIO_O_RAW2_CK_CTL_fs_shift                                               (1)
#define SYS_AIO_O_RAW2_CK_CTL_fs_mask                                                (0x0000001E)
#define SYS_AIO_O_RAW2_CK_CTL_fs(data)                                               (0x0000001E&((data)<<1))
#define SYS_AIO_O_RAW2_CK_CTL_fs_src(data)                                           ((0x0000001E&(data))>>1)
#define SYS_AIO_O_RAW2_CK_CTL_get_fs(data)                                           ((0x0000001E&(data))>>1)
#define SYS_AIO_O_RAW2_CK_CTL_clken_shift                                            (0)
#define SYS_AIO_O_RAW2_CK_CTL_clken_mask                                             (0x00000001)
#define SYS_AIO_O_RAW2_CK_CTL_clken(data)                                            (0x00000001&((data)<<0))
#define SYS_AIO_O_RAW2_CK_CTL_clken_src(data)                                        ((0x00000001&(data))>>0)
#define SYS_AIO_O_RAW2_CK_CTL_get_clken(data)                                        ((0x00000001&(data))>>0)


#define SYS_APS_CTL                                                                  0x9800007C
#define SYS_APS_CTL_reg_addr                                                         "0x9800007C"
#define SYS_APS_CTL_reg                                                              0x9800007C
#define set_SYS_APS_CTL_reg(data)   (*((volatile unsigned int*) SYS_APS_CTL_reg)=data)
#define get_SYS_APS_CTL_reg   (*((volatile unsigned int*) SYS_APS_CTL_reg))
#define SYS_APS_CTL_inst_adr                                                         "0x001F"
#define SYS_APS_CTL_inst                                                             0x001F
#define SYS_APS_CTL_write_en2_shift                                                  (1)
#define SYS_APS_CTL_write_en2_mask                                                   (0x00000002)
#define SYS_APS_CTL_write_en2(data)                                                  (0x00000002&((data)<<1))
#define SYS_APS_CTL_write_en2_src(data)                                              ((0x00000002&(data))>>1)
#define SYS_APS_CTL_get_write_en2(data)                                              ((0x00000002&(data))>>1)
#define SYS_APS_CTL_dds_rstn_shift                                                   (0)
#define SYS_APS_CTL_dds_rstn_mask                                                    (0x00000001)
#define SYS_APS_CTL_dds_rstn(data)                                                   (0x00000001&((data)<<0))
#define SYS_APS_CTL_dds_rstn_src(data)                                               ((0x00000001&(data))>>0)
#define SYS_APS_CTL_get_dds_rstn(data)                                               ((0x00000001&(data))>>0)


#define SYS_AIO_I_PCM_CK_CTL                                                         0x98000080
#define SYS_AIO_I_PCM_CK_CTL_reg_addr                                                "0x98000080"
#define SYS_AIO_I_PCM_CK_CTL_reg                                                     0x98000080
#define set_SYS_AIO_I_PCM_CK_CTL_reg(data)   (*((volatile unsigned int*) SYS_AIO_I_PCM_CK_CTL_reg)=data)
#define get_SYS_AIO_I_PCM_CK_CTL_reg   (*((volatile unsigned int*) SYS_AIO_I_PCM_CK_CTL_reg))
#define SYS_AIO_I_PCM_CK_CTL_inst_adr                                                "0x0020"
#define SYS_AIO_I_PCM_CK_CTL_inst                                                    0x0020
#define SYS_AIO_I_PCM_CK_CTL_mclk_sel_shift                                          (5)
#define SYS_AIO_I_PCM_CK_CTL_mclk_sel_mask                                           (0x000000E0)
#define SYS_AIO_I_PCM_CK_CTL_mclk_sel(data)                                          (0x000000E0&((data)<<5))
#define SYS_AIO_I_PCM_CK_CTL_mclk_sel_src(data)                                      ((0x000000E0&(data))>>5)
#define SYS_AIO_I_PCM_CK_CTL_get_mclk_sel(data)                                      ((0x000000E0&(data))>>5)
#define SYS_AIO_I_PCM_CK_CTL_fs_shift                                                (1)
#define SYS_AIO_I_PCM_CK_CTL_fs_mask                                                 (0x0000001E)
#define SYS_AIO_I_PCM_CK_CTL_fs(data)                                                (0x0000001E&((data)<<1))
#define SYS_AIO_I_PCM_CK_CTL_fs_src(data)                                            ((0x0000001E&(data))>>1)
#define SYS_AIO_I_PCM_CK_CTL_get_fs(data)                                            ((0x0000001E&(data))>>1)
#define SYS_AIO_I_PCM_CK_CTL_clken_shift                                             (0)
#define SYS_AIO_I_PCM_CK_CTL_clken_mask                                              (0x00000001)
#define SYS_AIO_I_PCM_CK_CTL_clken(data)                                             (0x00000001&((data)<<0))
#define SYS_AIO_I_PCM_CK_CTL_clken_src(data)                                         ((0x00000001&(data))>>0)
#define SYS_AIO_I_PCM_CK_CTL_get_clken(data)                                         ((0x00000001&(data))>>0)


#define SYS_PLL_SCPU0                                                                0x98000100
#define SYS_PLL_SCPU0_reg_addr                                                       "0x98000100"
#define SYS_PLL_SCPU0_reg                                                            0x98000100
#define set_SYS_PLL_SCPU0_reg(data)   (*((volatile unsigned int*) SYS_PLL_SCPU0_reg)=data)
#define get_SYS_PLL_SCPU0_reg   (*((volatile unsigned int*) SYS_PLL_SCPU0_reg))
#define SYS_PLL_SCPU0_inst_adr                                                       "0x0040"
#define SYS_PLL_SCPU0_inst                                                           0x0040
#define SYS_PLL_SCPU0_REG_LDO18V_SEL_shift                                           (19)
#define SYS_PLL_SCPU0_REG_LDO18V_SEL_mask                                            (0x00180000)
#define SYS_PLL_SCPU0_REG_LDO18V_SEL(data)                                           (0x00180000&((data)<<19))
#define SYS_PLL_SCPU0_REG_LDO18V_SEL_src(data)                                       ((0x00180000&(data))>>19)
#define SYS_PLL_SCPU0_get_REG_LDO18V_SEL(data)                                       ((0x00180000&(data))>>19)
#define SYS_PLL_SCPU0_REG_LDO10V_SEL_shift                                           (17)
#define SYS_PLL_SCPU0_REG_LDO10V_SEL_mask                                            (0x00060000)
#define SYS_PLL_SCPU0_REG_LDO10V_SEL(data)                                           (0x00060000&((data)<<17))
#define SYS_PLL_SCPU0_REG_LDO10V_SEL_src(data)                                       ((0x00060000&(data))>>17)
#define SYS_PLL_SCPU0_get_REG_LDO10V_SEL(data)                                       ((0x00060000&(data))>>17)
#define SYS_PLL_SCPU0_REG_TESTSEL_PLLA_shift                                         (16)
#define SYS_PLL_SCPU0_REG_TESTSEL_PLLA_mask                                          (0x00010000)
#define SYS_PLL_SCPU0_REG_TESTSEL_PLLA(data)                                         (0x00010000&((data)<<16))
#define SYS_PLL_SCPU0_REG_TESTSEL_PLLA_src(data)                                     ((0x00010000&(data))>>16)
#define SYS_PLL_SCPU0_get_REG_TESTSEL_PLLA(data)                                     ((0x00010000&(data))>>16)
#define SYS_PLL_SCPU0_REG_WD_SET_PLLA_shift                                          (14)
#define SYS_PLL_SCPU0_REG_WD_SET_PLLA_mask                                           (0x00004000)
#define SYS_PLL_SCPU0_REG_WD_SET_PLLA(data)                                          (0x00004000&((data)<<14))
#define SYS_PLL_SCPU0_REG_WD_SET_PLLA_src(data)                                      ((0x00004000&(data))>>14)
#define SYS_PLL_SCPU0_get_REG_WD_SET_PLLA(data)                                      ((0x00004000&(data))>>14)
#define SYS_PLL_SCPU0_REG_WD_RST_PLLA_shift                                          (13)
#define SYS_PLL_SCPU0_REG_WD_RST_PLLA_mask                                           (0x00002000)
#define SYS_PLL_SCPU0_REG_WD_RST_PLLA(data)                                          (0x00002000&((data)<<13))
#define SYS_PLL_SCPU0_REG_WD_RST_PLLA_src(data)                                      ((0x00002000&(data))>>13)
#define SYS_PLL_SCPU0_get_REG_WD_RST_PLLA(data)                                      ((0x00002000&(data))>>13)
#define SYS_PLL_SCPU0_REG_SEL_CCO_PLLA_shift                                         (12)
#define SYS_PLL_SCPU0_REG_SEL_CCO_PLLA_mask                                          (0x00001000)
#define SYS_PLL_SCPU0_REG_SEL_CCO_PLLA(data)                                         (0x00001000&((data)<<12))
#define SYS_PLL_SCPU0_REG_SEL_CCO_PLLA_src(data)                                     ((0x00001000&(data))>>12)
#define SYS_PLL_SCPU0_get_REG_SEL_CCO_PLLA(data)                                     ((0x00001000&(data))>>12)
#define SYS_PLL_SCPU0_REG_SCPU_DBUG_EN_PLLA_shift                                    (11)
#define SYS_PLL_SCPU0_REG_SCPU_DBUG_EN_PLLA_mask                                     (0x00000800)
#define SYS_PLL_SCPU0_REG_SCPU_DBUG_EN_PLLA(data)                                    (0x00000800&((data)<<11))
#define SYS_PLL_SCPU0_REG_SCPU_DBUG_EN_PLLA_src(data)                                ((0x00000800&(data))>>11)
#define SYS_PLL_SCPU0_get_REG_SCPU_DBUG_EN_PLLA(data)                                ((0x00000800&(data))>>11)
#define SYS_PLL_SCPU0_REG_LPF_RS_PLLA_shift                                          (8)
#define SYS_PLL_SCPU0_REG_LPF_RS_PLLA_mask                                           (0x00000700)
#define SYS_PLL_SCPU0_REG_LPF_RS_PLLA(data)                                          (0x00000700&((data)<<8))
#define SYS_PLL_SCPU0_REG_LPF_RS_PLLA_src(data)                                      ((0x00000700&(data))>>8)
#define SYS_PLL_SCPU0_get_REG_LPF_RS_PLLA(data)                                      ((0x00000700&(data))>>8)
#define SYS_PLL_SCPU0_REG_LPF_CS_PLLA_shift                                          (6)
#define SYS_PLL_SCPU0_REG_LPF_CS_PLLA_mask                                           (0x000000C0)
#define SYS_PLL_SCPU0_REG_LPF_CS_PLLA(data)                                          (0x000000C0&((data)<<6))
#define SYS_PLL_SCPU0_REG_LPF_CS_PLLA_src(data)                                      ((0x000000C0&(data))>>6)
#define SYS_PLL_SCPU0_get_REG_LPF_CS_PLLA(data)                                      ((0x000000C0&(data))>>6)
#define SYS_PLL_SCPU0_REG_ICP_PLLA_shift                                             (3)
#define SYS_PLL_SCPU0_REG_ICP_PLLA_mask                                              (0x00000038)
#define SYS_PLL_SCPU0_REG_ICP_PLLA(data)                                             (0x00000038&((data)<<3))
#define SYS_PLL_SCPU0_REG_ICP_PLLA_src(data)                                         ((0x00000038&(data))>>3)
#define SYS_PLL_SCPU0_get_REG_ICP_PLLA(data)                                         ((0x00000038&(data))>>3)
#define SYS_PLL_SCPU0_REG_DIV_PREDIV_BPS_PLLA_shift                                  (2)
#define SYS_PLL_SCPU0_REG_DIV_PREDIV_BPS_PLLA_mask                                   (0x00000004)
#define SYS_PLL_SCPU0_REG_DIV_PREDIV_BPS_PLLA(data)                                  (0x00000004&((data)<<2))
#define SYS_PLL_SCPU0_REG_DIV_PREDIV_BPS_PLLA_src(data)                              ((0x00000004&(data))>>2)
#define SYS_PLL_SCPU0_get_REG_DIV_PREDIV_BPS_PLLA(data)                              ((0x00000004&(data))>>2)
#define SYS_PLL_SCPU0_REG_DIV_PREDIV_SEL_PLLA_shift                                  (0)
#define SYS_PLL_SCPU0_REG_DIV_PREDIV_SEL_PLLA_mask                                   (0x00000003)
#define SYS_PLL_SCPU0_REG_DIV_PREDIV_SEL_PLLA(data)                                  (0x00000003&((data)<<0))
#define SYS_PLL_SCPU0_REG_DIV_PREDIV_SEL_PLLA_src(data)                              ((0x00000003&(data))>>0)
#define SYS_PLL_SCPU0_get_REG_DIV_PREDIV_SEL_PLLA(data)                              ((0x00000003&(data))>>0)


#define SYS_PLL_SCPU1                                                                0x98000104
#define SYS_PLL_SCPU1_reg_addr                                                       "0x98000104"
#define SYS_PLL_SCPU1_reg                                                            0x98000104
#define set_SYS_PLL_SCPU1_reg(data)   (*((volatile unsigned int*) SYS_PLL_SCPU1_reg)=data)
#define get_SYS_PLL_SCPU1_reg   (*((volatile unsigned int*) SYS_PLL_SCPU1_reg))
#define SYS_PLL_SCPU1_inst_adr                                                       "0x0041"
#define SYS_PLL_SCPU1_inst                                                           0x0041
#define SYS_PLL_SCPU1_REG_OEB_PLLA_shift                                             (2)
#define SYS_PLL_SCPU1_REG_OEB_PLLA_mask                                              (0x00000004)
#define SYS_PLL_SCPU1_REG_OEB_PLLA(data)                                             (0x00000004&((data)<<2))
#define SYS_PLL_SCPU1_REG_OEB_PLLA_src(data)                                         ((0x00000004&(data))>>2)
#define SYS_PLL_SCPU1_get_REG_OEB_PLLA(data)                                         ((0x00000004&(data))>>2)
#define SYS_PLL_SCPU1_SCPU_RSTB_PLLA_shift                                           (1)
#define SYS_PLL_SCPU1_SCPU_RSTB_PLLA_mask                                            (0x00000002)
#define SYS_PLL_SCPU1_SCPU_RSTB_PLLA(data)                                           (0x00000002&((data)<<1))
#define SYS_PLL_SCPU1_SCPU_RSTB_PLLA_src(data)                                       ((0x00000002&(data))>>1)
#define SYS_PLL_SCPU1_get_SCPU_RSTB_PLLA(data)                                       ((0x00000002&(data))>>1)
#define SYS_PLL_SCPU1_SCPU_POW_PLLA_shift                                            (0)
#define SYS_PLL_SCPU1_SCPU_POW_PLLA_mask                                             (0x00000001)
#define SYS_PLL_SCPU1_SCPU_POW_PLLA(data)                                            (0x00000001&((data)<<0))
#define SYS_PLL_SCPU1_SCPU_POW_PLLA_src(data)                                        ((0x00000001&(data))>>0)
#define SYS_PLL_SCPU1_get_SCPU_POW_PLLA(data)                                        ((0x00000001&(data))>>0)


#define SYS_PLL_ACPU1                                                                0x9800010C
#define SYS_PLL_ACPU1_reg_addr                                                       "0x9800010C"
#define SYS_PLL_ACPU1_reg                                                            0x9800010C
#define set_SYS_PLL_ACPU1_reg(data)   (*((volatile unsigned int*) SYS_PLL_ACPU1_reg)=data)
#define get_SYS_PLL_ACPU1_reg   (*((volatile unsigned int*) SYS_PLL_ACPU1_reg))
#define SYS_PLL_ACPU1_inst_adr                                                       "0x0043"
#define SYS_PLL_ACPU1_inst                                                           0x0043
#define SYS_PLL_ACPU1_REG_PLLACPU_PDIV_shift                                         (17)
#define SYS_PLL_ACPU1_REG_PLLACPU_PDIV_mask                                          (0x00060000)
#define SYS_PLL_ACPU1_REG_PLLACPU_PDIV(data)                                         (0x00060000&((data)<<17))
#define SYS_PLL_ACPU1_REG_PLLACPU_PDIV_src(data)                                     ((0x00060000&(data))>>17)
#define SYS_PLL_ACPU1_get_REG_PLLACPU_PDIV(data)                                     ((0x00060000&(data))>>17)
#define SYS_PLL_ACPU1_REG_PLLACPU_LPF_RS_shift                                       (14)
#define SYS_PLL_ACPU1_REG_PLLACPU_LPF_RS_mask                                        (0x0001C000)
#define SYS_PLL_ACPU1_REG_PLLACPU_LPF_RS(data)                                       (0x0001C000&((data)<<14))
#define SYS_PLL_ACPU1_REG_PLLACPU_LPF_RS_src(data)                                   ((0x0001C000&(data))>>14)
#define SYS_PLL_ACPU1_get_REG_PLLACPU_LPF_RS(data)                                   ((0x0001C000&(data))>>14)
#define SYS_PLL_ACPU1_REG_PLLACPU_LPF_CS_shift                                       (12)
#define SYS_PLL_ACPU1_REG_PLLACPU_LPF_CS_mask                                        (0x00003000)
#define SYS_PLL_ACPU1_REG_PLLACPU_LPF_CS(data)                                       (0x00003000&((data)<<12))
#define SYS_PLL_ACPU1_REG_PLLACPU_LPF_CS_src(data)                                   ((0x00003000&(data))>>12)
#define SYS_PLL_ACPU1_get_REG_PLLACPU_LPF_CS(data)                                   ((0x00003000&(data))>>12)
#define SYS_PLL_ACPU1_REG_PLLACPU_ICP_shift                                          (9)
#define SYS_PLL_ACPU1_REG_PLLACPU_ICP_mask                                           (0x00000E00)
#define SYS_PLL_ACPU1_REG_PLLACPU_ICP(data)                                          (0x00000E00&((data)<<9))
#define SYS_PLL_ACPU1_REG_PLLACPU_ICP_src(data)                                      ((0x00000E00&(data))>>9)
#define SYS_PLL_ACPU1_get_REG_PLLACPU_ICP(data)                                      ((0x00000E00&(data))>>9)
#define SYS_PLL_ACPU1_REG_PLLACPU_WDRST_shift                                        (8)
#define SYS_PLL_ACPU1_REG_PLLACPU_WDRST_mask                                         (0x00000100)
#define SYS_PLL_ACPU1_REG_PLLACPU_WDRST(data)                                        (0x00000100&((data)<<8))
#define SYS_PLL_ACPU1_REG_PLLACPU_WDRST_src(data)                                    ((0x00000100&(data))>>8)
#define SYS_PLL_ACPU1_get_REG_PLLACPU_WDRST(data)                                    ((0x00000100&(data))>>8)
#define SYS_PLL_ACPU1_REG_PLLACPU_WDSET_shift                                        (7)
#define SYS_PLL_ACPU1_REG_PLLACPU_WDSET_mask                                         (0x00000080)
#define SYS_PLL_ACPU1_REG_PLLACPU_WDSET(data)                                        (0x00000080&((data)<<7))
#define SYS_PLL_ACPU1_REG_PLLACPU_WDSET_src(data)                                    ((0x00000080&(data))>>7)
#define SYS_PLL_ACPU1_get_REG_PLLACPU_WDSET(data)                                    ((0x00000080&(data))>>7)
#define SYS_PLL_ACPU1_REG_PLLACPU_TESTSEL_shift                                      (6)
#define SYS_PLL_ACPU1_REG_PLLACPU_TESTSEL_mask                                       (0x00000040)
#define SYS_PLL_ACPU1_REG_PLLACPU_TESTSEL(data)                                      (0x00000040&((data)<<6))
#define SYS_PLL_ACPU1_REG_PLLACPU_TESTSEL_src(data)                                  ((0x00000040&(data))>>6)
#define SYS_PLL_ACPU1_get_REG_PLLACPU_TESTSEL(data)                                  ((0x00000040&(data))>>6)
#define SYS_PLL_ACPU1_REG_PLLACPU_SEL_CCO_shift                                      (5)
#define SYS_PLL_ACPU1_REG_PLLACPU_SEL_CCO_mask                                       (0x00000020)
#define SYS_PLL_ACPU1_REG_PLLACPU_SEL_CCO(data)                                      (0x00000020&((data)<<5))
#define SYS_PLL_ACPU1_REG_PLLACPU_SEL_CCO_src(data)                                  ((0x00000020&(data))>>5)
#define SYS_PLL_ACPU1_get_REG_PLLACPU_SEL_CCO(data)                                  ((0x00000020&(data))>>5)
#define SYS_PLL_ACPU1_REG_PLLACPU_PDIV_BPS_shift                                     (4)
#define SYS_PLL_ACPU1_REG_PLLACPU_PDIV_BPS_mask                                      (0x00000010)
#define SYS_PLL_ACPU1_REG_PLLACPU_PDIV_BPS(data)                                     (0x00000010&((data)<<4))
#define SYS_PLL_ACPU1_REG_PLLACPU_PDIV_BPS_src(data)                                 ((0x00000010&(data))>>4)
#define SYS_PLL_ACPU1_get_REG_PLLACPU_PDIV_BPS(data)                                 ((0x00000010&(data))>>4)
#define SYS_PLL_ACPU1_REG_PLLACPU_DBUG_EN_shift                                      (3)
#define SYS_PLL_ACPU1_REG_PLLACPU_DBUG_EN_mask                                       (0x00000008)
#define SYS_PLL_ACPU1_REG_PLLACPU_DBUG_EN(data)                                      (0x00000008&((data)<<3))
#define SYS_PLL_ACPU1_REG_PLLACPU_DBUG_EN_src(data)                                  ((0x00000008&(data))>>3)
#define SYS_PLL_ACPU1_get_REG_PLLACPU_DBUG_EN(data)                                  ((0x00000008&(data))>>3)


#define SYS_PLL_ACPU2                                                                0x98000110
#define SYS_PLL_ACPU2_reg_addr                                                       "0x98000110"
#define SYS_PLL_ACPU2_reg                                                            0x98000110
#define set_SYS_PLL_ACPU2_reg(data)   (*((volatile unsigned int*) SYS_PLL_ACPU2_reg)=data)
#define get_SYS_PLL_ACPU2_reg   (*((volatile unsigned int*) SYS_PLL_ACPU2_reg))
#define SYS_PLL_ACPU2_inst_adr                                                       "0x0044"
#define SYS_PLL_ACPU2_inst                                                           0x0044
#define SYS_PLL_ACPU2_REG_PLLACPU_OEB_shift                                          (2)
#define SYS_PLL_ACPU2_REG_PLLACPU_OEB_mask                                           (0x00000004)
#define SYS_PLL_ACPU2_REG_PLLACPU_OEB(data)                                          (0x00000004&((data)<<2))
#define SYS_PLL_ACPU2_REG_PLLACPU_OEB_src(data)                                      ((0x00000004&(data))>>2)
#define SYS_PLL_ACPU2_get_REG_PLLACPU_OEB(data)                                      ((0x00000004&(data))>>2)
#define SYS_PLL_ACPU2_REG_PLLACPU_RSTB_shift                                         (1)
#define SYS_PLL_ACPU2_REG_PLLACPU_RSTB_mask                                          (0x00000002)
#define SYS_PLL_ACPU2_REG_PLLACPU_RSTB(data)                                         (0x00000002&((data)<<1))
#define SYS_PLL_ACPU2_REG_PLLACPU_RSTB_src(data)                                     ((0x00000002&(data))>>1)
#define SYS_PLL_ACPU2_get_REG_PLLACPU_RSTB(data)                                     ((0x00000002&(data))>>1)
#define SYS_PLL_ACPU2_REG_PLLACPU_POW_shift                                          (0)
#define SYS_PLL_ACPU2_REG_PLLACPU_POW_mask                                           (0x00000001)
#define SYS_PLL_ACPU2_REG_PLLACPU_POW(data)                                          (0x00000001&((data)<<0))
#define SYS_PLL_ACPU2_REG_PLLACPU_POW_src(data)                                      ((0x00000001&(data))>>0)
#define SYS_PLL_ACPU2_get_REG_PLLACPU_POW(data)                                      ((0x00000001&(data))>>0)


#define SYS_PLL_VE1_1                                                                0x98000114
#define SYS_PLL_VE1_1_reg_addr                                                       "0x98000114"
#define SYS_PLL_VE1_1_reg                                                            0x98000114
#define set_SYS_PLL_VE1_1_reg(data)   (*((volatile unsigned int*) SYS_PLL_VE1_1_reg)=data)
#define get_SYS_PLL_VE1_1_reg   (*((volatile unsigned int*) SYS_PLL_VE1_1_reg))
#define SYS_PLL_VE1_1_inst_adr                                                       "0x0045"
#define SYS_PLL_VE1_1_inst                                                           0x0045
#define SYS_PLL_VE1_1_REG_PLLVCPU_WDRST_shift                                        (22)
#define SYS_PLL_VE1_1_REG_PLLVCPU_WDRST_mask                                         (0x00400000)
#define SYS_PLL_VE1_1_REG_PLLVCPU_WDRST(data)                                        (0x00400000&((data)<<22))
#define SYS_PLL_VE1_1_REG_PLLVCPU_WDRST_src(data)                                    ((0x00400000&(data))>>22)
#define SYS_PLL_VE1_1_get_REG_PLLVCPU_WDRST(data)                                    ((0x00400000&(data))>>22)
#define SYS_PLL_VE1_1_REG_PLLVCPU_WDSET_shift                                        (21)
#define SYS_PLL_VE1_1_REG_PLLVCPU_WDSET_mask                                         (0x00200000)
#define SYS_PLL_VE1_1_REG_PLLVCPU_WDSET(data)                                        (0x00200000&((data)<<21))
#define SYS_PLL_VE1_1_REG_PLLVCPU_WDSET_src(data)                                    ((0x00200000&(data))>>21)
#define SYS_PLL_VE1_1_get_REG_PLLVCPU_WDSET(data)                                    ((0x00200000&(data))>>21)
#define SYS_PLL_VE1_1_REG_PLLVCPU_CS_shift                                           (19)
#define SYS_PLL_VE1_1_REG_PLLVCPU_CS_mask                                            (0x00180000)
#define SYS_PLL_VE1_1_REG_PLLVCPU_CS(data)                                           (0x00180000&((data)<<19))
#define SYS_PLL_VE1_1_REG_PLLVCPU_CS_src(data)                                       ((0x00180000&(data))>>19)
#define SYS_PLL_VE1_1_get_REG_PLLVCPU_CS(data)                                       ((0x00180000&(data))>>19)
#define SYS_PLL_VE1_1_REG_PLLVCPU_O_shift                                            (17)
#define SYS_PLL_VE1_1_REG_PLLVCPU_O_mask                                             (0x00060000)
#define SYS_PLL_VE1_1_REG_PLLVCPU_O(data)                                            (0x00060000&((data)<<17))
#define SYS_PLL_VE1_1_REG_PLLVCPU_O_src(data)                                        ((0x00060000&(data))>>17)
#define SYS_PLL_VE1_1_get_REG_PLLVCPU_O(data)                                        ((0x00060000&(data))>>17)
#define SYS_PLL_VE1_1_REG_PLLVCPU_RS_shift                                           (14)
#define SYS_PLL_VE1_1_REG_PLLVCPU_RS_mask                                            (0x0001C000)
#define SYS_PLL_VE1_1_REG_PLLVCPU_RS(data)                                           (0x0001C000&((data)<<14))
#define SYS_PLL_VE1_1_REG_PLLVCPU_RS_src(data)                                       ((0x0001C000&(data))>>14)
#define SYS_PLL_VE1_1_get_REG_PLLVCPU_RS(data)                                       ((0x0001C000&(data))>>14)
#define SYS_PLL_VE1_1_REG_PLLVCPU_N_shift                                            (12)
#define SYS_PLL_VE1_1_REG_PLLVCPU_N_mask                                             (0x00003000)
#define SYS_PLL_VE1_1_REG_PLLVCPU_N(data)                                            (0x00003000&((data)<<12))
#define SYS_PLL_VE1_1_REG_PLLVCPU_N_src(data)                                        ((0x00003000&(data))>>12)
#define SYS_PLL_VE1_1_get_REG_PLLVCPU_N(data)                                        ((0x00003000&(data))>>12)
#define SYS_PLL_VE1_1_REG_PLLVCPU_M_shift                                            (4)
#define SYS_PLL_VE1_1_REG_PLLVCPU_M_mask                                             (0x00000FF0)
#define SYS_PLL_VE1_1_REG_PLLVCPU_M(data)                                            (0x00000FF0&((data)<<4))
#define SYS_PLL_VE1_1_REG_PLLVCPU_M_src(data)                                        ((0x00000FF0&(data))>>4)
#define SYS_PLL_VE1_1_get_REG_PLLVCPU_M(data)                                        ((0x00000FF0&(data))>>4)
#define SYS_PLL_VE1_1_REG_PLLVCPU_IP_shift                                           (1)
#define SYS_PLL_VE1_1_REG_PLLVCPU_IP_mask                                            (0x0000000E)
#define SYS_PLL_VE1_1_REG_PLLVCPU_IP(data)                                           (0x0000000E&((data)<<1))
#define SYS_PLL_VE1_1_REG_PLLVCPU_IP_src(data)                                       ((0x0000000E&(data))>>1)
#define SYS_PLL_VE1_1_get_REG_PLLVCPU_IP(data)                                       ((0x0000000E&(data))>>1)
#define SYS_PLL_VE1_1_REG_PLLVCPU_TST_shift                                          (0)
#define SYS_PLL_VE1_1_REG_PLLVCPU_TST_mask                                           (0x00000001)
#define SYS_PLL_VE1_1_REG_PLLVCPU_TST(data)                                          (0x00000001&((data)<<0))
#define SYS_PLL_VE1_1_REG_PLLVCPU_TST_src(data)                                      ((0x00000001&(data))>>0)
#define SYS_PLL_VE1_1_get_REG_PLLVCPU_TST(data)                                      ((0x00000001&(data))>>0)


#define SYS_PLL_VE1_2                                                                0x98000118
#define SYS_PLL_VE1_2_reg_addr                                                       "0x98000118"
#define SYS_PLL_VE1_2_reg                                                            0x98000118
#define set_SYS_PLL_VE1_2_reg(data)   (*((volatile unsigned int*) SYS_PLL_VE1_2_reg)=data)
#define get_SYS_PLL_VE1_2_reg   (*((volatile unsigned int*) SYS_PLL_VE1_2_reg))
#define SYS_PLL_VE1_2_inst_adr                                                       "0x0046"
#define SYS_PLL_VE1_2_inst                                                           0x0046
#define SYS_PLL_VE1_2_REG_PLLVCPU_OEB_shift                                          (2)
#define SYS_PLL_VE1_2_REG_PLLVCPU_OEB_mask                                           (0x00000004)
#define SYS_PLL_VE1_2_REG_PLLVCPU_OEB(data)                                          (0x00000004&((data)<<2))
#define SYS_PLL_VE1_2_REG_PLLVCPU_OEB_src(data)                                      ((0x00000004&(data))>>2)
#define SYS_PLL_VE1_2_get_REG_PLLVCPU_OEB(data)                                      ((0x00000004&(data))>>2)
#define SYS_PLL_VE1_2_REG_PLLVCPU_RSTB_shift                                         (1)
#define SYS_PLL_VE1_2_REG_PLLVCPU_RSTB_mask                                          (0x00000002)
#define SYS_PLL_VE1_2_REG_PLLVCPU_RSTB(data)                                         (0x00000002&((data)<<1))
#define SYS_PLL_VE1_2_REG_PLLVCPU_RSTB_src(data)                                     ((0x00000002&(data))>>1)
#define SYS_PLL_VE1_2_get_REG_PLLVCPU_RSTB(data)                                     ((0x00000002&(data))>>1)
#define SYS_PLL_VE1_2_REG_PLLVCPU_POW_shift                                          (0)
#define SYS_PLL_VE1_2_REG_PLLVCPU_POW_mask                                           (0x00000001)
#define SYS_PLL_VE1_2_REG_PLLVCPU_POW(data)                                          (0x00000001&((data)<<0))
#define SYS_PLL_VE1_2_REG_PLLVCPU_POW_src(data)                                      ((0x00000001&(data))>>0)
#define SYS_PLL_VE1_2_get_REG_PLLVCPU_POW(data)                                      ((0x00000001&(data))>>0)


#define SYS_PLL_DDSA1                                                                0x98000120
#define SYS_PLL_DDSA1_reg_addr                                                       "0x98000120"
#define SYS_PLL_DDSA1_reg                                                            0x98000120
#define set_SYS_PLL_DDSA1_reg(data)   (*((volatile unsigned int*) SYS_PLL_DDSA1_reg)=data)
#define get_SYS_PLL_DDSA1_reg   (*((volatile unsigned int*) SYS_PLL_DDSA1_reg))
#define SYS_PLL_DDSA1_inst_adr                                                       "0x0048"
#define SYS_PLL_DDSA1_inst                                                           0x0048
#define SYS_PLL_DDSA1_REG_PLLDDSA_WDMODE_shift                                       (23)
#define SYS_PLL_DDSA1_REG_PLLDDSA_WDMODE_mask                                        (0x01800000)
#define SYS_PLL_DDSA1_REG_PLLDDSA_WDMODE(data)                                       (0x01800000&((data)<<23))
#define SYS_PLL_DDSA1_REG_PLLDDSA_WDMODE_src(data)                                   ((0x01800000&(data))>>23)
#define SYS_PLL_DDSA1_get_REG_PLLDDSA_WDMODE(data)                                   ((0x01800000&(data))>>23)
#define SYS_PLL_DDSA1_REG_PLLDDSA_RS_shift                                           (20)
#define SYS_PLL_DDSA1_REG_PLLDDSA_RS_mask                                            (0x00700000)
#define SYS_PLL_DDSA1_REG_PLLDDSA_RS(data)                                           (0x00700000&((data)<<20))
#define SYS_PLL_DDSA1_REG_PLLDDSA_RS_src(data)                                       ((0x00700000&(data))>>20)
#define SYS_PLL_DDSA1_get_REG_PLLDDSA_RS(data)                                       ((0x00700000&(data))>>20)
#define SYS_PLL_DDSA1_REG_PLLDDSA_O_shift                                            (18)
#define SYS_PLL_DDSA1_REG_PLLDDSA_O_mask                                             (0x000C0000)
#define SYS_PLL_DDSA1_REG_PLLDDSA_O(data)                                            (0x000C0000&((data)<<18))
#define SYS_PLL_DDSA1_REG_PLLDDSA_O_src(data)                                        ((0x000C0000&(data))>>18)
#define SYS_PLL_DDSA1_get_REG_PLLDDSA_O(data)                                        ((0x000C0000&(data))>>18)
#define SYS_PLL_DDSA1_REG_PLLDDSA_N_shift                                            (16)
#define SYS_PLL_DDSA1_REG_PLLDDSA_N_mask                                             (0x00030000)
#define SYS_PLL_DDSA1_REG_PLLDDSA_N(data)                                            (0x00030000&((data)<<16))
#define SYS_PLL_DDSA1_REG_PLLDDSA_N_src(data)                                        ((0x00030000&(data))>>16)
#define SYS_PLL_DDSA1_get_REG_PLLDDSA_N(data)                                        ((0x00030000&(data))>>16)
#define SYS_PLL_DDSA1_REG_PLLDDSA_IP_shift                                           (12)
#define SYS_PLL_DDSA1_REG_PLLDDSA_IP_mask                                            (0x0000F000)
#define SYS_PLL_DDSA1_REG_PLLDDSA_IP(data)                                           (0x0000F000&((data)<<12))
#define SYS_PLL_DDSA1_REG_PLLDDSA_IP_src(data)                                       ((0x0000F000&(data))>>12)
#define SYS_PLL_DDSA1_get_REG_PLLDDSA_IP(data)                                       ((0x0000F000&(data))>>12)
#define SYS_PLL_DDSA1_REG_PLLDDSA_CS_shift                                           (10)
#define SYS_PLL_DDSA1_REG_PLLDDSA_CS_mask                                            (0x00000C00)
#define SYS_PLL_DDSA1_REG_PLLDDSA_CS(data)                                           (0x00000C00&((data)<<10))
#define SYS_PLL_DDSA1_REG_PLLDDSA_CS_src(data)                                       ((0x00000C00&(data))>>10)
#define SYS_PLL_DDSA1_get_REG_PLLDDSA_CS(data)                                       ((0x00000C00&(data))>>10)
#define SYS_PLL_DDSA1_REG_PLLDDSA_CP_shift                                           (8)
#define SYS_PLL_DDSA1_REG_PLLDDSA_CP_mask                                            (0x00000300)
#define SYS_PLL_DDSA1_REG_PLLDDSA_CP(data)                                           (0x00000300&((data)<<8))
#define SYS_PLL_DDSA1_REG_PLLDDSA_CP_src(data)                                       ((0x00000300&(data))>>8)
#define SYS_PLL_DDSA1_get_REG_PLLDDSA_CP(data)                                       ((0x00000300&(data))>>8)
#define SYS_PLL_DDSA1_REG_PLLDDSA_VCORB_shift                                        (7)
#define SYS_PLL_DDSA1_REG_PLLDDSA_VCORB_mask                                         (0x00000080)
#define SYS_PLL_DDSA1_REG_PLLDDSA_VCORB(data)                                        (0x00000080&((data)<<7))
#define SYS_PLL_DDSA1_REG_PLLDDSA_VCORB_src(data)                                    ((0x00000080&(data))>>7)
#define SYS_PLL_DDSA1_get_REG_PLLDDSA_VCORB(data)                                    ((0x00000080&(data))>>7)
#define SYS_PLL_DDSA1_REG_PLLDDSA_TST_shift                                          (6)
#define SYS_PLL_DDSA1_REG_PLLDDSA_TST_mask                                           (0x00000040)
#define SYS_PLL_DDSA1_REG_PLLDDSA_TST(data)                                          (0x00000040&((data)<<6))
#define SYS_PLL_DDSA1_REG_PLLDDSA_TST_src(data)                                      ((0x00000040&(data))>>6)
#define SYS_PLL_DDSA1_get_REG_PLLDDSA_TST(data)                                      ((0x00000040&(data))>>6)
#define SYS_PLL_DDSA1_REG_PLLDDSA_PSTST_shift                                        (5)
#define SYS_PLL_DDSA1_REG_PLLDDSA_PSTST_mask                                         (0x00000020)
#define SYS_PLL_DDSA1_REG_PLLDDSA_PSTST(data)                                        (0x00000020&((data)<<5))
#define SYS_PLL_DDSA1_REG_PLLDDSA_PSTST_src(data)                                    ((0x00000020&(data))>>5)
#define SYS_PLL_DDSA1_get_REG_PLLDDSA_PSTST(data)                                    ((0x00000020&(data))>>5)


#define SYS_PLL_DDSA2                                                                0x98000128
#define SYS_PLL_DDSA2_reg_addr                                                       "0x98000128"
#define SYS_PLL_DDSA2_reg                                                            0x98000128
#define set_SYS_PLL_DDSA2_reg(data)   (*((volatile unsigned int*) SYS_PLL_DDSA2_reg)=data)
#define get_SYS_PLL_DDSA2_reg   (*((volatile unsigned int*) SYS_PLL_DDSA2_reg))
#define SYS_PLL_DDSA2_inst_adr                                                       "0x004A"
#define SYS_PLL_DDSA2_inst                                                           0x004A
#define SYS_PLL_DDSA2_REG_PLLDDSA_OEB_shift                                          (2)
#define SYS_PLL_DDSA2_REG_PLLDDSA_OEB_mask                                           (0x00000004)
#define SYS_PLL_DDSA2_REG_PLLDDSA_OEB(data)                                          (0x00000004&((data)<<2))
#define SYS_PLL_DDSA2_REG_PLLDDSA_OEB_src(data)                                      ((0x00000004&(data))>>2)
#define SYS_PLL_DDSA2_get_REG_PLLDDSA_OEB(data)                                      ((0x00000004&(data))>>2)
#define SYS_PLL_DDSA2_REG_PLLDDSA_RSTB_shift                                         (1)
#define SYS_PLL_DDSA2_REG_PLLDDSA_RSTB_mask                                          (0x00000002)
#define SYS_PLL_DDSA2_REG_PLLDDSA_RSTB(data)                                         (0x00000002&((data)<<1))
#define SYS_PLL_DDSA2_REG_PLLDDSA_RSTB_src(data)                                     ((0x00000002&(data))>>1)
#define SYS_PLL_DDSA2_get_REG_PLLDDSA_RSTB(data)                                     ((0x00000002&(data))>>1)
#define SYS_PLL_DDSA2_REG_PLLDDSA_POW_shift                                          (0)
#define SYS_PLL_DDSA2_REG_PLLDDSA_POW_mask                                           (0x00000001)
#define SYS_PLL_DDSA2_REG_PLLDDSA_POW(data)                                          (0x00000001&((data)<<0))
#define SYS_PLL_DDSA2_REG_PLLDDSA_POW_src(data)                                      ((0x00000001&(data))>>0)
#define SYS_PLL_DDSA2_get_REG_PLLDDSA_POW(data)                                      ((0x00000001&(data))>>0)


#define SYS_PLL_PSAUDA1                                                              0x98000130
#define SYS_PLL_PSAUDA1_reg_addr                                                     "0x98000130"
#define SYS_PLL_PSAUDA1_reg                                                          0x98000130
#define set_SYS_PLL_PSAUDA1_reg(data)   (*((volatile unsigned int*) SYS_PLL_PSAUDA1_reg)=data)
#define get_SYS_PLL_PSAUDA1_reg   (*((volatile unsigned int*) SYS_PLL_PSAUDA1_reg))
#define SYS_PLL_PSAUDA1_inst_adr                                                     "0x004C"
#define SYS_PLL_PSAUDA1_inst                                                         0x004C
#define SYS_PLL_PSAUDA1_write_en11_shift                                             (28)
#define SYS_PLL_PSAUDA1_write_en11_mask                                              (0x10000000)
#define SYS_PLL_PSAUDA1_write_en11(data)                                             (0x10000000&((data)<<28))
#define SYS_PLL_PSAUDA1_write_en11_src(data)                                         ((0x10000000&(data))>>28)
#define SYS_PLL_PSAUDA1_get_write_en11(data)                                         ((0x10000000&(data))>>28)
#define SYS_PLL_PSAUDA1_psaud_1a_phase_sel_shift                                     (27)
#define SYS_PLL_PSAUDA1_psaud_1a_phase_sel_mask                                      (0x08000000)
#define SYS_PLL_PSAUDA1_psaud_1a_phase_sel(data)                                     (0x08000000&((data)<<27))
#define SYS_PLL_PSAUDA1_psaud_1a_phase_sel_src(data)                                 ((0x08000000&(data))>>27)
#define SYS_PLL_PSAUDA1_get_psaud_1a_phase_sel(data)                                 ((0x08000000&(data))>>27)
#define SYS_PLL_PSAUDA1_psaud_2a_phase_sel_shift                                     (26)
#define SYS_PLL_PSAUDA1_psaud_2a_phase_sel_mask                                      (0x04000000)
#define SYS_PLL_PSAUDA1_psaud_2a_phase_sel(data)                                     (0x04000000&((data)<<26))
#define SYS_PLL_PSAUDA1_psaud_2a_phase_sel_src(data)                                 ((0x04000000&(data))>>26)
#define SYS_PLL_PSAUDA1_get_psaud_2a_phase_sel(data)                                 ((0x04000000&(data))>>26)
#define SYS_PLL_PSAUDA1_write_en10_shift                                             (25)
#define SYS_PLL_PSAUDA1_write_en10_mask                                              (0x02000000)
#define SYS_PLL_PSAUDA1_write_en10(data)                                             (0x02000000&((data)<<25))
#define SYS_PLL_PSAUDA1_write_en10_src(data)                                         ((0x02000000&(data))>>25)
#define SYS_PLL_PSAUDA1_get_write_en10(data)                                         ((0x02000000&(data))>>25)
#define SYS_PLL_PSAUDA1_pcr_a_smooth_en_shift                                        (24)
#define SYS_PLL_PSAUDA1_pcr_a_smooth_en_mask                                         (0x01000000)
#define SYS_PLL_PSAUDA1_pcr_a_smooth_en(data)                                        (0x01000000&((data)<<24))
#define SYS_PLL_PSAUDA1_pcr_a_smooth_en_src(data)                                    ((0x01000000&(data))>>24)
#define SYS_PLL_PSAUDA1_get_pcr_a_smooth_en(data)                                    ((0x01000000&(data))>>24)
#define SYS_PLL_PSAUDA1_write_en9_shift                                              (23)
#define SYS_PLL_PSAUDA1_write_en9_mask                                               (0x00800000)
#define SYS_PLL_PSAUDA1_write_en9(data)                                              (0x00800000&((data)<<23))
#define SYS_PLL_PSAUDA1_write_en9_src(data)                                          ((0x00800000&(data))>>23)
#define SYS_PLL_PSAUDA1_get_write_en9(data)                                          ((0x00800000&(data))>>23)
#define SYS_PLL_PSAUDA1_pcr_a_phase_sel_shift                                        (22)
#define SYS_PLL_PSAUDA1_pcr_a_phase_sel_mask                                         (0x00400000)
#define SYS_PLL_PSAUDA1_pcr_a_phase_sel(data)                                        (0x00400000&((data)<<22))
#define SYS_PLL_PSAUDA1_pcr_a_phase_sel_src(data)                                    ((0x00400000&(data))>>22)
#define SYS_PLL_PSAUDA1_get_pcr_a_phase_sel(data)                                    ((0x00400000&(data))>>22)
#define SYS_PLL_PSAUDA1_write_en8_shift                                              (21)
#define SYS_PLL_PSAUDA1_write_en8_mask                                               (0x00200000)
#define SYS_PLL_PSAUDA1_write_en8(data)                                              (0x00200000&((data)<<21))
#define SYS_PLL_PSAUDA1_write_en8_src(data)                                          ((0x00200000&(data))>>21)
#define SYS_PLL_PSAUDA1_get_write_en8(data)                                          ((0x00200000&(data))>>21)
#define SYS_PLL_PSAUDA1_pcr_a_ctl_en_shift                                           (20)
#define SYS_PLL_PSAUDA1_pcr_a_ctl_en_mask                                            (0x00100000)
#define SYS_PLL_PSAUDA1_pcr_a_ctl_en(data)                                           (0x00100000&((data)<<20))
#define SYS_PLL_PSAUDA1_pcr_a_ctl_en_src(data)                                       ((0x00100000&(data))>>20)
#define SYS_PLL_PSAUDA1_get_pcr_a_ctl_en(data)                                       ((0x00100000&(data))>>20)
#define SYS_PLL_PSAUDA1_write_en3_shift                                              (10)
#define SYS_PLL_PSAUDA1_write_en3_mask                                               (0x00000400)
#define SYS_PLL_PSAUDA1_write_en3(data)                                              (0x00000400&((data)<<10))
#define SYS_PLL_PSAUDA1_write_en3_src(data)                                          ((0x00000400&(data))>>10)
#define SYS_PLL_PSAUDA1_get_write_en3(data)                                          ((0x00000400&(data))>>10)
#define SYS_PLL_PSAUDA1_REG_PSAUD1A_FUPDN_shift                                      (9)
#define SYS_PLL_PSAUDA1_REG_PSAUD1A_FUPDN_mask                                       (0x00000200)
#define SYS_PLL_PSAUDA1_REG_PSAUD1A_FUPDN(data)                                      (0x00000200&((data)<<9))
#define SYS_PLL_PSAUDA1_REG_PSAUD1A_FUPDN_src(data)                                  ((0x00000200&(data))>>9)
#define SYS_PLL_PSAUDA1_get_REG_PSAUD1A_FUPDN(data)                                  ((0x00000200&(data))>>9)
#define SYS_PLL_PSAUDA1_REG_PSAUD1A_DIV_shift                                        (8)
#define SYS_PLL_PSAUDA1_REG_PSAUD1A_DIV_mask                                         (0x00000100)
#define SYS_PLL_PSAUDA1_REG_PSAUD1A_DIV(data)                                        (0x00000100&((data)<<8))
#define SYS_PLL_PSAUDA1_REG_PSAUD1A_DIV_src(data)                                    ((0x00000100&(data))>>8)
#define SYS_PLL_PSAUDA1_get_REG_PSAUD1A_DIV(data)                                    ((0x00000100&(data))>>8)
#define SYS_PLL_PSAUDA1_write_en2_shift                                              (7)
#define SYS_PLL_PSAUDA1_write_en2_mask                                               (0x00000080)
#define SYS_PLL_PSAUDA1_write_en2(data)                                              (0x00000080&((data)<<7))
#define SYS_PLL_PSAUDA1_write_en2_src(data)                                          ((0x00000080&(data))>>7)
#define SYS_PLL_PSAUDA1_get_write_en2(data)                                          ((0x00000080&(data))>>7)
#define SYS_PLL_PSAUDA1_REG_PSAUD1A_TST_shift                                        (6)
#define SYS_PLL_PSAUDA1_REG_PSAUD1A_TST_mask                                         (0x00000040)
#define SYS_PLL_PSAUDA1_REG_PSAUD1A_TST(data)                                        (0x00000040&((data)<<6))
#define SYS_PLL_PSAUDA1_REG_PSAUD1A_TST_src(data)                                    ((0x00000040&(data))>>6)
#define SYS_PLL_PSAUDA1_get_REG_PSAUD1A_TST(data)                                    ((0x00000040&(data))>>6)
#define SYS_PLL_PSAUDA1_REG_PSAUD1A_PSEN_shift                                       (5)
#define SYS_PLL_PSAUDA1_REG_PSAUD1A_PSEN_mask                                        (0x00000020)
#define SYS_PLL_PSAUDA1_REG_PSAUD1A_PSEN(data)                                       (0x00000020&((data)<<5))
#define SYS_PLL_PSAUDA1_REG_PSAUD1A_PSEN_src(data)                                   ((0x00000020&(data))>>5)
#define SYS_PLL_PSAUDA1_get_REG_PSAUD1A_PSEN(data)                                   ((0x00000020&(data))>>5)
#define SYS_PLL_PSAUDA1_write_en1_shift                                              (4)
#define SYS_PLL_PSAUDA1_write_en1_mask                                               (0x00000010)
#define SYS_PLL_PSAUDA1_write_en1(data)                                              (0x00000010&((data)<<4))
#define SYS_PLL_PSAUDA1_write_en1_src(data)                                          ((0x00000010&(data))>>4)
#define SYS_PLL_PSAUDA1_get_write_en1(data)                                          ((0x00000010&(data))>>4)
#define SYS_PLL_PSAUDA1_REG_PSAUD2A_FUPDN_shift                                      (3)
#define SYS_PLL_PSAUDA1_REG_PSAUD2A_FUPDN_mask                                       (0x00000008)
#define SYS_PLL_PSAUDA1_REG_PSAUD2A_FUPDN(data)                                      (0x00000008&((data)<<3))
#define SYS_PLL_PSAUDA1_REG_PSAUD2A_FUPDN_src(data)                                  ((0x00000008&(data))>>3)
#define SYS_PLL_PSAUDA1_get_REG_PSAUD2A_FUPDN(data)                                  ((0x00000008&(data))>>3)
#define SYS_PLL_PSAUDA1_REG_PSAUD2A_DIV_shift                                        (2)
#define SYS_PLL_PSAUDA1_REG_PSAUD2A_DIV_mask                                         (0x00000004)
#define SYS_PLL_PSAUDA1_REG_PSAUD2A_DIV(data)                                        (0x00000004&((data)<<2))
#define SYS_PLL_PSAUDA1_REG_PSAUD2A_DIV_src(data)                                    ((0x00000004&(data))>>2)
#define SYS_PLL_PSAUDA1_get_REG_PSAUD2A_DIV(data)                                    ((0x00000004&(data))>>2)
#define SYS_PLL_PSAUDA1_REG_PSAUD2A_TST_shift                                        (1)
#define SYS_PLL_PSAUDA1_REG_PSAUD2A_TST_mask                                         (0x00000002)
#define SYS_PLL_PSAUDA1_REG_PSAUD2A_TST(data)                                        (0x00000002&((data)<<1))
#define SYS_PLL_PSAUDA1_REG_PSAUD2A_TST_src(data)                                    ((0x00000002&(data))>>1)
#define SYS_PLL_PSAUDA1_get_REG_PSAUD2A_TST(data)                                    ((0x00000002&(data))>>1)
#define SYS_PLL_PSAUDA1_REG_PSAUD2A_PSEN_shift                                       (0)
#define SYS_PLL_PSAUDA1_REG_PSAUD2A_PSEN_mask                                        (0x00000001)
#define SYS_PLL_PSAUDA1_REG_PSAUD2A_PSEN(data)                                       (0x00000001&((data)<<0))
#define SYS_PLL_PSAUDA1_REG_PSAUD2A_PSEN_src(data)                                   ((0x00000001&(data))>>0)
#define SYS_PLL_PSAUDA1_get_REG_PSAUD2A_PSEN(data)                                   ((0x00000001&(data))>>0)


#define SYS_PLL_PSAUDA2                                                              0x98000134
#define SYS_PLL_PSAUDA2_reg_addr                                                     "0x98000134"
#define SYS_PLL_PSAUDA2_reg                                                          0x98000134
#define set_SYS_PLL_PSAUDA2_reg(data)   (*((volatile unsigned int*) SYS_PLL_PSAUDA2_reg)=data)
#define get_SYS_PLL_PSAUDA2_reg   (*((volatile unsigned int*) SYS_PLL_PSAUDA2_reg))
#define SYS_PLL_PSAUDA2_inst_adr                                                     "0x004D"
#define SYS_PLL_PSAUDA2_inst                                                         0x004D
#define SYS_PLL_PSAUDA2_REG_PSAUD1A_OEB_shift                                        (3)
#define SYS_PLL_PSAUDA2_REG_PSAUD1A_OEB_mask                                         (0x00000008)
#define SYS_PLL_PSAUDA2_REG_PSAUD1A_OEB(data)                                        (0x00000008&((data)<<3))
#define SYS_PLL_PSAUDA2_REG_PSAUD1A_OEB_src(data)                                    ((0x00000008&(data))>>3)
#define SYS_PLL_PSAUDA2_get_REG_PSAUD1A_OEB(data)                                    ((0x00000008&(data))>>3)
#define SYS_PLL_PSAUDA2_REG_PSAUD1A_RSTB_shift                                       (2)
#define SYS_PLL_PSAUDA2_REG_PSAUD1A_RSTB_mask                                        (0x00000004)
#define SYS_PLL_PSAUDA2_REG_PSAUD1A_RSTB(data)                                       (0x00000004&((data)<<2))
#define SYS_PLL_PSAUDA2_REG_PSAUD1A_RSTB_src(data)                                   ((0x00000004&(data))>>2)
#define SYS_PLL_PSAUDA2_get_REG_PSAUD1A_RSTB(data)                                   ((0x00000004&(data))>>2)
#define SYS_PLL_PSAUDA2_REG_PSAUD2A_OEB_shift                                        (1)
#define SYS_PLL_PSAUDA2_REG_PSAUD2A_OEB_mask                                         (0x00000002)
#define SYS_PLL_PSAUDA2_REG_PSAUD2A_OEB(data)                                        (0x00000002&((data)<<1))
#define SYS_PLL_PSAUDA2_REG_PSAUD2A_OEB_src(data)                                    ((0x00000002&(data))>>1)
#define SYS_PLL_PSAUDA2_get_REG_PSAUD2A_OEB(data)                                    ((0x00000002&(data))>>1)
#define SYS_PLL_PSAUDA2_REG_PSAUD2A_RSTB_shift                                       (0)
#define SYS_PLL_PSAUDA2_REG_PSAUD2A_RSTB_mask                                        (0x00000001)
#define SYS_PLL_PSAUDA2_REG_PSAUD2A_RSTB(data)                                       (0x00000001&((data)<<0))
#define SYS_PLL_PSAUDA2_REG_PSAUD2A_RSTB_src(data)                                   ((0x00000001&(data))>>0)
#define SYS_PLL_PSAUDA2_get_REG_PSAUD2A_RSTB(data)                                   ((0x00000001&(data))>>0)


#define SYS_PLL_DISP_HD1                                                             0x98000138
#define SYS_PLL_DISP_HD1_reg_addr                                                    "0x98000138"
#define SYS_PLL_DISP_HD1_reg                                                         0x98000138
#define set_SYS_PLL_DISP_HD1_reg(data)   (*((volatile unsigned int*) SYS_PLL_DISP_HD1_reg)=data)
#define get_SYS_PLL_DISP_HD1_reg   (*((volatile unsigned int*) SYS_PLL_DISP_HD1_reg))
#define SYS_PLL_DISP_HD1_inst_adr                                                    "0x004E"
#define SYS_PLL_DISP_HD1_inst                                                        0x004E
#define SYS_PLL_DISP_HD1_reserved_pll_disp_hd1_shift                                 (0)
#define SYS_PLL_DISP_HD1_reserved_pll_disp_hd1_mask                                  (0x00000001)
#define SYS_PLL_DISP_HD1_reserved_pll_disp_hd1(data)                                 (0x00000001&((data)<<0))
#define SYS_PLL_DISP_HD1_reserved_pll_disp_hd1_src(data)                             ((0x00000001&(data))>>0)
#define SYS_PLL_DISP_HD1_get_reserved_pll_disp_hd1(data)                             ((0x00000001&(data))>>0)


#define SYS_PLL_DISP_HD2                                                             0x9800013c
#define SYS_PLL_DISP_HD2_reg_addr                                                    "0x9800013C"
#define SYS_PLL_DISP_HD2_reg                                                         0x9800013C
#define set_SYS_PLL_DISP_HD2_reg(data)   (*((volatile unsigned int*) SYS_PLL_DISP_HD2_reg)=data)
#define get_SYS_PLL_DISP_HD2_reg   (*((volatile unsigned int*) SYS_PLL_DISP_HD2_reg))
#define SYS_PLL_DISP_HD2_inst_adr                                                    "0x004F"
#define SYS_PLL_DISP_HD2_inst                                                        0x004F
#define SYS_PLL_DISP_HD2_reserved_pll_disp_hd2_shift                                 (0)
#define SYS_PLL_DISP_HD2_reserved_pll_disp_hd2_mask                                  (0x00000001)
#define SYS_PLL_DISP_HD2_reserved_pll_disp_hd2(data)                                 (0x00000001&((data)<<0))
#define SYS_PLL_DISP_HD2_reserved_pll_disp_hd2_src(data)                             ((0x00000001&(data))>>0)
#define SYS_PLL_DISP_HD2_get_reserved_pll_disp_hd2(data)                             ((0x00000001&(data))>>0)


#define SYS_PLL1_TEST                                                                0x98000140
#define SYS_PLL1_TEST_reg_addr                                                       "0x98000140"
#define SYS_PLL1_TEST_reg                                                            0x98000140
#define set_SYS_PLL1_TEST_reg(data)   (*((volatile unsigned int*) SYS_PLL1_TEST_reg)=data)
#define get_SYS_PLL1_TEST_reg   (*((volatile unsigned int*) SYS_PLL1_TEST_reg))
#define SYS_PLL1_TEST_inst_adr                                                       "0x0050"
#define SYS_PLL1_TEST_inst                                                           0x0050
#define SYS_PLL1_TEST_REG_PLLTST_POW_shift                                           (4)
#define SYS_PLL1_TEST_REG_PLLTST_POW_mask                                            (0x00000010)
#define SYS_PLL1_TEST_REG_PLLTST_POW(data)                                           (0x00000010&((data)<<4))
#define SYS_PLL1_TEST_REG_PLLTST_POW_src(data)                                       ((0x00000010&(data))>>4)
#define SYS_PLL1_TEST_get_REG_PLLTST_POW(data)                                       ((0x00000010&(data))>>4)


#define SYS_PLL_BUS1                                                                 0x98000164
#define SYS_PLL_BUS1_reg_addr                                                        "0x98000164"
#define SYS_PLL_BUS1_reg                                                             0x98000164
#define set_SYS_PLL_BUS1_reg(data)   (*((volatile unsigned int*) SYS_PLL_BUS1_reg)=data)
#define get_SYS_PLL_BUS1_reg   (*((volatile unsigned int*) SYS_PLL_BUS1_reg))
#define SYS_PLL_BUS1_inst_adr                                                        "0x0059"
#define SYS_PLL_BUS1_inst                                                            0x0059
#define SYS_PLL_BUS1_REG_PLLBUS_RESER_shift                                          (19)
#define SYS_PLL_BUS1_REG_PLLBUS_RESER_mask                                           (0x07F80000)
#define SYS_PLL_BUS1_REG_PLLBUS_RESER(data)                                          (0x07F80000&((data)<<19))
#define SYS_PLL_BUS1_REG_PLLBUS_RESER_src(data)                                      ((0x07F80000&(data))>>19)
#define SYS_PLL_BUS1_get_REG_PLLBUS_RESER(data)                                      ((0x07F80000&(data))>>19)
#define SYS_PLL_BUS1_REG_PLLBUS_PDIV_shift                                           (17)
#define SYS_PLL_BUS1_REG_PLLBUS_PDIV_mask                                            (0x00060000)
#define SYS_PLL_BUS1_REG_PLLBUS_PDIV(data)                                           (0x00060000&((data)<<17))
#define SYS_PLL_BUS1_REG_PLLBUS_PDIV_src(data)                                       ((0x00060000&(data))>>17)
#define SYS_PLL_BUS1_get_REG_PLLBUS_PDIV(data)                                       ((0x00060000&(data))>>17)
#define SYS_PLL_BUS1_REG_PLLBUS_LPF_RS_shift                                         (14)
#define SYS_PLL_BUS1_REG_PLLBUS_LPF_RS_mask                                          (0x0001C000)
#define SYS_PLL_BUS1_REG_PLLBUS_LPF_RS(data)                                         (0x0001C000&((data)<<14))
#define SYS_PLL_BUS1_REG_PLLBUS_LPF_RS_src(data)                                     ((0x0001C000&(data))>>14)
#define SYS_PLL_BUS1_get_REG_PLLBUS_LPF_RS(data)                                     ((0x0001C000&(data))>>14)
#define SYS_PLL_BUS1_REG_PLLBUS_LPF_CS_shift                                         (12)
#define SYS_PLL_BUS1_REG_PLLBUS_LPF_CS_mask                                          (0x00003000)
#define SYS_PLL_BUS1_REG_PLLBUS_LPF_CS(data)                                         (0x00003000&((data)<<12))
#define SYS_PLL_BUS1_REG_PLLBUS_LPF_CS_src(data)                                     ((0x00003000&(data))>>12)
#define SYS_PLL_BUS1_get_REG_PLLBUS_LPF_CS(data)                                     ((0x00003000&(data))>>12)
#define SYS_PLL_BUS1_REG_PLLBUS_ICP_shift                                            (9)
#define SYS_PLL_BUS1_REG_PLLBUS_ICP_mask                                             (0x00000E00)
#define SYS_PLL_BUS1_REG_PLLBUS_ICP(data)                                            (0x00000E00&((data)<<9))
#define SYS_PLL_BUS1_REG_PLLBUS_ICP_src(data)                                        ((0x00000E00&(data))>>9)
#define SYS_PLL_BUS1_get_REG_PLLBUS_ICP(data)                                        ((0x00000E00&(data))>>9)
#define SYS_PLL_BUS1_REG_PLLBUS_WDSET_shift                                          (8)
#define SYS_PLL_BUS1_REG_PLLBUS_WDSET_mask                                           (0x00000100)
#define SYS_PLL_BUS1_REG_PLLBUS_WDSET(data)                                          (0x00000100&((data)<<8))
#define SYS_PLL_BUS1_REG_PLLBUS_WDSET_src(data)                                      ((0x00000100&(data))>>8)
#define SYS_PLL_BUS1_get_REG_PLLBUS_WDSET(data)                                      ((0x00000100&(data))>>8)
#define SYS_PLL_BUS1_REG_PLLBUS_WDRST_shift                                          (7)
#define SYS_PLL_BUS1_REG_PLLBUS_WDRST_mask                                           (0x00000080)
#define SYS_PLL_BUS1_REG_PLLBUS_WDRST(data)                                          (0x00000080&((data)<<7))
#define SYS_PLL_BUS1_REG_PLLBUS_WDRST_src(data)                                      ((0x00000080&(data))>>7)
#define SYS_PLL_BUS1_get_REG_PLLBUS_WDRST(data)                                      ((0x00000080&(data))>>7)
#define SYS_PLL_BUS1_REG_PLLBUS_TESTSEL_shift                                        (6)
#define SYS_PLL_BUS1_REG_PLLBUS_TESTSEL_mask                                         (0x00000040)
#define SYS_PLL_BUS1_REG_PLLBUS_TESTSEL(data)                                        (0x00000040&((data)<<6))
#define SYS_PLL_BUS1_REG_PLLBUS_TESTSEL_src(data)                                    ((0x00000040&(data))>>6)
#define SYS_PLL_BUS1_get_REG_PLLBUS_TESTSEL(data)                                    ((0x00000040&(data))>>6)
#define SYS_PLL_BUS1_REG_PLLBUS_SEL_CCO_shift                                        (5)
#define SYS_PLL_BUS1_REG_PLLBUS_SEL_CCO_mask                                         (0x00000020)
#define SYS_PLL_BUS1_REG_PLLBUS_SEL_CCO(data)                                        (0x00000020&((data)<<5))
#define SYS_PLL_BUS1_REG_PLLBUS_SEL_CCO_src(data)                                    ((0x00000020&(data))>>5)
#define SYS_PLL_BUS1_get_REG_PLLBUS_SEL_CCO(data)                                    ((0x00000020&(data))>>5)
#define SYS_PLL_BUS1_REG_PLLBUS_PDIV_BPS_shift                                       (4)
#define SYS_PLL_BUS1_REG_PLLBUS_PDIV_BPS_mask                                        (0x00000010)
#define SYS_PLL_BUS1_REG_PLLBUS_PDIV_BPS(data)                                       (0x00000010&((data)<<4))
#define SYS_PLL_BUS1_REG_PLLBUS_PDIV_BPS_src(data)                                   ((0x00000010&(data))>>4)
#define SYS_PLL_BUS1_get_REG_PLLBUS_PDIV_BPS(data)                                   ((0x00000010&(data))>>4)
#define SYS_PLL_BUS1_REG_PLLBUS_DBUG_EN_shift                                        (3)
#define SYS_PLL_BUS1_REG_PLLBUS_DBUG_EN_mask                                         (0x00000008)
#define SYS_PLL_BUS1_REG_PLLBUS_DBUG_EN(data)                                        (0x00000008&((data)<<3))
#define SYS_PLL_BUS1_REG_PLLBUS_DBUG_EN_src(data)                                    ((0x00000008&(data))>>3)
#define SYS_PLL_BUS1_get_REG_PLLBUS_DBUG_EN(data)                                    ((0x00000008&(data))>>3)


#define SYS_PLL_BUS2                                                                 0x9800016C
#define SYS_PLL_BUS2_reg_addr                                                        "0x9800016C"
#define SYS_PLL_BUS2_reg                                                             0x9800016C
#define set_SYS_PLL_BUS2_reg(data)   (*((volatile unsigned int*) SYS_PLL_BUS2_reg)=data)
#define get_SYS_PLL_BUS2_reg   (*((volatile unsigned int*) SYS_PLL_BUS2_reg))
#define SYS_PLL_BUS2_inst_adr                                                        "0x005B"
#define SYS_PLL_BUS2_inst                                                            0x005B
#define SYS_PLL_BUS2_REG_PLLBUS_OEB_shift                                            (2)
#define SYS_PLL_BUS2_REG_PLLBUS_OEB_mask                                             (0x00000004)
#define SYS_PLL_BUS2_REG_PLLBUS_OEB(data)                                            (0x00000004&((data)<<2))
#define SYS_PLL_BUS2_REG_PLLBUS_OEB_src(data)                                        ((0x00000004&(data))>>2)
#define SYS_PLL_BUS2_get_REG_PLLBUS_OEB(data)                                        ((0x00000004&(data))>>2)
#define SYS_PLL_BUS2_REG_PLLBUS_RSTB_shift                                           (1)
#define SYS_PLL_BUS2_REG_PLLBUS_RSTB_mask                                            (0x00000002)
#define SYS_PLL_BUS2_REG_PLLBUS_RSTB(data)                                           (0x00000002&((data)<<1))
#define SYS_PLL_BUS2_REG_PLLBUS_RSTB_src(data)                                       ((0x00000002&(data))>>1)
#define SYS_PLL_BUS2_get_REG_PLLBUS_RSTB(data)                                       ((0x00000002&(data))>>1)
#define SYS_PLL_BUS2_REG_PLLBUS_POW_shift                                            (0)
#define SYS_PLL_BUS2_REG_PLLBUS_POW_mask                                             (0x00000001)
#define SYS_PLL_BUS2_REG_PLLBUS_POW(data)                                            (0x00000001&((data)<<0))
#define SYS_PLL_BUS2_REG_PLLBUS_POW_src(data)                                        ((0x00000001&(data))>>0)
#define SYS_PLL_BUS2_get_REG_PLLBUS_POW(data)                                        ((0x00000001&(data))>>0)


#define SYS_PLL_WDOUT                                                                0x98000170
#define SYS_PLL_WDOUT_reg_addr                                                       "0x98000170"
#define SYS_PLL_WDOUT_reg                                                            0x98000170
#define set_SYS_PLL_WDOUT_reg(data)   (*((volatile unsigned int*) SYS_PLL_WDOUT_reg)=data)
#define get_SYS_PLL_WDOUT_reg   (*((volatile unsigned int*) SYS_PLL_WDOUT_reg))
#define SYS_PLL_WDOUT_inst_adr                                                       "0x005C"
#define SYS_PLL_WDOUT_inst                                                           0x005C
#define SYS_PLL_WDOUT_REG_EDPPLL_WDO_shift                                           (14)
#define SYS_PLL_WDOUT_REG_EDPPLL_WDO_mask                                            (0x00004000)
#define SYS_PLL_WDOUT_REG_EDPPLL_WDO(data)                                           (0x00004000&((data)<<14))
#define SYS_PLL_WDOUT_REG_EDPPLL_WDO_src(data)                                       ((0x00004000&(data))>>14)
#define SYS_PLL_WDOUT_get_REG_EDPPLL_WDO(data)                                       ((0x00004000&(data))>>14)
#define SYS_PLL_WDOUT_REG_PIXELPLL_WDO_shift                                         (13)
#define SYS_PLL_WDOUT_REG_PIXELPLL_WDO_mask                                          (0x00002000)
#define SYS_PLL_WDOUT_REG_PIXELPLL_WDO(data)                                         (0x00002000&((data)<<13))
#define SYS_PLL_WDOUT_REG_PIXELPLL_WDO_src(data)                                     ((0x00002000&(data))>>13)
#define SYS_PLL_WDOUT_get_REG_PIXELPLL_WDO(data)                                     ((0x00002000&(data))>>13)
#define SYS_PLL_WDOUT_REG_PLLGPU_WDOUT_shift                                         (12)
#define SYS_PLL_WDOUT_REG_PLLGPU_WDOUT_mask                                          (0x00001000)
#define SYS_PLL_WDOUT_REG_PLLGPU_WDOUT(data)                                         (0x00001000&((data)<<12))
#define SYS_PLL_WDOUT_REG_PLLGPU_WDOUT_src(data)                                     ((0x00001000&(data))>>12)
#define SYS_PLL_WDOUT_get_REG_PLLGPU_WDOUT(data)                                     ((0x00001000&(data))>>12)
#define SYS_PLL_WDOUT_REG_PLLBUS_WDOUT_H_shift                                       (10)
#define SYS_PLL_WDOUT_REG_PLLBUS_WDOUT_H_mask                                        (0x00000400)
#define SYS_PLL_WDOUT_REG_PLLBUS_WDOUT_H(data)                                       (0x00000400&((data)<<10))
#define SYS_PLL_WDOUT_REG_PLLBUS_WDOUT_H_src(data)                                   ((0x00000400&(data))>>10)
#define SYS_PLL_WDOUT_get_REG_PLLBUS_WDOUT_H(data)                                   ((0x00000400&(data))>>10)
#define SYS_PLL_WDOUT_REG_PLLVODMA_WDOUT_shift                                       (8)
#define SYS_PLL_WDOUT_REG_PLLVODMA_WDOUT_mask                                        (0x00000100)
#define SYS_PLL_WDOUT_REG_PLLVODMA_WDOUT(data)                                       (0x00000100&((data)<<8))
#define SYS_PLL_WDOUT_REG_PLLVODMA_WDOUT_src(data)                                   ((0x00000100&(data))>>8)
#define SYS_PLL_WDOUT_get_REG_PLLVODMA_WDOUT(data)                                   ((0x00000100&(data))>>8)
#define SYS_PLL_WDOUT_REG_PLLVCPU_WDOUT_2_shift                                      (7)
#define SYS_PLL_WDOUT_REG_PLLVCPU_WDOUT_2_mask                                       (0x00000080)
#define SYS_PLL_WDOUT_REG_PLLVCPU_WDOUT_2(data)                                      (0x00000080&((data)<<7))
#define SYS_PLL_WDOUT_REG_PLLVCPU_WDOUT_2_src(data)                                  ((0x00000080&(data))>>7)
#define SYS_PLL_WDOUT_get_REG_PLLVCPU_WDOUT_2(data)                                  ((0x00000080&(data))>>7)
#define SYS_PLL_WDOUT_REG_PLLBUS_WDOUT_shift                                         (6)
#define SYS_PLL_WDOUT_REG_PLLBUS_WDOUT_mask                                          (0x00000040)
#define SYS_PLL_WDOUT_REG_PLLBUS_WDOUT(data)                                         (0x00000040&((data)<<6))
#define SYS_PLL_WDOUT_REG_PLLBUS_WDOUT_src(data)                                     ((0x00000040&(data))>>6)
#define SYS_PLL_WDOUT_get_REG_PLLBUS_WDOUT(data)                                     ((0x00000040&(data))>>6)
#define SYS_PLL_WDOUT_REG_PLLDDSB_WDOUT_shift                                        (4)
#define SYS_PLL_WDOUT_REG_PLLDDSB_WDOUT_mask                                         (0x00000010)
#define SYS_PLL_WDOUT_REG_PLLDDSB_WDOUT(data)                                        (0x00000010&((data)<<4))
#define SYS_PLL_WDOUT_REG_PLLDDSB_WDOUT_src(data)                                    ((0x00000010&(data))>>4)
#define SYS_PLL_WDOUT_get_REG_PLLDDSB_WDOUT(data)                                    ((0x00000010&(data))>>4)
#define SYS_PLL_WDOUT_REG_PLLDDSA_WDOUT_shift                                        (3)
#define SYS_PLL_WDOUT_REG_PLLDDSA_WDOUT_mask                                         (0x00000008)
#define SYS_PLL_WDOUT_REG_PLLDDSA_WDOUT(data)                                        (0x00000008&((data)<<3))
#define SYS_PLL_WDOUT_REG_PLLDDSA_WDOUT_src(data)                                    ((0x00000008&(data))>>3)
#define SYS_PLL_WDOUT_get_REG_PLLDDSA_WDOUT(data)                                    ((0x00000008&(data))>>3)
#define SYS_PLL_WDOUT_REG_PLLVCPU_WDOUT_shift                                        (2)
#define SYS_PLL_WDOUT_REG_PLLVCPU_WDOUT_mask                                         (0x00000004)
#define SYS_PLL_WDOUT_REG_PLLVCPU_WDOUT(data)                                        (0x00000004&((data)<<2))
#define SYS_PLL_WDOUT_REG_PLLVCPU_WDOUT_src(data)                                    ((0x00000004&(data))>>2)
#define SYS_PLL_WDOUT_get_REG_PLLVCPU_WDOUT(data)                                    ((0x00000004&(data))>>2)
#define SYS_PLL_WDOUT_REG_PLLACPU_WDOUT_shift                                        (1)
#define SYS_PLL_WDOUT_REG_PLLACPU_WDOUT_mask                                         (0x00000002)
#define SYS_PLL_WDOUT_REG_PLLACPU_WDOUT(data)                                        (0x00000002&((data)<<1))
#define SYS_PLL_WDOUT_REG_PLLACPU_WDOUT_src(data)                                    ((0x00000002&(data))>>1)
#define SYS_PLL_WDOUT_get_REG_PLLACPU_WDOUT(data)                                    ((0x00000002&(data))>>1)


#define SYS_PLL_DDSB1                                                                0x98000174
#define SYS_PLL_DDSB1_reg_addr                                                       "0x98000174"
#define SYS_PLL_DDSB1_reg                                                            0x98000174
#define set_SYS_PLL_DDSB1_reg(data)   (*((volatile unsigned int*) SYS_PLL_DDSB1_reg)=data)
#define get_SYS_PLL_DDSB1_reg   (*((volatile unsigned int*) SYS_PLL_DDSB1_reg))
#define SYS_PLL_DDSB1_inst_adr                                                       "0x005D"
#define SYS_PLL_DDSB1_inst                                                           0x005D
#define SYS_PLL_DDSB1_REG_PLLDDSB_WDMODE_shift                                       (23)
#define SYS_PLL_DDSB1_REG_PLLDDSB_WDMODE_mask                                        (0x01800000)
#define SYS_PLL_DDSB1_REG_PLLDDSB_WDMODE(data)                                       (0x01800000&((data)<<23))
#define SYS_PLL_DDSB1_REG_PLLDDSB_WDMODE_src(data)                                   ((0x01800000&(data))>>23)
#define SYS_PLL_DDSB1_get_REG_PLLDDSB_WDMODE(data)                                   ((0x01800000&(data))>>23)
#define SYS_PLL_DDSB1_REG_PLLDDSB_RS_shift                                           (20)
#define SYS_PLL_DDSB1_REG_PLLDDSB_RS_mask                                            (0x00700000)
#define SYS_PLL_DDSB1_REG_PLLDDSB_RS(data)                                           (0x00700000&((data)<<20))
#define SYS_PLL_DDSB1_REG_PLLDDSB_RS_src(data)                                       ((0x00700000&(data))>>20)
#define SYS_PLL_DDSB1_get_REG_PLLDDSB_RS(data)                                       ((0x00700000&(data))>>20)
#define SYS_PLL_DDSB1_REG_PLLDDSB_O_shift                                            (18)
#define SYS_PLL_DDSB1_REG_PLLDDSB_O_mask                                             (0x000C0000)
#define SYS_PLL_DDSB1_REG_PLLDDSB_O(data)                                            (0x000C0000&((data)<<18))
#define SYS_PLL_DDSB1_REG_PLLDDSB_O_src(data)                                        ((0x000C0000&(data))>>18)
#define SYS_PLL_DDSB1_get_REG_PLLDDSB_O(data)                                        ((0x000C0000&(data))>>18)
#define SYS_PLL_DDSB1_REG_PLLDDSB_N_shift                                            (16)
#define SYS_PLL_DDSB1_REG_PLLDDSB_N_mask                                             (0x00030000)
#define SYS_PLL_DDSB1_REG_PLLDDSB_N(data)                                            (0x00030000&((data)<<16))
#define SYS_PLL_DDSB1_REG_PLLDDSB_N_src(data)                                        ((0x00030000&(data))>>16)
#define SYS_PLL_DDSB1_get_REG_PLLDDSB_N(data)                                        ((0x00030000&(data))>>16)
#define SYS_PLL_DDSB1_REG_PLLDDSB_IP_shift                                           (12)
#define SYS_PLL_DDSB1_REG_PLLDDSB_IP_mask                                            (0x0000F000)
#define SYS_PLL_DDSB1_REG_PLLDDSB_IP(data)                                           (0x0000F000&((data)<<12))
#define SYS_PLL_DDSB1_REG_PLLDDSB_IP_src(data)                                       ((0x0000F000&(data))>>12)
#define SYS_PLL_DDSB1_get_REG_PLLDDSB_IP(data)                                       ((0x0000F000&(data))>>12)
#define SYS_PLL_DDSB1_REG_PLLDDSB_CS_shift                                           (10)
#define SYS_PLL_DDSB1_REG_PLLDDSB_CS_mask                                            (0x00000C00)
#define SYS_PLL_DDSB1_REG_PLLDDSB_CS(data)                                           (0x00000C00&((data)<<10))
#define SYS_PLL_DDSB1_REG_PLLDDSB_CS_src(data)                                       ((0x00000C00&(data))>>10)
#define SYS_PLL_DDSB1_get_REG_PLLDDSB_CS(data)                                       ((0x00000C00&(data))>>10)
#define SYS_PLL_DDSB1_REG_PLLDDSB_CP_shift                                           (8)
#define SYS_PLL_DDSB1_REG_PLLDDSB_CP_mask                                            (0x00000300)
#define SYS_PLL_DDSB1_REG_PLLDDSB_CP(data)                                           (0x00000300&((data)<<8))
#define SYS_PLL_DDSB1_REG_PLLDDSB_CP_src(data)                                       ((0x00000300&(data))>>8)
#define SYS_PLL_DDSB1_get_REG_PLLDDSB_CP(data)                                       ((0x00000300&(data))>>8)
#define SYS_PLL_DDSB1_REG_PLLDDSB_VCORB_shift                                        (7)
#define SYS_PLL_DDSB1_REG_PLLDDSB_VCORB_mask                                         (0x00000080)
#define SYS_PLL_DDSB1_REG_PLLDDSB_VCORB(data)                                        (0x00000080&((data)<<7))
#define SYS_PLL_DDSB1_REG_PLLDDSB_VCORB_src(data)                                    ((0x00000080&(data))>>7)
#define SYS_PLL_DDSB1_get_REG_PLLDDSB_VCORB(data)                                    ((0x00000080&(data))>>7)
#define SYS_PLL_DDSB1_REG_PLLDDSB_TST_shift                                          (6)
#define SYS_PLL_DDSB1_REG_PLLDDSB_TST_mask                                           (0x00000040)
#define SYS_PLL_DDSB1_REG_PLLDDSB_TST(data)                                          (0x00000040&((data)<<6))
#define SYS_PLL_DDSB1_REG_PLLDDSB_TST_src(data)                                      ((0x00000040&(data))>>6)
#define SYS_PLL_DDSB1_get_REG_PLLDDSB_TST(data)                                      ((0x00000040&(data))>>6)
#define SYS_PLL_DDSB1_REG_PLLDDSB_PSTST_shift                                        (5)
#define SYS_PLL_DDSB1_REG_PLLDDSB_PSTST_mask                                         (0x00000020)
#define SYS_PLL_DDSB1_REG_PLLDDSB_PSTST(data)                                        (0x00000020&((data)<<5))
#define SYS_PLL_DDSB1_REG_PLLDDSB_PSTST_src(data)                                    ((0x00000020&(data))>>5)
#define SYS_PLL_DDSB1_get_REG_PLLDDSB_PSTST(data)                                    ((0x00000020&(data))>>5)


#define SYS_PLL_DDSB2                                                                0x98000178
#define SYS_PLL_DDSB2_reg_addr                                                       "0x98000178"
#define SYS_PLL_DDSB2_reg                                                            0x98000178
#define set_SYS_PLL_DDSB2_reg(data)   (*((volatile unsigned int*) SYS_PLL_DDSB2_reg)=data)
#define get_SYS_PLL_DDSB2_reg   (*((volatile unsigned int*) SYS_PLL_DDSB2_reg))
#define SYS_PLL_DDSB2_inst_adr                                                       "0x005E"
#define SYS_PLL_DDSB2_inst                                                           0x005E
#define SYS_PLL_DDSB2_REG_PLLDDSB_OEB_shift                                          (2)
#define SYS_PLL_DDSB2_REG_PLLDDSB_OEB_mask                                           (0x00000004)
#define SYS_PLL_DDSB2_REG_PLLDDSB_OEB(data)                                          (0x00000004&((data)<<2))
#define SYS_PLL_DDSB2_REG_PLLDDSB_OEB_src(data)                                      ((0x00000004&(data))>>2)
#define SYS_PLL_DDSB2_get_REG_PLLDDSB_OEB(data)                                      ((0x00000004&(data))>>2)
#define SYS_PLL_DDSB2_REG_PLLDDSB_RSTB_shift                                         (1)
#define SYS_PLL_DDSB2_REG_PLLDDSB_RSTB_mask                                          (0x00000002)
#define SYS_PLL_DDSB2_REG_PLLDDSB_RSTB(data)                                         (0x00000002&((data)<<1))
#define SYS_PLL_DDSB2_REG_PLLDDSB_RSTB_src(data)                                     ((0x00000002&(data))>>1)
#define SYS_PLL_DDSB2_get_REG_PLLDDSB_RSTB(data)                                     ((0x00000002&(data))>>1)
#define SYS_PLL_DDSB2_REG_PLLDDSB_POW_shift                                          (0)
#define SYS_PLL_DDSB2_REG_PLLDDSB_POW_mask                                           (0x00000001)
#define SYS_PLL_DDSB2_REG_PLLDDSB_POW(data)                                          (0x00000001&((data)<<0))
#define SYS_PLL_DDSB2_REG_PLLDDSB_POW_src(data)                                      ((0x00000001&(data))>>0)
#define SYS_PLL_DDSB2_get_REG_PLLDDSB_POW(data)                                      ((0x00000001&(data))>>0)


#define SYS_PLL_PSAUDB1                                                              0x98000188
#define SYS_PLL_PSAUDB1_reg_addr                                                     "0x98000188"
#define SYS_PLL_PSAUDB1_reg                                                          0x98000188
#define set_SYS_PLL_PSAUDB1_reg(data)   (*((volatile unsigned int*) SYS_PLL_PSAUDB1_reg)=data)
#define get_SYS_PLL_PSAUDB1_reg   (*((volatile unsigned int*) SYS_PLL_PSAUDB1_reg))
#define SYS_PLL_PSAUDB1_inst_adr                                                     "0x0062"
#define SYS_PLL_PSAUDB1_inst                                                         0x0062
#define SYS_PLL_PSAUDB1_write_en10_shift                                             (25)
#define SYS_PLL_PSAUDB1_write_en10_mask                                              (0x02000000)
#define SYS_PLL_PSAUDB1_write_en10(data)                                             (0x02000000&((data)<<25))
#define SYS_PLL_PSAUDB1_write_en10_src(data)                                         ((0x02000000&(data))>>25)
#define SYS_PLL_PSAUDB1_get_write_en10(data)                                         ((0x02000000&(data))>>25)
#define SYS_PLL_PSAUDB1_pcr_b_smooth_en_shift                                        (24)
#define SYS_PLL_PSAUDB1_pcr_b_smooth_en_mask                                         (0x01000000)
#define SYS_PLL_PSAUDB1_pcr_b_smooth_en(data)                                        (0x01000000&((data)<<24))
#define SYS_PLL_PSAUDB1_pcr_b_smooth_en_src(data)                                    ((0x01000000&(data))>>24)
#define SYS_PLL_PSAUDB1_get_pcr_b_smooth_en(data)                                    ((0x01000000&(data))>>24)
#define SYS_PLL_PSAUDB1_write_en9_shift                                              (23)
#define SYS_PLL_PSAUDB1_write_en9_mask                                               (0x00800000)
#define SYS_PLL_PSAUDB1_write_en9(data)                                              (0x00800000&((data)<<23))
#define SYS_PLL_PSAUDB1_write_en9_src(data)                                          ((0x00800000&(data))>>23)
#define SYS_PLL_PSAUDB1_get_write_en9(data)                                          ((0x00800000&(data))>>23)
#define SYS_PLL_PSAUDB1_pcr_b_phase_sel_shift                                        (22)
#define SYS_PLL_PSAUDB1_pcr_b_phase_sel_mask                                         (0x00400000)
#define SYS_PLL_PSAUDB1_pcr_b_phase_sel(data)                                        (0x00400000&((data)<<22))
#define SYS_PLL_PSAUDB1_pcr_b_phase_sel_src(data)                                    ((0x00400000&(data))>>22)
#define SYS_PLL_PSAUDB1_get_pcr_b_phase_sel(data)                                    ((0x00400000&(data))>>22)
#define SYS_PLL_PSAUDB1_write_en8_shift                                              (21)
#define SYS_PLL_PSAUDB1_write_en8_mask                                               (0x00200000)
#define SYS_PLL_PSAUDB1_write_en8(data)                                              (0x00200000&((data)<<21))
#define SYS_PLL_PSAUDB1_write_en8_src(data)                                          ((0x00200000&(data))>>21)
#define SYS_PLL_PSAUDB1_get_write_en8(data)                                          ((0x00200000&(data))>>21)
#define SYS_PLL_PSAUDB1_pcr_b_ctl_en_shift                                           (20)
#define SYS_PLL_PSAUDB1_pcr_b_ctl_en_mask                                            (0x00100000)
#define SYS_PLL_PSAUDB1_pcr_b_ctl_en(data)                                           (0x00100000&((data)<<20))
#define SYS_PLL_PSAUDB1_pcr_b_ctl_en_src(data)                                       ((0x00100000&(data))>>20)
#define SYS_PLL_PSAUDB1_get_pcr_b_ctl_en(data)                                       ((0x00100000&(data))>>20)
#define SYS_PLL_PSAUDB1_write_en3_shift                                              (10)
#define SYS_PLL_PSAUDB1_write_en3_mask                                               (0x00000400)
#define SYS_PLL_PSAUDB1_write_en3(data)                                              (0x00000400&((data)<<10))
#define SYS_PLL_PSAUDB1_write_en3_src(data)                                          ((0x00000400&(data))>>10)
#define SYS_PLL_PSAUDB1_get_write_en3(data)                                          ((0x00000400&(data))>>10)
#define SYS_PLL_PSAUDB1_REG_PSAUD1B_FUPDN_shift                                      (9)
#define SYS_PLL_PSAUDB1_REG_PSAUD1B_FUPDN_mask                                       (0x00000200)
#define SYS_PLL_PSAUDB1_REG_PSAUD1B_FUPDN(data)                                      (0x00000200&((data)<<9))
#define SYS_PLL_PSAUDB1_REG_PSAUD1B_FUPDN_src(data)                                  ((0x00000200&(data))>>9)
#define SYS_PLL_PSAUDB1_get_REG_PSAUD1B_FUPDN(data)                                  ((0x00000200&(data))>>9)
#define SYS_PLL_PSAUDB1_REG_PSAUD1B_DIV_shift                                        (8)
#define SYS_PLL_PSAUDB1_REG_PSAUD1B_DIV_mask                                         (0x00000100)
#define SYS_PLL_PSAUDB1_REG_PSAUD1B_DIV(data)                                        (0x00000100&((data)<<8))
#define SYS_PLL_PSAUDB1_REG_PSAUD1B_DIV_src(data)                                    ((0x00000100&(data))>>8)
#define SYS_PLL_PSAUDB1_get_REG_PSAUD1B_DIV(data)                                    ((0x00000100&(data))>>8)
#define SYS_PLL_PSAUDB1_write_en2_shift                                              (7)
#define SYS_PLL_PSAUDB1_write_en2_mask                                               (0x00000080)
#define SYS_PLL_PSAUDB1_write_en2(data)                                              (0x00000080&((data)<<7))
#define SYS_PLL_PSAUDB1_write_en2_src(data)                                          ((0x00000080&(data))>>7)
#define SYS_PLL_PSAUDB1_get_write_en2(data)                                          ((0x00000080&(data))>>7)
#define SYS_PLL_PSAUDB1_REG_PSAUD1B_TST_shift                                        (6)
#define SYS_PLL_PSAUDB1_REG_PSAUD1B_TST_mask                                         (0x00000040)
#define SYS_PLL_PSAUDB1_REG_PSAUD1B_TST(data)                                        (0x00000040&((data)<<6))
#define SYS_PLL_PSAUDB1_REG_PSAUD1B_TST_src(data)                                    ((0x00000040&(data))>>6)
#define SYS_PLL_PSAUDB1_get_REG_PSAUD1B_TST(data)                                    ((0x00000040&(data))>>6)
#define SYS_PLL_PSAUDB1_REG_PSAUD1B_PSEN_shift                                       (5)
#define SYS_PLL_PSAUDB1_REG_PSAUD1B_PSEN_mask                                        (0x00000020)
#define SYS_PLL_PSAUDB1_REG_PSAUD1B_PSEN(data)                                       (0x00000020&((data)<<5))
#define SYS_PLL_PSAUDB1_REG_PSAUD1B_PSEN_src(data)                                   ((0x00000020&(data))>>5)
#define SYS_PLL_PSAUDB1_get_REG_PSAUD1B_PSEN(data)                                   ((0x00000020&(data))>>5)
#define SYS_PLL_PSAUDB1_write_en1_shift                                              (4)
#define SYS_PLL_PSAUDB1_write_en1_mask                                               (0x00000010)
#define SYS_PLL_PSAUDB1_write_en1(data)                                              (0x00000010&((data)<<4))
#define SYS_PLL_PSAUDB1_write_en1_src(data)                                          ((0x00000010&(data))>>4)
#define SYS_PLL_PSAUDB1_get_write_en1(data)                                          ((0x00000010&(data))>>4)
#define SYS_PLL_PSAUDB1_REG_PSAUD2B_FUPDN_shift                                      (3)
#define SYS_PLL_PSAUDB1_REG_PSAUD2B_FUPDN_mask                                       (0x00000008)
#define SYS_PLL_PSAUDB1_REG_PSAUD2B_FUPDN(data)                                      (0x00000008&((data)<<3))
#define SYS_PLL_PSAUDB1_REG_PSAUD2B_FUPDN_src(data)                                  ((0x00000008&(data))>>3)
#define SYS_PLL_PSAUDB1_get_REG_PSAUD2B_FUPDN(data)                                  ((0x00000008&(data))>>3)
#define SYS_PLL_PSAUDB1_REG_PSAUD2B_DIV_shift                                        (2)
#define SYS_PLL_PSAUDB1_REG_PSAUD2B_DIV_mask                                         (0x00000004)
#define SYS_PLL_PSAUDB1_REG_PSAUD2B_DIV(data)                                        (0x00000004&((data)<<2))
#define SYS_PLL_PSAUDB1_REG_PSAUD2B_DIV_src(data)                                    ((0x00000004&(data))>>2)
#define SYS_PLL_PSAUDB1_get_REG_PSAUD2B_DIV(data)                                    ((0x00000004&(data))>>2)
#define SYS_PLL_PSAUDB1_REG_PSAUD2B_TST_shift                                        (1)
#define SYS_PLL_PSAUDB1_REG_PSAUD2B_TST_mask                                         (0x00000002)
#define SYS_PLL_PSAUDB1_REG_PSAUD2B_TST(data)                                        (0x00000002&((data)<<1))
#define SYS_PLL_PSAUDB1_REG_PSAUD2B_TST_src(data)                                    ((0x00000002&(data))>>1)
#define SYS_PLL_PSAUDB1_get_REG_PSAUD2B_TST(data)                                    ((0x00000002&(data))>>1)
#define SYS_PLL_PSAUDB1_REG_PSAUD2B_PSEN_shift                                       (0)
#define SYS_PLL_PSAUDB1_REG_PSAUD2B_PSEN_mask                                        (0x00000001)
#define SYS_PLL_PSAUDB1_REG_PSAUD2B_PSEN(data)                                       (0x00000001&((data)<<0))
#define SYS_PLL_PSAUDB1_REG_PSAUD2B_PSEN_src(data)                                   ((0x00000001&(data))>>0)
#define SYS_PLL_PSAUDB1_get_REG_PSAUD2B_PSEN(data)                                   ((0x00000001&(data))>>0)


#define SYS_PLL_PSAUDB2                                                              0x9800018C
#define SYS_PLL_PSAUDB2_reg_addr                                                     "0x9800018C"
#define SYS_PLL_PSAUDB2_reg                                                          0x9800018C
#define set_SYS_PLL_PSAUDB2_reg(data)   (*((volatile unsigned int*) SYS_PLL_PSAUDB2_reg)=data)
#define get_SYS_PLL_PSAUDB2_reg   (*((volatile unsigned int*) SYS_PLL_PSAUDB2_reg))
#define SYS_PLL_PSAUDB2_inst_adr                                                     "0x0063"
#define SYS_PLL_PSAUDB2_inst                                                         0x0063
#define SYS_PLL_PSAUDB2_REG_PSAUD1B_OEB_shift                                        (3)
#define SYS_PLL_PSAUDB2_REG_PSAUD1B_OEB_mask                                         (0x00000008)
#define SYS_PLL_PSAUDB2_REG_PSAUD1B_OEB(data)                                        (0x00000008&((data)<<3))
#define SYS_PLL_PSAUDB2_REG_PSAUD1B_OEB_src(data)                                    ((0x00000008&(data))>>3)
#define SYS_PLL_PSAUDB2_get_REG_PSAUD1B_OEB(data)                                    ((0x00000008&(data))>>3)
#define SYS_PLL_PSAUDB2_REG_PSAUD1B_RSTB_shift                                       (2)
#define SYS_PLL_PSAUDB2_REG_PSAUD1B_RSTB_mask                                        (0x00000004)
#define SYS_PLL_PSAUDB2_REG_PSAUD1B_RSTB(data)                                       (0x00000004&((data)<<2))
#define SYS_PLL_PSAUDB2_REG_PSAUD1B_RSTB_src(data)                                   ((0x00000004&(data))>>2)
#define SYS_PLL_PSAUDB2_get_REG_PSAUD1B_RSTB(data)                                   ((0x00000004&(data))>>2)
#define SYS_PLL_PSAUDB2_REG_PSAUD2B_OEB_shift                                        (1)
#define SYS_PLL_PSAUDB2_REG_PSAUD2B_OEB_mask                                         (0x00000002)
#define SYS_PLL_PSAUDB2_REG_PSAUD2B_OEB(data)                                        (0x00000002&((data)<<1))
#define SYS_PLL_PSAUDB2_REG_PSAUD2B_OEB_src(data)                                    ((0x00000002&(data))>>1)
#define SYS_PLL_PSAUDB2_get_REG_PSAUD2B_OEB(data)                                    ((0x00000002&(data))>>1)
#define SYS_PLL_PSAUDB2_REG_PSAUD2B_RSTB_shift                                       (0)
#define SYS_PLL_PSAUDB2_REG_PSAUD2B_RSTB_mask                                        (0x00000001)
#define SYS_PLL_PSAUDB2_REG_PSAUD2B_RSTB(data)                                       (0x00000001&((data)<<0))
#define SYS_PLL_PSAUDB2_REG_PSAUD2B_RSTB_src(data)                                   ((0x00000001&(data))>>0)
#define SYS_PLL_PSAUDB2_get_REG_PSAUD2B_RSTB(data)                                   ((0x00000001&(data))>>0)


#define SYS_PLL_HDMI                                                                 0x98000190
#define SYS_PLL_HDMI_reg_addr                                                        "0x98000190"
#define SYS_PLL_HDMI_reg                                                             0x98000190
#define set_SYS_PLL_HDMI_reg(data)   (*((volatile unsigned int*) SYS_PLL_HDMI_reg)=data)
#define get_SYS_PLL_HDMI_reg   (*((volatile unsigned int*) SYS_PLL_HDMI_reg))
#define SYS_PLL_HDMI_inst_adr                                                        "0x0064"
#define SYS_PLL_HDMI_inst                                                            0x0064
#define SYS_PLL_HDMI_PLLDISP_OEB_shift                                               (8)
#define SYS_PLL_HDMI_PLLDISP_OEB_mask                                                (0x00000100)
#define SYS_PLL_HDMI_PLLDISP_OEB(data)                                               (0x00000100&((data)<<8))
#define SYS_PLL_HDMI_PLLDISP_OEB_src(data)                                           ((0x00000100&(data))>>8)
#define SYS_PLL_HDMI_get_PLLDISP_OEB(data)                                           ((0x00000100&(data))>>8)
#define SYS_PLL_HDMI_PLLDISP_VCORSTB_shift                                           (7)
#define SYS_PLL_HDMI_PLLDISP_VCORSTB_mask                                            (0x00000080)
#define SYS_PLL_HDMI_PLLDISP_VCORSTB(data)                                           (0x00000080&((data)<<7))
#define SYS_PLL_HDMI_PLLDISP_VCORSTB_src(data)                                       ((0x00000080&(data))>>7)
#define SYS_PLL_HDMI_get_PLLDISP_VCORSTB(data)                                       ((0x00000080&(data))>>7)
#define SYS_PLL_HDMI_REG_PLL_MHL3_DIV_EN_shift                                       (6)
#define SYS_PLL_HDMI_REG_PLL_MHL3_DIV_EN_mask                                        (0x00000040)
#define SYS_PLL_HDMI_REG_PLL_MHL3_DIV_EN(data)                                       (0x00000040&((data)<<6))
#define SYS_PLL_HDMI_REG_PLL_MHL3_DIV_EN_src(data)                                   ((0x00000040&(data))>>6)
#define SYS_PLL_HDMI_get_REG_PLL_MHL3_DIV_EN(data)                                   ((0x00000040&(data))>>6)
#define SYS_PLL_HDMI_REG_PLLDISP_RSTB_shift                                          (5)
#define SYS_PLL_HDMI_REG_PLLDISP_RSTB_mask                                           (0x00000020)
#define SYS_PLL_HDMI_REG_PLLDISP_RSTB(data)                                          (0x00000020&((data)<<5))
#define SYS_PLL_HDMI_REG_PLLDISP_RSTB_src(data)                                      ((0x00000020&(data))>>5)
#define SYS_PLL_HDMI_get_REG_PLLDISP_RSTB(data)                                      ((0x00000020&(data))>>5)
#define SYS_PLL_HDMI_REG_PLLDISP_POW_shift                                           (4)
#define SYS_PLL_HDMI_REG_PLLDISP_POW_mask                                            (0x00000010)
#define SYS_PLL_HDMI_REG_PLLDISP_POW(data)                                           (0x00000010&((data)<<4))
#define SYS_PLL_HDMI_REG_PLLDISP_POW_src(data)                                       ((0x00000010&(data))>>4)
#define SYS_PLL_HDMI_get_REG_PLLDISP_POW(data)                                       ((0x00000010&(data))>>4)
#define SYS_PLL_HDMI_REG_TMDS_POW_shift                                              (3)
#define SYS_PLL_HDMI_REG_TMDS_POW_mask                                               (0x00000008)
#define SYS_PLL_HDMI_REG_TMDS_POW(data)                                              (0x00000008&((data)<<3))
#define SYS_PLL_HDMI_REG_TMDS_POW_src(data)                                          ((0x00000008&(data))>>3)
#define SYS_PLL_HDMI_get_REG_TMDS_POW(data)                                          ((0x00000008&(data))>>3)
#define SYS_PLL_HDMI_REG_PLL_RSTB_shift                                              (2)
#define SYS_PLL_HDMI_REG_PLL_RSTB_mask                                               (0x00000004)
#define SYS_PLL_HDMI_REG_PLL_RSTB(data)                                              (0x00000004&((data)<<2))
#define SYS_PLL_HDMI_REG_PLL_RSTB_src(data)                                          ((0x00000004&(data))>>2)
#define SYS_PLL_HDMI_get_REG_PLL_RSTB(data)                                          ((0x00000004&(data))>>2)
#define SYS_PLL_HDMI_REG_PLL_POW_shift                                               (1)
#define SYS_PLL_HDMI_REG_PLL_POW_mask                                                (0x00000002)
#define SYS_PLL_HDMI_REG_PLL_POW(data)                                               (0x00000002&((data)<<1))
#define SYS_PLL_HDMI_REG_PLL_POW_src(data)                                           ((0x00000002&(data))>>1)
#define SYS_PLL_HDMI_get_REG_PLL_POW(data)                                           ((0x00000002&(data))>>1)
#define SYS_PLL_HDMI_REG_HDMI_CK_EN_shift                                            (0)
#define SYS_PLL_HDMI_REG_HDMI_CK_EN_mask                                             (0x00000001)
#define SYS_PLL_HDMI_REG_HDMI_CK_EN(data)                                            (0x00000001&((data)<<0))
#define SYS_PLL_HDMI_REG_HDMI_CK_EN_src(data)                                        ((0x00000001&(data))>>0)
#define SYS_PLL_HDMI_get_REG_HDMI_CK_EN(data)                                        ((0x00000001&(data))>>0)


#define SYS_PLL_HDMI2                                                                0x98000194
#define SYS_PLL_HDMI2_reg_addr                                                       "0x98000194"
#define SYS_PLL_HDMI2_reg                                                            0x98000194
#define set_SYS_PLL_HDMI2_reg(data)   (*((volatile unsigned int*) SYS_PLL_HDMI2_reg)=data)
#define get_SYS_PLL_HDMI2_reg   (*((volatile unsigned int*) SYS_PLL_HDMI2_reg))
#define SYS_PLL_HDMI2_inst_adr                                                       "0x0065"
#define SYS_PLL_HDMI2_inst                                                           0x0065
#define SYS_PLL_HDMI2_REG_ICO_PDIV2_shift                                            (20)
#define SYS_PLL_HDMI2_REG_ICO_PDIV2_mask                                             (0x00700000)
#define SYS_PLL_HDMI2_REG_ICO_PDIV2(data)                                            (0x00700000&((data)<<20))
#define SYS_PLL_HDMI2_REG_ICO_PDIV2_src(data)                                        ((0x00700000&(data))>>20)
#define SYS_PLL_HDMI2_get_REG_ICO_PDIV2(data)                                        ((0x00700000&(data))>>20)
#define SYS_PLL_HDMI2_REG_TMDS_DIV_shift                                             (16)
#define SYS_PLL_HDMI2_REG_TMDS_DIV_mask                                              (0x000F0000)
#define SYS_PLL_HDMI2_REG_TMDS_DIV(data)                                             (0x000F0000&((data)<<16))
#define SYS_PLL_HDMI2_REG_TMDS_DIV_src(data)                                         ((0x000F0000&(data))>>16)
#define SYS_PLL_HDMI2_get_REG_TMDS_DIV(data)                                         ((0x000F0000&(data))>>16)
#define SYS_PLL_HDMI2_REG_PLLDISP_N_shift                                            (14)
#define SYS_PLL_HDMI2_REG_PLLDISP_N_mask                                             (0x0000C000)
#define SYS_PLL_HDMI2_REG_PLLDISP_N(data)                                            (0x0000C000&((data)<<14))
#define SYS_PLL_HDMI2_REG_PLLDISP_N_src(data)                                        ((0x0000C000&(data))>>14)
#define SYS_PLL_HDMI2_get_REG_PLLDISP_N(data)                                        ((0x0000C000&(data))>>14)
#define SYS_PLL_HDMI2_REG_PLLDISP_K_shift                                            (12)
#define SYS_PLL_HDMI2_REG_PLLDISP_K_mask                                             (0x00003000)
#define SYS_PLL_HDMI2_REG_PLLDISP_K(data)                                            (0x00003000&((data)<<12))
#define SYS_PLL_HDMI2_REG_PLLDISP_K_src(data)                                        ((0x00003000&(data))>>12)
#define SYS_PLL_HDMI2_get_REG_PLLDISP_K(data)                                        ((0x00003000&(data))>>12)
#define SYS_PLL_HDMI2_REG_PIXEL_DIV_shift                                            (4)
#define SYS_PLL_HDMI2_REG_PIXEL_DIV_mask                                             (0x00000FF0)
#define SYS_PLL_HDMI2_REG_PIXEL_DIV(data)                                            (0x00000FF0&((data)<<4))
#define SYS_PLL_HDMI2_REG_PIXEL_DIV_src(data)                                        ((0x00000FF0&(data))>>4)
#define SYS_PLL_HDMI2_get_REG_PIXEL_DIV(data)                                        ((0x00000FF0&(data))>>4)
#define SYS_PLL_HDMI2_REG_PLL_M2_shift                                               (2)
#define SYS_PLL_HDMI2_REG_PLL_M2_mask                                                (0x0000000C)
#define SYS_PLL_HDMI2_REG_PLL_M2(data)                                               (0x0000000C&((data)<<2))
#define SYS_PLL_HDMI2_REG_PLL_M2_src(data)                                           ((0x0000000C&(data))>>2)
#define SYS_PLL_HDMI2_get_REG_PLL_M2(data)                                           ((0x0000000C&(data))>>2)
#define SYS_PLL_HDMI2_REG_PLL_M1_shift                                               (0)
#define SYS_PLL_HDMI2_REG_PLL_M1_mask                                                (0x00000003)
#define SYS_PLL_HDMI2_REG_PLL_M1(data)                                               (0x00000003&((data)<<0))
#define SYS_PLL_HDMI2_REG_PLL_M1_src(data)                                           ((0x00000003&(data))>>0)
#define SYS_PLL_HDMI2_get_REG_PLL_M1(data)                                           ((0x00000003&(data))>>0)


#define SYS_PLL_SDIO1                                                                0x980001A0
#define SYS_PLL_SDIO1_reg_addr                                                       "0x980001A0"
#define SYS_PLL_SDIO1_reg                                                            0x980001A0
#define set_SYS_PLL_SDIO1_reg(data)   (*((volatile unsigned int*) SYS_PLL_SDIO1_reg)=data)
#define get_SYS_PLL_SDIO1_reg   (*((volatile unsigned int*) SYS_PLL_SDIO1_reg))
#define SYS_PLL_SDIO1_inst_adr                                                       "0x0068"
#define SYS_PLL_SDIO1_inst                                                           0x0068
#define SYS_PLL_SDIO1_phsel1_shift                                                   (8)
#define SYS_PLL_SDIO1_phsel1_mask                                                    (0x00001F00)
#define SYS_PLL_SDIO1_phsel1(data)                                                   (0x00001F00&((data)<<8))
#define SYS_PLL_SDIO1_phsel1_src(data)                                               ((0x00001F00&(data))>>8)
#define SYS_PLL_SDIO1_get_phsel1(data)                                               ((0x00001F00&(data))>>8)
#define SYS_PLL_SDIO1_phsel0_shift                                                   (3)
#define SYS_PLL_SDIO1_phsel0_mask                                                    (0x000000F8)
#define SYS_PLL_SDIO1_phsel0(data)                                                   (0x000000F8&((data)<<3))
#define SYS_PLL_SDIO1_phsel0_src(data)                                               ((0x000000F8&(data))>>3)
#define SYS_PLL_SDIO1_get_phsel0(data)                                               ((0x000000F8&(data))>>3)
#define SYS_PLL_SDIO1_phrstb_dly_sel_shift                                           (2)
#define SYS_PLL_SDIO1_phrstb_dly_sel_mask                                            (0x00000004)
#define SYS_PLL_SDIO1_phrstb_dly_sel(data)                                           (0x00000004&((data)<<2))
#define SYS_PLL_SDIO1_phrstb_dly_sel_src(data)                                       ((0x00000004&(data))>>2)
#define SYS_PLL_SDIO1_get_phrstb_dly_sel(data)                                       ((0x00000004&(data))>>2)
#define SYS_PLL_SDIO1_phrt0_shift                                                    (1)
#define SYS_PLL_SDIO1_phrt0_mask                                                     (0x00000002)
#define SYS_PLL_SDIO1_phrt0(data)                                                    (0x00000002&((data)<<1))
#define SYS_PLL_SDIO1_phrt0_src(data)                                                ((0x00000002&(data))>>1)
#define SYS_PLL_SDIO1_get_phrt0(data)                                                ((0x00000002&(data))>>1)
#define SYS_PLL_SDIO1_bias_en_shift                                                  (0)
#define SYS_PLL_SDIO1_bias_en_mask                                                   (0x00000001)
#define SYS_PLL_SDIO1_bias_en(data)                                                  (0x00000001&((data)<<0))
#define SYS_PLL_SDIO1_bias_en_src(data)                                              ((0x00000001&(data))>>0)
#define SYS_PLL_SDIO1_get_bias_en(data)                                              ((0x00000001&(data))>>0)


#define SYS_PLL_SDIO2                                                                0x980001A4
#define SYS_PLL_SDIO2_reg_addr                                                       "0x980001A4"
#define SYS_PLL_SDIO2_reg                                                            0x980001A4
#define set_SYS_PLL_SDIO2_reg(data)   (*((volatile unsigned int*) SYS_PLL_SDIO2_reg)=data)
#define get_SYS_PLL_SDIO2_reg   (*((volatile unsigned int*) SYS_PLL_SDIO2_reg))
#define SYS_PLL_SDIO2_inst_adr                                                       "0x0069"
#define SYS_PLL_SDIO2_inst                                                           0x0069
#define SYS_PLL_SDIO2_en_cpnew_shift                                                 (26)
#define SYS_PLL_SDIO2_en_cpnew_mask                                                  (0x04000000)
#define SYS_PLL_SDIO2_en_cpnew(data)                                                 (0x04000000&((data)<<26))
#define SYS_PLL_SDIO2_en_cpnew_src(data)                                             ((0x04000000&(data))>>26)
#define SYS_PLL_SDIO2_get_en_cpnew(data)                                             ((0x04000000&(data))>>26)
#define SYS_PLL_SDIO2_ssc_div_ext_f_shift                                            (18)
#define SYS_PLL_SDIO2_ssc_div_ext_f_mask                                             (0x03FC0000)
#define SYS_PLL_SDIO2_ssc_div_ext_f(data)                                            (0x03FC0000&((data)<<18))
#define SYS_PLL_SDIO2_ssc_div_ext_f_src(data)                                        ((0x03FC0000&(data))>>18)
#define SYS_PLL_SDIO2_get_ssc_div_ext_f(data)                                        ((0x03FC0000&(data))>>18)
#define SYS_PLL_SDIO2_ssc_div_f_sel_shift                                            (17)
#define SYS_PLL_SDIO2_ssc_div_f_sel_mask                                             (0x00020000)
#define SYS_PLL_SDIO2_ssc_div_f_sel(data)                                            (0x00020000&((data)<<17))
#define SYS_PLL_SDIO2_ssc_div_f_sel_src(data)                                        ((0x00020000&(data))>>17)
#define SYS_PLL_SDIO2_get_ssc_div_f_sel(data)                                        ((0x00020000&(data))>>17)
#define SYS_PLL_SDIO2_ssc_8x_en_shift                                                (16)
#define SYS_PLL_SDIO2_ssc_8x_en_mask                                                 (0x00010000)
#define SYS_PLL_SDIO2_ssc_8x_en(data)                                                (0x00010000&((data)<<16))
#define SYS_PLL_SDIO2_ssc_8x_en_src(data)                                            ((0x00010000&(data))>>16)
#define SYS_PLL_SDIO2_get_ssc_8x_en(data)                                            ((0x00010000&(data))>>16)
#define SYS_PLL_SDIO2_ssc_depth_shift                                                (13)
#define SYS_PLL_SDIO2_ssc_depth_mask                                                 (0x0000E000)
#define SYS_PLL_SDIO2_ssc_depth(data)                                                (0x0000E000&((data)<<13))
#define SYS_PLL_SDIO2_ssc_depth_src(data)                                            ((0x0000E000&(data))>>13)
#define SYS_PLL_SDIO2_get_ssc_depth(data)                                            ((0x0000E000&(data))>>13)
#define SYS_PLL_SDIO2_sscpll_rs_shift                                                (10)
#define SYS_PLL_SDIO2_sscpll_rs_mask                                                 (0x00001C00)
#define SYS_PLL_SDIO2_sscpll_rs(data)                                                (0x00001C00&((data)<<10))
#define SYS_PLL_SDIO2_sscpll_rs_src(data)                                            ((0x00001C00&(data))>>10)
#define SYS_PLL_SDIO2_get_sscpll_rs(data)                                            ((0x00001C00&(data))>>10)
#define SYS_PLL_SDIO2_sscpll_icp_shift                                               (5)
#define SYS_PLL_SDIO2_sscpll_icp_mask                                                (0x000003E0)
#define SYS_PLL_SDIO2_sscpll_icp(data)                                               (0x000003E0&((data)<<5))
#define SYS_PLL_SDIO2_sscpll_icp_src(data)                                           ((0x000003E0&(data))>>5)
#define SYS_PLL_SDIO2_get_sscpll_icp(data)                                           ((0x000003E0&(data))>>5)
#define SYS_PLL_SDIO2_sscpll_cs1_shift                                               (3)
#define SYS_PLL_SDIO2_sscpll_cs1_mask                                                (0x00000018)
#define SYS_PLL_SDIO2_sscpll_cs1(data)                                               (0x00000018&((data)<<3))
#define SYS_PLL_SDIO2_sscpll_cs1_src(data)                                           ((0x00000018&(data))>>3)
#define SYS_PLL_SDIO2_get_sscpll_cs1(data)                                           ((0x00000018&(data))>>3)
#define SYS_PLL_SDIO2_reg_tune11_shift                                               (1)
#define SYS_PLL_SDIO2_reg_tune11_mask                                                (0x00000006)
#define SYS_PLL_SDIO2_reg_tune11(data)                                               (0x00000006&((data)<<1))
#define SYS_PLL_SDIO2_reg_tune11_src(data)                                           ((0x00000006&(data))>>1)
#define SYS_PLL_SDIO2_get_reg_tune11(data)                                           ((0x00000006&(data))>>1)
#define SYS_PLL_SDIO2_sscldo_en_shift                                                (0)
#define SYS_PLL_SDIO2_sscldo_en_mask                                                 (0x00000001)
#define SYS_PLL_SDIO2_sscldo_en(data)                                                (0x00000001&((data)<<0))
#define SYS_PLL_SDIO2_sscldo_en_src(data)                                            ((0x00000001&(data))>>0)
#define SYS_PLL_SDIO2_get_sscldo_en(data)                                            ((0x00000001&(data))>>0)


#define SYS_PLL_SDIO3                                                                0x980001A8
#define SYS_PLL_SDIO3_reg_addr                                                       "0x980001A8"
#define SYS_PLL_SDIO3_reg                                                            0x980001A8
#define set_SYS_PLL_SDIO3_reg(data)   (*((volatile unsigned int*) SYS_PLL_SDIO3_reg)=data)
#define get_SYS_PLL_SDIO3_reg   (*((volatile unsigned int*) SYS_PLL_SDIO3_reg))
#define SYS_PLL_SDIO3_inst_adr                                                       "0x006A"
#define SYS_PLL_SDIO3_inst                                                           0x006A
#define SYS_PLL_SDIO3_ssc_div_n_shift                                                (16)
#define SYS_PLL_SDIO3_ssc_div_n_mask                                                 (0x03FF0000)
#define SYS_PLL_SDIO3_ssc_div_n(data)                                                (0x03FF0000&((data)<<16))
#define SYS_PLL_SDIO3_ssc_div_n_src(data)                                            ((0x03FF0000&(data))>>16)
#define SYS_PLL_SDIO3_get_ssc_div_n(data)                                            ((0x03FF0000&(data))>>16)
#define SYS_PLL_SDIO3_ssc_step_in_shift                                              (8)
#define SYS_PLL_SDIO3_ssc_step_in_mask                                               (0x00007F00)
#define SYS_PLL_SDIO3_ssc_step_in(data)                                              (0x00007F00&((data)<<8))
#define SYS_PLL_SDIO3_ssc_step_in_src(data)                                          ((0x00007F00&(data))>>8)
#define SYS_PLL_SDIO3_get_ssc_step_in(data)                                          ((0x00007F00&(data))>>8)
#define SYS_PLL_SDIO3_ssc_tbase_shift                                                (0)
#define SYS_PLL_SDIO3_ssc_tbase_mask                                                 (0x000000FF)
#define SYS_PLL_SDIO3_ssc_tbase(data)                                                (0x000000FF&((data)<<0))
#define SYS_PLL_SDIO3_ssc_tbase_src(data)                                            ((0x000000FF&(data))>>0)
#define SYS_PLL_SDIO3_get_ssc_tbase(data)                                            ((0x000000FF&(data))>>0)


#define SYS_PLL_SDIO4                                                                0x980001AC
#define SYS_PLL_SDIO4_reg_addr                                                       "0x980001AC"
#define SYS_PLL_SDIO4_reg                                                            0x980001AC
#define set_SYS_PLL_SDIO4_reg(data)   (*((volatile unsigned int*) SYS_PLL_SDIO4_reg)=data)
#define get_SYS_PLL_SDIO4_reg   (*((volatile unsigned int*) SYS_PLL_SDIO4_reg))
#define SYS_PLL_SDIO4_inst_adr                                                       "0x006B"
#define SYS_PLL_SDIO4_inst                                                           0x006B
#define SYS_PLL_SDIO4_ssc_pll_pow_shift                                              (2)
#define SYS_PLL_SDIO4_ssc_pll_pow_mask                                               (0x00000004)
#define SYS_PLL_SDIO4_ssc_pll_pow(data)                                              (0x00000004&((data)<<2))
#define SYS_PLL_SDIO4_ssc_pll_pow_src(data)                                          ((0x00000004&(data))>>2)
#define SYS_PLL_SDIO4_get_ssc_pll_pow(data)                                          ((0x00000004&(data))>>2)
#define SYS_PLL_SDIO4_ssc_pll_rstb_shift                                             (1)
#define SYS_PLL_SDIO4_ssc_pll_rstb_mask                                              (0x00000002)
#define SYS_PLL_SDIO4_ssc_pll_rstb(data)                                             (0x00000002&((data)<<1))
#define SYS_PLL_SDIO4_ssc_pll_rstb_src(data)                                         ((0x00000002&(data))>>1)
#define SYS_PLL_SDIO4_get_ssc_pll_rstb(data)                                         ((0x00000002&(data))>>1)
#define SYS_PLL_SDIO4_ssc_rstb_shift                                                 (0)
#define SYS_PLL_SDIO4_ssc_rstb_mask                                                  (0x00000001)
#define SYS_PLL_SDIO4_ssc_rstb(data)                                                 (0x00000001&((data)<<0))
#define SYS_PLL_SDIO4_ssc_rstb_src(data)                                             ((0x00000001&(data))>>0)
#define SYS_PLL_SDIO4_get_ssc_rstb(data)                                             ((0x00000001&(data))>>0)


#define SYS_PLL_BUSH1                                                                0x980001B0
#define SYS_PLL_BUSH1_reg_addr                                                       "0x980001B0"
#define SYS_PLL_BUSH1_reg                                                            0x980001B0
#define set_SYS_PLL_BUSH1_reg(data)   (*((volatile unsigned int*) SYS_PLL_BUSH1_reg)=data)
#define get_SYS_PLL_BUSH1_reg   (*((volatile unsigned int*) SYS_PLL_BUSH1_reg))
#define SYS_PLL_BUSH1_inst_adr                                                       "0x006C"
#define SYS_PLL_BUSH1_inst                                                           0x006C
#define SYS_PLL_BUSH1_REG_PLLBUS_PDIV_H_shift                                        (17)
#define SYS_PLL_BUSH1_REG_PLLBUS_PDIV_H_mask                                         (0x00060000)
#define SYS_PLL_BUSH1_REG_PLLBUS_PDIV_H(data)                                        (0x00060000&((data)<<17))
#define SYS_PLL_BUSH1_REG_PLLBUS_PDIV_H_src(data)                                    ((0x00060000&(data))>>17)
#define SYS_PLL_BUSH1_get_REG_PLLBUS_PDIV_H(data)                                    ((0x00060000&(data))>>17)
#define SYS_PLL_BUSH1_REG_PLLBUS_LPF_RS_H_shift                                      (14)
#define SYS_PLL_BUSH1_REG_PLLBUS_LPF_RS_H_mask                                       (0x0001C000)
#define SYS_PLL_BUSH1_REG_PLLBUS_LPF_RS_H(data)                                      (0x0001C000&((data)<<14))
#define SYS_PLL_BUSH1_REG_PLLBUS_LPF_RS_H_src(data)                                  ((0x0001C000&(data))>>14)
#define SYS_PLL_BUSH1_get_REG_PLLBUS_LPF_RS_H(data)                                  ((0x0001C000&(data))>>14)
#define SYS_PLL_BUSH1_REG_PLLBUS_LPF_CS_H_shift                                      (12)
#define SYS_PLL_BUSH1_REG_PLLBUS_LPF_CS_H_mask                                       (0x00003000)
#define SYS_PLL_BUSH1_REG_PLLBUS_LPF_CS_H(data)                                      (0x00003000&((data)<<12))
#define SYS_PLL_BUSH1_REG_PLLBUS_LPF_CS_H_src(data)                                  ((0x00003000&(data))>>12)
#define SYS_PLL_BUSH1_get_REG_PLLBUS_LPF_CS_H(data)                                  ((0x00003000&(data))>>12)
#define SYS_PLL_BUSH1_REG_PLLBUS_ICP_H_shift                                         (9)
#define SYS_PLL_BUSH1_REG_PLLBUS_ICP_H_mask                                          (0x00000E00)
#define SYS_PLL_BUSH1_REG_PLLBUS_ICP_H(data)                                         (0x00000E00&((data)<<9))
#define SYS_PLL_BUSH1_REG_PLLBUS_ICP_H_src(data)                                     ((0x00000E00&(data))>>9)
#define SYS_PLL_BUSH1_get_REG_PLLBUS_ICP_H(data)                                     ((0x00000E00&(data))>>9)
#define SYS_PLL_BUSH1_REG_PLLBUS_WDSET_H_shift                                       (8)
#define SYS_PLL_BUSH1_REG_PLLBUS_WDSET_H_mask                                        (0x00000100)
#define SYS_PLL_BUSH1_REG_PLLBUS_WDSET_H(data)                                       (0x00000100&((data)<<8))
#define SYS_PLL_BUSH1_REG_PLLBUS_WDSET_H_src(data)                                   ((0x00000100&(data))>>8)
#define SYS_PLL_BUSH1_get_REG_PLLBUS_WDSET_H(data)                                   ((0x00000100&(data))>>8)
#define SYS_PLL_BUSH1_REG_PLLBUS_WDRST_H_shift                                       (7)
#define SYS_PLL_BUSH1_REG_PLLBUS_WDRST_H_mask                                        (0x00000080)
#define SYS_PLL_BUSH1_REG_PLLBUS_WDRST_H(data)                                       (0x00000080&((data)<<7))
#define SYS_PLL_BUSH1_REG_PLLBUS_WDRST_H_src(data)                                   ((0x00000080&(data))>>7)
#define SYS_PLL_BUSH1_get_REG_PLLBUS_WDRST_H(data)                                   ((0x00000080&(data))>>7)
#define SYS_PLL_BUSH1_REG_PLLBUS_TESTSEL_H_shift                                     (6)
#define SYS_PLL_BUSH1_REG_PLLBUS_TESTSEL_H_mask                                      (0x00000040)
#define SYS_PLL_BUSH1_REG_PLLBUS_TESTSEL_H(data)                                     (0x00000040&((data)<<6))
#define SYS_PLL_BUSH1_REG_PLLBUS_TESTSEL_H_src(data)                                 ((0x00000040&(data))>>6)
#define SYS_PLL_BUSH1_get_REG_PLLBUS_TESTSEL_H(data)                                 ((0x00000040&(data))>>6)
#define SYS_PLL_BUSH1_REG_PLLBUS_SEL_CCO_H_shift                                     (5)
#define SYS_PLL_BUSH1_REG_PLLBUS_SEL_CCO_H_mask                                      (0x00000020)
#define SYS_PLL_BUSH1_REG_PLLBUS_SEL_CCO_H(data)                                     (0x00000020&((data)<<5))
#define SYS_PLL_BUSH1_REG_PLLBUS_SEL_CCO_H_src(data)                                 ((0x00000020&(data))>>5)
#define SYS_PLL_BUSH1_get_REG_PLLBUS_SEL_CCO_H(data)                                 ((0x00000020&(data))>>5)
#define SYS_PLL_BUSH1_REG_PLLBUS_PDIV_BPS_H_shift                                    (4)
#define SYS_PLL_BUSH1_REG_PLLBUS_PDIV_BPS_H_mask                                     (0x00000010)
#define SYS_PLL_BUSH1_REG_PLLBUS_PDIV_BPS_H(data)                                    (0x00000010&((data)<<4))
#define SYS_PLL_BUSH1_REG_PLLBUS_PDIV_BPS_H_src(data)                                ((0x00000010&(data))>>4)
#define SYS_PLL_BUSH1_get_REG_PLLBUS_PDIV_BPS_H(data)                                ((0x00000010&(data))>>4)
#define SYS_PLL_BUSH1_REG_PLLBUS_DBUG_EN_H_shift                                     (3)
#define SYS_PLL_BUSH1_REG_PLLBUS_DBUG_EN_H_mask                                      (0x00000008)
#define SYS_PLL_BUSH1_REG_PLLBUS_DBUG_EN_H(data)                                     (0x00000008&((data)<<3))
#define SYS_PLL_BUSH1_REG_PLLBUS_DBUG_EN_H_src(data)                                 ((0x00000008&(data))>>3)
#define SYS_PLL_BUSH1_get_REG_PLLBUS_DBUG_EN_H(data)                                 ((0x00000008&(data))>>3)


#define SYS_PLL_BUSH2                                                                0x980001B8
#define SYS_PLL_BUSH2_reg_addr                                                       "0x980001B8"
#define SYS_PLL_BUSH2_reg                                                            0x980001B8
#define set_SYS_PLL_BUSH2_reg(data)   (*((volatile unsigned int*) SYS_PLL_BUSH2_reg)=data)
#define get_SYS_PLL_BUSH2_reg   (*((volatile unsigned int*) SYS_PLL_BUSH2_reg))
#define SYS_PLL_BUSH2_inst_adr                                                       "0x006E"
#define SYS_PLL_BUSH2_inst                                                           0x006E
#define SYS_PLL_BUSH2_REG_PLLBUS_OEB_H_shift                                         (2)
#define SYS_PLL_BUSH2_REG_PLLBUS_OEB_H_mask                                          (0x00000004)
#define SYS_PLL_BUSH2_REG_PLLBUS_OEB_H(data)                                         (0x00000004&((data)<<2))
#define SYS_PLL_BUSH2_REG_PLLBUS_OEB_H_src(data)                                     ((0x00000004&(data))>>2)
#define SYS_PLL_BUSH2_get_REG_PLLBUS_OEB_H(data)                                     ((0x00000004&(data))>>2)
#define SYS_PLL_BUSH2_REG_PLLBUS_RSTB_H_shift                                        (1)
#define SYS_PLL_BUSH2_REG_PLLBUS_RSTB_H_mask                                         (0x00000002)
#define SYS_PLL_BUSH2_REG_PLLBUS_RSTB_H(data)                                        (0x00000002&((data)<<1))
#define SYS_PLL_BUSH2_REG_PLLBUS_RSTB_H_src(data)                                    ((0x00000002&(data))>>1)
#define SYS_PLL_BUSH2_get_REG_PLLBUS_RSTB_H(data)                                    ((0x00000002&(data))>>1)
#define SYS_PLL_BUSH2_REG_PLLBUS_POW_H_shift                                         (0)
#define SYS_PLL_BUSH2_REG_PLLBUS_POW_H_mask                                          (0x00000001)
#define SYS_PLL_BUSH2_REG_PLLBUS_POW_H(data)                                         (0x00000001&((data)<<0))
#define SYS_PLL_BUSH2_REG_PLLBUS_POW_H_src(data)                                     ((0x00000001&(data))>>0)
#define SYS_PLL_BUSH2_get_REG_PLLBUS_POW_H(data)                                     ((0x00000001&(data))>>0)


#define SYS_PLL_GPU1                                                                 0x980001C0
#define SYS_PLL_GPU1_reg_addr                                                        "0x980001C0"
#define SYS_PLL_GPU1_reg                                                             0x980001C0
#define set_SYS_PLL_GPU1_reg(data)   (*((volatile unsigned int*) SYS_PLL_GPU1_reg)=data)
#define get_SYS_PLL_GPU1_reg   (*((volatile unsigned int*) SYS_PLL_GPU1_reg))
#define SYS_PLL_GPU1_inst_adr                                                        "0x0070"
#define SYS_PLL_GPU1_inst                                                            0x0070
#define SYS_PLL_GPU1_REG_PLLGPU_PDIV_shift                                           (17)
#define SYS_PLL_GPU1_REG_PLLGPU_PDIV_mask                                            (0x00060000)
#define SYS_PLL_GPU1_REG_PLLGPU_PDIV(data)                                           (0x00060000&((data)<<17))
#define SYS_PLL_GPU1_REG_PLLGPU_PDIV_src(data)                                       ((0x00060000&(data))>>17)
#define SYS_PLL_GPU1_get_REG_PLLGPU_PDIV(data)                                       ((0x00060000&(data))>>17)
#define SYS_PLL_GPU1_REG_PLLGPU_LPF_RS_shift                                         (14)
#define SYS_PLL_GPU1_REG_PLLGPU_LPF_RS_mask                                          (0x0001C000)
#define SYS_PLL_GPU1_REG_PLLGPU_LPF_RS(data)                                         (0x0001C000&((data)<<14))
#define SYS_PLL_GPU1_REG_PLLGPU_LPF_RS_src(data)                                     ((0x0001C000&(data))>>14)
#define SYS_PLL_GPU1_get_REG_PLLGPU_LPF_RS(data)                                     ((0x0001C000&(data))>>14)
#define SYS_PLL_GPU1_REG_PLLGPU_LPF_CS_shift                                         (12)
#define SYS_PLL_GPU1_REG_PLLGPU_LPF_CS_mask                                          (0x00003000)
#define SYS_PLL_GPU1_REG_PLLGPU_LPF_CS(data)                                         (0x00003000&((data)<<12))
#define SYS_PLL_GPU1_REG_PLLGPU_LPF_CS_src(data)                                     ((0x00003000&(data))>>12)
#define SYS_PLL_GPU1_get_REG_PLLGPU_LPF_CS(data)                                     ((0x00003000&(data))>>12)
#define SYS_PLL_GPU1_REG_PLLGPU_ICP_shift                                            (9)
#define SYS_PLL_GPU1_REG_PLLGPU_ICP_mask                                             (0x00000E00)
#define SYS_PLL_GPU1_REG_PLLGPU_ICP(data)                                            (0x00000E00&((data)<<9))
#define SYS_PLL_GPU1_REG_PLLGPU_ICP_src(data)                                        ((0x00000E00&(data))>>9)
#define SYS_PLL_GPU1_get_REG_PLLGPU_ICP(data)                                        ((0x00000E00&(data))>>9)
#define SYS_PLL_GPU1_REG_PLLGPU_WDRST_shift                                          (8)
#define SYS_PLL_GPU1_REG_PLLGPU_WDRST_mask                                           (0x00000100)
#define SYS_PLL_GPU1_REG_PLLGPU_WDRST(data)                                          (0x00000100&((data)<<8))
#define SYS_PLL_GPU1_REG_PLLGPU_WDRST_src(data)                                      ((0x00000100&(data))>>8)
#define SYS_PLL_GPU1_get_REG_PLLGPU_WDRST(data)                                      ((0x00000100&(data))>>8)
#define SYS_PLL_GPU1_REG_PLLGPU_WDSET_shift                                          (7)
#define SYS_PLL_GPU1_REG_PLLGPU_WDSET_mask                                           (0x00000080)
#define SYS_PLL_GPU1_REG_PLLGPU_WDSET(data)                                          (0x00000080&((data)<<7))
#define SYS_PLL_GPU1_REG_PLLGPU_WDSET_src(data)                                      ((0x00000080&(data))>>7)
#define SYS_PLL_GPU1_get_REG_PLLGPU_WDSET(data)                                      ((0x00000080&(data))>>7)
#define SYS_PLL_GPU1_REG_PLLGPU_TESTSEL_shift                                        (6)
#define SYS_PLL_GPU1_REG_PLLGPU_TESTSEL_mask                                         (0x00000040)
#define SYS_PLL_GPU1_REG_PLLGPU_TESTSEL(data)                                        (0x00000040&((data)<<6))
#define SYS_PLL_GPU1_REG_PLLGPU_TESTSEL_src(data)                                    ((0x00000040&(data))>>6)
#define SYS_PLL_GPU1_get_REG_PLLGPU_TESTSEL(data)                                    ((0x00000040&(data))>>6)
#define SYS_PLL_GPU1_REG_PLLGPU_SEL_CCO_shift                                        (5)
#define SYS_PLL_GPU1_REG_PLLGPU_SEL_CCO_mask                                         (0x00000020)
#define SYS_PLL_GPU1_REG_PLLGPU_SEL_CCO(data)                                        (0x00000020&((data)<<5))
#define SYS_PLL_GPU1_REG_PLLGPU_SEL_CCO_src(data)                                    ((0x00000020&(data))>>5)
#define SYS_PLL_GPU1_get_REG_PLLGPU_SEL_CCO(data)                                    ((0x00000020&(data))>>5)
#define SYS_PLL_GPU1_REG_PLLGPU_PDIV_BPS_shift                                       (4)
#define SYS_PLL_GPU1_REG_PLLGPU_PDIV_BPS_mask                                        (0x00000010)
#define SYS_PLL_GPU1_REG_PLLGPU_PDIV_BPS(data)                                       (0x00000010&((data)<<4))
#define SYS_PLL_GPU1_REG_PLLGPU_PDIV_BPS_src(data)                                   ((0x00000010&(data))>>4)
#define SYS_PLL_GPU1_get_REG_PLLGPU_PDIV_BPS(data)                                   ((0x00000010&(data))>>4)
#define SYS_PLL_GPU1_REG_PLLGPU_DBUG_EN_shift                                        (3)
#define SYS_PLL_GPU1_REG_PLLGPU_DBUG_EN_mask                                         (0x00000008)
#define SYS_PLL_GPU1_REG_PLLGPU_DBUG_EN(data)                                        (0x00000008&((data)<<3))
#define SYS_PLL_GPU1_REG_PLLGPU_DBUG_EN_src(data)                                    ((0x00000008&(data))>>3)
#define SYS_PLL_GPU1_get_REG_PLLGPU_DBUG_EN(data)                                    ((0x00000008&(data))>>3)


#define SYS_PLL_GPU2                                                                 0x980001C4
#define SYS_PLL_GPU2_reg_addr                                                        "0x980001C4"
#define SYS_PLL_GPU2_reg                                                             0x980001C4
#define set_SYS_PLL_GPU2_reg(data)   (*((volatile unsigned int*) SYS_PLL_GPU2_reg)=data)
#define get_SYS_PLL_GPU2_reg   (*((volatile unsigned int*) SYS_PLL_GPU2_reg))
#define SYS_PLL_GPU2_inst_adr                                                        "0x0071"
#define SYS_PLL_GPU2_inst                                                            0x0071
#define SYS_PLL_GPU2_REG_PLLGPU_OEB_shift                                            (2)
#define SYS_PLL_GPU2_REG_PLLGPU_OEB_mask                                             (0x00000004)
#define SYS_PLL_GPU2_REG_PLLGPU_OEB(data)                                            (0x00000004&((data)<<2))
#define SYS_PLL_GPU2_REG_PLLGPU_OEB_src(data)                                        ((0x00000004&(data))>>2)
#define SYS_PLL_GPU2_get_REG_PLLGPU_OEB(data)                                        ((0x00000004&(data))>>2)
#define SYS_PLL_GPU2_REG_PLLGPU_RSTB_shift                                           (1)
#define SYS_PLL_GPU2_REG_PLLGPU_RSTB_mask                                            (0x00000002)
#define SYS_PLL_GPU2_REG_PLLGPU_RSTB(data)                                           (0x00000002&((data)<<1))
#define SYS_PLL_GPU2_REG_PLLGPU_RSTB_src(data)                                       ((0x00000002&(data))>>1)
#define SYS_PLL_GPU2_get_REG_PLLGPU_RSTB(data)                                       ((0x00000002&(data))>>1)
#define SYS_PLL_GPU2_REG_PLLGPU_POW_shift                                            (0)
#define SYS_PLL_GPU2_REG_PLLGPU_POW_mask                                             (0x00000001)
#define SYS_PLL_GPU2_REG_PLLGPU_POW(data)                                            (0x00000001&((data)<<0))
#define SYS_PLL_GPU2_REG_PLLGPU_POW_src(data)                                        ((0x00000001&(data))>>0)
#define SYS_PLL_GPU2_get_REG_PLLGPU_POW(data)                                        ((0x00000001&(data))>>0)


#define SYS_PLL_VE2_1                                                                0x980001D0
#define SYS_PLL_VE2_1_reg_addr                                                       "0x980001D0"
#define SYS_PLL_VE2_1_reg                                                            0x980001D0
#define set_SYS_PLL_VE2_1_reg(data)   (*((volatile unsigned int*) SYS_PLL_VE2_1_reg)=data)
#define get_SYS_PLL_VE2_1_reg   (*((volatile unsigned int*) SYS_PLL_VE2_1_reg))
#define SYS_PLL_VE2_1_inst_adr                                                       "0x0074"
#define SYS_PLL_VE2_1_inst                                                           0x0074
#define SYS_PLL_VE2_1_REG_PLLVCPU_WDRST_2_shift                                      (22)
#define SYS_PLL_VE2_1_REG_PLLVCPU_WDRST_2_mask                                       (0x00400000)
#define SYS_PLL_VE2_1_REG_PLLVCPU_WDRST_2(data)                                      (0x00400000&((data)<<22))
#define SYS_PLL_VE2_1_REG_PLLVCPU_WDRST_2_src(data)                                  ((0x00400000&(data))>>22)
#define SYS_PLL_VE2_1_get_REG_PLLVCPU_WDRST_2(data)                                  ((0x00400000&(data))>>22)
#define SYS_PLL_VE2_1_REG_PLLVCPU_WDSET_2_shift                                      (21)
#define SYS_PLL_VE2_1_REG_PLLVCPU_WDSET_2_mask                                       (0x00200000)
#define SYS_PLL_VE2_1_REG_PLLVCPU_WDSET_2(data)                                      (0x00200000&((data)<<21))
#define SYS_PLL_VE2_1_REG_PLLVCPU_WDSET_2_src(data)                                  ((0x00200000&(data))>>21)
#define SYS_PLL_VE2_1_get_REG_PLLVCPU_WDSET_2(data)                                  ((0x00200000&(data))>>21)
#define SYS_PLL_VE2_1_REG_PLLVCPU_CS_2_shift                                         (19)
#define SYS_PLL_VE2_1_REG_PLLVCPU_CS_2_mask                                          (0x00180000)
#define SYS_PLL_VE2_1_REG_PLLVCPU_CS_2(data)                                         (0x00180000&((data)<<19))
#define SYS_PLL_VE2_1_REG_PLLVCPU_CS_2_src(data)                                     ((0x00180000&(data))>>19)
#define SYS_PLL_VE2_1_get_REG_PLLVCPU_CS_2(data)                                     ((0x00180000&(data))>>19)
#define SYS_PLL_VE2_1_REG_PLLVCPU_O_2_shift                                          (17)
#define SYS_PLL_VE2_1_REG_PLLVCPU_O_2_mask                                           (0x00060000)
#define SYS_PLL_VE2_1_REG_PLLVCPU_O_2(data)                                          (0x00060000&((data)<<17))
#define SYS_PLL_VE2_1_REG_PLLVCPU_O_2_src(data)                                      ((0x00060000&(data))>>17)
#define SYS_PLL_VE2_1_get_REG_PLLVCPU_O_2(data)                                      ((0x00060000&(data))>>17)
#define SYS_PLL_VE2_1_REG_PLLVCPU_RS_2_shift                                         (14)
#define SYS_PLL_VE2_1_REG_PLLVCPU_RS_2_mask                                          (0x0001C000)
#define SYS_PLL_VE2_1_REG_PLLVCPU_RS_2(data)                                         (0x0001C000&((data)<<14))
#define SYS_PLL_VE2_1_REG_PLLVCPU_RS_2_src(data)                                     ((0x0001C000&(data))>>14)
#define SYS_PLL_VE2_1_get_REG_PLLVCPU_RS_2(data)                                     ((0x0001C000&(data))>>14)
#define SYS_PLL_VE2_1_REG_PLLVCPU_N_2_shift                                          (12)
#define SYS_PLL_VE2_1_REG_PLLVCPU_N_2_mask                                           (0x00003000)
#define SYS_PLL_VE2_1_REG_PLLVCPU_N_2(data)                                          (0x00003000&((data)<<12))
#define SYS_PLL_VE2_1_REG_PLLVCPU_N_2_src(data)                                      ((0x00003000&(data))>>12)
#define SYS_PLL_VE2_1_get_REG_PLLVCPU_N_2(data)                                      ((0x00003000&(data))>>12)
#define SYS_PLL_VE2_1_REG_PLLVCPU_M_2_shift                                          (4)
#define SYS_PLL_VE2_1_REG_PLLVCPU_M_2_mask                                           (0x00000FF0)
#define SYS_PLL_VE2_1_REG_PLLVCPU_M_2(data)                                          (0x00000FF0&((data)<<4))
#define SYS_PLL_VE2_1_REG_PLLVCPU_M_2_src(data)                                      ((0x00000FF0&(data))>>4)
#define SYS_PLL_VE2_1_get_REG_PLLVCPU_M_2(data)                                      ((0x00000FF0&(data))>>4)
#define SYS_PLL_VE2_1_REG_PLLVCPU_IP_2_shift                                         (1)
#define SYS_PLL_VE2_1_REG_PLLVCPU_IP_2_mask                                          (0x0000000E)
#define SYS_PLL_VE2_1_REG_PLLVCPU_IP_2(data)                                         (0x0000000E&((data)<<1))
#define SYS_PLL_VE2_1_REG_PLLVCPU_IP_2_src(data)                                     ((0x0000000E&(data))>>1)
#define SYS_PLL_VE2_1_get_REG_PLLVCPU_IP_2(data)                                     ((0x0000000E&(data))>>1)
#define SYS_PLL_VE2_1_REG_PLLVCPU_TST_2_shift                                        (0)
#define SYS_PLL_VE2_1_REG_PLLVCPU_TST_2_mask                                         (0x00000001)
#define SYS_PLL_VE2_1_REG_PLLVCPU_TST_2(data)                                        (0x00000001&((data)<<0))
#define SYS_PLL_VE2_1_REG_PLLVCPU_TST_2_src(data)                                    ((0x00000001&(data))>>0)
#define SYS_PLL_VE2_1_get_REG_PLLVCPU_TST_2(data)                                    ((0x00000001&(data))>>0)


#define SYS_PLL_VE2_2                                                                0x980001D4
#define SYS_PLL_VE2_2_reg_addr                                                       "0x980001D4"
#define SYS_PLL_VE2_2_reg                                                            0x980001D4
#define set_SYS_PLL_VE2_2_reg(data)   (*((volatile unsigned int*) SYS_PLL_VE2_2_reg)=data)
#define get_SYS_PLL_VE2_2_reg   (*((volatile unsigned int*) SYS_PLL_VE2_2_reg))
#define SYS_PLL_VE2_2_inst_adr                                                       "0x0075"
#define SYS_PLL_VE2_2_inst                                                           0x0075
#define SYS_PLL_VE2_2_REG_PLLVCPU_OEB_2_shift                                        (2)
#define SYS_PLL_VE2_2_REG_PLLVCPU_OEB_2_mask                                         (0x00000004)
#define SYS_PLL_VE2_2_REG_PLLVCPU_OEB_2(data)                                        (0x00000004&((data)<<2))
#define SYS_PLL_VE2_2_REG_PLLVCPU_OEB_2_src(data)                                    ((0x00000004&(data))>>2)
#define SYS_PLL_VE2_2_get_REG_PLLVCPU_OEB_2(data)                                    ((0x00000004&(data))>>2)
#define SYS_PLL_VE2_2_REG_PLLVCPU_RSTB_2_shift                                       (1)
#define SYS_PLL_VE2_2_REG_PLLVCPU_RSTB_2_mask                                        (0x00000002)
#define SYS_PLL_VE2_2_REG_PLLVCPU_RSTB_2(data)                                       (0x00000002&((data)<<1))
#define SYS_PLL_VE2_2_REG_PLLVCPU_RSTB_2_src(data)                                   ((0x00000002&(data))>>1)
#define SYS_PLL_VE2_2_get_REG_PLLVCPU_RSTB_2(data)                                   ((0x00000002&(data))>>1)
#define SYS_PLL_VE2_2_REG_PLLVCPU_POW_2_shift                                        (0)
#define SYS_PLL_VE2_2_REG_PLLVCPU_POW_2_mask                                         (0x00000001)
#define SYS_PLL_VE2_2_REG_PLLVCPU_POW_2(data)                                        (0x00000001&((data)<<0))
#define SYS_PLL_VE2_2_REG_PLLVCPU_POW_2_src(data)                                    ((0x00000001&(data))>>0)
#define SYS_PLL_VE2_2_get_REG_PLLVCPU_POW_2(data)                                    ((0x00000001&(data))>>0)


#define SYS_PLL_SD1                                                                  0x980001E0
#define SYS_PLL_SD1_reg_addr                                                         "0x980001E0"
#define SYS_PLL_SD1_reg                                                              0x980001E0
#define set_SYS_PLL_SD1_reg(data)   (*((volatile unsigned int*) SYS_PLL_SD1_reg)=data)
#define get_SYS_PLL_SD1_reg   (*((volatile unsigned int*) SYS_PLL_SD1_reg))
#define SYS_PLL_SD1_inst_adr                                                         "0x0078"
#define SYS_PLL_SD1_inst                                                             0x0078
#define SYS_PLL_SD1_reg_sel3318_shift                                                (13)
#define SYS_PLL_SD1_reg_sel3318_mask                                                 (0x00006000)
#define SYS_PLL_SD1_reg_sel3318(data)                                                (0x00006000&((data)<<13))
#define SYS_PLL_SD1_reg_sel3318_src(data)                                            ((0x00006000&(data))>>13)
#define SYS_PLL_SD1_get_reg_sel3318(data)                                            ((0x00006000&(data))>>13)
#define SYS_PLL_SD1_phsel1_shift                                                     (8)
#define SYS_PLL_SD1_phsel1_mask                                                      (0x00001F00)
#define SYS_PLL_SD1_phsel1(data)                                                     (0x00001F00&((data)<<8))
#define SYS_PLL_SD1_phsel1_src(data)                                                 ((0x00001F00&(data))>>8)
#define SYS_PLL_SD1_get_phsel1(data)                                                 ((0x00001F00&(data))>>8)
#define SYS_PLL_SD1_phsel0_shift                                                     (3)
#define SYS_PLL_SD1_phsel0_mask                                                      (0x000000F8)
#define SYS_PLL_SD1_phsel0(data)                                                     (0x000000F8&((data)<<3))
#define SYS_PLL_SD1_phsel0_src(data)                                                 ((0x000000F8&(data))>>3)
#define SYS_PLL_SD1_get_phsel0(data)                                                 ((0x000000F8&(data))>>3)
#define SYS_PLL_SD1_phrstb_dly_sel_shift                                             (2)
#define SYS_PLL_SD1_phrstb_dly_sel_mask                                              (0x00000004)
#define SYS_PLL_SD1_phrstb_dly_sel(data)                                             (0x00000004&((data)<<2))
#define SYS_PLL_SD1_phrstb_dly_sel_src(data)                                         ((0x00000004&(data))>>2)
#define SYS_PLL_SD1_get_phrstb_dly_sel(data)                                         ((0x00000004&(data))>>2)
#define SYS_PLL_SD1_phrt0_shift                                                      (1)
#define SYS_PLL_SD1_phrt0_mask                                                       (0x00000002)
#define SYS_PLL_SD1_phrt0(data)                                                      (0x00000002&((data)<<1))
#define SYS_PLL_SD1_phrt0_src(data)                                                  ((0x00000002&(data))>>1)
#define SYS_PLL_SD1_get_phrt0(data)                                                  ((0x00000002&(data))>>1)
#define SYS_PLL_SD1_bias_en_shift                                                    (0)
#define SYS_PLL_SD1_bias_en_mask                                                     (0x00000001)
#define SYS_PLL_SD1_bias_en(data)                                                    (0x00000001&((data)<<0))
#define SYS_PLL_SD1_bias_en_src(data)                                                ((0x00000001&(data))>>0)
#define SYS_PLL_SD1_get_bias_en(data)                                                ((0x00000001&(data))>>0)


#define SYS_PLL_SD2                                                                  0x980001E4
#define SYS_PLL_SD2_reg_addr                                                         "0x980001E4"
#define SYS_PLL_SD2_reg                                                              0x980001E4
#define set_SYS_PLL_SD2_reg(data)   (*((volatile unsigned int*) SYS_PLL_SD2_reg)=data)
#define get_SYS_PLL_SD2_reg   (*((volatile unsigned int*) SYS_PLL_SD2_reg))
#define SYS_PLL_SD2_inst_adr                                                         "0x0079"
#define SYS_PLL_SD2_inst                                                             0x0079
#define SYS_PLL_SD2_en_cpnew_shift                                                   (26)
#define SYS_PLL_SD2_en_cpnew_mask                                                    (0x04000000)
#define SYS_PLL_SD2_en_cpnew(data)                                                   (0x04000000&((data)<<26))
#define SYS_PLL_SD2_en_cpnew_src(data)                                               ((0x04000000&(data))>>26)
#define SYS_PLL_SD2_get_en_cpnew(data)                                               ((0x04000000&(data))>>26)
#define SYS_PLL_SD2_ssc_div_ext_f_shift                                              (18)
#define SYS_PLL_SD2_ssc_div_ext_f_mask                                               (0x03FC0000)
#define SYS_PLL_SD2_ssc_div_ext_f(data)                                              (0x03FC0000&((data)<<18))
#define SYS_PLL_SD2_ssc_div_ext_f_src(data)                                          ((0x03FC0000&(data))>>18)
#define SYS_PLL_SD2_get_ssc_div_ext_f(data)                                          ((0x03FC0000&(data))>>18)
#define SYS_PLL_SD2_ssc_div_f_sel_shift                                              (17)
#define SYS_PLL_SD2_ssc_div_f_sel_mask                                               (0x00020000)
#define SYS_PLL_SD2_ssc_div_f_sel(data)                                              (0x00020000&((data)<<17))
#define SYS_PLL_SD2_ssc_div_f_sel_src(data)                                          ((0x00020000&(data))>>17)
#define SYS_PLL_SD2_get_ssc_div_f_sel(data)                                          ((0x00020000&(data))>>17)
#define SYS_PLL_SD2_ssc_8x_en_shift                                                  (16)
#define SYS_PLL_SD2_ssc_8x_en_mask                                                   (0x00010000)
#define SYS_PLL_SD2_ssc_8x_en(data)                                                  (0x00010000&((data)<<16))
#define SYS_PLL_SD2_ssc_8x_en_src(data)                                              ((0x00010000&(data))>>16)
#define SYS_PLL_SD2_get_ssc_8x_en(data)                                              ((0x00010000&(data))>>16)
#define SYS_PLL_SD2_ssc_depth_shift                                                  (13)
#define SYS_PLL_SD2_ssc_depth_mask                                                   (0x0000E000)
#define SYS_PLL_SD2_ssc_depth(data)                                                  (0x0000E000&((data)<<13))
#define SYS_PLL_SD2_ssc_depth_src(data)                                              ((0x0000E000&(data))>>13)
#define SYS_PLL_SD2_get_ssc_depth(data)                                              ((0x0000E000&(data))>>13)
#define SYS_PLL_SD2_sscpll_rs_shift                                                  (10)
#define SYS_PLL_SD2_sscpll_rs_mask                                                   (0x00001C00)
#define SYS_PLL_SD2_sscpll_rs(data)                                                  (0x00001C00&((data)<<10))
#define SYS_PLL_SD2_sscpll_rs_src(data)                                              ((0x00001C00&(data))>>10)
#define SYS_PLL_SD2_get_sscpll_rs(data)                                              ((0x00001C00&(data))>>10)
#define SYS_PLL_SD2_sscpll_icp_shift                                                 (5)
#define SYS_PLL_SD2_sscpll_icp_mask                                                  (0x000003E0)
#define SYS_PLL_SD2_sscpll_icp(data)                                                 (0x000003E0&((data)<<5))
#define SYS_PLL_SD2_sscpll_icp_src(data)                                             ((0x000003E0&(data))>>5)
#define SYS_PLL_SD2_get_sscpll_icp(data)                                             ((0x000003E0&(data))>>5)
#define SYS_PLL_SD2_sscpll_cs1_shift                                                 (3)
#define SYS_PLL_SD2_sscpll_cs1_mask                                                  (0x00000018)
#define SYS_PLL_SD2_sscpll_cs1(data)                                                 (0x00000018&((data)<<3))
#define SYS_PLL_SD2_sscpll_cs1_src(data)                                             ((0x00000018&(data))>>3)
#define SYS_PLL_SD2_get_sscpll_cs1(data)                                             ((0x00000018&(data))>>3)
#define SYS_PLL_SD2_reg_tune11_shift                                                 (1)
#define SYS_PLL_SD2_reg_tune11_mask                                                  (0x00000006)
#define SYS_PLL_SD2_reg_tune11(data)                                                 (0x00000006&((data)<<1))
#define SYS_PLL_SD2_reg_tune11_src(data)                                             ((0x00000006&(data))>>1)
#define SYS_PLL_SD2_get_reg_tune11(data)                                             ((0x00000006&(data))>>1)
#define SYS_PLL_SD2_sscldo_en_shift                                                  (0)
#define SYS_PLL_SD2_sscldo_en_mask                                                   (0x00000001)
#define SYS_PLL_SD2_sscldo_en(data)                                                  (0x00000001&((data)<<0))
#define SYS_PLL_SD2_sscldo_en_src(data)                                              ((0x00000001&(data))>>0)
#define SYS_PLL_SD2_get_sscldo_en(data)                                              ((0x00000001&(data))>>0)


#define SYS_PLL_SD3                                                                  0x980001E8
#define SYS_PLL_SD3_reg_addr                                                         "0x980001E8"
#define SYS_PLL_SD3_reg                                                              0x980001E8
#define set_SYS_PLL_SD3_reg(data)   (*((volatile unsigned int*) SYS_PLL_SD3_reg)=data)
#define get_SYS_PLL_SD3_reg   (*((volatile unsigned int*) SYS_PLL_SD3_reg))
#define SYS_PLL_SD3_inst_adr                                                         "0x007A"
#define SYS_PLL_SD3_inst                                                             0x007A
#define SYS_PLL_SD3_ssc_div_n_shift                                                  (16)
#define SYS_PLL_SD3_ssc_div_n_mask                                                   (0x03FF0000)
#define SYS_PLL_SD3_ssc_div_n(data)                                                  (0x03FF0000&((data)<<16))
#define SYS_PLL_SD3_ssc_div_n_src(data)                                              ((0x03FF0000&(data))>>16)
#define SYS_PLL_SD3_get_ssc_div_n(data)                                              ((0x03FF0000&(data))>>16)
#define SYS_PLL_SD3_ssc_step_in_shift                                                (8)
#define SYS_PLL_SD3_ssc_step_in_mask                                                 (0x00007F00)
#define SYS_PLL_SD3_ssc_step_in(data)                                                (0x00007F00&((data)<<8))
#define SYS_PLL_SD3_ssc_step_in_src(data)                                            ((0x00007F00&(data))>>8)
#define SYS_PLL_SD3_get_ssc_step_in(data)                                            ((0x00007F00&(data))>>8)
#define SYS_PLL_SD3_ssc_tbase_shift                                                  (0)
#define SYS_PLL_SD3_ssc_tbase_mask                                                   (0x000000FF)
#define SYS_PLL_SD3_ssc_tbase(data)                                                  (0x000000FF&((data)<<0))
#define SYS_PLL_SD3_ssc_tbase_src(data)                                              ((0x000000FF&(data))>>0)
#define SYS_PLL_SD3_get_ssc_tbase(data)                                              ((0x000000FF&(data))>>0)


#define SYS_PLL_SD4                                                                  0x980001EC
#define SYS_PLL_SD4_reg_addr                                                         "0x980001EC"
#define SYS_PLL_SD4_reg                                                              0x980001EC
#define set_SYS_PLL_SD4_reg(data)   (*((volatile unsigned int*) SYS_PLL_SD4_reg)=data)
#define get_SYS_PLL_SD4_reg   (*((volatile unsigned int*) SYS_PLL_SD4_reg))
#define SYS_PLL_SD4_inst_adr                                                         "0x007B"
#define SYS_PLL_SD4_inst                                                             0x007B
#define SYS_PLL_SD4_ssc_pll_pow_shift                                                (2)
#define SYS_PLL_SD4_ssc_pll_pow_mask                                                 (0x00000004)
#define SYS_PLL_SD4_ssc_pll_pow(data)                                                (0x00000004&((data)<<2))
#define SYS_PLL_SD4_ssc_pll_pow_src(data)                                            ((0x00000004&(data))>>2)
#define SYS_PLL_SD4_get_ssc_pll_pow(data)                                            ((0x00000004&(data))>>2)
#define SYS_PLL_SD4_ssc_pll_rstb_shift                                               (1)
#define SYS_PLL_SD4_ssc_pll_rstb_mask                                                (0x00000002)
#define SYS_PLL_SD4_ssc_pll_rstb(data)                                               (0x00000002&((data)<<1))
#define SYS_PLL_SD4_ssc_pll_rstb_src(data)                                           ((0x00000002&(data))>>1)
#define SYS_PLL_SD4_get_ssc_pll_rstb(data)                                           ((0x00000002&(data))>>1)
#define SYS_PLL_SD4_ssc_rstb_shift                                                   (0)
#define SYS_PLL_SD4_ssc_rstb_mask                                                    (0x00000001)
#define SYS_PLL_SD4_ssc_rstb(data)                                                   (0x00000001&((data)<<0))
#define SYS_PLL_SD4_ssc_rstb_src(data)                                               ((0x00000001&(data))>>0)
#define SYS_PLL_SD4_get_ssc_rstb(data)                                               ((0x00000001&(data))>>0)


#define SYS_PLL_EMMC1                                                                0x980001F0
#define SYS_PLL_EMMC1_reg_addr                                                       "0x980001F0"
#define SYS_PLL_EMMC1_reg                                                            0x980001F0
#define set_SYS_PLL_EMMC1_reg(data)   (*((volatile unsigned int*) SYS_PLL_EMMC1_reg)=data)
#define get_SYS_PLL_EMMC1_reg   (*((volatile unsigned int*) SYS_PLL_EMMC1_reg))
#define SYS_PLL_EMMC1_inst_adr                                                       "0x007C"
#define SYS_PLL_EMMC1_inst                                                           0x007C
#define SYS_PLL_EMMC1_phsel1_shift                                                   (8)
#define SYS_PLL_EMMC1_phsel1_mask                                                    (0x00001F00)
#define SYS_PLL_EMMC1_phsel1(data)                                                   (0x00001F00&((data)<<8))
#define SYS_PLL_EMMC1_phsel1_src(data)                                               ((0x00001F00&(data))>>8)
#define SYS_PLL_EMMC1_get_phsel1(data)                                               ((0x00001F00&(data))>>8)
#define SYS_PLL_EMMC1_phsel0_shift                                                   (3)
#define SYS_PLL_EMMC1_phsel0_mask                                                    (0x000000F8)
#define SYS_PLL_EMMC1_phsel0(data)                                                   (0x000000F8&((data)<<3))
#define SYS_PLL_EMMC1_phsel0_src(data)                                               ((0x000000F8&(data))>>3)
#define SYS_PLL_EMMC1_get_phsel0(data)                                               ((0x000000F8&(data))>>3)
#define SYS_PLL_EMMC1_phrstb_dly_sel_shift                                           (2)
#define SYS_PLL_EMMC1_phrstb_dly_sel_mask                                            (0x00000004)
#define SYS_PLL_EMMC1_phrstb_dly_sel(data)                                           (0x00000004&((data)<<2))
#define SYS_PLL_EMMC1_phrstb_dly_sel_src(data)                                       ((0x00000004&(data))>>2)
#define SYS_PLL_EMMC1_get_phrstb_dly_sel(data)                                       ((0x00000004&(data))>>2)
#define SYS_PLL_EMMC1_phrt0_shift                                                    (1)
#define SYS_PLL_EMMC1_phrt0_mask                                                     (0x00000002)
#define SYS_PLL_EMMC1_phrt0(data)                                                    (0x00000002&((data)<<1))
#define SYS_PLL_EMMC1_phrt0_src(data)                                                ((0x00000002&(data))>>1)
#define SYS_PLL_EMMC1_get_phrt0(data)                                                ((0x00000002&(data))>>1)
#define SYS_PLL_EMMC1_bias_en_shift                                                  (0)
#define SYS_PLL_EMMC1_bias_en_mask                                                   (0x00000001)
#define SYS_PLL_EMMC1_bias_en(data)                                                  (0x00000001&((data)<<0))
#define SYS_PLL_EMMC1_bias_en_src(data)                                              ((0x00000001&(data))>>0)
#define SYS_PLL_EMMC1_get_bias_en(data)                                              ((0x00000001&(data))>>0)


#define SYS_PLL_EMMC2                                                                0x980001F4
#define SYS_PLL_EMMC2_reg_addr                                                       "0x980001F4"
#define SYS_PLL_EMMC2_reg                                                            0x980001F4
#define set_SYS_PLL_EMMC2_reg(data)   (*((volatile unsigned int*) SYS_PLL_EMMC2_reg)=data)
#define get_SYS_PLL_EMMC2_reg   (*((volatile unsigned int*) SYS_PLL_EMMC2_reg))
#define SYS_PLL_EMMC2_inst_adr                                                       "0x007D"
#define SYS_PLL_EMMC2_inst                                                           0x007D
#define SYS_PLL_EMMC2_en_cpnew_shift                                                 (26)
#define SYS_PLL_EMMC2_en_cpnew_mask                                                  (0x04000000)
#define SYS_PLL_EMMC2_en_cpnew(data)                                                 (0x04000000&((data)<<26))
#define SYS_PLL_EMMC2_en_cpnew_src(data)                                             ((0x04000000&(data))>>26)
#define SYS_PLL_EMMC2_get_en_cpnew(data)                                             ((0x04000000&(data))>>26)
#define SYS_PLL_EMMC2_ssc_div_ext_f_shift                                            (18)
#define SYS_PLL_EMMC2_ssc_div_ext_f_mask                                             (0x03FC0000)
#define SYS_PLL_EMMC2_ssc_div_ext_f(data)                                            (0x03FC0000&((data)<<18))
#define SYS_PLL_EMMC2_ssc_div_ext_f_src(data)                                        ((0x03FC0000&(data))>>18)
#define SYS_PLL_EMMC2_get_ssc_div_ext_f(data)                                        ((0x03FC0000&(data))>>18)
#define SYS_PLL_EMMC2_ssc_div_f_sel_shift                                            (17)
#define SYS_PLL_EMMC2_ssc_div_f_sel_mask                                             (0x00020000)
#define SYS_PLL_EMMC2_ssc_div_f_sel(data)                                            (0x00020000&((data)<<17))
#define SYS_PLL_EMMC2_ssc_div_f_sel_src(data)                                        ((0x00020000&(data))>>17)
#define SYS_PLL_EMMC2_get_ssc_div_f_sel(data)                                        ((0x00020000&(data))>>17)
#define SYS_PLL_EMMC2_ssc_8x_en_shift                                                (16)
#define SYS_PLL_EMMC2_ssc_8x_en_mask                                                 (0x00010000)
#define SYS_PLL_EMMC2_ssc_8x_en(data)                                                (0x00010000&((data)<<16))
#define SYS_PLL_EMMC2_ssc_8x_en_src(data)                                            ((0x00010000&(data))>>16)
#define SYS_PLL_EMMC2_get_ssc_8x_en(data)                                            ((0x00010000&(data))>>16)
#define SYS_PLL_EMMC2_ssc_depth_shift                                                (13)
#define SYS_PLL_EMMC2_ssc_depth_mask                                                 (0x0000E000)
#define SYS_PLL_EMMC2_ssc_depth(data)                                                (0x0000E000&((data)<<13))
#define SYS_PLL_EMMC2_ssc_depth_src(data)                                            ((0x0000E000&(data))>>13)
#define SYS_PLL_EMMC2_get_ssc_depth(data)                                            ((0x0000E000&(data))>>13)
#define SYS_PLL_EMMC2_sscpll_rs_shift                                                (10)
#define SYS_PLL_EMMC2_sscpll_rs_mask                                                 (0x00001C00)
#define SYS_PLL_EMMC2_sscpll_rs(data)                                                (0x00001C00&((data)<<10))
#define SYS_PLL_EMMC2_sscpll_rs_src(data)                                            ((0x00001C00&(data))>>10)
#define SYS_PLL_EMMC2_get_sscpll_rs(data)                                            ((0x00001C00&(data))>>10)
#define SYS_PLL_EMMC2_sscpll_icp_shift                                               (5)
#define SYS_PLL_EMMC2_sscpll_icp_mask                                                (0x000003E0)
#define SYS_PLL_EMMC2_sscpll_icp(data)                                               (0x000003E0&((data)<<5))
#define SYS_PLL_EMMC2_sscpll_icp_src(data)                                           ((0x000003E0&(data))>>5)
#define SYS_PLL_EMMC2_get_sscpll_icp(data)                                           ((0x000003E0&(data))>>5)
#define SYS_PLL_EMMC2_sscpll_cs1_shift                                               (3)
#define SYS_PLL_EMMC2_sscpll_cs1_mask                                                (0x00000018)
#define SYS_PLL_EMMC2_sscpll_cs1(data)                                               (0x00000018&((data)<<3))
#define SYS_PLL_EMMC2_sscpll_cs1_src(data)                                           ((0x00000018&(data))>>3)
#define SYS_PLL_EMMC2_get_sscpll_cs1(data)                                           ((0x00000018&(data))>>3)
#define SYS_PLL_EMMC2_reg_tune11_shift                                               (1)
#define SYS_PLL_EMMC2_reg_tune11_mask                                                (0x00000006)
#define SYS_PLL_EMMC2_reg_tune11(data)                                               (0x00000006&((data)<<1))
#define SYS_PLL_EMMC2_reg_tune11_src(data)                                           ((0x00000006&(data))>>1)
#define SYS_PLL_EMMC2_get_reg_tune11(data)                                           ((0x00000006&(data))>>1)
#define SYS_PLL_EMMC2_sscldo_en_shift                                                (0)
#define SYS_PLL_EMMC2_sscldo_en_mask                                                 (0x00000001)
#define SYS_PLL_EMMC2_sscldo_en(data)                                                (0x00000001&((data)<<0))
#define SYS_PLL_EMMC2_sscldo_en_src(data)                                            ((0x00000001&(data))>>0)
#define SYS_PLL_EMMC2_get_sscldo_en(data)                                            ((0x00000001&(data))>>0)


#define SYS_PLL_EMMC3                                                                0x980001F8
#define SYS_PLL_EMMC3_reg_addr                                                       "0x980001F8"
#define SYS_PLL_EMMC3_reg                                                            0x980001F8
#define set_SYS_PLL_EMMC3_reg(data)   (*((volatile unsigned int*) SYS_PLL_EMMC3_reg)=data)
#define get_SYS_PLL_EMMC3_reg   (*((volatile unsigned int*) SYS_PLL_EMMC3_reg))
#define SYS_PLL_EMMC3_inst_adr                                                       "0x007E"
#define SYS_PLL_EMMC3_inst                                                           0x007E
#define SYS_PLL_EMMC3_ssc_div_n_shift                                                (16)
#define SYS_PLL_EMMC3_ssc_div_n_mask                                                 (0x03FF0000)
#define SYS_PLL_EMMC3_ssc_div_n(data)                                                (0x03FF0000&((data)<<16))
#define SYS_PLL_EMMC3_ssc_div_n_src(data)                                            ((0x03FF0000&(data))>>16)
#define SYS_PLL_EMMC3_get_ssc_div_n(data)                                            ((0x03FF0000&(data))>>16)
#define SYS_PLL_EMMC3_ssc_step_in_shift                                              (8)
#define SYS_PLL_EMMC3_ssc_step_in_mask                                               (0x00007F00)
#define SYS_PLL_EMMC3_ssc_step_in(data)                                              (0x00007F00&((data)<<8))
#define SYS_PLL_EMMC3_ssc_step_in_src(data)                                          ((0x00007F00&(data))>>8)
#define SYS_PLL_EMMC3_get_ssc_step_in(data)                                          ((0x00007F00&(data))>>8)
#define SYS_PLL_EMMC3_ssc_tbase_shift                                                (0)
#define SYS_PLL_EMMC3_ssc_tbase_mask                                                 (0x000000FF)
#define SYS_PLL_EMMC3_ssc_tbase(data)                                                (0x000000FF&((data)<<0))
#define SYS_PLL_EMMC3_ssc_tbase_src(data)                                            ((0x000000FF&(data))>>0)
#define SYS_PLL_EMMC3_get_ssc_tbase(data)                                            ((0x000000FF&(data))>>0)


#define SYS_PLL_EMMC4                                                                0x980001FC
#define SYS_PLL_EMMC4_reg_addr                                                       "0x980001FC"
#define SYS_PLL_EMMC4_reg                                                            0x980001FC
#define set_SYS_PLL_EMMC4_reg(data)   (*((volatile unsigned int*) SYS_PLL_EMMC4_reg)=data)
#define get_SYS_PLL_EMMC4_reg   (*((volatile unsigned int*) SYS_PLL_EMMC4_reg))
#define SYS_PLL_EMMC4_inst_adr                                                       "0x007F"
#define SYS_PLL_EMMC4_inst                                                           0x007F
#define SYS_PLL_EMMC4_ssc_pll_pow_shift                                              (2)
#define SYS_PLL_EMMC4_ssc_pll_pow_mask                                               (0x00000004)
#define SYS_PLL_EMMC4_ssc_pll_pow(data)                                              (0x00000004&((data)<<2))
#define SYS_PLL_EMMC4_ssc_pll_pow_src(data)                                          ((0x00000004&(data))>>2)
#define SYS_PLL_EMMC4_get_ssc_pll_pow(data)                                          ((0x00000004&(data))>>2)
#define SYS_PLL_EMMC4_ssc_pll_rstb_shift                                             (1)
#define SYS_PLL_EMMC4_ssc_pll_rstb_mask                                              (0x00000002)
#define SYS_PLL_EMMC4_ssc_pll_rstb(data)                                             (0x00000002&((data)<<1))
#define SYS_PLL_EMMC4_ssc_pll_rstb_src(data)                                         ((0x00000002&(data))>>1)
#define SYS_PLL_EMMC4_get_ssc_pll_rstb(data)                                         ((0x00000002&(data))>>1)
#define SYS_PLL_EMMC4_ssc_rstb_shift                                                 (0)
#define SYS_PLL_EMMC4_ssc_rstb_mask                                                  (0x00000001)
#define SYS_PLL_EMMC4_ssc_rstb(data)                                                 (0x00000001&((data)<<0))
#define SYS_PLL_EMMC4_ssc_rstb_src(data)                                             ((0x00000001&(data))>>0)
#define SYS_PLL_EMMC4_get_ssc_rstb(data)                                             ((0x00000001&(data))>>0)


#define SYS_PLL_OTHER                                                                0x98000200
#define SYS_PLL_OTHER_reg_addr                                                       "0x98000200"
#define SYS_PLL_OTHER_reg                                                            0x98000200
#define set_SYS_PLL_OTHER_reg(data)   (*((volatile unsigned int*) SYS_PLL_OTHER_reg)=data)
#define get_SYS_PLL_OTHER_reg   (*((volatile unsigned int*) SYS_PLL_OTHER_reg))
#define SYS_PLL_OTHER_inst_adr                                                       "0x0080"
#define SYS_PLL_OTHER_inst                                                           0x0080
#define SYS_PLL_OTHER_REG_TEST_SEL_shift                                             (12)
#define SYS_PLL_OTHER_REG_TEST_SEL_mask                                              (0x00003000)
#define SYS_PLL_OTHER_REG_TEST_SEL(data)                                             (0x00003000&((data)<<12))
#define SYS_PLL_OTHER_REG_TEST_SEL_src(data)                                         ((0x00003000&(data))>>12)
#define SYS_PLL_OTHER_get_REG_TEST_SEL(data)                                         ((0x00003000&(data))>>12)
#define SYS_PLL_OTHER_POR_VSET_shift                                                 (11)
#define SYS_PLL_OTHER_POR_VSET_mask                                                  (0x00000800)
#define SYS_PLL_OTHER_POR_VSET(data)                                                 (0x00000800&((data)<<11))
#define SYS_PLL_OTHER_POR_VSET_src(data)                                             ((0x00000800&(data))>>11)
#define SYS_PLL_OTHER_get_POR_VSET(data)                                             ((0x00000800&(data))>>11)
#define SYS_PLL_OTHER_REG_PLLDDSB_CKIN_SEL_shift                                     (10)
#define SYS_PLL_OTHER_REG_PLLDDSB_CKIN_SEL_mask                                      (0x00000400)
#define SYS_PLL_OTHER_REG_PLLDDSB_CKIN_SEL(data)                                     (0x00000400&((data)<<10))
#define SYS_PLL_OTHER_REG_PLLDDSB_CKIN_SEL_src(data)                                 ((0x00000400&(data))>>10)
#define SYS_PLL_OTHER_get_REG_PLLDDSB_CKIN_SEL(data)                                 ((0x00000400&(data))>>10)
#define SYS_PLL_OTHER_REG_PLLDISP_SEL_shift                                          (8)
#define SYS_PLL_OTHER_REG_PLLDISP_SEL_mask                                           (0x00000300)
#define SYS_PLL_OTHER_REG_PLLDISP_SEL(data)                                          (0x00000300&((data)<<8))
#define SYS_PLL_OTHER_REG_PLLDISP_SEL_src(data)                                      ((0x00000300&(data))>>8)
#define SYS_PLL_OTHER_get_REG_PLLDISP_SEL(data)                                      ((0x00000300&(data))>>8)
#define SYS_PLL_OTHER_REG_HDMITX_27M_SEL_shift                                       (6)
#define SYS_PLL_OTHER_REG_HDMITX_27M_SEL_mask                                        (0x000000C0)
#define SYS_PLL_OTHER_REG_HDMITX_27M_SEL(data)                                       (0x000000C0&((data)<<6))
#define SYS_PLL_OTHER_REG_HDMITX_27M_SEL_src(data)                                   ((0x000000C0&(data))>>6)
#define SYS_PLL_OTHER_get_REG_HDMITX_27M_SEL(data)                                   ((0x000000C0&(data))>>6)
#define SYS_PLL_OTHER_REG_PLLGPU_BYPASS_PI_shift                                     (5)
#define SYS_PLL_OTHER_REG_PLLGPU_BYPASS_PI_mask                                      (0x00000020)
#define SYS_PLL_OTHER_REG_PLLGPU_BYPASS_PI(data)                                     (0x00000020&((data)<<5))
#define SYS_PLL_OTHER_REG_PLLGPU_BYPASS_PI_src(data)                                 ((0x00000020&(data))>>5)
#define SYS_PLL_OTHER_get_REG_PLLGPU_BYPASS_PI(data)                                 ((0x00000020&(data))>>5)
#define SYS_PLL_OTHER_REG_PLLDDSB_BYPASS_PI_shift                                    (4)
#define SYS_PLL_OTHER_REG_PLLDDSB_BYPASS_PI_mask                                     (0x00000010)
#define SYS_PLL_OTHER_REG_PLLDDSB_BYPASS_PI(data)                                    (0x00000010&((data)<<4))
#define SYS_PLL_OTHER_REG_PLLDDSB_BYPASS_PI_src(data)                                ((0x00000010&(data))>>4)
#define SYS_PLL_OTHER_get_REG_PLLDDSB_BYPASS_PI(data)                                ((0x00000010&(data))>>4)
#define SYS_PLL_OTHER_REG_PLLDDSA_BYPASS_PI_shift                                    (3)
#define SYS_PLL_OTHER_REG_PLLDDSA_BYPASS_PI_mask                                     (0x00000008)
#define SYS_PLL_OTHER_REG_PLLDDSA_BYPASS_PI(data)                                    (0x00000008&((data)<<3))
#define SYS_PLL_OTHER_REG_PLLDDSA_BYPASS_PI_src(data)                                ((0x00000008&(data))>>3)
#define SYS_PLL_OTHER_get_REG_PLLDDSA_BYPASS_PI(data)                                ((0x00000008&(data))>>3)
#define SYS_PLL_OTHER_REG_PLLBUS_BYPASS_PI_H_shift                                   (2)
#define SYS_PLL_OTHER_REG_PLLBUS_BYPASS_PI_H_mask                                    (0x00000004)
#define SYS_PLL_OTHER_REG_PLLBUS_BYPASS_PI_H(data)                                   (0x00000004&((data)<<2))
#define SYS_PLL_OTHER_REG_PLLBUS_BYPASS_PI_H_src(data)                               ((0x00000004&(data))>>2)
#define SYS_PLL_OTHER_get_REG_PLLBUS_BYPASS_PI_H(data)                               ((0x00000004&(data))>>2)
#define SYS_PLL_OTHER_REG_PLLBUS_BYPASS_PI_shift                                     (1)
#define SYS_PLL_OTHER_REG_PLLBUS_BYPASS_PI_mask                                      (0x00000002)
#define SYS_PLL_OTHER_REG_PLLBUS_BYPASS_PI(data)                                     (0x00000002&((data)<<1))
#define SYS_PLL_OTHER_REG_PLLBUS_BYPASS_PI_src(data)                                 ((0x00000002&(data))>>1)
#define SYS_PLL_OTHER_get_REG_PLLBUS_BYPASS_PI(data)                                 ((0x00000002&(data))>>1)
#define SYS_PLL_OTHER_REG_PLLACPU_BYPASS_PI_shift                                    (0)
#define SYS_PLL_OTHER_REG_PLLACPU_BYPASS_PI_mask                                     (0x00000001)
#define SYS_PLL_OTHER_REG_PLLACPU_BYPASS_PI(data)                                    (0x00000001&((data)<<0))
#define SYS_PLL_OTHER_REG_PLLACPU_BYPASS_PI_src(data)                                ((0x00000001&(data))>>0)
#define SYS_PLL_OTHER_get_REG_PLLACPU_BYPASS_PI(data)                                ((0x00000001&(data))>>0)


#define SYS_PLL_HDMI_SD1                                                             0x98000204
#define SYS_PLL_HDMI_SD1_reg_addr                                                    "0x98000204"
#define SYS_PLL_HDMI_SD1_reg                                                         0x98000204
#define set_SYS_PLL_HDMI_SD1_reg(data)   (*((volatile unsigned int*) SYS_PLL_HDMI_SD1_reg)=data)
#define get_SYS_PLL_HDMI_SD1_reg   (*((volatile unsigned int*) SYS_PLL_HDMI_SD1_reg))
#define SYS_PLL_HDMI_SD1_inst_adr                                                    "0x0081"
#define SYS_PLL_HDMI_SD1_inst                                                        0x0081
#define SYS_PLL_HDMI_SD1_time_rdy_ckout_shift                                        (30)
#define SYS_PLL_HDMI_SD1_time_rdy_ckout_mask                                         (0xC0000000)
#define SYS_PLL_HDMI_SD1_time_rdy_ckout(data)                                        (0xC0000000&((data)<<30))
#define SYS_PLL_HDMI_SD1_time_rdy_ckout_src(data)                                    ((0xC0000000&(data))>>30)
#define SYS_PLL_HDMI_SD1_get_time_rdy_ckout(data)                                    ((0xC0000000&(data))>>30)
#define SYS_PLL_HDMI_SD1_time2_rst_width_shift                                       (28)
#define SYS_PLL_HDMI_SD1_time2_rst_width_mask                                        (0x30000000)
#define SYS_PLL_HDMI_SD1_time2_rst_width(data)                                       (0x30000000&((data)<<28))
#define SYS_PLL_HDMI_SD1_time2_rst_width_src(data)                                   ((0x30000000&(data))>>28)
#define SYS_PLL_HDMI_SD1_get_time2_rst_width(data)                                   ((0x30000000&(data))>>28)
#define SYS_PLL_HDMI_SD1_pcr_rst_n_shift                                             (27)
#define SYS_PLL_HDMI_SD1_pcr_rst_n_mask                                              (0x08000000)
#define SYS_PLL_HDMI_SD1_pcr_rst_n(data)                                             (0x08000000&((data)<<27))
#define SYS_PLL_HDMI_SD1_pcr_rst_n_src(data)                                         ((0x08000000&(data))>>27)
#define SYS_PLL_HDMI_SD1_get_pcr_rst_n(data)                                         ((0x08000000&(data))>>27)
#define SYS_PLL_HDMI_SD1_time0_ck_shift                                              (24)
#define SYS_PLL_HDMI_SD1_time0_ck_mask                                               (0x07000000)
#define SYS_PLL_HDMI_SD1_time0_ck(data)                                              (0x07000000&((data)<<24))
#define SYS_PLL_HDMI_SD1_time0_ck_src(data)                                          ((0x07000000&(data))>>24)
#define SYS_PLL_HDMI_SD1_get_time0_ck(data)                                          ((0x07000000&(data))>>24)
#define SYS_PLL_HDMI_SD1_f390k_shift                                                 (22)
#define SYS_PLL_HDMI_SD1_f390k_mask                                                  (0x00C00000)
#define SYS_PLL_HDMI_SD1_f390k(data)                                                 (0x00C00000&((data)<<22))
#define SYS_PLL_HDMI_SD1_f390k_src(data)                                             ((0x00C00000&(data))>>22)
#define SYS_PLL_HDMI_SD1_get_f390k(data)                                             ((0x00C00000&(data))>>22)
#define SYS_PLL_HDMI_SD1_pll_en_shift                                                (21)
#define SYS_PLL_HDMI_SD1_pll_en_mask                                                 (0x00200000)
#define SYS_PLL_HDMI_SD1_pll_en(data)                                                (0x00200000&((data)<<21))
#define SYS_PLL_HDMI_SD1_pll_en_src(data)                                            ((0x00200000&(data))>>21)
#define SYS_PLL_HDMI_SD1_get_pll_en(data)                                            ((0x00200000&(data))>>21)
#define SYS_PLL_HDMI_SD1_en_wdog_shift                                               (20)
#define SYS_PLL_HDMI_SD1_en_wdog_mask                                                (0x00100000)
#define SYS_PLL_HDMI_SD1_en_wdog(data)                                               (0x00100000&((data)<<20))
#define SYS_PLL_HDMI_SD1_en_wdog_src(data)                                           ((0x00100000&(data))>>20)
#define SYS_PLL_HDMI_SD1_get_en_wdog(data)                                           ((0x00100000&(data))>>20)
#define SYS_PLL_HDMI_SD1_ssc_ckinv_shift                                             (19)
#define SYS_PLL_HDMI_SD1_ssc_ckinv_mask                                              (0x00080000)
#define SYS_PLL_HDMI_SD1_ssc_ckinv(data)                                             (0x00080000&((data)<<19))
#define SYS_PLL_HDMI_SD1_ssc_ckinv_src(data)                                         ((0x00080000&(data))>>19)
#define SYS_PLL_HDMI_SD1_get_ssc_ckinv(data)                                         ((0x00080000&(data))>>19)
#define SYS_PLL_HDMI_SD1_fcode_shift                                                 (8)
#define SYS_PLL_HDMI_SD1_fcode_mask                                                  (0x0007FF00)
#define SYS_PLL_HDMI_SD1_fcode(data)                                                 (0x0007FF00&((data)<<8))
#define SYS_PLL_HDMI_SD1_fcode_src(data)                                             ((0x0007FF00&(data))>>8)
#define SYS_PLL_HDMI_SD1_get_fcode(data)                                             ((0x0007FF00&(data))>>8)
#define SYS_PLL_HDMI_SD1_ncode_shift                                                 (0)
#define SYS_PLL_HDMI_SD1_ncode_mask                                                  (0x000000FF)
#define SYS_PLL_HDMI_SD1_ncode(data)                                                 (0x000000FF&((data)<<0))
#define SYS_PLL_HDMI_SD1_ncode_src(data)                                             ((0x000000FF&(data))>>0)
#define SYS_PLL_HDMI_SD1_get_ncode(data)                                             ((0x000000FF&(data))>>0)


#define SYS_PLL_HDMI_SD2                                                             0x98000208
#define SYS_PLL_HDMI_SD2_reg_addr                                                    "0x98000208"
#define SYS_PLL_HDMI_SD2_reg                                                         0x98000208
#define set_SYS_PLL_HDMI_SD2_reg(data)   (*((volatile unsigned int*) SYS_PLL_HDMI_SD2_reg)=data)
#define get_SYS_PLL_HDMI_SD2_reg   (*((volatile unsigned int*) SYS_PLL_HDMI_SD2_reg))
#define SYS_PLL_HDMI_SD2_inst_adr                                                    "0x0082"
#define SYS_PLL_HDMI_SD2_inst                                                        0x0082
#define SYS_PLL_HDMI_SD2_bypass_pi_shift                                             (31)
#define SYS_PLL_HDMI_SD2_bypass_pi_mask                                              (0x80000000)
#define SYS_PLL_HDMI_SD2_bypass_pi(data)                                             (0x80000000&((data)<<31))
#define SYS_PLL_HDMI_SD2_bypass_pi_src(data)                                         ((0x80000000&(data))>>31)
#define SYS_PLL_HDMI_SD2_get_bypass_pi(data)                                         ((0x80000000&(data))>>31)
#define SYS_PLL_HDMI_SD2_en_pi_debug_shift                                           (30)
#define SYS_PLL_HDMI_SD2_en_pi_debug_mask                                            (0x40000000)
#define SYS_PLL_HDMI_SD2_en_pi_debug(data)                                           (0x40000000&((data)<<30))
#define SYS_PLL_HDMI_SD2_en_pi_debug_src(data)                                       ((0x40000000&(data))>>30)
#define SYS_PLL_HDMI_SD2_get_en_pi_debug(data)                                       ((0x40000000&(data))>>30)
#define SYS_PLL_HDMI_SD2_hs_oc_stop_diff_shift                                       (28)
#define SYS_PLL_HDMI_SD2_hs_oc_stop_diff_mask                                        (0x30000000)
#define SYS_PLL_HDMI_SD2_hs_oc_stop_diff(data)                                       (0x30000000&((data)<<28))
#define SYS_PLL_HDMI_SD2_hs_oc_stop_diff_src(data)                                   ((0x30000000&(data))>>28)
#define SYS_PLL_HDMI_SD2_get_hs_oc_stop_diff(data)                                   ((0x30000000&(data))>>28)
#define SYS_PLL_HDMI_SD2_sel_oc_mode_shift                                           (24)
#define SYS_PLL_HDMI_SD2_sel_oc_mode_mask                                            (0x03000000)
#define SYS_PLL_HDMI_SD2_sel_oc_mode(data)                                           (0x03000000&((data)<<24))
#define SYS_PLL_HDMI_SD2_sel_oc_mode_src(data)                                       ((0x03000000&(data))>>24)
#define SYS_PLL_HDMI_SD2_get_sel_oc_mode(data)                                       ((0x03000000&(data))>>24)
#define SYS_PLL_HDMI_SD2_oc_done_delay_shift                                         (16)
#define SYS_PLL_HDMI_SD2_oc_done_delay_mask                                          (0x003F0000)
#define SYS_PLL_HDMI_SD2_oc_done_delay(data)                                         (0x003F0000&((data)<<16))
#define SYS_PLL_HDMI_SD2_oc_done_delay_src(data)                                     ((0x003F0000&(data))>>16)
#define SYS_PLL_HDMI_SD2_get_oc_done_delay(data)                                     ((0x003F0000&(data))>>16)
#define SYS_PLL_HDMI_SD2_pi_cur_sel_shift                                            (12)
#define SYS_PLL_HDMI_SD2_pi_cur_sel_mask                                             (0x00007000)
#define SYS_PLL_HDMI_SD2_pi_cur_sel(data)                                            (0x00007000&((data)<<12))
#define SYS_PLL_HDMI_SD2_pi_cur_sel_src(data)                                        ((0x00007000&(data))>>12)
#define SYS_PLL_HDMI_SD2_get_pi_cur_sel(data)                                        ((0x00007000&(data))>>12)
#define SYS_PLL_HDMI_SD2_oc_step_set_shift                                           (2)
#define SYS_PLL_HDMI_SD2_oc_step_set_mask                                            (0x00000FFC)
#define SYS_PLL_HDMI_SD2_oc_step_set(data)                                           (0x00000FFC&((data)<<2))
#define SYS_PLL_HDMI_SD2_oc_step_set_src(data)                                       ((0x00000FFC&(data))>>2)
#define SYS_PLL_HDMI_SD2_get_oc_step_set(data)                                       ((0x00000FFC&(data))>>2)
#define SYS_PLL_HDMI_SD2_sdm_order_shift                                             (1)
#define SYS_PLL_HDMI_SD2_sdm_order_mask                                              (0x00000002)
#define SYS_PLL_HDMI_SD2_sdm_order(data)                                             (0x00000002&((data)<<1))
#define SYS_PLL_HDMI_SD2_sdm_order_src(data)                                         ((0x00000002&(data))>>1)
#define SYS_PLL_HDMI_SD2_get_sdm_order(data)                                         ((0x00000002&(data))>>1)
#define SYS_PLL_HDMI_SD2_oc_en_shift                                                 (0)
#define SYS_PLL_HDMI_SD2_oc_en_mask                                                  (0x00000001)
#define SYS_PLL_HDMI_SD2_oc_en(data)                                                 (0x00000001&((data)<<0))
#define SYS_PLL_HDMI_SD2_oc_en_src(data)                                             ((0x00000001&(data))>>0)
#define SYS_PLL_HDMI_SD2_get_oc_en(data)                                             ((0x00000001&(data))>>0)


#define SYS_PLL_HDMI_SD3                                                             0x98000210
#define SYS_PLL_HDMI_SD3_reg_addr                                                    "0x98000210"
#define SYS_PLL_HDMI_SD3_reg                                                         0x98000210
#define set_SYS_PLL_HDMI_SD3_reg(data)   (*((volatile unsigned int*) SYS_PLL_HDMI_SD3_reg)=data)
#define get_SYS_PLL_HDMI_SD3_reg   (*((volatile unsigned int*) SYS_PLL_HDMI_SD3_reg))
#define SYS_PLL_HDMI_SD3_inst_adr                                                    "0x0084"
#define SYS_PLL_HDMI_SD3_inst                                                        0x0084
#define SYS_PLL_HDMI_SD3_load_fcw_shift                                              (31)
#define SYS_PLL_HDMI_SD3_load_fcw_mask                                               (0x80000000)
#define SYS_PLL_HDMI_SD3_load_fcw(data)                                              (0x80000000&((data)<<31))
#define SYS_PLL_HDMI_SD3_load_fcw_src(data)                                          ((0x80000000&(data))>>31)
#define SYS_PLL_HDMI_SD3_get_load_fcw(data)                                          ((0x80000000&(data))>>31)
#define SYS_PLL_HDMI_SD3_fmod_shift                                                  (27)
#define SYS_PLL_HDMI_SD3_fmod_mask                                                   (0x08000000)
#define SYS_PLL_HDMI_SD3_fmod(data)                                                  (0x08000000&((data)<<27))
#define SYS_PLL_HDMI_SD3_fmod_src(data)                                              ((0x08000000&(data))>>27)
#define SYS_PLL_HDMI_SD3_get_fmod(data)                                              ((0x08000000&(data))>>27)
#define SYS_PLL_HDMI_SD3_fcode_debug_shift                                           (16)
#define SYS_PLL_HDMI_SD3_fcode_debug_mask                                            (0x07FF0000)
#define SYS_PLL_HDMI_SD3_fcode_debug(data)                                           (0x07FF0000&((data)<<16))
#define SYS_PLL_HDMI_SD3_fcode_debug_src(data)                                       ((0x07FF0000&(data))>>16)
#define SYS_PLL_HDMI_SD3_get_fcode_debug(data)                                       ((0x07FF0000&(data))>>16)
#define SYS_PLL_HDMI_SD3_ncode_debug_shift                                           (8)
#define SYS_PLL_HDMI_SD3_ncode_debug_mask                                            (0x0000FF00)
#define SYS_PLL_HDMI_SD3_ncode_debug(data)                                           (0x0000FF00&((data)<<8))
#define SYS_PLL_HDMI_SD3_ncode_debug_src(data)                                       ((0x0000FF00&(data))>>8)
#define SYS_PLL_HDMI_SD3_get_ncode_debug(data)                                       ((0x0000FF00&(data))>>8)
#define SYS_PLL_HDMI_SD3_clkrdy_shift                                                (1)
#define SYS_PLL_HDMI_SD3_clkrdy_mask                                                 (0x00000002)
#define SYS_PLL_HDMI_SD3_clkrdy(data)                                                (0x00000002&((data)<<1))
#define SYS_PLL_HDMI_SD3_clkrdy_src(data)                                            ((0x00000002&(data))>>1)
#define SYS_PLL_HDMI_SD3_get_clkrdy(data)                                            ((0x00000002&(data))>>1)
#define SYS_PLL_HDMI_SD3_oc_done_shift                                               (0)
#define SYS_PLL_HDMI_SD3_oc_done_mask                                                (0x00000001)
#define SYS_PLL_HDMI_SD3_oc_done(data)                                               (0x00000001&((data)<<0))
#define SYS_PLL_HDMI_SD3_oc_done_src(data)                                           ((0x00000001&(data))>>0)
#define SYS_PLL_HDMI_SD3_get_oc_done(data)                                           ((0x00000001&(data))>>0)


#define SYS_PLL_HDMI_SD4                                                             0x9800021c
#define SYS_PLL_HDMI_SD4_reg_addr                                                    "0x9800021C"
#define SYS_PLL_HDMI_SD4_reg                                                         0x9800021C
#define set_SYS_PLL_HDMI_SD4_reg(data)   (*((volatile unsigned int*) SYS_PLL_HDMI_SD4_reg)=data)
#define get_SYS_PLL_HDMI_SD4_reg   (*((volatile unsigned int*) SYS_PLL_HDMI_SD4_reg))
#define SYS_PLL_HDMI_SD4_inst_adr                                                    "0x0087"
#define SYS_PLL_HDMI_SD4_inst                                                        0x0087
#define SYS_PLL_HDMI_SD4_ssc_en_shift                                                (19)
#define SYS_PLL_HDMI_SD4_ssc_en_mask                                                 (0x00080000)
#define SYS_PLL_HDMI_SD4_ssc_en(data)                                                (0x00080000&((data)<<19))
#define SYS_PLL_HDMI_SD4_ssc_en_src(data)                                            ((0x00080000&(data))>>19)
#define SYS_PLL_HDMI_SD4_get_ssc_en(data)                                            ((0x00080000&(data))>>19)
#define SYS_PLL_HDMI_SD4_fcode_ssc_shift                                             (8)
#define SYS_PLL_HDMI_SD4_fcode_ssc_mask                                              (0x0007FF00)
#define SYS_PLL_HDMI_SD4_fcode_ssc(data)                                             (0x0007FF00&((data)<<8))
#define SYS_PLL_HDMI_SD4_fcode_ssc_src(data)                                         ((0x0007FF00&(data))>>8)
#define SYS_PLL_HDMI_SD4_get_fcode_ssc(data)                                         ((0x0007FF00&(data))>>8)
#define SYS_PLL_HDMI_SD4_ncode_ssc_shift                                             (0)
#define SYS_PLL_HDMI_SD4_ncode_ssc_mask                                              (0x000000FF)
#define SYS_PLL_HDMI_SD4_ncode_ssc(data)                                             (0x000000FF&((data)<<0))
#define SYS_PLL_HDMI_SD4_ncode_ssc_src(data)                                         ((0x000000FF&(data))>>0)
#define SYS_PLL_HDMI_SD4_get_ncode_ssc(data)                                         ((0x000000FF&(data))>>0)


#define SYS_PLL_HDMI_SD5                                                             0x98000220
#define SYS_PLL_HDMI_SD5_reg_addr                                                    "0x98000220"
#define SYS_PLL_HDMI_SD5_reg                                                         0x98000220
#define set_SYS_PLL_HDMI_SD5_reg(data)   (*((volatile unsigned int*) SYS_PLL_HDMI_SD5_reg)=data)
#define get_SYS_PLL_HDMI_SD5_reg   (*((volatile unsigned int*) SYS_PLL_HDMI_SD5_reg))
#define SYS_PLL_HDMI_SD5_inst_adr                                                    "0x0088"
#define SYS_PLL_HDMI_SD5_inst                                                        0x0088
#define SYS_PLL_HDMI_SD5_RSTB_HDMITX_shift                                           (23)
#define SYS_PLL_HDMI_SD5_RSTB_HDMITX_mask                                            (0x00800000)
#define SYS_PLL_HDMI_SD5_RSTB_HDMITX(data)                                           (0x00800000&((data)<<23))
#define SYS_PLL_HDMI_SD5_RSTB_HDMITX_src(data)                                       ((0x00800000&(data))>>23)
#define SYS_PLL_HDMI_SD5_get_RSTB_HDMITX(data)                                       ((0x00800000&(data))>>23)
#define SYS_PLL_HDMI_SD5_gran_auto_rst_shift                                         (22)
#define SYS_PLL_HDMI_SD5_gran_auto_rst_mask                                          (0x00400000)
#define SYS_PLL_HDMI_SD5_gran_auto_rst(data)                                         (0x00400000&((data)<<22))
#define SYS_PLL_HDMI_SD5_gran_auto_rst_src(data)                                     ((0x00400000&(data))>>22)
#define SYS_PLL_HDMI_SD5_get_gran_auto_rst(data)                                     ((0x00400000&(data))>>22)
#define SYS_PLL_HDMI_SD5_dot_gran_shift                                              (19)
#define SYS_PLL_HDMI_SD5_dot_gran_mask                                               (0x00380000)
#define SYS_PLL_HDMI_SD5_dot_gran(data)                                              (0x00380000&((data)<<19))
#define SYS_PLL_HDMI_SD5_dot_gran_src(data)                                          ((0x00380000&(data))>>19)
#define SYS_PLL_HDMI_SD5_get_dot_gran(data)                                          ((0x00380000&(data))>>19)
#define SYS_PLL_HDMI_SD5_gran_est_shift                                              (0)
#define SYS_PLL_HDMI_SD5_gran_est_mask                                               (0x0007FFFF)
#define SYS_PLL_HDMI_SD5_gran_est(data)                                              (0x0007FFFF&((data)<<0))
#define SYS_PLL_HDMI_SD5_gran_est_src(data)                                          ((0x0007FFFF&(data))>>0)
#define SYS_PLL_HDMI_SD5_get_gran_est(data)                                          ((0x0007FFFF&(data))>>0)


#define SYS_BG_CTL                                                                   0x98000224
#define SYS_BG_CTL_reg_addr                                                          "0x98000224"
#define SYS_BG_CTL_reg                                                               0x98000224
#define set_SYS_BG_CTL_reg(data)   (*((volatile unsigned int*) SYS_BG_CTL_reg)=data)
#define get_SYS_BG_CTL_reg   (*((volatile unsigned int*) SYS_BG_CTL_reg))
#define SYS_BG_CTL_inst_adr                                                          "0x0089"
#define SYS_BG_CTL_inst                                                              0x0089
#define SYS_BG_CTL_REG_PLL_RESERVED_shift                                            (24)
#define SYS_BG_CTL_REG_PLL_RESERVED_mask                                             (0xFF000000)
#define SYS_BG_CTL_REG_PLL_RESERVED(data)                                            (0xFF000000&((data)<<24))
#define SYS_BG_CTL_REG_PLL_RESERVED_src(data)                                        ((0xFF000000&(data))>>24)
#define SYS_BG_CTL_get_REG_PLL_RESERVED(data)                                        ((0xFF000000&(data))>>24)
#define SYS_BG_CTL_REG_LDO2V_SEL_shift                                               (9)
#define SYS_BG_CTL_REG_LDO2V_SEL_mask                                                (0x00000600)
#define SYS_BG_CTL_REG_LDO2V_SEL(data)                                               (0x00000600&((data)<<9))
#define SYS_BG_CTL_REG_LDO2V_SEL_src(data)                                           ((0x00000600&(data))>>9)
#define SYS_BG_CTL_get_REG_LDO2V_SEL(data)                                           ((0x00000600&(data))>>9)
#define SYS_BG_CTL_REG_LDO2V_POW_shift                                               (8)
#define SYS_BG_CTL_REG_LDO2V_POW_mask                                                (0x00000100)
#define SYS_BG_CTL_REG_LDO2V_POW(data)                                               (0x00000100&((data)<<8))
#define SYS_BG_CTL_REG_LDO2V_POW_src(data)                                           ((0x00000100&(data))>>8)
#define SYS_BG_CTL_get_REG_LDO2V_POW(data)                                           ((0x00000100&(data))>>8)


#define SYS_POR_DET                                                                  0x98000228
#define SYS_POR_DET_reg_addr                                                         "0x98000228"
#define SYS_POR_DET_reg                                                              0x98000228
#define set_SYS_POR_DET_reg(data)   (*((volatile unsigned int*) SYS_POR_DET_reg)=data)
#define get_SYS_POR_DET_reg   (*((volatile unsigned int*) SYS_POR_DET_reg))
#define SYS_POR_DET_inst_adr                                                         "0x008A"
#define SYS_POR_DET_inst                                                             0x008A
#define SYS_POR_DET_POR_VDD_D10_OVER_shift                                           (0)
#define SYS_POR_DET_POR_VDD_D10_OVER_mask                                            (0x00000001)
#define SYS_POR_DET_POR_VDD_D10_OVER(data)                                           (0x00000001&((data)<<0))
#define SYS_POR_DET_POR_VDD_D10_OVER_src(data)                                       ((0x00000001&(data))>>0)
#define SYS_POR_DET_get_POR_VDD_D10_OVER(data)                                       ((0x00000001&(data))>>0)


#define SYS_PLL_HDMI_LDO1                                                            0x98000230
#define SYS_PLL_HDMI_LDO1_reg_addr                                                   "0x98000230"
#define SYS_PLL_HDMI_LDO1_reg                                                        0x98000230
#define set_SYS_PLL_HDMI_LDO1_reg(data)   (*((volatile unsigned int*) SYS_PLL_HDMI_LDO1_reg)=data)
#define get_SYS_PLL_HDMI_LDO1_reg   (*((volatile unsigned int*) SYS_PLL_HDMI_LDO1_reg))
#define SYS_PLL_HDMI_LDO1_inst_adr                                                   "0x008C"
#define SYS_PLL_HDMI_LDO1_inst                                                       0x008C
#define SYS_PLL_HDMI_LDO1_REG_BYPASS_PI_shift                                        (29)
#define SYS_PLL_HDMI_LDO1_REG_BYPASS_PI_mask                                         (0x20000000)
#define SYS_PLL_HDMI_LDO1_REG_BYPASS_PI(data)                                        (0x20000000&((data)<<29))
#define SYS_PLL_HDMI_LDO1_REG_BYPASS_PI_src(data)                                    ((0x20000000&(data))>>29)
#define SYS_PLL_HDMI_LDO1_get_REG_BYPASS_PI(data)                                    ((0x20000000&(data))>>29)
#define SYS_PLL_HDMI_LDO1_REG_P2S_LDO_SEL_shift                                      (27)
#define SYS_PLL_HDMI_LDO1_REG_P2S_LDO_SEL_mask                                       (0x18000000)
#define SYS_PLL_HDMI_LDO1_REG_P2S_LDO_SEL(data)                                      (0x18000000&((data)<<27))
#define SYS_PLL_HDMI_LDO1_REG_P2S_LDO_SEL_src(data)                                  ((0x18000000&(data))>>27)
#define SYS_PLL_HDMI_LDO1_get_REG_P2S_LDO_SEL(data)                                  ((0x18000000&(data))>>27)
#define SYS_PLL_HDMI_LDO1_REG_P2S_MODE_shift                                         (25)
#define SYS_PLL_HDMI_LDO1_REG_P2S_MODE_mask                                          (0x06000000)
#define SYS_PLL_HDMI_LDO1_REG_P2S_MODE(data)                                         (0x06000000&((data)<<25))
#define SYS_PLL_HDMI_LDO1_REG_P2S_MODE_src(data)                                     ((0x06000000&(data))>>25)
#define SYS_PLL_HDMI_LDO1_get_REG_P2S_MODE(data)                                     ((0x06000000&(data))>>25)
#define SYS_PLL_HDMI_LDO1_REG_TSPC_SEL_shift                                         (24)
#define SYS_PLL_HDMI_LDO1_REG_TSPC_SEL_mask                                          (0x01000000)
#define SYS_PLL_HDMI_LDO1_REG_TSPC_SEL(data)                                         (0x01000000&((data)<<24))
#define SYS_PLL_HDMI_LDO1_REG_TSPC_SEL_src(data)                                     ((0x01000000&(data))>>24)
#define SYS_PLL_HDMI_LDO1_get_REG_TSPC_SEL(data)                                     ((0x01000000&(data))>>24)
#define SYS_PLL_HDMI_LDO1_REG_MHL_MODE_shift                                         (23)
#define SYS_PLL_HDMI_LDO1_REG_MHL_MODE_mask                                          (0x00800000)
#define SYS_PLL_HDMI_LDO1_REG_MHL_MODE(data)                                         (0x00800000&((data)<<23))
#define SYS_PLL_HDMI_LDO1_REG_MHL_MODE_src(data)                                     ((0x00800000&(data))>>23)
#define SYS_PLL_HDMI_LDO1_get_REG_MHL_MODE(data)                                     ((0x00800000&(data))>>23)
#define SYS_PLL_HDMI_LDO1_REG_HDMI_MODE_shift                                        (22)
#define SYS_PLL_HDMI_LDO1_REG_HDMI_MODE_mask                                         (0x00400000)
#define SYS_PLL_HDMI_LDO1_REG_HDMI_MODE(data)                                        (0x00400000&((data)<<22))
#define SYS_PLL_HDMI_LDO1_REG_HDMI_MODE_src(data)                                    ((0x00400000&(data))>>22)
#define SYS_PLL_HDMI_LDO1_get_REG_HDMI_MODE(data)                                    ((0x00400000&(data))>>22)
#define SYS_PLL_HDMI_LDO1_REG_HDMICK_SEL_shift                                       (21)
#define SYS_PLL_HDMI_LDO1_REG_HDMICK_SEL_mask                                        (0x00200000)
#define SYS_PLL_HDMI_LDO1_REG_HDMICK_SEL(data)                                       (0x00200000&((data)<<21))
#define SYS_PLL_HDMI_LDO1_REG_HDMICK_SEL_src(data)                                   ((0x00200000&(data))>>21)
#define SYS_PLL_HDMI_LDO1_get_REG_HDMICK_SEL(data)                                   ((0x00200000&(data))>>21)
#define SYS_PLL_HDMI_LDO1_REG_PLL_TST_POW_shift                                      (20)
#define SYS_PLL_HDMI_LDO1_REG_PLL_TST_POW_mask                                       (0x00100000)
#define SYS_PLL_HDMI_LDO1_REG_PLL_TST_POW(data)                                      (0x00100000&((data)<<20))
#define SYS_PLL_HDMI_LDO1_REG_PLL_TST_POW_src(data)                                  ((0x00100000&(data))>>20)
#define SYS_PLL_HDMI_LDO1_get_REG_PLL_TST_POW(data)                                  ((0x00100000&(data))>>20)
#define SYS_PLL_HDMI_LDO1_REG_PLL_LDO_V18_SEL_shift                                  (18)
#define SYS_PLL_HDMI_LDO1_REG_PLL_LDO_V18_SEL_mask                                   (0x000C0000)
#define SYS_PLL_HDMI_LDO1_REG_PLL_LDO_V18_SEL(data)                                  (0x000C0000&((data)<<18))
#define SYS_PLL_HDMI_LDO1_REG_PLL_LDO_V18_SEL_src(data)                              ((0x000C0000&(data))>>18)
#define SYS_PLL_HDMI_LDO1_get_REG_PLL_LDO_V18_SEL(data)                              ((0x000C0000&(data))>>18)
#define SYS_PLL_HDMI_LDO1_REG_PLL_LDO_LV_SEL_shift                                   (16)
#define SYS_PLL_HDMI_LDO1_REG_PLL_LDO_LV_SEL_mask                                    (0x00030000)
#define SYS_PLL_HDMI_LDO1_REG_PLL_LDO_LV_SEL(data)                                   (0x00030000&((data)<<16))
#define SYS_PLL_HDMI_LDO1_REG_PLL_LDO_LV_SEL_src(data)                               ((0x00030000&(data))>>16)
#define SYS_PLL_HDMI_LDO1_get_REG_PLL_LDO_LV_SEL(data)                               ((0x00030000&(data))>>16)
#define SYS_PLL_HDMI_LDO1_REG_TST_DIV_shift                                          (13)
#define SYS_PLL_HDMI_LDO1_REG_TST_DIV_mask                                           (0x0000E000)
#define SYS_PLL_HDMI_LDO1_REG_TST_DIV(data)                                          (0x0000E000&((data)<<13))
#define SYS_PLL_HDMI_LDO1_REG_TST_DIV_src(data)                                      ((0x0000E000&(data))>>13)
#define SYS_PLL_HDMI_LDO1_get_REG_TST_DIV(data)                                      ((0x0000E000&(data))>>13)
#define SYS_PLL_HDMI_LDO1_REG_PLL_RS_shift                                           (10)
#define SYS_PLL_HDMI_LDO1_REG_PLL_RS_mask                                            (0x00001C00)
#define SYS_PLL_HDMI_LDO1_REG_PLL_RS(data)                                           (0x00001C00&((data)<<10))
#define SYS_PLL_HDMI_LDO1_REG_PLL_RS_src(data)                                       ((0x00001C00&(data))>>10)
#define SYS_PLL_HDMI_LDO1_get_REG_PLL_RS(data)                                       ((0x00001C00&(data))>>10)
#define SYS_PLL_HDMI_LDO1_REG_PLL_WDSET_shift                                        (9)
#define SYS_PLL_HDMI_LDO1_REG_PLL_WDSET_mask                                         (0x00000200)
#define SYS_PLL_HDMI_LDO1_REG_PLL_WDSET(data)                                        (0x00000200&((data)<<9))
#define SYS_PLL_HDMI_LDO1_REG_PLL_WDSET_src(data)                                    ((0x00000200&(data))>>9)
#define SYS_PLL_HDMI_LDO1_get_REG_PLL_WDSET(data)                                    ((0x00000200&(data))>>9)
#define SYS_PLL_HDMI_LDO1_REG_PLL_WDRST_shift                                        (8)
#define SYS_PLL_HDMI_LDO1_REG_PLL_WDRST_mask                                         (0x00000100)
#define SYS_PLL_HDMI_LDO1_REG_PLL_WDRST(data)                                        (0x00000100&((data)<<8))
#define SYS_PLL_HDMI_LDO1_REG_PLL_WDRST_src(data)                                    ((0x00000100&(data))>>8)
#define SYS_PLL_HDMI_LDO1_get_REG_PLL_WDRST(data)                                    ((0x00000100&(data))>>8)
#define SYS_PLL_HDMI_LDO1_REG_PLL_VCOGAIN_shift                                      (7)
#define SYS_PLL_HDMI_LDO1_REG_PLL_VCOGAIN_mask                                       (0x00000080)
#define SYS_PLL_HDMI_LDO1_REG_PLL_VCOGAIN(data)                                      (0x00000080&((data)<<7))
#define SYS_PLL_HDMI_LDO1_REG_PLL_VCOGAIN_src(data)                                  ((0x00000080&(data))>>7)
#define SYS_PLL_HDMI_LDO1_get_REG_PLL_VCOGAIN(data)                                  ((0x00000080&(data))>>7)
#define SYS_PLL_HDMI_LDO1_REG_PLL_EXT_LDO_LV_shift                                   (6)
#define SYS_PLL_HDMI_LDO1_REG_PLL_EXT_LDO_LV_mask                                    (0x00000040)
#define SYS_PLL_HDMI_LDO1_REG_PLL_EXT_LDO_LV(data)                                   (0x00000040&((data)<<6))
#define SYS_PLL_HDMI_LDO1_REG_PLL_EXT_LDO_LV_src(data)                               ((0x00000040&(data))>>6)
#define SYS_PLL_HDMI_LDO1_get_REG_PLL_EXT_LDO_LV(data)                               ((0x00000040&(data))>>6)
#define SYS_PLL_HDMI_LDO1_REG_PLL_CKSEL_shift                                        (4)
#define SYS_PLL_HDMI_LDO1_REG_PLL_CKSEL_mask                                         (0x00000030)
#define SYS_PLL_HDMI_LDO1_REG_PLL_CKSEL(data)                                        (0x00000030&((data)<<4))
#define SYS_PLL_HDMI_LDO1_REG_PLL_CKSEL_src(data)                                    ((0x00000030&(data))>>4)
#define SYS_PLL_HDMI_LDO1_get_REG_PLL_CKSEL(data)                                    ((0x00000030&(data))>>4)
#define SYS_PLL_HDMI_LDO1_REG_PLL_CS_shift                                           (2)
#define SYS_PLL_HDMI_LDO1_REG_PLL_CS_mask                                            (0x0000000C)
#define SYS_PLL_HDMI_LDO1_REG_PLL_CS(data)                                           (0x0000000C&((data)<<2))
#define SYS_PLL_HDMI_LDO1_REG_PLL_CS_src(data)                                       ((0x0000000C&(data))>>2)
#define SYS_PLL_HDMI_LDO1_get_REG_PLL_CS(data)                                       ((0x0000000C&(data))>>2)
#define SYS_PLL_HDMI_LDO1_REG_PLL_CP_shift                                           (0)
#define SYS_PLL_HDMI_LDO1_REG_PLL_CP_mask                                            (0x00000003)
#define SYS_PLL_HDMI_LDO1_REG_PLL_CP(data)                                           (0x00000003&((data)<<0))
#define SYS_PLL_HDMI_LDO1_REG_PLL_CP_src(data)                                       ((0x00000003&(data))>>0)
#define SYS_PLL_HDMI_LDO1_get_REG_PLL_CP(data)                                       ((0x00000003&(data))>>0)


#define SYS_PLL_HDMI_LDO2                                                            0x98000234
#define SYS_PLL_HDMI_LDO2_reg_addr                                                   "0x98000234"
#define SYS_PLL_HDMI_LDO2_reg                                                        0x98000234
#define set_SYS_PLL_HDMI_LDO2_reg(data)   (*((volatile unsigned int*) SYS_PLL_HDMI_LDO2_reg)=data)
#define get_SYS_PLL_HDMI_LDO2_reg   (*((volatile unsigned int*) SYS_PLL_HDMI_LDO2_reg))
#define SYS_PLL_HDMI_LDO2_inst_adr                                                   "0x008D"
#define SYS_PLL_HDMI_LDO2_inst                                                       0x008D
#define SYS_PLL_HDMI_LDO2_REG_TMDS_RSELCK_shift                                      (24)
#define SYS_PLL_HDMI_LDO2_REG_TMDS_RSELCK_mask                                       (0x03000000)
#define SYS_PLL_HDMI_LDO2_REG_TMDS_RSELCK(data)                                      (0x03000000&((data)<<24))
#define SYS_PLL_HDMI_LDO2_REG_TMDS_RSELCK_src(data)                                  ((0x03000000&(data))>>24)
#define SYS_PLL_HDMI_LDO2_get_REG_TMDS_RSELCK(data)                                  ((0x03000000&(data))>>24)
#define SYS_PLL_HDMI_LDO2_REG_TMDS_RSELC_shift                                       (22)
#define SYS_PLL_HDMI_LDO2_REG_TMDS_RSELC_mask                                        (0x00C00000)
#define SYS_PLL_HDMI_LDO2_REG_TMDS_RSELC(data)                                       (0x00C00000&((data)<<22))
#define SYS_PLL_HDMI_LDO2_REG_TMDS_RSELC_src(data)                                   ((0x00C00000&(data))>>22)
#define SYS_PLL_HDMI_LDO2_get_REG_TMDS_RSELC(data)                                   ((0x00C00000&(data))>>22)
#define SYS_PLL_HDMI_LDO2_REG_TMDS_RSELB_shift                                       (20)
#define SYS_PLL_HDMI_LDO2_REG_TMDS_RSELB_mask                                        (0x00300000)
#define SYS_PLL_HDMI_LDO2_REG_TMDS_RSELB(data)                                       (0x00300000&((data)<<20))
#define SYS_PLL_HDMI_LDO2_REG_TMDS_RSELB_src(data)                                   ((0x00300000&(data))>>20)
#define SYS_PLL_HDMI_LDO2_get_REG_TMDS_RSELB(data)                                   ((0x00300000&(data))>>20)
#define SYS_PLL_HDMI_LDO2_REG_TMDS_RSELA_shift                                       (18)
#define SYS_PLL_HDMI_LDO2_REG_TMDS_RSELA_mask                                        (0x000C0000)
#define SYS_PLL_HDMI_LDO2_REG_TMDS_RSELA(data)                                       (0x000C0000&((data)<<18))
#define SYS_PLL_HDMI_LDO2_REG_TMDS_RSELA_src(data)                                   ((0x000C0000&(data))>>18)
#define SYS_PLL_HDMI_LDO2_get_REG_TMDS_RSELA(data)                                   ((0x000C0000&(data))>>18)
#define SYS_PLL_HDMI_LDO2_REG_TMDS_CSELCK_shift                                      (16)
#define SYS_PLL_HDMI_LDO2_REG_TMDS_CSELCK_mask                                       (0x00030000)
#define SYS_PLL_HDMI_LDO2_REG_TMDS_CSELCK(data)                                      (0x00030000&((data)<<16))
#define SYS_PLL_HDMI_LDO2_REG_TMDS_CSELCK_src(data)                                  ((0x00030000&(data))>>16)
#define SYS_PLL_HDMI_LDO2_get_REG_TMDS_CSELCK(data)                                  ((0x00030000&(data))>>16)
#define SYS_PLL_HDMI_LDO2_REG_TMDS_CSELC_shift                                       (14)
#define SYS_PLL_HDMI_LDO2_REG_TMDS_CSELC_mask                                        (0x0000C000)
#define SYS_PLL_HDMI_LDO2_REG_TMDS_CSELC(data)                                       (0x0000C000&((data)<<14))
#define SYS_PLL_HDMI_LDO2_REG_TMDS_CSELC_src(data)                                   ((0x0000C000&(data))>>14)
#define SYS_PLL_HDMI_LDO2_get_REG_TMDS_CSELC(data)                                   ((0x0000C000&(data))>>14)
#define SYS_PLL_HDMI_LDO2_REG_TMDS_CSELB_shift                                       (12)
#define SYS_PLL_HDMI_LDO2_REG_TMDS_CSELB_mask                                        (0x00003000)
#define SYS_PLL_HDMI_LDO2_REG_TMDS_CSELB(data)                                       (0x00003000&((data)<<12))
#define SYS_PLL_HDMI_LDO2_REG_TMDS_CSELB_src(data)                                   ((0x00003000&(data))>>12)
#define SYS_PLL_HDMI_LDO2_get_REG_TMDS_CSELB(data)                                   ((0x00003000&(data))>>12)
#define SYS_PLL_HDMI_LDO2_REG_TMDS_CSELA_shift                                       (10)
#define SYS_PLL_HDMI_LDO2_REG_TMDS_CSELA_mask                                        (0x00000C00)
#define SYS_PLL_HDMI_LDO2_REG_TMDS_CSELA(data)                                       (0x00000C00&((data)<<10))
#define SYS_PLL_HDMI_LDO2_REG_TMDS_CSELA_src(data)                                   ((0x00000C00&(data))>>10)
#define SYS_PLL_HDMI_LDO2_get_REG_TMDS_CSELA(data)                                   ((0x00000C00&(data))>>10)
#define SYS_PLL_HDMI_LDO2_REG_TMDS_POWMHLCK_B_shift                                  (9)
#define SYS_PLL_HDMI_LDO2_REG_TMDS_POWMHLCK_B_mask                                   (0x00000200)
#define SYS_PLL_HDMI_LDO2_REG_TMDS_POWMHLCK_B(data)                                  (0x00000200&((data)<<9))
#define SYS_PLL_HDMI_LDO2_REG_TMDS_POWMHLCK_B_src(data)                              ((0x00000200&(data))>>9)
#define SYS_PLL_HDMI_LDO2_get_REG_TMDS_POWMHLCK_B(data)                              ((0x00000200&(data))>>9)
#define SYS_PLL_HDMI_LDO2_REG_TMDS_POWMHLCK_A_shift                                  (8)
#define SYS_PLL_HDMI_LDO2_REG_TMDS_POWMHLCK_A_mask                                   (0x00000100)
#define SYS_PLL_HDMI_LDO2_REG_TMDS_POWMHLCK_A(data)                                  (0x00000100&((data)<<8))
#define SYS_PLL_HDMI_LDO2_REG_TMDS_POWMHLCK_A_src(data)                              ((0x00000100&(data))>>8)
#define SYS_PLL_HDMI_LDO2_get_REG_TMDS_POWMHLCK_A(data)                              ((0x00000100&(data))>>8)
#define SYS_PLL_HDMI_LDO2_REG_TMDS_POWCK_shift                                       (7)
#define SYS_PLL_HDMI_LDO2_REG_TMDS_POWCK_mask                                        (0x00000080)
#define SYS_PLL_HDMI_LDO2_REG_TMDS_POWCK(data)                                       (0x00000080&((data)<<7))
#define SYS_PLL_HDMI_LDO2_REG_TMDS_POWCK_src(data)                                   ((0x00000080&(data))>>7)
#define SYS_PLL_HDMI_LDO2_get_REG_TMDS_POWCK(data)                                   ((0x00000080&(data))>>7)
#define SYS_PLL_HDMI_LDO2_REG_TMDS_POWC_shift                                        (6)
#define SYS_PLL_HDMI_LDO2_REG_TMDS_POWC_mask                                         (0x00000040)
#define SYS_PLL_HDMI_LDO2_REG_TMDS_POWC(data)                                        (0x00000040&((data)<<6))
#define SYS_PLL_HDMI_LDO2_REG_TMDS_POWC_src(data)                                    ((0x00000040&(data))>>6)
#define SYS_PLL_HDMI_LDO2_get_REG_TMDS_POWC(data)                                    ((0x00000040&(data))>>6)
#define SYS_PLL_HDMI_LDO2_REG_TMDS_POWB_shift                                        (5)
#define SYS_PLL_HDMI_LDO2_REG_TMDS_POWB_mask                                         (0x00000020)
#define SYS_PLL_HDMI_LDO2_REG_TMDS_POWB(data)                                        (0x00000020&((data)<<5))
#define SYS_PLL_HDMI_LDO2_REG_TMDS_POWB_src(data)                                    ((0x00000020&(data))>>5)
#define SYS_PLL_HDMI_LDO2_get_REG_TMDS_POWB(data)                                    ((0x00000020&(data))>>5)
#define SYS_PLL_HDMI_LDO2_REG_TMDS_POWA_shift                                        (4)
#define SYS_PLL_HDMI_LDO2_REG_TMDS_POWA_mask                                         (0x00000010)
#define SYS_PLL_HDMI_LDO2_REG_TMDS_POWA(data)                                        (0x00000010&((data)<<4))
#define SYS_PLL_HDMI_LDO2_REG_TMDS_POWA_src(data)                                    ((0x00000010&(data))>>4)
#define SYS_PLL_HDMI_LDO2_get_REG_TMDS_POWA(data)                                    ((0x00000010&(data))>>4)
#define SYS_PLL_HDMI_LDO2_REG_TMDS_EMCK_shift                                        (3)
#define SYS_PLL_HDMI_LDO2_REG_TMDS_EMCK_mask                                         (0x00000008)
#define SYS_PLL_HDMI_LDO2_REG_TMDS_EMCK(data)                                        (0x00000008&((data)<<3))
#define SYS_PLL_HDMI_LDO2_REG_TMDS_EMCK_src(data)                                    ((0x00000008&(data))>>3)
#define SYS_PLL_HDMI_LDO2_get_REG_TMDS_EMCK(data)                                    ((0x00000008&(data))>>3)
#define SYS_PLL_HDMI_LDO2_REG_TMDS_EMC_shift                                         (2)
#define SYS_PLL_HDMI_LDO2_REG_TMDS_EMC_mask                                          (0x00000004)
#define SYS_PLL_HDMI_LDO2_REG_TMDS_EMC(data)                                         (0x00000004&((data)<<2))
#define SYS_PLL_HDMI_LDO2_REG_TMDS_EMC_src(data)                                     ((0x00000004&(data))>>2)
#define SYS_PLL_HDMI_LDO2_get_REG_TMDS_EMC(data)                                     ((0x00000004&(data))>>2)
#define SYS_PLL_HDMI_LDO2_REG_TMDS_EMB_shift                                         (1)
#define SYS_PLL_HDMI_LDO2_REG_TMDS_EMB_mask                                          (0x00000002)
#define SYS_PLL_HDMI_LDO2_REG_TMDS_EMB(data)                                         (0x00000002&((data)<<1))
#define SYS_PLL_HDMI_LDO2_REG_TMDS_EMB_src(data)                                     ((0x00000002&(data))>>1)
#define SYS_PLL_HDMI_LDO2_get_REG_TMDS_EMB(data)                                     ((0x00000002&(data))>>1)
#define SYS_PLL_HDMI_LDO2_REG_TMDS_EMA_shift                                         (0)
#define SYS_PLL_HDMI_LDO2_REG_TMDS_EMA_mask                                          (0x00000001)
#define SYS_PLL_HDMI_LDO2_REG_TMDS_EMA(data)                                         (0x00000001&((data)<<0))
#define SYS_PLL_HDMI_LDO2_REG_TMDS_EMA_src(data)                                     ((0x00000001&(data))>>0)
#define SYS_PLL_HDMI_LDO2_get_REG_TMDS_EMA(data)                                     ((0x00000001&(data))>>0)


#define SYS_PLL_HDMI_LDO3                                                            0x98000238
#define SYS_PLL_HDMI_LDO3_reg_addr                                                   "0x98000238"
#define SYS_PLL_HDMI_LDO3_reg                                                        0x98000238
#define set_SYS_PLL_HDMI_LDO3_reg(data)   (*((volatile unsigned int*) SYS_PLL_HDMI_LDO3_reg)=data)
#define get_SYS_PLL_HDMI_LDO3_reg   (*((volatile unsigned int*) SYS_PLL_HDMI_LDO3_reg))
#define SYS_PLL_HDMI_LDO3_inst_adr                                                   "0x008E"
#define SYS_PLL_HDMI_LDO3_inst                                                       0x008E
#define SYS_PLL_HDMI_LDO3_REG_PLL_CKIN_SEL_shift                                     (24)
#define SYS_PLL_HDMI_LDO3_REG_PLL_CKIN_SEL_mask                                      (0x03000000)
#define SYS_PLL_HDMI_LDO3_REG_PLL_CKIN_SEL(data)                                     (0x03000000&((data)<<24))
#define SYS_PLL_HDMI_LDO3_REG_PLL_CKIN_SEL_src(data)                                 ((0x03000000&(data))>>24)
#define SYS_PLL_HDMI_LDO3_get_REG_PLL_CKIN_SEL(data)                                 ((0x03000000&(data))>>24)
#define SYS_PLL_HDMI_LDO3_REG_PLL_TSPC_SEL_shift                                     (23)
#define SYS_PLL_HDMI_LDO3_REG_PLL_TSPC_SEL_mask                                      (0x00800000)
#define SYS_PLL_HDMI_LDO3_REG_PLL_TSPC_SEL(data)                                     (0x00800000&((data)<<23))
#define SYS_PLL_HDMI_LDO3_REG_PLL_TSPC_SEL_src(data)                                 ((0x00800000&(data))>>23)
#define SYS_PLL_HDMI_LDO3_get_REG_PLL_TSPC_SEL(data)                                 ((0x00800000&(data))>>23)
#define SYS_PLL_HDMI_LDO3_REG_PCR_27M_SEL_shift                                      (22)
#define SYS_PLL_HDMI_LDO3_REG_PCR_27M_SEL_mask                                       (0x00400000)
#define SYS_PLL_HDMI_LDO3_REG_PCR_27M_SEL(data)                                      (0x00400000&((data)<<22))
#define SYS_PLL_HDMI_LDO3_REG_PCR_27M_SEL_src(data)                                  ((0x00400000&(data))>>22)
#define SYS_PLL_HDMI_LDO3_get_REG_PCR_27M_SEL(data)                                  ((0x00400000&(data))>>22)
#define SYS_PLL_HDMI_LDO3_REG_TMDS_IDRVCK_shift                                      (19)
#define SYS_PLL_HDMI_LDO3_REG_TMDS_IDRVCK_mask                                       (0x00380000)
#define SYS_PLL_HDMI_LDO3_REG_TMDS_IDRVCK(data)                                      (0x00380000&((data)<<19))
#define SYS_PLL_HDMI_LDO3_REG_TMDS_IDRVCK_src(data)                                  ((0x00380000&(data))>>19)
#define SYS_PLL_HDMI_LDO3_get_REG_TMDS_IDRVCK(data)                                  ((0x00380000&(data))>>19)
#define SYS_PLL_HDMI_LDO3_REG_TMDS_IDRVC_shift                                       (16)
#define SYS_PLL_HDMI_LDO3_REG_TMDS_IDRVC_mask                                        (0x00070000)
#define SYS_PLL_HDMI_LDO3_REG_TMDS_IDRVC(data)                                       (0x00070000&((data)<<16))
#define SYS_PLL_HDMI_LDO3_REG_TMDS_IDRVC_src(data)                                   ((0x00070000&(data))>>16)
#define SYS_PLL_HDMI_LDO3_get_REG_TMDS_IDRVC(data)                                   ((0x00070000&(data))>>16)
#define SYS_PLL_HDMI_LDO3_REG_TMDS_IDRVB_shift                                       (13)
#define SYS_PLL_HDMI_LDO3_REG_TMDS_IDRVB_mask                                        (0x0000E000)
#define SYS_PLL_HDMI_LDO3_REG_TMDS_IDRVB(data)                                       (0x0000E000&((data)<<13))
#define SYS_PLL_HDMI_LDO3_REG_TMDS_IDRVB_src(data)                                   ((0x0000E000&(data))>>13)
#define SYS_PLL_HDMI_LDO3_get_REG_TMDS_IDRVB(data)                                   ((0x0000E000&(data))>>13)
#define SYS_PLL_HDMI_LDO3_REG_TMDS_IDRVA_shift                                       (10)
#define SYS_PLL_HDMI_LDO3_REG_TMDS_IDRVA_mask                                        (0x00001C00)
#define SYS_PLL_HDMI_LDO3_REG_TMDS_IDRVA(data)                                       (0x00001C00&((data)<<10))
#define SYS_PLL_HDMI_LDO3_REG_TMDS_IDRVA_src(data)                                   ((0x00001C00&(data))>>10)
#define SYS_PLL_HDMI_LDO3_get_REG_TMDS_IDRVA(data)                                   ((0x00001C00&(data))>>10)
#define SYS_PLL_HDMI_LDO3_REG_TMDS_SRMHLCK_shift                                     (8)
#define SYS_PLL_HDMI_LDO3_REG_TMDS_SRMHLCK_mask                                      (0x00000300)
#define SYS_PLL_HDMI_LDO3_REG_TMDS_SRMHLCK(data)                                     (0x00000300&((data)<<8))
#define SYS_PLL_HDMI_LDO3_REG_TMDS_SRMHLCK_src(data)                                 ((0x00000300&(data))>>8)
#define SYS_PLL_HDMI_LDO3_get_REG_TMDS_SRMHLCK(data)                                 ((0x00000300&(data))>>8)
#define SYS_PLL_HDMI_LDO3_REG_TMDS_SRCK_shift                                        (6)
#define SYS_PLL_HDMI_LDO3_REG_TMDS_SRCK_mask                                         (0x000000C0)
#define SYS_PLL_HDMI_LDO3_REG_TMDS_SRCK(data)                                        (0x000000C0&((data)<<6))
#define SYS_PLL_HDMI_LDO3_REG_TMDS_SRCK_src(data)                                    ((0x000000C0&(data))>>6)
#define SYS_PLL_HDMI_LDO3_get_REG_TMDS_SRCK(data)                                    ((0x000000C0&(data))>>6)
#define SYS_PLL_HDMI_LDO3_REG_TMDS_SRC_shift                                         (4)
#define SYS_PLL_HDMI_LDO3_REG_TMDS_SRC_mask                                          (0x00000030)
#define SYS_PLL_HDMI_LDO3_REG_TMDS_SRC(data)                                         (0x00000030&((data)<<4))
#define SYS_PLL_HDMI_LDO3_REG_TMDS_SRC_src(data)                                     ((0x00000030&(data))>>4)
#define SYS_PLL_HDMI_LDO3_get_REG_TMDS_SRC(data)                                     ((0x00000030&(data))>>4)
#define SYS_PLL_HDMI_LDO3_REG_TMDS_SRB_shift                                         (2)
#define SYS_PLL_HDMI_LDO3_REG_TMDS_SRB_mask                                          (0x0000000C)
#define SYS_PLL_HDMI_LDO3_REG_TMDS_SRB(data)                                         (0x0000000C&((data)<<2))
#define SYS_PLL_HDMI_LDO3_REG_TMDS_SRB_src(data)                                     ((0x0000000C&(data))>>2)
#define SYS_PLL_HDMI_LDO3_get_REG_TMDS_SRB(data)                                     ((0x0000000C&(data))>>2)
#define SYS_PLL_HDMI_LDO3_REG_TMDS_SRA_shift                                         (0)
#define SYS_PLL_HDMI_LDO3_REG_TMDS_SRA_mask                                          (0x00000003)
#define SYS_PLL_HDMI_LDO3_REG_TMDS_SRA(data)                                         (0x00000003&((data)<<0))
#define SYS_PLL_HDMI_LDO3_REG_TMDS_SRA_src(data)                                     ((0x00000003&(data))>>0)
#define SYS_PLL_HDMI_LDO3_get_REG_TMDS_SRA(data)                                     ((0x00000003&(data))>>0)


#define SYS_PLL_HDMI_LDO4                                                            0x9800023c
#define SYS_PLL_HDMI_LDO4_reg_addr                                                   "0x9800023C"
#define SYS_PLL_HDMI_LDO4_reg                                                        0x9800023C
#define set_SYS_PLL_HDMI_LDO4_reg(data)   (*((volatile unsigned int*) SYS_PLL_HDMI_LDO4_reg)=data)
#define get_SYS_PLL_HDMI_LDO4_reg   (*((volatile unsigned int*) SYS_PLL_HDMI_LDO4_reg))
#define SYS_PLL_HDMI_LDO4_inst_adr                                                   "0x008F"
#define SYS_PLL_HDMI_LDO4_inst                                                       0x008F
#define SYS_PLL_HDMI_LDO4_REG_PLLDISP_DDSEN_shift                                    (29)
#define SYS_PLL_HDMI_LDO4_REG_PLLDISP_DDSEN_mask                                     (0x20000000)
#define SYS_PLL_HDMI_LDO4_REG_PLLDISP_DDSEN(data)                                    (0x20000000&((data)<<29))
#define SYS_PLL_HDMI_LDO4_REG_PLLDISP_DDSEN_src(data)                                ((0x20000000&(data))>>29)
#define SYS_PLL_HDMI_LDO4_get_REG_PLLDISP_DDSEN(data)                                ((0x20000000&(data))>>29)
#define SYS_PLL_HDMI_LDO4_REG_PLLDISP_CS_shift                                       (27)
#define SYS_PLL_HDMI_LDO4_REG_PLLDISP_CS_mask                                        (0x18000000)
#define SYS_PLL_HDMI_LDO4_REG_PLLDISP_CS(data)                                       (0x18000000&((data)<<27))
#define SYS_PLL_HDMI_LDO4_REG_PLLDISP_CS_src(data)                                   ((0x18000000&(data))>>27)
#define SYS_PLL_HDMI_LDO4_get_REG_PLLDISP_CS(data)                                   ((0x18000000&(data))>>27)
#define SYS_PLL_HDMI_LDO4_REG_PLLDISP_CP_shift                                       (25)
#define SYS_PLL_HDMI_LDO4_REG_PLLDISP_CP_mask                                        (0x06000000)
#define SYS_PLL_HDMI_LDO4_REG_PLLDISP_CP(data)                                       (0x06000000&((data)<<25))
#define SYS_PLL_HDMI_LDO4_REG_PLLDISP_CP_src(data)                                   ((0x06000000&(data))>>25)
#define SYS_PLL_HDMI_LDO4_get_REG_PLLDISP_CP(data)                                   ((0x06000000&(data))>>25)
#define SYS_PLL_HDMI_LDO4_REG_PLLDISP_C3_shift                                       (23)
#define SYS_PLL_HDMI_LDO4_REG_PLLDISP_C3_mask                                        (0x01800000)
#define SYS_PLL_HDMI_LDO4_REG_PLLDISP_C3(data)                                       (0x01800000&((data)<<23))
#define SYS_PLL_HDMI_LDO4_REG_PLLDISP_C3_src(data)                                   ((0x01800000&(data))>>23)
#define SYS_PLL_HDMI_LDO4_get_REG_PLLDISP_C3(data)                                   ((0x01800000&(data))>>23)
#define SYS_PLL_HDMI_LDO4_REG_TEST_LDO_SEL_shift                                     (21)
#define SYS_PLL_HDMI_LDO4_REG_TEST_LDO_SEL_mask                                      (0x00600000)
#define SYS_PLL_HDMI_LDO4_REG_TEST_LDO_SEL(data)                                     (0x00600000&((data)<<21))
#define SYS_PLL_HDMI_LDO4_REG_TEST_LDO_SEL_src(data)                                 ((0x00600000&(data))>>21)
#define SYS_PLL_HDMI_LDO4_get_REG_TEST_LDO_SEL(data)                                 ((0x00600000&(data))>>21)
#define SYS_PLL_HDMI_LDO4_REG_TESTSIG_SEL_shift                                      (19)
#define SYS_PLL_HDMI_LDO4_REG_TESTSIG_SEL_mask                                       (0x00180000)
#define SYS_PLL_HDMI_LDO4_REG_TESTSIG_SEL(data)                                      (0x00180000&((data)<<19))
#define SYS_PLL_HDMI_LDO4_REG_TESTSIG_SEL_src(data)                                  ((0x00180000&(data))>>19)
#define SYS_PLL_HDMI_LDO4_get_REG_TESTSIG_SEL(data)                                  ((0x00180000&(data))>>19)
#define SYS_PLL_HDMI_LDO4_REG_PLL_IP_shift                                           (15)
#define SYS_PLL_HDMI_LDO4_REG_PLL_IP_mask                                            (0x00078000)
#define SYS_PLL_HDMI_LDO4_REG_PLL_IP(data)                                           (0x00078000&((data)<<15))
#define SYS_PLL_HDMI_LDO4_REG_PLL_IP_src(data)                                       ((0x00078000&(data))>>15)
#define SYS_PLL_HDMI_LDO4_get_REG_PLL_IP(data)                                       ((0x00078000&(data))>>15)
#define SYS_PLL_HDMI_LDO4_REG_TMDS_IMHLCK_shift                                      (12)
#define SYS_PLL_HDMI_LDO4_REG_TMDS_IMHLCK_mask                                       (0x00007000)
#define SYS_PLL_HDMI_LDO4_REG_TMDS_IMHLCK(data)                                      (0x00007000&((data)<<12))
#define SYS_PLL_HDMI_LDO4_REG_TMDS_IMHLCK_src(data)                                  ((0x00007000&(data))>>12)
#define SYS_PLL_HDMI_LDO4_get_REG_TMDS_IMHLCK(data)                                  ((0x00007000&(data))>>12)
#define SYS_PLL_HDMI_LDO4_REG_TMDS_IEMCK_shift                                       (9)
#define SYS_PLL_HDMI_LDO4_REG_TMDS_IEMCK_mask                                        (0x00000E00)
#define SYS_PLL_HDMI_LDO4_REG_TMDS_IEMCK(data)                                       (0x00000E00&((data)<<9))
#define SYS_PLL_HDMI_LDO4_REG_TMDS_IEMCK_src(data)                                   ((0x00000E00&(data))>>9)
#define SYS_PLL_HDMI_LDO4_get_REG_TMDS_IEMCK(data)                                   ((0x00000E00&(data))>>9)
#define SYS_PLL_HDMI_LDO4_REG_TMDS_IEMC_shift                                        (6)
#define SYS_PLL_HDMI_LDO4_REG_TMDS_IEMC_mask                                         (0x000001C0)
#define SYS_PLL_HDMI_LDO4_REG_TMDS_IEMC(data)                                        (0x000001C0&((data)<<6))
#define SYS_PLL_HDMI_LDO4_REG_TMDS_IEMC_src(data)                                    ((0x000001C0&(data))>>6)
#define SYS_PLL_HDMI_LDO4_get_REG_TMDS_IEMC(data)                                    ((0x000001C0&(data))>>6)
#define SYS_PLL_HDMI_LDO4_REG_TMDS_IEMB_shift                                        (3)
#define SYS_PLL_HDMI_LDO4_REG_TMDS_IEMB_mask                                         (0x00000038)
#define SYS_PLL_HDMI_LDO4_REG_TMDS_IEMB(data)                                        (0x00000038&((data)<<3))
#define SYS_PLL_HDMI_LDO4_REG_TMDS_IEMB_src(data)                                    ((0x00000038&(data))>>3)
#define SYS_PLL_HDMI_LDO4_get_REG_TMDS_IEMB(data)                                    ((0x00000038&(data))>>3)
#define SYS_PLL_HDMI_LDO4_REG_TMDS_IEMA_shift                                        (0)
#define SYS_PLL_HDMI_LDO4_REG_TMDS_IEMA_mask                                         (0x00000007)
#define SYS_PLL_HDMI_LDO4_REG_TMDS_IEMA(data)                                        (0x00000007&((data)<<0))
#define SYS_PLL_HDMI_LDO4_REG_TMDS_IEMA_src(data)                                    ((0x00000007&(data))>>0)
#define SYS_PLL_HDMI_LDO4_get_REG_TMDS_IEMA(data)                                    ((0x00000007&(data))>>0)


#define SYS_PLL_HDMI_LDO5                                                            0x98000240
#define SYS_PLL_HDMI_LDO5_reg_addr                                                   "0x98000240"
#define SYS_PLL_HDMI_LDO5_reg                                                        0x98000240
#define set_SYS_PLL_HDMI_LDO5_reg(data)   (*((volatile unsigned int*) SYS_PLL_HDMI_LDO5_reg)=data)
#define get_SYS_PLL_HDMI_LDO5_reg   (*((volatile unsigned int*) SYS_PLL_HDMI_LDO5_reg))
#define SYS_PLL_HDMI_LDO5_inst_adr                                                   "0x0090"
#define SYS_PLL_HDMI_LDO5_inst                                                       0x0090
#define SYS_PLL_HDMI_LDO5_REG_HDMITX_RESERVE_shift                                   (16)
#define SYS_PLL_HDMI_LDO5_REG_HDMITX_RESERVE_mask                                    (0xFFFF0000)
#define SYS_PLL_HDMI_LDO5_REG_HDMITX_RESERVE(data)                                   (0xFFFF0000&((data)<<16))
#define SYS_PLL_HDMI_LDO5_REG_HDMITX_RESERVE_src(data)                               ((0xFFFF0000&(data))>>16)
#define SYS_PLL_HDMI_LDO5_get_REG_HDMITX_RESERVE(data)                               ((0xFFFF0000&(data))>>16)
#define SYS_PLL_HDMI_LDO5_REG_PLLDISP_LDOSEL_shift                                   (14)
#define SYS_PLL_HDMI_LDO5_REG_PLLDISP_LDOSEL_mask                                    (0x0000C000)
#define SYS_PLL_HDMI_LDO5_REG_PLLDISP_LDOSEL(data)                                   (0x0000C000&((data)<<14))
#define SYS_PLL_HDMI_LDO5_REG_PLLDISP_LDOSEL_src(data)                               ((0x0000C000&(data))>>14)
#define SYS_PLL_HDMI_LDO5_get_REG_PLLDISP_LDOSEL(data)                               ((0x0000C000&(data))>>14)
#define SYS_PLL_HDMI_LDO5_REG_PLLDISP_SSC_ENL_shift                                  (13)
#define SYS_PLL_HDMI_LDO5_REG_PLLDISP_SSC_ENL_mask                                   (0x00002000)
#define SYS_PLL_HDMI_LDO5_REG_PLLDISP_SSC_ENL(data)                                  (0x00002000&((data)<<13))
#define SYS_PLL_HDMI_LDO5_REG_PLLDISP_SSC_ENL_src(data)                              ((0x00002000&(data))>>13)
#define SYS_PLL_HDMI_LDO5_get_REG_PLLDISP_SSC_ENL(data)                              ((0x00002000&(data))>>13)
#define SYS_PLL_HDMI_LDO5_REG_PLLDISP_WDMODE_shift                                   (11)
#define SYS_PLL_HDMI_LDO5_REG_PLLDISP_WDMODE_mask                                    (0x00001800)
#define SYS_PLL_HDMI_LDO5_REG_PLLDISP_WDMODE(data)                                   (0x00001800&((data)<<11))
#define SYS_PLL_HDMI_LDO5_REG_PLLDISP_WDMODE_src(data)                               ((0x00001800&(data))>>11)
#define SYS_PLL_HDMI_LDO5_get_REG_PLLDISP_WDMODE(data)                               ((0x00001800&(data))>>11)
#define SYS_PLL_HDMI_LDO5_REG_PLLDISP_RS_shift                                       (8)
#define SYS_PLL_HDMI_LDO5_REG_PLLDISP_RS_mask                                        (0x00000700)
#define SYS_PLL_HDMI_LDO5_REG_PLLDISP_RS(data)                                       (0x00000700&((data)<<8))
#define SYS_PLL_HDMI_LDO5_REG_PLLDISP_RS_src(data)                                   ((0x00000700&(data))>>8)
#define SYS_PLL_HDMI_LDO5_get_REG_PLLDISP_RS(data)                                   ((0x00000700&(data))>>8)
#define SYS_PLL_HDMI_LDO5_REG_PLLDISP_R3_shift                                       (5)
#define SYS_PLL_HDMI_LDO5_REG_PLLDISP_R3_mask                                        (0x000000E0)
#define SYS_PLL_HDMI_LDO5_REG_PLLDISP_R3(data)                                       (0x000000E0&((data)<<5))
#define SYS_PLL_HDMI_LDO5_REG_PLLDISP_R3_src(data)                                   ((0x000000E0&(data))>>5)
#define SYS_PLL_HDMI_LDO5_get_REG_PLLDISP_R3(data)                                   ((0x000000E0&(data))>>5)
#define SYS_PLL_HDMI_LDO5_REG_PLLDISP_PSTST_shift                                    (4)
#define SYS_PLL_HDMI_LDO5_REG_PLLDISP_PSTST_mask                                     (0x00000010)
#define SYS_PLL_HDMI_LDO5_REG_PLLDISP_PSTST(data)                                    (0x00000010&((data)<<4))
#define SYS_PLL_HDMI_LDO5_REG_PLLDISP_PSTST_src(data)                                ((0x00000010&(data))>>4)
#define SYS_PLL_HDMI_LDO5_get_REG_PLLDISP_PSTST(data)                                ((0x00000010&(data))>>4)
#define SYS_PLL_HDMI_LDO5_REG_PLLDISP_IP_shift                                       (0)
#define SYS_PLL_HDMI_LDO5_REG_PLLDISP_IP_mask                                        (0x0000000F)
#define SYS_PLL_HDMI_LDO5_REG_PLLDISP_IP(data)                                       (0x0000000F&((data)<<0))
#define SYS_PLL_HDMI_LDO5_REG_PLLDISP_IP_src(data)                                   ((0x0000000F&(data))>>0)
#define SYS_PLL_HDMI_LDO5_get_REG_PLLDISP_IP(data)                                   ((0x0000000F&(data))>>0)


#define SYS_PLL_EDP1                                                                 0x98000248
#define SYS_PLL_EDP1_reg_addr                                                        "0x98000248"
#define SYS_PLL_EDP1_reg                                                             0x98000248
#define set_SYS_PLL_EDP1_reg(data)   (*((volatile unsigned int*) SYS_PLL_EDP1_reg)=data)
#define get_SYS_PLL_EDP1_reg   (*((volatile unsigned int*) SYS_PLL_EDP1_reg))
#define SYS_PLL_EDP1_inst_adr                                                        "0x0092"
#define SYS_PLL_EDP1_inst                                                            0x0092
#define SYS_PLL_EDP1_REG_EDPPLL_LDOPOW_shift                                         (31)
#define SYS_PLL_EDP1_REG_EDPPLL_LDOPOW_mask                                          (0x80000000)
#define SYS_PLL_EDP1_REG_EDPPLL_LDOPOW(data)                                         (0x80000000&((data)<<31))
#define SYS_PLL_EDP1_REG_EDPPLL_LDOPOW_src(data)                                     ((0x80000000&(data))>>31)
#define SYS_PLL_EDP1_get_REG_EDPPLL_LDOPOW(data)                                     ((0x80000000&(data))>>31)
#define SYS_PLL_EDP1_REG_EDPPLL_LDOSEL_shift                                         (28)
#define SYS_PLL_EDP1_REG_EDPPLL_LDOSEL_mask                                          (0x30000000)
#define SYS_PLL_EDP1_REG_EDPPLL_LDOSEL(data)                                         (0x30000000&((data)<<28))
#define SYS_PLL_EDP1_REG_EDPPLL_LDOSEL_src(data)                                     ((0x30000000&(data))>>28)
#define SYS_PLL_EDP1_get_REG_EDPPLL_LDOSEL(data)                                     ((0x30000000&(data))>>28)
#define SYS_PLL_EDP1_REG_EDPPLL_LDOV10POW_shift                                      (27)
#define SYS_PLL_EDP1_REG_EDPPLL_LDOV10POW_mask                                       (0x08000000)
#define SYS_PLL_EDP1_REG_EDPPLL_LDOV10POW(data)                                      (0x08000000&((data)<<27))
#define SYS_PLL_EDP1_REG_EDPPLL_LDOV10POW_src(data)                                  ((0x08000000&(data))>>27)
#define SYS_PLL_EDP1_get_REG_EDPPLL_LDOV10POW(data)                                  ((0x08000000&(data))>>27)
#define SYS_PLL_EDP1_REG_EDPPLL_LDOV10SEL_shift                                      (24)
#define SYS_PLL_EDP1_REG_EDPPLL_LDOV10SEL_mask                                       (0x03000000)
#define SYS_PLL_EDP1_REG_EDPPLL_LDOV10SEL(data)                                      (0x03000000&((data)<<24))
#define SYS_PLL_EDP1_REG_EDPPLL_LDOV10SEL_src(data)                                  ((0x03000000&(data))>>24)
#define SYS_PLL_EDP1_get_REG_EDPPLL_LDOV10SEL(data)                                  ((0x03000000&(data))>>24)
#define SYS_PLL_EDP1_REG_EDPPLL_CS_shift                                             (20)
#define SYS_PLL_EDP1_REG_EDPPLL_CS_mask                                              (0x00300000)
#define SYS_PLL_EDP1_REG_EDPPLL_CS(data)                                             (0x00300000&((data)<<20))
#define SYS_PLL_EDP1_REG_EDPPLL_CS_src(data)                                         ((0x00300000&(data))>>20)
#define SYS_PLL_EDP1_get_REG_EDPPLL_CS(data)                                         ((0x00300000&(data))>>20)
#define SYS_PLL_EDP1_REG_EDPPLL_RS_shift                                             (16)
#define SYS_PLL_EDP1_REG_EDPPLL_RS_mask                                              (0x00070000)
#define SYS_PLL_EDP1_REG_EDPPLL_RS(data)                                             (0x00070000&((data)<<16))
#define SYS_PLL_EDP1_REG_EDPPLL_RS_src(data)                                         ((0x00070000&(data))>>16)
#define SYS_PLL_EDP1_get_REG_EDPPLL_RS(data)                                         ((0x00070000&(data))>>16)
#define SYS_PLL_EDP1_REG_EDPPLL_CP_shift                                             (15)
#define SYS_PLL_EDP1_REG_EDPPLL_CP_mask                                              (0x00008000)
#define SYS_PLL_EDP1_REG_EDPPLL_CP(data)                                             (0x00008000&((data)<<15))
#define SYS_PLL_EDP1_REG_EDPPLL_CP_src(data)                                         ((0x00008000&(data))>>15)
#define SYS_PLL_EDP1_get_REG_EDPPLL_CP(data)                                         ((0x00008000&(data))>>15)
#define SYS_PLL_EDP1_REG_EDPPLL_IP_shift                                             (12)
#define SYS_PLL_EDP1_REG_EDPPLL_IP_mask                                              (0x00007000)
#define SYS_PLL_EDP1_REG_EDPPLL_IP(data)                                             (0x00007000&((data)<<12))
#define SYS_PLL_EDP1_REG_EDPPLL_IP_src(data)                                         ((0x00007000&(data))>>12)
#define SYS_PLL_EDP1_get_REG_EDPPLL_IP(data)                                         ((0x00007000&(data))>>12)
#define SYS_PLL_EDP1_REG_EDPPLL_DIV10X_shift                                         (11)
#define SYS_PLL_EDP1_REG_EDPPLL_DIV10X_mask                                          (0x00000800)
#define SYS_PLL_EDP1_REG_EDPPLL_DIV10X(data)                                         (0x00000800&((data)<<11))
#define SYS_PLL_EDP1_REG_EDPPLL_DIV10X_src(data)                                     ((0x00000800&(data))>>11)
#define SYS_PLL_EDP1_get_REG_EDPPLL_DIV10X(data)                                     ((0x00000800&(data))>>11)
#define SYS_PLL_EDP1_REG_EDPPLL_WDRST_shift                                          (9)
#define SYS_PLL_EDP1_REG_EDPPLL_WDRST_mask                                           (0x00000200)
#define SYS_PLL_EDP1_REG_EDPPLL_WDRST(data)                                          (0x00000200&((data)<<9))
#define SYS_PLL_EDP1_REG_EDPPLL_WDRST_src(data)                                      ((0x00000200&(data))>>9)
#define SYS_PLL_EDP1_get_REG_EDPPLL_WDRST(data)                                      ((0x00000200&(data))>>9)
#define SYS_PLL_EDP1_REG_EDPPLL_WDSET_shift                                          (8)
#define SYS_PLL_EDP1_REG_EDPPLL_WDSET_mask                                           (0x00000100)
#define SYS_PLL_EDP1_REG_EDPPLL_WDSET(data)                                          (0x00000100&((data)<<8))
#define SYS_PLL_EDP1_REG_EDPPLL_WDSET_src(data)                                      ((0x00000100&(data))>>8)
#define SYS_PLL_EDP1_get_REG_EDPPLL_WDSET(data)                                      ((0x00000100&(data))>>8)
#define SYS_PLL_EDP1_REG_EDPPLL_N_shift                                              (6)
#define SYS_PLL_EDP1_REG_EDPPLL_N_mask                                               (0x000000C0)
#define SYS_PLL_EDP1_REG_EDPPLL_N(data)                                              (0x000000C0&((data)<<6))
#define SYS_PLL_EDP1_REG_EDPPLL_N_src(data)                                          ((0x000000C0&(data))>>6)
#define SYS_PLL_EDP1_get_REG_EDPPLL_N(data)                                          ((0x000000C0&(data))>>6)
#define SYS_PLL_EDP1_REG_EDPPLL_DIV_P_shift                                          (4)
#define SYS_PLL_EDP1_REG_EDPPLL_DIV_P_mask                                           (0x00000030)
#define SYS_PLL_EDP1_REG_EDPPLL_DIV_P(data)                                          (0x00000030&((data)<<4))
#define SYS_PLL_EDP1_REG_EDPPLL_DIV_P_src(data)                                      ((0x00000030&(data))>>4)
#define SYS_PLL_EDP1_get_REG_EDPPLL_DIV_P(data)                                      ((0x00000030&(data))>>4)
#define SYS_PLL_EDP1_REG_EDPPLL_TEST_shift                                           (3)
#define SYS_PLL_EDP1_REG_EDPPLL_TEST_mask                                            (0x00000008)
#define SYS_PLL_EDP1_REG_EDPPLL_TEST(data)                                           (0x00000008&((data)<<3))
#define SYS_PLL_EDP1_REG_EDPPLL_TEST_src(data)                                       ((0x00000008&(data))>>3)
#define SYS_PLL_EDP1_get_REG_EDPPLL_TEST(data)                                       ((0x00000008&(data))>>3)
#define SYS_PLL_EDP1_REG_EDPPLL_INCF_shift                                           (2)
#define SYS_PLL_EDP1_REG_EDPPLL_INCF_mask                                            (0x00000004)
#define SYS_PLL_EDP1_REG_EDPPLL_INCF(data)                                           (0x00000004&((data)<<2))
#define SYS_PLL_EDP1_REG_EDPPLL_INCF_src(data)                                       ((0x00000004&(data))>>2)
#define SYS_PLL_EDP1_get_REG_EDPPLL_INCF(data)                                       ((0x00000004&(data))>>2)
#define SYS_PLL_EDP1_REG_EDPPLL_PI_BPS_shift                                         (1)
#define SYS_PLL_EDP1_REG_EDPPLL_PI_BPS_mask                                          (0x00000002)
#define SYS_PLL_EDP1_REG_EDPPLL_PI_BPS(data)                                         (0x00000002&((data)<<1))
#define SYS_PLL_EDP1_REG_EDPPLL_PI_BPS_src(data)                                     ((0x00000002&(data))>>1)
#define SYS_PLL_EDP1_get_REG_EDPPLL_PI_BPS(data)                                     ((0x00000002&(data))>>1)
#define SYS_PLL_EDP1_REG_BIAS_POW_shift                                              (0)
#define SYS_PLL_EDP1_REG_BIAS_POW_mask                                               (0x00000001)
#define SYS_PLL_EDP1_REG_BIAS_POW(data)                                              (0x00000001&((data)<<0))
#define SYS_PLL_EDP1_REG_BIAS_POW_src(data)                                          ((0x00000001&(data))>>0)
#define SYS_PLL_EDP1_get_REG_BIAS_POW(data)                                          ((0x00000001&(data))>>0)


#define SYS_PLL_EDP2                                                                 0x9800024C
#define SYS_PLL_EDP2_reg_addr                                                        "0x9800024C"
#define SYS_PLL_EDP2_reg                                                             0x9800024C
#define set_SYS_PLL_EDP2_reg(data)   (*((volatile unsigned int*) SYS_PLL_EDP2_reg)=data)
#define get_SYS_PLL_EDP2_reg   (*((volatile unsigned int*) SYS_PLL_EDP2_reg))
#define SYS_PLL_EDP2_inst_adr                                                        "0x0093"
#define SYS_PLL_EDP2_inst                                                            0x0093
#define SYS_PLL_EDP2_REG_EDPPLL_RESERVED_shift                                       (2)
#define SYS_PLL_EDP2_REG_EDPPLL_RESERVED_mask                                        (0x000003FC)
#define SYS_PLL_EDP2_REG_EDPPLL_RESERVED(data)                                       (0x000003FC&((data)<<2))
#define SYS_PLL_EDP2_REG_EDPPLL_RESERVED_src(data)                                   ((0x000003FC&(data))>>2)
#define SYS_PLL_EDP2_get_REG_EDPPLL_RESERVED(data)                                   ((0x000003FC&(data))>>2)
#define SYS_PLL_EDP2_REG_EDPPLL_RSTB_shift                                           (1)
#define SYS_PLL_EDP2_REG_EDPPLL_RSTB_mask                                            (0x00000002)
#define SYS_PLL_EDP2_REG_EDPPLL_RSTB(data)                                           (0x00000002&((data)<<1))
#define SYS_PLL_EDP2_REG_EDPPLL_RSTB_src(data)                                       ((0x00000002&(data))>>1)
#define SYS_PLL_EDP2_get_REG_EDPPLL_RSTB(data)                                       ((0x00000002&(data))>>1)
#define SYS_PLL_EDP2_REG_EDPPLL_POW_shift                                            (0)
#define SYS_PLL_EDP2_REG_EDPPLL_POW_mask                                             (0x00000001)
#define SYS_PLL_EDP2_REG_EDPPLL_POW(data)                                            (0x00000001&((data)<<0))
#define SYS_PLL_EDP2_REG_EDPPLL_POW_src(data)                                        ((0x00000001&(data))>>0)
#define SYS_PLL_EDP2_get_REG_EDPPLL_POW(data)                                        ((0x00000001&(data))>>0)


#define SYS_PLL_PIXEL1                                                               0x98000250
#define SYS_PLL_PIXEL1_reg_addr                                                      "0x98000250"
#define SYS_PLL_PIXEL1_reg                                                           0x98000250
#define set_SYS_PLL_PIXEL1_reg(data)   (*((volatile unsigned int*) SYS_PLL_PIXEL1_reg)=data)
#define get_SYS_PLL_PIXEL1_reg   (*((volatile unsigned int*) SYS_PLL_PIXEL1_reg))
#define SYS_PLL_PIXEL1_inst_adr                                                      "0x0094"
#define SYS_PLL_PIXEL1_inst                                                          0x0094
#define SYS_PLL_PIXEL1_REG_PIXELPLL_LDOPOW_shift                                     (31)
#define SYS_PLL_PIXEL1_REG_PIXELPLL_LDOPOW_mask                                      (0x80000000)
#define SYS_PLL_PIXEL1_REG_PIXELPLL_LDOPOW(data)                                     (0x80000000&((data)<<31))
#define SYS_PLL_PIXEL1_REG_PIXELPLL_LDOPOW_src(data)                                 ((0x80000000&(data))>>31)
#define SYS_PLL_PIXEL1_get_REG_PIXELPLL_LDOPOW(data)                                 ((0x80000000&(data))>>31)
#define SYS_PLL_PIXEL1_REG_PIXELPLL_LDOSEL_shift                                     (28)
#define SYS_PLL_PIXEL1_REG_PIXELPLL_LDOSEL_mask                                      (0x30000000)
#define SYS_PLL_PIXEL1_REG_PIXELPLL_LDOSEL(data)                                     (0x30000000&((data)<<28))
#define SYS_PLL_PIXEL1_REG_PIXELPLL_LDOSEL_src(data)                                 ((0x30000000&(data))>>28)
#define SYS_PLL_PIXEL1_get_REG_PIXELPLL_LDOSEL(data)                                 ((0x30000000&(data))>>28)
#define SYS_PLL_PIXEL1_REG_PIXELPLL_RS_shift                                         (24)
#define SYS_PLL_PIXEL1_REG_PIXELPLL_RS_mask                                          (0x07000000)
#define SYS_PLL_PIXEL1_REG_PIXELPLL_RS(data)                                         (0x07000000&((data)<<24))
#define SYS_PLL_PIXEL1_REG_PIXELPLL_RS_src(data)                                     ((0x07000000&(data))>>24)
#define SYS_PLL_PIXEL1_get_REG_PIXELPLL_RS(data)                                     ((0x07000000&(data))>>24)
#define SYS_PLL_PIXEL1_REG_PIXELPLL_IP_shift                                         (20)
#define SYS_PLL_PIXEL1_REG_PIXELPLL_IP_mask                                          (0x00700000)
#define SYS_PLL_PIXEL1_REG_PIXELPLL_IP(data)                                         (0x00700000&((data)<<20))
#define SYS_PLL_PIXEL1_REG_PIXELPLL_IP_src(data)                                     ((0x00700000&(data))>>20)
#define SYS_PLL_PIXEL1_get_REG_PIXELPLL_IP(data)                                     ((0x00700000&(data))>>20)
#define SYS_PLL_PIXEL1_REG_PIXELPLL_CP_shift                                         (18)
#define SYS_PLL_PIXEL1_REG_PIXELPLL_CP_mask                                          (0x000C0000)
#define SYS_PLL_PIXEL1_REG_PIXELPLL_CP(data)                                         (0x000C0000&((data)<<18))
#define SYS_PLL_PIXEL1_REG_PIXELPLL_CP_src(data)                                     ((0x000C0000&(data))>>18)
#define SYS_PLL_PIXEL1_get_REG_PIXELPLL_CP(data)                                     ((0x000C0000&(data))>>18)
#define SYS_PLL_PIXEL1_REG_PIXELPLL_CS_shift                                         (16)
#define SYS_PLL_PIXEL1_REG_PIXELPLL_CS_mask                                          (0x00030000)
#define SYS_PLL_PIXEL1_REG_PIXELPLL_CS(data)                                         (0x00030000&((data)<<16))
#define SYS_PLL_PIXEL1_REG_PIXELPLL_CS_src(data)                                     ((0x00030000&(data))>>16)
#define SYS_PLL_PIXEL1_get_REG_PIXELPLL_CS(data)                                     ((0x00030000&(data))>>16)
#define SYS_PLL_PIXEL1_REG_PIXELPLL_RSTB_shift                                       (14)
#define SYS_PLL_PIXEL1_REG_PIXELPLL_RSTB_mask                                        (0x00004000)
#define SYS_PLL_PIXEL1_REG_PIXELPLL_RSTB(data)                                       (0x00004000&((data)<<14))
#define SYS_PLL_PIXEL1_REG_PIXELPLL_RSTB_src(data)                                   ((0x00004000&(data))>>14)
#define SYS_PLL_PIXEL1_get_REG_PIXELPLL_RSTB(data)                                   ((0x00004000&(data))>>14)
#define SYS_PLL_PIXEL1_REG_PIXELPLL_WDRST_shift                                      (13)
#define SYS_PLL_PIXEL1_REG_PIXELPLL_WDRST_mask                                       (0x00002000)
#define SYS_PLL_PIXEL1_REG_PIXELPLL_WDRST(data)                                      (0x00002000&((data)<<13))
#define SYS_PLL_PIXEL1_REG_PIXELPLL_WDRST_src(data)                                  ((0x00002000&(data))>>13)
#define SYS_PLL_PIXEL1_get_REG_PIXELPLL_WDRST(data)                                  ((0x00002000&(data))>>13)
#define SYS_PLL_PIXEL1_REG_PIXELPLL_WDSET_shift                                      (12)
#define SYS_PLL_PIXEL1_REG_PIXELPLL_WDSET_mask                                       (0x00001000)
#define SYS_PLL_PIXEL1_REG_PIXELPLL_WDSET(data)                                      (0x00001000&((data)<<12))
#define SYS_PLL_PIXEL1_REG_PIXELPLL_WDSET_src(data)                                  ((0x00001000&(data))>>12)
#define SYS_PLL_PIXEL1_get_REG_PIXELPLL_WDSET(data)                                  ((0x00001000&(data))>>12)
#define SYS_PLL_PIXEL1_REG_PIXELPLL_BPSIN_shift                                      (11)
#define SYS_PLL_PIXEL1_REG_PIXELPLL_BPSIN_mask                                       (0x00000800)
#define SYS_PLL_PIXEL1_REG_PIXELPLL_BPSIN(data)                                      (0x00000800&((data)<<11))
#define SYS_PLL_PIXEL1_REG_PIXELPLL_BPSIN_src(data)                                  ((0x00000800&(data))>>11)
#define SYS_PLL_PIXEL1_get_REG_PIXELPLL_BPSIN(data)                                  ((0x00000800&(data))>>11)
#define SYS_PLL_PIXEL1_REG_PIXELPLL_N_shift                                          (8)
#define SYS_PLL_PIXEL1_REG_PIXELPLL_N_mask                                           (0x00000700)
#define SYS_PLL_PIXEL1_REG_PIXELPLL_N(data)                                          (0x00000700&((data)<<8))
#define SYS_PLL_PIXEL1_REG_PIXELPLL_N_src(data)                                      ((0x00000700&(data))>>8)
#define SYS_PLL_PIXEL1_get_REG_PIXELPLL_N(data)                                      ((0x00000700&(data))>>8)
#define SYS_PLL_PIXEL1_REG_PIXELPLL_VCORSTB_shift                                    (7)
#define SYS_PLL_PIXEL1_REG_PIXELPLL_VCORSTB_mask                                     (0x00000080)
#define SYS_PLL_PIXEL1_REG_PIXELPLL_VCORSTB(data)                                    (0x00000080&((data)<<7))
#define SYS_PLL_PIXEL1_REG_PIXELPLL_VCORSTB_src(data)                                ((0x00000080&(data))>>7)
#define SYS_PLL_PIXEL1_get_REG_PIXELPLL_VCORSTB(data)                                ((0x00000080&(data))>>7)
#define SYS_PLL_PIXEL1_REG_PIXELPLL_O_shift                                          (4)
#define SYS_PLL_PIXEL1_REG_PIXELPLL_O_mask                                           (0x00000030)
#define SYS_PLL_PIXEL1_REG_PIXELPLL_O(data)                                          (0x00000030&((data)<<4))
#define SYS_PLL_PIXEL1_REG_PIXELPLL_O_src(data)                                      ((0x00000030&(data))>>4)
#define SYS_PLL_PIXEL1_get_REG_PIXELPLL_O(data)                                      ((0x00000030&(data))>>4)
#define SYS_PLL_PIXEL1_REG_PIXELPLL_TEST_shift                                       (3)
#define SYS_PLL_PIXEL1_REG_PIXELPLL_TEST_mask                                        (0x00000008)
#define SYS_PLL_PIXEL1_REG_PIXELPLL_TEST(data)                                       (0x00000008&((data)<<3))
#define SYS_PLL_PIXEL1_REG_PIXELPLL_TEST_src(data)                                   ((0x00000008&(data))>>3)
#define SYS_PLL_PIXEL1_get_REG_PIXELPLL_TEST(data)                                   ((0x00000008&(data))>>3)
#define SYS_PLL_PIXEL1_REG_PIXELPLL_FREEZE_shift                                     (2)
#define SYS_PLL_PIXEL1_REG_PIXELPLL_FREEZE_mask                                      (0x00000004)
#define SYS_PLL_PIXEL1_REG_PIXELPLL_FREEZE(data)                                     (0x00000004&((data)<<2))
#define SYS_PLL_PIXEL1_REG_PIXELPLL_FREEZE_src(data)                                 ((0x00000004&(data))>>2)
#define SYS_PLL_PIXEL1_get_REG_PIXELPLL_FREEZE(data)                                 ((0x00000004&(data))>>2)
#define SYS_PLL_PIXEL1_REG_PIXELPLL_BPSPI_shift                                      (1)
#define SYS_PLL_PIXEL1_REG_PIXELPLL_BPSPI_mask                                       (0x00000002)
#define SYS_PLL_PIXEL1_REG_PIXELPLL_BPSPI(data)                                      (0x00000002&((data)<<1))
#define SYS_PLL_PIXEL1_REG_PIXELPLL_BPSPI_src(data)                                  ((0x00000002&(data))>>1)
#define SYS_PLL_PIXEL1_get_REG_PIXELPLL_BPSPI(data)                                  ((0x00000002&(data))>>1)


#define SYS_PLL_PIXEL2                                                               0x98000254
#define SYS_PLL_PIXEL2_reg_addr                                                      "0x98000254"
#define SYS_PLL_PIXEL2_reg                                                           0x98000254
#define set_SYS_PLL_PIXEL2_reg(data)   (*((volatile unsigned int*) SYS_PLL_PIXEL2_reg)=data)
#define get_SYS_PLL_PIXEL2_reg   (*((volatile unsigned int*) SYS_PLL_PIXEL2_reg))
#define SYS_PLL_PIXEL2_inst_adr                                                      "0x0095"
#define SYS_PLL_PIXEL2_inst                                                          0x0095
#define SYS_PLL_PIXEL2_REG_PIXELPLL_RESER_shift                                      (9)
#define SYS_PLL_PIXEL2_REG_PIXELPLL_RESER_mask                                       (0x00001E00)
#define SYS_PLL_PIXEL2_REG_PIXELPLL_RESER(data)                                      (0x00001E00&((data)<<9))
#define SYS_PLL_PIXEL2_REG_PIXELPLL_RESER_src(data)                                  ((0x00001E00&(data))>>9)
#define SYS_PLL_PIXEL2_get_REG_PIXELPLL_RESER(data)                                  ((0x00001E00&(data))>>9)
#define SYS_PLL_PIXEL2_REG_PIXELPLL_RESERVED_shift                                   (1)
#define SYS_PLL_PIXEL2_REG_PIXELPLL_RESERVED_mask                                    (0x000001FE)
#define SYS_PLL_PIXEL2_REG_PIXELPLL_RESERVED(data)                                   (0x000001FE&((data)<<1))
#define SYS_PLL_PIXEL2_REG_PIXELPLL_RESERVED_src(data)                               ((0x000001FE&(data))>>1)
#define SYS_PLL_PIXEL2_get_REG_PIXELPLL_RESERVED(data)                               ((0x000001FE&(data))>>1)
#define SYS_PLL_PIXEL2_REG_PIXELPLL_POW_shift                                        (0)
#define SYS_PLL_PIXEL2_REG_PIXELPLL_POW_mask                                         (0x00000001)
#define SYS_PLL_PIXEL2_REG_PIXELPLL_POW(data)                                        (0x00000001&((data)<<0))
#define SYS_PLL_PIXEL2_REG_PIXELPLL_POW_src(data)                                    ((0x00000001&(data))>>0)
#define SYS_PLL_PIXEL2_get_REG_PIXELPLL_POW(data)                                    ((0x00000001&(data))>>0)


#define SYS_PLL_VODMA1                                                               0x98000260
#define SYS_PLL_VODMA1_reg_addr                                                      "0x98000260"
#define SYS_PLL_VODMA1_reg                                                           0x98000260
#define set_SYS_PLL_VODMA1_reg(data)   (*((volatile unsigned int*) SYS_PLL_VODMA1_reg)=data)
#define get_SYS_PLL_VODMA1_reg   (*((volatile unsigned int*) SYS_PLL_VODMA1_reg))
#define SYS_PLL_VODMA1_inst_adr                                                      "0x0098"
#define SYS_PLL_VODMA1_inst                                                          0x0098
#define SYS_PLL_VODMA1_REG_PLLVODMA_WDRST_shift                                      (22)
#define SYS_PLL_VODMA1_REG_PLLVODMA_WDRST_mask                                       (0x00400000)
#define SYS_PLL_VODMA1_REG_PLLVODMA_WDRST(data)                                      (0x00400000&((data)<<22))
#define SYS_PLL_VODMA1_REG_PLLVODMA_WDRST_src(data)                                  ((0x00400000&(data))>>22)
#define SYS_PLL_VODMA1_get_REG_PLLVODMA_WDRST(data)                                  ((0x00400000&(data))>>22)
#define SYS_PLL_VODMA1_REG_PLLVODMA_WDSET_shift                                      (21)
#define SYS_PLL_VODMA1_REG_PLLVODMA_WDSET_mask                                       (0x00200000)
#define SYS_PLL_VODMA1_REG_PLLVODMA_WDSET(data)                                      (0x00200000&((data)<<21))
#define SYS_PLL_VODMA1_REG_PLLVODMA_WDSET_src(data)                                  ((0x00200000&(data))>>21)
#define SYS_PLL_VODMA1_get_REG_PLLVODMA_WDSET(data)                                  ((0x00200000&(data))>>21)
#define SYS_PLL_VODMA1_REG_PLLVODMA_CS_shift                                         (19)
#define SYS_PLL_VODMA1_REG_PLLVODMA_CS_mask                                          (0x00180000)
#define SYS_PLL_VODMA1_REG_PLLVODMA_CS(data)                                         (0x00180000&((data)<<19))
#define SYS_PLL_VODMA1_REG_PLLVODMA_CS_src(data)                                     ((0x00180000&(data))>>19)
#define SYS_PLL_VODMA1_get_REG_PLLVODMA_CS(data)                                     ((0x00180000&(data))>>19)
#define SYS_PLL_VODMA1_REG_PLLVODMA_O_shift                                          (17)
#define SYS_PLL_VODMA1_REG_PLLVODMA_O_mask                                           (0x00060000)
#define SYS_PLL_VODMA1_REG_PLLVODMA_O(data)                                          (0x00060000&((data)<<17))
#define SYS_PLL_VODMA1_REG_PLLVODMA_O_src(data)                                      ((0x00060000&(data))>>17)
#define SYS_PLL_VODMA1_get_REG_PLLVODMA_O(data)                                      ((0x00060000&(data))>>17)
#define SYS_PLL_VODMA1_REG_PLLVODMA_RS_shift                                         (14)
#define SYS_PLL_VODMA1_REG_PLLVODMA_RS_mask                                          (0x0001C000)
#define SYS_PLL_VODMA1_REG_PLLVODMA_RS(data)                                         (0x0001C000&((data)<<14))
#define SYS_PLL_VODMA1_REG_PLLVODMA_RS_src(data)                                     ((0x0001C000&(data))>>14)
#define SYS_PLL_VODMA1_get_REG_PLLVODMA_RS(data)                                     ((0x0001C000&(data))>>14)
#define SYS_PLL_VODMA1_REG_PLLVODMA_N_shift                                          (12)
#define SYS_PLL_VODMA1_REG_PLLVODMA_N_mask                                           (0x00003000)
#define SYS_PLL_VODMA1_REG_PLLVODMA_N(data)                                          (0x00003000&((data)<<12))
#define SYS_PLL_VODMA1_REG_PLLVODMA_N_src(data)                                      ((0x00003000&(data))>>12)
#define SYS_PLL_VODMA1_get_REG_PLLVODMA_N(data)                                      ((0x00003000&(data))>>12)
#define SYS_PLL_VODMA1_REG_PLLVODMA_M_shift                                          (4)
#define SYS_PLL_VODMA1_REG_PLLVODMA_M_mask                                           (0x00000FF0)
#define SYS_PLL_VODMA1_REG_PLLVODMA_M(data)                                          (0x00000FF0&((data)<<4))
#define SYS_PLL_VODMA1_REG_PLLVODMA_M_src(data)                                      ((0x00000FF0&(data))>>4)
#define SYS_PLL_VODMA1_get_REG_PLLVODMA_M(data)                                      ((0x00000FF0&(data))>>4)
#define SYS_PLL_VODMA1_REG_PLLVODMA_IP_shift                                         (1)
#define SYS_PLL_VODMA1_REG_PLLVODMA_IP_mask                                          (0x0000000E)
#define SYS_PLL_VODMA1_REG_PLLVODMA_IP(data)                                         (0x0000000E&((data)<<1))
#define SYS_PLL_VODMA1_REG_PLLVODMA_IP_src(data)                                     ((0x0000000E&(data))>>1)
#define SYS_PLL_VODMA1_get_REG_PLLVODMA_IP(data)                                     ((0x0000000E&(data))>>1)
#define SYS_PLL_VODMA1_REG_PLLVODMA_TST_shift                                        (0)
#define SYS_PLL_VODMA1_REG_PLLVODMA_TST_mask                                         (0x00000001)
#define SYS_PLL_VODMA1_REG_PLLVODMA_TST(data)                                        (0x00000001&((data)<<0))
#define SYS_PLL_VODMA1_REG_PLLVODMA_TST_src(data)                                    ((0x00000001&(data))>>0)
#define SYS_PLL_VODMA1_get_REG_PLLVODMA_TST(data)                                    ((0x00000001&(data))>>0)


#define SYS_PLL_VODMA2                                                               0x98000264
#define SYS_PLL_VODMA2_reg_addr                                                      "0x98000264"
#define SYS_PLL_VODMA2_reg                                                           0x98000264
#define set_SYS_PLL_VODMA2_reg(data)   (*((volatile unsigned int*) SYS_PLL_VODMA2_reg)=data)
#define get_SYS_PLL_VODMA2_reg   (*((volatile unsigned int*) SYS_PLL_VODMA2_reg))
#define SYS_PLL_VODMA2_inst_adr                                                      "0x0099"
#define SYS_PLL_VODMA2_inst                                                          0x0099
#define SYS_PLL_VODMA2_REG_PLLVODMA_OEB_shift                                        (2)
#define SYS_PLL_VODMA2_REG_PLLVODMA_OEB_mask                                         (0x00000004)
#define SYS_PLL_VODMA2_REG_PLLVODMA_OEB(data)                                        (0x00000004&((data)<<2))
#define SYS_PLL_VODMA2_REG_PLLVODMA_OEB_src(data)                                    ((0x00000004&(data))>>2)
#define SYS_PLL_VODMA2_get_REG_PLLVODMA_OEB(data)                                    ((0x00000004&(data))>>2)
#define SYS_PLL_VODMA2_REG_PLLVODMA_RSTB_shift                                       (1)
#define SYS_PLL_VODMA2_REG_PLLVODMA_RSTB_mask                                        (0x00000002)
#define SYS_PLL_VODMA2_REG_PLLVODMA_RSTB(data)                                       (0x00000002&((data)<<1))
#define SYS_PLL_VODMA2_REG_PLLVODMA_RSTB_src(data)                                   ((0x00000002&(data))>>1)
#define SYS_PLL_VODMA2_get_REG_PLLVODMA_RSTB(data)                                   ((0x00000002&(data))>>1)
#define SYS_PLL_VODMA2_REG_PLLVODMA_POW_shift                                        (0)
#define SYS_PLL_VODMA2_REG_PLLVODMA_POW_mask                                         (0x00000001)
#define SYS_PLL_VODMA2_REG_PLLVODMA_POW(data)                                        (0x00000001&((data)<<0))
#define SYS_PLL_VODMA2_REG_PLLVODMA_POW_src(data)                                    ((0x00000001&(data))>>0)
#define SYS_PLL_VODMA2_get_REG_PLLVODMA_POW(data)                                    ((0x00000001&(data))>>0)


#define SYS_CHIP_INFO2                                                               0x98000308
#define SYS_CHIP_INFO2_reg_addr                                                      "0x98000308"
#define SYS_CHIP_INFO2_reg                                                           0x98000308
#define set_SYS_CHIP_INFO2_reg(data)   (*((volatile unsigned int*) SYS_CHIP_INFO2_reg)=data)
#define get_SYS_CHIP_INFO2_reg   (*((volatile unsigned int*) SYS_CHIP_INFO2_reg))
#define SYS_CHIP_INFO2_inst_adr                                                      "0x00C2"
#define SYS_CHIP_INFO2_inst                                                          0x00C2
#define SYS_CHIP_INFO2_testmode_shift                                                (2)
#define SYS_CHIP_INFO2_testmode_mask                                                 (0x00000004)
#define SYS_CHIP_INFO2_testmode(data)                                                (0x00000004&((data)<<2))
#define SYS_CHIP_INFO2_testmode_src(data)                                            ((0x00000004&(data))>>2)
#define SYS_CHIP_INFO2_get_testmode(data)                                            ((0x00000004&(data))>>2)
#define SYS_CHIP_INFO2_nf_sel_shift                                                  (1)
#define SYS_CHIP_INFO2_nf_sel_mask                                                   (0x00000002)
#define SYS_CHIP_INFO2_nf_sel(data)                                                  (0x00000002&((data)<<1))
#define SYS_CHIP_INFO2_nf_sel_src(data)                                              ((0x00000002&(data))>>1)
#define SYS_CHIP_INFO2_get_nf_sel(data)                                              ((0x00000002&(data))>>1)
#define SYS_CHIP_INFO2_boot_sel_shift                                                (0)
#define SYS_CHIP_INFO2_boot_sel_mask                                                 (0x00000001)
#define SYS_CHIP_INFO2_boot_sel(data)                                                (0x00000001&((data)<<0))
#define SYS_CHIP_INFO2_boot_sel_src(data)                                            ((0x00000001&(data))>>0)
#define SYS_CHIP_INFO2_get_boot_sel(data)                                            ((0x00000001&(data))>>0)


#define SYS_SCPU_L2                                                                  0x9800030C
#define SYS_SCPU_L2_reg_addr                                                         "0x9800030C"
#define SYS_SCPU_L2_reg                                                              0x9800030C
#define set_SYS_SCPU_L2_reg(data)   (*((volatile unsigned int*) SYS_SCPU_L2_reg)=data)
#define get_SYS_SCPU_L2_reg   (*((volatile unsigned int*) SYS_SCPU_L2_reg))
#define SYS_SCPU_L2_inst_adr                                                         "0x00C3"
#define SYS_SCPU_L2_inst                                                             0x00C3
#define SYS_SCPU_L2_reserved_scpu_l2_shift                                           (0)
#define SYS_SCPU_L2_reserved_scpu_l2_mask                                            (0x00000001)
#define SYS_SCPU_L2_reserved_scpu_l2(data)                                           (0x00000001&((data)<<0))
#define SYS_SCPU_L2_reserved_scpu_l2_src(data)                                       ((0x00000001&(data))>>0)
#define SYS_SCPU_L2_get_reserved_scpu_l2(data)                                       ((0x00000001&(data))>>0)


#define SYS_PWDN_CTRL                                                                0x98000320
#define SYS_PWDN_CTRL_reg_addr                                                       "0x98000320"
#define SYS_PWDN_CTRL_reg                                                            0x98000320
#define set_SYS_PWDN_CTRL_reg(data)   (*((volatile unsigned int*) SYS_PWDN_CTRL_reg)=data)
#define get_SYS_PWDN_CTRL_reg   (*((volatile unsigned int*) SYS_PWDN_CTRL_reg))
#define SYS_PWDN_CTRL_inst_adr                                                       "0x00C8"
#define SYS_PWDN_CTRL_inst                                                           0x00C8
#define SYS_PWDN_CTRL_scpu_boot_info_shift                                           (0)
#define SYS_PWDN_CTRL_scpu_boot_info_mask                                            (0xFFFFFFFF)
#define SYS_PWDN_CTRL_scpu_boot_info(data)                                           (0xFFFFFFFF&((data)<<0))
#define SYS_PWDN_CTRL_scpu_boot_info_src(data)                                       ((0xFFFFFFFF&(data))>>0)
#define SYS_PWDN_CTRL_get_scpu_boot_info(data)                                       ((0xFFFFFFFF&(data))>>0)


#define SYS_PWDN_CTRL2                                                               0x98000324
#define SYS_PWDN_CTRL2_reg_addr                                                      "0x98000324"
#define SYS_PWDN_CTRL2_reg                                                           0x98000324
#define set_SYS_PWDN_CTRL2_reg(data)   (*((volatile unsigned int*) SYS_PWDN_CTRL2_reg)=data)
#define get_SYS_PWDN_CTRL2_reg   (*((volatile unsigned int*) SYS_PWDN_CTRL2_reg))
#define SYS_PWDN_CTRL2_inst_adr                                                      "0x00C9"
#define SYS_PWDN_CTRL2_inst                                                          0x00C9
#define SYS_PWDN_CTRL2_acpu_boot_info_shift                                          (0)
#define SYS_PWDN_CTRL2_acpu_boot_info_mask                                           (0xFFFFFFFF)
#define SYS_PWDN_CTRL2_acpu_boot_info(data)                                          (0xFFFFFFFF&((data)<<0))
#define SYS_PWDN_CTRL2_acpu_boot_info_src(data)                                      ((0xFFFFFFFF&(data))>>0)
#define SYS_PWDN_CTRL2_get_acpu_boot_info(data)                                      ((0xFFFFFFFF&(data))>>0)


#define SYS_PWDN_CTRL3                                                               0x98000328
#define SYS_PWDN_CTRL3_reg_addr                                                      "0x98000328"
#define SYS_PWDN_CTRL3_reg                                                           0x98000328
#define set_SYS_PWDN_CTRL3_reg(data)   (*((volatile unsigned int*) SYS_PWDN_CTRL3_reg)=data)
#define get_SYS_PWDN_CTRL3_reg   (*((volatile unsigned int*) SYS_PWDN_CTRL3_reg))
#define SYS_PWDN_CTRL3_inst_adr                                                      "0x00CA"
#define SYS_PWDN_CTRL3_inst                                                          0x00CA
#define SYS_PWDN_CTRL3_write_en2_shift                                               (3)
#define SYS_PWDN_CTRL3_write_en2_mask                                                (0x00000008)
#define SYS_PWDN_CTRL3_write_en2(data)                                               (0x00000008&((data)<<3))
#define SYS_PWDN_CTRL3_write_en2_src(data)                                           ((0x00000008&(data))>>3)
#define SYS_PWDN_CTRL3_get_write_en2(data)                                           ((0x00000008&(data))>>3)
#define SYS_PWDN_CTRL3_scpu_boot_info_valid_shift                                    (2)
#define SYS_PWDN_CTRL3_scpu_boot_info_valid_mask                                     (0x00000004)
#define SYS_PWDN_CTRL3_scpu_boot_info_valid(data)                                    (0x00000004&((data)<<2))
#define SYS_PWDN_CTRL3_scpu_boot_info_valid_src(data)                                ((0x00000004&(data))>>2)
#define SYS_PWDN_CTRL3_get_scpu_boot_info_valid(data)                                ((0x00000004&(data))>>2)
#define SYS_PWDN_CTRL3_write_en1_shift                                               (1)
#define SYS_PWDN_CTRL3_write_en1_mask                                                (0x00000002)
#define SYS_PWDN_CTRL3_write_en1(data)                                               (0x00000002&((data)<<1))
#define SYS_PWDN_CTRL3_write_en1_src(data)                                           ((0x00000002&(data))>>1)
#define SYS_PWDN_CTRL3_get_write_en1(data)                                           ((0x00000002&(data))>>1)
#define SYS_PWDN_CTRL3_scpu_sw_rst_shift                                             (0)
#define SYS_PWDN_CTRL3_scpu_sw_rst_mask                                              (0x00000001)
#define SYS_PWDN_CTRL3_scpu_sw_rst(data)                                             (0x00000001&((data)<<0))
#define SYS_PWDN_CTRL3_scpu_sw_rst_src(data)                                         ((0x00000001&(data))>>0)
#define SYS_PWDN_CTRL3_get_scpu_sw_rst(data)                                         ((0x00000001&(data))>>0)


#define SYS_PWDN_CTRL4                                                               0x9800032C
#define SYS_PWDN_CTRL4_reg_addr                                                      "0x9800032C"
#define SYS_PWDN_CTRL4_reg                                                           0x9800032C
#define set_SYS_PWDN_CTRL4_reg(data)   (*((volatile unsigned int*) SYS_PWDN_CTRL4_reg)=data)
#define get_SYS_PWDN_CTRL4_reg   (*((volatile unsigned int*) SYS_PWDN_CTRL4_reg))
#define SYS_PWDN_CTRL4_inst_adr                                                      "0x00CB"
#define SYS_PWDN_CTRL4_inst                                                          0x00CB
#define SYS_PWDN_CTRL4_acpu_boot_info_valid_shift                                    (0)
#define SYS_PWDN_CTRL4_acpu_boot_info_valid_mask                                     (0x00000001)
#define SYS_PWDN_CTRL4_acpu_boot_info_valid(data)                                    (0x00000001&((data)<<0))
#define SYS_PWDN_CTRL4_acpu_boot_info_valid_src(data)                                ((0x00000001&(data))>>0)
#define SYS_PWDN_CTRL4_get_acpu_boot_info_valid(data)                                ((0x00000001&(data))>>0)


#define SYS_AT_SPEED                                                                 0x98000330
#define SYS_AT_SPEED_reg_addr                                                        "0x98000330"
#define SYS_AT_SPEED_reg                                                             0x98000330
#define set_SYS_AT_SPEED_reg(data)   (*((volatile unsigned int*) SYS_AT_SPEED_reg)=data)
#define get_SYS_AT_SPEED_reg   (*((volatile unsigned int*) SYS_AT_SPEED_reg))
#define SYS_AT_SPEED_inst_adr                                                        "0x00CC"
#define SYS_AT_SPEED_inst                                                            0x00CC
#define SYS_AT_SPEED_write_en3_shift                                                 (5)
#define SYS_AT_SPEED_write_en3_mask                                                  (0x00000020)
#define SYS_AT_SPEED_write_en3(data)                                                 (0x00000020&((data)<<5))
#define SYS_AT_SPEED_write_en3_src(data)                                             ((0x00000020&(data))>>5)
#define SYS_AT_SPEED_get_write_en3(data)                                             ((0x00000020&(data))>>5)
#define SYS_AT_SPEED_hdmirx_at_speed_pll_done_shift                                  (4)
#define SYS_AT_SPEED_hdmirx_at_speed_pll_done_mask                                   (0x00000010)
#define SYS_AT_SPEED_hdmirx_at_speed_pll_done(data)                                  (0x00000010&((data)<<4))
#define SYS_AT_SPEED_hdmirx_at_speed_pll_done_src(data)                              ((0x00000010&(data))>>4)
#define SYS_AT_SPEED_get_hdmirx_at_speed_pll_done(data)                              ((0x00000010&(data))>>4)
#define SYS_AT_SPEED_write_en2_shift                                                 (3)
#define SYS_AT_SPEED_write_en2_mask                                                  (0x00000008)
#define SYS_AT_SPEED_write_en2(data)                                                 (0x00000008&((data)<<3))
#define SYS_AT_SPEED_write_en2_src(data)                                             ((0x00000008&(data))>>3)
#define SYS_AT_SPEED_get_write_en2(data)                                             ((0x00000008&(data))>>3)
#define SYS_AT_SPEED_dac_test_shift                                                  (2)
#define SYS_AT_SPEED_dac_test_mask                                                   (0x00000004)
#define SYS_AT_SPEED_dac_test(data)                                                  (0x00000004&((data)<<2))
#define SYS_AT_SPEED_dac_test_src(data)                                              ((0x00000004&(data))>>2)
#define SYS_AT_SPEED_get_dac_test(data)                                              ((0x00000004&(data))>>2)
#define SYS_AT_SPEED_write_en1_shift                                                 (1)
#define SYS_AT_SPEED_write_en1_mask                                                  (0x00000002)
#define SYS_AT_SPEED_write_en1(data)                                                 (0x00000002&((data)<<1))
#define SYS_AT_SPEED_write_en1_src(data)                                             ((0x00000002&(data))>>1)
#define SYS_AT_SPEED_get_write_en1(data)                                             ((0x00000002&(data))>>1)
#define SYS_AT_SPEED_scpu_config_done_shift                                          (0)
#define SYS_AT_SPEED_scpu_config_done_mask                                           (0x00000001)
#define SYS_AT_SPEED_scpu_config_done(data)                                          (0x00000001&((data)<<0))
#define SYS_AT_SPEED_scpu_config_done_src(data)                                      ((0x00000001&(data))>>0)
#define SYS_AT_SPEED_get_scpu_config_done(data)                                      ((0x00000001&(data))>>0)


#define SYS_ANA_CTRL                                                                 0x98000334
#define SYS_ANA_CTRL_reg_addr                                                        "0x98000334"
#define SYS_ANA_CTRL_reg                                                             0x98000334
#define set_SYS_ANA_CTRL_reg(data)   (*((volatile unsigned int*) SYS_ANA_CTRL_reg)=data)
#define get_SYS_ANA_CTRL_reg   (*((volatile unsigned int*) SYS_ANA_CTRL_reg))
#define SYS_ANA_CTRL_inst_adr                                                        "0x00CD"
#define SYS_ANA_CTRL_inst                                                            0x00CD
#define SYS_ANA_CTRL_reserved_ana_ctrl_shift                                         (0)
#define SYS_ANA_CTRL_reserved_ana_ctrl_mask                                          (0x00000001)
#define SYS_ANA_CTRL_reserved_ana_ctrl(data)                                         (0x00000001&((data)<<0))
#define SYS_ANA_CTRL_reserved_ana_ctrl_src(data)                                     ((0x00000001&(data))>>0)
#define SYS_ANA_CTRL_get_reserved_ana_ctrl(data)                                     ((0x00000001&(data))>>0)


#define SYS_TP_DEMOD_CTRL                                                            0x98000338
#define SYS_TP_DEMOD_CTRL_reg_addr                                                   "0x98000338"
#define SYS_TP_DEMOD_CTRL_reg                                                        0x98000338
#define set_SYS_TP_DEMOD_CTRL_reg(data)   (*((volatile unsigned int*) SYS_TP_DEMOD_CTRL_reg)=data)
#define get_SYS_TP_DEMOD_CTRL_reg   (*((volatile unsigned int*) SYS_TP_DEMOD_CTRL_reg))
#define SYS_TP_DEMOD_CTRL_inst_adr                                                   "0x00CE"
#define SYS_TP_DEMOD_CTRL_inst                                                       0x00CE
#define SYS_TP_DEMOD_CTRL_reserved_tp_demod_ctrl_shift                               (0)
#define SYS_TP_DEMOD_CTRL_reserved_tp_demod_ctrl_mask                                (0x00000001)
#define SYS_TP_DEMOD_CTRL_reserved_tp_demod_ctrl(data)                               (0x00000001&((data)<<0))
#define SYS_TP_DEMOD_CTRL_reserved_tp_demod_ctrl_src(data)                           ((0x00000001&(data))>>0)
#define SYS_TP_DEMOD_CTRL_get_reserved_tp_demod_ctrl(data)                           ((0x00000001&(data))>>0)


#define SYS_PHY_FUNC                                                                 0x98000340
#define SYS_PHY_FUNC_reg_addr                                                        "0x98000340"
#define SYS_PHY_FUNC_reg                                                             0x98000340
#define set_SYS_PHY_FUNC_reg(data)   (*((volatile unsigned int*) SYS_PHY_FUNC_reg)=data)
#define get_SYS_PHY_FUNC_reg   (*((volatile unsigned int*) SYS_PHY_FUNC_reg))
#define SYS_PHY_FUNC_inst_adr                                                        "0x00D0"
#define SYS_PHY_FUNC_inst                                                            0x00D0
#define SYS_PHY_FUNC_reserved_phy_func_shift                                         (0)
#define SYS_PHY_FUNC_reserved_phy_func_mask                                          (0x00000001)
#define SYS_PHY_FUNC_reserved_phy_func(data)                                         (0x00000001&((data)<<0))
#define SYS_PHY_FUNC_reserved_phy_func_src(data)                                     ((0x00000001&(data))>>0)
#define SYS_PHY_FUNC_get_reserved_phy_func(data)                                     ((0x00000001&(data))>>0)


#define SYS_ANLG                                                                     0x98000344
#define SYS_ANLG_reg_addr                                                            "0x98000344"
#define SYS_ANLG_reg                                                                 0x98000344
#define set_SYS_ANLG_reg(data)   (*((volatile unsigned int*) SYS_ANLG_reg)=data)
#define get_SYS_ANLG_reg   (*((volatile unsigned int*) SYS_ANLG_reg))
#define SYS_ANLG_inst_adr                                                            "0x00D1"
#define SYS_ANLG_inst                                                                0x00D1
#define SYS_ANLG_analogy_mode_sel_shift                                              (0)
#define SYS_ANLG_analogy_mode_sel_mask                                               (0x0000000F)
#define SYS_ANLG_analogy_mode_sel(data)                                              (0x0000000F&((data)<<0))
#define SYS_ANLG_analogy_mode_sel_src(data)                                          ((0x0000000F&(data))>>0)
#define SYS_ANLG_get_analogy_mode_sel(data)                                          ((0x0000000F&(data))>>0)


#define SYS_PLL_TEST1                                                                0x98000348
#define SYS_PLL_TEST1_reg_addr                                                       "0x98000348"
#define SYS_PLL_TEST1_reg                                                            0x98000348
#define set_SYS_PLL_TEST1_reg(data)   (*((volatile unsigned int*) SYS_PLL_TEST1_reg)=data)
#define get_SYS_PLL_TEST1_reg   (*((volatile unsigned int*) SYS_PLL_TEST1_reg))
#define SYS_PLL_TEST1_inst_adr                                                       "0x00D2"
#define SYS_PLL_TEST1_inst                                                           0x00D2
#define SYS_PLL_TEST1_REG_TEST_EN_shift                                              (9)
#define SYS_PLL_TEST1_REG_TEST_EN_mask                                               (0x00000200)
#define SYS_PLL_TEST1_REG_TEST_EN(data)                                              (0x00000200&((data)<<9))
#define SYS_PLL_TEST1_REG_TEST_EN_src(data)                                          ((0x00000200&(data))>>9)
#define SYS_PLL_TEST1_get_REG_TEST_EN(data)                                          ((0x00000200&(data))>>9)
#define SYS_PLL_TEST1_REG_PLLTST_EN_shift                                            (8)
#define SYS_PLL_TEST1_REG_PLLTST_EN_mask                                             (0x00000100)
#define SYS_PLL_TEST1_REG_PLLTST_EN(data)                                            (0x00000100&((data)<<8))
#define SYS_PLL_TEST1_REG_PLLTST_EN_src(data)                                        ((0x00000100&(data))>>8)
#define SYS_PLL_TEST1_get_REG_PLLTST_EN(data)                                        ((0x00000100&(data))>>8)
#define SYS_PLL_TEST1_REG_PLLTST_DIV32_shift                                         (7)
#define SYS_PLL_TEST1_REG_PLLTST_DIV32_mask                                          (0x00000080)
#define SYS_PLL_TEST1_REG_PLLTST_DIV32(data)                                         (0x00000080&((data)<<7))
#define SYS_PLL_TEST1_REG_PLLTST_DIV32_src(data)                                     ((0x00000080&(data))>>7)
#define SYS_PLL_TEST1_get_REG_PLLTST_DIV32(data)                                     ((0x00000080&(data))>>7)
#define SYS_PLL_TEST1_REG_PLLTST_DIV16_shift                                         (6)
#define SYS_PLL_TEST1_REG_PLLTST_DIV16_mask                                          (0x00000040)
#define SYS_PLL_TEST1_REG_PLLTST_DIV16(data)                                         (0x00000040&((data)<<6))
#define SYS_PLL_TEST1_REG_PLLTST_DIV16_src(data)                                     ((0x00000040&(data))>>6)
#define SYS_PLL_TEST1_get_REG_PLLTST_DIV16(data)                                     ((0x00000040&(data))>>6)
#define SYS_PLL_TEST1_REG_PLLTST_SEL_shift                                           (2)
#define SYS_PLL_TEST1_REG_PLLTST_SEL_mask                                            (0x0000003C)
#define SYS_PLL_TEST1_REG_PLLTST_SEL(data)                                           (0x0000003C&((data)<<2))
#define SYS_PLL_TEST1_REG_PLLTST_SEL_src(data)                                       ((0x0000003C&(data))>>2)
#define SYS_PLL_TEST1_get_REG_PLLTST_SEL(data)                                       ((0x0000003C&(data))>>2)
#define SYS_PLL_TEST1_REG_PLLTST_DIV_shift                                           (0)
#define SYS_PLL_TEST1_REG_PLLTST_DIV_mask                                            (0x00000003)
#define SYS_PLL_TEST1_REG_PLLTST_DIV(data)                                           (0x00000003&((data)<<0))
#define SYS_PLL_TEST1_REG_PLLTST_DIV_src(data)                                       ((0x00000003&(data))>>0)
#define SYS_PLL_TEST1_get_REG_PLLTST_DIV(data)                                       ((0x00000003&(data))>>0)


#define SYS_LSADC_PG                                                                 0x9800034c
#define SYS_LSADC_PG_reg_addr                                                        "0x9800034C"
#define SYS_LSADC_PG_reg                                                             0x9800034C
#define set_SYS_LSADC_PG_reg(data)   (*((volatile unsigned int*) SYS_LSADC_PG_reg)=data)
#define get_SYS_LSADC_PG_reg   (*((volatile unsigned int*) SYS_LSADC_PG_reg))
#define SYS_LSADC_PG_inst_adr                                                        "0x00D3"
#define SYS_LSADC_PG_inst                                                            0x00D3
#define SYS_LSADC_PG_REG_VDDMUX_SEL_shift                                            (10)
#define SYS_LSADC_PG_REG_VDDMUX_SEL_mask                                             (0x00000400)
#define SYS_LSADC_PG_REG_VDDMUX_SEL(data)                                            (0x00000400&((data)<<10))
#define SYS_LSADC_PG_REG_VDDMUX_SEL_src(data)                                        ((0x00000400&(data))>>10)
#define SYS_LSADC_PG_get_REG_VDDMUX_SEL(data)                                        ((0x00000400&(data))>>10)
#define SYS_LSADC_PG_REG_VDD_MUX1_shift                                              (6)
#define SYS_LSADC_PG_REG_VDD_MUX1_mask                                               (0x000003C0)
#define SYS_LSADC_PG_REG_VDD_MUX1(data)                                              (0x000003C0&((data)<<6))
#define SYS_LSADC_PG_REG_VDD_MUX1_src(data)                                          ((0x000003C0&(data))>>6)
#define SYS_LSADC_PG_get_REG_VDD_MUX1(data)                                          ((0x000003C0&(data))>>6)
#define SYS_LSADC_PG_REG_VDD_MUX2_shift                                              (2)
#define SYS_LSADC_PG_REG_VDD_MUX2_mask                                               (0x0000003C)
#define SYS_LSADC_PG_REG_VDD_MUX2(data)                                              (0x0000003C&((data)<<2))
#define SYS_LSADC_PG_REG_VDD_MUX2_src(data)                                          ((0x0000003C&(data))>>2)
#define SYS_LSADC_PG_get_REG_VDD_MUX2(data)                                          ((0x0000003C&(data))>>2)
#define SYS_LSADC_PG_REG_VDDMUX_EN_shift                                             (1)
#define SYS_LSADC_PG_REG_VDDMUX_EN_mask                                              (0x00000002)
#define SYS_LSADC_PG_REG_VDDMUX_EN(data)                                             (0x00000002&((data)<<1))
#define SYS_LSADC_PG_REG_VDDMUX_EN_src(data)                                         ((0x00000002&(data))>>1)
#define SYS_LSADC_PG_get_REG_VDDMUX_EN(data)                                         ((0x00000002&(data))>>1)
#define SYS_LSADC_PG_REG_TEST_OUT_EN_shift                                           (0)
#define SYS_LSADC_PG_REG_TEST_OUT_EN_mask                                            (0x00000001)
#define SYS_LSADC_PG_REG_TEST_OUT_EN(data)                                           (0x00000001&((data)<<0))
#define SYS_LSADC_PG_REG_TEST_OUT_EN_src(data)                                       ((0x00000001&(data))>>0)
#define SYS_LSADC_PG_get_REG_TEST_OUT_EN(data)                                       ((0x00000001&(data))>>0)


#define SYS_SCAN_CTRL                                                                0x98000350
#define SYS_SCAN_CTRL_reg_addr                                                       "0x98000350"
#define SYS_SCAN_CTRL_reg                                                            0x98000350
#define set_SYS_SCAN_CTRL_reg(data)   (*((volatile unsigned int*) SYS_SCAN_CTRL_reg)=data)
#define get_SYS_SCAN_CTRL_reg   (*((volatile unsigned int*) SYS_SCAN_CTRL_reg))
#define SYS_SCAN_CTRL_inst_adr                                                       "0x00D4"
#define SYS_SCAN_CTRL_inst                                                           0x00D4
#define SYS_SCAN_CTRL_scan_occ_chain_sel_shift                                       (0)
#define SYS_SCAN_CTRL_scan_occ_chain_sel_mask                                        (0x00000001)
#define SYS_SCAN_CTRL_scan_occ_chain_sel(data)                                       (0x00000001&((data)<<0))
#define SYS_SCAN_CTRL_scan_occ_chain_sel_src(data)                                   ((0x00000001&(data))>>0)
#define SYS_SCAN_CTRL_get_scan_occ_chain_sel(data)                                   ((0x00000001&(data))>>0)


#define SYS_DISP_SRAM_PWR0                                                           0x98000360
#define SYS_DISP_SRAM_PWR0_reg_addr                                                  "0x98000360"
#define SYS_DISP_SRAM_PWR0_reg                                                       0x98000360
#define set_SYS_DISP_SRAM_PWR0_reg(data)   (*((volatile unsigned int*) SYS_DISP_SRAM_PWR0_reg)=data)
#define get_SYS_DISP_SRAM_PWR0_reg   (*((volatile unsigned int*) SYS_DISP_SRAM_PWR0_reg))
#define SYS_DISP_SRAM_PWR0_inst_adr                                                  "0x00D8"
#define SYS_DISP_SRAM_PWR0_inst                                                      0x00D8
#define SYS_DISP_SRAM_PWR0_L2H_DELAY_CYCLE_shift                                     (0)
#define SYS_DISP_SRAM_PWR0_L2H_DELAY_CYCLE_mask                                      (0xFFFFFFFF)
#define SYS_DISP_SRAM_PWR0_L2H_DELAY_CYCLE(data)                                     (0xFFFFFFFF&((data)<<0))
#define SYS_DISP_SRAM_PWR0_L2H_DELAY_CYCLE_src(data)                                 ((0xFFFFFFFF&(data))>>0)
#define SYS_DISP_SRAM_PWR0_get_L2H_DELAY_CYCLE(data)                                 ((0xFFFFFFFF&(data))>>0)


#define SYS_DISP_SRAM_PWR1                                                           0x98000364
#define SYS_DISP_SRAM_PWR1_reg_addr                                                  "0x98000364"
#define SYS_DISP_SRAM_PWR1_reg                                                       0x98000364
#define set_SYS_DISP_SRAM_PWR1_reg(data)   (*((volatile unsigned int*) SYS_DISP_SRAM_PWR1_reg)=data)
#define get_SYS_DISP_SRAM_PWR1_reg   (*((volatile unsigned int*) SYS_DISP_SRAM_PWR1_reg))
#define SYS_DISP_SRAM_PWR1_inst_adr                                                  "0x00D9"
#define SYS_DISP_SRAM_PWR1_inst                                                      0x00D9
#define SYS_DISP_SRAM_PWR1_H2L_DELAY_CYCLE_shift                                     (0)
#define SYS_DISP_SRAM_PWR1_H2L_DELAY_CYCLE_mask                                      (0xFFFFFFFF)
#define SYS_DISP_SRAM_PWR1_H2L_DELAY_CYCLE(data)                                     (0xFFFFFFFF&((data)<<0))
#define SYS_DISP_SRAM_PWR1_H2L_DELAY_CYCLE_src(data)                                 ((0xFFFFFFFF&(data))>>0)
#define SYS_DISP_SRAM_PWR1_get_H2L_DELAY_CYCLE(data)                                 ((0xFFFFFFFF&(data))>>0)


#define SYS_DISP_SRAM_PWR2                                                           0x98000368
#define SYS_DISP_SRAM_PWR2_reg_addr                                                  "0x98000368"
#define SYS_DISP_SRAM_PWR2_reg                                                       0x98000368
#define set_SYS_DISP_SRAM_PWR2_reg(data)   (*((volatile unsigned int*) SYS_DISP_SRAM_PWR2_reg)=data)
#define get_SYS_DISP_SRAM_PWR2_reg   (*((volatile unsigned int*) SYS_DISP_SRAM_PWR2_reg))
#define SYS_DISP_SRAM_PWR2_inst_adr                                                  "0x00DA"
#define SYS_DISP_SRAM_PWR2_inst                                                      0x00DA
#define SYS_DISP_SRAM_PWR2_SD_REG_shift                                              (0)
#define SYS_DISP_SRAM_PWR2_SD_REG_mask                                               (0xFFFFFFFF)
#define SYS_DISP_SRAM_PWR2_SD_REG(data)                                              (0xFFFFFFFF&((data)<<0))
#define SYS_DISP_SRAM_PWR2_SD_REG_src(data)                                          ((0xFFFFFFFF&(data))>>0)
#define SYS_DISP_SRAM_PWR2_get_SD_REG(data)                                          ((0xFFFFFFFF&(data))>>0)


#define SYS_DISP_SRAM_PWR3                                                           0x9800036c
#define SYS_DISP_SRAM_PWR3_reg_addr                                                  "0x9800036C"
#define SYS_DISP_SRAM_PWR3_reg                                                       0x9800036C
#define set_SYS_DISP_SRAM_PWR3_reg(data)   (*((volatile unsigned int*) SYS_DISP_SRAM_PWR3_reg)=data)
#define get_SYS_DISP_SRAM_PWR3_reg   (*((volatile unsigned int*) SYS_DISP_SRAM_PWR3_reg))
#define SYS_DISP_SRAM_PWR3_inst_adr                                                  "0x00DB"
#define SYS_DISP_SRAM_PWR3_inst                                                      0x00DB
#define SYS_DISP_SRAM_PWR3_MUX_REG_shift                                             (0)
#define SYS_DISP_SRAM_PWR3_MUX_REG_mask                                              (0xFFFFFFFF)
#define SYS_DISP_SRAM_PWR3_MUX_REG(data)                                             (0xFFFFFFFF&((data)<<0))
#define SYS_DISP_SRAM_PWR3_MUX_REG_src(data)                                         ((0xFFFFFFFF&(data))>>0)
#define SYS_DISP_SRAM_PWR3_get_MUX_REG(data)                                         ((0xFFFFFFFF&(data))>>0)


#define SYS_DISP_SRAM_PWR4                                                           0x98000370
#define SYS_DISP_SRAM_PWR4_reg_addr                                                  "0x98000370"
#define SYS_DISP_SRAM_PWR4_reg                                                       0x98000370
#define set_SYS_DISP_SRAM_PWR4_reg(data)   (*((volatile unsigned int*) SYS_DISP_SRAM_PWR4_reg)=data)
#define get_SYS_DISP_SRAM_PWR4_reg   (*((volatile unsigned int*) SYS_DISP_SRAM_PWR4_reg))
#define SYS_DISP_SRAM_PWR4_inst_adr                                                  "0x00DC"
#define SYS_DISP_SRAM_PWR4_inst                                                      0x00DC
#define SYS_DISP_SRAM_PWR4_CTRL_shift                                                (0)
#define SYS_DISP_SRAM_PWR4_CTRL_mask                                                 (0xFFFFFFFF)
#define SYS_DISP_SRAM_PWR4_CTRL(data)                                                (0xFFFFFFFF&((data)<<0))
#define SYS_DISP_SRAM_PWR4_CTRL_src(data)                                            ((0xFFFFFFFF&(data))>>0)
#define SYS_DISP_SRAM_PWR4_get_CTRL(data)                                            ((0xFFFFFFFF&(data))>>0)


#define SYS_DISP_SRAM_PWR5                                                           0x98000374
#define SYS_DISP_SRAM_PWR5_reg_addr                                                  "0x98000374"
#define SYS_DISP_SRAM_PWR5_reg                                                       0x98000374
#define set_SYS_DISP_SRAM_PWR5_reg(data)   (*((volatile unsigned int*) SYS_DISP_SRAM_PWR5_reg)=data)
#define get_SYS_DISP_SRAM_PWR5_reg   (*((volatile unsigned int*) SYS_DISP_SRAM_PWR5_reg))
#define SYS_DISP_SRAM_PWR5_inst_adr                                                  "0x00DD"
#define SYS_DISP_SRAM_PWR5_inst                                                      0x00DD
#define SYS_DISP_SRAM_PWR5_disp_sram_int_shift                                       (2)
#define SYS_DISP_SRAM_PWR5_disp_sram_int_mask                                        (0x00000004)
#define SYS_DISP_SRAM_PWR5_disp_sram_int(data)                                       (0x00000004&((data)<<2))
#define SYS_DISP_SRAM_PWR5_disp_sram_int_src(data)                                   ((0x00000004&(data))>>2)
#define SYS_DISP_SRAM_PWR5_get_disp_sram_int(data)                                   ((0x00000004&(data))>>2)
#define SYS_DISP_SRAM_PWR5_write_data_shift                                          (0)
#define SYS_DISP_SRAM_PWR5_write_data_mask                                           (0x00000001)
#define SYS_DISP_SRAM_PWR5_write_data(data)                                          (0x00000001&((data)<<0))
#define SYS_DISP_SRAM_PWR5_write_data_src(data)                                      ((0x00000001&(data))>>0)
#define SYS_DISP_SRAM_PWR5_get_write_data(data)                                      ((0x00000001&(data))>>0)


#define SYS_DISP_SRAM_PWR6                                                           0x98000378
#define SYS_DISP_SRAM_PWR6_reg_addr                                                  "0x98000378"
#define SYS_DISP_SRAM_PWR6_reg                                                       0x98000378
#define set_SYS_DISP_SRAM_PWR6_reg(data)   (*((volatile unsigned int*) SYS_DISP_SRAM_PWR6_reg)=data)
#define get_SYS_DISP_SRAM_PWR6_reg   (*((volatile unsigned int*) SYS_DISP_SRAM_PWR6_reg))
#define SYS_DISP_SRAM_PWR6_inst_adr                                                  "0x00DE"
#define SYS_DISP_SRAM_PWR6_inst                                                      0x00DE
#define SYS_DISP_SRAM_PWR6_last_delay_cycle_shift                                    (0)
#define SYS_DISP_SRAM_PWR6_last_delay_cycle_mask                                     (0xFFFFFFFF)
#define SYS_DISP_SRAM_PWR6_last_delay_cycle(data)                                    (0xFFFFFFFF&((data)<<0))
#define SYS_DISP_SRAM_PWR6_last_delay_cycle_src(data)                                ((0xFFFFFFFF&(data))>>0)
#define SYS_DISP_SRAM_PWR6_get_last_delay_cycle(data)                                ((0xFFFFFFFF&(data))>>0)


#define SYS_DISP_SRAM_PWR7                                                           0x9800037c
#define SYS_DISP_SRAM_PWR7_reg_addr                                                  "0x9800037C"
#define SYS_DISP_SRAM_PWR7_reg                                                       0x9800037C
#define set_SYS_DISP_SRAM_PWR7_reg(data)   (*((volatile unsigned int*) SYS_DISP_SRAM_PWR7_reg)=data)
#define get_SYS_DISP_SRAM_PWR7_reg   (*((volatile unsigned int*) SYS_DISP_SRAM_PWR7_reg))
#define SYS_DISP_SRAM_PWR7_inst_adr                                                  "0x00DF"
#define SYS_DISP_SRAM_PWR7_inst                                                      0x00DF
#define SYS_DISP_SRAM_PWR7_pg_switch_info_shift                                      (0)
#define SYS_DISP_SRAM_PWR7_pg_switch_info_mask                                       (0xFFFFFFFF)
#define SYS_DISP_SRAM_PWR7_pg_switch_info(data)                                      (0xFFFFFFFF&((data)<<0))
#define SYS_DISP_SRAM_PWR7_pg_switch_info_src(data)                                  ((0xFFFFFFFF&(data))>>0)
#define SYS_DISP_SRAM_PWR7_get_pg_switch_info(data)                                  ((0xFFFFFFFF&(data))>>0)


#define SYS_VE1_SRAM_PWR0                                                            0x98000380
#define SYS_VE1_SRAM_PWR0_reg_addr                                                   "0x98000380"
#define SYS_VE1_SRAM_PWR0_reg                                                        0x98000380
#define set_SYS_VE1_SRAM_PWR0_reg(data)   (*((volatile unsigned int*) SYS_VE1_SRAM_PWR0_reg)=data)
#define get_SYS_VE1_SRAM_PWR0_reg   (*((volatile unsigned int*) SYS_VE1_SRAM_PWR0_reg))
#define SYS_VE1_SRAM_PWR0_inst_adr                                                   "0x00E0"
#define SYS_VE1_SRAM_PWR0_inst                                                       0x00E0
#define SYS_VE1_SRAM_PWR0_L2H_DELAY_CYCLE_shift                                      (0)
#define SYS_VE1_SRAM_PWR0_L2H_DELAY_CYCLE_mask                                       (0xFFFFFFFF)
#define SYS_VE1_SRAM_PWR0_L2H_DELAY_CYCLE(data)                                      (0xFFFFFFFF&((data)<<0))
#define SYS_VE1_SRAM_PWR0_L2H_DELAY_CYCLE_src(data)                                  ((0xFFFFFFFF&(data))>>0)
#define SYS_VE1_SRAM_PWR0_get_L2H_DELAY_CYCLE(data)                                  ((0xFFFFFFFF&(data))>>0)


#define SYS_VE1_SRAM_PWR1                                                            0x98000384
#define SYS_VE1_SRAM_PWR1_reg_addr                                                   "0x98000384"
#define SYS_VE1_SRAM_PWR1_reg                                                        0x98000384
#define set_SYS_VE1_SRAM_PWR1_reg(data)   (*((volatile unsigned int*) SYS_VE1_SRAM_PWR1_reg)=data)
#define get_SYS_VE1_SRAM_PWR1_reg   (*((volatile unsigned int*) SYS_VE1_SRAM_PWR1_reg))
#define SYS_VE1_SRAM_PWR1_inst_adr                                                   "0x00E1"
#define SYS_VE1_SRAM_PWR1_inst                                                       0x00E1
#define SYS_VE1_SRAM_PWR1_H2L_DELAY_CYCLE_shift                                      (0)
#define SYS_VE1_SRAM_PWR1_H2L_DELAY_CYCLE_mask                                       (0xFFFFFFFF)
#define SYS_VE1_SRAM_PWR1_H2L_DELAY_CYCLE(data)                                      (0xFFFFFFFF&((data)<<0))
#define SYS_VE1_SRAM_PWR1_H2L_DELAY_CYCLE_src(data)                                  ((0xFFFFFFFF&(data))>>0)
#define SYS_VE1_SRAM_PWR1_get_H2L_DELAY_CYCLE(data)                                  ((0xFFFFFFFF&(data))>>0)


#define SYS_VE1_SRAM_PWR2                                                            0x98000388
#define SYS_VE1_SRAM_PWR2_reg_addr                                                   "0x98000388"
#define SYS_VE1_SRAM_PWR2_reg                                                        0x98000388
#define set_SYS_VE1_SRAM_PWR2_reg(data)   (*((volatile unsigned int*) SYS_VE1_SRAM_PWR2_reg)=data)
#define get_SYS_VE1_SRAM_PWR2_reg   (*((volatile unsigned int*) SYS_VE1_SRAM_PWR2_reg))
#define SYS_VE1_SRAM_PWR2_inst_adr                                                   "0x00E2"
#define SYS_VE1_SRAM_PWR2_inst                                                       0x00E2
#define SYS_VE1_SRAM_PWR2_SD_REG_shift                                               (0)
#define SYS_VE1_SRAM_PWR2_SD_REG_mask                                                (0xFFFFFFFF)
#define SYS_VE1_SRAM_PWR2_SD_REG(data)                                               (0xFFFFFFFF&((data)<<0))
#define SYS_VE1_SRAM_PWR2_SD_REG_src(data)                                           ((0xFFFFFFFF&(data))>>0)
#define SYS_VE1_SRAM_PWR2_get_SD_REG(data)                                           ((0xFFFFFFFF&(data))>>0)


#define SYS_VE1_SRAM_PWR3                                                            0x9800038c
#define SYS_VE1_SRAM_PWR3_reg_addr                                                   "0x9800038C"
#define SYS_VE1_SRAM_PWR3_reg                                                        0x9800038C
#define set_SYS_VE1_SRAM_PWR3_reg(data)   (*((volatile unsigned int*) SYS_VE1_SRAM_PWR3_reg)=data)
#define get_SYS_VE1_SRAM_PWR3_reg   (*((volatile unsigned int*) SYS_VE1_SRAM_PWR3_reg))
#define SYS_VE1_SRAM_PWR3_inst_adr                                                   "0x00E3"
#define SYS_VE1_SRAM_PWR3_inst                                                       0x00E3
#define SYS_VE1_SRAM_PWR3_MUX_REG_shift                                              (0)
#define SYS_VE1_SRAM_PWR3_MUX_REG_mask                                               (0xFFFFFFFF)
#define SYS_VE1_SRAM_PWR3_MUX_REG(data)                                              (0xFFFFFFFF&((data)<<0))
#define SYS_VE1_SRAM_PWR3_MUX_REG_src(data)                                          ((0xFFFFFFFF&(data))>>0)
#define SYS_VE1_SRAM_PWR3_get_MUX_REG(data)                                          ((0xFFFFFFFF&(data))>>0)


#define SYS_VE1_SRAM_PWR4                                                            0x98000390
#define SYS_VE1_SRAM_PWR4_reg_addr                                                   "0x98000390"
#define SYS_VE1_SRAM_PWR4_reg                                                        0x98000390
#define set_SYS_VE1_SRAM_PWR4_reg(data)   (*((volatile unsigned int*) SYS_VE1_SRAM_PWR4_reg)=data)
#define get_SYS_VE1_SRAM_PWR4_reg   (*((volatile unsigned int*) SYS_VE1_SRAM_PWR4_reg))
#define SYS_VE1_SRAM_PWR4_inst_adr                                                   "0x00E4"
#define SYS_VE1_SRAM_PWR4_inst                                                       0x00E4
#define SYS_VE1_SRAM_PWR4_CTRL_shift                                                 (0)
#define SYS_VE1_SRAM_PWR4_CTRL_mask                                                  (0xFFFFFFFF)
#define SYS_VE1_SRAM_PWR4_CTRL(data)                                                 (0xFFFFFFFF&((data)<<0))
#define SYS_VE1_SRAM_PWR4_CTRL_src(data)                                             ((0xFFFFFFFF&(data))>>0)
#define SYS_VE1_SRAM_PWR4_get_CTRL(data)                                             ((0xFFFFFFFF&(data))>>0)


#define SYS_GPU_SRAM_PWR0                                                            0x98000394
#define SYS_GPU_SRAM_PWR0_reg_addr                                                   "0x98000394"
#define SYS_GPU_SRAM_PWR0_reg                                                        0x98000394
#define set_SYS_GPU_SRAM_PWR0_reg(data)   (*((volatile unsigned int*) SYS_GPU_SRAM_PWR0_reg)=data)
#define get_SYS_GPU_SRAM_PWR0_reg   (*((volatile unsigned int*) SYS_GPU_SRAM_PWR0_reg))
#define SYS_GPU_SRAM_PWR0_inst_adr                                                   "0x00E5"
#define SYS_GPU_SRAM_PWR0_inst                                                       0x00E5
#define SYS_GPU_SRAM_PWR0_L2H_DELAY_CYCLE_shift                                      (0)
#define SYS_GPU_SRAM_PWR0_L2H_DELAY_CYCLE_mask                                       (0xFFFFFFFF)
#define SYS_GPU_SRAM_PWR0_L2H_DELAY_CYCLE(data)                                      (0xFFFFFFFF&((data)<<0))
#define SYS_GPU_SRAM_PWR0_L2H_DELAY_CYCLE_src(data)                                  ((0xFFFFFFFF&(data))>>0)
#define SYS_GPU_SRAM_PWR0_get_L2H_DELAY_CYCLE(data)                                  ((0xFFFFFFFF&(data))>>0)


#define SYS_GPU_SRAM_PWR1                                                            0x98000398
#define SYS_GPU_SRAM_PWR1_reg_addr                                                   "0x98000398"
#define SYS_GPU_SRAM_PWR1_reg                                                        0x98000398
#define set_SYS_GPU_SRAM_PWR1_reg(data)   (*((volatile unsigned int*) SYS_GPU_SRAM_PWR1_reg)=data)
#define get_SYS_GPU_SRAM_PWR1_reg   (*((volatile unsigned int*) SYS_GPU_SRAM_PWR1_reg))
#define SYS_GPU_SRAM_PWR1_inst_adr                                                   "0x00E6"
#define SYS_GPU_SRAM_PWR1_inst                                                       0x00E6
#define SYS_GPU_SRAM_PWR1_H2L_DELAY_CYCLE_shift                                      (0)
#define SYS_GPU_SRAM_PWR1_H2L_DELAY_CYCLE_mask                                       (0xFFFFFFFF)
#define SYS_GPU_SRAM_PWR1_H2L_DELAY_CYCLE(data)                                      (0xFFFFFFFF&((data)<<0))
#define SYS_GPU_SRAM_PWR1_H2L_DELAY_CYCLE_src(data)                                  ((0xFFFFFFFF&(data))>>0)
#define SYS_GPU_SRAM_PWR1_get_H2L_DELAY_CYCLE(data)                                  ((0xFFFFFFFF&(data))>>0)


#define SYS_GPU_SRAM_PWR2                                                            0x9800039c
#define SYS_GPU_SRAM_PWR2_reg_addr                                                   "0x9800039C"
#define SYS_GPU_SRAM_PWR2_reg                                                        0x9800039C
#define set_SYS_GPU_SRAM_PWR2_reg(data)   (*((volatile unsigned int*) SYS_GPU_SRAM_PWR2_reg)=data)
#define get_SYS_GPU_SRAM_PWR2_reg   (*((volatile unsigned int*) SYS_GPU_SRAM_PWR2_reg))
#define SYS_GPU_SRAM_PWR2_inst_adr                                                   "0x00E7"
#define SYS_GPU_SRAM_PWR2_inst                                                       0x00E7
#define SYS_GPU_SRAM_PWR2_SD_REG_shift                                               (0)
#define SYS_GPU_SRAM_PWR2_SD_REG_mask                                                (0xFFFFFFFF)
#define SYS_GPU_SRAM_PWR2_SD_REG(data)                                               (0xFFFFFFFF&((data)<<0))
#define SYS_GPU_SRAM_PWR2_SD_REG_src(data)                                           ((0xFFFFFFFF&(data))>>0)
#define SYS_GPU_SRAM_PWR2_get_SD_REG(data)                                           ((0xFFFFFFFF&(data))>>0)


#define SYS_GPU_SRAM_PWR3                                                            0x980003a0
#define SYS_GPU_SRAM_PWR3_reg_addr                                                   "0x980003A0"
#define SYS_GPU_SRAM_PWR3_reg                                                        0x980003A0
#define set_SYS_GPU_SRAM_PWR3_reg(data)   (*((volatile unsigned int*) SYS_GPU_SRAM_PWR3_reg)=data)
#define get_SYS_GPU_SRAM_PWR3_reg   (*((volatile unsigned int*) SYS_GPU_SRAM_PWR3_reg))
#define SYS_GPU_SRAM_PWR3_inst_adr                                                   "0x00E8"
#define SYS_GPU_SRAM_PWR3_inst                                                       0x00E8
#define SYS_GPU_SRAM_PWR3_MUX_REG_shift                                              (0)
#define SYS_GPU_SRAM_PWR3_MUX_REG_mask                                               (0xFFFFFFFF)
#define SYS_GPU_SRAM_PWR3_MUX_REG(data)                                              (0xFFFFFFFF&((data)<<0))
#define SYS_GPU_SRAM_PWR3_MUX_REG_src(data)                                          ((0xFFFFFFFF&(data))>>0)
#define SYS_GPU_SRAM_PWR3_get_MUX_REG(data)                                          ((0xFFFFFFFF&(data))>>0)


#define SYS_GPU_SRAM_PWR4                                                            0x980003a4
#define SYS_GPU_SRAM_PWR4_reg_addr                                                   "0x980003A4"
#define SYS_GPU_SRAM_PWR4_reg                                                        0x980003A4
#define set_SYS_GPU_SRAM_PWR4_reg(data)   (*((volatile unsigned int*) SYS_GPU_SRAM_PWR4_reg)=data)
#define get_SYS_GPU_SRAM_PWR4_reg   (*((volatile unsigned int*) SYS_GPU_SRAM_PWR4_reg))
#define SYS_GPU_SRAM_PWR4_inst_adr                                                   "0x00E9"
#define SYS_GPU_SRAM_PWR4_inst                                                       0x00E9
#define SYS_GPU_SRAM_PWR4_CTRL_shift                                                 (0)
#define SYS_GPU_SRAM_PWR4_CTRL_mask                                                  (0xFFFFFFFF)
#define SYS_GPU_SRAM_PWR4_CTRL(data)                                                 (0xFFFFFFFF&((data)<<0))
#define SYS_GPU_SRAM_PWR4_CTRL_src(data)                                             ((0xFFFFFFFF&(data))>>0)
#define SYS_GPU_SRAM_PWR4_get_CTRL(data)                                             ((0xFFFFFFFF&(data))>>0)


#define SYS_VE1_SRAM_PWR5                                                            0x980003a8
#define SYS_VE1_SRAM_PWR5_reg_addr                                                   "0x980003A8"
#define SYS_VE1_SRAM_PWR5_reg                                                        0x980003A8
#define set_SYS_VE1_SRAM_PWR5_reg(data)   (*((volatile unsigned int*) SYS_VE1_SRAM_PWR5_reg)=data)
#define get_SYS_VE1_SRAM_PWR5_reg   (*((volatile unsigned int*) SYS_VE1_SRAM_PWR5_reg))
#define SYS_VE1_SRAM_PWR5_inst_adr                                                   "0x00EA"
#define SYS_VE1_SRAM_PWR5_inst                                                       0x00EA
#define SYS_VE1_SRAM_PWR5_ve1_sram_int_shift                                         (2)
#define SYS_VE1_SRAM_PWR5_ve1_sram_int_mask                                          (0x00000004)
#define SYS_VE1_SRAM_PWR5_ve1_sram_int(data)                                         (0x00000004&((data)<<2))
#define SYS_VE1_SRAM_PWR5_ve1_sram_int_src(data)                                     ((0x00000004&(data))>>2)
#define SYS_VE1_SRAM_PWR5_get_ve1_sram_int(data)                                     ((0x00000004&(data))>>2)
#define SYS_VE1_SRAM_PWR5_write_data_shift                                           (0)
#define SYS_VE1_SRAM_PWR5_write_data_mask                                            (0x00000001)
#define SYS_VE1_SRAM_PWR5_write_data(data)                                           (0x00000001&((data)<<0))
#define SYS_VE1_SRAM_PWR5_write_data_src(data)                                       ((0x00000001&(data))>>0)
#define SYS_VE1_SRAM_PWR5_get_write_data(data)                                       ((0x00000001&(data))>>0)


#define SYS_GPU_SRAM_PWR5                                                            0x980003ac
#define SYS_GPU_SRAM_PWR5_reg_addr                                                   "0x980003AC"
#define SYS_GPU_SRAM_PWR5_reg                                                        0x980003AC
#define set_SYS_GPU_SRAM_PWR5_reg(data)   (*((volatile unsigned int*) SYS_GPU_SRAM_PWR5_reg)=data)
#define get_SYS_GPU_SRAM_PWR5_reg   (*((volatile unsigned int*) SYS_GPU_SRAM_PWR5_reg))
#define SYS_GPU_SRAM_PWR5_inst_adr                                                   "0x00EB"
#define SYS_GPU_SRAM_PWR5_inst                                                       0x00EB
#define SYS_GPU_SRAM_PWR5_gpu_sram_int_shift                                         (2)
#define SYS_GPU_SRAM_PWR5_gpu_sram_int_mask                                          (0x00000004)
#define SYS_GPU_SRAM_PWR5_gpu_sram_int(data)                                         (0x00000004&((data)<<2))
#define SYS_GPU_SRAM_PWR5_gpu_sram_int_src(data)                                     ((0x00000004&(data))>>2)
#define SYS_GPU_SRAM_PWR5_get_gpu_sram_int(data)                                     ((0x00000004&(data))>>2)
#define SYS_GPU_SRAM_PWR5_write_data_shift                                           (0)
#define SYS_GPU_SRAM_PWR5_write_data_mask                                            (0x00000001)
#define SYS_GPU_SRAM_PWR5_write_data(data)                                           (0x00000001&((data)<<0))
#define SYS_GPU_SRAM_PWR5_write_data_src(data)                                       ((0x00000001&(data))>>0)
#define SYS_GPU_SRAM_PWR5_get_write_data(data)                                       ((0x00000001&(data))>>0)


#define SYS_VE1_SRAM_PWR6                                                            0x980003b0
#define SYS_VE1_SRAM_PWR6_reg_addr                                                   "0x980003B0"
#define SYS_VE1_SRAM_PWR6_reg                                                        0x980003B0
#define set_SYS_VE1_SRAM_PWR6_reg(data)   (*((volatile unsigned int*) SYS_VE1_SRAM_PWR6_reg)=data)
#define get_SYS_VE1_SRAM_PWR6_reg   (*((volatile unsigned int*) SYS_VE1_SRAM_PWR6_reg))
#define SYS_VE1_SRAM_PWR6_inst_adr                                                   "0x00EC"
#define SYS_VE1_SRAM_PWR6_inst                                                       0x00EC
#define SYS_VE1_SRAM_PWR6_last_delay_cycle_shift                                     (0)
#define SYS_VE1_SRAM_PWR6_last_delay_cycle_mask                                      (0xFFFFFFFF)
#define SYS_VE1_SRAM_PWR6_last_delay_cycle(data)                                     (0xFFFFFFFF&((data)<<0))
#define SYS_VE1_SRAM_PWR6_last_delay_cycle_src(data)                                 ((0xFFFFFFFF&(data))>>0)
#define SYS_VE1_SRAM_PWR6_get_last_delay_cycle(data)                                 ((0xFFFFFFFF&(data))>>0)


#define SYS_GPU_SRAM_PWR6                                                            0x980003b4
#define SYS_GPU_SRAM_PWR6_reg_addr                                                   "0x980003B4"
#define SYS_GPU_SRAM_PWR6_reg                                                        0x980003B4
#define set_SYS_GPU_SRAM_PWR6_reg(data)   (*((volatile unsigned int*) SYS_GPU_SRAM_PWR6_reg)=data)
#define get_SYS_GPU_SRAM_PWR6_reg   (*((volatile unsigned int*) SYS_GPU_SRAM_PWR6_reg))
#define SYS_GPU_SRAM_PWR6_inst_adr                                                   "0x00ED"
#define SYS_GPU_SRAM_PWR6_inst                                                       0x00ED
#define SYS_GPU_SRAM_PWR6_last_delay_cycle_shift                                     (0)
#define SYS_GPU_SRAM_PWR6_last_delay_cycle_mask                                      (0xFFFFFFFF)
#define SYS_GPU_SRAM_PWR6_last_delay_cycle(data)                                     (0xFFFFFFFF&((data)<<0))
#define SYS_GPU_SRAM_PWR6_last_delay_cycle_src(data)                                 ((0xFFFFFFFF&(data))>>0)
#define SYS_GPU_SRAM_PWR6_get_last_delay_cycle(data)                                 ((0xFFFFFFFF&(data))>>0)


#define SYS_VE1_SRAM_PWR7                                                            0x980003b8
#define SYS_VE1_SRAM_PWR7_reg_addr                                                   "0x980003B8"
#define SYS_VE1_SRAM_PWR7_reg                                                        0x980003B8
#define set_SYS_VE1_SRAM_PWR7_reg(data)   (*((volatile unsigned int*) SYS_VE1_SRAM_PWR7_reg)=data)
#define get_SYS_VE1_SRAM_PWR7_reg   (*((volatile unsigned int*) SYS_VE1_SRAM_PWR7_reg))
#define SYS_VE1_SRAM_PWR7_inst_adr                                                   "0x00EE"
#define SYS_VE1_SRAM_PWR7_inst                                                       0x00EE
#define SYS_VE1_SRAM_PWR7_pg_switch_info_shift                                       (0)
#define SYS_VE1_SRAM_PWR7_pg_switch_info_mask                                        (0xFFFFFFFF)
#define SYS_VE1_SRAM_PWR7_pg_switch_info(data)                                       (0xFFFFFFFF&((data)<<0))
#define SYS_VE1_SRAM_PWR7_pg_switch_info_src(data)                                   ((0xFFFFFFFF&(data))>>0)
#define SYS_VE1_SRAM_PWR7_get_pg_switch_info(data)                                   ((0xFFFFFFFF&(data))>>0)


#define SYS_GPU_SRAM_PWR7                                                            0x980003bc
#define SYS_GPU_SRAM_PWR7_reg_addr                                                   "0x980003BC"
#define SYS_GPU_SRAM_PWR7_reg                                                        0x980003BC
#define set_SYS_GPU_SRAM_PWR7_reg(data)   (*((volatile unsigned int*) SYS_GPU_SRAM_PWR7_reg)=data)
#define get_SYS_GPU_SRAM_PWR7_reg   (*((volatile unsigned int*) SYS_GPU_SRAM_PWR7_reg))
#define SYS_GPU_SRAM_PWR7_inst_adr                                                   "0x00EF"
#define SYS_GPU_SRAM_PWR7_inst                                                       0x00EF
#define SYS_GPU_SRAM_PWR7_pg_switch_info_shift                                       (0)
#define SYS_GPU_SRAM_PWR7_pg_switch_info_mask                                        (0xFFFFFFFF)
#define SYS_GPU_SRAM_PWR7_pg_switch_info(data)                                       (0xFFFFFFFF&((data)<<0))
#define SYS_GPU_SRAM_PWR7_pg_switch_info_src(data)                                   ((0xFFFFFFFF&(data))>>0)
#define SYS_GPU_SRAM_PWR7_get_pg_switch_info(data)                                   ((0xFFFFFFFF&(data))>>0)


#define SYS_VE2_SRAM_PWR0                                                            0x980003c0
#define SYS_VE2_SRAM_PWR0_reg_addr                                                   "0x980003C0"
#define SYS_VE2_SRAM_PWR0_reg                                                        0x980003C0
#define set_SYS_VE2_SRAM_PWR0_reg(data)   (*((volatile unsigned int*) SYS_VE2_SRAM_PWR0_reg)=data)
#define get_SYS_VE2_SRAM_PWR0_reg   (*((volatile unsigned int*) SYS_VE2_SRAM_PWR0_reg))
#define SYS_VE2_SRAM_PWR0_inst_adr                                                   "0x00F0"
#define SYS_VE2_SRAM_PWR0_inst                                                       0x00F0
#define SYS_VE2_SRAM_PWR0_L2H_DELAY_CYCLE_shift                                      (0)
#define SYS_VE2_SRAM_PWR0_L2H_DELAY_CYCLE_mask                                       (0xFFFFFFFF)
#define SYS_VE2_SRAM_PWR0_L2H_DELAY_CYCLE(data)                                      (0xFFFFFFFF&((data)<<0))
#define SYS_VE2_SRAM_PWR0_L2H_DELAY_CYCLE_src(data)                                  ((0xFFFFFFFF&(data))>>0)
#define SYS_VE2_SRAM_PWR0_get_L2H_DELAY_CYCLE(data)                                  ((0xFFFFFFFF&(data))>>0)


#define SYS_VE2_SRAM_PWR1                                                            0x980003c4
#define SYS_VE2_SRAM_PWR1_reg_addr                                                   "0x980003C4"
#define SYS_VE2_SRAM_PWR1_reg                                                        0x980003C4
#define set_SYS_VE2_SRAM_PWR1_reg(data)   (*((volatile unsigned int*) SYS_VE2_SRAM_PWR1_reg)=data)
#define get_SYS_VE2_SRAM_PWR1_reg   (*((volatile unsigned int*) SYS_VE2_SRAM_PWR1_reg))
#define SYS_VE2_SRAM_PWR1_inst_adr                                                   "0x00F1"
#define SYS_VE2_SRAM_PWR1_inst                                                       0x00F1
#define SYS_VE2_SRAM_PWR1_H2L_DELAY_CYCLE_shift                                      (0)
#define SYS_VE2_SRAM_PWR1_H2L_DELAY_CYCLE_mask                                       (0xFFFFFFFF)
#define SYS_VE2_SRAM_PWR1_H2L_DELAY_CYCLE(data)                                      (0xFFFFFFFF&((data)<<0))
#define SYS_VE2_SRAM_PWR1_H2L_DELAY_CYCLE_src(data)                                  ((0xFFFFFFFF&(data))>>0)
#define SYS_VE2_SRAM_PWR1_get_H2L_DELAY_CYCLE(data)                                  ((0xFFFFFFFF&(data))>>0)


#define SYS_VE2_SRAM_PWR2                                                            0x980003c8
#define SYS_VE2_SRAM_PWR2_reg_addr                                                   "0x980003C8"
#define SYS_VE2_SRAM_PWR2_reg                                                        0x980003C8
#define set_SYS_VE2_SRAM_PWR2_reg(data)   (*((volatile unsigned int*) SYS_VE2_SRAM_PWR2_reg)=data)
#define get_SYS_VE2_SRAM_PWR2_reg   (*((volatile unsigned int*) SYS_VE2_SRAM_PWR2_reg))
#define SYS_VE2_SRAM_PWR2_inst_adr                                                   "0x00F2"
#define SYS_VE2_SRAM_PWR2_inst                                                       0x00F2
#define SYS_VE2_SRAM_PWR2_SD_REG_shift                                               (0)
#define SYS_VE2_SRAM_PWR2_SD_REG_mask                                                (0xFFFFFFFF)
#define SYS_VE2_SRAM_PWR2_SD_REG(data)                                               (0xFFFFFFFF&((data)<<0))
#define SYS_VE2_SRAM_PWR2_SD_REG_src(data)                                           ((0xFFFFFFFF&(data))>>0)
#define SYS_VE2_SRAM_PWR2_get_SD_REG(data)                                           ((0xFFFFFFFF&(data))>>0)


#define SYS_VE2_SRAM_PWR3                                                            0x980003cc
#define SYS_VE2_SRAM_PWR3_reg_addr                                                   "0x980003CC"
#define SYS_VE2_SRAM_PWR3_reg                                                        0x980003CC
#define set_SYS_VE2_SRAM_PWR3_reg(data)   (*((volatile unsigned int*) SYS_VE2_SRAM_PWR3_reg)=data)
#define get_SYS_VE2_SRAM_PWR3_reg   (*((volatile unsigned int*) SYS_VE2_SRAM_PWR3_reg))
#define SYS_VE2_SRAM_PWR3_inst_adr                                                   "0x00F3"
#define SYS_VE2_SRAM_PWR3_inst                                                       0x00F3
#define SYS_VE2_SRAM_PWR3_MUX_REG_shift                                              (0)
#define SYS_VE2_SRAM_PWR3_MUX_REG_mask                                               (0xFFFFFFFF)
#define SYS_VE2_SRAM_PWR3_MUX_REG(data)                                              (0xFFFFFFFF&((data)<<0))
#define SYS_VE2_SRAM_PWR3_MUX_REG_src(data)                                          ((0xFFFFFFFF&(data))>>0)
#define SYS_VE2_SRAM_PWR3_get_MUX_REG(data)                                          ((0xFFFFFFFF&(data))>>0)


#define SYS_VE2_SRAM_PWR4                                                            0x980003d0
#define SYS_VE2_SRAM_PWR4_reg_addr                                                   "0x980003D0"
#define SYS_VE2_SRAM_PWR4_reg                                                        0x980003D0
#define set_SYS_VE2_SRAM_PWR4_reg(data)   (*((volatile unsigned int*) SYS_VE2_SRAM_PWR4_reg)=data)
#define get_SYS_VE2_SRAM_PWR4_reg   (*((volatile unsigned int*) SYS_VE2_SRAM_PWR4_reg))
#define SYS_VE2_SRAM_PWR4_inst_adr                                                   "0x00F4"
#define SYS_VE2_SRAM_PWR4_inst                                                       0x00F4
#define SYS_VE2_SRAM_PWR4_CTRL_shift                                                 (0)
#define SYS_VE2_SRAM_PWR4_CTRL_mask                                                  (0xFFFFFFFF)
#define SYS_VE2_SRAM_PWR4_CTRL(data)                                                 (0xFFFFFFFF&((data)<<0))
#define SYS_VE2_SRAM_PWR4_CTRL_src(data)                                             ((0xFFFFFFFF&(data))>>0)
#define SYS_VE2_SRAM_PWR4_get_CTRL(data)                                             ((0xFFFFFFFF&(data))>>0)


#define SYS_VE2_SRAM_PWR5                                                            0x980003d4
#define SYS_VE2_SRAM_PWR5_reg_addr                                                   "0x980003D4"
#define SYS_VE2_SRAM_PWR5_reg                                                        0x980003D4
#define set_SYS_VE2_SRAM_PWR5_reg(data)   (*((volatile unsigned int*) SYS_VE2_SRAM_PWR5_reg)=data)
#define get_SYS_VE2_SRAM_PWR5_reg   (*((volatile unsigned int*) SYS_VE2_SRAM_PWR5_reg))
#define SYS_VE2_SRAM_PWR5_inst_adr                                                   "0x00F5"
#define SYS_VE2_SRAM_PWR5_inst                                                       0x00F5
#define SYS_VE2_SRAM_PWR5_ve2_sram_int_shift                                         (2)
#define SYS_VE2_SRAM_PWR5_ve2_sram_int_mask                                          (0x00000004)
#define SYS_VE2_SRAM_PWR5_ve2_sram_int(data)                                         (0x00000004&((data)<<2))
#define SYS_VE2_SRAM_PWR5_ve2_sram_int_src(data)                                     ((0x00000004&(data))>>2)
#define SYS_VE2_SRAM_PWR5_get_ve2_sram_int(data)                                     ((0x00000004&(data))>>2)
#define SYS_VE2_SRAM_PWR5_write_data_shift                                           (0)
#define SYS_VE2_SRAM_PWR5_write_data_mask                                            (0x00000001)
#define SYS_VE2_SRAM_PWR5_write_data(data)                                           (0x00000001&((data)<<0))
#define SYS_VE2_SRAM_PWR5_write_data_src(data)                                       ((0x00000001&(data))>>0)
#define SYS_VE2_SRAM_PWR5_get_write_data(data)                                       ((0x00000001&(data))>>0)


#define SYS_VE2_SRAM_PWR6                                                            0x980003d8
#define SYS_VE2_SRAM_PWR6_reg_addr                                                   "0x980003D8"
#define SYS_VE2_SRAM_PWR6_reg                                                        0x980003D8
#define set_SYS_VE2_SRAM_PWR6_reg(data)   (*((volatile unsigned int*) SYS_VE2_SRAM_PWR6_reg)=data)
#define get_SYS_VE2_SRAM_PWR6_reg   (*((volatile unsigned int*) SYS_VE2_SRAM_PWR6_reg))
#define SYS_VE2_SRAM_PWR6_inst_adr                                                   "0x00F6"
#define SYS_VE2_SRAM_PWR6_inst                                                       0x00F6
#define SYS_VE2_SRAM_PWR6_last_delay_cycle_shift                                     (0)
#define SYS_VE2_SRAM_PWR6_last_delay_cycle_mask                                      (0xFFFFFFFF)
#define SYS_VE2_SRAM_PWR6_last_delay_cycle(data)                                     (0xFFFFFFFF&((data)<<0))
#define SYS_VE2_SRAM_PWR6_last_delay_cycle_src(data)                                 ((0xFFFFFFFF&(data))>>0)
#define SYS_VE2_SRAM_PWR6_get_last_delay_cycle(data)                                 ((0xFFFFFFFF&(data))>>0)


#define SYS_VE2_SRAM_PWR7                                                            0x980003dc
#define SYS_VE2_SRAM_PWR7_reg_addr                                                   "0x980003DC"
#define SYS_VE2_SRAM_PWR7_reg                                                        0x980003DC
#define set_SYS_VE2_SRAM_PWR7_reg(data)   (*((volatile unsigned int*) SYS_VE2_SRAM_PWR7_reg)=data)
#define get_SYS_VE2_SRAM_PWR7_reg   (*((volatile unsigned int*) SYS_VE2_SRAM_PWR7_reg))
#define SYS_VE2_SRAM_PWR7_inst_adr                                                   "0x00F7"
#define SYS_VE2_SRAM_PWR7_inst                                                       0x00F7
#define SYS_VE2_SRAM_PWR7_pg_switch_info_shift                                       (0)
#define SYS_VE2_SRAM_PWR7_pg_switch_info_mask                                        (0xFFFFFFFF)
#define SYS_VE2_SRAM_PWR7_pg_switch_info(data)                                       (0xFFFFFFFF&((data)<<0))
#define SYS_VE2_SRAM_PWR7_pg_switch_info_src(data)                                   ((0xFFFFFFFF&(data))>>0)
#define SYS_VE2_SRAM_PWR7_get_pg_switch_info(data)                                   ((0xFFFFFFFF&(data))>>0)


#define SYS_VE3_SRAM_PWR0                                                            0x980003e0
#define SYS_VE3_SRAM_PWR0_reg_addr                                                   "0x980003E0"
#define SYS_VE3_SRAM_PWR0_reg                                                        0x980003E0
#define set_SYS_VE3_SRAM_PWR0_reg(data)   (*((volatile unsigned int*) SYS_VE3_SRAM_PWR0_reg)=data)
#define get_SYS_VE3_SRAM_PWR0_reg   (*((volatile unsigned int*) SYS_VE3_SRAM_PWR0_reg))
#define SYS_VE3_SRAM_PWR0_inst_adr                                                   "0x00F8"
#define SYS_VE3_SRAM_PWR0_inst                                                       0x00F8
#define SYS_VE3_SRAM_PWR0_L2H_DELAY_CYCLE_shift                                      (0)
#define SYS_VE3_SRAM_PWR0_L2H_DELAY_CYCLE_mask                                       (0xFFFFFFFF)
#define SYS_VE3_SRAM_PWR0_L2H_DELAY_CYCLE(data)                                      (0xFFFFFFFF&((data)<<0))
#define SYS_VE3_SRAM_PWR0_L2H_DELAY_CYCLE_src(data)                                  ((0xFFFFFFFF&(data))>>0)
#define SYS_VE3_SRAM_PWR0_get_L2H_DELAY_CYCLE(data)                                  ((0xFFFFFFFF&(data))>>0)


#define SYS_VE3_SRAM_PWR1                                                            0x980003e4
#define SYS_VE3_SRAM_PWR1_reg_addr                                                   "0x980003E4"
#define SYS_VE3_SRAM_PWR1_reg                                                        0x980003E4
#define set_SYS_VE3_SRAM_PWR1_reg(data)   (*((volatile unsigned int*) SYS_VE3_SRAM_PWR1_reg)=data)
#define get_SYS_VE3_SRAM_PWR1_reg   (*((volatile unsigned int*) SYS_VE3_SRAM_PWR1_reg))
#define SYS_VE3_SRAM_PWR1_inst_adr                                                   "0x00F9"
#define SYS_VE3_SRAM_PWR1_inst                                                       0x00F9
#define SYS_VE3_SRAM_PWR1_H2L_DELAY_CYCLE_shift                                      (0)
#define SYS_VE3_SRAM_PWR1_H2L_DELAY_CYCLE_mask                                       (0xFFFFFFFF)
#define SYS_VE3_SRAM_PWR1_H2L_DELAY_CYCLE(data)                                      (0xFFFFFFFF&((data)<<0))
#define SYS_VE3_SRAM_PWR1_H2L_DELAY_CYCLE_src(data)                                  ((0xFFFFFFFF&(data))>>0)
#define SYS_VE3_SRAM_PWR1_get_H2L_DELAY_CYCLE(data)                                  ((0xFFFFFFFF&(data))>>0)


#define SYS_VE3_SRAM_PWR2                                                            0x980003e8
#define SYS_VE3_SRAM_PWR2_reg_addr                                                   "0x980003E8"
#define SYS_VE3_SRAM_PWR2_reg                                                        0x980003E8
#define set_SYS_VE3_SRAM_PWR2_reg(data)   (*((volatile unsigned int*) SYS_VE3_SRAM_PWR2_reg)=data)
#define get_SYS_VE3_SRAM_PWR2_reg   (*((volatile unsigned int*) SYS_VE3_SRAM_PWR2_reg))
#define SYS_VE3_SRAM_PWR2_inst_adr                                                   "0x00FA"
#define SYS_VE3_SRAM_PWR2_inst                                                       0x00FA
#define SYS_VE3_SRAM_PWR2_SD_REG_shift                                               (0)
#define SYS_VE3_SRAM_PWR2_SD_REG_mask                                                (0xFFFFFFFF)
#define SYS_VE3_SRAM_PWR2_SD_REG(data)                                               (0xFFFFFFFF&((data)<<0))
#define SYS_VE3_SRAM_PWR2_SD_REG_src(data)                                           ((0xFFFFFFFF&(data))>>0)
#define SYS_VE3_SRAM_PWR2_get_SD_REG(data)                                           ((0xFFFFFFFF&(data))>>0)


#define SYS_VE3_SRAM_PWR3                                                            0x980003ec
#define SYS_VE3_SRAM_PWR3_reg_addr                                                   "0x980003EC"
#define SYS_VE3_SRAM_PWR3_reg                                                        0x980003EC
#define set_SYS_VE3_SRAM_PWR3_reg(data)   (*((volatile unsigned int*) SYS_VE3_SRAM_PWR3_reg)=data)
#define get_SYS_VE3_SRAM_PWR3_reg   (*((volatile unsigned int*) SYS_VE3_SRAM_PWR3_reg))
#define SYS_VE3_SRAM_PWR3_inst_adr                                                   "0x00FB"
#define SYS_VE3_SRAM_PWR3_inst                                                       0x00FB
#define SYS_VE3_SRAM_PWR3_MUX_REG_shift                                              (0)
#define SYS_VE3_SRAM_PWR3_MUX_REG_mask                                               (0xFFFFFFFF)
#define SYS_VE3_SRAM_PWR3_MUX_REG(data)                                              (0xFFFFFFFF&((data)<<0))
#define SYS_VE3_SRAM_PWR3_MUX_REG_src(data)                                          ((0xFFFFFFFF&(data))>>0)
#define SYS_VE3_SRAM_PWR3_get_MUX_REG(data)                                          ((0xFFFFFFFF&(data))>>0)


#define SYS_VE3_SRAM_PWR4                                                            0x980003f0
#define SYS_VE3_SRAM_PWR4_reg_addr                                                   "0x980003F0"
#define SYS_VE3_SRAM_PWR4_reg                                                        0x980003F0
#define set_SYS_VE3_SRAM_PWR4_reg(data)   (*((volatile unsigned int*) SYS_VE3_SRAM_PWR4_reg)=data)
#define get_SYS_VE3_SRAM_PWR4_reg   (*((volatile unsigned int*) SYS_VE3_SRAM_PWR4_reg))
#define SYS_VE3_SRAM_PWR4_inst_adr                                                   "0x00FC"
#define SYS_VE3_SRAM_PWR4_inst                                                       0x00FC
#define SYS_VE3_SRAM_PWR4_CTRL_shift                                                 (0)
#define SYS_VE3_SRAM_PWR4_CTRL_mask                                                  (0xFFFFFFFF)
#define SYS_VE3_SRAM_PWR4_CTRL(data)                                                 (0xFFFFFFFF&((data)<<0))
#define SYS_VE3_SRAM_PWR4_CTRL_src(data)                                             ((0xFFFFFFFF&(data))>>0)
#define SYS_VE3_SRAM_PWR4_get_CTRL(data)                                             ((0xFFFFFFFF&(data))>>0)


#define SYS_VE3_SRAM_PWR5                                                            0x980003f4
#define SYS_VE3_SRAM_PWR5_reg_addr                                                   "0x980003F4"
#define SYS_VE3_SRAM_PWR5_reg                                                        0x980003F4
#define set_SYS_VE3_SRAM_PWR5_reg(data)   (*((volatile unsigned int*) SYS_VE3_SRAM_PWR5_reg)=data)
#define get_SYS_VE3_SRAM_PWR5_reg   (*((volatile unsigned int*) SYS_VE3_SRAM_PWR5_reg))
#define SYS_VE3_SRAM_PWR5_inst_adr                                                   "0x00FD"
#define SYS_VE3_SRAM_PWR5_inst                                                       0x00FD
#define SYS_VE3_SRAM_PWR5_ve3_sram_int_shift                                         (2)
#define SYS_VE3_SRAM_PWR5_ve3_sram_int_mask                                          (0x00000004)
#define SYS_VE3_SRAM_PWR5_ve3_sram_int(data)                                         (0x00000004&((data)<<2))
#define SYS_VE3_SRAM_PWR5_ve3_sram_int_src(data)                                     ((0x00000004&(data))>>2)
#define SYS_VE3_SRAM_PWR5_get_ve3_sram_int(data)                                     ((0x00000004&(data))>>2)
#define SYS_VE3_SRAM_PWR5_write_data_shift                                           (0)
#define SYS_VE3_SRAM_PWR5_write_data_mask                                            (0x00000001)
#define SYS_VE3_SRAM_PWR5_write_data(data)                                           (0x00000001&((data)<<0))
#define SYS_VE3_SRAM_PWR5_write_data_src(data)                                       ((0x00000001&(data))>>0)
#define SYS_VE3_SRAM_PWR5_get_write_data(data)                                       ((0x00000001&(data))>>0)


#define SYS_VE3_SRAM_PWR6                                                            0x980003f8
#define SYS_VE3_SRAM_PWR6_reg_addr                                                   "0x980003F8"
#define SYS_VE3_SRAM_PWR6_reg                                                        0x980003F8
#define set_SYS_VE3_SRAM_PWR6_reg(data)   (*((volatile unsigned int*) SYS_VE3_SRAM_PWR6_reg)=data)
#define get_SYS_VE3_SRAM_PWR6_reg   (*((volatile unsigned int*) SYS_VE3_SRAM_PWR6_reg))
#define SYS_VE3_SRAM_PWR6_inst_adr                                                   "0x00FE"
#define SYS_VE3_SRAM_PWR6_inst                                                       0x00FE
#define SYS_VE3_SRAM_PWR6_last_delay_cycle_shift                                     (0)
#define SYS_VE3_SRAM_PWR6_last_delay_cycle_mask                                      (0xFFFFFFFF)
#define SYS_VE3_SRAM_PWR6_last_delay_cycle(data)                                     (0xFFFFFFFF&((data)<<0))
#define SYS_VE3_SRAM_PWR6_last_delay_cycle_src(data)                                 ((0xFFFFFFFF&(data))>>0)
#define SYS_VE3_SRAM_PWR6_get_last_delay_cycle(data)                                 ((0xFFFFFFFF&(data))>>0)


#define SYS_VE3_SRAM_PWR7                                                            0x980003fc
#define SYS_VE3_SRAM_PWR7_reg_addr                                                   "0x980003FC"
#define SYS_VE3_SRAM_PWR7_reg                                                        0x980003FC
#define set_SYS_VE3_SRAM_PWR7_reg(data)   (*((volatile unsigned int*) SYS_VE3_SRAM_PWR7_reg)=data)
#define get_SYS_VE3_SRAM_PWR7_reg   (*((volatile unsigned int*) SYS_VE3_SRAM_PWR7_reg))
#define SYS_VE3_SRAM_PWR7_inst_adr                                                   "0x00FF"
#define SYS_VE3_SRAM_PWR7_inst                                                       0x00FF
#define SYS_VE3_SRAM_PWR7_pg_switch_info_shift                                       (0)
#define SYS_VE3_SRAM_PWR7_pg_switch_info_mask                                        (0xFFFFFFFF)
#define SYS_VE3_SRAM_PWR7_pg_switch_info(data)                                       (0xFFFFFFFF&((data)<<0))
#define SYS_VE3_SRAM_PWR7_pg_switch_info_src(data)                                   ((0xFFFFFFFF&(data))>>0)
#define SYS_VE3_SRAM_PWR7_get_pg_switch_info(data)                                   ((0xFFFFFFFF&(data))>>0)


#define SYS_POWER_CTRL                                                               0x98000400
#define SYS_POWER_CTRL_reg_addr                                                      "0x98000400"
#define SYS_POWER_CTRL_reg                                                           0x98000400
#define set_SYS_POWER_CTRL_reg(data)   (*((volatile unsigned int*) SYS_POWER_CTRL_reg)=data)
#define get_SYS_POWER_CTRL_reg   (*((volatile unsigned int*) SYS_POWER_CTRL_reg))
#define SYS_POWER_CTRL_inst_adr                                                      "0x0000"
#define SYS_POWER_CTRL_inst                                                          0x0000
#define SYS_POWER_CTRL_nat_sram_int_mask_shift                                       (19)
#define SYS_POWER_CTRL_nat_sram_int_mask_mask                                        (0x00080000)
#define SYS_POWER_CTRL_nat_sram_int_mask(data)                                       (0x00080000&((data)<<19))
#define SYS_POWER_CTRL_nat_sram_int_mask_src(data)                                   ((0x00080000&(data))>>19)
#define SYS_POWER_CTRL_get_nat_sram_int_mask(data)                                   ((0x00080000&(data))>>19)
#define SYS_POWER_CTRL_iso_nat_shift                                                 (18)
#define SYS_POWER_CTRL_iso_nat_mask                                                  (0x00040000)
#define SYS_POWER_CTRL_iso_nat(data)                                                 (0x00040000&((data)<<18))
#define SYS_POWER_CTRL_iso_nat_src(data)                                             ((0x00040000&(data))>>18)
#define SYS_POWER_CTRL_get_iso_nat(data)                                             ((0x00040000&(data))>>18)
#define SYS_POWER_CTRL_vetop_rm_shift                                                (14)
#define SYS_POWER_CTRL_vetop_rm_mask                                                 (0x0003C000)
#define SYS_POWER_CTRL_vetop_rm(data)                                                (0x0003C000&((data)<<14))
#define SYS_POWER_CTRL_vetop_rm_src(data)                                            ((0x0003C000&(data))>>14)
#define SYS_POWER_CTRL_get_vetop_rm(data)                                            ((0x0003C000&(data))>>14)
#define SYS_POWER_CTRL_vetop_rme_shift                                               (13)
#define SYS_POWER_CTRL_vetop_rme_mask                                                (0x00002000)
#define SYS_POWER_CTRL_vetop_rme(data)                                               (0x00002000&((data)<<13))
#define SYS_POWER_CTRL_vetop_rme_src(data)                                           ((0x00002000&(data))>>13)
#define SYS_POWER_CTRL_get_vetop_rme(data)                                           ((0x00002000&(data))>>13)
#define SYS_POWER_CTRL_vetop_sd_shift                                                (12)
#define SYS_POWER_CTRL_vetop_sd_mask                                                 (0x00001000)
#define SYS_POWER_CTRL_vetop_sd(data)                                                (0x00001000&((data)<<12))
#define SYS_POWER_CTRL_vetop_sd_src(data)                                            ((0x00001000&(data))>>12)
#define SYS_POWER_CTRL_get_vetop_sd(data)                                            ((0x00001000&(data))>>12)
#define SYS_POWER_CTRL_vetop_ds_shift                                                (11)
#define SYS_POWER_CTRL_vetop_ds_mask                                                 (0x00000800)
#define SYS_POWER_CTRL_vetop_ds(data)                                                (0x00000800&((data)<<11))
#define SYS_POWER_CTRL_vetop_ds_src(data)                                            ((0x00000800&(data))>>11)
#define SYS_POWER_CTRL_get_vetop_ds(data)                                            ((0x00000800&(data))>>11)
#define SYS_POWER_CTRL_vetop_ls_shift                                                (10)
#define SYS_POWER_CTRL_vetop_ls_mask                                                 (0x00000400)
#define SYS_POWER_CTRL_vetop_ls(data)                                                (0x00000400&((data)<<10))
#define SYS_POWER_CTRL_vetop_ls_src(data)                                            ((0x00000400&(data))>>10)
#define SYS_POWER_CTRL_get_vetop_ls(data)                                            ((0x00000400&(data))>>10)
#define SYS_POWER_CTRL_disp_sram_int_mask_shift                                      (9)
#define SYS_POWER_CTRL_disp_sram_int_mask_mask                                       (0x00000200)
#define SYS_POWER_CTRL_disp_sram_int_mask(data)                                      (0x00000200&((data)<<9))
#define SYS_POWER_CTRL_disp_sram_int_mask_src(data)                                  ((0x00000200&(data))>>9)
#define SYS_POWER_CTRL_get_disp_sram_int_mask(data)                                  ((0x00000200&(data))>>9)
#define SYS_POWER_CTRL_iso_disp_shift                                                (8)
#define SYS_POWER_CTRL_iso_disp_mask                                                 (0x00000100)
#define SYS_POWER_CTRL_iso_disp(data)                                                (0x00000100&((data)<<8))
#define SYS_POWER_CTRL_iso_disp_src(data)                                            ((0x00000100&(data))>>8)
#define SYS_POWER_CTRL_get_iso_disp(data)                                            ((0x00000100&(data))>>8)
#define SYS_POWER_CTRL_ve3_sram_int_mask_shift                                       (7)
#define SYS_POWER_CTRL_ve3_sram_int_mask_mask                                        (0x00000080)
#define SYS_POWER_CTRL_ve3_sram_int_mask(data)                                       (0x00000080&((data)<<7))
#define SYS_POWER_CTRL_ve3_sram_int_mask_src(data)                                   ((0x00000080&(data))>>7)
#define SYS_POWER_CTRL_get_ve3_sram_int_mask(data)                                   ((0x00000080&(data))>>7)
#define SYS_POWER_CTRL_iso_ve3_shift                                                 (6)
#define SYS_POWER_CTRL_iso_ve3_mask                                                  (0x00000040)
#define SYS_POWER_CTRL_iso_ve3(data)                                                 (0x00000040&((data)<<6))
#define SYS_POWER_CTRL_iso_ve3_src(data)                                             ((0x00000040&(data))>>6)
#define SYS_POWER_CTRL_get_iso_ve3(data)                                             ((0x00000040&(data))>>6)
#define SYS_POWER_CTRL_ve2_sram_int_mask_shift                                       (5)
#define SYS_POWER_CTRL_ve2_sram_int_mask_mask                                        (0x00000020)
#define SYS_POWER_CTRL_ve2_sram_int_mask(data)                                       (0x00000020&((data)<<5))
#define SYS_POWER_CTRL_ve2_sram_int_mask_src(data)                                   ((0x00000020&(data))>>5)
#define SYS_POWER_CTRL_get_ve2_sram_int_mask(data)                                   ((0x00000020&(data))>>5)
#define SYS_POWER_CTRL_iso_ve2_shift                                                 (4)
#define SYS_POWER_CTRL_iso_ve2_mask                                                  (0x00000010)
#define SYS_POWER_CTRL_iso_ve2(data)                                                 (0x00000010&((data)<<4))
#define SYS_POWER_CTRL_iso_ve2_src(data)                                             ((0x00000010&(data))>>4)
#define SYS_POWER_CTRL_get_iso_ve2(data)                                             ((0x00000010&(data))>>4)
#define SYS_POWER_CTRL_ve1_sram_int_mask_shift                                       (3)
#define SYS_POWER_CTRL_ve1_sram_int_mask_mask                                        (0x00000008)
#define SYS_POWER_CTRL_ve1_sram_int_mask(data)                                       (0x00000008&((data)<<3))
#define SYS_POWER_CTRL_ve1_sram_int_mask_src(data)                                   ((0x00000008&(data))>>3)
#define SYS_POWER_CTRL_get_ve1_sram_int_mask(data)                                   ((0x00000008&(data))>>3)
#define SYS_POWER_CTRL_gpu_sram_int_mask_shift                                       (2)
#define SYS_POWER_CTRL_gpu_sram_int_mask_mask                                        (0x00000004)
#define SYS_POWER_CTRL_gpu_sram_int_mask(data)                                       (0x00000004&((data)<<2))
#define SYS_POWER_CTRL_gpu_sram_int_mask_src(data)                                   ((0x00000004&(data))>>2)
#define SYS_POWER_CTRL_get_gpu_sram_int_mask(data)                                   ((0x00000004&(data))>>2)
#define SYS_POWER_CTRL_iso_gpu_shift                                                 (1)
#define SYS_POWER_CTRL_iso_gpu_mask                                                  (0x00000002)
#define SYS_POWER_CTRL_iso_gpu(data)                                                 (0x00000002&((data)<<1))
#define SYS_POWER_CTRL_iso_gpu_src(data)                                             ((0x00000002&(data))>>1)
#define SYS_POWER_CTRL_get_iso_gpu(data)                                             ((0x00000002&(data))>>1)
#define SYS_POWER_CTRL_iso_ve1_shift                                                 (0)
#define SYS_POWER_CTRL_iso_ve1_mask                                                  (0x00000001)
#define SYS_POWER_CTRL_iso_ve1(data)                                                 (0x00000001&((data)<<0))
#define SYS_POWER_CTRL_iso_ve1_src(data)                                             ((0x00000001&(data))>>0)
#define SYS_POWER_CTRL_get_iso_ve1(data)                                             ((0x00000001&(data))>>0)


#define SYS_PLL_PROB                                                                 0x98000408
#define SYS_PLL_PROB_reg_addr                                                        "0x98000408"
#define SYS_PLL_PROB_reg                                                             0x98000408
#define set_SYS_PLL_PROB_reg(data)   (*((volatile unsigned int*) SYS_PLL_PROB_reg)=data)
#define get_SYS_PLL_PROB_reg   (*((volatile unsigned int*) SYS_PLL_PROB_reg))
#define SYS_PLL_PROB_inst_adr                                                        "0x0002"
#define SYS_PLL_PROB_inst                                                            0x0002
#define SYS_PLL_PROB_vprob_plltest_sel_loc1_shift                                    (10)
#define SYS_PLL_PROB_vprob_plltest_sel_loc1_mask                                     (0x00007C00)
#define SYS_PLL_PROB_vprob_plltest_sel_loc1(data)                                    (0x00007C00&((data)<<10))
#define SYS_PLL_PROB_vprob_plltest_sel_loc1_src(data)                                ((0x00007C00&(data))>>10)
#define SYS_PLL_PROB_get_vprob_plltest_sel_loc1(data)                                ((0x00007C00&(data))>>10)
#define SYS_PLL_PROB_vprob_plltest_sel_loc0_shift                                    (5)
#define SYS_PLL_PROB_vprob_plltest_sel_loc0_mask                                     (0x000003E0)
#define SYS_PLL_PROB_vprob_plltest_sel_loc0(data)                                    (0x000003E0&((data)<<5))
#define SYS_PLL_PROB_vprob_plltest_sel_loc0_src(data)                                ((0x000003E0&(data))>>5)
#define SYS_PLL_PROB_get_vprob_plltest_sel_loc0(data)                                ((0x000003E0&(data))>>5)
#define SYS_PLL_PROB_vprob_ea_loc1_shift                                             (4)
#define SYS_PLL_PROB_vprob_ea_loc1_mask                                              (0x00000010)
#define SYS_PLL_PROB_vprob_ea_loc1(data)                                             (0x00000010&((data)<<4))
#define SYS_PLL_PROB_vprob_ea_loc1_src(data)                                         ((0x00000010&(data))>>4)
#define SYS_PLL_PROB_get_vprob_ea_loc1(data)                                         ((0x00000010&(data))>>4)
#define SYS_PLL_PROB_vprob_ea_loc0_shift                                             (3)
#define SYS_PLL_PROB_vprob_ea_loc0_mask                                              (0x00000008)
#define SYS_PLL_PROB_vprob_ea_loc0(data)                                             (0x00000008&((data)<<3))
#define SYS_PLL_PROB_vprob_ea_loc0_src(data)                                         ((0x00000008&(data))>>3)
#define SYS_PLL_PROB_get_vprob_ea_loc0(data)                                         ((0x00000008&(data))>>3)


#define SYS_CRT_DEBUG                                                                0x98000410
#define SYS_CRT_DEBUG_reg_addr                                                       "0x98000410"
#define SYS_CRT_DEBUG_reg                                                            0x98000410
#define set_SYS_CRT_DEBUG_reg(data)   (*((volatile unsigned int*) SYS_CRT_DEBUG_reg)=data)
#define get_SYS_CRT_DEBUG_reg   (*((volatile unsigned int*) SYS_CRT_DEBUG_reg))
#define SYS_CRT_DEBUG_inst_adr                                                       "0x0004"
#define SYS_CRT_DEBUG_inst                                                           0x0004
#define SYS_CRT_DEBUG_crt_dbg_en_shift                                               (8)
#define SYS_CRT_DEBUG_crt_dbg_en_mask                                                (0x00000100)
#define SYS_CRT_DEBUG_crt_dbg_en(data)                                               (0x00000100&((data)<<8))
#define SYS_CRT_DEBUG_crt_dbg_en_src(data)                                           ((0x00000100&(data))>>8)
#define SYS_CRT_DEBUG_get_crt_dbg_en(data)                                           ((0x00000100&(data))>>8)
#define SYS_CRT_DEBUG_crt_dbg_sel0_shift                                             (4)
#define SYS_CRT_DEBUG_crt_dbg_sel0_mask                                              (0x000000F0)
#define SYS_CRT_DEBUG_crt_dbg_sel0(data)                                             (0x000000F0&((data)<<4))
#define SYS_CRT_DEBUG_crt_dbg_sel0_src(data)                                         ((0x000000F0&(data))>>4)
#define SYS_CRT_DEBUG_get_crt_dbg_sel0(data)                                         ((0x000000F0&(data))>>4)
#define SYS_CRT_DEBUG_crt_dbg_sel1_shift                                             (0)
#define SYS_CRT_DEBUG_crt_dbg_sel1_mask                                              (0x0000000F)
#define SYS_CRT_DEBUG_crt_dbg_sel1(data)                                             (0x0000000F&((data)<<0))
#define SYS_CRT_DEBUG_crt_dbg_sel1_src(data)                                         ((0x0000000F&(data))>>0)
#define SYS_CRT_DEBUG_get_crt_dbg_sel1(data)                                         ((0x0000000F&(data))>>0)


#define SYS_DEBUG                                                                    0x98000414
#define SYS_DEBUG_reg_addr                                                           "0x98000414"
#define SYS_DEBUG_reg                                                                0x98000414
#define set_SYS_DEBUG_reg(data)   (*((volatile unsigned int*) SYS_DEBUG_reg)=data)
#define get_SYS_DEBUG_reg   (*((volatile unsigned int*) SYS_DEBUG_reg))
#define SYS_DEBUG_inst_adr                                                           "0x0005"
#define SYS_DEBUG_inst                                                               0x0005
#define SYS_DEBUG_reserved_debug_shift                                               (0)
#define SYS_DEBUG_reserved_debug_mask                                                (0x00000001)
#define SYS_DEBUG_reserved_debug(data)                                               (0x00000001&((data)<<0))
#define SYS_DEBUG_reserved_debug_src(data)                                           ((0x00000001&(data))>>0)
#define SYS_DEBUG_get_reserved_debug(data)                                           ((0x00000001&(data))>>0)


#define SYS_MBIST                                                                    0x98000418
#define SYS_MBIST_reg_addr                                                           "0x98000418"
#define SYS_MBIST_reg                                                                0x98000418
#define set_SYS_MBIST_reg(data)   (*((volatile unsigned int*) SYS_MBIST_reg)=data)
#define get_SYS_MBIST_reg   (*((volatile unsigned int*) SYS_MBIST_reg))
#define SYS_MBIST_inst_adr                                                           "0x0006"
#define SYS_MBIST_inst                                                               0x0006
#define SYS_MBIST_rbus_protect_shift                                                 (0)
#define SYS_MBIST_rbus_protect_mask                                                  (0xFFFFFFFF)
#define SYS_MBIST_rbus_protect(data)                                                 (0xFFFFFFFF&((data)<<0))
#define SYS_MBIST_rbus_protect_src(data)                                             ((0xFFFFFFFF&(data))>>0)
#define SYS_MBIST_get_rbus_protect(data)                                             ((0xFFFFFFFF&(data))>>0)


#define SYS_PLLDIV                                                                   0x9800041c
#define SYS_PLLDIV_reg_addr                                                          "0x9800041C"
#define SYS_PLLDIV_reg                                                               0x9800041C
#define set_SYS_PLLDIV_reg(data)   (*((volatile unsigned int*) SYS_PLLDIV_reg)=data)
#define get_SYS_PLLDIV_reg   (*((volatile unsigned int*) SYS_PLLDIV_reg))
#define SYS_PLLDIV_inst_adr                                                          "0x0007"
#define SYS_PLLDIV_inst                                                              0x0007
#define SYS_PLLDIV_dvsorting_shift                                                   (6)
#define SYS_PLLDIV_dvsorting_mask                                                    (0x00000040)
#define SYS_PLLDIV_dvsorting(data)                                                   (0x00000040&((data)<<6))
#define SYS_PLLDIV_dvsorting_src(data)                                               ((0x00000040&(data))>>6)
#define SYS_PLLDIV_get_dvsorting(data)                                               ((0x00000040&(data))>>6)
#define SYS_PLLDIV_pcie1_bak_sel_shift                                               (5)
#define SYS_PLLDIV_pcie1_bak_sel_mask                                                (0x00000020)
#define SYS_PLLDIV_pcie1_bak_sel(data)                                               (0x00000020&((data)<<5))
#define SYS_PLLDIV_pcie1_bak_sel_src(data)                                           ((0x00000020&(data))>>5)
#define SYS_PLLDIV_get_pcie1_bak_sel(data)                                           ((0x00000020&(data))>>5)
#define SYS_PLLDIV_pcie0_bak_sel_shift                                               (4)
#define SYS_PLLDIV_pcie0_bak_sel_mask                                                (0x00000010)
#define SYS_PLLDIV_pcie0_bak_sel(data)                                               (0x00000010&((data)<<4))
#define SYS_PLLDIV_pcie0_bak_sel_src(data)                                           ((0x00000010&(data))>>4)
#define SYS_PLLDIV_get_pcie0_bak_sel(data)                                           ((0x00000010&(data))>>4)
#define SYS_PLLDIV_plldiv_sel_shift                                                  (0)
#define SYS_PLLDIV_plldiv_sel_mask                                                   (0x0000000F)
#define SYS_PLLDIV_plldiv_sel(data)                                                  (0x0000000F&((data)<<0))
#define SYS_PLLDIV_plldiv_sel_src(data)                                              ((0x0000000F&(data))>>0)
#define SYS_PLLDIV_get_plldiv_sel(data)                                              ((0x0000000F&(data))>>0)


#define SYS_NAT_SRAM_PWR0                                                            0x98000420
#define SYS_NAT_SRAM_PWR0_reg_addr                                                   "0x98000420"
#define SYS_NAT_SRAM_PWR0_reg                                                        0x98000420
#define set_SYS_NAT_SRAM_PWR0_reg(data)   (*((volatile unsigned int*) SYS_NAT_SRAM_PWR0_reg)=data)
#define get_SYS_NAT_SRAM_PWR0_reg   (*((volatile unsigned int*) SYS_NAT_SRAM_PWR0_reg))
#define SYS_NAT_SRAM_PWR0_inst_adr                                                   "0x0008"
#define SYS_NAT_SRAM_PWR0_inst                                                       0x0008
#define SYS_NAT_SRAM_PWR0_L2H_DELAY_CYCLE_shift                                      (0)
#define SYS_NAT_SRAM_PWR0_L2H_DELAY_CYCLE_mask                                       (0xFFFFFFFF)
#define SYS_NAT_SRAM_PWR0_L2H_DELAY_CYCLE(data)                                      (0xFFFFFFFF&((data)<<0))
#define SYS_NAT_SRAM_PWR0_L2H_DELAY_CYCLE_src(data)                                  ((0xFFFFFFFF&(data))>>0)
#define SYS_NAT_SRAM_PWR0_get_L2H_DELAY_CYCLE(data)                                  ((0xFFFFFFFF&(data))>>0)


#define SYS_NAT_SRAM_PWR1                                                            0x98000424
#define SYS_NAT_SRAM_PWR1_reg_addr                                                   "0x98000424"
#define SYS_NAT_SRAM_PWR1_reg                                                        0x98000424
#define set_SYS_NAT_SRAM_PWR1_reg(data)   (*((volatile unsigned int*) SYS_NAT_SRAM_PWR1_reg)=data)
#define get_SYS_NAT_SRAM_PWR1_reg   (*((volatile unsigned int*) SYS_NAT_SRAM_PWR1_reg))
#define SYS_NAT_SRAM_PWR1_inst_adr                                                   "0x0009"
#define SYS_NAT_SRAM_PWR1_inst                                                       0x0009
#define SYS_NAT_SRAM_PWR1_H2L_DELAY_CYCLE_shift                                      (0)
#define SYS_NAT_SRAM_PWR1_H2L_DELAY_CYCLE_mask                                       (0xFFFFFFFF)
#define SYS_NAT_SRAM_PWR1_H2L_DELAY_CYCLE(data)                                      (0xFFFFFFFF&((data)<<0))
#define SYS_NAT_SRAM_PWR1_H2L_DELAY_CYCLE_src(data)                                  ((0xFFFFFFFF&(data))>>0)
#define SYS_NAT_SRAM_PWR1_get_H2L_DELAY_CYCLE(data)                                  ((0xFFFFFFFF&(data))>>0)


#define SYS_NAT_SRAM_PWR2                                                            0x98000428
#define SYS_NAT_SRAM_PWR2_reg_addr                                                   "0x98000428"
#define SYS_NAT_SRAM_PWR2_reg                                                        0x98000428
#define set_SYS_NAT_SRAM_PWR2_reg(data)   (*((volatile unsigned int*) SYS_NAT_SRAM_PWR2_reg)=data)
#define get_SYS_NAT_SRAM_PWR2_reg   (*((volatile unsigned int*) SYS_NAT_SRAM_PWR2_reg))
#define SYS_NAT_SRAM_PWR2_inst_adr                                                   "0x000A"
#define SYS_NAT_SRAM_PWR2_inst                                                       0x000A
#define SYS_NAT_SRAM_PWR2_SD_REG_shift                                               (0)
#define SYS_NAT_SRAM_PWR2_SD_REG_mask                                                (0xFFFFFFFF)
#define SYS_NAT_SRAM_PWR2_SD_REG(data)                                               (0xFFFFFFFF&((data)<<0))
#define SYS_NAT_SRAM_PWR2_SD_REG_src(data)                                           ((0xFFFFFFFF&(data))>>0)
#define SYS_NAT_SRAM_PWR2_get_SD_REG(data)                                           ((0xFFFFFFFF&(data))>>0)


#define SYS_NAT_SRAM_PWR3                                                            0x9800042c
#define SYS_NAT_SRAM_PWR3_reg_addr                                                   "0x9800042C"
#define SYS_NAT_SRAM_PWR3_reg                                                        0x9800042C
#define set_SYS_NAT_SRAM_PWR3_reg(data)   (*((volatile unsigned int*) SYS_NAT_SRAM_PWR3_reg)=data)
#define get_SYS_NAT_SRAM_PWR3_reg   (*((volatile unsigned int*) SYS_NAT_SRAM_PWR3_reg))
#define SYS_NAT_SRAM_PWR3_inst_adr                                                   "0x000B"
#define SYS_NAT_SRAM_PWR3_inst                                                       0x000B
#define SYS_NAT_SRAM_PWR3_MUX_REG_shift                                              (0)
#define SYS_NAT_SRAM_PWR3_MUX_REG_mask                                               (0xFFFFFFFF)
#define SYS_NAT_SRAM_PWR3_MUX_REG(data)                                              (0xFFFFFFFF&((data)<<0))
#define SYS_NAT_SRAM_PWR3_MUX_REG_src(data)                                          ((0xFFFFFFFF&(data))>>0)
#define SYS_NAT_SRAM_PWR3_get_MUX_REG(data)                                          ((0xFFFFFFFF&(data))>>0)


#define SYS_NAT_SRAM_PWR4                                                            0x98000430
#define SYS_NAT_SRAM_PWR4_reg_addr                                                   "0x98000430"
#define SYS_NAT_SRAM_PWR4_reg                                                        0x98000430
#define set_SYS_NAT_SRAM_PWR4_reg(data)   (*((volatile unsigned int*) SYS_NAT_SRAM_PWR4_reg)=data)
#define get_SYS_NAT_SRAM_PWR4_reg   (*((volatile unsigned int*) SYS_NAT_SRAM_PWR4_reg))
#define SYS_NAT_SRAM_PWR4_inst_adr                                                   "0x000C"
#define SYS_NAT_SRAM_PWR4_inst                                                       0x000C
#define SYS_NAT_SRAM_PWR4_CTRL_shift                                                 (0)
#define SYS_NAT_SRAM_PWR4_CTRL_mask                                                  (0xFFFFFFFF)
#define SYS_NAT_SRAM_PWR4_CTRL(data)                                                 (0xFFFFFFFF&((data)<<0))
#define SYS_NAT_SRAM_PWR4_CTRL_src(data)                                             ((0xFFFFFFFF&(data))>>0)
#define SYS_NAT_SRAM_PWR4_get_CTRL(data)                                             ((0xFFFFFFFF&(data))>>0)


#define SYS_NAT_SRAM_PWR5                                                            0x98000434
#define SYS_NAT_SRAM_PWR5_reg_addr                                                   "0x98000434"
#define SYS_NAT_SRAM_PWR5_reg                                                        0x98000434
#define set_SYS_NAT_SRAM_PWR5_reg(data)   (*((volatile unsigned int*) SYS_NAT_SRAM_PWR5_reg)=data)
#define get_SYS_NAT_SRAM_PWR5_reg   (*((volatile unsigned int*) SYS_NAT_SRAM_PWR5_reg))
#define SYS_NAT_SRAM_PWR5_inst_adr                                                   "0x000D"
#define SYS_NAT_SRAM_PWR5_inst                                                       0x000D
#define SYS_NAT_SRAM_PWR5_nat_sram_int_shift                                         (2)
#define SYS_NAT_SRAM_PWR5_nat_sram_int_mask                                          (0x00000004)
#define SYS_NAT_SRAM_PWR5_nat_sram_int(data)                                         (0x00000004&((data)<<2))
#define SYS_NAT_SRAM_PWR5_nat_sram_int_src(data)                                     ((0x00000004&(data))>>2)
#define SYS_NAT_SRAM_PWR5_get_nat_sram_int(data)                                     ((0x00000004&(data))>>2)
#define SYS_NAT_SRAM_PWR5_write_data_shift                                           (0)
#define SYS_NAT_SRAM_PWR5_write_data_mask                                            (0x00000001)
#define SYS_NAT_SRAM_PWR5_write_data(data)                                           (0x00000001&((data)<<0))
#define SYS_NAT_SRAM_PWR5_write_data_src(data)                                       ((0x00000001&(data))>>0)
#define SYS_NAT_SRAM_PWR5_get_write_data(data)                                       ((0x00000001&(data))>>0)


#define SYS_NAT_SRAM_PWR6                                                            0x98000438
#define SYS_NAT_SRAM_PWR6_reg_addr                                                   "0x98000438"
#define SYS_NAT_SRAM_PWR6_reg                                                        0x98000438
#define set_SYS_NAT_SRAM_PWR6_reg(data)   (*((volatile unsigned int*) SYS_NAT_SRAM_PWR6_reg)=data)
#define get_SYS_NAT_SRAM_PWR6_reg   (*((volatile unsigned int*) SYS_NAT_SRAM_PWR6_reg))
#define SYS_NAT_SRAM_PWR6_inst_adr                                                   "0x000E"
#define SYS_NAT_SRAM_PWR6_inst                                                       0x000E
#define SYS_NAT_SRAM_PWR6_last_delay_cycle_shift                                     (0)
#define SYS_NAT_SRAM_PWR6_last_delay_cycle_mask                                      (0xFFFFFFFF)
#define SYS_NAT_SRAM_PWR6_last_delay_cycle(data)                                     (0xFFFFFFFF&((data)<<0))
#define SYS_NAT_SRAM_PWR6_last_delay_cycle_src(data)                                 ((0xFFFFFFFF&(data))>>0)
#define SYS_NAT_SRAM_PWR6_get_last_delay_cycle(data)                                 ((0xFFFFFFFF&(data))>>0)


#define SYS_NAT_SRAM_PWR7                                                            0x9800043c
#define SYS_NAT_SRAM_PWR7_reg_addr                                                   "0x9800043C"
#define SYS_NAT_SRAM_PWR7_reg                                                        0x9800043C
#define set_SYS_NAT_SRAM_PWR7_reg(data)   (*((volatile unsigned int*) SYS_NAT_SRAM_PWR7_reg)=data)
#define get_SYS_NAT_SRAM_PWR7_reg   (*((volatile unsigned int*) SYS_NAT_SRAM_PWR7_reg))
#define SYS_NAT_SRAM_PWR7_inst_adr                                                   "0x000F"
#define SYS_NAT_SRAM_PWR7_inst                                                       0x000F
#define SYS_NAT_SRAM_PWR7_pg_switch_info_shift                                       (0)
#define SYS_NAT_SRAM_PWR7_pg_switch_info_mask                                        (0xFFFFFFFF)
#define SYS_NAT_SRAM_PWR7_pg_switch_info(data)                                       (0xFFFFFFFF&((data)<<0))
#define SYS_NAT_SRAM_PWR7_pg_switch_info_src(data)                                   ((0xFFFFFFFF&(data))>>0)
#define SYS_NAT_SRAM_PWR7_get_pg_switch_info(data)                                   ((0xFFFFFFFF&(data))>>0)


#define SYS_DUMMY0                                                                   0x98000450
#define SYS_DUMMY0_reg_addr                                                          "0x98000450"
#define SYS_DUMMY0_reg                                                               0x98000450
#define set_SYS_DUMMY0_reg(data)   (*((volatile unsigned int*) SYS_DUMMY0_reg)=data)
#define get_SYS_DUMMY0_reg   (*((volatile unsigned int*) SYS_DUMMY0_reg))
#define SYS_DUMMY0_inst_adr                                                          "0x0014"
#define SYS_DUMMY0_inst                                                              0x0014
#define SYS_DUMMY0_dmyreg0_rst0_shift                                                (0)
#define SYS_DUMMY0_dmyreg0_rst0_mask                                                 (0xFFFFFFFF)
#define SYS_DUMMY0_dmyreg0_rst0(data)                                                (0xFFFFFFFF&((data)<<0))
#define SYS_DUMMY0_dmyreg0_rst0_src(data)                                            ((0xFFFFFFFF&(data))>>0)
#define SYS_DUMMY0_get_dmyreg0_rst0(data)                                            ((0xFFFFFFFF&(data))>>0)


#define SYS_DUMMY1                                                                   0x98000454
#define SYS_DUMMY1_reg_addr                                                          "0x98000454"
#define SYS_DUMMY1_reg                                                               0x98000454
#define set_SYS_DUMMY1_reg(data)   (*((volatile unsigned int*) SYS_DUMMY1_reg)=data)
#define get_SYS_DUMMY1_reg   (*((volatile unsigned int*) SYS_DUMMY1_reg))
#define SYS_DUMMY1_inst_adr                                                          "0x0015"
#define SYS_DUMMY1_inst                                                              0x0015
#define SYS_DUMMY1_dmyreg1_rst0_shift                                                (0)
#define SYS_DUMMY1_dmyreg1_rst0_mask                                                 (0xFFFFFFFF)
#define SYS_DUMMY1_dmyreg1_rst0(data)                                                (0xFFFFFFFF&((data)<<0))
#define SYS_DUMMY1_dmyreg1_rst0_src(data)                                            ((0xFFFFFFFF&(data))>>0)
#define SYS_DUMMY1_get_dmyreg1_rst0(data)                                            ((0xFFFFFFFF&(data))>>0)


#define SYS_DUMMY2                                                                   0x98000458
#define SYS_DUMMY2_reg_addr                                                          "0x98000458"
#define SYS_DUMMY2_reg                                                               0x98000458
#define set_SYS_DUMMY2_reg(data)   (*((volatile unsigned int*) SYS_DUMMY2_reg)=data)
#define get_SYS_DUMMY2_reg   (*((volatile unsigned int*) SYS_DUMMY2_reg))
#define SYS_DUMMY2_inst_adr                                                          "0x0016"
#define SYS_DUMMY2_inst                                                              0x0016
#define SYS_DUMMY2_dmyreg2_rst1_shift                                                (0)
#define SYS_DUMMY2_dmyreg2_rst1_mask                                                 (0xFFFFFFFF)
#define SYS_DUMMY2_dmyreg2_rst1(data)                                                (0xFFFFFFFF&((data)<<0))
#define SYS_DUMMY2_dmyreg2_rst1_src(data)                                            ((0xFFFFFFFF&(data))>>0)
#define SYS_DUMMY2_get_dmyreg2_rst1(data)                                            ((0xFFFFFFFF&(data))>>0)


#define SYS_DUMMY3                                                                   0x9800045c
#define SYS_DUMMY3_reg_addr                                                          "0x9800045C"
#define SYS_DUMMY3_reg                                                               0x9800045C
#define set_SYS_DUMMY3_reg(data)   (*((volatile unsigned int*) SYS_DUMMY3_reg)=data)
#define get_SYS_DUMMY3_reg   (*((volatile unsigned int*) SYS_DUMMY3_reg))
#define SYS_DUMMY3_inst_adr                                                          "0x0017"
#define SYS_DUMMY3_inst                                                              0x0017
#define SYS_DUMMY3_dmyreg3_rst1_shift                                                (0)
#define SYS_DUMMY3_dmyreg3_rst1_mask                                                 (0xFFFFFFFF)
#define SYS_DUMMY3_dmyreg3_rst1(data)                                                (0xFFFFFFFF&((data)<<0))
#define SYS_DUMMY3_dmyreg3_rst1_src(data)                                            ((0xFFFFFFFF&(data))>>0)
#define SYS_DUMMY3_get_dmyreg3_rst1(data)                                            ((0xFFFFFFFF&(data))>>0)


#define SYS_PLL_SSC_DIG_SCPU0                                                        0x98000500
#define SYS_PLL_SSC_DIG_SCPU0_reg_addr                                               "0x98000500"
#define SYS_PLL_SSC_DIG_SCPU0_reg                                                    0x98000500
#define set_SYS_PLL_SSC_DIG_SCPU0_reg(data)   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_SCPU0_reg)=data)
#define get_SYS_PLL_SSC_DIG_SCPU0_reg   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_SCPU0_reg))
#define SYS_PLL_SSC_DIG_SCPU0_inst_adr                                               "0x0040"
#define SYS_PLL_SSC_DIG_SCPU0_inst                                                   0x0040
#define SYS_PLL_SSC_DIG_SCPU0_REG_CKSSC_INV_SCPU_shift                               (4)
#define SYS_PLL_SSC_DIG_SCPU0_REG_CKSSC_INV_SCPU_mask                                (0x00000010)
#define SYS_PLL_SSC_DIG_SCPU0_REG_CKSSC_INV_SCPU(data)                               (0x00000010&((data)<<4))
#define SYS_PLL_SSC_DIG_SCPU0_REG_CKSSC_INV_SCPU_src(data)                           ((0x00000010&(data))>>4)
#define SYS_PLL_SSC_DIG_SCPU0_get_REG_CKSSC_INV_SCPU(data)                           ((0x00000010&(data))>>4)
#define SYS_PLL_SSC_DIG_SCPU0_REG_GRAN_AUTO_RST_SCPU_shift                           (3)
#define SYS_PLL_SSC_DIG_SCPU0_REG_GRAN_AUTO_RST_SCPU_mask                            (0x00000008)
#define SYS_PLL_SSC_DIG_SCPU0_REG_GRAN_AUTO_RST_SCPU(data)                           (0x00000008&((data)<<3))
#define SYS_PLL_SSC_DIG_SCPU0_REG_GRAN_AUTO_RST_SCPU_src(data)                       ((0x00000008&(data))>>3)
#define SYS_PLL_SSC_DIG_SCPU0_get_REG_GRAN_AUTO_RST_SCPU(data)                       ((0x00000008&(data))>>3)
#define SYS_PLL_SSC_DIG_SCPU0_RSTB_SCPU_shift                                        (2)
#define SYS_PLL_SSC_DIG_SCPU0_RSTB_SCPU_mask                                         (0x00000004)
#define SYS_PLL_SSC_DIG_SCPU0_RSTB_SCPU(data)                                        (0x00000004&((data)<<2))
#define SYS_PLL_SSC_DIG_SCPU0_RSTB_SCPU_src(data)                                    ((0x00000004&(data))>>2)
#define SYS_PLL_SSC_DIG_SCPU0_get_RSTB_SCPU(data)                                    ((0x00000004&(data))>>2)
#define SYS_PLL_SSC_DIG_SCPU0_EN_SSC_SCPU_shift                                      (1)
#define SYS_PLL_SSC_DIG_SCPU0_EN_SSC_SCPU_mask                                       (0x00000002)
#define SYS_PLL_SSC_DIG_SCPU0_EN_SSC_SCPU(data)                                      (0x00000002&((data)<<1))
#define SYS_PLL_SSC_DIG_SCPU0_EN_SSC_SCPU_src(data)                                  ((0x00000002&(data))>>1)
#define SYS_PLL_SSC_DIG_SCPU0_get_EN_SSC_SCPU(data)                                  ((0x00000002&(data))>>1)
#define SYS_PLL_SSC_DIG_SCPU0_OC_EN_SCPU_shift                                       (0)
#define SYS_PLL_SSC_DIG_SCPU0_OC_EN_SCPU_mask                                        (0x00000001)
#define SYS_PLL_SSC_DIG_SCPU0_OC_EN_SCPU(data)                                       (0x00000001&((data)<<0))
#define SYS_PLL_SSC_DIG_SCPU0_OC_EN_SCPU_src(data)                                   ((0x00000001&(data))>>0)
#define SYS_PLL_SSC_DIG_SCPU0_get_OC_EN_SCPU(data)                                   ((0x00000001&(data))>>0)


#define SYS_PLL_SSC_DIG_SCPU1                                                        0x98000504
#define SYS_PLL_SSC_DIG_SCPU1_reg_addr                                               "0x98000504"
#define SYS_PLL_SSC_DIG_SCPU1_reg                                                    0x98000504
#define set_SYS_PLL_SSC_DIG_SCPU1_reg(data)   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_SCPU1_reg)=data)
#define get_SYS_PLL_SSC_DIG_SCPU1_reg   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_SCPU1_reg))
#define SYS_PLL_SSC_DIG_SCPU1_inst_adr                                               "0x0041"
#define SYS_PLL_SSC_DIG_SCPU1_inst                                                   0x0041
#define SYS_PLL_SSC_DIG_SCPU1_NCODE_T_SCPU_shift                                     (11)
#define SYS_PLL_SSC_DIG_SCPU1_NCODE_T_SCPU_mask                                      (0x0007F800)
#define SYS_PLL_SSC_DIG_SCPU1_NCODE_T_SCPU(data)                                     (0x0007F800&((data)<<11))
#define SYS_PLL_SSC_DIG_SCPU1_NCODE_T_SCPU_src(data)                                 ((0x0007F800&(data))>>11)
#define SYS_PLL_SSC_DIG_SCPU1_get_NCODE_T_SCPU(data)                                 ((0x0007F800&(data))>>11)
#define SYS_PLL_SSC_DIG_SCPU1_FCODE_T_SCPU_shift                                     (0)
#define SYS_PLL_SSC_DIG_SCPU1_FCODE_T_SCPU_mask                                      (0x000007FF)
#define SYS_PLL_SSC_DIG_SCPU1_FCODE_T_SCPU(data)                                     (0x000007FF&((data)<<0))
#define SYS_PLL_SSC_DIG_SCPU1_FCODE_T_SCPU_src(data)                                 ((0x000007FF&(data))>>0)
#define SYS_PLL_SSC_DIG_SCPU1_get_FCODE_T_SCPU(data)                                 ((0x000007FF&(data))>>0)


#define SYS_PLL_SSC_DIG_SCPU2                                                        0x98000508
#define SYS_PLL_SSC_DIG_SCPU2_reg_addr                                               "0x98000508"
#define SYS_PLL_SSC_DIG_SCPU2_reg                                                    0x98000508
#define set_SYS_PLL_SSC_DIG_SCPU2_reg(data)   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_SCPU2_reg)=data)
#define get_SYS_PLL_SSC_DIG_SCPU2_reg   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_SCPU2_reg))
#define SYS_PLL_SSC_DIG_SCPU2_inst_adr                                               "0x0042"
#define SYS_PLL_SSC_DIG_SCPU2_inst                                                   0x0042
#define SYS_PLL_SSC_DIG_SCPU2_REG_BYPASS_DIVN_shift                                  (27)
#define SYS_PLL_SSC_DIG_SCPU2_REG_BYPASS_DIVN_mask                                   (0x08000000)
#define SYS_PLL_SSC_DIG_SCPU2_REG_BYPASS_DIVN(data)                                  (0x08000000&((data)<<27))
#define SYS_PLL_SSC_DIG_SCPU2_REG_BYPASS_DIVN_src(data)                              ((0x08000000&(data))>>27)
#define SYS_PLL_SSC_DIG_SCPU2_get_REG_BYPASS_DIVN(data)                              ((0x08000000&(data))>>27)
#define SYS_PLL_SSC_DIG_SCPU2_REG_OC_STEP_SET_SCPU_shift                             (17)
#define SYS_PLL_SSC_DIG_SCPU2_REG_OC_STEP_SET_SCPU_mask                              (0x07FE0000)
#define SYS_PLL_SSC_DIG_SCPU2_REG_OC_STEP_SET_SCPU(data)                             (0x07FE0000&((data)<<17))
#define SYS_PLL_SSC_DIG_SCPU2_REG_OC_STEP_SET_SCPU_src(data)                         ((0x07FE0000&(data))>>17)
#define SYS_PLL_SSC_DIG_SCPU2_get_REG_OC_STEP_SET_SCPU(data)                         ((0x07FE0000&(data))>>17)
#define SYS_PLL_SSC_DIG_SCPU2_REG_SEL_OC_MODE_SCPU_shift                             (15)
#define SYS_PLL_SSC_DIG_SCPU2_REG_SEL_OC_MODE_SCPU_mask                              (0x00018000)
#define SYS_PLL_SSC_DIG_SCPU2_REG_SEL_OC_MODE_SCPU(data)                             (0x00018000&((data)<<15))
#define SYS_PLL_SSC_DIG_SCPU2_REG_SEL_OC_MODE_SCPU_src(data)                         ((0x00018000&(data))>>15)
#define SYS_PLL_SSC_DIG_SCPU2_get_REG_SEL_OC_MODE_SCPU(data)                         ((0x00018000&(data))>>15)
#define SYS_PLL_SSC_DIG_SCPU2_REG_HS_OC_STOP_DIFF_SCPU_shift                         (13)
#define SYS_PLL_SSC_DIG_SCPU2_REG_HS_OC_STOP_DIFF_SCPU_mask                          (0x00006000)
#define SYS_PLL_SSC_DIG_SCPU2_REG_HS_OC_STOP_DIFF_SCPU(data)                         (0x00006000&((data)<<13))
#define SYS_PLL_SSC_DIG_SCPU2_REG_HS_OC_STOP_DIFF_SCPU_src(data)                     ((0x00006000&(data))>>13)
#define SYS_PLL_SSC_DIG_SCPU2_get_REG_HS_OC_STOP_DIFF_SCPU(data)                     ((0x00006000&(data))>>13)
#define SYS_PLL_SSC_DIG_SCPU2_REG_OC_DONE_DELAY_SCPU_shift                           (7)
#define SYS_PLL_SSC_DIG_SCPU2_REG_OC_DONE_DELAY_SCPU_mask                            (0x00001F80)
#define SYS_PLL_SSC_DIG_SCPU2_REG_OC_DONE_DELAY_SCPU(data)                           (0x00001F80&((data)<<7))
#define SYS_PLL_SSC_DIG_SCPU2_REG_OC_DONE_DELAY_SCPU_src(data)                       ((0x00001F80&(data))>>7)
#define SYS_PLL_SSC_DIG_SCPU2_get_REG_OC_DONE_DELAY_SCPU(data)                       ((0x00001F80&(data))>>7)
#define SYS_PLL_SSC_DIG_SCPU2_REG_PI_CUR_SEL_SCPU_shift                              (5)
#define SYS_PLL_SSC_DIG_SCPU2_REG_PI_CUR_SEL_SCPU_mask                               (0x00000060)
#define SYS_PLL_SSC_DIG_SCPU2_REG_PI_CUR_SEL_SCPU(data)                              (0x00000060&((data)<<5))
#define SYS_PLL_SSC_DIG_SCPU2_REG_PI_CUR_SEL_SCPU_src(data)                          ((0x00000060&(data))>>5)
#define SYS_PLL_SSC_DIG_SCPU2_get_REG_PI_CUR_SEL_SCPU(data)                          ((0x00000060&(data))>>5)
#define SYS_PLL_SSC_DIG_SCPU2_REG_BYPASS_PI_SCPU_shift                               (4)
#define SYS_PLL_SSC_DIG_SCPU2_REG_BYPASS_PI_SCPU_mask                                (0x00000010)
#define SYS_PLL_SSC_DIG_SCPU2_REG_BYPASS_PI_SCPU(data)                               (0x00000010&((data)<<4))
#define SYS_PLL_SSC_DIG_SCPU2_REG_BYPASS_PI_SCPU_src(data)                           ((0x00000010&(data))>>4)
#define SYS_PLL_SSC_DIG_SCPU2_get_REG_BYPASS_PI_SCPU(data)                           ((0x00000010&(data))>>4)
#define SYS_PLL_SSC_DIG_SCPU2_REG_SDM_ORDER_SCPU_shift                               (3)
#define SYS_PLL_SSC_DIG_SCPU2_REG_SDM_ORDER_SCPU_mask                                (0x00000008)
#define SYS_PLL_SSC_DIG_SCPU2_REG_SDM_ORDER_SCPU(data)                               (0x00000008&((data)<<3))
#define SYS_PLL_SSC_DIG_SCPU2_REG_SDM_ORDER_SCPU_src(data)                           ((0x00000008&(data))>>3)
#define SYS_PLL_SSC_DIG_SCPU2_get_REG_SDM_ORDER_SCPU(data)                           ((0x00000008&(data))>>3)
#define SYS_PLL_SSC_DIG_SCPU2_REG_EN_PI_DEBUG_SCPU_shift                             (2)
#define SYS_PLL_SSC_DIG_SCPU2_REG_EN_PI_DEBUG_SCPU_mask                              (0x00000004)
#define SYS_PLL_SSC_DIG_SCPU2_REG_EN_PI_DEBUG_SCPU(data)                             (0x00000004&((data)<<2))
#define SYS_PLL_SSC_DIG_SCPU2_REG_EN_PI_DEBUG_SCPU_src(data)                         ((0x00000004&(data))>>2)
#define SYS_PLL_SSC_DIG_SCPU2_get_REG_EN_PI_DEBUG_SCPU(data)                         ((0x00000004&(data))>>2)


#define SYS_PLL_SSC_DIG_SCPU3                                                        0x9800050C
#define SYS_PLL_SSC_DIG_SCPU3_reg_addr                                               "0x9800050C"
#define SYS_PLL_SSC_DIG_SCPU3_reg                                                    0x9800050C
#define set_SYS_PLL_SSC_DIG_SCPU3_reg(data)   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_SCPU3_reg)=data)
#define get_SYS_PLL_SSC_DIG_SCPU3_reg   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_SCPU3_reg))
#define SYS_PLL_SSC_DIG_SCPU3_inst_adr                                               "0x0043"
#define SYS_PLL_SSC_DIG_SCPU3_inst                                                   0x0043
#define SYS_PLL_SSC_DIG_SCPU3_NCODE_SSC_SCPU_shift                                   (11)
#define SYS_PLL_SSC_DIG_SCPU3_NCODE_SSC_SCPU_mask                                    (0x0007F800)
#define SYS_PLL_SSC_DIG_SCPU3_NCODE_SSC_SCPU(data)                                   (0x0007F800&((data)<<11))
#define SYS_PLL_SSC_DIG_SCPU3_NCODE_SSC_SCPU_src(data)                               ((0x0007F800&(data))>>11)
#define SYS_PLL_SSC_DIG_SCPU3_get_NCODE_SSC_SCPU(data)                               ((0x0007F800&(data))>>11)
#define SYS_PLL_SSC_DIG_SCPU3_FCODE_SSC_SCPU_shift                                   (0)
#define SYS_PLL_SSC_DIG_SCPU3_FCODE_SSC_SCPU_mask                                    (0x000007FF)
#define SYS_PLL_SSC_DIG_SCPU3_FCODE_SSC_SCPU(data)                                   (0x000007FF&((data)<<0))
#define SYS_PLL_SSC_DIG_SCPU3_FCODE_SSC_SCPU_src(data)                               ((0x000007FF&(data))>>0)
#define SYS_PLL_SSC_DIG_SCPU3_get_FCODE_SSC_SCPU(data)                               ((0x000007FF&(data))>>0)


#define SYS_PLL_SSC_DIG_SCPU4                                                        0x98000510
#define SYS_PLL_SSC_DIG_SCPU4_reg_addr                                               "0x98000510"
#define SYS_PLL_SSC_DIG_SCPU4_reg                                                    0x98000510
#define set_SYS_PLL_SSC_DIG_SCPU4_reg(data)   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_SCPU4_reg)=data)
#define get_SYS_PLL_SSC_DIG_SCPU4_reg   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_SCPU4_reg))
#define SYS_PLL_SSC_DIG_SCPU4_inst_adr                                               "0x0044"
#define SYS_PLL_SSC_DIG_SCPU4_inst                                                   0x0044
#define SYS_PLL_SSC_DIG_SCPU4_GRAN_EST_SCPU_shift                                    (0)
#define SYS_PLL_SSC_DIG_SCPU4_GRAN_EST_SCPU_mask                                     (0x0007FFFF)
#define SYS_PLL_SSC_DIG_SCPU4_GRAN_EST_SCPU(data)                                    (0x0007FFFF&((data)<<0))
#define SYS_PLL_SSC_DIG_SCPU4_GRAN_EST_SCPU_src(data)                                ((0x0007FFFF&(data))>>0)
#define SYS_PLL_SSC_DIG_SCPU4_get_GRAN_EST_SCPU(data)                                ((0x0007FFFF&(data))>>0)


#define SYS_PLL_SSC_DIG_SCPU5                                                        0x98000514
#define SYS_PLL_SSC_DIG_SCPU5_reg_addr                                               "0x98000514"
#define SYS_PLL_SSC_DIG_SCPU5_reg                                                    0x98000514
#define set_SYS_PLL_SSC_DIG_SCPU5_reg(data)   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_SCPU5_reg)=data)
#define get_SYS_PLL_SSC_DIG_SCPU5_reg   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_SCPU5_reg))
#define SYS_PLL_SSC_DIG_SCPU5_inst_adr                                               "0x0045"
#define SYS_PLL_SSC_DIG_SCPU5_inst                                                   0x0045
#define SYS_PLL_SSC_DIG_SCPU5_FCW_SSC_DEFAULT_SCPU_shift                             (0)
#define SYS_PLL_SSC_DIG_SCPU5_FCW_SSC_DEFAULT_SCPU_mask                              (0x0007FFFF)
#define SYS_PLL_SSC_DIG_SCPU5_FCW_SSC_DEFAULT_SCPU(data)                             (0x0007FFFF&((data)<<0))
#define SYS_PLL_SSC_DIG_SCPU5_FCW_SSC_DEFAULT_SCPU_src(data)                         ((0x0007FFFF&(data))>>0)
#define SYS_PLL_SSC_DIG_SCPU5_get_FCW_SSC_DEFAULT_SCPU(data)                         ((0x0007FFFF&(data))>>0)


#define SYS_PLL_SSC_DIG_SCPU_DBG1                                                    0x98000518
#define SYS_PLL_SSC_DIG_SCPU_DBG1_reg_addr                                           "0x98000518"
#define SYS_PLL_SSC_DIG_SCPU_DBG1_reg                                                0x98000518
#define set_SYS_PLL_SSC_DIG_SCPU_DBG1_reg(data)   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_SCPU_DBG1_reg)=data)
#define get_SYS_PLL_SSC_DIG_SCPU_DBG1_reg   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_SCPU_DBG1_reg))
#define SYS_PLL_SSC_DIG_SCPU_DBG1_inst_adr                                           "0x0046"
#define SYS_PLL_SSC_DIG_SCPU_DBG1_inst                                               0x0046
#define SYS_PLL_SSC_DIG_SCPU_DBG1_LOOP_PI_ISEL_SCPU_shift                            (13)
#define SYS_PLL_SSC_DIG_SCPU_DBG1_LOOP_PI_ISEL_SCPU_mask                             (0x00006000)
#define SYS_PLL_SSC_DIG_SCPU_DBG1_LOOP_PI_ISEL_SCPU(data)                            (0x00006000&((data)<<13))
#define SYS_PLL_SSC_DIG_SCPU_DBG1_LOOP_PI_ISEL_SCPU_src(data)                        ((0x00006000&(data))>>13)
#define SYS_PLL_SSC_DIG_SCPU_DBG1_get_LOOP_PI_ISEL_SCPU(data)                        ((0x00006000&(data))>>13)
#define SYS_PLL_SSC_DIG_SCPU_DBG1_PHSEL_SCPU_shift                                   (8)
#define SYS_PLL_SSC_DIG_SCPU_DBG1_PHSEL_SCPU_mask                                    (0x00001F00)
#define SYS_PLL_SSC_DIG_SCPU_DBG1_PHSEL_SCPU(data)                                   (0x00001F00&((data)<<8))
#define SYS_PLL_SSC_DIG_SCPU_DBG1_PHSEL_SCPU_src(data)                               ((0x00001F00&(data))>>8)
#define SYS_PLL_SSC_DIG_SCPU_DBG1_get_PHSEL_SCPU(data)                               ((0x00001F00&(data))>>8)
#define SYS_PLL_SSC_DIG_SCPU_DBG1_DIVN_SCPU_shift                                    (0)
#define SYS_PLL_SSC_DIG_SCPU_DBG1_DIVN_SCPU_mask                                     (0x000000FF)
#define SYS_PLL_SSC_DIG_SCPU_DBG1_DIVN_SCPU(data)                                    (0x000000FF&((data)<<0))
#define SYS_PLL_SSC_DIG_SCPU_DBG1_DIVN_SCPU_src(data)                                ((0x000000FF&(data))>>0)
#define SYS_PLL_SSC_DIG_SCPU_DBG1_get_DIVN_SCPU(data)                                ((0x000000FF&(data))>>0)


#define SYS_PLL_SSC_DIG_SCPU_DBG2                                                    0x9800051C
#define SYS_PLL_SSC_DIG_SCPU_DBG2_reg_addr                                           "0x9800051C"
#define SYS_PLL_SSC_DIG_SCPU_DBG2_reg                                                0x9800051C
#define set_SYS_PLL_SSC_DIG_SCPU_DBG2_reg(data)   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_SCPU_DBG2_reg)=data)
#define get_SYS_PLL_SSC_DIG_SCPU_DBG2_reg   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_SCPU_DBG2_reg))
#define SYS_PLL_SSC_DIG_SCPU_DBG2_inst_adr                                           "0x0047"
#define SYS_PLL_SSC_DIG_SCPU_DBG2_inst                                               0x0047
#define SYS_PLL_SSC_DIG_SCPU_DBG2_load_FCW_SCPU_shift                                (21)
#define SYS_PLL_SSC_DIG_SCPU_DBG2_load_FCW_SCPU_mask                                 (0x00200000)
#define SYS_PLL_SSC_DIG_SCPU_DBG2_load_FCW_SCPU(data)                                (0x00200000&((data)<<21))
#define SYS_PLL_SSC_DIG_SCPU_DBG2_load_FCW_SCPU_src(data)                            ((0x00200000&(data))>>21)
#define SYS_PLL_SSC_DIG_SCPU_DBG2_get_load_FCW_SCPU(data)                            ((0x00200000&(data))>>21)
#define SYS_PLL_SSC_DIG_SCPU_DBG2_OC_DONE_SCPU_shift                                 (20)
#define SYS_PLL_SSC_DIG_SCPU_DBG2_OC_DONE_SCPU_mask                                  (0x00100000)
#define SYS_PLL_SSC_DIG_SCPU_DBG2_OC_DONE_SCPU(data)                                 (0x00100000&((data)<<20))
#define SYS_PLL_SSC_DIG_SCPU_DBG2_OC_DONE_SCPU_src(data)                             ((0x00100000&(data))>>20)
#define SYS_PLL_SSC_DIG_SCPU_DBG2_get_OC_DONE_SCPU(data)                             ((0x00100000&(data))>>20)
#define SYS_PLL_SSC_DIG_SCPU_DBG2_FMOD_SCPU_shift                                    (19)
#define SYS_PLL_SSC_DIG_SCPU_DBG2_FMOD_SCPU_mask                                     (0x00080000)
#define SYS_PLL_SSC_DIG_SCPU_DBG2_FMOD_SCPU(data)                                    (0x00080000&((data)<<19))
#define SYS_PLL_SSC_DIG_SCPU_DBG2_FMOD_SCPU_src(data)                                ((0x00080000&(data))>>19)
#define SYS_PLL_SSC_DIG_SCPU_DBG2_get_FMOD_SCPU(data)                                ((0x00080000&(data))>>19)
#define SYS_PLL_SSC_DIG_SCPU_DBG2_NCODE_DEBUG_SCPU_shift                             (11)
#define SYS_PLL_SSC_DIG_SCPU_DBG2_NCODE_DEBUG_SCPU_mask                              (0x0007F800)
#define SYS_PLL_SSC_DIG_SCPU_DBG2_NCODE_DEBUG_SCPU(data)                             (0x0007F800&((data)<<11))
#define SYS_PLL_SSC_DIG_SCPU_DBG2_NCODE_DEBUG_SCPU_src(data)                         ((0x0007F800&(data))>>11)
#define SYS_PLL_SSC_DIG_SCPU_DBG2_get_NCODE_DEBUG_SCPU(data)                         ((0x0007F800&(data))>>11)
#define SYS_PLL_SSC_DIG_SCPU_DBG2_FCODE_DEBUG_SCPU_shift                             (0)
#define SYS_PLL_SSC_DIG_SCPU_DBG2_FCODE_DEBUG_SCPU_mask                              (0x000007FF)
#define SYS_PLL_SSC_DIG_SCPU_DBG2_FCODE_DEBUG_SCPU(data)                             (0x000007FF&((data)<<0))
#define SYS_PLL_SSC_DIG_SCPU_DBG2_FCODE_DEBUG_SCPU_src(data)                         ((0x000007FF&(data))>>0)
#define SYS_PLL_SSC_DIG_SCPU_DBG2_get_FCODE_DEBUG_SCPU(data)                         ((0x000007FF&(data))>>0)


#define SYS_PLL_SSC_DIG_BUS0                                                         0x98000520
#define SYS_PLL_SSC_DIG_BUS0_reg_addr                                                "0x98000520"
#define SYS_PLL_SSC_DIG_BUS0_reg                                                     0x98000520
#define set_SYS_PLL_SSC_DIG_BUS0_reg(data)   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_BUS0_reg)=data)
#define get_SYS_PLL_SSC_DIG_BUS0_reg   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_BUS0_reg))
#define SYS_PLL_SSC_DIG_BUS0_inst_adr                                                "0x0048"
#define SYS_PLL_SSC_DIG_BUS0_inst                                                    0x0048
#define SYS_PLL_SSC_DIG_BUS0_REG_CKSSC_INV_BUS_shift                                 (4)
#define SYS_PLL_SSC_DIG_BUS0_REG_CKSSC_INV_BUS_mask                                  (0x00000010)
#define SYS_PLL_SSC_DIG_BUS0_REG_CKSSC_INV_BUS(data)                                 (0x00000010&((data)<<4))
#define SYS_PLL_SSC_DIG_BUS0_REG_CKSSC_INV_BUS_src(data)                             ((0x00000010&(data))>>4)
#define SYS_PLL_SSC_DIG_BUS0_get_REG_CKSSC_INV_BUS(data)                             ((0x00000010&(data))>>4)
#define SYS_PLL_SSC_DIG_BUS0_REG_GRAN_AUTO_RST_BUS_shift                             (3)
#define SYS_PLL_SSC_DIG_BUS0_REG_GRAN_AUTO_RST_BUS_mask                              (0x00000008)
#define SYS_PLL_SSC_DIG_BUS0_REG_GRAN_AUTO_RST_BUS(data)                             (0x00000008&((data)<<3))
#define SYS_PLL_SSC_DIG_BUS0_REG_GRAN_AUTO_RST_BUS_src(data)                         ((0x00000008&(data))>>3)
#define SYS_PLL_SSC_DIG_BUS0_get_REG_GRAN_AUTO_RST_BUS(data)                         ((0x00000008&(data))>>3)
#define SYS_PLL_SSC_DIG_BUS0_RSTB_BUS_shift                                          (2)
#define SYS_PLL_SSC_DIG_BUS0_RSTB_BUS_mask                                           (0x00000004)
#define SYS_PLL_SSC_DIG_BUS0_RSTB_BUS(data)                                          (0x00000004&((data)<<2))
#define SYS_PLL_SSC_DIG_BUS0_RSTB_BUS_src(data)                                      ((0x00000004&(data))>>2)
#define SYS_PLL_SSC_DIG_BUS0_get_RSTB_BUS(data)                                      ((0x00000004&(data))>>2)
#define SYS_PLL_SSC_DIG_BUS0_EN_SSC_BUS_shift                                        (1)
#define SYS_PLL_SSC_DIG_BUS0_EN_SSC_BUS_mask                                         (0x00000002)
#define SYS_PLL_SSC_DIG_BUS0_EN_SSC_BUS(data)                                        (0x00000002&((data)<<1))
#define SYS_PLL_SSC_DIG_BUS0_EN_SSC_BUS_src(data)                                    ((0x00000002&(data))>>1)
#define SYS_PLL_SSC_DIG_BUS0_get_EN_SSC_BUS(data)                                    ((0x00000002&(data))>>1)
#define SYS_PLL_SSC_DIG_BUS0_OC_EN_BUS_shift                                         (0)
#define SYS_PLL_SSC_DIG_BUS0_OC_EN_BUS_mask                                          (0x00000001)
#define SYS_PLL_SSC_DIG_BUS0_OC_EN_BUS(data)                                         (0x00000001&((data)<<0))
#define SYS_PLL_SSC_DIG_BUS0_OC_EN_BUS_src(data)                                     ((0x00000001&(data))>>0)
#define SYS_PLL_SSC_DIG_BUS0_get_OC_EN_BUS(data)                                     ((0x00000001&(data))>>0)


#define SYS_PLL_SSC_DIG_BUS1                                                         0x98000524
#define SYS_PLL_SSC_DIG_BUS1_reg_addr                                                "0x98000524"
#define SYS_PLL_SSC_DIG_BUS1_reg                                                     0x98000524
#define set_SYS_PLL_SSC_DIG_BUS1_reg(data)   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_BUS1_reg)=data)
#define get_SYS_PLL_SSC_DIG_BUS1_reg   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_BUS1_reg))
#define SYS_PLL_SSC_DIG_BUS1_inst_adr                                                "0x0049"
#define SYS_PLL_SSC_DIG_BUS1_inst                                                    0x0049
#define SYS_PLL_SSC_DIG_BUS1_NCODE_T_BUS_shift                                       (11)
#define SYS_PLL_SSC_DIG_BUS1_NCODE_T_BUS_mask                                        (0x0007F800)
#define SYS_PLL_SSC_DIG_BUS1_NCODE_T_BUS(data)                                       (0x0007F800&((data)<<11))
#define SYS_PLL_SSC_DIG_BUS1_NCODE_T_BUS_src(data)                                   ((0x0007F800&(data))>>11)
#define SYS_PLL_SSC_DIG_BUS1_get_NCODE_T_BUS(data)                                   ((0x0007F800&(data))>>11)
#define SYS_PLL_SSC_DIG_BUS1_FCODE_T_BUS_shift                                       (0)
#define SYS_PLL_SSC_DIG_BUS1_FCODE_T_BUS_mask                                        (0x000007FF)
#define SYS_PLL_SSC_DIG_BUS1_FCODE_T_BUS(data)                                       (0x000007FF&((data)<<0))
#define SYS_PLL_SSC_DIG_BUS1_FCODE_T_BUS_src(data)                                   ((0x000007FF&(data))>>0)
#define SYS_PLL_SSC_DIG_BUS1_get_FCODE_T_BUS(data)                                   ((0x000007FF&(data))>>0)


#define SYS_PLL_SSC_DIG_BUS2                                                         0x98000528
#define SYS_PLL_SSC_DIG_BUS2_reg_addr                                                "0x98000528"
#define SYS_PLL_SSC_DIG_BUS2_reg                                                     0x98000528
#define set_SYS_PLL_SSC_DIG_BUS2_reg(data)   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_BUS2_reg)=data)
#define get_SYS_PLL_SSC_DIG_BUS2_reg   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_BUS2_reg))
#define SYS_PLL_SSC_DIG_BUS2_inst_adr                                                "0x004A"
#define SYS_PLL_SSC_DIG_BUS2_inst                                                    0x004A
#define SYS_PLL_SSC_DIG_BUS2_REG_BYPASS_DIVN_shift                                   (27)
#define SYS_PLL_SSC_DIG_BUS2_REG_BYPASS_DIVN_mask                                    (0x08000000)
#define SYS_PLL_SSC_DIG_BUS2_REG_BYPASS_DIVN(data)                                   (0x08000000&((data)<<27))
#define SYS_PLL_SSC_DIG_BUS2_REG_BYPASS_DIVN_src(data)                               ((0x08000000&(data))>>27)
#define SYS_PLL_SSC_DIG_BUS2_get_REG_BYPASS_DIVN(data)                               ((0x08000000&(data))>>27)
#define SYS_PLL_SSC_DIG_BUS2_REG_OC_STEP_SET_BUS_shift                               (17)
#define SYS_PLL_SSC_DIG_BUS2_REG_OC_STEP_SET_BUS_mask                                (0x07FE0000)
#define SYS_PLL_SSC_DIG_BUS2_REG_OC_STEP_SET_BUS(data)                               (0x07FE0000&((data)<<17))
#define SYS_PLL_SSC_DIG_BUS2_REG_OC_STEP_SET_BUS_src(data)                           ((0x07FE0000&(data))>>17)
#define SYS_PLL_SSC_DIG_BUS2_get_REG_OC_STEP_SET_BUS(data)                           ((0x07FE0000&(data))>>17)
#define SYS_PLL_SSC_DIG_BUS2_REG_SEL_OC_MODE_BUS_shift                               (15)
#define SYS_PLL_SSC_DIG_BUS2_REG_SEL_OC_MODE_BUS_mask                                (0x00018000)
#define SYS_PLL_SSC_DIG_BUS2_REG_SEL_OC_MODE_BUS(data)                               (0x00018000&((data)<<15))
#define SYS_PLL_SSC_DIG_BUS2_REG_SEL_OC_MODE_BUS_src(data)                           ((0x00018000&(data))>>15)
#define SYS_PLL_SSC_DIG_BUS2_get_REG_SEL_OC_MODE_BUS(data)                           ((0x00018000&(data))>>15)
#define SYS_PLL_SSC_DIG_BUS2_REG_HS_OC_STOP_DIFF_BUS_shift                           (13)
#define SYS_PLL_SSC_DIG_BUS2_REG_HS_OC_STOP_DIFF_BUS_mask                            (0x00006000)
#define SYS_PLL_SSC_DIG_BUS2_REG_HS_OC_STOP_DIFF_BUS(data)                           (0x00006000&((data)<<13))
#define SYS_PLL_SSC_DIG_BUS2_REG_HS_OC_STOP_DIFF_BUS_src(data)                       ((0x00006000&(data))>>13)
#define SYS_PLL_SSC_DIG_BUS2_get_REG_HS_OC_STOP_DIFF_BUS(data)                       ((0x00006000&(data))>>13)
#define SYS_PLL_SSC_DIG_BUS2_REG_OC_DONE_DELAY_BUS_shift                             (7)
#define SYS_PLL_SSC_DIG_BUS2_REG_OC_DONE_DELAY_BUS_mask                              (0x00001F80)
#define SYS_PLL_SSC_DIG_BUS2_REG_OC_DONE_DELAY_BUS(data)                             (0x00001F80&((data)<<7))
#define SYS_PLL_SSC_DIG_BUS2_REG_OC_DONE_DELAY_BUS_src(data)                         ((0x00001F80&(data))>>7)
#define SYS_PLL_SSC_DIG_BUS2_get_REG_OC_DONE_DELAY_BUS(data)                         ((0x00001F80&(data))>>7)
#define SYS_PLL_SSC_DIG_BUS2_REG_BYPASS_PI_BUS_shift                                 (6)
#define SYS_PLL_SSC_DIG_BUS2_REG_BYPASS_PI_BUS_mask                                  (0x00000040)
#define SYS_PLL_SSC_DIG_BUS2_REG_BYPASS_PI_BUS(data)                                 (0x00000040&((data)<<6))
#define SYS_PLL_SSC_DIG_BUS2_REG_BYPASS_PI_BUS_src(data)                             ((0x00000040&(data))>>6)
#define SYS_PLL_SSC_DIG_BUS2_get_REG_BYPASS_PI_BUS(data)                             ((0x00000040&(data))>>6)
#define SYS_PLL_SSC_DIG_BUS2_REG_SDM_ORDER_BUS_shift                                 (5)
#define SYS_PLL_SSC_DIG_BUS2_REG_SDM_ORDER_BUS_mask                                  (0x00000020)
#define SYS_PLL_SSC_DIG_BUS2_REG_SDM_ORDER_BUS(data)                                 (0x00000020&((data)<<5))
#define SYS_PLL_SSC_DIG_BUS2_REG_SDM_ORDER_BUS_src(data)                             ((0x00000020&(data))>>5)
#define SYS_PLL_SSC_DIG_BUS2_get_REG_SDM_ORDER_BUS(data)                             ((0x00000020&(data))>>5)
#define SYS_PLL_SSC_DIG_BUS2_REG_PI_CUR_SEL_BUS_shift                                (2)
#define SYS_PLL_SSC_DIG_BUS2_REG_PI_CUR_SEL_BUS_mask                                 (0x0000001C)
#define SYS_PLL_SSC_DIG_BUS2_REG_PI_CUR_SEL_BUS(data)                                (0x0000001C&((data)<<2))
#define SYS_PLL_SSC_DIG_BUS2_REG_PI_CUR_SEL_BUS_src(data)                            ((0x0000001C&(data))>>2)
#define SYS_PLL_SSC_DIG_BUS2_get_REG_PI_CUR_SEL_BUS(data)                            ((0x0000001C&(data))>>2)
#define SYS_PLL_SSC_DIG_BUS2_REG_EN_PI_DEBUG_BUS_shift                               (1)
#define SYS_PLL_SSC_DIG_BUS2_REG_EN_PI_DEBUG_BUS_mask                                (0x00000002)
#define SYS_PLL_SSC_DIG_BUS2_REG_EN_PI_DEBUG_BUS(data)                               (0x00000002&((data)<<1))
#define SYS_PLL_SSC_DIG_BUS2_REG_EN_PI_DEBUG_BUS_src(data)                           ((0x00000002&(data))>>1)
#define SYS_PLL_SSC_DIG_BUS2_get_REG_EN_PI_DEBUG_BUS(data)                           ((0x00000002&(data))>>1)


#define SYS_PLL_SSC_DIG_BUS3                                                         0x9800052C
#define SYS_PLL_SSC_DIG_BUS3_reg_addr                                                "0x9800052C"
#define SYS_PLL_SSC_DIG_BUS3_reg                                                     0x9800052C
#define set_SYS_PLL_SSC_DIG_BUS3_reg(data)   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_BUS3_reg)=data)
#define get_SYS_PLL_SSC_DIG_BUS3_reg   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_BUS3_reg))
#define SYS_PLL_SSC_DIG_BUS3_inst_adr                                                "0x004B"
#define SYS_PLL_SSC_DIG_BUS3_inst                                                    0x004B
#define SYS_PLL_SSC_DIG_BUS3_NCODE_SSC_BUS_shift                                     (11)
#define SYS_PLL_SSC_DIG_BUS3_NCODE_SSC_BUS_mask                                      (0x0007F800)
#define SYS_PLL_SSC_DIG_BUS3_NCODE_SSC_BUS(data)                                     (0x0007F800&((data)<<11))
#define SYS_PLL_SSC_DIG_BUS3_NCODE_SSC_BUS_src(data)                                 ((0x0007F800&(data))>>11)
#define SYS_PLL_SSC_DIG_BUS3_get_NCODE_SSC_BUS(data)                                 ((0x0007F800&(data))>>11)
#define SYS_PLL_SSC_DIG_BUS3_FCODE_SSC_BUS_shift                                     (0)
#define SYS_PLL_SSC_DIG_BUS3_FCODE_SSC_BUS_mask                                      (0x000007FF)
#define SYS_PLL_SSC_DIG_BUS3_FCODE_SSC_BUS(data)                                     (0x000007FF&((data)<<0))
#define SYS_PLL_SSC_DIG_BUS3_FCODE_SSC_BUS_src(data)                                 ((0x000007FF&(data))>>0)
#define SYS_PLL_SSC_DIG_BUS3_get_FCODE_SSC_BUS(data)                                 ((0x000007FF&(data))>>0)


#define SYS_PLL_SSC_DIG_BUS4                                                         0x98000530
#define SYS_PLL_SSC_DIG_BUS4_reg_addr                                                "0x98000530"
#define SYS_PLL_SSC_DIG_BUS4_reg                                                     0x98000530
#define set_SYS_PLL_SSC_DIG_BUS4_reg(data)   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_BUS4_reg)=data)
#define get_SYS_PLL_SSC_DIG_BUS4_reg   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_BUS4_reg))
#define SYS_PLL_SSC_DIG_BUS4_inst_adr                                                "0x004C"
#define SYS_PLL_SSC_DIG_BUS4_inst                                                    0x004C
#define SYS_PLL_SSC_DIG_BUS4_GRAN_EST_BUS_shift                                      (0)
#define SYS_PLL_SSC_DIG_BUS4_GRAN_EST_BUS_mask                                       (0x0007FFFF)
#define SYS_PLL_SSC_DIG_BUS4_GRAN_EST_BUS(data)                                      (0x0007FFFF&((data)<<0))
#define SYS_PLL_SSC_DIG_BUS4_GRAN_EST_BUS_src(data)                                  ((0x0007FFFF&(data))>>0)
#define SYS_PLL_SSC_DIG_BUS4_get_GRAN_EST_BUS(data)                                  ((0x0007FFFF&(data))>>0)


#define SYS_PLL_SSC_DIG_BUS5                                                         0x98000534
#define SYS_PLL_SSC_DIG_BUS5_reg_addr                                                "0x98000534"
#define SYS_PLL_SSC_DIG_BUS5_reg                                                     0x98000534
#define set_SYS_PLL_SSC_DIG_BUS5_reg(data)   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_BUS5_reg)=data)
#define get_SYS_PLL_SSC_DIG_BUS5_reg   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_BUS5_reg))
#define SYS_PLL_SSC_DIG_BUS5_inst_adr                                                "0x004D"
#define SYS_PLL_SSC_DIG_BUS5_inst                                                    0x004D
#define SYS_PLL_SSC_DIG_BUS5_FCW_SSC_DEFAULT_BUS_shift                               (0)
#define SYS_PLL_SSC_DIG_BUS5_FCW_SSC_DEFAULT_BUS_mask                                (0x0007FFFF)
#define SYS_PLL_SSC_DIG_BUS5_FCW_SSC_DEFAULT_BUS(data)                               (0x0007FFFF&((data)<<0))
#define SYS_PLL_SSC_DIG_BUS5_FCW_SSC_DEFAULT_BUS_src(data)                           ((0x0007FFFF&(data))>>0)
#define SYS_PLL_SSC_DIG_BUS5_get_FCW_SSC_DEFAULT_BUS(data)                           ((0x0007FFFF&(data))>>0)


#define SYS_PLL_SSC_DIG_BUS_DBG1                                                     0x98000538
#define SYS_PLL_SSC_DIG_BUS_DBG1_reg_addr                                            "0x98000538"
#define SYS_PLL_SSC_DIG_BUS_DBG1_reg                                                 0x98000538
#define set_SYS_PLL_SSC_DIG_BUS_DBG1_reg(data)   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_BUS_DBG1_reg)=data)
#define get_SYS_PLL_SSC_DIG_BUS_DBG1_reg   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_BUS_DBG1_reg))
#define SYS_PLL_SSC_DIG_BUS_DBG1_inst_adr                                            "0x004E"
#define SYS_PLL_SSC_DIG_BUS_DBG1_inst                                                0x004E
#define SYS_PLL_SSC_DIG_BUS_DBG1_LOOP_PI_ISEL_BUS_shift                              (13)
#define SYS_PLL_SSC_DIG_BUS_DBG1_LOOP_PI_ISEL_BUS_mask                               (0x0000E000)
#define SYS_PLL_SSC_DIG_BUS_DBG1_LOOP_PI_ISEL_BUS(data)                              (0x0000E000&((data)<<13))
#define SYS_PLL_SSC_DIG_BUS_DBG1_LOOP_PI_ISEL_BUS_src(data)                          ((0x0000E000&(data))>>13)
#define SYS_PLL_SSC_DIG_BUS_DBG1_get_LOOP_PI_ISEL_BUS(data)                          ((0x0000E000&(data))>>13)
#define SYS_PLL_SSC_DIG_BUS_DBG1_PHSEL_BUS_shift                                     (8)
#define SYS_PLL_SSC_DIG_BUS_DBG1_PHSEL_BUS_mask                                      (0x00001F00)
#define SYS_PLL_SSC_DIG_BUS_DBG1_PHSEL_BUS(data)                                     (0x00001F00&((data)<<8))
#define SYS_PLL_SSC_DIG_BUS_DBG1_PHSEL_BUS_src(data)                                 ((0x00001F00&(data))>>8)
#define SYS_PLL_SSC_DIG_BUS_DBG1_get_PHSEL_BUS(data)                                 ((0x00001F00&(data))>>8)
#define SYS_PLL_SSC_DIG_BUS_DBG1_DIVN_BUS_shift                                      (0)
#define SYS_PLL_SSC_DIG_BUS_DBG1_DIVN_BUS_mask                                       (0x000000FF)
#define SYS_PLL_SSC_DIG_BUS_DBG1_DIVN_BUS(data)                                      (0x000000FF&((data)<<0))
#define SYS_PLL_SSC_DIG_BUS_DBG1_DIVN_BUS_src(data)                                  ((0x000000FF&(data))>>0)
#define SYS_PLL_SSC_DIG_BUS_DBG1_get_DIVN_BUS(data)                                  ((0x000000FF&(data))>>0)


#define SYS_PLL_SSC_DIG_BUS_DBG2                                                     0x9800053C
#define SYS_PLL_SSC_DIG_BUS_DBG2_reg_addr                                            "0x9800053C"
#define SYS_PLL_SSC_DIG_BUS_DBG2_reg                                                 0x9800053C
#define set_SYS_PLL_SSC_DIG_BUS_DBG2_reg(data)   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_BUS_DBG2_reg)=data)
#define get_SYS_PLL_SSC_DIG_BUS_DBG2_reg   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_BUS_DBG2_reg))
#define SYS_PLL_SSC_DIG_BUS_DBG2_inst_adr                                            "0x004F"
#define SYS_PLL_SSC_DIG_BUS_DBG2_inst                                                0x004F
#define SYS_PLL_SSC_DIG_BUS_DBG2_load_FCW_BUS_shift                                  (21)
#define SYS_PLL_SSC_DIG_BUS_DBG2_load_FCW_BUS_mask                                   (0x00200000)
#define SYS_PLL_SSC_DIG_BUS_DBG2_load_FCW_BUS(data)                                  (0x00200000&((data)<<21))
#define SYS_PLL_SSC_DIG_BUS_DBG2_load_FCW_BUS_src(data)                              ((0x00200000&(data))>>21)
#define SYS_PLL_SSC_DIG_BUS_DBG2_get_load_FCW_BUS(data)                              ((0x00200000&(data))>>21)
#define SYS_PLL_SSC_DIG_BUS_DBG2_OC_DONE_BUS_shift                                   (20)
#define SYS_PLL_SSC_DIG_BUS_DBG2_OC_DONE_BUS_mask                                    (0x00100000)
#define SYS_PLL_SSC_DIG_BUS_DBG2_OC_DONE_BUS(data)                                   (0x00100000&((data)<<20))
#define SYS_PLL_SSC_DIG_BUS_DBG2_OC_DONE_BUS_src(data)                               ((0x00100000&(data))>>20)
#define SYS_PLL_SSC_DIG_BUS_DBG2_get_OC_DONE_BUS(data)                               ((0x00100000&(data))>>20)
#define SYS_PLL_SSC_DIG_BUS_DBG2_FMOD_BUS_shift                                      (19)
#define SYS_PLL_SSC_DIG_BUS_DBG2_FMOD_BUS_mask                                       (0x00080000)
#define SYS_PLL_SSC_DIG_BUS_DBG2_FMOD_BUS(data)                                      (0x00080000&((data)<<19))
#define SYS_PLL_SSC_DIG_BUS_DBG2_FMOD_BUS_src(data)                                  ((0x00080000&(data))>>19)
#define SYS_PLL_SSC_DIG_BUS_DBG2_get_FMOD_BUS(data)                                  ((0x00080000&(data))>>19)
#define SYS_PLL_SSC_DIG_BUS_DBG2_NCODE_DEBUG_BUS_shift                               (11)
#define SYS_PLL_SSC_DIG_BUS_DBG2_NCODE_DEBUG_BUS_mask                                (0x0007F800)
#define SYS_PLL_SSC_DIG_BUS_DBG2_NCODE_DEBUG_BUS(data)                               (0x0007F800&((data)<<11))
#define SYS_PLL_SSC_DIG_BUS_DBG2_NCODE_DEBUG_BUS_src(data)                           ((0x0007F800&(data))>>11)
#define SYS_PLL_SSC_DIG_BUS_DBG2_get_NCODE_DEBUG_BUS(data)                           ((0x0007F800&(data))>>11)
#define SYS_PLL_SSC_DIG_BUS_DBG2_FCODE_DEBUG_BUS_shift                               (0)
#define SYS_PLL_SSC_DIG_BUS_DBG2_FCODE_DEBUG_BUS_mask                                (0x000007FF)
#define SYS_PLL_SSC_DIG_BUS_DBG2_FCODE_DEBUG_BUS(data)                               (0x000007FF&((data)<<0))
#define SYS_PLL_SSC_DIG_BUS_DBG2_FCODE_DEBUG_BUS_src(data)                           ((0x000007FF&(data))>>0)
#define SYS_PLL_SSC_DIG_BUS_DBG2_get_FCODE_DEBUG_BUS(data)                           ((0x000007FF&(data))>>0)


#define SYS_PLL_SSC_DIG_BUSH0                                                        0x98000540
#define SYS_PLL_SSC_DIG_BUSH0_reg_addr                                               "0x98000540"
#define SYS_PLL_SSC_DIG_BUSH0_reg                                                    0x98000540
#define set_SYS_PLL_SSC_DIG_BUSH0_reg(data)   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_BUSH0_reg)=data)
#define get_SYS_PLL_SSC_DIG_BUSH0_reg   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_BUSH0_reg))
#define SYS_PLL_SSC_DIG_BUSH0_inst_adr                                               "0x0050"
#define SYS_PLL_SSC_DIG_BUSH0_inst                                                   0x0050
#define SYS_PLL_SSC_DIG_BUSH0_REG_CKSSC_INV_BUS_H_shift                              (4)
#define SYS_PLL_SSC_DIG_BUSH0_REG_CKSSC_INV_BUS_H_mask                               (0x00000010)
#define SYS_PLL_SSC_DIG_BUSH0_REG_CKSSC_INV_BUS_H(data)                              (0x00000010&((data)<<4))
#define SYS_PLL_SSC_DIG_BUSH0_REG_CKSSC_INV_BUS_H_src(data)                          ((0x00000010&(data))>>4)
#define SYS_PLL_SSC_DIG_BUSH0_get_REG_CKSSC_INV_BUS_H(data)                          ((0x00000010&(data))>>4)
#define SYS_PLL_SSC_DIG_BUSH0_REG_GRAN_AUTO_RST_BUS_H_shift                          (3)
#define SYS_PLL_SSC_DIG_BUSH0_REG_GRAN_AUTO_RST_BUS_H_mask                           (0x00000008)
#define SYS_PLL_SSC_DIG_BUSH0_REG_GRAN_AUTO_RST_BUS_H(data)                          (0x00000008&((data)<<3))
#define SYS_PLL_SSC_DIG_BUSH0_REG_GRAN_AUTO_RST_BUS_H_src(data)                      ((0x00000008&(data))>>3)
#define SYS_PLL_SSC_DIG_BUSH0_get_REG_GRAN_AUTO_RST_BUS_H(data)                      ((0x00000008&(data))>>3)
#define SYS_PLL_SSC_DIG_BUSH0_RSTB_BUS_H_shift                                       (2)
#define SYS_PLL_SSC_DIG_BUSH0_RSTB_BUS_H_mask                                        (0x00000004)
#define SYS_PLL_SSC_DIG_BUSH0_RSTB_BUS_H(data)                                       (0x00000004&((data)<<2))
#define SYS_PLL_SSC_DIG_BUSH0_RSTB_BUS_H_src(data)                                   ((0x00000004&(data))>>2)
#define SYS_PLL_SSC_DIG_BUSH0_get_RSTB_BUS_H(data)                                   ((0x00000004&(data))>>2)
#define SYS_PLL_SSC_DIG_BUSH0_EN_SSC_BUS_H_shift                                     (1)
#define SYS_PLL_SSC_DIG_BUSH0_EN_SSC_BUS_H_mask                                      (0x00000002)
#define SYS_PLL_SSC_DIG_BUSH0_EN_SSC_BUS_H(data)                                     (0x00000002&((data)<<1))
#define SYS_PLL_SSC_DIG_BUSH0_EN_SSC_BUS_H_src(data)                                 ((0x00000002&(data))>>1)
#define SYS_PLL_SSC_DIG_BUSH0_get_EN_SSC_BUS_H(data)                                 ((0x00000002&(data))>>1)
#define SYS_PLL_SSC_DIG_BUSH0_OC_EN_BUS_H_shift                                      (0)
#define SYS_PLL_SSC_DIG_BUSH0_OC_EN_BUS_H_mask                                       (0x00000001)
#define SYS_PLL_SSC_DIG_BUSH0_OC_EN_BUS_H(data)                                      (0x00000001&((data)<<0))
#define SYS_PLL_SSC_DIG_BUSH0_OC_EN_BUS_H_src(data)                                  ((0x00000001&(data))>>0)
#define SYS_PLL_SSC_DIG_BUSH0_get_OC_EN_BUS_H(data)                                  ((0x00000001&(data))>>0)


#define SYS_PLL_SSC_DIG_BUSH1                                                        0x98000544
#define SYS_PLL_SSC_DIG_BUSH1_reg_addr                                               "0x98000544"
#define SYS_PLL_SSC_DIG_BUSH1_reg                                                    0x98000544
#define set_SYS_PLL_SSC_DIG_BUSH1_reg(data)   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_BUSH1_reg)=data)
#define get_SYS_PLL_SSC_DIG_BUSH1_reg   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_BUSH1_reg))
#define SYS_PLL_SSC_DIG_BUSH1_inst_adr                                               "0x0051"
#define SYS_PLL_SSC_DIG_BUSH1_inst                                                   0x0051
#define SYS_PLL_SSC_DIG_BUSH1_NCODE_T_BUS_H_shift                                    (11)
#define SYS_PLL_SSC_DIG_BUSH1_NCODE_T_BUS_H_mask                                     (0x0007F800)
#define SYS_PLL_SSC_DIG_BUSH1_NCODE_T_BUS_H(data)                                    (0x0007F800&((data)<<11))
#define SYS_PLL_SSC_DIG_BUSH1_NCODE_T_BUS_H_src(data)                                ((0x0007F800&(data))>>11)
#define SYS_PLL_SSC_DIG_BUSH1_get_NCODE_T_BUS_H(data)                                ((0x0007F800&(data))>>11)
#define SYS_PLL_SSC_DIG_BUSH1_FCODE_T_BUS_H_shift                                    (0)
#define SYS_PLL_SSC_DIG_BUSH1_FCODE_T_BUS_H_mask                                     (0x000007FF)
#define SYS_PLL_SSC_DIG_BUSH1_FCODE_T_BUS_H(data)                                    (0x000007FF&((data)<<0))
#define SYS_PLL_SSC_DIG_BUSH1_FCODE_T_BUS_H_src(data)                                ((0x000007FF&(data))>>0)
#define SYS_PLL_SSC_DIG_BUSH1_get_FCODE_T_BUS_H(data)                                ((0x000007FF&(data))>>0)


#define SYS_PLL_SSC_DIG_BUSH2                                                        0x98000548
#define SYS_PLL_SSC_DIG_BUSH2_reg_addr                                               "0x98000548"
#define SYS_PLL_SSC_DIG_BUSH2_reg                                                    0x98000548
#define set_SYS_PLL_SSC_DIG_BUSH2_reg(data)   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_BUSH2_reg)=data)
#define get_SYS_PLL_SSC_DIG_BUSH2_reg   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_BUSH2_reg))
#define SYS_PLL_SSC_DIG_BUSH2_inst_adr                                               "0x0052"
#define SYS_PLL_SSC_DIG_BUSH2_inst                                                   0x0052
#define SYS_PLL_SSC_DIG_BUSH2_REG_BYPASS_DIVN_shift                                  (27)
#define SYS_PLL_SSC_DIG_BUSH2_REG_BYPASS_DIVN_mask                                   (0x08000000)
#define SYS_PLL_SSC_DIG_BUSH2_REG_BYPASS_DIVN(data)                                  (0x08000000&((data)<<27))
#define SYS_PLL_SSC_DIG_BUSH2_REG_BYPASS_DIVN_src(data)                              ((0x08000000&(data))>>27)
#define SYS_PLL_SSC_DIG_BUSH2_get_REG_BYPASS_DIVN(data)                              ((0x08000000&(data))>>27)
#define SYS_PLL_SSC_DIG_BUSH2_REG_OC_STEP_SET_BUS_H_shift                            (17)
#define SYS_PLL_SSC_DIG_BUSH2_REG_OC_STEP_SET_BUS_H_mask                             (0x07FE0000)
#define SYS_PLL_SSC_DIG_BUSH2_REG_OC_STEP_SET_BUS_H(data)                            (0x07FE0000&((data)<<17))
#define SYS_PLL_SSC_DIG_BUSH2_REG_OC_STEP_SET_BUS_H_src(data)                        ((0x07FE0000&(data))>>17)
#define SYS_PLL_SSC_DIG_BUSH2_get_REG_OC_STEP_SET_BUS_H(data)                        ((0x07FE0000&(data))>>17)
#define SYS_PLL_SSC_DIG_BUSH2_REG_SEL_OC_MODE_BUS_H_shift                            (15)
#define SYS_PLL_SSC_DIG_BUSH2_REG_SEL_OC_MODE_BUS_H_mask                             (0x00018000)
#define SYS_PLL_SSC_DIG_BUSH2_REG_SEL_OC_MODE_BUS_H(data)                            (0x00018000&((data)<<15))
#define SYS_PLL_SSC_DIG_BUSH2_REG_SEL_OC_MODE_BUS_H_src(data)                        ((0x00018000&(data))>>15)
#define SYS_PLL_SSC_DIG_BUSH2_get_REG_SEL_OC_MODE_BUS_H(data)                        ((0x00018000&(data))>>15)
#define SYS_PLL_SSC_DIG_BUSH2_REG_HS_OC_STOP_DIFF_BUS_H_shift                        (13)
#define SYS_PLL_SSC_DIG_BUSH2_REG_HS_OC_STOP_DIFF_BUS_H_mask                         (0x00006000)
#define SYS_PLL_SSC_DIG_BUSH2_REG_HS_OC_STOP_DIFF_BUS_H(data)                        (0x00006000&((data)<<13))
#define SYS_PLL_SSC_DIG_BUSH2_REG_HS_OC_STOP_DIFF_BUS_H_src(data)                    ((0x00006000&(data))>>13)
#define SYS_PLL_SSC_DIG_BUSH2_get_REG_HS_OC_STOP_DIFF_BUS_H(data)                    ((0x00006000&(data))>>13)
#define SYS_PLL_SSC_DIG_BUSH2_REG_OC_DONE_DELAY_BUS_H_shift                          (7)
#define SYS_PLL_SSC_DIG_BUSH2_REG_OC_DONE_DELAY_BUS_H_mask                           (0x00001F80)
#define SYS_PLL_SSC_DIG_BUSH2_REG_OC_DONE_DELAY_BUS_H(data)                          (0x00001F80&((data)<<7))
#define SYS_PLL_SSC_DIG_BUSH2_REG_OC_DONE_DELAY_BUS_H_src(data)                      ((0x00001F80&(data))>>7)
#define SYS_PLL_SSC_DIG_BUSH2_get_REG_OC_DONE_DELAY_BUS_H(data)                      ((0x00001F80&(data))>>7)
#define SYS_PLL_SSC_DIG_BUSH2_REG_BYPASS_PI_BUS_H_shift                              (6)
#define SYS_PLL_SSC_DIG_BUSH2_REG_BYPASS_PI_BUS_H_mask                               (0x00000040)
#define SYS_PLL_SSC_DIG_BUSH2_REG_BYPASS_PI_BUS_H(data)                              (0x00000040&((data)<<6))
#define SYS_PLL_SSC_DIG_BUSH2_REG_BYPASS_PI_BUS_H_src(data)                          ((0x00000040&(data))>>6)
#define SYS_PLL_SSC_DIG_BUSH2_get_REG_BYPASS_PI_BUS_H(data)                          ((0x00000040&(data))>>6)
#define SYS_PLL_SSC_DIG_BUSH2_REG_SDM_ORDER_BUS_H_shift                              (5)
#define SYS_PLL_SSC_DIG_BUSH2_REG_SDM_ORDER_BUS_H_mask                               (0x00000020)
#define SYS_PLL_SSC_DIG_BUSH2_REG_SDM_ORDER_BUS_H(data)                              (0x00000020&((data)<<5))
#define SYS_PLL_SSC_DIG_BUSH2_REG_SDM_ORDER_BUS_H_src(data)                          ((0x00000020&(data))>>5)
#define SYS_PLL_SSC_DIG_BUSH2_get_REG_SDM_ORDER_BUS_H(data)                          ((0x00000020&(data))>>5)
#define SYS_PLL_SSC_DIG_BUSH2_REG_PI_CUR_SEL_BUS_H_shift                             (2)
#define SYS_PLL_SSC_DIG_BUSH2_REG_PI_CUR_SEL_BUS_H_mask                              (0x0000001C)
#define SYS_PLL_SSC_DIG_BUSH2_REG_PI_CUR_SEL_BUS_H(data)                             (0x0000001C&((data)<<2))
#define SYS_PLL_SSC_DIG_BUSH2_REG_PI_CUR_SEL_BUS_H_src(data)                         ((0x0000001C&(data))>>2)
#define SYS_PLL_SSC_DIG_BUSH2_get_REG_PI_CUR_SEL_BUS_H(data)                         ((0x0000001C&(data))>>2)
#define SYS_PLL_SSC_DIG_BUSH2_REG_EN_PI_DEBUG_BUS_H_shift                            (1)
#define SYS_PLL_SSC_DIG_BUSH2_REG_EN_PI_DEBUG_BUS_H_mask                             (0x00000002)
#define SYS_PLL_SSC_DIG_BUSH2_REG_EN_PI_DEBUG_BUS_H(data)                            (0x00000002&((data)<<1))
#define SYS_PLL_SSC_DIG_BUSH2_REG_EN_PI_DEBUG_BUS_H_src(data)                        ((0x00000002&(data))>>1)
#define SYS_PLL_SSC_DIG_BUSH2_get_REG_EN_PI_DEBUG_BUS_H(data)                        ((0x00000002&(data))>>1)


#define SYS_PLL_SSC_DIG_BUSH3                                                        0x9800054C
#define SYS_PLL_SSC_DIG_BUSH3_reg_addr                                               "0x9800054C"
#define SYS_PLL_SSC_DIG_BUSH3_reg                                                    0x9800054C
#define set_SYS_PLL_SSC_DIG_BUSH3_reg(data)   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_BUSH3_reg)=data)
#define get_SYS_PLL_SSC_DIG_BUSH3_reg   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_BUSH3_reg))
#define SYS_PLL_SSC_DIG_BUSH3_inst_adr                                               "0x0053"
#define SYS_PLL_SSC_DIG_BUSH3_inst                                                   0x0053
#define SYS_PLL_SSC_DIG_BUSH3_NCODE_SSC_BUS_H_shift                                  (11)
#define SYS_PLL_SSC_DIG_BUSH3_NCODE_SSC_BUS_H_mask                                   (0x0007F800)
#define SYS_PLL_SSC_DIG_BUSH3_NCODE_SSC_BUS_H(data)                                  (0x0007F800&((data)<<11))
#define SYS_PLL_SSC_DIG_BUSH3_NCODE_SSC_BUS_H_src(data)                              ((0x0007F800&(data))>>11)
#define SYS_PLL_SSC_DIG_BUSH3_get_NCODE_SSC_BUS_H(data)                              ((0x0007F800&(data))>>11)
#define SYS_PLL_SSC_DIG_BUSH3_FCODE_SSC_BUS_H_shift                                  (0)
#define SYS_PLL_SSC_DIG_BUSH3_FCODE_SSC_BUS_H_mask                                   (0x000007FF)
#define SYS_PLL_SSC_DIG_BUSH3_FCODE_SSC_BUS_H(data)                                  (0x000007FF&((data)<<0))
#define SYS_PLL_SSC_DIG_BUSH3_FCODE_SSC_BUS_H_src(data)                              ((0x000007FF&(data))>>0)
#define SYS_PLL_SSC_DIG_BUSH3_get_FCODE_SSC_BUS_H(data)                              ((0x000007FF&(data))>>0)


#define SYS_PLL_SSC_DIG_BUSH4                                                        0x98000550
#define SYS_PLL_SSC_DIG_BUSH4_reg_addr                                               "0x98000550"
#define SYS_PLL_SSC_DIG_BUSH4_reg                                                    0x98000550
#define set_SYS_PLL_SSC_DIG_BUSH4_reg(data)   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_BUSH4_reg)=data)
#define get_SYS_PLL_SSC_DIG_BUSH4_reg   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_BUSH4_reg))
#define SYS_PLL_SSC_DIG_BUSH4_inst_adr                                               "0x0054"
#define SYS_PLL_SSC_DIG_BUSH4_inst                                                   0x0054
#define SYS_PLL_SSC_DIG_BUSH4_GRAN_EST_BUS_H_shift                                   (0)
#define SYS_PLL_SSC_DIG_BUSH4_GRAN_EST_BUS_H_mask                                    (0x0007FFFF)
#define SYS_PLL_SSC_DIG_BUSH4_GRAN_EST_BUS_H(data)                                   (0x0007FFFF&((data)<<0))
#define SYS_PLL_SSC_DIG_BUSH4_GRAN_EST_BUS_H_src(data)                               ((0x0007FFFF&(data))>>0)
#define SYS_PLL_SSC_DIG_BUSH4_get_GRAN_EST_BUS_H(data)                               ((0x0007FFFF&(data))>>0)


#define SYS_PLL_SSC_DIG_BUSH5                                                        0x98000554
#define SYS_PLL_SSC_DIG_BUSH5_reg_addr                                               "0x98000554"
#define SYS_PLL_SSC_DIG_BUSH5_reg                                                    0x98000554
#define set_SYS_PLL_SSC_DIG_BUSH5_reg(data)   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_BUSH5_reg)=data)
#define get_SYS_PLL_SSC_DIG_BUSH5_reg   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_BUSH5_reg))
#define SYS_PLL_SSC_DIG_BUSH5_inst_adr                                               "0x0055"
#define SYS_PLL_SSC_DIG_BUSH5_inst                                                   0x0055
#define SYS_PLL_SSC_DIG_BUSH5_FCW_SSC_DEFAULT_BUS_H_shift                            (0)
#define SYS_PLL_SSC_DIG_BUSH5_FCW_SSC_DEFAULT_BUS_H_mask                             (0x0007FFFF)
#define SYS_PLL_SSC_DIG_BUSH5_FCW_SSC_DEFAULT_BUS_H(data)                            (0x0007FFFF&((data)<<0))
#define SYS_PLL_SSC_DIG_BUSH5_FCW_SSC_DEFAULT_BUS_H_src(data)                        ((0x0007FFFF&(data))>>0)
#define SYS_PLL_SSC_DIG_BUSH5_get_FCW_SSC_DEFAULT_BUS_H(data)                        ((0x0007FFFF&(data))>>0)


#define SYS_PLL_SSC_DIG_BUSH_DBG1                                                    0x98000558
#define SYS_PLL_SSC_DIG_BUSH_DBG1_reg_addr                                           "0x98000558"
#define SYS_PLL_SSC_DIG_BUSH_DBG1_reg                                                0x98000558
#define set_SYS_PLL_SSC_DIG_BUSH_DBG1_reg(data)   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_BUSH_DBG1_reg)=data)
#define get_SYS_PLL_SSC_DIG_BUSH_DBG1_reg   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_BUSH_DBG1_reg))
#define SYS_PLL_SSC_DIG_BUSH_DBG1_inst_adr                                           "0x0056"
#define SYS_PLL_SSC_DIG_BUSH_DBG1_inst                                               0x0056
#define SYS_PLL_SSC_DIG_BUSH_DBG1_LOOP_PI_ISEL_BUS_H_shift                           (13)
#define SYS_PLL_SSC_DIG_BUSH_DBG1_LOOP_PI_ISEL_BUS_H_mask                            (0x0000E000)
#define SYS_PLL_SSC_DIG_BUSH_DBG1_LOOP_PI_ISEL_BUS_H(data)                           (0x0000E000&((data)<<13))
#define SYS_PLL_SSC_DIG_BUSH_DBG1_LOOP_PI_ISEL_BUS_H_src(data)                       ((0x0000E000&(data))>>13)
#define SYS_PLL_SSC_DIG_BUSH_DBG1_get_LOOP_PI_ISEL_BUS_H(data)                       ((0x0000E000&(data))>>13)
#define SYS_PLL_SSC_DIG_BUSH_DBG1_PHSEL_BUS_H_shift                                  (8)
#define SYS_PLL_SSC_DIG_BUSH_DBG1_PHSEL_BUS_H_mask                                   (0x00001F00)
#define SYS_PLL_SSC_DIG_BUSH_DBG1_PHSEL_BUS_H(data)                                  (0x00001F00&((data)<<8))
#define SYS_PLL_SSC_DIG_BUSH_DBG1_PHSEL_BUS_H_src(data)                              ((0x00001F00&(data))>>8)
#define SYS_PLL_SSC_DIG_BUSH_DBG1_get_PHSEL_BUS_H(data)                              ((0x00001F00&(data))>>8)
#define SYS_PLL_SSC_DIG_BUSH_DBG1_DIVN_BUS_H_shift                                   (0)
#define SYS_PLL_SSC_DIG_BUSH_DBG1_DIVN_BUS_H_mask                                    (0x000000FF)
#define SYS_PLL_SSC_DIG_BUSH_DBG1_DIVN_BUS_H(data)                                   (0x000000FF&((data)<<0))
#define SYS_PLL_SSC_DIG_BUSH_DBG1_DIVN_BUS_H_src(data)                               ((0x000000FF&(data))>>0)
#define SYS_PLL_SSC_DIG_BUSH_DBG1_get_DIVN_BUS_H(data)                               ((0x000000FF&(data))>>0)


#define SYS_PLL_SSC_DIG_BUSH_DBG2                                                    0x9800055C
#define SYS_PLL_SSC_DIG_BUSH_DBG2_reg_addr                                           "0x9800055C"
#define SYS_PLL_SSC_DIG_BUSH_DBG2_reg                                                0x9800055C
#define set_SYS_PLL_SSC_DIG_BUSH_DBG2_reg(data)   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_BUSH_DBG2_reg)=data)
#define get_SYS_PLL_SSC_DIG_BUSH_DBG2_reg   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_BUSH_DBG2_reg))
#define SYS_PLL_SSC_DIG_BUSH_DBG2_inst_adr                                           "0x0057"
#define SYS_PLL_SSC_DIG_BUSH_DBG2_inst                                               0x0057
#define SYS_PLL_SSC_DIG_BUSH_DBG2_load_FCW_BUS_H_shift                               (21)
#define SYS_PLL_SSC_DIG_BUSH_DBG2_load_FCW_BUS_H_mask                                (0x00200000)
#define SYS_PLL_SSC_DIG_BUSH_DBG2_load_FCW_BUS_H(data)                               (0x00200000&((data)<<21))
#define SYS_PLL_SSC_DIG_BUSH_DBG2_load_FCW_BUS_H_src(data)                           ((0x00200000&(data))>>21)
#define SYS_PLL_SSC_DIG_BUSH_DBG2_get_load_FCW_BUS_H(data)                           ((0x00200000&(data))>>21)
#define SYS_PLL_SSC_DIG_BUSH_DBG2_OC_DONE_BUS_H_shift                                (20)
#define SYS_PLL_SSC_DIG_BUSH_DBG2_OC_DONE_BUS_H_mask                                 (0x00100000)
#define SYS_PLL_SSC_DIG_BUSH_DBG2_OC_DONE_BUS_H(data)                                (0x00100000&((data)<<20))
#define SYS_PLL_SSC_DIG_BUSH_DBG2_OC_DONE_BUS_H_src(data)                            ((0x00100000&(data))>>20)
#define SYS_PLL_SSC_DIG_BUSH_DBG2_get_OC_DONE_BUS_H(data)                            ((0x00100000&(data))>>20)
#define SYS_PLL_SSC_DIG_BUSH_DBG2_FMOD_BUS_H_shift                                   (19)
#define SYS_PLL_SSC_DIG_BUSH_DBG2_FMOD_BUS_H_mask                                    (0x00080000)
#define SYS_PLL_SSC_DIG_BUSH_DBG2_FMOD_BUS_H(data)                                   (0x00080000&((data)<<19))
#define SYS_PLL_SSC_DIG_BUSH_DBG2_FMOD_BUS_H_src(data)                               ((0x00080000&(data))>>19)
#define SYS_PLL_SSC_DIG_BUSH_DBG2_get_FMOD_BUS_H(data)                               ((0x00080000&(data))>>19)
#define SYS_PLL_SSC_DIG_BUSH_DBG2_NCODE_DEBUG_BUS_H_shift                            (11)
#define SYS_PLL_SSC_DIG_BUSH_DBG2_NCODE_DEBUG_BUS_H_mask                             (0x0007F800)
#define SYS_PLL_SSC_DIG_BUSH_DBG2_NCODE_DEBUG_BUS_H(data)                            (0x0007F800&((data)<<11))
#define SYS_PLL_SSC_DIG_BUSH_DBG2_NCODE_DEBUG_BUS_H_src(data)                        ((0x0007F800&(data))>>11)
#define SYS_PLL_SSC_DIG_BUSH_DBG2_get_NCODE_DEBUG_BUS_H(data)                        ((0x0007F800&(data))>>11)
#define SYS_PLL_SSC_DIG_BUSH_DBG2_FCODE_DEBUG_BUS_H_shift                            (0)
#define SYS_PLL_SSC_DIG_BUSH_DBG2_FCODE_DEBUG_BUS_H_mask                             (0x000007FF)
#define SYS_PLL_SSC_DIG_BUSH_DBG2_FCODE_DEBUG_BUS_H(data)                            (0x000007FF&((data)<<0))
#define SYS_PLL_SSC_DIG_BUSH_DBG2_FCODE_DEBUG_BUS_H_src(data)                        ((0x000007FF&(data))>>0)
#define SYS_PLL_SSC_DIG_BUSH_DBG2_get_FCODE_DEBUG_BUS_H(data)                        ((0x000007FF&(data))>>0)


#define SYS_PLL_SSC_DIG_DDSA0                                                        0x98000560
#define SYS_PLL_SSC_DIG_DDSA0_reg_addr                                               "0x98000560"
#define SYS_PLL_SSC_DIG_DDSA0_reg                                                    0x98000560
#define set_SYS_PLL_SSC_DIG_DDSA0_reg(data)   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_DDSA0_reg)=data)
#define get_SYS_PLL_SSC_DIG_DDSA0_reg   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_DDSA0_reg))
#define SYS_PLL_SSC_DIG_DDSA0_inst_adr                                               "0x0058"
#define SYS_PLL_SSC_DIG_DDSA0_inst                                                   0x0058
#define SYS_PLL_SSC_DIG_DDSA0_REG_CKSSC_INV_DDSA_shift                               (4)
#define SYS_PLL_SSC_DIG_DDSA0_REG_CKSSC_INV_DDSA_mask                                (0x00000010)
#define SYS_PLL_SSC_DIG_DDSA0_REG_CKSSC_INV_DDSA(data)                               (0x00000010&((data)<<4))
#define SYS_PLL_SSC_DIG_DDSA0_REG_CKSSC_INV_DDSA_src(data)                           ((0x00000010&(data))>>4)
#define SYS_PLL_SSC_DIG_DDSA0_get_REG_CKSSC_INV_DDSA(data)                           ((0x00000010&(data))>>4)
#define SYS_PLL_SSC_DIG_DDSA0_REG_GRAN_AUTO_RST_DDSA_shift                           (3)
#define SYS_PLL_SSC_DIG_DDSA0_REG_GRAN_AUTO_RST_DDSA_mask                            (0x00000008)
#define SYS_PLL_SSC_DIG_DDSA0_REG_GRAN_AUTO_RST_DDSA(data)                           (0x00000008&((data)<<3))
#define SYS_PLL_SSC_DIG_DDSA0_REG_GRAN_AUTO_RST_DDSA_src(data)                       ((0x00000008&(data))>>3)
#define SYS_PLL_SSC_DIG_DDSA0_get_REG_GRAN_AUTO_RST_DDSA(data)                       ((0x00000008&(data))>>3)
#define SYS_PLL_SSC_DIG_DDSA0_RSTB_DDSA_shift                                        (2)
#define SYS_PLL_SSC_DIG_DDSA0_RSTB_DDSA_mask                                         (0x00000004)
#define SYS_PLL_SSC_DIG_DDSA0_RSTB_DDSA(data)                                        (0x00000004&((data)<<2))
#define SYS_PLL_SSC_DIG_DDSA0_RSTB_DDSA_src(data)                                    ((0x00000004&(data))>>2)
#define SYS_PLL_SSC_DIG_DDSA0_get_RSTB_DDSA(data)                                    ((0x00000004&(data))>>2)
#define SYS_PLL_SSC_DIG_DDSA0_EN_SSC_DDSA_shift                                      (1)
#define SYS_PLL_SSC_DIG_DDSA0_EN_SSC_DDSA_mask                                       (0x00000002)
#define SYS_PLL_SSC_DIG_DDSA0_EN_SSC_DDSA(data)                                      (0x00000002&((data)<<1))
#define SYS_PLL_SSC_DIG_DDSA0_EN_SSC_DDSA_src(data)                                  ((0x00000002&(data))>>1)
#define SYS_PLL_SSC_DIG_DDSA0_get_EN_SSC_DDSA(data)                                  ((0x00000002&(data))>>1)
#define SYS_PLL_SSC_DIG_DDSA0_OC_EN_DDSA_shift                                       (0)
#define SYS_PLL_SSC_DIG_DDSA0_OC_EN_DDSA_mask                                        (0x00000001)
#define SYS_PLL_SSC_DIG_DDSA0_OC_EN_DDSA(data)                                       (0x00000001&((data)<<0))
#define SYS_PLL_SSC_DIG_DDSA0_OC_EN_DDSA_src(data)                                   ((0x00000001&(data))>>0)
#define SYS_PLL_SSC_DIG_DDSA0_get_OC_EN_DDSA(data)                                   ((0x00000001&(data))>>0)


#define SYS_PLL_SSC_DIG_DDSA1                                                        0x98000564
#define SYS_PLL_SSC_DIG_DDSA1_reg_addr                                               "0x98000564"
#define SYS_PLL_SSC_DIG_DDSA1_reg                                                    0x98000564
#define set_SYS_PLL_SSC_DIG_DDSA1_reg(data)   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_DDSA1_reg)=data)
#define get_SYS_PLL_SSC_DIG_DDSA1_reg   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_DDSA1_reg))
#define SYS_PLL_SSC_DIG_DDSA1_inst_adr                                               "0x0059"
#define SYS_PLL_SSC_DIG_DDSA1_inst                                                   0x0059
#define SYS_PLL_SSC_DIG_DDSA1_REG_PLLDDSA_ICO_PDIV2_shift                            (19)
#define SYS_PLL_SSC_DIG_DDSA1_REG_PLLDDSA_ICO_PDIV2_mask                             (0x00380000)
#define SYS_PLL_SSC_DIG_DDSA1_REG_PLLDDSA_ICO_PDIV2(data)                            (0x00380000&((data)<<19))
#define SYS_PLL_SSC_DIG_DDSA1_REG_PLLDDSA_ICO_PDIV2_src(data)                        ((0x00380000&(data))>>19)
#define SYS_PLL_SSC_DIG_DDSA1_get_REG_PLLDDSA_ICO_PDIV2(data)                        ((0x00380000&(data))>>19)
#define SYS_PLL_SSC_DIG_DDSA1_NCODE_T_DDSA_shift                                     (11)
#define SYS_PLL_SSC_DIG_DDSA1_NCODE_T_DDSA_mask                                      (0x0007F800)
#define SYS_PLL_SSC_DIG_DDSA1_NCODE_T_DDSA(data)                                     (0x0007F800&((data)<<11))
#define SYS_PLL_SSC_DIG_DDSA1_NCODE_T_DDSA_src(data)                                 ((0x0007F800&(data))>>11)
#define SYS_PLL_SSC_DIG_DDSA1_get_NCODE_T_DDSA(data)                                 ((0x0007F800&(data))>>11)
#define SYS_PLL_SSC_DIG_DDSA1_FCODE_T_DDSA_shift                                     (0)
#define SYS_PLL_SSC_DIG_DDSA1_FCODE_T_DDSA_mask                                      (0x000007FF)
#define SYS_PLL_SSC_DIG_DDSA1_FCODE_T_DDSA(data)                                     (0x000007FF&((data)<<0))
#define SYS_PLL_SSC_DIG_DDSA1_FCODE_T_DDSA_src(data)                                 ((0x000007FF&(data))>>0)
#define SYS_PLL_SSC_DIG_DDSA1_get_FCODE_T_DDSA(data)                                 ((0x000007FF&(data))>>0)


#define SYS_PLL_SSC_DIG_DDSA2                                                        0x98000568
#define SYS_PLL_SSC_DIG_DDSA2_reg_addr                                               "0x98000568"
#define SYS_PLL_SSC_DIG_DDSA2_reg                                                    0x98000568
#define set_SYS_PLL_SSC_DIG_DDSA2_reg(data)   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_DDSA2_reg)=data)
#define get_SYS_PLL_SSC_DIG_DDSA2_reg   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_DDSA2_reg))
#define SYS_PLL_SSC_DIG_DDSA2_inst_adr                                               "0x005A"
#define SYS_PLL_SSC_DIG_DDSA2_inst                                                   0x005A
#define SYS_PLL_SSC_DIG_DDSA2_REG_BYPASS_DIVN_shift                                  (27)
#define SYS_PLL_SSC_DIG_DDSA2_REG_BYPASS_DIVN_mask                                   (0x08000000)
#define SYS_PLL_SSC_DIG_DDSA2_REG_BYPASS_DIVN(data)                                  (0x08000000&((data)<<27))
#define SYS_PLL_SSC_DIG_DDSA2_REG_BYPASS_DIVN_src(data)                              ((0x08000000&(data))>>27)
#define SYS_PLL_SSC_DIG_DDSA2_get_REG_BYPASS_DIVN(data)                              ((0x08000000&(data))>>27)
#define SYS_PLL_SSC_DIG_DDSA2_REG_OC_STEP_SET_DDSA_shift                             (17)
#define SYS_PLL_SSC_DIG_DDSA2_REG_OC_STEP_SET_DDSA_mask                              (0x07FE0000)
#define SYS_PLL_SSC_DIG_DDSA2_REG_OC_STEP_SET_DDSA(data)                             (0x07FE0000&((data)<<17))
#define SYS_PLL_SSC_DIG_DDSA2_REG_OC_STEP_SET_DDSA_src(data)                         ((0x07FE0000&(data))>>17)
#define SYS_PLL_SSC_DIG_DDSA2_get_REG_OC_STEP_SET_DDSA(data)                         ((0x07FE0000&(data))>>17)
#define SYS_PLL_SSC_DIG_DDSA2_REG_SEL_OC_MODE_DDSA_shift                             (15)
#define SYS_PLL_SSC_DIG_DDSA2_REG_SEL_OC_MODE_DDSA_mask                              (0x00018000)
#define SYS_PLL_SSC_DIG_DDSA2_REG_SEL_OC_MODE_DDSA(data)                             (0x00018000&((data)<<15))
#define SYS_PLL_SSC_DIG_DDSA2_REG_SEL_OC_MODE_DDSA_src(data)                         ((0x00018000&(data))>>15)
#define SYS_PLL_SSC_DIG_DDSA2_get_REG_SEL_OC_MODE_DDSA(data)                         ((0x00018000&(data))>>15)
#define SYS_PLL_SSC_DIG_DDSA2_REG_HS_OC_STOP_DIFF_DDSA_shift                         (13)
#define SYS_PLL_SSC_DIG_DDSA2_REG_HS_OC_STOP_DIFF_DDSA_mask                          (0x00006000)
#define SYS_PLL_SSC_DIG_DDSA2_REG_HS_OC_STOP_DIFF_DDSA(data)                         (0x00006000&((data)<<13))
#define SYS_PLL_SSC_DIG_DDSA2_REG_HS_OC_STOP_DIFF_DDSA_src(data)                     ((0x00006000&(data))>>13)
#define SYS_PLL_SSC_DIG_DDSA2_get_REG_HS_OC_STOP_DIFF_DDSA(data)                     ((0x00006000&(data))>>13)
#define SYS_PLL_SSC_DIG_DDSA2_REG_OC_DONE_DELAY_DDSA_shift                           (7)
#define SYS_PLL_SSC_DIG_DDSA2_REG_OC_DONE_DELAY_DDSA_mask                            (0x00001F80)
#define SYS_PLL_SSC_DIG_DDSA2_REG_OC_DONE_DELAY_DDSA(data)                           (0x00001F80&((data)<<7))
#define SYS_PLL_SSC_DIG_DDSA2_REG_OC_DONE_DELAY_DDSA_src(data)                       ((0x00001F80&(data))>>7)
#define SYS_PLL_SSC_DIG_DDSA2_get_REG_OC_DONE_DELAY_DDSA(data)                       ((0x00001F80&(data))>>7)
#define SYS_PLL_SSC_DIG_DDSA2_REG_BYPASS_PI_DDSA_shift                               (6)
#define SYS_PLL_SSC_DIG_DDSA2_REG_BYPASS_PI_DDSA_mask                                (0x00000040)
#define SYS_PLL_SSC_DIG_DDSA2_REG_BYPASS_PI_DDSA(data)                               (0x00000040&((data)<<6))
#define SYS_PLL_SSC_DIG_DDSA2_REG_BYPASS_PI_DDSA_src(data)                           ((0x00000040&(data))>>6)
#define SYS_PLL_SSC_DIG_DDSA2_get_REG_BYPASS_PI_DDSA(data)                           ((0x00000040&(data))>>6)
#define SYS_PLL_SSC_DIG_DDSA2_REG_SDM_ORDER_DDSA_shift                               (5)
#define SYS_PLL_SSC_DIG_DDSA2_REG_SDM_ORDER_DDSA_mask                                (0x00000020)
#define SYS_PLL_SSC_DIG_DDSA2_REG_SDM_ORDER_DDSA(data)                               (0x00000020&((data)<<5))
#define SYS_PLL_SSC_DIG_DDSA2_REG_SDM_ORDER_DDSA_src(data)                           ((0x00000020&(data))>>5)
#define SYS_PLL_SSC_DIG_DDSA2_get_REG_SDM_ORDER_DDSA(data)                           ((0x00000020&(data))>>5)
#define SYS_PLL_SSC_DIG_DDSA2_REG_PI_CUR_SEL_DDSA_shift                              (2)
#define SYS_PLL_SSC_DIG_DDSA2_REG_PI_CUR_SEL_DDSA_mask                               (0x0000001C)
#define SYS_PLL_SSC_DIG_DDSA2_REG_PI_CUR_SEL_DDSA(data)                              (0x0000001C&((data)<<2))
#define SYS_PLL_SSC_DIG_DDSA2_REG_PI_CUR_SEL_DDSA_src(data)                          ((0x0000001C&(data))>>2)
#define SYS_PLL_SSC_DIG_DDSA2_get_REG_PI_CUR_SEL_DDSA(data)                          ((0x0000001C&(data))>>2)
#define SYS_PLL_SSC_DIG_DDSA2_REG_EN_PI_DEBUG_DDSA_shift                             (1)
#define SYS_PLL_SSC_DIG_DDSA2_REG_EN_PI_DEBUG_DDSA_mask                              (0x00000002)
#define SYS_PLL_SSC_DIG_DDSA2_REG_EN_PI_DEBUG_DDSA(data)                             (0x00000002&((data)<<1))
#define SYS_PLL_SSC_DIG_DDSA2_REG_EN_PI_DEBUG_DDSA_src(data)                         ((0x00000002&(data))>>1)
#define SYS_PLL_SSC_DIG_DDSA2_get_REG_EN_PI_DEBUG_DDSA(data)                         ((0x00000002&(data))>>1)


#define SYS_PLL_SSC_DIG_DDSA3                                                        0x9800056C
#define SYS_PLL_SSC_DIG_DDSA3_reg_addr                                               "0x9800056C"
#define SYS_PLL_SSC_DIG_DDSA3_reg                                                    0x9800056C
#define set_SYS_PLL_SSC_DIG_DDSA3_reg(data)   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_DDSA3_reg)=data)
#define get_SYS_PLL_SSC_DIG_DDSA3_reg   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_DDSA3_reg))
#define SYS_PLL_SSC_DIG_DDSA3_inst_adr                                               "0x005B"
#define SYS_PLL_SSC_DIG_DDSA3_inst                                                   0x005B
#define SYS_PLL_SSC_DIG_DDSA3_NCODE_SSC_DDSA_shift                                   (11)
#define SYS_PLL_SSC_DIG_DDSA3_NCODE_SSC_DDSA_mask                                    (0x0007F800)
#define SYS_PLL_SSC_DIG_DDSA3_NCODE_SSC_DDSA(data)                                   (0x0007F800&((data)<<11))
#define SYS_PLL_SSC_DIG_DDSA3_NCODE_SSC_DDSA_src(data)                               ((0x0007F800&(data))>>11)
#define SYS_PLL_SSC_DIG_DDSA3_get_NCODE_SSC_DDSA(data)                               ((0x0007F800&(data))>>11)
#define SYS_PLL_SSC_DIG_DDSA3_FCODE_SSC_DDSA_shift                                   (0)
#define SYS_PLL_SSC_DIG_DDSA3_FCODE_SSC_DDSA_mask                                    (0x000007FF)
#define SYS_PLL_SSC_DIG_DDSA3_FCODE_SSC_DDSA(data)                                   (0x000007FF&((data)<<0))
#define SYS_PLL_SSC_DIG_DDSA3_FCODE_SSC_DDSA_src(data)                               ((0x000007FF&(data))>>0)
#define SYS_PLL_SSC_DIG_DDSA3_get_FCODE_SSC_DDSA(data)                               ((0x000007FF&(data))>>0)


#define SYS_PLL_SSC_DIG_DDSA4                                                        0x98000570
#define SYS_PLL_SSC_DIG_DDSA4_reg_addr                                               "0x98000570"
#define SYS_PLL_SSC_DIG_DDSA4_reg                                                    0x98000570
#define set_SYS_PLL_SSC_DIG_DDSA4_reg(data)   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_DDSA4_reg)=data)
#define get_SYS_PLL_SSC_DIG_DDSA4_reg   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_DDSA4_reg))
#define SYS_PLL_SSC_DIG_DDSA4_inst_adr                                               "0x005C"
#define SYS_PLL_SSC_DIG_DDSA4_inst                                                   0x005C
#define SYS_PLL_SSC_DIG_DDSA4_GRAN_EST_DDSA_shift                                    (0)
#define SYS_PLL_SSC_DIG_DDSA4_GRAN_EST_DDSA_mask                                     (0x0007FFFF)
#define SYS_PLL_SSC_DIG_DDSA4_GRAN_EST_DDSA(data)                                    (0x0007FFFF&((data)<<0))
#define SYS_PLL_SSC_DIG_DDSA4_GRAN_EST_DDSA_src(data)                                ((0x0007FFFF&(data))>>0)
#define SYS_PLL_SSC_DIG_DDSA4_get_GRAN_EST_DDSA(data)                                ((0x0007FFFF&(data))>>0)


#define SYS_PLL_SSC_DIG_DDSA5                                                        0x98000574
#define SYS_PLL_SSC_DIG_DDSA5_reg_addr                                               "0x98000574"
#define SYS_PLL_SSC_DIG_DDSA5_reg                                                    0x98000574
#define set_SYS_PLL_SSC_DIG_DDSA5_reg(data)   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_DDSA5_reg)=data)
#define get_SYS_PLL_SSC_DIG_DDSA5_reg   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_DDSA5_reg))
#define SYS_PLL_SSC_DIG_DDSA5_inst_adr                                               "0x005D"
#define SYS_PLL_SSC_DIG_DDSA5_inst                                                   0x005D
#define SYS_PLL_SSC_DIG_DDSA5_FCW_SSC_DEFAULT_DDSA_shift                             (0)
#define SYS_PLL_SSC_DIG_DDSA5_FCW_SSC_DEFAULT_DDSA_mask                              (0x0007FFFF)
#define SYS_PLL_SSC_DIG_DDSA5_FCW_SSC_DEFAULT_DDSA(data)                             (0x0007FFFF&((data)<<0))
#define SYS_PLL_SSC_DIG_DDSA5_FCW_SSC_DEFAULT_DDSA_src(data)                         ((0x0007FFFF&(data))>>0)
#define SYS_PLL_SSC_DIG_DDSA5_get_FCW_SSC_DEFAULT_DDSA(data)                         ((0x0007FFFF&(data))>>0)


#define SYS_PLL_SSC_DIG_DDSA_DBG1                                                    0x98000578
#define SYS_PLL_SSC_DIG_DDSA_DBG1_reg_addr                                           "0x98000578"
#define SYS_PLL_SSC_DIG_DDSA_DBG1_reg                                                0x98000578
#define set_SYS_PLL_SSC_DIG_DDSA_DBG1_reg(data)   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_DDSA_DBG1_reg)=data)
#define get_SYS_PLL_SSC_DIG_DDSA_DBG1_reg   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_DDSA_DBG1_reg))
#define SYS_PLL_SSC_DIG_DDSA_DBG1_inst_adr                                           "0x005E"
#define SYS_PLL_SSC_DIG_DDSA_DBG1_inst                                               0x005E
#define SYS_PLL_SSC_DIG_DDSA_DBG1_LOOP_PI_ISEL_DDSA_shift                            (14)
#define SYS_PLL_SSC_DIG_DDSA_DBG1_LOOP_PI_ISEL_DDSA_mask                             (0x0001C000)
#define SYS_PLL_SSC_DIG_DDSA_DBG1_LOOP_PI_ISEL_DDSA(data)                            (0x0001C000&((data)<<14))
#define SYS_PLL_SSC_DIG_DDSA_DBG1_LOOP_PI_ISEL_DDSA_src(data)                        ((0x0001C000&(data))>>14)
#define SYS_PLL_SSC_DIG_DDSA_DBG1_get_LOOP_PI_ISEL_DDSA(data)                        ((0x0001C000&(data))>>14)
#define SYS_PLL_SSC_DIG_DDSA_DBG1_PHSEL_DDSA_shift                                   (8)
#define SYS_PLL_SSC_DIG_DDSA_DBG1_PHSEL_DDSA_mask                                    (0x00003F00)
#define SYS_PLL_SSC_DIG_DDSA_DBG1_PHSEL_DDSA(data)                                   (0x00003F00&((data)<<8))
#define SYS_PLL_SSC_DIG_DDSA_DBG1_PHSEL_DDSA_src(data)                               ((0x00003F00&(data))>>8)
#define SYS_PLL_SSC_DIG_DDSA_DBG1_get_PHSEL_DDSA(data)                               ((0x00003F00&(data))>>8)
#define SYS_PLL_SSC_DIG_DDSA_DBG1_DIVN_DDSA_shift                                    (0)
#define SYS_PLL_SSC_DIG_DDSA_DBG1_DIVN_DDSA_mask                                     (0x000000FF)
#define SYS_PLL_SSC_DIG_DDSA_DBG1_DIVN_DDSA(data)                                    (0x000000FF&((data)<<0))
#define SYS_PLL_SSC_DIG_DDSA_DBG1_DIVN_DDSA_src(data)                                ((0x000000FF&(data))>>0)
#define SYS_PLL_SSC_DIG_DDSA_DBG1_get_DIVN_DDSA(data)                                ((0x000000FF&(data))>>0)


#define SYS_PLL_SSC_DIG_DDSA_DBG2                                                    0x9800057C
#define SYS_PLL_SSC_DIG_DDSA_DBG2_reg_addr                                           "0x9800057C"
#define SYS_PLL_SSC_DIG_DDSA_DBG2_reg                                                0x9800057C
#define set_SYS_PLL_SSC_DIG_DDSA_DBG2_reg(data)   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_DDSA_DBG2_reg)=data)
#define get_SYS_PLL_SSC_DIG_DDSA_DBG2_reg   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_DDSA_DBG2_reg))
#define SYS_PLL_SSC_DIG_DDSA_DBG2_inst_adr                                           "0x005F"
#define SYS_PLL_SSC_DIG_DDSA_DBG2_inst                                               0x005F
#define SYS_PLL_SSC_DIG_DDSA_DBG2_load_FCW_DDSA_shift                                (21)
#define SYS_PLL_SSC_DIG_DDSA_DBG2_load_FCW_DDSA_mask                                 (0x00200000)
#define SYS_PLL_SSC_DIG_DDSA_DBG2_load_FCW_DDSA(data)                                (0x00200000&((data)<<21))
#define SYS_PLL_SSC_DIG_DDSA_DBG2_load_FCW_DDSA_src(data)                            ((0x00200000&(data))>>21)
#define SYS_PLL_SSC_DIG_DDSA_DBG2_get_load_FCW_DDSA(data)                            ((0x00200000&(data))>>21)
#define SYS_PLL_SSC_DIG_DDSA_DBG2_OC_DONE_DDSA_shift                                 (20)
#define SYS_PLL_SSC_DIG_DDSA_DBG2_OC_DONE_DDSA_mask                                  (0x00100000)
#define SYS_PLL_SSC_DIG_DDSA_DBG2_OC_DONE_DDSA(data)                                 (0x00100000&((data)<<20))
#define SYS_PLL_SSC_DIG_DDSA_DBG2_OC_DONE_DDSA_src(data)                             ((0x00100000&(data))>>20)
#define SYS_PLL_SSC_DIG_DDSA_DBG2_get_OC_DONE_DDSA(data)                             ((0x00100000&(data))>>20)
#define SYS_PLL_SSC_DIG_DDSA_DBG2_FMOD_DDSA_shift                                    (19)
#define SYS_PLL_SSC_DIG_DDSA_DBG2_FMOD_DDSA_mask                                     (0x00080000)
#define SYS_PLL_SSC_DIG_DDSA_DBG2_FMOD_DDSA(data)                                    (0x00080000&((data)<<19))
#define SYS_PLL_SSC_DIG_DDSA_DBG2_FMOD_DDSA_src(data)                                ((0x00080000&(data))>>19)
#define SYS_PLL_SSC_DIG_DDSA_DBG2_get_FMOD_DDSA(data)                                ((0x00080000&(data))>>19)
#define SYS_PLL_SSC_DIG_DDSA_DBG2_NCODE_DEBUG_DDSA_shift                             (11)
#define SYS_PLL_SSC_DIG_DDSA_DBG2_NCODE_DEBUG_DDSA_mask                              (0x0007F800)
#define SYS_PLL_SSC_DIG_DDSA_DBG2_NCODE_DEBUG_DDSA(data)                             (0x0007F800&((data)<<11))
#define SYS_PLL_SSC_DIG_DDSA_DBG2_NCODE_DEBUG_DDSA_src(data)                         ((0x0007F800&(data))>>11)
#define SYS_PLL_SSC_DIG_DDSA_DBG2_get_NCODE_DEBUG_DDSA(data)                         ((0x0007F800&(data))>>11)
#define SYS_PLL_SSC_DIG_DDSA_DBG2_FCODE_DEBUG_DDSA_shift                             (0)
#define SYS_PLL_SSC_DIG_DDSA_DBG2_FCODE_DEBUG_DDSA_mask                              (0x000007FF)
#define SYS_PLL_SSC_DIG_DDSA_DBG2_FCODE_DEBUG_DDSA(data)                             (0x000007FF&((data)<<0))
#define SYS_PLL_SSC_DIG_DDSA_DBG2_FCODE_DEBUG_DDSA_src(data)                         ((0x000007FF&(data))>>0)
#define SYS_PLL_SSC_DIG_DDSA_DBG2_get_FCODE_DEBUG_DDSA(data)                         ((0x000007FF&(data))>>0)


#define SYS_PLL_SSC_DIG_DDSB0                                                        0x98000580
#define SYS_PLL_SSC_DIG_DDSB0_reg_addr                                               "0x98000580"
#define SYS_PLL_SSC_DIG_DDSB0_reg                                                    0x98000580
#define set_SYS_PLL_SSC_DIG_DDSB0_reg(data)   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_DDSB0_reg)=data)
#define get_SYS_PLL_SSC_DIG_DDSB0_reg   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_DDSB0_reg))
#define SYS_PLL_SSC_DIG_DDSB0_inst_adr                                               "0x0060"
#define SYS_PLL_SSC_DIG_DDSB0_inst                                                   0x0060
#define SYS_PLL_SSC_DIG_DDSB0_REG_CKSSC_INV_DDSB_shift                               (4)
#define SYS_PLL_SSC_DIG_DDSB0_REG_CKSSC_INV_DDSB_mask                                (0x00000010)
#define SYS_PLL_SSC_DIG_DDSB0_REG_CKSSC_INV_DDSB(data)                               (0x00000010&((data)<<4))
#define SYS_PLL_SSC_DIG_DDSB0_REG_CKSSC_INV_DDSB_src(data)                           ((0x00000010&(data))>>4)
#define SYS_PLL_SSC_DIG_DDSB0_get_REG_CKSSC_INV_DDSB(data)                           ((0x00000010&(data))>>4)
#define SYS_PLL_SSC_DIG_DDSB0_REG_GRAN_AUTO_RST_DDSB_shift                           (3)
#define SYS_PLL_SSC_DIG_DDSB0_REG_GRAN_AUTO_RST_DDSB_mask                            (0x00000008)
#define SYS_PLL_SSC_DIG_DDSB0_REG_GRAN_AUTO_RST_DDSB(data)                           (0x00000008&((data)<<3))
#define SYS_PLL_SSC_DIG_DDSB0_REG_GRAN_AUTO_RST_DDSB_src(data)                       ((0x00000008&(data))>>3)
#define SYS_PLL_SSC_DIG_DDSB0_get_REG_GRAN_AUTO_RST_DDSB(data)                       ((0x00000008&(data))>>3)
#define SYS_PLL_SSC_DIG_DDSB0_RSTB_DDSB_shift                                        (2)
#define SYS_PLL_SSC_DIG_DDSB0_RSTB_DDSB_mask                                         (0x00000004)
#define SYS_PLL_SSC_DIG_DDSB0_RSTB_DDSB(data)                                        (0x00000004&((data)<<2))
#define SYS_PLL_SSC_DIG_DDSB0_RSTB_DDSB_src(data)                                    ((0x00000004&(data))>>2)
#define SYS_PLL_SSC_DIG_DDSB0_get_RSTB_DDSB(data)                                    ((0x00000004&(data))>>2)
#define SYS_PLL_SSC_DIG_DDSB0_EN_SSC_DDSB_shift                                      (1)
#define SYS_PLL_SSC_DIG_DDSB0_EN_SSC_DDSB_mask                                       (0x00000002)
#define SYS_PLL_SSC_DIG_DDSB0_EN_SSC_DDSB(data)                                      (0x00000002&((data)<<1))
#define SYS_PLL_SSC_DIG_DDSB0_EN_SSC_DDSB_src(data)                                  ((0x00000002&(data))>>1)
#define SYS_PLL_SSC_DIG_DDSB0_get_EN_SSC_DDSB(data)                                  ((0x00000002&(data))>>1)
#define SYS_PLL_SSC_DIG_DDSB0_OC_EN_DDSB_shift                                       (0)
#define SYS_PLL_SSC_DIG_DDSB0_OC_EN_DDSB_mask                                        (0x00000001)
#define SYS_PLL_SSC_DIG_DDSB0_OC_EN_DDSB(data)                                       (0x00000001&((data)<<0))
#define SYS_PLL_SSC_DIG_DDSB0_OC_EN_DDSB_src(data)                                   ((0x00000001&(data))>>0)
#define SYS_PLL_SSC_DIG_DDSB0_get_OC_EN_DDSB(data)                                   ((0x00000001&(data))>>0)


#define SYS_PLL_SSC_DIG_DDSB1                                                        0x98000584
#define SYS_PLL_SSC_DIG_DDSB1_reg_addr                                               "0x98000584"
#define SYS_PLL_SSC_DIG_DDSB1_reg                                                    0x98000584
#define set_SYS_PLL_SSC_DIG_DDSB1_reg(data)   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_DDSB1_reg)=data)
#define get_SYS_PLL_SSC_DIG_DDSB1_reg   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_DDSB1_reg))
#define SYS_PLL_SSC_DIG_DDSB1_inst_adr                                               "0x0061"
#define SYS_PLL_SSC_DIG_DDSB1_inst                                                   0x0061
#define SYS_PLL_SSC_DIG_DDSB1_REG_PLLDDSB_ICO_PDIV2_shift                            (19)
#define SYS_PLL_SSC_DIG_DDSB1_REG_PLLDDSB_ICO_PDIV2_mask                             (0x00380000)
#define SYS_PLL_SSC_DIG_DDSB1_REG_PLLDDSB_ICO_PDIV2(data)                            (0x00380000&((data)<<19))
#define SYS_PLL_SSC_DIG_DDSB1_REG_PLLDDSB_ICO_PDIV2_src(data)                        ((0x00380000&(data))>>19)
#define SYS_PLL_SSC_DIG_DDSB1_get_REG_PLLDDSB_ICO_PDIV2(data)                        ((0x00380000&(data))>>19)
#define SYS_PLL_SSC_DIG_DDSB1_NCODE_T_DDSB_shift                                     (11)
#define SYS_PLL_SSC_DIG_DDSB1_NCODE_T_DDSB_mask                                      (0x0007F800)
#define SYS_PLL_SSC_DIG_DDSB1_NCODE_T_DDSB(data)                                     (0x0007F800&((data)<<11))
#define SYS_PLL_SSC_DIG_DDSB1_NCODE_T_DDSB_src(data)                                 ((0x0007F800&(data))>>11)
#define SYS_PLL_SSC_DIG_DDSB1_get_NCODE_T_DDSB(data)                                 ((0x0007F800&(data))>>11)
#define SYS_PLL_SSC_DIG_DDSB1_FCODE_T_DDSB_shift                                     (0)
#define SYS_PLL_SSC_DIG_DDSB1_FCODE_T_DDSB_mask                                      (0x000007FF)
#define SYS_PLL_SSC_DIG_DDSB1_FCODE_T_DDSB(data)                                     (0x000007FF&((data)<<0))
#define SYS_PLL_SSC_DIG_DDSB1_FCODE_T_DDSB_src(data)                                 ((0x000007FF&(data))>>0)
#define SYS_PLL_SSC_DIG_DDSB1_get_FCODE_T_DDSB(data)                                 ((0x000007FF&(data))>>0)


#define SYS_PLL_SSC_DIG_DDSB2                                                        0x98000588
#define SYS_PLL_SSC_DIG_DDSB2_reg_addr                                               "0x98000588"
#define SYS_PLL_SSC_DIG_DDSB2_reg                                                    0x98000588
#define set_SYS_PLL_SSC_DIG_DDSB2_reg(data)   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_DDSB2_reg)=data)
#define get_SYS_PLL_SSC_DIG_DDSB2_reg   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_DDSB2_reg))
#define SYS_PLL_SSC_DIG_DDSB2_inst_adr                                               "0x0062"
#define SYS_PLL_SSC_DIG_DDSB2_inst                                                   0x0062
#define SYS_PLL_SSC_DIG_DDSB2_REG_BYPASS_DIVN_shift                                  (27)
#define SYS_PLL_SSC_DIG_DDSB2_REG_BYPASS_DIVN_mask                                   (0x08000000)
#define SYS_PLL_SSC_DIG_DDSB2_REG_BYPASS_DIVN(data)                                  (0x08000000&((data)<<27))
#define SYS_PLL_SSC_DIG_DDSB2_REG_BYPASS_DIVN_src(data)                              ((0x08000000&(data))>>27)
#define SYS_PLL_SSC_DIG_DDSB2_get_REG_BYPASS_DIVN(data)                              ((0x08000000&(data))>>27)
#define SYS_PLL_SSC_DIG_DDSB2_REG_OC_STEP_SET_DDSB_shift                             (17)
#define SYS_PLL_SSC_DIG_DDSB2_REG_OC_STEP_SET_DDSB_mask                              (0x07FE0000)
#define SYS_PLL_SSC_DIG_DDSB2_REG_OC_STEP_SET_DDSB(data)                             (0x07FE0000&((data)<<17))
#define SYS_PLL_SSC_DIG_DDSB2_REG_OC_STEP_SET_DDSB_src(data)                         ((0x07FE0000&(data))>>17)
#define SYS_PLL_SSC_DIG_DDSB2_get_REG_OC_STEP_SET_DDSB(data)                         ((0x07FE0000&(data))>>17)
#define SYS_PLL_SSC_DIG_DDSB2_REG_SEL_OC_MODE_DDSB_shift                             (15)
#define SYS_PLL_SSC_DIG_DDSB2_REG_SEL_OC_MODE_DDSB_mask                              (0x00018000)
#define SYS_PLL_SSC_DIG_DDSB2_REG_SEL_OC_MODE_DDSB(data)                             (0x00018000&((data)<<15))
#define SYS_PLL_SSC_DIG_DDSB2_REG_SEL_OC_MODE_DDSB_src(data)                         ((0x00018000&(data))>>15)
#define SYS_PLL_SSC_DIG_DDSB2_get_REG_SEL_OC_MODE_DDSB(data)                         ((0x00018000&(data))>>15)
#define SYS_PLL_SSC_DIG_DDSB2_REG_HS_OC_STOP_DIFF_DDSB_shift                         (13)
#define SYS_PLL_SSC_DIG_DDSB2_REG_HS_OC_STOP_DIFF_DDSB_mask                          (0x00006000)
#define SYS_PLL_SSC_DIG_DDSB2_REG_HS_OC_STOP_DIFF_DDSB(data)                         (0x00006000&((data)<<13))
#define SYS_PLL_SSC_DIG_DDSB2_REG_HS_OC_STOP_DIFF_DDSB_src(data)                     ((0x00006000&(data))>>13)
#define SYS_PLL_SSC_DIG_DDSB2_get_REG_HS_OC_STOP_DIFF_DDSB(data)                     ((0x00006000&(data))>>13)
#define SYS_PLL_SSC_DIG_DDSB2_REG_OC_DONE_DELAY_DDSB_shift                           (7)
#define SYS_PLL_SSC_DIG_DDSB2_REG_OC_DONE_DELAY_DDSB_mask                            (0x00001F80)
#define SYS_PLL_SSC_DIG_DDSB2_REG_OC_DONE_DELAY_DDSB(data)                           (0x00001F80&((data)<<7))
#define SYS_PLL_SSC_DIG_DDSB2_REG_OC_DONE_DELAY_DDSB_src(data)                       ((0x00001F80&(data))>>7)
#define SYS_PLL_SSC_DIG_DDSB2_get_REG_OC_DONE_DELAY_DDSB(data)                       ((0x00001F80&(data))>>7)
#define SYS_PLL_SSC_DIG_DDSB2_REG_BYPASS_PI_DDSB_shift                               (6)
#define SYS_PLL_SSC_DIG_DDSB2_REG_BYPASS_PI_DDSB_mask                                (0x00000040)
#define SYS_PLL_SSC_DIG_DDSB2_REG_BYPASS_PI_DDSB(data)                               (0x00000040&((data)<<6))
#define SYS_PLL_SSC_DIG_DDSB2_REG_BYPASS_PI_DDSB_src(data)                           ((0x00000040&(data))>>6)
#define SYS_PLL_SSC_DIG_DDSB2_get_REG_BYPASS_PI_DDSB(data)                           ((0x00000040&(data))>>6)
#define SYS_PLL_SSC_DIG_DDSB2_REG_SDM_ORDER_DDSB_shift                               (5)
#define SYS_PLL_SSC_DIG_DDSB2_REG_SDM_ORDER_DDSB_mask                                (0x00000020)
#define SYS_PLL_SSC_DIG_DDSB2_REG_SDM_ORDER_DDSB(data)                               (0x00000020&((data)<<5))
#define SYS_PLL_SSC_DIG_DDSB2_REG_SDM_ORDER_DDSB_src(data)                           ((0x00000020&(data))>>5)
#define SYS_PLL_SSC_DIG_DDSB2_get_REG_SDM_ORDER_DDSB(data)                           ((0x00000020&(data))>>5)
#define SYS_PLL_SSC_DIG_DDSB2_REG_PI_CUR_SEL_DDSB_shift                              (2)
#define SYS_PLL_SSC_DIG_DDSB2_REG_PI_CUR_SEL_DDSB_mask                               (0x0000001C)
#define SYS_PLL_SSC_DIG_DDSB2_REG_PI_CUR_SEL_DDSB(data)                              (0x0000001C&((data)<<2))
#define SYS_PLL_SSC_DIG_DDSB2_REG_PI_CUR_SEL_DDSB_src(data)                          ((0x0000001C&(data))>>2)
#define SYS_PLL_SSC_DIG_DDSB2_get_REG_PI_CUR_SEL_DDSB(data)                          ((0x0000001C&(data))>>2)
#define SYS_PLL_SSC_DIG_DDSB2_REG_EN_PI_DEBUG_DDSB_shift                             (1)
#define SYS_PLL_SSC_DIG_DDSB2_REG_EN_PI_DEBUG_DDSB_mask                              (0x00000002)
#define SYS_PLL_SSC_DIG_DDSB2_REG_EN_PI_DEBUG_DDSB(data)                             (0x00000002&((data)<<1))
#define SYS_PLL_SSC_DIG_DDSB2_REG_EN_PI_DEBUG_DDSB_src(data)                         ((0x00000002&(data))>>1)
#define SYS_PLL_SSC_DIG_DDSB2_get_REG_EN_PI_DEBUG_DDSB(data)                         ((0x00000002&(data))>>1)


#define SYS_PLL_SSC_DIG_DDSB3                                                        0x9800058C
#define SYS_PLL_SSC_DIG_DDSB3_reg_addr                                               "0x9800058C"
#define SYS_PLL_SSC_DIG_DDSB3_reg                                                    0x9800058C
#define set_SYS_PLL_SSC_DIG_DDSB3_reg(data)   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_DDSB3_reg)=data)
#define get_SYS_PLL_SSC_DIG_DDSB3_reg   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_DDSB3_reg))
#define SYS_PLL_SSC_DIG_DDSB3_inst_adr                                               "0x0063"
#define SYS_PLL_SSC_DIG_DDSB3_inst                                                   0x0063
#define SYS_PLL_SSC_DIG_DDSB3_NCODE_SSC_DDSB_shift                                   (11)
#define SYS_PLL_SSC_DIG_DDSB3_NCODE_SSC_DDSB_mask                                    (0x0007F800)
#define SYS_PLL_SSC_DIG_DDSB3_NCODE_SSC_DDSB(data)                                   (0x0007F800&((data)<<11))
#define SYS_PLL_SSC_DIG_DDSB3_NCODE_SSC_DDSB_src(data)                               ((0x0007F800&(data))>>11)
#define SYS_PLL_SSC_DIG_DDSB3_get_NCODE_SSC_DDSB(data)                               ((0x0007F800&(data))>>11)
#define SYS_PLL_SSC_DIG_DDSB3_FCODE_SSC_DDSB_shift                                   (0)
#define SYS_PLL_SSC_DIG_DDSB3_FCODE_SSC_DDSB_mask                                    (0x000007FF)
#define SYS_PLL_SSC_DIG_DDSB3_FCODE_SSC_DDSB(data)                                   (0x000007FF&((data)<<0))
#define SYS_PLL_SSC_DIG_DDSB3_FCODE_SSC_DDSB_src(data)                               ((0x000007FF&(data))>>0)
#define SYS_PLL_SSC_DIG_DDSB3_get_FCODE_SSC_DDSB(data)                               ((0x000007FF&(data))>>0)


#define SYS_PLL_SSC_DIG_DDSB4                                                        0x98000590
#define SYS_PLL_SSC_DIG_DDSB4_reg_addr                                               "0x98000590"
#define SYS_PLL_SSC_DIG_DDSB4_reg                                                    0x98000590
#define set_SYS_PLL_SSC_DIG_DDSB4_reg(data)   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_DDSB4_reg)=data)
#define get_SYS_PLL_SSC_DIG_DDSB4_reg   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_DDSB4_reg))
#define SYS_PLL_SSC_DIG_DDSB4_inst_adr                                               "0x0064"
#define SYS_PLL_SSC_DIG_DDSB4_inst                                                   0x0064
#define SYS_PLL_SSC_DIG_DDSB4_GRAN_EST_DDSB_shift                                    (0)
#define SYS_PLL_SSC_DIG_DDSB4_GRAN_EST_DDSB_mask                                     (0x0007FFFF)
#define SYS_PLL_SSC_DIG_DDSB4_GRAN_EST_DDSB(data)                                    (0x0007FFFF&((data)<<0))
#define SYS_PLL_SSC_DIG_DDSB4_GRAN_EST_DDSB_src(data)                                ((0x0007FFFF&(data))>>0)
#define SYS_PLL_SSC_DIG_DDSB4_get_GRAN_EST_DDSB(data)                                ((0x0007FFFF&(data))>>0)


#define SYS_PLL_SSC_DIG_DDSB5                                                        0x98000594
#define SYS_PLL_SSC_DIG_DDSB5_reg_addr                                               "0x98000594"
#define SYS_PLL_SSC_DIG_DDSB5_reg                                                    0x98000594
#define set_SYS_PLL_SSC_DIG_DDSB5_reg(data)   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_DDSB5_reg)=data)
#define get_SYS_PLL_SSC_DIG_DDSB5_reg   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_DDSB5_reg))
#define SYS_PLL_SSC_DIG_DDSB5_inst_adr                                               "0x0065"
#define SYS_PLL_SSC_DIG_DDSB5_inst                                                   0x0065
#define SYS_PLL_SSC_DIG_DDSB5_FCW_SSC_DEFAULT_DDSB_shift                             (0)
#define SYS_PLL_SSC_DIG_DDSB5_FCW_SSC_DEFAULT_DDSB_mask                              (0x0007FFFF)
#define SYS_PLL_SSC_DIG_DDSB5_FCW_SSC_DEFAULT_DDSB(data)                             (0x0007FFFF&((data)<<0))
#define SYS_PLL_SSC_DIG_DDSB5_FCW_SSC_DEFAULT_DDSB_src(data)                         ((0x0007FFFF&(data))>>0)
#define SYS_PLL_SSC_DIG_DDSB5_get_FCW_SSC_DEFAULT_DDSB(data)                         ((0x0007FFFF&(data))>>0)


#define SYS_PLL_SSC_DIG_DDSB_DBG1                                                    0x98000598
#define SYS_PLL_SSC_DIG_DDSB_DBG1_reg_addr                                           "0x98000598"
#define SYS_PLL_SSC_DIG_DDSB_DBG1_reg                                                0x98000598
#define set_SYS_PLL_SSC_DIG_DDSB_DBG1_reg(data)   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_DDSB_DBG1_reg)=data)
#define get_SYS_PLL_SSC_DIG_DDSB_DBG1_reg   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_DDSB_DBG1_reg))
#define SYS_PLL_SSC_DIG_DDSB_DBG1_inst_adr                                           "0x0066"
#define SYS_PLL_SSC_DIG_DDSB_DBG1_inst                                               0x0066
#define SYS_PLL_SSC_DIG_DDSB_DBG1_LOOP_PI_ISEL_DDSB_shift                            (14)
#define SYS_PLL_SSC_DIG_DDSB_DBG1_LOOP_PI_ISEL_DDSB_mask                             (0x0001C000)
#define SYS_PLL_SSC_DIG_DDSB_DBG1_LOOP_PI_ISEL_DDSB(data)                            (0x0001C000&((data)<<14))
#define SYS_PLL_SSC_DIG_DDSB_DBG1_LOOP_PI_ISEL_DDSB_src(data)                        ((0x0001C000&(data))>>14)
#define SYS_PLL_SSC_DIG_DDSB_DBG1_get_LOOP_PI_ISEL_DDSB(data)                        ((0x0001C000&(data))>>14)
#define SYS_PLL_SSC_DIG_DDSB_DBG1_PHSEL_DDSB_shift                                   (8)
#define SYS_PLL_SSC_DIG_DDSB_DBG1_PHSEL_DDSB_mask                                    (0x00003F00)
#define SYS_PLL_SSC_DIG_DDSB_DBG1_PHSEL_DDSB(data)                                   (0x00003F00&((data)<<8))
#define SYS_PLL_SSC_DIG_DDSB_DBG1_PHSEL_DDSB_src(data)                               ((0x00003F00&(data))>>8)
#define SYS_PLL_SSC_DIG_DDSB_DBG1_get_PHSEL_DDSB(data)                               ((0x00003F00&(data))>>8)
#define SYS_PLL_SSC_DIG_DDSB_DBG1_DIVN_DDSB_shift                                    (0)
#define SYS_PLL_SSC_DIG_DDSB_DBG1_DIVN_DDSB_mask                                     (0x000000FF)
#define SYS_PLL_SSC_DIG_DDSB_DBG1_DIVN_DDSB(data)                                    (0x000000FF&((data)<<0))
#define SYS_PLL_SSC_DIG_DDSB_DBG1_DIVN_DDSB_src(data)                                ((0x000000FF&(data))>>0)
#define SYS_PLL_SSC_DIG_DDSB_DBG1_get_DIVN_DDSB(data)                                ((0x000000FF&(data))>>0)


#define SYS_PLL_SSC_DIG_DDSB_DBG2                                                    0x9800059C
#define SYS_PLL_SSC_DIG_DDSB_DBG2_reg_addr                                           "0x9800059C"
#define SYS_PLL_SSC_DIG_DDSB_DBG2_reg                                                0x9800059C
#define set_SYS_PLL_SSC_DIG_DDSB_DBG2_reg(data)   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_DDSB_DBG2_reg)=data)
#define get_SYS_PLL_SSC_DIG_DDSB_DBG2_reg   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_DDSB_DBG2_reg))
#define SYS_PLL_SSC_DIG_DDSB_DBG2_inst_adr                                           "0x0067"
#define SYS_PLL_SSC_DIG_DDSB_DBG2_inst                                               0x0067
#define SYS_PLL_SSC_DIG_DDSB_DBG2_load_FCW_DDSB_shift                                (21)
#define SYS_PLL_SSC_DIG_DDSB_DBG2_load_FCW_DDSB_mask                                 (0x00200000)
#define SYS_PLL_SSC_DIG_DDSB_DBG2_load_FCW_DDSB(data)                                (0x00200000&((data)<<21))
#define SYS_PLL_SSC_DIG_DDSB_DBG2_load_FCW_DDSB_src(data)                            ((0x00200000&(data))>>21)
#define SYS_PLL_SSC_DIG_DDSB_DBG2_get_load_FCW_DDSB(data)                            ((0x00200000&(data))>>21)
#define SYS_PLL_SSC_DIG_DDSB_DBG2_OC_DONE_DDSB_shift                                 (20)
#define SYS_PLL_SSC_DIG_DDSB_DBG2_OC_DONE_DDSB_mask                                  (0x00100000)
#define SYS_PLL_SSC_DIG_DDSB_DBG2_OC_DONE_DDSB(data)                                 (0x00100000&((data)<<20))
#define SYS_PLL_SSC_DIG_DDSB_DBG2_OC_DONE_DDSB_src(data)                             ((0x00100000&(data))>>20)
#define SYS_PLL_SSC_DIG_DDSB_DBG2_get_OC_DONE_DDSB(data)                             ((0x00100000&(data))>>20)
#define SYS_PLL_SSC_DIG_DDSB_DBG2_FMOD_DDSB_shift                                    (19)
#define SYS_PLL_SSC_DIG_DDSB_DBG2_FMOD_DDSB_mask                                     (0x00080000)
#define SYS_PLL_SSC_DIG_DDSB_DBG2_FMOD_DDSB(data)                                    (0x00080000&((data)<<19))
#define SYS_PLL_SSC_DIG_DDSB_DBG2_FMOD_DDSB_src(data)                                ((0x00080000&(data))>>19)
#define SYS_PLL_SSC_DIG_DDSB_DBG2_get_FMOD_DDSB(data)                                ((0x00080000&(data))>>19)
#define SYS_PLL_SSC_DIG_DDSB_DBG2_NCODE_DEBUG_DDSB_shift                             (11)
#define SYS_PLL_SSC_DIG_DDSB_DBG2_NCODE_DEBUG_DDSB_mask                              (0x0007F800)
#define SYS_PLL_SSC_DIG_DDSB_DBG2_NCODE_DEBUG_DDSB(data)                             (0x0007F800&((data)<<11))
#define SYS_PLL_SSC_DIG_DDSB_DBG2_NCODE_DEBUG_DDSB_src(data)                         ((0x0007F800&(data))>>11)
#define SYS_PLL_SSC_DIG_DDSB_DBG2_get_NCODE_DEBUG_DDSB(data)                         ((0x0007F800&(data))>>11)
#define SYS_PLL_SSC_DIG_DDSB_DBG2_FCODE_DEBUG_DDSB_shift                             (0)
#define SYS_PLL_SSC_DIG_DDSB_DBG2_FCODE_DEBUG_DDSB_mask                              (0x000007FF)
#define SYS_PLL_SSC_DIG_DDSB_DBG2_FCODE_DEBUG_DDSB(data)                             (0x000007FF&((data)<<0))
#define SYS_PLL_SSC_DIG_DDSB_DBG2_FCODE_DEBUG_DDSB_src(data)                         ((0x000007FF&(data))>>0)
#define SYS_PLL_SSC_DIG_DDSB_DBG2_get_FCODE_DEBUG_DDSB(data)                         ((0x000007FF&(data))>>0)


#define SYS_PLL_SSC_DIG_GPU0                                                         0x980005A0
#define SYS_PLL_SSC_DIG_GPU0_reg_addr                                                "0x980005A0"
#define SYS_PLL_SSC_DIG_GPU0_reg                                                     0x980005A0
#define set_SYS_PLL_SSC_DIG_GPU0_reg(data)   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_GPU0_reg)=data)
#define get_SYS_PLL_SSC_DIG_GPU0_reg   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_GPU0_reg))
#define SYS_PLL_SSC_DIG_GPU0_inst_adr                                                "0x0068"
#define SYS_PLL_SSC_DIG_GPU0_inst                                                    0x0068
#define SYS_PLL_SSC_DIG_GPU0_REG_CKSSC_INV_GPU_shift                                 (4)
#define SYS_PLL_SSC_DIG_GPU0_REG_CKSSC_INV_GPU_mask                                  (0x00000010)
#define SYS_PLL_SSC_DIG_GPU0_REG_CKSSC_INV_GPU(data)                                 (0x00000010&((data)<<4))
#define SYS_PLL_SSC_DIG_GPU0_REG_CKSSC_INV_GPU_src(data)                             ((0x00000010&(data))>>4)
#define SYS_PLL_SSC_DIG_GPU0_get_REG_CKSSC_INV_GPU(data)                             ((0x00000010&(data))>>4)
#define SYS_PLL_SSC_DIG_GPU0_REG_GRAN_AUTO_RST_GPU_shift                             (3)
#define SYS_PLL_SSC_DIG_GPU0_REG_GRAN_AUTO_RST_GPU_mask                              (0x00000008)
#define SYS_PLL_SSC_DIG_GPU0_REG_GRAN_AUTO_RST_GPU(data)                             (0x00000008&((data)<<3))
#define SYS_PLL_SSC_DIG_GPU0_REG_GRAN_AUTO_RST_GPU_src(data)                         ((0x00000008&(data))>>3)
#define SYS_PLL_SSC_DIG_GPU0_get_REG_GRAN_AUTO_RST_GPU(data)                         ((0x00000008&(data))>>3)
#define SYS_PLL_SSC_DIG_GPU0_RSTB_GPU_shift                                          (2)
#define SYS_PLL_SSC_DIG_GPU0_RSTB_GPU_mask                                           (0x00000004)
#define SYS_PLL_SSC_DIG_GPU0_RSTB_GPU(data)                                          (0x00000004&((data)<<2))
#define SYS_PLL_SSC_DIG_GPU0_RSTB_GPU_src(data)                                      ((0x00000004&(data))>>2)
#define SYS_PLL_SSC_DIG_GPU0_get_RSTB_GPU(data)                                      ((0x00000004&(data))>>2)
#define SYS_PLL_SSC_DIG_GPU0_EN_SSC_GPU_shift                                        (1)
#define SYS_PLL_SSC_DIG_GPU0_EN_SSC_GPU_mask                                         (0x00000002)
#define SYS_PLL_SSC_DIG_GPU0_EN_SSC_GPU(data)                                        (0x00000002&((data)<<1))
#define SYS_PLL_SSC_DIG_GPU0_EN_SSC_GPU_src(data)                                    ((0x00000002&(data))>>1)
#define SYS_PLL_SSC_DIG_GPU0_get_EN_SSC_GPU(data)                                    ((0x00000002&(data))>>1)
#define SYS_PLL_SSC_DIG_GPU0_OC_EN_GPU_shift                                         (0)
#define SYS_PLL_SSC_DIG_GPU0_OC_EN_GPU_mask                                          (0x00000001)
#define SYS_PLL_SSC_DIG_GPU0_OC_EN_GPU(data)                                         (0x00000001&((data)<<0))
#define SYS_PLL_SSC_DIG_GPU0_OC_EN_GPU_src(data)                                     ((0x00000001&(data))>>0)
#define SYS_PLL_SSC_DIG_GPU0_get_OC_EN_GPU(data)                                     ((0x00000001&(data))>>0)


#define SYS_PLL_SSC_DIG_GPU1                                                         0x980005A4
#define SYS_PLL_SSC_DIG_GPU1_reg_addr                                                "0x980005A4"
#define SYS_PLL_SSC_DIG_GPU1_reg                                                     0x980005A4
#define set_SYS_PLL_SSC_DIG_GPU1_reg(data)   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_GPU1_reg)=data)
#define get_SYS_PLL_SSC_DIG_GPU1_reg   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_GPU1_reg))
#define SYS_PLL_SSC_DIG_GPU1_inst_adr                                                "0x0069"
#define SYS_PLL_SSC_DIG_GPU1_inst                                                    0x0069
#define SYS_PLL_SSC_DIG_GPU1_NCODE_T_GPU_shift                                       (11)
#define SYS_PLL_SSC_DIG_GPU1_NCODE_T_GPU_mask                                        (0x0007F800)
#define SYS_PLL_SSC_DIG_GPU1_NCODE_T_GPU(data)                                       (0x0007F800&((data)<<11))
#define SYS_PLL_SSC_DIG_GPU1_NCODE_T_GPU_src(data)                                   ((0x0007F800&(data))>>11)
#define SYS_PLL_SSC_DIG_GPU1_get_NCODE_T_GPU(data)                                   ((0x0007F800&(data))>>11)
#define SYS_PLL_SSC_DIG_GPU1_FCODE_T_GPU_shift                                       (0)
#define SYS_PLL_SSC_DIG_GPU1_FCODE_T_GPU_mask                                        (0x000007FF)
#define SYS_PLL_SSC_DIG_GPU1_FCODE_T_GPU(data)                                       (0x000007FF&((data)<<0))
#define SYS_PLL_SSC_DIG_GPU1_FCODE_T_GPU_src(data)                                   ((0x000007FF&(data))>>0)
#define SYS_PLL_SSC_DIG_GPU1_get_FCODE_T_GPU(data)                                   ((0x000007FF&(data))>>0)


#define SYS_PLL_SSC_DIG_GPU2                                                         0x980005A8
#define SYS_PLL_SSC_DIG_GPU2_reg_addr                                                "0x980005A8"
#define SYS_PLL_SSC_DIG_GPU2_reg                                                     0x980005A8
#define set_SYS_PLL_SSC_DIG_GPU2_reg(data)   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_GPU2_reg)=data)
#define get_SYS_PLL_SSC_DIG_GPU2_reg   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_GPU2_reg))
#define SYS_PLL_SSC_DIG_GPU2_inst_adr                                                "0x006A"
#define SYS_PLL_SSC_DIG_GPU2_inst                                                    0x006A
#define SYS_PLL_SSC_DIG_GPU2_REG_BYPASS_DIVN_shift                                   (27)
#define SYS_PLL_SSC_DIG_GPU2_REG_BYPASS_DIVN_mask                                    (0x08000000)
#define SYS_PLL_SSC_DIG_GPU2_REG_BYPASS_DIVN(data)                                   (0x08000000&((data)<<27))
#define SYS_PLL_SSC_DIG_GPU2_REG_BYPASS_DIVN_src(data)                               ((0x08000000&(data))>>27)
#define SYS_PLL_SSC_DIG_GPU2_get_REG_BYPASS_DIVN(data)                               ((0x08000000&(data))>>27)
#define SYS_PLL_SSC_DIG_GPU2_REG_OC_STEP_SET_GPU_shift                               (17)
#define SYS_PLL_SSC_DIG_GPU2_REG_OC_STEP_SET_GPU_mask                                (0x07FE0000)
#define SYS_PLL_SSC_DIG_GPU2_REG_OC_STEP_SET_GPU(data)                               (0x07FE0000&((data)<<17))
#define SYS_PLL_SSC_DIG_GPU2_REG_OC_STEP_SET_GPU_src(data)                           ((0x07FE0000&(data))>>17)
#define SYS_PLL_SSC_DIG_GPU2_get_REG_OC_STEP_SET_GPU(data)                           ((0x07FE0000&(data))>>17)
#define SYS_PLL_SSC_DIG_GPU2_REG_SEL_OC_MODE_GPU_shift                               (15)
#define SYS_PLL_SSC_DIG_GPU2_REG_SEL_OC_MODE_GPU_mask                                (0x00018000)
#define SYS_PLL_SSC_DIG_GPU2_REG_SEL_OC_MODE_GPU(data)                               (0x00018000&((data)<<15))
#define SYS_PLL_SSC_DIG_GPU2_REG_SEL_OC_MODE_GPU_src(data)                           ((0x00018000&(data))>>15)
#define SYS_PLL_SSC_DIG_GPU2_get_REG_SEL_OC_MODE_GPU(data)                           ((0x00018000&(data))>>15)
#define SYS_PLL_SSC_DIG_GPU2_REG_HS_OC_STOP_DIFF_GPU_shift                           (13)
#define SYS_PLL_SSC_DIG_GPU2_REG_HS_OC_STOP_DIFF_GPU_mask                            (0x00006000)
#define SYS_PLL_SSC_DIG_GPU2_REG_HS_OC_STOP_DIFF_GPU(data)                           (0x00006000&((data)<<13))
#define SYS_PLL_SSC_DIG_GPU2_REG_HS_OC_STOP_DIFF_GPU_src(data)                       ((0x00006000&(data))>>13)
#define SYS_PLL_SSC_DIG_GPU2_get_REG_HS_OC_STOP_DIFF_GPU(data)                       ((0x00006000&(data))>>13)
#define SYS_PLL_SSC_DIG_GPU2_REG_OC_DONE_DELAY_GPU_shift                             (7)
#define SYS_PLL_SSC_DIG_GPU2_REG_OC_DONE_DELAY_GPU_mask                              (0x00001F80)
#define SYS_PLL_SSC_DIG_GPU2_REG_OC_DONE_DELAY_GPU(data)                             (0x00001F80&((data)<<7))
#define SYS_PLL_SSC_DIG_GPU2_REG_OC_DONE_DELAY_GPU_src(data)                         ((0x00001F80&(data))>>7)
#define SYS_PLL_SSC_DIG_GPU2_get_REG_OC_DONE_DELAY_GPU(data)                         ((0x00001F80&(data))>>7)
#define SYS_PLL_SSC_DIG_GPU2_REG_BYPASS_PI_GPU_shift                                 (6)
#define SYS_PLL_SSC_DIG_GPU2_REG_BYPASS_PI_GPU_mask                                  (0x00000040)
#define SYS_PLL_SSC_DIG_GPU2_REG_BYPASS_PI_GPU(data)                                 (0x00000040&((data)<<6))
#define SYS_PLL_SSC_DIG_GPU2_REG_BYPASS_PI_GPU_src(data)                             ((0x00000040&(data))>>6)
#define SYS_PLL_SSC_DIG_GPU2_get_REG_BYPASS_PI_GPU(data)                             ((0x00000040&(data))>>6)
#define SYS_PLL_SSC_DIG_GPU2_REG_SDM_ORDER_GPU_shift                                 (5)
#define SYS_PLL_SSC_DIG_GPU2_REG_SDM_ORDER_GPU_mask                                  (0x00000020)
#define SYS_PLL_SSC_DIG_GPU2_REG_SDM_ORDER_GPU(data)                                 (0x00000020&((data)<<5))
#define SYS_PLL_SSC_DIG_GPU2_REG_SDM_ORDER_GPU_src(data)                             ((0x00000020&(data))>>5)
#define SYS_PLL_SSC_DIG_GPU2_get_REG_SDM_ORDER_GPU(data)                             ((0x00000020&(data))>>5)
#define SYS_PLL_SSC_DIG_GPU2_REG_PI_CUR_SEL_GPU_shift                                (2)
#define SYS_PLL_SSC_DIG_GPU2_REG_PI_CUR_SEL_GPU_mask                                 (0x0000001C)
#define SYS_PLL_SSC_DIG_GPU2_REG_PI_CUR_SEL_GPU(data)                                (0x0000001C&((data)<<2))
#define SYS_PLL_SSC_DIG_GPU2_REG_PI_CUR_SEL_GPU_src(data)                            ((0x0000001C&(data))>>2)
#define SYS_PLL_SSC_DIG_GPU2_get_REG_PI_CUR_SEL_GPU(data)                            ((0x0000001C&(data))>>2)
#define SYS_PLL_SSC_DIG_GPU2_REG_EN_PI_DEBUG_GPU_shift                               (1)
#define SYS_PLL_SSC_DIG_GPU2_REG_EN_PI_DEBUG_GPU_mask                                (0x00000002)
#define SYS_PLL_SSC_DIG_GPU2_REG_EN_PI_DEBUG_GPU(data)                               (0x00000002&((data)<<1))
#define SYS_PLL_SSC_DIG_GPU2_REG_EN_PI_DEBUG_GPU_src(data)                           ((0x00000002&(data))>>1)
#define SYS_PLL_SSC_DIG_GPU2_get_REG_EN_PI_DEBUG_GPU(data)                           ((0x00000002&(data))>>1)


#define SYS_PLL_SSC_DIG_GPU3                                                         0x980005AC
#define SYS_PLL_SSC_DIG_GPU3_reg_addr                                                "0x980005AC"
#define SYS_PLL_SSC_DIG_GPU3_reg                                                     0x980005AC
#define set_SYS_PLL_SSC_DIG_GPU3_reg(data)   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_GPU3_reg)=data)
#define get_SYS_PLL_SSC_DIG_GPU3_reg   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_GPU3_reg))
#define SYS_PLL_SSC_DIG_GPU3_inst_adr                                                "0x006B"
#define SYS_PLL_SSC_DIG_GPU3_inst                                                    0x006B
#define SYS_PLL_SSC_DIG_GPU3_NCODE_SSC_GPU_shift                                     (11)
#define SYS_PLL_SSC_DIG_GPU3_NCODE_SSC_GPU_mask                                      (0x0007F800)
#define SYS_PLL_SSC_DIG_GPU3_NCODE_SSC_GPU(data)                                     (0x0007F800&((data)<<11))
#define SYS_PLL_SSC_DIG_GPU3_NCODE_SSC_GPU_src(data)                                 ((0x0007F800&(data))>>11)
#define SYS_PLL_SSC_DIG_GPU3_get_NCODE_SSC_GPU(data)                                 ((0x0007F800&(data))>>11)
#define SYS_PLL_SSC_DIG_GPU3_FCODE_SSC_GPU_shift                                     (0)
#define SYS_PLL_SSC_DIG_GPU3_FCODE_SSC_GPU_mask                                      (0x000007FF)
#define SYS_PLL_SSC_DIG_GPU3_FCODE_SSC_GPU(data)                                     (0x000007FF&((data)<<0))
#define SYS_PLL_SSC_DIG_GPU3_FCODE_SSC_GPU_src(data)                                 ((0x000007FF&(data))>>0)
#define SYS_PLL_SSC_DIG_GPU3_get_FCODE_SSC_GPU(data)                                 ((0x000007FF&(data))>>0)


#define SYS_PLL_SSC_DIG_GPU4                                                         0x980005B0
#define SYS_PLL_SSC_DIG_GPU4_reg_addr                                                "0x980005B0"
#define SYS_PLL_SSC_DIG_GPU4_reg                                                     0x980005B0
#define set_SYS_PLL_SSC_DIG_GPU4_reg(data)   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_GPU4_reg)=data)
#define get_SYS_PLL_SSC_DIG_GPU4_reg   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_GPU4_reg))
#define SYS_PLL_SSC_DIG_GPU4_inst_adr                                                "0x006C"
#define SYS_PLL_SSC_DIG_GPU4_inst                                                    0x006C
#define SYS_PLL_SSC_DIG_GPU4_GRAN_EST_GPU_shift                                      (0)
#define SYS_PLL_SSC_DIG_GPU4_GRAN_EST_GPU_mask                                       (0x0007FFFF)
#define SYS_PLL_SSC_DIG_GPU4_GRAN_EST_GPU(data)                                      (0x0007FFFF&((data)<<0))
#define SYS_PLL_SSC_DIG_GPU4_GRAN_EST_GPU_src(data)                                  ((0x0007FFFF&(data))>>0)
#define SYS_PLL_SSC_DIG_GPU4_get_GRAN_EST_GPU(data)                                  ((0x0007FFFF&(data))>>0)


#define SYS_PLL_SSC_DIG_GPU5                                                         0x980005B4
#define SYS_PLL_SSC_DIG_GPU5_reg_addr                                                "0x980005B4"
#define SYS_PLL_SSC_DIG_GPU5_reg                                                     0x980005B4
#define set_SYS_PLL_SSC_DIG_GPU5_reg(data)   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_GPU5_reg)=data)
#define get_SYS_PLL_SSC_DIG_GPU5_reg   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_GPU5_reg))
#define SYS_PLL_SSC_DIG_GPU5_inst_adr                                                "0x006D"
#define SYS_PLL_SSC_DIG_GPU5_inst                                                    0x006D
#define SYS_PLL_SSC_DIG_GPU5_FCW_SSC_DEFAULT_GPU_shift                               (0)
#define SYS_PLL_SSC_DIG_GPU5_FCW_SSC_DEFAULT_GPU_mask                                (0x0007FFFF)
#define SYS_PLL_SSC_DIG_GPU5_FCW_SSC_DEFAULT_GPU(data)                               (0x0007FFFF&((data)<<0))
#define SYS_PLL_SSC_DIG_GPU5_FCW_SSC_DEFAULT_GPU_src(data)                           ((0x0007FFFF&(data))>>0)
#define SYS_PLL_SSC_DIG_GPU5_get_FCW_SSC_DEFAULT_GPU(data)                           ((0x0007FFFF&(data))>>0)


#define SYS_PLL_SSC_DIG_GPU_DBG1                                                     0x980005B8
#define SYS_PLL_SSC_DIG_GPU_DBG1_reg_addr                                            "0x980005B8"
#define SYS_PLL_SSC_DIG_GPU_DBG1_reg                                                 0x980005B8
#define set_SYS_PLL_SSC_DIG_GPU_DBG1_reg(data)   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_GPU_DBG1_reg)=data)
#define get_SYS_PLL_SSC_DIG_GPU_DBG1_reg   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_GPU_DBG1_reg))
#define SYS_PLL_SSC_DIG_GPU_DBG1_inst_adr                                            "0x006E"
#define SYS_PLL_SSC_DIG_GPU_DBG1_inst                                                0x006E
#define SYS_PLL_SSC_DIG_GPU_DBG1_LOOP_PI_ISEL_GPU_shift                              (13)
#define SYS_PLL_SSC_DIG_GPU_DBG1_LOOP_PI_ISEL_GPU_mask                               (0x0000E000)
#define SYS_PLL_SSC_DIG_GPU_DBG1_LOOP_PI_ISEL_GPU(data)                              (0x0000E000&((data)<<13))
#define SYS_PLL_SSC_DIG_GPU_DBG1_LOOP_PI_ISEL_GPU_src(data)                          ((0x0000E000&(data))>>13)
#define SYS_PLL_SSC_DIG_GPU_DBG1_get_LOOP_PI_ISEL_GPU(data)                          ((0x0000E000&(data))>>13)
#define SYS_PLL_SSC_DIG_GPU_DBG1_PHSEL_GPU_shift                                     (8)
#define SYS_PLL_SSC_DIG_GPU_DBG1_PHSEL_GPU_mask                                      (0x00001F00)
#define SYS_PLL_SSC_DIG_GPU_DBG1_PHSEL_GPU(data)                                     (0x00001F00&((data)<<8))
#define SYS_PLL_SSC_DIG_GPU_DBG1_PHSEL_GPU_src(data)                                 ((0x00001F00&(data))>>8)
#define SYS_PLL_SSC_DIG_GPU_DBG1_get_PHSEL_GPU(data)                                 ((0x00001F00&(data))>>8)
#define SYS_PLL_SSC_DIG_GPU_DBG1_DIVN_GPU_shift                                      (0)
#define SYS_PLL_SSC_DIG_GPU_DBG1_DIVN_GPU_mask                                       (0x000000FF)
#define SYS_PLL_SSC_DIG_GPU_DBG1_DIVN_GPU(data)                                      (0x000000FF&((data)<<0))
#define SYS_PLL_SSC_DIG_GPU_DBG1_DIVN_GPU_src(data)                                  ((0x000000FF&(data))>>0)
#define SYS_PLL_SSC_DIG_GPU_DBG1_get_DIVN_GPU(data)                                  ((0x000000FF&(data))>>0)


#define SYS_PLL_SSC_DIG_GPU_DBG2                                                     0x980005BC
#define SYS_PLL_SSC_DIG_GPU_DBG2_reg_addr                                            "0x980005BC"
#define SYS_PLL_SSC_DIG_GPU_DBG2_reg                                                 0x980005BC
#define set_SYS_PLL_SSC_DIG_GPU_DBG2_reg(data)   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_GPU_DBG2_reg)=data)
#define get_SYS_PLL_SSC_DIG_GPU_DBG2_reg   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_GPU_DBG2_reg))
#define SYS_PLL_SSC_DIG_GPU_DBG2_inst_adr                                            "0x006F"
#define SYS_PLL_SSC_DIG_GPU_DBG2_inst                                                0x006F
#define SYS_PLL_SSC_DIG_GPU_DBG2_load_FCW_GPU_shift                                  (21)
#define SYS_PLL_SSC_DIG_GPU_DBG2_load_FCW_GPU_mask                                   (0x00200000)
#define SYS_PLL_SSC_DIG_GPU_DBG2_load_FCW_GPU(data)                                  (0x00200000&((data)<<21))
#define SYS_PLL_SSC_DIG_GPU_DBG2_load_FCW_GPU_src(data)                              ((0x00200000&(data))>>21)
#define SYS_PLL_SSC_DIG_GPU_DBG2_get_load_FCW_GPU(data)                              ((0x00200000&(data))>>21)
#define SYS_PLL_SSC_DIG_GPU_DBG2_OC_DONE_GPU_shift                                   (20)
#define SYS_PLL_SSC_DIG_GPU_DBG2_OC_DONE_GPU_mask                                    (0x00100000)
#define SYS_PLL_SSC_DIG_GPU_DBG2_OC_DONE_GPU(data)                                   (0x00100000&((data)<<20))
#define SYS_PLL_SSC_DIG_GPU_DBG2_OC_DONE_GPU_src(data)                               ((0x00100000&(data))>>20)
#define SYS_PLL_SSC_DIG_GPU_DBG2_get_OC_DONE_GPU(data)                               ((0x00100000&(data))>>20)
#define SYS_PLL_SSC_DIG_GPU_DBG2_FMOD_GPU_shift                                      (19)
#define SYS_PLL_SSC_DIG_GPU_DBG2_FMOD_GPU_mask                                       (0x00080000)
#define SYS_PLL_SSC_DIG_GPU_DBG2_FMOD_GPU(data)                                      (0x00080000&((data)<<19))
#define SYS_PLL_SSC_DIG_GPU_DBG2_FMOD_GPU_src(data)                                  ((0x00080000&(data))>>19)
#define SYS_PLL_SSC_DIG_GPU_DBG2_get_FMOD_GPU(data)                                  ((0x00080000&(data))>>19)
#define SYS_PLL_SSC_DIG_GPU_DBG2_NCODE_DEBUG_GPU_shift                               (11)
#define SYS_PLL_SSC_DIG_GPU_DBG2_NCODE_DEBUG_GPU_mask                                (0x0007F800)
#define SYS_PLL_SSC_DIG_GPU_DBG2_NCODE_DEBUG_GPU(data)                               (0x0007F800&((data)<<11))
#define SYS_PLL_SSC_DIG_GPU_DBG2_NCODE_DEBUG_GPU_src(data)                           ((0x0007F800&(data))>>11)
#define SYS_PLL_SSC_DIG_GPU_DBG2_get_NCODE_DEBUG_GPU(data)                           ((0x0007F800&(data))>>11)
#define SYS_PLL_SSC_DIG_GPU_DBG2_FCODE_DEBUG_GPU_shift                               (0)
#define SYS_PLL_SSC_DIG_GPU_DBG2_FCODE_DEBUG_GPU_mask                                (0x000007FF)
#define SYS_PLL_SSC_DIG_GPU_DBG2_FCODE_DEBUG_GPU(data)                               (0x000007FF&((data)<<0))
#define SYS_PLL_SSC_DIG_GPU_DBG2_FCODE_DEBUG_GPU_src(data)                           ((0x000007FF&(data))>>0)
#define SYS_PLL_SSC_DIG_GPU_DBG2_get_FCODE_DEBUG_GPU(data)                           ((0x000007FF&(data))>>0)


#define SYS_PLL_SSC_DIG_ACPU0                                                        0x980005C0
#define SYS_PLL_SSC_DIG_ACPU0_reg_addr                                               "0x980005C0"
#define SYS_PLL_SSC_DIG_ACPU0_reg                                                    0x980005C0
#define set_SYS_PLL_SSC_DIG_ACPU0_reg(data)   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_ACPU0_reg)=data)
#define get_SYS_PLL_SSC_DIG_ACPU0_reg   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_ACPU0_reg))
#define SYS_PLL_SSC_DIG_ACPU0_inst_adr                                               "0x0070"
#define SYS_PLL_SSC_DIG_ACPU0_inst                                                   0x0070
#define SYS_PLL_SSC_DIG_ACPU0_REG_CKSSC_INV_ACPU_shift                               (4)
#define SYS_PLL_SSC_DIG_ACPU0_REG_CKSSC_INV_ACPU_mask                                (0x00000010)
#define SYS_PLL_SSC_DIG_ACPU0_REG_CKSSC_INV_ACPU(data)                               (0x00000010&((data)<<4))
#define SYS_PLL_SSC_DIG_ACPU0_REG_CKSSC_INV_ACPU_src(data)                           ((0x00000010&(data))>>4)
#define SYS_PLL_SSC_DIG_ACPU0_get_REG_CKSSC_INV_ACPU(data)                           ((0x00000010&(data))>>4)
#define SYS_PLL_SSC_DIG_ACPU0_REG_GRAN_AUTO_RST_ACPU_shift                           (3)
#define SYS_PLL_SSC_DIG_ACPU0_REG_GRAN_AUTO_RST_ACPU_mask                            (0x00000008)
#define SYS_PLL_SSC_DIG_ACPU0_REG_GRAN_AUTO_RST_ACPU(data)                           (0x00000008&((data)<<3))
#define SYS_PLL_SSC_DIG_ACPU0_REG_GRAN_AUTO_RST_ACPU_src(data)                       ((0x00000008&(data))>>3)
#define SYS_PLL_SSC_DIG_ACPU0_get_REG_GRAN_AUTO_RST_ACPU(data)                       ((0x00000008&(data))>>3)
#define SYS_PLL_SSC_DIG_ACPU0_RSTB_ACPU_shift                                        (2)
#define SYS_PLL_SSC_DIG_ACPU0_RSTB_ACPU_mask                                         (0x00000004)
#define SYS_PLL_SSC_DIG_ACPU0_RSTB_ACPU(data)                                        (0x00000004&((data)<<2))
#define SYS_PLL_SSC_DIG_ACPU0_RSTB_ACPU_src(data)                                    ((0x00000004&(data))>>2)
#define SYS_PLL_SSC_DIG_ACPU0_get_RSTB_ACPU(data)                                    ((0x00000004&(data))>>2)
#define SYS_PLL_SSC_DIG_ACPU0_EN_SSC_ACPU_shift                                      (1)
#define SYS_PLL_SSC_DIG_ACPU0_EN_SSC_ACPU_mask                                       (0x00000002)
#define SYS_PLL_SSC_DIG_ACPU0_EN_SSC_ACPU(data)                                      (0x00000002&((data)<<1))
#define SYS_PLL_SSC_DIG_ACPU0_EN_SSC_ACPU_src(data)                                  ((0x00000002&(data))>>1)
#define SYS_PLL_SSC_DIG_ACPU0_get_EN_SSC_ACPU(data)                                  ((0x00000002&(data))>>1)
#define SYS_PLL_SSC_DIG_ACPU0_OC_EN_ACPU_shift                                       (0)
#define SYS_PLL_SSC_DIG_ACPU0_OC_EN_ACPU_mask                                        (0x00000001)
#define SYS_PLL_SSC_DIG_ACPU0_OC_EN_ACPU(data)                                       (0x00000001&((data)<<0))
#define SYS_PLL_SSC_DIG_ACPU0_OC_EN_ACPU_src(data)                                   ((0x00000001&(data))>>0)
#define SYS_PLL_SSC_DIG_ACPU0_get_OC_EN_ACPU(data)                                   ((0x00000001&(data))>>0)


#define SYS_PLL_SSC_DIG_ACPU1                                                        0x980005C4
#define SYS_PLL_SSC_DIG_ACPU1_reg_addr                                               "0x980005C4"
#define SYS_PLL_SSC_DIG_ACPU1_reg                                                    0x980005C4
#define set_SYS_PLL_SSC_DIG_ACPU1_reg(data)   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_ACPU1_reg)=data)
#define get_SYS_PLL_SSC_DIG_ACPU1_reg   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_ACPU1_reg))
#define SYS_PLL_SSC_DIG_ACPU1_inst_adr                                               "0x0071"
#define SYS_PLL_SSC_DIG_ACPU1_inst                                                   0x0071
#define SYS_PLL_SSC_DIG_ACPU1_NCODE_T_ACPU_shift                                     (11)
#define SYS_PLL_SSC_DIG_ACPU1_NCODE_T_ACPU_mask                                      (0x0007F800)
#define SYS_PLL_SSC_DIG_ACPU1_NCODE_T_ACPU(data)                                     (0x0007F800&((data)<<11))
#define SYS_PLL_SSC_DIG_ACPU1_NCODE_T_ACPU_src(data)                                 ((0x0007F800&(data))>>11)
#define SYS_PLL_SSC_DIG_ACPU1_get_NCODE_T_ACPU(data)                                 ((0x0007F800&(data))>>11)
#define SYS_PLL_SSC_DIG_ACPU1_FCODE_T_ACPU_shift                                     (0)
#define SYS_PLL_SSC_DIG_ACPU1_FCODE_T_ACPU_mask                                      (0x000007FF)
#define SYS_PLL_SSC_DIG_ACPU1_FCODE_T_ACPU(data)                                     (0x000007FF&((data)<<0))
#define SYS_PLL_SSC_DIG_ACPU1_FCODE_T_ACPU_src(data)                                 ((0x000007FF&(data))>>0)
#define SYS_PLL_SSC_DIG_ACPU1_get_FCODE_T_ACPU(data)                                 ((0x000007FF&(data))>>0)


#define SYS_PLL_SSC_DIG_ACPU2                                                        0x980005C8
#define SYS_PLL_SSC_DIG_ACPU2_reg_addr                                               "0x980005C8"
#define SYS_PLL_SSC_DIG_ACPU2_reg                                                    0x980005C8
#define set_SYS_PLL_SSC_DIG_ACPU2_reg(data)   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_ACPU2_reg)=data)
#define get_SYS_PLL_SSC_DIG_ACPU2_reg   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_ACPU2_reg))
#define SYS_PLL_SSC_DIG_ACPU2_inst_adr                                               "0x0072"
#define SYS_PLL_SSC_DIG_ACPU2_inst                                                   0x0072
#define SYS_PLL_SSC_DIG_ACPU2_REG_BYPASS_DIVN_shift                                  (27)
#define SYS_PLL_SSC_DIG_ACPU2_REG_BYPASS_DIVN_mask                                   (0x08000000)
#define SYS_PLL_SSC_DIG_ACPU2_REG_BYPASS_DIVN(data)                                  (0x08000000&((data)<<27))
#define SYS_PLL_SSC_DIG_ACPU2_REG_BYPASS_DIVN_src(data)                              ((0x08000000&(data))>>27)
#define SYS_PLL_SSC_DIG_ACPU2_get_REG_BYPASS_DIVN(data)                              ((0x08000000&(data))>>27)
#define SYS_PLL_SSC_DIG_ACPU2_REG_OC_STEP_SET_ACPU_shift                             (17)
#define SYS_PLL_SSC_DIG_ACPU2_REG_OC_STEP_SET_ACPU_mask                              (0x07FE0000)
#define SYS_PLL_SSC_DIG_ACPU2_REG_OC_STEP_SET_ACPU(data)                             (0x07FE0000&((data)<<17))
#define SYS_PLL_SSC_DIG_ACPU2_REG_OC_STEP_SET_ACPU_src(data)                         ((0x07FE0000&(data))>>17)
#define SYS_PLL_SSC_DIG_ACPU2_get_REG_OC_STEP_SET_ACPU(data)                         ((0x07FE0000&(data))>>17)
#define SYS_PLL_SSC_DIG_ACPU2_REG_SEL_OC_MODE_ACPU_shift                             (15)
#define SYS_PLL_SSC_DIG_ACPU2_REG_SEL_OC_MODE_ACPU_mask                              (0x00018000)
#define SYS_PLL_SSC_DIG_ACPU2_REG_SEL_OC_MODE_ACPU(data)                             (0x00018000&((data)<<15))
#define SYS_PLL_SSC_DIG_ACPU2_REG_SEL_OC_MODE_ACPU_src(data)                         ((0x00018000&(data))>>15)
#define SYS_PLL_SSC_DIG_ACPU2_get_REG_SEL_OC_MODE_ACPU(data)                         ((0x00018000&(data))>>15)
#define SYS_PLL_SSC_DIG_ACPU2_REG_HS_OC_STOP_DIFF_ACPU_shift                         (13)
#define SYS_PLL_SSC_DIG_ACPU2_REG_HS_OC_STOP_DIFF_ACPU_mask                          (0x00006000)
#define SYS_PLL_SSC_DIG_ACPU2_REG_HS_OC_STOP_DIFF_ACPU(data)                         (0x00006000&((data)<<13))
#define SYS_PLL_SSC_DIG_ACPU2_REG_HS_OC_STOP_DIFF_ACPU_src(data)                     ((0x00006000&(data))>>13)
#define SYS_PLL_SSC_DIG_ACPU2_get_REG_HS_OC_STOP_DIFF_ACPU(data)                     ((0x00006000&(data))>>13)
#define SYS_PLL_SSC_DIG_ACPU2_REG_OC_DONE_DELAY_ACPU_shift                           (7)
#define SYS_PLL_SSC_DIG_ACPU2_REG_OC_DONE_DELAY_ACPU_mask                            (0x00001F80)
#define SYS_PLL_SSC_DIG_ACPU2_REG_OC_DONE_DELAY_ACPU(data)                           (0x00001F80&((data)<<7))
#define SYS_PLL_SSC_DIG_ACPU2_REG_OC_DONE_DELAY_ACPU_src(data)                       ((0x00001F80&(data))>>7)
#define SYS_PLL_SSC_DIG_ACPU2_get_REG_OC_DONE_DELAY_ACPU(data)                       ((0x00001F80&(data))>>7)
#define SYS_PLL_SSC_DIG_ACPU2_REG_BYPASS_PI_ACPU_shift                               (6)
#define SYS_PLL_SSC_DIG_ACPU2_REG_BYPASS_PI_ACPU_mask                                (0x00000040)
#define SYS_PLL_SSC_DIG_ACPU2_REG_BYPASS_PI_ACPU(data)                               (0x00000040&((data)<<6))
#define SYS_PLL_SSC_DIG_ACPU2_REG_BYPASS_PI_ACPU_src(data)                           ((0x00000040&(data))>>6)
#define SYS_PLL_SSC_DIG_ACPU2_get_REG_BYPASS_PI_ACPU(data)                           ((0x00000040&(data))>>6)
#define SYS_PLL_SSC_DIG_ACPU2_REG_SDM_ORDER_ACPU_shift                               (5)
#define SYS_PLL_SSC_DIG_ACPU2_REG_SDM_ORDER_ACPU_mask                                (0x00000020)
#define SYS_PLL_SSC_DIG_ACPU2_REG_SDM_ORDER_ACPU(data)                               (0x00000020&((data)<<5))
#define SYS_PLL_SSC_DIG_ACPU2_REG_SDM_ORDER_ACPU_src(data)                           ((0x00000020&(data))>>5)
#define SYS_PLL_SSC_DIG_ACPU2_get_REG_SDM_ORDER_ACPU(data)                           ((0x00000020&(data))>>5)
#define SYS_PLL_SSC_DIG_ACPU2_REG_PI_CUR_SEL_ACPU_shift                              (2)
#define SYS_PLL_SSC_DIG_ACPU2_REG_PI_CUR_SEL_ACPU_mask                               (0x0000001C)
#define SYS_PLL_SSC_DIG_ACPU2_REG_PI_CUR_SEL_ACPU(data)                              (0x0000001C&((data)<<2))
#define SYS_PLL_SSC_DIG_ACPU2_REG_PI_CUR_SEL_ACPU_src(data)                          ((0x0000001C&(data))>>2)
#define SYS_PLL_SSC_DIG_ACPU2_get_REG_PI_CUR_SEL_ACPU(data)                          ((0x0000001C&(data))>>2)
#define SYS_PLL_SSC_DIG_ACPU2_REG_EN_PI_DEBUG_ACPU_shift                             (1)
#define SYS_PLL_SSC_DIG_ACPU2_REG_EN_PI_DEBUG_ACPU_mask                              (0x00000002)
#define SYS_PLL_SSC_DIG_ACPU2_REG_EN_PI_DEBUG_ACPU(data)                             (0x00000002&((data)<<1))
#define SYS_PLL_SSC_DIG_ACPU2_REG_EN_PI_DEBUG_ACPU_src(data)                         ((0x00000002&(data))>>1)
#define SYS_PLL_SSC_DIG_ACPU2_get_REG_EN_PI_DEBUG_ACPU(data)                         ((0x00000002&(data))>>1)


#define SYS_PLL_SSC_DIG_ACPU3                                                        0x980005CC
#define SYS_PLL_SSC_DIG_ACPU3_reg_addr                                               "0x980005CC"
#define SYS_PLL_SSC_DIG_ACPU3_reg                                                    0x980005CC
#define set_SYS_PLL_SSC_DIG_ACPU3_reg(data)   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_ACPU3_reg)=data)
#define get_SYS_PLL_SSC_DIG_ACPU3_reg   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_ACPU3_reg))
#define SYS_PLL_SSC_DIG_ACPU3_inst_adr                                               "0x0073"
#define SYS_PLL_SSC_DIG_ACPU3_inst                                                   0x0073
#define SYS_PLL_SSC_DIG_ACPU3_NCODE_SSC_ACPU_shift                                   (11)
#define SYS_PLL_SSC_DIG_ACPU3_NCODE_SSC_ACPU_mask                                    (0x0007F800)
#define SYS_PLL_SSC_DIG_ACPU3_NCODE_SSC_ACPU(data)                                   (0x0007F800&((data)<<11))
#define SYS_PLL_SSC_DIG_ACPU3_NCODE_SSC_ACPU_src(data)                               ((0x0007F800&(data))>>11)
#define SYS_PLL_SSC_DIG_ACPU3_get_NCODE_SSC_ACPU(data)                               ((0x0007F800&(data))>>11)
#define SYS_PLL_SSC_DIG_ACPU3_FCODE_SSC_ACPU_shift                                   (0)
#define SYS_PLL_SSC_DIG_ACPU3_FCODE_SSC_ACPU_mask                                    (0x000007FF)
#define SYS_PLL_SSC_DIG_ACPU3_FCODE_SSC_ACPU(data)                                   (0x000007FF&((data)<<0))
#define SYS_PLL_SSC_DIG_ACPU3_FCODE_SSC_ACPU_src(data)                               ((0x000007FF&(data))>>0)
#define SYS_PLL_SSC_DIG_ACPU3_get_FCODE_SSC_ACPU(data)                               ((0x000007FF&(data))>>0)


#define SYS_PLL_SSC_DIG_ACPU4                                                        0x980005D0
#define SYS_PLL_SSC_DIG_ACPU4_reg_addr                                               "0x980005D0"
#define SYS_PLL_SSC_DIG_ACPU4_reg                                                    0x980005D0
#define set_SYS_PLL_SSC_DIG_ACPU4_reg(data)   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_ACPU4_reg)=data)
#define get_SYS_PLL_SSC_DIG_ACPU4_reg   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_ACPU4_reg))
#define SYS_PLL_SSC_DIG_ACPU4_inst_adr                                               "0x0074"
#define SYS_PLL_SSC_DIG_ACPU4_inst                                                   0x0074
#define SYS_PLL_SSC_DIG_ACPU4_GRAN_EST_ACPU_shift                                    (0)
#define SYS_PLL_SSC_DIG_ACPU4_GRAN_EST_ACPU_mask                                     (0x0007FFFF)
#define SYS_PLL_SSC_DIG_ACPU4_GRAN_EST_ACPU(data)                                    (0x0007FFFF&((data)<<0))
#define SYS_PLL_SSC_DIG_ACPU4_GRAN_EST_ACPU_src(data)                                ((0x0007FFFF&(data))>>0)
#define SYS_PLL_SSC_DIG_ACPU4_get_GRAN_EST_ACPU(data)                                ((0x0007FFFF&(data))>>0)


#define SYS_PLL_SSC_DIG_ACPU5                                                        0x980005D4
#define SYS_PLL_SSC_DIG_ACPU5_reg_addr                                               "0x980005D4"
#define SYS_PLL_SSC_DIG_ACPU5_reg                                                    0x980005D4
#define set_SYS_PLL_SSC_DIG_ACPU5_reg(data)   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_ACPU5_reg)=data)
#define get_SYS_PLL_SSC_DIG_ACPU5_reg   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_ACPU5_reg))
#define SYS_PLL_SSC_DIG_ACPU5_inst_adr                                               "0x0075"
#define SYS_PLL_SSC_DIG_ACPU5_inst                                                   0x0075
#define SYS_PLL_SSC_DIG_ACPU5_FCW_SSC_DEFAULT_ACPU_shift                             (0)
#define SYS_PLL_SSC_DIG_ACPU5_FCW_SSC_DEFAULT_ACPU_mask                              (0x0007FFFF)
#define SYS_PLL_SSC_DIG_ACPU5_FCW_SSC_DEFAULT_ACPU(data)                             (0x0007FFFF&((data)<<0))
#define SYS_PLL_SSC_DIG_ACPU5_FCW_SSC_DEFAULT_ACPU_src(data)                         ((0x0007FFFF&(data))>>0)
#define SYS_PLL_SSC_DIG_ACPU5_get_FCW_SSC_DEFAULT_ACPU(data)                         ((0x0007FFFF&(data))>>0)


#define SYS_PLL_SSC_DIG_ACPU_DBG1                                                    0x980005D8
#define SYS_PLL_SSC_DIG_ACPU_DBG1_reg_addr                                           "0x980005D8"
#define SYS_PLL_SSC_DIG_ACPU_DBG1_reg                                                0x980005D8
#define set_SYS_PLL_SSC_DIG_ACPU_DBG1_reg(data)   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_ACPU_DBG1_reg)=data)
#define get_SYS_PLL_SSC_DIG_ACPU_DBG1_reg   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_ACPU_DBG1_reg))
#define SYS_PLL_SSC_DIG_ACPU_DBG1_inst_adr                                           "0x0076"
#define SYS_PLL_SSC_DIG_ACPU_DBG1_inst                                               0x0076
#define SYS_PLL_SSC_DIG_ACPU_DBG1_LOOP_PI_ISEL_ACPU_shift                            (13)
#define SYS_PLL_SSC_DIG_ACPU_DBG1_LOOP_PI_ISEL_ACPU_mask                             (0x0000E000)
#define SYS_PLL_SSC_DIG_ACPU_DBG1_LOOP_PI_ISEL_ACPU(data)                            (0x0000E000&((data)<<13))
#define SYS_PLL_SSC_DIG_ACPU_DBG1_LOOP_PI_ISEL_ACPU_src(data)                        ((0x0000E000&(data))>>13)
#define SYS_PLL_SSC_DIG_ACPU_DBG1_get_LOOP_PI_ISEL_ACPU(data)                        ((0x0000E000&(data))>>13)
#define SYS_PLL_SSC_DIG_ACPU_DBG1_PHSEL_ACPU_shift                                   (8)
#define SYS_PLL_SSC_DIG_ACPU_DBG1_PHSEL_ACPU_mask                                    (0x00001F00)
#define SYS_PLL_SSC_DIG_ACPU_DBG1_PHSEL_ACPU(data)                                   (0x00001F00&((data)<<8))
#define SYS_PLL_SSC_DIG_ACPU_DBG1_PHSEL_ACPU_src(data)                               ((0x00001F00&(data))>>8)
#define SYS_PLL_SSC_DIG_ACPU_DBG1_get_PHSEL_ACPU(data)                               ((0x00001F00&(data))>>8)
#define SYS_PLL_SSC_DIG_ACPU_DBG1_DIVN_ACPU_shift                                    (0)
#define SYS_PLL_SSC_DIG_ACPU_DBG1_DIVN_ACPU_mask                                     (0x000000FF)
#define SYS_PLL_SSC_DIG_ACPU_DBG1_DIVN_ACPU(data)                                    (0x000000FF&((data)<<0))
#define SYS_PLL_SSC_DIG_ACPU_DBG1_DIVN_ACPU_src(data)                                ((0x000000FF&(data))>>0)
#define SYS_PLL_SSC_DIG_ACPU_DBG1_get_DIVN_ACPU(data)                                ((0x000000FF&(data))>>0)


#define SYS_PLL_SSC_DIG_ACPU_DBG2                                                    0x980005DC
#define SYS_PLL_SSC_DIG_ACPU_DBG2_reg_addr                                           "0x980005DC"
#define SYS_PLL_SSC_DIG_ACPU_DBG2_reg                                                0x980005DC
#define set_SYS_PLL_SSC_DIG_ACPU_DBG2_reg(data)   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_ACPU_DBG2_reg)=data)
#define get_SYS_PLL_SSC_DIG_ACPU_DBG2_reg   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_ACPU_DBG2_reg))
#define SYS_PLL_SSC_DIG_ACPU_DBG2_inst_adr                                           "0x0077"
#define SYS_PLL_SSC_DIG_ACPU_DBG2_inst                                               0x0077
#define SYS_PLL_SSC_DIG_ACPU_DBG2_load_FCW_ACPU_shift                                (21)
#define SYS_PLL_SSC_DIG_ACPU_DBG2_load_FCW_ACPU_mask                                 (0x00200000)
#define SYS_PLL_SSC_DIG_ACPU_DBG2_load_FCW_ACPU(data)                                (0x00200000&((data)<<21))
#define SYS_PLL_SSC_DIG_ACPU_DBG2_load_FCW_ACPU_src(data)                            ((0x00200000&(data))>>21)
#define SYS_PLL_SSC_DIG_ACPU_DBG2_get_load_FCW_ACPU(data)                            ((0x00200000&(data))>>21)
#define SYS_PLL_SSC_DIG_ACPU_DBG2_OC_DONE_ACPU_shift                                 (20)
#define SYS_PLL_SSC_DIG_ACPU_DBG2_OC_DONE_ACPU_mask                                  (0x00100000)
#define SYS_PLL_SSC_DIG_ACPU_DBG2_OC_DONE_ACPU(data)                                 (0x00100000&((data)<<20))
#define SYS_PLL_SSC_DIG_ACPU_DBG2_OC_DONE_ACPU_src(data)                             ((0x00100000&(data))>>20)
#define SYS_PLL_SSC_DIG_ACPU_DBG2_get_OC_DONE_ACPU(data)                             ((0x00100000&(data))>>20)
#define SYS_PLL_SSC_DIG_ACPU_DBG2_FMOD_ACPU_shift                                    (19)
#define SYS_PLL_SSC_DIG_ACPU_DBG2_FMOD_ACPU_mask                                     (0x00080000)
#define SYS_PLL_SSC_DIG_ACPU_DBG2_FMOD_ACPU(data)                                    (0x00080000&((data)<<19))
#define SYS_PLL_SSC_DIG_ACPU_DBG2_FMOD_ACPU_src(data)                                ((0x00080000&(data))>>19)
#define SYS_PLL_SSC_DIG_ACPU_DBG2_get_FMOD_ACPU(data)                                ((0x00080000&(data))>>19)
#define SYS_PLL_SSC_DIG_ACPU_DBG2_NCODE_DEBUG_ACPU_shift                             (11)
#define SYS_PLL_SSC_DIG_ACPU_DBG2_NCODE_DEBUG_ACPU_mask                              (0x0007F800)
#define SYS_PLL_SSC_DIG_ACPU_DBG2_NCODE_DEBUG_ACPU(data)                             (0x0007F800&((data)<<11))
#define SYS_PLL_SSC_DIG_ACPU_DBG2_NCODE_DEBUG_ACPU_src(data)                         ((0x0007F800&(data))>>11)
#define SYS_PLL_SSC_DIG_ACPU_DBG2_get_NCODE_DEBUG_ACPU(data)                         ((0x0007F800&(data))>>11)
#define SYS_PLL_SSC_DIG_ACPU_DBG2_FCODE_DEBUG_ACPU_shift                             (0)
#define SYS_PLL_SSC_DIG_ACPU_DBG2_FCODE_DEBUG_ACPU_mask                              (0x000007FF)
#define SYS_PLL_SSC_DIG_ACPU_DBG2_FCODE_DEBUG_ACPU(data)                             (0x000007FF&((data)<<0))
#define SYS_PLL_SSC_DIG_ACPU_DBG2_FCODE_DEBUG_ACPU_src(data)                         ((0x000007FF&(data))>>0)
#define SYS_PLL_SSC_DIG_ACPU_DBG2_get_FCODE_DEBUG_ACPU(data)                         ((0x000007FF&(data))>>0)


#define SYS_PLL_SSC_DIG_EDP0                                                         0x980005E0
#define SYS_PLL_SSC_DIG_EDP0_reg_addr                                                "0x980005E0"
#define SYS_PLL_SSC_DIG_EDP0_reg                                                     0x980005E0
#define set_SYS_PLL_SSC_DIG_EDP0_reg(data)   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_EDP0_reg)=data)
#define get_SYS_PLL_SSC_DIG_EDP0_reg   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_EDP0_reg))
#define SYS_PLL_SSC_DIG_EDP0_inst_adr                                                "0x0078"
#define SYS_PLL_SSC_DIG_EDP0_inst                                                    0x0078
#define SYS_PLL_SSC_DIG_EDP0_REG_CKSSC_INV_EDP_shift                                 (4)
#define SYS_PLL_SSC_DIG_EDP0_REG_CKSSC_INV_EDP_mask                                  (0x00000010)
#define SYS_PLL_SSC_DIG_EDP0_REG_CKSSC_INV_EDP(data)                                 (0x00000010&((data)<<4))
#define SYS_PLL_SSC_DIG_EDP0_REG_CKSSC_INV_EDP_src(data)                             ((0x00000010&(data))>>4)
#define SYS_PLL_SSC_DIG_EDP0_get_REG_CKSSC_INV_EDP(data)                             ((0x00000010&(data))>>4)
#define SYS_PLL_SSC_DIG_EDP0_REG_GRAN_AUTO_RST_EDP_shift                             (3)
#define SYS_PLL_SSC_DIG_EDP0_REG_GRAN_AUTO_RST_EDP_mask                              (0x00000008)
#define SYS_PLL_SSC_DIG_EDP0_REG_GRAN_AUTO_RST_EDP(data)                             (0x00000008&((data)<<3))
#define SYS_PLL_SSC_DIG_EDP0_REG_GRAN_AUTO_RST_EDP_src(data)                         ((0x00000008&(data))>>3)
#define SYS_PLL_SSC_DIG_EDP0_get_REG_GRAN_AUTO_RST_EDP(data)                         ((0x00000008&(data))>>3)
#define SYS_PLL_SSC_DIG_EDP0_RSTB_EDP_shift                                          (2)
#define SYS_PLL_SSC_DIG_EDP0_RSTB_EDP_mask                                           (0x00000004)
#define SYS_PLL_SSC_DIG_EDP0_RSTB_EDP(data)                                          (0x00000004&((data)<<2))
#define SYS_PLL_SSC_DIG_EDP0_RSTB_EDP_src(data)                                      ((0x00000004&(data))>>2)
#define SYS_PLL_SSC_DIG_EDP0_get_RSTB_EDP(data)                                      ((0x00000004&(data))>>2)
#define SYS_PLL_SSC_DIG_EDP0_EN_SSC_EDP_shift                                        (1)
#define SYS_PLL_SSC_DIG_EDP0_EN_SSC_EDP_mask                                         (0x00000002)
#define SYS_PLL_SSC_DIG_EDP0_EN_SSC_EDP(data)                                        (0x00000002&((data)<<1))
#define SYS_PLL_SSC_DIG_EDP0_EN_SSC_EDP_src(data)                                    ((0x00000002&(data))>>1)
#define SYS_PLL_SSC_DIG_EDP0_get_EN_SSC_EDP(data)                                    ((0x00000002&(data))>>1)
#define SYS_PLL_SSC_DIG_EDP0_OC_EN_EDP_shift                                         (0)
#define SYS_PLL_SSC_DIG_EDP0_OC_EN_EDP_mask                                          (0x00000001)
#define SYS_PLL_SSC_DIG_EDP0_OC_EN_EDP(data)                                         (0x00000001&((data)<<0))
#define SYS_PLL_SSC_DIG_EDP0_OC_EN_EDP_src(data)                                     ((0x00000001&(data))>>0)
#define SYS_PLL_SSC_DIG_EDP0_get_OC_EN_EDP(data)                                     ((0x00000001&(data))>>0)


#define SYS_PLL_SSC_DIG_EDP1                                                         0x980005E4
#define SYS_PLL_SSC_DIG_EDP1_reg_addr                                                "0x980005E4"
#define SYS_PLL_SSC_DIG_EDP1_reg                                                     0x980005E4
#define set_SYS_PLL_SSC_DIG_EDP1_reg(data)   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_EDP1_reg)=data)
#define get_SYS_PLL_SSC_DIG_EDP1_reg   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_EDP1_reg))
#define SYS_PLL_SSC_DIG_EDP1_inst_adr                                                "0x0079"
#define SYS_PLL_SSC_DIG_EDP1_inst                                                    0x0079
#define SYS_PLL_SSC_DIG_EDP1_NCODE_T_EDP_shift                                       (11)
#define SYS_PLL_SSC_DIG_EDP1_NCODE_T_EDP_mask                                        (0x0007F800)
#define SYS_PLL_SSC_DIG_EDP1_NCODE_T_EDP(data)                                       (0x0007F800&((data)<<11))
#define SYS_PLL_SSC_DIG_EDP1_NCODE_T_EDP_src(data)                                   ((0x0007F800&(data))>>11)
#define SYS_PLL_SSC_DIG_EDP1_get_NCODE_T_EDP(data)                                   ((0x0007F800&(data))>>11)
#define SYS_PLL_SSC_DIG_EDP1_FCODE_T_EDP_shift                                       (0)
#define SYS_PLL_SSC_DIG_EDP1_FCODE_T_EDP_mask                                        (0x000007FF)
#define SYS_PLL_SSC_DIG_EDP1_FCODE_T_EDP(data)                                       (0x000007FF&((data)<<0))
#define SYS_PLL_SSC_DIG_EDP1_FCODE_T_EDP_src(data)                                   ((0x000007FF&(data))>>0)
#define SYS_PLL_SSC_DIG_EDP1_get_FCODE_T_EDP(data)                                   ((0x000007FF&(data))>>0)


#define SYS_PLL_SSC_DIG_EDP2                                                         0x980005E8
#define SYS_PLL_SSC_DIG_EDP2_reg_addr                                                "0x980005E8"
#define SYS_PLL_SSC_DIG_EDP2_reg                                                     0x980005E8
#define set_SYS_PLL_SSC_DIG_EDP2_reg(data)   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_EDP2_reg)=data)
#define get_SYS_PLL_SSC_DIG_EDP2_reg   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_EDP2_reg))
#define SYS_PLL_SSC_DIG_EDP2_inst_adr                                                "0x007A"
#define SYS_PLL_SSC_DIG_EDP2_inst                                                    0x007A
#define SYS_PLL_SSC_DIG_EDP2_REG_BYPASS_DIVN_shift                                   (27)
#define SYS_PLL_SSC_DIG_EDP2_REG_BYPASS_DIVN_mask                                    (0x08000000)
#define SYS_PLL_SSC_DIG_EDP2_REG_BYPASS_DIVN(data)                                   (0x08000000&((data)<<27))
#define SYS_PLL_SSC_DIG_EDP2_REG_BYPASS_DIVN_src(data)                               ((0x08000000&(data))>>27)
#define SYS_PLL_SSC_DIG_EDP2_get_REG_BYPASS_DIVN(data)                               ((0x08000000&(data))>>27)
#define SYS_PLL_SSC_DIG_EDP2_REG_OC_STEP_SET_EDP_shift                               (17)
#define SYS_PLL_SSC_DIG_EDP2_REG_OC_STEP_SET_EDP_mask                                (0x07FE0000)
#define SYS_PLL_SSC_DIG_EDP2_REG_OC_STEP_SET_EDP(data)                               (0x07FE0000&((data)<<17))
#define SYS_PLL_SSC_DIG_EDP2_REG_OC_STEP_SET_EDP_src(data)                           ((0x07FE0000&(data))>>17)
#define SYS_PLL_SSC_DIG_EDP2_get_REG_OC_STEP_SET_EDP(data)                           ((0x07FE0000&(data))>>17)
#define SYS_PLL_SSC_DIG_EDP2_REG_SEL_OC_MODE_EDP_shift                               (15)
#define SYS_PLL_SSC_DIG_EDP2_REG_SEL_OC_MODE_EDP_mask                                (0x00018000)
#define SYS_PLL_SSC_DIG_EDP2_REG_SEL_OC_MODE_EDP(data)                               (0x00018000&((data)<<15))
#define SYS_PLL_SSC_DIG_EDP2_REG_SEL_OC_MODE_EDP_src(data)                           ((0x00018000&(data))>>15)
#define SYS_PLL_SSC_DIG_EDP2_get_REG_SEL_OC_MODE_EDP(data)                           ((0x00018000&(data))>>15)
#define SYS_PLL_SSC_DIG_EDP2_REG_HS_OC_STOP_DIFF_EDP_shift                           (13)
#define SYS_PLL_SSC_DIG_EDP2_REG_HS_OC_STOP_DIFF_EDP_mask                            (0x00006000)
#define SYS_PLL_SSC_DIG_EDP2_REG_HS_OC_STOP_DIFF_EDP(data)                           (0x00006000&((data)<<13))
#define SYS_PLL_SSC_DIG_EDP2_REG_HS_OC_STOP_DIFF_EDP_src(data)                       ((0x00006000&(data))>>13)
#define SYS_PLL_SSC_DIG_EDP2_get_REG_HS_OC_STOP_DIFF_EDP(data)                       ((0x00006000&(data))>>13)
#define SYS_PLL_SSC_DIG_EDP2_REG_OC_DONE_DELAY_EDP_shift                             (7)
#define SYS_PLL_SSC_DIG_EDP2_REG_OC_DONE_DELAY_EDP_mask                              (0x00001F80)
#define SYS_PLL_SSC_DIG_EDP2_REG_OC_DONE_DELAY_EDP(data)                             (0x00001F80&((data)<<7))
#define SYS_PLL_SSC_DIG_EDP2_REG_OC_DONE_DELAY_EDP_src(data)                         ((0x00001F80&(data))>>7)
#define SYS_PLL_SSC_DIG_EDP2_get_REG_OC_DONE_DELAY_EDP(data)                         ((0x00001F80&(data))>>7)
#define SYS_PLL_SSC_DIG_EDP2_REG_PI_CUR_SEL_EDP_shift                                (5)
#define SYS_PLL_SSC_DIG_EDP2_REG_PI_CUR_SEL_EDP_mask                                 (0x00000060)
#define SYS_PLL_SSC_DIG_EDP2_REG_PI_CUR_SEL_EDP(data)                                (0x00000060&((data)<<5))
#define SYS_PLL_SSC_DIG_EDP2_REG_PI_CUR_SEL_EDP_src(data)                            ((0x00000060&(data))>>5)
#define SYS_PLL_SSC_DIG_EDP2_get_REG_PI_CUR_SEL_EDP(data)                            ((0x00000060&(data))>>5)
#define SYS_PLL_SSC_DIG_EDP2_REG_BYPASS_PI_EDP_shift                                 (4)
#define SYS_PLL_SSC_DIG_EDP2_REG_BYPASS_PI_EDP_mask                                  (0x00000010)
#define SYS_PLL_SSC_DIG_EDP2_REG_BYPASS_PI_EDP(data)                                 (0x00000010&((data)<<4))
#define SYS_PLL_SSC_DIG_EDP2_REG_BYPASS_PI_EDP_src(data)                             ((0x00000010&(data))>>4)
#define SYS_PLL_SSC_DIG_EDP2_get_REG_BYPASS_PI_EDP(data)                             ((0x00000010&(data))>>4)
#define SYS_PLL_SSC_DIG_EDP2_REG_SDM_ORDER_EDP_shift                                 (3)
#define SYS_PLL_SSC_DIG_EDP2_REG_SDM_ORDER_EDP_mask                                  (0x00000008)
#define SYS_PLL_SSC_DIG_EDP2_REG_SDM_ORDER_EDP(data)                                 (0x00000008&((data)<<3))
#define SYS_PLL_SSC_DIG_EDP2_REG_SDM_ORDER_EDP_src(data)                             ((0x00000008&(data))>>3)
#define SYS_PLL_SSC_DIG_EDP2_get_REG_SDM_ORDER_EDP(data)                             ((0x00000008&(data))>>3)
#define SYS_PLL_SSC_DIG_EDP2_REG_EN_PI_DEBUG_EDP_shift                               (2)
#define SYS_PLL_SSC_DIG_EDP2_REG_EN_PI_DEBUG_EDP_mask                                (0x00000004)
#define SYS_PLL_SSC_DIG_EDP2_REG_EN_PI_DEBUG_EDP(data)                               (0x00000004&((data)<<2))
#define SYS_PLL_SSC_DIG_EDP2_REG_EN_PI_DEBUG_EDP_src(data)                           ((0x00000004&(data))>>2)
#define SYS_PLL_SSC_DIG_EDP2_get_REG_EN_PI_DEBUG_EDP(data)                           ((0x00000004&(data))>>2)


#define SYS_PLL_SSC_DIG_EDP3                                                         0x980005EC
#define SYS_PLL_SSC_DIG_EDP3_reg_addr                                                "0x980005EC"
#define SYS_PLL_SSC_DIG_EDP3_reg                                                     0x980005EC
#define set_SYS_PLL_SSC_DIG_EDP3_reg(data)   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_EDP3_reg)=data)
#define get_SYS_PLL_SSC_DIG_EDP3_reg   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_EDP3_reg))
#define SYS_PLL_SSC_DIG_EDP3_inst_adr                                                "0x007B"
#define SYS_PLL_SSC_DIG_EDP3_inst                                                    0x007B
#define SYS_PLL_SSC_DIG_EDP3_NCODE_SSC_EDP_shift                                     (11)
#define SYS_PLL_SSC_DIG_EDP3_NCODE_SSC_EDP_mask                                      (0x0007F800)
#define SYS_PLL_SSC_DIG_EDP3_NCODE_SSC_EDP(data)                                     (0x0007F800&((data)<<11))
#define SYS_PLL_SSC_DIG_EDP3_NCODE_SSC_EDP_src(data)                                 ((0x0007F800&(data))>>11)
#define SYS_PLL_SSC_DIG_EDP3_get_NCODE_SSC_EDP(data)                                 ((0x0007F800&(data))>>11)
#define SYS_PLL_SSC_DIG_EDP3_FCODE_SSC_EDP_shift                                     (0)
#define SYS_PLL_SSC_DIG_EDP3_FCODE_SSC_EDP_mask                                      (0x000007FF)
#define SYS_PLL_SSC_DIG_EDP3_FCODE_SSC_EDP(data)                                     (0x000007FF&((data)<<0))
#define SYS_PLL_SSC_DIG_EDP3_FCODE_SSC_EDP_src(data)                                 ((0x000007FF&(data))>>0)
#define SYS_PLL_SSC_DIG_EDP3_get_FCODE_SSC_EDP(data)                                 ((0x000007FF&(data))>>0)


#define SYS_PLL_SSC_DIG_EDP4                                                         0x980005F0
#define SYS_PLL_SSC_DIG_EDP4_reg_addr                                                "0x980005F0"
#define SYS_PLL_SSC_DIG_EDP4_reg                                                     0x980005F0
#define set_SYS_PLL_SSC_DIG_EDP4_reg(data)   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_EDP4_reg)=data)
#define get_SYS_PLL_SSC_DIG_EDP4_reg   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_EDP4_reg))
#define SYS_PLL_SSC_DIG_EDP4_inst_adr                                                "0x007C"
#define SYS_PLL_SSC_DIG_EDP4_inst                                                    0x007C
#define SYS_PLL_SSC_DIG_EDP4_GRAN_EST_EDP_shift                                      (0)
#define SYS_PLL_SSC_DIG_EDP4_GRAN_EST_EDP_mask                                       (0x0007FFFF)
#define SYS_PLL_SSC_DIG_EDP4_GRAN_EST_EDP(data)                                      (0x0007FFFF&((data)<<0))
#define SYS_PLL_SSC_DIG_EDP4_GRAN_EST_EDP_src(data)                                  ((0x0007FFFF&(data))>>0)
#define SYS_PLL_SSC_DIG_EDP4_get_GRAN_EST_EDP(data)                                  ((0x0007FFFF&(data))>>0)


#define SYS_PLL_SSC_DIG_EDP5                                                         0x980005F4
#define SYS_PLL_SSC_DIG_EDP5_reg_addr                                                "0x980005F4"
#define SYS_PLL_SSC_DIG_EDP5_reg                                                     0x980005F4
#define set_SYS_PLL_SSC_DIG_EDP5_reg(data)   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_EDP5_reg)=data)
#define get_SYS_PLL_SSC_DIG_EDP5_reg   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_EDP5_reg))
#define SYS_PLL_SSC_DIG_EDP5_inst_adr                                                "0x007D"
#define SYS_PLL_SSC_DIG_EDP5_inst                                                    0x007D
#define SYS_PLL_SSC_DIG_EDP5_FCW_SSC_DEFAULT_EDP_shift                               (0)
#define SYS_PLL_SSC_DIG_EDP5_FCW_SSC_DEFAULT_EDP_mask                                (0x0007FFFF)
#define SYS_PLL_SSC_DIG_EDP5_FCW_SSC_DEFAULT_EDP(data)                               (0x0007FFFF&((data)<<0))
#define SYS_PLL_SSC_DIG_EDP5_FCW_SSC_DEFAULT_EDP_src(data)                           ((0x0007FFFF&(data))>>0)
#define SYS_PLL_SSC_DIG_EDP5_get_FCW_SSC_DEFAULT_EDP(data)                           ((0x0007FFFF&(data))>>0)


#define SYS_PLL_SSC_DIG_EDP_DBG1                                                     0x980005F8
#define SYS_PLL_SSC_DIG_EDP_DBG1_reg_addr                                            "0x980005F8"
#define SYS_PLL_SSC_DIG_EDP_DBG1_reg                                                 0x980005F8
#define set_SYS_PLL_SSC_DIG_EDP_DBG1_reg(data)   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_EDP_DBG1_reg)=data)
#define get_SYS_PLL_SSC_DIG_EDP_DBG1_reg   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_EDP_DBG1_reg))
#define SYS_PLL_SSC_DIG_EDP_DBG1_inst_adr                                            "0x007E"
#define SYS_PLL_SSC_DIG_EDP_DBG1_inst                                                0x007E
#define SYS_PLL_SSC_DIG_EDP_DBG1_LOOP_PI_ISEL_EDP_shift                              (14)
#define SYS_PLL_SSC_DIG_EDP_DBG1_LOOP_PI_ISEL_EDP_mask                               (0x0000C000)
#define SYS_PLL_SSC_DIG_EDP_DBG1_LOOP_PI_ISEL_EDP(data)                              (0x0000C000&((data)<<14))
#define SYS_PLL_SSC_DIG_EDP_DBG1_LOOP_PI_ISEL_EDP_src(data)                          ((0x0000C000&(data))>>14)
#define SYS_PLL_SSC_DIG_EDP_DBG1_get_LOOP_PI_ISEL_EDP(data)                          ((0x0000C000&(data))>>14)
#define SYS_PLL_SSC_DIG_EDP_DBG1_PHSEL_EDP_shift                                     (8)
#define SYS_PLL_SSC_DIG_EDP_DBG1_PHSEL_EDP_mask                                      (0x00003F00)
#define SYS_PLL_SSC_DIG_EDP_DBG1_PHSEL_EDP(data)                                     (0x00003F00&((data)<<8))
#define SYS_PLL_SSC_DIG_EDP_DBG1_PHSEL_EDP_src(data)                                 ((0x00003F00&(data))>>8)
#define SYS_PLL_SSC_DIG_EDP_DBG1_get_PHSEL_EDP(data)                                 ((0x00003F00&(data))>>8)
#define SYS_PLL_SSC_DIG_EDP_DBG1_DIVN_EDP_shift                                      (0)
#define SYS_PLL_SSC_DIG_EDP_DBG1_DIVN_EDP_mask                                       (0x000000FF)
#define SYS_PLL_SSC_DIG_EDP_DBG1_DIVN_EDP(data)                                      (0x000000FF&((data)<<0))
#define SYS_PLL_SSC_DIG_EDP_DBG1_DIVN_EDP_src(data)                                  ((0x000000FF&(data))>>0)
#define SYS_PLL_SSC_DIG_EDP_DBG1_get_DIVN_EDP(data)                                  ((0x000000FF&(data))>>0)


#define SYS_PLL_SSC_DIG_EDP_DBG2                                                     0x980005FC
#define SYS_PLL_SSC_DIG_EDP_DBG2_reg_addr                                            "0x980005FC"
#define SYS_PLL_SSC_DIG_EDP_DBG2_reg                                                 0x980005FC
#define set_SYS_PLL_SSC_DIG_EDP_DBG2_reg(data)   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_EDP_DBG2_reg)=data)
#define get_SYS_PLL_SSC_DIG_EDP_DBG2_reg   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_EDP_DBG2_reg))
#define SYS_PLL_SSC_DIG_EDP_DBG2_inst_adr                                            "0x007F"
#define SYS_PLL_SSC_DIG_EDP_DBG2_inst                                                0x007F
#define SYS_PLL_SSC_DIG_EDP_DBG2_load_FCW_EDP_shift                                  (21)
#define SYS_PLL_SSC_DIG_EDP_DBG2_load_FCW_EDP_mask                                   (0x00200000)
#define SYS_PLL_SSC_DIG_EDP_DBG2_load_FCW_EDP(data)                                  (0x00200000&((data)<<21))
#define SYS_PLL_SSC_DIG_EDP_DBG2_load_FCW_EDP_src(data)                              ((0x00200000&(data))>>21)
#define SYS_PLL_SSC_DIG_EDP_DBG2_get_load_FCW_EDP(data)                              ((0x00200000&(data))>>21)
#define SYS_PLL_SSC_DIG_EDP_DBG2_OC_DONE_EDP_shift                                   (20)
#define SYS_PLL_SSC_DIG_EDP_DBG2_OC_DONE_EDP_mask                                    (0x00100000)
#define SYS_PLL_SSC_DIG_EDP_DBG2_OC_DONE_EDP(data)                                   (0x00100000&((data)<<20))
#define SYS_PLL_SSC_DIG_EDP_DBG2_OC_DONE_EDP_src(data)                               ((0x00100000&(data))>>20)
#define SYS_PLL_SSC_DIG_EDP_DBG2_get_OC_DONE_EDP(data)                               ((0x00100000&(data))>>20)
#define SYS_PLL_SSC_DIG_EDP_DBG2_FMOD_EDP_shift                                      (19)
#define SYS_PLL_SSC_DIG_EDP_DBG2_FMOD_EDP_mask                                       (0x00080000)
#define SYS_PLL_SSC_DIG_EDP_DBG2_FMOD_EDP(data)                                      (0x00080000&((data)<<19))
#define SYS_PLL_SSC_DIG_EDP_DBG2_FMOD_EDP_src(data)                                  ((0x00080000&(data))>>19)
#define SYS_PLL_SSC_DIG_EDP_DBG2_get_FMOD_EDP(data)                                  ((0x00080000&(data))>>19)
#define SYS_PLL_SSC_DIG_EDP_DBG2_NCODE_DEBUG_EDP_shift                               (11)
#define SYS_PLL_SSC_DIG_EDP_DBG2_NCODE_DEBUG_EDP_mask                                (0x0007F800)
#define SYS_PLL_SSC_DIG_EDP_DBG2_NCODE_DEBUG_EDP(data)                               (0x0007F800&((data)<<11))
#define SYS_PLL_SSC_DIG_EDP_DBG2_NCODE_DEBUG_EDP_src(data)                           ((0x0007F800&(data))>>11)
#define SYS_PLL_SSC_DIG_EDP_DBG2_get_NCODE_DEBUG_EDP(data)                           ((0x0007F800&(data))>>11)
#define SYS_PLL_SSC_DIG_EDP_DBG2_FCODE_DEBUG_EDP_shift                               (0)
#define SYS_PLL_SSC_DIG_EDP_DBG2_FCODE_DEBUG_EDP_mask                                (0x000007FF)
#define SYS_PLL_SSC_DIG_EDP_DBG2_FCODE_DEBUG_EDP(data)                               (0x000007FF&((data)<<0))
#define SYS_PLL_SSC_DIG_EDP_DBG2_FCODE_DEBUG_EDP_src(data)                           ((0x000007FF&(data))>>0)
#define SYS_PLL_SSC_DIG_EDP_DBG2_get_FCODE_DEBUG_EDP(data)                           ((0x000007FF&(data))>>0)


#define SYS_PLL_SSC_DIG_PIXEL0                                                       0x98000600
#define SYS_PLL_SSC_DIG_PIXEL0_reg_addr                                              "0x98000600"
#define SYS_PLL_SSC_DIG_PIXEL0_reg                                                   0x98000600
#define set_SYS_PLL_SSC_DIG_PIXEL0_reg(data)   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_PIXEL0_reg)=data)
#define get_SYS_PLL_SSC_DIG_PIXEL0_reg   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_PIXEL0_reg))
#define SYS_PLL_SSC_DIG_PIXEL0_inst_adr                                              "0x0080"
#define SYS_PLL_SSC_DIG_PIXEL0_inst                                                  0x0080
#define SYS_PLL_SSC_DIG_PIXEL0_REG_CKSSC_INV_PIXEL_shift                             (4)
#define SYS_PLL_SSC_DIG_PIXEL0_REG_CKSSC_INV_PIXEL_mask                              (0x00000010)
#define SYS_PLL_SSC_DIG_PIXEL0_REG_CKSSC_INV_PIXEL(data)                             (0x00000010&((data)<<4))
#define SYS_PLL_SSC_DIG_PIXEL0_REG_CKSSC_INV_PIXEL_src(data)                         ((0x00000010&(data))>>4)
#define SYS_PLL_SSC_DIG_PIXEL0_get_REG_CKSSC_INV_PIXEL(data)                         ((0x00000010&(data))>>4)
#define SYS_PLL_SSC_DIG_PIXEL0_REG_GRAN_AUTO_RST_PIXEL_shift                         (3)
#define SYS_PLL_SSC_DIG_PIXEL0_REG_GRAN_AUTO_RST_PIXEL_mask                          (0x00000008)
#define SYS_PLL_SSC_DIG_PIXEL0_REG_GRAN_AUTO_RST_PIXEL(data)                         (0x00000008&((data)<<3))
#define SYS_PLL_SSC_DIG_PIXEL0_REG_GRAN_AUTO_RST_PIXEL_src(data)                     ((0x00000008&(data))>>3)
#define SYS_PLL_SSC_DIG_PIXEL0_get_REG_GRAN_AUTO_RST_PIXEL(data)                     ((0x00000008&(data))>>3)
#define SYS_PLL_SSC_DIG_PIXEL0_RSTB_PIXEL_shift                                      (2)
#define SYS_PLL_SSC_DIG_PIXEL0_RSTB_PIXEL_mask                                       (0x00000004)
#define SYS_PLL_SSC_DIG_PIXEL0_RSTB_PIXEL(data)                                      (0x00000004&((data)<<2))
#define SYS_PLL_SSC_DIG_PIXEL0_RSTB_PIXEL_src(data)                                  ((0x00000004&(data))>>2)
#define SYS_PLL_SSC_DIG_PIXEL0_get_RSTB_PIXEL(data)                                  ((0x00000004&(data))>>2)
#define SYS_PLL_SSC_DIG_PIXEL0_EN_SSC_PIXEL_shift                                    (1)
#define SYS_PLL_SSC_DIG_PIXEL0_EN_SSC_PIXEL_mask                                     (0x00000002)
#define SYS_PLL_SSC_DIG_PIXEL0_EN_SSC_PIXEL(data)                                    (0x00000002&((data)<<1))
#define SYS_PLL_SSC_DIG_PIXEL0_EN_SSC_PIXEL_src(data)                                ((0x00000002&(data))>>1)
#define SYS_PLL_SSC_DIG_PIXEL0_get_EN_SSC_PIXEL(data)                                ((0x00000002&(data))>>1)
#define SYS_PLL_SSC_DIG_PIXEL0_OC_EN_PIXEL_shift                                     (0)
#define SYS_PLL_SSC_DIG_PIXEL0_OC_EN_PIXEL_mask                                      (0x00000001)
#define SYS_PLL_SSC_DIG_PIXEL0_OC_EN_PIXEL(data)                                     (0x00000001&((data)<<0))
#define SYS_PLL_SSC_DIG_PIXEL0_OC_EN_PIXEL_src(data)                                 ((0x00000001&(data))>>0)
#define SYS_PLL_SSC_DIG_PIXEL0_get_OC_EN_PIXEL(data)                                 ((0x00000001&(data))>>0)


#define SYS_PLL_SSC_DIG_PIXEL1                                                       0x98000604
#define SYS_PLL_SSC_DIG_PIXEL1_reg_addr                                              "0x98000604"
#define SYS_PLL_SSC_DIG_PIXEL1_reg                                                   0x98000604
#define set_SYS_PLL_SSC_DIG_PIXEL1_reg(data)   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_PIXEL1_reg)=data)
#define get_SYS_PLL_SSC_DIG_PIXEL1_reg   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_PIXEL1_reg))
#define SYS_PLL_SSC_DIG_PIXEL1_inst_adr                                              "0x0081"
#define SYS_PLL_SSC_DIG_PIXEL1_inst                                                  0x0081
#define SYS_PLL_SSC_DIG_PIXEL1_NCODE_T_PIXEL_shift                                   (11)
#define SYS_PLL_SSC_DIG_PIXEL1_NCODE_T_PIXEL_mask                                    (0x0007F800)
#define SYS_PLL_SSC_DIG_PIXEL1_NCODE_T_PIXEL(data)                                   (0x0007F800&((data)<<11))
#define SYS_PLL_SSC_DIG_PIXEL1_NCODE_T_PIXEL_src(data)                               ((0x0007F800&(data))>>11)
#define SYS_PLL_SSC_DIG_PIXEL1_get_NCODE_T_PIXEL(data)                               ((0x0007F800&(data))>>11)
#define SYS_PLL_SSC_DIG_PIXEL1_FCODE_T_PIXEL_shift                                   (0)
#define SYS_PLL_SSC_DIG_PIXEL1_FCODE_T_PIXEL_mask                                    (0x000007FF)
#define SYS_PLL_SSC_DIG_PIXEL1_FCODE_T_PIXEL(data)                                   (0x000007FF&((data)<<0))
#define SYS_PLL_SSC_DIG_PIXEL1_FCODE_T_PIXEL_src(data)                               ((0x000007FF&(data))>>0)
#define SYS_PLL_SSC_DIG_PIXEL1_get_FCODE_T_PIXEL(data)                               ((0x000007FF&(data))>>0)


#define SYS_PLL_SSC_DIG_PIXEL2                                                       0x98000608
#define SYS_PLL_SSC_DIG_PIXEL2_reg_addr                                              "0x98000608"
#define SYS_PLL_SSC_DIG_PIXEL2_reg                                                   0x98000608
#define set_SYS_PLL_SSC_DIG_PIXEL2_reg(data)   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_PIXEL2_reg)=data)
#define get_SYS_PLL_SSC_DIG_PIXEL2_reg   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_PIXEL2_reg))
#define SYS_PLL_SSC_DIG_PIXEL2_inst_adr                                              "0x0082"
#define SYS_PLL_SSC_DIG_PIXEL2_inst                                                  0x0082
#define SYS_PLL_SSC_DIG_PIXEL2_REG_BYPASS_DIVN_shift                                 (27)
#define SYS_PLL_SSC_DIG_PIXEL2_REG_BYPASS_DIVN_mask                                  (0x08000000)
#define SYS_PLL_SSC_DIG_PIXEL2_REG_BYPASS_DIVN(data)                                 (0x08000000&((data)<<27))
#define SYS_PLL_SSC_DIG_PIXEL2_REG_BYPASS_DIVN_src(data)                             ((0x08000000&(data))>>27)
#define SYS_PLL_SSC_DIG_PIXEL2_get_REG_BYPASS_DIVN(data)                             ((0x08000000&(data))>>27)
#define SYS_PLL_SSC_DIG_PIXEL2_REG_OC_STEP_SET_PIXEL_shift                           (17)
#define SYS_PLL_SSC_DIG_PIXEL2_REG_OC_STEP_SET_PIXEL_mask                            (0x07FE0000)
#define SYS_PLL_SSC_DIG_PIXEL2_REG_OC_STEP_SET_PIXEL(data)                           (0x07FE0000&((data)<<17))
#define SYS_PLL_SSC_DIG_PIXEL2_REG_OC_STEP_SET_PIXEL_src(data)                       ((0x07FE0000&(data))>>17)
#define SYS_PLL_SSC_DIG_PIXEL2_get_REG_OC_STEP_SET_PIXEL(data)                       ((0x07FE0000&(data))>>17)
#define SYS_PLL_SSC_DIG_PIXEL2_REG_SEL_OC_MODE_PIXEL_shift                           (15)
#define SYS_PLL_SSC_DIG_PIXEL2_REG_SEL_OC_MODE_PIXEL_mask                            (0x00018000)
#define SYS_PLL_SSC_DIG_PIXEL2_REG_SEL_OC_MODE_PIXEL(data)                           (0x00018000&((data)<<15))
#define SYS_PLL_SSC_DIG_PIXEL2_REG_SEL_OC_MODE_PIXEL_src(data)                       ((0x00018000&(data))>>15)
#define SYS_PLL_SSC_DIG_PIXEL2_get_REG_SEL_OC_MODE_PIXEL(data)                       ((0x00018000&(data))>>15)
#define SYS_PLL_SSC_DIG_PIXEL2_REG_HS_OC_STOP_DIFF_PIXEL_shift                       (13)
#define SYS_PLL_SSC_DIG_PIXEL2_REG_HS_OC_STOP_DIFF_PIXEL_mask                        (0x00006000)
#define SYS_PLL_SSC_DIG_PIXEL2_REG_HS_OC_STOP_DIFF_PIXEL(data)                       (0x00006000&((data)<<13))
#define SYS_PLL_SSC_DIG_PIXEL2_REG_HS_OC_STOP_DIFF_PIXEL_src(data)                   ((0x00006000&(data))>>13)
#define SYS_PLL_SSC_DIG_PIXEL2_get_REG_HS_OC_STOP_DIFF_PIXEL(data)                   ((0x00006000&(data))>>13)
#define SYS_PLL_SSC_DIG_PIXEL2_REG_OC_DONE_DELAY_PIXEL_shift                         (7)
#define SYS_PLL_SSC_DIG_PIXEL2_REG_OC_DONE_DELAY_PIXEL_mask                          (0x00001F80)
#define SYS_PLL_SSC_DIG_PIXEL2_REG_OC_DONE_DELAY_PIXEL(data)                         (0x00001F80&((data)<<7))
#define SYS_PLL_SSC_DIG_PIXEL2_REG_OC_DONE_DELAY_PIXEL_src(data)                     ((0x00001F80&(data))>>7)
#define SYS_PLL_SSC_DIG_PIXEL2_get_REG_OC_DONE_DELAY_PIXEL(data)                     ((0x00001F80&(data))>>7)
#define SYS_PLL_SSC_DIG_PIXEL2_REG_PI_CUR_SEL_PIXEL_shift                            (5)
#define SYS_PLL_SSC_DIG_PIXEL2_REG_PI_CUR_SEL_PIXEL_mask                             (0x00000060)
#define SYS_PLL_SSC_DIG_PIXEL2_REG_PI_CUR_SEL_PIXEL(data)                            (0x00000060&((data)<<5))
#define SYS_PLL_SSC_DIG_PIXEL2_REG_PI_CUR_SEL_PIXEL_src(data)                        ((0x00000060&(data))>>5)
#define SYS_PLL_SSC_DIG_PIXEL2_get_REG_PI_CUR_SEL_PIXEL(data)                        ((0x00000060&(data))>>5)
#define SYS_PLL_SSC_DIG_PIXEL2_REG_BYPASS_PI_PIXEL_shift                             (4)
#define SYS_PLL_SSC_DIG_PIXEL2_REG_BYPASS_PI_PIXEL_mask                              (0x00000010)
#define SYS_PLL_SSC_DIG_PIXEL2_REG_BYPASS_PI_PIXEL(data)                             (0x00000010&((data)<<4))
#define SYS_PLL_SSC_DIG_PIXEL2_REG_BYPASS_PI_PIXEL_src(data)                         ((0x00000010&(data))>>4)
#define SYS_PLL_SSC_DIG_PIXEL2_get_REG_BYPASS_PI_PIXEL(data)                         ((0x00000010&(data))>>4)
#define SYS_PLL_SSC_DIG_PIXEL2_REG_SDM_ORDER_PIXEL_shift                             (3)
#define SYS_PLL_SSC_DIG_PIXEL2_REG_SDM_ORDER_PIXEL_mask                              (0x00000008)
#define SYS_PLL_SSC_DIG_PIXEL2_REG_SDM_ORDER_PIXEL(data)                             (0x00000008&((data)<<3))
#define SYS_PLL_SSC_DIG_PIXEL2_REG_SDM_ORDER_PIXEL_src(data)                         ((0x00000008&(data))>>3)
#define SYS_PLL_SSC_DIG_PIXEL2_get_REG_SDM_ORDER_PIXEL(data)                         ((0x00000008&(data))>>3)
#define SYS_PLL_SSC_DIG_PIXEL2_REG_EN_PI_DEBUG_PIXEL_shift                           (2)
#define SYS_PLL_SSC_DIG_PIXEL2_REG_EN_PI_DEBUG_PIXEL_mask                            (0x00000004)
#define SYS_PLL_SSC_DIG_PIXEL2_REG_EN_PI_DEBUG_PIXEL(data)                           (0x00000004&((data)<<2))
#define SYS_PLL_SSC_DIG_PIXEL2_REG_EN_PI_DEBUG_PIXEL_src(data)                       ((0x00000004&(data))>>2)
#define SYS_PLL_SSC_DIG_PIXEL2_get_REG_EN_PI_DEBUG_PIXEL(data)                       ((0x00000004&(data))>>2)


#define SYS_PLL_SSC_DIG_PIXEL3                                                       0x9800060C
#define SYS_PLL_SSC_DIG_PIXEL3_reg_addr                                              "0x9800060C"
#define SYS_PLL_SSC_DIG_PIXEL3_reg                                                   0x9800060C
#define set_SYS_PLL_SSC_DIG_PIXEL3_reg(data)   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_PIXEL3_reg)=data)
#define get_SYS_PLL_SSC_DIG_PIXEL3_reg   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_PIXEL3_reg))
#define SYS_PLL_SSC_DIG_PIXEL3_inst_adr                                              "0x0083"
#define SYS_PLL_SSC_DIG_PIXEL3_inst                                                  0x0083
#define SYS_PLL_SSC_DIG_PIXEL3_NCODE_SSC_PIXEL_shift                                 (11)
#define SYS_PLL_SSC_DIG_PIXEL3_NCODE_SSC_PIXEL_mask                                  (0x0007F800)
#define SYS_PLL_SSC_DIG_PIXEL3_NCODE_SSC_PIXEL(data)                                 (0x0007F800&((data)<<11))
#define SYS_PLL_SSC_DIG_PIXEL3_NCODE_SSC_PIXEL_src(data)                             ((0x0007F800&(data))>>11)
#define SYS_PLL_SSC_DIG_PIXEL3_get_NCODE_SSC_PIXEL(data)                             ((0x0007F800&(data))>>11)
#define SYS_PLL_SSC_DIG_PIXEL3_FCODE_SSC_PIXEL_shift                                 (0)
#define SYS_PLL_SSC_DIG_PIXEL3_FCODE_SSC_PIXEL_mask                                  (0x000007FF)
#define SYS_PLL_SSC_DIG_PIXEL3_FCODE_SSC_PIXEL(data)                                 (0x000007FF&((data)<<0))
#define SYS_PLL_SSC_DIG_PIXEL3_FCODE_SSC_PIXEL_src(data)                             ((0x000007FF&(data))>>0)
#define SYS_PLL_SSC_DIG_PIXEL3_get_FCODE_SSC_PIXEL(data)                             ((0x000007FF&(data))>>0)


#define SYS_PLL_SSC_DIG_PIXEL4                                                       0x98000610
#define SYS_PLL_SSC_DIG_PIXEL4_reg_addr                                              "0x98000610"
#define SYS_PLL_SSC_DIG_PIXEL4_reg                                                   0x98000610
#define set_SYS_PLL_SSC_DIG_PIXEL4_reg(data)   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_PIXEL4_reg)=data)
#define get_SYS_PLL_SSC_DIG_PIXEL4_reg   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_PIXEL4_reg))
#define SYS_PLL_SSC_DIG_PIXEL4_inst_adr                                              "0x0084"
#define SYS_PLL_SSC_DIG_PIXEL4_inst                                                  0x0084
#define SYS_PLL_SSC_DIG_PIXEL4_GRAN_EST_PIXEL_shift                                  (0)
#define SYS_PLL_SSC_DIG_PIXEL4_GRAN_EST_PIXEL_mask                                   (0x0007FFFF)
#define SYS_PLL_SSC_DIG_PIXEL4_GRAN_EST_PIXEL(data)                                  (0x0007FFFF&((data)<<0))
#define SYS_PLL_SSC_DIG_PIXEL4_GRAN_EST_PIXEL_src(data)                              ((0x0007FFFF&(data))>>0)
#define SYS_PLL_SSC_DIG_PIXEL4_get_GRAN_EST_PIXEL(data)                              ((0x0007FFFF&(data))>>0)


#define SYS_PLL_SSC_DIG_PIXEL5                                                       0x98000614
#define SYS_PLL_SSC_DIG_PIXEL5_reg_addr                                              "0x98000614"
#define SYS_PLL_SSC_DIG_PIXEL5_reg                                                   0x98000614
#define set_SYS_PLL_SSC_DIG_PIXEL5_reg(data)   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_PIXEL5_reg)=data)
#define get_SYS_PLL_SSC_DIG_PIXEL5_reg   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_PIXEL5_reg))
#define SYS_PLL_SSC_DIG_PIXEL5_inst_adr                                              "0x0085"
#define SYS_PLL_SSC_DIG_PIXEL5_inst                                                  0x0085
#define SYS_PLL_SSC_DIG_PIXEL5_FCW_SSC_DEFAULT_PIXEL_shift                           (0)
#define SYS_PLL_SSC_DIG_PIXEL5_FCW_SSC_DEFAULT_PIXEL_mask                            (0x0007FFFF)
#define SYS_PLL_SSC_DIG_PIXEL5_FCW_SSC_DEFAULT_PIXEL(data)                           (0x0007FFFF&((data)<<0))
#define SYS_PLL_SSC_DIG_PIXEL5_FCW_SSC_DEFAULT_PIXEL_src(data)                       ((0x0007FFFF&(data))>>0)
#define SYS_PLL_SSC_DIG_PIXEL5_get_FCW_SSC_DEFAULT_PIXEL(data)                       ((0x0007FFFF&(data))>>0)


#define SYS_PLL_SSC_DIG_PIXEL_DBG1                                                   0x98000618
#define SYS_PLL_SSC_DIG_PIXEL_DBG1_reg_addr                                          "0x98000618"
#define SYS_PLL_SSC_DIG_PIXEL_DBG1_reg                                               0x98000618
#define set_SYS_PLL_SSC_DIG_PIXEL_DBG1_reg(data)   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_PIXEL_DBG1_reg)=data)
#define get_SYS_PLL_SSC_DIG_PIXEL_DBG1_reg   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_PIXEL_DBG1_reg))
#define SYS_PLL_SSC_DIG_PIXEL_DBG1_inst_adr                                          "0x0086"
#define SYS_PLL_SSC_DIG_PIXEL_DBG1_inst                                              0x0086
#define SYS_PLL_SSC_DIG_PIXEL_DBG1_LOOP_PI_ISEL_PIXEL_shift                          (14)
#define SYS_PLL_SSC_DIG_PIXEL_DBG1_LOOP_PI_ISEL_PIXEL_mask                           (0x0000C000)
#define SYS_PLL_SSC_DIG_PIXEL_DBG1_LOOP_PI_ISEL_PIXEL(data)                          (0x0000C000&((data)<<14))
#define SYS_PLL_SSC_DIG_PIXEL_DBG1_LOOP_PI_ISEL_PIXEL_src(data)                      ((0x0000C000&(data))>>14)
#define SYS_PLL_SSC_DIG_PIXEL_DBG1_get_LOOP_PI_ISEL_PIXEL(data)                      ((0x0000C000&(data))>>14)
#define SYS_PLL_SSC_DIG_PIXEL_DBG1_PHSEL_PIXEL_shift                                 (8)
#define SYS_PLL_SSC_DIG_PIXEL_DBG1_PHSEL_PIXEL_mask                                  (0x00003F00)
#define SYS_PLL_SSC_DIG_PIXEL_DBG1_PHSEL_PIXEL(data)                                 (0x00003F00&((data)<<8))
#define SYS_PLL_SSC_DIG_PIXEL_DBG1_PHSEL_PIXEL_src(data)                             ((0x00003F00&(data))>>8)
#define SYS_PLL_SSC_DIG_PIXEL_DBG1_get_PHSEL_PIXEL(data)                             ((0x00003F00&(data))>>8)
#define SYS_PLL_SSC_DIG_PIXEL_DBG1_DIVN_PIXEL_shift                                  (0)
#define SYS_PLL_SSC_DIG_PIXEL_DBG1_DIVN_PIXEL_mask                                   (0x000000FF)
#define SYS_PLL_SSC_DIG_PIXEL_DBG1_DIVN_PIXEL(data)                                  (0x000000FF&((data)<<0))
#define SYS_PLL_SSC_DIG_PIXEL_DBG1_DIVN_PIXEL_src(data)                              ((0x000000FF&(data))>>0)
#define SYS_PLL_SSC_DIG_PIXEL_DBG1_get_DIVN_PIXEL(data)                              ((0x000000FF&(data))>>0)


#define SYS_PLL_SSC_DIG_PIXEL_DBG2                                                   0x9800061C
#define SYS_PLL_SSC_DIG_PIXEL_DBG2_reg_addr                                          "0x9800061C"
#define SYS_PLL_SSC_DIG_PIXEL_DBG2_reg                                               0x9800061C
#define set_SYS_PLL_SSC_DIG_PIXEL_DBG2_reg(data)   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_PIXEL_DBG2_reg)=data)
#define get_SYS_PLL_SSC_DIG_PIXEL_DBG2_reg   (*((volatile unsigned int*) SYS_PLL_SSC_DIG_PIXEL_DBG2_reg))
#define SYS_PLL_SSC_DIG_PIXEL_DBG2_inst_adr                                          "0x0087"
#define SYS_PLL_SSC_DIG_PIXEL_DBG2_inst                                              0x0087
#define SYS_PLL_SSC_DIG_PIXEL_DBG2_load_FCW_PIXEL_shift                              (21)
#define SYS_PLL_SSC_DIG_PIXEL_DBG2_load_FCW_PIXEL_mask                               (0x00200000)
#define SYS_PLL_SSC_DIG_PIXEL_DBG2_load_FCW_PIXEL(data)                              (0x00200000&((data)<<21))
#define SYS_PLL_SSC_DIG_PIXEL_DBG2_load_FCW_PIXEL_src(data)                          ((0x00200000&(data))>>21)
#define SYS_PLL_SSC_DIG_PIXEL_DBG2_get_load_FCW_PIXEL(data)                          ((0x00200000&(data))>>21)
#define SYS_PLL_SSC_DIG_PIXEL_DBG2_OC_DONE_PIXEL_shift                               (20)
#define SYS_PLL_SSC_DIG_PIXEL_DBG2_OC_DONE_PIXEL_mask                                (0x00100000)
#define SYS_PLL_SSC_DIG_PIXEL_DBG2_OC_DONE_PIXEL(data)                               (0x00100000&((data)<<20))
#define SYS_PLL_SSC_DIG_PIXEL_DBG2_OC_DONE_PIXEL_src(data)                           ((0x00100000&(data))>>20)
#define SYS_PLL_SSC_DIG_PIXEL_DBG2_get_OC_DONE_PIXEL(data)                           ((0x00100000&(data))>>20)
#define SYS_PLL_SSC_DIG_PIXEL_DBG2_FMOD_PIXEL_shift                                  (19)
#define SYS_PLL_SSC_DIG_PIXEL_DBG2_FMOD_PIXEL_mask                                   (0x00080000)
#define SYS_PLL_SSC_DIG_PIXEL_DBG2_FMOD_PIXEL(data)                                  (0x00080000&((data)<<19))
#define SYS_PLL_SSC_DIG_PIXEL_DBG2_FMOD_PIXEL_src(data)                              ((0x00080000&(data))>>19)
#define SYS_PLL_SSC_DIG_PIXEL_DBG2_get_FMOD_PIXEL(data)                              ((0x00080000&(data))>>19)
#define SYS_PLL_SSC_DIG_PIXEL_DBG2_NCODE_DEBUG_PIXEL_shift                           (11)
#define SYS_PLL_SSC_DIG_PIXEL_DBG2_NCODE_DEBUG_PIXEL_mask                            (0x0007F800)
#define SYS_PLL_SSC_DIG_PIXEL_DBG2_NCODE_DEBUG_PIXEL(data)                           (0x0007F800&((data)<<11))
#define SYS_PLL_SSC_DIG_PIXEL_DBG2_NCODE_DEBUG_PIXEL_src(data)                       ((0x0007F800&(data))>>11)
#define SYS_PLL_SSC_DIG_PIXEL_DBG2_get_NCODE_DEBUG_PIXEL(data)                       ((0x0007F800&(data))>>11)
#define SYS_PLL_SSC_DIG_PIXEL_DBG2_FCODE_DEBUG_PIXEL_shift                           (0)
#define SYS_PLL_SSC_DIG_PIXEL_DBG2_FCODE_DEBUG_PIXEL_mask                            (0x000007FF)
#define SYS_PLL_SSC_DIG_PIXEL_DBG2_FCODE_DEBUG_PIXEL(data)                           (0x000007FF&((data)<<0))
#define SYS_PLL_SSC_DIG_PIXEL_DBG2_FCODE_DEBUG_PIXEL_src(data)                       ((0x000007FF&(data))>>0)
#define SYS_PLL_SSC_DIG_PIXEL_DBG2_get_FCODE_DEBUG_PIXEL(data)                       ((0x000007FF&(data))>>0)


#define SYS_PLL_HDMI_SD6                                                             0x98000620
#define SYS_PLL_HDMI_SD6_reg_addr                                                    "0x98000620"
#define SYS_PLL_HDMI_SD6_reg                                                         0x98000620
#define set_SYS_PLL_HDMI_SD6_reg(data)   (*((volatile unsigned int*) SYS_PLL_HDMI_SD6_reg)=data)
#define get_SYS_PLL_HDMI_SD6_reg   (*((volatile unsigned int*) SYS_PLL_HDMI_SD6_reg))
#define SYS_PLL_HDMI_SD6_inst_adr                                                    "0x0088"
#define SYS_PLL_HDMI_SD6_inst                                                        0x0088
#define SYS_PLL_HDMI_SD6_REG_BYPASS_DIVN_shift                                       (19)
#define SYS_PLL_HDMI_SD6_REG_BYPASS_DIVN_mask                                        (0x00080000)
#define SYS_PLL_HDMI_SD6_REG_BYPASS_DIVN(data)                                       (0x00080000&((data)<<19))
#define SYS_PLL_HDMI_SD6_REG_BYPASS_DIVN_src(data)                                   ((0x00080000&(data))>>19)
#define SYS_PLL_HDMI_SD6_get_REG_BYPASS_DIVN(data)                                   ((0x00080000&(data))>>19)
#define SYS_PLL_HDMI_SD6_FCW_SSC_DEFAULT_HDMITX_shift                                (0)
#define SYS_PLL_HDMI_SD6_FCW_SSC_DEFAULT_HDMITX_mask                                 (0x0007FFFF)
#define SYS_PLL_HDMI_SD6_FCW_SSC_DEFAULT_HDMITX(data)                                (0x0007FFFF&((data)<<0))
#define SYS_PLL_HDMI_SD6_FCW_SSC_DEFAULT_HDMITX_src(data)                            ((0x0007FFFF&(data))>>0)
#define SYS_PLL_HDMI_SD6_get_FCW_SSC_DEFAULT_HDMITX(data)                            ((0x0007FFFF&(data))>>0)


#endif
