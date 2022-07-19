/**************************************************************
// Spec Version                  : 0.0.1
// Parser Version                : DVR_Parser_6.3
// CModelGen Version             : 5.0 2009.04.09
// Naming Rule                   :  Register_Name
// Naming Rule                   : Module_Register_Name_reg
// Parse Option                  : Only Parse _op1
// Parse Address Region          : All Address Region 
// Decode bit number             : 12 bits
// Firmware Header Generate Date : 2014/5/8 11:0:19
***************************************************************/


#ifndef _CBUS_TX_REG_H_INCLUDED_
#define _CBUS_TX_REG_H_INCLUDED_
#ifdef  _CBUS_TX_USE_STRUCT
typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     sys_clk_div:3;
unsigned int     clk_1m_div:8;
unsigned int     abs_thres_en:1;
unsigned int     reserved_1:1;
unsigned int     sync0_hb:9;
unsigned int     sync0_lb:9;
}CBUS_CTRL0;

typedef struct 
{
unsigned int     parity_time:8;
unsigned int     abs_threshold:8;
unsigned int     sync1_hb:8;
unsigned int     sync1_lb:8;
}CBUS_CTRL1;

typedef struct 
{
unsigned int     vendor_id:8;
unsigned int     reserved_0:1;
unsigned int     ack_0:7;
unsigned int     reserved_1:1;
unsigned int     ack_fall:7;
unsigned int     reserved_2:3;
unsigned int     parity_limit:5;
}CBUS_CTRL2;

typedef struct 
{
unsigned int     tx_bit_time:8;
unsigned int     reserved_0:1;
unsigned int     tx_ack_fal:7;
unsigned int     reserved_1:1;
unsigned int     tx_ack_low_hb:7;
unsigned int     reserved_2:1;
unsigned int     tx_ack_low_lb:7;
}CBUS_CTRL3;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     glob_time:2;
unsigned int     link_time:5;
unsigned int     req_hold:4;
unsigned int     resp_hold:4;
unsigned int     wait_time:4;
unsigned int     fast_reply_en:1;
unsigned int     drv_str:2;
unsigned int     drv_hi_cbus:6;
unsigned int     retry_lv:3;
}CBUS_CTRL4;

typedef struct 
{
unsigned int     burst_wait:4;
unsigned int     fw_rxsense_en:1;
unsigned int     mhl_conn:1;
unsigned int     fw_path_en:1;
unsigned int     send_path:1;
unsigned int     req_opp_flt:8;
unsigned int     req_opp_int:2;
unsigned int     chk_point:6;
unsigned int     reserved_0:3;
unsigned int     avoid_conf:1;
unsigned int     reserved_1:1;
unsigned int     cbus_imp_fw_en:1;
unsigned int     z_5k_on:1;
unsigned int     z_10k_on:1;
}CBUS_CTRL5;

typedef struct 
{
unsigned int     wake_pulse_width1:2;
unsigned int     dis_chk_high:3;
unsigned int     reserved_0:1;
unsigned int     wake_pulse_width2:4;
unsigned int     src_cbus_float:4;
unsigned int     src_pulse_width:7;
unsigned int     src_conn:2;
unsigned int     rxsense_deglitch:9;
}CBUS_CTRL6;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     wake_to_discover:10;
unsigned int     src_vbus_cbus_stable:10;
unsigned int     vbus_out_to_stable:10;
}CBUS_CTRL7;

typedef struct 
{
unsigned int     req_cont:8;
unsigned int     src_arbitrate:3;
unsigned int     pulse_count:5;
unsigned int     wait_sink_float:1;
unsigned int     sink_cbus_float:2;
unsigned int     reserved_0:3;
unsigned int     rxsense_chk:10;
}CBUS_CTRL8;

typedef struct 
{
unsigned int     reserved_0:13;
unsigned int     retry_flag:1;
unsigned int     link_err:1;
unsigned int     conflict_err:1;
unsigned int     sync_bit_time:8;
unsigned int     reserved_1:4;
unsigned int     discovery_st:3;
unsigned int     write_data:1;
}CBUS_STATUS;

typedef struct 
{
unsigned int     fw0_req:1;
unsigned int     fw0_tx_case:3;
unsigned int     fw0_wait_case:2;
unsigned int     fw0_head:2;
unsigned int     fw0_fifo_clr:1;
unsigned int     reserved_0:23;
}FW0_CMD_INF;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     fw0_cmd2:8;
unsigned int     fw0_offset:8;
unsigned int     fw0_cmd1:8;
}FW0_CMD;

typedef struct 
{
unsigned int     fw0_cmd_rcv:8;
unsigned int     fw0_data_rcv:8;
unsigned int     fw0_rcv_err:1;
unsigned int     fw0_fifo_full:1;
unsigned int     fw0_fifo_empty:1;
unsigned int     fw0_fifo_len:5;
unsigned int     fw0_rty_ovr:1;
unsigned int     msc_hpd:1;
unsigned int     reserved_0:5;
unsigned int     write_data:1;
}FW0_STATUS;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     fw0_data:8;
}FW0_WDATA;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     fw0_rdata:8;
}FW0_RDATA;

typedef struct 
{
unsigned int     scr_offset:8;
unsigned int     sta_offset:8;
unsigned int     int_offset:8;
unsigned int     cap_offset:8;
}DEVCAP_OFFSET;

typedef struct 
{
unsigned int     que_fsm:4;
unsigned int     sch_fsm:4;
unsigned int     burst_timeout:1;
unsigned int     reserved_0:22;
unsigned int     write_data:1;
}MSC_STATUS;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     ucpk_rcv:8;
unsigned int     ucp_rcv:8;
unsigned int     ucpe_rcv:8;
}MSG_STATUS1;

typedef struct 
{
unsigned int     msge_rcv:8;
unsigned int     rcpk_rcv:8;
unsigned int     rcp_rcv:8;
unsigned int     rcpe_rcv:8;
}MSG_STATUS2;

typedef struct 
{
unsigned int     rap_rcv:8;
unsigned int     rapk_rcv:8;
unsigned int     msg_dat:8;
unsigned int     msg_cmd:8;
}MSG_STATUS3;

typedef struct 
{
unsigned int     wb_id_chk:1;
unsigned int     rcp_reply_nack:1;
unsigned int     rcp_reply_abort:1;
unsigned int     reserved_0:5;
unsigned int     fwdef_cmd_rev:8;
unsigned int     reserved_1:16;
}ADOPTERID_CTRL;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     reserved_1:8;
unsigned int     adop_idl_rcv:8;
unsigned int     adop_idh_rcv:8;
}RCV_ADOPTER_ID;

typedef struct 
{
unsigned int     mcumsc_en:1;
unsigned int     reserved_0:1;
unsigned int     msc_wait_arb:1;
unsigned int     rx_fifo_clr:1;
unsigned int     reserved_1:1;
unsigned int     reserved_2:1;
unsigned int     que_fsm_clr:1;
unsigned int     sch_fsm_clr:1;
unsigned int     reserved_3:24;
}MSC_CTRL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     msc_err_code:8;
}MSC_BURST_DATA;

typedef struct 
{
unsigned int     rx_fifo_full:1;
unsigned int     rx_fifo_empty:1;
unsigned int     reserved_0:1;
unsigned int     na_rx_len:5;
unsigned int     reserved_1:8;
unsigned int     na_msc_offset:8;
unsigned int     na_msc_cmd:8;
}MSC_RCV_CMD;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     rx_fifo_data:8;
}MSC_RCV_DATA;

typedef struct 
{
unsigned int     msc_err_force:1;
unsigned int     reserved_0:23;
unsigned int     msc_err_fw:8;
}MSC_WRITE_ERR_CODE;

typedef struct 
{
unsigned int     ddc_rdy:1;
unsigned int     ddc_cmd_type:3;
unsigned int     ddc_num:4;
unsigned int     ddc_nack_limit:8;
unsigned int     reserved_0:5;
unsigned int     ddc_err_code_clr:1;
unsigned int     ddc_prior_dis:1;
unsigned int     ddc_fsm_clr:1;
unsigned int     reserved_1:5;
unsigned int     ddc_nack_retry:1;
unsigned int     ddc_wait_case:1;
unsigned int     ddc_fw_en:1;
}DDC_CMD_INF;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     ddc_segval:8;
unsigned int     ddc_offset:8;
unsigned int     ddc_devaddr:8;
}DDC_CMD_DATA;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     ddc_wdata:8;
}DDC_WD;

typedef struct 
{
unsigned int     reserved_0:11;
unsigned int     ddc_fsm:5;
unsigned int     reserved_1:8;
unsigned int     ddc_rdata:8;
}DDC_RD;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     ddc_fifo_full:1;
unsigned int     ddc_fifo_empty:1;
unsigned int     ddc_err_code:8;
unsigned int     reserved_1:8;
unsigned int     ddc_wp:4;
unsigned int     ddc_rp:4;
}DDC_STATUS;

typedef struct 
{
unsigned int     ddc_err_force:1;
unsigned int     reserved_0:23;
unsigned int     ddc_err_fw:8;
}DDC_WRITE_ERR_CODE;

typedef struct 
{
unsigned int     wr_stat_irq:1;
unsigned int     rd_devcap_irq:1;
unsigned int     get_stat_irq:1;
unsigned int     get_id_irq:1;
unsigned int     get_msg_irq:1;
unsigned int     sc1_err_irq:1;
unsigned int     ddc_err_irq:1;
unsigned int     msc_err_irq:1;
unsigned int     wr_burst_irq:1;
unsigned int     sc3_err_irq:1;
unsigned int     fwdef_cmd_irq:1;
unsigned int     allmsc_cmd_irq:1;
unsigned int     abort_res_irq:1;
unsigned int     abort_req_irq:1;
unsigned int     ddc_abort_irq:1;
unsigned int     ddc_nack_irq:1;
unsigned int     msge_irq:1;
unsigned int     rcp_irq:1;
unsigned int     rcpk_irq:1;
unsigned int     rcpe_irq:1;
unsigned int     rap_irq:1;
unsigned int     rapk_irq:1;
unsigned int     ucp_irq:1;
unsigned int     ucpe_irq:1;
unsigned int     ucpk_irq:1;
unsigned int     msg_sub_irq:1;
unsigned int     det_rxsense_irq:1;
unsigned int     msc_hpd_irq:1;
unsigned int     reserved_0:4;
}MSC_IRQ;

typedef struct 
{
unsigned int     wr_stat_irq_en:1;
unsigned int     rd_devcap_irq_en:1;
unsigned int     get_stat_irq_en:1;
unsigned int     get_id_irq_en:1;
unsigned int     get_msg_irq_en:1;
unsigned int     sc1_err_irq_en:1;
unsigned int     ddc_err_irq_en:1;
unsigned int     msc_err_irq_en:1;
unsigned int     wr_burst_irq_en:1;
unsigned int     sc3_err_irq_en:1;
unsigned int     fwdef_cmd_irq_en:1;
unsigned int     allmsc_cmd_irq_en:1;
unsigned int     abort_res_irq_en:1;
unsigned int     abort_req_irq_en:1;
unsigned int     ddc_abort_irq_en:1;
unsigned int     ddc_nack_irq_en:1;
unsigned int     msge_irq_en:1;
unsigned int     rcp_irq_en:1;
unsigned int     rcpk_irq_en:1;
unsigned int     rcpe_irq_en:1;
unsigned int     rap_irq_en:1;
unsigned int     rapk_irq_en:1;
unsigned int     ucp_irq_en:1;
unsigned int     ucpe_irq_en:1;
unsigned int     ucpk_irq_en:1;
unsigned int     msg_sub_irq_en:1;
unsigned int     det_rxsense_irq_en:1;
unsigned int     msc_hpd_irq_en:1;
unsigned int     reserved_0:4;
}MSC_IRQ_EN;

typedef struct 
{
unsigned int     fw0_fin_irq_en:1;
unsigned int     fw0_cmd_irq_en:1;
unsigned int     fw0_data_irq_en:1;
unsigned int     reserved_0:5;
unsigned int     ddc_fin_irq_en:1;
unsigned int     reserved_1:7;
unsigned int     clk_mode_irq_en:1;
unsigned int     dcap_rdy_irq_en:1;
unsigned int     muted_chg_irq_en:1;
unsigned int     path_en_irq_en:1;
unsigned int     det_z1k_irq_en:1;
unsigned int     sink_det_irq_en:1;
unsigned int     parity_err_irq_en:1;
unsigned int     disconn_irq_en:1;
unsigned int     det_hpd_irq_en:1;
unsigned int     reserved_2:7;
}CBUS_TX_INT;

typedef struct 
{
unsigned int     fw0_fin_irq:1;
unsigned int     fw0_cmd_irq:1;
unsigned int     fw0_data_irq:1;
unsigned int     reserved_0:5;
unsigned int     ddc_fin_irq:1;
unsigned int     reserved_1:7;
unsigned int     clk_mode_chg:1;
unsigned int     dcap_rdy_chg:1;
unsigned int     muted_chg:1;
unsigned int     path_en_chg:1;
unsigned int     det_z1k_irq:1;
unsigned int     sink_det_irq:1;
unsigned int     parity_err_irq:1;
unsigned int     disconn_irq:1;
unsigned int     det_hpd_irq:1;
unsigned int     reserved_2:7;
}CBUS_TX_INT1;

typedef struct 
{
unsigned int     chg23_irq_en:8;
unsigned int     chg22_irq_en:8;
unsigned int     dchg_bit7_irq_en:1;
unsigned int     dchg_bit6_irq_en:1;
unsigned int     dchg_bit5_irq_en:1;
unsigned int     dchg_bit4_irq_en:1;
unsigned int     dchg_bit3_irq_en:1;
unsigned int     dchg_bit2_irq_en:1;
unsigned int     edid_irq_en:1;
unsigned int     dchg_bit0_irq_en:1;
unsigned int     rchg_irq_en:3;
unsigned int     req_3d_irq_en:1;
unsigned int     grt_irq_en:1;
unsigned int     req_irq_en:1;
unsigned int     dscr_irq_en:1;
unsigned int     dcap_irq_en:1;
}DEVCAP_INT_EN;

typedef struct 
{
unsigned int     chg27_irq_en:8;
unsigned int     chg26_irq_en:8;
unsigned int     chg25_irq_en:8;
unsigned int     chg24_irq_en:8;
}DEVCAP_INT_EN1;

typedef struct 
{
unsigned int     cbus_test_md:2;
unsigned int     fw_out:1;
unsigned int     dbg_sel:3;
unsigned int     reserved_0:26;
}CBUS_TEST;

typedef struct 
{
unsigned int     reg_mhl_bmos_en_tx:1;
unsigned int     reg_mhl_hpd_det_tx:1;
unsigned int     reg_mhl_r1k_det_tx:1;
unsigned int     reg_r1k_vth_sel_tx:1;
unsigned int     reg_mhl_tst_en_tx:1;
unsigned int     reg_mhl_vsel_tx:3;
unsigned int     reg_mhl_r10k_tx:3;
unsigned int     reg_cbus_strc_tx:3;
unsigned int     reg_en_bias_txrx:1;
unsigned int     tst_sel_h_tx:2;
unsigned int     reg_mhl_r10k_test_tx:1;
unsigned int     reserved_0:14;
}PHY_CTRL;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     hdmi_hpd_out_tx:1;
unsigned int     hdmi_hpd_en_tx:1;
unsigned int     rego_mhl_hpd_det_tx:1;
unsigned int     rego_mhl_r1k_det_tx:1;
}PHY_STATUS;

typedef struct 
{
unsigned int     reserved_0:5;
unsigned int     deb_lv:3;
unsigned int     reserved_1:4;
unsigned int     det_r1k_cnt:4;
unsigned int     reserved_2:6;
unsigned int     clk_1k_div:10;
}CBUS_CTRL9;

typedef struct 
{
unsigned int     dummy_reg:32;
}DUMMY_CTRL;

typedef struct 
{
unsigned int     link_layer_st:4;
unsigned int     reserved_0:2;
unsigned int     hw_en_10k:1;
unsigned int     hw_en_5k:1;
unsigned int     reserved_1:6;
unsigned int     det_r1k_st:2;
unsigned int     reserved_2:4;
unsigned int     hw_mhl_hpd_det:1;
unsigned int     hw_mhl_r1k_det:1;
unsigned int     hw_mhl_bmos_en:1;
unsigned int     hw_mhl_vtl_sel:1;
unsigned int     reserved_3:3;
unsigned int     fw_rst_r1k_st:1;
unsigned int     reserved_4:2;
unsigned int     fw_r1k_det_en:1;
unsigned int     fw_r1k_det:1;
}CBUS_CTRL10;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     msc_offset_adr:7;
unsigned int     devcap_rdata:8;
unsigned int     reserved_1:7;
unsigned int     devcap_write:1;
unsigned int     msc_reg_data:8;
}DEVCAP_WRITE;

typedef struct 
{
unsigned int     adop_id_h:8;
unsigned int     dev_cat:1;
unsigned int     plim:2;
unsigned int     pow:1;
unsigned int     dev_type:4;
unsigned int     mhl_ver:8;
unsigned int     dev_state:8;
}MSC_DEVCAP0;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     aud_link_md:6;
unsigned int     aud_8ch:1;
unsigned int     aud_2ch:1;
unsigned int     vid_link_md:2;
unsigned int     supp_vga:1;
unsigned int     supp_islands:1;
unsigned int     supp_ppixel:1;
unsigned int     supp_yuv422:1;
unsigned int     supp_yuv444:1;
unsigned int     supp_rgb444:1;
unsigned int     adop_id_l:8;
}MSC_DEVCAP1;

typedef struct 
{
unsigned int     device_id_h:8;
unsigned int     feature_flag:3;
unsigned int     ucp_recv_supp:1;
unsigned int     ucp_send_supp:1;
unsigned int     sp_supp:1;
unsigned int     rap_supp:1;
unsigned int     rcp_supp:1;
unsigned int     reserved_0:8;
unsigned int     ld_gui:1;
unsigned int     ld_speaker:1;
unsigned int     ld_record:1;
unsigned int     ld_tuner:1;
unsigned int     ld_media:1;
unsigned int     ld_audio:1;
unsigned int     ld_video:1;
unsigned int     ld_display:1;
}MSC_DEVCAP2;

typedef struct 
{
unsigned int     cap_0f:8;
unsigned int     stat_size:4;
unsigned int     int_size:4;
unsigned int     scratchpad_size:8;
unsigned int     device_id_l:8;
}MSC_DEVCAP3;

typedef struct 
{
unsigned int     chg23_irq:8;
unsigned int     chg22_irq:8;
unsigned int     dchg_irq:6;
unsigned int     edid_chg:1;
unsigned int     dchg_irq_0:1;
unsigned int     rchg_irq:3;
unsigned int     3d_req:1;
unsigned int     grt_wrt:1;
unsigned int     req_wrt:1;
unsigned int     dscr_chg:1;
unsigned int     dcap_chg:1;
}MSC_DEVCAP4;

typedef struct 
{
unsigned int     chg27_irq:8;
unsigned int     chg26_irq:8;
unsigned int     chg25_irq:8;
unsigned int     chg24_irq:8;
}MSC_DEVCAP5;

typedef struct 
{
unsigned int     reserved_0:32;
}MSC_DEVCAP6;

typedef struct 
{
unsigned int     reserved_0:32;
}MSC_DEVCAP7;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     reserved_1:8;
unsigned int     reserved_2:3;
unsigned int     muted:1;
unsigned int     path_en:1;
unsigned int     clk_mode:3;
unsigned int     reserved_3:7;
unsigned int     dcap_rdy:1;
}MSC_DEVCAP8;

typedef struct 
{
unsigned int     reserved_0:32;
}MSC_DEVCAP9;

typedef struct 
{
unsigned int     reserved_0:32;
}MSC_DEVCAP10;

typedef struct 
{
unsigned int     reserved_0:32;
}MSC_DEVCAP11;

typedef struct 
{
unsigned int     scratchpad_reg0:32;
}MSC_DEVCAP12;

typedef struct 
{
unsigned int     scratchpad_reg1:32;
}MSC_DEVCAP13;

typedef struct 
{
unsigned int     scratchpad_reg2:32;
}MSC_DEVCAP14;

typedef struct 
{
unsigned int     scratchpad_reg3:32;
}MSC_DEVCAP15;

typedef struct 
{
unsigned int     scratchpad_reg4:32;
}MSC_DEVCAP16;

typedef struct 
{
unsigned int     scratchpad_reg5:32;
}MSC_DEVCAP17;

typedef struct 
{
unsigned int     scratchpad_reg6:32;
}MSC_DEVCAP18;

typedef struct 
{
unsigned int     scratchpad_reg7:32;
}MSC_DEVCAP19;

#endif

#define CBUS_CTRL0                                                                   0x00
#define CBUS_CTRL0_reg_addr                                                          "0x98037B00"
#define CBUS_CTRL0_reg                                                               0x98037B00
#define set_CBUS_CTRL0_reg(data)   (*((volatile unsigned int*) CBUS_CTRL0_reg)=data)
#define get_CBUS_CTRL0_reg   (*((volatile unsigned int*) CBUS_CTRL0_reg))
#define CBUS_CTRL0_inst_adr                                                          "0x0000"
#define CBUS_CTRL0_inst                                                              0x0000
#define CBUS_CTRL0_sys_clk_div_shift                                                 (28)
#define CBUS_CTRL0_sys_clk_div_mask                                                  (0x70000000)
#define CBUS_CTRL0_sys_clk_div(data)                                                 (0x70000000&((data)<<28))
#define CBUS_CTRL0_sys_clk_div_src(data)                                             ((0x70000000&(data))>>28)
#define CBUS_CTRL0_get_sys_clk_div(data)                                             ((0x70000000&(data))>>28)
#define CBUS_CTRL0_clk_1m_div_shift                                                  (20)
#define CBUS_CTRL0_clk_1m_div_mask                                                   (0x0FF00000)
#define CBUS_CTRL0_clk_1m_div(data)                                                  (0x0FF00000&((data)<<20))
#define CBUS_CTRL0_clk_1m_div_src(data)                                              ((0x0FF00000&(data))>>20)
#define CBUS_CTRL0_get_clk_1m_div(data)                                              ((0x0FF00000&(data))>>20)
#define CBUS_CTRL0_abs_thres_en_shift                                                (19)
#define CBUS_CTRL0_abs_thres_en_mask                                                 (0x00080000)
#define CBUS_CTRL0_abs_thres_en(data)                                                (0x00080000&((data)<<19))
#define CBUS_CTRL0_abs_thres_en_src(data)                                            ((0x00080000&(data))>>19)
#define CBUS_CTRL0_get_abs_thres_en(data)                                            ((0x00080000&(data))>>19)
#define CBUS_CTRL0_sync0_hb_shift                                                    (9)
#define CBUS_CTRL0_sync0_hb_mask                                                     (0x0003FE00)
#define CBUS_CTRL0_sync0_hb(data)                                                    (0x0003FE00&((data)<<9))
#define CBUS_CTRL0_sync0_hb_src(data)                                                ((0x0003FE00&(data))>>9)
#define CBUS_CTRL0_get_sync0_hb(data)                                                ((0x0003FE00&(data))>>9)
#define CBUS_CTRL0_sync0_lb_shift                                                    (0)
#define CBUS_CTRL0_sync0_lb_mask                                                     (0x000001FF)
#define CBUS_CTRL0_sync0_lb(data)                                                    (0x000001FF&((data)<<0))
#define CBUS_CTRL0_sync0_lb_src(data)                                                ((0x000001FF&(data))>>0)
#define CBUS_CTRL0_get_sync0_lb(data)                                                ((0x000001FF&(data))>>0)


#define CBUS_CTRL1                                                                   0x04
#define CBUS_CTRL1_reg_addr                                                          "0x98037B04"
#define CBUS_CTRL1_reg                                                               0x98037B04
#define set_CBUS_CTRL1_reg(data)   (*((volatile unsigned int*) CBUS_CTRL1_reg)=data)
#define get_CBUS_CTRL1_reg   (*((volatile unsigned int*) CBUS_CTRL1_reg))
#define CBUS_CTRL1_inst_adr                                                          "0x0001"
#define CBUS_CTRL1_inst                                                              0x0001
#define CBUS_CTRL1_parity_time_shift                                                 (24)
#define CBUS_CTRL1_parity_time_mask                                                  (0xFF000000)
#define CBUS_CTRL1_parity_time(data)                                                 (0xFF000000&((data)<<24))
#define CBUS_CTRL1_parity_time_src(data)                                             ((0xFF000000&(data))>>24)
#define CBUS_CTRL1_get_parity_time(data)                                             ((0xFF000000&(data))>>24)
#define CBUS_CTRL1_abs_threshold_shift                                               (16)
#define CBUS_CTRL1_abs_threshold_mask                                                (0x00FF0000)
#define CBUS_CTRL1_abs_threshold(data)                                               (0x00FF0000&((data)<<16))
#define CBUS_CTRL1_abs_threshold_src(data)                                           ((0x00FF0000&(data))>>16)
#define CBUS_CTRL1_get_abs_threshold(data)                                           ((0x00FF0000&(data))>>16)
#define CBUS_CTRL1_sync1_hb_shift                                                    (8)
#define CBUS_CTRL1_sync1_hb_mask                                                     (0x0000FF00)
#define CBUS_CTRL1_sync1_hb(data)                                                    (0x0000FF00&((data)<<8))
#define CBUS_CTRL1_sync1_hb_src(data)                                                ((0x0000FF00&(data))>>8)
#define CBUS_CTRL1_get_sync1_hb(data)                                                ((0x0000FF00&(data))>>8)
#define CBUS_CTRL1_sync1_lb_shift                                                    (0)
#define CBUS_CTRL1_sync1_lb_mask                                                     (0x000000FF)
#define CBUS_CTRL1_sync1_lb(data)                                                    (0x000000FF&((data)<<0))
#define CBUS_CTRL1_sync1_lb_src(data)                                                ((0x000000FF&(data))>>0)
#define CBUS_CTRL1_get_sync1_lb(data)                                                ((0x000000FF&(data))>>0)


#define CBUS_CTRL2                                                                   0x08
#define CBUS_CTRL2_reg_addr                                                          "0x98037B08"
#define CBUS_CTRL2_reg                                                               0x98037B08
#define set_CBUS_CTRL2_reg(data)   (*((volatile unsigned int*) CBUS_CTRL2_reg)=data)
#define get_CBUS_CTRL2_reg   (*((volatile unsigned int*) CBUS_CTRL2_reg))
#define CBUS_CTRL2_inst_adr                                                          "0x0002"
#define CBUS_CTRL2_inst                                                              0x0002
#define CBUS_CTRL2_vendor_id_shift                                                   (24)
#define CBUS_CTRL2_vendor_id_mask                                                    (0xFF000000)
#define CBUS_CTRL2_vendor_id(data)                                                   (0xFF000000&((data)<<24))
#define CBUS_CTRL2_vendor_id_src(data)                                               ((0xFF000000&(data))>>24)
#define CBUS_CTRL2_get_vendor_id(data)                                               ((0xFF000000&(data))>>24)
#define CBUS_CTRL2_ack_0_shift                                                       (16)
#define CBUS_CTRL2_ack_0_mask                                                        (0x007F0000)
#define CBUS_CTRL2_ack_0(data)                                                       (0x007F0000&((data)<<16))
#define CBUS_CTRL2_ack_0_src(data)                                                   ((0x007F0000&(data))>>16)
#define CBUS_CTRL2_get_ack_0(data)                                                   ((0x007F0000&(data))>>16)
#define CBUS_CTRL2_ack_fall_shift                                                    (8)
#define CBUS_CTRL2_ack_fall_mask                                                     (0x00007F00)
#define CBUS_CTRL2_ack_fall(data)                                                    (0x00007F00&((data)<<8))
#define CBUS_CTRL2_ack_fall_src(data)                                                ((0x00007F00&(data))>>8)
#define CBUS_CTRL2_get_ack_fall(data)                                                ((0x00007F00&(data))>>8)
#define CBUS_CTRL2_parity_limit_shift                                                (0)
#define CBUS_CTRL2_parity_limit_mask                                                 (0x0000001F)
#define CBUS_CTRL2_parity_limit(data)                                                (0x0000001F&((data)<<0))
#define CBUS_CTRL2_parity_limit_src(data)                                            ((0x0000001F&(data))>>0)
#define CBUS_CTRL2_get_parity_limit(data)                                            ((0x0000001F&(data))>>0)


