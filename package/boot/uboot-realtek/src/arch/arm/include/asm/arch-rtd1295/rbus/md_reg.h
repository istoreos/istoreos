/**************************************************************
// Spec Version                  : 0.4
// Parser Version                : DVR_Parser_6.3
// CModelGen Version             : 5.0 2009.04.09
// Naming Rule                   : Register_Name
// Naming Rule                   : Module_Register_Name_reg
// Parse Option                  : Only Parse _op1
// Parse Address Region          : All Address Region 
// Decode bit number             : 12 bits
// Firmware Header Generate Date : 2013/9/16 19:58:8
***************************************************************/


#ifndef MD_REG_H
#define MD_REG_H
#ifdef  _MD_USE_STRUCT
typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     smq_idle:1;
unsigned int     smq_cmd_swap:1;
unsigned int     smq_go:1;
unsigned int     write_data:1;
}MD_SMQ_CNTL;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     gsp_length_err:1;
unsigned int     gsp_rx_thd_ints:1;
unsigned int     gsp_txdat_thd_ints:1;
unsigned int     gsp_txbasic_thd_ints:1;
unsigned int     gsp_tx_thd_ints:1;
unsigned int     smq_chksum_err:1;
unsigned int     ur_length_err:1;
unsigned int     ur_rx_timeout:1;
unsigned int     ur_rx_thd:1;
unsigned int     ur_tx_thd:1;
unsigned int     smq_mode_2b4berr:1;
unsigned int     fdma_done:1;
unsigned int     smq_empty:1;
unsigned int     smq_length_err:1;
unsigned int     smq_inst_err:1;
unsigned int     write_data:1;
}MD_SMQ_INT_STATUS;

typedef struct 
{
unsigned int     reserved_0:15;
unsigned int     scpu_int_en:1;
unsigned int     gsp_length_err_en:1;
unsigned int     gsp_rx_thd_en:1;
unsigned int     gsp_txdat_thd_en:1;
unsigned int     gsp_txbasic_thd_en:1;
unsigned int     gsp_tx_thd_en:1;
unsigned int     smq_chksum_err_en:1;
unsigned int     ur_length_err_en:1;
unsigned int     ur_rx_timeout_en:1;
unsigned int     ur_rx_thd_en:1;
unsigned int     ur_tx_thd_en:1;
unsigned int     smq_mode_2b4b_err_en:1;
unsigned int     fdma_done_en:1;
unsigned int     smq_empty_en:1;
unsigned int     smq_length_err_en:1;
unsigned int     smq_inst_err_en:1;
unsigned int     write_data:1;
}MD_SMQ_INT_ENABLE;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     smq_base:27;
unsigned int     reserved_1:4;
}MD_SMQBASE;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     smq_limit:27;
unsigned int     reserved_1:4;
}MD_SMQLIMIT;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     smq_rdptr:27;
unsigned int     reserved_1:4;
}MD_SMQRDPTR;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     smq_wrptr:27;
unsigned int     reserved_1:4;
}MD_SMQWRPTR;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     smq_inst_remain:5;
}MD_SMQFIFOSTATE;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     smq_inst_cnt:16;
}MD_SMQ_INSTCNT;

typedef struct 
{
unsigned int     smq_chksum:32;
}MD_SMQ_CHKSUM;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     vmq_idle:1;
unsigned int     vmq_cmd_swap:1;
unsigned int     vmq_go:1;
unsigned int     write_data:1;
}MD_VMQ_CNTL;

typedef struct 
{
unsigned int     reserved_0:26;
unsigned int     vmq_chksum_err:1;
unsigned int     vmq_mode_2b4berr:1;
unsigned int     vmq_empty:1;
unsigned int     vmq_length_err:1;
unsigned int     vmq_inst_err:1;
unsigned int     write_data:1;
}MD_VMQ_INT_STATUS;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     vcpu_int_en:1;
unsigned int     vmq_chksum_err_en:1;
unsigned int     vmq_mode_2b4b_err_en:1;
unsigned int     vmq_empty_en:1;
unsigned int     vmq_length_err_en:1;
unsigned int     vmq_inst_err_en:1;
unsigned int     write_data:1;
}MD_VMQ_INT_ENABLE;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     vmq_base:27;
unsigned int     reserved_1:4;
}MD_VMQBASE;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     vmq_limit:27;
unsigned int     reserved_1:4;
}MD_VMQLIMIT;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     vmq_rdptr:27;
unsigned int     reserved_1:4;
}MD_VMQRDPTR;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     vmq_wrptr:27;
unsigned int     reserved_1:4;
}MD_VMQWRPTR;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     vmq_inst_remain:5;
}MD_VMQFIFOSTATE;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     vmq_inst_cnt:16;
}MD_VMQ_INSTCNT;

typedef struct 
{
unsigned int     vmq_chksum:32;
}MD_VMQ_CHKSUM;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     kmq_idle:1;
unsigned int     kmq_cmd_swap:1;
unsigned int     kmq_go:1;
unsigned int     write_data:1;
}MD_KMQ_CNTL;

typedef struct 
{
unsigned int     reserved_0:26;
unsigned int     kmq_chksum_err:1;
unsigned int     kmq_mode_2b4berr:1;
unsigned int     kmq_empty:1;
unsigned int     kmq_length_err:1;
unsigned int     kmq_inst_err:1;
unsigned int     write_data:1;
}MD_KMQ_INT_STATUS;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     kcpu_int_en:1;
unsigned int     kmq_chksum_err_en:1;
unsigned int     kmq_mode_2b4b_err_en:1;
unsigned int     kmq_empty_en:1;
unsigned int     kmq_length_err_en:1;
unsigned int     kmq_inst_err_en:1;
unsigned int     write_data:1;
}MD_KMQ_INT_ENABLE;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     kmq_base:27;
unsigned int     reserved_1:4;
}MD_KMQBASE;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     kmq_limit:27;
unsigned int     reserved_1:4;
}MD_KMQLIMIT;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     kmq_rdptr:27;
unsigned int     reserved_1:4;
}MD_KMQRDPTR;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     kmq_wrptr:27;
unsigned int     reserved_1:4;
}MD_KMQWRPTR;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     kmq_inst_remain:5;
}MD_KMQFIFOSTATE;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     kmq_inst_cnt:16;
}MD_KMQ_INSTCNT;

typedef struct 
{
unsigned int     kmq_chksum:32;
}MD_KMQ_CHKSUM;

typedef struct 
{
unsigned int     reserved_0:17;
unsigned int     md_dbg_sel1:7;
unsigned int     md_dbg_sel0:7;
unsigned int     md_dbg_enable:1;
}MD_DBG;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     fdma_ddr_saddr:31;
}MD_FDMA_DDR_SADDR;

typedef struct 
{
unsigned int     reserved_0:7;
unsigned int     fdma_fl_saddr:25;
}MD_FDMA_FL_SADDR;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     fl_cp_en:1;
unsigned int     fl_mapping_mode:1;
unsigned int     fdma_swap:1;
unsigned int     fdma_max_xfer:2;
unsigned int     fdma_dir:1;
unsigned int     fdma_length:25;
}MD_FDMA_CTRL2;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     write_en2:1;
unsigned int     fdma_stop:1;
unsigned int     write_en1:1;
unsigned int     fdma_go:1;
}MD_FDMA_CTRL1;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     tx_base:28;
unsigned int     reserved_1:3;
}MD_UR_TXBASE;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     tx_limit:28;
unsigned int     reserved_1:3;
}MD_UR_TXLIMIT;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     tx_wrptr:31;
}MD_UR_TXWRPTR;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     tx_rdptr:31;
}MD_UR_TXRDPTR;

typedef struct 
{
unsigned int     tx_thd:32;
}MD_UR_TXTHD;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     rx_base:28;
unsigned int     reserved_1:3;
}MD_UR_RXBASE;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     rx_limit:28;
unsigned int     reserved_1:3;
}MD_UR_RXLIMIT;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     rx_wrptr:31;
}MD_UR_RXWRPTR;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     rx_rdptr:31;
}MD_UR_RXRDPTR;

typedef struct 
{
unsigned int     rx_thd:32;
}MD_UR_RXTHD;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     ur_en:1;
}MD_UR_ENABLE;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     gsp_tx_base:28;
unsigned int     reserved_1:3;
}MD_GSP_TXBASE;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     gsp_tx_limit:28;
unsigned int     reserved_1:3;
}MD_GSP_TXLIMIT;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     gsp_tx_wrptr:31;
}MD_GSP_TXWRPTR;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     gsp_tx_rdptr:31;
}MD_GSP_TXRDPTR;

typedef struct 
{
unsigned int     gsp_tx_thd:32;
}MD_GSP_TXTHD;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     gsp_rx_base:28;
unsigned int     reserved_1:3;
}MD_GSP_RXBASE;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     gsp_rx_limit:28;
unsigned int     reserved_1:3;
}MD_GSP_RXLIMIT;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     gsp_rx_wrptr:31;
}MD_GSP_RXWRPTR;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     gsp_rx_rdptr:31;
}MD_GSP_RXRDPTR;

typedef struct 
{
unsigned int     gsp_rx_thd:32;
}MD_GSP_RXTHD;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     gsp_en:1;
}MD_GSP_ENABLE;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     gsp_txbasic_base:28;
unsigned int     reserved_1:3;
}MD_GSP_TXBASICBASE;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     gsp_txbasic_limit:28;
unsigned int     reserved_1:3;
}MD_GSP_TXBASICLIMIT;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     gsp_txbasic_wrptr:31;
}MD_GSP_TXBASICWRPTR;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     gsp_txbasic_rdptr:31;
}MD_GSP_TXBASICRDPTR;

typedef struct 
{
unsigned int     gsp_txbasic_thd:32;
}MD_GSP_TXBASICTHD;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     gsp_txdat_base:28;
unsigned int     reserved_1:3;
}MD_GSP_TXDATBASE;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     gsp_txdat_limit:28;
unsigned int     reserved_1:3;
}MD_GSP_TXDATLIMIT;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     gsp_txdat_wrptr:31;
}MD_GSP_TXDATWRPTR;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     gsp_txdat_rdptr:31;
}MD_GSP_TXDATRDPTR;

typedef struct 
{
unsigned int     gsp_txdat_thd:32;
}MD_GSP_TXDATTHD;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     gating_en:1;
}MD_POWER;

typedef struct 
{
unsigned int     dummy1:32;
}MD_DUMMY1;

typedef struct 
{
unsigned int     dummy2:32;
}MD_DUMMY2;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     dvse:1;
unsigned int     dvs_3:1;
unsigned int     dvs_2:1;
unsigned int     dvs_1:1;
unsigned int     dvs_0:1;
}BIST_DVS;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     bist_fail2:1;
unsigned int     bist_fail1:1;
unsigned int     bist_fail0:1;
unsigned int     bist_done:1;
}BIST_ST;

typedef struct 
{
unsigned int     reserved_0:15;
unsigned int     drf_start_pause:1;
unsigned int     reserved_1:12;
unsigned int     drf_fail2:1;
unsigned int     drf_fail1:1;
unsigned int     drf_fail0:1;
unsigned int     drf_done:1;
}DRF_ST;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     drf_test_resume:1;
unsigned int     drf_bist_mode:1;
unsigned int     bist_mode:1;
}MBIST_CON;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     smq_freerun:1;
}MD_SMQFREERUN;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     vmq_freerun:1;
}MD_VMQFREERUN;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     kmq_freerun:1;
}MD_KMQFREERUN;

#endif

#define MD_SMQ_CNTL                                                                  0x9800B000
#define MD_SMQ_CNTL_reg_addr                                                         "0x9800B000"
#define MD_SMQ_CNTL_reg                                                              0x9800B000
#define set_MD_SMQ_CNTL_reg(data)   (*((volatile unsigned int*) MD_SMQ_CNTL_reg)=data)
#define get_MD_SMQ_CNTL_reg   (*((volatile unsigned int*) MD_SMQ_CNTL_reg))
#define MD_SMQ_CNTL_inst_adr                                                         "0x0000"
#define MD_SMQ_CNTL_inst                                                             0x0000
#define MD_SMQ_CNTL_smq_idle_shift                                                   (3)
#define MD_SMQ_CNTL_smq_idle_mask                                                    (0x00000008)
#define MD_SMQ_CNTL_smq_idle(data)                                                   (0x00000008&((data)<<3))
#define MD_SMQ_CNTL_smq_idle_src(data)                                               ((0x00000008&(data))>>3)
#define MD_SMQ_CNTL_get_smq_idle(data)                                               ((0x00000008&(data))>>3)
#define MD_SMQ_CNTL_smq_cmd_swap_shift                                               (2)
#define MD_SMQ_CNTL_smq_cmd_swap_mask                                                (0x00000004)
#define MD_SMQ_CNTL_smq_cmd_swap(data)                                               (0x00000004&((data)<<2))
#define MD_SMQ_CNTL_smq_cmd_swap_src(data)                                           ((0x00000004&(data))>>2)
#define MD_SMQ_CNTL_get_smq_cmd_swap(data)                                           ((0x00000004&(data))>>2)
#define MD_SMQ_CNTL_smq_go_shift                                                     (1)
#define MD_SMQ_CNTL_smq_go_mask                                                      (0x00000002)
#define MD_SMQ_CNTL_smq_go(data)                                                     (0x00000002&((data)<<1))
#define MD_SMQ_CNTL_smq_go_src(data)                                                 ((0x00000002&(data))>>1)
#define MD_SMQ_CNTL_get_smq_go(data)                                                 ((0x00000002&(data))>>1)
#define MD_SMQ_CNTL_write_data_shift                                                 (0)
#define MD_SMQ_CNTL_write_data_mask                                                  (0x00000001)
#define MD_SMQ_CNTL_write_data(data)                                                 (0x00000001&((data)<<0))
#define MD_SMQ_CNTL_write_data_src(data)                                             ((0x00000001&(data))>>0)
#define MD_SMQ_CNTL_get_write_data(data)                                             ((0x00000001&(data))>>0)


