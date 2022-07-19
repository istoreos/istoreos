/**************************************************************
 Spec Version                  : 0.0.1
 Parser Version                : DVR_Parser_6.11(120105)
 CModelGen Version             : 5.1 2012.01.05
 Naming Rule                   :  Register_Name
 Naming Rule                   : Module_Register_Name_reg
 Parse Option                  : Only Parse _op1
 Parse Address Region          : All Address Region 
 Decode bit number             : 12 bits
 Firmware Header Generate Date : 2015/7/3 10:1:36
***************************************************************/


#ifndef _DP_IP_REG_DEF__SV_
#define _DP_IP_REG_DEF__SV_
#ifdef  _DP_IP_USE_STRUCT
typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Reserved:5;
unsigned int     enhance_md:1;
unsigned int     lane_num:2;
}DP_MAC_CTRL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     pg_reset:1;
unsigned int     msa_reset:1;
unsigned int     aux_reset:1;
unsigned int     clk_gen_reset:1;
unsigned int     measure_reset:1;
unsigned int     Reserved:3;
}DP_RESET_CTRL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Reserved:2;
unsigned int     dptx_arb_debug_sel:2;
unsigned int     dptx_debug_sel:4;
}DP_DEBUG_CTRL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     dptx_irq_en:1;
unsigned int     Reserved:6;
unsigned int     dptx_irq:1;
}DPTX_IRQ_CTRL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     lfifo_full:1;
unsigned int     lfifo_udf:1;
unsigned int     lfifo_udf_uni:1;
unsigned int     sfifo_ful:1;
unsigned int     sfifo_ove:1;
unsigned int     sfifo_ove_uni:1;
unsigned int     lfifo_maxwl_clear:1;
unsigned int     Reserved:1;
}PG_FIFO_CTRL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     max_wl:8;
}MAX_WL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     lfifo_wl:8;
}LFIFO_WL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Reserved:6;
unsigned int     lfifo_udf_int_en:1;
unsigned int     sfifo_ove_int_en:1;
}LFIFO_WL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     mn_vid_auto_en:1;
unsigned int     mn_vid_db:1;
unsigned int     Reserved:6;
}MN_VID_AUTO_EN_1;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     mvid2316:8;
}MN_M_VID_H;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     mvid158:8;
}MN_M_VID_M;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     mvid70:8;
}MN_M_VID_L;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     nvid2316:8;
}MN_N_VID_H;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     nvid158:8;
}MN_N_VID_M;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     nvid70:8;
}MN_N_VID_L;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     mvid_auto2316:8;
}MVID_AUTO_H;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     mvid_auto158:8;
}MVID_AUTO_M;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     mvid_auto70:8;
}MVID_AUTO_L;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     nvid_async158:8;
}NVID_ASYNC_M;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     nvid_async70:8;
}NVID_ASYNC_L;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     msa_db:1;
unsigned int     msa_db_vblank:1;
unsigned int     Reserved:6;
}MSA_CTRL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     colorbit:3;
unsigned int     ycc_col:1;
unsigned int     dyn_range:1;
unsigned int     component_format:2;
unsigned int     sync_clk_en:1;
}MSA_MISC0;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     y_only:1;
unsigned int     Reserved:4;
unsigned int     stereo_video_attr:2;
unsigned int     vtt_even:1;
}MN_STRM_ATTR_MISC1;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     htotal158:8;
}MN_STRM_ATTR_HTT_M;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     htotal70:8;
}MN_STRM_ATTR_HTT_L;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     hstart158:8;
}MN_STRM_ATTR_HST_M;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     hstart70:8;
}MN_STRM_ATTR_HST_L;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     hwidth158:8;
}MN_STRM_ATTR_HWD_M;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     hwidth70:8;
}MN_STRM_ATTR_HWD_L;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     hsp:1;
unsigned int     hsw148:7;
}MN_STRM_ATTR_HSW_M;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     hsw70:8;
}MN_STRM_ATTR_HSW_L;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     vtotal158:8;
}MN_STRM_ATTR_VTTE_M;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     vtotal70:8;
}MN_STRM_ATTR_VTTE_L;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     vstart158:8;
}MN_STRM_ATTR_VST_M;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     vstart70:8;
}MN_STRM_ATTR_VST_L;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     vheight158:8;
}MN_STRM_ATTR_VHT_M;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     vheight70:8;
}MN_STRM_ATTR_VHT_L;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     vsp:1;
unsigned int     vsw148:7;
}MN_STRM_ATTR_VSW_M;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     vsw70:8;
}MN_STRM_ATTR_VSW_L;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Reserved:5;
unsigned int     audiomute_flag:1;
unsigned int     novideo_flag:1;
unsigned int     interlace:1;
}VBID;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Reserved:7;
unsigned int     vbid_fw_ctrl:1;
}VBID_FW_CTL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Reserved:6;
unsigned int     vactive_md:1;
unsigned int     arbiter_en:1;
}ARBITER_CTRL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Reserved:1;
unsigned int     v_data_per_line148:7;
}V_DATA_PER_LINE0;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     v_data_per_line70:8;
}V_DATA_PER_LINE1;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Reserved:1;
unsigned int     tu_size:7;
}TU_SIZE;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Reserved:1;
unsigned int     tu_data_size93:7;
}TU_DATA_SIZE0;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Reserved:5;
unsigned int     tu_data_size20:3;
}TU_DATA_SIZE1;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Reserved:1;
unsigned int     hdelay148:7;
}HDELAY0;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     hdelay70:8;
}HDELAY1;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Reserved:1;
unsigned int     auto_hdelay148:7;
}AUTO_HDELAY0;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     auto_hdelay70:8;
}AUTO_HDELAY1;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     wl_mid_regen:1;
unsigned int     wl_mid_set:7;
}LFIFO_WL_SET;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Reserved:1;
unsigned int     sec_end_cnt148:7;
}ARBITER_SEC_END_CNT_HB;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     sec_end_cnt70:8;
}ARBITER_SEC_END_CNT_LB;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Reserved:3;
unsigned int     den_line_end_occur:1;
unsigned int     v_active_occur:1;
unsigned int     sec_tx_end_nv_miss:1;
unsigned int     sec_tx_end_v_miss:1;
unsigned int     vsync_de:1;
}ARBITER_DEBUG;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Reserved:5;
unsigned int     dptx_force_ctsfifo_rstn:1;
unsigned int     dptx_en_ctsfifo_vsrst:1;
unsigned int     dptx_en_ctsfifo_bypass:1;
}DPTX_CTSFIFO_CTRL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     dptx_ctsfifo_rsv1:8;
}DPTX_CTSFIFO_RSV1;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Reserved:6;
unsigned int     dptx_vesa_source:1;
unsigned int     dptx_source:1;
}DPTX_TOP_CTL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     dptx_rsv1:8;
}DPTX_TOP_RSV1;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     dptx_rsv2:8;
}DPTX_TOP_RSV2;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     min_h_blank_width_clr:1;
unsigned int     min_h_blank_width148:7;
}ARBITER_MIN_H_BLANK_WIDTH_HB;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     min_h_blank_width70:8;
}ARBITER_MIN_H_BLANK_WIDTH_LB;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Reserved:5;
unsigned int     den_line_end_occur_int_en:1;
unsigned int     sec_tx_end_nv_miss_int_en:1;
unsigned int     sec_tx_end_v_miss_int_en:1;
}ARBITER_INTERRUPT_CTRL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Reserved:6;
unsigned int     measure_bypass_en:1;
unsigned int     vesa_fmt_regen_en:1;
}VESA_FMT_REGEN;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     ckrd_sel:2;
unsigned int     ckrd_sel_post:1;
unsigned int     div_num:5;
}DPTX_CLK_GEN;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     bist_mode_pg:1;
unsigned int     bist_done_pg:1;
unsigned int     bist_fail_pg:1;
unsigned int     dvse_pg:1;
unsigned int     dvs_pg:4;
}PG_MBIST_CTRL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     drf_bist_mode_pg:1;
unsigned int     drf_test_resume_pg:1;
unsigned int     drf_start_pause_pg:1;
unsigned int     drf_bist_done_pg:1;
unsigned int     drf_bist_fail_pg:1;
unsigned int     Reserved:1;
unsigned int     bist_clk_en_pg:1;
unsigned int     bist_rst_pg:1;
}PG_DRF_MBIST_CTRL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     sec_idle_end_cnt:8;
}ARBITER_SEC_IDLE_END_CNT;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Dummy:6;
unsigned int     field_inv:1;
unsigned int     field_md:1;
}DPTX_TOP_RSV3;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Dummy:8;
}DPTX_TOP_RSV4;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Dummy:8;
}DPTX_TOP_RSV5;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Dummy:8;
}DPTX_TOP_RSV6;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Dummy:8;
}DPTX_TOP_RSV7;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Dummy:8;
}DPTX_TOP_RSV8;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Dummy:8;
}DPTX_TOP_RSV9;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Dummy:8;
}DPTX_TOP_RSV10;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     v2analog:4;
unsigned int     lane_num:2;
unsigned int     mst_en:1;
unsigned int     phy_reset:1;
}DP_PHY_CTRL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     tx_ml_pat_sel:4;
unsigned int     switch_pattern_auto:1;
unsigned int     prbs_reverse:1;
unsigned int     tx_ml_pat_sel_en:1;
unsigned int     pat_sel_dbuf:1;
}DPTX_ML_PAT_SEL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     pat_byte0:8;
}CUSTOM_PATTERN_0;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     pat_byte1:8;
}CUSTOM_PATTERN_1;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     pat_byte2:8;
}CUSTOM_PATTERN_2;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     pat_byte3:8;
}CUSTOM_PATTERN_3;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     pat_byte4:8;
}CUSTOM_PATTERN_4;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     pat_byte5:8;
}CUSTOM_PATTERN_5;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     pat_byte6:8;
}CUSTOM_PATTERN_6;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     pat_byte7:8;
}CUSTOM_PATTERN_7;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     pat_byte8:8;
}CUSTOM_PATTERN_8;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     pat_byte9:8;
}CUSTOM_PATTERN_9;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Reserved:7;
unsigned int     eye_pat_sel:1;
}COMPLIANCE_EYE_PATTERN;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     hw_measure_en:1;
unsigned int     Reserved:2;
unsigned int     sr_insert_en:1;
unsigned int     Reserved:1;
unsigned int     dptx_skew_en:1;
unsigned int     dptx_scb_mode:1;
unsigned int     dptx_scb_en:1;
}DPTX_PHY_CTRL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     lane0_source:2;
unsigned int     lane1_source:2;
unsigned int     lane2_source:2;
unsigned int     lane3_source:2;
}DPTX_LANE_SWAP;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Reserved:5;
unsigned int     dptx_8b10b_tst_mode:3;
}DPTX_8B10B_TST;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     dptx_phy_dummy:8;
}DPTX_PHY_DUMMY;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     riv6356:8;
}RIV0;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     riv5548:8;
}RIV1;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     riv4740:8;
}RIV2;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     riv3932:8;
}RIV3;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     riv3124:8;
}RIV4;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     riv2316:8;
}RIV5;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     riv158:8;
}RIV6;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     riv70:8;
}RIV7;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Reserved:3;
unsigned int     repeater:1;
unsigned int     key_dl_en:1;
unsigned int     hdcp_encrypted:1;
unsigned int     hdcp_encry_en:1;
unsigned int     hdcp_en:1;
}DPTX_HDCP_CTRL1;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Reserved:1;
unsigned int     km_clk_sel:1;
unsigned int     ri_en:1;
unsigned int     an_sel:1;
unsigned int     an_gen_start:1;
unsigned int     an_gen_done:1;
unsigned int     computation_en:1;
unsigned int     computation_done:1;
}DPTX_HDCP_CTRL2;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     key_dl_port:8;
}DP_HDCP_KEY_DL_PORT;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     key_out:8;
}DP_HDCP_KEY_OUTPUT;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     an_63_56:8;
}AN_BYTE_7;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     an_55_48:8;
}AN_BYTE_6;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     an_47_40:8;
}AN_BYTE_5;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     an_39_32:8;
}AN_BYTE_4;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     an_31_24:8;
}AN_BYTE_3;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     an_23_16:8;
}AN_BYTE_2;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     an_15_8:8;
}AN_BYTE_1;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     an_7_0:8;
}AN_BYTE_0;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     m06356:8;
}M0_BYTE_7;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     m05548:8;
}M0_BYTE_6;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     m04740:8;
}M0_BYTE_5;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     m03932:8;
}M0_BYTE_4;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     m03124:8;
}M0_BYTE_3;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     m02316:8;
}M0_BYTE_2;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     m0158:8;
}M0_BYTE_1;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     m070:8;
}M0_BYTE_0;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     km5548:8;
}KM_BYTE_6;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     km4740:8;
}KM_BYTE_5;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     km3932:8;
}KM_BYTE_4;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     km3124:8;
}KM_BYTE_3;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     km2316:8;
}KM_BYTE_2;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     km158:8;
}KM_BYTE_1;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     km70:8;
}KM_BYTE_0;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     r0158:8;
}R0_BYTE_MSB;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     r070:8;
}R0_BYTE_LSB;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     ri158:8;
}RI_BYTE_MSB;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     ri70:8;
}RI_BYTE_LSB;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     bksv70:8;
}BKSV_0;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     bksv158:8;
}BKSV_1;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     bksv2316:8;
}BKSV_2;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     bksv3124:8;
}BKSV_3;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     bksv3932:8;
}BKSV_4;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     li_pattern158:8;
}HDCP_TX_LIP_H;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     li_pattern70:8;
}HDCP_TX_LIP_L;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     lk_pos:1;
unsigned int     Reserved:3;
unsigned int     freerun_init_en:1;
unsigned int     check_bksv_en:1;
unsigned int     check_bksv_done:1;
unsigned int     check_bksv_fail:1;
}DP_HDCP_TX;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     hdcp_drf_bist_en:1;
unsigned int     hdcp_drf_bist_done:1;
unsigned int     hdcp_drf_bist_fail:1;
unsigned int     hdcp_drf_test_resume:1;
unsigned int     hdcp_drf_start_pause:1;
unsigned int     hdcp_bist_en:1;
unsigned int     hdcp_bist_done:1;
unsigned int     hdcp_bist_fail:1;
}DP_HDCP_BIST;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     freerun_init:8;
}DP_HDCP_AN_SEED;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     dp_hdcp_tx_irq:1;
unsigned int     Reserved:4;
unsigned int     computation_done_irq_en:1;
unsigned int     bksv_fail_irq_en:1;
unsigned int     bksv_done_irq_en:1;
}HDCP_IRQ_EVENT;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Reserved:3;
unsigned int     authdone:1;
unsigned int     authkm:1;
unsigned int     dp_hdcp_tst_mode:2;
unsigned int     dp_hdcp_tst_en:1;
}DPTX_HDCP_TST;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     sha_v_select:3;
unsigned int     sha_done:1;
unsigned int     sha_run_first:1;
unsigned int     sha_run_en:1;
unsigned int     sha_wptr_rst:1;
unsigned int     sha_data_wen:1;
}DP_HDCP_TX_SHA_CTRL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     sha_data3124:8;
}DP_HDCP_TX_SHA_DATA_3;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     sha_data2316:8;
}DP_HDCP_TX_SHA_DATA_2;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     sha_data158:8;
}DP_HDCP_TX_SHA_DATA_1;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     sha_data70:8;
}DP_HDCP_TX_SHA_DATA_0;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     sha_v_out3124:8;
}DP_HDCP_TX_SHA_OUT_3;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     sha_v_out2316:8;
}DP_HDCP_TX_SHA_OUT_2;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     sha_v_out158:8;
}DP_HDCP_TX_SHA_OUT_1;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     sha_v_out70:8;
}DP_HDCP_TX_SHA_OUT_0;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     ecf_compute_auto:1;
unsigned int     ecf_byte_0:7;
}HDCP_ECF_BYTE0;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     ecf_byte_1:8;
}HDCP_ECF_BYTE1;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     ecf_byte_2:8;
}HDCP_ECF_BYTE2;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     ecf_byte_3:8;
}HDCP_ECF_BYTE3;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     ecf_byte_4:8;
}HDCP_ECF_BYTE4;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     ecf_byte_5:8;
}HDCP_ECF_BYTE5;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     ecf_byte_6:8;
}HDCP_ECF_BYTE6;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     ecf_byte_7:8;
}HDCP_ECF_BYTE7;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Reserved:1;
unsigned int     hdcp_enc_stream_1:1;
unsigned int     alloc_pbn_1:6;
}DP_STREAM_1_PBN;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Reserved:1;
unsigned int     hdcp_enc_stream_2:1;
unsigned int     alloc_pbn_2:6;
}DP_STREAM_2_PBN;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Reserved:1;
unsigned int     hdcp_enc_stream_3:1;
unsigned int     alloc_pbn_3:6;
}DP_STREAM_3_PBN;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Reserved:1;
unsigned int     hdcp_enc_stream_4:1;
unsigned int     alloc_pbn_4:6;
}DP_STREAM_4_PBN;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     aes_cipher_key127120:8;
}HDCP_AES_CIPHER_KEY_15;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     aes_cipher_key119112:8;
}HDCP_AES_CIPHER_KEY_14;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     aes_cipher_key111104:8;
}HDCP_AES_CIPHER_KEY_13;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     aes_cipher_key10396:8;
}HDCP_AES_CIPHER_KEY_12;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     aes_cipher_key9588:8;
}HDCP_AES_CIPHER_KEY_11;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     aes_cipher_key8780:8;
}HDCP_AES_CIPHER_KEY_10;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     aes_cipher_key7972:8;
}HDCP_AES_CIPHER_KEY_9;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     aes_cipher_key7164:8;
}HDCP_AES_CIPHER_KEY_8;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     aes_cipher_key6356:8;
}HDCP_AES_CIPHER_KEY_7;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     aes_cipher_key5548:8;
}HDCP_AES_CIPHER_KEY_6;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     aes_cipher_key4740:8;
}HDCP_AES_CIPHER_KEY_5;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     aes_cipher_key3932:8;
}HDCP_AES_CIPHER_KEY_4;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     aes_cipher_key3124:8;
}HDCP_AES_CIPHER_KEY_3;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     aes_cipher_key2316:8;
}HDCP_AES_CIPHER_KEY_2;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     aes_cipher_key158:8;
}HDCP_AES_CIPHER_KEY_1;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     aes_cipher_key70:8;
}HDCP_AES_CIPHER_KEY_0;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     st1_type:1;
unsigned int     st2_type:1;
unsigned int     st3_type:1;
unsigned int     st4_type:1;
unsigned int     header_type:1;
unsigned int     Reserved:1;
unsigned int     authdone_hdcp22:1;
unsigned int     hdcp22_en:1;
}HDCP22_CTRL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     type_to_aes0:8;
}HDCP22_TYPE_AES_0;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     type_to_aes1:8;
}HDCP22_TYPE_AES_1;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     DUMMY:7;
unsigned int     Bist_clk_en_hdcp:1;
}DUMMY_1;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     DUMMY:8;
}DUMMY_2;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     DUMMY:8;
}DUMMY_3;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     hpd_en:1;
unsigned int     hpd_clk_div:2;
unsigned int     hpd_deb_level:2;
unsigned int     hpd_deb:1;
unsigned int     Reserved:2;
}HPD_CTRL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     ihpd_int:1;
unsigned int     shpd_int:1;
unsigned int     lhpd_int:1;
unsigned int     uhpd_int:1;
unsigned int     unhpd_int:1;
unsigned int     rhpd_int:1;
unsigned int     fhpd_int:1;
unsigned int     Reserved:1;
}HPD_IRQ;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     ihpd_int_en:1;
unsigned int     shpd_int_en:1;
unsigned int     lhpd_int_en:1;
unsigned int     uhpd_int_en:1;
unsigned int     unhpd_int_en:1;
unsigned int     rhpd_int_en:1;
unsigned int     fhpd_int_en:1;
unsigned int     Reserved:1;
}HPD_IRQ_EN;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     hpd_t5118:4;
unsigned int     hpd_t10118:4;
}HPD_TIMER1;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     hpd_t570:8;
}HPD_TIMER2;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     hpd_t1070:8;
}HPD_TIMER3;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Reserved:4;
unsigned int     hpd_t20118:4;
}HPD_TIMER4;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     hpd_t2070:8;
}HPD_TIMER5;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     hpd_t100158:8;
}HPD_TIMER6;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     hpd_t10070:8;
}HPD_TIMER7;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     hpd_long158:8;
}HPD_LONG0;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     hpd_long70:8;
}HPD_LONG1;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Reserved:4;
unsigned int     hpd_state:4;
}HPD_STATE;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     hpd_rsv1:8;
}RESERVED_0;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     hpd_rsv2:8;
}RESERVED_1;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     reg_pow_dptx:1;
unsigned int     reg_dptx_testen:1;
unsigned int     Reserved:1;
unsigned int     reg_dptx_cmu_en:1;
unsigned int     reg_pow_dptx_lane30:4;
}DPTX_PHY_CTRL0;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     dptx_tx2idle30:4;
unsigned int     reg_dptx_pdown30:4;
}DPTX_PHY_CTRL1;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     reg_dptx_force_rcvdet:1;
unsigned int     reg_dptx_rcvdet_en:1;
unsigned int     reg_dptx_rcv_detect:1;
unsigned int     Reserved:5;
}DPTX_RCV_DET0;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     dptx_rxdet30:4;
unsigned int     dptx_enddet30:4;
}DPTX_RCV_DET1;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     reg_dptx_beacon30:4;
unsigned int     dptx_pn_swap30:4;
}DPTX_PN_SWAP;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     tx_en:1;
unsigned int     rate_mode:2;
unsigned int     fifo_in_flip:1;
unsigned int     Reserved:2;
unsigned int     wovflow:1;
unsigned int     rudflow:1;
}DPTX_SFIFO_CTRL0;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     water_level:3;
unsigned int     Reserved:2;
unsigned int     rd_start_pos:3;
}DPTX_SFIFO_CTRL1;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     fifo_source_sel:1;
unsigned int     Dummy:7;
}DPTX_SFIFO_LANE_SWAP0;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     lane0_source:2;
unsigned int     lane1_source:2;
unsigned int     lane2_source:2;
unsigned int     lane3_source:2;
}DPTX_SFIFO_LANE_SWAP1;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     v2a_sel:1;
unsigned int     v2a_val:4;
unsigned int     Reserved:3;
}DPTX_SFIFO_INT_EN;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Reserved:2;
unsigned int     infoframe_mpeg_en:1;
unsigned int     infoframe_avi_en:1;
unsigned int     infoframe_audio_en:1;
unsigned int     psr_en:1;
unsigned int     audio_timestamp_en:1;
unsigned int     audio_en:1;
}SEC_FUNCTION_CTRL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Reserved:7;
unsigned int     strm_attr_errc_en:1;
}SEC_RESERVED_0;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Reserved:6;
unsigned int     sec_db_vblank:1;
unsigned int     sec_db:1;
}SEC_DBUF_CTRL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Reserved:1;
unsigned int     sec_lfifo_ctrl_debug_sel:2;
unsigned int     bs_9th_occur:1;
unsigned int     Reserved:1;
unsigned int     sec_debug_sel:3;
}SEC_DEBUG;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     vsc_db0:8;
}SEC_PSR_DB0;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     vsc_db1:8;
}SEC_PSR_DB1;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     vsc_db2:8;
}SEC_PSR_DB2;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     vsc_db3:8;
}SEC_PSR_DB3;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     vsc_db4:8;
}SEC_PSR_DB4;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     vsc_db5:8;
}SEC_PSR_DB5;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     vsc_db6:8;
}SEC_PSR_DB6;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     vsc_db7:8;
}SEC_PSR_DB7;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     vsc_db8:8;
}SEC_PSR_DB8;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     vsc_db9:8;
}SEC_PSR_DB9;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     vsc_db10:8;
}SEC_PSR_DB10;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     vsc_db11:8;
}SEC_PSR_DB11;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     vsc_db12:8;
}SEC_PSR_DB12;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     vsc_db13:8;
}SEC_PSR_DB13;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     vsc_db14:8;
}SEC_PSR_DB14;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     vsc_db15:8;
}SEC_PSR_DB15;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Reserved:8;
}SEC_RESERVED_1;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Reserved:8;
}SEC_RESERVED_2;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Reserved:8;
}SEC_RESERVED_3;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Reserved:8;
}SEC_RESERVED_4;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     audio_source:1;
unsigned int     eight_channel_layout:1;
unsigned int     sec_aud_ptr_errc:1;
unsigned int     audio_idle_send:1;
unsigned int     audio_sfifo_send_wl:4;
}AUD_FUNCTION_CTRL1;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     aud_sp:1;
unsigned int     aud_r:1;
unsigned int     aud_pr:2;
unsigned int     aud_p:1;
unsigned int     aud_c:1;
unsigned int     aud_u:1;
unsigned int     aud_v:1;
}AUD_PAYLOAD_B3;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     aud_pkt_id:8;
}DP_AUD_ID;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Reserved:8;
}SEC_RESERVED_6;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     aud_lfifo_of:1;
unsigned int     max_lfifo_wl_clear:1;
unsigned int     Reserved:6;
}AUD_FIFO_CTRL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Reserved:1;
unsigned int     max_lfifo_wl:7;
}AUD_LFIFO_MAX_WL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Reserved:1;
unsigned int     lfifo_wl:7;
}AUD_LFIFO_WL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Reserved:7;
unsigned int     aud_lfifo_of_int_en:1;
}AUD_INTERRUPT_CTRL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     maud2316:8;
}AUD_TS_MAUD_H;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     maud158:8;
}AUD_TS_MAUD_M;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     maud70:8;
}AUD_TS_MAUD_L;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     naud2316:8;
}AUD_TS_NAUD_H;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     naud158:8;
}AUD_TS_NAUD_M;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     naud70:8;
}AUD_TS_NAUD_L;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     info_audio_db0:8;
}SEC_INFO_AUD_DB0;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     info_audio_db1:8;
}SEC_INFO_AUD_DB1;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     info_audio_db2:8;
}SEC_INFO_AUD_DB2;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     info_audio_db3:8;
}SEC_INFO_AUD_DB3;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     info_audio_db4:8;
}SEC_INFO_AUD_DB4;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     info_audio_db5:8;
}SEC_INFO_AUD_DB5;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     info_audio_db6:8;
}SEC_INFO_AUD_DB6;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     info_audio_db7:8;
}SEC_INFO_AUD_DB7;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     info_audio_db8:8;
}SEC_INFO_AUD_DB8;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     info_audio_db9:8;
}SEC_INFO_AUD_DB9;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     info_avi_db0:8;
}SEC_INFO_AVI_DB0;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     info_avi_db1:8;
}SEC_INFO_AVI_DB1;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     info_avi_db2:8;
}SEC_INFO_AVI_DB2;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     info_avi_db3:8;
}SEC_INFO_AVI_DB3;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     info_avi_db4:8;
}SEC_INFO_AVI_DB4;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     info_avi_db5:8;
}SEC_INFO_AVI_DB5;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     info_avi_db6:8;
}SEC_INFO_AVI_DB6;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     info_avi_db7:8;
}SEC_INFO_AVI_DB7;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     info_avi_db8:8;
}SEC_INFO_AVI_DB8;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     info_avi_db9:8;
}SEC_INFO_AVI_DB9;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     info_avi_db10:8;
}SEC_INFO_AVI_DB10;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     info_avi_db11:8;
}SEC_INFO_AVI_DB11;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     info_avi_db12:8;
}SEC_INFO_AVI_DB12;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     info_mpeg_db0:8;
}SEC_INFO_MPEG_DB0;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     info_mpeg_db1:8;
}SEC_INFO_MPEG_DB1;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     info_mpeg_db2:8;
}SEC_INFO_MPEG_DB2;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     info_mpeg_db3:8;
}SEC_INFO_MPEG_DB3;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     info_mpeg_db4:8;
}SEC_INFO_MPEG_DB4;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     info_mpeg_db5:8;
}SEC_INFO_MPEG_DB5;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     info_mpeg_db6:8;
}SEC_INFO_MPEG_DB6;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     info_mpeg_db7:8;
}SEC_INFO_MPEG_DB7;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     info_mpeg_db8:8;
}SEC_INFO_MPEG_DB8;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     info_mpeg_db9:8;
}SEC_INFO_MPEG_DB9;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     audio_long_packet:1;
unsigned int     audio_long_packet_end_chk:1;
unsigned int     max_long_packet_cnt:6;
}AUD_FUNCTION_CTRL2;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Reserved:4;
unsigned int     audio_i2s_8ch:1;
unsigned int     audio_source_db_en:1;
unsigned int     tx_code_nb_swap:1;
unsigned int     tx_code_reverse:1;
}AUD_FUNCTION_CTRL3;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     mst_sec_packet_id:8;
}MST_SEC_PKT_ID;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Reserved:1;
unsigned int     mst_channel_cnt:3;
unsigned int     mst_coding_type:4;
}MST_SEC_PKT_HB3;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     rs_dec_en_strm2:1;
unsigned int     code_nb_swap_strm2:1;
unsigned int     code_reverse_strm2:1;
unsigned int     rs_err2_enh_mode_strm2:1;
unsigned int     rs_err2_mode_strm2:1;
unsigned int     rs_err1:1;
unsigned int     rs_err2:1;
unsigned int     rs_dec_err2_proc:1;
}SEC_RS_DECODE_CTRL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     afreq_det:1;
unsigned int     Reserved:2;
unsigned int     aud_freq_status_method:1;
unsigned int     aud_freq_range_clr:1;
unsigned int     aud_freq_stable:1;
unsigned int     aud_sp_cnt_clr:1;
unsigned int     aud_441_48_same_en:1;
}SEC_AUD_FREQDET_CTRL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     aud_xclk_div:8;
}SEC_AUD_XCLK_DIV;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     aud_freq_time:2;
unsigned int     Reserved:6;
}SEC_AUD_FREQ_TIME;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     aud_freq_range:4;
unsigned int     aud_sp_cnt118:4;
}SEC_AUD_SAMPLE_CNT_HB;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     aud_sp_cnt70:8;
}SEC_AUD_SAMPLE_CNT_LB;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     bist_mode_sec:1;
unsigned int     bist_done_sec:1;
unsigned int     bist_fail_sec:1;
unsigned int     dvse_sec:1;
unsigned int     dvs_sec:4;
}AUD_MBIST_CTRL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     drf_bist_mode_sec:1;
unsigned int     drf_test_resume_sec:1;
unsigned int     drf_start_pause_sec:1;
unsigned int     drf_bist_done_sec:1;
unsigned int     drf_bist_fail_sec:1;
unsigned int     Reserved:1;
unsigned int     bist_clk_en_sec:1;
unsigned int     bist_rst_sec:1;
}AUD_DRF_MBIST_CTRL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     dp_info_fm_rsv0:8;
}DP_INFO_FM_RSV0;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     dp_info_fm_rsv1:8;
}DP_INFO_FM_RSV1;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Reserved:1;
unsigned int     dp_info_fm_adr:7;
}DP_INFO_FM_ADR;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     dp_info_fm_dat:8;
}DP_INFO_FM_DAT;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Reserved:8;
}RESERVED_57;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     vsc_rx_db0:8;
}VSC_RX_DB0;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     vsc_rx_db1:8;
}VSC_RX_DB1;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     vsc_rx_db2:8;
}VSC_RX_DB2;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     vsc_rx_db3:8;
}VSC_RX_DB3;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     vsc_rx_db4:8;
}VSC_RX_DB4;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     vsc_rx_db5:8;
}VSC_RX_DB5;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     vsc_rx_db6:8;
}VSC_RX_DB6;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     vsc_rx_db7:8;
}VSC_RX_DB7;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     aud_th_noaudio118:4;
unsigned int     aud_th_group1118:4;
}AUD_FREQ_TH_0;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     aud_th_group2118:4;
unsigned int     aud_th_group3118:4;
}AUD_FREQ_TH_1;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     aud_th_noaudio70:8;
}AUD_FREQ_TH_2;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     aud_th_group170:8;
}AUD_FREQ_TH_3;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     aud_th_group270:8;
}AUD_FREQ_TH_4;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     aud_th_group370:8;
}AUD_FREQ_TH_5;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     aud_range_th:8;
}AUD_FREQ_TH_6;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Reserved:8;
}RESERVED_67;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Reserved:8;
}RESERVED_68;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Reserved:8;
}RESERVED_69;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     vsc_rx_hb23_care:1;
unsigned int     Reserved:3;
unsigned int     psr_int_en:1;
unsigned int     psr_int:1;
unsigned int     vsc_rx_3d_int_en:1;
unsigned int     vsc_3d_chg:1;
}VSC_CTRL_0;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     vsc_rx_hb0:8;
}VSC_RX_HB0;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     vsc_rx_hb1:8;
}VSC_RX_HB1;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     vsc_rx_hb2:8;
}VSC_RX_HB2;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     vsc_rx_hb3:8;
}VSC_RX_HB3;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Reserved:1;
unsigned int     awd_vbid4_chg_en:1;
unsigned int     awd_vbid3_chg_en:1;
unsigned int     awd_vbid2_chg_en:1;
unsigned int     awd_aud_freq_chg_en:1;
unsigned int     awd_mst_sec_packet_id_chg_en:1;
unsigned int     awd_mst_coding_type_chg_en:1;
unsigned int     awd_mst_channel_cnt_chg_en:1;
}SEC_AWD_CTRL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Reserved:2;
unsigned int     ats_sent:1;
unsigned int     info_aud_sent:1;
unsigned int     aud_freq_chg:1;
unsigned int     mst_sec_packet_id_chg:1;
unsigned int     mst_coding_type_chg:1;
unsigned int     mst_channel_cnt_chg:1;
}SEC_AWD_STATUS_0;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Reserved:1;
unsigned int     irq_vbid4_chg_en:1;
unsigned int     irq_vbid3_chg_en:1;
unsigned int     irq_vbid2_chg_en:1;
unsigned int     irq_aud_freq_chg_en:1;
unsigned int     irq_mst_sec_packet_id_chg_en:1;
unsigned int     irq_mst_coding_type_chg_en:1;
unsigned int     irq_mst_channel_cnt_chg_en:1;
}SEC_IRQ_CTRL0;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     packet_header_hb70:8;
}SEC_PH_HB0;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     packet_header_hb158:8;
}SEC_PH_HB1;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     packet_header_hb2316:8;
}SEC_PH_HB2;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     packet_header_hb3124:8;
}SEC_PH_HB3;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     packet_header_pb70:8;
}SEC_PH_PB0;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     packet_header_pb158:8;
}SEC_PH_PB1;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     packet_header_pb2316:8;
}SEC_PH_PB2;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     packet_header_pb3124:8;
}SEC_PH_PB3;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Reserved:4;
unsigned int     packet_type:4;
}SEC_PH_PACKET_TYPE;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     vbid_4_chg:1;
unsigned int     vbid_3_chg:1;
unsigned int     vbid_2_chg:1;
unsigned int     Reserved:5;
}SEC_AWD_STATUS_1;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Reserved:3;
unsigned int     var_mpg_fr_en:1;
unsigned int     var_mpg_mb_en:1;
unsigned int     var_aud_lsv_en:1;
unsigned int     var_aud_ca_en:1;
unsigned int     var_avi_bar_en:1;
}DP_INFO_VAR_EN_M;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     var_avi_b_en:1;
unsigned int     var_avi_sc_en:1;
unsigned int     var_avi_q_en:1;
unsigned int     var_avi_itc_en:1;
unsigned int     var_avi_pr_en:1;
unsigned int     var_avi_s_en:1;
unsigned int     var_avi_a_en:1;
unsigned int     var_avi_y_en:1;
}DP_INFO_VAR_EN_L;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Reserved:3;
unsigned int     var_mpg_fr:1;
unsigned int     var_mpg_mb:1;
unsigned int     var_aud_lsv:1;
unsigned int     var_aud_ca:1;
unsigned int     var_avi_bar:1;
}DP_INFO_VAR_ST_M;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     var_avi_b:1;
unsigned int     var_avi_sc:1;
unsigned int     var_avi_q:1;
unsigned int     var_avi_itc:1;
unsigned int     var_avi_pr:1;
unsigned int     var_avi_s:1;
unsigned int     var_avi_a:1;
unsigned int     var_avi_y:1;
}DP_INFO_VAR_ST_L;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     ch_status70:8;
}CH_STATUS_0;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     ch_status158:8;
}CH_STATUS_1;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     ch_status2316:8;
}CH_STATUS_2;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     ch_status3124:8;
}CH_STATUS_3;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     ch_status3932:8;
}CH_STATUS_4;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Reserved:4;
unsigned int     swd_by_vsc_en:1;
unsigned int     swd_by_mpg_en:1;
unsigned int     swd_by_aud_en:1;
unsigned int     swd_by_avi_en:1;
}DP_AVWD_CTRL0;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Reserved:8;
}RESERVED_8B;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Reserved:8;
}RESERVED_8C;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Reserved:8;
}RESERVED_8D;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Reserved:8;
}RESERVED_8E;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     i2s_0_switch:1;
unsigned int     i2s_1_switch:1;
unsigned int     i2s_2_switch:1;
unsigned int     i2s_3_switch:1;
unsigned int     pr_field_ch_exist:1;
unsigned int     parity_type:1;
unsigned int     as_payload_byte3_auto:1;
unsigned int     ch_status_cnt_en:1;
}DPTX_I2S_CTRL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Dummy:4;
unsigned int     irq_by_vsc_en:1;
unsigned int     irq_by_mpg_en:1;
unsigned int     irq_by_aud_en:1;
unsigned int     irq_by_avi_en:1;
}SEC_IRQ_CTRL1;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Dummy:8;
}DUMMY_95;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Dummy:8;
}DUMMY_96;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Dummy:8;
}DUMMY_97;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Dummy:6;
unsigned int     aud_freq_chg_deb_md:2;
}DUMMY_98;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Dummy:4;
unsigned int     audio_dec_err_drop:1;
unsigned int     audio_sample_det_md:1;
unsigned int     ch_lyo_fw:1;
unsigned int     hbr_audio_mode:1;
}DUMMY_99;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Dummy:8;
}DUMMY_9A;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Dummy:8;
}DUMMY_9B;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Dummy:8;
}DUMMY_9C;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Reserved:3;
unsigned int     reg_aux_sers:3;
unsigned int     reg_aux_sewins:2;
}DIG_TX_04;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     reg_aux_vldo:3;
unsigned int     reg_aux_selvcom:1;
unsigned int     reg_aux_rx_adjr_p:4;
}AUX_1;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     reg_aux_autok:1;
unsigned int     reg_aux_se_fromp:1;
unsigned int     reg_aux_en_singleend:1;
unsigned int     reg_aux_sel_threshold:2;
unsigned int     reg_aux_entst:1;
unsigned int     reg_en_aux_psm:1;
unsigned int     reg_en_aux_rx_bigz0_p:1;
}AUX_2;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     reg_en_aux_psm_bias:1;
unsigned int     reg_aux_tst:6;
unsigned int     reg_aux_z0_ok:1;
}AUX_3;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     reg_aux_rev76:2;
unsigned int     reg_aux_rev52:4;
unsigned int     reg_aux_rev1:1;
unsigned int     reg_aux_rev0:1;
}AUX_4;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     reg_aux_rstb:1;
unsigned int     reg_dda_40u_d2:1;
unsigned int     reg_dda_psm_40u_d2:1;
unsigned int     Reserved:5;
}AUX_5;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Reserved:2;
unsigned int     reg_aux_din_sel:1;
unsigned int     reg_en_aux_rx_bigz0_n:1;
unsigned int     reg_aux_rx_adjr_n:4;
}AUX_6;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     reg_aux_tx_adjr_p:4;
unsigned int     reg_aux_tx_adjr_n:4;
}DIG_TX_03;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Reserved:7;
unsigned int     aux_en:1;
}AUX_TX_CTRL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     aux_timeout_en:1;
unsigned int     aux_timeout_num:7;
}AUX_TIMEOUT;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     debug_sel20:3;
unsigned int     fsm_work:1;
unsigned int     auxch_fsm:4;
}AUX_FSM_STATUS;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     tx_addronly:1;
unsigned int     aux_phy_wake_en:1;
unsigned int     aux_fw_handle:1;
unsigned int     Reserved:4;
unsigned int     tx_start:1;
}AUXTX_TRAN_CTRL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     tx_cmd:4;
unsigned int     tx_addr1916:4;
}AUXTX_REQ_CMD;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     tx_addr158:8;
}AUXTX_REQ_ADDR_M;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     tx_addr70:8;
}AUXTX_REQ_ADDR_L;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Reserved:4;
unsigned int     tx_len:4;
}AUXTX_REQ_LEN;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     tx_data:8;
}AUXTX_REQ_DATA;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     aux_rx_cmd:4;
unsigned int     aux_rx_len:4;
}AUX_REPLY_CMD;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     aux_reply_data:8;
}AUX_REPLY_DATA;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Reserved:3;
unsigned int     i2c_req_len_sel:1;
unsigned int     readfail_auto_en:1;
unsigned int     force_req_intval:1;
unsigned int     i2c_fifo_rst:1;
unsigned int     na_fifo_rst:1;
}AUX_FIFO_CTRL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     aux_fifo_full:1;
unsigned int     aux_fifo_empty:1;
unsigned int     Reserved:2;
unsigned int     na_fifo_ovf:1;
unsigned int     na_fifo_udf:1;
unsigned int     i2c_fifo_ovf:1;
unsigned int     i2c_fifo_udf:1;
}AUX_TX_FIFO_STATUS;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Reserved:3;
unsigned int     rd_ptr:5;
}AUX_FIFO_RD_PTR;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Reserved:3;
unsigned int     wr_ptr:5;
}AUX_FIFO_WR_PTR;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Reserved:2;
unsigned int     retry_work:1;
unsigned int     retry_lock:1;
unsigned int     retry_num:4;
}AUX_RETRY_1;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     retry_en:1;
unsigned int     retry_defer_en:1;
unsigned int     retry_timeout_en:1;
unsigned int     retry_nack_en:1;
unsigned int     retry_error_en:1;
unsigned int     Reserved:3;
}AUX_RETRY_2;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Reserved:1;
unsigned int     alpm_fail_irq:1;
unsigned int     auxdone_irq:1;
unsigned int     rxerror_irq:1;
unsigned int     readfail_irq:1;
unsigned int     nack_irq:1;
unsigned int     retry_irq:1;
unsigned int     timeout_irq:1;
}AUX_IRQ_EVENT;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Reserved:1;
unsigned int     alpm_irq_en:1;
unsigned int     auxdone_irq_en:1;
unsigned int     rxerror_irq_en:1;
unsigned int     readfail_irq_en:1;
unsigned int     nack_irq_en:1;
unsigned int     retry_irq_en:1;
unsigned int     timeout_irq_en:1;
}AUX_IRQ_EN;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     ave_pos:5;
unsigned int     aux_50duty_control:1;
unsigned int     rsv_aux_dig_phy2:1;
unsigned int     aux_pn_swap:1;
}AUX_DIG_PHY2;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     aux_clksel_auto_en:1;
unsigned int     Reserved:7;
}AUX_DIG_PHY3;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Reserved:3;
unsigned int     pcharge_num:5;
}AUX_DIG_PHY4;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     ave_man_en:1;
unsigned int     ave_num:7;
}AUX_DIG_PHY5;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     tx_clk1m_factor:8;
}AUX_DIG_PHY6;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     aux_phy_int_en:1;
unsigned int     aux_phy_int:1;
unsigned int     Reserved:6;
}AUX_DIG_PHY7;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Reserved:2;
unsigned int     error_handle:1;
unsigned int     sync1_wo_idle:1;
unsigned int     ehandle_man_dis:1;
unsigned int     ehandle_stop_dis:1;
unsigned int     ehandle_syncend_dis:1;
unsigned int     ehandle_8x_dis:1;
}AUX_DIG_PHY8;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     single_end_mode:1;
unsigned int     Reserved:3;
unsigned int     man_error:1;
unsigned int     stop_error:1;
unsigned int     syncend_error:1;
unsigned int     data_8x_error:1;
}AUX_DIG_PHY9;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     aux_d1:1;
unsigned int     aux_d2:1;
unsigned int     Reserved:3;
unsigned int     fsm_state:3;
}AUX_DEBUG;

#endif

#define DP_MAC_CTRL                                                                  0x9803D280
#define DP_MAC_CTRL_reg_addr                                                         "0x9803D280"
#define DP_MAC_CTRL_reg                                                              0x9803D280
#define set_DP_MAC_CTRL_reg(data)   (*((volatile unsigned int*) DP_MAC_CTRL_reg)=data)
#define get_DP_MAC_CTRL_reg   (*((volatile unsigned int*) DP_MAC_CTRL_reg))
#define DP_MAC_CTRL_inst_adr                                                         "0x00A0"
#define DP_MAC_CTRL_inst                                                             0x00A0
#define DP_MAC_CTRL_Reserved_shift                                                   (3)
#define DP_MAC_CTRL_Reserved_mask                                                    (0x000000F8)
#define DP_MAC_CTRL_Reserved(data)                                                   (0x000000F8&((data)<<3))
#define DP_MAC_CTRL_Reserved_src(data)                                               ((0x000000F8&(data))>>3)
#define DP_MAC_CTRL_get_Reserved(data)                                               ((0x000000F8&(data))>>3)
#define DP_MAC_CTRL_enhance_md_shift                                                 (2)
#define DP_MAC_CTRL_enhance_md_mask                                                  (0x00000004)
#define DP_MAC_CTRL_enhance_md(data)                                                 (0x00000004&((data)<<2))
#define DP_MAC_CTRL_enhance_md_src(data)                                             ((0x00000004&(data))>>2)
#define DP_MAC_CTRL_get_enhance_md(data)                                             ((0x00000004&(data))>>2)
#define DP_MAC_CTRL_lane_num_shift                                                   (0)
#define DP_MAC_CTRL_lane_num_mask                                                    (0x00000003)
#define DP_MAC_CTRL_lane_num(data)                                                   (0x00000003&((data)<<0))
#define DP_MAC_CTRL_lane_num_src(data)                                               ((0x00000003&(data))>>0)
#define DP_MAC_CTRL_get_lane_num(data)                                               ((0x00000003&(data))>>0)


#define DP_RESET_CTRL                                                                0x9803D284
#define DP_RESET_CTRL_reg_addr                                                       "0x9803D284"
#define DP_RESET_CTRL_reg                                                            0x9803D284
#define set_DP_RESET_CTRL_reg(data)   (*((volatile unsigned int*) DP_RESET_CTRL_reg)=data)
#define get_DP_RESET_CTRL_reg   (*((volatile unsigned int*) DP_RESET_CTRL_reg))
#define DP_RESET_CTRL_inst_adr                                                       "0x00A1"
#define DP_RESET_CTRL_inst                                                           0x00A1
#define DP_RESET_CTRL_pg_reset_shift                                                 (7)
#define DP_RESET_CTRL_pg_reset_mask                                                  (0x00000080)
#define DP_RESET_CTRL_pg_reset(data)                                                 (0x00000080&((data)<<7))
#define DP_RESET_CTRL_pg_reset_src(data)                                             ((0x00000080&(data))>>7)
#define DP_RESET_CTRL_get_pg_reset(data)                                             ((0x00000080&(data))>>7)
#define DP_RESET_CTRL_msa_reset_shift                                                (6)
#define DP_RESET_CTRL_msa_reset_mask                                                 (0x00000040)
#define DP_RESET_CTRL_msa_reset(data)                                                (0x00000040&((data)<<6))
#define DP_RESET_CTRL_msa_reset_src(data)                                            ((0x00000040&(data))>>6)
#define DP_RESET_CTRL_get_msa_reset(data)                                            ((0x00000040&(data))>>6)
#define DP_RESET_CTRL_aux_reset_shift                                                (5)
#define DP_RESET_CTRL_aux_reset_mask                                                 (0x00000020)
#define DP_RESET_CTRL_aux_reset(data)                                                (0x00000020&((data)<<5))
#define DP_RESET_CTRL_aux_reset_src(data)                                            ((0x00000020&(data))>>5)
#define DP_RESET_CTRL_get_aux_reset(data)                                            ((0x00000020&(data))>>5)
#define DP_RESET_CTRL_clk_gen_reset_shift                                            (4)
#define DP_RESET_CTRL_clk_gen_reset_mask                                             (0x00000010)
#define DP_RESET_CTRL_clk_gen_reset(data)                                            (0x00000010&((data)<<4))
#define DP_RESET_CTRL_clk_gen_reset_src(data)                                        ((0x00000010&(data))>>4)
#define DP_RESET_CTRL_get_clk_gen_reset(data)                                        ((0x00000010&(data))>>4)
#define DP_RESET_CTRL_measure_reset_shift                                            (3)
#define DP_RESET_CTRL_measure_reset_mask                                             (0x00000008)
#define DP_RESET_CTRL_measure_reset(data)                                            (0x00000008&((data)<<3))
#define DP_RESET_CTRL_measure_reset_src(data)                                        ((0x00000008&(data))>>3)
#define DP_RESET_CTRL_get_measure_reset(data)                                        ((0x00000008&(data))>>3)
#define DP_RESET_CTRL_Reserved_shift                                                 (0)
#define DP_RESET_CTRL_Reserved_mask                                                  (0x00000007)
#define DP_RESET_CTRL_Reserved(data)                                                 (0x00000007&((data)<<0))
#define DP_RESET_CTRL_Reserved_src(data)                                             ((0x00000007&(data))>>0)
#define DP_RESET_CTRL_get_Reserved(data)                                             ((0x00000007&(data))>>0)


#define DP_DEBUG_CTRL                                                                0x9803D288
#define DP_DEBUG_CTRL_reg_addr                                                       "0x9803D288"
#define DP_DEBUG_CTRL_reg                                                            0x9803D288
#define set_DP_DEBUG_CTRL_reg(data)   (*((volatile unsigned int*) DP_DEBUG_CTRL_reg)=data)
#define get_DP_DEBUG_CTRL_reg   (*((volatile unsigned int*) DP_DEBUG_CTRL_reg))
#define DP_DEBUG_CTRL_inst_adr                                                       "0x00A2"
#define DP_DEBUG_CTRL_inst                                                           0x00A2
#define DP_DEBUG_CTRL_Reserved_shift                                                 (6)
#define DP_DEBUG_CTRL_Reserved_mask                                                  (0x000000C0)
#define DP_DEBUG_CTRL_Reserved(data)                                                 (0x000000C0&((data)<<6))
#define DP_DEBUG_CTRL_Reserved_src(data)                                             ((0x000000C0&(data))>>6)
#define DP_DEBUG_CTRL_get_Reserved(data)                                             ((0x000000C0&(data))>>6)
#define DP_DEBUG_CTRL_dptx_arb_debug_sel_shift                                       (4)
#define DP_DEBUG_CTRL_dptx_arb_debug_sel_mask                                        (0x00000030)
#define DP_DEBUG_CTRL_dptx_arb_debug_sel(data)                                       (0x00000030&((data)<<4))
#define DP_DEBUG_CTRL_dptx_arb_debug_sel_src(data)                                   ((0x00000030&(data))>>4)
#define DP_DEBUG_CTRL_get_dptx_arb_debug_sel(data)                                   ((0x00000030&(data))>>4)
#define DP_DEBUG_CTRL_dptx_debug_sel_shift                                           (0)
#define DP_DEBUG_CTRL_dptx_debug_sel_mask                                            (0x0000000F)
#define DP_DEBUG_CTRL_dptx_debug_sel(data)                                           (0x0000000F&((data)<<0))
#define DP_DEBUG_CTRL_dptx_debug_sel_src(data)                                       ((0x0000000F&(data))>>0)
#define DP_DEBUG_CTRL_get_dptx_debug_sel(data)                                       ((0x0000000F&(data))>>0)


#define DPTX_IRQ_CTRL                                                                0x9803D28C
#define DPTX_IRQ_CTRL_reg_addr                                                       "0x9803D28C"
#define DPTX_IRQ_CTRL_reg                                                            0x9803D28C
#define set_DPTX_IRQ_CTRL_reg(data)   (*((volatile unsigned int*) DPTX_IRQ_CTRL_reg)=data)
#define get_DPTX_IRQ_CTRL_reg   (*((volatile unsigned int*) DPTX_IRQ_CTRL_reg))
#define DPTX_IRQ_CTRL_inst_adr                                                       "0x00A3"
#define DPTX_IRQ_CTRL_inst                                                           0x00A3
#define DPTX_IRQ_CTRL_dptx_irq_en_shift                                              (7)
#define DPTX_IRQ_CTRL_dptx_irq_en_mask                                               (0x00000080)
#define DPTX_IRQ_CTRL_dptx_irq_en(data)                                              (0x00000080&((data)<<7))
#define DPTX_IRQ_CTRL_dptx_irq_en_src(data)                                          ((0x00000080&(data))>>7)
#define DPTX_IRQ_CTRL_get_dptx_irq_en(data)                                          ((0x00000080&(data))>>7)
#define DPTX_IRQ_CTRL_Reserved_shift                                                 (1)
#define DPTX_IRQ_CTRL_Reserved_mask                                                  (0x0000007E)
#define DPTX_IRQ_CTRL_Reserved(data)                                                 (0x0000007E&((data)<<1))
#define DPTX_IRQ_CTRL_Reserved_src(data)                                             ((0x0000007E&(data))>>1)
#define DPTX_IRQ_CTRL_get_Reserved(data)                                             ((0x0000007E&(data))>>1)
#define DPTX_IRQ_CTRL_dptx_irq_shift                                                 (0)
#define DPTX_IRQ_CTRL_dptx_irq_mask                                                  (0x00000001)
#define DPTX_IRQ_CTRL_dptx_irq(data)                                                 (0x00000001&((data)<<0))
#define DPTX_IRQ_CTRL_dptx_irq_src(data)                                             ((0x00000001&(data))>>0)
#define DPTX_IRQ_CTRL_get_dptx_irq(data)                                             ((0x00000001&(data))>>0)


#define PG_FIFO_CTRL                                                                 0x9803D290
#define PG_FIFO_CTRL_reg_addr                                                        "0x9803D290"
#define PG_FIFO_CTRL_reg                                                             0x9803D290
#define set_PG_FIFO_CTRL_reg(data)   (*((volatile unsigned int*) PG_FIFO_CTRL_reg)=data)
#define get_PG_FIFO_CTRL_reg   (*((volatile unsigned int*) PG_FIFO_CTRL_reg))
#define PG_FIFO_CTRL_inst_adr                                                        "0x00A4"
#define PG_FIFO_CTRL_inst                                                            0x00A4
#define PG_FIFO_CTRL_lfifo_full_shift                                                (7)
#define PG_FIFO_CTRL_lfifo_full_mask                                                 (0x00000080)
#define PG_FIFO_CTRL_lfifo_full(data)                                                (0x00000080&((data)<<7))
#define PG_FIFO_CTRL_lfifo_full_src(data)                                            ((0x00000080&(data))>>7)
#define PG_FIFO_CTRL_get_lfifo_full(data)                                            ((0x00000080&(data))>>7)
#define PG_FIFO_CTRL_lfifo_udf_shift                                                 (6)
#define PG_FIFO_CTRL_lfifo_udf_mask                                                  (0x00000040)
#define PG_FIFO_CTRL_lfifo_udf(data)                                                 (0x00000040&((data)<<6))
#define PG_FIFO_CTRL_lfifo_udf_src(data)                                             ((0x00000040&(data))>>6)
#define PG_FIFO_CTRL_get_lfifo_udf(data)                                             ((0x00000040&(data))>>6)
#define PG_FIFO_CTRL_lfifo_udf_uni_shift                                             (5)
#define PG_FIFO_CTRL_lfifo_udf_uni_mask                                              (0x00000020)
#define PG_FIFO_CTRL_lfifo_udf_uni(data)                                             (0x00000020&((data)<<5))
#define PG_FIFO_CTRL_lfifo_udf_uni_src(data)                                         ((0x00000020&(data))>>5)
#define PG_FIFO_CTRL_get_lfifo_udf_uni(data)                                         ((0x00000020&(data))>>5)
#define PG_FIFO_CTRL_sfifo_ful_shift                                                 (4)
#define PG_FIFO_CTRL_sfifo_ful_mask                                                  (0x00000010)
#define PG_FIFO_CTRL_sfifo_ful(data)                                                 (0x00000010&((data)<<4))
#define PG_FIFO_CTRL_sfifo_ful_src(data)                                             ((0x00000010&(data))>>4)
#define PG_FIFO_CTRL_get_sfifo_ful(data)                                             ((0x00000010&(data))>>4)
#define PG_FIFO_CTRL_sfifo_ove_shift                                                 (3)
#define PG_FIFO_CTRL_sfifo_ove_mask                                                  (0x00000008)
#define PG_FIFO_CTRL_sfifo_ove(data)                                                 (0x00000008&((data)<<3))
#define PG_FIFO_CTRL_sfifo_ove_src(data)                                             ((0x00000008&(data))>>3)
#define PG_FIFO_CTRL_get_sfifo_ove(data)                                             ((0x00000008&(data))>>3)
#define PG_FIFO_CTRL_sfifo_ove_uni_shift                                             (2)
#define PG_FIFO_CTRL_sfifo_ove_uni_mask                                              (0x00000004)
#define PG_FIFO_CTRL_sfifo_ove_uni(data)                                             (0x00000004&((data)<<2))
#define PG_FIFO_CTRL_sfifo_ove_uni_src(data)                                         ((0x00000004&(data))>>2)
#define PG_FIFO_CTRL_get_sfifo_ove_uni(data)                                         ((0x00000004&(data))>>2)
#define PG_FIFO_CTRL_lfifo_maxwl_clear_shift                                         (1)
#define PG_FIFO_CTRL_lfifo_maxwl_clear_mask                                          (0x00000002)
#define PG_FIFO_CTRL_lfifo_maxwl_clear(data)                                         (0x00000002&((data)<<1))
#define PG_FIFO_CTRL_lfifo_maxwl_clear_src(data)                                     ((0x00000002&(data))>>1)
#define PG_FIFO_CTRL_get_lfifo_maxwl_clear(data)                                     ((0x00000002&(data))>>1)
#define PG_FIFO_CTRL_Reserved_shift                                                  (0)
#define PG_FIFO_CTRL_Reserved_mask                                                   (0x00000001)
#define PG_FIFO_CTRL_Reserved(data)                                                  (0x00000001&((data)<<0))
#define PG_FIFO_CTRL_Reserved_src(data)                                              ((0x00000001&(data))>>0)
#define PG_FIFO_CTRL_get_Reserved(data)                                              ((0x00000001&(data))>>0)


#define MAX_WL                                                                       0x9803D294
#define MAX_WL_reg_addr                                                              "0x9803D294"
#define MAX_WL_reg                                                                   0x9803D294
#define set_MAX_WL_reg(data)   (*((volatile unsigned int*) MAX_WL_reg)=data)
#define get_MAX_WL_reg   (*((volatile unsigned int*) MAX_WL_reg))
#define MAX_WL_inst_adr                                                              "0x00A5"
#define MAX_WL_inst                                                                  0x00A5
#define MAX_WL_max_wl_shift                                                          (0)
#define MAX_WL_max_wl_mask                                                           (0x000000FF)
#define MAX_WL_max_wl(data)                                                          (0x000000FF&((data)<<0))
#define MAX_WL_max_wl_src(data)                                                      ((0x000000FF&(data))>>0)
#define MAX_WL_get_max_wl(data)                                                      ((0x000000FF&(data))>>0)


#define LFIFO_WL                                                                     0x9803D298
#define LFIFO_WL_reg_addr                                                            "0x9803D298"
#define LFIFO_WL_reg                                                                 0x9803D298
#define set_LFIFO_WL_reg(data)   (*((volatile unsigned int*) LFIFO_WL_reg)=data)
#define get_LFIFO_WL_reg   (*((volatile unsigned int*) LFIFO_WL_reg))
#define LFIFO_WL_inst_adr                                                            "0x00A6"
#define LFIFO_WL_inst                                                                0x00A6
#define LFIFO_WL_lfifo_wl_shift                                                      (0)
#define LFIFO_WL_lfifo_wl_mask                                                       (0x000000FF)
#define LFIFO_WL_lfifo_wl(data)                                                      (0x000000FF&((data)<<0))
#define LFIFO_WL_lfifo_wl_src(data)                                                  ((0x000000FF&(data))>>0)
#define LFIFO_WL_get_lfifo_wl(data)                                                  ((0x000000FF&(data))>>0)


#define LFIFO_WL_INT                                                                 0x9803D29C
#define LFIFO_WL_INT_reg_addr                                                            "0x9803D29C"
#define LFIFO_WL_INT_reg                                                                 0x9803D29C
#define set_LFIFO_WL_INT_reg(data)   (*((volatile unsigned int*) LFIFO_WL_reg)=data)
#define get_LFIFO_WL_INT_reg   (*((volatile unsigned int*) LFIFO_WL_reg))
#define LFIFO_WL_INT_inst_adr                                                            "0x00A7"
#define LFIFO_WL_INT_inst                                                                0x00A7
#define LFIFO_WL_Reserved_shift                                                      (2)
#define LFIFO_WL_Reserved_mask                                                       (0x000000FC)
#define LFIFO_WL_Reserved(data)                                                      (0x000000FC&((data)<<2))
#define LFIFO_WL_Reserved_src(data)                                                  ((0x000000FC&(data))>>2)
#define LFIFO_WL_get_Reserved(data)                                                  ((0x000000FC&(data))>>2)
#define LFIFO_WL_lfifo_udf_int_en_shift                                              (1)
#define LFIFO_WL_lfifo_udf_int_en_mask                                               (0x00000002)
#define LFIFO_WL_lfifo_udf_int_en(data)                                              (0x00000002&((data)<<1))
#define LFIFO_WL_lfifo_udf_int_en_src(data)                                          ((0x00000002&(data))>>1)
#define LFIFO_WL_get_lfifo_udf_int_en(data)                                          ((0x00000002&(data))>>1)
#define LFIFO_WL_sfifo_ove_int_en_shift                                              (0)
#define LFIFO_WL_sfifo_ove_int_en_mask                                               (0x00000001)
#define LFIFO_WL_sfifo_ove_int_en(data)                                              (0x00000001&((data)<<0))
#define LFIFO_WL_sfifo_ove_int_en_src(data)                                          ((0x00000001&(data))>>0)
#define LFIFO_WL_get_sfifo_ove_int_en(data)                                          ((0x00000001&(data))>>0)


#define MN_VID_AUTO_EN_1                                                             0x9803D2A0
#define MN_VID_AUTO_EN_1_reg_addr                                                    "0x9803D2A0"
#define MN_VID_AUTO_EN_1_reg                                                         0x9803D2A0
#define set_MN_VID_AUTO_EN_1_reg(data)   (*((volatile unsigned int*) MN_VID_AUTO_EN_1_reg)=data)
#define get_MN_VID_AUTO_EN_1_reg   (*((volatile unsigned int*) MN_VID_AUTO_EN_1_reg))
#define MN_VID_AUTO_EN_1_inst_adr                                                    "0x00A8"
#define MN_VID_AUTO_EN_1_inst                                                        0x00A8
#define MN_VID_AUTO_EN_1_mn_vid_auto_en_shift                                        (7)
#define MN_VID_AUTO_EN_1_mn_vid_auto_en_mask                                         (0x00000080)
#define MN_VID_AUTO_EN_1_mn_vid_auto_en(data)                                        (0x00000080&((data)<<7))
#define MN_VID_AUTO_EN_1_mn_vid_auto_en_src(data)                                    ((0x00000080&(data))>>7)
#define MN_VID_AUTO_EN_1_get_mn_vid_auto_en(data)                                    ((0x00000080&(data))>>7)
#define MN_VID_AUTO_EN_1_mn_vid_db_shift                                             (6)
#define MN_VID_AUTO_EN_1_mn_vid_db_mask                                              (0x00000040)
#define MN_VID_AUTO_EN_1_mn_vid_db(data)                                             (0x00000040&((data)<<6))
#define MN_VID_AUTO_EN_1_mn_vid_db_src(data)                                         ((0x00000040&(data))>>6)
#define MN_VID_AUTO_EN_1_get_mn_vid_db(data)                                         ((0x00000040&(data))>>6)
#define MN_VID_AUTO_EN_1_Reserved_shift                                              (0)
#define MN_VID_AUTO_EN_1_Reserved_mask                                               (0x0000003F)
#define MN_VID_AUTO_EN_1_Reserved(data)                                              (0x0000003F&((data)<<0))
#define MN_VID_AUTO_EN_1_Reserved_src(data)                                          ((0x0000003F&(data))>>0)
#define MN_VID_AUTO_EN_1_get_Reserved(data)                                          ((0x0000003F&(data))>>0)


#define MN_M_VID_H                                                                   0x9803D2A4
#define MN_M_VID_H_reg_addr                                                          "0x9803D2A4"
#define MN_M_VID_H_reg                                                               0x9803D2A4
#define set_MN_M_VID_H_reg(data)   (*((volatile unsigned int*) MN_M_VID_H_reg)=data)
#define get_MN_M_VID_H_reg   (*((volatile unsigned int*) MN_M_VID_H_reg))
#define MN_M_VID_H_inst_adr                                                          "0x00A9"
#define MN_M_VID_H_inst                                                              0x00A9
#define MN_M_VID_H_mvid2316_shift                                                    (0)
#define MN_M_VID_H_mvid2316_mask                                                     (0x000000FF)
#define MN_M_VID_H_mvid2316(data)                                                    (0x000000FF&((data)<<0))
#define MN_M_VID_H_mvid2316_src(data)                                                ((0x000000FF&(data))>>0)
#define MN_M_VID_H_get_mvid2316(data)                                                ((0x000000FF&(data))>>0)


#define MN_M_VID_M                                                                   0x9803D2A8
#define MN_M_VID_M_reg_addr                                                          "0x9803D2A8"
#define MN_M_VID_M_reg                                                               0x9803D2A8
#define set_MN_M_VID_M_reg(data)   (*((volatile unsigned int*) MN_M_VID_M_reg)=data)
#define get_MN_M_VID_M_reg   (*((volatile unsigned int*) MN_M_VID_M_reg))
#define MN_M_VID_M_inst_adr                                                          "0x00AA"
#define MN_M_VID_M_inst                                                              0x00AA
#define MN_M_VID_M_mvid158_shift                                                     (0)
#define MN_M_VID_M_mvid158_mask                                                      (0x000000FF)
#define MN_M_VID_M_mvid158(data)                                                     (0x000000FF&((data)<<0))
#define MN_M_VID_M_mvid158_src(data)                                                 ((0x000000FF&(data))>>0)
#define MN_M_VID_M_get_mvid158(data)                                                 ((0x000000FF&(data))>>0)


#define MN_M_VID_L                                                                   0x9803D2AC
#define MN_M_VID_L_reg_addr                                                          "0x9803D2AC"
#define MN_M_VID_L_reg                                                               0x9803D2AC
#define set_MN_M_VID_L_reg(data)   (*((volatile unsigned int*) MN_M_VID_L_reg)=data)
#define get_MN_M_VID_L_reg   (*((volatile unsigned int*) MN_M_VID_L_reg))
#define MN_M_VID_L_inst_adr                                                          "0x00AB"
#define MN_M_VID_L_inst                                                              0x00AB
#define MN_M_VID_L_mvid70_shift                                                      (0)
#define MN_M_VID_L_mvid70_mask                                                       (0x000000FF)
#define MN_M_VID_L_mvid70(data)                                                      (0x000000FF&((data)<<0))
#define MN_M_VID_L_mvid70_src(data)                                                  ((0x000000FF&(data))>>0)
#define MN_M_VID_L_get_mvid70(data)                                                  ((0x000000FF&(data))>>0)


#define MN_N_VID_H                                                                   0x9803D2B0
#define MN_N_VID_H_reg_addr                                                          "0x9803D2B0"
#define MN_N_VID_H_reg                                                               0x9803D2B0
#define set_MN_N_VID_H_reg(data)   (*((volatile unsigned int*) MN_N_VID_H_reg)=data)
#define get_MN_N_VID_H_reg   (*((volatile unsigned int*) MN_N_VID_H_reg))
#define MN_N_VID_H_inst_adr                                                          "0x00AC"
#define MN_N_VID_H_inst                                                              0x00AC
#define MN_N_VID_H_nvid2316_shift                                                    (0)
#define MN_N_VID_H_nvid2316_mask                                                     (0x000000FF)
#define MN_N_VID_H_nvid2316(data)                                                    (0x000000FF&((data)<<0))
#define MN_N_VID_H_nvid2316_src(data)                                                ((0x000000FF&(data))>>0)
#define MN_N_VID_H_get_nvid2316(data)                                                ((0x000000FF&(data))>>0)


#define MN_N_VID_M                                                                   0x9803D2B4
#define MN_N_VID_M_reg_addr                                                          "0x9803D2B4"
#define MN_N_VID_M_reg                                                               0x9803D2B4
#define set_MN_N_VID_M_reg(data)   (*((volatile unsigned int*) MN_N_VID_M_reg)=data)
#define get_MN_N_VID_M_reg   (*((volatile unsigned int*) MN_N_VID_M_reg))
#define MN_N_VID_M_inst_adr                                                          "0x00AD"
#define MN_N_VID_M_inst                                                              0x00AD
#define MN_N_VID_M_nvid158_shift                                                     (0)
#define MN_N_VID_M_nvid158_mask                                                      (0x000000FF)
#define MN_N_VID_M_nvid158(data)                                                     (0x000000FF&((data)<<0))
#define MN_N_VID_M_nvid158_src(data)                                                 ((0x000000FF&(data))>>0)
#define MN_N_VID_M_get_nvid158(data)                                                 ((0x000000FF&(data))>>0)


#define MN_N_VID_L                                                                   0x9803D2B8
#define MN_N_VID_L_reg_addr                                                          "0x9803D2B8"
#define MN_N_VID_L_reg                                                               0x9803D2B8
#define set_MN_N_VID_L_reg(data)   (*((volatile unsigned int*) MN_N_VID_L_reg)=data)
#define get_MN_N_VID_L_reg   (*((volatile unsigned int*) MN_N_VID_L_reg))
#define MN_N_VID_L_inst_adr                                                          "0x00AE"
#define MN_N_VID_L_inst                                                              0x00AE
#define MN_N_VID_L_nvid70_shift                                                      (0)
#define MN_N_VID_L_nvid70_mask                                                       (0x000000FF)
#define MN_N_VID_L_nvid70(data)                                                      (0x000000FF&((data)<<0))
#define MN_N_VID_L_nvid70_src(data)                                                  ((0x000000FF&(data))>>0)
#define MN_N_VID_L_get_nvid70(data)                                                  ((0x000000FF&(data))>>0)


#define MVID_AUTO_H                                                                  0x9803D2BC
#define MVID_AUTO_H_reg_addr                                                         "0x9803D2BC"
#define MVID_AUTO_H_reg                                                              0x9803D2BC
#define set_MVID_AUTO_H_reg(data)   (*((volatile unsigned int*) MVID_AUTO_H_reg)=data)
#define get_MVID_AUTO_H_reg   (*((volatile unsigned int*) MVID_AUTO_H_reg))
#define MVID_AUTO_H_inst_adr                                                         "0x00AF"
#define MVID_AUTO_H_inst                                                             0x00AF
#define MVID_AUTO_H_mvid_auto2316_shift                                              (0)
#define MVID_AUTO_H_mvid_auto2316_mask                                               (0x000000FF)
#define MVID_AUTO_H_mvid_auto2316(data)                                              (0x000000FF&((data)<<0))
#define MVID_AUTO_H_mvid_auto2316_src(data)                                          ((0x000000FF&(data))>>0)
#define MVID_AUTO_H_get_mvid_auto2316(data)                                          ((0x000000FF&(data))>>0)


#define MVID_AUTO_M                                                                  0x9803D2C0
#define MVID_AUTO_M_reg_addr                                                         "0x9803D2C0"
#define MVID_AUTO_M_reg                                                              0x9803D2C0
#define set_MVID_AUTO_M_reg(data)   (*((volatile unsigned int*) MVID_AUTO_M_reg)=data)
#define get_MVID_AUTO_M_reg   (*((volatile unsigned int*) MVID_AUTO_M_reg))
#define MVID_AUTO_M_inst_adr                                                         "0x00B0"
#define MVID_AUTO_M_inst                                                             0x00B0
#define MVID_AUTO_M_mvid_auto158_shift                                               (0)
#define MVID_AUTO_M_mvid_auto158_mask                                                (0x000000FF)
#define MVID_AUTO_M_mvid_auto158(data)                                               (0x000000FF&((data)<<0))
#define MVID_AUTO_M_mvid_auto158_src(data)                                           ((0x000000FF&(data))>>0)
#define MVID_AUTO_M_get_mvid_auto158(data)                                           ((0x000000FF&(data))>>0)


#define MVID_AUTO_L                                                                  0x9803D2C4
#define MVID_AUTO_L_reg_addr                                                         "0x9803D2C4"
#define MVID_AUTO_L_reg                                                              0x9803D2C4
#define set_MVID_AUTO_L_reg(data)   (*((volatile unsigned int*) MVID_AUTO_L_reg)=data)
#define get_MVID_AUTO_L_reg   (*((volatile unsigned int*) MVID_AUTO_L_reg))
#define MVID_AUTO_L_inst_adr                                                         "0x00B1"
#define MVID_AUTO_L_inst                                                             0x00B1
#define MVID_AUTO_L_mvid_auto70_shift                                                (0)
#define MVID_AUTO_L_mvid_auto70_mask                                                 (0x000000FF)
#define MVID_AUTO_L_mvid_auto70(data)                                                (0x000000FF&((data)<<0))
#define MVID_AUTO_L_mvid_auto70_src(data)                                            ((0x000000FF&(data))>>0)
#define MVID_AUTO_L_get_mvid_auto70(data)                                            ((0x000000FF&(data))>>0)


#define NVID_ASYNC_M                                                                 0x9803D2C8
#define NVID_ASYNC_M_reg_addr                                                        "0x9803D2C8"
#define NVID_ASYNC_M_reg                                                             0x9803D2C8
#define set_NVID_ASYNC_M_reg(data)   (*((volatile unsigned int*) NVID_ASYNC_M_reg)=data)
#define get_NVID_ASYNC_M_reg   (*((volatile unsigned int*) NVID_ASYNC_M_reg))
#define NVID_ASYNC_M_inst_adr                                                        "0x00B2"
#define NVID_ASYNC_M_inst                                                            0x00B2
#define NVID_ASYNC_M_nvid_async158_shift                                             (0)
#define NVID_ASYNC_M_nvid_async158_mask                                              (0x000000FF)
#define NVID_ASYNC_M_nvid_async158(data)                                             (0x000000FF&((data)<<0))
#define NVID_ASYNC_M_nvid_async158_src(data)                                         ((0x000000FF&(data))>>0)
#define NVID_ASYNC_M_get_nvid_async158(data)                                         ((0x000000FF&(data))>>0)


#define NVID_ASYNC_L                                                                 0x9803D2CC
#define NVID_ASYNC_L_reg_addr                                                        "0x9803D2CC"
#define NVID_ASYNC_L_reg                                                             0x9803D2CC
#define set_NVID_ASYNC_L_reg(data)   (*((volatile unsigned int*) NVID_ASYNC_L_reg)=data)
#define get_NVID_ASYNC_L_reg   (*((volatile unsigned int*) NVID_ASYNC_L_reg))
#define NVID_ASYNC_L_inst_adr                                                        "0x00B3"
#define NVID_ASYNC_L_inst                                                            0x00B3
#define NVID_ASYNC_L_nvid_async70_shift                                              (0)
#define NVID_ASYNC_L_nvid_async70_mask                                               (0x000000FF)
#define NVID_ASYNC_L_nvid_async70(data)                                              (0x000000FF&((data)<<0))
#define NVID_ASYNC_L_nvid_async70_src(data)                                          ((0x000000FF&(data))>>0)
#define NVID_ASYNC_L_get_nvid_async70(data)                                          ((0x000000FF&(data))>>0)


#define MSA_CTRL                                                                     0x9803D2D0
#define MSA_CTRL_reg_addr                                                            "0x9803D2D0"
#define MSA_CTRL_reg                                                                 0x9803D2D0
#define set_MSA_CTRL_reg(data)   (*((volatile unsigned int*) MSA_CTRL_reg)=data)
#define get_MSA_CTRL_reg   (*((volatile unsigned int*) MSA_CTRL_reg))
#define MSA_CTRL_inst_adr                                                            "0x00B4"
#define MSA_CTRL_inst                                                                0x00B4
#define MSA_CTRL_msa_db_shift                                                        (7)
#define MSA_CTRL_msa_db_mask                                                         (0x00000080)
#define MSA_CTRL_msa_db(data)                                                        (0x00000080&((data)<<7))
#define MSA_CTRL_msa_db_src(data)                                                    ((0x00000080&(data))>>7)
#define MSA_CTRL_get_msa_db(data)                                                    ((0x00000080&(data))>>7)
#define MSA_CTRL_msa_db_vblank_shift                                                 (6)
#define MSA_CTRL_msa_db_vblank_mask                                                  (0x00000040)
#define MSA_CTRL_msa_db_vblank(data)                                                 (0x00000040&((data)<<6))
#define MSA_CTRL_msa_db_vblank_src(data)                                             ((0x00000040&(data))>>6)
#define MSA_CTRL_get_msa_db_vblank(data)                                             ((0x00000040&(data))>>6)
#define MSA_CTRL_Reserved_shift                                                      (0)
#define MSA_CTRL_Reserved_mask                                                       (0x0000003F)
#define MSA_CTRL_Reserved(data)                                                      (0x0000003F&((data)<<0))
#define MSA_CTRL_Reserved_src(data)                                                  ((0x0000003F&(data))>>0)
#define MSA_CTRL_get_Reserved(data)                                                  ((0x0000003F&(data))>>0)


#define MSA_MISC0                                                                    0x9803D2D4
#define MSA_MISC0_reg_addr                                                           "0x9803D2D4"
#define MSA_MISC0_reg                                                                0x9803D2D4
#define set_MSA_MISC0_reg(data)   (*((volatile unsigned int*) MSA_MISC0_reg)=data)
#define get_MSA_MISC0_reg   (*((volatile unsigned int*) MSA_MISC0_reg))
#define MSA_MISC0_inst_adr                                                           "0x00B5"
#define MSA_MISC0_inst                                                               0x00B5
#define MSA_MISC0_colorbit_shift                                                     (5)
#define MSA_MISC0_colorbit_mask                                                      (0x000000E0)
#define MSA_MISC0_colorbit(data)                                                     (0x000000E0&((data)<<5))
#define MSA_MISC0_colorbit_src(data)                                                 ((0x000000E0&(data))>>5)
#define MSA_MISC0_get_colorbit(data)                                                 ((0x000000E0&(data))>>5)
#define MSA_MISC0_ycc_col_shift                                                      (4)
#define MSA_MISC0_ycc_col_mask                                                       (0x00000010)
#define MSA_MISC0_ycc_col(data)                                                      (0x00000010&((data)<<4))
#define MSA_MISC0_ycc_col_src(data)                                                  ((0x00000010&(data))>>4)
#define MSA_MISC0_get_ycc_col(data)                                                  ((0x00000010&(data))>>4)
#define MSA_MISC0_dyn_range_shift                                                    (3)
#define MSA_MISC0_dyn_range_mask                                                     (0x00000008)
#define MSA_MISC0_dyn_range(data)                                                    (0x00000008&((data)<<3))
#define MSA_MISC0_dyn_range_src(data)                                                ((0x00000008&(data))>>3)
#define MSA_MISC0_get_dyn_range(data)                                                ((0x00000008&(data))>>3)
#define MSA_MISC0_component_format_shift                                             (1)
#define MSA_MISC0_component_format_mask                                              (0x00000006)
#define MSA_MISC0_component_format(data)                                             (0x00000006&((data)<<1))
#define MSA_MISC0_component_format_src(data)                                         ((0x00000006&(data))>>1)
#define MSA_MISC0_get_component_format(data)                                         ((0x00000006&(data))>>1)
#define MSA_MISC0_sync_clk_en_shift                                                  (0)
#define MSA_MISC0_sync_clk_en_mask                                                   (0x00000001)
#define MSA_MISC0_sync_clk_en(data)                                                  (0x00000001&((data)<<0))
#define MSA_MISC0_sync_clk_en_src(data)                                              ((0x00000001&(data))>>0)
#define MSA_MISC0_get_sync_clk_en(data)                                              ((0x00000001&(data))>>0)


#define MN_STRM_ATTR_MISC1                                                           0x9803D2D8
#define MN_STRM_ATTR_MISC1_reg_addr                                                  "0x9803D2D8"
#define MN_STRM_ATTR_MISC1_reg                                                       0x9803D2D8
#define set_MN_STRM_ATTR_MISC1_reg(data)   (*((volatile unsigned int*) MN_STRM_ATTR_MISC1_reg)=data)
#define get_MN_STRM_ATTR_MISC1_reg   (*((volatile unsigned int*) MN_STRM_ATTR_MISC1_reg))
#define MN_STRM_ATTR_MISC1_inst_adr                                                  "0x00B6"
#define MN_STRM_ATTR_MISC1_inst                                                      0x00B6
#define MN_STRM_ATTR_MISC1_y_only_shift                                              (7)
#define MN_STRM_ATTR_MISC1_y_only_mask                                               (0x00000080)
#define MN_STRM_ATTR_MISC1_y_only(data)                                              (0x00000080&((data)<<7))
#define MN_STRM_ATTR_MISC1_y_only_src(data)                                          ((0x00000080&(data))>>7)
#define MN_STRM_ATTR_MISC1_get_y_only(data)                                          ((0x00000080&(data))>>7)
#define MN_STRM_ATTR_MISC1_Reserved_shift                                            (3)
#define MN_STRM_ATTR_MISC1_Reserved_mask                                             (0x00000078)
#define MN_STRM_ATTR_MISC1_Reserved(data)                                            (0x00000078&((data)<<3))
#define MN_STRM_ATTR_MISC1_Reserved_src(data)                                        ((0x00000078&(data))>>3)
#define MN_STRM_ATTR_MISC1_get_Reserved(data)                                        ((0x00000078&(data))>>3)
#define MN_STRM_ATTR_MISC1_stereo_video_attr_shift                                   (1)
#define MN_STRM_ATTR_MISC1_stereo_video_attr_mask                                    (0x00000006)
#define MN_STRM_ATTR_MISC1_stereo_video_attr(data)                                   (0x00000006&((data)<<1))
#define MN_STRM_ATTR_MISC1_stereo_video_attr_src(data)                               ((0x00000006&(data))>>1)
#define MN_STRM_ATTR_MISC1_get_stereo_video_attr(data)                               ((0x00000006&(data))>>1)
#define MN_STRM_ATTR_MISC1_vtt_even_shift                                            (0)
#define MN_STRM_ATTR_MISC1_vtt_even_mask                                             (0x00000001)
#define MN_STRM_ATTR_MISC1_vtt_even(data)                                            (0x00000001&((data)<<0))
#define MN_STRM_ATTR_MISC1_vtt_even_src(data)                                        ((0x00000001&(data))>>0)
#define MN_STRM_ATTR_MISC1_get_vtt_even(data)                                        ((0x00000001&(data))>>0)


#define MN_STRM_ATTR_HTT_M                                                           0x9803D2DC
#define MN_STRM_ATTR_HTT_M_reg_addr                                                  "0x9803D2DC"
#define MN_STRM_ATTR_HTT_M_reg                                                       0x9803D2DC
#define set_MN_STRM_ATTR_HTT_M_reg(data)   (*((volatile unsigned int*) MN_STRM_ATTR_HTT_M_reg)=data)
#define get_MN_STRM_ATTR_HTT_M_reg   (*((volatile unsigned int*) MN_STRM_ATTR_HTT_M_reg))
#define MN_STRM_ATTR_HTT_M_inst_adr                                                  "0x00B7"
#define MN_STRM_ATTR_HTT_M_inst                                                      0x00B7
#define MN_STRM_ATTR_HTT_M_htotal158_shift                                           (0)
#define MN_STRM_ATTR_HTT_M_htotal158_mask                                            (0x000000FF)
#define MN_STRM_ATTR_HTT_M_htotal158(data)                                           (0x000000FF&((data)<<0))
#define MN_STRM_ATTR_HTT_M_htotal158_src(data)                                       ((0x000000FF&(data))>>0)
#define MN_STRM_ATTR_HTT_M_get_htotal158(data)                                       ((0x000000FF&(data))>>0)


#define MN_STRM_ATTR_HTT_L                                                           0x9803D2E0
#define MN_STRM_ATTR_HTT_L_reg_addr                                                  "0x9803D2E0"
#define MN_STRM_ATTR_HTT_L_reg                                                       0x9803D2E0
#define set_MN_STRM_ATTR_HTT_L_reg(data)   (*((volatile unsigned int*) MN_STRM_ATTR_HTT_L_reg)=data)
#define get_MN_STRM_ATTR_HTT_L_reg   (*((volatile unsigned int*) MN_STRM_ATTR_HTT_L_reg))
#define MN_STRM_ATTR_HTT_L_inst_adr                                                  "0x00B8"
#define MN_STRM_ATTR_HTT_L_inst                                                      0x00B8
#define MN_STRM_ATTR_HTT_L_htotal70_shift                                            (0)
#define MN_STRM_ATTR_HTT_L_htotal70_mask                                             (0x000000FF)
#define MN_STRM_ATTR_HTT_L_htotal70(data)                                            (0x000000FF&((data)<<0))
#define MN_STRM_ATTR_HTT_L_htotal70_src(data)                                        ((0x000000FF&(data))>>0)
#define MN_STRM_ATTR_HTT_L_get_htotal70(data)                                        ((0x000000FF&(data))>>0)


#define MN_STRM_ATTR_HST_M                                                           0x9803D2E4
#define MN_STRM_ATTR_HST_M_reg_addr                                                  "0x9803D2E4"
#define MN_STRM_ATTR_HST_M_reg                                                       0x9803D2E4
#define set_MN_STRM_ATTR_HST_M_reg(data)   (*((volatile unsigned int*) MN_STRM_ATTR_HST_M_reg)=data)
#define get_MN_STRM_ATTR_HST_M_reg   (*((volatile unsigned int*) MN_STRM_ATTR_HST_M_reg))
#define MN_STRM_ATTR_HST_M_inst_adr                                                  "0x00B9"
#define MN_STRM_ATTR_HST_M_inst                                                      0x00B9
#define MN_STRM_ATTR_HST_M_hstart158_shift                                           (0)
#define MN_STRM_ATTR_HST_M_hstart158_mask                                            (0x000000FF)
#define MN_STRM_ATTR_HST_M_hstart158(data)                                           (0x000000FF&((data)<<0))
#define MN_STRM_ATTR_HST_M_hstart158_src(data)                                       ((0x000000FF&(data))>>0)
#define MN_STRM_ATTR_HST_M_get_hstart158(data)                                       ((0x000000FF&(data))>>0)


#define MN_STRM_ATTR_HST_L                                                           0x9803D2E8
#define MN_STRM_ATTR_HST_L_reg_addr                                                  "0x9803D2E8"
#define MN_STRM_ATTR_HST_L_reg                                                       0x9803D2E8
#define set_MN_STRM_ATTR_HST_L_reg(data)   (*((volatile unsigned int*) MN_STRM_ATTR_HST_L_reg)=data)
#define get_MN_STRM_ATTR_HST_L_reg   (*((volatile unsigned int*) MN_STRM_ATTR_HST_L_reg))
#define MN_STRM_ATTR_HST_L_inst_adr                                                  "0x00BA"
#define MN_STRM_ATTR_HST_L_inst                                                      0x00BA
#define MN_STRM_ATTR_HST_L_hstart70_shift                                            (0)
#define MN_STRM_ATTR_HST_L_hstart70_mask                                             (0x000000FF)
#define MN_STRM_ATTR_HST_L_hstart70(data)                                            (0x000000FF&((data)<<0))
#define MN_STRM_ATTR_HST_L_hstart70_src(data)                                        ((0x000000FF&(data))>>0)
#define MN_STRM_ATTR_HST_L_get_hstart70(data)                                        ((0x000000FF&(data))>>0)


#define MN_STRM_ATTR_HWD_M                                                           0x9803D2EC
#define MN_STRM_ATTR_HWD_M_reg_addr                                                  "0x9803D2EC"
#define MN_STRM_ATTR_HWD_M_reg                                                       0x9803D2EC
#define set_MN_STRM_ATTR_HWD_M_reg(data)   (*((volatile unsigned int*) MN_STRM_ATTR_HWD_M_reg)=data)
#define get_MN_STRM_ATTR_HWD_M_reg   (*((volatile unsigned int*) MN_STRM_ATTR_HWD_M_reg))
#define MN_STRM_ATTR_HWD_M_inst_adr                                                  "0x00BB"
#define MN_STRM_ATTR_HWD_M_inst                                                      0x00BB
#define MN_STRM_ATTR_HWD_M_hwidth158_shift                                           (0)
#define MN_STRM_ATTR_HWD_M_hwidth158_mask                                            (0x000000FF)
#define MN_STRM_ATTR_HWD_M_hwidth158(data)                                           (0x000000FF&((data)<<0))
#define MN_STRM_ATTR_HWD_M_hwidth158_src(data)                                       ((0x000000FF&(data))>>0)
#define MN_STRM_ATTR_HWD_M_get_hwidth158(data)                                       ((0x000000FF&(data))>>0)


#define MN_STRM_ATTR_HWD_L                                                           0x9803D2F0
#define MN_STRM_ATTR_HWD_L_reg_addr                                                  "0x9803D2F0"
#define MN_STRM_ATTR_HWD_L_reg                                                       0x9803D2F0
#define set_MN_STRM_ATTR_HWD_L_reg(data)   (*((volatile unsigned int*) MN_STRM_ATTR_HWD_L_reg)=data)
#define get_MN_STRM_ATTR_HWD_L_reg   (*((volatile unsigned int*) MN_STRM_ATTR_HWD_L_reg))
#define MN_STRM_ATTR_HWD_L_inst_adr                                                  "0x00BC"
#define MN_STRM_ATTR_HWD_L_inst                                                      0x00BC
#define MN_STRM_ATTR_HWD_L_hwidth70_shift                                            (0)
#define MN_STRM_ATTR_HWD_L_hwidth70_mask                                             (0x000000FF)
#define MN_STRM_ATTR_HWD_L_hwidth70(data)                                            (0x000000FF&((data)<<0))
#define MN_STRM_ATTR_HWD_L_hwidth70_src(data)                                        ((0x000000FF&(data))>>0)
#define MN_STRM_ATTR_HWD_L_get_hwidth70(data)                                        ((0x000000FF&(data))>>0)


#define MN_STRM_ATTR_HSW_M                                                           0x9803D2F4
#define MN_STRM_ATTR_HSW_M_reg_addr                                                  "0x9803D2F4"
#define MN_STRM_ATTR_HSW_M_reg                                                       0x9803D2F4
#define set_MN_STRM_ATTR_HSW_M_reg(data)   (*((volatile unsigned int*) MN_STRM_ATTR_HSW_M_reg)=data)
#define get_MN_STRM_ATTR_HSW_M_reg   (*((volatile unsigned int*) MN_STRM_ATTR_HSW_M_reg))
#define MN_STRM_ATTR_HSW_M_inst_adr                                                  "0x00BD"
#define MN_STRM_ATTR_HSW_M_inst                                                      0x00BD
#define MN_STRM_ATTR_HSW_M_hsp_shift                                                 (7)
#define MN_STRM_ATTR_HSW_M_hsp_mask                                                  (0x00000080)
#define MN_STRM_ATTR_HSW_M_hsp(data)                                                 (0x00000080&((data)<<7))
#define MN_STRM_ATTR_HSW_M_hsp_src(data)                                             ((0x00000080&(data))>>7)
#define MN_STRM_ATTR_HSW_M_get_hsp(data)                                             ((0x00000080&(data))>>7)
#define MN_STRM_ATTR_HSW_M_hsw148_shift                                              (0)
#define MN_STRM_ATTR_HSW_M_hsw148_mask                                               (0x0000007F)
#define MN_STRM_ATTR_HSW_M_hsw148(data)                                              (0x0000007F&((data)<<0))
#define MN_STRM_ATTR_HSW_M_hsw148_src(data)                                          ((0x0000007F&(data))>>0)
#define MN_STRM_ATTR_HSW_M_get_hsw148(data)                                          ((0x0000007F&(data))>>0)


#define MN_STRM_ATTR_HSW_L                                                           0x9803D2F8
#define MN_STRM_ATTR_HSW_L_reg_addr                                                  "0x9803D2F8"
#define MN_STRM_ATTR_HSW_L_reg                                                       0x9803D2F8
#define set_MN_STRM_ATTR_HSW_L_reg(data)   (*((volatile unsigned int*) MN_STRM_ATTR_HSW_L_reg)=data)
#define get_MN_STRM_ATTR_HSW_L_reg   (*((volatile unsigned int*) MN_STRM_ATTR_HSW_L_reg))
#define MN_STRM_ATTR_HSW_L_inst_adr                                                  "0x00BE"
#define MN_STRM_ATTR_HSW_L_inst                                                      0x00BE
#define MN_STRM_ATTR_HSW_L_hsw70_shift                                               (0)
#define MN_STRM_ATTR_HSW_L_hsw70_mask                                                (0x000000FF)
#define MN_STRM_ATTR_HSW_L_hsw70(data)                                               (0x000000FF&((data)<<0))
#define MN_STRM_ATTR_HSW_L_hsw70_src(data)                                           ((0x000000FF&(data))>>0)
#define MN_STRM_ATTR_HSW_L_get_hsw70(data)                                           ((0x000000FF&(data))>>0)


#define MN_STRM_ATTR_VTTE_M                                                          0x9803D2FC
#define MN_STRM_ATTR_VTTE_M_reg_addr                                                 "0x9803D2FC"
#define MN_STRM_ATTR_VTTE_M_reg                                                      0x9803D2FC
#define set_MN_STRM_ATTR_VTTE_M_reg(data)   (*((volatile unsigned int*) MN_STRM_ATTR_VTTE_M_reg)=data)
#define get_MN_STRM_ATTR_VTTE_M_reg   (*((volatile unsigned int*) MN_STRM_ATTR_VTTE_M_reg))
#define MN_STRM_ATTR_VTTE_M_inst_adr                                                 "0x00BF"
#define MN_STRM_ATTR_VTTE_M_inst                                                     0x00BF
#define MN_STRM_ATTR_VTTE_M_vtotal158_shift                                          (0)
#define MN_STRM_ATTR_VTTE_M_vtotal158_mask                                           (0x000000FF)
#define MN_STRM_ATTR_VTTE_M_vtotal158(data)                                          (0x000000FF&((data)<<0))
#define MN_STRM_ATTR_VTTE_M_vtotal158_src(data)                                      ((0x000000FF&(data))>>0)
#define MN_STRM_ATTR_VTTE_M_get_vtotal158(data)                                      ((0x000000FF&(data))>>0)


#define MN_STRM_ATTR_VTTE_L                                                          0x9803D300
#define MN_STRM_ATTR_VTTE_L_reg_addr                                                 "0x9803D300"
#define MN_STRM_ATTR_VTTE_L_reg                                                      0x9803D300
#define set_MN_STRM_ATTR_VTTE_L_reg(data)   (*((volatile unsigned int*) MN_STRM_ATTR_VTTE_L_reg)=data)
#define get_MN_STRM_ATTR_VTTE_L_reg   (*((volatile unsigned int*) MN_STRM_ATTR_VTTE_L_reg))
#define MN_STRM_ATTR_VTTE_L_inst_adr                                                 "0x00C0"
#define MN_STRM_ATTR_VTTE_L_inst                                                     0x00C0
#define MN_STRM_ATTR_VTTE_L_vtotal70_shift                                           (0)
#define MN_STRM_ATTR_VTTE_L_vtotal70_mask                                            (0x000000FF)
#define MN_STRM_ATTR_VTTE_L_vtotal70(data)                                           (0x000000FF&((data)<<0))
#define MN_STRM_ATTR_VTTE_L_vtotal70_src(data)                                       ((0x000000FF&(data))>>0)
#define MN_STRM_ATTR_VTTE_L_get_vtotal70(data)                                       ((0x000000FF&(data))>>0)


#define MN_STRM_ATTR_VST_M                                                           0x9803D304
#define MN_STRM_ATTR_VST_M_reg_addr                                                  "0x9803D304"
#define MN_STRM_ATTR_VST_M_reg                                                       0x9803D304
#define set_MN_STRM_ATTR_VST_M_reg(data)   (*((volatile unsigned int*) MN_STRM_ATTR_VST_M_reg)=data)
#define get_MN_STRM_ATTR_VST_M_reg   (*((volatile unsigned int*) MN_STRM_ATTR_VST_M_reg))
#define MN_STRM_ATTR_VST_M_inst_adr                                                  "0x00C1"
#define MN_STRM_ATTR_VST_M_inst                                                      0x00C1
#define MN_STRM_ATTR_VST_M_vstart158_shift                                           (0)
#define MN_STRM_ATTR_VST_M_vstart158_mask                                            (0x000000FF)
#define MN_STRM_ATTR_VST_M_vstart158(data)                                           (0x000000FF&((data)<<0))
#define MN_STRM_ATTR_VST_M_vstart158_src(data)                                       ((0x000000FF&(data))>>0)
#define MN_STRM_ATTR_VST_M_get_vstart158(data)                                       ((0x000000FF&(data))>>0)


#define MN_STRM_ATTR_VST_L                                                           0x9803D308
#define MN_STRM_ATTR_VST_L_reg_addr                                                  "0x9803D308"
#define MN_STRM_ATTR_VST_L_reg                                                       0x9803D308
#define set_MN_STRM_ATTR_VST_L_reg(data)   (*((volatile unsigned int*) MN_STRM_ATTR_VST_L_reg)=data)
#define get_MN_STRM_ATTR_VST_L_reg   (*((volatile unsigned int*) MN_STRM_ATTR_VST_L_reg))
#define MN_STRM_ATTR_VST_L_inst_adr                                                  "0x00C2"
#define MN_STRM_ATTR_VST_L_inst                                                      0x00C2
#define MN_STRM_ATTR_VST_L_vstart70_shift                                            (0)
#define MN_STRM_ATTR_VST_L_vstart70_mask                                             (0x000000FF)
#define MN_STRM_ATTR_VST_L_vstart70(data)                                            (0x000000FF&((data)<<0))
#define MN_STRM_ATTR_VST_L_vstart70_src(data)                                        ((0x000000FF&(data))>>0)
#define MN_STRM_ATTR_VST_L_get_vstart70(data)                                        ((0x000000FF&(data))>>0)


#define MN_STRM_ATTR_VHT_M                                                           0x9803D30C
#define MN_STRM_ATTR_VHT_M_reg_addr                                                  "0x9803D30C"
#define MN_STRM_ATTR_VHT_M_reg                                                       0x9803D30C
#define set_MN_STRM_ATTR_VHT_M_reg(data)   (*((volatile unsigned int*) MN_STRM_ATTR_VHT_M_reg)=data)
#define get_MN_STRM_ATTR_VHT_M_reg   (*((volatile unsigned int*) MN_STRM_ATTR_VHT_M_reg))
#define MN_STRM_ATTR_VHT_M_inst_adr                                                  "0x00C3"
#define MN_STRM_ATTR_VHT_M_inst                                                      0x00C3
#define MN_STRM_ATTR_VHT_M_vheight158_shift                                          (0)
#define MN_STRM_ATTR_VHT_M_vheight158_mask                                           (0x000000FF)
#define MN_STRM_ATTR_VHT_M_vheight158(data)                                          (0x000000FF&((data)<<0))
#define MN_STRM_ATTR_VHT_M_vheight158_src(data)                                      ((0x000000FF&(data))>>0)
#define MN_STRM_ATTR_VHT_M_get_vheight158(data)                                      ((0x000000FF&(data))>>0)


#define MN_STRM_ATTR_VHT_L                                                           0x9803D310
#define MN_STRM_ATTR_VHT_L_reg_addr                                                  "0x9803D310"
#define MN_STRM_ATTR_VHT_L_reg                                                       0x9803D310
#define set_MN_STRM_ATTR_VHT_L_reg(data)   (*((volatile unsigned int*) MN_STRM_ATTR_VHT_L_reg)=data)
#define get_MN_STRM_ATTR_VHT_L_reg   (*((volatile unsigned int*) MN_STRM_ATTR_VHT_L_reg))
#define MN_STRM_ATTR_VHT_L_inst_adr                                                  "0x00C4"
#define MN_STRM_ATTR_VHT_L_inst                                                      0x00C4
#define MN_STRM_ATTR_VHT_L_vheight70_shift                                           (0)
#define MN_STRM_ATTR_VHT_L_vheight70_mask                                            (0x000000FF)
#define MN_STRM_ATTR_VHT_L_vheight70(data)                                           (0x000000FF&((data)<<0))
#define MN_STRM_ATTR_VHT_L_vheight70_src(data)                                       ((0x000000FF&(data))>>0)
#define MN_STRM_ATTR_VHT_L_get_vheight70(data)                                       ((0x000000FF&(data))>>0)


#define MN_STRM_ATTR_VSW_M                                                           0x9803D314
#define MN_STRM_ATTR_VSW_M_reg_addr                                                  "0x9803D314"
#define MN_STRM_ATTR_VSW_M_reg                                                       0x9803D314
#define set_MN_STRM_ATTR_VSW_M_reg(data)   (*((volatile unsigned int*) MN_STRM_ATTR_VSW_M_reg)=data)
#define get_MN_STRM_ATTR_VSW_M_reg   (*((volatile unsigned int*) MN_STRM_ATTR_VSW_M_reg))
#define MN_STRM_ATTR_VSW_M_inst_adr                                                  "0x00C5"
#define MN_STRM_ATTR_VSW_M_inst                                                      0x00C5
#define MN_STRM_ATTR_VSW_M_vsp_shift                                                 (7)
#define MN_STRM_ATTR_VSW_M_vsp_mask                                                  (0x00000080)
#define MN_STRM_ATTR_VSW_M_vsp(data)                                                 (0x00000080&((data)<<7))
#define MN_STRM_ATTR_VSW_M_vsp_src(data)                                             ((0x00000080&(data))>>7)
#define MN_STRM_ATTR_VSW_M_get_vsp(data)                                             ((0x00000080&(data))>>7)
#define MN_STRM_ATTR_VSW_M_vsw148_shift                                              (0)
#define MN_STRM_ATTR_VSW_M_vsw148_mask                                               (0x0000007F)
#define MN_STRM_ATTR_VSW_M_vsw148(data)                                              (0x0000007F&((data)<<0))
#define MN_STRM_ATTR_VSW_M_vsw148_src(data)                                          ((0x0000007F&(data))>>0)
#define MN_STRM_ATTR_VSW_M_get_vsw148(data)                                          ((0x0000007F&(data))>>0)


#define MN_STRM_ATTR_VSW_L                                                           0x9803D318
#define MN_STRM_ATTR_VSW_L_reg_addr                                                  "0x9803D318"
#define MN_STRM_ATTR_VSW_L_reg                                                       0x9803D318
#define set_MN_STRM_ATTR_VSW_L_reg(data)   (*((volatile unsigned int*) MN_STRM_ATTR_VSW_L_reg)=data)
#define get_MN_STRM_ATTR_VSW_L_reg   (*((volatile unsigned int*) MN_STRM_ATTR_VSW_L_reg))
#define MN_STRM_ATTR_VSW_L_inst_adr                                                  "0x00C6"
#define MN_STRM_ATTR_VSW_L_inst                                                      0x00C6
#define MN_STRM_ATTR_VSW_L_vsw70_shift                                               (0)
#define MN_STRM_ATTR_VSW_L_vsw70_mask                                                (0x000000FF)
#define MN_STRM_ATTR_VSW_L_vsw70(data)                                               (0x000000FF&((data)<<0))
#define MN_STRM_ATTR_VSW_L_vsw70_src(data)                                           ((0x000000FF&(data))>>0)
#define MN_STRM_ATTR_VSW_L_get_vsw70(data)                                           ((0x000000FF&(data))>>0)


#define VBID                                                                         0x9803D31C
#define VBID_reg_addr                                                                "0x9803D31C"
#define VBID_reg                                                                     0x9803D31C
#define set_VBID_reg(data)   (*((volatile unsigned int*) VBID_reg)=data)
#define get_VBID_reg   (*((volatile unsigned int*) VBID_reg))
#define VBID_inst_adr                                                                "0x00C7"
#define VBID_inst                                                                    0x00C7
#define VBID_Reserved_shift                                                          (3)
#define VBID_Reserved_mask                                                           (0x000000F8)
#define VBID_Reserved(data)                                                          (0x000000F8&((data)<<3))
#define VBID_Reserved_src(data)                                                      ((0x000000F8&(data))>>3)
#define VBID_get_Reserved(data)                                                      ((0x000000F8&(data))>>3)
#define VBID_audiomute_flag_shift                                                    (2)
#define VBID_audiomute_flag_mask                                                     (0x00000004)
#define VBID_audiomute_flag(data)                                                    (0x00000004&((data)<<2))
#define VBID_audiomute_flag_src(data)                                                ((0x00000004&(data))>>2)
#define VBID_get_audiomute_flag(data)                                                ((0x00000004&(data))>>2)
#define VBID_novideo_flag_shift                                                      (1)
#define VBID_novideo_flag_mask                                                       (0x00000002)
#define VBID_novideo_flag(data)                                                      (0x00000002&((data)<<1))
#define VBID_novideo_flag_src(data)                                                  ((0x00000002&(data))>>1)
#define VBID_get_novideo_flag(data)                                                  ((0x00000002&(data))>>1)
#define VBID_interlace_shift                                                         (0)
#define VBID_interlace_mask                                                          (0x00000001)
#define VBID_interlace(data)                                                         (0x00000001&((data)<<0))
#define VBID_interlace_src(data)                                                     ((0x00000001&(data))>>0)
#define VBID_get_interlace(data)                                                     ((0x00000001&(data))>>0)


#define VBID_FW_CTL                                                                  0x9803D320
#define VBID_FW_CTL_reg_addr                                                         "0x9803D320"
#define VBID_FW_CTL_reg                                                              0x9803D320
#define set_VBID_FW_CTL_reg(data)   (*((volatile unsigned int*) VBID_FW_CTL_reg)=data)
#define get_VBID_FW_CTL_reg   (*((volatile unsigned int*) VBID_FW_CTL_reg))
#define VBID_FW_CTL_inst_adr                                                         "0x00C8"
#define VBID_FW_CTL_inst                                                             0x00C8
#define VBID_FW_CTL_Reserved_shift                                                   (1)
#define VBID_FW_CTL_Reserved_mask                                                    (0x000000FE)
#define VBID_FW_CTL_Reserved(data)                                                   (0x000000FE&((data)<<1))
#define VBID_FW_CTL_Reserved_src(data)                                               ((0x000000FE&(data))>>1)
#define VBID_FW_CTL_get_Reserved(data)                                               ((0x000000FE&(data))>>1)
#define VBID_FW_CTL_vbid_fw_ctrl_shift                                               (0)
#define VBID_FW_CTL_vbid_fw_ctrl_mask                                                (0x00000001)
#define VBID_FW_CTL_vbid_fw_ctrl(data)                                               (0x00000001&((data)<<0))
#define VBID_FW_CTL_vbid_fw_ctrl_src(data)                                           ((0x00000001&(data))>>0)
#define VBID_FW_CTL_get_vbid_fw_ctrl(data)                                           ((0x00000001&(data))>>0)


#define ARBITER_CTRL                                                                 0x9803D324
#define ARBITER_CTRL_reg_addr                                                        "0x9803D324"
#define ARBITER_CTRL_reg                                                             0x9803D324
#define set_ARBITER_CTRL_reg(data)   (*((volatile unsigned int*) ARBITER_CTRL_reg)=data)
#define get_ARBITER_CTRL_reg   (*((volatile unsigned int*) ARBITER_CTRL_reg))
#define ARBITER_CTRL_inst_adr                                                        "0x00C9"
#define ARBITER_CTRL_inst                                                            0x00C9
#define ARBITER_CTRL_Reserved_shift                                                  (2)
#define ARBITER_CTRL_Reserved_mask                                                   (0x000000FC)
#define ARBITER_CTRL_Reserved(data)                                                  (0x000000FC&((data)<<2))
#define ARBITER_CTRL_Reserved_src(data)                                              ((0x000000FC&(data))>>2)
#define ARBITER_CTRL_get_Reserved(data)                                              ((0x000000FC&(data))>>2)
#define ARBITER_CTRL_vactive_md_shift                                                (1)
#define ARBITER_CTRL_vactive_md_mask                                                 (0x00000002)
#define ARBITER_CTRL_vactive_md(data)                                                (0x00000002&((data)<<1))
#define ARBITER_CTRL_vactive_md_src(data)                                            ((0x00000002&(data))>>1)
#define ARBITER_CTRL_get_vactive_md(data)                                            ((0x00000002&(data))>>1)
#define ARBITER_CTRL_arbiter_en_shift                                                (0)
#define ARBITER_CTRL_arbiter_en_mask                                                 (0x00000001)
#define ARBITER_CTRL_arbiter_en(data)                                                (0x00000001&((data)<<0))
#define ARBITER_CTRL_arbiter_en_src(data)                                            ((0x00000001&(data))>>0)
#define ARBITER_CTRL_get_arbiter_en(data)                                            ((0x00000001&(data))>>0)


#define V_DATA_PER_LINE0                                                             0x9803D328
#define V_DATA_PER_LINE0_reg_addr                                                    "0x9803D328"
#define V_DATA_PER_LINE0_reg                                                         0x9803D328
#define set_V_DATA_PER_LINE0_reg(data)   (*((volatile unsigned int*) V_DATA_PER_LINE0_reg)=data)
#define get_V_DATA_PER_LINE0_reg   (*((volatile unsigned int*) V_DATA_PER_LINE0_reg))
#define V_DATA_PER_LINE0_inst_adr                                                    "0x00CA"
#define V_DATA_PER_LINE0_inst                                                        0x00CA
#define V_DATA_PER_LINE0_Reserved_shift                                              (7)
#define V_DATA_PER_LINE0_Reserved_mask                                               (0x00000080)
#define V_DATA_PER_LINE0_Reserved(data)                                              (0x00000080&((data)<<7))
#define V_DATA_PER_LINE0_Reserved_src(data)                                          ((0x00000080&(data))>>7)
#define V_DATA_PER_LINE0_get_Reserved(data)                                          ((0x00000080&(data))>>7)
#define V_DATA_PER_LINE0_v_data_per_line148_shift                                    (0)
#define V_DATA_PER_LINE0_v_data_per_line148_mask                                     (0x0000007F)
#define V_DATA_PER_LINE0_v_data_per_line148(data)                                    (0x0000007F&((data)<<0))
#define V_DATA_PER_LINE0_v_data_per_line148_src(data)                                ((0x0000007F&(data))>>0)
#define V_DATA_PER_LINE0_get_v_data_per_line148(data)                                ((0x0000007F&(data))>>0)


#define V_DATA_PER_LINE1                                                             0x9803D32C
#define V_DATA_PER_LINE1_reg_addr                                                    "0x9803D32C"
#define V_DATA_PER_LINE1_reg                                                         0x9803D32C
#define set_V_DATA_PER_LINE1_reg(data)   (*((volatile unsigned int*) V_DATA_PER_LINE1_reg)=data)
#define get_V_DATA_PER_LINE1_reg   (*((volatile unsigned int*) V_DATA_PER_LINE1_reg))
#define V_DATA_PER_LINE1_inst_adr                                                    "0x00CB"
#define V_DATA_PER_LINE1_inst                                                        0x00CB
#define V_DATA_PER_LINE1_v_data_per_line70_shift                                     (0)
#define V_DATA_PER_LINE1_v_data_per_line70_mask                                      (0x000000FF)
#define V_DATA_PER_LINE1_v_data_per_line70(data)                                     (0x000000FF&((data)<<0))
#define V_DATA_PER_LINE1_v_data_per_line70_src(data)                                 ((0x000000FF&(data))>>0)
#define V_DATA_PER_LINE1_get_v_data_per_line70(data)                                 ((0x000000FF&(data))>>0)


#define TU_SIZE                                                                      0x9803D330
#define TU_SIZE_reg_addr                                                             "0x9803D330"
#define TU_SIZE_reg                                                                  0x9803D330
#define set_TU_SIZE_reg(data)   (*((volatile unsigned int*) TU_SIZE_reg)=data)
#define get_TU_SIZE_reg   (*((volatile unsigned int*) TU_SIZE_reg))
#define TU_SIZE_inst_adr                                                             "0x00CC"
#define TU_SIZE_inst                                                                 0x00CC
#define TU_SIZE_Reserved_shift                                                       (7)
#define TU_SIZE_Reserved_mask                                                        (0x00000080)
#define TU_SIZE_Reserved(data)                                                       (0x00000080&((data)<<7))
#define TU_SIZE_Reserved_src(data)                                                   ((0x00000080&(data))>>7)
#define TU_SIZE_get_Reserved(data)                                                   ((0x00000080&(data))>>7)
#define TU_SIZE_tu_size_shift                                                        (0)
#define TU_SIZE_tu_size_mask                                                         (0x0000007F)
#define TU_SIZE_tu_size(data)                                                        (0x0000007F&((data)<<0))
#define TU_SIZE_tu_size_src(data)                                                    ((0x0000007F&(data))>>0)
#define TU_SIZE_get_tu_size(data)                                                    ((0x0000007F&(data))>>0)


#define TU_DATA_SIZE0                                                                0x9803D334
#define TU_DATA_SIZE0_reg_addr                                                       "0x9803D334"
#define TU_DATA_SIZE0_reg                                                            0x9803D334
#define set_TU_DATA_SIZE0_reg(data)   (*((volatile unsigned int*) TU_DATA_SIZE0_reg)=data)
#define get_TU_DATA_SIZE0_reg   (*((volatile unsigned int*) TU_DATA_SIZE0_reg))
#define TU_DATA_SIZE0_inst_adr                                                       "0x00CD"
#define TU_DATA_SIZE0_inst                                                           0x00CD
#define TU_DATA_SIZE0_Reserved_shift                                                 (7)
#define TU_DATA_SIZE0_Reserved_mask                                                  (0x00000080)
#define TU_DATA_SIZE0_Reserved(data)                                                 (0x00000080&((data)<<7))
#define TU_DATA_SIZE0_Reserved_src(data)                                             ((0x00000080&(data))>>7)
#define TU_DATA_SIZE0_get_Reserved(data)                                             ((0x00000080&(data))>>7)
#define TU_DATA_SIZE0_tu_data_size93_shift                                           (0)
#define TU_DATA_SIZE0_tu_data_size93_mask                                            (0x0000007F)
#define TU_DATA_SIZE0_tu_data_size93(data)                                           (0x0000007F&((data)<<0))
#define TU_DATA_SIZE0_tu_data_size93_src(data)                                       ((0x0000007F&(data))>>0)
#define TU_DATA_SIZE0_get_tu_data_size93(data)                                       ((0x0000007F&(data))>>0)


#define TU_DATA_SIZE1                                                                0x9803D338
#define TU_DATA_SIZE1_reg_addr                                                       "0x9803D338"
#define TU_DATA_SIZE1_reg                                                            0x9803D338
#define set_TU_DATA_SIZE1_reg(data)   (*((volatile unsigned int*) TU_DATA_SIZE1_reg)=data)
#define get_TU_DATA_SIZE1_reg   (*((volatile unsigned int*) TU_DATA_SIZE1_reg))
#define TU_DATA_SIZE1_inst_adr                                                       "0x00CE"
#define TU_DATA_SIZE1_inst                                                           0x00CE
#define TU_DATA_SIZE1_Reserved_shift                                                 (3)
#define TU_DATA_SIZE1_Reserved_mask                                                  (0x000000F8)
#define TU_DATA_SIZE1_Reserved(data)                                                 (0x000000F8&((data)<<3))
#define TU_DATA_SIZE1_Reserved_src(data)                                             ((0x000000F8&(data))>>3)
#define TU_DATA_SIZE1_get_Reserved(data)                                             ((0x000000F8&(data))>>3)
#define TU_DATA_SIZE1_tu_data_size20_shift                                           (0)
#define TU_DATA_SIZE1_tu_data_size20_mask                                            (0x00000007)
#define TU_DATA_SIZE1_tu_data_size20(data)                                           (0x00000007&((data)<<0))
#define TU_DATA_SIZE1_tu_data_size20_src(data)                                       ((0x00000007&(data))>>0)
#define TU_DATA_SIZE1_get_tu_data_size20(data)                                       ((0x00000007&(data))>>0)


#define HDELAY0                                                                      0x9803D33C
#define HDELAY0_reg_addr                                                             "0x9803D33C"
#define HDELAY0_reg                                                                  0x9803D33C
#define set_HDELAY0_reg(data)   (*((volatile unsigned int*) HDELAY0_reg)=data)
#define get_HDELAY0_reg   (*((volatile unsigned int*) HDELAY0_reg))
#define HDELAY0_inst_adr                                                             "0x00CF"
#define HDELAY0_inst                                                                 0x00CF
#define HDELAY0_Reserved_shift                                                       (7)
#define HDELAY0_Reserved_mask                                                        (0x00000080)
#define HDELAY0_Reserved(data)                                                       (0x00000080&((data)<<7))
#define HDELAY0_Reserved_src(data)                                                   ((0x00000080&(data))>>7)
#define HDELAY0_get_Reserved(data)                                                   ((0x00000080&(data))>>7)
#define HDELAY0_hdelay148_shift                                                      (0)
#define HDELAY0_hdelay148_mask                                                       (0x0000007F)
#define HDELAY0_hdelay148(data)                                                      (0x0000007F&((data)<<0))
#define HDELAY0_hdelay148_src(data)                                                  ((0x0000007F&(data))>>0)
#define HDELAY0_get_hdelay148(data)                                                  ((0x0000007F&(data))>>0)


#define HDELAY1                                                                      0x9803D340
#define HDELAY1_reg_addr                                                             "0x9803D340"
#define HDELAY1_reg                                                                  0x9803D340
#define set_HDELAY1_reg(data)   (*((volatile unsigned int*) HDELAY1_reg)=data)
#define get_HDELAY1_reg   (*((volatile unsigned int*) HDELAY1_reg))
#define HDELAY1_inst_adr                                                             "0x00D0"
#define HDELAY1_inst                                                                 0x00D0
#define HDELAY1_hdelay70_shift                                                       (0)
#define HDELAY1_hdelay70_mask                                                        (0x000000FF)
#define HDELAY1_hdelay70(data)                                                       (0x000000FF&((data)<<0))
#define HDELAY1_hdelay70_src(data)                                                   ((0x000000FF&(data))>>0)
#define HDELAY1_get_hdelay70(data)                                                   ((0x000000FF&(data))>>0)


#define AUTO_HDELAY0                                                                 0x9803D344
#define AUTO_HDELAY0_reg_addr                                                        "0x9803D344"
#define AUTO_HDELAY0_reg                                                             0x9803D344
#define set_AUTO_HDELAY0_reg(data)   (*((volatile unsigned int*) AUTO_HDELAY0_reg)=data)
#define get_AUTO_HDELAY0_reg   (*((volatile unsigned int*) AUTO_HDELAY0_reg))
#define AUTO_HDELAY0_inst_adr                                                        "0x00D1"
#define AUTO_HDELAY0_inst                                                            0x00D1
#define AUTO_HDELAY0_Reserved_shift                                                  (7)
#define AUTO_HDELAY0_Reserved_mask                                                   (0x00000080)
#define AUTO_HDELAY0_Reserved(data)                                                  (0x00000080&((data)<<7))
#define AUTO_HDELAY0_Reserved_src(data)                                              ((0x00000080&(data))>>7)
#define AUTO_HDELAY0_get_Reserved(data)                                              ((0x00000080&(data))>>7)
#define AUTO_HDELAY0_auto_hdelay148_shift                                            (0)
#define AUTO_HDELAY0_auto_hdelay148_mask                                             (0x0000007F)
#define AUTO_HDELAY0_auto_hdelay148(data)                                            (0x0000007F&((data)<<0))
#define AUTO_HDELAY0_auto_hdelay148_src(data)                                        ((0x0000007F&(data))>>0)
#define AUTO_HDELAY0_get_auto_hdelay148(data)                                        ((0x0000007F&(data))>>0)


#define AUTO_HDELAY1                                                                 0x9803D348
#define AUTO_HDELAY1_reg_addr                                                        "0x9803D348"
#define AUTO_HDELAY1_reg                                                             0x9803D348
#define set_AUTO_HDELAY1_reg(data)   (*((volatile unsigned int*) AUTO_HDELAY1_reg)=data)
#define get_AUTO_HDELAY1_reg   (*((volatile unsigned int*) AUTO_HDELAY1_reg))
#define AUTO_HDELAY1_inst_adr                                                        "0x00D2"
#define AUTO_HDELAY1_inst                                                            0x00D2
#define AUTO_HDELAY1_auto_hdelay70_shift                                             (0)
#define AUTO_HDELAY1_auto_hdelay70_mask                                              (0x000000FF)
#define AUTO_HDELAY1_auto_hdelay70(data)                                             (0x000000FF&((data)<<0))
#define AUTO_HDELAY1_auto_hdelay70_src(data)                                         ((0x000000FF&(data))>>0)
#define AUTO_HDELAY1_get_auto_hdelay70(data)                                         ((0x000000FF&(data))>>0)


#define LFIFO_WL_SET                                                                 0x9803D34C
#define LFIFO_WL_SET_reg_addr                                                        "0x9803D34C"
#define LFIFO_WL_SET_reg                                                             0x9803D34C
#define set_LFIFO_WL_SET_reg(data)   (*((volatile unsigned int*) LFIFO_WL_SET_reg)=data)
#define get_LFIFO_WL_SET_reg   (*((volatile unsigned int*) LFIFO_WL_SET_reg))
#define LFIFO_WL_SET_inst_adr                                                        "0x00D3"
#define LFIFO_WL_SET_inst                                                            0x00D3
#define LFIFO_WL_SET_wl_mid_regen_shift                                              (7)
#define LFIFO_WL_SET_wl_mid_regen_mask                                               (0x00000080)
#define LFIFO_WL_SET_wl_mid_regen(data)                                              (0x00000080&((data)<<7))
#define LFIFO_WL_SET_wl_mid_regen_src(data)                                          ((0x00000080&(data))>>7)
#define LFIFO_WL_SET_get_wl_mid_regen(data)                                          ((0x00000080&(data))>>7)
#define LFIFO_WL_SET_wl_mid_set_shift                                                (0)
#define LFIFO_WL_SET_wl_mid_set_mask                                                 (0x0000007F)
#define LFIFO_WL_SET_wl_mid_set(data)                                                (0x0000007F&((data)<<0))
#define LFIFO_WL_SET_wl_mid_set_src(data)                                            ((0x0000007F&(data))>>0)
#define LFIFO_WL_SET_get_wl_mid_set(data)                                            ((0x0000007F&(data))>>0)


#define ARBITER_SEC_END_CNT_HB                                                       0x9803D350
#define ARBITER_SEC_END_CNT_HB_reg_addr                                              "0x9803D350"
#define ARBITER_SEC_END_CNT_HB_reg                                                   0x9803D350
#define set_ARBITER_SEC_END_CNT_HB_reg(data)   (*((volatile unsigned int*) ARBITER_SEC_END_CNT_HB_reg)=data)
#define get_ARBITER_SEC_END_CNT_HB_reg   (*((volatile unsigned int*) ARBITER_SEC_END_CNT_HB_reg))
#define ARBITER_SEC_END_CNT_HB_inst_adr                                              "0x00D4"
#define ARBITER_SEC_END_CNT_HB_inst                                                  0x00D4
#define ARBITER_SEC_END_CNT_HB_Reserved_shift                                        (7)
#define ARBITER_SEC_END_CNT_HB_Reserved_mask                                         (0x00000080)
#define ARBITER_SEC_END_CNT_HB_Reserved(data)                                        (0x00000080&((data)<<7))
#define ARBITER_SEC_END_CNT_HB_Reserved_src(data)                                    ((0x00000080&(data))>>7)
#define ARBITER_SEC_END_CNT_HB_get_Reserved(data)                                    ((0x00000080&(data))>>7)
#define ARBITER_SEC_END_CNT_HB_sec_end_cnt148_shift                                  (0)
#define ARBITER_SEC_END_CNT_HB_sec_end_cnt148_mask                                   (0x0000007F)
#define ARBITER_SEC_END_CNT_HB_sec_end_cnt148(data)                                  (0x0000007F&((data)<<0))
#define ARBITER_SEC_END_CNT_HB_sec_end_cnt148_src(data)                              ((0x0000007F&(data))>>0)
#define ARBITER_SEC_END_CNT_HB_get_sec_end_cnt148(data)                              ((0x0000007F&(data))>>0)


#define ARBITER_SEC_END_CNT_LB                                                       0x9803D354
#define ARBITER_SEC_END_CNT_LB_reg_addr                                              "0x9803D354"
#define ARBITER_SEC_END_CNT_LB_reg                                                   0x9803D354
#define set_ARBITER_SEC_END_CNT_LB_reg(data)   (*((volatile unsigned int*) ARBITER_SEC_END_CNT_LB_reg)=data)
#define get_ARBITER_SEC_END_CNT_LB_reg   (*((volatile unsigned int*) ARBITER_SEC_END_CNT_LB_reg))
#define ARBITER_SEC_END_CNT_LB_inst_adr                                              "0x00D5"
#define ARBITER_SEC_END_CNT_LB_inst                                                  0x00D5
#define ARBITER_SEC_END_CNT_LB_sec_end_cnt70_shift                                   (0)
#define ARBITER_SEC_END_CNT_LB_sec_end_cnt70_mask                                    (0x000000FF)
#define ARBITER_SEC_END_CNT_LB_sec_end_cnt70(data)                                   (0x000000FF&((data)<<0))
#define ARBITER_SEC_END_CNT_LB_sec_end_cnt70_src(data)                               ((0x000000FF&(data))>>0)
#define ARBITER_SEC_END_CNT_LB_get_sec_end_cnt70(data)                               ((0x000000FF&(data))>>0)


#define ARBITER_DEBUG                                                                0x9803D358
#define ARBITER_DEBUG_reg_addr                                                       "0x9803D358"
#define ARBITER_DEBUG_reg                                                            0x9803D358
#define set_ARBITER_DEBUG_reg(data)   (*((volatile unsigned int*) ARBITER_DEBUG_reg)=data)
#define get_ARBITER_DEBUG_reg   (*((volatile unsigned int*) ARBITER_DEBUG_reg))
#define ARBITER_DEBUG_inst_adr                                                       "0x00D6"
#define ARBITER_DEBUG_inst                                                           0x00D6
#define ARBITER_DEBUG_Reserved_shift                                                 (5)
#define ARBITER_DEBUG_Reserved_mask                                                  (0x000000E0)
#define ARBITER_DEBUG_Reserved(data)                                                 (0x000000E0&((data)<<5))
#define ARBITER_DEBUG_Reserved_src(data)                                             ((0x000000E0&(data))>>5)
#define ARBITER_DEBUG_get_Reserved(data)                                             ((0x000000E0&(data))>>5)
#define ARBITER_DEBUG_den_line_end_occur_shift                                       (4)
#define ARBITER_DEBUG_den_line_end_occur_mask                                        (0x00000010)
#define ARBITER_DEBUG_den_line_end_occur(data)                                       (0x00000010&((data)<<4))
#define ARBITER_DEBUG_den_line_end_occur_src(data)                                   ((0x00000010&(data))>>4)
#define ARBITER_DEBUG_get_den_line_end_occur(data)                                   ((0x00000010&(data))>>4)
#define ARBITER_DEBUG_v_active_occur_shift                                           (3)
#define ARBITER_DEBUG_v_active_occur_mask                                            (0x00000008)
#define ARBITER_DEBUG_v_active_occur(data)                                           (0x00000008&((data)<<3))
#define ARBITER_DEBUG_v_active_occur_src(data)                                       ((0x00000008&(data))>>3)
#define ARBITER_DEBUG_get_v_active_occur(data)                                       ((0x00000008&(data))>>3)
#define ARBITER_DEBUG_sec_tx_end_nv_miss_shift                                       (2)
#define ARBITER_DEBUG_sec_tx_end_nv_miss_mask                                        (0x00000004)
#define ARBITER_DEBUG_sec_tx_end_nv_miss(data)                                       (0x00000004&((data)<<2))
#define ARBITER_DEBUG_sec_tx_end_nv_miss_src(data)                                   ((0x00000004&(data))>>2)
#define ARBITER_DEBUG_get_sec_tx_end_nv_miss(data)                                   ((0x00000004&(data))>>2)
#define ARBITER_DEBUG_sec_tx_end_v_miss_shift                                        (1)
#define ARBITER_DEBUG_sec_tx_end_v_miss_mask                                         (0x00000002)
#define ARBITER_DEBUG_sec_tx_end_v_miss(data)                                        (0x00000002&((data)<<1))
#define ARBITER_DEBUG_sec_tx_end_v_miss_src(data)                                    ((0x00000002&(data))>>1)
#define ARBITER_DEBUG_get_sec_tx_end_v_miss(data)                                    ((0x00000002&(data))>>1)
#define ARBITER_DEBUG_vsync_de_shift                                                 (0)
#define ARBITER_DEBUG_vsync_de_mask                                                  (0x00000001)
#define ARBITER_DEBUG_vsync_de(data)                                                 (0x00000001&((data)<<0))
#define ARBITER_DEBUG_vsync_de_src(data)                                             ((0x00000001&(data))>>0)
#define ARBITER_DEBUG_get_vsync_de(data)                                             ((0x00000001&(data))>>0)


#define DPTX_CTSFIFO_CTRL                                                            0x9803D35C
#define DPTX_CTSFIFO_CTRL_reg_addr                                                   "0x9803D35C"
#define DPTX_CTSFIFO_CTRL_reg                                                        0x9803D35C
#define set_DPTX_CTSFIFO_CTRL_reg(data)   (*((volatile unsigned int*) DPTX_CTSFIFO_CTRL_reg)=data)
#define get_DPTX_CTSFIFO_CTRL_reg   (*((volatile unsigned int*) DPTX_CTSFIFO_CTRL_reg))
#define DPTX_CTSFIFO_CTRL_inst_adr                                                   "0x00D7"
#define DPTX_CTSFIFO_CTRL_inst                                                       0x00D7
#define DPTX_CTSFIFO_CTRL_Reserved_shift                                             (3)
#define DPTX_CTSFIFO_CTRL_Reserved_mask                                              (0x000000F8)
#define DPTX_CTSFIFO_CTRL_Reserved(data)                                             (0x000000F8&((data)<<3))
#define DPTX_CTSFIFO_CTRL_Reserved_src(data)                                         ((0x000000F8&(data))>>3)
#define DPTX_CTSFIFO_CTRL_get_Reserved(data)                                         ((0x000000F8&(data))>>3)
#define DPTX_CTSFIFO_CTRL_dptx_force_ctsfifo_rstn_shift                              (2)
#define DPTX_CTSFIFO_CTRL_dptx_force_ctsfifo_rstn_mask                               (0x00000004)
#define DPTX_CTSFIFO_CTRL_dptx_force_ctsfifo_rstn(data)                              (0x00000004&((data)<<2))
#define DPTX_CTSFIFO_CTRL_dptx_force_ctsfifo_rstn_src(data)                          ((0x00000004&(data))>>2)
#define DPTX_CTSFIFO_CTRL_get_dptx_force_ctsfifo_rstn(data)                          ((0x00000004&(data))>>2)
#define DPTX_CTSFIFO_CTRL_dptx_en_ctsfifo_vsrst_shift                                (1)
#define DPTX_CTSFIFO_CTRL_dptx_en_ctsfifo_vsrst_mask                                 (0x00000002)
#define DPTX_CTSFIFO_CTRL_dptx_en_ctsfifo_vsrst(data)                                (0x00000002&((data)<<1))
#define DPTX_CTSFIFO_CTRL_dptx_en_ctsfifo_vsrst_src(data)                            ((0x00000002&(data))>>1)
#define DPTX_CTSFIFO_CTRL_get_dptx_en_ctsfifo_vsrst(data)                            ((0x00000002&(data))>>1)
#define DPTX_CTSFIFO_CTRL_dptx_en_ctsfifo_bypass_shift                               (0)
#define DPTX_CTSFIFO_CTRL_dptx_en_ctsfifo_bypass_mask                                (0x00000001)
#define DPTX_CTSFIFO_CTRL_dptx_en_ctsfifo_bypass(data)                               (0x00000001&((data)<<0))
#define DPTX_CTSFIFO_CTRL_dptx_en_ctsfifo_bypass_src(data)                           ((0x00000001&(data))>>0)
#define DPTX_CTSFIFO_CTRL_get_dptx_en_ctsfifo_bypass(data)                           ((0x00000001&(data))>>0)


#define DPTX_CTSFIFO_RSV1                                                            0x9803D360
#define DPTX_CTSFIFO_RSV1_reg_addr                                                   "0x9803D360"
#define DPTX_CTSFIFO_RSV1_reg                                                        0x9803D360
#define set_DPTX_CTSFIFO_RSV1_reg(data)   (*((volatile unsigned int*) DPTX_CTSFIFO_RSV1_reg)=data)
#define get_DPTX_CTSFIFO_RSV1_reg   (*((volatile unsigned int*) DPTX_CTSFIFO_RSV1_reg))
#define DPTX_CTSFIFO_RSV1_inst_adr                                                   "0x00D8"
#define DPTX_CTSFIFO_RSV1_inst                                                       0x00D8
#define DPTX_CTSFIFO_RSV1_dptx_ctsfifo_rsv1_shift                                    (0)
#define DPTX_CTSFIFO_RSV1_dptx_ctsfifo_rsv1_mask                                     (0x000000FF)
#define DPTX_CTSFIFO_RSV1_dptx_ctsfifo_rsv1(data)                                    (0x000000FF&((data)<<0))
#define DPTX_CTSFIFO_RSV1_dptx_ctsfifo_rsv1_src(data)                                ((0x000000FF&(data))>>0)
#define DPTX_CTSFIFO_RSV1_get_dptx_ctsfifo_rsv1(data)                                ((0x000000FF&(data))>>0)


#define DPTX_TOP_CTL                                                                 0x9803D364
#define DPTX_TOP_CTL_reg_addr                                                        "0x9803D364"
#define DPTX_TOP_CTL_reg                                                             0x9803D364
#define set_DPTX_TOP_CTL_reg(data)   (*((volatile unsigned int*) DPTX_TOP_CTL_reg)=data)
#define get_DPTX_TOP_CTL_reg   (*((volatile unsigned int*) DPTX_TOP_CTL_reg))
#define DPTX_TOP_CTL_inst_adr                                                        "0x00D9"
#define DPTX_TOP_CTL_inst                                                            0x00D9
#define DPTX_TOP_CTL_Reserved_shift                                                  (2)
#define DPTX_TOP_CTL_Reserved_mask                                                   (0x000000FC)
#define DPTX_TOP_CTL_Reserved(data)                                                  (0x000000FC&((data)<<2))
#define DPTX_TOP_CTL_Reserved_src(data)                                              ((0x000000FC&(data))>>2)
#define DPTX_TOP_CTL_get_Reserved(data)                                              ((0x000000FC&(data))>>2)
#define DPTX_TOP_CTL_dptx_vesa_source_shift                                          (1)
#define DPTX_TOP_CTL_dptx_vesa_source_mask                                           (0x00000002)
#define DPTX_TOP_CTL_dptx_vesa_source(data)                                          (0x00000002&((data)<<1))
#define DPTX_TOP_CTL_dptx_vesa_source_src(data)                                      ((0x00000002&(data))>>1)
#define DPTX_TOP_CTL_get_dptx_vesa_source(data)                                      ((0x00000002&(data))>>1)
#define DPTX_TOP_CTL_dptx_source_shift                                               (0)
#define DPTX_TOP_CTL_dptx_source_mask                                                (0x00000001)
#define DPTX_TOP_CTL_dptx_source(data)                                               (0x00000001&((data)<<0))
#define DPTX_TOP_CTL_dptx_source_src(data)                                           ((0x00000001&(data))>>0)
#define DPTX_TOP_CTL_get_dptx_source(data)                                           ((0x00000001&(data))>>0)


#define DPTX_TOP_RSV1                                                                0x9803D368
#define DPTX_TOP_RSV1_reg_addr                                                       "0x9803D368"
#define DPTX_TOP_RSV1_reg                                                            0x9803D368
#define set_DPTX_TOP_RSV1_reg(data)   (*((volatile unsigned int*) DPTX_TOP_RSV1_reg)=data)
#define get_DPTX_TOP_RSV1_reg   (*((volatile unsigned int*) DPTX_TOP_RSV1_reg))
#define DPTX_TOP_RSV1_inst_adr                                                       "0x00DA"
#define DPTX_TOP_RSV1_inst                                                           0x00DA
#define DPTX_TOP_RSV1_dptx_rsv1_shift                                                (0)
#define DPTX_TOP_RSV1_dptx_rsv1_mask                                                 (0x000000FF)
#define DPTX_TOP_RSV1_dptx_rsv1(data)                                                (0x000000FF&((data)<<0))
#define DPTX_TOP_RSV1_dptx_rsv1_src(data)                                            ((0x000000FF&(data))>>0)
#define DPTX_TOP_RSV1_get_dptx_rsv1(data)                                            ((0x000000FF&(data))>>0)


#define DPTX_TOP_RSV2                                                                0x9803D36C
#define DPTX_TOP_RSV2_reg_addr                                                       "0x9803D36C"
#define DPTX_TOP_RSV2_reg                                                            0x9803D36C
#define set_DPTX_TOP_RSV2_reg(data)   (*((volatile unsigned int*) DPTX_TOP_RSV2_reg)=data)
#define get_DPTX_TOP_RSV2_reg   (*((volatile unsigned int*) DPTX_TOP_RSV2_reg))
#define DPTX_TOP_RSV2_inst_adr                                                       "0x00DB"
#define DPTX_TOP_RSV2_inst                                                           0x00DB
#define DPTX_TOP_RSV2_dptx_rsv2_shift                                                (0)
#define DPTX_TOP_RSV2_dptx_rsv2_mask                                                 (0x000000FF)
#define DPTX_TOP_RSV2_dptx_rsv2(data)                                                (0x000000FF&((data)<<0))
#define DPTX_TOP_RSV2_dptx_rsv2_src(data)                                            ((0x000000FF&(data))>>0)
#define DPTX_TOP_RSV2_get_dptx_rsv2(data)                                            ((0x000000FF&(data))>>0)


#define ARBITER_MIN_H_BLANK_WIDTH_HB                                                 0x9803D370
#define ARBITER_MIN_H_BLANK_WIDTH_HB_reg_addr                                        "0x9803D370"
#define ARBITER_MIN_H_BLANK_WIDTH_HB_reg                                             0x9803D370
#define set_ARBITER_MIN_H_BLANK_WIDTH_HB_reg(data)   (*((volatile unsigned int*) ARBITER_MIN_H_BLANK_WIDTH_HB_reg)=data)
#define get_ARBITER_MIN_H_BLANK_WIDTH_HB_reg   (*((volatile unsigned int*) ARBITER_MIN_H_BLANK_WIDTH_HB_reg))
#define ARBITER_MIN_H_BLANK_WIDTH_HB_inst_adr                                        "0x00DC"
#define ARBITER_MIN_H_BLANK_WIDTH_HB_inst                                            0x00DC
#define ARBITER_MIN_H_BLANK_WIDTH_HB_min_h_blank_width_clr_shift                     (7)
#define ARBITER_MIN_H_BLANK_WIDTH_HB_min_h_blank_width_clr_mask                      (0x00000080)
#define ARBITER_MIN_H_BLANK_WIDTH_HB_min_h_blank_width_clr(data)                     (0x00000080&((data)<<7))
#define ARBITER_MIN_H_BLANK_WIDTH_HB_min_h_blank_width_clr_src(data)                 ((0x00000080&(data))>>7)
#define ARBITER_MIN_H_BLANK_WIDTH_HB_get_min_h_blank_width_clr(data)                 ((0x00000080&(data))>>7)
#define ARBITER_MIN_H_BLANK_WIDTH_HB_min_h_blank_width148_shift                      (0)
#define ARBITER_MIN_H_BLANK_WIDTH_HB_min_h_blank_width148_mask                       (0x0000007F)
#define ARBITER_MIN_H_BLANK_WIDTH_HB_min_h_blank_width148(data)                      (0x0000007F&((data)<<0))
#define ARBITER_MIN_H_BLANK_WIDTH_HB_min_h_blank_width148_src(data)                  ((0x0000007F&(data))>>0)
#define ARBITER_MIN_H_BLANK_WIDTH_HB_get_min_h_blank_width148(data)                  ((0x0000007F&(data))>>0)


#define ARBITER_MIN_H_BLANK_WIDTH_LB                                                 0x9803D374
#define ARBITER_MIN_H_BLANK_WIDTH_LB_reg_addr                                        "0x9803D374"
#define ARBITER_MIN_H_BLANK_WIDTH_LB_reg                                             0x9803D374
#define set_ARBITER_MIN_H_BLANK_WIDTH_LB_reg(data)   (*((volatile unsigned int*) ARBITER_MIN_H_BLANK_WIDTH_LB_reg)=data)
#define get_ARBITER_MIN_H_BLANK_WIDTH_LB_reg   (*((volatile unsigned int*) ARBITER_MIN_H_BLANK_WIDTH_LB_reg))
#define ARBITER_MIN_H_BLANK_WIDTH_LB_inst_adr                                        "0x00DD"
#define ARBITER_MIN_H_BLANK_WIDTH_LB_inst                                            0x00DD
#define ARBITER_MIN_H_BLANK_WIDTH_LB_min_h_blank_width70_shift                       (0)
#define ARBITER_MIN_H_BLANK_WIDTH_LB_min_h_blank_width70_mask                        (0x000000FF)
#define ARBITER_MIN_H_BLANK_WIDTH_LB_min_h_blank_width70(data)                       (0x000000FF&((data)<<0))
#define ARBITER_MIN_H_BLANK_WIDTH_LB_min_h_blank_width70_src(data)                   ((0x000000FF&(data))>>0)
#define ARBITER_MIN_H_BLANK_WIDTH_LB_get_min_h_blank_width70(data)                   ((0x000000FF&(data))>>0)


#define ARBITER_INTERRUPT_CTRL                                                       0x9803D378
#define ARBITER_INTERRUPT_CTRL_reg_addr                                              "0x9803D378"
#define ARBITER_INTERRUPT_CTRL_reg                                                   0x9803D378
#define set_ARBITER_INTERRUPT_CTRL_reg(data)   (*((volatile unsigned int*) ARBITER_INTERRUPT_CTRL_reg)=data)
#define get_ARBITER_INTERRUPT_CTRL_reg   (*((volatile unsigned int*) ARBITER_INTERRUPT_CTRL_reg))
#define ARBITER_INTERRUPT_CTRL_inst_adr                                              "0x00DE"
#define ARBITER_INTERRUPT_CTRL_inst                                                  0x00DE
#define ARBITER_INTERRUPT_CTRL_Reserved_shift                                        (3)
#define ARBITER_INTERRUPT_CTRL_Reserved_mask                                         (0x000000F8)
#define ARBITER_INTERRUPT_CTRL_Reserved(data)                                        (0x000000F8&((data)<<3))
#define ARBITER_INTERRUPT_CTRL_Reserved_src(data)                                    ((0x000000F8&(data))>>3)
#define ARBITER_INTERRUPT_CTRL_get_Reserved(data)                                    ((0x000000F8&(data))>>3)
#define ARBITER_INTERRUPT_CTRL_den_line_end_occur_int_en_shift                       (2)
#define ARBITER_INTERRUPT_CTRL_den_line_end_occur_int_en_mask                        (0x00000004)
#define ARBITER_INTERRUPT_CTRL_den_line_end_occur_int_en(data)                       (0x00000004&((data)<<2))
#define ARBITER_INTERRUPT_CTRL_den_line_end_occur_int_en_src(data)                   ((0x00000004&(data))>>2)
#define ARBITER_INTERRUPT_CTRL_get_den_line_end_occur_int_en(data)                   ((0x00000004&(data))>>2)
#define ARBITER_INTERRUPT_CTRL_sec_tx_end_nv_miss_int_en_shift                       (1)
#define ARBITER_INTERRUPT_CTRL_sec_tx_end_nv_miss_int_en_mask                        (0x00000002)
#define ARBITER_INTERRUPT_CTRL_sec_tx_end_nv_miss_int_en(data)                       (0x00000002&((data)<<1))
#define ARBITER_INTERRUPT_CTRL_sec_tx_end_nv_miss_int_en_src(data)                   ((0x00000002&(data))>>1)
#define ARBITER_INTERRUPT_CTRL_get_sec_tx_end_nv_miss_int_en(data)                   ((0x00000002&(data))>>1)
#define ARBITER_INTERRUPT_CTRL_sec_tx_end_v_miss_int_en_shift                        (0)
#define ARBITER_INTERRUPT_CTRL_sec_tx_end_v_miss_int_en_mask                         (0x00000001)
#define ARBITER_INTERRUPT_CTRL_sec_tx_end_v_miss_int_en(data)                        (0x00000001&((data)<<0))
#define ARBITER_INTERRUPT_CTRL_sec_tx_end_v_miss_int_en_src(data)                    ((0x00000001&(data))>>0)
#define ARBITER_INTERRUPT_CTRL_get_sec_tx_end_v_miss_int_en(data)                    ((0x00000001&(data))>>0)


#define VESA_FMT_REGEN                                                               0x9803D37C
#define VESA_FMT_REGEN_reg_addr                                                      "0x9803D37C"
#define VESA_FMT_REGEN_reg                                                           0x9803D37C
#define set_VESA_FMT_REGEN_reg(data)   (*((volatile unsigned int*) VESA_FMT_REGEN_reg)=data)
#define get_VESA_FMT_REGEN_reg   (*((volatile unsigned int*) VESA_FMT_REGEN_reg))
#define VESA_FMT_REGEN_inst_adr                                                      "0x00DF"
#define VESA_FMT_REGEN_inst                                                          0x00DF
#define VESA_FMT_REGEN_Reserved_shift                                                (2)
#define VESA_FMT_REGEN_Reserved_mask                                                 (0x000000FC)
#define VESA_FMT_REGEN_Reserved(data)                                                (0x000000FC&((data)<<2))
#define VESA_FMT_REGEN_Reserved_src(data)                                            ((0x000000FC&(data))>>2)
#define VESA_FMT_REGEN_get_Reserved(data)                                            ((0x000000FC&(data))>>2)
#define VESA_FMT_REGEN_measure_bypass_en_shift                                       (1)
#define VESA_FMT_REGEN_measure_bypass_en_mask                                        (0x00000002)
#define VESA_FMT_REGEN_measure_bypass_en(data)                                       (0x00000002&((data)<<1))
#define VESA_FMT_REGEN_measure_bypass_en_src(data)                                   ((0x00000002&(data))>>1)
#define VESA_FMT_REGEN_get_measure_bypass_en(data)                                   ((0x00000002&(data))>>1)
#define VESA_FMT_REGEN_vesa_fmt_regen_en_shift                                       (0)
#define VESA_FMT_REGEN_vesa_fmt_regen_en_mask                                        (0x00000001)
#define VESA_FMT_REGEN_vesa_fmt_regen_en(data)                                       (0x00000001&((data)<<0))
#define VESA_FMT_REGEN_vesa_fmt_regen_en_src(data)                                   ((0x00000001&(data))>>0)
#define VESA_FMT_REGEN_get_vesa_fmt_regen_en(data)                                   ((0x00000001&(data))>>0)


#define DPTX_CLK_GEN                                                                 0x9803D380
#define DPTX_CLK_GEN_reg_addr                                                        "0x9803D380"
#define DPTX_CLK_GEN_reg                                                             0x9803D380
#define set_DPTX_CLK_GEN_reg(data)   (*((volatile unsigned int*) DPTX_CLK_GEN_reg)=data)
#define get_DPTX_CLK_GEN_reg   (*((volatile unsigned int*) DPTX_CLK_GEN_reg))
#define DPTX_CLK_GEN_inst_adr                                                        "0x00E0"
#define DPTX_CLK_GEN_inst                                                            0x00E0
#define DPTX_CLK_GEN_ckrd_sel_shift                                                  (6)
#define DPTX_CLK_GEN_ckrd_sel_mask                                                   (0x000000C0)
#define DPTX_CLK_GEN_ckrd_sel(data)                                                  (0x000000C0&((data)<<6))
#define DPTX_CLK_GEN_ckrd_sel_src(data)                                              ((0x000000C0&(data))>>6)
#define DPTX_CLK_GEN_get_ckrd_sel(data)                                              ((0x000000C0&(data))>>6)
#define DPTX_CLK_GEN_ckrd_sel_post_shift                                             (5)
#define DPTX_CLK_GEN_ckrd_sel_post_mask                                              (0x00000020)
#define DPTX_CLK_GEN_ckrd_sel_post(data)                                             (0x00000020&((data)<<5))
#define DPTX_CLK_GEN_ckrd_sel_post_src(data)                                         ((0x00000020&(data))>>5)
#define DPTX_CLK_GEN_get_ckrd_sel_post(data)                                         ((0x00000020&(data))>>5)
#define DPTX_CLK_GEN_div_num_shift                                                   (0)
#define DPTX_CLK_GEN_div_num_mask                                                    (0x0000001F)
#define DPTX_CLK_GEN_div_num(data)                                                   (0x0000001F&((data)<<0))
#define DPTX_CLK_GEN_div_num_src(data)                                               ((0x0000001F&(data))>>0)
#define DPTX_CLK_GEN_get_div_num(data)                                               ((0x0000001F&(data))>>0)


#define PG_MBIST_CTRL                                                                0x9803D384
#define PG_MBIST_CTRL_reg_addr                                                       "0x9803D384"
#define PG_MBIST_CTRL_reg                                                            0x9803D384
#define set_PG_MBIST_CTRL_reg(data)   (*((volatile unsigned int*) PG_MBIST_CTRL_reg)=data)
#define get_PG_MBIST_CTRL_reg   (*((volatile unsigned int*) PG_MBIST_CTRL_reg))
#define PG_MBIST_CTRL_inst_adr                                                       "0x00E1"
#define PG_MBIST_CTRL_inst                                                           0x00E1
#define PG_MBIST_CTRL_bist_mode_pg_shift                                             (7)
#define PG_MBIST_CTRL_bist_mode_pg_mask                                              (0x00000080)
#define PG_MBIST_CTRL_bist_mode_pg(data)                                             (0x00000080&((data)<<7))
#define PG_MBIST_CTRL_bist_mode_pg_src(data)                                         ((0x00000080&(data))>>7)
#define PG_MBIST_CTRL_get_bist_mode_pg(data)                                         ((0x00000080&(data))>>7)
#define PG_MBIST_CTRL_bist_done_pg_shift                                             (6)
#define PG_MBIST_CTRL_bist_done_pg_mask                                              (0x00000040)
#define PG_MBIST_CTRL_bist_done_pg(data)                                             (0x00000040&((data)<<6))
#define PG_MBIST_CTRL_bist_done_pg_src(data)                                         ((0x00000040&(data))>>6)
#define PG_MBIST_CTRL_get_bist_done_pg(data)                                         ((0x00000040&(data))>>6)
#define PG_MBIST_CTRL_bist_fail_pg_shift                                             (5)
#define PG_MBIST_CTRL_bist_fail_pg_mask                                              (0x00000020)
#define PG_MBIST_CTRL_bist_fail_pg(data)                                             (0x00000020&((data)<<5))
#define PG_MBIST_CTRL_bist_fail_pg_src(data)                                         ((0x00000020&(data))>>5)
#define PG_MBIST_CTRL_get_bist_fail_pg(data)                                         ((0x00000020&(data))>>5)
#define PG_MBIST_CTRL_dvse_pg_shift                                                  (4)
#define PG_MBIST_CTRL_dvse_pg_mask                                                   (0x00000010)
#define PG_MBIST_CTRL_dvse_pg(data)                                                  (0x00000010&((data)<<4))
#define PG_MBIST_CTRL_dvse_pg_src(data)                                              ((0x00000010&(data))>>4)
#define PG_MBIST_CTRL_get_dvse_pg(data)                                              ((0x00000010&(data))>>4)
#define PG_MBIST_CTRL_dvs_pg_shift                                                   (0)
#define PG_MBIST_CTRL_dvs_pg_mask                                                    (0x0000000F)
#define PG_MBIST_CTRL_dvs_pg(data)                                                   (0x0000000F&((data)<<0))
#define PG_MBIST_CTRL_dvs_pg_src(data)                                               ((0x0000000F&(data))>>0)
#define PG_MBIST_CTRL_get_dvs_pg(data)                                               ((0x0000000F&(data))>>0)


#define PG_DRF_MBIST_CTRL                                                            0x9803D388
#define PG_DRF_MBIST_CTRL_reg_addr                                                   "0x9803D388"
#define PG_DRF_MBIST_CTRL_reg                                                        0x9803D388
#define set_PG_DRF_MBIST_CTRL_reg(data)   (*((volatile unsigned int*) PG_DRF_MBIST_CTRL_reg)=data)
#define get_PG_DRF_MBIST_CTRL_reg   (*((volatile unsigned int*) PG_DRF_MBIST_CTRL_reg))
#define PG_DRF_MBIST_CTRL_inst_adr                                                   "0x00E2"
#define PG_DRF_MBIST_CTRL_inst                                                       0x00E2
#define PG_DRF_MBIST_CTRL_drf_bist_mode_pg_shift                                     (7)
#define PG_DRF_MBIST_CTRL_drf_bist_mode_pg_mask                                      (0x00000080)
#define PG_DRF_MBIST_CTRL_drf_bist_mode_pg(data)                                     (0x00000080&((data)<<7))
#define PG_DRF_MBIST_CTRL_drf_bist_mode_pg_src(data)                                 ((0x00000080&(data))>>7)
#define PG_DRF_MBIST_CTRL_get_drf_bist_mode_pg(data)                                 ((0x00000080&(data))>>7)
#define PG_DRF_MBIST_CTRL_drf_test_resume_pg_shift                                   (6)
#define PG_DRF_MBIST_CTRL_drf_test_resume_pg_mask                                    (0x00000040)
#define PG_DRF_MBIST_CTRL_drf_test_resume_pg(data)                                   (0x00000040&((data)<<6))
#define PG_DRF_MBIST_CTRL_drf_test_resume_pg_src(data)                               ((0x00000040&(data))>>6)
#define PG_DRF_MBIST_CTRL_get_drf_test_resume_pg(data)                               ((0x00000040&(data))>>6)
#define PG_DRF_MBIST_CTRL_drf_start_pause_pg_shift                                   (5)
#define PG_DRF_MBIST_CTRL_drf_start_pause_pg_mask                                    (0x00000020)
#define PG_DRF_MBIST_CTRL_drf_start_pause_pg(data)                                   (0x00000020&((data)<<5))
#define PG_DRF_MBIST_CTRL_drf_start_pause_pg_src(data)                               ((0x00000020&(data))>>5)
#define PG_DRF_MBIST_CTRL_get_drf_start_pause_pg(data)                               ((0x00000020&(data))>>5)
#define PG_DRF_MBIST_CTRL_drf_bist_done_pg_shift                                     (4)
#define PG_DRF_MBIST_CTRL_drf_bist_done_pg_mask                                      (0x00000010)
#define PG_DRF_MBIST_CTRL_drf_bist_done_pg(data)                                     (0x00000010&((data)<<4))
#define PG_DRF_MBIST_CTRL_drf_bist_done_pg_src(data)                                 ((0x00000010&(data))>>4)
#define PG_DRF_MBIST_CTRL_get_drf_bist_done_pg(data)                                 ((0x00000010&(data))>>4)
#define PG_DRF_MBIST_CTRL_drf_bist_fail_pg_shift                                     (3)
#define PG_DRF_MBIST_CTRL_drf_bist_fail_pg_mask                                      (0x00000008)
#define PG_DRF_MBIST_CTRL_drf_bist_fail_pg(data)                                     (0x00000008&((data)<<3))
#define PG_DRF_MBIST_CTRL_drf_bist_fail_pg_src(data)                                 ((0x00000008&(data))>>3)
#define PG_DRF_MBIST_CTRL_get_drf_bist_fail_pg(data)                                 ((0x00000008&(data))>>3)
#define PG_DRF_MBIST_CTRL_Reserved_shift                                             (2)
#define PG_DRF_MBIST_CTRL_Reserved_mask                                              (0x00000004)
#define PG_DRF_MBIST_CTRL_Reserved(data)                                             (0x00000004&((data)<<2))
#define PG_DRF_MBIST_CTRL_Reserved_src(data)                                         ((0x00000004&(data))>>2)
#define PG_DRF_MBIST_CTRL_get_Reserved(data)                                         ((0x00000004&(data))>>2)
#define PG_DRF_MBIST_CTRL_bist_clk_en_pg_shift                                       (1)
#define PG_DRF_MBIST_CTRL_bist_clk_en_pg_mask                                        (0x00000002)
#define PG_DRF_MBIST_CTRL_bist_clk_en_pg(data)                                       (0x00000002&((data)<<1))
#define PG_DRF_MBIST_CTRL_bist_clk_en_pg_src(data)                                   ((0x00000002&(data))>>1)
#define PG_DRF_MBIST_CTRL_get_bist_clk_en_pg(data)                                   ((0x00000002&(data))>>1)
#define PG_DRF_MBIST_CTRL_bist_rst_pg_shift                                          (0)
#define PG_DRF_MBIST_CTRL_bist_rst_pg_mask                                           (0x00000001)
#define PG_DRF_MBIST_CTRL_bist_rst_pg(data)                                          (0x00000001&((data)<<0))
#define PG_DRF_MBIST_CTRL_bist_rst_pg_src(data)                                      ((0x00000001&(data))>>0)
#define PG_DRF_MBIST_CTRL_get_bist_rst_pg(data)                                      ((0x00000001&(data))>>0)


#define ARBITER_SEC_IDLE_END_CNT                                                     0x9803D3C0
#define ARBITER_SEC_IDLE_END_CNT_reg_addr                                            "0x9803D3C0"
#define ARBITER_SEC_IDLE_END_CNT_reg                                                 0x9803D3C0
#define set_ARBITER_SEC_IDLE_END_CNT_reg(data)   (*((volatile unsigned int*) ARBITER_SEC_IDLE_END_CNT_reg)=data)
#define get_ARBITER_SEC_IDLE_END_CNT_reg   (*((volatile unsigned int*) ARBITER_SEC_IDLE_END_CNT_reg))
#define ARBITER_SEC_IDLE_END_CNT_inst_adr                                            "0x00F0"
#define ARBITER_SEC_IDLE_END_CNT_inst                                                0x00F0
#define ARBITER_SEC_IDLE_END_CNT_sec_idle_end_cnt_shift                              (0)
#define ARBITER_SEC_IDLE_END_CNT_sec_idle_end_cnt_mask                               (0x000000FF)
#define ARBITER_SEC_IDLE_END_CNT_sec_idle_end_cnt(data)                              (0x000000FF&((data)<<0))
#define ARBITER_SEC_IDLE_END_CNT_sec_idle_end_cnt_src(data)                          ((0x000000FF&(data))>>0)
#define ARBITER_SEC_IDLE_END_CNT_get_sec_idle_end_cnt(data)                          ((0x000000FF&(data))>>0)


#define DPTX_TOP_RSV3                                                                0x9803D3E0
#define DPTX_TOP_RSV3_reg_addr                                                       "0x9803D3E0"
#define DPTX_TOP_RSV3_reg                                                            0x9803D3E0
#define set_DPTX_TOP_RSV3_reg(data)   (*((volatile unsigned int*) DPTX_TOP_RSV3_reg)=data)
#define get_DPTX_TOP_RSV3_reg   (*((volatile unsigned int*) DPTX_TOP_RSV3_reg))
#define DPTX_TOP_RSV3_inst_adr                                                       "0x00F8"
#define DPTX_TOP_RSV3_inst                                                           0x00F8
#define DPTX_TOP_RSV3_Dummy_shift                                                    (2)
#define DPTX_TOP_RSV3_Dummy_mask                                                     (0x000000FC)
#define DPTX_TOP_RSV3_Dummy(data)                                                    (0x000000FC&((data)<<2))
#define DPTX_TOP_RSV3_Dummy_src(data)                                                ((0x000000FC&(data))>>2)
#define DPTX_TOP_RSV3_get_Dummy(data)                                                ((0x000000FC&(data))>>2)
#define DPTX_TOP_RSV3_field_inv_shift                                                (1)
#define DPTX_TOP_RSV3_field_inv_mask                                                 (0x00000002)
#define DPTX_TOP_RSV3_field_inv(data)                                                (0x00000002&((data)<<1))
#define DPTX_TOP_RSV3_field_inv_src(data)                                            ((0x00000002&(data))>>1)
#define DPTX_TOP_RSV3_get_field_inv(data)                                            ((0x00000002&(data))>>1)
#define DPTX_TOP_RSV3_field_md_shift                                                 (0)
#define DPTX_TOP_RSV3_field_md_mask                                                  (0x00000001)
#define DPTX_TOP_RSV3_field_md(data)                                                 (0x00000001&((data)<<0))
#define DPTX_TOP_RSV3_field_md_src(data)                                             ((0x00000001&(data))>>0)
#define DPTX_TOP_RSV3_get_field_md(data)                                             ((0x00000001&(data))>>0)


#define DPTX_TOP_RSV4                                                                0x9803D3E4
#define DPTX_TOP_RSV4_reg_addr                                                       "0x9803D3E4"
#define DPTX_TOP_RSV4_reg                                                            0x9803D3E4
#define set_DPTX_TOP_RSV4_reg(data)   (*((volatile unsigned int*) DPTX_TOP_RSV4_reg)=data)
#define get_DPTX_TOP_RSV4_reg   (*((volatile unsigned int*) DPTX_TOP_RSV4_reg))
#define DPTX_TOP_RSV4_inst_adr                                                       "0x00F9"
#define DPTX_TOP_RSV4_inst                                                           0x00F9
#define DPTX_TOP_RSV4_Dummy_shift                                                    (0)
#define DPTX_TOP_RSV4_Dummy_mask                                                     (0x000000FF)
#define DPTX_TOP_RSV4_Dummy(data)                                                    (0x000000FF&((data)<<0))
#define DPTX_TOP_RSV4_Dummy_src(data)                                                ((0x000000FF&(data))>>0)
#define DPTX_TOP_RSV4_get_Dummy(data)                                                ((0x000000FF&(data))>>0)


#define DPTX_TOP_RSV5                                                                0x9803D3E8
#define DPTX_TOP_RSV5_reg_addr                                                       "0x9803D3E8"
#define DPTX_TOP_RSV5_reg                                                            0x9803D3E8
#define set_DPTX_TOP_RSV5_reg(data)   (*((volatile unsigned int*) DPTX_TOP_RSV5_reg)=data)
#define get_DPTX_TOP_RSV5_reg   (*((volatile unsigned int*) DPTX_TOP_RSV5_reg))
#define DPTX_TOP_RSV5_inst_adr                                                       "0x00FA"
#define DPTX_TOP_RSV5_inst                                                           0x00FA
#define DPTX_TOP_RSV5_Dummy_shift                                                    (0)
#define DPTX_TOP_RSV5_Dummy_mask                                                     (0x000000FF)
#define DPTX_TOP_RSV5_Dummy(data)                                                    (0x000000FF&((data)<<0))
#define DPTX_TOP_RSV5_Dummy_src(data)                                                ((0x000000FF&(data))>>0)
#define DPTX_TOP_RSV5_get_Dummy(data)                                                ((0x000000FF&(data))>>0)


#define DPTX_TOP_RSV6                                                                0x9803D3EC
#define DPTX_TOP_RSV6_reg_addr                                                       "0x9803D3EC"
#define DPTX_TOP_RSV6_reg                                                            0x9803D3EC
#define set_DPTX_TOP_RSV6_reg(data)   (*((volatile unsigned int*) DPTX_TOP_RSV6_reg)=data)
#define get_DPTX_TOP_RSV6_reg   (*((volatile unsigned int*) DPTX_TOP_RSV6_reg))
#define DPTX_TOP_RSV6_inst_adr                                                       "0x00FB"
#define DPTX_TOP_RSV6_inst                                                           0x00FB
#define DPTX_TOP_RSV6_Dummy_shift                                                    (0)
#define DPTX_TOP_RSV6_Dummy_mask                                                     (0x000000FF)
#define DPTX_TOP_RSV6_Dummy(data)                                                    (0x000000FF&((data)<<0))
#define DPTX_TOP_RSV6_Dummy_src(data)                                                ((0x000000FF&(data))>>0)
#define DPTX_TOP_RSV6_get_Dummy(data)                                                ((0x000000FF&(data))>>0)


#define DPTX_TOP_RSV7                                                                0x9803D3F0
#define DPTX_TOP_RSV7_reg_addr                                                       "0x9803D3F0"
#define DPTX_TOP_RSV7_reg                                                            0x9803D3F0
#define set_DPTX_TOP_RSV7_reg(data)   (*((volatile unsigned int*) DPTX_TOP_RSV7_reg)=data)
#define get_DPTX_TOP_RSV7_reg   (*((volatile unsigned int*) DPTX_TOP_RSV7_reg))
#define DPTX_TOP_RSV7_inst_adr                                                       "0x00FC"
#define DPTX_TOP_RSV7_inst                                                           0x00FC
#define DPTX_TOP_RSV7_Dummy_shift                                                    (0)
#define DPTX_TOP_RSV7_Dummy_mask                                                     (0x000000FF)
#define DPTX_TOP_RSV7_Dummy(data)                                                    (0x000000FF&((data)<<0))
#define DPTX_TOP_RSV7_Dummy_src(data)                                                ((0x000000FF&(data))>>0)
#define DPTX_TOP_RSV7_get_Dummy(data)                                                ((0x000000FF&(data))>>0)


#define DPTX_TOP_RSV8                                                                0x9803D3F4
#define DPTX_TOP_RSV8_reg_addr                                                       "0x9803D3F4"
#define DPTX_TOP_RSV8_reg                                                            0x9803D3F4
#define set_DPTX_TOP_RSV8_reg(data)   (*((volatile unsigned int*) DPTX_TOP_RSV8_reg)=data)
#define get_DPTX_TOP_RSV8_reg   (*((volatile unsigned int*) DPTX_TOP_RSV8_reg))
#define DPTX_TOP_RSV8_inst_adr                                                       "0x00FD"
#define DPTX_TOP_RSV8_inst                                                           0x00FD
#define DPTX_TOP_RSV8_Dummy_shift                                                    (0)
#define DPTX_TOP_RSV8_Dummy_mask                                                     (0x000000FF)
#define DPTX_TOP_RSV8_Dummy(data)                                                    (0x000000FF&((data)<<0))
#define DPTX_TOP_RSV8_Dummy_src(data)                                                ((0x000000FF&(data))>>0)
#define DPTX_TOP_RSV8_get_Dummy(data)                                                ((0x000000FF&(data))>>0)


#define DPTX_TOP_RSV9                                                                0x9803D3F8
#define DPTX_TOP_RSV9_reg_addr                                                       "0x9803D3F8"
#define DPTX_TOP_RSV9_reg                                                            0x9803D3F8
#define set_DPTX_TOP_RSV9_reg(data)   (*((volatile unsigned int*) DPTX_TOP_RSV9_reg)=data)
#define get_DPTX_TOP_RSV9_reg   (*((volatile unsigned int*) DPTX_TOP_RSV9_reg))
#define DPTX_TOP_RSV9_inst_adr                                                       "0x00FE"
#define DPTX_TOP_RSV9_inst                                                           0x00FE
#define DPTX_TOP_RSV9_Dummy_shift                                                    (0)
#define DPTX_TOP_RSV9_Dummy_mask                                                     (0x000000FF)
#define DPTX_TOP_RSV9_Dummy(data)                                                    (0x000000FF&((data)<<0))
#define DPTX_TOP_RSV9_Dummy_src(data)                                                ((0x000000FF&(data))>>0)
#define DPTX_TOP_RSV9_get_Dummy(data)                                                ((0x000000FF&(data))>>0)


#define DPTX_TOP_RSV10                                                               0x9803D3FC
#define DPTX_TOP_RSV10_reg_addr                                                      "0x9803D3FC"
#define DPTX_TOP_RSV10_reg                                                           0x9803D3FC
#define set_DPTX_TOP_RSV10_reg(data)   (*((volatile unsigned int*) DPTX_TOP_RSV10_reg)=data)
#define get_DPTX_TOP_RSV10_reg   (*((volatile unsigned int*) DPTX_TOP_RSV10_reg))
#define DPTX_TOP_RSV10_inst_adr                                                      "0x00FF"
#define DPTX_TOP_RSV10_inst                                                          0x00FF
#define DPTX_TOP_RSV10_Dummy_shift                                                   (0)
#define DPTX_TOP_RSV10_Dummy_mask                                                    (0x000000FF)
#define DPTX_TOP_RSV10_Dummy(data)                                                   (0x000000FF&((data)<<0))
#define DPTX_TOP_RSV10_Dummy_src(data)                                               ((0x000000FF&(data))>>0)
#define DPTX_TOP_RSV10_get_Dummy(data)                                               ((0x000000FF&(data))>>0)


#define DP_PHY_CTRL                                                                  0x9803D000
#define DP_PHY_CTRL_reg_addr                                                         "0x9803D000"
#define DP_PHY_CTRL_reg                                                              0x9803D000
#define set_DP_PHY_CTRL_reg(data)   (*((volatile unsigned int*) DP_PHY_CTRL_reg)=data)
#define get_DP_PHY_CTRL_reg   (*((volatile unsigned int*) DP_PHY_CTRL_reg))
#define DP_PHY_CTRL_inst_adr                                                         "0x0000"
#define DP_PHY_CTRL_inst                                                             0x0000
#define DP_PHY_CTRL_v2analog_shift                                                   (4)
#define DP_PHY_CTRL_v2analog_mask                                                    (0x000000F0)
#define DP_PHY_CTRL_v2analog(data)                                                   (0x000000F0&((data)<<4))
#define DP_PHY_CTRL_v2analog_src(data)                                               ((0x000000F0&(data))>>4)
#define DP_PHY_CTRL_get_v2analog(data)                                               ((0x000000F0&(data))>>4)
#define DP_PHY_CTRL_lane_num_shift                                                   (2)
#define DP_PHY_CTRL_lane_num_mask                                                    (0x0000000C)
#define DP_PHY_CTRL_lane_num(data)                                                   (0x0000000C&((data)<<2))
#define DP_PHY_CTRL_lane_num_src(data)                                               ((0x0000000C&(data))>>2)
#define DP_PHY_CTRL_get_lane_num(data)                                               ((0x0000000C&(data))>>2)
#define DP_PHY_CTRL_mst_en_shift                                                     (1)
#define DP_PHY_CTRL_mst_en_mask                                                      (0x00000002)
#define DP_PHY_CTRL_mst_en(data)                                                     (0x00000002&((data)<<1))
#define DP_PHY_CTRL_mst_en_src(data)                                                 ((0x00000002&(data))>>1)
#define DP_PHY_CTRL_get_mst_en(data)                                                 ((0x00000002&(data))>>1)
#define DP_PHY_CTRL_phy_reset_shift                                                  (0)
#define DP_PHY_CTRL_phy_reset_mask                                                   (0x00000001)
#define DP_PHY_CTRL_phy_reset(data)                                                  (0x00000001&((data)<<0))
#define DP_PHY_CTRL_phy_reset_src(data)                                              ((0x00000001&(data))>>0)
#define DP_PHY_CTRL_get_phy_reset(data)                                              ((0x00000001&(data))>>0)


#define DPTX_ML_PAT_SEL                                                              0x9803D004
#define DPTX_ML_PAT_SEL_reg_addr                                                     "0x9803D004"
#define DPTX_ML_PAT_SEL_reg                                                          0x9803D004
#define set_DPTX_ML_PAT_SEL_reg(data)   (*((volatile unsigned int*) DPTX_ML_PAT_SEL_reg)=data)
#define get_DPTX_ML_PAT_SEL_reg   (*((volatile unsigned int*) DPTX_ML_PAT_SEL_reg))
#define DPTX_ML_PAT_SEL_inst_adr                                                     "0x0001"
#define DPTX_ML_PAT_SEL_inst                                                         0x0001
#define DPTX_ML_PAT_SEL_tx_ml_pat_sel_shift                                          (4)
#define DPTX_ML_PAT_SEL_tx_ml_pat_sel_mask                                           (0x000000F0)
#define DPTX_ML_PAT_SEL_tx_ml_pat_sel(data)                                          (0x000000F0&((data)<<4))
#define DPTX_ML_PAT_SEL_tx_ml_pat_sel_src(data)                                      ((0x000000F0&(data))>>4)
#define DPTX_ML_PAT_SEL_get_tx_ml_pat_sel(data)                                      ((0x000000F0&(data))>>4)
#define DPTX_ML_PAT_SEL_switch_pattern_auto_shift                                    (3)
#define DPTX_ML_PAT_SEL_switch_pattern_auto_mask                                     (0x00000008)
#define DPTX_ML_PAT_SEL_switch_pattern_auto(data)                                    (0x00000008&((data)<<3))
#define DPTX_ML_PAT_SEL_switch_pattern_auto_src(data)                                ((0x00000008&(data))>>3)
#define DPTX_ML_PAT_SEL_get_switch_pattern_auto(data)                                ((0x00000008&(data))>>3)
#define DPTX_ML_PAT_SEL_prbs_reverse_shift                                           (2)
#define DPTX_ML_PAT_SEL_prbs_reverse_mask                                            (0x00000004)
#define DPTX_ML_PAT_SEL_prbs_reverse(data)                                           (0x00000004&((data)<<2))
#define DPTX_ML_PAT_SEL_prbs_reverse_src(data)                                       ((0x00000004&(data))>>2)
#define DPTX_ML_PAT_SEL_get_prbs_reverse(data)                                       ((0x00000004&(data))>>2)
#define DPTX_ML_PAT_SEL_tx_ml_pat_sel_en_shift                                       (1)
#define DPTX_ML_PAT_SEL_tx_ml_pat_sel_en_mask                                        (0x00000002)
#define DPTX_ML_PAT_SEL_tx_ml_pat_sel_en(data)                                       (0x00000002&((data)<<1))
#define DPTX_ML_PAT_SEL_tx_ml_pat_sel_en_src(data)                                   ((0x00000002&(data))>>1)
#define DPTX_ML_PAT_SEL_get_tx_ml_pat_sel_en(data)                                   ((0x00000002&(data))>>1)
#define DPTX_ML_PAT_SEL_pat_sel_dbuf_shift                                           (0)
#define DPTX_ML_PAT_SEL_pat_sel_dbuf_mask                                            (0x00000001)
#define DPTX_ML_PAT_SEL_pat_sel_dbuf(data)                                           (0x00000001&((data)<<0))
#define DPTX_ML_PAT_SEL_pat_sel_dbuf_src(data)                                       ((0x00000001&(data))>>0)
#define DPTX_ML_PAT_SEL_get_pat_sel_dbuf(data)                                       ((0x00000001&(data))>>0)


#define CUSTOM_PATTERN_0                                                             0x9803D008
#define CUSTOM_PATTERN_0_reg_addr                                                    "0x9803D008"
#define CUSTOM_PATTERN_0_reg                                                         0x9803D008
#define set_CUSTOM_PATTERN_0_reg(data)   (*((volatile unsigned int*) CUSTOM_PATTERN_0_reg)=data)
#define get_CUSTOM_PATTERN_0_reg   (*((volatile unsigned int*) CUSTOM_PATTERN_0_reg))
#define CUSTOM_PATTERN_0_inst_adr                                                    "0x0002"
#define CUSTOM_PATTERN_0_inst                                                        0x0002
#define CUSTOM_PATTERN_0_pat_byte0_shift                                             (0)
#define CUSTOM_PATTERN_0_pat_byte0_mask                                              (0x000000FF)
#define CUSTOM_PATTERN_0_pat_byte0(data)                                             (0x000000FF&((data)<<0))
#define CUSTOM_PATTERN_0_pat_byte0_src(data)                                         ((0x000000FF&(data))>>0)
#define CUSTOM_PATTERN_0_get_pat_byte0(data)                                         ((0x000000FF&(data))>>0)


#define CUSTOM_PATTERN_1                                                             0x9803D00C
#define CUSTOM_PATTERN_1_reg_addr                                                    "0x9803D00C"
#define CUSTOM_PATTERN_1_reg                                                         0x9803D00C
#define set_CUSTOM_PATTERN_1_reg(data)   (*((volatile unsigned int*) CUSTOM_PATTERN_1_reg)=data)
#define get_CUSTOM_PATTERN_1_reg   (*((volatile unsigned int*) CUSTOM_PATTERN_1_reg))
#define CUSTOM_PATTERN_1_inst_adr                                                    "0x0003"
#define CUSTOM_PATTERN_1_inst                                                        0x0003
#define CUSTOM_PATTERN_1_pat_byte1_shift                                             (0)
#define CUSTOM_PATTERN_1_pat_byte1_mask                                              (0x000000FF)
#define CUSTOM_PATTERN_1_pat_byte1(data)                                             (0x000000FF&((data)<<0))
#define CUSTOM_PATTERN_1_pat_byte1_src(data)                                         ((0x000000FF&(data))>>0)
#define CUSTOM_PATTERN_1_get_pat_byte1(data)                                         ((0x000000FF&(data))>>0)


#define CUSTOM_PATTERN_2                                                             0x9803D010
#define CUSTOM_PATTERN_2_reg_addr                                                    "0x9803D010"
#define CUSTOM_PATTERN_2_reg                                                         0x9803D010
#define set_CUSTOM_PATTERN_2_reg(data)   (*((volatile unsigned int*) CUSTOM_PATTERN_2_reg)=data)
#define get_CUSTOM_PATTERN_2_reg   (*((volatile unsigned int*) CUSTOM_PATTERN_2_reg))
#define CUSTOM_PATTERN_2_inst_adr                                                    "0x0004"
#define CUSTOM_PATTERN_2_inst                                                        0x0004
#define CUSTOM_PATTERN_2_pat_byte2_shift                                             (0)
#define CUSTOM_PATTERN_2_pat_byte2_mask                                              (0x000000FF)
#define CUSTOM_PATTERN_2_pat_byte2(data)                                             (0x000000FF&((data)<<0))
#define CUSTOM_PATTERN_2_pat_byte2_src(data)                                         ((0x000000FF&(data))>>0)
#define CUSTOM_PATTERN_2_get_pat_byte2(data)                                         ((0x000000FF&(data))>>0)


#define CUSTOM_PATTERN_3                                                             0x9803D014
#define CUSTOM_PATTERN_3_reg_addr                                                    "0x9803D014"
#define CUSTOM_PATTERN_3_reg                                                         0x9803D014
#define set_CUSTOM_PATTERN_3_reg(data)   (*((volatile unsigned int*) CUSTOM_PATTERN_3_reg)=data)
#define get_CUSTOM_PATTERN_3_reg   (*((volatile unsigned int*) CUSTOM_PATTERN_3_reg))
#define CUSTOM_PATTERN_3_inst_adr                                                    "0x0005"
#define CUSTOM_PATTERN_3_inst                                                        0x0005
#define CUSTOM_PATTERN_3_pat_byte3_shift                                             (0)
#define CUSTOM_PATTERN_3_pat_byte3_mask                                              (0x000000FF)
#define CUSTOM_PATTERN_3_pat_byte3(data)                                             (0x000000FF&((data)<<0))
#define CUSTOM_PATTERN_3_pat_byte3_src(data)                                         ((0x000000FF&(data))>>0)
#define CUSTOM_PATTERN_3_get_pat_byte3(data)                                         ((0x000000FF&(data))>>0)


#define CUSTOM_PATTERN_4                                                             0x9803D018
#define CUSTOM_PATTERN_4_reg_addr                                                    "0x9803D018"
#define CUSTOM_PATTERN_4_reg                                                         0x9803D018
#define set_CUSTOM_PATTERN_4_reg(data)   (*((volatile unsigned int*) CUSTOM_PATTERN_4_reg)=data)
#define get_CUSTOM_PATTERN_4_reg   (*((volatile unsigned int*) CUSTOM_PATTERN_4_reg))
#define CUSTOM_PATTERN_4_inst_adr                                                    "0x0006"
#define CUSTOM_PATTERN_4_inst                                                        0x0006
#define CUSTOM_PATTERN_4_pat_byte4_shift                                             (0)
#define CUSTOM_PATTERN_4_pat_byte4_mask                                              (0x000000FF)
#define CUSTOM_PATTERN_4_pat_byte4(data)                                             (0x000000FF&((data)<<0))
#define CUSTOM_PATTERN_4_pat_byte4_src(data)                                         ((0x000000FF&(data))>>0)
#define CUSTOM_PATTERN_4_get_pat_byte4(data)                                         ((0x000000FF&(data))>>0)


#define CUSTOM_PATTERN_5                                                             0x9803D01C
#define CUSTOM_PATTERN_5_reg_addr                                                    "0x9803D01C"
#define CUSTOM_PATTERN_5_reg                                                         0x9803D01C
#define set_CUSTOM_PATTERN_5_reg(data)   (*((volatile unsigned int*) CUSTOM_PATTERN_5_reg)=data)
#define get_CUSTOM_PATTERN_5_reg   (*((volatile unsigned int*) CUSTOM_PATTERN_5_reg))
#define CUSTOM_PATTERN_5_inst_adr                                                    "0x0007"
#define CUSTOM_PATTERN_5_inst                                                        0x0007
#define CUSTOM_PATTERN_5_pat_byte5_shift                                             (0)
#define CUSTOM_PATTERN_5_pat_byte5_mask                                              (0x000000FF)
#define CUSTOM_PATTERN_5_pat_byte5(data)                                             (0x000000FF&((data)<<0))
#define CUSTOM_PATTERN_5_pat_byte5_src(data)                                         ((0x000000FF&(data))>>0)
#define CUSTOM_PATTERN_5_get_pat_byte5(data)                                         ((0x000000FF&(data))>>0)


#define CUSTOM_PATTERN_6                                                             0x9803D020
#define CUSTOM_PATTERN_6_reg_addr                                                    "0x9803D020"
#define CUSTOM_PATTERN_6_reg                                                         0x9803D020
#define set_CUSTOM_PATTERN_6_reg(data)   (*((volatile unsigned int*) CUSTOM_PATTERN_6_reg)=data)
#define get_CUSTOM_PATTERN_6_reg   (*((volatile unsigned int*) CUSTOM_PATTERN_6_reg))
#define CUSTOM_PATTERN_6_inst_adr                                                    "0x0008"
#define CUSTOM_PATTERN_6_inst                                                        0x0008
#define CUSTOM_PATTERN_6_pat_byte6_shift                                             (0)
#define CUSTOM_PATTERN_6_pat_byte6_mask                                              (0x000000FF)
#define CUSTOM_PATTERN_6_pat_byte6(data)                                             (0x000000FF&((data)<<0))
#define CUSTOM_PATTERN_6_pat_byte6_src(data)                                         ((0x000000FF&(data))>>0)
#define CUSTOM_PATTERN_6_get_pat_byte6(data)                                         ((0x000000FF&(data))>>0)


#define CUSTOM_PATTERN_7                                                             0x9803D024
#define CUSTOM_PATTERN_7_reg_addr                                                    "0x9803D024"
#define CUSTOM_PATTERN_7_reg                                                         0x9803D024
#define set_CUSTOM_PATTERN_7_reg(data)   (*((volatile unsigned int*) CUSTOM_PATTERN_7_reg)=data)
#define get_CUSTOM_PATTERN_7_reg   (*((volatile unsigned int*) CUSTOM_PATTERN_7_reg))
#define CUSTOM_PATTERN_7_inst_adr                                                    "0x0009"
#define CUSTOM_PATTERN_7_inst                                                        0x0009
#define CUSTOM_PATTERN_7_pat_byte7_shift                                             (0)
#define CUSTOM_PATTERN_7_pat_byte7_mask                                              (0x000000FF)
#define CUSTOM_PATTERN_7_pat_byte7(data)                                             (0x000000FF&((data)<<0))
#define CUSTOM_PATTERN_7_pat_byte7_src(data)                                         ((0x000000FF&(data))>>0)
#define CUSTOM_PATTERN_7_get_pat_byte7(data)                                         ((0x000000FF&(data))>>0)


#define CUSTOM_PATTERN_8                                                             0x9803D028
#define CUSTOM_PATTERN_8_reg_addr                                                    "0x9803D028"
#define CUSTOM_PATTERN_8_reg                                                         0x9803D028
#define set_CUSTOM_PATTERN_8_reg(data)   (*((volatile unsigned int*) CUSTOM_PATTERN_8_reg)=data)
#define get_CUSTOM_PATTERN_8_reg   (*((volatile unsigned int*) CUSTOM_PATTERN_8_reg))
#define CUSTOM_PATTERN_8_inst_adr                                                    "0x000A"
#define CUSTOM_PATTERN_8_inst                                                        0x000A
#define CUSTOM_PATTERN_8_pat_byte8_shift                                             (0)
#define CUSTOM_PATTERN_8_pat_byte8_mask                                              (0x000000FF)
#define CUSTOM_PATTERN_8_pat_byte8(data)                                             (0x000000FF&((data)<<0))
#define CUSTOM_PATTERN_8_pat_byte8_src(data)                                         ((0x000000FF&(data))>>0)
#define CUSTOM_PATTERN_8_get_pat_byte8(data)                                         ((0x000000FF&(data))>>0)


#define CUSTOM_PATTERN_9                                                             0x9803D02C
#define CUSTOM_PATTERN_9_reg_addr                                                    "0x9803D02C"
#define CUSTOM_PATTERN_9_reg                                                         0x9803D02C
#define set_CUSTOM_PATTERN_9_reg(data)   (*((volatile unsigned int*) CUSTOM_PATTERN_9_reg)=data)
#define get_CUSTOM_PATTERN_9_reg   (*((volatile unsigned int*) CUSTOM_PATTERN_9_reg))
#define CUSTOM_PATTERN_9_inst_adr                                                    "0x000B"
#define CUSTOM_PATTERN_9_inst                                                        0x000B
#define CUSTOM_PATTERN_9_pat_byte9_shift                                             (0)
#define CUSTOM_PATTERN_9_pat_byte9_mask                                              (0x000000FF)
#define CUSTOM_PATTERN_9_pat_byte9(data)                                             (0x000000FF&((data)<<0))
#define CUSTOM_PATTERN_9_pat_byte9_src(data)                                         ((0x000000FF&(data))>>0)
#define CUSTOM_PATTERN_9_get_pat_byte9(data)                                         ((0x000000FF&(data))>>0)


#define COMPLIANCE_EYE_PATTERN                                                       0x9803D030
#define COMPLIANCE_EYE_PATTERN_reg_addr                                              "0x9803D030"
#define COMPLIANCE_EYE_PATTERN_reg                                                   0x9803D030
#define set_COMPLIANCE_EYE_PATTERN_reg(data)   (*((volatile unsigned int*) COMPLIANCE_EYE_PATTERN_reg)=data)
#define get_COMPLIANCE_EYE_PATTERN_reg   (*((volatile unsigned int*) COMPLIANCE_EYE_PATTERN_reg))
#define COMPLIANCE_EYE_PATTERN_inst_adr                                              "0x000C"
#define COMPLIANCE_EYE_PATTERN_inst                                                  0x000C
#define COMPLIANCE_EYE_PATTERN_Reserved_shift                                        (1)
#define COMPLIANCE_EYE_PATTERN_Reserved_mask                                         (0x000000FE)
#define COMPLIANCE_EYE_PATTERN_Reserved(data)                                        (0x000000FE&((data)<<1))
#define COMPLIANCE_EYE_PATTERN_Reserved_src(data)                                    ((0x000000FE&(data))>>1)
#define COMPLIANCE_EYE_PATTERN_get_Reserved(data)                                    ((0x000000FE&(data))>>1)
#define COMPLIANCE_EYE_PATTERN_eye_pat_sel_shift                                     (0)
#define COMPLIANCE_EYE_PATTERN_eye_pat_sel_mask                                      (0x00000001)
#define COMPLIANCE_EYE_PATTERN_eye_pat_sel(data)                                     (0x00000001&((data)<<0))
#define COMPLIANCE_EYE_PATTERN_eye_pat_sel_src(data)                                 ((0x00000001&(data))>>0)
#define COMPLIANCE_EYE_PATTERN_get_eye_pat_sel(data)                                 ((0x00000001&(data))>>0)


#define DPTX_PHY_CTRL                                                                0x9803D034
#define DPTX_PHY_CTRL_reg_addr                                                       "0x9803D034"
#define DPTX_PHY_CTRL_reg                                                            0x9803D034
#define set_DPTX_PHY_CTRL_reg(data)   (*((volatile unsigned int*) DPTX_PHY_CTRL_reg)=data)
#define get_DPTX_PHY_CTRL_reg   (*((volatile unsigned int*) DPTX_PHY_CTRL_reg))
#define DPTX_PHY_CTRL_inst_adr                                                       "0x000D"
#define DPTX_PHY_CTRL_inst                                                           0x000D
#define DPTX_PHY_CTRL_hw_measure_en_shift                                            (7)
#define DPTX_PHY_CTRL_hw_measure_en_mask                                             (0x00000080)
#define DPTX_PHY_CTRL_hw_measure_en(data)                                            (0x00000080&((data)<<7))
#define DPTX_PHY_CTRL_hw_measure_en_src(data)                                        ((0x00000080&(data))>>7)
#define DPTX_PHY_CTRL_get_hw_measure_en(data)                                        ((0x00000080&(data))>>7)
#define DPTX_PHY_CTRL_Reserved0_shift                                                 (5)
#define DPTX_PHY_CTRL_Reserved0_mask                                                  (0x00000060)
#define DPTX_PHY_CTRL_Reserved0(data)                                                 (0x00000060&((data)<<5))
#define DPTX_PHY_CTRL_Reserved0_src(data)                                             ((0x00000060&(data))>>5)
#define DPTX_PHY_CTRL_get_Reserved0(data)                                             ((0x00000060&(data))>>5)
#define DPTX_PHY_CTRL_sr_insert_en_shift                                             (4)
#define DPTX_PHY_CTRL_sr_insert_en_mask                                              (0x00000010)
#define DPTX_PHY_CTRL_sr_insert_en(data)                                             (0x00000010&((data)<<4))
#define DPTX_PHY_CTRL_sr_insert_en_src(data)                                         ((0x00000010&(data))>>4)
#define DPTX_PHY_CTRL_get_sr_insert_en(data)                                         ((0x00000010&(data))>>4)
#define DPTX_PHY_CTRL_Reserved1_shift                                                 (3)
#define DPTX_PHY_CTRL_Reserved1_mask                                                  (0x00000008)
#define DPTX_PHY_CTRL_Reserved1(data)                                                 (0x00000008&((data)<<3))
#define DPTX_PHY_CTRL_Reserved1_src(data)                                             ((0x00000008&(data))>>3)
#define DPTX_PHY_CTRL_get_Reserved1(data)                                             ((0x00000008&(data))>>3)
#define DPTX_PHY_CTRL_dptx_skew_en_shift                                             (2)
#define DPTX_PHY_CTRL_dptx_skew_en_mask                                              (0x00000004)
#define DPTX_PHY_CTRL_dptx_skew_en(data)                                             (0x00000004&((data)<<2))
#define DPTX_PHY_CTRL_dptx_skew_en_src(data)                                         ((0x00000004&(data))>>2)
#define DPTX_PHY_CTRL_get_dptx_skew_en(data)                                         ((0x00000004&(data))>>2)
#define DPTX_PHY_CTRL_dptx_scb_mode_shift                                            (1)
#define DPTX_PHY_CTRL_dptx_scb_mode_mask                                             (0x00000002)
#define DPTX_PHY_CTRL_dptx_scb_mode(data)                                            (0x00000002&((data)<<1))
#define DPTX_PHY_CTRL_dptx_scb_mode_src(data)                                        ((0x00000002&(data))>>1)
#define DPTX_PHY_CTRL_get_dptx_scb_mode(data)                                        ((0x00000002&(data))>>1)
#define DPTX_PHY_CTRL_dptx_scb_en_shift                                              (0)
#define DPTX_PHY_CTRL_dptx_scb_en_mask                                               (0x00000001)
#define DPTX_PHY_CTRL_dptx_scb_en(data)                                              (0x00000001&((data)<<0))
#define DPTX_PHY_CTRL_dptx_scb_en_src(data)                                          ((0x00000001&(data))>>0)
#define DPTX_PHY_CTRL_get_dptx_scb_en(data)                                          ((0x00000001&(data))>>0)


#define DPTX_LANE_SWAP                                                               0x9803D038
#define DPTX_LANE_SWAP_reg_addr                                                      "0x9803D038"
#define DPTX_LANE_SWAP_reg                                                           0x9803D038
#define set_DPTX_LANE_SWAP_reg(data)   (*((volatile unsigned int*) DPTX_LANE_SWAP_reg)=data)
#define get_DPTX_LANE_SWAP_reg   (*((volatile unsigned int*) DPTX_LANE_SWAP_reg))
#define DPTX_LANE_SWAP_inst_adr                                                      "0x000E"
#define DPTX_LANE_SWAP_inst                                                          0x000E
#define DPTX_LANE_SWAP_lane0_source_shift                                            (6)
#define DPTX_LANE_SWAP_lane0_source_mask                                             (0x000000C0)
#define DPTX_LANE_SWAP_lane0_source(data)                                            (0x000000C0&((data)<<6))
#define DPTX_LANE_SWAP_lane0_source_src(data)                                        ((0x000000C0&(data))>>6)
#define DPTX_LANE_SWAP_get_lane0_source(data)                                        ((0x000000C0&(data))>>6)
#define DPTX_LANE_SWAP_lane1_source_shift                                            (4)
#define DPTX_LANE_SWAP_lane1_source_mask                                             (0x00000030)
#define DPTX_LANE_SWAP_lane1_source(data)                                            (0x00000030&((data)<<4))
#define DPTX_LANE_SWAP_lane1_source_src(data)                                        ((0x00000030&(data))>>4)
#define DPTX_LANE_SWAP_get_lane1_source(data)                                        ((0x00000030&(data))>>4)
#define DPTX_LANE_SWAP_lane2_source_shift                                            (2)
#define DPTX_LANE_SWAP_lane2_source_mask                                             (0x0000000C)
#define DPTX_LANE_SWAP_lane2_source(data)                                            (0x0000000C&((data)<<2))
#define DPTX_LANE_SWAP_lane2_source_src(data)                                        ((0x0000000C&(data))>>2)
#define DPTX_LANE_SWAP_get_lane2_source(data)                                        ((0x0000000C&(data))>>2)
#define DPTX_LANE_SWAP_lane3_source_shift                                            (0)
#define DPTX_LANE_SWAP_lane3_source_mask                                             (0x00000003)
#define DPTX_LANE_SWAP_lane3_source(data)                                            (0x00000003&((data)<<0))
#define DPTX_LANE_SWAP_lane3_source_src(data)                                        ((0x00000003&(data))>>0)
#define DPTX_LANE_SWAP_get_lane3_source(data)                                        ((0x00000003&(data))>>0)


#define DPTX_8B10B_TST                                                               0x9803D03C
#define DPTX_8B10B_TST_reg_addr                                                      "0x9803D03C"
#define DPTX_8B10B_TST_reg                                                           0x9803D03C
#define set_DPTX_8B10B_TST_reg(data)   (*((volatile unsigned int*) DPTX_8B10B_TST_reg)=data)
#define get_DPTX_8B10B_TST_reg   (*((volatile unsigned int*) DPTX_8B10B_TST_reg))
#define DPTX_8B10B_TST_inst_adr                                                      "0x000F"
#define DPTX_8B10B_TST_inst                                                          0x000F
#define DPTX_8B10B_TST_Reserved_shift                                                (3)
#define DPTX_8B10B_TST_Reserved_mask                                                 (0x000000F8)
#define DPTX_8B10B_TST_Reserved(data)                                                (0x000000F8&((data)<<3))
#define DPTX_8B10B_TST_Reserved_src(data)                                            ((0x000000F8&(data))>>3)
#define DPTX_8B10B_TST_get_Reserved(data)                                            ((0x000000F8&(data))>>3)
#define DPTX_8B10B_TST_dptx_8b10b_tst_mode_shift                                     (0)
#define DPTX_8B10B_TST_dptx_8b10b_tst_mode_mask                                      (0x00000007)
#define DPTX_8B10B_TST_dptx_8b10b_tst_mode(data)                                     (0x00000007&((data)<<0))
#define DPTX_8B10B_TST_dptx_8b10b_tst_mode_src(data)                                 ((0x00000007&(data))>>0)
#define DPTX_8B10B_TST_get_dptx_8b10b_tst_mode(data)                                 ((0x00000007&(data))>>0)


#define DPTX_PHY_DUMMY                                                               0x9803D040
#define DPTX_PHY_DUMMY_reg_addr                                                      "0x9803D040"
#define DPTX_PHY_DUMMY_reg                                                           0x9803D040
#define set_DPTX_PHY_DUMMY_reg(data)   (*((volatile unsigned int*) DPTX_PHY_DUMMY_reg)=data)
#define get_DPTX_PHY_DUMMY_reg   (*((volatile unsigned int*) DPTX_PHY_DUMMY_reg))
#define DPTX_PHY_DUMMY_inst_adr                                                      "0x0010"
#define DPTX_PHY_DUMMY_inst                                                          0x0010
#define DPTX_PHY_DUMMY_dptx_phy_dummy_shift                                          (0)
#define DPTX_PHY_DUMMY_dptx_phy_dummy_mask                                           (0x000000FF)
#define DPTX_PHY_DUMMY_dptx_phy_dummy(data)                                          (0x000000FF&((data)<<0))
#define DPTX_PHY_DUMMY_dptx_phy_dummy_src(data)                                      ((0x000000FF&(data))>>0)
#define DPTX_PHY_DUMMY_get_dptx_phy_dummy(data)                                      ((0x000000FF&(data))>>0)


#define RIV0                                                                         0x9803D044
#define RIV0_reg_addr                                                                "0x9803D044"
#define RIV0_reg                                                                     0x9803D044
#define set_RIV0_reg(data)   (*((volatile unsigned int*) RIV0_reg)=data)
#define get_RIV0_reg   (*((volatile unsigned int*) RIV0_reg))
#define RIV0_inst_adr                                                                "0x0011"
#define RIV0_inst                                                                    0x0011
#define RIV0_riv6356_shift                                                           (0)
#define RIV0_riv6356_mask                                                            (0x000000FF)
#define RIV0_riv6356(data)                                                           (0x000000FF&((data)<<0))
#define RIV0_riv6356_src(data)                                                       ((0x000000FF&(data))>>0)
#define RIV0_get_riv6356(data)                                                       ((0x000000FF&(data))>>0)


#define RIV1                                                                         0x9803D048
#define RIV1_reg_addr                                                                "0x9803D048"
#define RIV1_reg                                                                     0x9803D048
#define set_RIV1_reg(data)   (*((volatile unsigned int*) RIV1_reg)=data)
#define get_RIV1_reg   (*((volatile unsigned int*) RIV1_reg))
#define RIV1_inst_adr                                                                "0x0012"
#define RIV1_inst                                                                    0x0012
#define RIV1_riv5548_shift                                                           (0)
#define RIV1_riv5548_mask                                                            (0x000000FF)
#define RIV1_riv5548(data)                                                           (0x000000FF&((data)<<0))
#define RIV1_riv5548_src(data)                                                       ((0x000000FF&(data))>>0)
#define RIV1_get_riv5548(data)                                                       ((0x000000FF&(data))>>0)


#define RIV2                                                                         0x9803D04C
#define RIV2_reg_addr                                                                "0x9803D04C"
#define RIV2_reg                                                                     0x9803D04C
#define set_RIV2_reg(data)   (*((volatile unsigned int*) RIV2_reg)=data)
#define get_RIV2_reg   (*((volatile unsigned int*) RIV2_reg))
#define RIV2_inst_adr                                                                "0x0013"
#define RIV2_inst                                                                    0x0013
#define RIV2_riv4740_shift                                                           (0)
#define RIV2_riv4740_mask                                                            (0x000000FF)
#define RIV2_riv4740(data)                                                           (0x000000FF&((data)<<0))
#define RIV2_riv4740_src(data)                                                       ((0x000000FF&(data))>>0)
#define RIV2_get_riv4740(data)                                                       ((0x000000FF&(data))>>0)


#define RIV3                                                                         0x9803D050
#define RIV3_reg_addr                                                                "0x9803D050"
#define RIV3_reg                                                                     0x9803D050
#define set_RIV3_reg(data)   (*((volatile unsigned int*) RIV3_reg)=data)
#define get_RIV3_reg   (*((volatile unsigned int*) RIV3_reg))
#define RIV3_inst_adr                                                                "0x0014"
#define RIV3_inst                                                                    0x0014
#define RIV3_riv3932_shift                                                           (0)
#define RIV3_riv3932_mask                                                            (0x000000FF)
#define RIV3_riv3932(data)                                                           (0x000000FF&((data)<<0))
#define RIV3_riv3932_src(data)                                                       ((0x000000FF&(data))>>0)
#define RIV3_get_riv3932(data)                                                       ((0x000000FF&(data))>>0)


#define RIV4                                                                         0x9803D054
#define RIV4_reg_addr                                                                "0x9803D054"
#define RIV4_reg                                                                     0x9803D054
#define set_RIV4_reg(data)   (*((volatile unsigned int*) RIV4_reg)=data)
#define get_RIV4_reg   (*((volatile unsigned int*) RIV4_reg))
#define RIV4_inst_adr                                                                "0x0015"
#define RIV4_inst                                                                    0x0015
#define RIV4_riv3124_shift                                                           (0)
#define RIV4_riv3124_mask                                                            (0x000000FF)
#define RIV4_riv3124(data)                                                           (0x000000FF&((data)<<0))
#define RIV4_riv3124_src(data)                                                       ((0x000000FF&(data))>>0)
#define RIV4_get_riv3124(data)                                                       ((0x000000FF&(data))>>0)


#define RIV5                                                                         0x9803D058
#define RIV5_reg_addr                                                                "0x9803D058"
#define RIV5_reg                                                                     0x9803D058
#define set_RIV5_reg(data)   (*((volatile unsigned int*) RIV5_reg)=data)
#define get_RIV5_reg   (*((volatile unsigned int*) RIV5_reg))
#define RIV5_inst_adr                                                                "0x0016"
#define RIV5_inst                                                                    0x0016
#define RIV5_riv2316_shift                                                           (0)
#define RIV5_riv2316_mask                                                            (0x000000FF)
#define RIV5_riv2316(data)                                                           (0x000000FF&((data)<<0))
#define RIV5_riv2316_src(data)                                                       ((0x000000FF&(data))>>0)
#define RIV5_get_riv2316(data)                                                       ((0x000000FF&(data))>>0)


#define RIV6                                                                         0x9803D05C
#define RIV6_reg_addr                                                                "0x9803D05C"
#define RIV6_reg                                                                     0x9803D05C
#define set_RIV6_reg(data)   (*((volatile unsigned int*) RIV6_reg)=data)
#define get_RIV6_reg   (*((volatile unsigned int*) RIV6_reg))
#define RIV6_inst_adr                                                                "0x0017"
#define RIV6_inst                                                                    0x0017
#define RIV6_riv158_shift                                                            (0)
#define RIV6_riv158_mask                                                             (0x000000FF)
#define RIV6_riv158(data)                                                            (0x000000FF&((data)<<0))
#define RIV6_riv158_src(data)                                                        ((0x000000FF&(data))>>0)
#define RIV6_get_riv158(data)                                                        ((0x000000FF&(data))>>0)


#define RIV7                                                                         0x9803D060
#define RIV7_reg_addr                                                                "0x9803D060"
#define RIV7_reg                                                                     0x9803D060
#define set_RIV7_reg(data)   (*((volatile unsigned int*) RIV7_reg)=data)
#define get_RIV7_reg   (*((volatile unsigned int*) RIV7_reg))
#define RIV7_inst_adr                                                                "0x0018"
#define RIV7_inst                                                                    0x0018
#define RIV7_riv70_shift                                                             (0)
#define RIV7_riv70_mask                                                              (0x000000FF)
#define RIV7_riv70(data)                                                             (0x000000FF&((data)<<0))
#define RIV7_riv70_src(data)                                                         ((0x000000FF&(data))>>0)
#define RIV7_get_riv70(data)                                                         ((0x000000FF&(data))>>0)


#define DPTX_HDCP_CTRL1                                                              0x9803D0C0
#define DPTX_HDCP_CTRL1_reg_addr                                                     "0x9803D0C0"
#define DPTX_HDCP_CTRL1_reg                                                          0x9803D0C0
#define set_DPTX_HDCP_CTRL1_reg(data)   (*((volatile unsigned int*) DPTX_HDCP_CTRL1_reg)=data)
#define get_DPTX_HDCP_CTRL1_reg   (*((volatile unsigned int*) DPTX_HDCP_CTRL1_reg))
#define DPTX_HDCP_CTRL1_inst_adr                                                     "0x0030"
#define DPTX_HDCP_CTRL1_inst                                                         0x0030
#define DPTX_HDCP_CTRL1_Reserved_shift                                               (5)
#define DPTX_HDCP_CTRL1_Reserved_mask                                                (0x000000E0)
#define DPTX_HDCP_CTRL1_Reserved(data)                                               (0x000000E0&((data)<<5))
#define DPTX_HDCP_CTRL1_Reserved_src(data)                                           ((0x000000E0&(data))>>5)
#define DPTX_HDCP_CTRL1_get_Reserved(data)                                           ((0x000000E0&(data))>>5)
#define DPTX_HDCP_CTRL1_repeater_shift                                               (4)
#define DPTX_HDCP_CTRL1_repeater_mask                                                (0x00000010)
#define DPTX_HDCP_CTRL1_repeater(data)                                               (0x00000010&((data)<<4))
#define DPTX_HDCP_CTRL1_repeater_src(data)                                           ((0x00000010&(data))>>4)
#define DPTX_HDCP_CTRL1_get_repeater(data)                                           ((0x00000010&(data))>>4)
#define DPTX_HDCP_CTRL1_key_dl_en_shift                                              (3)
#define DPTX_HDCP_CTRL1_key_dl_en_mask                                               (0x00000008)
#define DPTX_HDCP_CTRL1_key_dl_en(data)                                              (0x00000008&((data)<<3))
#define DPTX_HDCP_CTRL1_key_dl_en_src(data)                                          ((0x00000008&(data))>>3)
#define DPTX_HDCP_CTRL1_get_key_dl_en(data)                                          ((0x00000008&(data))>>3)
#define DPTX_HDCP_CTRL1_hdcp_encrypted_shift                                         (2)
#define DPTX_HDCP_CTRL1_hdcp_encrypted_mask                                          (0x00000004)
#define DPTX_HDCP_CTRL1_hdcp_encrypted(data)                                         (0x00000004&((data)<<2))
#define DPTX_HDCP_CTRL1_hdcp_encrypted_src(data)                                     ((0x00000004&(data))>>2)
#define DPTX_HDCP_CTRL1_get_hdcp_encrypted(data)                                     ((0x00000004&(data))>>2)
#define DPTX_HDCP_CTRL1_hdcp_encry_en_shift                                          (1)
#define DPTX_HDCP_CTRL1_hdcp_encry_en_mask                                           (0x00000002)
#define DPTX_HDCP_CTRL1_hdcp_encry_en(data)                                          (0x00000002&((data)<<1))
#define DPTX_HDCP_CTRL1_hdcp_encry_en_src(data)                                      ((0x00000002&(data))>>1)
#define DPTX_HDCP_CTRL1_get_hdcp_encry_en(data)                                      ((0x00000002&(data))>>1)
#define DPTX_HDCP_CTRL1_hdcp_en_shift                                                (0)
#define DPTX_HDCP_CTRL1_hdcp_en_mask                                                 (0x00000001)
#define DPTX_HDCP_CTRL1_hdcp_en(data)                                                (0x00000001&((data)<<0))
#define DPTX_HDCP_CTRL1_hdcp_en_src(data)                                            ((0x00000001&(data))>>0)
#define DPTX_HDCP_CTRL1_get_hdcp_en(data)                                            ((0x00000001&(data))>>0)


#define DPTX_HDCP_CTRL2                                                              0x9803D0C4
#define DPTX_HDCP_CTRL2_reg_addr                                                     "0x9803D0C4"
#define DPTX_HDCP_CTRL2_reg                                                          0x9803D0C4
#define set_DPTX_HDCP_CTRL2_reg(data)   (*((volatile unsigned int*) DPTX_HDCP_CTRL2_reg)=data)
#define get_DPTX_HDCP_CTRL2_reg   (*((volatile unsigned int*) DPTX_HDCP_CTRL2_reg))
#define DPTX_HDCP_CTRL2_inst_adr                                                     "0x0031"
#define DPTX_HDCP_CTRL2_inst                                                         0x0031
#define DPTX_HDCP_CTRL2_Reserved_shift                                               (7)
#define DPTX_HDCP_CTRL2_Reserved_mask                                                (0x00000080)
#define DPTX_HDCP_CTRL2_Reserved(data)                                               (0x00000080&((data)<<7))
#define DPTX_HDCP_CTRL2_Reserved_src(data)                                           ((0x00000080&(data))>>7)
#define DPTX_HDCP_CTRL2_get_Reserved(data)                                           ((0x00000080&(data))>>7)
#define DPTX_HDCP_CTRL2_km_clk_sel_shift                                             (6)
#define DPTX_HDCP_CTRL2_km_clk_sel_mask                                              (0x00000040)
#define DPTX_HDCP_CTRL2_km_clk_sel(data)                                             (0x00000040&((data)<<6))
#define DPTX_HDCP_CTRL2_km_clk_sel_src(data)                                         ((0x00000040&(data))>>6)
#define DPTX_HDCP_CTRL2_get_km_clk_sel(data)                                         ((0x00000040&(data))>>6)
#define DPTX_HDCP_CTRL2_ri_en_shift                                                  (5)
#define DPTX_HDCP_CTRL2_ri_en_mask                                                   (0x00000020)
#define DPTX_HDCP_CTRL2_ri_en(data)                                                  (0x00000020&((data)<<5))
#define DPTX_HDCP_CTRL2_ri_en_src(data)                                              ((0x00000020&(data))>>5)
#define DPTX_HDCP_CTRL2_get_ri_en(data)                                              ((0x00000020&(data))>>5)
#define DPTX_HDCP_CTRL2_an_sel_shift                                                 (4)
#define DPTX_HDCP_CTRL2_an_sel_mask                                                  (0x00000010)
#define DPTX_HDCP_CTRL2_an_sel(data)                                                 (0x00000010&((data)<<4))
#define DPTX_HDCP_CTRL2_an_sel_src(data)                                             ((0x00000010&(data))>>4)
#define DPTX_HDCP_CTRL2_get_an_sel(data)                                             ((0x00000010&(data))>>4)
#define DPTX_HDCP_CTRL2_an_gen_start_shift                                           (3)
#define DPTX_HDCP_CTRL2_an_gen_start_mask                                            (0x00000008)
#define DPTX_HDCP_CTRL2_an_gen_start(data)                                           (0x00000008&((data)<<3))
#define DPTX_HDCP_CTRL2_an_gen_start_src(data)                                       ((0x00000008&(data))>>3)
#define DPTX_HDCP_CTRL2_get_an_gen_start(data)                                       ((0x00000008&(data))>>3)
#define DPTX_HDCP_CTRL2_an_gen_done_shift                                            (2)
#define DPTX_HDCP_CTRL2_an_gen_done_mask                                             (0x00000004)
#define DPTX_HDCP_CTRL2_an_gen_done(data)                                            (0x00000004&((data)<<2))
#define DPTX_HDCP_CTRL2_an_gen_done_src(data)                                        ((0x00000004&(data))>>2)
#define DPTX_HDCP_CTRL2_get_an_gen_done(data)                                        ((0x00000004&(data))>>2)
#define DPTX_HDCP_CTRL2_computation_en_shift                                         (1)
#define DPTX_HDCP_CTRL2_computation_en_mask                                          (0x00000002)
#define DPTX_HDCP_CTRL2_computation_en(data)                                         (0x00000002&((data)<<1))
#define DPTX_HDCP_CTRL2_computation_en_src(data)                                     ((0x00000002&(data))>>1)
#define DPTX_HDCP_CTRL2_get_computation_en(data)                                     ((0x00000002&(data))>>1)
#define DPTX_HDCP_CTRL2_computation_done_shift                                       (0)
#define DPTX_HDCP_CTRL2_computation_done_mask                                        (0x00000001)
#define DPTX_HDCP_CTRL2_computation_done(data)                                       (0x00000001&((data)<<0))
#define DPTX_HDCP_CTRL2_computation_done_src(data)                                   ((0x00000001&(data))>>0)
#define DPTX_HDCP_CTRL2_get_computation_done(data)                                   ((0x00000001&(data))>>0)


#define DP_HDCP_KEY_DL_PORT                                                          0x9803D0C8
#define DP_HDCP_KEY_DL_PORT_reg_addr                                                 "0x9803D0C8"
#define DP_HDCP_KEY_DL_PORT_reg                                                      0x9803D0C8
#define set_DP_HDCP_KEY_DL_PORT_reg(data)   (*((volatile unsigned int*) DP_HDCP_KEY_DL_PORT_reg)=data)
#define get_DP_HDCP_KEY_DL_PORT_reg   (*((volatile unsigned int*) DP_HDCP_KEY_DL_PORT_reg))
#define DP_HDCP_KEY_DL_PORT_inst_adr                                                 "0x0032"
#define DP_HDCP_KEY_DL_PORT_inst                                                     0x0032
#define DP_HDCP_KEY_DL_PORT_key_dl_port_shift                                        (0)
#define DP_HDCP_KEY_DL_PORT_key_dl_port_mask                                         (0x000000FF)
#define DP_HDCP_KEY_DL_PORT_key_dl_port(data)                                        (0x000000FF&((data)<<0))
#define DP_HDCP_KEY_DL_PORT_key_dl_port_src(data)                                    ((0x000000FF&(data))>>0)
#define DP_HDCP_KEY_DL_PORT_get_key_dl_port(data)                                    ((0x000000FF&(data))>>0)


#define DP_HDCP_KEY_OUTPUT                                                           0x9803D0CC
#define DP_HDCP_KEY_OUTPUT_reg_addr                                                  "0x9803D0CC"
#define DP_HDCP_KEY_OUTPUT_reg                                                       0x9803D0CC
#define set_DP_HDCP_KEY_OUTPUT_reg(data)   (*((volatile unsigned int*) DP_HDCP_KEY_OUTPUT_reg)=data)
#define get_DP_HDCP_KEY_OUTPUT_reg   (*((volatile unsigned int*) DP_HDCP_KEY_OUTPUT_reg))
#define DP_HDCP_KEY_OUTPUT_inst_adr                                                  "0x0033"
#define DP_HDCP_KEY_OUTPUT_inst                                                      0x0033
#define DP_HDCP_KEY_OUTPUT_key_out_shift                                             (0)
#define DP_HDCP_KEY_OUTPUT_key_out_mask                                              (0x000000FF)
#define DP_HDCP_KEY_OUTPUT_key_out(data)                                             (0x000000FF&((data)<<0))
#define DP_HDCP_KEY_OUTPUT_key_out_src(data)                                         ((0x000000FF&(data))>>0)
#define DP_HDCP_KEY_OUTPUT_get_key_out(data)                                         ((0x000000FF&(data))>>0)


#define AN_BYTE_7                                                                    0x9803D0D0
#define AN_BYTE_7_reg_addr                                                           "0x9803D0D0"
#define AN_BYTE_7_reg                                                                0x9803D0D0
#define set_AN_BYTE_7_reg(data)   (*((volatile unsigned int*) AN_BYTE_7_reg)=data)
#define get_AN_BYTE_7_reg   (*((volatile unsigned int*) AN_BYTE_7_reg))
#define AN_BYTE_7_inst_adr                                                           "0x0034"
#define AN_BYTE_7_inst                                                               0x0034
#define AN_BYTE_7_an_63_56_shift                                                     (0)
#define AN_BYTE_7_an_63_56_mask                                                      (0x000000FF)
#define AN_BYTE_7_an_63_56(data)                                                     (0x000000FF&((data)<<0))
#define AN_BYTE_7_an_63_56_src(data)                                                 ((0x000000FF&(data))>>0)
#define AN_BYTE_7_get_an_63_56(data)                                                 ((0x000000FF&(data))>>0)


#define AN_BYTE_6                                                                    0x9803D0D4
#define AN_BYTE_6_reg_addr                                                           "0x9803D0D4"
#define AN_BYTE_6_reg                                                                0x9803D0D4
#define set_AN_BYTE_6_reg(data)   (*((volatile unsigned int*) AN_BYTE_6_reg)=data)
#define get_AN_BYTE_6_reg   (*((volatile unsigned int*) AN_BYTE_6_reg))
#define AN_BYTE_6_inst_adr                                                           "0x0035"
#define AN_BYTE_6_inst                                                               0x0035
#define AN_BYTE_6_an_55_48_shift                                                     (0)
#define AN_BYTE_6_an_55_48_mask                                                      (0x000000FF)
#define AN_BYTE_6_an_55_48(data)                                                     (0x000000FF&((data)<<0))
#define AN_BYTE_6_an_55_48_src(data)                                                 ((0x000000FF&(data))>>0)
#define AN_BYTE_6_get_an_55_48(data)                                                 ((0x000000FF&(data))>>0)


#define AN_BYTE_5                                                                    0x9803D0D8
#define AN_BYTE_5_reg_addr                                                           "0x9803D0D8"
#define AN_BYTE_5_reg                                                                0x9803D0D8
#define set_AN_BYTE_5_reg(data)   (*((volatile unsigned int*) AN_BYTE_5_reg)=data)
#define get_AN_BYTE_5_reg   (*((volatile unsigned int*) AN_BYTE_5_reg))
#define AN_BYTE_5_inst_adr                                                           "0x0036"
#define AN_BYTE_5_inst                                                               0x0036
#define AN_BYTE_5_an_47_40_shift                                                     (0)
#define AN_BYTE_5_an_47_40_mask                                                      (0x000000FF)
#define AN_BYTE_5_an_47_40(data)                                                     (0x000000FF&((data)<<0))
#define AN_BYTE_5_an_47_40_src(data)                                                 ((0x000000FF&(data))>>0)
#define AN_BYTE_5_get_an_47_40(data)                                                 ((0x000000FF&(data))>>0)


#define AN_BYTE_4                                                                    0x9803D0DC
#define AN_BYTE_4_reg_addr                                                           "0x9803D0DC"
#define AN_BYTE_4_reg                                                                0x9803D0DC
#define set_AN_BYTE_4_reg(data)   (*((volatile unsigned int*) AN_BYTE_4_reg)=data)
#define get_AN_BYTE_4_reg   (*((volatile unsigned int*) AN_BYTE_4_reg))
#define AN_BYTE_4_inst_adr                                                           "0x0037"
#define AN_BYTE_4_inst                                                               0x0037
#define AN_BYTE_4_an_39_32_shift                                                     (0)
#define AN_BYTE_4_an_39_32_mask                                                      (0x000000FF)
#define AN_BYTE_4_an_39_32(data)                                                     (0x000000FF&((data)<<0))
#define AN_BYTE_4_an_39_32_src(data)                                                 ((0x000000FF&(data))>>0)
#define AN_BYTE_4_get_an_39_32(data)                                                 ((0x000000FF&(data))>>0)


#define AN_BYTE_3                                                                    0x9803D0E0
#define AN_BYTE_3_reg_addr                                                           "0x9803D0E0"
#define AN_BYTE_3_reg                                                                0x9803D0E0
#define set_AN_BYTE_3_reg(data)   (*((volatile unsigned int*) AN_BYTE_3_reg)=data)
#define get_AN_BYTE_3_reg   (*((volatile unsigned int*) AN_BYTE_3_reg))
#define AN_BYTE_3_inst_adr                                                           "0x0038"
#define AN_BYTE_3_inst                                                               0x0038
#define AN_BYTE_3_an_31_24_shift                                                     (0)
#define AN_BYTE_3_an_31_24_mask                                                      (0x000000FF)
#define AN_BYTE_3_an_31_24(data)                                                     (0x000000FF&((data)<<0))
#define AN_BYTE_3_an_31_24_src(data)                                                 ((0x000000FF&(data))>>0)
#define AN_BYTE_3_get_an_31_24(data)                                                 ((0x000000FF&(data))>>0)


#define AN_BYTE_2                                                                    0x9803D0E4
#define AN_BYTE_2_reg_addr                                                           "0x9803D0E4"
#define AN_BYTE_2_reg                                                                0x9803D0E4
#define set_AN_BYTE_2_reg(data)   (*((volatile unsigned int*) AN_BYTE_2_reg)=data)
#define get_AN_BYTE_2_reg   (*((volatile unsigned int*) AN_BYTE_2_reg))
#define AN_BYTE_2_inst_adr                                                           "0x0039"
#define AN_BYTE_2_inst                                                               0x0039
#define AN_BYTE_2_an_23_16_shift                                                     (0)
#define AN_BYTE_2_an_23_16_mask                                                      (0x000000FF)
#define AN_BYTE_2_an_23_16(data)                                                     (0x000000FF&((data)<<0))
#define AN_BYTE_2_an_23_16_src(data)                                                 ((0x000000FF&(data))>>0)
#define AN_BYTE_2_get_an_23_16(data)                                                 ((0x000000FF&(data))>>0)


#define AN_BYTE_1                                                                    0x9803D0E8
#define AN_BYTE_1_reg_addr                                                           "0x9803D0E8"
#define AN_BYTE_1_reg                                                                0x9803D0E8
#define set_AN_BYTE_1_reg(data)   (*((volatile unsigned int*) AN_BYTE_1_reg)=data)
#define get_AN_BYTE_1_reg   (*((volatile unsigned int*) AN_BYTE_1_reg))
#define AN_BYTE_1_inst_adr                                                           "0x003A"
#define AN_BYTE_1_inst                                                               0x003A
#define AN_BYTE_1_an_15_8_shift                                                      (0)
#define AN_BYTE_1_an_15_8_mask                                                       (0x000000FF)
#define AN_BYTE_1_an_15_8(data)                                                      (0x000000FF&((data)<<0))
#define AN_BYTE_1_an_15_8_src(data)                                                  ((0x000000FF&(data))>>0)
#define AN_BYTE_1_get_an_15_8(data)                                                  ((0x000000FF&(data))>>0)


#define AN_BYTE_0                                                                    0x9803D0EC
#define AN_BYTE_0_reg_addr                                                           "0x9803D0EC"
#define AN_BYTE_0_reg                                                                0x9803D0EC
#define set_AN_BYTE_0_reg(data)   (*((volatile unsigned int*) AN_BYTE_0_reg)=data)
#define get_AN_BYTE_0_reg   (*((volatile unsigned int*) AN_BYTE_0_reg))
#define AN_BYTE_0_inst_adr                                                           "0x003B"
#define AN_BYTE_0_inst                                                               0x003B
#define AN_BYTE_0_an_7_0_shift                                                       (0)
#define AN_BYTE_0_an_7_0_mask                                                        (0x000000FF)
#define AN_BYTE_0_an_7_0(data)                                                       (0x000000FF&((data)<<0))
#define AN_BYTE_0_an_7_0_src(data)                                                   ((0x000000FF&(data))>>0)
#define AN_BYTE_0_get_an_7_0(data)                                                   ((0x000000FF&(data))>>0)


#define M0_BYTE_7                                                                    0x9803D0F0
#define M0_BYTE_7_reg_addr                                                           "0x9803D0F0"
#define M0_BYTE_7_reg                                                                0x9803D0F0
#define set_M0_BYTE_7_reg(data)   (*((volatile unsigned int*) M0_BYTE_7_reg)=data)
#define get_M0_BYTE_7_reg   (*((volatile unsigned int*) M0_BYTE_7_reg))
#define M0_BYTE_7_inst_adr                                                           "0x003C"
#define M0_BYTE_7_inst                                                               0x003C
#define M0_BYTE_7_m06356_shift                                                       (0)
#define M0_BYTE_7_m06356_mask                                                        (0x000000FF)
#define M0_BYTE_7_m06356(data)                                                       (0x000000FF&((data)<<0))
#define M0_BYTE_7_m06356_src(data)                                                   ((0x000000FF&(data))>>0)
#define M0_BYTE_7_get_m06356(data)                                                   ((0x000000FF&(data))>>0)


#define M0_BYTE_6                                                                    0x9803D0F4
#define M0_BYTE_6_reg_addr                                                           "0x9803D0F4"
#define M0_BYTE_6_reg                                                                0x9803D0F4
#define set_M0_BYTE_6_reg(data)   (*((volatile unsigned int*) M0_BYTE_6_reg)=data)
#define get_M0_BYTE_6_reg   (*((volatile unsigned int*) M0_BYTE_6_reg))
#define M0_BYTE_6_inst_adr                                                           "0x003D"
#define M0_BYTE_6_inst                                                               0x003D
#define M0_BYTE_6_m05548_shift                                                       (0)
#define M0_BYTE_6_m05548_mask                                                        (0x000000FF)
#define M0_BYTE_6_m05548(data)                                                       (0x000000FF&((data)<<0))
#define M0_BYTE_6_m05548_src(data)                                                   ((0x000000FF&(data))>>0)
#define M0_BYTE_6_get_m05548(data)                                                   ((0x000000FF&(data))>>0)


#define M0_BYTE_5                                                                    0x9803D0F8
#define M0_BYTE_5_reg_addr                                                           "0x9803D0F8"
#define M0_BYTE_5_reg                                                                0x9803D0F8
#define set_M0_BYTE_5_reg(data)   (*((volatile unsigned int*) M0_BYTE_5_reg)=data)
#define get_M0_BYTE_5_reg   (*((volatile unsigned int*) M0_BYTE_5_reg))
#define M0_BYTE_5_inst_adr                                                           "0x003E"
#define M0_BYTE_5_inst                                                               0x003E
#define M0_BYTE_5_m04740_shift                                                       (0)
#define M0_BYTE_5_m04740_mask                                                        (0x000000FF)
#define M0_BYTE_5_m04740(data)                                                       (0x000000FF&((data)<<0))
#define M0_BYTE_5_m04740_src(data)                                                   ((0x000000FF&(data))>>0)
#define M0_BYTE_5_get_m04740(data)                                                   ((0x000000FF&(data))>>0)


#define M0_BYTE_4                                                                    0x9803D0FC
#define M0_BYTE_4_reg_addr                                                           "0x9803D0FC"
#define M0_BYTE_4_reg                                                                0x9803D0FC
#define set_M0_BYTE_4_reg(data)   (*((volatile unsigned int*) M0_BYTE_4_reg)=data)
#define get_M0_BYTE_4_reg   (*((volatile unsigned int*) M0_BYTE_4_reg))
#define M0_BYTE_4_inst_adr                                                           "0x003F"
#define M0_BYTE_4_inst                                                               0x003F
#define M0_BYTE_4_m03932_shift                                                       (0)
#define M0_BYTE_4_m03932_mask                                                        (0x000000FF)
#define M0_BYTE_4_m03932(data)                                                       (0x000000FF&((data)<<0))
#define M0_BYTE_4_m03932_src(data)                                                   ((0x000000FF&(data))>>0)
#define M0_BYTE_4_get_m03932(data)                                                   ((0x000000FF&(data))>>0)


#define M0_BYTE_3                                                                    0x9803D100
#define M0_BYTE_3_reg_addr                                                           "0x9803D100"
#define M0_BYTE_3_reg                                                                0x9803D100
#define set_M0_BYTE_3_reg(data)   (*((volatile unsigned int*) M0_BYTE_3_reg)=data)
#define get_M0_BYTE_3_reg   (*((volatile unsigned int*) M0_BYTE_3_reg))
#define M0_BYTE_3_inst_adr                                                           "0x0040"
#define M0_BYTE_3_inst                                                               0x0040
#define M0_BYTE_3_m03124_shift                                                       (0)
#define M0_BYTE_3_m03124_mask                                                        (0x000000FF)
#define M0_BYTE_3_m03124(data)                                                       (0x000000FF&((data)<<0))
#define M0_BYTE_3_m03124_src(data)                                                   ((0x000000FF&(data))>>0)
#define M0_BYTE_3_get_m03124(data)                                                   ((0x000000FF&(data))>>0)


#define M0_BYTE_2                                                                    0x9803D104
#define M0_BYTE_2_reg_addr                                                           "0x9803D104"
#define M0_BYTE_2_reg                                                                0x9803D104
#define set_M0_BYTE_2_reg(data)   (*((volatile unsigned int*) M0_BYTE_2_reg)=data)
#define get_M0_BYTE_2_reg   (*((volatile unsigned int*) M0_BYTE_2_reg))
#define M0_BYTE_2_inst_adr                                                           "0x0041"
#define M0_BYTE_2_inst                                                               0x0041
#define M0_BYTE_2_m02316_shift                                                       (0)
#define M0_BYTE_2_m02316_mask                                                        (0x000000FF)
#define M0_BYTE_2_m02316(data)                                                       (0x000000FF&((data)<<0))
#define M0_BYTE_2_m02316_src(data)                                                   ((0x000000FF&(data))>>0)
#define M0_BYTE_2_get_m02316(data)                                                   ((0x000000FF&(data))>>0)


#define M0_BYTE_1                                                                    0x9803D108
#define M0_BYTE_1_reg_addr                                                           "0x9803D108"
#define M0_BYTE_1_reg                                                                0x9803D108
#define set_M0_BYTE_1_reg(data)   (*((volatile unsigned int*) M0_BYTE_1_reg)=data)
#define get_M0_BYTE_1_reg   (*((volatile unsigned int*) M0_BYTE_1_reg))
#define M0_BYTE_1_inst_adr                                                           "0x0042"
#define M0_BYTE_1_inst                                                               0x0042
#define M0_BYTE_1_m0158_shift                                                        (0)
#define M0_BYTE_1_m0158_mask                                                         (0x000000FF)
#define M0_BYTE_1_m0158(data)                                                        (0x000000FF&((data)<<0))
#define M0_BYTE_1_m0158_src(data)                                                    ((0x000000FF&(data))>>0)
#define M0_BYTE_1_get_m0158(data)                                                    ((0x000000FF&(data))>>0)


#define M0_BYTE_0                                                                    0x9803D10C
#define M0_BYTE_0_reg_addr                                                           "0x9803D10C"
#define M0_BYTE_0_reg                                                                0x9803D10C
#define set_M0_BYTE_0_reg(data)   (*((volatile unsigned int*) M0_BYTE_0_reg)=data)
#define get_M0_BYTE_0_reg   (*((volatile unsigned int*) M0_BYTE_0_reg))
#define M0_BYTE_0_inst_adr                                                           "0x0043"
#define M0_BYTE_0_inst                                                               0x0043
#define M0_BYTE_0_m070_shift                                                         (0)
#define M0_BYTE_0_m070_mask                                                          (0x000000FF)
#define M0_BYTE_0_m070(data)                                                         (0x000000FF&((data)<<0))
#define M0_BYTE_0_m070_src(data)                                                     ((0x000000FF&(data))>>0)
#define M0_BYTE_0_get_m070(data)                                                     ((0x000000FF&(data))>>0)


#define KM_BYTE_6                                                                    0x9803D110
#define KM_BYTE_6_reg_addr                                                           "0x9803D110"
#define KM_BYTE_6_reg                                                                0x9803D110
#define set_KM_BYTE_6_reg(data)   (*((volatile unsigned int*) KM_BYTE_6_reg)=data)
#define get_KM_BYTE_6_reg   (*((volatile unsigned int*) KM_BYTE_6_reg))
#define KM_BYTE_6_inst_adr                                                           "0x0044"
#define KM_BYTE_6_inst                                                               0x0044
#define KM_BYTE_6_km5548_shift                                                       (0)
#define KM_BYTE_6_km5548_mask                                                        (0x000000FF)
#define KM_BYTE_6_km5548(data)                                                       (0x000000FF&((data)<<0))
#define KM_BYTE_6_km5548_src(data)                                                   ((0x000000FF&(data))>>0)
#define KM_BYTE_6_get_km5548(data)                                                   ((0x000000FF&(data))>>0)


#define KM_BYTE_5                                                                    0x9803D114
#define KM_BYTE_5_reg_addr                                                           "0x9803D114"
#define KM_BYTE_5_reg                                                                0x9803D114
#define set_KM_BYTE_5_reg(data)   (*((volatile unsigned int*) KM_BYTE_5_reg)=data)
#define get_KM_BYTE_5_reg   (*((volatile unsigned int*) KM_BYTE_5_reg))
#define KM_BYTE_5_inst_adr                                                           "0x0045"
#define KM_BYTE_5_inst                                                               0x0045
#define KM_BYTE_5_km4740_shift                                                       (0)
#define KM_BYTE_5_km4740_mask                                                        (0x000000FF)
#define KM_BYTE_5_km4740(data)                                                       (0x000000FF&((data)<<0))
#define KM_BYTE_5_km4740_src(data)                                                   ((0x000000FF&(data))>>0)
#define KM_BYTE_5_get_km4740(data)                                                   ((0x000000FF&(data))>>0)


#define KM_BYTE_4                                                                    0x9803D118
#define KM_BYTE_4_reg_addr                                                           "0x9803D118"
#define KM_BYTE_4_reg                                                                0x9803D118
#define set_KM_BYTE_4_reg(data)   (*((volatile unsigned int*) KM_BYTE_4_reg)=data)
#define get_KM_BYTE_4_reg   (*((volatile unsigned int*) KM_BYTE_4_reg))
#define KM_BYTE_4_inst_adr                                                           "0x0046"
#define KM_BYTE_4_inst                                                               0x0046
#define KM_BYTE_4_km3932_shift                                                       (0)
#define KM_BYTE_4_km3932_mask                                                        (0x000000FF)
#define KM_BYTE_4_km3932(data)                                                       (0x000000FF&((data)<<0))
#define KM_BYTE_4_km3932_src(data)                                                   ((0x000000FF&(data))>>0)
#define KM_BYTE_4_get_km3932(data)                                                   ((0x000000FF&(data))>>0)


#define KM_BYTE_3                                                                    0x9803D11C
#define KM_BYTE_3_reg_addr                                                           "0x9803D11C"
#define KM_BYTE_3_reg                                                                0x9803D11C
#define set_KM_BYTE_3_reg(data)   (*((volatile unsigned int*) KM_BYTE_3_reg)=data)
#define get_KM_BYTE_3_reg   (*((volatile unsigned int*) KM_BYTE_3_reg))
#define KM_BYTE_3_inst_adr                                                           "0x0047"
#define KM_BYTE_3_inst                                                               0x0047
#define KM_BYTE_3_km3124_shift                                                       (0)
#define KM_BYTE_3_km3124_mask                                                        (0x000000FF)
#define KM_BYTE_3_km3124(data)                                                       (0x000000FF&((data)<<0))
#define KM_BYTE_3_km3124_src(data)                                                   ((0x000000FF&(data))>>0)
#define KM_BYTE_3_get_km3124(data)                                                   ((0x000000FF&(data))>>0)


#define KM_BYTE_2                                                                    0x9803D120
#define KM_BYTE_2_reg_addr                                                           "0x9803D120"
#define KM_BYTE_2_reg                                                                0x9803D120
#define set_KM_BYTE_2_reg(data)   (*((volatile unsigned int*) KM_BYTE_2_reg)=data)
#define get_KM_BYTE_2_reg   (*((volatile unsigned int*) KM_BYTE_2_reg))
#define KM_BYTE_2_inst_adr                                                           "0x0048"
#define KM_BYTE_2_inst                                                               0x0048
#define KM_BYTE_2_km2316_shift                                                       (0)
#define KM_BYTE_2_km2316_mask                                                        (0x000000FF)
#define KM_BYTE_2_km2316(data)                                                       (0x000000FF&((data)<<0))
#define KM_BYTE_2_km2316_src(data)                                                   ((0x000000FF&(data))>>0)
#define KM_BYTE_2_get_km2316(data)                                                   ((0x000000FF&(data))>>0)


#define KM_BYTE_1                                                                    0x9803D124
#define KM_BYTE_1_reg_addr                                                           "0x9803D124"
#define KM_BYTE_1_reg                                                                0x9803D124
#define set_KM_BYTE_1_reg(data)   (*((volatile unsigned int*) KM_BYTE_1_reg)=data)
#define get_KM_BYTE_1_reg   (*((volatile unsigned int*) KM_BYTE_1_reg))
#define KM_BYTE_1_inst_adr                                                           "0x0049"
#define KM_BYTE_1_inst                                                               0x0049
#define KM_BYTE_1_km158_shift                                                        (0)
#define KM_BYTE_1_km158_mask                                                         (0x000000FF)
#define KM_BYTE_1_km158(data)                                                        (0x000000FF&((data)<<0))
#define KM_BYTE_1_km158_src(data)                                                    ((0x000000FF&(data))>>0)
#define KM_BYTE_1_get_km158(data)                                                    ((0x000000FF&(data))>>0)


#define KM_BYTE_0                                                                    0x9803D128
#define KM_BYTE_0_reg_addr                                                           "0x9803D128"
#define KM_BYTE_0_reg                                                                0x9803D128
#define set_KM_BYTE_0_reg(data)   (*((volatile unsigned int*) KM_BYTE_0_reg)=data)
#define get_KM_BYTE_0_reg   (*((volatile unsigned int*) KM_BYTE_0_reg))
#define KM_BYTE_0_inst_adr                                                           "0x004A"
#define KM_BYTE_0_inst                                                               0x004A
#define KM_BYTE_0_km70_shift                                                         (0)
#define KM_BYTE_0_km70_mask                                                          (0x000000FF)
#define KM_BYTE_0_km70(data)                                                         (0x000000FF&((data)<<0))
#define KM_BYTE_0_km70_src(data)                                                     ((0x000000FF&(data))>>0)
#define KM_BYTE_0_get_km70(data)                                                     ((0x000000FF&(data))>>0)


#define R0_BYTE_MSB                                                                  0x9803D12C
#define R0_BYTE_MSB_reg_addr                                                         "0x9803D12C"
#define R0_BYTE_MSB_reg                                                              0x9803D12C
#define set_R0_BYTE_MSB_reg(data)   (*((volatile unsigned int*) R0_BYTE_MSB_reg)=data)
#define get_R0_BYTE_MSB_reg   (*((volatile unsigned int*) R0_BYTE_MSB_reg))
#define R0_BYTE_MSB_inst_adr                                                         "0x004B"
#define R0_BYTE_MSB_inst                                                             0x004B
#define R0_BYTE_MSB_r0158_shift                                                      (0)
#define R0_BYTE_MSB_r0158_mask                                                       (0x000000FF)
#define R0_BYTE_MSB_r0158(data)                                                      (0x000000FF&((data)<<0))
#define R0_BYTE_MSB_r0158_src(data)                                                  ((0x000000FF&(data))>>0)
#define R0_BYTE_MSB_get_r0158(data)                                                  ((0x000000FF&(data))>>0)


#define R0_BYTE_LSB                                                                  0x9803D130
#define R0_BYTE_LSB_reg_addr                                                         "0x9803D130"
#define R0_BYTE_LSB_reg                                                              0x9803D130
#define set_R0_BYTE_LSB_reg(data)   (*((volatile unsigned int*) R0_BYTE_LSB_reg)=data)
#define get_R0_BYTE_LSB_reg   (*((volatile unsigned int*) R0_BYTE_LSB_reg))
#define R0_BYTE_LSB_inst_adr                                                         "0x004C"
#define R0_BYTE_LSB_inst                                                             0x004C
#define R0_BYTE_LSB_r070_shift                                                       (0)
#define R0_BYTE_LSB_r070_mask                                                        (0x000000FF)
#define R0_BYTE_LSB_r070(data)                                                       (0x000000FF&((data)<<0))
#define R0_BYTE_LSB_r070_src(data)                                                   ((0x000000FF&(data))>>0)
#define R0_BYTE_LSB_get_r070(data)                                                   ((0x000000FF&(data))>>0)


#define RI_BYTE_MSB                                                                  0x9803D134
#define RI_BYTE_MSB_reg_addr                                                         "0x9803D134"
#define RI_BYTE_MSB_reg                                                              0x9803D134
#define set_RI_BYTE_MSB_reg(data)   (*((volatile unsigned int*) RI_BYTE_MSB_reg)=data)
#define get_RI_BYTE_MSB_reg   (*((volatile unsigned int*) RI_BYTE_MSB_reg))
#define RI_BYTE_MSB_inst_adr                                                         "0x004D"
#define RI_BYTE_MSB_inst                                                             0x004D
#define RI_BYTE_MSB_ri158_shift                                                      (0)
#define RI_BYTE_MSB_ri158_mask                                                       (0x000000FF)
#define RI_BYTE_MSB_ri158(data)                                                      (0x000000FF&((data)<<0))
#define RI_BYTE_MSB_ri158_src(data)                                                  ((0x000000FF&(data))>>0)
#define RI_BYTE_MSB_get_ri158(data)                                                  ((0x000000FF&(data))>>0)


#define RI_BYTE_LSB                                                                  0x9803D138
#define RI_BYTE_LSB_reg_addr                                                         "0x9803D138"
#define RI_BYTE_LSB_reg                                                              0x9803D138
#define set_RI_BYTE_LSB_reg(data)   (*((volatile unsigned int*) RI_BYTE_LSB_reg)=data)
#define get_RI_BYTE_LSB_reg   (*((volatile unsigned int*) RI_BYTE_LSB_reg))
#define RI_BYTE_LSB_inst_adr                                                         "0x004E"
#define RI_BYTE_LSB_inst                                                             0x004E
#define RI_BYTE_LSB_ri70_shift                                                       (0)
#define RI_BYTE_LSB_ri70_mask                                                        (0x000000FF)
#define RI_BYTE_LSB_ri70(data)                                                       (0x000000FF&((data)<<0))
#define RI_BYTE_LSB_ri70_src(data)                                                   ((0x000000FF&(data))>>0)
#define RI_BYTE_LSB_get_ri70(data)                                                   ((0x000000FF&(data))>>0)


#define BKSV_0                                                                       0x9803D13C
#define BKSV_0_reg_addr                                                              "0x9803D13C"
#define BKSV_0_reg                                                                   0x9803D13C
#define set_BKSV_0_reg(data)   (*((volatile unsigned int*) BKSV_0_reg)=data)
#define get_BKSV_0_reg   (*((volatile unsigned int*) BKSV_0_reg))
#define BKSV_0_inst_adr                                                              "0x004F"
#define BKSV_0_inst                                                                  0x004F
#define BKSV_0_bksv70_shift                                                          (0)
#define BKSV_0_bksv70_mask                                                           (0x000000FF)
#define BKSV_0_bksv70(data)                                                          (0x000000FF&((data)<<0))
#define BKSV_0_bksv70_src(data)                                                      ((0x000000FF&(data))>>0)
#define BKSV_0_get_bksv70(data)                                                      ((0x000000FF&(data))>>0)


#define BKSV_1                                                                       0x9803D140
#define BKSV_1_reg_addr                                                              "0x9803D140"
#define BKSV_1_reg                                                                   0x9803D140
#define set_BKSV_1_reg(data)   (*((volatile unsigned int*) BKSV_1_reg)=data)
#define get_BKSV_1_reg   (*((volatile unsigned int*) BKSV_1_reg))
#define BKSV_1_inst_adr                                                              "0x0050"
#define BKSV_1_inst                                                                  0x0050
#define BKSV_1_bksv158_shift                                                         (0)
#define BKSV_1_bksv158_mask                                                          (0x000000FF)
#define BKSV_1_bksv158(data)                                                         (0x000000FF&((data)<<0))
#define BKSV_1_bksv158_src(data)                                                     ((0x000000FF&(data))>>0)
#define BKSV_1_get_bksv158(data)                                                     ((0x000000FF&(data))>>0)


#define BKSV_2                                                                       0x9803D144
#define BKSV_2_reg_addr                                                              "0x9803D144"
#define BKSV_2_reg                                                                   0x9803D144
#define set_BKSV_2_reg(data)   (*((volatile unsigned int*) BKSV_2_reg)=data)
#define get_BKSV_2_reg   (*((volatile unsigned int*) BKSV_2_reg))
#define BKSV_2_inst_adr                                                              "0x0051"
#define BKSV_2_inst                                                                  0x0051
#define BKSV_2_bksv2316_shift                                                        (0)
#define BKSV_2_bksv2316_mask                                                         (0x000000FF)
#define BKSV_2_bksv2316(data)                                                        (0x000000FF&((data)<<0))
#define BKSV_2_bksv2316_src(data)                                                    ((0x000000FF&(data))>>0)
#define BKSV_2_get_bksv2316(data)                                                    ((0x000000FF&(data))>>0)


#define BKSV_3                                                                       0x9803D148
#define BKSV_3_reg_addr                                                              "0x9803D148"
#define BKSV_3_reg                                                                   0x9803D148
#define set_BKSV_3_reg(data)   (*((volatile unsigned int*) BKSV_3_reg)=data)
#define get_BKSV_3_reg   (*((volatile unsigned int*) BKSV_3_reg))
#define BKSV_3_inst_adr                                                              "0x0052"
#define BKSV_3_inst                                                                  0x0052
#define BKSV_3_bksv3124_shift                                                        (0)
#define BKSV_3_bksv3124_mask                                                         (0x000000FF)
#define BKSV_3_bksv3124(data)                                                        (0x000000FF&((data)<<0))
#define BKSV_3_bksv3124_src(data)                                                    ((0x000000FF&(data))>>0)
#define BKSV_3_get_bksv3124(data)                                                    ((0x000000FF&(data))>>0)


#define BKSV_4                                                                       0x9803D14C
#define BKSV_4_reg_addr                                                              "0x9803D14C"
#define BKSV_4_reg                                                                   0x9803D14C
#define set_BKSV_4_reg(data)   (*((volatile unsigned int*) BKSV_4_reg)=data)
#define get_BKSV_4_reg   (*((volatile unsigned int*) BKSV_4_reg))
#define BKSV_4_inst_adr                                                              "0x0053"
#define BKSV_4_inst                                                                  0x0053
#define BKSV_4_bksv3932_shift                                                        (0)
#define BKSV_4_bksv3932_mask                                                         (0x000000FF)
#define BKSV_4_bksv3932(data)                                                        (0x000000FF&((data)<<0))
#define BKSV_4_bksv3932_src(data)                                                    ((0x000000FF&(data))>>0)
#define BKSV_4_get_bksv3932(data)                                                    ((0x000000FF&(data))>>0)


#define HDCP_TX_LIP_H                                                                0x9803D150
#define HDCP_TX_LIP_H_reg_addr                                                       "0x9803D150"
#define HDCP_TX_LIP_H_reg                                                            0x9803D150
#define set_HDCP_TX_LIP_H_reg(data)   (*((volatile unsigned int*) HDCP_TX_LIP_H_reg)=data)
#define get_HDCP_TX_LIP_H_reg   (*((volatile unsigned int*) HDCP_TX_LIP_H_reg))
#define HDCP_TX_LIP_H_inst_adr                                                       "0x0054"
#define HDCP_TX_LIP_H_inst                                                           0x0054
#define HDCP_TX_LIP_H_li_pattern158_shift                                            (0)
#define HDCP_TX_LIP_H_li_pattern158_mask                                             (0x000000FF)
#define HDCP_TX_LIP_H_li_pattern158(data)                                            (0x000000FF&((data)<<0))
#define HDCP_TX_LIP_H_li_pattern158_src(data)                                        ((0x000000FF&(data))>>0)
#define HDCP_TX_LIP_H_get_li_pattern158(data)                                        ((0x000000FF&(data))>>0)


#define HDCP_TX_LIP_L                                                                0x9803D154
#define HDCP_TX_LIP_L_reg_addr                                                       "0x9803D154"
#define HDCP_TX_LIP_L_reg                                                            0x9803D154
#define set_HDCP_TX_LIP_L_reg(data)   (*((volatile unsigned int*) HDCP_TX_LIP_L_reg)=data)
#define get_HDCP_TX_LIP_L_reg   (*((volatile unsigned int*) HDCP_TX_LIP_L_reg))
#define HDCP_TX_LIP_L_inst_adr                                                       "0x0055"
#define HDCP_TX_LIP_L_inst                                                           0x0055
#define HDCP_TX_LIP_L_li_pattern70_shift                                             (0)
#define HDCP_TX_LIP_L_li_pattern70_mask                                              (0x000000FF)
#define HDCP_TX_LIP_L_li_pattern70(data)                                             (0x000000FF&((data)<<0))
#define HDCP_TX_LIP_L_li_pattern70_src(data)                                         ((0x000000FF&(data))>>0)
#define HDCP_TX_LIP_L_get_li_pattern70(data)                                         ((0x000000FF&(data))>>0)


#define DP_HDCP_TX                                                                   0x9803D158
#define DP_HDCP_TX_reg_addr                                                          "0x9803D158"
#define DP_HDCP_TX_reg                                                               0x9803D158
#define set_DP_HDCP_TX_reg(data)   (*((volatile unsigned int*) DP_HDCP_TX_reg)=data)
#define get_DP_HDCP_TX_reg   (*((volatile unsigned int*) DP_HDCP_TX_reg))
#define DP_HDCP_TX_inst_adr                                                          "0x0056"
#define DP_HDCP_TX_inst                                                              0x0056
#define DP_HDCP_TX_lk_pos_shift                                                      (7)
#define DP_HDCP_TX_lk_pos_mask                                                       (0x00000080)
#define DP_HDCP_TX_lk_pos(data)                                                      (0x00000080&((data)<<7))
#define DP_HDCP_TX_lk_pos_src(data)                                                  ((0x00000080&(data))>>7)
#define DP_HDCP_TX_get_lk_pos(data)                                                  ((0x00000080&(data))>>7)
#define DP_HDCP_TX_Reserved_shift                                                    (4)
#define DP_HDCP_TX_Reserved_mask                                                     (0x00000070)
#define DP_HDCP_TX_Reserved(data)                                                    (0x00000070&((data)<<4))
#define DP_HDCP_TX_Reserved_src(data)                                                ((0x00000070&(data))>>4)
#define DP_HDCP_TX_get_Reserved(data)                                                ((0x00000070&(data))>>4)
#define DP_HDCP_TX_freerun_init_en_shift                                             (3)
#define DP_HDCP_TX_freerun_init_en_mask                                              (0x00000008)
#define DP_HDCP_TX_freerun_init_en(data)                                             (0x00000008&((data)<<3))
#define DP_HDCP_TX_freerun_init_en_src(data)                                         ((0x00000008&(data))>>3)
#define DP_HDCP_TX_get_freerun_init_en(data)                                         ((0x00000008&(data))>>3)
#define DP_HDCP_TX_check_bksv_en_shift                                               (2)
#define DP_HDCP_TX_check_bksv_en_mask                                                (0x00000004)
#define DP_HDCP_TX_check_bksv_en(data)                                               (0x00000004&((data)<<2))
#define DP_HDCP_TX_check_bksv_en_src(data)                                           ((0x00000004&(data))>>2)
#define DP_HDCP_TX_get_check_bksv_en(data)                                           ((0x00000004&(data))>>2)
#define DP_HDCP_TX_check_bksv_done_shift                                             (1)
#define DP_HDCP_TX_check_bksv_done_mask                                              (0x00000002)
#define DP_HDCP_TX_check_bksv_done(data)                                             (0x00000002&((data)<<1))
#define DP_HDCP_TX_check_bksv_done_src(data)                                         ((0x00000002&(data))>>1)
#define DP_HDCP_TX_get_check_bksv_done(data)                                         ((0x00000002&(data))>>1)
#define DP_HDCP_TX_check_bksv_fail_shift                                             (0)
#define DP_HDCP_TX_check_bksv_fail_mask                                              (0x00000001)
#define DP_HDCP_TX_check_bksv_fail(data)                                             (0x00000001&((data)<<0))
#define DP_HDCP_TX_check_bksv_fail_src(data)                                         ((0x00000001&(data))>>0)
#define DP_HDCP_TX_get_check_bksv_fail(data)                                         ((0x00000001&(data))>>0)


#define DP_HDCP_BIST                                                                 0x9803D15C
#define DP_HDCP_BIST_reg_addr                                                        "0x9803D15C"
#define DP_HDCP_BIST_reg                                                             0x9803D15C
#define set_DP_HDCP_BIST_reg(data)   (*((volatile unsigned int*) DP_HDCP_BIST_reg)=data)
#define get_DP_HDCP_BIST_reg   (*((volatile unsigned int*) DP_HDCP_BIST_reg))
#define DP_HDCP_BIST_inst_adr                                                        "0x0057"
#define DP_HDCP_BIST_inst                                                            0x0057
#define DP_HDCP_BIST_hdcp_drf_bist_en_shift                                          (7)
#define DP_HDCP_BIST_hdcp_drf_bist_en_mask                                           (0x00000080)
#define DP_HDCP_BIST_hdcp_drf_bist_en(data)                                          (0x00000080&((data)<<7))
#define DP_HDCP_BIST_hdcp_drf_bist_en_src(data)                                      ((0x00000080&(data))>>7)
#define DP_HDCP_BIST_get_hdcp_drf_bist_en(data)                                      ((0x00000080&(data))>>7)
#define DP_HDCP_BIST_hdcp_drf_bist_done_shift                                        (6)
#define DP_HDCP_BIST_hdcp_drf_bist_done_mask                                         (0x00000040)
#define DP_HDCP_BIST_hdcp_drf_bist_done(data)                                        (0x00000040&((data)<<6))
#define DP_HDCP_BIST_hdcp_drf_bist_done_src(data)                                    ((0x00000040&(data))>>6)
#define DP_HDCP_BIST_get_hdcp_drf_bist_done(data)                                    ((0x00000040&(data))>>6)
#define DP_HDCP_BIST_hdcp_drf_bist_fail_shift                                        (5)
#define DP_HDCP_BIST_hdcp_drf_bist_fail_mask                                         (0x00000020)
#define DP_HDCP_BIST_hdcp_drf_bist_fail(data)                                        (0x00000020&((data)<<5))
#define DP_HDCP_BIST_hdcp_drf_bist_fail_src(data)                                    ((0x00000020&(data))>>5)
#define DP_HDCP_BIST_get_hdcp_drf_bist_fail(data)                                    ((0x00000020&(data))>>5)
#define DP_HDCP_BIST_hdcp_drf_test_resume_shift                                      (4)
#define DP_HDCP_BIST_hdcp_drf_test_resume_mask                                       (0x00000010)
#define DP_HDCP_BIST_hdcp_drf_test_resume(data)                                      (0x00000010&((data)<<4))
#define DP_HDCP_BIST_hdcp_drf_test_resume_src(data)                                  ((0x00000010&(data))>>4)
#define DP_HDCP_BIST_get_hdcp_drf_test_resume(data)                                  ((0x00000010&(data))>>4)
#define DP_HDCP_BIST_hdcp_drf_start_pause_shift                                      (3)
#define DP_HDCP_BIST_hdcp_drf_start_pause_mask                                       (0x00000008)
#define DP_HDCP_BIST_hdcp_drf_start_pause(data)                                      (0x00000008&((data)<<3))
#define DP_HDCP_BIST_hdcp_drf_start_pause_src(data)                                  ((0x00000008&(data))>>3)
#define DP_HDCP_BIST_get_hdcp_drf_start_pause(data)                                  ((0x00000008&(data))>>3)
#define DP_HDCP_BIST_hdcp_bist_en_shift                                              (2)
#define DP_HDCP_BIST_hdcp_bist_en_mask                                               (0x00000004)
#define DP_HDCP_BIST_hdcp_bist_en(data)                                              (0x00000004&((data)<<2))
#define DP_HDCP_BIST_hdcp_bist_en_src(data)                                          ((0x00000004&(data))>>2)
#define DP_HDCP_BIST_get_hdcp_bist_en(data)                                          ((0x00000004&(data))>>2)
#define DP_HDCP_BIST_hdcp_bist_done_shift                                            (1)
#define DP_HDCP_BIST_hdcp_bist_done_mask                                             (0x00000002)
#define DP_HDCP_BIST_hdcp_bist_done(data)                                            (0x00000002&((data)<<1))
#define DP_HDCP_BIST_hdcp_bist_done_src(data)                                        ((0x00000002&(data))>>1)
#define DP_HDCP_BIST_get_hdcp_bist_done(data)                                        ((0x00000002&(data))>>1)
#define DP_HDCP_BIST_hdcp_bist_fail_shift                                            (0)
#define DP_HDCP_BIST_hdcp_bist_fail_mask                                             (0x00000001)
#define DP_HDCP_BIST_hdcp_bist_fail(data)                                            (0x00000001&((data)<<0))
#define DP_HDCP_BIST_hdcp_bist_fail_src(data)                                        ((0x00000001&(data))>>0)
#define DP_HDCP_BIST_get_hdcp_bist_fail(data)                                        ((0x00000001&(data))>>0)


#define DP_HDCP_AN_SEED                                                              0x9803D160
#define DP_HDCP_AN_SEED_reg_addr                                                     "0x9803D160"
#define DP_HDCP_AN_SEED_reg                                                          0x9803D160
#define set_DP_HDCP_AN_SEED_reg(data)   (*((volatile unsigned int*) DP_HDCP_AN_SEED_reg)=data)
#define get_DP_HDCP_AN_SEED_reg   (*((volatile unsigned int*) DP_HDCP_AN_SEED_reg))
#define DP_HDCP_AN_SEED_inst_adr                                                     "0x0058"
#define DP_HDCP_AN_SEED_inst                                                         0x0058
#define DP_HDCP_AN_SEED_freerun_init_shift                                           (0)
#define DP_HDCP_AN_SEED_freerun_init_mask                                            (0x000000FF)
#define DP_HDCP_AN_SEED_freerun_init(data)                                           (0x000000FF&((data)<<0))
#define DP_HDCP_AN_SEED_freerun_init_src(data)                                       ((0x000000FF&(data))>>0)
#define DP_HDCP_AN_SEED_get_freerun_init(data)                                       ((0x000000FF&(data))>>0)


#define HDCP_IRQ_EVENT                                                               0x9803D164
#define HDCP_IRQ_EVENT_reg_addr                                                      "0x9803D164"
#define HDCP_IRQ_EVENT_reg                                                           0x9803D164
#define set_HDCP_IRQ_EVENT_reg(data)   (*((volatile unsigned int*) HDCP_IRQ_EVENT_reg)=data)
#define get_HDCP_IRQ_EVENT_reg   (*((volatile unsigned int*) HDCP_IRQ_EVENT_reg))
#define HDCP_IRQ_EVENT_inst_adr                                                      "0x0059"
#define HDCP_IRQ_EVENT_inst                                                          0x0059
#define HDCP_IRQ_EVENT_dp_hdcp_tx_irq_shift                                          (7)
#define HDCP_IRQ_EVENT_dp_hdcp_tx_irq_mask                                           (0x00000080)
#define HDCP_IRQ_EVENT_dp_hdcp_tx_irq(data)                                          (0x00000080&((data)<<7))
#define HDCP_IRQ_EVENT_dp_hdcp_tx_irq_src(data)                                      ((0x00000080&(data))>>7)
#define HDCP_IRQ_EVENT_get_dp_hdcp_tx_irq(data)                                      ((0x00000080&(data))>>7)
#define HDCP_IRQ_EVENT_Reserved_shift                                                (3)
#define HDCP_IRQ_EVENT_Reserved_mask                                                 (0x00000078)
#define HDCP_IRQ_EVENT_Reserved(data)                                                (0x00000078&((data)<<3))
#define HDCP_IRQ_EVENT_Reserved_src(data)                                            ((0x00000078&(data))>>3)
#define HDCP_IRQ_EVENT_get_Reserved(data)                                            ((0x00000078&(data))>>3)
#define HDCP_IRQ_EVENT_computation_done_irq_en_shift                                 (2)
#define HDCP_IRQ_EVENT_computation_done_irq_en_mask                                  (0x00000004)
#define HDCP_IRQ_EVENT_computation_done_irq_en(data)                                 (0x00000004&((data)<<2))
#define HDCP_IRQ_EVENT_computation_done_irq_en_src(data)                             ((0x00000004&(data))>>2)
#define HDCP_IRQ_EVENT_get_computation_done_irq_en(data)                             ((0x00000004&(data))>>2)
#define HDCP_IRQ_EVENT_bksv_fail_irq_en_shift                                        (1)
#define HDCP_IRQ_EVENT_bksv_fail_irq_en_mask                                         (0x00000002)
#define HDCP_IRQ_EVENT_bksv_fail_irq_en(data)                                        (0x00000002&((data)<<1))
#define HDCP_IRQ_EVENT_bksv_fail_irq_en_src(data)                                    ((0x00000002&(data))>>1)
#define HDCP_IRQ_EVENT_get_bksv_fail_irq_en(data)                                    ((0x00000002&(data))>>1)
#define HDCP_IRQ_EVENT_bksv_done_irq_en_shift                                        (0)
#define HDCP_IRQ_EVENT_bksv_done_irq_en_mask                                         (0x00000001)
#define HDCP_IRQ_EVENT_bksv_done_irq_en(data)                                        (0x00000001&((data)<<0))
#define HDCP_IRQ_EVENT_bksv_done_irq_en_src(data)                                    ((0x00000001&(data))>>0)
#define HDCP_IRQ_EVENT_get_bksv_done_irq_en(data)                                    ((0x00000001&(data))>>0)


#define DPTX_HDCP_TST                                                                0x9803D168
#define DPTX_HDCP_TST_reg_addr                                                       "0x9803D168"
#define DPTX_HDCP_TST_reg                                                            0x9803D168
#define set_DPTX_HDCP_TST_reg(data)   (*((volatile unsigned int*) DPTX_HDCP_TST_reg)=data)
#define get_DPTX_HDCP_TST_reg   (*((volatile unsigned int*) DPTX_HDCP_TST_reg))
#define DPTX_HDCP_TST_inst_adr                                                       "0x005A"
#define DPTX_HDCP_TST_inst                                                           0x005A
#define DPTX_HDCP_TST_Reserved_shift                                                 (5)
#define DPTX_HDCP_TST_Reserved_mask                                                  (0x000000E0)
#define DPTX_HDCP_TST_Reserved(data)                                                 (0x000000E0&((data)<<5))
#define DPTX_HDCP_TST_Reserved_src(data)                                             ((0x000000E0&(data))>>5)
#define DPTX_HDCP_TST_get_Reserved(data)                                             ((0x000000E0&(data))>>5)
#define DPTX_HDCP_TST_authdone_shift                                                 (4)
#define DPTX_HDCP_TST_authdone_mask                                                  (0x00000010)
#define DPTX_HDCP_TST_authdone(data)                                                 (0x00000010&((data)<<4))
#define DPTX_HDCP_TST_authdone_src(data)                                             ((0x00000010&(data))>>4)
#define DPTX_HDCP_TST_get_authdone(data)                                             ((0x00000010&(data))>>4)
#define DPTX_HDCP_TST_authkm_shift                                                   (3)
#define DPTX_HDCP_TST_authkm_mask                                                    (0x00000008)
#define DPTX_HDCP_TST_authkm(data)                                                   (0x00000008&((data)<<3))
#define DPTX_HDCP_TST_authkm_src(data)                                               ((0x00000008&(data))>>3)
#define DPTX_HDCP_TST_get_authkm(data)                                               ((0x00000008&(data))>>3)
#define DPTX_HDCP_TST_dp_hdcp_tst_mode_shift                                         (1)
#define DPTX_HDCP_TST_dp_hdcp_tst_mode_mask                                          (0x00000006)
#define DPTX_HDCP_TST_dp_hdcp_tst_mode(data)                                         (0x00000006&((data)<<1))
#define DPTX_HDCP_TST_dp_hdcp_tst_mode_src(data)                                     ((0x00000006&(data))>>1)
#define DPTX_HDCP_TST_get_dp_hdcp_tst_mode(data)                                     ((0x00000006&(data))>>1)
#define DPTX_HDCP_TST_dp_hdcp_tst_en_shift                                           (0)
#define DPTX_HDCP_TST_dp_hdcp_tst_en_mask                                            (0x00000001)
#define DPTX_HDCP_TST_dp_hdcp_tst_en(data)                                           (0x00000001&((data)<<0))
#define DPTX_HDCP_TST_dp_hdcp_tst_en_src(data)                                       ((0x00000001&(data))>>0)
#define DPTX_HDCP_TST_get_dp_hdcp_tst_en(data)                                       ((0x00000001&(data))>>0)


#define DP_HDCP_TX_SHA_CTRL                                                          0x9803D16C
#define DP_HDCP_TX_SHA_CTRL_reg_addr                                                 "0x9803D16C"
#define DP_HDCP_TX_SHA_CTRL_reg                                                      0x9803D16C
#define set_DP_HDCP_TX_SHA_CTRL_reg(data)   (*((volatile unsigned int*) DP_HDCP_TX_SHA_CTRL_reg)=data)
#define get_DP_HDCP_TX_SHA_CTRL_reg   (*((volatile unsigned int*) DP_HDCP_TX_SHA_CTRL_reg))
#define DP_HDCP_TX_SHA_CTRL_inst_adr                                                 "0x005B"
#define DP_HDCP_TX_SHA_CTRL_inst                                                     0x005B
#define DP_HDCP_TX_SHA_CTRL_sha_v_select_shift                                       (5)
#define DP_HDCP_TX_SHA_CTRL_sha_v_select_mask                                        (0x000000E0)
#define DP_HDCP_TX_SHA_CTRL_sha_v_select(data)                                       (0x000000E0&((data)<<5))
#define DP_HDCP_TX_SHA_CTRL_sha_v_select_src(data)                                   ((0x000000E0&(data))>>5)
#define DP_HDCP_TX_SHA_CTRL_get_sha_v_select(data)                                   ((0x000000E0&(data))>>5)
#define DP_HDCP_TX_SHA_CTRL_sha_done_shift                                           (4)
#define DP_HDCP_TX_SHA_CTRL_sha_done_mask                                            (0x00000010)
#define DP_HDCP_TX_SHA_CTRL_sha_done(data)                                           (0x00000010&((data)<<4))
#define DP_HDCP_TX_SHA_CTRL_sha_done_src(data)                                       ((0x00000010&(data))>>4)
#define DP_HDCP_TX_SHA_CTRL_get_sha_done(data)                                       ((0x00000010&(data))>>4)
#define DP_HDCP_TX_SHA_CTRL_sha_run_first_shift                                      (3)
#define DP_HDCP_TX_SHA_CTRL_sha_run_first_mask                                       (0x00000008)
#define DP_HDCP_TX_SHA_CTRL_sha_run_first(data)                                      (0x00000008&((data)<<3))
#define DP_HDCP_TX_SHA_CTRL_sha_run_first_src(data)                                  ((0x00000008&(data))>>3)
#define DP_HDCP_TX_SHA_CTRL_get_sha_run_first(data)                                  ((0x00000008&(data))>>3)
#define DP_HDCP_TX_SHA_CTRL_sha_run_en_shift                                         (2)
#define DP_HDCP_TX_SHA_CTRL_sha_run_en_mask                                          (0x00000004)
#define DP_HDCP_TX_SHA_CTRL_sha_run_en(data)                                         (0x00000004&((data)<<2))
#define DP_HDCP_TX_SHA_CTRL_sha_run_en_src(data)                                     ((0x00000004&(data))>>2)
#define DP_HDCP_TX_SHA_CTRL_get_sha_run_en(data)                                     ((0x00000004&(data))>>2)
#define DP_HDCP_TX_SHA_CTRL_sha_wptr_rst_shift                                       (1)
#define DP_HDCP_TX_SHA_CTRL_sha_wptr_rst_mask                                        (0x00000002)
#define DP_HDCP_TX_SHA_CTRL_sha_wptr_rst(data)                                       (0x00000002&((data)<<1))
#define DP_HDCP_TX_SHA_CTRL_sha_wptr_rst_src(data)                                   ((0x00000002&(data))>>1)
#define DP_HDCP_TX_SHA_CTRL_get_sha_wptr_rst(data)                                   ((0x00000002&(data))>>1)
#define DP_HDCP_TX_SHA_CTRL_sha_data_wen_shift                                       (0)
#define DP_HDCP_TX_SHA_CTRL_sha_data_wen_mask                                        (0x00000001)
#define DP_HDCP_TX_SHA_CTRL_sha_data_wen(data)                                       (0x00000001&((data)<<0))
#define DP_HDCP_TX_SHA_CTRL_sha_data_wen_src(data)                                   ((0x00000001&(data))>>0)
#define DP_HDCP_TX_SHA_CTRL_get_sha_data_wen(data)                                   ((0x00000001&(data))>>0)


#define DP_HDCP_TX_SHA_DATA_3                                                        0x9803D170
#define DP_HDCP_TX_SHA_DATA_3_reg_addr                                               "0x9803D170"
#define DP_HDCP_TX_SHA_DATA_3_reg                                                    0x9803D170
#define set_DP_HDCP_TX_SHA_DATA_3_reg(data)   (*((volatile unsigned int*) DP_HDCP_TX_SHA_DATA_3_reg)=data)
#define get_DP_HDCP_TX_SHA_DATA_3_reg   (*((volatile unsigned int*) DP_HDCP_TX_SHA_DATA_3_reg))
#define DP_HDCP_TX_SHA_DATA_3_inst_adr                                               "0x005C"
#define DP_HDCP_TX_SHA_DATA_3_inst                                                   0x005C
#define DP_HDCP_TX_SHA_DATA_3_sha_data3124_shift                                     (0)
#define DP_HDCP_TX_SHA_DATA_3_sha_data3124_mask                                      (0x000000FF)
#define DP_HDCP_TX_SHA_DATA_3_sha_data3124(data)                                     (0x000000FF&((data)<<0))
#define DP_HDCP_TX_SHA_DATA_3_sha_data3124_src(data)                                 ((0x000000FF&(data))>>0)
#define DP_HDCP_TX_SHA_DATA_3_get_sha_data3124(data)                                 ((0x000000FF&(data))>>0)


#define DP_HDCP_TX_SHA_DATA_2                                                        0x9803D174
#define DP_HDCP_TX_SHA_DATA_2_reg_addr                                               "0x9803D174"
#define DP_HDCP_TX_SHA_DATA_2_reg                                                    0x9803D174
#define set_DP_HDCP_TX_SHA_DATA_2_reg(data)   (*((volatile unsigned int*) DP_HDCP_TX_SHA_DATA_2_reg)=data)
#define get_DP_HDCP_TX_SHA_DATA_2_reg   (*((volatile unsigned int*) DP_HDCP_TX_SHA_DATA_2_reg))
#define DP_HDCP_TX_SHA_DATA_2_inst_adr                                               "0x005D"
#define DP_HDCP_TX_SHA_DATA_2_inst                                                   0x005D
#define DP_HDCP_TX_SHA_DATA_2_sha_data2316_shift                                     (0)
#define DP_HDCP_TX_SHA_DATA_2_sha_data2316_mask                                      (0x000000FF)
#define DP_HDCP_TX_SHA_DATA_2_sha_data2316(data)                                     (0x000000FF&((data)<<0))
#define DP_HDCP_TX_SHA_DATA_2_sha_data2316_src(data)                                 ((0x000000FF&(data))>>0)
#define DP_HDCP_TX_SHA_DATA_2_get_sha_data2316(data)                                 ((0x000000FF&(data))>>0)


#define DP_HDCP_TX_SHA_DATA_1                                                        0x9803D178
#define DP_HDCP_TX_SHA_DATA_1_reg_addr                                               "0x9803D178"
#define DP_HDCP_TX_SHA_DATA_1_reg                                                    0x9803D178
#define set_DP_HDCP_TX_SHA_DATA_1_reg(data)   (*((volatile unsigned int*) DP_HDCP_TX_SHA_DATA_1_reg)=data)
#define get_DP_HDCP_TX_SHA_DATA_1_reg   (*((volatile unsigned int*) DP_HDCP_TX_SHA_DATA_1_reg))
#define DP_HDCP_TX_SHA_DATA_1_inst_adr                                               "0x005E"
#define DP_HDCP_TX_SHA_DATA_1_inst                                                   0x005E
#define DP_HDCP_TX_SHA_DATA_1_sha_data158_shift                                      (0)
#define DP_HDCP_TX_SHA_DATA_1_sha_data158_mask                                       (0x000000FF)
#define DP_HDCP_TX_SHA_DATA_1_sha_data158(data)                                      (0x000000FF&((data)<<0))
#define DP_HDCP_TX_SHA_DATA_1_sha_data158_src(data)                                  ((0x000000FF&(data))>>0)
#define DP_HDCP_TX_SHA_DATA_1_get_sha_data158(data)                                  ((0x000000FF&(data))>>0)


#define DP_HDCP_TX_SHA_DATA_0                                                        0x9803D17C
#define DP_HDCP_TX_SHA_DATA_0_reg_addr                                               "0x9803D17C"
#define DP_HDCP_TX_SHA_DATA_0_reg                                                    0x9803D17C
#define set_DP_HDCP_TX_SHA_DATA_0_reg(data)   (*((volatile unsigned int*) DP_HDCP_TX_SHA_DATA_0_reg)=data)
#define get_DP_HDCP_TX_SHA_DATA_0_reg   (*((volatile unsigned int*) DP_HDCP_TX_SHA_DATA_0_reg))
#define DP_HDCP_TX_SHA_DATA_0_inst_adr                                               "0x005F"
#define DP_HDCP_TX_SHA_DATA_0_inst                                                   0x005F
#define DP_HDCP_TX_SHA_DATA_0_sha_data70_shift                                       (0)
#define DP_HDCP_TX_SHA_DATA_0_sha_data70_mask                                        (0x000000FF)
#define DP_HDCP_TX_SHA_DATA_0_sha_data70(data)                                       (0x000000FF&((data)<<0))
#define DP_HDCP_TX_SHA_DATA_0_sha_data70_src(data)                                   ((0x000000FF&(data))>>0)
#define DP_HDCP_TX_SHA_DATA_0_get_sha_data70(data)                                   ((0x000000FF&(data))>>0)


#define DP_HDCP_TX_SHA_OUT_3                                                         0x9803D180
#define DP_HDCP_TX_SHA_OUT_3_reg_addr                                                "0x9803D180"
#define DP_HDCP_TX_SHA_OUT_3_reg                                                     0x9803D180
#define set_DP_HDCP_TX_SHA_OUT_3_reg(data)   (*((volatile unsigned int*) DP_HDCP_TX_SHA_OUT_3_reg)=data)
#define get_DP_HDCP_TX_SHA_OUT_3_reg   (*((volatile unsigned int*) DP_HDCP_TX_SHA_OUT_3_reg))
#define DP_HDCP_TX_SHA_OUT_3_inst_adr                                                "0x0060"
#define DP_HDCP_TX_SHA_OUT_3_inst                                                    0x0060
#define DP_HDCP_TX_SHA_OUT_3_sha_v_out3124_shift                                     (0)
#define DP_HDCP_TX_SHA_OUT_3_sha_v_out3124_mask                                      (0x000000FF)
#define DP_HDCP_TX_SHA_OUT_3_sha_v_out3124(data)                                     (0x000000FF&((data)<<0))
#define DP_HDCP_TX_SHA_OUT_3_sha_v_out3124_src(data)                                 ((0x000000FF&(data))>>0)
#define DP_HDCP_TX_SHA_OUT_3_get_sha_v_out3124(data)                                 ((0x000000FF&(data))>>0)


#define DP_HDCP_TX_SHA_OUT_2                                                         0x9803D184
#define DP_HDCP_TX_SHA_OUT_2_reg_addr                                                "0x9803D184"
#define DP_HDCP_TX_SHA_OUT_2_reg                                                     0x9803D184
#define set_DP_HDCP_TX_SHA_OUT_2_reg(data)   (*((volatile unsigned int*) DP_HDCP_TX_SHA_OUT_2_reg)=data)
#define get_DP_HDCP_TX_SHA_OUT_2_reg   (*((volatile unsigned int*) DP_HDCP_TX_SHA_OUT_2_reg))
#define DP_HDCP_TX_SHA_OUT_2_inst_adr                                                "0x0061"
#define DP_HDCP_TX_SHA_OUT_2_inst                                                    0x0061
#define DP_HDCP_TX_SHA_OUT_2_sha_v_out2316_shift                                     (0)
#define DP_HDCP_TX_SHA_OUT_2_sha_v_out2316_mask                                      (0x000000FF)
#define DP_HDCP_TX_SHA_OUT_2_sha_v_out2316(data)                                     (0x000000FF&((data)<<0))
#define DP_HDCP_TX_SHA_OUT_2_sha_v_out2316_src(data)                                 ((0x000000FF&(data))>>0)
#define DP_HDCP_TX_SHA_OUT_2_get_sha_v_out2316(data)                                 ((0x000000FF&(data))>>0)


#define DP_HDCP_TX_SHA_OUT_1                                                         0x9803D188
#define DP_HDCP_TX_SHA_OUT_1_reg_addr                                                "0x9803D188"
#define DP_HDCP_TX_SHA_OUT_1_reg                                                     0x9803D188
#define set_DP_HDCP_TX_SHA_OUT_1_reg(data)   (*((volatile unsigned int*) DP_HDCP_TX_SHA_OUT_1_reg)=data)
#define get_DP_HDCP_TX_SHA_OUT_1_reg   (*((volatile unsigned int*) DP_HDCP_TX_SHA_OUT_1_reg))
#define DP_HDCP_TX_SHA_OUT_1_inst_adr                                                "0x0062"
#define DP_HDCP_TX_SHA_OUT_1_inst                                                    0x0062
#define DP_HDCP_TX_SHA_OUT_1_sha_v_out158_shift                                      (0)
#define DP_HDCP_TX_SHA_OUT_1_sha_v_out158_mask                                       (0x000000FF)
#define DP_HDCP_TX_SHA_OUT_1_sha_v_out158(data)                                      (0x000000FF&((data)<<0))
#define DP_HDCP_TX_SHA_OUT_1_sha_v_out158_src(data)                                  ((0x000000FF&(data))>>0)
#define DP_HDCP_TX_SHA_OUT_1_get_sha_v_out158(data)                                  ((0x000000FF&(data))>>0)


#define DP_HDCP_TX_SHA_OUT_0                                                         0x9803D18C
#define DP_HDCP_TX_SHA_OUT_0_reg_addr                                                "0x9803D18C"
#define DP_HDCP_TX_SHA_OUT_0_reg                                                     0x9803D18C
#define set_DP_HDCP_TX_SHA_OUT_0_reg(data)   (*((volatile unsigned int*) DP_HDCP_TX_SHA_OUT_0_reg)=data)
#define get_DP_HDCP_TX_SHA_OUT_0_reg   (*((volatile unsigned int*) DP_HDCP_TX_SHA_OUT_0_reg))
#define DP_HDCP_TX_SHA_OUT_0_inst_adr                                                "0x0063"
#define DP_HDCP_TX_SHA_OUT_0_inst                                                    0x0063
#define DP_HDCP_TX_SHA_OUT_0_sha_v_out70_shift                                       (0)
#define DP_HDCP_TX_SHA_OUT_0_sha_v_out70_mask                                        (0x000000FF)
#define DP_HDCP_TX_SHA_OUT_0_sha_v_out70(data)                                       (0x000000FF&((data)<<0))
#define DP_HDCP_TX_SHA_OUT_0_sha_v_out70_src(data)                                   ((0x000000FF&(data))>>0)
#define DP_HDCP_TX_SHA_OUT_0_get_sha_v_out70(data)                                   ((0x000000FF&(data))>>0)


#define HDCP_ECF_BYTE0                                                               0x9803D190
#define HDCP_ECF_BYTE0_reg_addr                                                      "0x9803D190"
#define HDCP_ECF_BYTE0_reg                                                           0x9803D190
#define set_HDCP_ECF_BYTE0_reg(data)   (*((volatile unsigned int*) HDCP_ECF_BYTE0_reg)=data)
#define get_HDCP_ECF_BYTE0_reg   (*((volatile unsigned int*) HDCP_ECF_BYTE0_reg))
#define HDCP_ECF_BYTE0_inst_adr                                                      "0x0064"
#define HDCP_ECF_BYTE0_inst                                                          0x0064
#define HDCP_ECF_BYTE0_ecf_compute_auto_shift                                        (7)
#define HDCP_ECF_BYTE0_ecf_compute_auto_mask                                         (0x00000080)
#define HDCP_ECF_BYTE0_ecf_compute_auto(data)                                        (0x00000080&((data)<<7))
#define HDCP_ECF_BYTE0_ecf_compute_auto_src(data)                                    ((0x00000080&(data))>>7)
#define HDCP_ECF_BYTE0_get_ecf_compute_auto(data)                                    ((0x00000080&(data))>>7)
#define HDCP_ECF_BYTE0_ecf_byte_0_shift                                              (0)
#define HDCP_ECF_BYTE0_ecf_byte_0_mask                                               (0x0000007F)
#define HDCP_ECF_BYTE0_ecf_byte_0(data)                                              (0x0000007F&((data)<<0))
#define HDCP_ECF_BYTE0_ecf_byte_0_src(data)                                          ((0x0000007F&(data))>>0)
#define HDCP_ECF_BYTE0_get_ecf_byte_0(data)                                          ((0x0000007F&(data))>>0)


#define HDCP_ECF_BYTE1                                                               0x9803D194
#define HDCP_ECF_BYTE1_reg_addr                                                      "0x9803D194"
#define HDCP_ECF_BYTE1_reg                                                           0x9803D194
#define set_HDCP_ECF_BYTE1_reg(data)   (*((volatile unsigned int*) HDCP_ECF_BYTE1_reg)=data)
#define get_HDCP_ECF_BYTE1_reg   (*((volatile unsigned int*) HDCP_ECF_BYTE1_reg))
#define HDCP_ECF_BYTE1_inst_adr                                                      "0x0065"
#define HDCP_ECF_BYTE1_inst                                                          0x0065
#define HDCP_ECF_BYTE1_ecf_byte_1_shift                                              (0)
#define HDCP_ECF_BYTE1_ecf_byte_1_mask                                               (0x000000FF)
#define HDCP_ECF_BYTE1_ecf_byte_1(data)                                              (0x000000FF&((data)<<0))
#define HDCP_ECF_BYTE1_ecf_byte_1_src(data)                                          ((0x000000FF&(data))>>0)
#define HDCP_ECF_BYTE1_get_ecf_byte_1(data)                                          ((0x000000FF&(data))>>0)


#define HDCP_ECF_BYTE2                                                               0x9803D198
#define HDCP_ECF_BYTE2_reg_addr                                                      "0x9803D198"
#define HDCP_ECF_BYTE2_reg                                                           0x9803D198
#define set_HDCP_ECF_BYTE2_reg(data)   (*((volatile unsigned int*) HDCP_ECF_BYTE2_reg)=data)
#define get_HDCP_ECF_BYTE2_reg   (*((volatile unsigned int*) HDCP_ECF_BYTE2_reg))
#define HDCP_ECF_BYTE2_inst_adr                                                      "0x0066"
#define HDCP_ECF_BYTE2_inst                                                          0x0066
#define HDCP_ECF_BYTE2_ecf_byte_2_shift                                              (0)
#define HDCP_ECF_BYTE2_ecf_byte_2_mask                                               (0x000000FF)
#define HDCP_ECF_BYTE2_ecf_byte_2(data)                                              (0x000000FF&((data)<<0))
#define HDCP_ECF_BYTE2_ecf_byte_2_src(data)                                          ((0x000000FF&(data))>>0)
#define HDCP_ECF_BYTE2_get_ecf_byte_2(data)                                          ((0x000000FF&(data))>>0)


#define HDCP_ECF_BYTE3                                                               0x9803D19C
#define HDCP_ECF_BYTE3_reg_addr                                                      "0x9803D19C"
#define HDCP_ECF_BYTE3_reg                                                           0x9803D19C
#define set_HDCP_ECF_BYTE3_reg(data)   (*((volatile unsigned int*) HDCP_ECF_BYTE3_reg)=data)
#define get_HDCP_ECF_BYTE3_reg   (*((volatile unsigned int*) HDCP_ECF_BYTE3_reg))
#define HDCP_ECF_BYTE3_inst_adr                                                      "0x0067"
#define HDCP_ECF_BYTE3_inst                                                          0x0067
#define HDCP_ECF_BYTE3_ecf_byte_3_shift                                              (0)
#define HDCP_ECF_BYTE3_ecf_byte_3_mask                                               (0x000000FF)
#define HDCP_ECF_BYTE3_ecf_byte_3(data)                                              (0x000000FF&((data)<<0))
#define HDCP_ECF_BYTE3_ecf_byte_3_src(data)                                          ((0x000000FF&(data))>>0)
#define HDCP_ECF_BYTE3_get_ecf_byte_3(data)                                          ((0x000000FF&(data))>>0)


#define HDCP_ECF_BYTE4                                                               0x9803D1A0
#define HDCP_ECF_BYTE4_reg_addr                                                      "0x9803D1A0"
#define HDCP_ECF_BYTE4_reg                                                           0x9803D1A0
#define set_HDCP_ECF_BYTE4_reg(data)   (*((volatile unsigned int*) HDCP_ECF_BYTE4_reg)=data)
#define get_HDCP_ECF_BYTE4_reg   (*((volatile unsigned int*) HDCP_ECF_BYTE4_reg))
#define HDCP_ECF_BYTE4_inst_adr                                                      "0x0068"
#define HDCP_ECF_BYTE4_inst                                                          0x0068
#define HDCP_ECF_BYTE4_ecf_byte_4_shift                                              (0)
#define HDCP_ECF_BYTE4_ecf_byte_4_mask                                               (0x000000FF)
#define HDCP_ECF_BYTE4_ecf_byte_4(data)                                              (0x000000FF&((data)<<0))
#define HDCP_ECF_BYTE4_ecf_byte_4_src(data)                                          ((0x000000FF&(data))>>0)
#define HDCP_ECF_BYTE4_get_ecf_byte_4(data)                                          ((0x000000FF&(data))>>0)


#define HDCP_ECF_BYTE5                                                               0x9803D1A4
#define HDCP_ECF_BYTE5_reg_addr                                                      "0x9803D1A4"
#define HDCP_ECF_BYTE5_reg                                                           0x9803D1A4
#define set_HDCP_ECF_BYTE5_reg(data)   (*((volatile unsigned int*) HDCP_ECF_BYTE5_reg)=data)
#define get_HDCP_ECF_BYTE5_reg   (*((volatile unsigned int*) HDCP_ECF_BYTE5_reg))
#define HDCP_ECF_BYTE5_inst_adr                                                      "0x0069"
#define HDCP_ECF_BYTE5_inst                                                          0x0069
#define HDCP_ECF_BYTE5_ecf_byte_5_shift                                              (0)
#define HDCP_ECF_BYTE5_ecf_byte_5_mask                                               (0x000000FF)
#define HDCP_ECF_BYTE5_ecf_byte_5(data)                                              (0x000000FF&((data)<<0))
#define HDCP_ECF_BYTE5_ecf_byte_5_src(data)                                          ((0x000000FF&(data))>>0)
#define HDCP_ECF_BYTE5_get_ecf_byte_5(data)                                          ((0x000000FF&(data))>>0)


#define HDCP_ECF_BYTE6                                                               0x9803D1A8
#define HDCP_ECF_BYTE6_reg_addr                                                      "0x9803D1A8"
#define HDCP_ECF_BYTE6_reg                                                           0x9803D1A8
#define set_HDCP_ECF_BYTE6_reg(data)   (*((volatile unsigned int*) HDCP_ECF_BYTE6_reg)=data)
#define get_HDCP_ECF_BYTE6_reg   (*((volatile unsigned int*) HDCP_ECF_BYTE6_reg))
#define HDCP_ECF_BYTE6_inst_adr                                                      "0x006A"
#define HDCP_ECF_BYTE6_inst                                                          0x006A
#define HDCP_ECF_BYTE6_ecf_byte_6_shift                                              (0)
#define HDCP_ECF_BYTE6_ecf_byte_6_mask                                               (0x000000FF)
#define HDCP_ECF_BYTE6_ecf_byte_6(data)                                              (0x000000FF&((data)<<0))
#define HDCP_ECF_BYTE6_ecf_byte_6_src(data)                                          ((0x000000FF&(data))>>0)
#define HDCP_ECF_BYTE6_get_ecf_byte_6(data)                                          ((0x000000FF&(data))>>0)


#define HDCP_ECF_BYTE7                                                               0x9803D1AC
#define HDCP_ECF_BYTE7_reg_addr                                                      "0x9803D1AC"
#define HDCP_ECF_BYTE7_reg                                                           0x9803D1AC
#define set_HDCP_ECF_BYTE7_reg(data)   (*((volatile unsigned int*) HDCP_ECF_BYTE7_reg)=data)
#define get_HDCP_ECF_BYTE7_reg   (*((volatile unsigned int*) HDCP_ECF_BYTE7_reg))
#define HDCP_ECF_BYTE7_inst_adr                                                      "0x006B"
#define HDCP_ECF_BYTE7_inst                                                          0x006B
#define HDCP_ECF_BYTE7_ecf_byte_7_shift                                              (0)
#define HDCP_ECF_BYTE7_ecf_byte_7_mask                                               (0x000000FF)
#define HDCP_ECF_BYTE7_ecf_byte_7(data)                                              (0x000000FF&((data)<<0))
#define HDCP_ECF_BYTE7_ecf_byte_7_src(data)                                          ((0x000000FF&(data))>>0)
#define HDCP_ECF_BYTE7_get_ecf_byte_7(data)                                          ((0x000000FF&(data))>>0)


#define DP_STREAM_1_PBN                                                              0x9803D1B0
#define DP_STREAM_1_PBN_reg_addr                                                     "0x9803D1B0"
#define DP_STREAM_1_PBN_reg                                                          0x9803D1B0
#define set_DP_STREAM_1_PBN_reg(data)   (*((volatile unsigned int*) DP_STREAM_1_PBN_reg)=data)
#define get_DP_STREAM_1_PBN_reg   (*((volatile unsigned int*) DP_STREAM_1_PBN_reg))
#define DP_STREAM_1_PBN_inst_adr                                                     "0x006C"
#define DP_STREAM_1_PBN_inst                                                         0x006C
#define DP_STREAM_1_PBN_Reserved_shift                                               (7)
#define DP_STREAM_1_PBN_Reserved_mask                                                (0x00000080)
#define DP_STREAM_1_PBN_Reserved(data)                                               (0x00000080&((data)<<7))
#define DP_STREAM_1_PBN_Reserved_src(data)                                           ((0x00000080&(data))>>7)
#define DP_STREAM_1_PBN_get_Reserved(data)                                           ((0x00000080&(data))>>7)
#define DP_STREAM_1_PBN_hdcp_enc_stream_1_shift                                      (6)
#define DP_STREAM_1_PBN_hdcp_enc_stream_1_mask                                       (0x00000040)
#define DP_STREAM_1_PBN_hdcp_enc_stream_1(data)                                      (0x00000040&((data)<<6))
#define DP_STREAM_1_PBN_hdcp_enc_stream_1_src(data)                                  ((0x00000040&(data))>>6)
#define DP_STREAM_1_PBN_get_hdcp_enc_stream_1(data)                                  ((0x00000040&(data))>>6)
#define DP_STREAM_1_PBN_alloc_pbn_1_shift                                            (0)
#define DP_STREAM_1_PBN_alloc_pbn_1_mask                                             (0x0000003F)
#define DP_STREAM_1_PBN_alloc_pbn_1(data)                                            (0x0000003F&((data)<<0))
#define DP_STREAM_1_PBN_alloc_pbn_1_src(data)                                        ((0x0000003F&(data))>>0)
#define DP_STREAM_1_PBN_get_alloc_pbn_1(data)                                        ((0x0000003F&(data))>>0)


#define DP_STREAM_2_PBN                                                              0x9803D1B4
#define DP_STREAM_2_PBN_reg_addr                                                     "0x9803D1B4"
#define DP_STREAM_2_PBN_reg                                                          0x9803D1B4
#define set_DP_STREAM_2_PBN_reg(data)   (*((volatile unsigned int*) DP_STREAM_2_PBN_reg)=data)
#define get_DP_STREAM_2_PBN_reg   (*((volatile unsigned int*) DP_STREAM_2_PBN_reg))
#define DP_STREAM_2_PBN_inst_adr                                                     "0x006D"
#define DP_STREAM_2_PBN_inst                                                         0x006D
#define DP_STREAM_2_PBN_Reserved_shift                                               (7)
#define DP_STREAM_2_PBN_Reserved_mask                                                (0x00000080)
#define DP_STREAM_2_PBN_Reserved(data)                                               (0x00000080&((data)<<7))
#define DP_STREAM_2_PBN_Reserved_src(data)                                           ((0x00000080&(data))>>7)
#define DP_STREAM_2_PBN_get_Reserved(data)                                           ((0x00000080&(data))>>7)
#define DP_STREAM_2_PBN_hdcp_enc_stream_2_shift                                      (6)
#define DP_STREAM_2_PBN_hdcp_enc_stream_2_mask                                       (0x00000040)
#define DP_STREAM_2_PBN_hdcp_enc_stream_2(data)                                      (0x00000040&((data)<<6))
#define DP_STREAM_2_PBN_hdcp_enc_stream_2_src(data)                                  ((0x00000040&(data))>>6)
#define DP_STREAM_2_PBN_get_hdcp_enc_stream_2(data)                                  ((0x00000040&(data))>>6)
#define DP_STREAM_2_PBN_alloc_pbn_2_shift                                            (0)
#define DP_STREAM_2_PBN_alloc_pbn_2_mask                                             (0x0000003F)
#define DP_STREAM_2_PBN_alloc_pbn_2(data)                                            (0x0000003F&((data)<<0))
#define DP_STREAM_2_PBN_alloc_pbn_2_src(data)                                        ((0x0000003F&(data))>>0)
#define DP_STREAM_2_PBN_get_alloc_pbn_2(data)                                        ((0x0000003F&(data))>>0)


#define DP_STREAM_3_PBN                                                              0x9803D1B8
#define DP_STREAM_3_PBN_reg_addr                                                     "0x9803D1B8"
#define DP_STREAM_3_PBN_reg                                                          0x9803D1B8
#define set_DP_STREAM_3_PBN_reg(data)   (*((volatile unsigned int*) DP_STREAM_3_PBN_reg)=data)
#define get_DP_STREAM_3_PBN_reg   (*((volatile unsigned int*) DP_STREAM_3_PBN_reg))
#define DP_STREAM_3_PBN_inst_adr                                                     "0x006E"
#define DP_STREAM_3_PBN_inst                                                         0x006E
#define DP_STREAM_3_PBN_Reserved_shift                                               (7)
#define DP_STREAM_3_PBN_Reserved_mask                                                (0x00000080)
#define DP_STREAM_3_PBN_Reserved(data)                                               (0x00000080&((data)<<7))
#define DP_STREAM_3_PBN_Reserved_src(data)                                           ((0x00000080&(data))>>7)
#define DP_STREAM_3_PBN_get_Reserved(data)                                           ((0x00000080&(data))>>7)
#define DP_STREAM_3_PBN_hdcp_enc_stream_3_shift                                      (6)
#define DP_STREAM_3_PBN_hdcp_enc_stream_3_mask                                       (0x00000040)
#define DP_STREAM_3_PBN_hdcp_enc_stream_3(data)                                      (0x00000040&((data)<<6))
#define DP_STREAM_3_PBN_hdcp_enc_stream_3_src(data)                                  ((0x00000040&(data))>>6)
#define DP_STREAM_3_PBN_get_hdcp_enc_stream_3(data)                                  ((0x00000040&(data))>>6)
#define DP_STREAM_3_PBN_alloc_pbn_3_shift                                            (0)
#define DP_STREAM_3_PBN_alloc_pbn_3_mask                                             (0x0000003F)
#define DP_STREAM_3_PBN_alloc_pbn_3(data)                                            (0x0000003F&((data)<<0))
#define DP_STREAM_3_PBN_alloc_pbn_3_src(data)                                        ((0x0000003F&(data))>>0)
#define DP_STREAM_3_PBN_get_alloc_pbn_3(data)                                        ((0x0000003F&(data))>>0)


#define DP_STREAM_4_PBN                                                              0x9803D1BC
#define DP_STREAM_4_PBN_reg_addr                                                     "0x9803D1BC"
#define DP_STREAM_4_PBN_reg                                                          0x9803D1BC
#define set_DP_STREAM_4_PBN_reg(data)   (*((volatile unsigned int*) DP_STREAM_4_PBN_reg)=data)
#define get_DP_STREAM_4_PBN_reg   (*((volatile unsigned int*) DP_STREAM_4_PBN_reg))
#define DP_STREAM_4_PBN_inst_adr                                                     "0x006F"
#define DP_STREAM_4_PBN_inst                                                         0x006F
#define DP_STREAM_4_PBN_Reserved_shift                                               (7)
#define DP_STREAM_4_PBN_Reserved_mask                                                (0x00000080)
#define DP_STREAM_4_PBN_Reserved(data)                                               (0x00000080&((data)<<7))
#define DP_STREAM_4_PBN_Reserved_src(data)                                           ((0x00000080&(data))>>7)
#define DP_STREAM_4_PBN_get_Reserved(data)                                           ((0x00000080&(data))>>7)
#define DP_STREAM_4_PBN_hdcp_enc_stream_4_shift                                      (6)
#define DP_STREAM_4_PBN_hdcp_enc_stream_4_mask                                       (0x00000040)
#define DP_STREAM_4_PBN_hdcp_enc_stream_4(data)                                      (0x00000040&((data)<<6))
#define DP_STREAM_4_PBN_hdcp_enc_stream_4_src(data)                                  ((0x00000040&(data))>>6)
#define DP_STREAM_4_PBN_get_hdcp_enc_stream_4(data)                                  ((0x00000040&(data))>>6)
#define DP_STREAM_4_PBN_alloc_pbn_4_shift                                            (0)
#define DP_STREAM_4_PBN_alloc_pbn_4_mask                                             (0x0000003F)
#define DP_STREAM_4_PBN_alloc_pbn_4(data)                                            (0x0000003F&((data)<<0))
#define DP_STREAM_4_PBN_alloc_pbn_4_src(data)                                        ((0x0000003F&(data))>>0)
#define DP_STREAM_4_PBN_get_alloc_pbn_4(data)                                        ((0x0000003F&(data))>>0)


#define HDCP_AES_CIPHER_KEY_15                                                       0x9803D200
#define HDCP_AES_CIPHER_KEY_15_reg_addr                                              "0x9803D200"
#define HDCP_AES_CIPHER_KEY_15_reg                                                   0x9803D200
#define set_HDCP_AES_CIPHER_KEY_15_reg(data)   (*((volatile unsigned int*) HDCP_AES_CIPHER_KEY_15_reg)=data)
#define get_HDCP_AES_CIPHER_KEY_15_reg   (*((volatile unsigned int*) HDCP_AES_CIPHER_KEY_15_reg))
#define HDCP_AES_CIPHER_KEY_15_inst_adr                                              "0x0080"
#define HDCP_AES_CIPHER_KEY_15_inst                                                  0x0080
#define HDCP_AES_CIPHER_KEY_15_aes_cipher_key127120_shift                            (0)
#define HDCP_AES_CIPHER_KEY_15_aes_cipher_key127120_mask                             (0x000000FF)
#define HDCP_AES_CIPHER_KEY_15_aes_cipher_key127120(data)                            (0x000000FF&((data)<<0))
#define HDCP_AES_CIPHER_KEY_15_aes_cipher_key127120_src(data)                        ((0x000000FF&(data))>>0)
#define HDCP_AES_CIPHER_KEY_15_get_aes_cipher_key127120(data)                        ((0x000000FF&(data))>>0)


#define HDCP_AES_CIPHER_KEY_14                                                       0x9803D204
#define HDCP_AES_CIPHER_KEY_14_reg_addr                                              "0x9803D204"
#define HDCP_AES_CIPHER_KEY_14_reg                                                   0x9803D204
#define set_HDCP_AES_CIPHER_KEY_14_reg(data)   (*((volatile unsigned int*) HDCP_AES_CIPHER_KEY_14_reg)=data)
#define get_HDCP_AES_CIPHER_KEY_14_reg   (*((volatile unsigned int*) HDCP_AES_CIPHER_KEY_14_reg))
#define HDCP_AES_CIPHER_KEY_14_inst_adr                                              "0x0081"
#define HDCP_AES_CIPHER_KEY_14_inst                                                  0x0081
#define HDCP_AES_CIPHER_KEY_14_aes_cipher_key119112_shift                            (0)
#define HDCP_AES_CIPHER_KEY_14_aes_cipher_key119112_mask                             (0x000000FF)
#define HDCP_AES_CIPHER_KEY_14_aes_cipher_key119112(data)                            (0x000000FF&((data)<<0))
#define HDCP_AES_CIPHER_KEY_14_aes_cipher_key119112_src(data)                        ((0x000000FF&(data))>>0)
#define HDCP_AES_CIPHER_KEY_14_get_aes_cipher_key119112(data)                        ((0x000000FF&(data))>>0)


#define HDCP_AES_CIPHER_KEY_13                                                       0x9803D208
#define HDCP_AES_CIPHER_KEY_13_reg_addr                                              "0x9803D208"
#define HDCP_AES_CIPHER_KEY_13_reg                                                   0x9803D208
#define set_HDCP_AES_CIPHER_KEY_13_reg(data)   (*((volatile unsigned int*) HDCP_AES_CIPHER_KEY_13_reg)=data)
#define get_HDCP_AES_CIPHER_KEY_13_reg   (*((volatile unsigned int*) HDCP_AES_CIPHER_KEY_13_reg))
#define HDCP_AES_CIPHER_KEY_13_inst_adr                                              "0x0082"
#define HDCP_AES_CIPHER_KEY_13_inst                                                  0x0082
#define HDCP_AES_CIPHER_KEY_13_aes_cipher_key111104_shift                            (0)
#define HDCP_AES_CIPHER_KEY_13_aes_cipher_key111104_mask                             (0x000000FF)
#define HDCP_AES_CIPHER_KEY_13_aes_cipher_key111104(data)                            (0x000000FF&((data)<<0))
#define HDCP_AES_CIPHER_KEY_13_aes_cipher_key111104_src(data)                        ((0x000000FF&(data))>>0)
#define HDCP_AES_CIPHER_KEY_13_get_aes_cipher_key111104(data)                        ((0x000000FF&(data))>>0)


#define HDCP_AES_CIPHER_KEY_12                                                       0x9803D20C
#define HDCP_AES_CIPHER_KEY_12_reg_addr                                              "0x9803D20C"
#define HDCP_AES_CIPHER_KEY_12_reg                                                   0x9803D20C
#define set_HDCP_AES_CIPHER_KEY_12_reg(data)   (*((volatile unsigned int*) HDCP_AES_CIPHER_KEY_12_reg)=data)
#define get_HDCP_AES_CIPHER_KEY_12_reg   (*((volatile unsigned int*) HDCP_AES_CIPHER_KEY_12_reg))
#define HDCP_AES_CIPHER_KEY_12_inst_adr                                              "0x0083"
#define HDCP_AES_CIPHER_KEY_12_inst                                                  0x0083
#define HDCP_AES_CIPHER_KEY_12_aes_cipher_key10396_shift                             (0)
#define HDCP_AES_CIPHER_KEY_12_aes_cipher_key10396_mask                              (0x000000FF)
#define HDCP_AES_CIPHER_KEY_12_aes_cipher_key10396(data)                             (0x000000FF&((data)<<0))
#define HDCP_AES_CIPHER_KEY_12_aes_cipher_key10396_src(data)                         ((0x000000FF&(data))>>0)
#define HDCP_AES_CIPHER_KEY_12_get_aes_cipher_key10396(data)                         ((0x000000FF&(data))>>0)


#define HDCP_AES_CIPHER_KEY_11                                                       0x9803D210
#define HDCP_AES_CIPHER_KEY_11_reg_addr                                              "0x9803D210"
#define HDCP_AES_CIPHER_KEY_11_reg                                                   0x9803D210
#define set_HDCP_AES_CIPHER_KEY_11_reg(data)   (*((volatile unsigned int*) HDCP_AES_CIPHER_KEY_11_reg)=data)
#define get_HDCP_AES_CIPHER_KEY_11_reg   (*((volatile unsigned int*) HDCP_AES_CIPHER_KEY_11_reg))
#define HDCP_AES_CIPHER_KEY_11_inst_adr                                              "0x0084"
#define HDCP_AES_CIPHER_KEY_11_inst                                                  0x0084
#define HDCP_AES_CIPHER_KEY_11_aes_cipher_key9588_shift                              (0)
#define HDCP_AES_CIPHER_KEY_11_aes_cipher_key9588_mask                               (0x000000FF)
#define HDCP_AES_CIPHER_KEY_11_aes_cipher_key9588(data)                              (0x000000FF&((data)<<0))
#define HDCP_AES_CIPHER_KEY_11_aes_cipher_key9588_src(data)                          ((0x000000FF&(data))>>0)
#define HDCP_AES_CIPHER_KEY_11_get_aes_cipher_key9588(data)                          ((0x000000FF&(data))>>0)


#define HDCP_AES_CIPHER_KEY_10                                                       0x9803D214
#define HDCP_AES_CIPHER_KEY_10_reg_addr                                              "0x9803D214"
#define HDCP_AES_CIPHER_KEY_10_reg                                                   0x9803D214
#define set_HDCP_AES_CIPHER_KEY_10_reg(data)   (*((volatile unsigned int*) HDCP_AES_CIPHER_KEY_10_reg)=data)
#define get_HDCP_AES_CIPHER_KEY_10_reg   (*((volatile unsigned int*) HDCP_AES_CIPHER_KEY_10_reg))
#define HDCP_AES_CIPHER_KEY_10_inst_adr                                              "0x0085"
#define HDCP_AES_CIPHER_KEY_10_inst                                                  0x0085
#define HDCP_AES_CIPHER_KEY_10_aes_cipher_key8780_shift                              (0)
#define HDCP_AES_CIPHER_KEY_10_aes_cipher_key8780_mask                               (0x000000FF)
#define HDCP_AES_CIPHER_KEY_10_aes_cipher_key8780(data)                              (0x000000FF&((data)<<0))
#define HDCP_AES_CIPHER_KEY_10_aes_cipher_key8780_src(data)                          ((0x000000FF&(data))>>0)
#define HDCP_AES_CIPHER_KEY_10_get_aes_cipher_key8780(data)                          ((0x000000FF&(data))>>0)


#define HDCP_AES_CIPHER_KEY_9                                                        0x9803D218
#define HDCP_AES_CIPHER_KEY_9_reg_addr                                               "0x9803D218"
#define HDCP_AES_CIPHER_KEY_9_reg                                                    0x9803D218
#define set_HDCP_AES_CIPHER_KEY_9_reg(data)   (*((volatile unsigned int*) HDCP_AES_CIPHER_KEY_9_reg)=data)
#define get_HDCP_AES_CIPHER_KEY_9_reg   (*((volatile unsigned int*) HDCP_AES_CIPHER_KEY_9_reg))
#define HDCP_AES_CIPHER_KEY_9_inst_adr                                               "0x0086"
#define HDCP_AES_CIPHER_KEY_9_inst                                                   0x0086
#define HDCP_AES_CIPHER_KEY_9_aes_cipher_key7972_shift                               (0)
#define HDCP_AES_CIPHER_KEY_9_aes_cipher_key7972_mask                                (0x000000FF)
#define HDCP_AES_CIPHER_KEY_9_aes_cipher_key7972(data)                               (0x000000FF&((data)<<0))
#define HDCP_AES_CIPHER_KEY_9_aes_cipher_key7972_src(data)                           ((0x000000FF&(data))>>0)
#define HDCP_AES_CIPHER_KEY_9_get_aes_cipher_key7972(data)                           ((0x000000FF&(data))>>0)


#define HDCP_AES_CIPHER_KEY_8                                                        0x9803D21C
#define HDCP_AES_CIPHER_KEY_8_reg_addr                                               "0x9803D21C"
#define HDCP_AES_CIPHER_KEY_8_reg                                                    0x9803D21C
#define set_HDCP_AES_CIPHER_KEY_8_reg(data)   (*((volatile unsigned int*) HDCP_AES_CIPHER_KEY_8_reg)=data)
#define get_HDCP_AES_CIPHER_KEY_8_reg   (*((volatile unsigned int*) HDCP_AES_CIPHER_KEY_8_reg))
#define HDCP_AES_CIPHER_KEY_8_inst_adr                                               "0x0087"
#define HDCP_AES_CIPHER_KEY_8_inst                                                   0x0087
#define HDCP_AES_CIPHER_KEY_8_aes_cipher_key7164_shift                               (0)
#define HDCP_AES_CIPHER_KEY_8_aes_cipher_key7164_mask                                (0x000000FF)
#define HDCP_AES_CIPHER_KEY_8_aes_cipher_key7164(data)                               (0x000000FF&((data)<<0))
#define HDCP_AES_CIPHER_KEY_8_aes_cipher_key7164_src(data)                           ((0x000000FF&(data))>>0)
#define HDCP_AES_CIPHER_KEY_8_get_aes_cipher_key7164(data)                           ((0x000000FF&(data))>>0)


#define HDCP_AES_CIPHER_KEY_7                                                        0x9803D220
#define HDCP_AES_CIPHER_KEY_7_reg_addr                                               "0x9803D220"
#define HDCP_AES_CIPHER_KEY_7_reg                                                    0x9803D220
#define set_HDCP_AES_CIPHER_KEY_7_reg(data)   (*((volatile unsigned int*) HDCP_AES_CIPHER_KEY_7_reg)=data)
#define get_HDCP_AES_CIPHER_KEY_7_reg   (*((volatile unsigned int*) HDCP_AES_CIPHER_KEY_7_reg))
#define HDCP_AES_CIPHER_KEY_7_inst_adr                                               "0x0088"
#define HDCP_AES_CIPHER_KEY_7_inst                                                   0x0088
#define HDCP_AES_CIPHER_KEY_7_aes_cipher_key6356_shift                               (0)
#define HDCP_AES_CIPHER_KEY_7_aes_cipher_key6356_mask                                (0x000000FF)
#define HDCP_AES_CIPHER_KEY_7_aes_cipher_key6356(data)                               (0x000000FF&((data)<<0))
#define HDCP_AES_CIPHER_KEY_7_aes_cipher_key6356_src(data)                           ((0x000000FF&(data))>>0)
#define HDCP_AES_CIPHER_KEY_7_get_aes_cipher_key6356(data)                           ((0x000000FF&(data))>>0)


#define HDCP_AES_CIPHER_KEY_6                                                        0x9803D224
#define HDCP_AES_CIPHER_KEY_6_reg_addr                                               "0x9803D224"
#define HDCP_AES_CIPHER_KEY_6_reg                                                    0x9803D224
#define set_HDCP_AES_CIPHER_KEY_6_reg(data)   (*((volatile unsigned int*) HDCP_AES_CIPHER_KEY_6_reg)=data)
#define get_HDCP_AES_CIPHER_KEY_6_reg   (*((volatile unsigned int*) HDCP_AES_CIPHER_KEY_6_reg))
#define HDCP_AES_CIPHER_KEY_6_inst_adr                                               "0x0089"
#define HDCP_AES_CIPHER_KEY_6_inst                                                   0x0089
#define HDCP_AES_CIPHER_KEY_6_aes_cipher_key5548_shift                               (0)
#define HDCP_AES_CIPHER_KEY_6_aes_cipher_key5548_mask                                (0x000000FF)
#define HDCP_AES_CIPHER_KEY_6_aes_cipher_key5548(data)                               (0x000000FF&((data)<<0))
#define HDCP_AES_CIPHER_KEY_6_aes_cipher_key5548_src(data)                           ((0x000000FF&(data))>>0)
#define HDCP_AES_CIPHER_KEY_6_get_aes_cipher_key5548(data)                           ((0x000000FF&(data))>>0)


#define HDCP_AES_CIPHER_KEY_5                                                        0x9803D228
#define HDCP_AES_CIPHER_KEY_5_reg_addr                                               "0x9803D228"
#define HDCP_AES_CIPHER_KEY_5_reg                                                    0x9803D228
#define set_HDCP_AES_CIPHER_KEY_5_reg(data)   (*((volatile unsigned int*) HDCP_AES_CIPHER_KEY_5_reg)=data)
#define get_HDCP_AES_CIPHER_KEY_5_reg   (*((volatile unsigned int*) HDCP_AES_CIPHER_KEY_5_reg))
#define HDCP_AES_CIPHER_KEY_5_inst_adr                                               "0x008A"
#define HDCP_AES_CIPHER_KEY_5_inst                                                   0x008A
#define HDCP_AES_CIPHER_KEY_5_aes_cipher_key4740_shift                               (0)
#define HDCP_AES_CIPHER_KEY_5_aes_cipher_key4740_mask                                (0x000000FF)
#define HDCP_AES_CIPHER_KEY_5_aes_cipher_key4740(data)                               (0x000000FF&((data)<<0))
#define HDCP_AES_CIPHER_KEY_5_aes_cipher_key4740_src(data)                           ((0x000000FF&(data))>>0)
#define HDCP_AES_CIPHER_KEY_5_get_aes_cipher_key4740(data)                           ((0x000000FF&(data))>>0)


#define HDCP_AES_CIPHER_KEY_4                                                        0x9803D22C
#define HDCP_AES_CIPHER_KEY_4_reg_addr                                               "0x9803D22C"
#define HDCP_AES_CIPHER_KEY_4_reg                                                    0x9803D22C
#define set_HDCP_AES_CIPHER_KEY_4_reg(data)   (*((volatile unsigned int*) HDCP_AES_CIPHER_KEY_4_reg)=data)
#define get_HDCP_AES_CIPHER_KEY_4_reg   (*((volatile unsigned int*) HDCP_AES_CIPHER_KEY_4_reg))
#define HDCP_AES_CIPHER_KEY_4_inst_adr                                               "0x008B"
#define HDCP_AES_CIPHER_KEY_4_inst                                                   0x008B
#define HDCP_AES_CIPHER_KEY_4_aes_cipher_key3932_shift                               (0)
#define HDCP_AES_CIPHER_KEY_4_aes_cipher_key3932_mask                                (0x000000FF)
#define HDCP_AES_CIPHER_KEY_4_aes_cipher_key3932(data)                               (0x000000FF&((data)<<0))
#define HDCP_AES_CIPHER_KEY_4_aes_cipher_key3932_src(data)                           ((0x000000FF&(data))>>0)
#define HDCP_AES_CIPHER_KEY_4_get_aes_cipher_key3932(data)                           ((0x000000FF&(data))>>0)


#define HDCP_AES_CIPHER_KEY_3                                                        0x9803D230
#define HDCP_AES_CIPHER_KEY_3_reg_addr                                               "0x9803D230"
#define HDCP_AES_CIPHER_KEY_3_reg                                                    0x9803D230
#define set_HDCP_AES_CIPHER_KEY_3_reg(data)   (*((volatile unsigned int*) HDCP_AES_CIPHER_KEY_3_reg)=data)
#define get_HDCP_AES_CIPHER_KEY_3_reg   (*((volatile unsigned int*) HDCP_AES_CIPHER_KEY_3_reg))
#define HDCP_AES_CIPHER_KEY_3_inst_adr                                               "0x008C"
#define HDCP_AES_CIPHER_KEY_3_inst                                                   0x008C
#define HDCP_AES_CIPHER_KEY_3_aes_cipher_key3124_shift                               (0)
#define HDCP_AES_CIPHER_KEY_3_aes_cipher_key3124_mask                                (0x000000FF)
#define HDCP_AES_CIPHER_KEY_3_aes_cipher_key3124(data)                               (0x000000FF&((data)<<0))
#define HDCP_AES_CIPHER_KEY_3_aes_cipher_key3124_src(data)                           ((0x000000FF&(data))>>0)
#define HDCP_AES_CIPHER_KEY_3_get_aes_cipher_key3124(data)                           ((0x000000FF&(data))>>0)


#define HDCP_AES_CIPHER_KEY_2                                                        0x9803D234
#define HDCP_AES_CIPHER_KEY_2_reg_addr                                               "0x9803D234"
#define HDCP_AES_CIPHER_KEY_2_reg                                                    0x9803D234
#define set_HDCP_AES_CIPHER_KEY_2_reg(data)   (*((volatile unsigned int*) HDCP_AES_CIPHER_KEY_2_reg)=data)
#define get_HDCP_AES_CIPHER_KEY_2_reg   (*((volatile unsigned int*) HDCP_AES_CIPHER_KEY_2_reg))
#define HDCP_AES_CIPHER_KEY_2_inst_adr                                               "0x008D"
#define HDCP_AES_CIPHER_KEY_2_inst                                                   0x008D
#define HDCP_AES_CIPHER_KEY_2_aes_cipher_key2316_shift                               (0)
#define HDCP_AES_CIPHER_KEY_2_aes_cipher_key2316_mask                                (0x000000FF)
#define HDCP_AES_CIPHER_KEY_2_aes_cipher_key2316(data)                               (0x000000FF&((data)<<0))
#define HDCP_AES_CIPHER_KEY_2_aes_cipher_key2316_src(data)                           ((0x000000FF&(data))>>0)
#define HDCP_AES_CIPHER_KEY_2_get_aes_cipher_key2316(data)                           ((0x000000FF&(data))>>0)


#define HDCP_AES_CIPHER_KEY_1                                                        0x9803D238
#define HDCP_AES_CIPHER_KEY_1_reg_addr                                               "0x9803D238"
#define HDCP_AES_CIPHER_KEY_1_reg                                                    0x9803D238
#define set_HDCP_AES_CIPHER_KEY_1_reg(data)   (*((volatile unsigned int*) HDCP_AES_CIPHER_KEY_1_reg)=data)
#define get_HDCP_AES_CIPHER_KEY_1_reg   (*((volatile unsigned int*) HDCP_AES_CIPHER_KEY_1_reg))
#define HDCP_AES_CIPHER_KEY_1_inst_adr                                               "0x008E"
#define HDCP_AES_CIPHER_KEY_1_inst                                                   0x008E
#define HDCP_AES_CIPHER_KEY_1_aes_cipher_key158_shift                                (0)
#define HDCP_AES_CIPHER_KEY_1_aes_cipher_key158_mask                                 (0x000000FF)
#define HDCP_AES_CIPHER_KEY_1_aes_cipher_key158(data)                                (0x000000FF&((data)<<0))
#define HDCP_AES_CIPHER_KEY_1_aes_cipher_key158_src(data)                            ((0x000000FF&(data))>>0)
#define HDCP_AES_CIPHER_KEY_1_get_aes_cipher_key158(data)                            ((0x000000FF&(data))>>0)


#define HDCP_AES_CIPHER_KEY_0                                                        0x9803D23C
#define HDCP_AES_CIPHER_KEY_0_reg_addr                                               "0x9803D23C"
#define HDCP_AES_CIPHER_KEY_0_reg                                                    0x9803D23C
#define set_HDCP_AES_CIPHER_KEY_0_reg(data)   (*((volatile unsigned int*) HDCP_AES_CIPHER_KEY_0_reg)=data)
#define get_HDCP_AES_CIPHER_KEY_0_reg   (*((volatile unsigned int*) HDCP_AES_CIPHER_KEY_0_reg))
#define HDCP_AES_CIPHER_KEY_0_inst_adr                                               "0x008F"
#define HDCP_AES_CIPHER_KEY_0_inst                                                   0x008F
#define HDCP_AES_CIPHER_KEY_0_aes_cipher_key70_shift                                 (0)
#define HDCP_AES_CIPHER_KEY_0_aes_cipher_key70_mask                                  (0x000000FF)
#define HDCP_AES_CIPHER_KEY_0_aes_cipher_key70(data)                                 (0x000000FF&((data)<<0))
#define HDCP_AES_CIPHER_KEY_0_aes_cipher_key70_src(data)                             ((0x000000FF&(data))>>0)
#define HDCP_AES_CIPHER_KEY_0_get_aes_cipher_key70(data)                             ((0x000000FF&(data))>>0)


#define HDCP22_CTRL                                                                  0x9803D240
#define HDCP22_CTRL_reg_addr                                                         "0x9803D240"
#define HDCP22_CTRL_reg                                                              0x9803D240
#define set_HDCP22_CTRL_reg(data)   (*((volatile unsigned int*) HDCP22_CTRL_reg)=data)
#define get_HDCP22_CTRL_reg   (*((volatile unsigned int*) HDCP22_CTRL_reg))
#define HDCP22_CTRL_inst_adr                                                         "0x0090"
#define HDCP22_CTRL_inst                                                             0x0090
#define HDCP22_CTRL_st1_type_shift                                                   (7)
#define HDCP22_CTRL_st1_type_mask                                                    (0x00000080)
#define HDCP22_CTRL_st1_type(data)                                                   (0x00000080&((data)<<7))
#define HDCP22_CTRL_st1_type_src(data)                                               ((0x00000080&(data))>>7)
#define HDCP22_CTRL_get_st1_type(data)                                               ((0x00000080&(data))>>7)
#define HDCP22_CTRL_st2_type_shift                                                   (6)
#define HDCP22_CTRL_st2_type_mask                                                    (0x00000040)
#define HDCP22_CTRL_st2_type(data)                                                   (0x00000040&((data)<<6))
#define HDCP22_CTRL_st2_type_src(data)                                               ((0x00000040&(data))>>6)
#define HDCP22_CTRL_get_st2_type(data)                                               ((0x00000040&(data))>>6)
#define HDCP22_CTRL_st3_type_shift                                                   (5)
#define HDCP22_CTRL_st3_type_mask                                                    (0x00000020)
#define HDCP22_CTRL_st3_type(data)                                                   (0x00000020&((data)<<5))
#define HDCP22_CTRL_st3_type_src(data)                                               ((0x00000020&(data))>>5)
#define HDCP22_CTRL_get_st3_type(data)                                               ((0x00000020&(data))>>5)
#define HDCP22_CTRL_st4_type_shift                                                   (4)
#define HDCP22_CTRL_st4_type_mask                                                    (0x00000010)
#define HDCP22_CTRL_st4_type(data)                                                   (0x00000010&((data)<<4))
#define HDCP22_CTRL_st4_type_src(data)                                               ((0x00000010&(data))>>4)
#define HDCP22_CTRL_get_st4_type(data)                                               ((0x00000010&(data))>>4)
#define HDCP22_CTRL_header_type_shift                                                (3)
#define HDCP22_CTRL_header_type_mask                                                 (0x00000008)
#define HDCP22_CTRL_header_type(data)                                                (0x00000008&((data)<<3))
#define HDCP22_CTRL_header_type_src(data)                                            ((0x00000008&(data))>>3)
#define HDCP22_CTRL_get_header_type(data)                                            ((0x00000008&(data))>>3)
#define HDCP22_CTRL_Reserved_shift                                                   (2)
#define HDCP22_CTRL_Reserved_mask                                                    (0x00000004)
#define HDCP22_CTRL_Reserved(data)                                                   (0x00000004&((data)<<2))
#define HDCP22_CTRL_Reserved_src(data)                                               ((0x00000004&(data))>>2)
#define HDCP22_CTRL_get_Reserved(data)                                               ((0x00000004&(data))>>2)
#define HDCP22_CTRL_authdone_hdcp22_shift                                            (1)
#define HDCP22_CTRL_authdone_hdcp22_mask                                             (0x00000002)
#define HDCP22_CTRL_authdone_hdcp22(data)                                            (0x00000002&((data)<<1))
#define HDCP22_CTRL_authdone_hdcp22_src(data)                                        ((0x00000002&(data))>>1)
#define HDCP22_CTRL_get_authdone_hdcp22(data)                                        ((0x00000002&(data))>>1)
#define HDCP22_CTRL_hdcp22_en_shift                                                  (0)
#define HDCP22_CTRL_hdcp22_en_mask                                                   (0x00000001)
#define HDCP22_CTRL_hdcp22_en(data)                                                  (0x00000001&((data)<<0))
#define HDCP22_CTRL_hdcp22_en_src(data)                                              ((0x00000001&(data))>>0)
#define HDCP22_CTRL_get_hdcp22_en(data)                                              ((0x00000001&(data))>>0)


#define HDCP22_TYPE_AES_0                                                            0x9803D244
#define HDCP22_TYPE_AES_0_reg_addr                                                   "0x9803D244"
#define HDCP22_TYPE_AES_0_reg                                                        0x9803D244
#define set_HDCP22_TYPE_AES_0_reg(data)   (*((volatile unsigned int*) HDCP22_TYPE_AES_0_reg)=data)
#define get_HDCP22_TYPE_AES_0_reg   (*((volatile unsigned int*) HDCP22_TYPE_AES_0_reg))
#define HDCP22_TYPE_AES_0_inst_adr                                                   "0x0091"
#define HDCP22_TYPE_AES_0_inst                                                       0x0091
#define HDCP22_TYPE_AES_0_type_to_aes0_shift                                         (0)
#define HDCP22_TYPE_AES_0_type_to_aes0_mask                                          (0x000000FF)
#define HDCP22_TYPE_AES_0_type_to_aes0(data)                                         (0x000000FF&((data)<<0))
#define HDCP22_TYPE_AES_0_type_to_aes0_src(data)                                     ((0x000000FF&(data))>>0)
#define HDCP22_TYPE_AES_0_get_type_to_aes0(data)                                     ((0x000000FF&(data))>>0)


#define HDCP22_TYPE_AES_1                                                            0x9803D248
#define HDCP22_TYPE_AES_1_reg_addr                                                   "0x9803D248"
#define HDCP22_TYPE_AES_1_reg                                                        0x9803D248
#define set_HDCP22_TYPE_AES_1_reg(data)   (*((volatile unsigned int*) HDCP22_TYPE_AES_1_reg)=data)
#define get_HDCP22_TYPE_AES_1_reg   (*((volatile unsigned int*) HDCP22_TYPE_AES_1_reg))
#define HDCP22_TYPE_AES_1_inst_adr                                                   "0x0092"
#define HDCP22_TYPE_AES_1_inst                                                       0x0092
#define HDCP22_TYPE_AES_1_type_to_aes1_shift                                         (0)
#define HDCP22_TYPE_AES_1_type_to_aes1_mask                                          (0x000000FF)
#define HDCP22_TYPE_AES_1_type_to_aes1(data)                                         (0x000000FF&((data)<<0))
#define HDCP22_TYPE_AES_1_type_to_aes1_src(data)                                     ((0x000000FF&(data))>>0)
#define HDCP22_TYPE_AES_1_get_type_to_aes1(data)                                     ((0x000000FF&(data))>>0)


#define DUMMY_1                                                                      0x9803D268
#define DUMMY_1_reg_addr                                                             "0x9803D268"
#define DUMMY_1_reg                                                                  0x9803D268
#define set_DUMMY_1_reg(data)   (*((volatile unsigned int*) DUMMY_1_reg)=data)
#define get_DUMMY_1_reg   (*((volatile unsigned int*) DUMMY_1_reg))
#define DUMMY_1_inst_adr                                                             "0x009A"
#define DUMMY_1_inst                                                                 0x009A
#define DUMMY_1_DUMMY_shift                                                          (1)
#define DUMMY_1_DUMMY_mask                                                           (0x000000FE)
#define DUMMY_1_DUMMY(data)                                                          (0x000000FE&((data)<<1))
#define DUMMY_1_DUMMY_src(data)                                                      ((0x000000FE&(data))>>1)
#define DUMMY_1_get_DUMMY(data)                                                      ((0x000000FE&(data))>>1)
#define DUMMY_1_Bist_clk_en_hdcp_shift                                               (0)
#define DUMMY_1_Bist_clk_en_hdcp_mask                                                (0x00000001)
#define DUMMY_1_Bist_clk_en_hdcp(data)                                               (0x00000001&((data)<<0))
#define DUMMY_1_Bist_clk_en_hdcp_src(data)                                           ((0x00000001&(data))>>0)
#define DUMMY_1_get_Bist_clk_en_hdcp(data)                                           ((0x00000001&(data))>>0)


#define DUMMY_2                                                                      0x9803D26C
#define DUMMY_2_reg_addr                                                             "0x9803D26C"
#define DUMMY_2_reg                                                                  0x9803D26C
#define set_DUMMY_2_reg(data)   (*((volatile unsigned int*) DUMMY_2_reg)=data)
#define get_DUMMY_2_reg   (*((volatile unsigned int*) DUMMY_2_reg))
#define DUMMY_2_inst_adr                                                             "0x009B"
#define DUMMY_2_inst                                                                 0x009B
#define DUMMY_2_DUMMY_shift                                                          (0)
#define DUMMY_2_DUMMY_mask                                                           (0x000000FF)
#define DUMMY_2_DUMMY(data)                                                          (0x000000FF&((data)<<0))
#define DUMMY_2_DUMMY_src(data)                                                      ((0x000000FF&(data))>>0)
#define DUMMY_2_get_DUMMY(data)                                                      ((0x000000FF&(data))>>0)


#define DUMMY_3                                                                      0x9803D270
#define DUMMY_3_reg_addr                                                             "0x9803D270"
#define DUMMY_3_reg                                                                  0x9803D270
#define set_DUMMY_3_reg(data)   (*((volatile unsigned int*) DUMMY_3_reg)=data)
#define get_DUMMY_3_reg   (*((volatile unsigned int*) DUMMY_3_reg))
#define DUMMY_3_inst_adr                                                             "0x009C"
#define DUMMY_3_inst                                                                 0x009C
#define DUMMY_3_DUMMY_shift                                                          (0)
#define DUMMY_3_DUMMY_mask                                                           (0x000000FF)
#define DUMMY_3_DUMMY(data)                                                          (0x000000FF&((data)<<0))
#define DUMMY_3_DUMMY_src(data)                                                      ((0x000000FF&(data))>>0)
#define DUMMY_3_get_DUMMY(data)                                                      ((0x000000FF&(data))>>0)


#define HPD_CTRL                                                                     0x9803D1C0
#define HPD_CTRL_reg_addr                                                            "0x9803D1C0"
#define HPD_CTRL_reg                                                                 0x9803D1C0
#define set_HPD_CTRL_reg(data)   (*((volatile unsigned int*) HPD_CTRL_reg)=data)
#define get_HPD_CTRL_reg   (*((volatile unsigned int*) HPD_CTRL_reg))
#define HPD_CTRL_inst_adr                                                            "0x0070"
#define HPD_CTRL_inst                                                                0x0070
#define HPD_CTRL_hpd_en_shift                                                        (7)
#define HPD_CTRL_hpd_en_mask                                                         (0x00000080)
#define HPD_CTRL_hpd_en(data)                                                        (0x00000080&((data)<<7))
#define HPD_CTRL_hpd_en_src(data)                                                    ((0x00000080&(data))>>7)
#define HPD_CTRL_get_hpd_en(data)                                                    ((0x00000080&(data))>>7)
#define HPD_CTRL_hpd_clk_div_shift                                                   (5)
#define HPD_CTRL_hpd_clk_div_mask                                                    (0x00000060)
#define HPD_CTRL_hpd_clk_div(data)                                                   (0x00000060&((data)<<5))
#define HPD_CTRL_hpd_clk_div_src(data)                                               ((0x00000060&(data))>>5)
#define HPD_CTRL_get_hpd_clk_div(data)                                               ((0x00000060&(data))>>5)
#define HPD_CTRL_hpd_deb_level_shift                                                 (3)
#define HPD_CTRL_hpd_deb_level_mask                                                  (0x00000018)
#define HPD_CTRL_hpd_deb_level(data)                                                 (0x00000018&((data)<<3))
#define HPD_CTRL_hpd_deb_level_src(data)                                             ((0x00000018&(data))>>3)
#define HPD_CTRL_get_hpd_deb_level(data)                                             ((0x00000018&(data))>>3)
#define HPD_CTRL_hpd_deb_shift                                                       (2)
#define HPD_CTRL_hpd_deb_mask                                                        (0x00000004)
#define HPD_CTRL_hpd_deb(data)                                                       (0x00000004&((data)<<2))
#define HPD_CTRL_hpd_deb_src(data)                                                   ((0x00000004&(data))>>2)
#define HPD_CTRL_get_hpd_deb(data)                                                   ((0x00000004&(data))>>2)
#define HPD_CTRL_Reserved_shift                                                      (0)
#define HPD_CTRL_Reserved_mask                                                       (0x00000003)
#define HPD_CTRL_Reserved(data)                                                      (0x00000003&((data)<<0))
#define HPD_CTRL_Reserved_src(data)                                                  ((0x00000003&(data))>>0)
#define HPD_CTRL_get_Reserved(data)                                                  ((0x00000003&(data))>>0)


#define HPD_IRQ                                                                      0x9803D1C4
#define HPD_IRQ_reg_addr                                                             "0x9803D1C4"
#define HPD_IRQ_reg                                                                  0x9803D1C4
#define set_HPD_IRQ_reg(data)   (*((volatile unsigned int*) HPD_IRQ_reg)=data)
#define get_HPD_IRQ_reg   (*((volatile unsigned int*) HPD_IRQ_reg))
#define HPD_IRQ_inst_adr                                                             "0x0071"
#define HPD_IRQ_inst                                                                 0x0071
#define HPD_IRQ_ihpd_int_shift                                                       (7)
#define HPD_IRQ_ihpd_int_mask                                                        (0x00000080)
#define HPD_IRQ_ihpd_int(data)                                                       (0x00000080&((data)<<7))
#define HPD_IRQ_ihpd_int_src(data)                                                   ((0x00000080&(data))>>7)
#define HPD_IRQ_get_ihpd_int(data)                                                   ((0x00000080&(data))>>7)
#define HPD_IRQ_shpd_int_shift                                                       (6)
#define HPD_IRQ_shpd_int_mask                                                        (0x00000040)
#define HPD_IRQ_shpd_int(data)                                                       (0x00000040&((data)<<6))
#define HPD_IRQ_shpd_int_src(data)                                                   ((0x00000040&(data))>>6)
#define HPD_IRQ_get_shpd_int(data)                                                   ((0x00000040&(data))>>6)
#define HPD_IRQ_lhpd_int_shift                                                       (5)
#define HPD_IRQ_lhpd_int_mask                                                        (0x00000020)
#define HPD_IRQ_lhpd_int(data)                                                       (0x00000020&((data)<<5))
#define HPD_IRQ_lhpd_int_src(data)                                                   ((0x00000020&(data))>>5)
#define HPD_IRQ_get_lhpd_int(data)                                                   ((0x00000020&(data))>>5)
#define HPD_IRQ_uhpd_int_shift                                                       (4)
#define HPD_IRQ_uhpd_int_mask                                                        (0x00000010)
#define HPD_IRQ_uhpd_int(data)                                                       (0x00000010&((data)<<4))
#define HPD_IRQ_uhpd_int_src(data)                                                   ((0x00000010&(data))>>4)
#define HPD_IRQ_get_uhpd_int(data)                                                   ((0x00000010&(data))>>4)
#define HPD_IRQ_unhpd_int_shift                                                      (3)
#define HPD_IRQ_unhpd_int_mask                                                       (0x00000008)
#define HPD_IRQ_unhpd_int(data)                                                      (0x00000008&((data)<<3))
#define HPD_IRQ_unhpd_int_src(data)                                                  ((0x00000008&(data))>>3)
#define HPD_IRQ_get_unhpd_int(data)                                                  ((0x00000008&(data))>>3)
#define HPD_IRQ_rhpd_int_shift                                                       (2)
#define HPD_IRQ_rhpd_int_mask                                                        (0x00000004)
#define HPD_IRQ_rhpd_int(data)                                                       (0x00000004&((data)<<2))
#define HPD_IRQ_rhpd_int_src(data)                                                   ((0x00000004&(data))>>2)
#define HPD_IRQ_get_rhpd_int(data)                                                   ((0x00000004&(data))>>2)
#define HPD_IRQ_fhpd_int_shift                                                       (1)
#define HPD_IRQ_fhpd_int_mask                                                        (0x00000002)
#define HPD_IRQ_fhpd_int(data)                                                       (0x00000002&((data)<<1))
#define HPD_IRQ_fhpd_int_src(data)                                                   ((0x00000002&(data))>>1)
#define HPD_IRQ_get_fhpd_int(data)                                                   ((0x00000002&(data))>>1)
#define HPD_IRQ_Reserved_shift                                                       (0)
#define HPD_IRQ_Reserved_mask                                                        (0x00000001)
#define HPD_IRQ_Reserved(data)                                                       (0x00000001&((data)<<0))
#define HPD_IRQ_Reserved_src(data)                                                   ((0x00000001&(data))>>0)
#define HPD_IRQ_get_Reserved(data)                                                   ((0x00000001&(data))>>0)


#define HPD_IRQ_EN                                                                   0x9803D1C8
#define HPD_IRQ_EN_reg_addr                                                          "0x9803D1C8"
#define HPD_IRQ_EN_reg                                                               0x9803D1C8
#define set_HPD_IRQ_EN_reg(data)   (*((volatile unsigned int*) HPD_IRQ_EN_reg)=data)
#define get_HPD_IRQ_EN_reg   (*((volatile unsigned int*) HPD_IRQ_EN_reg))
#define HPD_IRQ_EN_inst_adr                                                          "0x0072"
#define HPD_IRQ_EN_inst                                                              0x0072
#define HPD_IRQ_EN_ihpd_int_en_shift                                                 (7)
#define HPD_IRQ_EN_ihpd_int_en_mask                                                  (0x00000080)
#define HPD_IRQ_EN_ihpd_int_en(data)                                                 (0x00000080&((data)<<7))
#define HPD_IRQ_EN_ihpd_int_en_src(data)                                             ((0x00000080&(data))>>7)
#define HPD_IRQ_EN_get_ihpd_int_en(data)                                             ((0x00000080&(data))>>7)
#define HPD_IRQ_EN_shpd_int_en_shift                                                 (6)
#define HPD_IRQ_EN_shpd_int_en_mask                                                  (0x00000040)
#define HPD_IRQ_EN_shpd_int_en(data)                                                 (0x00000040&((data)<<6))
#define HPD_IRQ_EN_shpd_int_en_src(data)                                             ((0x00000040&(data))>>6)
#define HPD_IRQ_EN_get_shpd_int_en(data)                                             ((0x00000040&(data))>>6)
#define HPD_IRQ_EN_lhpd_int_en_shift                                                 (5)
#define HPD_IRQ_EN_lhpd_int_en_mask                                                  (0x00000020)
#define HPD_IRQ_EN_lhpd_int_en(data)                                                 (0x00000020&((data)<<5))
#define HPD_IRQ_EN_lhpd_int_en_src(data)                                             ((0x00000020&(data))>>5)
#define HPD_IRQ_EN_get_lhpd_int_en(data)                                             ((0x00000020&(data))>>5)
#define HPD_IRQ_EN_uhpd_int_en_shift                                                 (4)
#define HPD_IRQ_EN_uhpd_int_en_mask                                                  (0x00000010)
#define HPD_IRQ_EN_uhpd_int_en(data)                                                 (0x00000010&((data)<<4))
#define HPD_IRQ_EN_uhpd_int_en_src(data)                                             ((0x00000010&(data))>>4)
#define HPD_IRQ_EN_get_uhpd_int_en(data)                                             ((0x00000010&(data))>>4)
#define HPD_IRQ_EN_unhpd_int_en_shift                                                (3)
#define HPD_IRQ_EN_unhpd_int_en_mask                                                 (0x00000008)
#define HPD_IRQ_EN_unhpd_int_en(data)                                                (0x00000008&((data)<<3))
#define HPD_IRQ_EN_unhpd_int_en_src(data)                                            ((0x00000008&(data))>>3)
#define HPD_IRQ_EN_get_unhpd_int_en(data)                                            ((0x00000008&(data))>>3)
#define HPD_IRQ_EN_rhpd_int_en_shift                                                 (2)
#define HPD_IRQ_EN_rhpd_int_en_mask                                                  (0x00000004)
#define HPD_IRQ_EN_rhpd_int_en(data)                                                 (0x00000004&((data)<<2))
#define HPD_IRQ_EN_rhpd_int_en_src(data)                                             ((0x00000004&(data))>>2)
#define HPD_IRQ_EN_get_rhpd_int_en(data)                                             ((0x00000004&(data))>>2)
#define HPD_IRQ_EN_fhpd_int_en_shift                                                 (1)
#define HPD_IRQ_EN_fhpd_int_en_mask                                                  (0x00000002)
#define HPD_IRQ_EN_fhpd_int_en(data)                                                 (0x00000002&((data)<<1))
#define HPD_IRQ_EN_fhpd_int_en_src(data)                                             ((0x00000002&(data))>>1)
#define HPD_IRQ_EN_get_fhpd_int_en(data)                                             ((0x00000002&(data))>>1)
#define HPD_IRQ_EN_Reserved_shift                                                    (0)
#define HPD_IRQ_EN_Reserved_mask                                                     (0x00000001)
#define HPD_IRQ_EN_Reserved(data)                                                    (0x00000001&((data)<<0))
#define HPD_IRQ_EN_Reserved_src(data)                                                ((0x00000001&(data))>>0)
#define HPD_IRQ_EN_get_Reserved(data)                                                ((0x00000001&(data))>>0)


#define HPD_TIMER1                                                                   0x9803D1CC
#define HPD_TIMER1_reg_addr                                                          "0x9803D1CC"
#define HPD_TIMER1_reg                                                               0x9803D1CC
#define set_HPD_TIMER1_reg(data)   (*((volatile unsigned int*) HPD_TIMER1_reg)=data)
#define get_HPD_TIMER1_reg   (*((volatile unsigned int*) HPD_TIMER1_reg))
#define HPD_TIMER1_inst_adr                                                          "0x0073"
#define HPD_TIMER1_inst                                                              0x0073
#define HPD_TIMER1_hpd_t5118_shift                                                   (4)
#define HPD_TIMER1_hpd_t5118_mask                                                    (0x000000F0)
#define HPD_TIMER1_hpd_t5118(data)                                                   (0x000000F0&((data)<<4))
#define HPD_TIMER1_hpd_t5118_src(data)                                               ((0x000000F0&(data))>>4)
#define HPD_TIMER1_get_hpd_t5118(data)                                               ((0x000000F0&(data))>>4)
#define HPD_TIMER1_hpd_t10118_shift                                                  (0)
#define HPD_TIMER1_hpd_t10118_mask                                                   (0x0000000F)
#define HPD_TIMER1_hpd_t10118(data)                                                  (0x0000000F&((data)<<0))
#define HPD_TIMER1_hpd_t10118_src(data)                                              ((0x0000000F&(data))>>0)
#define HPD_TIMER1_get_hpd_t10118(data)                                              ((0x0000000F&(data))>>0)


#define HPD_TIMER2                                                                   0x9803D1D0
#define HPD_TIMER2_reg_addr                                                          "0x9803D1D0"
#define HPD_TIMER2_reg                                                               0x9803D1D0
#define set_HPD_TIMER2_reg(data)   (*((volatile unsigned int*) HPD_TIMER2_reg)=data)
#define get_HPD_TIMER2_reg   (*((volatile unsigned int*) HPD_TIMER2_reg))
#define HPD_TIMER2_inst_adr                                                          "0x0074"
#define HPD_TIMER2_inst                                                              0x0074
#define HPD_TIMER2_hpd_t570_shift                                                    (0)
#define HPD_TIMER2_hpd_t570_mask                                                     (0x000000FF)
#define HPD_TIMER2_hpd_t570(data)                                                    (0x000000FF&((data)<<0))
#define HPD_TIMER2_hpd_t570_src(data)                                                ((0x000000FF&(data))>>0)
#define HPD_TIMER2_get_hpd_t570(data)                                                ((0x000000FF&(data))>>0)


#define HPD_TIMER3                                                                   0x9803D1D4
#define HPD_TIMER3_reg_addr                                                          "0x9803D1D4"
#define HPD_TIMER3_reg                                                               0x9803D1D4
#define set_HPD_TIMER3_reg(data)   (*((volatile unsigned int*) HPD_TIMER3_reg)=data)
#define get_HPD_TIMER3_reg   (*((volatile unsigned int*) HPD_TIMER3_reg))
#define HPD_TIMER3_inst_adr                                                          "0x0075"
#define HPD_TIMER3_inst                                                              0x0075
#define HPD_TIMER3_hpd_t1070_shift                                                   (0)
#define HPD_TIMER3_hpd_t1070_mask                                                    (0x000000FF)
#define HPD_TIMER3_hpd_t1070(data)                                                   (0x000000FF&((data)<<0))
#define HPD_TIMER3_hpd_t1070_src(data)                                               ((0x000000FF&(data))>>0)
#define HPD_TIMER3_get_hpd_t1070(data)                                               ((0x000000FF&(data))>>0)


#define HPD_TIMER4                                                                   0x9803D1D8
#define HPD_TIMER4_reg_addr                                                          "0x9803D1D8"
#define HPD_TIMER4_reg                                                               0x9803D1D8
#define set_HPD_TIMER4_reg(data)   (*((volatile unsigned int*) HPD_TIMER4_reg)=data)
#define get_HPD_TIMER4_reg   (*((volatile unsigned int*) HPD_TIMER4_reg))
#define HPD_TIMER4_inst_adr                                                          "0x0076"
#define HPD_TIMER4_inst                                                              0x0076
#define HPD_TIMER4_Reserved_shift                                                    (4)
#define HPD_TIMER4_Reserved_mask                                                     (0x000000F0)
#define HPD_TIMER4_Reserved(data)                                                    (0x000000F0&((data)<<4))
#define HPD_TIMER4_Reserved_src(data)                                                ((0x000000F0&(data))>>4)
#define HPD_TIMER4_get_Reserved(data)                                                ((0x000000F0&(data))>>4)
#define HPD_TIMER4_hpd_t20118_shift                                                  (0)
#define HPD_TIMER4_hpd_t20118_mask                                                   (0x0000000F)
#define HPD_TIMER4_hpd_t20118(data)                                                  (0x0000000F&((data)<<0))
#define HPD_TIMER4_hpd_t20118_src(data)                                              ((0x0000000F&(data))>>0)
#define HPD_TIMER4_get_hpd_t20118(data)                                              ((0x0000000F&(data))>>0)


#define HPD_TIMER5                                                                   0x9803D1DC
#define HPD_TIMER5_reg_addr                                                          "0x9803D1DC"
#define HPD_TIMER5_reg                                                               0x9803D1DC
#define set_HPD_TIMER5_reg(data)   (*((volatile unsigned int*) HPD_TIMER5_reg)=data)
#define get_HPD_TIMER5_reg   (*((volatile unsigned int*) HPD_TIMER5_reg))
#define HPD_TIMER5_inst_adr                                                          "0x0077"
#define HPD_TIMER5_inst                                                              0x0077
#define HPD_TIMER5_hpd_t2070_shift                                                   (0)
#define HPD_TIMER5_hpd_t2070_mask                                                    (0x000000FF)
#define HPD_TIMER5_hpd_t2070(data)                                                   (0x000000FF&((data)<<0))
#define HPD_TIMER5_hpd_t2070_src(data)                                               ((0x000000FF&(data))>>0)
#define HPD_TIMER5_get_hpd_t2070(data)                                               ((0x000000FF&(data))>>0)


#define HPD_TIMER6                                                                   0x9803D1E0
#define HPD_TIMER6_reg_addr                                                          "0x9803D1E0"
#define HPD_TIMER6_reg                                                               0x9803D1E0
#define set_HPD_TIMER6_reg(data)   (*((volatile unsigned int*) HPD_TIMER6_reg)=data)
#define get_HPD_TIMER6_reg   (*((volatile unsigned int*) HPD_TIMER6_reg))
#define HPD_TIMER6_inst_adr                                                          "0x0078"
#define HPD_TIMER6_inst                                                              0x0078
#define HPD_TIMER6_hpd_t100158_shift                                                 (0)
#define HPD_TIMER6_hpd_t100158_mask                                                  (0x000000FF)
#define HPD_TIMER6_hpd_t100158(data)                                                 (0x000000FF&((data)<<0))
#define HPD_TIMER6_hpd_t100158_src(data)                                             ((0x000000FF&(data))>>0)
#define HPD_TIMER6_get_hpd_t100158(data)                                             ((0x000000FF&(data))>>0)


#define HPD_TIMER7                                                                   0x9803D1E4
#define HPD_TIMER7_reg_addr                                                          "0x9803D1E4"
#define HPD_TIMER7_reg                                                               0x9803D1E4
#define set_HPD_TIMER7_reg(data)   (*((volatile unsigned int*) HPD_TIMER7_reg)=data)
#define get_HPD_TIMER7_reg   (*((volatile unsigned int*) HPD_TIMER7_reg))
#define HPD_TIMER7_inst_adr                                                          "0x0079"
#define HPD_TIMER7_inst                                                              0x0079
#define HPD_TIMER7_hpd_t10070_shift                                                  (0)
#define HPD_TIMER7_hpd_t10070_mask                                                   (0x000000FF)
#define HPD_TIMER7_hpd_t10070(data)                                                  (0x000000FF&((data)<<0))
#define HPD_TIMER7_hpd_t10070_src(data)                                              ((0x000000FF&(data))>>0)
#define HPD_TIMER7_get_hpd_t10070(data)                                              ((0x000000FF&(data))>>0)


#define HPD_LONG0                                                                    0x9803D1E8
#define HPD_LONG0_reg_addr                                                           "0x9803D1E8"
#define HPD_LONG0_reg                                                                0x9803D1E8
#define set_HPD_LONG0_reg(data)   (*((volatile unsigned int*) HPD_LONG0_reg)=data)
#define get_HPD_LONG0_reg   (*((volatile unsigned int*) HPD_LONG0_reg))
#define HPD_LONG0_inst_adr                                                           "0x007A"
#define HPD_LONG0_inst                                                               0x007A
#define HPD_LONG0_hpd_long158_shift                                                  (0)
#define HPD_LONG0_hpd_long158_mask                                                   (0x000000FF)
#define HPD_LONG0_hpd_long158(data)                                                  (0x000000FF&((data)<<0))
#define HPD_LONG0_hpd_long158_src(data)                                              ((0x000000FF&(data))>>0)
#define HPD_LONG0_get_hpd_long158(data)                                              ((0x000000FF&(data))>>0)


#define HPD_LONG1                                                                    0x9803D1EC
#define HPD_LONG1_reg_addr                                                           "0x9803D1EC"
#define HPD_LONG1_reg                                                                0x9803D1EC
#define set_HPD_LONG1_reg(data)   (*((volatile unsigned int*) HPD_LONG1_reg)=data)
#define get_HPD_LONG1_reg   (*((volatile unsigned int*) HPD_LONG1_reg))
#define HPD_LONG1_inst_adr                                                           "0x007B"
#define HPD_LONG1_inst                                                               0x007B
#define HPD_LONG1_hpd_long70_shift                                                   (0)
#define HPD_LONG1_hpd_long70_mask                                                    (0x000000FF)
#define HPD_LONG1_hpd_long70(data)                                                   (0x000000FF&((data)<<0))
#define HPD_LONG1_hpd_long70_src(data)                                               ((0x000000FF&(data))>>0)
#define HPD_LONG1_get_hpd_long70(data)                                               ((0x000000FF&(data))>>0)


#define HPD_STATE                                                                    0x9803D1F0
#define HPD_STATE_reg_addr                                                           "0x9803D1F0"
#define HPD_STATE_reg                                                                0x9803D1F0
#define set_HPD_STATE_reg(data)   (*((volatile unsigned int*) HPD_STATE_reg)=data)
#define get_HPD_STATE_reg   (*((volatile unsigned int*) HPD_STATE_reg))
#define HPD_STATE_inst_adr                                                           "0x007C"
#define HPD_STATE_inst                                                               0x007C
#define HPD_STATE_Reserved_shift                                                     (4)
#define HPD_STATE_Reserved_mask                                                      (0x000000F0)
#define HPD_STATE_Reserved(data)                                                     (0x000000F0&((data)<<4))
#define HPD_STATE_Reserved_src(data)                                                 ((0x000000F0&(data))>>4)
#define HPD_STATE_get_Reserved(data)                                                 ((0x000000F0&(data))>>4)
#define HPD_STATE_hpd_state_shift                                                    (0)
#define HPD_STATE_hpd_state_mask                                                     (0x0000000F)
#define HPD_STATE_hpd_state(data)                                                    (0x0000000F&((data)<<0))
#define HPD_STATE_hpd_state_src(data)                                                ((0x0000000F&(data))>>0)
#define HPD_STATE_get_hpd_state(data)                                                ((0x0000000F&(data))>>0)


#define RESERVED_0                                                                   0x9803D1F4
#define RESERVED_0_reg_addr                                                          "0x9803D1F4"
#define RESERVED_0_reg                                                               0x9803D1F4
#define set_RESERVED_0_reg(data)   (*((volatile unsigned int*) RESERVED_0_reg)=data)
#define get_RESERVED_0_reg   (*((volatile unsigned int*) RESERVED_0_reg))
#define RESERVED_0_inst_adr                                                          "0x007D"
#define RESERVED_0_inst                                                              0x007D
#define RESERVED_0_hpd_rsv1_shift                                                    (0)
#define RESERVED_0_hpd_rsv1_mask                                                     (0x000000FF)
#define RESERVED_0_hpd_rsv1(data)                                                    (0x000000FF&((data)<<0))
#define RESERVED_0_hpd_rsv1_src(data)                                                ((0x000000FF&(data))>>0)
#define RESERVED_0_get_hpd_rsv1(data)                                                ((0x000000FF&(data))>>0)


#define RESERVED_1                                                                   0x9803D1F8
#define RESERVED_1_reg_addr                                                          "0x9803D1F8"
#define RESERVED_1_reg                                                               0x9803D1F8
#define set_RESERVED_1_reg(data)   (*((volatile unsigned int*) RESERVED_1_reg)=data)
#define get_RESERVED_1_reg   (*((volatile unsigned int*) RESERVED_1_reg))
#define RESERVED_1_inst_adr                                                          "0x007E"
#define RESERVED_1_inst                                                              0x007E
#define RESERVED_1_hpd_rsv2_shift                                                    (0)
#define RESERVED_1_hpd_rsv2_mask                                                     (0x000000FF)
#define RESERVED_1_hpd_rsv2(data)                                                    (0x000000FF&((data)<<0))
#define RESERVED_1_hpd_rsv2_src(data)                                                ((0x000000FF&(data))>>0)
#define RESERVED_1_get_hpd_rsv2(data)                                                ((0x000000FF&(data))>>0)


#define DPTX_PHY_CTRL0                                                               0x9803D680
#define DPTX_PHY_CTRL0_reg_addr                                                      "0x9803D680"
#define DPTX_PHY_CTRL0_reg                                                           0x9803D680
#define set_DPTX_PHY_CTRL0_reg(data)   (*((volatile unsigned int*) DPTX_PHY_CTRL0_reg)=data)
#define get_DPTX_PHY_CTRL0_reg   (*((volatile unsigned int*) DPTX_PHY_CTRL0_reg))
#define DPTX_PHY_CTRL0_inst_adr                                                      "0x00A0"
#define DPTX_PHY_CTRL0_inst                                                          0x00A0
#define DPTX_PHY_CTRL0_reg_pow_dptx_shift                                            (7)
#define DPTX_PHY_CTRL0_reg_pow_dptx_mask                                             (0x00000080)
#define DPTX_PHY_CTRL0_reg_pow_dptx(data)                                            (0x00000080&((data)<<7))
#define DPTX_PHY_CTRL0_reg_pow_dptx_src(data)                                        ((0x00000080&(data))>>7)
#define DPTX_PHY_CTRL0_get_reg_pow_dptx(data)                                        ((0x00000080&(data))>>7)
#define DPTX_PHY_CTRL0_reg_dptx_testen_shift                                         (6)
#define DPTX_PHY_CTRL0_reg_dptx_testen_mask                                          (0x00000040)
#define DPTX_PHY_CTRL0_reg_dptx_testen(data)                                         (0x00000040&((data)<<6))
#define DPTX_PHY_CTRL0_reg_dptx_testen_src(data)                                     ((0x00000040&(data))>>6)
#define DPTX_PHY_CTRL0_get_reg_dptx_testen(data)                                     ((0x00000040&(data))>>6)
#define DPTX_PHY_CTRL0_Reserved_shift                                                (5)
#define DPTX_PHY_CTRL0_Reserved_mask                                                 (0x00000020)
#define DPTX_PHY_CTRL0_Reserved(data)                                                (0x00000020&((data)<<5))
#define DPTX_PHY_CTRL0_Reserved_src(data)                                            ((0x00000020&(data))>>5)
#define DPTX_PHY_CTRL0_get_Reserved(data)                                            ((0x00000020&(data))>>5)
#define DPTX_PHY_CTRL0_reg_dptx_cmu_en_shift                                         (4)
#define DPTX_PHY_CTRL0_reg_dptx_cmu_en_mask                                          (0x00000010)
#define DPTX_PHY_CTRL0_reg_dptx_cmu_en(data)                                         (0x00000010&((data)<<4))
#define DPTX_PHY_CTRL0_reg_dptx_cmu_en_src(data)                                     ((0x00000010&(data))>>4)
#define DPTX_PHY_CTRL0_get_reg_dptx_cmu_en(data)                                     ((0x00000010&(data))>>4)
#define DPTX_PHY_CTRL0_reg_pow_dptx_lane30_shift                                     (0)
#define DPTX_PHY_CTRL0_reg_pow_dptx_lane30_mask                                      (0x0000000F)
#define DPTX_PHY_CTRL0_reg_pow_dptx_lane30(data)                                     (0x0000000F&((data)<<0))
#define DPTX_PHY_CTRL0_reg_pow_dptx_lane30_src(data)                                 ((0x0000000F&(data))>>0)
#define DPTX_PHY_CTRL0_get_reg_pow_dptx_lane30(data)                                 ((0x0000000F&(data))>>0)


#define DPTX_PHY_CTRL1                                                               0x9803D684
#define DPTX_PHY_CTRL1_reg_addr                                                      "0x9803D684"
#define DPTX_PHY_CTRL1_reg                                                           0x9803D684
#define set_DPTX_PHY_CTRL1_reg(data)   (*((volatile unsigned int*) DPTX_PHY_CTRL1_reg)=data)
#define get_DPTX_PHY_CTRL1_reg   (*((volatile unsigned int*) DPTX_PHY_CTRL1_reg))
#define DPTX_PHY_CTRL1_inst_adr                                                      "0x00A1"
#define DPTX_PHY_CTRL1_inst                                                          0x00A1
#define DPTX_PHY_CTRL1_dptx_tx2idle30_shift                                          (4)
#define DPTX_PHY_CTRL1_dptx_tx2idle30_mask                                           (0x000000F0)
#define DPTX_PHY_CTRL1_dptx_tx2idle30(data)                                          (0x000000F0&((data)<<4))
#define DPTX_PHY_CTRL1_dptx_tx2idle30_src(data)                                      ((0x000000F0&(data))>>4)
#define DPTX_PHY_CTRL1_get_dptx_tx2idle30(data)                                      ((0x000000F0&(data))>>4)
#define DPTX_PHY_CTRL1_reg_dptx_pdown30_shift                                        (0)
#define DPTX_PHY_CTRL1_reg_dptx_pdown30_mask                                         (0x0000000F)
#define DPTX_PHY_CTRL1_reg_dptx_pdown30(data)                                        (0x0000000F&((data)<<0))
#define DPTX_PHY_CTRL1_reg_dptx_pdown30_src(data)                                    ((0x0000000F&(data))>>0)
#define DPTX_PHY_CTRL1_get_reg_dptx_pdown30(data)                                    ((0x0000000F&(data))>>0)


#define DPTX_RCV_DET0                                                                0x9803D688
#define DPTX_RCV_DET0_reg_addr                                                       "0x9803D688"
#define DPTX_RCV_DET0_reg                                                            0x9803D688
#define set_DPTX_RCV_DET0_reg(data)   (*((volatile unsigned int*) DPTX_RCV_DET0_reg)=data)
#define get_DPTX_RCV_DET0_reg   (*((volatile unsigned int*) DPTX_RCV_DET0_reg))
#define DPTX_RCV_DET0_inst_adr                                                       "0x00A2"
#define DPTX_RCV_DET0_inst                                                           0x00A2
#define DPTX_RCV_DET0_reg_dptx_force_rcvdet_shift                                    (7)
#define DPTX_RCV_DET0_reg_dptx_force_rcvdet_mask                                     (0x00000080)
#define DPTX_RCV_DET0_reg_dptx_force_rcvdet(data)                                    (0x00000080&((data)<<7))
#define DPTX_RCV_DET0_reg_dptx_force_rcvdet_src(data)                                ((0x00000080&(data))>>7)
#define DPTX_RCV_DET0_get_reg_dptx_force_rcvdet(data)                                ((0x00000080&(data))>>7)
#define DPTX_RCV_DET0_reg_dptx_rcvdet_en_shift                                       (6)
#define DPTX_RCV_DET0_reg_dptx_rcvdet_en_mask                                        (0x00000040)
#define DPTX_RCV_DET0_reg_dptx_rcvdet_en(data)                                       (0x00000040&((data)<<6))
#define DPTX_RCV_DET0_reg_dptx_rcvdet_en_src(data)                                   ((0x00000040&(data))>>6)
#define DPTX_RCV_DET0_get_reg_dptx_rcvdet_en(data)                                   ((0x00000040&(data))>>6)
#define DPTX_RCV_DET0_reg_dptx_rcv_detect_shift                                      (5)
#define DPTX_RCV_DET0_reg_dptx_rcv_detect_mask                                       (0x00000020)
#define DPTX_RCV_DET0_reg_dptx_rcv_detect(data)                                      (0x00000020&((data)<<5))
#define DPTX_RCV_DET0_reg_dptx_rcv_detect_src(data)                                  ((0x00000020&(data))>>5)
#define DPTX_RCV_DET0_get_reg_dptx_rcv_detect(data)                                  ((0x00000020&(data))>>5)
#define DPTX_RCV_DET0_Reserved_shift                                                 (0)
#define DPTX_RCV_DET0_Reserved_mask                                                  (0x0000001F)
#define DPTX_RCV_DET0_Reserved(data)                                                 (0x0000001F&((data)<<0))
#define DPTX_RCV_DET0_Reserved_src(data)                                             ((0x0000001F&(data))>>0)
#define DPTX_RCV_DET0_get_Reserved(data)                                             ((0x0000001F&(data))>>0)


#define DPTX_RCV_DET1                                                                0x9803D68C
#define DPTX_RCV_DET1_reg_addr                                                       "0x9803D68C"
#define DPTX_RCV_DET1_reg                                                            0x9803D68C
#define set_DPTX_RCV_DET1_reg(data)   (*((volatile unsigned int*) DPTX_RCV_DET1_reg)=data)
#define get_DPTX_RCV_DET1_reg   (*((volatile unsigned int*) DPTX_RCV_DET1_reg))
#define DPTX_RCV_DET1_inst_adr                                                       "0x00A3"
#define DPTX_RCV_DET1_inst                                                           0x00A3
#define DPTX_RCV_DET1_dptx_rxdet30_shift                                             (4)
#define DPTX_RCV_DET1_dptx_rxdet30_mask                                              (0x000000F0)
#define DPTX_RCV_DET1_dptx_rxdet30(data)                                             (0x000000F0&((data)<<4))
#define DPTX_RCV_DET1_dptx_rxdet30_src(data)                                         ((0x000000F0&(data))>>4)
#define DPTX_RCV_DET1_get_dptx_rxdet30(data)                                         ((0x000000F0&(data))>>4)
#define DPTX_RCV_DET1_dptx_enddet30_shift                                            (0)
#define DPTX_RCV_DET1_dptx_enddet30_mask                                             (0x0000000F)
#define DPTX_RCV_DET1_dptx_enddet30(data)                                            (0x0000000F&((data)<<0))
#define DPTX_RCV_DET1_dptx_enddet30_src(data)                                        ((0x0000000F&(data))>>0)
#define DPTX_RCV_DET1_get_dptx_enddet30(data)                                        ((0x0000000F&(data))>>0)


#define DPTX_PN_SWAP                                                                 0x9803D690
#define DPTX_PN_SWAP_reg_addr                                                        "0x9803D690"
#define DPTX_PN_SWAP_reg                                                             0x9803D690
#define set_DPTX_PN_SWAP_reg(data)   (*((volatile unsigned int*) DPTX_PN_SWAP_reg)=data)
#define get_DPTX_PN_SWAP_reg   (*((volatile unsigned int*) DPTX_PN_SWAP_reg))
#define DPTX_PN_SWAP_inst_adr                                                        "0x00A4"
#define DPTX_PN_SWAP_inst                                                            0x00A4
#define DPTX_PN_SWAP_reg_dptx_beacon30_shift                                         (4)
#define DPTX_PN_SWAP_reg_dptx_beacon30_mask                                          (0x000000F0)
#define DPTX_PN_SWAP_reg_dptx_beacon30(data)                                         (0x000000F0&((data)<<4))
#define DPTX_PN_SWAP_reg_dptx_beacon30_src(data)                                     ((0x000000F0&(data))>>4)
#define DPTX_PN_SWAP_get_reg_dptx_beacon30(data)                                     ((0x000000F0&(data))>>4)
#define DPTX_PN_SWAP_dptx_pn_swap30_shift                                            (0)
#define DPTX_PN_SWAP_dptx_pn_swap30_mask                                             (0x0000000F)
#define DPTX_PN_SWAP_dptx_pn_swap30(data)                                            (0x0000000F&((data)<<0))
#define DPTX_PN_SWAP_dptx_pn_swap30_src(data)                                        ((0x0000000F&(data))>>0)
#define DPTX_PN_SWAP_get_dptx_pn_swap30(data)                                        ((0x0000000F&(data))>>0)


#define DPTX_SFIFO_CTRL0                                                             0x9803D69C
#define DPTX_SFIFO_CTRL0_reg_addr                                                    "0x9803D69C"
#define DPTX_SFIFO_CTRL0_reg                                                         0x9803D69C
#define set_DPTX_SFIFO_CTRL0_reg(data)   (*((volatile unsigned int*) DPTX_SFIFO_CTRL0_reg)=data)
#define get_DPTX_SFIFO_CTRL0_reg   (*((volatile unsigned int*) DPTX_SFIFO_CTRL0_reg))
#define DPTX_SFIFO_CTRL0_inst_adr                                                    "0x00A7"
#define DPTX_SFIFO_CTRL0_inst                                                        0x00A7
#define DPTX_SFIFO_CTRL0_tx_en_shift                                                 (7)
#define DPTX_SFIFO_CTRL0_tx_en_mask                                                  (0x00000080)
#define DPTX_SFIFO_CTRL0_tx_en(data)                                                 (0x00000080&((data)<<7))
#define DPTX_SFIFO_CTRL0_tx_en_src(data)                                             ((0x00000080&(data))>>7)
#define DPTX_SFIFO_CTRL0_get_tx_en(data)                                             ((0x00000080&(data))>>7)
#define DPTX_SFIFO_CTRL0_rate_mode_shift                                             (5)
#define DPTX_SFIFO_CTRL0_rate_mode_mask                                              (0x00000060)
#define DPTX_SFIFO_CTRL0_rate_mode(data)                                             (0x00000060&((data)<<5))
#define DPTX_SFIFO_CTRL0_rate_mode_src(data)                                         ((0x00000060&(data))>>5)
#define DPTX_SFIFO_CTRL0_get_rate_mode(data)                                         ((0x00000060&(data))>>5)
#define DPTX_SFIFO_CTRL0_fifo_in_flip_shift                                          (4)
#define DPTX_SFIFO_CTRL0_fifo_in_flip_mask                                           (0x00000010)
#define DPTX_SFIFO_CTRL0_fifo_in_flip(data)                                          (0x00000010&((data)<<4))
#define DPTX_SFIFO_CTRL0_fifo_in_flip_src(data)                                      ((0x00000010&(data))>>4)
#define DPTX_SFIFO_CTRL0_get_fifo_in_flip(data)                                      ((0x00000010&(data))>>4)
#define DPTX_SFIFO_CTRL0_Reserved_shift                                              (2)
#define DPTX_SFIFO_CTRL0_Reserved_mask                                               (0x0000000C)
#define DPTX_SFIFO_CTRL0_Reserved(data)                                              (0x0000000C&((data)<<2))
#define DPTX_SFIFO_CTRL0_Reserved_src(data)                                          ((0x0000000C&(data))>>2)
#define DPTX_SFIFO_CTRL0_get_Reserved(data)                                          ((0x0000000C&(data))>>2)
#define DPTX_SFIFO_CTRL0_wovflow_shift                                               (1)
#define DPTX_SFIFO_CTRL0_wovflow_mask                                                (0x00000002)
#define DPTX_SFIFO_CTRL0_wovflow(data)                                               (0x00000002&((data)<<1))
#define DPTX_SFIFO_CTRL0_wovflow_src(data)                                           ((0x00000002&(data))>>1)
#define DPTX_SFIFO_CTRL0_get_wovflow(data)                                           ((0x00000002&(data))>>1)
#define DPTX_SFIFO_CTRL0_rudflow_shift                                               (0)
#define DPTX_SFIFO_CTRL0_rudflow_mask                                                (0x00000001)
#define DPTX_SFIFO_CTRL0_rudflow(data)                                               (0x00000001&((data)<<0))
#define DPTX_SFIFO_CTRL0_rudflow_src(data)                                           ((0x00000001&(data))>>0)
#define DPTX_SFIFO_CTRL0_get_rudflow(data)                                           ((0x00000001&(data))>>0)


#define DPTX_SFIFO_CTRL1                                                             0x9803D6A0
#define DPTX_SFIFO_CTRL1_reg_addr                                                    "0x9803D6A0"
#define DPTX_SFIFO_CTRL1_reg                                                         0x9803D6A0
#define set_DPTX_SFIFO_CTRL1_reg(data)   (*((volatile unsigned int*) DPTX_SFIFO_CTRL1_reg)=data)
#define get_DPTX_SFIFO_CTRL1_reg   (*((volatile unsigned int*) DPTX_SFIFO_CTRL1_reg))
#define DPTX_SFIFO_CTRL1_inst_adr                                                    "0x00A8"
#define DPTX_SFIFO_CTRL1_inst                                                        0x00A8
#define DPTX_SFIFO_CTRL1_water_level_shift                                           (5)
#define DPTX_SFIFO_CTRL1_water_level_mask                                            (0x000000E0)
#define DPTX_SFIFO_CTRL1_water_level(data)                                           (0x000000E0&((data)<<5))
#define DPTX_SFIFO_CTRL1_water_level_src(data)                                       ((0x000000E0&(data))>>5)
#define DPTX_SFIFO_CTRL1_get_water_level(data)                                       ((0x000000E0&(data))>>5)
#define DPTX_SFIFO_CTRL1_Reserved_shift                                              (3)
#define DPTX_SFIFO_CTRL1_Reserved_mask                                               (0x00000018)
#define DPTX_SFIFO_CTRL1_Reserved(data)                                              (0x00000018&((data)<<3))
#define DPTX_SFIFO_CTRL1_Reserved_src(data)                                          ((0x00000018&(data))>>3)
#define DPTX_SFIFO_CTRL1_get_Reserved(data)                                          ((0x00000018&(data))>>3)
#define DPTX_SFIFO_CTRL1_rd_start_pos_shift                                          (0)
#define DPTX_SFIFO_CTRL1_rd_start_pos_mask                                           (0x00000007)
#define DPTX_SFIFO_CTRL1_rd_start_pos(data)                                          (0x00000007&((data)<<0))
#define DPTX_SFIFO_CTRL1_rd_start_pos_src(data)                                      ((0x00000007&(data))>>0)
#define DPTX_SFIFO_CTRL1_get_rd_start_pos(data)                                      ((0x00000007&(data))>>0)


#define DPTX_SFIFO_LANE_SWAP0                                                        0x9803D6A4
#define DPTX_SFIFO_LANE_SWAP0_reg_addr                                               "0x9803D6A4"
#define DPTX_SFIFO_LANE_SWAP0_reg                                                    0x9803D6A4
#define set_DPTX_SFIFO_LANE_SWAP0_reg(data)   (*((volatile unsigned int*) DPTX_SFIFO_LANE_SWAP0_reg)=data)
#define get_DPTX_SFIFO_LANE_SWAP0_reg   (*((volatile unsigned int*) DPTX_SFIFO_LANE_SWAP0_reg))
#define DPTX_SFIFO_LANE_SWAP0_inst_adr                                               "0x00A9"
#define DPTX_SFIFO_LANE_SWAP0_inst                                                   0x00A9
#define DPTX_SFIFO_LANE_SWAP0_fifo_source_sel_shift                                  (7)
#define DPTX_SFIFO_LANE_SWAP0_fifo_source_sel_mask                                   (0x00000080)
#define DPTX_SFIFO_LANE_SWAP0_fifo_source_sel(data)                                  (0x00000080&((data)<<7))
#define DPTX_SFIFO_LANE_SWAP0_fifo_source_sel_src(data)                              ((0x00000080&(data))>>7)
#define DPTX_SFIFO_LANE_SWAP0_get_fifo_source_sel(data)                              ((0x00000080&(data))>>7)
#define DPTX_SFIFO_LANE_SWAP0_Dummy_shift                                            (0)
#define DPTX_SFIFO_LANE_SWAP0_Dummy_mask                                             (0x0000007F)
#define DPTX_SFIFO_LANE_SWAP0_Dummy(data)                                            (0x0000007F&((data)<<0))
#define DPTX_SFIFO_LANE_SWAP0_Dummy_src(data)                                        ((0x0000007F&(data))>>0)
#define DPTX_SFIFO_LANE_SWAP0_get_Dummy(data)                                        ((0x0000007F&(data))>>0)


#define DPTX_SFIFO_LANE_SWAP1                                                        0x9803D6A8
#define DPTX_SFIFO_LANE_SWAP1_reg_addr                                               "0x9803D6A8"
#define DPTX_SFIFO_LANE_SWAP1_reg                                                    0x9803D6A8
#define set_DPTX_SFIFO_LANE_SWAP1_reg(data)   (*((volatile unsigned int*) DPTX_SFIFO_LANE_SWAP1_reg)=data)
#define get_DPTX_SFIFO_LANE_SWAP1_reg   (*((volatile unsigned int*) DPTX_SFIFO_LANE_SWAP1_reg))
#define DPTX_SFIFO_LANE_SWAP1_inst_adr                                               "0x00AA"
#define DPTX_SFIFO_LANE_SWAP1_inst                                                   0x00AA
#define DPTX_SFIFO_LANE_SWAP1_lane0_source_shift                                     (6)
#define DPTX_SFIFO_LANE_SWAP1_lane0_source_mask                                      (0x000000C0)
#define DPTX_SFIFO_LANE_SWAP1_lane0_source(data)                                     (0x000000C0&((data)<<6))
#define DPTX_SFIFO_LANE_SWAP1_lane0_source_src(data)                                 ((0x000000C0&(data))>>6)
#define DPTX_SFIFO_LANE_SWAP1_get_lane0_source(data)                                 ((0x000000C0&(data))>>6)
#define DPTX_SFIFO_LANE_SWAP1_lane1_source_shift                                     (4)
#define DPTX_SFIFO_LANE_SWAP1_lane1_source_mask                                      (0x00000030)
#define DPTX_SFIFO_LANE_SWAP1_lane1_source(data)                                     (0x00000030&((data)<<4))
#define DPTX_SFIFO_LANE_SWAP1_lane1_source_src(data)                                 ((0x00000030&(data))>>4)
#define DPTX_SFIFO_LANE_SWAP1_get_lane1_source(data)                                 ((0x00000030&(data))>>4)
#define DPTX_SFIFO_LANE_SWAP1_lane2_source_shift                                     (2)
#define DPTX_SFIFO_LANE_SWAP1_lane2_source_mask                                      (0x0000000C)
#define DPTX_SFIFO_LANE_SWAP1_lane2_source(data)                                     (0x0000000C&((data)<<2))
#define DPTX_SFIFO_LANE_SWAP1_lane2_source_src(data)                                 ((0x0000000C&(data))>>2)
#define DPTX_SFIFO_LANE_SWAP1_get_lane2_source(data)                                 ((0x0000000C&(data))>>2)
#define DPTX_SFIFO_LANE_SWAP1_lane3_source_shift                                     (0)
#define DPTX_SFIFO_LANE_SWAP1_lane3_source_mask                                      (0x00000003)
#define DPTX_SFIFO_LANE_SWAP1_lane3_source(data)                                     (0x00000003&((data)<<0))
#define DPTX_SFIFO_LANE_SWAP1_lane3_source_src(data)                                 ((0x00000003&(data))>>0)
#define DPTX_SFIFO_LANE_SWAP1_get_lane3_source(data)                                 ((0x00000003&(data))>>0)


#define DPTX_SFIFO_INT_EN                                                            0x9803D6AC
#define DPTX_SFIFO_INT_EN_reg_addr                                                   "0x9803D6AC"
#define DPTX_SFIFO_INT_EN_reg                                                        0x9803D6AC
#define set_DPTX_SFIFO_INT_EN_reg(data)   (*((volatile unsigned int*) DPTX_SFIFO_INT_EN_reg)=data)
#define get_DPTX_SFIFO_INT_EN_reg   (*((volatile unsigned int*) DPTX_SFIFO_INT_EN_reg))
#define DPTX_SFIFO_INT_EN_inst_adr                                                   "0x00AB"
#define DPTX_SFIFO_INT_EN_inst                                                       0x00AB
#define DPTX_SFIFO_INT_EN_v2a_sel_shift                                              (7)
#define DPTX_SFIFO_INT_EN_v2a_sel_mask                                               (0x00000080)
#define DPTX_SFIFO_INT_EN_v2a_sel(data)                                              (0x00000080&((data)<<7))
#define DPTX_SFIFO_INT_EN_v2a_sel_src(data)                                          ((0x00000080&(data))>>7)
#define DPTX_SFIFO_INT_EN_get_v2a_sel(data)                                          ((0x00000080&(data))>>7)
#define DPTX_SFIFO_INT_EN_v2a_val_shift                                              (3)
#define DPTX_SFIFO_INT_EN_v2a_val_mask                                               (0x00000078)
#define DPTX_SFIFO_INT_EN_v2a_val(data)                                              (0x00000078&((data)<<3))
#define DPTX_SFIFO_INT_EN_v2a_val_src(data)                                          ((0x00000078&(data))>>3)
#define DPTX_SFIFO_INT_EN_get_v2a_val(data)                                          ((0x00000078&(data))>>3)
#define DPTX_SFIFO_INT_EN_Reserved_shift                                             (0)
#define DPTX_SFIFO_INT_EN_Reserved_mask                                              (0x00000007)
#define DPTX_SFIFO_INT_EN_Reserved(data)                                             (0x00000007&((data)<<0))
#define DPTX_SFIFO_INT_EN_Reserved_src(data)                                         ((0x00000007&(data))>>0)
#define DPTX_SFIFO_INT_EN_get_Reserved(data)                                         ((0x00000007&(data))>>0)


#define SEC_FUNCTION_CTRL                                                            0x9803D400
#define SEC_FUNCTION_CTRL_reg_addr                                                   "0x9803D400"
#define SEC_FUNCTION_CTRL_reg                                                        0x9803D400
#define set_SEC_FUNCTION_CTRL_reg(data)   (*((volatile unsigned int*) SEC_FUNCTION_CTRL_reg)=data)
#define get_SEC_FUNCTION_CTRL_reg   (*((volatile unsigned int*) SEC_FUNCTION_CTRL_reg))
#define SEC_FUNCTION_CTRL_inst_adr                                                   "0x0000"
#define SEC_FUNCTION_CTRL_inst                                                       0x0000
#define SEC_FUNCTION_CTRL_Reserved_shift                                             (6)
#define SEC_FUNCTION_CTRL_Reserved_mask                                              (0x000000C0)
#define SEC_FUNCTION_CTRL_Reserved(data)                                             (0x000000C0&((data)<<6))
#define SEC_FUNCTION_CTRL_Reserved_src(data)                                         ((0x000000C0&(data))>>6)
#define SEC_FUNCTION_CTRL_get_Reserved(data)                                         ((0x000000C0&(data))>>6)
#define SEC_FUNCTION_CTRL_infoframe_mpeg_en_shift                                    (5)
#define SEC_FUNCTION_CTRL_infoframe_mpeg_en_mask                                     (0x00000020)
#define SEC_FUNCTION_CTRL_infoframe_mpeg_en(data)                                    (0x00000020&((data)<<5))
#define SEC_FUNCTION_CTRL_infoframe_mpeg_en_src(data)                                ((0x00000020&(data))>>5)
#define SEC_FUNCTION_CTRL_get_infoframe_mpeg_en(data)                                ((0x00000020&(data))>>5)
#define SEC_FUNCTION_CTRL_infoframe_avi_en_shift                                     (4)
#define SEC_FUNCTION_CTRL_infoframe_avi_en_mask                                      (0x00000010)
#define SEC_FUNCTION_CTRL_infoframe_avi_en(data)                                     (0x00000010&((data)<<4))
#define SEC_FUNCTION_CTRL_infoframe_avi_en_src(data)                                 ((0x00000010&(data))>>4)
#define SEC_FUNCTION_CTRL_get_infoframe_avi_en(data)                                 ((0x00000010&(data))>>4)
#define SEC_FUNCTION_CTRL_infoframe_audio_en_shift                                   (3)
#define SEC_FUNCTION_CTRL_infoframe_audio_en_mask                                    (0x00000008)
#define SEC_FUNCTION_CTRL_infoframe_audio_en(data)                                   (0x00000008&((data)<<3))
#define SEC_FUNCTION_CTRL_infoframe_audio_en_src(data)                               ((0x00000008&(data))>>3)
#define SEC_FUNCTION_CTRL_get_infoframe_audio_en(data)                               ((0x00000008&(data))>>3)
#define SEC_FUNCTION_CTRL_psr_en_shift                                               (2)
#define SEC_FUNCTION_CTRL_psr_en_mask                                                (0x00000004)
#define SEC_FUNCTION_CTRL_psr_en(data)                                               (0x00000004&((data)<<2))
#define SEC_FUNCTION_CTRL_psr_en_src(data)                                           ((0x00000004&(data))>>2)
#define SEC_FUNCTION_CTRL_get_psr_en(data)                                           ((0x00000004&(data))>>2)
#define SEC_FUNCTION_CTRL_audio_timestamp_en_shift                                   (1)
#define SEC_FUNCTION_CTRL_audio_timestamp_en_mask                                    (0x00000002)
#define SEC_FUNCTION_CTRL_audio_timestamp_en(data)                                   (0x00000002&((data)<<1))
#define SEC_FUNCTION_CTRL_audio_timestamp_en_src(data)                               ((0x00000002&(data))>>1)
#define SEC_FUNCTION_CTRL_get_audio_timestamp_en(data)                               ((0x00000002&(data))>>1)
#define SEC_FUNCTION_CTRL_audio_en_shift                                             (0)
#define SEC_FUNCTION_CTRL_audio_en_mask                                              (0x00000001)
#define SEC_FUNCTION_CTRL_audio_en(data)                                             (0x00000001&((data)<<0))
#define SEC_FUNCTION_CTRL_audio_en_src(data)                                         ((0x00000001&(data))>>0)
#define SEC_FUNCTION_CTRL_get_audio_en(data)                                         ((0x00000001&(data))>>0)


#define SEC_RESERVED_0                                                               0x9803D404
#define SEC_RESERVED_0_reg_addr                                                      "0x9803D404"
#define SEC_RESERVED_0_reg                                                           0x9803D404
#define set_SEC_RESERVED_0_reg(data)   (*((volatile unsigned int*) SEC_RESERVED_0_reg)=data)
#define get_SEC_RESERVED_0_reg   (*((volatile unsigned int*) SEC_RESERVED_0_reg))
#define SEC_RESERVED_0_inst_adr                                                      "0x0001"
#define SEC_RESERVED_0_inst                                                          0x0001
#define SEC_RESERVED_0_Reserved_shift                                                (1)
#define SEC_RESERVED_0_Reserved_mask                                                 (0x000000FE)
#define SEC_RESERVED_0_Reserved(data)                                                (0x000000FE&((data)<<1))
#define SEC_RESERVED_0_Reserved_src(data)                                            ((0x000000FE&(data))>>1)
#define SEC_RESERVED_0_get_Reserved(data)                                            ((0x000000FE&(data))>>1)
#define SEC_RESERVED_0_strm_attr_errc_en_shift                                       (0)
#define SEC_RESERVED_0_strm_attr_errc_en_mask                                        (0x00000001)
#define SEC_RESERVED_0_strm_attr_errc_en(data)                                       (0x00000001&((data)<<0))
#define SEC_RESERVED_0_strm_attr_errc_en_src(data)                                   ((0x00000001&(data))>>0)
#define SEC_RESERVED_0_get_strm_attr_errc_en(data)                                   ((0x00000001&(data))>>0)


#define SEC_DBUF_CTRL                                                                0x9803D408
#define SEC_DBUF_CTRL_reg_addr                                                       "0x9803D408"
#define SEC_DBUF_CTRL_reg                                                            0x9803D408
#define set_SEC_DBUF_CTRL_reg(data)   (*((volatile unsigned int*) SEC_DBUF_CTRL_reg)=data)
#define get_SEC_DBUF_CTRL_reg   (*((volatile unsigned int*) SEC_DBUF_CTRL_reg))
#define SEC_DBUF_CTRL_inst_adr                                                       "0x0002"
#define SEC_DBUF_CTRL_inst                                                           0x0002
#define SEC_DBUF_CTRL_Reserved_shift                                                 (2)
#define SEC_DBUF_CTRL_Reserved_mask                                                  (0x000000FC)
#define SEC_DBUF_CTRL_Reserved(data)                                                 (0x000000FC&((data)<<2))
#define SEC_DBUF_CTRL_Reserved_src(data)                                             ((0x000000FC&(data))>>2)
#define SEC_DBUF_CTRL_get_Reserved(data)                                             ((0x000000FC&(data))>>2)
#define SEC_DBUF_CTRL_sec_db_vblank_shift                                            (1)
#define SEC_DBUF_CTRL_sec_db_vblank_mask                                             (0x00000002)
#define SEC_DBUF_CTRL_sec_db_vblank(data)                                            (0x00000002&((data)<<1))
#define SEC_DBUF_CTRL_sec_db_vblank_src(data)                                        ((0x00000002&(data))>>1)
#define SEC_DBUF_CTRL_get_sec_db_vblank(data)                                        ((0x00000002&(data))>>1)
#define SEC_DBUF_CTRL_sec_db_shift                                                   (0)
#define SEC_DBUF_CTRL_sec_db_mask                                                    (0x00000001)
#define SEC_DBUF_CTRL_sec_db(data)                                                   (0x00000001&((data)<<0))
#define SEC_DBUF_CTRL_sec_db_src(data)                                               ((0x00000001&(data))>>0)
#define SEC_DBUF_CTRL_get_sec_db(data)                                               ((0x00000001&(data))>>0)


#define SEC_DEBUG                                                                    0x9803D40C
#define SEC_DEBUG_reg_addr                                                           "0x9803D40C"
#define SEC_DEBUG_reg                                                                0x9803D40C
#define set_SEC_DEBUG_reg(data)   (*((volatile unsigned int*) SEC_DEBUG_reg)=data)
#define get_SEC_DEBUG_reg   (*((volatile unsigned int*) SEC_DEBUG_reg))
#define SEC_DEBUG_inst_adr                                                           "0x0003"
#define SEC_DEBUG_inst                                                               0x0003
#define SEC_DEBUG_Reserved0_shift                                                     (7)
#define SEC_DEBUG_Reserved0_mask                                                      (0x00000080)
#define SEC_DEBUG_Reserved0(data)                                                     (0x00000080&((data)<<7))
#define SEC_DEBUG_Reserved0_src(data)                                                 ((0x00000080&(data))>>7)
#define SEC_DEBUG_get_Reserved0(data)                                                 ((0x00000080&(data))>>7)
#define SEC_DEBUG_sec_lfifo_ctrl_debug_sel_shift                                     (5)
#define SEC_DEBUG_sec_lfifo_ctrl_debug_sel_mask                                      (0x00000060)
#define SEC_DEBUG_sec_lfifo_ctrl_debug_sel(data)                                     (0x00000060&((data)<<5))
#define SEC_DEBUG_sec_lfifo_ctrl_debug_sel_src(data)                                 ((0x00000060&(data))>>5)
#define SEC_DEBUG_get_sec_lfifo_ctrl_debug_sel(data)                                 ((0x00000060&(data))>>5)
#define SEC_DEBUG_bs_9th_occur_shift                                                 (4)
#define SEC_DEBUG_bs_9th_occur_mask                                                  (0x00000010)
#define SEC_DEBUG_bs_9th_occur(data)                                                 (0x00000010&((data)<<4))
#define SEC_DEBUG_bs_9th_occur_src(data)                                             ((0x00000010&(data))>>4)
#define SEC_DEBUG_get_bs_9th_occur(data)                                             ((0x00000010&(data))>>4)
#define SEC_DEBUG_Reserved1_shift                                                     (3)
#define SEC_DEBUG_Reserved1_mask                                                      (0x00000008)
#define SEC_DEBUG_Reserved1(data)                                                     (0x00000008&((data)<<3))
#define SEC_DEBUG_Reserved_src1(data)                                                 ((0x00000008&(data))>>3)
#define SEC_DEBUG_get_Reserved1(data)                                                 ((0x00000008&(data))>>3)
#define SEC_DEBUG_sec_debug_sel_shift                                                (0)
#define SEC_DEBUG_sec_debug_sel_mask                                                 (0x00000007)
#define SEC_DEBUG_sec_debug_sel(data)                                                (0x00000007&((data)<<0))
#define SEC_DEBUG_sec_debug_sel_src(data)                                            ((0x00000007&(data))>>0)
#define SEC_DEBUG_get_sec_debug_sel(data)                                            ((0x00000007&(data))>>0)


#define SEC_PSR_DB0                                                                  0x9803D410
#define SEC_PSR_DB0_reg_addr                                                         "0x9803D410"
#define SEC_PSR_DB0_reg                                                              0x9803D410
#define set_SEC_PSR_DB0_reg(data)   (*((volatile unsigned int*) SEC_PSR_DB0_reg)=data)
#define get_SEC_PSR_DB0_reg   (*((volatile unsigned int*) SEC_PSR_DB0_reg))
#define SEC_PSR_DB0_inst_adr                                                         "0x0004"
#define SEC_PSR_DB0_inst                                                             0x0004
#define SEC_PSR_DB0_vsc_db0_shift                                                    (0)
#define SEC_PSR_DB0_vsc_db0_mask                                                     (0x000000FF)
#define SEC_PSR_DB0_vsc_db0(data)                                                    (0x000000FF&((data)<<0))
#define SEC_PSR_DB0_vsc_db0_src(data)                                                ((0x000000FF&(data))>>0)
#define SEC_PSR_DB0_get_vsc_db0(data)                                                ((0x000000FF&(data))>>0)


#define SEC_PSR_DB1                                                                  0x9803D414
#define SEC_PSR_DB1_reg_addr                                                         "0x9803D414"
#define SEC_PSR_DB1_reg                                                              0x9803D414
#define set_SEC_PSR_DB1_reg(data)   (*((volatile unsigned int*) SEC_PSR_DB1_reg)=data)
#define get_SEC_PSR_DB1_reg   (*((volatile unsigned int*) SEC_PSR_DB1_reg))
#define SEC_PSR_DB1_inst_adr                                                         "0x0005"
#define SEC_PSR_DB1_inst                                                             0x0005
#define SEC_PSR_DB1_vsc_db1_shift                                                    (0)
#define SEC_PSR_DB1_vsc_db1_mask                                                     (0x000000FF)
#define SEC_PSR_DB1_vsc_db1(data)                                                    (0x000000FF&((data)<<0))
#define SEC_PSR_DB1_vsc_db1_src(data)                                                ((0x000000FF&(data))>>0)
#define SEC_PSR_DB1_get_vsc_db1(data)                                                ((0x000000FF&(data))>>0)


#define SEC_PSR_DB2                                                                  0x9803D418
#define SEC_PSR_DB2_reg_addr                                                         "0x9803D418"
#define SEC_PSR_DB2_reg                                                              0x9803D418
#define set_SEC_PSR_DB2_reg(data)   (*((volatile unsigned int*) SEC_PSR_DB2_reg)=data)
#define get_SEC_PSR_DB2_reg   (*((volatile unsigned int*) SEC_PSR_DB2_reg))
#define SEC_PSR_DB2_inst_adr                                                         "0x0006"
#define SEC_PSR_DB2_inst                                                             0x0006
#define SEC_PSR_DB2_vsc_db2_shift                                                    (0)
#define SEC_PSR_DB2_vsc_db2_mask                                                     (0x000000FF)
#define SEC_PSR_DB2_vsc_db2(data)                                                    (0x000000FF&((data)<<0))
#define SEC_PSR_DB2_vsc_db2_src(data)                                                ((0x000000FF&(data))>>0)
#define SEC_PSR_DB2_get_vsc_db2(data)                                                ((0x000000FF&(data))>>0)


#define SEC_PSR_DB3                                                                  0x9803D41C
#define SEC_PSR_DB3_reg_addr                                                         "0x9803D41C"
#define SEC_PSR_DB3_reg                                                              0x9803D41C
#define set_SEC_PSR_DB3_reg(data)   (*((volatile unsigned int*) SEC_PSR_DB3_reg)=data)
#define get_SEC_PSR_DB3_reg   (*((volatile unsigned int*) SEC_PSR_DB3_reg))
#define SEC_PSR_DB3_inst_adr                                                         "0x0007"
#define SEC_PSR_DB3_inst                                                             0x0007
#define SEC_PSR_DB3_vsc_db3_shift                                                    (0)
#define SEC_PSR_DB3_vsc_db3_mask                                                     (0x000000FF)
#define SEC_PSR_DB3_vsc_db3(data)                                                    (0x000000FF&((data)<<0))
#define SEC_PSR_DB3_vsc_db3_src(data)                                                ((0x000000FF&(data))>>0)
#define SEC_PSR_DB3_get_vsc_db3(data)                                                ((0x000000FF&(data))>>0)


#define SEC_PSR_DB4                                                                  0x9803D420
#define SEC_PSR_DB4_reg_addr                                                         "0x9803D420"
#define SEC_PSR_DB4_reg                                                              0x9803D420
#define set_SEC_PSR_DB4_reg(data)   (*((volatile unsigned int*) SEC_PSR_DB4_reg)=data)
#define get_SEC_PSR_DB4_reg   (*((volatile unsigned int*) SEC_PSR_DB4_reg))
#define SEC_PSR_DB4_inst_adr                                                         "0x0008"
#define SEC_PSR_DB4_inst                                                             0x0008
#define SEC_PSR_DB4_vsc_db4_shift                                                    (0)
#define SEC_PSR_DB4_vsc_db4_mask                                                     (0x000000FF)
#define SEC_PSR_DB4_vsc_db4(data)                                                    (0x000000FF&((data)<<0))
#define SEC_PSR_DB4_vsc_db4_src(data)                                                ((0x000000FF&(data))>>0)
#define SEC_PSR_DB4_get_vsc_db4(data)                                                ((0x000000FF&(data))>>0)


#define SEC_PSR_DB5                                                                  0x9803D424
#define SEC_PSR_DB5_reg_addr                                                         "0x9803D424"
#define SEC_PSR_DB5_reg                                                              0x9803D424
#define set_SEC_PSR_DB5_reg(data)   (*((volatile unsigned int*) SEC_PSR_DB5_reg)=data)
#define get_SEC_PSR_DB5_reg   (*((volatile unsigned int*) SEC_PSR_DB5_reg))
#define SEC_PSR_DB5_inst_adr                                                         "0x0009"
#define SEC_PSR_DB5_inst                                                             0x0009
#define SEC_PSR_DB5_vsc_db5_shift                                                    (0)
#define SEC_PSR_DB5_vsc_db5_mask                                                     (0x000000FF)
#define SEC_PSR_DB5_vsc_db5(data)                                                    (0x000000FF&((data)<<0))
#define SEC_PSR_DB5_vsc_db5_src(data)                                                ((0x000000FF&(data))>>0)
#define SEC_PSR_DB5_get_vsc_db5(data)                                                ((0x000000FF&(data))>>0)


#define SEC_PSR_DB6                                                                  0x9803D428
#define SEC_PSR_DB6_reg_addr                                                         "0x9803D428"
#define SEC_PSR_DB6_reg                                                              0x9803D428
#define set_SEC_PSR_DB6_reg(data)   (*((volatile unsigned int*) SEC_PSR_DB6_reg)=data)
#define get_SEC_PSR_DB6_reg   (*((volatile unsigned int*) SEC_PSR_DB6_reg))
#define SEC_PSR_DB6_inst_adr                                                         "0x000A"
#define SEC_PSR_DB6_inst                                                             0x000A
#define SEC_PSR_DB6_vsc_db6_shift                                                    (0)
#define SEC_PSR_DB6_vsc_db6_mask                                                     (0x000000FF)
#define SEC_PSR_DB6_vsc_db6(data)                                                    (0x000000FF&((data)<<0))
#define SEC_PSR_DB6_vsc_db6_src(data)                                                ((0x000000FF&(data))>>0)
#define SEC_PSR_DB6_get_vsc_db6(data)                                                ((0x000000FF&(data))>>0)


#define SEC_PSR_DB7                                                                  0x9803D42C
#define SEC_PSR_DB7_reg_addr                                                         "0x9803D42C"
#define SEC_PSR_DB7_reg                                                              0x9803D42C
#define set_SEC_PSR_DB7_reg(data)   (*((volatile unsigned int*) SEC_PSR_DB7_reg)=data)
#define get_SEC_PSR_DB7_reg   (*((volatile unsigned int*) SEC_PSR_DB7_reg))
#define SEC_PSR_DB7_inst_adr                                                         "0x000B"
#define SEC_PSR_DB7_inst                                                             0x000B
#define SEC_PSR_DB7_vsc_db7_shift                                                    (0)
#define SEC_PSR_DB7_vsc_db7_mask                                                     (0x000000FF)
#define SEC_PSR_DB7_vsc_db7(data)                                                    (0x000000FF&((data)<<0))
#define SEC_PSR_DB7_vsc_db7_src(data)                                                ((0x000000FF&(data))>>0)
#define SEC_PSR_DB7_get_vsc_db7(data)                                                ((0x000000FF&(data))>>0)


#define SEC_PSR_DB8                                                                  0x9803D430
#define SEC_PSR_DB8_reg_addr                                                         "0x9803D430"
#define SEC_PSR_DB8_reg                                                              0x9803D430
#define set_SEC_PSR_DB8_reg(data)   (*((volatile unsigned int*) SEC_PSR_DB8_reg)=data)
#define get_SEC_PSR_DB8_reg   (*((volatile unsigned int*) SEC_PSR_DB8_reg))
#define SEC_PSR_DB8_inst_adr                                                         "0x000C"
#define SEC_PSR_DB8_inst                                                             0x000C
#define SEC_PSR_DB8_vsc_db8_shift                                                    (0)
#define SEC_PSR_DB8_vsc_db8_mask                                                     (0x000000FF)
#define SEC_PSR_DB8_vsc_db8(data)                                                    (0x000000FF&((data)<<0))
#define SEC_PSR_DB8_vsc_db8_src(data)                                                ((0x000000FF&(data))>>0)
#define SEC_PSR_DB8_get_vsc_db8(data)                                                ((0x000000FF&(data))>>0)


#define SEC_PSR_DB9                                                                  0x9803D434
#define SEC_PSR_DB9_reg_addr                                                         "0x9803D434"
#define SEC_PSR_DB9_reg                                                              0x9803D434
#define set_SEC_PSR_DB9_reg(data)   (*((volatile unsigned int*) SEC_PSR_DB9_reg)=data)
#define get_SEC_PSR_DB9_reg   (*((volatile unsigned int*) SEC_PSR_DB9_reg))
#define SEC_PSR_DB9_inst_adr                                                         "0x000D"
#define SEC_PSR_DB9_inst                                                             0x000D
#define SEC_PSR_DB9_vsc_db9_shift                                                    (0)
#define SEC_PSR_DB9_vsc_db9_mask                                                     (0x000000FF)
#define SEC_PSR_DB9_vsc_db9(data)                                                    (0x000000FF&((data)<<0))
#define SEC_PSR_DB9_vsc_db9_src(data)                                                ((0x000000FF&(data))>>0)
#define SEC_PSR_DB9_get_vsc_db9(data)                                                ((0x000000FF&(data))>>0)


#define SEC_PSR_DB10                                                                 0x9803D438
#define SEC_PSR_DB10_reg_addr                                                        "0x9803D438"
#define SEC_PSR_DB10_reg                                                             0x9803D438
#define set_SEC_PSR_DB10_reg(data)   (*((volatile unsigned int*) SEC_PSR_DB10_reg)=data)
#define get_SEC_PSR_DB10_reg   (*((volatile unsigned int*) SEC_PSR_DB10_reg))
#define SEC_PSR_DB10_inst_adr                                                        "0x000E"
#define SEC_PSR_DB10_inst                                                            0x000E
#define SEC_PSR_DB10_vsc_db10_shift                                                  (0)
#define SEC_PSR_DB10_vsc_db10_mask                                                   (0x000000FF)
#define SEC_PSR_DB10_vsc_db10(data)                                                  (0x000000FF&((data)<<0))
#define SEC_PSR_DB10_vsc_db10_src(data)                                              ((0x000000FF&(data))>>0)
#define SEC_PSR_DB10_get_vsc_db10(data)                                              ((0x000000FF&(data))>>0)


#define SEC_PSR_DB11                                                                 0x9803D43C
#define SEC_PSR_DB11_reg_addr                                                        "0x9803D43C"
#define SEC_PSR_DB11_reg                                                             0x9803D43C
#define set_SEC_PSR_DB11_reg(data)   (*((volatile unsigned int*) SEC_PSR_DB11_reg)=data)
#define get_SEC_PSR_DB11_reg   (*((volatile unsigned int*) SEC_PSR_DB11_reg))
#define SEC_PSR_DB11_inst_adr                                                        "0x000F"
#define SEC_PSR_DB11_inst                                                            0x000F
#define SEC_PSR_DB11_vsc_db11_shift                                                  (0)
#define SEC_PSR_DB11_vsc_db11_mask                                                   (0x000000FF)
#define SEC_PSR_DB11_vsc_db11(data)                                                  (0x000000FF&((data)<<0))
#define SEC_PSR_DB11_vsc_db11_src(data)                                              ((0x000000FF&(data))>>0)
#define SEC_PSR_DB11_get_vsc_db11(data)                                              ((0x000000FF&(data))>>0)


#define SEC_PSR_DB12                                                                 0x9803D440
#define SEC_PSR_DB12_reg_addr                                                        "0x9803D440"
#define SEC_PSR_DB12_reg                                                             0x9803D440
#define set_SEC_PSR_DB12_reg(data)   (*((volatile unsigned int*) SEC_PSR_DB12_reg)=data)
#define get_SEC_PSR_DB12_reg   (*((volatile unsigned int*) SEC_PSR_DB12_reg))
#define SEC_PSR_DB12_inst_adr                                                        "0x0010"
#define SEC_PSR_DB12_inst                                                            0x0010
#define SEC_PSR_DB12_vsc_db12_shift                                                  (0)
#define SEC_PSR_DB12_vsc_db12_mask                                                   (0x000000FF)
#define SEC_PSR_DB12_vsc_db12(data)                                                  (0x000000FF&((data)<<0))
#define SEC_PSR_DB12_vsc_db12_src(data)                                              ((0x000000FF&(data))>>0)
#define SEC_PSR_DB12_get_vsc_db12(data)                                              ((0x000000FF&(data))>>0)


#define SEC_PSR_DB13                                                                 0x9803D444
#define SEC_PSR_DB13_reg_addr                                                        "0x9803D444"
#define SEC_PSR_DB13_reg                                                             0x9803D444
#define set_SEC_PSR_DB13_reg(data)   (*((volatile unsigned int*) SEC_PSR_DB13_reg)=data)
#define get_SEC_PSR_DB13_reg   (*((volatile unsigned int*) SEC_PSR_DB13_reg))
#define SEC_PSR_DB13_inst_adr                                                        "0x0011"
#define SEC_PSR_DB13_inst                                                            0x0011
#define SEC_PSR_DB13_vsc_db13_shift                                                  (0)
#define SEC_PSR_DB13_vsc_db13_mask                                                   (0x000000FF)
#define SEC_PSR_DB13_vsc_db13(data)                                                  (0x000000FF&((data)<<0))
#define SEC_PSR_DB13_vsc_db13_src(data)                                              ((0x000000FF&(data))>>0)
#define SEC_PSR_DB13_get_vsc_db13(data)                                              ((0x000000FF&(data))>>0)


#define SEC_PSR_DB14                                                                 0x9803D448
#define SEC_PSR_DB14_reg_addr                                                        "0x9803D448"
#define SEC_PSR_DB14_reg                                                             0x9803D448
#define set_SEC_PSR_DB14_reg(data)   (*((volatile unsigned int*) SEC_PSR_DB14_reg)=data)
#define get_SEC_PSR_DB14_reg   (*((volatile unsigned int*) SEC_PSR_DB14_reg))
#define SEC_PSR_DB14_inst_adr                                                        "0x0012"
#define SEC_PSR_DB14_inst                                                            0x0012
#define SEC_PSR_DB14_vsc_db14_shift                                                  (0)
#define SEC_PSR_DB14_vsc_db14_mask                                                   (0x000000FF)
#define SEC_PSR_DB14_vsc_db14(data)                                                  (0x000000FF&((data)<<0))
#define SEC_PSR_DB14_vsc_db14_src(data)                                              ((0x000000FF&(data))>>0)
#define SEC_PSR_DB14_get_vsc_db14(data)                                              ((0x000000FF&(data))>>0)


#define SEC_PSR_DB15                                                                 0x9803D44C
#define SEC_PSR_DB15_reg_addr                                                        "0x9803D44C"
#define SEC_PSR_DB15_reg                                                             0x9803D44C
#define set_SEC_PSR_DB15_reg(data)   (*((volatile unsigned int*) SEC_PSR_DB15_reg)=data)
#define get_SEC_PSR_DB15_reg   (*((volatile unsigned int*) SEC_PSR_DB15_reg))
#define SEC_PSR_DB15_inst_adr                                                        "0x0013"
#define SEC_PSR_DB15_inst                                                            0x0013
#define SEC_PSR_DB15_vsc_db15_shift                                                  (0)
#define SEC_PSR_DB15_vsc_db15_mask                                                   (0x000000FF)
#define SEC_PSR_DB15_vsc_db15(data)                                                  (0x000000FF&((data)<<0))
#define SEC_PSR_DB15_vsc_db15_src(data)                                              ((0x000000FF&(data))>>0)
#define SEC_PSR_DB15_get_vsc_db15(data)                                              ((0x000000FF&(data))>>0)


#define SEC_RESERVED_1                                                               0x9803D450
#define SEC_RESERVED_1_reg_addr                                                      "0x9803D450"
#define SEC_RESERVED_1_reg                                                           0x9803D450
#define set_SEC_RESERVED_1_reg(data)   (*((volatile unsigned int*) SEC_RESERVED_1_reg)=data)
#define get_SEC_RESERVED_1_reg   (*((volatile unsigned int*) SEC_RESERVED_1_reg))
#define SEC_RESERVED_1_inst_adr                                                      "0x0014"
#define SEC_RESERVED_1_inst                                                          0x0014
#define SEC_RESERVED_1_Reserved_shift                                                (0)
#define SEC_RESERVED_1_Reserved_mask                                                 (0x000000FF)
#define SEC_RESERVED_1_Reserved(data)                                                (0x000000FF&((data)<<0))
#define SEC_RESERVED_1_Reserved_src(data)                                            ((0x000000FF&(data))>>0)
#define SEC_RESERVED_1_get_Reserved(data)                                            ((0x000000FF&(data))>>0)


#define SEC_RESERVED_2                                                               0x9803D454
#define SEC_RESERVED_2_reg_addr                                                      "0x9803D454"
#define SEC_RESERVED_2_reg                                                           0x9803D454
#define set_SEC_RESERVED_2_reg(data)   (*((volatile unsigned int*) SEC_RESERVED_2_reg)=data)
#define get_SEC_RESERVED_2_reg   (*((volatile unsigned int*) SEC_RESERVED_2_reg))
#define SEC_RESERVED_2_inst_adr                                                      "0x0015"
#define SEC_RESERVED_2_inst                                                          0x0015
#define SEC_RESERVED_2_Reserved_shift                                                (0)
#define SEC_RESERVED_2_Reserved_mask                                                 (0x000000FF)
#define SEC_RESERVED_2_Reserved(data)                                                (0x000000FF&((data)<<0))
#define SEC_RESERVED_2_Reserved_src(data)                                            ((0x000000FF&(data))>>0)
#define SEC_RESERVED_2_get_Reserved(data)                                            ((0x000000FF&(data))>>0)


#define SEC_RESERVED_3                                                               0x9803D458
#define SEC_RESERVED_3_reg_addr                                                      "0x9803D458"
#define SEC_RESERVED_3_reg                                                           0x9803D458
#define set_SEC_RESERVED_3_reg(data)   (*((volatile unsigned int*) SEC_RESERVED_3_reg)=data)
#define get_SEC_RESERVED_3_reg   (*((volatile unsigned int*) SEC_RESERVED_3_reg))
#define SEC_RESERVED_3_inst_adr                                                      "0x0016"
#define SEC_RESERVED_3_inst                                                          0x0016
#define SEC_RESERVED_3_Reserved_shift                                                (0)
#define SEC_RESERVED_3_Reserved_mask                                                 (0x000000FF)
#define SEC_RESERVED_3_Reserved(data)                                                (0x000000FF&((data)<<0))
#define SEC_RESERVED_3_Reserved_src(data)                                            ((0x000000FF&(data))>>0)
#define SEC_RESERVED_3_get_Reserved(data)                                            ((0x000000FF&(data))>>0)


#define SEC_RESERVED_4                                                               0x9803D45C
#define SEC_RESERVED_4_reg_addr                                                      "0x9803D45C"
#define SEC_RESERVED_4_reg                                                           0x9803D45C
#define set_SEC_RESERVED_4_reg(data)   (*((volatile unsigned int*) SEC_RESERVED_4_reg)=data)
#define get_SEC_RESERVED_4_reg   (*((volatile unsigned int*) SEC_RESERVED_4_reg))
#define SEC_RESERVED_4_inst_adr                                                      "0x0017"
#define SEC_RESERVED_4_inst                                                          0x0017
#define SEC_RESERVED_4_Reserved_shift                                                (0)
#define SEC_RESERVED_4_Reserved_mask                                                 (0x000000FF)
#define SEC_RESERVED_4_Reserved(data)                                                (0x000000FF&((data)<<0))
#define SEC_RESERVED_4_Reserved_src(data)                                            ((0x000000FF&(data))>>0)
#define SEC_RESERVED_4_get_Reserved(data)                                            ((0x000000FF&(data))>>0)


#define AUD_FUNCTION_CTRL1                                                           0x9803D460
#define AUD_FUNCTION_CTRL1_reg_addr                                                  "0x9803D460"
#define AUD_FUNCTION_CTRL1_reg                                                       0x9803D460
#define set_AUD_FUNCTION_CTRL1_reg(data)   (*((volatile unsigned int*) AUD_FUNCTION_CTRL1_reg)=data)
#define get_AUD_FUNCTION_CTRL1_reg   (*((volatile unsigned int*) AUD_FUNCTION_CTRL1_reg))
#define AUD_FUNCTION_CTRL1_inst_adr                                                  "0x0018"
#define AUD_FUNCTION_CTRL1_inst                                                      0x0018
#define AUD_FUNCTION_CTRL1_audio_source_shift                                        (7)
#define AUD_FUNCTION_CTRL1_audio_source_mask                                         (0x00000080)
#define AUD_FUNCTION_CTRL1_audio_source(data)                                        (0x00000080&((data)<<7))
#define AUD_FUNCTION_CTRL1_audio_source_src(data)                                    ((0x00000080&(data))>>7)
#define AUD_FUNCTION_CTRL1_get_audio_source(data)                                    ((0x00000080&(data))>>7)
#define AUD_FUNCTION_CTRL1_eight_channel_layout_shift                                (6)
#define AUD_FUNCTION_CTRL1_eight_channel_layout_mask                                 (0x00000040)
#define AUD_FUNCTION_CTRL1_eight_channel_layout(data)                                (0x00000040&((data)<<6))
#define AUD_FUNCTION_CTRL1_eight_channel_layout_src(data)                            ((0x00000040&(data))>>6)
#define AUD_FUNCTION_CTRL1_get_eight_channel_layout(data)                            ((0x00000040&(data))>>6)
#define AUD_FUNCTION_CTRL1_sec_aud_ptr_errc_shift                                    (5)
#define AUD_FUNCTION_CTRL1_sec_aud_ptr_errc_mask                                     (0x00000020)
#define AUD_FUNCTION_CTRL1_sec_aud_ptr_errc(data)                                    (0x00000020&((data)<<5))
#define AUD_FUNCTION_CTRL1_sec_aud_ptr_errc_src(data)                                ((0x00000020&(data))>>5)
#define AUD_FUNCTION_CTRL1_get_sec_aud_ptr_errc(data)                                ((0x00000020&(data))>>5)
#define AUD_FUNCTION_CTRL1_audio_idle_send_shift                                     (4)
#define AUD_FUNCTION_CTRL1_audio_idle_send_mask                                      (0x00000010)
#define AUD_FUNCTION_CTRL1_audio_idle_send(data)                                     (0x00000010&((data)<<4))
#define AUD_FUNCTION_CTRL1_audio_idle_send_src(data)                                 ((0x00000010&(data))>>4)
#define AUD_FUNCTION_CTRL1_get_audio_idle_send(data)                                 ((0x00000010&(data))>>4)
#define AUD_FUNCTION_CTRL1_audio_sfifo_send_wl_shift                                 (0)
#define AUD_FUNCTION_CTRL1_audio_sfifo_send_wl_mask                                  (0x0000000F)
#define AUD_FUNCTION_CTRL1_audio_sfifo_send_wl(data)                                 (0x0000000F&((data)<<0))
#define AUD_FUNCTION_CTRL1_audio_sfifo_send_wl_src(data)                             ((0x0000000F&(data))>>0)
#define AUD_FUNCTION_CTRL1_get_audio_sfifo_send_wl(data)                             ((0x0000000F&(data))>>0)


#define AUD_PAYLOAD_B3                                                               0x9803D464
#define AUD_PAYLOAD_B3_reg_addr                                                      "0x9803D464"
#define AUD_PAYLOAD_B3_reg                                                           0x9803D464
#define set_AUD_PAYLOAD_B3_reg(data)   (*((volatile unsigned int*) AUD_PAYLOAD_B3_reg)=data)
#define get_AUD_PAYLOAD_B3_reg   (*((volatile unsigned int*) AUD_PAYLOAD_B3_reg))
#define AUD_PAYLOAD_B3_inst_adr                                                      "0x0019"
#define AUD_PAYLOAD_B3_inst                                                          0x0019
#define AUD_PAYLOAD_B3_aud_sp_shift                                                  (7)
#define AUD_PAYLOAD_B3_aud_sp_mask                                                   (0x00000080)
#define AUD_PAYLOAD_B3_aud_sp(data)                                                  (0x00000080&((data)<<7))
#define AUD_PAYLOAD_B3_aud_sp_src(data)                                              ((0x00000080&(data))>>7)
#define AUD_PAYLOAD_B3_get_aud_sp(data)                                              ((0x00000080&(data))>>7)
#define AUD_PAYLOAD_B3_aud_r_shift                                                   (6)
#define AUD_PAYLOAD_B3_aud_r_mask                                                    (0x00000040)
#define AUD_PAYLOAD_B3_aud_r(data)                                                   (0x00000040&((data)<<6))
#define AUD_PAYLOAD_B3_aud_r_src(data)                                               ((0x00000040&(data))>>6)
#define AUD_PAYLOAD_B3_get_aud_r(data)                                               ((0x00000040&(data))>>6)
#define AUD_PAYLOAD_B3_aud_pr_shift                                                  (4)
#define AUD_PAYLOAD_B3_aud_pr_mask                                                   (0x00000030)
#define AUD_PAYLOAD_B3_aud_pr(data)                                                  (0x00000030&((data)<<4))
#define AUD_PAYLOAD_B3_aud_pr_src(data)                                              ((0x00000030&(data))>>4)
#define AUD_PAYLOAD_B3_get_aud_pr(data)                                              ((0x00000030&(data))>>4)
#define AUD_PAYLOAD_B3_aud_p_shift                                                   (3)
#define AUD_PAYLOAD_B3_aud_p_mask                                                    (0x00000008)
#define AUD_PAYLOAD_B3_aud_p(data)                                                   (0x00000008&((data)<<3))
#define AUD_PAYLOAD_B3_aud_p_src(data)                                               ((0x00000008&(data))>>3)
#define AUD_PAYLOAD_B3_get_aud_p(data)                                               ((0x00000008&(data))>>3)
#define AUD_PAYLOAD_B3_aud_c_shift                                                   (2)
#define AUD_PAYLOAD_B3_aud_c_mask                                                    (0x00000004)
#define AUD_PAYLOAD_B3_aud_c(data)                                                   (0x00000004&((data)<<2))
#define AUD_PAYLOAD_B3_aud_c_src(data)                                               ((0x00000004&(data))>>2)
#define AUD_PAYLOAD_B3_get_aud_c(data)                                               ((0x00000004&(data))>>2)
#define AUD_PAYLOAD_B3_aud_u_shift                                                   (1)
#define AUD_PAYLOAD_B3_aud_u_mask                                                    (0x00000002)
#define AUD_PAYLOAD_B3_aud_u(data)                                                   (0x00000002&((data)<<1))
#define AUD_PAYLOAD_B3_aud_u_src(data)                                               ((0x00000002&(data))>>1)
#define AUD_PAYLOAD_B3_get_aud_u(data)                                               ((0x00000002&(data))>>1)
#define AUD_PAYLOAD_B3_aud_v_shift                                                   (0)
#define AUD_PAYLOAD_B3_aud_v_mask                                                    (0x00000001)
#define AUD_PAYLOAD_B3_aud_v(data)                                                   (0x00000001&((data)<<0))
#define AUD_PAYLOAD_B3_aud_v_src(data)                                               ((0x00000001&(data))>>0)
#define AUD_PAYLOAD_B3_get_aud_v(data)                                               ((0x00000001&(data))>>0)


#define DP_AUD_ID                                                                    0x9803D468
#define DP_AUD_ID_reg_addr                                                           "0x9803D468"
#define DP_AUD_ID_reg                                                                0x9803D468
#define set_DP_AUD_ID_reg(data)   (*((volatile unsigned int*) DP_AUD_ID_reg)=data)
#define get_DP_AUD_ID_reg   (*((volatile unsigned int*) DP_AUD_ID_reg))
#define DP_AUD_ID_inst_adr                                                           "0x001A"
#define DP_AUD_ID_inst                                                               0x001A
#define DP_AUD_ID_aud_pkt_id_shift                                                   (0)
#define DP_AUD_ID_aud_pkt_id_mask                                                    (0x000000FF)
#define DP_AUD_ID_aud_pkt_id(data)                                                   (0x000000FF&((data)<<0))
#define DP_AUD_ID_aud_pkt_id_src(data)                                               ((0x000000FF&(data))>>0)
#define DP_AUD_ID_get_aud_pkt_id(data)                                               ((0x000000FF&(data))>>0)


#define SEC_RESERVED_6                                                               0x9803D46C
#define SEC_RESERVED_6_reg_addr                                                      "0x9803D46C"
#define SEC_RESERVED_6_reg                                                           0x9803D46C
#define set_SEC_RESERVED_6_reg(data)   (*((volatile unsigned int*) SEC_RESERVED_6_reg)=data)
#define get_SEC_RESERVED_6_reg   (*((volatile unsigned int*) SEC_RESERVED_6_reg))
#define SEC_RESERVED_6_inst_adr                                                      "0x001B"
#define SEC_RESERVED_6_inst                                                          0x001B
#define SEC_RESERVED_6_Reserved_shift                                                (0)
#define SEC_RESERVED_6_Reserved_mask                                                 (0x000000FF)
#define SEC_RESERVED_6_Reserved(data)                                                (0x000000FF&((data)<<0))
#define SEC_RESERVED_6_Reserved_src(data)                                            ((0x000000FF&(data))>>0)
#define SEC_RESERVED_6_get_Reserved(data)                                            ((0x000000FF&(data))>>0)


#define AUD_FIFO_CTRL                                                                0x9803D470
#define AUD_FIFO_CTRL_reg_addr                                                       "0x9803D470"
#define AUD_FIFO_CTRL_reg                                                            0x9803D470
#define set_AUD_FIFO_CTRL_reg(data)   (*((volatile unsigned int*) AUD_FIFO_CTRL_reg)=data)
#define get_AUD_FIFO_CTRL_reg   (*((volatile unsigned int*) AUD_FIFO_CTRL_reg))
#define AUD_FIFO_CTRL_inst_adr                                                       "0x001C"
#define AUD_FIFO_CTRL_inst                                                           0x001C
#define AUD_FIFO_CTRL_aud_lfifo_of_shift                                             (7)
#define AUD_FIFO_CTRL_aud_lfifo_of_mask                                              (0x00000080)
#define AUD_FIFO_CTRL_aud_lfifo_of(data)                                             (0x00000080&((data)<<7))
#define AUD_FIFO_CTRL_aud_lfifo_of_src(data)                                         ((0x00000080&(data))>>7)
#define AUD_FIFO_CTRL_get_aud_lfifo_of(data)                                         ((0x00000080&(data))>>7)
#define AUD_FIFO_CTRL_max_lfifo_wl_clear_shift                                       (6)
#define AUD_FIFO_CTRL_max_lfifo_wl_clear_mask                                        (0x00000040)
#define AUD_FIFO_CTRL_max_lfifo_wl_clear(data)                                       (0x00000040&((data)<<6))
#define AUD_FIFO_CTRL_max_lfifo_wl_clear_src(data)                                   ((0x00000040&(data))>>6)
#define AUD_FIFO_CTRL_get_max_lfifo_wl_clear(data)                                   ((0x00000040&(data))>>6)
#define AUD_FIFO_CTRL_Reserved_shift                                                 (0)
#define AUD_FIFO_CTRL_Reserved_mask                                                  (0x0000003F)
#define AUD_FIFO_CTRL_Reserved(data)                                                 (0x0000003F&((data)<<0))
#define AUD_FIFO_CTRL_Reserved_src(data)                                             ((0x0000003F&(data))>>0)
#define AUD_FIFO_CTRL_get_Reserved(data)                                             ((0x0000003F&(data))>>0)


#define AUD_LFIFO_MAX_WL                                                             0x9803D474
#define AUD_LFIFO_MAX_WL_reg_addr                                                    "0x9803D474"
#define AUD_LFIFO_MAX_WL_reg                                                         0x9803D474
#define set_AUD_LFIFO_MAX_WL_reg(data)   (*((volatile unsigned int*) AUD_LFIFO_MAX_WL_reg)=data)
#define get_AUD_LFIFO_MAX_WL_reg   (*((volatile unsigned int*) AUD_LFIFO_MAX_WL_reg))
#define AUD_LFIFO_MAX_WL_inst_adr                                                    "0x001D"
#define AUD_LFIFO_MAX_WL_inst                                                        0x001D
#define AUD_LFIFO_MAX_WL_Reserved_shift                                              (7)
#define AUD_LFIFO_MAX_WL_Reserved_mask                                               (0x00000080)
#define AUD_LFIFO_MAX_WL_Reserved(data)                                              (0x00000080&((data)<<7))
#define AUD_LFIFO_MAX_WL_Reserved_src(data)                                          ((0x00000080&(data))>>7)
#define AUD_LFIFO_MAX_WL_get_Reserved(data)                                          ((0x00000080&(data))>>7)
#define AUD_LFIFO_MAX_WL_max_lfifo_wl_shift                                          (0)
#define AUD_LFIFO_MAX_WL_max_lfifo_wl_mask                                           (0x0000007F)
#define AUD_LFIFO_MAX_WL_max_lfifo_wl(data)                                          (0x0000007F&((data)<<0))
#define AUD_LFIFO_MAX_WL_max_lfifo_wl_src(data)                                      ((0x0000007F&(data))>>0)
#define AUD_LFIFO_MAX_WL_get_max_lfifo_wl(data)                                      ((0x0000007F&(data))>>0)


#define AUD_LFIFO_WL                                                                 0x9803D478
#define AUD_LFIFO_WL_reg_addr                                                        "0x9803D478"
#define AUD_LFIFO_WL_reg                                                             0x9803D478
#define set_AUD_LFIFO_WL_reg(data)   (*((volatile unsigned int*) AUD_LFIFO_WL_reg)=data)
#define get_AUD_LFIFO_WL_reg   (*((volatile unsigned int*) AUD_LFIFO_WL_reg))
#define AUD_LFIFO_WL_inst_adr                                                        "0x001E"
#define AUD_LFIFO_WL_inst                                                            0x001E
#define AUD_LFIFO_WL_Reserved_shift                                                  (7)
#define AUD_LFIFO_WL_Reserved_mask                                                   (0x00000080)
#define AUD_LFIFO_WL_Reserved(data)                                                  (0x00000080&((data)<<7))
#define AUD_LFIFO_WL_Reserved_src(data)                                              ((0x00000080&(data))>>7)
#define AUD_LFIFO_WL_get_Reserved(data)                                              ((0x00000080&(data))>>7)
#define AUD_LFIFO_WL_lfifo_wl_shift                                                  (0)
#define AUD_LFIFO_WL_lfifo_wl_mask                                                   (0x0000007F)
#define AUD_LFIFO_WL_lfifo_wl(data)                                                  (0x0000007F&((data)<<0))
#define AUD_LFIFO_WL_lfifo_wl_src(data)                                              ((0x0000007F&(data))>>0)
#define AUD_LFIFO_WL_get_lfifo_wl(data)                                              ((0x0000007F&(data))>>0)


#define AUD_INTERRUPT_CTRL                                                           0x9803D47C
#define AUD_INTERRUPT_CTRL_reg_addr                                                  "0x9803D47C"
#define AUD_INTERRUPT_CTRL_reg                                                       0x9803D47C
#define set_AUD_INTERRUPT_CTRL_reg(data)   (*((volatile unsigned int*) AUD_INTERRUPT_CTRL_reg)=data)
#define get_AUD_INTERRUPT_CTRL_reg   (*((volatile unsigned int*) AUD_INTERRUPT_CTRL_reg))
#define AUD_INTERRUPT_CTRL_inst_adr                                                  "0x001F"
#define AUD_INTERRUPT_CTRL_inst                                                      0x001F
#define AUD_INTERRUPT_CTRL_Reserved_shift                                            (1)
#define AUD_INTERRUPT_CTRL_Reserved_mask                                             (0x000000FE)
#define AUD_INTERRUPT_CTRL_Reserved(data)                                            (0x000000FE&((data)<<1))
#define AUD_INTERRUPT_CTRL_Reserved_src(data)                                        ((0x000000FE&(data))>>1)
#define AUD_INTERRUPT_CTRL_get_Reserved(data)                                        ((0x000000FE&(data))>>1)
#define AUD_INTERRUPT_CTRL_aud_lfifo_of_int_en_shift                                 (0)
#define AUD_INTERRUPT_CTRL_aud_lfifo_of_int_en_mask                                  (0x00000001)
#define AUD_INTERRUPT_CTRL_aud_lfifo_of_int_en(data)                                 (0x00000001&((data)<<0))
#define AUD_INTERRUPT_CTRL_aud_lfifo_of_int_en_src(data)                             ((0x00000001&(data))>>0)
#define AUD_INTERRUPT_CTRL_get_aud_lfifo_of_int_en(data)                             ((0x00000001&(data))>>0)


#define AUD_TS_MAUD_H                                                                0x9803D480
#define AUD_TS_MAUD_H_reg_addr                                                       "0x9803D480"
#define AUD_TS_MAUD_H_reg                                                            0x9803D480
#define set_AUD_TS_MAUD_H_reg(data)   (*((volatile unsigned int*) AUD_TS_MAUD_H_reg)=data)
#define get_AUD_TS_MAUD_H_reg   (*((volatile unsigned int*) AUD_TS_MAUD_H_reg))
#define AUD_TS_MAUD_H_inst_adr                                                       "0x0020"
#define AUD_TS_MAUD_H_inst                                                           0x0020
#define AUD_TS_MAUD_H_maud2316_shift                                                 (0)
#define AUD_TS_MAUD_H_maud2316_mask                                                  (0x000000FF)
#define AUD_TS_MAUD_H_maud2316(data)                                                 (0x000000FF&((data)<<0))
#define AUD_TS_MAUD_H_maud2316_src(data)                                             ((0x000000FF&(data))>>0)
#define AUD_TS_MAUD_H_get_maud2316(data)                                             ((0x000000FF&(data))>>0)


#define AUD_TS_MAUD_M                                                                0x9803D484
#define AUD_TS_MAUD_M_reg_addr                                                       "0x9803D484"
#define AUD_TS_MAUD_M_reg                                                            0x9803D484
#define set_AUD_TS_MAUD_M_reg(data)   (*((volatile unsigned int*) AUD_TS_MAUD_M_reg)=data)
#define get_AUD_TS_MAUD_M_reg   (*((volatile unsigned int*) AUD_TS_MAUD_M_reg))
#define AUD_TS_MAUD_M_inst_adr                                                       "0x0021"
#define AUD_TS_MAUD_M_inst                                                           0x0021
#define AUD_TS_MAUD_M_maud158_shift                                                  (0)
#define AUD_TS_MAUD_M_maud158_mask                                                   (0x000000FF)
#define AUD_TS_MAUD_M_maud158(data)                                                  (0x000000FF&((data)<<0))
#define AUD_TS_MAUD_M_maud158_src(data)                                              ((0x000000FF&(data))>>0)
#define AUD_TS_MAUD_M_get_maud158(data)                                              ((0x000000FF&(data))>>0)


#define AUD_TS_MAUD_L                                                                0x9803D488
#define AUD_TS_MAUD_L_reg_addr                                                       "0x9803D488"
#define AUD_TS_MAUD_L_reg                                                            0x9803D488
#define set_AUD_TS_MAUD_L_reg(data)   (*((volatile unsigned int*) AUD_TS_MAUD_L_reg)=data)
#define get_AUD_TS_MAUD_L_reg   (*((volatile unsigned int*) AUD_TS_MAUD_L_reg))
#define AUD_TS_MAUD_L_inst_adr                                                       "0x0022"
#define AUD_TS_MAUD_L_inst                                                           0x0022
#define AUD_TS_MAUD_L_maud70_shift                                                   (0)
#define AUD_TS_MAUD_L_maud70_mask                                                    (0x000000FF)
#define AUD_TS_MAUD_L_maud70(data)                                                   (0x000000FF&((data)<<0))
#define AUD_TS_MAUD_L_maud70_src(data)                                               ((0x000000FF&(data))>>0)
#define AUD_TS_MAUD_L_get_maud70(data)                                               ((0x000000FF&(data))>>0)


#define AUD_TS_NAUD_H                                                                0x9803D48C
#define AUD_TS_NAUD_H_reg_addr                                                       "0x9803D48C"
#define AUD_TS_NAUD_H_reg                                                            0x9803D48C
#define set_AUD_TS_NAUD_H_reg(data)   (*((volatile unsigned int*) AUD_TS_NAUD_H_reg)=data)
#define get_AUD_TS_NAUD_H_reg   (*((volatile unsigned int*) AUD_TS_NAUD_H_reg))
#define AUD_TS_NAUD_H_inst_adr                                                       "0x0023"
#define AUD_TS_NAUD_H_inst                                                           0x0023
#define AUD_TS_NAUD_H_naud2316_shift                                                 (0)
#define AUD_TS_NAUD_H_naud2316_mask                                                  (0x000000FF)
#define AUD_TS_NAUD_H_naud2316(data)                                                 (0x000000FF&((data)<<0))
#define AUD_TS_NAUD_H_naud2316_src(data)                                             ((0x000000FF&(data))>>0)
#define AUD_TS_NAUD_H_get_naud2316(data)                                             ((0x000000FF&(data))>>0)


#define AUD_TS_NAUD_M                                                                0x9803D490
#define AUD_TS_NAUD_M_reg_addr                                                       "0x9803D490"
#define AUD_TS_NAUD_M_reg                                                            0x9803D490
#define set_AUD_TS_NAUD_M_reg(data)   (*((volatile unsigned int*) AUD_TS_NAUD_M_reg)=data)
#define get_AUD_TS_NAUD_M_reg   (*((volatile unsigned int*) AUD_TS_NAUD_M_reg))
#define AUD_TS_NAUD_M_inst_adr                                                       "0x0024"
#define AUD_TS_NAUD_M_inst                                                           0x0024
#define AUD_TS_NAUD_M_naud158_shift                                                  (0)
#define AUD_TS_NAUD_M_naud158_mask                                                   (0x000000FF)
#define AUD_TS_NAUD_M_naud158(data)                                                  (0x000000FF&((data)<<0))
#define AUD_TS_NAUD_M_naud158_src(data)                                              ((0x000000FF&(data))>>0)
#define AUD_TS_NAUD_M_get_naud158(data)                                              ((0x000000FF&(data))>>0)


#define AUD_TS_NAUD_L                                                                0x9803D494
#define AUD_TS_NAUD_L_reg_addr                                                       "0x9803D494"
#define AUD_TS_NAUD_L_reg                                                            0x9803D494
#define set_AUD_TS_NAUD_L_reg(data)   (*((volatile unsigned int*) AUD_TS_NAUD_L_reg)=data)
#define get_AUD_TS_NAUD_L_reg   (*((volatile unsigned int*) AUD_TS_NAUD_L_reg))
#define AUD_TS_NAUD_L_inst_adr                                                       "0x0025"
#define AUD_TS_NAUD_L_inst                                                           0x0025
#define AUD_TS_NAUD_L_naud70_shift                                                   (0)
#define AUD_TS_NAUD_L_naud70_mask                                                    (0x000000FF)
#define AUD_TS_NAUD_L_naud70(data)                                                   (0x000000FF&((data)<<0))
#define AUD_TS_NAUD_L_naud70_src(data)                                               ((0x000000FF&(data))>>0)
#define AUD_TS_NAUD_L_get_naud70(data)                                               ((0x000000FF&(data))>>0)


#define SEC_INFO_AUD_DB0                                                             0x9803D498
#define SEC_INFO_AUD_DB0_reg_addr                                                    "0x9803D498"
#define SEC_INFO_AUD_DB0_reg                                                         0x9803D498
#define set_SEC_INFO_AUD_DB0_reg(data)   (*((volatile unsigned int*) SEC_INFO_AUD_DB0_reg)=data)
#define get_SEC_INFO_AUD_DB0_reg   (*((volatile unsigned int*) SEC_INFO_AUD_DB0_reg))
#define SEC_INFO_AUD_DB0_inst_adr                                                    "0x0026"
#define SEC_INFO_AUD_DB0_inst                                                        0x0026
#define SEC_INFO_AUD_DB0_info_audio_db0_shift                                        (0)
#define SEC_INFO_AUD_DB0_info_audio_db0_mask                                         (0x000000FF)
#define SEC_INFO_AUD_DB0_info_audio_db0(data)                                        (0x000000FF&((data)<<0))
#define SEC_INFO_AUD_DB0_info_audio_db0_src(data)                                    ((0x000000FF&(data))>>0)
#define SEC_INFO_AUD_DB0_get_info_audio_db0(data)                                    ((0x000000FF&(data))>>0)


#define SEC_INFO_AUD_DB1                                                             0x9803D49C
#define SEC_INFO_AUD_DB1_reg_addr                                                    "0x9803D49C"
#define SEC_INFO_AUD_DB1_reg                                                         0x9803D49C
#define set_SEC_INFO_AUD_DB1_reg(data)   (*((volatile unsigned int*) SEC_INFO_AUD_DB1_reg)=data)
#define get_SEC_INFO_AUD_DB1_reg   (*((volatile unsigned int*) SEC_INFO_AUD_DB1_reg))
#define SEC_INFO_AUD_DB1_inst_adr                                                    "0x0027"
#define SEC_INFO_AUD_DB1_inst                                                        0x0027
#define SEC_INFO_AUD_DB1_info_audio_db1_shift                                        (0)
#define SEC_INFO_AUD_DB1_info_audio_db1_mask                                         (0x000000FF)
#define SEC_INFO_AUD_DB1_info_audio_db1(data)                                        (0x000000FF&((data)<<0))
#define SEC_INFO_AUD_DB1_info_audio_db1_src(data)                                    ((0x000000FF&(data))>>0)
#define SEC_INFO_AUD_DB1_get_info_audio_db1(data)                                    ((0x000000FF&(data))>>0)


#define SEC_INFO_AUD_DB2                                                             0x9803D4A0
#define SEC_INFO_AUD_DB2_reg_addr                                                    "0x9803D4A0"
#define SEC_INFO_AUD_DB2_reg                                                         0x9803D4A0
#define set_SEC_INFO_AUD_DB2_reg(data)   (*((volatile unsigned int*) SEC_INFO_AUD_DB2_reg)=data)
#define get_SEC_INFO_AUD_DB2_reg   (*((volatile unsigned int*) SEC_INFO_AUD_DB2_reg))
#define SEC_INFO_AUD_DB2_inst_adr                                                    "0x0028"
#define SEC_INFO_AUD_DB2_inst                                                        0x0028
#define SEC_INFO_AUD_DB2_info_audio_db2_shift                                        (0)
#define SEC_INFO_AUD_DB2_info_audio_db2_mask                                         (0x000000FF)
#define SEC_INFO_AUD_DB2_info_audio_db2(data)                                        (0x000000FF&((data)<<0))
#define SEC_INFO_AUD_DB2_info_audio_db2_src(data)                                    ((0x000000FF&(data))>>0)
#define SEC_INFO_AUD_DB2_get_info_audio_db2(data)                                    ((0x000000FF&(data))>>0)


#define SEC_INFO_AUD_DB3                                                             0x9803D4A4
#define SEC_INFO_AUD_DB3_reg_addr                                                    "0x9803D4A4"
#define SEC_INFO_AUD_DB3_reg                                                         0x9803D4A4
#define set_SEC_INFO_AUD_DB3_reg(data)   (*((volatile unsigned int*) SEC_INFO_AUD_DB3_reg)=data)
#define get_SEC_INFO_AUD_DB3_reg   (*((volatile unsigned int*) SEC_INFO_AUD_DB3_reg))
#define SEC_INFO_AUD_DB3_inst_adr                                                    "0x0029"
#define SEC_INFO_AUD_DB3_inst                                                        0x0029
#define SEC_INFO_AUD_DB3_info_audio_db3_shift                                        (0)
#define SEC_INFO_AUD_DB3_info_audio_db3_mask                                         (0x000000FF)
#define SEC_INFO_AUD_DB3_info_audio_db3(data)                                        (0x000000FF&((data)<<0))
#define SEC_INFO_AUD_DB3_info_audio_db3_src(data)                                    ((0x000000FF&(data))>>0)
#define SEC_INFO_AUD_DB3_get_info_audio_db3(data)                                    ((0x000000FF&(data))>>0)


#define SEC_INFO_AUD_DB4                                                             0x9803D4A8
#define SEC_INFO_AUD_DB4_reg_addr                                                    "0x9803D4A8"
#define SEC_INFO_AUD_DB4_reg                                                         0x9803D4A8
#define set_SEC_INFO_AUD_DB4_reg(data)   (*((volatile unsigned int*) SEC_INFO_AUD_DB4_reg)=data)
#define get_SEC_INFO_AUD_DB4_reg   (*((volatile unsigned int*) SEC_INFO_AUD_DB4_reg))
#define SEC_INFO_AUD_DB4_inst_adr                                                    "0x002A"
#define SEC_INFO_AUD_DB4_inst                                                        0x002A
#define SEC_INFO_AUD_DB4_info_audio_db4_shift                                        (0)
#define SEC_INFO_AUD_DB4_info_audio_db4_mask                                         (0x000000FF)
#define SEC_INFO_AUD_DB4_info_audio_db4(data)                                        (0x000000FF&((data)<<0))
#define SEC_INFO_AUD_DB4_info_audio_db4_src(data)                                    ((0x000000FF&(data))>>0)
#define SEC_INFO_AUD_DB4_get_info_audio_db4(data)                                    ((0x000000FF&(data))>>0)


#define SEC_INFO_AUD_DB5                                                             0x9803D4AC
#define SEC_INFO_AUD_DB5_reg_addr                                                    "0x9803D4AC"
#define SEC_INFO_AUD_DB5_reg                                                         0x9803D4AC
#define set_SEC_INFO_AUD_DB5_reg(data)   (*((volatile unsigned int*) SEC_INFO_AUD_DB5_reg)=data)
#define get_SEC_INFO_AUD_DB5_reg   (*((volatile unsigned int*) SEC_INFO_AUD_DB5_reg))
#define SEC_INFO_AUD_DB5_inst_adr                                                    "0x002B"
#define SEC_INFO_AUD_DB5_inst                                                        0x002B
#define SEC_INFO_AUD_DB5_info_audio_db5_shift                                        (0)
#define SEC_INFO_AUD_DB5_info_audio_db5_mask                                         (0x000000FF)
#define SEC_INFO_AUD_DB5_info_audio_db5(data)                                        (0x000000FF&((data)<<0))
#define SEC_INFO_AUD_DB5_info_audio_db5_src(data)                                    ((0x000000FF&(data))>>0)
#define SEC_INFO_AUD_DB5_get_info_audio_db5(data)                                    ((0x000000FF&(data))>>0)


#define SEC_INFO_AUD_DB6                                                             0x9803D4B0
#define SEC_INFO_AUD_DB6_reg_addr                                                    "0x9803D4B0"
#define SEC_INFO_AUD_DB6_reg                                                         0x9803D4B0
#define set_SEC_INFO_AUD_DB6_reg(data)   (*((volatile unsigned int*) SEC_INFO_AUD_DB6_reg)=data)
#define get_SEC_INFO_AUD_DB6_reg   (*((volatile unsigned int*) SEC_INFO_AUD_DB6_reg))
#define SEC_INFO_AUD_DB6_inst_adr                                                    "0x002C"
#define SEC_INFO_AUD_DB6_inst                                                        0x002C
#define SEC_INFO_AUD_DB6_info_audio_db6_shift                                        (0)
#define SEC_INFO_AUD_DB6_info_audio_db6_mask                                         (0x000000FF)
#define SEC_INFO_AUD_DB6_info_audio_db6(data)                                        (0x000000FF&((data)<<0))
#define SEC_INFO_AUD_DB6_info_audio_db6_src(data)                                    ((0x000000FF&(data))>>0)
#define SEC_INFO_AUD_DB6_get_info_audio_db6(data)                                    ((0x000000FF&(data))>>0)


#define SEC_INFO_AUD_DB7                                                             0x9803D4B4
#define SEC_INFO_AUD_DB7_reg_addr                                                    "0x9803D4B4"
#define SEC_INFO_AUD_DB7_reg                                                         0x9803D4B4
#define set_SEC_INFO_AUD_DB7_reg(data)   (*((volatile unsigned int*) SEC_INFO_AUD_DB7_reg)=data)
#define get_SEC_INFO_AUD_DB7_reg   (*((volatile unsigned int*) SEC_INFO_AUD_DB7_reg))
#define SEC_INFO_AUD_DB7_inst_adr                                                    "0x002D"
#define SEC_INFO_AUD_DB7_inst                                                        0x002D
#define SEC_INFO_AUD_DB7_info_audio_db7_shift                                        (0)
#define SEC_INFO_AUD_DB7_info_audio_db7_mask                                         (0x000000FF)
#define SEC_INFO_AUD_DB7_info_audio_db7(data)                                        (0x000000FF&((data)<<0))
#define SEC_INFO_AUD_DB7_info_audio_db7_src(data)                                    ((0x000000FF&(data))>>0)
#define SEC_INFO_AUD_DB7_get_info_audio_db7(data)                                    ((0x000000FF&(data))>>0)


#define SEC_INFO_AUD_DB8                                                             0x9803D4B8
#define SEC_INFO_AUD_DB8_reg_addr                                                    "0x9803D4B8"
#define SEC_INFO_AUD_DB8_reg                                                         0x9803D4B8
#define set_SEC_INFO_AUD_DB8_reg(data)   (*((volatile unsigned int*) SEC_INFO_AUD_DB8_reg)=data)
#define get_SEC_INFO_AUD_DB8_reg   (*((volatile unsigned int*) SEC_INFO_AUD_DB8_reg))
#define SEC_INFO_AUD_DB8_inst_adr                                                    "0x002E"
#define SEC_INFO_AUD_DB8_inst                                                        0x002E
#define SEC_INFO_AUD_DB8_info_audio_db8_shift                                        (0)
#define SEC_INFO_AUD_DB8_info_audio_db8_mask                                         (0x000000FF)
#define SEC_INFO_AUD_DB8_info_audio_db8(data)                                        (0x000000FF&((data)<<0))
#define SEC_INFO_AUD_DB8_info_audio_db8_src(data)                                    ((0x000000FF&(data))>>0)
#define SEC_INFO_AUD_DB8_get_info_audio_db8(data)                                    ((0x000000FF&(data))>>0)


#define SEC_INFO_AUD_DB9                                                             0x9803D4BC
#define SEC_INFO_AUD_DB9_reg_addr                                                    "0x9803D4BC"
#define SEC_INFO_AUD_DB9_reg                                                         0x9803D4BC
#define set_SEC_INFO_AUD_DB9_reg(data)   (*((volatile unsigned int*) SEC_INFO_AUD_DB9_reg)=data)
#define get_SEC_INFO_AUD_DB9_reg   (*((volatile unsigned int*) SEC_INFO_AUD_DB9_reg))
#define SEC_INFO_AUD_DB9_inst_adr                                                    "0x002F"
#define SEC_INFO_AUD_DB9_inst                                                        0x002F
#define SEC_INFO_AUD_DB9_info_audio_db9_shift                                        (0)
#define SEC_INFO_AUD_DB9_info_audio_db9_mask                                         (0x000000FF)
#define SEC_INFO_AUD_DB9_info_audio_db9(data)                                        (0x000000FF&((data)<<0))
#define SEC_INFO_AUD_DB9_info_audio_db9_src(data)                                    ((0x000000FF&(data))>>0)
#define SEC_INFO_AUD_DB9_get_info_audio_db9(data)                                    ((0x000000FF&(data))>>0)


#define SEC_INFO_AVI_DB0                                                             0x9803D4C0
#define SEC_INFO_AVI_DB0_reg_addr                                                    "0x9803D4C0"
#define SEC_INFO_AVI_DB0_reg                                                         0x9803D4C0
#define set_SEC_INFO_AVI_DB0_reg(data)   (*((volatile unsigned int*) SEC_INFO_AVI_DB0_reg)=data)
#define get_SEC_INFO_AVI_DB0_reg   (*((volatile unsigned int*) SEC_INFO_AVI_DB0_reg))
#define SEC_INFO_AVI_DB0_inst_adr                                                    "0x0030"
#define SEC_INFO_AVI_DB0_inst                                                        0x0030
#define SEC_INFO_AVI_DB0_info_avi_db0_shift                                          (0)
#define SEC_INFO_AVI_DB0_info_avi_db0_mask                                           (0x000000FF)
#define SEC_INFO_AVI_DB0_info_avi_db0(data)                                          (0x000000FF&((data)<<0))
#define SEC_INFO_AVI_DB0_info_avi_db0_src(data)                                      ((0x000000FF&(data))>>0)
#define SEC_INFO_AVI_DB0_get_info_avi_db0(data)                                      ((0x000000FF&(data))>>0)


#define SEC_INFO_AVI_DB1                                                             0x9803D4C4
#define SEC_INFO_AVI_DB1_reg_addr                                                    "0x9803D4C4"
#define SEC_INFO_AVI_DB1_reg                                                         0x9803D4C4
#define set_SEC_INFO_AVI_DB1_reg(data)   (*((volatile unsigned int*) SEC_INFO_AVI_DB1_reg)=data)
#define get_SEC_INFO_AVI_DB1_reg   (*((volatile unsigned int*) SEC_INFO_AVI_DB1_reg))
#define SEC_INFO_AVI_DB1_inst_adr                                                    "0x0031"
#define SEC_INFO_AVI_DB1_inst                                                        0x0031
#define SEC_INFO_AVI_DB1_info_avi_db1_shift                                          (0)
#define SEC_INFO_AVI_DB1_info_avi_db1_mask                                           (0x000000FF)
#define SEC_INFO_AVI_DB1_info_avi_db1(data)                                          (0x000000FF&((data)<<0))
#define SEC_INFO_AVI_DB1_info_avi_db1_src(data)                                      ((0x000000FF&(data))>>0)
#define SEC_INFO_AVI_DB1_get_info_avi_db1(data)                                      ((0x000000FF&(data))>>0)


#define SEC_INFO_AVI_DB2                                                             0x9803D4C8
#define SEC_INFO_AVI_DB2_reg_addr                                                    "0x9803D4C8"
#define SEC_INFO_AVI_DB2_reg                                                         0x9803D4C8
#define set_SEC_INFO_AVI_DB2_reg(data)   (*((volatile unsigned int*) SEC_INFO_AVI_DB2_reg)=data)
#define get_SEC_INFO_AVI_DB2_reg   (*((volatile unsigned int*) SEC_INFO_AVI_DB2_reg))
#define SEC_INFO_AVI_DB2_inst_adr                                                    "0x0032"
#define SEC_INFO_AVI_DB2_inst                                                        0x0032
#define SEC_INFO_AVI_DB2_info_avi_db2_shift                                          (0)
#define SEC_INFO_AVI_DB2_info_avi_db2_mask                                           (0x000000FF)
#define SEC_INFO_AVI_DB2_info_avi_db2(data)                                          (0x000000FF&((data)<<0))
#define SEC_INFO_AVI_DB2_info_avi_db2_src(data)                                      ((0x000000FF&(data))>>0)
#define SEC_INFO_AVI_DB2_get_info_avi_db2(data)                                      ((0x000000FF&(data))>>0)


#define SEC_INFO_AVI_DB3                                                             0x9803D4CC
#define SEC_INFO_AVI_DB3_reg_addr                                                    "0x9803D4CC"
#define SEC_INFO_AVI_DB3_reg                                                         0x9803D4CC
#define set_SEC_INFO_AVI_DB3_reg(data)   (*((volatile unsigned int*) SEC_INFO_AVI_DB3_reg)=data)
#define get_SEC_INFO_AVI_DB3_reg   (*((volatile unsigned int*) SEC_INFO_AVI_DB3_reg))
#define SEC_INFO_AVI_DB3_inst_adr                                                    "0x0033"
#define SEC_INFO_AVI_DB3_inst                                                        0x0033
#define SEC_INFO_AVI_DB3_info_avi_db3_shift                                          (0)
#define SEC_INFO_AVI_DB3_info_avi_db3_mask                                           (0x000000FF)
#define SEC_INFO_AVI_DB3_info_avi_db3(data)                                          (0x000000FF&((data)<<0))
#define SEC_INFO_AVI_DB3_info_avi_db3_src(data)                                      ((0x000000FF&(data))>>0)
#define SEC_INFO_AVI_DB3_get_info_avi_db3(data)                                      ((0x000000FF&(data))>>0)


#define SEC_INFO_AVI_DB4                                                             0x9803D4D0
#define SEC_INFO_AVI_DB4_reg_addr                                                    "0x9803D4D0"
#define SEC_INFO_AVI_DB4_reg                                                         0x9803D4D0
#define set_SEC_INFO_AVI_DB4_reg(data)   (*((volatile unsigned int*) SEC_INFO_AVI_DB4_reg)=data)
#define get_SEC_INFO_AVI_DB4_reg   (*((volatile unsigned int*) SEC_INFO_AVI_DB4_reg))
#define SEC_INFO_AVI_DB4_inst_adr                                                    "0x0034"
#define SEC_INFO_AVI_DB4_inst                                                        0x0034
#define SEC_INFO_AVI_DB4_info_avi_db4_shift                                          (0)
#define SEC_INFO_AVI_DB4_info_avi_db4_mask                                           (0x000000FF)
#define SEC_INFO_AVI_DB4_info_avi_db4(data)                                          (0x000000FF&((data)<<0))
#define SEC_INFO_AVI_DB4_info_avi_db4_src(data)                                      ((0x000000FF&(data))>>0)
#define SEC_INFO_AVI_DB4_get_info_avi_db4(data)                                      ((0x000000FF&(data))>>0)


#define SEC_INFO_AVI_DB5                                                             0x9803D4D4
#define SEC_INFO_AVI_DB5_reg_addr                                                    "0x9803D4D4"
#define SEC_INFO_AVI_DB5_reg                                                         0x9803D4D4
#define set_SEC_INFO_AVI_DB5_reg(data)   (*((volatile unsigned int*) SEC_INFO_AVI_DB5_reg)=data)
#define get_SEC_INFO_AVI_DB5_reg   (*((volatile unsigned int*) SEC_INFO_AVI_DB5_reg))
#define SEC_INFO_AVI_DB5_inst_adr                                                    "0x0035"
#define SEC_INFO_AVI_DB5_inst                                                        0x0035
#define SEC_INFO_AVI_DB5_info_avi_db5_shift                                          (0)
#define SEC_INFO_AVI_DB5_info_avi_db5_mask                                           (0x000000FF)
#define SEC_INFO_AVI_DB5_info_avi_db5(data)                                          (0x000000FF&((data)<<0))
#define SEC_INFO_AVI_DB5_info_avi_db5_src(data)                                      ((0x000000FF&(data))>>0)
#define SEC_INFO_AVI_DB5_get_info_avi_db5(data)                                      ((0x000000FF&(data))>>0)


#define SEC_INFO_AVI_DB6                                                             0x9803D4D8
#define SEC_INFO_AVI_DB6_reg_addr                                                    "0x9803D4D8"
#define SEC_INFO_AVI_DB6_reg                                                         0x9803D4D8
#define set_SEC_INFO_AVI_DB6_reg(data)   (*((volatile unsigned int*) SEC_INFO_AVI_DB6_reg)=data)
#define get_SEC_INFO_AVI_DB6_reg   (*((volatile unsigned int*) SEC_INFO_AVI_DB6_reg))
#define SEC_INFO_AVI_DB6_inst_adr                                                    "0x0036"
#define SEC_INFO_AVI_DB6_inst                                                        0x0036
#define SEC_INFO_AVI_DB6_info_avi_db6_shift                                          (0)
#define SEC_INFO_AVI_DB6_info_avi_db6_mask                                           (0x000000FF)
#define SEC_INFO_AVI_DB6_info_avi_db6(data)                                          (0x000000FF&((data)<<0))
#define SEC_INFO_AVI_DB6_info_avi_db6_src(data)                                      ((0x000000FF&(data))>>0)
#define SEC_INFO_AVI_DB6_get_info_avi_db6(data)                                      ((0x000000FF&(data))>>0)


#define SEC_INFO_AVI_DB7                                                             0x9803D4DC
#define SEC_INFO_AVI_DB7_reg_addr                                                    "0x9803D4DC"
#define SEC_INFO_AVI_DB7_reg                                                         0x9803D4DC
#define set_SEC_INFO_AVI_DB7_reg(data)   (*((volatile unsigned int*) SEC_INFO_AVI_DB7_reg)=data)
#define get_SEC_INFO_AVI_DB7_reg   (*((volatile unsigned int*) SEC_INFO_AVI_DB7_reg))
#define SEC_INFO_AVI_DB7_inst_adr                                                    "0x0037"
#define SEC_INFO_AVI_DB7_inst                                                        0x0037
#define SEC_INFO_AVI_DB7_info_avi_db7_shift                                          (0)
#define SEC_INFO_AVI_DB7_info_avi_db7_mask                                           (0x000000FF)
#define SEC_INFO_AVI_DB7_info_avi_db7(data)                                          (0x000000FF&((data)<<0))
#define SEC_INFO_AVI_DB7_info_avi_db7_src(data)                                      ((0x000000FF&(data))>>0)
#define SEC_INFO_AVI_DB7_get_info_avi_db7(data)                                      ((0x000000FF&(data))>>0)


#define SEC_INFO_AVI_DB8                                                             0x9803D4E0
#define SEC_INFO_AVI_DB8_reg_addr                                                    "0x9803D4E0"
#define SEC_INFO_AVI_DB8_reg                                                         0x9803D4E0
#define set_SEC_INFO_AVI_DB8_reg(data)   (*((volatile unsigned int*) SEC_INFO_AVI_DB8_reg)=data)
#define get_SEC_INFO_AVI_DB8_reg   (*((volatile unsigned int*) SEC_INFO_AVI_DB8_reg))
#define SEC_INFO_AVI_DB8_inst_adr                                                    "0x0038"
#define SEC_INFO_AVI_DB8_inst                                                        0x0038
#define SEC_INFO_AVI_DB8_info_avi_db8_shift                                          (0)
#define SEC_INFO_AVI_DB8_info_avi_db8_mask                                           (0x000000FF)
#define SEC_INFO_AVI_DB8_info_avi_db8(data)                                          (0x000000FF&((data)<<0))
#define SEC_INFO_AVI_DB8_info_avi_db8_src(data)                                      ((0x000000FF&(data))>>0)
#define SEC_INFO_AVI_DB8_get_info_avi_db8(data)                                      ((0x000000FF&(data))>>0)


#define SEC_INFO_AVI_DB9                                                             0x9803D4E4
#define SEC_INFO_AVI_DB9_reg_addr                                                    "0x9803D4E4"
#define SEC_INFO_AVI_DB9_reg                                                         0x9803D4E4
#define set_SEC_INFO_AVI_DB9_reg(data)   (*((volatile unsigned int*) SEC_INFO_AVI_DB9_reg)=data)
#define get_SEC_INFO_AVI_DB9_reg   (*((volatile unsigned int*) SEC_INFO_AVI_DB9_reg))
#define SEC_INFO_AVI_DB9_inst_adr                                                    "0x0039"
#define SEC_INFO_AVI_DB9_inst                                                        0x0039
#define SEC_INFO_AVI_DB9_info_avi_db9_shift                                          (0)
#define SEC_INFO_AVI_DB9_info_avi_db9_mask                                           (0x000000FF)
#define SEC_INFO_AVI_DB9_info_avi_db9(data)                                          (0x000000FF&((data)<<0))
#define SEC_INFO_AVI_DB9_info_avi_db9_src(data)                                      ((0x000000FF&(data))>>0)
#define SEC_INFO_AVI_DB9_get_info_avi_db9(data)                                      ((0x000000FF&(data))>>0)


#define SEC_INFO_AVI_DB10                                                            0x9803D4E8
#define SEC_INFO_AVI_DB10_reg_addr                                                   "0x9803D4E8"
#define SEC_INFO_AVI_DB10_reg                                                        0x9803D4E8
#define set_SEC_INFO_AVI_DB10_reg(data)   (*((volatile unsigned int*) SEC_INFO_AVI_DB10_reg)=data)
#define get_SEC_INFO_AVI_DB10_reg   (*((volatile unsigned int*) SEC_INFO_AVI_DB10_reg))
#define SEC_INFO_AVI_DB10_inst_adr                                                   "0x003A"
#define SEC_INFO_AVI_DB10_inst                                                       0x003A
#define SEC_INFO_AVI_DB10_info_avi_db10_shift                                        (0)
#define SEC_INFO_AVI_DB10_info_avi_db10_mask                                         (0x000000FF)
#define SEC_INFO_AVI_DB10_info_avi_db10(data)                                        (0x000000FF&((data)<<0))
#define SEC_INFO_AVI_DB10_info_avi_db10_src(data)                                    ((0x000000FF&(data))>>0)
#define SEC_INFO_AVI_DB10_get_info_avi_db10(data)                                    ((0x000000FF&(data))>>0)


#define SEC_INFO_AVI_DB11                                                            0x9803D4EC
#define SEC_INFO_AVI_DB11_reg_addr                                                   "0x9803D4EC"
#define SEC_INFO_AVI_DB11_reg                                                        0x9803D4EC
#define set_SEC_INFO_AVI_DB11_reg(data)   (*((volatile unsigned int*) SEC_INFO_AVI_DB11_reg)=data)
#define get_SEC_INFO_AVI_DB11_reg   (*((volatile unsigned int*) SEC_INFO_AVI_DB11_reg))
#define SEC_INFO_AVI_DB11_inst_adr                                                   "0x003B"
#define SEC_INFO_AVI_DB11_inst                                                       0x003B
#define SEC_INFO_AVI_DB11_info_avi_db11_shift                                        (0)
#define SEC_INFO_AVI_DB11_info_avi_db11_mask                                         (0x000000FF)
#define SEC_INFO_AVI_DB11_info_avi_db11(data)                                        (0x000000FF&((data)<<0))
#define SEC_INFO_AVI_DB11_info_avi_db11_src(data)                                    ((0x000000FF&(data))>>0)
#define SEC_INFO_AVI_DB11_get_info_avi_db11(data)                                    ((0x000000FF&(data))>>0)


#define SEC_INFO_AVI_DB12                                                            0x9803D4F0
#define SEC_INFO_AVI_DB12_reg_addr                                                   "0x9803D4F0"
#define SEC_INFO_AVI_DB12_reg                                                        0x9803D4F0
#define set_SEC_INFO_AVI_DB12_reg(data)   (*((volatile unsigned int*) SEC_INFO_AVI_DB12_reg)=data)
#define get_SEC_INFO_AVI_DB12_reg   (*((volatile unsigned int*) SEC_INFO_AVI_DB12_reg))
#define SEC_INFO_AVI_DB12_inst_adr                                                   "0x003C"
#define SEC_INFO_AVI_DB12_inst                                                       0x003C
#define SEC_INFO_AVI_DB12_info_avi_db12_shift                                        (0)
#define SEC_INFO_AVI_DB12_info_avi_db12_mask                                         (0x000000FF)
#define SEC_INFO_AVI_DB12_info_avi_db12(data)                                        (0x000000FF&((data)<<0))
#define SEC_INFO_AVI_DB12_info_avi_db12_src(data)                                    ((0x000000FF&(data))>>0)
#define SEC_INFO_AVI_DB12_get_info_avi_db12(data)                                    ((0x000000FF&(data))>>0)


#define SEC_INFO_MPEG_DB0                                                            0x9803D4F4
#define SEC_INFO_MPEG_DB0_reg_addr                                                   "0x9803D4F4"
#define SEC_INFO_MPEG_DB0_reg                                                        0x9803D4F4
#define set_SEC_INFO_MPEG_DB0_reg(data)   (*((volatile unsigned int*) SEC_INFO_MPEG_DB0_reg)=data)
#define get_SEC_INFO_MPEG_DB0_reg   (*((volatile unsigned int*) SEC_INFO_MPEG_DB0_reg))
#define SEC_INFO_MPEG_DB0_inst_adr                                                   "0x003D"
#define SEC_INFO_MPEG_DB0_inst                                                       0x003D
#define SEC_INFO_MPEG_DB0_info_mpeg_db0_shift                                        (0)
#define SEC_INFO_MPEG_DB0_info_mpeg_db0_mask                                         (0x000000FF)
#define SEC_INFO_MPEG_DB0_info_mpeg_db0(data)                                        (0x000000FF&((data)<<0))
#define SEC_INFO_MPEG_DB0_info_mpeg_db0_src(data)                                    ((0x000000FF&(data))>>0)
#define SEC_INFO_MPEG_DB0_get_info_mpeg_db0(data)                                    ((0x000000FF&(data))>>0)


#define SEC_INFO_MPEG_DB1                                                            0x9803D4F8
#define SEC_INFO_MPEG_DB1_reg_addr                                                   "0x9803D4F8"
#define SEC_INFO_MPEG_DB1_reg                                                        0x9803D4F8
#define set_SEC_INFO_MPEG_DB1_reg(data)   (*((volatile unsigned int*) SEC_INFO_MPEG_DB1_reg)=data)
#define get_SEC_INFO_MPEG_DB1_reg   (*((volatile unsigned int*) SEC_INFO_MPEG_DB1_reg))
#define SEC_INFO_MPEG_DB1_inst_adr                                                   "0x003E"
#define SEC_INFO_MPEG_DB1_inst                                                       0x003E
#define SEC_INFO_MPEG_DB1_info_mpeg_db1_shift                                        (0)
#define SEC_INFO_MPEG_DB1_info_mpeg_db1_mask                                         (0x000000FF)
#define SEC_INFO_MPEG_DB1_info_mpeg_db1(data)                                        (0x000000FF&((data)<<0))
#define SEC_INFO_MPEG_DB1_info_mpeg_db1_src(data)                                    ((0x000000FF&(data))>>0)
#define SEC_INFO_MPEG_DB1_get_info_mpeg_db1(data)                                    ((0x000000FF&(data))>>0)


#define SEC_INFO_MPEG_DB2                                                            0x9803D4FC
#define SEC_INFO_MPEG_DB2_reg_addr                                                   "0x9803D4FC"
#define SEC_INFO_MPEG_DB2_reg                                                        0x9803D4FC
#define set_SEC_INFO_MPEG_DB2_reg(data)   (*((volatile unsigned int*) SEC_INFO_MPEG_DB2_reg)=data)
#define get_SEC_INFO_MPEG_DB2_reg   (*((volatile unsigned int*) SEC_INFO_MPEG_DB2_reg))
#define SEC_INFO_MPEG_DB2_inst_adr                                                   "0x003F"
#define SEC_INFO_MPEG_DB2_inst                                                       0x003F
#define SEC_INFO_MPEG_DB2_info_mpeg_db2_shift                                        (0)
#define SEC_INFO_MPEG_DB2_info_mpeg_db2_mask                                         (0x000000FF)
#define SEC_INFO_MPEG_DB2_info_mpeg_db2(data)                                        (0x000000FF&((data)<<0))
#define SEC_INFO_MPEG_DB2_info_mpeg_db2_src(data)                                    ((0x000000FF&(data))>>0)
#define SEC_INFO_MPEG_DB2_get_info_mpeg_db2(data)                                    ((0x000000FF&(data))>>0)


#define SEC_INFO_MPEG_DB3                                                            0x9803D500
#define SEC_INFO_MPEG_DB3_reg_addr                                                   "0x9803D500"
#define SEC_INFO_MPEG_DB3_reg                                                        0x9803D500
#define set_SEC_INFO_MPEG_DB3_reg(data)   (*((volatile unsigned int*) SEC_INFO_MPEG_DB3_reg)=data)
#define get_SEC_INFO_MPEG_DB3_reg   (*((volatile unsigned int*) SEC_INFO_MPEG_DB3_reg))
#define SEC_INFO_MPEG_DB3_inst_adr                                                   "0x0040"
#define SEC_INFO_MPEG_DB3_inst                                                       0x0040
#define SEC_INFO_MPEG_DB3_info_mpeg_db3_shift                                        (0)
#define SEC_INFO_MPEG_DB3_info_mpeg_db3_mask                                         (0x000000FF)
#define SEC_INFO_MPEG_DB3_info_mpeg_db3(data)                                        (0x000000FF&((data)<<0))
#define SEC_INFO_MPEG_DB3_info_mpeg_db3_src(data)                                    ((0x000000FF&(data))>>0)
#define SEC_INFO_MPEG_DB3_get_info_mpeg_db3(data)                                    ((0x000000FF&(data))>>0)


#define SEC_INFO_MPEG_DB4                                                            0x9803D504
#define SEC_INFO_MPEG_DB4_reg_addr                                                   "0x9803D504"
#define SEC_INFO_MPEG_DB4_reg                                                        0x9803D504
#define set_SEC_INFO_MPEG_DB4_reg(data)   (*((volatile unsigned int*) SEC_INFO_MPEG_DB4_reg)=data)
#define get_SEC_INFO_MPEG_DB4_reg   (*((volatile unsigned int*) SEC_INFO_MPEG_DB4_reg))
#define SEC_INFO_MPEG_DB4_inst_adr                                                   "0x0041"
#define SEC_INFO_MPEG_DB4_inst                                                       0x0041
#define SEC_INFO_MPEG_DB4_info_mpeg_db4_shift                                        (0)
#define SEC_INFO_MPEG_DB4_info_mpeg_db4_mask                                         (0x000000FF)
#define SEC_INFO_MPEG_DB4_info_mpeg_db4(data)                                        (0x000000FF&((data)<<0))
#define SEC_INFO_MPEG_DB4_info_mpeg_db4_src(data)                                    ((0x000000FF&(data))>>0)
#define SEC_INFO_MPEG_DB4_get_info_mpeg_db4(data)                                    ((0x000000FF&(data))>>0)


#define SEC_INFO_MPEG_DB5                                                            0x9803D508
#define SEC_INFO_MPEG_DB5_reg_addr                                                   "0x9803D508"
#define SEC_INFO_MPEG_DB5_reg                                                        0x9803D508
#define set_SEC_INFO_MPEG_DB5_reg(data)   (*((volatile unsigned int*) SEC_INFO_MPEG_DB5_reg)=data)
#define get_SEC_INFO_MPEG_DB5_reg   (*((volatile unsigned int*) SEC_INFO_MPEG_DB5_reg))
#define SEC_INFO_MPEG_DB5_inst_adr                                                   "0x0042"
#define SEC_INFO_MPEG_DB5_inst                                                       0x0042
#define SEC_INFO_MPEG_DB5_info_mpeg_db5_shift                                        (0)
#define SEC_INFO_MPEG_DB5_info_mpeg_db5_mask                                         (0x000000FF)
#define SEC_INFO_MPEG_DB5_info_mpeg_db5(data)                                        (0x000000FF&((data)<<0))
#define SEC_INFO_MPEG_DB5_info_mpeg_db5_src(data)                                    ((0x000000FF&(data))>>0)
#define SEC_INFO_MPEG_DB5_get_info_mpeg_db5(data)                                    ((0x000000FF&(data))>>0)


#define SEC_INFO_MPEG_DB6                                                            0x9803D50C
#define SEC_INFO_MPEG_DB6_reg_addr                                                   "0x9803D50C"
#define SEC_INFO_MPEG_DB6_reg                                                        0x9803D50C
#define set_SEC_INFO_MPEG_DB6_reg(data)   (*((volatile unsigned int*) SEC_INFO_MPEG_DB6_reg)=data)
#define get_SEC_INFO_MPEG_DB6_reg   (*((volatile unsigned int*) SEC_INFO_MPEG_DB6_reg))
#define SEC_INFO_MPEG_DB6_inst_adr                                                   "0x0043"
#define SEC_INFO_MPEG_DB6_inst                                                       0x0043
#define SEC_INFO_MPEG_DB6_info_mpeg_db6_shift                                        (0)
#define SEC_INFO_MPEG_DB6_info_mpeg_db6_mask                                         (0x000000FF)
#define SEC_INFO_MPEG_DB6_info_mpeg_db6(data)                                        (0x000000FF&((data)<<0))
#define SEC_INFO_MPEG_DB6_info_mpeg_db6_src(data)                                    ((0x000000FF&(data))>>0)
#define SEC_INFO_MPEG_DB6_get_info_mpeg_db6(data)                                    ((0x000000FF&(data))>>0)


#define SEC_INFO_MPEG_DB7                                                            0x9803D510
#define SEC_INFO_MPEG_DB7_reg_addr                                                   "0x9803D510"
#define SEC_INFO_MPEG_DB7_reg                                                        0x9803D510
#define set_SEC_INFO_MPEG_DB7_reg(data)   (*((volatile unsigned int*) SEC_INFO_MPEG_DB7_reg)=data)
#define get_SEC_INFO_MPEG_DB7_reg   (*((volatile unsigned int*) SEC_INFO_MPEG_DB7_reg))
#define SEC_INFO_MPEG_DB7_inst_adr                                                   "0x0044"
#define SEC_INFO_MPEG_DB7_inst                                                       0x0044
#define SEC_INFO_MPEG_DB7_info_mpeg_db7_shift                                        (0)
#define SEC_INFO_MPEG_DB7_info_mpeg_db7_mask                                         (0x000000FF)
#define SEC_INFO_MPEG_DB7_info_mpeg_db7(data)                                        (0x000000FF&((data)<<0))
#define SEC_INFO_MPEG_DB7_info_mpeg_db7_src(data)                                    ((0x000000FF&(data))>>0)
#define SEC_INFO_MPEG_DB7_get_info_mpeg_db7(data)                                    ((0x000000FF&(data))>>0)


#define SEC_INFO_MPEG_DB8                                                            0x9803D514
#define SEC_INFO_MPEG_DB8_reg_addr                                                   "0x9803D514"
#define SEC_INFO_MPEG_DB8_reg                                                        0x9803D514
#define set_SEC_INFO_MPEG_DB8_reg(data)   (*((volatile unsigned int*) SEC_INFO_MPEG_DB8_reg)=data)
#define get_SEC_INFO_MPEG_DB8_reg   (*((volatile unsigned int*) SEC_INFO_MPEG_DB8_reg))
#define SEC_INFO_MPEG_DB8_inst_adr                                                   "0x0045"
#define SEC_INFO_MPEG_DB8_inst                                                       0x0045
#define SEC_INFO_MPEG_DB8_info_mpeg_db8_shift                                        (0)
#define SEC_INFO_MPEG_DB8_info_mpeg_db8_mask                                         (0x000000FF)
#define SEC_INFO_MPEG_DB8_info_mpeg_db8(data)                                        (0x000000FF&((data)<<0))
#define SEC_INFO_MPEG_DB8_info_mpeg_db8_src(data)                                    ((0x000000FF&(data))>>0)
#define SEC_INFO_MPEG_DB8_get_info_mpeg_db8(data)                                    ((0x000000FF&(data))>>0)


#define SEC_INFO_MPEG_DB9                                                            0x9803D518
#define SEC_INFO_MPEG_DB9_reg_addr                                                   "0x9803D518"
#define SEC_INFO_MPEG_DB9_reg                                                        0x9803D518
#define set_SEC_INFO_MPEG_DB9_reg(data)   (*((volatile unsigned int*) SEC_INFO_MPEG_DB9_reg)=data)
#define get_SEC_INFO_MPEG_DB9_reg   (*((volatile unsigned int*) SEC_INFO_MPEG_DB9_reg))
#define SEC_INFO_MPEG_DB9_inst_adr                                                   "0x0046"
#define SEC_INFO_MPEG_DB9_inst                                                       0x0046
#define SEC_INFO_MPEG_DB9_info_mpeg_db9_shift                                        (0)
#define SEC_INFO_MPEG_DB9_info_mpeg_db9_mask                                         (0x000000FF)
#define SEC_INFO_MPEG_DB9_info_mpeg_db9(data)                                        (0x000000FF&((data)<<0))
#define SEC_INFO_MPEG_DB9_info_mpeg_db9_src(data)                                    ((0x000000FF&(data))>>0)
#define SEC_INFO_MPEG_DB9_get_info_mpeg_db9(data)                                    ((0x000000FF&(data))>>0)


#define AUD_FUNCTION_CTRL2                                                           0x9803D51C
#define AUD_FUNCTION_CTRL2_reg_addr                                                  "0x9803D51C"
#define AUD_FUNCTION_CTRL2_reg                                                       0x9803D51C
#define set_AUD_FUNCTION_CTRL2_reg(data)   (*((volatile unsigned int*) AUD_FUNCTION_CTRL2_reg)=data)
#define get_AUD_FUNCTION_CTRL2_reg   (*((volatile unsigned int*) AUD_FUNCTION_CTRL2_reg))
#define AUD_FUNCTION_CTRL2_inst_adr                                                  "0x0047"
#define AUD_FUNCTION_CTRL2_inst                                                      0x0047
#define AUD_FUNCTION_CTRL2_audio_long_packet_shift                                   (7)
#define AUD_FUNCTION_CTRL2_audio_long_packet_mask                                    (0x00000080)
#define AUD_FUNCTION_CTRL2_audio_long_packet(data)                                   (0x00000080&((data)<<7))
#define AUD_FUNCTION_CTRL2_audio_long_packet_src(data)                               ((0x00000080&(data))>>7)
#define AUD_FUNCTION_CTRL2_get_audio_long_packet(data)                               ((0x00000080&(data))>>7)
#define AUD_FUNCTION_CTRL2_audio_long_packet_end_chk_shift                           (6)
#define AUD_FUNCTION_CTRL2_audio_long_packet_end_chk_mask                            (0x00000040)
#define AUD_FUNCTION_CTRL2_audio_long_packet_end_chk(data)                           (0x00000040&((data)<<6))
#define AUD_FUNCTION_CTRL2_audio_long_packet_end_chk_src(data)                       ((0x00000040&(data))>>6)
#define AUD_FUNCTION_CTRL2_get_audio_long_packet_end_chk(data)                       ((0x00000040&(data))>>6)
#define AUD_FUNCTION_CTRL2_max_long_packet_cnt_shift                                 (0)
#define AUD_FUNCTION_CTRL2_max_long_packet_cnt_mask                                  (0x0000003F)
#define AUD_FUNCTION_CTRL2_max_long_packet_cnt(data)                                 (0x0000003F&((data)<<0))
#define AUD_FUNCTION_CTRL2_max_long_packet_cnt_src(data)                             ((0x0000003F&(data))>>0)
#define AUD_FUNCTION_CTRL2_get_max_long_packet_cnt(data)                             ((0x0000003F&(data))>>0)


#define AUD_FUNCTION_CTRL3                                                           0x9803D520
#define AUD_FUNCTION_CTRL3_reg_addr                                                  "0x9803D520"
#define AUD_FUNCTION_CTRL3_reg                                                       0x9803D520
#define set_AUD_FUNCTION_CTRL3_reg(data)   (*((volatile unsigned int*) AUD_FUNCTION_CTRL3_reg)=data)
#define get_AUD_FUNCTION_CTRL3_reg   (*((volatile unsigned int*) AUD_FUNCTION_CTRL3_reg))
#define AUD_FUNCTION_CTRL3_inst_adr                                                  "0x0048"
#define AUD_FUNCTION_CTRL3_inst                                                      0x0048
#define AUD_FUNCTION_CTRL3_Reserved_shift                                            (4)
#define AUD_FUNCTION_CTRL3_Reserved_mask                                             (0x000000F0)
#define AUD_FUNCTION_CTRL3_Reserved(data)                                            (0x000000F0&((data)<<4))
#define AUD_FUNCTION_CTRL3_Reserved_src(data)                                        ((0x000000F0&(data))>>4)
#define AUD_FUNCTION_CTRL3_get_Reserved(data)                                        ((0x000000F0&(data))>>4)
#define AUD_FUNCTION_CTRL3_audio_i2s_8ch_shift                                       (3)
#define AUD_FUNCTION_CTRL3_audio_i2s_8ch_mask                                        (0x00000008)
#define AUD_FUNCTION_CTRL3_audio_i2s_8ch(data)                                       (0x00000008&((data)<<3))
#define AUD_FUNCTION_CTRL3_audio_i2s_8ch_src(data)                                   ((0x00000008&(data))>>3)
#define AUD_FUNCTION_CTRL3_get_audio_i2s_8ch(data)                                   ((0x00000008&(data))>>3)
#define AUD_FUNCTION_CTRL3_audio_source_db_en_shift                                  (2)
#define AUD_FUNCTION_CTRL3_audio_source_db_en_mask                                   (0x00000004)
#define AUD_FUNCTION_CTRL3_audio_source_db_en(data)                                  (0x00000004&((data)<<2))
#define AUD_FUNCTION_CTRL3_audio_source_db_en_src(data)                              ((0x00000004&(data))>>2)
#define AUD_FUNCTION_CTRL3_get_audio_source_db_en(data)                              ((0x00000004&(data))>>2)
#define AUD_FUNCTION_CTRL3_tx_code_nb_swap_shift                                     (1)
#define AUD_FUNCTION_CTRL3_tx_code_nb_swap_mask                                      (0x00000002)
#define AUD_FUNCTION_CTRL3_tx_code_nb_swap(data)                                     (0x00000002&((data)<<1))
#define AUD_FUNCTION_CTRL3_tx_code_nb_swap_src(data)                                 ((0x00000002&(data))>>1)
#define AUD_FUNCTION_CTRL3_get_tx_code_nb_swap(data)                                 ((0x00000002&(data))>>1)
#define AUD_FUNCTION_CTRL3_tx_code_reverse_shift                                     (0)
#define AUD_FUNCTION_CTRL3_tx_code_reverse_mask                                      (0x00000001)
#define AUD_FUNCTION_CTRL3_tx_code_reverse(data)                                     (0x00000001&((data)<<0))
#define AUD_FUNCTION_CTRL3_tx_code_reverse_src(data)                                 ((0x00000001&(data))>>0)
#define AUD_FUNCTION_CTRL3_get_tx_code_reverse(data)                                 ((0x00000001&(data))>>0)


#define MST_SEC_PKT_ID                                                               0x9803D524
#define MST_SEC_PKT_ID_reg_addr                                                      "0x9803D524"
#define MST_SEC_PKT_ID_reg                                                           0x9803D524
#define set_MST_SEC_PKT_ID_reg(data)   (*((volatile unsigned int*) MST_SEC_PKT_ID_reg)=data)
#define get_MST_SEC_PKT_ID_reg   (*((volatile unsigned int*) MST_SEC_PKT_ID_reg))
#define MST_SEC_PKT_ID_inst_adr                                                      "0x0049"
#define MST_SEC_PKT_ID_inst                                                          0x0049
#define MST_SEC_PKT_ID_mst_sec_packet_id_shift                                       (0)
#define MST_SEC_PKT_ID_mst_sec_packet_id_mask                                        (0x000000FF)
#define MST_SEC_PKT_ID_mst_sec_packet_id(data)                                       (0x000000FF&((data)<<0))
#define MST_SEC_PKT_ID_mst_sec_packet_id_src(data)                                   ((0x000000FF&(data))>>0)
#define MST_SEC_PKT_ID_get_mst_sec_packet_id(data)                                   ((0x000000FF&(data))>>0)


#define MST_SEC_PKT_HB3                                                              0x9803D528
#define MST_SEC_PKT_HB3_reg_addr                                                     "0x9803D528"
#define MST_SEC_PKT_HB3_reg                                                          0x9803D528
#define set_MST_SEC_PKT_HB3_reg(data)   (*((volatile unsigned int*) MST_SEC_PKT_HB3_reg)=data)
#define get_MST_SEC_PKT_HB3_reg   (*((volatile unsigned int*) MST_SEC_PKT_HB3_reg))
#define MST_SEC_PKT_HB3_inst_adr                                                     "0x004A"
#define MST_SEC_PKT_HB3_inst                                                         0x004A
#define MST_SEC_PKT_HB3_Reserved_shift                                               (7)
#define MST_SEC_PKT_HB3_Reserved_mask                                                (0x00000080)
#define MST_SEC_PKT_HB3_Reserved(data)                                               (0x00000080&((data)<<7))
#define MST_SEC_PKT_HB3_Reserved_src(data)                                           ((0x00000080&(data))>>7)
#define MST_SEC_PKT_HB3_get_Reserved(data)                                           ((0x00000080&(data))>>7)
#define MST_SEC_PKT_HB3_mst_channel_cnt_shift                                        (4)
#define MST_SEC_PKT_HB3_mst_channel_cnt_mask                                         (0x00000070)
#define MST_SEC_PKT_HB3_mst_channel_cnt(data)                                        (0x00000070&((data)<<4))
#define MST_SEC_PKT_HB3_mst_channel_cnt_src(data)                                    ((0x00000070&(data))>>4)
#define MST_SEC_PKT_HB3_get_mst_channel_cnt(data)                                    ((0x00000070&(data))>>4)
#define MST_SEC_PKT_HB3_mst_coding_type_shift                                        (0)
#define MST_SEC_PKT_HB3_mst_coding_type_mask                                         (0x0000000F)
#define MST_SEC_PKT_HB3_mst_coding_type(data)                                        (0x0000000F&((data)<<0))
#define MST_SEC_PKT_HB3_mst_coding_type_src(data)                                    ((0x0000000F&(data))>>0)
#define MST_SEC_PKT_HB3_get_mst_coding_type(data)                                    ((0x0000000F&(data))>>0)


#define SEC_RS_DECODE_CTRL                                                           0x9803D52C
#define SEC_RS_DECODE_CTRL_reg_addr                                                  "0x9803D52C"
#define SEC_RS_DECODE_CTRL_reg                                                       0x9803D52C
#define set_SEC_RS_DECODE_CTRL_reg(data)   (*((volatile unsigned int*) SEC_RS_DECODE_CTRL_reg)=data)
#define get_SEC_RS_DECODE_CTRL_reg   (*((volatile unsigned int*) SEC_RS_DECODE_CTRL_reg))
#define SEC_RS_DECODE_CTRL_inst_adr                                                  "0x004B"
#define SEC_RS_DECODE_CTRL_inst                                                      0x004B
#define SEC_RS_DECODE_CTRL_rs_dec_en_strm2_shift                                     (7)
#define SEC_RS_DECODE_CTRL_rs_dec_en_strm2_mask                                      (0x00000080)
#define SEC_RS_DECODE_CTRL_rs_dec_en_strm2(data)                                     (0x00000080&((data)<<7))
#define SEC_RS_DECODE_CTRL_rs_dec_en_strm2_src(data)                                 ((0x00000080&(data))>>7)
#define SEC_RS_DECODE_CTRL_get_rs_dec_en_strm2(data)                                 ((0x00000080&(data))>>7)
#define SEC_RS_DECODE_CTRL_code_nb_swap_strm2_shift                                  (6)
#define SEC_RS_DECODE_CTRL_code_nb_swap_strm2_mask                                   (0x00000040)
#define SEC_RS_DECODE_CTRL_code_nb_swap_strm2(data)                                  (0x00000040&((data)<<6))
#define SEC_RS_DECODE_CTRL_code_nb_swap_strm2_src(data)                              ((0x00000040&(data))>>6)
#define SEC_RS_DECODE_CTRL_get_code_nb_swap_strm2(data)                              ((0x00000040&(data))>>6)
#define SEC_RS_DECODE_CTRL_code_reverse_strm2_shift                                  (5)
#define SEC_RS_DECODE_CTRL_code_reverse_strm2_mask                                   (0x00000020)
#define SEC_RS_DECODE_CTRL_code_reverse_strm2(data)                                  (0x00000020&((data)<<5))
#define SEC_RS_DECODE_CTRL_code_reverse_strm2_src(data)                              ((0x00000020&(data))>>5)
#define SEC_RS_DECODE_CTRL_get_code_reverse_strm2(data)                              ((0x00000020&(data))>>5)
#define SEC_RS_DECODE_CTRL_rs_err2_enh_mode_strm2_shift                              (4)
#define SEC_RS_DECODE_CTRL_rs_err2_enh_mode_strm2_mask                               (0x00000010)
#define SEC_RS_DECODE_CTRL_rs_err2_enh_mode_strm2(data)                              (0x00000010&((data)<<4))
#define SEC_RS_DECODE_CTRL_rs_err2_enh_mode_strm2_src(data)                          ((0x00000010&(data))>>4)
#define SEC_RS_DECODE_CTRL_get_rs_err2_enh_mode_strm2(data)                          ((0x00000010&(data))>>4)
#define SEC_RS_DECODE_CTRL_rs_err2_mode_strm2_shift                                  (3)
#define SEC_RS_DECODE_CTRL_rs_err2_mode_strm2_mask                                   (0x00000008)
#define SEC_RS_DECODE_CTRL_rs_err2_mode_strm2(data)                                  (0x00000008&((data)<<3))
#define SEC_RS_DECODE_CTRL_rs_err2_mode_strm2_src(data)                              ((0x00000008&(data))>>3)
#define SEC_RS_DECODE_CTRL_get_rs_err2_mode_strm2(data)                              ((0x00000008&(data))>>3)
#define SEC_RS_DECODE_CTRL_rs_err1_shift                                             (2)
#define SEC_RS_DECODE_CTRL_rs_err1_mask                                              (0x00000004)
#define SEC_RS_DECODE_CTRL_rs_err1(data)                                             (0x00000004&((data)<<2))
#define SEC_RS_DECODE_CTRL_rs_err1_src(data)                                         ((0x00000004&(data))>>2)
#define SEC_RS_DECODE_CTRL_get_rs_err1(data)                                         ((0x00000004&(data))>>2)
#define SEC_RS_DECODE_CTRL_rs_err2_shift                                             (1)
#define SEC_RS_DECODE_CTRL_rs_err2_mask                                              (0x00000002)
#define SEC_RS_DECODE_CTRL_rs_err2(data)                                             (0x00000002&((data)<<1))
#define SEC_RS_DECODE_CTRL_rs_err2_src(data)                                         ((0x00000002&(data))>>1)
#define SEC_RS_DECODE_CTRL_get_rs_err2(data)                                         ((0x00000002&(data))>>1)
#define SEC_RS_DECODE_CTRL_rs_dec_err2_proc_shift                                    (0)
#define SEC_RS_DECODE_CTRL_rs_dec_err2_proc_mask                                     (0x00000001)
#define SEC_RS_DECODE_CTRL_rs_dec_err2_proc(data)                                    (0x00000001&((data)<<0))
#define SEC_RS_DECODE_CTRL_rs_dec_err2_proc_src(data)                                ((0x00000001&(data))>>0)
#define SEC_RS_DECODE_CTRL_get_rs_dec_err2_proc(data)                                ((0x00000001&(data))>>0)


#define SEC_AUD_FREQDET_CTRL                                                         0x9803D530
#define SEC_AUD_FREQDET_CTRL_reg_addr                                                "0x9803D530"
#define SEC_AUD_FREQDET_CTRL_reg                                                     0x9803D530
#define set_SEC_AUD_FREQDET_CTRL_reg(data)   (*((volatile unsigned int*) SEC_AUD_FREQDET_CTRL_reg)=data)
#define get_SEC_AUD_FREQDET_CTRL_reg   (*((volatile unsigned int*) SEC_AUD_FREQDET_CTRL_reg))
#define SEC_AUD_FREQDET_CTRL_inst_adr                                                "0x004C"
#define SEC_AUD_FREQDET_CTRL_inst                                                    0x004C
#define SEC_AUD_FREQDET_CTRL_afreq_det_shift                                         (7)
#define SEC_AUD_FREQDET_CTRL_afreq_det_mask                                          (0x00000080)
#define SEC_AUD_FREQDET_CTRL_afreq_det(data)                                         (0x00000080&((data)<<7))
#define SEC_AUD_FREQDET_CTRL_afreq_det_src(data)                                     ((0x00000080&(data))>>7)
#define SEC_AUD_FREQDET_CTRL_get_afreq_det(data)                                     ((0x00000080&(data))>>7)
#define SEC_AUD_FREQDET_CTRL_Reserved_shift                                          (5)
#define SEC_AUD_FREQDET_CTRL_Reserved_mask                                           (0x00000060)
#define SEC_AUD_FREQDET_CTRL_Reserved(data)                                          (0x00000060&((data)<<5))
#define SEC_AUD_FREQDET_CTRL_Reserved_src(data)                                      ((0x00000060&(data))>>5)
#define SEC_AUD_FREQDET_CTRL_get_Reserved(data)                                      ((0x00000060&(data))>>5)
#define SEC_AUD_FREQDET_CTRL_aud_freq_status_method_shift                            (4)
#define SEC_AUD_FREQDET_CTRL_aud_freq_status_method_mask                             (0x00000010)
#define SEC_AUD_FREQDET_CTRL_aud_freq_status_method(data)                            (0x00000010&((data)<<4))
#define SEC_AUD_FREQDET_CTRL_aud_freq_status_method_src(data)                        ((0x00000010&(data))>>4)
#define SEC_AUD_FREQDET_CTRL_get_aud_freq_status_method(data)                        ((0x00000010&(data))>>4)
#define SEC_AUD_FREQDET_CTRL_aud_freq_range_clr_shift                                (3)
#define SEC_AUD_FREQDET_CTRL_aud_freq_range_clr_mask                                 (0x00000008)
#define SEC_AUD_FREQDET_CTRL_aud_freq_range_clr(data)                                (0x00000008&((data)<<3))
#define SEC_AUD_FREQDET_CTRL_aud_freq_range_clr_src(data)                            ((0x00000008&(data))>>3)
#define SEC_AUD_FREQDET_CTRL_get_aud_freq_range_clr(data)                            ((0x00000008&(data))>>3)
#define SEC_AUD_FREQDET_CTRL_aud_freq_stable_shift                                   (2)
#define SEC_AUD_FREQDET_CTRL_aud_freq_stable_mask                                    (0x00000004)
#define SEC_AUD_FREQDET_CTRL_aud_freq_stable(data)                                   (0x00000004&((data)<<2))
#define SEC_AUD_FREQDET_CTRL_aud_freq_stable_src(data)                               ((0x00000004&(data))>>2)
#define SEC_AUD_FREQDET_CTRL_get_aud_freq_stable(data)                               ((0x00000004&(data))>>2)
#define SEC_AUD_FREQDET_CTRL_aud_sp_cnt_clr_shift                                    (1)
#define SEC_AUD_FREQDET_CTRL_aud_sp_cnt_clr_mask                                     (0x00000002)
#define SEC_AUD_FREQDET_CTRL_aud_sp_cnt_clr(data)                                    (0x00000002&((data)<<1))
#define SEC_AUD_FREQDET_CTRL_aud_sp_cnt_clr_src(data)                                ((0x00000002&(data))>>1)
#define SEC_AUD_FREQDET_CTRL_get_aud_sp_cnt_clr(data)                                ((0x00000002&(data))>>1)
#define SEC_AUD_FREQDET_CTRL_aud_441_48_same_en_shift                                (0)
#define SEC_AUD_FREQDET_CTRL_aud_441_48_same_en_mask                                 (0x00000001)
#define SEC_AUD_FREQDET_CTRL_aud_441_48_same_en(data)                                (0x00000001&((data)<<0))
#define SEC_AUD_FREQDET_CTRL_aud_441_48_same_en_src(data)                            ((0x00000001&(data))>>0)
#define SEC_AUD_FREQDET_CTRL_get_aud_441_48_same_en(data)                            ((0x00000001&(data))>>0)


#define SEC_AUD_XCLK_DIV                                                             0x9803D534
#define SEC_AUD_XCLK_DIV_reg_addr                                                    "0x9803D534"
#define SEC_AUD_XCLK_DIV_reg                                                         0x9803D534
#define set_SEC_AUD_XCLK_DIV_reg(data)   (*((volatile unsigned int*) SEC_AUD_XCLK_DIV_reg)=data)
#define get_SEC_AUD_XCLK_DIV_reg   (*((volatile unsigned int*) SEC_AUD_XCLK_DIV_reg))
#define SEC_AUD_XCLK_DIV_inst_adr                                                    "0x004D"
#define SEC_AUD_XCLK_DIV_inst                                                        0x004D
#define SEC_AUD_XCLK_DIV_aud_xclk_div_shift                                          (0)
#define SEC_AUD_XCLK_DIV_aud_xclk_div_mask                                           (0x000000FF)
#define SEC_AUD_XCLK_DIV_aud_xclk_div(data)                                          (0x000000FF&((data)<<0))
#define SEC_AUD_XCLK_DIV_aud_xclk_div_src(data)                                      ((0x000000FF&(data))>>0)
#define SEC_AUD_XCLK_DIV_get_aud_xclk_div(data)                                      ((0x000000FF&(data))>>0)


#define SEC_AUD_FREQ_TIME                                                            0x9803D538
#define SEC_AUD_FREQ_TIME_reg_addr                                                   "0x9803D538"
#define SEC_AUD_FREQ_TIME_reg                                                        0x9803D538
#define set_SEC_AUD_FREQ_TIME_reg(data)   (*((volatile unsigned int*) SEC_AUD_FREQ_TIME_reg)=data)
#define get_SEC_AUD_FREQ_TIME_reg   (*((volatile unsigned int*) SEC_AUD_FREQ_TIME_reg))
#define SEC_AUD_FREQ_TIME_inst_adr                                                   "0x004E"
#define SEC_AUD_FREQ_TIME_inst                                                       0x004E
#define SEC_AUD_FREQ_TIME_aud_freq_time_shift                                        (6)
#define SEC_AUD_FREQ_TIME_aud_freq_time_mask                                         (0x000000C0)
#define SEC_AUD_FREQ_TIME_aud_freq_time(data)                                        (0x000000C0&((data)<<6))
#define SEC_AUD_FREQ_TIME_aud_freq_time_src(data)                                    ((0x000000C0&(data))>>6)
#define SEC_AUD_FREQ_TIME_get_aud_freq_time(data)                                    ((0x000000C0&(data))>>6)
#define SEC_AUD_FREQ_TIME_Reserved_shift                                             (0)
#define SEC_AUD_FREQ_TIME_Reserved_mask                                              (0x0000003F)
#define SEC_AUD_FREQ_TIME_Reserved(data)                                             (0x0000003F&((data)<<0))
#define SEC_AUD_FREQ_TIME_Reserved_src(data)                                         ((0x0000003F&(data))>>0)
#define SEC_AUD_FREQ_TIME_get_Reserved(data)                                         ((0x0000003F&(data))>>0)


#define SEC_AUD_SAMPLE_CNT_HB                                                        0x9803D53C
#define SEC_AUD_SAMPLE_CNT_HB_reg_addr                                               "0x9803D53C"
#define SEC_AUD_SAMPLE_CNT_HB_reg                                                    0x9803D53C
#define set_SEC_AUD_SAMPLE_CNT_HB_reg(data)   (*((volatile unsigned int*) SEC_AUD_SAMPLE_CNT_HB_reg)=data)
#define get_SEC_AUD_SAMPLE_CNT_HB_reg   (*((volatile unsigned int*) SEC_AUD_SAMPLE_CNT_HB_reg))
#define SEC_AUD_SAMPLE_CNT_HB_inst_adr                                               "0x004F"
#define SEC_AUD_SAMPLE_CNT_HB_inst                                                   0x004F
#define SEC_AUD_SAMPLE_CNT_HB_aud_freq_range_shift                                   (4)
#define SEC_AUD_SAMPLE_CNT_HB_aud_freq_range_mask                                    (0x000000F0)
#define SEC_AUD_SAMPLE_CNT_HB_aud_freq_range(data)                                   (0x000000F0&((data)<<4))
#define SEC_AUD_SAMPLE_CNT_HB_aud_freq_range_src(data)                               ((0x000000F0&(data))>>4)
#define SEC_AUD_SAMPLE_CNT_HB_get_aud_freq_range(data)                               ((0x000000F0&(data))>>4)
#define SEC_AUD_SAMPLE_CNT_HB_aud_sp_cnt118_shift                                    (0)
#define SEC_AUD_SAMPLE_CNT_HB_aud_sp_cnt118_mask                                     (0x0000000F)
#define SEC_AUD_SAMPLE_CNT_HB_aud_sp_cnt118(data)                                    (0x0000000F&((data)<<0))
#define SEC_AUD_SAMPLE_CNT_HB_aud_sp_cnt118_src(data)                                ((0x0000000F&(data))>>0)
#define SEC_AUD_SAMPLE_CNT_HB_get_aud_sp_cnt118(data)                                ((0x0000000F&(data))>>0)


#define SEC_AUD_SAMPLE_CNT_LB                                                        0x9803D540
#define SEC_AUD_SAMPLE_CNT_LB_reg_addr                                               "0x9803D540"
#define SEC_AUD_SAMPLE_CNT_LB_reg                                                    0x9803D540
#define set_SEC_AUD_SAMPLE_CNT_LB_reg(data)   (*((volatile unsigned int*) SEC_AUD_SAMPLE_CNT_LB_reg)=data)
#define get_SEC_AUD_SAMPLE_CNT_LB_reg   (*((volatile unsigned int*) SEC_AUD_SAMPLE_CNT_LB_reg))
#define SEC_AUD_SAMPLE_CNT_LB_inst_adr                                               "0x0050"
#define SEC_AUD_SAMPLE_CNT_LB_inst                                                   0x0050
#define SEC_AUD_SAMPLE_CNT_LB_aud_sp_cnt70_shift                                     (0)
#define SEC_AUD_SAMPLE_CNT_LB_aud_sp_cnt70_mask                                      (0x000000FF)
#define SEC_AUD_SAMPLE_CNT_LB_aud_sp_cnt70(data)                                     (0x000000FF&((data)<<0))
#define SEC_AUD_SAMPLE_CNT_LB_aud_sp_cnt70_src(data)                                 ((0x000000FF&(data))>>0)
#define SEC_AUD_SAMPLE_CNT_LB_get_aud_sp_cnt70(data)                                 ((0x000000FF&(data))>>0)


#define AUD_MBIST_CTRL                                                               0x9803D544
#define AUD_MBIST_CTRL_reg_addr                                                      "0x9803D544"
#define AUD_MBIST_CTRL_reg                                                           0x9803D544
#define set_AUD_MBIST_CTRL_reg(data)   (*((volatile unsigned int*) AUD_MBIST_CTRL_reg)=data)
#define get_AUD_MBIST_CTRL_reg   (*((volatile unsigned int*) AUD_MBIST_CTRL_reg))
#define AUD_MBIST_CTRL_inst_adr                                                      "0x0051"
#define AUD_MBIST_CTRL_inst                                                          0x0051
#define AUD_MBIST_CTRL_bist_mode_sec_shift                                           (7)
#define AUD_MBIST_CTRL_bist_mode_sec_mask                                            (0x00000080)
#define AUD_MBIST_CTRL_bist_mode_sec(data)                                           (0x00000080&((data)<<7))
#define AUD_MBIST_CTRL_bist_mode_sec_src(data)                                       ((0x00000080&(data))>>7)
#define AUD_MBIST_CTRL_get_bist_mode_sec(data)                                       ((0x00000080&(data))>>7)
#define AUD_MBIST_CTRL_bist_done_sec_shift                                           (6)
#define AUD_MBIST_CTRL_bist_done_sec_mask                                            (0x00000040)
#define AUD_MBIST_CTRL_bist_done_sec(data)                                           (0x00000040&((data)<<6))
#define AUD_MBIST_CTRL_bist_done_sec_src(data)                                       ((0x00000040&(data))>>6)
#define AUD_MBIST_CTRL_get_bist_done_sec(data)                                       ((0x00000040&(data))>>6)
#define AUD_MBIST_CTRL_bist_fail_sec_shift                                           (5)
#define AUD_MBIST_CTRL_bist_fail_sec_mask                                            (0x00000020)
#define AUD_MBIST_CTRL_bist_fail_sec(data)                                           (0x00000020&((data)<<5))
#define AUD_MBIST_CTRL_bist_fail_sec_src(data)                                       ((0x00000020&(data))>>5)
#define AUD_MBIST_CTRL_get_bist_fail_sec(data)                                       ((0x00000020&(data))>>5)
#define AUD_MBIST_CTRL_dvse_sec_shift                                                (4)
#define AUD_MBIST_CTRL_dvse_sec_mask                                                 (0x00000010)
#define AUD_MBIST_CTRL_dvse_sec(data)                                                (0x00000010&((data)<<4))
#define AUD_MBIST_CTRL_dvse_sec_src(data)                                            ((0x00000010&(data))>>4)
#define AUD_MBIST_CTRL_get_dvse_sec(data)                                            ((0x00000010&(data))>>4)
#define AUD_MBIST_CTRL_dvs_sec_shift                                                 (0)
#define AUD_MBIST_CTRL_dvs_sec_mask                                                  (0x0000000F)
#define AUD_MBIST_CTRL_dvs_sec(data)                                                 (0x0000000F&((data)<<0))
#define AUD_MBIST_CTRL_dvs_sec_src(data)                                             ((0x0000000F&(data))>>0)
#define AUD_MBIST_CTRL_get_dvs_sec(data)                                             ((0x0000000F&(data))>>0)


#define AUD_DRF_MBIST_CTRL                                                           0x9803D548
#define AUD_DRF_MBIST_CTRL_reg_addr                                                  "0x9803D548"
#define AUD_DRF_MBIST_CTRL_reg                                                       0x9803D548
#define set_AUD_DRF_MBIST_CTRL_reg(data)   (*((volatile unsigned int*) AUD_DRF_MBIST_CTRL_reg)=data)
#define get_AUD_DRF_MBIST_CTRL_reg   (*((volatile unsigned int*) AUD_DRF_MBIST_CTRL_reg))
#define AUD_DRF_MBIST_CTRL_inst_adr                                                  "0x0052"
#define AUD_DRF_MBIST_CTRL_inst                                                      0x0052
#define AUD_DRF_MBIST_CTRL_drf_bist_mode_sec_shift                                   (7)
#define AUD_DRF_MBIST_CTRL_drf_bist_mode_sec_mask                                    (0x00000080)
#define AUD_DRF_MBIST_CTRL_drf_bist_mode_sec(data)                                   (0x00000080&((data)<<7))
#define AUD_DRF_MBIST_CTRL_drf_bist_mode_sec_src(data)                               ((0x00000080&(data))>>7)
#define AUD_DRF_MBIST_CTRL_get_drf_bist_mode_sec(data)                               ((0x00000080&(data))>>7)
#define AUD_DRF_MBIST_CTRL_drf_test_resume_sec_shift                                 (6)
#define AUD_DRF_MBIST_CTRL_drf_test_resume_sec_mask                                  (0x00000040)
#define AUD_DRF_MBIST_CTRL_drf_test_resume_sec(data)                                 (0x00000040&((data)<<6))
#define AUD_DRF_MBIST_CTRL_drf_test_resume_sec_src(data)                             ((0x00000040&(data))>>6)
#define AUD_DRF_MBIST_CTRL_get_drf_test_resume_sec(data)                             ((0x00000040&(data))>>6)
#define AUD_DRF_MBIST_CTRL_drf_start_pause_sec_shift                                 (5)
#define AUD_DRF_MBIST_CTRL_drf_start_pause_sec_mask                                  (0x00000020)
#define AUD_DRF_MBIST_CTRL_drf_start_pause_sec(data)                                 (0x00000020&((data)<<5))
#define AUD_DRF_MBIST_CTRL_drf_start_pause_sec_src(data)                             ((0x00000020&(data))>>5)
#define AUD_DRF_MBIST_CTRL_get_drf_start_pause_sec(data)                             ((0x00000020&(data))>>5)
#define AUD_DRF_MBIST_CTRL_drf_bist_done_sec_shift                                   (4)
#define AUD_DRF_MBIST_CTRL_drf_bist_done_sec_mask                                    (0x00000010)
#define AUD_DRF_MBIST_CTRL_drf_bist_done_sec(data)                                   (0x00000010&((data)<<4))
#define AUD_DRF_MBIST_CTRL_drf_bist_done_sec_src(data)                               ((0x00000010&(data))>>4)
#define AUD_DRF_MBIST_CTRL_get_drf_bist_done_sec(data)                               ((0x00000010&(data))>>4)
#define AUD_DRF_MBIST_CTRL_drf_bist_fail_sec_shift                                   (3)
#define AUD_DRF_MBIST_CTRL_drf_bist_fail_sec_mask                                    (0x00000008)
#define AUD_DRF_MBIST_CTRL_drf_bist_fail_sec(data)                                   (0x00000008&((data)<<3))
#define AUD_DRF_MBIST_CTRL_drf_bist_fail_sec_src(data)                               ((0x00000008&(data))>>3)
#define AUD_DRF_MBIST_CTRL_get_drf_bist_fail_sec(data)                               ((0x00000008&(data))>>3)
#define AUD_DRF_MBIST_CTRL_Reserved_shift                                            (2)
#define AUD_DRF_MBIST_CTRL_Reserved_mask                                             (0x00000004)
#define AUD_DRF_MBIST_CTRL_Reserved(data)                                            (0x00000004&((data)<<2))
#define AUD_DRF_MBIST_CTRL_Reserved_src(data)                                        ((0x00000004&(data))>>2)
#define AUD_DRF_MBIST_CTRL_get_Reserved(data)                                        ((0x00000004&(data))>>2)
#define AUD_DRF_MBIST_CTRL_bist_clk_en_sec_shift                                     (1)
#define AUD_DRF_MBIST_CTRL_bist_clk_en_sec_mask                                      (0x00000002)
#define AUD_DRF_MBIST_CTRL_bist_clk_en_sec(data)                                     (0x00000002&((data)<<1))
#define AUD_DRF_MBIST_CTRL_bist_clk_en_sec_src(data)                                 ((0x00000002&(data))>>1)
#define AUD_DRF_MBIST_CTRL_get_bist_clk_en_sec(data)                                 ((0x00000002&(data))>>1)
#define AUD_DRF_MBIST_CTRL_bist_rst_sec_shift                                        (0)
#define AUD_DRF_MBIST_CTRL_bist_rst_sec_mask                                         (0x00000001)
#define AUD_DRF_MBIST_CTRL_bist_rst_sec(data)                                        (0x00000001&((data)<<0))
#define AUD_DRF_MBIST_CTRL_bist_rst_sec_src(data)                                    ((0x00000001&(data))>>0)
#define AUD_DRF_MBIST_CTRL_get_bist_rst_sec(data)                                    ((0x00000001&(data))>>0)


#define DP_INFO_FM_RSV0                                                              0x9803D54C
#define DP_INFO_FM_RSV0_reg_addr                                                     "0x9803D54C"
#define DP_INFO_FM_RSV0_reg                                                          0x9803D54C
#define set_DP_INFO_FM_RSV0_reg(data)   (*((volatile unsigned int*) DP_INFO_FM_RSV0_reg)=data)
#define get_DP_INFO_FM_RSV0_reg   (*((volatile unsigned int*) DP_INFO_FM_RSV0_reg))
#define DP_INFO_FM_RSV0_inst_adr                                                     "0x0053"
#define DP_INFO_FM_RSV0_inst                                                         0x0053
#define DP_INFO_FM_RSV0_dp_info_fm_rsv0_shift                                        (0)
#define DP_INFO_FM_RSV0_dp_info_fm_rsv0_mask                                         (0x000000FF)
#define DP_INFO_FM_RSV0_dp_info_fm_rsv0(data)                                        (0x000000FF&((data)<<0))
#define DP_INFO_FM_RSV0_dp_info_fm_rsv0_src(data)                                    ((0x000000FF&(data))>>0)
#define DP_INFO_FM_RSV0_get_dp_info_fm_rsv0(data)                                    ((0x000000FF&(data))>>0)


#define DP_INFO_FM_RSV1                                                              0x9803D550
#define DP_INFO_FM_RSV1_reg_addr                                                     "0x9803D550"
#define DP_INFO_FM_RSV1_reg                                                          0x9803D550
#define set_DP_INFO_FM_RSV1_reg(data)   (*((volatile unsigned int*) DP_INFO_FM_RSV1_reg)=data)
#define get_DP_INFO_FM_RSV1_reg   (*((volatile unsigned int*) DP_INFO_FM_RSV1_reg))
#define DP_INFO_FM_RSV1_inst_adr                                                     "0x0054"
#define DP_INFO_FM_RSV1_inst                                                         0x0054
#define DP_INFO_FM_RSV1_dp_info_fm_rsv1_shift                                        (0)
#define DP_INFO_FM_RSV1_dp_info_fm_rsv1_mask                                         (0x000000FF)
#define DP_INFO_FM_RSV1_dp_info_fm_rsv1(data)                                        (0x000000FF&((data)<<0))
#define DP_INFO_FM_RSV1_dp_info_fm_rsv1_src(data)                                    ((0x000000FF&(data))>>0)
#define DP_INFO_FM_RSV1_get_dp_info_fm_rsv1(data)                                    ((0x000000FF&(data))>>0)


#define DP_INFO_FM_ADR                                                               0x9803D554
#define DP_INFO_FM_ADR_reg_addr                                                      "0x9803D554"
#define DP_INFO_FM_ADR_reg                                                           0x9803D554
#define set_DP_INFO_FM_ADR_reg(data)   (*((volatile unsigned int*) DP_INFO_FM_ADR_reg)=data)
#define get_DP_INFO_FM_ADR_reg   (*((volatile unsigned int*) DP_INFO_FM_ADR_reg))
#define DP_INFO_FM_ADR_inst_adr                                                      "0x0055"
#define DP_INFO_FM_ADR_inst                                                          0x0055
#define DP_INFO_FM_ADR_Reserved_shift                                                (7)
#define DP_INFO_FM_ADR_Reserved_mask                                                 (0x00000080)
#define DP_INFO_FM_ADR_Reserved(data)                                                (0x00000080&((data)<<7))
#define DP_INFO_FM_ADR_Reserved_src(data)                                            ((0x00000080&(data))>>7)
#define DP_INFO_FM_ADR_get_Reserved(data)                                            ((0x00000080&(data))>>7)
#define DP_INFO_FM_ADR_dp_info_fm_adr_shift                                          (0)
#define DP_INFO_FM_ADR_dp_info_fm_adr_mask                                           (0x0000007F)
#define DP_INFO_FM_ADR_dp_info_fm_adr(data)                                          (0x0000007F&((data)<<0))
#define DP_INFO_FM_ADR_dp_info_fm_adr_src(data)                                      ((0x0000007F&(data))>>0)
#define DP_INFO_FM_ADR_get_dp_info_fm_adr(data)                                      ((0x0000007F&(data))>>0)


#define DP_INFO_FM_DAT                                                               0x9803D558
#define DP_INFO_FM_DAT_reg_addr                                                      "0x9803D558"
#define DP_INFO_FM_DAT_reg                                                           0x9803D558
#define set_DP_INFO_FM_DAT_reg(data)   (*((volatile unsigned int*) DP_INFO_FM_DAT_reg)=data)
#define get_DP_INFO_FM_DAT_reg   (*((volatile unsigned int*) DP_INFO_FM_DAT_reg))
#define DP_INFO_FM_DAT_inst_adr                                                      "0x0056"
#define DP_INFO_FM_DAT_inst                                                          0x0056
#define DP_INFO_FM_DAT_dp_info_fm_dat_shift                                          (0)
#define DP_INFO_FM_DAT_dp_info_fm_dat_mask                                           (0x000000FF)
#define DP_INFO_FM_DAT_dp_info_fm_dat(data)                                          (0x000000FF&((data)<<0))
#define DP_INFO_FM_DAT_dp_info_fm_dat_src(data)                                      ((0x000000FF&(data))>>0)
#define DP_INFO_FM_DAT_get_dp_info_fm_dat(data)                                      ((0x000000FF&(data))>>0)


#define RESERVED_57                                                                  0x9803D55C
#define RESERVED_57_reg_addr                                                         "0x9803D55C"
#define RESERVED_57_reg                                                              0x9803D55C
#define set_RESERVED_57_reg(data)   (*((volatile unsigned int*) RESERVED_57_reg)=data)
#define get_RESERVED_57_reg   (*((volatile unsigned int*) RESERVED_57_reg))
#define RESERVED_57_inst_adr                                                         "0x0057"
#define RESERVED_57_inst                                                             0x0057
#define RESERVED_57_Reserved_shift                                                   (0)
#define RESERVED_57_Reserved_mask                                                    (0x000000FF)
#define RESERVED_57_Reserved(data)                                                   (0x000000FF&((data)<<0))
#define RESERVED_57_Reserved_src(data)                                               ((0x000000FF&(data))>>0)
#define RESERVED_57_get_Reserved(data)                                               ((0x000000FF&(data))>>0)


#define VSC_RX_DB0                                                                   0x9803D560
#define VSC_RX_DB0_reg_addr                                                          "0x9803D560"
#define VSC_RX_DB0_reg                                                               0x9803D560
#define set_VSC_RX_DB0_reg(data)   (*((volatile unsigned int*) VSC_RX_DB0_reg)=data)
#define get_VSC_RX_DB0_reg   (*((volatile unsigned int*) VSC_RX_DB0_reg))
#define VSC_RX_DB0_inst_adr                                                          "0x0058"
#define VSC_RX_DB0_inst                                                              0x0058
#define VSC_RX_DB0_vsc_rx_db0_shift                                                  (0)
#define VSC_RX_DB0_vsc_rx_db0_mask                                                   (0x000000FF)
#define VSC_RX_DB0_vsc_rx_db0(data)                                                  (0x000000FF&((data)<<0))
#define VSC_RX_DB0_vsc_rx_db0_src(data)                                              ((0x000000FF&(data))>>0)
#define VSC_RX_DB0_get_vsc_rx_db0(data)                                              ((0x000000FF&(data))>>0)


#define VSC_RX_DB1                                                                   0x9803D564
#define VSC_RX_DB1_reg_addr                                                          "0x9803D564"
#define VSC_RX_DB1_reg                                                               0x9803D564
#define set_VSC_RX_DB1_reg(data)   (*((volatile unsigned int*) VSC_RX_DB1_reg)=data)
#define get_VSC_RX_DB1_reg   (*((volatile unsigned int*) VSC_RX_DB1_reg))
#define VSC_RX_DB1_inst_adr                                                          "0x0059"
#define VSC_RX_DB1_inst                                                              0x0059
#define VSC_RX_DB1_vsc_rx_db1_shift                                                  (0)
#define VSC_RX_DB1_vsc_rx_db1_mask                                                   (0x000000FF)
#define VSC_RX_DB1_vsc_rx_db1(data)                                                  (0x000000FF&((data)<<0))
#define VSC_RX_DB1_vsc_rx_db1_src(data)                                              ((0x000000FF&(data))>>0)
#define VSC_RX_DB1_get_vsc_rx_db1(data)                                              ((0x000000FF&(data))>>0)


#define VSC_RX_DB2                                                                   0x9803D568
#define VSC_RX_DB2_reg_addr                                                          "0x9803D568"
#define VSC_RX_DB2_reg                                                               0x9803D568
#define set_VSC_RX_DB2_reg(data)   (*((volatile unsigned int*) VSC_RX_DB2_reg)=data)
#define get_VSC_RX_DB2_reg   (*((volatile unsigned int*) VSC_RX_DB2_reg))
#define VSC_RX_DB2_inst_adr                                                          "0x005A"
#define VSC_RX_DB2_inst                                                              0x005A
#define VSC_RX_DB2_vsc_rx_db2_shift                                                  (0)
#define VSC_RX_DB2_vsc_rx_db2_mask                                                   (0x000000FF)
#define VSC_RX_DB2_vsc_rx_db2(data)                                                  (0x000000FF&((data)<<0))
#define VSC_RX_DB2_vsc_rx_db2_src(data)                                              ((0x000000FF&(data))>>0)
#define VSC_RX_DB2_get_vsc_rx_db2(data)                                              ((0x000000FF&(data))>>0)


#define VSC_RX_DB3                                                                   0x9803D56C
#define VSC_RX_DB3_reg_addr                                                          "0x9803D56C"
#define VSC_RX_DB3_reg                                                               0x9803D56C
#define set_VSC_RX_DB3_reg(data)   (*((volatile unsigned int*) VSC_RX_DB3_reg)=data)
#define get_VSC_RX_DB3_reg   (*((volatile unsigned int*) VSC_RX_DB3_reg))
#define VSC_RX_DB3_inst_adr                                                          "0x005B"
#define VSC_RX_DB3_inst                                                              0x005B
#define VSC_RX_DB3_vsc_rx_db3_shift                                                  (0)
#define VSC_RX_DB3_vsc_rx_db3_mask                                                   (0x000000FF)
#define VSC_RX_DB3_vsc_rx_db3(data)                                                  (0x000000FF&((data)<<0))
#define VSC_RX_DB3_vsc_rx_db3_src(data)                                              ((0x000000FF&(data))>>0)
#define VSC_RX_DB3_get_vsc_rx_db3(data)                                              ((0x000000FF&(data))>>0)


#define VSC_RX_DB4                                                                   0x9803D570
#define VSC_RX_DB4_reg_addr                                                          "0x9803D570"
#define VSC_RX_DB4_reg                                                               0x9803D570
#define set_VSC_RX_DB4_reg(data)   (*((volatile unsigned int*) VSC_RX_DB4_reg)=data)
#define get_VSC_RX_DB4_reg   (*((volatile unsigned int*) VSC_RX_DB4_reg))
#define VSC_RX_DB4_inst_adr                                                          "0x005C"
#define VSC_RX_DB4_inst                                                              0x005C
#define VSC_RX_DB4_vsc_rx_db4_shift                                                  (0)
#define VSC_RX_DB4_vsc_rx_db4_mask                                                   (0x000000FF)
#define VSC_RX_DB4_vsc_rx_db4(data)                                                  (0x000000FF&((data)<<0))
#define VSC_RX_DB4_vsc_rx_db4_src(data)                                              ((0x000000FF&(data))>>0)
#define VSC_RX_DB4_get_vsc_rx_db4(data)                                              ((0x000000FF&(data))>>0)


#define VSC_RX_DB5                                                                   0x9803D574
#define VSC_RX_DB5_reg_addr                                                          "0x9803D574"
#define VSC_RX_DB5_reg                                                               0x9803D574
#define set_VSC_RX_DB5_reg(data)   (*((volatile unsigned int*) VSC_RX_DB5_reg)=data)
#define get_VSC_RX_DB5_reg   (*((volatile unsigned int*) VSC_RX_DB5_reg))
#define VSC_RX_DB5_inst_adr                                                          "0x005D"
#define VSC_RX_DB5_inst                                                              0x005D
#define VSC_RX_DB5_vsc_rx_db5_shift                                                  (0)
#define VSC_RX_DB5_vsc_rx_db5_mask                                                   (0x000000FF)
#define VSC_RX_DB5_vsc_rx_db5(data)                                                  (0x000000FF&((data)<<0))
#define VSC_RX_DB5_vsc_rx_db5_src(data)                                              ((0x000000FF&(data))>>0)
#define VSC_RX_DB5_get_vsc_rx_db5(data)                                              ((0x000000FF&(data))>>0)


#define VSC_RX_DB6                                                                   0x9803D578
#define VSC_RX_DB6_reg_addr                                                          "0x9803D578"
#define VSC_RX_DB6_reg                                                               0x9803D578
#define set_VSC_RX_DB6_reg(data)   (*((volatile unsigned int*) VSC_RX_DB6_reg)=data)
#define get_VSC_RX_DB6_reg   (*((volatile unsigned int*) VSC_RX_DB6_reg))
#define VSC_RX_DB6_inst_adr                                                          "0x005E"
#define VSC_RX_DB6_inst                                                              0x005E
#define VSC_RX_DB6_vsc_rx_db6_shift                                                  (0)
#define VSC_RX_DB6_vsc_rx_db6_mask                                                   (0x000000FF)
#define VSC_RX_DB6_vsc_rx_db6(data)                                                  (0x000000FF&((data)<<0))
#define VSC_RX_DB6_vsc_rx_db6_src(data)                                              ((0x000000FF&(data))>>0)
#define VSC_RX_DB6_get_vsc_rx_db6(data)                                              ((0x000000FF&(data))>>0)


#define VSC_RX_DB7                                                                   0x9803D57C
#define VSC_RX_DB7_reg_addr                                                          "0x9803D57C"
#define VSC_RX_DB7_reg                                                               0x9803D57C
#define set_VSC_RX_DB7_reg(data)   (*((volatile unsigned int*) VSC_RX_DB7_reg)=data)
#define get_VSC_RX_DB7_reg   (*((volatile unsigned int*) VSC_RX_DB7_reg))
#define VSC_RX_DB7_inst_adr                                                          "0x005F"
#define VSC_RX_DB7_inst                                                              0x005F
#define VSC_RX_DB7_vsc_rx_db7_shift                                                  (0)
#define VSC_RX_DB7_vsc_rx_db7_mask                                                   (0x000000FF)
#define VSC_RX_DB7_vsc_rx_db7(data)                                                  (0x000000FF&((data)<<0))
#define VSC_RX_DB7_vsc_rx_db7_src(data)                                              ((0x000000FF&(data))>>0)
#define VSC_RX_DB7_get_vsc_rx_db7(data)                                              ((0x000000FF&(data))>>0)


#define AUD_FREQ_TH_0                                                                0x9803D580
#define AUD_FREQ_TH_0_reg_addr                                                       "0x9803D580"
#define AUD_FREQ_TH_0_reg                                                            0x9803D580
#define set_AUD_FREQ_TH_0_reg(data)   (*((volatile unsigned int*) AUD_FREQ_TH_0_reg)=data)
#define get_AUD_FREQ_TH_0_reg   (*((volatile unsigned int*) AUD_FREQ_TH_0_reg))
#define AUD_FREQ_TH_0_inst_adr                                                       "0x0060"
#define AUD_FREQ_TH_0_inst                                                           0x0060
#define AUD_FREQ_TH_0_aud_th_noaudio118_shift                                        (4)
#define AUD_FREQ_TH_0_aud_th_noaudio118_mask                                         (0x000000F0)
#define AUD_FREQ_TH_0_aud_th_noaudio118(data)                                        (0x000000F0&((data)<<4))
#define AUD_FREQ_TH_0_aud_th_noaudio118_src(data)                                    ((0x000000F0&(data))>>4)
#define AUD_FREQ_TH_0_get_aud_th_noaudio118(data)                                    ((0x000000F0&(data))>>4)
#define AUD_FREQ_TH_0_aud_th_group1118_shift                                         (0)
#define AUD_FREQ_TH_0_aud_th_group1118_mask                                          (0x0000000F)
#define AUD_FREQ_TH_0_aud_th_group1118(data)                                         (0x0000000F&((data)<<0))
#define AUD_FREQ_TH_0_aud_th_group1118_src(data)                                     ((0x0000000F&(data))>>0)
#define AUD_FREQ_TH_0_get_aud_th_group1118(data)                                     ((0x0000000F&(data))>>0)


#define AUD_FREQ_TH_1                                                                0x9803D584
#define AUD_FREQ_TH_1_reg_addr                                                       "0x9803D584"
#define AUD_FREQ_TH_1_reg                                                            0x9803D584
#define set_AUD_FREQ_TH_1_reg(data)   (*((volatile unsigned int*) AUD_FREQ_TH_1_reg)=data)
#define get_AUD_FREQ_TH_1_reg   (*((volatile unsigned int*) AUD_FREQ_TH_1_reg))
#define AUD_FREQ_TH_1_inst_adr                                                       "0x0061"
#define AUD_FREQ_TH_1_inst                                                           0x0061
#define AUD_FREQ_TH_1_aud_th_group2118_shift                                         (4)
#define AUD_FREQ_TH_1_aud_th_group2118_mask                                          (0x000000F0)
#define AUD_FREQ_TH_1_aud_th_group2118(data)                                         (0x000000F0&((data)<<4))
#define AUD_FREQ_TH_1_aud_th_group2118_src(data)                                     ((0x000000F0&(data))>>4)
#define AUD_FREQ_TH_1_get_aud_th_group2118(data)                                     ((0x000000F0&(data))>>4)
#define AUD_FREQ_TH_1_aud_th_group3118_shift                                         (0)
#define AUD_FREQ_TH_1_aud_th_group3118_mask                                          (0x0000000F)
#define AUD_FREQ_TH_1_aud_th_group3118(data)                                         (0x0000000F&((data)<<0))
#define AUD_FREQ_TH_1_aud_th_group3118_src(data)                                     ((0x0000000F&(data))>>0)
#define AUD_FREQ_TH_1_get_aud_th_group3118(data)                                     ((0x0000000F&(data))>>0)


#define AUD_FREQ_TH_2                                                                0x9803D588
#define AUD_FREQ_TH_2_reg_addr                                                       "0x9803D588"
#define AUD_FREQ_TH_2_reg                                                            0x9803D588
#define set_AUD_FREQ_TH_2_reg(data)   (*((volatile unsigned int*) AUD_FREQ_TH_2_reg)=data)
#define get_AUD_FREQ_TH_2_reg   (*((volatile unsigned int*) AUD_FREQ_TH_2_reg))
#define AUD_FREQ_TH_2_inst_adr                                                       "0x0062"
#define AUD_FREQ_TH_2_inst                                                           0x0062
#define AUD_FREQ_TH_2_aud_th_noaudio70_shift                                         (0)
#define AUD_FREQ_TH_2_aud_th_noaudio70_mask                                          (0x000000FF)
#define AUD_FREQ_TH_2_aud_th_noaudio70(data)                                         (0x000000FF&((data)<<0))
#define AUD_FREQ_TH_2_aud_th_noaudio70_src(data)                                     ((0x000000FF&(data))>>0)
#define AUD_FREQ_TH_2_get_aud_th_noaudio70(data)                                     ((0x000000FF&(data))>>0)


#define AUD_FREQ_TH_3                                                                0x9803D58C
#define AUD_FREQ_TH_3_reg_addr                                                       "0x9803D58C"
#define AUD_FREQ_TH_3_reg                                                            0x9803D58C
#define set_AUD_FREQ_TH_3_reg(data)   (*((volatile unsigned int*) AUD_FREQ_TH_3_reg)=data)
#define get_AUD_FREQ_TH_3_reg   (*((volatile unsigned int*) AUD_FREQ_TH_3_reg))
#define AUD_FREQ_TH_3_inst_adr                                                       "0x0063"
#define AUD_FREQ_TH_3_inst                                                           0x0063
#define AUD_FREQ_TH_3_aud_th_group170_shift                                          (0)
#define AUD_FREQ_TH_3_aud_th_group170_mask                                           (0x000000FF)
#define AUD_FREQ_TH_3_aud_th_group170(data)                                          (0x000000FF&((data)<<0))
#define AUD_FREQ_TH_3_aud_th_group170_src(data)                                      ((0x000000FF&(data))>>0)
#define AUD_FREQ_TH_3_get_aud_th_group170(data)                                      ((0x000000FF&(data))>>0)


#define AUD_FREQ_TH_4                                                                0x9803D590
#define AUD_FREQ_TH_4_reg_addr                                                       "0x9803D590"
#define AUD_FREQ_TH_4_reg                                                            0x9803D590
#define set_AUD_FREQ_TH_4_reg(data)   (*((volatile unsigned int*) AUD_FREQ_TH_4_reg)=data)
#define get_AUD_FREQ_TH_4_reg   (*((volatile unsigned int*) AUD_FREQ_TH_4_reg))
#define AUD_FREQ_TH_4_inst_adr                                                       "0x0064"
#define AUD_FREQ_TH_4_inst                                                           0x0064
#define AUD_FREQ_TH_4_aud_th_group270_shift                                          (0)
#define AUD_FREQ_TH_4_aud_th_group270_mask                                           (0x000000FF)
#define AUD_FREQ_TH_4_aud_th_group270(data)                                          (0x000000FF&((data)<<0))
#define AUD_FREQ_TH_4_aud_th_group270_src(data)                                      ((0x000000FF&(data))>>0)
#define AUD_FREQ_TH_4_get_aud_th_group270(data)                                      ((0x000000FF&(data))>>0)


#define AUD_FREQ_TH_5                                                                0x9803D594
#define AUD_FREQ_TH_5_reg_addr                                                       "0x9803D594"
#define AUD_FREQ_TH_5_reg                                                            0x9803D594
#define set_AUD_FREQ_TH_5_reg(data)   (*((volatile unsigned int*) AUD_FREQ_TH_5_reg)=data)
#define get_AUD_FREQ_TH_5_reg   (*((volatile unsigned int*) AUD_FREQ_TH_5_reg))
#define AUD_FREQ_TH_5_inst_adr                                                       "0x0065"
#define AUD_FREQ_TH_5_inst                                                           0x0065
#define AUD_FREQ_TH_5_aud_th_group370_shift                                          (0)
#define AUD_FREQ_TH_5_aud_th_group370_mask                                           (0x000000FF)
#define AUD_FREQ_TH_5_aud_th_group370(data)                                          (0x000000FF&((data)<<0))
#define AUD_FREQ_TH_5_aud_th_group370_src(data)                                      ((0x000000FF&(data))>>0)
#define AUD_FREQ_TH_5_get_aud_th_group370(data)                                      ((0x000000FF&(data))>>0)


#define AUD_FREQ_TH_6                                                                0x9803D598
#define AUD_FREQ_TH_6_reg_addr                                                       "0x9803D598"
#define AUD_FREQ_TH_6_reg                                                            0x9803D598
#define set_AUD_FREQ_TH_6_reg(data)   (*((volatile unsigned int*) AUD_FREQ_TH_6_reg)=data)
#define get_AUD_FREQ_TH_6_reg   (*((volatile unsigned int*) AUD_FREQ_TH_6_reg))
#define AUD_FREQ_TH_6_inst_adr                                                       "0x0066"
#define AUD_FREQ_TH_6_inst                                                           0x0066
#define AUD_FREQ_TH_6_aud_range_th_shift                                             (0)
#define AUD_FREQ_TH_6_aud_range_th_mask                                              (0x000000FF)
#define AUD_FREQ_TH_6_aud_range_th(data)                                             (0x000000FF&((data)<<0))
#define AUD_FREQ_TH_6_aud_range_th_src(data)                                         ((0x000000FF&(data))>>0)
#define AUD_FREQ_TH_6_get_aud_range_th(data)                                         ((0x000000FF&(data))>>0)


#define RESERVED_67                                                                  0x9803D59C
#define RESERVED_67_reg_addr                                                         "0x9803D59C"
#define RESERVED_67_reg                                                              0x9803D59C
#define set_RESERVED_67_reg(data)   (*((volatile unsigned int*) RESERVED_67_reg)=data)
#define get_RESERVED_67_reg   (*((volatile unsigned int*) RESERVED_67_reg))
#define RESERVED_67_inst_adr                                                         "0x0067"
#define RESERVED_67_inst                                                             0x0067
#define RESERVED_67_Reserved_shift                                                   (0)
#define RESERVED_67_Reserved_mask                                                    (0x000000FF)
#define RESERVED_67_Reserved(data)                                                   (0x000000FF&((data)<<0))
#define RESERVED_67_Reserved_src(data)                                               ((0x000000FF&(data))>>0)
#define RESERVED_67_get_Reserved(data)                                               ((0x000000FF&(data))>>0)


#define RESERVED_68                                                                  0x9803D5A0
#define RESERVED_68_reg_addr                                                         "0x9803D5A0"
#define RESERVED_68_reg                                                              0x9803D5A0
#define set_RESERVED_68_reg(data)   (*((volatile unsigned int*) RESERVED_68_reg)=data)
#define get_RESERVED_68_reg   (*((volatile unsigned int*) RESERVED_68_reg))
#define RESERVED_68_inst_adr                                                         "0x0068"
#define RESERVED_68_inst                                                             0x0068
#define RESERVED_68_Reserved_shift                                                   (0)
#define RESERVED_68_Reserved_mask                                                    (0x000000FF)
#define RESERVED_68_Reserved(data)                                                   (0x000000FF&((data)<<0))
#define RESERVED_68_Reserved_src(data)                                               ((0x000000FF&(data))>>0)
#define RESERVED_68_get_Reserved(data)                                               ((0x000000FF&(data))>>0)


#define RESERVED_69                                                                  0x9803D5A4
#define RESERVED_69_reg_addr                                                         "0x9803D5A4"
#define RESERVED_69_reg                                                              0x9803D5A4
#define set_RESERVED_69_reg(data)   (*((volatile unsigned int*) RESERVED_69_reg)=data)
#define get_RESERVED_69_reg   (*((volatile unsigned int*) RESERVED_69_reg))
#define RESERVED_69_inst_adr                                                         "0x0069"
#define RESERVED_69_inst                                                             0x0069
#define RESERVED_69_Reserved_shift                                                   (0)
#define RESERVED_69_Reserved_mask                                                    (0x000000FF)
#define RESERVED_69_Reserved(data)                                                   (0x000000FF&((data)<<0))
#define RESERVED_69_Reserved_src(data)                                               ((0x000000FF&(data))>>0)
#define RESERVED_69_get_Reserved(data)                                               ((0x000000FF&(data))>>0)


#define VSC_CTRL_0                                                                   0x9803D5A8
#define VSC_CTRL_0_reg_addr                                                          "0x9803D5A8"
#define VSC_CTRL_0_reg                                                               0x9803D5A8
#define set_VSC_CTRL_0_reg(data)   (*((volatile unsigned int*) VSC_CTRL_0_reg)=data)
#define get_VSC_CTRL_0_reg   (*((volatile unsigned int*) VSC_CTRL_0_reg))
#define VSC_CTRL_0_inst_adr                                                          "0x006A"
#define VSC_CTRL_0_inst                                                              0x006A
#define VSC_CTRL_0_vsc_rx_hb23_care_shift                                            (7)
#define VSC_CTRL_0_vsc_rx_hb23_care_mask                                             (0x00000080)
#define VSC_CTRL_0_vsc_rx_hb23_care(data)                                            (0x00000080&((data)<<7))
#define VSC_CTRL_0_vsc_rx_hb23_care_src(data)                                        ((0x00000080&(data))>>7)
#define VSC_CTRL_0_get_vsc_rx_hb23_care(data)                                        ((0x00000080&(data))>>7)
#define VSC_CTRL_0_Reserved_shift                                                    (4)
#define VSC_CTRL_0_Reserved_mask                                                     (0x00000070)
#define VSC_CTRL_0_Reserved(data)                                                    (0x00000070&((data)<<4))
#define VSC_CTRL_0_Reserved_src(data)                                                ((0x00000070&(data))>>4)
#define VSC_CTRL_0_get_Reserved(data)                                                ((0x00000070&(data))>>4)
#define VSC_CTRL_0_psr_int_en_shift                                                  (3)
#define VSC_CTRL_0_psr_int_en_mask                                                   (0x00000008)
#define VSC_CTRL_0_psr_int_en(data)                                                  (0x00000008&((data)<<3))
#define VSC_CTRL_0_psr_int_en_src(data)                                              ((0x00000008&(data))>>3)
#define VSC_CTRL_0_get_psr_int_en(data)                                              ((0x00000008&(data))>>3)
#define VSC_CTRL_0_psr_int_shift                                                     (2)
#define VSC_CTRL_0_psr_int_mask                                                      (0x00000004)
#define VSC_CTRL_0_psr_int(data)                                                     (0x00000004&((data)<<2))
#define VSC_CTRL_0_psr_int_src(data)                                                 ((0x00000004&(data))>>2)
#define VSC_CTRL_0_get_psr_int(data)                                                 ((0x00000004&(data))>>2)
#define VSC_CTRL_0_vsc_rx_3d_int_en_shift                                            (1)
#define VSC_CTRL_0_vsc_rx_3d_int_en_mask                                             (0x00000002)
#define VSC_CTRL_0_vsc_rx_3d_int_en(data)                                            (0x00000002&((data)<<1))
#define VSC_CTRL_0_vsc_rx_3d_int_en_src(data)                                        ((0x00000002&(data))>>1)
#define VSC_CTRL_0_get_vsc_rx_3d_int_en(data)                                        ((0x00000002&(data))>>1)
#define VSC_CTRL_0_vsc_3d_chg_shift                                                  (0)
#define VSC_CTRL_0_vsc_3d_chg_mask                                                   (0x00000001)
#define VSC_CTRL_0_vsc_3d_chg(data)                                                  (0x00000001&((data)<<0))
#define VSC_CTRL_0_vsc_3d_chg_src(data)                                              ((0x00000001&(data))>>0)
#define VSC_CTRL_0_get_vsc_3d_chg(data)                                              ((0x00000001&(data))>>0)


#define VSC_RX_HB0                                                                   0x9803D5AC
#define VSC_RX_HB0_reg_addr                                                          "0x9803D5AC"
#define VSC_RX_HB0_reg                                                               0x9803D5AC
#define set_VSC_RX_HB0_reg(data)   (*((volatile unsigned int*) VSC_RX_HB0_reg)=data)
#define get_VSC_RX_HB0_reg   (*((volatile unsigned int*) VSC_RX_HB0_reg))
#define VSC_RX_HB0_inst_adr                                                          "0x006B"
#define VSC_RX_HB0_inst                                                              0x006B
#define VSC_RX_HB0_vsc_rx_hb0_shift                                                  (0)
#define VSC_RX_HB0_vsc_rx_hb0_mask                                                   (0x000000FF)
#define VSC_RX_HB0_vsc_rx_hb0(data)                                                  (0x000000FF&((data)<<0))
#define VSC_RX_HB0_vsc_rx_hb0_src(data)                                              ((0x000000FF&(data))>>0)
#define VSC_RX_HB0_get_vsc_rx_hb0(data)                                              ((0x000000FF&(data))>>0)


#define VSC_RX_HB1                                                                   0x9803D5B0
#define VSC_RX_HB1_reg_addr                                                          "0x9803D5B0"
#define VSC_RX_HB1_reg                                                               0x9803D5B0
#define set_VSC_RX_HB1_reg(data)   (*((volatile unsigned int*) VSC_RX_HB1_reg)=data)
#define get_VSC_RX_HB1_reg   (*((volatile unsigned int*) VSC_RX_HB1_reg))
#define VSC_RX_HB1_inst_adr                                                          "0x006C"
#define VSC_RX_HB1_inst                                                              0x006C
#define VSC_RX_HB1_vsc_rx_hb1_shift                                                  (0)
#define VSC_RX_HB1_vsc_rx_hb1_mask                                                   (0x000000FF)
#define VSC_RX_HB1_vsc_rx_hb1(data)                                                  (0x000000FF&((data)<<0))
#define VSC_RX_HB1_vsc_rx_hb1_src(data)                                              ((0x000000FF&(data))>>0)
#define VSC_RX_HB1_get_vsc_rx_hb1(data)                                              ((0x000000FF&(data))>>0)


#define VSC_RX_HB2                                                                   0x9803D5B4
#define VSC_RX_HB2_reg_addr                                                          "0x9803D5B4"
#define VSC_RX_HB2_reg                                                               0x9803D5B4
#define set_VSC_RX_HB2_reg(data)   (*((volatile unsigned int*) VSC_RX_HB2_reg)=data)
#define get_VSC_RX_HB2_reg   (*((volatile unsigned int*) VSC_RX_HB2_reg))
#define VSC_RX_HB2_inst_adr                                                          "0x006D"
#define VSC_RX_HB2_inst                                                              0x006D
#define VSC_RX_HB2_vsc_rx_hb2_shift                                                  (0)
#define VSC_RX_HB2_vsc_rx_hb2_mask                                                   (0x000000FF)
#define VSC_RX_HB2_vsc_rx_hb2(data)                                                  (0x000000FF&((data)<<0))
#define VSC_RX_HB2_vsc_rx_hb2_src(data)                                              ((0x000000FF&(data))>>0)
#define VSC_RX_HB2_get_vsc_rx_hb2(data)                                              ((0x000000FF&(data))>>0)


#define VSC_RX_HB3                                                                   0x9803D5B8
#define VSC_RX_HB3_reg_addr                                                          "0x9803D5B8"
#define VSC_RX_HB3_reg                                                               0x9803D5B8
#define set_VSC_RX_HB3_reg(data)   (*((volatile unsigned int*) VSC_RX_HB3_reg)=data)
#define get_VSC_RX_HB3_reg   (*((volatile unsigned int*) VSC_RX_HB3_reg))
#define VSC_RX_HB3_inst_adr                                                          "0x006E"
#define VSC_RX_HB3_inst                                                              0x006E
#define VSC_RX_HB3_vsc_rx_hb3_shift                                                  (0)
#define VSC_RX_HB3_vsc_rx_hb3_mask                                                   (0x000000FF)
#define VSC_RX_HB3_vsc_rx_hb3(data)                                                  (0x000000FF&((data)<<0))
#define VSC_RX_HB3_vsc_rx_hb3_src(data)                                              ((0x000000FF&(data))>>0)
#define VSC_RX_HB3_get_vsc_rx_hb3(data)                                              ((0x000000FF&(data))>>0)


#define SEC_AWD_CTRL                                                                 0x9803D5C0
#define SEC_AWD_CTRL_reg_addr                                                        "0x9803D5C0"
#define SEC_AWD_CTRL_reg                                                             0x9803D5C0
#define set_SEC_AWD_CTRL_reg(data)   (*((volatile unsigned int*) SEC_AWD_CTRL_reg)=data)
#define get_SEC_AWD_CTRL_reg   (*((volatile unsigned int*) SEC_AWD_CTRL_reg))
#define SEC_AWD_CTRL_inst_adr                                                        "0x0070"
#define SEC_AWD_CTRL_inst                                                            0x0070
#define SEC_AWD_CTRL_Reserved_shift                                                  (7)
#define SEC_AWD_CTRL_Reserved_mask                                                   (0x00000080)
#define SEC_AWD_CTRL_Reserved(data)                                                  (0x00000080&((data)<<7))
#define SEC_AWD_CTRL_Reserved_src(data)                                              ((0x00000080&(data))>>7)
#define SEC_AWD_CTRL_get_Reserved(data)                                              ((0x00000080&(data))>>7)
#define SEC_AWD_CTRL_awd_vbid4_chg_en_shift                                          (6)
#define SEC_AWD_CTRL_awd_vbid4_chg_en_mask                                           (0x00000040)
#define SEC_AWD_CTRL_awd_vbid4_chg_en(data)                                          (0x00000040&((data)<<6))
#define SEC_AWD_CTRL_awd_vbid4_chg_en_src(data)                                      ((0x00000040&(data))>>6)
#define SEC_AWD_CTRL_get_awd_vbid4_chg_en(data)                                      ((0x00000040&(data))>>6)
#define SEC_AWD_CTRL_awd_vbid3_chg_en_shift                                          (5)
#define SEC_AWD_CTRL_awd_vbid3_chg_en_mask                                           (0x00000020)
#define SEC_AWD_CTRL_awd_vbid3_chg_en(data)                                          (0x00000020&((data)<<5))
#define SEC_AWD_CTRL_awd_vbid3_chg_en_src(data)                                      ((0x00000020&(data))>>5)
#define SEC_AWD_CTRL_get_awd_vbid3_chg_en(data)                                      ((0x00000020&(data))>>5)
#define SEC_AWD_CTRL_awd_vbid2_chg_en_shift                                          (4)
#define SEC_AWD_CTRL_awd_vbid2_chg_en_mask                                           (0x00000010)
#define SEC_AWD_CTRL_awd_vbid2_chg_en(data)                                          (0x00000010&((data)<<4))
#define SEC_AWD_CTRL_awd_vbid2_chg_en_src(data)                                      ((0x00000010&(data))>>4)
#define SEC_AWD_CTRL_get_awd_vbid2_chg_en(data)                                      ((0x00000010&(data))>>4)
#define SEC_AWD_CTRL_awd_aud_freq_chg_en_shift                                       (3)
#define SEC_AWD_CTRL_awd_aud_freq_chg_en_mask                                        (0x00000008)
#define SEC_AWD_CTRL_awd_aud_freq_chg_en(data)                                       (0x00000008&((data)<<3))
#define SEC_AWD_CTRL_awd_aud_freq_chg_en_src(data)                                   ((0x00000008&(data))>>3)
#define SEC_AWD_CTRL_get_awd_aud_freq_chg_en(data)                                   ((0x00000008&(data))>>3)
#define SEC_AWD_CTRL_awd_mst_sec_packet_id_chg_en_shift                              (2)
#define SEC_AWD_CTRL_awd_mst_sec_packet_id_chg_en_mask                               (0x00000004)
#define SEC_AWD_CTRL_awd_mst_sec_packet_id_chg_en(data)                              (0x00000004&((data)<<2))
#define SEC_AWD_CTRL_awd_mst_sec_packet_id_chg_en_src(data)                          ((0x00000004&(data))>>2)
#define SEC_AWD_CTRL_get_awd_mst_sec_packet_id_chg_en(data)                          ((0x00000004&(data))>>2)
#define SEC_AWD_CTRL_awd_mst_coding_type_chg_en_shift                                (1)
#define SEC_AWD_CTRL_awd_mst_coding_type_chg_en_mask                                 (0x00000002)
#define SEC_AWD_CTRL_awd_mst_coding_type_chg_en(data)                                (0x00000002&((data)<<1))
#define SEC_AWD_CTRL_awd_mst_coding_type_chg_en_src(data)                            ((0x00000002&(data))>>1)
#define SEC_AWD_CTRL_get_awd_mst_coding_type_chg_en(data)                            ((0x00000002&(data))>>1)
#define SEC_AWD_CTRL_awd_mst_channel_cnt_chg_en_shift                                (0)
#define SEC_AWD_CTRL_awd_mst_channel_cnt_chg_en_mask                                 (0x00000001)
#define SEC_AWD_CTRL_awd_mst_channel_cnt_chg_en(data)                                (0x00000001&((data)<<0))
#define SEC_AWD_CTRL_awd_mst_channel_cnt_chg_en_src(data)                            ((0x00000001&(data))>>0)
#define SEC_AWD_CTRL_get_awd_mst_channel_cnt_chg_en(data)                            ((0x00000001&(data))>>0)


#define SEC_AWD_STATUS_0                                                             0x9803D5C4
#define SEC_AWD_STATUS_0_reg_addr                                                    "0x9803D5C4"
#define SEC_AWD_STATUS_0_reg                                                         0x9803D5C4
#define set_SEC_AWD_STATUS_0_reg(data)   (*((volatile unsigned int*) SEC_AWD_STATUS_0_reg)=data)
#define get_SEC_AWD_STATUS_0_reg   (*((volatile unsigned int*) SEC_AWD_STATUS_0_reg))
#define SEC_AWD_STATUS_0_inst_adr                                                    "0x0071"
#define SEC_AWD_STATUS_0_inst                                                        0x0071
#define SEC_AWD_STATUS_0_Reserved_shift                                              (6)
#define SEC_AWD_STATUS_0_Reserved_mask                                               (0x000000C0)
#define SEC_AWD_STATUS_0_Reserved(data)                                              (0x000000C0&((data)<<6))
#define SEC_AWD_STATUS_0_Reserved_src(data)                                          ((0x000000C0&(data))>>6)
#define SEC_AWD_STATUS_0_get_Reserved(data)                                          ((0x000000C0&(data))>>6)
#define SEC_AWD_STATUS_0_ats_sent_shift                                              (5)
#define SEC_AWD_STATUS_0_ats_sent_mask                                               (0x00000020)
#define SEC_AWD_STATUS_0_ats_sent(data)                                              (0x00000020&((data)<<5))
#define SEC_AWD_STATUS_0_ats_sent_src(data)                                          ((0x00000020&(data))>>5)
#define SEC_AWD_STATUS_0_get_ats_sent(data)                                          ((0x00000020&(data))>>5)
#define SEC_AWD_STATUS_0_info_aud_sent_shift                                         (4)
#define SEC_AWD_STATUS_0_info_aud_sent_mask                                          (0x00000010)
#define SEC_AWD_STATUS_0_info_aud_sent(data)                                         (0x00000010&((data)<<4))
#define SEC_AWD_STATUS_0_info_aud_sent_src(data)                                     ((0x00000010&(data))>>4)
#define SEC_AWD_STATUS_0_get_info_aud_sent(data)                                     ((0x00000010&(data))>>4)
#define SEC_AWD_STATUS_0_aud_freq_chg_shift                                          (3)
#define SEC_AWD_STATUS_0_aud_freq_chg_mask                                           (0x00000008)
#define SEC_AWD_STATUS_0_aud_freq_chg(data)                                          (0x00000008&((data)<<3))
#define SEC_AWD_STATUS_0_aud_freq_chg_src(data)                                      ((0x00000008&(data))>>3)
#define SEC_AWD_STATUS_0_get_aud_freq_chg(data)                                      ((0x00000008&(data))>>3)
#define SEC_AWD_STATUS_0_mst_sec_packet_id_chg_shift                                 (2)
#define SEC_AWD_STATUS_0_mst_sec_packet_id_chg_mask                                  (0x00000004)
#define SEC_AWD_STATUS_0_mst_sec_packet_id_chg(data)                                 (0x00000004&((data)<<2))
#define SEC_AWD_STATUS_0_mst_sec_packet_id_chg_src(data)                             ((0x00000004&(data))>>2)
#define SEC_AWD_STATUS_0_get_mst_sec_packet_id_chg(data)                             ((0x00000004&(data))>>2)
#define SEC_AWD_STATUS_0_mst_coding_type_chg_shift                                   (1)
#define SEC_AWD_STATUS_0_mst_coding_type_chg_mask                                    (0x00000002)
#define SEC_AWD_STATUS_0_mst_coding_type_chg(data)                                   (0x00000002&((data)<<1))
#define SEC_AWD_STATUS_0_mst_coding_type_chg_src(data)                               ((0x00000002&(data))>>1)
#define SEC_AWD_STATUS_0_get_mst_coding_type_chg(data)                               ((0x00000002&(data))>>1)
#define SEC_AWD_STATUS_0_mst_channel_cnt_chg_shift                                   (0)
#define SEC_AWD_STATUS_0_mst_channel_cnt_chg_mask                                    (0x00000001)
#define SEC_AWD_STATUS_0_mst_channel_cnt_chg(data)                                   (0x00000001&((data)<<0))
#define SEC_AWD_STATUS_0_mst_channel_cnt_chg_src(data)                               ((0x00000001&(data))>>0)
#define SEC_AWD_STATUS_0_get_mst_channel_cnt_chg(data)                               ((0x00000001&(data))>>0)


#define SEC_IRQ_CTRL0                                                                0x9803D5C8
#define SEC_IRQ_CTRL0_reg_addr                                                       "0x9803D5C8"
#define SEC_IRQ_CTRL0_reg                                                            0x9803D5C8
#define set_SEC_IRQ_CTRL0_reg(data)   (*((volatile unsigned int*) SEC_IRQ_CTRL0_reg)=data)
#define get_SEC_IRQ_CTRL0_reg   (*((volatile unsigned int*) SEC_IRQ_CTRL0_reg))
#define SEC_IRQ_CTRL0_inst_adr                                                       "0x0072"
#define SEC_IRQ_CTRL0_inst                                                           0x0072
#define SEC_IRQ_CTRL0_Reserved_shift                                                 (7)
#define SEC_IRQ_CTRL0_Reserved_mask                                                  (0x00000080)
#define SEC_IRQ_CTRL0_Reserved(data)                                                 (0x00000080&((data)<<7))
#define SEC_IRQ_CTRL0_Reserved_src(data)                                             ((0x00000080&(data))>>7)
#define SEC_IRQ_CTRL0_get_Reserved(data)                                             ((0x00000080&(data))>>7)
#define SEC_IRQ_CTRL0_irq_vbid4_chg_en_shift                                         (6)
#define SEC_IRQ_CTRL0_irq_vbid4_chg_en_mask                                          (0x00000040)
#define SEC_IRQ_CTRL0_irq_vbid4_chg_en(data)                                         (0x00000040&((data)<<6))
#define SEC_IRQ_CTRL0_irq_vbid4_chg_en_src(data)                                     ((0x00000040&(data))>>6)
#define SEC_IRQ_CTRL0_get_irq_vbid4_chg_en(data)                                     ((0x00000040&(data))>>6)
#define SEC_IRQ_CTRL0_irq_vbid3_chg_en_shift                                         (5)
#define SEC_IRQ_CTRL0_irq_vbid3_chg_en_mask                                          (0x00000020)
#define SEC_IRQ_CTRL0_irq_vbid3_chg_en(data)                                         (0x00000020&((data)<<5))
#define SEC_IRQ_CTRL0_irq_vbid3_chg_en_src(data)                                     ((0x00000020&(data))>>5)
#define SEC_IRQ_CTRL0_get_irq_vbid3_chg_en(data)                                     ((0x00000020&(data))>>5)
#define SEC_IRQ_CTRL0_irq_vbid2_chg_en_shift                                         (4)
#define SEC_IRQ_CTRL0_irq_vbid2_chg_en_mask                                          (0x00000010)
#define SEC_IRQ_CTRL0_irq_vbid2_chg_en(data)                                         (0x00000010&((data)<<4))
#define SEC_IRQ_CTRL0_irq_vbid2_chg_en_src(data)                                     ((0x00000010&(data))>>4)
#define SEC_IRQ_CTRL0_get_irq_vbid2_chg_en(data)                                     ((0x00000010&(data))>>4)
#define SEC_IRQ_CTRL0_irq_aud_freq_chg_en_shift                                      (3)
#define SEC_IRQ_CTRL0_irq_aud_freq_chg_en_mask                                       (0x00000008)
#define SEC_IRQ_CTRL0_irq_aud_freq_chg_en(data)                                      (0x00000008&((data)<<3))
#define SEC_IRQ_CTRL0_irq_aud_freq_chg_en_src(data)                                  ((0x00000008&(data))>>3)
#define SEC_IRQ_CTRL0_get_irq_aud_freq_chg_en(data)                                  ((0x00000008&(data))>>3)
#define SEC_IRQ_CTRL0_irq_mst_sec_packet_id_chg_en_shift                             (2)
#define SEC_IRQ_CTRL0_irq_mst_sec_packet_id_chg_en_mask                              (0x00000004)
#define SEC_IRQ_CTRL0_irq_mst_sec_packet_id_chg_en(data)                             (0x00000004&((data)<<2))
#define SEC_IRQ_CTRL0_irq_mst_sec_packet_id_chg_en_src(data)                         ((0x00000004&(data))>>2)
#define SEC_IRQ_CTRL0_get_irq_mst_sec_packet_id_chg_en(data)                         ((0x00000004&(data))>>2)
#define SEC_IRQ_CTRL0_irq_mst_coding_type_chg_en_shift                               (1)
#define SEC_IRQ_CTRL0_irq_mst_coding_type_chg_en_mask                                (0x00000002)
#define SEC_IRQ_CTRL0_irq_mst_coding_type_chg_en(data)                               (0x00000002&((data)<<1))
#define SEC_IRQ_CTRL0_irq_mst_coding_type_chg_en_src(data)                           ((0x00000002&(data))>>1)
#define SEC_IRQ_CTRL0_get_irq_mst_coding_type_chg_en(data)                           ((0x00000002&(data))>>1)
#define SEC_IRQ_CTRL0_irq_mst_channel_cnt_chg_en_shift                               (0)
#define SEC_IRQ_CTRL0_irq_mst_channel_cnt_chg_en_mask                                (0x00000001)
#define SEC_IRQ_CTRL0_irq_mst_channel_cnt_chg_en(data)                               (0x00000001&((data)<<0))
#define SEC_IRQ_CTRL0_irq_mst_channel_cnt_chg_en_src(data)                           ((0x00000001&(data))>>0)
#define SEC_IRQ_CTRL0_get_irq_mst_channel_cnt_chg_en(data)                           ((0x00000001&(data))>>0)


#define SEC_PH_HB0                                                                   0x9803D5CC
#define SEC_PH_HB0_reg_addr                                                          "0x9803D5CC"
#define SEC_PH_HB0_reg                                                               0x9803D5CC
#define set_SEC_PH_HB0_reg(data)   (*((volatile unsigned int*) SEC_PH_HB0_reg)=data)
#define get_SEC_PH_HB0_reg   (*((volatile unsigned int*) SEC_PH_HB0_reg))
#define SEC_PH_HB0_inst_adr                                                          "0x0073"
#define SEC_PH_HB0_inst                                                              0x0073
#define SEC_PH_HB0_packet_header_hb70_shift                                          (0)
#define SEC_PH_HB0_packet_header_hb70_mask                                           (0x000000FF)
#define SEC_PH_HB0_packet_header_hb70(data)                                          (0x000000FF&((data)<<0))
#define SEC_PH_HB0_packet_header_hb70_src(data)                                      ((0x000000FF&(data))>>0)
#define SEC_PH_HB0_get_packet_header_hb70(data)                                      ((0x000000FF&(data))>>0)


#define SEC_PH_HB1                                                                   0x9803D5D0
#define SEC_PH_HB1_reg_addr                                                          "0x9803D5D0"
#define SEC_PH_HB1_reg                                                               0x9803D5D0
#define set_SEC_PH_HB1_reg(data)   (*((volatile unsigned int*) SEC_PH_HB1_reg)=data)
#define get_SEC_PH_HB1_reg   (*((volatile unsigned int*) SEC_PH_HB1_reg))
#define SEC_PH_HB1_inst_adr                                                          "0x0074"
#define SEC_PH_HB1_inst                                                              0x0074
#define SEC_PH_HB1_packet_header_hb158_shift                                         (0)
#define SEC_PH_HB1_packet_header_hb158_mask                                          (0x000000FF)
#define SEC_PH_HB1_packet_header_hb158(data)                                         (0x000000FF&((data)<<0))
#define SEC_PH_HB1_packet_header_hb158_src(data)                                     ((0x000000FF&(data))>>0)
#define SEC_PH_HB1_get_packet_header_hb158(data)                                     ((0x000000FF&(data))>>0)


#define SEC_PH_HB2                                                                   0x9803D5D4
#define SEC_PH_HB2_reg_addr                                                          "0x9803D5D4"
#define SEC_PH_HB2_reg                                                               0x9803D5D4
#define set_SEC_PH_HB2_reg(data)   (*((volatile unsigned int*) SEC_PH_HB2_reg)=data)
#define get_SEC_PH_HB2_reg   (*((volatile unsigned int*) SEC_PH_HB2_reg))
#define SEC_PH_HB2_inst_adr                                                          "0x0075"
#define SEC_PH_HB2_inst                                                              0x0075
#define SEC_PH_HB2_packet_header_hb2316_shift                                        (0)
#define SEC_PH_HB2_packet_header_hb2316_mask                                         (0x000000FF)
#define SEC_PH_HB2_packet_header_hb2316(data)                                        (0x000000FF&((data)<<0))
#define SEC_PH_HB2_packet_header_hb2316_src(data)                                    ((0x000000FF&(data))>>0)
#define SEC_PH_HB2_get_packet_header_hb2316(data)                                    ((0x000000FF&(data))>>0)


#define SEC_PH_HB3                                                                   0x9803D5D8
#define SEC_PH_HB3_reg_addr                                                          "0x9803D5D8"
#define SEC_PH_HB3_reg                                                               0x9803D5D8
#define set_SEC_PH_HB3_reg(data)   (*((volatile unsigned int*) SEC_PH_HB3_reg)=data)
#define get_SEC_PH_HB3_reg   (*((volatile unsigned int*) SEC_PH_HB3_reg))
#define SEC_PH_HB3_inst_adr                                                          "0x0076"
#define SEC_PH_HB3_inst                                                              0x0076
#define SEC_PH_HB3_packet_header_hb3124_shift                                        (0)
#define SEC_PH_HB3_packet_header_hb3124_mask                                         (0x000000FF)
#define SEC_PH_HB3_packet_header_hb3124(data)                                        (0x000000FF&((data)<<0))
#define SEC_PH_HB3_packet_header_hb3124_src(data)                                    ((0x000000FF&(data))>>0)
#define SEC_PH_HB3_get_packet_header_hb3124(data)                                    ((0x000000FF&(data))>>0)


#define SEC_PH_PB0                                                                   0x9803D5DC
#define SEC_PH_PB0_reg_addr                                                          "0x9803D5DC"
#define SEC_PH_PB0_reg                                                               0x9803D5DC
#define set_SEC_PH_PB0_reg(data)   (*((volatile unsigned int*) SEC_PH_PB0_reg)=data)
#define get_SEC_PH_PB0_reg   (*((volatile unsigned int*) SEC_PH_PB0_reg))
#define SEC_PH_PB0_inst_adr                                                          "0x0077"
#define SEC_PH_PB0_inst                                                              0x0077
#define SEC_PH_PB0_packet_header_pb70_shift                                          (0)
#define SEC_PH_PB0_packet_header_pb70_mask                                           (0x000000FF)
#define SEC_PH_PB0_packet_header_pb70(data)                                          (0x000000FF&((data)<<0))
#define SEC_PH_PB0_packet_header_pb70_src(data)                                      ((0x000000FF&(data))>>0)
#define SEC_PH_PB0_get_packet_header_pb70(data)                                      ((0x000000FF&(data))>>0)


#define SEC_PH_PB1                                                                   0x9803D5E0
#define SEC_PH_PB1_reg_addr                                                          "0x9803D5E0"
#define SEC_PH_PB1_reg                                                               0x9803D5E0
#define set_SEC_PH_PB1_reg(data)   (*((volatile unsigned int*) SEC_PH_PB1_reg)=data)
#define get_SEC_PH_PB1_reg   (*((volatile unsigned int*) SEC_PH_PB1_reg))
#define SEC_PH_PB1_inst_adr                                                          "0x0078"
#define SEC_PH_PB1_inst                                                              0x0078
#define SEC_PH_PB1_packet_header_pb158_shift                                         (0)
#define SEC_PH_PB1_packet_header_pb158_mask                                          (0x000000FF)
#define SEC_PH_PB1_packet_header_pb158(data)                                         (0x000000FF&((data)<<0))
#define SEC_PH_PB1_packet_header_pb158_src(data)                                     ((0x000000FF&(data))>>0)
#define SEC_PH_PB1_get_packet_header_pb158(data)                                     ((0x000000FF&(data))>>0)


#define SEC_PH_PB2                                                                   0x9803D5E4
#define SEC_PH_PB2_reg_addr                                                          "0x9803D5E4"
#define SEC_PH_PB2_reg                                                               0x9803D5E4
#define set_SEC_PH_PB2_reg(data)   (*((volatile unsigned int*) SEC_PH_PB2_reg)=data)
#define get_SEC_PH_PB2_reg   (*((volatile unsigned int*) SEC_PH_PB2_reg))
#define SEC_PH_PB2_inst_adr                                                          "0x0079"
#define SEC_PH_PB2_inst                                                              0x0079
#define SEC_PH_PB2_packet_header_pb2316_shift                                        (0)
#define SEC_PH_PB2_packet_header_pb2316_mask                                         (0x000000FF)
#define SEC_PH_PB2_packet_header_pb2316(data)                                        (0x000000FF&((data)<<0))
#define SEC_PH_PB2_packet_header_pb2316_src(data)                                    ((0x000000FF&(data))>>0)
#define SEC_PH_PB2_get_packet_header_pb2316(data)                                    ((0x000000FF&(data))>>0)


#define SEC_PH_PB3                                                                   0x9803D5E8
#define SEC_PH_PB3_reg_addr                                                          "0x9803D5E8"
#define SEC_PH_PB3_reg                                                               0x9803D5E8
#define set_SEC_PH_PB3_reg(data)   (*((volatile unsigned int*) SEC_PH_PB3_reg)=data)
#define get_SEC_PH_PB3_reg   (*((volatile unsigned int*) SEC_PH_PB3_reg))
#define SEC_PH_PB3_inst_adr                                                          "0x007A"
#define SEC_PH_PB3_inst                                                              0x007A
#define SEC_PH_PB3_packet_header_pb3124_shift                                        (0)
#define SEC_PH_PB3_packet_header_pb3124_mask                                         (0x000000FF)
#define SEC_PH_PB3_packet_header_pb3124(data)                                        (0x000000FF&((data)<<0))
#define SEC_PH_PB3_packet_header_pb3124_src(data)                                    ((0x000000FF&(data))>>0)
#define SEC_PH_PB3_get_packet_header_pb3124(data)                                    ((0x000000FF&(data))>>0)


#define SEC_PH_PACKET_TYPE                                                           0x9803D5EC
#define SEC_PH_PACKET_TYPE_reg_addr                                                  "0x9803D5EC"
#define SEC_PH_PACKET_TYPE_reg                                                       0x9803D5EC
#define set_SEC_PH_PACKET_TYPE_reg(data)   (*((volatile unsigned int*) SEC_PH_PACKET_TYPE_reg)=data)
#define get_SEC_PH_PACKET_TYPE_reg   (*((volatile unsigned int*) SEC_PH_PACKET_TYPE_reg))
#define SEC_PH_PACKET_TYPE_inst_adr                                                  "0x007B"
#define SEC_PH_PACKET_TYPE_inst                                                      0x007B
#define SEC_PH_PACKET_TYPE_Reserved_shift                                            (4)
#define SEC_PH_PACKET_TYPE_Reserved_mask                                             (0x000000F0)
#define SEC_PH_PACKET_TYPE_Reserved(data)                                            (0x000000F0&((data)<<4))
#define SEC_PH_PACKET_TYPE_Reserved_src(data)                                        ((0x000000F0&(data))>>4)
#define SEC_PH_PACKET_TYPE_get_Reserved(data)                                        ((0x000000F0&(data))>>4)
#define SEC_PH_PACKET_TYPE_packet_type_shift                                         (0)
#define SEC_PH_PACKET_TYPE_packet_type_mask                                          (0x0000000F)
#define SEC_PH_PACKET_TYPE_packet_type(data)                                         (0x0000000F&((data)<<0))
#define SEC_PH_PACKET_TYPE_packet_type_src(data)                                     ((0x0000000F&(data))>>0)
#define SEC_PH_PACKET_TYPE_get_packet_type(data)                                     ((0x0000000F&(data))>>0)


#define SEC_AWD_STATUS_1                                                             0x9803D600
#define SEC_AWD_STATUS_1_reg_addr                                                    "0x9803D600"
#define SEC_AWD_STATUS_1_reg                                                         0x9803D600
#define set_SEC_AWD_STATUS_1_reg(data)   (*((volatile unsigned int*) SEC_AWD_STATUS_1_reg)=data)
#define get_SEC_AWD_STATUS_1_reg   (*((volatile unsigned int*) SEC_AWD_STATUS_1_reg))
#define SEC_AWD_STATUS_1_inst_adr                                                    "0x0080"
#define SEC_AWD_STATUS_1_inst                                                        0x0080
#define SEC_AWD_STATUS_1_vbid_4_chg_shift                                            (7)
#define SEC_AWD_STATUS_1_vbid_4_chg_mask                                             (0x00000080)
#define SEC_AWD_STATUS_1_vbid_4_chg(data)                                            (0x00000080&((data)<<7))
#define SEC_AWD_STATUS_1_vbid_4_chg_src(data)                                        ((0x00000080&(data))>>7)
#define SEC_AWD_STATUS_1_get_vbid_4_chg(data)                                        ((0x00000080&(data))>>7)
#define SEC_AWD_STATUS_1_vbid_3_chg_shift                                            (6)
#define SEC_AWD_STATUS_1_vbid_3_chg_mask                                             (0x00000040)
#define SEC_AWD_STATUS_1_vbid_3_chg(data)                                            (0x00000040&((data)<<6))
#define SEC_AWD_STATUS_1_vbid_3_chg_src(data)                                        ((0x00000040&(data))>>6)
#define SEC_AWD_STATUS_1_get_vbid_3_chg(data)                                        ((0x00000040&(data))>>6)
#define SEC_AWD_STATUS_1_vbid_2_chg_shift                                            (5)
#define SEC_AWD_STATUS_1_vbid_2_chg_mask                                             (0x00000020)
#define SEC_AWD_STATUS_1_vbid_2_chg(data)                                            (0x00000020&((data)<<5))
#define SEC_AWD_STATUS_1_vbid_2_chg_src(data)                                        ((0x00000020&(data))>>5)
#define SEC_AWD_STATUS_1_get_vbid_2_chg(data)                                        ((0x00000020&(data))>>5)
#define SEC_AWD_STATUS_1_Reserved_shift                                              (0)
#define SEC_AWD_STATUS_1_Reserved_mask                                               (0x0000001F)
#define SEC_AWD_STATUS_1_Reserved(data)                                              (0x0000001F&((data)<<0))
#define SEC_AWD_STATUS_1_Reserved_src(data)                                          ((0x0000001F&(data))>>0)
#define SEC_AWD_STATUS_1_get_Reserved(data)                                          ((0x0000001F&(data))>>0)


#define DP_INFO_VAR_EN_M                                                             0x9803D604
#define DP_INFO_VAR_EN_M_reg_addr                                                    "0x9803D604"
#define DP_INFO_VAR_EN_M_reg                                                         0x9803D604
#define set_DP_INFO_VAR_EN_M_reg(data)   (*((volatile unsigned int*) DP_INFO_VAR_EN_M_reg)=data)
#define get_DP_INFO_VAR_EN_M_reg   (*((volatile unsigned int*) DP_INFO_VAR_EN_M_reg))
#define DP_INFO_VAR_EN_M_inst_adr                                                    "0x0081"
#define DP_INFO_VAR_EN_M_inst                                                        0x0081
#define DP_INFO_VAR_EN_M_Reserved_shift                                              (5)
#define DP_INFO_VAR_EN_M_Reserved_mask                                               (0x000000E0)
#define DP_INFO_VAR_EN_M_Reserved(data)                                              (0x000000E0&((data)<<5))
#define DP_INFO_VAR_EN_M_Reserved_src(data)                                          ((0x000000E0&(data))>>5)
#define DP_INFO_VAR_EN_M_get_Reserved(data)                                          ((0x000000E0&(data))>>5)
#define DP_INFO_VAR_EN_M_var_mpg_fr_en_shift                                         (4)
#define DP_INFO_VAR_EN_M_var_mpg_fr_en_mask                                          (0x00000010)
#define DP_INFO_VAR_EN_M_var_mpg_fr_en(data)                                         (0x00000010&((data)<<4))
#define DP_INFO_VAR_EN_M_var_mpg_fr_en_src(data)                                     ((0x00000010&(data))>>4)
#define DP_INFO_VAR_EN_M_get_var_mpg_fr_en(data)                                     ((0x00000010&(data))>>4)
#define DP_INFO_VAR_EN_M_var_mpg_mb_en_shift                                         (3)
#define DP_INFO_VAR_EN_M_var_mpg_mb_en_mask                                          (0x00000008)
#define DP_INFO_VAR_EN_M_var_mpg_mb_en(data)                                         (0x00000008&((data)<<3))
#define DP_INFO_VAR_EN_M_var_mpg_mb_en_src(data)                                     ((0x00000008&(data))>>3)
#define DP_INFO_VAR_EN_M_get_var_mpg_mb_en(data)                                     ((0x00000008&(data))>>3)
#define DP_INFO_VAR_EN_M_var_aud_lsv_en_shift                                        (2)
#define DP_INFO_VAR_EN_M_var_aud_lsv_en_mask                                         (0x00000004)
#define DP_INFO_VAR_EN_M_var_aud_lsv_en(data)                                        (0x00000004&((data)<<2))
#define DP_INFO_VAR_EN_M_var_aud_lsv_en_src(data)                                    ((0x00000004&(data))>>2)
#define DP_INFO_VAR_EN_M_get_var_aud_lsv_en(data)                                    ((0x00000004&(data))>>2)
#define DP_INFO_VAR_EN_M_var_aud_ca_en_shift                                         (1)
#define DP_INFO_VAR_EN_M_var_aud_ca_en_mask                                          (0x00000002)
#define DP_INFO_VAR_EN_M_var_aud_ca_en(data)                                         (0x00000002&((data)<<1))
#define DP_INFO_VAR_EN_M_var_aud_ca_en_src(data)                                     ((0x00000002&(data))>>1)
#define DP_INFO_VAR_EN_M_get_var_aud_ca_en(data)                                     ((0x00000002&(data))>>1)
#define DP_INFO_VAR_EN_M_var_avi_bar_en_shift                                        (0)
#define DP_INFO_VAR_EN_M_var_avi_bar_en_mask                                         (0x00000001)
#define DP_INFO_VAR_EN_M_var_avi_bar_en(data)                                        (0x00000001&((data)<<0))
#define DP_INFO_VAR_EN_M_var_avi_bar_en_src(data)                                    ((0x00000001&(data))>>0)
#define DP_INFO_VAR_EN_M_get_var_avi_bar_en(data)                                    ((0x00000001&(data))>>0)


#define DP_INFO_VAR_EN_L                                                             0x9803D608
#define DP_INFO_VAR_EN_L_reg_addr                                                    "0x9803D608"
#define DP_INFO_VAR_EN_L_reg                                                         0x9803D608
#define set_DP_INFO_VAR_EN_L_reg(data)   (*((volatile unsigned int*) DP_INFO_VAR_EN_L_reg)=data)
#define get_DP_INFO_VAR_EN_L_reg   (*((volatile unsigned int*) DP_INFO_VAR_EN_L_reg))
#define DP_INFO_VAR_EN_L_inst_adr                                                    "0x0082"
#define DP_INFO_VAR_EN_L_inst                                                        0x0082
#define DP_INFO_VAR_EN_L_var_avi_b_en_shift                                          (7)
#define DP_INFO_VAR_EN_L_var_avi_b_en_mask                                           (0x00000080)
#define DP_INFO_VAR_EN_L_var_avi_b_en(data)                                          (0x00000080&((data)<<7))
#define DP_INFO_VAR_EN_L_var_avi_b_en_src(data)                                      ((0x00000080&(data))>>7)
#define DP_INFO_VAR_EN_L_get_var_avi_b_en(data)                                      ((0x00000080&(data))>>7)
#define DP_INFO_VAR_EN_L_var_avi_sc_en_shift                                         (6)
#define DP_INFO_VAR_EN_L_var_avi_sc_en_mask                                          (0x00000040)
#define DP_INFO_VAR_EN_L_var_avi_sc_en(data)                                         (0x00000040&((data)<<6))
#define DP_INFO_VAR_EN_L_var_avi_sc_en_src(data)                                     ((0x00000040&(data))>>6)
#define DP_INFO_VAR_EN_L_get_var_avi_sc_en(data)                                     ((0x00000040&(data))>>6)
#define DP_INFO_VAR_EN_L_var_avi_q_en_shift                                          (5)
#define DP_INFO_VAR_EN_L_var_avi_q_en_mask                                           (0x00000020)
#define DP_INFO_VAR_EN_L_var_avi_q_en(data)                                          (0x00000020&((data)<<5))
#define DP_INFO_VAR_EN_L_var_avi_q_en_src(data)                                      ((0x00000020&(data))>>5)
#define DP_INFO_VAR_EN_L_get_var_avi_q_en(data)                                      ((0x00000020&(data))>>5)
#define DP_INFO_VAR_EN_L_var_avi_itc_en_shift                                        (4)
#define DP_INFO_VAR_EN_L_var_avi_itc_en_mask                                         (0x00000010)
#define DP_INFO_VAR_EN_L_var_avi_itc_en(data)                                        (0x00000010&((data)<<4))
#define DP_INFO_VAR_EN_L_var_avi_itc_en_src(data)                                    ((0x00000010&(data))>>4)
#define DP_INFO_VAR_EN_L_get_var_avi_itc_en(data)                                    ((0x00000010&(data))>>4)
#define DP_INFO_VAR_EN_L_var_avi_pr_en_shift                                         (3)
#define DP_INFO_VAR_EN_L_var_avi_pr_en_mask                                          (0x00000008)
#define DP_INFO_VAR_EN_L_var_avi_pr_en(data)                                         (0x00000008&((data)<<3))
#define DP_INFO_VAR_EN_L_var_avi_pr_en_src(data)                                     ((0x00000008&(data))>>3)
#define DP_INFO_VAR_EN_L_get_var_avi_pr_en(data)                                     ((0x00000008&(data))>>3)
#define DP_INFO_VAR_EN_L_var_avi_s_en_shift                                          (2)
#define DP_INFO_VAR_EN_L_var_avi_s_en_mask                                           (0x00000004)
#define DP_INFO_VAR_EN_L_var_avi_s_en(data)                                          (0x00000004&((data)<<2))
#define DP_INFO_VAR_EN_L_var_avi_s_en_src(data)                                      ((0x00000004&(data))>>2)
#define DP_INFO_VAR_EN_L_get_var_avi_s_en(data)                                      ((0x00000004&(data))>>2)
#define DP_INFO_VAR_EN_L_var_avi_a_en_shift                                          (1)
#define DP_INFO_VAR_EN_L_var_avi_a_en_mask                                           (0x00000002)
#define DP_INFO_VAR_EN_L_var_avi_a_en(data)                                          (0x00000002&((data)<<1))
#define DP_INFO_VAR_EN_L_var_avi_a_en_src(data)                                      ((0x00000002&(data))>>1)
#define DP_INFO_VAR_EN_L_get_var_avi_a_en(data)                                      ((0x00000002&(data))>>1)
#define DP_INFO_VAR_EN_L_var_avi_y_en_shift                                          (0)
#define DP_INFO_VAR_EN_L_var_avi_y_en_mask                                           (0x00000001)
#define DP_INFO_VAR_EN_L_var_avi_y_en(data)                                          (0x00000001&((data)<<0))
#define DP_INFO_VAR_EN_L_var_avi_y_en_src(data)                                      ((0x00000001&(data))>>0)
#define DP_INFO_VAR_EN_L_get_var_avi_y_en(data)                                      ((0x00000001&(data))>>0)


#define DP_INFO_VAR_ST_M                                                             0x9803D60C
#define DP_INFO_VAR_ST_M_reg_addr                                                    "0x9803D60C"
#define DP_INFO_VAR_ST_M_reg                                                         0x9803D60C
#define set_DP_INFO_VAR_ST_M_reg(data)   (*((volatile unsigned int*) DP_INFO_VAR_ST_M_reg)=data)
#define get_DP_INFO_VAR_ST_M_reg   (*((volatile unsigned int*) DP_INFO_VAR_ST_M_reg))
#define DP_INFO_VAR_ST_M_inst_adr                                                    "0x0083"
#define DP_INFO_VAR_ST_M_inst                                                        0x0083
#define DP_INFO_VAR_ST_M_Reserved_shift                                              (5)
#define DP_INFO_VAR_ST_M_Reserved_mask                                               (0x000000E0)
#define DP_INFO_VAR_ST_M_Reserved(data)                                              (0x000000E0&((data)<<5))
#define DP_INFO_VAR_ST_M_Reserved_src(data)                                          ((0x000000E0&(data))>>5)
#define DP_INFO_VAR_ST_M_get_Reserved(data)                                          ((0x000000E0&(data))>>5)
#define DP_INFO_VAR_ST_M_var_mpg_fr_shift                                            (4)
#define DP_INFO_VAR_ST_M_var_mpg_fr_mask                                             (0x00000010)
#define DP_INFO_VAR_ST_M_var_mpg_fr(data)                                            (0x00000010&((data)<<4))
#define DP_INFO_VAR_ST_M_var_mpg_fr_src(data)                                        ((0x00000010&(data))>>4)
#define DP_INFO_VAR_ST_M_get_var_mpg_fr(data)                                        ((0x00000010&(data))>>4)
#define DP_INFO_VAR_ST_M_var_mpg_mb_shift                                            (3)
#define DP_INFO_VAR_ST_M_var_mpg_mb_mask                                             (0x00000008)
#define DP_INFO_VAR_ST_M_var_mpg_mb(data)                                            (0x00000008&((data)<<3))
#define DP_INFO_VAR_ST_M_var_mpg_mb_src(data)                                        ((0x00000008&(data))>>3)
#define DP_INFO_VAR_ST_M_get_var_mpg_mb(data)                                        ((0x00000008&(data))>>3)
#define DP_INFO_VAR_ST_M_var_aud_lsv_shift                                           (2)
#define DP_INFO_VAR_ST_M_var_aud_lsv_mask                                            (0x00000004)
#define DP_INFO_VAR_ST_M_var_aud_lsv(data)                                           (0x00000004&((data)<<2))
#define DP_INFO_VAR_ST_M_var_aud_lsv_src(data)                                       ((0x00000004&(data))>>2)
#define DP_INFO_VAR_ST_M_get_var_aud_lsv(data)                                       ((0x00000004&(data))>>2)
#define DP_INFO_VAR_ST_M_var_aud_ca_shift                                            (1)
#define DP_INFO_VAR_ST_M_var_aud_ca_mask                                             (0x00000002)
#define DP_INFO_VAR_ST_M_var_aud_ca(data)                                            (0x00000002&((data)<<1))
#define DP_INFO_VAR_ST_M_var_aud_ca_src(data)                                        ((0x00000002&(data))>>1)
#define DP_INFO_VAR_ST_M_get_var_aud_ca(data)                                        ((0x00000002&(data))>>1)
#define DP_INFO_VAR_ST_M_var_avi_bar_shift                                           (0)
#define DP_INFO_VAR_ST_M_var_avi_bar_mask                                            (0x00000001)
#define DP_INFO_VAR_ST_M_var_avi_bar(data)                                           (0x00000001&((data)<<0))
#define DP_INFO_VAR_ST_M_var_avi_bar_src(data)                                       ((0x00000001&(data))>>0)
#define DP_INFO_VAR_ST_M_get_var_avi_bar(data)                                       ((0x00000001&(data))>>0)


#define DP_INFO_VAR_ST_L                                                             0x9803D610
#define DP_INFO_VAR_ST_L_reg_addr                                                    "0x9803D610"
#define DP_INFO_VAR_ST_L_reg                                                         0x9803D610
#define set_DP_INFO_VAR_ST_L_reg(data)   (*((volatile unsigned int*) DP_INFO_VAR_ST_L_reg)=data)
#define get_DP_INFO_VAR_ST_L_reg   (*((volatile unsigned int*) DP_INFO_VAR_ST_L_reg))
#define DP_INFO_VAR_ST_L_inst_adr                                                    "0x0084"
#define DP_INFO_VAR_ST_L_inst                                                        0x0084
#define DP_INFO_VAR_ST_L_var_avi_b_shift                                             (7)
#define DP_INFO_VAR_ST_L_var_avi_b_mask                                              (0x00000080)
#define DP_INFO_VAR_ST_L_var_avi_b(data)                                             (0x00000080&((data)<<7))
#define DP_INFO_VAR_ST_L_var_avi_b_src(data)                                         ((0x00000080&(data))>>7)
#define DP_INFO_VAR_ST_L_get_var_avi_b(data)                                         ((0x00000080&(data))>>7)
#define DP_INFO_VAR_ST_L_var_avi_sc_shift                                            (6)
#define DP_INFO_VAR_ST_L_var_avi_sc_mask                                             (0x00000040)
#define DP_INFO_VAR_ST_L_var_avi_sc(data)                                            (0x00000040&((data)<<6))
#define DP_INFO_VAR_ST_L_var_avi_sc_src(data)                                        ((0x00000040&(data))>>6)
#define DP_INFO_VAR_ST_L_get_var_avi_sc(data)                                        ((0x00000040&(data))>>6)
#define DP_INFO_VAR_ST_L_var_avi_q_shift                                             (5)
#define DP_INFO_VAR_ST_L_var_avi_q_mask                                              (0x00000020)
#define DP_INFO_VAR_ST_L_var_avi_q(data)                                             (0x00000020&((data)<<5))
#define DP_INFO_VAR_ST_L_var_avi_q_src(data)                                         ((0x00000020&(data))>>5)
#define DP_INFO_VAR_ST_L_get_var_avi_q(data)                                         ((0x00000020&(data))>>5)
#define DP_INFO_VAR_ST_L_var_avi_itc_shift                                           (4)
#define DP_INFO_VAR_ST_L_var_avi_itc_mask                                            (0x00000010)
#define DP_INFO_VAR_ST_L_var_avi_itc(data)                                           (0x00000010&((data)<<4))
#define DP_INFO_VAR_ST_L_var_avi_itc_src(data)                                       ((0x00000010&(data))>>4)
#define DP_INFO_VAR_ST_L_get_var_avi_itc(data)                                       ((0x00000010&(data))>>4)
#define DP_INFO_VAR_ST_L_var_avi_pr_shift                                            (3)
#define DP_INFO_VAR_ST_L_var_avi_pr_mask                                             (0x00000008)
#define DP_INFO_VAR_ST_L_var_avi_pr(data)                                            (0x00000008&((data)<<3))
#define DP_INFO_VAR_ST_L_var_avi_pr_src(data)                                        ((0x00000008&(data))>>3)
#define DP_INFO_VAR_ST_L_get_var_avi_pr(data)                                        ((0x00000008&(data))>>3)
#define DP_INFO_VAR_ST_L_var_avi_s_shift                                             (2)
#define DP_INFO_VAR_ST_L_var_avi_s_mask                                              (0x00000004)
#define DP_INFO_VAR_ST_L_var_avi_s(data)                                             (0x00000004&((data)<<2))
#define DP_INFO_VAR_ST_L_var_avi_s_src(data)                                         ((0x00000004&(data))>>2)
#define DP_INFO_VAR_ST_L_get_var_avi_s(data)                                         ((0x00000004&(data))>>2)
#define DP_INFO_VAR_ST_L_var_avi_a_shift                                             (1)
#define DP_INFO_VAR_ST_L_var_avi_a_mask                                              (0x00000002)
#define DP_INFO_VAR_ST_L_var_avi_a(data)                                             (0x00000002&((data)<<1))
#define DP_INFO_VAR_ST_L_var_avi_a_src(data)                                         ((0x00000002&(data))>>1)
#define DP_INFO_VAR_ST_L_get_var_avi_a(data)                                         ((0x00000002&(data))>>1)
#define DP_INFO_VAR_ST_L_var_avi_y_shift                                             (0)
#define DP_INFO_VAR_ST_L_var_avi_y_mask                                              (0x00000001)
#define DP_INFO_VAR_ST_L_var_avi_y(data)                                             (0x00000001&((data)<<0))
#define DP_INFO_VAR_ST_L_var_avi_y_src(data)                                         ((0x00000001&(data))>>0)
#define DP_INFO_VAR_ST_L_get_var_avi_y(data)                                         ((0x00000001&(data))>>0)


#define CH_STATUS_0                                                                  0x9803D614
#define CH_STATUS_0_reg_addr                                                         "0x9803D614"
#define CH_STATUS_0_reg                                                              0x9803D614
#define set_CH_STATUS_0_reg(data)   (*((volatile unsigned int*) CH_STATUS_0_reg)=data)
#define get_CH_STATUS_0_reg   (*((volatile unsigned int*) CH_STATUS_0_reg))
#define CH_STATUS_0_inst_adr                                                         "0x0085"
#define CH_STATUS_0_inst                                                             0x0085
#define CH_STATUS_0_ch_status70_shift                                                (0)
#define CH_STATUS_0_ch_status70_mask                                                 (0x000000FF)
#define CH_STATUS_0_ch_status70(data)                                                (0x000000FF&((data)<<0))
#define CH_STATUS_0_ch_status70_src(data)                                            ((0x000000FF&(data))>>0)
#define CH_STATUS_0_get_ch_status70(data)                                            ((0x000000FF&(data))>>0)


#define CH_STATUS_1                                                                  0x9803D618
#define CH_STATUS_1_reg_addr                                                         "0x9803D618"
#define CH_STATUS_1_reg                                                              0x9803D618
#define set_CH_STATUS_1_reg(data)   (*((volatile unsigned int*) CH_STATUS_1_reg)=data)
#define get_CH_STATUS_1_reg   (*((volatile unsigned int*) CH_STATUS_1_reg))
#define CH_STATUS_1_inst_adr                                                         "0x0086"
#define CH_STATUS_1_inst                                                             0x0086
#define CH_STATUS_1_ch_status158_shift                                               (0)
#define CH_STATUS_1_ch_status158_mask                                                (0x000000FF)
#define CH_STATUS_1_ch_status158(data)                                               (0x000000FF&((data)<<0))
#define CH_STATUS_1_ch_status158_src(data)                                           ((0x000000FF&(data))>>0)
#define CH_STATUS_1_get_ch_status158(data)                                           ((0x000000FF&(data))>>0)


#define CH_STATUS_2                                                                  0x9803D61C
#define CH_STATUS_2_reg_addr                                                         "0x9803D61C"
#define CH_STATUS_2_reg                                                              0x9803D61C
#define set_CH_STATUS_2_reg(data)   (*((volatile unsigned int*) CH_STATUS_2_reg)=data)
#define get_CH_STATUS_2_reg   (*((volatile unsigned int*) CH_STATUS_2_reg))
#define CH_STATUS_2_inst_adr                                                         "0x0087"
#define CH_STATUS_2_inst                                                             0x0087
#define CH_STATUS_2_ch_status2316_shift                                              (0)
#define CH_STATUS_2_ch_status2316_mask                                               (0x000000FF)
#define CH_STATUS_2_ch_status2316(data)                                              (0x000000FF&((data)<<0))
#define CH_STATUS_2_ch_status2316_src(data)                                          ((0x000000FF&(data))>>0)
#define CH_STATUS_2_get_ch_status2316(data)                                          ((0x000000FF&(data))>>0)


#define CH_STATUS_3                                                                  0x9803D620
#define CH_STATUS_3_reg_addr                                                         "0x9803D620"
#define CH_STATUS_3_reg                                                              0x9803D620
#define set_CH_STATUS_3_reg(data)   (*((volatile unsigned int*) CH_STATUS_3_reg)=data)
#define get_CH_STATUS_3_reg   (*((volatile unsigned int*) CH_STATUS_3_reg))
#define CH_STATUS_3_inst_adr                                                         "0x0088"
#define CH_STATUS_3_inst                                                             0x0088
#define CH_STATUS_3_ch_status3124_shift                                              (0)
#define CH_STATUS_3_ch_status3124_mask                                               (0x000000FF)
#define CH_STATUS_3_ch_status3124(data)                                              (0x000000FF&((data)<<0))
#define CH_STATUS_3_ch_status3124_src(data)                                          ((0x000000FF&(data))>>0)
#define CH_STATUS_3_get_ch_status3124(data)                                          ((0x000000FF&(data))>>0)


#define CH_STATUS_4                                                                  0x9803D624
#define CH_STATUS_4_reg_addr                                                         "0x9803D624"
#define CH_STATUS_4_reg                                                              0x9803D624
#define set_CH_STATUS_4_reg(data)   (*((volatile unsigned int*) CH_STATUS_4_reg)=data)
#define get_CH_STATUS_4_reg   (*((volatile unsigned int*) CH_STATUS_4_reg))
#define CH_STATUS_4_inst_adr                                                         "0x0089"
#define CH_STATUS_4_inst                                                             0x0089
#define CH_STATUS_4_ch_status3932_shift                                              (0)
#define CH_STATUS_4_ch_status3932_mask                                               (0x000000FF)
#define CH_STATUS_4_ch_status3932(data)                                              (0x000000FF&((data)<<0))
#define CH_STATUS_4_ch_status3932_src(data)                                          ((0x000000FF&(data))>>0)
#define CH_STATUS_4_get_ch_status3932(data)                                          ((0x000000FF&(data))>>0)


#define DP_AVWD_CTRL0                                                                0x9803D628
#define DP_AVWD_CTRL0_reg_addr                                                       "0x9803D628"
#define DP_AVWD_CTRL0_reg                                                            0x9803D628
#define set_DP_AVWD_CTRL0_reg(data)   (*((volatile unsigned int*) DP_AVWD_CTRL0_reg)=data)
#define get_DP_AVWD_CTRL0_reg   (*((volatile unsigned int*) DP_AVWD_CTRL0_reg))
#define DP_AVWD_CTRL0_inst_adr                                                       "0x008A"
#define DP_AVWD_CTRL0_inst                                                           0x008A
#define DP_AVWD_CTRL0_Reserved_shift                                                 (4)
#define DP_AVWD_CTRL0_Reserved_mask                                                  (0x000000F0)
#define DP_AVWD_CTRL0_Reserved(data)                                                 (0x000000F0&((data)<<4))
#define DP_AVWD_CTRL0_Reserved_src(data)                                             ((0x000000F0&(data))>>4)
#define DP_AVWD_CTRL0_get_Reserved(data)                                             ((0x000000F0&(data))>>4)
#define DP_AVWD_CTRL0_swd_by_vsc_en_shift                                            (3)
#define DP_AVWD_CTRL0_swd_by_vsc_en_mask                                             (0x00000008)
#define DP_AVWD_CTRL0_swd_by_vsc_en(data)                                            (0x00000008&((data)<<3))
#define DP_AVWD_CTRL0_swd_by_vsc_en_src(data)                                        ((0x00000008&(data))>>3)
#define DP_AVWD_CTRL0_get_swd_by_vsc_en(data)                                        ((0x00000008&(data))>>3)
#define DP_AVWD_CTRL0_swd_by_mpg_en_shift                                            (2)
#define DP_AVWD_CTRL0_swd_by_mpg_en_mask                                             (0x00000004)
#define DP_AVWD_CTRL0_swd_by_mpg_en(data)                                            (0x00000004&((data)<<2))
#define DP_AVWD_CTRL0_swd_by_mpg_en_src(data)                                        ((0x00000004&(data))>>2)
#define DP_AVWD_CTRL0_get_swd_by_mpg_en(data)                                        ((0x00000004&(data))>>2)
#define DP_AVWD_CTRL0_swd_by_aud_en_shift                                            (1)
#define DP_AVWD_CTRL0_swd_by_aud_en_mask                                             (0x00000002)
#define DP_AVWD_CTRL0_swd_by_aud_en(data)                                            (0x00000002&((data)<<1))
#define DP_AVWD_CTRL0_swd_by_aud_en_src(data)                                        ((0x00000002&(data))>>1)
#define DP_AVWD_CTRL0_get_swd_by_aud_en(data)                                        ((0x00000002&(data))>>1)
#define DP_AVWD_CTRL0_swd_by_avi_en_shift                                            (0)
#define DP_AVWD_CTRL0_swd_by_avi_en_mask                                             (0x00000001)
#define DP_AVWD_CTRL0_swd_by_avi_en(data)                                            (0x00000001&((data)<<0))
#define DP_AVWD_CTRL0_swd_by_avi_en_src(data)                                        ((0x00000001&(data))>>0)
#define DP_AVWD_CTRL0_get_swd_by_avi_en(data)                                        ((0x00000001&(data))>>0)


#define RESERVED_8B                                                                  0x9803D62C
#define RESERVED_8B_reg_addr                                                         "0x9803D62C"
#define RESERVED_8B_reg                                                              0x9803D62C
#define set_RESERVED_8B_reg(data)   (*((volatile unsigned int*) RESERVED_8B_reg)=data)
#define get_RESERVED_8B_reg   (*((volatile unsigned int*) RESERVED_8B_reg))
#define RESERVED_8B_inst_adr                                                         "0x008B"
#define RESERVED_8B_inst                                                             0x008B
#define RESERVED_8B_Reserved_shift                                                   (0)
#define RESERVED_8B_Reserved_mask                                                    (0x000000FF)
#define RESERVED_8B_Reserved(data)                                                   (0x000000FF&((data)<<0))
#define RESERVED_8B_Reserved_src(data)                                               ((0x000000FF&(data))>>0)
#define RESERVED_8B_get_Reserved(data)                                               ((0x000000FF&(data))>>0)


#define RESERVED_8C                                                                  0x9803D630
#define RESERVED_8C_reg_addr                                                         "0x9803D630"
#define RESERVED_8C_reg                                                              0x9803D630
#define set_RESERVED_8C_reg(data)   (*((volatile unsigned int*) RESERVED_8C_reg)=data)
#define get_RESERVED_8C_reg   (*((volatile unsigned int*) RESERVED_8C_reg))
#define RESERVED_8C_inst_adr                                                         "0x008C"
#define RESERVED_8C_inst                                                             0x008C
#define RESERVED_8C_Reserved_shift                                                   (0)
#define RESERVED_8C_Reserved_mask                                                    (0x000000FF)
#define RESERVED_8C_Reserved(data)                                                   (0x000000FF&((data)<<0))
#define RESERVED_8C_Reserved_src(data)                                               ((0x000000FF&(data))>>0)
#define RESERVED_8C_get_Reserved(data)                                               ((0x000000FF&(data))>>0)


#define RESERVED_8D                                                                  0x9803D634
#define RESERVED_8D_reg_addr                                                         "0x9803D634"
#define RESERVED_8D_reg                                                              0x9803D634
#define set_RESERVED_8D_reg(data)   (*((volatile unsigned int*) RESERVED_8D_reg)=data)
#define get_RESERVED_8D_reg   (*((volatile unsigned int*) RESERVED_8D_reg))
#define RESERVED_8D_inst_adr                                                         "0x008D"
#define RESERVED_8D_inst                                                             0x008D
#define RESERVED_8D_Reserved_shift                                                   (0)
#define RESERVED_8D_Reserved_mask                                                    (0x000000FF)
#define RESERVED_8D_Reserved(data)                                                   (0x000000FF&((data)<<0))
#define RESERVED_8D_Reserved_src(data)                                               ((0x000000FF&(data))>>0)
#define RESERVED_8D_get_Reserved(data)                                               ((0x000000FF&(data))>>0)


#define RESERVED_8E                                                                  0x9803D638
#define RESERVED_8E_reg_addr                                                         "0x9803D638"
#define RESERVED_8E_reg                                                              0x9803D638
#define set_RESERVED_8E_reg(data)   (*((volatile unsigned int*) RESERVED_8E_reg)=data)
#define get_RESERVED_8E_reg   (*((volatile unsigned int*) RESERVED_8E_reg))
#define RESERVED_8E_inst_adr                                                         "0x008E"
#define RESERVED_8E_inst                                                             0x008E
#define RESERVED_8E_Reserved_shift                                                   (0)
#define RESERVED_8E_Reserved_mask                                                    (0x000000FF)
#define RESERVED_8E_Reserved(data)                                                   (0x000000FF&((data)<<0))
#define RESERVED_8E_Reserved_src(data)                                               ((0x000000FF&(data))>>0)
#define RESERVED_8E_get_Reserved(data)                                               ((0x000000FF&(data))>>0)


#define DPTX_I2S_CTRL                                                                0x9803D63C
#define DPTX_I2S_CTRL_reg_addr                                                       "0x9803D63C"
#define DPTX_I2S_CTRL_reg                                                            0x9803D63C
#define set_DPTX_I2S_CTRL_reg(data)   (*((volatile unsigned int*) DPTX_I2S_CTRL_reg)=data)
#define get_DPTX_I2S_CTRL_reg   (*((volatile unsigned int*) DPTX_I2S_CTRL_reg))
#define DPTX_I2S_CTRL_inst_adr                                                       "0x008F"
#define DPTX_I2S_CTRL_inst                                                           0x008F
#define DPTX_I2S_CTRL_i2s_0_switch_shift                                             (7)
#define DPTX_I2S_CTRL_i2s_0_switch_mask                                              (0x00000080)
#define DPTX_I2S_CTRL_i2s_0_switch(data)                                             (0x00000080&((data)<<7))
#define DPTX_I2S_CTRL_i2s_0_switch_src(data)                                         ((0x00000080&(data))>>7)
#define DPTX_I2S_CTRL_get_i2s_0_switch(data)                                         ((0x00000080&(data))>>7)
#define DPTX_I2S_CTRL_i2s_1_switch_shift                                             (6)
#define DPTX_I2S_CTRL_i2s_1_switch_mask                                              (0x00000040)
#define DPTX_I2S_CTRL_i2s_1_switch(data)                                             (0x00000040&((data)<<6))
#define DPTX_I2S_CTRL_i2s_1_switch_src(data)                                         ((0x00000040&(data))>>6)
#define DPTX_I2S_CTRL_get_i2s_1_switch(data)                                         ((0x00000040&(data))>>6)
#define DPTX_I2S_CTRL_i2s_2_switch_shift                                             (5)
#define DPTX_I2S_CTRL_i2s_2_switch_mask                                              (0x00000020)
#define DPTX_I2S_CTRL_i2s_2_switch(data)                                             (0x00000020&((data)<<5))
#define DPTX_I2S_CTRL_i2s_2_switch_src(data)                                         ((0x00000020&(data))>>5)
#define DPTX_I2S_CTRL_get_i2s_2_switch(data)                                         ((0x00000020&(data))>>5)
#define DPTX_I2S_CTRL_i2s_3_switch_shift                                             (4)
#define DPTX_I2S_CTRL_i2s_3_switch_mask                                              (0x00000010)
#define DPTX_I2S_CTRL_i2s_3_switch(data)                                             (0x00000010&((data)<<4))
#define DPTX_I2S_CTRL_i2s_3_switch_src(data)                                         ((0x00000010&(data))>>4)
#define DPTX_I2S_CTRL_get_i2s_3_switch(data)                                         ((0x00000010&(data))>>4)
#define DPTX_I2S_CTRL_pr_field_ch_exist_shift                                        (3)
#define DPTX_I2S_CTRL_pr_field_ch_exist_mask                                         (0x00000008)
#define DPTX_I2S_CTRL_pr_field_ch_exist(data)                                        (0x00000008&((data)<<3))
#define DPTX_I2S_CTRL_pr_field_ch_exist_src(data)                                    ((0x00000008&(data))>>3)
#define DPTX_I2S_CTRL_get_pr_field_ch_exist(data)                                    ((0x00000008&(data))>>3)
#define DPTX_I2S_CTRL_parity_type_shift                                              (2)
#define DPTX_I2S_CTRL_parity_type_mask                                               (0x00000004)
#define DPTX_I2S_CTRL_parity_type(data)                                              (0x00000004&((data)<<2))
#define DPTX_I2S_CTRL_parity_type_src(data)                                          ((0x00000004&(data))>>2)
#define DPTX_I2S_CTRL_get_parity_type(data)                                          ((0x00000004&(data))>>2)
#define DPTX_I2S_CTRL_as_payload_byte3_auto_shift                                    (1)
#define DPTX_I2S_CTRL_as_payload_byte3_auto_mask                                     (0x00000002)
#define DPTX_I2S_CTRL_as_payload_byte3_auto(data)                                    (0x00000002&((data)<<1))
#define DPTX_I2S_CTRL_as_payload_byte3_auto_src(data)                                ((0x00000002&(data))>>1)
#define DPTX_I2S_CTRL_get_as_payload_byte3_auto(data)                                ((0x00000002&(data))>>1)
#define DPTX_I2S_CTRL_ch_status_cnt_en_shift                                         (0)
#define DPTX_I2S_CTRL_ch_status_cnt_en_mask                                          (0x00000001)
#define DPTX_I2S_CTRL_ch_status_cnt_en(data)                                         (0x00000001&((data)<<0))
#define DPTX_I2S_CTRL_ch_status_cnt_en_src(data)                                     ((0x00000001&(data))>>0)
#define DPTX_I2S_CTRL_get_ch_status_cnt_en(data)                                     ((0x00000001&(data))>>0)


#define SEC_IRQ_CTRL1                                                                0x9803D640
#define SEC_IRQ_CTRL1_reg_addr                                                       "0x9803D640"
#define SEC_IRQ_CTRL1_reg                                                            0x9803D640
#define set_SEC_IRQ_CTRL1_reg(data)   (*((volatile unsigned int*) SEC_IRQ_CTRL1_reg)=data)
#define get_SEC_IRQ_CTRL1_reg   (*((volatile unsigned int*) SEC_IRQ_CTRL1_reg))
#define SEC_IRQ_CTRL1_inst_adr                                                       "0x0090"
#define SEC_IRQ_CTRL1_inst                                                           0x0090
#define SEC_IRQ_CTRL1_Dummy_shift                                                    (4)
#define SEC_IRQ_CTRL1_Dummy_mask                                                     (0x000000F0)
#define SEC_IRQ_CTRL1_Dummy(data)                                                    (0x000000F0&((data)<<4))
#define SEC_IRQ_CTRL1_Dummy_src(data)                                                ((0x000000F0&(data))>>4)
#define SEC_IRQ_CTRL1_get_Dummy(data)                                                ((0x000000F0&(data))>>4)
#define SEC_IRQ_CTRL1_irq_by_vsc_en_shift                                            (3)
#define SEC_IRQ_CTRL1_irq_by_vsc_en_mask                                             (0x00000008)
#define SEC_IRQ_CTRL1_irq_by_vsc_en(data)                                            (0x00000008&((data)<<3))
#define SEC_IRQ_CTRL1_irq_by_vsc_en_src(data)                                        ((0x00000008&(data))>>3)
#define SEC_IRQ_CTRL1_get_irq_by_vsc_en(data)                                        ((0x00000008&(data))>>3)
#define SEC_IRQ_CTRL1_irq_by_mpg_en_shift                                            (2)
#define SEC_IRQ_CTRL1_irq_by_mpg_en_mask                                             (0x00000004)
#define SEC_IRQ_CTRL1_irq_by_mpg_en(data)                                            (0x00000004&((data)<<2))
#define SEC_IRQ_CTRL1_irq_by_mpg_en_src(data)                                        ((0x00000004&(data))>>2)
#define SEC_IRQ_CTRL1_get_irq_by_mpg_en(data)                                        ((0x00000004&(data))>>2)
#define SEC_IRQ_CTRL1_irq_by_aud_en_shift                                            (1)
#define SEC_IRQ_CTRL1_irq_by_aud_en_mask                                             (0x00000002)
#define SEC_IRQ_CTRL1_irq_by_aud_en(data)                                            (0x00000002&((data)<<1))
#define SEC_IRQ_CTRL1_irq_by_aud_en_src(data)                                        ((0x00000002&(data))>>1)
#define SEC_IRQ_CTRL1_get_irq_by_aud_en(data)                                        ((0x00000002&(data))>>1)
#define SEC_IRQ_CTRL1_irq_by_avi_en_shift                                            (0)
#define SEC_IRQ_CTRL1_irq_by_avi_en_mask                                             (0x00000001)
#define SEC_IRQ_CTRL1_irq_by_avi_en(data)                                            (0x00000001&((data)<<0))
#define SEC_IRQ_CTRL1_irq_by_avi_en_src(data)                                        ((0x00000001&(data))>>0)
#define SEC_IRQ_CTRL1_get_irq_by_avi_en(data)                                        ((0x00000001&(data))>>0)


#define DUMMY_95                                                                     0x9803D654
#define DUMMY_95_reg_addr                                                            "0x9803D654"
#define DUMMY_95_reg                                                                 0x9803D654
#define set_DUMMY_95_reg(data)   (*((volatile unsigned int*) DUMMY_95_reg)=data)
#define get_DUMMY_95_reg   (*((volatile unsigned int*) DUMMY_95_reg))
#define DUMMY_95_inst_adr                                                            "0x0095"
#define DUMMY_95_inst                                                                0x0095
#define DUMMY_95_Dummy_shift                                                         (0)
#define DUMMY_95_Dummy_mask                                                          (0x000000FF)
#define DUMMY_95_Dummy(data)                                                         (0x000000FF&((data)<<0))
#define DUMMY_95_Dummy_src(data)                                                     ((0x000000FF&(data))>>0)
#define DUMMY_95_get_Dummy(data)                                                     ((0x000000FF&(data))>>0)


#define DUMMY_96                                                                     0x9803D658
#define DUMMY_96_reg_addr                                                            "0x9803D658"
#define DUMMY_96_reg                                                                 0x9803D658
#define set_DUMMY_96_reg(data)   (*((volatile unsigned int*) DUMMY_96_reg)=data)
#define get_DUMMY_96_reg   (*((volatile unsigned int*) DUMMY_96_reg))
#define DUMMY_96_inst_adr                                                            "0x0096"
#define DUMMY_96_inst                                                                0x0096
#define DUMMY_96_Dummy_shift                                                         (0)
#define DUMMY_96_Dummy_mask                                                          (0x000000FF)
#define DUMMY_96_Dummy(data)                                                         (0x000000FF&((data)<<0))
#define DUMMY_96_Dummy_src(data)                                                     ((0x000000FF&(data))>>0)
#define DUMMY_96_get_Dummy(data)                                                     ((0x000000FF&(data))>>0)


#define DUMMY_97                                                                     0x9803D65C
#define DUMMY_97_reg_addr                                                            "0x9803D65C"
#define DUMMY_97_reg                                                                 0x9803D65C
#define set_DUMMY_97_reg(data)   (*((volatile unsigned int*) DUMMY_97_reg)=data)
#define get_DUMMY_97_reg   (*((volatile unsigned int*) DUMMY_97_reg))
#define DUMMY_97_inst_adr                                                            "0x0097"
#define DUMMY_97_inst                                                                0x0097
#define DUMMY_97_Dummy_shift                                                         (0)
#define DUMMY_97_Dummy_mask                                                          (0x000000FF)
#define DUMMY_97_Dummy(data)                                                         (0x000000FF&((data)<<0))
#define DUMMY_97_Dummy_src(data)                                                     ((0x000000FF&(data))>>0)
#define DUMMY_97_get_Dummy(data)                                                     ((0x000000FF&(data))>>0)


#define DUMMY_98                                                                     0x9803D660
#define DUMMY_98_reg_addr                                                            "0x9803D660"
#define DUMMY_98_reg                                                                 0x9803D660
#define set_DUMMY_98_reg(data)   (*((volatile unsigned int*) DUMMY_98_reg)=data)
#define get_DUMMY_98_reg   (*((volatile unsigned int*) DUMMY_98_reg))
#define DUMMY_98_inst_adr                                                            "0x0098"
#define DUMMY_98_inst                                                                0x0098
#define DUMMY_98_Dummy_shift                                                         (2)
#define DUMMY_98_Dummy_mask                                                          (0x000000FC)
#define DUMMY_98_Dummy(data)                                                         (0x000000FC&((data)<<2))
#define DUMMY_98_Dummy_src(data)                                                     ((0x000000FC&(data))>>2)
#define DUMMY_98_get_Dummy(data)                                                     ((0x000000FC&(data))>>2)
#define DUMMY_98_aud_freq_chg_deb_md_shift                                           (0)
#define DUMMY_98_aud_freq_chg_deb_md_mask                                            (0x00000003)
#define DUMMY_98_aud_freq_chg_deb_md(data)                                           (0x00000003&((data)<<0))
#define DUMMY_98_aud_freq_chg_deb_md_src(data)                                       ((0x00000003&(data))>>0)
#define DUMMY_98_get_aud_freq_chg_deb_md(data)                                       ((0x00000003&(data))>>0)


#define DUMMY_99                                                                     0x9803D664
#define DUMMY_99_reg_addr                                                            "0x9803D664"
#define DUMMY_99_reg                                                                 0x9803D664
#define set_DUMMY_99_reg(data)   (*((volatile unsigned int*) DUMMY_99_reg)=data)
#define get_DUMMY_99_reg   (*((volatile unsigned int*) DUMMY_99_reg))
#define DUMMY_99_inst_adr                                                            "0x0099"
#define DUMMY_99_inst                                                                0x0099
#define DUMMY_99_Dummy_shift                                                         (4)
#define DUMMY_99_Dummy_mask                                                          (0x000000F0)
#define DUMMY_99_Dummy(data)                                                         (0x000000F0&((data)<<4))
#define DUMMY_99_Dummy_src(data)                                                     ((0x000000F0&(data))>>4)
#define DUMMY_99_get_Dummy(data)                                                     ((0x000000F0&(data))>>4)
#define DUMMY_99_audio_dec_err_drop_shift                                            (3)
#define DUMMY_99_audio_dec_err_drop_mask                                             (0x00000008)
#define DUMMY_99_audio_dec_err_drop(data)                                            (0x00000008&((data)<<3))
#define DUMMY_99_audio_dec_err_drop_src(data)                                        ((0x00000008&(data))>>3)
#define DUMMY_99_get_audio_dec_err_drop(data)                                        ((0x00000008&(data))>>3)
#define DUMMY_99_audio_sample_det_md_shift                                           (2)
#define DUMMY_99_audio_sample_det_md_mask                                            (0x00000004)
#define DUMMY_99_audio_sample_det_md(data)                                           (0x00000004&((data)<<2))
#define DUMMY_99_audio_sample_det_md_src(data)                                       ((0x00000004&(data))>>2)
#define DUMMY_99_get_audio_sample_det_md(data)                                       ((0x00000004&(data))>>2)
#define DUMMY_99_ch_lyo_fw_shift                                                     (1)
#define DUMMY_99_ch_lyo_fw_mask                                                      (0x00000002)
#define DUMMY_99_ch_lyo_fw(data)                                                     (0x00000002&((data)<<1))
#define DUMMY_99_ch_lyo_fw_src(data)                                                 ((0x00000002&(data))>>1)
#define DUMMY_99_get_ch_lyo_fw(data)                                                 ((0x00000002&(data))>>1)
#define DUMMY_99_hbr_audio_mode_shift                                                (0)
#define DUMMY_99_hbr_audio_mode_mask                                                 (0x00000001)
#define DUMMY_99_hbr_audio_mode(data)                                                (0x00000001&((data)<<0))
#define DUMMY_99_hbr_audio_mode_src(data)                                            ((0x00000001&(data))>>0)
#define DUMMY_99_get_hbr_audio_mode(data)                                            ((0x00000001&(data))>>0)


#define DUMMY_9A                                                                     0x9803D668
#define DUMMY_9A_reg_addr                                                            "0x9803D668"
#define DUMMY_9A_reg                                                                 0x9803D668
#define set_DUMMY_9A_reg(data)   (*((volatile unsigned int*) DUMMY_9A_reg)=data)
#define get_DUMMY_9A_reg   (*((volatile unsigned int*) DUMMY_9A_reg))
#define DUMMY_9A_inst_adr                                                            "0x009A"
#define DUMMY_9A_inst                                                                0x009A
#define DUMMY_9A_Dummy_shift                                                         (0)
#define DUMMY_9A_Dummy_mask                                                          (0x000000FF)
#define DUMMY_9A_Dummy(data)                                                         (0x000000FF&((data)<<0))
#define DUMMY_9A_Dummy_src(data)                                                     ((0x000000FF&(data))>>0)
#define DUMMY_9A_get_Dummy(data)                                                     ((0x000000FF&(data))>>0)


#define DUMMY_9B                                                                     0x9803D66C
#define DUMMY_9B_reg_addr                                                            "0x9803D66C"
#define DUMMY_9B_reg                                                                 0x9803D66C
#define set_DUMMY_9B_reg(data)   (*((volatile unsigned int*) DUMMY_9B_reg)=data)
#define get_DUMMY_9B_reg   (*((volatile unsigned int*) DUMMY_9B_reg))
#define DUMMY_9B_inst_adr                                                            "0x009B"
#define DUMMY_9B_inst                                                                0x009B
#define DUMMY_9B_Dummy_shift                                                         (0)
#define DUMMY_9B_Dummy_mask                                                          (0x000000FF)
#define DUMMY_9B_Dummy(data)                                                         (0x000000FF&((data)<<0))
#define DUMMY_9B_Dummy_src(data)                                                     ((0x000000FF&(data))>>0)
#define DUMMY_9B_get_Dummy(data)                                                     ((0x000000FF&(data))>>0)


#define DUMMY_9C                                                                     0x9803D670
#define DUMMY_9C_reg_addr                                                            "0x9803D670"
#define DUMMY_9C_reg                                                                 0x9803D670
#define set_DUMMY_9C_reg(data)   (*((volatile unsigned int*) DUMMY_9C_reg)=data)
#define get_DUMMY_9C_reg   (*((volatile unsigned int*) DUMMY_9C_reg))
#define DUMMY_9C_inst_adr                                                            "0x009C"
#define DUMMY_9C_inst                                                                0x009C
#define DUMMY_9C_Dummy_shift                                                         (0)
#define DUMMY_9C_Dummy_mask                                                          (0x000000FF)
#define DUMMY_9C_Dummy(data)                                                         (0x000000FF&((data)<<0))
#define DUMMY_9C_Dummy_src(data)                                                     ((0x000000FF&(data))>>0)
#define DUMMY_9C_get_Dummy(data)                                                     ((0x000000FF&(data))>>0)


#define DIG_TX_04                                                                    0x9803D980
#define DIG_TX_04_reg_addr                                                           "0x9803D980"
#define DIG_TX_04_reg                                                                0x9803D980
#define set_DIG_TX_04_reg(data)   (*((volatile unsigned int*) DIG_TX_04_reg)=data)
#define get_DIG_TX_04_reg   (*((volatile unsigned int*) DIG_TX_04_reg))
#define DIG_TX_04_inst_adr                                                           "0x0060"
#define DIG_TX_04_inst                                                               0x0060
#define DIG_TX_04_Reserved_shift                                                     (5)
#define DIG_TX_04_Reserved_mask                                                      (0x000000E0)
#define DIG_TX_04_Reserved(data)                                                     (0x000000E0&((data)<<5))
#define DIG_TX_04_Reserved_src(data)                                                 ((0x000000E0&(data))>>5)
#define DIG_TX_04_get_Reserved(data)                                                 ((0x000000E0&(data))>>5)
#define DIG_TX_04_reg_aux_sers_shift                                                 (2)
#define DIG_TX_04_reg_aux_sers_mask                                                  (0x0000001C)
#define DIG_TX_04_reg_aux_sers(data)                                                 (0x0000001C&((data)<<2))
#define DIG_TX_04_reg_aux_sers_src(data)                                             ((0x0000001C&(data))>>2)
#define DIG_TX_04_get_reg_aux_sers(data)                                             ((0x0000001C&(data))>>2)
#define DIG_TX_04_reg_aux_sewins_shift                                               (0)
#define DIG_TX_04_reg_aux_sewins_mask                                                (0x00000003)
#define DIG_TX_04_reg_aux_sewins(data)                                               (0x00000003&((data)<<0))
#define DIG_TX_04_reg_aux_sewins_src(data)                                           ((0x00000003&(data))>>0)
#define DIG_TX_04_get_reg_aux_sewins(data)                                           ((0x00000003&(data))>>0)


#define AUX_1                                                                        0x9803D984
#define AUX_1_reg_addr                                                               "0x9803D984"
#define AUX_1_reg                                                                    0x9803D984
#define set_AUX_1_reg(data)   (*((volatile unsigned int*) AUX_1_reg)=data)
#define get_AUX_1_reg   (*((volatile unsigned int*) AUX_1_reg))
#define AUX_1_inst_adr                                                               "0x0061"
#define AUX_1_inst                                                                   0x0061
#define AUX_1_reg_aux_vldo_shift                                                     (5)
#define AUX_1_reg_aux_vldo_mask                                                      (0x000000E0)
#define AUX_1_reg_aux_vldo(data)                                                     (0x000000E0&((data)<<5))
#define AUX_1_reg_aux_vldo_src(data)                                                 ((0x000000E0&(data))>>5)
#define AUX_1_get_reg_aux_vldo(data)                                                 ((0x000000E0&(data))>>5)
#define AUX_1_reg_aux_selvcom_shift                                                  (4)
#define AUX_1_reg_aux_selvcom_mask                                                   (0x00000010)
#define AUX_1_reg_aux_selvcom(data)                                                  (0x00000010&((data)<<4))
#define AUX_1_reg_aux_selvcom_src(data)                                              ((0x00000010&(data))>>4)
#define AUX_1_get_reg_aux_selvcom(data)                                              ((0x00000010&(data))>>4)
#define AUX_1_reg_aux_rx_adjr_p_shift                                                (0)
#define AUX_1_reg_aux_rx_adjr_p_mask                                                 (0x0000000F)
#define AUX_1_reg_aux_rx_adjr_p(data)                                                (0x0000000F&((data)<<0))
#define AUX_1_reg_aux_rx_adjr_p_src(data)                                            ((0x0000000F&(data))>>0)
#define AUX_1_get_reg_aux_rx_adjr_p(data)                                            ((0x0000000F&(data))>>0)


#define AUX_2                                                                        0x9803D988
#define AUX_2_reg_addr                                                               "0x9803D988"
#define AUX_2_reg                                                                    0x9803D988
#define set_AUX_2_reg(data)   (*((volatile unsigned int*) AUX_2_reg)=data)
#define get_AUX_2_reg   (*((volatile unsigned int*) AUX_2_reg))
#define AUX_2_inst_adr                                                               "0x0062"
#define AUX_2_inst                                                                   0x0062
#define AUX_2_reg_aux_autok_shift                                                    (7)
#define AUX_2_reg_aux_autok_mask                                                     (0x00000080)
#define AUX_2_reg_aux_autok(data)                                                    (0x00000080&((data)<<7))
#define AUX_2_reg_aux_autok_src(data)                                                ((0x00000080&(data))>>7)
#define AUX_2_get_reg_aux_autok(data)                                                ((0x00000080&(data))>>7)
#define AUX_2_reg_aux_se_fromp_shift                                                 (6)
#define AUX_2_reg_aux_se_fromp_mask                                                  (0x00000040)
#define AUX_2_reg_aux_se_fromp(data)                                                 (0x00000040&((data)<<6))
#define AUX_2_reg_aux_se_fromp_src(data)                                             ((0x00000040&(data))>>6)
#define AUX_2_get_reg_aux_se_fromp(data)                                             ((0x00000040&(data))>>6)
#define AUX_2_reg_aux_en_singleend_shift                                             (5)
#define AUX_2_reg_aux_en_singleend_mask                                              (0x00000020)
#define AUX_2_reg_aux_en_singleend(data)                                             (0x00000020&((data)<<5))
#define AUX_2_reg_aux_en_singleend_src(data)                                         ((0x00000020&(data))>>5)
#define AUX_2_get_reg_aux_en_singleend(data)                                         ((0x00000020&(data))>>5)
#define AUX_2_reg_aux_sel_threshold_shift                                            (3)
#define AUX_2_reg_aux_sel_threshold_mask                                             (0x00000018)
#define AUX_2_reg_aux_sel_threshold(data)                                            (0x00000018&((data)<<3))
#define AUX_2_reg_aux_sel_threshold_src(data)                                        ((0x00000018&(data))>>3)
#define AUX_2_get_reg_aux_sel_threshold(data)                                        ((0x00000018&(data))>>3)
#define AUX_2_reg_aux_entst_shift                                                    (2)
#define AUX_2_reg_aux_entst_mask                                                     (0x00000004)
#define AUX_2_reg_aux_entst(data)                                                    (0x00000004&((data)<<2))
#define AUX_2_reg_aux_entst_src(data)                                                ((0x00000004&(data))>>2)
#define AUX_2_get_reg_aux_entst(data)                                                ((0x00000004&(data))>>2)
#define AUX_2_reg_en_aux_psm_shift                                                   (1)
#define AUX_2_reg_en_aux_psm_mask                                                    (0x00000002)
#define AUX_2_reg_en_aux_psm(data)                                                   (0x00000002&((data)<<1))
#define AUX_2_reg_en_aux_psm_src(data)                                               ((0x00000002&(data))>>1)
#define AUX_2_get_reg_en_aux_psm(data)                                               ((0x00000002&(data))>>1)
#define AUX_2_reg_en_aux_rx_bigz0_p_shift                                            (0)
#define AUX_2_reg_en_aux_rx_bigz0_p_mask                                             (0x00000001)
#define AUX_2_reg_en_aux_rx_bigz0_p(data)                                            (0x00000001&((data)<<0))
#define AUX_2_reg_en_aux_rx_bigz0_p_src(data)                                        ((0x00000001&(data))>>0)
#define AUX_2_get_reg_en_aux_rx_bigz0_p(data)                                        ((0x00000001&(data))>>0)


#define AUX_3                                                                        0x9803D98C
#define AUX_3_reg_addr                                                               "0x9803D98C"
#define AUX_3_reg                                                                    0x9803D98C
#define set_AUX_3_reg(data)   (*((volatile unsigned int*) AUX_3_reg)=data)
#define get_AUX_3_reg   (*((volatile unsigned int*) AUX_3_reg))
#define AUX_3_inst_adr                                                               "0x0063"
#define AUX_3_inst                                                                   0x0063
#define AUX_3_reg_en_aux_psm_bias_shift                                              (7)
#define AUX_3_reg_en_aux_psm_bias_mask                                               (0x00000080)
#define AUX_3_reg_en_aux_psm_bias(data)                                              (0x00000080&((data)<<7))
#define AUX_3_reg_en_aux_psm_bias_src(data)                                          ((0x00000080&(data))>>7)
#define AUX_3_get_reg_en_aux_psm_bias(data)                                          ((0x00000080&(data))>>7)
#define AUX_3_reg_aux_tst_shift                                                      (1)
#define AUX_3_reg_aux_tst_mask                                                       (0x0000007E)
#define AUX_3_reg_aux_tst(data)                                                      (0x0000007E&((data)<<1))
#define AUX_3_reg_aux_tst_src(data)                                                  ((0x0000007E&(data))>>1)
#define AUX_3_get_reg_aux_tst(data)                                                  ((0x0000007E&(data))>>1)
#define AUX_3_reg_aux_z0_ok_shift                                                    (0)
#define AUX_3_reg_aux_z0_ok_mask                                                     (0x00000001)
#define AUX_3_reg_aux_z0_ok(data)                                                    (0x00000001&((data)<<0))
#define AUX_3_reg_aux_z0_ok_src(data)                                                ((0x00000001&(data))>>0)
#define AUX_3_get_reg_aux_z0_ok(data)                                                ((0x00000001&(data))>>0)


#define AUX_4                                                                        0x9803D990
#define AUX_4_reg_addr                                                               "0x9803D990"
#define AUX_4_reg                                                                    0x9803D990
#define set_AUX_4_reg(data)   (*((volatile unsigned int*) AUX_4_reg)=data)
#define get_AUX_4_reg   (*((volatile unsigned int*) AUX_4_reg))
#define AUX_4_inst_adr                                                               "0x0064"
#define AUX_4_inst                                                                   0x0064
#define AUX_4_reg_aux_rev76_shift                                                    (6)
#define AUX_4_reg_aux_rev76_mask                                                     (0x000000C0)
#define AUX_4_reg_aux_rev76(data)                                                    (0x000000C0&((data)<<6))
#define AUX_4_reg_aux_rev76_src(data)                                                ((0x000000C0&(data))>>6)
#define AUX_4_get_reg_aux_rev76(data)                                                ((0x000000C0&(data))>>6)
#define AUX_4_reg_aux_rev52_shift                                                    (2)
#define AUX_4_reg_aux_rev52_mask                                                     (0x0000003C)
#define AUX_4_reg_aux_rev52(data)                                                    (0x0000003C&((data)<<2))
#define AUX_4_reg_aux_rev52_src(data)                                                ((0x0000003C&(data))>>2)
#define AUX_4_get_reg_aux_rev52(data)                                                ((0x0000003C&(data))>>2)
#define AUX_4_reg_aux_rev1_shift                                                     (1)
#define AUX_4_reg_aux_rev1_mask                                                      (0x00000002)
#define AUX_4_reg_aux_rev1(data)                                                     (0x00000002&((data)<<1))
#define AUX_4_reg_aux_rev1_src(data)                                                 ((0x00000002&(data))>>1)
#define AUX_4_get_reg_aux_rev1(data)                                                 ((0x00000002&(data))>>1)
#define AUX_4_reg_aux_rev0_shift                                                     (0)
#define AUX_4_reg_aux_rev0_mask                                                      (0x00000001)
#define AUX_4_reg_aux_rev0(data)                                                     (0x00000001&((data)<<0))
#define AUX_4_reg_aux_rev0_src(data)                                                 ((0x00000001&(data))>>0)
#define AUX_4_get_reg_aux_rev0(data)                                                 ((0x00000001&(data))>>0)


#define AUX_5                                                                        0x9803D994
#define AUX_5_reg_addr                                                               "0x9803D994"
#define AUX_5_reg                                                                    0x9803D994
#define set_AUX_5_reg(data)   (*((volatile unsigned int*) AUX_5_reg)=data)
#define get_AUX_5_reg   (*((volatile unsigned int*) AUX_5_reg))
#define AUX_5_inst_adr                                                               "0x0065"
#define AUX_5_inst                                                                   0x0065
#define AUX_5_reg_aux_rstb_shift                                                     (7)
#define AUX_5_reg_aux_rstb_mask                                                      (0x00000080)
#define AUX_5_reg_aux_rstb(data)                                                     (0x00000080&((data)<<7))
#define AUX_5_reg_aux_rstb_src(data)                                                 ((0x00000080&(data))>>7)
#define AUX_5_get_reg_aux_rstb(data)                                                 ((0x00000080&(data))>>7)
#define AUX_5_reg_dda_40u_d2_shift                                                   (6)
#define AUX_5_reg_dda_40u_d2_mask                                                    (0x00000040)
#define AUX_5_reg_dda_40u_d2(data)                                                   (0x00000040&((data)<<6))
#define AUX_5_reg_dda_40u_d2_src(data)                                               ((0x00000040&(data))>>6)
#define AUX_5_get_reg_dda_40u_d2(data)                                               ((0x00000040&(data))>>6)
#define AUX_5_reg_dda_psm_40u_d2_shift                                               (5)
#define AUX_5_reg_dda_psm_40u_d2_mask                                                (0x00000020)
#define AUX_5_reg_dda_psm_40u_d2(data)                                               (0x00000020&((data)<<5))
#define AUX_5_reg_dda_psm_40u_d2_src(data)                                           ((0x00000020&(data))>>5)
#define AUX_5_get_reg_dda_psm_40u_d2(data)                                           ((0x00000020&(data))>>5)
#define AUX_5_Reserved_shift                                                         (0)
#define AUX_5_Reserved_mask                                                          (0x0000001F)
#define AUX_5_Reserved(data)                                                         (0x0000001F&((data)<<0))
#define AUX_5_Reserved_src(data)                                                     ((0x0000001F&(data))>>0)
#define AUX_5_get_Reserved(data)                                                     ((0x0000001F&(data))>>0)


#define AUX_6                                                                        0x9803D998
#define AUX_6_reg_addr                                                               "0x9803D998"
#define AUX_6_reg                                                                    0x9803D998
#define set_AUX_6_reg(data)   (*((volatile unsigned int*) AUX_6_reg)=data)
#define get_AUX_6_reg   (*((volatile unsigned int*) AUX_6_reg))
#define AUX_6_inst_adr                                                               "0x0066"
#define AUX_6_inst                                                                   0x0066
#define AUX_6_Reserved_shift                                                         (6)
#define AUX_6_Reserved_mask                                                          (0x000000C0)
#define AUX_6_Reserved(data)                                                         (0x000000C0&((data)<<6))
#define AUX_6_Reserved_src(data)                                                     ((0x000000C0&(data))>>6)
#define AUX_6_get_Reserved(data)                                                     ((0x000000C0&(data))>>6)
#define AUX_6_reg_aux_din_sel_shift                                                  (5)
#define AUX_6_reg_aux_din_sel_mask                                                   (0x00000020)
#define AUX_6_reg_aux_din_sel(data)                                                  (0x00000020&((data)<<5))
#define AUX_6_reg_aux_din_sel_src(data)                                              ((0x00000020&(data))>>5)
#define AUX_6_get_reg_aux_din_sel(data)                                              ((0x00000020&(data))>>5)
#define AUX_6_reg_en_aux_rx_bigz0_n_shift                                            (4)
#define AUX_6_reg_en_aux_rx_bigz0_n_mask                                             (0x00000010)
#define AUX_6_reg_en_aux_rx_bigz0_n(data)                                            (0x00000010&((data)<<4))
#define AUX_6_reg_en_aux_rx_bigz0_n_src(data)                                        ((0x00000010&(data))>>4)
#define AUX_6_get_reg_en_aux_rx_bigz0_n(data)                                        ((0x00000010&(data))>>4)
#define AUX_6_reg_aux_rx_adjr_n_shift                                                (0)
#define AUX_6_reg_aux_rx_adjr_n_mask                                                 (0x0000000F)
#define AUX_6_reg_aux_rx_adjr_n(data)                                                (0x0000000F&((data)<<0))
#define AUX_6_reg_aux_rx_adjr_n_src(data)                                            ((0x0000000F&(data))>>0)
#define AUX_6_get_reg_aux_rx_adjr_n(data)                                            ((0x0000000F&(data))>>0)


#define DIG_TX_03                                                                    0x9803D99C
#define DIG_TX_03_reg_addr                                                           "0x9803D99C"
#define DIG_TX_03_reg                                                                0x9803D99C
#define set_DIG_TX_03_reg(data)   (*((volatile unsigned int*) DIG_TX_03_reg)=data)
#define get_DIG_TX_03_reg   (*((volatile unsigned int*) DIG_TX_03_reg))
#define DIG_TX_03_inst_adr                                                           "0x0067"
#define DIG_TX_03_inst                                                               0x0067
#define DIG_TX_03_reg_aux_tx_adjr_p_shift                                            (4)
#define DIG_TX_03_reg_aux_tx_adjr_p_mask                                             (0x000000F0)
#define DIG_TX_03_reg_aux_tx_adjr_p(data)                                            (0x000000F0&((data)<<4))
#define DIG_TX_03_reg_aux_tx_adjr_p_src(data)                                        ((0x000000F0&(data))>>4)
#define DIG_TX_03_get_reg_aux_tx_adjr_p(data)                                        ((0x000000F0&(data))>>4)
#define DIG_TX_03_reg_aux_tx_adjr_n_shift                                            (0)
#define DIG_TX_03_reg_aux_tx_adjr_n_mask                                             (0x0000000F)
#define DIG_TX_03_reg_aux_tx_adjr_n(data)                                            (0x0000000F&((data)<<0))
#define DIG_TX_03_reg_aux_tx_adjr_n_src(data)                                        ((0x0000000F&(data))>>0)
#define DIG_TX_03_get_reg_aux_tx_adjr_n(data)                                        ((0x0000000F&(data))>>0)


#define AUX_TX_CTRL                                                                  0x9803DA80
#define AUX_TX_CTRL_reg_addr                                                         "0x9803DA80"
#define AUX_TX_CTRL_reg                                                              0x9803DA80
#define set_AUX_TX_CTRL_reg(data)   (*((volatile unsigned int*) AUX_TX_CTRL_reg)=data)
#define get_AUX_TX_CTRL_reg   (*((volatile unsigned int*) AUX_TX_CTRL_reg))
#define AUX_TX_CTRL_inst_adr                                                         "0x00A0"
#define AUX_TX_CTRL_inst                                                             0x00A0
#define AUX_TX_CTRL_Reserved_shift                                                   (1)
#define AUX_TX_CTRL_Reserved_mask                                                    (0x000000FE)
#define AUX_TX_CTRL_Reserved(data)                                                   (0x000000FE&((data)<<1))
#define AUX_TX_CTRL_Reserved_src(data)                                               ((0x000000FE&(data))>>1)
#define AUX_TX_CTRL_get_Reserved(data)                                               ((0x000000FE&(data))>>1)
#define AUX_TX_CTRL_aux_en_shift                                                     (0)
#define AUX_TX_CTRL_aux_en_mask                                                      (0x00000001)
#define AUX_TX_CTRL_aux_en(data)                                                     (0x00000001&((data)<<0))
#define AUX_TX_CTRL_aux_en_src(data)                                                 ((0x00000001&(data))>>0)
#define AUX_TX_CTRL_get_aux_en(data)                                                 ((0x00000001&(data))>>0)


#define AUX_TIMEOUT                                                                  0x9803DA84
#define AUX_TIMEOUT_reg_addr                                                         "0x9803DA84"
#define AUX_TIMEOUT_reg                                                              0x9803DA84
#define set_AUX_TIMEOUT_reg(data)   (*((volatile unsigned int*) AUX_TIMEOUT_reg)=data)
#define get_AUX_TIMEOUT_reg   (*((volatile unsigned int*) AUX_TIMEOUT_reg))
#define AUX_TIMEOUT_inst_adr                                                         "0x00A1"
#define AUX_TIMEOUT_inst                                                             0x00A1
#define AUX_TIMEOUT_aux_timeout_en_shift                                             (7)
#define AUX_TIMEOUT_aux_timeout_en_mask                                              (0x00000080)
#define AUX_TIMEOUT_aux_timeout_en(data)                                             (0x00000080&((data)<<7))
#define AUX_TIMEOUT_aux_timeout_en_src(data)                                         ((0x00000080&(data))>>7)
#define AUX_TIMEOUT_get_aux_timeout_en(data)                                         ((0x00000080&(data))>>7)
#define AUX_TIMEOUT_aux_timeout_num_shift                                            (0)
#define AUX_TIMEOUT_aux_timeout_num_mask                                             (0x0000007F)
#define AUX_TIMEOUT_aux_timeout_num(data)                                            (0x0000007F&((data)<<0))
#define AUX_TIMEOUT_aux_timeout_num_src(data)                                        ((0x0000007F&(data))>>0)
#define AUX_TIMEOUT_get_aux_timeout_num(data)                                        ((0x0000007F&(data))>>0)


#define AUX_FSM_STATUS                                                               0x9803DA88
#define AUX_FSM_STATUS_reg_addr                                                      "0x9803DA88"
#define AUX_FSM_STATUS_reg                                                           0x9803DA88
#define set_AUX_FSM_STATUS_reg(data)   (*((volatile unsigned int*) AUX_FSM_STATUS_reg)=data)
#define get_AUX_FSM_STATUS_reg   (*((volatile unsigned int*) AUX_FSM_STATUS_reg))
#define AUX_FSM_STATUS_inst_adr                                                      "0x00A2"
#define AUX_FSM_STATUS_inst                                                          0x00A2
#define AUX_FSM_STATUS_debug_sel20_shift                                             (5)
#define AUX_FSM_STATUS_debug_sel20_mask                                              (0x000000E0)
#define AUX_FSM_STATUS_debug_sel20(data)                                             (0x000000E0&((data)<<5))
#define AUX_FSM_STATUS_debug_sel20_src(data)                                         ((0x000000E0&(data))>>5)
#define AUX_FSM_STATUS_get_debug_sel20(data)                                         ((0x000000E0&(data))>>5)
#define AUX_FSM_STATUS_fsm_work_shift                                                (4)
#define AUX_FSM_STATUS_fsm_work_mask                                                 (0x00000010)
#define AUX_FSM_STATUS_fsm_work(data)                                                (0x00000010&((data)<<4))
#define AUX_FSM_STATUS_fsm_work_src(data)                                            ((0x00000010&(data))>>4)
#define AUX_FSM_STATUS_get_fsm_work(data)                                            ((0x00000010&(data))>>4)
#define AUX_FSM_STATUS_auxch_fsm_shift                                               (0)
#define AUX_FSM_STATUS_auxch_fsm_mask                                                (0x0000000F)
#define AUX_FSM_STATUS_auxch_fsm(data)                                               (0x0000000F&((data)<<0))
#define AUX_FSM_STATUS_auxch_fsm_src(data)                                           ((0x0000000F&(data))>>0)
#define AUX_FSM_STATUS_get_auxch_fsm(data)                                           ((0x0000000F&(data))>>0)


#define AUXTX_TRAN_CTRL                                                              0x9803DA8C
#define AUXTX_TRAN_CTRL_reg_addr                                                     "0x9803DA8C"
#define AUXTX_TRAN_CTRL_reg                                                          0x9803DA8C
#define set_AUXTX_TRAN_CTRL_reg(data)   (*((volatile unsigned int*) AUXTX_TRAN_CTRL_reg)=data)
#define get_AUXTX_TRAN_CTRL_reg   (*((volatile unsigned int*) AUXTX_TRAN_CTRL_reg))
#define AUXTX_TRAN_CTRL_inst_adr                                                     "0x00A3"
#define AUXTX_TRAN_CTRL_inst                                                         0x00A3
#define AUXTX_TRAN_CTRL_tx_addronly_shift                                            (7)
#define AUXTX_TRAN_CTRL_tx_addronly_mask                                             (0x00000080)
#define AUXTX_TRAN_CTRL_tx_addronly(data)                                            (0x00000080&((data)<<7))
#define AUXTX_TRAN_CTRL_tx_addronly_src(data)                                        ((0x00000080&(data))>>7)
#define AUXTX_TRAN_CTRL_get_tx_addronly(data)                                        ((0x00000080&(data))>>7)
#define AUXTX_TRAN_CTRL_aux_phy_wake_en_shift                                        (6)
#define AUXTX_TRAN_CTRL_aux_phy_wake_en_mask                                         (0x00000040)
#define AUXTX_TRAN_CTRL_aux_phy_wake_en(data)                                        (0x00000040&((data)<<6))
#define AUXTX_TRAN_CTRL_aux_phy_wake_en_src(data)                                    ((0x00000040&(data))>>6)
#define AUXTX_TRAN_CTRL_get_aux_phy_wake_en(data)                                    ((0x00000040&(data))>>6)
#define AUXTX_TRAN_CTRL_aux_fw_handle_shift                                          (5)
#define AUXTX_TRAN_CTRL_aux_fw_handle_mask                                           (0x00000020)
#define AUXTX_TRAN_CTRL_aux_fw_handle(data)                                          (0x00000020&((data)<<5))
#define AUXTX_TRAN_CTRL_aux_fw_handle_src(data)                                      ((0x00000020&(data))>>5)
#define AUXTX_TRAN_CTRL_get_aux_fw_handle(data)                                      ((0x00000020&(data))>>5)
#define AUXTX_TRAN_CTRL_Reserved_shift                                               (1)
#define AUXTX_TRAN_CTRL_Reserved_mask                                                (0x0000001E)
#define AUXTX_TRAN_CTRL_Reserved(data)                                               (0x0000001E&((data)<<1))
#define AUXTX_TRAN_CTRL_Reserved_src(data)                                           ((0x0000001E&(data))>>1)
#define AUXTX_TRAN_CTRL_get_Reserved(data)                                           ((0x0000001E&(data))>>1)
#define AUXTX_TRAN_CTRL_tx_start_shift                                               (0)
#define AUXTX_TRAN_CTRL_tx_start_mask                                                (0x00000001)
#define AUXTX_TRAN_CTRL_tx_start(data)                                               (0x00000001&((data)<<0))
#define AUXTX_TRAN_CTRL_tx_start_src(data)                                           ((0x00000001&(data))>>0)
#define AUXTX_TRAN_CTRL_get_tx_start(data)                                           ((0x00000001&(data))>>0)


#define AUXTX_REQ_CMD                                                                0x9803DA90
#define AUXTX_REQ_CMD_reg_addr                                                       "0x9803DA90"
#define AUXTX_REQ_CMD_reg                                                            0x9803DA90
#define set_AUXTX_REQ_CMD_reg(data)   (*((volatile unsigned int*) AUXTX_REQ_CMD_reg)=data)
#define get_AUXTX_REQ_CMD_reg   (*((volatile unsigned int*) AUXTX_REQ_CMD_reg))
#define AUXTX_REQ_CMD_inst_adr                                                       "0x00A4"
#define AUXTX_REQ_CMD_inst                                                           0x00A4
#define AUXTX_REQ_CMD_tx_cmd_shift                                                   (4)
#define AUXTX_REQ_CMD_tx_cmd_mask                                                    (0x000000F0)
#define AUXTX_REQ_CMD_tx_cmd(data)                                                   (0x000000F0&((data)<<4))
#define AUXTX_REQ_CMD_tx_cmd_src(data)                                               ((0x000000F0&(data))>>4)
#define AUXTX_REQ_CMD_get_tx_cmd(data)                                               ((0x000000F0&(data))>>4)
#define AUXTX_REQ_CMD_tx_addr1916_shift                                              (0)
#define AUXTX_REQ_CMD_tx_addr1916_mask                                               (0x0000000F)
#define AUXTX_REQ_CMD_tx_addr1916(data)                                              (0x0000000F&((data)<<0))
#define AUXTX_REQ_CMD_tx_addr1916_src(data)                                          ((0x0000000F&(data))>>0)
#define AUXTX_REQ_CMD_get_tx_addr1916(data)                                          ((0x0000000F&(data))>>0)


#define AUXTX_REQ_ADDR_M                                                             0x9803DA94
#define AUXTX_REQ_ADDR_M_reg_addr                                                    "0x9803DA94"
#define AUXTX_REQ_ADDR_M_reg                                                         0x9803DA94
#define set_AUXTX_REQ_ADDR_M_reg(data)   (*((volatile unsigned int*) AUXTX_REQ_ADDR_M_reg)=data)
#define get_AUXTX_REQ_ADDR_M_reg   (*((volatile unsigned int*) AUXTX_REQ_ADDR_M_reg))
#define AUXTX_REQ_ADDR_M_inst_adr                                                    "0x00A5"
#define AUXTX_REQ_ADDR_M_inst                                                        0x00A5
#define AUXTX_REQ_ADDR_M_tx_addr158_shift                                            (0)
#define AUXTX_REQ_ADDR_M_tx_addr158_mask                                             (0x000000FF)
#define AUXTX_REQ_ADDR_M_tx_addr158(data)                                            (0x000000FF&((data)<<0))
#define AUXTX_REQ_ADDR_M_tx_addr158_src(data)                                        ((0x000000FF&(data))>>0)
#define AUXTX_REQ_ADDR_M_get_tx_addr158(data)                                        ((0x000000FF&(data))>>0)


#define AUXTX_REQ_ADDR_L                                                             0x9803DA98
#define AUXTX_REQ_ADDR_L_reg_addr                                                    "0x9803DA98"
#define AUXTX_REQ_ADDR_L_reg                                                         0x9803DA98
#define set_AUXTX_REQ_ADDR_L_reg(data)   (*((volatile unsigned int*) AUXTX_REQ_ADDR_L_reg)=data)
#define get_AUXTX_REQ_ADDR_L_reg   (*((volatile unsigned int*) AUXTX_REQ_ADDR_L_reg))
#define AUXTX_REQ_ADDR_L_inst_adr                                                    "0x00A6"
#define AUXTX_REQ_ADDR_L_inst                                                        0x00A6
#define AUXTX_REQ_ADDR_L_tx_addr70_shift                                             (0)
#define AUXTX_REQ_ADDR_L_tx_addr70_mask                                              (0x000000FF)
#define AUXTX_REQ_ADDR_L_tx_addr70(data)                                             (0x000000FF&((data)<<0))
#define AUXTX_REQ_ADDR_L_tx_addr70_src(data)                                         ((0x000000FF&(data))>>0)
#define AUXTX_REQ_ADDR_L_get_tx_addr70(data)                                         ((0x000000FF&(data))>>0)


#define AUXTX_REQ_LEN                                                                0x9803DA9C
#define AUXTX_REQ_LEN_reg_addr                                                       "0x9803DA9C"
#define AUXTX_REQ_LEN_reg                                                            0x9803DA9C
#define set_AUXTX_REQ_LEN_reg(data)   (*((volatile unsigned int*) AUXTX_REQ_LEN_reg)=data)
#define get_AUXTX_REQ_LEN_reg   (*((volatile unsigned int*) AUXTX_REQ_LEN_reg))
#define AUXTX_REQ_LEN_inst_adr                                                       "0x00A7"
#define AUXTX_REQ_LEN_inst                                                           0x00A7
#define AUXTX_REQ_LEN_Reserved_shift                                                 (4)
#define AUXTX_REQ_LEN_Reserved_mask                                                  (0x000000F0)
#define AUXTX_REQ_LEN_Reserved(data)                                                 (0x000000F0&((data)<<4))
#define AUXTX_REQ_LEN_Reserved_src(data)                                             ((0x000000F0&(data))>>4)
#define AUXTX_REQ_LEN_get_Reserved(data)                                             ((0x000000F0&(data))>>4)
#define AUXTX_REQ_LEN_tx_len_shift                                                   (0)
#define AUXTX_REQ_LEN_tx_len_mask                                                    (0x0000000F)
#define AUXTX_REQ_LEN_tx_len(data)                                                   (0x0000000F&((data)<<0))
#define AUXTX_REQ_LEN_tx_len_src(data)                                               ((0x0000000F&(data))>>0)
#define AUXTX_REQ_LEN_get_tx_len(data)                                               ((0x0000000F&(data))>>0)


#define AUXTX_REQ_DATA                                                               0x9803DAA0
#define AUXTX_REQ_DATA_reg_addr                                                      "0x9803DAA0"
#define AUXTX_REQ_DATA_reg                                                           0x9803DAA0
#define set_AUXTX_REQ_DATA_reg(data)   (*((volatile unsigned int*) AUXTX_REQ_DATA_reg)=data)
#define get_AUXTX_REQ_DATA_reg   (*((volatile unsigned int*) AUXTX_REQ_DATA_reg))
#define AUXTX_REQ_DATA_inst_adr                                                      "0x00A8"
#define AUXTX_REQ_DATA_inst                                                          0x00A8
#define AUXTX_REQ_DATA_tx_data_shift                                                 (0)
#define AUXTX_REQ_DATA_tx_data_mask                                                  (0x000000FF)
#define AUXTX_REQ_DATA_tx_data(data)                                                 (0x000000FF&((data)<<0))
#define AUXTX_REQ_DATA_tx_data_src(data)                                             ((0x000000FF&(data))>>0)
#define AUXTX_REQ_DATA_get_tx_data(data)                                             ((0x000000FF&(data))>>0)


#define AUX_REPLY_CMD                                                                0x9803DAA4
#define AUX_REPLY_CMD_reg_addr                                                       "0x9803DAA4"
#define AUX_REPLY_CMD_reg                                                            0x9803DAA4
#define set_AUX_REPLY_CMD_reg(data)   (*((volatile unsigned int*) AUX_REPLY_CMD_reg)=data)
#define get_AUX_REPLY_CMD_reg   (*((volatile unsigned int*) AUX_REPLY_CMD_reg))
#define AUX_REPLY_CMD_inst_adr                                                       "0x00A9"
#define AUX_REPLY_CMD_inst                                                           0x00A9
#define AUX_REPLY_CMD_aux_rx_cmd_shift                                               (4)
#define AUX_REPLY_CMD_aux_rx_cmd_mask                                                (0x000000F0)
#define AUX_REPLY_CMD_aux_rx_cmd(data)                                               (0x000000F0&((data)<<4))
#define AUX_REPLY_CMD_aux_rx_cmd_src(data)                                           ((0x000000F0&(data))>>4)
#define AUX_REPLY_CMD_get_aux_rx_cmd(data)                                           ((0x000000F0&(data))>>4)
#define AUX_REPLY_CMD_aux_rx_len_shift                                               (0)
#define AUX_REPLY_CMD_aux_rx_len_mask                                                (0x0000000F)
#define AUX_REPLY_CMD_aux_rx_len(data)                                               (0x0000000F&((data)<<0))
#define AUX_REPLY_CMD_aux_rx_len_src(data)                                           ((0x0000000F&(data))>>0)
#define AUX_REPLY_CMD_get_aux_rx_len(data)                                           ((0x0000000F&(data))>>0)


#define AUX_REPLY_DATA                                                               0x9803DAA8
#define AUX_REPLY_DATA_reg_addr                                                      "0x9803DAA8"
#define AUX_REPLY_DATA_reg                                                           0x9803DAA8
#define set_AUX_REPLY_DATA_reg(data)   (*((volatile unsigned int*) AUX_REPLY_DATA_reg)=data)
#define get_AUX_REPLY_DATA_reg   (*((volatile unsigned int*) AUX_REPLY_DATA_reg))
#define AUX_REPLY_DATA_inst_adr                                                      "0x00AA"
#define AUX_REPLY_DATA_inst                                                          0x00AA
#define AUX_REPLY_DATA_aux_reply_data_shift                                          (0)
#define AUX_REPLY_DATA_aux_reply_data_mask                                           (0x000000FF)
#define AUX_REPLY_DATA_aux_reply_data(data)                                          (0x000000FF&((data)<<0))
#define AUX_REPLY_DATA_aux_reply_data_src(data)                                      ((0x000000FF&(data))>>0)
#define AUX_REPLY_DATA_get_aux_reply_data(data)                                      ((0x000000FF&(data))>>0)


#define AUX_FIFO_CTRL                                                                0x9803DAAC
#define AUX_FIFO_CTRL_reg_addr                                                       "0x9803DAAC"
#define AUX_FIFO_CTRL_reg                                                            0x9803DAAC
#define set_AUX_FIFO_CTRL_reg(data)   (*((volatile unsigned int*) AUX_FIFO_CTRL_reg)=data)
#define get_AUX_FIFO_CTRL_reg   (*((volatile unsigned int*) AUX_FIFO_CTRL_reg))
#define AUX_FIFO_CTRL_inst_adr                                                       "0x00AB"
#define AUX_FIFO_CTRL_inst                                                           0x00AB
#define AUX_FIFO_CTRL_Reserved_shift                                                 (5)
#define AUX_FIFO_CTRL_Reserved_mask                                                  (0x000000E0)
#define AUX_FIFO_CTRL_Reserved(data)                                                 (0x000000E0&((data)<<5))
#define AUX_FIFO_CTRL_Reserved_src(data)                                             ((0x000000E0&(data))>>5)
#define AUX_FIFO_CTRL_get_Reserved(data)                                             ((0x000000E0&(data))>>5)
#define AUX_FIFO_CTRL_i2c_req_len_sel_shift                                          (4)
#define AUX_FIFO_CTRL_i2c_req_len_sel_mask                                           (0x00000010)
#define AUX_FIFO_CTRL_i2c_req_len_sel(data)                                          (0x00000010&((data)<<4))
#define AUX_FIFO_CTRL_i2c_req_len_sel_src(data)                                      ((0x00000010&(data))>>4)
#define AUX_FIFO_CTRL_get_i2c_req_len_sel(data)                                      ((0x00000010&(data))>>4)
#define AUX_FIFO_CTRL_readfail_auto_en_shift                                         (3)
#define AUX_FIFO_CTRL_readfail_auto_en_mask                                          (0x00000008)
#define AUX_FIFO_CTRL_readfail_auto_en(data)                                         (0x00000008&((data)<<3))
#define AUX_FIFO_CTRL_readfail_auto_en_src(data)                                     ((0x00000008&(data))>>3)
#define AUX_FIFO_CTRL_get_readfail_auto_en(data)                                     ((0x00000008&(data))>>3)
#define AUX_FIFO_CTRL_force_req_intval_shift                                         (2)
#define AUX_FIFO_CTRL_force_req_intval_mask                                          (0x00000004)
#define AUX_FIFO_CTRL_force_req_intval(data)                                         (0x00000004&((data)<<2))
#define AUX_FIFO_CTRL_force_req_intval_src(data)                                     ((0x00000004&(data))>>2)
#define AUX_FIFO_CTRL_get_force_req_intval(data)                                     ((0x00000004&(data))>>2)
#define AUX_FIFO_CTRL_i2c_fifo_rst_shift                                             (1)
#define AUX_FIFO_CTRL_i2c_fifo_rst_mask                                              (0x00000002)
#define AUX_FIFO_CTRL_i2c_fifo_rst(data)                                             (0x00000002&((data)<<1))
#define AUX_FIFO_CTRL_i2c_fifo_rst_src(data)                                         ((0x00000002&(data))>>1)
#define AUX_FIFO_CTRL_get_i2c_fifo_rst(data)                                         ((0x00000002&(data))>>1)
#define AUX_FIFO_CTRL_na_fifo_rst_shift                                              (0)
#define AUX_FIFO_CTRL_na_fifo_rst_mask                                               (0x00000001)
#define AUX_FIFO_CTRL_na_fifo_rst(data)                                              (0x00000001&((data)<<0))
#define AUX_FIFO_CTRL_na_fifo_rst_src(data)                                          ((0x00000001&(data))>>0)
#define AUX_FIFO_CTRL_get_na_fifo_rst(data)                                          ((0x00000001&(data))>>0)


#define AUX_TX_FIFO_STATUS                                                           0x9803DAB0
#define AUX_TX_FIFO_STATUS_reg_addr                                                  "0x9803DAB0"
#define AUX_TX_FIFO_STATUS_reg                                                       0x9803DAB0
#define set_AUX_TX_FIFO_STATUS_reg(data)   (*((volatile unsigned int*) AUX_TX_FIFO_STATUS_reg)=data)
#define get_AUX_TX_FIFO_STATUS_reg   (*((volatile unsigned int*) AUX_TX_FIFO_STATUS_reg))
#define AUX_TX_FIFO_STATUS_inst_adr                                                  "0x00AC"
#define AUX_TX_FIFO_STATUS_inst                                                      0x00AC
#define AUX_TX_FIFO_STATUS_aux_fifo_full_shift                                       (7)
#define AUX_TX_FIFO_STATUS_aux_fifo_full_mask                                        (0x00000080)
#define AUX_TX_FIFO_STATUS_aux_fifo_full(data)                                       (0x00000080&((data)<<7))
#define AUX_TX_FIFO_STATUS_aux_fifo_full_src(data)                                   ((0x00000080&(data))>>7)
#define AUX_TX_FIFO_STATUS_get_aux_fifo_full(data)                                   ((0x00000080&(data))>>7)
#define AUX_TX_FIFO_STATUS_aux_fifo_empty_shift                                      (6)
#define AUX_TX_FIFO_STATUS_aux_fifo_empty_mask                                       (0x00000040)
#define AUX_TX_FIFO_STATUS_aux_fifo_empty(data)                                      (0x00000040&((data)<<6))
#define AUX_TX_FIFO_STATUS_aux_fifo_empty_src(data)                                  ((0x00000040&(data))>>6)
#define AUX_TX_FIFO_STATUS_get_aux_fifo_empty(data)                                  ((0x00000040&(data))>>6)
#define AUX_TX_FIFO_STATUS_Reserved_shift                                            (4)
#define AUX_TX_FIFO_STATUS_Reserved_mask                                             (0x00000030)
#define AUX_TX_FIFO_STATUS_Reserved(data)                                            (0x00000030&((data)<<4))
#define AUX_TX_FIFO_STATUS_Reserved_src(data)                                        ((0x00000030&(data))>>4)
#define AUX_TX_FIFO_STATUS_get_Reserved(data)                                        ((0x00000030&(data))>>4)
#define AUX_TX_FIFO_STATUS_na_fifo_ovf_shift                                         (3)
#define AUX_TX_FIFO_STATUS_na_fifo_ovf_mask                                          (0x00000008)
#define AUX_TX_FIFO_STATUS_na_fifo_ovf(data)                                         (0x00000008&((data)<<3))
#define AUX_TX_FIFO_STATUS_na_fifo_ovf_src(data)                                     ((0x00000008&(data))>>3)
#define AUX_TX_FIFO_STATUS_get_na_fifo_ovf(data)                                     ((0x00000008&(data))>>3)
#define AUX_TX_FIFO_STATUS_na_fifo_udf_shift                                         (2)
#define AUX_TX_FIFO_STATUS_na_fifo_udf_mask                                          (0x00000004)
#define AUX_TX_FIFO_STATUS_na_fifo_udf(data)                                         (0x00000004&((data)<<2))
#define AUX_TX_FIFO_STATUS_na_fifo_udf_src(data)                                     ((0x00000004&(data))>>2)
#define AUX_TX_FIFO_STATUS_get_na_fifo_udf(data)                                     ((0x00000004&(data))>>2)
#define AUX_TX_FIFO_STATUS_i2c_fifo_ovf_shift                                        (1)
#define AUX_TX_FIFO_STATUS_i2c_fifo_ovf_mask                                         (0x00000002)
#define AUX_TX_FIFO_STATUS_i2c_fifo_ovf(data)                                        (0x00000002&((data)<<1))
#define AUX_TX_FIFO_STATUS_i2c_fifo_ovf_src(data)                                    ((0x00000002&(data))>>1)
#define AUX_TX_FIFO_STATUS_get_i2c_fifo_ovf(data)                                    ((0x00000002&(data))>>1)
#define AUX_TX_FIFO_STATUS_i2c_fifo_udf_shift                                        (0)
#define AUX_TX_FIFO_STATUS_i2c_fifo_udf_mask                                         (0x00000001)
#define AUX_TX_FIFO_STATUS_i2c_fifo_udf(data)                                        (0x00000001&((data)<<0))
#define AUX_TX_FIFO_STATUS_i2c_fifo_udf_src(data)                                    ((0x00000001&(data))>>0)
#define AUX_TX_FIFO_STATUS_get_i2c_fifo_udf(data)                                    ((0x00000001&(data))>>0)


#define AUX_FIFO_RD_PTR                                                              0x9803DAB4
#define AUX_FIFO_RD_PTR_reg_addr                                                     "0x9803DAB4"
#define AUX_FIFO_RD_PTR_reg                                                          0x9803DAB4
#define set_AUX_FIFO_RD_PTR_reg(data)   (*((volatile unsigned int*) AUX_FIFO_RD_PTR_reg)=data)
#define get_AUX_FIFO_RD_PTR_reg   (*((volatile unsigned int*) AUX_FIFO_RD_PTR_reg))
#define AUX_FIFO_RD_PTR_inst_adr                                                     "0x00AD"
#define AUX_FIFO_RD_PTR_inst                                                         0x00AD
#define AUX_FIFO_RD_PTR_Reserved_shift                                               (5)
#define AUX_FIFO_RD_PTR_Reserved_mask                                                (0x000000E0)
#define AUX_FIFO_RD_PTR_Reserved(data)                                               (0x000000E0&((data)<<5))
#define AUX_FIFO_RD_PTR_Reserved_src(data)                                           ((0x000000E0&(data))>>5)
#define AUX_FIFO_RD_PTR_get_Reserved(data)                                           ((0x000000E0&(data))>>5)
#define AUX_FIFO_RD_PTR_rd_ptr_shift                                                 (0)
#define AUX_FIFO_RD_PTR_rd_ptr_mask                                                  (0x0000001F)
#define AUX_FIFO_RD_PTR_rd_ptr(data)                                                 (0x0000001F&((data)<<0))
#define AUX_FIFO_RD_PTR_rd_ptr_src(data)                                             ((0x0000001F&(data))>>0)
#define AUX_FIFO_RD_PTR_get_rd_ptr(data)                                             ((0x0000001F&(data))>>0)


#define AUX_FIFO_WR_PTR                                                              0x9803DAB8
#define AUX_FIFO_WR_PTR_reg_addr                                                     "0x9803DAB8"
#define AUX_FIFO_WR_PTR_reg                                                          0x9803DAB8
#define set_AUX_FIFO_WR_PTR_reg(data)   (*((volatile unsigned int*) AUX_FIFO_WR_PTR_reg)=data)
#define get_AUX_FIFO_WR_PTR_reg   (*((volatile unsigned int*) AUX_FIFO_WR_PTR_reg))
#define AUX_FIFO_WR_PTR_inst_adr                                                     "0x00AE"
#define AUX_FIFO_WR_PTR_inst                                                         0x00AE
#define AUX_FIFO_WR_PTR_Reserved_shift                                               (5)
#define AUX_FIFO_WR_PTR_Reserved_mask                                                (0x000000E0)
#define AUX_FIFO_WR_PTR_Reserved(data)                                               (0x000000E0&((data)<<5))
#define AUX_FIFO_WR_PTR_Reserved_src(data)                                           ((0x000000E0&(data))>>5)
#define AUX_FIFO_WR_PTR_get_Reserved(data)                                           ((0x000000E0&(data))>>5)
#define AUX_FIFO_WR_PTR_wr_ptr_shift                                                 (0)
#define AUX_FIFO_WR_PTR_wr_ptr_mask                                                  (0x0000001F)
#define AUX_FIFO_WR_PTR_wr_ptr(data)                                                 (0x0000001F&((data)<<0))
#define AUX_FIFO_WR_PTR_wr_ptr_src(data)                                             ((0x0000001F&(data))>>0)
#define AUX_FIFO_WR_PTR_get_wr_ptr(data)                                             ((0x0000001F&(data))>>0)


#define AUX_RETRY_1                                                                  0x9803DABC
#define AUX_RETRY_1_reg_addr                                                         "0x9803DABC"
#define AUX_RETRY_1_reg                                                              0x9803DABC
#define set_AUX_RETRY_1_reg(data)   (*((volatile unsigned int*) AUX_RETRY_1_reg)=data)
#define get_AUX_RETRY_1_reg   (*((volatile unsigned int*) AUX_RETRY_1_reg))
#define AUX_RETRY_1_inst_adr                                                         "0x00AF"
#define AUX_RETRY_1_inst                                                             0x00AF
#define AUX_RETRY_1_Reserved_shift                                                   (6)
#define AUX_RETRY_1_Reserved_mask                                                    (0x000000C0)
#define AUX_RETRY_1_Reserved(data)                                                   (0x000000C0&((data)<<6))
#define AUX_RETRY_1_Reserved_src(data)                                               ((0x000000C0&(data))>>6)
#define AUX_RETRY_1_get_Reserved(data)                                               ((0x000000C0&(data))>>6)
#define AUX_RETRY_1_retry_work_shift                                                 (5)
#define AUX_RETRY_1_retry_work_mask                                                  (0x00000020)
#define AUX_RETRY_1_retry_work(data)                                                 (0x00000020&((data)<<5))
#define AUX_RETRY_1_retry_work_src(data)                                             ((0x00000020&(data))>>5)
#define AUX_RETRY_1_get_retry_work(data)                                             ((0x00000020&(data))>>5)
#define AUX_RETRY_1_retry_lock_shift                                                 (4)
#define AUX_RETRY_1_retry_lock_mask                                                  (0x00000010)
#define AUX_RETRY_1_retry_lock(data)                                                 (0x00000010&((data)<<4))
#define AUX_RETRY_1_retry_lock_src(data)                                             ((0x00000010&(data))>>4)
#define AUX_RETRY_1_get_retry_lock(data)                                             ((0x00000010&(data))>>4)
#define AUX_RETRY_1_retry_num_shift                                                  (0)
#define AUX_RETRY_1_retry_num_mask                                                   (0x0000000F)
#define AUX_RETRY_1_retry_num(data)                                                  (0x0000000F&((data)<<0))
#define AUX_RETRY_1_retry_num_src(data)                                              ((0x0000000F&(data))>>0)
#define AUX_RETRY_1_get_retry_num(data)                                              ((0x0000000F&(data))>>0)


#define AUX_RETRY_2                                                                  0x9803DAC0
#define AUX_RETRY_2_reg_addr                                                         "0x9803DAC0"
#define AUX_RETRY_2_reg                                                              0x9803DAC0
#define set_AUX_RETRY_2_reg(data)   (*((volatile unsigned int*) AUX_RETRY_2_reg)=data)
#define get_AUX_RETRY_2_reg   (*((volatile unsigned int*) AUX_RETRY_2_reg))
#define AUX_RETRY_2_inst_adr                                                         "0x00B0"
#define AUX_RETRY_2_inst                                                             0x00B0
#define AUX_RETRY_2_retry_en_shift                                                   (7)
#define AUX_RETRY_2_retry_en_mask                                                    (0x00000080)
#define AUX_RETRY_2_retry_en(data)                                                   (0x00000080&((data)<<7))
#define AUX_RETRY_2_retry_en_src(data)                                               ((0x00000080&(data))>>7)
#define AUX_RETRY_2_get_retry_en(data)                                               ((0x00000080&(data))>>7)
#define AUX_RETRY_2_retry_defer_en_shift                                             (6)
#define AUX_RETRY_2_retry_defer_en_mask                                              (0x00000040)
#define AUX_RETRY_2_retry_defer_en(data)                                             (0x00000040&((data)<<6))
#define AUX_RETRY_2_retry_defer_en_src(data)                                         ((0x00000040&(data))>>6)
#define AUX_RETRY_2_get_retry_defer_en(data)                                         ((0x00000040&(data))>>6)
#define AUX_RETRY_2_retry_timeout_en_shift                                           (5)
#define AUX_RETRY_2_retry_timeout_en_mask                                            (0x00000020)
#define AUX_RETRY_2_retry_timeout_en(data)                                           (0x00000020&((data)<<5))
#define AUX_RETRY_2_retry_timeout_en_src(data)                                       ((0x00000020&(data))>>5)
#define AUX_RETRY_2_get_retry_timeout_en(data)                                       ((0x00000020&(data))>>5)
#define AUX_RETRY_2_retry_nack_en_shift                                              (4)
#define AUX_RETRY_2_retry_nack_en_mask                                               (0x00000010)
#define AUX_RETRY_2_retry_nack_en(data)                                              (0x00000010&((data)<<4))
#define AUX_RETRY_2_retry_nack_en_src(data)                                          ((0x00000010&(data))>>4)
#define AUX_RETRY_2_get_retry_nack_en(data)                                          ((0x00000010&(data))>>4)
#define AUX_RETRY_2_retry_error_en_shift                                             (3)
#define AUX_RETRY_2_retry_error_en_mask                                              (0x00000008)
#define AUX_RETRY_2_retry_error_en(data)                                             (0x00000008&((data)<<3))
#define AUX_RETRY_2_retry_error_en_src(data)                                         ((0x00000008&(data))>>3)
#define AUX_RETRY_2_get_retry_error_en(data)                                         ((0x00000008&(data))>>3)
#define AUX_RETRY_2_Reserved_shift                                                   (0)
#define AUX_RETRY_2_Reserved_mask                                                    (0x00000007)
#define AUX_RETRY_2_Reserved(data)                                                   (0x00000007&((data)<<0))
#define AUX_RETRY_2_Reserved_src(data)                                               ((0x00000007&(data))>>0)
#define AUX_RETRY_2_get_Reserved(data)                                               ((0x00000007&(data))>>0)


#define AUX_IRQ_EVENT                                                                0x9803DAC4
#define AUX_IRQ_EVENT_reg_addr                                                       "0x9803DAC4"
#define AUX_IRQ_EVENT_reg                                                            0x9803DAC4
#define set_AUX_IRQ_EVENT_reg(data)   (*((volatile unsigned int*) AUX_IRQ_EVENT_reg)=data)
#define get_AUX_IRQ_EVENT_reg   (*((volatile unsigned int*) AUX_IRQ_EVENT_reg))
#define AUX_IRQ_EVENT_inst_adr                                                       "0x00B1"
#define AUX_IRQ_EVENT_inst                                                           0x00B1
#define AUX_IRQ_EVENT_Reserved_shift                                                 (7)
#define AUX_IRQ_EVENT_Reserved_mask                                                  (0x00000080)
#define AUX_IRQ_EVENT_Reserved(data)                                                 (0x00000080&((data)<<7))
#define AUX_IRQ_EVENT_Reserved_src(data)                                             ((0x00000080&(data))>>7)
#define AUX_IRQ_EVENT_get_Reserved(data)                                             ((0x00000080&(data))>>7)
#define AUX_IRQ_EVENT_alpm_fail_irq_shift                                            (6)
#define AUX_IRQ_EVENT_alpm_fail_irq_mask                                             (0x00000040)
#define AUX_IRQ_EVENT_alpm_fail_irq(data)                                            (0x00000040&((data)<<6))
#define AUX_IRQ_EVENT_alpm_fail_irq_src(data)                                        ((0x00000040&(data))>>6)
#define AUX_IRQ_EVENT_get_alpm_fail_irq(data)                                        ((0x00000040&(data))>>6)
#define AUX_IRQ_EVENT_auxdone_irq_shift                                              (5)
#define AUX_IRQ_EVENT_auxdone_irq_mask                                               (0x00000020)
#define AUX_IRQ_EVENT_auxdone_irq(data)                                              (0x00000020&((data)<<5))
#define AUX_IRQ_EVENT_auxdone_irq_src(data)                                          ((0x00000020&(data))>>5)
#define AUX_IRQ_EVENT_get_auxdone_irq(data)                                          ((0x00000020&(data))>>5)
#define AUX_IRQ_EVENT_rxerror_irq_shift                                              (4)
#define AUX_IRQ_EVENT_rxerror_irq_mask                                               (0x00000010)
#define AUX_IRQ_EVENT_rxerror_irq(data)                                              (0x00000010&((data)<<4))
#define AUX_IRQ_EVENT_rxerror_irq_src(data)                                          ((0x00000010&(data))>>4)
#define AUX_IRQ_EVENT_get_rxerror_irq(data)                                          ((0x00000010&(data))>>4)
#define AUX_IRQ_EVENT_readfail_irq_shift                                             (3)
#define AUX_IRQ_EVENT_readfail_irq_mask                                              (0x00000008)
#define AUX_IRQ_EVENT_readfail_irq(data)                                             (0x00000008&((data)<<3))
#define AUX_IRQ_EVENT_readfail_irq_src(data)                                         ((0x00000008&(data))>>3)
#define AUX_IRQ_EVENT_get_readfail_irq(data)                                         ((0x00000008&(data))>>3)
#define AUX_IRQ_EVENT_nack_irq_shift                                                 (2)
#define AUX_IRQ_EVENT_nack_irq_mask                                                  (0x00000004)
#define AUX_IRQ_EVENT_nack_irq(data)                                                 (0x00000004&((data)<<2))
#define AUX_IRQ_EVENT_nack_irq_src(data)                                             ((0x00000004&(data))>>2)
#define AUX_IRQ_EVENT_get_nack_irq(data)                                             ((0x00000004&(data))>>2)
#define AUX_IRQ_EVENT_retry_irq_shift                                                (1)
#define AUX_IRQ_EVENT_retry_irq_mask                                                 (0x00000002)
#define AUX_IRQ_EVENT_retry_irq(data)                                                (0x00000002&((data)<<1))
#define AUX_IRQ_EVENT_retry_irq_src(data)                                            ((0x00000002&(data))>>1)
#define AUX_IRQ_EVENT_get_retry_irq(data)                                            ((0x00000002&(data))>>1)
#define AUX_IRQ_EVENT_timeout_irq_shift                                              (0)
#define AUX_IRQ_EVENT_timeout_irq_mask                                               (0x00000001)
#define AUX_IRQ_EVENT_timeout_irq(data)                                              (0x00000001&((data)<<0))
#define AUX_IRQ_EVENT_timeout_irq_src(data)                                          ((0x00000001&(data))>>0)
#define AUX_IRQ_EVENT_get_timeout_irq(data)                                          ((0x00000001&(data))>>0)


#define AUX_IRQ_EN                                                                   0x9803DAC8
#define AUX_IRQ_EN_reg_addr                                                          "0x9803DAC8"
#define AUX_IRQ_EN_reg                                                               0x9803DAC8
#define set_AUX_IRQ_EN_reg(data)   (*((volatile unsigned int*) AUX_IRQ_EN_reg)=data)
#define get_AUX_IRQ_EN_reg   (*((volatile unsigned int*) AUX_IRQ_EN_reg))
#define AUX_IRQ_EN_inst_adr                                                          "0x00B2"
#define AUX_IRQ_EN_inst                                                              0x00B2
#define AUX_IRQ_EN_Reserved_shift                                                    (7)
#define AUX_IRQ_EN_Reserved_mask                                                     (0x00000080)
#define AUX_IRQ_EN_Reserved(data)                                                    (0x00000080&((data)<<7))
#define AUX_IRQ_EN_Reserved_src(data)                                                ((0x00000080&(data))>>7)
#define AUX_IRQ_EN_get_Reserved(data)                                                ((0x00000080&(data))>>7)
#define AUX_IRQ_EN_alpm_irq_en_shift                                                 (6)
#define AUX_IRQ_EN_alpm_irq_en_mask                                                  (0x00000040)
#define AUX_IRQ_EN_alpm_irq_en(data)                                                 (0x00000040&((data)<<6))
#define AUX_IRQ_EN_alpm_irq_en_src(data)                                             ((0x00000040&(data))>>6)
#define AUX_IRQ_EN_get_alpm_irq_en(data)                                             ((0x00000040&(data))>>6)
#define AUX_IRQ_EN_auxdone_irq_en_shift                                              (5)
#define AUX_IRQ_EN_auxdone_irq_en_mask                                               (0x00000020)
#define AUX_IRQ_EN_auxdone_irq_en(data)                                              (0x00000020&((data)<<5))
#define AUX_IRQ_EN_auxdone_irq_en_src(data)                                          ((0x00000020&(data))>>5)
#define AUX_IRQ_EN_get_auxdone_irq_en(data)                                          ((0x00000020&(data))>>5)
#define AUX_IRQ_EN_rxerror_irq_en_shift                                              (4)
#define AUX_IRQ_EN_rxerror_irq_en_mask                                               (0x00000010)
#define AUX_IRQ_EN_rxerror_irq_en(data)                                              (0x00000010&((data)<<4))
#define AUX_IRQ_EN_rxerror_irq_en_src(data)                                          ((0x00000010&(data))>>4)
#define AUX_IRQ_EN_get_rxerror_irq_en(data)                                          ((0x00000010&(data))>>4)
#define AUX_IRQ_EN_readfail_irq_en_shift                                             (3)
#define AUX_IRQ_EN_readfail_irq_en_mask                                              (0x00000008)
#define AUX_IRQ_EN_readfail_irq_en(data)                                             (0x00000008&((data)<<3))
#define AUX_IRQ_EN_readfail_irq_en_src(data)                                         ((0x00000008&(data))>>3)
#define AUX_IRQ_EN_get_readfail_irq_en(data)                                         ((0x00000008&(data))>>3)
#define AUX_IRQ_EN_nack_irq_en_shift                                                 (2)
#define AUX_IRQ_EN_nack_irq_en_mask                                                  (0x00000004)
#define AUX_IRQ_EN_nack_irq_en(data)                                                 (0x00000004&((data)<<2))
#define AUX_IRQ_EN_nack_irq_en_src(data)                                             ((0x00000004&(data))>>2)
#define AUX_IRQ_EN_get_nack_irq_en(data)                                             ((0x00000004&(data))>>2)
#define AUX_IRQ_EN_retry_irq_en_shift                                                (1)
#define AUX_IRQ_EN_retry_irq_en_mask                                                 (0x00000002)
#define AUX_IRQ_EN_retry_irq_en(data)                                                (0x00000002&((data)<<1))
#define AUX_IRQ_EN_retry_irq_en_src(data)                                            ((0x00000002&(data))>>1)
#define AUX_IRQ_EN_get_retry_irq_en(data)                                            ((0x00000002&(data))>>1)
#define AUX_IRQ_EN_timeout_irq_en_shift                                              (0)
#define AUX_IRQ_EN_timeout_irq_en_mask                                               (0x00000001)
#define AUX_IRQ_EN_timeout_irq_en(data)                                              (0x00000001&((data)<<0))
#define AUX_IRQ_EN_timeout_irq_en_src(data)                                          ((0x00000001&(data))>>0)
#define AUX_IRQ_EN_get_timeout_irq_en(data)                                          ((0x00000001&(data))>>0)


#define AUX_DIG_PHY2                                                                 0x9803DBC0
#define AUX_DIG_PHY2_reg_addr                                                        "0x9803DBC0"
#define AUX_DIG_PHY2_reg                                                             0x9803DBC0
#define set_AUX_DIG_PHY2_reg(data)   (*((volatile unsigned int*) AUX_DIG_PHY2_reg)=data)
#define get_AUX_DIG_PHY2_reg   (*((volatile unsigned int*) AUX_DIG_PHY2_reg))
#define AUX_DIG_PHY2_inst_adr                                                        "0x00F0"
#define AUX_DIG_PHY2_inst                                                            0x00F0
#define AUX_DIG_PHY2_ave_pos_shift                                                   (3)
#define AUX_DIG_PHY2_ave_pos_mask                                                    (0x000000F8)
#define AUX_DIG_PHY2_ave_pos(data)                                                   (0x000000F8&((data)<<3))
#define AUX_DIG_PHY2_ave_pos_src(data)                                               ((0x000000F8&(data))>>3)
#define AUX_DIG_PHY2_get_ave_pos(data)                                               ((0x000000F8&(data))>>3)
#define AUX_DIG_PHY2_aux_50duty_control_shift                                        (2)
#define AUX_DIG_PHY2_aux_50duty_control_mask                                         (0x00000004)
#define AUX_DIG_PHY2_aux_50duty_control(data)                                        (0x00000004&((data)<<2))
#define AUX_DIG_PHY2_aux_50duty_control_src(data)                                    ((0x00000004&(data))>>2)
#define AUX_DIG_PHY2_get_aux_50duty_control(data)                                    ((0x00000004&(data))>>2)
#define AUX_DIG_PHY2_rsv_aux_dig_phy2_shift                                          (1)
#define AUX_DIG_PHY2_rsv_aux_dig_phy2_mask                                           (0x00000002)
#define AUX_DIG_PHY2_rsv_aux_dig_phy2(data)                                          (0x00000002&((data)<<1))
#define AUX_DIG_PHY2_rsv_aux_dig_phy2_src(data)                                      ((0x00000002&(data))>>1)
#define AUX_DIG_PHY2_get_rsv_aux_dig_phy2(data)                                      ((0x00000002&(data))>>1)
#define AUX_DIG_PHY2_aux_pn_swap_shift                                               (0)
#define AUX_DIG_PHY2_aux_pn_swap_mask                                                (0x00000001)
#define AUX_DIG_PHY2_aux_pn_swap(data)                                               (0x00000001&((data)<<0))
#define AUX_DIG_PHY2_aux_pn_swap_src(data)                                           ((0x00000001&(data))>>0)
#define AUX_DIG_PHY2_get_aux_pn_swap(data)                                           ((0x00000001&(data))>>0)


#define AUX_DIG_PHY3                                                                 0x9803DBC4
#define AUX_DIG_PHY3_reg_addr                                                        "0x9803DBC4"
#define AUX_DIG_PHY3_reg                                                             0x9803DBC4
#define set_AUX_DIG_PHY3_reg(data)   (*((volatile unsigned int*) AUX_DIG_PHY3_reg)=data)
#define get_AUX_DIG_PHY3_reg   (*((volatile unsigned int*) AUX_DIG_PHY3_reg))
#define AUX_DIG_PHY3_inst_adr                                                        "0x00F1"
#define AUX_DIG_PHY3_inst                                                            0x00F1
#define AUX_DIG_PHY3_aux_clksel_auto_en_shift                                        (7)
#define AUX_DIG_PHY3_aux_clksel_auto_en_mask                                         (0x00000080)
#define AUX_DIG_PHY3_aux_clksel_auto_en(data)                                        (0x00000080&((data)<<7))
#define AUX_DIG_PHY3_aux_clksel_auto_en_src(data)                                    ((0x00000080&(data))>>7)
#define AUX_DIG_PHY3_get_aux_clksel_auto_en(data)                                    ((0x00000080&(data))>>7)
#define AUX_DIG_PHY3_Reserved_shift                                                  (0)
#define AUX_DIG_PHY3_Reserved_mask                                                   (0x0000007F)
#define AUX_DIG_PHY3_Reserved(data)                                                  (0x0000007F&((data)<<0))
#define AUX_DIG_PHY3_Reserved_src(data)                                              ((0x0000007F&(data))>>0)
#define AUX_DIG_PHY3_get_Reserved(data)                                              ((0x0000007F&(data))>>0)


#define AUX_DIG_PHY4                                                                 0x9803DBC8
#define AUX_DIG_PHY4_reg_addr                                                        "0x9803DBC8"
#define AUX_DIG_PHY4_reg                                                             0x9803DBC8
#define set_AUX_DIG_PHY4_reg(data)   (*((volatile unsigned int*) AUX_DIG_PHY4_reg)=data)
#define get_AUX_DIG_PHY4_reg   (*((volatile unsigned int*) AUX_DIG_PHY4_reg))
#define AUX_DIG_PHY4_inst_adr                                                        "0x00F2"
#define AUX_DIG_PHY4_inst                                                            0x00F2
#define AUX_DIG_PHY4_Reserved_shift                                                  (5)
#define AUX_DIG_PHY4_Reserved_mask                                                   (0x000000E0)
#define AUX_DIG_PHY4_Reserved(data)                                                  (0x000000E0&((data)<<5))
#define AUX_DIG_PHY4_Reserved_src(data)                                              ((0x000000E0&(data))>>5)
#define AUX_DIG_PHY4_get_Reserved(data)                                              ((0x000000E0&(data))>>5)
#define AUX_DIG_PHY4_pcharge_num_shift                                               (0)
#define AUX_DIG_PHY4_pcharge_num_mask                                                (0x0000001F)
#define AUX_DIG_PHY4_pcharge_num(data)                                               (0x0000001F&((data)<<0))
#define AUX_DIG_PHY4_pcharge_num_src(data)                                           ((0x0000001F&(data))>>0)
#define AUX_DIG_PHY4_get_pcharge_num(data)                                           ((0x0000001F&(data))>>0)


#define AUX_DIG_PHY5                                                                 0x9803DBCC
#define AUX_DIG_PHY5_reg_addr                                                        "0x9803DBCC"
#define AUX_DIG_PHY5_reg                                                             0x9803DBCC
#define set_AUX_DIG_PHY5_reg(data)   (*((volatile unsigned int*) AUX_DIG_PHY5_reg)=data)
#define get_AUX_DIG_PHY5_reg   (*((volatile unsigned int*) AUX_DIG_PHY5_reg))
#define AUX_DIG_PHY5_inst_adr                                                        "0x00F3"
#define AUX_DIG_PHY5_inst                                                            0x00F3
#define AUX_DIG_PHY5_ave_man_en_shift                                                (7)
#define AUX_DIG_PHY5_ave_man_en_mask                                                 (0x00000080)
#define AUX_DIG_PHY5_ave_man_en(data)                                                (0x00000080&((data)<<7))
#define AUX_DIG_PHY5_ave_man_en_src(data)                                            ((0x00000080&(data))>>7)
#define AUX_DIG_PHY5_get_ave_man_en(data)                                            ((0x00000080&(data))>>7)
#define AUX_DIG_PHY5_ave_num_shift                                                   (0)
#define AUX_DIG_PHY5_ave_num_mask                                                    (0x0000007F)
#define AUX_DIG_PHY5_ave_num(data)                                                   (0x0000007F&((data)<<0))
#define AUX_DIG_PHY5_ave_num_src(data)                                               ((0x0000007F&(data))>>0)
#define AUX_DIG_PHY5_get_ave_num(data)                                               ((0x0000007F&(data))>>0)


#define AUX_DIG_PHY6                                                                 0x9803DBD0
#define AUX_DIG_PHY6_reg_addr                                                        "0x9803DBD0"
#define AUX_DIG_PHY6_reg                                                             0x9803DBD0
#define set_AUX_DIG_PHY6_reg(data)   (*((volatile unsigned int*) AUX_DIG_PHY6_reg)=data)
#define get_AUX_DIG_PHY6_reg   (*((volatile unsigned int*) AUX_DIG_PHY6_reg))
#define AUX_DIG_PHY6_inst_adr                                                        "0x00F4"
#define AUX_DIG_PHY6_inst                                                            0x00F4
#define AUX_DIG_PHY6_tx_clk1m_factor_shift                                           (0)
#define AUX_DIG_PHY6_tx_clk1m_factor_mask                                            (0x000000FF)
#define AUX_DIG_PHY6_tx_clk1m_factor(data)                                           (0x000000FF&((data)<<0))
#define AUX_DIG_PHY6_tx_clk1m_factor_src(data)                                       ((0x000000FF&(data))>>0)
#define AUX_DIG_PHY6_get_tx_clk1m_factor(data)                                       ((0x000000FF&(data))>>0)


#define AUX_DIG_PHY7                                                                 0x9803DBD4
#define AUX_DIG_PHY7_reg_addr                                                        "0x9803DBD4"
#define AUX_DIG_PHY7_reg                                                             0x9803DBD4
#define set_AUX_DIG_PHY7_reg(data)   (*((volatile unsigned int*) AUX_DIG_PHY7_reg)=data)
#define get_AUX_DIG_PHY7_reg   (*((volatile unsigned int*) AUX_DIG_PHY7_reg))
#define AUX_DIG_PHY7_inst_adr                                                        "0x00F5"
#define AUX_DIG_PHY7_inst                                                            0x00F5
#define AUX_DIG_PHY7_aux_phy_int_en_shift                                            (7)
#define AUX_DIG_PHY7_aux_phy_int_en_mask                                             (0x00000080)
#define AUX_DIG_PHY7_aux_phy_int_en(data)                                            (0x00000080&((data)<<7))
#define AUX_DIG_PHY7_aux_phy_int_en_src(data)                                        ((0x00000080&(data))>>7)
#define AUX_DIG_PHY7_get_aux_phy_int_en(data)                                        ((0x00000080&(data))>>7)
#define AUX_DIG_PHY7_aux_phy_int_shift                                               (6)
#define AUX_DIG_PHY7_aux_phy_int_mask                                                (0x00000040)
#define AUX_DIG_PHY7_aux_phy_int(data)                                               (0x00000040&((data)<<6))
#define AUX_DIG_PHY7_aux_phy_int_src(data)                                           ((0x00000040&(data))>>6)
#define AUX_DIG_PHY7_get_aux_phy_int(data)                                           ((0x00000040&(data))>>6)
#define AUX_DIG_PHY7_Reserved_shift                                                  (0)
#define AUX_DIG_PHY7_Reserved_mask                                                   (0x0000003F)
#define AUX_DIG_PHY7_Reserved(data)                                                  (0x0000003F&((data)<<0))
#define AUX_DIG_PHY7_Reserved_src(data)                                              ((0x0000003F&(data))>>0)
#define AUX_DIG_PHY7_get_Reserved(data)                                              ((0x0000003F&(data))>>0)


#define AUX_DIG_PHY8                                                                 0x9803DBD8
#define AUX_DIG_PHY8_reg_addr                                                        "0x9803DBD8"
#define AUX_DIG_PHY8_reg                                                             0x9803DBD8
#define set_AUX_DIG_PHY8_reg(data)   (*((volatile unsigned int*) AUX_DIG_PHY8_reg)=data)
#define get_AUX_DIG_PHY8_reg   (*((volatile unsigned int*) AUX_DIG_PHY8_reg))
#define AUX_DIG_PHY8_inst_adr                                                        "0x00F6"
#define AUX_DIG_PHY8_inst                                                            0x00F6
#define AUX_DIG_PHY8_Reserved_shift                                                  (6)
#define AUX_DIG_PHY8_Reserved_mask                                                   (0x000000C0)
#define AUX_DIG_PHY8_Reserved(data)                                                  (0x000000C0&((data)<<6))
#define AUX_DIG_PHY8_Reserved_src(data)                                              ((0x000000C0&(data))>>6)
#define AUX_DIG_PHY8_get_Reserved(data)                                              ((0x000000C0&(data))>>6)
#define AUX_DIG_PHY8_error_handle_shift                                              (5)
#define AUX_DIG_PHY8_error_handle_mask                                               (0x00000020)
#define AUX_DIG_PHY8_error_handle(data)                                              (0x00000020&((data)<<5))
#define AUX_DIG_PHY8_error_handle_src(data)                                          ((0x00000020&(data))>>5)
#define AUX_DIG_PHY8_get_error_handle(data)                                          ((0x00000020&(data))>>5)
#define AUX_DIG_PHY8_sync1_wo_idle_shift                                             (4)
#define AUX_DIG_PHY8_sync1_wo_idle_mask                                              (0x00000010)
#define AUX_DIG_PHY8_sync1_wo_idle(data)                                             (0x00000010&((data)<<4))
#define AUX_DIG_PHY8_sync1_wo_idle_src(data)                                         ((0x00000010&(data))>>4)
#define AUX_DIG_PHY8_get_sync1_wo_idle(data)                                         ((0x00000010&(data))>>4)
#define AUX_DIG_PHY8_ehandle_man_dis_shift                                           (3)
#define AUX_DIG_PHY8_ehandle_man_dis_mask                                            (0x00000008)
#define AUX_DIG_PHY8_ehandle_man_dis(data)                                           (0x00000008&((data)<<3))
#define AUX_DIG_PHY8_ehandle_man_dis_src(data)                                       ((0x00000008&(data))>>3)
#define AUX_DIG_PHY8_get_ehandle_man_dis(data)                                       ((0x00000008&(data))>>3)
#define AUX_DIG_PHY8_ehandle_stop_dis_shift                                          (2)
#define AUX_DIG_PHY8_ehandle_stop_dis_mask                                           (0x00000004)
#define AUX_DIG_PHY8_ehandle_stop_dis(data)                                          (0x00000004&((data)<<2))
#define AUX_DIG_PHY8_ehandle_stop_dis_src(data)                                      ((0x00000004&(data))>>2)
#define AUX_DIG_PHY8_get_ehandle_stop_dis(data)                                      ((0x00000004&(data))>>2)
#define AUX_DIG_PHY8_ehandle_syncend_dis_shift                                       (1)
#define AUX_DIG_PHY8_ehandle_syncend_dis_mask                                        (0x00000002)
#define AUX_DIG_PHY8_ehandle_syncend_dis(data)                                       (0x00000002&((data)<<1))
#define AUX_DIG_PHY8_ehandle_syncend_dis_src(data)                                   ((0x00000002&(data))>>1)
#define AUX_DIG_PHY8_get_ehandle_syncend_dis(data)                                   ((0x00000002&(data))>>1)
#define AUX_DIG_PHY8_ehandle_8x_dis_shift                                            (0)
#define AUX_DIG_PHY8_ehandle_8x_dis_mask                                             (0x00000001)
#define AUX_DIG_PHY8_ehandle_8x_dis(data)                                            (0x00000001&((data)<<0))
#define AUX_DIG_PHY8_ehandle_8x_dis_src(data)                                        ((0x00000001&(data))>>0)
#define AUX_DIG_PHY8_get_ehandle_8x_dis(data)                                        ((0x00000001&(data))>>0)


#define AUX_DIG_PHY9                                                                 0x9803DBDC
#define AUX_DIG_PHY9_reg_addr                                                        "0x9803DBDC"
#define AUX_DIG_PHY9_reg                                                             0x9803DBDC
#define set_AUX_DIG_PHY9_reg(data)   (*((volatile unsigned int*) AUX_DIG_PHY9_reg)=data)
#define get_AUX_DIG_PHY9_reg   (*((volatile unsigned int*) AUX_DIG_PHY9_reg))
#define AUX_DIG_PHY9_inst_adr                                                        "0x00F7"
#define AUX_DIG_PHY9_inst                                                            0x00F7
#define AUX_DIG_PHY9_single_end_mode_shift                                           (7)
#define AUX_DIG_PHY9_single_end_mode_mask                                            (0x00000080)
#define AUX_DIG_PHY9_single_end_mode(data)                                           (0x00000080&((data)<<7))
#define AUX_DIG_PHY9_single_end_mode_src(data)                                       ((0x00000080&(data))>>7)
#define AUX_DIG_PHY9_get_single_end_mode(data)                                       ((0x00000080&(data))>>7)
#define AUX_DIG_PHY9_Reserved_shift                                                  (4)
#define AUX_DIG_PHY9_Reserved_mask                                                   (0x00000070)
#define AUX_DIG_PHY9_Reserved(data)                                                  (0x00000070&((data)<<4))
#define AUX_DIG_PHY9_Reserved_src(data)                                              ((0x00000070&(data))>>4)
#define AUX_DIG_PHY9_get_Reserved(data)                                              ((0x00000070&(data))>>4)
#define AUX_DIG_PHY9_man_error_shift                                                 (3)
#define AUX_DIG_PHY9_man_error_mask                                                  (0x00000008)
#define AUX_DIG_PHY9_man_error(data)                                                 (0x00000008&((data)<<3))
#define AUX_DIG_PHY9_man_error_src(data)                                             ((0x00000008&(data))>>3)
#define AUX_DIG_PHY9_get_man_error(data)                                             ((0x00000008&(data))>>3)
#define AUX_DIG_PHY9_stop_error_shift                                                (2)
#define AUX_DIG_PHY9_stop_error_mask                                                 (0x00000004)
#define AUX_DIG_PHY9_stop_error(data)                                                (0x00000004&((data)<<2))
#define AUX_DIG_PHY9_stop_error_src(data)                                            ((0x00000004&(data))>>2)
#define AUX_DIG_PHY9_get_stop_error(data)                                            ((0x00000004&(data))>>2)
#define AUX_DIG_PHY9_syncend_error_shift                                             (1)
#define AUX_DIG_PHY9_syncend_error_mask                                              (0x00000002)
#define AUX_DIG_PHY9_syncend_error(data)                                             (0x00000002&((data)<<1))
#define AUX_DIG_PHY9_syncend_error_src(data)                                         ((0x00000002&(data))>>1)
#define AUX_DIG_PHY9_get_syncend_error(data)                                         ((0x00000002&(data))>>1)
#define AUX_DIG_PHY9_data_8x_error_shift                                             (0)
#define AUX_DIG_PHY9_data_8x_error_mask                                              (0x00000001)
#define AUX_DIG_PHY9_data_8x_error(data)                                             (0x00000001&((data)<<0))
#define AUX_DIG_PHY9_data_8x_error_src(data)                                         ((0x00000001&(data))>>0)
#define AUX_DIG_PHY9_get_data_8x_error(data)                                         ((0x00000001&(data))>>0)


#define AUX_DEBUG                                                                    0x9803DBE0
#define AUX_DEBUG_reg_addr                                                           "0x9803DBE0"
#define AUX_DEBUG_reg                                                                0x9803DBE0
#define set_AUX_DEBUG_reg(data)   (*((volatile unsigned int*) AUX_DEBUG_reg)=data)
#define get_AUX_DEBUG_reg   (*((volatile unsigned int*) AUX_DEBUG_reg))
#define AUX_DEBUG_inst_adr                                                           "0x00F8"
#define AUX_DEBUG_inst                                                               0x00F8
#define AUX_DEBUG_aux_d1_shift                                                       (7)
#define AUX_DEBUG_aux_d1_mask                                                        (0x00000080)
#define AUX_DEBUG_aux_d1(data)                                                       (0x00000080&((data)<<7))
#define AUX_DEBUG_aux_d1_src(data)                                                   ((0x00000080&(data))>>7)
#define AUX_DEBUG_get_aux_d1(data)                                                   ((0x00000080&(data))>>7)
#define AUX_DEBUG_aux_d2_shift                                                       (6)
#define AUX_DEBUG_aux_d2_mask                                                        (0x00000040)
#define AUX_DEBUG_aux_d2(data)                                                       (0x00000040&((data)<<6))
#define AUX_DEBUG_aux_d2_src(data)                                                   ((0x00000040&(data))>>6)
#define AUX_DEBUG_get_aux_d2(data)                                                   ((0x00000040&(data))>>6)
#define AUX_DEBUG_Reserved_shift                                                     (3)
#define AUX_DEBUG_Reserved_mask                                                      (0x00000038)
#define AUX_DEBUG_Reserved(data)                                                     (0x00000038&((data)<<3))
#define AUX_DEBUG_Reserved_src(data)                                                 ((0x00000038&(data))>>3)
#define AUX_DEBUG_get_Reserved(data)                                                 ((0x00000038&(data))>>3)
#define AUX_DEBUG_fsm_state_shift                                                    (0)
#define AUX_DEBUG_fsm_state_mask                                                     (0x00000007)
#define AUX_DEBUG_fsm_state(data)                                                    (0x00000007&((data)<<0))
#define AUX_DEBUG_fsm_state_src(data)                                                ((0x00000007&(data))>>0)
#define AUX_DEBUG_get_fsm_state(data)                                                ((0x00000007&(data))>>0)


#endif
