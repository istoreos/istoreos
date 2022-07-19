/**************************************************************
// Spec Version                  : 0.6
// Parser Version                : DVR_Parser_6.11(120105)
// CModelGen Version             : 5.1 2012.01.05
// Naming Rule                   :  Module_Register_Name
// Naming Rule                   : Module_Register_Name
// Parse Option                  : Only Parse _op1
// Parse Address Region          : All Address Region 
// Decode bit number             : 12 bits
// Firmware Header Generate Date : 2015/7/15 20:39:21
***************************************************************/


#ifndef _SATA_REG_H_INCLUDED_
#define _SATA_REG_H_INCLUDED_
#ifdef  _SATA_USE_STRUCT
typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     Mbist_sata_st:1;
unsigned int     cp_pod1:1;
unsigned int     cp_pod0:1;
unsigned int     pme_req:1;
unsigned int     sata_mac_int:1;
}SATA_SATA_MAC_IN;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     sata_phy_rst_force:1;
unsigned int     sata_phy_rstn:2;
}SATA_SATA_FORCE_RST;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     sata_ls_en:1;
unsigned int     sata_clk_gate_en:1;
}SATA_SATA_SAVE;

typedef struct 
{
unsigned int     reserved_0:14;
unsigned int     rx_error_CDR_sel:2;
unsigned int     rx_error_sel:2;
unsigned int     clk_mode_sel_1:2;
unsigned int     clk_mode_sel_0:2;
unsigned int     ckbuf_en1:1;
unsigned int     ckbuf_en0:1;
unsigned int     mp_switch1:1;
unsigned int     mp_switch0:1;
unsigned int     cp_det1:1;
unsigned int     cp_det0:1;
unsigned int     phy_rx_err_1:1;
unsigned int     phy_rx_err_0:1;
unsigned int     phy_iprx_en_1:1;
unsigned int     phy_iprx_en_0:1;
}SATA_SATA_CTR;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     phy_rdy_1:1;
unsigned int     phy_rdy_0:1;
unsigned int     phy_calibrated_1:1;
unsigned int     phy_calibrated_0:1;
}SATA_SATA_PHY_MON;

typedef struct 
{
unsigned int     reserved_0:14;
unsigned int     rdata_in_order:1;
unsigned int     wcmd_bufable_sel:1;
unsigned int     reserved_1:4;
unsigned int     outstd_wcmd:4;
unsigned int     reserved_2:3;
unsigned int     outstd_rcmd:5;
}SATA_SATA_WRAPPER_DMA_CTRL;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     dbus2_remote_cmd_num:4;
unsigned int     reserved_1:4;
unsigned int     dbus_remote_cmd_num:4;
unsigned int     reserved_2:2;
unsigned int     dbus2_remote_wdata_num:6;
unsigned int     reserved_3:2;
unsigned int     dbus_remote_wdata_num:6;
}SATA_SATA_WRAPPER_DC_CTRL;

typedef struct 
{
unsigned int     reserved_0:19;
unsigned int     dbg_sel1:6;
unsigned int     dbg_sel0:6;
unsigned int     dbg_en:1;
}SATA_SATA_DBG;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     sram_debug_sel:1;
unsigned int     sram_debug_mode:1;
}SATA_WRAP_CTR;

typedef struct 
{
unsigned int     data:16;
unsigned int     phy_addr:2;
unsigned int     phy_reg_addr:6;
unsigned int     mdio_busy:1;
unsigned int     mdio_st:2;
unsigned int     mdio_rdy:1;
unsigned int     mclk_rate:2;
unsigned int     mdio_srst:1;
unsigned int     mdio_rdwr:1;
}SATA_MDIO_CTR;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     phy_sel:1;
}SATA_MDIO_CTR1;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     p1_spd_mode_st:2;
unsigned int     p0_spd_mode_st:2;
unsigned int     p1_spd_mode:2;
unsigned int     p0_spd_mode:2;
}SATA_SPD;

typedef struct 
{
unsigned int     reserved_0:15;
unsigned int     done_st:1;
unsigned int     reserved_1:15;
unsigned int     go_ct:1;
}SATA_RAM_CTR;

typedef struct 
{
unsigned int     sram_addr:32;
}SATA_RAM_ADDR;

typedef struct 
{
unsigned int     ram_wdata:32;
}SATA_RAM_WDATA;

typedef struct 
{
unsigned int     ram_rdata:32;
}SATA_RAM_RDATA;

typedef struct 
{
unsigned int     p0_csr_diagnr:32;
}SATA_SATA_MAC_P0_DBG0;

typedef struct 
{
unsigned int     p0_csr_diagnr1:32;
}SATA_SATA_MAC_P0_DBG1;

typedef struct 
{
unsigned int     p0_csr_is:32;
}SATA_SATA_MAC_P0_DBG2;

typedef struct 
{
unsigned int     p0_csr_cmd:32;
}SATA_SATA_MAC_P0_DBG3;

typedef struct 
{
unsigned int     p1_csr_diagnr:32;
}SATA_SATA_MAC_P1_DBG0;

typedef struct 
{
unsigned int     p1_csr_diagnr1:32;
}SATA_SATA_MAC_P1_DBG1;

typedef struct 
{
unsigned int     p1_csr_is:32;
}SATA_SATA_MAC_P1_DBG2;

typedef struct 
{
unsigned int     p1_csr_cmd:32;
}SATA_SATA_MAC_P1_DBG3;

typedef struct 
{
unsigned int     reserved_0:26;
unsigned int     p0_rx_error:1;
unsigned int     p0_link_state:5;
}SATA_SATA_MAC_P0_DBG4;

typedef struct 
{
unsigned int     reserved_0:26;
unsigned int     p1_rx_error:1;
unsigned int     p1_link_state:5;
}SATA_SATA_MAC_P1_DBG4;

typedef struct 
{
unsigned int     reserved_0:15;
unsigned int     sata_bist1_ls10:2;
unsigned int     sata_bist1_rm_1:4;
unsigned int     sata_bist1_rme_1:1;
unsigned int     sata_bist1_rm_0:4;
unsigned int     sata_bist1_rme_0:1;
unsigned int     sata_drf_1_test_resume:1;
unsigned int     sata_drf_bist1_en:1;
unsigned int     sata_bist1_en:1;
unsigned int     sata_bist1_rstn:1;
unsigned int     sata_bist1_test_mode:1;
}SATA_SATA_BIST1_CTRL;

typedef struct 
{
unsigned int     reserved_0:21;
unsigned int     sata_bist2_ls50:6;
unsigned int     sata_drf_2_test_resume:1;
unsigned int     sata_drf_bist2_en:1;
unsigned int     sata_bist2_en:1;
unsigned int     sata_bist2_rstn:1;
unsigned int     sata_bist2_test_mode:1;
}SATA_SATA_BIST2_CTRL;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     sata_bist2_rm_5:4;
unsigned int     sata_bist2_rme_5:1;
unsigned int     sata_bist2_rm_4:4;
unsigned int     sata_bist2_rme_4:1;
unsigned int     sata_bist2_rm_3:4;
unsigned int     sata_bist2_rme_3:1;
unsigned int     sata_bist2_rm_2:4;
unsigned int     sata_bist2_rme_2:1;
unsigned int     sata_bist2_rm_1:4;
unsigned int     sata_bist2_rme_1:1;
unsigned int     sata_bist2_rm_0:4;
unsigned int     sata_bist2_rme_0:1;
}SATA_SATA_BIST2_CTRL1;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     sata_drf_bist1_fail_1:1;
unsigned int     sata_bist1_fail_1:1;
unsigned int     sata_drf_bist1_fail_0:1;
unsigned int     sata_bist1_fail_0:1;
unsigned int     sata_drf_1_start_pause:1;
unsigned int     sata_drf_bist1_done:1;
unsigned int     sata_bist1_done:1;
}SATA_SATA_BIST1_STS;

typedef struct 
{
unsigned int     reserved_0:17;
unsigned int     sata_drf_bist2_fail_5:1;
unsigned int     sata_bist2_fail_5:1;
unsigned int     sata_drf_bist2_fail_4:1;
unsigned int     sata_bist2_fail_4:1;
unsigned int     sata_drf_bist2_fail_3:1;
unsigned int     sata_bist2_fail_3:1;
unsigned int     sata_drf_bist2_fail_2:1;
unsigned int     sata_bist2_fail_2:1;
unsigned int     sata_drf_bist2_fail_1:1;
unsigned int     sata_bist2_fail_1:1;
unsigned int     sata_drf_bist2_fail_0:1;
unsigned int     sata_bist2_fail_0:1;
unsigned int     sata_drf_2_start_pause:1;
unsigned int     sata_drf_bist2_done:1;
unsigned int     sata_bist2_done:1;
}SATA_SATA_BIST2_STS;

typedef struct 
{
unsigned int     dummy_0:32;
}SATA_SATA_DUMMY_0_REG;

typedef struct 
{
unsigned int     dummy_1:32;
}SATA_SATA_DUMMY_1_REG;

#endif

#define SATA_SATA_MAC_IN                                                             0x9803FF00
#define SATA_SATA_MAC_IN_reg_addr                                                    "0xD803FF00"
#define SATA_SATA_MAC_IN_reg                                                         0xD803FF00
#define set_SATA_SATA_MAC_IN_reg(data)   (*((volatile unsigned int*) SATA_SATA_MAC_IN_reg)=data)
#define get_SATA_SATA_MAC_IN_reg   (*((volatile unsigned int*) SATA_SATA_MAC_IN_reg))
#define SATA_SATA_MAC_IN_inst_adr                                                    "0x00C0"
#define SATA_SATA_MAC_IN_inst                                                        0x00C0
#define SATA_SATA_MAC_IN_Mbist_sata_st_shift                                         (4)
#define SATA_SATA_MAC_IN_Mbist_sata_st_mask                                          (0x00000010)
#define SATA_SATA_MAC_IN_Mbist_sata_st(data)                                         (0x00000010&((data)<<4))
#define SATA_SATA_MAC_IN_Mbist_sata_st_src(data)                                     ((0x00000010&(data))>>4)
#define SATA_SATA_MAC_IN_get_Mbist_sata_st(data)                                     ((0x00000010&(data))>>4)
#define SATA_SATA_MAC_IN_cp_pod1_shift                                               (3)
#define SATA_SATA_MAC_IN_cp_pod1_mask                                                (0x00000008)
#define SATA_SATA_MAC_IN_cp_pod1(data)                                               (0x00000008&((data)<<3))
#define SATA_SATA_MAC_IN_cp_pod1_src(data)                                           ((0x00000008&(data))>>3)
#define SATA_SATA_MAC_IN_get_cp_pod1(data)                                           ((0x00000008&(data))>>3)
#define SATA_SATA_MAC_IN_cp_pod0_shift                                               (2)
#define SATA_SATA_MAC_IN_cp_pod0_mask                                                (0x00000004)
#define SATA_SATA_MAC_IN_cp_pod0(data)                                               (0x00000004&((data)<<2))
#define SATA_SATA_MAC_IN_cp_pod0_src(data)                                           ((0x00000004&(data))>>2)
#define SATA_SATA_MAC_IN_get_cp_pod0(data)                                           ((0x00000004&(data))>>2)
#define SATA_SATA_MAC_IN_pme_req_shift                                               (1)
#define SATA_SATA_MAC_IN_pme_req_mask                                                (0x00000002)
#define SATA_SATA_MAC_IN_pme_req(data)                                               (0x00000002&((data)<<1))
#define SATA_SATA_MAC_IN_pme_req_src(data)                                           ((0x00000002&(data))>>1)
#define SATA_SATA_MAC_IN_get_pme_req(data)                                           ((0x00000002&(data))>>1)
#define SATA_SATA_MAC_IN_sata_mac_int_shift                                          (0)
#define SATA_SATA_MAC_IN_sata_mac_int_mask                                           (0x00000001)
#define SATA_SATA_MAC_IN_sata_mac_int(data)                                          (0x00000001&((data)<<0))
#define SATA_SATA_MAC_IN_sata_mac_int_src(data)                                      ((0x00000001&(data))>>0)
#define SATA_SATA_MAC_IN_get_sata_mac_int(data)                                      ((0x00000001&(data))>>0)