#define MD_SMQ_INT_STATUS                                                            0x9800B004
#define MD_SMQ_INT_STATUS_reg_addr                                                   "0x9800B004"
#define MD_SMQ_INT_STATUS_reg                                                        0x9800B004
#define set_MD_SMQ_INT_STATUS_reg(data)   (*((volatile unsigned int*) MD_SMQ_INT_STATUS_reg)=data)
#define get_MD_SMQ_INT_STATUS_reg   (*((volatile unsigned int*) MD_SMQ_INT_STATUS_reg))
#define MD_SMQ_INT_STATUS_inst_adr                                                   "0x0001"
#define MD_SMQ_INT_STATUS_inst                                                       0x0001
#define MD_SMQ_INT_STATUS_gsp_length_err_shift                                       (15)
#define MD_SMQ_INT_STATUS_gsp_length_err_mask                                        (0x00008000)
#define MD_SMQ_INT_STATUS_gsp_length_err(data)                                       (0x00008000&((data)<<15))
#define MD_SMQ_INT_STATUS_gsp_length_err_src(data)                                   ((0x00008000&(data))>>15)
#define MD_SMQ_INT_STATUS_get_gsp_length_err(data)                                   ((0x00008000&(data))>>15)
#define MD_SMQ_INT_STATUS_gsp_rx_thd_ints_shift                                      (14)
#define MD_SMQ_INT_STATUS_gsp_rx_thd_ints_mask                                       (0x00004000)
#define MD_SMQ_INT_STATUS_gsp_rx_thd_ints(data)                                      (0x00004000&((data)<<14))
#define MD_SMQ_INT_STATUS_gsp_rx_thd_ints_src(data)                                  ((0x00004000&(data))>>14)
#define MD_SMQ_INT_STATUS_get_gsp_rx_thd_ints(data)                                  ((0x00004000&(data))>>14)
#define MD_SMQ_INT_STATUS_gsp_txdat_thd_ints_shift                                   (13)
#define MD_SMQ_INT_STATUS_gsp_txdat_thd_ints_mask                                    (0x00002000)
#define MD_SMQ_INT_STATUS_gsp_txdat_thd_ints(data)                                   (0x00002000&((data)<<13))
#define MD_SMQ_INT_STATUS_gsp_txdat_thd_ints_src(data)                               ((0x00002000&(data))>>13)
#define MD_SMQ_INT_STATUS_get_gsp_txdat_thd_ints(data)                               ((0x00002000&(data))>>13)
#define MD_SMQ_INT_STATUS_gsp_txbasic_thd_ints_shift                                 (12)
#define MD_SMQ_INT_STATUS_gsp_txbasic_thd_ints_mask                                  (0x00001000)
#define MD_SMQ_INT_STATUS_gsp_txbasic_thd_ints(data)                                 (0x00001000&((data)<<12))
#define MD_SMQ_INT_STATUS_gsp_txbasic_thd_ints_src(data)                             ((0x00001000&(data))>>12)
#define MD_SMQ_INT_STATUS_get_gsp_txbasic_thd_ints(data)                             ((0x00001000&(data))>>12)
#define MD_SMQ_INT_STATUS_gsp_tx_thd_ints_shift                                      (11)
#define MD_SMQ_INT_STATUS_gsp_tx_thd_ints_mask                                       (0x00000800)
#define MD_SMQ_INT_STATUS_gsp_tx_thd_ints(data)                                      (0x00000800&((data)<<11))
#define MD_SMQ_INT_STATUS_gsp_tx_thd_ints_src(data)                                  ((0x00000800&(data))>>11)
#define MD_SMQ_INT_STATUS_get_gsp_tx_thd_ints(data)                                  ((0x00000800&(data))>>11)
#define MD_SMQ_INT_STATUS_smq_chksum_err_shift                                       (10)
#define MD_SMQ_INT_STATUS_smq_chksum_err_mask                                        (0x00000400)
#define MD_SMQ_INT_STATUS_smq_chksum_err(data)                                       (0x00000400&((data)<<10))
#define MD_SMQ_INT_STATUS_smq_chksum_err_src(data)                                   ((0x00000400&(data))>>10)
#define MD_SMQ_INT_STATUS_get_smq_chksum_err(data)                                   ((0x00000400&(data))>>10)
#define MD_SMQ_INT_STATUS_ur_length_err_shift                                        (9)
#define MD_SMQ_INT_STATUS_ur_length_err_mask                                         (0x00000200)
#define MD_SMQ_INT_STATUS_ur_length_err(data)                                        (0x00000200&((data)<<9))
#define MD_SMQ_INT_STATUS_ur_length_err_src(data)                                    ((0x00000200&(data))>>9)
#define MD_SMQ_INT_STATUS_get_ur_length_err(data)                                    ((0x00000200&(data))>>9)
#define MD_SMQ_INT_STATUS_ur_rx_timeout_shift                                        (8)
#define MD_SMQ_INT_STATUS_ur_rx_timeout_mask                                         (0x00000100)
#define MD_SMQ_INT_STATUS_ur_rx_timeout(data)                                        (0x00000100&((data)<<8))
#define MD_SMQ_INT_STATUS_ur_rx_timeout_src(data)                                    ((0x00000100&(data))>>8)
#define MD_SMQ_INT_STATUS_get_ur_rx_timeout(data)                                    ((0x00000100&(data))>>8)
#define MD_SMQ_INT_STATUS_ur_rx_thd_shift                                            (7)
#define MD_SMQ_INT_STATUS_ur_rx_thd_mask                                             (0x00000080)
#define MD_SMQ_INT_STATUS_ur_rx_thd(data)                                            (0x00000080&((data)<<7))
#define MD_SMQ_INT_STATUS_ur_rx_thd_src(data)                                        ((0x00000080&(data))>>7)
#define MD_SMQ_INT_STATUS_get_ur_rx_thd(data)                                        ((0x00000080&(data))>>7)
#define MD_SMQ_INT_STATUS_ur_tx_thd_shift                                            (6)
#define MD_SMQ_INT_STATUS_ur_tx_thd_mask                                             (0x00000040)
#define MD_SMQ_INT_STATUS_ur_tx_thd(data)                                            (0x00000040&((data)<<6))
#define MD_SMQ_INT_STATUS_ur_tx_thd_src(data)                                        ((0x00000040&(data))>>6)
#define MD_SMQ_INT_STATUS_get_ur_tx_thd(data)                                        ((0x00000040&(data))>>6)
#define MD_SMQ_INT_STATUS_smq_mode_2b4berr_shift                                     (5)
#define MD_SMQ_INT_STATUS_smq_mode_2b4berr_mask                                      (0x00000020)
#define MD_SMQ_INT_STATUS_smq_mode_2b4berr(data)                                     (0x00000020&((data)<<5))
#define MD_SMQ_INT_STATUS_smq_mode_2b4berr_src(data)                                 ((0x00000020&(data))>>5)
#define MD_SMQ_INT_STATUS_get_smq_mode_2b4berr(data)                                 ((0x00000020&(data))>>5)
#define MD_SMQ_INT_STATUS_fdma_done_shift                                            (4)
#define MD_SMQ_INT_STATUS_fdma_done_mask                                             (0x00000010)
#define MD_SMQ_INT_STATUS_fdma_done(data)                                            (0x00000010&((data)<<4))
#define MD_SMQ_INT_STATUS_fdma_done_src(data)                                        ((0x00000010&(data))>>4)
#define MD_SMQ_INT_STATUS_get_fdma_done(data)                                        ((0x00000010&(data))>>4)
#define MD_SMQ_INT_STATUS_smq_empty_shift                                            (3)
#define MD_SMQ_INT_STATUS_smq_empty_mask                                             (0x00000008)
#define MD_SMQ_INT_STATUS_smq_empty(data)                                            (0x00000008&((data)<<3))
#define MD_SMQ_INT_STATUS_smq_empty_src(data)                                        ((0x00000008&(data))>>3)
#define MD_SMQ_INT_STATUS_get_smq_empty(data)                                        ((0x00000008&(data))>>3)
#define MD_SMQ_INT_STATUS_smq_length_err_shift                                       (2)
#define MD_SMQ_INT_STATUS_smq_length_err_mask                                        (0x00000004)
#define MD_SMQ_INT_STATUS_smq_length_err(data)                                       (0x00000004&((data)<<2))
#define MD_SMQ_INT_STATUS_smq_length_err_src(data)                                   ((0x00000004&(data))>>2)
#define MD_SMQ_INT_STATUS_get_smq_length_err(data)                                   ((0x00000004&(data))>>2)
#define MD_SMQ_INT_STATUS_smq_inst_err_shift                                         (1)
#define MD_SMQ_INT_STATUS_smq_inst_err_mask                                          (0x00000002)
#define MD_SMQ_INT_STATUS_smq_inst_err(data)                                         (0x00000002&((data)<<1))
#define MD_SMQ_INT_STATUS_smq_inst_err_src(data)                                     ((0x00000002&(data))>>1)
#define MD_SMQ_INT_STATUS_get_smq_inst_err(data)                                     ((0x00000002&(data))>>1)
#define MD_SMQ_INT_STATUS_write_data_shift                                           (0)
#define MD_SMQ_INT_STATUS_write_data_mask                                            (0x00000001)
#define MD_SMQ_INT_STATUS_write_data(data)                                           (0x00000001&((data)<<0))
#define MD_SMQ_INT_STATUS_write_data_src(data)                                       ((0x00000001&(data))>>0)
#define MD_SMQ_INT_STATUS_get_write_data(data)                                       ((0x00000001&(data))>>0)


#define MD_SMQ_INT_ENABLE                                                            0x9800B008
#define MD_SMQ_INT_ENABLE_reg_addr                                                   "0x9800B008"
#define MD_SMQ_INT_ENABLE_reg                                                        0x9800B008
#define set_MD_SMQ_INT_ENABLE_reg(data)   (*((volatile unsigned int*) MD_SMQ_INT_ENABLE_reg)=data)
#define get_MD_SMQ_INT_ENABLE_reg   (*((volatile unsigned int*) MD_SMQ_INT_ENABLE_reg))
#define MD_SMQ_INT_ENABLE_inst_adr                                                   "0x0002"
#define MD_SMQ_INT_ENABLE_inst                                                       0x0002
#define MD_SMQ_INT_ENABLE_scpu_int_en_shift                                          (16)
#define MD_SMQ_INT_ENABLE_scpu_int_en_mask                                           (0x00010000)
#define MD_SMQ_INT_ENABLE_scpu_int_en(data)                                          (0x00010000&((data)<<16))
#define MD_SMQ_INT_ENABLE_scpu_int_en_src(data)                                      ((0x00010000&(data))>>16)
#define MD_SMQ_INT_ENABLE_get_scpu_int_en(data)                                      ((0x00010000&(data))>>16)
#define MD_SMQ_INT_ENABLE_gsp_length_err_en_shift                                    (15)
#define MD_SMQ_INT_ENABLE_gsp_length_err_en_mask                                     (0x00008000)
#define MD_SMQ_INT_ENABLE_gsp_length_err_en(data)                                    (0x00008000&((data)<<15))
#define MD_SMQ_INT_ENABLE_gsp_length_err_en_src(data)                                ((0x00008000&(data))>>15)
#define MD_SMQ_INT_ENABLE_get_gsp_length_err_en(data)                                ((0x00008000&(data))>>15)
#define MD_SMQ_INT_ENABLE_gsp_rx_thd_en_shift                                        (14)
#define MD_SMQ_INT_ENABLE_gsp_rx_thd_en_mask                                         (0x00004000)
#define MD_SMQ_INT_ENABLE_gsp_rx_thd_en(data)                                        (0x00004000&((data)<<14))
#define MD_SMQ_INT_ENABLE_gsp_rx_thd_en_src(data)                                    ((0x00004000&(data))>>14)
#define MD_SMQ_INT_ENABLE_get_gsp_rx_thd_en(data)                                    ((0x00004000&(data))>>14)
#define MD_SMQ_INT_ENABLE_gsp_txdat_thd_en_shift                                     (13)
#define MD_SMQ_INT_ENABLE_gsp_txdat_thd_en_mask                                      (0x00002000)
#define MD_SMQ_INT_ENABLE_gsp_txdat_thd_en(data)                                     (0x00002000&((data)<<13))
#define MD_SMQ_INT_ENABLE_gsp_txdat_thd_en_src(data)                                 ((0x00002000&(data))>>13)
#define MD_SMQ_INT_ENABLE_get_gsp_txdat_thd_en(data)                                 ((0x00002000&(data))>>13)
#define MD_SMQ_INT_ENABLE_gsp_txbasic_thd_en_shift                                   (12)
#define MD_SMQ_INT_ENABLE_gsp_txbasic_thd_en_mask                                    (0x00001000)
#define MD_SMQ_INT_ENABLE_gsp_txbasic_thd_en(data)                                   (0x00001000&((data)<<12))
#define MD_SMQ_INT_ENABLE_gsp_txbasic_thd_en_src(data)                               ((0x00001000&(data))>>12)
#define MD_SMQ_INT_ENABLE_get_gsp_txbasic_thd_en(data)                               ((0x00001000&(data))>>12)
#define MD_SMQ_INT_ENABLE_gsp_tx_thd_en_shift                                        (11)
#define MD_SMQ_INT_ENABLE_gsp_tx_thd_en_mask                                         (0x00000800)
#define MD_SMQ_INT_ENABLE_gsp_tx_thd_en(data)                                        (0x00000800&((data)<<11))
#define MD_SMQ_INT_ENABLE_gsp_tx_thd_en_src(data)                                    ((0x00000800&(data))>>11)
#define MD_SMQ_INT_ENABLE_get_gsp_tx_thd_en(data)                                    ((0x00000800&(data))>>11)
#define MD_SMQ_INT_ENABLE_smq_chksum_err_en_shift                                    (10)
#define MD_SMQ_INT_ENABLE_smq_chksum_err_en_mask                                     (0x00000400)
#define MD_SMQ_INT_ENABLE_smq_chksum_err_en(data)                                    (0x00000400&((data)<<10))
#define MD_SMQ_INT_ENABLE_smq_chksum_err_en_src(data)                                ((0x00000400&(data))>>10)
#define MD_SMQ_INT_ENABLE_get_smq_chksum_err_en(data)                                ((0x00000400&(data))>>10)
#define MD_SMQ_INT_ENABLE_ur_length_err_en_shift                                     (9)
#define MD_SMQ_INT_ENABLE_ur_length_err_en_mask                                      (0x00000200)
#define MD_SMQ_INT_ENABLE_ur_length_err_en(data)                                     (0x00000200&((data)<<9))
#define MD_SMQ_INT_ENABLE_ur_length_err_en_src(data)                                 ((0x00000200&(data))>>9)
#define MD_SMQ_INT_ENABLE_get_ur_length_err_en(data)                                 ((0x00000200&(data))>>9)
#define MD_SMQ_INT_ENABLE_ur_rx_timeout_en_shift                                     (8)
#define MD_SMQ_INT_ENABLE_ur_rx_timeout_en_mask                                      (0x00000100)
#define MD_SMQ_INT_ENABLE_ur_rx_timeout_en(data)                                     (0x00000100&((data)<<8))
#define MD_SMQ_INT_ENABLE_ur_rx_timeout_en_src(data)                                 ((0x00000100&(data))>>8)
#define MD_SMQ_INT_ENABLE_get_ur_rx_timeout_en(data)                                 ((0x00000100&(data))>>8)
#define MD_SMQ_INT_ENABLE_ur_rx_thd_en_shift                                         (7)
#define MD_SMQ_INT_ENABLE_ur_rx_thd_en_mask                                          (0x00000080)
#define MD_SMQ_INT_ENABLE_ur_rx_thd_en(data)                                         (0x00000080&((data)<<7))
#define MD_SMQ_INT_ENABLE_ur_rx_thd_en_src(data)                                     ((0x00000080&(data))>>7)
#define MD_SMQ_INT_ENABLE_get_ur_rx_thd_en(data)                                     ((0x00000080&(data))>>7)
#define MD_SMQ_INT_ENABLE_ur_tx_thd_en_shift                                         (6)
#define MD_SMQ_INT_ENABLE_ur_tx_thd_en_mask                                          (0x00000040)
#define MD_SMQ_INT_ENABLE_ur_tx_thd_en(data)                                         (0x00000040&((data)<<6))
#define MD_SMQ_INT_ENABLE_ur_tx_thd_en_src(data)                                     ((0x00000040&(data))>>6)
#define MD_SMQ_INT_ENABLE_get_ur_tx_thd_en(data)                                     ((0x00000040&(data))>>6)
#define MD_SMQ_INT_ENABLE_smq_mode_2b4b_err_en_shift                                 (5)
#define MD_SMQ_INT_ENABLE_smq_mode_2b4b_err_en_mask                                  (0x00000020)
#define MD_SMQ_INT_ENABLE_smq_mode_2b4b_err_en(data)                                 (0x00000020&((data)<<5))
#define MD_SMQ_INT_ENABLE_smq_mode_2b4b_err_en_src(data)                             ((0x00000020&(data))>>5)
#define MD_SMQ_INT_ENABLE_get_smq_mode_2b4b_err_en(data)                             ((0x00000020&(data))>>5)
#define MD_SMQ_INT_ENABLE_fdma_done_en_shift                                         (4)
#define MD_SMQ_INT_ENABLE_fdma_done_en_mask                                          (0x00000010)
#define MD_SMQ_INT_ENABLE_fdma_done_en(data)                                         (0x00000010&((data)<<4))
#define MD_SMQ_INT_ENABLE_fdma_done_en_src(data)                                     ((0x00000010&(data))>>4)
#define MD_SMQ_INT_ENABLE_get_fdma_done_en(data)                                     ((0x00000010&(data))>>4)
#define MD_SMQ_INT_ENABLE_smq_empty_en_shift                                         (3)
#define MD_SMQ_INT_ENABLE_smq_empty_en_mask                                          (0x00000008)
#define MD_SMQ_INT_ENABLE_smq_empty_en(data)                                         (0x00000008&((data)<<3))
#define MD_SMQ_INT_ENABLE_smq_empty_en_src(data)                                     ((0x00000008&(data))>>3)
#define MD_SMQ_INT_ENABLE_get_smq_empty_en(data)                                     ((0x00000008&(data))>>3)
#define MD_SMQ_INT_ENABLE_smq_length_err_en_shift                                    (2)
#define MD_SMQ_INT_ENABLE_smq_length_err_en_mask                                     (0x00000004)
#define MD_SMQ_INT_ENABLE_smq_length_err_en(data)                                    (0x00000004&((data)<<2))
#define MD_SMQ_INT_ENABLE_smq_length_err_en_src(data)                                ((0x00000004&(data))>>2)
#define MD_SMQ_INT_ENABLE_get_smq_length_err_en(data)                                ((0x00000004&(data))>>2)
#define MD_SMQ_INT_ENABLE_smq_inst_err_en_shift                                      (1)
#define MD_SMQ_INT_ENABLE_smq_inst_err_en_mask                                       (0x00000002)
#define MD_SMQ_INT_ENABLE_smq_inst_err_en(data)                                      (0x00000002&((data)<<1))
#define MD_SMQ_INT_ENABLE_smq_inst_err_en_src(data)                                  ((0x00000002&(data))>>1)
#define MD_SMQ_INT_ENABLE_get_smq_inst_err_en(data)                                  ((0x00000002&(data))>>1)
#define MD_SMQ_INT_ENABLE_write_data_shift                                           (0)
#define MD_SMQ_INT_ENABLE_write_data_mask                                            (0x00000001)
#define MD_SMQ_INT_ENABLE_write_data(data)                                           (0x00000001&((data)<<0))
#define MD_SMQ_INT_ENABLE_write_data_src(data)                                       ((0x00000001&(data))>>0)
#define MD_SMQ_INT_ENABLE_get_write_data(data)                                       ((0x00000001&(data))>>0)


#define MD_SMQBASE                                                                   0x9800B00C
#define MD_SMQBASE_reg_addr                                                          "0x9800B00C"
#define MD_SMQBASE_reg                                                               0x9800B00C
#define set_MD_SMQBASE_reg(data)   (*((volatile unsigned int*) MD_SMQBASE_reg)=data)
#define get_MD_SMQBASE_reg   (*((volatile unsigned int*) MD_SMQBASE_reg))
#define MD_SMQBASE_inst_adr                                                          "0x0003"
#define MD_SMQBASE_inst                                                              0x0003
#define MD_SMQBASE_smq_base_shift                                                    (4)
#define MD_SMQBASE_smq_base_mask                                                     (0x7FFFFFF0)
#define MD_SMQBASE_smq_base(data)                                                    (0x7FFFFFF0&((data)<<4))
#define MD_SMQBASE_smq_base_src(data)                                                ((0x7FFFFFF0&(data))>>4)
#define MD_SMQBASE_get_smq_base(data)                                                ((0x7FFFFFF0&(data))>>4)


#define MD_SMQLIMIT                                                                  0x9800B010
#define MD_SMQLIMIT_reg_addr                                                         "0x9800B010"
#define MD_SMQLIMIT_reg                                                              0x9800B010
#define set_MD_SMQLIMIT_reg(data)   (*((volatile unsigned int*) MD_SMQLIMIT_reg)=data)
#define get_MD_SMQLIMIT_reg   (*((volatile unsigned int*) MD_SMQLIMIT_reg))
#define MD_SMQLIMIT_inst_adr                                                         "0x0004"
#define MD_SMQLIMIT_inst                                                             0x0004
#define MD_SMQLIMIT_smq_limit_shift                                                  (4)
#define MD_SMQLIMIT_smq_limit_mask                                                   (0x7FFFFFF0)
#define MD_SMQLIMIT_smq_limit(data)                                                  (0x7FFFFFF0&((data)<<4))
#define MD_SMQLIMIT_smq_limit_src(data)                                              ((0x7FFFFFF0&(data))>>4)
#define MD_SMQLIMIT_get_smq_limit(data)                                              ((0x7FFFFFF0&(data))>>4)