#define CBUS_CTRL3                                                                   0x0C
#define CBUS_CTRL3_reg_addr                                                          "0x98037B0C"
#define CBUS_CTRL3_reg                                                               0x98037B0C
#define set_CBUS_CTRL3_reg(data)   (*((volatile unsigned int*) CBUS_CTRL3_reg)=data)
#define get_CBUS_CTRL3_reg   (*((volatile unsigned int*) CBUS_CTRL3_reg))
#define CBUS_CTRL3_inst_adr                                                          "0x0003"
#define CBUS_CTRL3_inst                                                              0x0003
#define CBUS_CTRL3_tx_bit_time_shift                                                 (24)
#define CBUS_CTRL3_tx_bit_time_mask                                                  (0xFF000000)
#define CBUS_CTRL3_tx_bit_time(data)                                                 (0xFF000000&((data)<<24))
#define CBUS_CTRL3_tx_bit_time_src(data)                                             ((0xFF000000&(data))>>24)
#define CBUS_CTRL3_get_tx_bit_time(data)                                             ((0xFF000000&(data))>>24)
#define CBUS_CTRL3_tx_ack_fal_shift                                                  (16)
#define CBUS_CTRL3_tx_ack_fal_mask                                                   (0x007F0000)
#define CBUS_CTRL3_tx_ack_fal(data)                                                  (0x007F0000&((data)<<16))
#define CBUS_CTRL3_tx_ack_fal_src(data)                                              ((0x007F0000&(data))>>16)
#define CBUS_CTRL3_get_tx_ack_fal(data)                                              ((0x007F0000&(data))>>16)
#define CBUS_CTRL3_tx_ack_low_hb_shift                                               (8)
#define CBUS_CTRL3_tx_ack_low_hb_mask                                                (0x00007F00)
#define CBUS_CTRL3_tx_ack_low_hb(data)                                               (0x00007F00&((data)<<8))
#define CBUS_CTRL3_tx_ack_low_hb_src(data)                                           ((0x00007F00&(data))>>8)
#define CBUS_CTRL3_get_tx_ack_low_hb(data)                                           ((0x00007F00&(data))>>8)
#define CBUS_CTRL3_tx_ack_low_lb_shift                                               (0)
#define CBUS_CTRL3_tx_ack_low_lb_mask                                                (0x0000007F)
#define CBUS_CTRL3_tx_ack_low_lb(data)                                               (0x0000007F&((data)<<0))
#define CBUS_CTRL3_tx_ack_low_lb_src(data)                                           ((0x0000007F&(data))>>0)
#define CBUS_CTRL3_get_tx_ack_low_lb(data)                                           ((0x0000007F&(data))>>0)


#define CBUS_CTRL4                                                                   0x10
#define CBUS_CTRL4_reg_addr                                                          "0x98037B10"
#define CBUS_CTRL4_reg                                                               0x98037B10
#define set_CBUS_CTRL4_reg(data)   (*((volatile unsigned int*) CBUS_CTRL4_reg)=data)
#define get_CBUS_CTRL4_reg   (*((volatile unsigned int*) CBUS_CTRL4_reg))
#define CBUS_CTRL4_inst_adr                                                          "0x0004"
#define CBUS_CTRL4_inst                                                              0x0004
#define CBUS_CTRL4_glob_time_shift                                                   (29)
#define CBUS_CTRL4_glob_time_mask                                                    (0x60000000)
#define CBUS_CTRL4_glob_time(data)                                                   (0x60000000&((data)<<29))
#define CBUS_CTRL4_glob_time_src(data)                                               ((0x60000000&(data))>>29)
#define CBUS_CTRL4_get_glob_time(data)                                               ((0x60000000&(data))>>29)
#define CBUS_CTRL4_link_time_shift                                                   (24)
#define CBUS_CTRL4_link_time_mask                                                    (0x1F000000)
#define CBUS_CTRL4_link_time(data)                                                   (0x1F000000&((data)<<24))
#define CBUS_CTRL4_link_time_src(data)                                               ((0x1F000000&(data))>>24)
#define CBUS_CTRL4_get_link_time(data)                                               ((0x1F000000&(data))>>24)
#define CBUS_CTRL4_req_hold_shift                                                    (20)
#define CBUS_CTRL4_req_hold_mask                                                     (0x00F00000)
#define CBUS_CTRL4_req_hold(data)                                                    (0x00F00000&((data)<<20))
#define CBUS_CTRL4_req_hold_src(data)                                                ((0x00F00000&(data))>>20)
#define CBUS_CTRL4_get_req_hold(data)                                                ((0x00F00000&(data))>>20)
#define CBUS_CTRL4_resp_hold_shift                                                   (16)
#define CBUS_CTRL4_resp_hold_mask                                                    (0x000F0000)
#define CBUS_CTRL4_resp_hold(data)                                                   (0x000F0000&((data)<<16))
#define CBUS_CTRL4_resp_hold_src(data)                                               ((0x000F0000&(data))>>16)
#define CBUS_CTRL4_get_resp_hold(data)                                               ((0x000F0000&(data))>>16)
#define CBUS_CTRL4_wait_time_shift                                                   (12)
#define CBUS_CTRL4_wait_time_mask                                                    (0x0000F000)
#define CBUS_CTRL4_wait_time(data)                                                   (0x0000F000&((data)<<12))
#define CBUS_CTRL4_wait_time_src(data)                                               ((0x0000F000&(data))>>12)
#define CBUS_CTRL4_get_wait_time(data)                                               ((0x0000F000&(data))>>12)
#define CBUS_CTRL4_fast_reply_en_shift                                               (11)
#define CBUS_CTRL4_fast_reply_en_mask                                                (0x00000800)
#define CBUS_CTRL4_fast_reply_en(data)                                               (0x00000800&((data)<<11))
#define CBUS_CTRL4_fast_reply_en_src(data)                                           ((0x00000800&(data))>>11)
#define CBUS_CTRL4_get_fast_reply_en(data)                                           ((0x00000800&(data))>>11)
#define CBUS_CTRL4_drv_str_shift                                                     (9)
#define CBUS_CTRL4_drv_str_mask                                                      (0x00000600)
#define CBUS_CTRL4_drv_str(data)                                                     (0x00000600&((data)<<9))
#define CBUS_CTRL4_drv_str_src(data)                                                 ((0x00000600&(data))>>9)
#define CBUS_CTRL4_get_drv_str(data)                                                 ((0x00000600&(data))>>9)
#define CBUS_CTRL4_drv_hi_cbus_shift                                                 (3)
#define CBUS_CTRL4_drv_hi_cbus_mask                                                  (0x000001F8)
#define CBUS_CTRL4_drv_hi_cbus(data)                                                 (0x000001F8&((data)<<3))
#define CBUS_CTRL4_drv_hi_cbus_src(data)                                             ((0x000001F8&(data))>>3)
#define CBUS_CTRL4_get_drv_hi_cbus(data)                                             ((0x000001F8&(data))>>3)
#define CBUS_CTRL4_retry_lv_shift                                                    (0)
#define CBUS_CTRL4_retry_lv_mask                                                     (0x00000007)
#define CBUS_CTRL4_retry_lv(data)                                                    (0x00000007&((data)<<0))
#define CBUS_CTRL4_retry_lv_src(data)                                                ((0x00000007&(data))>>0)
#define CBUS_CTRL4_get_retry_lv(data)                                                ((0x00000007&(data))>>0)


#define CBUS_CTRL5                                                                   0x14
#define CBUS_CTRL5_reg_addr                                                          "0x98037B14"
#define CBUS_CTRL5_reg                                                               0x98037B14
#define set_CBUS_CTRL5_reg(data)   (*((volatile unsigned int*) CBUS_CTRL5_reg)=data)
#define get_CBUS_CTRL5_reg   (*((volatile unsigned int*) CBUS_CTRL5_reg))
#define CBUS_CTRL5_inst_adr                                                          "0x0005"
#define CBUS_CTRL5_inst                                                              0x0005
#define CBUS_CTRL5_burst_wait_shift                                                  (28)
#define CBUS_CTRL5_burst_wait_mask                                                   (0xF0000000)
#define CBUS_CTRL5_burst_wait(data)                                                  (0xF0000000&((data)<<28))
#define CBUS_CTRL5_burst_wait_src(data)                                              ((0xF0000000&(data))>>28)
#define CBUS_CTRL5_get_burst_wait(data)                                              ((0xF0000000&(data))>>28)
#define CBUS_CTRL5_fw_rxsense_en_shift                                               (27)
#define CBUS_CTRL5_fw_rxsense_en_mask                                                (0x08000000)
#define CBUS_CTRL5_fw_rxsense_en(data)                                               (0x08000000&((data)<<27))
#define CBUS_CTRL5_fw_rxsense_en_src(data)                                           ((0x08000000&(data))>>27)
#define CBUS_CTRL5_get_fw_rxsense_en(data)                                           ((0x08000000&(data))>>27)
#define CBUS_CTRL5_mhl_conn_shift                                                    (26)
#define CBUS_CTRL5_mhl_conn_mask                                                     (0x04000000)
#define CBUS_CTRL5_mhl_conn(data)                                                    (0x04000000&((data)<<26))
#define CBUS_CTRL5_mhl_conn_src(data)                                                ((0x04000000&(data))>>26)
#define CBUS_CTRL5_get_mhl_conn(data)                                                ((0x04000000&(data))>>26)
#define CBUS_CTRL5_fw_path_en_shift                                                  (25)
#define CBUS_CTRL5_fw_path_en_mask                                                   (0x02000000)
#define CBUS_CTRL5_fw_path_en(data)                                                  (0x02000000&((data)<<25))
#define CBUS_CTRL5_fw_path_en_src(data)                                              ((0x02000000&(data))>>25)
#define CBUS_CTRL5_get_fw_path_en(data)                                              ((0x02000000&(data))>>25)
#define CBUS_CTRL5_send_path_shift                                                   (24)
#define CBUS_CTRL5_send_path_mask                                                    (0x01000000)
#define CBUS_CTRL5_send_path(data)                                                   (0x01000000&((data)<<24))
#define CBUS_CTRL5_send_path_src(data)                                               ((0x01000000&(data))>>24)
#define CBUS_CTRL5_get_send_path(data)                                               ((0x01000000&(data))>>24)
#define CBUS_CTRL5_req_opp_flt_shift                                                 (16)
#define CBUS_CTRL5_req_opp_flt_mask                                                  (0x00FF0000)
#define CBUS_CTRL5_req_opp_flt(data)                                                 (0x00FF0000&((data)<<16))
#define CBUS_CTRL5_req_opp_flt_src(data)                                             ((0x00FF0000&(data))>>16)
#define CBUS_CTRL5_get_req_opp_flt(data)                                             ((0x00FF0000&(data))>>16)
#define CBUS_CTRL5_req_opp_int_shift                                                 (14)
#define CBUS_CTRL5_req_opp_int_mask                                                  (0x0000C000)
#define CBUS_CTRL5_req_opp_int(data)                                                 (0x0000C000&((data)<<14))
#define CBUS_CTRL5_req_opp_int_src(data)                                             ((0x0000C000&(data))>>14)
#define CBUS_CTRL5_get_req_opp_int(data)                                             ((0x0000C000&(data))>>14)
#define CBUS_CTRL5_chk_point_shift                                                   (8)
#define CBUS_CTRL5_chk_point_mask                                                    (0x00003F00)
#define CBUS_CTRL5_chk_point(data)                                                   (0x00003F00&((data)<<8))
#define CBUS_CTRL5_chk_point_src(data)                                               ((0x00003F00&(data))>>8)
#define CBUS_CTRL5_get_chk_point(data)                                               ((0x00003F00&(data))>>8)
#define CBUS_CTRL5_avoid_conf_shift                                                  (4)
#define CBUS_CTRL5_avoid_conf_mask                                                   (0x00000010)
#define CBUS_CTRL5_avoid_conf(data)                                                  (0x00000010&((data)<<4))
#define CBUS_CTRL5_avoid_conf_src(data)                                              ((0x00000010&(data))>>4)
#define CBUS_CTRL5_get_avoid_conf(data)                                              ((0x00000010&(data))>>4)
#define CBUS_CTRL5_cbus_imp_fw_en_shift                                              (2)
#define CBUS_CTRL5_cbus_imp_fw_en_mask                                               (0x00000004)
#define CBUS_CTRL5_cbus_imp_fw_en(data)                                              (0x00000004&((data)<<2))
#define CBUS_CTRL5_cbus_imp_fw_en_src(data)                                          ((0x00000004&(data))>>2)
#define CBUS_CTRL5_get_cbus_imp_fw_en(data)                                          ((0x00000004&(data))>>2)
#define CBUS_CTRL5_z_5k_on_shift                                                     (1)
#define CBUS_CTRL5_z_5k_on_mask                                                      (0x00000002)
#define CBUS_CTRL5_z_5k_on(data)                                                     (0x00000002&((data)<<1))
#define CBUS_CTRL5_z_5k_on_src(data)                                                 ((0x00000002&(data))>>1)
#define CBUS_CTRL5_get_z_5k_on(data)                                                 ((0x00000002&(data))>>1)
#define CBUS_CTRL5_z_10k_on_shift                                                    (0)
#define CBUS_CTRL5_z_10k_on_mask                                                     (0x00000001)
#define CBUS_CTRL5_z_10k_on(data)                                                    (0x00000001&((data)<<0))
#define CBUS_CTRL5_z_10k_on_src(data)                                                ((0x00000001&(data))>>0)
#define CBUS_CTRL5_get_z_10k_on(data)                                                ((0x00000001&(data))>>0)


#define CBUS_CTRL6                                                                   0x18
#define CBUS_CTRL6_reg_addr                                                          "0x98037B18"
#define CBUS_CTRL6_reg                                                               0x98037B18
#define set_CBUS_CTRL6_reg(data)   (*((volatile unsigned int*) CBUS_CTRL6_reg)=data)
#define get_CBUS_CTRL6_reg   (*((volatile unsigned int*) CBUS_CTRL6_reg))
#define CBUS_CTRL6_inst_adr                                                          "0x0006"
#define CBUS_CTRL6_inst                                                              0x0006
#define CBUS_CTRL6_wake_pulse_width1_shift                                           (30)
#define CBUS_CTRL6_wake_pulse_width1_mask                                            (0xC0000000)
#define CBUS_CTRL6_wake_pulse_width1(data)                                           (0xC0000000&((data)<<30))
#define CBUS_CTRL6_wake_pulse_width1_src(data)                                       ((0xC0000000&(data))>>30)
#define CBUS_CTRL6_get_wake_pulse_width1(data)                                       ((0xC0000000&(data))>>30)
#define CBUS_CTRL6_dis_chk_high_shift                                                (27)
#define CBUS_CTRL6_dis_chk_high_mask                                                 (0x38000000)
#define CBUS_CTRL6_dis_chk_high(data)                                                (0x38000000&((data)<<27))
#define CBUS_CTRL6_dis_chk_high_src(data)                                            ((0x38000000&(data))>>27)
#define CBUS_CTRL6_get_dis_chk_high(data)                                            ((0x38000000&(data))>>27)
#define CBUS_CTRL6_wake_pulse_width2_shift                                           (22)
#define CBUS_CTRL6_wake_pulse_width2_mask                                            (0x03C00000)
#define CBUS_CTRL6_wake_pulse_width2(data)                                           (0x03C00000&((data)<<22))
#define CBUS_CTRL6_wake_pulse_width2_src(data)                                       ((0x03C00000&(data))>>22)
#define CBUS_CTRL6_get_wake_pulse_width2(data)                                       ((0x03C00000&(data))>>22)
#define CBUS_CTRL6_src_cbus_float_shift                                              (18)
#define CBUS_CTRL6_src_cbus_float_mask                                               (0x003C0000)
#define CBUS_CTRL6_src_cbus_float(data)                                              (0x003C0000&((data)<<18))
#define CBUS_CTRL6_src_cbus_float_src(data)                                          ((0x003C0000&(data))>>18)
#define CBUS_CTRL6_get_src_cbus_float(data)                                          ((0x003C0000&(data))>>18)
#define CBUS_CTRL6_src_pulse_width_shift                                             (11)
#define CBUS_CTRL6_src_pulse_width_mask                                              (0x0003F800)
#define CBUS_CTRL6_src_pulse_width(data)                                             (0x0003F800&((data)<<11))
#define CBUS_CTRL6_src_pulse_width_src(data)                                         ((0x0003F800&(data))>>11)
#define CBUS_CTRL6_get_src_pulse_width(data)                                         ((0x0003F800&(data))>>11)
#define CBUS_CTRL6_src_conn_shift                                                    (9)
#define CBUS_CTRL6_src_conn_mask                                                     (0x00000600)
#define CBUS_CTRL6_src_conn(data)                                                    (0x00000600&((data)<<9))
#define CBUS_CTRL6_src_conn_src(data)                                                ((0x00000600&(data))>>9)
#define CBUS_CTRL6_get_src_conn(data)                                                ((0x00000600&(data))>>9)
#define CBUS_CTRL6_rxsense_deglitch_shift                                            (0)
#define CBUS_CTRL6_rxsense_deglitch_mask                                             (0x000001FF)
#define CBUS_CTRL6_rxsense_deglitch(data)                                            (0x000001FF&((data)<<0))
#define CBUS_CTRL6_rxsense_deglitch_src(data)                                        ((0x000001FF&(data))>>0)
#define CBUS_CTRL6_get_rxsense_deglitch(data)                                        ((0x000001FF&(data))>>0)


#define CBUS_CTRL7                                                                   0x1C
#define CBUS_CTRL7_reg_addr                                                          "0x98037B1C"
#define CBUS_CTRL7_reg                                                               0x98037B1C
#define set_CBUS_CTRL7_reg(data)   (*((volatile unsigned int*) CBUS_CTRL7_reg)=data)
#define get_CBUS_CTRL7_reg   (*((volatile unsigned int*) CBUS_CTRL7_reg))
#define CBUS_CTRL7_inst_adr                                                          "0x0007"
#define CBUS_CTRL7_inst                                                              0x0007
#define CBUS_CTRL7_wake_to_discover_shift                                            (20)
#define CBUS_CTRL7_wake_to_discover_mask                                             (0x3FF00000)
#define CBUS_CTRL7_wake_to_discover(data)                                            (0x3FF00000&((data)<<20))
#define CBUS_CTRL7_wake_to_discover_src(data)                                        ((0x3FF00000&(data))>>20)
#define CBUS_CTRL7_get_wake_to_discover(data)                                        ((0x3FF00000&(data))>>20)
#define CBUS_CTRL7_src_vbus_cbus_stable_shift                                        (10)
#define CBUS_CTRL7_src_vbus_cbus_stable_mask                                         (0x000FFC00)
#define CBUS_CTRL7_src_vbus_cbus_stable(data)                                        (0x000FFC00&((data)<<10))
#define CBUS_CTRL7_src_vbus_cbus_stable_src(data)                                    ((0x000FFC00&(data))>>10)
#define CBUS_CTRL7_get_src_vbus_cbus_stable(data)                                    ((0x000FFC00&(data))>>10)
#define CBUS_CTRL7_vbus_out_to_stable_shift                                          (0)
#define CBUS_CTRL7_vbus_out_to_stable_mask                                           (0x000003FF)
#define CBUS_CTRL7_vbus_out_to_stable(data)                                          (0x000003FF&((data)<<0))
#define CBUS_CTRL7_vbus_out_to_stable_src(data)                                      ((0x000003FF&(data))>>0)
#define CBUS_CTRL7_get_vbus_out_to_stable(data)                                      ((0x000003FF&(data))>>0)


#define CBUS_CTRL8                                                                   0x20
#define CBUS_CTRL8_reg_addr                                                          "0x98037B20"
#define CBUS_CTRL8_reg                                                               0x98037B20
#define set_CBUS_CTRL8_reg(data)   (*((volatile unsigned int*) CBUS_CTRL8_reg)=data)
#define get_CBUS_CTRL8_reg   (*((volatile unsigned int*) CBUS_CTRL8_reg))
#define CBUS_CTRL8_inst_adr                                                          "0x0008"
#define CBUS_CTRL8_inst                                                              0x0008
#define CBUS_CTRL8_req_cont_shift                                                    (24)
#define CBUS_CTRL8_req_cont_mask                                                     (0xFF000000)
#define CBUS_CTRL8_req_cont(data)                                                    (0xFF000000&((data)<<24))
#define CBUS_CTRL8_req_cont_src(data)                                                ((0xFF000000&(data))>>24)
#define CBUS_CTRL8_get_req_cont(data)                                                ((0xFF000000&(data))>>24)
#define CBUS_CTRL8_src_arbitrate_shift                                               (21)
#define CBUS_CTRL8_src_arbitrate_mask                                                (0x00E00000)
#define CBUS_CTRL8_src_arbitrate(data)                                               (0x00E00000&((data)<<21))
#define CBUS_CTRL8_src_arbitrate_src(data)                                           ((0x00E00000&(data))>>21)
#define CBUS_CTRL8_get_src_arbitrate(data)                                           ((0x00E00000&(data))>>21)
#define CBUS_CTRL8_pulse_count_shift                                                 (16)
#define CBUS_CTRL8_pulse_count_mask                                                  (0x001F0000)
#define CBUS_CTRL8_pulse_count(data)                                                 (0x001F0000&((data)<<16))
#define CBUS_CTRL8_pulse_count_src(data)                                             ((0x001F0000&(data))>>16)
#define CBUS_CTRL8_get_pulse_count(data)                                             ((0x001F0000&(data))>>16)
#define CBUS_CTRL8_wait_sink_float_shift                                             (15)
#define CBUS_CTRL8_wait_sink_float_mask                                              (0x00008000)
#define CBUS_CTRL8_wait_sink_float(data)                                             (0x00008000&((data)<<15))
#define CBUS_CTRL8_wait_sink_float_src(data)                                         ((0x00008000&(data))>>15)
#define CBUS_CTRL8_get_wait_sink_float(data)                                         ((0x00008000&(data))>>15)
#define CBUS_CTRL8_sink_cbus_float_shift                                             (13)
#define CBUS_CTRL8_sink_cbus_float_mask                                              (0x00006000)
#define CBUS_CTRL8_sink_cbus_float(data)                                             (0x00006000&((data)<<13))
#define CBUS_CTRL8_sink_cbus_float_src(data)                                         ((0x00006000&(data))>>13)
#define CBUS_CTRL8_get_sink_cbus_float(data)                                         ((0x00006000&(data))>>13)
#define CBUS_CTRL8_rxsense_chk_shift                                                 (0)
#define CBUS_CTRL8_rxsense_chk_mask                                                  (0x000003FF)
#define CBUS_CTRL8_rxsense_chk(data)                                                 (0x000003FF&((data)<<0))
#define CBUS_CTRL8_rxsense_chk_src(data)                                             ((0x000003FF&(data))>>0)
#define CBUS_CTRL8_get_rxsense_chk(data)                                             ((0x000003FF&(data))>>0)


#define CBUS_STATUS                                                                  0x24
#define CBUS_STATUS_reg_addr                                                         "0x98037B24"
#define CBUS_STATUS_reg                                                              0x98037B24
#define set_CBUS_STATUS_reg(data)   (*((volatile unsigned int*) CBUS_STATUS_reg)=data)
#define get_CBUS_STATUS_reg   (*((volatile unsigned int*) CBUS_STATUS_reg))
#define CBUS_STATUS_inst_adr                                                         "0x0009"
#define CBUS_STATUS_inst                                                             0x0009
#define CBUS_STATUS_retry_flag_shift                                                 (18)
#define CBUS_STATUS_retry_flag_mask                                                  (0x00040000)
#define CBUS_STATUS_retry_flag(data)                                                 (0x00040000&((data)<<18))
#define CBUS_STATUS_retry_flag_src(data)                                             ((0x00040000&(data))>>18)
#define CBUS_STATUS_get_retry_flag(data)                                             ((0x00040000&(data))>>18)
#define CBUS_STATUS_link_err_shift                                                   (17)
#define CBUS_STATUS_link_err_mask                                                    (0x00020000)
#define CBUS_STATUS_link_err(data)                                                   (0x00020000&((data)<<17))
#define CBUS_STATUS_link_err_src(data)                                               ((0x00020000&(data))>>17)
#define CBUS_STATUS_get_link_err(data)                                               ((0x00020000&(data))>>17)
#define CBUS_STATUS_conflict_err_shift                                               (16)
#define CBUS_STATUS_conflict_err_mask                                                (0x00010000)
#define CBUS_STATUS_conflict_err(data)                                               (0x00010000&((data)<<16))
#define CBUS_STATUS_conflict_err_src(data)                                           ((0x00010000&(data))>>16)
#define CBUS_STATUS_get_conflict_err(data)                                           ((0x00010000&(data))>>16)
#define CBUS_STATUS_sync_bit_time_shift                                              (8)
#define CBUS_STATUS_sync_bit_time_mask                                               (0x0000FF00)
#define CBUS_STATUS_sync_bit_time(data)                                              (0x0000FF00&((data)<<8))
#define CBUS_STATUS_sync_bit_time_src(data)                                          ((0x0000FF00&(data))>>8)
#define CBUS_STATUS_get_sync_bit_time(data)                                          ((0x0000FF00&(data))>>8)
#define CBUS_STATUS_discovery_st_shift                                               (1)
#define CBUS_STATUS_discovery_st_mask                                                (0x0000000E)
#define CBUS_STATUS_discovery_st(data)                                               (0x0000000E&((data)<<1))
#define CBUS_STATUS_discovery_st_src(data)                                           ((0x0000000E&(data))>>1)
#define CBUS_STATUS_get_discovery_st(data)                                           ((0x0000000E&(data))>>1)
#define CBUS_STATUS_write_data_shift                                                 (0)
#define CBUS_STATUS_write_data_mask                                                  (0x00000001)
#define CBUS_STATUS_write_data(data)                                                 (0x00000001&((data)<<0))
#define CBUS_STATUS_write_data_src(data)                                             ((0x00000001&(data))>>0)
#define CBUS_STATUS_get_write_data(data)                                             ((0x00000001&(data))>>0)


#define FW0_CMD_INF                                                                  0x28
#define FW0_CMD_INF_reg_addr                                                         "0x98037B28"
#define FW0_CMD_INF_reg                                                              0x98037B28
#define set_FW0_CMD_INF_reg(data)   (*((volatile unsigned int*) FW0_CMD_INF_reg)=data)
#define get_FW0_CMD_INF_reg   (*((volatile unsigned int*) FW0_CMD_INF_reg))
#define FW0_CMD_INF_inst_adr                                                         "0x000A"
#define FW0_CMD_INF_inst                                                             0x000A
#define FW0_CMD_INF_fw0_req_shift                                                    (31)
#define FW0_CMD_INF_fw0_req_mask                                                     (0x80000000)
#define FW0_CMD_INF_fw0_req(data)                                                    (0x80000000&((data)<<31))
#define FW0_CMD_INF_fw0_req_src(data)                                                ((0x80000000&(data))>>31)
#define FW0_CMD_INF_get_fw0_req(data)                                                ((0x80000000&(data))>>31)
#define FW0_CMD_INF_fw0_tx_case_shift                                                (28)
#define FW0_CMD_INF_fw0_tx_case_mask                                                 (0x70000000)
#define FW0_CMD_INF_fw0_tx_case(data)                                                (0x70000000&((data)<<28))
#define FW0_CMD_INF_fw0_tx_case_src(data)                                            ((0x70000000&(data))>>28)
#define FW0_CMD_INF_get_fw0_tx_case(data)                                            ((0x70000000&(data))>>28)
#define FW0_CMD_INF_fw0_wait_case_shift                                              (26)
#define FW0_CMD_INF_fw0_wait_case_mask                                               (0x0C000000)
#define FW0_CMD_INF_fw0_wait_case(data)                                              (0x0C000000&((data)<<26))
#define FW0_CMD_INF_fw0_wait_case_src(data)                                          ((0x0C000000&(data))>>26)
#define FW0_CMD_INF_get_fw0_wait_case(data)                                          ((0x0C000000&(data))>>26)
#define FW0_CMD_INF_fw0_head_shift                                                   (24)
#define FW0_CMD_INF_fw0_head_mask                                                    (0x03000000)
#define FW0_CMD_INF_fw0_head(data)                                                   (0x03000000&((data)<<24))
#define FW0_CMD_INF_fw0_head_src(data)                                               ((0x03000000&(data))>>24)
#define FW0_CMD_INF_get_fw0_head(data)                                               ((0x03000000&(data))>>24)
#define FW0_CMD_INF_fw0_fifo_clr_shift                                               (23)
#define FW0_CMD_INF_fw0_fifo_clr_mask                                                (0x00800000)
#define FW0_CMD_INF_fw0_fifo_clr(data)                                               (0x00800000&((data)<<23))
#define FW0_CMD_INF_fw0_fifo_clr_src(data)                                           ((0x00800000&(data))>>23)
#define FW0_CMD_INF_get_fw0_fifo_clr(data)                                           ((0x00800000&(data))>>23)