#define SATA_SATA_FORCE_RST                                                          0x9803FF10
#define SATA_SATA_FORCE_RST_reg_addr                                                 "0xD803FF10"
#define SATA_SATA_FORCE_RST_reg                                                      0xD803FF10
#define set_SATA_SATA_FORCE_RST_reg(data)   (*((volatile unsigned int*) SATA_SATA_FORCE_RST_reg)=data)
#define get_SATA_SATA_FORCE_RST_reg   (*((volatile unsigned int*) SATA_SATA_FORCE_RST_reg))
#define SATA_SATA_FORCE_RST_inst_adr                                                 "0x00C4"
#define SATA_SATA_FORCE_RST_inst                                                     0x00C4
#define SATA_SATA_FORCE_RST_sata_phy_rst_force_shift                                 (2)
#define SATA_SATA_FORCE_RST_sata_phy_rst_force_mask                                  (0x00000004)
#define SATA_SATA_FORCE_RST_sata_phy_rst_force(data)                                 (0x00000004&((data)<<2))
#define SATA_SATA_FORCE_RST_sata_phy_rst_force_src(data)                             ((0x00000004&(data))>>2)
#define SATA_SATA_FORCE_RST_get_sata_phy_rst_force(data)                             ((0x00000004&(data))>>2)
#define SATA_SATA_FORCE_RST_sata_phy_rstn_shift                                      (0)
#define SATA_SATA_FORCE_RST_sata_phy_rstn_mask                                       (0x00000003)
#define SATA_SATA_FORCE_RST_sata_phy_rstn(data)                                      (0x00000003&((data)<<0))
#define SATA_SATA_FORCE_RST_sata_phy_rstn_src(data)                                  ((0x00000003&(data))>>0)
#define SATA_SATA_FORCE_RST_get_sata_phy_rstn(data)                                  ((0x00000003&(data))>>0)


#define SATA_SATA_SAVE                                                               0x9803FF14
#define SATA_SATA_SAVE_reg_addr                                                      "0xD803FF14"
#define SATA_SATA_SAVE_reg                                                           0xD803FF14
#define set_SATA_SATA_SAVE_reg(data)   (*((volatile unsigned int*) SATA_SATA_SAVE_reg)=data)
#define get_SATA_SATA_SAVE_reg   (*((volatile unsigned int*) SATA_SATA_SAVE_reg))
#define SATA_SATA_SAVE_inst_adr                                                      "0x00C5"
#define SATA_SATA_SAVE_inst                                                          0x00C5
#define SATA_SATA_SAVE_sata_ls_en_shift                                              (1)
#define SATA_SATA_SAVE_sata_ls_en_mask                                               (0x00000002)
#define SATA_SATA_SAVE_sata_ls_en(data)                                              (0x00000002&((data)<<1))
#define SATA_SATA_SAVE_sata_ls_en_src(data)                                          ((0x00000002&(data))>>1)
#define SATA_SATA_SAVE_get_sata_ls_en(data)                                          ((0x00000002&(data))>>1)
#define SATA_SATA_SAVE_sata_clk_gate_en_shift                                        (0)
#define SATA_SATA_SAVE_sata_clk_gate_en_mask                                         (0x00000001)
#define SATA_SATA_SAVE_sata_clk_gate_en(data)                                        (0x00000001&((data)<<0))
#define SATA_SATA_SAVE_sata_clk_gate_en_src(data)                                    ((0x00000001&(data))>>0)
#define SATA_SATA_SAVE_get_sata_clk_gate_en(data)                                    ((0x00000001&(data))>>0)


#define SATA_SATA_CTR                                                                0x9803FF20
#define SATA_SATA_CTR_reg_addr                                                       "0xD803FF20"
#define SATA_SATA_CTR_reg                                                            0xD803FF20
#define set_SATA_SATA_CTR_reg(data)   (*((volatile unsigned int*) SATA_SATA_CTR_reg)=data)
#define get_SATA_SATA_CTR_reg   (*((volatile unsigned int*) SATA_SATA_CTR_reg))
#define SATA_SATA_CTR_inst_adr                                                       "0x00C8"
#define SATA_SATA_CTR_inst                                                           0x00C8
#define SATA_SATA_CTR_rx_error_CDR_sel_shift                                         (16)
#define SATA_SATA_CTR_rx_error_CDR_sel_mask                                          (0x00030000)
#define SATA_SATA_CTR_rx_error_CDR_sel(data)                                         (0x00030000&((data)<<16))
#define SATA_SATA_CTR_rx_error_CDR_sel_src(data)                                     ((0x00030000&(data))>>16)
#define SATA_SATA_CTR_get_rx_error_CDR_sel(data)                                     ((0x00030000&(data))>>16)
#define SATA_SATA_CTR_rx_error_sel_shift                                             (14)
#define SATA_SATA_CTR_rx_error_sel_mask                                              (0x0000C000)
#define SATA_SATA_CTR_rx_error_sel(data)                                             (0x0000C000&((data)<<14))
#define SATA_SATA_CTR_rx_error_sel_src(data)                                         ((0x0000C000&(data))>>14)
#define SATA_SATA_CTR_get_rx_error_sel(data)                                         ((0x0000C000&(data))>>14)
#define SATA_SATA_CTR_clk_mode_sel_1_shift                                           (12)
#define SATA_SATA_CTR_clk_mode_sel_1_mask                                            (0x00003000)
#define SATA_SATA_CTR_clk_mode_sel_1(data)                                           (0x00003000&((data)<<12))
#define SATA_SATA_CTR_clk_mode_sel_1_src(data)                                       ((0x00003000&(data))>>12)
#define SATA_SATA_CTR_get_clk_mode_sel_1(data)                                       ((0x00003000&(data))>>12)
#define SATA_SATA_CTR_clk_mode_sel_0_shift                                           (10)
#define SATA_SATA_CTR_clk_mode_sel_0_mask                                            (0x00000C00)
#define SATA_SATA_CTR_clk_mode_sel_0(data)                                           (0x00000C00&((data)<<10))
#define SATA_SATA_CTR_clk_mode_sel_0_src(data)                                       ((0x00000C00&(data))>>10)
#define SATA_SATA_CTR_get_clk_mode_sel_0(data)                                       ((0x00000C00&(data))>>10)
#define SATA_SATA_CTR_ckbuf_en1_shift                                                (9)
#define SATA_SATA_CTR_ckbuf_en1_mask                                                 (0x00000200)
#define SATA_SATA_CTR_ckbuf_en1(data)                                                (0x00000200&((data)<<9))
#define SATA_SATA_CTR_ckbuf_en1_src(data)                                            ((0x00000200&(data))>>9)
#define SATA_SATA_CTR_get_ckbuf_en1(data)                                            ((0x00000200&(data))>>9)
#define SATA_SATA_CTR_ckbuf_en0_shift                                                (8)
#define SATA_SATA_CTR_ckbuf_en0_mask                                                 (0x00000100)
#define SATA_SATA_CTR_ckbuf_en0(data)                                                (0x00000100&((data)<<8))
#define SATA_SATA_CTR_ckbuf_en0_src(data)                                            ((0x00000100&(data))>>8)
#define SATA_SATA_CTR_get_ckbuf_en0(data)                                            ((0x00000100&(data))>>8)
#define SATA_SATA_CTR_mp_switch1_shift                                               (7)
#define SATA_SATA_CTR_mp_switch1_mask                                                (0x00000080)
#define SATA_SATA_CTR_mp_switch1(data)                                               (0x00000080&((data)<<7))
#define SATA_SATA_CTR_mp_switch1_src(data)                                           ((0x00000080&(data))>>7)
#define SATA_SATA_CTR_get_mp_switch1(data)                                           ((0x00000080&(data))>>7)
#define SATA_SATA_CTR_mp_switch0_shift                                               (6)
#define SATA_SATA_CTR_mp_switch0_mask                                                (0x00000040)
#define SATA_SATA_CTR_mp_switch0(data)                                               (0x00000040&((data)<<6))
#define SATA_SATA_CTR_mp_switch0_src(data)                                           ((0x00000040&(data))>>6)
#define SATA_SATA_CTR_get_mp_switch0(data)                                           ((0x00000040&(data))>>6)
#define SATA_SATA_CTR_cp_det1_shift                                                  (5)
#define SATA_SATA_CTR_cp_det1_mask                                                   (0x00000020)
#define SATA_SATA_CTR_cp_det1(data)                                                  (0x00000020&((data)<<5))
#define SATA_SATA_CTR_cp_det1_src(data)                                              ((0x00000020&(data))>>5)
#define SATA_SATA_CTR_get_cp_det1(data)                                              ((0x00000020&(data))>>5)
#define SATA_SATA_CTR_cp_det0_shift                                                  (4)
#define SATA_SATA_CTR_cp_det0_mask                                                   (0x00000010)
#define SATA_SATA_CTR_cp_det0(data)                                                  (0x00000010&((data)<<4))
#define SATA_SATA_CTR_cp_det0_src(data)                                              ((0x00000010&(data))>>4)
#define SATA_SATA_CTR_get_cp_det0(data)                                              ((0x00000010&(data))>>4)
#define SATA_SATA_CTR_phy_rx_err_1_shift                                             (3)
#define SATA_SATA_CTR_phy_rx_err_1_mask                                              (0x00000008)
#define SATA_SATA_CTR_phy_rx_err_1(data)                                             (0x00000008&((data)<<3))
#define SATA_SATA_CTR_phy_rx_err_1_src(data)                                         ((0x00000008&(data))>>3)
#define SATA_SATA_CTR_get_phy_rx_err_1(data)                                         ((0x00000008&(data))>>3)
#define SATA_SATA_CTR_phy_rx_err_0_shift                                             (2)
#define SATA_SATA_CTR_phy_rx_err_0_mask                                              (0x00000004)
#define SATA_SATA_CTR_phy_rx_err_0(data)                                             (0x00000004&((data)<<2))
#define SATA_SATA_CTR_phy_rx_err_0_src(data)                                         ((0x00000004&(data))>>2)
#define SATA_SATA_CTR_get_phy_rx_err_0(data)                                         ((0x00000004&(data))>>2)
#define SATA_SATA_CTR_phy_iprx_en_1_shift                                            (1)
#define SATA_SATA_CTR_phy_iprx_en_1_mask                                             (0x00000002)
#define SATA_SATA_CTR_phy_iprx_en_1(data)                                            (0x00000002&((data)<<1))
#define SATA_SATA_CTR_phy_iprx_en_1_src(data)                                        ((0x00000002&(data))>>1)
#define SATA_SATA_CTR_get_phy_iprx_en_1(data)                                        ((0x00000002&(data))>>1)
#define SATA_SATA_CTR_phy_iprx_en_0_shift                                            (0)
#define SATA_SATA_CTR_phy_iprx_en_0_mask                                             (0x00000001)
#define SATA_SATA_CTR_phy_iprx_en_0(data)                                            (0x00000001&((data)<<0))
#define SATA_SATA_CTR_phy_iprx_en_0_src(data)                                        ((0x00000001&(data))>>0)
#define SATA_SATA_CTR_get_phy_iprx_en_0(data)                                        ((0x00000001&(data))>>0)


#define SATA_SATA_PHY_MON                                                            0x9803FF24
#define SATA_SATA_PHY_MON_reg_addr                                                   "0xD803FF24"
#define SATA_SATA_PHY_MON_reg                                                        0xD803FF24
#define set_SATA_SATA_PHY_MON_reg(data)   (*((volatile unsigned int*) SATA_SATA_PHY_MON_reg)=data)
#define get_SATA_SATA_PHY_MON_reg   (*((volatile unsigned int*) SATA_SATA_PHY_MON_reg))
#define SATA_SATA_PHY_MON_inst_adr                                                   "0x00C9"
#define SATA_SATA_PHY_MON_inst                                                       0x00C9
#define SATA_SATA_PHY_MON_phy_rdy_1_shift                                            (3)
#define SATA_SATA_PHY_MON_phy_rdy_1_mask                                             (0x00000008)
#define SATA_SATA_PHY_MON_phy_rdy_1(data)                                            (0x00000008&((data)<<3))
#define SATA_SATA_PHY_MON_phy_rdy_1_src(data)                                        ((0x00000008&(data))>>3)
#define SATA_SATA_PHY_MON_get_phy_rdy_1(data)                                        ((0x00000008&(data))>>3)
#define SATA_SATA_PHY_MON_phy_rdy_0_shift                                            (2)
#define SATA_SATA_PHY_MON_phy_rdy_0_mask                                             (0x00000004)
#define SATA_SATA_PHY_MON_phy_rdy_0(data)                                            (0x00000004&((data)<<2))
#define SATA_SATA_PHY_MON_phy_rdy_0_src(data)                                        ((0x00000004&(data))>>2)
#define SATA_SATA_PHY_MON_get_phy_rdy_0(data)                                        ((0x00000004&(data))>>2)
#define SATA_SATA_PHY_MON_phy_calibrated_1_shift                                     (1)
#define SATA_SATA_PHY_MON_phy_calibrated_1_mask                                      (0x00000002)
#define SATA_SATA_PHY_MON_phy_calibrated_1(data)                                     (0x00000002&((data)<<1))
#define SATA_SATA_PHY_MON_phy_calibrated_1_src(data)                                 ((0x00000002&(data))>>1)
#define SATA_SATA_PHY_MON_get_phy_calibrated_1(data)                                 ((0x00000002&(data))>>1)
#define SATA_SATA_PHY_MON_phy_calibrated_0_shift                                     (0)
#define SATA_SATA_PHY_MON_phy_calibrated_0_mask                                      (0x00000001)
#define SATA_SATA_PHY_MON_phy_calibrated_0(data)                                     (0x00000001&((data)<<0))
#define SATA_SATA_PHY_MON_phy_calibrated_0_src(data)                                 ((0x00000001&(data))>>0)
#define SATA_SATA_PHY_MON_get_phy_calibrated_0(data)                                 ((0x00000001&(data))>>0)