#define MD_SMQRDPTR                                                                  0x9800B014
#define MD_SMQRDPTR_reg_addr                                                         "0x9800B014"
#define MD_SMQRDPTR_reg                                                              0x9800B014
#define set_MD_SMQRDPTR_reg(data)   (*((volatile unsigned int*) MD_SMQRDPTR_reg)=data)
#define get_MD_SMQRDPTR_reg   (*((volatile unsigned int*) MD_SMQRDPTR_reg))
#define MD_SMQRDPTR_inst_adr                                                         "0x0005"
#define MD_SMQRDPTR_inst                                                             0x0005
#define MD_SMQRDPTR_smq_rdptr_shift                                                  (4)
#define MD_SMQRDPTR_smq_rdptr_mask                                                   (0x7FFFFFF0)
#define MD_SMQRDPTR_smq_rdptr(data)                                                  (0x7FFFFFF0&((data)<<4))
#define MD_SMQRDPTR_smq_rdptr_src(data)                                              ((0x7FFFFFF0&(data))>>4)
#define MD_SMQRDPTR_get_smq_rdptr(data)                                              ((0x7FFFFFF0&(data))>>4)


#define MD_SMQWRPTR                                                                  0x9800B018
#define MD_SMQWRPTR_reg_addr                                                         "0x9800B018"
#define MD_SMQWRPTR_reg                                                              0x9800B018
#define set_MD_SMQWRPTR_reg(data)   (*((volatile unsigned int*) MD_SMQWRPTR_reg)=data)
#define get_MD_SMQWRPTR_reg   (*((volatile unsigned int*) MD_SMQWRPTR_reg))
#define MD_SMQWRPTR_inst_adr                                                         "0x0006"
#define MD_SMQWRPTR_inst                                                             0x0006
#define MD_SMQWRPTR_smq_wrptr_shift                                                  (4)
#define MD_SMQWRPTR_smq_wrptr_mask                                                   (0x7FFFFFF0)
#define MD_SMQWRPTR_smq_wrptr(data)                                                  (0x7FFFFFF0&((data)<<4))
#define MD_SMQWRPTR_smq_wrptr_src(data)                                              ((0x7FFFFFF0&(data))>>4)
#define MD_SMQWRPTR_get_smq_wrptr(data)                                              ((0x7FFFFFF0&(data))>>4)


#define MD_SMQFIFOSTATE                                                              0x9800B01C
#define MD_SMQFIFOSTATE_reg_addr                                                     "0x9800B01C"
#define MD_SMQFIFOSTATE_reg                                                          0x9800B01C
#define set_MD_SMQFIFOSTATE_reg(data)   (*((volatile unsigned int*) MD_SMQFIFOSTATE_reg)=data)
#define get_MD_SMQFIFOSTATE_reg   (*((volatile unsigned int*) MD_SMQFIFOSTATE_reg))
#define MD_SMQFIFOSTATE_inst_adr                                                     "0x0007"
#define MD_SMQFIFOSTATE_inst                                                         0x0007
#define MD_SMQFIFOSTATE_smq_inst_remain_shift                                        (0)
#define MD_SMQFIFOSTATE_smq_inst_remain_mask                                         (0x0000001F)
#define MD_SMQFIFOSTATE_smq_inst_remain(data)                                        (0x0000001F&((data)<<0))
#define MD_SMQFIFOSTATE_smq_inst_remain_src(data)                                    ((0x0000001F&(data))>>0)
#define MD_SMQFIFOSTATE_get_smq_inst_remain(data)                                    ((0x0000001F&(data))>>0)


#define MD_SMQ_INSTCNT                                                               0x9800B020
#define MD_SMQ_INSTCNT_reg_addr                                                      "0x9800B020"
#define MD_SMQ_INSTCNT_reg                                                           0x9800B020
#define set_MD_SMQ_INSTCNT_reg(data)   (*((volatile unsigned int*) MD_SMQ_INSTCNT_reg)=data)
#define get_MD_SMQ_INSTCNT_reg   (*((volatile unsigned int*) MD_SMQ_INSTCNT_reg))
#define MD_SMQ_INSTCNT_inst_adr                                                      "0x0008"
#define MD_SMQ_INSTCNT_inst                                                          0x0008
#define MD_SMQ_INSTCNT_smq_inst_cnt_shift                                            (0)
#define MD_SMQ_INSTCNT_smq_inst_cnt_mask                                             (0x0000FFFF)
#define MD_SMQ_INSTCNT_smq_inst_cnt(data)                                            (0x0000FFFF&((data)<<0))
#define MD_SMQ_INSTCNT_smq_inst_cnt_src(data)                                        ((0x0000FFFF&(data))>>0)
#define MD_SMQ_INSTCNT_get_smq_inst_cnt(data)                                        ((0x0000FFFF&(data))>>0)


#define MD_SMQ_CHKSUM                                                                0x9800B024
#define MD_SMQ_CHKSUM_reg_addr                                                       "0x9800B024"
#define MD_SMQ_CHKSUM_reg                                                            0x9800B024
#define set_MD_SMQ_CHKSUM_reg(data)   (*((volatile unsigned int*) MD_SMQ_CHKSUM_reg)=data)
#define get_MD_SMQ_CHKSUM_reg   (*((volatile unsigned int*) MD_SMQ_CHKSUM_reg))
#define MD_SMQ_CHKSUM_inst_adr                                                       "0x0009"
#define MD_SMQ_CHKSUM_inst                                                           0x0009
#define MD_SMQ_CHKSUM_smq_chksum_shift                                               (0)
#define MD_SMQ_CHKSUM_smq_chksum_mask                                                (0xFFFFFFFF)
#define MD_SMQ_CHKSUM_smq_chksum(data)                                               (0xFFFFFFFF&((data)<<0))
#define MD_SMQ_CHKSUM_smq_chksum_src(data)                                           ((0xFFFFFFFF&(data))>>0)
#define MD_SMQ_CHKSUM_get_smq_chksum(data)                                           ((0xFFFFFFFF&(data))>>0)


#define MD_VMQ_CNTL                                                                  0x9800B030
#define MD_VMQ_CNTL_reg_addr                                                         "0x9800B030"
#define MD_VMQ_CNTL_reg                                                              0x9800B030
#define set_MD_VMQ_CNTL_reg(data)   (*((volatile unsigned int*) MD_VMQ_CNTL_reg)=data)
#define get_MD_VMQ_CNTL_reg   (*((volatile unsigned int*) MD_VMQ_CNTL_reg))
#define MD_VMQ_CNTL_inst_adr                                                         "0x000C"
#define MD_VMQ_CNTL_inst                                                             0x000C
#define MD_VMQ_CNTL_vmq_idle_shift                                                   (3)
#define MD_VMQ_CNTL_vmq_idle_mask                                                    (0x00000008)
#define MD_VMQ_CNTL_vmq_idle(data)                                                   (0x00000008&((data)<<3))
#define MD_VMQ_CNTL_vmq_idle_src(data)                                               ((0x00000008&(data))>>3)
#define MD_VMQ_CNTL_get_vmq_idle(data)                                               ((0x00000008&(data))>>3)
#define MD_VMQ_CNTL_vmq_cmd_swap_shift                                               (2)
#define MD_VMQ_CNTL_vmq_cmd_swap_mask                                                (0x00000004)
#define MD_VMQ_CNTL_vmq_cmd_swap(data)                                               (0x00000004&((data)<<2))
#define MD_VMQ_CNTL_vmq_cmd_swap_src(data)                                           ((0x00000004&(data))>>2)
#define MD_VMQ_CNTL_get_vmq_cmd_swap(data)                                           ((0x00000004&(data))>>2)
#define MD_VMQ_CNTL_vmq_go_shift                                                     (1)
#define MD_VMQ_CNTL_vmq_go_mask                                                      (0x00000002)
#define MD_VMQ_CNTL_vmq_go(data)                                                     (0x00000002&((data)<<1))
#define MD_VMQ_CNTL_vmq_go_src(data)                                                 ((0x00000002&(data))>>1)
#define MD_VMQ_CNTL_get_vmq_go(data)                                                 ((0x00000002&(data))>>1)
#define MD_VMQ_CNTL_write_data_shift                                                 (0)
#define MD_VMQ_CNTL_write_data_mask                                                  (0x00000001)
#define MD_VMQ_CNTL_write_data(data)                                                 (0x00000001&((data)<<0))
#define MD_VMQ_CNTL_write_data_src(data)                                             ((0x00000001&(data))>>0)
#define MD_VMQ_CNTL_get_write_data(data)                                             ((0x00000001&(data))>>0)


#define MD_VMQ_INT_STATUS                                                            0x9800B034
#define MD_VMQ_INT_STATUS_reg_addr                                                   "0x9800B034"
#define MD_VMQ_INT_STATUS_reg                                                        0x9800B034
#define set_MD_VMQ_INT_STATUS_reg(data)   (*((volatile unsigned int*) MD_VMQ_INT_STATUS_reg)=data)
#define get_MD_VMQ_INT_STATUS_reg   (*((volatile unsigned int*) MD_VMQ_INT_STATUS_reg))
#define MD_VMQ_INT_STATUS_inst_adr                                                   "0x000D"
#define MD_VMQ_INT_STATUS_inst                                                       0x000D
#define MD_VMQ_INT_STATUS_vmq_chksum_err_shift                                       (5)
#define MD_VMQ_INT_STATUS_vmq_chksum_err_mask                                        (0x00000020)
#define MD_VMQ_INT_STATUS_vmq_chksum_err(data)                                       (0x00000020&((data)<<5))
#define MD_VMQ_INT_STATUS_vmq_chksum_err_src(data)                                   ((0x00000020&(data))>>5)
#define MD_VMQ_INT_STATUS_get_vmq_chksum_err(data)                                   ((0x00000020&(data))>>5)
#define MD_VMQ_INT_STATUS_vmq_mode_2b4berr_shift                                     (4)
#define MD_VMQ_INT_STATUS_vmq_mode_2b4berr_mask                                      (0x00000010)
#define MD_VMQ_INT_STATUS_vmq_mode_2b4berr(data)                                     (0x00000010&((data)<<4))
#define MD_VMQ_INT_STATUS_vmq_mode_2b4berr_src(data)                                 ((0x00000010&(data))>>4)
#define MD_VMQ_INT_STATUS_get_vmq_mode_2b4berr(data)                                 ((0x00000010&(data))>>4)
#define MD_VMQ_INT_STATUS_vmq_empty_shift                                            (3)
#define MD_VMQ_INT_STATUS_vmq_empty_mask                                             (0x00000008)
#define MD_VMQ_INT_STATUS_vmq_empty(data)                                            (0x00000008&((data)<<3))
#define MD_VMQ_INT_STATUS_vmq_empty_src(data)                                        ((0x00000008&(data))>>3)
#define MD_VMQ_INT_STATUS_get_vmq_empty(data)                                        ((0x00000008&(data))>>3)
#define MD_VMQ_INT_STATUS_vmq_length_err_shift                                       (2)
#define MD_VMQ_INT_STATUS_vmq_length_err_mask                                        (0x00000004)
#define MD_VMQ_INT_STATUS_vmq_length_err(data)                                       (0x00000004&((data)<<2))
#define MD_VMQ_INT_STATUS_vmq_length_err_src(data)                                   ((0x00000004&(data))>>2)
#define MD_VMQ_INT_STATUS_get_vmq_length_err(data)                                   ((0x00000004&(data))>>2)
#define MD_VMQ_INT_STATUS_vmq_inst_err_shift                                         (1)
#define MD_VMQ_INT_STATUS_vmq_inst_err_mask                                          (0x00000002)
#define MD_VMQ_INT_STATUS_vmq_inst_err(data)                                         (0x00000002&((data)<<1))
#define MD_VMQ_INT_STATUS_vmq_inst_err_src(data)                                     ((0x00000002&(data))>>1)
#define MD_VMQ_INT_STATUS_get_vmq_inst_err(data)                                     ((0x00000002&(data))>>1)
#define MD_VMQ_INT_STATUS_write_data_shift                                           (0)
#define MD_VMQ_INT_STATUS_write_data_mask                                            (0x00000001)
#define MD_VMQ_INT_STATUS_write_data(data)                                           (0x00000001&((data)<<0))
#define MD_VMQ_INT_STATUS_write_data_src(data)                                       ((0x00000001&(data))>>0)
#define MD_VMQ_INT_STATUS_get_write_data(data)                                       ((0x00000001&(data))>>0)


#define MD_VMQ_INT_ENABLE                                                            0x9800B038
#define MD_VMQ_INT_ENABLE_reg_addr                                                   "0x9800B038"
#define MD_VMQ_INT_ENABLE_reg                                                        0x9800B038
#define set_MD_VMQ_INT_ENABLE_reg(data)   (*((volatile unsigned int*) MD_VMQ_INT_ENABLE_reg)=data)
#define get_MD_VMQ_INT_ENABLE_reg   (*((volatile unsigned int*) MD_VMQ_INT_ENABLE_reg))
#define MD_VMQ_INT_ENABLE_inst_adr                                                   "0x000E"
#define MD_VMQ_INT_ENABLE_inst                                                       0x000E
#define MD_VMQ_INT_ENABLE_vcpu_int_en_shift                                          (6)
#define MD_VMQ_INT_ENABLE_vcpu_int_en_mask                                           (0x00000040)
#define MD_VMQ_INT_ENABLE_vcpu_int_en(data)                                          (0x00000040&((data)<<6))
#define MD_VMQ_INT_ENABLE_vcpu_int_en_src(data)                                      ((0x00000040&(data))>>6)
#define MD_VMQ_INT_ENABLE_get_vcpu_int_en(data)                                      ((0x00000040&(data))>>6)
#define MD_VMQ_INT_ENABLE_vmq_chksum_err_en_shift                                    (5)
#define MD_VMQ_INT_ENABLE_vmq_chksum_err_en_mask                                     (0x00000020)
#define MD_VMQ_INT_ENABLE_vmq_chksum_err_en(data)                                    (0x00000020&((data)<<5))
#define MD_VMQ_INT_ENABLE_vmq_chksum_err_en_src(data)                                ((0x00000020&(data))>>5)
#define MD_VMQ_INT_ENABLE_get_vmq_chksum_err_en(data)                                ((0x00000020&(data))>>5)
#define MD_VMQ_INT_ENABLE_vmq_mode_2b4b_err_en_shift                                 (4)
#define MD_VMQ_INT_ENABLE_vmq_mode_2b4b_err_en_mask                                  (0x00000010)
#define MD_VMQ_INT_ENABLE_vmq_mode_2b4b_err_en(data)                                 (0x00000010&((data)<<4))
#define MD_VMQ_INT_ENABLE_vmq_mode_2b4b_err_en_src(data)                             ((0x00000010&(data))>>4)
#define MD_VMQ_INT_ENABLE_get_vmq_mode_2b4b_err_en(data)                             ((0x00000010&(data))>>4)
#define MD_VMQ_INT_ENABLE_vmq_empty_en_shift                                         (3)
#define MD_VMQ_INT_ENABLE_vmq_empty_en_mask                                          (0x00000008)
#define MD_VMQ_INT_ENABLE_vmq_empty_en(data)                                         (0x00000008&((data)<<3))
#define MD_VMQ_INT_ENABLE_vmq_empty_en_src(data)                                     ((0x00000008&(data))>>3)
#define MD_VMQ_INT_ENABLE_get_vmq_empty_en(data)                                     ((0x00000008&(data))>>3)
#define MD_VMQ_INT_ENABLE_vmq_length_err_en_shift                                    (2)
#define MD_VMQ_INT_ENABLE_vmq_length_err_en_mask                                     (0x00000004)
#define MD_VMQ_INT_ENABLE_vmq_length_err_en(data)                                    (0x00000004&((data)<<2))
#define MD_VMQ_INT_ENABLE_vmq_length_err_en_src(data)                                ((0x00000004&(data))>>2)
#define MD_VMQ_INT_ENABLE_get_vmq_length_err_en(data)                                ((0x00000004&(data))>>2)
#define MD_VMQ_INT_ENABLE_vmq_inst_err_en_shift                                      (1)
#define MD_VMQ_INT_ENABLE_vmq_inst_err_en_mask                                       (0x00000002)
#define MD_VMQ_INT_ENABLE_vmq_inst_err_en(data)                                      (0x00000002&((data)<<1))
#define MD_VMQ_INT_ENABLE_vmq_inst_err_en_src(data)                                  ((0x00000002&(data))>>1)
#define MD_VMQ_INT_ENABLE_get_vmq_inst_err_en(data)                                  ((0x00000002&(data))>>1)
#define MD_VMQ_INT_ENABLE_write_data_shift                                           (0)
#define MD_VMQ_INT_ENABLE_write_data_mask                                            (0x00000001)
#define MD_VMQ_INT_ENABLE_write_data(data)                                           (0x00000001&((data)<<0))
#define MD_VMQ_INT_ENABLE_write_data_src(data)                                       ((0x00000001&(data))>>0)
#define MD_VMQ_INT_ENABLE_get_write_data(data)                                       ((0x00000001&(data))>>0)


#define MD_VMQBASE                                                                   0x9800B03C
#define MD_VMQBASE_reg_addr                                                          "0x9800B03C"
#define MD_VMQBASE_reg                                                               0x9800B03C
#define set_MD_VMQBASE_reg(data)   (*((volatile unsigned int*) MD_VMQBASE_reg)=data)
#define get_MD_VMQBASE_reg   (*((volatile unsigned int*) MD_VMQBASE_reg))
#define MD_VMQBASE_inst_adr                                                          "0x000F"
#define MD_VMQBASE_inst                                                              0x000F
#define MD_VMQBASE_vmq_base_shift                                                    (4)
#define MD_VMQBASE_vmq_base_mask                                                     (0x7FFFFFF0)
#define MD_VMQBASE_vmq_base(data)                                                    (0x7FFFFFF0&((data)<<4))
#define MD_VMQBASE_vmq_base_src(data)                                                ((0x7FFFFFF0&(data))>>4)
#define MD_VMQBASE_get_vmq_base(data)                                                ((0x7FFFFFF0&(data))>>4)


#define MD_VMQLIMIT                                                                  0x9800B040
#define MD_VMQLIMIT_reg_addr                                                         "0x9800B040"
#define MD_VMQLIMIT_reg                                                              0x9800B040
#define set_MD_VMQLIMIT_reg(data)   (*((volatile unsigned int*) MD_VMQLIMIT_reg)=data)
#define get_MD_VMQLIMIT_reg   (*((volatile unsigned int*) MD_VMQLIMIT_reg))
#define MD_VMQLIMIT_inst_adr                                                         "0x0010"
#define MD_VMQLIMIT_inst                                                             0x0010
#define MD_VMQLIMIT_vmq_limit_shift                                                  (4)
#define MD_VMQLIMIT_vmq_limit_mask                                                   (0x7FFFFFF0)
#define MD_VMQLIMIT_vmq_limit(data)                                                  (0x7FFFFFF0&((data)<<4))
#define MD_VMQLIMIT_vmq_limit_src(data)                                              ((0x7FFFFFF0&(data))>>4)
#define MD_VMQLIMIT_get_vmq_limit(data)                                              ((0x7FFFFFF0&(data))>>4)