#define FW0_CMD                                                                      0x2C
#define FW0_CMD_reg_addr                                                             "0x98037B2C"
#define FW0_CMD_reg                                                                  0x98037B2C
#define set_FW0_CMD_reg(data)   (*((volatile unsigned int*) FW0_CMD_reg)=data)
#define get_FW0_CMD_reg   (*((volatile unsigned int*) FW0_CMD_reg))
#define FW0_CMD_inst_adr                                                             "0x000B"
#define FW0_CMD_inst                                                                 0x000B
#define FW0_CMD_fw0_cmd2_shift                                                       (16)
#define FW0_CMD_fw0_cmd2_mask                                                        (0x00FF0000)
#define FW0_CMD_fw0_cmd2(data)                                                       (0x00FF0000&((data)<<16))
#define FW0_CMD_fw0_cmd2_src(data)                                                   ((0x00FF0000&(data))>>16)
#define FW0_CMD_get_fw0_cmd2(data)                                                   ((0x00FF0000&(data))>>16)
#define FW0_CMD_fw0_offset_shift                                                     (8)
#define FW0_CMD_fw0_offset_mask                                                      (0x0000FF00)
#define FW0_CMD_fw0_offset(data)                                                     (0x0000FF00&((data)<<8))
#define FW0_CMD_fw0_offset_src(data)                                                 ((0x0000FF00&(data))>>8)
#define FW0_CMD_get_fw0_offset(data)                                                 ((0x0000FF00&(data))>>8)
#define FW0_CMD_fw0_cmd1_shift                                                       (0)
#define FW0_CMD_fw0_cmd1_mask                                                        (0x000000FF)
#define FW0_CMD_fw0_cmd1(data)                                                       (0x000000FF&((data)<<0))
#define FW0_CMD_fw0_cmd1_src(data)                                                   ((0x000000FF&(data))>>0)
#define FW0_CMD_get_fw0_cmd1(data)                                                   ((0x000000FF&(data))>>0)


#define FW0_STATUS                                                                   0x30
#define FW0_STATUS_reg_addr                                                          "0x98037B30"
#define FW0_STATUS_reg                                                               0x98037B30
#define set_FW0_STATUS_reg(data)   (*((volatile unsigned int*) FW0_STATUS_reg)=data)
#define get_FW0_STATUS_reg   (*((volatile unsigned int*) FW0_STATUS_reg))
#define FW0_STATUS_inst_adr                                                          "0x000C"
#define FW0_STATUS_inst                                                              0x000C
#define FW0_STATUS_fw0_cmd_rcv_shift                                                 (24)
#define FW0_STATUS_fw0_cmd_rcv_mask                                                  (0xFF000000)
#define FW0_STATUS_fw0_cmd_rcv(data)                                                 (0xFF000000&((data)<<24))
#define FW0_STATUS_fw0_cmd_rcv_src(data)                                             ((0xFF000000&(data))>>24)
#define FW0_STATUS_get_fw0_cmd_rcv(data)                                             ((0xFF000000&(data))>>24)
#define FW0_STATUS_fw0_data_rcv_shift                                                (16)
#define FW0_STATUS_fw0_data_rcv_mask                                                 (0x00FF0000)
#define FW0_STATUS_fw0_data_rcv(data)                                                (0x00FF0000&((data)<<16))
#define FW0_STATUS_fw0_data_rcv_src(data)                                            ((0x00FF0000&(data))>>16)
#define FW0_STATUS_get_fw0_data_rcv(data)                                            ((0x00FF0000&(data))>>16)
#define FW0_STATUS_fw0_rcv_err_shift                                                 (15)
#define FW0_STATUS_fw0_rcv_err_mask                                                  (0x00008000)
#define FW0_STATUS_fw0_rcv_err(data)                                                 (0x00008000&((data)<<15))
#define FW0_STATUS_fw0_rcv_err_src(data)                                             ((0x00008000&(data))>>15)
#define FW0_STATUS_get_fw0_rcv_err(data)                                             ((0x00008000&(data))>>15)
#define FW0_STATUS_fw0_fifo_full_shift                                               (14)
#define FW0_STATUS_fw0_fifo_full_mask                                                (0x00004000)
#define FW0_STATUS_fw0_fifo_full(data)                                               (0x00004000&((data)<<14))
#define FW0_STATUS_fw0_fifo_full_src(data)                                           ((0x00004000&(data))>>14)
#define FW0_STATUS_get_fw0_fifo_full(data)                                           ((0x00004000&(data))>>14)
#define FW0_STATUS_fw0_fifo_empty_shift                                              (13)
#define FW0_STATUS_fw0_fifo_empty_mask                                               (0x00002000)
#define FW0_STATUS_fw0_fifo_empty(data)                                              (0x00002000&((data)<<13))
#define FW0_STATUS_fw0_fifo_empty_src(data)                                          ((0x00002000&(data))>>13)
#define FW0_STATUS_get_fw0_fifo_empty(data)                                          ((0x00002000&(data))>>13)
#define FW0_STATUS_fw0_fifo_len_shift                                                (8)
#define FW0_STATUS_fw0_fifo_len_mask                                                 (0x00001F00)
#define FW0_STATUS_fw0_fifo_len(data)                                                (0x00001F00&((data)<<8))
#define FW0_STATUS_fw0_fifo_len_src(data)                                            ((0x00001F00&(data))>>8)
#define FW0_STATUS_get_fw0_fifo_len(data)                                            ((0x00001F00&(data))>>8)
#define FW0_STATUS_fw0_rty_ovr_shift                                                 (7)
#define FW0_STATUS_fw0_rty_ovr_mask                                                  (0x00000080)
#define FW0_STATUS_fw0_rty_ovr(data)                                                 (0x00000080&((data)<<7))
#define FW0_STATUS_fw0_rty_ovr_src(data)                                             ((0x00000080&(data))>>7)
#define FW0_STATUS_get_fw0_rty_ovr(data)                                             ((0x00000080&(data))>>7)
#define FW0_STATUS_msc_hpd_shift                                                     (6)
#define FW0_STATUS_msc_hpd_mask                                                      (0x00000040)
#define FW0_STATUS_msc_hpd(data)                                                     (0x00000040&((data)<<6))
#define FW0_STATUS_msc_hpd_src(data)                                                 ((0x00000040&(data))>>6)
#define FW0_STATUS_get_msc_hpd(data)                                                 ((0x00000040&(data))>>6)
#define FW0_STATUS_write_data_shift                                                  (0)
#define FW0_STATUS_write_data_mask                                                   (0x00000001)
#define FW0_STATUS_write_data(data)                                                  (0x00000001&((data)<<0))
#define FW0_STATUS_write_data_src(data)                                              ((0x00000001&(data))>>0)
#define FW0_STATUS_get_write_data(data)                                              ((0x00000001&(data))>>0)


#define FW0_WDATA                                                                    0x34
#define FW0_WDATA_reg_addr                                                           "0x98037B34"
#define FW0_WDATA_reg                                                                0x98037B34
#define set_FW0_WDATA_reg(data)   (*((volatile unsigned int*) FW0_WDATA_reg)=data)
#define get_FW0_WDATA_reg   (*((volatile unsigned int*) FW0_WDATA_reg))
#define FW0_WDATA_inst_adr                                                           "0x000D"
#define FW0_WDATA_inst                                                               0x000D
#define FW0_WDATA_fw0_data_shift                                                     (0)
#define FW0_WDATA_fw0_data_mask                                                      (0x000000FF)
#define FW0_WDATA_fw0_data(data)                                                     (0x000000FF&((data)<<0))
#define FW0_WDATA_fw0_data_src(data)                                                 ((0x000000FF&(data))>>0)
#define FW0_WDATA_get_fw0_data(data)                                                 ((0x000000FF&(data))>>0)


#define FW0_RDATA                                                                    0x38
#define FW0_RDATA_reg_addr                                                           "0x98037B38"
#define FW0_RDATA_reg                                                                0x98037B38
#define set_FW0_RDATA_reg(data)   (*((volatile unsigned int*) FW0_RDATA_reg)=data)
#define get_FW0_RDATA_reg   (*((volatile unsigned int*) FW0_RDATA_reg))
#define FW0_RDATA_inst_adr                                                           "0x000E"
#define FW0_RDATA_inst                                                               0x000E
#define FW0_RDATA_fw0_rdata_shift                                                    (0)
#define FW0_RDATA_fw0_rdata_mask                                                     (0x000000FF)
#define FW0_RDATA_fw0_rdata(data)                                                    (0x000000FF&((data)<<0))
#define FW0_RDATA_fw0_rdata_src(data)                                                ((0x000000FF&(data))>>0)
#define FW0_RDATA_get_fw0_rdata(data)                                                ((0x000000FF&(data))>>0)


#define DEVCAP_OFFSET                                                                0x3C
#define DEVCAP_OFFSET_reg_addr                                                       "0x98037B3C"
#define DEVCAP_OFFSET_reg                                                            0x98037B3C
#define set_DEVCAP_OFFSET_reg(data)   (*((volatile unsigned int*) DEVCAP_OFFSET_reg)=data)
#define get_DEVCAP_OFFSET_reg   (*((volatile unsigned int*) DEVCAP_OFFSET_reg))
#define DEVCAP_OFFSET_inst_adr                                                       "0x000F"
#define DEVCAP_OFFSET_inst                                                           0x000F
#define DEVCAP_OFFSET_scr_offset_shift                                               (24)
#define DEVCAP_OFFSET_scr_offset_mask                                                (0xFF000000)
#define DEVCAP_OFFSET_scr_offset(data)                                               (0xFF000000&((data)<<24))
#define DEVCAP_OFFSET_scr_offset_src(data)                                           ((0xFF000000&(data))>>24)
#define DEVCAP_OFFSET_get_scr_offset(data)                                           ((0xFF000000&(data))>>24)
#define DEVCAP_OFFSET_sta_offset_shift                                               (16)
#define DEVCAP_OFFSET_sta_offset_mask                                                (0x00FF0000)
#define DEVCAP_OFFSET_sta_offset(data)                                               (0x00FF0000&((data)<<16))
#define DEVCAP_OFFSET_sta_offset_src(data)                                           ((0x00FF0000&(data))>>16)
#define DEVCAP_OFFSET_get_sta_offset(data)                                           ((0x00FF0000&(data))>>16)
#define DEVCAP_OFFSET_int_offset_shift                                               (8)
#define DEVCAP_OFFSET_int_offset_mask                                                (0x0000FF00)
#define DEVCAP_OFFSET_int_offset(data)                                               (0x0000FF00&((data)<<8))
#define DEVCAP_OFFSET_int_offset_src(data)                                           ((0x0000FF00&(data))>>8)
#define DEVCAP_OFFSET_get_int_offset(data)                                           ((0x0000FF00&(data))>>8)
#define DEVCAP_OFFSET_cap_offset_shift                                               (0)
#define DEVCAP_OFFSET_cap_offset_mask                                                (0x000000FF)
#define DEVCAP_OFFSET_cap_offset(data)                                               (0x000000FF&((data)<<0))
#define DEVCAP_OFFSET_cap_offset_src(data)                                           ((0x000000FF&(data))>>0)
#define DEVCAP_OFFSET_get_cap_offset(data)                                           ((0x000000FF&(data))>>0)


#define MSC_STATUS                                                                   0x44
#define MSC_STATUS_reg_addr                                                          "0x98037B44"
#define MSC_STATUS_reg                                                               0x98037B44
#define set_MSC_STATUS_reg(data)   (*((volatile unsigned int*) MSC_STATUS_reg)=data)
#define get_MSC_STATUS_reg   (*((volatile unsigned int*) MSC_STATUS_reg))
#define MSC_STATUS_inst_adr                                                          "0x0011"
#define MSC_STATUS_inst                                                              0x0011
#define MSC_STATUS_que_fsm_shift                                                     (28)
#define MSC_STATUS_que_fsm_mask                                                      (0xF0000000)
#define MSC_STATUS_que_fsm(data)                                                     (0xF0000000&((data)<<28))
#define MSC_STATUS_que_fsm_src(data)                                                 ((0xF0000000&(data))>>28)
#define MSC_STATUS_get_que_fsm(data)                                                 ((0xF0000000&(data))>>28)
#define MSC_STATUS_sch_fsm_shift                                                     (24)
#define MSC_STATUS_sch_fsm_mask                                                      (0x0F000000)
#define MSC_STATUS_sch_fsm(data)                                                     (0x0F000000&((data)<<24))
#define MSC_STATUS_sch_fsm_src(data)                                                 ((0x0F000000&(data))>>24)
#define MSC_STATUS_get_sch_fsm(data)                                                 ((0x0F000000&(data))>>24)
#define MSC_STATUS_burst_timeout_shift                                               (23)
#define MSC_STATUS_burst_timeout_mask                                                (0x00800000)
#define MSC_STATUS_burst_timeout(data)                                               (0x00800000&((data)<<23))
#define MSC_STATUS_burst_timeout_src(data)                                           ((0x00800000&(data))>>23)
#define MSC_STATUS_get_burst_timeout(data)                                           ((0x00800000&(data))>>23)
#define MSC_STATUS_write_data_shift                                                  (0)
#define MSC_STATUS_write_data_mask                                                   (0x00000001)
#define MSC_STATUS_write_data(data)                                                  (0x00000001&((data)<<0))
#define MSC_STATUS_write_data_src(data)                                              ((0x00000001&(data))>>0)
#define MSC_STATUS_get_write_data(data)                                              ((0x00000001&(data))>>0)


#define MSG_STATUS1                                                                  0x48
#define MSG_STATUS1_reg_addr                                                         "0x98037B48"
#define MSG_STATUS1_reg                                                              0x98037B48
#define set_MSG_STATUS1_reg(data)   (*((volatile unsigned int*) MSG_STATUS1_reg)=data)
#define get_MSG_STATUS1_reg   (*((volatile unsigned int*) MSG_STATUS1_reg))
#define MSG_STATUS1_inst_adr                                                         "0x0012"
#define MSG_STATUS1_inst                                                             0x0012
#define MSG_STATUS1_ucpk_rcv_shift                                                   (16)
#define MSG_STATUS1_ucpk_rcv_mask                                                    (0x00FF0000)
#define MSG_STATUS1_ucpk_rcv(data)                                                   (0x00FF0000&((data)<<16))
#define MSG_STATUS1_ucpk_rcv_src(data)                                               ((0x00FF0000&(data))>>16)
#define MSG_STATUS1_get_ucpk_rcv(data)                                               ((0x00FF0000&(data))>>16)
#define MSG_STATUS1_ucp_rcv_shift                                                    (8)
#define MSG_STATUS1_ucp_rcv_mask                                                     (0x0000FF00)
#define MSG_STATUS1_ucp_rcv(data)                                                    (0x0000FF00&((data)<<8))
#define MSG_STATUS1_ucp_rcv_src(data)                                                ((0x0000FF00&(data))>>8)
#define MSG_STATUS1_get_ucp_rcv(data)                                                ((0x0000FF00&(data))>>8)
#define MSG_STATUS1_ucpe_rcv_shift                                                   (0)
#define MSG_STATUS1_ucpe_rcv_mask                                                    (0x000000FF)
#define MSG_STATUS1_ucpe_rcv(data)                                                   (0x000000FF&((data)<<0))
#define MSG_STATUS1_ucpe_rcv_src(data)                                               ((0x000000FF&(data))>>0)
#define MSG_STATUS1_get_ucpe_rcv(data)                                               ((0x000000FF&(data))>>0)


#define MSG_STATUS2                                                                  0x50
#define MSG_STATUS2_reg_addr                                                         "0x98037B50"
#define MSG_STATUS2_reg                                                              0x98037B50
#define set_MSG_STATUS2_reg(data)   (*((volatile unsigned int*) MSG_STATUS2_reg)=data)
#define get_MSG_STATUS2_reg   (*((volatile unsigned int*) MSG_STATUS2_reg))
#define MSG_STATUS2_inst_adr                                                         "0x0014"
#define MSG_STATUS2_inst                                                             0x0014
#define MSG_STATUS2_msge_rcv_shift                                                   (24)
#define MSG_STATUS2_msge_rcv_mask                                                    (0xFF000000)
#define MSG_STATUS2_msge_rcv(data)                                                   (0xFF000000&((data)<<24))
#define MSG_STATUS2_msge_rcv_src(data)                                               ((0xFF000000&(data))>>24)
#define MSG_STATUS2_get_msge_rcv(data)                                               ((0xFF000000&(data))>>24)
#define MSG_STATUS2_rcpk_rcv_shift                                                   (16)
#define MSG_STATUS2_rcpk_rcv_mask                                                    (0x00FF0000)
#define MSG_STATUS2_rcpk_rcv(data)                                                   (0x00FF0000&((data)<<16))
#define MSG_STATUS2_rcpk_rcv_src(data)                                               ((0x00FF0000&(data))>>16)
#define MSG_STATUS2_get_rcpk_rcv(data)                                               ((0x00FF0000&(data))>>16)
#define MSG_STATUS2_rcp_rcv_shift                                                    (8)
#define MSG_STATUS2_rcp_rcv_mask                                                     (0x0000FF00)
#define MSG_STATUS2_rcp_rcv(data)                                                    (0x0000FF00&((data)<<8))
#define MSG_STATUS2_rcp_rcv_src(data)                                                ((0x0000FF00&(data))>>8)
#define MSG_STATUS2_get_rcp_rcv(data)                                                ((0x0000FF00&(data))>>8)
#define MSG_STATUS2_rcpe_rcv_shift                                                   (0)
#define MSG_STATUS2_rcpe_rcv_mask                                                    (0x000000FF)
#define MSG_STATUS2_rcpe_rcv(data)                                                   (0x000000FF&((data)<<0))
#define MSG_STATUS2_rcpe_rcv_src(data)                                               ((0x000000FF&(data))>>0)
#define MSG_STATUS2_get_rcpe_rcv(data)                                               ((0x000000FF&(data))>>0)


#define MSG_STATUS3                                                                  0x54
#define MSG_STATUS3_reg_addr                                                         "0x98037B54"
#define MSG_STATUS3_reg                                                              0x98037B54
#define set_MSG_STATUS3_reg(data)   (*((volatile unsigned int*) MSG_STATUS3_reg)=data)
#define get_MSG_STATUS3_reg   (*((volatile unsigned int*) MSG_STATUS3_reg))
#define MSG_STATUS3_inst_adr                                                         "0x0015"
#define MSG_STATUS3_inst                                                             0x0015
#define MSG_STATUS3_rap_rcv_shift                                                    (24)
#define MSG_STATUS3_rap_rcv_mask                                                     (0xFF000000)
#define MSG_STATUS3_rap_rcv(data)                                                    (0xFF000000&((data)<<24))
#define MSG_STATUS3_rap_rcv_src(data)                                                ((0xFF000000&(data))>>24)
#define MSG_STATUS3_get_rap_rcv(data)                                                ((0xFF000000&(data))>>24)
#define MSG_STATUS3_rapk_rcv_shift                                                   (16)
#define MSG_STATUS3_rapk_rcv_mask                                                    (0x00FF0000)
#define MSG_STATUS3_rapk_rcv(data)                                                   (0x00FF0000&((data)<<16))
#define MSG_STATUS3_rapk_rcv_src(data)                                               ((0x00FF0000&(data))>>16)
#define MSG_STATUS3_get_rapk_rcv(data)                                               ((0x00FF0000&(data))>>16)
#define MSG_STATUS3_msg_dat_shift                                                    (8)
#define MSG_STATUS3_msg_dat_mask                                                     (0x0000FF00)
#define MSG_STATUS3_msg_dat(data)                                                    (0x0000FF00&((data)<<8))
#define MSG_STATUS3_msg_dat_src(data)                                                ((0x0000FF00&(data))>>8)
#define MSG_STATUS3_get_msg_dat(data)                                                ((0x0000FF00&(data))>>8)
#define MSG_STATUS3_msg_cmd_shift                                                    (0)
#define MSG_STATUS3_msg_cmd_mask                                                     (0x000000FF)
#define MSG_STATUS3_msg_cmd(data)                                                    (0x000000FF&((data)<<0))
#define MSG_STATUS3_msg_cmd_src(data)                                                ((0x000000FF&(data))>>0)
#define MSG_STATUS3_get_msg_cmd(data)                                                ((0x000000FF&(data))>>0)


#define ADOPTERID_CTRL                                                               0x60
#define ADOPTERID_CTRL_reg_addr                                                      "0x98037B60"
#define ADOPTERID_CTRL_reg                                                           0x98037B60
#define set_ADOPTERID_CTRL_reg(data)   (*((volatile unsigned int*) ADOPTERID_CTRL_reg)=data)
#define get_ADOPTERID_CTRL_reg   (*((volatile unsigned int*) ADOPTERID_CTRL_reg))
#define ADOPTERID_CTRL_inst_adr                                                      "0x0018"
#define ADOPTERID_CTRL_inst                                                          0x0018
#define ADOPTERID_CTRL_wb_id_chk_shift                                               (31)
#define ADOPTERID_CTRL_wb_id_chk_mask                                                (0x80000000)
#define ADOPTERID_CTRL_wb_id_chk(data)                                               (0x80000000&((data)<<31))
#define ADOPTERID_CTRL_wb_id_chk_src(data)                                           ((0x80000000&(data))>>31)
#define ADOPTERID_CTRL_get_wb_id_chk(data)                                           ((0x80000000&(data))>>31)
#define ADOPTERID_CTRL_rcp_reply_nack_shift                                          (30)
#define ADOPTERID_CTRL_rcp_reply_nack_mask                                           (0x40000000)
#define ADOPTERID_CTRL_rcp_reply_nack(data)                                          (0x40000000&((data)<<30))
#define ADOPTERID_CTRL_rcp_reply_nack_src(data)                                      ((0x40000000&(data))>>30)
#define ADOPTERID_CTRL_get_rcp_reply_nack(data)                                      ((0x40000000&(data))>>30)
#define ADOPTERID_CTRL_rcp_reply_abort_shift                                         (29)
#define ADOPTERID_CTRL_rcp_reply_abort_mask                                          (0x20000000)
#define ADOPTERID_CTRL_rcp_reply_abort(data)                                         (0x20000000&((data)<<29))
#define ADOPTERID_CTRL_rcp_reply_abort_src(data)                                     ((0x20000000&(data))>>29)
#define ADOPTERID_CTRL_get_rcp_reply_abort(data)                                     ((0x20000000&(data))>>29)
#define ADOPTERID_CTRL_fwdef_cmd_rev_shift                                           (16)
#define ADOPTERID_CTRL_fwdef_cmd_rev_mask                                            (0x00FF0000)
#define ADOPTERID_CTRL_fwdef_cmd_rev(data)                                           (0x00FF0000&((data)<<16))
#define ADOPTERID_CTRL_fwdef_cmd_rev_src(data)                                       ((0x00FF0000&(data))>>16)
#define ADOPTERID_CTRL_get_fwdef_cmd_rev(data)                                       ((0x00FF0000&(data))>>16)


#define RCV_ADOPTER_ID                                                               0x64
#define RCV_ADOPTER_ID_reg_addr                                                      "0x98037B64"
#define RCV_ADOPTER_ID_reg                                                           0x98037B64
#define set_RCV_ADOPTER_ID_reg(data)   (*((volatile unsigned int*) RCV_ADOPTER_ID_reg)=data)
#define get_RCV_ADOPTER_ID_reg   (*((volatile unsigned int*) RCV_ADOPTER_ID_reg))
#define RCV_ADOPTER_ID_inst_adr                                                      "0x0019"
#define RCV_ADOPTER_ID_inst                                                          0x0019
#define RCV_ADOPTER_ID_adop_idl_rcv_shift                                            (8)
#define RCV_ADOPTER_ID_adop_idl_rcv_mask                                             (0x0000FF00)
#define RCV_ADOPTER_ID_adop_idl_rcv(data)                                            (0x0000FF00&((data)<<8))
#define RCV_ADOPTER_ID_adop_idl_rcv_src(data)                                        ((0x0000FF00&(data))>>8)
#define RCV_ADOPTER_ID_get_adop_idl_rcv(data)                                        ((0x0000FF00&(data))>>8)
#define RCV_ADOPTER_ID_adop_idh_rcv_shift                                            (0)
#define RCV_ADOPTER_ID_adop_idh_rcv_mask                                             (0x000000FF)
#define RCV_ADOPTER_ID_adop_idh_rcv(data)                                            (0x000000FF&((data)<<0))
#define RCV_ADOPTER_ID_adop_idh_rcv_src(data)                                        ((0x000000FF&(data))>>0)
#define RCV_ADOPTER_ID_get_adop_idh_rcv(data)                                        ((0x000000FF&(data))>>0)


#define MSC_CTRL                                                                     0x68
#define MSC_CTRL_reg_addr                                                            "0x98037B68"
#define MSC_CTRL_reg                                                                 0x98037B68
#define set_MSC_CTRL_reg(data)   (*((volatile unsigned int*) MSC_CTRL_reg)=data)
#define get_MSC_CTRL_reg   (*((volatile unsigned int*) MSC_CTRL_reg))
#define MSC_CTRL_inst_adr                                                            "0x001A"
#define MSC_CTRL_inst                                                                0x001A
#define MSC_CTRL_mcumsc_en_shift                                                     (31)
#define MSC_CTRL_mcumsc_en_mask                                                      (0x80000000)
#define MSC_CTRL_mcumsc_en(data)                                                     (0x80000000&((data)<<31))
#define MSC_CTRL_mcumsc_en_src(data)                                                 ((0x80000000&(data))>>31)
#define MSC_CTRL_get_mcumsc_en(data)                                                 ((0x80000000&(data))>>31)
#define MSC_CTRL_msc_wait_arb_shift                                                  (29)
#define MSC_CTRL_msc_wait_arb_mask                                                   (0x20000000)
#define MSC_CTRL_msc_wait_arb(data)                                                  (0x20000000&((data)<<29))
#define MSC_CTRL_msc_wait_arb_src(data)                                              ((0x20000000&(data))>>29)
#define MSC_CTRL_get_msc_wait_arb(data)                                              ((0x20000000&(data))>>29)
#define MSC_CTRL_rx_fifo_clr_shift                                                   (28)
#define MSC_CTRL_rx_fifo_clr_mask                                                    (0x10000000)
#define MSC_CTRL_rx_fifo_clr(data)                                                   (0x10000000&((data)<<28))
#define MSC_CTRL_rx_fifo_clr_src(data)                                               ((0x10000000&(data))>>28)
#define MSC_CTRL_get_rx_fifo_clr(data)                                               ((0x10000000&(data))>>28)
#define MSC_CTRL_que_fsm_clr_shift                                                   (25)
#define MSC_CTRL_que_fsm_clr_mask                                                    (0x02000000)
#define MSC_CTRL_que_fsm_clr(data)                                                   (0x02000000&((data)<<25))
#define MSC_CTRL_que_fsm_clr_src(data)                                               ((0x02000000&(data))>>25)
#define MSC_CTRL_get_que_fsm_clr(data)                                               ((0x02000000&(data))>>25)
#define MSC_CTRL_sch_fsm_clr_shift                                                   (24)
#define MSC_CTRL_sch_fsm_clr_mask                                                    (0x01000000)
#define MSC_CTRL_sch_fsm_clr(data)                                                   (0x01000000&((data)<<24))
#define MSC_CTRL_sch_fsm_clr_src(data)                                               ((0x01000000&(data))>>24)
#define MSC_CTRL_get_sch_fsm_clr(data)                                               ((0x01000000&(data))>>24)