#define SATA_SATA_WRAPPER_DMA_CTRL                                                   0x9803FF30
#define SATA_SATA_WRAPPER_DMA_CTRL_reg_addr                                          "0xD803FF30"
#define SATA_SATA_WRAPPER_DMA_CTRL_reg                                               0xD803FF30
#define set_SATA_SATA_WRAPPER_DMA_CTRL_reg(data)   (*((volatile unsigned int*) SATA_SATA_WRAPPER_DMA_CTRL_reg)=data)
#define get_SATA_SATA_WRAPPER_DMA_CTRL_reg   (*((volatile unsigned int*) SATA_SATA_WRAPPER_DMA_CTRL_reg))
#define SATA_SATA_WRAPPER_DMA_CTRL_inst_adr                                          "0x00CC"
#define SATA_SATA_WRAPPER_DMA_CTRL_inst                                              0x00CC
#define SATA_SATA_WRAPPER_DMA_CTRL_rdata_in_order_shift                              (17)
#define SATA_SATA_WRAPPER_DMA_CTRL_rdata_in_order_mask                               (0x00020000)
#define SATA_SATA_WRAPPER_DMA_CTRL_rdata_in_order(data)                              (0x00020000&((data)<<17))
#define SATA_SATA_WRAPPER_DMA_CTRL_rdata_in_order_src(data)                          ((0x00020000&(data))>>17)
#define SATA_SATA_WRAPPER_DMA_CTRL_get_rdata_in_order(data)                          ((0x00020000&(data))>>17)
#define SATA_SATA_WRAPPER_DMA_CTRL_wcmd_bufable_sel_shift                            (16)
#define SATA_SATA_WRAPPER_DMA_CTRL_wcmd_bufable_sel_mask                             (0x00010000)
#define SATA_SATA_WRAPPER_DMA_CTRL_wcmd_bufable_sel(data)                            (0x00010000&((data)<<16))
#define SATA_SATA_WRAPPER_DMA_CTRL_wcmd_bufable_sel_src(data)                        ((0x00010000&(data))>>16)
#define SATA_SATA_WRAPPER_DMA_CTRL_get_wcmd_bufable_sel(data)                        ((0x00010000&(data))>>16)
#define SATA_SATA_WRAPPER_DMA_CTRL_outstd_wcmd_shift                                 (8)
#define SATA_SATA_WRAPPER_DMA_CTRL_outstd_wcmd_mask                                  (0x00000F00)
#define SATA_SATA_WRAPPER_DMA_CTRL_outstd_wcmd(data)                                 (0x00000F00&((data)<<8))
#define SATA_SATA_WRAPPER_DMA_CTRL_outstd_wcmd_src(data)                             ((0x00000F00&(data))>>8)
#define SATA_SATA_WRAPPER_DMA_CTRL_get_outstd_wcmd(data)                             ((0x00000F00&(data))>>8)
#define SATA_SATA_WRAPPER_DMA_CTRL_outstd_rcmd_shift                                 (0)
#define SATA_SATA_WRAPPER_DMA_CTRL_outstd_rcmd_mask                                  (0x0000001F)
#define SATA_SATA_WRAPPER_DMA_CTRL_outstd_rcmd(data)                                 (0x0000001F&((data)<<0))
#define SATA_SATA_WRAPPER_DMA_CTRL_outstd_rcmd_src(data)                             ((0x0000001F&(data))>>0)
#define SATA_SATA_WRAPPER_DMA_CTRL_get_outstd_rcmd(data)                             ((0x0000001F&(data))>>0)


#define SATA_SATA_WRAPPER_DC_CTRL                                                    0x9803FF34
#define SATA_SATA_WRAPPER_DC_CTRL_reg_addr                                           "0xD803FF34"
#define SATA_SATA_WRAPPER_DC_CTRL_reg                                                0xD803FF34
#define set_SATA_SATA_WRAPPER_DC_CTRL_reg(data)   (*((volatile unsigned int*) SATA_SATA_WRAPPER_DC_CTRL_reg)=data)
#define get_SATA_SATA_WRAPPER_DC_CTRL_reg   (*((volatile unsigned int*) SATA_SATA_WRAPPER_DC_CTRL_reg))
#define SATA_SATA_WRAPPER_DC_CTRL_inst_adr                                           "0x00CD"
#define SATA_SATA_WRAPPER_DC_CTRL_inst                                               0x00CD
#define SATA_SATA_WRAPPER_DC_CTRL_dbus2_remote_cmd_num_shift                         (24)
#define SATA_SATA_WRAPPER_DC_CTRL_dbus2_remote_cmd_num_mask                          (0x0F000000)
#define SATA_SATA_WRAPPER_DC_CTRL_dbus2_remote_cmd_num(data)                         (0x0F000000&((data)<<24))
#define SATA_SATA_WRAPPER_DC_CTRL_dbus2_remote_cmd_num_src(data)                     ((0x0F000000&(data))>>24)
#define SATA_SATA_WRAPPER_DC_CTRL_get_dbus2_remote_cmd_num(data)                     ((0x0F000000&(data))>>24)
#define SATA_SATA_WRAPPER_DC_CTRL_dbus_remote_cmd_num_shift                          (16)
#define SATA_SATA_WRAPPER_DC_CTRL_dbus_remote_cmd_num_mask                           (0x000F0000)
#define SATA_SATA_WRAPPER_DC_CTRL_dbus_remote_cmd_num(data)                          (0x000F0000&((data)<<16))
#define SATA_SATA_WRAPPER_DC_CTRL_dbus_remote_cmd_num_src(data)                      ((0x000F0000&(data))>>16)
#define SATA_SATA_WRAPPER_DC_CTRL_get_dbus_remote_cmd_num(data)                      ((0x000F0000&(data))>>16)
#define SATA_SATA_WRAPPER_DC_CTRL_dbus2_remote_wdata_num_shift                       (8)
#define SATA_SATA_WRAPPER_DC_CTRL_dbus2_remote_wdata_num_mask                        (0x00003F00)
#define SATA_SATA_WRAPPER_DC_CTRL_dbus2_remote_wdata_num(data)                       (0x00003F00&((data)<<8))
#define SATA_SATA_WRAPPER_DC_CTRL_dbus2_remote_wdata_num_src(data)                   ((0x00003F00&(data))>>8)
#define SATA_SATA_WRAPPER_DC_CTRL_get_dbus2_remote_wdata_num(data)                   ((0x00003F00&(data))>>8)
#define SATA_SATA_WRAPPER_DC_CTRL_dbus_remote_wdata_num_shift                        (0)
#define SATA_SATA_WRAPPER_DC_CTRL_dbus_remote_wdata_num_mask                         (0x0000003F)
#define SATA_SATA_WRAPPER_DC_CTRL_dbus_remote_wdata_num(data)                        (0x0000003F&((data)<<0))
#define SATA_SATA_WRAPPER_DC_CTRL_dbus_remote_wdata_num_src(data)                    ((0x0000003F&(data))>>0)
#define SATA_SATA_WRAPPER_DC_CTRL_get_dbus_remote_wdata_num(data)                    ((0x0000003F&(data))>>0)


#define SATA_SATA_DBG                                                                0x9803FF40
#define SATA_SATA_DBG_reg_addr                                                       "0xD803FF40"
#define SATA_SATA_DBG_reg                                                            0xD803FF40
#define set_SATA_SATA_DBG_reg(data)   (*((volatile unsigned int*) SATA_SATA_DBG_reg)=data)
#define get_SATA_SATA_DBG_reg   (*((volatile unsigned int*) SATA_SATA_DBG_reg))
#define SATA_SATA_DBG_inst_adr                                                       "0x00D0"
#define SATA_SATA_DBG_inst                                                           0x00D0
#define SATA_SATA_DBG_dbg_sel1_shift                                                 (7)
#define SATA_SATA_DBG_dbg_sel1_mask                                                  (0x00001F80)
#define SATA_SATA_DBG_dbg_sel1(data)                                                 (0x00001F80&((data)<<7))
#define SATA_SATA_DBG_dbg_sel1_src(data)                                             ((0x00001F80&(data))>>7)
#define SATA_SATA_DBG_get_dbg_sel1(data)                                             ((0x00001F80&(data))>>7)
#define SATA_SATA_DBG_dbg_sel0_shift                                                 (1)
#define SATA_SATA_DBG_dbg_sel0_mask                                                  (0x0000007E)
#define SATA_SATA_DBG_dbg_sel0(data)                                                 (0x0000007E&((data)<<1))
#define SATA_SATA_DBG_dbg_sel0_src(data)                                             ((0x0000007E&(data))>>1)
#define SATA_SATA_DBG_get_dbg_sel0(data)                                             ((0x0000007E&(data))>>1)
#define SATA_SATA_DBG_dbg_en_shift                                                   (0)
#define SATA_SATA_DBG_dbg_en_mask                                                    (0x00000001)
#define SATA_SATA_DBG_dbg_en(data)                                                   (0x00000001&((data)<<0))
#define SATA_SATA_DBG_dbg_en_src(data)                                               ((0x00000001&(data))>>0)
#define SATA_SATA_DBG_get_dbg_en(data)                                               ((0x00000001&(data))>>0)


#define SATA_WRAP_CTR                                                                0x9803FF50
#define SATA_WRAP_CTR_reg_addr                                                       "0xD803FF50"
#define SATA_WRAP_CTR_reg                                                            0xD803FF50
#define set_SATA_WRAP_CTR_reg(data)   (*((volatile unsigned int*) SATA_WRAP_CTR_reg)=data)
#define get_SATA_WRAP_CTR_reg   (*((volatile unsigned int*) SATA_WRAP_CTR_reg))
#define SATA_WRAP_CTR_inst_adr                                                       "0x00D4"
#define SATA_WRAP_CTR_inst                                                           0x00D4
#define SATA_WRAP_CTR_sram_debug_sel_shift                                           (1)
#define SATA_WRAP_CTR_sram_debug_sel_mask                                            (0x00000002)
#define SATA_WRAP_CTR_sram_debug_sel(data)                                           (0x00000002&((data)<<1))
#define SATA_WRAP_CTR_sram_debug_sel_src(data)                                       ((0x00000002&(data))>>1)
#define SATA_WRAP_CTR_get_sram_debug_sel(data)                                       ((0x00000002&(data))>>1)
#define SATA_WRAP_CTR_sram_debug_mode_shift                                          (0)
#define SATA_WRAP_CTR_sram_debug_mode_mask                                           (0x00000001)
#define SATA_WRAP_CTR_sram_debug_mode(data)                                          (0x00000001&((data)<<0))
#define SATA_WRAP_CTR_sram_debug_mode_src(data)                                      ((0x00000001&(data))>>0)
#define SATA_WRAP_CTR_get_sram_debug_mode(data)                                      ((0x00000001&(data))>>0)