#define MD_VMQRDPTR                                                                  0x9800B044
#define MD_VMQRDPTR_reg_addr                                                         "0x9800B044"
#define MD_VMQRDPTR_reg                                                              0x9800B044
#define set_MD_VMQRDPTR_reg(data)   (*((volatile unsigned int*) MD_VMQRDPTR_reg)=data)
#define get_MD_VMQRDPTR_reg   (*((volatile unsigned int*) MD_VMQRDPTR_reg))
#define MD_VMQRDPTR_inst_adr                                                         "0x0011"
#define MD_VMQRDPTR_inst                                                             0x0011
#define MD_VMQRDPTR_vmq_rdptr_shift                                                  (4)
#define MD_VMQRDPTR_vmq_rdptr_mask                                                   (0x7FFFFFF0)
#define MD_VMQRDPTR_vmq_rdptr(data)                                                  (0x7FFFFFF0&((data)<<4))
#define MD_VMQRDPTR_vmq_rdptr_src(data)                                              ((0x7FFFFFF0&(data))>>4)
#define MD_VMQRDPTR_get_vmq_rdptr(data)                                              ((0x7FFFFFF0&(data))>>4)


#define MD_VMQWRPTR                                                                  0x9800B048
#define MD_VMQWRPTR_reg_addr                                                         "0x9800B048"
#define MD_VMQWRPTR_reg                                                              0x9800B048
#define set_MD_VMQWRPTR_reg(data)   (*((volatile unsigned int*) MD_VMQWRPTR_reg)=data)
#define get_MD_VMQWRPTR_reg   (*((volatile unsigned int*) MD_VMQWRPTR_reg))
#define MD_VMQWRPTR_inst_adr                                                         "0x0012"
#define MD_VMQWRPTR_inst                                                             0x0012
#define MD_VMQWRPTR_vmq_wrptr_shift                                                  (4)
#define MD_VMQWRPTR_vmq_wrptr_mask                                                   (0x7FFFFFF0)
#define MD_VMQWRPTR_vmq_wrptr(data)                                                  (0x7FFFFFF0&((data)<<4))
#define MD_VMQWRPTR_vmq_wrptr_src(data)                                              ((0x7FFFFFF0&(data))>>4)
#define MD_VMQWRPTR_get_vmq_wrptr(data)                                              ((0x7FFFFFF0&(data))>>4)


#define MD_VMQFIFOSTATE                                                              0x9800B04C
#define MD_VMQFIFOSTATE_reg_addr                                                     "0x9800B04C"
#define MD_VMQFIFOSTATE_reg                                                          0x9800B04C
#define set_MD_VMQFIFOSTATE_reg(data)   (*((volatile unsigned int*) MD_VMQFIFOSTATE_reg)=data)
#define get_MD_VMQFIFOSTATE_reg   (*((volatile unsigned int*) MD_VMQFIFOSTATE_reg))
#define MD_VMQFIFOSTATE_inst_adr                                                     "0x0013"
#define MD_VMQFIFOSTATE_inst                                                         0x0013
#define MD_VMQFIFOSTATE_vmq_inst_remain_shift                                        (0)
#define MD_VMQFIFOSTATE_vmq_inst_remain_mask                                         (0x0000001F)
#define MD_VMQFIFOSTATE_vmq_inst_remain(data)                                        (0x0000001F&((data)<<0))
#define MD_VMQFIFOSTATE_vmq_inst_remain_src(data)                                    ((0x0000001F&(data))>>0)
#define MD_VMQFIFOSTATE_get_vmq_inst_remain(data)                                    ((0x0000001F&(data))>>0)


#define MD_VMQ_INSTCNT                                                               0x9800B050
#define MD_VMQ_INSTCNT_reg_addr                                                      "0x9800B050"
#define MD_VMQ_INSTCNT_reg                                                           0x9800B050
#define set_MD_VMQ_INSTCNT_reg(data)   (*((volatile unsigned int*) MD_VMQ_INSTCNT_reg)=data)
#define get_MD_VMQ_INSTCNT_reg   (*((volatile unsigned int*) MD_VMQ_INSTCNT_reg))
#define MD_VMQ_INSTCNT_inst_adr                                                      "0x0014"
#define MD_VMQ_INSTCNT_inst                                                          0x0014
#define MD_VMQ_INSTCNT_vmq_inst_cnt_shift                                            (0)
#define MD_VMQ_INSTCNT_vmq_inst_cnt_mask                                             (0x0000FFFF)
#define MD_VMQ_INSTCNT_vmq_inst_cnt(data)                                            (0x0000FFFF&((data)<<0))
#define MD_VMQ_INSTCNT_vmq_inst_cnt_src(data)                                        ((0x0000FFFF&(data))>>0)
#define MD_VMQ_INSTCNT_get_vmq_inst_cnt(data)                                        ((0x0000FFFF&(data))>>0)


#define MD_VMQ_CHKSUM                                                                0x9800B054
#define MD_VMQ_CHKSUM_reg_addr                                                       "0x9800B054"
#define MD_VMQ_CHKSUM_reg                                                            0x9800B054
#define set_MD_VMQ_CHKSUM_reg(data)   (*((volatile unsigned int*) MD_VMQ_CHKSUM_reg)=data)
#define get_MD_VMQ_CHKSUM_reg   (*((volatile unsigned int*) MD_VMQ_CHKSUM_reg))
#define MD_VMQ_CHKSUM_inst_adr                                                       "0x0015"
#define MD_VMQ_CHKSUM_inst                                                           0x0015
#define MD_VMQ_CHKSUM_vmq_chksum_shift                                               (0)
#define MD_VMQ_CHKSUM_vmq_chksum_mask                                                (0xFFFFFFFF)
#define MD_VMQ_CHKSUM_vmq_chksum(data)                                               (0xFFFFFFFF&((data)<<0))
#define MD_VMQ_CHKSUM_vmq_chksum_src(data)                                           ((0xFFFFFFFF&(data))>>0)
#define MD_VMQ_CHKSUM_get_vmq_chksum(data)                                           ((0xFFFFFFFF&(data))>>0)


#define MD_KMQ_CNTL                                                                  0x9800B060
#define MD_KMQ_CNTL_reg_addr                                                         "0x9800B060"
#define MD_KMQ_CNTL_reg                                                              0x9800B060
#define set_MD_KMQ_CNTL_reg(data)   (*((volatile unsigned int*) MD_KMQ_CNTL_reg)=data)
#define get_MD_KMQ_CNTL_reg   (*((volatile unsigned int*) MD_KMQ_CNTL_reg))
#define MD_KMQ_CNTL_inst_adr                                                         "0x0018"
#define MD_KMQ_CNTL_inst                                                             0x0018
#define MD_KMQ_CNTL_kmq_idle_shift                                                   (3)
#define MD_KMQ_CNTL_kmq_idle_mask                                                    (0x00000008)
#define MD_KMQ_CNTL_kmq_idle(data)                                                   (0x00000008&((data)<<3))
#define MD_KMQ_CNTL_kmq_idle_src(data)                                               ((0x00000008&(data))>>3)
#define MD_KMQ_CNTL_get_kmq_idle(data)                                               ((0x00000008&(data))>>3)
#define MD_KMQ_CNTL_kmq_cmd_swap_shift                                               (2)
#define MD_KMQ_CNTL_kmq_cmd_swap_mask                                                (0x00000004)
#define MD_KMQ_CNTL_kmq_cmd_swap(data)                                               (0x00000004&((data)<<2))
#define MD_KMQ_CNTL_kmq_cmd_swap_src(data)                                           ((0x00000004&(data))>>2)
#define MD_KMQ_CNTL_get_kmq_cmd_swap(data)                                           ((0x00000004&(data))>>2)
#define MD_KMQ_CNTL_kmq_go_shift                                                     (1)
#define MD_KMQ_CNTL_kmq_go_mask                                                      (0x00000002)
#define MD_KMQ_CNTL_kmq_go(data)                                                     (0x00000002&((data)<<1))
#define MD_KMQ_CNTL_kmq_go_src(data)                                                 ((0x00000002&(data))>>1)
#define MD_KMQ_CNTL_get_kmq_go(data)                                                 ((0x00000002&(data))>>1)
#define MD_KMQ_CNTL_write_data_shift                                                 (0)
#define MD_KMQ_CNTL_write_data_mask                                                  (0x00000001)
#define MD_KMQ_CNTL_write_data(data)                                                 (0x00000001&((data)<<0))
#define MD_KMQ_CNTL_write_data_src(data)                                             ((0x00000001&(data))>>0)
#define MD_KMQ_CNTL_get_write_data(data)                                             ((0x00000001&(data))>>0)


#define MD_KMQ_INT_STATUS                                                            0x9800B064
#define MD_KMQ_INT_STATUS_reg_addr                                                   "0x9800B064"
#define MD_KMQ_INT_STATUS_reg                                                        0x9800B064
#define set_MD_KMQ_INT_STATUS_reg(data)   (*((volatile unsigned int*) MD_KMQ_INT_STATUS_reg)=data)
#define get_MD_KMQ_INT_STATUS_reg   (*((volatile unsigned int*) MD_KMQ_INT_STATUS_reg))
#define MD_KMQ_INT_STATUS_inst_adr                                                   "0x0019"
#define MD_KMQ_INT_STATUS_inst                                                       0x0019
#define MD_KMQ_INT_STATUS_kmq_chksum_err_shift                                       (5)
#define MD_KMQ_INT_STATUS_kmq_chksum_err_mask                                        (0x00000020)
#define MD_KMQ_INT_STATUS_kmq_chksum_err(data)                                       (0x00000020&((data)<<5))
#define MD_KMQ_INT_STATUS_kmq_chksum_err_src(data)                                   ((0x00000020&(data))>>5)
#define MD_KMQ_INT_STATUS_get_kmq_chksum_err(data)                                   ((0x00000020&(data))>>5)
#define MD_KMQ_INT_STATUS_kmq_mode_2b4berr_shift                                     (4)
#define MD_KMQ_INT_STATUS_kmq_mode_2b4berr_mask                                      (0x00000010)
#define MD_KMQ_INT_STATUS_kmq_mode_2b4berr(data)                                     (0x00000010&((data)<<4))
#define MD_KMQ_INT_STATUS_kmq_mode_2b4berr_src(data)                                 ((0x00000010&(data))>>4)
#define MD_KMQ_INT_STATUS_get_kmq_mode_2b4berr(data)                                 ((0x00000010&(data))>>4)
#define MD_KMQ_INT_STATUS_kmq_empty_shift                                            (3)
#define MD_KMQ_INT_STATUS_kmq_empty_mask                                             (0x00000008)
#define MD_KMQ_INT_STATUS_kmq_empty(data)                                            (0x00000008&((data)<<3))
#define MD_KMQ_INT_STATUS_kmq_empty_src(data)                                        ((0x00000008&(data))>>3)
#define MD_KMQ_INT_STATUS_get_kmq_empty(data)                                        ((0x00000008&(data))>>3)
#define MD_KMQ_INT_STATUS_kmq_length_err_shift                                       (2)
#define MD_KMQ_INT_STATUS_kmq_length_err_mask                                        (0x00000004)
#define MD_KMQ_INT_STATUS_kmq_length_err(data)                                       (0x00000004&((data)<<2))
#define MD_KMQ_INT_STATUS_kmq_length_err_src(data)                                   ((0x00000004&(data))>>2)
#define MD_KMQ_INT_STATUS_get_kmq_length_err(data)                                   ((0x00000004&(data))>>2)
#define MD_KMQ_INT_STATUS_kmq_inst_err_shift                                         (1)
#define MD_KMQ_INT_STATUS_kmq_inst_err_mask                                          (0x00000002)
#define MD_KMQ_INT_STATUS_kmq_inst_err(data)                                         (0x00000002&((data)<<1))
#define MD_KMQ_INT_STATUS_kmq_inst_err_src(data)                                     ((0x00000002&(data))>>1)
#define MD_KMQ_INT_STATUS_get_kmq_inst_err(data)                                     ((0x00000002&(data))>>1)
#define MD_KMQ_INT_STATUS_write_data_shift                                           (0)
#define MD_KMQ_INT_STATUS_write_data_mask                                            (0x00000001)
#define MD_KMQ_INT_STATUS_write_data(data)                                           (0x00000001&((data)<<0))
#define MD_KMQ_INT_STATUS_write_data_src(data)                                       ((0x00000001&(data))>>0)
#define MD_KMQ_INT_STATUS_get_write_data(data)                                       ((0x00000001&(data))>>0)


#define MD_KMQ_INT_ENABLE                                                            0x9800B068
#define MD_KMQ_INT_ENABLE_reg_addr                                                   "0x9800B068"
#define MD_KMQ_INT_ENABLE_reg                                                        0x9800B068
#define set_MD_KMQ_INT_ENABLE_reg(data)   (*((volatile unsigned int*) MD_KMQ_INT_ENABLE_reg)=data)
#define get_MD_KMQ_INT_ENABLE_reg   (*((volatile unsigned int*) MD_KMQ_INT_ENABLE_reg))
#define MD_KMQ_INT_ENABLE_inst_adr                                                   "0x001A"
#define MD_KMQ_INT_ENABLE_inst                                                       0x001A
#define MD_KMQ_INT_ENABLE_kcpu_int_en_shift                                          (6)
#define MD_KMQ_INT_ENABLE_kcpu_int_en_mask                                           (0x00000040)
#define MD_KMQ_INT_ENABLE_kcpu_int_en(data)                                          (0x00000040&((data)<<6))
#define MD_KMQ_INT_ENABLE_kcpu_int_en_src(data)                                      ((0x00000040&(data))>>6)
#define MD_KMQ_INT_ENABLE_get_kcpu_int_en(data)                                      ((0x00000040&(data))>>6)
#define MD_KMQ_INT_ENABLE_kmq_chksum_err_en_shift                                    (5)
#define MD_KMQ_INT_ENABLE_kmq_chksum_err_en_mask                                     (0x00000020)
#define MD_KMQ_INT_ENABLE_kmq_chksum_err_en(data)                                    (0x00000020&((data)<<5))
#define MD_KMQ_INT_ENABLE_kmq_chksum_err_en_src(data)                                ((0x00000020&(data))>>5)
#define MD_KMQ_INT_ENABLE_get_kmq_chksum_err_en(data)                                ((0x00000020&(data))>>5)
#define MD_KMQ_INT_ENABLE_kmq_mode_2b4b_err_en_shift                                 (4)
#define MD_KMQ_INT_ENABLE_kmq_mode_2b4b_err_en_mask                                  (0x00000010)
#define MD_KMQ_INT_ENABLE_kmq_mode_2b4b_err_en(data)                                 (0x00000010&((data)<<4))
#define MD_KMQ_INT_ENABLE_kmq_mode_2b4b_err_en_src(data)                             ((0x00000010&(data))>>4)
#define MD_KMQ_INT_ENABLE_get_kmq_mode_2b4b_err_en(data)                             ((0x00000010&(data))>>4)
#define MD_KMQ_INT_ENABLE_kmq_empty_en_shift                                         (3)
#define MD_KMQ_INT_ENABLE_kmq_empty_en_mask                                          (0x00000008)
#define MD_KMQ_INT_ENABLE_kmq_empty_en(data)                                         (0x00000008&((data)<<3))
#define MD_KMQ_INT_ENABLE_kmq_empty_en_src(data)                                     ((0x00000008&(data))>>3)
#define MD_KMQ_INT_ENABLE_get_kmq_empty_en(data)                                     ((0x00000008&(data))>>3)
#define MD_KMQ_INT_ENABLE_kmq_length_err_en_shift                                    (2)
#define MD_KMQ_INT_ENABLE_kmq_length_err_en_mask                                     (0x00000004)
#define MD_KMQ_INT_ENABLE_kmq_length_err_en(data)                                    (0x00000004&((data)<<2))
#define MD_KMQ_INT_ENABLE_kmq_length_err_en_src(data)                                ((0x00000004&(data))>>2)
#define MD_KMQ_INT_ENABLE_get_kmq_length_err_en(data)                                ((0x00000004&(data))>>2)
#define MD_KMQ_INT_ENABLE_kmq_inst_err_en_shift                                      (1)
#define MD_KMQ_INT_ENABLE_kmq_inst_err_en_mask                                       (0x00000002)
#define MD_KMQ_INT_ENABLE_kmq_inst_err_en(data)                                      (0x00000002&((data)<<1))
#define MD_KMQ_INT_ENABLE_kmq_inst_err_en_src(data)                                  ((0x00000002&(data))>>1)
#define MD_KMQ_INT_ENABLE_get_kmq_inst_err_en(data)                                  ((0x00000002&(data))>>1)
#define MD_KMQ_INT_ENABLE_write_data_shift                                           (0)
#define MD_KMQ_INT_ENABLE_write_data_mask                                            (0x00000001)
#define MD_KMQ_INT_ENABLE_write_data(data)                                           (0x00000001&((data)<<0))
#define MD_KMQ_INT_ENABLE_write_data_src(data)                                       ((0x00000001&(data))>>0)
#define MD_KMQ_INT_ENABLE_get_write_data(data)                                       ((0x00000001&(data))>>0)


#define MD_KMQBASE                                                                   0x9800B06C
#define MD_KMQBASE_reg_addr                                                          "0x9800B06C"
#define MD_KMQBASE_reg                                                               0x9800B06C
#define set_MD_KMQBASE_reg(data)   (*((volatile unsigned int*) MD_KMQBASE_reg)=data)
#define get_MD_KMQBASE_reg   (*((volatile unsigned int*) MD_KMQBASE_reg))
#define MD_KMQBASE_inst_adr                                                          "0x001B"
#define MD_KMQBASE_inst                                                              0x001B
#define MD_KMQBASE_kmq_base_shift                                                    (4)
#define MD_KMQBASE_kmq_base_mask                                                     (0x7FFFFFF0)
#define MD_KMQBASE_kmq_base(data)                                                    (0x7FFFFFF0&((data)<<4))
#define MD_KMQBASE_kmq_base_src(data)                                                ((0x7FFFFFF0&(data))>>4)
#define MD_KMQBASE_get_kmq_base(data)                                                ((0x7FFFFFF0&(data))>>4)