#define MSC_BURST_DATA                                                               0x6C
#define MSC_BURST_DATA_reg_addr                                                      "0x98037B6C"
#define MSC_BURST_DATA_reg                                                           0x98037B6C
#define set_MSC_BURST_DATA_reg(data)   (*((volatile unsigned int*) MSC_BURST_DATA_reg)=data)
#define get_MSC_BURST_DATA_reg   (*((volatile unsigned int*) MSC_BURST_DATA_reg))
#define MSC_BURST_DATA_inst_adr                                                      "0x001B"
#define MSC_BURST_DATA_inst                                                          0x001B
#define MSC_BURST_DATA_msc_err_code_shift                                            (0)
#define MSC_BURST_DATA_msc_err_code_mask                                             (0x000000FF)
#define MSC_BURST_DATA_msc_err_code(data)                                            (0x000000FF&((data)<<0))
#define MSC_BURST_DATA_msc_err_code_src(data)                                        ((0x000000FF&(data))>>0)
#define MSC_BURST_DATA_get_msc_err_code(data)                                        ((0x000000FF&(data))>>0)


#define MSC_RCV_CMD                                                                  0x70
#define MSC_RCV_CMD_reg_addr                                                         "0x98037B70"
#define MSC_RCV_CMD_reg                                                              0x98037B70
#define set_MSC_RCV_CMD_reg(data)   (*((volatile unsigned int*) MSC_RCV_CMD_reg)=data)
#define get_MSC_RCV_CMD_reg   (*((volatile unsigned int*) MSC_RCV_CMD_reg))
#define MSC_RCV_CMD_inst_adr                                                         "0x001C"
#define MSC_RCV_CMD_inst                                                             0x001C
#define MSC_RCV_CMD_rx_fifo_full_shift                                               (31)
#define MSC_RCV_CMD_rx_fifo_full_mask                                                (0x80000000)
#define MSC_RCV_CMD_rx_fifo_full(data)                                               (0x80000000&((data)<<31))
#define MSC_RCV_CMD_rx_fifo_full_src(data)                                           ((0x80000000&(data))>>31)
#define MSC_RCV_CMD_get_rx_fifo_full(data)                                           ((0x80000000&(data))>>31)
#define MSC_RCV_CMD_rx_fifo_empty_shift                                              (30)
#define MSC_RCV_CMD_rx_fifo_empty_mask                                               (0x40000000)
#define MSC_RCV_CMD_rx_fifo_empty(data)                                              (0x40000000&((data)<<30))
#define MSC_RCV_CMD_rx_fifo_empty_src(data)                                          ((0x40000000&(data))>>30)
#define MSC_RCV_CMD_get_rx_fifo_empty(data)                                          ((0x40000000&(data))>>30)
#define MSC_RCV_CMD_na_rx_len_shift                                                  (24)
#define MSC_RCV_CMD_na_rx_len_mask                                                   (0x1F000000)
#define MSC_RCV_CMD_na_rx_len(data)                                                  (0x1F000000&((data)<<24))
#define MSC_RCV_CMD_na_rx_len_src(data)                                              ((0x1F000000&(data))>>24)
#define MSC_RCV_CMD_get_na_rx_len(data)                                              ((0x1F000000&(data))>>24)
#define MSC_RCV_CMD_na_msc_offset_shift                                              (8)
#define MSC_RCV_CMD_na_msc_offset_mask                                               (0x0000FF00)
#define MSC_RCV_CMD_na_msc_offset(data)                                              (0x0000FF00&((data)<<8))
#define MSC_RCV_CMD_na_msc_offset_src(data)                                          ((0x0000FF00&(data))>>8)
#define MSC_RCV_CMD_get_na_msc_offset(data)                                          ((0x0000FF00&(data))>>8)
#define MSC_RCV_CMD_na_msc_cmd_shift                                                 (0)
#define MSC_RCV_CMD_na_msc_cmd_mask                                                  (0x000000FF)
#define MSC_RCV_CMD_na_msc_cmd(data)                                                 (0x000000FF&((data)<<0))
#define MSC_RCV_CMD_na_msc_cmd_src(data)                                             ((0x000000FF&(data))>>0)
#define MSC_RCV_CMD_get_na_msc_cmd(data)                                             ((0x000000FF&(data))>>0)


#define MSC_RCV_DATA                                                                 0x74
#define MSC_RCV_DATA_reg_addr                                                        "0x98037B74"
#define MSC_RCV_DATA_reg                                                             0x98037B74
#define set_MSC_RCV_DATA_reg(data)   (*((volatile unsigned int*) MSC_RCV_DATA_reg)=data)
#define get_MSC_RCV_DATA_reg   (*((volatile unsigned int*) MSC_RCV_DATA_reg))
#define MSC_RCV_DATA_inst_adr                                                        "0x001D"
#define MSC_RCV_DATA_inst                                                            0x001D
#define MSC_RCV_DATA_rx_fifo_data_shift                                              (0)
#define MSC_RCV_DATA_rx_fifo_data_mask                                               (0x000000FF)
#define MSC_RCV_DATA_rx_fifo_data(data)                                              (0x000000FF&((data)<<0))
#define MSC_RCV_DATA_rx_fifo_data_src(data)                                          ((0x000000FF&(data))>>0)
#define MSC_RCV_DATA_get_rx_fifo_data(data)                                          ((0x000000FF&(data))>>0)


#define MSC_WRITE_ERR_CODE                                                           0xA4
#define MSC_WRITE_ERR_CODE_reg_addr                                                  "0x98037BA4"
#define MSC_WRITE_ERR_CODE_reg                                                       0x98037BA4
#define set_MSC_WRITE_ERR_CODE_reg(data)   (*((volatile unsigned int*) MSC_WRITE_ERR_CODE_reg)=data)
#define get_MSC_WRITE_ERR_CODE_reg   (*((volatile unsigned int*) MSC_WRITE_ERR_CODE_reg))
#define MSC_WRITE_ERR_CODE_inst_adr                                                  "0x0029"
#define MSC_WRITE_ERR_CODE_inst                                                      0x0029
#define MSC_WRITE_ERR_CODE_msc_err_force_shift                                       (31)
#define MSC_WRITE_ERR_CODE_msc_err_force_mask                                        (0x80000000)
#define MSC_WRITE_ERR_CODE_msc_err_force(data)                                       (0x80000000&((data)<<31))
#define MSC_WRITE_ERR_CODE_msc_err_force_src(data)                                   ((0x80000000&(data))>>31)
#define MSC_WRITE_ERR_CODE_get_msc_err_force(data)                                   ((0x80000000&(data))>>31)
#define MSC_WRITE_ERR_CODE_msc_err_fw_shift                                          (0)
#define MSC_WRITE_ERR_CODE_msc_err_fw_mask                                           (0x000000FF)
#define MSC_WRITE_ERR_CODE_msc_err_fw(data)                                          (0x000000FF&((data)<<0))
#define MSC_WRITE_ERR_CODE_msc_err_fw_src(data)                                      ((0x000000FF&(data))>>0)
#define MSC_WRITE_ERR_CODE_get_msc_err_fw(data)                                      ((0x000000FF&(data))>>0)


#define DDC_CMD_INF                                                                  0x7C
#define DDC_CMD_INF_reg_addr                                                         "0x98037B7C"
#define DDC_CMD_INF_reg                                                              0x98037B7C
#define set_DDC_CMD_INF_reg(data)   (*((volatile unsigned int*) DDC_CMD_INF_reg)=data)
#define get_DDC_CMD_INF_reg   (*((volatile unsigned int*) DDC_CMD_INF_reg))
#define DDC_CMD_INF_inst_adr                                                         "0x001F"
#define DDC_CMD_INF_inst                                                             0x001F
#define DDC_CMD_INF_ddc_rdy_shift                                                    (31)
#define DDC_CMD_INF_ddc_rdy_mask                                                     (0x80000000)
#define DDC_CMD_INF_ddc_rdy(data)                                                    (0x80000000&((data)<<31))
#define DDC_CMD_INF_ddc_rdy_src(data)                                                ((0x80000000&(data))>>31)
#define DDC_CMD_INF_get_ddc_rdy(data)                                                ((0x80000000&(data))>>31)
#define DDC_CMD_INF_ddc_cmd_type_shift                                               (28)
#define DDC_CMD_INF_ddc_cmd_type_mask                                                (0x70000000)
#define DDC_CMD_INF_ddc_cmd_type(data)                                               (0x70000000&((data)<<28))
#define DDC_CMD_INF_ddc_cmd_type_src(data)                                           ((0x70000000&(data))>>28)
#define DDC_CMD_INF_get_ddc_cmd_type(data)                                           ((0x70000000&(data))>>28)
#define DDC_CMD_INF_ddc_num_shift                                                    (24)
#define DDC_CMD_INF_ddc_num_mask                                                     (0x0F000000)
#define DDC_CMD_INF_ddc_num(data)                                                    (0x0F000000&((data)<<24))
#define DDC_CMD_INF_ddc_num_src(data)                                                ((0x0F000000&(data))>>24)
#define DDC_CMD_INF_get_ddc_num(data)                                                ((0x0F000000&(data))>>24)
#define DDC_CMD_INF_ddc_nack_limit_shift                                             (16)
#define DDC_CMD_INF_ddc_nack_limit_mask                                              (0x00FF0000)
#define DDC_CMD_INF_ddc_nack_limit(data)                                             (0x00FF0000&((data)<<16))
#define DDC_CMD_INF_ddc_nack_limit_src(data)                                         ((0x00FF0000&(data))>>16)
#define DDC_CMD_INF_get_ddc_nack_limit(data)                                         ((0x00FF0000&(data))>>16)
#define DDC_CMD_INF_ddc_err_code_clr_shift                                           (10)
#define DDC_CMD_INF_ddc_err_code_clr_mask                                            (0x00000400)
#define DDC_CMD_INF_ddc_err_code_clr(data)                                           (0x00000400&((data)<<10))
#define DDC_CMD_INF_ddc_err_code_clr_src(data)                                       ((0x00000400&(data))>>10)
#define DDC_CMD_INF_get_ddc_err_code_clr(data)                                       ((0x00000400&(data))>>10)
#define DDC_CMD_INF_ddc_prior_dis_shift                                              (9)
#define DDC_CMD_INF_ddc_prior_dis_mask                                               (0x00000200)
#define DDC_CMD_INF_ddc_prior_dis(data)                                              (0x00000200&((data)<<9))
#define DDC_CMD_INF_ddc_prior_dis_src(data)                                          ((0x00000200&(data))>>9)
#define DDC_CMD_INF_get_ddc_prior_dis(data)                                          ((0x00000200&(data))>>9)
#define DDC_CMD_INF_ddc_fsm_clr_shift                                                (8)
#define DDC_CMD_INF_ddc_fsm_clr_mask                                                 (0x00000100)
#define DDC_CMD_INF_ddc_fsm_clr(data)                                                (0x00000100&((data)<<8))
#define DDC_CMD_INF_ddc_fsm_clr_src(data)                                            ((0x00000100&(data))>>8)
#define DDC_CMD_INF_get_ddc_fsm_clr(data)                                            ((0x00000100&(data))>>8)
#define DDC_CMD_INF_ddc_nack_retry_shift                                             (2)
#define DDC_CMD_INF_ddc_nack_retry_mask                                              (0x00000004)
#define DDC_CMD_INF_ddc_nack_retry(data)                                             (0x00000004&((data)<<2))
#define DDC_CMD_INF_ddc_nack_retry_src(data)                                         ((0x00000004&(data))>>2)
#define DDC_CMD_INF_get_ddc_nack_retry(data)                                         ((0x00000004&(data))>>2)
#define DDC_CMD_INF_ddc_wait_case_shift                                              (1)
#define DDC_CMD_INF_ddc_wait_case_mask                                               (0x00000002)
#define DDC_CMD_INF_ddc_wait_case(data)                                              (0x00000002&((data)<<1))
#define DDC_CMD_INF_ddc_wait_case_src(data)                                          ((0x00000002&(data))>>1)
#define DDC_CMD_INF_get_ddc_wait_case(data)                                          ((0x00000002&(data))>>1)
#define DDC_CMD_INF_ddc_fw_en_shift                                                  (0)
#define DDC_CMD_INF_ddc_fw_en_mask                                                   (0x00000001)
#define DDC_CMD_INF_ddc_fw_en(data)                                                  (0x00000001&((data)<<0))
#define DDC_CMD_INF_ddc_fw_en_src(data)                                              ((0x00000001&(data))>>0)
#define DDC_CMD_INF_get_ddc_fw_en(data)                                              ((0x00000001&(data))>>0)


#define DDC_CMD_DATA                                                                 0x80
#define DDC_CMD_DATA_reg_addr                                                        "0x98037B80"
#define DDC_CMD_DATA_reg                                                             0x98037B80
#define set_DDC_CMD_DATA_reg(data)   (*((volatile unsigned int*) DDC_CMD_DATA_reg)=data)
#define get_DDC_CMD_DATA_reg   (*((volatile unsigned int*) DDC_CMD_DATA_reg))
#define DDC_CMD_DATA_inst_adr                                                        "0x0020"
#define DDC_CMD_DATA_inst                                                            0x0020
#define DDC_CMD_DATA_ddc_segval_shift                                                (16)
#define DDC_CMD_DATA_ddc_segval_mask                                                 (0x00FF0000)
#define DDC_CMD_DATA_ddc_segval(data)                                                (0x00FF0000&((data)<<16))
#define DDC_CMD_DATA_ddc_segval_src(data)                                            ((0x00FF0000&(data))>>16)
#define DDC_CMD_DATA_get_ddc_segval(data)                                            ((0x00FF0000&(data))>>16)
#define DDC_CMD_DATA_ddc_offset_shift                                                (8)
#define DDC_CMD_DATA_ddc_offset_mask                                                 (0x0000FF00)
#define DDC_CMD_DATA_ddc_offset(data)                                                (0x0000FF00&((data)<<8))
#define DDC_CMD_DATA_ddc_offset_src(data)                                            ((0x0000FF00&(data))>>8)
#define DDC_CMD_DATA_get_ddc_offset(data)                                            ((0x0000FF00&(data))>>8)
#define DDC_CMD_DATA_ddc_devaddr_shift                                               (0)
#define DDC_CMD_DATA_ddc_devaddr_mask                                                (0x000000FF)
#define DDC_CMD_DATA_ddc_devaddr(data)                                               (0x000000FF&((data)<<0))
#define DDC_CMD_DATA_ddc_devaddr_src(data)                                           ((0x000000FF&(data))>>0)
#define DDC_CMD_DATA_get_ddc_devaddr(data)                                           ((0x000000FF&(data))>>0)


#define DDC_WD                                                                       0x84
#define DDC_WD_reg_addr                                                              "0x98037B84"
#define DDC_WD_reg                                                                   0x98037B84
#define set_DDC_WD_reg(data)   (*((volatile unsigned int*) DDC_WD_reg)=data)
#define get_DDC_WD_reg   (*((volatile unsigned int*) DDC_WD_reg))
#define DDC_WD_inst_adr                                                              "0x0021"
#define DDC_WD_inst                                                                  0x0021
#define DDC_WD_ddc_wdata_shift                                                       (0)
#define DDC_WD_ddc_wdata_mask                                                        (0x000000FF)
#define DDC_WD_ddc_wdata(data)                                                       (0x000000FF&((data)<<0))
#define DDC_WD_ddc_wdata_src(data)                                                   ((0x000000FF&(data))>>0)
#define DDC_WD_get_ddc_wdata(data)                                                   ((0x000000FF&(data))>>0)


#define DDC_RD                                                                       0x88
#define DDC_RD_reg_addr                                                              "0x98037B88"
#define DDC_RD_reg                                                                   0x98037B88
#define set_DDC_RD_reg(data)   (*((volatile unsigned int*) DDC_RD_reg)=data)
#define get_DDC_RD_reg   (*((volatile unsigned int*) DDC_RD_reg))
#define DDC_RD_inst_adr                                                              "0x0022"
#define DDC_RD_inst                                                                  0x0022
#define DDC_RD_ddc_fsm_shift                                                         (16)
#define DDC_RD_ddc_fsm_mask                                                          (0x001F0000)
#define DDC_RD_ddc_fsm(data)                                                         (0x001F0000&((data)<<16))
#define DDC_RD_ddc_fsm_src(data)                                                     ((0x001F0000&(data))>>16)
#define DDC_RD_get_ddc_fsm(data)                                                     ((0x001F0000&(data))>>16)
#define DDC_RD_ddc_rdata_shift                                                       (0)
#define DDC_RD_ddc_rdata_mask                                                        (0x000000FF)
#define DDC_RD_ddc_rdata(data)                                                       (0x000000FF&((data)<<0))
#define DDC_RD_ddc_rdata_src(data)                                                   ((0x000000FF&(data))>>0)
#define DDC_RD_get_ddc_rdata(data)                                                   ((0x000000FF&(data))>>0)


#define DDC_STATUS                                                                   0x8C
#define DDC_STATUS_reg_addr                                                          "0x98037B8C"
#define DDC_STATUS_reg                                                               0x98037B8C
#define set_DDC_STATUS_reg(data)   (*((volatile unsigned int*) DDC_STATUS_reg)=data)
#define get_DDC_STATUS_reg   (*((volatile unsigned int*) DDC_STATUS_reg))
#define DDC_STATUS_inst_adr                                                          "0x0023"
#define DDC_STATUS_inst                                                              0x0023
#define DDC_STATUS_ddc_fifo_full_shift                                               (25)
#define DDC_STATUS_ddc_fifo_full_mask                                                (0x02000000)
#define DDC_STATUS_ddc_fifo_full(data)                                               (0x02000000&((data)<<25))
#define DDC_STATUS_ddc_fifo_full_src(data)                                           ((0x02000000&(data))>>25)
#define DDC_STATUS_get_ddc_fifo_full(data)                                           ((0x02000000&(data))>>25)
#define DDC_STATUS_ddc_fifo_empty_shift                                              (24)
#define DDC_STATUS_ddc_fifo_empty_mask                                               (0x01000000)
#define DDC_STATUS_ddc_fifo_empty(data)                                              (0x01000000&((data)<<24))
#define DDC_STATUS_ddc_fifo_empty_src(data)                                          ((0x01000000&(data))>>24)
#define DDC_STATUS_get_ddc_fifo_empty(data)                                          ((0x01000000&(data))>>24)
#define DDC_STATUS_ddc_err_code_shift                                                (16)
#define DDC_STATUS_ddc_err_code_mask                                                 (0x00FF0000)
#define DDC_STATUS_ddc_err_code(data)                                                (0x00FF0000&((data)<<16))
#define DDC_STATUS_ddc_err_code_src(data)                                            ((0x00FF0000&(data))>>16)
#define DDC_STATUS_get_ddc_err_code(data)                                            ((0x00FF0000&(data))>>16)
#define DDC_STATUS_ddc_wp_shift                                                      (4)
#define DDC_STATUS_ddc_wp_mask                                                       (0x000000F0)
#define DDC_STATUS_ddc_wp(data)                                                      (0x000000F0&((data)<<4))
#define DDC_STATUS_ddc_wp_src(data)                                                  ((0x000000F0&(data))>>4)
#define DDC_STATUS_get_ddc_wp(data)                                                  ((0x000000F0&(data))>>4)
#define DDC_STATUS_ddc_rp_shift                                                      (0)
#define DDC_STATUS_ddc_rp_mask                                                       (0x0000000F)
#define DDC_STATUS_ddc_rp(data)                                                      (0x0000000F&((data)<<0))
#define DDC_STATUS_ddc_rp_src(data)                                                  ((0x0000000F&(data))>>0)
#define DDC_STATUS_get_ddc_rp(data)                                                  ((0x0000000F&(data))>>0)


#define DDC_WRITE_ERR_CODE                                                           0xA0
#define DDC_WRITE_ERR_CODE_reg_addr                                                  "0x98037BA0"
#define DDC_WRITE_ERR_CODE_reg                                                       0x98037BA0
#define set_DDC_WRITE_ERR_CODE_reg(data)   (*((volatile unsigned int*) DDC_WRITE_ERR_CODE_reg)=data)
#define get_DDC_WRITE_ERR_CODE_reg   (*((volatile unsigned int*) DDC_WRITE_ERR_CODE_reg))
#define DDC_WRITE_ERR_CODE_inst_adr                                                  "0x0028"
#define DDC_WRITE_ERR_CODE_inst                                                      0x0028
#define DDC_WRITE_ERR_CODE_ddc_err_force_shift                                       (31)
#define DDC_WRITE_ERR_CODE_ddc_err_force_mask                                        (0x80000000)
#define DDC_WRITE_ERR_CODE_ddc_err_force(data)                                       (0x80000000&((data)<<31))
#define DDC_WRITE_ERR_CODE_ddc_err_force_src(data)                                   ((0x80000000&(data))>>31)
#define DDC_WRITE_ERR_CODE_get_ddc_err_force(data)                                   ((0x80000000&(data))>>31)
#define DDC_WRITE_ERR_CODE_ddc_err_fw_shift                                          (0)
#define DDC_WRITE_ERR_CODE_ddc_err_fw_mask                                           (0x000000FF)
#define DDC_WRITE_ERR_CODE_ddc_err_fw(data)                                          (0x000000FF&((data)<<0))
#define DDC_WRITE_ERR_CODE_ddc_err_fw_src(data)                                      ((0x000000FF&(data))>>0)
#define DDC_WRITE_ERR_CODE_get_ddc_err_fw(data)                                      ((0x000000FF&(data))>>0)


#define MSC_IRQ                                                                      0x58
#define MSC_IRQ_reg_addr                                                             "0x98037B58"
#define MSC_IRQ_reg                                                                  0x98037B58
#define set_MSC_IRQ_reg(data)   (*((volatile unsigned int*) MSC_IRQ_reg)=data)
#define get_MSC_IRQ_reg   (*((volatile unsigned int*) MSC_IRQ_reg))
#define MSC_IRQ_inst_adr                                                             "0x0016"
#define MSC_IRQ_inst                                                                 0x0016
#define MSC_IRQ_wr_stat_irq_shift                                                    (31)
#define MSC_IRQ_wr_stat_irq_mask                                                     (0x80000000)
#define MSC_IRQ_wr_stat_irq(data)                                                    (0x80000000&((data)<<31))
#define MSC_IRQ_wr_stat_irq_src(data)                                                ((0x80000000&(data))>>31)
#define MSC_IRQ_get_wr_stat_irq(data)                                                ((0x80000000&(data))>>31)
#define MSC_IRQ_rd_devcap_irq_shift                                                  (30)
#define MSC_IRQ_rd_devcap_irq_mask                                                   (0x40000000)
#define MSC_IRQ_rd_devcap_irq(data)                                                  (0x40000000&((data)<<30))
#define MSC_IRQ_rd_devcap_irq_src(data)                                              ((0x40000000&(data))>>30)
#define MSC_IRQ_get_rd_devcap_irq(data)                                              ((0x40000000&(data))>>30)
#define MSC_IRQ_get_stat_irq_shift                                                   (29)
#define MSC_IRQ_get_stat_irq_mask                                                    (0x20000000)
#define MSC_IRQ_get_stat_irq(data)                                                   (0x20000000&((data)<<29))
#define MSC_IRQ_get_stat_irq_src(data)                                               ((0x20000000&(data))>>29)
#define MSC_IRQ_get_get_stat_irq(data)                                               ((0x20000000&(data))>>29)
#define MSC_IRQ_get_id_irq_shift                                                     (28)
#define MSC_IRQ_get_id_irq_mask                                                      (0x10000000)
#define MSC_IRQ_get_id_irq(data)                                                     (0x10000000&((data)<<28))
#define MSC_IRQ_get_id_irq_src(data)                                                 ((0x10000000&(data))>>28)
#define MSC_IRQ_get_get_id_irq(data)                                                 ((0x10000000&(data))>>28)
#define MSC_IRQ_get_msg_irq_shift                                                    (27)
#define MSC_IRQ_get_msg_irq_mask                                                     (0x08000000)
#define MSC_IRQ_get_msg_irq(data)                                                    (0x08000000&((data)<<27))
#define MSC_IRQ_get_msg_irq_src(data)                                                ((0x08000000&(data))>>27)
#define MSC_IRQ_get_get_msg_irq(data)                                                ((0x08000000&(data))>>27)
#define MSC_IRQ_sc1_err_irq_shift                                                    (26)
#define MSC_IRQ_sc1_err_irq_mask                                                     (0x04000000)
#define MSC_IRQ_sc1_err_irq(data)                                                    (0x04000000&((data)<<26))
#define MSC_IRQ_sc1_err_irq_src(data)                                                ((0x04000000&(data))>>26)
#define MSC_IRQ_get_sc1_err_irq(data)                                                ((0x04000000&(data))>>26)
#define MSC_IRQ_ddc_err_irq_shift                                                    (25)
#define MSC_IRQ_ddc_err_irq_mask                                                     (0x02000000)
#define MSC_IRQ_ddc_err_irq(data)                                                    (0x02000000&((data)<<25))
#define MSC_IRQ_ddc_err_irq_src(data)                                                ((0x02000000&(data))>>25)
#define MSC_IRQ_get_ddc_err_irq(data)                                                ((0x02000000&(data))>>25)
#define MSC_IRQ_msc_err_irq_shift                                                    (24)
#define MSC_IRQ_msc_err_irq_mask                                                     (0x01000000)
#define MSC_IRQ_msc_err_irq(data)                                                    (0x01000000&((data)<<24))
#define MSC_IRQ_msc_err_irq_src(data)                                                ((0x01000000&(data))>>24)
#define MSC_IRQ_get_msc_err_irq(data)                                                ((0x01000000&(data))>>24)
#define MSC_IRQ_wr_burst_irq_shift                                                   (23)
#define MSC_IRQ_wr_burst_irq_mask                                                    (0x00800000)
#define MSC_IRQ_wr_burst_irq(data)                                                   (0x00800000&((data)<<23))
#define MSC_IRQ_wr_burst_irq_src(data)                                               ((0x00800000&(data))>>23)
#define MSC_IRQ_get_wr_burst_irq(data)                                               ((0x00800000&(data))>>23)
#define MSC_IRQ_sc3_err_irq_shift                                                    (22)
#define MSC_IRQ_sc3_err_irq_mask                                                     (0x00400000)
#define MSC_IRQ_sc3_err_irq(data)                                                    (0x00400000&((data)<<22))
#define MSC_IRQ_sc3_err_irq_src(data)                                                ((0x00400000&(data))>>22)
#define MSC_IRQ_get_sc3_err_irq(data)                                                ((0x00400000&(data))>>22)
#define MSC_IRQ_fwdef_cmd_irq_shift                                                  (21)
#define MSC_IRQ_fwdef_cmd_irq_mask                                                   (0x00200000)
#define MSC_IRQ_fwdef_cmd_irq(data)                                                  (0x00200000&((data)<<21))
#define MSC_IRQ_fwdef_cmd_irq_src(data)                                              ((0x00200000&(data))>>21)
#define MSC_IRQ_get_fwdef_cmd_irq(data)                                              ((0x00200000&(data))>>21)
#define MSC_IRQ_allmsc_cmd_irq_shift                                                 (20)
#define MSC_IRQ_allmsc_cmd_irq_mask                                                  (0x00100000)
#define MSC_IRQ_allmsc_cmd_irq(data)                                                 (0x00100000&((data)<<20))
#define MSC_IRQ_allmsc_cmd_irq_src(data)                                             ((0x00100000&(data))>>20)
#define MSC_IRQ_get_allmsc_cmd_irq(data)                                             ((0x00100000&(data))>>20)
#define MSC_IRQ_abort_res_irq_shift                                                  (19)
#define MSC_IRQ_abort_res_irq_mask                                                   (0x00080000)
#define MSC_IRQ_abort_res_irq(data)                                                  (0x00080000&((data)<<19))
#define MSC_IRQ_abort_res_irq_src(data)                                              ((0x00080000&(data))>>19)
#define MSC_IRQ_get_abort_res_irq(data)                                              ((0x00080000&(data))>>19)
#define MSC_IRQ_abort_req_irq_shift                                                  (18)
#define MSC_IRQ_abort_req_irq_mask                                                   (0x00040000)
#define MSC_IRQ_abort_req_irq(data)                                                  (0x00040000&((data)<<18))
#define MSC_IRQ_abort_req_irq_src(data)                                              ((0x00040000&(data))>>18)
#define MSC_IRQ_get_abort_req_irq(data)                                              ((0x00040000&(data))>>18)
#define MSC_IRQ_ddc_abort_irq_shift                                                  (17)
#define MSC_IRQ_ddc_abort_irq_mask                                                   (0x00020000)
#define MSC_IRQ_ddc_abort_irq(data)                                                  (0x00020000&((data)<<17))
#define MSC_IRQ_ddc_abort_irq_src(data)                                              ((0x00020000&(data))>>17)
#define MSC_IRQ_get_ddc_abort_irq(data)                                              ((0x00020000&(data))>>17)
#define MSC_IRQ_ddc_nack_irq_shift                                                   (16)
#define MSC_IRQ_ddc_nack_irq_mask                                                    (0x00010000)
#define MSC_IRQ_ddc_nack_irq(data)                                                   (0x00010000&((data)<<16))
#define MSC_IRQ_ddc_nack_irq_src(data)                                               ((0x00010000&(data))>>16)
#define MSC_IRQ_get_ddc_nack_irq(data)                                               ((0x00010000&(data))>>16)
#define MSC_IRQ_msge_irq_shift                                                       (15)
#define MSC_IRQ_msge_irq_mask                                                        (0x00008000)
#define MSC_IRQ_msge_irq(data)                                                       (0x00008000&((data)<<15))
#define MSC_IRQ_msge_irq_src(data)                                                   ((0x00008000&(data))>>15)
#define MSC_IRQ_get_msge_irq(data)                                                   ((0x00008000&(data))>>15)
#define MSC_IRQ_rcp_irq_shift                                                        (14)
#define MSC_IRQ_rcp_irq_mask                                                         (0x00004000)
#define MSC_IRQ_rcp_irq(data)                                                        (0x00004000&((data)<<14))
#define MSC_IRQ_rcp_irq_src(data)                                                    ((0x00004000&(data))>>14)
#define MSC_IRQ_get_rcp_irq(data)                                                    ((0x00004000&(data))>>14)
#define MSC_IRQ_rcpk_irq_shift                                                       (13)
#define MSC_IRQ_rcpk_irq_mask                                                        (0x00002000)
#define MSC_IRQ_rcpk_irq(data)                                                       (0x00002000&((data)<<13))
#define MSC_IRQ_rcpk_irq_src(data)                                                   ((0x00002000&(data))>>13)
#define MSC_IRQ_get_rcpk_irq(data)                                                   ((0x00002000&(data))>>13)
#define MSC_IRQ_rcpe_irq_shift                                                       (12)
#define MSC_IRQ_rcpe_irq_mask                                                        (0x00001000)
#define MSC_IRQ_rcpe_irq(data)                                                       (0x00001000&((data)<<12))
#define MSC_IRQ_rcpe_irq_src(data)                                                   ((0x00001000&(data))>>12)
#define MSC_IRQ_get_rcpe_irq(data)                                                   ((0x00001000&(data))>>12)
#define MSC_IRQ_rap_irq_shift                                                        (11)
#define MSC_IRQ_rap_irq_mask                                                         (0x00000800)
#define MSC_IRQ_rap_irq(data)                                                        (0x00000800&((data)<<11))
#define MSC_IRQ_rap_irq_src(data)                                                    ((0x00000800&(data))>>11)
#define MSC_IRQ_get_rap_irq(data)                                                    ((0x00000800&(data))>>11)
#define MSC_IRQ_rapk_irq_shift                                                       (10)
#define MSC_IRQ_rapk_irq_mask                                                        (0x00000400)
#define MSC_IRQ_rapk_irq(data)                                                       (0x00000400&((data)<<10))
#define MSC_IRQ_rapk_irq_src(data)                                                   ((0x00000400&(data))>>10)
#define MSC_IRQ_get_rapk_irq(data)                                                   ((0x00000400&(data))>>10)
#define MSC_IRQ_ucp_irq_shift                                                        (9)
#define MSC_IRQ_ucp_irq_mask                                                         (0x00000200)
#define MSC_IRQ_ucp_irq(data)                                                        (0x00000200&((data)<<9))
#define MSC_IRQ_ucp_irq_src(data)                                                    ((0x00000200&(data))>>9)
#define MSC_IRQ_get_ucp_irq(data)                                                    ((0x00000200&(data))>>9)
#define MSC_IRQ_ucpe_irq_shift                                                       (8)
#define MSC_IRQ_ucpe_irq_mask                                                        (0x00000100)
#define MSC_IRQ_ucpe_irq(data)                                                       (0x00000100&((data)<<8))
#define MSC_IRQ_ucpe_irq_src(data)                                                   ((0x00000100&(data))>>8)
#define MSC_IRQ_get_ucpe_irq(data)                                                   ((0x00000100&(data))>>8)
#define MSC_IRQ_ucpk_irq_shift                                                       (7)
#define MSC_IRQ_ucpk_irq_mask                                                        (0x00000080)
#define MSC_IRQ_ucpk_irq(data)                                                       (0x00000080&((data)<<7))
#define MSC_IRQ_ucpk_irq_src(data)                                                   ((0x00000080&(data))>>7)
#define MSC_IRQ_get_ucpk_irq(data)                                                   ((0x00000080&(data))>>7)
#define MSC_IRQ_msg_sub_irq_shift                                                    (6)
#define MSC_IRQ_msg_sub_irq_mask                                                     (0x00000040)
#define MSC_IRQ_msg_sub_irq(data)                                                    (0x00000040&((data)<<6))
#define MSC_IRQ_msg_sub_irq_src(data)                                                ((0x00000040&(data))>>6)
#define MSC_IRQ_get_msg_sub_irq(data)                                                ((0x00000040&(data))>>6)
#define MSC_IRQ_det_rxsense_irq_shift                                                (5)
#define MSC_IRQ_det_rxsense_irq_mask                                                 (0x00000020)
#define MSC_IRQ_det_rxsense_irq(data)                                                (0x00000020&((data)<<5))
#define MSC_IRQ_det_rxsense_irq_src(data)                                            ((0x00000020&(data))>>5)
#define MSC_IRQ_get_det_rxsense_irq(data)                                            ((0x00000020&(data))>>5)
#define MSC_IRQ_msc_hpd_irq_shift                                                    (4)
#define MSC_IRQ_msc_hpd_irq_mask                                                     (0x00000010)
#define MSC_IRQ_msc_hpd_irq(data)                                                    (0x00000010&((data)<<4))
#define MSC_IRQ_msc_hpd_irq_src(data)                                                ((0x00000010&(data))>>4)
#define MSC_IRQ_get_msc_hpd_irq(data)                                                ((0x00000010&(data))>>4)