#define SATA_MDIO_CTR                                                                0x9803FF60
#define SATA_MDIO_CTR_reg_addr                                                       "0xD803FF60"
#define SATA_MDIO_CTR_reg                                                            0xD803FF60
#define set_SATA_MDIO_CTR_reg(data)   (*((volatile unsigned int*) SATA_MDIO_CTR_reg)=data)
#define get_SATA_MDIO_CTR_reg   (*((volatile unsigned int*) SATA_MDIO_CTR_reg))
#define SATA_MDIO_CTR_inst_adr                                                       "0x00D8"
#define SATA_MDIO_CTR_inst                                                           0x00D8
#define SATA_MDIO_CTR_data_shift                                                     (16)
#define SATA_MDIO_CTR_data_mask                                                      (0xFFFF0000)
#define SATA_MDIO_CTR_data(data)                                                     (0xFFFF0000&((data)<<16))
#define SATA_MDIO_CTR_data_src(data)                                                 ((0xFFFF0000&(data))>>16)
#define SATA_MDIO_CTR_get_data(data)                                                 ((0xFFFF0000&(data))>>16)
#define SATA_MDIO_CTR_phy_addr_shift                                                 (14)
#define SATA_MDIO_CTR_phy_addr_mask                                                  (0x0000C000)
#define SATA_MDIO_CTR_phy_addr(data)                                                 (0x0000C000&((data)<<14))
#define SATA_MDIO_CTR_phy_addr_src(data)                                             ((0x0000C000&(data))>>14)
#define SATA_MDIO_CTR_get_phy_addr(data)                                             ((0x0000C000&(data))>>14)
#define SATA_MDIO_CTR_phy_reg_addr_shift                                             (8)
#define SATA_MDIO_CTR_phy_reg_addr_mask                                              (0x00003F00)
#define SATA_MDIO_CTR_phy_reg_addr(data)                                             (0x00003F00&((data)<<8))
#define SATA_MDIO_CTR_phy_reg_addr_src(data)                                         ((0x00003F00&(data))>>8)
#define SATA_MDIO_CTR_get_phy_reg_addr(data)                                         ((0x00003F00&(data))>>8)
#define SATA_MDIO_CTR_mdio_busy_shift                                                (7)
#define SATA_MDIO_CTR_mdio_busy_mask                                                 (0x00000080)
#define SATA_MDIO_CTR_mdio_busy(data)                                                (0x00000080&((data)<<7))
#define SATA_MDIO_CTR_mdio_busy_src(data)                                            ((0x00000080&(data))>>7)
#define SATA_MDIO_CTR_get_mdio_busy(data)                                            ((0x00000080&(data))>>7)
#define SATA_MDIO_CTR_mdio_st_shift                                                  (5)
#define SATA_MDIO_CTR_mdio_st_mask                                                   (0x00000060)
#define SATA_MDIO_CTR_mdio_st(data)                                                  (0x00000060&((data)<<5))
#define SATA_MDIO_CTR_mdio_st_src(data)                                              ((0x00000060&(data))>>5)
#define SATA_MDIO_CTR_get_mdio_st(data)                                              ((0x00000060&(data))>>5)
#define SATA_MDIO_CTR_mdio_rdy_shift                                                 (4)
#define SATA_MDIO_CTR_mdio_rdy_mask                                                  (0x00000010)
#define SATA_MDIO_CTR_mdio_rdy(data)                                                 (0x00000010&((data)<<4))
#define SATA_MDIO_CTR_mdio_rdy_src(data)                                             ((0x00000010&(data))>>4)
#define SATA_MDIO_CTR_get_mdio_rdy(data)                                             ((0x00000010&(data))>>4)
#define SATA_MDIO_CTR_mclk_rate_shift                                                (2)
#define SATA_MDIO_CTR_mclk_rate_mask                                                 (0x0000000C)
#define SATA_MDIO_CTR_mclk_rate(data)                                                (0x0000000C&((data)<<2))
#define SATA_MDIO_CTR_mclk_rate_src(data)                                            ((0x0000000C&(data))>>2)
#define SATA_MDIO_CTR_get_mclk_rate(data)                                            ((0x0000000C&(data))>>2)
#define SATA_MDIO_CTR_mdio_srst_shift                                                (1)
#define SATA_MDIO_CTR_mdio_srst_mask                                                 (0x00000002)
#define SATA_MDIO_CTR_mdio_srst(data)                                                (0x00000002&((data)<<1))
#define SATA_MDIO_CTR_mdio_srst_src(data)                                            ((0x00000002&(data))>>1)
#define SATA_MDIO_CTR_get_mdio_srst(data)                                            ((0x00000002&(data))>>1)
#define SATA_MDIO_CTR_mdio_rdwr_shift                                                (0)
#define SATA_MDIO_CTR_mdio_rdwr_mask                                                 (0x00000001)
#define SATA_MDIO_CTR_mdio_rdwr(data)                                                (0x00000001&((data)<<0))
#define SATA_MDIO_CTR_mdio_rdwr_src(data)                                            ((0x00000001&(data))>>0)
#define SATA_MDIO_CTR_get_mdio_rdwr(data)                                            ((0x00000001&(data))>>0)


#define SATA_MDIO_CTR1                                                               0x9803FF64
#define SATA_MDIO_CTR1_reg_addr                                                      "0xD803FF64"
#define SATA_MDIO_CTR1_reg                                                           0xD803FF64
#define set_SATA_MDIO_CTR1_reg(data)   (*((volatile unsigned int*) SATA_MDIO_CTR1_reg)=data)
#define get_SATA_MDIO_CTR1_reg   (*((volatile unsigned int*) SATA_MDIO_CTR1_reg))
#define SATA_MDIO_CTR1_inst_adr                                                      "0x00D9"
#define SATA_MDIO_CTR1_inst                                                          0x00D9
#define SATA_MDIO_CTR1_phy_sel_shift                                                 (0)
#define SATA_MDIO_CTR1_phy_sel_mask                                                  (0x00000001)
#define SATA_MDIO_CTR1_phy_sel(data)                                                 (0x00000001&((data)<<0))
#define SATA_MDIO_CTR1_phy_sel_src(data)                                             ((0x00000001&(data))>>0)
#define SATA_MDIO_CTR1_get_phy_sel(data)                                             ((0x00000001&(data))>>0)


#define SATA_SPD                                                                     0x9803FF68
#define SATA_SPD_reg_addr                                                            "0xD803FF68"
#define SATA_SPD_reg                                                                 0xD803FF68
#define set_SATA_SPD_reg(data)   (*((volatile unsigned int*) SATA_SPD_reg)=data)
#define get_SATA_SPD_reg   (*((volatile unsigned int*) SATA_SPD_reg))
#define SATA_SPD_inst_adr                                                            "0x00DA"
#define SATA_SPD_inst                                                                0x00DA
#define SATA_SPD_p1_spd_mode_st_shift                                                (6)
#define SATA_SPD_p1_spd_mode_st_mask                                                 (0x000000C0)
#define SATA_SPD_p1_spd_mode_st(data)                                                (0x000000C0&((data)<<6))
#define SATA_SPD_p1_spd_mode_st_src(data)                                            ((0x000000C0&(data))>>6)
#define SATA_SPD_get_p1_spd_mode_st(data)                                            ((0x000000C0&(data))>>6)
#define SATA_SPD_p0_spd_mode_st_shift                                                (4)
#define SATA_SPD_p0_spd_mode_st_mask                                                 (0x00000030)
#define SATA_SPD_p0_spd_mode_st(data)                                                (0x00000030&((data)<<4))
#define SATA_SPD_p0_spd_mode_st_src(data)                                            ((0x00000030&(data))>>4)
#define SATA_SPD_get_p0_spd_mode_st(data)                                            ((0x00000030&(data))>>4)
#define SATA_SPD_p1_spd_mode_shift                                                   (2)
#define SATA_SPD_p1_spd_mode_mask                                                    (0x0000000C)
#define SATA_SPD_p1_spd_mode(data)                                                   (0x0000000C&((data)<<2))
#define SATA_SPD_p1_spd_mode_src(data)                                               ((0x0000000C&(data))>>2)
#define SATA_SPD_get_p1_spd_mode(data)                                               ((0x0000000C&(data))>>2)
#define SATA_SPD_p0_spd_mode_shift                                                   (0)
#define SATA_SPD_p0_spd_mode_mask                                                    (0x00000003)
#define SATA_SPD_p0_spd_mode(data)                                                   (0x00000003&((data)<<0))
#define SATA_SPD_p0_spd_mode_src(data)                                               ((0x00000003&(data))>>0)
#define SATA_SPD_get_p0_spd_mode(data)                                               ((0x00000003&(data))>>0)


#define SATA_RAM_CTR                                                                 0x9803FF70
#define SATA_RAM_CTR_reg_addr                                                        "0xD803FF70"
#define SATA_RAM_CTR_reg                                                             0xD803FF70
#define set_SATA_RAM_CTR_reg(data)   (*((volatile unsigned int*) SATA_RAM_CTR_reg)=data)
#define get_SATA_RAM_CTR_reg   (*((volatile unsigned int*) SATA_RAM_CTR_reg))
#define SATA_RAM_CTR_inst_adr                                                        "0x00DC"
#define SATA_RAM_CTR_inst                                                            0x00DC
#define SATA_RAM_CTR_done_st_shift                                                   (16)
#define SATA_RAM_CTR_done_st_mask                                                    (0x00010000)
#define SATA_RAM_CTR_done_st(data)                                                   (0x00010000&((data)<<16))
#define SATA_RAM_CTR_done_st_src(data)                                               ((0x00010000&(data))>>16)
#define SATA_RAM_CTR_get_done_st(data)                                               ((0x00010000&(data))>>16)
#define SATA_RAM_CTR_go_ct_shift                                                     (0)
#define SATA_RAM_CTR_go_ct_mask                                                      (0x00000001)
#define SATA_RAM_CTR_go_ct(data)                                                     (0x00000001&((data)<<0))
#define SATA_RAM_CTR_go_ct_src(data)                                                 ((0x00000001&(data))>>0)
#define SATA_RAM_CTR_get_go_ct(data)                                                 ((0x00000001&(data))>>0)


#define SATA_RAM_ADDR                                                                0x9803FF74
#define SATA_RAM_ADDR_reg_addr                                                       "0xD803FF74"
#define SATA_RAM_ADDR_reg                                                            0xD803FF74
#define set_SATA_RAM_ADDR_reg(data)   (*((volatile unsigned int*) SATA_RAM_ADDR_reg)=data)
#define get_SATA_RAM_ADDR_reg   (*((volatile unsigned int*) SATA_RAM_ADDR_reg))
#define SATA_RAM_ADDR_inst_adr                                                       "0x00DD"
#define SATA_RAM_ADDR_inst                                                           0x00DD
#define SATA_RAM_ADDR_sram_addr_shift                                                (0)
#define SATA_RAM_ADDR_sram_addr_mask                                                 (0xFFFFFFFF)
#define SATA_RAM_ADDR_sram_addr(data)                                                (0xFFFFFFFF&((data)<<0))
#define SATA_RAM_ADDR_sram_addr_src(data)                                            ((0xFFFFFFFF&(data))>>0)
#define SATA_RAM_ADDR_get_sram_addr(data)                                            ((0xFFFFFFFF&(data))>>0)


#define SATA_RAM_WDATA                                                               0x9803FF78
#define SATA_RAM_WDATA_reg_addr                                                      "0xD803FF78"
#define SATA_RAM_WDATA_reg                                                           0xD803FF78
#define set_SATA_RAM_WDATA_reg(data)   (*((volatile unsigned int*) SATA_RAM_WDATA_reg)=data)
#define get_SATA_RAM_WDATA_reg   (*((volatile unsigned int*) SATA_RAM_WDATA_reg))
#define SATA_RAM_WDATA_inst_adr                                                      "0x00DE"
#define SATA_RAM_WDATA_inst                                                          0x00DE
#define SATA_RAM_WDATA_ram_wdata_shift                                               (0)
#define SATA_RAM_WDATA_ram_wdata_mask                                                (0xFFFFFFFF)
#define SATA_RAM_WDATA_ram_wdata(data)                                               (0xFFFFFFFF&((data)<<0))
#define SATA_RAM_WDATA_ram_wdata_src(data)                                           ((0xFFFFFFFF&(data))>>0)
#define SATA_RAM_WDATA_get_ram_wdata(data)                                           ((0xFFFFFFFF&(data))>>0)


#define SATA_RAM_RDATA                                                               0x9803FF7C
#define SATA_RAM_RDATA_reg_addr                                                      "0xD803FF7C"
#define SATA_RAM_RDATA_reg                                                           0xD803FF7C
#define set_SATA_RAM_RDATA_reg(data)   (*((volatile unsigned int*) SATA_RAM_RDATA_reg)=data)
#define get_SATA_RAM_RDATA_reg   (*((volatile unsigned int*) SATA_RAM_RDATA_reg))
#define SATA_RAM_RDATA_inst_adr                                                      "0x00DF"
#define SATA_RAM_RDATA_inst                                                          0x00DF
#define SATA_RAM_RDATA_ram_rdata_shift                                               (0)
#define SATA_RAM_RDATA_ram_rdata_mask                                                (0xFFFFFFFF)
#define SATA_RAM_RDATA_ram_rdata(data)                                               (0xFFFFFFFF&((data)<<0))
#define SATA_RAM_RDATA_ram_rdata_src(data)                                           ((0xFFFFFFFF&(data))>>0)
#define SATA_RAM_RDATA_get_ram_rdata(data)                                           ((0xFFFFFFFF&(data))>>0)