#define MD_KMQLIMIT                                                                  0x9800B070
#define MD_KMQLIMIT_reg_addr                                                         "0x9800B070"
#define MD_KMQLIMIT_reg                                                              0x9800B070
#define set_MD_KMQLIMIT_reg(data)   (*((volatile unsigned int*) MD_KMQLIMIT_reg)=data)
#define get_MD_KMQLIMIT_reg   (*((volatile unsigned int*) MD_KMQLIMIT_reg))
#define MD_KMQLIMIT_inst_adr                                                         "0x001C"
#define MD_KMQLIMIT_inst                                                             0x001C
#define MD_KMQLIMIT_kmq_limit_shift                                                  (4)
#define MD_KMQLIMIT_kmq_limit_mask                                                   (0x7FFFFFF0)
#define MD_KMQLIMIT_kmq_limit(data)                                                  (0x7FFFFFF0&((data)<<4))
#define MD_KMQLIMIT_kmq_limit_src(data)                                              ((0x7FFFFFF0&(data))>>4)
#define MD_KMQLIMIT_get_kmq_limit(data)                                              ((0x7FFFFFF0&(data))>>4)


#define MD_KMQRDPTR                                                                  0x9800B074
#define MD_KMQRDPTR_reg_addr                                                         "0x9800B074"
#define MD_KMQRDPTR_reg                                                              0x9800B074
#define set_MD_KMQRDPTR_reg(data)   (*((volatile unsigned int*) MD_KMQRDPTR_reg)=data)
#define get_MD_KMQRDPTR_reg   (*((volatile unsigned int*) MD_KMQRDPTR_reg))
#define MD_KMQRDPTR_inst_adr                                                         "0x001D"
#define MD_KMQRDPTR_inst                                                             0x001D
#define MD_KMQRDPTR_kmq_rdptr_shift                                                  (4)
#define MD_KMQRDPTR_kmq_rdptr_mask                                                   (0x7FFFFFF0)
#define MD_KMQRDPTR_kmq_rdptr(data)                                                  (0x7FFFFFF0&((data)<<4))
#define MD_KMQRDPTR_kmq_rdptr_src(data)                                              ((0x7FFFFFF0&(data))>>4)
#define MD_KMQRDPTR_get_kmq_rdptr(data)                                              ((0x7FFFFFF0&(data))>>4)


#define MD_KMQWRPTR                                                                  0x9800B078
#define MD_KMQWRPTR_reg_addr                                                         "0x9800B078"
#define MD_KMQWRPTR_reg                                                              0x9800B078
#define set_MD_KMQWRPTR_reg(data)   (*((volatile unsigned int*) MD_KMQWRPTR_reg)=data)
#define get_MD_KMQWRPTR_reg   (*((volatile unsigned int*) MD_KMQWRPTR_reg))
#define MD_KMQWRPTR_inst_adr                                                         "0x001E"
#define MD_KMQWRPTR_inst                                                             0x001E
#define MD_KMQWRPTR_kmq_wrptr_shift                                                  (4)
#define MD_KMQWRPTR_kmq_wrptr_mask                                                   (0x7FFFFFF0)
#define MD_KMQWRPTR_kmq_wrptr(data)                                                  (0x7FFFFFF0&((data)<<4))
#define MD_KMQWRPTR_kmq_wrptr_src(data)                                              ((0x7FFFFFF0&(data))>>4)
#define MD_KMQWRPTR_get_kmq_wrptr(data)                                              ((0x7FFFFFF0&(data))>>4)


#define MD_KMQFIFOSTATE                                                              0x9800B07C
#define MD_KMQFIFOSTATE_reg_addr                                                     "0x9800B07C"
#define MD_KMQFIFOSTATE_reg                                                          0x9800B07C
#define set_MD_KMQFIFOSTATE_reg(data)   (*((volatile unsigned int*) MD_KMQFIFOSTATE_reg)=data)
#define get_MD_KMQFIFOSTATE_reg   (*((volatile unsigned int*) MD_KMQFIFOSTATE_reg))
#define MD_KMQFIFOSTATE_inst_adr                                                     "0x001F"
#define MD_KMQFIFOSTATE_inst                                                         0x001F
#define MD_KMQFIFOSTATE_kmq_inst_remain_shift                                        (0)
#define MD_KMQFIFOSTATE_kmq_inst_remain_mask                                         (0x0000001F)
#define MD_KMQFIFOSTATE_kmq_inst_remain(data)                                        (0x0000001F&((data)<<0))
#define MD_KMQFIFOSTATE_kmq_inst_remain_src(data)                                    ((0x0000001F&(data))>>0)
#define MD_KMQFIFOSTATE_get_kmq_inst_remain(data)                                    ((0x0000001F&(data))>>0)


#define MD_KMQ_INSTCNT                                                               0x9800B080
#define MD_KMQ_INSTCNT_reg_addr                                                      "0x9800B080"
#define MD_KMQ_INSTCNT_reg                                                           0x9800B080
#define set_MD_KMQ_INSTCNT_reg(data)   (*((volatile unsigned int*) MD_KMQ_INSTCNT_reg)=data)
#define get_MD_KMQ_INSTCNT_reg   (*((volatile unsigned int*) MD_KMQ_INSTCNT_reg))
#define MD_KMQ_INSTCNT_inst_adr                                                      "0x0020"
#define MD_KMQ_INSTCNT_inst                                                          0x0020
#define MD_KMQ_INSTCNT_kmq_inst_cnt_shift                                            (0)
#define MD_KMQ_INSTCNT_kmq_inst_cnt_mask                                             (0x0000FFFF)
#define MD_KMQ_INSTCNT_kmq_inst_cnt(data)                                            (0x0000FFFF&((data)<<0))
#define MD_KMQ_INSTCNT_kmq_inst_cnt_src(data)                                        ((0x0000FFFF&(data))>>0)
#define MD_KMQ_INSTCNT_get_kmq_inst_cnt(data)                                        ((0x0000FFFF&(data))>>0)


#define MD_KMQ_CHKSUM                                                                0x9800B084
#define MD_KMQ_CHKSUM_reg_addr                                                       "0x9800B084"
#define MD_KMQ_CHKSUM_reg                                                            0x9800B084
#define set_MD_KMQ_CHKSUM_reg(data)   (*((volatile unsigned int*) MD_KMQ_CHKSUM_reg)=data)
#define get_MD_KMQ_CHKSUM_reg   (*((volatile unsigned int*) MD_KMQ_CHKSUM_reg))
#define MD_KMQ_CHKSUM_inst_adr                                                       "0x0021"
#define MD_KMQ_CHKSUM_inst                                                           0x0021
#define MD_KMQ_CHKSUM_kmq_chksum_shift                                               (0)
#define MD_KMQ_CHKSUM_kmq_chksum_mask                                                (0xFFFFFFFF)
#define MD_KMQ_CHKSUM_kmq_chksum(data)                                               (0xFFFFFFFF&((data)<<0))
#define MD_KMQ_CHKSUM_kmq_chksum_src(data)                                           ((0xFFFFFFFF&(data))>>0)
#define MD_KMQ_CHKSUM_get_kmq_chksum(data)                                           ((0xFFFFFFFF&(data))>>0)


#define MD_DBG                                                                       0x9800B0D0
#define MD_DBG_reg_addr                                                              "0x9800B0D0"
#define MD_DBG_reg                                                                   0x9800B0D0
#define set_MD_DBG_reg(data)   (*((volatile unsigned int*) MD_DBG_reg)=data)
#define get_MD_DBG_reg   (*((volatile unsigned int*) MD_DBG_reg))
#define MD_DBG_inst_adr                                                              "0x0034"
#define MD_DBG_inst                                                                  0x0034
#define MD_DBG_md_dbg_sel1_shift                                                     (8)
#define MD_DBG_md_dbg_sel1_mask                                                      (0x00007F00)
#define MD_DBG_md_dbg_sel1(data)                                                     (0x00007F00&((data)<<8))
#define MD_DBG_md_dbg_sel1_src(data)                                                 ((0x00007F00&(data))>>8)
#define MD_DBG_get_md_dbg_sel1(data)                                                 ((0x00007F00&(data))>>8)
#define MD_DBG_md_dbg_sel0_shift                                                     (1)
#define MD_DBG_md_dbg_sel0_mask                                                      (0x000000FE)
#define MD_DBG_md_dbg_sel0(data)                                                     (0x000000FE&((data)<<1))
#define MD_DBG_md_dbg_sel0_src(data)                                                 ((0x000000FE&(data))>>1)
#define MD_DBG_get_md_dbg_sel0(data)                                                 ((0x000000FE&(data))>>1)
#define MD_DBG_md_dbg_enable_shift                                                   (0)
#define MD_DBG_md_dbg_enable_mask                                                    (0x00000001)
#define MD_DBG_md_dbg_enable(data)                                                   (0x00000001&((data)<<0))
#define MD_DBG_md_dbg_enable_src(data)                                               ((0x00000001&(data))>>0)
#define MD_DBG_get_md_dbg_enable(data)                                               ((0x00000001&(data))>>0)


#define MD_FDMA_DDR_SADDR                                                            0x9800B088
#define MD_FDMA_DDR_SADDR_reg_addr                                                   "0x9800B088"
#define MD_FDMA_DDR_SADDR_reg                                                        0x9800B088
#define set_MD_FDMA_DDR_SADDR_reg(data)   (*((volatile unsigned int*) MD_FDMA_DDR_SADDR_reg)=data)
#define get_MD_FDMA_DDR_SADDR_reg   (*((volatile unsigned int*) MD_FDMA_DDR_SADDR_reg))
#define MD_FDMA_DDR_SADDR_inst_adr                                                   "0x0022"
#define MD_FDMA_DDR_SADDR_inst                                                       0x0022
#define MD_FDMA_DDR_SADDR_fdma_ddr_saddr_shift                                       (0)
#define MD_FDMA_DDR_SADDR_fdma_ddr_saddr_mask                                        (0x7FFFFFFF)
#define MD_FDMA_DDR_SADDR_fdma_ddr_saddr(data)                                       (0x7FFFFFFF&((data)<<0))
#define MD_FDMA_DDR_SADDR_fdma_ddr_saddr_src(data)                                   ((0x7FFFFFFF&(data))>>0)
#define MD_FDMA_DDR_SADDR_get_fdma_ddr_saddr(data)                                   ((0x7FFFFFFF&(data))>>0)


#define MD_FDMA_FL_SADDR                                                             0x9800B08c
#define MD_FDMA_FL_SADDR_reg_addr                                                    "0x9800B08C"
#define MD_FDMA_FL_SADDR_reg                                                         0x9800B08C
#define set_MD_FDMA_FL_SADDR_reg(data)   (*((volatile unsigned int*) MD_FDMA_FL_SADDR_reg)=data)
#define get_MD_FDMA_FL_SADDR_reg   (*((volatile unsigned int*) MD_FDMA_FL_SADDR_reg))
#define MD_FDMA_FL_SADDR_inst_adr                                                    "0x0023"
#define MD_FDMA_FL_SADDR_inst                                                        0x0023
#define MD_FDMA_FL_SADDR_fdma_fl_saddr_shift                                         (0)
#define MD_FDMA_FL_SADDR_fdma_fl_saddr_mask                                          (0x01FFFFFF)
#define MD_FDMA_FL_SADDR_fdma_fl_saddr(data)                                         (0x01FFFFFF&((data)<<0))
#define MD_FDMA_FL_SADDR_fdma_fl_saddr_src(data)                                     ((0x01FFFFFF&(data))>>0)
#define MD_FDMA_FL_SADDR_get_fdma_fl_saddr(data)                                     ((0x01FFFFFF&(data))>>0)


#define MD_FDMA_CTRL2                                                                0x9800B090
#define MD_FDMA_CTRL2_reg_addr                                                       "0x9800B090"
#define MD_FDMA_CTRL2_reg                                                            0x9800B090
#define set_MD_FDMA_CTRL2_reg(data)   (*((volatile unsigned int*) MD_FDMA_CTRL2_reg)=data)
#define get_MD_FDMA_CTRL2_reg   (*((volatile unsigned int*) MD_FDMA_CTRL2_reg))
#define MD_FDMA_CTRL2_inst_adr                                                       "0x0024"
#define MD_FDMA_CTRL2_inst                                                           0x0024
#define MD_FDMA_CTRL2_fl_cp_en_shift                                                 (30)
#define MD_FDMA_CTRL2_fl_cp_en_mask                                                  (0x40000000)
#define MD_FDMA_CTRL2_fl_cp_en(data)                                                 (0x40000000&((data)<<30))
#define MD_FDMA_CTRL2_fl_cp_en_src(data)                                             ((0x40000000&(data))>>30)
#define MD_FDMA_CTRL2_get_fl_cp_en(data)                                             ((0x40000000&(data))>>30)
#define MD_FDMA_CTRL2_fl_mapping_mode_shift                                          (29)
#define MD_FDMA_CTRL2_fl_mapping_mode_mask                                           (0x20000000)
#define MD_FDMA_CTRL2_fl_mapping_mode(data)                                          (0x20000000&((data)<<29))
#define MD_FDMA_CTRL2_fl_mapping_mode_src(data)                                      ((0x20000000&(data))>>29)
#define MD_FDMA_CTRL2_get_fl_mapping_mode(data)                                      ((0x20000000&(data))>>29)
#define MD_FDMA_CTRL2_fdma_swap_shift                                                (28)
#define MD_FDMA_CTRL2_fdma_swap_mask                                                 (0x10000000)
#define MD_FDMA_CTRL2_fdma_swap(data)                                                (0x10000000&((data)<<28))
#define MD_FDMA_CTRL2_fdma_swap_src(data)                                            ((0x10000000&(data))>>28)
#define MD_FDMA_CTRL2_get_fdma_swap(data)                                            ((0x10000000&(data))>>28)
#define MD_FDMA_CTRL2_fdma_max_xfer_shift                                            (26)
#define MD_FDMA_CTRL2_fdma_max_xfer_mask                                             (0x0C000000)
#define MD_FDMA_CTRL2_fdma_max_xfer(data)                                            (0x0C000000&((data)<<26))
#define MD_FDMA_CTRL2_fdma_max_xfer_src(data)                                        ((0x0C000000&(data))>>26)
#define MD_FDMA_CTRL2_get_fdma_max_xfer(data)                                        ((0x0C000000&(data))>>26)
#define MD_FDMA_CTRL2_fdma_dir_shift                                                 (25)
#define MD_FDMA_CTRL2_fdma_dir_mask                                                  (0x02000000)
#define MD_FDMA_CTRL2_fdma_dir(data)                                                 (0x02000000&((data)<<25))
#define MD_FDMA_CTRL2_fdma_dir_src(data)                                             ((0x02000000&(data))>>25)
#define MD_FDMA_CTRL2_get_fdma_dir(data)                                             ((0x02000000&(data))>>25)
#define MD_FDMA_CTRL2_fdma_length_shift                                              (0)
#define MD_FDMA_CTRL2_fdma_length_mask                                               (0x01FFFFFF)
#define MD_FDMA_CTRL2_fdma_length(data)                                              (0x01FFFFFF&((data)<<0))
#define MD_FDMA_CTRL2_fdma_length_src(data)                                          ((0x01FFFFFF&(data))>>0)
#define MD_FDMA_CTRL2_get_fdma_length(data)                                          ((0x01FFFFFF&(data))>>0)


#define MD_FDMA_CTRL1                                                                0x9800B094
#define MD_FDMA_CTRL1_reg_addr                                                       "0x9800B094"
#define MD_FDMA_CTRL1_reg                                                            0x9800B094
#define set_MD_FDMA_CTRL1_reg(data)   (*((volatile unsigned int*) MD_FDMA_CTRL1_reg)=data)
#define get_MD_FDMA_CTRL1_reg   (*((volatile unsigned int*) MD_FDMA_CTRL1_reg))
#define MD_FDMA_CTRL1_inst_adr                                                       "0x0025"
#define MD_FDMA_CTRL1_inst                                                           0x0025
#define MD_FDMA_CTRL1_write_en2_shift                                                (3)
#define MD_FDMA_CTRL1_write_en2_mask                                                 (0x00000008)
#define MD_FDMA_CTRL1_write_en2(data)                                                (0x00000008&((data)<<3))
#define MD_FDMA_CTRL1_write_en2_src(data)                                            ((0x00000008&(data))>>3)
#define MD_FDMA_CTRL1_get_write_en2(data)                                            ((0x00000008&(data))>>3)
#define MD_FDMA_CTRL1_fdma_stop_shift                                                (2)
#define MD_FDMA_CTRL1_fdma_stop_mask                                                 (0x00000004)
#define MD_FDMA_CTRL1_fdma_stop(data)                                                (0x00000004&((data)<<2))
#define MD_FDMA_CTRL1_fdma_stop_src(data)                                            ((0x00000004&(data))>>2)
#define MD_FDMA_CTRL1_get_fdma_stop(data)                                            ((0x00000004&(data))>>2)
#define MD_FDMA_CTRL1_write_en1_shift                                                (1)
#define MD_FDMA_CTRL1_write_en1_mask                                                 (0x00000002)
#define MD_FDMA_CTRL1_write_en1(data)                                                (0x00000002&((data)<<1))
#define MD_FDMA_CTRL1_write_en1_src(data)                                            ((0x00000002&(data))>>1)
#define MD_FDMA_CTRL1_get_write_en1(data)                                            ((0x00000002&(data))>>1)
#define MD_FDMA_CTRL1_fdma_go_shift                                                  (0)
#define MD_FDMA_CTRL1_fdma_go_mask                                                   (0x00000001)
#define MD_FDMA_CTRL1_fdma_go(data)                                                  (0x00000001&((data)<<0))
#define MD_FDMA_CTRL1_fdma_go_src(data)                                              ((0x00000001&(data))>>0)
#define MD_FDMA_CTRL1_get_fdma_go(data)                                              ((0x00000001&(data))>>0)