#define MSC_IRQ_EN                                                                   0x5C
#define MSC_IRQ_EN_reg_addr                                                          "0x98037B5C"
#define MSC_IRQ_EN_reg                                                               0x98037B5C
#define set_MSC_IRQ_EN_reg(data)   (*((volatile unsigned int*) MSC_IRQ_EN_reg)=data)
#define get_MSC_IRQ_EN_reg   (*((volatile unsigned int*) MSC_IRQ_EN_reg))
#define MSC_IRQ_EN_inst_adr                                                          "0x0017"
#define MSC_IRQ_EN_inst                                                              0x0017
#define MSC_IRQ_EN_wr_stat_irq_en_shift                                              (31)
#define MSC_IRQ_EN_wr_stat_irq_en_mask                                               (0x80000000)
#define MSC_IRQ_EN_wr_stat_irq_en(data)                                              (0x80000000&((data)<<31))
#define MSC_IRQ_EN_wr_stat_irq_en_src(data)                                          ((0x80000000&(data))>>31)
#define MSC_IRQ_EN_get_wr_stat_irq_en(data)                                          ((0x80000000&(data))>>31)
#define MSC_IRQ_EN_rd_devcap_irq_en_shift                                            (30)
#define MSC_IRQ_EN_rd_devcap_irq_en_mask                                             (0x40000000)
#define MSC_IRQ_EN_rd_devcap_irq_en(data)                                            (0x40000000&((data)<<30))
#define MSC_IRQ_EN_rd_devcap_irq_en_src(data)                                        ((0x40000000&(data))>>30)
#define MSC_IRQ_EN_get_rd_devcap_irq_en(data)                                        ((0x40000000&(data))>>30)
#define MSC_IRQ_EN_get_stat_irq_en_shift                                             (29)
#define MSC_IRQ_EN_get_stat_irq_en_mask                                              (0x20000000)
#define MSC_IRQ_EN_get_stat_irq_en(data)                                             (0x20000000&((data)<<29))
#define MSC_IRQ_EN_get_stat_irq_en_src(data)                                         ((0x20000000&(data))>>29)
#define MSC_IRQ_EN_get_get_stat_irq_en(data)                                         ((0x20000000&(data))>>29)
#define MSC_IRQ_EN_get_id_irq_en_shift                                               (28)
#define MSC_IRQ_EN_get_id_irq_en_mask                                                (0x10000000)
#define MSC_IRQ_EN_get_id_irq_en(data)                                               (0x10000000&((data)<<28))
#define MSC_IRQ_EN_get_id_irq_en_src(data)                                           ((0x10000000&(data))>>28)
#define MSC_IRQ_EN_get_get_id_irq_en(data)                                           ((0x10000000&(data))>>28)
#define MSC_IRQ_EN_get_msg_irq_en_shift                                              (27)
#define MSC_IRQ_EN_get_msg_irq_en_mask                                               (0x08000000)
#define MSC_IRQ_EN_get_msg_irq_en(data)                                              (0x08000000&((data)<<27))
#define MSC_IRQ_EN_get_msg_irq_en_src(data)                                          ((0x08000000&(data))>>27)
#define MSC_IRQ_EN_get_get_msg_irq_en(data)                                          ((0x08000000&(data))>>27)
#define MSC_IRQ_EN_sc1_err_irq_en_shift                                              (26)
#define MSC_IRQ_EN_sc1_err_irq_en_mask                                               (0x04000000)
#define MSC_IRQ_EN_sc1_err_irq_en(data)                                              (0x04000000&((data)<<26))
#define MSC_IRQ_EN_sc1_err_irq_en_src(data)                                          ((0x04000000&(data))>>26)
#define MSC_IRQ_EN_get_sc1_err_irq_en(data)                                          ((0x04000000&(data))>>26)
#define MSC_IRQ_EN_ddc_err_irq_en_shift                                              (25)
#define MSC_IRQ_EN_ddc_err_irq_en_mask                                               (0x02000000)
#define MSC_IRQ_EN_ddc_err_irq_en(data)                                              (0x02000000&((data)<<25))
#define MSC_IRQ_EN_ddc_err_irq_en_src(data)                                          ((0x02000000&(data))>>25)
#define MSC_IRQ_EN_get_ddc_err_irq_en(data)                                          ((0x02000000&(data))>>25)
#define MSC_IRQ_EN_msc_err_irq_en_shift                                              (24)
#define MSC_IRQ_EN_msc_err_irq_en_mask                                               (0x01000000)
#define MSC_IRQ_EN_msc_err_irq_en(data)                                              (0x01000000&((data)<<24))
#define MSC_IRQ_EN_msc_err_irq_en_src(data)                                          ((0x01000000&(data))>>24)
#define MSC_IRQ_EN_get_msc_err_irq_en(data)                                          ((0x01000000&(data))>>24)
#define MSC_IRQ_EN_wr_burst_irq_en_shift                                             (23)
#define MSC_IRQ_EN_wr_burst_irq_en_mask                                              (0x00800000)
#define MSC_IRQ_EN_wr_burst_irq_en(data)                                             (0x00800000&((data)<<23))
#define MSC_IRQ_EN_wr_burst_irq_en_src(data)                                         ((0x00800000&(data))>>23)
#define MSC_IRQ_EN_get_wr_burst_irq_en(data)                                         ((0x00800000&(data))>>23)
#define MSC_IRQ_EN_sc3_err_irq_en_shift                                              (22)
#define MSC_IRQ_EN_sc3_err_irq_en_mask                                               (0x00400000)
#define MSC_IRQ_EN_sc3_err_irq_en(data)                                              (0x00400000&((data)<<22))
#define MSC_IRQ_EN_sc3_err_irq_en_src(data)                                          ((0x00400000&(data))>>22)
#define MSC_IRQ_EN_get_sc3_err_irq_en(data)                                          ((0x00400000&(data))>>22)
#define MSC_IRQ_EN_fwdef_cmd_irq_en_shift                                            (21)
#define MSC_IRQ_EN_fwdef_cmd_irq_en_mask                                             (0x00200000)
#define MSC_IRQ_EN_fwdef_cmd_irq_en(data)                                            (0x00200000&((data)<<21))
#define MSC_IRQ_EN_fwdef_cmd_irq_en_src(data)                                        ((0x00200000&(data))>>21)
#define MSC_IRQ_EN_get_fwdef_cmd_irq_en(data)                                        ((0x00200000&(data))>>21)
#define MSC_IRQ_EN_allmsc_cmd_irq_en_shift                                           (20)
#define MSC_IRQ_EN_allmsc_cmd_irq_en_mask                                            (0x00100000)
#define MSC_IRQ_EN_allmsc_cmd_irq_en(data)                                           (0x00100000&((data)<<20))
#define MSC_IRQ_EN_allmsc_cmd_irq_en_src(data)                                       ((0x00100000&(data))>>20)
#define MSC_IRQ_EN_get_allmsc_cmd_irq_en(data)                                       ((0x00100000&(data))>>20)
#define MSC_IRQ_EN_abort_res_irq_en_shift                                            (19)
#define MSC_IRQ_EN_abort_res_irq_en_mask                                             (0x00080000)
#define MSC_IRQ_EN_abort_res_irq_en(data)                                            (0x00080000&((data)<<19))
#define MSC_IRQ_EN_abort_res_irq_en_src(data)                                        ((0x00080000&(data))>>19)
#define MSC_IRQ_EN_get_abort_res_irq_en(data)                                        ((0x00080000&(data))>>19)
#define MSC_IRQ_EN_abort_req_irq_en_shift                                            (18)
#define MSC_IRQ_EN_abort_req_irq_en_mask                                             (0x00040000)
#define MSC_IRQ_EN_abort_req_irq_en(data)                                            (0x00040000&((data)<<18))
#define MSC_IRQ_EN_abort_req_irq_en_src(data)                                        ((0x00040000&(data))>>18)
#define MSC_IRQ_EN_get_abort_req_irq_en(data)                                        ((0x00040000&(data))>>18)
#define MSC_IRQ_EN_ddc_abort_irq_en_shift                                            (17)
#define MSC_IRQ_EN_ddc_abort_irq_en_mask                                             (0x00020000)
#define MSC_IRQ_EN_ddc_abort_irq_en(data)                                            (0x00020000&((data)<<17))
#define MSC_IRQ_EN_ddc_abort_irq_en_src(data)                                        ((0x00020000&(data))>>17)
#define MSC_IRQ_EN_get_ddc_abort_irq_en(data)                                        ((0x00020000&(data))>>17)
#define MSC_IRQ_EN_ddc_nack_irq_en_shift                                             (16)
#define MSC_IRQ_EN_ddc_nack_irq_en_mask                                              (0x00010000)
#define MSC_IRQ_EN_ddc_nack_irq_en(data)                                             (0x00010000&((data)<<16))
#define MSC_IRQ_EN_ddc_nack_irq_en_src(data)                                         ((0x00010000&(data))>>16)
#define MSC_IRQ_EN_get_ddc_nack_irq_en(data)                                         ((0x00010000&(data))>>16)
#define MSC_IRQ_EN_msge_irq_en_shift                                                 (15)
#define MSC_IRQ_EN_msge_irq_en_mask                                                  (0x00008000)
#define MSC_IRQ_EN_msge_irq_en(data)                                                 (0x00008000&((data)<<15))
#define MSC_IRQ_EN_msge_irq_en_src(data)                                             ((0x00008000&(data))>>15)
#define MSC_IRQ_EN_get_msge_irq_en(data)                                             ((0x00008000&(data))>>15)
#define MSC_IRQ_EN_rcp_irq_en_shift                                                  (14)
#define MSC_IRQ_EN_rcp_irq_en_mask                                                   (0x00004000)
#define MSC_IRQ_EN_rcp_irq_en(data)                                                  (0x00004000&((data)<<14))
#define MSC_IRQ_EN_rcp_irq_en_src(data)                                              ((0x00004000&(data))>>14)
#define MSC_IRQ_EN_get_rcp_irq_en(data)                                              ((0x00004000&(data))>>14)
#define MSC_IRQ_EN_rcpk_irq_en_shift                                                 (13)
#define MSC_IRQ_EN_rcpk_irq_en_mask                                                  (0x00002000)
#define MSC_IRQ_EN_rcpk_irq_en(data)                                                 (0x00002000&((data)<<13))
#define MSC_IRQ_EN_rcpk_irq_en_src(data)                                             ((0x00002000&(data))>>13)
#define MSC_IRQ_EN_get_rcpk_irq_en(data)                                             ((0x00002000&(data))>>13)
#define MSC_IRQ_EN_rcpe_irq_en_shift                                                 (12)
#define MSC_IRQ_EN_rcpe_irq_en_mask                                                  (0x00001000)
#define MSC_IRQ_EN_rcpe_irq_en(data)                                                 (0x00001000&((data)<<12))
#define MSC_IRQ_EN_rcpe_irq_en_src(data)                                             ((0x00001000&(data))>>12)
#define MSC_IRQ_EN_get_rcpe_irq_en(data)                                             ((0x00001000&(data))>>12)
#define MSC_IRQ_EN_rap_irq_en_shift                                                  (11)
#define MSC_IRQ_EN_rap_irq_en_mask                                                   (0x00000800)
#define MSC_IRQ_EN_rap_irq_en(data)                                                  (0x00000800&((data)<<11))
#define MSC_IRQ_EN_rap_irq_en_src(data)                                              ((0x00000800&(data))>>11)
#define MSC_IRQ_EN_get_rap_irq_en(data)                                              ((0x00000800&(data))>>11)
#define MSC_IRQ_EN_rapk_irq_en_shift                                                 (10)
#define MSC_IRQ_EN_rapk_irq_en_mask                                                  (0x00000400)
#define MSC_IRQ_EN_rapk_irq_en(data)                                                 (0x00000400&((data)<<10))
#define MSC_IRQ_EN_rapk_irq_en_src(data)                                             ((0x00000400&(data))>>10)
#define MSC_IRQ_EN_get_rapk_irq_en(data)                                             ((0x00000400&(data))>>10)
#define MSC_IRQ_EN_ucp_irq_en_shift                                                  (9)
#define MSC_IRQ_EN_ucp_irq_en_mask                                                   (0x00000200)
#define MSC_IRQ_EN_ucp_irq_en(data)                                                  (0x00000200&((data)<<9))
#define MSC_IRQ_EN_ucp_irq_en_src(data)                                              ((0x00000200&(data))>>9)
#define MSC_IRQ_EN_get_ucp_irq_en(data)                                              ((0x00000200&(data))>>9)
#define MSC_IRQ_EN_ucpe_irq_en_shift                                                 (8)
#define MSC_IRQ_EN_ucpe_irq_en_mask                                                  (0x00000100)
#define MSC_IRQ_EN_ucpe_irq_en(data)                                                 (0x00000100&((data)<<8))
#define MSC_IRQ_EN_ucpe_irq_en_src(data)                                             ((0x00000100&(data))>>8)
#define MSC_IRQ_EN_get_ucpe_irq_en(data)                                             ((0x00000100&(data))>>8)
#define MSC_IRQ_EN_ucpk_irq_en_shift                                                 (7)
#define MSC_IRQ_EN_ucpk_irq_en_mask                                                  (0x00000080)
#define MSC_IRQ_EN_ucpk_irq_en(data)                                                 (0x00000080&((data)<<7))
#define MSC_IRQ_EN_ucpk_irq_en_src(data)                                             ((0x00000080&(data))>>7)
#define MSC_IRQ_EN_get_ucpk_irq_en(data)                                             ((0x00000080&(data))>>7)
#define MSC_IRQ_EN_msg_sub_irq_en_shift                                              (6)
#define MSC_IRQ_EN_msg_sub_irq_en_mask                                               (0x00000040)
#define MSC_IRQ_EN_msg_sub_irq_en(data)                                              (0x00000040&((data)<<6))
#define MSC_IRQ_EN_msg_sub_irq_en_src(data)                                          ((0x00000040&(data))>>6)
#define MSC_IRQ_EN_get_msg_sub_irq_en(data)                                          ((0x00000040&(data))>>6)
#define MSC_IRQ_EN_det_rxsense_irq_en_shift                                          (5)
#define MSC_IRQ_EN_det_rxsense_irq_en_mask                                           (0x00000020)
#define MSC_IRQ_EN_det_rxsense_irq_en(data)                                          (0x00000020&((data)<<5))
#define MSC_IRQ_EN_det_rxsense_irq_en_src(data)                                      ((0x00000020&(data))>>5)
#define MSC_IRQ_EN_get_det_rxsense_irq_en(data)                                      ((0x00000020&(data))>>5)
#define MSC_IRQ_EN_msc_hpd_irq_en_shift                                              (4)
#define MSC_IRQ_EN_msc_hpd_irq_en_mask                                               (0x00000010)
#define MSC_IRQ_EN_msc_hpd_irq_en(data)                                              (0x00000010&((data)<<4))
#define MSC_IRQ_EN_msc_hpd_irq_en_src(data)                                          ((0x00000010&(data))>>4)
#define MSC_IRQ_EN_get_msc_hpd_irq_en(data)                                          ((0x00000010&(data))>>4)


#define CBUS_TX_INT                                                                  0x90
#define CBUS_TX_INT_reg_addr                                                         "0x98037B90"
#define CBUS_TX_INT_reg                                                              0x98037B90
#define set_CBUS_TX_INT_reg(data)   (*((volatile unsigned int*) CBUS_TX_INT_reg)=data)
#define get_CBUS_TX_INT_reg   (*((volatile unsigned int*) CBUS_TX_INT_reg))
#define CBUS_TX_INT_inst_adr                                                         "0x0024"
#define CBUS_TX_INT_inst                                                             0x0024
#define CBUS_TX_INT_fw0_fin_irq_en_shift                                             (31)
#define CBUS_TX_INT_fw0_fin_irq_en_mask                                              (0x80000000)
#define CBUS_TX_INT_fw0_fin_irq_en(data)                                             (0x80000000&((data)<<31))
#define CBUS_TX_INT_fw0_fin_irq_en_src(data)                                         ((0x80000000&(data))>>31)
#define CBUS_TX_INT_get_fw0_fin_irq_en(data)                                         ((0x80000000&(data))>>31)
#define CBUS_TX_INT_fw0_cmd_irq_en_shift                                             (30)
#define CBUS_TX_INT_fw0_cmd_irq_en_mask                                              (0x40000000)
#define CBUS_TX_INT_fw0_cmd_irq_en(data)                                             (0x40000000&((data)<<30))
#define CBUS_TX_INT_fw0_cmd_irq_en_src(data)                                         ((0x40000000&(data))>>30)
#define CBUS_TX_INT_get_fw0_cmd_irq_en(data)                                         ((0x40000000&(data))>>30)
#define CBUS_TX_INT_fw0_data_irq_en_shift                                            (29)
#define CBUS_TX_INT_fw0_data_irq_en_mask                                             (0x20000000)
#define CBUS_TX_INT_fw0_data_irq_en(data)                                            (0x20000000&((data)<<29))
#define CBUS_TX_INT_fw0_data_irq_en_src(data)                                        ((0x20000000&(data))>>29)
#define CBUS_TX_INT_get_fw0_data_irq_en(data)                                        ((0x20000000&(data))>>29)
#define CBUS_TX_INT_ddc_fin_irq_en_shift                                             (23)
#define CBUS_TX_INT_ddc_fin_irq_en_mask                                              (0x00800000)
#define CBUS_TX_INT_ddc_fin_irq_en(data)                                             (0x00800000&((data)<<23))
#define CBUS_TX_INT_ddc_fin_irq_en_src(data)                                         ((0x00800000&(data))>>23)
#define CBUS_TX_INT_get_ddc_fin_irq_en(data)                                         ((0x00800000&(data))>>23)
#define CBUS_TX_INT_clk_mode_irq_en_shift                                            (15)
#define CBUS_TX_INT_clk_mode_irq_en_mask                                             (0x00008000)
#define CBUS_TX_INT_clk_mode_irq_en(data)                                            (0x00008000&((data)<<15))
#define CBUS_TX_INT_clk_mode_irq_en_src(data)                                        ((0x00008000&(data))>>15)
#define CBUS_TX_INT_get_clk_mode_irq_en(data)                                        ((0x00008000&(data))>>15)
#define CBUS_TX_INT_dcap_rdy_irq_en_shift                                            (14)
#define CBUS_TX_INT_dcap_rdy_irq_en_mask                                             (0x00004000)
#define CBUS_TX_INT_dcap_rdy_irq_en(data)                                            (0x00004000&((data)<<14))
#define CBUS_TX_INT_dcap_rdy_irq_en_src(data)                                        ((0x00004000&(data))>>14)
#define CBUS_TX_INT_get_dcap_rdy_irq_en(data)                                        ((0x00004000&(data))>>14)
#define CBUS_TX_INT_muted_chg_irq_en_shift                                           (13)
#define CBUS_TX_INT_muted_chg_irq_en_mask                                            (0x00002000)
#define CBUS_TX_INT_muted_chg_irq_en(data)                                           (0x00002000&((data)<<13))
#define CBUS_TX_INT_muted_chg_irq_en_src(data)                                       ((0x00002000&(data))>>13)
#define CBUS_TX_INT_get_muted_chg_irq_en(data)                                       ((0x00002000&(data))>>13)
#define CBUS_TX_INT_path_en_irq_en_shift                                             (12)
#define CBUS_TX_INT_path_en_irq_en_mask                                              (0x00001000)
#define CBUS_TX_INT_path_en_irq_en(data)                                             (0x00001000&((data)<<12))
#define CBUS_TX_INT_path_en_irq_en_src(data)                                         ((0x00001000&(data))>>12)
#define CBUS_TX_INT_get_path_en_irq_en(data)                                         ((0x00001000&(data))>>12)
#define CBUS_TX_INT_det_z1k_irq_en_shift                                             (11)
#define CBUS_TX_INT_det_z1k_irq_en_mask                                              (0x00000800)
#define CBUS_TX_INT_det_z1k_irq_en(data)                                             (0x00000800&((data)<<11))
#define CBUS_TX_INT_det_z1k_irq_en_src(data)                                         ((0x00000800&(data))>>11)
#define CBUS_TX_INT_get_det_z1k_irq_en(data)                                         ((0x00000800&(data))>>11)
#define CBUS_TX_INT_sink_det_irq_en_shift                                            (10)
#define CBUS_TX_INT_sink_det_irq_en_mask                                             (0x00000400)
#define CBUS_TX_INT_sink_det_irq_en(data)                                            (0x00000400&((data)<<10))
#define CBUS_TX_INT_sink_det_irq_en_src(data)                                        ((0x00000400&(data))>>10)
#define CBUS_TX_INT_get_sink_det_irq_en(data)                                        ((0x00000400&(data))>>10)
#define CBUS_TX_INT_parity_err_irq_en_shift                                          (9)
#define CBUS_TX_INT_parity_err_irq_en_mask                                           (0x00000200)
#define CBUS_TX_INT_parity_err_irq_en(data)                                          (0x00000200&((data)<<9))
#define CBUS_TX_INT_parity_err_irq_en_src(data)                                      ((0x00000200&(data))>>9)
#define CBUS_TX_INT_get_parity_err_irq_en(data)                                      ((0x00000200&(data))>>9)
#define CBUS_TX_INT_disconn_irq_en_shift                                             (8)
#define CBUS_TX_INT_disconn_irq_en_mask                                              (0x00000100)
#define CBUS_TX_INT_disconn_irq_en(data)                                             (0x00000100&((data)<<8))
#define CBUS_TX_INT_disconn_irq_en_src(data)                                         ((0x00000100&(data))>>8)
#define CBUS_TX_INT_get_disconn_irq_en(data)                                         ((0x00000100&(data))>>8)
#define CBUS_TX_INT_det_hpd_irq_en_shift                                             (7)
#define CBUS_TX_INT_det_hpd_irq_en_mask                                              (0x00000080)
#define CBUS_TX_INT_det_hpd_irq_en(data)                                             (0x00000080&((data)<<7))
#define CBUS_TX_INT_det_hpd_irq_en_src(data)                                         ((0x00000080&(data))>>7)
#define CBUS_TX_INT_get_det_hpd_irq_en(data)                                         ((0x00000080&(data))>>7)