#define SATA_SATA_MAC_P0_DBG0                                                        0x9803FF80
#define SATA_SATA_MAC_P0_DBG0_reg_addr                                               "0xD803FF80"
#define SATA_SATA_MAC_P0_DBG0_reg                                                    0xD803FF80
#define set_SATA_SATA_MAC_P0_DBG0_reg(data)   (*((volatile unsigned int*) SATA_SATA_MAC_P0_DBG0_reg)=data)
#define get_SATA_SATA_MAC_P0_DBG0_reg   (*((volatile unsigned int*) SATA_SATA_MAC_P0_DBG0_reg))
#define SATA_SATA_MAC_P0_DBG0_inst_adr                                               "0x00E0"
#define SATA_SATA_MAC_P0_DBG0_inst                                                   0x00E0
#define SATA_SATA_MAC_P0_DBG0_p0_csr_diagnr_shift                                    (0)
#define SATA_SATA_MAC_P0_DBG0_p0_csr_diagnr_mask                                     (0xFFFFFFFF)
#define SATA_SATA_MAC_P0_DBG0_p0_csr_diagnr(data)                                    (0xFFFFFFFF&((data)<<0))
#define SATA_SATA_MAC_P0_DBG0_p0_csr_diagnr_src(data)                                ((0xFFFFFFFF&(data))>>0)
#define SATA_SATA_MAC_P0_DBG0_get_p0_csr_diagnr(data)                                ((0xFFFFFFFF&(data))>>0)


#define SATA_SATA_MAC_P0_DBG1                                                        0x9803FF84
#define SATA_SATA_MAC_P0_DBG1_reg_addr                                               "0xD803FF84"
#define SATA_SATA_MAC_P0_DBG1_reg                                                    0xD803FF84
#define set_SATA_SATA_MAC_P0_DBG1_reg(data)   (*((volatile unsigned int*) SATA_SATA_MAC_P0_DBG1_reg)=data)
#define get_SATA_SATA_MAC_P0_DBG1_reg   (*((volatile unsigned int*) SATA_SATA_MAC_P0_DBG1_reg))
#define SATA_SATA_MAC_P0_DBG1_inst_adr                                               "0x00E1"
#define SATA_SATA_MAC_P0_DBG1_inst                                                   0x00E1
#define SATA_SATA_MAC_P0_DBG1_p0_csr_diagnr1_shift                                   (0)
#define SATA_SATA_MAC_P0_DBG1_p0_csr_diagnr1_mask                                    (0xFFFFFFFF)
#define SATA_SATA_MAC_P0_DBG1_p0_csr_diagnr1(data)                                   (0xFFFFFFFF&((data)<<0))
#define SATA_SATA_MAC_P0_DBG1_p0_csr_diagnr1_src(data)                               ((0xFFFFFFFF&(data))>>0)
#define SATA_SATA_MAC_P0_DBG1_get_p0_csr_diagnr1(data)                               ((0xFFFFFFFF&(data))>>0)


#define SATA_SATA_MAC_P0_DBG2                                                        0x9803FF88
#define SATA_SATA_MAC_P0_DBG2_reg_addr                                               "0xD803FF88"
#define SATA_SATA_MAC_P0_DBG2_reg                                                    0xD803FF88
#define set_SATA_SATA_MAC_P0_DBG2_reg(data)   (*((volatile unsigned int*) SATA_SATA_MAC_P0_DBG2_reg)=data)
#define get_SATA_SATA_MAC_P0_DBG2_reg   (*((volatile unsigned int*) SATA_SATA_MAC_P0_DBG2_reg))
#define SATA_SATA_MAC_P0_DBG2_inst_adr                                               "0x00E2"
#define SATA_SATA_MAC_P0_DBG2_inst                                                   0x00E2
#define SATA_SATA_MAC_P0_DBG2_p0_csr_is_shift                                        (0)
#define SATA_SATA_MAC_P0_DBG2_p0_csr_is_mask                                         (0xFFFFFFFF)
#define SATA_SATA_MAC_P0_DBG2_p0_csr_is(data)                                        (0xFFFFFFFF&((data)<<0))
#define SATA_SATA_MAC_P0_DBG2_p0_csr_is_src(data)                                    ((0xFFFFFFFF&(data))>>0)
#define SATA_SATA_MAC_P0_DBG2_get_p0_csr_is(data)                                    ((0xFFFFFFFF&(data))>>0)


#define SATA_SATA_MAC_P0_DBG3                                                        0x9803FF8C
#define SATA_SATA_MAC_P0_DBG3_reg_addr                                               "0xD803FF8C"
#define SATA_SATA_MAC_P0_DBG3_reg                                                    0xD803FF8C
#define set_SATA_SATA_MAC_P0_DBG3_reg(data)   (*((volatile unsigned int*) SATA_SATA_MAC_P0_DBG3_reg)=data)
#define get_SATA_SATA_MAC_P0_DBG3_reg   (*((volatile unsigned int*) SATA_SATA_MAC_P0_DBG3_reg))
#define SATA_SATA_MAC_P0_DBG3_inst_adr                                               "0x00E3"
#define SATA_SATA_MAC_P0_DBG3_inst                                                   0x00E3
#define SATA_SATA_MAC_P0_DBG3_p0_csr_cmd_shift                                       (0)
#define SATA_SATA_MAC_P0_DBG3_p0_csr_cmd_mask                                        (0xFFFFFFFF)
#define SATA_SATA_MAC_P0_DBG3_p0_csr_cmd(data)                                       (0xFFFFFFFF&((data)<<0))
#define SATA_SATA_MAC_P0_DBG3_p0_csr_cmd_src(data)                                   ((0xFFFFFFFF&(data))>>0)
#define SATA_SATA_MAC_P0_DBG3_get_p0_csr_cmd(data)                                   ((0xFFFFFFFF&(data))>>0)


#define SATA_SATA_MAC_P1_DBG0                                                        0x9803FF90
#define SATA_SATA_MAC_P1_DBG0_reg_addr                                               "0xD803FF90"
#define SATA_SATA_MAC_P1_DBG0_reg                                                    0xD803FF90
#define set_SATA_SATA_MAC_P1_DBG0_reg(data)   (*((volatile unsigned int*) SATA_SATA_MAC_P1_DBG0_reg)=data)
#define get_SATA_SATA_MAC_P1_DBG0_reg   (*((volatile unsigned int*) SATA_SATA_MAC_P1_DBG0_reg))
#define SATA_SATA_MAC_P1_DBG0_inst_adr                                               "0x00E4"
#define SATA_SATA_MAC_P1_DBG0_inst                                                   0x00E4
#define SATA_SATA_MAC_P1_DBG0_p1_csr_diagnr_shift                                    (0)
#define SATA_SATA_MAC_P1_DBG0_p1_csr_diagnr_mask                                     (0xFFFFFFFF)
#define SATA_SATA_MAC_P1_DBG0_p1_csr_diagnr(data)                                    (0xFFFFFFFF&((data)<<0))
#define SATA_SATA_MAC_P1_DBG0_p1_csr_diagnr_src(data)                                ((0xFFFFFFFF&(data))>>0)
#define SATA_SATA_MAC_P1_DBG0_get_p1_csr_diagnr(data)                                ((0xFFFFFFFF&(data))>>0)


#define SATA_SATA_MAC_P1_DBG1                                                        0x9803FF94
#define SATA_SATA_MAC_P1_DBG1_reg_addr                                               "0xD803FF94"
#define SATA_SATA_MAC_P1_DBG1_reg                                                    0xD803FF94
#define set_SATA_SATA_MAC_P1_DBG1_reg(data)   (*((volatile unsigned int*) SATA_SATA_MAC_P1_DBG1_reg)=data)
#define get_SATA_SATA_MAC_P1_DBG1_reg   (*((volatile unsigned int*) SATA_SATA_MAC_P1_DBG1_reg))
#define SATA_SATA_MAC_P1_DBG1_inst_adr                                               "0x00E5"
#define SATA_SATA_MAC_P1_DBG1_inst                                                   0x00E5
#define SATA_SATA_MAC_P1_DBG1_p1_csr_diagnr1_shift                                   (0)
#define SATA_SATA_MAC_P1_DBG1_p1_csr_diagnr1_mask                                    (0xFFFFFFFF)
#define SATA_SATA_MAC_P1_DBG1_p1_csr_diagnr1(data)                                   (0xFFFFFFFF&((data)<<0))
#define SATA_SATA_MAC_P1_DBG1_p1_csr_diagnr1_src(data)                               ((0xFFFFFFFF&(data))>>0)
#define SATA_SATA_MAC_P1_DBG1_get_p1_csr_diagnr1(data)                               ((0xFFFFFFFF&(data))>>0)


#define SATA_SATA_MAC_P1_DBG2                                                        0x9803FF98
#define SATA_SATA_MAC_P1_DBG2_reg_addr                                               "0xD803FF98"
#define SATA_SATA_MAC_P1_DBG2_reg                                                    0xD803FF98
#define set_SATA_SATA_MAC_P1_DBG2_reg(data)   (*((volatile unsigned int*) SATA_SATA_MAC_P1_DBG2_reg)=data)
#define get_SATA_SATA_MAC_P1_DBG2_reg   (*((volatile unsigned int*) SATA_SATA_MAC_P1_DBG2_reg))
#define SATA_SATA_MAC_P1_DBG2_inst_adr                                               "0x00E6"
#define SATA_SATA_MAC_P1_DBG2_inst                                                   0x00E6
#define SATA_SATA_MAC_P1_DBG2_p1_csr_is_shift                                        (0)
#define SATA_SATA_MAC_P1_DBG2_p1_csr_is_mask                                         (0xFFFFFFFF)
#define SATA_SATA_MAC_P1_DBG2_p1_csr_is(data)                                        (0xFFFFFFFF&((data)<<0))
#define SATA_SATA_MAC_P1_DBG2_p1_csr_is_src(data)                                    ((0xFFFFFFFF&(data))>>0)
#define SATA_SATA_MAC_P1_DBG2_get_p1_csr_is(data)                                    ((0xFFFFFFFF&(data))>>0)


#define SATA_SATA_MAC_P1_DBG3                                                        0x9803FF9c
#define SATA_SATA_MAC_P1_DBG3_reg_addr                                               "0xD803FF9C"
#define SATA_SATA_MAC_P1_DBG3_reg                                                    0xD803FF9C
#define set_SATA_SATA_MAC_P1_DBG3_reg(data)   (*((volatile unsigned int*) SATA_SATA_MAC_P1_DBG3_reg)=data)
#define get_SATA_SATA_MAC_P1_DBG3_reg   (*((volatile unsigned int*) SATA_SATA_MAC_P1_DBG3_reg))
#define SATA_SATA_MAC_P1_DBG3_inst_adr                                               "0x00E7"
#define SATA_SATA_MAC_P1_DBG3_inst                                                   0x00E7
#define SATA_SATA_MAC_P1_DBG3_p1_csr_cmd_shift                                       (0)
#define SATA_SATA_MAC_P1_DBG3_p1_csr_cmd_mask                                        (0xFFFFFFFF)
#define SATA_SATA_MAC_P1_DBG3_p1_csr_cmd(data)                                       (0xFFFFFFFF&((data)<<0))
#define SATA_SATA_MAC_P1_DBG3_p1_csr_cmd_src(data)                                   ((0xFFFFFFFF&(data))>>0)
#define SATA_SATA_MAC_P1_DBG3_get_p1_csr_cmd(data)                                   ((0xFFFFFFFF&(data))>>0)


#define SATA_SATA_MAC_P0_DBG4                                                        0x9803FFA0
#define SATA_SATA_MAC_P0_DBG4_reg_addr                                               "0xD803FFA0"
#define SATA_SATA_MAC_P0_DBG4_reg                                                    0xD803FFA0
#define set_SATA_SATA_MAC_P0_DBG4_reg(data)   (*((volatile unsigned int*) SATA_SATA_MAC_P0_DBG4_reg)=data)
#define get_SATA_SATA_MAC_P0_DBG4_reg   (*((volatile unsigned int*) SATA_SATA_MAC_P0_DBG4_reg))
#define SATA_SATA_MAC_P0_DBG4_inst_adr                                               "0x00E8"
#define SATA_SATA_MAC_P0_DBG4_inst                                                   0x00E8
#define SATA_SATA_MAC_P0_DBG4_p0_rx_error_shift                                      (5)
#define SATA_SATA_MAC_P0_DBG4_p0_rx_error_mask                                       (0x00000020)
#define SATA_SATA_MAC_P0_DBG4_p0_rx_error(data)                                      (0x00000020&((data)<<5))
#define SATA_SATA_MAC_P0_DBG4_p0_rx_error_src(data)                                  ((0x00000020&(data))>>5)
#define SATA_SATA_MAC_P0_DBG4_get_p0_rx_error(data)                                  ((0x00000020&(data))>>5)
#define SATA_SATA_MAC_P0_DBG4_p0_link_state_shift                                    (0)
#define SATA_SATA_MAC_P0_DBG4_p0_link_state_mask                                     (0x0000001F)
#define SATA_SATA_MAC_P0_DBG4_p0_link_state(data)                                    (0x0000001F&((data)<<0))
#define SATA_SATA_MAC_P0_DBG4_p0_link_state_src(data)                                ((0x0000001F&(data))>>0)
#define SATA_SATA_MAC_P0_DBG4_get_p0_link_state(data)                                ((0x0000001F&(data))>>0)