#define MD_UR_TXBASE                                                                 0x9800B0A4
#define MD_UR_TXBASE_reg_addr                                                        "0x9800B0A4"
#define MD_UR_TXBASE_reg                                                             0x9800B0A4
#define set_MD_UR_TXBASE_reg(data)   (*((volatile unsigned int*) MD_UR_TXBASE_reg)=data)
#define get_MD_UR_TXBASE_reg   (*((volatile unsigned int*) MD_UR_TXBASE_reg))
#define MD_UR_TXBASE_inst_adr                                                        "0x0029"
#define MD_UR_TXBASE_inst                                                            0x0029
#define MD_UR_TXBASE_tx_base_shift                                                   (3)
#define MD_UR_TXBASE_tx_base_mask                                                    (0x7FFFFFF8)
#define MD_UR_TXBASE_tx_base(data)                                                   (0x7FFFFFF8&((data)<<3))
#define MD_UR_TXBASE_tx_base_src(data)                                               ((0x7FFFFFF8&(data))>>3)
#define MD_UR_TXBASE_get_tx_base(data)                                               ((0x7FFFFFF8&(data))>>3)


#define MD_UR_TXLIMIT                                                                0x9800B0A8
#define MD_UR_TXLIMIT_reg_addr                                                       "0x9800B0A8"
#define MD_UR_TXLIMIT_reg                                                            0x9800B0A8
#define set_MD_UR_TXLIMIT_reg(data)   (*((volatile unsigned int*) MD_UR_TXLIMIT_reg)=data)
#define get_MD_UR_TXLIMIT_reg   (*((volatile unsigned int*) MD_UR_TXLIMIT_reg))
#define MD_UR_TXLIMIT_inst_adr                                                       "0x002A"
#define MD_UR_TXLIMIT_inst                                                           0x002A
#define MD_UR_TXLIMIT_tx_limit_shift                                                 (3)
#define MD_UR_TXLIMIT_tx_limit_mask                                                  (0x7FFFFFF8)
#define MD_UR_TXLIMIT_tx_limit(data)                                                 (0x7FFFFFF8&((data)<<3))
#define MD_UR_TXLIMIT_tx_limit_src(data)                                             ((0x7FFFFFF8&(data))>>3)
#define MD_UR_TXLIMIT_get_tx_limit(data)                                             ((0x7FFFFFF8&(data))>>3)


#define MD_UR_TXWRPTR                                                                0x9800B0AC
#define MD_UR_TXWRPTR_reg_addr                                                       "0x9800B0AC"
#define MD_UR_TXWRPTR_reg                                                            0x9800B0AC
#define set_MD_UR_TXWRPTR_reg(data)   (*((volatile unsigned int*) MD_UR_TXWRPTR_reg)=data)
#define get_MD_UR_TXWRPTR_reg   (*((volatile unsigned int*) MD_UR_TXWRPTR_reg))
#define MD_UR_TXWRPTR_inst_adr                                                       "0x002B"
#define MD_UR_TXWRPTR_inst                                                           0x002B
#define MD_UR_TXWRPTR_tx_wrptr_shift                                                 (0)
#define MD_UR_TXWRPTR_tx_wrptr_mask                                                  (0x7FFFFFFF)
#define MD_UR_TXWRPTR_tx_wrptr(data)                                                 (0x7FFFFFFF&((data)<<0))
#define MD_UR_TXWRPTR_tx_wrptr_src(data)                                             ((0x7FFFFFFF&(data))>>0)
#define MD_UR_TXWRPTR_get_tx_wrptr(data)                                             ((0x7FFFFFFF&(data))>>0)


#define MD_UR_TXRDPTR                                                                0x9800B0B0
#define MD_UR_TXRDPTR_reg_addr                                                       "0x9800B0B0"
#define MD_UR_TXRDPTR_reg                                                            0x9800B0B0
#define set_MD_UR_TXRDPTR_reg(data)   (*((volatile unsigned int*) MD_UR_TXRDPTR_reg)=data)
#define get_MD_UR_TXRDPTR_reg   (*((volatile unsigned int*) MD_UR_TXRDPTR_reg))
#define MD_UR_TXRDPTR_inst_adr                                                       "0x002C"
#define MD_UR_TXRDPTR_inst                                                           0x002C
#define MD_UR_TXRDPTR_tx_rdptr_shift                                                 (0)
#define MD_UR_TXRDPTR_tx_rdptr_mask                                                  (0x7FFFFFFF)
#define MD_UR_TXRDPTR_tx_rdptr(data)                                                 (0x7FFFFFFF&((data)<<0))
#define MD_UR_TXRDPTR_tx_rdptr_src(data)                                             ((0x7FFFFFFF&(data))>>0)
#define MD_UR_TXRDPTR_get_tx_rdptr(data)                                             ((0x7FFFFFFF&(data))>>0)


#define MD_UR_TXTHD                                                                  0x9800B0B4
#define MD_UR_TXTHD_reg_addr                                                         "0x9800B0B4"
#define MD_UR_TXTHD_reg                                                              0x9800B0B4
#define set_MD_UR_TXTHD_reg(data)   (*((volatile unsigned int*) MD_UR_TXTHD_reg)=data)
#define get_MD_UR_TXTHD_reg   (*((volatile unsigned int*) MD_UR_TXTHD_reg))
#define MD_UR_TXTHD_inst_adr                                                         "0x002D"
#define MD_UR_TXTHD_inst                                                             0x002D
#define MD_UR_TXTHD_tx_thd_shift                                                     (0)
#define MD_UR_TXTHD_tx_thd_mask                                                      (0xFFFFFFFF)
#define MD_UR_TXTHD_tx_thd(data)                                                     (0xFFFFFFFF&((data)<<0))
#define MD_UR_TXTHD_tx_thd_src(data)                                                 ((0xFFFFFFFF&(data))>>0)
#define MD_UR_TXTHD_get_tx_thd(data)                                                 ((0xFFFFFFFF&(data))>>0)


#define MD_UR_RXBASE                                                                 0x9800B0B8
#define MD_UR_RXBASE_reg_addr                                                        "0x9800B0B8"
#define MD_UR_RXBASE_reg                                                             0x9800B0B8
#define set_MD_UR_RXBASE_reg(data)   (*((volatile unsigned int*) MD_UR_RXBASE_reg)=data)
#define get_MD_UR_RXBASE_reg   (*((volatile unsigned int*) MD_UR_RXBASE_reg))
#define MD_UR_RXBASE_inst_adr                                                        "0x002E"
#define MD_UR_RXBASE_inst                                                            0x002E
#define MD_UR_RXBASE_rx_base_shift                                                   (3)
#define MD_UR_RXBASE_rx_base_mask                                                    (0x7FFFFFF8)
#define MD_UR_RXBASE_rx_base(data)                                                   (0x7FFFFFF8&((data)<<3))
#define MD_UR_RXBASE_rx_base_src(data)                                               ((0x7FFFFFF8&(data))>>3)
#define MD_UR_RXBASE_get_rx_base(data)                                               ((0x7FFFFFF8&(data))>>3)


#define MD_UR_RXLIMIT                                                                0x9800B0BC
#define MD_UR_RXLIMIT_reg_addr                                                       "0x9800B0BC"
#define MD_UR_RXLIMIT_reg                                                            0x9800B0BC
#define set_MD_UR_RXLIMIT_reg(data)   (*((volatile unsigned int*) MD_UR_RXLIMIT_reg)=data)
#define get_MD_UR_RXLIMIT_reg   (*((volatile unsigned int*) MD_UR_RXLIMIT_reg))
#define MD_UR_RXLIMIT_inst_adr                                                       "0x002F"
#define MD_UR_RXLIMIT_inst                                                           0x002F
#define MD_UR_RXLIMIT_rx_limit_shift                                                 (3)
#define MD_UR_RXLIMIT_rx_limit_mask                                                  (0x7FFFFFF8)
#define MD_UR_RXLIMIT_rx_limit(data)                                                 (0x7FFFFFF8&((data)<<3))
#define MD_UR_RXLIMIT_rx_limit_src(data)                                             ((0x7FFFFFF8&(data))>>3)
#define MD_UR_RXLIMIT_get_rx_limit(data)                                             ((0x7FFFFFF8&(data))>>3)


#define MD_UR_RXWRPTR                                                                0x9800B0C0
#define MD_UR_RXWRPTR_reg_addr                                                       "0x9800B0C0"
#define MD_UR_RXWRPTR_reg                                                            0x9800B0C0
#define set_MD_UR_RXWRPTR_reg(data)   (*((volatile unsigned int*) MD_UR_RXWRPTR_reg)=data)
#define get_MD_UR_RXWRPTR_reg   (*((volatile unsigned int*) MD_UR_RXWRPTR_reg))
#define MD_UR_RXWRPTR_inst_adr                                                       "0x0030"
#define MD_UR_RXWRPTR_inst                                                           0x0030
#define MD_UR_RXWRPTR_rx_wrptr_shift                                                 (0)
#define MD_UR_RXWRPTR_rx_wrptr_mask                                                  (0x7FFFFFFF)
#define MD_UR_RXWRPTR_rx_wrptr(data)                                                 (0x7FFFFFFF&((data)<<0))
#define MD_UR_RXWRPTR_rx_wrptr_src(data)                                             ((0x7FFFFFFF&(data))>>0)
#define MD_UR_RXWRPTR_get_rx_wrptr(data)                                             ((0x7FFFFFFF&(data))>>0)


#define MD_UR_RXRDPTR                                                                0x9800B0C4
#define MD_UR_RXRDPTR_reg_addr                                                       "0x9800B0C4"
#define MD_UR_RXRDPTR_reg                                                            0x9800B0C4
#define set_MD_UR_RXRDPTR_reg(data)   (*((volatile unsigned int*) MD_UR_RXRDPTR_reg)=data)
#define get_MD_UR_RXRDPTR_reg   (*((volatile unsigned int*) MD_UR_RXRDPTR_reg))
#define MD_UR_RXRDPTR_inst_adr                                                       "0x0031"
#define MD_UR_RXRDPTR_inst                                                           0x0031
#define MD_UR_RXRDPTR_rx_rdptr_shift                                                 (0)
#define MD_UR_RXRDPTR_rx_rdptr_mask                                                  (0x7FFFFFFF)
#define MD_UR_RXRDPTR_rx_rdptr(data)                                                 (0x7FFFFFFF&((data)<<0))
#define MD_UR_RXRDPTR_rx_rdptr_src(data)                                             ((0x7FFFFFFF&(data))>>0)
#define MD_UR_RXRDPTR_get_rx_rdptr(data)                                             ((0x7FFFFFFF&(data))>>0)


#define MD_UR_RXTHD                                                                  0x9800B0C8
#define MD_UR_RXTHD_reg_addr                                                         "0x9800B0C8"
#define MD_UR_RXTHD_reg                                                              0x9800B0C8
#define set_MD_UR_RXTHD_reg(data)   (*((volatile unsigned int*) MD_UR_RXTHD_reg)=data)
#define get_MD_UR_RXTHD_reg   (*((volatile unsigned int*) MD_UR_RXTHD_reg))
#define MD_UR_RXTHD_inst_adr                                                         "0x0032"
#define MD_UR_RXTHD_inst                                                             0x0032
#define MD_UR_RXTHD_rx_thd_shift                                                     (0)
#define MD_UR_RXTHD_rx_thd_mask                                                      (0xFFFFFFFF)
#define MD_UR_RXTHD_rx_thd(data)                                                     (0xFFFFFFFF&((data)<<0))
#define MD_UR_RXTHD_rx_thd_src(data)                                                 ((0xFFFFFFFF&(data))>>0)
#define MD_UR_RXTHD_get_rx_thd(data)                                                 ((0xFFFFFFFF&(data))>>0)


#define MD_UR_ENABLE                                                                 0x9800B0CC
#define MD_UR_ENABLE_reg_addr                                                        "0x9800B0CC"
#define MD_UR_ENABLE_reg                                                             0x9800B0CC
#define set_MD_UR_ENABLE_reg(data)   (*((volatile unsigned int*) MD_UR_ENABLE_reg)=data)
#define get_MD_UR_ENABLE_reg   (*((volatile unsigned int*) MD_UR_ENABLE_reg))
#define MD_UR_ENABLE_inst_adr                                                        "0x0033"
#define MD_UR_ENABLE_inst                                                            0x0033
#define MD_UR_ENABLE_ur_en_shift                                                     (0)
#define MD_UR_ENABLE_ur_en_mask                                                      (0x00000001)
#define MD_UR_ENABLE_ur_en(data)                                                     (0x00000001&((data)<<0))
#define MD_UR_ENABLE_ur_en_src(data)                                                 ((0x00000001&(data))>>0)
#define MD_UR_ENABLE_get_ur_en(data)                                                 ((0x00000001&(data))>>0)


#define MD_GSP_TXBASE                                                                0x9800B0D4
#define MD_GSP_TXBASE_reg_addr                                                       "0x9800B0D4"
#define MD_GSP_TXBASE_reg                                                            0x9800B0D4
#define set_MD_GSP_TXBASE_reg(data)   (*((volatile unsigned int*) MD_GSP_TXBASE_reg)=data)
#define get_MD_GSP_TXBASE_reg   (*((volatile unsigned int*) MD_GSP_TXBASE_reg))
#define MD_GSP_TXBASE_inst_adr                                                       "0x0035"
#define MD_GSP_TXBASE_inst                                                           0x0035
#define MD_GSP_TXBASE_gsp_tx_base_shift                                              (3)
#define MD_GSP_TXBASE_gsp_tx_base_mask                                               (0x7FFFFFF8)
#define MD_GSP_TXBASE_gsp_tx_base(data)                                              (0x7FFFFFF8&((data)<<3))
#define MD_GSP_TXBASE_gsp_tx_base_src(data)                                          ((0x7FFFFFF8&(data))>>3)
#define MD_GSP_TXBASE_get_gsp_tx_base(data)                                          ((0x7FFFFFF8&(data))>>3)


#define MD_GSP_TXLIMIT                                                               0x9800B0D8
#define MD_GSP_TXLIMIT_reg_addr                                                      "0x9800B0D8"
#define MD_GSP_TXLIMIT_reg                                                           0x9800B0D8
#define set_MD_GSP_TXLIMIT_reg(data)   (*((volatile unsigned int*) MD_GSP_TXLIMIT_reg)=data)
#define get_MD_GSP_TXLIMIT_reg   (*((volatile unsigned int*) MD_GSP_TXLIMIT_reg))
#define MD_GSP_TXLIMIT_inst_adr                                                      "0x0036"
#define MD_GSP_TXLIMIT_inst                                                          0x0036
#define MD_GSP_TXLIMIT_gsp_tx_limit_shift                                            (3)
#define MD_GSP_TXLIMIT_gsp_tx_limit_mask                                             (0x7FFFFFF8)
#define MD_GSP_TXLIMIT_gsp_tx_limit(data)                                            (0x7FFFFFF8&((data)<<3))
#define MD_GSP_TXLIMIT_gsp_tx_limit_src(data)                                        ((0x7FFFFFF8&(data))>>3)
#define MD_GSP_TXLIMIT_get_gsp_tx_limit(data)                                        ((0x7FFFFFF8&(data))>>3)


#define MD_GSP_TXWRPTR                                                               0x9800B0DC
#define MD_GSP_TXWRPTR_reg_addr                                                      "0x9800B0DC"
#define MD_GSP_TXWRPTR_reg                                                           0x9800B0DC
#define set_MD_GSP_TXWRPTR_reg(data)   (*((volatile unsigned int*) MD_GSP_TXWRPTR_reg)=data)
#define get_MD_GSP_TXWRPTR_reg   (*((volatile unsigned int*) MD_GSP_TXWRPTR_reg))
#define MD_GSP_TXWRPTR_inst_adr                                                      "0x0037"
#define MD_GSP_TXWRPTR_inst                                                          0x0037
#define MD_GSP_TXWRPTR_gsp_tx_wrptr_shift                                            (0)
#define MD_GSP_TXWRPTR_gsp_tx_wrptr_mask                                             (0x7FFFFFFF)
#define MD_GSP_TXWRPTR_gsp_tx_wrptr(data)                                            (0x7FFFFFFF&((data)<<0))
#define MD_GSP_TXWRPTR_gsp_tx_wrptr_src(data)                                        ((0x7FFFFFFF&(data))>>0)
#define MD_GSP_TXWRPTR_get_gsp_tx_wrptr(data)                                        ((0x7FFFFFFF&(data))>>0)


#define MD_GSP_TXRDPTR                                                               0x9800B0E0
#define MD_GSP_TXRDPTR_reg_addr                                                      "0x9800B0E0"
#define MD_GSP_TXRDPTR_reg                                                           0x9800B0E0
#define set_MD_GSP_TXRDPTR_reg(data)   (*((volatile unsigned int*) MD_GSP_TXRDPTR_reg)=data)
#define get_MD_GSP_TXRDPTR_reg   (*((volatile unsigned int*) MD_GSP_TXRDPTR_reg))
#define MD_GSP_TXRDPTR_inst_adr                                                      "0x0038"
#define MD_GSP_TXRDPTR_inst                                                          0x0038
#define MD_GSP_TXRDPTR_gsp_tx_rdptr_shift                                            (0)
#define MD_GSP_TXRDPTR_gsp_tx_rdptr_mask                                             (0x7FFFFFFF)
#define MD_GSP_TXRDPTR_gsp_tx_rdptr(data)                                            (0x7FFFFFFF&((data)<<0))
#define MD_GSP_TXRDPTR_gsp_tx_rdptr_src(data)                                        ((0x7FFFFFFF&(data))>>0)
#define MD_GSP_TXRDPTR_get_gsp_tx_rdptr(data)                                        ((0x7FFFFFFF&(data))>>0)


