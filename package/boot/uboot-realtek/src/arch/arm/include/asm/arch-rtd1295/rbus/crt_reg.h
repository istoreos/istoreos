/**************************************************************
// Spec Version                  : 1.0
// Parser Version                : DVR_Parser_6.11(120105)
// CModelGen Version             : 5.1 2012.01.05
// Naming Rule                   :  Register_Name
// Naming Rule                   : Module_Register_Name_reg
// Parse Option                  : Only Parse _op1
// Parse Address Region          : All Address Region 
// Decode bit number             : 12 bits
// Firmware Header Generate Date : 2013/6/18 10:2:33
***************************************************************/


#ifndef _CRT_REG_H_INCLUDED_
#define _CRT_REG_H_INCLUDED_
#ifdef  _CRT_USE_STRUCT
typedef struct 
{
unsigned int     reserved_0:1;
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
unsigned int     rstn_ve_jpeg:1;
unsigned int     rstn_ve_h264:1;
unsigned int     rstn_gpu:1;
unsigned int     rstn_aio:1;
unsigned int     rstn_etn_phy:1;
unsigned int     rstn_etn:1;
unsigned int     rstn_hdmi:1;
unsigned int     rstn_hdmirx:1;
unsigned int     rstn_cbusrx:1;
unsigned int     rstn_usb_phy1:1;
unsigned int     rstn_usb_phy0:1;
unsigned int     rstn_cbustx:1;
unsigned int     rstn_usb:1;
unsigned int     rstn_ve_h265:1;
unsigned int     reserved_1:1;
unsigned int     rstn_gspi:1;
unsigned int     reserved_2:1;
unsigned int     rstn_rng:1;
unsigned int     rstn_misc:1;
}SOFT_RESET1;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     rstn_ur0:1;
unsigned int     rstn_ur1:1;
unsigned int     rstn_i2c_0:1;
unsigned int     rstn_i2c_1:1;
unsigned int     rstn_i2c_2:1;
unsigned int     rstn_i2c_3:1;
unsigned int     rstn_i2c_4:1;
unsigned int     rstn_ir:1;
unsigned int     rstn_cec1:1;
unsigned int     rstn_rtc:1;
unsigned int     rstn_vfd:1;
unsigned int     rstn_i2c_5:1;
unsigned int     rstn_i2c_6:1;
unsigned int     rstn_cec0:1;
unsigned int     reserved_1:3;
unsigned int     rstn_sdio:1;
unsigned int     rstn_emmc:1;
unsigned int     rstn_cr:1;
unsigned int     rstn_pcr_cnt:1;
unsigned int     reserved_2:5;
unsigned int     rstn_vde:1;
unsigned int     rstn_ade:1;
unsigned int     rstn_vcpu:1;
unsigned int     rstn_acpu:1;
}SOFT_RESET2;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     rstn_sb2:1;
}SOFT_RESET3;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     clk_en_sdio:1;
unsigned int     clk_en_ve_h265:1;
unsigned int     clk_en_cbustx:1;
unsigned int     clk_en_mipi:1;
unsigned int     clk_en_oobmac:1;
unsigned int     clk_en_cr:1;
unsigned int     clk_en_emmc:1;
unsigned int     clk_en_nf:1;
unsigned int     clk_en_ae:1;
unsigned int     clk_en_tp:1;
unsigned int     clk_en_md:1;
unsigned int     clk_en_cp:1;
unsigned int     clk_en_dcu:1;
unsigned int     clk_en_se:1;
unsigned int     clk_en_lvds:1;
unsigned int     clk_en_vo:1;
unsigned int     clk_en_tve:1;
unsigned int     clk_en_ve_jpeg:1;
unsigned int     clk_en_ve_h264:1;
unsigned int     clk_en_gpu:1;
unsigned int     clk_en_aio:1;
unsigned int     clk_en_etn:1;
unsigned int     clk_en_hdmi:1;
unsigned int     clk_en_etn_250m:1;
unsigned int     clk_en_iso_misc:1;
unsigned int     clk_en_pcr:1;
unsigned int     clk_en_usb:1;
unsigned int     clk_en_gspi:1;
unsigned int     clk_en_cbusrx:1;
unsigned int     clk_en_hdmirx:1;
unsigned int     clk_en_misc:1;
}CLOCK_ENABLE1;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     clk_en_ur0:1;
unsigned int     clk_en_ur1:1;
unsigned int     reserved_1:3;
unsigned int     clk_en_misc_i2c_0:1;
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
unsigned int     clk_en_misc_ir:1;
unsigned int     clk_en_misc_cec1:1;
unsigned int     clk_en_misc_rtc:1;
unsigned int     clk_en_misc_vfd:1;
unsigned int     clk_en_misc_cec0:1;
unsigned int     clk_en_vde:1;
unsigned int     clk_en_ade:1;
unsigned int     clk_en_vcpu:1;
unsigned int     clk_en_acpu:1;
unsigned int     clk_en_dp:1;
unsigned int     clk_en_scpu:1;
unsigned int     clk_en_misc_i2c_5:1;
unsigned int     clk_en_misc_i2c_6:1;
}CLOCK_ENABLE2;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     clk_en_kcpu:1;
unsigned int     clk_en_sb2:1;
}GROUP1_CK_EN;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     voclk_sel:1;
unsigned int     sclk_sel:1;
}GROUP1_CK_SEL;

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
}TVE_CK_SEL;

typedef struct 
{
unsigned int     reserved_0:20;
unsigned int     write_en2:1;
unsigned int     dac2_div:5;
unsigned int     write_en1:1;
unsigned int     dac1_div:5;
}DISP_PLL_DIV;

typedef struct 
{
unsigned int     reserved_0:7;
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
}DISP_PLL_DIV2;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     dds_clk_sel:1;
}DDS_VIDEO_CK_SEL;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     audio_use_sysclk:1;
}AUDIO_CLK_CTL;

typedef struct 
{
unsigned int     reserved_0:23;
unsigned int     scpu_freq_sel:2;
unsigned int     vcpu_freq_sel:2;
unsigned int     acpu_freq_sel:2;
unsigned int     ddr_freq_sel:2;
unsigned int     bus_freq_sel:1;
}PLL_DIV;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clk_sel:1;
}DCPHY_CKSEL;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     nf_div:3;
}NF_CKSEL;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     nds_sc_div:3;
}NDS_SC_CKSEL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     write_en2:1;
unsigned int     emmc_div:3;
unsigned int     write_en1:1;
unsigned int     cr_div:3;
}CR_CKSEL;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     clk_camera1_sel:2;
unsigned int     clk_camera0_sel:2;
}MISC_CKSEL;

typedef struct 
{
unsigned int     bus_ssc_sse:1;
unsigned int     bus_ssc_ckinv:1;
unsigned int     bus_ssc_sss:6;
unsigned int     reserved_0:1;
unsigned int     bus_ssc_ssn:7;
unsigned int     bus_ssc_ssfpv:8;
unsigned int     reserved_1:6;
unsigned int     bus_ssc_stms:2;
}BUS_PLL_SSC;

typedef struct 
{
unsigned int     reserved_0:3;
unsigned int     SSCDDR_SEL_ORDER:1;
unsigned int     SSCDDR_WEIGHTING_SEL:3;
unsigned int     SSCDDR_STEP_IN:13;
unsigned int     SSCDDR_TBASE:12;
}PLL_DDR_SSC2;

typedef struct 
{
unsigned int     dcsb_ssc_sse:1;
unsigned int     dcsb_ssc_ckinv:1;
unsigned int     dcsb_ssc_sss:6;
unsigned int     reserved_0:1;
unsigned int     dcsb_ssc_ssn:7;
unsigned int     dcsb_ssc_ssfpv:8;
unsigned int     reserved_1:6;
unsigned int     dcsb_ssc_stms:2;
}DCSB_PLL_SSC;

typedef struct 
{
unsigned int     lvds_ssc_sse:1;
unsigned int     lvds_ssc_ckinv:1;
unsigned int     lvds_ssc_sss:6;
unsigned int     reserved_0:1;
unsigned int     lvds_ssc_ssn:7;
unsigned int     lvds_ssc_ssfpv:8;
unsigned int     reserved_1:6;
unsigned int     lvds_ssc_stms:2;
}LVDS_PLL_SSC;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     mclk_sel:3;
unsigned int     fs:4;
unsigned int     clken:1;
}AIO_O_PCM_CK_CTL;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     fs:4;
unsigned int     clken:1;
}AIO_O_RAW_CK_CTL;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     fs:4;
unsigned int     clken:1;
}AIO_O_RAW2_CK_CTL;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     write_en2:1;
unsigned int     dds_rstn:1;
}APS_CTL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     mclk_sel:3;
unsigned int     fs:4;
unsigned int     clken:1;
}AIO_I_PCM_CK_CTL;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     CLK_VO_SEL:1;
}CLK_VO_CTRL;

typedef struct 
{
unsigned int     REG_PLLSCPU_RS:3;
unsigned int     REG_PLLSCPU_LDO_VSEL:2;
unsigned int     REG_PLLSCPU_CP:1;
unsigned int     REG_PLLSCPU_DBUG_EN:1;
unsigned int     REG_PLLSCPU_CPMODE:1;
unsigned int     REG_PLLSCPU_HIGH_KVCO:1;
unsigned int     REG_PLLSCPU_RESERVE:1;
unsigned int     REG_PLLSCPU_CCO:1;
unsigned int     reserved_0:12;
unsigned int     PLLSCPU_N:2;
unsigned int     REG_PLLSCPU_IP:4;
unsigned int     REG_PLLSCPU_TST:1;
unsigned int     PLLSCPU_RSTB:1;
unsigned int     PLLSCPU_POW:1;
}PLL_SCPU1;

typedef struct 
{
unsigned int     reserved_0:3;
unsigned int     NCODE_T_SCPU:8;
unsigned int     FCODE_T_SCPU:11;
unsigned int     REG_OC_STEP_SET:10;
}PLL_SCPU2;

typedef struct 
{
unsigned int     reserved_0:5;
unsigned int     REG_SEL_OC_MODE:2;
unsigned int     REG_HS_OC_STOP_DIFF:2;
unsigned int     REG_OC_DONE_delay:6;
unsigned int     REG_PI_CUR_SEL:2;
unsigned int     REG_F390K:2;
unsigned int     REG_TIME0_CK:3;
unsigned int     REG_TIME_RDY_CKOUT:2;
unsigned int     REG_TIME2_RST_WIDTH:2;
unsigned int     REG_BYPASS_PI:1;
unsigned int     REG_SDM_ORDER:1;
unsigned int     REG_EN_WDOG:1;
unsigned int     REG_EN_PI_DEBUG:1;
unsigned int     RSTB:1;
unsigned int     OC_EN:1;
}PLL_SCPU3;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     REG_PLLACPU_WDRST:1;
unsigned int     REG_PLLACPU_WDSET:1;
unsigned int     REG_PLLACPU_CS:2;
unsigned int     REG_PLLACPU_O:2;
unsigned int     REG_PLLACPU_RS:3;
unsigned int     PLLACPU_N:2;
unsigned int     PLLACPU_M:7;
unsigned int     PLLACPU_IP:3;
unsigned int     reserved_1:8;
unsigned int     PLLACPU_TST:1;
}PLL_ACPU1;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     PLLACPU_OEB:1;
unsigned int     PLLACPU_RSTB:1;
unsigned int     PLLACPU_POW:1;
}PLL_ACPU2;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     REG_PLLVCPU_WDRST:1;
unsigned int     REG_PLLVCPU_WDSET:1;
unsigned int     REG_PLLVCPU_CS:2;
unsigned int     REG_PLLVCPU_O:2;
unsigned int     REG_PLLVCPU_RS:3;
unsigned int     reserved_1:1;
unsigned int     PLLVCPU_N:2;
unsigned int     PLLVCPU_M:7;
unsigned int     PLLVCPU_IP:3;
unsigned int     reserved_2:1;
unsigned int     reserved_3:2;
unsigned int     reserved_4:4;
unsigned int     PLLVCPU_TST:1;
}PLL_VCPU1;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     PLLVCPU_OEB:1;
unsigned int     PLLVCPU_RSTB:1;
unsigned int     PLLVCPU_POW:1;
}PLL_VCPU2;

typedef struct 
{
unsigned int     PLLDDSA_N:2;
unsigned int     PLLDDSA_M:7;
unsigned int     PLLDDSA_IP:3;
unsigned int     PLLDDSA_RS:3;
unsigned int     PLLDDSA_CS:2;
unsigned int     PLLDDSA_CP:2;
unsigned int     PLLDDSA_R3:3;
unsigned int     PLLDDSA_C3:2;
unsigned int     PLLDDSA_PI_RL:2;
unsigned int     PLLDDSA_PI_RS:2;
unsigned int     PLLDDSA_PI_BIAS:2;
unsigned int     PLLDDSA_WDMODE:2;
}PLL_DISP_SD1;

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
unsigned int     write_en7:1;
unsigned int     PLLDDSA_FUPDN:1;
unsigned int     write_en6:1;
unsigned int     PLLDDSA_DDSEN:1;
unsigned int     write_en5:1;
unsigned int     PLLDDSA_VCORB:1;
unsigned int     write_en4:1;
unsigned int     PLLDDSA_TST:1;
unsigned int     PLLDDSA_PSTST:1;
unsigned int     write_en3:1;
unsigned int     PSAUD1A_FUPDN:1;
unsigned int     PSAUD1A_DIV:1;
unsigned int     write_en2:1;
unsigned int     PSAUD1A_TST:1;
unsigned int     PSAUD1A_PSEN:1;
unsigned int     write_en1:1;
unsigned int     PSAUD2A_FUPDN:1;
unsigned int     PSAUD2A_DIV:1;
unsigned int     PSAUD2A_TST:1;
unsigned int     PSAUD2A_PSEN:1;
}PLL_DISP_SD2;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     PSAUD1A_OEB:1;
unsigned int     PSAUD1A_RSTB:1;
unsigned int     PSAUD2A_OEB:1;
unsigned int     PSAUD2A_RSTB:1;
}PLL_DISP_SD3;

typedef struct 
{
unsigned int     reserved_0:26;
unsigned int     PLLDDSA_K:2;
unsigned int     reserved_1:1;
unsigned int     PLLDDSA_OEB:1;
unsigned int     PLLDDSA_RSTB:1;
unsigned int     PLLDDSA_POW:1;
}PLL_DISP_SD4;

typedef struct 
{
unsigned int     N:16;
unsigned int     M:16;
}PLL_DISP_SD5;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     N_nxt:16;
}PLL_DISP_SD6;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     N_nxt_add:8;
unsigned int     N_nxt_add_period:16;
}PLL_DISP_SD7;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     PLLDISP_Q2:2;
unsigned int     PLLDISP_BP:1;
unsigned int     PLLDISP_N:3;
unsigned int     PLLDISP_Q1:2;
unsigned int     PLLDISP_M:7;
unsigned int     PLLDISP_IP:2;
unsigned int     PLLDISP_RS:3;
unsigned int     PLLDISP_CS:2;
unsigned int     reserved_1:1;
unsigned int     PLLDISP_WDRST:1;
unsigned int     PLLDISP_WDSET:1;
unsigned int     PLLDISP_TST:1;
}PLL_DISP_HD1;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     PLLDISP_OEB2:1;
unsigned int     PLLDISP_OEB1:1;
unsigned int     PLLDISP_RSTB:1;
unsigned int     PLLDISP_POW:1;
}PLL_DISP_HD2;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     REG_PLLTST_POW:1;
unsigned int     reserved_1:4;
}PLL1_TEST;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     write_en4:1;
unsigned int     PLLDDR_CCO_BAND:2;
unsigned int     PLLDDR_CCO_KVCO:1;
unsigned int     write_en3:1;
unsigned int     PLLDISP_REG:2;
unsigned int     PLLDISP_POWREG:1;
unsigned int     write_en2:1;
unsigned int     PLLDDS_REG:2;
unsigned int     PLLDDS_POWREG:1;
unsigned int     write_en1:1;
unsigned int     PLLCPU_REG:2;
unsigned int     PLLCPU_POWREG:1;
}PLL_REG_CTRL;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     write_en4:1;
unsigned int     PLLDDR_PDIV:2;
unsigned int     write_en3:1;
unsigned int     PLLDDR_ICP:4;
unsigned int     PLLDDR_PLL_SEL_CPMODE:1;
unsigned int     PLLDDR_LPF_SR:3;
unsigned int     PLLDDR_LPF_CP:1;
unsigned int     PLLDDR_LOOP_PI_ISEL:3;
unsigned int     write_en2:1;
unsigned int     PLLDDR_POST_PI_SEL6:5;
unsigned int     PLLDDR_POST_PI_RL:2;
unsigned int     PLLDDR_POST_PI_BIAS:2;
unsigned int     PLLDDR_POST_PI_RS:1;
unsigned int     write_en1:1;
unsigned int     PLLDDR_CKREF_SEL:1;
unsigned int     PLLDDR_PLL_LDO_VSEL:2;
}PLL_DDR1;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     PLLDDR_POST_PI_SEL5:5;
unsigned int     PLLDDR_POST_PI_SEL4:5;
unsigned int     PLLDDR_POST_PI_SEL3:5;
unsigned int     PLLDDR_POST_PI_SEL2:5;
unsigned int     PLLDDR_POST_PI_SEL1:5;
unsigned int     PLLDDR_POST_PI_SEL0:5;
}PLL_DDR2;

typedef struct 
{
unsigned int     write_en2:1;
unsigned int     PLLDDR_DUM:8;
unsigned int     PLLDDR_PLL_DBUG_EN:1;
unsigned int     PLLDDR_OESYNC_OP_SEL:6;
unsigned int     PLLDDR_EN_POST_PI:7;
unsigned int     write_en1:1;
unsigned int     PLLDDR_CLK_OE:6;
unsigned int     PLLDDR_RSTB_IN:1;
unsigned int     PLLDDR_PLL_EN:1;
}PLL_DDR3;

typedef struct 
{
unsigned int     reserved_0:21;
unsigned int     PLLDDR_WDOUT_CLR:1;
unsigned int     PLLDDR_WD_EN:1;
unsigned int     PLLDDR_F390K:2;
unsigned int     PLLDDR_TIME0_CK:3;
unsigned int     PLLDDR_TIME_RDY_CKOUT:2;
unsigned int     PLLDDR_TIME2_RST_WIDTH:2;
}PLL_DDR4;

typedef struct 
{
unsigned int     reserved_0:3;
unsigned int     SSCDDR_N_CODE:8;
unsigned int     SSCDDR_F_CODE:13;
unsigned int     reserved_1:4;
unsigned int     SSCDDR_BYPASS_PI:1;
unsigned int     SSCDDR_SEL_MODE:1;
unsigned int     SSCDDR_EN_CENTER_IN:1;
unsigned int     SSCDDR_EN_SSC:1;
}PLL_DDR_SSC1;

typedef struct 
{
unsigned int     reserved_0:5;
unsigned int     PLLBUS_N:2;
unsigned int     PLLBUS_M:7;
unsigned int     PLLBUS_IP:3;
unsigned int     reserved_1:1;
unsigned int     PLLBUS_RS:3;
unsigned int     reserved_2:1;
unsigned int     PLLBUS_CS:2;
unsigned int     reserved_3:1;
unsigned int     PLLBUS_CP:2;
unsigned int     PLLBUS_R3:3;
unsigned int     PLLBUS_C3:2;
}PLL_BUS1;

typedef struct 
{
unsigned int     reserved_0:13;
unsigned int     write_en5:1;
unsigned int     PLLBUS_PI_RL:2;
unsigned int     PLLBUS_PI_RS:2;
unsigned int     PLLBUS_PI_BIAS:2;
unsigned int     write_en4:1;
unsigned int     PLLBUS_WDMODE:2;
unsigned int     reserved_1:2;
unsigned int     write_en3:1;
unsigned int     PLLBUS_FUPDN:1;
unsigned int     PLLBUS_PSEN:1;
unsigned int     PLLBUS_VCORB:1;
unsigned int     write_en1:1;
unsigned int     PLLBUS_TST:1;
unsigned int     PLLBUS_PSTST:1;
}PLL_BUS2;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     PLLBUS_O:2;
unsigned int     PLLBUS_OEB:1;
unsigned int     PLLBUS_RSTB:1;
unsigned int     PLLBUS_POW:1;
}PLL_BUS3;

typedef struct 
{
unsigned int     reserved_0:19;
unsigned int     PLLGPU_WDOUT:1;
unsigned int     PLLLVDS_WDOUT:1;
unsigned int     PLLDCSB_WDOUT:1;
unsigned int     PLLHDMI_WDOUT:1;
unsigned int     reserved_1:1;
unsigned int     PLLDDR_WDOUT:1;
unsigned int     PLLBUS_WDOUT:1;
unsigned int     PLLDISP_WDOUT:1;
unsigned int     PLLDDSB_WDOUT:1;
unsigned int     PLLDDSA_WDOUT:1;
unsigned int     PLLVCPU_WDOUT:1;
unsigned int     PLLACPU_WDOUT:1;
unsigned int     PLLSCPU_WDOUT:1;
}CRT_PLL_WDOUT;

typedef struct 
{
unsigned int     PLLDDSB_N:2;
unsigned int     PLLDDSB_M:7;
unsigned int     PLLDDSB_IP:3;
unsigned int     PLLDDSB_RS:3;
unsigned int     PLLDDSB_CS:2;
unsigned int     PLLDDSB_CP:2;
unsigned int     PLLDDSB_R3:3;
unsigned int     PLLDDSB_C3:2;
unsigned int     PLLDDSB_PI_RL:2;
unsigned int     PLLDDSB_PI_RS:2;
unsigned int     PLLDDSB_PI_BIAS:2;
unsigned int     PLLDDSB_WDMODE:2;
}PLL_DISP_2_SD1;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     write_en10:1;
unsigned int     pcr_b_smooth_en:1;
unsigned int     write_en9:1;
unsigned int     pcr_b_phase_sel:1;
unsigned int     write_en8:1;
unsigned int     pcr_b_ctl_en:1;
unsigned int     write_en7:1;
unsigned int     PLLDDSB_FUPDN:1;
unsigned int     write_en6:1;
unsigned int     PLLDDSB_DDSEN:1;
unsigned int     write_en5:1;
unsigned int     PLLDDSB_VCORB:1;
unsigned int     write_en4:1;
unsigned int     PLLDDSB_TST:1;
unsigned int     PLLDDSB_PSTST:1;
unsigned int     write_en3:1;
unsigned int     PSAUD1B_FUPDN:1;
unsigned int     PSAUD1B_DIV:1;
unsigned int     write_en2:1;
unsigned int     PSAUD1B_TST:1;
unsigned int     PSAUD1B_PSEN:1;
unsigned int     write_en1:1;
unsigned int     PSAUD2B_FUPDN:1;
unsigned int     PSAUD2B_DIV:1;
unsigned int     PSAUD2B_TST:1;
unsigned int     PSAUD2B_PSEN:1;
}PLL_DISP_2_SD2;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     PSAUD1B_OEB:1;
unsigned int     PSAUD1B_RSTB:1;
unsigned int     PSAUD2B_OEB:1;
unsigned int     PSAUD2B_RSTB:1;
}PLL_DISP_2_SD3;

typedef struct 
{
unsigned int     reserved_0:26;
unsigned int     PLLDDSB_K:2;
unsigned int     reserved_1:1;
unsigned int     PLLDDSB_OEB:1;
unsigned int     PLLDDSB_RSTB:1;
unsigned int     PLLDDSB_POW:1;
}PLL_DISP_2_SD4;

typedef struct 
{
unsigned int     N:16;
unsigned int     M:16;
}PLL_DISP_2_SD5;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     N_nxt:16;
}PLL_DISP_2_SD6;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     N_nxt_add:8;
unsigned int     N_nxt_add_period:16;
}PLL_DISP_2_SD7;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     REG_LDO_TMDS_PU:1;
unsigned int     REG_TV_PLL_PU:1;
unsigned int     REG_HDMI_CK_EN:1;
}PLL_HDMI;

typedef struct 
{
unsigned int     reserved_0:12;
unsigned int     REG_TV_PRE_DIV:1;
unsigned int     REG_TV_LDIV:6;
unsigned int     REG_TV_PSTEP_EN:1;
unsigned int     REG_TV_PSTEP:3;
unsigned int     REG_PIXEL_DIV3:1;
unsigned int     REG_PIXEL_DIV5:1;
unsigned int     REG_PIXEL_DIV16:3;
unsigned int     REG_TMDS_DIV5:1;
unsigned int     REG_TMDS_DIV16:3;
}PLL_HDMI2;

typedef struct 
{
unsigned int     reserved_0:5;
unsigned int     PLLDCSB_N:2;
unsigned int     PLLDCSB_M:7;
unsigned int     PLLDCSB_IP:3;
unsigned int     reserved_1:1;
unsigned int     PLLDCSB_RS:3;
unsigned int     reserved_2:1;
unsigned int     PLLDCSB_CS:2;
unsigned int     reserved_3:1;
unsigned int     PLLDCSB_CP:2;
unsigned int     PLLDCSB_R3:3;
unsigned int     PLLDCSB_C3:2;
}PLL_DCSB1;

typedef struct 
{
unsigned int     reserved_0:13;
unsigned int     write_en5:1;
unsigned int     PLLDCSB_PI_RL:2;
unsigned int     PLLDCSB_PI_RS:2;
unsigned int     PLLDCSB_PI_BIAS:2;
unsigned int     write_en4:1;
unsigned int     PLLDCSB_WDMODE:2;
unsigned int     reserved_1:2;
unsigned int     write_en3:1;
unsigned int     PLLDCSB_FUPDN:1;
unsigned int     PLLDCSB_PSEN:1;
unsigned int     PLLDCSB_VCORB:1;
unsigned int     write_en1:1;
unsigned int     PLLDCSB_TST:1;
unsigned int     PLLDCSB_PSTST:1;
}PLL_DCSB2;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     REG_PLLDCSB_O:2;
unsigned int     PLLDCSB_OEB:1;
unsigned int     PLLDCSB_RSTB:1;
unsigned int     PLLDCSB_POW:1;
}PLL_DCSB3;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     REG_PLLGPU_WDRST:1;
unsigned int     REG_PLLGPU_WDSET:1;
unsigned int     REG_PLLGPU_CS:2;
unsigned int     REG_PLLGPU_O:2;
unsigned int     REG_PLLGPU_RS:3;
unsigned int     reserved_1:1;
unsigned int     PLLGPU_N:2;
unsigned int     PLLGPU_M:7;
unsigned int     PLLGPU_IP:3;
unsigned int     reserved_2:1;
unsigned int     reserved_3:2;
unsigned int     reserved_4:4;
unsigned int     PLLGPU_TST:1;
}PLL_GPU1;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     PLLGPU_OEB:1;
unsigned int     PLLGPU_RSTB:1;
unsigned int     PLLGPU_POW:1;
}PLL_GPU2;

typedef struct 
{
unsigned int     REG_PLLLVDS_BPN:1;
unsigned int     REG_PLLLVDS_BPPHS:1;
unsigned int     REG_PLLLVDS_FREEZE:1;
unsigned int     REG_PLLLVDS_FUPDN:1;
unsigned int     REG_PLLLVDS_POW:1;
unsigned int     REG_PLLLVDS_RESERVE:1;
unsigned int     REG_PLLLVDS_RSTB:1;
unsigned int     REG_PLLLVDS_STOP:1;
unsigned int     REG_PLLLVDS_VCORSTB:1;
unsigned int     REG_PLLLVDS_WDRST:1;
unsigned int     REG_PLLLVDS_WDSET:1;
unsigned int     REG_PLLLVDS_CP:2;
unsigned int     REG_PLLLVDS_CS:2;
unsigned int     REG_PLLLVDS_O:2;
unsigned int     REG_PLLLVDS_IP:3;
unsigned int     REG_PLLLVDS_RS:3;
unsigned int     reserved_0:7;
unsigned int     PLLLVDS_RESER:1;
unsigned int     REG_PLLLVDS_TST:1;
}PLL_LVDS1;

typedef struct 
{
unsigned int     reserved_0:21;
unsigned int     REG_PLLLVDS_M:8;
unsigned int     REG_PLLLVDS_N:3;
}PLL_LVDS2;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     PLLDDR_PLL_STABLE:1;
unsigned int     POWDET_DDR:1;
}PLL_DDR6;

typedef struct 
{
unsigned int     reserved_0:19;
unsigned int     POR_VSET:1;
unsigned int     REG_PLLDDSB_SEL:1;
unsigned int     PLLDISP_SEL:2;
unsigned int     PLLHDMI_SEL:2;
unsigned int     PLLTST_SEL:4;
unsigned int     PLLTST_DIV:3;
}PLL_OTHER;

typedef struct 
{
unsigned int     reserved_0:10;
unsigned int     reg_tuned3318:3;
unsigned int     reg_d3318pow:2;
unsigned int     regpd_d3318:1;
unsigned int     reserved_1:3;
unsigned int     phsel1:5;
unsigned int     phsel0:5;
unsigned int     phrstb_dly_sel:1;
unsigned int     phrt0:1;
unsigned int     bias_en:1;
}PLL_SD1;

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
}PLL_SD2;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     ssc_div_n:10;
unsigned int     reserved_1:1;
unsigned int     ssc_step_in:7;
unsigned int     ssc_tbase:8;
}PLL_SD3;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     ssc_pll_pow:1;
unsigned int     ssc_pll_rstb:1;
unsigned int     ssc_rstb:1;
}PLL_SD4;

typedef struct 
{
unsigned int     reserved_0:10;
unsigned int     reg_tuned3318:3;
unsigned int     reg_d3318pow:2;
unsigned int     regpd_d3318:1;
unsigned int     reserved_1:3;
unsigned int     phsel1:5;
unsigned int     phsel0:5;
unsigned int     phrstb_dly_sel:1;
unsigned int     phrt0:1;
unsigned int     bias_en:1;
}PLL_EMMC1;

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
}PLL_EMMC2;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     ssc_div_n:10;
unsigned int     reserved_1:1;
unsigned int     ssc_step_in:7;
unsigned int     ssc_tbase:8;
}PLL_EMMC3;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     ssc_pll_pow:1;
unsigned int     ssc_pll_rstb:1;
unsigned int     ssc_rstb:1;
}PLL_EMMC4;

typedef struct 
{
unsigned int     REG_PLL_RESERVED:8;
unsigned int     reserved_0:16;
unsigned int     REG_LDO1_POW:1;
unsigned int     REG_LDO1_SEL:2;
unsigned int     REG_LDO2_POW:1;
unsigned int     REG_LDO2_SEL:2;
unsigned int     VDAC_BGR:2;
}BG_CTL;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     testmode:1;
unsigned int     nf_sel:1;
unsigned int     boot_sel:1;
}CRT_CHIP_INFO2;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     scpu_l2_bypass:1;
}SCPU_L2;

typedef struct 
{
unsigned int     reserved_0:15;
unsigned int     CMP_OUT:1;
unsigned int     PWDB1:1;
unsigned int     SBG1:3;
unsigned int     SDATA1:7;
unsigned int     SINL1:2;
unsigned int     SOS1:3;
}THML_SNSR_CTRL;

typedef struct 
{
unsigned int     kcpu_boot_info:32;
}PWDN_CTRL;

typedef struct 
{
unsigned int     acpu_boot_info:32;
}PWDN_CTRL2;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     write_en2:1;
unsigned int     kcpu_boot_info_valid:1;
unsigned int     write_en1:1;
unsigned int     kcpu_sw_rst:1;
}PWDN_CTRL3;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     acpu_boot_info_valid:1;
}PWDN_CTRL4;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     write_en2:1;
unsigned int     dac_test:1;
unsigned int     write_en1:1;
unsigned int     scpu_config_done:1;
}AT_SPEED;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     write_en2:1;
unsigned int     etn_phy_gpio_en:1;
unsigned int     write_en1:1;
unsigned int     etn_phy_125m_en:1;
}ANA_CTRL;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     demod_i2c_saddr:1;
unsigned int     demod_i2c_sel:1;
unsigned int     tp2_dm_sel:1;
unsigned int     tp1_dm_sel:1;
unsigned int     tp0_dm_sel:1;
}TP_DEMOD_CTRL;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     sata0_func_exist:1;
}PHY_FUNC;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     analogy_mode_sel:2;
}CRT_ANLG;

typedef struct 
{
unsigned int     Rvd1:32;
}DMY2;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     DP:3;
unsigned int     reserved_1:1;
unsigned int     DN:3;
}RGMII_PAD;

typedef struct 
{
unsigned int     nf_dd_7:2;
unsigned int     nf_dd_6:2;
unsigned int     nf_dd_5:2;
unsigned int     nf_dd_4:2;
unsigned int     nf_dd_3:2;
unsigned int     nf_dd_2:2;
unsigned int     nf_dd_1:2;
unsigned int     nf_dd_0:2;
unsigned int     nf_ce_n_1:2;
unsigned int     nf_ce_n_0:2;
unsigned int     nf_cle:2;
unsigned int     nf_ale:2;
unsigned int     nf_wr_n:2;
unsigned int     nf_rd_n:2;
unsigned int     nf_rdy:2;
unsigned int     reserved_0:2;
}CRT_MUXPAD0;

typedef struct 
{
unsigned int     mmc_data_3:2;
unsigned int     mmc_data_2:2;
unsigned int     mmc_data_1:2;
unsigned int     mmc_data_0:2;
unsigned int     mmc_cd:2;
unsigned int     mmc_wp:2;
unsigned int     mmc_clk:2;
unsigned int     mmc_cmd:2;
unsigned int     reserved_0:4;
unsigned int     sdio_data_3:2;
unsigned int     sdio_data_2:2;
unsigned int     sdio_data_1:2;
unsigned int     sdio_data_0:2;
unsigned int     sdio_clk:2;
unsigned int     sdio_cmd:2;
}CRT_MUXPAD1;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     tp1_clk:2;
unsigned int     tp1_valid:2;
unsigned int     tp1_sync:2;
unsigned int     tp1_data:2;
unsigned int     reserved_1:8;
unsigned int     tp0_clk:2;
unsigned int     tp0_valid:2;
unsigned int     tp0_sync:2;
unsigned int     tp0_data:2;
}MUXPAD2;

typedef struct 
{
unsigned int     sensor_cko_0:2;
unsigned int     sensor_cko_1:2;
unsigned int     sensor_rst:2;
unsigned int     sensor_stb_0:2;
unsigned int     sensor_stb_1:2;
unsigned int     ejtag_scpu_loc:2;
unsigned int     hi_loc:2;
unsigned int     usb_id:2;
unsigned int     hdmi_hpd:2;
unsigned int     spdif:2;
unsigned int     i2c_scl_5:2;
unsigned int     i2c_sda_5:2;
unsigned int     i2c_scl_4:2;
unsigned int     i2c_sda_4:2;
unsigned int     i2c_scl_1:2;
unsigned int     i2c_sda_1:2;
}MUXPAD3;

typedef struct 
{
unsigned int     reserved_0:10;
unsigned int     gpio_8:2;
unsigned int     gpio_7:2;
unsigned int     gpio_6:2;
unsigned int     gpio_5:2;
unsigned int     gpio_4:2;
unsigned int     gpio_3:3;
unsigned int     gpio_2:3;
unsigned int     gpio_1:3;
unsigned int     gpio_0:3;
}MUXPAD4;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     arm_trace_dbg_en:1;
unsigned int     sf_en:1;
}MUXPAD5;

typedef struct 
{
unsigned int     nf_cle_smt:1;
unsigned int     nf_cle_e2:1;
unsigned int     nf_cle_pud_en:1;
unsigned int     nf_cle_pud_sel:1;
unsigned int     nf_wr_n_smt:1;
unsigned int     nf_wr_n_e2:1;
unsigned int     nf_wr_n_pud_en:1;
unsigned int     nf_wr_n_pud_sel:1;
unsigned int     nf_rd_n_smt:1;
unsigned int     nf_rd_n_e2:1;
unsigned int     nf_rd_n_pud_en:1;
unsigned int     nf_rd_n_pud_sel:1;
unsigned int     nf_rdy_smt:1;
unsigned int     nf_rdy_e2:1;
unsigned int     nf_rdy_pud_en:1;
unsigned int     nf_rdy_pud_sel:1;
unsigned int     nf_ce_n_1_smt:1;
unsigned int     nf_ce_n_1_e2:1;
unsigned int     nf_ce_n_1_pud_en:1;
unsigned int     nf_ce_n_1_pud_sel:1;
unsigned int     nf_ce_n_0_smt:1;
unsigned int     nf_ce_n_0_e2:1;
unsigned int     nf_ce_n_0_pud_en:1;
unsigned int     nf_ce_n_0_pud_sel:1;
unsigned int     nf_ale_smt:1;
unsigned int     nf_ale_e2:1;
unsigned int     nf_ale_pud_en:1;
unsigned int     nf_ale_pud_sel:1;
unsigned int     reserved_0:4;
}PFUNC_NF0;

typedef struct 
{
unsigned int     nf_dd_7_smt:1;
unsigned int     nf_dd_7_e2:1;
unsigned int     nf_dd_7_pud_en:1;
unsigned int     nf_dd_7_pud_sel:1;
unsigned int     nf_dd_6_smt:1;
unsigned int     nf_dd_6_e2:1;
unsigned int     nf_dd_6_pud_en:1;
unsigned int     nf_dd_6_pud_sel:1;
unsigned int     nf_dd_5_smt:1;
unsigned int     nf_dd_5_e2:1;
unsigned int     nf_dd_5_pud_en:1;
unsigned int     nf_dd_5_pud_sel:1;
unsigned int     nf_dd_4_smt:1;
unsigned int     nf_dd_4_e2:1;
unsigned int     nf_dd_4_pud_en:1;
unsigned int     nf_dd_4_pud_sel:1;
unsigned int     nf_dd_3_smt:1;
unsigned int     nf_dd_3_e2:1;
unsigned int     nf_dd_3_pud_en:1;
unsigned int     nf_dd_3_pud_sel:1;
unsigned int     nf_dd_2_smt:1;
unsigned int     nf_dd_2_e2:1;
unsigned int     nf_dd_2_pud_en:1;
unsigned int     nf_dd_2_pud_sel:1;
unsigned int     nf_dd_1_smt:1;
unsigned int     nf_dd_1_e2:1;
unsigned int     nf_dd_1_pud_en:1;
unsigned int     nf_dd_1_pud_sel:1;
unsigned int     nf_dd_0_smt:1;
unsigned int     nf_dd_0_e2:1;
unsigned int     nf_dd_0_pud_en:1;
unsigned int     nf_dd_0_pud_sel:1;
}PFUNC_NF1;

typedef struct 
{
unsigned int     mmc_data_3_smt:1;
unsigned int     mmc_data_3_e2:1;
unsigned int     mmc_data_3_pud_en:1;
unsigned int     mmc_data_3_pud_sel:1;
unsigned int     mmc_data_2_smt:1;
unsigned int     mmc_data_2_e2:1;
unsigned int     mmc_data_2_pud_en:1;
unsigned int     mmc_data_2_pud_sel:1;
unsigned int     mmc_data_1_smt:1;
unsigned int     mmc_data_1_e2:1;
unsigned int     mmc_data_1_pud_en:1;
unsigned int     mmc_data_1_pud_sel:1;
unsigned int     mmc_data_0_smt:1;
unsigned int     mmc_data_0_e2:1;
unsigned int     mmc_data_0_pud_en:1;
unsigned int     mmc_data_0_pud_sel:1;
unsigned int     mmc_cd_smt:1;
unsigned int     mmc_cd_e2:1;
unsigned int     mmc_cd_pud_en:1;
unsigned int     mmc_cd_pud_sel:1;
unsigned int     mmc_wp_smt:1;
unsigned int     mmc_wp_e2:1;
unsigned int     mmc_wp_pud_en:1;
unsigned int     mmc_wp_pud_sel:1;
unsigned int     mmc_clk_smt:1;
unsigned int     mmc_clk_e2:1;
unsigned int     mmc_clk_pud_en:1;
unsigned int     mmc_clk_pud_sel:1;
unsigned int     mmc_cmd_smt:1;
unsigned int     mmc_cmd_e2:1;
unsigned int     mmc_cmd_pud_en:1;
unsigned int     mmc_cmd_pud_sel:1;
}PFUNC_CR;

typedef struct 
{
unsigned int     sdio_data_3_smt:1;
unsigned int     sdio_data_3_e2:1;
unsigned int     sdio_data_3_pud_en:1;
unsigned int     sdio_data_3_pud_sel:1;
unsigned int     sdio_data_2_smt:1;
unsigned int     sdio_data_2_e2:1;
unsigned int     sdio_data_2_pud_en:1;
unsigned int     sdio_data_2_pud_sel:1;
unsigned int     sdio_data_1_smt:1;
unsigned int     sdio_data_1_e2:1;
unsigned int     sdio_data_1_pud_en:1;
unsigned int     sdio_data_1_pud_sel:1;
unsigned int     sdio_data_0_smt:1;
unsigned int     sdio_data_0_e2:1;
unsigned int     sdio_data_0_pud_en:1;
unsigned int     sdio_data_0_pud_sel:1;
unsigned int     sdio_cd_smt:1;
unsigned int     sdio_cd_e2:1;
unsigned int     sdio_cd_pud_en:1;
unsigned int     sdio_cd_pud_sel:1;
unsigned int     sdio_wp_smt:1;
unsigned int     sdio_wp_e2:1;
unsigned int     sdio_wp_pud_en:1;
unsigned int     sdio_wp_pud_sel:1;
unsigned int     sdio_clk_smt:1;
unsigned int     sdio_clk_e2:1;
unsigned int     sdio_clk_pud_en:1;
unsigned int     sdio_clk_pud_sel:1;
unsigned int     sdio_cmd_smt:1;
unsigned int     sdio_cmd_e2:1;
unsigned int     sdio_cmd_pud_en:1;
unsigned int     sdio_cmd_pud_sel:1;
}PFUNC_SDIO;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     spdif_out_e2:1;
unsigned int     spdif_out_pud_en:1;
unsigned int     spdif_out_pud_sel:1;
}PFUNC_AIO;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     tp0_data_smt:1;
unsigned int     tp0_data_e2:1;
unsigned int     tp0_data_pud_en:1;
unsigned int     tp0_data_pud_sel:1;
unsigned int     tp0_valid_smt:1;
unsigned int     tp0_valid_e2:1;
unsigned int     tp0_valid_pud_en:1;
unsigned int     tp0_valid_pud_sel:1;
unsigned int     tp0_sync_smt:1;
unsigned int     tp0_sync_e2:1;
unsigned int     tp0_sync_pud_en:1;
unsigned int     tp0_sync_pud_sel:1;
unsigned int     tp0_clk_smt:1;
unsigned int     tp0_clk_e2:1;
unsigned int     tp0_clk_pud_en:1;
unsigned int     tp0_clk_pud_sel:1;
}PFUNC_TP0;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     tp1_data_smt:1;
unsigned int     tp1_data_e2:1;
unsigned int     tp1_data_pud_en:1;
unsigned int     tp1_data_pud_sel:1;
unsigned int     tp1_valid_smt:1;
unsigned int     tp1_valid_e2:1;
unsigned int     tp1_valid_pud_en:1;
unsigned int     tp1_valid_pud_sel:1;
unsigned int     tp1_sync_smt:1;
unsigned int     tp1_sync_e2:1;
unsigned int     tp1_sync_pud_en:1;
unsigned int     tp1_sync_pud_sel:1;
unsigned int     tp1_clk_smt:1;
unsigned int     tp1_clk_e2:1;
unsigned int     tp1_clk_pud_en:1;
unsigned int     tp1_clk_pud_sel:1;
}PFUNC_TP1;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     i2c_scl_5_smt:1;
unsigned int     i2c_scl_5_e2:1;
unsigned int     i2c_scl_5_pud_en:1;
unsigned int     i2c_scl_5_pud_sel:1;
unsigned int     i2c_sda_5_smt:1;
unsigned int     i2c_sda_5_e2:1;
unsigned int     i2c_sda_5_pud_en:1;
unsigned int     i2c_sda_5_pud_sel:1;
unsigned int     i2c_scl_4_smt:1;
unsigned int     i2c_scl_4_e2:1;
unsigned int     i2c_scl_4_pud_en:1;
unsigned int     i2c_scl_4_pud_sel:1;
unsigned int     i2c_sda_4_smt:1;
unsigned int     i2c_sda_4_e2:1;
unsigned int     i2c_sda_4_pud_en:1;
unsigned int     i2c_sda_4_pud_sel:1;
unsigned int     i2c_scl_1_smt:1;
unsigned int     i2c_scl_1_e2:1;
unsigned int     i2c_scl_1_pud_en:1;
unsigned int     i2c_scl_1_pud_sel:1;
unsigned int     i2c_sda_1_smt:1;
unsigned int     i2c_sda_1_e2:1;
unsigned int     i2c_sda_1_pud_en:1;
unsigned int     i2c_sda_1_pud_sel:1;
}PFUNC_MISC0;

typedef struct 
{
unsigned int     gpio_7_smt:1;
unsigned int     gpio_7_e2:1;
unsigned int     gpio_7_pud_en:1;
unsigned int     gpio_7_pud_sel:1;
unsigned int     gpio_6_smt:1;
unsigned int     gpio_6_e2:1;
unsigned int     gpio_6_pud_en:1;
unsigned int     gpio_6_pud_sel:1;
unsigned int     gpio_5_smt:1;
unsigned int     gpio_5_e2:1;
unsigned int     gpio_5_pud_en:1;
unsigned int     gpio_5_pud_sel:1;
unsigned int     gpio_4_smt:1;
unsigned int     gpio_4_e2:1;
unsigned int     gpio_4_pud_en:1;
unsigned int     gpio_4_pud_sel:1;
unsigned int     gpio_3_smt:1;
unsigned int     gpio_3_e2:1;
unsigned int     gpio_3_pud_en:1;
unsigned int     gpio_3_pud_sel:1;
unsigned int     gpio_2_smt:1;
unsigned int     gpio_2_e2:1;
unsigned int     gpio_2_pud_en:1;
unsigned int     gpio_2_pud_sel:1;
unsigned int     gpio_1_smt:1;
unsigned int     gpio_1_e2:1;
unsigned int     gpio_1_pud_en:1;
unsigned int     gpio_1_pud_sel:1;
unsigned int     gpio_0_smt:1;
unsigned int     gpio_0_e2:1;
unsigned int     gpio_0_pud_en:1;
unsigned int     gpio_0_pud_sel:1;
}PFUNC_MISC1;

typedef struct 
{
unsigned int     sensor_cko1_smt:1;
unsigned int     sensor_cko1_e2:1;
unsigned int     sensor_cko1_pud_en:1;
unsigned int     sensor_cko1_pud_sel:1;
unsigned int     sensor_cko0_smt:1;
unsigned int     sensor_cko0_e2:1;
unsigned int     sensor_cko0_pud_en:1;
unsigned int     sensor_cko0_pud_sel:1;
unsigned int     sensor_rst_smt:1;
unsigned int     sensor_rst_e2:1;
unsigned int     sensor_rst_pud_en:1;
unsigned int     sensor_rst_pud_sel:1;
unsigned int     sensor_stb1_smt:1;
unsigned int     sensor_stb1_e2:1;
unsigned int     sensor_stb1_pud_en:1;
unsigned int     sensor_stb1_pud_sel:1;
unsigned int     sensor_stb0_smt:1;
unsigned int     sensor_stb0_e2:1;
unsigned int     sensor_stb0_pud_en:1;
unsigned int     sensor_stb0_pud_sel:1;
unsigned int     usb_id_smt:1;
unsigned int     usb_id_e2:1;
unsigned int     usb_id_pud_en:1;
unsigned int     usb_id_pud_sel:1;
unsigned int     hdmi_hpd_smt:1;
unsigned int     hdmi_hpd_e2:1;
unsigned int     hdmi_hpd_pud_en:1;
unsigned int     hdmi_hpd_pud_sel:1;
unsigned int     gpio_8_smt:1;
unsigned int     gpio_8_e2:1;
unsigned int     gpio_8_pud_en:1;
unsigned int     gpio_8_pud_sel:1;
}PFUNC_MISC2;

typedef struct 
{
unsigned int     reserved_0:14;
unsigned int     boption9_en:1;
unsigned int     boption9_sel:1;
unsigned int     boption8_en:1;
unsigned int     boption8_sel:1;
unsigned int     boption7_en:1;
unsigned int     boption7_sel:1;
unsigned int     boption6_en:1;
unsigned int     boption6_sel:1;
unsigned int     boption5_en:1;
unsigned int     boption5_sel:1;
unsigned int     boption4_en:1;
unsigned int     boption4_sel:1;
unsigned int     boption3_en:1;
unsigned int     boption3_sel:1;
unsigned int     boption1_en:1;
unsigned int     boption1_sel:1;
unsigned int     boption0_en:1;
unsigned int     boption0_sel:1;
}PFUNC_MISC3;

typedef struct 
{
unsigned int     reserved_0:23;
unsigned int     crt_dbg_en:1;
unsigned int     crt_dbg_sel0:4;
unsigned int     crt_dbg_sel1:4;
}CRT_DEBUG;

typedef struct 
{
unsigned int     reserved_0:17;
unsigned int     dbg_en:1;
unsigned int     dbg_loc:2;
unsigned int     dbg_sel0:6;
unsigned int     dbg_sel1:6;
}DEBUG;

typedef struct 
{
unsigned int     dummy_reg:32;
}DUMMY;

#endif

#define SOFT_RESET1                                                                  0x98000000
#define SOFT_RESET1_reg_addr                                                         "0x98000000"
#define SOFT_RESET1_reg                                                              0x98000000
#define set_SOFT_RESET1_reg(data)   (*((volatile unsigned int*) SOFT_RESET1_reg)=data)
#define get_SOFT_RESET1_reg   (*((volatile unsigned int*) SOFT_RESET1_reg))
#define SOFT_RESET1_inst_adr                                                         "0x0000"
#define SOFT_RESET1_inst                                                             0x0000
#define SOFT_RESET1_rstn_mipi_shift                                                  (30)
#define SOFT_RESET1_rstn_mipi_mask                                                   (0x40000000)
#define SOFT_RESET1_rstn_mipi(data)                                                  (0x40000000&((data)<<30))
#define SOFT_RESET1_rstn_mipi_src(data)                                              ((0x40000000&(data))>>30)
#define SOFT_RESET1_get_rstn_mipi(data)                                              ((0x40000000&(data))>>30)
#define SOFT_RESET1_rstn_nf_shift                                                    (29)
#define SOFT_RESET1_rstn_nf_mask                                                     (0x20000000)
#define SOFT_RESET1_rstn_nf(data)                                                    (0x20000000&((data)<<29))
#define SOFT_RESET1_rstn_nf_src(data)                                                ((0x20000000&(data))>>29)
#define SOFT_RESET1_get_rstn_nf(data)                                                ((0x20000000&(data))>>29)
#define SOFT_RESET1_rstn_ae_shift                                                    (28)
#define SOFT_RESET1_rstn_ae_mask                                                     (0x10000000)
#define SOFT_RESET1_rstn_ae(data)                                                    (0x10000000&((data)<<28))
#define SOFT_RESET1_rstn_ae_src(data)                                                ((0x10000000&(data))>>28)
#define SOFT_RESET1_get_rstn_ae(data)                                                ((0x10000000&(data))>>28)
#define SOFT_RESET1_rstn_tp_shift                                                    (27)
#define SOFT_RESET1_rstn_tp_mask                                                     (0x08000000)
#define SOFT_RESET1_rstn_tp(data)                                                    (0x08000000&((data)<<27))
#define SOFT_RESET1_rstn_tp_src(data)                                                ((0x08000000&(data))>>27)
#define SOFT_RESET1_get_rstn_tp(data)                                                ((0x08000000&(data))>>27)
#define SOFT_RESET1_rstn_md_shift                                                    (26)
#define SOFT_RESET1_rstn_md_mask                                                     (0x04000000)
#define SOFT_RESET1_rstn_md(data)                                                    (0x04000000&((data)<<26))
#define SOFT_RESET1_rstn_md_src(data)                                                ((0x04000000&(data))>>26)
#define SOFT_RESET1_get_rstn_md(data)                                                ((0x04000000&(data))>>26)
#define SOFT_RESET1_rstn_cp_shift                                                    (25)
#define SOFT_RESET1_rstn_cp_mask                                                     (0x02000000)
#define SOFT_RESET1_rstn_cp(data)                                                    (0x02000000&((data)<<25))
#define SOFT_RESET1_rstn_cp_src(data)                                                ((0x02000000&(data))>>25)
#define SOFT_RESET1_get_rstn_cp(data)                                                ((0x02000000&(data))>>25)
#define SOFT_RESET1_rstn_dc_phy_shift                                                (24)
#define SOFT_RESET1_rstn_dc_phy_mask                                                 (0x01000000)
#define SOFT_RESET1_rstn_dc_phy(data)                                                (0x01000000&((data)<<24))
#define SOFT_RESET1_rstn_dc_phy_src(data)                                            ((0x01000000&(data))>>24)
#define SOFT_RESET1_get_rstn_dc_phy(data)                                            ((0x01000000&(data))>>24)
#define SOFT_RESET1_rstn_dcu_shift                                                   (23)
#define SOFT_RESET1_rstn_dcu_mask                                                    (0x00800000)
#define SOFT_RESET1_rstn_dcu(data)                                                   (0x00800000&((data)<<23))
#define SOFT_RESET1_rstn_dcu_src(data)                                               ((0x00800000&(data))>>23)
#define SOFT_RESET1_get_rstn_dcu(data)                                               ((0x00800000&(data))>>23)
#define SOFT_RESET1_rstn_se_shift                                                    (22)
#define SOFT_RESET1_rstn_se_mask                                                     (0x00400000)
#define SOFT_RESET1_rstn_se(data)                                                    (0x00400000&((data)<<22))
#define SOFT_RESET1_rstn_se_src(data)                                                ((0x00400000&(data))>>22)
#define SOFT_RESET1_get_rstn_se(data)                                                ((0x00400000&(data))>>22)
#define SOFT_RESET1_rstn_lvds_shift                                                  (21)
#define SOFT_RESET1_rstn_lvds_mask                                                   (0x00200000)
#define SOFT_RESET1_rstn_lvds(data)                                                  (0x00200000&((data)<<21))
#define SOFT_RESET1_rstn_lvds_src(data)                                              ((0x00200000&(data))>>21)
#define SOFT_RESET1_get_rstn_lvds(data)                                              ((0x00200000&(data))>>21)
#define SOFT_RESET1_rstn_vo_shift                                                    (20)
#define SOFT_RESET1_rstn_vo_mask                                                     (0x00100000)
#define SOFT_RESET1_rstn_vo(data)                                                    (0x00100000&((data)<<20))
#define SOFT_RESET1_rstn_vo_src(data)                                                ((0x00100000&(data))>>20)
#define SOFT_RESET1_get_rstn_vo(data)                                                ((0x00100000&(data))>>20)
#define SOFT_RESET1_rstn_tve_shift                                                   (19)
#define SOFT_RESET1_rstn_tve_mask                                                    (0x00080000)
#define SOFT_RESET1_rstn_tve(data)                                                   (0x00080000&((data)<<19))
#define SOFT_RESET1_rstn_tve_src(data)                                               ((0x00080000&(data))>>19)
#define SOFT_RESET1_get_rstn_tve(data)                                               ((0x00080000&(data))>>19)
#define SOFT_RESET1_rstn_ve_jpeg_shift                                               (18)
#define SOFT_RESET1_rstn_ve_jpeg_mask                                                (0x00040000)
#define SOFT_RESET1_rstn_ve_jpeg(data)                                               (0x00040000&((data)<<18))
#define SOFT_RESET1_rstn_ve_jpeg_src(data)                                           ((0x00040000&(data))>>18)
#define SOFT_RESET1_get_rstn_ve_jpeg(data)                                           ((0x00040000&(data))>>18)
#define SOFT_RESET1_rstn_ve_h264_shift                                               (17)
#define SOFT_RESET1_rstn_ve_h264_mask                                                (0x00020000)
#define SOFT_RESET1_rstn_ve_h264(data)                                               (0x00020000&((data)<<17))
#define SOFT_RESET1_rstn_ve_h264_src(data)                                           ((0x00020000&(data))>>17)
#define SOFT_RESET1_get_rstn_ve_h264(data)                                           ((0x00020000&(data))>>17)
#define SOFT_RESET1_rstn_gpu_shift                                                   (16)
#define SOFT_RESET1_rstn_gpu_mask                                                    (0x00010000)
#define SOFT_RESET1_rstn_gpu(data)                                                   (0x00010000&((data)<<16))
#define SOFT_RESET1_rstn_gpu_src(data)                                               ((0x00010000&(data))>>16)
#define SOFT_RESET1_get_rstn_gpu(data)                                               ((0x00010000&(data))>>16)
#define SOFT_RESET1_rstn_aio_shift                                                   (15)
#define SOFT_RESET1_rstn_aio_mask                                                    (0x00008000)
#define SOFT_RESET1_rstn_aio(data)                                                   (0x00008000&((data)<<15))
#define SOFT_RESET1_rstn_aio_src(data)                                               ((0x00008000&(data))>>15)
#define SOFT_RESET1_get_rstn_aio(data)                                               ((0x00008000&(data))>>15)
#define SOFT_RESET1_rstn_etn_phy_shift                                               (14)
#define SOFT_RESET1_rstn_etn_phy_mask                                                (0x00004000)
#define SOFT_RESET1_rstn_etn_phy(data)                                               (0x00004000&((data)<<14))
#define SOFT_RESET1_rstn_etn_phy_src(data)                                           ((0x00004000&(data))>>14)
#define SOFT_RESET1_get_rstn_etn_phy(data)                                           ((0x00004000&(data))>>14)
#define SOFT_RESET1_rstn_etn_shift                                                   (13)
#define SOFT_RESET1_rstn_etn_mask                                                    (0x00002000)
#define SOFT_RESET1_rstn_etn(data)                                                   (0x00002000&((data)<<13))
#define SOFT_RESET1_rstn_etn_src(data)                                               ((0x00002000&(data))>>13)
#define SOFT_RESET1_get_rstn_etn(data)                                               ((0x00002000&(data))>>13)
#define SOFT_RESET1_rstn_hdmi_shift                                                  (12)
#define SOFT_RESET1_rstn_hdmi_mask                                                   (0x00001000)
#define SOFT_RESET1_rstn_hdmi(data)                                                  (0x00001000&((data)<<12))
#define SOFT_RESET1_rstn_hdmi_src(data)                                              ((0x00001000&(data))>>12)
#define SOFT_RESET1_get_rstn_hdmi(data)                                              ((0x00001000&(data))>>12)
#define SOFT_RESET1_rstn_hdmirx_shift                                                (11)
#define SOFT_RESET1_rstn_hdmirx_mask                                                 (0x00000800)
#define SOFT_RESET1_rstn_hdmirx(data)                                                (0x00000800&((data)<<11))
#define SOFT_RESET1_rstn_hdmirx_src(data)                                            ((0x00000800&(data))>>11)
#define SOFT_RESET1_get_rstn_hdmirx(data)                                            ((0x00000800&(data))>>11)
#define SOFT_RESET1_rstn_cbusrx_shift                                                (10)
#define SOFT_RESET1_rstn_cbusrx_mask                                                 (0x00000400)
#define SOFT_RESET1_rstn_cbusrx(data)                                                (0x00000400&((data)<<10))
#define SOFT_RESET1_rstn_cbusrx_src(data)                                            ((0x00000400&(data))>>10)
#define SOFT_RESET1_get_rstn_cbusrx(data)                                            ((0x00000400&(data))>>10)
#define SOFT_RESET1_rstn_usb_phy1_shift                                              (9)
#define SOFT_RESET1_rstn_usb_phy1_mask                                               (0x00000200)
#define SOFT_RESET1_rstn_usb_phy1(data)                                              (0x00000200&((data)<<9))
#define SOFT_RESET1_rstn_usb_phy1_src(data)                                          ((0x00000200&(data))>>9)
#define SOFT_RESET1_get_rstn_usb_phy1(data)                                          ((0x00000200&(data))>>9)
#define SOFT_RESET1_rstn_usb_phy0_shift                                              (8)
#define SOFT_RESET1_rstn_usb_phy0_mask                                               (0x00000100)
#define SOFT_RESET1_rstn_usb_phy0(data)                                              (0x00000100&((data)<<8))
#define SOFT_RESET1_rstn_usb_phy0_src(data)                                          ((0x00000100&(data))>>8)
#define SOFT_RESET1_get_rstn_usb_phy0(data)                                          ((0x00000100&(data))>>8)
#define SOFT_RESET1_rstn_cbustx_shift                                                (7)
#define SOFT_RESET1_rstn_cbustx_mask                                                 (0x00000080)
#define SOFT_RESET1_rstn_cbustx(data)                                                (0x00000080&((data)<<7))
#define SOFT_RESET1_rstn_cbustx_src(data)                                            ((0x00000080&(data))>>7)
#define SOFT_RESET1_get_rstn_cbustx(data)                                            ((0x00000080&(data))>>7)
#define SOFT_RESET1_rstn_usb_shift                                                   (6)
#define SOFT_RESET1_rstn_usb_mask                                                    (0x00000040)
#define SOFT_RESET1_rstn_usb(data)                                                   (0x00000040&((data)<<6))
#define SOFT_RESET1_rstn_usb_src(data)                                               ((0x00000040&(data))>>6)
#define SOFT_RESET1_get_rstn_usb(data)                                               ((0x00000040&(data))>>6)
#define SOFT_RESET1_rstn_ve_h265_shift                                               (5)
#define SOFT_RESET1_rstn_ve_h265_mask                                                (0x00000020)
#define SOFT_RESET1_rstn_ve_h265(data)                                               (0x00000020&((data)<<5))
#define SOFT_RESET1_rstn_ve_h265_src(data)                                           ((0x00000020&(data))>>5)
#define SOFT_RESET1_get_rstn_ve_h265(data)                                           ((0x00000020&(data))>>5)
#define SOFT_RESET1_rstn_gspi_shift                                                  (3)
#define SOFT_RESET1_rstn_gspi_mask                                                   (0x00000008)
#define SOFT_RESET1_rstn_gspi(data)                                                  (0x00000008&((data)<<3))
#define SOFT_RESET1_rstn_gspi_src(data)                                              ((0x00000008&(data))>>3)
#define SOFT_RESET1_get_rstn_gspi(data)                                              ((0x00000008&(data))>>3)
#define SOFT_RESET1_rstn_rng_shift                                                   (1)
#define SOFT_RESET1_rstn_rng_mask                                                    (0x00000002)
#define SOFT_RESET1_rstn_rng(data)                                                   (0x00000002&((data)<<1))
#define SOFT_RESET1_rstn_rng_src(data)                                               ((0x00000002&(data))>>1)
#define SOFT_RESET1_get_rstn_rng(data)                                               ((0x00000002&(data))>>1)
#define SOFT_RESET1_rstn_misc_shift                                                  (0)
#define SOFT_RESET1_rstn_misc_mask                                                   (0x00000001)
#define SOFT_RESET1_rstn_misc(data)                                                  (0x00000001&((data)<<0))
#define SOFT_RESET1_rstn_misc_src(data)                                              ((0x00000001&(data))>>0)
#define SOFT_RESET1_get_rstn_misc(data)                                              ((0x00000001&(data))>>0)


#define SOFT_RESET2                                                                  0x98000004
#define SOFT_RESET2_reg_addr                                                         "0x98000004"
#define SOFT_RESET2_reg                                                              0x98000004
#define set_SOFT_RESET2_reg(data)   (*((volatile unsigned int*) SOFT_RESET2_reg)=data)
#define get_SOFT_RESET2_reg   (*((volatile unsigned int*) SOFT_RESET2_reg))
#define SOFT_RESET2_inst_adr                                                         "0x0001"
#define SOFT_RESET2_inst                                                             0x0001
#define SOFT_RESET2_rstn_ur0_shift                                                   (29)
#define SOFT_RESET2_rstn_ur0_mask                                                    (0x20000000)
#define SOFT_RESET2_rstn_ur0(data)                                                   (0x20000000&((data)<<29))
#define SOFT_RESET2_rstn_ur0_src(data)                                               ((0x20000000&(data))>>29)
#define SOFT_RESET2_get_rstn_ur0(data)                                               ((0x20000000&(data))>>29)
#define SOFT_RESET2_rstn_ur1_shift                                                   (28)
#define SOFT_RESET2_rstn_ur1_mask                                                    (0x10000000)
#define SOFT_RESET2_rstn_ur1(data)                                                   (0x10000000&((data)<<28))
#define SOFT_RESET2_rstn_ur1_src(data)                                               ((0x10000000&(data))>>28)
#define SOFT_RESET2_get_rstn_ur1(data)                                               ((0x10000000&(data))>>28)
#define SOFT_RESET2_rstn_i2c_0_shift                                                 (27)
#define SOFT_RESET2_rstn_i2c_0_mask                                                  (0x08000000)
#define SOFT_RESET2_rstn_i2c_0(data)                                                 (0x08000000&((data)<<27))
#define SOFT_RESET2_rstn_i2c_0_src(data)                                             ((0x08000000&(data))>>27)
#define SOFT_RESET2_get_rstn_i2c_0(data)                                             ((0x08000000&(data))>>27)
#define SOFT_RESET2_rstn_i2c_1_shift                                                 (26)
#define SOFT_RESET2_rstn_i2c_1_mask                                                  (0x04000000)
#define SOFT_RESET2_rstn_i2c_1(data)                                                 (0x04000000&((data)<<26))
#define SOFT_RESET2_rstn_i2c_1_src(data)                                             ((0x04000000&(data))>>26)
#define SOFT_RESET2_get_rstn_i2c_1(data)                                             ((0x04000000&(data))>>26)
#define SOFT_RESET2_rstn_i2c_2_shift                                                 (25)
#define SOFT_RESET2_rstn_i2c_2_mask                                                  (0x02000000)
#define SOFT_RESET2_rstn_i2c_2(data)                                                 (0x02000000&((data)<<25))
#define SOFT_RESET2_rstn_i2c_2_src(data)                                             ((0x02000000&(data))>>25)
#define SOFT_RESET2_get_rstn_i2c_2(data)                                             ((0x02000000&(data))>>25)
#define SOFT_RESET2_rstn_i2c_3_shift                                                 (24)
#define SOFT_RESET2_rstn_i2c_3_mask                                                  (0x01000000)
#define SOFT_RESET2_rstn_i2c_3(data)                                                 (0x01000000&((data)<<24))
#define SOFT_RESET2_rstn_i2c_3_src(data)                                             ((0x01000000&(data))>>24)
#define SOFT_RESET2_get_rstn_i2c_3(data)                                             ((0x01000000&(data))>>24)
#define SOFT_RESET2_rstn_i2c_4_shift                                                 (23)
#define SOFT_RESET2_rstn_i2c_4_mask                                                  (0x00800000)
#define SOFT_RESET2_rstn_i2c_4(data)                                                 (0x00800000&((data)<<23))
#define SOFT_RESET2_rstn_i2c_4_src(data)                                             ((0x00800000&(data))>>23)
#define SOFT_RESET2_get_rstn_i2c_4(data)                                             ((0x00800000&(data))>>23)
#define SOFT_RESET2_rstn_ir_shift                                                    (22)
#define SOFT_RESET2_rstn_ir_mask                                                     (0x00400000)
#define SOFT_RESET2_rstn_ir(data)                                                    (0x00400000&((data)<<22))
#define SOFT_RESET2_rstn_ir_src(data)                                                ((0x00400000&(data))>>22)
#define SOFT_RESET2_get_rstn_ir(data)                                                ((0x00400000&(data))>>22)
#define SOFT_RESET2_rstn_cec1_shift                                                  (21)
#define SOFT_RESET2_rstn_cec1_mask                                                   (0x00200000)
#define SOFT_RESET2_rstn_cec1(data)                                                  (0x00200000&((data)<<21))
#define SOFT_RESET2_rstn_cec1_src(data)                                              ((0x00200000&(data))>>21)
#define SOFT_RESET2_get_rstn_cec1(data)                                              ((0x00200000&(data))>>21)
#define SOFT_RESET2_rstn_rtc_shift                                                   (20)
#define SOFT_RESET2_rstn_rtc_mask                                                    (0x00100000)
#define SOFT_RESET2_rstn_rtc(data)                                                   (0x00100000&((data)<<20))
#define SOFT_RESET2_rstn_rtc_src(data)                                               ((0x00100000&(data))>>20)
#define SOFT_RESET2_get_rstn_rtc(data)                                               ((0x00100000&(data))>>20)
#define SOFT_RESET2_rstn_vfd_shift                                                   (19)
#define SOFT_RESET2_rstn_vfd_mask                                                    (0x00080000)
#define SOFT_RESET2_rstn_vfd(data)                                                   (0x00080000&((data)<<19))
#define SOFT_RESET2_rstn_vfd_src(data)                                               ((0x00080000&(data))>>19)
#define SOFT_RESET2_get_rstn_vfd(data)                                               ((0x00080000&(data))>>19)
#define SOFT_RESET2_rstn_i2c_5_shift                                                 (18)
#define SOFT_RESET2_rstn_i2c_5_mask                                                  (0x00040000)
#define SOFT_RESET2_rstn_i2c_5(data)                                                 (0x00040000&((data)<<18))
#define SOFT_RESET2_rstn_i2c_5_src(data)                                             ((0x00040000&(data))>>18)
#define SOFT_RESET2_get_rstn_i2c_5(data)                                             ((0x00040000&(data))>>18)
#define SOFT_RESET2_rstn_i2c_6_shift                                                 (17)
#define SOFT_RESET2_rstn_i2c_6_mask                                                  (0x00020000)
#define SOFT_RESET2_rstn_i2c_6(data)                                                 (0x00020000&((data)<<17))
#define SOFT_RESET2_rstn_i2c_6_src(data)                                             ((0x00020000&(data))>>17)
#define SOFT_RESET2_get_rstn_i2c_6(data)                                             ((0x00020000&(data))>>17)
#define SOFT_RESET2_rstn_cec0_shift                                                  (16)
#define SOFT_RESET2_rstn_cec0_mask                                                   (0x00010000)
#define SOFT_RESET2_rstn_cec0(data)                                                  (0x00010000&((data)<<16))
#define SOFT_RESET2_rstn_cec0_src(data)                                              ((0x00010000&(data))>>16)
#define SOFT_RESET2_get_rstn_cec0(data)                                              ((0x00010000&(data))>>16)
#define SOFT_RESET2_rstn_sdio_shift                                                  (12)
#define SOFT_RESET2_rstn_sdio_mask                                                   (0x00001000)
#define SOFT_RESET2_rstn_sdio(data)                                                  (0x00001000&((data)<<12))
#define SOFT_RESET2_rstn_sdio_src(data)                                              ((0x00001000&(data))>>12)
#define SOFT_RESET2_get_rstn_sdio(data)                                              ((0x00001000&(data))>>12)
#define SOFT_RESET2_rstn_emmc_shift                                                  (11)
#define SOFT_RESET2_rstn_emmc_mask                                                   (0x00000800)
#define SOFT_RESET2_rstn_emmc(data)                                                  (0x00000800&((data)<<11))
#define SOFT_RESET2_rstn_emmc_src(data)                                              ((0x00000800&(data))>>11)
#define SOFT_RESET2_get_rstn_emmc(data)                                              ((0x00000800&(data))>>11)
#define SOFT_RESET2_rstn_cr_shift                                                    (10)
#define SOFT_RESET2_rstn_cr_mask                                                     (0x00000400)
#define SOFT_RESET2_rstn_cr(data)                                                    (0x00000400&((data)<<10))
#define SOFT_RESET2_rstn_cr_src(data)                                                ((0x00000400&(data))>>10)
#define SOFT_RESET2_get_rstn_cr(data)                                                ((0x00000400&(data))>>10)
#define SOFT_RESET2_rstn_pcr_cnt_shift                                               (9)
#define SOFT_RESET2_rstn_pcr_cnt_mask                                                (0x00000200)
#define SOFT_RESET2_rstn_pcr_cnt(data)                                               (0x00000200&((data)<<9))
#define SOFT_RESET2_rstn_pcr_cnt_src(data)                                           ((0x00000200&(data))>>9)
#define SOFT_RESET2_get_rstn_pcr_cnt(data)                                           ((0x00000200&(data))>>9)
#define SOFT_RESET2_rstn_vde_shift                                                   (3)
#define SOFT_RESET2_rstn_vde_mask                                                    (0x00000008)
#define SOFT_RESET2_rstn_vde(data)                                                   (0x00000008&((data)<<3))
#define SOFT_RESET2_rstn_vde_src(data)                                               ((0x00000008&(data))>>3)
#define SOFT_RESET2_get_rstn_vde(data)                                               ((0x00000008&(data))>>3)
#define SOFT_RESET2_rstn_ade_shift                                                   (2)
#define SOFT_RESET2_rstn_ade_mask                                                    (0x00000004)
#define SOFT_RESET2_rstn_ade(data)                                                   (0x00000004&((data)<<2))
#define SOFT_RESET2_rstn_ade_src(data)                                               ((0x00000004&(data))>>2)
#define SOFT_RESET2_get_rstn_ade(data)                                               ((0x00000004&(data))>>2)
#define SOFT_RESET2_rstn_vcpu_shift                                                  (1)
#define SOFT_RESET2_rstn_vcpu_mask                                                   (0x00000002)
#define SOFT_RESET2_rstn_vcpu(data)                                                  (0x00000002&((data)<<1))
#define SOFT_RESET2_rstn_vcpu_src(data)                                              ((0x00000002&(data))>>1)
#define SOFT_RESET2_get_rstn_vcpu(data)                                              ((0x00000002&(data))>>1)
#define SOFT_RESET2_rstn_acpu_shift                                                  (0)
#define SOFT_RESET2_rstn_acpu_mask                                                   (0x00000001)
#define SOFT_RESET2_rstn_acpu(data)                                                  (0x00000001&((data)<<0))
#define SOFT_RESET2_rstn_acpu_src(data)                                              ((0x00000001&(data))>>0)
#define SOFT_RESET2_get_rstn_acpu(data)                                              ((0x00000001&(data))>>0)


#define SOFT_RESET3                                                                  0x98000008
#define SOFT_RESET3_reg_addr                                                         "0x98000008"
#define SOFT_RESET3_reg                                                              0x98000008
#define set_SOFT_RESET3_reg(data)   (*((volatile unsigned int*) SOFT_RESET3_reg)=data)
#define get_SOFT_RESET3_reg   (*((volatile unsigned int*) SOFT_RESET3_reg))
#define SOFT_RESET3_inst_adr                                                         "0x0002"
#define SOFT_RESET3_inst                                                             0x0002
#define SOFT_RESET3_rstn_sb2_shift                                                   (0)
#define SOFT_RESET3_rstn_sb2_mask                                                    (0x00000001)
#define SOFT_RESET3_rstn_sb2(data)                                                   (0x00000001&((data)<<0))
#define SOFT_RESET3_rstn_sb2_src(data)                                               ((0x00000001&(data))>>0)
#define SOFT_RESET3_get_rstn_sb2(data)                                               ((0x00000001&(data))>>0)


#define CLOCK_ENABLE1                                                                0x9800000C
#define CLOCK_ENABLE1_reg_addr                                                       "0x9800000C"
#define CLOCK_ENABLE1_reg                                                            0x9800000C
#define set_CLOCK_ENABLE1_reg(data)   (*((volatile unsigned int*) CLOCK_ENABLE1_reg)=data)
#define get_CLOCK_ENABLE1_reg   (*((volatile unsigned int*) CLOCK_ENABLE1_reg))
#define CLOCK_ENABLE1_inst_adr                                                       "0x0003"
#define CLOCK_ENABLE1_inst                                                           0x0003
#define CLOCK_ENABLE1_clk_en_sdio_shift                                              (30)
#define CLOCK_ENABLE1_clk_en_sdio_mask                                               (0x40000000)
#define CLOCK_ENABLE1_clk_en_sdio(data)                                              (0x40000000&((data)<<30))
#define CLOCK_ENABLE1_clk_en_sdio_src(data)                                          ((0x40000000&(data))>>30)
#define CLOCK_ENABLE1_get_clk_en_sdio(data)                                          ((0x40000000&(data))>>30)
#define CLOCK_ENABLE1_clk_en_ve_h265_shift                                           (29)
#define CLOCK_ENABLE1_clk_en_ve_h265_mask                                            (0x20000000)
#define CLOCK_ENABLE1_clk_en_ve_h265(data)                                           (0x20000000&((data)<<29))
#define CLOCK_ENABLE1_clk_en_ve_h265_src(data)                                       ((0x20000000&(data))>>29)
#define CLOCK_ENABLE1_get_clk_en_ve_h265(data)                                       ((0x20000000&(data))>>29)
#define CLOCK_ENABLE1_clk_en_cbustx_shift                                            (28)
#define CLOCK_ENABLE1_clk_en_cbustx_mask                                             (0x10000000)
#define CLOCK_ENABLE1_clk_en_cbustx(data)                                            (0x10000000&((data)<<28))
#define CLOCK_ENABLE1_clk_en_cbustx_src(data)                                        ((0x10000000&(data))>>28)
#define CLOCK_ENABLE1_get_clk_en_cbustx(data)                                        ((0x10000000&(data))>>28)
#define CLOCK_ENABLE1_clk_en_mipi_shift                                              (27)
#define CLOCK_ENABLE1_clk_en_mipi_mask                                               (0x08000000)
#define CLOCK_ENABLE1_clk_en_mipi(data)                                              (0x08000000&((data)<<27))
#define CLOCK_ENABLE1_clk_en_mipi_src(data)                                          ((0x08000000&(data))>>27)
#define CLOCK_ENABLE1_get_clk_en_mipi(data)                                          ((0x08000000&(data))>>27)
#define CLOCK_ENABLE1_clk_en_oobmac_shift                                            (26)
#define CLOCK_ENABLE1_clk_en_oobmac_mask                                             (0x04000000)
#define CLOCK_ENABLE1_clk_en_oobmac(data)                                            (0x04000000&((data)<<26))
#define CLOCK_ENABLE1_clk_en_oobmac_src(data)                                        ((0x04000000&(data))>>26)
#define CLOCK_ENABLE1_get_clk_en_oobmac(data)                                        ((0x04000000&(data))>>26)
#define CLOCK_ENABLE1_clk_en_cr_shift                                                (25)
#define CLOCK_ENABLE1_clk_en_cr_mask                                                 (0x02000000)
#define CLOCK_ENABLE1_clk_en_cr(data)                                                (0x02000000&((data)<<25))
#define CLOCK_ENABLE1_clk_en_cr_src(data)                                            ((0x02000000&(data))>>25)
#define CLOCK_ENABLE1_get_clk_en_cr(data)                                            ((0x02000000&(data))>>25)
#define CLOCK_ENABLE1_clk_en_emmc_shift                                              (24)
#define CLOCK_ENABLE1_clk_en_emmc_mask                                               (0x01000000)
#define CLOCK_ENABLE1_clk_en_emmc(data)                                              (0x01000000&((data)<<24))
#define CLOCK_ENABLE1_clk_en_emmc_src(data)                                          ((0x01000000&(data))>>24)
#define CLOCK_ENABLE1_get_clk_en_emmc(data)                                          ((0x01000000&(data))>>24)
#define CLOCK_ENABLE1_clk_en_nf_shift                                                (23)
#define CLOCK_ENABLE1_clk_en_nf_mask                                                 (0x00800000)
#define CLOCK_ENABLE1_clk_en_nf(data)                                                (0x00800000&((data)<<23))
#define CLOCK_ENABLE1_clk_en_nf_src(data)                                            ((0x00800000&(data))>>23)
#define CLOCK_ENABLE1_get_clk_en_nf(data)                                            ((0x00800000&(data))>>23)
#define CLOCK_ENABLE1_clk_en_ae_shift                                                (22)
#define CLOCK_ENABLE1_clk_en_ae_mask                                                 (0x00400000)
#define CLOCK_ENABLE1_clk_en_ae(data)                                                (0x00400000&((data)<<22))
#define CLOCK_ENABLE1_clk_en_ae_src(data)                                            ((0x00400000&(data))>>22)
#define CLOCK_ENABLE1_get_clk_en_ae(data)                                            ((0x00400000&(data))>>22)
#define CLOCK_ENABLE1_clk_en_tp_shift                                                (21)
#define CLOCK_ENABLE1_clk_en_tp_mask                                                 (0x00200000)
#define CLOCK_ENABLE1_clk_en_tp(data)                                                (0x00200000&((data)<<21))
#define CLOCK_ENABLE1_clk_en_tp_src(data)                                            ((0x00200000&(data))>>21)
#define CLOCK_ENABLE1_get_clk_en_tp(data)                                            ((0x00200000&(data))>>21)
#define CLOCK_ENABLE1_clk_en_md_shift                                                (20)
#define CLOCK_ENABLE1_clk_en_md_mask                                                 (0x00100000)
#define CLOCK_ENABLE1_clk_en_md(data)                                                (0x00100000&((data)<<20))
#define CLOCK_ENABLE1_clk_en_md_src(data)                                            ((0x00100000&(data))>>20)
#define CLOCK_ENABLE1_get_clk_en_md(data)                                            ((0x00100000&(data))>>20)
#define CLOCK_ENABLE1_clk_en_cp_shift                                                (19)
#define CLOCK_ENABLE1_clk_en_cp_mask                                                 (0x00080000)
#define CLOCK_ENABLE1_clk_en_cp(data)                                                (0x00080000&((data)<<19))
#define CLOCK_ENABLE1_clk_en_cp_src(data)                                            ((0x00080000&(data))>>19)
#define CLOCK_ENABLE1_get_clk_en_cp(data)                                            ((0x00080000&(data))>>19)
#define CLOCK_ENABLE1_clk_en_dcu_shift                                               (18)
#define CLOCK_ENABLE1_clk_en_dcu_mask                                                (0x00040000)
#define CLOCK_ENABLE1_clk_en_dcu(data)                                               (0x00040000&((data)<<18))
#define CLOCK_ENABLE1_clk_en_dcu_src(data)                                           ((0x00040000&(data))>>18)
#define CLOCK_ENABLE1_get_clk_en_dcu(data)                                           ((0x00040000&(data))>>18)
#define CLOCK_ENABLE1_clk_en_se_shift                                                (17)
#define CLOCK_ENABLE1_clk_en_se_mask                                                 (0x00020000)
#define CLOCK_ENABLE1_clk_en_se(data)                                                (0x00020000&((data)<<17))
#define CLOCK_ENABLE1_clk_en_se_src(data)                                            ((0x00020000&(data))>>17)
#define CLOCK_ENABLE1_get_clk_en_se(data)                                            ((0x00020000&(data))>>17)
#define CLOCK_ENABLE1_clk_en_lvds_shift                                              (16)
#define CLOCK_ENABLE1_clk_en_lvds_mask                                               (0x00010000)
#define CLOCK_ENABLE1_clk_en_lvds(data)                                              (0x00010000&((data)<<16))
#define CLOCK_ENABLE1_clk_en_lvds_src(data)                                          ((0x00010000&(data))>>16)
#define CLOCK_ENABLE1_get_clk_en_lvds(data)                                          ((0x00010000&(data))>>16)
#define CLOCK_ENABLE1_clk_en_vo_shift                                                (15)
#define CLOCK_ENABLE1_clk_en_vo_mask                                                 (0x00008000)
#define CLOCK_ENABLE1_clk_en_vo(data)                                                (0x00008000&((data)<<15))
#define CLOCK_ENABLE1_clk_en_vo_src(data)                                            ((0x00008000&(data))>>15)
#define CLOCK_ENABLE1_get_clk_en_vo(data)                                            ((0x00008000&(data))>>15)
#define CLOCK_ENABLE1_clk_en_tve_shift                                               (14)
#define CLOCK_ENABLE1_clk_en_tve_mask                                                (0x00004000)
#define CLOCK_ENABLE1_clk_en_tve(data)                                               (0x00004000&((data)<<14))
#define CLOCK_ENABLE1_clk_en_tve_src(data)                                           ((0x00004000&(data))>>14)
#define CLOCK_ENABLE1_get_clk_en_tve(data)                                           ((0x00004000&(data))>>14)
#define CLOCK_ENABLE1_clk_en_ve_jpeg_shift                                           (13)
#define CLOCK_ENABLE1_clk_en_ve_jpeg_mask                                            (0x00002000)
#define CLOCK_ENABLE1_clk_en_ve_jpeg(data)                                           (0x00002000&((data)<<13))
#define CLOCK_ENABLE1_clk_en_ve_jpeg_src(data)                                       ((0x00002000&(data))>>13)
#define CLOCK_ENABLE1_get_clk_en_ve_jpeg(data)                                       ((0x00002000&(data))>>13)
#define CLOCK_ENABLE1_clk_en_ve_h264_shift                                           (12)
#define CLOCK_ENABLE1_clk_en_ve_h264_mask                                            (0x00001000)
#define CLOCK_ENABLE1_clk_en_ve_h264(data)                                           (0x00001000&((data)<<12))
#define CLOCK_ENABLE1_clk_en_ve_h264_src(data)                                       ((0x00001000&(data))>>12)
#define CLOCK_ENABLE1_get_clk_en_ve_h264(data)                                       ((0x00001000&(data))>>12)
#define CLOCK_ENABLE1_clk_en_gpu_shift                                               (11)
#define CLOCK_ENABLE1_clk_en_gpu_mask                                                (0x00000800)
#define CLOCK_ENABLE1_clk_en_gpu(data)                                               (0x00000800&((data)<<11))
#define CLOCK_ENABLE1_clk_en_gpu_src(data)                                           ((0x00000800&(data))>>11)
#define CLOCK_ENABLE1_get_clk_en_gpu(data)                                           ((0x00000800&(data))>>11)
#define CLOCK_ENABLE1_clk_en_aio_shift                                               (10)
#define CLOCK_ENABLE1_clk_en_aio_mask                                                (0x00000400)
#define CLOCK_ENABLE1_clk_en_aio(data)                                               (0x00000400&((data)<<10))
#define CLOCK_ENABLE1_clk_en_aio_src(data)                                           ((0x00000400&(data))>>10)
#define CLOCK_ENABLE1_get_clk_en_aio(data)                                           ((0x00000400&(data))>>10)
#define CLOCK_ENABLE1_clk_en_etn_shift                                               (9)
#define CLOCK_ENABLE1_clk_en_etn_mask                                                (0x00000200)
#define CLOCK_ENABLE1_clk_en_etn(data)                                               (0x00000200&((data)<<9))
#define CLOCK_ENABLE1_clk_en_etn_src(data)                                           ((0x00000200&(data))>>9)
#define CLOCK_ENABLE1_get_clk_en_etn(data)                                           ((0x00000200&(data))>>9)
#define CLOCK_ENABLE1_clk_en_hdmi_shift                                              (8)
#define CLOCK_ENABLE1_clk_en_hdmi_mask                                               (0x00000100)
#define CLOCK_ENABLE1_clk_en_hdmi(data)                                              (0x00000100&((data)<<8))
#define CLOCK_ENABLE1_clk_en_hdmi_src(data)                                          ((0x00000100&(data))>>8)
#define CLOCK_ENABLE1_get_clk_en_hdmi(data)                                          ((0x00000100&(data))>>8)
#define CLOCK_ENABLE1_clk_en_etn_250m_shift                                          (7)
#define CLOCK_ENABLE1_clk_en_etn_250m_mask                                           (0x00000080)
#define CLOCK_ENABLE1_clk_en_etn_250m(data)                                          (0x00000080&((data)<<7))
#define CLOCK_ENABLE1_clk_en_etn_250m_src(data)                                      ((0x00000080&(data))>>7)
#define CLOCK_ENABLE1_get_clk_en_etn_250m(data)                                      ((0x00000080&(data))>>7)
#define CLOCK_ENABLE1_clk_en_iso_misc_shift                                          (6)
#define CLOCK_ENABLE1_clk_en_iso_misc_mask                                           (0x00000040)
#define CLOCK_ENABLE1_clk_en_iso_misc(data)                                          (0x00000040&((data)<<6))
#define CLOCK_ENABLE1_clk_en_iso_misc_src(data)                                      ((0x00000040&(data))>>6)
#define CLOCK_ENABLE1_get_clk_en_iso_misc(data)                                      ((0x00000040&(data))>>6)
#define CLOCK_ENABLE1_clk_en_pcr_shift                                               (5)
#define CLOCK_ENABLE1_clk_en_pcr_mask                                                (0x00000020)
#define CLOCK_ENABLE1_clk_en_pcr(data)                                               (0x00000020&((data)<<5))
#define CLOCK_ENABLE1_clk_en_pcr_src(data)                                           ((0x00000020&(data))>>5)
#define CLOCK_ENABLE1_get_clk_en_pcr(data)                                           ((0x00000020&(data))>>5)
#define CLOCK_ENABLE1_clk_en_usb_shift                                               (4)
#define CLOCK_ENABLE1_clk_en_usb_mask                                                (0x00000010)
#define CLOCK_ENABLE1_clk_en_usb(data)                                               (0x00000010&((data)<<4))
#define CLOCK_ENABLE1_clk_en_usb_src(data)                                           ((0x00000010&(data))>>4)
#define CLOCK_ENABLE1_get_clk_en_usb(data)                                           ((0x00000010&(data))>>4)
#define CLOCK_ENABLE1_clk_en_gspi_shift                                              (3)
#define CLOCK_ENABLE1_clk_en_gspi_mask                                               (0x00000008)
#define CLOCK_ENABLE1_clk_en_gspi(data)                                              (0x00000008&((data)<<3))
#define CLOCK_ENABLE1_clk_en_gspi_src(data)                                          ((0x00000008&(data))>>3)
#define CLOCK_ENABLE1_get_clk_en_gspi(data)                                          ((0x00000008&(data))>>3)
#define CLOCK_ENABLE1_clk_en_cbusrx_shift                                            (2)
#define CLOCK_ENABLE1_clk_en_cbusrx_mask                                             (0x00000004)
#define CLOCK_ENABLE1_clk_en_cbusrx(data)                                            (0x00000004&((data)<<2))
#define CLOCK_ENABLE1_clk_en_cbusrx_src(data)                                        ((0x00000004&(data))>>2)
#define CLOCK_ENABLE1_get_clk_en_cbusrx(data)                                        ((0x00000004&(data))>>2)
#define CLOCK_ENABLE1_clk_en_hdmirx_shift                                            (1)
#define CLOCK_ENABLE1_clk_en_hdmirx_mask                                             (0x00000002)
#define CLOCK_ENABLE1_clk_en_hdmirx(data)                                            (0x00000002&((data)<<1))
#define CLOCK_ENABLE1_clk_en_hdmirx_src(data)                                        ((0x00000002&(data))>>1)
#define CLOCK_ENABLE1_get_clk_en_hdmirx(data)                                        ((0x00000002&(data))>>1)
#define CLOCK_ENABLE1_clk_en_misc_shift                                              (0)
#define CLOCK_ENABLE1_clk_en_misc_mask                                               (0x00000001)
#define CLOCK_ENABLE1_clk_en_misc(data)                                              (0x00000001&((data)<<0))
#define CLOCK_ENABLE1_clk_en_misc_src(data)                                          ((0x00000001&(data))>>0)
#define CLOCK_ENABLE1_get_clk_en_misc(data)                                          ((0x00000001&(data))>>0)


#define CLOCK_ENABLE2                                                                0x98000010
#define CLOCK_ENABLE2_reg_addr                                                       "0x98000010"
#define CLOCK_ENABLE2_reg                                                            0x98000010
#define set_CLOCK_ENABLE2_reg(data)   (*((volatile unsigned int*) CLOCK_ENABLE2_reg)=data)
#define get_CLOCK_ENABLE2_reg   (*((volatile unsigned int*) CLOCK_ENABLE2_reg))
#define CLOCK_ENABLE2_inst_adr                                                       "0x0004"
#define CLOCK_ENABLE2_inst                                                           0x0004
#define CLOCK_ENABLE2_clk_en_ur0_shift                                               (29)
#define CLOCK_ENABLE2_clk_en_ur0_mask                                                (0x20000000)
#define CLOCK_ENABLE2_clk_en_ur0(data)                                               (0x20000000&((data)<<29))
#define CLOCK_ENABLE2_clk_en_ur0_src(data)                                           ((0x20000000&(data))>>29)
#define CLOCK_ENABLE2_get_clk_en_ur0(data)                                           ((0x20000000&(data))>>29)
#define CLOCK_ENABLE2_clk_en_ur1_shift                                               (28)
#define CLOCK_ENABLE2_clk_en_ur1_mask                                                (0x10000000)
#define CLOCK_ENABLE2_clk_en_ur1(data)                                               (0x10000000&((data)<<28))
#define CLOCK_ENABLE2_clk_en_ur1_src(data)                                           ((0x10000000&(data))>>28)
#define CLOCK_ENABLE2_get_clk_en_ur1(data)                                           ((0x10000000&(data))>>28)
#define CLOCK_ENABLE2_clk_en_misc_i2c_0_shift                                        (24)
#define CLOCK_ENABLE2_clk_en_misc_i2c_0_mask                                         (0x01000000)
#define CLOCK_ENABLE2_clk_en_misc_i2c_0(data)                                        (0x01000000&((data)<<24))
#define CLOCK_ENABLE2_clk_en_misc_i2c_0_src(data)                                    ((0x01000000&(data))>>24)
#define CLOCK_ENABLE2_get_clk_en_misc_i2c_0(data)                                    ((0x01000000&(data))>>24)
#define CLOCK_ENABLE2_clk_en_aio_mclk_shift                                          (23)
#define CLOCK_ENABLE2_clk_en_aio_mclk_mask                                           (0x00800000)
#define CLOCK_ENABLE2_clk_en_aio_mclk(data)                                          (0x00800000&((data)<<23))
#define CLOCK_ENABLE2_clk_en_aio_mclk_src(data)                                      ((0x00800000&(data))>>23)
#define CLOCK_ENABLE2_get_clk_en_aio_mclk(data)                                      ((0x00800000&(data))>>23)
#define CLOCK_ENABLE2_clk_en_aio_i2s_shift                                           (22)
#define CLOCK_ENABLE2_clk_en_aio_i2s_mask                                            (0x00400000)
#define CLOCK_ENABLE2_clk_en_aio_i2s(data)                                           (0x00400000&((data)<<22))
#define CLOCK_ENABLE2_clk_en_aio_i2s_src(data)                                       ((0x00400000&(data))>>22)
#define CLOCK_ENABLE2_get_clk_en_aio_i2s(data)                                       ((0x00400000&(data))>>22)
#define CLOCK_ENABLE2_clk_en_aio_spdif_shift                                         (21)
#define CLOCK_ENABLE2_clk_en_aio_spdif_mask                                          (0x00200000)
#define CLOCK_ENABLE2_clk_en_aio_spdif(data)                                         (0x00200000&((data)<<21))
#define CLOCK_ENABLE2_clk_en_aio_spdif_src(data)                                     ((0x00200000&(data))>>21)
#define CLOCK_ENABLE2_get_clk_en_aio_spdif(data)                                     ((0x00200000&(data))>>21)
#define CLOCK_ENABLE2_clk_en_aio_hdmi_shift                                          (20)
#define CLOCK_ENABLE2_clk_en_aio_hdmi_mask                                           (0x00100000)
#define CLOCK_ENABLE2_clk_en_aio_hdmi(data)                                          (0x00100000&((data)<<20))
#define CLOCK_ENABLE2_clk_en_aio_hdmi_src(data)                                      ((0x00100000&(data))>>20)
#define CLOCK_ENABLE2_get_clk_en_aio_hdmi(data)                                      ((0x00100000&(data))>>20)
#define CLOCK_ENABLE2_clk_en_aio_da_shift                                            (19)
#define CLOCK_ENABLE2_clk_en_aio_da_mask                                             (0x00080000)
#define CLOCK_ENABLE2_clk_en_aio_da(data)                                            (0x00080000&((data)<<19))
#define CLOCK_ENABLE2_clk_en_aio_da_src(data)                                        ((0x00080000&(data))>>19)
#define CLOCK_ENABLE2_get_clk_en_aio_da(data)                                        ((0x00080000&(data))>>19)
#define CLOCK_ENABLE2_clk_en_aio_mod_shift                                           (18)
#define CLOCK_ENABLE2_clk_en_aio_mod_mask                                            (0x00040000)
#define CLOCK_ENABLE2_clk_en_aio_mod(data)                                           (0x00040000&((data)<<18))
#define CLOCK_ENABLE2_clk_en_aio_mod_src(data)                                       ((0x00040000&(data))>>18)
#define CLOCK_ENABLE2_get_clk_en_aio_mod(data)                                       ((0x00040000&(data))>>18)
#define CLOCK_ENABLE2_clk_en_aio_au_codec_shift                                      (17)
#define CLOCK_ENABLE2_clk_en_aio_au_codec_mask                                       (0x00020000)
#define CLOCK_ENABLE2_clk_en_aio_au_codec(data)                                      (0x00020000&((data)<<17))
#define CLOCK_ENABLE2_clk_en_aio_au_codec_src(data)                                  ((0x00020000&(data))>>17)
#define CLOCK_ENABLE2_get_clk_en_aio_au_codec(data)                                  ((0x00020000&(data))>>17)
#define CLOCK_ENABLE2_clk_en_misc_i2c_1_shift                                        (16)
#define CLOCK_ENABLE2_clk_en_misc_i2c_1_mask                                         (0x00010000)
#define CLOCK_ENABLE2_clk_en_misc_i2c_1(data)                                        (0x00010000&((data)<<16))
#define CLOCK_ENABLE2_clk_en_misc_i2c_1_src(data)                                    ((0x00010000&(data))>>16)
#define CLOCK_ENABLE2_get_clk_en_misc_i2c_1(data)                                    ((0x00010000&(data))>>16)
#define CLOCK_ENABLE2_clk_en_misc_i2c_2_shift                                        (15)
#define CLOCK_ENABLE2_clk_en_misc_i2c_2_mask                                         (0x00008000)
#define CLOCK_ENABLE2_clk_en_misc_i2c_2(data)                                        (0x00008000&((data)<<15))
#define CLOCK_ENABLE2_clk_en_misc_i2c_2_src(data)                                    ((0x00008000&(data))>>15)
#define CLOCK_ENABLE2_get_clk_en_misc_i2c_2(data)                                    ((0x00008000&(data))>>15)
#define CLOCK_ENABLE2_clk_en_misc_i2c_3_shift                                        (14)
#define CLOCK_ENABLE2_clk_en_misc_i2c_3_mask                                         (0x00004000)
#define CLOCK_ENABLE2_clk_en_misc_i2c_3(data)                                        (0x00004000&((data)<<14))
#define CLOCK_ENABLE2_clk_en_misc_i2c_3_src(data)                                    ((0x00004000&(data))>>14)
#define CLOCK_ENABLE2_get_clk_en_misc_i2c_3(data)                                    ((0x00004000&(data))>>14)
#define CLOCK_ENABLE2_clk_en_misc_i2c_4_shift                                        (13)
#define CLOCK_ENABLE2_clk_en_misc_i2c_4_mask                                         (0x00002000)
#define CLOCK_ENABLE2_clk_en_misc_i2c_4(data)                                        (0x00002000&((data)<<13))
#define CLOCK_ENABLE2_clk_en_misc_i2c_4_src(data)                                    ((0x00002000&(data))>>13)
#define CLOCK_ENABLE2_get_clk_en_misc_i2c_4(data)                                    ((0x00002000&(data))>>13)
#define CLOCK_ENABLE2_clk_en_misc_ir_shift                                           (12)
#define CLOCK_ENABLE2_clk_en_misc_ir_mask                                            (0x00001000)
#define CLOCK_ENABLE2_clk_en_misc_ir(data)                                           (0x00001000&((data)<<12))
#define CLOCK_ENABLE2_clk_en_misc_ir_src(data)                                       ((0x00001000&(data))>>12)
#define CLOCK_ENABLE2_get_clk_en_misc_ir(data)                                       ((0x00001000&(data))>>12)
#define CLOCK_ENABLE2_clk_en_misc_cec1_shift                                         (11)
#define CLOCK_ENABLE2_clk_en_misc_cec1_mask                                          (0x00000800)
#define CLOCK_ENABLE2_clk_en_misc_cec1(data)                                         (0x00000800&((data)<<11))
#define CLOCK_ENABLE2_clk_en_misc_cec1_src(data)                                     ((0x00000800&(data))>>11)
#define CLOCK_ENABLE2_get_clk_en_misc_cec1(data)                                     ((0x00000800&(data))>>11)
#define CLOCK_ENABLE2_clk_en_misc_rtc_shift                                          (10)
#define CLOCK_ENABLE2_clk_en_misc_rtc_mask                                           (0x00000400)
#define CLOCK_ENABLE2_clk_en_misc_rtc(data)                                          (0x00000400&((data)<<10))
#define CLOCK_ENABLE2_clk_en_misc_rtc_src(data)                                      ((0x00000400&(data))>>10)
#define CLOCK_ENABLE2_get_clk_en_misc_rtc(data)                                      ((0x00000400&(data))>>10)
#define CLOCK_ENABLE2_clk_en_misc_vfd_shift                                          (9)
#define CLOCK_ENABLE2_clk_en_misc_vfd_mask                                           (0x00000200)
#define CLOCK_ENABLE2_clk_en_misc_vfd(data)                                          (0x00000200&((data)<<9))
#define CLOCK_ENABLE2_clk_en_misc_vfd_src(data)                                      ((0x00000200&(data))>>9)
#define CLOCK_ENABLE2_get_clk_en_misc_vfd(data)                                      ((0x00000200&(data))>>9)
#define CLOCK_ENABLE2_clk_en_misc_cec0_shift                                         (8)
#define CLOCK_ENABLE2_clk_en_misc_cec0_mask                                          (0x00000100)
#define CLOCK_ENABLE2_clk_en_misc_cec0(data)                                         (0x00000100&((data)<<8))
#define CLOCK_ENABLE2_clk_en_misc_cec0_src(data)                                     ((0x00000100&(data))>>8)
#define CLOCK_ENABLE2_get_clk_en_misc_cec0(data)                                     ((0x00000100&(data))>>8)
#define CLOCK_ENABLE2_clk_en_vde_shift                                               (7)
#define CLOCK_ENABLE2_clk_en_vde_mask                                                (0x00000080)
#define CLOCK_ENABLE2_clk_en_vde(data)                                               (0x00000080&((data)<<7))
#define CLOCK_ENABLE2_clk_en_vde_src(data)                                           ((0x00000080&(data))>>7)
#define CLOCK_ENABLE2_get_clk_en_vde(data)                                           ((0x00000080&(data))>>7)
#define CLOCK_ENABLE2_clk_en_ade_shift                                               (6)
#define CLOCK_ENABLE2_clk_en_ade_mask                                                (0x00000040)
#define CLOCK_ENABLE2_clk_en_ade(data)                                               (0x00000040&((data)<<6))
#define CLOCK_ENABLE2_clk_en_ade_src(data)                                           ((0x00000040&(data))>>6)
#define CLOCK_ENABLE2_get_clk_en_ade(data)                                           ((0x00000040&(data))>>6)
#define CLOCK_ENABLE2_clk_en_vcpu_shift                                              (5)
#define CLOCK_ENABLE2_clk_en_vcpu_mask                                               (0x00000020)
#define CLOCK_ENABLE2_clk_en_vcpu(data)                                              (0x00000020&((data)<<5))
#define CLOCK_ENABLE2_clk_en_vcpu_src(data)                                          ((0x00000020&(data))>>5)
#define CLOCK_ENABLE2_get_clk_en_vcpu(data)                                          ((0x00000020&(data))>>5)
#define CLOCK_ENABLE2_clk_en_acpu_shift                                              (4)
#define CLOCK_ENABLE2_clk_en_acpu_mask                                               (0x00000010)
#define CLOCK_ENABLE2_clk_en_acpu(data)                                              (0x00000010&((data)<<4))
#define CLOCK_ENABLE2_clk_en_acpu_src(data)                                          ((0x00000010&(data))>>4)
#define CLOCK_ENABLE2_get_clk_en_acpu(data)                                          ((0x00000010&(data))>>4)
#define CLOCK_ENABLE2_clk_en_dp_shift                                                (3)
#define CLOCK_ENABLE2_clk_en_dp_mask                                                 (0x00000008)
#define CLOCK_ENABLE2_clk_en_dp(data)                                                (0x00000008&((data)<<3))
#define CLOCK_ENABLE2_clk_en_dp_src(data)                                            ((0x00000008&(data))>>3)
#define CLOCK_ENABLE2_get_clk_en_dp(data)                                            ((0x00000008&(data))>>3)
#define CLOCK_ENABLE2_clk_en_scpu_shift                                              (2)
#define CLOCK_ENABLE2_clk_en_scpu_mask                                               (0x00000004)
#define CLOCK_ENABLE2_clk_en_scpu(data)                                              (0x00000004&((data)<<2))
#define CLOCK_ENABLE2_clk_en_scpu_src(data)                                          ((0x00000004&(data))>>2)
#define CLOCK_ENABLE2_get_clk_en_scpu(data)                                          ((0x00000004&(data))>>2)
#define CLOCK_ENABLE2_clk_en_misc_i2c_5_shift                                        (1)
#define CLOCK_ENABLE2_clk_en_misc_i2c_5_mask                                         (0x00000002)
#define CLOCK_ENABLE2_clk_en_misc_i2c_5(data)                                        (0x00000002&((data)<<1))
#define CLOCK_ENABLE2_clk_en_misc_i2c_5_src(data)                                    ((0x00000002&(data))>>1)
#define CLOCK_ENABLE2_get_clk_en_misc_i2c_5(data)                                    ((0x00000002&(data))>>1)
#define CLOCK_ENABLE2_clk_en_misc_i2c_6_shift                                        (0)
#define CLOCK_ENABLE2_clk_en_misc_i2c_6_mask                                         (0x00000001)
#define CLOCK_ENABLE2_clk_en_misc_i2c_6(data)                                        (0x00000001&((data)<<0))
#define CLOCK_ENABLE2_clk_en_misc_i2c_6_src(data)                                    ((0x00000001&(data))>>0)
#define CLOCK_ENABLE2_get_clk_en_misc_i2c_6(data)                                    ((0x00000001&(data))>>0)


#define GROUP1_CK_EN                                                                 0x98000014
#define GROUP1_CK_EN_reg_addr                                                        "0x98000014"
#define GROUP1_CK_EN_reg                                                             0x98000014
#define set_GROUP1_CK_EN_reg(data)   (*((volatile unsigned int*) GROUP1_CK_EN_reg)=data)
#define get_GROUP1_CK_EN_reg   (*((volatile unsigned int*) GROUP1_CK_EN_reg))
#define GROUP1_CK_EN_inst_adr                                                        "0x0005"
#define GROUP1_CK_EN_inst                                                            0x0005
#define GROUP1_CK_EN_clk_en_kcpu_shift                                               (1)
#define GROUP1_CK_EN_clk_en_kcpu_mask                                                (0x00000002)
#define GROUP1_CK_EN_clk_en_kcpu(data)                                               (0x00000002&((data)<<1))
#define GROUP1_CK_EN_clk_en_kcpu_src(data)                                           ((0x00000002&(data))>>1)
#define GROUP1_CK_EN_get_clk_en_kcpu(data)                                           ((0x00000002&(data))>>1)
#define GROUP1_CK_EN_clk_en_sb2_shift                                                (0)
#define GROUP1_CK_EN_clk_en_sb2_mask                                                 (0x00000001)
#define GROUP1_CK_EN_clk_en_sb2(data)                                                (0x00000001&((data)<<0))
#define GROUP1_CK_EN_clk_en_sb2_src(data)                                            ((0x00000001&(data))>>0)
#define GROUP1_CK_EN_get_clk_en_sb2(data)                                            ((0x00000001&(data))>>0)


#define GROUP1_CK_SEL                                                                0x98000018
#define GROUP1_CK_SEL_reg_addr                                                       "0x98000018"
#define GROUP1_CK_SEL_reg                                                            0x98000018
#define set_GROUP1_CK_SEL_reg(data)   (*((volatile unsigned int*) GROUP1_CK_SEL_reg)=data)
#define get_GROUP1_CK_SEL_reg   (*((volatile unsigned int*) GROUP1_CK_SEL_reg))
#define GROUP1_CK_SEL_inst_adr                                                       "0x0006"
#define GROUP1_CK_SEL_inst                                                           0x0006
#define GROUP1_CK_SEL_voclk_sel_shift                                                (1)
#define GROUP1_CK_SEL_voclk_sel_mask                                                 (0x00000002)
#define GROUP1_CK_SEL_voclk_sel(data)                                                (0x00000002&((data)<<1))
#define GROUP1_CK_SEL_voclk_sel_src(data)                                            ((0x00000002&(data))>>1)
#define GROUP1_CK_SEL_get_voclk_sel(data)                                            ((0x00000002&(data))>>1)
#define GROUP1_CK_SEL_sclk_sel_shift                                                 (0)
#define GROUP1_CK_SEL_sclk_sel_mask                                                  (0x00000001)
#define GROUP1_CK_SEL_sclk_sel(data)                                                 (0x00000001&((data)<<0))
#define GROUP1_CK_SEL_sclk_sel_src(data)                                             ((0x00000001&(data))>>0)
#define GROUP1_CK_SEL_get_sclk_sel(data)                                             ((0x00000001&(data))>>0)


#define TVE_CK_SEL                                                                   0x9800001C
#define TVE_CK_SEL_reg_addr                                                          "0x9800001C"
#define TVE_CK_SEL_reg                                                               0x9800001C
#define set_TVE_CK_SEL_reg(data)   (*((volatile unsigned int*) TVE_CK_SEL_reg)=data)
#define get_TVE_CK_SEL_reg   (*((volatile unsigned int*) TVE_CK_SEL_reg))
#define TVE_CK_SEL_inst_adr                                                          "0x0007"
#define TVE_CK_SEL_inst                                                              0x0007
#define TVE_CK_SEL_write_en5_shift                                                   (12)
#define TVE_CK_SEL_write_en5_mask                                                    (0x00001000)
#define TVE_CK_SEL_write_en5(data)                                                   (0x00001000&((data)<<12))
#define TVE_CK_SEL_write_en5_src(data)                                               ((0x00001000&(data))>>12)
#define TVE_CK_SEL_get_write_en5(data)                                               ((0x00001000&(data))>>12)
#define TVE_CK_SEL_clk_tve_p_vo_clk_sel2_shift                                       (11)
#define TVE_CK_SEL_clk_tve_p_vo_clk_sel2_mask                                        (0x00000800)
#define TVE_CK_SEL_clk_tve_p_vo_clk_sel2(data)                                       (0x00000800&((data)<<11))
#define TVE_CK_SEL_clk_tve_p_vo_clk_sel2_src(data)                                   ((0x00000800&(data))>>11)
#define TVE_CK_SEL_get_clk_tve_p_vo_clk_sel2(data)                                   ((0x00000800&(data))>>11)
#define TVE_CK_SEL_write_en4_shift                                                   (10)
#define TVE_CK_SEL_write_en4_mask                                                    (0x00000400)
#define TVE_CK_SEL_write_en4(data)                                                   (0x00000400&((data)<<10))
#define TVE_CK_SEL_write_en4_src(data)                                               ((0x00000400&(data))>>10)
#define TVE_CK_SEL_get_write_en4(data)                                               ((0x00000400&(data))>>10)
#define TVE_CK_SEL_clk_tve_p_vo_clk_sel_shift                                        (9)
#define TVE_CK_SEL_clk_tve_p_vo_clk_sel_mask                                         (0x00000200)
#define TVE_CK_SEL_clk_tve_p_vo_clk_sel(data)                                        (0x00000200&((data)<<9))
#define TVE_CK_SEL_clk_tve_p_vo_clk_sel_src(data)                                    ((0x00000200&(data))>>9)
#define TVE_CK_SEL_get_clk_tve_p_vo_clk_sel(data)                                    ((0x00000200&(data))>>9)
#define TVE_CK_SEL_write_en3_shift                                                   (8)
#define TVE_CK_SEL_write_en3_mask                                                    (0x00000100)
#define TVE_CK_SEL_write_en3(data)                                                   (0x00000100&((data)<<8))
#define TVE_CK_SEL_write_en3_src(data)                                               ((0x00000100&(data))>>8)
#define TVE_CK_SEL_get_write_en3(data)                                               ((0x00000100&(data))>>8)
#define TVE_CK_SEL_hdmi_phy_ckinv_shift                                              (7)
#define TVE_CK_SEL_hdmi_phy_ckinv_mask                                               (0x00000080)
#define TVE_CK_SEL_hdmi_phy_ckinv(data)                                              (0x00000080&((data)<<7))
#define TVE_CK_SEL_hdmi_phy_ckinv_src(data)                                          ((0x00000080&(data))>>7)
#define TVE_CK_SEL_get_hdmi_phy_ckinv(data)                                          ((0x00000080&(data))>>7)
#define TVE_CK_SEL_write_en2_shift                                                   (6)
#define TVE_CK_SEL_write_en2_mask                                                    (0x00000040)
#define TVE_CK_SEL_write_en2(data)                                                   (0x00000040&((data)<<6))
#define TVE_CK_SEL_write_en2_src(data)                                               ((0x00000040&(data))>>6)
#define TVE_CK_SEL_get_write_en2(data)                                               ((0x00000040&(data))>>6)
#define TVE_CK_SEL_dac2_ckinv_shift                                                  (3)
#define TVE_CK_SEL_dac2_ckinv_mask                                                   (0x00000008)
#define TVE_CK_SEL_dac2_ckinv(data)                                                  (0x00000008&((data)<<3))
#define TVE_CK_SEL_dac2_ckinv_src(data)                                              ((0x00000008&(data))>>3)
#define TVE_CK_SEL_get_dac2_ckinv(data)                                              ((0x00000008&(data))>>3)
#define TVE_CK_SEL_dac1_ckinv_shift                                                  (2)
#define TVE_CK_SEL_dac1_ckinv_mask                                                   (0x00000004)
#define TVE_CK_SEL_dac1_ckinv(data)                                                  (0x00000004&((data)<<2))
#define TVE_CK_SEL_dac1_ckinv_src(data)                                              ((0x00000004&(data))>>2)
#define TVE_CK_SEL_get_dac1_ckinv(data)                                              ((0x00000004&(data))>>2)
#define TVE_CK_SEL_write_en1_shift                                                   (1)
#define TVE_CK_SEL_write_en1_mask                                                    (0x00000002)
#define TVE_CK_SEL_write_en1(data)                                                   (0x00000002&((data)<<1))
#define TVE_CK_SEL_write_en1_src(data)                                               ((0x00000002&(data))>>1)
#define TVE_CK_SEL_get_write_en1(data)                                               ((0x00000002&(data))>>1)
#define TVE_CK_SEL_tveck_mix_sel_shift                                               (0)
#define TVE_CK_SEL_tveck_mix_sel_mask                                                (0x00000001)
#define TVE_CK_SEL_tveck_mix_sel(data)                                               (0x00000001&((data)<<0))
#define TVE_CK_SEL_tveck_mix_sel_src(data)                                           ((0x00000001&(data))>>0)
#define TVE_CK_SEL_get_tveck_mix_sel(data)                                           ((0x00000001&(data))>>0)


#define DISP_PLL_DIV                                                                 0x98000020
#define DISP_PLL_DIV_reg_addr                                                        "0x98000020"
#define DISP_PLL_DIV_reg                                                             0x98000020
#define set_DISP_PLL_DIV_reg(data)   (*((volatile unsigned int*) DISP_PLL_DIV_reg)=data)
#define get_DISP_PLL_DIV_reg   (*((volatile unsigned int*) DISP_PLL_DIV_reg))
#define DISP_PLL_DIV_inst_adr                                                        "0x0008"
#define DISP_PLL_DIV_inst                                                            0x0008
#define DISP_PLL_DIV_write_en2_shift                                                 (11)
#define DISP_PLL_DIV_write_en2_mask                                                  (0x00000800)
#define DISP_PLL_DIV_write_en2(data)                                                 (0x00000800&((data)<<11))
#define DISP_PLL_DIV_write_en2_src(data)                                             ((0x00000800&(data))>>11)
#define DISP_PLL_DIV_get_write_en2(data)                                             ((0x00000800&(data))>>11)
#define DISP_PLL_DIV_dac2_div_shift                                                  (6)
#define DISP_PLL_DIV_dac2_div_mask                                                   (0x000007C0)
#define DISP_PLL_DIV_dac2_div(data)                                                  (0x000007C0&((data)<<6))
#define DISP_PLL_DIV_dac2_div_src(data)                                              ((0x000007C0&(data))>>6)
#define DISP_PLL_DIV_get_dac2_div(data)                                              ((0x000007C0&(data))>>6)
#define DISP_PLL_DIV_write_en1_shift                                                 (5)
#define DISP_PLL_DIV_write_en1_mask                                                  (0x00000020)
#define DISP_PLL_DIV_write_en1(data)                                                 (0x00000020&((data)<<5))
#define DISP_PLL_DIV_write_en1_src(data)                                             ((0x00000020&(data))>>5)
#define DISP_PLL_DIV_get_write_en1(data)                                             ((0x00000020&(data))>>5)
#define DISP_PLL_DIV_dac1_div_shift                                                  (0)
#define DISP_PLL_DIV_dac1_div_mask                                                   (0x0000001F)
#define DISP_PLL_DIV_dac1_div(data)                                                  (0x0000001F&((data)<<0))
#define DISP_PLL_DIV_dac1_div_src(data)                                              ((0x0000001F&(data))>>0)
#define DISP_PLL_DIV_get_dac1_div(data)                                              ((0x0000001F&(data))>>0)


#define DISP_PLL_DIV2                                                                0x98000024
#define DISP_PLL_DIV2_reg_addr                                                       "0x98000024"
#define DISP_PLL_DIV2_reg                                                            0x98000024
#define set_DISP_PLL_DIV2_reg(data)   (*((volatile unsigned int*) DISP_PLL_DIV2_reg)=data)
#define get_DISP_PLL_DIV2_reg   (*((volatile unsigned int*) DISP_PLL_DIV2_reg))
#define DISP_PLL_DIV2_inst_adr                                                       "0x0009"
#define DISP_PLL_DIV2_inst                                                           0x0009
#define DISP_PLL_DIV2_write_en10_shift                                               (24)
#define DISP_PLL_DIV2_write_en10_mask                                                (0x01000000)
#define DISP_PLL_DIV2_write_en10(data)                                               (0x01000000&((data)<<24))
#define DISP_PLL_DIV2_write_en10_src(data)                                           ((0x01000000&(data))>>24)
#define DISP_PLL_DIV2_get_write_en10(data)                                           ((0x01000000&(data))>>24)
#define DISP_PLL_DIV2_sel_pllhdmi_mhl_shift                                          (23)
#define DISP_PLL_DIV2_sel_pllhdmi_mhl_mask                                           (0x00800000)
#define DISP_PLL_DIV2_sel_pllhdmi_mhl(data)                                          (0x00800000&((data)<<23))
#define DISP_PLL_DIV2_sel_pllhdmi_mhl_src(data)                                      ((0x00800000&(data))>>23)
#define DISP_PLL_DIV2_get_sel_pllhdmi_mhl(data)                                      ((0x00800000&(data))>>23)
#define DISP_PLL_DIV2_write_en9_shift                                                (22)
#define DISP_PLL_DIV2_write_en9_mask                                                 (0x00400000)
#define DISP_PLL_DIV2_write_en9(data)                                                (0x00400000&((data)<<22))
#define DISP_PLL_DIV2_write_en9_src(data)                                            ((0x00400000&(data))>>22)
#define DISP_PLL_DIV2_get_write_en9(data)                                            ((0x00400000&(data))>>22)
#define DISP_PLL_DIV2_clk_lvds_sel_shift                                             (17)
#define DISP_PLL_DIV2_clk_lvds_sel_mask                                              (0x003E0000)
#define DISP_PLL_DIV2_clk_lvds_sel(data)                                             (0x003E0000&((data)<<17))
#define DISP_PLL_DIV2_clk_lvds_sel_src(data)                                         ((0x003E0000&(data))>>17)
#define DISP_PLL_DIV2_get_clk_lvds_sel(data)                                         ((0x003E0000&(data))>>17)
#define DISP_PLL_DIV2_write_en8_shift                                                (16)
#define DISP_PLL_DIV2_write_en8_mask                                                 (0x00010000)
#define DISP_PLL_DIV2_write_en8(data)                                                (0x00010000&((data)<<16))
#define DISP_PLL_DIV2_write_en8_src(data)                                            ((0x00010000&(data))>>16)
#define DISP_PLL_DIV2_get_write_en8(data)                                            ((0x00010000&(data))>>16)
#define DISP_PLL_DIV2_sel_plldisp_clk2_shift                                         (15)
#define DISP_PLL_DIV2_sel_plldisp_clk2_mask                                          (0x00008000)
#define DISP_PLL_DIV2_sel_plldisp_clk2(data)                                         (0x00008000&((data)<<15))
#define DISP_PLL_DIV2_sel_plldisp_clk2_src(data)                                     ((0x00008000&(data))>>15)
#define DISP_PLL_DIV2_get_sel_plldisp_clk2(data)                                     ((0x00008000&(data))>>15)
#define DISP_PLL_DIV2_write_en7_shift                                                (14)
#define DISP_PLL_DIV2_write_en7_mask                                                 (0x00004000)
#define DISP_PLL_DIV2_write_en7(data)                                                (0x00004000&((data)<<14))
#define DISP_PLL_DIV2_write_en7_src(data)                                            ((0x00004000&(data))>>14)
#define DISP_PLL_DIV2_get_write_en7(data)                                            ((0x00004000&(data))>>14)
#define DISP_PLL_DIV2_sel_pllhdmi_clk_shift                                          (13)
#define DISP_PLL_DIV2_sel_pllhdmi_clk_mask                                           (0x00002000)
#define DISP_PLL_DIV2_sel_pllhdmi_clk(data)                                          (0x00002000&((data)<<13))
#define DISP_PLL_DIV2_sel_pllhdmi_clk_src(data)                                      ((0x00002000&(data))>>13)
#define DISP_PLL_DIV2_get_sel_pllhdmi_clk(data)                                      ((0x00002000&(data))>>13)
#define DISP_PLL_DIV2_write_en6_shift                                                (12)
#define DISP_PLL_DIV2_write_en6_mask                                                 (0x00001000)
#define DISP_PLL_DIV2_write_en6(data)                                                (0x00001000&((data)<<12))
#define DISP_PLL_DIV2_write_en6_src(data)                                            ((0x00001000&(data))>>12)
#define DISP_PLL_DIV2_get_write_en6(data)                                            ((0x00001000&(data))>>12)
#define DISP_PLL_DIV2_hdmi_pxl_repeat_shift                                          (11)
#define DISP_PLL_DIV2_hdmi_pxl_repeat_mask                                           (0x00000800)
#define DISP_PLL_DIV2_hdmi_pxl_repeat(data)                                          (0x00000800&((data)<<11))
#define DISP_PLL_DIV2_hdmi_pxl_repeat_src(data)                                      ((0x00000800&(data))>>11)
#define DISP_PLL_DIV2_get_hdmi_pxl_repeat(data)                                      ((0x00000800&(data))>>11)
#define DISP_PLL_DIV2_write_en5_shift                                                (10)
#define DISP_PLL_DIV2_write_en5_mask                                                 (0x00000400)
#define DISP_PLL_DIV2_write_en5(data)                                                (0x00000400&((data)<<10))
#define DISP_PLL_DIV2_write_en5_src(data)                                            ((0x00000400&(data))>>10)
#define DISP_PLL_DIV2_get_write_en5(data)                                            ((0x00000400&(data))>>10)
#define DISP_PLL_DIV2_hdmi_phy_clk_sel_shift                                         (9)
#define DISP_PLL_DIV2_hdmi_phy_clk_sel_mask                                          (0x00000200)
#define DISP_PLL_DIV2_hdmi_phy_clk_sel(data)                                         (0x00000200&((data)<<9))
#define DISP_PLL_DIV2_hdmi_phy_clk_sel_src(data)                                     ((0x00000200&(data))>>9)
#define DISP_PLL_DIV2_get_hdmi_phy_clk_sel(data)                                     ((0x00000200&(data))>>9)
#define DISP_PLL_DIV2_write_en4_shift                                                (8)
#define DISP_PLL_DIV2_write_en4_mask                                                 (0x00000100)
#define DISP_PLL_DIV2_write_en4(data)                                                (0x00000100&((data)<<8))
#define DISP_PLL_DIV2_write_en4_src(data)                                            ((0x00000100&(data))>>8)
#define DISP_PLL_DIV2_get_write_en4(data)                                            ((0x00000100&(data))>>8)
#define DISP_PLL_DIV2_hdmi_div_shift                                                 (5)
#define DISP_PLL_DIV2_hdmi_div_mask                                                  (0x000000E0)
#define DISP_PLL_DIV2_hdmi_div(data)                                                 (0x000000E0&((data)<<5))
#define DISP_PLL_DIV2_hdmi_div_src(data)                                             ((0x000000E0&(data))>>5)
#define DISP_PLL_DIV2_get_hdmi_div(data)                                             ((0x000000E0&(data))>>5)
#define DISP_PLL_DIV2_write_en3_shift                                                (4)
#define DISP_PLL_DIV2_write_en3_mask                                                 (0x00000010)
#define DISP_PLL_DIV2_write_en3(data)                                                (0x00000010&((data)<<4))
#define DISP_PLL_DIV2_write_en3_src(data)                                            ((0x00000010&(data))>>4)
#define DISP_PLL_DIV2_get_write_en3(data)                                            ((0x00000010&(data))>>4)
#define DISP_PLL_DIV2_tve_div_shift                                                  (0)
#define DISP_PLL_DIV2_tve_div_mask                                                   (0x0000000F)
#define DISP_PLL_DIV2_tve_div(data)                                                  (0x0000000F&((data)<<0))
#define DISP_PLL_DIV2_tve_div_src(data)                                              ((0x0000000F&(data))>>0)
#define DISP_PLL_DIV2_get_tve_div(data)                                              ((0x0000000F&(data))>>0)


#define DDS_VIDEO_CK_SEL                                                             0x98000028
#define DDS_VIDEO_CK_SEL_reg_addr                                                    "0x98000028"
#define DDS_VIDEO_CK_SEL_reg                                                         0x98000028
#define set_DDS_VIDEO_CK_SEL_reg(data)   (*((volatile unsigned int*) DDS_VIDEO_CK_SEL_reg)=data)
#define get_DDS_VIDEO_CK_SEL_reg   (*((volatile unsigned int*) DDS_VIDEO_CK_SEL_reg))
#define DDS_VIDEO_CK_SEL_inst_adr                                                    "0x000A"
#define DDS_VIDEO_CK_SEL_inst                                                        0x000A
#define DDS_VIDEO_CK_SEL_dds_clk_sel_shift                                           (0)
#define DDS_VIDEO_CK_SEL_dds_clk_sel_mask                                            (0x00000001)
#define DDS_VIDEO_CK_SEL_dds_clk_sel(data)                                           (0x00000001&((data)<<0))
#define DDS_VIDEO_CK_SEL_dds_clk_sel_src(data)                                       ((0x00000001&(data))>>0)
#define DDS_VIDEO_CK_SEL_get_dds_clk_sel(data)                                       ((0x00000001&(data))>>0)


#define AUDIO_CLK_CTL                                                                0x9800002C
#define AUDIO_CLK_CTL_reg_addr                                                       "0x9800002C"
#define AUDIO_CLK_CTL_reg                                                            0x9800002C
#define set_AUDIO_CLK_CTL_reg(data)   (*((volatile unsigned int*) AUDIO_CLK_CTL_reg)=data)
#define get_AUDIO_CLK_CTL_reg   (*((volatile unsigned int*) AUDIO_CLK_CTL_reg))
#define AUDIO_CLK_CTL_inst_adr                                                       "0x000B"
#define AUDIO_CLK_CTL_inst                                                           0x000B
#define AUDIO_CLK_CTL_audio_use_sysclk_shift                                         (0)
#define AUDIO_CLK_CTL_audio_use_sysclk_mask                                          (0x00000001)
#define AUDIO_CLK_CTL_audio_use_sysclk(data)                                         (0x00000001&((data)<<0))
#define AUDIO_CLK_CTL_audio_use_sysclk_src(data)                                     ((0x00000001&(data))>>0)
#define AUDIO_CLK_CTL_get_audio_use_sysclk(data)                                     ((0x00000001&(data))>>0)


#define PLL_DIV                                                                      0x98000030
#define PLL_DIV_reg_addr                                                             "0x98000030"
#define PLL_DIV_reg                                                                  0x98000030
#define set_PLL_DIV_reg(data)   (*((volatile unsigned int*) PLL_DIV_reg)=data)
#define get_PLL_DIV_reg   (*((volatile unsigned int*) PLL_DIV_reg))
#define PLL_DIV_inst_adr                                                             "0x000C"
#define PLL_DIV_inst                                                                 0x000C
#define PLL_DIV_scpu_freq_sel_shift                                                  (7)
#define PLL_DIV_scpu_freq_sel_mask                                                   (0x00000180)
#define PLL_DIV_scpu_freq_sel(data)                                                  (0x00000180&((data)<<7))
#define PLL_DIV_scpu_freq_sel_src(data)                                              ((0x00000180&(data))>>7)
#define PLL_DIV_get_scpu_freq_sel(data)                                              ((0x00000180&(data))>>7)
#define PLL_DIV_acpu_freq_sel_shift                                                  (3)
#define PLL_DIV_acpu_freq_sel_mask                                                   (0x00000018)
#define PLL_DIV_acpu_freq_sel(data)                                                  (0x00000018&((data)<<3))
#define PLL_DIV_acpu_freq_sel_src(data)                                              ((0x00000018&(data))>>3)
#define PLL_DIV_get_acpu_freq_sel(data)                                              ((0x00000018&(data))>>3)
#define PLL_DIV_get_ddr_freq_sel(data)                                               ((0x00000006&(data))>>1)
#define PLL_DIV_bus_freq_sel_shift                                                   (0)
#define PLL_DIV_bus_freq_sel_mask                                                    (0x00000001)
#define PLL_DIV_bus_freq_sel(data)                                                   (0x00000001&((data)<<0))
#define PLL_DIV_bus_freq_sel_src(data)                                               ((0x00000001&(data))>>0)
#define PLL_DIV_get_bus_freq_sel(data)                                               ((0x00000001&(data))>>0)


#define DCPHY_CKSEL                                                                  0x98000034
#define DCPHY_CKSEL_reg_addr                                                         "0x98000034"
#define DCPHY_CKSEL_reg                                                              0x98000034
#define set_DCPHY_CKSEL_reg(data)   (*((volatile unsigned int*) DCPHY_CKSEL_reg)=data)
#define get_DCPHY_CKSEL_reg   (*((volatile unsigned int*) DCPHY_CKSEL_reg))
#define DCPHY_CKSEL_inst_adr                                                         "0x000D"
#define DCPHY_CKSEL_inst                                                             0x000D
#define DCPHY_CKSEL_clk_sel_shift                                                    (0)
#define DCPHY_CKSEL_clk_sel_mask                                                     (0x00000001)
#define DCPHY_CKSEL_clk_sel(data)                                                    (0x00000001&((data)<<0))
#define DCPHY_CKSEL_clk_sel_src(data)                                                ((0x00000001&(data))>>0)
#define DCPHY_CKSEL_get_clk_sel(data)                                                ((0x00000001&(data))>>0)


#define NF_CKSEL                                                                     0x98000038
#define NF_CKSEL_reg_addr                                                            "0x98000038"
#define NF_CKSEL_reg                                                                 0x98000038
#define set_NF_CKSEL_reg(data)   (*((volatile unsigned int*) NF_CKSEL_reg)=data)
#define get_NF_CKSEL_reg   (*((volatile unsigned int*) NF_CKSEL_reg))
#define NF_CKSEL_inst_adr                                                            "0x000E"
#define NF_CKSEL_inst                                                                0x000E
#define NF_CKSEL_nf_div_shift                                                        (0)
#define NF_CKSEL_nf_div_mask                                                         (0x00000007)
#define NF_CKSEL_nf_div(data)                                                        (0x00000007&((data)<<0))
#define NF_CKSEL_nf_div_src(data)                                                    ((0x00000007&(data))>>0)
#define NF_CKSEL_get_nf_div(data)                                                    ((0x00000007&(data))>>0)


#define NDS_SC_CKSEL                                                                 0x9800003C
#define NDS_SC_CKSEL_reg_addr                                                        "0x9800003C"
#define NDS_SC_CKSEL_reg                                                             0x9800003C
#define set_NDS_SC_CKSEL_reg(data)   (*((volatile unsigned int*) NDS_SC_CKSEL_reg)=data)
#define get_NDS_SC_CKSEL_reg   (*((volatile unsigned int*) NDS_SC_CKSEL_reg))
#define NDS_SC_CKSEL_inst_adr                                                        "0x000F"
#define NDS_SC_CKSEL_inst                                                            0x000F
#define NDS_SC_CKSEL_nds_sc_div_shift                                                (0)
#define NDS_SC_CKSEL_nds_sc_div_mask                                                 (0x00000007)
#define NDS_SC_CKSEL_nds_sc_div(data)                                                (0x00000007&((data)<<0))
#define NDS_SC_CKSEL_nds_sc_div_src(data)                                            ((0x00000007&(data))>>0)
#define NDS_SC_CKSEL_get_nds_sc_div(data)                                            ((0x00000007&(data))>>0)


#define CR_CKSEL                                                                     0x98000040
#define CR_CKSEL_reg_addr                                                            "0x98000040"
#define CR_CKSEL_reg                                                                 0x98000040
#define set_CR_CKSEL_reg(data)   (*((volatile unsigned int*) CR_CKSEL_reg)=data)
#define get_CR_CKSEL_reg   (*((volatile unsigned int*) CR_CKSEL_reg))
#define CR_CKSEL_inst_adr                                                            "0x0010"
#define CR_CKSEL_inst                                                                0x0010
#define CR_CKSEL_write_en2_shift                                                     (7)
#define CR_CKSEL_write_en2_mask                                                      (0x00000080)
#define CR_CKSEL_write_en2(data)                                                     (0x00000080&((data)<<7))
#define CR_CKSEL_write_en2_src(data)                                                 ((0x00000080&(data))>>7)
#define CR_CKSEL_get_write_en2(data)                                                 ((0x00000080&(data))>>7)
#define CR_CKSEL_emmc_div_shift                                                      (4)
#define CR_CKSEL_emmc_div_mask                                                       (0x00000070)
#define CR_CKSEL_emmc_div(data)                                                      (0x00000070&((data)<<4))
#define CR_CKSEL_emmc_div_src(data)                                                  ((0x00000070&(data))>>4)
#define CR_CKSEL_get_emmc_div(data)                                                  ((0x00000070&(data))>>4)
#define CR_CKSEL_write_en1_shift                                                     (3)
#define CR_CKSEL_write_en1_mask                                                      (0x00000008)
#define CR_CKSEL_write_en1(data)                                                     (0x00000008&((data)<<3))
#define CR_CKSEL_write_en1_src(data)                                                 ((0x00000008&(data))>>3)
#define CR_CKSEL_get_write_en1(data)                                                 ((0x00000008&(data))>>3)
#define CR_CKSEL_cr_div_shift                                                        (0)
#define CR_CKSEL_cr_div_mask                                                         (0x00000007)
#define CR_CKSEL_cr_div(data)                                                        (0x00000007&((data)<<0))
#define CR_CKSEL_cr_div_src(data)                                                    ((0x00000007&(data))>>0)
#define CR_CKSEL_get_cr_div(data)                                                    ((0x00000007&(data))>>0)


#define MISC_CKSEL                                                                   0x98000044
#define MISC_CKSEL_reg_addr                                                          "0x98000044"
#define MISC_CKSEL_reg                                                               0x98000044
#define set_MISC_CKSEL_reg(data)   (*((volatile unsigned int*) MISC_CKSEL_reg)=data)
#define get_MISC_CKSEL_reg   (*((volatile unsigned int*) MISC_CKSEL_reg))
#define MISC_CKSEL_inst_adr                                                          "0x0011"
#define MISC_CKSEL_inst                                                              0x0011
#define MISC_CKSEL_clk_camera1_sel_shift                                             (2)
#define MISC_CKSEL_clk_camera1_sel_mask                                              (0x0000000C)
#define MISC_CKSEL_clk_camera1_sel(data)                                             (0x0000000C&((data)<<2))
#define MISC_CKSEL_clk_camera1_sel_src(data)                                         ((0x0000000C&(data))>>2)
#define MISC_CKSEL_get_clk_camera1_sel(data)                                         ((0x0000000C&(data))>>2)
#define MISC_CKSEL_clk_camera0_sel_shift                                             (0)
#define MISC_CKSEL_clk_camera0_sel_mask                                              (0x00000003)
#define MISC_CKSEL_clk_camera0_sel(data)                                             (0x00000003&((data)<<0))
#define MISC_CKSEL_clk_camera0_sel_src(data)                                         ((0x00000003&(data))>>0)
#define MISC_CKSEL_get_clk_camera0_sel(data)                                         ((0x00000003&(data))>>0)


#define BUS_PLL_SSC                                                                  0x98000060
#define BUS_PLL_SSC_reg_addr                                                         "0x98000060"
#define BUS_PLL_SSC_reg                                                              0x98000060
#define set_BUS_PLL_SSC_reg(data)   (*((volatile unsigned int*) BUS_PLL_SSC_reg)=data)
#define get_BUS_PLL_SSC_reg   (*((volatile unsigned int*) BUS_PLL_SSC_reg))
#define BUS_PLL_SSC_inst_adr                                                         "0x0018"
#define BUS_PLL_SSC_inst                                                             0x0018
#define BUS_PLL_SSC_bus_ssc_sse_shift                                                (31)
#define BUS_PLL_SSC_bus_ssc_sse_mask                                                 (0x80000000)
#define BUS_PLL_SSC_bus_ssc_sse(data)                                                (0x80000000&((data)<<31))
#define BUS_PLL_SSC_bus_ssc_sse_src(data)                                            ((0x80000000&(data))>>31)
#define BUS_PLL_SSC_get_bus_ssc_sse(data)                                            ((0x80000000&(data))>>31)
#define BUS_PLL_SSC_bus_ssc_ckinv_shift                                              (30)
#define BUS_PLL_SSC_bus_ssc_ckinv_mask                                               (0x40000000)
#define BUS_PLL_SSC_bus_ssc_ckinv(data)                                              (0x40000000&((data)<<30))
#define BUS_PLL_SSC_bus_ssc_ckinv_src(data)                                          ((0x40000000&(data))>>30)
#define BUS_PLL_SSC_get_bus_ssc_ckinv(data)                                          ((0x40000000&(data))>>30)
#define BUS_PLL_SSC_bus_ssc_sss_shift                                                (24)
#define BUS_PLL_SSC_bus_ssc_sss_mask                                                 (0x3F000000)
#define BUS_PLL_SSC_bus_ssc_sss(data)                                                (0x3F000000&((data)<<24))
#define BUS_PLL_SSC_bus_ssc_sss_src(data)                                            ((0x3F000000&(data))>>24)
#define BUS_PLL_SSC_get_bus_ssc_sss(data)                                            ((0x3F000000&(data))>>24)
#define BUS_PLL_SSC_bus_ssc_ssn_shift                                                (16)
#define BUS_PLL_SSC_bus_ssc_ssn_mask                                                 (0x007F0000)
#define BUS_PLL_SSC_bus_ssc_ssn(data)                                                (0x007F0000&((data)<<16))
#define BUS_PLL_SSC_bus_ssc_ssn_src(data)                                            ((0x007F0000&(data))>>16)
#define BUS_PLL_SSC_get_bus_ssc_ssn(data)                                            ((0x007F0000&(data))>>16)
#define BUS_PLL_SSC_bus_ssc_ssfpv_shift                                              (8)
#define BUS_PLL_SSC_bus_ssc_ssfpv_mask                                               (0x0000FF00)
#define BUS_PLL_SSC_bus_ssc_ssfpv(data)                                              (0x0000FF00&((data)<<8))
#define BUS_PLL_SSC_bus_ssc_ssfpv_src(data)                                          ((0x0000FF00&(data))>>8)
#define BUS_PLL_SSC_get_bus_ssc_ssfpv(data)                                          ((0x0000FF00&(data))>>8)
#define BUS_PLL_SSC_bus_ssc_stms_shift                                               (0)
#define BUS_PLL_SSC_bus_ssc_stms_mask                                                (0x00000003)
#define BUS_PLL_SSC_bus_ssc_stms(data)                                               (0x00000003&((data)<<0))
#define BUS_PLL_SSC_bus_ssc_stms_src(data)                                           ((0x00000003&(data))>>0)
#define BUS_PLL_SSC_get_bus_ssc_stms(data)                                           ((0x00000003&(data))>>0)


#define PLL_DDR_SSC2                                                                 0x98000064
#define PLL_DDR_SSC2_reg_addr                                                        "0x98000064"
#define PLL_DDR_SSC2_reg                                                             0x98000064
#define set_PLL_DDR_SSC2_reg(data)   (*((volatile unsigned int*) PLL_DDR_SSC2_reg)=data)
#define get_PLL_DDR_SSC2_reg   (*((volatile unsigned int*) PLL_DDR_SSC2_reg))
#define PLL_DDR_SSC2_inst_adr                                                        "0x0019"
#define PLL_DDR_SSC2_inst                                                            0x0019
#define PLL_DDR_SSC2_SSCDDR_SEL_ORDER_shift                                          (28)
#define PLL_DDR_SSC2_SSCDDR_SEL_ORDER_mask                                           (0x10000000)
#define PLL_DDR_SSC2_SSCDDR_SEL_ORDER(data)                                          (0x10000000&((data)<<28))
#define PLL_DDR_SSC2_SSCDDR_SEL_ORDER_src(data)                                      ((0x10000000&(data))>>28)
#define PLL_DDR_SSC2_get_SSCDDR_SEL_ORDER(data)                                      ((0x10000000&(data))>>28)
#define PLL_DDR_SSC2_SSCDDR_WEIGHTING_SEL_shift                                      (25)
#define PLL_DDR_SSC2_SSCDDR_WEIGHTING_SEL_mask                                       (0x0E000000)
#define PLL_DDR_SSC2_SSCDDR_WEIGHTING_SEL(data)                                      (0x0E000000&((data)<<25))
#define PLL_DDR_SSC2_SSCDDR_WEIGHTING_SEL_src(data)                                  ((0x0E000000&(data))>>25)
#define PLL_DDR_SSC2_get_SSCDDR_WEIGHTING_SEL(data)                                  ((0x0E000000&(data))>>25)
#define PLL_DDR_SSC2_SSCDDR_STEP_IN_shift                                            (12)
#define PLL_DDR_SSC2_SSCDDR_STEP_IN_mask                                             (0x01FFF000)
#define PLL_DDR_SSC2_SSCDDR_STEP_IN(data)                                            (0x01FFF000&((data)<<12))
#define PLL_DDR_SSC2_SSCDDR_STEP_IN_src(data)                                        ((0x01FFF000&(data))>>12)
#define PLL_DDR_SSC2_get_SSCDDR_STEP_IN(data)                                        ((0x01FFF000&(data))>>12)
#define PLL_DDR_SSC2_SSCDDR_TBASE_shift                                              (0)
#define PLL_DDR_SSC2_SSCDDR_TBASE_mask                                               (0x00000FFF)
#define PLL_DDR_SSC2_SSCDDR_TBASE(data)                                              (0x00000FFF&((data)<<0))
#define PLL_DDR_SSC2_SSCDDR_TBASE_src(data)                                          ((0x00000FFF&(data))>>0)
#define PLL_DDR_SSC2_get_SSCDDR_TBASE(data)                                          ((0x00000FFF&(data))>>0)


#define DCSB_PLL_SSC                                                                 0x98000068
#define DCSB_PLL_SSC_reg_addr                                                        "0x98000068"
#define DCSB_PLL_SSC_reg                                                             0x98000068
#define set_DCSB_PLL_SSC_reg(data)   (*((volatile unsigned int*) DCSB_PLL_SSC_reg)=data)
#define get_DCSB_PLL_SSC_reg   (*((volatile unsigned int*) DCSB_PLL_SSC_reg))
#define DCSB_PLL_SSC_inst_adr                                                        "0x001A"
#define DCSB_PLL_SSC_inst                                                            0x001A
#define DCSB_PLL_SSC_dcsb_ssc_sse_shift                                              (31)
#define DCSB_PLL_SSC_dcsb_ssc_sse_mask                                               (0x80000000)
#define DCSB_PLL_SSC_dcsb_ssc_sse(data)                                              (0x80000000&((data)<<31))
#define DCSB_PLL_SSC_dcsb_ssc_sse_src(data)                                          ((0x80000000&(data))>>31)
#define DCSB_PLL_SSC_get_dcsb_ssc_sse(data)                                          ((0x80000000&(data))>>31)
#define DCSB_PLL_SSC_dcsb_ssc_ckinv_shift                                            (30)
#define DCSB_PLL_SSC_dcsb_ssc_ckinv_mask                                             (0x40000000)
#define DCSB_PLL_SSC_dcsb_ssc_ckinv(data)                                            (0x40000000&((data)<<30))
#define DCSB_PLL_SSC_dcsb_ssc_ckinv_src(data)                                        ((0x40000000&(data))>>30)
#define DCSB_PLL_SSC_get_dcsb_ssc_ckinv(data)                                        ((0x40000000&(data))>>30)
#define DCSB_PLL_SSC_dcsb_ssc_sss_shift                                              (24)
#define DCSB_PLL_SSC_dcsb_ssc_sss_mask                                               (0x3F000000)
#define DCSB_PLL_SSC_dcsb_ssc_sss(data)                                              (0x3F000000&((data)<<24))
#define DCSB_PLL_SSC_dcsb_ssc_sss_src(data)                                          ((0x3F000000&(data))>>24)
#define DCSB_PLL_SSC_get_dcsb_ssc_sss(data)                                          ((0x3F000000&(data))>>24)
#define DCSB_PLL_SSC_dcsb_ssc_ssn_shift                                              (16)
#define DCSB_PLL_SSC_dcsb_ssc_ssn_mask                                               (0x007F0000)
#define DCSB_PLL_SSC_dcsb_ssc_ssn(data)                                              (0x007F0000&((data)<<16))
#define DCSB_PLL_SSC_dcsb_ssc_ssn_src(data)                                          ((0x007F0000&(data))>>16)
#define DCSB_PLL_SSC_get_dcsb_ssc_ssn(data)                                          ((0x007F0000&(data))>>16)
#define DCSB_PLL_SSC_dcsb_ssc_ssfpv_shift                                            (8)
#define DCSB_PLL_SSC_dcsb_ssc_ssfpv_mask                                             (0x0000FF00)
#define DCSB_PLL_SSC_dcsb_ssc_ssfpv(data)                                            (0x0000FF00&((data)<<8))
#define DCSB_PLL_SSC_dcsb_ssc_ssfpv_src(data)                                        ((0x0000FF00&(data))>>8)
#define DCSB_PLL_SSC_get_dcsb_ssc_ssfpv(data)                                        ((0x0000FF00&(data))>>8)
#define DCSB_PLL_SSC_dcsb_ssc_stms_shift                                             (0)
#define DCSB_PLL_SSC_dcsb_ssc_stms_mask                                              (0x00000003)
#define DCSB_PLL_SSC_dcsb_ssc_stms(data)                                             (0x00000003&((data)<<0))
#define DCSB_PLL_SSC_dcsb_ssc_stms_src(data)                                         ((0x00000003&(data))>>0)
#define DCSB_PLL_SSC_get_dcsb_ssc_stms(data)                                         ((0x00000003&(data))>>0)


#define LVDS_PLL_SSC                                                                 0x9800006c
#define LVDS_PLL_SSC_reg_addr                                                        "0x9800006C"
#define LVDS_PLL_SSC_reg                                                             0x9800006C
#define set_LVDS_PLL_SSC_reg(data)   (*((volatile unsigned int*) LVDS_PLL_SSC_reg)=data)
#define get_LVDS_PLL_SSC_reg   (*((volatile unsigned int*) LVDS_PLL_SSC_reg))
#define LVDS_PLL_SSC_inst_adr                                                        "0x001B"
#define LVDS_PLL_SSC_inst                                                            0x001B
#define LVDS_PLL_SSC_lvds_ssc_sse_shift                                              (31)
#define LVDS_PLL_SSC_lvds_ssc_sse_mask                                               (0x80000000)
#define LVDS_PLL_SSC_lvds_ssc_sse(data)                                              (0x80000000&((data)<<31))
#define LVDS_PLL_SSC_lvds_ssc_sse_src(data)                                          ((0x80000000&(data))>>31)
#define LVDS_PLL_SSC_get_lvds_ssc_sse(data)                                          ((0x80000000&(data))>>31)
#define LVDS_PLL_SSC_lvds_ssc_ckinv_shift                                            (30)
#define LVDS_PLL_SSC_lvds_ssc_ckinv_mask                                             (0x40000000)
#define LVDS_PLL_SSC_lvds_ssc_ckinv(data)                                            (0x40000000&((data)<<30))
#define LVDS_PLL_SSC_lvds_ssc_ckinv_src(data)                                        ((0x40000000&(data))>>30)
#define LVDS_PLL_SSC_get_lvds_ssc_ckinv(data)                                        ((0x40000000&(data))>>30)
#define LVDS_PLL_SSC_lvds_ssc_sss_shift                                              (24)
#define LVDS_PLL_SSC_lvds_ssc_sss_mask                                               (0x3F000000)
#define LVDS_PLL_SSC_lvds_ssc_sss(data)                                              (0x3F000000&((data)<<24))
#define LVDS_PLL_SSC_lvds_ssc_sss_src(data)                                          ((0x3F000000&(data))>>24)
#define LVDS_PLL_SSC_get_lvds_ssc_sss(data)                                          ((0x3F000000&(data))>>24)
#define LVDS_PLL_SSC_lvds_ssc_ssn_shift                                              (16)
#define LVDS_PLL_SSC_lvds_ssc_ssn_mask                                               (0x007F0000)
#define LVDS_PLL_SSC_lvds_ssc_ssn(data)                                              (0x007F0000&((data)<<16))
#define LVDS_PLL_SSC_lvds_ssc_ssn_src(data)                                          ((0x007F0000&(data))>>16)
#define LVDS_PLL_SSC_get_lvds_ssc_ssn(data)                                          ((0x007F0000&(data))>>16)
#define LVDS_PLL_SSC_lvds_ssc_ssfpv_shift                                            (8)
#define LVDS_PLL_SSC_lvds_ssc_ssfpv_mask                                             (0x0000FF00)
#define LVDS_PLL_SSC_lvds_ssc_ssfpv(data)                                            (0x0000FF00&((data)<<8))
#define LVDS_PLL_SSC_lvds_ssc_ssfpv_src(data)                                        ((0x0000FF00&(data))>>8)
#define LVDS_PLL_SSC_get_lvds_ssc_ssfpv(data)                                        ((0x0000FF00&(data))>>8)
#define LVDS_PLL_SSC_lvds_ssc_stms_shift                                             (0)
#define LVDS_PLL_SSC_lvds_ssc_stms_mask                                              (0x00000003)
#define LVDS_PLL_SSC_lvds_ssc_stms(data)                                             (0x00000003&((data)<<0))
#define LVDS_PLL_SSC_lvds_ssc_stms_src(data)                                         ((0x00000003&(data))>>0)
#define LVDS_PLL_SSC_get_lvds_ssc_stms(data)                                         ((0x00000003&(data))>>0)


#define AIO_O_PCM_CK_CTL                                                             0x98000070
#define AIO_O_PCM_CK_CTL_reg_addr                                                    "0x98000070"
#define AIO_O_PCM_CK_CTL_reg                                                         0x98000070
#define set_AIO_O_PCM_CK_CTL_reg(data)   (*((volatile unsigned int*) AIO_O_PCM_CK_CTL_reg)=data)
#define get_AIO_O_PCM_CK_CTL_reg   (*((volatile unsigned int*) AIO_O_PCM_CK_CTL_reg))
#define AIO_O_PCM_CK_CTL_inst_adr                                                    "0x001C"
#define AIO_O_PCM_CK_CTL_inst                                                        0x001C
#define AIO_O_PCM_CK_CTL_mclk_sel_shift                                              (5)
#define AIO_O_PCM_CK_CTL_mclk_sel_mask                                               (0x000000E0)
#define AIO_O_PCM_CK_CTL_mclk_sel(data)                                              (0x000000E0&((data)<<5))
#define AIO_O_PCM_CK_CTL_mclk_sel_src(data)                                          ((0x000000E0&(data))>>5)
#define AIO_O_PCM_CK_CTL_get_mclk_sel(data)                                          ((0x000000E0&(data))>>5)
#define AIO_O_PCM_CK_CTL_fs_shift                                                    (1)
#define AIO_O_PCM_CK_CTL_fs_mask                                                     (0x0000001E)
#define AIO_O_PCM_CK_CTL_fs(data)                                                    (0x0000001E&((data)<<1))
#define AIO_O_PCM_CK_CTL_fs_src(data)                                                ((0x0000001E&(data))>>1)
#define AIO_O_PCM_CK_CTL_get_fs(data)                                                ((0x0000001E&(data))>>1)
#define AIO_O_PCM_CK_CTL_clken_shift                                                 (0)
#define AIO_O_PCM_CK_CTL_clken_mask                                                  (0x00000001)
#define AIO_O_PCM_CK_CTL_clken(data)                                                 (0x00000001&((data)<<0))
#define AIO_O_PCM_CK_CTL_clken_src(data)                                             ((0x00000001&(data))>>0)
#define AIO_O_PCM_CK_CTL_get_clken(data)                                             ((0x00000001&(data))>>0)


#define AIO_O_RAW_CK_CTL                                                             0x98000074
#define AIO_O_RAW_CK_CTL_reg_addr                                                    "0x98000074"
#define AIO_O_RAW_CK_CTL_reg                                                         0x98000074
#define set_AIO_O_RAW_CK_CTL_reg(data)   (*((volatile unsigned int*) AIO_O_RAW_CK_CTL_reg)=data)
#define get_AIO_O_RAW_CK_CTL_reg   (*((volatile unsigned int*) AIO_O_RAW_CK_CTL_reg))
#define AIO_O_RAW_CK_CTL_inst_adr                                                    "0x001D"
#define AIO_O_RAW_CK_CTL_inst                                                        0x001D
#define AIO_O_RAW_CK_CTL_fs_shift                                                    (1)
#define AIO_O_RAW_CK_CTL_fs_mask                                                     (0x0000001E)
#define AIO_O_RAW_CK_CTL_fs(data)                                                    (0x0000001E&((data)<<1))
#define AIO_O_RAW_CK_CTL_fs_src(data)                                                ((0x0000001E&(data))>>1)
#define AIO_O_RAW_CK_CTL_get_fs(data)                                                ((0x0000001E&(data))>>1)
#define AIO_O_RAW_CK_CTL_clken_shift                                                 (0)
#define AIO_O_RAW_CK_CTL_clken_mask                                                  (0x00000001)
#define AIO_O_RAW_CK_CTL_clken(data)                                                 (0x00000001&((data)<<0))
#define AIO_O_RAW_CK_CTL_clken_src(data)                                             ((0x00000001&(data))>>0)
#define AIO_O_RAW_CK_CTL_get_clken(data)                                             ((0x00000001&(data))>>0)


#define AIO_O_RAW2_CK_CTL                                                            0x98000078
#define AIO_O_RAW2_CK_CTL_reg_addr                                                   "0x98000078"
#define AIO_O_RAW2_CK_CTL_reg                                                        0x98000078
#define set_AIO_O_RAW2_CK_CTL_reg(data)   (*((volatile unsigned int*) AIO_O_RAW2_CK_CTL_reg)=data)
#define get_AIO_O_RAW2_CK_CTL_reg   (*((volatile unsigned int*) AIO_O_RAW2_CK_CTL_reg))
#define AIO_O_RAW2_CK_CTL_inst_adr                                                   "0x001E"
#define AIO_O_RAW2_CK_CTL_inst                                                       0x001E
#define AIO_O_RAW2_CK_CTL_fs_shift                                                   (1)
#define AIO_O_RAW2_CK_CTL_fs_mask                                                    (0x0000001E)
#define AIO_O_RAW2_CK_CTL_fs(data)                                                   (0x0000001E&((data)<<1))
#define AIO_O_RAW2_CK_CTL_fs_src(data)                                               ((0x0000001E&(data))>>1)
#define AIO_O_RAW2_CK_CTL_get_fs(data)                                               ((0x0000001E&(data))>>1)
#define AIO_O_RAW2_CK_CTL_clken_shift                                                (0)
#define AIO_O_RAW2_CK_CTL_clken_mask                                                 (0x00000001)
#define AIO_O_RAW2_CK_CTL_clken(data)                                                (0x00000001&((data)<<0))
#define AIO_O_RAW2_CK_CTL_clken_src(data)                                            ((0x00000001&(data))>>0)
#define AIO_O_RAW2_CK_CTL_get_clken(data)                                            ((0x00000001&(data))>>0)


#define APS_CTL                                                                      0x9800007C
#define APS_CTL_reg_addr                                                             "0x9800007C"
#define APS_CTL_reg                                                                  0x9800007C
#define set_APS_CTL_reg(data)   (*((volatile unsigned int*) APS_CTL_reg)=data)
#define get_APS_CTL_reg   (*((volatile unsigned int*) APS_CTL_reg))
#define APS_CTL_inst_adr                                                             "0x001F"
#define APS_CTL_inst                                                                 0x001F
#define APS_CTL_write_en2_shift                                                      (1)
#define APS_CTL_write_en2_mask                                                       (0x00000002)
#define APS_CTL_write_en2(data)                                                      (0x00000002&((data)<<1))
#define APS_CTL_write_en2_src(data)                                                  ((0x00000002&(data))>>1)
#define APS_CTL_get_write_en2(data)                                                  ((0x00000002&(data))>>1)
#define APS_CTL_dds_rstn_shift                                                       (0)
#define APS_CTL_dds_rstn_mask                                                        (0x00000001)
#define APS_CTL_dds_rstn(data)                                                       (0x00000001&((data)<<0))
#define APS_CTL_dds_rstn_src(data)                                                   ((0x00000001&(data))>>0)
#define APS_CTL_get_dds_rstn(data)                                                   ((0x00000001&(data))>>0)


#define AIO_I_PCM_CK_CTL                                                             0x98000080
#define AIO_I_PCM_CK_CTL_reg_addr                                                    "0x98000080"
#define AIO_I_PCM_CK_CTL_reg                                                         0x98000080
#define set_AIO_I_PCM_CK_CTL_reg(data)   (*((volatile unsigned int*) AIO_I_PCM_CK_CTL_reg)=data)
#define get_AIO_I_PCM_CK_CTL_reg   (*((volatile unsigned int*) AIO_I_PCM_CK_CTL_reg))
#define AIO_I_PCM_CK_CTL_inst_adr                                                    "0x0020"
#define AIO_I_PCM_CK_CTL_inst                                                        0x0020
#define AIO_I_PCM_CK_CTL_mclk_sel_shift                                              (5)
#define AIO_I_PCM_CK_CTL_mclk_sel_mask                                               (0x000000E0)
#define AIO_I_PCM_CK_CTL_mclk_sel(data)                                              (0x000000E0&((data)<<5))
#define AIO_I_PCM_CK_CTL_mclk_sel_src(data)                                          ((0x000000E0&(data))>>5)
#define AIO_I_PCM_CK_CTL_get_mclk_sel(data)                                          ((0x000000E0&(data))>>5)
#define AIO_I_PCM_CK_CTL_fs_shift                                                    (1)
#define AIO_I_PCM_CK_CTL_fs_mask                                                     (0x0000001E)
#define AIO_I_PCM_CK_CTL_fs(data)                                                    (0x0000001E&((data)<<1))
#define AIO_I_PCM_CK_CTL_fs_src(data)                                                ((0x0000001E&(data))>>1)
#define AIO_I_PCM_CK_CTL_get_fs(data)                                                ((0x0000001E&(data))>>1)
#define AIO_I_PCM_CK_CTL_clken_shift                                                 (0)
#define AIO_I_PCM_CK_CTL_clken_mask                                                  (0x00000001)
#define AIO_I_PCM_CK_CTL_clken(data)                                                 (0x00000001&((data)<<0))
#define AIO_I_PCM_CK_CTL_clken_src(data)                                             ((0x00000001&(data))>>0)
#define AIO_I_PCM_CK_CTL_get_clken(data)                                             ((0x00000001&(data))>>0)


#define CLK_VO_CTRL                                                                  0x98000084
#define CLK_VO_CTRL_reg_addr                                                         "0x98000084"
#define CLK_VO_CTRL_reg                                                              0x98000084
#define set_CLK_VO_CTRL_reg(data)   (*((volatile unsigned int*) CLK_VO_CTRL_reg)=data)
#define get_CLK_VO_CTRL_reg   (*((volatile unsigned int*) CLK_VO_CTRL_reg))
#define CLK_VO_CTRL_inst_adr                                                         "0x0021"
#define CLK_VO_CTRL_inst                                                             0x0021
#define CLK_VO_CTRL_CLK_VO_SEL_shift                                                 (0)
#define CLK_VO_CTRL_CLK_VO_SEL_mask                                                  (0x00000001)
#define CLK_VO_CTRL_CLK_VO_SEL(data)                                                 (0x00000001&((data)<<0))
#define CLK_VO_CTRL_CLK_VO_SEL_src(data)                                             ((0x00000001&(data))>>0)
#define CLK_VO_CTRL_get_CLK_VO_SEL(data)                                             ((0x00000001&(data))>>0)


#define PLL_SCPU1                                                                    0x98000100
#define PLL_SCPU1_reg_addr                                                           "0x98000100"
#define PLL_SCPU1_reg                                                                0x98000100
#define set_PLL_SCPU1_reg(data)   (*((volatile unsigned int*) PLL_SCPU1_reg)=data)
#define get_PLL_SCPU1_reg   (*((volatile unsigned int*) PLL_SCPU1_reg))
#define PLL_SCPU1_inst_adr                                                           "0x0040"
#define PLL_SCPU1_inst                                                               0x0040
#define PLL_SCPU1_REG_PLLSCPU_RS_shift                                               (29)
#define PLL_SCPU1_REG_PLLSCPU_RS_mask                                                (0xE0000000)
#define PLL_SCPU1_REG_PLLSCPU_RS(data)                                               (0xE0000000&((data)<<29))
#define PLL_SCPU1_REG_PLLSCPU_RS_src(data)                                           ((0xE0000000&(data))>>29)
#define PLL_SCPU1_get_REG_PLLSCPU_RS(data)                                           ((0xE0000000&(data))>>29)
#define PLL_SCPU1_REG_PLLSCPU_LDO_VSEL_shift                                         (27)
#define PLL_SCPU1_REG_PLLSCPU_LDO_VSEL_mask                                          (0x18000000)
#define PLL_SCPU1_REG_PLLSCPU_LDO_VSEL(data)                                         (0x18000000&((data)<<27))
#define PLL_SCPU1_REG_PLLSCPU_LDO_VSEL_src(data)                                     ((0x18000000&(data))>>27)
#define PLL_SCPU1_get_REG_PLLSCPU_LDO_VSEL(data)                                     ((0x18000000&(data))>>27)
#define PLL_SCPU1_REG_PLLSCPU_CP_shift                                               (26)
#define PLL_SCPU1_REG_PLLSCPU_CP_mask                                                (0x04000000)
#define PLL_SCPU1_REG_PLLSCPU_CP(data)                                               (0x04000000&((data)<<26))
#define PLL_SCPU1_REG_PLLSCPU_CP_src(data)                                           ((0x04000000&(data))>>26)
#define PLL_SCPU1_get_REG_PLLSCPU_CP(data)                                           ((0x04000000&(data))>>26)
#define PLL_SCPU1_REG_PLLSCPU_DBUG_EN_shift                                          (25)
#define PLL_SCPU1_REG_PLLSCPU_DBUG_EN_mask                                           (0x02000000)
#define PLL_SCPU1_REG_PLLSCPU_DBUG_EN(data)                                          (0x02000000&((data)<<25))
#define PLL_SCPU1_REG_PLLSCPU_DBUG_EN_src(data)                                      ((0x02000000&(data))>>25)
#define PLL_SCPU1_get_REG_PLLSCPU_DBUG_EN(data)                                      ((0x02000000&(data))>>25)
#define PLL_SCPU1_REG_PLLSCPU_CPMODE_shift                                           (24)
#define PLL_SCPU1_REG_PLLSCPU_CPMODE_mask                                            (0x01000000)
#define PLL_SCPU1_REG_PLLSCPU_CPMODE(data)                                           (0x01000000&((data)<<24))
#define PLL_SCPU1_REG_PLLSCPU_CPMODE_src(data)                                       ((0x01000000&(data))>>24)
#define PLL_SCPU1_get_REG_PLLSCPU_CPMODE(data)                                       ((0x01000000&(data))>>24)
#define PLL_SCPU1_REG_PLLSCPU_HIGH_KVCO_shift                                        (23)
#define PLL_SCPU1_REG_PLLSCPU_HIGH_KVCO_mask                                         (0x00800000)
#define PLL_SCPU1_REG_PLLSCPU_HIGH_KVCO(data)                                        (0x00800000&((data)<<23))
#define PLL_SCPU1_REG_PLLSCPU_HIGH_KVCO_src(data)                                    ((0x00800000&(data))>>23)
#define PLL_SCPU1_get_REG_PLLSCPU_HIGH_KVCO(data)                                    ((0x00800000&(data))>>23)
#define PLL_SCPU1_REG_PLLSCPU_RESERVE_shift                                          (22)
#define PLL_SCPU1_REG_PLLSCPU_RESERVE_mask                                           (0x00400000)
#define PLL_SCPU1_REG_PLLSCPU_RESERVE(data)                                          (0x00400000&((data)<<22))
#define PLL_SCPU1_REG_PLLSCPU_RESERVE_src(data)                                      ((0x00400000&(data))>>22)
#define PLL_SCPU1_get_REG_PLLSCPU_RESERVE(data)                                      ((0x00400000&(data))>>22)
#define PLL_SCPU1_REG_PLLSCPU_CCO_shift                                              (21)
#define PLL_SCPU1_REG_PLLSCPU_CCO_mask                                               (0x00200000)
#define PLL_SCPU1_REG_PLLSCPU_CCO(data)                                              (0x00200000&((data)<<21))
#define PLL_SCPU1_REG_PLLSCPU_CCO_src(data)                                          ((0x00200000&(data))>>21)
#define PLL_SCPU1_get_REG_PLLSCPU_CCO(data)                                          ((0x00200000&(data))>>21)
#define PLL_SCPU1_PLLSCPU_N_shift                                                    (7)
#define PLL_SCPU1_PLLSCPU_N_mask                                                     (0x00000180)
#define PLL_SCPU1_PLLSCPU_N(data)                                                    (0x00000180&((data)<<7))
#define PLL_SCPU1_PLLSCPU_N_src(data)                                                ((0x00000180&(data))>>7)
#define PLL_SCPU1_get_PLLSCPU_N(data)                                                ((0x00000180&(data))>>7)
#define PLL_SCPU1_REG_PLLSCPU_IP_shift                                               (3)
#define PLL_SCPU1_REG_PLLSCPU_IP_mask                                                (0x00000078)
#define PLL_SCPU1_REG_PLLSCPU_IP(data)                                               (0x00000078&((data)<<3))
#define PLL_SCPU1_REG_PLLSCPU_IP_src(data)                                           ((0x00000078&(data))>>3)
#define PLL_SCPU1_get_REG_PLLSCPU_IP(data)                                           ((0x00000078&(data))>>3)
#define PLL_SCPU1_REG_PLLSCPU_TST_shift                                              (2)
#define PLL_SCPU1_REG_PLLSCPU_TST_mask                                               (0x00000004)
#define PLL_SCPU1_REG_PLLSCPU_TST(data)                                              (0x00000004&((data)<<2))
#define PLL_SCPU1_REG_PLLSCPU_TST_src(data)                                          ((0x00000004&(data))>>2)
#define PLL_SCPU1_get_REG_PLLSCPU_TST(data)                                          ((0x00000004&(data))>>2)
#define PLL_SCPU1_PLLSCPU_RSTB_shift                                                 (1)
#define PLL_SCPU1_PLLSCPU_RSTB_mask                                                  (0x00000002)
#define PLL_SCPU1_PLLSCPU_RSTB(data)                                                 (0x00000002&((data)<<1))
#define PLL_SCPU1_PLLSCPU_RSTB_src(data)                                             ((0x00000002&(data))>>1)
#define PLL_SCPU1_get_PLLSCPU_RSTB(data)                                             ((0x00000002&(data))>>1)
#define PLL_SCPU1_PLLSCPU_POW_shift                                                  (0)
#define PLL_SCPU1_PLLSCPU_POW_mask                                                   (0x00000001)
#define PLL_SCPU1_PLLSCPU_POW(data)                                                  (0x00000001&((data)<<0))
#define PLL_SCPU1_PLLSCPU_POW_src(data)                                              ((0x00000001&(data))>>0)
#define PLL_SCPU1_get_PLLSCPU_POW(data)                                              ((0x00000001&(data))>>0)


#define PLL_SCPU2                                                                    0x98000104
#define PLL_SCPU2_reg_addr                                                           "0x98000104"
#define PLL_SCPU2_reg                                                                0x98000104
#define set_PLL_SCPU2_reg(data)   (*((volatile unsigned int*) PLL_SCPU2_reg)=data)
#define get_PLL_SCPU2_reg   (*((volatile unsigned int*) PLL_SCPU2_reg))
#define PLL_SCPU2_inst_adr                                                           "0x0041"
#define PLL_SCPU2_inst                                                               0x0041
#define PLL_SCPU2_NCODE_T_SCPU_shift                                                 (21)
#define PLL_SCPU2_NCODE_T_SCPU_mask                                                  (0x1FE00000)
#define PLL_SCPU2_NCODE_T_SCPU(data)                                                 (0x1FE00000&((data)<<21))
#define PLL_SCPU2_NCODE_T_SCPU_src(data)                                             ((0x1FE00000&(data))>>21)
#define PLL_SCPU2_get_NCODE_T_SCPU(data)                                             ((0x1FE00000&(data))>>21)
#define PLL_SCPU2_FCODE_T_SCPU_shift                                                 (10)
#define PLL_SCPU2_FCODE_T_SCPU_mask                                                  (0x001FFC00)
#define PLL_SCPU2_FCODE_T_SCPU(data)                                                 (0x001FFC00&((data)<<10))
#define PLL_SCPU2_FCODE_T_SCPU_src(data)                                             ((0x001FFC00&(data))>>10)
#define PLL_SCPU2_get_FCODE_T_SCPU(data)                                             ((0x001FFC00&(data))>>10)
#define PLL_SCPU2_REG_OC_STEP_SET_shift                                              (0)
#define PLL_SCPU2_REG_OC_STEP_SET_mask                                               (0x000003FF)
#define PLL_SCPU2_REG_OC_STEP_SET(data)                                              (0x000003FF&((data)<<0))
#define PLL_SCPU2_REG_OC_STEP_SET_src(data)                                          ((0x000003FF&(data))>>0)
#define PLL_SCPU2_get_REG_OC_STEP_SET(data)                                          ((0x000003FF&(data))>>0)


#define PLL_SCPU3                                                                    0x98000108
#define PLL_SCPU3_reg_addr                                                           "0x98000108"
#define PLL_SCPU3_reg                                                                0x98000108
#define set_PLL_SCPU3_reg(data)   (*((volatile unsigned int*) PLL_SCPU3_reg)=data)
#define get_PLL_SCPU3_reg   (*((volatile unsigned int*) PLL_SCPU3_reg))
#define PLL_SCPU3_inst_adr                                                           "0x0042"
#define PLL_SCPU3_inst                                                               0x0042
#define PLL_SCPU3_REG_SEL_OC_MODE_shift                                              (25)
#define PLL_SCPU3_REG_SEL_OC_MODE_mask                                               (0x06000000)
#define PLL_SCPU3_REG_SEL_OC_MODE(data)                                              (0x06000000&((data)<<25))
#define PLL_SCPU3_REG_SEL_OC_MODE_src(data)                                          ((0x06000000&(data))>>25)
#define PLL_SCPU3_get_REG_SEL_OC_MODE(data)                                          ((0x06000000&(data))>>25)
#define PLL_SCPU3_REG_HS_OC_STOP_DIFF_shift                                          (23)
#define PLL_SCPU3_REG_HS_OC_STOP_DIFF_mask                                           (0x01800000)
#define PLL_SCPU3_REG_HS_OC_STOP_DIFF(data)                                          (0x01800000&((data)<<23))
#define PLL_SCPU3_REG_HS_OC_STOP_DIFF_src(data)                                      ((0x01800000&(data))>>23)
#define PLL_SCPU3_get_REG_HS_OC_STOP_DIFF(data)                                      ((0x01800000&(data))>>23)
#define PLL_SCPU3_REG_OC_DONE_delay_shift                                            (17)
#define PLL_SCPU3_REG_OC_DONE_delay_mask                                             (0x007E0000)
#define PLL_SCPU3_REG_OC_DONE_delay(data)                                            (0x007E0000&((data)<<17))
#define PLL_SCPU3_REG_OC_DONE_delay_src(data)                                        ((0x007E0000&(data))>>17)
#define PLL_SCPU3_get_REG_OC_DONE_delay(data)                                        ((0x007E0000&(data))>>17)
#define PLL_SCPU3_REG_PI_CUR_SEL_shift                                               (15)
#define PLL_SCPU3_REG_PI_CUR_SEL_mask                                                (0x00018000)
#define PLL_SCPU3_REG_PI_CUR_SEL(data)                                               (0x00018000&((data)<<15))
#define PLL_SCPU3_REG_PI_CUR_SEL_src(data)                                           ((0x00018000&(data))>>15)
#define PLL_SCPU3_get_REG_PI_CUR_SEL(data)                                           ((0x00018000&(data))>>15)
#define PLL_SCPU3_REG_F390K_shift                                                    (13)
#define PLL_SCPU3_REG_F390K_mask                                                     (0x00006000)
#define PLL_SCPU3_REG_F390K(data)                                                    (0x00006000&((data)<<13))
#define PLL_SCPU3_REG_F390K_src(data)                                                ((0x00006000&(data))>>13)
#define PLL_SCPU3_get_REG_F390K(data)                                                ((0x00006000&(data))>>13)
#define PLL_SCPU3_REG_TIME0_CK_shift                                                 (10)
#define PLL_SCPU3_REG_TIME0_CK_mask                                                  (0x00001C00)
#define PLL_SCPU3_REG_TIME0_CK(data)                                                 (0x00001C00&((data)<<10))
#define PLL_SCPU3_REG_TIME0_CK_src(data)                                             ((0x00001C00&(data))>>10)
#define PLL_SCPU3_get_REG_TIME0_CK(data)                                             ((0x00001C00&(data))>>10)
#define PLL_SCPU3_REG_TIME_RDY_CKOUT_shift                                           (8)
#define PLL_SCPU3_REG_TIME_RDY_CKOUT_mask                                            (0x00000300)
#define PLL_SCPU3_REG_TIME_RDY_CKOUT(data)                                           (0x00000300&((data)<<8))
#define PLL_SCPU3_REG_TIME_RDY_CKOUT_src(data)                                       ((0x00000300&(data))>>8)
#define PLL_SCPU3_get_REG_TIME_RDY_CKOUT(data)                                       ((0x00000300&(data))>>8)
#define PLL_SCPU3_REG_TIME2_RST_WIDTH_shift                                          (6)
#define PLL_SCPU3_REG_TIME2_RST_WIDTH_mask                                           (0x000000C0)
#define PLL_SCPU3_REG_TIME2_RST_WIDTH(data)                                          (0x000000C0&((data)<<6))
#define PLL_SCPU3_REG_TIME2_RST_WIDTH_src(data)                                      ((0x000000C0&(data))>>6)
#define PLL_SCPU3_get_REG_TIME2_RST_WIDTH(data)                                      ((0x000000C0&(data))>>6)
#define PLL_SCPU3_REG_BYPASS_PI_shift                                                (5)
#define PLL_SCPU3_REG_BYPASS_PI_mask                                                 (0x00000020)
#define PLL_SCPU3_REG_BYPASS_PI(data)                                                (0x00000020&((data)<<5))
#define PLL_SCPU3_REG_BYPASS_PI_src(data)                                            ((0x00000020&(data))>>5)
#define PLL_SCPU3_get_REG_BYPASS_PI(data)                                            ((0x00000020&(data))>>5)
#define PLL_SCPU3_REG_SDM_ORDER_shift                                                (4)
#define PLL_SCPU3_REG_SDM_ORDER_mask                                                 (0x00000010)
#define PLL_SCPU3_REG_SDM_ORDER(data)                                                (0x00000010&((data)<<4))
#define PLL_SCPU3_REG_SDM_ORDER_src(data)                                            ((0x00000010&(data))>>4)
#define PLL_SCPU3_get_REG_SDM_ORDER(data)                                            ((0x00000010&(data))>>4)
#define PLL_SCPU3_REG_EN_WDOG_shift                                                  (3)
#define PLL_SCPU3_REG_EN_WDOG_mask                                                   (0x00000008)
#define PLL_SCPU3_REG_EN_WDOG(data)                                                  (0x00000008&((data)<<3))
#define PLL_SCPU3_REG_EN_WDOG_src(data)                                              ((0x00000008&(data))>>3)
#define PLL_SCPU3_get_REG_EN_WDOG(data)                                              ((0x00000008&(data))>>3)
#define PLL_SCPU3_REG_EN_PI_DEBUG_shift                                              (2)
#define PLL_SCPU3_REG_EN_PI_DEBUG_mask                                               (0x00000004)
#define PLL_SCPU3_REG_EN_PI_DEBUG(data)                                              (0x00000004&((data)<<2))
#define PLL_SCPU3_REG_EN_PI_DEBUG_src(data)                                          ((0x00000004&(data))>>2)
#define PLL_SCPU3_get_REG_EN_PI_DEBUG(data)                                          ((0x00000004&(data))>>2)
#define PLL_SCPU3_RSTB_shift                                                         (1)
#define PLL_SCPU3_RSTB_mask                                                          (0x00000002)
#define PLL_SCPU3_RSTB(data)                                                         (0x00000002&((data)<<1))
#define PLL_SCPU3_RSTB_src(data)                                                     ((0x00000002&(data))>>1)
#define PLL_SCPU3_get_RSTB(data)                                                     ((0x00000002&(data))>>1)
#define PLL_SCPU3_OC_EN_shift                                                        (0)
#define PLL_SCPU3_OC_EN_mask                                                         (0x00000001)
#define PLL_SCPU3_OC_EN(data)                                                        (0x00000001&((data)<<0))
#define PLL_SCPU3_OC_EN_src(data)                                                    ((0x00000001&(data))>>0)
#define PLL_SCPU3_get_OC_EN(data)                                                    ((0x00000001&(data))>>0)


#define PLL_ACPU1                                                                    0x9800010c
#define PLL_ACPU1_reg_addr                                                           "0x9800010C"
#define PLL_ACPU1_reg                                                                0x9800010C
#define set_PLL_ACPU1_reg(data)   (*((volatile unsigned int*) PLL_ACPU1_reg)=data)
#define get_PLL_ACPU1_reg   (*((volatile unsigned int*) PLL_ACPU1_reg))
#define PLL_ACPU1_inst_adr                                                           "0x0043"
#define PLL_ACPU1_inst                                                               0x0043
#define PLL_ACPU1_REG_PLLACPU_WDRST_shift                                            (29)
#define PLL_ACPU1_REG_PLLACPU_WDRST_mask                                             (0x20000000)
#define PLL_ACPU1_REG_PLLACPU_WDRST(data)                                            (0x20000000&((data)<<29))
#define PLL_ACPU1_REG_PLLACPU_WDRST_src(data)                                        ((0x20000000&(data))>>29)
#define PLL_ACPU1_get_REG_PLLACPU_WDRST(data)                                        ((0x20000000&(data))>>29)
#define PLL_ACPU1_REG_PLLACPU_WDSET_shift                                            (28)
#define PLL_ACPU1_REG_PLLACPU_WDSET_mask                                             (0x10000000)
#define PLL_ACPU1_REG_PLLACPU_WDSET(data)                                            (0x10000000&((data)<<28))
#define PLL_ACPU1_REG_PLLACPU_WDSET_src(data)                                        ((0x10000000&(data))>>28)
#define PLL_ACPU1_get_REG_PLLACPU_WDSET(data)                                        ((0x10000000&(data))>>28)
#define PLL_ACPU1_REG_PLLACPU_CS_shift                                               (26)
#define PLL_ACPU1_REG_PLLACPU_CS_mask                                                (0x0C000000)
#define PLL_ACPU1_REG_PLLACPU_CS(data)                                               (0x0C000000&((data)<<26))
#define PLL_ACPU1_REG_PLLACPU_CS_src(data)                                           ((0x0C000000&(data))>>26)
#define PLL_ACPU1_get_REG_PLLACPU_CS(data)                                           ((0x0C000000&(data))>>26)
#define PLL_ACPU1_REG_PLLACPU_O_shift                                                (24)
#define PLL_ACPU1_REG_PLLACPU_O_mask                                                 (0x03000000)
#define PLL_ACPU1_REG_PLLACPU_O(data)                                                (0x03000000&((data)<<24))
#define PLL_ACPU1_REG_PLLACPU_O_src(data)                                            ((0x03000000&(data))>>24)
#define PLL_ACPU1_get_REG_PLLACPU_O(data)                                            ((0x03000000&(data))>>24)
#define PLL_ACPU1_REG_PLLACPU_RS_shift                                               (21)
#define PLL_ACPU1_REG_PLLACPU_RS_mask                                                (0x00E00000)
#define PLL_ACPU1_REG_PLLACPU_RS(data)                                               (0x00E00000&((data)<<21))
#define PLL_ACPU1_REG_PLLACPU_RS_src(data)                                           ((0x00E00000&(data))>>21)
#define PLL_ACPU1_get_REG_PLLACPU_RS(data)                                           ((0x00E00000&(data))>>21)
#define PLL_ACPU1_PLLACPU_N_shift                                                    (19)
#define PLL_ACPU1_PLLACPU_N_mask                                                     (0x00180000)
#define PLL_ACPU1_PLLACPU_N(data)                                                    (0x00180000&((data)<<19))
#define PLL_ACPU1_PLLACPU_N_src(data)                                                ((0x00180000&(data))>>19)
#define PLL_ACPU1_get_PLLACPU_N(data)                                                ((0x00180000&(data))>>19)
#define PLL_ACPU1_PLLACPU_M_shift                                                    (12)
#define PLL_ACPU1_PLLACPU_M_mask                                                     (0x0007F000)
#define PLL_ACPU1_PLLACPU_M(data)                                                    (0x0007F000&((data)<<12))
#define PLL_ACPU1_PLLACPU_M_src(data)                                                ((0x0007F000&(data))>>12)
#define PLL_ACPU1_get_PLLACPU_M(data)                                                ((0x0007F000&(data))>>12)
#define PLL_ACPU1_PLLACPU_IP_shift                                                   (9)
#define PLL_ACPU1_PLLACPU_IP_mask                                                    (0x00000E00)
#define PLL_ACPU1_PLLACPU_IP(data)                                                   (0x00000E00&((data)<<9))
#define PLL_ACPU1_PLLACPU_IP_src(data)                                               ((0x00000E00&(data))>>9)
#define PLL_ACPU1_get_PLLACPU_IP(data)                                               ((0x00000E00&(data))>>9)
#define PLL_ACPU1_PLLACPU_TST_shift                                                  (0)
#define PLL_ACPU1_PLLACPU_TST_mask                                                   (0x00000001)
#define PLL_ACPU1_PLLACPU_TST(data)                                                  (0x00000001&((data)<<0))
#define PLL_ACPU1_PLLACPU_TST_src(data)                                              ((0x00000001&(data))>>0)
#define PLL_ACPU1_get_PLLACPU_TST(data)                                              ((0x00000001&(data))>>0)


#define PLL_ACPU2                                                                    0x98000110
#define PLL_ACPU2_reg_addr                                                           "0x98000110"
#define PLL_ACPU2_reg                                                                0x98000110
#define set_PLL_ACPU2_reg(data)   (*((volatile unsigned int*) PLL_ACPU2_reg)=data)
#define get_PLL_ACPU2_reg   (*((volatile unsigned int*) PLL_ACPU2_reg))
#define PLL_ACPU2_inst_adr                                                           "0x0044"
#define PLL_ACPU2_inst                                                               0x0044
#define PLL_ACPU2_PLLACPU_OEB_shift                                                  (2)
#define PLL_ACPU2_PLLACPU_OEB_mask                                                   (0x00000004)
#define PLL_ACPU2_PLLACPU_OEB(data)                                                  (0x00000004&((data)<<2))
#define PLL_ACPU2_PLLACPU_OEB_src(data)                                              ((0x00000004&(data))>>2)
#define PLL_ACPU2_get_PLLACPU_OEB(data)                                              ((0x00000004&(data))>>2)
#define PLL_ACPU2_PLLACPU_RSTB_shift                                                 (1)
#define PLL_ACPU2_PLLACPU_RSTB_mask                                                  (0x00000002)
#define PLL_ACPU2_PLLACPU_RSTB(data)                                                 (0x00000002&((data)<<1))
#define PLL_ACPU2_PLLACPU_RSTB_src(data)                                             ((0x00000002&(data))>>1)
#define PLL_ACPU2_get_PLLACPU_RSTB(data)                                             ((0x00000002&(data))>>1)
#define PLL_ACPU2_PLLACPU_POW_shift                                                  (0)
#define PLL_ACPU2_PLLACPU_POW_mask                                                   (0x00000001)
#define PLL_ACPU2_PLLACPU_POW(data)                                                  (0x00000001&((data)<<0))
#define PLL_ACPU2_PLLACPU_POW_src(data)                                              ((0x00000001&(data))>>0)
#define PLL_ACPU2_get_PLLACPU_POW(data)                                              ((0x00000001&(data))>>0)


#define PLL_VCPU1                                                                    0x98000114
#define PLL_VCPU1_reg_addr                                                           "0x98000114"
#define PLL_VCPU1_reg                                                                0x98000114
#define set_PLL_VCPU1_reg(data)   (*((volatile unsigned int*) PLL_VCPU1_reg)=data)
#define get_PLL_VCPU1_reg   (*((volatile unsigned int*) PLL_VCPU1_reg))
#define PLL_VCPU1_inst_adr                                                           "0x0045"
#define PLL_VCPU1_inst                                                               0x0045
#define PLL_VCPU1_REG_PLLVCPU_WDRST_shift                                            (22)
#define PLL_VCPU1_REG_PLLVCPU_WDRST_mask                                             (0x00400000)
#define PLL_VCPU1_REG_PLLVCPU_WDRST(data)                                            (0x00400000&((data)<<22))
#define PLL_VCPU1_REG_PLLVCPU_WDRST_src(data)                                        ((0x00400000&(data))>>22)
#define PLL_VCPU1_get_REG_PLLVCPU_WDRST(data)                                        ((0x00400000&(data))>>22)
#define PLL_VCPU1_REG_PLLVCPU_WDSET_shift                                            (21)
#define PLL_VCPU1_REG_PLLVCPU_WDSET_mask                                             (0x00200000)
#define PLL_VCPU1_REG_PLLVCPU_WDSET(data)                                            (0x00200000&((data)<<21))
#define PLL_VCPU1_REG_PLLVCPU_WDSET_src(data)                                        ((0x00200000&(data))>>21)
#define PLL_VCPU1_get_REG_PLLVCPU_WDSET(data)                                        ((0x00200000&(data))>>21)
#define PLL_VCPU1_REG_PLLVCPU_CS_shift                                               (19)
#define PLL_VCPU1_REG_PLLVCPU_CS_mask                                                (0x00180000)
#define PLL_VCPU1_REG_PLLVCPU_CS(data)                                               (0x00180000&((data)<<19))
#define PLL_VCPU1_REG_PLLVCPU_CS_src(data)                                           ((0x00180000&(data))>>19)
#define PLL_VCPU1_get_REG_PLLVCPU_CS(data)                                           ((0x00180000&(data))>>19)
#define PLL_VCPU1_REG_PLLVCPU_O_shift                                                (17)
#define PLL_VCPU1_REG_PLLVCPU_O_mask                                                 (0x00060000)
#define PLL_VCPU1_REG_PLLVCPU_O(data)                                                (0x00060000&((data)<<17))
#define PLL_VCPU1_REG_PLLVCPU_O_src(data)                                            ((0x00060000&(data))>>17)
#define PLL_VCPU1_get_REG_PLLVCPU_O(data)                                            ((0x00060000&(data))>>17)
#define PLL_VCPU1_REG_PLLVCPU_RS_shift                                               (14)
#define PLL_VCPU1_REG_PLLVCPU_RS_mask                                                (0x0001C000)
#define PLL_VCPU1_REG_PLLVCPU_RS(data)                                               (0x0001C000&((data)<<14))
#define PLL_VCPU1_REG_PLLVCPU_RS_src(data)                                           ((0x0001C000&(data))>>14)
#define PLL_VCPU1_get_REG_PLLVCPU_RS(data)                                           ((0x0001C000&(data))>>14)
#define PLL_VCPU1_PLLVCPU_N_shift                                                    (12)
#define PLL_VCPU1_PLLVCPU_N_mask                                                     (0x00003000)
#define PLL_VCPU1_PLLVCPU_N(data)                                                    (0x00003000&((data)<<12))
#define PLL_VCPU1_PLLVCPU_N_src(data)                                                ((0x00003000&(data))>>12)
#define PLL_VCPU1_get_PLLVCPU_N(data)                                                ((0x00003000&(data))>>12)
#define PLL_VCPU1_PLLVCPU_M_shift                                                    (4)
#define PLL_VCPU1_PLLVCPU_M_mask                                                     (0x00000FF0)
#define PLL_VCPU1_PLLVCPU_M(data)                                                    (0x00000FF0&((data)<<4))
#define PLL_VCPU1_PLLVCPU_M_src(data)                                                ((0x00000FF0&(data))>>4)
#define PLL_VCPU1_get_PLLVCPU_M(data)                                                ((0x00000FF0&(data))>>4)
#define PLL_VCPU1_PLLVCPU_IP_shift                                                   (1)
#define PLL_VCPU1_PLLVCPU_IP_mask                                                    (0x000000E0)
#define PLL_VCPU1_PLLVCPU_IP(data)                                                   (0x000000E0&((data)<<1))
#define PLL_VCPU1_PLLVCPU_IP_src(data)                                               ((0x000000E0&(data))>>1)
#define PLL_VCPU1_get_PLLVCPU_IP(data)                                               ((0x000000E0&(data))>>1)
#define PLL_VCPU1_PLLVCPU_TST_shift                                                  (0)
#define PLL_VCPU1_PLLVCPU_TST_mask                                                   (0x00000001)
#define PLL_VCPU1_PLLVCPU_TST(data)                                                  (0x00000001&((data)<<0))
#define PLL_VCPU1_PLLVCPU_TST_src(data)                                              ((0x00000001&(data))>>0)
#define PLL_VCPU1_get_PLLVCPU_TST(data)                                              ((0x00000001&(data))>>0)


#define PLL_DISP_SD1                                                                 0x9800011c
#define PLL_DISP_SD1_reg_addr                                                        "0x9800011C"
#define PLL_DISP_SD1_reg                                                             0x9800011C
#define set_PLL_DISP_SD1_reg(data)   (*((volatile unsigned int*) PLL_DISP_SD1_reg)=data)
#define get_PLL_DISP_SD1_reg   (*((volatile unsigned int*) PLL_DISP_SD1_reg))
#define PLL_DISP_SD1_inst_adr                                                        "0x0047"
#define PLL_DISP_SD1_inst                                                            0x0047
#define PLL_DISP_SD1_PLLDDSA_N_shift                                                 (30)
#define PLL_DISP_SD1_PLLDDSA_N_mask                                                  (0xC0000000)
#define PLL_DISP_SD1_PLLDDSA_N(data)                                                 (0xC0000000&((data)<<30))
#define PLL_DISP_SD1_PLLDDSA_N_src(data)                                             ((0xC0000000&(data))>>30)
#define PLL_DISP_SD1_get_PLLDDSA_N(data)                                             ((0xC0000000&(data))>>30)
#define PLL_DISP_SD1_PLLDDSA_M_shift                                                 (23)
#define PLL_DISP_SD1_PLLDDSA_M_mask                                                  (0x3F800000)
#define PLL_DISP_SD1_PLLDDSA_M(data)                                                 (0x3F800000&((data)<<23))
#define PLL_DISP_SD1_PLLDDSA_M_src(data)                                             ((0x3F800000&(data))>>23)
#define PLL_DISP_SD1_get_PLLDDSA_M(data)                                             ((0x3F800000&(data))>>23)
#define PLL_DISP_SD1_PLLDDSA_IP_shift                                                (20)
#define PLL_DISP_SD1_PLLDDSA_IP_mask                                                 (0x00700000)
#define PLL_DISP_SD1_PLLDDSA_IP(data)                                                (0x00700000&((data)<<20))
#define PLL_DISP_SD1_PLLDDSA_IP_src(data)                                            ((0x00700000&(data))>>20)
#define PLL_DISP_SD1_get_PLLDDSA_IP(data)                                            ((0x00700000&(data))>>20)
#define PLL_DISP_SD1_PLLDDSA_RS_shift                                                (17)
#define PLL_DISP_SD1_PLLDDSA_RS_mask                                                 (0x000E0000)
#define PLL_DISP_SD1_PLLDDSA_RS(data)                                                (0x000E0000&((data)<<17))
#define PLL_DISP_SD1_PLLDDSA_RS_src(data)                                            ((0x000E0000&(data))>>17)
#define PLL_DISP_SD1_get_PLLDDSA_RS(data)                                            ((0x000E0000&(data))>>17)
#define PLL_DISP_SD1_PLLDDSA_CS_shift                                                (15)
#define PLL_DISP_SD1_PLLDDSA_CS_mask                                                 (0x00018000)
#define PLL_DISP_SD1_PLLDDSA_CS(data)                                                (0x00018000&((data)<<15))
#define PLL_DISP_SD1_PLLDDSA_CS_src(data)                                            ((0x00018000&(data))>>15)
#define PLL_DISP_SD1_get_PLLDDSA_CS(data)                                            ((0x00018000&(data))>>15)
#define PLL_DISP_SD1_PLLDDSA_CP_shift                                                (13)
#define PLL_DISP_SD1_PLLDDSA_CP_mask                                                 (0x00006000)
#define PLL_DISP_SD1_PLLDDSA_CP(data)                                                (0x00006000&((data)<<13))
#define PLL_DISP_SD1_PLLDDSA_CP_src(data)                                            ((0x00006000&(data))>>13)
#define PLL_DISP_SD1_get_PLLDDSA_CP(data)                                            ((0x00006000&(data))>>13)
#define PLL_DISP_SD1_PLLDDSA_R3_shift                                                (10)
#define PLL_DISP_SD1_PLLDDSA_R3_mask                                                 (0x00001C00)
#define PLL_DISP_SD1_PLLDDSA_R3(data)                                                (0x00001C00&((data)<<10))
#define PLL_DISP_SD1_PLLDDSA_R3_src(data)                                            ((0x00001C00&(data))>>10)
#define PLL_DISP_SD1_get_PLLDDSA_R3(data)                                            ((0x00001C00&(data))>>10)
#define PLL_DISP_SD1_PLLDDSA_C3_shift                                                (8)
#define PLL_DISP_SD1_PLLDDSA_C3_mask                                                 (0x00000300)
#define PLL_DISP_SD1_PLLDDSA_C3(data)                                                (0x00000300&((data)<<8))
#define PLL_DISP_SD1_PLLDDSA_C3_src(data)                                            ((0x00000300&(data))>>8)
#define PLL_DISP_SD1_get_PLLDDSA_C3(data)                                            ((0x00000300&(data))>>8)
#define PLL_DISP_SD1_PLLDDSA_PI_RL_shift                                             (6)
#define PLL_DISP_SD1_PLLDDSA_PI_RL_mask                                              (0x000000C0)
#define PLL_DISP_SD1_PLLDDSA_PI_RL(data)                                             (0x000000C0&((data)<<6))
#define PLL_DISP_SD1_PLLDDSA_PI_RL_src(data)                                         ((0x000000C0&(data))>>6)
#define PLL_DISP_SD1_get_PLLDDSA_PI_RL(data)                                         ((0x000000C0&(data))>>6)
#define PLL_DISP_SD1_PLLDDSA_PI_RS_shift                                             (4)
#define PLL_DISP_SD1_PLLDDSA_PI_RS_mask                                              (0x00000030)
#define PLL_DISP_SD1_PLLDDSA_PI_RS(data)                                             (0x00000030&((data)<<4))
#define PLL_DISP_SD1_PLLDDSA_PI_RS_src(data)                                         ((0x00000030&(data))>>4)
#define PLL_DISP_SD1_get_PLLDDSA_PI_RS(data)                                         ((0x00000030&(data))>>4)
#define PLL_DISP_SD1_PLLDDSA_PI_BIAS_shift                                           (2)
#define PLL_DISP_SD1_PLLDDSA_PI_BIAS_mask                                            (0x0000000C)
#define PLL_DISP_SD1_PLLDDSA_PI_BIAS(data)                                           (0x0000000C&((data)<<2))
#define PLL_DISP_SD1_PLLDDSA_PI_BIAS_src(data)                                       ((0x0000000C&(data))>>2)
#define PLL_DISP_SD1_get_PLLDDSA_PI_BIAS(data)                                       ((0x0000000C&(data))>>2)
#define PLL_DISP_SD1_PLLDDSA_WDMODE_shift                                            (0)
#define PLL_DISP_SD1_PLLDDSA_WDMODE_mask                                             (0x00000003)
#define PLL_DISP_SD1_PLLDDSA_WDMODE(data)                                            (0x00000003&((data)<<0))
#define PLL_DISP_SD1_PLLDDSA_WDMODE_src(data)                                        ((0x00000003&(data))>>0)
#define PLL_DISP_SD1_get_PLLDDSA_WDMODE(data)                                        ((0x00000003&(data))>>0)


#define PLL_DISP_SD2                                                                 0x98000120
#define PLL_DISP_SD2_reg_addr                                                        "0x98000120"
#define PLL_DISP_SD2_reg                                                             0x98000120
#define set_PLL_DISP_SD2_reg(data)   (*((volatile unsigned int*) PLL_DISP_SD2_reg)=data)
#define get_PLL_DISP_SD2_reg   (*((volatile unsigned int*) PLL_DISP_SD2_reg))
#define PLL_DISP_SD2_inst_adr                                                        "0x0048"
#define PLL_DISP_SD2_inst                                                            0x0048
#define PLL_DISP_SD2_write_en11_shift                                                (28)
#define PLL_DISP_SD2_write_en11_mask                                                 (0x10000000)
#define PLL_DISP_SD2_write_en11(data)                                                (0x10000000&((data)<<28))
#define PLL_DISP_SD2_write_en11_src(data)                                            ((0x10000000&(data))>>28)
#define PLL_DISP_SD2_get_write_en11(data)                                            ((0x10000000&(data))>>28)
#define PLL_DISP_SD2_psaud_1a_phase_sel_shift                                        (27)
#define PLL_DISP_SD2_psaud_1a_phase_sel_mask                                         (0x08000000)
#define PLL_DISP_SD2_psaud_1a_phase_sel(data)                                        (0x08000000&((data)<<27))
#define PLL_DISP_SD2_psaud_1a_phase_sel_src(data)                                    ((0x08000000&(data))>>27)
#define PLL_DISP_SD2_get_psaud_1a_phase_sel(data)                                    ((0x08000000&(data))>>27)
#define PLL_DISP_SD2_psaud_2a_phase_sel_shift                                        (26)
#define PLL_DISP_SD2_psaud_2a_phase_sel_mask                                         (0x04000000)
#define PLL_DISP_SD2_psaud_2a_phase_sel(data)                                        (0x04000000&((data)<<26))
#define PLL_DISP_SD2_psaud_2a_phase_sel_src(data)                                    ((0x04000000&(data))>>26)
#define PLL_DISP_SD2_get_psaud_2a_phase_sel(data)                                    ((0x04000000&(data))>>26)
#define PLL_DISP_SD2_write_en10_shift                                                (25)
#define PLL_DISP_SD2_write_en10_mask                                                 (0x02000000)
#define PLL_DISP_SD2_write_en10(data)                                                (0x02000000&((data)<<25))
#define PLL_DISP_SD2_write_en10_src(data)                                            ((0x02000000&(data))>>25)
#define PLL_DISP_SD2_get_write_en10(data)                                            ((0x02000000&(data))>>25)
#define PLL_DISP_SD2_pcr_a_smooth_en_shift                                           (24)
#define PLL_DISP_SD2_pcr_a_smooth_en_mask                                            (0x01000000)
#define PLL_DISP_SD2_pcr_a_smooth_en(data)                                           (0x01000000&((data)<<24))
#define PLL_DISP_SD2_pcr_a_smooth_en_src(data)                                       ((0x01000000&(data))>>24)
#define PLL_DISP_SD2_get_pcr_a_smooth_en(data)                                       ((0x01000000&(data))>>24)
#define PLL_DISP_SD2_write_en9_shift                                                 (23)
#define PLL_DISP_SD2_write_en9_mask                                                  (0x00800000)
#define PLL_DISP_SD2_write_en9(data)                                                 (0x00800000&((data)<<23))
#define PLL_DISP_SD2_write_en9_src(data)                                             ((0x00800000&(data))>>23)
#define PLL_DISP_SD2_get_write_en9(data)                                             ((0x00800000&(data))>>23)
#define PLL_DISP_SD2_pcr_a_phase_sel_shift                                           (22)
#define PLL_DISP_SD2_pcr_a_phase_sel_mask                                            (0x00400000)
#define PLL_DISP_SD2_pcr_a_phase_sel(data)                                           (0x00400000&((data)<<22))
#define PLL_DISP_SD2_pcr_a_phase_sel_src(data)                                       ((0x00400000&(data))>>22)
#define PLL_DISP_SD2_get_pcr_a_phase_sel(data)                                       ((0x00400000&(data))>>22)
#define PLL_DISP_SD2_write_en8_shift                                                 (21)
#define PLL_DISP_SD2_write_en8_mask                                                  (0x00200000)
#define PLL_DISP_SD2_write_en8(data)                                                 (0x00200000&((data)<<21))
#define PLL_DISP_SD2_write_en8_src(data)                                             ((0x00200000&(data))>>21)
#define PLL_DISP_SD2_get_write_en8(data)                                             ((0x00200000&(data))>>21)
#define PLL_DISP_SD2_pcr_a_ctl_en_shift                                              (20)
#define PLL_DISP_SD2_pcr_a_ctl_en_mask                                               (0x00100000)
#define PLL_DISP_SD2_pcr_a_ctl_en(data)                                              (0x00100000&((data)<<20))
#define PLL_DISP_SD2_pcr_a_ctl_en_src(data)                                          ((0x00100000&(data))>>20)
#define PLL_DISP_SD2_get_pcr_a_ctl_en(data)                                          ((0x00100000&(data))>>20)
#define PLL_DISP_SD2_write_en7_shift                                                 (19)
#define PLL_DISP_SD2_write_en7_mask                                                  (0x00080000)
#define PLL_DISP_SD2_write_en7(data)                                                 (0x00080000&((data)<<19))
#define PLL_DISP_SD2_write_en7_src(data)                                             ((0x00080000&(data))>>19)
#define PLL_DISP_SD2_get_write_en7(data)                                             ((0x00080000&(data))>>19)
#define PLL_DISP_SD2_PLLDDSA_FUPDN_shift                                             (18)
#define PLL_DISP_SD2_PLLDDSA_FUPDN_mask                                              (0x00040000)
#define PLL_DISP_SD2_PLLDDSA_FUPDN(data)                                             (0x00040000&((data)<<18))
#define PLL_DISP_SD2_PLLDDSA_FUPDN_src(data)                                         ((0x00040000&(data))>>18)
#define PLL_DISP_SD2_get_PLLDDSA_FUPDN(data)                                         ((0x00040000&(data))>>18)
#define PLL_DISP_SD2_write_en6_shift                                                 (17)
#define PLL_DISP_SD2_write_en6_mask                                                  (0x00020000)
#define PLL_DISP_SD2_write_en6(data)                                                 (0x00020000&((data)<<17))
#define PLL_DISP_SD2_write_en6_src(data)                                             ((0x00020000&(data))>>17)
#define PLL_DISP_SD2_get_write_en6(data)                                             ((0x00020000&(data))>>17)
#define PLL_DISP_SD2_PLLDDSA_DDSEN_shift                                             (16)
#define PLL_DISP_SD2_PLLDDSA_DDSEN_mask                                              (0x00010000)
#define PLL_DISP_SD2_PLLDDSA_DDSEN(data)                                             (0x00010000&((data)<<16))
#define PLL_DISP_SD2_PLLDDSA_DDSEN_src(data)                                         ((0x00010000&(data))>>16)
#define PLL_DISP_SD2_get_PLLDDSA_DDSEN(data)                                         ((0x00010000&(data))>>16)
#define PLL_DISP_SD2_write_en5_shift                                                 (15)
#define PLL_DISP_SD2_write_en5_mask                                                  (0x00008000)
#define PLL_DISP_SD2_write_en5(data)                                                 (0x00008000&((data)<<15))
#define PLL_DISP_SD2_write_en5_src(data)                                             ((0x00008000&(data))>>15)
#define PLL_DISP_SD2_get_write_en5(data)                                             ((0x00008000&(data))>>15)
#define PLL_DISP_SD2_PLLDDSA_VCORB_shift                                             (14)
#define PLL_DISP_SD2_PLLDDSA_VCORB_mask                                              (0x00004000)
#define PLL_DISP_SD2_PLLDDSA_VCORB(data)                                             (0x00004000&((data)<<14))
#define PLL_DISP_SD2_PLLDDSA_VCORB_src(data)                                         ((0x00004000&(data))>>14)
#define PLL_DISP_SD2_get_PLLDDSA_VCORB(data)                                         ((0x00004000&(data))>>14)
#define PLL_DISP_SD2_write_en4_shift                                                 (13)
#define PLL_DISP_SD2_write_en4_mask                                                  (0x00002000)
#define PLL_DISP_SD2_write_en4(data)                                                 (0x00002000&((data)<<13))
#define PLL_DISP_SD2_write_en4_src(data)                                             ((0x00002000&(data))>>13)
#define PLL_DISP_SD2_get_write_en4(data)                                             ((0x00002000&(data))>>13)
#define PLL_DISP_SD2_PLLDDSA_TST_shift                                               (12)
#define PLL_DISP_SD2_PLLDDSA_TST_mask                                                (0x00001000)
#define PLL_DISP_SD2_PLLDDSA_TST(data)                                               (0x00001000&((data)<<12))
#define PLL_DISP_SD2_PLLDDSA_TST_src(data)                                           ((0x00001000&(data))>>12)
#define PLL_DISP_SD2_get_PLLDDSA_TST(data)                                           ((0x00001000&(data))>>12)
#define PLL_DISP_SD2_PLLDDSA_PSTST_shift                                             (11)
#define PLL_DISP_SD2_PLLDDSA_PSTST_mask                                              (0x00000800)
#define PLL_DISP_SD2_PLLDDSA_PSTST(data)                                             (0x00000800&((data)<<11))
#define PLL_DISP_SD2_PLLDDSA_PSTST_src(data)                                         ((0x00000800&(data))>>11)
#define PLL_DISP_SD2_get_PLLDDSA_PSTST(data)                                         ((0x00000800&(data))>>11)
#define PLL_DISP_SD2_write_en3_shift                                                 (10)
#define PLL_DISP_SD2_write_en3_mask                                                  (0x00000400)
#define PLL_DISP_SD2_write_en3(data)                                                 (0x00000400&((data)<<10))
#define PLL_DISP_SD2_write_en3_src(data)                                             ((0x00000400&(data))>>10)
#define PLL_DISP_SD2_get_write_en3(data)                                             ((0x00000400&(data))>>10)
#define PLL_DISP_SD2_PSAUD1A_FUPDN_shift                                             (9)
#define PLL_DISP_SD2_PSAUD1A_FUPDN_mask                                              (0x00000200)
#define PLL_DISP_SD2_PSAUD1A_FUPDN(data)                                             (0x00000200&((data)<<9))
#define PLL_DISP_SD2_PSAUD1A_FUPDN_src(data)                                         ((0x00000200&(data))>>9)
#define PLL_DISP_SD2_get_PSAUD1A_FUPDN(data)                                         ((0x00000200&(data))>>9)
#define PLL_DISP_SD2_PSAUD1A_DIV_shift                                               (8)
#define PLL_DISP_SD2_PSAUD1A_DIV_mask                                                (0x00000100)
#define PLL_DISP_SD2_PSAUD1A_DIV(data)                                               (0x00000100&((data)<<8))
#define PLL_DISP_SD2_PSAUD1A_DIV_src(data)                                           ((0x00000100&(data))>>8)
#define PLL_DISP_SD2_get_PSAUD1A_DIV(data)                                           ((0x00000100&(data))>>8)
#define PLL_DISP_SD2_write_en2_shift                                                 (7)
#define PLL_DISP_SD2_write_en2_mask                                                  (0x00000080)
#define PLL_DISP_SD2_write_en2(data)                                                 (0x00000080&((data)<<7))
#define PLL_DISP_SD2_write_en2_src(data)                                             ((0x00000080&(data))>>7)
#define PLL_DISP_SD2_get_write_en2(data)                                             ((0x00000080&(data))>>7)
#define PLL_DISP_SD2_PSAUD1A_TST_shift                                               (6)
#define PLL_DISP_SD2_PSAUD1A_TST_mask                                                (0x00000040)
#define PLL_DISP_SD2_PSAUD1A_TST(data)                                               (0x00000040&((data)<<6))
#define PLL_DISP_SD2_PSAUD1A_TST_src(data)                                           ((0x00000040&(data))>>6)
#define PLL_DISP_SD2_get_PSAUD1A_TST(data)                                           ((0x00000040&(data))>>6)
#define PLL_DISP_SD2_PSAUD1A_PSEN_shift                                              (5)
#define PLL_DISP_SD2_PSAUD1A_PSEN_mask                                               (0x00000020)
#define PLL_DISP_SD2_PSAUD1A_PSEN(data)                                              (0x00000020&((data)<<5))
#define PLL_DISP_SD2_PSAUD1A_PSEN_src(data)                                          ((0x00000020&(data))>>5)
#define PLL_DISP_SD2_get_PSAUD1A_PSEN(data)                                          ((0x00000020&(data))>>5)
#define PLL_DISP_SD2_write_en1_shift                                                 (4)
#define PLL_DISP_SD2_write_en1_mask                                                  (0x00000010)
#define PLL_DISP_SD2_write_en1(data)                                                 (0x00000010&((data)<<4))
#define PLL_DISP_SD2_write_en1_src(data)                                             ((0x00000010&(data))>>4)
#define PLL_DISP_SD2_get_write_en1(data)                                             ((0x00000010&(data))>>4)
#define PLL_DISP_SD2_PSAUD2A_FUPDN_shift                                             (3)
#define PLL_DISP_SD2_PSAUD2A_FUPDN_mask                                              (0x00000008)
#define PLL_DISP_SD2_PSAUD2A_FUPDN(data)                                             (0x00000008&((data)<<3))
#define PLL_DISP_SD2_PSAUD2A_FUPDN_src(data)                                         ((0x00000008&(data))>>3)
#define PLL_DISP_SD2_get_PSAUD2A_FUPDN(data)                                         ((0x00000008&(data))>>3)
#define PLL_DISP_SD2_PSAUD2A_DIV_shift                                               (2)
#define PLL_DISP_SD2_PSAUD2A_DIV_mask                                                (0x00000004)
#define PLL_DISP_SD2_PSAUD2A_DIV(data)                                               (0x00000004&((data)<<2))
#define PLL_DISP_SD2_PSAUD2A_DIV_src(data)                                           ((0x00000004&(data))>>2)
#define PLL_DISP_SD2_get_PSAUD2A_DIV(data)                                           ((0x00000004&(data))>>2)
#define PLL_DISP_SD2_PSAUD2A_TST_shift                                               (1)
#define PLL_DISP_SD2_PSAUD2A_TST_mask                                                (0x00000002)
#define PLL_DISP_SD2_PSAUD2A_TST(data)                                               (0x00000002&((data)<<1))
#define PLL_DISP_SD2_PSAUD2A_TST_src(data)                                           ((0x00000002&(data))>>1)
#define PLL_DISP_SD2_get_PSAUD2A_TST(data)                                           ((0x00000002&(data))>>1)
#define PLL_DISP_SD2_PSAUD2A_PSEN_shift                                              (0)
#define PLL_DISP_SD2_PSAUD2A_PSEN_mask                                               (0x00000001)
#define PLL_DISP_SD2_PSAUD2A_PSEN(data)                                              (0x00000001&((data)<<0))
#define PLL_DISP_SD2_PSAUD2A_PSEN_src(data)                                          ((0x00000001&(data))>>0)
#define PLL_DISP_SD2_get_PSAUD2A_PSEN(data)                                          ((0x00000001&(data))>>0)


#define PLL_DISP_SD3                                                                 0x98000124
#define PLL_DISP_SD3_reg_addr                                                        "0x98000124"
#define PLL_DISP_SD3_reg                                                             0x98000124
#define set_PLL_DISP_SD3_reg(data)   (*((volatile unsigned int*) PLL_DISP_SD3_reg)=data)
#define get_PLL_DISP_SD3_reg   (*((volatile unsigned int*) PLL_DISP_SD3_reg))
#define PLL_DISP_SD3_inst_adr                                                        "0x0049"
#define PLL_DISP_SD3_inst                                                            0x0049
#define PLL_DISP_SD3_PSAUD1A_OEB_shift                                               (3)
#define PLL_DISP_SD3_PSAUD1A_OEB_mask                                                (0x00000008)
#define PLL_DISP_SD3_PSAUD1A_OEB(data)                                               (0x00000008&((data)<<3))
#define PLL_DISP_SD3_PSAUD1A_OEB_src(data)                                           ((0x00000008&(data))>>3)
#define PLL_DISP_SD3_get_PSAUD1A_OEB(data)                                           ((0x00000008&(data))>>3)
#define PLL_DISP_SD3_PSAUD1A_RSTB_shift                                              (2)
#define PLL_DISP_SD3_PSAUD1A_RSTB_mask                                               (0x00000004)
#define PLL_DISP_SD3_PSAUD1A_RSTB(data)                                              (0x00000004&((data)<<2))
#define PLL_DISP_SD3_PSAUD1A_RSTB_src(data)                                          ((0x00000004&(data))>>2)
#define PLL_DISP_SD3_get_PSAUD1A_RSTB(data)                                          ((0x00000004&(data))>>2)
#define PLL_DISP_SD3_PSAUD2A_OEB_shift                                               (1)
#define PLL_DISP_SD3_PSAUD2A_OEB_mask                                                (0x00000002)
#define PLL_DISP_SD3_PSAUD2A_OEB(data)                                               (0x00000002&((data)<<1))
#define PLL_DISP_SD3_PSAUD2A_OEB_src(data)                                           ((0x00000002&(data))>>1)
#define PLL_DISP_SD3_get_PSAUD2A_OEB(data)                                           ((0x00000002&(data))>>1)
#define PLL_DISP_SD3_PSAUD2A_RSTB_shift                                              (0)
#define PLL_DISP_SD3_PSAUD2A_RSTB_mask                                               (0x00000001)
#define PLL_DISP_SD3_PSAUD2A_RSTB(data)                                              (0x00000001&((data)<<0))
#define PLL_DISP_SD3_PSAUD2A_RSTB_src(data)                                          ((0x00000001&(data))>>0)
#define PLL_DISP_SD3_get_PSAUD2A_RSTB(data)                                          ((0x00000001&(data))>>0)


#define PLL_DISP_SD4                                                                 0x98000128
#define PLL_DISP_SD4_reg_addr                                                        "0x98000128"
#define PLL_DISP_SD4_reg                                                             0x98000128
#define set_PLL_DISP_SD4_reg(data)   (*((volatile unsigned int*) PLL_DISP_SD4_reg)=data)
#define get_PLL_DISP_SD4_reg   (*((volatile unsigned int*) PLL_DISP_SD4_reg))
#define PLL_DISP_SD4_inst_adr                                                        "0x004A"
#define PLL_DISP_SD4_inst                                                            0x004A
#define PLL_DISP_SD4_PLLDDSA_K_shift                                                 (4)
#define PLL_DISP_SD4_PLLDDSA_K_mask                                                  (0x00000030)
#define PLL_DISP_SD4_PLLDDSA_K(data)                                                 (0x00000030&((data)<<4))
#define PLL_DISP_SD4_PLLDDSA_K_src(data)                                             ((0x00000030&(data))>>4)
#define PLL_DISP_SD4_get_PLLDDSA_K(data)                                             ((0x00000030&(data))>>4)
#define PLL_DISP_SD4_PLLDDSA_OEB_shift                                               (2)
#define PLL_DISP_SD4_PLLDDSA_OEB_mask                                                (0x00000004)
#define PLL_DISP_SD4_PLLDDSA_OEB(data)                                               (0x00000004&((data)<<2))
#define PLL_DISP_SD4_PLLDDSA_OEB_src(data)                                           ((0x00000004&(data))>>2)
#define PLL_DISP_SD4_get_PLLDDSA_OEB(data)                                           ((0x00000004&(data))>>2)
#define PLL_DISP_SD4_PLLDDSA_RSTB_shift                                              (1)
#define PLL_DISP_SD4_PLLDDSA_RSTB_mask                                               (0x00000002)
#define PLL_DISP_SD4_PLLDDSA_RSTB(data)                                              (0x00000002&((data)<<1))
#define PLL_DISP_SD4_PLLDDSA_RSTB_src(data)                                          ((0x00000002&(data))>>1)
#define PLL_DISP_SD4_get_PLLDDSA_RSTB(data)                                          ((0x00000002&(data))>>1)
#define PLL_DISP_SD4_PLLDDSA_POW_shift                                               (0)
#define PLL_DISP_SD4_PLLDDSA_POW_mask                                                (0x00000001)
#define PLL_DISP_SD4_PLLDDSA_POW(data)                                               (0x00000001&((data)<<0))
#define PLL_DISP_SD4_PLLDDSA_POW_src(data)                                           ((0x00000001&(data))>>0)
#define PLL_DISP_SD4_get_PLLDDSA_POW(data)                                           ((0x00000001&(data))>>0)


#define PLL_DISP_SD5                                                                 0x9800012c
#define PLL_DISP_SD5_reg_addr                                                        "0x9800012C"
#define PLL_DISP_SD5_reg                                                             0x9800012C
#define set_PLL_DISP_SD5_reg(data)   (*((volatile unsigned int*) PLL_DISP_SD5_reg)=data)
#define get_PLL_DISP_SD5_reg   (*((volatile unsigned int*) PLL_DISP_SD5_reg))
#define PLL_DISP_SD5_inst_adr                                                        "0x004B"
#define PLL_DISP_SD5_inst                                                            0x004B
#define PLL_DISP_SD5_N_shift                                                         (16)
#define PLL_DISP_SD5_N_mask                                                          (0xFFFF0000)
#define PLL_DISP_SD5_N(data)                                                         (0xFFFF0000&((data)<<16))
#define PLL_DISP_SD5_N_src(data)                                                     ((0xFFFF0000&(data))>>16)
#define PLL_DISP_SD5_get_N(data)                                                     ((0xFFFF0000&(data))>>16)
#define PLL_DISP_SD5_M_shift                                                         (0)
#define PLL_DISP_SD5_M_mask                                                          (0x0000FFFF)
#define PLL_DISP_SD5_M(data)                                                         (0x0000FFFF&((data)<<0))
#define PLL_DISP_SD5_M_src(data)                                                     ((0x0000FFFF&(data))>>0)
#define PLL_DISP_SD5_get_M(data)                                                     ((0x0000FFFF&(data))>>0)


#define PLL_DISP_SD6                                                                 0x98000130
#define PLL_DISP_SD6_reg_addr                                                        "0x98000130"
#define PLL_DISP_SD6_reg                                                             0x98000130
#define set_PLL_DISP_SD6_reg(data)   (*((volatile unsigned int*) PLL_DISP_SD6_reg)=data)
#define get_PLL_DISP_SD6_reg   (*((volatile unsigned int*) PLL_DISP_SD6_reg))
#define PLL_DISP_SD6_inst_adr                                                        "0x004C"
#define PLL_DISP_SD6_inst                                                            0x004C
#define PLL_DISP_SD6_N_nxt_shift                                                     (0)
#define PLL_DISP_SD6_N_nxt_mask                                                      (0x0000FFFF)
#define PLL_DISP_SD6_N_nxt(data)                                                     (0x0000FFFF&((data)<<0))
#define PLL_DISP_SD6_N_nxt_src(data)                                                 ((0x0000FFFF&(data))>>0)
#define PLL_DISP_SD6_get_N_nxt(data)                                                 ((0x0000FFFF&(data))>>0)


#define PLL_DISP_SD7                                                                 0x98000134
#define PLL_DISP_SD7_reg_addr                                                        "0x98000134"
#define PLL_DISP_SD7_reg                                                             0x98000134
#define set_PLL_DISP_SD7_reg(data)   (*((volatile unsigned int*) PLL_DISP_SD7_reg)=data)
#define get_PLL_DISP_SD7_reg   (*((volatile unsigned int*) PLL_DISP_SD7_reg))
#define PLL_DISP_SD7_inst_adr                                                        "0x004D"
#define PLL_DISP_SD7_inst                                                            0x004D
#define PLL_DISP_SD7_N_nxt_add_shift                                                 (16)
#define PLL_DISP_SD7_N_nxt_add_mask                                                  (0x00FF0000)
#define PLL_DISP_SD7_N_nxt_add(data)                                                 (0x00FF0000&((data)<<16))
#define PLL_DISP_SD7_N_nxt_add_src(data)                                             ((0x00FF0000&(data))>>16)
#define PLL_DISP_SD7_get_N_nxt_add(data)                                             ((0x00FF0000&(data))>>16)
#define PLL_DISP_SD7_N_nxt_add_period_shift                                          (0)
#define PLL_DISP_SD7_N_nxt_add_period_mask                                           (0x0000FFFF)
#define PLL_DISP_SD7_N_nxt_add_period(data)                                          (0x0000FFFF&((data)<<0))
#define PLL_DISP_SD7_N_nxt_add_period_src(data)                                      ((0x0000FFFF&(data))>>0)
#define PLL_DISP_SD7_get_N_nxt_add_period(data)                                      ((0x0000FFFF&(data))>>0)


#define PLL_DISP_HD1                                                                 0x98000138
#define PLL_DISP_HD1_reg_addr                                                        "0x98000138"
#define PLL_DISP_HD1_reg                                                             0x98000138
#define set_PLL_DISP_HD1_reg(data)   (*((volatile unsigned int*) PLL_DISP_HD1_reg)=data)
#define get_PLL_DISP_HD1_reg   (*((volatile unsigned int*) PLL_DISP_HD1_reg))
#define PLL_DISP_HD1_inst_adr                                                        "0x004E"
#define PLL_DISP_HD1_inst                                                            0x004E
#define PLL_DISP_HD1_PLLDISP_Q2_shift                                                (24)
#define PLL_DISP_HD1_PLLDISP_Q2_mask                                                 (0x03000000)
#define PLL_DISP_HD1_PLLDISP_Q2(data)                                                (0x03000000&((data)<<24))
#define PLL_DISP_HD1_PLLDISP_Q2_src(data)                                            ((0x03000000&(data))>>24)
#define PLL_DISP_HD1_get_PLLDISP_Q2(data)                                            ((0x03000000&(data))>>24)
#define PLL_DISP_HD1_PLLDISP_BP_shift                                                (23)
#define PLL_DISP_HD1_PLLDISP_BP_mask                                                 (0x00800000)
#define PLL_DISP_HD1_PLLDISP_BP(data)                                                (0x00800000&((data)<<23))
#define PLL_DISP_HD1_PLLDISP_BP_src(data)                                            ((0x00800000&(data))>>23)
#define PLL_DISP_HD1_get_PLLDISP_BP(data)                                            ((0x00800000&(data))>>23)
#define PLL_DISP_HD1_PLLDISP_N_shift                                                 (20)
#define PLL_DISP_HD1_PLLDISP_N_mask                                                  (0x00700000)
#define PLL_DISP_HD1_PLLDISP_N(data)                                                 (0x00700000&((data)<<20))
#define PLL_DISP_HD1_PLLDISP_N_src(data)                                             ((0x00700000&(data))>>20)
#define PLL_DISP_HD1_get_PLLDISP_N(data)                                             ((0x00700000&(data))>>20)
#define PLL_DISP_HD1_PLLDISP_Q1_shift                                                (18)
#define PLL_DISP_HD1_PLLDISP_Q1_mask                                                 (0x000C0000)
#define PLL_DISP_HD1_PLLDISP_Q1(data)                                                (0x000C0000&((data)<<18))
#define PLL_DISP_HD1_PLLDISP_Q1_src(data)                                            ((0x000C0000&(data))>>18)
#define PLL_DISP_HD1_get_PLLDISP_Q1(data)                                            ((0x000C0000&(data))>>18)
#define PLL_DISP_HD1_PLLDISP_M_shift                                                 (11)
#define PLL_DISP_HD1_PLLDISP_M_mask                                                  (0x0003F800)
#define PLL_DISP_HD1_PLLDISP_M(data)                                                 (0x0003F800&((data)<<11))
#define PLL_DISP_HD1_PLLDISP_M_src(data)                                             ((0x0003F800&(data))>>11)
#define PLL_DISP_HD1_get_PLLDISP_M(data)                                             ((0x0003F800&(data))>>11)
#define PLL_DISP_HD1_PLLDISP_IP_shift                                                (9)
#define PLL_DISP_HD1_PLLDISP_IP_mask                                                 (0x00000600)
#define PLL_DISP_HD1_PLLDISP_IP(data)                                                (0x00000600&((data)<<9))
#define PLL_DISP_HD1_PLLDISP_IP_src(data)                                            ((0x00000600&(data))>>9)
#define PLL_DISP_HD1_get_PLLDISP_IP(data)                                            ((0x00000600&(data))>>9)
#define PLL_DISP_HD1_PLLDISP_RS_shift                                                (6)
#define PLL_DISP_HD1_PLLDISP_RS_mask                                                 (0x000001C0)
#define PLL_DISP_HD1_PLLDISP_RS(data)                                                (0x000001C0&((data)<<6))
#define PLL_DISP_HD1_PLLDISP_RS_src(data)                                            ((0x000001C0&(data))>>6)
#define PLL_DISP_HD1_get_PLLDISP_RS(data)                                            ((0x000001C0&(data))>>6)
#define PLL_DISP_HD1_PLLDISP_CS_shift                                                (4)
#define PLL_DISP_HD1_PLLDISP_CS_mask                                                 (0x00000030)
#define PLL_DISP_HD1_PLLDISP_CS(data)                                                (0x00000030&((data)<<4))
#define PLL_DISP_HD1_PLLDISP_CS_src(data)                                            ((0x00000030&(data))>>4)
#define PLL_DISP_HD1_get_PLLDISP_CS(data)                                            ((0x00000030&(data))>>4)
#define PLL_DISP_HD1_PLLDISP_WDRST_shift                                             (2)
#define PLL_DISP_HD1_PLLDISP_WDRST_mask                                              (0x00000004)
#define PLL_DISP_HD1_PLLDISP_WDRST(data)                                             (0x00000004&((data)<<2))
#define PLL_DISP_HD1_PLLDISP_WDRST_src(data)                                         ((0x00000004&(data))>>2)
#define PLL_DISP_HD1_get_PLLDISP_WDRST(data)                                         ((0x00000004&(data))>>2)
#define PLL_DISP_HD1_PLLDISP_WDSET_shift                                             (1)
#define PLL_DISP_HD1_PLLDISP_WDSET_mask                                              (0x00000002)
#define PLL_DISP_HD1_PLLDISP_WDSET(data)                                             (0x00000002&((data)<<1))
#define PLL_DISP_HD1_PLLDISP_WDSET_src(data)                                         ((0x00000002&(data))>>1)
#define PLL_DISP_HD1_get_PLLDISP_WDSET(data)                                         ((0x00000002&(data))>>1)
#define PLL_DISP_HD1_PLLDISP_TST_shift                                               (0)
#define PLL_DISP_HD1_PLLDISP_TST_mask                                                (0x00000001)
#define PLL_DISP_HD1_PLLDISP_TST(data)                                               (0x00000001&((data)<<0))
#define PLL_DISP_HD1_PLLDISP_TST_src(data)                                           ((0x00000001&(data))>>0)
#define PLL_DISP_HD1_get_PLLDISP_TST(data)                                           ((0x00000001&(data))>>0)


#define PLL_DISP_HD2                                                                 0x9800013c
#define PLL_DISP_HD2_reg_addr                                                        "0x9800013C"
#define PLL_DISP_HD2_reg                                                             0x9800013C
#define set_PLL_DISP_HD2_reg(data)   (*((volatile unsigned int*) PLL_DISP_HD2_reg)=data)
#define get_PLL_DISP_HD2_reg   (*((volatile unsigned int*) PLL_DISP_HD2_reg))
#define PLL_DISP_HD2_inst_adr                                                        "0x004F"
#define PLL_DISP_HD2_inst                                                            0x004F
#define PLL_DISP_HD2_PLLDISP_OEB2_shift                                              (3)
#define PLL_DISP_HD2_PLLDISP_OEB2_mask                                               (0x00000008)
#define PLL_DISP_HD2_PLLDISP_OEB2(data)                                              (0x00000008&((data)<<3))
#define PLL_DISP_HD2_PLLDISP_OEB2_src(data)                                          ((0x00000008&(data))>>3)
#define PLL_DISP_HD2_get_PLLDISP_OEB2(data)                                          ((0x00000008&(data))>>3)
#define PLL_DISP_HD2_PLLDISP_OEB1_shift                                              (2)
#define PLL_DISP_HD2_PLLDISP_OEB1_mask                                               (0x00000004)
#define PLL_DISP_HD2_PLLDISP_OEB1(data)                                              (0x00000004&((data)<<2))
#define PLL_DISP_HD2_PLLDISP_OEB1_src(data)                                          ((0x00000004&(data))>>2)
#define PLL_DISP_HD2_get_PLLDISP_OEB1(data)                                          ((0x00000004&(data))>>2)
#define PLL_DISP_HD2_PLLDISP_RSTB_shift                                              (1)
#define PLL_DISP_HD2_PLLDISP_RSTB_mask                                               (0x00000002)
#define PLL_DISP_HD2_PLLDISP_RSTB(data)                                              (0x00000002&((data)<<1))
#define PLL_DISP_HD2_PLLDISP_RSTB_src(data)                                          ((0x00000002&(data))>>1)
#define PLL_DISP_HD2_get_PLLDISP_RSTB(data)                                          ((0x00000002&(data))>>1)
#define PLL_DISP_HD2_PLLDISP_POW_shift                                               (0)
#define PLL_DISP_HD2_PLLDISP_POW_mask                                                (0x00000001)
#define PLL_DISP_HD2_PLLDISP_POW(data)                                               (0x00000001&((data)<<0))
#define PLL_DISP_HD2_PLLDISP_POW_src(data)                                           ((0x00000001&(data))>>0)
#define PLL_DISP_HD2_get_PLLDISP_POW(data)                                           ((0x00000001&(data))>>0)


#define PLL1_TEST                                                                    0x98000140
#define PLL1_TEST_reg_addr                                                           "0x98000140"
#define PLL1_TEST_reg                                                                0x98000140
#define set_PLL1_TEST_reg(data)   (*((volatile unsigned int*) PLL1_TEST_reg)=data)
#define get_PLL1_TEST_reg   (*((volatile unsigned int*) PLL1_TEST_reg))
#define PLL1_TEST_inst_adr                                                           "0x0050"
#define PLL1_TEST_inst                                                               0x0050
#define PLL1_TEST_REG_PLLTST_POW_shift                                               (4)
#define PLL1_TEST_REG_PLLTST_POW_mask                                                (0x00000010)
#define PLL1_TEST_REG_PLLTST_POW(data)                                               (0x00000010&((data)<<4))
#define PLL1_TEST_REG_PLLTST_POW_src(data)                                           ((0x00000010&(data))>>4)
#define PLL1_TEST_get_REG_PLLTST_POW(data)                                           ((0x00000010&(data))>>4)


#define PLL_REG_CTRL                                                                 0x98000144
#define PLL_REG_CTRL_reg_addr                                                        "0x98000144"
#define PLL_REG_CTRL_reg                                                             0x98000144
#define set_PLL_REG_CTRL_reg(data)   (*((volatile unsigned int*) PLL_REG_CTRL_reg)=data)
#define get_PLL_REG_CTRL_reg   (*((volatile unsigned int*) PLL_REG_CTRL_reg))
#define PLL_REG_CTRL_inst_adr                                                        "0x0051"
#define PLL_REG_CTRL_inst                                                            0x0051
#define PLL_REG_CTRL_write_en4_shift                                                 (15)
#define PLL_REG_CTRL_write_en4_mask                                                  (0x00008000)
#define PLL_REG_CTRL_write_en4(data)                                                 (0x00008000&((data)<<15))
#define PLL_REG_CTRL_write_en4_src(data)                                             ((0x00008000&(data))>>15)
#define PLL_REG_CTRL_get_write_en4(data)                                             ((0x00008000&(data))>>15)
#define PLL_REG_CTRL_PLLDDR_CCO_BAND_shift                                           (13)
#define PLL_REG_CTRL_PLLDDR_CCO_BAND_mask                                            (0x00006000)
#define PLL_REG_CTRL_PLLDDR_CCO_BAND(data)                                           (0x00006000&((data)<<13))
#define PLL_REG_CTRL_PLLDDR_CCO_BAND_src(data)                                       ((0x00006000&(data))>>13)
#define PLL_REG_CTRL_get_PLLDDR_CCO_BAND(data)                                       ((0x00006000&(data))>>13)
#define PLL_REG_CTRL_PLLDDR_CCO_KVCO_shift                                           (12)
#define PLL_REG_CTRL_PLLDDR_CCO_KVCO_mask                                            (0x00001000)
#define PLL_REG_CTRL_PLLDDR_CCO_KVCO(data)                                           (0x00001000&((data)<<12))
#define PLL_REG_CTRL_PLLDDR_CCO_KVCO_src(data)                                       ((0x00001000&(data))>>12)
#define PLL_REG_CTRL_get_PLLDDR_CCO_KVCO(data)                                       ((0x00001000&(data))>>12)
#define PLL_REG_CTRL_write_en3_shift                                                 (11)
#define PLL_REG_CTRL_write_en3_mask                                                  (0x00000800)
#define PLL_REG_CTRL_write_en3(data)                                                 (0x00000800&((data)<<11))
#define PLL_REG_CTRL_write_en3_src(data)                                             ((0x00000800&(data))>>11)
#define PLL_REG_CTRL_get_write_en3(data)                                             ((0x00000800&(data))>>11)
#define PLL_REG_CTRL_PLLDISP_REG_shift                                               (9)
#define PLL_REG_CTRL_PLLDISP_REG_mask                                                (0x00000600)
#define PLL_REG_CTRL_PLLDISP_REG(data)                                               (0x00000600&((data)<<9))
#define PLL_REG_CTRL_PLLDISP_REG_src(data)                                           ((0x00000600&(data))>>9)
#define PLL_REG_CTRL_get_PLLDISP_REG(data)                                           ((0x00000600&(data))>>9)
#define PLL_REG_CTRL_PLLDISP_POWREG_shift                                            (8)
#define PLL_REG_CTRL_PLLDISP_POWREG_mask                                             (0x00000100)
#define PLL_REG_CTRL_PLLDISP_POWREG(data)                                            (0x00000100&((data)<<8))
#define PLL_REG_CTRL_PLLDISP_POWREG_src(data)                                        ((0x00000100&(data))>>8)
#define PLL_REG_CTRL_get_PLLDISP_POWREG(data)                                        ((0x00000100&(data))>>8)
#define PLL_REG_CTRL_write_en2_shift                                                 (7)
#define PLL_REG_CTRL_write_en2_mask                                                  (0x00000080)
#define PLL_REG_CTRL_write_en2(data)                                                 (0x00000080&((data)<<7))
#define PLL_REG_CTRL_write_en2_src(data)                                             ((0x00000080&(data))>>7)
#define PLL_REG_CTRL_get_write_en2(data)                                             ((0x00000080&(data))>>7)
#define PLL_REG_CTRL_PLLDDS_REG_shift                                                (5)
#define PLL_REG_CTRL_PLLDDS_REG_mask                                                 (0x00000060)
#define PLL_REG_CTRL_PLLDDS_REG(data)                                                (0x00000060&((data)<<5))
#define PLL_REG_CTRL_PLLDDS_REG_src(data)                                            ((0x00000060&(data))>>5)
#define PLL_REG_CTRL_get_PLLDDS_REG(data)                                            ((0x00000060&(data))>>5)
#define PLL_REG_CTRL_PLLDDS_POWREG_shift                                             (4)
#define PLL_REG_CTRL_PLLDDS_POWREG_mask                                              (0x00000010)
#define PLL_REG_CTRL_PLLDDS_POWREG(data)                                             (0x00000010&((data)<<4))
#define PLL_REG_CTRL_PLLDDS_POWREG_src(data)                                         ((0x00000010&(data))>>4)
#define PLL_REG_CTRL_get_PLLDDS_POWREG(data)                                         ((0x00000010&(data))>>4)
#define PLL_REG_CTRL_write_en1_shift                                                 (3)
#define PLL_REG_CTRL_write_en1_mask                                                  (0x00000008)
#define PLL_REG_CTRL_write_en1(data)                                                 (0x00000008&((data)<<3))
#define PLL_REG_CTRL_write_en1_src(data)                                             ((0x00000008&(data))>>3)
#define PLL_REG_CTRL_get_write_en1(data)                                             ((0x00000008&(data))>>3)
#define PLL_REG_CTRL_PLLCPU_REG_shift                                                (1)
#define PLL_REG_CTRL_PLLCPU_REG_mask                                                 (0x00000006)
#define PLL_REG_CTRL_PLLCPU_REG(data)                                                (0x00000006&((data)<<1))
#define PLL_REG_CTRL_PLLCPU_REG_src(data)                                            ((0x00000006&(data))>>1)
#define PLL_REG_CTRL_get_PLLCPU_REG(data)                                            ((0x00000006&(data))>>1)
#define PLL_REG_CTRL_PLLCPU_POWREG_shift                                             (0)
#define PLL_REG_CTRL_PLLCPU_POWREG_mask                                              (0x00000001)
#define PLL_REG_CTRL_PLLCPU_POWREG(data)                                             (0x00000001&((data)<<0))
#define PLL_REG_CTRL_PLLCPU_POWREG_src(data)                                         ((0x00000001&(data))>>0)
#define PLL_REG_CTRL_get_PLLCPU_POWREG(data)                                         ((0x00000001&(data))>>0)


#define PLL_DDR1                                                                     0x98000150
#define PLL_DDR1_reg_addr                                                            "0x98000150"
#define PLL_DDR1_reg                                                                 0x98000150
#define set_PLL_DDR1_reg(data)   (*((volatile unsigned int*) PLL_DDR1_reg)=data)
#define get_PLL_DDR1_reg   (*((volatile unsigned int*) PLL_DDR1_reg))
#define PLL_DDR1_inst_adr                                                            "0x0054"
#define PLL_DDR1_inst                                                                0x0054
#define PLL_DDR1_write_en4_shift                                                     (30)
#define PLL_DDR1_write_en4_mask                                                      (0x40000000)
#define PLL_DDR1_write_en4(data)                                                     (0x40000000&((data)<<30))
#define PLL_DDR1_write_en4_src(data)                                                 ((0x40000000&(data))>>30)
#define PLL_DDR1_get_write_en4(data)                                                 ((0x40000000&(data))>>30)
#define PLL_DDR1_PLLDDR_PDIV_shift                                                   (28)
#define PLL_DDR1_PLLDDR_PDIV_mask                                                    (0x30000000)
#define PLL_DDR1_PLLDDR_PDIV(data)                                                   (0x30000000&((data)<<28))
#define PLL_DDR1_PLLDDR_PDIV_src(data)                                               ((0x30000000&(data))>>28)
#define PLL_DDR1_get_PLLDDR_PDIV(data)                                               ((0x30000000&(data))>>28)
#define PLL_DDR1_write_en3_shift                                                     (27)
#define PLL_DDR1_write_en3_mask                                                      (0x08000000)
#define PLL_DDR1_write_en3(data)                                                     (0x08000000&((data)<<27))
#define PLL_DDR1_write_en3_src(data)                                                 ((0x08000000&(data))>>27)
#define PLL_DDR1_get_write_en3(data)                                                 ((0x08000000&(data))>>27)
#define PLL_DDR1_PLLDDR_ICP_shift                                                    (23)
#define PLL_DDR1_PLLDDR_ICP_mask                                                     (0x07800000)
#define PLL_DDR1_PLLDDR_ICP(data)                                                    (0x07800000&((data)<<23))
#define PLL_DDR1_PLLDDR_ICP_src(data)                                                ((0x07800000&(data))>>23)
#define PLL_DDR1_get_PLLDDR_ICP(data)                                                ((0x07800000&(data))>>23)
#define PLL_DDR1_PLLDDR_PLL_SEL_CPMODE_shift                                         (22)
#define PLL_DDR1_PLLDDR_PLL_SEL_CPMODE_mask                                          (0x00400000)
#define PLL_DDR1_PLLDDR_PLL_SEL_CPMODE(data)                                         (0x00400000&((data)<<22))
#define PLL_DDR1_PLLDDR_PLL_SEL_CPMODE_src(data)                                     ((0x00400000&(data))>>22)
#define PLL_DDR1_get_PLLDDR_PLL_SEL_CPMODE(data)                                     ((0x00400000&(data))>>22)
#define PLL_DDR1_PLLDDR_LPF_SR_shift                                                 (19)
#define PLL_DDR1_PLLDDR_LPF_SR_mask                                                  (0x00380000)
#define PLL_DDR1_PLLDDR_LPF_SR(data)                                                 (0x00380000&((data)<<19))
#define PLL_DDR1_PLLDDR_LPF_SR_src(data)                                             ((0x00380000&(data))>>19)
#define PLL_DDR1_get_PLLDDR_LPF_SR(data)                                             ((0x00380000&(data))>>19)
#define PLL_DDR1_PLLDDR_LPF_CP_shift                                                 (18)
#define PLL_DDR1_PLLDDR_LPF_CP_mask                                                  (0x00040000)
#define PLL_DDR1_PLLDDR_LPF_CP(data)                                                 (0x00040000&((data)<<18))
#define PLL_DDR1_PLLDDR_LPF_CP_src(data)                                             ((0x00040000&(data))>>18)
#define PLL_DDR1_get_PLLDDR_LPF_CP(data)                                             ((0x00040000&(data))>>18)
#define PLL_DDR1_PLLDDR_LOOP_PI_ISEL_shift                                           (15)
#define PLL_DDR1_PLLDDR_LOOP_PI_ISEL_mask                                            (0x00038000)
#define PLL_DDR1_PLLDDR_LOOP_PI_ISEL(data)                                           (0x00038000&((data)<<15))
#define PLL_DDR1_PLLDDR_LOOP_PI_ISEL_src(data)                                       ((0x00038000&(data))>>15)
#define PLL_DDR1_get_PLLDDR_LOOP_PI_ISEL(data)                                       ((0x00038000&(data))>>15)
#define PLL_DDR1_write_en2_shift                                                     (14)
#define PLL_DDR1_write_en2_mask                                                      (0x00004000)
#define PLL_DDR1_write_en2(data)                                                     (0x00004000&((data)<<14))
#define PLL_DDR1_write_en2_src(data)                                                 ((0x00004000&(data))>>14)
#define PLL_DDR1_get_write_en2(data)                                                 ((0x00004000&(data))>>14)
#define PLL_DDR1_PLLDDR_POST_PI_SEL6_shift                                           (9)
#define PLL_DDR1_PLLDDR_POST_PI_SEL6_mask                                            (0x00003E00)
#define PLL_DDR1_PLLDDR_POST_PI_SEL6(data)                                           (0x00003E00&((data)<<9))
#define PLL_DDR1_PLLDDR_POST_PI_SEL6_src(data)                                       ((0x00003E00&(data))>>9)
#define PLL_DDR1_get_PLLDDR_POST_PI_SEL6(data)                                       ((0x00003E00&(data))>>9)
#define PLL_DDR1_PLLDDR_POST_PI_RL_shift                                             (7)
#define PLL_DDR1_PLLDDR_POST_PI_RL_mask                                              (0x00000180)
#define PLL_DDR1_PLLDDR_POST_PI_RL(data)                                             (0x00000180&((data)<<7))
#define PLL_DDR1_PLLDDR_POST_PI_RL_src(data)                                         ((0x00000180&(data))>>7)
#define PLL_DDR1_get_PLLDDR_POST_PI_RL(data)                                         ((0x00000180&(data))>>7)
#define PLL_DDR1_PLLDDR_POST_PI_BIAS_shift                                           (5)
#define PLL_DDR1_PLLDDR_POST_PI_BIAS_mask                                            (0x00000060)
#define PLL_DDR1_PLLDDR_POST_PI_BIAS(data)                                           (0x00000060&((data)<<5))
#define PLL_DDR1_PLLDDR_POST_PI_BIAS_src(data)                                       ((0x00000060&(data))>>5)
#define PLL_DDR1_get_PLLDDR_POST_PI_BIAS(data)                                       ((0x00000060&(data))>>5)
#define PLL_DDR1_PLLDDR_POST_PI_RS_shift                                             (4)
#define PLL_DDR1_PLLDDR_POST_PI_RS_mask                                              (0x00000010)
#define PLL_DDR1_PLLDDR_POST_PI_RS(data)                                             (0x00000010&((data)<<4))
#define PLL_DDR1_PLLDDR_POST_PI_RS_src(data)                                         ((0x00000010&(data))>>4)
#define PLL_DDR1_get_PLLDDR_POST_PI_RS(data)                                         ((0x00000010&(data))>>4)
#define PLL_DDR1_write_en1_shift                                                     (3)
#define PLL_DDR1_write_en1_mask                                                      (0x00000008)
#define PLL_DDR1_write_en1(data)                                                     (0x00000008&((data)<<3))
#define PLL_DDR1_write_en1_src(data)                                                 ((0x00000008&(data))>>3)
#define PLL_DDR1_get_write_en1(data)                                                 ((0x00000008&(data))>>3)
#define PLL_DDR1_PLLDDR_CKREF_SEL_shift                                              (2)
#define PLL_DDR1_PLLDDR_CKREF_SEL_mask                                               (0x00000004)
#define PLL_DDR1_PLLDDR_CKREF_SEL(data)                                              (0x00000004&((data)<<2))
#define PLL_DDR1_PLLDDR_CKREF_SEL_src(data)                                          ((0x00000004&(data))>>2)
#define PLL_DDR1_get_PLLDDR_CKREF_SEL(data)                                          ((0x00000004&(data))>>2)
#define PLL_DDR1_PLLDDR_PLL_LDO_VSEL_shift                                           (0)
#define PLL_DDR1_PLLDDR_PLL_LDO_VSEL_mask                                            (0x00000003)
#define PLL_DDR1_PLLDDR_PLL_LDO_VSEL(data)                                           (0x00000003&((data)<<0))
#define PLL_DDR1_PLLDDR_PLL_LDO_VSEL_src(data)                                       ((0x00000003&(data))>>0)
#define PLL_DDR1_get_PLLDDR_PLL_LDO_VSEL(data)                                       ((0x00000003&(data))>>0)


#define PLL_DDR2                                                                     0x98000154
#define PLL_DDR2_reg_addr                                                            "0x98000154"
#define PLL_DDR2_reg                                                                 0x98000154
#define set_PLL_DDR2_reg(data)   (*((volatile unsigned int*) PLL_DDR2_reg)=data)
#define get_PLL_DDR2_reg   (*((volatile unsigned int*) PLL_DDR2_reg))
#define PLL_DDR2_inst_adr                                                            "0x0055"
#define PLL_DDR2_inst                                                                0x0055
#define PLL_DDR2_PLLDDR_POST_PI_SEL5_shift                                           (25)
#define PLL_DDR2_PLLDDR_POST_PI_SEL5_mask                                            (0x3E000000)
#define PLL_DDR2_PLLDDR_POST_PI_SEL5(data)                                           (0x3E000000&((data)<<25))
#define PLL_DDR2_PLLDDR_POST_PI_SEL5_src(data)                                       ((0x3E000000&(data))>>25)
#define PLL_DDR2_get_PLLDDR_POST_PI_SEL5(data)                                       ((0x3E000000&(data))>>25)
#define PLL_DDR2_PLLDDR_POST_PI_SEL4_shift                                           (20)
#define PLL_DDR2_PLLDDR_POST_PI_SEL4_mask                                            (0x01F00000)
#define PLL_DDR2_PLLDDR_POST_PI_SEL4(data)                                           (0x01F00000&((data)<<20))
#define PLL_DDR2_PLLDDR_POST_PI_SEL4_src(data)                                       ((0x01F00000&(data))>>20)
#define PLL_DDR2_get_PLLDDR_POST_PI_SEL4(data)                                       ((0x01F00000&(data))>>20)
#define PLL_DDR2_PLLDDR_POST_PI_SEL3_shift                                           (15)
#define PLL_DDR2_PLLDDR_POST_PI_SEL3_mask                                            (0x000F8000)
#define PLL_DDR2_PLLDDR_POST_PI_SEL3(data)                                           (0x000F8000&((data)<<15))
#define PLL_DDR2_PLLDDR_POST_PI_SEL3_src(data)                                       ((0x000F8000&(data))>>15)
#define PLL_DDR2_get_PLLDDR_POST_PI_SEL3(data)                                       ((0x000F8000&(data))>>15)
#define PLL_DDR2_PLLDDR_POST_PI_SEL2_shift                                           (10)
#define PLL_DDR2_PLLDDR_POST_PI_SEL2_mask                                            (0x00007C00)
#define PLL_DDR2_PLLDDR_POST_PI_SEL2(data)                                           (0x00007C00&((data)<<10))
#define PLL_DDR2_PLLDDR_POST_PI_SEL2_src(data)                                       ((0x00007C00&(data))>>10)
#define PLL_DDR2_get_PLLDDR_POST_PI_SEL2(data)                                       ((0x00007C00&(data))>>10)
#define PLL_DDR2_PLLDDR_POST_PI_SEL1_shift                                           (5)
#define PLL_DDR2_PLLDDR_POST_PI_SEL1_mask                                            (0x000003E0)
#define PLL_DDR2_PLLDDR_POST_PI_SEL1(data)                                           (0x000003E0&((data)<<5))
#define PLL_DDR2_PLLDDR_POST_PI_SEL1_src(data)                                       ((0x000003E0&(data))>>5)
#define PLL_DDR2_get_PLLDDR_POST_PI_SEL1(data)                                       ((0x000003E0&(data))>>5)
#define PLL_DDR2_PLLDDR_POST_PI_SEL0_shift                                           (0)
#define PLL_DDR2_PLLDDR_POST_PI_SEL0_mask                                            (0x0000001F)
#define PLL_DDR2_PLLDDR_POST_PI_SEL0(data)                                           (0x0000001F&((data)<<0))
#define PLL_DDR2_PLLDDR_POST_PI_SEL0_src(data)                                       ((0x0000001F&(data))>>0)
#define PLL_DDR2_get_PLLDDR_POST_PI_SEL0(data)                                       ((0x0000001F&(data))>>0)


#define PLL_DDR3                                                                     0x98000158
#define PLL_DDR3_reg_addr                                                            "0x98000158"
#define PLL_DDR3_reg                                                                 0x98000158
#define set_PLL_DDR3_reg(data)   (*((volatile unsigned int*) PLL_DDR3_reg)=data)
#define get_PLL_DDR3_reg   (*((volatile unsigned int*) PLL_DDR3_reg))
#define PLL_DDR3_inst_adr                                                            "0x0056"
#define PLL_DDR3_inst                                                                0x0056
#define PLL_DDR3_write_en2_shift                                                     (31)
#define PLL_DDR3_write_en2_mask                                                      (0x80000000)
#define PLL_DDR3_write_en2(data)                                                     (0x80000000&((data)<<31))
#define PLL_DDR3_write_en2_src(data)                                                 ((0x80000000&(data))>>31)
#define PLL_DDR3_get_write_en2(data)                                                 ((0x80000000&(data))>>31)
#define PLL_DDR3_PLLDDR_DUM_shift                                                    (23)
#define PLL_DDR3_PLLDDR_DUM_mask                                                     (0x7F800000)
#define PLL_DDR3_PLLDDR_DUM(data)                                                    (0x7F800000&((data)<<23))
#define PLL_DDR3_PLLDDR_DUM_src(data)                                                ((0x7F800000&(data))>>23)
#define PLL_DDR3_get_PLLDDR_DUM(data)                                                ((0x7F800000&(data))>>23)
#define PLL_DDR3_PLLDDR_PLL_DBUG_EN_shift                                            (22)
#define PLL_DDR3_PLLDDR_PLL_DBUG_EN_mask                                             (0x00400000)
#define PLL_DDR3_PLLDDR_PLL_DBUG_EN(data)                                            (0x00400000&((data)<<22))
#define PLL_DDR3_PLLDDR_PLL_DBUG_EN_src(data)                                        ((0x00400000&(data))>>22)
#define PLL_DDR3_get_PLLDDR_PLL_DBUG_EN(data)                                        ((0x00400000&(data))>>22)
#define PLL_DDR3_PLLDDR_OESYNC_OP_SEL_shift                                          (16)
#define PLL_DDR3_PLLDDR_OESYNC_OP_SEL_mask                                           (0x003F0000)
#define PLL_DDR3_PLLDDR_OESYNC_OP_SEL(data)                                          (0x003F0000&((data)<<16))
#define PLL_DDR3_PLLDDR_OESYNC_OP_SEL_src(data)                                      ((0x003F0000&(data))>>16)
#define PLL_DDR3_get_PLLDDR_OESYNC_OP_SEL(data)                                      ((0x003F0000&(data))>>16)
#define PLL_DDR3_PLLDDR_EN_POST_PI_shift                                             (9)
#define PLL_DDR3_PLLDDR_EN_POST_PI_mask                                              (0x0000FE00)
#define PLL_DDR3_PLLDDR_EN_POST_PI(data)                                             (0x0000FE00&((data)<<9))
#define PLL_DDR3_PLLDDR_EN_POST_PI_src(data)                                         ((0x0000FE00&(data))>>9)
#define PLL_DDR3_get_PLLDDR_EN_POST_PI(data)                                         ((0x0000FE00&(data))>>9)
#define PLL_DDR3_write_en1_shift                                                     (8)
#define PLL_DDR3_write_en1_mask                                                      (0x00000100)
#define PLL_DDR3_write_en1(data)                                                     (0x00000100&((data)<<8))
#define PLL_DDR3_write_en1_src(data)                                                 ((0x00000100&(data))>>8)
#define PLL_DDR3_get_write_en1(data)                                                 ((0x00000100&(data))>>8)
#define PLL_DDR3_PLLDDR_CLK_OE_shift                                                 (2)
#define PLL_DDR3_PLLDDR_CLK_OE_mask                                                  (0x000000FC)
#define PLL_DDR3_PLLDDR_CLK_OE(data)                                                 (0x000000FC&((data)<<2))
#define PLL_DDR3_PLLDDR_CLK_OE_src(data)                                             ((0x000000FC&(data))>>2)
#define PLL_DDR3_get_PLLDDR_CLK_OE(data)                                             ((0x000000FC&(data))>>2)
#define PLL_DDR3_PLLDDR_RSTB_IN_shift                                                (1)
#define PLL_DDR3_PLLDDR_RSTB_IN_mask                                                 (0x00000002)
#define PLL_DDR3_PLLDDR_RSTB_IN(data)                                                (0x00000002&((data)<<1))
#define PLL_DDR3_PLLDDR_RSTB_IN_src(data)                                            ((0x00000002&(data))>>1)
#define PLL_DDR3_get_PLLDDR_RSTB_IN(data)                                            ((0x00000002&(data))>>1)
#define PLL_DDR3_PLLDDR_PLL_EN_shift                                                 (0)
#define PLL_DDR3_PLLDDR_PLL_EN_mask                                                  (0x00000001)
#define PLL_DDR3_PLLDDR_PLL_EN(data)                                                 (0x00000001&((data)<<0))
#define PLL_DDR3_PLLDDR_PLL_EN_src(data)                                             ((0x00000001&(data))>>0)
#define PLL_DDR3_get_PLLDDR_PLL_EN(data)                                             ((0x00000001&(data))>>0)


#define PLL_DDR4                                                                     0x9800015C
#define PLL_DDR4_reg_addr                                                            "0x9800015C"
#define PLL_DDR4_reg                                                                 0x9800015C
#define set_PLL_DDR4_reg(data)   (*((volatile unsigned int*) PLL_DDR4_reg)=data)
#define get_PLL_DDR4_reg   (*((volatile unsigned int*) PLL_DDR4_reg))
#define PLL_DDR4_inst_adr                                                            "0x0057"
#define PLL_DDR4_inst                                                                0x0057
#define PLL_DDR4_PLLDDR_WDOUT_CLR_shift                                              (10)
#define PLL_DDR4_PLLDDR_WDOUT_CLR_mask                                               (0x00000400)
#define PLL_DDR4_PLLDDR_WDOUT_CLR(data)                                              (0x00000400&((data)<<10))
#define PLL_DDR4_PLLDDR_WDOUT_CLR_src(data)                                          ((0x00000400&(data))>>10)
#define PLL_DDR4_get_PLLDDR_WDOUT_CLR(data)                                          ((0x00000400&(data))>>10)
#define PLL_DDR4_PLLDDR_WD_EN_shift                                                  (9)
#define PLL_DDR4_PLLDDR_WD_EN_mask                                                   (0x00000200)
#define PLL_DDR4_PLLDDR_WD_EN(data)                                                  (0x00000200&((data)<<9))
#define PLL_DDR4_PLLDDR_WD_EN_src(data)                                              ((0x00000200&(data))>>9)
#define PLL_DDR4_get_PLLDDR_WD_EN(data)                                              ((0x00000200&(data))>>9)
#define PLL_DDR4_PLLDDR_F390K_shift                                                  (7)
#define PLL_DDR4_PLLDDR_F390K_mask                                                   (0x00000180)
#define PLL_DDR4_PLLDDR_F390K(data)                                                  (0x00000180&((data)<<7))
#define PLL_DDR4_PLLDDR_F390K_src(data)                                              ((0x00000180&(data))>>7)
#define PLL_DDR4_get_PLLDDR_F390K(data)                                              ((0x00000180&(data))>>7)
#define PLL_DDR4_PLLDDR_TIME0_CK_shift                                               (4)
#define PLL_DDR4_PLLDDR_TIME0_CK_mask                                                (0x00000070)
#define PLL_DDR4_PLLDDR_TIME0_CK(data)                                               (0x00000070&((data)<<4))
#define PLL_DDR4_PLLDDR_TIME0_CK_src(data)                                           ((0x00000070&(data))>>4)
#define PLL_DDR4_get_PLLDDR_TIME0_CK(data)                                           ((0x00000070&(data))>>4)
#define PLL_DDR4_PLLDDR_TIME_RDY_CKOUT_shift                                         (2)
#define PLL_DDR4_PLLDDR_TIME_RDY_CKOUT_mask                                          (0x0000000C)
#define PLL_DDR4_PLLDDR_TIME_RDY_CKOUT(data)                                         (0x0000000C&((data)<<2))
#define PLL_DDR4_PLLDDR_TIME_RDY_CKOUT_src(data)                                     ((0x0000000C&(data))>>2)
#define PLL_DDR4_get_PLLDDR_TIME_RDY_CKOUT(data)                                     ((0x0000000C&(data))>>2)
#define PLL_DDR4_PLLDDR_TIME2_RST_WIDTH_shift                                        (0)
#define PLL_DDR4_PLLDDR_TIME2_RST_WIDTH_mask                                         (0x00000003)
#define PLL_DDR4_PLLDDR_TIME2_RST_WIDTH(data)                                        (0x00000003&((data)<<0))
#define PLL_DDR4_PLLDDR_TIME2_RST_WIDTH_src(data)                                    ((0x00000003&(data))>>0)
#define PLL_DDR4_get_PLLDDR_TIME2_RST_WIDTH(data)                                    ((0x00000003&(data))>>0)


#define PLL_DDR_SSC1                                                                 0x98000160
#define PLL_DDR_SSC1_reg_addr                                                        "0x98000160"
#define PLL_DDR_SSC1_reg                                                             0x98000160
#define set_PLL_DDR_SSC1_reg(data)   (*((volatile unsigned int*) PLL_DDR_SSC1_reg)=data)
#define get_PLL_DDR_SSC1_reg   (*((volatile unsigned int*) PLL_DDR_SSC1_reg))
#define PLL_DDR_SSC1_inst_adr                                                        "0x0058"
#define PLL_DDR_SSC1_inst                                                            0x0058
#define PLL_DDR_SSC1_SSCDDR_N_CODE_shift                                             (21)
#define PLL_DDR_SSC1_SSCDDR_N_CODE_mask                                              (0x1FE00000)
#define PLL_DDR_SSC1_SSCDDR_N_CODE(data)                                             (0x1FE00000&((data)<<21))
#define PLL_DDR_SSC1_SSCDDR_N_CODE_src(data)                                         ((0x1FE00000&(data))>>21)
#define PLL_DDR_SSC1_get_SSCDDR_N_CODE(data)                                         ((0x1FE00000&(data))>>21)
#define PLL_DDR_SSC1_SSCDDR_F_CODE_shift                                             (8)
#define PLL_DDR_SSC1_SSCDDR_F_CODE_mask                                              (0x001FFF00)
#define PLL_DDR_SSC1_SSCDDR_F_CODE(data)                                             (0x001FFF00&((data)<<8))
#define PLL_DDR_SSC1_SSCDDR_F_CODE_src(data)                                         ((0x001FFF00&(data))>>8)
#define PLL_DDR_SSC1_get_SSCDDR_F_CODE(data)                                         ((0x001FFF00&(data))>>8)
#define PLL_DDR_SSC1_SSCDDR_BYPASS_PI_shift                                          (3)
#define PLL_DDR_SSC1_SSCDDR_BYPASS_PI_mask                                           (0x00000008)
#define PLL_DDR_SSC1_SSCDDR_BYPASS_PI(data)                                          (0x00000008&((data)<<3))
#define PLL_DDR_SSC1_SSCDDR_BYPASS_PI_src(data)                                      ((0x00000008&(data))>>3)
#define PLL_DDR_SSC1_get_SSCDDR_BYPASS_PI(data)                                      ((0x00000008&(data))>>3)
#define PLL_DDR_SSC1_SSCDDR_SEL_MODE_shift                                           (2)
#define PLL_DDR_SSC1_SSCDDR_SEL_MODE_mask                                            (0x00000004)
#define PLL_DDR_SSC1_SSCDDR_SEL_MODE(data)                                           (0x00000004&((data)<<2))
#define PLL_DDR_SSC1_SSCDDR_SEL_MODE_src(data)                                       ((0x00000004&(data))>>2)
#define PLL_DDR_SSC1_get_SSCDDR_SEL_MODE(data)                                       ((0x00000004&(data))>>2)
#define PLL_DDR_SSC1_SSCDDR_EN_CENTER_IN_shift                                       (1)
#define PLL_DDR_SSC1_SSCDDR_EN_CENTER_IN_mask                                        (0x00000002)
#define PLL_DDR_SSC1_SSCDDR_EN_CENTER_IN(data)                                       (0x00000002&((data)<<1))
#define PLL_DDR_SSC1_SSCDDR_EN_CENTER_IN_src(data)                                   ((0x00000002&(data))>>1)
#define PLL_DDR_SSC1_get_SSCDDR_EN_CENTER_IN(data)                                   ((0x00000002&(data))>>1)
#define PLL_DDR_SSC1_SSCDDR_EN_SSC_shift                                             (0)
#define PLL_DDR_SSC1_SSCDDR_EN_SSC_mask                                              (0x00000001)
#define PLL_DDR_SSC1_SSCDDR_EN_SSC(data)                                             (0x00000001&((data)<<0))
#define PLL_DDR_SSC1_SSCDDR_EN_SSC_src(data)                                         ((0x00000001&(data))>>0)
#define PLL_DDR_SSC1_get_SSCDDR_EN_SSC(data)                                         ((0x00000001&(data))>>0)


#define PLL_BUS1                                                                     0x98000164
#define PLL_BUS1_reg_addr                                                            "0x98000164"
#define PLL_BUS1_reg                                                                 0x98000164
#define set_PLL_BUS1_reg(data)   (*((volatile unsigned int*) PLL_BUS1_reg)=data)
#define get_PLL_BUS1_reg   (*((volatile unsigned int*) PLL_BUS1_reg))
#define PLL_BUS1_inst_adr                                                            "0x0059"
#define PLL_BUS1_inst                                                                0x0059
#define PLL_BUS1_PLLBUS_N_shift                                                      (25)
#define PLL_BUS1_PLLBUS_N_mask                                                       (0x06000000)
#define PLL_BUS1_PLLBUS_N(data)                                                      (0x06000000&((data)<<25))
#define PLL_BUS1_PLLBUS_N_src(data)                                                  ((0x06000000&(data))>>25)
#define PLL_BUS1_get_PLLBUS_N(data)                                                  ((0x06000000&(data))>>25)
#define PLL_BUS1_PLLBUS_M_shift                                                      (18)
#define PLL_BUS1_PLLBUS_M_mask                                                       (0x01FC0000)
#define PLL_BUS1_PLLBUS_M(data)                                                      (0x01FC0000&((data)<<18))
#define PLL_BUS1_PLLBUS_M_src(data)                                                  ((0x01FC0000&(data))>>18)
#define PLL_BUS1_get_PLLBUS_M(data)                                                  ((0x01FC0000&(data))>>18)
#define PLL_BUS1_PLLBUS_IP_shift                                                     (15)
#define PLL_BUS1_PLLBUS_IP_mask                                                      (0x00038000)
#define PLL_BUS1_PLLBUS_IP(data)                                                     (0x00038000&((data)<<15))
#define PLL_BUS1_PLLBUS_IP_src(data)                                                 ((0x00038000&(data))>>15)
#define PLL_BUS1_get_PLLBUS_IP(data)                                                 ((0x00038000&(data))>>15)
#define PLL_BUS1_PLLBUS_RS_shift                                                     (11)
#define PLL_BUS1_PLLBUS_RS_mask                                                      (0x00003800)
#define PLL_BUS1_PLLBUS_RS(data)                                                     (0x00003800&((data)<<11))
#define PLL_BUS1_PLLBUS_RS_src(data)                                                 ((0x00003800&(data))>>11)
#define PLL_BUS1_get_PLLBUS_RS(data)                                                 ((0x00003800&(data))>>11)
#define PLL_BUS1_PLLBUS_CS_shift                                                     (8)
#define PLL_BUS1_PLLBUS_CS_mask                                                      (0x00000300)
#define PLL_BUS1_PLLBUS_CS(data)                                                     (0x00000300&((data)<<8))
#define PLL_BUS1_PLLBUS_CS_src(data)                                                 ((0x00000300&(data))>>8)
#define PLL_BUS1_get_PLLBUS_CS(data)                                                 ((0x00000300&(data))>>8)
#define PLL_BUS1_PLLBUS_CP_shift                                                     (5)
#define PLL_BUS1_PLLBUS_CP_mask                                                      (0x00000060)
#define PLL_BUS1_PLLBUS_CP(data)                                                     (0x00000060&((data)<<5))
#define PLL_BUS1_PLLBUS_CP_src(data)                                                 ((0x00000060&(data))>>5)
#define PLL_BUS1_get_PLLBUS_CP(data)                                                 ((0x00000060&(data))>>5)
#define PLL_BUS1_PLLBUS_R3_shift                                                     (2)
#define PLL_BUS1_PLLBUS_R3_mask                                                      (0x0000001C)
#define PLL_BUS1_PLLBUS_R3(data)                                                     (0x0000001C&((data)<<2))
#define PLL_BUS1_PLLBUS_R3_src(data)                                                 ((0x0000001C&(data))>>2)
#define PLL_BUS1_get_PLLBUS_R3(data)                                                 ((0x0000001C&(data))>>2)
#define PLL_BUS1_PLLBUS_C3_shift                                                     (0)
#define PLL_BUS1_PLLBUS_C3_mask                                                      (0x00000003)
#define PLL_BUS1_PLLBUS_C3(data)                                                     (0x00000003&((data)<<0))
#define PLL_BUS1_PLLBUS_C3_src(data)                                                 ((0x00000003&(data))>>0)
#define PLL_BUS1_get_PLLBUS_C3(data)                                                 ((0x00000003&(data))>>0)


#define PLL_BUS2                                                                     0x98000168
#define PLL_BUS2_reg_addr                                                            "0x98000168"
#define PLL_BUS2_reg                                                                 0x98000168
#define set_PLL_BUS2_reg(data)   (*((volatile unsigned int*) PLL_BUS2_reg)=data)
#define get_PLL_BUS2_reg   (*((volatile unsigned int*) PLL_BUS2_reg))
#define PLL_BUS2_inst_adr                                                            "0x005A"
#define PLL_BUS2_inst                                                                0x005A
#define PLL_BUS2_write_en5_shift                                                     (18)
#define PLL_BUS2_write_en5_mask                                                      (0x00040000)
#define PLL_BUS2_write_en5(data)                                                     (0x00040000&((data)<<18))
#define PLL_BUS2_write_en5_src(data)                                                 ((0x00040000&(data))>>18)
#define PLL_BUS2_get_write_en5(data)                                                 ((0x00040000&(data))>>18)
#define PLL_BUS2_PLLBUS_PI_RL_shift                                                  (16)
#define PLL_BUS2_PLLBUS_PI_RL_mask                                                   (0x00030000)
#define PLL_BUS2_PLLBUS_PI_RL(data)                                                  (0x00030000&((data)<<16))
#define PLL_BUS2_PLLBUS_PI_RL_src(data)                                              ((0x00030000&(data))>>16)
#define PLL_BUS2_get_PLLBUS_PI_RL(data)                                              ((0x00030000&(data))>>16)
#define PLL_BUS2_PLLBUS_PI_RS_shift                                                  (14)
#define PLL_BUS2_PLLBUS_PI_RS_mask                                                   (0x0000C000)
#define PLL_BUS2_PLLBUS_PI_RS(data)                                                  (0x0000C000&((data)<<14))
#define PLL_BUS2_PLLBUS_PI_RS_src(data)                                              ((0x0000C000&(data))>>14)
#define PLL_BUS2_get_PLLBUS_PI_RS(data)                                              ((0x0000C000&(data))>>14)
#define PLL_BUS2_PLLBUS_PI_BIAS_shift                                                (12)
#define PLL_BUS2_PLLBUS_PI_BIAS_mask                                                 (0x00003000)
#define PLL_BUS2_PLLBUS_PI_BIAS(data)                                                (0x00003000&((data)<<12))
#define PLL_BUS2_PLLBUS_PI_BIAS_src(data)                                            ((0x00003000&(data))>>12)
#define PLL_BUS2_get_PLLBUS_PI_BIAS(data)                                            ((0x00003000&(data))>>12)
#define PLL_BUS2_write_en4_shift                                                     (11)
#define PLL_BUS2_write_en4_mask                                                      (0x00000800)
#define PLL_BUS2_write_en4(data)                                                     (0x00000800&((data)<<11))
#define PLL_BUS2_write_en4_src(data)                                                 ((0x00000800&(data))>>11)
#define PLL_BUS2_get_write_en4(data)                                                 ((0x00000800&(data))>>11)
#define PLL_BUS2_PLLBUS_WDMODE_shift                                                 (9)
#define PLL_BUS2_PLLBUS_WDMODE_mask                                                  (0x00000600)
#define PLL_BUS2_PLLBUS_WDMODE(data)                                                 (0x00000600&((data)<<9))
#define PLL_BUS2_PLLBUS_WDMODE_src(data)                                             ((0x00000600&(data))>>9)
#define PLL_BUS2_get_PLLBUS_WDMODE(data)                                             ((0x00000600&(data))>>9)
#define PLL_BUS2_write_en3_shift                                                     (6)
#define PLL_BUS2_write_en3_mask                                                      (0x00000040)
#define PLL_BUS2_write_en3(data)                                                     (0x00000040&((data)<<6))
#define PLL_BUS2_write_en3_src(data)                                                 ((0x00000040&(data))>>6)
#define PLL_BUS2_get_write_en3(data)                                                 ((0x00000040&(data))>>6)
#define PLL_BUS2_PLLBUS_FUPDN_shift                                                  (5)
#define PLL_BUS2_PLLBUS_FUPDN_mask                                                   (0x00000020)
#define PLL_BUS2_PLLBUS_FUPDN(data)                                                  (0x00000020&((data)<<5))
#define PLL_BUS2_PLLBUS_FUPDN_src(data)                                              ((0x00000020&(data))>>5)
#define PLL_BUS2_get_PLLBUS_FUPDN(data)                                              ((0x00000020&(data))>>5)
#define PLL_BUS2_PLLBUS_PSEN_shift                                                   (4)
#define PLL_BUS2_PLLBUS_PSEN_mask                                                    (0x00000010)
#define PLL_BUS2_PLLBUS_PSEN(data)                                                   (0x00000010&((data)<<4))
#define PLL_BUS2_PLLBUS_PSEN_src(data)                                               ((0x00000010&(data))>>4)
#define PLL_BUS2_get_PLLBUS_PSEN(data)                                               ((0x00000010&(data))>>4)
#define PLL_BUS2_PLLBUS_VCORB_shift                                                  (3)
#define PLL_BUS2_PLLBUS_VCORB_mask                                                   (0x00000008)
#define PLL_BUS2_PLLBUS_VCORB(data)                                                  (0x00000008&((data)<<3))
#define PLL_BUS2_PLLBUS_VCORB_src(data)                                              ((0x00000008&(data))>>3)
#define PLL_BUS2_get_PLLBUS_VCORB(data)                                              ((0x00000008&(data))>>3)
#define PLL_BUS2_write_en1_shift                                                     (2)
#define PLL_BUS2_write_en1_mask                                                      (0x00000004)
#define PLL_BUS2_write_en1(data)                                                     (0x00000004&((data)<<2))
#define PLL_BUS2_write_en1_src(data)                                                 ((0x00000004&(data))>>2)
#define PLL_BUS2_get_write_en1(data)                                                 ((0x00000004&(data))>>2)
#define PLL_BUS2_PLLBUS_TST_shift                                                    (1)
#define PLL_BUS2_PLLBUS_TST_mask                                                     (0x00000002)
#define PLL_BUS2_PLLBUS_TST(data)                                                    (0x00000002&((data)<<1))
#define PLL_BUS2_PLLBUS_TST_src(data)                                                ((0x00000002&(data))>>1)
#define PLL_BUS2_get_PLLBUS_TST(data)                                                ((0x00000002&(data))>>1)
#define PLL_BUS2_PLLBUS_PSTST_shift                                                  (0)
#define PLL_BUS2_PLLBUS_PSTST_mask                                                   (0x00000001)
#define PLL_BUS2_PLLBUS_PSTST(data)                                                  (0x00000001&((data)<<0))
#define PLL_BUS2_PLLBUS_PSTST_src(data)                                              ((0x00000001&(data))>>0)
#define PLL_BUS2_get_PLLBUS_PSTST(data)                                              ((0x00000001&(data))>>0)


#define PLL_BUS3                                                                     0x9800016C
#define PLL_BUS3_reg_addr                                                            "0x9800016C"
#define PLL_BUS3_reg                                                                 0x9800016C
#define set_PLL_BUS3_reg(data)   (*((volatile unsigned int*) PLL_BUS3_reg)=data)
#define get_PLL_BUS3_reg   (*((volatile unsigned int*) PLL_BUS3_reg))
#define PLL_BUS3_inst_adr                                                            "0x005B"
#define PLL_BUS3_inst                                                                0x005B
#define PLL_BUS3_PLLBUS_O_shift                                                      (3)
#define PLL_BUS3_PLLBUS_O_mask                                                       (0x00000018)
#define PLL_BUS3_PLLBUS_O(data)                                                      (0x00000018&((data)<<3))
#define PLL_BUS3_PLLBUS_O_src(data)                                                  ((0x00000018&(data))>>3)
#define PLL_BUS3_get_PLLBUS_O(data)                                                  ((0x00000018&(data))>>3)
#define PLL_BUS3_PLLBUS_OEB_shift                                                    (2)
#define PLL_BUS3_PLLBUS_OEB_mask                                                     (0x00000004)
#define PLL_BUS3_PLLBUS_OEB(data)                                                    (0x00000004&((data)<<2))
#define PLL_BUS3_PLLBUS_OEB_src(data)                                                ((0x00000004&(data))>>2)
#define PLL_BUS3_get_PLLBUS_OEB(data)                                                ((0x00000004&(data))>>2)
#define PLL_BUS3_PLLBUS_RSTB_shift                                                   (1)
#define PLL_BUS3_PLLBUS_RSTB_mask                                                    (0x00000002)
#define PLL_BUS3_PLLBUS_RSTB(data)                                                   (0x00000002&((data)<<1))
#define PLL_BUS3_PLLBUS_RSTB_src(data)                                               ((0x00000002&(data))>>1)
#define PLL_BUS3_get_PLLBUS_RSTB(data)                                               ((0x00000002&(data))>>1)
#define PLL_BUS3_PLLBUS_POW_shift                                                    (0)
#define PLL_BUS3_PLLBUS_POW_mask                                                     (0x00000001)
#define PLL_BUS3_PLLBUS_POW(data)                                                    (0x00000001&((data)<<0))
#define PLL_BUS3_PLLBUS_POW_src(data)                                                ((0x00000001&(data))>>0)
#define PLL_BUS3_get_PLLBUS_POW(data)                                                ((0x00000001&(data))>>0)


#define CRT_PLL_WDOUT                                                                 0x98000170
#define CRT_PLL_WDOUT_reg_addr                                                        "0x98000170"
#define CRT_PLL_WDOUT_reg                                                             0x98000170
#define CRT_set_PLL_WDOUT_reg(data)   (*((volatile unsigned int*) PLL_WDOUT_reg)=data)
#define CRT_get_PLL_WDOUT_reg   (*((volatile unsigned int*) PLL_WDOUT_reg))
#define CRT_PLL_WDOUT_inst_adr                                                        "0x005C"
#define CRT_PLL_WDOUT_inst                                                            0x005C
#define CRT_PLL_WDOUT_PLLGPU_WDOUT_shift                                              (12)
#define CRT_PLL_WDOUT_PLLGPU_WDOUT_mask                                               (0x00001000)
#define CRT_PLL_WDOUT_PLLGPU_WDOUT(data)                                              (0x00001000&((data)<<12))
#define CRT_PLL_WDOUT_PLLGPU_WDOUT_src(data)                                          ((0x00001000&(data))>>12)
#define CRT_PLL_WDOUT_get_PLLGPU_WDOUT(data)                                          ((0x00001000&(data))>>12)
#define CRT_PLL_WDOUT_PLLLVDS_WDOUT_shift                                             (11)
#define CRT_PLL_WDOUT_PLLLVDS_WDOUT_mask                                              (0x00000800)
#define CRT_PLL_WDOUT_PLLLVDS_WDOUT(data)                                             (0x00000800&((data)<<11))
#define CRT_PLL_WDOUT_PLLLVDS_WDOUT_src(data)                                         ((0x00000800&(data))>>11)
#define CRT_PLL_WDOUT_get_PLLLVDS_WDOUT(data)                                         ((0x00000800&(data))>>11)
#define CRT_PLL_WDOUT_PLLDCSB_WDOUT_shift                                             (10)
#define CRT_PLL_WDOUT_PLLDCSB_WDOUT_mask                                              (0x00000400)
#define CRT_PLL_WDOUT_PLLDCSB_WDOUT(data)                                             (0x00000400&((data)<<10))
#define CRT_PLL_WDOUT_PLLDCSB_WDOUT_src(data)                                         ((0x00000400&(data))>>10)
#define CRT_PLL_WDOUT_get_PLLDCSB_WDOUT(data)                                         ((0x00000400&(data))>>10)
#define CRT_PLL_WDOUT_PLLHDMI_WDOUT_shift                                             (9)
#define CRT_PLL_WDOUT_PLLHDMI_WDOUT_mask                                              (0x00000200)
#define CRT_PLL_WDOUT_PLLHDMI_WDOUT(data)                                             (0x00000200&((data)<<9))
#define CRT_PLL_WDOUT_PLLHDMI_WDOUT_src(data)                                         ((0x00000200&(data))>>9)
#define CRT_PLL_WDOUT_get_PLLHDMI_WDOUT(data)                                         ((0x00000200&(data))>>9)
#define CRT_PLL_WDOUT_PLLDDR_WDOUT_shift                                              (7)
#define CRT_PLL_WDOUT_PLLDDR_WDOUT_mask                                               (0x00000080)
#define CRT_PLL_WDOUT_PLLDDR_WDOUT(data)                                              (0x00000080&((data)<<7))
#define CRT_PLL_WDOUT_PLLDDR_WDOUT_src(data)                                          ((0x00000080&(data))>>7)
#define CRT_PLL_WDOUT_get_PLLDDR_WDOUT(data)                                          ((0x00000080&(data))>>7)
#define CRT_PLL_WDOUT_PLLBUS_WDOUT_shift                                              (6)
#define CRT_PLL_WDOUT_PLLBUS_WDOUT_mask                                               (0x00000040)
#define CRT_PLL_WDOUT_PLLBUS_WDOUT(data)                                              (0x00000040&((data)<<6))
#define CRT_PLL_WDOUT_PLLBUS_WDOUT_src(data)                                          ((0x00000040&(data))>>6)
#define CRT_PLL_WDOUT_get_PLLBUS_WDOUT(data)                                          ((0x00000040&(data))>>6)
#define CRT_PLL_WDOUT_PLLDISP_WDOUT_shift                                             (5)
#define CRT_PLL_WDOUT_PLLDISP_WDOUT_mask                                              (0x00000020)
#define CRT_PLL_WDOUT_PLLDISP_WDOUT(data)                                             (0x00000020&((data)<<5))
#define CRT_PLL_WDOUT_PLLDISP_WDOUT_src(data)                                         ((0x00000020&(data))>>5)
#define CRT_PLL_WDOUT_get_PLLDISP_WDOUT(data)                                         ((0x00000020&(data))>>5)
#define CRT_PLL_WDOUT_PLLDDSB_WDOUT_shift                                             (4)
#define CRT_PLL_WDOUT_PLLDDSB_WDOUT_mask                                              (0x00000010)
#define CRT_PLL_WDOUT_PLLDDSB_WDOUT(data)                                             (0x00000010&((data)<<4))
#define CRT_PLL_WDOUT_PLLDDSB_WDOUT_src(data)                                         ((0x00000010&(data))>>4)
#define CRT_PLL_WDOUT_get_PLLDDSB_WDOUT(data)                                         ((0x00000010&(data))>>4)
#define CRT_PLL_WDOUT_PLLDDSA_WDOUT_shift                                             (3)
#define CRT_PLL_WDOUT_PLLDDSA_WDOUT_mask                                              (0x00000008)
#define CRT_PLL_WDOUT_PLLDDSA_WDOUT(data)                                             (0x00000008&((data)<<3))
#define CRT_PLL_WDOUT_PLLDDSA_WDOUT_src(data)                                         ((0x00000008&(data))>>3)
#define CRT_PLL_WDOUT_get_PLLDDSA_WDOUT(data)                                         ((0x00000008&(data))>>3)
#define CRT_PLL_WDOUT_PLLVCPU_WDOUT_shift                                             (2)
#define CRT_PLL_WDOUT_PLLVCPU_WDOUT_mask                                              (0x00000004)
#define CRT_PLL_WDOUT_PLLVCPU_WDOUT(data)                                             (0x00000004&((data)<<2))
#define CRT_PLL_WDOUT_PLLVCPU_WDOUT_src(data)                                         ((0x00000004&(data))>>2)
#define CRT_PLL_WDOUT_get_PLLVCPU_WDOUT(data)                                         ((0x00000004&(data))>>2)
#define CRT_PLL_WDOUT_PLLACPU_WDOUT_shift                                             (1)
#define CRT_PLL_WDOUT_PLLACPU_WDOUT_mask                                              (0x00000002)
#define CRT_PLL_WDOUT_PLLACPU_WDOUT(data)                                             (0x00000002&((data)<<1))
#define CRT_PLL_WDOUT_PLLACPU_WDOUT_src(data)                                         ((0x00000002&(data))>>1)
#define CRT_PLL_WDOUT_get_PLLACPU_WDOUT(data)                                         ((0x00000002&(data))>>1)
#define CRT_PLL_WDOUT_PLLSCPU_WDOUT_shift                                             (0)
#define CRT_PLL_WDOUT_PLLSCPU_WDOUT_mask                                              (0x00000001)
#define CRT_PLL_WDOUT_PLLSCPU_WDOUT(data)                                             (0x00000001&((data)<<0))
#define CRT_PLL_WDOUT_PLLSCPU_WDOUT_src(data)                                         ((0x00000001&(data))>>0)
#define CRT_PLL_WDOUT_get_PLLSCPU_WDOUT(data)                                         ((0x00000001&(data))>>0)


#define PLL_DISP_2_SD1                                                               0x98000174
#define PLL_DISP_2_SD1_reg_addr                                                      "0x98000174"
#define PLL_DISP_2_SD1_reg                                                           0x98000174
#define set_PLL_DISP_2_SD1_reg(data)   (*((volatile unsigned int*) PLL_DISP_2_SD1_reg)=data)
#define get_PLL_DISP_2_SD1_reg   (*((volatile unsigned int*) PLL_DISP_2_SD1_reg))
#define PLL_DISP_2_SD1_inst_adr                                                      "0x005D"
#define PLL_DISP_2_SD1_inst                                                          0x005D
#define PLL_DISP_2_SD1_PLLDDSB_N_shift                                               (30)
#define PLL_DISP_2_SD1_PLLDDSB_N_mask                                                (0xC0000000)
#define PLL_DISP_2_SD1_PLLDDSB_N(data)                                               (0xC0000000&((data)<<30))
#define PLL_DISP_2_SD1_PLLDDSB_N_src(data)                                           ((0xC0000000&(data))>>30)
#define PLL_DISP_2_SD1_get_PLLDDSB_N(data)                                           ((0xC0000000&(data))>>30)
#define PLL_DISP_2_SD1_PLLDDSB_M_shift                                               (23)
#define PLL_DISP_2_SD1_PLLDDSB_M_mask                                                (0x3F800000)
#define PLL_DISP_2_SD1_PLLDDSB_M(data)                                               (0x3F800000&((data)<<23))
#define PLL_DISP_2_SD1_PLLDDSB_M_src(data)                                           ((0x3F800000&(data))>>23)
#define PLL_DISP_2_SD1_get_PLLDDSB_M(data)                                           ((0x3F800000&(data))>>23)
#define PLL_DISP_2_SD1_PLLDDSB_IP_shift                                              (20)
#define PLL_DISP_2_SD1_PLLDDSB_IP_mask                                               (0x00700000)
#define PLL_DISP_2_SD1_PLLDDSB_IP(data)                                              (0x00700000&((data)<<20))
#define PLL_DISP_2_SD1_PLLDDSB_IP_src(data)                                          ((0x00700000&(data))>>20)
#define PLL_DISP_2_SD1_get_PLLDDSB_IP(data)                                          ((0x00700000&(data))>>20)
#define PLL_DISP_2_SD1_PLLDDSB_RS_shift                                              (17)
#define PLL_DISP_2_SD1_PLLDDSB_RS_mask                                               (0x000E0000)
#define PLL_DISP_2_SD1_PLLDDSB_RS(data)                                              (0x000E0000&((data)<<17))
#define PLL_DISP_2_SD1_PLLDDSB_RS_src(data)                                          ((0x000E0000&(data))>>17)
#define PLL_DISP_2_SD1_get_PLLDDSB_RS(data)                                          ((0x000E0000&(data))>>17)
#define PLL_DISP_2_SD1_PLLDDSB_CS_shift                                              (15)
#define PLL_DISP_2_SD1_PLLDDSB_CS_mask                                               (0x00018000)
#define PLL_DISP_2_SD1_PLLDDSB_CS(data)                                              (0x00018000&((data)<<15))
#define PLL_DISP_2_SD1_PLLDDSB_CS_src(data)                                          ((0x00018000&(data))>>15)
#define PLL_DISP_2_SD1_get_PLLDDSB_CS(data)                                          ((0x00018000&(data))>>15)
#define PLL_DISP_2_SD1_PLLDDSB_CP_shift                                              (13)
#define PLL_DISP_2_SD1_PLLDDSB_CP_mask                                               (0x00006000)
#define PLL_DISP_2_SD1_PLLDDSB_CP(data)                                              (0x00006000&((data)<<13))
#define PLL_DISP_2_SD1_PLLDDSB_CP_src(data)                                          ((0x00006000&(data))>>13)
#define PLL_DISP_2_SD1_get_PLLDDSB_CP(data)                                          ((0x00006000&(data))>>13)
#define PLL_DISP_2_SD1_PLLDDSB_R3_shift                                              (10)
#define PLL_DISP_2_SD1_PLLDDSB_R3_mask                                               (0x00001C00)
#define PLL_DISP_2_SD1_PLLDDSB_R3(data)                                              (0x00001C00&((data)<<10))
#define PLL_DISP_2_SD1_PLLDDSB_R3_src(data)                                          ((0x00001C00&(data))>>10)
#define PLL_DISP_2_SD1_get_PLLDDSB_R3(data)                                          ((0x00001C00&(data))>>10)
#define PLL_DISP_2_SD1_PLLDDSB_C3_shift                                              (8)
#define PLL_DISP_2_SD1_PLLDDSB_C3_mask                                               (0x00000300)
#define PLL_DISP_2_SD1_PLLDDSB_C3(data)                                              (0x00000300&((data)<<8))
#define PLL_DISP_2_SD1_PLLDDSB_C3_src(data)                                          ((0x00000300&(data))>>8)
#define PLL_DISP_2_SD1_get_PLLDDSB_C3(data)                                          ((0x00000300&(data))>>8)
#define PLL_DISP_2_SD1_PLLDDSB_PI_RL_shift                                           (6)
#define PLL_DISP_2_SD1_PLLDDSB_PI_RL_mask                                            (0x000000C0)
#define PLL_DISP_2_SD1_PLLDDSB_PI_RL(data)                                           (0x000000C0&((data)<<6))
#define PLL_DISP_2_SD1_PLLDDSB_PI_RL_src(data)                                       ((0x000000C0&(data))>>6)
#define PLL_DISP_2_SD1_get_PLLDDSB_PI_RL(data)                                       ((0x000000C0&(data))>>6)
#define PLL_DISP_2_SD1_PLLDDSB_PI_RS_shift                                           (4)
#define PLL_DISP_2_SD1_PLLDDSB_PI_RS_mask                                            (0x00000030)
#define PLL_DISP_2_SD1_PLLDDSB_PI_RS(data)                                           (0x00000030&((data)<<4))
#define PLL_DISP_2_SD1_PLLDDSB_PI_RS_src(data)                                       ((0x00000030&(data))>>4)
#define PLL_DISP_2_SD1_get_PLLDDSB_PI_RS(data)                                       ((0x00000030&(data))>>4)
#define PLL_DISP_2_SD1_PLLDDSB_PI_BIAS_shift                                         (2)
#define PLL_DISP_2_SD1_PLLDDSB_PI_BIAS_mask                                          (0x0000000C)
#define PLL_DISP_2_SD1_PLLDDSB_PI_BIAS(data)                                         (0x0000000C&((data)<<2))
#define PLL_DISP_2_SD1_PLLDDSB_PI_BIAS_src(data)                                     ((0x0000000C&(data))>>2)
#define PLL_DISP_2_SD1_get_PLLDDSB_PI_BIAS(data)                                     ((0x0000000C&(data))>>2)
#define PLL_DISP_2_SD1_PLLDDSB_WDMODE_shift                                          (0)
#define PLL_DISP_2_SD1_PLLDDSB_WDMODE_mask                                           (0x00000003)
#define PLL_DISP_2_SD1_PLLDDSB_WDMODE(data)                                          (0x00000003&((data)<<0))
#define PLL_DISP_2_SD1_PLLDDSB_WDMODE_src(data)                                      ((0x00000003&(data))>>0)
#define PLL_DISP_2_SD1_get_PLLDDSB_WDMODE(data)                                      ((0x00000003&(data))>>0)


#define PLL_DISP_2_SD2                                                               0x98000178
#define PLL_DISP_2_SD2_reg_addr                                                      "0x98000178"
#define PLL_DISP_2_SD2_reg                                                           0x98000178
#define set_PLL_DISP_2_SD2_reg(data)   (*((volatile unsigned int*) PLL_DISP_2_SD2_reg)=data)
#define get_PLL_DISP_2_SD2_reg   (*((volatile unsigned int*) PLL_DISP_2_SD2_reg))
#define PLL_DISP_2_SD2_inst_adr                                                      "0x005E"
#define PLL_DISP_2_SD2_inst                                                          0x005E
#define PLL_DISP_2_SD2_write_en10_shift                                              (25)
#define PLL_DISP_2_SD2_write_en10_mask                                               (0x02000000)
#define PLL_DISP_2_SD2_write_en10(data)                                              (0x02000000&((data)<<25))
#define PLL_DISP_2_SD2_write_en10_src(data)                                          ((0x02000000&(data))>>25)
#define PLL_DISP_2_SD2_get_write_en10(data)                                          ((0x02000000&(data))>>25)
#define PLL_DISP_2_SD2_pcr_b_smooth_en_shift                                         (24)
#define PLL_DISP_2_SD2_pcr_b_smooth_en_mask                                          (0x01000000)
#define PLL_DISP_2_SD2_pcr_b_smooth_en(data)                                         (0x01000000&((data)<<24))
#define PLL_DISP_2_SD2_pcr_b_smooth_en_src(data)                                     ((0x01000000&(data))>>24)
#define PLL_DISP_2_SD2_get_pcr_b_smooth_en(data)                                     ((0x01000000&(data))>>24)
#define PLL_DISP_2_SD2_write_en9_shift                                               (23)
#define PLL_DISP_2_SD2_write_en9_mask                                                (0x00800000)
#define PLL_DISP_2_SD2_write_en9(data)                                               (0x00800000&((data)<<23))
#define PLL_DISP_2_SD2_write_en9_src(data)                                           ((0x00800000&(data))>>23)
#define PLL_DISP_2_SD2_get_write_en9(data)                                           ((0x00800000&(data))>>23)
#define PLL_DISP_2_SD2_pcr_b_phase_sel_shift                                         (22)
#define PLL_DISP_2_SD2_pcr_b_phase_sel_mask                                          (0x00400000)
#define PLL_DISP_2_SD2_pcr_b_phase_sel(data)                                         (0x00400000&((data)<<22))
#define PLL_DISP_2_SD2_pcr_b_phase_sel_src(data)                                     ((0x00400000&(data))>>22)
#define PLL_DISP_2_SD2_get_pcr_b_phase_sel(data)                                     ((0x00400000&(data))>>22)
#define PLL_DISP_2_SD2_write_en8_shift                                               (21)
#define PLL_DISP_2_SD2_write_en8_mask                                                (0x00200000)
#define PLL_DISP_2_SD2_write_en8(data)                                               (0x00200000&((data)<<21))
#define PLL_DISP_2_SD2_write_en8_src(data)                                           ((0x00200000&(data))>>21)
#define PLL_DISP_2_SD2_get_write_en8(data)                                           ((0x00200000&(data))>>21)
#define PLL_DISP_2_SD2_pcr_b_ctl_en_shift                                            (20)
#define PLL_DISP_2_SD2_pcr_b_ctl_en_mask                                             (0x00100000)
#define PLL_DISP_2_SD2_pcr_b_ctl_en(data)                                            (0x00100000&((data)<<20))
#define PLL_DISP_2_SD2_pcr_b_ctl_en_src(data)                                        ((0x00100000&(data))>>20)
#define PLL_DISP_2_SD2_get_pcr_b_ctl_en(data)                                        ((0x00100000&(data))>>20)
#define PLL_DISP_2_SD2_write_en7_shift                                               (19)
#define PLL_DISP_2_SD2_write_en7_mask                                                (0x00080000)
#define PLL_DISP_2_SD2_write_en7(data)                                               (0x00080000&((data)<<19))
#define PLL_DISP_2_SD2_write_en7_src(data)                                           ((0x00080000&(data))>>19)
#define PLL_DISP_2_SD2_get_write_en7(data)                                           ((0x00080000&(data))>>19)
#define PLL_DISP_2_SD2_PLLDDSB_FUPDN_shift                                           (18)
#define PLL_DISP_2_SD2_PLLDDSB_FUPDN_mask                                            (0x00040000)
#define PLL_DISP_2_SD2_PLLDDSB_FUPDN(data)                                           (0x00040000&((data)<<18))
#define PLL_DISP_2_SD2_PLLDDSB_FUPDN_src(data)                                       ((0x00040000&(data))>>18)
#define PLL_DISP_2_SD2_get_PLLDDSB_FUPDN(data)                                       ((0x00040000&(data))>>18)
#define PLL_DISP_2_SD2_write_en6_shift                                               (17)
#define PLL_DISP_2_SD2_write_en6_mask                                                (0x00020000)
#define PLL_DISP_2_SD2_write_en6(data)                                               (0x00020000&((data)<<17))
#define PLL_DISP_2_SD2_write_en6_src(data)                                           ((0x00020000&(data))>>17)
#define PLL_DISP_2_SD2_get_write_en6(data)                                           ((0x00020000&(data))>>17)
#define PLL_DISP_2_SD2_PLLDDSB_DDSEN_shift                                           (16)
#define PLL_DISP_2_SD2_PLLDDSB_DDSEN_mask                                            (0x00010000)
#define PLL_DISP_2_SD2_PLLDDSB_DDSEN(data)                                           (0x00010000&((data)<<16))
#define PLL_DISP_2_SD2_PLLDDSB_DDSEN_src(data)                                       ((0x00010000&(data))>>16)
#define PLL_DISP_2_SD2_get_PLLDDSB_DDSEN(data)                                       ((0x00010000&(data))>>16)
#define PLL_DISP_2_SD2_write_en5_shift                                               (15)
#define PLL_DISP_2_SD2_write_en5_mask                                                (0x00008000)
#define PLL_DISP_2_SD2_write_en5(data)                                               (0x00008000&((data)<<15))
#define PLL_DISP_2_SD2_write_en5_src(data)                                           ((0x00008000&(data))>>15)
#define PLL_DISP_2_SD2_get_write_en5(data)                                           ((0x00008000&(data))>>15)
#define PLL_DISP_2_SD2_PLLDDSB_VCORB_shift                                           (14)
#define PLL_DISP_2_SD2_PLLDDSB_VCORB_mask                                            (0x00004000)
#define PLL_DISP_2_SD2_PLLDDSB_VCORB(data)                                           (0x00004000&((data)<<14))
#define PLL_DISP_2_SD2_PLLDDSB_VCORB_src(data)                                       ((0x00004000&(data))>>14)
#define PLL_DISP_2_SD2_get_PLLDDSB_VCORB(data)                                       ((0x00004000&(data))>>14)
#define PLL_DISP_2_SD2_write_en4_shift                                               (13)
#define PLL_DISP_2_SD2_write_en4_mask                                                (0x00002000)
#define PLL_DISP_2_SD2_write_en4(data)                                               (0x00002000&((data)<<13))
#define PLL_DISP_2_SD2_write_en4_src(data)                                           ((0x00002000&(data))>>13)
#define PLL_DISP_2_SD2_get_write_en4(data)                                           ((0x00002000&(data))>>13)
#define PLL_DISP_2_SD2_PLLDDSB_TST_shift                                             (12)
#define PLL_DISP_2_SD2_PLLDDSB_TST_mask                                              (0x00001000)
#define PLL_DISP_2_SD2_PLLDDSB_TST(data)                                             (0x00001000&((data)<<12))
#define PLL_DISP_2_SD2_PLLDDSB_TST_src(data)                                         ((0x00001000&(data))>>12)
#define PLL_DISP_2_SD2_get_PLLDDSB_TST(data)                                         ((0x00001000&(data))>>12)
#define PLL_DISP_2_SD2_PLLDDSB_PSTST_shift                                           (11)
#define PLL_DISP_2_SD2_PLLDDSB_PSTST_mask                                            (0x00000800)
#define PLL_DISP_2_SD2_PLLDDSB_PSTST(data)                                           (0x00000800&((data)<<11))
#define PLL_DISP_2_SD2_PLLDDSB_PSTST_src(data)                                       ((0x00000800&(data))>>11)
#define PLL_DISP_2_SD2_get_PLLDDSB_PSTST(data)                                       ((0x00000800&(data))>>11)
#define PLL_DISP_2_SD2_write_en3_shift                                               (10)
#define PLL_DISP_2_SD2_write_en3_mask                                                (0x00000400)
#define PLL_DISP_2_SD2_write_en3(data)                                               (0x00000400&((data)<<10))
#define PLL_DISP_2_SD2_write_en3_src(data)                                           ((0x00000400&(data))>>10)
#define PLL_DISP_2_SD2_get_write_en3(data)                                           ((0x00000400&(data))>>10)
#define PLL_DISP_2_SD2_PSAUD1B_FUPDN_shift                                           (9)
#define PLL_DISP_2_SD2_PSAUD1B_FUPDN_mask                                            (0x00000200)
#define PLL_DISP_2_SD2_PSAUD1B_FUPDN(data)                                           (0x00000200&((data)<<9))
#define PLL_DISP_2_SD2_PSAUD1B_FUPDN_src(data)                                       ((0x00000200&(data))>>9)
#define PLL_DISP_2_SD2_get_PSAUD1B_FUPDN(data)                                       ((0x00000200&(data))>>9)
#define PLL_DISP_2_SD2_PSAUD1B_DIV_shift                                             (8)
#define PLL_DISP_2_SD2_PSAUD1B_DIV_mask                                              (0x00000100)
#define PLL_DISP_2_SD2_PSAUD1B_DIV(data)                                             (0x00000100&((data)<<8))
#define PLL_DISP_2_SD2_PSAUD1B_DIV_src(data)                                         ((0x00000100&(data))>>8)
#define PLL_DISP_2_SD2_get_PSAUD1B_DIV(data)                                         ((0x00000100&(data))>>8)
#define PLL_DISP_2_SD2_write_en2_shift                                               (7)
#define PLL_DISP_2_SD2_write_en2_mask                                                (0x00000080)
#define PLL_DISP_2_SD2_write_en2(data)                                               (0x00000080&((data)<<7))
#define PLL_DISP_2_SD2_write_en2_src(data)                                           ((0x00000080&(data))>>7)
#define PLL_DISP_2_SD2_get_write_en2(data)                                           ((0x00000080&(data))>>7)
#define PLL_DISP_2_SD2_PSAUD1B_TST_shift                                             (6)
#define PLL_DISP_2_SD2_PSAUD1B_TST_mask                                              (0x00000040)
#define PLL_DISP_2_SD2_PSAUD1B_TST(data)                                             (0x00000040&((data)<<6))
#define PLL_DISP_2_SD2_PSAUD1B_TST_src(data)                                         ((0x00000040&(data))>>6)
#define PLL_DISP_2_SD2_get_PSAUD1B_TST(data)                                         ((0x00000040&(data))>>6)
#define PLL_DISP_2_SD2_PSAUD1B_PSEN_shift                                            (5)
#define PLL_DISP_2_SD2_PSAUD1B_PSEN_mask                                             (0x00000020)
#define PLL_DISP_2_SD2_PSAUD1B_PSEN(data)                                            (0x00000020&((data)<<5))
#define PLL_DISP_2_SD2_PSAUD1B_PSEN_src(data)                                        ((0x00000020&(data))>>5)
#define PLL_DISP_2_SD2_get_PSAUD1B_PSEN(data)                                        ((0x00000020&(data))>>5)
#define PLL_DISP_2_SD2_write_en1_shift                                               (4)
#define PLL_DISP_2_SD2_write_en1_mask                                                (0x00000010)
#define PLL_DISP_2_SD2_write_en1(data)                                               (0x00000010&((data)<<4))
#define PLL_DISP_2_SD2_write_en1_src(data)                                           ((0x00000010&(data))>>4)
#define PLL_DISP_2_SD2_get_write_en1(data)                                           ((0x00000010&(data))>>4)
#define PLL_DISP_2_SD2_PSAUD2B_FUPDN_shift                                           (3)
#define PLL_DISP_2_SD2_PSAUD2B_FUPDN_mask                                            (0x00000008)
#define PLL_DISP_2_SD2_PSAUD2B_FUPDN(data)                                           (0x00000008&((data)<<3))
#define PLL_DISP_2_SD2_PSAUD2B_FUPDN_src(data)                                       ((0x00000008&(data))>>3)
#define PLL_DISP_2_SD2_get_PSAUD2B_FUPDN(data)                                       ((0x00000008&(data))>>3)
#define PLL_DISP_2_SD2_PSAUD2B_DIV_shift                                             (2)
#define PLL_DISP_2_SD2_PSAUD2B_DIV_mask                                              (0x00000004)
#define PLL_DISP_2_SD2_PSAUD2B_DIV(data)                                             (0x00000004&((data)<<2))
#define PLL_DISP_2_SD2_PSAUD2B_DIV_src(data)                                         ((0x00000004&(data))>>2)
#define PLL_DISP_2_SD2_get_PSAUD2B_DIV(data)                                         ((0x00000004&(data))>>2)
#define PLL_DISP_2_SD2_PSAUD2B_TST_shift                                             (1)
#define PLL_DISP_2_SD2_PSAUD2B_TST_mask                                              (0x00000002)
#define PLL_DISP_2_SD2_PSAUD2B_TST(data)                                             (0x00000002&((data)<<1))
#define PLL_DISP_2_SD2_PSAUD2B_TST_src(data)                                         ((0x00000002&(data))>>1)
#define PLL_DISP_2_SD2_get_PSAUD2B_TST(data)                                         ((0x00000002&(data))>>1)
#define PLL_DISP_2_SD2_PSAUD2B_PSEN_shift                                            (0)
#define PLL_DISP_2_SD2_PSAUD2B_PSEN_mask                                             (0x00000001)
#define PLL_DISP_2_SD2_PSAUD2B_PSEN(data)                                            (0x00000001&((data)<<0))
#define PLL_DISP_2_SD2_PSAUD2B_PSEN_src(data)                                        ((0x00000001&(data))>>0)
#define PLL_DISP_2_SD2_get_PSAUD2B_PSEN(data)                                        ((0x00000001&(data))>>0)


#define PLL_DISP_2_SD3                                                               0x9800017C
#define PLL_DISP_2_SD3_reg_addr                                                      "0x9800017C"
#define PLL_DISP_2_SD3_reg                                                           0x9800017C
#define set_PLL_DISP_2_SD3_reg(data)   (*((volatile unsigned int*) PLL_DISP_2_SD3_reg)=data)
#define get_PLL_DISP_2_SD3_reg   (*((volatile unsigned int*) PLL_DISP_2_SD3_reg))
#define PLL_DISP_2_SD3_inst_adr                                                      "0x005F"
#define PLL_DISP_2_SD3_inst                                                          0x005F
#define PLL_DISP_2_SD3_PSAUD1B_OEB_shift                                             (3)
#define PLL_DISP_2_SD3_PSAUD1B_OEB_mask                                              (0x00000008)
#define PLL_DISP_2_SD3_PSAUD1B_OEB(data)                                             (0x00000008&((data)<<3))
#define PLL_DISP_2_SD3_PSAUD1B_OEB_src(data)                                         ((0x00000008&(data))>>3)
#define PLL_DISP_2_SD3_get_PSAUD1B_OEB(data)                                         ((0x00000008&(data))>>3)
#define PLL_DISP_2_SD3_PSAUD1B_RSTB_shift                                            (2)
#define PLL_DISP_2_SD3_PSAUD1B_RSTB_mask                                             (0x00000004)
#define PLL_DISP_2_SD3_PSAUD1B_RSTB(data)                                            (0x00000004&((data)<<2))
#define PLL_DISP_2_SD3_PSAUD1B_RSTB_src(data)                                        ((0x00000004&(data))>>2)
#define PLL_DISP_2_SD3_get_PSAUD1B_RSTB(data)                                        ((0x00000004&(data))>>2)
#define PLL_DISP_2_SD3_PSAUD2B_OEB_shift                                             (1)
#define PLL_DISP_2_SD3_PSAUD2B_OEB_mask                                              (0x00000002)
#define PLL_DISP_2_SD3_PSAUD2B_OEB(data)                                             (0x00000002&((data)<<1))
#define PLL_DISP_2_SD3_PSAUD2B_OEB_src(data)                                         ((0x00000002&(data))>>1)
#define PLL_DISP_2_SD3_get_PSAUD2B_OEB(data)                                         ((0x00000002&(data))>>1)
#define PLL_DISP_2_SD3_PSAUD2B_RSTB_shift                                            (0)
#define PLL_DISP_2_SD3_PSAUD2B_RSTB_mask                                             (0x00000001)
#define PLL_DISP_2_SD3_PSAUD2B_RSTB(data)                                            (0x00000001&((data)<<0))
#define PLL_DISP_2_SD3_PSAUD2B_RSTB_src(data)                                        ((0x00000001&(data))>>0)
#define PLL_DISP_2_SD3_get_PSAUD2B_RSTB(data)                                        ((0x00000001&(data))>>0)


#define PLL_DISP_2_SD4                                                               0x98000180
#define PLL_DISP_2_SD4_reg_addr                                                      "0x98000180"
#define PLL_DISP_2_SD4_reg                                                           0x98000180
#define set_PLL_DISP_2_SD4_reg(data)   (*((volatile unsigned int*) PLL_DISP_2_SD4_reg)=data)
#define get_PLL_DISP_2_SD4_reg   (*((volatile unsigned int*) PLL_DISP_2_SD4_reg))
#define PLL_DISP_2_SD4_inst_adr                                                      "0x0060"
#define PLL_DISP_2_SD4_inst                                                          0x0060
#define PLL_DISP_2_SD4_PLLDDSB_K_shift                                               (4)
#define PLL_DISP_2_SD4_PLLDDSB_K_mask                                                (0x00000030)
#define PLL_DISP_2_SD4_PLLDDSB_K(data)                                               (0x00000030&((data)<<4))
#define PLL_DISP_2_SD4_PLLDDSB_K_src(data)                                           ((0x00000030&(data))>>4)
#define PLL_DISP_2_SD4_get_PLLDDSB_K(data)                                           ((0x00000030&(data))>>4)
#define PLL_DISP_2_SD4_PLLDDSB_OEB_shift                                             (2)
#define PLL_DISP_2_SD4_PLLDDSB_OEB_mask                                              (0x00000004)
#define PLL_DISP_2_SD4_PLLDDSB_OEB(data)                                             (0x00000004&((data)<<2))
#define PLL_DISP_2_SD4_PLLDDSB_OEB_src(data)                                         ((0x00000004&(data))>>2)
#define PLL_DISP_2_SD4_get_PLLDDSB_OEB(data)                                         ((0x00000004&(data))>>2)
#define PLL_DISP_2_SD4_PLLDDSB_RSTB_shift                                            (1)
#define PLL_DISP_2_SD4_PLLDDSB_RSTB_mask                                             (0x00000002)
#define PLL_DISP_2_SD4_PLLDDSB_RSTB(data)                                            (0x00000002&((data)<<1))
#define PLL_DISP_2_SD4_PLLDDSB_RSTB_src(data)                                        ((0x00000002&(data))>>1)
#define PLL_DISP_2_SD4_get_PLLDDSB_RSTB(data)                                        ((0x00000002&(data))>>1)
#define PLL_DISP_2_SD4_PLLDDSB_POW_shift                                             (0)
#define PLL_DISP_2_SD4_PLLDDSB_POW_mask                                              (0x00000001)
#define PLL_DISP_2_SD4_PLLDDSB_POW(data)                                             (0x00000001&((data)<<0))
#define PLL_DISP_2_SD4_PLLDDSB_POW_src(data)                                         ((0x00000001&(data))>>0)
#define PLL_DISP_2_SD4_get_PLLDDSB_POW(data)                                         ((0x00000001&(data))>>0)


#define PLL_DISP_2_SD5                                                               0x98000184
#define PLL_DISP_2_SD5_reg_addr                                                      "0x98000184"
#define PLL_DISP_2_SD5_reg                                                           0x98000184
#define set_PLL_DISP_2_SD5_reg(data)   (*((volatile unsigned int*) PLL_DISP_2_SD5_reg)=data)
#define get_PLL_DISP_2_SD5_reg   (*((volatile unsigned int*) PLL_DISP_2_SD5_reg))
#define PLL_DISP_2_SD5_inst_adr                                                      "0x0061"
#define PLL_DISP_2_SD5_inst                                                          0x0061
#define PLL_DISP_2_SD5_N_shift                                                       (16)
#define PLL_DISP_2_SD5_N_mask                                                        (0xFFFF0000)
#define PLL_DISP_2_SD5_N(data)                                                       (0xFFFF0000&((data)<<16))
#define PLL_DISP_2_SD5_N_src(data)                                                   ((0xFFFF0000&(data))>>16)
#define PLL_DISP_2_SD5_get_N(data)                                                   ((0xFFFF0000&(data))>>16)
#define PLL_DISP_2_SD5_M_shift                                                       (0)
#define PLL_DISP_2_SD5_M_mask                                                        (0x0000FFFF)
#define PLL_DISP_2_SD5_M(data)                                                       (0x0000FFFF&((data)<<0))
#define PLL_DISP_2_SD5_M_src(data)                                                   ((0x0000FFFF&(data))>>0)
#define PLL_DISP_2_SD5_get_M(data)                                                   ((0x0000FFFF&(data))>>0)


#define PLL_DISP_2_SD6                                                               0x98000188
#define PLL_DISP_2_SD6_reg_addr                                                      "0x98000188"
#define PLL_DISP_2_SD6_reg                                                           0x98000188
#define set_PLL_DISP_2_SD6_reg(data)   (*((volatile unsigned int*) PLL_DISP_2_SD6_reg)=data)
#define get_PLL_DISP_2_SD6_reg   (*((volatile unsigned int*) PLL_DISP_2_SD6_reg))
#define PLL_DISP_2_SD6_inst_adr                                                      "0x0062"
#define PLL_DISP_2_SD6_inst                                                          0x0062
#define PLL_DISP_2_SD6_N_nxt_shift                                                   (0)
#define PLL_DISP_2_SD6_N_nxt_mask                                                    (0x0000FFFF)
#define PLL_DISP_2_SD6_N_nxt(data)                                                   (0x0000FFFF&((data)<<0))
#define PLL_DISP_2_SD6_N_nxt_src(data)                                               ((0x0000FFFF&(data))>>0)
#define PLL_DISP_2_SD6_get_N_nxt(data)                                               ((0x0000FFFF&(data))>>0)


#define PLL_DISP_2_SD7                                                               0x9800018C
#define PLL_DISP_2_SD7_reg_addr                                                      "0x9800018C"
#define PLL_DISP_2_SD7_reg                                                           0x9800018C
#define set_PLL_DISP_2_SD7_reg(data)   (*((volatile unsigned int*) PLL_DISP_2_SD7_reg)=data)
#define get_PLL_DISP_2_SD7_reg   (*((volatile unsigned int*) PLL_DISP_2_SD7_reg))
#define PLL_DISP_2_SD7_inst_adr                                                      "0x0063"
#define PLL_DISP_2_SD7_inst                                                          0x0063
#define PLL_DISP_2_SD7_N_nxt_add_shift                                               (16)
#define PLL_DISP_2_SD7_N_nxt_add_mask                                                (0x00FF0000)
#define PLL_DISP_2_SD7_N_nxt_add(data)                                               (0x00FF0000&((data)<<16))
#define PLL_DISP_2_SD7_N_nxt_add_src(data)                                           ((0x00FF0000&(data))>>16)
#define PLL_DISP_2_SD7_get_N_nxt_add(data)                                           ((0x00FF0000&(data))>>16)
#define PLL_DISP_2_SD7_N_nxt_add_period_shift                                        (0)
#define PLL_DISP_2_SD7_N_nxt_add_period_mask                                         (0x0000FFFF)
#define PLL_DISP_2_SD7_N_nxt_add_period(data)                                        (0x0000FFFF&((data)<<0))
#define PLL_DISP_2_SD7_N_nxt_add_period_src(data)                                    ((0x0000FFFF&(data))>>0)
#define PLL_DISP_2_SD7_get_N_nxt_add_period(data)                                    ((0x0000FFFF&(data))>>0)


#define PLL_HDMI                                                                     0x98000190
#define PLL_HDMI_reg_addr                                                            "0x98000190"
#define PLL_HDMI_reg                                                                 0x98000190
#define set_PLL_HDMI_reg(data)   (*((volatile unsigned int*) PLL_HDMI_reg)=data)
#define get_PLL_HDMI_reg   (*((volatile unsigned int*) PLL_HDMI_reg))
#define PLL_HDMI_inst_adr                                                            "0x0064"
#define PLL_HDMI_inst                                                                0x0064
#define PLL_HDMI_REG_LDO_TMDS_PU_shift                                               (2)
#define PLL_HDMI_REG_LDO_TMDS_PU_mask                                                (0x00000004)
#define PLL_HDMI_REG_LDO_TMDS_PU(data)                                               (0x00000004&((data)<<2))
#define PLL_HDMI_REG_LDO_TMDS_PU_src(data)                                           ((0x00000004&(data))>>2)
#define PLL_HDMI_get_REG_LDO_TMDS_PU(data)                                           ((0x00000004&(data))>>2)
#define PLL_HDMI_REG_TV_PLL_PU_shift                                                 (1)
#define PLL_HDMI_REG_TV_PLL_PU_mask                                                  (0x00000002)
#define PLL_HDMI_REG_TV_PLL_PU(data)                                                 (0x00000002&((data)<<1))
#define PLL_HDMI_REG_TV_PLL_PU_src(data)                                             ((0x00000002&(data))>>1)
#define PLL_HDMI_get_REG_TV_PLL_PU(data)                                             ((0x00000002&(data))>>1)
#define PLL_HDMI_REG_HDMI_CK_EN_shift                                                (0)
#define PLL_HDMI_REG_HDMI_CK_EN_mask                                                 (0x00000001)
#define PLL_HDMI_REG_HDMI_CK_EN(data)                                                (0x00000001&((data)<<0))
#define PLL_HDMI_REG_HDMI_CK_EN_src(data)                                            ((0x00000001&(data))>>0)
#define PLL_HDMI_get_REG_HDMI_CK_EN(data)                                            ((0x00000001&(data))>>0)


#define PLL_HDMI2                                                                    0x98000194
#define PLL_HDMI2_reg_addr                                                           "0x98000194"
#define PLL_HDMI2_reg                                                                0x98000194
#define set_PLL_HDMI2_reg(data)   (*((volatile unsigned int*) PLL_HDMI2_reg)=data)
#define get_PLL_HDMI2_reg   (*((volatile unsigned int*) PLL_HDMI2_reg))
#define PLL_HDMI2_inst_adr                                                           "0x0065"
#define PLL_HDMI2_inst                                                               0x0065
#define PLL_HDMI2_REG_TV_PRE_DIV_shift                                               (19)
#define PLL_HDMI2_REG_TV_PRE_DIV_mask                                                (0x00080000)
#define PLL_HDMI2_REG_TV_PRE_DIV(data)                                               (0x00080000&((data)<<19))
#define PLL_HDMI2_REG_TV_PRE_DIV_src(data)                                           ((0x00080000&(data))>>19)
#define PLL_HDMI2_get_REG_TV_PRE_DIV(data)                                           ((0x00080000&(data))>>19)
#define PLL_HDMI2_REG_TV_LDIV_shift                                                  (13)
#define PLL_HDMI2_REG_TV_LDIV_mask                                                   (0x0007E000)
#define PLL_HDMI2_REG_TV_LDIV(data)                                                  (0x0007E000&((data)<<13))
#define PLL_HDMI2_REG_TV_LDIV_src(data)                                              ((0x0007E000&(data))>>13)
#define PLL_HDMI2_get_REG_TV_LDIV(data)                                              ((0x0007E000&(data))>>13)
#define PLL_HDMI2_REG_TV_PSTEP_EN_shift                                              (12)
#define PLL_HDMI2_REG_TV_PSTEP_EN_mask                                               (0x00001000)
#define PLL_HDMI2_REG_TV_PSTEP_EN(data)                                              (0x00001000&((data)<<12))
#define PLL_HDMI2_REG_TV_PSTEP_EN_src(data)                                          ((0x00001000&(data))>>12)
#define PLL_HDMI2_get_REG_TV_PSTEP_EN(data)                                          ((0x00001000&(data))>>12)
#define PLL_HDMI2_REG_TV_PSTEP_shift                                                 (9)
#define PLL_HDMI2_REG_TV_PSTEP_mask                                                  (0x00000E00)
#define PLL_HDMI2_REG_TV_PSTEP(data)                                                 (0x00000E00&((data)<<9))
#define PLL_HDMI2_REG_TV_PSTEP_src(data)                                             ((0x00000E00&(data))>>9)
#define PLL_HDMI2_get_REG_TV_PSTEP(data)                                             ((0x00000E00&(data))>>9)
#define PLL_HDMI2_REG_PIXEL_DIV3_shift                                               (8)
#define PLL_HDMI2_REG_PIXEL_DIV3_mask                                                (0x00000100)
#define PLL_HDMI2_REG_PIXEL_DIV3(data)                                               (0x00000100&((data)<<8))
#define PLL_HDMI2_REG_PIXEL_DIV3_src(data)                                           ((0x00000100&(data))>>8)
#define PLL_HDMI2_get_REG_PIXEL_DIV3(data)                                           ((0x00000100&(data))>>8)
#define PLL_HDMI2_REG_PIXEL_DIV5_shift                                               (7)
#define PLL_HDMI2_REG_PIXEL_DIV5_mask                                                (0x00000080)
#define PLL_HDMI2_REG_PIXEL_DIV5(data)                                               (0x00000080&((data)<<7))
#define PLL_HDMI2_REG_PIXEL_DIV5_src(data)                                           ((0x00000080&(data))>>7)
#define PLL_HDMI2_get_REG_PIXEL_DIV5(data)                                           ((0x00000080&(data))>>7)
#define PLL_HDMI2_REG_PIXEL_DIV16_shift                                              (4)
#define PLL_HDMI2_REG_PIXEL_DIV16_mask                                               (0x00000070)
#define PLL_HDMI2_REG_PIXEL_DIV16(data)                                              (0x00000070&((data)<<4))
#define PLL_HDMI2_REG_PIXEL_DIV16_src(data)                                          ((0x00000070&(data))>>4)
#define PLL_HDMI2_get_REG_PIXEL_DIV16(data)                                          ((0x00000070&(data))>>4)
#define PLL_HDMI2_REG_TMDS_DIV5_shift                                                (3)
#define PLL_HDMI2_REG_TMDS_DIV5_mask                                                 (0x00000008)
#define PLL_HDMI2_REG_TMDS_DIV5(data)                                                (0x00000008&((data)<<3))
#define PLL_HDMI2_REG_TMDS_DIV5_src(data)                                            ((0x00000008&(data))>>3)
#define PLL_HDMI2_get_REG_TMDS_DIV5(data)                                            ((0x00000008&(data))>>3)
#define PLL_HDMI2_REG_TMDS_DIV16_shift                                               (0)
#define PLL_HDMI2_REG_TMDS_DIV16_mask                                                (0x00000007)
#define PLL_HDMI2_REG_TMDS_DIV16(data)                                               (0x00000007&((data)<<0))
#define PLL_HDMI2_REG_TMDS_DIV16_src(data)                                           ((0x00000007&(data))>>0)
#define PLL_HDMI2_get_REG_TMDS_DIV16(data)                                           ((0x00000007&(data))>>0)


#define PLL_DCSB1                                                                    0x980001B0
#define PLL_DCSB1_reg_addr                                                           "0x980001B0"
#define PLL_DCSB1_reg                                                                0x980001B0
#define set_PLL_DCSB1_reg(data)   (*((volatile unsigned int*) PLL_DCSB1_reg)=data)
#define get_PLL_DCSB1_reg   (*((volatile unsigned int*) PLL_DCSB1_reg))
#define PLL_DCSB1_inst_adr                                                           "0x006C"
#define PLL_DCSB1_inst                                                               0x006C
#define PLL_DCSB1_PLLDCSB_N_shift                                                    (25)
#define PLL_DCSB1_PLLDCSB_N_mask                                                     (0x06000000)
#define PLL_DCSB1_PLLDCSB_N(data)                                                    (0x06000000&((data)<<25))
#define PLL_DCSB1_PLLDCSB_N_src(data)                                                ((0x06000000&(data))>>25)
#define PLL_DCSB1_get_PLLDCSB_N(data)                                                ((0x06000000&(data))>>25)
#define PLL_DCSB1_PLLDCSB_M_shift                                                    (18)
#define PLL_DCSB1_PLLDCSB_M_mask                                                     (0x01FC0000)
#define PLL_DCSB1_PLLDCSB_M(data)                                                    (0x01FC0000&((data)<<18))
#define PLL_DCSB1_PLLDCSB_M_src(data)                                                ((0x01FC0000&(data))>>18)
#define PLL_DCSB1_get_PLLDCSB_M(data)                                                ((0x01FC0000&(data))>>18)
#define PLL_DCSB1_PLLDCSB_IP_shift                                                   (15)
#define PLL_DCSB1_PLLDCSB_IP_mask                                                    (0x00038000)
#define PLL_DCSB1_PLLDCSB_IP(data)                                                   (0x00038000&((data)<<15))
#define PLL_DCSB1_PLLDCSB_IP_src(data)                                               ((0x00038000&(data))>>15)
#define PLL_DCSB1_get_PLLDCSB_IP(data)                                               ((0x00038000&(data))>>15)
#define PLL_DCSB1_PLLDCSB_RS_shift                                                   (11)
#define PLL_DCSB1_PLLDCSB_RS_mask                                                    (0x00003800)
#define PLL_DCSB1_PLLDCSB_RS(data)                                                   (0x00003800&((data)<<11))
#define PLL_DCSB1_PLLDCSB_RS_src(data)                                               ((0x00003800&(data))>>11)
#define PLL_DCSB1_get_PLLDCSB_RS(data)                                               ((0x00003800&(data))>>11)
#define PLL_DCSB1_PLLDCSB_CS_shift                                                   (8)
#define PLL_DCSB1_PLLDCSB_CS_mask                                                    (0x00000300)
#define PLL_DCSB1_PLLDCSB_CS(data)                                                   (0x00000300&((data)<<8))
#define PLL_DCSB1_PLLDCSB_CS_src(data)                                               ((0x00000300&(data))>>8)
#define PLL_DCSB1_get_PLLDCSB_CS(data)                                               ((0x00000300&(data))>>8)
#define PLL_DCSB1_PLLDCSB_CP_shift                                                   (5)
#define PLL_DCSB1_PLLDCSB_CP_mask                                                    (0x00000060)
#define PLL_DCSB1_PLLDCSB_CP(data)                                                   (0x00000060&((data)<<5))
#define PLL_DCSB1_PLLDCSB_CP_src(data)                                               ((0x00000060&(data))>>5)
#define PLL_DCSB1_get_PLLDCSB_CP(data)                                               ((0x00000060&(data))>>5)
#define PLL_DCSB1_PLLDCSB_R3_shift                                                   (2)
#define PLL_DCSB1_PLLDCSB_R3_mask                                                    (0x0000001C)
#define PLL_DCSB1_PLLDCSB_R3(data)                                                   (0x0000001C&((data)<<2))
#define PLL_DCSB1_PLLDCSB_R3_src(data)                                               ((0x0000001C&(data))>>2)
#define PLL_DCSB1_get_PLLDCSB_R3(data)                                               ((0x0000001C&(data))>>2)
#define PLL_DCSB1_PLLDCSB_C3_shift                                                   (0)
#define PLL_DCSB1_PLLDCSB_C3_mask                                                    (0x00000003)
#define PLL_DCSB1_PLLDCSB_C3(data)                                                   (0x00000003&((data)<<0))
#define PLL_DCSB1_PLLDCSB_C3_src(data)                                               ((0x00000003&(data))>>0)
#define PLL_DCSB1_get_PLLDCSB_C3(data)                                               ((0x00000003&(data))>>0)


#define PLL_DCSB2                                                                    0x980001B4
#define PLL_DCSB2_reg_addr                                                           "0x980001B4"
#define PLL_DCSB2_reg                                                                0x980001B4
#define set_PLL_DCSB2_reg(data)   (*((volatile unsigned int*) PLL_DCSB2_reg)=data)
#define get_PLL_DCSB2_reg   (*((volatile unsigned int*) PLL_DCSB2_reg))
#define PLL_DCSB2_inst_adr                                                           "0x006D"
#define PLL_DCSB2_inst                                                               0x006D
#define PLL_DCSB2_write_en5_shift                                                    (18)
#define PLL_DCSB2_write_en5_mask                                                     (0x00040000)
#define PLL_DCSB2_write_en5(data)                                                    (0x00040000&((data)<<18))
#define PLL_DCSB2_write_en5_src(data)                                                ((0x00040000&(data))>>18)
#define PLL_DCSB2_get_write_en5(data)                                                ((0x00040000&(data))>>18)
#define PLL_DCSB2_PLLDCSB_PI_RL_shift                                                (16)
#define PLL_DCSB2_PLLDCSB_PI_RL_mask                                                 (0x00030000)
#define PLL_DCSB2_PLLDCSB_PI_RL(data)                                                (0x00030000&((data)<<16))
#define PLL_DCSB2_PLLDCSB_PI_RL_src(data)                                            ((0x00030000&(data))>>16)
#define PLL_DCSB2_get_PLLDCSB_PI_RL(data)                                            ((0x00030000&(data))>>16)
#define PLL_DCSB2_PLLDCSB_PI_RS_shift                                                (14)
#define PLL_DCSB2_PLLDCSB_PI_RS_mask                                                 (0x0000C000)
#define PLL_DCSB2_PLLDCSB_PI_RS(data)                                                (0x0000C000&((data)<<14))
#define PLL_DCSB2_PLLDCSB_PI_RS_src(data)                                            ((0x0000C000&(data))>>14)
#define PLL_DCSB2_get_PLLDCSB_PI_RS(data)                                            ((0x0000C000&(data))>>14)
#define PLL_DCSB2_PLLDCSB_PI_BIAS_shift                                              (12)
#define PLL_DCSB2_PLLDCSB_PI_BIAS_mask                                               (0x00003000)
#define PLL_DCSB2_PLLDCSB_PI_BIAS(data)                                              (0x00003000&((data)<<12))
#define PLL_DCSB2_PLLDCSB_PI_BIAS_src(data)                                          ((0x00003000&(data))>>12)
#define PLL_DCSB2_get_PLLDCSB_PI_BIAS(data)                                          ((0x00003000&(data))>>12)
#define PLL_DCSB2_write_en4_shift                                                    (11)
#define PLL_DCSB2_write_en4_mask                                                     (0x00000800)
#define PLL_DCSB2_write_en4(data)                                                    (0x00000800&((data)<<11))
#define PLL_DCSB2_write_en4_src(data)                                                ((0x00000800&(data))>>11)
#define PLL_DCSB2_get_write_en4(data)                                                ((0x00000800&(data))>>11)
#define PLL_DCSB2_PLLDCSB_WDMODE_shift                                               (9)
#define PLL_DCSB2_PLLDCSB_WDMODE_mask                                                (0x00000600)
#define PLL_DCSB2_PLLDCSB_WDMODE(data)                                               (0x00000600&((data)<<9))
#define PLL_DCSB2_PLLDCSB_WDMODE_src(data)                                           ((0x00000600&(data))>>9)
#define PLL_DCSB2_get_PLLDCSB_WDMODE(data)                                           ((0x00000600&(data))>>9)
#define PLL_DCSB2_write_en3_shift                                                    (6)
#define PLL_DCSB2_write_en3_mask                                                     (0x00000040)
#define PLL_DCSB2_write_en3(data)                                                    (0x00000040&((data)<<6))
#define PLL_DCSB2_write_en3_src(data)                                                ((0x00000040&(data))>>6)
#define PLL_DCSB2_get_write_en3(data)                                                ((0x00000040&(data))>>6)
#define PLL_DCSB2_PLLDCSB_FUPDN_shift                                                (5)
#define PLL_DCSB2_PLLDCSB_FUPDN_mask                                                 (0x00000020)
#define PLL_DCSB2_PLLDCSB_FUPDN(data)                                                (0x00000020&((data)<<5))
#define PLL_DCSB2_PLLDCSB_FUPDN_src(data)                                            ((0x00000020&(data))>>5)
#define PLL_DCSB2_get_PLLDCSB_FUPDN(data)                                            ((0x00000020&(data))>>5)
#define PLL_DCSB2_PLLDCSB_PSEN_shift                                                 (4)
#define PLL_DCSB2_PLLDCSB_PSEN_mask                                                  (0x00000010)
#define PLL_DCSB2_PLLDCSB_PSEN(data)                                                 (0x00000010&((data)<<4))
#define PLL_DCSB2_PLLDCSB_PSEN_src(data)                                             ((0x00000010&(data))>>4)
#define PLL_DCSB2_get_PLLDCSB_PSEN(data)                                             ((0x00000010&(data))>>4)
#define PLL_DCSB2_PLLDCSB_VCORB_shift                                                (3)
#define PLL_DCSB2_PLLDCSB_VCORB_mask                                                 (0x00000008)
#define PLL_DCSB2_PLLDCSB_VCORB(data)                                                (0x00000008&((data)<<3))
#define PLL_DCSB2_PLLDCSB_VCORB_src(data)                                            ((0x00000008&(data))>>3)
#define PLL_DCSB2_get_PLLDCSB_VCORB(data)                                            ((0x00000008&(data))>>3)
#define PLL_DCSB2_write_en1_shift                                                    (2)
#define PLL_DCSB2_write_en1_mask                                                     (0x00000004)
#define PLL_DCSB2_write_en1(data)                                                    (0x00000004&((data)<<2))
#define PLL_DCSB2_write_en1_src(data)                                                ((0x00000004&(data))>>2)
#define PLL_DCSB2_get_write_en1(data)                                                ((0x00000004&(data))>>2)
#define PLL_DCSB2_PLLDCSB_TST_shift                                                  (1)
#define PLL_DCSB2_PLLDCSB_TST_mask                                                   (0x00000002)
#define PLL_DCSB2_PLLDCSB_TST(data)                                                  (0x00000002&((data)<<1))
#define PLL_DCSB2_PLLDCSB_TST_src(data)                                              ((0x00000002&(data))>>1)
#define PLL_DCSB2_get_PLLDCSB_TST(data)                                              ((0x00000002&(data))>>1)
#define PLL_DCSB2_PLLDCSB_PSTST_shift                                                (0)
#define PLL_DCSB2_PLLDCSB_PSTST_mask                                                 (0x00000001)
#define PLL_DCSB2_PLLDCSB_PSTST(data)                                                (0x00000001&((data)<<0))
#define PLL_DCSB2_PLLDCSB_PSTST_src(data)                                            ((0x00000001&(data))>>0)
#define PLL_DCSB2_get_PLLDCSB_PSTST(data)                                            ((0x00000001&(data))>>0)


#define PLL_DCSB3                                                                    0x980001B8
#define PLL_DCSB3_reg_addr                                                           "0x980001B8"
#define PLL_DCSB3_reg                                                                0x980001B8
#define set_PLL_DCSB3_reg(data)   (*((volatile unsigned int*) PLL_DCSB3_reg)=data)
#define get_PLL_DCSB3_reg   (*((volatile unsigned int*) PLL_DCSB3_reg))
#define PLL_DCSB3_inst_adr                                                           "0x006E"
#define PLL_DCSB3_inst                                                               0x006E
#define PLL_DCSB3_REG_PLLDCSB_O_shift                                                (3)
#define PLL_DCSB3_REG_PLLDCSB_O_mask                                                 (0x00000018)
#define PLL_DCSB3_REG_PLLDCSB_O(data)                                                (0x00000018&((data)<<3))
#define PLL_DCSB3_REG_PLLDCSB_O_src(data)                                            ((0x00000018&(data))>>3)
#define PLL_DCSB3_get_REG_PLLDCSB_O(data)                                            ((0x00000018&(data))>>3)
#define PLL_DCSB3_PLLDCSB_OEB_shift                                                  (2)
#define PLL_DCSB3_PLLDCSB_OEB_mask                                                   (0x00000004)
#define PLL_DCSB3_PLLDCSB_OEB(data)                                                  (0x00000004&((data)<<2))
#define PLL_DCSB3_PLLDCSB_OEB_src(data)                                              ((0x00000004&(data))>>2)
#define PLL_DCSB3_get_PLLDCSB_OEB(data)                                              ((0x00000004&(data))>>2)
#define PLL_DCSB3_PLLDCSB_RSTB_shift                                                 (1)
#define PLL_DCSB3_PLLDCSB_RSTB_mask                                                  (0x00000002)
#define PLL_DCSB3_PLLDCSB_RSTB(data)                                                 (0x00000002&((data)<<1))
#define PLL_DCSB3_PLLDCSB_RSTB_src(data)                                             ((0x00000002&(data))>>1)
#define PLL_DCSB3_get_PLLDCSB_RSTB(data)                                             ((0x00000002&(data))>>1)
#define PLL_DCSB3_PLLDCSB_POW_shift                                                  (0)
#define PLL_DCSB3_PLLDCSB_POW_mask                                                   (0x00000001)
#define PLL_DCSB3_PLLDCSB_POW(data)                                                  (0x00000001&((data)<<0))
#define PLL_DCSB3_PLLDCSB_POW_src(data)                                              ((0x00000001&(data))>>0)
#define PLL_DCSB3_get_PLLDCSB_POW(data)                                              ((0x00000001&(data))>>0)


#define PLL_GPU1                                                                     0x980001C0
#define PLL_GPU1_reg_addr                                                            "0x980001C0"
#define PLL_GPU1_reg                                                                 0x980001C0
#define set_PLL_GPU1_reg(data)   (*((volatile unsigned int*) PLL_GPU1_reg)=data)
#define get_PLL_GPU1_reg   (*((volatile unsigned int*) PLL_GPU1_reg))
#define PLL_GPU1_inst_adr                                                            "0x0070"
#define PLL_GPU1_inst                                                                0x0070
#define PLL_GPU1_REG_PLLGPU_WDRST_shift                                              (29)
#define PLL_GPU1_REG_PLLGPU_WDRST_mask                                               (0x20000000)
#define PLL_GPU1_REG_PLLGPU_WDRST(data)                                              (0x20000000&((data)<<29))
#define PLL_GPU1_REG_PLLGPU_WDRST_src(data)                                          ((0x20000000&(data))>>29)
#define PLL_GPU1_get_REG_PLLGPU_WDRST(data)                                          ((0x20000000&(data))>>29)
#define PLL_GPU1_REG_PLLGPU_WDSET_shift                                              (28)
#define PLL_GPU1_REG_PLLGPU_WDSET_mask                                               (0x10000000)
#define PLL_GPU1_REG_PLLGPU_WDSET(data)                                              (0x10000000&((data)<<28))
#define PLL_GPU1_REG_PLLGPU_WDSET_src(data)                                          ((0x10000000&(data))>>28)
#define PLL_GPU1_get_REG_PLLGPU_WDSET(data)                                          ((0x10000000&(data))>>28)
#define PLL_GPU1_REG_PLLGPU_CS_shift                                                 (26)
#define PLL_GPU1_REG_PLLGPU_CS_mask                                                  (0x0C000000)
#define PLL_GPU1_REG_PLLGPU_CS(data)                                                 (0x0C000000&((data)<<26))
#define PLL_GPU1_REG_PLLGPU_CS_src(data)                                             ((0x0C000000&(data))>>26)
#define PLL_GPU1_get_REG_PLLGPU_CS(data)                                             ((0x0C000000&(data))>>26)
#define PLL_GPU1_REG_PLLGPU_O_shift                                                  (24)
#define PLL_GPU1_REG_PLLGPU_O_mask                                                   (0x03000000)
#define PLL_GPU1_REG_PLLGPU_O(data)                                                  (0x03000000&((data)<<24))
#define PLL_GPU1_REG_PLLGPU_O_src(data)                                              ((0x03000000&(data))>>24)
#define PLL_GPU1_get_REG_PLLGPU_O(data)                                              ((0x03000000&(data))>>24)
#define PLL_GPU1_REG_PLLGPU_RS_shift                                                 (21)
#define PLL_GPU1_REG_PLLGPU_RS_mask                                                  (0x00E00000)
#define PLL_GPU1_REG_PLLGPU_RS(data)                                                 (0x00E00000&((data)<<21))
#define PLL_GPU1_REG_PLLGPU_RS_src(data)                                             ((0x00E00000&(data))>>21)
#define PLL_GPU1_get_REG_PLLGPU_RS(data)                                             ((0x00E00000&(data))>>21)
#define PLL_GPU1_PLLGPU_N_shift                                                      (18)
#define PLL_GPU1_PLLGPU_N_mask                                                       (0x000C0000)
#define PLL_GPU1_PLLGPU_N(data)                                                      (0x000C0000&((data)<<18))
#define PLL_GPU1_PLLGPU_N_src(data)                                                  ((0x000C0000&(data))>>18)
#define PLL_GPU1_get_PLLGPU_N(data)                                                  ((0x000C0000&(data))>>18)
#define PLL_GPU1_PLLGPU_M_shift                                                      (11)
#define PLL_GPU1_PLLGPU_M_mask                                                       (0x0003F800)
#define PLL_GPU1_PLLGPU_M(data)                                                      (0x0003F800&((data)<<11))
#define PLL_GPU1_PLLGPU_M_src(data)                                                  ((0x0003F800&(data))>>11)
#define PLL_GPU1_get_PLLGPU_M(data)                                                  ((0x0003F800&(data))>>11)
#define PLL_GPU1_PLLGPU_IP_shift                                                     (8)
#define PLL_GPU1_PLLGPU_IP_mask                                                      (0x00000700)
#define PLL_GPU1_PLLGPU_IP(data)                                                     (0x00000700&((data)<<8))
#define PLL_GPU1_PLLGPU_IP_src(data)                                                 ((0x00000700&(data))>>8)
#define PLL_GPU1_get_PLLGPU_IP(data)                                                 ((0x00000700&(data))>>8)
#define PLL_GPU1_PLLGPU_TST_shift                                                    (0)
#define PLL_GPU1_PLLGPU_TST_mask                                                     (0x00000001)
#define PLL_GPU1_PLLGPU_TST(data)                                                    (0x00000001&((data)<<0))
#define PLL_GPU1_PLLGPU_TST_src(data)                                                ((0x00000001&(data))>>0)
#define PLL_GPU1_get_PLLGPU_TST(data)                                                ((0x00000001&(data))>>0)


#define PLL_GPU2                                                                     0x980001C4
#define PLL_GPU2_reg_addr                                                            "0x980001C4"
#define PLL_GPU2_reg                                                                 0x980001C4
#define set_PLL_GPU2_reg(data)   (*((volatile unsigned int*) PLL_GPU2_reg)=data)
#define get_PLL_GPU2_reg   (*((volatile unsigned int*) PLL_GPU2_reg))
#define PLL_GPU2_inst_adr                                                            "0x0071"
#define PLL_GPU2_inst                                                                0x0071
#define PLL_GPU2_PLLGPU_OEB_shift                                                    (2)
#define PLL_GPU2_PLLGPU_OEB_mask                                                     (0x00000004)
#define PLL_GPU2_PLLGPU_OEB(data)                                                    (0x00000004&((data)<<2))
#define PLL_GPU2_PLLGPU_OEB_src(data)                                                ((0x00000004&(data))>>2)
#define PLL_GPU2_get_PLLGPU_OEB(data)                                                ((0x00000004&(data))>>2)
#define PLL_GPU2_PLLGPU_RSTB_shift                                                   (1)
#define PLL_GPU2_PLLGPU_RSTB_mask                                                    (0x00000002)
#define PLL_GPU2_PLLGPU_RSTB(data)                                                   (0x00000002&((data)<<1))
#define PLL_GPU2_PLLGPU_RSTB_src(data)                                               ((0x00000002&(data))>>1)
#define PLL_GPU2_get_PLLGPU_RSTB(data)                                               ((0x00000002&(data))>>1)
#define PLL_GPU2_PLLGPU_POW_shift                                                    (0)
#define PLL_GPU2_PLLGPU_POW_mask                                                     (0x00000001)
#define PLL_GPU2_PLLGPU_POW(data)                                                    (0x00000001&((data)<<0))
#define PLL_GPU2_PLLGPU_POW_src(data)                                                ((0x00000001&(data))>>0)
#define PLL_GPU2_get_PLLGPU_POW(data)                                                ((0x00000001&(data))>>0)


#define PLL_VCPU2                                                                    0x980001D0
#define PLL_VCPU2_reg_addr                                                           "0x980001D0"
#define PLL_VCPU2_reg                                                                0x980001D0
#define set_PLL_VCPU2_reg(data)   (*((volatile unsigned int*) PLL_VCPU2_reg)=data)
#define get_PLL_VCPU2_reg   (*((volatile unsigned int*) PLL_VCPU2_reg))
#define PLL_VCPU2_inst_adr                                                           "0x0045"
#define PLL_VCPU2_inst                                                               0x0045
#define PLL_VCPU2_REG_PLLVCPU_WDRST_shift                                            (22)
#define PLL_VCPU2_REG_PLLVCPU_WDRST_mask                                             (0x00400000)
#define PLL_VCPU2_REG_PLLVCPU_WDRST(data)                                            (0x00400000&((data)<<22))
#define PLL_VCPU2_REG_PLLVCPU_WDRST_src(data)                                        ((0x00400000&(data))>>22)
#define PLL_VCPU2_get_REG_PLLVCPU_WDRST(data)                                        ((0x00400000&(data))>>22)
#define PLL_VCPU2_REG_PLLVCPU_WDSET_shift                                            (21)
#define PLL_VCPU2_REG_PLLVCPU_WDSET_mask                                             (0x00200000)
#define PLL_VCPU2_REG_PLLVCPU_WDSET(data)                                            (0x00200000&((data)<<21))
#define PLL_VCPU2_REG_PLLVCPU_WDSET_src(data)                                        ((0x00200000&(data))>>21)
#define PLL_VCPU2_get_REG_PLLVCPU_WDSET(data)                                        ((0x00200000&(data))>>21)
#define PLL_VCPU2_REG_PLLVCPU_CS_shift                                               (19)
#define PLL_VCPU2_REG_PLLVCPU_CS_mask                                                (0x00180000)
#define PLL_VCPU2_REG_PLLVCPU_CS(data)                                               (0x00180000&((data)<<19))
#define PLL_VCPU2_REG_PLLVCPU_CS_src(data)                                           ((0x00180000&(data))>>19)
#define PLL_VCPU2_get_REG_PLLVCPU_CS(data)                                           ((0x00180000&(data))>>19)
#define PLL_VCPU2_REG_PLLVCPU_O_shift                                                (17)
#define PLL_VCPU2_REG_PLLVCPU_O_mask                                                 (0x00060000)
#define PLL_VCPU2_REG_PLLVCPU_O(data)                                                (0x00060000&((data)<<17))
#define PLL_VCPU2_REG_PLLVCPU_O_src(data)                                            ((0x00060000&(data))>>17)
#define PLL_VCPU2_get_REG_PLLVCPU_O(data)                                            ((0x00060000&(data))>>17)
#define PLL_VCPU2_REG_PLLVCPU_RS_shift                                               (14)
#define PLL_VCPU2_REG_PLLVCPU_RS_mask                                                (0x0001C000)
#define PLL_VCPU2_REG_PLLVCPU_RS(data)                                               (0x0001C000&((data)<<14))
#define PLL_VCPU2_REG_PLLVCPU_RS_src(data)                                           ((0x0001C000&(data))>>14)
#define PLL_VCPU2_get_REG_PLLVCPU_RS(data)                                           ((0x0001C000&(data))>>14)
#define PLL_VCPU2_PLLVCPU_N_shift                                                    (12)
#define PLL_VCPU2_PLLVCPU_N_mask                                                     (0x00003000)
#define PLL_VCPU2_PLLVCPU_N(data)                                                    (0x00003000&((data)<<12))
#define PLL_VCPU2_PLLVCPU_N_src(data)                                                ((0x00003000&(data))>>12)
#define PLL_VCPU2_get_PLLVCPU_N(data)                                                ((0x00003000&(data))>>12)
#define PLL_VCPU2_PLLVCPU_M_shift                                                    (4)
#define PLL_VCPU2_PLLVCPU_M_mask                                                     (0x00000FF0)
#define PLL_VCPU2_PLLVCPU_M(data)                                                    (0x00000FF0&((data)<<4))
#define PLL_VCPU2_PLLVCPU_M_src(data)                                                ((0x00000FF0&(data))>>4)
#define PLL_VCPU2_get_PLLVCPU_M(data)                                                ((0x00000FF0&(data))>>4)
#define PLL_VCPU2_PLLVCPU_IP_shift                                                   (1)
#define PLL_VCPU2_PLLVCPU_IP_mask                                                    (0x000000E0)
#define PLL_VCPU2_PLLVCPU_IP(data)                                                   (0x000000E0&((data)<<1))
#define PLL_VCPU2_PLLVCPU_IP_src(data)                                               ((0x000000E0&(data))>>1)
#define PLL_VCPU2_get_PLLVCPU_IP(data)                                               ((0x000000E0&(data))>>1)
#define PLL_VCPU2_PLLVCPU_TST_shift                                                  (0)
#define PLL_VCPU2_PLLVCPU_TST_mask                                                   (0x00000001)
#define PLL_VCPU2_PLLVCPU_TST(data)                                                  (0x00000001&((data)<<0))
#define PLL_VCPU2_PLLVCPU_TST_src(data)                                              ((0x00000001&(data))>>0)
#define PLL_VCPU2_get_PLLVCPU_TST(data)                                              ((0x00000001&(data))>>0)


#define PLL_LVDS1                                                                    0x980001D0
#define PLL_LVDS1_reg_addr                                                           "0x980001D0"
#define PLL_LVDS1_reg                                                                0x980001D0
#define set_PLL_LVDS1_reg(data)   (*((volatile unsigned int*) PLL_LVDS1_reg)=data)
#define get_PLL_LVDS1_reg   (*((volatile unsigned int*) PLL_LVDS1_reg))
#define PLL_LVDS1_inst_adr                                                           "0x0074"
#define PLL_LVDS1_inst                                                               0x0074
#define PLL_LVDS1_REG_PLLLVDS_BPN_shift                                              (31)
#define PLL_LVDS1_REG_PLLLVDS_BPN_mask                                               (0x80000000)
#define PLL_LVDS1_REG_PLLLVDS_BPN(data)                                              (0x80000000&((data)<<31))
#define PLL_LVDS1_REG_PLLLVDS_BPN_src(data)                                          ((0x80000000&(data))>>31)
#define PLL_LVDS1_get_REG_PLLLVDS_BPN(data)                                          ((0x80000000&(data))>>31)
#define PLL_LVDS1_REG_PLLLVDS_BPPHS_shift                                            (30)
#define PLL_LVDS1_REG_PLLLVDS_BPPHS_mask                                             (0x40000000)
#define PLL_LVDS1_REG_PLLLVDS_BPPHS(data)                                            (0x40000000&((data)<<30))
#define PLL_LVDS1_REG_PLLLVDS_BPPHS_src(data)                                        ((0x40000000&(data))>>30)
#define PLL_LVDS1_get_REG_PLLLVDS_BPPHS(data)                                        ((0x40000000&(data))>>30)
#define PLL_LVDS1_REG_PLLLVDS_FREEZE_shift                                           (29)
#define PLL_LVDS1_REG_PLLLVDS_FREEZE_mask                                            (0x20000000)
#define PLL_LVDS1_REG_PLLLVDS_FREEZE(data)                                           (0x20000000&((data)<<29))
#define PLL_LVDS1_REG_PLLLVDS_FREEZE_src(data)                                       ((0x20000000&(data))>>29)
#define PLL_LVDS1_get_REG_PLLLVDS_FREEZE(data)                                       ((0x20000000&(data))>>29)
#define PLL_LVDS1_REG_PLLLVDS_FUPDN_shift                                            (28)
#define PLL_LVDS1_REG_PLLLVDS_FUPDN_mask                                             (0x10000000)
#define PLL_LVDS1_REG_PLLLVDS_FUPDN(data)                                            (0x10000000&((data)<<28))
#define PLL_LVDS1_REG_PLLLVDS_FUPDN_src(data)                                        ((0x10000000&(data))>>28)
#define PLL_LVDS1_get_REG_PLLLVDS_FUPDN(data)                                        ((0x10000000&(data))>>28)
#define PLL_LVDS1_REG_PLLLVDS_POW_shift                                              (27)
#define PLL_LVDS1_REG_PLLLVDS_POW_mask                                               (0x08000000)
#define PLL_LVDS1_REG_PLLLVDS_POW(data)                                              (0x08000000&((data)<<27))
#define PLL_LVDS1_REG_PLLLVDS_POW_src(data)                                          ((0x08000000&(data))>>27)
#define PLL_LVDS1_get_REG_PLLLVDS_POW(data)                                          ((0x08000000&(data))>>27)
#define PLL_LVDS1_REG_PLLLVDS_RESERVE_shift                                          (26)
#define PLL_LVDS1_REG_PLLLVDS_RESERVE_mask                                           (0x04000000)
#define PLL_LVDS1_REG_PLLLVDS_RESERVE(data)                                          (0x04000000&((data)<<26))
#define PLL_LVDS1_REG_PLLLVDS_RESERVE_src(data)                                      ((0x04000000&(data))>>26)
#define PLL_LVDS1_get_REG_PLLLVDS_RESERVE(data)                                      ((0x04000000&(data))>>26)
#define PLL_LVDS1_REG_PLLLVDS_RSTB_shift                                             (25)
#define PLL_LVDS1_REG_PLLLVDS_RSTB_mask                                              (0x02000000)
#define PLL_LVDS1_REG_PLLLVDS_RSTB(data)                                             (0x02000000&((data)<<25))
#define PLL_LVDS1_REG_PLLLVDS_RSTB_src(data)                                         ((0x02000000&(data))>>25)
#define PLL_LVDS1_get_REG_PLLLVDS_RSTB(data)                                         ((0x02000000&(data))>>25)
#define PLL_LVDS1_REG_PLLLVDS_STOP_shift                                             (24)
#define PLL_LVDS1_REG_PLLLVDS_STOP_mask                                              (0x01000000)
#define PLL_LVDS1_REG_PLLLVDS_STOP(data)                                             (0x01000000&((data)<<24))
#define PLL_LVDS1_REG_PLLLVDS_STOP_src(data)                                         ((0x01000000&(data))>>24)
#define PLL_LVDS1_get_REG_PLLLVDS_STOP(data)                                         ((0x01000000&(data))>>24)
#define PLL_LVDS1_REG_PLLLVDS_VCORSTB_shift                                          (23)
#define PLL_LVDS1_REG_PLLLVDS_VCORSTB_mask                                           (0x00800000)
#define PLL_LVDS1_REG_PLLLVDS_VCORSTB(data)                                          (0x00800000&((data)<<23))
#define PLL_LVDS1_REG_PLLLVDS_VCORSTB_src(data)                                      ((0x00800000&(data))>>23)
#define PLL_LVDS1_get_REG_PLLLVDS_VCORSTB(data)                                      ((0x00800000&(data))>>23)
#define PLL_LVDS1_REG_PLLLVDS_WDRST_shift                                            (22)
#define PLL_LVDS1_REG_PLLLVDS_WDRST_mask                                             (0x00400000)
#define PLL_LVDS1_REG_PLLLVDS_WDRST(data)                                            (0x00400000&((data)<<22))
#define PLL_LVDS1_REG_PLLLVDS_WDRST_src(data)                                        ((0x00400000&(data))>>22)
#define PLL_LVDS1_get_REG_PLLLVDS_WDRST(data)                                        ((0x00400000&(data))>>22)
#define PLL_LVDS1_REG_PLLLVDS_WDSET_shift                                            (21)
#define PLL_LVDS1_REG_PLLLVDS_WDSET_mask                                             (0x00200000)
#define PLL_LVDS1_REG_PLLLVDS_WDSET(data)                                            (0x00200000&((data)<<21))
#define PLL_LVDS1_REG_PLLLVDS_WDSET_src(data)                                        ((0x00200000&(data))>>21)
#define PLL_LVDS1_get_REG_PLLLVDS_WDSET(data)                                        ((0x00200000&(data))>>21)
#define PLL_LVDS1_REG_PLLLVDS_CP_shift                                               (19)
#define PLL_LVDS1_REG_PLLLVDS_CP_mask                                                (0x00180000)
#define PLL_LVDS1_REG_PLLLVDS_CP(data)                                               (0x00180000&((data)<<19))
#define PLL_LVDS1_REG_PLLLVDS_CP_src(data)                                           ((0x00180000&(data))>>19)
#define PLL_LVDS1_get_REG_PLLLVDS_CP(data)                                           ((0x00180000&(data))>>19)
#define PLL_LVDS1_REG_PLLLVDS_CS_shift                                               (17)
#define PLL_LVDS1_REG_PLLLVDS_CS_mask                                                (0x00060000)
#define PLL_LVDS1_REG_PLLLVDS_CS(data)                                               (0x00060000&((data)<<17))
#define PLL_LVDS1_REG_PLLLVDS_CS_src(data)                                           ((0x00060000&(data))>>17)
#define PLL_LVDS1_get_REG_PLLLVDS_CS(data)                                           ((0x00060000&(data))>>17)
#define PLL_LVDS1_REG_PLLLVDS_O_shift                                                (15)
#define PLL_LVDS1_REG_PLLLVDS_O_mask                                                 (0x00018000)
#define PLL_LVDS1_REG_PLLLVDS_O(data)                                                (0x00018000&((data)<<15))
#define PLL_LVDS1_REG_PLLLVDS_O_src(data)                                            ((0x00018000&(data))>>15)
#define PLL_LVDS1_get_REG_PLLLVDS_O(data)                                            ((0x00018000&(data))>>15)
#define PLL_LVDS1_REG_PLLLVDS_IP_shift                                               (12)
#define PLL_LVDS1_REG_PLLLVDS_IP_mask                                                (0x00007000)
#define PLL_LVDS1_REG_PLLLVDS_IP(data)                                               (0x00007000&((data)<<12))
#define PLL_LVDS1_REG_PLLLVDS_IP_src(data)                                           ((0x00007000&(data))>>12)
#define PLL_LVDS1_get_REG_PLLLVDS_IP(data)                                           ((0x00007000&(data))>>12)
#define PLL_LVDS1_REG_PLLLVDS_RS_shift                                               (9)
#define PLL_LVDS1_REG_PLLLVDS_RS_mask                                                (0x00000E00)
#define PLL_LVDS1_REG_PLLLVDS_RS(data)                                               (0x00000E00&((data)<<9))
#define PLL_LVDS1_REG_PLLLVDS_RS_src(data)                                           ((0x00000E00&(data))>>9)
#define PLL_LVDS1_get_REG_PLLLVDS_RS(data)                                           ((0x00000E00&(data))>>9)
#define PLL_LVDS1_PLLLVDS_RESER_shift                                                (1)
#define PLL_LVDS1_PLLLVDS_RESER_mask                                                 (0x00000002)
#define PLL_LVDS1_PLLLVDS_RESER(data)                                                (0x00000002&((data)<<1))
#define PLL_LVDS1_PLLLVDS_RESER_src(data)                                            ((0x00000002&(data))>>1)
#define PLL_LVDS1_get_PLLLVDS_RESER(data)                                            ((0x00000002&(data))>>1)
#define PLL_LVDS1_REG_PLLLVDS_TST_shift                                              (0)
#define PLL_LVDS1_REG_PLLLVDS_TST_mask                                               (0x00000001)
#define PLL_LVDS1_REG_PLLLVDS_TST(data)                                              (0x00000001&((data)<<0))
#define PLL_LVDS1_REG_PLLLVDS_TST_src(data)                                          ((0x00000001&(data))>>0)
#define PLL_LVDS1_get_REG_PLLLVDS_TST(data)                                          ((0x00000001&(data))>>0)


#define PLL_LVDS2                                                                    0x980001D4
#define PLL_LVDS2_reg_addr                                                           "0x980001D4"
#define PLL_LVDS2_reg                                                                0x980001D4
#define set_PLL_LVDS2_reg(data)   (*((volatile unsigned int*) PLL_LVDS2_reg)=data)
#define get_PLL_LVDS2_reg   (*((volatile unsigned int*) PLL_LVDS2_reg))
#define PLL_LVDS2_inst_adr                                                           "0x0075"
#define PLL_LVDS2_inst                                                               0x0075
#define PLL_LVDS2_REG_PLLLVDS_M_shift                                                (3)
#define PLL_LVDS2_REG_PLLLVDS_M_mask                                                 (0x000007F8)
#define PLL_LVDS2_REG_PLLLVDS_M(data)                                                (0x000007F8&((data)<<3))
#define PLL_LVDS2_REG_PLLLVDS_M_src(data)                                            ((0x000007F8&(data))>>3)
#define PLL_LVDS2_get_REG_PLLLVDS_M(data)                                            ((0x000007F8&(data))>>3)
#define PLL_LVDS2_REG_PLLLVDS_N_shift                                                (0)
#define PLL_LVDS2_REG_PLLLVDS_N_mask                                                 (0x00000007)
#define PLL_LVDS2_REG_PLLLVDS_N(data)                                                (0x00000007&((data)<<0))
#define PLL_LVDS2_REG_PLLLVDS_N_src(data)                                            ((0x00000007&(data))>>0)
#define PLL_LVDS2_get_REG_PLLLVDS_N(data)                                            ((0x00000007&(data))>>0)


#define PLL_DDR6                                                                     0x980001DC
#define PLL_DDR6_reg_addr                                                            "0x980001DC"
#define PLL_DDR6_reg                                                                 0x980001DC
#define set_PLL_DDR6_reg(data)   (*((volatile unsigned int*) PLL_DDR6_reg)=data)
#define get_PLL_DDR6_reg   (*((volatile unsigned int*) PLL_DDR6_reg))
#define PLL_DDR6_inst_adr                                                            "0x0077"
#define PLL_DDR6_inst                                                                0x0077
#define PLL_DDR6_PLLDDR_PLL_STABLE_shift                                             (1)
#define PLL_DDR6_PLLDDR_PLL_STABLE_mask                                              (0x00000002)
#define PLL_DDR6_PLLDDR_PLL_STABLE(data)                                             (0x00000002&((data)<<1))
#define PLL_DDR6_PLLDDR_PLL_STABLE_src(data)                                         ((0x00000002&(data))>>1)
#define PLL_DDR6_get_PLLDDR_PLL_STABLE(data)                                         ((0x00000002&(data))>>1)
#define PLL_DDR6_POWDET_DDR_shift                                                    (0)
#define PLL_DDR6_POWDET_DDR_mask                                                     (0x00000001)
#define PLL_DDR6_POWDET_DDR(data)                                                    (0x00000001&((data)<<0))
#define PLL_DDR6_POWDET_DDR_src(data)                                                ((0x00000001&(data))>>0)
#define PLL_DDR6_get_POWDET_DDR(data)                                                ((0x00000001&(data))>>0)


#define PLL_OTHER                                                                    0x98000200
#define PLL_OTHER_reg_addr                                                           "0x98000200"
#define PLL_OTHER_reg                                                                0x98000200
#define set_PLL_OTHER_reg(data)   (*((volatile unsigned int*) PLL_OTHER_reg)=data)
#define get_PLL_OTHER_reg   (*((volatile unsigned int*) PLL_OTHER_reg))
#define PLL_OTHER_inst_adr                                                           "0x0080"
#define PLL_OTHER_inst                                                               0x0080
#define PLL_OTHER_POR_VSET_shift                                                     (12)
#define PLL_OTHER_POR_VSET_mask                                                      (0x00001000)
#define PLL_OTHER_POR_VSET(data)                                                     (0x00001000&((data)<<12))
#define PLL_OTHER_POR_VSET_src(data)                                                 ((0x00001000&(data))>>12)
#define PLL_OTHER_get_POR_VSET(data)                                                 ((0x00001000&(data))>>12)
#define PLL_OTHER_REG_PLLDDSB_SEL_shift                                              (11)
#define PLL_OTHER_REG_PLLDDSB_SEL_mask                                               (0x00000800)
#define PLL_OTHER_REG_PLLDDSB_SEL(data)                                              (0x00000800&((data)<<11))
#define PLL_OTHER_REG_PLLDDSB_SEL_src(data)                                          ((0x00000800&(data))>>11)
#define PLL_OTHER_get_REG_PLLDDSB_SEL(data)                                          ((0x00000800&(data))>>11)
#define PLL_OTHER_PLLDISP_SEL_shift                                                  (9)
#define PLL_OTHER_PLLDISP_SEL_mask                                                   (0x00000600)
#define PLL_OTHER_PLLDISP_SEL(data)                                                  (0x00000600&((data)<<9))
#define PLL_OTHER_PLLDISP_SEL_src(data)                                              ((0x00000600&(data))>>9)
#define PLL_OTHER_get_PLLDISP_SEL(data)                                              ((0x00000600&(data))>>9)
#define PLL_OTHER_PLLHDMI_SEL_shift                                                  (7)
#define PLL_OTHER_PLLHDMI_SEL_mask                                                   (0x00000180)
#define PLL_OTHER_PLLHDMI_SEL(data)                                                  (0x00000180&((data)<<7))
#define PLL_OTHER_PLLHDMI_SEL_src(data)                                              ((0x00000180&(data))>>7)
#define PLL_OTHER_get_PLLHDMI_SEL(data)                                              ((0x00000180&(data))>>7)
#define PLL_OTHER_PLLTST_SEL_shift                                                   (3)
#define PLL_OTHER_PLLTST_SEL_mask                                                    (0x00000078)
#define PLL_OTHER_PLLTST_SEL(data)                                                   (0x00000078&((data)<<3))
#define PLL_OTHER_PLLTST_SEL_src(data)                                               ((0x00000078&(data))>>3)
#define PLL_OTHER_get_PLLTST_SEL(data)                                               ((0x00000078&(data))>>3)
#define PLL_OTHER_PLLTST_DIV_shift                                                   (0)
#define PLL_OTHER_PLLTST_DIV_mask                                                    (0x00000007)
#define PLL_OTHER_PLLTST_DIV(data)                                                   (0x00000007&((data)<<0))
#define PLL_OTHER_PLLTST_DIV_src(data)                                               ((0x00000007&(data))>>0)
#define PLL_OTHER_get_PLLTST_DIV(data)                                               ((0x00000007&(data))>>0)


#define PLL_SD1                                                                      0x980001E0
#define PLL_SD1_reg_addr                                                             "0x980001E0"
#define PLL_SD1_reg                                                                  0x980001E0
#define set_PLL_SD1_reg(data)   (*((volatile unsigned int*) PLL_SD1_reg)=data)
#define get_PLL_SD1_reg   (*((volatile unsigned int*) PLL_SD1_reg))
#define PLL_SD1_inst_adr                                                             "0x0078"
#define PLL_SD1_inst                                                                 0x0078
#define PLL_SD1_reg_tuned3318_shift                                                  (19)
#define PLL_SD1_reg_tuned3318_mask                                                   (0x00380000)
#define PLL_SD1_reg_tuned3318(data)                                                  (0x00380000&((data)<<19))
#define PLL_SD1_reg_tuned3318_src(data)                                              ((0x00380000&(data))>>19)
#define PLL_SD1_get_reg_tuned3318(data)                                              ((0x00380000&(data))>>19)
#define PLL_SD1_reg_d3318pow_shift                                                   (17)
#define PLL_SD1_reg_d3318pow_mask                                                    (0x00060000)
#define PLL_SD1_reg_d3318pow(data)                                                   (0x00060000&((data)<<17))
#define PLL_SD1_reg_d3318pow_src(data)                                               ((0x00060000&(data))>>17)
#define PLL_SD1_get_reg_d3318pow(data)                                               ((0x00060000&(data))>>17)
#define PLL_SD1_regpd_d3318_shift                                                    (16)
#define PLL_SD1_regpd_d3318_mask                                                     (0x00010000)
#define PLL_SD1_regpd_d3318(data)                                                    (0x00010000&((data)<<16))
#define PLL_SD1_regpd_d3318_src(data)                                                ((0x00010000&(data))>>16)
#define PLL_SD1_get_regpd_d3318(data)                                                ((0x00010000&(data))>>16)
#define PLL_SD1_phsel1_shift                                                         (8)
#define PLL_SD1_phsel1_mask                                                          (0x00001F00)
#define PLL_SD1_phsel1(data)                                                         (0x00001F00&((data)<<8))
#define PLL_SD1_phsel1_src(data)                                                     ((0x00001F00&(data))>>8)
#define PLL_SD1_get_phsel1(data)                                                     ((0x00001F00&(data))>>8)
#define PLL_SD1_phsel0_shift                                                         (3)
#define PLL_SD1_phsel0_mask                                                          (0x000000F8)
#define PLL_SD1_phsel0(data)                                                         (0x000000F8&((data)<<3))
#define PLL_SD1_phsel0_src(data)                                                     ((0x000000F8&(data))>>3)
#define PLL_SD1_get_phsel0(data)                                                     ((0x000000F8&(data))>>3)
#define PLL_SD1_phrstb_dly_sel_shift                                                 (2)
#define PLL_SD1_phrstb_dly_sel_mask                                                  (0x00000004)
#define PLL_SD1_phrstb_dly_sel(data)                                                 (0x00000004&((data)<<2))
#define PLL_SD1_phrstb_dly_sel_src(data)                                             ((0x00000004&(data))>>2)
#define PLL_SD1_get_phrstb_dly_sel(data)                                             ((0x00000004&(data))>>2)
#define PLL_SD1_phrt0_shift                                                          (1)
#define PLL_SD1_phrt0_mask                                                           (0x00000002)
#define PLL_SD1_phrt0(data)                                                          (0x00000002&((data)<<1))
#define PLL_SD1_phrt0_src(data)                                                      ((0x00000002&(data))>>1)
#define PLL_SD1_get_phrt0(data)                                                      ((0x00000002&(data))>>1)
#define PLL_SD1_bias_en_shift                                                        (0)
#define PLL_SD1_bias_en_mask                                                         (0x00000001)
#define PLL_SD1_bias_en(data)                                                        (0x00000001&((data)<<0))
#define PLL_SD1_bias_en_src(data)                                                    ((0x00000001&(data))>>0)
#define PLL_SD1_get_bias_en(data)                                                    ((0x00000001&(data))>>0)


#define PLL_SD2                                                                      0x980001E4
#define PLL_SD2_reg_addr                                                             "0x980001E4"
#define PLL_SD2_reg                                                                  0x980001E4
#define set_PLL_SD2_reg(data)   (*((volatile unsigned int*) PLL_SD2_reg)=data)
#define get_PLL_SD2_reg   (*((volatile unsigned int*) PLL_SD2_reg))
#define PLL_SD2_inst_adr                                                             "0x0079"
#define PLL_SD2_inst                                                                 0x0079
#define PLL_SD2_en_cpnew_shift                                                       (26)
#define PLL_SD2_en_cpnew_mask                                                        (0x04000000)
#define PLL_SD2_en_cpnew(data)                                                       (0x04000000&((data)<<26))
#define PLL_SD2_en_cpnew_src(data)                                                   ((0x04000000&(data))>>26)
#define PLL_SD2_get_en_cpnew(data)                                                   ((0x04000000&(data))>>26)
#define PLL_SD2_ssc_div_ext_f_shift                                                  (18)
#define PLL_SD2_ssc_div_ext_f_mask                                                   (0x03FC0000)
#define PLL_SD2_ssc_div_ext_f(data)                                                  (0x03FC0000&((data)<<18))
#define PLL_SD2_ssc_div_ext_f_src(data)                                              ((0x03FC0000&(data))>>18)
#define PLL_SD2_get_ssc_div_ext_f(data)                                              ((0x03FC0000&(data))>>18)
#define PLL_SD2_ssc_div_f_sel_shift                                                  (17)
#define PLL_SD2_ssc_div_f_sel_mask                                                   (0x00020000)
#define PLL_SD2_ssc_div_f_sel(data)                                                  (0x00020000&((data)<<17))
#define PLL_SD2_ssc_div_f_sel_src(data)                                              ((0x00020000&(data))>>17)
#define PLL_SD2_get_ssc_div_f_sel(data)                                              ((0x00020000&(data))>>17)
#define PLL_SD2_ssc_8x_en_shift                                                      (16)
#define PLL_SD2_ssc_8x_en_mask                                                       (0x00010000)
#define PLL_SD2_ssc_8x_en(data)                                                      (0x00010000&((data)<<16))
#define PLL_SD2_ssc_8x_en_src(data)                                                  ((0x00010000&(data))>>16)
#define PLL_SD2_get_ssc_8x_en(data)                                                  ((0x00010000&(data))>>16)
#define PLL_SD2_ssc_depth_shift                                                      (13)
#define PLL_SD2_ssc_depth_mask                                                       (0x0000E000)
#define PLL_SD2_ssc_depth(data)                                                      (0x0000E000&((data)<<13))
#define PLL_SD2_ssc_depth_src(data)                                                  ((0x0000E000&(data))>>13)
#define PLL_SD2_get_ssc_depth(data)                                                  ((0x0000E000&(data))>>13)
#define PLL_SD2_sscpll_rs_shift                                                      (10)
#define PLL_SD2_sscpll_rs_mask                                                       (0x00001C00)
#define PLL_SD2_sscpll_rs(data)                                                      (0x00001C00&((data)<<10))
#define PLL_SD2_sscpll_rs_src(data)                                                  ((0x00001C00&(data))>>10)
#define PLL_SD2_get_sscpll_rs(data)                                                  ((0x00001C00&(data))>>10)
#define PLL_SD2_sscpll_icp_shift                                                     (5)
#define PLL_SD2_sscpll_icp_mask                                                      (0x000003E0)
#define PLL_SD2_sscpll_icp(data)                                                     (0x000003E0&((data)<<5))
#define PLL_SD2_sscpll_icp_src(data)                                                 ((0x000003E0&(data))>>5)
#define PLL_SD2_get_sscpll_icp(data)                                                 ((0x000003E0&(data))>>5)
#define PLL_SD2_sscpll_cs1_shift                                                     (3)
#define PLL_SD2_sscpll_cs1_mask                                                      (0x00000018)
#define PLL_SD2_sscpll_cs1(data)                                                     (0x00000018&((data)<<3))
#define PLL_SD2_sscpll_cs1_src(data)                                                 ((0x00000018&(data))>>3)
#define PLL_SD2_get_sscpll_cs1(data)                                                 ((0x00000018&(data))>>3)
#define PLL_SD2_reg_tune11_shift                                                     (1)
#define PLL_SD2_reg_tune11_mask                                                      (0x00000006)
#define PLL_SD2_reg_tune11(data)                                                     (0x00000006&((data)<<1))
#define PLL_SD2_reg_tune11_src(data)                                                 ((0x00000006&(data))>>1)
#define PLL_SD2_get_reg_tune11(data)                                                 ((0x00000006&(data))>>1)
#define PLL_SD2_sscldo_en_shift                                                      (0)
#define PLL_SD2_sscldo_en_mask                                                       (0x00000001)
#define PLL_SD2_sscldo_en(data)                                                      (0x00000001&((data)<<0))
#define PLL_SD2_sscldo_en_src(data)                                                  ((0x00000001&(data))>>0)
#define PLL_SD2_get_sscldo_en(data)                                                  ((0x00000001&(data))>>0)


#define PLL_SD3                                                                      0x980001E8
#define PLL_SD3_reg_addr                                                             "0x980001E8"
#define PLL_SD3_reg                                                                  0x980001E8
#define set_PLL_SD3_reg(data)   (*((volatile unsigned int*) PLL_SD3_reg)=data)
#define get_PLL_SD3_reg   (*((volatile unsigned int*) PLL_SD3_reg))
#define PLL_SD3_inst_adr                                                             "0x007A"
#define PLL_SD3_inst                                                                 0x007A
#define PLL_SD3_ssc_div_n_shift                                                      (16)
#define PLL_SD3_ssc_div_n_mask                                                       (0x03FF0000)
#define PLL_SD3_ssc_div_n(data)                                                      (0x03FF0000&((data)<<16))
#define PLL_SD3_ssc_div_n_src(data)                                                  ((0x03FF0000&(data))>>16)
#define PLL_SD3_get_ssc_div_n(data)                                                  ((0x03FF0000&(data))>>16)
#define PLL_SD3_ssc_step_in_shift                                                    (8)
#define PLL_SD3_ssc_step_in_mask                                                     (0x00007F00)
#define PLL_SD3_ssc_step_in(data)                                                    (0x00007F00&((data)<<8))
#define PLL_SD3_ssc_step_in_src(data)                                                ((0x00007F00&(data))>>8)
#define PLL_SD3_get_ssc_step_in(data)                                                ((0x00007F00&(data))>>8)
#define PLL_SD3_ssc_tbase_shift                                                      (0)
#define PLL_SD3_ssc_tbase_mask                                                       (0x000000FF)
#define PLL_SD3_ssc_tbase(data)                                                      (0x000000FF&((data)<<0))
#define PLL_SD3_ssc_tbase_src(data)                                                  ((0x000000FF&(data))>>0)
#define PLL_SD3_get_ssc_tbase(data)                                                  ((0x000000FF&(data))>>0)


#define PLL_SD4                                                                      0x980001EC
#define PLL_SD4_reg_addr                                                             "0x980001EC"
#define PLL_SD4_reg                                                                  0x980001EC
#define set_PLL_SD4_reg(data)   (*((volatile unsigned int*) PLL_SD4_reg)=data)
#define get_PLL_SD4_reg   (*((volatile unsigned int*) PLL_SD4_reg))
#define PLL_SD4_inst_adr                                                             "0x007B"
#define PLL_SD4_inst                                                                 0x007B
#define PLL_SD4_ssc_pll_pow_shift                                                    (2)
#define PLL_SD4_ssc_pll_pow_mask                                                     (0x00000004)
#define PLL_SD4_ssc_pll_pow(data)                                                    (0x00000004&((data)<<2))
#define PLL_SD4_ssc_pll_pow_src(data)                                                ((0x00000004&(data))>>2)
#define PLL_SD4_get_ssc_pll_pow(data)                                                ((0x00000004&(data))>>2)
#define PLL_SD4_ssc_pll_rstb_shift                                                   (1)
#define PLL_SD4_ssc_pll_rstb_mask                                                    (0x00000002)
#define PLL_SD4_ssc_pll_rstb(data)                                                   (0x00000002&((data)<<1))
#define PLL_SD4_ssc_pll_rstb_src(data)                                               ((0x00000002&(data))>>1)
#define PLL_SD4_get_ssc_pll_rstb(data)                                               ((0x00000002&(data))>>1)
#define PLL_SD4_ssc_rstb_shift                                                       (0)
#define PLL_SD4_ssc_rstb_mask                                                        (0x00000001)
#define PLL_SD4_ssc_rstb(data)                                                       (0x00000001&((data)<<0))
#define PLL_SD4_ssc_rstb_src(data)                                                   ((0x00000001&(data))>>0)
#define PLL_SD4_get_ssc_rstb(data)                                                   ((0x00000001&(data))>>0)


//#define PLL_EMMC1                                                                    0x980001F0
#define PLL_EMMC1_reg_addr                                                           "0x980001F0"
#define PLL_EMMC1_reg                                                                0x980001F0
#define set_PLL_EMMC1_reg(data)   (*((volatile unsigned int*) PLL_EMMC1_reg)=data)
#define get_PLL_EMMC1_reg   (*((volatile unsigned int*) PLL_EMMC1_reg))
#define PLL_EMMC1_inst_adr                                                           "0x007C"
#define PLL_EMMC1_inst                                                               0x007C
#define PLL_EMMC1_reg_tuned3318_shift                                                (19)
#define PLL_EMMC1_reg_tuned3318_mask                                                 (0x00380000)
#define PLL_EMMC1_reg_tuned3318(data)                                                (0x00380000&((data)<<19))
#define PLL_EMMC1_reg_tuned3318_src(data)                                            ((0x00380000&(data))>>19)
#define PLL_EMMC1_get_reg_tuned3318(data)                                            ((0x00380000&(data))>>19)
#define PLL_EMMC1_reg_d3318pow_shift                                                 (17)
#define PLL_EMMC1_reg_d3318pow_mask                                                  (0x00060000)
#define PLL_EMMC1_reg_d3318pow(data)                                                 (0x00060000&((data)<<17))
#define PLL_EMMC1_reg_d3318pow_src(data)                                             ((0x00060000&(data))>>17)
#define PLL_EMMC1_get_reg_d3318pow(data)                                             ((0x00060000&(data))>>17)
#define PLL_EMMC1_regpd_d3318_shift                                                  (16)
#define PLL_EMMC1_regpd_d3318_mask                                                   (0x00010000)
#define PLL_EMMC1_regpd_d3318(data)                                                  (0x00010000&((data)<<16))
#define PLL_EMMC1_regpd_d3318_src(data)                                              ((0x00010000&(data))>>16)
#define PLL_EMMC1_get_regpd_d3318(data)                                              ((0x00010000&(data))>>16)
#define PLL_EMMC1_phsel1_shift                                                       (8)
#define PLL_EMMC1_phsel1_mask                                                        (0x00001F00)
#define PLL_EMMC1_phsel1(data)                                                       (0x00001F00&((data)<<8))
#define PLL_EMMC1_phsel1_src(data)                                                   ((0x00001F00&(data))>>8)
#define PLL_EMMC1_get_phsel1(data)                                                   ((0x00001F00&(data))>>8)
#define PLL_EMMC1_phsel0_shift                                                       (3)
#define PLL_EMMC1_phsel0_mask                                                        (0x000000F8)
#define PLL_EMMC1_phsel0(data)                                                       (0x000000F8&((data)<<3))
#define PLL_EMMC1_phsel0_src(data)                                                   ((0x000000F8&(data))>>3)
#define PLL_EMMC1_get_phsel0(data)                                                   ((0x000000F8&(data))>>3)
#define PLL_EMMC1_phrstb_dly_sel_shift                                               (2)
#define PLL_EMMC1_phrstb_dly_sel_mask                                                (0x00000004)
#define PLL_EMMC1_phrstb_dly_sel(data)                                               (0x00000004&((data)<<2))
#define PLL_EMMC1_phrstb_dly_sel_src(data)                                           ((0x00000004&(data))>>2)
#define PLL_EMMC1_get_phrstb_dly_sel(data)                                           ((0x00000004&(data))>>2)
#define PLL_EMMC1_phrt0_shift                                                        (1)
#define PLL_EMMC1_phrt0_mask                                                         (0x00000002)
#define PLL_EMMC1_phrt0(data)                                                        (0x00000002&((data)<<1))
#define PLL_EMMC1_phrt0_src(data)                                                    ((0x00000002&(data))>>1)
#define PLL_EMMC1_get_phrt0(data)                                                    ((0x00000002&(data))>>1)
#define PLL_EMMC1_bias_en_shift                                                      (0)
#define PLL_EMMC1_bias_en_mask                                                       (0x00000001)
#define PLL_EMMC1_bias_en(data)                                                      (0x00000001&((data)<<0))
#define PLL_EMMC1_bias_en_src(data)                                                  ((0x00000001&(data))>>0)
#define PLL_EMMC1_get_bias_en(data)                                                  ((0x00000001&(data))>>0)


//#define PLL_EMMC2                                                                    0x980001F4
#define PLL_EMMC2_reg_addr                                                           "0x980001F4"
#define PLL_EMMC2_reg                                                                0x980001F4
#define set_PLL_EMMC2_reg(data)   (*((volatile unsigned int*) PLL_EMMC2_reg)=data)
#define get_PLL_EMMC2_reg   (*((volatile unsigned int*) PLL_EMMC2_reg))
#define PLL_EMMC2_inst_adr                                                           "0x007D"
#define PLL_EMMC2_inst                                                               0x007D
#define PLL_EMMC2_en_cpnew_shift                                                     (26)
#define PLL_EMMC2_en_cpnew_mask                                                      (0x04000000)
#define PLL_EMMC2_en_cpnew(data)                                                     (0x04000000&((data)<<26))
#define PLL_EMMC2_en_cpnew_src(data)                                                 ((0x04000000&(data))>>26)
#define PLL_EMMC2_get_en_cpnew(data)                                                 ((0x04000000&(data))>>26)
#define PLL_EMMC2_ssc_div_ext_f_shift                                                (18)
#define PLL_EMMC2_ssc_div_ext_f_mask                                                 (0x03FC0000)
#define PLL_EMMC2_ssc_div_ext_f(data)                                                (0x03FC0000&((data)<<18))
#define PLL_EMMC2_ssc_div_ext_f_src(data)                                            ((0x03FC0000&(data))>>18)
#define PLL_EMMC2_get_ssc_div_ext_f(data)                                            ((0x03FC0000&(data))>>18)
#define PLL_EMMC2_ssc_div_f_sel_shift                                                (17)
#define PLL_EMMC2_ssc_div_f_sel_mask                                                 (0x00020000)
#define PLL_EMMC2_ssc_div_f_sel(data)                                                (0x00020000&((data)<<17))
#define PLL_EMMC2_ssc_div_f_sel_src(data)                                            ((0x00020000&(data))>>17)
#define PLL_EMMC2_get_ssc_div_f_sel(data)                                            ((0x00020000&(data))>>17)
#define PLL_EMMC2_ssc_8x_en_shift                                                    (16)
#define PLL_EMMC2_ssc_8x_en_mask                                                     (0x00010000)
#define PLL_EMMC2_ssc_8x_en(data)                                                    (0x00010000&((data)<<16))
#define PLL_EMMC2_ssc_8x_en_src(data)                                                ((0x00010000&(data))>>16)
#define PLL_EMMC2_get_ssc_8x_en(data)                                                ((0x00010000&(data))>>16)
#define PLL_EMMC2_ssc_depth_shift                                                    (13)
#define PLL_EMMC2_ssc_depth_mask                                                     (0x0000E000)
#define PLL_EMMC2_ssc_depth(data)                                                    (0x0000E000&((data)<<13))
#define PLL_EMMC2_ssc_depth_src(data)                                                ((0x0000E000&(data))>>13)
#define PLL_EMMC2_get_ssc_depth(data)                                                ((0x0000E000&(data))>>13)
#define PLL_EMMC2_sscpll_rs_shift                                                    (10)
#define PLL_EMMC2_sscpll_rs_mask                                                     (0x00001C00)
#define PLL_EMMC2_sscpll_rs(data)                                                    (0x00001C00&((data)<<10))
#define PLL_EMMC2_sscpll_rs_src(data)                                                ((0x00001C00&(data))>>10)
#define PLL_EMMC2_get_sscpll_rs(data)                                                ((0x00001C00&(data))>>10)
#define PLL_EMMC2_sscpll_icp_shift                                                   (5)
#define PLL_EMMC2_sscpll_icp_mask                                                    (0x000003E0)
#define PLL_EMMC2_sscpll_icp(data)                                                   (0x000003E0&((data)<<5))
#define PLL_EMMC2_sscpll_icp_src(data)                                               ((0x000003E0&(data))>>5)
#define PLL_EMMC2_get_sscpll_icp(data)                                               ((0x000003E0&(data))>>5)
#define PLL_EMMC2_sscpll_cs1_shift                                                   (3)
#define PLL_EMMC2_sscpll_cs1_mask                                                    (0x00000018)
#define PLL_EMMC2_sscpll_cs1(data)                                                   (0x00000018&((data)<<3))
#define PLL_EMMC2_sscpll_cs1_src(data)                                               ((0x00000018&(data))>>3)
#define PLL_EMMC2_get_sscpll_cs1(data)                                               ((0x00000018&(data))>>3)
#define PLL_EMMC2_reg_tune11_shift                                                   (1)
#define PLL_EMMC2_reg_tune11_mask                                                    (0x00000006)
#define PLL_EMMC2_reg_tune11(data)                                                   (0x00000006&((data)<<1))
#define PLL_EMMC2_reg_tune11_src(data)                                               ((0x00000006&(data))>>1)
#define PLL_EMMC2_get_reg_tune11(data)                                               ((0x00000006&(data))>>1)
#define PLL_EMMC2_sscldo_en_shift                                                    (0)
#define PLL_EMMC2_sscldo_en_mask                                                     (0x00000001)
#define PLL_EMMC2_sscldo_en(data)                                                    (0x00000001&((data)<<0))
#define PLL_EMMC2_sscldo_en_src(data)                                                ((0x00000001&(data))>>0)
#define PLL_EMMC2_get_sscldo_en(data)                                                ((0x00000001&(data))>>0)


//#define PLL_EMMC3                                                                    0x980001F8
#define PLL_EMMC3_reg_addr                                                           "0x980001F8"
#define PLL_EMMC3_reg                                                                0x980001F8
#define set_PLL_EMMC3_reg(data)   (*((volatile unsigned int*) PLL_EMMC3_reg)=data)
#define get_PLL_EMMC3_reg   (*((volatile unsigned int*) PLL_EMMC3_reg))
#define PLL_EMMC3_inst_adr                                                           "0x007E"
#define PLL_EMMC3_inst                                                               0x007E
#define PLL_EMMC3_ssc_div_n_shift                                                    (16)
#define PLL_EMMC3_ssc_div_n_mask                                                     (0x03FF0000)
#define PLL_EMMC3_ssc_div_n(data)                                                    (0x03FF0000&((data)<<16))
#define PLL_EMMC3_ssc_div_n_src(data)                                                ((0x03FF0000&(data))>>16)
#define PLL_EMMC3_get_ssc_div_n(data)                                                ((0x03FF0000&(data))>>16)
#define PLL_EMMC3_ssc_step_in_shift                                                  (8)
#define PLL_EMMC3_ssc_step_in_mask                                                   (0x00007F00)
#define PLL_EMMC3_ssc_step_in(data)                                                  (0x00007F00&((data)<<8))
#define PLL_EMMC3_ssc_step_in_src(data)                                              ((0x00007F00&(data))>>8)
#define PLL_EMMC3_get_ssc_step_in(data)                                              ((0x00007F00&(data))>>8)
#define PLL_EMMC3_ssc_tbase_shift                                                    (0)
#define PLL_EMMC3_ssc_tbase_mask                                                     (0x000000FF)
#define PLL_EMMC3_ssc_tbase(data)                                                    (0x000000FF&((data)<<0))
#define PLL_EMMC3_ssc_tbase_src(data)                                                ((0x000000FF&(data))>>0)
#define PLL_EMMC3_get_ssc_tbase(data)                                                ((0x000000FF&(data))>>0)


//#define PLL_EMMC4                                                                    0x980001FC
#define PLL_EMMC4_reg_addr                                                           "0x980001FC"
#define PLL_EMMC4_reg                                                                0x980001FC
#define set_PLL_EMMC4_reg(data)   (*((volatile unsigned int*) PLL_EMMC4_reg)=data)
#define get_PLL_EMMC4_reg   (*((volatile unsigned int*) PLL_EMMC4_reg))
#define PLL_EMMC4_inst_adr                                                           "0x007F"
#define PLL_EMMC4_inst                                                               0x007F
#define PLL_EMMC4_ssc_pll_pow_shift                                                  (2)
#define PLL_EMMC4_ssc_pll_pow_mask                                                   (0x00000004)
#define PLL_EMMC4_ssc_pll_pow(data)                                                  (0x00000004&((data)<<2))
#define PLL_EMMC4_ssc_pll_pow_src(data)                                              ((0x00000004&(data))>>2)
#define PLL_EMMC4_get_ssc_pll_pow(data)                                              ((0x00000004&(data))>>2)
#define PLL_EMMC4_ssc_pll_rstb_shift                                                 (1)
#define PLL_EMMC4_ssc_pll_rstb_mask                                                  (0x00000002)
#define PLL_EMMC4_ssc_pll_rstb(data)                                                 (0x00000002&((data)<<1))
#define PLL_EMMC4_ssc_pll_rstb_src(data)                                             ((0x00000002&(data))>>1)
#define PLL_EMMC4_get_ssc_pll_rstb(data)                                             ((0x00000002&(data))>>1)
#define PLL_EMMC4_ssc_rstb_shift                                                     (0)
#define PLL_EMMC4_ssc_rstb_mask                                                      (0x00000001)
#define PLL_EMMC4_ssc_rstb(data)                                                     (0x00000001&((data)<<0))
#define PLL_EMMC4_ssc_rstb_src(data)                                                 ((0x00000001&(data))>>0)
#define PLL_EMMC4_get_ssc_rstb(data)                                                 ((0x00000001&(data))>>0)


#define BG_CTL                                                                       0x98000204
#define BG_CTL_reg_addr                                                              "0x98000204"
#define BG_CTL_reg                                                                   0x98000204
#define set_BG_CTL_reg(data)   (*((volatile unsigned int*) BG_CTL_reg)=data)
#define get_BG_CTL_reg   (*((volatile unsigned int*) BG_CTL_reg))
#define BG_CTL_inst_adr                                                              "0x0081"
#define BG_CTL_inst                                                                  0x0081
#define BG_CTL_REG_PLL_RESERVED_shift                                                (24)
#define BG_CTL_REG_PLL_RESERVED_mask                                                 (0xFF000000)
#define BG_CTL_REG_PLL_RESERVED(data)                                                (0xFF000000&((data)<<24))
#define BG_CTL_REG_PLL_RESERVED_src(data)                                            ((0xFF000000&(data))>>24)
#define BG_CTL_get_REG_PLL_RESERVED(data)                                            ((0xFF000000&(data))>>24)
#define BG_CTL_REG_LDO1_POW_shift                                                    (7)
#define BG_CTL_REG_LDO1_POW_mask                                                     (0x00000080)
#define BG_CTL_REG_LDO1_POW(data)                                                    (0x00000080&((data)<<7))
#define BG_CTL_REG_LDO1_POW_src(data)                                                ((0x00000080&(data))>>7)
#define BG_CTL_get_REG_LDO1_POW(data)                                                ((0x00000080&(data))>>7)
#define BG_CTL_REG_LDO1_SEL_shift                                                    (5)
#define BG_CTL_REG_LDO1_SEL_mask                                                     (0x00000060)
#define BG_CTL_REG_LDO1_SEL(data)                                                    (0x00000060&((data)<<5))
#define BG_CTL_REG_LDO1_SEL_src(data)                                                ((0x00000060&(data))>>5)
#define BG_CTL_get_REG_LDO1_SEL(data)                                                ((0x00000060&(data))>>5)
#define BG_CTL_REG_LDO2_POW_shift                                                    (4)
#define BG_CTL_REG_LDO2_POW_mask                                                     (0x00000010)
#define BG_CTL_REG_LDO2_POW(data)                                                    (0x00000010&((data)<<4))
#define BG_CTL_REG_LDO2_POW_src(data)                                                ((0x00000010&(data))>>4)
#define BG_CTL_get_REG_LDO2_POW(data)                                                ((0x00000010&(data))>>4)
#define BG_CTL_REG_LDO2_SEL_shift                                                    (2)
#define BG_CTL_REG_LDO2_SEL_mask                                                     (0x0000000C)
#define BG_CTL_REG_LDO2_SEL(data)                                                    (0x0000000C&((data)<<2))
#define BG_CTL_REG_LDO2_SEL_src(data)                                                ((0x0000000C&(data))>>2)
#define BG_CTL_get_REG_LDO2_SEL(data)                                                ((0x0000000C&(data))>>2)
#define BG_CTL_VDAC_BGR_shift                                                        (0)
#define BG_CTL_VDAC_BGR_mask                                                         (0x00000003)
#define BG_CTL_VDAC_BGR(data)                                                        (0x00000003&((data)<<0))
#define BG_CTL_VDAC_BGR_src(data)                                                    ((0x00000003&(data))>>0)
#define BG_CTL_get_VDAC_BGR(data)                                                    ((0x00000003&(data))>>0)


#define CRT_CHIP_INFO2                                                                   0x98000308
#define CRT_CHIP_INFO2_reg_addr                                                          "0x98000308"
#define CRT_CHIP_INFO2_reg                                                               0x98000308
#define CRT_set_CHIP_INFO2_reg(data)   (*((volatile unsigned int*) CHIP_INFO2_reg)=data)
#define CRT_get_CHIP_INFO2_reg   (*((volatile unsigned int*) CHIP_INFO2_reg))
#define CRT_CHIP_INFO2_inst_adr                                                          "0x00C2"
#define CRT_CHIP_INFO2_inst                                                              0x00C2
#define CRT_CHIP_INFO2_testmode_shift                                                    (2)
#define CRT_CHIP_INFO2_testmode_mask                                                     (0x00000004)
#define CRT_CHIP_INFO2_testmode(data)                                                    (0x00000004&((data)<<2))
#define CRT_CHIP_INFO2_testmode_src(data)                                                ((0x00000004&(data))>>2)
#define CRT_CHIP_INFO2_get_testmode(data)                                                ((0x00000004&(data))>>2)
#define CRT_CHIP_INFO2_nf_sel_shift                                                      (1)
#define CRT_CHIP_INFO2_nf_sel_mask                                                       (0x00000002)
#define CRT_CHIP_INFO2_nf_sel(data)                                                      (0x00000002&((data)<<1))
#define CRT_CHIP_INFO2_nf_sel_src(data)                                                  ((0x00000002&(data))>>1)
#define CRT_CHIP_INFO2_get_nf_sel(data)                                                  ((0x00000002&(data))>>1)
#define CRT_CHIP_INFO2_boot_sel_shift                                                    (0)
#define CRT_CHIP_INFO2_boot_sel_mask                                                     (0x00000001)
#define CRT_CHIP_INFO2_boot_sel(data)                                                    (0x00000001&((data)<<0))
#define CRT_CHIP_INFO2_boot_sel_src(data)                                                ((0x00000001&(data))>>0)
#define CRT_CHIP_INFO2_get_boot_sel(data)                                                ((0x00000001&(data))>>0)


#define SCPU_L2                                                                      0x9800030C
#define SCPU_L2_reg_addr                                                             "0x9800030C"
#define SCPU_L2_reg                                                                  0x9800030C
#define set_SCPU_L2_reg(data)   (*((volatile unsigned int*) SCPU_L2_reg)=data)
#define get_SCPU_L2_reg   (*((volatile unsigned int*) SCPU_L2_reg))
#define SCPU_L2_inst_adr                                                             "0x00C3"
#define SCPU_L2_inst                                                                 0x00C3
#define SCPU_L2_scpu_l2_bypass_shift                                                 (0)
#define SCPU_L2_scpu_l2_bypass_mask                                                  (0x00000001)
#define SCPU_L2_scpu_l2_bypass(data)                                                 (0x00000001&((data)<<0))
#define SCPU_L2_scpu_l2_bypass_src(data)                                             ((0x00000001&(data))>>0)
#define SCPU_L2_get_scpu_l2_bypass(data)                                             ((0x00000001&(data))>>0)


#define THML_SNSR_CTRL                                                               0x98000310
#define THML_SNSR_CTRL_reg_addr                                                      "0x98000310"
#define THML_SNSR_CTRL_reg                                                           0x98000310
#define set_THML_SNSR_CTRL_reg(data)   (*((volatile unsigned int*) THML_SNSR_CTRL_reg)=data)
#define get_THML_SNSR_CTRL_reg   (*((volatile unsigned int*) THML_SNSR_CTRL_reg))
#define THML_SNSR_CTRL_inst_adr                                                      "0x00C4"
#define THML_SNSR_CTRL_inst                                                          0x00C4
#define THML_SNSR_CTRL_CMP_OUT_shift                                                 (16)
#define THML_SNSR_CTRL_CMP_OUT_mask                                                  (0x00010000)
#define THML_SNSR_CTRL_CMP_OUT(data)                                                 (0x00010000&((data)<<16))
#define THML_SNSR_CTRL_CMP_OUT_src(data)                                             ((0x00010000&(data))>>16)
#define THML_SNSR_CTRL_get_CMP_OUT(data)                                             ((0x00010000&(data))>>16)
#define THML_SNSR_CTRL_PWDB1_shift                                                   (15)
#define THML_SNSR_CTRL_PWDB1_mask                                                    (0x00008000)
#define THML_SNSR_CTRL_PWDB1(data)                                                   (0x00008000&((data)<<15))
#define THML_SNSR_CTRL_PWDB1_src(data)                                               ((0x00008000&(data))>>15)
#define THML_SNSR_CTRL_get_PWDB1(data)                                               ((0x00008000&(data))>>15)
#define THML_SNSR_CTRL_SBG1_shift                                                    (12)
#define THML_SNSR_CTRL_SBG1_mask                                                     (0x00007000)
#define THML_SNSR_CTRL_SBG1(data)                                                    (0x00007000&((data)<<12))
#define THML_SNSR_CTRL_SBG1_src(data)                                                ((0x00007000&(data))>>12)
#define THML_SNSR_CTRL_get_SBG1(data)                                                ((0x00007000&(data))>>12)
#define THML_SNSR_CTRL_SDATA1_shift                                                  (5)
#define THML_SNSR_CTRL_SDATA1_mask                                                   (0x00000FE0)
#define THML_SNSR_CTRL_SDATA1(data)                                                  (0x00000FE0&((data)<<5))
#define THML_SNSR_CTRL_SDATA1_src(data)                                              ((0x00000FE0&(data))>>5)
#define THML_SNSR_CTRL_get_SDATA1(data)                                              ((0x00000FE0&(data))>>5)
#define THML_SNSR_CTRL_SINL1_shift                                                   (3)
#define THML_SNSR_CTRL_SINL1_mask                                                    (0x00000018)
#define THML_SNSR_CTRL_SINL1(data)                                                   (0x00000018&((data)<<3))
#define THML_SNSR_CTRL_SINL1_src(data)                                               ((0x00000018&(data))>>3)
#define THML_SNSR_CTRL_get_SINL1(data)                                               ((0x00000018&(data))>>3)
#define THML_SNSR_CTRL_SOS1_shift                                                    (0)
#define THML_SNSR_CTRL_SOS1_mask                                                     (0x00000007)
#define THML_SNSR_CTRL_SOS1(data)                                                    (0x00000007&((data)<<0))
#define THML_SNSR_CTRL_SOS1_src(data)                                                ((0x00000007&(data))>>0)
#define THML_SNSR_CTRL_get_SOS1(data)                                                ((0x00000007&(data))>>0)


#define PWDN_CTRL                                                                    0x98000320
#define PWDN_CTRL_reg_addr                                                           "0x98000320"
#define PWDN_CTRL_reg                                                                0x98000320
#define set_PWDN_CTRL_reg(data)   (*((volatile unsigned int*) PWDN_CTRL_reg)=data)
#define get_PWDN_CTRL_reg   (*((volatile unsigned int*) PWDN_CTRL_reg))
#define PWDN_CTRL_inst_adr                                                           "0x00C8"
#define PWDN_CTRL_inst                                                               0x00C8
#define PWDN_CTRL_kcpu_boot_info_shift                                               (0)
#define PWDN_CTRL_kcpu_boot_info_mask                                                (0xFFFFFFFF)
#define PWDN_CTRL_kcpu_boot_info(data)                                               (0xFFFFFFFF&((data)<<0))
#define PWDN_CTRL_kcpu_boot_info_src(data)                                           ((0xFFFFFFFF&(data))>>0)
#define PWDN_CTRL_get_kcpu_boot_info(data)                                           ((0xFFFFFFFF&(data))>>0)


#define PWDN_CTRL2                                                                   0x98000324
#define PWDN_CTRL2_reg_addr                                                          "0x98000324"
#define PWDN_CTRL2_reg                                                               0x98000324
#define set_PWDN_CTRL2_reg(data)   (*((volatile unsigned int*) PWDN_CTRL2_reg)=data)
#define get_PWDN_CTRL2_reg   (*((volatile unsigned int*) PWDN_CTRL2_reg))
#define PWDN_CTRL2_inst_adr                                                          "0x00C9"
#define PWDN_CTRL2_inst                                                              0x00C9
#define PWDN_CTRL2_acpu_boot_info_shift                                              (0)
#define PWDN_CTRL2_acpu_boot_info_mask                                               (0xFFFFFFFF)
#define PWDN_CTRL2_acpu_boot_info(data)                                              (0xFFFFFFFF&((data)<<0))
#define PWDN_CTRL2_acpu_boot_info_src(data)                                          ((0xFFFFFFFF&(data))>>0)
#define PWDN_CTRL2_get_acpu_boot_info(data)                                          ((0xFFFFFFFF&(data))>>0)


#define PWDN_CTRL3                                                                   0x98000328
#define PWDN_CTRL3_reg_addr                                                          "0x98000328"
#define PWDN_CTRL3_reg                                                               0x98000328
#define set_PWDN_CTRL3_reg(data)   (*((volatile unsigned int*) PWDN_CTRL3_reg)=data)
#define get_PWDN_CTRL3_reg   (*((volatile unsigned int*) PWDN_CTRL3_reg))
#define PWDN_CTRL3_inst_adr                                                          "0x00CA"
#define PWDN_CTRL3_inst                                                              0x00CA
#define PWDN_CTRL3_write_en2_shift                                                   (3)
#define PWDN_CTRL3_write_en2_mask                                                    (0x00000008)
#define PWDN_CTRL3_write_en2(data)                                                   (0x00000008&((data)<<3))
#define PWDN_CTRL3_write_en2_src(data)                                               ((0x00000008&(data))>>3)
#define PWDN_CTRL3_get_write_en2(data)                                               ((0x00000008&(data))>>3)
#define PWDN_CTRL3_kcpu_boot_info_valid_shift                                        (2)
#define PWDN_CTRL3_kcpu_boot_info_valid_mask                                         (0x00000004)
#define PWDN_CTRL3_kcpu_boot_info_valid(data)                                        (0x00000004&((data)<<2))
#define PWDN_CTRL3_kcpu_boot_info_valid_src(data)                                    ((0x00000004&(data))>>2)
#define PWDN_CTRL3_get_kcpu_boot_info_valid(data)                                    ((0x00000004&(data))>>2)
#define PWDN_CTRL3_write_en1_shift                                                   (1)
#define PWDN_CTRL3_write_en1_mask                                                    (0x00000002)
#define PWDN_CTRL3_write_en1(data)                                                   (0x00000002&((data)<<1))
#define PWDN_CTRL3_write_en1_src(data)                                               ((0x00000002&(data))>>1)
#define PWDN_CTRL3_get_write_en1(data)                                               ((0x00000002&(data))>>1)
#define PWDN_CTRL3_kcpu_sw_rst_shift                                                 (0)
#define PWDN_CTRL3_kcpu_sw_rst_mask                                                  (0x00000001)
#define PWDN_CTRL3_kcpu_sw_rst(data)                                                 (0x00000001&((data)<<0))
#define PWDN_CTRL3_kcpu_sw_rst_src(data)                                             ((0x00000001&(data))>>0)
#define PWDN_CTRL3_get_kcpu_sw_rst(data)                                             ((0x00000001&(data))>>0)


#define PWDN_CTRL4                                                                   0x9800032C
#define PWDN_CTRL4_reg_addr                                                          "0x9800032C"
#define PWDN_CTRL4_reg                                                               0x9800032C
#define set_PWDN_CTRL4_reg(data)   (*((volatile unsigned int*) PWDN_CTRL4_reg)=data)
#define get_PWDN_CTRL4_reg   (*((volatile unsigned int*) PWDN_CTRL4_reg))
#define PWDN_CTRL4_inst_adr                                                          "0x00CB"
#define PWDN_CTRL4_inst                                                              0x00CB
#define PWDN_CTRL4_acpu_boot_info_valid_shift                                        (0)
#define PWDN_CTRL4_acpu_boot_info_valid_mask                                         (0x00000001)
#define PWDN_CTRL4_acpu_boot_info_valid(data)                                        (0x00000001&((data)<<0))
#define PWDN_CTRL4_acpu_boot_info_valid_src(data)                                    ((0x00000001&(data))>>0)
#define PWDN_CTRL4_get_acpu_boot_info_valid(data)                                    ((0x00000001&(data))>>0)


#define AT_SPEED                                                                     0x98000330
#define AT_SPEED_reg_addr                                                            "0x98000330"
#define AT_SPEED_reg                                                                 0x98000330
#define set_AT_SPEED_reg(data)   (*((volatile unsigned int*) AT_SPEED_reg)=data)
#define get_AT_SPEED_reg   (*((volatile unsigned int*) AT_SPEED_reg))
#define AT_SPEED_inst_adr                                                            "0x00CC"
#define AT_SPEED_inst                                                                0x00CC
#define AT_SPEED_write_en2_shift                                                     (3)
#define AT_SPEED_write_en2_mask                                                      (0x00000008)
#define AT_SPEED_write_en2(data)                                                     (0x00000008&((data)<<3))
#define AT_SPEED_write_en2_src(data)                                                 ((0x00000008&(data))>>3)
#define AT_SPEED_get_write_en2(data)                                                 ((0x00000008&(data))>>3)
#define AT_SPEED_dac_test_shift                                                      (2)
#define AT_SPEED_dac_test_mask                                                       (0x00000004)
#define AT_SPEED_dac_test(data)                                                      (0x00000004&((data)<<2))
#define AT_SPEED_dac_test_src(data)                                                  ((0x00000004&(data))>>2)
#define AT_SPEED_get_dac_test(data)                                                  ((0x00000004&(data))>>2)
#define AT_SPEED_write_en1_shift                                                     (1)
#define AT_SPEED_write_en1_mask                                                      (0x00000002)
#define AT_SPEED_write_en1(data)                                                     (0x00000002&((data)<<1))
#define AT_SPEED_write_en1_src(data)                                                 ((0x00000002&(data))>>1)
#define AT_SPEED_get_write_en1(data)                                                 ((0x00000002&(data))>>1)
#define AT_SPEED_scpu_config_done_shift                                              (0)
#define AT_SPEED_scpu_config_done_mask                                               (0x00000001)
#define AT_SPEED_scpu_config_done(data)                                              (0x00000001&((data)<<0))
#define AT_SPEED_scpu_config_done_src(data)                                          ((0x00000001&(data))>>0)
#define AT_SPEED_get_scpu_config_done(data)                                          ((0x00000001&(data))>>0)


#define ANA_CTRL                                                                     0x98000334
#define ANA_CTRL_reg_addr                                                            "0x98000334"
#define ANA_CTRL_reg                                                                 0x98000334
#define set_ANA_CTRL_reg(data)   (*((volatile unsigned int*) ANA_CTRL_reg)=data)
#define get_ANA_CTRL_reg   (*((volatile unsigned int*) ANA_CTRL_reg))
#define ANA_CTRL_inst_adr                                                            "0x00CD"
#define ANA_CTRL_inst                                                                0x00CD
#define ANA_CTRL_write_en2_shift                                                     (3)
#define ANA_CTRL_write_en2_mask                                                      (0x00000008)
#define ANA_CTRL_write_en2(data)                                                     (0x00000008&((data)<<3))
#define ANA_CTRL_write_en2_src(data)                                                 ((0x00000008&(data))>>3)
#define ANA_CTRL_get_write_en2(data)                                                 ((0x00000008&(data))>>3)
#define ANA_CTRL_etn_phy_gpio_en_shift                                               (2)
#define ANA_CTRL_etn_phy_gpio_en_mask                                                (0x00000004)
#define ANA_CTRL_etn_phy_gpio_en(data)                                               (0x00000004&((data)<<2))
#define ANA_CTRL_etn_phy_gpio_en_src(data)                                           ((0x00000004&(data))>>2)
#define ANA_CTRL_get_etn_phy_gpio_en(data)                                           ((0x00000004&(data))>>2)
#define ANA_CTRL_write_en1_shift                                                     (1)
#define ANA_CTRL_write_en1_mask                                                      (0x00000002)
#define ANA_CTRL_write_en1(data)                                                     (0x00000002&((data)<<1))
#define ANA_CTRL_write_en1_src(data)                                                 ((0x00000002&(data))>>1)
#define ANA_CTRL_get_write_en1(data)                                                 ((0x00000002&(data))>>1)
#define ANA_CTRL_etn_phy_125m_en_shift                                               (0)
#define ANA_CTRL_etn_phy_125m_en_mask                                                (0x00000001)
#define ANA_CTRL_etn_phy_125m_en(data)                                               (0x00000001&((data)<<0))
#define ANA_CTRL_etn_phy_125m_en_src(data)                                           ((0x00000001&(data))>>0)
#define ANA_CTRL_get_etn_phy_125m_en(data)                                           ((0x00000001&(data))>>0)


#define TP_DEMOD_CTRL                                                                0x98000338
#define TP_DEMOD_CTRL_reg_addr                                                       "0x98000338"
#define TP_DEMOD_CTRL_reg                                                            0x98000338
#define set_TP_DEMOD_CTRL_reg(data)   (*((volatile unsigned int*) TP_DEMOD_CTRL_reg)=data)
#define get_TP_DEMOD_CTRL_reg   (*((volatile unsigned int*) TP_DEMOD_CTRL_reg))
#define TP_DEMOD_CTRL_inst_adr                                                       "0x00CE"
#define TP_DEMOD_CTRL_inst                                                           0x00CE
#define TP_DEMOD_CTRL_demod_i2c_saddr_shift                                          (4)
#define TP_DEMOD_CTRL_demod_i2c_saddr_mask                                           (0x00000010)
#define TP_DEMOD_CTRL_demod_i2c_saddr(data)                                          (0x00000010&((data)<<4))
#define TP_DEMOD_CTRL_demod_i2c_saddr_src(data)                                      ((0x00000010&(data))>>4)
#define TP_DEMOD_CTRL_get_demod_i2c_saddr(data)                                      ((0x00000010&(data))>>4)
#define TP_DEMOD_CTRL_demod_i2c_sel_shift                                            (3)
#define TP_DEMOD_CTRL_demod_i2c_sel_mask                                             (0x00000008)
#define TP_DEMOD_CTRL_demod_i2c_sel(data)                                            (0x00000008&((data)<<3))
#define TP_DEMOD_CTRL_demod_i2c_sel_src(data)                                        ((0x00000008&(data))>>3)
#define TP_DEMOD_CTRL_get_demod_i2c_sel(data)                                        ((0x00000008&(data))>>3)
#define TP_DEMOD_CTRL_tp2_dm_sel_shift                                               (2)
#define TP_DEMOD_CTRL_tp2_dm_sel_mask                                                (0x00000004)
#define TP_DEMOD_CTRL_tp2_dm_sel(data)                                               (0x00000004&((data)<<2))
#define TP_DEMOD_CTRL_tp2_dm_sel_src(data)                                           ((0x00000004&(data))>>2)
#define TP_DEMOD_CTRL_get_tp2_dm_sel(data)                                           ((0x00000004&(data))>>2)
#define TP_DEMOD_CTRL_tp1_dm_sel_shift                                               (1)
#define TP_DEMOD_CTRL_tp1_dm_sel_mask                                                (0x00000002)
#define TP_DEMOD_CTRL_tp1_dm_sel(data)                                               (0x00000002&((data)<<1))
#define TP_DEMOD_CTRL_tp1_dm_sel_src(data)                                           ((0x00000002&(data))>>1)
#define TP_DEMOD_CTRL_get_tp1_dm_sel(data)                                           ((0x00000002&(data))>>1)
#define TP_DEMOD_CTRL_tp0_dm_sel_shift                                               (0)
#define TP_DEMOD_CTRL_tp0_dm_sel_mask                                                (0x00000001)
#define TP_DEMOD_CTRL_tp0_dm_sel(data)                                               (0x00000001&((data)<<0))
#define TP_DEMOD_CTRL_tp0_dm_sel_src(data)                                           ((0x00000001&(data))>>0)
#define TP_DEMOD_CTRL_get_tp0_dm_sel(data)                                           ((0x00000001&(data))>>0)


#define PHY_FUNC                                                                     0x98000340
#define PHY_FUNC_reg_addr                                                            "0x98000340"
#define PHY_FUNC_reg                                                                 0x98000340
#define set_PHY_FUNC_reg(data)   (*((volatile unsigned int*) PHY_FUNC_reg)=data)
#define get_PHY_FUNC_reg   (*((volatile unsigned int*) PHY_FUNC_reg))
#define PHY_FUNC_inst_adr                                                            "0x00D0"
#define PHY_FUNC_inst                                                                0x00D0
#define PHY_FUNC_sata0_func_exist_shift                                              (0)
#define PHY_FUNC_sata0_func_exist_mask                                               (0x00000001)
#define PHY_FUNC_sata0_func_exist(data)                                              (0x00000001&((data)<<0))
#define PHY_FUNC_sata0_func_exist_src(data)                                          ((0x00000001&(data))>>0)
#define PHY_FUNC_get_sata0_func_exist(data)                                          ((0x00000001&(data))>>0)


#define CRT_ANLG                                                                         0x98000344
#define CRT_ANLG_reg_addr                                                                "0x98000344"
#define CRT_ANLG_reg                                                                     0x98000344
#define CRT_set_ANLG_reg(data)   (*((volatile unsigned int*) ANLG_reg)=data)
#define CRT_get_ANLG_reg   (*((volatile unsigned int*) ANLG_reg))
#define CRT_ANLG_inst_adr                                                                "0x00D1"
#define CRT_ANLG_inst                                                                    0x00D1
#define CRT_ANLG_analogy_mode_sel_shift                                                  (0)
#define CRT_ANLG_analogy_mode_sel_mask                                                   (0x00000003)
#define CRT_ANLG_analogy_mode_sel(data)                                                  (0x00000003&((data)<<0))
#define CRT_ANLG_analogy_mode_sel_src(data)                                              ((0x00000003&(data))>>0)
#define CRT_ANLG_get_analogy_mode_sel(data)                                              ((0x00000003&(data))>>0)


#define DMY2                                                                         0x98000348
#define DMY2_reg_addr                                                                "0x98000348"
#define DMY2_reg                                                                     0x98000348
#define set_DMY2_reg(data)   (*((volatile unsigned int*) DMY2_reg)=data)
#define get_DMY2_reg   (*((volatile unsigned int*) DMY2_reg))
#define DMY2_inst_adr                                                                "0x00D2"
#define DMY2_inst                                                                    0x00D2
#define DMY2_Rvd1_shift                                                              (0)
#define DMY2_Rvd1_mask                                                               (0xFFFFFFFF)
#define DMY2_Rvd1(data)                                                              (0xFFFFFFFF&((data)<<0))
#define DMY2_Rvd1_src(data)                                                          ((0xFFFFFFFF&(data))>>0)
#define DMY2_get_Rvd1(data)                                                          ((0xFFFFFFFF&(data))>>0)


#define RGMII_PAD                                                                    0x9800034C
#define RGMII_PAD_reg_addr                                                           "0x9800034C"
#define RGMII_PAD_reg                                                                0x9800034C
#define set_RGMII_PAD_reg(data)   (*((volatile unsigned int*) RGMII_PAD_reg)=data)
#define get_RGMII_PAD_reg   (*((volatile unsigned int*) RGMII_PAD_reg))
#define RGMII_PAD_inst_adr                                                           "0x00D3"
#define RGMII_PAD_inst                                                               0x00D3
#define RGMII_PAD_DP_shift                                                           (4)
#define RGMII_PAD_DP_mask                                                            (0x00000070)
#define RGMII_PAD_DP(data)                                                           (0x00000070&((data)<<4))
#define RGMII_PAD_DP_src(data)                                                       ((0x00000070&(data))>>4)
#define RGMII_PAD_get_DP(data)                                                       ((0x00000070&(data))>>4)
#define RGMII_PAD_DN_shift                                                           (0)
#define RGMII_PAD_DN_mask                                                            (0x00000007)
#define RGMII_PAD_DN(data)                                                           (0x00000007&((data)<<0))
#define RGMII_PAD_DN_src(data)                                                       ((0x00000007&(data))>>0)
#define RGMII_PAD_get_DN(data)                                                       ((0x00000007&(data))>>0)


#define CRT_MUXPAD0                                                                  0x98000360
#define CRT_MUXPAD0_reg_addr                                                         "0x98000360"
#define CRT_MUXPAD0_reg                                                              0x98000360
#define CRT_set_MUXPAD0_reg(data)   (*((volatile unsigned int*) MUXPAD0_reg)=data)   
#define CRT_get_MUXPAD0_reg   (*((volatile unsigned int*) MUXPAD0_reg))              
#define CRT_MUXPAD0_inst_adr                                                         "0x00D8"
#define CRT_MUXPAD0_inst                                                             0x00D8
#define MUXPAD0_nf_dd_7_shift                                                        (30)
#define MUXPAD0_nf_dd_7_mask                                                         (0xC0000000)
#define MUXPAD0_nf_dd_7(data)                                                        (0xC0000000&((data)<<30))
#define MUXPAD0_nf_dd_7_src(data)                                                    ((0xC0000000&(data))>>30)
#define MUXPAD0_get_nf_dd_7(data)                                                    ((0xC0000000&(data))>>30)
#define MUXPAD0_nf_dd_6_shift                                                        (28)
#define MUXPAD0_nf_dd_6_mask                                                         (0x30000000)
#define MUXPAD0_nf_dd_6(data)                                                        (0x30000000&((data)<<28))
#define MUXPAD0_nf_dd_6_src(data)                                                    ((0x30000000&(data))>>28)
#define MUXPAD0_get_nf_dd_6(data)                                                    ((0x30000000&(data))>>28)
#define MUXPAD0_nf_dd_5_shift                                                        (26)
#define MUXPAD0_nf_dd_5_mask                                                         (0x0C000000)
#define MUXPAD0_nf_dd_5(data)                                                        (0x0C000000&((data)<<26))
#define MUXPAD0_nf_dd_5_src(data)                                                    ((0x0C000000&(data))>>26)
#define MUXPAD0_get_nf_dd_5(data)                                                    ((0x0C000000&(data))>>26)
#define MUXPAD0_nf_dd_4_shift                                                        (24)
#define MUXPAD0_nf_dd_4_mask                                                         (0x03000000)
#define MUXPAD0_nf_dd_4(data)                                                        (0x03000000&((data)<<24))
#define MUXPAD0_nf_dd_4_src(data)                                                    ((0x03000000&(data))>>24)
#define MUXPAD0_get_nf_dd_4(data)                                                    ((0x03000000&(data))>>24)
#define MUXPAD0_nf_dd_3_shift                                                        (22)
#define MUXPAD0_nf_dd_3_mask                                                         (0x00C00000)
#define MUXPAD0_nf_dd_3(data)                                                        (0x00C00000&((data)<<22))
#define MUXPAD0_nf_dd_3_src(data)                                                    ((0x00C00000&(data))>>22)
#define MUXPAD0_get_nf_dd_3(data)                                                    ((0x00C00000&(data))>>22)
#define MUXPAD0_nf_dd_2_shift                                                        (20)
#define MUXPAD0_nf_dd_2_mask                                                         (0x00300000)
#define MUXPAD0_nf_dd_2(data)                                                        (0x00300000&((data)<<20))
#define MUXPAD0_nf_dd_2_src(data)                                                    ((0x00300000&(data))>>20)
#define MUXPAD0_get_nf_dd_2(data)                                                    ((0x00300000&(data))>>20)
#define MUXPAD0_nf_dd_1_shift                                                        (18)
#define MUXPAD0_nf_dd_1_mask                                                         (0x000C0000)
#define MUXPAD0_nf_dd_1(data)                                                        (0x000C0000&((data)<<18))
#define MUXPAD0_nf_dd_1_src(data)                                                    ((0x000C0000&(data))>>18)
#define MUXPAD0_get_nf_dd_1(data)                                                    ((0x000C0000&(data))>>18)
#define MUXPAD0_nf_dd_0_shift                                                        (16)
#define MUXPAD0_nf_dd_0_mask                                                         (0x00030000)
#define MUXPAD0_nf_dd_0(data)                                                        (0x00030000&((data)<<16))
#define MUXPAD0_nf_dd_0_src(data)                                                    ((0x00030000&(data))>>16)
#define MUXPAD0_get_nf_dd_0(data)                                                    ((0x00030000&(data))>>16)
#define MUXPAD0_nf_ce_n_1_shift                                                      (14)
#define MUXPAD0_nf_ce_n_1_mask                                                       (0x0000C000)
#define MUXPAD0_nf_ce_n_1(data)                                                      (0x0000C000&((data)<<14))
#define MUXPAD0_nf_ce_n_1_src(data)                                                  ((0x0000C000&(data))>>14)
#define MUXPAD0_get_nf_ce_n_1(data)                                                  ((0x0000C000&(data))>>14)
#define MUXPAD0_nf_ce_n_0_shift                                                      (12)
#define MUXPAD0_nf_ce_n_0_mask                                                       (0x00003000)
#define MUXPAD0_nf_ce_n_0(data)                                                      (0x00003000&((data)<<12))
#define MUXPAD0_nf_ce_n_0_src(data)                                                  ((0x00003000&(data))>>12)
#define MUXPAD0_get_nf_ce_n_0(data)                                                  ((0x00003000&(data))>>12)
#define MUXPAD0_nf_cle_shift                                                         (10)
#define MUXPAD0_nf_cle_mask                                                          (0x00000C00)
#define MUXPAD0_nf_cle(data)                                                         (0x00000C00&((data)<<10))
#define MUXPAD0_nf_cle_src(data)                                                     ((0x00000C00&(data))>>10)
#define MUXPAD0_get_nf_cle(data)                                                     ((0x00000C00&(data))>>10)
#define MUXPAD0_nf_ale_shift                                                         (8)
#define MUXPAD0_nf_ale_mask                                                          (0x00000300)
#define MUXPAD0_nf_ale(data)                                                         (0x00000300&((data)<<8))
#define MUXPAD0_nf_ale_src(data)                                                     ((0x00000300&(data))>>8)
#define MUXPAD0_get_nf_ale(data)                                                     ((0x00000300&(data))>>8)
#define MUXPAD0_nf_wr_n_shift                                                        (6)
#define MUXPAD0_nf_wr_n_mask                                                         (0x000000C0)
#define MUXPAD0_nf_wr_n(data)                                                        (0x000000C0&((data)<<6))
#define MUXPAD0_nf_wr_n_src(data)                                                    ((0x000000C0&(data))>>6)
#define MUXPAD0_get_nf_wr_n(data)                                                    ((0x000000C0&(data))>>6)
#define MUXPAD0_nf_rd_n_shift                                                        (4)
#define MUXPAD0_nf_rd_n_mask                                                         (0x00000030)
#define MUXPAD0_nf_rd_n(data)                                                        (0x00000030&((data)<<4))
#define MUXPAD0_nf_rd_n_src(data)                                                    ((0x00000030&(data))>>4)
#define MUXPAD0_get_nf_rd_n(data)                                                    ((0x00000030&(data))>>4)
#define MUXPAD0_nf_rdy_shift                                                         (2)
#define MUXPAD0_nf_rdy_mask                                                          (0x0000000C)
#define MUXPAD0_nf_rdy(data)                                                         (0x0000000C&((data)<<2))
#define MUXPAD0_nf_rdy_src(data)                                                     ((0x0000000C&(data))>>2)
#define MUXPAD0_get_nf_rdy(data)                                                     ((0x0000000C&(data))>>2)


#define CRT_MUXPAD1                                                                   0x98000364
#define CRT_MUXPAD1_reg_addr                                                          "0x98000364"
#define CRT_MUXPAD1_reg                                                               0x98000364
#define CRT_set_MUXPAD1_reg(data)   (*((volatile unsigned int*) MUXPAD1_reg)=data)    
#define CRT_get_MUXPAD1_reg   (*((volatile unsigned int*) MUXPAD1_reg))               
#define CRT_MUXPAD1_inst_adr                                                          "0x00D9"
#define CRT_MUXPAD1_inst                                                              0x00D9
#define MUXPAD1_mmc_data_3_shift                                                     (30)
#define MUXPAD1_mmc_data_3_mask                                                      (0xC0000000)
#define MUXPAD1_mmc_data_3(data)                                                     (0xC0000000&((data)<<30))
#define MUXPAD1_mmc_data_3_src(data)                                                 ((0xC0000000&(data))>>30)
#define MUXPAD1_get_mmc_data_3(data)                                                 ((0xC0000000&(data))>>30)
#define MUXPAD1_mmc_data_2_shift                                                     (28)
#define MUXPAD1_mmc_data_2_mask                                                      (0x30000000)
#define MUXPAD1_mmc_data_2(data)                                                     (0x30000000&((data)<<28))
#define MUXPAD1_mmc_data_2_src(data)                                                 ((0x30000000&(data))>>28)
#define MUXPAD1_get_mmc_data_2(data)                                                 ((0x30000000&(data))>>28)
#define MUXPAD1_mmc_data_1_shift                                                     (26)
#define MUXPAD1_mmc_data_1_mask                                                      (0x0C000000)
#define MUXPAD1_mmc_data_1(data)                                                     (0x0C000000&((data)<<26))
#define MUXPAD1_mmc_data_1_src(data)                                                 ((0x0C000000&(data))>>26)
#define MUXPAD1_get_mmc_data_1(data)                                                 ((0x0C000000&(data))>>26)
#define MUXPAD1_mmc_data_0_shift                                                     (24)
#define MUXPAD1_mmc_data_0_mask                                                      (0x03000000)
#define MUXPAD1_mmc_data_0(data)                                                     (0x03000000&((data)<<24))
#define MUXPAD1_mmc_data_0_src(data)                                                 ((0x03000000&(data))>>24)
#define MUXPAD1_get_mmc_data_0(data)                                                 ((0x03000000&(data))>>24)
#define MUXPAD1_mmc_cd_shift                                                         (22)
#define MUXPAD1_mmc_cd_mask                                                          (0x00C00000)
#define MUXPAD1_mmc_cd(data)                                                         (0x00C00000&((data)<<22))
#define MUXPAD1_mmc_cd_src(data)                                                     ((0x00C00000&(data))>>22)
#define MUXPAD1_get_mmc_cd(data)                                                     ((0x00C00000&(data))>>22)
#define MUXPAD1_mmc_wp_shift                                                         (20)
#define MUXPAD1_mmc_wp_mask                                                          (0x00300000)
#define MUXPAD1_mmc_wp(data)                                                         (0x00300000&((data)<<20))
#define MUXPAD1_mmc_wp_src(data)                                                     ((0x00300000&(data))>>20)
#define MUXPAD1_get_mmc_wp(data)                                                     ((0x00300000&(data))>>20)
#define MUXPAD1_mmc_clk_shift                                                        (18)
#define MUXPAD1_mmc_clk_mask                                                         (0x000C0000)
#define MUXPAD1_mmc_clk(data)                                                        (0x000C0000&((data)<<18))
#define MUXPAD1_mmc_clk_src(data)                                                    ((0x000C0000&(data))>>18)
#define MUXPAD1_get_mmc_clk(data)                                                    ((0x000C0000&(data))>>18)
#define MUXPAD1_mmc_cmd_shift                                                        (16)
#define MUXPAD1_mmc_cmd_mask                                                         (0x00030000)
#define MUXPAD1_mmc_cmd(data)                                                        (0x00030000&((data)<<16))
#define MUXPAD1_mmc_cmd_src(data)                                                    ((0x00030000&(data))>>16)
#define MUXPAD1_get_mmc_cmd(data)                                                    ((0x00030000&(data))>>16)
#define MUXPAD1_sdio_data_3_shift                                                    (10)
#define MUXPAD1_sdio_data_3_mask                                                     (0x00000C00)
#define MUXPAD1_sdio_data_3(data)                                                    (0x00000C00&((data)<<10))
#define MUXPAD1_sdio_data_3_src(data)                                                ((0x00000C00&(data))>>10)
#define MUXPAD1_get_sdio_data_3(data)                                                ((0x00000C00&(data))>>10)
#define MUXPAD1_sdio_data_2_shift                                                    (8)
#define MUXPAD1_sdio_data_2_mask                                                     (0x00000300)
#define MUXPAD1_sdio_data_2(data)                                                    (0x00000300&((data)<<8))
#define MUXPAD1_sdio_data_2_src(data)                                                ((0x00000300&(data))>>8)
#define MUXPAD1_get_sdio_data_2(data)                                                ((0x00000300&(data))>>8)
#define MUXPAD1_sdio_data_1_shift                                                    (6)
#define MUXPAD1_sdio_data_1_mask                                                     (0x000000C0)
#define MUXPAD1_sdio_data_1(data)                                                    (0x000000C0&((data)<<6))
#define MUXPAD1_sdio_data_1_src(data)                                                ((0x000000C0&(data))>>6)
#define MUXPAD1_get_sdio_data_1(data)                                                ((0x000000C0&(data))>>6)
#define MUXPAD1_sdio_data_0_shift                                                    (4)
#define MUXPAD1_sdio_data_0_mask                                                     (0x00000030)
#define MUXPAD1_sdio_data_0(data)                                                    (0x00000030&((data)<<4))
#define MUXPAD1_sdio_data_0_src(data)                                                ((0x00000030&(data))>>4)
#define MUXPAD1_get_sdio_data_0(data)                                                ((0x00000030&(data))>>4)
#define MUXPAD1_sdio_clk_shift                                                       (2)
#define MUXPAD1_sdio_clk_mask                                                        (0x0000000C)
#define MUXPAD1_sdio_clk(data)                                                       (0x0000000C&((data)<<2))
#define MUXPAD1_sdio_clk_src(data)                                                   ((0x0000000C&(data))>>2)
#define MUXPAD1_get_sdio_clk(data)                                                   ((0x0000000C&(data))>>2)
#define MUXPAD1_sdio_cmd_shift                                                       (0)
#define MUXPAD1_sdio_cmd_mask                                                        (0x00000003)
#define MUXPAD1_sdio_cmd(data)                                                       (0x00000003&((data)<<0))
#define MUXPAD1_sdio_cmd_src(data)                                                   ((0x00000003&(data))>>0)
#define MUXPAD1_get_sdio_cmd(data)                                                   ((0x00000003&(data))>>0)


#define MUXPAD2                                                                      0x98000368
#define MUXPAD2_reg_addr                                                             "0x98000368"
#define MUXPAD2_reg                                                                  0x98000368
#define set_MUXPAD2_reg(data)   (*((volatile unsigned int*) MUXPAD2_reg)=data)
#define get_MUXPAD2_reg   (*((volatile unsigned int*) MUXPAD2_reg))
#define MUXPAD2_inst_adr                                                             "0x00DA"
#define MUXPAD2_inst                                                                 0x00DA
#define MUXPAD2_tp1_clk_shift                                                        (22)
#define MUXPAD2_tp1_clk_mask                                                         (0x00C00000)
#define MUXPAD2_tp1_clk(data)                                                        (0x00C00000&((data)<<22))
#define MUXPAD2_tp1_clk_src(data)                                                    ((0x00C00000&(data))>>22)
#define MUXPAD2_get_tp1_clk(data)                                                    ((0x00C00000&(data))>>22)
#define MUXPAD2_tp1_valid_shift                                                      (20)
#define MUXPAD2_tp1_valid_mask                                                       (0x00300000)
#define MUXPAD2_tp1_valid(data)                                                      (0x00300000&((data)<<20))
#define MUXPAD2_tp1_valid_src(data)                                                  ((0x00300000&(data))>>20)
#define MUXPAD2_get_tp1_valid(data)                                                  ((0x00300000&(data))>>20)
#define MUXPAD2_tp1_sync_shift                                                       (18)
#define MUXPAD2_tp1_sync_mask                                                        (0x000C0000)
#define MUXPAD2_tp1_sync(data)                                                       (0x000C0000&((data)<<18))
#define MUXPAD2_tp1_sync_src(data)                                                   ((0x000C0000&(data))>>18)
#define MUXPAD2_get_tp1_sync(data)                                                   ((0x000C0000&(data))>>18)
#define MUXPAD2_tp1_data_shift                                                       (16)
#define MUXPAD2_tp1_data_mask                                                        (0x00030000)
#define MUXPAD2_tp1_data(data)                                                       (0x00030000&((data)<<16))
#define MUXPAD2_tp1_data_src(data)                                                   ((0x00030000&(data))>>16)
#define MUXPAD2_get_tp1_data(data)                                                   ((0x00030000&(data))>>16)
#define MUXPAD2_tp0_clk_shift                                                        (6)
#define MUXPAD2_tp0_clk_mask                                                         (0x000000C0)
#define MUXPAD2_tp0_clk(data)                                                        (0x000000C0&((data)<<6))
#define MUXPAD2_tp0_clk_src(data)                                                    ((0x000000C0&(data))>>6)
#define MUXPAD2_get_tp0_clk(data)                                                    ((0x000000C0&(data))>>6)
#define MUXPAD2_tp0_valid_shift                                                      (4)
#define MUXPAD2_tp0_valid_mask                                                       (0x00000030)
#define MUXPAD2_tp0_valid(data)                                                      (0x00000030&((data)<<4))
#define MUXPAD2_tp0_valid_src(data)                                                  ((0x00000030&(data))>>4)
#define MUXPAD2_get_tp0_valid(data)                                                  ((0x00000030&(data))>>4)
#define MUXPAD2_tp0_sync_shift                                                       (2)
#define MUXPAD2_tp0_sync_mask                                                        (0x0000000C)
#define MUXPAD2_tp0_sync(data)                                                       (0x0000000C&((data)<<2))
#define MUXPAD2_tp0_sync_src(data)                                                   ((0x0000000C&(data))>>2)
#define MUXPAD2_get_tp0_sync(data)                                                   ((0x0000000C&(data))>>2)
#define MUXPAD2_tp0_data_shift                                                       (0)
#define MUXPAD2_tp0_data_mask                                                        (0x00000003)
#define MUXPAD2_tp0_data(data)                                                       (0x00000003&((data)<<0))
#define MUXPAD2_tp0_data_src(data)                                                   ((0x00000003&(data))>>0)
#define MUXPAD2_get_tp0_data(data)                                                   ((0x00000003&(data))>>0)


#define MUXPAD3                                                                      0x9800036C
#define MUXPAD3_reg_addr                                                             "0x9800036C"
#define MUXPAD3_reg                                                                  0x9800036C
#define set_MUXPAD3_reg(data)   (*((volatile unsigned int*) MUXPAD3_reg)=data)
#define get_MUXPAD3_reg   (*((volatile unsigned int*) MUXPAD3_reg))
#define MUXPAD3_inst_adr                                                             "0x00DB"
#define MUXPAD3_inst                                                                 0x00DB
#define MUXPAD3_sensor_cko_0_shift                                                   (30)
#define MUXPAD3_sensor_cko_0_mask                                                    (0xC0000000)
#define MUXPAD3_sensor_cko_0(data)                                                   (0xC0000000&((data)<<30))
#define MUXPAD3_sensor_cko_0_src(data)                                               ((0xC0000000&(data))>>30)
#define MUXPAD3_get_sensor_cko_0(data)                                               ((0xC0000000&(data))>>30)
#define MUXPAD3_sensor_cko_1_shift                                                   (28)
#define MUXPAD3_sensor_cko_1_mask                                                    (0x30000000)
#define MUXPAD3_sensor_cko_1(data)                                                   (0x30000000&((data)<<28))
#define MUXPAD3_sensor_cko_1_src(data)                                               ((0x30000000&(data))>>28)
#define MUXPAD3_get_sensor_cko_1(data)                                               ((0x30000000&(data))>>28)
#define MUXPAD3_sensor_rst_shift                                                     (26)
#define MUXPAD3_sensor_rst_mask                                                      (0x0C000000)
#define MUXPAD3_sensor_rst(data)                                                     (0x0C000000&((data)<<26))
#define MUXPAD3_sensor_rst_src(data)                                                 ((0x0C000000&(data))>>26)
#define MUXPAD3_get_sensor_rst(data)                                                 ((0x0C000000&(data))>>26)
#define MUXPAD3_sensor_stb_0_shift                                                   (24)
#define MUXPAD3_sensor_stb_0_mask                                                    (0x03000000)
#define MUXPAD3_sensor_stb_0(data)                                                   (0x03000000&((data)<<24))
#define MUXPAD3_sensor_stb_0_src(data)                                               ((0x03000000&(data))>>24)
#define MUXPAD3_get_sensor_stb_0(data)                                               ((0x03000000&(data))>>24)
#define MUXPAD3_sensor_stb_1_shift                                                   (22)
#define MUXPAD3_sensor_stb_1_mask                                                    (0x00C00000)
#define MUXPAD3_sensor_stb_1(data)                                                   (0x00C00000&((data)<<22))
#define MUXPAD3_sensor_stb_1_src(data)                                               ((0x00C00000&(data))>>22)
#define MUXPAD3_get_sensor_stb_1(data)                                               ((0x00C00000&(data))>>22)
#define MUXPAD3_ejtag_scpu_loc_shift                                                 (20)
#define MUXPAD3_ejtag_scpu_loc_mask                                                  (0x00300000)
#define MUXPAD3_ejtag_scpu_loc(data)                                                 (0x00300000&((data)<<20))
#define MUXPAD3_ejtag_scpu_loc_src(data)                                             ((0x00300000&(data))>>20)
#define MUXPAD3_get_ejtag_scpu_loc(data)                                             ((0x00300000&(data))>>20)
#define MUXPAD3_hi_loc_shift                                                         (18)
#define MUXPAD3_hi_loc_mask                                                          (0x000C0000)
#define MUXPAD3_hi_loc(data)                                                         (0x000C0000&((data)<<18))
#define MUXPAD3_hi_loc_src(data)                                                     ((0x000C0000&(data))>>18)
#define MUXPAD3_get_hi_loc(data)                                                     ((0x000C0000&(data))>>18)
#define MUXPAD3_usb_id_shift                                                         (16)
#define MUXPAD3_usb_id_mask                                                          (0x00030000)
#define MUXPAD3_usb_id(data)                                                         (0x00030000&((data)<<16))
#define MUXPAD3_usb_id_src(data)                                                     ((0x00030000&(data))>>16)
#define MUXPAD3_get_usb_id(data)                                                     ((0x00030000&(data))>>16)
#define MUXPAD3_hdmi_hpd_shift                                                       (14)
#define MUXPAD3_hdmi_hpd_mask                                                        (0x0000C000)
#define MUXPAD3_hdmi_hpd(data)                                                       (0x0000C000&((data)<<14))
#define MUXPAD3_hdmi_hpd_src(data)                                                   ((0x0000C000&(data))>>14)
#define MUXPAD3_get_hdmi_hpd(data)                                                   ((0x0000C000&(data))>>14)
#define MUXPAD3_spdif_shift                                                          (12)
#define MUXPAD3_spdif_mask                                                           (0x00003000)
#define MUXPAD3_spdif(data)                                                          (0x00003000&((data)<<12))
#define MUXPAD3_spdif_src(data)                                                      ((0x00003000&(data))>>12)
#define MUXPAD3_get_spdif(data)                                                      ((0x00003000&(data))>>12)
#define MUXPAD3_i2c_scl_5_shift                                                      (10)
#define MUXPAD3_i2c_scl_5_mask                                                       (0x00000C00)
#define MUXPAD3_i2c_scl_5(data)                                                      (0x00000C00&((data)<<10))
#define MUXPAD3_i2c_scl_5_src(data)                                                  ((0x00000C00&(data))>>10)
#define MUXPAD3_get_i2c_scl_5(data)                                                  ((0x00000C00&(data))>>10)
#define MUXPAD3_i2c_sda_5_shift                                                      (8)
#define MUXPAD3_i2c_sda_5_mask                                                       (0x00000300)
#define MUXPAD3_i2c_sda_5(data)                                                      (0x00000300&((data)<<8))
#define MUXPAD3_i2c_sda_5_src(data)                                                  ((0x00000300&(data))>>8)
#define MUXPAD3_get_i2c_sda_5(data)                                                  ((0x00000300&(data))>>8)
#define MUXPAD3_i2c_scl_4_shift                                                      (6)
#define MUXPAD3_i2c_scl_4_mask                                                       (0x000000C0)
#define MUXPAD3_i2c_scl_4(data)                                                      (0x000000C0&((data)<<6))
#define MUXPAD3_i2c_scl_4_src(data)                                                  ((0x000000C0&(data))>>6)
#define MUXPAD3_get_i2c_scl_4(data)                                                  ((0x000000C0&(data))>>6)
#define MUXPAD3_i2c_sda_4_shift                                                      (4)
#define MUXPAD3_i2c_sda_4_mask                                                       (0x00000030)
#define MUXPAD3_i2c_sda_4(data)                                                      (0x00000030&((data)<<4))
#define MUXPAD3_i2c_sda_4_src(data)                                                  ((0x00000030&(data))>>4)
#define MUXPAD3_get_i2c_sda_4(data)                                                  ((0x00000030&(data))>>4)
#define MUXPAD3_i2c_scl_1_shift                                                      (2)
#define MUXPAD3_i2c_scl_1_mask                                                       (0x0000000C)
#define MUXPAD3_i2c_scl_1(data)                                                      (0x0000000C&((data)<<2))
#define MUXPAD3_i2c_scl_1_src(data)                                                  ((0x0000000C&(data))>>2)
#define MUXPAD3_get_i2c_scl_1(data)                                                  ((0x0000000C&(data))>>2)
#define MUXPAD3_i2c_sda_1_shift                                                      (0)
#define MUXPAD3_i2c_sda_1_mask                                                       (0x00000003)
#define MUXPAD3_i2c_sda_1(data)                                                      (0x00000003&((data)<<0))
#define MUXPAD3_i2c_sda_1_src(data)                                                  ((0x00000003&(data))>>0)
#define MUXPAD3_get_i2c_sda_1(data)                                                  ((0x00000003&(data))>>0)


#define MUXPAD4                                                                      0x98000370
#define MUXPAD4_reg_addr                                                             "0x98000370"
#define MUXPAD4_reg                                                                  0x98000370
#define set_MUXPAD4_reg(data)   (*((volatile unsigned int*) MUXPAD4_reg)=data)
#define get_MUXPAD4_reg   (*((volatile unsigned int*) MUXPAD4_reg))
#define MUXPAD4_inst_adr                                                             "0x00DC"
#define MUXPAD4_inst                                                                 0x00DC
#define MUXPAD4_gpio_8_shift                                                         (20)
#define MUXPAD4_gpio_8_mask                                                          (0x00300000)
#define MUXPAD4_gpio_8(data)                                                         (0x00300000&((data)<<20))
#define MUXPAD4_gpio_8_src(data)                                                     ((0x00300000&(data))>>20)
#define MUXPAD4_get_gpio_8(data)                                                     ((0x00300000&(data))>>20)
#define MUXPAD4_gpio_7_shift                                                         (18)
#define MUXPAD4_gpio_7_mask                                                          (0x000C0000)
#define MUXPAD4_gpio_7(data)                                                         (0x000C0000&((data)<<18))
#define MUXPAD4_gpio_7_src(data)                                                     ((0x000C0000&(data))>>18)
#define MUXPAD4_get_gpio_7(data)                                                     ((0x000C0000&(data))>>18)
#define MUXPAD4_gpio_6_shift                                                         (16)
#define MUXPAD4_gpio_6_mask                                                          (0x00030000)
#define MUXPAD4_gpio_6(data)                                                         (0x00030000&((data)<<16))
#define MUXPAD4_gpio_6_src(data)                                                     ((0x00030000&(data))>>16)
#define MUXPAD4_get_gpio_6(data)                                                     ((0x00030000&(data))>>16)
#define MUXPAD4_gpio_5_shift                                                         (14)
#define MUXPAD4_gpio_5_mask                                                          (0x0000C000)
#define MUXPAD4_gpio_5(data)                                                         (0x0000C000&((data)<<14))
#define MUXPAD4_gpio_5_src(data)                                                     ((0x0000C000&(data))>>14)
#define MUXPAD4_get_gpio_5(data)                                                     ((0x0000C000&(data))>>14)
#define MUXPAD4_gpio_4_shift                                                         (12)
#define MUXPAD4_gpio_4_mask                                                          (0x00003000)
#define MUXPAD4_gpio_4(data)                                                         (0x00003000&((data)<<12))
#define MUXPAD4_gpio_4_src(data)                                                     ((0x00003000&(data))>>12)
#define MUXPAD4_get_gpio_4(data)                                                     ((0x00003000&(data))>>12)
#define MUXPAD4_gpio_3_shift                                                         (9)
#define MUXPAD4_gpio_3_mask                                                          (0x00000E00)
#define MUXPAD4_gpio_3(data)                                                         (0x00000E00&((data)<<9))
#define MUXPAD4_gpio_3_src(data)                                                     ((0x00000E00&(data))>>9)
#define MUXPAD4_get_gpio_3(data)                                                     ((0x00000E00&(data))>>9)
#define MUXPAD4_gpio_2_shift                                                         (6)
#define MUXPAD4_gpio_2_mask                                                          (0x000001C0)
#define MUXPAD4_gpio_2(data)                                                         (0x000001C0&((data)<<6))
#define MUXPAD4_gpio_2_src(data)                                                     ((0x000001C0&(data))>>6)
#define MUXPAD4_get_gpio_2(data)                                                     ((0x000001C0&(data))>>6)
#define MUXPAD4_gpio_1_shift                                                         (3)
#define MUXPAD4_gpio_1_mask                                                          (0x00000038)
#define MUXPAD4_gpio_1(data)                                                         (0x00000038&((data)<<3))
#define MUXPAD4_gpio_1_src(data)                                                     ((0x00000038&(data))>>3)
#define MUXPAD4_get_gpio_1(data)                                                     ((0x00000038&(data))>>3)
#define MUXPAD4_gpio_0_shift                                                         (0)
#define MUXPAD4_gpio_0_mask                                                          (0x00000007)
#define MUXPAD4_gpio_0(data)                                                         (0x00000007&((data)<<0))
#define MUXPAD4_gpio_0_src(data)                                                     ((0x00000007&(data))>>0)
#define MUXPAD4_get_gpio_0(data)                                                     ((0x00000007&(data))>>0)


#define MUXPAD5                                                                      0x98000374
#define MUXPAD5_reg_addr                                                             "0x98000374"
#define MUXPAD5_reg                                                                  0x98000374
#define set_MUXPAD5_reg(data)   (*((volatile unsigned int*) MUXPAD5_reg)=data)
#define get_MUXPAD5_reg   (*((volatile unsigned int*) MUXPAD5_reg))
#define MUXPAD5_inst_adr                                                             "0x00DD"
#define MUXPAD5_inst                                                                 0x00DD
#define MUXPAD5_arm_trace_dbg_en_shift                                               (1)
#define MUXPAD5_arm_trace_dbg_en_mask                                                (0x00000002)
#define MUXPAD5_arm_trace_dbg_en(data)                                               (0x00000002&((data)<<1))
#define MUXPAD5_arm_trace_dbg_en_src(data)                                           ((0x00000002&(data))>>1)
#define MUXPAD5_get_arm_trace_dbg_en(data)                                           ((0x00000002&(data))>>1)
#define MUXPAD5_sf_en_shift                                                          (0)
#define MUXPAD5_sf_en_mask                                                           (0x00000001)
#define MUXPAD5_sf_en(data)                                                          (0x00000001&((data)<<0))
#define MUXPAD5_sf_en_src(data)                                                      ((0x00000001&(data))>>0)
#define MUXPAD5_get_sf_en(data)                                                      ((0x00000001&(data))>>0)


#define PFUNC_NF0                                                                    0x98000378
#define PFUNC_NF0_reg_addr                                                           "0x98000378"
#define PFUNC_NF0_reg                                                                0x98000378
#define set_PFUNC_NF0_reg(data)   (*((volatile unsigned int*) PFUNC_NF0_reg)=data)
#define get_PFUNC_NF0_reg   (*((volatile unsigned int*) PFUNC_NF0_reg))
#define PFUNC_NF0_inst_adr                                                           "0x00DE"
#define PFUNC_NF0_inst                                                               0x00DE
#define PFUNC_NF0_nf_cle_smt_shift                                                   (31)
#define PFUNC_NF0_nf_cle_smt_mask                                                    (0x80000000)
#define PFUNC_NF0_nf_cle_smt(data)                                                   (0x80000000&((data)<<31))
#define PFUNC_NF0_nf_cle_smt_src(data)                                               ((0x80000000&(data))>>31)
#define PFUNC_NF0_get_nf_cle_smt(data)                                               ((0x80000000&(data))>>31)
#define PFUNC_NF0_nf_cle_e2_shift                                                    (30)
#define PFUNC_NF0_nf_cle_e2_mask                                                     (0x40000000)
#define PFUNC_NF0_nf_cle_e2(data)                                                    (0x40000000&((data)<<30))
#define PFUNC_NF0_nf_cle_e2_src(data)                                                ((0x40000000&(data))>>30)
#define PFUNC_NF0_get_nf_cle_e2(data)                                                ((0x40000000&(data))>>30)
#define PFUNC_NF0_nf_cle_pud_en_shift                                                (29)
#define PFUNC_NF0_nf_cle_pud_en_mask                                                 (0x20000000)
#define PFUNC_NF0_nf_cle_pud_en(data)                                                (0x20000000&((data)<<29))
#define PFUNC_NF0_nf_cle_pud_en_src(data)                                            ((0x20000000&(data))>>29)
#define PFUNC_NF0_get_nf_cle_pud_en(data)                                            ((0x20000000&(data))>>29)
#define PFUNC_NF0_nf_cle_pud_sel_shift                                               (28)
#define PFUNC_NF0_nf_cle_pud_sel_mask                                                (0x10000000)
#define PFUNC_NF0_nf_cle_pud_sel(data)                                               (0x10000000&((data)<<28))
#define PFUNC_NF0_nf_cle_pud_sel_src(data)                                           ((0x10000000&(data))>>28)
#define PFUNC_NF0_get_nf_cle_pud_sel(data)                                           ((0x10000000&(data))>>28)
#define PFUNC_NF0_nf_wr_n_smt_shift                                                  (27)
#define PFUNC_NF0_nf_wr_n_smt_mask                                                   (0x08000000)
#define PFUNC_NF0_nf_wr_n_smt(data)                                                  (0x08000000&((data)<<27))
#define PFUNC_NF0_nf_wr_n_smt_src(data)                                              ((0x08000000&(data))>>27)
#define PFUNC_NF0_get_nf_wr_n_smt(data)                                              ((0x08000000&(data))>>27)
#define PFUNC_NF0_nf_wr_n_e2_shift                                                   (26)
#define PFUNC_NF0_nf_wr_n_e2_mask                                                    (0x04000000)
#define PFUNC_NF0_nf_wr_n_e2(data)                                                   (0x04000000&((data)<<26))
#define PFUNC_NF0_nf_wr_n_e2_src(data)                                               ((0x04000000&(data))>>26)
#define PFUNC_NF0_get_nf_wr_n_e2(data)                                               ((0x04000000&(data))>>26)
#define PFUNC_NF0_nf_wr_n_pud_en_shift                                               (25)
#define PFUNC_NF0_nf_wr_n_pud_en_mask                                                (0x02000000)
#define PFUNC_NF0_nf_wr_n_pud_en(data)                                               (0x02000000&((data)<<25))
#define PFUNC_NF0_nf_wr_n_pud_en_src(data)                                           ((0x02000000&(data))>>25)
#define PFUNC_NF0_get_nf_wr_n_pud_en(data)                                           ((0x02000000&(data))>>25)
#define PFUNC_NF0_nf_wr_n_pud_sel_shift                                              (24)
#define PFUNC_NF0_nf_wr_n_pud_sel_mask                                               (0x01000000)
#define PFUNC_NF0_nf_wr_n_pud_sel(data)                                              (0x01000000&((data)<<24))
#define PFUNC_NF0_nf_wr_n_pud_sel_src(data)                                          ((0x01000000&(data))>>24)
#define PFUNC_NF0_get_nf_wr_n_pud_sel(data)                                          ((0x01000000&(data))>>24)
#define PFUNC_NF0_nf_rd_n_smt_shift                                                  (23)
#define PFUNC_NF0_nf_rd_n_smt_mask                                                   (0x00800000)
#define PFUNC_NF0_nf_rd_n_smt(data)                                                  (0x00800000&((data)<<23))
#define PFUNC_NF0_nf_rd_n_smt_src(data)                                              ((0x00800000&(data))>>23)
#define PFUNC_NF0_get_nf_rd_n_smt(data)                                              ((0x00800000&(data))>>23)
#define PFUNC_NF0_nf_rd_n_e2_shift                                                   (22)
#define PFUNC_NF0_nf_rd_n_e2_mask                                                    (0x00400000)
#define PFUNC_NF0_nf_rd_n_e2(data)                                                   (0x00400000&((data)<<22))
#define PFUNC_NF0_nf_rd_n_e2_src(data)                                               ((0x00400000&(data))>>22)
#define PFUNC_NF0_get_nf_rd_n_e2(data)                                               ((0x00400000&(data))>>22)
#define PFUNC_NF0_nf_rd_n_pud_en_shift                                               (21)
#define PFUNC_NF0_nf_rd_n_pud_en_mask                                                (0x00200000)
#define PFUNC_NF0_nf_rd_n_pud_en(data)                                               (0x00200000&((data)<<21))
#define PFUNC_NF0_nf_rd_n_pud_en_src(data)                                           ((0x00200000&(data))>>21)
#define PFUNC_NF0_get_nf_rd_n_pud_en(data)                                           ((0x00200000&(data))>>21)
#define PFUNC_NF0_nf_rd_n_pud_sel_shift                                              (20)
#define PFUNC_NF0_nf_rd_n_pud_sel_mask                                               (0x00100000)
#define PFUNC_NF0_nf_rd_n_pud_sel(data)                                              (0x00100000&((data)<<20))
#define PFUNC_NF0_nf_rd_n_pud_sel_src(data)                                          ((0x00100000&(data))>>20)
#define PFUNC_NF0_get_nf_rd_n_pud_sel(data)                                          ((0x00100000&(data))>>20)
#define PFUNC_NF0_nf_rdy_smt_shift                                                   (19)
#define PFUNC_NF0_nf_rdy_smt_mask                                                    (0x00080000)
#define PFUNC_NF0_nf_rdy_smt(data)                                                   (0x00080000&((data)<<19))
#define PFUNC_NF0_nf_rdy_smt_src(data)                                               ((0x00080000&(data))>>19)
#define PFUNC_NF0_get_nf_rdy_smt(data)                                               ((0x00080000&(data))>>19)
#define PFUNC_NF0_nf_rdy_e2_shift                                                    (18)
#define PFUNC_NF0_nf_rdy_e2_mask                                                     (0x00040000)
#define PFUNC_NF0_nf_rdy_e2(data)                                                    (0x00040000&((data)<<18))
#define PFUNC_NF0_nf_rdy_e2_src(data)                                                ((0x00040000&(data))>>18)
#define PFUNC_NF0_get_nf_rdy_e2(data)                                                ((0x00040000&(data))>>18)
#define PFUNC_NF0_nf_rdy_pud_en_shift                                                (17)
#define PFUNC_NF0_nf_rdy_pud_en_mask                                                 (0x00020000)
#define PFUNC_NF0_nf_rdy_pud_en(data)                                                (0x00020000&((data)<<17))
#define PFUNC_NF0_nf_rdy_pud_en_src(data)                                            ((0x00020000&(data))>>17)
#define PFUNC_NF0_get_nf_rdy_pud_en(data)                                            ((0x00020000&(data))>>17)
#define PFUNC_NF0_nf_rdy_pud_sel_shift                                               (16)
#define PFUNC_NF0_nf_rdy_pud_sel_mask                                                (0x00010000)
#define PFUNC_NF0_nf_rdy_pud_sel(data)                                               (0x00010000&((data)<<16))
#define PFUNC_NF0_nf_rdy_pud_sel_src(data)                                           ((0x00010000&(data))>>16)
#define PFUNC_NF0_get_nf_rdy_pud_sel(data)                                           ((0x00010000&(data))>>16)
#define PFUNC_NF0_nf_ce_n_1_smt_shift                                                (15)
#define PFUNC_NF0_nf_ce_n_1_smt_mask                                                 (0x00008000)
#define PFUNC_NF0_nf_ce_n_1_smt(data)                                                (0x00008000&((data)<<15))
#define PFUNC_NF0_nf_ce_n_1_smt_src(data)                                            ((0x00008000&(data))>>15)
#define PFUNC_NF0_get_nf_ce_n_1_smt(data)                                            ((0x00008000&(data))>>15)
#define PFUNC_NF0_nf_ce_n_1_e2_shift                                                 (14)
#define PFUNC_NF0_nf_ce_n_1_e2_mask                                                  (0x00004000)
#define PFUNC_NF0_nf_ce_n_1_e2(data)                                                 (0x00004000&((data)<<14))
#define PFUNC_NF0_nf_ce_n_1_e2_src(data)                                             ((0x00004000&(data))>>14)
#define PFUNC_NF0_get_nf_ce_n_1_e2(data)                                             ((0x00004000&(data))>>14)
#define PFUNC_NF0_nf_ce_n_1_pud_en_shift                                             (13)
#define PFUNC_NF0_nf_ce_n_1_pud_en_mask                                              (0x00002000)
#define PFUNC_NF0_nf_ce_n_1_pud_en(data)                                             (0x00002000&((data)<<13))
#define PFUNC_NF0_nf_ce_n_1_pud_en_src(data)                                         ((0x00002000&(data))>>13)
#define PFUNC_NF0_get_nf_ce_n_1_pud_en(data)                                         ((0x00002000&(data))>>13)
#define PFUNC_NF0_nf_ce_n_1_pud_sel_shift                                            (12)
#define PFUNC_NF0_nf_ce_n_1_pud_sel_mask                                             (0x00001000)
#define PFUNC_NF0_nf_ce_n_1_pud_sel(data)                                            (0x00001000&((data)<<12))
#define PFUNC_NF0_nf_ce_n_1_pud_sel_src(data)                                        ((0x00001000&(data))>>12)
#define PFUNC_NF0_get_nf_ce_n_1_pud_sel(data)                                        ((0x00001000&(data))>>12)
#define PFUNC_NF0_nf_ce_n_0_smt_shift                                                (11)
#define PFUNC_NF0_nf_ce_n_0_smt_mask                                                 (0x00000800)
#define PFUNC_NF0_nf_ce_n_0_smt(data)                                                (0x00000800&((data)<<11))
#define PFUNC_NF0_nf_ce_n_0_smt_src(data)                                            ((0x00000800&(data))>>11)
#define PFUNC_NF0_get_nf_ce_n_0_smt(data)                                            ((0x00000800&(data))>>11)
#define PFUNC_NF0_nf_ce_n_0_e2_shift                                                 (10)
#define PFUNC_NF0_nf_ce_n_0_e2_mask                                                  (0x00000400)
#define PFUNC_NF0_nf_ce_n_0_e2(data)                                                 (0x00000400&((data)<<10))
#define PFUNC_NF0_nf_ce_n_0_e2_src(data)                                             ((0x00000400&(data))>>10)
#define PFUNC_NF0_get_nf_ce_n_0_e2(data)                                             ((0x00000400&(data))>>10)
#define PFUNC_NF0_nf_ce_n_0_pud_en_shift                                             (9)
#define PFUNC_NF0_nf_ce_n_0_pud_en_mask                                              (0x00000200)
#define PFUNC_NF0_nf_ce_n_0_pud_en(data)                                             (0x00000200&((data)<<9))
#define PFUNC_NF0_nf_ce_n_0_pud_en_src(data)                                         ((0x00000200&(data))>>9)
#define PFUNC_NF0_get_nf_ce_n_0_pud_en(data)                                         ((0x00000200&(data))>>9)
#define PFUNC_NF0_nf_ce_n_0_pud_sel_shift                                            (8)
#define PFUNC_NF0_nf_ce_n_0_pud_sel_mask                                             (0x00000100)
#define PFUNC_NF0_nf_ce_n_0_pud_sel(data)                                            (0x00000100&((data)<<8))
#define PFUNC_NF0_nf_ce_n_0_pud_sel_src(data)                                        ((0x00000100&(data))>>8)
#define PFUNC_NF0_get_nf_ce_n_0_pud_sel(data)                                        ((0x00000100&(data))>>8)
#define PFUNC_NF0_nf_ale_smt_shift                                                   (7)
#define PFUNC_NF0_nf_ale_smt_mask                                                    (0x00000080)
#define PFUNC_NF0_nf_ale_smt(data)                                                   (0x00000080&((data)<<7))
#define PFUNC_NF0_nf_ale_smt_src(data)                                               ((0x00000080&(data))>>7)
#define PFUNC_NF0_get_nf_ale_smt(data)                                               ((0x00000080&(data))>>7)
#define PFUNC_NF0_nf_ale_e2_shift                                                    (6)
#define PFUNC_NF0_nf_ale_e2_mask                                                     (0x00000040)
#define PFUNC_NF0_nf_ale_e2(data)                                                    (0x00000040&((data)<<6))
#define PFUNC_NF0_nf_ale_e2_src(data)                                                ((0x00000040&(data))>>6)
#define PFUNC_NF0_get_nf_ale_e2(data)                                                ((0x00000040&(data))>>6)
#define PFUNC_NF0_nf_ale_pud_en_shift                                                (5)
#define PFUNC_NF0_nf_ale_pud_en_mask                                                 (0x00000020)
#define PFUNC_NF0_nf_ale_pud_en(data)                                                (0x00000020&((data)<<5))
#define PFUNC_NF0_nf_ale_pud_en_src(data)                                            ((0x00000020&(data))>>5)
#define PFUNC_NF0_get_nf_ale_pud_en(data)                                            ((0x00000020&(data))>>5)
#define PFUNC_NF0_nf_ale_pud_sel_shift                                               (4)
#define PFUNC_NF0_nf_ale_pud_sel_mask                                                (0x00000010)
#define PFUNC_NF0_nf_ale_pud_sel(data)                                               (0x00000010&((data)<<4))
#define PFUNC_NF0_nf_ale_pud_sel_src(data)                                           ((0x00000010&(data))>>4)
#define PFUNC_NF0_get_nf_ale_pud_sel(data)                                           ((0x00000010&(data))>>4)


#define PFUNC_NF1                                                                    0x9800037C
#define PFUNC_NF1_reg_addr                                                           "0x9800037C"
#define PFUNC_NF1_reg                                                                0x9800037C
#define set_PFUNC_NF1_reg(data)   (*((volatile unsigned int*) PFUNC_NF1_reg)=data)
#define get_PFUNC_NF1_reg   (*((volatile unsigned int*) PFUNC_NF1_reg))
#define PFUNC_NF1_inst_adr                                                           "0x00DF"
#define PFUNC_NF1_inst                                                               0x00DF
#define PFUNC_NF1_nf_dd_7_smt_shift                                                  (31)
#define PFUNC_NF1_nf_dd_7_smt_mask                                                   (0x80000000)
#define PFUNC_NF1_nf_dd_7_smt(data)                                                  (0x80000000&((data)<<31))
#define PFUNC_NF1_nf_dd_7_smt_src(data)                                              ((0x80000000&(data))>>31)
#define PFUNC_NF1_get_nf_dd_7_smt(data)                                              ((0x80000000&(data))>>31)
#define PFUNC_NF1_nf_dd_7_e2_shift                                                   (30)
#define PFUNC_NF1_nf_dd_7_e2_mask                                                    (0x40000000)
#define PFUNC_NF1_nf_dd_7_e2(data)                                                   (0x40000000&((data)<<30))
#define PFUNC_NF1_nf_dd_7_e2_src(data)                                               ((0x40000000&(data))>>30)
#define PFUNC_NF1_get_nf_dd_7_e2(data)                                               ((0x40000000&(data))>>30)
#define PFUNC_NF1_nf_dd_7_pud_en_shift                                               (29)
#define PFUNC_NF1_nf_dd_7_pud_en_mask                                                (0x20000000)
#define PFUNC_NF1_nf_dd_7_pud_en(data)                                               (0x20000000&((data)<<29))
#define PFUNC_NF1_nf_dd_7_pud_en_src(data)                                           ((0x20000000&(data))>>29)
#define PFUNC_NF1_get_nf_dd_7_pud_en(data)                                           ((0x20000000&(data))>>29)
#define PFUNC_NF1_nf_dd_7_pud_sel_shift                                              (28)
#define PFUNC_NF1_nf_dd_7_pud_sel_mask                                               (0x10000000)
#define PFUNC_NF1_nf_dd_7_pud_sel(data)                                              (0x10000000&((data)<<28))
#define PFUNC_NF1_nf_dd_7_pud_sel_src(data)                                          ((0x10000000&(data))>>28)
#define PFUNC_NF1_get_nf_dd_7_pud_sel(data)                                          ((0x10000000&(data))>>28)
#define PFUNC_NF1_nf_dd_6_smt_shift                                                  (27)
#define PFUNC_NF1_nf_dd_6_smt_mask                                                   (0x08000000)
#define PFUNC_NF1_nf_dd_6_smt(data)                                                  (0x08000000&((data)<<27))
#define PFUNC_NF1_nf_dd_6_smt_src(data)                                              ((0x08000000&(data))>>27)
#define PFUNC_NF1_get_nf_dd_6_smt(data)                                              ((0x08000000&(data))>>27)
#define PFUNC_NF1_nf_dd_6_e2_shift                                                   (26)
#define PFUNC_NF1_nf_dd_6_e2_mask                                                    (0x04000000)
#define PFUNC_NF1_nf_dd_6_e2(data)                                                   (0x04000000&((data)<<26))
#define PFUNC_NF1_nf_dd_6_e2_src(data)                                               ((0x04000000&(data))>>26)
#define PFUNC_NF1_get_nf_dd_6_e2(data)                                               ((0x04000000&(data))>>26)
#define PFUNC_NF1_nf_dd_6_pud_en_shift                                               (25)
#define PFUNC_NF1_nf_dd_6_pud_en_mask                                                (0x02000000)
#define PFUNC_NF1_nf_dd_6_pud_en(data)                                               (0x02000000&((data)<<25))
#define PFUNC_NF1_nf_dd_6_pud_en_src(data)                                           ((0x02000000&(data))>>25)
#define PFUNC_NF1_get_nf_dd_6_pud_en(data)                                           ((0x02000000&(data))>>25)
#define PFUNC_NF1_nf_dd_6_pud_sel_shift                                              (24)
#define PFUNC_NF1_nf_dd_6_pud_sel_mask                                               (0x01000000)
#define PFUNC_NF1_nf_dd_6_pud_sel(data)                                              (0x01000000&((data)<<24))
#define PFUNC_NF1_nf_dd_6_pud_sel_src(data)                                          ((0x01000000&(data))>>24)
#define PFUNC_NF1_get_nf_dd_6_pud_sel(data)                                          ((0x01000000&(data))>>24)
#define PFUNC_NF1_nf_dd_5_smt_shift                                                  (23)
#define PFUNC_NF1_nf_dd_5_smt_mask                                                   (0x00800000)
#define PFUNC_NF1_nf_dd_5_smt(data)                                                  (0x00800000&((data)<<23))
#define PFUNC_NF1_nf_dd_5_smt_src(data)                                              ((0x00800000&(data))>>23)
#define PFUNC_NF1_get_nf_dd_5_smt(data)                                              ((0x00800000&(data))>>23)
#define PFUNC_NF1_nf_dd_5_e2_shift                                                   (22)
#define PFUNC_NF1_nf_dd_5_e2_mask                                                    (0x00400000)
#define PFUNC_NF1_nf_dd_5_e2(data)                                                   (0x00400000&((data)<<22))
#define PFUNC_NF1_nf_dd_5_e2_src(data)                                               ((0x00400000&(data))>>22)
#define PFUNC_NF1_get_nf_dd_5_e2(data)                                               ((0x00400000&(data))>>22)
#define PFUNC_NF1_nf_dd_5_pud_en_shift                                               (21)
#define PFUNC_NF1_nf_dd_5_pud_en_mask                                                (0x00200000)
#define PFUNC_NF1_nf_dd_5_pud_en(data)                                               (0x00200000&((data)<<21))
#define PFUNC_NF1_nf_dd_5_pud_en_src(data)                                           ((0x00200000&(data))>>21)
#define PFUNC_NF1_get_nf_dd_5_pud_en(data)                                           ((0x00200000&(data))>>21)
#define PFUNC_NF1_nf_dd_5_pud_sel_shift                                              (20)
#define PFUNC_NF1_nf_dd_5_pud_sel_mask                                               (0x00100000)
#define PFUNC_NF1_nf_dd_5_pud_sel(data)                                              (0x00100000&((data)<<20))
#define PFUNC_NF1_nf_dd_5_pud_sel_src(data)                                          ((0x00100000&(data))>>20)
#define PFUNC_NF1_get_nf_dd_5_pud_sel(data)                                          ((0x00100000&(data))>>20)
#define PFUNC_NF1_nf_dd_4_smt_shift                                                  (19)
#define PFUNC_NF1_nf_dd_4_smt_mask                                                   (0x00080000)
#define PFUNC_NF1_nf_dd_4_smt(data)                                                  (0x00080000&((data)<<19))
#define PFUNC_NF1_nf_dd_4_smt_src(data)                                              ((0x00080000&(data))>>19)
#define PFUNC_NF1_get_nf_dd_4_smt(data)                                              ((0x00080000&(data))>>19)
#define PFUNC_NF1_nf_dd_4_e2_shift                                                   (18)
#define PFUNC_NF1_nf_dd_4_e2_mask                                                    (0x00040000)
#define PFUNC_NF1_nf_dd_4_e2(data)                                                   (0x00040000&((data)<<18))
#define PFUNC_NF1_nf_dd_4_e2_src(data)                                               ((0x00040000&(data))>>18)
#define PFUNC_NF1_get_nf_dd_4_e2(data)                                               ((0x00040000&(data))>>18)
#define PFUNC_NF1_nf_dd_4_pud_en_shift                                               (17)
#define PFUNC_NF1_nf_dd_4_pud_en_mask                                                (0x00020000)
#define PFUNC_NF1_nf_dd_4_pud_en(data)                                               (0x00020000&((data)<<17))
#define PFUNC_NF1_nf_dd_4_pud_en_src(data)                                           ((0x00020000&(data))>>17)
#define PFUNC_NF1_get_nf_dd_4_pud_en(data)                                           ((0x00020000&(data))>>17)
#define PFUNC_NF1_nf_dd_4_pud_sel_shift                                              (16)
#define PFUNC_NF1_nf_dd_4_pud_sel_mask                                               (0x00010000)
#define PFUNC_NF1_nf_dd_4_pud_sel(data)                                              (0x00010000&((data)<<16))
#define PFUNC_NF1_nf_dd_4_pud_sel_src(data)                                          ((0x00010000&(data))>>16)
#define PFUNC_NF1_get_nf_dd_4_pud_sel(data)                                          ((0x00010000&(data))>>16)
#define PFUNC_NF1_nf_dd_3_smt_shift                                                  (15)
#define PFUNC_NF1_nf_dd_3_smt_mask                                                   (0x00008000)
#define PFUNC_NF1_nf_dd_3_smt(data)                                                  (0x00008000&((data)<<15))
#define PFUNC_NF1_nf_dd_3_smt_src(data)                                              ((0x00008000&(data))>>15)
#define PFUNC_NF1_get_nf_dd_3_smt(data)                                              ((0x00008000&(data))>>15)
#define PFUNC_NF1_nf_dd_3_e2_shift                                                   (14)
#define PFUNC_NF1_nf_dd_3_e2_mask                                                    (0x00004000)
#define PFUNC_NF1_nf_dd_3_e2(data)                                                   (0x00004000&((data)<<14))
#define PFUNC_NF1_nf_dd_3_e2_src(data)                                               ((0x00004000&(data))>>14)
#define PFUNC_NF1_get_nf_dd_3_e2(data)                                               ((0x00004000&(data))>>14)
#define PFUNC_NF1_nf_dd_3_pud_en_shift                                               (13)
#define PFUNC_NF1_nf_dd_3_pud_en_mask                                                (0x00002000)
#define PFUNC_NF1_nf_dd_3_pud_en(data)                                               (0x00002000&((data)<<13))
#define PFUNC_NF1_nf_dd_3_pud_en_src(data)                                           ((0x00002000&(data))>>13)
#define PFUNC_NF1_get_nf_dd_3_pud_en(data)                                           ((0x00002000&(data))>>13)
#define PFUNC_NF1_nf_dd_3_pud_sel_shift                                              (12)
#define PFUNC_NF1_nf_dd_3_pud_sel_mask                                               (0x00001000)
#define PFUNC_NF1_nf_dd_3_pud_sel(data)                                              (0x00001000&((data)<<12))
#define PFUNC_NF1_nf_dd_3_pud_sel_src(data)                                          ((0x00001000&(data))>>12)
#define PFUNC_NF1_get_nf_dd_3_pud_sel(data)                                          ((0x00001000&(data))>>12)
#define PFUNC_NF1_nf_dd_2_smt_shift                                                  (11)
#define PFUNC_NF1_nf_dd_2_smt_mask                                                   (0x00000800)
#define PFUNC_NF1_nf_dd_2_smt(data)                                                  (0x00000800&((data)<<11))
#define PFUNC_NF1_nf_dd_2_smt_src(data)                                              ((0x00000800&(data))>>11)
#define PFUNC_NF1_get_nf_dd_2_smt(data)                                              ((0x00000800&(data))>>11)
#define PFUNC_NF1_nf_dd_2_e2_shift                                                   (10)
#define PFUNC_NF1_nf_dd_2_e2_mask                                                    (0x00000400)
#define PFUNC_NF1_nf_dd_2_e2(data)                                                   (0x00000400&((data)<<10))
#define PFUNC_NF1_nf_dd_2_e2_src(data)                                               ((0x00000400&(data))>>10)
#define PFUNC_NF1_get_nf_dd_2_e2(data)                                               ((0x00000400&(data))>>10)
#define PFUNC_NF1_nf_dd_2_pud_en_shift                                               (9)
#define PFUNC_NF1_nf_dd_2_pud_en_mask                                                (0x00000200)
#define PFUNC_NF1_nf_dd_2_pud_en(data)                                               (0x00000200&((data)<<9))
#define PFUNC_NF1_nf_dd_2_pud_en_src(data)                                           ((0x00000200&(data))>>9)
#define PFUNC_NF1_get_nf_dd_2_pud_en(data)                                           ((0x00000200&(data))>>9)
#define PFUNC_NF1_nf_dd_2_pud_sel_shift                                              (8)
#define PFUNC_NF1_nf_dd_2_pud_sel_mask                                               (0x00000100)
#define PFUNC_NF1_nf_dd_2_pud_sel(data)                                              (0x00000100&((data)<<8))
#define PFUNC_NF1_nf_dd_2_pud_sel_src(data)                                          ((0x00000100&(data))>>8)
#define PFUNC_NF1_get_nf_dd_2_pud_sel(data)                                          ((0x00000100&(data))>>8)
#define PFUNC_NF1_nf_dd_1_smt_shift                                                  (7)
#define PFUNC_NF1_nf_dd_1_smt_mask                                                   (0x00000080)
#define PFUNC_NF1_nf_dd_1_smt(data)                                                  (0x00000080&((data)<<7))
#define PFUNC_NF1_nf_dd_1_smt_src(data)                                              ((0x00000080&(data))>>7)
#define PFUNC_NF1_get_nf_dd_1_smt(data)                                              ((0x00000080&(data))>>7)
#define PFUNC_NF1_nf_dd_1_e2_shift                                                   (6)
#define PFUNC_NF1_nf_dd_1_e2_mask                                                    (0x00000040)
#define PFUNC_NF1_nf_dd_1_e2(data)                                                   (0x00000040&((data)<<6))
#define PFUNC_NF1_nf_dd_1_e2_src(data)                                               ((0x00000040&(data))>>6)
#define PFUNC_NF1_get_nf_dd_1_e2(data)                                               ((0x00000040&(data))>>6)
#define PFUNC_NF1_nf_dd_1_pud_en_shift                                               (5)
#define PFUNC_NF1_nf_dd_1_pud_en_mask                                                (0x00000020)
#define PFUNC_NF1_nf_dd_1_pud_en(data)                                               (0x00000020&((data)<<5))
#define PFUNC_NF1_nf_dd_1_pud_en_src(data)                                           ((0x00000020&(data))>>5)
#define PFUNC_NF1_get_nf_dd_1_pud_en(data)                                           ((0x00000020&(data))>>5)
#define PFUNC_NF1_nf_dd_1_pud_sel_shift                                              (4)
#define PFUNC_NF1_nf_dd_1_pud_sel_mask                                               (0x00000010)
#define PFUNC_NF1_nf_dd_1_pud_sel(data)                                              (0x00000010&((data)<<4))
#define PFUNC_NF1_nf_dd_1_pud_sel_src(data)                                          ((0x00000010&(data))>>4)
#define PFUNC_NF1_get_nf_dd_1_pud_sel(data)                                          ((0x00000010&(data))>>4)
#define PFUNC_NF1_nf_dd_0_smt_shift                                                  (3)
#define PFUNC_NF1_nf_dd_0_smt_mask                                                   (0x00000008)
#define PFUNC_NF1_nf_dd_0_smt(data)                                                  (0x00000008&((data)<<3))
#define PFUNC_NF1_nf_dd_0_smt_src(data)                                              ((0x00000008&(data))>>3)
#define PFUNC_NF1_get_nf_dd_0_smt(data)                                              ((0x00000008&(data))>>3)
#define PFUNC_NF1_nf_dd_0_e2_shift                                                   (2)
#define PFUNC_NF1_nf_dd_0_e2_mask                                                    (0x00000004)
#define PFUNC_NF1_nf_dd_0_e2(data)                                                   (0x00000004&((data)<<2))
#define PFUNC_NF1_nf_dd_0_e2_src(data)                                               ((0x00000004&(data))>>2)
#define PFUNC_NF1_get_nf_dd_0_e2(data)                                               ((0x00000004&(data))>>2)
#define PFUNC_NF1_nf_dd_0_pud_en_shift                                               (1)
#define PFUNC_NF1_nf_dd_0_pud_en_mask                                                (0x00000002)
#define PFUNC_NF1_nf_dd_0_pud_en(data)                                               (0x00000002&((data)<<1))
#define PFUNC_NF1_nf_dd_0_pud_en_src(data)                                           ((0x00000002&(data))>>1)
#define PFUNC_NF1_get_nf_dd_0_pud_en(data)                                           ((0x00000002&(data))>>1)
#define PFUNC_NF1_nf_dd_0_pud_sel_shift                                              (0)
#define PFUNC_NF1_nf_dd_0_pud_sel_mask                                               (0x00000001)
#define PFUNC_NF1_nf_dd_0_pud_sel(data)                                              (0x00000001&((data)<<0))
#define PFUNC_NF1_nf_dd_0_pud_sel_src(data)                                          ((0x00000001&(data))>>0)
#define PFUNC_NF1_get_nf_dd_0_pud_sel(data)                                          ((0x00000001&(data))>>0)


#define PFUNC_CR                                                                     0x98000380
#define PFUNC_CR_reg_addr                                                            "0x98000380"
#define PFUNC_CR_reg                                                                 0x98000380
#define set_PFUNC_CR_reg(data)   (*((volatile unsigned int*) PFUNC_CR_reg)=data)
#define get_PFUNC_CR_reg   (*((volatile unsigned int*) PFUNC_CR_reg))
#define PFUNC_CR_inst_adr                                                            "0x00E0"
#define PFUNC_CR_inst                                                                0x00E0
#define PFUNC_CR_mmc_data_3_smt_shift                                                (31)
#define PFUNC_CR_mmc_data_3_smt_mask                                                 (0x80000000)
#define PFUNC_CR_mmc_data_3_smt(data)                                                (0x80000000&((data)<<31))
#define PFUNC_CR_mmc_data_3_smt_src(data)                                            ((0x80000000&(data))>>31)
#define PFUNC_CR_get_mmc_data_3_smt(data)                                            ((0x80000000&(data))>>31)
#define PFUNC_CR_mmc_data_3_e2_shift                                                 (30)
#define PFUNC_CR_mmc_data_3_e2_mask                                                  (0x40000000)
#define PFUNC_CR_mmc_data_3_e2(data)                                                 (0x40000000&((data)<<30))
#define PFUNC_CR_mmc_data_3_e2_src(data)                                             ((0x40000000&(data))>>30)
#define PFUNC_CR_get_mmc_data_3_e2(data)                                             ((0x40000000&(data))>>30)
#define PFUNC_CR_mmc_data_3_pud_en_shift                                             (29)
#define PFUNC_CR_mmc_data_3_pud_en_mask                                              (0x20000000)
#define PFUNC_CR_mmc_data_3_pud_en(data)                                             (0x20000000&((data)<<29))
#define PFUNC_CR_mmc_data_3_pud_en_src(data)                                         ((0x20000000&(data))>>29)
#define PFUNC_CR_get_mmc_data_3_pud_en(data)                                         ((0x20000000&(data))>>29)
#define PFUNC_CR_mmc_data_3_pud_sel_shift                                            (28)
#define PFUNC_CR_mmc_data_3_pud_sel_mask                                             (0x10000000)
#define PFUNC_CR_mmc_data_3_pud_sel(data)                                            (0x10000000&((data)<<28))
#define PFUNC_CR_mmc_data_3_pud_sel_src(data)                                        ((0x10000000&(data))>>28)
#define PFUNC_CR_get_mmc_data_3_pud_sel(data)                                        ((0x10000000&(data))>>28)
#define PFUNC_CR_mmc_data_2_smt_shift                                                (27)
#define PFUNC_CR_mmc_data_2_smt_mask                                                 (0x08000000)
#define PFUNC_CR_mmc_data_2_smt(data)                                                (0x08000000&((data)<<27))
#define PFUNC_CR_mmc_data_2_smt_src(data)                                            ((0x08000000&(data))>>27)
#define PFUNC_CR_get_mmc_data_2_smt(data)                                            ((0x08000000&(data))>>27)
#define PFUNC_CR_mmc_data_2_e2_shift                                                 (26)
#define PFUNC_CR_mmc_data_2_e2_mask                                                  (0x04000000)
#define PFUNC_CR_mmc_data_2_e2(data)                                                 (0x04000000&((data)<<26))
#define PFUNC_CR_mmc_data_2_e2_src(data)                                             ((0x04000000&(data))>>26)
#define PFUNC_CR_get_mmc_data_2_e2(data)                                             ((0x04000000&(data))>>26)
#define PFUNC_CR_mmc_data_2_pud_en_shift                                             (25)
#define PFUNC_CR_mmc_data_2_pud_en_mask                                              (0x02000000)
#define PFUNC_CR_mmc_data_2_pud_en(data)                                             (0x02000000&((data)<<25))
#define PFUNC_CR_mmc_data_2_pud_en_src(data)                                         ((0x02000000&(data))>>25)
#define PFUNC_CR_get_mmc_data_2_pud_en(data)                                         ((0x02000000&(data))>>25)
#define PFUNC_CR_mmc_data_2_pud_sel_shift                                            (24)
#define PFUNC_CR_mmc_data_2_pud_sel_mask                                             (0x01000000)
#define PFUNC_CR_mmc_data_2_pud_sel(data)                                            (0x01000000&((data)<<24))
#define PFUNC_CR_mmc_data_2_pud_sel_src(data)                                        ((0x01000000&(data))>>24)
#define PFUNC_CR_get_mmc_data_2_pud_sel(data)                                        ((0x01000000&(data))>>24)
#define PFUNC_CR_mmc_data_1_smt_shift                                                (23)
#define PFUNC_CR_mmc_data_1_smt_mask                                                 (0x00800000)
#define PFUNC_CR_mmc_data_1_smt(data)                                                (0x00800000&((data)<<23))
#define PFUNC_CR_mmc_data_1_smt_src(data)                                            ((0x00800000&(data))>>23)
#define PFUNC_CR_get_mmc_data_1_smt(data)                                            ((0x00800000&(data))>>23)
#define PFUNC_CR_mmc_data_1_e2_shift                                                 (22)
#define PFUNC_CR_mmc_data_1_e2_mask                                                  (0x00400000)
#define PFUNC_CR_mmc_data_1_e2(data)                                                 (0x00400000&((data)<<22))
#define PFUNC_CR_mmc_data_1_e2_src(data)                                             ((0x00400000&(data))>>22)
#define PFUNC_CR_get_mmc_data_1_e2(data)                                             ((0x00400000&(data))>>22)
#define PFUNC_CR_mmc_data_1_pud_en_shift                                             (21)
#define PFUNC_CR_mmc_data_1_pud_en_mask                                              (0x00200000)
#define PFUNC_CR_mmc_data_1_pud_en(data)                                             (0x00200000&((data)<<21))
#define PFUNC_CR_mmc_data_1_pud_en_src(data)                                         ((0x00200000&(data))>>21)
#define PFUNC_CR_get_mmc_data_1_pud_en(data)                                         ((0x00200000&(data))>>21)
#define PFUNC_CR_mmc_data_1_pud_sel_shift                                            (20)
#define PFUNC_CR_mmc_data_1_pud_sel_mask                                             (0x00100000)
#define PFUNC_CR_mmc_data_1_pud_sel(data)                                            (0x00100000&((data)<<20))
#define PFUNC_CR_mmc_data_1_pud_sel_src(data)                                        ((0x00100000&(data))>>20)
#define PFUNC_CR_get_mmc_data_1_pud_sel(data)                                        ((0x00100000&(data))>>20)
#define PFUNC_CR_mmc_data_0_smt_shift                                                (19)
#define PFUNC_CR_mmc_data_0_smt_mask                                                 (0x00080000)
#define PFUNC_CR_mmc_data_0_smt(data)                                                (0x00080000&((data)<<19))
#define PFUNC_CR_mmc_data_0_smt_src(data)                                            ((0x00080000&(data))>>19)
#define PFUNC_CR_get_mmc_data_0_smt(data)                                            ((0x00080000&(data))>>19)
#define PFUNC_CR_mmc_data_0_e2_shift                                                 (18)
#define PFUNC_CR_mmc_data_0_e2_mask                                                  (0x00040000)
#define PFUNC_CR_mmc_data_0_e2(data)                                                 (0x00040000&((data)<<18))
#define PFUNC_CR_mmc_data_0_e2_src(data)                                             ((0x00040000&(data))>>18)
#define PFUNC_CR_get_mmc_data_0_e2(data)                                             ((0x00040000&(data))>>18)
#define PFUNC_CR_mmc_data_0_pud_en_shift                                             (17)
#define PFUNC_CR_mmc_data_0_pud_en_mask                                              (0x00020000)
#define PFUNC_CR_mmc_data_0_pud_en(data)                                             (0x00020000&((data)<<17))
#define PFUNC_CR_mmc_data_0_pud_en_src(data)                                         ((0x00020000&(data))>>17)
#define PFUNC_CR_get_mmc_data_0_pud_en(data)                                         ((0x00020000&(data))>>17)
#define PFUNC_CR_mmc_data_0_pud_sel_shift                                            (16)
#define PFUNC_CR_mmc_data_0_pud_sel_mask                                             (0x00010000)
#define PFUNC_CR_mmc_data_0_pud_sel(data)                                            (0x00010000&((data)<<16))
#define PFUNC_CR_mmc_data_0_pud_sel_src(data)                                        ((0x00010000&(data))>>16)
#define PFUNC_CR_get_mmc_data_0_pud_sel(data)                                        ((0x00010000&(data))>>16)
#define PFUNC_CR_mmc_cd_smt_shift                                                    (15)
#define PFUNC_CR_mmc_cd_smt_mask                                                     (0x00008000)
#define PFUNC_CR_mmc_cd_smt(data)                                                    (0x00008000&((data)<<15))
#define PFUNC_CR_mmc_cd_smt_src(data)                                                ((0x00008000&(data))>>15)
#define PFUNC_CR_get_mmc_cd_smt(data)                                                ((0x00008000&(data))>>15)
#define PFUNC_CR_mmc_cd_e2_shift                                                     (14)
#define PFUNC_CR_mmc_cd_e2_mask                                                      (0x00004000)
#define PFUNC_CR_mmc_cd_e2(data)                                                     (0x00004000&((data)<<14))
#define PFUNC_CR_mmc_cd_e2_src(data)                                                 ((0x00004000&(data))>>14)
#define PFUNC_CR_get_mmc_cd_e2(data)                                                 ((0x00004000&(data))>>14)
#define PFUNC_CR_mmc_cd_pud_en_shift                                                 (13)
#define PFUNC_CR_mmc_cd_pud_en_mask                                                  (0x00002000)
#define PFUNC_CR_mmc_cd_pud_en(data)                                                 (0x00002000&((data)<<13))
#define PFUNC_CR_mmc_cd_pud_en_src(data)                                             ((0x00002000&(data))>>13)
#define PFUNC_CR_get_mmc_cd_pud_en(data)                                             ((0x00002000&(data))>>13)
#define PFUNC_CR_mmc_cd_pud_sel_shift                                                (12)
#define PFUNC_CR_mmc_cd_pud_sel_mask                                                 (0x00001000)
#define PFUNC_CR_mmc_cd_pud_sel(data)                                                (0x00001000&((data)<<12))
#define PFUNC_CR_mmc_cd_pud_sel_src(data)                                            ((0x00001000&(data))>>12)
#define PFUNC_CR_get_mmc_cd_pud_sel(data)                                            ((0x00001000&(data))>>12)
#define PFUNC_CR_mmc_wp_smt_shift                                                    (11)
#define PFUNC_CR_mmc_wp_smt_mask                                                     (0x00000800)
#define PFUNC_CR_mmc_wp_smt(data)                                                    (0x00000800&((data)<<11))
#define PFUNC_CR_mmc_wp_smt_src(data)                                                ((0x00000800&(data))>>11)
#define PFUNC_CR_get_mmc_wp_smt(data)                                                ((0x00000800&(data))>>11)
#define PFUNC_CR_mmc_wp_e2_shift                                                     (10)
#define PFUNC_CR_mmc_wp_e2_mask                                                      (0x00000400)
#define PFUNC_CR_mmc_wp_e2(data)                                                     (0x00000400&((data)<<10))
#define PFUNC_CR_mmc_wp_e2_src(data)                                                 ((0x00000400&(data))>>10)
#define PFUNC_CR_get_mmc_wp_e2(data)                                                 ((0x00000400&(data))>>10)
#define PFUNC_CR_mmc_wp_pud_en_shift                                                 (9)
#define PFUNC_CR_mmc_wp_pud_en_mask                                                  (0x00000200)
#define PFUNC_CR_mmc_wp_pud_en(data)                                                 (0x00000200&((data)<<9))
#define PFUNC_CR_mmc_wp_pud_en_src(data)                                             ((0x00000200&(data))>>9)
#define PFUNC_CR_get_mmc_wp_pud_en(data)                                             ((0x00000200&(data))>>9)
#define PFUNC_CR_mmc_wp_pud_sel_shift                                                (8)
#define PFUNC_CR_mmc_wp_pud_sel_mask                                                 (0x00000100)
#define PFUNC_CR_mmc_wp_pud_sel(data)                                                (0x00000100&((data)<<8))
#define PFUNC_CR_mmc_wp_pud_sel_src(data)                                            ((0x00000100&(data))>>8)
#define PFUNC_CR_get_mmc_wp_pud_sel(data)                                            ((0x00000100&(data))>>8)
#define PFUNC_CR_mmc_clk_smt_shift                                                   (7)
#define PFUNC_CR_mmc_clk_smt_mask                                                    (0x00000080)
#define PFUNC_CR_mmc_clk_smt(data)                                                   (0x00000080&((data)<<7))
#define PFUNC_CR_mmc_clk_smt_src(data)                                               ((0x00000080&(data))>>7)
#define PFUNC_CR_get_mmc_clk_smt(data)                                               ((0x00000080&(data))>>7)
#define PFUNC_CR_mmc_clk_e2_shift                                                    (6)
#define PFUNC_CR_mmc_clk_e2_mask                                                     (0x00000040)
#define PFUNC_CR_mmc_clk_e2(data)                                                    (0x00000040&((data)<<6))
#define PFUNC_CR_mmc_clk_e2_src(data)                                                ((0x00000040&(data))>>6)
#define PFUNC_CR_get_mmc_clk_e2(data)                                                ((0x00000040&(data))>>6)
#define PFUNC_CR_mmc_clk_pud_en_shift                                                (5)
#define PFUNC_CR_mmc_clk_pud_en_mask                                                 (0x00000020)
#define PFUNC_CR_mmc_clk_pud_en(data)                                                (0x00000020&((data)<<5))
#define PFUNC_CR_mmc_clk_pud_en_src(data)                                            ((0x00000020&(data))>>5)
#define PFUNC_CR_get_mmc_clk_pud_en(data)                                            ((0x00000020&(data))>>5)
#define PFUNC_CR_mmc_clk_pud_sel_shift                                               (4)
#define PFUNC_CR_mmc_clk_pud_sel_mask                                                (0x00000010)
#define PFUNC_CR_mmc_clk_pud_sel(data)                                               (0x00000010&((data)<<4))
#define PFUNC_CR_mmc_clk_pud_sel_src(data)                                           ((0x00000010&(data))>>4)
#define PFUNC_CR_get_mmc_clk_pud_sel(data)                                           ((0x00000010&(data))>>4)
#define PFUNC_CR_mmc_cmd_smt_shift                                                   (3)
#define PFUNC_CR_mmc_cmd_smt_mask                                                    (0x00000008)
#define PFUNC_CR_mmc_cmd_smt(data)                                                   (0x00000008&((data)<<3))
#define PFUNC_CR_mmc_cmd_smt_src(data)                                               ((0x00000008&(data))>>3)
#define PFUNC_CR_get_mmc_cmd_smt(data)                                               ((0x00000008&(data))>>3)
#define PFUNC_CR_mmc_cmd_e2_shift                                                    (2)
#define PFUNC_CR_mmc_cmd_e2_mask                                                     (0x00000004)
#define PFUNC_CR_mmc_cmd_e2(data)                                                    (0x00000004&((data)<<2))
#define PFUNC_CR_mmc_cmd_e2_src(data)                                                ((0x00000004&(data))>>2)
#define PFUNC_CR_get_mmc_cmd_e2(data)                                                ((0x00000004&(data))>>2)
#define PFUNC_CR_mmc_cmd_pud_en_shift                                                (1)
#define PFUNC_CR_mmc_cmd_pud_en_mask                                                 (0x00000002)
#define PFUNC_CR_mmc_cmd_pud_en(data)                                                (0x00000002&((data)<<1))
#define PFUNC_CR_mmc_cmd_pud_en_src(data)                                            ((0x00000002&(data))>>1)
#define PFUNC_CR_get_mmc_cmd_pud_en(data)                                            ((0x00000002&(data))>>1)
#define PFUNC_CR_mmc_cmd_pud_sel_shift                                               (0)
#define PFUNC_CR_mmc_cmd_pud_sel_mask                                                (0x00000001)
#define PFUNC_CR_mmc_cmd_pud_sel(data)                                               (0x00000001&((data)<<0))
#define PFUNC_CR_mmc_cmd_pud_sel_src(data)                                           ((0x00000001&(data))>>0)
#define PFUNC_CR_get_mmc_cmd_pud_sel(data)                                           ((0x00000001&(data))>>0)


#define PFUNC_SDIO                                                                   0x98000384
#define PFUNC_SDIO_reg_addr                                                          "0x98000384"
#define PFUNC_SDIO_reg                                                               0x98000384
#define set_PFUNC_SDIO_reg(data)   (*((volatile unsigned int*) PFUNC_SDIO_reg)=data)
#define get_PFUNC_SDIO_reg   (*((volatile unsigned int*) PFUNC_SDIO_reg))
#define PFUNC_SDIO_inst_adr                                                          "0x00E1"
#define PFUNC_SDIO_inst                                                              0x00E1
#define PFUNC_SDIO_sdio_data_3_smt_shift                                             (31)
#define PFUNC_SDIO_sdio_data_3_smt_mask                                              (0x80000000)
#define PFUNC_SDIO_sdio_data_3_smt(data)                                             (0x80000000&((data)<<31))
#define PFUNC_SDIO_sdio_data_3_smt_src(data)                                         ((0x80000000&(data))>>31)
#define PFUNC_SDIO_get_sdio_data_3_smt(data)                                         ((0x80000000&(data))>>31)
#define PFUNC_SDIO_sdio_data_3_e2_shift                                              (30)
#define PFUNC_SDIO_sdio_data_3_e2_mask                                               (0x40000000)
#define PFUNC_SDIO_sdio_data_3_e2(data)                                              (0x40000000&((data)<<30))
#define PFUNC_SDIO_sdio_data_3_e2_src(data)                                          ((0x40000000&(data))>>30)
#define PFUNC_SDIO_get_sdio_data_3_e2(data)                                          ((0x40000000&(data))>>30)
#define PFUNC_SDIO_sdio_data_3_pud_en_shift                                          (29)
#define PFUNC_SDIO_sdio_data_3_pud_en_mask                                           (0x20000000)
#define PFUNC_SDIO_sdio_data_3_pud_en(data)                                          (0x20000000&((data)<<29))
#define PFUNC_SDIO_sdio_data_3_pud_en_src(data)                                      ((0x20000000&(data))>>29)
#define PFUNC_SDIO_get_sdio_data_3_pud_en(data)                                      ((0x20000000&(data))>>29)
#define PFUNC_SDIO_sdio_data_3_pud_sel_shift                                         (28)
#define PFUNC_SDIO_sdio_data_3_pud_sel_mask                                          (0x10000000)
#define PFUNC_SDIO_sdio_data_3_pud_sel(data)                                         (0x10000000&((data)<<28))
#define PFUNC_SDIO_sdio_data_3_pud_sel_src(data)                                     ((0x10000000&(data))>>28)
#define PFUNC_SDIO_get_sdio_data_3_pud_sel(data)                                     ((0x10000000&(data))>>28)
#define PFUNC_SDIO_sdio_data_2_smt_shift                                             (27)
#define PFUNC_SDIO_sdio_data_2_smt_mask                                              (0x08000000)
#define PFUNC_SDIO_sdio_data_2_smt(data)                                             (0x08000000&((data)<<27))
#define PFUNC_SDIO_sdio_data_2_smt_src(data)                                         ((0x08000000&(data))>>27)
#define PFUNC_SDIO_get_sdio_data_2_smt(data)                                         ((0x08000000&(data))>>27)
#define PFUNC_SDIO_sdio_data_2_e2_shift                                              (26)
#define PFUNC_SDIO_sdio_data_2_e2_mask                                               (0x04000000)
#define PFUNC_SDIO_sdio_data_2_e2(data)                                              (0x04000000&((data)<<26))
#define PFUNC_SDIO_sdio_data_2_e2_src(data)                                          ((0x04000000&(data))>>26)
#define PFUNC_SDIO_get_sdio_data_2_e2(data)                                          ((0x04000000&(data))>>26)
#define PFUNC_SDIO_sdio_data_2_pud_en_shift                                          (25)
#define PFUNC_SDIO_sdio_data_2_pud_en_mask                                           (0x02000000)
#define PFUNC_SDIO_sdio_data_2_pud_en(data)                                          (0x02000000&((data)<<25))
#define PFUNC_SDIO_sdio_data_2_pud_en_src(data)                                      ((0x02000000&(data))>>25)
#define PFUNC_SDIO_get_sdio_data_2_pud_en(data)                                      ((0x02000000&(data))>>25)
#define PFUNC_SDIO_sdio_data_2_pud_sel_shift                                         (24)
#define PFUNC_SDIO_sdio_data_2_pud_sel_mask                                          (0x01000000)
#define PFUNC_SDIO_sdio_data_2_pud_sel(data)                                         (0x01000000&((data)<<24))
#define PFUNC_SDIO_sdio_data_2_pud_sel_src(data)                                     ((0x01000000&(data))>>24)
#define PFUNC_SDIO_get_sdio_data_2_pud_sel(data)                                     ((0x01000000&(data))>>24)
#define PFUNC_SDIO_sdio_data_1_smt_shift                                             (23)
#define PFUNC_SDIO_sdio_data_1_smt_mask                                              (0x00800000)
#define PFUNC_SDIO_sdio_data_1_smt(data)                                             (0x00800000&((data)<<23))
#define PFUNC_SDIO_sdio_data_1_smt_src(data)                                         ((0x00800000&(data))>>23)
#define PFUNC_SDIO_get_sdio_data_1_smt(data)                                         ((0x00800000&(data))>>23)
#define PFUNC_SDIO_sdio_data_1_e2_shift                                              (22)
#define PFUNC_SDIO_sdio_data_1_e2_mask                                               (0x00400000)
#define PFUNC_SDIO_sdio_data_1_e2(data)                                              (0x00400000&((data)<<22))
#define PFUNC_SDIO_sdio_data_1_e2_src(data)                                          ((0x00400000&(data))>>22)
#define PFUNC_SDIO_get_sdio_data_1_e2(data)                                          ((0x00400000&(data))>>22)
#define PFUNC_SDIO_sdio_data_1_pud_en_shift                                          (21)
#define PFUNC_SDIO_sdio_data_1_pud_en_mask                                           (0x00200000)
#define PFUNC_SDIO_sdio_data_1_pud_en(data)                                          (0x00200000&((data)<<21))
#define PFUNC_SDIO_sdio_data_1_pud_en_src(data)                                      ((0x00200000&(data))>>21)
#define PFUNC_SDIO_get_sdio_data_1_pud_en(data)                                      ((0x00200000&(data))>>21)
#define PFUNC_SDIO_sdio_data_1_pud_sel_shift                                         (20)
#define PFUNC_SDIO_sdio_data_1_pud_sel_mask                                          (0x00100000)
#define PFUNC_SDIO_sdio_data_1_pud_sel(data)                                         (0x00100000&((data)<<20))
#define PFUNC_SDIO_sdio_data_1_pud_sel_src(data)                                     ((0x00100000&(data))>>20)
#define PFUNC_SDIO_get_sdio_data_1_pud_sel(data)                                     ((0x00100000&(data))>>20)
#define PFUNC_SDIO_sdio_data_0_smt_shift                                             (19)
#define PFUNC_SDIO_sdio_data_0_smt_mask                                              (0x00080000)
#define PFUNC_SDIO_sdio_data_0_smt(data)                                             (0x00080000&((data)<<19))
#define PFUNC_SDIO_sdio_data_0_smt_src(data)                                         ((0x00080000&(data))>>19)
#define PFUNC_SDIO_get_sdio_data_0_smt(data)                                         ((0x00080000&(data))>>19)
#define PFUNC_SDIO_sdio_data_0_e2_shift                                              (18)
#define PFUNC_SDIO_sdio_data_0_e2_mask                                               (0x00040000)
#define PFUNC_SDIO_sdio_data_0_e2(data)                                              (0x00040000&((data)<<18))
#define PFUNC_SDIO_sdio_data_0_e2_src(data)                                          ((0x00040000&(data))>>18)
#define PFUNC_SDIO_get_sdio_data_0_e2(data)                                          ((0x00040000&(data))>>18)
#define PFUNC_SDIO_sdio_data_0_pud_en_shift                                          (17)
#define PFUNC_SDIO_sdio_data_0_pud_en_mask                                           (0x00020000)
#define PFUNC_SDIO_sdio_data_0_pud_en(data)                                          (0x00020000&((data)<<17))
#define PFUNC_SDIO_sdio_data_0_pud_en_src(data)                                      ((0x00020000&(data))>>17)
#define PFUNC_SDIO_get_sdio_data_0_pud_en(data)                                      ((0x00020000&(data))>>17)
#define PFUNC_SDIO_sdio_data_0_pud_sel_shift                                         (16)
#define PFUNC_SDIO_sdio_data_0_pud_sel_mask                                          (0x00010000)
#define PFUNC_SDIO_sdio_data_0_pud_sel(data)                                         (0x00010000&((data)<<16))
#define PFUNC_SDIO_sdio_data_0_pud_sel_src(data)                                     ((0x00010000&(data))>>16)
#define PFUNC_SDIO_get_sdio_data_0_pud_sel(data)                                     ((0x00010000&(data))>>16)
#define PFUNC_SDIO_sdio_cd_smt_shift                                                 (15)
#define PFUNC_SDIO_sdio_cd_smt_mask                                                  (0x00008000)
#define PFUNC_SDIO_sdio_cd_smt(data)                                                 (0x00008000&((data)<<15))
#define PFUNC_SDIO_sdio_cd_smt_src(data)                                             ((0x00008000&(data))>>15)
#define PFUNC_SDIO_get_sdio_cd_smt(data)                                             ((0x00008000&(data))>>15)
#define PFUNC_SDIO_sdio_cd_e2_shift                                                  (14)
#define PFUNC_SDIO_sdio_cd_e2_mask                                                   (0x00004000)
#define PFUNC_SDIO_sdio_cd_e2(data)                                                  (0x00004000&((data)<<14))
#define PFUNC_SDIO_sdio_cd_e2_src(data)                                              ((0x00004000&(data))>>14)
#define PFUNC_SDIO_get_sdio_cd_e2(data)                                              ((0x00004000&(data))>>14)
#define PFUNC_SDIO_sdio_cd_pud_en_shift                                              (13)
#define PFUNC_SDIO_sdio_cd_pud_en_mask                                               (0x00002000)
#define PFUNC_SDIO_sdio_cd_pud_en(data)                                              (0x00002000&((data)<<13))
#define PFUNC_SDIO_sdio_cd_pud_en_src(data)                                          ((0x00002000&(data))>>13)
#define PFUNC_SDIO_get_sdio_cd_pud_en(data)                                          ((0x00002000&(data))>>13)
#define PFUNC_SDIO_sdio_cd_pud_sel_shift                                             (12)
#define PFUNC_SDIO_sdio_cd_pud_sel_mask                                              (0x00001000)
#define PFUNC_SDIO_sdio_cd_pud_sel(data)                                             (0x00001000&((data)<<12))
#define PFUNC_SDIO_sdio_cd_pud_sel_src(data)                                         ((0x00001000&(data))>>12)
#define PFUNC_SDIO_get_sdio_cd_pud_sel(data)                                         ((0x00001000&(data))>>12)
#define PFUNC_SDIO_sdio_wp_smt_shift                                                 (11)
#define PFUNC_SDIO_sdio_wp_smt_mask                                                  (0x00000800)
#define PFUNC_SDIO_sdio_wp_smt(data)                                                 (0x00000800&((data)<<11))
#define PFUNC_SDIO_sdio_wp_smt_src(data)                                             ((0x00000800&(data))>>11)
#define PFUNC_SDIO_get_sdio_wp_smt(data)                                             ((0x00000800&(data))>>11)
#define PFUNC_SDIO_sdio_wp_e2_shift                                                  (10)
#define PFUNC_SDIO_sdio_wp_e2_mask                                                   (0x00000400)
#define PFUNC_SDIO_sdio_wp_e2(data)                                                  (0x00000400&((data)<<10))
#define PFUNC_SDIO_sdio_wp_e2_src(data)                                              ((0x00000400&(data))>>10)
#define PFUNC_SDIO_get_sdio_wp_e2(data)                                              ((0x00000400&(data))>>10)
#define PFUNC_SDIO_sdio_wp_pud_en_shift                                              (9)
#define PFUNC_SDIO_sdio_wp_pud_en_mask                                               (0x00000200)
#define PFUNC_SDIO_sdio_wp_pud_en(data)                                              (0x00000200&((data)<<9))
#define PFUNC_SDIO_sdio_wp_pud_en_src(data)                                          ((0x00000200&(data))>>9)
#define PFUNC_SDIO_get_sdio_wp_pud_en(data)                                          ((0x00000200&(data))>>9)
#define PFUNC_SDIO_sdio_wp_pud_sel_shift                                             (8)
#define PFUNC_SDIO_sdio_wp_pud_sel_mask                                              (0x00000100)
#define PFUNC_SDIO_sdio_wp_pud_sel(data)                                             (0x00000100&((data)<<8))
#define PFUNC_SDIO_sdio_wp_pud_sel_src(data)                                         ((0x00000100&(data))>>8)
#define PFUNC_SDIO_get_sdio_wp_pud_sel(data)                                         ((0x00000100&(data))>>8)
#define PFUNC_SDIO_sdio_clk_smt_shift                                                (7)
#define PFUNC_SDIO_sdio_clk_smt_mask                                                 (0x00000080)
#define PFUNC_SDIO_sdio_clk_smt(data)                                                (0x00000080&((data)<<7))
#define PFUNC_SDIO_sdio_clk_smt_src(data)                                            ((0x00000080&(data))>>7)
#define PFUNC_SDIO_get_sdio_clk_smt(data)                                            ((0x00000080&(data))>>7)
#define PFUNC_SDIO_sdio_clk_e2_shift                                                 (6)
#define PFUNC_SDIO_sdio_clk_e2_mask                                                  (0x00000040)
#define PFUNC_SDIO_sdio_clk_e2(data)                                                 (0x00000040&((data)<<6))
#define PFUNC_SDIO_sdio_clk_e2_src(data)                                             ((0x00000040&(data))>>6)
#define PFUNC_SDIO_get_sdio_clk_e2(data)                                             ((0x00000040&(data))>>6)
#define PFUNC_SDIO_sdio_clk_pud_en_shift                                             (5)
#define PFUNC_SDIO_sdio_clk_pud_en_mask                                              (0x00000020)
#define PFUNC_SDIO_sdio_clk_pud_en(data)                                             (0x00000020&((data)<<5))
#define PFUNC_SDIO_sdio_clk_pud_en_src(data)                                         ((0x00000020&(data))>>5)
#define PFUNC_SDIO_get_sdio_clk_pud_en(data)                                         ((0x00000020&(data))>>5)
#define PFUNC_SDIO_sdio_clk_pud_sel_shift                                            (4)
#define PFUNC_SDIO_sdio_clk_pud_sel_mask                                             (0x00000010)
#define PFUNC_SDIO_sdio_clk_pud_sel(data)                                            (0x00000010&((data)<<4))
#define PFUNC_SDIO_sdio_clk_pud_sel_src(data)                                        ((0x00000010&(data))>>4)
#define PFUNC_SDIO_get_sdio_clk_pud_sel(data)                                        ((0x00000010&(data))>>4)
#define PFUNC_SDIO_sdio_cmd_smt_shift                                                (3)
#define PFUNC_SDIO_sdio_cmd_smt_mask                                                 (0x00000008)
#define PFUNC_SDIO_sdio_cmd_smt(data)                                                (0x00000008&((data)<<3))
#define PFUNC_SDIO_sdio_cmd_smt_src(data)                                            ((0x00000008&(data))>>3)
#define PFUNC_SDIO_get_sdio_cmd_smt(data)                                            ((0x00000008&(data))>>3)
#define PFUNC_SDIO_sdio_cmd_e2_shift                                                 (2)
#define PFUNC_SDIO_sdio_cmd_e2_mask                                                  (0x00000004)
#define PFUNC_SDIO_sdio_cmd_e2(data)                                                 (0x00000004&((data)<<2))
#define PFUNC_SDIO_sdio_cmd_e2_src(data)                                             ((0x00000004&(data))>>2)
#define PFUNC_SDIO_get_sdio_cmd_e2(data)                                             ((0x00000004&(data))>>2)
#define PFUNC_SDIO_sdio_cmd_pud_en_shift                                             (1)
#define PFUNC_SDIO_sdio_cmd_pud_en_mask                                              (0x00000002)
#define PFUNC_SDIO_sdio_cmd_pud_en(data)                                             (0x00000002&((data)<<1))
#define PFUNC_SDIO_sdio_cmd_pud_en_src(data)                                         ((0x00000002&(data))>>1)
#define PFUNC_SDIO_get_sdio_cmd_pud_en(data)                                         ((0x00000002&(data))>>1)
#define PFUNC_SDIO_sdio_cmd_pud_sel_shift                                            (0)
#define PFUNC_SDIO_sdio_cmd_pud_sel_mask                                             (0x00000001)
#define PFUNC_SDIO_sdio_cmd_pud_sel(data)                                            (0x00000001&((data)<<0))
#define PFUNC_SDIO_sdio_cmd_pud_sel_src(data)                                        ((0x00000001&(data))>>0)
#define PFUNC_SDIO_get_sdio_cmd_pud_sel(data)                                        ((0x00000001&(data))>>0)


#define PFUNC_AIO                                                                    0x98000388
#define PFUNC_AIO_reg_addr                                                           "0x98000388"
#define PFUNC_AIO_reg                                                                0x98000388
#define set_PFUNC_AIO_reg(data)   (*((volatile unsigned int*) PFUNC_AIO_reg)=data)
#define get_PFUNC_AIO_reg   (*((volatile unsigned int*) PFUNC_AIO_reg))
#define PFUNC_AIO_inst_adr                                                           "0x00E2"
#define PFUNC_AIO_inst                                                               0x00E2
#define PFUNC_AIO_spdif_out_e2_shift                                                 (2)
#define PFUNC_AIO_spdif_out_e2_mask                                                  (0x00000004)
#define PFUNC_AIO_spdif_out_e2(data)                                                 (0x00000004&((data)<<2))
#define PFUNC_AIO_spdif_out_e2_src(data)                                             ((0x00000004&(data))>>2)
#define PFUNC_AIO_get_spdif_out_e2(data)                                             ((0x00000004&(data))>>2)
#define PFUNC_AIO_spdif_out_pud_en_shift                                             (1)
#define PFUNC_AIO_spdif_out_pud_en_mask                                              (0x00000002)
#define PFUNC_AIO_spdif_out_pud_en(data)                                             (0x00000002&((data)<<1))
#define PFUNC_AIO_spdif_out_pud_en_src(data)                                         ((0x00000002&(data))>>1)
#define PFUNC_AIO_get_spdif_out_pud_en(data)                                         ((0x00000002&(data))>>1)
#define PFUNC_AIO_spdif_out_pud_sel_shift                                            (0)
#define PFUNC_AIO_spdif_out_pud_sel_mask                                             (0x00000001)
#define PFUNC_AIO_spdif_out_pud_sel(data)                                            (0x00000001&((data)<<0))
#define PFUNC_AIO_spdif_out_pud_sel_src(data)                                        ((0x00000001&(data))>>0)
#define PFUNC_AIO_get_spdif_out_pud_sel(data)                                        ((0x00000001&(data))>>0)


#define PFUNC_TP0                                                                    0x9800038C
#define PFUNC_TP0_reg_addr                                                           "0x9800038C"
#define PFUNC_TP0_reg                                                                0x9800038C
#define set_PFUNC_TP0_reg(data)   (*((volatile unsigned int*) PFUNC_TP0_reg)=data)
#define get_PFUNC_TP0_reg   (*((volatile unsigned int*) PFUNC_TP0_reg))
#define PFUNC_TP0_inst_adr                                                           "0x00E3"
#define PFUNC_TP0_inst                                                               0x00E3
#define PFUNC_TP0_tp0_data_smt_shift                                                 (15)
#define PFUNC_TP0_tp0_data_smt_mask                                                  (0x00008000)
#define PFUNC_TP0_tp0_data_smt(data)                                                 (0x00008000&((data)<<15))
#define PFUNC_TP0_tp0_data_smt_src(data)                                             ((0x00008000&(data))>>15)
#define PFUNC_TP0_get_tp0_data_smt(data)                                             ((0x00008000&(data))>>15)
#define PFUNC_TP0_tp0_data_e2_shift                                                  (14)
#define PFUNC_TP0_tp0_data_e2_mask                                                   (0x00004000)
#define PFUNC_TP0_tp0_data_e2(data)                                                  (0x00004000&((data)<<14))
#define PFUNC_TP0_tp0_data_e2_src(data)                                              ((0x00004000&(data))>>14)
#define PFUNC_TP0_get_tp0_data_e2(data)                                              ((0x00004000&(data))>>14)
#define PFUNC_TP0_tp0_data_pud_en_shift                                              (13)
#define PFUNC_TP0_tp0_data_pud_en_mask                                               (0x00002000)
#define PFUNC_TP0_tp0_data_pud_en(data)                                              (0x00002000&((data)<<13))
#define PFUNC_TP0_tp0_data_pud_en_src(data)                                          ((0x00002000&(data))>>13)
#define PFUNC_TP0_get_tp0_data_pud_en(data)                                          ((0x00002000&(data))>>13)
#define PFUNC_TP0_tp0_data_pud_sel_shift                                             (12)
#define PFUNC_TP0_tp0_data_pud_sel_mask                                              (0x00001000)
#define PFUNC_TP0_tp0_data_pud_sel(data)                                             (0x00001000&((data)<<12))
#define PFUNC_TP0_tp0_data_pud_sel_src(data)                                         ((0x00001000&(data))>>12)
#define PFUNC_TP0_get_tp0_data_pud_sel(data)                                         ((0x00001000&(data))>>12)
#define PFUNC_TP0_tp0_valid_smt_shift                                                (11)
#define PFUNC_TP0_tp0_valid_smt_mask                                                 (0x00000800)
#define PFUNC_TP0_tp0_valid_smt(data)                                                (0x00000800&((data)<<11))
#define PFUNC_TP0_tp0_valid_smt_src(data)                                            ((0x00000800&(data))>>11)
#define PFUNC_TP0_get_tp0_valid_smt(data)                                            ((0x00000800&(data))>>11)
#define PFUNC_TP0_tp0_valid_e2_shift                                                 (10)
#define PFUNC_TP0_tp0_valid_e2_mask                                                  (0x00000400)
#define PFUNC_TP0_tp0_valid_e2(data)                                                 (0x00000400&((data)<<10))
#define PFUNC_TP0_tp0_valid_e2_src(data)                                             ((0x00000400&(data))>>10)
#define PFUNC_TP0_get_tp0_valid_e2(data)                                             ((0x00000400&(data))>>10)
#define PFUNC_TP0_tp0_valid_pud_en_shift                                             (9)
#define PFUNC_TP0_tp0_valid_pud_en_mask                                              (0x00000200)
#define PFUNC_TP0_tp0_valid_pud_en(data)                                             (0x00000200&((data)<<9))
#define PFUNC_TP0_tp0_valid_pud_en_src(data)                                         ((0x00000200&(data))>>9)
#define PFUNC_TP0_get_tp0_valid_pud_en(data)                                         ((0x00000200&(data))>>9)
#define PFUNC_TP0_tp0_valid_pud_sel_shift                                            (8)
#define PFUNC_TP0_tp0_valid_pud_sel_mask                                             (0x00000100)
#define PFUNC_TP0_tp0_valid_pud_sel(data)                                            (0x00000100&((data)<<8))
#define PFUNC_TP0_tp0_valid_pud_sel_src(data)                                        ((0x00000100&(data))>>8)
#define PFUNC_TP0_get_tp0_valid_pud_sel(data)                                        ((0x00000100&(data))>>8)
#define PFUNC_TP0_tp0_sync_smt_shift                                                 (7)
#define PFUNC_TP0_tp0_sync_smt_mask                                                  (0x00000080)
#define PFUNC_TP0_tp0_sync_smt(data)                                                 (0x00000080&((data)<<7))
#define PFUNC_TP0_tp0_sync_smt_src(data)                                             ((0x00000080&(data))>>7)
#define PFUNC_TP0_get_tp0_sync_smt(data)                                             ((0x00000080&(data))>>7)
#define PFUNC_TP0_tp0_sync_e2_shift                                                  (6)
#define PFUNC_TP0_tp0_sync_e2_mask                                                   (0x00000040)
#define PFUNC_TP0_tp0_sync_e2(data)                                                  (0x00000040&((data)<<6))
#define PFUNC_TP0_tp0_sync_e2_src(data)                                              ((0x00000040&(data))>>6)
#define PFUNC_TP0_get_tp0_sync_e2(data)                                              ((0x00000040&(data))>>6)
#define PFUNC_TP0_tp0_sync_pud_en_shift                                              (5)
#define PFUNC_TP0_tp0_sync_pud_en_mask                                               (0x00000020)
#define PFUNC_TP0_tp0_sync_pud_en(data)                                              (0x00000020&((data)<<5))
#define PFUNC_TP0_tp0_sync_pud_en_src(data)                                          ((0x00000020&(data))>>5)
#define PFUNC_TP0_get_tp0_sync_pud_en(data)                                          ((0x00000020&(data))>>5)
#define PFUNC_TP0_tp0_sync_pud_sel_shift                                             (4)
#define PFUNC_TP0_tp0_sync_pud_sel_mask                                              (0x00000010)
#define PFUNC_TP0_tp0_sync_pud_sel(data)                                             (0x00000010&((data)<<4))
#define PFUNC_TP0_tp0_sync_pud_sel_src(data)                                         ((0x00000010&(data))>>4)
#define PFUNC_TP0_get_tp0_sync_pud_sel(data)                                         ((0x00000010&(data))>>4)
#define PFUNC_TP0_tp0_clk_smt_shift                                                  (3)
#define PFUNC_TP0_tp0_clk_smt_mask                                                   (0x00000008)
#define PFUNC_TP0_tp0_clk_smt(data)                                                  (0x00000008&((data)<<3))
#define PFUNC_TP0_tp0_clk_smt_src(data)                                              ((0x00000008&(data))>>3)
#define PFUNC_TP0_get_tp0_clk_smt(data)                                              ((0x00000008&(data))>>3)
#define PFUNC_TP0_tp0_clk_e2_shift                                                   (2)
#define PFUNC_TP0_tp0_clk_e2_mask                                                    (0x00000004)
#define PFUNC_TP0_tp0_clk_e2(data)                                                   (0x00000004&((data)<<2))
#define PFUNC_TP0_tp0_clk_e2_src(data)                                               ((0x00000004&(data))>>2)
#define PFUNC_TP0_get_tp0_clk_e2(data)                                               ((0x00000004&(data))>>2)
#define PFUNC_TP0_tp0_clk_pud_en_shift                                               (1)
#define PFUNC_TP0_tp0_clk_pud_en_mask                                                (0x00000002)
#define PFUNC_TP0_tp0_clk_pud_en(data)                                               (0x00000002&((data)<<1))
#define PFUNC_TP0_tp0_clk_pud_en_src(data)                                           ((0x00000002&(data))>>1)
#define PFUNC_TP0_get_tp0_clk_pud_en(data)                                           ((0x00000002&(data))>>1)
#define PFUNC_TP0_tp0_clk_pud_sel_shift                                              (0)
#define PFUNC_TP0_tp0_clk_pud_sel_mask                                               (0x00000001)
#define PFUNC_TP0_tp0_clk_pud_sel(data)                                              (0x00000001&((data)<<0))
#define PFUNC_TP0_tp0_clk_pud_sel_src(data)                                          ((0x00000001&(data))>>0)
#define PFUNC_TP0_get_tp0_clk_pud_sel(data)                                          ((0x00000001&(data))>>0)


#define PFUNC_TP1                                                                    0x98000390
#define PFUNC_TP1_reg_addr                                                           "0x98000390"
#define PFUNC_TP1_reg                                                                0x98000390
#define set_PFUNC_TP1_reg(data)   (*((volatile unsigned int*) PFUNC_TP1_reg)=data)
#define get_PFUNC_TP1_reg   (*((volatile unsigned int*) PFUNC_TP1_reg))
#define PFUNC_TP1_inst_adr                                                           "0x00E4"
#define PFUNC_TP1_inst                                                               0x00E4
#define PFUNC_TP1_tp1_data_smt_shift                                                 (15)
#define PFUNC_TP1_tp1_data_smt_mask                                                  (0x00008000)
#define PFUNC_TP1_tp1_data_smt(data)                                                 (0x00008000&((data)<<15))
#define PFUNC_TP1_tp1_data_smt_src(data)                                             ((0x00008000&(data))>>15)
#define PFUNC_TP1_get_tp1_data_smt(data)                                             ((0x00008000&(data))>>15)
#define PFUNC_TP1_tp1_data_e2_shift                                                  (14)
#define PFUNC_TP1_tp1_data_e2_mask                                                   (0x00004000)
#define PFUNC_TP1_tp1_data_e2(data)                                                  (0x00004000&((data)<<14))
#define PFUNC_TP1_tp1_data_e2_src(data)                                              ((0x00004000&(data))>>14)
#define PFUNC_TP1_get_tp1_data_e2(data)                                              ((0x00004000&(data))>>14)
#define PFUNC_TP1_tp1_data_pud_en_shift                                              (13)
#define PFUNC_TP1_tp1_data_pud_en_mask                                               (0x00002000)
#define PFUNC_TP1_tp1_data_pud_en(data)                                              (0x00002000&((data)<<13))
#define PFUNC_TP1_tp1_data_pud_en_src(data)                                          ((0x00002000&(data))>>13)
#define PFUNC_TP1_get_tp1_data_pud_en(data)                                          ((0x00002000&(data))>>13)
#define PFUNC_TP1_tp1_data_pud_sel_shift                                             (12)
#define PFUNC_TP1_tp1_data_pud_sel_mask                                              (0x00001000)
#define PFUNC_TP1_tp1_data_pud_sel(data)                                             (0x00001000&((data)<<12))
#define PFUNC_TP1_tp1_data_pud_sel_src(data)                                         ((0x00001000&(data))>>12)
#define PFUNC_TP1_get_tp1_data_pud_sel(data)                                         ((0x00001000&(data))>>12)
#define PFUNC_TP1_tp1_valid_smt_shift                                                (11)
#define PFUNC_TP1_tp1_valid_smt_mask                                                 (0x00000800)
#define PFUNC_TP1_tp1_valid_smt(data)                                                (0x00000800&((data)<<11))
#define PFUNC_TP1_tp1_valid_smt_src(data)                                            ((0x00000800&(data))>>11)
#define PFUNC_TP1_get_tp1_valid_smt(data)                                            ((0x00000800&(data))>>11)
#define PFUNC_TP1_tp1_valid_e2_shift                                                 (10)
#define PFUNC_TP1_tp1_valid_e2_mask                                                  (0x00000400)
#define PFUNC_TP1_tp1_valid_e2(data)                                                 (0x00000400&((data)<<10))
#define PFUNC_TP1_tp1_valid_e2_src(data)                                             ((0x00000400&(data))>>10)
#define PFUNC_TP1_get_tp1_valid_e2(data)                                             ((0x00000400&(data))>>10)
#define PFUNC_TP1_tp1_valid_pud_en_shift                                             (9)
#define PFUNC_TP1_tp1_valid_pud_en_mask                                              (0x00000200)
#define PFUNC_TP1_tp1_valid_pud_en(data)                                             (0x00000200&((data)<<9))
#define PFUNC_TP1_tp1_valid_pud_en_src(data)                                         ((0x00000200&(data))>>9)
#define PFUNC_TP1_get_tp1_valid_pud_en(data)                                         ((0x00000200&(data))>>9)
#define PFUNC_TP1_tp1_valid_pud_sel_shift                                            (8)
#define PFUNC_TP1_tp1_valid_pud_sel_mask                                             (0x00000100)
#define PFUNC_TP1_tp1_valid_pud_sel(data)                                            (0x00000100&((data)<<8))
#define PFUNC_TP1_tp1_valid_pud_sel_src(data)                                        ((0x00000100&(data))>>8)
#define PFUNC_TP1_get_tp1_valid_pud_sel(data)                                        ((0x00000100&(data))>>8)
#define PFUNC_TP1_tp1_sync_smt_shift                                                 (7)
#define PFUNC_TP1_tp1_sync_smt_mask                                                  (0x00000080)
#define PFUNC_TP1_tp1_sync_smt(data)                                                 (0x00000080&((data)<<7))
#define PFUNC_TP1_tp1_sync_smt_src(data)                                             ((0x00000080&(data))>>7)
#define PFUNC_TP1_get_tp1_sync_smt(data)                                             ((0x00000080&(data))>>7)
#define PFUNC_TP1_tp1_sync_e2_shift                                                  (6)
#define PFUNC_TP1_tp1_sync_e2_mask                                                   (0x00000040)
#define PFUNC_TP1_tp1_sync_e2(data)                                                  (0x00000040&((data)<<6))
#define PFUNC_TP1_tp1_sync_e2_src(data)                                              ((0x00000040&(data))>>6)
#define PFUNC_TP1_get_tp1_sync_e2(data)                                              ((0x00000040&(data))>>6)
#define PFUNC_TP1_tp1_sync_pud_en_shift                                              (5)
#define PFUNC_TP1_tp1_sync_pud_en_mask                                               (0x00000020)
#define PFUNC_TP1_tp1_sync_pud_en(data)                                              (0x00000020&((data)<<5))
#define PFUNC_TP1_tp1_sync_pud_en_src(data)                                          ((0x00000020&(data))>>5)
#define PFUNC_TP1_get_tp1_sync_pud_en(data)                                          ((0x00000020&(data))>>5)
#define PFUNC_TP1_tp1_sync_pud_sel_shift                                             (4)
#define PFUNC_TP1_tp1_sync_pud_sel_mask                                              (0x00000010)
#define PFUNC_TP1_tp1_sync_pud_sel(data)                                             (0x00000010&((data)<<4))
#define PFUNC_TP1_tp1_sync_pud_sel_src(data)                                         ((0x00000010&(data))>>4)
#define PFUNC_TP1_get_tp1_sync_pud_sel(data)                                         ((0x00000010&(data))>>4)
#define PFUNC_TP1_tp1_clk_smt_shift                                                  (3)
#define PFUNC_TP1_tp1_clk_smt_mask                                                   (0x00000008)
#define PFUNC_TP1_tp1_clk_smt(data)                                                  (0x00000008&((data)<<3))
#define PFUNC_TP1_tp1_clk_smt_src(data)                                              ((0x00000008&(data))>>3)
#define PFUNC_TP1_get_tp1_clk_smt(data)                                              ((0x00000008&(data))>>3)
#define PFUNC_TP1_tp1_clk_e2_shift                                                   (2)
#define PFUNC_TP1_tp1_clk_e2_mask                                                    (0x00000004)
#define PFUNC_TP1_tp1_clk_e2(data)                                                   (0x00000004&((data)<<2))
#define PFUNC_TP1_tp1_clk_e2_src(data)                                               ((0x00000004&(data))>>2)
#define PFUNC_TP1_get_tp1_clk_e2(data)                                               ((0x00000004&(data))>>2)
#define PFUNC_TP1_tp1_clk_pud_en_shift                                               (1)
#define PFUNC_TP1_tp1_clk_pud_en_mask                                                (0x00000002)
#define PFUNC_TP1_tp1_clk_pud_en(data)                                               (0x00000002&((data)<<1))
#define PFUNC_TP1_tp1_clk_pud_en_src(data)                                           ((0x00000002&(data))>>1)
#define PFUNC_TP1_get_tp1_clk_pud_en(data)                                           ((0x00000002&(data))>>1)
#define PFUNC_TP1_tp1_clk_pud_sel_shift                                              (0)
#define PFUNC_TP1_tp1_clk_pud_sel_mask                                               (0x00000001)
#define PFUNC_TP1_tp1_clk_pud_sel(data)                                              (0x00000001&((data)<<0))
#define PFUNC_TP1_tp1_clk_pud_sel_src(data)                                          ((0x00000001&(data))>>0)
#define PFUNC_TP1_get_tp1_clk_pud_sel(data)                                          ((0x00000001&(data))>>0)


#define PFUNC_MISC0                                                                  0x98000394
#define PFUNC_MISC0_reg_addr                                                         "0x98000394"
#define PFUNC_MISC0_reg                                                              0x98000394
#define set_PFUNC_MISC0_reg(data)   (*((volatile unsigned int*) PFUNC_MISC0_reg)=data)
#define get_PFUNC_MISC0_reg   (*((volatile unsigned int*) PFUNC_MISC0_reg))
#define PFUNC_MISC0_inst_adr                                                         "0x00E5"
#define PFUNC_MISC0_inst                                                             0x00E5
#define PFUNC_MISC0_i2c_scl_5_smt_shift                                              (23)
#define PFUNC_MISC0_i2c_scl_5_smt_mask                                               (0x00800000)
#define PFUNC_MISC0_i2c_scl_5_smt(data)                                              (0x00800000&((data)<<23))
#define PFUNC_MISC0_i2c_scl_5_smt_src(data)                                          ((0x00800000&(data))>>23)
#define PFUNC_MISC0_get_i2c_scl_5_smt(data)                                          ((0x00800000&(data))>>23)
#define PFUNC_MISC0_i2c_scl_5_e2_shift                                               (22)
#define PFUNC_MISC0_i2c_scl_5_e2_mask                                                (0x00400000)
#define PFUNC_MISC0_i2c_scl_5_e2(data)                                               (0x00400000&((data)<<22))
#define PFUNC_MISC0_i2c_scl_5_e2_src(data)                                           ((0x00400000&(data))>>22)
#define PFUNC_MISC0_get_i2c_scl_5_e2(data)                                           ((0x00400000&(data))>>22)
#define PFUNC_MISC0_i2c_scl_5_pud_en_shift                                           (21)
#define PFUNC_MISC0_i2c_scl_5_pud_en_mask                                            (0x00200000)
#define PFUNC_MISC0_i2c_scl_5_pud_en(data)                                           (0x00200000&((data)<<21))
#define PFUNC_MISC0_i2c_scl_5_pud_en_src(data)                                       ((0x00200000&(data))>>21)
#define PFUNC_MISC0_get_i2c_scl_5_pud_en(data)                                       ((0x00200000&(data))>>21)
#define PFUNC_MISC0_i2c_scl_5_pud_sel_shift                                          (20)
#define PFUNC_MISC0_i2c_scl_5_pud_sel_mask                                           (0x00100000)
#define PFUNC_MISC0_i2c_scl_5_pud_sel(data)                                          (0x00100000&((data)<<20))
#define PFUNC_MISC0_i2c_scl_5_pud_sel_src(data)                                      ((0x00100000&(data))>>20)
#define PFUNC_MISC0_get_i2c_scl_5_pud_sel(data)                                      ((0x00100000&(data))>>20)
#define PFUNC_MISC0_i2c_sda_5_smt_shift                                              (19)
#define PFUNC_MISC0_i2c_sda_5_smt_mask                                               (0x00080000)
#define PFUNC_MISC0_i2c_sda_5_smt(data)                                              (0x00080000&((data)<<19))
#define PFUNC_MISC0_i2c_sda_5_smt_src(data)                                          ((0x00080000&(data))>>19)
#define PFUNC_MISC0_get_i2c_sda_5_smt(data)                                          ((0x00080000&(data))>>19)
#define PFUNC_MISC0_i2c_sda_5_e2_shift                                               (18)
#define PFUNC_MISC0_i2c_sda_5_e2_mask                                                (0x00040000)
#define PFUNC_MISC0_i2c_sda_5_e2(data)                                               (0x00040000&((data)<<18))
#define PFUNC_MISC0_i2c_sda_5_e2_src(data)                                           ((0x00040000&(data))>>18)
#define PFUNC_MISC0_get_i2c_sda_5_e2(data)                                           ((0x00040000&(data))>>18)
#define PFUNC_MISC0_i2c_sda_5_pud_en_shift                                           (17)
#define PFUNC_MISC0_i2c_sda_5_pud_en_mask                                            (0x00020000)
#define PFUNC_MISC0_i2c_sda_5_pud_en(data)                                           (0x00020000&((data)<<17))
#define PFUNC_MISC0_i2c_sda_5_pud_en_src(data)                                       ((0x00020000&(data))>>17)
#define PFUNC_MISC0_get_i2c_sda_5_pud_en(data)                                       ((0x00020000&(data))>>17)
#define PFUNC_MISC0_i2c_sda_5_pud_sel_shift                                          (16)
#define PFUNC_MISC0_i2c_sda_5_pud_sel_mask                                           (0x00010000)
#define PFUNC_MISC0_i2c_sda_5_pud_sel(data)                                          (0x00010000&((data)<<16))
#define PFUNC_MISC0_i2c_sda_5_pud_sel_src(data)                                      ((0x00010000&(data))>>16)
#define PFUNC_MISC0_get_i2c_sda_5_pud_sel(data)                                      ((0x00010000&(data))>>16)
#define PFUNC_MISC0_i2c_scl_4_smt_shift                                              (15)
#define PFUNC_MISC0_i2c_scl_4_smt_mask                                               (0x00008000)
#define PFUNC_MISC0_i2c_scl_4_smt(data)                                              (0x00008000&((data)<<15))
#define PFUNC_MISC0_i2c_scl_4_smt_src(data)                                          ((0x00008000&(data))>>15)
#define PFUNC_MISC0_get_i2c_scl_4_smt(data)                                          ((0x00008000&(data))>>15)
#define PFUNC_MISC0_i2c_scl_4_e2_shift                                               (14)
#define PFUNC_MISC0_i2c_scl_4_e2_mask                                                (0x00004000)
#define PFUNC_MISC0_i2c_scl_4_e2(data)                                               (0x00004000&((data)<<14))
#define PFUNC_MISC0_i2c_scl_4_e2_src(data)                                           ((0x00004000&(data))>>14)
#define PFUNC_MISC0_get_i2c_scl_4_e2(data)                                           ((0x00004000&(data))>>14)
#define PFUNC_MISC0_i2c_scl_4_pud_en_shift                                           (13)
#define PFUNC_MISC0_i2c_scl_4_pud_en_mask                                            (0x00002000)
#define PFUNC_MISC0_i2c_scl_4_pud_en(data)                                           (0x00002000&((data)<<13))
#define PFUNC_MISC0_i2c_scl_4_pud_en_src(data)                                       ((0x00002000&(data))>>13)
#define PFUNC_MISC0_get_i2c_scl_4_pud_en(data)                                       ((0x00002000&(data))>>13)
#define PFUNC_MISC0_i2c_scl_4_pud_sel_shift                                          (12)
#define PFUNC_MISC0_i2c_scl_4_pud_sel_mask                                           (0x00001000)
#define PFUNC_MISC0_i2c_scl_4_pud_sel(data)                                          (0x00001000&((data)<<12))
#define PFUNC_MISC0_i2c_scl_4_pud_sel_src(data)                                      ((0x00001000&(data))>>12)
#define PFUNC_MISC0_get_i2c_scl_4_pud_sel(data)                                      ((0x00001000&(data))>>12)
#define PFUNC_MISC0_i2c_sda_4_smt_shift                                              (11)
#define PFUNC_MISC0_i2c_sda_4_smt_mask                                               (0x00000800)
#define PFUNC_MISC0_i2c_sda_4_smt(data)                                              (0x00000800&((data)<<11))
#define PFUNC_MISC0_i2c_sda_4_smt_src(data)                                          ((0x00000800&(data))>>11)
#define PFUNC_MISC0_get_i2c_sda_4_smt(data)                                          ((0x00000800&(data))>>11)
#define PFUNC_MISC0_i2c_sda_4_e2_shift                                               (10)
#define PFUNC_MISC0_i2c_sda_4_e2_mask                                                (0x00000400)
#define PFUNC_MISC0_i2c_sda_4_e2(data)                                               (0x00000400&((data)<<10))
#define PFUNC_MISC0_i2c_sda_4_e2_src(data)                                           ((0x00000400&(data))>>10)
#define PFUNC_MISC0_get_i2c_sda_4_e2(data)                                           ((0x00000400&(data))>>10)
#define PFUNC_MISC0_i2c_sda_4_pud_en_shift                                           (9)
#define PFUNC_MISC0_i2c_sda_4_pud_en_mask                                            (0x00000200)
#define PFUNC_MISC0_i2c_sda_4_pud_en(data)                                           (0x00000200&((data)<<9))
#define PFUNC_MISC0_i2c_sda_4_pud_en_src(data)                                       ((0x00000200&(data))>>9)
#define PFUNC_MISC0_get_i2c_sda_4_pud_en(data)                                       ((0x00000200&(data))>>9)
#define PFUNC_MISC0_i2c_sda_4_pud_sel_shift                                          (8)
#define PFUNC_MISC0_i2c_sda_4_pud_sel_mask                                           (0x00000100)
#define PFUNC_MISC0_i2c_sda_4_pud_sel(data)                                          (0x00000100&((data)<<8))
#define PFUNC_MISC0_i2c_sda_4_pud_sel_src(data)                                      ((0x00000100&(data))>>8)
#define PFUNC_MISC0_get_i2c_sda_4_pud_sel(data)                                      ((0x00000100&(data))>>8)
#define PFUNC_MISC0_i2c_scl_1_smt_shift                                              (7)
#define PFUNC_MISC0_i2c_scl_1_smt_mask                                               (0x00000080)
#define PFUNC_MISC0_i2c_scl_1_smt(data)                                              (0x00000080&((data)<<7))
#define PFUNC_MISC0_i2c_scl_1_smt_src(data)                                          ((0x00000080&(data))>>7)
#define PFUNC_MISC0_get_i2c_scl_1_smt(data)                                          ((0x00000080&(data))>>7)
#define PFUNC_MISC0_i2c_scl_1_e2_shift                                               (6)
#define PFUNC_MISC0_i2c_scl_1_e2_mask                                                (0x00000040)
#define PFUNC_MISC0_i2c_scl_1_e2(data)                                               (0x00000040&((data)<<6))
#define PFUNC_MISC0_i2c_scl_1_e2_src(data)                                           ((0x00000040&(data))>>6)
#define PFUNC_MISC0_get_i2c_scl_1_e2(data)                                           ((0x00000040&(data))>>6)
#define PFUNC_MISC0_i2c_scl_1_pud_en_shift                                           (5)
#define PFUNC_MISC0_i2c_scl_1_pud_en_mask                                            (0x00000020)
#define PFUNC_MISC0_i2c_scl_1_pud_en(data)                                           (0x00000020&((data)<<5))
#define PFUNC_MISC0_i2c_scl_1_pud_en_src(data)                                       ((0x00000020&(data))>>5)
#define PFUNC_MISC0_get_i2c_scl_1_pud_en(data)                                       ((0x00000020&(data))>>5)
#define PFUNC_MISC0_i2c_scl_1_pud_sel_shift                                          (4)
#define PFUNC_MISC0_i2c_scl_1_pud_sel_mask                                           (0x00000010)
#define PFUNC_MISC0_i2c_scl_1_pud_sel(data)                                          (0x00000010&((data)<<4))
#define PFUNC_MISC0_i2c_scl_1_pud_sel_src(data)                                      ((0x00000010&(data))>>4)
#define PFUNC_MISC0_get_i2c_scl_1_pud_sel(data)                                      ((0x00000010&(data))>>4)
#define PFUNC_MISC0_i2c_sda_1_smt_shift                                              (3)
#define PFUNC_MISC0_i2c_sda_1_smt_mask                                               (0x00000008)
#define PFUNC_MISC0_i2c_sda_1_smt(data)                                              (0x00000008&((data)<<3))
#define PFUNC_MISC0_i2c_sda_1_smt_src(data)                                          ((0x00000008&(data))>>3)
#define PFUNC_MISC0_get_i2c_sda_1_smt(data)                                          ((0x00000008&(data))>>3)
#define PFUNC_MISC0_i2c_sda_1_e2_shift                                               (2)
#define PFUNC_MISC0_i2c_sda_1_e2_mask                                                (0x00000004)
#define PFUNC_MISC0_i2c_sda_1_e2(data)                                               (0x00000004&((data)<<2))
#define PFUNC_MISC0_i2c_sda_1_e2_src(data)                                           ((0x00000004&(data))>>2)
#define PFUNC_MISC0_get_i2c_sda_1_e2(data)                                           ((0x00000004&(data))>>2)
#define PFUNC_MISC0_i2c_sda_1_pud_en_shift                                           (1)
#define PFUNC_MISC0_i2c_sda_1_pud_en_mask                                            (0x00000002)
#define PFUNC_MISC0_i2c_sda_1_pud_en(data)                                           (0x00000002&((data)<<1))
#define PFUNC_MISC0_i2c_sda_1_pud_en_src(data)                                       ((0x00000002&(data))>>1)
#define PFUNC_MISC0_get_i2c_sda_1_pud_en(data)                                       ((0x00000002&(data))>>1)
#define PFUNC_MISC0_i2c_sda_1_pud_sel_shift                                          (0)
#define PFUNC_MISC0_i2c_sda_1_pud_sel_mask                                           (0x00000001)
#define PFUNC_MISC0_i2c_sda_1_pud_sel(data)                                          (0x00000001&((data)<<0))
#define PFUNC_MISC0_i2c_sda_1_pud_sel_src(data)                                      ((0x00000001&(data))>>0)
#define PFUNC_MISC0_get_i2c_sda_1_pud_sel(data)                                      ((0x00000001&(data))>>0)


#define PFUNC_MISC1                                                                  0x98000398
#define PFUNC_MISC1_reg_addr                                                         "0x98000398"
#define PFUNC_MISC1_reg                                                              0x98000398
#define set_PFUNC_MISC1_reg(data)   (*((volatile unsigned int*) PFUNC_MISC1_reg)=data)
#define get_PFUNC_MISC1_reg   (*((volatile unsigned int*) PFUNC_MISC1_reg))
#define PFUNC_MISC1_inst_adr                                                         "0x00E6"
#define PFUNC_MISC1_inst                                                             0x00E6
#define PFUNC_MISC1_gpio_7_smt_shift                                                 (31)
#define PFUNC_MISC1_gpio_7_smt_mask                                                  (0x80000000)
#define PFUNC_MISC1_gpio_7_smt(data)                                                 (0x80000000&((data)<<31))
#define PFUNC_MISC1_gpio_7_smt_src(data)                                             ((0x80000000&(data))>>31)
#define PFUNC_MISC1_get_gpio_7_smt(data)                                             ((0x80000000&(data))>>31)
#define PFUNC_MISC1_gpio_7_e2_shift                                                  (30)
#define PFUNC_MISC1_gpio_7_e2_mask                                                   (0x40000000)
#define PFUNC_MISC1_gpio_7_e2(data)                                                  (0x40000000&((data)<<30))
#define PFUNC_MISC1_gpio_7_e2_src(data)                                              ((0x40000000&(data))>>30)
#define PFUNC_MISC1_get_gpio_7_e2(data)                                              ((0x40000000&(data))>>30)
#define PFUNC_MISC1_gpio_7_pud_en_shift                                              (29)
#define PFUNC_MISC1_gpio_7_pud_en_mask                                               (0x20000000)
#define PFUNC_MISC1_gpio_7_pud_en(data)                                              (0x20000000&((data)<<29))
#define PFUNC_MISC1_gpio_7_pud_en_src(data)                                          ((0x20000000&(data))>>29)
#define PFUNC_MISC1_get_gpio_7_pud_en(data)                                          ((0x20000000&(data))>>29)
#define PFUNC_MISC1_gpio_7_pud_sel_shift                                             (28)
#define PFUNC_MISC1_gpio_7_pud_sel_mask                                              (0x10000000)
#define PFUNC_MISC1_gpio_7_pud_sel(data)                                             (0x10000000&((data)<<28))
#define PFUNC_MISC1_gpio_7_pud_sel_src(data)                                         ((0x10000000&(data))>>28)
#define PFUNC_MISC1_get_gpio_7_pud_sel(data)                                         ((0x10000000&(data))>>28)
#define PFUNC_MISC1_gpio_6_smt_shift                                                 (27)
#define PFUNC_MISC1_gpio_6_smt_mask                                                  (0x08000000)
#define PFUNC_MISC1_gpio_6_smt(data)                                                 (0x08000000&((data)<<27))
#define PFUNC_MISC1_gpio_6_smt_src(data)                                             ((0x08000000&(data))>>27)
#define PFUNC_MISC1_get_gpio_6_smt(data)                                             ((0x08000000&(data))>>27)
#define PFUNC_MISC1_gpio_6_e2_shift                                                  (26)
#define PFUNC_MISC1_gpio_6_e2_mask                                                   (0x04000000)
#define PFUNC_MISC1_gpio_6_e2(data)                                                  (0x04000000&((data)<<26))
#define PFUNC_MISC1_gpio_6_e2_src(data)                                              ((0x04000000&(data))>>26)
#define PFUNC_MISC1_get_gpio_6_e2(data)                                              ((0x04000000&(data))>>26)
#define PFUNC_MISC1_gpio_6_pud_en_shift                                              (25)
#define PFUNC_MISC1_gpio_6_pud_en_mask                                               (0x02000000)
#define PFUNC_MISC1_gpio_6_pud_en(data)                                              (0x02000000&((data)<<25))
#define PFUNC_MISC1_gpio_6_pud_en_src(data)                                          ((0x02000000&(data))>>25)
#define PFUNC_MISC1_get_gpio_6_pud_en(data)                                          ((0x02000000&(data))>>25)
#define PFUNC_MISC1_gpio_6_pud_sel_shift                                             (24)
#define PFUNC_MISC1_gpio_6_pud_sel_mask                                              (0x01000000)
#define PFUNC_MISC1_gpio_6_pud_sel(data)                                             (0x01000000&((data)<<24))
#define PFUNC_MISC1_gpio_6_pud_sel_src(data)                                         ((0x01000000&(data))>>24)
#define PFUNC_MISC1_get_gpio_6_pud_sel(data)                                         ((0x01000000&(data))>>24)
#define PFUNC_MISC1_gpio_5_smt_shift                                                 (23)
#define PFUNC_MISC1_gpio_5_smt_mask                                                  (0x00800000)
#define PFUNC_MISC1_gpio_5_smt(data)                                                 (0x00800000&((data)<<23))
#define PFUNC_MISC1_gpio_5_smt_src(data)                                             ((0x00800000&(data))>>23)
#define PFUNC_MISC1_get_gpio_5_smt(data)                                             ((0x00800000&(data))>>23)
#define PFUNC_MISC1_gpio_5_e2_shift                                                  (22)
#define PFUNC_MISC1_gpio_5_e2_mask                                                   (0x00400000)
#define PFUNC_MISC1_gpio_5_e2(data)                                                  (0x00400000&((data)<<22))
#define PFUNC_MISC1_gpio_5_e2_src(data)                                              ((0x00400000&(data))>>22)
#define PFUNC_MISC1_get_gpio_5_e2(data)                                              ((0x00400000&(data))>>22)
#define PFUNC_MISC1_gpio_5_pud_en_shift                                              (21)
#define PFUNC_MISC1_gpio_5_pud_en_mask                                               (0x00200000)
#define PFUNC_MISC1_gpio_5_pud_en(data)                                              (0x00200000&((data)<<21))
#define PFUNC_MISC1_gpio_5_pud_en_src(data)                                          ((0x00200000&(data))>>21)
#define PFUNC_MISC1_get_gpio_5_pud_en(data)                                          ((0x00200000&(data))>>21)
#define PFUNC_MISC1_gpio_5_pud_sel_shift                                             (20)
#define PFUNC_MISC1_gpio_5_pud_sel_mask                                              (0x00100000)
#define PFUNC_MISC1_gpio_5_pud_sel(data)                                             (0x00100000&((data)<<20))
#define PFUNC_MISC1_gpio_5_pud_sel_src(data)                                         ((0x00100000&(data))>>20)
#define PFUNC_MISC1_get_gpio_5_pud_sel(data)                                         ((0x00100000&(data))>>20)
#define PFUNC_MISC1_gpio_4_smt_shift                                                 (19)
#define PFUNC_MISC1_gpio_4_smt_mask                                                  (0x00080000)
#define PFUNC_MISC1_gpio_4_smt(data)                                                 (0x00080000&((data)<<19))
#define PFUNC_MISC1_gpio_4_smt_src(data)                                             ((0x00080000&(data))>>19)
#define PFUNC_MISC1_get_gpio_4_smt(data)                                             ((0x00080000&(data))>>19)
#define PFUNC_MISC1_gpio_4_e2_shift                                                  (18)
#define PFUNC_MISC1_gpio_4_e2_mask                                                   (0x00040000)
#define PFUNC_MISC1_gpio_4_e2(data)                                                  (0x00040000&((data)<<18))
#define PFUNC_MISC1_gpio_4_e2_src(data)                                              ((0x00040000&(data))>>18)
#define PFUNC_MISC1_get_gpio_4_e2(data)                                              ((0x00040000&(data))>>18)
#define PFUNC_MISC1_gpio_4_pud_en_shift                                              (17)
#define PFUNC_MISC1_gpio_4_pud_en_mask                                               (0x00020000)
#define PFUNC_MISC1_gpio_4_pud_en(data)                                              (0x00020000&((data)<<17))
#define PFUNC_MISC1_gpio_4_pud_en_src(data)                                          ((0x00020000&(data))>>17)
#define PFUNC_MISC1_get_gpio_4_pud_en(data)                                          ((0x00020000&(data))>>17)
#define PFUNC_MISC1_gpio_4_pud_sel_shift                                             (16)
#define PFUNC_MISC1_gpio_4_pud_sel_mask                                              (0x00010000)
#define PFUNC_MISC1_gpio_4_pud_sel(data)                                             (0x00010000&((data)<<16))
#define PFUNC_MISC1_gpio_4_pud_sel_src(data)                                         ((0x00010000&(data))>>16)
#define PFUNC_MISC1_get_gpio_4_pud_sel(data)                                         ((0x00010000&(data))>>16)
#define PFUNC_MISC1_gpio_3_smt_shift                                                 (15)
#define PFUNC_MISC1_gpio_3_smt_mask                                                  (0x00008000)
#define PFUNC_MISC1_gpio_3_smt(data)                                                 (0x00008000&((data)<<15))
#define PFUNC_MISC1_gpio_3_smt_src(data)                                             ((0x00008000&(data))>>15)
#define PFUNC_MISC1_get_gpio_3_smt(data)                                             ((0x00008000&(data))>>15)
#define PFUNC_MISC1_gpio_3_e2_shift                                                  (14)
#define PFUNC_MISC1_gpio_3_e2_mask                                                   (0x00004000)
#define PFUNC_MISC1_gpio_3_e2(data)                                                  (0x00004000&((data)<<14))
#define PFUNC_MISC1_gpio_3_e2_src(data)                                              ((0x00004000&(data))>>14)
#define PFUNC_MISC1_get_gpio_3_e2(data)                                              ((0x00004000&(data))>>14)
#define PFUNC_MISC1_gpio_3_pud_en_shift                                              (13)
#define PFUNC_MISC1_gpio_3_pud_en_mask                                               (0x00002000)
#define PFUNC_MISC1_gpio_3_pud_en(data)                                              (0x00002000&((data)<<13))
#define PFUNC_MISC1_gpio_3_pud_en_src(data)                                          ((0x00002000&(data))>>13)
#define PFUNC_MISC1_get_gpio_3_pud_en(data)                                          ((0x00002000&(data))>>13)
#define PFUNC_MISC1_gpio_3_pud_sel_shift                                             (12)
#define PFUNC_MISC1_gpio_3_pud_sel_mask                                              (0x00001000)
#define PFUNC_MISC1_gpio_3_pud_sel(data)                                             (0x00001000&((data)<<12))
#define PFUNC_MISC1_gpio_3_pud_sel_src(data)                                         ((0x00001000&(data))>>12)
#define PFUNC_MISC1_get_gpio_3_pud_sel(data)                                         ((0x00001000&(data))>>12)
#define PFUNC_MISC1_gpio_2_smt_shift                                                 (11)
#define PFUNC_MISC1_gpio_2_smt_mask                                                  (0x00000800)
#define PFUNC_MISC1_gpio_2_smt(data)                                                 (0x00000800&((data)<<11))
#define PFUNC_MISC1_gpio_2_smt_src(data)                                             ((0x00000800&(data))>>11)
#define PFUNC_MISC1_get_gpio_2_smt(data)                                             ((0x00000800&(data))>>11)
#define PFUNC_MISC1_gpio_2_e2_shift                                                  (10)
#define PFUNC_MISC1_gpio_2_e2_mask                                                   (0x00000400)
#define PFUNC_MISC1_gpio_2_e2(data)                                                  (0x00000400&((data)<<10))
#define PFUNC_MISC1_gpio_2_e2_src(data)                                              ((0x00000400&(data))>>10)
#define PFUNC_MISC1_get_gpio_2_e2(data)                                              ((0x00000400&(data))>>10)
#define PFUNC_MISC1_gpio_2_pud_en_shift                                              (9)
#define PFUNC_MISC1_gpio_2_pud_en_mask                                               (0x00000200)
#define PFUNC_MISC1_gpio_2_pud_en(data)                                              (0x00000200&((data)<<9))
#define PFUNC_MISC1_gpio_2_pud_en_src(data)                                          ((0x00000200&(data))>>9)
#define PFUNC_MISC1_get_gpio_2_pud_en(data)                                          ((0x00000200&(data))>>9)
#define PFUNC_MISC1_gpio_2_pud_sel_shift                                             (8)
#define PFUNC_MISC1_gpio_2_pud_sel_mask                                              (0x00000100)
#define PFUNC_MISC1_gpio_2_pud_sel(data)                                             (0x00000100&((data)<<8))
#define PFUNC_MISC1_gpio_2_pud_sel_src(data)                                         ((0x00000100&(data))>>8)
#define PFUNC_MISC1_get_gpio_2_pud_sel(data)                                         ((0x00000100&(data))>>8)
#define PFUNC_MISC1_gpio_1_smt_shift                                                 (7)
#define PFUNC_MISC1_gpio_1_smt_mask                                                  (0x00000080)
#define PFUNC_MISC1_gpio_1_smt(data)                                                 (0x00000080&((data)<<7))
#define PFUNC_MISC1_gpio_1_smt_src(data)                                             ((0x00000080&(data))>>7)
#define PFUNC_MISC1_get_gpio_1_smt(data)                                             ((0x00000080&(data))>>7)
#define PFUNC_MISC1_gpio_1_e2_shift                                                  (6)
#define PFUNC_MISC1_gpio_1_e2_mask                                                   (0x00000040)
#define PFUNC_MISC1_gpio_1_e2(data)                                                  (0x00000040&((data)<<6))
#define PFUNC_MISC1_gpio_1_e2_src(data)                                              ((0x00000040&(data))>>6)
#define PFUNC_MISC1_get_gpio_1_e2(data)                                              ((0x00000040&(data))>>6)
#define PFUNC_MISC1_gpio_1_pud_en_shift                                              (5)
#define PFUNC_MISC1_gpio_1_pud_en_mask                                               (0x00000020)
#define PFUNC_MISC1_gpio_1_pud_en(data)                                              (0x00000020&((data)<<5))
#define PFUNC_MISC1_gpio_1_pud_en_src(data)                                          ((0x00000020&(data))>>5)
#define PFUNC_MISC1_get_gpio_1_pud_en(data)                                          ((0x00000020&(data))>>5)
#define PFUNC_MISC1_gpio_1_pud_sel_shift                                             (4)
#define PFUNC_MISC1_gpio_1_pud_sel_mask                                              (0x00000010)
#define PFUNC_MISC1_gpio_1_pud_sel(data)                                             (0x00000010&((data)<<4))
#define PFUNC_MISC1_gpio_1_pud_sel_src(data)                                         ((0x00000010&(data))>>4)
#define PFUNC_MISC1_get_gpio_1_pud_sel(data)                                         ((0x00000010&(data))>>4)
#define PFUNC_MISC1_gpio_0_smt_shift                                                 (3)
#define PFUNC_MISC1_gpio_0_smt_mask                                                  (0x00000008)
#define PFUNC_MISC1_gpio_0_smt(data)                                                 (0x00000008&((data)<<3))
#define PFUNC_MISC1_gpio_0_smt_src(data)                                             ((0x00000008&(data))>>3)
#define PFUNC_MISC1_get_gpio_0_smt(data)                                             ((0x00000008&(data))>>3)
#define PFUNC_MISC1_gpio_0_e2_shift                                                  (2)
#define PFUNC_MISC1_gpio_0_e2_mask                                                   (0x00000004)
#define PFUNC_MISC1_gpio_0_e2(data)                                                  (0x00000004&((data)<<2))
#define PFUNC_MISC1_gpio_0_e2_src(data)                                              ((0x00000004&(data))>>2)
#define PFUNC_MISC1_get_gpio_0_e2(data)                                              ((0x00000004&(data))>>2)
#define PFUNC_MISC1_gpio_0_pud_en_shift                                              (1)
#define PFUNC_MISC1_gpio_0_pud_en_mask                                               (0x00000002)
#define PFUNC_MISC1_gpio_0_pud_en(data)                                              (0x00000002&((data)<<1))
#define PFUNC_MISC1_gpio_0_pud_en_src(data)                                          ((0x00000002&(data))>>1)
#define PFUNC_MISC1_get_gpio_0_pud_en(data)                                          ((0x00000002&(data))>>1)
#define PFUNC_MISC1_gpio_0_pud_sel_shift                                             (0)
#define PFUNC_MISC1_gpio_0_pud_sel_mask                                              (0x00000001)
#define PFUNC_MISC1_gpio_0_pud_sel(data)                                             (0x00000001&((data)<<0))
#define PFUNC_MISC1_gpio_0_pud_sel_src(data)                                         ((0x00000001&(data))>>0)
#define PFUNC_MISC1_get_gpio_0_pud_sel(data)                                         ((0x00000001&(data))>>0)


#define PFUNC_MISC2                                                                  0x9800039C
#define PFUNC_MISC2_reg_addr                                                         "0x9800039C"
#define PFUNC_MISC2_reg                                                              0x9800039C
#define set_PFUNC_MISC2_reg(data)   (*((volatile unsigned int*) PFUNC_MISC2_reg)=data)
#define get_PFUNC_MISC2_reg   (*((volatile unsigned int*) PFUNC_MISC2_reg))
#define PFUNC_MISC2_inst_adr                                                         "0x00E7"
#define PFUNC_MISC2_inst                                                             0x00E7
#define PFUNC_MISC2_sensor_cko1_smt_shift                                            (31)
#define PFUNC_MISC2_sensor_cko1_smt_mask                                             (0x80000000)
#define PFUNC_MISC2_sensor_cko1_smt(data)                                            (0x80000000&((data)<<31))
#define PFUNC_MISC2_sensor_cko1_smt_src(data)                                        ((0x80000000&(data))>>31)
#define PFUNC_MISC2_get_sensor_cko1_smt(data)                                        ((0x80000000&(data))>>31)
#define PFUNC_MISC2_sensor_cko1_e2_shift                                             (30)
#define PFUNC_MISC2_sensor_cko1_e2_mask                                              (0x40000000)
#define PFUNC_MISC2_sensor_cko1_e2(data)                                             (0x40000000&((data)<<30))
#define PFUNC_MISC2_sensor_cko1_e2_src(data)                                         ((0x40000000&(data))>>30)
#define PFUNC_MISC2_get_sensor_cko1_e2(data)                                         ((0x40000000&(data))>>30)
#define PFUNC_MISC2_sensor_cko1_pud_en_shift                                         (29)
#define PFUNC_MISC2_sensor_cko1_pud_en_mask                                          (0x20000000)
#define PFUNC_MISC2_sensor_cko1_pud_en(data)                                         (0x20000000&((data)<<29))
#define PFUNC_MISC2_sensor_cko1_pud_en_src(data)                                     ((0x20000000&(data))>>29)
#define PFUNC_MISC2_get_sensor_cko1_pud_en(data)                                     ((0x20000000&(data))>>29)
#define PFUNC_MISC2_sensor_cko1_pud_sel_shift                                        (28)
#define PFUNC_MISC2_sensor_cko1_pud_sel_mask                                         (0x10000000)
#define PFUNC_MISC2_sensor_cko1_pud_sel(data)                                        (0x10000000&((data)<<28))
#define PFUNC_MISC2_sensor_cko1_pud_sel_src(data)                                    ((0x10000000&(data))>>28)
#define PFUNC_MISC2_get_sensor_cko1_pud_sel(data)                                    ((0x10000000&(data))>>28)
#define PFUNC_MISC2_sensor_cko0_smt_shift                                            (27)
#define PFUNC_MISC2_sensor_cko0_smt_mask                                             (0x08000000)
#define PFUNC_MISC2_sensor_cko0_smt(data)                                            (0x08000000&((data)<<27))
#define PFUNC_MISC2_sensor_cko0_smt_src(data)                                        ((0x08000000&(data))>>27)
#define PFUNC_MISC2_get_sensor_cko0_smt(data)                                        ((0x08000000&(data))>>27)
#define PFUNC_MISC2_sensor_cko0_e2_shift                                             (26)
#define PFUNC_MISC2_sensor_cko0_e2_mask                                              (0x04000000)
#define PFUNC_MISC2_sensor_cko0_e2(data)                                             (0x04000000&((data)<<26))
#define PFUNC_MISC2_sensor_cko0_e2_src(data)                                         ((0x04000000&(data))>>26)
#define PFUNC_MISC2_get_sensor_cko0_e2(data)                                         ((0x04000000&(data))>>26)
#define PFUNC_MISC2_sensor_cko0_pud_en_shift                                         (25)
#define PFUNC_MISC2_sensor_cko0_pud_en_mask                                          (0x02000000)
#define PFUNC_MISC2_sensor_cko0_pud_en(data)                                         (0x02000000&((data)<<25))
#define PFUNC_MISC2_sensor_cko0_pud_en_src(data)                                     ((0x02000000&(data))>>25)
#define PFUNC_MISC2_get_sensor_cko0_pud_en(data)                                     ((0x02000000&(data))>>25)
#define PFUNC_MISC2_sensor_cko0_pud_sel_shift                                        (24)
#define PFUNC_MISC2_sensor_cko0_pud_sel_mask                                         (0x01000000)
#define PFUNC_MISC2_sensor_cko0_pud_sel(data)                                        (0x01000000&((data)<<24))
#define PFUNC_MISC2_sensor_cko0_pud_sel_src(data)                                    ((0x01000000&(data))>>24)
#define PFUNC_MISC2_get_sensor_cko0_pud_sel(data)                                    ((0x01000000&(data))>>24)
#define PFUNC_MISC2_sensor_rst_smt_shift                                             (23)
#define PFUNC_MISC2_sensor_rst_smt_mask                                              (0x00800000)
#define PFUNC_MISC2_sensor_rst_smt(data)                                             (0x00800000&((data)<<23))
#define PFUNC_MISC2_sensor_rst_smt_src(data)                                         ((0x00800000&(data))>>23)
#define PFUNC_MISC2_get_sensor_rst_smt(data)                                         ((0x00800000&(data))>>23)
#define PFUNC_MISC2_sensor_rst_e2_shift                                              (22)
#define PFUNC_MISC2_sensor_rst_e2_mask                                               (0x00400000)
#define PFUNC_MISC2_sensor_rst_e2(data)                                              (0x00400000&((data)<<22))
#define PFUNC_MISC2_sensor_rst_e2_src(data)                                          ((0x00400000&(data))>>22)
#define PFUNC_MISC2_get_sensor_rst_e2(data)                                          ((0x00400000&(data))>>22)
#define PFUNC_MISC2_sensor_rst_pud_en_shift                                          (21)
#define PFUNC_MISC2_sensor_rst_pud_en_mask                                           (0x00200000)
#define PFUNC_MISC2_sensor_rst_pud_en(data)                                          (0x00200000&((data)<<21))
#define PFUNC_MISC2_sensor_rst_pud_en_src(data)                                      ((0x00200000&(data))>>21)
#define PFUNC_MISC2_get_sensor_rst_pud_en(data)                                      ((0x00200000&(data))>>21)
#define PFUNC_MISC2_sensor_rst_pud_sel_shift                                         (20)
#define PFUNC_MISC2_sensor_rst_pud_sel_mask                                          (0x00100000)
#define PFUNC_MISC2_sensor_rst_pud_sel(data)                                         (0x00100000&((data)<<20))
#define PFUNC_MISC2_sensor_rst_pud_sel_src(data)                                     ((0x00100000&(data))>>20)
#define PFUNC_MISC2_get_sensor_rst_pud_sel(data)                                     ((0x00100000&(data))>>20)
#define PFUNC_MISC2_sensor_stb1_smt_shift                                            (19)
#define PFUNC_MISC2_sensor_stb1_smt_mask                                             (0x00080000)
#define PFUNC_MISC2_sensor_stb1_smt(data)                                            (0x00080000&((data)<<19))
#define PFUNC_MISC2_sensor_stb1_smt_src(data)                                        ((0x00080000&(data))>>19)
#define PFUNC_MISC2_get_sensor_stb1_smt(data)                                        ((0x00080000&(data))>>19)
#define PFUNC_MISC2_sensor_stb1_e2_shift                                             (18)
#define PFUNC_MISC2_sensor_stb1_e2_mask                                              (0x00040000)
#define PFUNC_MISC2_sensor_stb1_e2(data)                                             (0x00040000&((data)<<18))
#define PFUNC_MISC2_sensor_stb1_e2_src(data)                                         ((0x00040000&(data))>>18)
#define PFUNC_MISC2_get_sensor_stb1_e2(data)                                         ((0x00040000&(data))>>18)
#define PFUNC_MISC2_sensor_stb1_pud_en_shift                                         (17)
#define PFUNC_MISC2_sensor_stb1_pud_en_mask                                          (0x00020000)
#define PFUNC_MISC2_sensor_stb1_pud_en(data)                                         (0x00020000&((data)<<17))
#define PFUNC_MISC2_sensor_stb1_pud_en_src(data)                                     ((0x00020000&(data))>>17)
#define PFUNC_MISC2_get_sensor_stb1_pud_en(data)                                     ((0x00020000&(data))>>17)
#define PFUNC_MISC2_sensor_stb1_pud_sel_shift                                        (16)
#define PFUNC_MISC2_sensor_stb1_pud_sel_mask                                         (0x00010000)
#define PFUNC_MISC2_sensor_stb1_pud_sel(data)                                        (0x00010000&((data)<<16))
#define PFUNC_MISC2_sensor_stb1_pud_sel_src(data)                                    ((0x00010000&(data))>>16)
#define PFUNC_MISC2_get_sensor_stb1_pud_sel(data)                                    ((0x00010000&(data))>>16)
#define PFUNC_MISC2_sensor_stb0_smt_shift                                            (15)
#define PFUNC_MISC2_sensor_stb0_smt_mask                                             (0x00008000)
#define PFUNC_MISC2_sensor_stb0_smt(data)                                            (0x00008000&((data)<<15))
#define PFUNC_MISC2_sensor_stb0_smt_src(data)                                        ((0x00008000&(data))>>15)
#define PFUNC_MISC2_get_sensor_stb0_smt(data)                                        ((0x00008000&(data))>>15)
#define PFUNC_MISC2_sensor_stb0_e2_shift                                             (14)
#define PFUNC_MISC2_sensor_stb0_e2_mask                                              (0x00004000)
#define PFUNC_MISC2_sensor_stb0_e2(data)                                             (0x00004000&((data)<<14))
#define PFUNC_MISC2_sensor_stb0_e2_src(data)                                         ((0x00004000&(data))>>14)
#define PFUNC_MISC2_get_sensor_stb0_e2(data)                                         ((0x00004000&(data))>>14)
#define PFUNC_MISC2_sensor_stb0_pud_en_shift                                         (13)
#define PFUNC_MISC2_sensor_stb0_pud_en_mask                                          (0x00002000)
#define PFUNC_MISC2_sensor_stb0_pud_en(data)                                         (0x00002000&((data)<<13))
#define PFUNC_MISC2_sensor_stb0_pud_en_src(data)                                     ((0x00002000&(data))>>13)
#define PFUNC_MISC2_get_sensor_stb0_pud_en(data)                                     ((0x00002000&(data))>>13)
#define PFUNC_MISC2_sensor_stb0_pud_sel_shift                                        (12)
#define PFUNC_MISC2_sensor_stb0_pud_sel_mask                                         (0x00001000)
#define PFUNC_MISC2_sensor_stb0_pud_sel(data)                                        (0x00001000&((data)<<12))
#define PFUNC_MISC2_sensor_stb0_pud_sel_src(data)                                    ((0x00001000&(data))>>12)
#define PFUNC_MISC2_get_sensor_stb0_pud_sel(data)                                    ((0x00001000&(data))>>12)
#define PFUNC_MISC2_usb_id_smt_shift                                                 (11)
#define PFUNC_MISC2_usb_id_smt_mask                                                  (0x00000800)
#define PFUNC_MISC2_usb_id_smt(data)                                                 (0x00000800&((data)<<11))
#define PFUNC_MISC2_usb_id_smt_src(data)                                             ((0x00000800&(data))>>11)
#define PFUNC_MISC2_get_usb_id_smt(data)                                             ((0x00000800&(data))>>11)
#define PFUNC_MISC2_usb_id_e2_shift                                                  (10)
#define PFUNC_MISC2_usb_id_e2_mask                                                   (0x00000400)
#define PFUNC_MISC2_usb_id_e2(data)                                                  (0x00000400&((data)<<10))
#define PFUNC_MISC2_usb_id_e2_src(data)                                              ((0x00000400&(data))>>10)
#define PFUNC_MISC2_get_usb_id_e2(data)                                              ((0x00000400&(data))>>10)
#define PFUNC_MISC2_usb_id_pud_en_shift                                              (9)
#define PFUNC_MISC2_usb_id_pud_en_mask                                               (0x00000200)
#define PFUNC_MISC2_usb_id_pud_en(data)                                              (0x00000200&((data)<<9))
#define PFUNC_MISC2_usb_id_pud_en_src(data)                                          ((0x00000200&(data))>>9)
#define PFUNC_MISC2_get_usb_id_pud_en(data)                                          ((0x00000200&(data))>>9)
#define PFUNC_MISC2_usb_id_pud_sel_shift                                             (8)
#define PFUNC_MISC2_usb_id_pud_sel_mask                                              (0x00000100)
#define PFUNC_MISC2_usb_id_pud_sel(data)                                             (0x00000100&((data)<<8))
#define PFUNC_MISC2_usb_id_pud_sel_src(data)                                         ((0x00000100&(data))>>8)
#define PFUNC_MISC2_get_usb_id_pud_sel(data)                                         ((0x00000100&(data))>>8)
#define PFUNC_MISC2_hdmi_hpd_smt_shift                                               (7)
#define PFUNC_MISC2_hdmi_hpd_smt_mask                                                (0x00000080)
#define PFUNC_MISC2_hdmi_hpd_smt(data)                                               (0x00000080&((data)<<7))
#define PFUNC_MISC2_hdmi_hpd_smt_src(data)                                           ((0x00000080&(data))>>7)
#define PFUNC_MISC2_get_hdmi_hpd_smt(data)                                           ((0x00000080&(data))>>7)
#define PFUNC_MISC2_hdmi_hpd_e2_shift                                                (6)
#define PFUNC_MISC2_hdmi_hpd_e2_mask                                                 (0x00000040)
#define PFUNC_MISC2_hdmi_hpd_e2(data)                                                (0x00000040&((data)<<6))
#define PFUNC_MISC2_hdmi_hpd_e2_src(data)                                            ((0x00000040&(data))>>6)
#define PFUNC_MISC2_get_hdmi_hpd_e2(data)                                            ((0x00000040&(data))>>6)
#define PFUNC_MISC2_hdmi_hpd_pud_en_shift                                            (5)
#define PFUNC_MISC2_hdmi_hpd_pud_en_mask                                             (0x00000020)
#define PFUNC_MISC2_hdmi_hpd_pud_en(data)                                            (0x00000020&((data)<<5))
#define PFUNC_MISC2_hdmi_hpd_pud_en_src(data)                                        ((0x00000020&(data))>>5)
#define PFUNC_MISC2_get_hdmi_hpd_pud_en(data)                                        ((0x00000020&(data))>>5)
#define PFUNC_MISC2_hdmi_hpd_pud_sel_shift                                           (4)
#define PFUNC_MISC2_hdmi_hpd_pud_sel_mask                                            (0x00000010)
#define PFUNC_MISC2_hdmi_hpd_pud_sel(data)                                           (0x00000010&((data)<<4))
#define PFUNC_MISC2_hdmi_hpd_pud_sel_src(data)                                       ((0x00000010&(data))>>4)
#define PFUNC_MISC2_get_hdmi_hpd_pud_sel(data)                                       ((0x00000010&(data))>>4)
#define PFUNC_MISC2_gpio_8_smt_shift                                                 (3)
#define PFUNC_MISC2_gpio_8_smt_mask                                                  (0x00000008)
#define PFUNC_MISC2_gpio_8_smt(data)                                                 (0x00000008&((data)<<3))
#define PFUNC_MISC2_gpio_8_smt_src(data)                                             ((0x00000008&(data))>>3)
#define PFUNC_MISC2_get_gpio_8_smt(data)                                             ((0x00000008&(data))>>3)
#define PFUNC_MISC2_gpio_8_e2_shift                                                  (2)
#define PFUNC_MISC2_gpio_8_e2_mask                                                   (0x00000004)
#define PFUNC_MISC2_gpio_8_e2(data)                                                  (0x00000004&((data)<<2))
#define PFUNC_MISC2_gpio_8_e2_src(data)                                              ((0x00000004&(data))>>2)
#define PFUNC_MISC2_get_gpio_8_e2(data)                                              ((0x00000004&(data))>>2)
#define PFUNC_MISC2_gpio_8_pud_en_shift                                              (1)
#define PFUNC_MISC2_gpio_8_pud_en_mask                                               (0x00000002)
#define PFUNC_MISC2_gpio_8_pud_en(data)                                              (0x00000002&((data)<<1))
#define PFUNC_MISC2_gpio_8_pud_en_src(data)                                          ((0x00000002&(data))>>1)
#define PFUNC_MISC2_get_gpio_8_pud_en(data)                                          ((0x00000002&(data))>>1)
#define PFUNC_MISC2_gpio_8_pud_sel_shift                                             (0)
#define PFUNC_MISC2_gpio_8_pud_sel_mask                                              (0x00000001)
#define PFUNC_MISC2_gpio_8_pud_sel(data)                                             (0x00000001&((data)<<0))
#define PFUNC_MISC2_gpio_8_pud_sel_src(data)                                         ((0x00000001&(data))>>0)
#define PFUNC_MISC2_get_gpio_8_pud_sel(data)                                         ((0x00000001&(data))>>0)


#define PFUNC_MISC3                                                                  0x980003A0
#define PFUNC_MISC3_reg_addr                                                         "0x980003A0"
#define PFUNC_MISC3_reg                                                              0x980003A0
#define set_PFUNC_MISC3_reg(data)   (*((volatile unsigned int*) PFUNC_MISC3_reg)=data)
#define get_PFUNC_MISC3_reg   (*((volatile unsigned int*) PFUNC_MISC3_reg))
#define PFUNC_MISC3_inst_adr                                                         "0x00E8"
#define PFUNC_MISC3_inst                                                             0x00E8
#define PFUNC_MISC3_boption9_en_shift                                                (17)
#define PFUNC_MISC3_boption9_en_mask                                                 (0x00020000)
#define PFUNC_MISC3_boption9_en(data)                                                (0x00020000&((data)<<17))
#define PFUNC_MISC3_boption9_en_src(data)                                            ((0x00020000&(data))>>17)
#define PFUNC_MISC3_get_boption9_en(data)                                            ((0x00020000&(data))>>17)
#define PFUNC_MISC3_boption9_sel_shift                                               (16)
#define PFUNC_MISC3_boption9_sel_mask                                                (0x00010000)
#define PFUNC_MISC3_boption9_sel(data)                                               (0x00010000&((data)<<16))
#define PFUNC_MISC3_boption9_sel_src(data)                                           ((0x00010000&(data))>>16)
#define PFUNC_MISC3_get_boption9_sel(data)                                           ((0x00010000&(data))>>16)
#define PFUNC_MISC3_boption8_en_shift                                                (15)
#define PFUNC_MISC3_boption8_en_mask                                                 (0x00008000)
#define PFUNC_MISC3_boption8_en(data)                                                (0x00008000&((data)<<15))
#define PFUNC_MISC3_boption8_en_src(data)                                            ((0x00008000&(data))>>15)
#define PFUNC_MISC3_get_boption8_en(data)                                            ((0x00008000&(data))>>15)
#define PFUNC_MISC3_boption8_sel_shift                                               (14)
#define PFUNC_MISC3_boption8_sel_mask                                                (0x00004000)
#define PFUNC_MISC3_boption8_sel(data)                                               (0x00004000&((data)<<14))
#define PFUNC_MISC3_boption8_sel_src(data)                                           ((0x00004000&(data))>>14)
#define PFUNC_MISC3_get_boption8_sel(data)                                           ((0x00004000&(data))>>14)
#define PFUNC_MISC3_boption7_en_shift                                                (13)
#define PFUNC_MISC3_boption7_en_mask                                                 (0x00002000)
#define PFUNC_MISC3_boption7_en(data)                                                (0x00002000&((data)<<13))
#define PFUNC_MISC3_boption7_en_src(data)                                            ((0x00002000&(data))>>13)
#define PFUNC_MISC3_get_boption7_en(data)                                            ((0x00002000&(data))>>13)
#define PFUNC_MISC3_boption7_sel_shift                                               (12)
#define PFUNC_MISC3_boption7_sel_mask                                                (0x00001000)
#define PFUNC_MISC3_boption7_sel(data)                                               (0x00001000&((data)<<12))
#define PFUNC_MISC3_boption7_sel_src(data)                                           ((0x00001000&(data))>>12)
#define PFUNC_MISC3_get_boption7_sel(data)                                           ((0x00001000&(data))>>12)
#define PFUNC_MISC3_boption6_en_shift                                                (11)
#define PFUNC_MISC3_boption6_en_mask                                                 (0x00000800)
#define PFUNC_MISC3_boption6_en(data)                                                (0x00000800&((data)<<11))
#define PFUNC_MISC3_boption6_en_src(data)                                            ((0x00000800&(data))>>11)
#define PFUNC_MISC3_get_boption6_en(data)                                            ((0x00000800&(data))>>11)
#define PFUNC_MISC3_boption6_sel_shift                                               (10)
#define PFUNC_MISC3_boption6_sel_mask                                                (0x00000400)
#define PFUNC_MISC3_boption6_sel(data)                                               (0x00000400&((data)<<10))
#define PFUNC_MISC3_boption6_sel_src(data)                                           ((0x00000400&(data))>>10)
#define PFUNC_MISC3_get_boption6_sel(data)                                           ((0x00000400&(data))>>10)
#define PFUNC_MISC3_boption5_en_shift                                                (9)
#define PFUNC_MISC3_boption5_en_mask                                                 (0x00000200)
#define PFUNC_MISC3_boption5_en(data)                                                (0x00000200&((data)<<9))
#define PFUNC_MISC3_boption5_en_src(data)                                            ((0x00000200&(data))>>9)
#define PFUNC_MISC3_get_boption5_en(data)                                            ((0x00000200&(data))>>9)
#define PFUNC_MISC3_boption5_sel_shift                                               (8)
#define PFUNC_MISC3_boption5_sel_mask                                                (0x00000100)
#define PFUNC_MISC3_boption5_sel(data)                                               (0x00000100&((data)<<8))
#define PFUNC_MISC3_boption5_sel_src(data)                                           ((0x00000100&(data))>>8)
#define PFUNC_MISC3_get_boption5_sel(data)                                           ((0x00000100&(data))>>8)
#define PFUNC_MISC3_boption4_en_shift                                                (7)
#define PFUNC_MISC3_boption4_en_mask                                                 (0x00000080)
#define PFUNC_MISC3_boption4_en(data)                                                (0x00000080&((data)<<7))
#define PFUNC_MISC3_boption4_en_src(data)                                            ((0x00000080&(data))>>7)
#define PFUNC_MISC3_get_boption4_en(data)                                            ((0x00000080&(data))>>7)
#define PFUNC_MISC3_boption4_sel_shift                                               (6)
#define PFUNC_MISC3_boption4_sel_mask                                                (0x00000040)
#define PFUNC_MISC3_boption4_sel(data)                                               (0x00000040&((data)<<6))
#define PFUNC_MISC3_boption4_sel_src(data)                                           ((0x00000040&(data))>>6)
#define PFUNC_MISC3_get_boption4_sel(data)                                           ((0x00000040&(data))>>6)
#define PFUNC_MISC3_boption3_en_shift                                                (5)
#define PFUNC_MISC3_boption3_en_mask                                                 (0x00000020)
#define PFUNC_MISC3_boption3_en(data)                                                (0x00000020&((data)<<5))
#define PFUNC_MISC3_boption3_en_src(data)                                            ((0x00000020&(data))>>5)
#define PFUNC_MISC3_get_boption3_en(data)                                            ((0x00000020&(data))>>5)
#define PFUNC_MISC3_boption3_sel_shift                                               (4)
#define PFUNC_MISC3_boption3_sel_mask                                                (0x00000010)
#define PFUNC_MISC3_boption3_sel(data)                                               (0x00000010&((data)<<4))
#define PFUNC_MISC3_boption3_sel_src(data)                                           ((0x00000010&(data))>>4)
#define PFUNC_MISC3_get_boption3_sel(data)                                           ((0x00000010&(data))>>4)
#define PFUNC_MISC3_boption1_en_shift                                                (3)
#define PFUNC_MISC3_boption1_en_mask                                                 (0x00000008)
#define PFUNC_MISC3_boption1_en(data)                                                (0x00000008&((data)<<3))
#define PFUNC_MISC3_boption1_en_src(data)                                            ((0x00000008&(data))>>3)
#define PFUNC_MISC3_get_boption1_en(data)                                            ((0x00000008&(data))>>3)
#define PFUNC_MISC3_boption1_sel_shift                                               (2)
#define PFUNC_MISC3_boption1_sel_mask                                                (0x00000004)
#define PFUNC_MISC3_boption1_sel(data)                                               (0x00000004&((data)<<2))
#define PFUNC_MISC3_boption1_sel_src(data)                                           ((0x00000004&(data))>>2)
#define PFUNC_MISC3_get_boption1_sel(data)                                           ((0x00000004&(data))>>2)
#define PFUNC_MISC3_boption0_en_shift                                                (1)
#define PFUNC_MISC3_boption0_en_mask                                                 (0x00000002)
#define PFUNC_MISC3_boption0_en(data)                                                (0x00000002&((data)<<1))
#define PFUNC_MISC3_boption0_en_src(data)                                            ((0x00000002&(data))>>1)
#define PFUNC_MISC3_get_boption0_en(data)                                            ((0x00000002&(data))>>1)
#define PFUNC_MISC3_boption0_sel_shift                                               (0)
#define PFUNC_MISC3_boption0_sel_mask                                                (0x00000001)
#define PFUNC_MISC3_boption0_sel(data)                                               (0x00000001&((data)<<0))
#define PFUNC_MISC3_boption0_sel_src(data)                                           ((0x00000001&(data))>>0)
#define PFUNC_MISC3_get_boption0_sel(data)                                           ((0x00000001&(data))>>0)


#define CRT_DEBUG                                                                    0x98000400
#define CRT_DEBUG_reg_addr                                                           "0x98000400"
#define CRT_DEBUG_reg                                                                0x98000400
#define set_CRT_DEBUG_reg(data)   (*((volatile unsigned int*) CRT_DEBUG_reg)=data)
#define get_CRT_DEBUG_reg   (*((volatile unsigned int*) CRT_DEBUG_reg))
#define CRT_DEBUG_inst_adr                                                           "0x0000"
#define CRT_DEBUG_inst                                                               0x0000
#define CRT_DEBUG_crt_dbg_en_shift                                                   (8)
#define CRT_DEBUG_crt_dbg_en_mask                                                    (0x00000100)
#define CRT_DEBUG_crt_dbg_en(data)                                                   (0x00000100&((data)<<8))
#define CRT_DEBUG_crt_dbg_en_src(data)                                               ((0x00000100&(data))>>8)
#define CRT_DEBUG_get_crt_dbg_en(data)                                               ((0x00000100&(data))>>8)
#define CRT_DEBUG_crt_dbg_sel0_shift                                                 (4)
#define CRT_DEBUG_crt_dbg_sel0_mask                                                  (0x000000F0)
#define CRT_DEBUG_crt_dbg_sel0(data)                                                 (0x000000F0&((data)<<4))
#define CRT_DEBUG_crt_dbg_sel0_src(data)                                             ((0x000000F0&(data))>>4)
#define CRT_DEBUG_get_crt_dbg_sel0(data)                                             ((0x000000F0&(data))>>4)
#define CRT_DEBUG_crt_dbg_sel1_shift                                                 (0)
#define CRT_DEBUG_crt_dbg_sel1_mask                                                  (0x0000000F)
#define CRT_DEBUG_crt_dbg_sel1(data)                                                 (0x0000000F&((data)<<0))
#define CRT_DEBUG_crt_dbg_sel1_src(data)                                             ((0x0000000F&(data))>>0)
#define CRT_DEBUG_get_crt_dbg_sel1(data)                                             ((0x0000000F&(data))>>0)


#define crt_DEBUG                                                                        0x98000404
#define crt_DEBUG_reg_addr                                                               "0x98000404"
#define crt_DEBUG_reg                                                                    0x98000404
#define crt_set_DEBUG_reg(data)   (*((volatile unsigned int*) DEBUG_reg)=data)
#define crt_get_DEBUG_reg   (*((volatile unsigned int*) DEBUG_reg))
#define crt_DEBUG_inst_adr                                                               "0x0001"
#define crt_DEBUG_inst                                                                   0x0001
#define crt_DEBUG_dbg_en_shift                                                           (14)
#define crt_DEBUG_dbg_en_mask                                                            (0x00004000)
#define crt_DEBUG_dbg_en(data)                                                           (0x00004000&((data)<<14))
#define crt_DEBUG_dbg_en_src(data)                                                       ((0x00004000&(data))>>14)
#define crt_DEBUG_get_dbg_en(data)                                                       ((0x00004000&(data))>>14)
#define crt_DEBUG_dbg_loc_shift                                                          (12)
#define crt_DEBUG_dbg_loc_mask                                                           (0x00003000)
#define crt_DEBUG_dbg_loc(data)                                                          (0x00003000&((data)<<12))
#define crt_DEBUG_dbg_loc_src(data)                                                      ((0x00003000&(data))>>12)
#define crt_DEBUG_get_dbg_loc(data)                                                      ((0x00003000&(data))>>12)
#define crt_DEBUG_dbg_sel0_shift                                                         (6)
#define crt_DEBUG_dbg_sel0_mask                                                          (0x00000FC0)
#define crt_DEBUG_dbg_sel0(data)                                                         (0x00000FC0&((data)<<6))
#define crt_DEBUG_dbg_sel0_src(data)                                                     ((0x00000FC0&(data))>>6)
#define crt_DEBUG_get_dbg_sel0(data)                                                     ((0x00000FC0&(data))>>6)
#define crt_DEBUG_dbg_sel1_shift                                                         (0)
#define crt_DEBUG_dbg_sel1_mask                                                          (0x0000003F)
#define crt_DEBUG_dbg_sel1(data)                                                         (0x0000003F&((data)<<0))
#define crt_DEBUG_dbg_sel1_src(data)                                                     ((0x0000003F&(data))>>0)
#define crt_DEBUG_get_dbg_sel1(data)                                                     ((0x0000003F&(data))>>0)


#define CRT_DUMMY                                                                        0x98000450
#define CRT_DUMMY_reg_addr                                                               "0x98000450"
#define CRT_DUMMY_reg                                                                    0x98000450
#define CRT_set_DUMMY_reg(data)   (*((volatile unsigned int*) DUMMY_reg)=data)
#define CRT_get_DUMMY_reg   (*((volatile unsigned int*) DUMMY_reg))
#define CRT_DUMMY_inst_adr                                                               "0x0014"
#define CRT_DUMMY_inst                                                                   0x0014
#define CRT_DUMMY_dummy_reg_shift                                                        (0)
#define CRT_DUMMY_dummy_reg_mask                                                         (0xFFFFFFFF)
#define CRT_DUMMY_dummy_reg(data)                                                        (0xFFFFFFFF&((data)<<0))
#define CRT_DUMMY_dummy_reg_src(data)                                                    ((0xFFFFFFFF&(data))>>0)
#define CRT_DUMMY_get_dummy_reg(data)                                                    ((0xFFFFFFFF&(data))>>0)


#define PLL_VODMA1                                                                0x98000260
#define PLL_VODMA1_reg_addr                                                       "0x98000260"
#define PLL_VODMA1_reg                                                            0x98000260
#define set_PLL_VODMA1_reg(data)   (*((volatile unsigned int*) PLL_VODMA1_reg)=data)
#define get_PLL_VODMA1_reg   (*((volatile unsigned int*) PLL_VODMA1_reg))
//#define PLL_VODMA1_inst_adr                                                               "0x0014"
//#define PLL_VODMA1_inst                                                                   0x0014
#define PLL_VODMA1_REG_PLLVODMA_WDRST_shift                                                 (22)
#define PLL_VODMA1_REG_PLLVODMA_WDRST_mask                                                  (0x00400000)
#define PLL_VODMA1_REG_PLLVODMA_WDRST(data)                                                 (0x00400000&((data)<<22))
#define PLL_VODMA1_REG_PLLVODMA_WDRST_src(data)                                             ((0x00400000&(data))>>22)
#define PLL_VODMA1_get_REG_PLLVODMA_WDRST(data)                                             ((0x00400000&(data))>>22)
#define PLL_VODMA1_REG_PLLVODMA_WDSET_shift                                                 (21)
#define PLL_VODMA1_REG_PLLVODMA_WDSET_mask                                                  (0x00200000)
#define PLL_VODMA1_REG_PLLVODMA_WDSET(data)                                                 (0x00200000&((data)<<21))
#define PLL_VODMA1_REG_PLLVODMA_WDSET_src(data)                                             ((0x00200000&(data))>>21)
#define PLL_VODMA1_get_REG_PLLVODMA_WDSET(data)                                             ((0x00200000&(data))>>21)
#define PLL_VODMA1_REG_PLLVODMA_CS_shift                                                 (19)
#define PLL_VODMA1_REG_PLLVODMA_CS_mask                                                  (0x00180000)
#define PLL_VODMA1_REG_PLLVODMA_CS(data)                                                 (0x00180000&((data)<<19))
#define PLL_VODMA1_REG_PLLVODMA_CS_src(data)                                             ((0x00180000&(data))>>19)
#define PLL_VODMA1_get_REG_PLLVODMA_CS(data)                                             ((0x00180000&(data))>>19)
#define PLL_VODMA1_REG_PLLVODMA_O_shift                                                 (17)
#define PLL_VODMA1_REG_PLLVODMA_O_mask                                                  (0x00060000)
#define PLL_VODMA1_REG_PLLVODMA_O(data)                                                 (0x00060000&((data)<<17))
#define PLL_VODMA1_REG_PLLVODMA_O_src(data)                                             ((0x00060000&(data))>>17)
#define PLL_VODMA1_get_REG_PLLVODMA_O(data)                                             ((0x00060000&(data))>>17)
#define PLL_VODMA1_REG_PLLVODMA_RS_shift                                                 (14)
#define PLL_VODMA1_REG_PLLVODMA_RS_mask                                                  (0x0001C000)
#define PLL_VODMA1_REG_PLLVODMA_RS(data)                                                 (0x0001C000&((data)<<14))
#define PLL_VODMA1_REG_PLLVODMA_RS_src(data)                                             ((0x0001C000&(data))>>14)
#define PLL_VODMA1_get_REG_PLLVODMA_RS(data)                                             ((0x0001C000&(data))>>14)
#define PLL_VODMA1_REG_PLLVODMA_N_shift                                                 (12)
#define PLL_VODMA1_REG_PLLVODMA_N_mask                                                  (0x00003000)
#define PLL_VODMA1_REG_PLLVODMA_N(data)                                                 (0x00003000&((data)<<12))
#define PLL_VODMA1_REG_PLLVODMA_N_src(data)                                             ((0x00003000&(data))>>12)
#define PLL_VODMA1_get_REG_PLLVODMA_N(data)                                             ((0x00003000&(data))>>12)
#define PLL_VODMA1_REG_PLLVODMA_M_shift                                                 (4)
#define PLL_VODMA1_REG_PLLVODMA_M_mask                                                  (0x00000FF0)
#define PLL_VODMA1_REG_PLLVODMA_M(data)                                                 (0x00000FF0&((data)<<4))
#define PLL_VODMA1_REG_PLLVODMA_M_src(data)                                             ((0x00000FF0&(data))>>4)
#define PLL_VODMA1_get_REG_PLLVODMA_M(data)                                             ((0x00000FF0&(data))>>4)
#define PLL_VODMA1_REG_PLLVODMA_IP_shift                                                 (1)
#define PLL_VODMA1_REG_PLLVODMA_IP_mask                                                  (0x0000000E)
#define PLL_VODMA1_REG_PLLVODMA_IP(data)                                                 (0x0000000E&((data)<<1))
#define PLL_VODMA1_REG_PLLVODMA_IP_src(data)                                             ((0x0000000E&(data))>>1)
#define PLL_VODMA1_get_REG_PLLVODMA_IP(data)                                             ((0x0000000E&(data))>>1)
#define PLL_VODMA1_REG_PLLVODMA_TST_shift                                                 (0)
#define PLL_VODMA1_REG_PLLVODMA_TST_mask                                                  (0x00000001)
#define PLL_VODMA1_REG_PLLVODMA_TST(data)                                                 (0x00000001&((data)<<1))
#define PLL_VODMA1_REG_PLLVODMA_TST_src(data)                                             ((0x00000001&(data))>>1)
#define PLL_VODMA1_get_REG_PLLVODMA_TST(data)                                             ((0x00000001&(data))>>1)


#define PLL_SSC_DIG_SCPU1                                                                0x98000504
#define PLL_SSC_DIG_SCPU1_reg_addr                                                       "0x98000504"
#define PLL_SSC_DIG_SCPU1_reg                                                            0x98000504
#define set_PLL_SSC_DIG_SCPU1_reg(data)   (*((volatile unsigned int*) PLL_SSC_DIG_SCPU1_reg)=data)
#define get_PLL_SSC_DIG_SCPU1_reg   (*((volatile unsigned int*) PLL_SSC_DIG_SCPU1_reg))
//#define PLL_SSC_DIG_SCPU1_inst_adr                                                               "0x0014"
//#define PLL_SSC_DIG_SCPU1_inst                                                                   0x0014
#define PLL_SSC_DIG_SCPU1_NCODE_T_SCPU_shift                                                        (11)
#define PLL_SSC_DIG_SCPU1_NCODE_T_SCPU_mask                                                         (0x0007F800)
#define PLL_SSC_DIG_SCPU1_NCODE_T_SCPU(data)                                                        (0x0007F800&((data)<<11))
#define PLL_SSC_DIG_SCPU1_NCODE_T_SCPU_src(data)                                                    ((0x0007F800&(data))>>11)
#define PLL_SSC_DIG_SCPU1_get_NCODE_T_SCPU(data)                                                    ((0x0007F800&(data))>>11)
#define PLL_SSC_DIG_SCPU1_FCODE_T_SCPU_shift                                                        (0)
#define PLL_SSC_DIG_SCPU1_FCODE_T_SCPU_mask                                                         (0x000007FF)
#define PLL_SSC_DIG_SCPU1_FCODE_T_SCPU(data)                                                        (0x000007FF&((data)<<0))
#define PLL_SSC_DIG_SCPU1_FCODE_T_SCPU_src(data)                                                    ((0x000007FF&(data))>>0)
#define PLL_SSC_DIG_SCPU1_get_FCODE_T_SCPU(data)                                                    ((0x000007FF&(data))>>0)


#define PLL_SSC_DIG_BUS1                                                                           0x98000524
#define PLL_SSC_DIG_BUS1_reg_addr                                                                  "0x98000524"
#define PLL_SSC_DIG_BUS1_reg                                                                       0x98000524
#define set_PLL_SSC_DIG_BUS1_reg(data)   (*((volatile unsigned int*) PLL_SSC_DIG_BUS1_reg)=data)
#define get_PLL_SSC_DIG_BUS1_reg   (*((volatile unsigned int*) PLL_SSC_DIG_BUS1_reg))
//#define PLL_SSC_DIG_BUS1_inst_adr                                                                "0x0014"
//#define PLL_SSC_DIG_BUS1_inst                                                                    0x0014
#define PLL_SSC_DIG_BUS1_NCODE_T_BUS_shift                                                        (11)
#define PLL_SSC_DIG_BUS1_NCODE_T_BUS_mask                                                         (0x0007F800)
#define PLL_SSC_DIG_BUS1_NCODE_T_BUS(data)                                                        (0x0007F800&((data)<<11))
#define PLL_SSC_DIG_BUS1_NCODE_T_BUS_src(data)                                                    ((0x0007F800&(data))>>11)
#define PLL_SSC_DIG_BUS1_get_NCODE_T_BUS(data)                                                    ((0x0007F800&(data))>>11)
#define PLL_SSC_DIG_BUS1_FCODE_T_BUS_shift                                                        (0)
#define PLL_SSC_DIG_BUS1_FCODE_T_BUS_mask                                                         (0x000007FF)
#define PLL_SSC_DIG_BUS1_FCODE_T_BUS(data)                                                        (0x000007FF&((data)<<0))
#define PLL_SSC_DIG_BUS1_FCODE_T_BUS_src(data)                                                    ((0x000007FF&(data))>>0)
#define PLL_SSC_DIG_BUS1_get_FCODE_T_BUS(data)                                                    ((0x000007FF&(data))>>0)


#define PLL_SSC_DIG_BUSH1                                                                           0x98000544
#define PLL_SSC_DIG_BUSH1_reg_addr                                                                  "0x98000544"
#define PLL_SSC_DIG_BUSH1_reg                                                                       0x98000544
#define set_PLL_SSC_DIG_BUSH1_reg(data)   (*((volatile unsigned int*) PLL_SSC_DIG_BUSH1_reg)=data)
#define get_PLL_SSC_DIG_BUSH1_reg   (*((volatile unsigned int*) PLL_SSC_DIG_BUSH1_reg))
//#define PLL_SSC_DIG_BUSH1_inst_adr                                                                "0x0014"
//#define PLL_SSC_DIG_BUSH1_inst                                                                    0x0014
#define PLL_SSC_DIG_BUSH1_NCODE_T_BUS_H_shift                                                        (11)
#define PLL_SSC_DIG_BUSH1_NCODE_T_BUS_H_mask                                                         (0x0007F800)
#define PLL_SSC_DIG_BUSH1_NCODE_T_BUS_H(data)                                                        (0x0007F800&((data)<<11))
#define PLL_SSC_DIG_BUSH1_NCODE_T_BUS_H_src(data)                                                    ((0x0007F800&(data))>>11)
#define PLL_SSC_DIG_BUSH1_get_NCODE_T_BUS_H(data)                                                    ((0x0007F800&(data))>>11)
#define PLL_SSC_DIG_BUSH1_FCODE_T_BUS_H_shift                                                        (0)
#define PLL_SSC_DIG_BUSH1_FCODE_T_BUS_H_mask                                                         (0x000007FF)
#define PLL_SSC_DIG_BUSH1_FCODE_T_BUS_H(data)                                                        (0x000007FF&((data)<<0))
#define PLL_SSC_DIG_BUSH1_FCODE_T_BUS_H_src(data)                                                    ((0x000007FF&(data))>>0)
#define PLL_SSC_DIG_BUSH1_get_FCODE_T_BUS_H(data)                                                    ((0x000007FF&(data))>>0)


#define PLL_SSC_DIG_DDSA1                                                                           0x98000564
#define PLL_SSC_DIG_DDSA1_reg_addr                                                                  "0x98000564"
#define PLL_SSC_DIG_DDSA1_reg                                                                       0x98000564
#define set_PLL_SSC_DIG_DDSA1_reg(data)   (*((volatile unsigned int*) PLL_SSC_DIG_DDSA1_reg)=data)
#define get_PLL_SSC_DIG_DDSA1_reg   (*((volatile unsigned int*) PLL_SSC_DIG_DDSA1_reg))
//#define PLL_SSC_DIG_DDSA1_inst_adr                                                                "0x0014"
//#define PLL_SSC_DIG_DDSA1_inst                                                                    0x0014
#define PLL_SSC_DIG_DDSA1_REG_PLLDDSA_ICO_PDIV2_shift                                               (19)
#define PLL_SSC_DIG_DDSA1_REG_PLLDDSA_ICO_PDIV2_mask                                                (0x00380000)
#define PLL_SSC_DIG_DDSA1_REG_PLLDDSA_ICO_PDIV2(data)                                               (0x00380000&((data)<<19))
#define PLL_SSC_DIG_DDSA1_REG_PLLDDSA_ICO_PDIV2_src(data)                                           ((0x00380000&(data))>>19)
#define PLL_SSC_DIG_DDSA1_get_REG_PLLDDSA_ICO_PDIV2(data)                                           ((0x00380000&(data))>>19)
#define PLL_SSC_DIG_DDSA1_NCODE_T_DDSA_shift                                                        (11)
#define PLL_SSC_DIG_DDSA1_NCODE_T_DDSA_mask                                                         (0x0007F800)
#define PLL_SSC_DIG_DDSA1_NCODE_T_DDSA(data)                                                        (0x0007F800&((data)<<11))
#define PLL_SSC_DIG_DDSA1_NCODE_T_DDSA_src(data)                                                    ((0x0007F800&(data))>>11)
#define PLL_SSC_DIG_DDSA1_get_NCODE_T_DDSA(data)                                                    ((0x0007F800&(data))>>11)
#define PLL_SSC_DIG_DDSA1_FCODE_T_DDSA_shift                                                        (0)
#define PLL_SSC_DIG_DDSA1_FCODE_T_DDSA_mask                                                         (0x000007FF)
#define PLL_SSC_DIG_DDSA1_FCODE_T_DDSA(data)                                                        (0x000007FF&((data)<<0))
#define PLL_SSC_DIG_DDSA1_FCODE_T_DDSA_src(data)                                                    ((0x000007FF&(data))>>0)
#define PLL_SSC_DIG_DDSA1_get_FCODE_T_DDSA(data)                                                    ((0x000007FF&(data))>>0)


#define PLL_SSC_DIG_DDSB1                                                                           0x98000584
#define PLL_SSC_DIG_DDSB1_reg_addr                                                                  "0x98000584"
#define PLL_SSC_DIG_DDSB1_reg                                                                       0x98000584
#define set_PLL_SSC_DIG_DDSB1_reg(data)   (*((volatile unsigned int*) PLL_SSC_DIG_DDSB1_reg)=data)
#define get_PLL_SSC_DIG_DDSB1_reg   (*((volatile unsigned int*) PLL_SSC_DIG_DDSB1_reg))
//#define PLL_SSC_DIG_DDSB1_inst_adr                                                                "0x0014"
//#define PLL_SSC_DIG_DDSB1_inst                                                                    0x0014
#define PLL_SSC_DIG_DDSB1_REG_PLLDDSB_ICO_PDIV2_shift                                               (19)
#define PLL_SSC_DIG_DDSB1_REG_PLLDDSB_ICO_PDIV2_mask                                                (0x00380000)
#define PLL_SSC_DIG_DDSB1_REG_PLLDDSB_ICO_PDIV2(data)                                               (0x00380000&((data)<<19))
#define PLL_SSC_DIG_DDSB1_REG_PLLDDSB_ICO_PDIV2_src(data)                                           ((0x00380000&(data))>>19)
#define PLL_SSC_DIG_DDSB1_get_REG_PLLDDSB_ICO_PDIV2(data)                                           ((0x00380000&(data))>>19)
#define PLL_SSC_DIG_DDSB1_NCODE_T_DDSB_shift                                                        (11)
#define PLL_SSC_DIG_DDSB1_NCODE_T_DDSB_mask                                                         (0x0007F800)
#define PLL_SSC_DIG_DDSB1_NCODE_T_DDSB(data)                                                        (0x0007F800&((data)<<11))
#define PLL_SSC_DIG_DDSB1_NCODE_T_DDSB_src(data)                                                    ((0x0007F800&(data))>>11)
#define PLL_SSC_DIG_DDSB1_get_NCODE_T_DDSB(data)                                                    ((0x0007F800&(data))>>11)
#define PLL_SSC_DIG_DDSB1_FCODE_T_DDSB_shift                                                        (0)
#define PLL_SSC_DIG_DDSB1_FCODE_T_DDSB_mask                                                         (0x000007FF)
#define PLL_SSC_DIG_DDSB1_FCODE_T_DDSB(data)                                                        (0x000007FF&((data)<<0))
#define PLL_SSC_DIG_DDSB1_FCODE_T_DDSB_src(data)                                                    ((0x000007FF&(data))>>0)
#define PLL_SSC_DIG_DDSB1_get_FCODE_T_DDSB(data)                                                    ((0x000007FF&(data))>>0)


#define PLL_SSC_DIG_GPU1                                                                0x980005A4
#define PLL_SSC_DIG_GPU1_reg_addr                                                       "0x980005A4"
#define PLL_SSC_DIG_GPU1_reg                                                            0x980005A4
#define set_PLL_SSC_DIG_GPU1_reg(data)   (*((volatile unsigned int*) PLL_SSC_DIG_GPU1_reg)=data)
#define get_PLL_SSC_DIG_GPU1_reg   (*((volatile unsigned int*) PLL_SSC_DIG_GPU1_reg))
//#define PLL_SSC_DIG_GPU1_inst_adr                                                               "0x0014"
//#define PLL_SSC_DIG_GPU1_inst                                                                   0x0014
#define PLL_SSC_DIG_GPU1_NCODE_T_GPU_shift                                                        (11)
#define PLL_SSC_DIG_GPU1_NCODE_T_GPU_mask                                                         (0x0007F800)
#define PLL_SSC_DIG_GPU1_NCODE_T_GPU(data)                                                        (0x0007F800&((data)<<11))
#define PLL_SSC_DIG_GPU1_NCODE_T_GPU_src(data)                                                    ((0x0007F800&(data))>>11)
#define PLL_SSC_DIG_GPU1_get_NCODE_T_GPU(data)                                                    ((0x0007F800&(data))>>11)
#define PLL_SSC_DIG_GPU1_FCODE_T_GPU_shift                                                        (0)
#define PLL_SSC_DIG_GPU1_FCODE_T_GPU_mask                                                         (0x000007FF)
#define PLL_SSC_DIG_GPU1_FCODE_T_GPU(data)                                                        (0x000007FF&((data)<<0))
#define PLL_SSC_DIG_GPU1_FCODE_T_GPU_src(data)                                                    ((0x000007FF&(data))>>0)
#define PLL_SSC_DIG_GPU1_get_FCODE_T_GPU(data)                                                    ((0x000007FF&(data))>>0)


#define PLL_SSC_DIG_ACPU1                                                                0x980005C4
#define PLL_SSC_DIG_ACPU1_reg_addr                                                       "0x980005C4"
#define PLL_SSC_DIG_ACPU1_reg                                                            0x980005C4
#define set_PLL_SSC_DIG_ACPU1_reg(data)   (*((volatile unsigned int*) PLL_SSC_DIG_ACPU1_reg)=data)
#define get_PLL_SSC_DIG_ACPU1_reg   (*((volatile unsigned int*) PLL_SSC_DIG_ACPU1_reg))
//#define PLL_SSC_DIG_ACPU1_inst_adr                                                               "0x0014"
//#define PLL_SSC_DIG_ACPU1_inst                                                                   0x0014
#define PLL_SSC_DIG_ACPU1_NCODE_T_ACPU_shift                                                        (11)
#define PLL_SSC_DIG_ACPU1_NCODE_T_ACPU_mask                                                         (0x0007F800)
#define PLL_SSC_DIG_ACPU1_NCODE_T_ACPU(data)                                                        (0x0007F800&((data)<<11))
#define PLL_SSC_DIG_ACPU1_NCODE_T_ACPU_src(data)                                                    ((0x0007F800&(data))>>11)
#define PLL_SSC_DIG_ACPU1_get_NCODE_T_ACPU(data)                                                    ((0x0007F800&(data))>>11)
#define PLL_SSC_DIG_ACPU1_FCODE_T_ACPU_shift                                                        (0)
#define PLL_SSC_DIG_ACPU1_FCODE_T_ACPU_mask                                                         (0x000007FF)
#define PLL_SSC_DIG_ACPU1_FCODE_T_ACPU(data)                                                        (0x000007FF&((data)<<0))
#define PLL_SSC_DIG_ACPU1_FCODE_T_ACPU_src(data)                                                    ((0x000007FF&(data))>>0)
#define PLL_SSC_DIG_ACPU1_get_FCODE_T_ACPU(data)                                                    ((0x000007FF&(data))>>0)
#endif