#define CBUS_TX_INT1                                                                 0x94
#define CBUS_TX_INT1_reg_addr                                                        "0x98037B94"
#define CBUS_TX_INT1_reg                                                             0x98037B94
#define set_CBUS_TX_INT1_reg(data)   (*((volatile unsigned int*) CBUS_TX_INT1_reg)=data)
#define get_CBUS_TX_INT1_reg   (*((volatile unsigned int*) CBUS_TX_INT1_reg))
#define CBUS_TX_INT1_inst_adr                                                        "0x0025"
#define CBUS_TX_INT1_inst                                                            0x0025
#define CBUS_TX_INT1_fw0_fin_irq_shift                                               (31)
#define CBUS_TX_INT1_fw0_fin_irq_mask                                                (0x80000000)
#define CBUS_TX_INT1_fw0_fin_irq(data)                                               (0x80000000&((data)<<31))
#define CBUS_TX_INT1_fw0_fin_irq_src(data)                                           ((0x80000000&(data))>>31)
#define CBUS_TX_INT1_get_fw0_fin_irq(data)                                           ((0x80000000&(data))>>31)
#define CBUS_TX_INT1_fw0_cmd_irq_shift                                               (30)
#define CBUS_TX_INT1_fw0_cmd_irq_mask                                                (0x40000000)
#define CBUS_TX_INT1_fw0_cmd_irq(data)                                               (0x40000000&((data)<<30))
#define CBUS_TX_INT1_fw0_cmd_irq_src(data)                                           ((0x40000000&(data))>>30)
#define CBUS_TX_INT1_get_fw0_cmd_irq(data)                                           ((0x40000000&(data))>>30)
#define CBUS_TX_INT1_fw0_data_irq_shift                                              (29)
#define CBUS_TX_INT1_fw0_data_irq_mask                                               (0x20000000)
#define CBUS_TX_INT1_fw0_data_irq(data)                                              (0x20000000&((data)<<29))
#define CBUS_TX_INT1_fw0_data_irq_src(data)                                          ((0x20000000&(data))>>29)
#define CBUS_TX_INT1_get_fw0_data_irq(data)                                          ((0x20000000&(data))>>29)
#define CBUS_TX_INT1_ddc_fin_irq_shift                                               (23)
#define CBUS_TX_INT1_ddc_fin_irq_mask                                                (0x00800000)
#define CBUS_TX_INT1_ddc_fin_irq(data)                                               (0x00800000&((data)<<23))
#define CBUS_TX_INT1_ddc_fin_irq_src(data)                                           ((0x00800000&(data))>>23)
#define CBUS_TX_INT1_get_ddc_fin_irq(data)                                           ((0x00800000&(data))>>23)
#define CBUS_TX_INT1_clk_mode_chg_shift                                              (15)
#define CBUS_TX_INT1_clk_mode_chg_mask                                               (0x00008000)
#define CBUS_TX_INT1_clk_mode_chg(data)                                              (0x00008000&((data)<<15))
#define CBUS_TX_INT1_clk_mode_chg_src(data)                                          ((0x00008000&(data))>>15)
#define CBUS_TX_INT1_get_clk_mode_chg(data)                                          ((0x00008000&(data))>>15)
#define CBUS_TX_INT1_dcap_rdy_chg_shift                                              (14)
#define CBUS_TX_INT1_dcap_rdy_chg_mask                                               (0x00004000)
#define CBUS_TX_INT1_dcap_rdy_chg(data)                                              (0x00004000&((data)<<14))
#define CBUS_TX_INT1_dcap_rdy_chg_src(data)                                          ((0x00004000&(data))>>14)
#define CBUS_TX_INT1_get_dcap_rdy_chg(data)                                          ((0x00004000&(data))>>14)
#define CBUS_TX_INT1_muted_chg_shift                                                 (13)
#define CBUS_TX_INT1_muted_chg_mask                                                  (0x00002000)
#define CBUS_TX_INT1_muted_chg(data)                                                 (0x00002000&((data)<<13))
#define CBUS_TX_INT1_muted_chg_src(data)                                             ((0x00002000&(data))>>13)
#define CBUS_TX_INT1_get_muted_chg(data)                                             ((0x00002000&(data))>>13)
#define CBUS_TX_INT1_path_en_chg_shift                                               (12)
#define CBUS_TX_INT1_path_en_chg_mask                                                (0x00001000)
#define CBUS_TX_INT1_path_en_chg(data)                                               (0x00001000&((data)<<12))
#define CBUS_TX_INT1_path_en_chg_src(data)                                           ((0x00001000&(data))>>12)
#define CBUS_TX_INT1_get_path_en_chg(data)                                           ((0x00001000&(data))>>12)
#define CBUS_TX_INT1_det_z1k_irq_shift                                               (11)
#define CBUS_TX_INT1_det_z1k_irq_mask                                                (0x00000800)
#define CBUS_TX_INT1_det_z1k_irq(data)                                               (0x00000800&((data)<<11))
#define CBUS_TX_INT1_det_z1k_irq_src(data)                                           ((0x00000800&(data))>>11)
#define CBUS_TX_INT1_get_det_z1k_irq(data)                                           ((0x00000800&(data))>>11)
#define CBUS_TX_INT1_sink_det_irq_shift                                              (10)
#define CBUS_TX_INT1_sink_det_irq_mask                                               (0x00000400)
#define CBUS_TX_INT1_sink_det_irq(data)                                              (0x00000400&((data)<<10))
#define CBUS_TX_INT1_sink_det_irq_src(data)                                          ((0x00000400&(data))>>10)
#define CBUS_TX_INT1_get_sink_det_irq(data)                                          ((0x00000400&(data))>>10)
#define CBUS_TX_INT1_parity_err_irq_shift                                            (9)
#define CBUS_TX_INT1_parity_err_irq_mask                                             (0x00000200)
#define CBUS_TX_INT1_parity_err_irq(data)                                            (0x00000200&((data)<<9))
#define CBUS_TX_INT1_parity_err_irq_src(data)                                        ((0x00000200&(data))>>9)
#define CBUS_TX_INT1_get_parity_err_irq(data)                                        ((0x00000200&(data))>>9)
#define CBUS_TX_INT1_disconn_irq_shift                                               (8)
#define CBUS_TX_INT1_disconn_irq_mask                                                (0x00000100)
#define CBUS_TX_INT1_disconn_irq(data)                                               (0x00000100&((data)<<8))
#define CBUS_TX_INT1_disconn_irq_src(data)                                           ((0x00000100&(data))>>8)
#define CBUS_TX_INT1_get_disconn_irq(data)                                           ((0x00000100&(data))>>8)
#define CBUS_TX_INT1_det_hpd_irq_shift                                               (7)
#define CBUS_TX_INT1_det_hpd_irq_mask                                                (0x00000080)
#define CBUS_TX_INT1_det_hpd_irq(data)                                               (0x00000080&((data)<<7))
#define CBUS_TX_INT1_det_hpd_irq_src(data)                                           ((0x00000080&(data))>>7)
#define CBUS_TX_INT1_get_det_hpd_irq(data)                                           ((0x00000080&(data))>>7)


#define DEVCAP_INT_EN                                                                0xA8
#define DEVCAP_INT_EN_reg_addr                                                       "0x98037BA8"
#define DEVCAP_INT_EN_reg                                                            0x98037BA8
#define set_DEVCAP_INT_EN_reg(data)   (*((volatile unsigned int*) DEVCAP_INT_EN_reg)=data)
#define get_DEVCAP_INT_EN_reg   (*((volatile unsigned int*) DEVCAP_INT_EN_reg))
#define DEVCAP_INT_EN_inst_adr                                                       "0x002A"
#define DEVCAP_INT_EN_inst                                                           0x002A
#define DEVCAP_INT_EN_chg23_irq_en_shift                                             (24)
#define DEVCAP_INT_EN_chg23_irq_en_mask                                              (0xFF000000)
#define DEVCAP_INT_EN_chg23_irq_en(data)                                             (0xFF000000&((data)<<24))
#define DEVCAP_INT_EN_chg23_irq_en_src(data)                                         ((0xFF000000&(data))>>24)
#define DEVCAP_INT_EN_get_chg23_irq_en(data)                                         ((0xFF000000&(data))>>24)
#define DEVCAP_INT_EN_chg22_irq_en_shift                                             (16)
#define DEVCAP_INT_EN_chg22_irq_en_mask                                              (0x00FF0000)
#define DEVCAP_INT_EN_chg22_irq_en(data)                                             (0x00FF0000&((data)<<16))
#define DEVCAP_INT_EN_chg22_irq_en_src(data)                                         ((0x00FF0000&(data))>>16)
#define DEVCAP_INT_EN_get_chg22_irq_en(data)                                         ((0x00FF0000&(data))>>16)
#define DEVCAP_INT_EN_dchg_bit7_irq_en_shift                                         (15)
#define DEVCAP_INT_EN_dchg_bit7_irq_en_mask                                          (0x00008000)
#define DEVCAP_INT_EN_dchg_bit7_irq_en(data)                                         (0x00008000&((data)<<15))
#define DEVCAP_INT_EN_dchg_bit7_irq_en_src(data)                                     ((0x00008000&(data))>>15)
#define DEVCAP_INT_EN_get_dchg_bit7_irq_en(data)                                     ((0x00008000&(data))>>15)
#define DEVCAP_INT_EN_dchg_bit6_irq_en_shift                                         (14)
#define DEVCAP_INT_EN_dchg_bit6_irq_en_mask                                          (0x00004000)
#define DEVCAP_INT_EN_dchg_bit6_irq_en(data)                                         (0x00004000&((data)<<14))
#define DEVCAP_INT_EN_dchg_bit6_irq_en_src(data)                                     ((0x00004000&(data))>>14)
#define DEVCAP_INT_EN_get_dchg_bit6_irq_en(data)                                     ((0x00004000&(data))>>14)
#define DEVCAP_INT_EN_dchg_bit5_irq_en_shift                                         (13)
#define DEVCAP_INT_EN_dchg_bit5_irq_en_mask                                          (0x00002000)
#define DEVCAP_INT_EN_dchg_bit5_irq_en(data)                                         (0x00002000&((data)<<13))
#define DEVCAP_INT_EN_dchg_bit5_irq_en_src(data)                                     ((0x00002000&(data))>>13)
#define DEVCAP_INT_EN_get_dchg_bit5_irq_en(data)                                     ((0x00002000&(data))>>13)
#define DEVCAP_INT_EN_dchg_bit4_irq_en_shift                                         (12)
#define DEVCAP_INT_EN_dchg_bit4_irq_en_mask                                          (0x00001000)
#define DEVCAP_INT_EN_dchg_bit4_irq_en(data)                                         (0x00001000&((data)<<12))
#define DEVCAP_INT_EN_dchg_bit4_irq_en_src(data)                                     ((0x00001000&(data))>>12)
#define DEVCAP_INT_EN_get_dchg_bit4_irq_en(data)                                     ((0x00001000&(data))>>12)
#define DEVCAP_INT_EN_dchg_bit3_irq_en_shift                                         (11)
#define DEVCAP_INT_EN_dchg_bit3_irq_en_mask                                          (0x00000800)
#define DEVCAP_INT_EN_dchg_bit3_irq_en(data)                                         (0x00000800&((data)<<11))
#define DEVCAP_INT_EN_dchg_bit3_irq_en_src(data)                                     ((0x00000800&(data))>>11)
#define DEVCAP_INT_EN_get_dchg_bit3_irq_en(data)                                     ((0x00000800&(data))>>11)
#define DEVCAP_INT_EN_dchg_bit2_irq_en_shift                                         (10)
#define DEVCAP_INT_EN_dchg_bit2_irq_en_mask                                          (0x00000400)
#define DEVCAP_INT_EN_dchg_bit2_irq_en(data)                                         (0x00000400&((data)<<10))
#define DEVCAP_INT_EN_dchg_bit2_irq_en_src(data)                                     ((0x00000400&(data))>>10)
#define DEVCAP_INT_EN_get_dchg_bit2_irq_en(data)                                     ((0x00000400&(data))>>10)
#define DEVCAP_INT_EN_edid_irq_en_shift                                              (9)
#define DEVCAP_INT_EN_edid_irq_en_mask                                               (0x00000200)
#define DEVCAP_INT_EN_edid_irq_en(data)                                              (0x00000200&((data)<<9))
#define DEVCAP_INT_EN_edid_irq_en_src(data)                                          ((0x00000200&(data))>>9)
#define DEVCAP_INT_EN_get_edid_irq_en(data)                                          ((0x00000200&(data))>>9)
#define DEVCAP_INT_EN_dchg_bit0_irq_en_shift                                         (8)
#define DEVCAP_INT_EN_dchg_bit0_irq_en_mask                                          (0x00000100)
#define DEVCAP_INT_EN_dchg_bit0_irq_en(data)                                         (0x00000100&((data)<<8))
#define DEVCAP_INT_EN_dchg_bit0_irq_en_src(data)                                     ((0x00000100&(data))>>8)
#define DEVCAP_INT_EN_get_dchg_bit0_irq_en(data)                                     ((0x00000100&(data))>>8)
#define DEVCAP_INT_EN_rchg_irq_en_shift                                              (5)
#define DEVCAP_INT_EN_rchg_irq_en_mask                                               (0x000000E0)
#define DEVCAP_INT_EN_rchg_irq_en(data)                                              (0x000000E0&((data)<<5))
#define DEVCAP_INT_EN_rchg_irq_en_src(data)                                          ((0x000000E0&(data))>>5)
#define DEVCAP_INT_EN_get_rchg_irq_en(data)                                          ((0x000000E0&(data))>>5)
#define DEVCAP_INT_EN_req_3d_irq_en_shift                                            (4)
#define DEVCAP_INT_EN_req_3d_irq_en_mask                                             (0x00000010)
#define DEVCAP_INT_EN_req_3d_irq_en(data)                                            (0x00000010&((data)<<4))
#define DEVCAP_INT_EN_req_3d_irq_en_src(data)                                        ((0x00000010&(data))>>4)
#define DEVCAP_INT_EN_get_req_3d_irq_en(data)                                        ((0x00000010&(data))>>4)
#define DEVCAP_INT_EN_grt_irq_en_shift                                               (3)
#define DEVCAP_INT_EN_grt_irq_en_mask                                                (0x00000008)
#define DEVCAP_INT_EN_grt_irq_en(data)                                               (0x00000008&((data)<<3))
#define DEVCAP_INT_EN_grt_irq_en_src(data)                                           ((0x00000008&(data))>>3)
#define DEVCAP_INT_EN_get_grt_irq_en(data)                                           ((0x00000008&(data))>>3)
#define DEVCAP_INT_EN_req_irq_en_shift                                               (2)
#define DEVCAP_INT_EN_req_irq_en_mask                                                (0x00000004)
#define DEVCAP_INT_EN_req_irq_en(data)                                               (0x00000004&((data)<<2))
#define DEVCAP_INT_EN_req_irq_en_src(data)                                           ((0x00000004&(data))>>2)
#define DEVCAP_INT_EN_get_req_irq_en(data)                                           ((0x00000004&(data))>>2)
#define DEVCAP_INT_EN_dscr_irq_en_shift                                              (1)
#define DEVCAP_INT_EN_dscr_irq_en_mask                                               (0x00000002)
#define DEVCAP_INT_EN_dscr_irq_en(data)                                              (0x00000002&((data)<<1))
#define DEVCAP_INT_EN_dscr_irq_en_src(data)                                          ((0x00000002&(data))>>1)
#define DEVCAP_INT_EN_get_dscr_irq_en(data)                                          ((0x00000002&(data))>>1)
#define DEVCAP_INT_EN_dcap_irq_en_shift                                              (0)
#define DEVCAP_INT_EN_dcap_irq_en_mask                                               (0x00000001)
#define DEVCAP_INT_EN_dcap_irq_en(data)                                              (0x00000001&((data)<<0))
#define DEVCAP_INT_EN_dcap_irq_en_src(data)                                          ((0x00000001&(data))>>0)
#define DEVCAP_INT_EN_get_dcap_irq_en(data)                                          ((0x00000001&(data))>>0)


#define DEVCAP_INT_EN1                                                               0xAC
#define DEVCAP_INT_EN1_reg_addr                                                      "0x98037BAC"
#define DEVCAP_INT_EN1_reg                                                           0x98037BAC
#define set_DEVCAP_INT_EN1_reg(data)   (*((volatile unsigned int*) DEVCAP_INT_EN1_reg)=data)
#define get_DEVCAP_INT_EN1_reg   (*((volatile unsigned int*) DEVCAP_INT_EN1_reg))
#define DEVCAP_INT_EN1_inst_adr                                                      "0x002B"
#define DEVCAP_INT_EN1_inst                                                          0x002B
#define DEVCAP_INT_EN1_chg27_irq_en_shift                                            (24)
#define DEVCAP_INT_EN1_chg27_irq_en_mask                                             (0xFF000000)
#define DEVCAP_INT_EN1_chg27_irq_en(data)                                            (0xFF000000&((data)<<24))
#define DEVCAP_INT_EN1_chg27_irq_en_src(data)                                        ((0xFF000000&(data))>>24)
#define DEVCAP_INT_EN1_get_chg27_irq_en(data)                                        ((0xFF000000&(data))>>24)
#define DEVCAP_INT_EN1_chg26_irq_en_shift                                            (16)
#define DEVCAP_INT_EN1_chg26_irq_en_mask                                             (0x00FF0000)
#define DEVCAP_INT_EN1_chg26_irq_en(data)                                            (0x00FF0000&((data)<<16))
#define DEVCAP_INT_EN1_chg26_irq_en_src(data)                                        ((0x00FF0000&(data))>>16)
#define DEVCAP_INT_EN1_get_chg26_irq_en(data)                                        ((0x00FF0000&(data))>>16)
#define DEVCAP_INT_EN1_chg25_irq_en_shift                                            (8)
#define DEVCAP_INT_EN1_chg25_irq_en_mask                                             (0x0000FF00)
#define DEVCAP_INT_EN1_chg25_irq_en(data)                                            (0x0000FF00&((data)<<8))
#define DEVCAP_INT_EN1_chg25_irq_en_src(data)                                        ((0x0000FF00&(data))>>8)
#define DEVCAP_INT_EN1_get_chg25_irq_en(data)                                        ((0x0000FF00&(data))>>8)
#define DEVCAP_INT_EN1_chg24_irq_en_shift                                            (0)
#define DEVCAP_INT_EN1_chg24_irq_en_mask                                             (0x000000FF)
#define DEVCAP_INT_EN1_chg24_irq_en(data)                                            (0x000000FF&((data)<<0))
#define DEVCAP_INT_EN1_chg24_irq_en_src(data)                                        ((0x000000FF&(data))>>0)
#define DEVCAP_INT_EN1_get_chg24_irq_en(data)                                        ((0x000000FF&(data))>>0)


#define CBUS_TEST                                                                    0x9C
#define CBUS_TEST_reg_addr                                                           "0x98037B9C"
#define CBUS_TEST_reg                                                                0x98037B9C
#define set_CBUS_TEST_reg(data)   (*((volatile unsigned int*) CBUS_TEST_reg)=data)
#define get_CBUS_TEST_reg   (*((volatile unsigned int*) CBUS_TEST_reg))
#define CBUS_TEST_inst_adr                                                           "0x0027"
#define CBUS_TEST_inst                                                               0x0027
#define CBUS_TEST_cbus_test_md_shift                                                 (30)
#define CBUS_TEST_cbus_test_md_mask                                                  (0xC0000000)
#define CBUS_TEST_cbus_test_md(data)                                                 (0xC0000000&((data)<<30))
#define CBUS_TEST_cbus_test_md_src(data)                                             ((0xC0000000&(data))>>30)
#define CBUS_TEST_get_cbus_test_md(data)                                             ((0xC0000000&(data))>>30)
#define CBUS_TEST_fw_out_shift                                                       (29)
#define CBUS_TEST_fw_out_mask                                                        (0x20000000)
#define CBUS_TEST_fw_out(data)                                                       (0x20000000&((data)<<29))
#define CBUS_TEST_fw_out_src(data)                                                   ((0x20000000&(data))>>29)
#define CBUS_TEST_get_fw_out(data)                                                   ((0x20000000&(data))>>29)
#define CBUS_TEST_dbg_sel_shift                                                      (26)
#define CBUS_TEST_dbg_sel_mask                                                       (0x1C000000)
#define CBUS_TEST_dbg_sel(data)                                                      (0x1C000000&((data)<<26))
#define CBUS_TEST_dbg_sel_src(data)                                                  ((0x1C000000&(data))>>26)
#define CBUS_TEST_get_dbg_sel(data)                                                  ((0x1C000000&(data))>>26)


#define PHY_CTRL                                                                     0xD0
#define PHY_CTRL_reg_addr                                                            "0x98037BD0"
#define PHY_CTRL_reg                                                                 0x98037BD0
#define set_PHY_CTRL_reg(data)   (*((volatile unsigned int*) PHY_CTRL_reg)=data)
#define get_PHY_CTRL_reg   (*((volatile unsigned int*) PHY_CTRL_reg))
#define PHY_CTRL_inst_adr                                                            "0x0034"
#define PHY_CTRL_inst                                                                0x0034
#define PHY_CTRL_reg_mhl_bmos_en_tx_shift                                            (31)
#define PHY_CTRL_reg_mhl_bmos_en_tx_mask                                             (0x80000000)
#define PHY_CTRL_reg_mhl_bmos_en_tx(data)                                            (0x80000000&((data)<<31))
#define PHY_CTRL_reg_mhl_bmos_en_tx_src(data)                                        ((0x80000000&(data))>>31)
#define PHY_CTRL_get_reg_mhl_bmos_en_tx(data)                                        ((0x80000000&(data))>>31)
#define PHY_CTRL_reg_mhl_hpd_det_tx_shift                                            (30)
#define PHY_CTRL_reg_mhl_hpd_det_tx_mask                                             (0x40000000)
#define PHY_CTRL_reg_mhl_hpd_det_tx(data)                                            (0x40000000&((data)<<30))
#define PHY_CTRL_reg_mhl_hpd_det_tx_src(data)                                        ((0x40000000&(data))>>30)
#define PHY_CTRL_get_reg_mhl_hpd_det_tx(data)                                        ((0x40000000&(data))>>30)
#define PHY_CTRL_reg_mhl_r1k_det_tx_shift                                            (29)
#define PHY_CTRL_reg_mhl_r1k_det_tx_mask                                             (0x20000000)
#define PHY_CTRL_reg_mhl_r1k_det_tx(data)                                            (0x20000000&((data)<<29))
#define PHY_CTRL_reg_mhl_r1k_det_tx_src(data)                                        ((0x20000000&(data))>>29)
#define PHY_CTRL_get_reg_mhl_r1k_det_tx(data)                                        ((0x20000000&(data))>>29)
#define PHY_CTRL_reg_r1k_vth_sel_tx_shift                                            (28)
#define PHY_CTRL_reg_r1k_vth_sel_tx_mask                                             (0x10000000)
#define PHY_CTRL_reg_r1k_vth_sel_tx(data)                                            (0x10000000&((data)<<28))
#define PHY_CTRL_reg_r1k_vth_sel_tx_src(data)                                        ((0x10000000&(data))>>28)
#define PHY_CTRL_get_reg_r1k_vth_sel_tx(data)                                        ((0x10000000&(data))>>28)
#define PHY_CTRL_reg_mhl_tst_en_tx_shift                                             (27)
#define PHY_CTRL_reg_mhl_tst_en_tx_mask                                              (0x08000000)
#define PHY_CTRL_reg_mhl_tst_en_tx(data)                                             (0x08000000&((data)<<27))
#define PHY_CTRL_reg_mhl_tst_en_tx_src(data)                                         ((0x08000000&(data))>>27)
#define PHY_CTRL_get_reg_mhl_tst_en_tx(data)                                         ((0x08000000&(data))>>27)
#define PHY_CTRL_reg_mhl_vsel_tx_shift                                               (24)
#define PHY_CTRL_reg_mhl_vsel_tx_mask                                                (0x07000000)
#define PHY_CTRL_reg_mhl_vsel_tx(data)                                               (0x07000000&((data)<<24))
#define PHY_CTRL_reg_mhl_vsel_tx_src(data)                                           ((0x07000000&(data))>>24)
#define PHY_CTRL_get_reg_mhl_vsel_tx(data)                                           ((0x07000000&(data))>>24)
#define PHY_CTRL_reg_mhl_r10k_tx_shift                                               (21)
#define PHY_CTRL_reg_mhl_r10k_tx_mask                                                (0x00E00000)
#define PHY_CTRL_reg_mhl_r10k_tx(data)                                               (0x00E00000&((data)<<21))
#define PHY_CTRL_reg_mhl_r10k_tx_src(data)                                           ((0x00E00000&(data))>>21)
#define PHY_CTRL_get_reg_mhl_r10k_tx(data)                                           ((0x00E00000&(data))>>21)
#define PHY_CTRL_reg_cbus_strc_tx_shift                                              (18)
#define PHY_CTRL_reg_cbus_strc_tx_mask                                               (0x001C0000)
#define PHY_CTRL_reg_cbus_strc_tx(data)                                              (0x001C0000&((data)<<18))
#define PHY_CTRL_reg_cbus_strc_tx_src(data)                                          ((0x001C0000&(data))>>18)
#define PHY_CTRL_get_reg_cbus_strc_tx(data)                                          ((0x001C0000&(data))>>18)
#define PHY_CTRL_reg_en_bias_txrx_shift                                              (17)
#define PHY_CTRL_reg_en_bias_txrx_mask                                               (0x00020000)
#define PHY_CTRL_reg_en_bias_txrx(data)                                              (0x00020000&((data)<<17))
#define PHY_CTRL_reg_en_bias_txrx_src(data)                                          ((0x00020000&(data))>>17)
#define PHY_CTRL_get_reg_en_bias_txrx(data)                                          ((0x00020000&(data))>>17)
#define PHY_CTRL_tst_sel_h_tx_shift                                                  (15)
#define PHY_CTRL_tst_sel_h_tx_mask                                                   (0x00018000)
#define PHY_CTRL_tst_sel_h_tx(data)                                                  (0x00018000&((data)<<15))
#define PHY_CTRL_tst_sel_h_tx_src(data)                                              ((0x00018000&(data))>>15)
#define PHY_CTRL_get_tst_sel_h_tx(data)                                              ((0x00018000&(data))>>15)
#define PHY_CTRL_reg_mhl_r10k_test_tx_shift                                          (14)
#define PHY_CTRL_reg_mhl_r10k_test_tx_mask                                           (0x00004000)
#define PHY_CTRL_reg_mhl_r10k_test_tx(data)                                          (0x00004000&((data)<<14))
#define PHY_CTRL_reg_mhl_r10k_test_tx_src(data)                                      ((0x00004000&(data))>>14)
#define PHY_CTRL_get_reg_mhl_r10k_test_tx(data)                                      ((0x00004000&(data))>>14)