#define MD_GSP_TXTHD                                                                 0x9800B0E4
#define MD_GSP_TXTHD_reg_addr                                                        "0x9800B0E4"
#define MD_GSP_TXTHD_reg                                                             0x9800B0E4
#define set_MD_GSP_TXTHD_reg(data)   (*((volatile unsigned int*) MD_GSP_TXTHD_reg)=data)
#define get_MD_GSP_TXTHD_reg   (*((volatile unsigned int*) MD_GSP_TXTHD_reg))
#define MD_GSP_TXTHD_inst_adr                                                        "0x0039"
#define MD_GSP_TXTHD_inst                                                            0x0039
#define MD_GSP_TXTHD_gsp_tx_thd_shift                                                (0)
#define MD_GSP_TXTHD_gsp_tx_thd_mask                                                 (0xFFFFFFFF)
#define MD_GSP_TXTHD_gsp_tx_thd(data)                                                (0xFFFFFFFF&((data)<<0))
#define MD_GSP_TXTHD_gsp_tx_thd_src(data)                                            ((0xFFFFFFFF&(data))>>0)
#define MD_GSP_TXTHD_get_gsp_tx_thd(data)                                            ((0xFFFFFFFF&(data))>>0)


#define MD_GSP_RXBASE                                                                0x9800B0E8
#define MD_GSP_RXBASE_reg_addr                                                       "0x9800B0E8"
#define MD_GSP_RXBASE_reg                                                            0x9800B0E8
#define set_MD_GSP_RXBASE_reg(data)   (*((volatile unsigned int*) MD_GSP_RXBASE_reg)=data)
#define get_MD_GSP_RXBASE_reg   (*((volatile unsigned int*) MD_GSP_RXBASE_reg))
#define MD_GSP_RXBASE_inst_adr                                                       "0x003A"
#define MD_GSP_RXBASE_inst                                                           0x003A
#define MD_GSP_RXBASE_gsp_rx_base_shift                                              (3)
#define MD_GSP_RXBASE_gsp_rx_base_mask                                               (0x7FFFFFF8)
#define MD_GSP_RXBASE_gsp_rx_base(data)                                              (0x7FFFFFF8&((data)<<3))
#define MD_GSP_RXBASE_gsp_rx_base_src(data)                                          ((0x7FFFFFF8&(data))>>3)
#define MD_GSP_RXBASE_get_gsp_rx_base(data)                                          ((0x7FFFFFF8&(data))>>3)


#define MD_GSP_RXLIMIT                                                               0x9800B0EC
#define MD_GSP_RXLIMIT_reg_addr                                                      "0x9800B0EC"
#define MD_GSP_RXLIMIT_reg                                                           0x9800B0EC
#define set_MD_GSP_RXLIMIT_reg(data)   (*((volatile unsigned int*) MD_GSP_RXLIMIT_reg)=data)
#define get_MD_GSP_RXLIMIT_reg   (*((volatile unsigned int*) MD_GSP_RXLIMIT_reg))
#define MD_GSP_RXLIMIT_inst_adr                                                      "0x003B"
#define MD_GSP_RXLIMIT_inst                                                          0x003B
#define MD_GSP_RXLIMIT_gsp_rx_limit_shift                                            (3)
#define MD_GSP_RXLIMIT_gsp_rx_limit_mask                                             (0x7FFFFFF8)
#define MD_GSP_RXLIMIT_gsp_rx_limit(data)                                            (0x7FFFFFF8&((data)<<3))
#define MD_GSP_RXLIMIT_gsp_rx_limit_src(data)                                        ((0x7FFFFFF8&(data))>>3)
#define MD_GSP_RXLIMIT_get_gsp_rx_limit(data)                                        ((0x7FFFFFF8&(data))>>3)


#define MD_GSP_RXWRPTR                                                               0x9800B0F0
#define MD_GSP_RXWRPTR_reg_addr                                                      "0x9800B0F0"
#define MD_GSP_RXWRPTR_reg                                                           0x9800B0F0
#define set_MD_GSP_RXWRPTR_reg(data)   (*((volatile unsigned int*) MD_GSP_RXWRPTR_reg)=data)
#define get_MD_GSP_RXWRPTR_reg   (*((volatile unsigned int*) MD_GSP_RXWRPTR_reg))
#define MD_GSP_RXWRPTR_inst_adr                                                      "0x003C"
#define MD_GSP_RXWRPTR_inst                                                          0x003C
#define MD_GSP_RXWRPTR_gsp_rx_wrptr_shift                                            (0)
#define MD_GSP_RXWRPTR_gsp_rx_wrptr_mask                                             (0x7FFFFFFF)
#define MD_GSP_RXWRPTR_gsp_rx_wrptr(data)                                            (0x7FFFFFFF&((data)<<0))
#define MD_GSP_RXWRPTR_gsp_rx_wrptr_src(data)                                        ((0x7FFFFFFF&(data))>>0)
#define MD_GSP_RXWRPTR_get_gsp_rx_wrptr(data)                                        ((0x7FFFFFFF&(data))>>0)


#define MD_GSP_RXRDPTR                                                               0x9800B0F4
#define MD_GSP_RXRDPTR_reg_addr                                                      "0x9800B0F4"
#define MD_GSP_RXRDPTR_reg                                                           0x9800B0F4
#define set_MD_GSP_RXRDPTR_reg(data)   (*((volatile unsigned int*) MD_GSP_RXRDPTR_reg)=data)
#define get_MD_GSP_RXRDPTR_reg   (*((volatile unsigned int*) MD_GSP_RXRDPTR_reg))
#define MD_GSP_RXRDPTR_inst_adr                                                      "0x003D"
#define MD_GSP_RXRDPTR_inst                                                          0x003D
#define MD_GSP_RXRDPTR_gsp_rx_rdptr_shift                                            (0)
#define MD_GSP_RXRDPTR_gsp_rx_rdptr_mask                                             (0x7FFFFFFF)
#define MD_GSP_RXRDPTR_gsp_rx_rdptr(data)                                            (0x7FFFFFFF&((data)<<0))
#define MD_GSP_RXRDPTR_gsp_rx_rdptr_src(data)                                        ((0x7FFFFFFF&(data))>>0)
#define MD_GSP_RXRDPTR_get_gsp_rx_rdptr(data)                                        ((0x7FFFFFFF&(data))>>0)


#define MD_GSP_RXTHD                                                                 0x9800B0F8
#define MD_GSP_RXTHD_reg_addr                                                        "0x9800B0F8"
#define MD_GSP_RXTHD_reg                                                             0x9800B0F8
#define set_MD_GSP_RXTHD_reg(data)   (*((volatile unsigned int*) MD_GSP_RXTHD_reg)=data)
#define get_MD_GSP_RXTHD_reg   (*((volatile unsigned int*) MD_GSP_RXTHD_reg))
#define MD_GSP_RXTHD_inst_adr                                                        "0x003E"
#define MD_GSP_RXTHD_inst                                                            0x003E
#define MD_GSP_RXTHD_gsp_rx_thd_shift                                                (0)
#define MD_GSP_RXTHD_gsp_rx_thd_mask                                                 (0xFFFFFFFF)
#define MD_GSP_RXTHD_gsp_rx_thd(data)                                                (0xFFFFFFFF&((data)<<0))
#define MD_GSP_RXTHD_gsp_rx_thd_src(data)                                            ((0xFFFFFFFF&(data))>>0)
#define MD_GSP_RXTHD_get_gsp_rx_thd(data)                                            ((0xFFFFFFFF&(data))>>0)


#define MD_GSP_ENABLE                                                                0x9800B0FC
#define MD_GSP_ENABLE_reg_addr                                                       "0x9800B0FC"
#define MD_GSP_ENABLE_reg                                                            0x9800B0FC
#define set_MD_GSP_ENABLE_reg(data)   (*((volatile unsigned int*) MD_GSP_ENABLE_reg)=data)
#define get_MD_GSP_ENABLE_reg   (*((volatile unsigned int*) MD_GSP_ENABLE_reg))
#define MD_GSP_ENABLE_inst_adr                                                       "0x003F"
#define MD_GSP_ENABLE_inst                                                           0x003F
#define MD_GSP_ENABLE_gsp_en_shift                                                   (0)
#define MD_GSP_ENABLE_gsp_en_mask                                                    (0x00000001)
#define MD_GSP_ENABLE_gsp_en(data)                                                   (0x00000001&((data)<<0))
#define MD_GSP_ENABLE_gsp_en_src(data)                                               ((0x00000001&(data))>>0)
#define MD_GSP_ENABLE_get_gsp_en(data)                                               ((0x00000001&(data))>>0)


#define MD_GSP_TXBASICBASE                                                           0x9800B100
#define MD_GSP_TXBASICBASE_reg_addr                                                  "0x9800B100"
#define MD_GSP_TXBASICBASE_reg                                                       0x9800B100
#define set_MD_GSP_TXBASICBASE_reg(data)   (*((volatile unsigned int*) MD_GSP_TXBASICBASE_reg)=data)
#define get_MD_GSP_TXBASICBASE_reg   (*((volatile unsigned int*) MD_GSP_TXBASICBASE_reg))
#define MD_GSP_TXBASICBASE_inst_adr                                                  "0x0040"
#define MD_GSP_TXBASICBASE_inst                                                      0x0040
#define MD_GSP_TXBASICBASE_gsp_txbasic_base_shift                                    (3)
#define MD_GSP_TXBASICBASE_gsp_txbasic_base_mask                                     (0x7FFFFFF8)
#define MD_GSP_TXBASICBASE_gsp_txbasic_base(data)                                    (0x7FFFFFF8&((data)<<3))
#define MD_GSP_TXBASICBASE_gsp_txbasic_base_src(data)                                ((0x7FFFFFF8&(data))>>3)
#define MD_GSP_TXBASICBASE_get_gsp_txbasic_base(data)                                ((0x7FFFFFF8&(data))>>3)


#define MD_GSP_TXBASICLIMIT                                                          0x9800B104
#define MD_GSP_TXBASICLIMIT_reg_addr                                                 "0x9800B104"
#define MD_GSP_TXBASICLIMIT_reg                                                      0x9800B104
#define set_MD_GSP_TXBASICLIMIT_reg(data)   (*((volatile unsigned int*) MD_GSP_TXBASICLIMIT_reg)=data)
#define get_MD_GSP_TXBASICLIMIT_reg   (*((volatile unsigned int*) MD_GSP_TXBASICLIMIT_reg))
#define MD_GSP_TXBASICLIMIT_inst_adr                                                 "0x0041"
#define MD_GSP_TXBASICLIMIT_inst                                                     0x0041
#define MD_GSP_TXBASICLIMIT_gsp_txbasic_limit_shift                                  (3)
#define MD_GSP_TXBASICLIMIT_gsp_txbasic_limit_mask                                   (0x7FFFFFF8)
#define MD_GSP_TXBASICLIMIT_gsp_txbasic_limit(data)                                  (0x7FFFFFF8&((data)<<3))
#define MD_GSP_TXBASICLIMIT_gsp_txbasic_limit_src(data)                              ((0x7FFFFFF8&(data))>>3)
#define MD_GSP_TXBASICLIMIT_get_gsp_txbasic_limit(data)                              ((0x7FFFFFF8&(data))>>3)


#define MD_GSP_TXBASICWRPTR                                                          0x9800B108
#define MD_GSP_TXBASICWRPTR_reg_addr                                                 "0x9800B108"
#define MD_GSP_TXBASICWRPTR_reg                                                      0x9800B108
#define set_MD_GSP_TXBASICWRPTR_reg(data)   (*((volatile unsigned int*) MD_GSP_TXBASICWRPTR_reg)=data)
#define get_MD_GSP_TXBASICWRPTR_reg   (*((volatile unsigned int*) MD_GSP_TXBASICWRPTR_reg))
#define MD_GSP_TXBASICWRPTR_inst_adr                                                 "0x0042"
#define MD_GSP_TXBASICWRPTR_inst                                                     0x0042
#define MD_GSP_TXBASICWRPTR_gsp_txbasic_wrptr_shift                                  (0)
#define MD_GSP_TXBASICWRPTR_gsp_txbasic_wrptr_mask                                   (0x7FFFFFFF)
#define MD_GSP_TXBASICWRPTR_gsp_txbasic_wrptr(data)                                  (0x7FFFFFFF&((data)<<0))
#define MD_GSP_TXBASICWRPTR_gsp_txbasic_wrptr_src(data)                              ((0x7FFFFFFF&(data))>>0)
#define MD_GSP_TXBASICWRPTR_get_gsp_txbasic_wrptr(data)                              ((0x7FFFFFFF&(data))>>0)


#define MD_GSP_TXBASICRDPTR                                                          0x9800B10C
#define MD_GSP_TXBASICRDPTR_reg_addr                                                 "0x9800B10C"
#define MD_GSP_TXBASICRDPTR_reg                                                      0x9800B10C
#define set_MD_GSP_TXBASICRDPTR_reg(data)   (*((volatile unsigned int*) MD_GSP_TXBASICRDPTR_reg)=data)
#define get_MD_GSP_TXBASICRDPTR_reg   (*((volatile unsigned int*) MD_GSP_TXBASICRDPTR_reg))
#define MD_GSP_TXBASICRDPTR_inst_adr                                                 "0x0043"
#define MD_GSP_TXBASICRDPTR_inst                                                     0x0043
#define MD_GSP_TXBASICRDPTR_gsp_txbasic_rdptr_shift                                  (0)
#define MD_GSP_TXBASICRDPTR_gsp_txbasic_rdptr_mask                                   (0x7FFFFFFF)
#define MD_GSP_TXBASICRDPTR_gsp_txbasic_rdptr(data)                                  (0x7FFFFFFF&((data)<<0))
#define MD_GSP_TXBASICRDPTR_gsp_txbasic_rdptr_src(data)                              ((0x7FFFFFFF&(data))>>0)
#define MD_GSP_TXBASICRDPTR_get_gsp_txbasic_rdptr(data)                              ((0x7FFFFFFF&(data))>>0)


#define MD_GSP_TXBASICTHD                                                            0x9800B110
#define MD_GSP_TXBASICTHD_reg_addr                                                   "0x9800B110"
#define MD_GSP_TXBASICTHD_reg                                                        0x9800B110
#define set_MD_GSP_TXBASICTHD_reg(data)   (*((volatile unsigned int*) MD_GSP_TXBASICTHD_reg)=data)
#define get_MD_GSP_TXBASICTHD_reg   (*((volatile unsigned int*) MD_GSP_TXBASICTHD_reg))
#define MD_GSP_TXBASICTHD_inst_adr                                                   "0x0044"
#define MD_GSP_TXBASICTHD_inst                                                       0x0044
#define MD_GSP_TXBASICTHD_gsp_txbasic_thd_shift                                      (0)
#define MD_GSP_TXBASICTHD_gsp_txbasic_thd_mask                                       (0xFFFFFFFF)
#define MD_GSP_TXBASICTHD_gsp_txbasic_thd(data)                                      (0xFFFFFFFF&((data)<<0))
#define MD_GSP_TXBASICTHD_gsp_txbasic_thd_src(data)                                  ((0xFFFFFFFF&(data))>>0)
#define MD_GSP_TXBASICTHD_get_gsp_txbasic_thd(data)                                  ((0xFFFFFFFF&(data))>>0)


#define MD_GSP_TXDATBASE                                                             0x9800B114
#define MD_GSP_TXDATBASE_reg_addr                                                    "0x9800B114"
#define MD_GSP_TXDATBASE_reg                                                         0x9800B114
#define set_MD_GSP_TXDATBASE_reg(data)   (*((volatile unsigned int*) MD_GSP_TXDATBASE_reg)=data)
#define get_MD_GSP_TXDATBASE_reg   (*((volatile unsigned int*) MD_GSP_TXDATBASE_reg))
#define MD_GSP_TXDATBASE_inst_adr                                                    "0x0045"
#define MD_GSP_TXDATBASE_inst                                                        0x0045
#define MD_GSP_TXDATBASE_gsp_txdat_base_shift                                        (3)
#define MD_GSP_TXDATBASE_gsp_txdat_base_mask                                         (0x7FFFFFF8)
#define MD_GSP_TXDATBASE_gsp_txdat_base(data)                                        (0x7FFFFFF8&((data)<<3))
#define MD_GSP_TXDATBASE_gsp_txdat_base_src(data)                                    ((0x7FFFFFF8&(data))>>3)
#define MD_GSP_TXDATBASE_get_gsp_txdat_base(data)                                    ((0x7FFFFFF8&(data))>>3)


#define MD_GSP_TXDATLIMIT                                                            0x9800B118
#define MD_GSP_TXDATLIMIT_reg_addr                                                   "0x9800B118"
#define MD_GSP_TXDATLIMIT_reg                                                        0x9800B118
#define set_MD_GSP_TXDATLIMIT_reg(data)   (*((volatile unsigned int*) MD_GSP_TXDATLIMIT_reg)=data)
#define get_MD_GSP_TXDATLIMIT_reg   (*((volatile unsigned int*) MD_GSP_TXDATLIMIT_reg))
#define MD_GSP_TXDATLIMIT_inst_adr                                                   "0x0046"
#define MD_GSP_TXDATLIMIT_inst                                                       0x0046
#define MD_GSP_TXDATLIMIT_gsp_txdat_limit_shift                                      (3)
#define MD_GSP_TXDATLIMIT_gsp_txdat_limit_mask                                       (0x7FFFFFF8)
#define MD_GSP_TXDATLIMIT_gsp_txdat_limit(data)                                      (0x7FFFFFF8&((data)<<3))
#define MD_GSP_TXDATLIMIT_gsp_txdat_limit_src(data)                                  ((0x7FFFFFF8&(data))>>3)
#define MD_GSP_TXDATLIMIT_get_gsp_txdat_limit(data)                                  ((0x7FFFFFF8&(data))>>3)


#define MD_GSP_TXDATWRPTR                                                            0x9800B11C
#define MD_GSP_TXDATWRPTR_reg_addr                                                   "0x9800B11C"
#define MD_GSP_TXDATWRPTR_reg                                                        0x9800B11C
#define set_MD_GSP_TXDATWRPTR_reg(data)   (*((volatile unsigned int*) MD_GSP_TXDATWRPTR_reg)=data)
#define get_MD_GSP_TXDATWRPTR_reg   (*((volatile unsigned int*) MD_GSP_TXDATWRPTR_reg))
#define MD_GSP_TXDATWRPTR_inst_adr                                                   "0x0047"
#define MD_GSP_TXDATWRPTR_inst                                                       0x0047
#define MD_GSP_TXDATWRPTR_gsp_txdat_wrptr_shift                                      (0)
#define MD_GSP_TXDATWRPTR_gsp_txdat_wrptr_mask                                       (0x7FFFFFFF)
#define MD_GSP_TXDATWRPTR_gsp_txdat_wrptr(data)                                      (0x7FFFFFFF&((data)<<0))
#define MD_GSP_TXDATWRPTR_gsp_txdat_wrptr_src(data)                                  ((0x7FFFFFFF&(data))>>0)
#define MD_GSP_TXDATWRPTR_get_gsp_txdat_wrptr(data)                                  ((0x7FFFFFFF&(data))>>0)