#define SATA_SATA_MAC_P1_DBG4                                                        0x9803FFA4
#define SATA_SATA_MAC_P1_DBG4_reg_addr                                               "0xD803FFA4"
#define SATA_SATA_MAC_P1_DBG4_reg                                                    0xD803FFA4
#define set_SATA_SATA_MAC_P1_DBG4_reg(data)   (*((volatile unsigned int*) SATA_SATA_MAC_P1_DBG4_reg)=data)
#define get_SATA_SATA_MAC_P1_DBG4_reg   (*((volatile unsigned int*) SATA_SATA_MAC_P1_DBG4_reg))
#define SATA_SATA_MAC_P1_DBG4_inst_adr                                               "0x00E9"
#define SATA_SATA_MAC_P1_DBG4_inst                                                   0x00E9
#define SATA_SATA_MAC_P1_DBG4_p1_rx_error_shift                                      (5)
#define SATA_SATA_MAC_P1_DBG4_p1_rx_error_mask                                       (0x00000020)
#define SATA_SATA_MAC_P1_DBG4_p1_rx_error(data)                                      (0x00000020&((data)<<5))
#define SATA_SATA_MAC_P1_DBG4_p1_rx_error_src(data)                                  ((0x00000020&(data))>>5)
#define SATA_SATA_MAC_P1_DBG4_get_p1_rx_error(data)                                  ((0x00000020&(data))>>5)
#define SATA_SATA_MAC_P1_DBG4_p1_link_state_shift                                    (0)
#define SATA_SATA_MAC_P1_DBG4_p1_link_state_mask                                     (0x0000001F)
#define SATA_SATA_MAC_P1_DBG4_p1_link_state(data)                                    (0x0000001F&((data)<<0))
#define SATA_SATA_MAC_P1_DBG4_p1_link_state_src(data)                                ((0x0000001F&(data))>>0)
#define SATA_SATA_MAC_P1_DBG4_get_p1_link_state(data)                                ((0x0000001F&(data))>>0)


#define SATA_SATA_BIST1_CTRL                                                         0x9803FFB0
#define SATA_SATA_BIST1_CTRL_reg_addr                                                "0xD803FFB0"
#define SATA_SATA_BIST1_CTRL_reg                                                     0xD803FFB0
#define set_SATA_SATA_BIST1_CTRL_reg(data)   (*((volatile unsigned int*) SATA_SATA_BIST1_CTRL_reg)=data)
#define get_SATA_SATA_BIST1_CTRL_reg   (*((volatile unsigned int*) SATA_SATA_BIST1_CTRL_reg))
#define SATA_SATA_BIST1_CTRL_inst_adr                                                "0x00EC"
#define SATA_SATA_BIST1_CTRL_inst                                                    0x00EC
#define SATA_SATA_BIST1_CTRL_sata_bist1_ls10_shift                                   (15)
#define SATA_SATA_BIST1_CTRL_sata_bist1_ls10_mask                                    (0x00018000)
#define SATA_SATA_BIST1_CTRL_sata_bist1_ls10(data)                                   (0x00018000&((data)<<15))
#define SATA_SATA_BIST1_CTRL_sata_bist1_ls10_src(data)                               ((0x00018000&(data))>>15)
#define SATA_SATA_BIST1_CTRL_get_sata_bist1_ls10(data)                               ((0x00018000&(data))>>15)
#define SATA_SATA_BIST1_CTRL_sata_bist1_rm_1_shift                                   (11)
#define SATA_SATA_BIST1_CTRL_sata_bist1_rm_1_mask                                    (0x00007800)
#define SATA_SATA_BIST1_CTRL_sata_bist1_rm_1(data)                                   (0x00007800&((data)<<11))
#define SATA_SATA_BIST1_CTRL_sata_bist1_rm_1_src(data)                               ((0x00007800&(data))>>11)
#define SATA_SATA_BIST1_CTRL_get_sata_bist1_rm_1(data)                               ((0x00007800&(data))>>11)
#define SATA_SATA_BIST1_CTRL_sata_bist1_rme_1_shift                                  (10)
#define SATA_SATA_BIST1_CTRL_sata_bist1_rme_1_mask                                   (0x00000400)
#define SATA_SATA_BIST1_CTRL_sata_bist1_rme_1(data)                                  (0x00000400&((data)<<10))
#define SATA_SATA_BIST1_CTRL_sata_bist1_rme_1_src(data)                              ((0x00000400&(data))>>10)
#define SATA_SATA_BIST1_CTRL_get_sata_bist1_rme_1(data)                              ((0x00000400&(data))>>10)
#define SATA_SATA_BIST1_CTRL_sata_bist1_rm_0_shift                                   (6)
#define SATA_SATA_BIST1_CTRL_sata_bist1_rm_0_mask                                    (0x000003C0)
#define SATA_SATA_BIST1_CTRL_sata_bist1_rm_0(data)                                   (0x000003C0&((data)<<6))
#define SATA_SATA_BIST1_CTRL_sata_bist1_rm_0_src(data)                               ((0x000003C0&(data))>>6)
#define SATA_SATA_BIST1_CTRL_get_sata_bist1_rm_0(data)                               ((0x000003C0&(data))>>6)
#define SATA_SATA_BIST1_CTRL_sata_bist1_rme_0_shift                                  (5)
#define SATA_SATA_BIST1_CTRL_sata_bist1_rme_0_mask                                   (0x00000020)
#define SATA_SATA_BIST1_CTRL_sata_bist1_rme_0(data)                                  (0x00000020&((data)<<5))
#define SATA_SATA_BIST1_CTRL_sata_bist1_rme_0_src(data)                              ((0x00000020&(data))>>5)
#define SATA_SATA_BIST1_CTRL_get_sata_bist1_rme_0(data)                              ((0x00000020&(data))>>5)
#define SATA_SATA_BIST1_CTRL_sata_drf_1_test_resume_shift                            (4)
#define SATA_SATA_BIST1_CTRL_sata_drf_1_test_resume_mask                             (0x00000010)
#define SATA_SATA_BIST1_CTRL_sata_drf_1_test_resume(data)                            (0x00000010&((data)<<4))
#define SATA_SATA_BIST1_CTRL_sata_drf_1_test_resume_src(data)                        ((0x00000010&(data))>>4)
#define SATA_SATA_BIST1_CTRL_get_sata_drf_1_test_resume(data)                        ((0x00000010&(data))>>4)
#define SATA_SATA_BIST1_CTRL_sata_drf_bist1_en_shift                                 (3)
#define SATA_SATA_BIST1_CTRL_sata_drf_bist1_en_mask                                  (0x00000008)
#define SATA_SATA_BIST1_CTRL_sata_drf_bist1_en(data)                                 (0x00000008&((data)<<3))
#define SATA_SATA_BIST1_CTRL_sata_drf_bist1_en_src(data)                             ((0x00000008&(data))>>3)
#define SATA_SATA_BIST1_CTRL_get_sata_drf_bist1_en(data)                             ((0x00000008&(data))>>3)
#define SATA_SATA_BIST1_CTRL_sata_bist1_en_shift                                     (2)
#define SATA_SATA_BIST1_CTRL_sata_bist1_en_mask                                      (0x00000004)
#define SATA_SATA_BIST1_CTRL_sata_bist1_en(data)                                     (0x00000004&((data)<<2))
#define SATA_SATA_BIST1_CTRL_sata_bist1_en_src(data)                                 ((0x00000004&(data))>>2)
#define SATA_SATA_BIST1_CTRL_get_sata_bist1_en(data)                                 ((0x00000004&(data))>>2)
#define SATA_SATA_BIST1_CTRL_sata_bist1_rstn_shift                                   (1)
#define SATA_SATA_BIST1_CTRL_sata_bist1_rstn_mask                                    (0x00000002)
#define SATA_SATA_BIST1_CTRL_sata_bist1_rstn(data)                                   (0x00000002&((data)<<1))
#define SATA_SATA_BIST1_CTRL_sata_bist1_rstn_src(data)                               ((0x00000002&(data))>>1)
#define SATA_SATA_BIST1_CTRL_get_sata_bist1_rstn(data)                               ((0x00000002&(data))>>1)
#define SATA_SATA_BIST1_CTRL_sata_bist1_test_mode_shift                              (0)
#define SATA_SATA_BIST1_CTRL_sata_bist1_test_mode_mask                               (0x00000001)
#define SATA_SATA_BIST1_CTRL_sata_bist1_test_mode(data)                              (0x00000001&((data)<<0))
#define SATA_SATA_BIST1_CTRL_sata_bist1_test_mode_src(data)                          ((0x00000001&(data))>>0)
#define SATA_SATA_BIST1_CTRL_get_sata_bist1_test_mode(data)                          ((0x00000001&(data))>>0)


#define SATA_SATA_BIST2_CTRL                                                         0x9803FFB4
#define SATA_SATA_BIST2_CTRL_reg_addr                                                "0xD803FFB4"
#define SATA_SATA_BIST2_CTRL_reg                                                     0xD803FFB4
#define set_SATA_SATA_BIST2_CTRL_reg(data)   (*((volatile unsigned int*) SATA_SATA_BIST2_CTRL_reg)=data)
#define get_SATA_SATA_BIST2_CTRL_reg   (*((volatile unsigned int*) SATA_SATA_BIST2_CTRL_reg))
#define SATA_SATA_BIST2_CTRL_inst_adr                                                "0x00ED"
#define SATA_SATA_BIST2_CTRL_inst                                                    0x00ED
#define SATA_SATA_BIST2_CTRL_sata_bist2_ls50_shift                                   (5)
#define SATA_SATA_BIST2_CTRL_sata_bist2_ls50_mask                                    (0x000007E0)
#define SATA_SATA_BIST2_CTRL_sata_bist2_ls50(data)                                   (0x000007E0&((data)<<5))
#define SATA_SATA_BIST2_CTRL_sata_bist2_ls50_src(data)                               ((0x000007E0&(data))>>5)
#define SATA_SATA_BIST2_CTRL_get_sata_bist2_ls50(data)                               ((0x000007E0&(data))>>5)
#define SATA_SATA_BIST2_CTRL_sata_drf_2_test_resume_shift                            (4)
#define SATA_SATA_BIST2_CTRL_sata_drf_2_test_resume_mask                             (0x00000010)
#define SATA_SATA_BIST2_CTRL_sata_drf_2_test_resume(data)                            (0x00000010&((data)<<4))
#define SATA_SATA_BIST2_CTRL_sata_drf_2_test_resume_src(data)                        ((0x00000010&(data))>>4)
#define SATA_SATA_BIST2_CTRL_get_sata_drf_2_test_resume(data)                        ((0x00000010&(data))>>4)
#define SATA_SATA_BIST2_CTRL_sata_drf_bist2_en_shift                                 (3)
#define SATA_SATA_BIST2_CTRL_sata_drf_bist2_en_mask                                  (0x00000008)
#define SATA_SATA_BIST2_CTRL_sata_drf_bist2_en(data)                                 (0x00000008&((data)<<3))
#define SATA_SATA_BIST2_CTRL_sata_drf_bist2_en_src(data)                             ((0x00000008&(data))>>3)
#define SATA_SATA_BIST2_CTRL_get_sata_drf_bist2_en(data)                             ((0x00000008&(data))>>3)
#define SATA_SATA_BIST2_CTRL_sata_bist2_en_shift                                     (2)
#define SATA_SATA_BIST2_CTRL_sata_bist2_en_mask                                      (0x00000004)
#define SATA_SATA_BIST2_CTRL_sata_bist2_en(data)                                     (0x00000004&((data)<<2))
#define SATA_SATA_BIST2_CTRL_sata_bist2_en_src(data)                                 ((0x00000004&(data))>>2)
#define SATA_SATA_BIST2_CTRL_get_sata_bist2_en(data)                                 ((0x00000004&(data))>>2)
#define SATA_SATA_BIST2_CTRL_sata_bist2_rstn_shift                                   (1)
#define SATA_SATA_BIST2_CTRL_sata_bist2_rstn_mask                                    (0x00000002)
#define SATA_SATA_BIST2_CTRL_sata_bist2_rstn(data)                                   (0x00000002&((data)<<1))
#define SATA_SATA_BIST2_CTRL_sata_bist2_rstn_src(data)                               ((0x00000002&(data))>>1)
#define SATA_SATA_BIST2_CTRL_get_sata_bist2_rstn(data)                               ((0x00000002&(data))>>1)
#define SATA_SATA_BIST2_CTRL_sata_bist2_test_mode_shift                              (0)
#define SATA_SATA_BIST2_CTRL_sata_bist2_test_mode_mask                               (0x00000001)
#define SATA_SATA_BIST2_CTRL_sata_bist2_test_mode(data)                              (0x00000001&((data)<<0))
#define SATA_SATA_BIST2_CTRL_sata_bist2_test_mode_src(data)                          ((0x00000001&(data))>>0)
#define SATA_SATA_BIST2_CTRL_get_sata_bist2_test_mode(data)                          ((0x00000001&(data))>>0)