#define PHY_STATUS                                                                   0xD4
#define PHY_STATUS_reg_addr                                                          "0x98037BD4"
#define PHY_STATUS_reg                                                               0x98037BD4
#define set_PHY_STATUS_reg(data)   (*((volatile unsigned int*) PHY_STATUS_reg)=data)
#define get_PHY_STATUS_reg   (*((volatile unsigned int*) PHY_STATUS_reg))
#define PHY_STATUS_inst_adr                                                          "0x0035"
#define PHY_STATUS_inst                                                              0x0035
#define PHY_STATUS_hdmi_hpd_out_tx_shift                                             (3)
#define PHY_STATUS_hdmi_hpd_out_tx_mask                                              (0x00000008)
#define PHY_STATUS_hdmi_hpd_out_tx(data)                                             (0x00000008&((data)<<3))
#define PHY_STATUS_hdmi_hpd_out_tx_src(data)                                         ((0x00000008&(data))>>3)
#define PHY_STATUS_get_hdmi_hpd_out_tx(data)                                         ((0x00000008&(data))>>3)
#define PHY_STATUS_hdmi_hpd_en_tx_shift                                              (2)
#define PHY_STATUS_hdmi_hpd_en_tx_mask                                               (0x00000004)
#define PHY_STATUS_hdmi_hpd_en_tx(data)                                              (0x00000004&((data)<<2))
#define PHY_STATUS_hdmi_hpd_en_tx_src(data)                                          ((0x00000004&(data))>>2)
#define PHY_STATUS_get_hdmi_hpd_en_tx(data)                                          ((0x00000004&(data))>>2)
#define PHY_STATUS_rego_mhl_hpd_det_tx_shift                                         (1)
#define PHY_STATUS_rego_mhl_hpd_det_tx_mask                                          (0x00000002)
#define PHY_STATUS_rego_mhl_hpd_det_tx(data)                                         (0x00000002&((data)<<1))
#define PHY_STATUS_rego_mhl_hpd_det_tx_src(data)                                     ((0x00000002&(data))>>1)
#define PHY_STATUS_get_rego_mhl_hpd_det_tx(data)                                     ((0x00000002&(data))>>1)
#define PHY_STATUS_rego_mhl_r1k_det_tx_shift                                         (0)
#define PHY_STATUS_rego_mhl_r1k_det_tx_mask                                          (0x00000001)
#define PHY_STATUS_rego_mhl_r1k_det_tx(data)                                         (0x00000001&((data)<<0))
#define PHY_STATUS_rego_mhl_r1k_det_tx_src(data)                                     ((0x00000001&(data))>>0)
#define PHY_STATUS_get_rego_mhl_r1k_det_tx(data)                                     ((0x00000001&(data))>>0)


#define CBUS_CTRL9                                                                   0xD8
#define CBUS_CTRL9_reg_addr                                                          "0x98037BD8"
#define CBUS_CTRL9_reg                                                               0x98037BD8
#define set_CBUS_CTRL9_reg(data)   (*((volatile unsigned int*) CBUS_CTRL9_reg)=data)
#define get_CBUS_CTRL9_reg   (*((volatile unsigned int*) CBUS_CTRL9_reg))
#define CBUS_CTRL9_inst_adr                                                          "0x0036"
#define CBUS_CTRL9_inst                                                              0x0036
#define CBUS_CTRL9_deb_lv_shift                                                      (24)
#define CBUS_CTRL9_deb_lv_mask                                                       (0x07000000)
#define CBUS_CTRL9_deb_lv(data)                                                      (0x07000000&((data)<<24))
#define CBUS_CTRL9_deb_lv_src(data)                                                  ((0x07000000&(data))>>24)
#define CBUS_CTRL9_get_deb_lv(data)                                                  ((0x07000000&(data))>>24)
#define CBUS_CTRL9_det_r1k_cnt_shift                                                 (16)
#define CBUS_CTRL9_det_r1k_cnt_mask                                                  (0x000F0000)
#define CBUS_CTRL9_det_r1k_cnt(data)                                                 (0x000F0000&((data)<<16))
#define CBUS_CTRL9_det_r1k_cnt_src(data)                                             ((0x000F0000&(data))>>16)
#define CBUS_CTRL9_get_det_r1k_cnt(data)                                             ((0x000F0000&(data))>>16)
#define CBUS_CTRL9_clk_1k_div_shift                                                  (0)
#define CBUS_CTRL9_clk_1k_div_mask                                                   (0x000003FF)
#define CBUS_CTRL9_clk_1k_div(data)                                                  (0x000003FF&((data)<<0))
#define CBUS_CTRL9_clk_1k_div_src(data)                                              ((0x000003FF&(data))>>0)
#define CBUS_CTRL9_get_clk_1k_div(data)                                              ((0x000003FF&(data))>>0)


#define DUMMY_CTRL                                                                   0xE0
#define DUMMY_CTRL_reg_addr                                                          "0x98037BE0"
#define DUMMY_CTRL_reg                                                               0x98037BE0
#define set_DUMMY_CTRL_reg(data)   (*((volatile unsigned int*) DUMMY_CTRL_reg)=data)
#define get_DUMMY_CTRL_reg   (*((volatile unsigned int*) DUMMY_CTRL_reg))
#define DUMMY_CTRL_inst_adr                                                          "0x0038"
#define DUMMY_CTRL_inst                                                              0x0038
#define DUMMY_CTRL_dummy_reg_shift                                                   (0)
#define DUMMY_CTRL_dummy_reg_mask                                                    (0xFFFFFFFF)
#define DUMMY_CTRL_dummy_reg(data)                                                   (0xFFFFFFFF&((data)<<0))
#define DUMMY_CTRL_dummy_reg_src(data)                                               ((0xFFFFFFFF&(data))>>0)
#define DUMMY_CTRL_get_dummy_reg(data)                                               ((0xFFFFFFFF&(data))>>0)


#define CBUS_CTRL10                                                                  0xDC
#define CBUS_CTRL10_reg_addr                                                         "0x98037BDC"
#define CBUS_CTRL10_reg                                                              0x98037BDC
#define set_CBUS_CTRL10_reg(data)   (*((volatile unsigned int*) CBUS_CTRL10_reg)=data)
#define get_CBUS_CTRL10_reg   (*((volatile unsigned int*) CBUS_CTRL10_reg))
#define CBUS_CTRL10_inst_adr                                                         "0x0037"
#define CBUS_CTRL10_inst                                                             0x0037
#define CBUS_CTRL10_link_layer_st_shift                                              (28)
#define CBUS_CTRL10_link_layer_st_mask                                               (0xF0000000)
#define CBUS_CTRL10_link_layer_st(data)                                              (0xF0000000&((data)<<28))
#define CBUS_CTRL10_link_layer_st_src(data)                                          ((0xF0000000&(data))>>28)
#define CBUS_CTRL10_get_link_layer_st(data)                                          ((0xF0000000&(data))>>28)
#define CBUS_CTRL10_hw_en_10k_shift                                                  (25)
#define CBUS_CTRL10_hw_en_10k_mask                                                   (0x02000000)
#define CBUS_CTRL10_hw_en_10k(data)                                                  (0x02000000&((data)<<25))
#define CBUS_CTRL10_hw_en_10k_src(data)                                              ((0x02000000&(data))>>25)
#define CBUS_CTRL10_get_hw_en_10k(data)                                              ((0x02000000&(data))>>25)
#define CBUS_CTRL10_hw_en_5k_shift                                                   (24)
#define CBUS_CTRL10_hw_en_5k_mask                                                    (0x01000000)
#define CBUS_CTRL10_hw_en_5k(data)                                                   (0x01000000&((data)<<24))
#define CBUS_CTRL10_hw_en_5k_src(data)                                               ((0x01000000&(data))>>24)
#define CBUS_CTRL10_get_hw_en_5k(data)                                               ((0x01000000&(data))>>24)
#define CBUS_CTRL10_det_r1k_st_shift                                                 (16)
#define CBUS_CTRL10_det_r1k_st_mask                                                  (0x00030000)
#define CBUS_CTRL10_det_r1k_st(data)                                                 (0x00030000&((data)<<16))
#define CBUS_CTRL10_det_r1k_st_src(data)                                             ((0x00030000&(data))>>16)
#define CBUS_CTRL10_get_det_r1k_st(data)                                             ((0x00030000&(data))>>16)
#define CBUS_CTRL10_hw_mhl_hpd_det_shift                                             (11)
#define CBUS_CTRL10_hw_mhl_hpd_det_mask                                              (0x00000800)
#define CBUS_CTRL10_hw_mhl_hpd_det(data)                                             (0x00000800&((data)<<11))
#define CBUS_CTRL10_hw_mhl_hpd_det_src(data)                                         ((0x00000800&(data))>>11)
#define CBUS_CTRL10_get_hw_mhl_hpd_det(data)                                         ((0x00000800&(data))>>11)
#define CBUS_CTRL10_hw_mhl_r1k_det_shift                                             (10)
#define CBUS_CTRL10_hw_mhl_r1k_det_mask                                              (0x00000400)
#define CBUS_CTRL10_hw_mhl_r1k_det(data)                                             (0x00000400&((data)<<10))
#define CBUS_CTRL10_hw_mhl_r1k_det_src(data)                                         ((0x00000400&(data))>>10)
#define CBUS_CTRL10_get_hw_mhl_r1k_det(data)                                         ((0x00000400&(data))>>10)
#define CBUS_CTRL10_hw_mhl_bmos_en_shift                                             (9)
#define CBUS_CTRL10_hw_mhl_bmos_en_mask                                              (0x00000200)
#define CBUS_CTRL10_hw_mhl_bmos_en(data)                                             (0x00000200&((data)<<9))
#define CBUS_CTRL10_hw_mhl_bmos_en_src(data)                                         ((0x00000200&(data))>>9)
#define CBUS_CTRL10_get_hw_mhl_bmos_en(data)                                         ((0x00000200&(data))>>9)
#define CBUS_CTRL10_hw_mhl_vtl_sel_shift                                             (8)
#define CBUS_CTRL10_hw_mhl_vtl_sel_mask                                              (0x00000100)
#define CBUS_CTRL10_hw_mhl_vtl_sel(data)                                             (0x00000100&((data)<<8))
#define CBUS_CTRL10_hw_mhl_vtl_sel_src(data)                                         ((0x00000100&(data))>>8)
#define CBUS_CTRL10_get_hw_mhl_vtl_sel(data)                                         ((0x00000100&(data))>>8)
#define CBUS_CTRL10_fw_rst_r1k_st_shift                                              (4)
#define CBUS_CTRL10_fw_rst_r1k_st_mask                                               (0x00000010)
#define CBUS_CTRL10_fw_rst_r1k_st(data)                                              (0x00000010&((data)<<4))
#define CBUS_CTRL10_fw_rst_r1k_st_src(data)                                          ((0x00000010&(data))>>4)
#define CBUS_CTRL10_get_fw_rst_r1k_st(data)                                          ((0x00000010&(data))>>4)
#define CBUS_CTRL10_fw_r1k_det_en_shift                                              (1)
#define CBUS_CTRL10_fw_r1k_det_en_mask                                               (0x00000002)
#define CBUS_CTRL10_fw_r1k_det_en(data)                                              (0x00000002&((data)<<1))
#define CBUS_CTRL10_fw_r1k_det_en_src(data)                                          ((0x00000002&(data))>>1)
#define CBUS_CTRL10_get_fw_r1k_det_en(data)                                          ((0x00000002&(data))>>1)
#define CBUS_CTRL10_fw_r1k_det_shift                                                 (0)
#define CBUS_CTRL10_fw_r1k_det_mask                                                  (0x00000001)
#define CBUS_CTRL10_fw_r1k_det(data)                                                 (0x00000001&((data)<<0))
#define CBUS_CTRL10_fw_r1k_det_src(data)                                             ((0x00000001&(data))>>0)
#define CBUS_CTRL10_get_fw_r1k_det(data)                                             ((0x00000001&(data))>>0)


#define DEVCAP_WRITE                                                                 0x98
#define DEVCAP_WRITE_reg_addr                                                        "0x98037B98"
#define DEVCAP_WRITE_reg                                                             0x98037B98
#define set_DEVCAP_WRITE_reg(data)   (*((volatile unsigned int*) DEVCAP_WRITE_reg)=data)
#define get_DEVCAP_WRITE_reg   (*((volatile unsigned int*) DEVCAP_WRITE_reg))
#define DEVCAP_WRITE_inst_adr                                                        "0x0026"
#define DEVCAP_WRITE_inst                                                            0x0026
#define DEVCAP_WRITE_msc_offset_adr_shift                                            (24)
#define DEVCAP_WRITE_msc_offset_adr_mask                                             (0x7F000000)
#define DEVCAP_WRITE_msc_offset_adr(data)                                            (0x7F000000&((data)<<24))
#define DEVCAP_WRITE_msc_offset_adr_src(data)                                        ((0x7F000000&(data))>>24)
#define DEVCAP_WRITE_get_msc_offset_adr(data)                                        ((0x7F000000&(data))>>24)
#define DEVCAP_WRITE_devcap_rdata_shift                                              (16)
#define DEVCAP_WRITE_devcap_rdata_mask                                               (0x00FF0000)
#define DEVCAP_WRITE_devcap_rdata(data)                                              (0x00FF0000&((data)<<16))
#define DEVCAP_WRITE_devcap_rdata_src(data)                                          ((0x00FF0000&(data))>>16)
#define DEVCAP_WRITE_get_devcap_rdata(data)                                          ((0x00FF0000&(data))>>16)
#define DEVCAP_WRITE_devcap_write_shift                                              (8)
#define DEVCAP_WRITE_devcap_write_mask                                               (0x00000100)
#define DEVCAP_WRITE_devcap_write(data)                                              (0x00000100&((data)<<8))
#define DEVCAP_WRITE_devcap_write_src(data)                                          ((0x00000100&(data))>>8)
#define DEVCAP_WRITE_get_devcap_write(data)                                          ((0x00000100&(data))>>8)
#define DEVCAP_WRITE_msc_reg_data_shift                                              (0)
#define DEVCAP_WRITE_msc_reg_data_mask                                               (0x000000FF)
#define DEVCAP_WRITE_msc_reg_data(data)                                              (0x000000FF&((data)<<0))
#define DEVCAP_WRITE_msc_reg_data_src(data)                                          ((0x000000FF&(data))>>0)
#define DEVCAP_WRITE_get_msc_reg_data(data)                                          ((0x000000FF&(data))>>0)


#define MSC_DEVCAP0                                                                  0x98037C00
#define MSC_DEVCAP0_reg_addr                                                         "0x98037C00"
#define MSC_DEVCAP0_reg                                                              0x18037100
#define set_MSC_DEVCAP0_reg(data)   (*((volatile unsigned int*) MSC_DEVCAP0_reg)=data)
#define get_MSC_DEVCAP0_reg   (*((volatile unsigned int*) MSC_DEVCAP0_reg))
#define MSC_DEVCAP0_inst_adr                                                         "0x0040"
#define MSC_DEVCAP0_inst                                                             0x0040
#define MSC_DEVCAP0_adop_id_h_shift                                                  (24)
#define MSC_DEVCAP0_adop_id_h_mask                                                   (0xFF000000)
#define MSC_DEVCAP0_adop_id_h(data)                                                  (0xFF000000&((data)<<24))
#define MSC_DEVCAP0_adop_id_h_src(data)                                              ((0xFF000000&(data))>>24)
#define MSC_DEVCAP0_get_adop_id_h(data)                                              ((0xFF000000&(data))>>24)
#define MSC_DEVCAP0_dev_cat_shift                                                    (23)
#define MSC_DEVCAP0_dev_cat_mask                                                     (0x00800000)
#define MSC_DEVCAP0_dev_cat(data)                                                    (0x00800000&((data)<<23))
#define MSC_DEVCAP0_dev_cat_src(data)                                                ((0x00800000&(data))>>23)
#define MSC_DEVCAP0_get_dev_cat(data)                                                ((0x00800000&(data))>>23)
#define MSC_DEVCAP0_plim_shift                                                       (21)
#define MSC_DEVCAP0_plim_mask                                                        (0x00600000)
#define MSC_DEVCAP0_plim(data)                                                       (0x00600000&((data)<<21))
#define MSC_DEVCAP0_plim_src(data)                                                   ((0x00600000&(data))>>21)
#define MSC_DEVCAP0_get_plim(data)                                                   ((0x00600000&(data))>>21)
#define MSC_DEVCAP0_pow_shift                                                        (20)
#define MSC_DEVCAP0_pow_mask                                                         (0x00100000)
#define MSC_DEVCAP0_pow(data)                                                        (0x00100000&((data)<<20))
#define MSC_DEVCAP0_pow_src(data)                                                    ((0x00100000&(data))>>20)
#define MSC_DEVCAP0_get_pow(data)                                                    ((0x00100000&(data))>>20)
#define MSC_DEVCAP0_dev_type_shift                                                   (16)
#define MSC_DEVCAP0_dev_type_mask                                                    (0x000F0000)
#define MSC_DEVCAP0_dev_type(data)                                                   (0x000F0000&((data)<<16))
#define MSC_DEVCAP0_dev_type_src(data)                                               ((0x000F0000&(data))>>16)
#define MSC_DEVCAP0_get_dev_type(data)                                               ((0x000F0000&(data))>>16)
#define MSC_DEVCAP0_mhl_ver_shift                                                    (8)
#define MSC_DEVCAP0_mhl_ver_mask                                                     (0x0000FF00)
#define MSC_DEVCAP0_mhl_ver(data)                                                    (0x0000FF00&((data)<<8))
#define MSC_DEVCAP0_mhl_ver_src(data)                                                ((0x0000FF00&(data))>>8)
#define MSC_DEVCAP0_get_mhl_ver(data)                                                ((0x0000FF00&(data))>>8)
#define MSC_DEVCAP0_dev_state_shift                                                  (0)
#define MSC_DEVCAP0_dev_state_mask                                                   (0x000000FF)
#define MSC_DEVCAP0_dev_state(data)                                                  (0x000000FF&((data)<<0))
#define MSC_DEVCAP0_dev_state_src(data)                                              ((0x000000FF&(data))>>0)
#define MSC_DEVCAP0_get_dev_state(data)                                              ((0x000000FF&(data))>>0)


#define MSC_DEVCAP1                                                                  0x98037C04
#define MSC_DEVCAP1_reg_addr                                                         "0x98037C04"
#define MSC_DEVCAP1_reg                                                              0x98037C04
#define set_MSC_DEVCAP1_reg(data)   (*((volatile unsigned int*) MSC_DEVCAP1_reg)=data)
#define get_MSC_DEVCAP1_reg   (*((volatile unsigned int*) MSC_DEVCAP1_reg))
#define MSC_DEVCAP1_inst_adr                                                         "0x0041"
#define MSC_DEVCAP1_inst                                                             0x0041
#define MSC_DEVCAP1_aud_link_md_shift                                                (18)
#define MSC_DEVCAP1_aud_link_md_mask                                                 (0x00FC0000)
#define MSC_DEVCAP1_aud_link_md(data)                                                (0x00FC0000&((data)<<18))
#define MSC_DEVCAP1_aud_link_md_src(data)                                            ((0x00FC0000&(data))>>18)
#define MSC_DEVCAP1_get_aud_link_md(data)                                            ((0x00FC0000&(data))>>18)
#define MSC_DEVCAP1_aud_8ch_shift                                                    (17)
#define MSC_DEVCAP1_aud_8ch_mask                                                     (0x00020000)
#define MSC_DEVCAP1_aud_8ch(data)                                                    (0x00020000&((data)<<17))
#define MSC_DEVCAP1_aud_8ch_src(data)                                                ((0x00020000&(data))>>17)
#define MSC_DEVCAP1_get_aud_8ch(data)                                                ((0x00020000&(data))>>17)
#define MSC_DEVCAP1_aud_2ch_shift                                                    (16)
#define MSC_DEVCAP1_aud_2ch_mask                                                     (0x00010000)
#define MSC_DEVCAP1_aud_2ch(data)                                                    (0x00010000&((data)<<16))
#define MSC_DEVCAP1_aud_2ch_src(data)                                                ((0x00010000&(data))>>16)
#define MSC_DEVCAP1_get_aud_2ch(data)                                                ((0x00010000&(data))>>16)
#define MSC_DEVCAP1_vid_link_md_shift                                                (14)
#define MSC_DEVCAP1_vid_link_md_mask                                                 (0x0000C000)
#define MSC_DEVCAP1_vid_link_md(data)                                                (0x0000C000&((data)<<14))
#define MSC_DEVCAP1_vid_link_md_src(data)                                            ((0x0000C000&(data))>>14)
#define MSC_DEVCAP1_get_vid_link_md(data)                                            ((0x0000C000&(data))>>14)
#define MSC_DEVCAP1_supp_vga_shift                                                   (13)
#define MSC_DEVCAP1_supp_vga_mask                                                    (0x00002000)
#define MSC_DEVCAP1_supp_vga(data)                                                   (0x00002000&((data)<<13))
#define MSC_DEVCAP1_supp_vga_src(data)                                               ((0x00002000&(data))>>13)
#define MSC_DEVCAP1_get_supp_vga(data)                                               ((0x00002000&(data))>>13)
#define MSC_DEVCAP1_supp_islands_shift                                               (12)
#define MSC_DEVCAP1_supp_islands_mask                                                (0x00001000)
#define MSC_DEVCAP1_supp_islands(data)                                               (0x00001000&((data)<<12))
#define MSC_DEVCAP1_supp_islands_src(data)                                           ((0x00001000&(data))>>12)
#define MSC_DEVCAP1_get_supp_islands(data)                                           ((0x00001000&(data))>>12)
#define MSC_DEVCAP1_supp_ppixel_shift                                                (11)
#define MSC_DEVCAP1_supp_ppixel_mask                                                 (0x00000800)
#define MSC_DEVCAP1_supp_ppixel(data)                                                (0x00000800&((data)<<11))
#define MSC_DEVCAP1_supp_ppixel_src(data)                                            ((0x00000800&(data))>>11)
#define MSC_DEVCAP1_get_supp_ppixel(data)                                            ((0x00000800&(data))>>11)
#define MSC_DEVCAP1_supp_yuv422_shift                                                (10)
#define MSC_DEVCAP1_supp_yuv422_mask                                                 (0x00000400)
#define MSC_DEVCAP1_supp_yuv422(data)                                                (0x00000400&((data)<<10))
#define MSC_DEVCAP1_supp_yuv422_src(data)                                            ((0x00000400&(data))>>10)
#define MSC_DEVCAP1_get_supp_yuv422(data)                                            ((0x00000400&(data))>>10)
#define MSC_DEVCAP1_supp_yuv444_shift                                                (9)
#define MSC_DEVCAP1_supp_yuv444_mask                                                 (0x00000200)
#define MSC_DEVCAP1_supp_yuv444(data)                                                (0x00000200&((data)<<9))
#define MSC_DEVCAP1_supp_yuv444_src(data)                                            ((0x00000200&(data))>>9)
#define MSC_DEVCAP1_get_supp_yuv444(data)                                            ((0x00000200&(data))>>9)
#define MSC_DEVCAP1_supp_rgb444_shift                                                (8)
#define MSC_DEVCAP1_supp_rgb444_mask                                                 (0x00000100)
#define MSC_DEVCAP1_supp_rgb444(data)                                                (0x00000100&((data)<<8))
#define MSC_DEVCAP1_supp_rgb444_src(data)                                            ((0x00000100&(data))>>8)
#define MSC_DEVCAP1_get_supp_rgb444(data)                                            ((0x00000100&(data))>>8)
#define MSC_DEVCAP1_adop_id_l_shift                                                  (0)
#define MSC_DEVCAP1_adop_id_l_mask                                                   (0x000000FF)
#define MSC_DEVCAP1_adop_id_l(data)                                                  (0x000000FF&((data)<<0))
#define MSC_DEVCAP1_adop_id_l_src(data)                                              ((0x000000FF&(data))>>0)
#define MSC_DEVCAP1_get_adop_id_l(data)                                              ((0x000000FF&(data))>>0)


#define MSC_DEVCAP2                                                                  0x98037C08
#define MSC_DEVCAP2_reg_addr                                                         "0x98037C08"
#define MSC_DEVCAP2_reg                                                              0x98037C08
#define set_MSC_DEVCAP2_reg(data)   (*((volatile unsigned int*) MSC_DEVCAP2_reg)=data)
#define get_MSC_DEVCAP2_reg   (*((volatile unsigned int*) MSC_DEVCAP2_reg))
#define MSC_DEVCAP2_inst_adr                                                         "0x0042"
#define MSC_DEVCAP2_inst                                                             0x0042
#define MSC_DEVCAP2_device_id_h_shift                                                (24)
#define MSC_DEVCAP2_device_id_h_mask                                                 (0xFF000000)
#define MSC_DEVCAP2_device_id_h(data)                                                (0xFF000000&((data)<<24))
#define MSC_DEVCAP2_device_id_h_src(data)                                            ((0xFF000000&(data))>>24)
#define MSC_DEVCAP2_get_device_id_h(data)                                            ((0xFF000000&(data))>>24)
#define MSC_DEVCAP2_feature_flag_shift                                               (21)
#define MSC_DEVCAP2_feature_flag_mask                                                (0x00E00000)
#define MSC_DEVCAP2_feature_flag(data)                                               (0x00E00000&((data)<<21))
#define MSC_DEVCAP2_feature_flag_src(data)                                           ((0x00E00000&(data))>>21)
#define MSC_DEVCAP2_get_feature_flag(data)                                           ((0x00E00000&(data))>>21)
#define MSC_DEVCAP2_ucp_recv_supp_shift                                              (20)
#define MSC_DEVCAP2_ucp_recv_supp_mask                                               (0x00100000)
#define MSC_DEVCAP2_ucp_recv_supp(data)                                              (0x00100000&((data)<<20))
#define MSC_DEVCAP2_ucp_recv_supp_src(data)                                          ((0x00100000&(data))>>20)
#define MSC_DEVCAP2_get_ucp_recv_supp(data)                                          ((0x00100000&(data))>>20)
#define MSC_DEVCAP2_ucp_send_supp_shift                                              (19)
#define MSC_DEVCAP2_ucp_send_supp_mask                                               (0x00080000)
#define MSC_DEVCAP2_ucp_send_supp(data)                                              (0x00080000&((data)<<19))
#define MSC_DEVCAP2_ucp_send_supp_src(data)                                          ((0x00080000&(data))>>19)
#define MSC_DEVCAP2_get_ucp_send_supp(data)                                          ((0x00080000&(data))>>19)
#define MSC_DEVCAP2_sp_supp_shift                                                    (18)
#define MSC_DEVCAP2_sp_supp_mask                                                     (0x00040000)
#define MSC_DEVCAP2_sp_supp(data)                                                    (0x00040000&((data)<<18))
#define MSC_DEVCAP2_sp_supp_src(data)                                                ((0x00040000&(data))>>18)
#define MSC_DEVCAP2_get_sp_supp(data)                                                ((0x00040000&(data))>>18)
#define MSC_DEVCAP2_rap_supp_shift                                                   (17)
#define MSC_DEVCAP2_rap_supp_mask                                                    (0x00020000)
#define MSC_DEVCAP2_rap_supp(data)                                                   (0x00020000&((data)<<17))
#define MSC_DEVCAP2_rap_supp_src(data)                                               ((0x00020000&(data))>>17)
#define MSC_DEVCAP2_get_rap_supp(data)                                               ((0x00020000&(data))>>17)
#define MSC_DEVCAP2_rcp_supp_shift                                                   (16)
#define MSC_DEVCAP2_rcp_supp_mask                                                    (0x00010000)
#define MSC_DEVCAP2_rcp_supp(data)                                                   (0x00010000&((data)<<16))
#define MSC_DEVCAP2_rcp_supp_src(data)                                               ((0x00010000&(data))>>16)
#define MSC_DEVCAP2_get_rcp_supp(data)                                               ((0x00010000&(data))>>16)
#define MSC_DEVCAP2_ld_gui_shift                                                     (7)
#define MSC_DEVCAP2_ld_gui_mask                                                      (0x00000080)
#define MSC_DEVCAP2_ld_gui(data)                                                     (0x00000080&((data)<<7))
#define MSC_DEVCAP2_ld_gui_src(data)                                                 ((0x00000080&(data))>>7)
#define MSC_DEVCAP2_get_ld_gui(data)                                                 ((0x00000080&(data))>>7)
#define MSC_DEVCAP2_ld_speaker_shift                                                 (6)
#define MSC_DEVCAP2_ld_speaker_mask                                                  (0x00000040)
#define MSC_DEVCAP2_ld_speaker(data)                                                 (0x00000040&((data)<<6))
#define MSC_DEVCAP2_ld_speaker_src(data)                                             ((0x00000040&(data))>>6)
#define MSC_DEVCAP2_get_ld_speaker(data)                                             ((0x00000040&(data))>>6)
#define MSC_DEVCAP2_ld_record_shift                                                  (5)
#define MSC_DEVCAP2_ld_record_mask                                                   (0x00000020)
#define MSC_DEVCAP2_ld_record(data)                                                  (0x00000020&((data)<<5))
#define MSC_DEVCAP2_ld_record_src(data)                                              ((0x00000020&(data))>>5)
#define MSC_DEVCAP2_get_ld_record(data)                                              ((0x00000020&(data))>>5)
#define MSC_DEVCAP2_ld_tuner_shift                                                   (4)
#define MSC_DEVCAP2_ld_tuner_mask                                                    (0x00000010)
#define MSC_DEVCAP2_ld_tuner(data)                                                   (0x00000010&((data)<<4))
#define MSC_DEVCAP2_ld_tuner_src(data)                                               ((0x00000010&(data))>>4)
#define MSC_DEVCAP2_get_ld_tuner(data)                                               ((0x00000010&(data))>>4)
#define MSC_DEVCAP2_ld_media_shift                                                   (3)
#define MSC_DEVCAP2_ld_media_mask                                                    (0x00000008)
#define MSC_DEVCAP2_ld_media(data)                                                   (0x00000008&((data)<<3))
#define MSC_DEVCAP2_ld_media_src(data)                                               ((0x00000008&(data))>>3)
#define MSC_DEVCAP2_get_ld_media(data)                                               ((0x00000008&(data))>>3)
#define MSC_DEVCAP2_ld_audio_shift                                                   (2)
#define MSC_DEVCAP2_ld_audio_mask                                                    (0x00000004)
#define MSC_DEVCAP2_ld_audio(data)                                                   (0x00000004&((data)<<2))
#define MSC_DEVCAP2_ld_audio_src(data)                                               ((0x00000004&(data))>>2)
#define MSC_DEVCAP2_get_ld_audio(data)                                               ((0x00000004&(data))>>2)
#define MSC_DEVCAP2_ld_video_shift                                                   (1)
#define MSC_DEVCAP2_ld_video_mask                                                    (0x00000002)
#define MSC_DEVCAP2_ld_video(data)                                                   (0x00000002&((data)<<1))
#define MSC_DEVCAP2_ld_video_src(data)                                               ((0x00000002&(data))>>1)
#define MSC_DEVCAP2_get_ld_video(data)                                               ((0x00000002&(data))>>1)
#define MSC_DEVCAP2_ld_display_shift                                                 (0)
#define MSC_DEVCAP2_ld_display_mask                                                  (0x00000001)
#define MSC_DEVCAP2_ld_display(data)                                                 (0x00000001&((data)<<0))
#define MSC_DEVCAP2_ld_display_src(data)                                             ((0x00000001&(data))>>0)
#define MSC_DEVCAP2_get_ld_display(data)                                             ((0x00000001&(data))>>0)