#define MD_GSP_TXDATRDPTR                                                            0x9800B120
#define MD_GSP_TXDATRDPTR_reg_addr                                                   "0x9800B120"
#define MD_GSP_TXDATRDPTR_reg                                                        0x9800B120
#define set_MD_GSP_TXDATRDPTR_reg(data)   (*((volatile unsigned int*) MD_GSP_TXDATRDPTR_reg)=data)
#define get_MD_GSP_TXDATRDPTR_reg   (*((volatile unsigned int*) MD_GSP_TXDATRDPTR_reg))
#define MD_GSP_TXDATRDPTR_inst_adr                                                   "0x0048"
#define MD_GSP_TXDATRDPTR_inst                                                       0x0048
#define MD_GSP_TXDATRDPTR_gsp_txdat_rdptr_shift                                      (0)
#define MD_GSP_TXDATRDPTR_gsp_txdat_rdptr_mask                                       (0x7FFFFFFF)
#define MD_GSP_TXDATRDPTR_gsp_txdat_rdptr(data)                                      (0x7FFFFFFF&((data)<<0))
#define MD_GSP_TXDATRDPTR_gsp_txdat_rdptr_src(data)                                  ((0x7FFFFFFF&(data))>>0)
#define MD_GSP_TXDATRDPTR_get_gsp_txdat_rdptr(data)                                  ((0x7FFFFFFF&(data))>>0)


#define MD_GSP_TXDATTHD                                                              0x9800B124
#define MD_GSP_TXDATTHD_reg_addr                                                     "0x9800B124"
#define MD_GSP_TXDATTHD_reg                                                          0x9800B124
#define set_MD_GSP_TXDATTHD_reg(data)   (*((volatile unsigned int*) MD_GSP_TXDATTHD_reg)=data)
#define get_MD_GSP_TXDATTHD_reg   (*((volatile unsigned int*) MD_GSP_TXDATTHD_reg))
#define MD_GSP_TXDATTHD_inst_adr                                                     "0x0049"
#define MD_GSP_TXDATTHD_inst                                                         0x0049
#define MD_GSP_TXDATTHD_gsp_txdat_thd_shift                                          (0)
#define MD_GSP_TXDATTHD_gsp_txdat_thd_mask                                           (0xFFFFFFFF)
#define MD_GSP_TXDATTHD_gsp_txdat_thd(data)                                          (0xFFFFFFFF&((data)<<0))
#define MD_GSP_TXDATTHD_gsp_txdat_thd_src(data)                                      ((0xFFFFFFFF&(data))>>0)
#define MD_GSP_TXDATTHD_get_gsp_txdat_thd(data)                                      ((0xFFFFFFFF&(data))>>0)


#define MD_POWER                                                                     0x9800B128
#define MD_POWER_reg_addr                                                            "0x9800B128"
#define MD_POWER_reg                                                                 0x9800B128
#define set_MD_POWER_reg(data)   (*((volatile unsigned int*) MD_POWER_reg)=data)
#define get_MD_POWER_reg   (*((volatile unsigned int*) MD_POWER_reg))
#define MD_POWER_inst_adr                                                            "0x004A"
#define MD_POWER_inst                                                                0x004A
#define MD_POWER_gating_en_shift                                                     (0)
#define MD_POWER_gating_en_mask                                                      (0x00000001)
#define MD_POWER_gating_en(data)                                                     (0x00000001&((data)<<0))
#define MD_POWER_gating_en_src(data)                                                 ((0x00000001&(data))>>0)
#define MD_POWER_get_gating_en(data)                                                 ((0x00000001&(data))>>0)


#define MD_DUMMY1                                                                    0x9800B09C
#define MD_DUMMY1_reg_addr                                                           "0x9800B09C"
#define MD_DUMMY1_reg                                                                0x9800B09C
#define set_MD_DUMMY1_reg(data)   (*((volatile unsigned int*) MD_DUMMY1_reg)=data)
#define get_MD_DUMMY1_reg   (*((volatile unsigned int*) MD_DUMMY1_reg))
#define MD_DUMMY1_inst_adr                                                           "0x0027"
#define MD_DUMMY1_inst                                                               0x0027
#define MD_DUMMY1_dummy1_shift                                                       (0)
#define MD_DUMMY1_dummy1_mask                                                        (0xFFFFFFFF)
#define MD_DUMMY1_dummy1(data)                                                       (0xFFFFFFFF&((data)<<0))
#define MD_DUMMY1_dummy1_src(data)                                                   ((0xFFFFFFFF&(data))>>0)
#define MD_DUMMY1_get_dummy1(data)                                                   ((0xFFFFFFFF&(data))>>0)


#define MD_DUMMY2                                                                    0x9800B0A0
#define MD_DUMMY2_reg_addr                                                           "0x9800B0A0"
#define MD_DUMMY2_reg                                                                0x9800B0A0
#define set_MD_DUMMY2_reg(data)   (*((volatile unsigned int*) MD_DUMMY2_reg)=data)
#define get_MD_DUMMY2_reg   (*((volatile unsigned int*) MD_DUMMY2_reg))
#define MD_DUMMY2_inst_adr                                                           "0x0028"
#define MD_DUMMY2_inst                                                               0x0028
#define MD_DUMMY2_dummy2_shift                                                       (0)
#define MD_DUMMY2_dummy2_mask                                                        (0xFFFFFFFF)
#define MD_DUMMY2_dummy2(data)                                                       (0xFFFFFFFF&((data)<<0))
#define MD_DUMMY2_dummy2_src(data)                                                   ((0xFFFFFFFF&(data))>>0)
#define MD_DUMMY2_get_dummy2(data)                                                   ((0xFFFFFFFF&(data))>>0)


#define BIST_DVS                                                                     0x9800B12C
#define BIST_DVS_reg_addr                                                            "0x9800B12C"
#define BIST_DVS_reg                                                                 0x9800B12C
#define set_BIST_DVS_reg(data)   (*((volatile unsigned int*) BIST_DVS_reg)=data)
#define get_BIST_DVS_reg   (*((volatile unsigned int*) BIST_DVS_reg))
#define BIST_DVS_inst_adr                                                            "0x004B"
#define BIST_DVS_inst                                                                0x004B
#define BIST_DVS_dvse_shift                                                          (4)
#define BIST_DVS_dvse_mask                                                           (0x00000010)
#define BIST_DVS_dvse(data)                                                          (0x00000010&((data)<<4))
#define BIST_DVS_dvse_src(data)                                                      ((0x00000010&(data))>>4)
#define BIST_DVS_get_dvse(data)                                                      ((0x00000010&(data))>>4)
#define BIST_DVS_dvs_3_shift                                                         (3)
#define BIST_DVS_dvs_3_mask                                                          (0x00000008)
#define BIST_DVS_dvs_3(data)                                                         (0x00000008&((data)<<3))
#define BIST_DVS_dvs_3_src(data)                                                     ((0x00000008&(data))>>3)
#define BIST_DVS_get_dvs_3(data)                                                     ((0x00000008&(data))>>3)
#define BIST_DVS_dvs_2_shift                                                         (2)
#define BIST_DVS_dvs_2_mask                                                          (0x00000004)
#define BIST_DVS_dvs_2(data)                                                         (0x00000004&((data)<<2))
#define BIST_DVS_dvs_2_src(data)                                                     ((0x00000004&(data))>>2)
#define BIST_DVS_get_dvs_2(data)                                                     ((0x00000004&(data))>>2)
#define BIST_DVS_dvs_1_shift                                                         (1)
#define BIST_DVS_dvs_1_mask                                                          (0x00000002)
#define BIST_DVS_dvs_1(data)                                                         (0x00000002&((data)<<1))
#define BIST_DVS_dvs_1_src(data)                                                     ((0x00000002&(data))>>1)
#define BIST_DVS_get_dvs_1(data)                                                     ((0x00000002&(data))>>1)
#define BIST_DVS_dvs_0_shift                                                         (0)
#define BIST_DVS_dvs_0_mask                                                          (0x00000001)
#define BIST_DVS_dvs_0(data)                                                         (0x00000001&((data)<<0))
#define BIST_DVS_dvs_0_src(data)                                                     ((0x00000001&(data))>>0)
#define BIST_DVS_get_dvs_0(data)                                                     ((0x00000001&(data))>>0)


#define BIST_ST                                                                      0x9800B130
#define BIST_ST_reg_addr                                                             "0x9800B130"
#define BIST_ST_reg                                                                  0x9800B130
#define set_BIST_ST_reg(data)   (*((volatile unsigned int*) BIST_ST_reg)=data)
#define get_BIST_ST_reg   (*((volatile unsigned int*) BIST_ST_reg))
#define BIST_ST_inst_adr                                                             "0x004C"
#define BIST_ST_inst                                                                 0x004C
#define BIST_ST_bist_fail2_shift                                                     (3)
#define BIST_ST_bist_fail2_mask                                                      (0x00000008)
#define BIST_ST_bist_fail2(data)                                                     (0x00000008&((data)<<3))
#define BIST_ST_bist_fail2_src(data)                                                 ((0x00000008&(data))>>3)
#define BIST_ST_get_bist_fail2(data)                                                 ((0x00000008&(data))>>3)
#define BIST_ST_bist_fail1_shift                                                     (2)
#define BIST_ST_bist_fail1_mask                                                      (0x00000004)
#define BIST_ST_bist_fail1(data)                                                     (0x00000004&((data)<<2))
#define BIST_ST_bist_fail1_src(data)                                                 ((0x00000004&(data))>>2)
#define BIST_ST_get_bist_fail1(data)                                                 ((0x00000004&(data))>>2)
#define BIST_ST_bist_fail0_shift                                                     (1)
#define BIST_ST_bist_fail0_mask                                                      (0x00000002)
#define BIST_ST_bist_fail0(data)                                                     (0x00000002&((data)<<1))
#define BIST_ST_bist_fail0_src(data)                                                 ((0x00000002&(data))>>1)
#define BIST_ST_get_bist_fail0(data)                                                 ((0x00000002&(data))>>1)
#define BIST_ST_bist_done_shift                                                      (0)
#define BIST_ST_bist_done_mask                                                       (0x00000001)
#define BIST_ST_bist_done(data)                                                      (0x00000001&((data)<<0))
#define BIST_ST_bist_done_src(data)                                                  ((0x00000001&(data))>>0)
#define BIST_ST_get_bist_done(data)                                                  ((0x00000001&(data))>>0)


#define DRF_ST                                                                       0x9800B134
#define DRF_ST_reg_addr                                                              "0x9800B134"
#define DRF_ST_reg                                                                   0x9800B134
#define set_DRF_ST_reg(data)   (*((volatile unsigned int*) DRF_ST_reg)=data)
#define get_DRF_ST_reg   (*((volatile unsigned int*) DRF_ST_reg))
#define DRF_ST_inst_adr                                                              "0x004D"
#define DRF_ST_inst                                                                  0x004D
#define DRF_ST_drf_start_pause_shift                                                 (16)
#define DRF_ST_drf_start_pause_mask                                                  (0x00010000)
#define DRF_ST_drf_start_pause(data)                                                 (0x00010000&((data)<<16))
#define DRF_ST_drf_start_pause_src(data)                                             ((0x00010000&(data))>>16)
#define DRF_ST_get_drf_start_pause(data)                                             ((0x00010000&(data))>>16)
#define DRF_ST_drf_fail2_shift                                                       (3)
#define DRF_ST_drf_fail2_mask                                                        (0x00000008)
#define DRF_ST_drf_fail2(data)                                                       (0x00000008&((data)<<3))
#define DRF_ST_drf_fail2_src(data)                                                   ((0x00000008&(data))>>3)
#define DRF_ST_get_drf_fail2(data)                                                   ((0x00000008&(data))>>3)
#define DRF_ST_drf_fail1_shift                                                       (2)
#define DRF_ST_drf_fail1_mask                                                        (0x00000004)
#define DRF_ST_drf_fail1(data)                                                       (0x00000004&((data)<<2))
#define DRF_ST_drf_fail1_src(data)                                                   ((0x00000004&(data))>>2)
#define DRF_ST_get_drf_fail1(data)                                                   ((0x00000004&(data))>>2)
#define DRF_ST_drf_fail0_shift                                                       (1)
#define DRF_ST_drf_fail0_mask                                                        (0x00000002)
#define DRF_ST_drf_fail0(data)                                                       (0x00000002&((data)<<1))
#define DRF_ST_drf_fail0_src(data)                                                   ((0x00000002&(data))>>1)
#define DRF_ST_get_drf_fail0(data)                                                   ((0x00000002&(data))>>1)
#define DRF_ST_drf_done_shift                                                        (0)
#define DRF_ST_drf_done_mask                                                         (0x00000001)
#define DRF_ST_drf_done(data)                                                        (0x00000001&((data)<<0))
#define DRF_ST_drf_done_src(data)                                                    ((0x00000001&(data))>>0)
#define DRF_ST_get_drf_done(data)                                                    ((0x00000001&(data))>>0)


#define MBIST_CON                                                                    0x9800B138
#define MBIST_CON_reg_addr                                                           "0x9800B138"
#define MBIST_CON_reg                                                                0x9800B138
#define set_MBIST_CON_reg(data)   (*((volatile unsigned int*) MBIST_CON_reg)=data)
#define get_MBIST_CON_reg   (*((volatile unsigned int*) MBIST_CON_reg))
#define MBIST_CON_inst_adr                                                           "0x004E"
#define MBIST_CON_inst                                                               0x004E
#define MBIST_CON_drf_test_resume_shift                                              (2)
#define MBIST_CON_drf_test_resume_mask                                               (0x00000004)
#define MBIST_CON_drf_test_resume(data)                                              (0x00000004&((data)<<2))
#define MBIST_CON_drf_test_resume_src(data)                                          ((0x00000004&(data))>>2)
#define MBIST_CON_get_drf_test_resume(data)                                          ((0x00000004&(data))>>2)
#define MBIST_CON_drf_bist_mode_shift                                                (1)
#define MBIST_CON_drf_bist_mode_mask                                                 (0x00000002)
#define MBIST_CON_drf_bist_mode(data)                                                (0x00000002&((data)<<1))
#define MBIST_CON_drf_bist_mode_src(data)                                            ((0x00000002&(data))>>1)
#define MBIST_CON_get_drf_bist_mode(data)                                            ((0x00000002&(data))>>1)
#define MBIST_CON_bist_mode_shift                                                    (0)
#define MBIST_CON_bist_mode_mask                                                     (0x00000001)
#define MBIST_CON_bist_mode(data)                                                    (0x00000001&((data)<<0))
#define MBIST_CON_bist_mode_src(data)                                                ((0x00000001&(data))>>0)
#define MBIST_CON_get_bist_mode(data)                                                ((0x00000001&(data))>>0)


#define MD_SMQFREERUN                                                                0x9800B140
#define MD_SMQFREERUN_reg_addr                                                       "0x9800B140"
#define MD_SMQFREERUN_reg                                                            0x9800B140
#define set_MD_SMQFREERUN_reg(data)   (*((volatile unsigned int*) MD_SMQFREERUN_reg)=data)
#define get_MD_SMQFREERUN_reg   (*((volatile unsigned int*) MD_SMQFREERUN_reg))
#define MD_SMQFREERUN_inst_adr                                                       "0x0050"
#define MD_SMQFREERUN_inst                                                           0x0050
#define MD_SMQFREERUN_smq_freerun_shift                                              (0)
#define MD_SMQFREERUN_smq_freerun_mask                                               (0x00000001)
#define MD_SMQFREERUN_smq_freerun(data)                                              (0x00000001&((data)<<0))
#define MD_SMQFREERUN_smq_freerun_src(data)                                          ((0x00000001&(data))>>0)
#define MD_SMQFREERUN_get_smq_freerun(data)                                          ((0x00000001&(data))>>0)


#define MD_VMQFREERUN                                                                0x9800B144
#define MD_VMQFREERUN_reg_addr                                                       "0x9800B144"
#define MD_VMQFREERUN_reg                                                            0x9800B144
#define set_MD_VMQFREERUN_reg(data)   (*((volatile unsigned int*) MD_VMQFREERUN_reg)=data)
#define get_MD_VMQFREERUN_reg   (*((volatile unsigned int*) MD_VMQFREERUN_reg))
#define MD_VMQFREERUN_inst_adr                                                       "0x0051"
#define MD_VMQFREERUN_inst                                                           0x0051
#define MD_VMQFREERUN_vmq_freerun_shift                                              (0)
#define MD_VMQFREERUN_vmq_freerun_mask                                               (0x00000001)
#define MD_VMQFREERUN_vmq_freerun(data)                                              (0x00000001&((data)<<0))
#define MD_VMQFREERUN_vmq_freerun_src(data)                                          ((0x00000001&(data))>>0)
#define MD_VMQFREERUN_get_vmq_freerun(data)                                          ((0x00000001&(data))>>0)


#define MD_KMQFREERUN                                                                0x9800B148
#define MD_KMQFREERUN_reg_addr                                                       "0x9800B148"
#define MD_KMQFREERUN_reg                                                            0x9800B148
#define set_MD_KMQFREERUN_reg(data)   (*((volatile unsigned int*) MD_KMQFREERUN_reg)=data)
#define get_MD_KMQFREERUN_reg   (*((volatile unsigned int*) MD_KMQFREERUN_reg))
#define MD_KMQFREERUN_inst_adr                                                       "0x0052"
#define MD_KMQFREERUN_inst                                                           0x0052
#define MD_KMQFREERUN_kmq_freerun_shift                                              (0)
#define MD_KMQFREERUN_kmq_freerun_mask                                               (0x00000001)
#define MD_KMQFREERUN_kmq_freerun(data)                                              (0x00000001&((data)<<0))
#define MD_KMQFREERUN_kmq_freerun_src(data)                                          ((0x00000001&(data))>>0)
#define MD_KMQFREERUN_get_kmq_freerun(data)                                          ((0x00000001&(data))>>0)


#endif