#define SATA_SATA_BIST2_CTRL1                                                        0x9803FFB8
#define SATA_SATA_BIST2_CTRL1_reg_addr                                               "0xD803FFB8"
#define SATA_SATA_BIST2_CTRL1_reg                                                    0xD803FFB8
#define set_SATA_SATA_BIST2_CTRL1_reg(data)   (*((volatile unsigned int*) SATA_SATA_BIST2_CTRL1_reg)=data)
#define get_SATA_SATA_BIST2_CTRL1_reg   (*((volatile unsigned int*) SATA_SATA_BIST2_CTRL1_reg))
#define SATA_SATA_BIST2_CTRL1_inst_adr                                               "0x00EE"
#define SATA_SATA_BIST2_CTRL1_inst                                                   0x00EE
#define SATA_SATA_BIST2_CTRL1_sata_bist2_rm_5_shift                                  (26)
#define SATA_SATA_BIST2_CTRL1_sata_bist2_rm_5_mask                                   (0x3C000000)
#define SATA_SATA_BIST2_CTRL1_sata_bist2_rm_5(data)                                  (0x3C000000&((data)<<26))
#define SATA_SATA_BIST2_CTRL1_sata_bist2_rm_5_src(data)                              ((0x3C000000&(data))>>26)
#define SATA_SATA_BIST2_CTRL1_get_sata_bist2_rm_5(data)                              ((0x3C000000&(data))>>26)
#define SATA_SATA_BIST2_CTRL1_sata_bist2_rme_5_shift                                 (25)
#define SATA_SATA_BIST2_CTRL1_sata_bist2_rme_5_mask                                  (0x02000000)
#define SATA_SATA_BIST2_CTRL1_sata_bist2_rme_5(data)                                 (0x02000000&((data)<<25))
#define SATA_SATA_BIST2_CTRL1_sata_bist2_rme_5_src(data)                             ((0x02000000&(data))>>25)
#define SATA_SATA_BIST2_CTRL1_get_sata_bist2_rme_5(data)                             ((0x02000000&(data))>>25)
#define SATA_SATA_BIST2_CTRL1_sata_bist2_rm_4_shift                                  (21)
#define SATA_SATA_BIST2_CTRL1_sata_bist2_rm_4_mask                                   (0x01E00000)
#define SATA_SATA_BIST2_CTRL1_sata_bist2_rm_4(data)                                  (0x01E00000&((data)<<21))
#define SATA_SATA_BIST2_CTRL1_sata_bist2_rm_4_src(data)                              ((0x01E00000&(data))>>21)
#define SATA_SATA_BIST2_CTRL1_get_sata_bist2_rm_4(data)                              ((0x01E00000&(data))>>21)
#define SATA_SATA_BIST2_CTRL1_sata_bist2_rme_4_shift                                 (20)
#define SATA_SATA_BIST2_CTRL1_sata_bist2_rme_4_mask                                  (0x00100000)
#define SATA_SATA_BIST2_CTRL1_sata_bist2_rme_4(data)                                 (0x00100000&((data)<<20))
#define SATA_SATA_BIST2_CTRL1_sata_bist2_rme_4_src(data)                             ((0x00100000&(data))>>20)
#define SATA_SATA_BIST2_CTRL1_get_sata_bist2_rme_4(data)                             ((0x00100000&(data))>>20)
#define SATA_SATA_BIST2_CTRL1_sata_bist2_rm_3_shift                                  (16)
#define SATA_SATA_BIST2_CTRL1_sata_bist2_rm_3_mask                                   (0x000F0000)
#define SATA_SATA_BIST2_CTRL1_sata_bist2_rm_3(data)                                  (0x000F0000&((data)<<16))
#define SATA_SATA_BIST2_CTRL1_sata_bist2_rm_3_src(data)                              ((0x000F0000&(data))>>16)
#define SATA_SATA_BIST2_CTRL1_get_sata_bist2_rm_3(data)                              ((0x000F0000&(data))>>16)
#define SATA_SATA_BIST2_CTRL1_sata_bist2_rme_3_shift                                 (15)
#define SATA_SATA_BIST2_CTRL1_sata_bist2_rme_3_mask                                  (0x00008000)
#define SATA_SATA_BIST2_CTRL1_sata_bist2_rme_3(data)                                 (0x00008000&((data)<<15))
#define SATA_SATA_BIST2_CTRL1_sata_bist2_rme_3_src(data)                             ((0x00008000&(data))>>15)
#define SATA_SATA_BIST2_CTRL1_get_sata_bist2_rme_3(data)                             ((0x00008000&(data))>>15)
#define SATA_SATA_BIST2_CTRL1_sata_bist2_rm_2_shift                                  (11)
#define SATA_SATA_BIST2_CTRL1_sata_bist2_rm_2_mask                                   (0x00007800)
#define SATA_SATA_BIST2_CTRL1_sata_bist2_rm_2(data)                                  (0x00007800&((data)<<11))
#define SATA_SATA_BIST2_CTRL1_sata_bist2_rm_2_src(data)                              ((0x00007800&(data))>>11)
#define SATA_SATA_BIST2_CTRL1_get_sata_bist2_rm_2(data)                              ((0x00007800&(data))>>11)
#define SATA_SATA_BIST2_CTRL1_sata_bist2_rme_2_shift                                 (10)
#define SATA_SATA_BIST2_CTRL1_sata_bist2_rme_2_mask                                  (0x00000400)
#define SATA_SATA_BIST2_CTRL1_sata_bist2_rme_2(data)                                 (0x00000400&((data)<<10))
#define SATA_SATA_BIST2_CTRL1_sata_bist2_rme_2_src(data)                             ((0x00000400&(data))>>10)
#define SATA_SATA_BIST2_CTRL1_get_sata_bist2_rme_2(data)                             ((0x00000400&(data))>>10)
#define SATA_SATA_BIST2_CTRL1_sata_bist2_rm_1_shift                                  (6)
#define SATA_SATA_BIST2_CTRL1_sata_bist2_rm_1_mask                                   (0x000003C0)
#define SATA_SATA_BIST2_CTRL1_sata_bist2_rm_1(data)                                  (0x000003C0&((data)<<6))
#define SATA_SATA_BIST2_CTRL1_sata_bist2_rm_1_src(data)                              ((0x000003C0&(data))>>6)
#define SATA_SATA_BIST2_CTRL1_get_sata_bist2_rm_1(data)                              ((0x000003C0&(data))>>6)
#define SATA_SATA_BIST2_CTRL1_sata_bist2_rme_1_shift                                 (5)
#define SATA_SATA_BIST2_CTRL1_sata_bist2_rme_1_mask                                  (0x00000020)
#define SATA_SATA_BIST2_CTRL1_sata_bist2_rme_1(data)                                 (0x00000020&((data)<<5))
#define SATA_SATA_BIST2_CTRL1_sata_bist2_rme_1_src(data)                             ((0x00000020&(data))>>5)
#define SATA_SATA_BIST2_CTRL1_get_sata_bist2_rme_1(data)                             ((0x00000020&(data))>>5)
#define SATA_SATA_BIST2_CTRL1_sata_bist2_rm_0_shift                                  (1)
#define SATA_SATA_BIST2_CTRL1_sata_bist2_rm_0_mask                                   (0x0000001E)
#define SATA_SATA_BIST2_CTRL1_sata_bist2_rm_0(data)                                  (0x0000001E&((data)<<1))
#define SATA_SATA_BIST2_CTRL1_sata_bist2_rm_0_src(data)                              ((0x0000001E&(data))>>1)
#define SATA_SATA_BIST2_CTRL1_get_sata_bist2_rm_0(data)                              ((0x0000001E&(data))>>1)
#define SATA_SATA_BIST2_CTRL1_sata_bist2_rme_0_shift                                 (0)
#define SATA_SATA_BIST2_CTRL1_sata_bist2_rme_0_mask                                  (0x00000001)
#define SATA_SATA_BIST2_CTRL1_sata_bist2_rme_0(data)                                 (0x00000001&((data)<<0))
#define SATA_SATA_BIST2_CTRL1_sata_bist2_rme_0_src(data)                             ((0x00000001&(data))>>0)
#define SATA_SATA_BIST2_CTRL1_get_sata_bist2_rme_0(data)                             ((0x00000001&(data))>>0)


#define SATA_SATA_BIST1_STS                                                          0x9803FFC0
#define SATA_SATA_BIST1_STS_reg_addr                                                 "0xD803FFC0"
#define SATA_SATA_BIST1_STS_reg                                                      0xD803FFC0
#define set_SATA_SATA_BIST1_STS_reg(data)   (*((volatile unsigned int*) SATA_SATA_BIST1_STS_reg)=data)
#define get_SATA_SATA_BIST1_STS_reg   (*((volatile unsigned int*) SATA_SATA_BIST1_STS_reg))
#define SATA_SATA_BIST1_STS_inst_adr                                                 "0x00F0"
#define SATA_SATA_BIST1_STS_inst                                                     0x00F0
#define SATA_SATA_BIST1_STS_sata_drf_bist1_fail_1_shift                              (6)
#define SATA_SATA_BIST1_STS_sata_drf_bist1_fail_1_mask                               (0x00000040)
#define SATA_SATA_BIST1_STS_sata_drf_bist1_fail_1(data)                              (0x00000040&((data)<<6))
#define SATA_SATA_BIST1_STS_sata_drf_bist1_fail_1_src(data)                          ((0x00000040&(data))>>6)
#define SATA_SATA_BIST1_STS_get_sata_drf_bist1_fail_1(data)                          ((0x00000040&(data))>>6)
#define SATA_SATA_BIST1_STS_sata_bist1_fail_1_shift                                  (5)
#define SATA_SATA_BIST1_STS_sata_bist1_fail_1_mask                                   (0x00000020)
#define SATA_SATA_BIST1_STS_sata_bist1_fail_1(data)                                  (0x00000020&((data)<<5))
#define SATA_SATA_BIST1_STS_sata_bist1_fail_1_src(data)                              ((0x00000020&(data))>>5)
#define SATA_SATA_BIST1_STS_get_sata_bist1_fail_1(data)                              ((0x00000020&(data))>>5)
#define SATA_SATA_BIST1_STS_sata_drf_bist1_fail_0_shift                              (4)
#define SATA_SATA_BIST1_STS_sata_drf_bist1_fail_0_mask                               (0x00000010)
#define SATA_SATA_BIST1_STS_sata_drf_bist1_fail_0(data)                              (0x00000010&((data)<<4))
#define SATA_SATA_BIST1_STS_sata_drf_bist1_fail_0_src(data)                          ((0x00000010&(data))>>4)
#define SATA_SATA_BIST1_STS_get_sata_drf_bist1_fail_0(data)                          ((0x00000010&(data))>>4)
#define SATA_SATA_BIST1_STS_sata_bist1_fail_0_shift                                  (3)
#define SATA_SATA_BIST1_STS_sata_bist1_fail_0_mask                                   (0x00000008)
#define SATA_SATA_BIST1_STS_sata_bist1_fail_0(data)                                  (0x00000008&((data)<<3))
#define SATA_SATA_BIST1_STS_sata_bist1_fail_0_src(data)                              ((0x00000008&(data))>>3)
#define SATA_SATA_BIST1_STS_get_sata_bist1_fail_0(data)                              ((0x00000008&(data))>>3)
#define SATA_SATA_BIST1_STS_sata_drf_1_start_pause_shift                             (2)
#define SATA_SATA_BIST1_STS_sata_drf_1_start_pause_mask                              (0x00000004)
#define SATA_SATA_BIST1_STS_sata_drf_1_start_pause(data)                             (0x00000004&((data)<<2))
#define SATA_SATA_BIST1_STS_sata_drf_1_start_pause_src(data)                         ((0x00000004&(data))>>2)
#define SATA_SATA_BIST1_STS_get_sata_drf_1_start_pause(data)                         ((0x00000004&(data))>>2)
#define SATA_SATA_BIST1_STS_sata_drf_bist1_done_shift                                (1)
#define SATA_SATA_BIST1_STS_sata_drf_bist1_done_mask                                 (0x00000002)
#define SATA_SATA_BIST1_STS_sata_drf_bist1_done(data)                                (0x00000002&((data)<<1))
#define SATA_SATA_BIST1_STS_sata_drf_bist1_done_src(data)                            ((0x00000002&(data))>>1)
#define SATA_SATA_BIST1_STS_get_sata_drf_bist1_done(data)                            ((0x00000002&(data))>>1)
#define SATA_SATA_BIST1_STS_sata_bist1_done_shift                                    (0)
#define SATA_SATA_BIST1_STS_sata_bist1_done_mask                                     (0x00000001)
#define SATA_SATA_BIST1_STS_sata_bist1_done(data)                                    (0x00000001&((data)<<0))
#define SATA_SATA_BIST1_STS_sata_bist1_done_src(data)                                ((0x00000001&(data))>>0)
#define SATA_SATA_BIST1_STS_get_sata_bist1_done(data)                                ((0x00000001&(data))>>0)