#define MSC_DEVCAP3                                                                  0x98037C0C
#define MSC_DEVCAP3_reg_addr                                                         "0x9803710C"
#define MSC_DEVCAP3_reg                                                              0x98037C0C
#define set_MSC_DEVCAP3_reg(data)   (*((volatile unsigned int*) MSC_DEVCAP3_reg)=data)
#define get_MSC_DEVCAP3_reg   (*((volatile unsigned int*) MSC_DEVCAP3_reg))
#define MSC_DEVCAP3_inst_adr                                                         "0x0043"
#define MSC_DEVCAP3_inst                                                             0x0043
#define MSC_DEVCAP3_cap_0f_shift                                                     (24)
#define MSC_DEVCAP3_cap_0f_mask                                                      (0xFF000000)
#define MSC_DEVCAP3_cap_0f(data)                                                     (0xFF000000&((data)<<24))
#define MSC_DEVCAP3_cap_0f_src(data)                                                 ((0xFF000000&(data))>>24)
#define MSC_DEVCAP3_get_cap_0f(data)                                                 ((0xFF000000&(data))>>24)
#define MSC_DEVCAP3_stat_size_shift                                                  (20)
#define MSC_DEVCAP3_stat_size_mask                                                   (0x00F00000)
#define MSC_DEVCAP3_stat_size(data)                                                  (0x00F00000&((data)<<20))
#define MSC_DEVCAP3_stat_size_src(data)                                              ((0x00F00000&(data))>>20)
#define MSC_DEVCAP3_get_stat_size(data)                                              ((0x00F00000&(data))>>20)
#define MSC_DEVCAP3_int_size_shift                                                   (16)
#define MSC_DEVCAP3_int_size_mask                                                    (0x000F0000)
#define MSC_DEVCAP3_int_size(data)                                                   (0x000F0000&((data)<<16))
#define MSC_DEVCAP3_int_size_src(data)                                               ((0x000F0000&(data))>>16)
#define MSC_DEVCAP3_get_int_size(data)                                               ((0x000F0000&(data))>>16)
#define MSC_DEVCAP3_scratchpad_size_shift                                            (8)
#define MSC_DEVCAP3_scratchpad_size_mask                                             (0x0000FF00)
#define MSC_DEVCAP3_scratchpad_size(data)                                            (0x0000FF00&((data)<<8))
#define MSC_DEVCAP3_scratchpad_size_src(data)                                        ((0x0000FF00&(data))>>8)
#define MSC_DEVCAP3_get_scratchpad_size(data)                                        ((0x0000FF00&(data))>>8)
#define MSC_DEVCAP3_device_id_l_shift                                                (0)
#define MSC_DEVCAP3_device_id_l_mask                                                 (0x000000FF)
#define MSC_DEVCAP3_device_id_l(data)                                                (0x000000FF&((data)<<0))
#define MSC_DEVCAP3_device_id_l_src(data)                                            ((0x000000FF&(data))>>0)
#define MSC_DEVCAP3_get_device_id_l(data)                                            ((0x000000FF&(data))>>0)


#define MSC_DEVCAP4                                                                  0x98037C10
#define MSC_DEVCAP4_reg_addr                                                         "0x98037C10"
#define MSC_DEVCAP4_reg                                                              0x98037C10
#define set_MSC_DEVCAP4_reg(data)   (*((volatile unsigned int*) MSC_DEVCAP4_reg)=data)
#define get_MSC_DEVCAP4_reg   (*((volatile unsigned int*) MSC_DEVCAP4_reg))
#define MSC_DEVCAP4_inst_adr                                                         "0x0044"
#define MSC_DEVCAP4_inst                                                             0x0044
#define MSC_DEVCAP4_chg23_irq_shift                                                  (24)
#define MSC_DEVCAP4_chg23_irq_mask                                                   (0xFF000000)
#define MSC_DEVCAP4_chg23_irq(data)                                                  (0xFF000000&((data)<<24))
#define MSC_DEVCAP4_chg23_irq_src(data)                                              ((0xFF000000&(data))>>24)
#define MSC_DEVCAP4_get_chg23_irq(data)                                              ((0xFF000000&(data))>>24)
#define MSC_DEVCAP4_chg22_irq_shift                                                  (16)
#define MSC_DEVCAP4_chg22_irq_mask                                                   (0x00FF0000)
#define MSC_DEVCAP4_chg22_irq(data)                                                  (0x00FF0000&((data)<<16))
#define MSC_DEVCAP4_chg22_irq_src(data)                                              ((0x00FF0000&(data))>>16)
#define MSC_DEVCAP4_get_chg22_irq(data)                                              ((0x00FF0000&(data))>>16)
#define MSC_DEVCAP4_dchg_irq_shift                                                   (10)
#define MSC_DEVCAP4_dchg_irq_mask                                                    (0x0000FC00)
#define MSC_DEVCAP4_dchg_irq(data)                                                   (0x0000FC00&((data)<<10))
#define MSC_DEVCAP4_dchg_irq_src(data)                                               ((0x0000FC00&(data))>>10)
#define MSC_DEVCAP4_get_dchg_irq(data)                                               ((0x0000FC00&(data))>>10)
#define MSC_DEVCAP4_edid_chg_shift                                                   (9)
#define MSC_DEVCAP4_edid_chg_mask                                                    (0x00000200)
#define MSC_DEVCAP4_edid_chg(data)                                                   (0x00000200&((data)<<9))
#define MSC_DEVCAP4_edid_chg_src(data)                                               ((0x00000200&(data))>>9)
#define MSC_DEVCAP4_get_edid_chg(data)                                               ((0x00000200&(data))>>9)
#define MSC_DEVCAP4_dchg_irq_0_shift                                                 (8)
#define MSC_DEVCAP4_dchg_irq_0_mask                                                  (0x00000100)
#define MSC_DEVCAP4_dchg_irq_0(data)                                                 (0x00000100&((data)<<8))
#define MSC_DEVCAP4_dchg_irq_0_src(data)                                             ((0x00000100&(data))>>8)
#define MSC_DEVCAP4_get_dchg_irq_0(data)                                             ((0x00000100&(data))>>8)
#define MSC_DEVCAP4_rchg_irq_shift                                                   (5)
#define MSC_DEVCAP4_rchg_irq_mask                                                    (0x000000E0)
#define MSC_DEVCAP4_rchg_irq(data)                                                   (0x000000E0&((data)<<5))
#define MSC_DEVCAP4_rchg_irq_src(data)                                               ((0x000000E0&(data))>>5)
#define MSC_DEVCAP4_get_rchg_irq(data)                                               ((0x000000E0&(data))>>5)
#define MSC_DEVCAP4_3d_req_shift                                                     (4)
#define MSC_DEVCAP4_3d_req_mask                                                      (0x00000010)
#define MSC_DEVCAP4_3d_req(data)                                                     (0x00000010&((data)<<4))
#define MSC_DEVCAP4_3d_req_src(data)                                                 ((0x00000010&(data))>>4)
#define MSC_DEVCAP4_get_3d_req(data)                                                 ((0x00000010&(data))>>4)
#define MSC_DEVCAP4_grt_wrt_shift                                                    (3)
#define MSC_DEVCAP4_grt_wrt_mask                                                     (0x00000008)
#define MSC_DEVCAP4_grt_wrt(data)                                                    (0x00000008&((data)<<3))
#define MSC_DEVCAP4_grt_wrt_src(data)                                                ((0x00000008&(data))>>3)
#define MSC_DEVCAP4_get_grt_wrt(data)                                                ((0x00000008&(data))>>3)
#define MSC_DEVCAP4_req_wrt_shift                                                    (2)
#define MSC_DEVCAP4_req_wrt_mask                                                     (0x00000004)
#define MSC_DEVCAP4_req_wrt(data)                                                    (0x00000004&((data)<<2))
#define MSC_DEVCAP4_req_wrt_src(data)                                                ((0x00000004&(data))>>2)
#define MSC_DEVCAP4_get_req_wrt(data)                                                ((0x00000004&(data))>>2)
#define MSC_DEVCAP4_dscr_chg_shift                                                   (1)
#define MSC_DEVCAP4_dscr_chg_mask                                                    (0x00000002)
#define MSC_DEVCAP4_dscr_chg(data)                                                   (0x00000002&((data)<<1))
#define MSC_DEVCAP4_dscr_chg_src(data)                                               ((0x00000002&(data))>>1)
#define MSC_DEVCAP4_get_dscr_chg(data)                                               ((0x00000002&(data))>>1)
#define MSC_DEVCAP4_dcap_chg_shift                                                   (0)
#define MSC_DEVCAP4_dcap_chg_mask                                                    (0x00000001)
#define MSC_DEVCAP4_dcap_chg(data)                                                   (0x00000001&((data)<<0))
#define MSC_DEVCAP4_dcap_chg_src(data)                                               ((0x00000001&(data))>>0)
#define MSC_DEVCAP4_get_dcap_chg(data)                                               ((0x00000001&(data))>>0)


#define MSC_DEVCAP5                                                                  0x98037C14
#define MSC_DEVCAP5_reg_addr                                                         "0x98037C14"
#define MSC_DEVCAP5_reg                                                              0x98037C14
#define set_MSC_DEVCAP5_reg(data)   (*((volatile unsigned int*) MSC_DEVCAP5_reg)=data)
#define get_MSC_DEVCAP5_reg   (*((volatile unsigned int*) MSC_DEVCAP5_reg))
#define MSC_DEVCAP5_inst_adr                                                         "0x0045"
#define MSC_DEVCAP5_inst                                                             0x0045
#define MSC_DEVCAP5_chg27_irq_shift                                                  (24)
#define MSC_DEVCAP5_chg27_irq_mask                                                   (0xFF000000)
#define MSC_DEVCAP5_chg27_irq(data)                                                  (0xFF000000&((data)<<24))
#define MSC_DEVCAP5_chg27_irq_src(data)                                              ((0xFF000000&(data))>>24)
#define MSC_DEVCAP5_get_chg27_irq(data)                                              ((0xFF000000&(data))>>24)
#define MSC_DEVCAP5_chg26_irq_shift                                                  (16)
#define MSC_DEVCAP5_chg26_irq_mask                                                   (0x00FF0000)
#define MSC_DEVCAP5_chg26_irq(data)                                                  (0x00FF0000&((data)<<16))
#define MSC_DEVCAP5_chg26_irq_src(data)                                              ((0x00FF0000&(data))>>16)
#define MSC_DEVCAP5_get_chg26_irq(data)                                              ((0x00FF0000&(data))>>16)
#define MSC_DEVCAP5_chg25_irq_shift                                                  (8)
#define MSC_DEVCAP5_chg25_irq_mask                                                   (0x0000FF00)
#define MSC_DEVCAP5_chg25_irq(data)                                                  (0x0000FF00&((data)<<8))
#define MSC_DEVCAP5_chg25_irq_src(data)                                              ((0x0000FF00&(data))>>8)
#define MSC_DEVCAP5_get_chg25_irq(data)                                              ((0x0000FF00&(data))>>8)
#define MSC_DEVCAP5_chg24_irq_shift                                                  (0)
#define MSC_DEVCAP5_chg24_irq_mask                                                   (0x000000FF)
#define MSC_DEVCAP5_chg24_irq(data)                                                  (0x000000FF&((data)<<0))
#define MSC_DEVCAP5_chg24_irq_src(data)                                              ((0x000000FF&(data))>>0)
#define MSC_DEVCAP5_get_chg24_irq(data)                                              ((0x000000FF&(data))>>0)


#define MSC_DEVCAP6                                                                  0x98037C18
#define MSC_DEVCAP6_reg_addr                                                         "0x98037C18"
#define MSC_DEVCAP6_reg                                                              0x98037C18
#define set_MSC_DEVCAP6_reg(data)   (*((volatile unsigned int*) MSC_DEVCAP6_reg)=data)
#define get_MSC_DEVCAP6_reg   (*((volatile unsigned int*) MSC_DEVCAP6_reg))
#define MSC_DEVCAP6_inst_adr                                                         "0x0046"
#define MSC_DEVCAP6_inst                                                             0x0046


#define MSC_DEVCAP7                                                                  0x98037C1C
#define MSC_DEVCAP7_reg_addr                                                         "0x98037C1C"
#define MSC_DEVCAP7_reg                                                              0x98037C1C
#define set_MSC_DEVCAP7_reg(data)   (*((volatile unsigned int*) MSC_DEVCAP7_reg)=data)
#define get_MSC_DEVCAP7_reg   (*((volatile unsigned int*) MSC_DEVCAP7_reg))
#define MSC_DEVCAP7_inst_adr                                                         "0x0047"
#define MSC_DEVCAP7_inst                                                             0x0047


#define MSC_DEVCAP8                                                                  0x98037C20
#define MSC_DEVCAP8_reg_addr                                                         "0x98037C20"
#define MSC_DEVCAP8_reg                                                              0x98037C20
#define set_MSC_DEVCAP8_reg(data)   (*((volatile unsigned int*) MSC_DEVCAP8_reg)=data)
#define get_MSC_DEVCAP8_reg   (*((volatile unsigned int*) MSC_DEVCAP8_reg))
#define MSC_DEVCAP8_inst_adr                                                         "0x0048"
#define MSC_DEVCAP8_inst                                                             0x0048
#define MSC_DEVCAP8_muted_shift                                                      (12)
#define MSC_DEVCAP8_muted_mask                                                       (0x00001000)
#define MSC_DEVCAP8_muted(data)                                                      (0x00001000&((data)<<12))
#define MSC_DEVCAP8_muted_src(data)                                                  ((0x00001000&(data))>>12)
#define MSC_DEVCAP8_get_muted(data)                                                  ((0x00001000&(data))>>12)
#define MSC_DEVCAP8_path_en_shift                                                    (11)
#define MSC_DEVCAP8_path_en_mask                                                     (0x00000800)
#define MSC_DEVCAP8_path_en(data)                                                    (0x00000800&((data)<<11))
#define MSC_DEVCAP8_path_en_src(data)                                                ((0x00000800&(data))>>11)
#define MSC_DEVCAP8_get_path_en(data)                                                ((0x00000800&(data))>>11)
#define MSC_DEVCAP8_clk_mode_shift                                                   (8)
#define MSC_DEVCAP8_clk_mode_mask                                                    (0x00000700)
#define MSC_DEVCAP8_clk_mode(data)                                                   (0x00000700&((data)<<8))
#define MSC_DEVCAP8_clk_mode_src(data)                                               ((0x00000700&(data))>>8)
#define MSC_DEVCAP8_get_clk_mode(data)                                               ((0x00000700&(data))>>8)
#define MSC_DEVCAP8_dcap_rdy_shift                                                   (0)
#define MSC_DEVCAP8_dcap_rdy_mask                                                    (0x00000001)
#define MSC_DEVCAP8_dcap_rdy(data)                                                   (0x00000001&((data)<<0))
#define MSC_DEVCAP8_dcap_rdy_src(data)                                               ((0x00000001&(data))>>0)
#define MSC_DEVCAP8_get_dcap_rdy(data)                                               ((0x00000001&(data))>>0)


#define MSC_DEVCAP9                                                                  0x98037C24
#define MSC_DEVCAP9_reg_addr                                                         "0x98037C24"
#define MSC_DEVCAP9_reg                                                              0x98037C24
#define set_MSC_DEVCAP9_reg(data)   (*((volatile unsigned int*) MSC_DEVCAP9_reg)=data)
#define get_MSC_DEVCAP9_reg   (*((volatile unsigned int*) MSC_DEVCAP9_reg))
#define MSC_DEVCAP9_inst_adr                                                         "0x0049"
#define MSC_DEVCAP9_inst                                                             0x0049


#define MSC_DEVCAP10                                                                 0x98037C28
#define MSC_DEVCAP10_reg_addr                                                        "0x98037C28"
#define MSC_DEVCAP10_reg                                                             0x98037C28
#define set_MSC_DEVCAP10_reg(data)   (*((volatile unsigned int*) MSC_DEVCAP10_reg)=data)
#define get_MSC_DEVCAP10_reg   (*((volatile unsigned int*) MSC_DEVCAP10_reg))
#define MSC_DEVCAP10_inst_adr                                                        "0x004A"
#define MSC_DEVCAP10_inst                                                            0x004A


#define MSC_DEVCAP11                                                                 0x98037C2c
#define MSC_DEVCAP11_reg_addr                                                        "0x98037C2C"
#define MSC_DEVCAP11_reg                                                             0x98037C2C
#define set_MSC_DEVCAP11_reg(data)   (*((volatile unsigned int*) MSC_DEVCAP11_reg)=data)
#define get_MSC_DEVCAP11_reg   (*((volatile unsigned int*) MSC_DEVCAP11_reg))
#define MSC_DEVCAP11_inst_adr                                                        "0x004B"
#define MSC_DEVCAP11_inst                                                            0x004B


#define MSC_DEVCAP12                                                                 0x98037C30
#define MSC_DEVCAP12_reg_addr                                                        "0x98037C30"
#define MSC_DEVCAP12_reg                                                             0x98037C30
#define set_MSC_DEVCAP12_reg(data)   (*((volatile unsigned int*) MSC_DEVCAP12_reg)=data)
#define get_MSC_DEVCAP12_reg   (*((volatile unsigned int*) MSC_DEVCAP12_reg))
#define MSC_DEVCAP12_inst_adr                                                        "0x004C"
#define MSC_DEVCAP12_inst                                                            0x004C
#define MSC_DEVCAP12_scratchpad_reg0_shift                                           (0)
#define MSC_DEVCAP12_scratchpad_reg0_mask                                            (0xFFFFFFFF)
#define MSC_DEVCAP12_scratchpad_reg0(data)                                           (0xFFFFFFFF&((data)<<0))
#define MSC_DEVCAP12_scratchpad_reg0_src(data)                                       ((0xFFFFFFFF&(data))>>0)
#define MSC_DEVCAP12_get_scratchpad_reg0(data)                                       ((0xFFFFFFFF&(data))>>0)


#define MSC_DEVCAP13                                                                 0x98037C34
#define MSC_DEVCAP13_reg_addr                                                        "0x98037C34"
#define MSC_DEVCAP13_reg                                                             0x98037C34
#define set_MSC_DEVCAP13_reg(data)   (*((volatile unsigned int*) MSC_DEVCAP13_reg)=data)
#define get_MSC_DEVCAP13_reg   (*((volatile unsigned int*) MSC_DEVCAP13_reg))
#define MSC_DEVCAP13_inst_adr                                                        "0x004D"
#define MSC_DEVCAP13_inst                                                            0x004D
#define MSC_DEVCAP13_scratchpad_reg1_shift                                           (0)
#define MSC_DEVCAP13_scratchpad_reg1_mask                                            (0xFFFFFFFF)
#define MSC_DEVCAP13_scratchpad_reg1(data)                                           (0xFFFFFFFF&((data)<<0))
#define MSC_DEVCAP13_scratchpad_reg1_src(data)                                       ((0xFFFFFFFF&(data))>>0)
#define MSC_DEVCAP13_get_scratchpad_reg1(data)                                       ((0xFFFFFFFF&(data))>>0)


#define MSC_DEVCAP14                                                                 0x98037C38
#define MSC_DEVCAP14_reg_addr                                                        "0x98037C38"
#define MSC_DEVCAP14_reg                                                             0x98037C38
#define set_MSC_DEVCAP14_reg(data)   (*((volatile unsigned int*) MSC_DEVCAP14_reg)=data)
#define get_MSC_DEVCAP14_reg   (*((volatile unsigned int*) MSC_DEVCAP14_reg))
#define MSC_DEVCAP14_inst_adr                                                        "0x004E"
#define MSC_DEVCAP14_inst                                                            0x004E
#define MSC_DEVCAP14_scratchpad_reg2_shift                                           (0)
#define MSC_DEVCAP14_scratchpad_reg2_mask                                            (0xFFFFFFFF)
#define MSC_DEVCAP14_scratchpad_reg2(data)                                           (0xFFFFFFFF&((data)<<0))
#define MSC_DEVCAP14_scratchpad_reg2_src(data)                                       ((0xFFFFFFFF&(data))>>0)
#define MSC_DEVCAP14_get_scratchpad_reg2(data)                                       ((0xFFFFFFFF&(data))>>0)


#define MSC_DEVCAP15                                                                 0x98037C3C
#define MSC_DEVCAP15_reg_addr                                                        "0x98037C3C"
#define MSC_DEVCAP15_reg                                                             0x98037C3C
#define set_MSC_DEVCAP15_reg(data)   (*((volatile unsigned int*) MSC_DEVCAP15_reg)=data)
#define get_MSC_DEVCAP15_reg   (*((volatile unsigned int*) MSC_DEVCAP15_reg))
#define MSC_DEVCAP15_inst_adr                                                        "0x004F"
#define MSC_DEVCAP15_inst                                                            0x004F
#define MSC_DEVCAP15_scratchpad_reg3_shift                                           (0)
#define MSC_DEVCAP15_scratchpad_reg3_mask                                            (0xFFFFFFFF)
#define MSC_DEVCAP15_scratchpad_reg3(data)                                           (0xFFFFFFFF&((data)<<0))
#define MSC_DEVCAP15_scratchpad_reg3_src(data)                                       ((0xFFFFFFFF&(data))>>0)
#define MSC_DEVCAP15_get_scratchpad_reg3(data)                                       ((0xFFFFFFFF&(data))>>0)


#define MSC_DEVCAP16                                                                 0x98037C40
#define MSC_DEVCAP16_reg_addr                                                        "0x98037C40"
#define MSC_DEVCAP16_reg                                                             0x98037C40
#define set_MSC_DEVCAP16_reg(data)   (*((volatile unsigned int*) MSC_DEVCAP16_reg)=data)
#define get_MSC_DEVCAP16_reg   (*((volatile unsigned int*) MSC_DEVCAP16_reg))
#define MSC_DEVCAP16_inst_adr                                                        "0x0050"
#define MSC_DEVCAP16_inst                                                            0x0050
#define MSC_DEVCAP16_scratchpad_reg4_shift                                           (0)
#define MSC_DEVCAP16_scratchpad_reg4_mask                                            (0xFFFFFFFF)
#define MSC_DEVCAP16_scratchpad_reg4(data)                                           (0xFFFFFFFF&((data)<<0))
#define MSC_DEVCAP16_scratchpad_reg4_src(data)                                       ((0xFFFFFFFF&(data))>>0)
#define MSC_DEVCAP16_get_scratchpad_reg4(data)                                       ((0xFFFFFFFF&(data))>>0)


#define MSC_DEVCAP17                                                                 0x98037C44
#define MSC_DEVCAP17_reg_addr                                                        "0x98037C44"
#define MSC_DEVCAP17_reg                                                             0x98037C44
#define set_MSC_DEVCAP17_reg(data)   (*((volatile unsigned int*) MSC_DEVCAP17_reg)=data)
#define get_MSC_DEVCAP17_reg   (*((volatile unsigned int*) MSC_DEVCAP17_reg))
#define MSC_DEVCAP17_inst_adr                                                        "0x0051"
#define MSC_DEVCAP17_inst                                                            0x0051
#define MSC_DEVCAP17_scratchpad_reg5_shift                                           (0)
#define MSC_DEVCAP17_scratchpad_reg5_mask                                            (0xFFFFFFFF)
#define MSC_DEVCAP17_scratchpad_reg5(data)                                           (0xFFFFFFFF&((data)<<0))
#define MSC_DEVCAP17_scratchpad_reg5_src(data)                                       ((0xFFFFFFFF&(data))>>0)
#define MSC_DEVCAP17_get_scratchpad_reg5(data)                                       ((0xFFFFFFFF&(data))>>0)


#define MSC_DEVCAP18                                                                 0x98037C48
#define MSC_DEVCAP18_reg_addr                                                        "0x98037C48"
#define MSC_DEVCAP18_reg                                                             0x98037C48
#define set_MSC_DEVCAP18_reg(data)   (*((volatile unsigned int*) MSC_DEVCAP18_reg)=data)
#define get_MSC_DEVCAP18_reg   (*((volatile unsigned int*) MSC_DEVCAP18_reg))
#define MSC_DEVCAP18_inst_adr                                                        "0x0052"
#define MSC_DEVCAP18_inst                                                            0x0052
#define MSC_DEVCAP18_scratchpad_reg6_shift                                           (0)
#define MSC_DEVCAP18_scratchpad_reg6_mask                                            (0xFFFFFFFF)
#define MSC_DEVCAP18_scratchpad_reg6(data)                                           (0xFFFFFFFF&((data)<<0))
#define MSC_DEVCAP18_scratchpad_reg6_src(data)                                       ((0xFFFFFFFF&(data))>>0)
#define MSC_DEVCAP18_get_scratchpad_reg6(data)                                       ((0xFFFFFFFF&(data))>>0)


#define MSC_DEVCAP19                                                                 0x98037C4C
#define MSC_DEVCAP19_reg_addr                                                        "0x98037C4C"
#define MSC_DEVCAP19_reg                                                             0x98037C4C
#define set_MSC_DEVCAP19_reg(data)   (*((volatile unsigned int*) MSC_DEVCAP19_reg)=data)
#define get_MSC_DEVCAP19_reg   (*((volatile unsigned int*) MSC_DEVCAP19_reg))
#define MSC_DEVCAP19_inst_adr                                                        "0x0053"
#define MSC_DEVCAP19_inst                                                            0x0053
#define MSC_DEVCAP19_scratchpad_reg7_shift                                           (0)
#define MSC_DEVCAP19_scratchpad_reg7_mask                                            (0xFFFFFFFF)
#define MSC_DEVCAP19_scratchpad_reg7(data)                                           (0xFFFFFFFF&((data)<<0))
#define MSC_DEVCAP19_scratchpad_reg7_src(data)                                       ((0xFFFFFFFF&(data))>>0)
#define MSC_DEVCAP19_get_scratchpad_reg7(data)                                       ((0xFFFFFFFF&(data))>>0)


#endif
