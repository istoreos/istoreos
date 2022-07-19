/**************************************************************
// Spec Version                  : 0.9
// Parser Version                : DVR_Parser_6.11(120105)
// CModelGen Version             : 5.1 2012.01.05
// Naming Rule                   :  Module_Register_Name
// Naming Rule                   : Module_Register_Name_reg
// Parse Option                  : Only Parse _op1
// Parse Address Region          : All Address Region 
// Decode bit number             : 12 bits
// Firmware Header Generate Date : 2015/6/10 11:50:54
***************************************************************/


#ifndef _EMMC_REG_H_INCLUDED_
#define _EMMC_REG_H_INCLUDED_
#ifdef  _EMMC_USE_STRUCT
typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     base:30;
}EMMC_DESC_CTL0;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     limit:30;
}EMMC_DESC_CTL1;

typedef struct 
{
unsigned int     desc_int_clr:1;
unsigned int     desc_go:1;
unsigned int     wptr:30;
}EMMC_DESC_CTL2;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     rptr:30;
}EMMC_DESC_CTL3;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     desc_sts:16;
}EMMC_DESC_STS;

typedef struct 
{
unsigned int     desc_timeout_bypass:1;
unsigned int     desc_timeout_thd:31;
}EMMC_DESC_THD;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     mcu_pp_sram_lp_ena:1;
unsigned int     sys_clk_gate_ena:1;
unsigned int     cp_clk_gate_ena:1;
unsigned int     dma_sram_lp_ena:1;
unsigned int     dma_sram_rdy_num:4;
}EMMC_SYS_LOW_PWR;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     cp_de_en:1;
unsigned int     cp_length:16;
unsigned int     cp_first:1;
unsigned int     cp_enable:1;
unsigned int     cp_sram_sel:1;
unsigned int     reserved_1:6;
}EMMC_CP;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     Dbus_endian_sel:1;
unsigned int     l4_gated_disable:1;
}EMMC_OTHER1;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     ip_int_mask:1;
unsigned int     desc_int_mask:1;
unsigned int     Dma_int_mask:1;
unsigned int     dma_done_int:1;
unsigned int     write_data:1;
}EMMC_ISR;

typedef struct 
{
unsigned int     dmy:32;
}EMMC_ISREN;

typedef struct 
{
unsigned int     dmy:32;
}EMMC_DUMMY_SYS;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     EMMC_ahb_m_big_endian:1;
unsigned int     EMMC_ahb_s_big_endian:1;
unsigned int     reserved_1:1;
}EMMC_AHB;

typedef struct 
{
unsigned int     reserved_0:18;
unsigned int     write_enable3:1;
unsigned int     sel1:5;
unsigned int     write_enable2:1;
unsigned int     sel0:5;
unsigned int     write_enable1:1;
unsigned int     enable:1;
}EMMC_DBG;

typedef struct 
{
unsigned int     reserved_0:7;
unsigned int     bist_cr_desc_rme_0:1;
unsigned int     bist_cr_desc_rm_0:4;
unsigned int     reserved_1:3;
unsigned int     bist_cr_ppb_rme_1:1;
unsigned int     bist_cr_ppb_rm_1:4;
unsigned int     reserved_2:3;
unsigned int     bist_cr_ppb_rme_0:1;
unsigned int     bist_cr_ppb_rm_0:4;
unsigned int     bist_drf_test_resume:1;
unsigned int     bist_drf_mode:1;
unsigned int     bist_en:1;
unsigned int     bist_ls:1;
}EMMC_PP_BIST_CTL;

typedef struct 
{
unsigned int     reserved_0:15;
unsigned int     bist_cr_ip_rme_1:1;
unsigned int     bist_cr_ip_rm_1:4;
unsigned int     reserved_1:3;
unsigned int     bist_cr_ip_rme_0:1;
unsigned int     bist_cr_ip_rm_0:4;
unsigned int     bist_drf_test_resume:1;
unsigned int     bist_drf_mode:1;
unsigned int     bist_en:1;
unsigned int     bist_ls:1;
}EMMC_IP_BIST_CTL;

typedef struct 
{
unsigned int     reserved_0:21;
unsigned int     bist_drf_start_pause:1;
unsigned int     reserved_1:1;
unsigned int     bist_drf_fail_2:1;
unsigned int     bist_drf_fail_1:1;
unsigned int     bist_drf_fail_0:1;
unsigned int     bist_drf_done:1;
unsigned int     reserved_2:1;
unsigned int     bist_2_fail:1;
unsigned int     bist_1_fail:1;
unsigned int     bist_0_fail:1;
unsigned int     bist_done:1;
}EMMC_PP_BIST_STS;

typedef struct 
{
unsigned int     reserved_0:21;
unsigned int     bist_drf_start_pause:1;
unsigned int     reserved_1:1;
unsigned int     reserved_2:1;
unsigned int     bist_drf_fail_1:1;
unsigned int     bist_drf_fail_0:1;
unsigned int     bist_drf_done:1;
unsigned int     reserved_3:1;
unsigned int     reserved_4:1;
unsigned int     bist_1_fail:1;
unsigned int     bist_0_fail:1;
unsigned int     bist_done:1;
}EMMC_IP_BIST_STS;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     asic_crc_dbgo_sel:8;
unsigned int     reserved_1:1;
unsigned int     crc_dbgo_sel:4;
unsigned int     ip_ea_flash:1;
unsigned int     crc_clk_disable_trig:1;
unsigned int     mcu_time_1_us:1;
}EMMC_IP_CTL;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     tune3318:1;
}EMMC_PAD_CTL;

typedef struct 
{
unsigned int     reserved_0:13;
unsigned int     sd30_sample_change:1;
unsigned int     sd30_push_change:1;
unsigned int     crc_clk_change:1;
unsigned int     reserved_1:2;
unsigned int     sd30_sample_clk_src:2;
unsigned int     reserved_2:2;
unsigned int     sd30_push_clk_src:2;
unsigned int     reserved_3:2;
unsigned int     crc_clk_src:2;
unsigned int     reserved_4:1;
unsigned int     clk_div:3;
}EMMC_CKGEN_CTL;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     buf_full:1;
unsigned int     buf_sw:1;
unsigned int     cpu_mode:1;
}EMMC_CPU_ACC_CTRL;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     EMMC_RST_n:1;
}EMMC_CARD_SIG;

typedef struct 
{
unsigned int     EMMC_card_drive:8;
unsigned int     EMMC_dat_n_drive:4;
unsigned int     EMMC_dat_p_drive:4;
unsigned int     EMMC_cmd_n_drive:4;
unsigned int     EMMC_cmd_p_drive:4;
unsigned int     EMMC_clk_n_drive:4;
unsigned int     EMMC_clk_p_drive:4;
}EMMC_CARD_DRV;

typedef struct 
{
unsigned int     reserved_0:23;
unsigned int     EMMC_sd_pupdc:3;
unsigned int     EMMC_card_output_en:6;
}EMMC_CARD_DRV;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     fw_set:1;
unsigned int     fw_dlyn:7;
}EMMC_DQS_CTRL1;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     auto_cal:1;
unsigned int     reserved_1:1;
unsigned int     pos_trig_sel:3;
unsigned int     pre_trig_sel:3;
}EMMC_DQS_CTRL2;

typedef struct 
{
unsigned int     Desc0:32;
}EMMC_IP_DESC0;

typedef struct 
{
unsigned int     Desc1:32;
}EMMC_IP_DESC1;

typedef struct 
{
unsigned int     Desc2:32;
}EMMC_IP_DESC2;

typedef struct 
{
unsigned int     Desc3:32;
}EMMC_IP_DESC3;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     main2_dbg_en:1;
unsigned int     main2_dbg_sel:2;
}EMMC_MAIN2_DBG;

typedef struct 
{
unsigned int     reserved_0:3;
unsigned int     reg_a:29;
}EMMC_TM_SENSOR_CTRL0;

typedef struct 
{
unsigned int     reserved_0:3;
unsigned int     reg_chopen:1;
unsigned int     reg_cal_en:1;
unsigned int     reg_biasdem_sel:1;
unsigned int     reg_biaschop:1;
unsigned int     reg_adccksel:3;
unsigned int     reg_b:22;
}EMMC_TM_SENSOR_CTRL1;

typedef struct 
{
unsigned int     reserved_0:7;
unsigned int     reg_vbe_biassel:2;
unsigned int     reg_sdm_test_en:1;
unsigned int     reg_sdm_test:1;
unsigned int     reg_rstb:1;
unsigned int     reg_resol:2;
unsigned int     reg_ppow:1;
unsigned int     reg_osccursel:2;
unsigned int     reg_order3:1;
unsigned int     reg_opcursel:2;
unsigned int     reg_hold_en:1;
unsigned int     reg_hold_dly:2;
unsigned int     reg_filteredgesel:1;
unsigned int     reg_dsr:3;
unsigned int     reg_cksourcesel:1;
unsigned int     reg_chopfreqsel:4;
}EMMC_TM_SENSOR_CTRL2;

typedef struct 
{
unsigned int     reserved_0:10;
unsigned int     reg_offset:22;
}EMMC_TM_SENSOR_CTRL3;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     reg_r:24;
}EMMC_TM_SENSOR_CTRL4;

typedef struct 
{
unsigned int     reserved_0:9;
unsigned int     reg_s:23;
}EMMC_TM_SENSOR_CTRL5;

typedef struct 
{
unsigned int     reserved_0:13;
unsigned int     ct_out:19;
}EMMC_TM_SENSOR_STATUS1;

typedef struct 
{
unsigned int     reserved_0:10;
unsigned int     u_out:22;
}EMMC_TM_SENSOR_STATUS2;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     swc_sel:1;
}EMMC_SWC_SEL;

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
unsigned int     nf_dqs:2;
}EMMC_MUXPAD0;

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
unsigned int     reserved_0:2;
unsigned int     emmc_dd_sb:2;
unsigned int     sdio_data_3:2;
unsigned int     sdio_data_2:2;
unsigned int     sdio_data_1:2;
unsigned int     sdio_data_0:2;
unsigned int     sdio_clk:2;
unsigned int     sdio_cmd:2;
}EMMC_MUXPAD1;

typedef struct 
{
unsigned int     nf_cle_smt:1;
unsigned int     reserved_0:1;
unsigned int     nf_cle_pud_en:1;
unsigned int     nf_cle_pud_sel:1;
unsigned int     nf_wr_n_smt:1;
unsigned int     reserved_1:1;
unsigned int     nf_wr_n_pud_en:1;
unsigned int     nf_wr_n_pud_sel:1;
unsigned int     nf_rd_n_smt:1;
unsigned int     reserved_2:1;
unsigned int     nf_rd_n_pud_en:1;
unsigned int     nf_rd_n_pud_sel:1;
unsigned int     nf_rdy_smt:1;
unsigned int     reserved_3:1;
unsigned int     nf_rdy_pud_en:1;
unsigned int     nf_rdy_pud_sel:1;
unsigned int     nf_ce_n_1_smt:1;
unsigned int     reserved_4:1;
unsigned int     nf_ce_n_1_pud_en:1;
unsigned int     nf_ce_n_1_pud_sel:1;
unsigned int     nf_ce_n_0_smt:1;
unsigned int     reserved_5:1;
unsigned int     nf_ce_n_0_pud_en:1;
unsigned int     nf_ce_n_0_pud_sel:1;
unsigned int     nf_ale_smt:1;
unsigned int     reserved_6:1;
unsigned int     nf_ale_pud_en:1;
unsigned int     nf_ale_pud_sel:1;
unsigned int     nf_dqs_smt:1;
unsigned int     reserved_7:1;
unsigned int     nf_dqs_pud_en:1;
unsigned int     nf_dqs_pud_sel:1;
}EMMC_PFUNC_NF0;

typedef struct 
{
unsigned int     nf_dd_7_smt:1;
unsigned int     reserved_0:1;
unsigned int     nf_dd_7_pud_en:1;
unsigned int     nf_dd_7_pud_sel:1;
unsigned int     nf_dd_6_smt:1;
unsigned int     reserved_1:1;
unsigned int     nf_dd_6_pud_en:1;
unsigned int     nf_dd_6_pud_sel:1;
unsigned int     nf_dd_5_smt:1;
unsigned int     reserved_2:1;
unsigned int     nf_dd_5_pud_en:1;
unsigned int     nf_dd_5_pud_sel:1;
unsigned int     nf_dd_4_smt:1;
unsigned int     reserved_3:1;
unsigned int     nf_dd_4_pud_en:1;
unsigned int     nf_dd_4_pud_sel:1;
unsigned int     nf_dd_3_smt:1;
unsigned int     reserved_4:1;
unsigned int     nf_dd_3_pud_en:1;
unsigned int     nf_dd_3_pud_sel:1;
unsigned int     nf_dd_2_smt:1;
unsigned int     reserved_5:1;
unsigned int     nf_dd_2_pud_en:1;
unsigned int     nf_dd_2_pud_sel:1;
unsigned int     nf_dd_1_smt:1;
unsigned int     reserved_6:1;
unsigned int     nf_dd_1_pud_en:1;
unsigned int     nf_dd_1_pud_sel:1;
unsigned int     nf_dd_0_smt:1;
unsigned int     reserved_7:1;
unsigned int     nf_dd_0_pud_en:1;
unsigned int     nf_dd_0_pud_sel:1;
}EMMC_PFUNC_NF1;

typedef struct 
{
unsigned int     mmc_data_3_smt:1;
unsigned int     reserved_0:1;
unsigned int     mmc_data_3_pud_en:1;
unsigned int     mmc_data_3_pud_sel:1;
unsigned int     mmc_data_2_smt:1;
unsigned int     reserved_1:1;
unsigned int     mmc_data_2_pud_en:1;
unsigned int     mmc_data_2_pud_sel:1;
unsigned int     mmc_data_1_smt:1;
unsigned int     reserved_2:1;
unsigned int     mmc_data_1_pud_en:1;
unsigned int     mmc_data_1_pud_sel:1;
unsigned int     mmc_data_0_smt:1;
unsigned int     reserved_3:1;
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
unsigned int     reserved_4:1;
unsigned int     mmc_clk_pud_en:1;
unsigned int     mmc_clk_pud_sel:1;
unsigned int     mmc_cmd_smt:1;
unsigned int     reserved_5:1;
unsigned int     mmc_cmd_pud_en:1;
unsigned int     mmc_cmd_pud_sel:1;
}EMMC_PFUNC_CR;

typedef struct 
{
unsigned int     sdio_data_3_smt:1;
unsigned int     reserved_0:1;
unsigned int     sdio_data_3_pud_en:1;
unsigned int     sdio_data_3_pud_sel:1;
unsigned int     sdio_data_2_smt:1;
unsigned int     reserved_1:1;
unsigned int     sdio_data_2_pud_en:1;
unsigned int     sdio_data_2_pud_sel:1;
unsigned int     sdio_data_1_smt:1;
unsigned int     reserved_2:1;
unsigned int     sdio_data_1_pud_en:1;
unsigned int     sdio_data_1_pud_sel:1;
unsigned int     sdio_data_0_smt:1;
unsigned int     reserved_3:1;
unsigned int     sdio_data_0_pud_en:1;
unsigned int     sdio_data_0_pud_sel:1;
unsigned int     reserved_4:8;
unsigned int     sdio_clk_smt:1;
unsigned int     reserved_5:1;
unsigned int     sdio_clk_pud_en:1;
unsigned int     sdio_clk_pud_sel:1;
unsigned int     sdio_cmd_smt:1;
unsigned int     reserved_6:1;
unsigned int     sdio_cmd_pud_en:1;
unsigned int     sdio_cmd_pud_sel:1;
}EMMC_PFUNC_SDIO;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     prob_3_smt:1;
unsigned int     prob_3_e2:1;
unsigned int     prob_3_pud_en:1;
unsigned int     prob_3_pud_sel:1;
unsigned int     prob_2_smt:1;
unsigned int     prob_2_e2:1;
unsigned int     prob_2_pud_en:1;
unsigned int     prob_2_pud_sel:1;
unsigned int     prob_1_smt:1;
unsigned int     prob_1_e2:1;
unsigned int     prob_1_pud_en:1;
unsigned int     prob_1_pud_sel:1;
unsigned int     prob_0_smt:1;
unsigned int     prob_0_e2:1;
unsigned int     prob_0_pud_en:1;
unsigned int     prob_0_pud_sel:1;
unsigned int     pcie_clkreq_1_smt:1;
unsigned int     pcie_clkreq_1_e2:1;
unsigned int     pcie_clkreq_1_pud_en:1;
unsigned int     pcie_clkreq_1_pud_sel:1;
unsigned int     pcie_clkreq_0_smt:1;
unsigned int     pcie_clkreq_0_e2:1;
unsigned int     pcie_clkreq_0_pud_en:1;
unsigned int     pcie_clkreq_0_pud_sel:1;
unsigned int     emmc_dd_sb_smt:1;
unsigned int     reserved_1:1;
unsigned int     emmc_dd_sb_pud_en:1;
unsigned int     emmc_dd_sb_pud_sel:1;
}EMMC_PFUNC_NF2;

typedef struct 
{
unsigned int     reserved_0:18;
unsigned int     prob_3:2;
unsigned int     prob_2:2;
unsigned int     prob_1:2;
unsigned int     prob_0:2;
unsigned int     pcie_clkreq_1:2;
unsigned int     pcie_clkreq_0:2;
unsigned int     sdio_loc:2;
}EMMC_MUXPAD2;

typedef struct 
{
unsigned int     nf_dqs_pdrive:4;
unsigned int     nf_dqs_ndrive:4;
unsigned int     nf_rdy_pdrive:4;
unsigned int     nf_rdy_ndrive:4;
unsigned int     nf_ce_n_0_pdrive:4;
unsigned int     nf_ce_n_0_ndrive:4;
unsigned int     nf_ce_n_1_pdrive:4;
unsigned int     nf_ce_n_1_ndrive:4;
}EMMC_PDRIVE_NF0;

typedef struct 
{
unsigned int     nf_dd_3_pdrive:4;
unsigned int     nf_dd_3_ndrive:4;
unsigned int     nf_dd_2_pdrive:4;
unsigned int     nf_dd_2_ndrive:4;
unsigned int     nf_dd_1_pdrive:4;
unsigned int     nf_dd_1_ndrive:4;
unsigned int     nf_dd_0_pdrive:4;
unsigned int     nf_dd_0_ndrive:4;
}EMMC_PDRIVE_NF1;

typedef struct 
{
unsigned int     nf_dd_7_pdrive:4;
unsigned int     nf_dd_7_ndrive:4;
unsigned int     nf_dd_6_pdrive:4;
unsigned int     nf_dd_6_ndrive:4;
unsigned int     nf_dd_5_pdrive:4;
unsigned int     nf_dd_5_ndrive:4;
unsigned int     nf_dd_4_pdrive:4;
unsigned int     nf_dd_4_ndrive:4;
}EMMC_PDRIVE_NF2;

typedef struct 
{
unsigned int     nf_rd_n_pdrive:4;
unsigned int     nf_rd_n_ndrive:4;
unsigned int     nf_wr_n_pdrive:4;
unsigned int     nf_wr_n_ndrive:4;
unsigned int     nf_cle_pdrive:4;
unsigned int     nf_cle_ndrive:4;
unsigned int     nf_ale_pdrive:4;
unsigned int     nf_ale_ndrive:4;
}EMMC_PDRIVE_NF3;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     emmc_dd_sb_pdrive:4;
unsigned int     emmc_dd_sb_ndrive:4;
}EMMC_PDRIVE_NF4;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     mmc_clk_pdrive:4;
unsigned int     mmc_clk_ndrive:4;
unsigned int     mmc_cmd_pdrive:4;
unsigned int     mmc_cmd_ndrive:4;
}EMMC_PDRIVE_CR0;

typedef struct 
{
unsigned int     mmc_data_3_pdrive:4;
unsigned int     mmc_data_3_ndrive:4;
unsigned int     mmc_data_2_pdrive:4;
unsigned int     mmc_data_2_ndrive:4;
unsigned int     mmc_data_1_pdrive:4;
unsigned int     mmc_data_1_ndrive:4;
unsigned int     mmc_data_0_pdrive:4;
unsigned int     mmc_data_0_ndrive:4;
}EMMC_PDRIVE_CR1;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     sdio_clk_pdrive:4;
unsigned int     sdio_clk_ndrive:4;
unsigned int     sdio_cmd_pdrive:4;
unsigned int     sdio_cmd_ndrive:4;
}EMMC_PDRIVE_SDIO0;

typedef struct 
{
unsigned int     sdio_data_3_pdrive:4;
unsigned int     sdio_data_3_ndrive:4;
unsigned int     sdio_data_2_pdrive:4;
unsigned int     sdio_data_2_ndrive:4;
unsigned int     sdio_data_1_pdrive:4;
unsigned int     sdio_data_1_ndrive:4;
unsigned int     sdio_data_0_pdrive:4;
unsigned int     sdio_data_0_ndrive:4;
}EMMC_PDRIVE_SDIO1;

typedef struct 
{
unsigned int     pad0_active:1;
unsigned int     reserved_0:7;
unsigned int     pad0_thred:8;
unsigned int     pad0_sw:4;
unsigned int     reserved_1:3;
unsigned int     pad0_ctrl:1;
unsigned int     reserved_2:2;
unsigned int     adc_val0:6;
}EMMC_LSADC0_PAD0;

typedef struct 
{
unsigned int     pad1_active:1;
unsigned int     reserved_0:7;
unsigned int     Pad1_thred:8;
unsigned int     Pad1_sw:4;
unsigned int     reserved_1:3;
unsigned int     Pad1_ctrl:1;
unsigned int     reserved_2:2;
unsigned int     adc_val0:6;
}EMMC_LSADC0_PAD1;

typedef struct 
{
unsigned int     Sel_wait:4;
unsigned int     Sel_adc_ck:4;
unsigned int     Debounce_cnt:4;
unsigned int     reserved_0:4;
unsigned int     Dout_Test_IN:8;
unsigned int     reserved_1:6;
unsigned int     Test_en:1;
unsigned int     Enable:1;
}EMMC_LSADC0_CTRL;

typedef struct 
{
unsigned int     IRQ_En:8;
unsigned int     PAD_CNT:4;
unsigned int     ADC_busy:1;
unsigned int     reserved_0:2;
unsigned int     pad_ctrl:5;
unsigned int     reserved_1:10;
unsigned int     Pad1_status:1;
unsigned int     Pad0_status:1;
}EMMC_LSADC0_STATUS;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     DUMMY2:4;
unsigned int     reserved_1:2;
unsigned int     JD_sbias:2;
unsigned int     reserved_2:2;
unsigned int     JD_adsbias:2;
unsigned int     JD_DUMMY:2;
unsigned int     reserved_3:1;
unsigned int     JD_svr:1;
unsigned int     reserved_4:3;
unsigned int     JD_adcksel:1;
unsigned int     reserved_5:3;
unsigned int     JD_power:1;
}EMMC_LSADC0_ANALOG_CTRL;

typedef struct 
{
unsigned int     reserved_0:13;
unsigned int     Lsadc_2_ifd_data_sel:3;
unsigned int     reserved_1:1;
unsigned int     Power_saving_enable:1;
unsigned int     Power_saving_cycle_time:3;
unsigned int     Power_saving_disable_time:3;
unsigned int     peri_top_debug:8;
}EMMC_LSADC0_PERI_TOP_DEBUG;

typedef struct 
{
unsigned int     Level_0_top_bound:8;
unsigned int     Level_0_low_bound:8;
unsigned int     Block0_en:1;
unsigned int     reserved_0:13;
unsigned int     INT_en0:1;
unsigned int     INT_pending_bit0:1;
}EMMC_LSADC0_PAD0_LEVEL_SET0;

typedef struct 
{
unsigned int     Level_1_top_bound:8;
unsigned int     Level_0_low_bound:8;
unsigned int     Block1_en:1;
unsigned int     reserved_0:13;
unsigned int     INT_en1:1;
unsigned int     INT_pending_bit1:1;
}EMMC_LSADC0_PAD0_LEVEL_SET1;

typedef struct 
{
unsigned int     Level_2_top_bound:8;
unsigned int     Level_2_low_bound:8;
unsigned int     Block2_en:1;
unsigned int     reserved_0:13;
unsigned int     INT_en2:1;
unsigned int     INT_pending_bit2:1;
}EMMC_LSADC0_PAD0_LEVEL_SET2;

typedef struct 
{
unsigned int     Level_3_top_bound:8;
unsigned int     Level_3_low_bound:8;
unsigned int     Block3_en:1;
unsigned int     reserved_0:13;
unsigned int     INT_en3:1;
unsigned int     INT_pending_bit3:1;
}EMMC_LSADC0_PAD0_LEVEL_SET3;

typedef struct 
{
unsigned int     Level_4_top_bound:8;
unsigned int     Level_4_low_bound:8;
unsigned int     Block4_en:1;
unsigned int     reserved_0:13;
unsigned int     INT_en4:1;
unsigned int     INT_pending_bit4:1;
}EMMC_LSADC0_PAD0_LEVEL_SET4;

typedef struct 
{
unsigned int     Level_5_top_bound:8;
unsigned int     Level_5_low_bound:8;
unsigned int     Block5_en:1;
unsigned int     reserved_0:13;
unsigned int     INT_en5:1;
unsigned int     INT_pending_bit5:1;
}EMMC_LSADC0_PAD0_LEVEL_SET5;

typedef struct 
{
unsigned int     Level_0_top_bound:8;
unsigned int     Level_0_low_bound:8;
unsigned int     Block0_en:1;
unsigned int     reserved_0:13;
unsigned int     INT_en0:1;
unsigned int     INT_pending_bit0:1;
}EMMC_LSADC0_PAD1_LEVEL_SET0;

typedef struct 
{
unsigned int     Level_1_top_bound:8;
unsigned int     Level_0_low_bound:8;
unsigned int     Block1_en:1;
unsigned int     reserved_0:13;
unsigned int     INT_en1:1;
unsigned int     INT_pending_bit1:1;
}EMMC_LSADC0_PAD1_LEVEL_SET1;

typedef struct 
{
unsigned int     Level_2_top_bound:8;
unsigned int     Level_2_low_bound:8;
unsigned int     Block2_en:1;
unsigned int     reserved_0:13;
unsigned int     INT_en2:1;
unsigned int     INT_pending_bit2:1;
}EMMC_LSADC0_PAD1_LEVEL_SET2;

typedef struct 
{
unsigned int     Level_3_top_bound:8;
unsigned int     Level_3_low_bound:8;
unsigned int     Block3_en:1;
unsigned int     reserved_0:13;
unsigned int     INT_en3:1;
unsigned int     INT_pending_bit3:1;
}EMMC_LSADC0_PAD1_LEVEL_SET3;

typedef struct 
{
unsigned int     Level_4_top_bound:8;
unsigned int     Level_4_low_bound:8;
unsigned int     Block4_en:1;
unsigned int     reserved_0:13;
unsigned int     INT_en4:1;
unsigned int     INT_pending_bit4:1;
}EMMC_LSADC0_PAD1_LEVEL_SET4;

typedef struct 
{
unsigned int     Level_5_top_bound:8;
unsigned int     Level_5_low_bound:8;
unsigned int     Block5_en:1;
unsigned int     reserved_0:13;
unsigned int     INT_en5:1;
unsigned int     INT_pending_bit5:1;
}EMMC_LSADC0_PAD1_LEVEL_SET5;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     reserved_1:2;
unsigned int     ADC_value0latch:6;
unsigned int     reserved_2:7;
unsigned int     INT_latchstatus:1;
}EMMC_LSADC0_INT_PAD0;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     reserved_1:2;
unsigned int     ADC_value1latch:6;
unsigned int     reserved_2:7;
unsigned int     INT_latchstatus:1;
}EMMC_LSADC0_INT_PAD1;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     lsadc1_clk_gating_en:1;
unsigned int     lsadc0_clk_gating_en:1;
}EMMC_LSADC_POWER;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     sel:1;
unsigned int     enable:1;
}EMMC_LSADC_DBG;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     sel:1;
}EMMC_LSADC_ANA_TEST;

typedef struct 
{
unsigned int     pad0_active:1;
unsigned int     reserved_0:6;
unsigned int     pad0_vref_sel:1;
unsigned int     pad0_thred:8;
unsigned int     DUMMY:3;
unsigned int     pad0_sw:1;
unsigned int     reserved_1:3;
unsigned int     pad0_ctrl:1;
unsigned int     reserved_2:2;
unsigned int     adc_val0:6;
}EMMC_LSADC1_PAD0;

typedef struct 
{
unsigned int     pad1_active:1;
unsigned int     reserved_0:6;
unsigned int     Pad1_vref_sel:1;
unsigned int     Pad1_thred:8;
unsigned int     DUMMY1:3;
unsigned int     Pad1_sw:1;
unsigned int     reserved_1:3;
unsigned int     Pad1_ctrl:1;
unsigned int     reserved_2:2;
unsigned int     adc_val0:6;
}EMMC_LSADC1_PAD1;

typedef struct 
{
unsigned int     Sel_wait:4;
unsigned int     Sel_adc_ck:4;
unsigned int     Debounce_cnt:8;
unsigned int     Dout_Test_IN:8;
unsigned int     reserved_0:2;
unsigned int     vdd_gnd_sel:1;
unsigned int     vdd_gnd_en:1;
unsigned int     reserved_1:2;
unsigned int     Test_en:1;
unsigned int     Enable:1;
}EMMC_LSADC1_CTRL;

typedef struct 
{
unsigned int     IRQ_En:8;
unsigned int     PAD_CNT:4;
unsigned int     ADC_busy:1;
unsigned int     reserved_0:2;
unsigned int     pad_ctrl:5;
unsigned int     reserved_1:10;
unsigned int     Pad1_status:1;
unsigned int     Pad0_status:1;
}EMMC_LSADC1_STATUS;

typedef struct 
{
unsigned int     test_in_en:1;
unsigned int     reserved_0:7;
unsigned int     DUMMY2:4;
unsigned int     reserved_1:2;
unsigned int     JD_sbias:2;
unsigned int     reserved_2:2;
unsigned int     JD_adsbias:2;
unsigned int     JD_DUMMY:2;
unsigned int     reserved_3:1;
unsigned int     JD_svr:1;
unsigned int     reserved_4:3;
unsigned int     JD_adcksel:1;
unsigned int     reserved_5:3;
unsigned int     JD_power:1;
}EMMC_LSADC1_ANALOG_CTRL;

typedef struct 
{
unsigned int     reserved_0:13;
unsigned int     Lsadc_2_ifd_data_sel:3;
unsigned int     reserved_1:1;
unsigned int     Power_saving_enable:1;
unsigned int     Power_saving_cycle_time:3;
unsigned int     Power_saving_disable_time:3;
unsigned int     peri_top_debug:8;
}EMMC_LSADC1_PERI_TOP_DEBUG;

typedef struct 
{
unsigned int     Level_0_top_bound:8;
unsigned int     Level_0_low_bound:8;
unsigned int     Block0_en:1;
unsigned int     reserved_0:13;
unsigned int     INT_en0:1;
unsigned int     INT_pending_bit0:1;
}EMMC_LSADC1_PAD0_LEVEL_SET0;

typedef struct 
{
unsigned int     Level_1_top_bound:8;
unsigned int     Level_0_low_bound:8;
unsigned int     Block1_en:1;
unsigned int     reserved_0:13;
unsigned int     INT_en1:1;
unsigned int     INT_pending_bit1:1;
}EMMC_LSADC1_PAD0_LEVEL_SET1;

typedef struct 
{
unsigned int     Level_2_top_bound:8;
unsigned int     Level_2_low_bound:8;
unsigned int     Block2_en:1;
unsigned int     reserved_0:13;
unsigned int     INT_en2:1;
unsigned int     INT_pending_bit2:1;
}EMMC_LSADC1_PAD0_LEVEL_SET2;

typedef struct 
{
unsigned int     Level_3_top_bound:8;
unsigned int     Level_3_low_bound:8;
unsigned int     Block3_en:1;
unsigned int     reserved_0:13;
unsigned int     INT_en3:1;
unsigned int     INT_pending_bit3:1;
}EMMC_LSADC1_PAD0_LEVEL_SET3;

typedef struct 
{
unsigned int     Level_4_top_bound:8;
unsigned int     Level_4_low_bound:8;
unsigned int     Block4_en:1;
unsigned int     reserved_0:13;
unsigned int     INT_en4:1;
unsigned int     INT_pending_bit4:1;
}EMMC_LSADC1_PAD0_LEVEL_SET4;

typedef struct 
{
unsigned int     Level_5_top_bound:8;
unsigned int     Level_5_low_bound:8;
unsigned int     Block5_en:1;
unsigned int     reserved_0:13;
unsigned int     INT_en5:1;
unsigned int     INT_pending_bit5:1;
}EMMC_LSADC1_PAD0_LEVEL_SET5;

typedef struct 
{
unsigned int     Level_0_top_bound:8;
unsigned int     Level_0_low_bound:8;
unsigned int     Block0_en:1;
unsigned int     reserved_0:13;
unsigned int     INT_en0:1;
unsigned int     INT_pending_bit0:1;
}EMMC_LSADC1_PAD1_LEVEL_SET0;

typedef struct 
{
unsigned int     Level_1_top_bound:8;
unsigned int     Level_0_low_bound:8;
unsigned int     Block1_en:1;
unsigned int     reserved_0:13;
unsigned int     INT_en1:1;
unsigned int     INT_pending_bit1:1;
}EMMC_LSADC1_PAD1_LEVEL_SET1;

typedef struct 
{
unsigned int     Level_2_top_bound:8;
unsigned int     Level_2_low_bound:8;
unsigned int     Block2_en:1;
unsigned int     reserved_0:13;
unsigned int     INT_en2:1;
unsigned int     INT_pending_bit2:1;
}EMMC_LSADC1_PAD1_LEVEL_SET2;

typedef struct 
{
unsigned int     Level_3_top_bound:8;
unsigned int     Level_3_low_bound:8;
unsigned int     Block3_en:1;
unsigned int     reserved_0:13;
unsigned int     INT_en3:1;
unsigned int     INT_pending_bit3:1;
}EMMC_LSADC1_PAD1_LEVEL_SET3;

typedef struct 
{
unsigned int     Level_4_top_bound:8;
unsigned int     Level_4_low_bound:8;
unsigned int     Block4_en:1;
unsigned int     reserved_0:13;
unsigned int     INT_en4:1;
unsigned int     INT_pending_bit4:1;
}EMMC_LSADC1_PAD1_LEVEL_SET4;

typedef struct 
{
unsigned int     Level_5_top_bound:8;
unsigned int     Level_5_low_bound:8;
unsigned int     Block5_en:1;
unsigned int     reserved_0:13;
unsigned int     INT_en5:1;
unsigned int     INT_pending_bit5:1;
}EMMC_LSADC1_PAD1_LEVEL_SET5;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     reserved_1:2;
unsigned int     ADC_value0latch:6;
unsigned int     reserved_2:7;
unsigned int     INT_latchstatus:1;
}EMMC_LSADC1_INT_PAD0;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     reserved_1:2;
unsigned int     ADC_value1latch:6;
unsigned int     reserved_2:7;
unsigned int     INT_latchstatus:1;
}EMMC_LSADC1_INT_PAD1;

#endif

#define EMMC_DESC_CTL0                                                               0x98012400
#define EMMC_DESC_CTL0_reg_addr                                                      "0x98012400"
#define EMMC_DESC_CTL0_reg                                                           0x98012400
#define set_EMMC_DESC_CTL0_reg(data)   (*((volatile unsigned int*) EMMC_DESC_CTL0_reg)=data)
#define get_EMMC_DESC_CTL0_reg   (*((volatile unsigned int*) EMMC_DESC_CTL0_reg))
#define EMMC_DESC_CTL0_inst_adr                                                      "0x0000"
#define EMMC_DESC_CTL0_inst                                                          0x0000
#define EMMC_DESC_CTL0_base_shift                                                    (0)
#define EMMC_DESC_CTL0_base_mask                                                     (0x3FFFFFFF)
#define EMMC_DESC_CTL0_base(data)                                                    (0x3FFFFFFF&((data)<<0))
#define EMMC_DESC_CTL0_base_src(data)                                                ((0x3FFFFFFF&(data))>>0)
#define EMMC_DESC_CTL0_get_base(data)                                                ((0x3FFFFFFF&(data))>>0)


#define EMMC_DESC_CTL1                                                               0x98012404
#define EMMC_DESC_CTL1_reg_addr                                                      "0x98012404"
#define EMMC_DESC_CTL1_reg                                                           0x98012404
#define set_EMMC_DESC_CTL1_reg(data)   (*((volatile unsigned int*) EMMC_DESC_CTL1_reg)=data)
#define get_EMMC_DESC_CTL1_reg   (*((volatile unsigned int*) EMMC_DESC_CTL1_reg))
#define EMMC_DESC_CTL1_inst_adr                                                      "0x0001"
#define EMMC_DESC_CTL1_inst                                                          0x0001
#define EMMC_DESC_CTL1_limit_shift                                                   (0)
#define EMMC_DESC_CTL1_limit_mask                                                    (0x3FFFFFFF)
#define EMMC_DESC_CTL1_limit(data)                                                   (0x3FFFFFFF&((data)<<0))
#define EMMC_DESC_CTL1_limit_src(data)                                               ((0x3FFFFFFF&(data))>>0)
#define EMMC_DESC_CTL1_get_limit(data)                                               ((0x3FFFFFFF&(data))>>0)


#define EMMC_DESC_CTL2                                                               0x98012408
#define EMMC_DESC_CTL2_reg_addr                                                      "0x98012408"
#define EMMC_DESC_CTL2_reg                                                           0x98012408
#define set_EMMC_DESC_CTL2_reg(data)   (*((volatile unsigned int*) EMMC_DESC_CTL2_reg)=data)
#define get_EMMC_DESC_CTL2_reg   (*((volatile unsigned int*) EMMC_DESC_CTL2_reg))
#define EMMC_DESC_CTL2_inst_adr                                                      "0x0002"
#define EMMC_DESC_CTL2_inst                                                          0x0002
#define EMMC_DESC_CTL2_desc_int_clr_shift                                            (31)
#define EMMC_DESC_CTL2_desc_int_clr_mask                                             (0x80000000)
#define EMMC_DESC_CTL2_desc_int_clr(data)                                            (0x80000000&((data)<<31))
#define EMMC_DESC_CTL2_desc_int_clr_src(data)                                        ((0x80000000&(data))>>31)
#define EMMC_DESC_CTL2_get_desc_int_clr(data)                                        ((0x80000000&(data))>>31)
#define EMMC_DESC_CTL2_desc_go_shift                                                 (30)
#define EMMC_DESC_CTL2_desc_go_mask                                                  (0x40000000)
#define EMMC_DESC_CTL2_desc_go(data)                                                 (0x40000000&((data)<<30))
#define EMMC_DESC_CTL2_desc_go_src(data)                                             ((0x40000000&(data))>>30)
#define EMMC_DESC_CTL2_get_desc_go(data)                                             ((0x40000000&(data))>>30)
#define EMMC_DESC_CTL2_wptr_shift                                                    (0)
#define EMMC_DESC_CTL2_wptr_mask                                                     (0x3FFFFFFF)
#define EMMC_DESC_CTL2_wptr(data)                                                    (0x3FFFFFFF&((data)<<0))
#define EMMC_DESC_CTL2_wptr_src(data)                                                ((0x3FFFFFFF&(data))>>0)
#define EMMC_DESC_CTL2_get_wptr(data)                                                ((0x3FFFFFFF&(data))>>0)


#define EMMC_DESC_CTL3                                                               0x9801240C
#define EMMC_DESC_CTL3_reg_addr                                                      "0x9801240C"
#define EMMC_DESC_CTL3_reg                                                           0x9801240C
#define set_EMMC_DESC_CTL3_reg(data)   (*((volatile unsigned int*) EMMC_DESC_CTL3_reg)=data)
#define get_EMMC_DESC_CTL3_reg   (*((volatile unsigned int*) EMMC_DESC_CTL3_reg))
#define EMMC_DESC_CTL3_inst_adr                                                      "0x0003"
#define EMMC_DESC_CTL3_inst                                                          0x0003
#define EMMC_DESC_CTL3_rptr_shift                                                    (0)
#define EMMC_DESC_CTL3_rptr_mask                                                     (0x3FFFFFFF)
#define EMMC_DESC_CTL3_rptr(data)                                                    (0x3FFFFFFF&((data)<<0))
#define EMMC_DESC_CTL3_rptr_src(data)                                                ((0x3FFFFFFF&(data))>>0)
#define EMMC_DESC_CTL3_get_rptr(data)                                                ((0x3FFFFFFF&(data))>>0)


#define EMMC_DESC_STS                                                                0x98012410
#define EMMC_DESC_STS_reg_addr                                                       "0x98012410"
#define EMMC_DESC_STS_reg                                                            0x98012410
#define set_EMMC_DESC_STS_reg(data)   (*((volatile unsigned int*) EMMC_DESC_STS_reg)=data)
#define get_EMMC_DESC_STS_reg   (*((volatile unsigned int*) EMMC_DESC_STS_reg))
#define EMMC_DESC_STS_inst_adr                                                       "0x0004"
#define EMMC_DESC_STS_inst                                                           0x0004
#define EMMC_DESC_STS_desc_sts_shift                                                 (0)
#define EMMC_DESC_STS_desc_sts_mask                                                  (0x0000FFFF)
#define EMMC_DESC_STS_desc_sts(data)                                                 (0x0000FFFF&((data)<<0))
#define EMMC_DESC_STS_desc_sts_src(data)                                             ((0x0000FFFF&(data))>>0)
#define EMMC_DESC_STS_get_desc_sts(data)                                             ((0x0000FFFF&(data))>>0)


#define EMMC_DESC_THD                                                                0x98012414
#define EMMC_DESC_THD_reg_addr                                                       "0x98012414"
#define EMMC_DESC_THD_reg                                                            0x98012414
#define set_EMMC_DESC_THD_reg(data)   (*((volatile unsigned int*) EMMC_DESC_THD_reg)=data)
#define get_EMMC_DESC_THD_reg   (*((volatile unsigned int*) EMMC_DESC_THD_reg))
#define EMMC_DESC_THD_inst_adr                                                       "0x0005"
#define EMMC_DESC_THD_inst                                                           0x0005
#define EMMC_DESC_THD_desc_timeout_bypass_shift                                      (31)
#define EMMC_DESC_THD_desc_timeout_bypass_mask                                       (0x80000000)
#define EMMC_DESC_THD_desc_timeout_bypass(data)                                      (0x80000000&((data)<<31))
#define EMMC_DESC_THD_desc_timeout_bypass_src(data)                                  ((0x80000000&(data))>>31)
#define EMMC_DESC_THD_get_desc_timeout_bypass(data)                                  ((0x80000000&(data))>>31)
#define EMMC_DESC_THD_desc_timeout_thd_shift                                         (0)
#define EMMC_DESC_THD_desc_timeout_thd_mask                                          (0x7FFFFFFF)
#define EMMC_DESC_THD_desc_timeout_thd(data)                                         (0x7FFFFFFF&((data)<<0))
#define EMMC_DESC_THD_desc_timeout_thd_src(data)                                     ((0x7FFFFFFF&(data))>>0)
#define EMMC_DESC_THD_get_desc_timeout_thd(data)                                     ((0x7FFFFFFF&(data))>>0)


#define EMMC_SYS_LOW_PWR                                                             0x98012418
#define EMMC_SYS_LOW_PWR_reg_addr                                                    "0x98012418"
#define EMMC_SYS_LOW_PWR_reg                                                         0x98012418
#define set_EMMC_SYS_LOW_PWR_reg(data)   (*((volatile unsigned int*) EMMC_SYS_LOW_PWR_reg)=data)
#define get_EMMC_SYS_LOW_PWR_reg   (*((volatile unsigned int*) EMMC_SYS_LOW_PWR_reg))
#define EMMC_SYS_LOW_PWR_inst_adr                                                    "0x0006"
#define EMMC_SYS_LOW_PWR_inst                                                        0x0006
#define EMMC_SYS_LOW_PWR_mcu_pp_sram_lp_ena_shift                                    (7)
#define EMMC_SYS_LOW_PWR_mcu_pp_sram_lp_ena_mask                                     (0x00000080)
#define EMMC_SYS_LOW_PWR_mcu_pp_sram_lp_ena(data)                                    (0x00000080&((data)<<7))
#define EMMC_SYS_LOW_PWR_mcu_pp_sram_lp_ena_src(data)                                ((0x00000080&(data))>>7)
#define EMMC_SYS_LOW_PWR_get_mcu_pp_sram_lp_ena(data)                                ((0x00000080&(data))>>7)
#define EMMC_SYS_LOW_PWR_sys_clk_gate_ena_shift                                      (6)
#define EMMC_SYS_LOW_PWR_sys_clk_gate_ena_mask                                       (0x00000040)
#define EMMC_SYS_LOW_PWR_sys_clk_gate_ena(data)                                      (0x00000040&((data)<<6))
#define EMMC_SYS_LOW_PWR_sys_clk_gate_ena_src(data)                                  ((0x00000040&(data))>>6)
#define EMMC_SYS_LOW_PWR_get_sys_clk_gate_ena(data)                                  ((0x00000040&(data))>>6)
#define EMMC_SYS_LOW_PWR_cp_clk_gate_ena_shift                                       (5)
#define EMMC_SYS_LOW_PWR_cp_clk_gate_ena_mask                                        (0x00000020)
#define EMMC_SYS_LOW_PWR_cp_clk_gate_ena(data)                                       (0x00000020&((data)<<5))
#define EMMC_SYS_LOW_PWR_cp_clk_gate_ena_src(data)                                   ((0x00000020&(data))>>5)
#define EMMC_SYS_LOW_PWR_get_cp_clk_gate_ena(data)                                   ((0x00000020&(data))>>5)
#define EMMC_SYS_LOW_PWR_dma_sram_lp_ena_shift                                       (4)
#define EMMC_SYS_LOW_PWR_dma_sram_lp_ena_mask                                        (0x00000010)
#define EMMC_SYS_LOW_PWR_dma_sram_lp_ena(data)                                       (0x00000010&((data)<<4))
#define EMMC_SYS_LOW_PWR_dma_sram_lp_ena_src(data)                                   ((0x00000010&(data))>>4)
#define EMMC_SYS_LOW_PWR_get_dma_sram_lp_ena(data)                                   ((0x00000010&(data))>>4)
#define EMMC_SYS_LOW_PWR_dma_sram_rdy_num_shift                                      (0)
#define EMMC_SYS_LOW_PWR_dma_sram_rdy_num_mask                                       (0x0000000F)
#define EMMC_SYS_LOW_PWR_dma_sram_rdy_num(data)                                      (0x0000000F&((data)<<0))
#define EMMC_SYS_LOW_PWR_dma_sram_rdy_num_src(data)                                  ((0x0000000F&(data))>>0)
#define EMMC_SYS_LOW_PWR_get_dma_sram_rdy_num(data)                                  ((0x0000000F&(data))>>0)


#define EMMC_CP                                                                      0x9801241c
#define EMMC_CP_reg_addr                                                             "0x9801241C"
#define EMMC_CP_reg                                                                  0x9801241C
#define set_EMMC_CP_reg(data)   (*((volatile unsigned int*) EMMC_CP_reg)=data)
#define get_EMMC_CP_reg   (*((volatile unsigned int*) EMMC_CP_reg))
#define EMMC_CP_inst_adr                                                             "0x0007"
#define EMMC_CP_inst                                                                 0x0007
#define EMMC_CP_cp_de_en_shift                                                       (25)
#define EMMC_CP_cp_de_en_mask                                                        (0x02000000)
#define EMMC_CP_cp_de_en(data)                                                       (0x02000000&((data)<<25))
#define EMMC_CP_cp_de_en_src(data)                                                   ((0x02000000&(data))>>25)
#define EMMC_CP_get_cp_de_en(data)                                                   ((0x02000000&(data))>>25)
#define EMMC_CP_cp_length_shift                                                      (9)
#define EMMC_CP_cp_length_mask                                                       (0x01FFFE00)
#define EMMC_CP_cp_length(data)                                                      (0x01FFFE00&((data)<<9))
#define EMMC_CP_cp_length_src(data)                                                  ((0x01FFFE00&(data))>>9)
#define EMMC_CP_get_cp_length(data)                                                  ((0x01FFFE00&(data))>>9)
#define EMMC_CP_cp_first_shift                                                       (8)
#define EMMC_CP_cp_first_mask                                                        (0x00000100)
#define EMMC_CP_cp_first(data)                                                       (0x00000100&((data)<<8))
#define EMMC_CP_cp_first_src(data)                                                   ((0x00000100&(data))>>8)
#define EMMC_CP_get_cp_first(data)                                                   ((0x00000100&(data))>>8)
#define EMMC_CP_cp_enable_shift                                                      (7)
#define EMMC_CP_cp_enable_mask                                                       (0x00000080)
#define EMMC_CP_cp_enable(data)                                                      (0x00000080&((data)<<7))
#define EMMC_CP_cp_enable_src(data)                                                  ((0x00000080&(data))>>7)
#define EMMC_CP_get_cp_enable(data)                                                  ((0x00000080&(data))>>7)
#define EMMC_CP_cp_sram_sel_shift                                                    (6)
#define EMMC_CP_cp_sram_sel_mask                                                     (0x00000040)
#define EMMC_CP_cp_sram_sel(data)                                                    (0x00000040&((data)<<6))
#define EMMC_CP_cp_sram_sel_src(data)                                                ((0x00000040&(data))>>6)
#define EMMC_CP_get_cp_sram_sel(data)                                                ((0x00000040&(data))>>6)


#define EMMC_OTHER1                                                                  0x98012420
#define EMMC_OTHER1_reg_addr                                                         "0x98012420"
#define EMMC_OTHER1_reg                                                              0x98012420
#define set_EMMC_OTHER1_reg(data)   (*((volatile unsigned int*) EMMC_OTHER1_reg)=data)
#define get_EMMC_OTHER1_reg   (*((volatile unsigned int*) EMMC_OTHER1_reg))
#define EMMC_OTHER1_inst_adr                                                         "0x0008"
#define EMMC_OTHER1_inst                                                             0x0008
#define EMMC_OTHER1_Dbus_endian_sel_shift                                            (1)
#define EMMC_OTHER1_Dbus_endian_sel_mask                                             (0x00000002)
#define EMMC_OTHER1_Dbus_endian_sel(data)                                            (0x00000002&((data)<<1))
#define EMMC_OTHER1_Dbus_endian_sel_src(data)                                        ((0x00000002&(data))>>1)
#define EMMC_OTHER1_get_Dbus_endian_sel(data)                                        ((0x00000002&(data))>>1)
#define EMMC_OTHER1_l4_gated_disable_shift                                           (0)
#define EMMC_OTHER1_l4_gated_disable_mask                                            (0x00000001)
#define EMMC_OTHER1_l4_gated_disable(data)                                           (0x00000001&((data)<<0))
#define EMMC_OTHER1_l4_gated_disable_src(data)                                       ((0x00000001&(data))>>0)
#define EMMC_OTHER1_get_l4_gated_disable(data)                                       ((0x00000001&(data))>>0)


#define EMMC_ISR                                                                     0x98012424
#define EMMC_ISR_reg_addr                                                            "0x98012424"
#define EMMC_ISR_reg                                                                 0x98012424
#define set_EMMC_ISR_reg(data)   (*((volatile unsigned int*) EMMC_ISR_reg)=data)
#define get_EMMC_ISR_reg   (*((volatile unsigned int*) EMMC_ISR_reg))
#define EMMC_ISR_inst_adr                                                            "0x0009"
#define EMMC_ISR_inst                                                                0x0009
#define EMMC_ISR_ip_int_mask_shift                                                   (4)
#define EMMC_ISR_ip_int_mask_mask                                                    (0x00000010)
#define EMMC_ISR_ip_int_mask(data)                                                   (0x00000010&((data)<<4))
#define EMMC_ISR_ip_int_mask_src(data)                                               ((0x00000010&(data))>>4)
#define EMMC_ISR_get_ip_int_mask(data)                                               ((0x00000010&(data))>>4)
#define EMMC_ISR_desc_int_mask_shift                                                 (3)
#define EMMC_ISR_desc_int_mask_mask                                                  (0x00000008)
#define EMMC_ISR_desc_int_mask(data)                                                 (0x00000008&((data)<<3))
#define EMMC_ISR_desc_int_mask_src(data)                                             ((0x00000008&(data))>>3)
#define EMMC_ISR_get_desc_int_mask(data)                                             ((0x00000008&(data))>>3)
#define EMMC_ISR_Dma_int_mask_shift                                                  (2)
#define EMMC_ISR_Dma_int_mask_mask                                                   (0x00000004)
#define EMMC_ISR_Dma_int_mask(data)                                                  (0x00000004&((data)<<2))
#define EMMC_ISR_Dma_int_mask_src(data)                                              ((0x00000004&(data))>>2)
#define EMMC_ISR_get_Dma_int_mask(data)                                              ((0x00000004&(data))>>2)
#define EMMC_ISR_dma_done_int_shift                                                  (1)
#define EMMC_ISR_dma_done_int_mask                                                   (0x00000002)
#define EMMC_ISR_dma_done_int(data)                                                  (0x00000002&((data)<<1))
#define EMMC_ISR_dma_done_int_src(data)                                              ((0x00000002&(data))>>1)
#define EMMC_ISR_get_dma_done_int(data)                                              ((0x00000002&(data))>>1)
#define EMMC_ISR_write_data_shift                                                    (0)
#define EMMC_ISR_write_data_mask                                                     (0x00000001)
#define EMMC_ISR_write_data(data)                                                    (0x00000001&((data)<<0))
#define EMMC_ISR_write_data_src(data)                                                ((0x00000001&(data))>>0)
#define EMMC_ISR_get_write_data(data)                                                ((0x00000001&(data))>>0)


#define EMMC_ISREN                                                                   0x98012428
#define EMMC_ISREN_reg_addr                                                          "0x98012428"
#define EMMC_ISREN_reg                                                               0x98012428
#define set_EMMC_ISREN_reg(data)   (*((volatile unsigned int*) EMMC_ISREN_reg)=data)
#define get_EMMC_ISREN_reg   (*((volatile unsigned int*) EMMC_ISREN_reg))
#define EMMC_ISREN_inst_adr                                                          "0x000A"
#define EMMC_ISREN_inst                                                              0x000A
#define EMMC_ISREN_dmy_shift                                                         (0)
#define EMMC_ISREN_dmy_mask                                                          (0xFFFFFFFF)
#define EMMC_ISREN_dmy(data)                                                         (0xFFFFFFFF&((data)<<0))
#define EMMC_ISREN_dmy_src(data)                                                     ((0xFFFFFFFF&(data))>>0)
#define EMMC_ISREN_get_dmy(data)                                                     ((0xFFFFFFFF&(data))>>0)


#define EMMC_DUMMY_SYS                                                               0x9801242C
#define EMMC_DUMMY_SYS_reg_addr                                                      "0x9801242C"
#define EMMC_DUMMY_SYS_reg                                                           0x9801242C
#define set_EMMC_DUMMY_SYS_reg(data)   (*((volatile unsigned int*) EMMC_DUMMY_SYS_reg)=data)
#define get_EMMC_DUMMY_SYS_reg   (*((volatile unsigned int*) EMMC_DUMMY_SYS_reg))
#define EMMC_DUMMY_SYS_inst_adr                                                      "0x000B"
#define EMMC_DUMMY_SYS_inst                                                          0x000B
#define EMMC_DUMMY_SYS_dmy_shift                                                     (0)
#define EMMC_DUMMY_SYS_dmy_mask                                                      (0xFFFFFFFF)
#define EMMC_DUMMY_SYS_dmy(data)                                                     (0xFFFFFFFF&((data)<<0))
#define EMMC_DUMMY_SYS_dmy_src(data)                                                 ((0xFFFFFFFF&(data))>>0)
#define EMMC_DUMMY_SYS_get_dmy(data)                                                 ((0xFFFFFFFF&(data))>>0)


#define EMMC_AHB                                                                     0x98012430
#define EMMC_AHB_reg_addr                                                            "0x98012430"
#define EMMC_AHB_reg                                                                 0x98012430
#define set_EMMC_AHB_reg(data)   (*((volatile unsigned int*) EMMC_AHB_reg)=data)
#define get_EMMC_AHB_reg   (*((volatile unsigned int*) EMMC_AHB_reg))
#define EMMC_AHB_inst_adr                                                            "0x000C"
#define EMMC_AHB_inst                                                                0x000C
#define EMMC_AHB_EMMC_ahb_m_big_endian_shift                                         (2)
#define EMMC_AHB_EMMC_ahb_m_big_endian_mask                                          (0x00000004)
#define EMMC_AHB_EMMC_ahb_m_big_endian(data)                                         (0x00000004&((data)<<2))
#define EMMC_AHB_EMMC_ahb_m_big_endian_src(data)                                     ((0x00000004&(data))>>2)
#define EMMC_AHB_get_EMMC_ahb_m_big_endian(data)                                     ((0x00000004&(data))>>2)
#define EMMC_AHB_EMMC_ahb_s_big_endian_shift                                         (1)
#define EMMC_AHB_EMMC_ahb_s_big_endian_mask                                          (0x00000002)
#define EMMC_AHB_EMMC_ahb_s_big_endian(data)                                         (0x00000002&((data)<<1))
#define EMMC_AHB_EMMC_ahb_s_big_endian_src(data)                                     ((0x00000002&(data))>>1)
#define EMMC_AHB_get_EMMC_ahb_s_big_endian(data)                                     ((0x00000002&(data))>>1)


#define EMMC_DBG                                                                     0x98012444
#define EMMC_DBG_reg_addr                                                            "0x98012444"
#define EMMC_DBG_reg                                                                 0x98012444
#define set_EMMC_DBG_reg(data)   (*((volatile unsigned int*) EMMC_DBG_reg)=data)
#define get_EMMC_DBG_reg   (*((volatile unsigned int*) EMMC_DBG_reg))
#define EMMC_DBG_inst_adr                                                            "0x0011"
#define EMMC_DBG_inst                                                                0x0011
#define EMMC_DBG_write_enable3_shift                                                 (13)
#define EMMC_DBG_write_enable3_mask                                                  (0x00002000)
#define EMMC_DBG_write_enable3(data)                                                 (0x00002000&((data)<<13))
#define EMMC_DBG_write_enable3_src(data)                                             ((0x00002000&(data))>>13)
#define EMMC_DBG_get_write_enable3(data)                                             ((0x00002000&(data))>>13)
#define EMMC_DBG_sel1_shift                                                          (8)
#define EMMC_DBG_sel1_mask                                                           (0x00001F00)
#define EMMC_DBG_sel1(data)                                                          (0x00001F00&((data)<<8))
#define EMMC_DBG_sel1_src(data)                                                      ((0x00001F00&(data))>>8)
#define EMMC_DBG_get_sel1(data)                                                      ((0x00001F00&(data))>>8)
#define EMMC_DBG_write_enable2_shift                                                 (7)
#define EMMC_DBG_write_enable2_mask                                                  (0x00000080)
#define EMMC_DBG_write_enable2(data)                                                 (0x00000080&((data)<<7))
#define EMMC_DBG_write_enable2_src(data)                                             ((0x00000080&(data))>>7)
#define EMMC_DBG_get_write_enable2(data)                                             ((0x00000080&(data))>>7)
#define EMMC_DBG_sel0_shift                                                          (2)
#define EMMC_DBG_sel0_mask                                                           (0x0000007C)
#define EMMC_DBG_sel0(data)                                                          (0x0000007C&((data)<<2))
#define EMMC_DBG_sel0_src(data)                                                      ((0x0000007C&(data))>>2)
#define EMMC_DBG_get_sel0(data)                                                      ((0x0000007C&(data))>>2)
#define EMMC_DBG_write_enable1_shift                                                 (1)
#define EMMC_DBG_write_enable1_mask                                                  (0x00000002)
#define EMMC_DBG_write_enable1(data)                                                 (0x00000002&((data)<<1))
#define EMMC_DBG_write_enable1_src(data)                                             ((0x00000002&(data))>>1)
#define EMMC_DBG_get_write_enable1(data)                                             ((0x00000002&(data))>>1)
#define EMMC_DBG_enable_shift                                                        (0)
#define EMMC_DBG_enable_mask                                                         (0x00000001)
#define EMMC_DBG_enable(data)                                                        (0x00000001&((data)<<0))
#define EMMC_DBG_enable_src(data)                                                    ((0x00000001&(data))>>0)
#define EMMC_DBG_get_enable(data)                                                    ((0x00000001&(data))>>0)


#define EMMC_PP_BIST_CTL                                                             0x98012460
#define EMMC_PP_BIST_CTL_reg_addr                                                    "0x98012460"
#define EMMC_PP_BIST_CTL_reg                                                         0x98012460
#define set_EMMC_PP_BIST_CTL_reg(data)   (*((volatile unsigned int*) EMMC_PP_BIST_CTL_reg)=data)
#define get_EMMC_PP_BIST_CTL_reg   (*((volatile unsigned int*) EMMC_PP_BIST_CTL_reg))
#define EMMC_PP_BIST_CTL_inst_adr                                                    "0x0018"
#define EMMC_PP_BIST_CTL_inst                                                        0x0018
#define EMMC_PP_BIST_CTL_bist_cr_desc_rme_0_shift                                    (24)
#define EMMC_PP_BIST_CTL_bist_cr_desc_rme_0_mask                                     (0x01000000)
#define EMMC_PP_BIST_CTL_bist_cr_desc_rme_0(data)                                    (0x01000000&((data)<<24))
#define EMMC_PP_BIST_CTL_bist_cr_desc_rme_0_src(data)                                ((0x01000000&(data))>>24)
#define EMMC_PP_BIST_CTL_get_bist_cr_desc_rme_0(data)                                ((0x01000000&(data))>>24)
#define EMMC_PP_BIST_CTL_bist_cr_desc_rm_0_shift                                     (20)
#define EMMC_PP_BIST_CTL_bist_cr_desc_rm_0_mask                                      (0x00F00000)
#define EMMC_PP_BIST_CTL_bist_cr_desc_rm_0(data)                                     (0x00F00000&((data)<<20))
#define EMMC_PP_BIST_CTL_bist_cr_desc_rm_0_src(data)                                 ((0x00F00000&(data))>>20)
#define EMMC_PP_BIST_CTL_get_bist_cr_desc_rm_0(data)                                 ((0x00F00000&(data))>>20)
#define EMMC_PP_BIST_CTL_bist_cr_ppb_rme_1_shift                                     (16)
#define EMMC_PP_BIST_CTL_bist_cr_ppb_rme_1_mask                                      (0x00010000)
#define EMMC_PP_BIST_CTL_bist_cr_ppb_rme_1(data)                                     (0x00010000&((data)<<16))
#define EMMC_PP_BIST_CTL_bist_cr_ppb_rme_1_src(data)                                 ((0x00010000&(data))>>16)
#define EMMC_PP_BIST_CTL_get_bist_cr_ppb_rme_1(data)                                 ((0x00010000&(data))>>16)
#define EMMC_PP_BIST_CTL_bist_cr_ppb_rm_1_shift                                      (12)
#define EMMC_PP_BIST_CTL_bist_cr_ppb_rm_1_mask                                       (0x0000F000)
#define EMMC_PP_BIST_CTL_bist_cr_ppb_rm_1(data)                                      (0x0000F000&((data)<<12))
#define EMMC_PP_BIST_CTL_bist_cr_ppb_rm_1_src(data)                                  ((0x0000F000&(data))>>12)
#define EMMC_PP_BIST_CTL_get_bist_cr_ppb_rm_1(data)                                  ((0x0000F000&(data))>>12)
#define EMMC_PP_BIST_CTL_bist_cr_ppb_rme_0_shift                                     (8)
#define EMMC_PP_BIST_CTL_bist_cr_ppb_rme_0_mask                                      (0x00000100)
#define EMMC_PP_BIST_CTL_bist_cr_ppb_rme_0(data)                                     (0x00000100&((data)<<8))
#define EMMC_PP_BIST_CTL_bist_cr_ppb_rme_0_src(data)                                 ((0x00000100&(data))>>8)
#define EMMC_PP_BIST_CTL_get_bist_cr_ppb_rme_0(data)                                 ((0x00000100&(data))>>8)
#define EMMC_PP_BIST_CTL_bist_cr_ppb_rm_0_shift                                      (4)
#define EMMC_PP_BIST_CTL_bist_cr_ppb_rm_0_mask                                       (0x000000F0)
#define EMMC_PP_BIST_CTL_bist_cr_ppb_rm_0(data)                                      (0x000000F0&((data)<<4))
#define EMMC_PP_BIST_CTL_bist_cr_ppb_rm_0_src(data)                                  ((0x000000F0&(data))>>4)
#define EMMC_PP_BIST_CTL_get_bist_cr_ppb_rm_0(data)                                  ((0x000000F0&(data))>>4)
#define EMMC_PP_BIST_CTL_bist_drf_test_resume_shift                                  (3)
#define EMMC_PP_BIST_CTL_bist_drf_test_resume_mask                                   (0x00000008)
#define EMMC_PP_BIST_CTL_bist_drf_test_resume(data)                                  (0x00000008&((data)<<3))
#define EMMC_PP_BIST_CTL_bist_drf_test_resume_src(data)                              ((0x00000008&(data))>>3)
#define EMMC_PP_BIST_CTL_get_bist_drf_test_resume(data)                              ((0x00000008&(data))>>3)
#define EMMC_PP_BIST_CTL_bist_drf_mode_shift                                         (2)
#define EMMC_PP_BIST_CTL_bist_drf_mode_mask                                          (0x00000004)
#define EMMC_PP_BIST_CTL_bist_drf_mode(data)                                         (0x00000004&((data)<<2))
#define EMMC_PP_BIST_CTL_bist_drf_mode_src(data)                                     ((0x00000004&(data))>>2)
#define EMMC_PP_BIST_CTL_get_bist_drf_mode(data)                                     ((0x00000004&(data))>>2)
#define EMMC_PP_BIST_CTL_bist_en_shift                                               (1)
#define EMMC_PP_BIST_CTL_bist_en_mask                                                (0x00000002)
#define EMMC_PP_BIST_CTL_bist_en(data)                                               (0x00000002&((data)<<1))
#define EMMC_PP_BIST_CTL_bist_en_src(data)                                           ((0x00000002&(data))>>1)
#define EMMC_PP_BIST_CTL_get_bist_en(data)                                           ((0x00000002&(data))>>1)
#define EMMC_PP_BIST_CTL_bist_ls_shift                                               (0)
#define EMMC_PP_BIST_CTL_bist_ls_mask                                                (0x00000001)
#define EMMC_PP_BIST_CTL_bist_ls(data)                                               (0x00000001&((data)<<0))
#define EMMC_PP_BIST_CTL_bist_ls_src(data)                                           ((0x00000001&(data))>>0)
#define EMMC_PP_BIST_CTL_get_bist_ls(data)                                           ((0x00000001&(data))>>0)


#define EMMC_IP_BIST_CTL                                                             0x98012464
#define EMMC_IP_BIST_CTL_reg_addr                                                    "0x98012464"
#define EMMC_IP_BIST_CTL_reg                                                         0x98012464
#define set_EMMC_IP_BIST_CTL_reg(data)   (*((volatile unsigned int*) EMMC_IP_BIST_CTL_reg)=data)
#define get_EMMC_IP_BIST_CTL_reg   (*((volatile unsigned int*) EMMC_IP_BIST_CTL_reg))
#define EMMC_IP_BIST_CTL_inst_adr                                                    "0x0019"
#define EMMC_IP_BIST_CTL_inst                                                        0x0019
#define EMMC_IP_BIST_CTL_bist_cr_ip_rme_1_shift                                      (16)
#define EMMC_IP_BIST_CTL_bist_cr_ip_rme_1_mask                                       (0x00010000)
#define EMMC_IP_BIST_CTL_bist_cr_ip_rme_1(data)                                      (0x00010000&((data)<<16))
#define EMMC_IP_BIST_CTL_bist_cr_ip_rme_1_src(data)                                  ((0x00010000&(data))>>16)
#define EMMC_IP_BIST_CTL_get_bist_cr_ip_rme_1(data)                                  ((0x00010000&(data))>>16)
#define EMMC_IP_BIST_CTL_bist_cr_ip_rm_1_shift                                       (12)
#define EMMC_IP_BIST_CTL_bist_cr_ip_rm_1_mask                                        (0x0000F000)
#define EMMC_IP_BIST_CTL_bist_cr_ip_rm_1(data)                                       (0x0000F000&((data)<<12))
#define EMMC_IP_BIST_CTL_bist_cr_ip_rm_1_src(data)                                   ((0x0000F000&(data))>>12)
#define EMMC_IP_BIST_CTL_get_bist_cr_ip_rm_1(data)                                   ((0x0000F000&(data))>>12)
#define EMMC_IP_BIST_CTL_bist_cr_ip_rme_0_shift                                      (8)
#define EMMC_IP_BIST_CTL_bist_cr_ip_rme_0_mask                                       (0x00000100)
#define EMMC_IP_BIST_CTL_bist_cr_ip_rme_0(data)                                      (0x00000100&((data)<<8))
#define EMMC_IP_BIST_CTL_bist_cr_ip_rme_0_src(data)                                  ((0x00000100&(data))>>8)
#define EMMC_IP_BIST_CTL_get_bist_cr_ip_rme_0(data)                                  ((0x00000100&(data))>>8)
#define EMMC_IP_BIST_CTL_bist_cr_ip_rm_0_shift                                       (4)
#define EMMC_IP_BIST_CTL_bist_cr_ip_rm_0_mask                                        (0x000000F0)
#define EMMC_IP_BIST_CTL_bist_cr_ip_rm_0(data)                                       (0x000000F0&((data)<<4))
#define EMMC_IP_BIST_CTL_bist_cr_ip_rm_0_src(data)                                   ((0x000000F0&(data))>>4)
#define EMMC_IP_BIST_CTL_get_bist_cr_ip_rm_0(data)                                   ((0x000000F0&(data))>>4)
#define EMMC_IP_BIST_CTL_bist_drf_test_resume_shift                                  (3)
#define EMMC_IP_BIST_CTL_bist_drf_test_resume_mask                                   (0x00000008)
#define EMMC_IP_BIST_CTL_bist_drf_test_resume(data)                                  (0x00000008&((data)<<3))
#define EMMC_IP_BIST_CTL_bist_drf_test_resume_src(data)                              ((0x00000008&(data))>>3)
#define EMMC_IP_BIST_CTL_get_bist_drf_test_resume(data)                              ((0x00000008&(data))>>3)
#define EMMC_IP_BIST_CTL_bist_drf_mode_shift                                         (2)
#define EMMC_IP_BIST_CTL_bist_drf_mode_mask                                          (0x00000004)
#define EMMC_IP_BIST_CTL_bist_drf_mode(data)                                         (0x00000004&((data)<<2))
#define EMMC_IP_BIST_CTL_bist_drf_mode_src(data)                                     ((0x00000004&(data))>>2)
#define EMMC_IP_BIST_CTL_get_bist_drf_mode(data)                                     ((0x00000004&(data))>>2)
#define EMMC_IP_BIST_CTL_bist_en_shift                                               (1)
#define EMMC_IP_BIST_CTL_bist_en_mask                                                (0x00000002)
#define EMMC_IP_BIST_CTL_bist_en(data)                                               (0x00000002&((data)<<1))
#define EMMC_IP_BIST_CTL_bist_en_src(data)                                           ((0x00000002&(data))>>1)
#define EMMC_IP_BIST_CTL_get_bist_en(data)                                           ((0x00000002&(data))>>1)
#define EMMC_IP_BIST_CTL_bist_ls_shift                                               (0)
#define EMMC_IP_BIST_CTL_bist_ls_mask                                                (0x00000001)
#define EMMC_IP_BIST_CTL_bist_ls(data)                                               (0x00000001&((data)<<0))
#define EMMC_IP_BIST_CTL_bist_ls_src(data)                                           ((0x00000001&(data))>>0)
#define EMMC_IP_BIST_CTL_get_bist_ls(data)                                           ((0x00000001&(data))>>0)


#define EMMC_PP_BIST_STS                                                             0x98012468
#define EMMC_PP_BIST_STS_reg_addr                                                    "0x98012468"
#define EMMC_PP_BIST_STS_reg                                                         0x98012468
#define set_EMMC_PP_BIST_STS_reg(data)   (*((volatile unsigned int*) EMMC_PP_BIST_STS_reg)=data)
#define get_EMMC_PP_BIST_STS_reg   (*((volatile unsigned int*) EMMC_PP_BIST_STS_reg))
#define EMMC_PP_BIST_STS_inst_adr                                                    "0x001A"
#define EMMC_PP_BIST_STS_inst                                                        0x001A
#define EMMC_PP_BIST_STS_bist_drf_start_pause_shift                                  (10)
#define EMMC_PP_BIST_STS_bist_drf_start_pause_mask                                   (0x00000400)
#define EMMC_PP_BIST_STS_bist_drf_start_pause(data)                                  (0x00000400&((data)<<10))
#define EMMC_PP_BIST_STS_bist_drf_start_pause_src(data)                              ((0x00000400&(data))>>10)
#define EMMC_PP_BIST_STS_get_bist_drf_start_pause(data)                              ((0x00000400&(data))>>10)
#define EMMC_PP_BIST_STS_bist_drf_fail_2_shift                                       (8)
#define EMMC_PP_BIST_STS_bist_drf_fail_2_mask                                        (0x00000100)
#define EMMC_PP_BIST_STS_bist_drf_fail_2(data)                                       (0x00000100&((data)<<8))
#define EMMC_PP_BIST_STS_bist_drf_fail_2_src(data)                                   ((0x00000100&(data))>>8)
#define EMMC_PP_BIST_STS_get_bist_drf_fail_2(data)                                   ((0x00000100&(data))>>8)
#define EMMC_PP_BIST_STS_bist_drf_fail_1_shift                                       (7)
#define EMMC_PP_BIST_STS_bist_drf_fail_1_mask                                        (0x00000080)
#define EMMC_PP_BIST_STS_bist_drf_fail_1(data)                                       (0x00000080&((data)<<7))
#define EMMC_PP_BIST_STS_bist_drf_fail_1_src(data)                                   ((0x00000080&(data))>>7)
#define EMMC_PP_BIST_STS_get_bist_drf_fail_1(data)                                   ((0x00000080&(data))>>7)
#define EMMC_PP_BIST_STS_bist_drf_fail_0_shift                                       (6)
#define EMMC_PP_BIST_STS_bist_drf_fail_0_mask                                        (0x00000040)
#define EMMC_PP_BIST_STS_bist_drf_fail_0(data)                                       (0x00000040&((data)<<6))
#define EMMC_PP_BIST_STS_bist_drf_fail_0_src(data)                                   ((0x00000040&(data))>>6)
#define EMMC_PP_BIST_STS_get_bist_drf_fail_0(data)                                   ((0x00000040&(data))>>6)
#define EMMC_PP_BIST_STS_bist_drf_done_shift                                         (5)
#define EMMC_PP_BIST_STS_bist_drf_done_mask                                          (0x00000020)
#define EMMC_PP_BIST_STS_bist_drf_done(data)                                         (0x00000020&((data)<<5))
#define EMMC_PP_BIST_STS_bist_drf_done_src(data)                                     ((0x00000020&(data))>>5)
#define EMMC_PP_BIST_STS_get_bist_drf_done(data)                                     ((0x00000020&(data))>>5)
#define EMMC_PP_BIST_STS_bist_2_fail_shift                                           (3)
#define EMMC_PP_BIST_STS_bist_2_fail_mask                                            (0x00000008)
#define EMMC_PP_BIST_STS_bist_2_fail(data)                                           (0x00000008&((data)<<3))
#define EMMC_PP_BIST_STS_bist_2_fail_src(data)                                       ((0x00000008&(data))>>3)
#define EMMC_PP_BIST_STS_get_bist_2_fail(data)                                       ((0x00000008&(data))>>3)
#define EMMC_PP_BIST_STS_bist_1_fail_shift                                           (2)
#define EMMC_PP_BIST_STS_bist_1_fail_mask                                            (0x00000004)
#define EMMC_PP_BIST_STS_bist_1_fail(data)                                           (0x00000004&((data)<<2))
#define EMMC_PP_BIST_STS_bist_1_fail_src(data)                                       ((0x00000004&(data))>>2)
#define EMMC_PP_BIST_STS_get_bist_1_fail(data)                                       ((0x00000004&(data))>>2)
#define EMMC_PP_BIST_STS_bist_0_fail_shift                                           (1)
#define EMMC_PP_BIST_STS_bist_0_fail_mask                                            (0x00000002)
#define EMMC_PP_BIST_STS_bist_0_fail(data)                                           (0x00000002&((data)<<1))
#define EMMC_PP_BIST_STS_bist_0_fail_src(data)                                       ((0x00000002&(data))>>1)
#define EMMC_PP_BIST_STS_get_bist_0_fail(data)                                       ((0x00000002&(data))>>1)
#define EMMC_PP_BIST_STS_bist_done_shift                                             (0)
#define EMMC_PP_BIST_STS_bist_done_mask                                              (0x00000001)
#define EMMC_PP_BIST_STS_bist_done(data)                                             (0x00000001&((data)<<0))
#define EMMC_PP_BIST_STS_bist_done_src(data)                                         ((0x00000001&(data))>>0)
#define EMMC_PP_BIST_STS_get_bist_done(data)                                         ((0x00000001&(data))>>0)


#define EMMC_IP_BIST_STS                                                             0x9801246c
#define EMMC_IP_BIST_STS_reg_addr                                                    "0x9801246C"
#define EMMC_IP_BIST_STS_reg                                                         0x9801246C
#define set_EMMC_IP_BIST_STS_reg(data)   (*((volatile unsigned int*) EMMC_IP_BIST_STS_reg)=data)
#define get_EMMC_IP_BIST_STS_reg   (*((volatile unsigned int*) EMMC_IP_BIST_STS_reg))
#define EMMC_IP_BIST_STS_inst_adr                                                    "0x001B"
#define EMMC_IP_BIST_STS_inst                                                        0x001B
#define EMMC_IP_BIST_STS_bist_drf_start_pause_shift                                  (10)
#define EMMC_IP_BIST_STS_bist_drf_start_pause_mask                                   (0x00000400)
#define EMMC_IP_BIST_STS_bist_drf_start_pause(data)                                  (0x00000400&((data)<<10))
#define EMMC_IP_BIST_STS_bist_drf_start_pause_src(data)                              ((0x00000400&(data))>>10)
#define EMMC_IP_BIST_STS_get_bist_drf_start_pause(data)                              ((0x00000400&(data))>>10)
#define EMMC_IP_BIST_STS_bist_drf_fail_1_shift                                       (7)
#define EMMC_IP_BIST_STS_bist_drf_fail_1_mask                                        (0x00000080)
#define EMMC_IP_BIST_STS_bist_drf_fail_1(data)                                       (0x00000080&((data)<<7))
#define EMMC_IP_BIST_STS_bist_drf_fail_1_src(data)                                   ((0x00000080&(data))>>7)
#define EMMC_IP_BIST_STS_get_bist_drf_fail_1(data)                                   ((0x00000080&(data))>>7)
#define EMMC_IP_BIST_STS_bist_drf_fail_0_shift                                       (6)
#define EMMC_IP_BIST_STS_bist_drf_fail_0_mask                                        (0x00000040)
#define EMMC_IP_BIST_STS_bist_drf_fail_0(data)                                       (0x00000040&((data)<<6))
#define EMMC_IP_BIST_STS_bist_drf_fail_0_src(data)                                   ((0x00000040&(data))>>6)
#define EMMC_IP_BIST_STS_get_bist_drf_fail_0(data)                                   ((0x00000040&(data))>>6)
#define EMMC_IP_BIST_STS_bist_drf_done_shift                                         (5)
#define EMMC_IP_BIST_STS_bist_drf_done_mask                                          (0x00000020)
#define EMMC_IP_BIST_STS_bist_drf_done(data)                                         (0x00000020&((data)<<5))
#define EMMC_IP_BIST_STS_bist_drf_done_src(data)                                     ((0x00000020&(data))>>5)
#define EMMC_IP_BIST_STS_get_bist_drf_done(data)                                     ((0x00000020&(data))>>5)
#define EMMC_IP_BIST_STS_bist_1_fail_shift                                           (2)
#define EMMC_IP_BIST_STS_bist_1_fail_mask                                            (0x00000004)
#define EMMC_IP_BIST_STS_bist_1_fail(data)                                           (0x00000004&((data)<<2))
#define EMMC_IP_BIST_STS_bist_1_fail_src(data)                                       ((0x00000004&(data))>>2)
#define EMMC_IP_BIST_STS_get_bist_1_fail(data)                                       ((0x00000004&(data))>>2)
#define EMMC_IP_BIST_STS_bist_0_fail_shift                                           (1)
#define EMMC_IP_BIST_STS_bist_0_fail_mask                                            (0x00000002)
#define EMMC_IP_BIST_STS_bist_0_fail(data)                                           (0x00000002&((data)<<1))
#define EMMC_IP_BIST_STS_bist_0_fail_src(data)                                       ((0x00000002&(data))>>1)
#define EMMC_IP_BIST_STS_get_bist_0_fail(data)                                       ((0x00000002&(data))>>1)
#define EMMC_IP_BIST_STS_bist_done_shift                                             (0)
#define EMMC_IP_BIST_STS_bist_done_mask                                              (0x00000001)
#define EMMC_IP_BIST_STS_bist_done(data)                                             (0x00000001&((data)<<0))
#define EMMC_IP_BIST_STS_bist_done_src(data)                                         ((0x00000001&(data))>>0)
#define EMMC_IP_BIST_STS_get_bist_done(data)                                         ((0x00000001&(data))>>0)


#define EMMC_IP_CTL                                                                  0x98012470
#define EMMC_IP_CTL_reg_addr                                                         "0x98012470"
#define EMMC_IP_CTL_reg                                                              0x98012470
#define set_EMMC_IP_CTL_reg(data)   (*((volatile unsigned int*) EMMC_IP_CTL_reg)=data)
#define get_EMMC_IP_CTL_reg   (*((volatile unsigned int*) EMMC_IP_CTL_reg))
#define EMMC_IP_CTL_inst_adr                                                         "0x001C"
#define EMMC_IP_CTL_inst                                                             0x001C
#define EMMC_IP_CTL_asic_crc_dbgo_sel_shift                                          (8)
#define EMMC_IP_CTL_asic_crc_dbgo_sel_mask                                           (0x0000FF00)
#define EMMC_IP_CTL_asic_crc_dbgo_sel(data)                                          (0x0000FF00&((data)<<8))
#define EMMC_IP_CTL_asic_crc_dbgo_sel_src(data)                                      ((0x0000FF00&(data))>>8)
#define EMMC_IP_CTL_get_asic_crc_dbgo_sel(data)                                      ((0x0000FF00&(data))>>8)
#define EMMC_IP_CTL_crc_dbgo_sel_shift                                               (3)
#define EMMC_IP_CTL_crc_dbgo_sel_mask                                                (0x00000078)
#define EMMC_IP_CTL_crc_dbgo_sel(data)                                               (0x00000078&((data)<<3))
#define EMMC_IP_CTL_crc_dbgo_sel_src(data)                                           ((0x00000078&(data))>>3)
#define EMMC_IP_CTL_get_crc_dbgo_sel(data)                                           ((0x00000078&(data))>>3)
#define EMMC_IP_CTL_ip_ea_flash_shift                                                (2)
#define EMMC_IP_CTL_ip_ea_flash_mask                                                 (0x00000004)
#define EMMC_IP_CTL_ip_ea_flash(data)                                                (0x00000004&((data)<<2))
#define EMMC_IP_CTL_ip_ea_flash_src(data)                                            ((0x00000004&(data))>>2)
#define EMMC_IP_CTL_get_ip_ea_flash(data)                                            ((0x00000004&(data))>>2)
#define EMMC_IP_CTL_crc_clk_disable_trig_shift                                       (1)
#define EMMC_IP_CTL_crc_clk_disable_trig_mask                                        (0x00000002)
#define EMMC_IP_CTL_crc_clk_disable_trig(data)                                       (0x00000002&((data)<<1))
#define EMMC_IP_CTL_crc_clk_disable_trig_src(data)                                   ((0x00000002&(data))>>1)
#define EMMC_IP_CTL_get_crc_clk_disable_trig(data)                                   ((0x00000002&(data))>>1)
#define EMMC_IP_CTL_mcu_time_1_us_shift                                              (0)
#define EMMC_IP_CTL_mcu_time_1_us_mask                                               (0x00000001)
#define EMMC_IP_CTL_mcu_time_1_us(data)                                              (0x00000001&((data)<<0))
#define EMMC_IP_CTL_mcu_time_1_us_src(data)                                          ((0x00000001&(data))>>0)
#define EMMC_IP_CTL_get_mcu_time_1_us(data)                                          ((0x00000001&(data))>>0)


#define EMMC_PAD_CTL                                                                 0x98012474
#define EMMC_PAD_CTL_reg_addr                                                        "0x98012474"
#define EMMC_PAD_CTL_reg                                                             0x98012474
#define set_EMMC_PAD_CTL_reg(data)   (*((volatile unsigned int*) EMMC_PAD_CTL_reg)=data)
#define get_EMMC_PAD_CTL_reg   (*((volatile unsigned int*) EMMC_PAD_CTL_reg))
#define EMMC_PAD_CTL_inst_adr                                                        "0x001D"
#define EMMC_PAD_CTL_inst                                                            0x001D
#define EMMC_PAD_CTL_tune3318_shift                                                  (0)
#define EMMC_PAD_CTL_tune3318_mask                                                   (0x00000001)
#define EMMC_PAD_CTL_tune3318(data)                                                  (0x00000001&((data)<<0))
#define EMMC_PAD_CTL_tune3318_src(data)                                              ((0x00000001&(data))>>0)
#define EMMC_PAD_CTL_get_tune3318(data)                                              ((0x00000001&(data))>>0)


#define EMMC_CKGEN_CTL                                                               0x98012478
#define EMMC_CKGEN_CTL_reg_addr                                                      "0x98012478"
#define EMMC_CKGEN_CTL_reg                                                           0x98012478
#define set_EMMC_CKGEN_CTL_reg(data)   (*((volatile unsigned int*) EMMC_CKGEN_CTL_reg)=data)
#define get_EMMC_CKGEN_CTL_reg   (*((volatile unsigned int*) EMMC_CKGEN_CTL_reg))
#define EMMC_CKGEN_CTL_inst_adr                                                      "0x001E"
#define EMMC_CKGEN_CTL_inst                                                          0x001E
#define EMMC_CKGEN_CTL_sd30_sample_change_shift                                      (18)
#define EMMC_CKGEN_CTL_sd30_sample_change_mask                                       (0x00040000)
#define EMMC_CKGEN_CTL_sd30_sample_change(data)                                      (0x00040000&((data)<<18))
#define EMMC_CKGEN_CTL_sd30_sample_change_src(data)                                  ((0x00040000&(data))>>18)
#define EMMC_CKGEN_CTL_get_sd30_sample_change(data)                                  ((0x00040000&(data))>>18)
#define EMMC_CKGEN_CTL_sd30_push_change_shift                                        (17)
#define EMMC_CKGEN_CTL_sd30_push_change_mask                                         (0x00020000)
#define EMMC_CKGEN_CTL_sd30_push_change(data)                                        (0x00020000&((data)<<17))
#define EMMC_CKGEN_CTL_sd30_push_change_src(data)                                    ((0x00020000&(data))>>17)
#define EMMC_CKGEN_CTL_get_sd30_push_change(data)                                    ((0x00020000&(data))>>17)
#define EMMC_CKGEN_CTL_crc_clk_change_shift                                          (16)
#define EMMC_CKGEN_CTL_crc_clk_change_mask                                           (0x00010000)
#define EMMC_CKGEN_CTL_crc_clk_change(data)                                          (0x00010000&((data)<<16))
#define EMMC_CKGEN_CTL_crc_clk_change_src(data)                                      ((0x00010000&(data))>>16)
#define EMMC_CKGEN_CTL_get_crc_clk_change(data)                                      ((0x00010000&(data))>>16)
#define EMMC_CKGEN_CTL_sd30_sample_clk_src_shift                                     (12)
#define EMMC_CKGEN_CTL_sd30_sample_clk_src_mask                                      (0x00003000)
#define EMMC_CKGEN_CTL_sd30_sample_clk_src(data)                                     (0x00003000&((data)<<12))
#define EMMC_CKGEN_CTL_sd30_sample_clk_src_src(data)                                 ((0x00003000&(data))>>12)
#define EMMC_CKGEN_CTL_get_sd30_sample_clk_src(data)                                 ((0x00003000&(data))>>12)
#define EMMC_CKGEN_CTL_sd30_push_clk_src_shift                                       (8)
#define EMMC_CKGEN_CTL_sd30_push_clk_src_mask                                        (0x00000300)
#define EMMC_CKGEN_CTL_sd30_push_clk_src(data)                                       (0x00000300&((data)<<8))
#define EMMC_CKGEN_CTL_sd30_push_clk_src_src(data)                                   ((0x00000300&(data))>>8)
#define EMMC_CKGEN_CTL_get_sd30_push_clk_src(data)                                   ((0x00000300&(data))>>8)
#define EMMC_CKGEN_CTL_crc_clk_src_shift                                             (4)
#define EMMC_CKGEN_CTL_crc_clk_src_mask                                              (0x00000030)
#define EMMC_CKGEN_CTL_crc_clk_src(data)                                             (0x00000030&((data)<<4))
#define EMMC_CKGEN_CTL_crc_clk_src_src(data)                                         ((0x00000030&(data))>>4)
#define EMMC_CKGEN_CTL_get_crc_clk_src(data)                                         ((0x00000030&(data))>>4)
#define EMMC_CKGEN_CTL_clk_div_shift                                                 (0)
#define EMMC_CKGEN_CTL_clk_div_mask                                                  (0x00000007)
#define EMMC_CKGEN_CTL_clk_div(data)                                                 (0x00000007&((data)<<0))
#define EMMC_CKGEN_CTL_clk_div_src(data)                                             ((0x00000007&(data))>>0)
#define EMMC_CKGEN_CTL_get_clk_div(data)                                             ((0x00000007&(data))>>0)


#define EMMC_CPU_ACC_CTRL                                                            0x98012480
#define EMMC_CPU_ACC_CTRL_reg_addr                                                   "0x98012480"
#define EMMC_CPU_ACC_CTRL_reg                                                        0x98012480
#define set_EMMC_CPU_ACC_CTRL_reg(data)   (*((volatile unsigned int*) EMMC_CPU_ACC_CTRL_reg)=data)
#define get_EMMC_CPU_ACC_CTRL_reg   (*((volatile unsigned int*) EMMC_CPU_ACC_CTRL_reg))
#define EMMC_CPU_ACC_CTRL_inst_adr                                                   "0x0020"
#define EMMC_CPU_ACC_CTRL_inst                                                       0x0020
#define EMMC_CPU_ACC_CTRL_buf_full_shift                                             (2)
#define EMMC_CPU_ACC_CTRL_buf_full_mask                                              (0x00000004)
#define EMMC_CPU_ACC_CTRL_buf_full(data)                                             (0x00000004&((data)<<2))
#define EMMC_CPU_ACC_CTRL_buf_full_src(data)                                         ((0x00000004&(data))>>2)
#define EMMC_CPU_ACC_CTRL_get_buf_full(data)                                         ((0x00000004&(data))>>2)
#define EMMC_CPU_ACC_CTRL_buf_sw_shift                                               (1)
#define EMMC_CPU_ACC_CTRL_buf_sw_mask                                                (0x00000002)
#define EMMC_CPU_ACC_CTRL_buf_sw(data)                                               (0x00000002&((data)<<1))
#define EMMC_CPU_ACC_CTRL_buf_sw_src(data)                                           ((0x00000002&(data))>>1)
#define EMMC_CPU_ACC_CTRL_get_buf_sw(data)                                           ((0x00000002&(data))>>1)
#define EMMC_CPU_ACC_CTRL_cpu_mode_shift                                             (0)
#define EMMC_CPU_ACC_CTRL_cpu_mode_mask                                              (0x00000001)
#define EMMC_CPU_ACC_CTRL_cpu_mode(data)                                             (0x00000001&((data)<<0))
#define EMMC_CPU_ACC_CTRL_cpu_mode_src(data)                                         ((0x00000001&(data))>>0)
#define EMMC_CPU_ACC_CTRL_get_cpu_mode(data)                                         ((0x00000001&(data))>>0)


#define EMMC_CARD_SIG                                                                0x98012484
#define EMMC_CARD_SIG_reg_addr                                                       "0x98012484"
#define EMMC_CARD_SIG_reg                                                            0x98012484
#define set_EMMC_CARD_SIG_reg(data)   (*((volatile unsigned int*) EMMC_CARD_SIG_reg)=data)
#define get_EMMC_CARD_SIG_reg   (*((volatile unsigned int*) EMMC_CARD_SIG_reg))
#define EMMC_CARD_SIG_inst_adr                                                       "0x0021"
#define EMMC_CARD_SIG_inst                                                           0x0021
#define EMMC_CARD_SIG_EMMC_RST_n_shift                                               (0)
#define EMMC_CARD_SIG_EMMC_RST_n_mask                                                (0x00000001)
#define EMMC_CARD_SIG_EMMC_RST_n(data)                                               (0x00000001&((data)<<0))
#define EMMC_CARD_SIG_EMMC_RST_n_src(data)                                           ((0x00000001&(data))>>0)
#define EMMC_CARD_SIG_get_EMMC_RST_n(data)                                           ((0x00000001&(data))>>0)


#define EMMC_CARD_DRV                                                                0x98012490
#define EMMC_CARD_DRV_reg_addr                                                       "0x98012490"
#define EMMC_CARD_DRV_reg                                                            0x98012490
#define set_EMMC_CARD_DRV_reg(data)   (*((volatile unsigned int*) EMMC_CARD_DRV_reg)=data)
#define get_EMMC_CARD_DRV_reg   (*((volatile unsigned int*) EMMC_CARD_DRV_reg))
#define EMMC_CARD_DRV_inst_adr                                                       "0x0024"
#define EMMC_CARD_DRV_inst                                                           0x0024
#define EMMC_CARD_DRV_EMMC_card_drive_shift                                          (24)
#define EMMC_CARD_DRV_EMMC_card_drive_mask                                           (0xFF000000)
#define EMMC_CARD_DRV_EMMC_card_drive(data)                                          (0xFF000000&((data)<<24))
#define EMMC_CARD_DRV_EMMC_card_drive_src(data)                                      ((0xFF000000&(data))>>24)
#define EMMC_CARD_DRV_get_EMMC_card_drive(data)                                      ((0xFF000000&(data))>>24)
#define EMMC_CARD_DRV_EMMC_dat_n_drive_shift                                         (20)
#define EMMC_CARD_DRV_EMMC_dat_n_drive_mask                                          (0x00F00000)
#define EMMC_CARD_DRV_EMMC_dat_n_drive(data)                                         (0x00F00000&((data)<<20))
#define EMMC_CARD_DRV_EMMC_dat_n_drive_src(data)                                     ((0x00F00000&(data))>>20)
#define EMMC_CARD_DRV_get_EMMC_dat_n_drive(data)                                     ((0x00F00000&(data))>>20)
#define EMMC_CARD_DRV_EMMC_dat_p_drive_shift                                         (16)
#define EMMC_CARD_DRV_EMMC_dat_p_drive_mask                                          (0x000F0000)
#define EMMC_CARD_DRV_EMMC_dat_p_drive(data)                                         (0x000F0000&((data)<<16))
#define EMMC_CARD_DRV_EMMC_dat_p_drive_src(data)                                     ((0x000F0000&(data))>>16)
#define EMMC_CARD_DRV_get_EMMC_dat_p_drive(data)                                     ((0x000F0000&(data))>>16)
#define EMMC_CARD_DRV_EMMC_cmd_n_drive_shift                                         (12)
#define EMMC_CARD_DRV_EMMC_cmd_n_drive_mask                                          (0x0000F000)
#define EMMC_CARD_DRV_EMMC_cmd_n_drive(data)                                         (0x0000F000&((data)<<12))
#define EMMC_CARD_DRV_EMMC_cmd_n_drive_src(data)                                     ((0x0000F000&(data))>>12)
#define EMMC_CARD_DRV_get_EMMC_cmd_n_drive(data)                                     ((0x0000F000&(data))>>12)
#define EMMC_CARD_DRV_EMMC_cmd_p_drive_shift                                         (8)
#define EMMC_CARD_DRV_EMMC_cmd_p_drive_mask                                          (0x00000F00)
#define EMMC_CARD_DRV_EMMC_cmd_p_drive(data)                                         (0x00000F00&((data)<<8))
#define EMMC_CARD_DRV_EMMC_cmd_p_drive_src(data)                                     ((0x00000F00&(data))>>8)
#define EMMC_CARD_DRV_get_EMMC_cmd_p_drive(data)                                     ((0x00000F00&(data))>>8)
#define EMMC_CARD_DRV_EMMC_clk_n_drive_shift                                         (4)
#define EMMC_CARD_DRV_EMMC_clk_n_drive_mask                                          (0x000000F0)
#define EMMC_CARD_DRV_EMMC_clk_n_drive(data)                                         (0x000000F0&((data)<<4))
#define EMMC_CARD_DRV_EMMC_clk_n_drive_src(data)                                     ((0x000000F0&(data))>>4)
#define EMMC_CARD_DRV_get_EMMC_clk_n_drive(data)                                     ((0x000000F0&(data))>>4)
#define EMMC_CARD_DRV_EMMC_clk_p_drive_shift                                         (0)
#define EMMC_CARD_DRV_EMMC_clk_p_drive_mask                                          (0x0000000F)
#define EMMC_CARD_DRV_EMMC_clk_p_drive(data)                                         (0x0000000F&((data)<<0))
#define EMMC_CARD_DRV_EMMC_clk_p_drive_src(data)                                     ((0x0000000F&(data))>>0)
#define EMMC_CARD_DRV_get_EMMC_clk_p_drive(data)                                     ((0x0000000F&(data))>>0)

/* Mark out first to prevent compile error
#define EMMC_CARD_DRV                                                                0x98012494
#define EMMC_CARD_DRV_reg_addr                                                       "0x98012494"
#define EMMC_CARD_DRV_reg                                                            0x98012494
#define set_EMMC_CARD_DRV_reg(data)   (*((volatile unsigned int*) EMMC_CARD_DRV_reg)=data)
#define get_EMMC_CARD_DRV_reg   (*((volatile unsigned int*) EMMC_CARD_DRV_reg))
#define EMMC_CARD_DRV_inst_adr                                                       "0x0025"
#define EMMC_CARD_DRV_inst                                                           0x0025
#define EMMC_CARD_DRV_EMMC_sd_pupdc_shift                                            (6)
#define EMMC_CARD_DRV_EMMC_sd_pupdc_mask                                             (0x000001C0)
#define EMMC_CARD_DRV_EMMC_sd_pupdc(data)                                            (0x000001C0&((data)<<6))
#define EMMC_CARD_DRV_EMMC_sd_pupdc_src(data)                                        ((0x000001C0&(data))>>6)
#define EMMC_CARD_DRV_get_EMMC_sd_pupdc(data)                                        ((0x000001C0&(data))>>6)
#define EMMC_CARD_DRV_EMMC_card_output_en_shift                                      (0)
#define EMMC_CARD_DRV_EMMC_card_output_en_mask                                       (0x0000003F)
#define EMMC_CARD_DRV_EMMC_card_output_en(data)                                      (0x0000003F&((data)<<0))
#define EMMC_CARD_DRV_EMMC_card_output_en_src(data)                                  ((0x0000003F&(data))>>0)
#define EMMC_CARD_DRV_get_EMMC_card_output_en(data)                                  ((0x0000003F&(data))>>0)
*/

#define EMMC_DQS_CTRL1                                                               0x98012498
#define EMMC_DQS_CTRL1_reg_addr                                                      "0x98012498"
#define EMMC_DQS_CTRL1_reg                                                           0x98012498
#define set_EMMC_DQS_CTRL1_reg(data)   (*((volatile unsigned int*) EMMC_DQS_CTRL1_reg)=data)
#define get_EMMC_DQS_CTRL1_reg   (*((volatile unsigned int*) EMMC_DQS_CTRL1_reg))
#define EMMC_DQS_CTRL1_inst_adr                                                      "0x0026"
#define EMMC_DQS_CTRL1_inst                                                          0x0026
#define EMMC_DQS_CTRL1_fw_set_shift                                                  (7)
#define EMMC_DQS_CTRL1_fw_set_mask                                                   (0x00000080)
#define EMMC_DQS_CTRL1_fw_set(data)                                                  (0x00000080&((data)<<7))
#define EMMC_DQS_CTRL1_fw_set_src(data)                                              ((0x00000080&(data))>>7)
#define EMMC_DQS_CTRL1_get_fw_set(data)                                              ((0x00000080&(data))>>7)
#define EMMC_DQS_CTRL1_fw_dlyn_shift                                                 (0)
#define EMMC_DQS_CTRL1_fw_dlyn_mask                                                  (0x0000007F)
#define EMMC_DQS_CTRL1_fw_dlyn(data)                                                 (0x0000007F&((data)<<0))
#define EMMC_DQS_CTRL1_fw_dlyn_src(data)                                             ((0x0000007F&(data))>>0)
#define EMMC_DQS_CTRL1_get_fw_dlyn(data)                                             ((0x0000007F&(data))>>0)


#define EMMC_DQS_CTRL2                                                               0x9801249c
#define EMMC_DQS_CTRL2_reg_addr                                                      "0x9801249C"
#define EMMC_DQS_CTRL2_reg                                                           0x9801249C
#define set_EMMC_DQS_CTRL2_reg(data)   (*((volatile unsigned int*) EMMC_DQS_CTRL2_reg)=data)
#define get_EMMC_DQS_CTRL2_reg   (*((volatile unsigned int*) EMMC_DQS_CTRL2_reg))
#define EMMC_DQS_CTRL2_inst_adr                                                      "0x0027"
#define EMMC_DQS_CTRL2_inst                                                          0x0027
#define EMMC_DQS_CTRL2_auto_cal_shift                                                (7)
#define EMMC_DQS_CTRL2_auto_cal_mask                                                 (0x00000080)
#define EMMC_DQS_CTRL2_auto_cal(data)                                                (0x00000080&((data)<<7))
#define EMMC_DQS_CTRL2_auto_cal_src(data)                                            ((0x00000080&(data))>>7)
#define EMMC_DQS_CTRL2_get_auto_cal(data)                                            ((0x00000080&(data))>>7)
#define EMMC_DQS_CTRL2_pos_trig_sel_shift                                            (3)
#define EMMC_DQS_CTRL2_pos_trig_sel_mask                                             (0x00000038)
#define EMMC_DQS_CTRL2_pos_trig_sel(data)                                            (0x00000038&((data)<<3))
#define EMMC_DQS_CTRL2_pos_trig_sel_src(data)                                        ((0x00000038&(data))>>3)
#define EMMC_DQS_CTRL2_get_pos_trig_sel(data)                                        ((0x00000038&(data))>>3)
#define EMMC_DQS_CTRL2_pre_trig_sel_shift                                            (0)
#define EMMC_DQS_CTRL2_pre_trig_sel_mask                                             (0x00000007)
#define EMMC_DQS_CTRL2_pre_trig_sel(data)                                            (0x00000007&((data)<<0))
#define EMMC_DQS_CTRL2_pre_trig_sel_src(data)                                        ((0x00000007&(data))>>0)
#define EMMC_DQS_CTRL2_get_pre_trig_sel(data)                                        ((0x00000007&(data))>>0)


#define EMMC_IP_DESC0                                                                0x980124a0
#define EMMC_IP_DESC0_reg_addr                                                       "0x980124A0"
#define EMMC_IP_DESC0_reg                                                            0x980124A0
#define set_EMMC_IP_DESC0_reg(data)   (*((volatile unsigned int*) EMMC_IP_DESC0_reg)=data)
#define get_EMMC_IP_DESC0_reg   (*((volatile unsigned int*) EMMC_IP_DESC0_reg))
#define EMMC_IP_DESC0_inst_adr                                                       "0x0028"
#define EMMC_IP_DESC0_inst                                                           0x0028
#define EMMC_IP_DESC0_Desc0_shift                                                    (0)
#define EMMC_IP_DESC0_Desc0_mask                                                     (0xFFFFFFFF)
#define EMMC_IP_DESC0_Desc0(data)                                                    (0xFFFFFFFF&((data)<<0))
#define EMMC_IP_DESC0_Desc0_src(data)                                                ((0xFFFFFFFF&(data))>>0)
#define EMMC_IP_DESC0_get_Desc0(data)                                                ((0xFFFFFFFF&(data))>>0)


#define EMMC_IP_DESC1                                                                0x980124a4
#define EMMC_IP_DESC1_reg_addr                                                       "0x980124A4"
#define EMMC_IP_DESC1_reg                                                            0x980124A4
#define set_EMMC_IP_DESC1_reg(data)   (*((volatile unsigned int*) EMMC_IP_DESC1_reg)=data)
#define get_EMMC_IP_DESC1_reg   (*((volatile unsigned int*) EMMC_IP_DESC1_reg))
#define EMMC_IP_DESC1_inst_adr                                                       "0x0029"
#define EMMC_IP_DESC1_inst                                                           0x0029
#define EMMC_IP_DESC1_Desc1_shift                                                    (0)
#define EMMC_IP_DESC1_Desc1_mask                                                     (0xFFFFFFFF)
#define EMMC_IP_DESC1_Desc1(data)                                                    (0xFFFFFFFF&((data)<<0))
#define EMMC_IP_DESC1_Desc1_src(data)                                                ((0xFFFFFFFF&(data))>>0)
#define EMMC_IP_DESC1_get_Desc1(data)                                                ((0xFFFFFFFF&(data))>>0)


#define EMMC_IP_DESC2                                                                0x980124a8
#define EMMC_IP_DESC2_reg_addr                                                       "0x980124A8"
#define EMMC_IP_DESC2_reg                                                            0x980124A8
#define set_EMMC_IP_DESC2_reg(data)   (*((volatile unsigned int*) EMMC_IP_DESC2_reg)=data)
#define get_EMMC_IP_DESC2_reg   (*((volatile unsigned int*) EMMC_IP_DESC2_reg))
#define EMMC_IP_DESC2_inst_adr                                                       "0x002A"
#define EMMC_IP_DESC2_inst                                                           0x002A
#define EMMC_IP_DESC2_Desc2_shift                                                    (0)
#define EMMC_IP_DESC2_Desc2_mask                                                     (0xFFFFFFFF)
#define EMMC_IP_DESC2_Desc2(data)                                                    (0xFFFFFFFF&((data)<<0))
#define EMMC_IP_DESC2_Desc2_src(data)                                                ((0xFFFFFFFF&(data))>>0)
#define EMMC_IP_DESC2_get_Desc2(data)                                                ((0xFFFFFFFF&(data))>>0)


#define EMMC_IP_DESC3                                                                0x980124ac
#define EMMC_IP_DESC3_reg_addr                                                       "0x980124AC"
#define EMMC_IP_DESC3_reg                                                            0x980124AC
#define set_EMMC_IP_DESC3_reg(data)   (*((volatile unsigned int*) EMMC_IP_DESC3_reg)=data)
#define get_EMMC_IP_DESC3_reg   (*((volatile unsigned int*) EMMC_IP_DESC3_reg))
#define EMMC_IP_DESC3_inst_adr                                                       "0x002B"
#define EMMC_IP_DESC3_inst                                                           0x002B
#define EMMC_IP_DESC3_Desc3_shift                                                    (0)
#define EMMC_IP_DESC3_Desc3_mask                                                     (0xFFFFFFFF)
#define EMMC_IP_DESC3_Desc3(data)                                                    (0xFFFFFFFF&((data)<<0))
#define EMMC_IP_DESC3_Desc3_src(data)                                                ((0xFFFFFFFF&(data))>>0)
#define EMMC_IP_DESC3_get_Desc3(data)                                                ((0xFFFFFFFF&(data))>>0)


#define EMMC_MAIN2_DBG                                                               0x980124b0
#define EMMC_MAIN2_DBG_reg_addr                                                      "0x980124B0"
#define EMMC_MAIN2_DBG_reg                                                           0x980124B0
#define set_EMMC_MAIN2_DBG_reg(data)   (*((volatile unsigned int*) EMMC_MAIN2_DBG_reg)=data)
#define get_EMMC_MAIN2_DBG_reg   (*((volatile unsigned int*) EMMC_MAIN2_DBG_reg))
#define EMMC_MAIN2_DBG_inst_adr                                                      "0x002C"
#define EMMC_MAIN2_DBG_inst                                                          0x002C
#define EMMC_MAIN2_DBG_main2_dbg_en_shift                                            (2)
#define EMMC_MAIN2_DBG_main2_dbg_en_mask                                             (0x00000004)
#define EMMC_MAIN2_DBG_main2_dbg_en(data)                                            (0x00000004&((data)<<2))
#define EMMC_MAIN2_DBG_main2_dbg_en_src(data)                                        ((0x00000004&(data))>>2)
#define EMMC_MAIN2_DBG_get_main2_dbg_en(data)                                        ((0x00000004&(data))>>2)
#define EMMC_MAIN2_DBG_main2_dbg_sel_shift                                           (0)
#define EMMC_MAIN2_DBG_main2_dbg_sel_mask                                            (0x00000003)
#define EMMC_MAIN2_DBG_main2_dbg_sel(data)                                           (0x00000003&((data)<<0))
#define EMMC_MAIN2_DBG_main2_dbg_sel_src(data)                                       ((0x00000003&(data))>>0)
#define EMMC_MAIN2_DBG_get_main2_dbg_sel(data)                                       ((0x00000003&(data))>>0)


#define EMMC_TM_SENSOR_CTRL0                                                         0x980124b4
#define EMMC_TM_SENSOR_CTRL0_reg_addr                                                "0x980124B4"
#define EMMC_TM_SENSOR_CTRL0_reg                                                     0x980124B4
#define set_EMMC_TM_SENSOR_CTRL0_reg(data)   (*((volatile unsigned int*) EMMC_TM_SENSOR_CTRL0_reg)=data)
#define get_EMMC_TM_SENSOR_CTRL0_reg   (*((volatile unsigned int*) EMMC_TM_SENSOR_CTRL0_reg))
#define EMMC_TM_SENSOR_CTRL0_inst_adr                                                "0x002D"
#define EMMC_TM_SENSOR_CTRL0_inst                                                    0x002D
#define EMMC_TM_SENSOR_CTRL0_reg_a_shift                                             (0)
#define EMMC_TM_SENSOR_CTRL0_reg_a_mask                                              (0x1FFFFFFF)
#define EMMC_TM_SENSOR_CTRL0_reg_a(data)                                             (0x1FFFFFFF&((data)<<0))
#define EMMC_TM_SENSOR_CTRL0_reg_a_src(data)                                         ((0x1FFFFFFF&(data))>>0)
#define EMMC_TM_SENSOR_CTRL0_get_reg_a(data)                                         ((0x1FFFFFFF&(data))>>0)


#define EMMC_TM_SENSOR_CTRL1                                                         0x980124b8
#define EMMC_TM_SENSOR_CTRL1_reg_addr                                                "0x980124B8"
#define EMMC_TM_SENSOR_CTRL1_reg                                                     0x980124B8
#define set_EMMC_TM_SENSOR_CTRL1_reg(data)   (*((volatile unsigned int*) EMMC_TM_SENSOR_CTRL1_reg)=data)
#define get_EMMC_TM_SENSOR_CTRL1_reg   (*((volatile unsigned int*) EMMC_TM_SENSOR_CTRL1_reg))
#define EMMC_TM_SENSOR_CTRL1_inst_adr                                                "0x002E"
#define EMMC_TM_SENSOR_CTRL1_inst                                                    0x002E
#define EMMC_TM_SENSOR_CTRL1_reg_chopen_shift                                        (28)
#define EMMC_TM_SENSOR_CTRL1_reg_chopen_mask                                         (0x10000000)
#define EMMC_TM_SENSOR_CTRL1_reg_chopen(data)                                        (0x10000000&((data)<<28))
#define EMMC_TM_SENSOR_CTRL1_reg_chopen_src(data)                                    ((0x10000000&(data))>>28)
#define EMMC_TM_SENSOR_CTRL1_get_reg_chopen(data)                                    ((0x10000000&(data))>>28)
#define EMMC_TM_SENSOR_CTRL1_reg_cal_en_shift                                        (27)
#define EMMC_TM_SENSOR_CTRL1_reg_cal_en_mask                                         (0x08000000)
#define EMMC_TM_SENSOR_CTRL1_reg_cal_en(data)                                        (0x08000000&((data)<<27))
#define EMMC_TM_SENSOR_CTRL1_reg_cal_en_src(data)                                    ((0x08000000&(data))>>27)
#define EMMC_TM_SENSOR_CTRL1_get_reg_cal_en(data)                                    ((0x08000000&(data))>>27)
#define EMMC_TM_SENSOR_CTRL1_reg_biasdem_sel_shift                                   (26)
#define EMMC_TM_SENSOR_CTRL1_reg_biasdem_sel_mask                                    (0x04000000)
#define EMMC_TM_SENSOR_CTRL1_reg_biasdem_sel(data)                                   (0x04000000&((data)<<26))
#define EMMC_TM_SENSOR_CTRL1_reg_biasdem_sel_src(data)                               ((0x04000000&(data))>>26)
#define EMMC_TM_SENSOR_CTRL1_get_reg_biasdem_sel(data)                               ((0x04000000&(data))>>26)
#define EMMC_TM_SENSOR_CTRL1_reg_biaschop_shift                                      (25)
#define EMMC_TM_SENSOR_CTRL1_reg_biaschop_mask                                       (0x02000000)
#define EMMC_TM_SENSOR_CTRL1_reg_biaschop(data)                                      (0x02000000&((data)<<25))
#define EMMC_TM_SENSOR_CTRL1_reg_biaschop_src(data)                                  ((0x02000000&(data))>>25)
#define EMMC_TM_SENSOR_CTRL1_get_reg_biaschop(data)                                  ((0x02000000&(data))>>25)
#define EMMC_TM_SENSOR_CTRL1_reg_adccksel_shift                                      (22)
#define EMMC_TM_SENSOR_CTRL1_reg_adccksel_mask                                       (0x01C00000)
#define EMMC_TM_SENSOR_CTRL1_reg_adccksel(data)                                      (0x01C00000&((data)<<22))
#define EMMC_TM_SENSOR_CTRL1_reg_adccksel_src(data)                                  ((0x01C00000&(data))>>22)
#define EMMC_TM_SENSOR_CTRL1_get_reg_adccksel(data)                                  ((0x01C00000&(data))>>22)
#define EMMC_TM_SENSOR_CTRL1_reg_b_shift                                             (0)
#define EMMC_TM_SENSOR_CTRL1_reg_b_mask                                              (0x003FFFFF)
#define EMMC_TM_SENSOR_CTRL1_reg_b(data)                                             (0x003FFFFF&((data)<<0))
#define EMMC_TM_SENSOR_CTRL1_reg_b_src(data)                                         ((0x003FFFFF&(data))>>0)
#define EMMC_TM_SENSOR_CTRL1_get_reg_b(data)                                         ((0x003FFFFF&(data))>>0)


#define EMMC_TM_SENSOR_CTRL2                                                         0x980124bc
#define EMMC_TM_SENSOR_CTRL2_reg_addr                                                "0x980124BC"
#define EMMC_TM_SENSOR_CTRL2_reg                                                     0x980124BC
#define set_EMMC_TM_SENSOR_CTRL2_reg(data)   (*((volatile unsigned int*) EMMC_TM_SENSOR_CTRL2_reg)=data)
#define get_EMMC_TM_SENSOR_CTRL2_reg   (*((volatile unsigned int*) EMMC_TM_SENSOR_CTRL2_reg))
#define EMMC_TM_SENSOR_CTRL2_inst_adr                                                "0x002F"
#define EMMC_TM_SENSOR_CTRL2_inst                                                    0x002F
#define EMMC_TM_SENSOR_CTRL2_reg_vbe_biassel_shift                                   (23)
#define EMMC_TM_SENSOR_CTRL2_reg_vbe_biassel_mask                                    (0x01800000)
#define EMMC_TM_SENSOR_CTRL2_reg_vbe_biassel(data)                                   (0x01800000&((data)<<23))
#define EMMC_TM_SENSOR_CTRL2_reg_vbe_biassel_src(data)                               ((0x01800000&(data))>>23)
#define EMMC_TM_SENSOR_CTRL2_get_reg_vbe_biassel(data)                               ((0x01800000&(data))>>23)
#define EMMC_TM_SENSOR_CTRL2_reg_sdm_test_en_shift                                   (22)
#define EMMC_TM_SENSOR_CTRL2_reg_sdm_test_en_mask                                    (0x00400000)
#define EMMC_TM_SENSOR_CTRL2_reg_sdm_test_en(data)                                   (0x00400000&((data)<<22))
#define EMMC_TM_SENSOR_CTRL2_reg_sdm_test_en_src(data)                               ((0x00400000&(data))>>22)
#define EMMC_TM_SENSOR_CTRL2_get_reg_sdm_test_en(data)                               ((0x00400000&(data))>>22)
#define EMMC_TM_SENSOR_CTRL2_reg_sdm_test_shift                                      (21)
#define EMMC_TM_SENSOR_CTRL2_reg_sdm_test_mask                                       (0x00200000)
#define EMMC_TM_SENSOR_CTRL2_reg_sdm_test(data)                                      (0x00200000&((data)<<21))
#define EMMC_TM_SENSOR_CTRL2_reg_sdm_test_src(data)                                  ((0x00200000&(data))>>21)
#define EMMC_TM_SENSOR_CTRL2_get_reg_sdm_test(data)                                  ((0x00200000&(data))>>21)
#define EMMC_TM_SENSOR_CTRL2_reg_rstb_shift                                          (20)
#define EMMC_TM_SENSOR_CTRL2_reg_rstb_mask                                           (0x00100000)
#define EMMC_TM_SENSOR_CTRL2_reg_rstb(data)                                          (0x00100000&((data)<<20))
#define EMMC_TM_SENSOR_CTRL2_reg_rstb_src(data)                                      ((0x00100000&(data))>>20)
#define EMMC_TM_SENSOR_CTRL2_get_reg_rstb(data)                                      ((0x00100000&(data))>>20)
#define EMMC_TM_SENSOR_CTRL2_reg_resol_shift                                         (18)
#define EMMC_TM_SENSOR_CTRL2_reg_resol_mask                                          (0x000C0000)
#define EMMC_TM_SENSOR_CTRL2_reg_resol(data)                                         (0x000C0000&((data)<<18))
#define EMMC_TM_SENSOR_CTRL2_reg_resol_src(data)                                     ((0x000C0000&(data))>>18)
#define EMMC_TM_SENSOR_CTRL2_get_reg_resol(data)                                     ((0x000C0000&(data))>>18)
#define EMMC_TM_SENSOR_CTRL2_reg_ppow_shift                                          (17)
#define EMMC_TM_SENSOR_CTRL2_reg_ppow_mask                                           (0x00020000)
#define EMMC_TM_SENSOR_CTRL2_reg_ppow(data)                                          (0x00020000&((data)<<17))
#define EMMC_TM_SENSOR_CTRL2_reg_ppow_src(data)                                      ((0x00020000&(data))>>17)
#define EMMC_TM_SENSOR_CTRL2_get_reg_ppow(data)                                      ((0x00020000&(data))>>17)
#define EMMC_TM_SENSOR_CTRL2_reg_osccursel_shift                                     (15)
#define EMMC_TM_SENSOR_CTRL2_reg_osccursel_mask                                      (0x00018000)
#define EMMC_TM_SENSOR_CTRL2_reg_osccursel(data)                                     (0x00018000&((data)<<15))
#define EMMC_TM_SENSOR_CTRL2_reg_osccursel_src(data)                                 ((0x00018000&(data))>>15)
#define EMMC_TM_SENSOR_CTRL2_get_reg_osccursel(data)                                 ((0x00018000&(data))>>15)
#define EMMC_TM_SENSOR_CTRL2_reg_order3_shift                                        (14)
#define EMMC_TM_SENSOR_CTRL2_reg_order3_mask                                         (0x00004000)
#define EMMC_TM_SENSOR_CTRL2_reg_order3(data)                                        (0x00004000&((data)<<14))
#define EMMC_TM_SENSOR_CTRL2_reg_order3_src(data)                                    ((0x00004000&(data))>>14)
#define EMMC_TM_SENSOR_CTRL2_get_reg_order3(data)                                    ((0x00004000&(data))>>14)
#define EMMC_TM_SENSOR_CTRL2_reg_opcursel_shift                                      (12)
#define EMMC_TM_SENSOR_CTRL2_reg_opcursel_mask                                       (0x00003000)
#define EMMC_TM_SENSOR_CTRL2_reg_opcursel(data)                                      (0x00003000&((data)<<12))
#define EMMC_TM_SENSOR_CTRL2_reg_opcursel_src(data)                                  ((0x00003000&(data))>>12)
#define EMMC_TM_SENSOR_CTRL2_get_reg_opcursel(data)                                  ((0x00003000&(data))>>12)
#define EMMC_TM_SENSOR_CTRL2_reg_hold_en_shift                                       (11)
#define EMMC_TM_SENSOR_CTRL2_reg_hold_en_mask                                        (0x00000800)
#define EMMC_TM_SENSOR_CTRL2_reg_hold_en(data)                                       (0x00000800&((data)<<11))
#define EMMC_TM_SENSOR_CTRL2_reg_hold_en_src(data)                                   ((0x00000800&(data))>>11)
#define EMMC_TM_SENSOR_CTRL2_get_reg_hold_en(data)                                   ((0x00000800&(data))>>11)
#define EMMC_TM_SENSOR_CTRL2_reg_hold_dly_shift                                      (9)
#define EMMC_TM_SENSOR_CTRL2_reg_hold_dly_mask                                       (0x00000600)
#define EMMC_TM_SENSOR_CTRL2_reg_hold_dly(data)                                      (0x00000600&((data)<<9))
#define EMMC_TM_SENSOR_CTRL2_reg_hold_dly_src(data)                                  ((0x00000600&(data))>>9)
#define EMMC_TM_SENSOR_CTRL2_get_reg_hold_dly(data)                                  ((0x00000600&(data))>>9)
#define EMMC_TM_SENSOR_CTRL2_reg_filteredgesel_shift                                 (8)
#define EMMC_TM_SENSOR_CTRL2_reg_filteredgesel_mask                                  (0x00000100)
#define EMMC_TM_SENSOR_CTRL2_reg_filteredgesel(data)                                 (0x00000100&((data)<<8))
#define EMMC_TM_SENSOR_CTRL2_reg_filteredgesel_src(data)                             ((0x00000100&(data))>>8)
#define EMMC_TM_SENSOR_CTRL2_get_reg_filteredgesel(data)                             ((0x00000100&(data))>>8)
#define EMMC_TM_SENSOR_CTRL2_reg_dsr_shift                                           (5)
#define EMMC_TM_SENSOR_CTRL2_reg_dsr_mask                                            (0x000000E0)
#define EMMC_TM_SENSOR_CTRL2_reg_dsr(data)                                           (0x000000E0&((data)<<5))
#define EMMC_TM_SENSOR_CTRL2_reg_dsr_src(data)                                       ((0x000000E0&(data))>>5)
#define EMMC_TM_SENSOR_CTRL2_get_reg_dsr(data)                                       ((0x000000E0&(data))>>5)
#define EMMC_TM_SENSOR_CTRL2_reg_cksourcesel_shift                                   (4)
#define EMMC_TM_SENSOR_CTRL2_reg_cksourcesel_mask                                    (0x00000010)
#define EMMC_TM_SENSOR_CTRL2_reg_cksourcesel(data)                                   (0x00000010&((data)<<4))
#define EMMC_TM_SENSOR_CTRL2_reg_cksourcesel_src(data)                               ((0x00000010&(data))>>4)
#define EMMC_TM_SENSOR_CTRL2_get_reg_cksourcesel(data)                               ((0x00000010&(data))>>4)
#define EMMC_TM_SENSOR_CTRL2_reg_chopfreqsel_shift                                   (0)
#define EMMC_TM_SENSOR_CTRL2_reg_chopfreqsel_mask                                    (0x0000000F)
#define EMMC_TM_SENSOR_CTRL2_reg_chopfreqsel(data)                                   (0x0000000F&((data)<<0))
#define EMMC_TM_SENSOR_CTRL2_reg_chopfreqsel_src(data)                               ((0x0000000F&(data))>>0)
#define EMMC_TM_SENSOR_CTRL2_get_reg_chopfreqsel(data)                               ((0x0000000F&(data))>>0)


#define EMMC_TM_SENSOR_CTRL3                                                         0x980124c0
#define EMMC_TM_SENSOR_CTRL3_reg_addr                                                "0x980124C0"
#define EMMC_TM_SENSOR_CTRL3_reg                                                     0x980124C0
#define set_EMMC_TM_SENSOR_CTRL3_reg(data)   (*((volatile unsigned int*) EMMC_TM_SENSOR_CTRL3_reg)=data)
#define get_EMMC_TM_SENSOR_CTRL3_reg   (*((volatile unsigned int*) EMMC_TM_SENSOR_CTRL3_reg))
#define EMMC_TM_SENSOR_CTRL3_inst_adr                                                "0x0030"
#define EMMC_TM_SENSOR_CTRL3_inst                                                    0x0030
#define EMMC_TM_SENSOR_CTRL3_reg_offset_shift                                        (0)
#define EMMC_TM_SENSOR_CTRL3_reg_offset_mask                                         (0x003FFFFF)
#define EMMC_TM_SENSOR_CTRL3_reg_offset(data)                                        (0x003FFFFF&((data)<<0))
#define EMMC_TM_SENSOR_CTRL3_reg_offset_src(data)                                    ((0x003FFFFF&(data))>>0)
#define EMMC_TM_SENSOR_CTRL3_get_reg_offset(data)                                    ((0x003FFFFF&(data))>>0)


#define EMMC_TM_SENSOR_CTRL4                                                         0x980124c4
#define EMMC_TM_SENSOR_CTRL4_reg_addr                                                "0x980124C4"
#define EMMC_TM_SENSOR_CTRL4_reg                                                     0x980124C4
#define set_EMMC_TM_SENSOR_CTRL4_reg(data)   (*((volatile unsigned int*) EMMC_TM_SENSOR_CTRL4_reg)=data)
#define get_EMMC_TM_SENSOR_CTRL4_reg   (*((volatile unsigned int*) EMMC_TM_SENSOR_CTRL4_reg))
#define EMMC_TM_SENSOR_CTRL4_inst_adr                                                "0x0031"
#define EMMC_TM_SENSOR_CTRL4_inst                                                    0x0031
#define EMMC_TM_SENSOR_CTRL4_reg_r_shift                                             (0)
#define EMMC_TM_SENSOR_CTRL4_reg_r_mask                                              (0x00FFFFFF)
#define EMMC_TM_SENSOR_CTRL4_reg_r(data)                                             (0x00FFFFFF&((data)<<0))
#define EMMC_TM_SENSOR_CTRL4_reg_r_src(data)                                         ((0x00FFFFFF&(data))>>0)
#define EMMC_TM_SENSOR_CTRL4_get_reg_r(data)                                         ((0x00FFFFFF&(data))>>0)


#define EMMC_TM_SENSOR_CTRL5                                                         0x980124c8
#define EMMC_TM_SENSOR_CTRL5_reg_addr                                                "0x980124C8"
#define EMMC_TM_SENSOR_CTRL5_reg                                                     0x980124C8
#define set_EMMC_TM_SENSOR_CTRL5_reg(data)   (*((volatile unsigned int*) EMMC_TM_SENSOR_CTRL5_reg)=data)
#define get_EMMC_TM_SENSOR_CTRL5_reg   (*((volatile unsigned int*) EMMC_TM_SENSOR_CTRL5_reg))
#define EMMC_TM_SENSOR_CTRL5_inst_adr                                                "0x0032"
#define EMMC_TM_SENSOR_CTRL5_inst                                                    0x0032
#define EMMC_TM_SENSOR_CTRL5_reg_s_shift                                             (0)
#define EMMC_TM_SENSOR_CTRL5_reg_s_mask                                              (0x007FFFFF)
#define EMMC_TM_SENSOR_CTRL5_reg_s(data)                                             (0x007FFFFF&((data)<<0))
#define EMMC_TM_SENSOR_CTRL5_reg_s_src(data)                                         ((0x007FFFFF&(data))>>0)
#define EMMC_TM_SENSOR_CTRL5_get_reg_s(data)                                         ((0x007FFFFF&(data))>>0)


#define EMMC_TM_SENSOR_STATUS1                                                       0x980124cc
#define EMMC_TM_SENSOR_STATUS1_reg_addr                                              "0x980124CC"
#define EMMC_TM_SENSOR_STATUS1_reg                                                   0x980124CC
#define set_EMMC_TM_SENSOR_STATUS1_reg(data)   (*((volatile unsigned int*) EMMC_TM_SENSOR_STATUS1_reg)=data)
#define get_EMMC_TM_SENSOR_STATUS1_reg   (*((volatile unsigned int*) EMMC_TM_SENSOR_STATUS1_reg))
#define EMMC_TM_SENSOR_STATUS1_inst_adr                                              "0x0033"
#define EMMC_TM_SENSOR_STATUS1_inst                                                  0x0033
#define EMMC_TM_SENSOR_STATUS1_ct_out_shift                                          (0)
#define EMMC_TM_SENSOR_STATUS1_ct_out_mask                                           (0x0007FFFF)
#define EMMC_TM_SENSOR_STATUS1_ct_out(data)                                          (0x0007FFFF&((data)<<0))
#define EMMC_TM_SENSOR_STATUS1_ct_out_src(data)                                      ((0x0007FFFF&(data))>>0)
#define EMMC_TM_SENSOR_STATUS1_get_ct_out(data)                                      ((0x0007FFFF&(data))>>0)


#define EMMC_TM_SENSOR_STATUS2                                                       0x980124d0
#define EMMC_TM_SENSOR_STATUS2_reg_addr                                              "0x980124D0"
#define EMMC_TM_SENSOR_STATUS2_reg                                                   0x980124D0
#define set_EMMC_TM_SENSOR_STATUS2_reg(data)   (*((volatile unsigned int*) EMMC_TM_SENSOR_STATUS2_reg)=data)
#define get_EMMC_TM_SENSOR_STATUS2_reg   (*((volatile unsigned int*) EMMC_TM_SENSOR_STATUS2_reg))
#define EMMC_TM_SENSOR_STATUS2_inst_adr                                              "0x0034"
#define EMMC_TM_SENSOR_STATUS2_inst                                                  0x0034
#define EMMC_TM_SENSOR_STATUS2_u_out_shift                                           (0)
#define EMMC_TM_SENSOR_STATUS2_u_out_mask                                            (0x003FFFFF)
#define EMMC_TM_SENSOR_STATUS2_u_out(data)                                           (0x003FFFFF&((data)<<0))
#define EMMC_TM_SENSOR_STATUS2_u_out_src(data)                                       ((0x003FFFFF&(data))>>0)
#define EMMC_TM_SENSOR_STATUS2_get_u_out(data)                                       ((0x003FFFFF&(data))>>0)


#define EMMC_SWC_SEL                                                                 0x980124d4
#define EMMC_SWC_SEL_reg_addr                                                        "0x980124D4"
#define EMMC_SWC_SEL_reg                                                             0x980124D4
#define set_EMMC_SWC_SEL_reg(data)   (*((volatile unsigned int*) EMMC_SWC_SEL_reg)=data)
#define get_EMMC_SWC_SEL_reg   (*((volatile unsigned int*) EMMC_SWC_SEL_reg))
#define EMMC_SWC_SEL_inst_adr                                                        "0x0035"
#define EMMC_SWC_SEL_inst                                                            0x0035
#define EMMC_SWC_SEL_swc_sel_shift                                                   (0)
#define EMMC_SWC_SEL_swc_sel_mask                                                    (0x00000001)
#define EMMC_SWC_SEL_swc_sel(data)                                                   (0x00000001&((data)<<0))
#define EMMC_SWC_SEL_swc_sel_src(data)                                               ((0x00000001&(data))>>0)
#define EMMC_SWC_SEL_get_swc_sel(data)                                               ((0x00000001&(data))>>0)


#define EMMC_MUXPAD0                                                                 0x98012600
#define EMMC_MUXPAD0_reg_addr                                                        "0x98012600"
#define EMMC_MUXPAD0_reg                                                             0x98012600
#define set_EMMC_MUXPAD0_reg(data)   (*((volatile unsigned int*) EMMC_MUXPAD0_reg)=data)
#define get_EMMC_MUXPAD0_reg   (*((volatile unsigned int*) EMMC_MUXPAD0_reg))
#define EMMC_MUXPAD0_inst_adr                                                        "0x0080"
#define EMMC_MUXPAD0_inst                                                            0x0080
#define EMMC_MUXPAD0_nf_dd_7_shift                                                   (30)
#define EMMC_MUXPAD0_nf_dd_7_mask                                                    (0xC0000000)
#define EMMC_MUXPAD0_nf_dd_7(data)                                                   (0xC0000000&((data)<<30))
#define EMMC_MUXPAD0_nf_dd_7_src(data)                                               ((0xC0000000&(data))>>30)
#define EMMC_MUXPAD0_get_nf_dd_7(data)                                               ((0xC0000000&(data))>>30)
#define EMMC_MUXPAD0_nf_dd_6_shift                                                   (28)
#define EMMC_MUXPAD0_nf_dd_6_mask                                                    (0x30000000)
#define EMMC_MUXPAD0_nf_dd_6(data)                                                   (0x30000000&((data)<<28))
#define EMMC_MUXPAD0_nf_dd_6_src(data)                                               ((0x30000000&(data))>>28)
#define EMMC_MUXPAD0_get_nf_dd_6(data)                                               ((0x30000000&(data))>>28)
#define EMMC_MUXPAD0_nf_dd_5_shift                                                   (26)
#define EMMC_MUXPAD0_nf_dd_5_mask                                                    (0x0C000000)
#define EMMC_MUXPAD0_nf_dd_5(data)                                                   (0x0C000000&((data)<<26))
#define EMMC_MUXPAD0_nf_dd_5_src(data)                                               ((0x0C000000&(data))>>26)
#define EMMC_MUXPAD0_get_nf_dd_5(data)                                               ((0x0C000000&(data))>>26)
#define EMMC_MUXPAD0_nf_dd_4_shift                                                   (24)
#define EMMC_MUXPAD0_nf_dd_4_mask                                                    (0x03000000)
#define EMMC_MUXPAD0_nf_dd_4(data)                                                   (0x03000000&((data)<<24))
#define EMMC_MUXPAD0_nf_dd_4_src(data)                                               ((0x03000000&(data))>>24)
#define EMMC_MUXPAD0_get_nf_dd_4(data)                                               ((0x03000000&(data))>>24)
#define EMMC_MUXPAD0_nf_dd_3_shift                                                   (22)
#define EMMC_MUXPAD0_nf_dd_3_mask                                                    (0x00C00000)
#define EMMC_MUXPAD0_nf_dd_3(data)                                                   (0x00C00000&((data)<<22))
#define EMMC_MUXPAD0_nf_dd_3_src(data)                                               ((0x00C00000&(data))>>22)
#define EMMC_MUXPAD0_get_nf_dd_3(data)                                               ((0x00C00000&(data))>>22)
#define EMMC_MUXPAD0_nf_dd_2_shift                                                   (20)
#define EMMC_MUXPAD0_nf_dd_2_mask                                                    (0x00300000)
#define EMMC_MUXPAD0_nf_dd_2(data)                                                   (0x00300000&((data)<<20))
#define EMMC_MUXPAD0_nf_dd_2_src(data)                                               ((0x00300000&(data))>>20)
#define EMMC_MUXPAD0_get_nf_dd_2(data)                                               ((0x00300000&(data))>>20)
#define EMMC_MUXPAD0_nf_dd_1_shift                                                   (18)
#define EMMC_MUXPAD0_nf_dd_1_mask                                                    (0x000C0000)
#define EMMC_MUXPAD0_nf_dd_1(data)                                                   (0x000C0000&((data)<<18))
#define EMMC_MUXPAD0_nf_dd_1_src(data)                                               ((0x000C0000&(data))>>18)
#define EMMC_MUXPAD0_get_nf_dd_1(data)                                               ((0x000C0000&(data))>>18)
#define EMMC_MUXPAD0_nf_dd_0_shift                                                   (16)
#define EMMC_MUXPAD0_nf_dd_0_mask                                                    (0x00030000)
#define EMMC_MUXPAD0_nf_dd_0(data)                                                   (0x00030000&((data)<<16))
#define EMMC_MUXPAD0_nf_dd_0_src(data)                                               ((0x00030000&(data))>>16)
#define EMMC_MUXPAD0_get_nf_dd_0(data)                                               ((0x00030000&(data))>>16)
#define EMMC_MUXPAD0_nf_ce_n_1_shift                                                 (14)
#define EMMC_MUXPAD0_nf_ce_n_1_mask                                                  (0x0000C000)
#define EMMC_MUXPAD0_nf_ce_n_1(data)                                                 (0x0000C000&((data)<<14))
#define EMMC_MUXPAD0_nf_ce_n_1_src(data)                                             ((0x0000C000&(data))>>14)
#define EMMC_MUXPAD0_get_nf_ce_n_1(data)                                             ((0x0000C000&(data))>>14)
#define EMMC_MUXPAD0_nf_ce_n_0_shift                                                 (12)
#define EMMC_MUXPAD0_nf_ce_n_0_mask                                                  (0x00003000)
#define EMMC_MUXPAD0_nf_ce_n_0(data)                                                 (0x00003000&((data)<<12))
#define EMMC_MUXPAD0_nf_ce_n_0_src(data)                                             ((0x00003000&(data))>>12)
#define EMMC_MUXPAD0_get_nf_ce_n_0(data)                                             ((0x00003000&(data))>>12)
#define EMMC_MUXPAD0_nf_cle_shift                                                    (10)
#define EMMC_MUXPAD0_nf_cle_mask                                                     (0x00000C00)
#define EMMC_MUXPAD0_nf_cle(data)                                                    (0x00000C00&((data)<<10))
#define EMMC_MUXPAD0_nf_cle_src(data)                                                ((0x00000C00&(data))>>10)
#define EMMC_MUXPAD0_get_nf_cle(data)                                                ((0x00000C00&(data))>>10)
#define EMMC_MUXPAD0_nf_ale_shift                                                    (8)
#define EMMC_MUXPAD0_nf_ale_mask                                                     (0x00000300)
#define EMMC_MUXPAD0_nf_ale(data)                                                    (0x00000300&((data)<<8))
#define EMMC_MUXPAD0_nf_ale_src(data)                                                ((0x00000300&(data))>>8)
#define EMMC_MUXPAD0_get_nf_ale(data)                                                ((0x00000300&(data))>>8)
#define EMMC_MUXPAD0_nf_wr_n_shift                                                   (6)
#define EMMC_MUXPAD0_nf_wr_n_mask                                                    (0x000000C0)
#define EMMC_MUXPAD0_nf_wr_n(data)                                                   (0x000000C0&((data)<<6))
#define EMMC_MUXPAD0_nf_wr_n_src(data)                                               ((0x000000C0&(data))>>6)
#define EMMC_MUXPAD0_get_nf_wr_n(data)                                               ((0x000000C0&(data))>>6)
#define EMMC_MUXPAD0_nf_rd_n_shift                                                   (4)
#define EMMC_MUXPAD0_nf_rd_n_mask                                                    (0x00000030)
#define EMMC_MUXPAD0_nf_rd_n(data)                                                   (0x00000030&((data)<<4))
#define EMMC_MUXPAD0_nf_rd_n_src(data)                                               ((0x00000030&(data))>>4)
#define EMMC_MUXPAD0_get_nf_rd_n(data)                                               ((0x00000030&(data))>>4)
#define EMMC_MUXPAD0_nf_rdy_shift                                                    (2)
#define EMMC_MUXPAD0_nf_rdy_mask                                                     (0x0000000C)
#define EMMC_MUXPAD0_nf_rdy(data)                                                    (0x0000000C&((data)<<2))
#define EMMC_MUXPAD0_nf_rdy_src(data)                                                ((0x0000000C&(data))>>2)
#define EMMC_MUXPAD0_get_nf_rdy(data)                                                ((0x0000000C&(data))>>2)
#define EMMC_MUXPAD0_nf_dqs_shift                                                    (0)
#define EMMC_MUXPAD0_nf_dqs_mask                                                     (0x00000003)
#define EMMC_MUXPAD0_nf_dqs(data)                                                    (0x00000003&((data)<<0))
#define EMMC_MUXPAD0_nf_dqs_src(data)                                                ((0x00000003&(data))>>0)
#define EMMC_MUXPAD0_get_nf_dqs(data)                                                ((0x00000003&(data))>>0)


#define EMMC_MUXPAD1                                                                 0x98012604
#define EMMC_MUXPAD1_reg_addr                                                        "0x98012604"
#define EMMC_MUXPAD1_reg                                                             0x98012604
#define set_EMMC_MUXPAD1_reg(data)   (*((volatile unsigned int*) EMMC_MUXPAD1_reg)=data)
#define get_EMMC_MUXPAD1_reg   (*((volatile unsigned int*) EMMC_MUXPAD1_reg))
#define EMMC_MUXPAD1_inst_adr                                                        "0x0081"
#define EMMC_MUXPAD1_inst                                                            0x0081
#define EMMC_MUXPAD1_mmc_data_3_shift                                                (30)
#define EMMC_MUXPAD1_mmc_data_3_mask                                                 (0xC0000000)
#define EMMC_MUXPAD1_mmc_data_3(data)                                                (0xC0000000&((data)<<30))
#define EMMC_MUXPAD1_mmc_data_3_src(data)                                            ((0xC0000000&(data))>>30)
#define EMMC_MUXPAD1_get_mmc_data_3(data)                                            ((0xC0000000&(data))>>30)
#define EMMC_MUXPAD1_mmc_data_2_shift                                                (28)
#define EMMC_MUXPAD1_mmc_data_2_mask                                                 (0x30000000)
#define EMMC_MUXPAD1_mmc_data_2(data)                                                (0x30000000&((data)<<28))
#define EMMC_MUXPAD1_mmc_data_2_src(data)                                            ((0x30000000&(data))>>28)
#define EMMC_MUXPAD1_get_mmc_data_2(data)                                            ((0x30000000&(data))>>28)
#define EMMC_MUXPAD1_mmc_data_1_shift                                                (26)
#define EMMC_MUXPAD1_mmc_data_1_mask                                                 (0x0C000000)
#define EMMC_MUXPAD1_mmc_data_1(data)                                                (0x0C000000&((data)<<26))
#define EMMC_MUXPAD1_mmc_data_1_src(data)                                            ((0x0C000000&(data))>>26)
#define EMMC_MUXPAD1_get_mmc_data_1(data)                                            ((0x0C000000&(data))>>26)
#define EMMC_MUXPAD1_mmc_data_0_shift                                                (24)
#define EMMC_MUXPAD1_mmc_data_0_mask                                                 (0x03000000)
#define EMMC_MUXPAD1_mmc_data_0(data)                                                (0x03000000&((data)<<24))
#define EMMC_MUXPAD1_mmc_data_0_src(data)                                            ((0x03000000&(data))>>24)
#define EMMC_MUXPAD1_get_mmc_data_0(data)                                            ((0x03000000&(data))>>24)
#define EMMC_MUXPAD1_mmc_cd_shift                                                    (22)
#define EMMC_MUXPAD1_mmc_cd_mask                                                     (0x00C00000)
#define EMMC_MUXPAD1_mmc_cd(data)                                                    (0x00C00000&((data)<<22))
#define EMMC_MUXPAD1_mmc_cd_src(data)                                                ((0x00C00000&(data))>>22)
#define EMMC_MUXPAD1_get_mmc_cd(data)                                                ((0x00C00000&(data))>>22)
#define EMMC_MUXPAD1_mmc_wp_shift                                                    (20)
#define EMMC_MUXPAD1_mmc_wp_mask                                                     (0x00300000)
#define EMMC_MUXPAD1_mmc_wp(data)                                                    (0x00300000&((data)<<20))
#define EMMC_MUXPAD1_mmc_wp_src(data)                                                ((0x00300000&(data))>>20)
#define EMMC_MUXPAD1_get_mmc_wp(data)                                                ((0x00300000&(data))>>20)
#define EMMC_MUXPAD1_mmc_clk_shift                                                   (18)
#define EMMC_MUXPAD1_mmc_clk_mask                                                    (0x000C0000)
#define EMMC_MUXPAD1_mmc_clk(data)                                                   (0x000C0000&((data)<<18))
#define EMMC_MUXPAD1_mmc_clk_src(data)                                               ((0x000C0000&(data))>>18)
#define EMMC_MUXPAD1_get_mmc_clk(data)                                               ((0x000C0000&(data))>>18)
#define EMMC_MUXPAD1_mmc_cmd_shift                                                   (16)
#define EMMC_MUXPAD1_mmc_cmd_mask                                                    (0x00030000)
#define EMMC_MUXPAD1_mmc_cmd(data)                                                   (0x00030000&((data)<<16))
#define EMMC_MUXPAD1_mmc_cmd_src(data)                                               ((0x00030000&(data))>>16)
#define EMMC_MUXPAD1_get_mmc_cmd(data)                                               ((0x00030000&(data))>>16)
#define EMMC_MUXPAD1_emmc_dd_sb_shift                                                (12)
#define EMMC_MUXPAD1_emmc_dd_sb_mask                                                 (0x00003000)
#define EMMC_MUXPAD1_emmc_dd_sb(data)                                                (0x00003000&((data)<<12))
#define EMMC_MUXPAD1_emmc_dd_sb_src(data)                                            ((0x00003000&(data))>>12)
#define EMMC_MUXPAD1_get_emmc_dd_sb(data)                                            ((0x00003000&(data))>>12)
#define EMMC_MUXPAD1_sdio_data_3_shift                                               (10)
#define EMMC_MUXPAD1_sdio_data_3_mask                                                (0x00000C00)
#define EMMC_MUXPAD1_sdio_data_3(data)                                               (0x00000C00&((data)<<10))
#define EMMC_MUXPAD1_sdio_data_3_src(data)                                           ((0x00000C00&(data))>>10)
#define EMMC_MUXPAD1_get_sdio_data_3(data)                                           ((0x00000C00&(data))>>10)
#define EMMC_MUXPAD1_sdio_data_2_shift                                               (8)
#define EMMC_MUXPAD1_sdio_data_2_mask                                                (0x00000300)
#define EMMC_MUXPAD1_sdio_data_2(data)                                               (0x00000300&((data)<<8))
#define EMMC_MUXPAD1_sdio_data_2_src(data)                                           ((0x00000300&(data))>>8)
#define EMMC_MUXPAD1_get_sdio_data_2(data)                                           ((0x00000300&(data))>>8)
#define EMMC_MUXPAD1_sdio_data_1_shift                                               (6)
#define EMMC_MUXPAD1_sdio_data_1_mask                                                (0x000000C0)
#define EMMC_MUXPAD1_sdio_data_1(data)                                               (0x000000C0&((data)<<6))
#define EMMC_MUXPAD1_sdio_data_1_src(data)                                           ((0x000000C0&(data))>>6)
#define EMMC_MUXPAD1_get_sdio_data_1(data)                                           ((0x000000C0&(data))>>6)
#define EMMC_MUXPAD1_sdio_data_0_shift                                               (4)
#define EMMC_MUXPAD1_sdio_data_0_mask                                                (0x00000030)
#define EMMC_MUXPAD1_sdio_data_0(data)                                               (0x00000030&((data)<<4))
#define EMMC_MUXPAD1_sdio_data_0_src(data)                                           ((0x00000030&(data))>>4)
#define EMMC_MUXPAD1_get_sdio_data_0(data)                                           ((0x00000030&(data))>>4)
#define EMMC_MUXPAD1_sdio_clk_shift                                                  (2)
#define EMMC_MUXPAD1_sdio_clk_mask                                                   (0x0000000C)
#define EMMC_MUXPAD1_sdio_clk(data)                                                  (0x0000000C&((data)<<2))
#define EMMC_MUXPAD1_sdio_clk_src(data)                                              ((0x0000000C&(data))>>2)
#define EMMC_MUXPAD1_get_sdio_clk(data)                                              ((0x0000000C&(data))>>2)
#define EMMC_MUXPAD1_sdio_cmd_shift                                                  (0)
#define EMMC_MUXPAD1_sdio_cmd_mask                                                   (0x00000003)
#define EMMC_MUXPAD1_sdio_cmd(data)                                                  (0x00000003&((data)<<0))
#define EMMC_MUXPAD1_sdio_cmd_src(data)                                              ((0x00000003&(data))>>0)
#define EMMC_MUXPAD1_get_sdio_cmd(data)                                              ((0x00000003&(data))>>0)


#define EMMC_PFUNC_NF0                                                               0x98012608
#define EMMC_PFUNC_NF0_reg_addr                                                      "0x98012608"
#define EMMC_PFUNC_NF0_reg                                                           0x98012608
#define set_EMMC_PFUNC_NF0_reg(data)   (*((volatile unsigned int*) EMMC_PFUNC_NF0_reg)=data)
#define get_EMMC_PFUNC_NF0_reg   (*((volatile unsigned int*) EMMC_PFUNC_NF0_reg))
#define EMMC_PFUNC_NF0_inst_adr                                                      "0x0082"
#define EMMC_PFUNC_NF0_inst                                                          0x0082
#define EMMC_PFUNC_NF0_nf_cle_smt_shift                                              (31)
#define EMMC_PFUNC_NF0_nf_cle_smt_mask                                               (0x80000000)
#define EMMC_PFUNC_NF0_nf_cle_smt(data)                                              (0x80000000&((data)<<31))
#define EMMC_PFUNC_NF0_nf_cle_smt_src(data)                                          ((0x80000000&(data))>>31)
#define EMMC_PFUNC_NF0_get_nf_cle_smt(data)                                          ((0x80000000&(data))>>31)
#define EMMC_PFUNC_NF0_nf_cle_pud_en_shift                                           (29)
#define EMMC_PFUNC_NF0_nf_cle_pud_en_mask                                            (0x20000000)
#define EMMC_PFUNC_NF0_nf_cle_pud_en(data)                                           (0x20000000&((data)<<29))
#define EMMC_PFUNC_NF0_nf_cle_pud_en_src(data)                                       ((0x20000000&(data))>>29)
#define EMMC_PFUNC_NF0_get_nf_cle_pud_en(data)                                       ((0x20000000&(data))>>29)
#define EMMC_PFUNC_NF0_nf_cle_pud_sel_shift                                          (28)
#define EMMC_PFUNC_NF0_nf_cle_pud_sel_mask                                           (0x10000000)
#define EMMC_PFUNC_NF0_nf_cle_pud_sel(data)                                          (0x10000000&((data)<<28))
#define EMMC_PFUNC_NF0_nf_cle_pud_sel_src(data)                                      ((0x10000000&(data))>>28)
#define EMMC_PFUNC_NF0_get_nf_cle_pud_sel(data)                                      ((0x10000000&(data))>>28)
#define EMMC_PFUNC_NF0_nf_wr_n_smt_shift                                             (27)
#define EMMC_PFUNC_NF0_nf_wr_n_smt_mask                                              (0x08000000)
#define EMMC_PFUNC_NF0_nf_wr_n_smt(data)                                             (0x08000000&((data)<<27))
#define EMMC_PFUNC_NF0_nf_wr_n_smt_src(data)                                         ((0x08000000&(data))>>27)
#define EMMC_PFUNC_NF0_get_nf_wr_n_smt(data)                                         ((0x08000000&(data))>>27)
#define EMMC_PFUNC_NF0_nf_wr_n_pud_en_shift                                          (25)
#define EMMC_PFUNC_NF0_nf_wr_n_pud_en_mask                                           (0x02000000)
#define EMMC_PFUNC_NF0_nf_wr_n_pud_en(data)                                          (0x02000000&((data)<<25))
#define EMMC_PFUNC_NF0_nf_wr_n_pud_en_src(data)                                      ((0x02000000&(data))>>25)
#define EMMC_PFUNC_NF0_get_nf_wr_n_pud_en(data)                                      ((0x02000000&(data))>>25)
#define EMMC_PFUNC_NF0_nf_wr_n_pud_sel_shift                                         (24)
#define EMMC_PFUNC_NF0_nf_wr_n_pud_sel_mask                                          (0x01000000)
#define EMMC_PFUNC_NF0_nf_wr_n_pud_sel(data)                                         (0x01000000&((data)<<24))
#define EMMC_PFUNC_NF0_nf_wr_n_pud_sel_src(data)                                     ((0x01000000&(data))>>24)
#define EMMC_PFUNC_NF0_get_nf_wr_n_pud_sel(data)                                     ((0x01000000&(data))>>24)
#define EMMC_PFUNC_NF0_nf_rd_n_smt_shift                                             (23)
#define EMMC_PFUNC_NF0_nf_rd_n_smt_mask                                              (0x00800000)
#define EMMC_PFUNC_NF0_nf_rd_n_smt(data)                                             (0x00800000&((data)<<23))
#define EMMC_PFUNC_NF0_nf_rd_n_smt_src(data)                                         ((0x00800000&(data))>>23)
#define EMMC_PFUNC_NF0_get_nf_rd_n_smt(data)                                         ((0x00800000&(data))>>23)
#define EMMC_PFUNC_NF0_nf_rd_n_pud_en_shift                                          (21)
#define EMMC_PFUNC_NF0_nf_rd_n_pud_en_mask                                           (0x00200000)
#define EMMC_PFUNC_NF0_nf_rd_n_pud_en(data)                                          (0x00200000&((data)<<21))
#define EMMC_PFUNC_NF0_nf_rd_n_pud_en_src(data)                                      ((0x00200000&(data))>>21)
#define EMMC_PFUNC_NF0_get_nf_rd_n_pud_en(data)                                      ((0x00200000&(data))>>21)
#define EMMC_PFUNC_NF0_nf_rd_n_pud_sel_shift                                         (20)
#define EMMC_PFUNC_NF0_nf_rd_n_pud_sel_mask                                          (0x00100000)
#define EMMC_PFUNC_NF0_nf_rd_n_pud_sel(data)                                         (0x00100000&((data)<<20))
#define EMMC_PFUNC_NF0_nf_rd_n_pud_sel_src(data)                                     ((0x00100000&(data))>>20)
#define EMMC_PFUNC_NF0_get_nf_rd_n_pud_sel(data)                                     ((0x00100000&(data))>>20)
#define EMMC_PFUNC_NF0_nf_rdy_smt_shift                                              (19)
#define EMMC_PFUNC_NF0_nf_rdy_smt_mask                                               (0x00080000)
#define EMMC_PFUNC_NF0_nf_rdy_smt(data)                                              (0x00080000&((data)<<19))
#define EMMC_PFUNC_NF0_nf_rdy_smt_src(data)                                          ((0x00080000&(data))>>19)
#define EMMC_PFUNC_NF0_get_nf_rdy_smt(data)                                          ((0x00080000&(data))>>19)
#define EMMC_PFUNC_NF0_nf_rdy_pud_en_shift                                           (17)
#define EMMC_PFUNC_NF0_nf_rdy_pud_en_mask                                            (0x00020000)
#define EMMC_PFUNC_NF0_nf_rdy_pud_en(data)                                           (0x00020000&((data)<<17))
#define EMMC_PFUNC_NF0_nf_rdy_pud_en_src(data)                                       ((0x00020000&(data))>>17)
#define EMMC_PFUNC_NF0_get_nf_rdy_pud_en(data)                                       ((0x00020000&(data))>>17)
#define EMMC_PFUNC_NF0_nf_rdy_pud_sel_shift                                          (16)
#define EMMC_PFUNC_NF0_nf_rdy_pud_sel_mask                                           (0x00010000)
#define EMMC_PFUNC_NF0_nf_rdy_pud_sel(data)                                          (0x00010000&((data)<<16))
#define EMMC_PFUNC_NF0_nf_rdy_pud_sel_src(data)                                      ((0x00010000&(data))>>16)
#define EMMC_PFUNC_NF0_get_nf_rdy_pud_sel(data)                                      ((0x00010000&(data))>>16)
#define EMMC_PFUNC_NF0_nf_ce_n_1_smt_shift                                           (15)
#define EMMC_PFUNC_NF0_nf_ce_n_1_smt_mask                                            (0x00008000)
#define EMMC_PFUNC_NF0_nf_ce_n_1_smt(data)                                           (0x00008000&((data)<<15))
#define EMMC_PFUNC_NF0_nf_ce_n_1_smt_src(data)                                       ((0x00008000&(data))>>15)
#define EMMC_PFUNC_NF0_get_nf_ce_n_1_smt(data)                                       ((0x00008000&(data))>>15)
#define EMMC_PFUNC_NF0_nf_ce_n_1_pud_en_shift                                        (13)
#define EMMC_PFUNC_NF0_nf_ce_n_1_pud_en_mask                                         (0x00002000)
#define EMMC_PFUNC_NF0_nf_ce_n_1_pud_en(data)                                        (0x00002000&((data)<<13))
#define EMMC_PFUNC_NF0_nf_ce_n_1_pud_en_src(data)                                    ((0x00002000&(data))>>13)
#define EMMC_PFUNC_NF0_get_nf_ce_n_1_pud_en(data)                                    ((0x00002000&(data))>>13)
#define EMMC_PFUNC_NF0_nf_ce_n_1_pud_sel_shift                                       (12)
#define EMMC_PFUNC_NF0_nf_ce_n_1_pud_sel_mask                                        (0x00001000)
#define EMMC_PFUNC_NF0_nf_ce_n_1_pud_sel(data)                                       (0x00001000&((data)<<12))
#define EMMC_PFUNC_NF0_nf_ce_n_1_pud_sel_src(data)                                   ((0x00001000&(data))>>12)
#define EMMC_PFUNC_NF0_get_nf_ce_n_1_pud_sel(data)                                   ((0x00001000&(data))>>12)
#define EMMC_PFUNC_NF0_nf_ce_n_0_smt_shift                                           (11)
#define EMMC_PFUNC_NF0_nf_ce_n_0_smt_mask                                            (0x00000800)
#define EMMC_PFUNC_NF0_nf_ce_n_0_smt(data)                                           (0x00000800&((data)<<11))
#define EMMC_PFUNC_NF0_nf_ce_n_0_smt_src(data)                                       ((0x00000800&(data))>>11)
#define EMMC_PFUNC_NF0_get_nf_ce_n_0_smt(data)                                       ((0x00000800&(data))>>11)
#define EMMC_PFUNC_NF0_nf_ce_n_0_pud_en_shift                                        (9)
#define EMMC_PFUNC_NF0_nf_ce_n_0_pud_en_mask                                         (0x00000200)
#define EMMC_PFUNC_NF0_nf_ce_n_0_pud_en(data)                                        (0x00000200&((data)<<9))
#define EMMC_PFUNC_NF0_nf_ce_n_0_pud_en_src(data)                                    ((0x00000200&(data))>>9)
#define EMMC_PFUNC_NF0_get_nf_ce_n_0_pud_en(data)                                    ((0x00000200&(data))>>9)
#define EMMC_PFUNC_NF0_nf_ce_n_0_pud_sel_shift                                       (8)
#define EMMC_PFUNC_NF0_nf_ce_n_0_pud_sel_mask                                        (0x00000100)
#define EMMC_PFUNC_NF0_nf_ce_n_0_pud_sel(data)                                       (0x00000100&((data)<<8))
#define EMMC_PFUNC_NF0_nf_ce_n_0_pud_sel_src(data)                                   ((0x00000100&(data))>>8)
#define EMMC_PFUNC_NF0_get_nf_ce_n_0_pud_sel(data)                                   ((0x00000100&(data))>>8)
#define EMMC_PFUNC_NF0_nf_ale_smt_shift                                              (7)
#define EMMC_PFUNC_NF0_nf_ale_smt_mask                                               (0x00000080)
#define EMMC_PFUNC_NF0_nf_ale_smt(data)                                              (0x00000080&((data)<<7))
#define EMMC_PFUNC_NF0_nf_ale_smt_src(data)                                          ((0x00000080&(data))>>7)
#define EMMC_PFUNC_NF0_get_nf_ale_smt(data)                                          ((0x00000080&(data))>>7)
#define EMMC_PFUNC_NF0_nf_ale_pud_en_shift                                           (5)
#define EMMC_PFUNC_NF0_nf_ale_pud_en_mask                                            (0x00000020)
#define EMMC_PFUNC_NF0_nf_ale_pud_en(data)                                           (0x00000020&((data)<<5))
#define EMMC_PFUNC_NF0_nf_ale_pud_en_src(data)                                       ((0x00000020&(data))>>5)
#define EMMC_PFUNC_NF0_get_nf_ale_pud_en(data)                                       ((0x00000020&(data))>>5)
#define EMMC_PFUNC_NF0_nf_ale_pud_sel_shift                                          (4)
#define EMMC_PFUNC_NF0_nf_ale_pud_sel_mask                                           (0x00000010)
#define EMMC_PFUNC_NF0_nf_ale_pud_sel(data)                                          (0x00000010&((data)<<4))
#define EMMC_PFUNC_NF0_nf_ale_pud_sel_src(data)                                      ((0x00000010&(data))>>4)
#define EMMC_PFUNC_NF0_get_nf_ale_pud_sel(data)                                      ((0x00000010&(data))>>4)
#define EMMC_PFUNC_NF0_nf_dqs_smt_shift                                              (3)
#define EMMC_PFUNC_NF0_nf_dqs_smt_mask                                               (0x00000008)
#define EMMC_PFUNC_NF0_nf_dqs_smt(data)                                              (0x00000008&((data)<<3))
#define EMMC_PFUNC_NF0_nf_dqs_smt_src(data)                                          ((0x00000008&(data))>>3)
#define EMMC_PFUNC_NF0_get_nf_dqs_smt(data)                                          ((0x00000008&(data))>>3)
#define EMMC_PFUNC_NF0_nf_dqs_pud_en_shift                                           (1)
#define EMMC_PFUNC_NF0_nf_dqs_pud_en_mask                                            (0x00000002)
#define EMMC_PFUNC_NF0_nf_dqs_pud_en(data)                                           (0x00000002&((data)<<1))
#define EMMC_PFUNC_NF0_nf_dqs_pud_en_src(data)                                       ((0x00000002&(data))>>1)
#define EMMC_PFUNC_NF0_get_nf_dqs_pud_en(data)                                       ((0x00000002&(data))>>1)
#define EMMC_PFUNC_NF0_nf_dqs_pud_sel_shift                                          (0)
#define EMMC_PFUNC_NF0_nf_dqs_pud_sel_mask                                           (0x00000001)
#define EMMC_PFUNC_NF0_nf_dqs_pud_sel(data)                                          (0x00000001&((data)<<0))
#define EMMC_PFUNC_NF0_nf_dqs_pud_sel_src(data)                                      ((0x00000001&(data))>>0)
#define EMMC_PFUNC_NF0_get_nf_dqs_pud_sel(data)                                      ((0x00000001&(data))>>0)


#define EMMC_PFUNC_NF1                                                               0x9801260C
#define EMMC_PFUNC_NF1_reg_addr                                                      "0x9801260C"
#define EMMC_PFUNC_NF1_reg                                                           0x9801260C
#define set_EMMC_PFUNC_NF1_reg(data)   (*((volatile unsigned int*) EMMC_PFUNC_NF1_reg)=data)
#define get_EMMC_PFUNC_NF1_reg   (*((volatile unsigned int*) EMMC_PFUNC_NF1_reg))
#define EMMC_PFUNC_NF1_inst_adr                                                      "0x0083"
#define EMMC_PFUNC_NF1_inst                                                          0x0083
#define EMMC_PFUNC_NF1_nf_dd_7_smt_shift                                             (31)
#define EMMC_PFUNC_NF1_nf_dd_7_smt_mask                                              (0x80000000)
#define EMMC_PFUNC_NF1_nf_dd_7_smt(data)                                             (0x80000000&((data)<<31))
#define EMMC_PFUNC_NF1_nf_dd_7_smt_src(data)                                         ((0x80000000&(data))>>31)
#define EMMC_PFUNC_NF1_get_nf_dd_7_smt(data)                                         ((0x80000000&(data))>>31)
#define EMMC_PFUNC_NF1_nf_dd_7_pud_en_shift                                          (29)
#define EMMC_PFUNC_NF1_nf_dd_7_pud_en_mask                                           (0x20000000)
#define EMMC_PFUNC_NF1_nf_dd_7_pud_en(data)                                          (0x20000000&((data)<<29))
#define EMMC_PFUNC_NF1_nf_dd_7_pud_en_src(data)                                      ((0x20000000&(data))>>29)
#define EMMC_PFUNC_NF1_get_nf_dd_7_pud_en(data)                                      ((0x20000000&(data))>>29)
#define EMMC_PFUNC_NF1_nf_dd_7_pud_sel_shift                                         (28)
#define EMMC_PFUNC_NF1_nf_dd_7_pud_sel_mask                                          (0x10000000)
#define EMMC_PFUNC_NF1_nf_dd_7_pud_sel(data)                                         (0x10000000&((data)<<28))
#define EMMC_PFUNC_NF1_nf_dd_7_pud_sel_src(data)                                     ((0x10000000&(data))>>28)
#define EMMC_PFUNC_NF1_get_nf_dd_7_pud_sel(data)                                     ((0x10000000&(data))>>28)
#define EMMC_PFUNC_NF1_nf_dd_6_smt_shift                                             (27)
#define EMMC_PFUNC_NF1_nf_dd_6_smt_mask                                              (0x08000000)
#define EMMC_PFUNC_NF1_nf_dd_6_smt(data)                                             (0x08000000&((data)<<27))
#define EMMC_PFUNC_NF1_nf_dd_6_smt_src(data)                                         ((0x08000000&(data))>>27)
#define EMMC_PFUNC_NF1_get_nf_dd_6_smt(data)                                         ((0x08000000&(data))>>27)
#define EMMC_PFUNC_NF1_nf_dd_6_pud_en_shift                                          (25)
#define EMMC_PFUNC_NF1_nf_dd_6_pud_en_mask                                           (0x02000000)
#define EMMC_PFUNC_NF1_nf_dd_6_pud_en(data)                                          (0x02000000&((data)<<25))
#define EMMC_PFUNC_NF1_nf_dd_6_pud_en_src(data)                                      ((0x02000000&(data))>>25)
#define EMMC_PFUNC_NF1_get_nf_dd_6_pud_en(data)                                      ((0x02000000&(data))>>25)
#define EMMC_PFUNC_NF1_nf_dd_6_pud_sel_shift                                         (24)
#define EMMC_PFUNC_NF1_nf_dd_6_pud_sel_mask                                          (0x01000000)
#define EMMC_PFUNC_NF1_nf_dd_6_pud_sel(data)                                         (0x01000000&((data)<<24))
#define EMMC_PFUNC_NF1_nf_dd_6_pud_sel_src(data)                                     ((0x01000000&(data))>>24)
#define EMMC_PFUNC_NF1_get_nf_dd_6_pud_sel(data)                                     ((0x01000000&(data))>>24)
#define EMMC_PFUNC_NF1_nf_dd_5_smt_shift                                             (23)
#define EMMC_PFUNC_NF1_nf_dd_5_smt_mask                                              (0x00800000)
#define EMMC_PFUNC_NF1_nf_dd_5_smt(data)                                             (0x00800000&((data)<<23))
#define EMMC_PFUNC_NF1_nf_dd_5_smt_src(data)                                         ((0x00800000&(data))>>23)
#define EMMC_PFUNC_NF1_get_nf_dd_5_smt(data)                                         ((0x00800000&(data))>>23)
#define EMMC_PFUNC_NF1_nf_dd_5_pud_en_shift                                          (21)
#define EMMC_PFUNC_NF1_nf_dd_5_pud_en_mask                                           (0x00200000)
#define EMMC_PFUNC_NF1_nf_dd_5_pud_en(data)                                          (0x00200000&((data)<<21))
#define EMMC_PFUNC_NF1_nf_dd_5_pud_en_src(data)                                      ((0x00200000&(data))>>21)
#define EMMC_PFUNC_NF1_get_nf_dd_5_pud_en(data)                                      ((0x00200000&(data))>>21)
#define EMMC_PFUNC_NF1_nf_dd_5_pud_sel_shift                                         (20)
#define EMMC_PFUNC_NF1_nf_dd_5_pud_sel_mask                                          (0x00100000)
#define EMMC_PFUNC_NF1_nf_dd_5_pud_sel(data)                                         (0x00100000&((data)<<20))
#define EMMC_PFUNC_NF1_nf_dd_5_pud_sel_src(data)                                     ((0x00100000&(data))>>20)
#define EMMC_PFUNC_NF1_get_nf_dd_5_pud_sel(data)                                     ((0x00100000&(data))>>20)
#define EMMC_PFUNC_NF1_nf_dd_4_smt_shift                                             (19)
#define EMMC_PFUNC_NF1_nf_dd_4_smt_mask                                              (0x00080000)
#define EMMC_PFUNC_NF1_nf_dd_4_smt(data)                                             (0x00080000&((data)<<19))
#define EMMC_PFUNC_NF1_nf_dd_4_smt_src(data)                                         ((0x00080000&(data))>>19)
#define EMMC_PFUNC_NF1_get_nf_dd_4_smt(data)                                         ((0x00080000&(data))>>19)
#define EMMC_PFUNC_NF1_nf_dd_4_pud_en_shift                                          (17)
#define EMMC_PFUNC_NF1_nf_dd_4_pud_en_mask                                           (0x00020000)
#define EMMC_PFUNC_NF1_nf_dd_4_pud_en(data)                                          (0x00020000&((data)<<17))
#define EMMC_PFUNC_NF1_nf_dd_4_pud_en_src(data)                                      ((0x00020000&(data))>>17)
#define EMMC_PFUNC_NF1_get_nf_dd_4_pud_en(data)                                      ((0x00020000&(data))>>17)
#define EMMC_PFUNC_NF1_nf_dd_4_pud_sel_shift                                         (16)
#define EMMC_PFUNC_NF1_nf_dd_4_pud_sel_mask                                          (0x00010000)
#define EMMC_PFUNC_NF1_nf_dd_4_pud_sel(data)                                         (0x00010000&((data)<<16))
#define EMMC_PFUNC_NF1_nf_dd_4_pud_sel_src(data)                                     ((0x00010000&(data))>>16)
#define EMMC_PFUNC_NF1_get_nf_dd_4_pud_sel(data)                                     ((0x00010000&(data))>>16)
#define EMMC_PFUNC_NF1_nf_dd_3_smt_shift                                             (15)
#define EMMC_PFUNC_NF1_nf_dd_3_smt_mask                                              (0x00008000)
#define EMMC_PFUNC_NF1_nf_dd_3_smt(data)                                             (0x00008000&((data)<<15))
#define EMMC_PFUNC_NF1_nf_dd_3_smt_src(data)                                         ((0x00008000&(data))>>15)
#define EMMC_PFUNC_NF1_get_nf_dd_3_smt(data)                                         ((0x00008000&(data))>>15)
#define EMMC_PFUNC_NF1_nf_dd_3_pud_en_shift                                          (13)
#define EMMC_PFUNC_NF1_nf_dd_3_pud_en_mask                                           (0x00002000)
#define EMMC_PFUNC_NF1_nf_dd_3_pud_en(data)                                          (0x00002000&((data)<<13))
#define EMMC_PFUNC_NF1_nf_dd_3_pud_en_src(data)                                      ((0x00002000&(data))>>13)
#define EMMC_PFUNC_NF1_get_nf_dd_3_pud_en(data)                                      ((0x00002000&(data))>>13)
#define EMMC_PFUNC_NF1_nf_dd_3_pud_sel_shift                                         (12)
#define EMMC_PFUNC_NF1_nf_dd_3_pud_sel_mask                                          (0x00001000)
#define EMMC_PFUNC_NF1_nf_dd_3_pud_sel(data)                                         (0x00001000&((data)<<12))
#define EMMC_PFUNC_NF1_nf_dd_3_pud_sel_src(data)                                     ((0x00001000&(data))>>12)
#define EMMC_PFUNC_NF1_get_nf_dd_3_pud_sel(data)                                     ((0x00001000&(data))>>12)
#define EMMC_PFUNC_NF1_nf_dd_2_smt_shift                                             (11)
#define EMMC_PFUNC_NF1_nf_dd_2_smt_mask                                              (0x00000800)
#define EMMC_PFUNC_NF1_nf_dd_2_smt(data)                                             (0x00000800&((data)<<11))
#define EMMC_PFUNC_NF1_nf_dd_2_smt_src(data)                                         ((0x00000800&(data))>>11)
#define EMMC_PFUNC_NF1_get_nf_dd_2_smt(data)                                         ((0x00000800&(data))>>11)
#define EMMC_PFUNC_NF1_nf_dd_2_pud_en_shift                                          (9)
#define EMMC_PFUNC_NF1_nf_dd_2_pud_en_mask                                           (0x00000200)
#define EMMC_PFUNC_NF1_nf_dd_2_pud_en(data)                                          (0x00000200&((data)<<9))
#define EMMC_PFUNC_NF1_nf_dd_2_pud_en_src(data)                                      ((0x00000200&(data))>>9)
#define EMMC_PFUNC_NF1_get_nf_dd_2_pud_en(data)                                      ((0x00000200&(data))>>9)
#define EMMC_PFUNC_NF1_nf_dd_2_pud_sel_shift                                         (8)
#define EMMC_PFUNC_NF1_nf_dd_2_pud_sel_mask                                          (0x00000100)
#define EMMC_PFUNC_NF1_nf_dd_2_pud_sel(data)                                         (0x00000100&((data)<<8))
#define EMMC_PFUNC_NF1_nf_dd_2_pud_sel_src(data)                                     ((0x00000100&(data))>>8)
#define EMMC_PFUNC_NF1_get_nf_dd_2_pud_sel(data)                                     ((0x00000100&(data))>>8)
#define EMMC_PFUNC_NF1_nf_dd_1_smt_shift                                             (7)
#define EMMC_PFUNC_NF1_nf_dd_1_smt_mask                                              (0x00000080)
#define EMMC_PFUNC_NF1_nf_dd_1_smt(data)                                             (0x00000080&((data)<<7))
#define EMMC_PFUNC_NF1_nf_dd_1_smt_src(data)                                         ((0x00000080&(data))>>7)
#define EMMC_PFUNC_NF1_get_nf_dd_1_smt(data)                                         ((0x00000080&(data))>>7)
#define EMMC_PFUNC_NF1_nf_dd_1_pud_en_shift                                          (5)
#define EMMC_PFUNC_NF1_nf_dd_1_pud_en_mask                                           (0x00000020)
#define EMMC_PFUNC_NF1_nf_dd_1_pud_en(data)                                          (0x00000020&((data)<<5))
#define EMMC_PFUNC_NF1_nf_dd_1_pud_en_src(data)                                      ((0x00000020&(data))>>5)
#define EMMC_PFUNC_NF1_get_nf_dd_1_pud_en(data)                                      ((0x00000020&(data))>>5)
#define EMMC_PFUNC_NF1_nf_dd_1_pud_sel_shift                                         (4)
#define EMMC_PFUNC_NF1_nf_dd_1_pud_sel_mask                                          (0x00000010)
#define EMMC_PFUNC_NF1_nf_dd_1_pud_sel(data)                                         (0x00000010&((data)<<4))
#define EMMC_PFUNC_NF1_nf_dd_1_pud_sel_src(data)                                     ((0x00000010&(data))>>4)
#define EMMC_PFUNC_NF1_get_nf_dd_1_pud_sel(data)                                     ((0x00000010&(data))>>4)
#define EMMC_PFUNC_NF1_nf_dd_0_smt_shift                                             (3)
#define EMMC_PFUNC_NF1_nf_dd_0_smt_mask                                              (0x00000008)
#define EMMC_PFUNC_NF1_nf_dd_0_smt(data)                                             (0x00000008&((data)<<3))
#define EMMC_PFUNC_NF1_nf_dd_0_smt_src(data)                                         ((0x00000008&(data))>>3)
#define EMMC_PFUNC_NF1_get_nf_dd_0_smt(data)                                         ((0x00000008&(data))>>3)
#define EMMC_PFUNC_NF1_nf_dd_0_pud_en_shift                                          (1)
#define EMMC_PFUNC_NF1_nf_dd_0_pud_en_mask                                           (0x00000002)
#define EMMC_PFUNC_NF1_nf_dd_0_pud_en(data)                                          (0x00000002&((data)<<1))
#define EMMC_PFUNC_NF1_nf_dd_0_pud_en_src(data)                                      ((0x00000002&(data))>>1)
#define EMMC_PFUNC_NF1_get_nf_dd_0_pud_en(data)                                      ((0x00000002&(data))>>1)
#define EMMC_PFUNC_NF1_nf_dd_0_pud_sel_shift                                         (0)
#define EMMC_PFUNC_NF1_nf_dd_0_pud_sel_mask                                          (0x00000001)
#define EMMC_PFUNC_NF1_nf_dd_0_pud_sel(data)                                         (0x00000001&((data)<<0))
#define EMMC_PFUNC_NF1_nf_dd_0_pud_sel_src(data)                                     ((0x00000001&(data))>>0)
#define EMMC_PFUNC_NF1_get_nf_dd_0_pud_sel(data)                                     ((0x00000001&(data))>>0)


#define EMMC_PFUNC_CR                                                                0x98012610
#define EMMC_PFUNC_CR_reg_addr                                                       "0x98012610"
#define EMMC_PFUNC_CR_reg                                                            0x98012610
#define set_EMMC_PFUNC_CR_reg(data)   (*((volatile unsigned int*) EMMC_PFUNC_CR_reg)=data)
#define get_EMMC_PFUNC_CR_reg   (*((volatile unsigned int*) EMMC_PFUNC_CR_reg))
#define EMMC_PFUNC_CR_inst_adr                                                       "0x0084"
#define EMMC_PFUNC_CR_inst                                                           0x0084
#define EMMC_PFUNC_CR_mmc_data_3_smt_shift                                           (31)
#define EMMC_PFUNC_CR_mmc_data_3_smt_mask                                            (0x80000000)
#define EMMC_PFUNC_CR_mmc_data_3_smt(data)                                           (0x80000000&((data)<<31))
#define EMMC_PFUNC_CR_mmc_data_3_smt_src(data)                                       ((0x80000000&(data))>>31)
#define EMMC_PFUNC_CR_get_mmc_data_3_smt(data)                                       ((0x80000000&(data))>>31)
#define EMMC_PFUNC_CR_mmc_data_3_pud_en_shift                                        (29)
#define EMMC_PFUNC_CR_mmc_data_3_pud_en_mask                                         (0x20000000)
#define EMMC_PFUNC_CR_mmc_data_3_pud_en(data)                                        (0x20000000&((data)<<29))
#define EMMC_PFUNC_CR_mmc_data_3_pud_en_src(data)                                    ((0x20000000&(data))>>29)
#define EMMC_PFUNC_CR_get_mmc_data_3_pud_en(data)                                    ((0x20000000&(data))>>29)
#define EMMC_PFUNC_CR_mmc_data_3_pud_sel_shift                                       (28)
#define EMMC_PFUNC_CR_mmc_data_3_pud_sel_mask                                        (0x10000000)
#define EMMC_PFUNC_CR_mmc_data_3_pud_sel(data)                                       (0x10000000&((data)<<28))
#define EMMC_PFUNC_CR_mmc_data_3_pud_sel_src(data)                                   ((0x10000000&(data))>>28)
#define EMMC_PFUNC_CR_get_mmc_data_3_pud_sel(data)                                   ((0x10000000&(data))>>28)
#define EMMC_PFUNC_CR_mmc_data_2_smt_shift                                           (27)
#define EMMC_PFUNC_CR_mmc_data_2_smt_mask                                            (0x08000000)
#define EMMC_PFUNC_CR_mmc_data_2_smt(data)                                           (0x08000000&((data)<<27))
#define EMMC_PFUNC_CR_mmc_data_2_smt_src(data)                                       ((0x08000000&(data))>>27)
#define EMMC_PFUNC_CR_get_mmc_data_2_smt(data)                                       ((0x08000000&(data))>>27)
#define EMMC_PFUNC_CR_mmc_data_2_pud_en_shift                                        (25)
#define EMMC_PFUNC_CR_mmc_data_2_pud_en_mask                                         (0x02000000)
#define EMMC_PFUNC_CR_mmc_data_2_pud_en(data)                                        (0x02000000&((data)<<25))
#define EMMC_PFUNC_CR_mmc_data_2_pud_en_src(data)                                    ((0x02000000&(data))>>25)
#define EMMC_PFUNC_CR_get_mmc_data_2_pud_en(data)                                    ((0x02000000&(data))>>25)
#define EMMC_PFUNC_CR_mmc_data_2_pud_sel_shift                                       (24)
#define EMMC_PFUNC_CR_mmc_data_2_pud_sel_mask                                        (0x01000000)
#define EMMC_PFUNC_CR_mmc_data_2_pud_sel(data)                                       (0x01000000&((data)<<24))
#define EMMC_PFUNC_CR_mmc_data_2_pud_sel_src(data)                                   ((0x01000000&(data))>>24)
#define EMMC_PFUNC_CR_get_mmc_data_2_pud_sel(data)                                   ((0x01000000&(data))>>24)
#define EMMC_PFUNC_CR_mmc_data_1_smt_shift                                           (23)
#define EMMC_PFUNC_CR_mmc_data_1_smt_mask                                            (0x00800000)
#define EMMC_PFUNC_CR_mmc_data_1_smt(data)                                           (0x00800000&((data)<<23))
#define EMMC_PFUNC_CR_mmc_data_1_smt_src(data)                                       ((0x00800000&(data))>>23)
#define EMMC_PFUNC_CR_get_mmc_data_1_smt(data)                                       ((0x00800000&(data))>>23)
#define EMMC_PFUNC_CR_mmc_data_1_pud_en_shift                                        (21)
#define EMMC_PFUNC_CR_mmc_data_1_pud_en_mask                                         (0x00200000)
#define EMMC_PFUNC_CR_mmc_data_1_pud_en(data)                                        (0x00200000&((data)<<21))
#define EMMC_PFUNC_CR_mmc_data_1_pud_en_src(data)                                    ((0x00200000&(data))>>21)
#define EMMC_PFUNC_CR_get_mmc_data_1_pud_en(data)                                    ((0x00200000&(data))>>21)
#define EMMC_PFUNC_CR_mmc_data_1_pud_sel_shift                                       (20)
#define EMMC_PFUNC_CR_mmc_data_1_pud_sel_mask                                        (0x00100000)
#define EMMC_PFUNC_CR_mmc_data_1_pud_sel(data)                                       (0x00100000&((data)<<20))
#define EMMC_PFUNC_CR_mmc_data_1_pud_sel_src(data)                                   ((0x00100000&(data))>>20)
#define EMMC_PFUNC_CR_get_mmc_data_1_pud_sel(data)                                   ((0x00100000&(data))>>20)
#define EMMC_PFUNC_CR_mmc_data_0_smt_shift                                           (19)
#define EMMC_PFUNC_CR_mmc_data_0_smt_mask                                            (0x00080000)
#define EMMC_PFUNC_CR_mmc_data_0_smt(data)                                           (0x00080000&((data)<<19))
#define EMMC_PFUNC_CR_mmc_data_0_smt_src(data)                                       ((0x00080000&(data))>>19)
#define EMMC_PFUNC_CR_get_mmc_data_0_smt(data)                                       ((0x00080000&(data))>>19)
#define EMMC_PFUNC_CR_mmc_data_0_pud_en_shift                                        (17)
#define EMMC_PFUNC_CR_mmc_data_0_pud_en_mask                                         (0x00020000)
#define EMMC_PFUNC_CR_mmc_data_0_pud_en(data)                                        (0x00020000&((data)<<17))
#define EMMC_PFUNC_CR_mmc_data_0_pud_en_src(data)                                    ((0x00020000&(data))>>17)
#define EMMC_PFUNC_CR_get_mmc_data_0_pud_en(data)                                    ((0x00020000&(data))>>17)
#define EMMC_PFUNC_CR_mmc_data_0_pud_sel_shift                                       (16)
#define EMMC_PFUNC_CR_mmc_data_0_pud_sel_mask                                        (0x00010000)
#define EMMC_PFUNC_CR_mmc_data_0_pud_sel(data)                                       (0x00010000&((data)<<16))
#define EMMC_PFUNC_CR_mmc_data_0_pud_sel_src(data)                                   ((0x00010000&(data))>>16)
#define EMMC_PFUNC_CR_get_mmc_data_0_pud_sel(data)                                   ((0x00010000&(data))>>16)
#define EMMC_PFUNC_CR_mmc_cd_smt_shift                                               (15)
#define EMMC_PFUNC_CR_mmc_cd_smt_mask                                                (0x00008000)
#define EMMC_PFUNC_CR_mmc_cd_smt(data)                                               (0x00008000&((data)<<15))
#define EMMC_PFUNC_CR_mmc_cd_smt_src(data)                                           ((0x00008000&(data))>>15)
#define EMMC_PFUNC_CR_get_mmc_cd_smt(data)                                           ((0x00008000&(data))>>15)
#define EMMC_PFUNC_CR_mmc_cd_e2_shift                                                (14)
#define EMMC_PFUNC_CR_mmc_cd_e2_mask                                                 (0x00004000)
#define EMMC_PFUNC_CR_mmc_cd_e2(data)                                                (0x00004000&((data)<<14))
#define EMMC_PFUNC_CR_mmc_cd_e2_src(data)                                            ((0x00004000&(data))>>14)
#define EMMC_PFUNC_CR_get_mmc_cd_e2(data)                                            ((0x00004000&(data))>>14)
#define EMMC_PFUNC_CR_mmc_cd_pud_en_shift                                            (13)
#define EMMC_PFUNC_CR_mmc_cd_pud_en_mask                                             (0x00002000)
#define EMMC_PFUNC_CR_mmc_cd_pud_en(data)                                            (0x00002000&((data)<<13))
#define EMMC_PFUNC_CR_mmc_cd_pud_en_src(data)                                        ((0x00002000&(data))>>13)
#define EMMC_PFUNC_CR_get_mmc_cd_pud_en(data)                                        ((0x00002000&(data))>>13)
#define EMMC_PFUNC_CR_mmc_cd_pud_sel_shift                                           (12)
#define EMMC_PFUNC_CR_mmc_cd_pud_sel_mask                                            (0x00001000)
#define EMMC_PFUNC_CR_mmc_cd_pud_sel(data)                                           (0x00001000&((data)<<12))
#define EMMC_PFUNC_CR_mmc_cd_pud_sel_src(data)                                       ((0x00001000&(data))>>12)
#define EMMC_PFUNC_CR_get_mmc_cd_pud_sel(data)                                       ((0x00001000&(data))>>12)
#define EMMC_PFUNC_CR_mmc_wp_smt_shift                                               (11)
#define EMMC_PFUNC_CR_mmc_wp_smt_mask                                                (0x00000800)
#define EMMC_PFUNC_CR_mmc_wp_smt(data)                                               (0x00000800&((data)<<11))
#define EMMC_PFUNC_CR_mmc_wp_smt_src(data)                                           ((0x00000800&(data))>>11)
#define EMMC_PFUNC_CR_get_mmc_wp_smt(data)                                           ((0x00000800&(data))>>11)
#define EMMC_PFUNC_CR_mmc_wp_e2_shift                                                (10)
#define EMMC_PFUNC_CR_mmc_wp_e2_mask                                                 (0x00000400)
#define EMMC_PFUNC_CR_mmc_wp_e2(data)                                                (0x00000400&((data)<<10))
#define EMMC_PFUNC_CR_mmc_wp_e2_src(data)                                            ((0x00000400&(data))>>10)
#define EMMC_PFUNC_CR_get_mmc_wp_e2(data)                                            ((0x00000400&(data))>>10)
#define EMMC_PFUNC_CR_mmc_wp_pud_en_shift                                            (9)
#define EMMC_PFUNC_CR_mmc_wp_pud_en_mask                                             (0x00000200)
#define EMMC_PFUNC_CR_mmc_wp_pud_en(data)                                            (0x00000200&((data)<<9))
#define EMMC_PFUNC_CR_mmc_wp_pud_en_src(data)                                        ((0x00000200&(data))>>9)
#define EMMC_PFUNC_CR_get_mmc_wp_pud_en(data)                                        ((0x00000200&(data))>>9)
#define EMMC_PFUNC_CR_mmc_wp_pud_sel_shift                                           (8)
#define EMMC_PFUNC_CR_mmc_wp_pud_sel_mask                                            (0x00000100)
#define EMMC_PFUNC_CR_mmc_wp_pud_sel(data)                                           (0x00000100&((data)<<8))
#define EMMC_PFUNC_CR_mmc_wp_pud_sel_src(data)                                       ((0x00000100&(data))>>8)
#define EMMC_PFUNC_CR_get_mmc_wp_pud_sel(data)                                       ((0x00000100&(data))>>8)
#define EMMC_PFUNC_CR_mmc_clk_smt_shift                                              (7)
#define EMMC_PFUNC_CR_mmc_clk_smt_mask                                               (0x00000080)
#define EMMC_PFUNC_CR_mmc_clk_smt(data)                                              (0x00000080&((data)<<7))
#define EMMC_PFUNC_CR_mmc_clk_smt_src(data)                                          ((0x00000080&(data))>>7)
#define EMMC_PFUNC_CR_get_mmc_clk_smt(data)                                          ((0x00000080&(data))>>7)
#define EMMC_PFUNC_CR_mmc_clk_pud_en_shift                                           (5)
#define EMMC_PFUNC_CR_mmc_clk_pud_en_mask                                            (0x00000020)
#define EMMC_PFUNC_CR_mmc_clk_pud_en(data)                                           (0x00000020&((data)<<5))
#define EMMC_PFUNC_CR_mmc_clk_pud_en_src(data)                                       ((0x00000020&(data))>>5)
#define EMMC_PFUNC_CR_get_mmc_clk_pud_en(data)                                       ((0x00000020&(data))>>5)
#define EMMC_PFUNC_CR_mmc_clk_pud_sel_shift                                          (4)
#define EMMC_PFUNC_CR_mmc_clk_pud_sel_mask                                           (0x00000010)
#define EMMC_PFUNC_CR_mmc_clk_pud_sel(data)                                          (0x00000010&((data)<<4))
#define EMMC_PFUNC_CR_mmc_clk_pud_sel_src(data)                                      ((0x00000010&(data))>>4)
#define EMMC_PFUNC_CR_get_mmc_clk_pud_sel(data)                                      ((0x00000010&(data))>>4)
#define EMMC_PFUNC_CR_mmc_cmd_smt_shift                                              (3)
#define EMMC_PFUNC_CR_mmc_cmd_smt_mask                                               (0x00000008)
#define EMMC_PFUNC_CR_mmc_cmd_smt(data)                                              (0x00000008&((data)<<3))
#define EMMC_PFUNC_CR_mmc_cmd_smt_src(data)                                          ((0x00000008&(data))>>3)
#define EMMC_PFUNC_CR_get_mmc_cmd_smt(data)                                          ((0x00000008&(data))>>3)
#define EMMC_PFUNC_CR_mmc_cmd_pud_en_shift                                           (1)
#define EMMC_PFUNC_CR_mmc_cmd_pud_en_mask                                            (0x00000002)
#define EMMC_PFUNC_CR_mmc_cmd_pud_en(data)                                           (0x00000002&((data)<<1))
#define EMMC_PFUNC_CR_mmc_cmd_pud_en_src(data)                                       ((0x00000002&(data))>>1)
#define EMMC_PFUNC_CR_get_mmc_cmd_pud_en(data)                                       ((0x00000002&(data))>>1)
#define EMMC_PFUNC_CR_mmc_cmd_pud_sel_shift                                          (0)
#define EMMC_PFUNC_CR_mmc_cmd_pud_sel_mask                                           (0x00000001)
#define EMMC_PFUNC_CR_mmc_cmd_pud_sel(data)                                          (0x00000001&((data)<<0))
#define EMMC_PFUNC_CR_mmc_cmd_pud_sel_src(data)                                      ((0x00000001&(data))>>0)
#define EMMC_PFUNC_CR_get_mmc_cmd_pud_sel(data)                                      ((0x00000001&(data))>>0)


#define EMMC_PFUNC_SDIO                                                              0x98012614
#define EMMC_PFUNC_SDIO_reg_addr                                                     "0x98012614"
#define EMMC_PFUNC_SDIO_reg                                                          0x98012614
#define set_EMMC_PFUNC_SDIO_reg(data)   (*((volatile unsigned int*) EMMC_PFUNC_SDIO_reg)=data)
#define get_EMMC_PFUNC_SDIO_reg   (*((volatile unsigned int*) EMMC_PFUNC_SDIO_reg))
#define EMMC_PFUNC_SDIO_inst_adr                                                     "0x0085"
#define EMMC_PFUNC_SDIO_inst                                                         0x0085
#define EMMC_PFUNC_SDIO_sdio_data_3_smt_shift                                        (31)
#define EMMC_PFUNC_SDIO_sdio_data_3_smt_mask                                         (0x80000000)
#define EMMC_PFUNC_SDIO_sdio_data_3_smt(data)                                        (0x80000000&((data)<<31))
#define EMMC_PFUNC_SDIO_sdio_data_3_smt_src(data)                                    ((0x80000000&(data))>>31)
#define EMMC_PFUNC_SDIO_get_sdio_data_3_smt(data)                                    ((0x80000000&(data))>>31)
#define EMMC_PFUNC_SDIO_sdio_data_3_pud_en_shift                                     (29)
#define EMMC_PFUNC_SDIO_sdio_data_3_pud_en_mask                                      (0x20000000)
#define EMMC_PFUNC_SDIO_sdio_data_3_pud_en(data)                                     (0x20000000&((data)<<29))
#define EMMC_PFUNC_SDIO_sdio_data_3_pud_en_src(data)                                 ((0x20000000&(data))>>29)
#define EMMC_PFUNC_SDIO_get_sdio_data_3_pud_en(data)                                 ((0x20000000&(data))>>29)
#define EMMC_PFUNC_SDIO_sdio_data_3_pud_sel_shift                                    (28)
#define EMMC_PFUNC_SDIO_sdio_data_3_pud_sel_mask                                     (0x10000000)
#define EMMC_PFUNC_SDIO_sdio_data_3_pud_sel(data)                                    (0x10000000&((data)<<28))
#define EMMC_PFUNC_SDIO_sdio_data_3_pud_sel_src(data)                                ((0x10000000&(data))>>28)
#define EMMC_PFUNC_SDIO_get_sdio_data_3_pud_sel(data)                                ((0x10000000&(data))>>28)
#define EMMC_PFUNC_SDIO_sdio_data_2_smt_shift                                        (27)
#define EMMC_PFUNC_SDIO_sdio_data_2_smt_mask                                         (0x08000000)
#define EMMC_PFUNC_SDIO_sdio_data_2_smt(data)                                        (0x08000000&((data)<<27))
#define EMMC_PFUNC_SDIO_sdio_data_2_smt_src(data)                                    ((0x08000000&(data))>>27)
#define EMMC_PFUNC_SDIO_get_sdio_data_2_smt(data)                                    ((0x08000000&(data))>>27)
#define EMMC_PFUNC_SDIO_sdio_data_2_pud_en_shift                                     (25)
#define EMMC_PFUNC_SDIO_sdio_data_2_pud_en_mask                                      (0x02000000)
#define EMMC_PFUNC_SDIO_sdio_data_2_pud_en(data)                                     (0x02000000&((data)<<25))
#define EMMC_PFUNC_SDIO_sdio_data_2_pud_en_src(data)                                 ((0x02000000&(data))>>25)
#define EMMC_PFUNC_SDIO_get_sdio_data_2_pud_en(data)                                 ((0x02000000&(data))>>25)
#define EMMC_PFUNC_SDIO_sdio_data_2_pud_sel_shift                                    (24)
#define EMMC_PFUNC_SDIO_sdio_data_2_pud_sel_mask                                     (0x01000000)
#define EMMC_PFUNC_SDIO_sdio_data_2_pud_sel(data)                                    (0x01000000&((data)<<24))
#define EMMC_PFUNC_SDIO_sdio_data_2_pud_sel_src(data)                                ((0x01000000&(data))>>24)
#define EMMC_PFUNC_SDIO_get_sdio_data_2_pud_sel(data)                                ((0x01000000&(data))>>24)
#define EMMC_PFUNC_SDIO_sdio_data_1_smt_shift                                        (23)
#define EMMC_PFUNC_SDIO_sdio_data_1_smt_mask                                         (0x00800000)
#define EMMC_PFUNC_SDIO_sdio_data_1_smt(data)                                        (0x00800000&((data)<<23))
#define EMMC_PFUNC_SDIO_sdio_data_1_smt_src(data)                                    ((0x00800000&(data))>>23)
#define EMMC_PFUNC_SDIO_get_sdio_data_1_smt(data)                                    ((0x00800000&(data))>>23)
#define EMMC_PFUNC_SDIO_sdio_data_1_pud_en_shift                                     (21)
#define EMMC_PFUNC_SDIO_sdio_data_1_pud_en_mask                                      (0x00200000)
#define EMMC_PFUNC_SDIO_sdio_data_1_pud_en(data)                                     (0x00200000&((data)<<21))
#define EMMC_PFUNC_SDIO_sdio_data_1_pud_en_src(data)                                 ((0x00200000&(data))>>21)
#define EMMC_PFUNC_SDIO_get_sdio_data_1_pud_en(data)                                 ((0x00200000&(data))>>21)
#define EMMC_PFUNC_SDIO_sdio_data_1_pud_sel_shift                                    (20)
#define EMMC_PFUNC_SDIO_sdio_data_1_pud_sel_mask                                     (0x00100000)
#define EMMC_PFUNC_SDIO_sdio_data_1_pud_sel(data)                                    (0x00100000&((data)<<20))
#define EMMC_PFUNC_SDIO_sdio_data_1_pud_sel_src(data)                                ((0x00100000&(data))>>20)
#define EMMC_PFUNC_SDIO_get_sdio_data_1_pud_sel(data)                                ((0x00100000&(data))>>20)
#define EMMC_PFUNC_SDIO_sdio_data_0_smt_shift                                        (19)
#define EMMC_PFUNC_SDIO_sdio_data_0_smt_mask                                         (0x00080000)
#define EMMC_PFUNC_SDIO_sdio_data_0_smt(data)                                        (0x00080000&((data)<<19))
#define EMMC_PFUNC_SDIO_sdio_data_0_smt_src(data)                                    ((0x00080000&(data))>>19)
#define EMMC_PFUNC_SDIO_get_sdio_data_0_smt(data)                                    ((0x00080000&(data))>>19)
#define EMMC_PFUNC_SDIO_sdio_data_0_pud_en_shift                                     (17)
#define EMMC_PFUNC_SDIO_sdio_data_0_pud_en_mask                                      (0x00020000)
#define EMMC_PFUNC_SDIO_sdio_data_0_pud_en(data)                                     (0x00020000&((data)<<17))
#define EMMC_PFUNC_SDIO_sdio_data_0_pud_en_src(data)                                 ((0x00020000&(data))>>17)
#define EMMC_PFUNC_SDIO_get_sdio_data_0_pud_en(data)                                 ((0x00020000&(data))>>17)
#define EMMC_PFUNC_SDIO_sdio_data_0_pud_sel_shift                                    (16)
#define EMMC_PFUNC_SDIO_sdio_data_0_pud_sel_mask                                     (0x00010000)
#define EMMC_PFUNC_SDIO_sdio_data_0_pud_sel(data)                                    (0x00010000&((data)<<16))
#define EMMC_PFUNC_SDIO_sdio_data_0_pud_sel_src(data)                                ((0x00010000&(data))>>16)
#define EMMC_PFUNC_SDIO_get_sdio_data_0_pud_sel(data)                                ((0x00010000&(data))>>16)
#define EMMC_PFUNC_SDIO_sdio_clk_smt_shift                                           (7)
#define EMMC_PFUNC_SDIO_sdio_clk_smt_mask                                            (0x00000080)
#define EMMC_PFUNC_SDIO_sdio_clk_smt(data)                                           (0x00000080&((data)<<7))
#define EMMC_PFUNC_SDIO_sdio_clk_smt_src(data)                                       ((0x00000080&(data))>>7)
#define EMMC_PFUNC_SDIO_get_sdio_clk_smt(data)                                       ((0x00000080&(data))>>7)
#define EMMC_PFUNC_SDIO_sdio_clk_pud_en_shift                                        (5)
#define EMMC_PFUNC_SDIO_sdio_clk_pud_en_mask                                         (0x00000020)
#define EMMC_PFUNC_SDIO_sdio_clk_pud_en(data)                                        (0x00000020&((data)<<5))
#define EMMC_PFUNC_SDIO_sdio_clk_pud_en_src(data)                                    ((0x00000020&(data))>>5)
#define EMMC_PFUNC_SDIO_get_sdio_clk_pud_en(data)                                    ((0x00000020&(data))>>5)
#define EMMC_PFUNC_SDIO_sdio_clk_pud_sel_shift                                       (4)
#define EMMC_PFUNC_SDIO_sdio_clk_pud_sel_mask                                        (0x00000010)
#define EMMC_PFUNC_SDIO_sdio_clk_pud_sel(data)                                       (0x00000010&((data)<<4))
#define EMMC_PFUNC_SDIO_sdio_clk_pud_sel_src(data)                                   ((0x00000010&(data))>>4)
#define EMMC_PFUNC_SDIO_get_sdio_clk_pud_sel(data)                                   ((0x00000010&(data))>>4)
#define EMMC_PFUNC_SDIO_sdio_cmd_smt_shift                                           (3)
#define EMMC_PFUNC_SDIO_sdio_cmd_smt_mask                                            (0x00000008)
#define EMMC_PFUNC_SDIO_sdio_cmd_smt(data)                                           (0x00000008&((data)<<3))
#define EMMC_PFUNC_SDIO_sdio_cmd_smt_src(data)                                       ((0x00000008&(data))>>3)
#define EMMC_PFUNC_SDIO_get_sdio_cmd_smt(data)                                       ((0x00000008&(data))>>3)
#define EMMC_PFUNC_SDIO_sdio_cmd_pud_en_shift                                        (1)
#define EMMC_PFUNC_SDIO_sdio_cmd_pud_en_mask                                         (0x00000002)
#define EMMC_PFUNC_SDIO_sdio_cmd_pud_en(data)                                        (0x00000002&((data)<<1))
#define EMMC_PFUNC_SDIO_sdio_cmd_pud_en_src(data)                                    ((0x00000002&(data))>>1)
#define EMMC_PFUNC_SDIO_get_sdio_cmd_pud_en(data)                                    ((0x00000002&(data))>>1)
#define EMMC_PFUNC_SDIO_sdio_cmd_pud_sel_shift                                       (0)
#define EMMC_PFUNC_SDIO_sdio_cmd_pud_sel_mask                                        (0x00000001)
#define EMMC_PFUNC_SDIO_sdio_cmd_pud_sel(data)                                       (0x00000001&((data)<<0))
#define EMMC_PFUNC_SDIO_sdio_cmd_pud_sel_src(data)                                   ((0x00000001&(data))>>0)
#define EMMC_PFUNC_SDIO_get_sdio_cmd_pud_sel(data)                                   ((0x00000001&(data))>>0)


#define EMMC_PFUNC_NF2                                                               0x98012618
#define EMMC_PFUNC_NF2_reg_addr                                                      "0x98012618"
#define EMMC_PFUNC_NF2_reg                                                           0x98012618
#define set_EMMC_PFUNC_NF2_reg(data)   (*((volatile unsigned int*) EMMC_PFUNC_NF2_reg)=data)
#define get_EMMC_PFUNC_NF2_reg   (*((volatile unsigned int*) EMMC_PFUNC_NF2_reg))
#define EMMC_PFUNC_NF2_inst_adr                                                      "0x0086"
#define EMMC_PFUNC_NF2_inst                                                          0x0086
#define EMMC_PFUNC_NF2_prob_3_smt_shift                                              (27)
#define EMMC_PFUNC_NF2_prob_3_smt_mask                                               (0x08000000)
#define EMMC_PFUNC_NF2_prob_3_smt(data)                                              (0x08000000&((data)<<27))
#define EMMC_PFUNC_NF2_prob_3_smt_src(data)                                          ((0x08000000&(data))>>27)
#define EMMC_PFUNC_NF2_get_prob_3_smt(data)                                          ((0x08000000&(data))>>27)
#define EMMC_PFUNC_NF2_prob_3_e2_shift                                               (26)
#define EMMC_PFUNC_NF2_prob_3_e2_mask                                                (0x04000000)
#define EMMC_PFUNC_NF2_prob_3_e2(data)                                               (0x04000000&((data)<<26))
#define EMMC_PFUNC_NF2_prob_3_e2_src(data)                                           ((0x04000000&(data))>>26)
#define EMMC_PFUNC_NF2_get_prob_3_e2(data)                                           ((0x04000000&(data))>>26)
#define EMMC_PFUNC_NF2_prob_3_pud_en_shift                                           (25)
#define EMMC_PFUNC_NF2_prob_3_pud_en_mask                                            (0x02000000)
#define EMMC_PFUNC_NF2_prob_3_pud_en(data)                                           (0x02000000&((data)<<25))
#define EMMC_PFUNC_NF2_prob_3_pud_en_src(data)                                       ((0x02000000&(data))>>25)
#define EMMC_PFUNC_NF2_get_prob_3_pud_en(data)                                       ((0x02000000&(data))>>25)
#define EMMC_PFUNC_NF2_prob_3_pud_sel_shift                                          (24)
#define EMMC_PFUNC_NF2_prob_3_pud_sel_mask                                           (0x01000000)
#define EMMC_PFUNC_NF2_prob_3_pud_sel(data)                                          (0x01000000&((data)<<24))
#define EMMC_PFUNC_NF2_prob_3_pud_sel_src(data)                                      ((0x01000000&(data))>>24)
#define EMMC_PFUNC_NF2_get_prob_3_pud_sel(data)                                      ((0x01000000&(data))>>24)
#define EMMC_PFUNC_NF2_prob_2_smt_shift                                              (23)
#define EMMC_PFUNC_NF2_prob_2_smt_mask                                               (0x00800000)
#define EMMC_PFUNC_NF2_prob_2_smt(data)                                              (0x00800000&((data)<<23))
#define EMMC_PFUNC_NF2_prob_2_smt_src(data)                                          ((0x00800000&(data))>>23)
#define EMMC_PFUNC_NF2_get_prob_2_smt(data)                                          ((0x00800000&(data))>>23)
#define EMMC_PFUNC_NF2_prob_2_e2_shift                                               (22)
#define EMMC_PFUNC_NF2_prob_2_e2_mask                                                (0x00400000)
#define EMMC_PFUNC_NF2_prob_2_e2(data)                                               (0x00400000&((data)<<22))
#define EMMC_PFUNC_NF2_prob_2_e2_src(data)                                           ((0x00400000&(data))>>22)
#define EMMC_PFUNC_NF2_get_prob_2_e2(data)                                           ((0x00400000&(data))>>22)
#define EMMC_PFUNC_NF2_prob_2_pud_en_shift                                           (21)
#define EMMC_PFUNC_NF2_prob_2_pud_en_mask                                            (0x00200000)
#define EMMC_PFUNC_NF2_prob_2_pud_en(data)                                           (0x00200000&((data)<<21))
#define EMMC_PFUNC_NF2_prob_2_pud_en_src(data)                                       ((0x00200000&(data))>>21)
#define EMMC_PFUNC_NF2_get_prob_2_pud_en(data)                                       ((0x00200000&(data))>>21)
#define EMMC_PFUNC_NF2_prob_2_pud_sel_shift                                          (20)
#define EMMC_PFUNC_NF2_prob_2_pud_sel_mask                                           (0x00100000)
#define EMMC_PFUNC_NF2_prob_2_pud_sel(data)                                          (0x00100000&((data)<<20))
#define EMMC_PFUNC_NF2_prob_2_pud_sel_src(data)                                      ((0x00100000&(data))>>20)
#define EMMC_PFUNC_NF2_get_prob_2_pud_sel(data)                                      ((0x00100000&(data))>>20)
#define EMMC_PFUNC_NF2_prob_1_smt_shift                                              (19)
#define EMMC_PFUNC_NF2_prob_1_smt_mask                                               (0x00080000)
#define EMMC_PFUNC_NF2_prob_1_smt(data)                                              (0x00080000&((data)<<19))
#define EMMC_PFUNC_NF2_prob_1_smt_src(data)                                          ((0x00080000&(data))>>19)
#define EMMC_PFUNC_NF2_get_prob_1_smt(data)                                          ((0x00080000&(data))>>19)
#define EMMC_PFUNC_NF2_prob_1_e2_shift                                               (18)
#define EMMC_PFUNC_NF2_prob_1_e2_mask                                                (0x00040000)
#define EMMC_PFUNC_NF2_prob_1_e2(data)                                               (0x00040000&((data)<<18))
#define EMMC_PFUNC_NF2_prob_1_e2_src(data)                                           ((0x00040000&(data))>>18)
#define EMMC_PFUNC_NF2_get_prob_1_e2(data)                                           ((0x00040000&(data))>>18)
#define EMMC_PFUNC_NF2_prob_1_pud_en_shift                                           (17)
#define EMMC_PFUNC_NF2_prob_1_pud_en_mask                                            (0x00020000)
#define EMMC_PFUNC_NF2_prob_1_pud_en(data)                                           (0x00020000&((data)<<17))
#define EMMC_PFUNC_NF2_prob_1_pud_en_src(data)                                       ((0x00020000&(data))>>17)
#define EMMC_PFUNC_NF2_get_prob_1_pud_en(data)                                       ((0x00020000&(data))>>17)
#define EMMC_PFUNC_NF2_prob_1_pud_sel_shift                                          (16)
#define EMMC_PFUNC_NF2_prob_1_pud_sel_mask                                           (0x00010000)
#define EMMC_PFUNC_NF2_prob_1_pud_sel(data)                                          (0x00010000&((data)<<16))
#define EMMC_PFUNC_NF2_prob_1_pud_sel_src(data)                                      ((0x00010000&(data))>>16)
#define EMMC_PFUNC_NF2_get_prob_1_pud_sel(data)                                      ((0x00010000&(data))>>16)
#define EMMC_PFUNC_NF2_prob_0_smt_shift                                              (15)
#define EMMC_PFUNC_NF2_prob_0_smt_mask                                               (0x00008000)
#define EMMC_PFUNC_NF2_prob_0_smt(data)                                              (0x00008000&((data)<<15))
#define EMMC_PFUNC_NF2_prob_0_smt_src(data)                                          ((0x00008000&(data))>>15)
#define EMMC_PFUNC_NF2_get_prob_0_smt(data)                                          ((0x00008000&(data))>>15)
#define EMMC_PFUNC_NF2_prob_0_e2_shift                                               (14)
#define EMMC_PFUNC_NF2_prob_0_e2_mask                                                (0x00004000)
#define EMMC_PFUNC_NF2_prob_0_e2(data)                                               (0x00004000&((data)<<14))
#define EMMC_PFUNC_NF2_prob_0_e2_src(data)                                           ((0x00004000&(data))>>14)
#define EMMC_PFUNC_NF2_get_prob_0_e2(data)                                           ((0x00004000&(data))>>14)
#define EMMC_PFUNC_NF2_prob_0_pud_en_shift                                           (13)
#define EMMC_PFUNC_NF2_prob_0_pud_en_mask                                            (0x00002000)
#define EMMC_PFUNC_NF2_prob_0_pud_en(data)                                           (0x00002000&((data)<<13))
#define EMMC_PFUNC_NF2_prob_0_pud_en_src(data)                                       ((0x00002000&(data))>>13)
#define EMMC_PFUNC_NF2_get_prob_0_pud_en(data)                                       ((0x00002000&(data))>>13)
#define EMMC_PFUNC_NF2_prob_0_pud_sel_shift                                          (12)
#define EMMC_PFUNC_NF2_prob_0_pud_sel_mask                                           (0x00001000)
#define EMMC_PFUNC_NF2_prob_0_pud_sel(data)                                          (0x00001000&((data)<<12))
#define EMMC_PFUNC_NF2_prob_0_pud_sel_src(data)                                      ((0x00001000&(data))>>12)
#define EMMC_PFUNC_NF2_get_prob_0_pud_sel(data)                                      ((0x00001000&(data))>>12)
#define EMMC_PFUNC_NF2_pcie_clkreq_1_smt_shift                                       (11)
#define EMMC_PFUNC_NF2_pcie_clkreq_1_smt_mask                                        (0x00000800)
#define EMMC_PFUNC_NF2_pcie_clkreq_1_smt(data)                                       (0x00000800&((data)<<11))
#define EMMC_PFUNC_NF2_pcie_clkreq_1_smt_src(data)                                   ((0x00000800&(data))>>11)
#define EMMC_PFUNC_NF2_get_pcie_clkreq_1_smt(data)                                   ((0x00000800&(data))>>11)
#define EMMC_PFUNC_NF2_pcie_clkreq_1_e2_shift                                        (10)
#define EMMC_PFUNC_NF2_pcie_clkreq_1_e2_mask                                         (0x00000400)
#define EMMC_PFUNC_NF2_pcie_clkreq_1_e2(data)                                        (0x00000400&((data)<<10))
#define EMMC_PFUNC_NF2_pcie_clkreq_1_e2_src(data)                                    ((0x00000400&(data))>>10)
#define EMMC_PFUNC_NF2_get_pcie_clkreq_1_e2(data)                                    ((0x00000400&(data))>>10)
#define EMMC_PFUNC_NF2_pcie_clkreq_1_pud_en_shift                                    (9)
#define EMMC_PFUNC_NF2_pcie_clkreq_1_pud_en_mask                                     (0x00000200)
#define EMMC_PFUNC_NF2_pcie_clkreq_1_pud_en(data)                                    (0x00000200&((data)<<9))
#define EMMC_PFUNC_NF2_pcie_clkreq_1_pud_en_src(data)                                ((0x00000200&(data))>>9)
#define EMMC_PFUNC_NF2_get_pcie_clkreq_1_pud_en(data)                                ((0x00000200&(data))>>9)
#define EMMC_PFUNC_NF2_pcie_clkreq_1_pud_sel_shift                                   (8)
#define EMMC_PFUNC_NF2_pcie_clkreq_1_pud_sel_mask                                    (0x00000100)
#define EMMC_PFUNC_NF2_pcie_clkreq_1_pud_sel(data)                                   (0x00000100&((data)<<8))
#define EMMC_PFUNC_NF2_pcie_clkreq_1_pud_sel_src(data)                               ((0x00000100&(data))>>8)
#define EMMC_PFUNC_NF2_get_pcie_clkreq_1_pud_sel(data)                               ((0x00000100&(data))>>8)
#define EMMC_PFUNC_NF2_pcie_clkreq_0_smt_shift                                       (7)
#define EMMC_PFUNC_NF2_pcie_clkreq_0_smt_mask                                        (0x00000080)
#define EMMC_PFUNC_NF2_pcie_clkreq_0_smt(data)                                       (0x00000080&((data)<<7))
#define EMMC_PFUNC_NF2_pcie_clkreq_0_smt_src(data)                                   ((0x00000080&(data))>>7)
#define EMMC_PFUNC_NF2_get_pcie_clkreq_0_smt(data)                                   ((0x00000080&(data))>>7)
#define EMMC_PFUNC_NF2_pcie_clkreq_0_e2_shift                                        (6)
#define EMMC_PFUNC_NF2_pcie_clkreq_0_e2_mask                                         (0x00000040)
#define EMMC_PFUNC_NF2_pcie_clkreq_0_e2(data)                                        (0x00000040&((data)<<6))
#define EMMC_PFUNC_NF2_pcie_clkreq_0_e2_src(data)                                    ((0x00000040&(data))>>6)
#define EMMC_PFUNC_NF2_get_pcie_clkreq_0_e2(data)                                    ((0x00000040&(data))>>6)
#define EMMC_PFUNC_NF2_pcie_clkreq_0_pud_en_shift                                    (5)
#define EMMC_PFUNC_NF2_pcie_clkreq_0_pud_en_mask                                     (0x00000020)
#define EMMC_PFUNC_NF2_pcie_clkreq_0_pud_en(data)                                    (0x00000020&((data)<<5))
#define EMMC_PFUNC_NF2_pcie_clkreq_0_pud_en_src(data)                                ((0x00000020&(data))>>5)
#define EMMC_PFUNC_NF2_get_pcie_clkreq_0_pud_en(data)                                ((0x00000020&(data))>>5)
#define EMMC_PFUNC_NF2_pcie_clkreq_0_pud_sel_shift                                   (4)
#define EMMC_PFUNC_NF2_pcie_clkreq_0_pud_sel_mask                                    (0x00000010)
#define EMMC_PFUNC_NF2_pcie_clkreq_0_pud_sel(data)                                   (0x00000010&((data)<<4))
#define EMMC_PFUNC_NF2_pcie_clkreq_0_pud_sel_src(data)                               ((0x00000010&(data))>>4)
#define EMMC_PFUNC_NF2_get_pcie_clkreq_0_pud_sel(data)                               ((0x00000010&(data))>>4)
#define EMMC_PFUNC_NF2_emmc_dd_sb_smt_shift                                          (3)
#define EMMC_PFUNC_NF2_emmc_dd_sb_smt_mask                                           (0x00000008)
#define EMMC_PFUNC_NF2_emmc_dd_sb_smt(data)                                          (0x00000008&((data)<<3))
#define EMMC_PFUNC_NF2_emmc_dd_sb_smt_src(data)                                      ((0x00000008&(data))>>3)
#define EMMC_PFUNC_NF2_get_emmc_dd_sb_smt(data)                                      ((0x00000008&(data))>>3)
#define EMMC_PFUNC_NF2_emmc_dd_sb_pud_en_shift                                       (1)
#define EMMC_PFUNC_NF2_emmc_dd_sb_pud_en_mask                                        (0x00000002)
#define EMMC_PFUNC_NF2_emmc_dd_sb_pud_en(data)                                       (0x00000002&((data)<<1))
#define EMMC_PFUNC_NF2_emmc_dd_sb_pud_en_src(data)                                   ((0x00000002&(data))>>1)
#define EMMC_PFUNC_NF2_get_emmc_dd_sb_pud_en(data)                                   ((0x00000002&(data))>>1)
#define EMMC_PFUNC_NF2_emmc_dd_sb_pud_sel_shift                                      (0)
#define EMMC_PFUNC_NF2_emmc_dd_sb_pud_sel_mask                                       (0x00000001)
#define EMMC_PFUNC_NF2_emmc_dd_sb_pud_sel(data)                                      (0x00000001&((data)<<0))
#define EMMC_PFUNC_NF2_emmc_dd_sb_pud_sel_src(data)                                  ((0x00000001&(data))>>0)
#define EMMC_PFUNC_NF2_get_emmc_dd_sb_pud_sel(data)                                  ((0x00000001&(data))>>0)


#define EMMC_MUXPAD2                                                                 0x9801261C
#define EMMC_MUXPAD2_reg_addr                                                        "0x9801261C"
#define EMMC_MUXPAD2_reg                                                             0x9801261C
#define set_EMMC_MUXPAD2_reg(data)   (*((volatile unsigned int*) EMMC_MUXPAD2_reg)=data)
#define get_EMMC_MUXPAD2_reg   (*((volatile unsigned int*) EMMC_MUXPAD2_reg))
#define EMMC_MUXPAD2_inst_adr                                                        "0x0087"
#define EMMC_MUXPAD2_inst                                                            0x0087
#define EMMC_MUXPAD2_prob_3_shift                                                    (12)
#define EMMC_MUXPAD2_prob_3_mask                                                     (0x00003000)
#define EMMC_MUXPAD2_prob_3(data)                                                    (0x00003000&((data)<<12))
#define EMMC_MUXPAD2_prob_3_src(data)                                                ((0x00003000&(data))>>12)
#define EMMC_MUXPAD2_get_prob_3(data)                                                ((0x00003000&(data))>>12)
#define EMMC_MUXPAD2_prob_2_shift                                                    (10)
#define EMMC_MUXPAD2_prob_2_mask                                                     (0x00000C00)
#define EMMC_MUXPAD2_prob_2(data)                                                    (0x00000C00&((data)<<10))
#define EMMC_MUXPAD2_prob_2_src(data)                                                ((0x00000C00&(data))>>10)
#define EMMC_MUXPAD2_get_prob_2(data)                                                ((0x00000C00&(data))>>10)
#define EMMC_MUXPAD2_prob_1_shift                                                    (8)
#define EMMC_MUXPAD2_prob_1_mask                                                     (0x00000300)
#define EMMC_MUXPAD2_prob_1(data)                                                    (0x00000300&((data)<<8))
#define EMMC_MUXPAD2_prob_1_src(data)                                                ((0x00000300&(data))>>8)
#define EMMC_MUXPAD2_get_prob_1(data)                                                ((0x00000300&(data))>>8)
#define EMMC_MUXPAD2_prob_0_shift                                                    (6)
#define EMMC_MUXPAD2_prob_0_mask                                                     (0x000000C0)
#define EMMC_MUXPAD2_prob_0(data)                                                    (0x000000C0&((data)<<6))
#define EMMC_MUXPAD2_prob_0_src(data)                                                ((0x000000C0&(data))>>6)
#define EMMC_MUXPAD2_get_prob_0(data)                                                ((0x000000C0&(data))>>6)
#define EMMC_MUXPAD2_pcie_clkreq_1_shift                                             (4)
#define EMMC_MUXPAD2_pcie_clkreq_1_mask                                              (0x00000030)
#define EMMC_MUXPAD2_pcie_clkreq_1(data)                                             (0x00000030&((data)<<4))
#define EMMC_MUXPAD2_pcie_clkreq_1_src(data)                                         ((0x00000030&(data))>>4)
#define EMMC_MUXPAD2_get_pcie_clkreq_1(data)                                         ((0x00000030&(data))>>4)
#define EMMC_MUXPAD2_pcie_clkreq_0_shift                                             (2)
#define EMMC_MUXPAD2_pcie_clkreq_0_mask                                              (0x0000000C)
#define EMMC_MUXPAD2_pcie_clkreq_0(data)                                             (0x0000000C&((data)<<2))
#define EMMC_MUXPAD2_pcie_clkreq_0_src(data)                                         ((0x0000000C&(data))>>2)
#define EMMC_MUXPAD2_get_pcie_clkreq_0(data)                                         ((0x0000000C&(data))>>2)
#define EMMC_MUXPAD2_sdio_loc_shift                                                  (0)
#define EMMC_MUXPAD2_sdio_loc_mask                                                   (0x00000003)
#define EMMC_MUXPAD2_sdio_loc(data)                                                  (0x00000003&((data)<<0))
#define EMMC_MUXPAD2_sdio_loc_src(data)                                              ((0x00000003&(data))>>0)
#define EMMC_MUXPAD2_get_sdio_loc(data)                                              ((0x00000003&(data))>>0)


#define EMMC_PDRIVE_NF0                                                              0x98012620
#define EMMC_PDRIVE_NF0_reg_addr                                                     "0x98012620"
#define EMMC_PDRIVE_NF0_reg                                                          0x98012620
#define set_EMMC_PDRIVE_NF0_reg(data)   (*((volatile unsigned int*) EMMC_PDRIVE_NF0_reg)=data)
#define get_EMMC_PDRIVE_NF0_reg   (*((volatile unsigned int*) EMMC_PDRIVE_NF0_reg))
#define EMMC_PDRIVE_NF0_inst_adr                                                     "0x0088"
#define EMMC_PDRIVE_NF0_inst                                                         0x0088
#define EMMC_PDRIVE_NF0_nf_dqs_pdrive_shift                                          (28)
#define EMMC_PDRIVE_NF0_nf_dqs_pdrive_mask                                           (0xF0000000)
#define EMMC_PDRIVE_NF0_nf_dqs_pdrive(data)                                          (0xF0000000&((data)<<28))
#define EMMC_PDRIVE_NF0_nf_dqs_pdrive_src(data)                                      ((0xF0000000&(data))>>28)
#define EMMC_PDRIVE_NF0_get_nf_dqs_pdrive(data)                                      ((0xF0000000&(data))>>28)
#define EMMC_PDRIVE_NF0_nf_dqs_ndrive_shift                                          (24)
#define EMMC_PDRIVE_NF0_nf_dqs_ndrive_mask                                           (0x0F000000)
#define EMMC_PDRIVE_NF0_nf_dqs_ndrive(data)                                          (0x0F000000&((data)<<24))
#define EMMC_PDRIVE_NF0_nf_dqs_ndrive_src(data)                                      ((0x0F000000&(data))>>24)
#define EMMC_PDRIVE_NF0_get_nf_dqs_ndrive(data)                                      ((0x0F000000&(data))>>24)
#define EMMC_PDRIVE_NF0_nf_rdy_pdrive_shift                                          (20)
#define EMMC_PDRIVE_NF0_nf_rdy_pdrive_mask                                           (0x00F00000)
#define EMMC_PDRIVE_NF0_nf_rdy_pdrive(data)                                          (0x00F00000&((data)<<20))
#define EMMC_PDRIVE_NF0_nf_rdy_pdrive_src(data)                                      ((0x00F00000&(data))>>20)
#define EMMC_PDRIVE_NF0_get_nf_rdy_pdrive(data)                                      ((0x00F00000&(data))>>20)
#define EMMC_PDRIVE_NF0_nf_rdy_ndrive_shift                                          (16)
#define EMMC_PDRIVE_NF0_nf_rdy_ndrive_mask                                           (0x000F0000)
#define EMMC_PDRIVE_NF0_nf_rdy_ndrive(data)                                          (0x000F0000&((data)<<16))
#define EMMC_PDRIVE_NF0_nf_rdy_ndrive_src(data)                                      ((0x000F0000&(data))>>16)
#define EMMC_PDRIVE_NF0_get_nf_rdy_ndrive(data)                                      ((0x000F0000&(data))>>16)
#define EMMC_PDRIVE_NF0_nf_ce_n_0_pdrive_shift                                       (12)
#define EMMC_PDRIVE_NF0_nf_ce_n_0_pdrive_mask                                        (0x0000F000)
#define EMMC_PDRIVE_NF0_nf_ce_n_0_pdrive(data)                                       (0x0000F000&((data)<<12))
#define EMMC_PDRIVE_NF0_nf_ce_n_0_pdrive_src(data)                                   ((0x0000F000&(data))>>12)
#define EMMC_PDRIVE_NF0_get_nf_ce_n_0_pdrive(data)                                   ((0x0000F000&(data))>>12)
#define EMMC_PDRIVE_NF0_nf_ce_n_0_ndrive_shift                                       (8)
#define EMMC_PDRIVE_NF0_nf_ce_n_0_ndrive_mask                                        (0x00000F00)
#define EMMC_PDRIVE_NF0_nf_ce_n_0_ndrive(data)                                       (0x00000F00&((data)<<8))
#define EMMC_PDRIVE_NF0_nf_ce_n_0_ndrive_src(data)                                   ((0x00000F00&(data))>>8)
#define EMMC_PDRIVE_NF0_get_nf_ce_n_0_ndrive(data)                                   ((0x00000F00&(data))>>8)
#define EMMC_PDRIVE_NF0_nf_ce_n_1_pdrive_shift                                       (4)
#define EMMC_PDRIVE_NF0_nf_ce_n_1_pdrive_mask                                        (0x000000F0)
#define EMMC_PDRIVE_NF0_nf_ce_n_1_pdrive(data)                                       (0x000000F0&((data)<<4))
#define EMMC_PDRIVE_NF0_nf_ce_n_1_pdrive_src(data)                                   ((0x000000F0&(data))>>4)
#define EMMC_PDRIVE_NF0_get_nf_ce_n_1_pdrive(data)                                   ((0x000000F0&(data))>>4)
#define EMMC_PDRIVE_NF0_nf_ce_n_1_ndrive_shift                                       (0)
#define EMMC_PDRIVE_NF0_nf_ce_n_1_ndrive_mask                                        (0x0000000F)
#define EMMC_PDRIVE_NF0_nf_ce_n_1_ndrive(data)                                       (0x0000000F&((data)<<0))
#define EMMC_PDRIVE_NF0_nf_ce_n_1_ndrive_src(data)                                   ((0x0000000F&(data))>>0)
#define EMMC_PDRIVE_NF0_get_nf_ce_n_1_ndrive(data)                                   ((0x0000000F&(data))>>0)


#define EMMC_PDRIVE_NF1                                                              0x98012624
#define EMMC_PDRIVE_NF1_reg_addr                                                     "0x98012624"
#define EMMC_PDRIVE_NF1_reg                                                          0x98012624
#define set_EMMC_PDRIVE_NF1_reg(data)   (*((volatile unsigned int*) EMMC_PDRIVE_NF1_reg)=data)
#define get_EMMC_PDRIVE_NF1_reg   (*((volatile unsigned int*) EMMC_PDRIVE_NF1_reg))
#define EMMC_PDRIVE_NF1_inst_adr                                                     "0x0089"
#define EMMC_PDRIVE_NF1_inst                                                         0x0089
#define EMMC_PDRIVE_NF1_nf_dd_3_pdrive_shift                                         (28)
#define EMMC_PDRIVE_NF1_nf_dd_3_pdrive_mask                                          (0xF0000000)
#define EMMC_PDRIVE_NF1_nf_dd_3_pdrive(data)                                         (0xF0000000&((data)<<28))
#define EMMC_PDRIVE_NF1_nf_dd_3_pdrive_src(data)                                     ((0xF0000000&(data))>>28)
#define EMMC_PDRIVE_NF1_get_nf_dd_3_pdrive(data)                                     ((0xF0000000&(data))>>28)
#define EMMC_PDRIVE_NF1_nf_dd_3_ndrive_shift                                         (24)
#define EMMC_PDRIVE_NF1_nf_dd_3_ndrive_mask                                          (0x0F000000)
#define EMMC_PDRIVE_NF1_nf_dd_3_ndrive(data)                                         (0x0F000000&((data)<<24))
#define EMMC_PDRIVE_NF1_nf_dd_3_ndrive_src(data)                                     ((0x0F000000&(data))>>24)
#define EMMC_PDRIVE_NF1_get_nf_dd_3_ndrive(data)                                     ((0x0F000000&(data))>>24)
#define EMMC_PDRIVE_NF1_nf_dd_2_pdrive_shift                                         (20)
#define EMMC_PDRIVE_NF1_nf_dd_2_pdrive_mask                                          (0x00F00000)
#define EMMC_PDRIVE_NF1_nf_dd_2_pdrive(data)                                         (0x00F00000&((data)<<20))
#define EMMC_PDRIVE_NF1_nf_dd_2_pdrive_src(data)                                     ((0x00F00000&(data))>>20)
#define EMMC_PDRIVE_NF1_get_nf_dd_2_pdrive(data)                                     ((0x00F00000&(data))>>20)
#define EMMC_PDRIVE_NF1_nf_dd_2_ndrive_shift                                         (16)
#define EMMC_PDRIVE_NF1_nf_dd_2_ndrive_mask                                          (0x000F0000)
#define EMMC_PDRIVE_NF1_nf_dd_2_ndrive(data)                                         (0x000F0000&((data)<<16))
#define EMMC_PDRIVE_NF1_nf_dd_2_ndrive_src(data)                                     ((0x000F0000&(data))>>16)
#define EMMC_PDRIVE_NF1_get_nf_dd_2_ndrive(data)                                     ((0x000F0000&(data))>>16)
#define EMMC_PDRIVE_NF1_nf_dd_1_pdrive_shift                                         (12)
#define EMMC_PDRIVE_NF1_nf_dd_1_pdrive_mask                                          (0x0000F000)
#define EMMC_PDRIVE_NF1_nf_dd_1_pdrive(data)                                         (0x0000F000&((data)<<12))
#define EMMC_PDRIVE_NF1_nf_dd_1_pdrive_src(data)                                     ((0x0000F000&(data))>>12)
#define EMMC_PDRIVE_NF1_get_nf_dd_1_pdrive(data)                                     ((0x0000F000&(data))>>12)
#define EMMC_PDRIVE_NF1_nf_dd_1_ndrive_shift                                         (8)
#define EMMC_PDRIVE_NF1_nf_dd_1_ndrive_mask                                          (0x00000F00)
#define EMMC_PDRIVE_NF1_nf_dd_1_ndrive(data)                                         (0x00000F00&((data)<<8))
#define EMMC_PDRIVE_NF1_nf_dd_1_ndrive_src(data)                                     ((0x00000F00&(data))>>8)
#define EMMC_PDRIVE_NF1_get_nf_dd_1_ndrive(data)                                     ((0x00000F00&(data))>>8)
#define EMMC_PDRIVE_NF1_nf_dd_0_pdrive_shift                                         (4)
#define EMMC_PDRIVE_NF1_nf_dd_0_pdrive_mask                                          (0x000000F0)
#define EMMC_PDRIVE_NF1_nf_dd_0_pdrive(data)                                         (0x000000F0&((data)<<4))
#define EMMC_PDRIVE_NF1_nf_dd_0_pdrive_src(data)                                     ((0x000000F0&(data))>>4)
#define EMMC_PDRIVE_NF1_get_nf_dd_0_pdrive(data)                                     ((0x000000F0&(data))>>4)
#define EMMC_PDRIVE_NF1_nf_dd_0_ndrive_shift                                         (0)
#define EMMC_PDRIVE_NF1_nf_dd_0_ndrive_mask                                          (0x0000000F)
#define EMMC_PDRIVE_NF1_nf_dd_0_ndrive(data)                                         (0x0000000F&((data)<<0))
#define EMMC_PDRIVE_NF1_nf_dd_0_ndrive_src(data)                                     ((0x0000000F&(data))>>0)
#define EMMC_PDRIVE_NF1_get_nf_dd_0_ndrive(data)                                     ((0x0000000F&(data))>>0)


#define EMMC_PDRIVE_NF2                                                              0x98012628
#define EMMC_PDRIVE_NF2_reg_addr                                                     "0x98012628"
#define EMMC_PDRIVE_NF2_reg                                                          0x98012628
#define set_EMMC_PDRIVE_NF2_reg(data)   (*((volatile unsigned int*) EMMC_PDRIVE_NF2_reg)=data)
#define get_EMMC_PDRIVE_NF2_reg   (*((volatile unsigned int*) EMMC_PDRIVE_NF2_reg))
#define EMMC_PDRIVE_NF2_inst_adr                                                     "0x008A"
#define EMMC_PDRIVE_NF2_inst                                                         0x008A
#define EMMC_PDRIVE_NF2_nf_dd_7_pdrive_shift                                         (28)
#define EMMC_PDRIVE_NF2_nf_dd_7_pdrive_mask                                          (0xF0000000)
#define EMMC_PDRIVE_NF2_nf_dd_7_pdrive(data)                                         (0xF0000000&((data)<<28))
#define EMMC_PDRIVE_NF2_nf_dd_7_pdrive_src(data)                                     ((0xF0000000&(data))>>28)
#define EMMC_PDRIVE_NF2_get_nf_dd_7_pdrive(data)                                     ((0xF0000000&(data))>>28)
#define EMMC_PDRIVE_NF2_nf_dd_7_ndrive_shift                                         (24)
#define EMMC_PDRIVE_NF2_nf_dd_7_ndrive_mask                                          (0x0F000000)
#define EMMC_PDRIVE_NF2_nf_dd_7_ndrive(data)                                         (0x0F000000&((data)<<24))
#define EMMC_PDRIVE_NF2_nf_dd_7_ndrive_src(data)                                     ((0x0F000000&(data))>>24)
#define EMMC_PDRIVE_NF2_get_nf_dd_7_ndrive(data)                                     ((0x0F000000&(data))>>24)
#define EMMC_PDRIVE_NF2_nf_dd_6_pdrive_shift                                         (20)
#define EMMC_PDRIVE_NF2_nf_dd_6_pdrive_mask                                          (0x00F00000)
#define EMMC_PDRIVE_NF2_nf_dd_6_pdrive(data)                                         (0x00F00000&((data)<<20))
#define EMMC_PDRIVE_NF2_nf_dd_6_pdrive_src(data)                                     ((0x00F00000&(data))>>20)
#define EMMC_PDRIVE_NF2_get_nf_dd_6_pdrive(data)                                     ((0x00F00000&(data))>>20)
#define EMMC_PDRIVE_NF2_nf_dd_6_ndrive_shift                                         (16)
#define EMMC_PDRIVE_NF2_nf_dd_6_ndrive_mask                                          (0x000F0000)
#define EMMC_PDRIVE_NF2_nf_dd_6_ndrive(data)                                         (0x000F0000&((data)<<16))
#define EMMC_PDRIVE_NF2_nf_dd_6_ndrive_src(data)                                     ((0x000F0000&(data))>>16)
#define EMMC_PDRIVE_NF2_get_nf_dd_6_ndrive(data)                                     ((0x000F0000&(data))>>16)
#define EMMC_PDRIVE_NF2_nf_dd_5_pdrive_shift                                         (12)
#define EMMC_PDRIVE_NF2_nf_dd_5_pdrive_mask                                          (0x0000F000)
#define EMMC_PDRIVE_NF2_nf_dd_5_pdrive(data)                                         (0x0000F000&((data)<<12))
#define EMMC_PDRIVE_NF2_nf_dd_5_pdrive_src(data)                                     ((0x0000F000&(data))>>12)
#define EMMC_PDRIVE_NF2_get_nf_dd_5_pdrive(data)                                     ((0x0000F000&(data))>>12)
#define EMMC_PDRIVE_NF2_nf_dd_5_ndrive_shift                                         (8)
#define EMMC_PDRIVE_NF2_nf_dd_5_ndrive_mask                                          (0x00000F00)
#define EMMC_PDRIVE_NF2_nf_dd_5_ndrive(data)                                         (0x00000F00&((data)<<8))
#define EMMC_PDRIVE_NF2_nf_dd_5_ndrive_src(data)                                     ((0x00000F00&(data))>>8)
#define EMMC_PDRIVE_NF2_get_nf_dd_5_ndrive(data)                                     ((0x00000F00&(data))>>8)
#define EMMC_PDRIVE_NF2_nf_dd_4_pdrive_shift                                         (4)
#define EMMC_PDRIVE_NF2_nf_dd_4_pdrive_mask                                          (0x000000F0)
#define EMMC_PDRIVE_NF2_nf_dd_4_pdrive(data)                                         (0x000000F0&((data)<<4))
#define EMMC_PDRIVE_NF2_nf_dd_4_pdrive_src(data)                                     ((0x000000F0&(data))>>4)
#define EMMC_PDRIVE_NF2_get_nf_dd_4_pdrive(data)                                     ((0x000000F0&(data))>>4)
#define EMMC_PDRIVE_NF2_nf_dd_4_ndrive_shift                                         (0)
#define EMMC_PDRIVE_NF2_nf_dd_4_ndrive_mask                                          (0x0000000F)
#define EMMC_PDRIVE_NF2_nf_dd_4_ndrive(data)                                         (0x0000000F&((data)<<0))
#define EMMC_PDRIVE_NF2_nf_dd_4_ndrive_src(data)                                     ((0x0000000F&(data))>>0)
#define EMMC_PDRIVE_NF2_get_nf_dd_4_ndrive(data)                                     ((0x0000000F&(data))>>0)


#define EMMC_PDRIVE_NF3                                                              0x9801262C
#define EMMC_PDRIVE_NF3_reg_addr                                                     "0x9801262C"
#define EMMC_PDRIVE_NF3_reg                                                          0x9801262C
#define set_EMMC_PDRIVE_NF3_reg(data)   (*((volatile unsigned int*) EMMC_PDRIVE_NF3_reg)=data)
#define get_EMMC_PDRIVE_NF3_reg   (*((volatile unsigned int*) EMMC_PDRIVE_NF3_reg))
#define EMMC_PDRIVE_NF3_inst_adr                                                     "0x008B"
#define EMMC_PDRIVE_NF3_inst                                                         0x008B
#define EMMC_PDRIVE_NF3_nf_rd_n_pdrive_shift                                         (28)
#define EMMC_PDRIVE_NF3_nf_rd_n_pdrive_mask                                          (0xF0000000)
#define EMMC_PDRIVE_NF3_nf_rd_n_pdrive(data)                                         (0xF0000000&((data)<<28))
#define EMMC_PDRIVE_NF3_nf_rd_n_pdrive_src(data)                                     ((0xF0000000&(data))>>28)
#define EMMC_PDRIVE_NF3_get_nf_rd_n_pdrive(data)                                     ((0xF0000000&(data))>>28)
#define EMMC_PDRIVE_NF3_nf_rd_n_ndrive_shift                                         (24)
#define EMMC_PDRIVE_NF3_nf_rd_n_ndrive_mask                                          (0x0F000000)
#define EMMC_PDRIVE_NF3_nf_rd_n_ndrive(data)                                         (0x0F000000&((data)<<24))
#define EMMC_PDRIVE_NF3_nf_rd_n_ndrive_src(data)                                     ((0x0F000000&(data))>>24)
#define EMMC_PDRIVE_NF3_get_nf_rd_n_ndrive(data)                                     ((0x0F000000&(data))>>24)
#define EMMC_PDRIVE_NF3_nf_wr_n_pdrive_shift                                         (20)
#define EMMC_PDRIVE_NF3_nf_wr_n_pdrive_mask                                          (0x00F00000)
#define EMMC_PDRIVE_NF3_nf_wr_n_pdrive(data)                                         (0x00F00000&((data)<<20))
#define EMMC_PDRIVE_NF3_nf_wr_n_pdrive_src(data)                                     ((0x00F00000&(data))>>20)
#define EMMC_PDRIVE_NF3_get_nf_wr_n_pdrive(data)                                     ((0x00F00000&(data))>>20)
#define EMMC_PDRIVE_NF3_nf_wr_n_ndrive_shift                                         (16)
#define EMMC_PDRIVE_NF3_nf_wr_n_ndrive_mask                                          (0x000F0000)
#define EMMC_PDRIVE_NF3_nf_wr_n_ndrive(data)                                         (0x000F0000&((data)<<16))
#define EMMC_PDRIVE_NF3_nf_wr_n_ndrive_src(data)                                     ((0x000F0000&(data))>>16)
#define EMMC_PDRIVE_NF3_get_nf_wr_n_ndrive(data)                                     ((0x000F0000&(data))>>16)
#define EMMC_PDRIVE_NF3_nf_cle_pdrive_shift                                          (12)
#define EMMC_PDRIVE_NF3_nf_cle_pdrive_mask                                           (0x0000F000)
#define EMMC_PDRIVE_NF3_nf_cle_pdrive(data)                                          (0x0000F000&((data)<<12))
#define EMMC_PDRIVE_NF3_nf_cle_pdrive_src(data)                                      ((0x0000F000&(data))>>12)
#define EMMC_PDRIVE_NF3_get_nf_cle_pdrive(data)                                      ((0x0000F000&(data))>>12)
#define EMMC_PDRIVE_NF3_nf_cle_ndrive_shift                                          (8)
#define EMMC_PDRIVE_NF3_nf_cle_ndrive_mask                                           (0x00000F00)
#define EMMC_PDRIVE_NF3_nf_cle_ndrive(data)                                          (0x00000F00&((data)<<8))
#define EMMC_PDRIVE_NF3_nf_cle_ndrive_src(data)                                      ((0x00000F00&(data))>>8)
#define EMMC_PDRIVE_NF3_get_nf_cle_ndrive(data)                                      ((0x00000F00&(data))>>8)
#define EMMC_PDRIVE_NF3_nf_ale_pdrive_shift                                          (4)
#define EMMC_PDRIVE_NF3_nf_ale_pdrive_mask                                           (0x000000F0)
#define EMMC_PDRIVE_NF3_nf_ale_pdrive(data)                                          (0x000000F0&((data)<<4))
#define EMMC_PDRIVE_NF3_nf_ale_pdrive_src(data)                                      ((0x000000F0&(data))>>4)
#define EMMC_PDRIVE_NF3_get_nf_ale_pdrive(data)                                      ((0x000000F0&(data))>>4)
#define EMMC_PDRIVE_NF3_nf_ale_ndrive_shift                                          (0)
#define EMMC_PDRIVE_NF3_nf_ale_ndrive_mask                                           (0x0000000F)
#define EMMC_PDRIVE_NF3_nf_ale_ndrive(data)                                          (0x0000000F&((data)<<0))
#define EMMC_PDRIVE_NF3_nf_ale_ndrive_src(data)                                      ((0x0000000F&(data))>>0)
#define EMMC_PDRIVE_NF3_get_nf_ale_ndrive(data)                                      ((0x0000000F&(data))>>0)


#define EMMC_PDRIVE_NF4                                                              0x98012630
#define EMMC_PDRIVE_NF4_reg_addr                                                     "0x98012630"
#define EMMC_PDRIVE_NF4_reg                                                          0x98012630
#define set_EMMC_PDRIVE_NF4_reg(data)   (*((volatile unsigned int*) EMMC_PDRIVE_NF4_reg)=data)
#define get_EMMC_PDRIVE_NF4_reg   (*((volatile unsigned int*) EMMC_PDRIVE_NF4_reg))
#define EMMC_PDRIVE_NF4_inst_adr                                                     "0x008C"
#define EMMC_PDRIVE_NF4_inst                                                         0x008C
#define EMMC_PDRIVE_NF4_emmc_dd_sb_pdrive_shift                                      (4)
#define EMMC_PDRIVE_NF4_emmc_dd_sb_pdrive_mask                                       (0x000000F0)
#define EMMC_PDRIVE_NF4_emmc_dd_sb_pdrive(data)                                      (0x000000F0&((data)<<4))
#define EMMC_PDRIVE_NF4_emmc_dd_sb_pdrive_src(data)                                  ((0x000000F0&(data))>>4)
#define EMMC_PDRIVE_NF4_get_emmc_dd_sb_pdrive(data)                                  ((0x000000F0&(data))>>4)
#define EMMC_PDRIVE_NF4_emmc_dd_sb_ndrive_shift                                      (0)
#define EMMC_PDRIVE_NF4_emmc_dd_sb_ndrive_mask                                       (0x0000000F)
#define EMMC_PDRIVE_NF4_emmc_dd_sb_ndrive(data)                                      (0x0000000F&((data)<<0))
#define EMMC_PDRIVE_NF4_emmc_dd_sb_ndrive_src(data)                                  ((0x0000000F&(data))>>0)
#define EMMC_PDRIVE_NF4_get_emmc_dd_sb_ndrive(data)                                  ((0x0000000F&(data))>>0)


#define EMMC_PDRIVE_CR0                                                              0x98012634
#define EMMC_PDRIVE_CR0_reg_addr                                                     "0x98012634"
#define EMMC_PDRIVE_CR0_reg                                                          0x98012634
#define set_EMMC_PDRIVE_CR0_reg(data)   (*((volatile unsigned int*) EMMC_PDRIVE_CR0_reg)=data)
#define get_EMMC_PDRIVE_CR0_reg   (*((volatile unsigned int*) EMMC_PDRIVE_CR0_reg))
#define EMMC_PDRIVE_CR0_inst_adr                                                     "0x008D"
#define EMMC_PDRIVE_CR0_inst                                                         0x008D
#define EMMC_PDRIVE_CR0_mmc_clk_pdrive_shift                                         (12)
#define EMMC_PDRIVE_CR0_mmc_clk_pdrive_mask                                          (0x0000F000)
#define EMMC_PDRIVE_CR0_mmc_clk_pdrive(data)                                         (0x0000F000&((data)<<12))
#define EMMC_PDRIVE_CR0_mmc_clk_pdrive_src(data)                                     ((0x0000F000&(data))>>12)
#define EMMC_PDRIVE_CR0_get_mmc_clk_pdrive(data)                                     ((0x0000F000&(data))>>12)
#define EMMC_PDRIVE_CR0_mmc_clk_ndrive_shift                                         (8)
#define EMMC_PDRIVE_CR0_mmc_clk_ndrive_mask                                          (0x00000F00)
#define EMMC_PDRIVE_CR0_mmc_clk_ndrive(data)                                         (0x00000F00&((data)<<8))
#define EMMC_PDRIVE_CR0_mmc_clk_ndrive_src(data)                                     ((0x00000F00&(data))>>8)
#define EMMC_PDRIVE_CR0_get_mmc_clk_ndrive(data)                                     ((0x00000F00&(data))>>8)
#define EMMC_PDRIVE_CR0_mmc_cmd_pdrive_shift                                         (4)
#define EMMC_PDRIVE_CR0_mmc_cmd_pdrive_mask                                          (0x000000F0)
#define EMMC_PDRIVE_CR0_mmc_cmd_pdrive(data)                                         (0x000000F0&((data)<<4))
#define EMMC_PDRIVE_CR0_mmc_cmd_pdrive_src(data)                                     ((0x000000F0&(data))>>4)
#define EMMC_PDRIVE_CR0_get_mmc_cmd_pdrive(data)                                     ((0x000000F0&(data))>>4)
#define EMMC_PDRIVE_CR0_mmc_cmd_ndrive_shift                                         (0)
#define EMMC_PDRIVE_CR0_mmc_cmd_ndrive_mask                                          (0x0000000F)
#define EMMC_PDRIVE_CR0_mmc_cmd_ndrive(data)                                         (0x0000000F&((data)<<0))
#define EMMC_PDRIVE_CR0_mmc_cmd_ndrive_src(data)                                     ((0x0000000F&(data))>>0)
#define EMMC_PDRIVE_CR0_get_mmc_cmd_ndrive(data)                                     ((0x0000000F&(data))>>0)


#define EMMC_PDRIVE_CR1                                                              0x98012638
#define EMMC_PDRIVE_CR1_reg_addr                                                     "0x98012638"
#define EMMC_PDRIVE_CR1_reg                                                          0x98012638
#define set_EMMC_PDRIVE_CR1_reg(data)   (*((volatile unsigned int*) EMMC_PDRIVE_CR1_reg)=data)
#define get_EMMC_PDRIVE_CR1_reg   (*((volatile unsigned int*) EMMC_PDRIVE_CR1_reg))
#define EMMC_PDRIVE_CR1_inst_adr                                                     "0x008E"
#define EMMC_PDRIVE_CR1_inst                                                         0x008E
#define EMMC_PDRIVE_CR1_mmc_data_3_pdrive_shift                                      (28)
#define EMMC_PDRIVE_CR1_mmc_data_3_pdrive_mask                                       (0xF0000000)
#define EMMC_PDRIVE_CR1_mmc_data_3_pdrive(data)                                      (0xF0000000&((data)<<28))
#define EMMC_PDRIVE_CR1_mmc_data_3_pdrive_src(data)                                  ((0xF0000000&(data))>>28)
#define EMMC_PDRIVE_CR1_get_mmc_data_3_pdrive(data)                                  ((0xF0000000&(data))>>28)
#define EMMC_PDRIVE_CR1_mmc_data_3_ndrive_shift                                      (24)
#define EMMC_PDRIVE_CR1_mmc_data_3_ndrive_mask                                       (0x0F000000)
#define EMMC_PDRIVE_CR1_mmc_data_3_ndrive(data)                                      (0x0F000000&((data)<<24))
#define EMMC_PDRIVE_CR1_mmc_data_3_ndrive_src(data)                                  ((0x0F000000&(data))>>24)
#define EMMC_PDRIVE_CR1_get_mmc_data_3_ndrive(data)                                  ((0x0F000000&(data))>>24)
#define EMMC_PDRIVE_CR1_mmc_data_2_pdrive_shift                                      (20)
#define EMMC_PDRIVE_CR1_mmc_data_2_pdrive_mask                                       (0x00F00000)
#define EMMC_PDRIVE_CR1_mmc_data_2_pdrive(data)                                      (0x00F00000&((data)<<20))
#define EMMC_PDRIVE_CR1_mmc_data_2_pdrive_src(data)                                  ((0x00F00000&(data))>>20)
#define EMMC_PDRIVE_CR1_get_mmc_data_2_pdrive(data)                                  ((0x00F00000&(data))>>20)
#define EMMC_PDRIVE_CR1_mmc_data_2_ndrive_shift                                      (16)
#define EMMC_PDRIVE_CR1_mmc_data_2_ndrive_mask                                       (0x000F0000)
#define EMMC_PDRIVE_CR1_mmc_data_2_ndrive(data)                                      (0x000F0000&((data)<<16))
#define EMMC_PDRIVE_CR1_mmc_data_2_ndrive_src(data)                                  ((0x000F0000&(data))>>16)
#define EMMC_PDRIVE_CR1_get_mmc_data_2_ndrive(data)                                  ((0x000F0000&(data))>>16)
#define EMMC_PDRIVE_CR1_mmc_data_1_pdrive_shift                                      (12)
#define EMMC_PDRIVE_CR1_mmc_data_1_pdrive_mask                                       (0x0000F000)
#define EMMC_PDRIVE_CR1_mmc_data_1_pdrive(data)                                      (0x0000F000&((data)<<12))
#define EMMC_PDRIVE_CR1_mmc_data_1_pdrive_src(data)                                  ((0x0000F000&(data))>>12)
#define EMMC_PDRIVE_CR1_get_mmc_data_1_pdrive(data)                                  ((0x0000F000&(data))>>12)
#define EMMC_PDRIVE_CR1_mmc_data_1_ndrive_shift                                      (8)
#define EMMC_PDRIVE_CR1_mmc_data_1_ndrive_mask                                       (0x00000F00)
#define EMMC_PDRIVE_CR1_mmc_data_1_ndrive(data)                                      (0x00000F00&((data)<<8))
#define EMMC_PDRIVE_CR1_mmc_data_1_ndrive_src(data)                                  ((0x00000F00&(data))>>8)
#define EMMC_PDRIVE_CR1_get_mmc_data_1_ndrive(data)                                  ((0x00000F00&(data))>>8)
#define EMMC_PDRIVE_CR1_mmc_data_0_pdrive_shift                                      (4)
#define EMMC_PDRIVE_CR1_mmc_data_0_pdrive_mask                                       (0x000000F0)
#define EMMC_PDRIVE_CR1_mmc_data_0_pdrive(data)                                      (0x000000F0&((data)<<4))
#define EMMC_PDRIVE_CR1_mmc_data_0_pdrive_src(data)                                  ((0x000000F0&(data))>>4)
#define EMMC_PDRIVE_CR1_get_mmc_data_0_pdrive(data)                                  ((0x000000F0&(data))>>4)
#define EMMC_PDRIVE_CR1_mmc_data_0_ndrive_shift                                      (0)
#define EMMC_PDRIVE_CR1_mmc_data_0_ndrive_mask                                       (0x0000000F)
#define EMMC_PDRIVE_CR1_mmc_data_0_ndrive(data)                                      (0x0000000F&((data)<<0))
#define EMMC_PDRIVE_CR1_mmc_data_0_ndrive_src(data)                                  ((0x0000000F&(data))>>0)
#define EMMC_PDRIVE_CR1_get_mmc_data_0_ndrive(data)                                  ((0x0000000F&(data))>>0)


#define EMMC_PDRIVE_SDIO0                                                            0x9801263C
#define EMMC_PDRIVE_SDIO0_reg_addr                                                   "0x9801263C"
#define EMMC_PDRIVE_SDIO0_reg                                                        0x9801263C
#define set_EMMC_PDRIVE_SDIO0_reg(data)   (*((volatile unsigned int*) EMMC_PDRIVE_SDIO0_reg)=data)
#define get_EMMC_PDRIVE_SDIO0_reg   (*((volatile unsigned int*) EMMC_PDRIVE_SDIO0_reg))
#define EMMC_PDRIVE_SDIO0_inst_adr                                                   "0x008F"
#define EMMC_PDRIVE_SDIO0_inst                                                       0x008F
#define EMMC_PDRIVE_SDIO0_sdio_clk_pdrive_shift                                      (12)
#define EMMC_PDRIVE_SDIO0_sdio_clk_pdrive_mask                                       (0x0000F000)
#define EMMC_PDRIVE_SDIO0_sdio_clk_pdrive(data)                                      (0x0000F000&((data)<<12))
#define EMMC_PDRIVE_SDIO0_sdio_clk_pdrive_src(data)                                  ((0x0000F000&(data))>>12)
#define EMMC_PDRIVE_SDIO0_get_sdio_clk_pdrive(data)                                  ((0x0000F000&(data))>>12)
#define EMMC_PDRIVE_SDIO0_sdio_clk_ndrive_shift                                      (8)
#define EMMC_PDRIVE_SDIO0_sdio_clk_ndrive_mask                                       (0x00000F00)
#define EMMC_PDRIVE_SDIO0_sdio_clk_ndrive(data)                                      (0x00000F00&((data)<<8))
#define EMMC_PDRIVE_SDIO0_sdio_clk_ndrive_src(data)                                  ((0x00000F00&(data))>>8)
#define EMMC_PDRIVE_SDIO0_get_sdio_clk_ndrive(data)                                  ((0x00000F00&(data))>>8)
#define EMMC_PDRIVE_SDIO0_sdio_cmd_pdrive_shift                                      (4)
#define EMMC_PDRIVE_SDIO0_sdio_cmd_pdrive_mask                                       (0x000000F0)
#define EMMC_PDRIVE_SDIO0_sdio_cmd_pdrive(data)                                      (0x000000F0&((data)<<4))
#define EMMC_PDRIVE_SDIO0_sdio_cmd_pdrive_src(data)                                  ((0x000000F0&(data))>>4)
#define EMMC_PDRIVE_SDIO0_get_sdio_cmd_pdrive(data)                                  ((0x000000F0&(data))>>4)
#define EMMC_PDRIVE_SDIO0_sdio_cmd_ndrive_shift                                      (0)
#define EMMC_PDRIVE_SDIO0_sdio_cmd_ndrive_mask                                       (0x0000000F)
#define EMMC_PDRIVE_SDIO0_sdio_cmd_ndrive(data)                                      (0x0000000F&((data)<<0))
#define EMMC_PDRIVE_SDIO0_sdio_cmd_ndrive_src(data)                                  ((0x0000000F&(data))>>0)
#define EMMC_PDRIVE_SDIO0_get_sdio_cmd_ndrive(data)                                  ((0x0000000F&(data))>>0)


#define EMMC_PDRIVE_SDIO1                                                            0x98012640
#define EMMC_PDRIVE_SDIO1_reg_addr                                                   "0x98012640"
#define EMMC_PDRIVE_SDIO1_reg                                                        0x98012640
#define set_EMMC_PDRIVE_SDIO1_reg(data)   (*((volatile unsigned int*) EMMC_PDRIVE_SDIO1_reg)=data)
#define get_EMMC_PDRIVE_SDIO1_reg   (*((volatile unsigned int*) EMMC_PDRIVE_SDIO1_reg))
#define EMMC_PDRIVE_SDIO1_inst_adr                                                   "0x0090"
#define EMMC_PDRIVE_SDIO1_inst                                                       0x0090
#define EMMC_PDRIVE_SDIO1_sdio_data_3_pdrive_shift                                   (28)
#define EMMC_PDRIVE_SDIO1_sdio_data_3_pdrive_mask                                    (0xF0000000)
#define EMMC_PDRIVE_SDIO1_sdio_data_3_pdrive(data)                                   (0xF0000000&((data)<<28))
#define EMMC_PDRIVE_SDIO1_sdio_data_3_pdrive_src(data)                               ((0xF0000000&(data))>>28)
#define EMMC_PDRIVE_SDIO1_get_sdio_data_3_pdrive(data)                               ((0xF0000000&(data))>>28)
#define EMMC_PDRIVE_SDIO1_sdio_data_3_ndrive_shift                                   (24)
#define EMMC_PDRIVE_SDIO1_sdio_data_3_ndrive_mask                                    (0x0F000000)
#define EMMC_PDRIVE_SDIO1_sdio_data_3_ndrive(data)                                   (0x0F000000&((data)<<24))
#define EMMC_PDRIVE_SDIO1_sdio_data_3_ndrive_src(data)                               ((0x0F000000&(data))>>24)
#define EMMC_PDRIVE_SDIO1_get_sdio_data_3_ndrive(data)                               ((0x0F000000&(data))>>24)
#define EMMC_PDRIVE_SDIO1_sdio_data_2_pdrive_shift                                   (20)
#define EMMC_PDRIVE_SDIO1_sdio_data_2_pdrive_mask                                    (0x00F00000)
#define EMMC_PDRIVE_SDIO1_sdio_data_2_pdrive(data)                                   (0x00F00000&((data)<<20))
#define EMMC_PDRIVE_SDIO1_sdio_data_2_pdrive_src(data)                               ((0x00F00000&(data))>>20)
#define EMMC_PDRIVE_SDIO1_get_sdio_data_2_pdrive(data)                               ((0x00F00000&(data))>>20)
#define EMMC_PDRIVE_SDIO1_sdio_data_2_ndrive_shift                                   (16)
#define EMMC_PDRIVE_SDIO1_sdio_data_2_ndrive_mask                                    (0x000F0000)
#define EMMC_PDRIVE_SDIO1_sdio_data_2_ndrive(data)                                   (0x000F0000&((data)<<16))
#define EMMC_PDRIVE_SDIO1_sdio_data_2_ndrive_src(data)                               ((0x000F0000&(data))>>16)
#define EMMC_PDRIVE_SDIO1_get_sdio_data_2_ndrive(data)                               ((0x000F0000&(data))>>16)
#define EMMC_PDRIVE_SDIO1_sdio_data_1_pdrive_shift                                   (12)
#define EMMC_PDRIVE_SDIO1_sdio_data_1_pdrive_mask                                    (0x0000F000)
#define EMMC_PDRIVE_SDIO1_sdio_data_1_pdrive(data)                                   (0x0000F000&((data)<<12))
#define EMMC_PDRIVE_SDIO1_sdio_data_1_pdrive_src(data)                               ((0x0000F000&(data))>>12)
#define EMMC_PDRIVE_SDIO1_get_sdio_data_1_pdrive(data)                               ((0x0000F000&(data))>>12)
#define EMMC_PDRIVE_SDIO1_sdio_data_1_ndrive_shift                                   (8)
#define EMMC_PDRIVE_SDIO1_sdio_data_1_ndrive_mask                                    (0x00000F00)
#define EMMC_PDRIVE_SDIO1_sdio_data_1_ndrive(data)                                   (0x00000F00&((data)<<8))
#define EMMC_PDRIVE_SDIO1_sdio_data_1_ndrive_src(data)                               ((0x00000F00&(data))>>8)
#define EMMC_PDRIVE_SDIO1_get_sdio_data_1_ndrive(data)                               ((0x00000F00&(data))>>8)
#define EMMC_PDRIVE_SDIO1_sdio_data_0_pdrive_shift                                   (4)
#define EMMC_PDRIVE_SDIO1_sdio_data_0_pdrive_mask                                    (0x000000F0)
#define EMMC_PDRIVE_SDIO1_sdio_data_0_pdrive(data)                                   (0x000000F0&((data)<<4))
#define EMMC_PDRIVE_SDIO1_sdio_data_0_pdrive_src(data)                               ((0x000000F0&(data))>>4)
#define EMMC_PDRIVE_SDIO1_get_sdio_data_0_pdrive(data)                               ((0x000000F0&(data))>>4)
#define EMMC_PDRIVE_SDIO1_sdio_data_0_ndrive_shift                                   (0)
#define EMMC_PDRIVE_SDIO1_sdio_data_0_ndrive_mask                                    (0x0000000F)
#define EMMC_PDRIVE_SDIO1_sdio_data_0_ndrive(data)                                   (0x0000000F&((data)<<0))
#define EMMC_PDRIVE_SDIO1_sdio_data_0_ndrive_src(data)                               ((0x0000000F&(data))>>0)
#define EMMC_PDRIVE_SDIO1_get_sdio_data_0_ndrive(data)                               ((0x0000000F&(data))>>0)


#define EMMC_LSADC0_PAD0                                                             0x98012800
#define EMMC_LSADC0_PAD0_reg_addr                                                    "0x98012800"
#define EMMC_LSADC0_PAD0_reg                                                         0x98012800
#define set_EMMC_LSADC0_PAD0_reg(data)   (*((volatile unsigned int*) EMMC_LSADC0_PAD0_reg)=data)
#define get_EMMC_LSADC0_PAD0_reg   (*((volatile unsigned int*) EMMC_LSADC0_PAD0_reg))
#define EMMC_LSADC0_PAD0_inst_adr                                                    "0x0000"
#define EMMC_LSADC0_PAD0_inst                                                        0x0000
#define EMMC_LSADC0_PAD0_pad0_active_shift                                           (31)
#define EMMC_LSADC0_PAD0_pad0_active_mask                                            (0x80000000)
#define EMMC_LSADC0_PAD0_pad0_active(data)                                           (0x80000000&((data)<<31))
#define EMMC_LSADC0_PAD0_pad0_active_src(data)                                       ((0x80000000&(data))>>31)
#define EMMC_LSADC0_PAD0_get_pad0_active(data)                                       ((0x80000000&(data))>>31)
#define EMMC_LSADC0_PAD0_pad0_thred_shift                                            (16)
#define EMMC_LSADC0_PAD0_pad0_thred_mask                                             (0x00FF0000)
#define EMMC_LSADC0_PAD0_pad0_thred(data)                                            (0x00FF0000&((data)<<16))
#define EMMC_LSADC0_PAD0_pad0_thred_src(data)                                        ((0x00FF0000&(data))>>16)
#define EMMC_LSADC0_PAD0_get_pad0_thred(data)                                        ((0x00FF0000&(data))>>16)
#define EMMC_LSADC0_PAD0_pad0_sw_shift                                               (12)
#define EMMC_LSADC0_PAD0_pad0_sw_mask                                                (0x0000F000)
#define EMMC_LSADC0_PAD0_pad0_sw(data)                                               (0x0000F000&((data)<<12))
#define EMMC_LSADC0_PAD0_pad0_sw_src(data)                                           ((0x0000F000&(data))>>12)
#define EMMC_LSADC0_PAD0_get_pad0_sw(data)                                           ((0x0000F000&(data))>>12)
#define EMMC_LSADC0_PAD0_pad0_ctrl_shift                                             (8)
#define EMMC_LSADC0_PAD0_pad0_ctrl_mask                                              (0x00000100)
#define EMMC_LSADC0_PAD0_pad0_ctrl(data)                                             (0x00000100&((data)<<8))
#define EMMC_LSADC0_PAD0_pad0_ctrl_src(data)                                         ((0x00000100&(data))>>8)
#define EMMC_LSADC0_PAD0_get_pad0_ctrl(data)                                         ((0x00000100&(data))>>8)
#define EMMC_LSADC0_PAD0_adc_val0_shift                                              (0)
#define EMMC_LSADC0_PAD0_adc_val0_mask                                               (0x0000003F)
#define EMMC_LSADC0_PAD0_adc_val0(data)                                              (0x0000003F&((data)<<0))
#define EMMC_LSADC0_PAD0_adc_val0_src(data)                                          ((0x0000003F&(data))>>0)
#define EMMC_LSADC0_PAD0_get_adc_val0(data)                                          ((0x0000003F&(data))>>0)


#define EMMC_LSADC0_PAD1                                                             0x98012804
#define EMMC_LSADC0_PAD1_reg_addr                                                    "0x98012804"
#define EMMC_LSADC0_PAD1_reg                                                         0x98012804
#define set_EMMC_LSADC0_PAD1_reg(data)   (*((volatile unsigned int*) EMMC_LSADC0_PAD1_reg)=data)
#define get_EMMC_LSADC0_PAD1_reg   (*((volatile unsigned int*) EMMC_LSADC0_PAD1_reg))
#define EMMC_LSADC0_PAD1_inst_adr                                                    "0x0001"
#define EMMC_LSADC0_PAD1_inst                                                        0x0001
#define EMMC_LSADC0_PAD1_pad1_active_shift                                           (31)
#define EMMC_LSADC0_PAD1_pad1_active_mask                                            (0x80000000)
#define EMMC_LSADC0_PAD1_pad1_active(data)                                           (0x80000000&((data)<<31))
#define EMMC_LSADC0_PAD1_pad1_active_src(data)                                       ((0x80000000&(data))>>31)
#define EMMC_LSADC0_PAD1_get_pad1_active(data)                                       ((0x80000000&(data))>>31)
#define EMMC_LSADC0_PAD1_Pad1_thred_shift                                            (16)
#define EMMC_LSADC0_PAD1_Pad1_thred_mask                                             (0x00FF0000)
#define EMMC_LSADC0_PAD1_Pad1_thred(data)                                            (0x00FF0000&((data)<<16))
#define EMMC_LSADC0_PAD1_Pad1_thred_src(data)                                        ((0x00FF0000&(data))>>16)
#define EMMC_LSADC0_PAD1_get_Pad1_thred(data)                                        ((0x00FF0000&(data))>>16)
#define EMMC_LSADC0_PAD1_Pad1_sw_shift                                               (12)
#define EMMC_LSADC0_PAD1_Pad1_sw_mask                                                (0x0000F000)
#define EMMC_LSADC0_PAD1_Pad1_sw(data)                                               (0x0000F000&((data)<<12))
#define EMMC_LSADC0_PAD1_Pad1_sw_src(data)                                           ((0x0000F000&(data))>>12)
#define EMMC_LSADC0_PAD1_get_Pad1_sw(data)                                           ((0x0000F000&(data))>>12)
#define EMMC_LSADC0_PAD1_Pad1_ctrl_shift                                             (8)
#define EMMC_LSADC0_PAD1_Pad1_ctrl_mask                                              (0x00000100)
#define EMMC_LSADC0_PAD1_Pad1_ctrl(data)                                             (0x00000100&((data)<<8))
#define EMMC_LSADC0_PAD1_Pad1_ctrl_src(data)                                         ((0x00000100&(data))>>8)
#define EMMC_LSADC0_PAD1_get_Pad1_ctrl(data)                                         ((0x00000100&(data))>>8)
#define EMMC_LSADC0_PAD1_adc_val0_shift                                              (0)
#define EMMC_LSADC0_PAD1_adc_val0_mask                                               (0x0000003F)
#define EMMC_LSADC0_PAD1_adc_val0(data)                                              (0x0000003F&((data)<<0))
#define EMMC_LSADC0_PAD1_adc_val0_src(data)                                          ((0x0000003F&(data))>>0)
#define EMMC_LSADC0_PAD1_get_adc_val0(data)                                          ((0x0000003F&(data))>>0)


#define EMMC_LSADC0_CTRL                                                             0x98012820
#define EMMC_LSADC0_CTRL_reg_addr                                                    "0x98012820"
#define EMMC_LSADC0_CTRL_reg                                                         0x98012820
#define set_EMMC_LSADC0_CTRL_reg(data)   (*((volatile unsigned int*) EMMC_LSADC0_CTRL_reg)=data)
#define get_EMMC_LSADC0_CTRL_reg   (*((volatile unsigned int*) EMMC_LSADC0_CTRL_reg))
#define EMMC_LSADC0_CTRL_inst_adr                                                    "0x0008"
#define EMMC_LSADC0_CTRL_inst                                                        0x0008
#define EMMC_LSADC0_CTRL_Sel_wait_shift                                              (28)
#define EMMC_LSADC0_CTRL_Sel_wait_mask                                               (0xF0000000)
#define EMMC_LSADC0_CTRL_Sel_wait(data)                                              (0xF0000000&((data)<<28))
#define EMMC_LSADC0_CTRL_Sel_wait_src(data)                                          ((0xF0000000&(data))>>28)
#define EMMC_LSADC0_CTRL_get_Sel_wait(data)                                          ((0xF0000000&(data))>>28)
#define EMMC_LSADC0_CTRL_Sel_adc_ck_shift                                            (24)
#define EMMC_LSADC0_CTRL_Sel_adc_ck_mask                                             (0x0F000000)
#define EMMC_LSADC0_CTRL_Sel_adc_ck(data)                                            (0x0F000000&((data)<<24))
#define EMMC_LSADC0_CTRL_Sel_adc_ck_src(data)                                        ((0x0F000000&(data))>>24)
#define EMMC_LSADC0_CTRL_get_Sel_adc_ck(data)                                        ((0x0F000000&(data))>>24)
#define EMMC_LSADC0_CTRL_Debounce_cnt_shift                                          (20)
#define EMMC_LSADC0_CTRL_Debounce_cnt_mask                                           (0x00F00000)
#define EMMC_LSADC0_CTRL_Debounce_cnt(data)                                          (0x00F00000&((data)<<20))
#define EMMC_LSADC0_CTRL_Debounce_cnt_src(data)                                      ((0x00F00000&(data))>>20)
#define EMMC_LSADC0_CTRL_get_Debounce_cnt(data)                                      ((0x00F00000&(data))>>20)
#define EMMC_LSADC0_CTRL_Dout_Test_IN_shift                                          (8)
#define EMMC_LSADC0_CTRL_Dout_Test_IN_mask                                           (0x0000FF00)
#define EMMC_LSADC0_CTRL_Dout_Test_IN(data)                                          (0x0000FF00&((data)<<8))
#define EMMC_LSADC0_CTRL_Dout_Test_IN_src(data)                                      ((0x0000FF00&(data))>>8)
#define EMMC_LSADC0_CTRL_get_Dout_Test_IN(data)                                      ((0x0000FF00&(data))>>8)
#define EMMC_LSADC0_CTRL_Test_en_shift                                               (1)
#define EMMC_LSADC0_CTRL_Test_en_mask                                                (0x00000002)
#define EMMC_LSADC0_CTRL_Test_en(data)                                               (0x00000002&((data)<<1))
#define EMMC_LSADC0_CTRL_Test_en_src(data)                                           ((0x00000002&(data))>>1)
#define EMMC_LSADC0_CTRL_get_Test_en(data)                                           ((0x00000002&(data))>>1)
#define EMMC_LSADC0_CTRL_Enable_shift                                                (0)
#define EMMC_LSADC0_CTRL_Enable_mask                                                 (0x00000001)
#define EMMC_LSADC0_CTRL_Enable(data)                                                (0x00000001&((data)<<0))
#define EMMC_LSADC0_CTRL_Enable_src(data)                                            ((0x00000001&(data))>>0)
#define EMMC_LSADC0_CTRL_get_Enable(data)                                            ((0x00000001&(data))>>0)


#define EMMC_LSADC0_STATUS                                                           0x98012824
#define EMMC_LSADC0_STATUS_reg_addr                                                  "0x98012824"
#define EMMC_LSADC0_STATUS_reg                                                       0x98012824
#define set_EMMC_LSADC0_STATUS_reg(data)   (*((volatile unsigned int*) EMMC_LSADC0_STATUS_reg)=data)
#define get_EMMC_LSADC0_STATUS_reg   (*((volatile unsigned int*) EMMC_LSADC0_STATUS_reg))
#define EMMC_LSADC0_STATUS_inst_adr                                                  "0x0009"
#define EMMC_LSADC0_STATUS_inst                                                      0x0009
#define EMMC_LSADC0_STATUS_IRQ_En_shift                                              (24)
#define EMMC_LSADC0_STATUS_IRQ_En_mask                                               (0xFF000000)
#define EMMC_LSADC0_STATUS_IRQ_En(data)                                              (0xFF000000&((data)<<24))
#define EMMC_LSADC0_STATUS_IRQ_En_src(data)                                          ((0xFF000000&(data))>>24)
#define EMMC_LSADC0_STATUS_get_IRQ_En(data)                                          ((0xFF000000&(data))>>24)
#define EMMC_LSADC0_STATUS_PAD_CNT_shift                                             (20)
#define EMMC_LSADC0_STATUS_PAD_CNT_mask                                              (0x00F00000)
#define EMMC_LSADC0_STATUS_PAD_CNT(data)                                             (0x00F00000&((data)<<20))
#define EMMC_LSADC0_STATUS_PAD_CNT_src(data)                                         ((0x00F00000&(data))>>20)
#define EMMC_LSADC0_STATUS_get_PAD_CNT(data)                                         ((0x00F00000&(data))>>20)
#define EMMC_LSADC0_STATUS_ADC_busy_shift                                            (19)
#define EMMC_LSADC0_STATUS_ADC_busy_mask                                             (0x00080000)
#define EMMC_LSADC0_STATUS_ADC_busy(data)                                            (0x00080000&((data)<<19))
#define EMMC_LSADC0_STATUS_ADC_busy_src(data)                                        ((0x00080000&(data))>>19)
#define EMMC_LSADC0_STATUS_get_ADC_busy(data)                                        ((0x00080000&(data))>>19)
#define EMMC_LSADC0_STATUS_pad_ctrl_shift                                            (12)
#define EMMC_LSADC0_STATUS_pad_ctrl_mask                                             (0x0001F000)
#define EMMC_LSADC0_STATUS_pad_ctrl(data)                                            (0x0001F000&((data)<<12))
#define EMMC_LSADC0_STATUS_pad_ctrl_src(data)                                        ((0x0001F000&(data))>>12)
#define EMMC_LSADC0_STATUS_get_pad_ctrl(data)                                        ((0x0001F000&(data))>>12)
#define EMMC_LSADC0_STATUS_Pad1_status_shift                                         (1)
#define EMMC_LSADC0_STATUS_Pad1_status_mask                                          (0x00000002)
#define EMMC_LSADC0_STATUS_Pad1_status(data)                                         (0x00000002&((data)<<1))
#define EMMC_LSADC0_STATUS_Pad1_status_src(data)                                     ((0x00000002&(data))>>1)
#define EMMC_LSADC0_STATUS_get_Pad1_status(data)                                     ((0x00000002&(data))>>1)
#define EMMC_LSADC0_STATUS_Pad0_status_shift                                         (0)
#define EMMC_LSADC0_STATUS_Pad0_status_mask                                          (0x00000001)
#define EMMC_LSADC0_STATUS_Pad0_status(data)                                         (0x00000001&((data)<<0))
#define EMMC_LSADC0_STATUS_Pad0_status_src(data)                                     ((0x00000001&(data))>>0)
#define EMMC_LSADC0_STATUS_get_Pad0_status(data)                                     ((0x00000001&(data))>>0)


#define EMMC_LSADC0_ANALOG_CTRL                                                      0x98012828
#define EMMC_LSADC0_ANALOG_CTRL_reg_addr                                             "0x98012828"
#define EMMC_LSADC0_ANALOG_CTRL_reg                                                  0x98012828
#define set_EMMC_LSADC0_ANALOG_CTRL_reg(data)   (*((volatile unsigned int*) EMMC_LSADC0_ANALOG_CTRL_reg)=data)
#define get_EMMC_LSADC0_ANALOG_CTRL_reg   (*((volatile unsigned int*) EMMC_LSADC0_ANALOG_CTRL_reg))
#define EMMC_LSADC0_ANALOG_CTRL_inst_adr                                             "0x000A"
#define EMMC_LSADC0_ANALOG_CTRL_inst                                                 0x000A
#define EMMC_LSADC0_ANALOG_CTRL_DUMMY2_shift                                         (20)
#define EMMC_LSADC0_ANALOG_CTRL_DUMMY2_mask                                          (0x00F00000)
#define EMMC_LSADC0_ANALOG_CTRL_DUMMY2(data)                                         (0x00F00000&((data)<<20))
#define EMMC_LSADC0_ANALOG_CTRL_DUMMY2_src(data)                                     ((0x00F00000&(data))>>20)
#define EMMC_LSADC0_ANALOG_CTRL_get_DUMMY2(data)                                     ((0x00F00000&(data))>>20)
#define EMMC_LSADC0_ANALOG_CTRL_JD_sbias_shift                                       (16)
#define EMMC_LSADC0_ANALOG_CTRL_JD_sbias_mask                                        (0x00030000)
#define EMMC_LSADC0_ANALOG_CTRL_JD_sbias(data)                                       (0x00030000&((data)<<16))
#define EMMC_LSADC0_ANALOG_CTRL_JD_sbias_src(data)                                   ((0x00030000&(data))>>16)
#define EMMC_LSADC0_ANALOG_CTRL_get_JD_sbias(data)                                   ((0x00030000&(data))>>16)
#define EMMC_LSADC0_ANALOG_CTRL_JD_adsbias_shift                                     (12)
#define EMMC_LSADC0_ANALOG_CTRL_JD_adsbias_mask                                      (0x00003000)
#define EMMC_LSADC0_ANALOG_CTRL_JD_adsbias(data)                                     (0x00003000&((data)<<12))
#define EMMC_LSADC0_ANALOG_CTRL_JD_adsbias_src(data)                                 ((0x00003000&(data))>>12)
#define EMMC_LSADC0_ANALOG_CTRL_get_JD_adsbias(data)                                 ((0x00003000&(data))>>12)
#define EMMC_LSADC0_ANALOG_CTRL_JD_DUMMY_shift                                       (10)
#define EMMC_LSADC0_ANALOG_CTRL_JD_DUMMY_mask                                        (0x00000C00)
#define EMMC_LSADC0_ANALOG_CTRL_JD_DUMMY(data)                                       (0x00000C00&((data)<<10))
#define EMMC_LSADC0_ANALOG_CTRL_JD_DUMMY_src(data)                                   ((0x00000C00&(data))>>10)
#define EMMC_LSADC0_ANALOG_CTRL_get_JD_DUMMY(data)                                   ((0x00000C00&(data))>>10)
#define EMMC_LSADC0_ANALOG_CTRL_JD_svr_shift                                         (8)
#define EMMC_LSADC0_ANALOG_CTRL_JD_svr_mask                                          (0x00000100)
#define EMMC_LSADC0_ANALOG_CTRL_JD_svr(data)                                         (0x00000100&((data)<<8))
#define EMMC_LSADC0_ANALOG_CTRL_JD_svr_src(data)                                     ((0x00000100&(data))>>8)
#define EMMC_LSADC0_ANALOG_CTRL_get_JD_svr(data)                                     ((0x00000100&(data))>>8)
#define EMMC_LSADC0_ANALOG_CTRL_JD_adcksel_shift                                     (4)
#define EMMC_LSADC0_ANALOG_CTRL_JD_adcksel_mask                                      (0x00000010)
#define EMMC_LSADC0_ANALOG_CTRL_JD_adcksel(data)                                     (0x00000010&((data)<<4))
#define EMMC_LSADC0_ANALOG_CTRL_JD_adcksel_src(data)                                 ((0x00000010&(data))>>4)
#define EMMC_LSADC0_ANALOG_CTRL_get_JD_adcksel(data)                                 ((0x00000010&(data))>>4)
#define EMMC_LSADC0_ANALOG_CTRL_JD_power_shift                                       (0)
#define EMMC_LSADC0_ANALOG_CTRL_JD_power_mask                                        (0x00000001)
#define EMMC_LSADC0_ANALOG_CTRL_JD_power(data)                                       (0x00000001&((data)<<0))
#define EMMC_LSADC0_ANALOG_CTRL_JD_power_src(data)                                   ((0x00000001&(data))>>0)
#define EMMC_LSADC0_ANALOG_CTRL_get_JD_power(data)                                   ((0x00000001&(data))>>0)


#define EMMC_LSADC0_PERI_TOP_DEBUG                                                   0x9801282C
#define EMMC_LSADC0_PERI_TOP_DEBUG_reg_addr                                          "0x9801282C"
#define EMMC_LSADC0_PERI_TOP_DEBUG_reg                                               0x9801282C
#define set_EMMC_LSADC0_PERI_TOP_DEBUG_reg(data)   (*((volatile unsigned int*) EMMC_LSADC0_PERI_TOP_DEBUG_reg)=data)
#define get_EMMC_LSADC0_PERI_TOP_DEBUG_reg   (*((volatile unsigned int*) EMMC_LSADC0_PERI_TOP_DEBUG_reg))
#define EMMC_LSADC0_PERI_TOP_DEBUG_inst_adr                                          "0x000B"
#define EMMC_LSADC0_PERI_TOP_DEBUG_inst                                              0x000B
#define EMMC_LSADC0_PERI_TOP_DEBUG_Lsadc_2_ifd_data_sel_shift                        (16)
#define EMMC_LSADC0_PERI_TOP_DEBUG_Lsadc_2_ifd_data_sel_mask                         (0x00070000)
#define EMMC_LSADC0_PERI_TOP_DEBUG_Lsadc_2_ifd_data_sel(data)                        (0x00070000&((data)<<16))
#define EMMC_LSADC0_PERI_TOP_DEBUG_Lsadc_2_ifd_data_sel_src(data)                    ((0x00070000&(data))>>16)
#define EMMC_LSADC0_PERI_TOP_DEBUG_get_Lsadc_2_ifd_data_sel(data)                    ((0x00070000&(data))>>16)
#define EMMC_LSADC0_PERI_TOP_DEBUG_Power_saving_enable_shift                         (14)
#define EMMC_LSADC0_PERI_TOP_DEBUG_Power_saving_enable_mask                          (0x00004000)
#define EMMC_LSADC0_PERI_TOP_DEBUG_Power_saving_enable(data)                         (0x00004000&((data)<<14))
#define EMMC_LSADC0_PERI_TOP_DEBUG_Power_saving_enable_src(data)                     ((0x00004000&(data))>>14)
#define EMMC_LSADC0_PERI_TOP_DEBUG_get_Power_saving_enable(data)                     ((0x00004000&(data))>>14)
#define EMMC_LSADC0_PERI_TOP_DEBUG_Power_saving_cycle_time_shift                     (11)
#define EMMC_LSADC0_PERI_TOP_DEBUG_Power_saving_cycle_time_mask                      (0x00003800)
#define EMMC_LSADC0_PERI_TOP_DEBUG_Power_saving_cycle_time(data)                     (0x00003800&((data)<<11))
#define EMMC_LSADC0_PERI_TOP_DEBUG_Power_saving_cycle_time_src(data)                 ((0x00003800&(data))>>11)
#define EMMC_LSADC0_PERI_TOP_DEBUG_get_Power_saving_cycle_time(data)                 ((0x00003800&(data))>>11)
#define EMMC_LSADC0_PERI_TOP_DEBUG_Power_saving_disable_time_shift                   (8)
#define EMMC_LSADC0_PERI_TOP_DEBUG_Power_saving_disable_time_mask                    (0x00000700)
#define EMMC_LSADC0_PERI_TOP_DEBUG_Power_saving_disable_time(data)                   (0x00000700&((data)<<8))
#define EMMC_LSADC0_PERI_TOP_DEBUG_Power_saving_disable_time_src(data)               ((0x00000700&(data))>>8)
#define EMMC_LSADC0_PERI_TOP_DEBUG_get_Power_saving_disable_time(data)               ((0x00000700&(data))>>8)
#define EMMC_LSADC0_PERI_TOP_DEBUG_peri_top_debug_shift                              (0)
#define EMMC_LSADC0_PERI_TOP_DEBUG_peri_top_debug_mask                               (0x000000FF)
#define EMMC_LSADC0_PERI_TOP_DEBUG_peri_top_debug(data)                              (0x000000FF&((data)<<0))
#define EMMC_LSADC0_PERI_TOP_DEBUG_peri_top_debug_src(data)                          ((0x000000FF&(data))>>0)
#define EMMC_LSADC0_PERI_TOP_DEBUG_get_peri_top_debug(data)                          ((0x000000FF&(data))>>0)


#define EMMC_LSADC0_PAD0_LEVEL_SET0                                                  0x98012830
#define EMMC_LSADC0_PAD0_LEVEL_SET0_reg_addr                                         "0x98012830"
#define EMMC_LSADC0_PAD0_LEVEL_SET0_reg                                              0x98012830
#define set_EMMC_LSADC0_PAD0_LEVEL_SET0_reg(data)   (*((volatile unsigned int*) EMMC_LSADC0_PAD0_LEVEL_SET0_reg)=data)
#define get_EMMC_LSADC0_PAD0_LEVEL_SET0_reg   (*((volatile unsigned int*) EMMC_LSADC0_PAD0_LEVEL_SET0_reg))
#define EMMC_LSADC0_PAD0_LEVEL_SET0_inst_adr                                         "0x000C"
#define EMMC_LSADC0_PAD0_LEVEL_SET0_inst                                             0x000C
#define EMMC_LSADC0_PAD0_LEVEL_SET0_Level_0_top_bound_shift                          (24)
#define EMMC_LSADC0_PAD0_LEVEL_SET0_Level_0_top_bound_mask                           (0xFF000000)
#define EMMC_LSADC0_PAD0_LEVEL_SET0_Level_0_top_bound(data)                          (0xFF000000&((data)<<24))
#define EMMC_LSADC0_PAD0_LEVEL_SET0_Level_0_top_bound_src(data)                      ((0xFF000000&(data))>>24)
#define EMMC_LSADC0_PAD0_LEVEL_SET0_get_Level_0_top_bound(data)                      ((0xFF000000&(data))>>24)
#define EMMC_LSADC0_PAD0_LEVEL_SET0_Level_0_low_bound_shift                          (16)
#define EMMC_LSADC0_PAD0_LEVEL_SET0_Level_0_low_bound_mask                           (0x00FF0000)
#define EMMC_LSADC0_PAD0_LEVEL_SET0_Level_0_low_bound(data)                          (0x00FF0000&((data)<<16))
#define EMMC_LSADC0_PAD0_LEVEL_SET0_Level_0_low_bound_src(data)                      ((0x00FF0000&(data))>>16)
#define EMMC_LSADC0_PAD0_LEVEL_SET0_get_Level_0_low_bound(data)                      ((0x00FF0000&(data))>>16)
#define EMMC_LSADC0_PAD0_LEVEL_SET0_Block0_en_shift                                  (15)
#define EMMC_LSADC0_PAD0_LEVEL_SET0_Block0_en_mask                                   (0x00008000)
#define EMMC_LSADC0_PAD0_LEVEL_SET0_Block0_en(data)                                  (0x00008000&((data)<<15))
#define EMMC_LSADC0_PAD0_LEVEL_SET0_Block0_en_src(data)                              ((0x00008000&(data))>>15)
#define EMMC_LSADC0_PAD0_LEVEL_SET0_get_Block0_en(data)                              ((0x00008000&(data))>>15)
#define EMMC_LSADC0_PAD0_LEVEL_SET0_INT_en0_shift                                    (1)
#define EMMC_LSADC0_PAD0_LEVEL_SET0_INT_en0_mask                                     (0x00000002)
#define EMMC_LSADC0_PAD0_LEVEL_SET0_INT_en0(data)                                    (0x00000002&((data)<<1))
#define EMMC_LSADC0_PAD0_LEVEL_SET0_INT_en0_src(data)                                ((0x00000002&(data))>>1)
#define EMMC_LSADC0_PAD0_LEVEL_SET0_get_INT_en0(data)                                ((0x00000002&(data))>>1)
#define EMMC_LSADC0_PAD0_LEVEL_SET0_INT_pending_bit0_shift                           (0)
#define EMMC_LSADC0_PAD0_LEVEL_SET0_INT_pending_bit0_mask                            (0x00000001)
#define EMMC_LSADC0_PAD0_LEVEL_SET0_INT_pending_bit0(data)                           (0x00000001&((data)<<0))
#define EMMC_LSADC0_PAD0_LEVEL_SET0_INT_pending_bit0_src(data)                       ((0x00000001&(data))>>0)
#define EMMC_LSADC0_PAD0_LEVEL_SET0_get_INT_pending_bit0(data)                       ((0x00000001&(data))>>0)


#define EMMC_LSADC0_PAD0_LEVEL_SET1                                                  0x98012834
#define EMMC_LSADC0_PAD0_LEVEL_SET1_reg_addr                                         "0x98012834"
#define EMMC_LSADC0_PAD0_LEVEL_SET1_reg                                              0x98012834
#define set_EMMC_LSADC0_PAD0_LEVEL_SET1_reg(data)   (*((volatile unsigned int*) EMMC_LSADC0_PAD0_LEVEL_SET1_reg)=data)
#define get_EMMC_LSADC0_PAD0_LEVEL_SET1_reg   (*((volatile unsigned int*) EMMC_LSADC0_PAD0_LEVEL_SET1_reg))
#define EMMC_LSADC0_PAD0_LEVEL_SET1_inst_adr                                         "0x000D"
#define EMMC_LSADC0_PAD0_LEVEL_SET1_inst                                             0x000D
#define EMMC_LSADC0_PAD0_LEVEL_SET1_Level_1_top_bound_shift                          (24)
#define EMMC_LSADC0_PAD0_LEVEL_SET1_Level_1_top_bound_mask                           (0xFF000000)
#define EMMC_LSADC0_PAD0_LEVEL_SET1_Level_1_top_bound(data)                          (0xFF000000&((data)<<24))
#define EMMC_LSADC0_PAD0_LEVEL_SET1_Level_1_top_bound_src(data)                      ((0xFF000000&(data))>>24)
#define EMMC_LSADC0_PAD0_LEVEL_SET1_get_Level_1_top_bound(data)                      ((0xFF000000&(data))>>24)
#define EMMC_LSADC0_PAD0_LEVEL_SET1_Level_0_low_bound_shift                          (16)
#define EMMC_LSADC0_PAD0_LEVEL_SET1_Level_0_low_bound_mask                           (0x00FF0000)
#define EMMC_LSADC0_PAD0_LEVEL_SET1_Level_0_low_bound(data)                          (0x00FF0000&((data)<<16))
#define EMMC_LSADC0_PAD0_LEVEL_SET1_Level_0_low_bound_src(data)                      ((0x00FF0000&(data))>>16)
#define EMMC_LSADC0_PAD0_LEVEL_SET1_get_Level_0_low_bound(data)                      ((0x00FF0000&(data))>>16)
#define EMMC_LSADC0_PAD0_LEVEL_SET1_Block1_en_shift                                  (15)
#define EMMC_LSADC0_PAD0_LEVEL_SET1_Block1_en_mask                                   (0x00008000)
#define EMMC_LSADC0_PAD0_LEVEL_SET1_Block1_en(data)                                  (0x00008000&((data)<<15))
#define EMMC_LSADC0_PAD0_LEVEL_SET1_Block1_en_src(data)                              ((0x00008000&(data))>>15)
#define EMMC_LSADC0_PAD0_LEVEL_SET1_get_Block1_en(data)                              ((0x00008000&(data))>>15)
#define EMMC_LSADC0_PAD0_LEVEL_SET1_INT_en1_shift                                    (1)
#define EMMC_LSADC0_PAD0_LEVEL_SET1_INT_en1_mask                                     (0x00000002)
#define EMMC_LSADC0_PAD0_LEVEL_SET1_INT_en1(data)                                    (0x00000002&((data)<<1))
#define EMMC_LSADC0_PAD0_LEVEL_SET1_INT_en1_src(data)                                ((0x00000002&(data))>>1)
#define EMMC_LSADC0_PAD0_LEVEL_SET1_get_INT_en1(data)                                ((0x00000002&(data))>>1)
#define EMMC_LSADC0_PAD0_LEVEL_SET1_INT_pending_bit1_shift                           (0)
#define EMMC_LSADC0_PAD0_LEVEL_SET1_INT_pending_bit1_mask                            (0x00000001)
#define EMMC_LSADC0_PAD0_LEVEL_SET1_INT_pending_bit1(data)                           (0x00000001&((data)<<0))
#define EMMC_LSADC0_PAD0_LEVEL_SET1_INT_pending_bit1_src(data)                       ((0x00000001&(data))>>0)
#define EMMC_LSADC0_PAD0_LEVEL_SET1_get_INT_pending_bit1(data)                       ((0x00000001&(data))>>0)


#define EMMC_LSADC0_PAD0_LEVEL_SET2                                                  0x98012838
#define EMMC_LSADC0_PAD0_LEVEL_SET2_reg_addr                                         "0x98012838"
#define EMMC_LSADC0_PAD0_LEVEL_SET2_reg                                              0x98012838
#define set_EMMC_LSADC0_PAD0_LEVEL_SET2_reg(data)   (*((volatile unsigned int*) EMMC_LSADC0_PAD0_LEVEL_SET2_reg)=data)
#define get_EMMC_LSADC0_PAD0_LEVEL_SET2_reg   (*((volatile unsigned int*) EMMC_LSADC0_PAD0_LEVEL_SET2_reg))
#define EMMC_LSADC0_PAD0_LEVEL_SET2_inst_adr                                         "0x000E"
#define EMMC_LSADC0_PAD0_LEVEL_SET2_inst                                             0x000E
#define EMMC_LSADC0_PAD0_LEVEL_SET2_Level_2_top_bound_shift                          (24)
#define EMMC_LSADC0_PAD0_LEVEL_SET2_Level_2_top_bound_mask                           (0xFF000000)
#define EMMC_LSADC0_PAD0_LEVEL_SET2_Level_2_top_bound(data)                          (0xFF000000&((data)<<24))
#define EMMC_LSADC0_PAD0_LEVEL_SET2_Level_2_top_bound_src(data)                      ((0xFF000000&(data))>>24)
#define EMMC_LSADC0_PAD0_LEVEL_SET2_get_Level_2_top_bound(data)                      ((0xFF000000&(data))>>24)
#define EMMC_LSADC0_PAD0_LEVEL_SET2_Level_2_low_bound_shift                          (16)
#define EMMC_LSADC0_PAD0_LEVEL_SET2_Level_2_low_bound_mask                           (0x00FF0000)
#define EMMC_LSADC0_PAD0_LEVEL_SET2_Level_2_low_bound(data)                          (0x00FF0000&((data)<<16))
#define EMMC_LSADC0_PAD0_LEVEL_SET2_Level_2_low_bound_src(data)                      ((0x00FF0000&(data))>>16)
#define EMMC_LSADC0_PAD0_LEVEL_SET2_get_Level_2_low_bound(data)                      ((0x00FF0000&(data))>>16)
#define EMMC_LSADC0_PAD0_LEVEL_SET2_Block2_en_shift                                  (15)
#define EMMC_LSADC0_PAD0_LEVEL_SET2_Block2_en_mask                                   (0x00008000)
#define EMMC_LSADC0_PAD0_LEVEL_SET2_Block2_en(data)                                  (0x00008000&((data)<<15))
#define EMMC_LSADC0_PAD0_LEVEL_SET2_Block2_en_src(data)                              ((0x00008000&(data))>>15)
#define EMMC_LSADC0_PAD0_LEVEL_SET2_get_Block2_en(data)                              ((0x00008000&(data))>>15)
#define EMMC_LSADC0_PAD0_LEVEL_SET2_INT_en2_shift                                    (1)
#define EMMC_LSADC0_PAD0_LEVEL_SET2_INT_en2_mask                                     (0x00000002)
#define EMMC_LSADC0_PAD0_LEVEL_SET2_INT_en2(data)                                    (0x00000002&((data)<<1))
#define EMMC_LSADC0_PAD0_LEVEL_SET2_INT_en2_src(data)                                ((0x00000002&(data))>>1)
#define EMMC_LSADC0_PAD0_LEVEL_SET2_get_INT_en2(data)                                ((0x00000002&(data))>>1)
#define EMMC_LSADC0_PAD0_LEVEL_SET2_INT_pending_bit2_shift                           (0)
#define EMMC_LSADC0_PAD0_LEVEL_SET2_INT_pending_bit2_mask                            (0x00000001)
#define EMMC_LSADC0_PAD0_LEVEL_SET2_INT_pending_bit2(data)                           (0x00000001&((data)<<0))
#define EMMC_LSADC0_PAD0_LEVEL_SET2_INT_pending_bit2_src(data)                       ((0x00000001&(data))>>0)
#define EMMC_LSADC0_PAD0_LEVEL_SET2_get_INT_pending_bit2(data)                       ((0x00000001&(data))>>0)


#define EMMC_LSADC0_PAD0_LEVEL_SET3                                                  0x9801283C
#define EMMC_LSADC0_PAD0_LEVEL_SET3_reg_addr                                         "0x9801283C"
#define EMMC_LSADC0_PAD0_LEVEL_SET3_reg                                              0x9801283C
#define set_EMMC_LSADC0_PAD0_LEVEL_SET3_reg(data)   (*((volatile unsigned int*) EMMC_LSADC0_PAD0_LEVEL_SET3_reg)=data)
#define get_EMMC_LSADC0_PAD0_LEVEL_SET3_reg   (*((volatile unsigned int*) EMMC_LSADC0_PAD0_LEVEL_SET3_reg))
#define EMMC_LSADC0_PAD0_LEVEL_SET3_inst_adr                                         "0x000F"
#define EMMC_LSADC0_PAD0_LEVEL_SET3_inst                                             0x000F
#define EMMC_LSADC0_PAD0_LEVEL_SET3_Level_3_top_bound_shift                          (24)
#define EMMC_LSADC0_PAD0_LEVEL_SET3_Level_3_top_bound_mask                           (0xFF000000)
#define EMMC_LSADC0_PAD0_LEVEL_SET3_Level_3_top_bound(data)                          (0xFF000000&((data)<<24))
#define EMMC_LSADC0_PAD0_LEVEL_SET3_Level_3_top_bound_src(data)                      ((0xFF000000&(data))>>24)
#define EMMC_LSADC0_PAD0_LEVEL_SET3_get_Level_3_top_bound(data)                      ((0xFF000000&(data))>>24)
#define EMMC_LSADC0_PAD0_LEVEL_SET3_Level_3_low_bound_shift                          (16)
#define EMMC_LSADC0_PAD0_LEVEL_SET3_Level_3_low_bound_mask                           (0x00FF0000)
#define EMMC_LSADC0_PAD0_LEVEL_SET3_Level_3_low_bound(data)                          (0x00FF0000&((data)<<16))
#define EMMC_LSADC0_PAD0_LEVEL_SET3_Level_3_low_bound_src(data)                      ((0x00FF0000&(data))>>16)
#define EMMC_LSADC0_PAD0_LEVEL_SET3_get_Level_3_low_bound(data)                      ((0x00FF0000&(data))>>16)
#define EMMC_LSADC0_PAD0_LEVEL_SET3_Block3_en_shift                                  (15)
#define EMMC_LSADC0_PAD0_LEVEL_SET3_Block3_en_mask                                   (0x00008000)
#define EMMC_LSADC0_PAD0_LEVEL_SET3_Block3_en(data)                                  (0x00008000&((data)<<15))
#define EMMC_LSADC0_PAD0_LEVEL_SET3_Block3_en_src(data)                              ((0x00008000&(data))>>15)
#define EMMC_LSADC0_PAD0_LEVEL_SET3_get_Block3_en(data)                              ((0x00008000&(data))>>15)
#define EMMC_LSADC0_PAD0_LEVEL_SET3_INT_en3_shift                                    (1)
#define EMMC_LSADC0_PAD0_LEVEL_SET3_INT_en3_mask                                     (0x00000002)
#define EMMC_LSADC0_PAD0_LEVEL_SET3_INT_en3(data)                                    (0x00000002&((data)<<1))
#define EMMC_LSADC0_PAD0_LEVEL_SET3_INT_en3_src(data)                                ((0x00000002&(data))>>1)
#define EMMC_LSADC0_PAD0_LEVEL_SET3_get_INT_en3(data)                                ((0x00000002&(data))>>1)
#define EMMC_LSADC0_PAD0_LEVEL_SET3_INT_pending_bit3_shift                           (0)
#define EMMC_LSADC0_PAD0_LEVEL_SET3_INT_pending_bit3_mask                            (0x00000001)
#define EMMC_LSADC0_PAD0_LEVEL_SET3_INT_pending_bit3(data)                           (0x00000001&((data)<<0))
#define EMMC_LSADC0_PAD0_LEVEL_SET3_INT_pending_bit3_src(data)                       ((0x00000001&(data))>>0)
#define EMMC_LSADC0_PAD0_LEVEL_SET3_get_INT_pending_bit3(data)                       ((0x00000001&(data))>>0)


#define EMMC_LSADC0_PAD0_LEVEL_SET4                                                  0x98012840
#define EMMC_LSADC0_PAD0_LEVEL_SET4_reg_addr                                         "0x98012840"
#define EMMC_LSADC0_PAD0_LEVEL_SET4_reg                                              0x98012840
#define set_EMMC_LSADC0_PAD0_LEVEL_SET4_reg(data)   (*((volatile unsigned int*) EMMC_LSADC0_PAD0_LEVEL_SET4_reg)=data)
#define get_EMMC_LSADC0_PAD0_LEVEL_SET4_reg   (*((volatile unsigned int*) EMMC_LSADC0_PAD0_LEVEL_SET4_reg))
#define EMMC_LSADC0_PAD0_LEVEL_SET4_inst_adr                                         "0x0010"
#define EMMC_LSADC0_PAD0_LEVEL_SET4_inst                                             0x0010
#define EMMC_LSADC0_PAD0_LEVEL_SET4_Level_4_top_bound_shift                          (24)
#define EMMC_LSADC0_PAD0_LEVEL_SET4_Level_4_top_bound_mask                           (0xFF000000)
#define EMMC_LSADC0_PAD0_LEVEL_SET4_Level_4_top_bound(data)                          (0xFF000000&((data)<<24))
#define EMMC_LSADC0_PAD0_LEVEL_SET4_Level_4_top_bound_src(data)                      ((0xFF000000&(data))>>24)
#define EMMC_LSADC0_PAD0_LEVEL_SET4_get_Level_4_top_bound(data)                      ((0xFF000000&(data))>>24)
#define EMMC_LSADC0_PAD0_LEVEL_SET4_Level_4_low_bound_shift                          (16)
#define EMMC_LSADC0_PAD0_LEVEL_SET4_Level_4_low_bound_mask                           (0x00FF0000)
#define EMMC_LSADC0_PAD0_LEVEL_SET4_Level_4_low_bound(data)                          (0x00FF0000&((data)<<16))
#define EMMC_LSADC0_PAD0_LEVEL_SET4_Level_4_low_bound_src(data)                      ((0x00FF0000&(data))>>16)
#define EMMC_LSADC0_PAD0_LEVEL_SET4_get_Level_4_low_bound(data)                      ((0x00FF0000&(data))>>16)
#define EMMC_LSADC0_PAD0_LEVEL_SET4_Block4_en_shift                                  (15)
#define EMMC_LSADC0_PAD0_LEVEL_SET4_Block4_en_mask                                   (0x00008000)
#define EMMC_LSADC0_PAD0_LEVEL_SET4_Block4_en(data)                                  (0x00008000&((data)<<15))
#define EMMC_LSADC0_PAD0_LEVEL_SET4_Block4_en_src(data)                              ((0x00008000&(data))>>15)
#define EMMC_LSADC0_PAD0_LEVEL_SET4_get_Block4_en(data)                              ((0x00008000&(data))>>15)
#define EMMC_LSADC0_PAD0_LEVEL_SET4_INT_en4_shift                                    (1)
#define EMMC_LSADC0_PAD0_LEVEL_SET4_INT_en4_mask                                     (0x00000002)
#define EMMC_LSADC0_PAD0_LEVEL_SET4_INT_en4(data)                                    (0x00000002&((data)<<1))
#define EMMC_LSADC0_PAD0_LEVEL_SET4_INT_en4_src(data)                                ((0x00000002&(data))>>1)
#define EMMC_LSADC0_PAD0_LEVEL_SET4_get_INT_en4(data)                                ((0x00000002&(data))>>1)
#define EMMC_LSADC0_PAD0_LEVEL_SET4_INT_pending_bit4_shift                           (0)
#define EMMC_LSADC0_PAD0_LEVEL_SET4_INT_pending_bit4_mask                            (0x00000001)
#define EMMC_LSADC0_PAD0_LEVEL_SET4_INT_pending_bit4(data)                           (0x00000001&((data)<<0))
#define EMMC_LSADC0_PAD0_LEVEL_SET4_INT_pending_bit4_src(data)                       ((0x00000001&(data))>>0)
#define EMMC_LSADC0_PAD0_LEVEL_SET4_get_INT_pending_bit4(data)                       ((0x00000001&(data))>>0)


#define EMMC_LSADC0_PAD0_LEVEL_SET5                                                  0x98012844
#define EMMC_LSADC0_PAD0_LEVEL_SET5_reg_addr                                         "0x98012844"
#define EMMC_LSADC0_PAD0_LEVEL_SET5_reg                                              0x98012844
#define set_EMMC_LSADC0_PAD0_LEVEL_SET5_reg(data)   (*((volatile unsigned int*) EMMC_LSADC0_PAD0_LEVEL_SET5_reg)=data)
#define get_EMMC_LSADC0_PAD0_LEVEL_SET5_reg   (*((volatile unsigned int*) EMMC_LSADC0_PAD0_LEVEL_SET5_reg))
#define EMMC_LSADC0_PAD0_LEVEL_SET5_inst_adr                                         "0x0011"
#define EMMC_LSADC0_PAD0_LEVEL_SET5_inst                                             0x0011
#define EMMC_LSADC0_PAD0_LEVEL_SET5_Level_5_top_bound_shift                          (24)
#define EMMC_LSADC0_PAD0_LEVEL_SET5_Level_5_top_bound_mask                           (0xFF000000)
#define EMMC_LSADC0_PAD0_LEVEL_SET5_Level_5_top_bound(data)                          (0xFF000000&((data)<<24))
#define EMMC_LSADC0_PAD0_LEVEL_SET5_Level_5_top_bound_src(data)                      ((0xFF000000&(data))>>24)
#define EMMC_LSADC0_PAD0_LEVEL_SET5_get_Level_5_top_bound(data)                      ((0xFF000000&(data))>>24)
#define EMMC_LSADC0_PAD0_LEVEL_SET5_Level_5_low_bound_shift                          (16)
#define EMMC_LSADC0_PAD0_LEVEL_SET5_Level_5_low_bound_mask                           (0x00FF0000)
#define EMMC_LSADC0_PAD0_LEVEL_SET5_Level_5_low_bound(data)                          (0x00FF0000&((data)<<16))
#define EMMC_LSADC0_PAD0_LEVEL_SET5_Level_5_low_bound_src(data)                      ((0x00FF0000&(data))>>16)
#define EMMC_LSADC0_PAD0_LEVEL_SET5_get_Level_5_low_bound(data)                      ((0x00FF0000&(data))>>16)
#define EMMC_LSADC0_PAD0_LEVEL_SET5_Block5_en_shift                                  (15)
#define EMMC_LSADC0_PAD0_LEVEL_SET5_Block5_en_mask                                   (0x00008000)
#define EMMC_LSADC0_PAD0_LEVEL_SET5_Block5_en(data)                                  (0x00008000&((data)<<15))
#define EMMC_LSADC0_PAD0_LEVEL_SET5_Block5_en_src(data)                              ((0x00008000&(data))>>15)
#define EMMC_LSADC0_PAD0_LEVEL_SET5_get_Block5_en(data)                              ((0x00008000&(data))>>15)
#define EMMC_LSADC0_PAD0_LEVEL_SET5_INT_en5_shift                                    (1)
#define EMMC_LSADC0_PAD0_LEVEL_SET5_INT_en5_mask                                     (0x00000002)
#define EMMC_LSADC0_PAD0_LEVEL_SET5_INT_en5(data)                                    (0x00000002&((data)<<1))
#define EMMC_LSADC0_PAD0_LEVEL_SET5_INT_en5_src(data)                                ((0x00000002&(data))>>1)
#define EMMC_LSADC0_PAD0_LEVEL_SET5_get_INT_en5(data)                                ((0x00000002&(data))>>1)
#define EMMC_LSADC0_PAD0_LEVEL_SET5_INT_pending_bit5_shift                           (0)
#define EMMC_LSADC0_PAD0_LEVEL_SET5_INT_pending_bit5_mask                            (0x00000001)
#define EMMC_LSADC0_PAD0_LEVEL_SET5_INT_pending_bit5(data)                           (0x00000001&((data)<<0))
#define EMMC_LSADC0_PAD0_LEVEL_SET5_INT_pending_bit5_src(data)                       ((0x00000001&(data))>>0)
#define EMMC_LSADC0_PAD0_LEVEL_SET5_get_INT_pending_bit5(data)                       ((0x00000001&(data))>>0)


#define EMMC_LSADC0_PAD1_LEVEL_SET0                                                  0x98012848
#define EMMC_LSADC0_PAD1_LEVEL_SET0_reg_addr                                         "0x98012848"
#define EMMC_LSADC0_PAD1_LEVEL_SET0_reg                                              0x98012848
#define set_EMMC_LSADC0_PAD1_LEVEL_SET0_reg(data)   (*((volatile unsigned int*) EMMC_LSADC0_PAD1_LEVEL_SET0_reg)=data)
#define get_EMMC_LSADC0_PAD1_LEVEL_SET0_reg   (*((volatile unsigned int*) EMMC_LSADC0_PAD1_LEVEL_SET0_reg))
#define EMMC_LSADC0_PAD1_LEVEL_SET0_inst_adr                                         "0x0012"
#define EMMC_LSADC0_PAD1_LEVEL_SET0_inst                                             0x0012
#define EMMC_LSADC0_PAD1_LEVEL_SET0_Level_0_top_bound_shift                          (24)
#define EMMC_LSADC0_PAD1_LEVEL_SET0_Level_0_top_bound_mask                           (0xFF000000)
#define EMMC_LSADC0_PAD1_LEVEL_SET0_Level_0_top_bound(data)                          (0xFF000000&((data)<<24))
#define EMMC_LSADC0_PAD1_LEVEL_SET0_Level_0_top_bound_src(data)                      ((0xFF000000&(data))>>24)
#define EMMC_LSADC0_PAD1_LEVEL_SET0_get_Level_0_top_bound(data)                      ((0xFF000000&(data))>>24)
#define EMMC_LSADC0_PAD1_LEVEL_SET0_Level_0_low_bound_shift                          (16)
#define EMMC_LSADC0_PAD1_LEVEL_SET0_Level_0_low_bound_mask                           (0x00FF0000)
#define EMMC_LSADC0_PAD1_LEVEL_SET0_Level_0_low_bound(data)                          (0x00FF0000&((data)<<16))
#define EMMC_LSADC0_PAD1_LEVEL_SET0_Level_0_low_bound_src(data)                      ((0x00FF0000&(data))>>16)
#define EMMC_LSADC0_PAD1_LEVEL_SET0_get_Level_0_low_bound(data)                      ((0x00FF0000&(data))>>16)
#define EMMC_LSADC0_PAD1_LEVEL_SET0_Block0_en_shift                                  (15)
#define EMMC_LSADC0_PAD1_LEVEL_SET0_Block0_en_mask                                   (0x00008000)
#define EMMC_LSADC0_PAD1_LEVEL_SET0_Block0_en(data)                                  (0x00008000&((data)<<15))
#define EMMC_LSADC0_PAD1_LEVEL_SET0_Block0_en_src(data)                              ((0x00008000&(data))>>15)
#define EMMC_LSADC0_PAD1_LEVEL_SET0_get_Block0_en(data)                              ((0x00008000&(data))>>15)
#define EMMC_LSADC0_PAD1_LEVEL_SET0_INT_en0_shift                                    (1)
#define EMMC_LSADC0_PAD1_LEVEL_SET0_INT_en0_mask                                     (0x00000002)
#define EMMC_LSADC0_PAD1_LEVEL_SET0_INT_en0(data)                                    (0x00000002&((data)<<1))
#define EMMC_LSADC0_PAD1_LEVEL_SET0_INT_en0_src(data)                                ((0x00000002&(data))>>1)
#define EMMC_LSADC0_PAD1_LEVEL_SET0_get_INT_en0(data)                                ((0x00000002&(data))>>1)
#define EMMC_LSADC0_PAD1_LEVEL_SET0_INT_pending_bit0_shift                           (0)
#define EMMC_LSADC0_PAD1_LEVEL_SET0_INT_pending_bit0_mask                            (0x00000001)
#define EMMC_LSADC0_PAD1_LEVEL_SET0_INT_pending_bit0(data)                           (0x00000001&((data)<<0))
#define EMMC_LSADC0_PAD1_LEVEL_SET0_INT_pending_bit0_src(data)                       ((0x00000001&(data))>>0)
#define EMMC_LSADC0_PAD1_LEVEL_SET0_get_INT_pending_bit0(data)                       ((0x00000001&(data))>>0)


#define EMMC_LSADC0_PAD1_LEVEL_SET1                                                  0x9801284C
#define EMMC_LSADC0_PAD1_LEVEL_SET1_reg_addr                                         "0x9801284C"
#define EMMC_LSADC0_PAD1_LEVEL_SET1_reg                                              0x9801284C
#define set_EMMC_LSADC0_PAD1_LEVEL_SET1_reg(data)   (*((volatile unsigned int*) EMMC_LSADC0_PAD1_LEVEL_SET1_reg)=data)
#define get_EMMC_LSADC0_PAD1_LEVEL_SET1_reg   (*((volatile unsigned int*) EMMC_LSADC0_PAD1_LEVEL_SET1_reg))
#define EMMC_LSADC0_PAD1_LEVEL_SET1_inst_adr                                         "0x0013"
#define EMMC_LSADC0_PAD1_LEVEL_SET1_inst                                             0x0013
#define EMMC_LSADC0_PAD1_LEVEL_SET1_Level_1_top_bound_shift                          (24)
#define EMMC_LSADC0_PAD1_LEVEL_SET1_Level_1_top_bound_mask                           (0xFF000000)
#define EMMC_LSADC0_PAD1_LEVEL_SET1_Level_1_top_bound(data)                          (0xFF000000&((data)<<24))
#define EMMC_LSADC0_PAD1_LEVEL_SET1_Level_1_top_bound_src(data)                      ((0xFF000000&(data))>>24)
#define EMMC_LSADC0_PAD1_LEVEL_SET1_get_Level_1_top_bound(data)                      ((0xFF000000&(data))>>24)
#define EMMC_LSADC0_PAD1_LEVEL_SET1_Level_0_low_bound_shift                          (16)
#define EMMC_LSADC0_PAD1_LEVEL_SET1_Level_0_low_bound_mask                           (0x00FF0000)
#define EMMC_LSADC0_PAD1_LEVEL_SET1_Level_0_low_bound(data)                          (0x00FF0000&((data)<<16))
#define EMMC_LSADC0_PAD1_LEVEL_SET1_Level_0_low_bound_src(data)                      ((0x00FF0000&(data))>>16)
#define EMMC_LSADC0_PAD1_LEVEL_SET1_get_Level_0_low_bound(data)                      ((0x00FF0000&(data))>>16)
#define EMMC_LSADC0_PAD1_LEVEL_SET1_Block1_en_shift                                  (15)
#define EMMC_LSADC0_PAD1_LEVEL_SET1_Block1_en_mask                                   (0x00008000)
#define EMMC_LSADC0_PAD1_LEVEL_SET1_Block1_en(data)                                  (0x00008000&((data)<<15))
#define EMMC_LSADC0_PAD1_LEVEL_SET1_Block1_en_src(data)                              ((0x00008000&(data))>>15)
#define EMMC_LSADC0_PAD1_LEVEL_SET1_get_Block1_en(data)                              ((0x00008000&(data))>>15)
#define EMMC_LSADC0_PAD1_LEVEL_SET1_INT_en1_shift                                    (1)
#define EMMC_LSADC0_PAD1_LEVEL_SET1_INT_en1_mask                                     (0x00000002)
#define EMMC_LSADC0_PAD1_LEVEL_SET1_INT_en1(data)                                    (0x00000002&((data)<<1))
#define EMMC_LSADC0_PAD1_LEVEL_SET1_INT_en1_src(data)                                ((0x00000002&(data))>>1)
#define EMMC_LSADC0_PAD1_LEVEL_SET1_get_INT_en1(data)                                ((0x00000002&(data))>>1)
#define EMMC_LSADC0_PAD1_LEVEL_SET1_INT_pending_bit1_shift                           (0)
#define EMMC_LSADC0_PAD1_LEVEL_SET1_INT_pending_bit1_mask                            (0x00000001)
#define EMMC_LSADC0_PAD1_LEVEL_SET1_INT_pending_bit1(data)                           (0x00000001&((data)<<0))
#define EMMC_LSADC0_PAD1_LEVEL_SET1_INT_pending_bit1_src(data)                       ((0x00000001&(data))>>0)
#define EMMC_LSADC0_PAD1_LEVEL_SET1_get_INT_pending_bit1(data)                       ((0x00000001&(data))>>0)


#define EMMC_LSADC0_PAD1_LEVEL_SET2                                                  0x98012850
#define EMMC_LSADC0_PAD1_LEVEL_SET2_reg_addr                                         "0x98012850"
#define EMMC_LSADC0_PAD1_LEVEL_SET2_reg                                              0x98012850
#define set_EMMC_LSADC0_PAD1_LEVEL_SET2_reg(data)   (*((volatile unsigned int*) EMMC_LSADC0_PAD1_LEVEL_SET2_reg)=data)
#define get_EMMC_LSADC0_PAD1_LEVEL_SET2_reg   (*((volatile unsigned int*) EMMC_LSADC0_PAD1_LEVEL_SET2_reg))
#define EMMC_LSADC0_PAD1_LEVEL_SET2_inst_adr                                         "0x0014"
#define EMMC_LSADC0_PAD1_LEVEL_SET2_inst                                             0x0014
#define EMMC_LSADC0_PAD1_LEVEL_SET2_Level_2_top_bound_shift                          (24)
#define EMMC_LSADC0_PAD1_LEVEL_SET2_Level_2_top_bound_mask                           (0xFF000000)
#define EMMC_LSADC0_PAD1_LEVEL_SET2_Level_2_top_bound(data)                          (0xFF000000&((data)<<24))
#define EMMC_LSADC0_PAD1_LEVEL_SET2_Level_2_top_bound_src(data)                      ((0xFF000000&(data))>>24)
#define EMMC_LSADC0_PAD1_LEVEL_SET2_get_Level_2_top_bound(data)                      ((0xFF000000&(data))>>24)
#define EMMC_LSADC0_PAD1_LEVEL_SET2_Level_2_low_bound_shift                          (16)
#define EMMC_LSADC0_PAD1_LEVEL_SET2_Level_2_low_bound_mask                           (0x00FF0000)
#define EMMC_LSADC0_PAD1_LEVEL_SET2_Level_2_low_bound(data)                          (0x00FF0000&((data)<<16))
#define EMMC_LSADC0_PAD1_LEVEL_SET2_Level_2_low_bound_src(data)                      ((0x00FF0000&(data))>>16)
#define EMMC_LSADC0_PAD1_LEVEL_SET2_get_Level_2_low_bound(data)                      ((0x00FF0000&(data))>>16)
#define EMMC_LSADC0_PAD1_LEVEL_SET2_Block2_en_shift                                  (15)
#define EMMC_LSADC0_PAD1_LEVEL_SET2_Block2_en_mask                                   (0x00008000)
#define EMMC_LSADC0_PAD1_LEVEL_SET2_Block2_en(data)                                  (0x00008000&((data)<<15))
#define EMMC_LSADC0_PAD1_LEVEL_SET2_Block2_en_src(data)                              ((0x00008000&(data))>>15)
#define EMMC_LSADC0_PAD1_LEVEL_SET2_get_Block2_en(data)                              ((0x00008000&(data))>>15)
#define EMMC_LSADC0_PAD1_LEVEL_SET2_INT_en2_shift                                    (1)
#define EMMC_LSADC0_PAD1_LEVEL_SET2_INT_en2_mask                                     (0x00000002)
#define EMMC_LSADC0_PAD1_LEVEL_SET2_INT_en2(data)                                    (0x00000002&((data)<<1))
#define EMMC_LSADC0_PAD1_LEVEL_SET2_INT_en2_src(data)                                ((0x00000002&(data))>>1)
#define EMMC_LSADC0_PAD1_LEVEL_SET2_get_INT_en2(data)                                ((0x00000002&(data))>>1)
#define EMMC_LSADC0_PAD1_LEVEL_SET2_INT_pending_bit2_shift                           (0)
#define EMMC_LSADC0_PAD1_LEVEL_SET2_INT_pending_bit2_mask                            (0x00000001)
#define EMMC_LSADC0_PAD1_LEVEL_SET2_INT_pending_bit2(data)                           (0x00000001&((data)<<0))
#define EMMC_LSADC0_PAD1_LEVEL_SET2_INT_pending_bit2_src(data)                       ((0x00000001&(data))>>0)
#define EMMC_LSADC0_PAD1_LEVEL_SET2_get_INT_pending_bit2(data)                       ((0x00000001&(data))>>0)


#define EMMC_LSADC0_PAD1_LEVEL_SET3                                                  0x98012854
#define EMMC_LSADC0_PAD1_LEVEL_SET3_reg_addr                                         "0x98012854"
#define EMMC_LSADC0_PAD1_LEVEL_SET3_reg                                              0x98012854
#define set_EMMC_LSADC0_PAD1_LEVEL_SET3_reg(data)   (*((volatile unsigned int*) EMMC_LSADC0_PAD1_LEVEL_SET3_reg)=data)
#define get_EMMC_LSADC0_PAD1_LEVEL_SET3_reg   (*((volatile unsigned int*) EMMC_LSADC0_PAD1_LEVEL_SET3_reg))
#define EMMC_LSADC0_PAD1_LEVEL_SET3_inst_adr                                         "0x0015"
#define EMMC_LSADC0_PAD1_LEVEL_SET3_inst                                             0x0015
#define EMMC_LSADC0_PAD1_LEVEL_SET3_Level_3_top_bound_shift                          (24)
#define EMMC_LSADC0_PAD1_LEVEL_SET3_Level_3_top_bound_mask                           (0xFF000000)
#define EMMC_LSADC0_PAD1_LEVEL_SET3_Level_3_top_bound(data)                          (0xFF000000&((data)<<24))
#define EMMC_LSADC0_PAD1_LEVEL_SET3_Level_3_top_bound_src(data)                      ((0xFF000000&(data))>>24)
#define EMMC_LSADC0_PAD1_LEVEL_SET3_get_Level_3_top_bound(data)                      ((0xFF000000&(data))>>24)
#define EMMC_LSADC0_PAD1_LEVEL_SET3_Level_3_low_bound_shift                          (16)
#define EMMC_LSADC0_PAD1_LEVEL_SET3_Level_3_low_bound_mask                           (0x00FF0000)
#define EMMC_LSADC0_PAD1_LEVEL_SET3_Level_3_low_bound(data)                          (0x00FF0000&((data)<<16))
#define EMMC_LSADC0_PAD1_LEVEL_SET3_Level_3_low_bound_src(data)                      ((0x00FF0000&(data))>>16)
#define EMMC_LSADC0_PAD1_LEVEL_SET3_get_Level_3_low_bound(data)                      ((0x00FF0000&(data))>>16)
#define EMMC_LSADC0_PAD1_LEVEL_SET3_Block3_en_shift                                  (15)
#define EMMC_LSADC0_PAD1_LEVEL_SET3_Block3_en_mask                                   (0x00008000)
#define EMMC_LSADC0_PAD1_LEVEL_SET3_Block3_en(data)                                  (0x00008000&((data)<<15))
#define EMMC_LSADC0_PAD1_LEVEL_SET3_Block3_en_src(data)                              ((0x00008000&(data))>>15)
#define EMMC_LSADC0_PAD1_LEVEL_SET3_get_Block3_en(data)                              ((0x00008000&(data))>>15)
#define EMMC_LSADC0_PAD1_LEVEL_SET3_INT_en3_shift                                    (1)
#define EMMC_LSADC0_PAD1_LEVEL_SET3_INT_en3_mask                                     (0x00000002)
#define EMMC_LSADC0_PAD1_LEVEL_SET3_INT_en3(data)                                    (0x00000002&((data)<<1))
#define EMMC_LSADC0_PAD1_LEVEL_SET3_INT_en3_src(data)                                ((0x00000002&(data))>>1)
#define EMMC_LSADC0_PAD1_LEVEL_SET3_get_INT_en3(data)                                ((0x00000002&(data))>>1)
#define EMMC_LSADC0_PAD1_LEVEL_SET3_INT_pending_bit3_shift                           (0)
#define EMMC_LSADC0_PAD1_LEVEL_SET3_INT_pending_bit3_mask                            (0x00000001)
#define EMMC_LSADC0_PAD1_LEVEL_SET3_INT_pending_bit3(data)                           (0x00000001&((data)<<0))
#define EMMC_LSADC0_PAD1_LEVEL_SET3_INT_pending_bit3_src(data)                       ((0x00000001&(data))>>0)
#define EMMC_LSADC0_PAD1_LEVEL_SET3_get_INT_pending_bit3(data)                       ((0x00000001&(data))>>0)


#define EMMC_LSADC0_PAD1_LEVEL_SET4                                                  0x98012858
#define EMMC_LSADC0_PAD1_LEVEL_SET4_reg_addr                                         "0x98012858"
#define EMMC_LSADC0_PAD1_LEVEL_SET4_reg                                              0x98012858
#define set_EMMC_LSADC0_PAD1_LEVEL_SET4_reg(data)   (*((volatile unsigned int*) EMMC_LSADC0_PAD1_LEVEL_SET4_reg)=data)
#define get_EMMC_LSADC0_PAD1_LEVEL_SET4_reg   (*((volatile unsigned int*) EMMC_LSADC0_PAD1_LEVEL_SET4_reg))
#define EMMC_LSADC0_PAD1_LEVEL_SET4_inst_adr                                         "0x0016"
#define EMMC_LSADC0_PAD1_LEVEL_SET4_inst                                             0x0016
#define EMMC_LSADC0_PAD1_LEVEL_SET4_Level_4_top_bound_shift                          (24)
#define EMMC_LSADC0_PAD1_LEVEL_SET4_Level_4_top_bound_mask                           (0xFF000000)
#define EMMC_LSADC0_PAD1_LEVEL_SET4_Level_4_top_bound(data)                          (0xFF000000&((data)<<24))
#define EMMC_LSADC0_PAD1_LEVEL_SET4_Level_4_top_bound_src(data)                      ((0xFF000000&(data))>>24)
#define EMMC_LSADC0_PAD1_LEVEL_SET4_get_Level_4_top_bound(data)                      ((0xFF000000&(data))>>24)
#define EMMC_LSADC0_PAD1_LEVEL_SET4_Level_4_low_bound_shift                          (16)
#define EMMC_LSADC0_PAD1_LEVEL_SET4_Level_4_low_bound_mask                           (0x00FF0000)
#define EMMC_LSADC0_PAD1_LEVEL_SET4_Level_4_low_bound(data)                          (0x00FF0000&((data)<<16))
#define EMMC_LSADC0_PAD1_LEVEL_SET4_Level_4_low_bound_src(data)                      ((0x00FF0000&(data))>>16)
#define EMMC_LSADC0_PAD1_LEVEL_SET4_get_Level_4_low_bound(data)                      ((0x00FF0000&(data))>>16)
#define EMMC_LSADC0_PAD1_LEVEL_SET4_Block4_en_shift                                  (15)
#define EMMC_LSADC0_PAD1_LEVEL_SET4_Block4_en_mask                                   (0x00008000)
#define EMMC_LSADC0_PAD1_LEVEL_SET4_Block4_en(data)                                  (0x00008000&((data)<<15))
#define EMMC_LSADC0_PAD1_LEVEL_SET4_Block4_en_src(data)                              ((0x00008000&(data))>>15)
#define EMMC_LSADC0_PAD1_LEVEL_SET4_get_Block4_en(data)                              ((0x00008000&(data))>>15)
#define EMMC_LSADC0_PAD1_LEVEL_SET4_INT_en4_shift                                    (1)
#define EMMC_LSADC0_PAD1_LEVEL_SET4_INT_en4_mask                                     (0x00000002)
#define EMMC_LSADC0_PAD1_LEVEL_SET4_INT_en4(data)                                    (0x00000002&((data)<<1))
#define EMMC_LSADC0_PAD1_LEVEL_SET4_INT_en4_src(data)                                ((0x00000002&(data))>>1)
#define EMMC_LSADC0_PAD1_LEVEL_SET4_get_INT_en4(data)                                ((0x00000002&(data))>>1)
#define EMMC_LSADC0_PAD1_LEVEL_SET4_INT_pending_bit4_shift                           (0)
#define EMMC_LSADC0_PAD1_LEVEL_SET4_INT_pending_bit4_mask                            (0x00000001)
#define EMMC_LSADC0_PAD1_LEVEL_SET4_INT_pending_bit4(data)                           (0x00000001&((data)<<0))
#define EMMC_LSADC0_PAD1_LEVEL_SET4_INT_pending_bit4_src(data)                       ((0x00000001&(data))>>0)
#define EMMC_LSADC0_PAD1_LEVEL_SET4_get_INT_pending_bit4(data)                       ((0x00000001&(data))>>0)


#define EMMC_LSADC0_PAD1_LEVEL_SET5                                                  0x9801285C
#define EMMC_LSADC0_PAD1_LEVEL_SET5_reg_addr                                         "0x9801285C"
#define EMMC_LSADC0_PAD1_LEVEL_SET5_reg                                              0x9801285C
#define set_EMMC_LSADC0_PAD1_LEVEL_SET5_reg(data)   (*((volatile unsigned int*) EMMC_LSADC0_PAD1_LEVEL_SET5_reg)=data)
#define get_EMMC_LSADC0_PAD1_LEVEL_SET5_reg   (*((volatile unsigned int*) EMMC_LSADC0_PAD1_LEVEL_SET5_reg))
#define EMMC_LSADC0_PAD1_LEVEL_SET5_inst_adr                                         "0x0017"
#define EMMC_LSADC0_PAD1_LEVEL_SET5_inst                                             0x0017
#define EMMC_LSADC0_PAD1_LEVEL_SET5_Level_5_top_bound_shift                          (24)
#define EMMC_LSADC0_PAD1_LEVEL_SET5_Level_5_top_bound_mask                           (0xFF000000)
#define EMMC_LSADC0_PAD1_LEVEL_SET5_Level_5_top_bound(data)                          (0xFF000000&((data)<<24))
#define EMMC_LSADC0_PAD1_LEVEL_SET5_Level_5_top_bound_src(data)                      ((0xFF000000&(data))>>24)
#define EMMC_LSADC0_PAD1_LEVEL_SET5_get_Level_5_top_bound(data)                      ((0xFF000000&(data))>>24)
#define EMMC_LSADC0_PAD1_LEVEL_SET5_Level_5_low_bound_shift                          (16)
#define EMMC_LSADC0_PAD1_LEVEL_SET5_Level_5_low_bound_mask                           (0x00FF0000)
#define EMMC_LSADC0_PAD1_LEVEL_SET5_Level_5_low_bound(data)                          (0x00FF0000&((data)<<16))
#define EMMC_LSADC0_PAD1_LEVEL_SET5_Level_5_low_bound_src(data)                      ((0x00FF0000&(data))>>16)
#define EMMC_LSADC0_PAD1_LEVEL_SET5_get_Level_5_low_bound(data)                      ((0x00FF0000&(data))>>16)
#define EMMC_LSADC0_PAD1_LEVEL_SET5_Block5_en_shift                                  (15)
#define EMMC_LSADC0_PAD1_LEVEL_SET5_Block5_en_mask                                   (0x00008000)
#define EMMC_LSADC0_PAD1_LEVEL_SET5_Block5_en(data)                                  (0x00008000&((data)<<15))
#define EMMC_LSADC0_PAD1_LEVEL_SET5_Block5_en_src(data)                              ((0x00008000&(data))>>15)
#define EMMC_LSADC0_PAD1_LEVEL_SET5_get_Block5_en(data)                              ((0x00008000&(data))>>15)
#define EMMC_LSADC0_PAD1_LEVEL_SET5_INT_en5_shift                                    (1)
#define EMMC_LSADC0_PAD1_LEVEL_SET5_INT_en5_mask                                     (0x00000002)
#define EMMC_LSADC0_PAD1_LEVEL_SET5_INT_en5(data)                                    (0x00000002&((data)<<1))
#define EMMC_LSADC0_PAD1_LEVEL_SET5_INT_en5_src(data)                                ((0x00000002&(data))>>1)
#define EMMC_LSADC0_PAD1_LEVEL_SET5_get_INT_en5(data)                                ((0x00000002&(data))>>1)
#define EMMC_LSADC0_PAD1_LEVEL_SET5_INT_pending_bit5_shift                           (0)
#define EMMC_LSADC0_PAD1_LEVEL_SET5_INT_pending_bit5_mask                            (0x00000001)
#define EMMC_LSADC0_PAD1_LEVEL_SET5_INT_pending_bit5(data)                           (0x00000001&((data)<<0))
#define EMMC_LSADC0_PAD1_LEVEL_SET5_INT_pending_bit5_src(data)                       ((0x00000001&(data))>>0)
#define EMMC_LSADC0_PAD1_LEVEL_SET5_get_INT_pending_bit5(data)                       ((0x00000001&(data))>>0)


#define EMMC_LSADC0_INT_PAD0                                                         0x98012878
#define EMMC_LSADC0_INT_PAD0_reg_addr                                                "0x98012878"
#define EMMC_LSADC0_INT_PAD0_reg                                                     0x98012878
#define set_EMMC_LSADC0_INT_PAD0_reg(data)   (*((volatile unsigned int*) EMMC_LSADC0_INT_PAD0_reg)=data)
#define get_EMMC_LSADC0_INT_PAD0_reg   (*((volatile unsigned int*) EMMC_LSADC0_INT_PAD0_reg))
#define EMMC_LSADC0_INT_PAD0_inst_adr                                                "0x001E"
#define EMMC_LSADC0_INT_PAD0_inst                                                    0x001E
#define EMMC_LSADC0_INT_PAD0_ADC_value0latch_shift                                   (8)
#define EMMC_LSADC0_INT_PAD0_ADC_value0latch_mask                                    (0x00003F00)
#define EMMC_LSADC0_INT_PAD0_ADC_value0latch(data)                                   (0x00003F00&((data)<<8))
#define EMMC_LSADC0_INT_PAD0_ADC_value0latch_src(data)                               ((0x00003F00&(data))>>8)
#define EMMC_LSADC0_INT_PAD0_get_ADC_value0latch(data)                               ((0x00003F00&(data))>>8)
#define EMMC_LSADC0_INT_PAD0_INT_latchstatus_shift                                   (0)
#define EMMC_LSADC0_INT_PAD0_INT_latchstatus_mask                                    (0x00000001)
#define EMMC_LSADC0_INT_PAD0_INT_latchstatus(data)                                   (0x00000001&((data)<<0))
#define EMMC_LSADC0_INT_PAD0_INT_latchstatus_src(data)                               ((0x00000001&(data))>>0)
#define EMMC_LSADC0_INT_PAD0_get_INT_latchstatus(data)                               ((0x00000001&(data))>>0)


#define EMMC_LSADC0_INT_PAD1                                                         0x9801287C
#define EMMC_LSADC0_INT_PAD1_reg_addr                                                "0x9801287C"
#define EMMC_LSADC0_INT_PAD1_reg                                                     0x9801287C
#define set_EMMC_LSADC0_INT_PAD1_reg(data)   (*((volatile unsigned int*) EMMC_LSADC0_INT_PAD1_reg)=data)
#define get_EMMC_LSADC0_INT_PAD1_reg   (*((volatile unsigned int*) EMMC_LSADC0_INT_PAD1_reg))
#define EMMC_LSADC0_INT_PAD1_inst_adr                                                "0x001F"
#define EMMC_LSADC0_INT_PAD1_inst                                                    0x001F
#define EMMC_LSADC0_INT_PAD1_ADC_value1latch_shift                                   (8)
#define EMMC_LSADC0_INT_PAD1_ADC_value1latch_mask                                    (0x00003F00)
#define EMMC_LSADC0_INT_PAD1_ADC_value1latch(data)                                   (0x00003F00&((data)<<8))
#define EMMC_LSADC0_INT_PAD1_ADC_value1latch_src(data)                               ((0x00003F00&(data))>>8)
#define EMMC_LSADC0_INT_PAD1_get_ADC_value1latch(data)                               ((0x00003F00&(data))>>8)
#define EMMC_LSADC0_INT_PAD1_INT_latchstatus_shift                                   (0)
#define EMMC_LSADC0_INT_PAD1_INT_latchstatus_mask                                    (0x00000001)
#define EMMC_LSADC0_INT_PAD1_INT_latchstatus(data)                                   (0x00000001&((data)<<0))
#define EMMC_LSADC0_INT_PAD1_INT_latchstatus_src(data)                               ((0x00000001&(data))>>0)
#define EMMC_LSADC0_INT_PAD1_get_INT_latchstatus(data)                               ((0x00000001&(data))>>0)


#define EMMC_LSADC_POWER                                                             0x98012880
#define EMMC_LSADC_POWER_reg_addr                                                    "0x98012880"
#define EMMC_LSADC_POWER_reg                                                         0x98012880
#define set_EMMC_LSADC_POWER_reg(data)   (*((volatile unsigned int*) EMMC_LSADC_POWER_reg)=data)
#define get_EMMC_LSADC_POWER_reg   (*((volatile unsigned int*) EMMC_LSADC_POWER_reg))
#define EMMC_LSADC_POWER_inst_adr                                                    "0x0020"
#define EMMC_LSADC_POWER_inst                                                        0x0020
#define EMMC_LSADC_POWER_lsadc1_clk_gating_en_shift                                  (1)
#define EMMC_LSADC_POWER_lsadc1_clk_gating_en_mask                                   (0x00000002)
#define EMMC_LSADC_POWER_lsadc1_clk_gating_en(data)                                  (0x00000002&((data)<<1))
#define EMMC_LSADC_POWER_lsadc1_clk_gating_en_src(data)                              ((0x00000002&(data))>>1)
#define EMMC_LSADC_POWER_get_lsadc1_clk_gating_en(data)                              ((0x00000002&(data))>>1)
#define EMMC_LSADC_POWER_lsadc0_clk_gating_en_shift                                  (0)
#define EMMC_LSADC_POWER_lsadc0_clk_gating_en_mask                                   (0x00000001)
#define EMMC_LSADC_POWER_lsadc0_clk_gating_en(data)                                  (0x00000001&((data)<<0))
#define EMMC_LSADC_POWER_lsadc0_clk_gating_en_src(data)                              ((0x00000001&(data))>>0)
#define EMMC_LSADC_POWER_get_lsadc0_clk_gating_en(data)                              ((0x00000001&(data))>>0)


#define EMMC_LSADC_DBG                                                               0x98012884
#define EMMC_LSADC_DBG_reg_addr                                                      "0x98012884"
#define EMMC_LSADC_DBG_reg                                                           0x98012884
#define set_EMMC_LSADC_DBG_reg(data)   (*((volatile unsigned int*) EMMC_LSADC_DBG_reg)=data)
#define get_EMMC_LSADC_DBG_reg   (*((volatile unsigned int*) EMMC_LSADC_DBG_reg))
#define EMMC_LSADC_DBG_inst_adr                                                      "0x0021"
#define EMMC_LSADC_DBG_inst                                                          0x0021
#define EMMC_LSADC_DBG_sel_shift                                                     (1)
#define EMMC_LSADC_DBG_sel_mask                                                      (0x00000002)
#define EMMC_LSADC_DBG_sel(data)                                                     (0x00000002&((data)<<1))
#define EMMC_LSADC_DBG_sel_src(data)                                                 ((0x00000002&(data))>>1)
#define EMMC_LSADC_DBG_get_sel(data)                                                 ((0x00000002&(data))>>1)
#define EMMC_LSADC_DBG_enable_shift                                                  (0)
#define EMMC_LSADC_DBG_enable_mask                                                   (0x00000001)
#define EMMC_LSADC_DBG_enable(data)                                                  (0x00000001&((data)<<0))
#define EMMC_LSADC_DBG_enable_src(data)                                              ((0x00000001&(data))>>0)
#define EMMC_LSADC_DBG_get_enable(data)                                              ((0x00000001&(data))>>0)


#define EMMC_LSADC_ANA_TEST                                                          0x98012888
#define EMMC_LSADC_ANA_TEST_reg_addr                                                 "0x98012888"
#define EMMC_LSADC_ANA_TEST_reg                                                      0x98012888
#define set_EMMC_LSADC_ANA_TEST_reg(data)   (*((volatile unsigned int*) EMMC_LSADC_ANA_TEST_reg)=data)
#define get_EMMC_LSADC_ANA_TEST_reg   (*((volatile unsigned int*) EMMC_LSADC_ANA_TEST_reg))
#define EMMC_LSADC_ANA_TEST_inst_adr                                                 "0x0022"
#define EMMC_LSADC_ANA_TEST_inst                                                     0x0022
#define EMMC_LSADC_ANA_TEST_sel_shift                                                (0)
#define EMMC_LSADC_ANA_TEST_sel_mask                                                 (0x00000001)
#define EMMC_LSADC_ANA_TEST_sel(data)                                                (0x00000001&((data)<<0))
#define EMMC_LSADC_ANA_TEST_sel_src(data)                                            ((0x00000001&(data))>>0)
#define EMMC_LSADC_ANA_TEST_get_sel(data)                                            ((0x00000001&(data))>>0)


#define EMMC_LSADC1_PAD0                                                             0x98012900
#define EMMC_LSADC1_PAD0_reg_addr                                                    "0x98012900"
#define EMMC_LSADC1_PAD0_reg                                                         0x98012900
#define set_EMMC_LSADC1_PAD0_reg(data)   (*((volatile unsigned int*) EMMC_LSADC1_PAD0_reg)=data)
#define get_EMMC_LSADC1_PAD0_reg   (*((volatile unsigned int*) EMMC_LSADC1_PAD0_reg))
#define EMMC_LSADC1_PAD0_inst_adr                                                    "0x0040"
#define EMMC_LSADC1_PAD0_inst                                                        0x0040
#define EMMC_LSADC1_PAD0_pad0_active_shift                                           (31)
#define EMMC_LSADC1_PAD0_pad0_active_mask                                            (0x80000000)
#define EMMC_LSADC1_PAD0_pad0_active(data)                                           (0x80000000&((data)<<31))
#define EMMC_LSADC1_PAD0_pad0_active_src(data)                                       ((0x80000000&(data))>>31)
#define EMMC_LSADC1_PAD0_get_pad0_active(data)                                       ((0x80000000&(data))>>31)
#define EMMC_LSADC1_PAD0_pad0_vref_sel_shift                                         (24)
#define EMMC_LSADC1_PAD0_pad0_vref_sel_mask                                          (0x01000000)
#define EMMC_LSADC1_PAD0_pad0_vref_sel(data)                                         (0x01000000&((data)<<24))
#define EMMC_LSADC1_PAD0_pad0_vref_sel_src(data)                                     ((0x01000000&(data))>>24)
#define EMMC_LSADC1_PAD0_get_pad0_vref_sel(data)                                     ((0x01000000&(data))>>24)
#define EMMC_LSADC1_PAD0_pad0_thred_shift                                            (16)
#define EMMC_LSADC1_PAD0_pad0_thred_mask                                             (0x00FF0000)
#define EMMC_LSADC1_PAD0_pad0_thred(data)                                            (0x00FF0000&((data)<<16))
#define EMMC_LSADC1_PAD0_pad0_thred_src(data)                                        ((0x00FF0000&(data))>>16)
#define EMMC_LSADC1_PAD0_get_pad0_thred(data)                                        ((0x00FF0000&(data))>>16)
#define EMMC_LSADC1_PAD0_DUMMY_shift                                                 (13)
#define EMMC_LSADC1_PAD0_DUMMY_mask                                                  (0x0000E000)
#define EMMC_LSADC1_PAD0_DUMMY(data)                                                 (0x0000E000&((data)<<13))
#define EMMC_LSADC1_PAD0_DUMMY_src(data)                                             ((0x0000E000&(data))>>13)
#define EMMC_LSADC1_PAD0_get_DUMMY(data)                                             ((0x0000E000&(data))>>13)
#define EMMC_LSADC1_PAD0_pad0_sw_shift                                               (12)
#define EMMC_LSADC1_PAD0_pad0_sw_mask                                                (0x00001000)
#define EMMC_LSADC1_PAD0_pad0_sw(data)                                               (0x00001000&((data)<<12))
#define EMMC_LSADC1_PAD0_pad0_sw_src(data)                                           ((0x00001000&(data))>>12)
#define EMMC_LSADC1_PAD0_get_pad0_sw(data)                                           ((0x00001000&(data))>>12)
#define EMMC_LSADC1_PAD0_pad0_ctrl_shift                                             (8)
#define EMMC_LSADC1_PAD0_pad0_ctrl_mask                                              (0x00000100)
#define EMMC_LSADC1_PAD0_pad0_ctrl(data)                                             (0x00000100&((data)<<8))
#define EMMC_LSADC1_PAD0_pad0_ctrl_src(data)                                         ((0x00000100&(data))>>8)
#define EMMC_LSADC1_PAD0_get_pad0_ctrl(data)                                         ((0x00000100&(data))>>8)
#define EMMC_LSADC1_PAD0_adc_val0_shift                                              (0)
#define EMMC_LSADC1_PAD0_adc_val0_mask                                               (0x0000003F)
#define EMMC_LSADC1_PAD0_adc_val0(data)                                              (0x0000003F&((data)<<0))
#define EMMC_LSADC1_PAD0_adc_val0_src(data)                                          ((0x0000003F&(data))>>0)
#define EMMC_LSADC1_PAD0_get_adc_val0(data)                                          ((0x0000003F&(data))>>0)


#define EMMC_LSADC1_PAD1                                                             0x98012904
#define EMMC_LSADC1_PAD1_reg_addr                                                    "0x98012904"
#define EMMC_LSADC1_PAD1_reg                                                         0x98012904
#define set_EMMC_LSADC1_PAD1_reg(data)   (*((volatile unsigned int*) EMMC_LSADC1_PAD1_reg)=data)
#define get_EMMC_LSADC1_PAD1_reg   (*((volatile unsigned int*) EMMC_LSADC1_PAD1_reg))
#define EMMC_LSADC1_PAD1_inst_adr                                                    "0x0041"
#define EMMC_LSADC1_PAD1_inst                                                        0x0041
#define EMMC_LSADC1_PAD1_pad1_active_shift                                           (31)
#define EMMC_LSADC1_PAD1_pad1_active_mask                                            (0x80000000)
#define EMMC_LSADC1_PAD1_pad1_active(data)                                           (0x80000000&((data)<<31))
#define EMMC_LSADC1_PAD1_pad1_active_src(data)                                       ((0x80000000&(data))>>31)
#define EMMC_LSADC1_PAD1_get_pad1_active(data)                                       ((0x80000000&(data))>>31)
#define EMMC_LSADC1_PAD1_Pad1_vref_sel_shift                                         (24)
#define EMMC_LSADC1_PAD1_Pad1_vref_sel_mask                                          (0x01000000)
#define EMMC_LSADC1_PAD1_Pad1_vref_sel(data)                                         (0x01000000&((data)<<24))
#define EMMC_LSADC1_PAD1_Pad1_vref_sel_src(data)                                     ((0x01000000&(data))>>24)
#define EMMC_LSADC1_PAD1_get_Pad1_vref_sel(data)                                     ((0x01000000&(data))>>24)
#define EMMC_LSADC1_PAD1_Pad1_thred_shift                                            (16)
#define EMMC_LSADC1_PAD1_Pad1_thred_mask                                             (0x00FF0000)
#define EMMC_LSADC1_PAD1_Pad1_thred(data)                                            (0x00FF0000&((data)<<16))
#define EMMC_LSADC1_PAD1_Pad1_thred_src(data)                                        ((0x00FF0000&(data))>>16)
#define EMMC_LSADC1_PAD1_get_Pad1_thred(data)                                        ((0x00FF0000&(data))>>16)
#define EMMC_LSADC1_PAD1_DUMMY1_shift                                                (13)
#define EMMC_LSADC1_PAD1_DUMMY1_mask                                                 (0x0000E000)
#define EMMC_LSADC1_PAD1_DUMMY1(data)                                                (0x0000E000&((data)<<13))
#define EMMC_LSADC1_PAD1_DUMMY1_src(data)                                            ((0x0000E000&(data))>>13)
#define EMMC_LSADC1_PAD1_get_DUMMY1(data)                                            ((0x0000E000&(data))>>13)
#define EMMC_LSADC1_PAD1_Pad1_sw_shift                                               (12)
#define EMMC_LSADC1_PAD1_Pad1_sw_mask                                                (0x00001000)
#define EMMC_LSADC1_PAD1_Pad1_sw(data)                                               (0x00001000&((data)<<12))
#define EMMC_LSADC1_PAD1_Pad1_sw_src(data)                                           ((0x00001000&(data))>>12)
#define EMMC_LSADC1_PAD1_get_Pad1_sw(data)                                           ((0x00001000&(data))>>12)
#define EMMC_LSADC1_PAD1_Pad1_ctrl_shift                                             (8)
#define EMMC_LSADC1_PAD1_Pad1_ctrl_mask                                              (0x00000100)
#define EMMC_LSADC1_PAD1_Pad1_ctrl(data)                                             (0x00000100&((data)<<8))
#define EMMC_LSADC1_PAD1_Pad1_ctrl_src(data)                                         ((0x00000100&(data))>>8)
#define EMMC_LSADC1_PAD1_get_Pad1_ctrl(data)                                         ((0x00000100&(data))>>8)
#define EMMC_LSADC1_PAD1_adc_val0_shift                                              (0)
#define EMMC_LSADC1_PAD1_adc_val0_mask                                               (0x0000003F)
#define EMMC_LSADC1_PAD1_adc_val0(data)                                              (0x0000003F&((data)<<0))
#define EMMC_LSADC1_PAD1_adc_val0_src(data)                                          ((0x0000003F&(data))>>0)
#define EMMC_LSADC1_PAD1_get_adc_val0(data)                                          ((0x0000003F&(data))>>0)


#define EMMC_LSADC1_CTRL                                                             0x98012920
#define EMMC_LSADC1_CTRL_reg_addr                                                    "0x98012920"
#define EMMC_LSADC1_CTRL_reg                                                         0x98012920
#define set_EMMC_LSADC1_CTRL_reg(data)   (*((volatile unsigned int*) EMMC_LSADC1_CTRL_reg)=data)
#define get_EMMC_LSADC1_CTRL_reg   (*((volatile unsigned int*) EMMC_LSADC1_CTRL_reg))
#define EMMC_LSADC1_CTRL_inst_adr                                                    "0x0048"
#define EMMC_LSADC1_CTRL_inst                                                        0x0048
#define EMMC_LSADC1_CTRL_Sel_wait_shift                                              (28)
#define EMMC_LSADC1_CTRL_Sel_wait_mask                                               (0xF0000000)
#define EMMC_LSADC1_CTRL_Sel_wait(data)                                              (0xF0000000&((data)<<28))
#define EMMC_LSADC1_CTRL_Sel_wait_src(data)                                          ((0xF0000000&(data))>>28)
#define EMMC_LSADC1_CTRL_get_Sel_wait(data)                                          ((0xF0000000&(data))>>28)
#define EMMC_LSADC1_CTRL_Sel_adc_ck_shift                                            (24)
#define EMMC_LSADC1_CTRL_Sel_adc_ck_mask                                             (0x0F000000)
#define EMMC_LSADC1_CTRL_Sel_adc_ck(data)                                            (0x0F000000&((data)<<24))
#define EMMC_LSADC1_CTRL_Sel_adc_ck_src(data)                                        ((0x0F000000&(data))>>24)
#define EMMC_LSADC1_CTRL_get_Sel_adc_ck(data)                                        ((0x0F000000&(data))>>24)
#define EMMC_LSADC1_CTRL_Debounce_cnt_shift                                          (16)
#define EMMC_LSADC1_CTRL_Debounce_cnt_mask                                           (0x00FF0000)
#define EMMC_LSADC1_CTRL_Debounce_cnt(data)                                          (0x00FF0000&((data)<<16))
#define EMMC_LSADC1_CTRL_Debounce_cnt_src(data)                                      ((0x00FF0000&(data))>>16)
#define EMMC_LSADC1_CTRL_get_Debounce_cnt(data)                                      ((0x00FF0000&(data))>>16)
#define EMMC_LSADC1_CTRL_Dout_Test_IN_shift                                          (8)
#define EMMC_LSADC1_CTRL_Dout_Test_IN_mask                                           (0x0000FF00)
#define EMMC_LSADC1_CTRL_Dout_Test_IN(data)                                          (0x0000FF00&((data)<<8))
#define EMMC_LSADC1_CTRL_Dout_Test_IN_src(data)                                      ((0x0000FF00&(data))>>8)
#define EMMC_LSADC1_CTRL_get_Dout_Test_IN(data)                                      ((0x0000FF00&(data))>>8)
#define EMMC_LSADC1_CTRL_vdd_gnd_sel_shift                                           (5)
#define EMMC_LSADC1_CTRL_vdd_gnd_sel_mask                                            (0x00000020)
#define EMMC_LSADC1_CTRL_vdd_gnd_sel(data)                                           (0x00000020&((data)<<5))
#define EMMC_LSADC1_CTRL_vdd_gnd_sel_src(data)                                       ((0x00000020&(data))>>5)
#define EMMC_LSADC1_CTRL_get_vdd_gnd_sel(data)                                       ((0x00000020&(data))>>5)
#define EMMC_LSADC1_CTRL_vdd_gnd_en_shift                                            (4)
#define EMMC_LSADC1_CTRL_vdd_gnd_en_mask                                             (0x00000010)
#define EMMC_LSADC1_CTRL_vdd_gnd_en(data)                                            (0x00000010&((data)<<4))
#define EMMC_LSADC1_CTRL_vdd_gnd_en_src(data)                                        ((0x00000010&(data))>>4)
#define EMMC_LSADC1_CTRL_get_vdd_gnd_en(data)                                        ((0x00000010&(data))>>4)
#define EMMC_LSADC1_CTRL_Test_en_shift                                               (1)
#define EMMC_LSADC1_CTRL_Test_en_mask                                                (0x00000002)
#define EMMC_LSADC1_CTRL_Test_en(data)                                               (0x00000002&((data)<<1))
#define EMMC_LSADC1_CTRL_Test_en_src(data)                                           ((0x00000002&(data))>>1)
#define EMMC_LSADC1_CTRL_get_Test_en(data)                                           ((0x00000002&(data))>>1)
#define EMMC_LSADC1_CTRL_Enable_shift                                                (0)
#define EMMC_LSADC1_CTRL_Enable_mask                                                 (0x00000001)
#define EMMC_LSADC1_CTRL_Enable(data)                                                (0x00000001&((data)<<0))
#define EMMC_LSADC1_CTRL_Enable_src(data)                                            ((0x00000001&(data))>>0)
#define EMMC_LSADC1_CTRL_get_Enable(data)                                            ((0x00000001&(data))>>0)


#define EMMC_LSADC1_STATUS                                                           0x98012924
#define EMMC_LSADC1_STATUS_reg_addr                                                  "0x98012924"
#define EMMC_LSADC1_STATUS_reg                                                       0x98012924
#define set_EMMC_LSADC1_STATUS_reg(data)   (*((volatile unsigned int*) EMMC_LSADC1_STATUS_reg)=data)
#define get_EMMC_LSADC1_STATUS_reg   (*((volatile unsigned int*) EMMC_LSADC1_STATUS_reg))
#define EMMC_LSADC1_STATUS_inst_adr                                                  "0x0049"
#define EMMC_LSADC1_STATUS_inst                                                      0x0049
#define EMMC_LSADC1_STATUS_IRQ_En_shift                                              (24)
#define EMMC_LSADC1_STATUS_IRQ_En_mask                                               (0xFF000000)
#define EMMC_LSADC1_STATUS_IRQ_En(data)                                              (0xFF000000&((data)<<24))
#define EMMC_LSADC1_STATUS_IRQ_En_src(data)                                          ((0xFF000000&(data))>>24)
#define EMMC_LSADC1_STATUS_get_IRQ_En(data)                                          ((0xFF000000&(data))>>24)
#define EMMC_LSADC1_STATUS_PAD_CNT_shift                                             (20)
#define EMMC_LSADC1_STATUS_PAD_CNT_mask                                              (0x00F00000)
#define EMMC_LSADC1_STATUS_PAD_CNT(data)                                             (0x00F00000&((data)<<20))
#define EMMC_LSADC1_STATUS_PAD_CNT_src(data)                                         ((0x00F00000&(data))>>20)
#define EMMC_LSADC1_STATUS_get_PAD_CNT(data)                                         ((0x00F00000&(data))>>20)
#define EMMC_LSADC1_STATUS_ADC_busy_shift                                            (19)
#define EMMC_LSADC1_STATUS_ADC_busy_mask                                             (0x00080000)
#define EMMC_LSADC1_STATUS_ADC_busy(data)                                            (0x00080000&((data)<<19))
#define EMMC_LSADC1_STATUS_ADC_busy_src(data)                                        ((0x00080000&(data))>>19)
#define EMMC_LSADC1_STATUS_get_ADC_busy(data)                                        ((0x00080000&(data))>>19)
#define EMMC_LSADC1_STATUS_pad_ctrl_shift                                            (12)
#define EMMC_LSADC1_STATUS_pad_ctrl_mask                                             (0x0001F000)
#define EMMC_LSADC1_STATUS_pad_ctrl(data)                                            (0x0001F000&((data)<<12))
#define EMMC_LSADC1_STATUS_pad_ctrl_src(data)                                        ((0x0001F000&(data))>>12)
#define EMMC_LSADC1_STATUS_get_pad_ctrl(data)                                        ((0x0001F000&(data))>>12)
#define EMMC_LSADC1_STATUS_Pad1_status_shift                                         (1)
#define EMMC_LSADC1_STATUS_Pad1_status_mask                                          (0x00000002)
#define EMMC_LSADC1_STATUS_Pad1_status(data)                                         (0x00000002&((data)<<1))
#define EMMC_LSADC1_STATUS_Pad1_status_src(data)                                     ((0x00000002&(data))>>1)
#define EMMC_LSADC1_STATUS_get_Pad1_status(data)                                     ((0x00000002&(data))>>1)
#define EMMC_LSADC1_STATUS_Pad0_status_shift                                         (0)
#define EMMC_LSADC1_STATUS_Pad0_status_mask                                          (0x00000001)
#define EMMC_LSADC1_STATUS_Pad0_status(data)                                         (0x00000001&((data)<<0))
#define EMMC_LSADC1_STATUS_Pad0_status_src(data)                                     ((0x00000001&(data))>>0)
#define EMMC_LSADC1_STATUS_get_Pad0_status(data)                                     ((0x00000001&(data))>>0)


#define EMMC_LSADC1_ANALOG_CTRL                                                      0x98012928
#define EMMC_LSADC1_ANALOG_CTRL_reg_addr                                             "0x98012928"
#define EMMC_LSADC1_ANALOG_CTRL_reg                                                  0x98012928
#define set_EMMC_LSADC1_ANALOG_CTRL_reg(data)   (*((volatile unsigned int*) EMMC_LSADC1_ANALOG_CTRL_reg)=data)
#define get_EMMC_LSADC1_ANALOG_CTRL_reg   (*((volatile unsigned int*) EMMC_LSADC1_ANALOG_CTRL_reg))
#define EMMC_LSADC1_ANALOG_CTRL_inst_adr                                             "0x004A"
#define EMMC_LSADC1_ANALOG_CTRL_inst                                                 0x004A
#define EMMC_LSADC1_ANALOG_CTRL_test_in_en_shift                                     (31)
#define EMMC_LSADC1_ANALOG_CTRL_test_in_en_mask                                      (0x80000000)
#define EMMC_LSADC1_ANALOG_CTRL_test_in_en(data)                                     (0x80000000&((data)<<31))
#define EMMC_LSADC1_ANALOG_CTRL_test_in_en_src(data)                                 ((0x80000000&(data))>>31)
#define EMMC_LSADC1_ANALOG_CTRL_get_test_in_en(data)                                 ((0x80000000&(data))>>31)
#define EMMC_LSADC1_ANALOG_CTRL_DUMMY2_shift                                         (20)
#define EMMC_LSADC1_ANALOG_CTRL_DUMMY2_mask                                          (0x00F00000)
#define EMMC_LSADC1_ANALOG_CTRL_DUMMY2(data)                                         (0x00F00000&((data)<<20))
#define EMMC_LSADC1_ANALOG_CTRL_DUMMY2_src(data)                                     ((0x00F00000&(data))>>20)
#define EMMC_LSADC1_ANALOG_CTRL_get_DUMMY2(data)                                     ((0x00F00000&(data))>>20)
#define EMMC_LSADC1_ANALOG_CTRL_JD_sbias_shift                                       (16)
#define EMMC_LSADC1_ANALOG_CTRL_JD_sbias_mask                                        (0x00030000)
#define EMMC_LSADC1_ANALOG_CTRL_JD_sbias(data)                                       (0x00030000&((data)<<16))
#define EMMC_LSADC1_ANALOG_CTRL_JD_sbias_src(data)                                   ((0x00030000&(data))>>16)
#define EMMC_LSADC1_ANALOG_CTRL_get_JD_sbias(data)                                   ((0x00030000&(data))>>16)
#define EMMC_LSADC1_ANALOG_CTRL_JD_adsbias_shift                                     (12)
#define EMMC_LSADC1_ANALOG_CTRL_JD_adsbias_mask                                      (0x00003000)
#define EMMC_LSADC1_ANALOG_CTRL_JD_adsbias(data)                                     (0x00003000&((data)<<12))
#define EMMC_LSADC1_ANALOG_CTRL_JD_adsbias_src(data)                                 ((0x00003000&(data))>>12)
#define EMMC_LSADC1_ANALOG_CTRL_get_JD_adsbias(data)                                 ((0x00003000&(data))>>12)
#define EMMC_LSADC1_ANALOG_CTRL_JD_DUMMY_shift                                       (10)
#define EMMC_LSADC1_ANALOG_CTRL_JD_DUMMY_mask                                        (0x00000C00)
#define EMMC_LSADC1_ANALOG_CTRL_JD_DUMMY(data)                                       (0x00000C00&((data)<<10))
#define EMMC_LSADC1_ANALOG_CTRL_JD_DUMMY_src(data)                                   ((0x00000C00&(data))>>10)
#define EMMC_LSADC1_ANALOG_CTRL_get_JD_DUMMY(data)                                   ((0x00000C00&(data))>>10)
#define EMMC_LSADC1_ANALOG_CTRL_JD_svr_shift                                         (8)
#define EMMC_LSADC1_ANALOG_CTRL_JD_svr_mask                                          (0x00000100)
#define EMMC_LSADC1_ANALOG_CTRL_JD_svr(data)                                         (0x00000100&((data)<<8))
#define EMMC_LSADC1_ANALOG_CTRL_JD_svr_src(data)                                     ((0x00000100&(data))>>8)
#define EMMC_LSADC1_ANALOG_CTRL_get_JD_svr(data)                                     ((0x00000100&(data))>>8)
#define EMMC_LSADC1_ANALOG_CTRL_JD_adcksel_shift                                     (4)
#define EMMC_LSADC1_ANALOG_CTRL_JD_adcksel_mask                                      (0x00000010)
#define EMMC_LSADC1_ANALOG_CTRL_JD_adcksel(data)                                     (0x00000010&((data)<<4))
#define EMMC_LSADC1_ANALOG_CTRL_JD_adcksel_src(data)                                 ((0x00000010&(data))>>4)
#define EMMC_LSADC1_ANALOG_CTRL_get_JD_adcksel(data)                                 ((0x00000010&(data))>>4)
#define EMMC_LSADC1_ANALOG_CTRL_JD_power_shift                                       (0)
#define EMMC_LSADC1_ANALOG_CTRL_JD_power_mask                                        (0x00000001)
#define EMMC_LSADC1_ANALOG_CTRL_JD_power(data)                                       (0x00000001&((data)<<0))
#define EMMC_LSADC1_ANALOG_CTRL_JD_power_src(data)                                   ((0x00000001&(data))>>0)
#define EMMC_LSADC1_ANALOG_CTRL_get_JD_power(data)                                   ((0x00000001&(data))>>0)


#define EMMC_LSADC1_PERI_TOP_DEBUG                                                   0x9801292C
#define EMMC_LSADC1_PERI_TOP_DEBUG_reg_addr                                          "0x9801292C"
#define EMMC_LSADC1_PERI_TOP_DEBUG_reg                                               0x9801292C
#define set_EMMC_LSADC1_PERI_TOP_DEBUG_reg(data)   (*((volatile unsigned int*) EMMC_LSADC1_PERI_TOP_DEBUG_reg)=data)
#define get_EMMC_LSADC1_PERI_TOP_DEBUG_reg   (*((volatile unsigned int*) EMMC_LSADC1_PERI_TOP_DEBUG_reg))
#define EMMC_LSADC1_PERI_TOP_DEBUG_inst_adr                                          "0x004B"
#define EMMC_LSADC1_PERI_TOP_DEBUG_inst                                              0x004B
#define EMMC_LSADC1_PERI_TOP_DEBUG_Lsadc_2_ifd_data_sel_shift                        (16)
#define EMMC_LSADC1_PERI_TOP_DEBUG_Lsadc_2_ifd_data_sel_mask                         (0x00070000)
#define EMMC_LSADC1_PERI_TOP_DEBUG_Lsadc_2_ifd_data_sel(data)                        (0x00070000&((data)<<16))
#define EMMC_LSADC1_PERI_TOP_DEBUG_Lsadc_2_ifd_data_sel_src(data)                    ((0x00070000&(data))>>16)
#define EMMC_LSADC1_PERI_TOP_DEBUG_get_Lsadc_2_ifd_data_sel(data)                    ((0x00070000&(data))>>16)
#define EMMC_LSADC1_PERI_TOP_DEBUG_Power_saving_enable_shift                         (14)
#define EMMC_LSADC1_PERI_TOP_DEBUG_Power_saving_enable_mask                          (0x00004000)
#define EMMC_LSADC1_PERI_TOP_DEBUG_Power_saving_enable(data)                         (0x00004000&((data)<<14))
#define EMMC_LSADC1_PERI_TOP_DEBUG_Power_saving_enable_src(data)                     ((0x00004000&(data))>>14)
#define EMMC_LSADC1_PERI_TOP_DEBUG_get_Power_saving_enable(data)                     ((0x00004000&(data))>>14)
#define EMMC_LSADC1_PERI_TOP_DEBUG_Power_saving_cycle_time_shift                     (11)
#define EMMC_LSADC1_PERI_TOP_DEBUG_Power_saving_cycle_time_mask                      (0x00003800)
#define EMMC_LSADC1_PERI_TOP_DEBUG_Power_saving_cycle_time(data)                     (0x00003800&((data)<<11))
#define EMMC_LSADC1_PERI_TOP_DEBUG_Power_saving_cycle_time_src(data)                 ((0x00003800&(data))>>11)
#define EMMC_LSADC1_PERI_TOP_DEBUG_get_Power_saving_cycle_time(data)                 ((0x00003800&(data))>>11)
#define EMMC_LSADC1_PERI_TOP_DEBUG_Power_saving_disable_time_shift                   (8)
#define EMMC_LSADC1_PERI_TOP_DEBUG_Power_saving_disable_time_mask                    (0x00000700)
#define EMMC_LSADC1_PERI_TOP_DEBUG_Power_saving_disable_time(data)                   (0x00000700&((data)<<8))
#define EMMC_LSADC1_PERI_TOP_DEBUG_Power_saving_disable_time_src(data)               ((0x00000700&(data))>>8)
#define EMMC_LSADC1_PERI_TOP_DEBUG_get_Power_saving_disable_time(data)               ((0x00000700&(data))>>8)
#define EMMC_LSADC1_PERI_TOP_DEBUG_peri_top_debug_shift                              (0)
#define EMMC_LSADC1_PERI_TOP_DEBUG_peri_top_debug_mask                               (0x000000FF)
#define EMMC_LSADC1_PERI_TOP_DEBUG_peri_top_debug(data)                              (0x000000FF&((data)<<0))
#define EMMC_LSADC1_PERI_TOP_DEBUG_peri_top_debug_src(data)                          ((0x000000FF&(data))>>0)
#define EMMC_LSADC1_PERI_TOP_DEBUG_get_peri_top_debug(data)                          ((0x000000FF&(data))>>0)


#define EMMC_LSADC1_PAD0_LEVEL_SET0                                                  0x98012930
#define EMMC_LSADC1_PAD0_LEVEL_SET0_reg_addr                                         "0x98012930"
#define EMMC_LSADC1_PAD0_LEVEL_SET0_reg                                              0x98012930
#define set_EMMC_LSADC1_PAD0_LEVEL_SET0_reg(data)   (*((volatile unsigned int*) EMMC_LSADC1_PAD0_LEVEL_SET0_reg)=data)
#define get_EMMC_LSADC1_PAD0_LEVEL_SET0_reg   (*((volatile unsigned int*) EMMC_LSADC1_PAD0_LEVEL_SET0_reg))
#define EMMC_LSADC1_PAD0_LEVEL_SET0_inst_adr                                         "0x004C"
#define EMMC_LSADC1_PAD0_LEVEL_SET0_inst                                             0x004C
#define EMMC_LSADC1_PAD0_LEVEL_SET0_Level_0_top_bound_shift                          (24)
#define EMMC_LSADC1_PAD0_LEVEL_SET0_Level_0_top_bound_mask                           (0xFF000000)
#define EMMC_LSADC1_PAD0_LEVEL_SET0_Level_0_top_bound(data)                          (0xFF000000&((data)<<24))
#define EMMC_LSADC1_PAD0_LEVEL_SET0_Level_0_top_bound_src(data)                      ((0xFF000000&(data))>>24)
#define EMMC_LSADC1_PAD0_LEVEL_SET0_get_Level_0_top_bound(data)                      ((0xFF000000&(data))>>24)
#define EMMC_LSADC1_PAD0_LEVEL_SET0_Level_0_low_bound_shift                          (16)
#define EMMC_LSADC1_PAD0_LEVEL_SET0_Level_0_low_bound_mask                           (0x00FF0000)
#define EMMC_LSADC1_PAD0_LEVEL_SET0_Level_0_low_bound(data)                          (0x00FF0000&((data)<<16))
#define EMMC_LSADC1_PAD0_LEVEL_SET0_Level_0_low_bound_src(data)                      ((0x00FF0000&(data))>>16)
#define EMMC_LSADC1_PAD0_LEVEL_SET0_get_Level_0_low_bound(data)                      ((0x00FF0000&(data))>>16)
#define EMMC_LSADC1_PAD0_LEVEL_SET0_Block0_en_shift                                  (15)
#define EMMC_LSADC1_PAD0_LEVEL_SET0_Block0_en_mask                                   (0x00008000)
#define EMMC_LSADC1_PAD0_LEVEL_SET0_Block0_en(data)                                  (0x00008000&((data)<<15))
#define EMMC_LSADC1_PAD0_LEVEL_SET0_Block0_en_src(data)                              ((0x00008000&(data))>>15)
#define EMMC_LSADC1_PAD0_LEVEL_SET0_get_Block0_en(data)                              ((0x00008000&(data))>>15)
#define EMMC_LSADC1_PAD0_LEVEL_SET0_INT_en0_shift                                    (1)
#define EMMC_LSADC1_PAD0_LEVEL_SET0_INT_en0_mask                                     (0x00000002)
#define EMMC_LSADC1_PAD0_LEVEL_SET0_INT_en0(data)                                    (0x00000002&((data)<<1))
#define EMMC_LSADC1_PAD0_LEVEL_SET0_INT_en0_src(data)                                ((0x00000002&(data))>>1)
#define EMMC_LSADC1_PAD0_LEVEL_SET0_get_INT_en0(data)                                ((0x00000002&(data))>>1)
#define EMMC_LSADC1_PAD0_LEVEL_SET0_INT_pending_bit0_shift                           (0)
#define EMMC_LSADC1_PAD0_LEVEL_SET0_INT_pending_bit0_mask                            (0x00000001)
#define EMMC_LSADC1_PAD0_LEVEL_SET0_INT_pending_bit0(data)                           (0x00000001&((data)<<0))
#define EMMC_LSADC1_PAD0_LEVEL_SET0_INT_pending_bit0_src(data)                       ((0x00000001&(data))>>0)
#define EMMC_LSADC1_PAD0_LEVEL_SET0_get_INT_pending_bit0(data)                       ((0x00000001&(data))>>0)


#define EMMC_LSADC1_PAD0_LEVEL_SET1                                                  0x98012934
#define EMMC_LSADC1_PAD0_LEVEL_SET1_reg_addr                                         "0x98012934"
#define EMMC_LSADC1_PAD0_LEVEL_SET1_reg                                              0x98012934
#define set_EMMC_LSADC1_PAD0_LEVEL_SET1_reg(data)   (*((volatile unsigned int*) EMMC_LSADC1_PAD0_LEVEL_SET1_reg)=data)
#define get_EMMC_LSADC1_PAD0_LEVEL_SET1_reg   (*((volatile unsigned int*) EMMC_LSADC1_PAD0_LEVEL_SET1_reg))
#define EMMC_LSADC1_PAD0_LEVEL_SET1_inst_adr                                         "0x004D"
#define EMMC_LSADC1_PAD0_LEVEL_SET1_inst                                             0x004D
#define EMMC_LSADC1_PAD0_LEVEL_SET1_Level_1_top_bound_shift                          (24)
#define EMMC_LSADC1_PAD0_LEVEL_SET1_Level_1_top_bound_mask                           (0xFF000000)
#define EMMC_LSADC1_PAD0_LEVEL_SET1_Level_1_top_bound(data)                          (0xFF000000&((data)<<24))
#define EMMC_LSADC1_PAD0_LEVEL_SET1_Level_1_top_bound_src(data)                      ((0xFF000000&(data))>>24)
#define EMMC_LSADC1_PAD0_LEVEL_SET1_get_Level_1_top_bound(data)                      ((0xFF000000&(data))>>24)
#define EMMC_LSADC1_PAD0_LEVEL_SET1_Level_0_low_bound_shift                          (16)
#define EMMC_LSADC1_PAD0_LEVEL_SET1_Level_0_low_bound_mask                           (0x00FF0000)
#define EMMC_LSADC1_PAD0_LEVEL_SET1_Level_0_low_bound(data)                          (0x00FF0000&((data)<<16))
#define EMMC_LSADC1_PAD0_LEVEL_SET1_Level_0_low_bound_src(data)                      ((0x00FF0000&(data))>>16)
#define EMMC_LSADC1_PAD0_LEVEL_SET1_get_Level_0_low_bound(data)                      ((0x00FF0000&(data))>>16)
#define EMMC_LSADC1_PAD0_LEVEL_SET1_Block1_en_shift                                  (15)
#define EMMC_LSADC1_PAD0_LEVEL_SET1_Block1_en_mask                                   (0x00008000)
#define EMMC_LSADC1_PAD0_LEVEL_SET1_Block1_en(data)                                  (0x00008000&((data)<<15))
#define EMMC_LSADC1_PAD0_LEVEL_SET1_Block1_en_src(data)                              ((0x00008000&(data))>>15)
#define EMMC_LSADC1_PAD0_LEVEL_SET1_get_Block1_en(data)                              ((0x00008000&(data))>>15)
#define EMMC_LSADC1_PAD0_LEVEL_SET1_INT_en1_shift                                    (1)
#define EMMC_LSADC1_PAD0_LEVEL_SET1_INT_en1_mask                                     (0x00000002)
#define EMMC_LSADC1_PAD0_LEVEL_SET1_INT_en1(data)                                    (0x00000002&((data)<<1))
#define EMMC_LSADC1_PAD0_LEVEL_SET1_INT_en1_src(data)                                ((0x00000002&(data))>>1)
#define EMMC_LSADC1_PAD0_LEVEL_SET1_get_INT_en1(data)                                ((0x00000002&(data))>>1)
#define EMMC_LSADC1_PAD0_LEVEL_SET1_INT_pending_bit1_shift                           (0)
#define EMMC_LSADC1_PAD0_LEVEL_SET1_INT_pending_bit1_mask                            (0x00000001)
#define EMMC_LSADC1_PAD0_LEVEL_SET1_INT_pending_bit1(data)                           (0x00000001&((data)<<0))
#define EMMC_LSADC1_PAD0_LEVEL_SET1_INT_pending_bit1_src(data)                       ((0x00000001&(data))>>0)
#define EMMC_LSADC1_PAD0_LEVEL_SET1_get_INT_pending_bit1(data)                       ((0x00000001&(data))>>0)


#define EMMC_LSADC1_PAD0_LEVEL_SET2                                                  0x98012938
#define EMMC_LSADC1_PAD0_LEVEL_SET2_reg_addr                                         "0x98012938"
#define EMMC_LSADC1_PAD0_LEVEL_SET2_reg                                              0x98012938
#define set_EMMC_LSADC1_PAD0_LEVEL_SET2_reg(data)   (*((volatile unsigned int*) EMMC_LSADC1_PAD0_LEVEL_SET2_reg)=data)
#define get_EMMC_LSADC1_PAD0_LEVEL_SET2_reg   (*((volatile unsigned int*) EMMC_LSADC1_PAD0_LEVEL_SET2_reg))
#define EMMC_LSADC1_PAD0_LEVEL_SET2_inst_adr                                         "0x004E"
#define EMMC_LSADC1_PAD0_LEVEL_SET2_inst                                             0x004E
#define EMMC_LSADC1_PAD0_LEVEL_SET2_Level_2_top_bound_shift                          (24)
#define EMMC_LSADC1_PAD0_LEVEL_SET2_Level_2_top_bound_mask                           (0xFF000000)
#define EMMC_LSADC1_PAD0_LEVEL_SET2_Level_2_top_bound(data)                          (0xFF000000&((data)<<24))
#define EMMC_LSADC1_PAD0_LEVEL_SET2_Level_2_top_bound_src(data)                      ((0xFF000000&(data))>>24)
#define EMMC_LSADC1_PAD0_LEVEL_SET2_get_Level_2_top_bound(data)                      ((0xFF000000&(data))>>24)
#define EMMC_LSADC1_PAD0_LEVEL_SET2_Level_2_low_bound_shift                          (16)
#define EMMC_LSADC1_PAD0_LEVEL_SET2_Level_2_low_bound_mask                           (0x00FF0000)
#define EMMC_LSADC1_PAD0_LEVEL_SET2_Level_2_low_bound(data)                          (0x00FF0000&((data)<<16))
#define EMMC_LSADC1_PAD0_LEVEL_SET2_Level_2_low_bound_src(data)                      ((0x00FF0000&(data))>>16)
#define EMMC_LSADC1_PAD0_LEVEL_SET2_get_Level_2_low_bound(data)                      ((0x00FF0000&(data))>>16)
#define EMMC_LSADC1_PAD0_LEVEL_SET2_Block2_en_shift                                  (15)
#define EMMC_LSADC1_PAD0_LEVEL_SET2_Block2_en_mask                                   (0x00008000)
#define EMMC_LSADC1_PAD0_LEVEL_SET2_Block2_en(data)                                  (0x00008000&((data)<<15))
#define EMMC_LSADC1_PAD0_LEVEL_SET2_Block2_en_src(data)                              ((0x00008000&(data))>>15)
#define EMMC_LSADC1_PAD0_LEVEL_SET2_get_Block2_en(data)                              ((0x00008000&(data))>>15)
#define EMMC_LSADC1_PAD0_LEVEL_SET2_INT_en2_shift                                    (1)
#define EMMC_LSADC1_PAD0_LEVEL_SET2_INT_en2_mask                                     (0x00000002)
#define EMMC_LSADC1_PAD0_LEVEL_SET2_INT_en2(data)                                    (0x00000002&((data)<<1))
#define EMMC_LSADC1_PAD0_LEVEL_SET2_INT_en2_src(data)                                ((0x00000002&(data))>>1)
#define EMMC_LSADC1_PAD0_LEVEL_SET2_get_INT_en2(data)                                ((0x00000002&(data))>>1)
#define EMMC_LSADC1_PAD0_LEVEL_SET2_INT_pending_bit2_shift                           (0)
#define EMMC_LSADC1_PAD0_LEVEL_SET2_INT_pending_bit2_mask                            (0x00000001)
#define EMMC_LSADC1_PAD0_LEVEL_SET2_INT_pending_bit2(data)                           (0x00000001&((data)<<0))
#define EMMC_LSADC1_PAD0_LEVEL_SET2_INT_pending_bit2_src(data)                       ((0x00000001&(data))>>0)
#define EMMC_LSADC1_PAD0_LEVEL_SET2_get_INT_pending_bit2(data)                       ((0x00000001&(data))>>0)


#define EMMC_LSADC1_PAD0_LEVEL_SET3                                                  0x9801293C
#define EMMC_LSADC1_PAD0_LEVEL_SET3_reg_addr                                         "0x9801293C"
#define EMMC_LSADC1_PAD0_LEVEL_SET3_reg                                              0x9801293C
#define set_EMMC_LSADC1_PAD0_LEVEL_SET3_reg(data)   (*((volatile unsigned int*) EMMC_LSADC1_PAD0_LEVEL_SET3_reg)=data)
#define get_EMMC_LSADC1_PAD0_LEVEL_SET3_reg   (*((volatile unsigned int*) EMMC_LSADC1_PAD0_LEVEL_SET3_reg))
#define EMMC_LSADC1_PAD0_LEVEL_SET3_inst_adr                                         "0x004F"
#define EMMC_LSADC1_PAD0_LEVEL_SET3_inst                                             0x004F
#define EMMC_LSADC1_PAD0_LEVEL_SET3_Level_3_top_bound_shift                          (24)
#define EMMC_LSADC1_PAD0_LEVEL_SET3_Level_3_top_bound_mask                           (0xFF000000)
#define EMMC_LSADC1_PAD0_LEVEL_SET3_Level_3_top_bound(data)                          (0xFF000000&((data)<<24))
#define EMMC_LSADC1_PAD0_LEVEL_SET3_Level_3_top_bound_src(data)                      ((0xFF000000&(data))>>24)
#define EMMC_LSADC1_PAD0_LEVEL_SET3_get_Level_3_top_bound(data)                      ((0xFF000000&(data))>>24)
#define EMMC_LSADC1_PAD0_LEVEL_SET3_Level_3_low_bound_shift                          (16)
#define EMMC_LSADC1_PAD0_LEVEL_SET3_Level_3_low_bound_mask                           (0x00FF0000)
#define EMMC_LSADC1_PAD0_LEVEL_SET3_Level_3_low_bound(data)                          (0x00FF0000&((data)<<16))
#define EMMC_LSADC1_PAD0_LEVEL_SET3_Level_3_low_bound_src(data)                      ((0x00FF0000&(data))>>16)
#define EMMC_LSADC1_PAD0_LEVEL_SET3_get_Level_3_low_bound(data)                      ((0x00FF0000&(data))>>16)
#define EMMC_LSADC1_PAD0_LEVEL_SET3_Block3_en_shift                                  (15)
#define EMMC_LSADC1_PAD0_LEVEL_SET3_Block3_en_mask                                   (0x00008000)
#define EMMC_LSADC1_PAD0_LEVEL_SET3_Block3_en(data)                                  (0x00008000&((data)<<15))
#define EMMC_LSADC1_PAD0_LEVEL_SET3_Block3_en_src(data)                              ((0x00008000&(data))>>15)
#define EMMC_LSADC1_PAD0_LEVEL_SET3_get_Block3_en(data)                              ((0x00008000&(data))>>15)
#define EMMC_LSADC1_PAD0_LEVEL_SET3_INT_en3_shift                                    (1)
#define EMMC_LSADC1_PAD0_LEVEL_SET3_INT_en3_mask                                     (0x00000002)
#define EMMC_LSADC1_PAD0_LEVEL_SET3_INT_en3(data)                                    (0x00000002&((data)<<1))
#define EMMC_LSADC1_PAD0_LEVEL_SET3_INT_en3_src(data)                                ((0x00000002&(data))>>1)
#define EMMC_LSADC1_PAD0_LEVEL_SET3_get_INT_en3(data)                                ((0x00000002&(data))>>1)
#define EMMC_LSADC1_PAD0_LEVEL_SET3_INT_pending_bit3_shift                           (0)
#define EMMC_LSADC1_PAD0_LEVEL_SET3_INT_pending_bit3_mask                            (0x00000001)
#define EMMC_LSADC1_PAD0_LEVEL_SET3_INT_pending_bit3(data)                           (0x00000001&((data)<<0))
#define EMMC_LSADC1_PAD0_LEVEL_SET3_INT_pending_bit3_src(data)                       ((0x00000001&(data))>>0)
#define EMMC_LSADC1_PAD0_LEVEL_SET3_get_INT_pending_bit3(data)                       ((0x00000001&(data))>>0)


#define EMMC_LSADC1_PAD0_LEVEL_SET4                                                  0x98012940
#define EMMC_LSADC1_PAD0_LEVEL_SET4_reg_addr                                         "0x98012940"
#define EMMC_LSADC1_PAD0_LEVEL_SET4_reg                                              0x98012940
#define set_EMMC_LSADC1_PAD0_LEVEL_SET4_reg(data)   (*((volatile unsigned int*) EMMC_LSADC1_PAD0_LEVEL_SET4_reg)=data)
#define get_EMMC_LSADC1_PAD0_LEVEL_SET4_reg   (*((volatile unsigned int*) EMMC_LSADC1_PAD0_LEVEL_SET4_reg))
#define EMMC_LSADC1_PAD0_LEVEL_SET4_inst_adr                                         "0x0050"
#define EMMC_LSADC1_PAD0_LEVEL_SET4_inst                                             0x0050
#define EMMC_LSADC1_PAD0_LEVEL_SET4_Level_4_top_bound_shift                          (24)
#define EMMC_LSADC1_PAD0_LEVEL_SET4_Level_4_top_bound_mask                           (0xFF000000)
#define EMMC_LSADC1_PAD0_LEVEL_SET4_Level_4_top_bound(data)                          (0xFF000000&((data)<<24))
#define EMMC_LSADC1_PAD0_LEVEL_SET4_Level_4_top_bound_src(data)                      ((0xFF000000&(data))>>24)
#define EMMC_LSADC1_PAD0_LEVEL_SET4_get_Level_4_top_bound(data)                      ((0xFF000000&(data))>>24)
#define EMMC_LSADC1_PAD0_LEVEL_SET4_Level_4_low_bound_shift                          (16)
#define EMMC_LSADC1_PAD0_LEVEL_SET4_Level_4_low_bound_mask                           (0x00FF0000)
#define EMMC_LSADC1_PAD0_LEVEL_SET4_Level_4_low_bound(data)                          (0x00FF0000&((data)<<16))
#define EMMC_LSADC1_PAD0_LEVEL_SET4_Level_4_low_bound_src(data)                      ((0x00FF0000&(data))>>16)
#define EMMC_LSADC1_PAD0_LEVEL_SET4_get_Level_4_low_bound(data)                      ((0x00FF0000&(data))>>16)
#define EMMC_LSADC1_PAD0_LEVEL_SET4_Block4_en_shift                                  (15)
#define EMMC_LSADC1_PAD0_LEVEL_SET4_Block4_en_mask                                   (0x00008000)
#define EMMC_LSADC1_PAD0_LEVEL_SET4_Block4_en(data)                                  (0x00008000&((data)<<15))
#define EMMC_LSADC1_PAD0_LEVEL_SET4_Block4_en_src(data)                              ((0x00008000&(data))>>15)
#define EMMC_LSADC1_PAD0_LEVEL_SET4_get_Block4_en(data)                              ((0x00008000&(data))>>15)
#define EMMC_LSADC1_PAD0_LEVEL_SET4_INT_en4_shift                                    (1)
#define EMMC_LSADC1_PAD0_LEVEL_SET4_INT_en4_mask                                     (0x00000002)
#define EMMC_LSADC1_PAD0_LEVEL_SET4_INT_en4(data)                                    (0x00000002&((data)<<1))
#define EMMC_LSADC1_PAD0_LEVEL_SET4_INT_en4_src(data)                                ((0x00000002&(data))>>1)
#define EMMC_LSADC1_PAD0_LEVEL_SET4_get_INT_en4(data)                                ((0x00000002&(data))>>1)
#define EMMC_LSADC1_PAD0_LEVEL_SET4_INT_pending_bit4_shift                           (0)
#define EMMC_LSADC1_PAD0_LEVEL_SET4_INT_pending_bit4_mask                            (0x00000001)
#define EMMC_LSADC1_PAD0_LEVEL_SET4_INT_pending_bit4(data)                           (0x00000001&((data)<<0))
#define EMMC_LSADC1_PAD0_LEVEL_SET4_INT_pending_bit4_src(data)                       ((0x00000001&(data))>>0)
#define EMMC_LSADC1_PAD0_LEVEL_SET4_get_INT_pending_bit4(data)                       ((0x00000001&(data))>>0)


#define EMMC_LSADC1_PAD0_LEVEL_SET5                                                  0x98012944
#define EMMC_LSADC1_PAD0_LEVEL_SET5_reg_addr                                         "0x98012944"
#define EMMC_LSADC1_PAD0_LEVEL_SET5_reg                                              0x98012944
#define set_EMMC_LSADC1_PAD0_LEVEL_SET5_reg(data)   (*((volatile unsigned int*) EMMC_LSADC1_PAD0_LEVEL_SET5_reg)=data)
#define get_EMMC_LSADC1_PAD0_LEVEL_SET5_reg   (*((volatile unsigned int*) EMMC_LSADC1_PAD0_LEVEL_SET5_reg))
#define EMMC_LSADC1_PAD0_LEVEL_SET5_inst_adr                                         "0x0051"
#define EMMC_LSADC1_PAD0_LEVEL_SET5_inst                                             0x0051
#define EMMC_LSADC1_PAD0_LEVEL_SET5_Level_5_top_bound_shift                          (24)
#define EMMC_LSADC1_PAD0_LEVEL_SET5_Level_5_top_bound_mask                           (0xFF000000)
#define EMMC_LSADC1_PAD0_LEVEL_SET5_Level_5_top_bound(data)                          (0xFF000000&((data)<<24))
#define EMMC_LSADC1_PAD0_LEVEL_SET5_Level_5_top_bound_src(data)                      ((0xFF000000&(data))>>24)
#define EMMC_LSADC1_PAD0_LEVEL_SET5_get_Level_5_top_bound(data)                      ((0xFF000000&(data))>>24)
#define EMMC_LSADC1_PAD0_LEVEL_SET5_Level_5_low_bound_shift                          (16)
#define EMMC_LSADC1_PAD0_LEVEL_SET5_Level_5_low_bound_mask                           (0x00FF0000)
#define EMMC_LSADC1_PAD0_LEVEL_SET5_Level_5_low_bound(data)                          (0x00FF0000&((data)<<16))
#define EMMC_LSADC1_PAD0_LEVEL_SET5_Level_5_low_bound_src(data)                      ((0x00FF0000&(data))>>16)
#define EMMC_LSADC1_PAD0_LEVEL_SET5_get_Level_5_low_bound(data)                      ((0x00FF0000&(data))>>16)
#define EMMC_LSADC1_PAD0_LEVEL_SET5_Block5_en_shift                                  (15)
#define EMMC_LSADC1_PAD0_LEVEL_SET5_Block5_en_mask                                   (0x00008000)
#define EMMC_LSADC1_PAD0_LEVEL_SET5_Block5_en(data)                                  (0x00008000&((data)<<15))
#define EMMC_LSADC1_PAD0_LEVEL_SET5_Block5_en_src(data)                              ((0x00008000&(data))>>15)
#define EMMC_LSADC1_PAD0_LEVEL_SET5_get_Block5_en(data)                              ((0x00008000&(data))>>15)
#define EMMC_LSADC1_PAD0_LEVEL_SET5_INT_en5_shift                                    (1)
#define EMMC_LSADC1_PAD0_LEVEL_SET5_INT_en5_mask                                     (0x00000002)
#define EMMC_LSADC1_PAD0_LEVEL_SET5_INT_en5(data)                                    (0x00000002&((data)<<1))
#define EMMC_LSADC1_PAD0_LEVEL_SET5_INT_en5_src(data)                                ((0x00000002&(data))>>1)
#define EMMC_LSADC1_PAD0_LEVEL_SET5_get_INT_en5(data)                                ((0x00000002&(data))>>1)
#define EMMC_LSADC1_PAD0_LEVEL_SET5_INT_pending_bit5_shift                           (0)
#define EMMC_LSADC1_PAD0_LEVEL_SET5_INT_pending_bit5_mask                            (0x00000001)
#define EMMC_LSADC1_PAD0_LEVEL_SET5_INT_pending_bit5(data)                           (0x00000001&((data)<<0))
#define EMMC_LSADC1_PAD0_LEVEL_SET5_INT_pending_bit5_src(data)                       ((0x00000001&(data))>>0)
#define EMMC_LSADC1_PAD0_LEVEL_SET5_get_INT_pending_bit5(data)                       ((0x00000001&(data))>>0)


#define EMMC_LSADC1_PAD1_LEVEL_SET0                                                  0x98012948
#define EMMC_LSADC1_PAD1_LEVEL_SET0_reg_addr                                         "0x98012948"
#define EMMC_LSADC1_PAD1_LEVEL_SET0_reg                                              0x98012948
#define set_EMMC_LSADC1_PAD1_LEVEL_SET0_reg(data)   (*((volatile unsigned int*) EMMC_LSADC1_PAD1_LEVEL_SET0_reg)=data)
#define get_EMMC_LSADC1_PAD1_LEVEL_SET0_reg   (*((volatile unsigned int*) EMMC_LSADC1_PAD1_LEVEL_SET0_reg))
#define EMMC_LSADC1_PAD1_LEVEL_SET0_inst_adr                                         "0x0052"
#define EMMC_LSADC1_PAD1_LEVEL_SET0_inst                                             0x0052
#define EMMC_LSADC1_PAD1_LEVEL_SET0_Level_0_top_bound_shift                          (24)
#define EMMC_LSADC1_PAD1_LEVEL_SET0_Level_0_top_bound_mask                           (0xFF000000)
#define EMMC_LSADC1_PAD1_LEVEL_SET0_Level_0_top_bound(data)                          (0xFF000000&((data)<<24))
#define EMMC_LSADC1_PAD1_LEVEL_SET0_Level_0_top_bound_src(data)                      ((0xFF000000&(data))>>24)
#define EMMC_LSADC1_PAD1_LEVEL_SET0_get_Level_0_top_bound(data)                      ((0xFF000000&(data))>>24)
#define EMMC_LSADC1_PAD1_LEVEL_SET0_Level_0_low_bound_shift                          (16)
#define EMMC_LSADC1_PAD1_LEVEL_SET0_Level_0_low_bound_mask                           (0x00FF0000)
#define EMMC_LSADC1_PAD1_LEVEL_SET0_Level_0_low_bound(data)                          (0x00FF0000&((data)<<16))
#define EMMC_LSADC1_PAD1_LEVEL_SET0_Level_0_low_bound_src(data)                      ((0x00FF0000&(data))>>16)
#define EMMC_LSADC1_PAD1_LEVEL_SET0_get_Level_0_low_bound(data)                      ((0x00FF0000&(data))>>16)
#define EMMC_LSADC1_PAD1_LEVEL_SET0_Block0_en_shift                                  (15)
#define EMMC_LSADC1_PAD1_LEVEL_SET0_Block0_en_mask                                   (0x00008000)
#define EMMC_LSADC1_PAD1_LEVEL_SET0_Block0_en(data)                                  (0x00008000&((data)<<15))
#define EMMC_LSADC1_PAD1_LEVEL_SET0_Block0_en_src(data)                              ((0x00008000&(data))>>15)
#define EMMC_LSADC1_PAD1_LEVEL_SET0_get_Block0_en(data)                              ((0x00008000&(data))>>15)
#define EMMC_LSADC1_PAD1_LEVEL_SET0_INT_en0_shift                                    (1)
#define EMMC_LSADC1_PAD1_LEVEL_SET0_INT_en0_mask                                     (0x00000002)
#define EMMC_LSADC1_PAD1_LEVEL_SET0_INT_en0(data)                                    (0x00000002&((data)<<1))
#define EMMC_LSADC1_PAD1_LEVEL_SET0_INT_en0_src(data)                                ((0x00000002&(data))>>1)
#define EMMC_LSADC1_PAD1_LEVEL_SET0_get_INT_en0(data)                                ((0x00000002&(data))>>1)
#define EMMC_LSADC1_PAD1_LEVEL_SET0_INT_pending_bit0_shift                           (0)
#define EMMC_LSADC1_PAD1_LEVEL_SET0_INT_pending_bit0_mask                            (0x00000001)
#define EMMC_LSADC1_PAD1_LEVEL_SET0_INT_pending_bit0(data)                           (0x00000001&((data)<<0))
#define EMMC_LSADC1_PAD1_LEVEL_SET0_INT_pending_bit0_src(data)                       ((0x00000001&(data))>>0)
#define EMMC_LSADC1_PAD1_LEVEL_SET0_get_INT_pending_bit0(data)                       ((0x00000001&(data))>>0)


#define EMMC_LSADC1_PAD1_LEVEL_SET1                                                  0x9801294C
#define EMMC_LSADC1_PAD1_LEVEL_SET1_reg_addr                                         "0x9801294C"
#define EMMC_LSADC1_PAD1_LEVEL_SET1_reg                                              0x9801294C
#define set_EMMC_LSADC1_PAD1_LEVEL_SET1_reg(data)   (*((volatile unsigned int*) EMMC_LSADC1_PAD1_LEVEL_SET1_reg)=data)
#define get_EMMC_LSADC1_PAD1_LEVEL_SET1_reg   (*((volatile unsigned int*) EMMC_LSADC1_PAD1_LEVEL_SET1_reg))
#define EMMC_LSADC1_PAD1_LEVEL_SET1_inst_adr                                         "0x0053"
#define EMMC_LSADC1_PAD1_LEVEL_SET1_inst                                             0x0053
#define EMMC_LSADC1_PAD1_LEVEL_SET1_Level_1_top_bound_shift                          (24)
#define EMMC_LSADC1_PAD1_LEVEL_SET1_Level_1_top_bound_mask                           (0xFF000000)
#define EMMC_LSADC1_PAD1_LEVEL_SET1_Level_1_top_bound(data)                          (0xFF000000&((data)<<24))
#define EMMC_LSADC1_PAD1_LEVEL_SET1_Level_1_top_bound_src(data)                      ((0xFF000000&(data))>>24)
#define EMMC_LSADC1_PAD1_LEVEL_SET1_get_Level_1_top_bound(data)                      ((0xFF000000&(data))>>24)
#define EMMC_LSADC1_PAD1_LEVEL_SET1_Level_0_low_bound_shift                          (16)
#define EMMC_LSADC1_PAD1_LEVEL_SET1_Level_0_low_bound_mask                           (0x00FF0000)
#define EMMC_LSADC1_PAD1_LEVEL_SET1_Level_0_low_bound(data)                          (0x00FF0000&((data)<<16))
#define EMMC_LSADC1_PAD1_LEVEL_SET1_Level_0_low_bound_src(data)                      ((0x00FF0000&(data))>>16)
#define EMMC_LSADC1_PAD1_LEVEL_SET1_get_Level_0_low_bound(data)                      ((0x00FF0000&(data))>>16)
#define EMMC_LSADC1_PAD1_LEVEL_SET1_Block1_en_shift                                  (15)
#define EMMC_LSADC1_PAD1_LEVEL_SET1_Block1_en_mask                                   (0x00008000)
#define EMMC_LSADC1_PAD1_LEVEL_SET1_Block1_en(data)                                  (0x00008000&((data)<<15))
#define EMMC_LSADC1_PAD1_LEVEL_SET1_Block1_en_src(data)                              ((0x00008000&(data))>>15)
#define EMMC_LSADC1_PAD1_LEVEL_SET1_get_Block1_en(data)                              ((0x00008000&(data))>>15)
#define EMMC_LSADC1_PAD1_LEVEL_SET1_INT_en1_shift                                    (1)
#define EMMC_LSADC1_PAD1_LEVEL_SET1_INT_en1_mask                                     (0x00000002)
#define EMMC_LSADC1_PAD1_LEVEL_SET1_INT_en1(data)                                    (0x00000002&((data)<<1))
#define EMMC_LSADC1_PAD1_LEVEL_SET1_INT_en1_src(data)                                ((0x00000002&(data))>>1)
#define EMMC_LSADC1_PAD1_LEVEL_SET1_get_INT_en1(data)                                ((0x00000002&(data))>>1)
#define EMMC_LSADC1_PAD1_LEVEL_SET1_INT_pending_bit1_shift                           (0)
#define EMMC_LSADC1_PAD1_LEVEL_SET1_INT_pending_bit1_mask                            (0x00000001)
#define EMMC_LSADC1_PAD1_LEVEL_SET1_INT_pending_bit1(data)                           (0x00000001&((data)<<0))
#define EMMC_LSADC1_PAD1_LEVEL_SET1_INT_pending_bit1_src(data)                       ((0x00000001&(data))>>0)
#define EMMC_LSADC1_PAD1_LEVEL_SET1_get_INT_pending_bit1(data)                       ((0x00000001&(data))>>0)


#define EMMC_LSADC1_PAD1_LEVEL_SET2                                                  0x98012950
#define EMMC_LSADC1_PAD1_LEVEL_SET2_reg_addr                                         "0x98012950"
#define EMMC_LSADC1_PAD1_LEVEL_SET2_reg                                              0x98012950
#define set_EMMC_LSADC1_PAD1_LEVEL_SET2_reg(data)   (*((volatile unsigned int*) EMMC_LSADC1_PAD1_LEVEL_SET2_reg)=data)
#define get_EMMC_LSADC1_PAD1_LEVEL_SET2_reg   (*((volatile unsigned int*) EMMC_LSADC1_PAD1_LEVEL_SET2_reg))
#define EMMC_LSADC1_PAD1_LEVEL_SET2_inst_adr                                         "0x0054"
#define EMMC_LSADC1_PAD1_LEVEL_SET2_inst                                             0x0054
#define EMMC_LSADC1_PAD1_LEVEL_SET2_Level_2_top_bound_shift                          (24)
#define EMMC_LSADC1_PAD1_LEVEL_SET2_Level_2_top_bound_mask                           (0xFF000000)
#define EMMC_LSADC1_PAD1_LEVEL_SET2_Level_2_top_bound(data)                          (0xFF000000&((data)<<24))
#define EMMC_LSADC1_PAD1_LEVEL_SET2_Level_2_top_bound_src(data)                      ((0xFF000000&(data))>>24)
#define EMMC_LSADC1_PAD1_LEVEL_SET2_get_Level_2_top_bound(data)                      ((0xFF000000&(data))>>24)
#define EMMC_LSADC1_PAD1_LEVEL_SET2_Level_2_low_bound_shift                          (16)
#define EMMC_LSADC1_PAD1_LEVEL_SET2_Level_2_low_bound_mask                           (0x00FF0000)
#define EMMC_LSADC1_PAD1_LEVEL_SET2_Level_2_low_bound(data)                          (0x00FF0000&((data)<<16))
#define EMMC_LSADC1_PAD1_LEVEL_SET2_Level_2_low_bound_src(data)                      ((0x00FF0000&(data))>>16)
#define EMMC_LSADC1_PAD1_LEVEL_SET2_get_Level_2_low_bound(data)                      ((0x00FF0000&(data))>>16)
#define EMMC_LSADC1_PAD1_LEVEL_SET2_Block2_en_shift                                  (15)
#define EMMC_LSADC1_PAD1_LEVEL_SET2_Block2_en_mask                                   (0x00008000)
#define EMMC_LSADC1_PAD1_LEVEL_SET2_Block2_en(data)                                  (0x00008000&((data)<<15))
#define EMMC_LSADC1_PAD1_LEVEL_SET2_Block2_en_src(data)                              ((0x00008000&(data))>>15)
#define EMMC_LSADC1_PAD1_LEVEL_SET2_get_Block2_en(data)                              ((0x00008000&(data))>>15)
#define EMMC_LSADC1_PAD1_LEVEL_SET2_INT_en2_shift                                    (1)
#define EMMC_LSADC1_PAD1_LEVEL_SET2_INT_en2_mask                                     (0x00000002)
#define EMMC_LSADC1_PAD1_LEVEL_SET2_INT_en2(data)                                    (0x00000002&((data)<<1))
#define EMMC_LSADC1_PAD1_LEVEL_SET2_INT_en2_src(data)                                ((0x00000002&(data))>>1)
#define EMMC_LSADC1_PAD1_LEVEL_SET2_get_INT_en2(data)                                ((0x00000002&(data))>>1)
#define EMMC_LSADC1_PAD1_LEVEL_SET2_INT_pending_bit2_shift                           (0)
#define EMMC_LSADC1_PAD1_LEVEL_SET2_INT_pending_bit2_mask                            (0x00000001)
#define EMMC_LSADC1_PAD1_LEVEL_SET2_INT_pending_bit2(data)                           (0x00000001&((data)<<0))
#define EMMC_LSADC1_PAD1_LEVEL_SET2_INT_pending_bit2_src(data)                       ((0x00000001&(data))>>0)
#define EMMC_LSADC1_PAD1_LEVEL_SET2_get_INT_pending_bit2(data)                       ((0x00000001&(data))>>0)


#define EMMC_LSADC1_PAD1_LEVEL_SET3                                                  0x98012954
#define EMMC_LSADC1_PAD1_LEVEL_SET3_reg_addr                                         "0x98012954"
#define EMMC_LSADC1_PAD1_LEVEL_SET3_reg                                              0x98012954
#define set_EMMC_LSADC1_PAD1_LEVEL_SET3_reg(data)   (*((volatile unsigned int*) EMMC_LSADC1_PAD1_LEVEL_SET3_reg)=data)
#define get_EMMC_LSADC1_PAD1_LEVEL_SET3_reg   (*((volatile unsigned int*) EMMC_LSADC1_PAD1_LEVEL_SET3_reg))
#define EMMC_LSADC1_PAD1_LEVEL_SET3_inst_adr                                         "0x0055"
#define EMMC_LSADC1_PAD1_LEVEL_SET3_inst                                             0x0055
#define EMMC_LSADC1_PAD1_LEVEL_SET3_Level_3_top_bound_shift                          (24)
#define EMMC_LSADC1_PAD1_LEVEL_SET3_Level_3_top_bound_mask                           (0xFF000000)
#define EMMC_LSADC1_PAD1_LEVEL_SET3_Level_3_top_bound(data)                          (0xFF000000&((data)<<24))
#define EMMC_LSADC1_PAD1_LEVEL_SET3_Level_3_top_bound_src(data)                      ((0xFF000000&(data))>>24)
#define EMMC_LSADC1_PAD1_LEVEL_SET3_get_Level_3_top_bound(data)                      ((0xFF000000&(data))>>24)
#define EMMC_LSADC1_PAD1_LEVEL_SET3_Level_3_low_bound_shift                          (16)
#define EMMC_LSADC1_PAD1_LEVEL_SET3_Level_3_low_bound_mask                           (0x00FF0000)
#define EMMC_LSADC1_PAD1_LEVEL_SET3_Level_3_low_bound(data)                          (0x00FF0000&((data)<<16))
#define EMMC_LSADC1_PAD1_LEVEL_SET3_Level_3_low_bound_src(data)                      ((0x00FF0000&(data))>>16)
#define EMMC_LSADC1_PAD1_LEVEL_SET3_get_Level_3_low_bound(data)                      ((0x00FF0000&(data))>>16)
#define EMMC_LSADC1_PAD1_LEVEL_SET3_Block3_en_shift                                  (15)
#define EMMC_LSADC1_PAD1_LEVEL_SET3_Block3_en_mask                                   (0x00008000)
#define EMMC_LSADC1_PAD1_LEVEL_SET3_Block3_en(data)                                  (0x00008000&((data)<<15))
#define EMMC_LSADC1_PAD1_LEVEL_SET3_Block3_en_src(data)                              ((0x00008000&(data))>>15)
#define EMMC_LSADC1_PAD1_LEVEL_SET3_get_Block3_en(data)                              ((0x00008000&(data))>>15)
#define EMMC_LSADC1_PAD1_LEVEL_SET3_INT_en3_shift                                    (1)
#define EMMC_LSADC1_PAD1_LEVEL_SET3_INT_en3_mask                                     (0x00000002)
#define EMMC_LSADC1_PAD1_LEVEL_SET3_INT_en3(data)                                    (0x00000002&((data)<<1))
#define EMMC_LSADC1_PAD1_LEVEL_SET3_INT_en3_src(data)                                ((0x00000002&(data))>>1)
#define EMMC_LSADC1_PAD1_LEVEL_SET3_get_INT_en3(data)                                ((0x00000002&(data))>>1)
#define EMMC_LSADC1_PAD1_LEVEL_SET3_INT_pending_bit3_shift                           (0)
#define EMMC_LSADC1_PAD1_LEVEL_SET3_INT_pending_bit3_mask                            (0x00000001)
#define EMMC_LSADC1_PAD1_LEVEL_SET3_INT_pending_bit3(data)                           (0x00000001&((data)<<0))
#define EMMC_LSADC1_PAD1_LEVEL_SET3_INT_pending_bit3_src(data)                       ((0x00000001&(data))>>0)
#define EMMC_LSADC1_PAD1_LEVEL_SET3_get_INT_pending_bit3(data)                       ((0x00000001&(data))>>0)


#define EMMC_LSADC1_PAD1_LEVEL_SET4                                                  0x98012958
#define EMMC_LSADC1_PAD1_LEVEL_SET4_reg_addr                                         "0x98012958"
#define EMMC_LSADC1_PAD1_LEVEL_SET4_reg                                              0x98012958
#define set_EMMC_LSADC1_PAD1_LEVEL_SET4_reg(data)   (*((volatile unsigned int*) EMMC_LSADC1_PAD1_LEVEL_SET4_reg)=data)
#define get_EMMC_LSADC1_PAD1_LEVEL_SET4_reg   (*((volatile unsigned int*) EMMC_LSADC1_PAD1_LEVEL_SET4_reg))
#define EMMC_LSADC1_PAD1_LEVEL_SET4_inst_adr                                         "0x0056"
#define EMMC_LSADC1_PAD1_LEVEL_SET4_inst                                             0x0056
#define EMMC_LSADC1_PAD1_LEVEL_SET4_Level_4_top_bound_shift                          (24)
#define EMMC_LSADC1_PAD1_LEVEL_SET4_Level_4_top_bound_mask                           (0xFF000000)
#define EMMC_LSADC1_PAD1_LEVEL_SET4_Level_4_top_bound(data)                          (0xFF000000&((data)<<24))
#define EMMC_LSADC1_PAD1_LEVEL_SET4_Level_4_top_bound_src(data)                      ((0xFF000000&(data))>>24)
#define EMMC_LSADC1_PAD1_LEVEL_SET4_get_Level_4_top_bound(data)                      ((0xFF000000&(data))>>24)
#define EMMC_LSADC1_PAD1_LEVEL_SET4_Level_4_low_bound_shift                          (16)
#define EMMC_LSADC1_PAD1_LEVEL_SET4_Level_4_low_bound_mask                           (0x00FF0000)
#define EMMC_LSADC1_PAD1_LEVEL_SET4_Level_4_low_bound(data)                          (0x00FF0000&((data)<<16))
#define EMMC_LSADC1_PAD1_LEVEL_SET4_Level_4_low_bound_src(data)                      ((0x00FF0000&(data))>>16)
#define EMMC_LSADC1_PAD1_LEVEL_SET4_get_Level_4_low_bound(data)                      ((0x00FF0000&(data))>>16)
#define EMMC_LSADC1_PAD1_LEVEL_SET4_Block4_en_shift                                  (15)
#define EMMC_LSADC1_PAD1_LEVEL_SET4_Block4_en_mask                                   (0x00008000)
#define EMMC_LSADC1_PAD1_LEVEL_SET4_Block4_en(data)                                  (0x00008000&((data)<<15))
#define EMMC_LSADC1_PAD1_LEVEL_SET4_Block4_en_src(data)                              ((0x00008000&(data))>>15)
#define EMMC_LSADC1_PAD1_LEVEL_SET4_get_Block4_en(data)                              ((0x00008000&(data))>>15)
#define EMMC_LSADC1_PAD1_LEVEL_SET4_INT_en4_shift                                    (1)
#define EMMC_LSADC1_PAD1_LEVEL_SET4_INT_en4_mask                                     (0x00000002)
#define EMMC_LSADC1_PAD1_LEVEL_SET4_INT_en4(data)                                    (0x00000002&((data)<<1))
#define EMMC_LSADC1_PAD1_LEVEL_SET4_INT_en4_src(data)                                ((0x00000002&(data))>>1)
#define EMMC_LSADC1_PAD1_LEVEL_SET4_get_INT_en4(data)                                ((0x00000002&(data))>>1)
#define EMMC_LSADC1_PAD1_LEVEL_SET4_INT_pending_bit4_shift                           (0)
#define EMMC_LSADC1_PAD1_LEVEL_SET4_INT_pending_bit4_mask                            (0x00000001)
#define EMMC_LSADC1_PAD1_LEVEL_SET4_INT_pending_bit4(data)                           (0x00000001&((data)<<0))
#define EMMC_LSADC1_PAD1_LEVEL_SET4_INT_pending_bit4_src(data)                       ((0x00000001&(data))>>0)
#define EMMC_LSADC1_PAD1_LEVEL_SET4_get_INT_pending_bit4(data)                       ((0x00000001&(data))>>0)


#define EMMC_LSADC1_PAD1_LEVEL_SET5                                                  0x9801295C
#define EMMC_LSADC1_PAD1_LEVEL_SET5_reg_addr                                         "0x9801295C"
#define EMMC_LSADC1_PAD1_LEVEL_SET5_reg                                              0x9801295C
#define set_EMMC_LSADC1_PAD1_LEVEL_SET5_reg(data)   (*((volatile unsigned int*) EMMC_LSADC1_PAD1_LEVEL_SET5_reg)=data)
#define get_EMMC_LSADC1_PAD1_LEVEL_SET5_reg   (*((volatile unsigned int*) EMMC_LSADC1_PAD1_LEVEL_SET5_reg))
#define EMMC_LSADC1_PAD1_LEVEL_SET5_inst_adr                                         "0x0057"
#define EMMC_LSADC1_PAD1_LEVEL_SET5_inst                                             0x0057
#define EMMC_LSADC1_PAD1_LEVEL_SET5_Level_5_top_bound_shift                          (24)
#define EMMC_LSADC1_PAD1_LEVEL_SET5_Level_5_top_bound_mask                           (0xFF000000)
#define EMMC_LSADC1_PAD1_LEVEL_SET5_Level_5_top_bound(data)                          (0xFF000000&((data)<<24))
#define EMMC_LSADC1_PAD1_LEVEL_SET5_Level_5_top_bound_src(data)                      ((0xFF000000&(data))>>24)
#define EMMC_LSADC1_PAD1_LEVEL_SET5_get_Level_5_top_bound(data)                      ((0xFF000000&(data))>>24)
#define EMMC_LSADC1_PAD1_LEVEL_SET5_Level_5_low_bound_shift                          (16)
#define EMMC_LSADC1_PAD1_LEVEL_SET5_Level_5_low_bound_mask                           (0x00FF0000)
#define EMMC_LSADC1_PAD1_LEVEL_SET5_Level_5_low_bound(data)                          (0x00FF0000&((data)<<16))
#define EMMC_LSADC1_PAD1_LEVEL_SET5_Level_5_low_bound_src(data)                      ((0x00FF0000&(data))>>16)
#define EMMC_LSADC1_PAD1_LEVEL_SET5_get_Level_5_low_bound(data)                      ((0x00FF0000&(data))>>16)
#define EMMC_LSADC1_PAD1_LEVEL_SET5_Block5_en_shift                                  (15)
#define EMMC_LSADC1_PAD1_LEVEL_SET5_Block5_en_mask                                   (0x00008000)
#define EMMC_LSADC1_PAD1_LEVEL_SET5_Block5_en(data)                                  (0x00008000&((data)<<15))
#define EMMC_LSADC1_PAD1_LEVEL_SET5_Block5_en_src(data)                              ((0x00008000&(data))>>15)
#define EMMC_LSADC1_PAD1_LEVEL_SET5_get_Block5_en(data)                              ((0x00008000&(data))>>15)
#define EMMC_LSADC1_PAD1_LEVEL_SET5_INT_en5_shift                                    (1)
#define EMMC_LSADC1_PAD1_LEVEL_SET5_INT_en5_mask                                     (0x00000002)
#define EMMC_LSADC1_PAD1_LEVEL_SET5_INT_en5(data)                                    (0x00000002&((data)<<1))
#define EMMC_LSADC1_PAD1_LEVEL_SET5_INT_en5_src(data)                                ((0x00000002&(data))>>1)
#define EMMC_LSADC1_PAD1_LEVEL_SET5_get_INT_en5(data)                                ((0x00000002&(data))>>1)
#define EMMC_LSADC1_PAD1_LEVEL_SET5_INT_pending_bit5_shift                           (0)
#define EMMC_LSADC1_PAD1_LEVEL_SET5_INT_pending_bit5_mask                            (0x00000001)
#define EMMC_LSADC1_PAD1_LEVEL_SET5_INT_pending_bit5(data)                           (0x00000001&((data)<<0))
#define EMMC_LSADC1_PAD1_LEVEL_SET5_INT_pending_bit5_src(data)                       ((0x00000001&(data))>>0)
#define EMMC_LSADC1_PAD1_LEVEL_SET5_get_INT_pending_bit5(data)                       ((0x00000001&(data))>>0)


#define EMMC_LSADC1_INT_PAD0                                                         0x98012978
#define EMMC_LSADC1_INT_PAD0_reg_addr                                                "0x98012978"
#define EMMC_LSADC1_INT_PAD0_reg                                                     0x98012978
#define set_EMMC_LSADC1_INT_PAD0_reg(data)   (*((volatile unsigned int*) EMMC_LSADC1_INT_PAD0_reg)=data)
#define get_EMMC_LSADC1_INT_PAD0_reg   (*((volatile unsigned int*) EMMC_LSADC1_INT_PAD0_reg))
#define EMMC_LSADC1_INT_PAD0_inst_adr                                                "0x005E"
#define EMMC_LSADC1_INT_PAD0_inst                                                    0x005E
#define EMMC_LSADC1_INT_PAD0_ADC_value0latch_shift                                   (8)
#define EMMC_LSADC1_INT_PAD0_ADC_value0latch_mask                                    (0x00003F00)
#define EMMC_LSADC1_INT_PAD0_ADC_value0latch(data)                                   (0x00003F00&((data)<<8))
#define EMMC_LSADC1_INT_PAD0_ADC_value0latch_src(data)                               ((0x00003F00&(data))>>8)
#define EMMC_LSADC1_INT_PAD0_get_ADC_value0latch(data)                               ((0x00003F00&(data))>>8)
#define EMMC_LSADC1_INT_PAD0_INT_latchstatus_shift                                   (0)
#define EMMC_LSADC1_INT_PAD0_INT_latchstatus_mask                                    (0x00000001)
#define EMMC_LSADC1_INT_PAD0_INT_latchstatus(data)                                   (0x00000001&((data)<<0))
#define EMMC_LSADC1_INT_PAD0_INT_latchstatus_src(data)                               ((0x00000001&(data))>>0)
#define EMMC_LSADC1_INT_PAD0_get_INT_latchstatus(data)                               ((0x00000001&(data))>>0)


#define EMMC_LSADC1_INT_PAD1                                                         0x9801297C
#define EMMC_LSADC1_INT_PAD1_reg_addr                                                "0x9801297C"
#define EMMC_LSADC1_INT_PAD1_reg                                                     0x9801297C
#define set_EMMC_LSADC1_INT_PAD1_reg(data)   (*((volatile unsigned int*) EMMC_LSADC1_INT_PAD1_reg)=data)
#define get_EMMC_LSADC1_INT_PAD1_reg   (*((volatile unsigned int*) EMMC_LSADC1_INT_PAD1_reg))
#define EMMC_LSADC1_INT_PAD1_inst_adr                                                "0x005F"
#define EMMC_LSADC1_INT_PAD1_inst                                                    0x005F
#define EMMC_LSADC1_INT_PAD1_ADC_value1latch_shift                                   (8)
#define EMMC_LSADC1_INT_PAD1_ADC_value1latch_mask                                    (0x00003F00)
#define EMMC_LSADC1_INT_PAD1_ADC_value1latch(data)                                   (0x00003F00&((data)<<8))
#define EMMC_LSADC1_INT_PAD1_ADC_value1latch_src(data)                               ((0x00003F00&(data))>>8)
#define EMMC_LSADC1_INT_PAD1_get_ADC_value1latch(data)                               ((0x00003F00&(data))>>8)
#define EMMC_LSADC1_INT_PAD1_INT_latchstatus_shift                                   (0)
#define EMMC_LSADC1_INT_PAD1_INT_latchstatus_mask                                    (0x00000001)
#define EMMC_LSADC1_INT_PAD1_INT_latchstatus(data)                                   (0x00000001&((data)<<0))
#define EMMC_LSADC1_INT_PAD1_INT_latchstatus_src(data)                               ((0x00000001&(data))>>0)
#define EMMC_LSADC1_INT_PAD1_get_INT_latchstatus(data)                               ((0x00000001&(data))>>0)


#endif