#define SATA_SATA_BIST2_STS                                                          0x9803FFC4
#define SATA_SATA_BIST2_STS_reg_addr                                                 "0xD803FFC4"
#define SATA_SATA_BIST2_STS_reg                                                      0xD803FFC4
#define set_SATA_SATA_BIST2_STS_reg(data)   (*((volatile unsigned int*) SATA_SATA_BIST2_STS_reg)=data)
#define get_SATA_SATA_BIST2_STS_reg   (*((volatile unsigned int*) SATA_SATA_BIST2_STS_reg))
#define SATA_SATA_BIST2_STS_inst_adr                                                 "0x00F1"
#define SATA_SATA_BIST2_STS_inst                                                     0x00F1
#define SATA_SATA_BIST2_STS_sata_drf_bist2_fail_5_shift                              (14)
#define SATA_SATA_BIST2_STS_sata_drf_bist2_fail_5_mask                               (0x00004000)
#define SATA_SATA_BIST2_STS_sata_drf_bist2_fail_5(data)                              (0x00004000&((data)<<14))
#define SATA_SATA_BIST2_STS_sata_drf_bist2_fail_5_src(data)                          ((0x00004000&(data))>>14)
#define SATA_SATA_BIST2_STS_get_sata_drf_bist2_fail_5(data)                          ((0x00004000&(data))>>14)
#define SATA_SATA_BIST2_STS_sata_bist2_fail_5_shift                                  (13)
#define SATA_SATA_BIST2_STS_sata_bist2_fail_5_mask                                   (0x00002000)
#define SATA_SATA_BIST2_STS_sata_bist2_fail_5(data)                                  (0x00002000&((data)<<13))
#define SATA_SATA_BIST2_STS_sata_bist2_fail_5_src(data)                              ((0x00002000&(data))>>13)
#define SATA_SATA_BIST2_STS_get_sata_bist2_fail_5(data)                              ((0x00002000&(data))>>13)
#define SATA_SATA_BIST2_STS_sata_drf_bist2_fail_4_shift                              (12)
#define SATA_SATA_BIST2_STS_sata_drf_bist2_fail_4_mask                               (0x00001000)
#define SATA_SATA_BIST2_STS_sata_drf_bist2_fail_4(data)                              (0x00001000&((data)<<12))
#define SATA_SATA_BIST2_STS_sata_drf_bist2_fail_4_src(data)                          ((0x00001000&(data))>>12)
#define SATA_SATA_BIST2_STS_get_sata_drf_bist2_fail_4(data)                          ((0x00001000&(data))>>12)
#define SATA_SATA_BIST2_STS_sata_bist2_fail_4_shift                                  (11)
#define SATA_SATA_BIST2_STS_sata_bist2_fail_4_mask                                   (0x00000800)
#define SATA_SATA_BIST2_STS_sata_bist2_fail_4(data)                                  (0x00000800&((data)<<11))
#define SATA_SATA_BIST2_STS_sata_bist2_fail_4_src(data)                              ((0x00000800&(data))>>11)
#define SATA_SATA_BIST2_STS_get_sata_bist2_fail_4(data)                              ((0x00000800&(data))>>11)
#define SATA_SATA_BIST2_STS_sata_drf_bist2_fail_3_shift                              (10)
#define SATA_SATA_BIST2_STS_sata_drf_bist2_fail_3_mask                               (0x00000400)
#define SATA_SATA_BIST2_STS_sata_drf_bist2_fail_3(data)                              (0x00000400&((data)<<10))
#define SATA_SATA_BIST2_STS_sata_drf_bist2_fail_3_src(data)                          ((0x00000400&(data))>>10)
#define SATA_SATA_BIST2_STS_get_sata_drf_bist2_fail_3(data)                          ((0x00000400&(data))>>10)
#define SATA_SATA_BIST2_STS_sata_bist2_fail_3_shift                                  (9)
#define SATA_SATA_BIST2_STS_sata_bist2_fail_3_mask                                   (0x00000200)
#define SATA_SATA_BIST2_STS_sata_bist2_fail_3(data)                                  (0x00000200&((data)<<9))
#define SATA_SATA_BIST2_STS_sata_bist2_fail_3_src(data)                              ((0x00000200&(data))>>9)
#define SATA_SATA_BIST2_STS_get_sata_bist2_fail_3(data)                              ((0x00000200&(data))>>9)
#define SATA_SATA_BIST2_STS_sata_drf_bist2_fail_2_shift                              (8)
#define SATA_SATA_BIST2_STS_sata_drf_bist2_fail_2_mask                               (0x00000100)
#define SATA_SATA_BIST2_STS_sata_drf_bist2_fail_2(data)                              (0x00000100&((data)<<8))
#define SATA_SATA_BIST2_STS_sata_drf_bist2_fail_2_src(data)                          ((0x00000100&(data))>>8)
#define SATA_SATA_BIST2_STS_get_sata_drf_bist2_fail_2(data)                          ((0x00000100&(data))>>8)
#define SATA_SATA_BIST2_STS_sata_bist2_fail_2_shift                                  (7)
#define SATA_SATA_BIST2_STS_sata_bist2_fail_2_mask                                   (0x00000080)
#define SATA_SATA_BIST2_STS_sata_bist2_fail_2(data)                                  (0x00000080&((data)<<7))
#define SATA_SATA_BIST2_STS_sata_bist2_fail_2_src(data)                              ((0x00000080&(data))>>7)
#define SATA_SATA_BIST2_STS_get_sata_bist2_fail_2(data)                              ((0x00000080&(data))>>7)
#define SATA_SATA_BIST2_STS_sata_drf_bist2_fail_1_shift                              (6)
#define SATA_SATA_BIST2_STS_sata_drf_bist2_fail_1_mask                               (0x00000040)
#define SATA_SATA_BIST2_STS_sata_drf_bist2_fail_1(data)                              (0x00000040&((data)<<6))
#define SATA_SATA_BIST2_STS_sata_drf_bist2_fail_1_src(data)                          ((0x00000040&(data))>>6)
#define SATA_SATA_BIST2_STS_get_sata_drf_bist2_fail_1(data)                          ((0x00000040&(data))>>6)
#define SATA_SATA_BIST2_STS_sata_bist2_fail_1_shift                                  (5)
#define SATA_SATA_BIST2_STS_sata_bist2_fail_1_mask                                   (0x00000020)
#define SATA_SATA_BIST2_STS_sata_bist2_fail_1(data)                                  (0x00000020&((data)<<5))
#define SATA_SATA_BIST2_STS_sata_bist2_fail_1_src(data)                              ((0x00000020&(data))>>5)
#define SATA_SATA_BIST2_STS_get_sata_bist2_fail_1(data)                              ((0x00000020&(data))>>5)
#define SATA_SATA_BIST2_STS_sata_drf_bist2_fail_0_shift                              (4)
#define SATA_SATA_BIST2_STS_sata_drf_bist2_fail_0_mask                               (0x00000010)
#define SATA_SATA_BIST2_STS_sata_drf_bist2_fail_0(data)                              (0x00000010&((data)<<4))
#define SATA_SATA_BIST2_STS_sata_drf_bist2_fail_0_src(data)                          ((0x00000010&(data))>>4)
#define SATA_SATA_BIST2_STS_get_sata_drf_bist2_fail_0(data)                          ((0x00000010&(data))>>4)
#define SATA_SATA_BIST2_STS_sata_bist2_fail_0_shift                                  (3)
#define SATA_SATA_BIST2_STS_sata_bist2_fail_0_mask                                   (0x00000008)
#define SATA_SATA_BIST2_STS_sata_bist2_fail_0(data)                                  (0x00000008&((data)<<3))
#define SATA_SATA_BIST2_STS_sata_bist2_fail_0_src(data)                              ((0x00000008&(data))>>3)
#define SATA_SATA_BIST2_STS_get_sata_bist2_fail_0(data)                              ((0x00000008&(data))>>3)
#define SATA_SATA_BIST2_STS_sata_drf_2_start_pause_shift                             (2)
#define SATA_SATA_BIST2_STS_sata_drf_2_start_pause_mask                              (0x00000004)
#define SATA_SATA_BIST2_STS_sata_drf_2_start_pause(data)                             (0x00000004&((data)<<2))
#define SATA_SATA_BIST2_STS_sata_drf_2_start_pause_src(data)                         ((0x00000004&(data))>>2)
#define SATA_SATA_BIST2_STS_get_sata_drf_2_start_pause(data)                         ((0x00000004&(data))>>2)
#define SATA_SATA_BIST2_STS_sata_drf_bist2_done_shift                                (1)
#define SATA_SATA_BIST2_STS_sata_drf_bist2_done_mask                                 (0x00000002)
#define SATA_SATA_BIST2_STS_sata_drf_bist2_done(data)                                (0x00000002&((data)<<1))
#define SATA_SATA_BIST2_STS_sata_drf_bist2_done_src(data)                            ((0x00000002&(data))>>1)
#define SATA_SATA_BIST2_STS_get_sata_drf_bist2_done(data)                            ((0x00000002&(data))>>1)
#define SATA_SATA_BIST2_STS_sata_bist2_done_shift                                    (0)
#define SATA_SATA_BIST2_STS_sata_bist2_done_mask                                     (0x00000001)
#define SATA_SATA_BIST2_STS_sata_bist2_done(data)                                    (0x00000001&((data)<<0))
#define SATA_SATA_BIST2_STS_sata_bist2_done_src(data)                                ((0x00000001&(data))>>0)
#define SATA_SATA_BIST2_STS_get_sata_bist2_done(data)                                ((0x00000001&(data))>>0)


#define SATA_SATA_DUMMY_0_REG                                                        0x9803FFC8
#define SATA_SATA_DUMMY_0_REG_reg_addr                                               "0xD803FFC8"
#define SATA_SATA_DUMMY_0_REG_reg                                                    0xD803FFC8
#define set_SATA_SATA_DUMMY_0_REG_reg(data)   (*((volatile unsigned int*) SATA_SATA_DUMMY_0_REG_reg)=data)
#define get_SATA_SATA_DUMMY_0_REG_reg   (*((volatile unsigned int*) SATA_SATA_DUMMY_0_REG_reg))
#define SATA_SATA_DUMMY_0_REG_inst_adr                                               "0x00F2"
#define SATA_SATA_DUMMY_0_REG_inst                                                   0x00F2
#define SATA_SATA_DUMMY_0_REG_dummy_0_shift                                          (0)
#define SATA_SATA_DUMMY_0_REG_dummy_0_mask                                           (0xFFFFFFFF)
#define SATA_SATA_DUMMY_0_REG_dummy_0(data)                                          (0xFFFFFFFF&((data)<<0))
#define SATA_SATA_DUMMY_0_REG_dummy_0_src(data)                                      ((0xFFFFFFFF&(data))>>0)
#define SATA_SATA_DUMMY_0_REG_get_dummy_0(data)                                      ((0xFFFFFFFF&(data))>>0)


#define SATA_SATA_DUMMY_1_REG                                                        0x9803FFCC
#define SATA_SATA_DUMMY_1_REG_reg_addr                                               "0xD803FFCC"
#define SATA_SATA_DUMMY_1_REG_reg                                                    0xD803FFCC
#define set_SATA_SATA_DUMMY_1_REG_reg(data)   (*((volatile unsigned int*) SATA_SATA_DUMMY_1_REG_reg)=data)
#define get_SATA_SATA_DUMMY_1_REG_reg   (*((volatile unsigned int*) SATA_SATA_DUMMY_1_REG_reg))
#define SATA_SATA_DUMMY_1_REG_inst_adr                                               "0x00F3"
#define SATA_SATA_DUMMY_1_REG_inst                                                   0x00F3
#define SATA_SATA_DUMMY_1_REG_dummy_1_shift                                          (0)
#define SATA_SATA_DUMMY_1_REG_dummy_1_mask                                           (0xFFFFFFFF)
#define SATA_SATA_DUMMY_1_REG_dummy_1(data)                                          (0xFFFFFFFF&((data)<<0))
#define SATA_SATA_DUMMY_1_REG_dummy_1_src(data)                                      ((0xFFFFFFFF&(data))>>0)
#define SATA_SATA_DUMMY_1_REG_get_dummy_1(data)                                      ((0xFFFFFFFF&(data))>>0)


#endif
