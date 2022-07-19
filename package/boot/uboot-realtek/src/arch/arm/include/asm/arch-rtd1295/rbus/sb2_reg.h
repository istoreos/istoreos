/**************************************************************
// Spec Version                  : 0.1
// Parser Version                : DVR_Parser_6.3
// CModelGen Version             : 5.0 2009.04.09
// Naming Rule                   :  Register_Name
// Naming Rule                   : Module_Register_Name_reg
// Parse Option                  : Only Parse _op1
// Parse Address Region          : All Address Region 
// Decode bit number             : 12 bits
// Firmware Header Generate Date : 2013/9/5 15:43:41
***************************************************************/


#ifndef _SB2_REG_H_
#define _SB2_REG_H_
#ifdef  _SB2_USE_STRUCT
typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     Semaphore:1;
}HD_SEM;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     swcivairq_en:1;
unsigned int     To_en1:1;
unsigned int     To_en:1;
unsigned int     acivairq_en:1;
unsigned int     reserved_1:1;
unsigned int     scivairq_en:1;
unsigned int     write_data:1;
}INV_INTEN;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     swciva_int:1;
unsigned int     Aciva_int:1;
unsigned int     reserved_1:1;
unsigned int     Sciva_int:1;
unsigned int     write_data:1;
}INV_INTSTAT;

typedef struct 
{
unsigned int     Inv_adr:32;
}INV_ADDR;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     To_thr1:3;
unsigned int     To_thr:2;
}DEBUG_REG;

typedef struct 
{
unsigned int     reserved_0:10;
unsigned int     Wr_hold_cyc:4;
unsigned int     reserved_1:3;
unsigned int     Wwr_cyc:5;
unsigned int     Wr_cyc:5;
unsigned int     Rd_cyc:5;
}FLASH_CTRL;

typedef struct 
{
unsigned int     reserved_0:17;
unsigned int     write_en13:1;
unsigned int     mult_wr_en:1;
unsigned int     write_en11:1;
unsigned int     ac_in_order:1;
unsigned int     write_en9:1;
unsigned int     ac_bypass:1;
unsigned int     write_en7:1;
unsigned int     ac_merge:1;
unsigned int     reserved_1:3;
unsigned int     write_en2:1;
unsigned int     sc_in_order:1;
unsigned int     reserved_2:2;
}WRAPPER_CTRL;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     enable:1;
}SCPU_INT_CHECK;

typedef struct 
{
unsigned int     Sync:32;
}SYNC;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     Dbg_mode:5;
}SB2_DBG;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     write_enable3:1;
unsigned int     sel1:6;
unsigned int     write_enable2:1;
unsigned int     sel0:6;
unsigned int     write_enable1:1;
unsigned int     enable:1;
}DEBUG;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     speed_up:1;
}LEXRA_CTRL;

typedef struct 
{
unsigned int     reserved_0:20;
unsigned int     int_aswc:1;
unsigned int     int_swca:1;
unsigned int     reserved_1:6;
unsigned int     int_as:1;
unsigned int     reserved_2:1;
unsigned int     int_sa:1;
unsigned int     write_data:1;
}CPU_INT;

typedef struct 
{
unsigned int     reserved_0:20;
unsigned int     int_aswc_en:1;
unsigned int     int_swca_en:1;
unsigned int     reserved_1:6;
unsigned int     int_as_en:1;
unsigned int     reserved_2:1;
unsigned int     int_sa_en:1;
unsigned int     write_data:1;
}CPU_INT_EN;

typedef struct 
{
unsigned int     reserved_0:26;
unsigned int     pending:1;
unsigned int     reserved_1:2;
unsigned int     mask_id:3;
}DREQ_MASK;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     Chip_id:16;
}CHIP_ID;

typedef struct 
{
unsigned int     Revise_id:16;
unsigned int     reserved_0:16;
}CHIP_INFO;

typedef struct 
{
unsigned int     reserved_0:20;
unsigned int     write_en6:1;
unsigned int     acpu_rbus_go:1;
unsigned int     reserved_1:2;
unsigned int     write_en4:1;
unsigned int     scpu_rbus_go:1;
unsigned int     write_en3:1;
unsigned int     acpu_dbus_go:1;
unsigned int     reserved_2:4;
}PC_CTRL;

typedef struct 
{
unsigned int     acpu_dbus_acc:32;
}ACPU_DACC;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     acpu_dreq_num:24;
}ACPU_DREQ_NUM;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     acpu_dreq_max:16;
}ACPU_DREQ_MAX;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     acpu_dreq_ack:26;
}ACPU_DREQ_ACK;

typedef struct 
{
unsigned int     scpu_rbus_acc:32;
}SCPU_RACC;

typedef struct 
{
unsigned int     scpu_rreq_max:8;
unsigned int     scpu_rreq_num:24;
}SCPU_RREQ_RLT;

typedef struct 
{
unsigned int     acpu_rbus_acc:32;
}ACPU_RACC;

typedef struct 
{
unsigned int     acpu_rreq_max:8;
unsigned int     acpu_rreq_num:24;
}ACPU_RREQ_RLT;

typedef struct 
{
unsigned int     Dbg_start_addr:32;
}DBG_START;

typedef struct 
{
unsigned int     Dbg_end_addr:32;
}DBG_END;

typedef struct 
{
unsigned int     reserved_0:18;
unsigned int     write_en6:1;
unsigned int     Dbg_acpu_chk_en:1;
unsigned int     reserved_1:2;
unsigned int     write_en4:1;
unsigned int     Dbg_scpu_chk_en:1;
unsigned int     write_en3:1;
unsigned int     Dbg_wr_chk:2;
unsigned int     write_en2:1;
unsigned int     Dbg_id_chk:2;
unsigned int     write_en1:1;
unsigned int     Dbg_en:1;
}DBG_CTRL;

typedef struct 
{
unsigned int     dbg_addr:32;
}DBG_ADDR;

typedef struct 
{
unsigned int     reserved_0:26;
unsigned int     acpu_dbg_write:1;
unsigned int     acpu_dbg_dacc:1;
unsigned int     scpu_dbg_write:1;
unsigned int     scpu_dbg_dacc:1;
unsigned int     reserved_1:2;
}DBG_ADDR1;

typedef struct 
{
unsigned int     reserved_0:19;
unsigned int     acpu_int:1;
unsigned int     reserved_1:1;
unsigned int     scpu_int:1;
unsigned int     acpu_int_en:1;
unsigned int     reserved_2:1;
unsigned int     scpu_int_en:1;
unsigned int     acpu_neg_int:1;
unsigned int     reserved_3:1;
unsigned int     scpu_neg_int:1;
unsigned int     acpu_neg_int_en:1;
unsigned int     reserved_4:1;
unsigned int     scpu_neg_int_en:1;
unsigned int     write_data:1;
}DBG_INT;

typedef struct 
{
unsigned int     data:32;
}DUMMY;

typedef struct 
{
unsigned int     data:32;
}SHADOW;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     Semaphore:1;
}HD_SEM_NEW;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     inva_wr_sec2_en:1;
unsigned int     reserved_1:1;
unsigned int     inva_wr_sec1_en:1;
}RBUS_INVA_ACC_CTRL;

typedef struct 
{
unsigned int     reserved_0:13;
unsigned int     sec1_start:17;
unsigned int     reserved_1:2;
}RBUS_INVA_ACC_SEC1_START;

typedef struct 
{
unsigned int     reserved_0:13;
unsigned int     sec1_end:17;
unsigned int     reserved_1:2;
}RBUS_INVA_ACC_SEC1_END;

typedef struct 
{
unsigned int     reserved_0:13;
unsigned int     sec2_start:17;
unsigned int     reserved_1:2;
}RBUS_INVA_ACC_SEC2_START;

typedef struct 
{
unsigned int     reserved_0:13;
unsigned int     sec2_end:17;
unsigned int     reserved_1:2;
}RBUS_INVA_ACC_SEC2_END;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     crc_cmp_latch_en:1;
}RBUS_CMP_CTRL;

typedef struct 
{
unsigned int     crc_cmp_expect:32;
}RBUS_CMP_DATA;

typedef struct 
{
unsigned int     crc_cmp_result:32;
}RBUS_CMP_RESULT;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     sb2_bist_rstn:1;
unsigned int     sb2_bist_en:1;
unsigned int     sb2_rom_ls:1;
unsigned int     sb2_rom_rme:1;
unsigned int     sb2_rom_rm:4;
}BIST_CTRL;

typedef struct 
{
unsigned int     reserved_0:15;
unsigned int     sb2_rom_bist_done:1;
unsigned int     sb2_misr_dataout_0:16;
}BIST_STATUS;

typedef struct 
{
unsigned int     reserved_0:21;
unsigned int     dual_mode:2;
unsigned int     fat_mode:1;
unsigned int     opc:8;
}SFC_OPCODE;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     reserved_1:11;
unsigned int     dataen:1;
unsigned int     adren:1;
unsigned int     dmycnt:3;
}SFC_CTL;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     reserved_1:7;
unsigned int     mode:1;
unsigned int     fdiv:8;
}SFC_SCK;

typedef struct 
{
unsigned int     tdt:16;
unsigned int     Phcnt:8;
unsigned int     Plcnt:8;
}SFC_CE;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     write_en5:1;
unsigned int     rdy:1;
unsigned int     reserved_1:24;
unsigned int     write_en1:1;
unsigned int     wp_n:1;
}SFC_WP;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     pos_latch:1;
}SFC_POS_LATCH;

typedef struct 
{
unsigned int     reserved_0:23;
unsigned int     wt_prog_done:1;
unsigned int     rdsr_op:8;
}SFC_WAIT_WR;

typedef struct 
{
unsigned int     reserved_0:23;
unsigned int     wt_prog_en:1;
unsigned int     wr_en_op:8;
}SFC_EN_WR;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     sf_dclk_sel:1;
unsigned int     fifo_write_tap:3;
unsigned int     fast_read_en:1;
}SFC_FAST_RD;

typedef struct 
{
unsigned int     delay_clk_tap:32;
}SFC_SCK_TAP;

#endif

#define HD_SEM                                                                       0x9801A000
#define HD_SEM_reg_addr                                                              "0x9801A000"
#define HD_SEM_reg                                                                   0x9801A000
#define set_HD_SEM_reg(data)   (*((volatile unsigned int*) HD_SEM_reg)=data)
#define get_HD_SEM_reg   (*((volatile unsigned int*) HD_SEM_reg))
#define HD_SEM_inst_adr                                                              "0x0000"
#define HD_SEM_inst                                                                  0x0000
#define HD_SEM_Semaphore_shift                                                       (0)
#define HD_SEM_Semaphore_mask                                                        (0x00000001)
#define HD_SEM_Semaphore(data)                                                       (0x00000001&((data)<<0))
#define HD_SEM_Semaphore_src(data)                                                   ((0x00000001&(data))>>0)
#define HD_SEM_get_Semaphore(data)                                                   ((0x00000001&(data))>>0)


#define INV_INTEN                                                                    0x9801A004
#define INV_INTEN_reg_addr                                                           "0x9801A004"
#define INV_INTEN_reg                                                                0x9801A004
#define set_INV_INTEN_reg(data)   (*((volatile unsigned int*) INV_INTEN_reg)=data)
#define get_INV_INTEN_reg   (*((volatile unsigned int*) INV_INTEN_reg))
#define INV_INTEN_inst_adr                                                           "0x0001"
#define INV_INTEN_inst                                                               0x0001
#define INV_INTEN_swcivairq_en_shift                                                 (6)
#define INV_INTEN_swcivairq_en_mask                                                  (0x00000040)
#define INV_INTEN_swcivairq_en(data)                                                 (0x00000040&((data)<<6))
#define INV_INTEN_swcivairq_en_src(data)                                             ((0x00000040&(data))>>6)
#define INV_INTEN_get_swcivairq_en(data)                                             ((0x00000040&(data))>>6)
#define INV_INTEN_To_en1_shift                                                       (5)
#define INV_INTEN_To_en1_mask                                                        (0x00000020)
#define INV_INTEN_To_en1(data)                                                       (0x00000020&((data)<<5))
#define INV_INTEN_To_en1_src(data)                                                   ((0x00000020&(data))>>5)
#define INV_INTEN_get_To_en1(data)                                                   ((0x00000020&(data))>>5)
#define INV_INTEN_To_en_shift                                                        (4)
#define INV_INTEN_To_en_mask                                                         (0x00000010)
#define INV_INTEN_To_en(data)                                                        (0x00000010&((data)<<4))
#define INV_INTEN_To_en_src(data)                                                    ((0x00000010&(data))>>4)
#define INV_INTEN_get_To_en(data)                                                    ((0x00000010&(data))>>4)
#define INV_INTEN_acivairq_en_shift                                                  (3)
#define INV_INTEN_acivairq_en_mask                                                   (0x00000008)
#define INV_INTEN_acivairq_en(data)                                                  (0x00000008&((data)<<3))
#define INV_INTEN_acivairq_en_src(data)                                              ((0x00000008&(data))>>3)
#define INV_INTEN_get_acivairq_en(data)                                              ((0x00000008&(data))>>3)
#define INV_INTEN_scivairq_en_shift                                                  (1)
#define INV_INTEN_scivairq_en_mask                                                   (0x00000002)
#define INV_INTEN_scivairq_en(data)                                                  (0x00000002&((data)<<1))
#define INV_INTEN_scivairq_en_src(data)                                              ((0x00000002&(data))>>1)
#define INV_INTEN_get_scivairq_en(data)                                              ((0x00000002&(data))>>1)
#define INV_INTEN_write_data_shift                                                   (0)
#define INV_INTEN_write_data_mask                                                    (0x00000001)
#define INV_INTEN_write_data(data)                                                   (0x00000001&((data)<<0))
#define INV_INTEN_write_data_src(data)                                               ((0x00000001&(data))>>0)
#define INV_INTEN_get_write_data(data)                                               ((0x00000001&(data))>>0)


#define INV_INTSTAT                                                                  0x9801A008
#define INV_INTSTAT_reg_addr                                                         "0x9801A008"
#define INV_INTSTAT_reg                                                              0x9801A008
#define set_INV_INTSTAT_reg(data)   (*((volatile unsigned int*) INV_INTSTAT_reg)=data)
#define get_INV_INTSTAT_reg   (*((volatile unsigned int*) INV_INTSTAT_reg))
#define INV_INTSTAT_inst_adr                                                         "0x0002"
#define INV_INTSTAT_inst                                                             0x0002
#define INV_INTSTAT_swciva_int_shift                                                 (4)
#define INV_INTSTAT_swciva_int_mask                                                  (0x00000010)
#define INV_INTSTAT_swciva_int(data)                                                 (0x00000010&((data)<<4))
#define INV_INTSTAT_swciva_int_src(data)                                             ((0x00000010&(data))>>4)
#define INV_INTSTAT_get_swciva_int(data)                                             ((0x00000010&(data))>>4)
#define INV_INTSTAT_Aciva_int_shift                                                  (3)
#define INV_INTSTAT_Aciva_int_mask                                                   (0x00000008)
#define INV_INTSTAT_Aciva_int(data)                                                  (0x00000008&((data)<<3))
#define INV_INTSTAT_Aciva_int_src(data)                                              ((0x00000008&(data))>>3)
#define INV_INTSTAT_get_Aciva_int(data)                                              ((0x00000008&(data))>>3)
#define INV_INTSTAT_Sciva_int_shift                                                  (1)
#define INV_INTSTAT_Sciva_int_mask                                                   (0x00000002)
#define INV_INTSTAT_Sciva_int(data)                                                  (0x00000002&((data)<<1))
#define INV_INTSTAT_Sciva_int_src(data)                                              ((0x00000002&(data))>>1)
#define INV_INTSTAT_get_Sciva_int(data)                                              ((0x00000002&(data))>>1)
#define INV_INTSTAT_write_data_shift                                                 (0)
#define INV_INTSTAT_write_data_mask                                                  (0x00000001)
#define INV_INTSTAT_write_data(data)                                                 (0x00000001&((data)<<0))
#define INV_INTSTAT_write_data_src(data)                                             ((0x00000001&(data))>>0)
#define INV_INTSTAT_get_write_data(data)                                             ((0x00000001&(data))>>0)


#define INV_ADDR                                                                     0x9801A00C
#define INV_ADDR_reg_addr                                                            "0x9801A00C"
#define INV_ADDR_reg                                                                 0x9801A00C
#define set_INV_ADDR_reg(data)   (*((volatile unsigned int*) INV_ADDR_reg)=data)
#define get_INV_ADDR_reg   (*((volatile unsigned int*) INV_ADDR_reg))
#define INV_ADDR_inst_adr                                                            "0x0003"
#define INV_ADDR_inst                                                                0x0003
#define INV_ADDR_Inv_adr_shift                                                       (0)
#define INV_ADDR_Inv_adr_mask                                                        (0xFFFFFFFF)
#define INV_ADDR_Inv_adr(data)                                                       (0xFFFFFFFF&((data)<<0))
#define INV_ADDR_Inv_adr_src(data)                                                   ((0xFFFFFFFF&(data))>>0)
#define INV_ADDR_get_Inv_adr(data)                                                   ((0xFFFFFFFF&(data))>>0)


#define DEBUG_REG                                                                    0x9801A010
#define DEBUG_REG_reg_addr                                                           "0x9801A010"
#define DEBUG_REG_reg                                                                0x9801A010
#define set_DEBUG_REG_reg(data)   (*((volatile unsigned int*) DEBUG_REG_reg)=data)
#define get_DEBUG_REG_reg   (*((volatile unsigned int*) DEBUG_REG_reg))
#define DEBUG_REG_inst_adr                                                           "0x0004"
#define DEBUG_REG_inst                                                               0x0004
#define DEBUG_REG_To_thr1_shift                                                      (2)
#define DEBUG_REG_To_thr1_mask                                                       (0x0000001C)
#define DEBUG_REG_To_thr1(data)                                                      (0x0000001C&((data)<<2))
#define DEBUG_REG_To_thr1_src(data)                                                  ((0x0000001C&(data))>>2)
#define DEBUG_REG_get_To_thr1(data)                                                  ((0x0000001C&(data))>>2)
#define DEBUG_REG_To_thr_shift                                                       (0)
#define DEBUG_REG_To_thr_mask                                                        (0x00000003)
#define DEBUG_REG_To_thr(data)                                                       (0x00000003&((data)<<0))
#define DEBUG_REG_To_thr_src(data)                                                   ((0x00000003&(data))>>0)
#define DEBUG_REG_get_To_thr(data)                                                   ((0x00000003&(data))>>0)


#define FLASH_CTRL                                                                   0x9801A014
#define FLASH_CTRL_reg_addr                                                          "0x9801A014"
#define FLASH_CTRL_reg                                                               0x9801A014
#define set_FLASH_CTRL_reg(data)   (*((volatile unsigned int*) FLASH_CTRL_reg)=data)
#define get_FLASH_CTRL_reg   (*((volatile unsigned int*) FLASH_CTRL_reg))
#define FLASH_CTRL_inst_adr                                                          "0x0005"
#define FLASH_CTRL_inst                                                              0x0005
#define FLASH_CTRL_Wr_hold_cyc_shift                                                 (18)
#define FLASH_CTRL_Wr_hold_cyc_mask                                                  (0x003C0000)
#define FLASH_CTRL_Wr_hold_cyc(data)                                                 (0x003C0000&((data)<<18))
#define FLASH_CTRL_Wr_hold_cyc_src(data)                                             ((0x003C0000&(data))>>18)
#define FLASH_CTRL_get_Wr_hold_cyc(data)                                             ((0x003C0000&(data))>>18)
#define FLASH_CTRL_Wwr_cyc_shift                                                     (10)
#define FLASH_CTRL_Wwr_cyc_mask                                                      (0x00007C00)
#define FLASH_CTRL_Wwr_cyc(data)                                                     (0x00007C00&((data)<<10))
#define FLASH_CTRL_Wwr_cyc_src(data)                                                 ((0x00007C00&(data))>>10)
#define FLASH_CTRL_get_Wwr_cyc(data)                                                 ((0x00007C00&(data))>>10)
#define FLASH_CTRL_Wr_cyc_shift                                                      (5)
#define FLASH_CTRL_Wr_cyc_mask                                                       (0x000003E0)
#define FLASH_CTRL_Wr_cyc(data)                                                      (0x000003E0&((data)<<5))
#define FLASH_CTRL_Wr_cyc_src(data)                                                  ((0x000003E0&(data))>>5)
#define FLASH_CTRL_get_Wr_cyc(data)                                                  ((0x000003E0&(data))>>5)
#define FLASH_CTRL_Rd_cyc_shift                                                      (0)
#define FLASH_CTRL_Rd_cyc_mask                                                       (0x0000001F)
#define FLASH_CTRL_Rd_cyc(data)                                                      (0x0000001F&((data)<<0))
#define FLASH_CTRL_Rd_cyc_src(data)                                                  ((0x0000001F&(data))>>0)
#define FLASH_CTRL_get_Rd_cyc(data)                                                  ((0x0000001F&(data))>>0)


#define WRAPPER_CTRL                                                                 0x9801A018
#define WRAPPER_CTRL_reg_addr                                                        "0x9801A018"
#define WRAPPER_CTRL_reg                                                             0x9801A018
#define set_WRAPPER_CTRL_reg(data)   (*((volatile unsigned int*) WRAPPER_CTRL_reg)=data)
#define get_WRAPPER_CTRL_reg   (*((volatile unsigned int*) WRAPPER_CTRL_reg))
#define WRAPPER_CTRL_inst_adr                                                        "0x0006"
#define WRAPPER_CTRL_inst                                                            0x0006
#define WRAPPER_CTRL_write_en13_shift                                                (14)
#define WRAPPER_CTRL_write_en13_mask                                                 (0x00004000)
#define WRAPPER_CTRL_write_en13(data)                                                (0x00004000&((data)<<14))
#define WRAPPER_CTRL_write_en13_src(data)                                            ((0x00004000&(data))>>14)
#define WRAPPER_CTRL_get_write_en13(data)                                            ((0x00004000&(data))>>14)
#define WRAPPER_CTRL_mult_wr_en_shift                                                (13)
#define WRAPPER_CTRL_mult_wr_en_mask                                                 (0x00002000)
#define WRAPPER_CTRL_mult_wr_en(data)                                                (0x00002000&((data)<<13))
#define WRAPPER_CTRL_mult_wr_en_src(data)                                            ((0x00002000&(data))>>13)
#define WRAPPER_CTRL_get_mult_wr_en(data)                                            ((0x00002000&(data))>>13)
#define WRAPPER_CTRL_write_en11_shift                                                (12)
#define WRAPPER_CTRL_write_en11_mask                                                 (0x00001000)
#define WRAPPER_CTRL_write_en11(data)                                                (0x00001000&((data)<<12))
#define WRAPPER_CTRL_write_en11_src(data)                                            ((0x00001000&(data))>>12)
#define WRAPPER_CTRL_get_write_en11(data)                                            ((0x00001000&(data))>>12)
#define WRAPPER_CTRL_ac_in_order_shift                                               (11)
#define WRAPPER_CTRL_ac_in_order_mask                                                (0x00000800)
#define WRAPPER_CTRL_ac_in_order(data)                                               (0x00000800&((data)<<11))
#define WRAPPER_CTRL_ac_in_order_src(data)                                           ((0x00000800&(data))>>11)
#define WRAPPER_CTRL_get_ac_in_order(data)                                           ((0x00000800&(data))>>11)
#define WRAPPER_CTRL_write_en9_shift                                                 (10)
#define WRAPPER_CTRL_write_en9_mask                                                  (0x00000400)
#define WRAPPER_CTRL_write_en9(data)                                                 (0x00000400&((data)<<10))
#define WRAPPER_CTRL_write_en9_src(data)                                             ((0x00000400&(data))>>10)
#define WRAPPER_CTRL_get_write_en9(data)                                             ((0x00000400&(data))>>10)
#define WRAPPER_CTRL_ac_bypass_shift                                                 (9)
#define WRAPPER_CTRL_ac_bypass_mask                                                  (0x00000200)
#define WRAPPER_CTRL_ac_bypass(data)                                                 (0x00000200&((data)<<9))
#define WRAPPER_CTRL_ac_bypass_src(data)                                             ((0x00000200&(data))>>9)
#define WRAPPER_CTRL_get_ac_bypass(data)                                             ((0x00000200&(data))>>9)
#define WRAPPER_CTRL_write_en7_shift                                                 (8)
#define WRAPPER_CTRL_write_en7_mask                                                  (0x00000100)
#define WRAPPER_CTRL_write_en7(data)                                                 (0x00000100&((data)<<8))
#define WRAPPER_CTRL_write_en7_src(data)                                             ((0x00000100&(data))>>8)
#define WRAPPER_CTRL_get_write_en7(data)                                             ((0x00000100&(data))>>8)
#define WRAPPER_CTRL_ac_merge_shift                                                  (7)
#define WRAPPER_CTRL_ac_merge_mask                                                   (0x00000080)
#define WRAPPER_CTRL_ac_merge(data)                                                  (0x00000080&((data)<<7))
#define WRAPPER_CTRL_ac_merge_src(data)                                              ((0x00000080&(data))>>7)
#define WRAPPER_CTRL_get_ac_merge(data)                                              ((0x00000080&(data))>>7)
#define WRAPPER_CTRL_write_en2_shift                                                 (3)
#define WRAPPER_CTRL_write_en2_mask                                                  (0x00000008)
#define WRAPPER_CTRL_write_en2(data)                                                 (0x00000008&((data)<<3))
#define WRAPPER_CTRL_write_en2_src(data)                                             ((0x00000008&(data))>>3)
#define WRAPPER_CTRL_get_write_en2(data)                                             ((0x00000008&(data))>>3)
#define WRAPPER_CTRL_sc_in_order_shift                                               (2)
#define WRAPPER_CTRL_sc_in_order_mask                                                (0x00000004)
#define WRAPPER_CTRL_sc_in_order(data)                                               (0x00000004&((data)<<2))
#define WRAPPER_CTRL_sc_in_order_src(data)                                           ((0x00000004&(data))>>2)
#define WRAPPER_CTRL_get_sc_in_order(data)                                           ((0x00000004&(data))>>2)


#define SCPU_INT_CHECK                                                               0x9801A01C
#define SCPU_INT_CHECK_reg_addr                                                      "0x9801A01C"
#define SCPU_INT_CHECK_reg                                                           0x9801A01C
#define set_SCPU_INT_CHECK_reg(data)   (*((volatile unsigned int*) SCPU_INT_CHECK_reg)=data)
#define get_SCPU_INT_CHECK_reg   (*((volatile unsigned int*) SCPU_INT_CHECK_reg))
#define SCPU_INT_CHECK_inst_adr                                                      "0x0007"
#define SCPU_INT_CHECK_inst                                                          0x0007
#define SCPU_INT_CHECK_enable_shift                                                  (0)
#define SCPU_INT_CHECK_enable_mask                                                   (0x00000001)
#define SCPU_INT_CHECK_enable(data)                                                  (0x00000001&((data)<<0))
#define SCPU_INT_CHECK_enable_src(data)                                              ((0x00000001&(data))>>0)
#define SCPU_INT_CHECK_get_enable(data)                                              ((0x00000001&(data))>>0)


#define SYNC                                                                         0x9801A020
#define SYNC_reg_addr                                                                "0x9801A020"
#define SYNC_reg                                                                     0x9801A020
#define set_SYNC_reg(data)   (*((volatile unsigned int*) SYNC_reg)=data)
#define get_SYNC_reg   (*((volatile unsigned int*) SYNC_reg))
#define SYNC_inst_adr                                                                "0x0008"
#define SYNC_inst                                                                    0x0008
#define SYNC_Sync_shift                                                              (0)
#define SYNC_Sync_mask                                                               (0xFFFFFFFF)
#define SYNC_Sync(data)                                                              (0xFFFFFFFF&((data)<<0))
#define SYNC_Sync_src(data)                                                          ((0xFFFFFFFF&(data))>>0)
#define SYNC_get_Sync(data)                                                          ((0xFFFFFFFF&(data))>>0)


#define SB2_DBG                                                                      0x9801A024
#define SB2_DBG_reg_addr                                                             "0x9801A024"
#define SB2_DBG_reg                                                                  0x9801A024
#define SB2_set_DBG_reg(data)   (*((volatile unsigned int*) DBG_reg)=data)           
#define SB2_get_DBG_reg   (*((volatile unsigned int*) DBG_reg))                      
#define SB2_DBG_inst_adr                                                             "0x0009"
#define SB2_DBG_inst                                                                 0x0009
#define SB2_DBG_Dbg_mode_shift                                                       (0)
#define SB2_DBG_Dbg_mode_mask                                                        (0x0000001F)
#define SB2_DBG_Dbg_mode(data)                                                       (0x0000001F&((data)<<0))
#define SB2_DBG_Dbg_mode_src(data)                                                   ((0x0000001F&(data))>>0)
#define SB2_DBG_get_Dbg_mode(data)                                                   ((0x0000001F&(data))>>0)
                                                                                     
                                                                                     
#define SB2_DEBUG                                                                    0x9801A028
#define SB2_DEBUG_reg_addr                                                           "0x9801A028"
#define SB2_DEBUG_reg                                                                0x9801A028
#define SB2_set_DEBUG_reg(data)   (*((volatile unsigned int*) DEBUG_reg)=data)       
#define SB2_get_DEBUG_reg   (*((volatile unsigned int*) DEBUG_reg))                  
#define SB2_DEBUG_inst_adr                                                           "0x000A"
#define SB2_DEBUG_inst                                                               0x000A
#define SB2_DEBUG_write_enable3_shift                                                (15)
#define SB2_DEBUG_write_enable3_mask                                                 (0x00008000)
#define SB2_DEBUG_write_enable3(data)                                                (0x00008000&((data)<<15))
#define SB2_DEBUG_write_enable3_src(data)                                            ((0x00008000&(data))>>15)
#define SB2_DEBUG_get_write_enable3(data)                                            ((0x00008000&(data))>>15)
#define SB2_DEBUG_sel1_shift                                                         (9)
#define SB2_DEBUG_sel1_mask                                                          (0x00007E00)
#define SB2_DEBUG_sel1(data)                                                         (0x00007E00&((data)<<9))
#define SB2_DEBUG_sel1_src(data)                                                     ((0x00007E00&(data))>>9)
#define SB2_DEBUG_get_sel1(data)                                                     ((0x00007E00&(data))>>9)
#define SB2_DEBUG_write_enable2_shift                                                (8)
#define SB2_DEBUG_write_enable2_mask                                                 (0x00000100)
#define SB2_DEBUG_write_enable2(data)                                                (0x00000100&((data)<<8))
#define SB2_DEBUG_write_enable2_src(data)                                            ((0x00000100&(data))>>8)
#define SB2_DEBUG_get_write_enable2(data)                                            ((0x00000100&(data))>>8)
#define SB2_DEBUG_sel0_shift                                                         (2)
#define SB2_DEBUG_sel0_mask                                                          (0x000000FC)
#define SB2_DEBUG_sel0(data)                                                         (0x000000FC&((data)<<2))
#define SB2_DEBUG_sel0_src(data)                                                     ((0x000000FC&(data))>>2)
#define SB2_DEBUG_get_sel0(data)                                                     ((0x000000FC&(data))>>2)
#define SB2_DEBUG_write_enable1_shift                                                (1)
#define SB2_DEBUG_write_enable1_mask                                                 (0x00000002)
#define SB2_DEBUG_write_enable1(data)                                                (0x00000002&((data)<<1))
#define SB2_DEBUG_write_enable1_src(data)                                            ((0x00000002&(data))>>1)
#define SB2_DEBUG_get_write_enable1(data)                                            ((0x00000002&(data))>>1)
#define SB2_DEBUG_enable_shift                                                       (0)
#define SB2_DEBUG_enable_mask                                                        (0x00000001)
#define SB2_DEBUG_enable(data)                                                       (0x00000001&((data)<<0))
#define SB2_DEBUG_enable_src(data)                                                   ((0x00000001&(data))>>0)
#define SB2_DEBUG_get_enable(data)                                                   ((0x00000001&(data))>>0)


#define LEXRA_CTRL                                                                   0x9801A070
#define LEXRA_CTRL_reg_addr                                                          "0x9801A070"
#define LEXRA_CTRL_reg                                                               0x9801A070
#define set_LEXRA_CTRL_reg(data)   (*((volatile unsigned int*) LEXRA_CTRL_reg)=data)
#define get_LEXRA_CTRL_reg   (*((volatile unsigned int*) LEXRA_CTRL_reg))
#define LEXRA_CTRL_inst_adr                                                          "0x001C"
#define LEXRA_CTRL_inst                                                              0x001C
#define LEXRA_CTRL_speed_up_shift                                                    (0)
#define LEXRA_CTRL_speed_up_mask                                                     (0x00000001)
#define LEXRA_CTRL_speed_up(data)                                                    (0x00000001&((data)<<0))
#define LEXRA_CTRL_speed_up_src(data)                                                ((0x00000001&(data))>>0)
#define LEXRA_CTRL_get_speed_up(data)                                                ((0x00000001&(data))>>0)


#define CPU_INT                                                                      0x9801A104
#define CPU_INT_reg_addr                                                             "0x9801A104"
#define CPU_INT_reg                                                                  0x9801A104
#define set_CPU_INT_reg(data)   (*((volatile unsigned int*) CPU_INT_reg)=data)
#define get_CPU_INT_reg   (*((volatile unsigned int*) CPU_INT_reg))
#define CPU_INT_inst_adr                                                             "0x0041"
#define CPU_INT_inst                                                                 0x0041
#define CPU_INT_int_aswc_shift                                                       (11)
#define CPU_INT_int_aswc_mask                                                        (0x00000800)
#define CPU_INT_int_aswc(data)                                                       (0x00000800&((data)<<11))
#define CPU_INT_int_aswc_src(data)                                                   ((0x00000800&(data))>>11)
#define CPU_INT_get_int_aswc(data)                                                   ((0x00000800&(data))>>11)
#define CPU_INT_int_swca_shift                                                       (10)
#define CPU_INT_int_swca_mask                                                        (0x00000400)
#define CPU_INT_int_swca(data)                                                       (0x00000400&((data)<<10))
#define CPU_INT_int_swca_src(data)                                                   ((0x00000400&(data))>>10)
#define CPU_INT_get_int_swca(data)                                                   ((0x00000400&(data))>>10)
#define CPU_INT_int_as_shift                                                         (3)
#define CPU_INT_int_as_mask                                                          (0x00000008)
#define CPU_INT_int_as(data)                                                         (0x00000008&((data)<<3))
#define CPU_INT_int_as_src(data)                                                     ((0x00000008&(data))>>3)
#define CPU_INT_get_int_as(data)                                                     ((0x00000008&(data))>>3)
#define CPU_INT_int_sa_shift                                                         (1)
#define CPU_INT_int_sa_mask                                                          (0x00000002)
#define CPU_INT_int_sa(data)                                                         (0x00000002&((data)<<1))
#define CPU_INT_int_sa_src(data)                                                     ((0x00000002&(data))>>1)
#define CPU_INT_get_int_sa(data)                                                     ((0x00000002&(data))>>1)
#define CPU_INT_write_data_shift                                                     (0)
#define CPU_INT_write_data_mask                                                      (0x00000001)
#define CPU_INT_write_data(data)                                                     (0x00000001&((data)<<0))
#define CPU_INT_write_data_src(data)                                                 ((0x00000001&(data))>>0)
#define CPU_INT_get_write_data(data)                                                 ((0x00000001&(data))>>0)


#define CPU_INT_EN                                                                   0x9801A108
#define CPU_INT_EN_reg_addr                                                          "0x9801A108"
#define CPU_INT_EN_reg                                                               0x9801A108
#define set_CPU_INT_EN_reg(data)   (*((volatile unsigned int*) CPU_INT_EN_reg)=data)
#define get_CPU_INT_EN_reg   (*((volatile unsigned int*) CPU_INT_EN_reg))
#define CPU_INT_EN_inst_adr                                                          "0x0042"
#define CPU_INT_EN_inst                                                              0x0042
#define CPU_INT_EN_int_aswc_en_shift                                                 (11)
#define CPU_INT_EN_int_aswc_en_mask                                                  (0x00000800)
#define CPU_INT_EN_int_aswc_en(data)                                                 (0x00000800&((data)<<11))
#define CPU_INT_EN_int_aswc_en_src(data)                                             ((0x00000800&(data))>>11)
#define CPU_INT_EN_get_int_aswc_en(data)                                             ((0x00000800&(data))>>11)
#define CPU_INT_EN_int_swca_en_shift                                                 (10)
#define CPU_INT_EN_int_swca_en_mask                                                  (0x00000400)
#define CPU_INT_EN_int_swca_en(data)                                                 (0x00000400&((data)<<10))
#define CPU_INT_EN_int_swca_en_src(data)                                             ((0x00000400&(data))>>10)
#define CPU_INT_EN_get_int_swca_en(data)                                             ((0x00000400&(data))>>10)
#define CPU_INT_EN_int_as_en_shift                                                   (3)
#define CPU_INT_EN_int_as_en_mask                                                    (0x00000008)
#define CPU_INT_EN_int_as_en(data)                                                   (0x00000008&((data)<<3))
#define CPU_INT_EN_int_as_en_src(data)                                               ((0x00000008&(data))>>3)
#define CPU_INT_EN_get_int_as_en(data)                                               ((0x00000008&(data))>>3)
#define CPU_INT_EN_int_sa_en_shift                                                   (1)
#define CPU_INT_EN_int_sa_en_mask                                                    (0x00000002)
#define CPU_INT_EN_int_sa_en(data)                                                   (0x00000002&((data)<<1))
#define CPU_INT_EN_int_sa_en_src(data)                                               ((0x00000002&(data))>>1)
#define CPU_INT_EN_get_int_sa_en(data)                                               ((0x00000002&(data))>>1)
#define CPU_INT_EN_write_data_shift                                                  (0)
#define CPU_INT_EN_write_data_mask                                                   (0x00000001)
#define CPU_INT_EN_write_data(data)                                                  (0x00000001&((data)<<0))
#define CPU_INT_EN_write_data_src(data)                                              ((0x00000001&(data))>>0)
#define CPU_INT_EN_get_write_data(data)                                              ((0x00000001&(data))>>0)


#define DREQ_MASK                                                                    0x9801A138
#define DREQ_MASK_reg_addr                                                           "0x9801A138"
#define DREQ_MASK_reg                                                                0x9801A138
#define set_DREQ_MASK_reg(data)   (*((volatile unsigned int*) DREQ_MASK_reg)=data)
#define get_DREQ_MASK_reg   (*((volatile unsigned int*) DREQ_MASK_reg))
#define DREQ_MASK_inst_adr                                                           "0x004E"
#define DREQ_MASK_inst                                                               0x004E
#define DREQ_MASK_pending_shift                                                      (5)
#define DREQ_MASK_pending_mask                                                       (0x00000020)
#define DREQ_MASK_pending(data)                                                      (0x00000020&((data)<<5))
#define DREQ_MASK_pending_src(data)                                                  ((0x00000020&(data))>>5)
#define DREQ_MASK_get_pending(data)                                                  ((0x00000020&(data))>>5)
#define DREQ_MASK_mask_id_shift                                                      (0)
#define DREQ_MASK_mask_id_mask                                                       (0x00000007)
#define DREQ_MASK_mask_id(data)                                                      (0x00000007&((data)<<0))
#define DREQ_MASK_mask_id_src(data)                                                  ((0x00000007&(data))>>0)
#define DREQ_MASK_get_mask_id(data)                                                  ((0x00000007&(data))>>0)


#define CHIP_ID                                                                      0x9801A200
#define CHIP_ID_reg_addr                                                             "0x9801A200"
#define CHIP_ID_reg                                                                  0x9801A200
#define set_CHIP_ID_reg(data)   (*((volatile unsigned int*) CHIP_ID_reg)=data)
#define get_CHIP_ID_reg   (*((volatile unsigned int*) CHIP_ID_reg))
#define CHIP_ID_inst_adr                                                             "0x0080"
#define CHIP_ID_inst                                                                 0x0080
#define CHIP_ID_Chip_id_shift                                                        (0)
#define CHIP_ID_Chip_id_mask                                                         (0x0000FFFF)
#define CHIP_ID_Chip_id(data)                                                        (0x0000FFFF&((data)<<0))
#define CHIP_ID_Chip_id_src(data)                                                    ((0x0000FFFF&(data))>>0)
#define CHIP_ID_get_Chip_id(data)                                                    ((0x0000FFFF&(data))>>0)


#define CHIP_INFO                                                                    0x9801A204
#define CHIP_INFO_reg_addr                                                           "0x9801A204"
#define CHIP_INFO_reg                                                                0x9801A204
#define set_CHIP_INFO_reg(data)   (*((volatile unsigned int*) CHIP_INFO_reg)=data)
#define get_CHIP_INFO_reg   (*((volatile unsigned int*) CHIP_INFO_reg))
#define CHIP_INFO_inst_adr                                                           "0x0081"
#define CHIP_INFO_inst                                                               0x0081
#define CHIP_INFO_Revise_id_shift                                                    (16)
#define CHIP_INFO_Revise_id_mask                                                     (0xFFFF0000)
#define CHIP_INFO_Revise_id(data)                                                    (0xFFFF0000&((data)<<16))
#define CHIP_INFO_Revise_id_src(data)                                                ((0xFFFF0000&(data))>>16)
#define CHIP_INFO_get_Revise_id(data)                                                ((0xFFFF0000&(data))>>16)


#define PC_CTRL                                                                      0x9801A400
#define PC_CTRL_reg_addr                                                             "0x9801A400"
#define PC_CTRL_reg                                                                  0x9801A400
#define set_PC_CTRL_reg(data)   (*((volatile unsigned int*) PC_CTRL_reg)=data)
#define get_PC_CTRL_reg   (*((volatile unsigned int*) PC_CTRL_reg))
#define PC_CTRL_inst_adr                                                             "0x0000"
#define PC_CTRL_inst                                                                 0x0000
#define PC_CTRL_write_en6_shift                                                      (11)
#define PC_CTRL_write_en6_mask                                                       (0x00000800)
#define PC_CTRL_write_en6(data)                                                      (0x00000800&((data)<<11))
#define PC_CTRL_write_en6_src(data)                                                  ((0x00000800&(data))>>11)
#define PC_CTRL_get_write_en6(data)                                                  ((0x00000800&(data))>>11)
#define PC_CTRL_acpu_rbus_go_shift                                                   (10)
#define PC_CTRL_acpu_rbus_go_mask                                                    (0x00000400)
#define PC_CTRL_acpu_rbus_go(data)                                                   (0x00000400&((data)<<10))
#define PC_CTRL_acpu_rbus_go_src(data)                                               ((0x00000400&(data))>>10)
#define PC_CTRL_get_acpu_rbus_go(data)                                               ((0x00000400&(data))>>10)
#define PC_CTRL_write_en4_shift                                                      (7)
#define PC_CTRL_write_en4_mask                                                       (0x00000080)
#define PC_CTRL_write_en4(data)                                                      (0x00000080&((data)<<7))
#define PC_CTRL_write_en4_src(data)                                                  ((0x00000080&(data))>>7)
#define PC_CTRL_get_write_en4(data)                                                  ((0x00000080&(data))>>7)
#define PC_CTRL_scpu_rbus_go_shift                                                   (6)
#define PC_CTRL_scpu_rbus_go_mask                                                    (0x00000040)
#define PC_CTRL_scpu_rbus_go(data)                                                   (0x00000040&((data)<<6))
#define PC_CTRL_scpu_rbus_go_src(data)                                               ((0x00000040&(data))>>6)
#define PC_CTRL_get_scpu_rbus_go(data)                                               ((0x00000040&(data))>>6)
#define PC_CTRL_write_en3_shift                                                      (5)
#define PC_CTRL_write_en3_mask                                                       (0x00000020)
#define PC_CTRL_write_en3(data)                                                      (0x00000020&((data)<<5))
#define PC_CTRL_write_en3_src(data)                                                  ((0x00000020&(data))>>5)
#define PC_CTRL_get_write_en3(data)                                                  ((0x00000020&(data))>>5)
#define PC_CTRL_acpu_dbus_go_shift                                                   (4)
#define PC_CTRL_acpu_dbus_go_mask                                                    (0x00000010)
#define PC_CTRL_acpu_dbus_go(data)                                                   (0x00000010&((data)<<4))
#define PC_CTRL_acpu_dbus_go_src(data)                                               ((0x00000010&(data))>>4)
#define PC_CTRL_get_acpu_dbus_go(data)                                               ((0x00000010&(data))>>4)


#define ACPU_DACC                                                                    0x9801A42C
#define ACPU_DACC_reg_addr                                                           "0x9801A42C"
#define ACPU_DACC_reg                                                                0x9801A42C
#define set_ACPU_DACC_reg(data)   (*((volatile unsigned int*) ACPU_DACC_reg)=data)
#define get_ACPU_DACC_reg   (*((volatile unsigned int*) ACPU_DACC_reg))
#define ACPU_DACC_inst_adr                                                           "0x000B"
#define ACPU_DACC_inst                                                               0x000B
#define ACPU_DACC_acpu_dbus_acc_shift                                                (0)
#define ACPU_DACC_acpu_dbus_acc_mask                                                 (0xFFFFFFFF)
#define ACPU_DACC_acpu_dbus_acc(data)                                                (0xFFFFFFFF&((data)<<0))
#define ACPU_DACC_acpu_dbus_acc_src(data)                                            ((0xFFFFFFFF&(data))>>0)
#define ACPU_DACC_get_acpu_dbus_acc(data)                                            ((0xFFFFFFFF&(data))>>0)


#define ACPU_DREQ_NUM                                                                0x9801A430
#define ACPU_DREQ_NUM_reg_addr                                                       "0x9801A430"
#define ACPU_DREQ_NUM_reg                                                            0x9801A430
#define set_ACPU_DREQ_NUM_reg(data)   (*((volatile unsigned int*) ACPU_DREQ_NUM_reg)=data)
#define get_ACPU_DREQ_NUM_reg   (*((volatile unsigned int*) ACPU_DREQ_NUM_reg))
#define ACPU_DREQ_NUM_inst_adr                                                       "0x000C"
#define ACPU_DREQ_NUM_inst                                                           0x000C
#define ACPU_DREQ_NUM_acpu_dreq_num_shift                                            (0)
#define ACPU_DREQ_NUM_acpu_dreq_num_mask                                             (0x00FFFFFF)
#define ACPU_DREQ_NUM_acpu_dreq_num(data)                                            (0x00FFFFFF&((data)<<0))
#define ACPU_DREQ_NUM_acpu_dreq_num_src(data)                                        ((0x00FFFFFF&(data))>>0)
#define ACPU_DREQ_NUM_get_acpu_dreq_num(data)                                        ((0x00FFFFFF&(data))>>0)


#define ACPU_DREQ_MAX                                                                0x9801A434
#define ACPU_DREQ_MAX_reg_addr                                                       "0x9801A434"
#define ACPU_DREQ_MAX_reg                                                            0x9801A434
#define set_ACPU_DREQ_MAX_reg(data)   (*((volatile unsigned int*) ACPU_DREQ_MAX_reg)=data)
#define get_ACPU_DREQ_MAX_reg   (*((volatile unsigned int*) ACPU_DREQ_MAX_reg))
#define ACPU_DREQ_MAX_inst_adr                                                       "0x000D"
#define ACPU_DREQ_MAX_inst                                                           0x000D
#define ACPU_DREQ_MAX_acpu_dreq_max_shift                                            (0)
#define ACPU_DREQ_MAX_acpu_dreq_max_mask                                             (0x0000FFFF)
#define ACPU_DREQ_MAX_acpu_dreq_max(data)                                            (0x0000FFFF&((data)<<0))
#define ACPU_DREQ_MAX_acpu_dreq_max_src(data)                                        ((0x0000FFFF&(data))>>0)
#define ACPU_DREQ_MAX_get_acpu_dreq_max(data)                                        ((0x0000FFFF&(data))>>0)


#define ACPU_DREQ_ACK                                                                0x9801A438
#define ACPU_DREQ_ACK_reg_addr                                                       "0x9801A438"
#define ACPU_DREQ_ACK_reg                                                            0x9801A438
#define set_ACPU_DREQ_ACK_reg(data)   (*((volatile unsigned int*) ACPU_DREQ_ACK_reg)=data)
#define get_ACPU_DREQ_ACK_reg   (*((volatile unsigned int*) ACPU_DREQ_ACK_reg))
#define ACPU_DREQ_ACK_inst_adr                                                       "0x000E"
#define ACPU_DREQ_ACK_inst                                                           0x000E
#define ACPU_DREQ_ACK_acpu_dreq_ack_shift                                            (0)
#define ACPU_DREQ_ACK_acpu_dreq_ack_mask                                             (0x03FFFFFF)
#define ACPU_DREQ_ACK_acpu_dreq_ack(data)                                            (0x03FFFFFF&((data)<<0))
#define ACPU_DREQ_ACK_acpu_dreq_ack_src(data)                                        ((0x03FFFFFF&(data))>>0)
#define ACPU_DREQ_ACK_get_acpu_dreq_ack(data)                                        ((0x03FFFFFF&(data))>>0)


#define SCPU_RACC                                                                    0x9801A440
#define SCPU_RACC_reg_addr                                                           "0x9801A440"
#define SCPU_RACC_reg                                                                0x9801A440
#define set_SCPU_RACC_reg(data)   (*((volatile unsigned int*) SCPU_RACC_reg)=data)
#define get_SCPU_RACC_reg   (*((volatile unsigned int*) SCPU_RACC_reg))
#define SCPU_RACC_inst_adr                                                           "0x0010"
#define SCPU_RACC_inst                                                               0x0010
#define SCPU_RACC_scpu_rbus_acc_shift                                                (0)
#define SCPU_RACC_scpu_rbus_acc_mask                                                 (0xFFFFFFFF)
#define SCPU_RACC_scpu_rbus_acc(data)                                                (0xFFFFFFFF&((data)<<0))
#define SCPU_RACC_scpu_rbus_acc_src(data)                                            ((0xFFFFFFFF&(data))>>0)
#define SCPU_RACC_get_scpu_rbus_acc(data)                                            ((0xFFFFFFFF&(data))>>0)


#define SCPU_RREQ_RLT                                                                0x9801A444
#define SCPU_RREQ_RLT_reg_addr                                                       "0x9801A444"
#define SCPU_RREQ_RLT_reg                                                            0x9801A444
#define set_SCPU_RREQ_RLT_reg(data)   (*((volatile unsigned int*) SCPU_RREQ_RLT_reg)=data)
#define get_SCPU_RREQ_RLT_reg   (*((volatile unsigned int*) SCPU_RREQ_RLT_reg))
#define SCPU_RREQ_RLT_inst_adr                                                       "0x0011"
#define SCPU_RREQ_RLT_inst                                                           0x0011
#define SCPU_RREQ_RLT_scpu_rreq_max_shift                                            (24)
#define SCPU_RREQ_RLT_scpu_rreq_max_mask                                             (0xFF000000)
#define SCPU_RREQ_RLT_scpu_rreq_max(data)                                            (0xFF000000&((data)<<24))
#define SCPU_RREQ_RLT_scpu_rreq_max_src(data)                                        ((0xFF000000&(data))>>24)
#define SCPU_RREQ_RLT_get_scpu_rreq_max(data)                                        ((0xFF000000&(data))>>24)
#define SCPU_RREQ_RLT_scpu_rreq_num_shift                                            (0)
#define SCPU_RREQ_RLT_scpu_rreq_num_mask                                             (0x00FFFFFF)
#define SCPU_RREQ_RLT_scpu_rreq_num(data)                                            (0x00FFFFFF&((data)<<0))
#define SCPU_RREQ_RLT_scpu_rreq_num_src(data)                                        ((0x00FFFFFF&(data))>>0)
#define SCPU_RREQ_RLT_get_scpu_rreq_num(data)                                        ((0x00FFFFFF&(data))>>0)


#define ACPU_RACC                                                                    0x9801A450
#define ACPU_RACC_reg_addr                                                           "0x9801A450"
#define ACPU_RACC_reg                                                                0x9801A450
#define set_ACPU_RACC_reg(data)   (*((volatile unsigned int*) ACPU_RACC_reg)=data)
#define get_ACPU_RACC_reg   (*((volatile unsigned int*) ACPU_RACC_reg))
#define ACPU_RACC_inst_adr                                                           "0x0014"
#define ACPU_RACC_inst                                                               0x0014
#define ACPU_RACC_acpu_rbus_acc_shift                                                (0)
#define ACPU_RACC_acpu_rbus_acc_mask                                                 (0xFFFFFFFF)
#define ACPU_RACC_acpu_rbus_acc(data)                                                (0xFFFFFFFF&((data)<<0))
#define ACPU_RACC_acpu_rbus_acc_src(data)                                            ((0xFFFFFFFF&(data))>>0)
#define ACPU_RACC_get_acpu_rbus_acc(data)                                            ((0xFFFFFFFF&(data))>>0)


#define ACPU_RREQ_RLT                                                                0x9801A454
#define ACPU_RREQ_RLT_reg_addr                                                       "0x9801A454"
#define ACPU_RREQ_RLT_reg                                                            0x9801A454
#define set_ACPU_RREQ_RLT_reg(data)   (*((volatile unsigned int*) ACPU_RREQ_RLT_reg)=data)
#define get_ACPU_RREQ_RLT_reg   (*((volatile unsigned int*) ACPU_RREQ_RLT_reg))
#define ACPU_RREQ_RLT_inst_adr                                                       "0x0015"
#define ACPU_RREQ_RLT_inst                                                           0x0015
#define ACPU_RREQ_RLT_acpu_rreq_max_shift                                            (24)
#define ACPU_RREQ_RLT_acpu_rreq_max_mask                                             (0xFF000000)
#define ACPU_RREQ_RLT_acpu_rreq_max(data)                                            (0xFF000000&((data)<<24))
#define ACPU_RREQ_RLT_acpu_rreq_max_src(data)                                        ((0xFF000000&(data))>>24)
#define ACPU_RREQ_RLT_get_acpu_rreq_max(data)                                        ((0xFF000000&(data))>>24)
#define ACPU_RREQ_RLT_acpu_rreq_num_shift                                            (0)
#define ACPU_RREQ_RLT_acpu_rreq_num_mask                                             (0x00FFFFFF)
#define ACPU_RREQ_RLT_acpu_rreq_num(data)                                            (0x00FFFFFF&((data)<<0))
#define ACPU_RREQ_RLT_acpu_rreq_num_src(data)                                        ((0x00FFFFFF&(data))>>0)
#define ACPU_RREQ_RLT_get_acpu_rreq_num(data)                                        ((0x00FFFFFF&(data))>>0)


#define DBG_START_0                                                                  0x9801A458
#define DBG_START_1                                                                  0x9801A45C
#define DBG_START_2                                                                  0x9801A460
#define DBG_START_3                                                                  0x9801A464
#define DBG_START_4                                                                  0x9801A468
#define DBG_START_5                                                                  0x9801A46C
#define DBG_START_6                                                                  0x9801A470
#define DBG_START_7                                                                  0x9801A474
#define DBG_START_0_reg_addr                                                         "0x9801A458"
#define DBG_START_1_reg_addr                                                         "0x9801A45C"
#define DBG_START_2_reg_addr                                                         "0x9801A460"
#define DBG_START_3_reg_addr                                                         "0x9801A464"
#define DBG_START_4_reg_addr                                                         "0x9801A468"
#define DBG_START_5_reg_addr                                                         "0x9801A46C"
#define DBG_START_6_reg_addr                                                         "0x9801A470"
#define DBG_START_7_reg_addr                                                         "0x9801A474"
#define DBG_START_0_reg                                                              0x9801A458
#define DBG_START_1_reg                                                              0x9801A45C
#define DBG_START_2_reg                                                              0x9801A460
#define DBG_START_3_reg                                                              0x9801A464
#define DBG_START_4_reg                                                              0x9801A468
#define DBG_START_5_reg                                                              0x9801A46C
#define DBG_START_6_reg                                                              0x9801A470
#define DBG_START_7_reg                                                              0x9801A474

#define set_DBG_START_0_reg(data)   (*((volatile unsigned int*) DBG_START_0_reg)=data)
#define set_DBG_START_1_reg(data)   (*((volatile unsigned int*) DBG_START_1_reg)=data)
#define set_DBG_START_2_reg(data)   (*((volatile unsigned int*) DBG_START_2_reg)=data)
#define set_DBG_START_3_reg(data)   (*((volatile unsigned int*) DBG_START_3_reg)=data)
#define set_DBG_START_4_reg(data)   (*((volatile unsigned int*) DBG_START_4_reg)=data)
#define set_DBG_START_5_reg(data)   (*((volatile unsigned int*) DBG_START_5_reg)=data)
#define set_DBG_START_6_reg(data)   (*((volatile unsigned int*) DBG_START_6_reg)=data)
#define set_DBG_START_7_reg(data)   (*((volatile unsigned int*) DBG_START_7_reg)=data)
#define get_DBG_START_0_reg   (*((volatile unsigned int*) DBG_START_0_reg))
#define get_DBG_START_1_reg   (*((volatile unsigned int*) DBG_START_1_reg))
#define get_DBG_START_2_reg   (*((volatile unsigned int*) DBG_START_2_reg))
#define get_DBG_START_3_reg   (*((volatile unsigned int*) DBG_START_3_reg))
#define get_DBG_START_4_reg   (*((volatile unsigned int*) DBG_START_4_reg))
#define get_DBG_START_5_reg   (*((volatile unsigned int*) DBG_START_5_reg))
#define get_DBG_START_6_reg   (*((volatile unsigned int*) DBG_START_6_reg))
#define get_DBG_START_7_reg   (*((volatile unsigned int*) DBG_START_7_reg))
#define DBG_START_0_inst_adr                                                         "0x0016"
#define DBG_START_1_inst_adr                                                         "0x0017"
#define DBG_START_2_inst_adr                                                         "0x0018"
#define DBG_START_3_inst_adr                                                         "0x0019"
#define DBG_START_4_inst_adr                                                         "0x001A"
#define DBG_START_5_inst_adr                                                         "0x001B"
#define DBG_START_6_inst_adr                                                         "0x001C"
#define DBG_START_7_inst_adr                                                         "0x001D"
#define DBG_START_0_inst                                                             0x0016
#define DBG_START_1_inst                                                             0x0017
#define DBG_START_2_inst                                                             0x0018
#define DBG_START_3_inst                                                             0x0019
#define DBG_START_4_inst                                                             0x001A
#define DBG_START_5_inst                                                             0x001B
#define DBG_START_6_inst                                                             0x001C
#define DBG_START_7_inst                                                             0x001D
#define DBG_START_Dbg_start_addr_shift                                               (0)
#define DBG_START_Dbg_start_addr_mask                                                (0xFFFFFFFF)
#define DBG_START_Dbg_start_addr(data)                                               (0xFFFFFFFF&((data)<<0))
#define DBG_START_Dbg_start_addr_src(data)                                           ((0xFFFFFFFF&(data))>>0)
#define DBG_START_get_Dbg_start_addr(data)                                           ((0xFFFFFFFF&(data))>>0)


#define DBG_END_0                                                                    0x9801A478
#define DBG_END_1                                                                    0x9801A47C
#define DBG_END_2                                                                    0x9801A480
#define DBG_END_3                                                                    0x9801A484
#define DBG_END_4                                                                    0x9801A488
#define DBG_END_5                                                                    0x9801A48C
#define DBG_END_6                                                                    0x9801A490
#define DBG_END_7                                                                    0x9801A494
#define DBG_END_0_reg_addr                                                           "0x9801A478"
#define DBG_END_1_reg_addr                                                           "0x9801A47C"
#define DBG_END_2_reg_addr                                                           "0x9801A480"
#define DBG_END_3_reg_addr                                                           "0x9801A484"
#define DBG_END_4_reg_addr                                                           "0x9801A488"
#define DBG_END_5_reg_addr                                                           "0x9801A48C"
#define DBG_END_6_reg_addr                                                           "0x9801A490"
#define DBG_END_7_reg_addr                                                           "0x9801A494"
#define DBG_END_0_reg                                                                0x9801A478
#define DBG_END_1_reg                                                                0x9801A47C
#define DBG_END_2_reg                                                                0x9801A480
#define DBG_END_3_reg                                                                0x9801A484
#define DBG_END_4_reg                                                                0x9801A488
#define DBG_END_5_reg                                                                0x9801A48C
#define DBG_END_6_reg                                                                0x9801A490
#define DBG_END_7_reg                                                                0x9801A494
#define set_DBG_END_0_reg(data)   (*((volatile unsigned int*) DBG_END_0_reg)=data)
#define set_DBG_END_1_reg(data)   (*((volatile unsigned int*) DBG_END_1_reg)=data)
#define set_DBG_END_2_reg(data)   (*((volatile unsigned int*) DBG_END_2_reg)=data)
#define set_DBG_END_3_reg(data)   (*((volatile unsigned int*) DBG_END_3_reg)=data)
#define set_DBG_END_4_reg(data)   (*((volatile unsigned int*) DBG_END_4_reg)=data)
#define set_DBG_END_5_reg(data)   (*((volatile unsigned int*) DBG_END_5_reg)=data)
#define set_DBG_END_6_reg(data)   (*((volatile unsigned int*) DBG_END_6_reg)=data)
#define set_DBG_END_7_reg(data)   (*((volatile unsigned int*) DBG_END_7_reg)=data)
#define get_DBG_END_0_reg   (*((volatile unsigned int*) DBG_END_0_reg))
#define get_DBG_END_1_reg   (*((volatile unsigned int*) DBG_END_1_reg))
#define get_DBG_END_2_reg   (*((volatile unsigned int*) DBG_END_2_reg))
#define get_DBG_END_3_reg   (*((volatile unsigned int*) DBG_END_3_reg))
#define get_DBG_END_4_reg   (*((volatile unsigned int*) DBG_END_4_reg))
#define get_DBG_END_5_reg   (*((volatile unsigned int*) DBG_END_5_reg))
#define get_DBG_END_6_reg   (*((volatile unsigned int*) DBG_END_6_reg))
#define get_DBG_END_7_reg   (*((volatile unsigned int*) DBG_END_7_reg))
#define DBG_END_0_inst_adr                                                           "0x001E"
#define DBG_END_1_inst_adr                                                           "0x001F"
#define DBG_END_2_inst_adr                                                           "0x0020"
#define DBG_END_3_inst_adr                                                           "0x0021"
#define DBG_END_4_inst_adr                                                           "0x0022"
#define DBG_END_5_inst_adr                                                           "0x0023"
#define DBG_END_6_inst_adr                                                           "0x0024"
#define DBG_END_7_inst_adr                                                           "0x0025"
#define DBG_END_0_inst                                                               0x001E
#define DBG_END_1_inst                                                               0x001F
#define DBG_END_2_inst                                                               0x0020
#define DBG_END_3_inst                                                               0x0021
#define DBG_END_4_inst                                                               0x0022
#define DBG_END_5_inst                                                               0x0023
#define DBG_END_6_inst                                                               0x0024
#define DBG_END_7_inst                                                               0x0025
#define DBG_END_Dbg_end_addr_shift                                                   (0)
#define DBG_END_Dbg_end_addr_mask                                                    (0xFFFFFFFF)
#define DBG_END_Dbg_end_addr(data)                                                   (0xFFFFFFFF&((data)<<0))
#define DBG_END_Dbg_end_addr_src(data)                                               ((0xFFFFFFFF&(data))>>0)
#define DBG_END_get_Dbg_end_addr(data)                                               ((0xFFFFFFFF&(data))>>0)


#define DBG_CTRL_0                                                                   0x9801A498
#define DBG_CTRL_1                                                                   0x9801A49C
#define DBG_CTRL_2                                                                   0x9801A4A0
#define DBG_CTRL_3                                                                   0x9801A4A4
#define DBG_CTRL_4                                                                   0x9801A4A8
#define DBG_CTRL_5                                                                   0x9801A4AC
#define DBG_CTRL_6                                                                   0x9801A4B0
#define DBG_CTRL_7                                                                   0x9801A4B4
#define DBG_CTRL_0_reg_addr                                                          "0x9801A498"
#define DBG_CTRL_1_reg_addr                                                          "0x9801A49C"
#define DBG_CTRL_2_reg_addr                                                          "0x9801A4A0"
#define DBG_CTRL_3_reg_addr                                                          "0x9801A4A4"
#define DBG_CTRL_4_reg_addr                                                          "0x9801A4A8"
#define DBG_CTRL_5_reg_addr                                                          "0x9801A4AC"
#define DBG_CTRL_6_reg_addr                                                          "0x9801A4B0"
#define DBG_CTRL_7_reg_addr                                                          "0x9801A4B4"
#define DBG_CTRL_0_reg                                                               0x9801A498
#define DBG_CTRL_1_reg                                                               0x9801A49C
#define DBG_CTRL_2_reg                                                               0x9801A4A0
#define DBG_CTRL_3_reg                                                               0x9801A4A4
#define DBG_CTRL_4_reg                                                               0x9801A4A8
#define DBG_CTRL_5_reg                                                               0x9801A4AC
#define DBG_CTRL_6_reg                                                               0x9801A4B0
#define DBG_CTRL_7_reg                                                               0x9801A4B4
#define set_DBG_CTRL_0_reg(data)   (*((volatile unsigned int*) DBG_CTRL_0_reg)=data)
#define set_DBG_CTRL_1_reg(data)   (*((volatile unsigned int*) DBG_CTRL_1_reg)=data)
#define set_DBG_CTRL_2_reg(data)   (*((volatile unsigned int*) DBG_CTRL_2_reg)=data)
#define set_DBG_CTRL_3_reg(data)   (*((volatile unsigned int*) DBG_CTRL_3_reg)=data)
#define set_DBG_CTRL_4_reg(data)   (*((volatile unsigned int*) DBG_CTRL_4_reg)=data)
#define set_DBG_CTRL_5_reg(data)   (*((volatile unsigned int*) DBG_CTRL_5_reg)=data)
#define set_DBG_CTRL_6_reg(data)   (*((volatile unsigned int*) DBG_CTRL_6_reg)=data)
#define set_DBG_CTRL_7_reg(data)   (*((volatile unsigned int*) DBG_CTRL_7_reg)=data)
#define get_DBG_CTRL_0_reg   (*((volatile unsigned int*) DBG_CTRL_0_reg))
#define get_DBG_CTRL_1_reg   (*((volatile unsigned int*) DBG_CTRL_1_reg))
#define get_DBG_CTRL_2_reg   (*((volatile unsigned int*) DBG_CTRL_2_reg))
#define get_DBG_CTRL_3_reg   (*((volatile unsigned int*) DBG_CTRL_3_reg))
#define get_DBG_CTRL_4_reg   (*((volatile unsigned int*) DBG_CTRL_4_reg))
#define get_DBG_CTRL_5_reg   (*((volatile unsigned int*) DBG_CTRL_5_reg))
#define get_DBG_CTRL_6_reg   (*((volatile unsigned int*) DBG_CTRL_6_reg))
#define get_DBG_CTRL_7_reg   (*((volatile unsigned int*) DBG_CTRL_7_reg))
#define DBG_CTRL_0_inst_adr                                                          "0x0026"
#define DBG_CTRL_1_inst_adr                                                          "0x0027"
#define DBG_CTRL_2_inst_adr                                                          "0x0028"
#define DBG_CTRL_3_inst_adr                                                          "0x0029"
#define DBG_CTRL_4_inst_adr                                                          "0x002A"
#define DBG_CTRL_5_inst_adr                                                          "0x002B"
#define DBG_CTRL_6_inst_adr                                                          "0x002C"
#define DBG_CTRL_7_inst_adr                                                          "0x002D"
#define DBG_CTRL_0_inst                                                              0x0026
#define DBG_CTRL_1_inst                                                              0x0027
#define DBG_CTRL_2_inst                                                              0x0028
#define DBG_CTRL_3_inst                                                              0x0029
#define DBG_CTRL_4_inst                                                              0x002A
#define DBG_CTRL_5_inst                                                              0x002B
#define DBG_CTRL_6_inst                                                              0x002C
#define DBG_CTRL_7_inst                                                              0x002D
#define DBG_CTRL_write_en6_shift                                                     (13)
#define DBG_CTRL_write_en6_mask                                                      (0x00002000)
#define DBG_CTRL_write_en6(data)                                                     (0x00002000&((data)<<13))
#define DBG_CTRL_write_en6_src(data)                                                 ((0x00002000&(data))>>13)
#define DBG_CTRL_get_write_en6(data)                                                 ((0x00002000&(data))>>13)
#define DBG_CTRL_Dbg_acpu_chk_en_shift                                               (12)
#define DBG_CTRL_Dbg_acpu_chk_en_mask                                                (0x00001000)
#define DBG_CTRL_Dbg_acpu_chk_en(data)                                               (0x00001000&((data)<<12))
#define DBG_CTRL_Dbg_acpu_chk_en_src(data)                                           ((0x00001000&(data))>>12)
#define DBG_CTRL_get_Dbg_acpu_chk_en(data)                                           ((0x00001000&(data))>>12)
#define DBG_CTRL_write_en4_shift                                                     (9)
#define DBG_CTRL_write_en4_mask                                                      (0x00000200)
#define DBG_CTRL_write_en4(data)                                                     (0x00000200&((data)<<9))
#define DBG_CTRL_write_en4_src(data)                                                 ((0x00000200&(data))>>9)
#define DBG_CTRL_get_write_en4(data)                                                 ((0x00000200&(data))>>9)
#define DBG_CTRL_Dbg_scpu_chk_en_shift                                               (8)
#define DBG_CTRL_Dbg_scpu_chk_en_mask                                                (0x00000100)
#define DBG_CTRL_Dbg_scpu_chk_en(data)                                               (0x00000100&((data)<<8))
#define DBG_CTRL_Dbg_scpu_chk_en_src(data)                                           ((0x00000100&(data))>>8)
#define DBG_CTRL_get_Dbg_scpu_chk_en(data)                                           ((0x00000100&(data))>>8)
#define DBG_CTRL_write_en3_shift                                                     (7)
#define DBG_CTRL_write_en3_mask                                                      (0x00000080)
#define DBG_CTRL_write_en3(data)                                                     (0x00000080&((data)<<7))
#define DBG_CTRL_write_en3_src(data)                                                 ((0x00000080&(data))>>7)
#define DBG_CTRL_get_write_en3(data)                                                 ((0x00000080&(data))>>7)
#define DBG_CTRL_Dbg_wr_chk_shift                                                    (5)
#define DBG_CTRL_Dbg_wr_chk_mask                                                     (0x00000060)
#define DBG_CTRL_Dbg_wr_chk(data)                                                    (0x00000060&((data)<<5))
#define DBG_CTRL_Dbg_wr_chk_src(data)                                                ((0x00000060&(data))>>5)
#define DBG_CTRL_get_Dbg_wr_chk(data)                                                ((0x00000060&(data))>>5)
#define DBG_CTRL_write_en2_shift                                                     (4)
#define DBG_CTRL_write_en2_mask                                                      (0x00000010)
#define DBG_CTRL_write_en2(data)                                                     (0x00000010&((data)<<4))
#define DBG_CTRL_write_en2_src(data)                                                 ((0x00000010&(data))>>4)
#define DBG_CTRL_get_write_en2(data)                                                 ((0x00000010&(data))>>4)
#define DBG_CTRL_Dbg_id_chk_shift                                                    (2)
#define DBG_CTRL_Dbg_id_chk_mask                                                     (0x0000000C)
#define DBG_CTRL_Dbg_id_chk(data)                                                    (0x0000000C&((data)<<2))
#define DBG_CTRL_Dbg_id_chk_src(data)                                                ((0x0000000C&(data))>>2)
#define DBG_CTRL_get_Dbg_id_chk(data)                                                ((0x0000000C&(data))>>2)
#define DBG_CTRL_write_en1_shift                                                     (1)
#define DBG_CTRL_write_en1_mask                                                      (0x00000002)
#define DBG_CTRL_write_en1(data)                                                     (0x00000002&((data)<<1))
#define DBG_CTRL_write_en1_src(data)                                                 ((0x00000002&(data))>>1)
#define DBG_CTRL_get_write_en1(data)                                                 ((0x00000002&(data))>>1)
#define DBG_CTRL_Dbg_en_shift                                                        (0)
#define DBG_CTRL_Dbg_en_mask                                                         (0x00000001)
#define DBG_CTRL_Dbg_en(data)                                                        (0x00000001&((data)<<0))
#define DBG_CTRL_Dbg_en_src(data)                                                    ((0x00000001&(data))>>0)
#define DBG_CTRL_get_Dbg_en(data)                                                    ((0x00000001&(data))>>0)


#define DBG_ADDR_0                                                                   0x9801A4B8
#define DBG_ADDR_1                                                                   0x9801A4BC
#define DBG_ADDR_2                                                                   0x9801A4C0
#define DBG_ADDR_0_reg_addr                                                          "0x9801A4B8"
#define DBG_ADDR_1_reg_addr                                                          "0x9801A4BC"
#define DBG_ADDR_2_reg_addr                                                          "0x9801A4C0"
#define DBG_ADDR_0_reg                                                               0x9801A4B8
#define DBG_ADDR_1_reg                                                               0x9801A4BC
#define DBG_ADDR_2_reg                                                               0x9801A4C0
#define set_DBG_ADDR_0_reg(data)   (*((volatile unsigned int*) DBG_ADDR_0_reg)=data)
#define set_DBG_ADDR_1_reg(data)   (*((volatile unsigned int*) DBG_ADDR_1_reg)=data)
#define set_DBG_ADDR_2_reg(data)   (*((volatile unsigned int*) DBG_ADDR_2_reg)=data)
#define get_DBG_ADDR_0_reg   (*((volatile unsigned int*) DBG_ADDR_0_reg))
#define get_DBG_ADDR_1_reg   (*((volatile unsigned int*) DBG_ADDR_1_reg))
#define get_DBG_ADDR_2_reg   (*((volatile unsigned int*) DBG_ADDR_2_reg))
#define DBG_ADDR_0_inst_adr                                                          "0x002E"
#define DBG_ADDR_1_inst_adr                                                          "0x002F"
#define DBG_ADDR_2_inst_adr                                                          "0x0030"
#define DBG_ADDR_0_inst                                                              0x002E
#define DBG_ADDR_1_inst                                                              0x002F
#define DBG_ADDR_2_inst                                                              0x0030
#define DBG_ADDR_dbg_addr_shift                                                      (0)
#define DBG_ADDR_dbg_addr_mask                                                       (0xFFFFFFFF)
#define DBG_ADDR_dbg_addr(data)                                                      (0xFFFFFFFF&((data)<<0))
#define DBG_ADDR_dbg_addr_src(data)                                                  ((0xFFFFFFFF&(data))>>0)
#define DBG_ADDR_get_dbg_addr(data)                                                  ((0xFFFFFFFF&(data))>>0)


#define DBG_ADDR1                                                                    0x9801A4C8
#define DBG_ADDR1_reg_addr                                                           "0x9801A4C8"
#define DBG_ADDR1_reg                                                                0x9801A4C8
#define set_DBG_ADDR1_reg(data)   (*((volatile unsigned int*) DBG_ADDR1_reg)=data)
#define get_DBG_ADDR1_reg   (*((volatile unsigned int*) DBG_ADDR1_reg))
#define DBG_ADDR1_inst_adr                                                           "0x0032"
#define DBG_ADDR1_inst                                                               0x0032
#define DBG_ADDR1_acpu_dbg_write_shift                                               (5)
#define DBG_ADDR1_acpu_dbg_write_mask                                                (0x00000020)
#define DBG_ADDR1_acpu_dbg_write(data)                                               (0x00000020&((data)<<5))
#define DBG_ADDR1_acpu_dbg_write_src(data)                                           ((0x00000020&(data))>>5)
#define DBG_ADDR1_get_acpu_dbg_write(data)                                           ((0x00000020&(data))>>5)
#define DBG_ADDR1_acpu_dbg_dacc_shift                                                (4)
#define DBG_ADDR1_acpu_dbg_dacc_mask                                                 (0x00000010)
#define DBG_ADDR1_acpu_dbg_dacc(data)                                                (0x00000010&((data)<<4))
#define DBG_ADDR1_acpu_dbg_dacc_src(data)                                            ((0x00000010&(data))>>4)
#define DBG_ADDR1_get_acpu_dbg_dacc(data)                                            ((0x00000010&(data))>>4)
#define DBG_ADDR1_scpu_dbg_write_shift                                               (3)
#define DBG_ADDR1_scpu_dbg_write_mask                                                (0x00000008)
#define DBG_ADDR1_scpu_dbg_write(data)                                               (0x00000008&((data)<<3))
#define DBG_ADDR1_scpu_dbg_write_src(data)                                           ((0x00000008&(data))>>3)
#define DBG_ADDR1_get_scpu_dbg_write(data)                                           ((0x00000008&(data))>>3)
#define DBG_ADDR1_scpu_dbg_dacc_shift                                                (2)
#define DBG_ADDR1_scpu_dbg_dacc_mask                                                 (0x00000004)
#define DBG_ADDR1_scpu_dbg_dacc(data)                                                (0x00000004&((data)<<2))
#define DBG_ADDR1_scpu_dbg_dacc_src(data)                                            ((0x00000004&(data))>>2)
#define DBG_ADDR1_get_scpu_dbg_dacc(data)                                            ((0x00000004&(data))>>2)


#define DBG_INT                                                                      0x9801A4E0
#define DBG_INT_reg_addr                                                             "0x9801A4E0"
#define DBG_INT_reg                                                                  0x9801A4E0
#define set_DBG_INT_reg(data)   (*((volatile unsigned int*) DBG_INT_reg)=data)
#define get_DBG_INT_reg   (*((volatile unsigned int*) DBG_INT_reg))
#define DBG_INT_inst_adr                                                             "0x0038"
#define DBG_INT_inst                                                                 0x0038
#define DBG_INT_acpu_int_shift                                                       (12)
#define DBG_INT_acpu_int_mask                                                        (0x00001000)
#define DBG_INT_acpu_int(data)                                                       (0x00001000&((data)<<12))
#define DBG_INT_acpu_int_src(data)                                                   ((0x00001000&(data))>>12)
#define DBG_INT_get_acpu_int(data)                                                   ((0x00001000&(data))>>12)
#define DBG_INT_scpu_int_shift                                                       (10)
#define DBG_INT_scpu_int_mask                                                        (0x00000400)
#define DBG_INT_scpu_int(data)                                                       (0x00000400&((data)<<10))
#define DBG_INT_scpu_int_src(data)                                                   ((0x00000400&(data))>>10)
#define DBG_INT_get_scpu_int(data)                                                   ((0x00000400&(data))>>10)
#define DBG_INT_acpu_int_en_shift                                                    (9)
#define DBG_INT_acpu_int_en_mask                                                     (0x00000200)
#define DBG_INT_acpu_int_en(data)                                                    (0x00000200&((data)<<9))
#define DBG_INT_acpu_int_en_src(data)                                                ((0x00000200&(data))>>9)
#define DBG_INT_get_acpu_int_en(data)                                                ((0x00000200&(data))>>9)
#define DBG_INT_scpu_int_en_shift                                                    (7)
#define DBG_INT_scpu_int_en_mask                                                     (0x00000080)
#define DBG_INT_scpu_int_en(data)                                                    (0x00000080&((data)<<7))
#define DBG_INT_scpu_int_en_src(data)                                                ((0x00000080&(data))>>7)
#define DBG_INT_get_scpu_int_en(data)                                                ((0x00000080&(data))>>7)
#define DBG_INT_acpu_neg_int_shift                                                   (6)
#define DBG_INT_acpu_neg_int_mask                                                    (0x00000040)
#define DBG_INT_acpu_neg_int(data)                                                   (0x00000040&((data)<<6))
#define DBG_INT_acpu_neg_int_src(data)                                               ((0x00000040&(data))>>6)
#define DBG_INT_get_acpu_neg_int(data)                                               ((0x00000040&(data))>>6)
#define DBG_INT_scpu_neg_int_shift                                                   (4)
#define DBG_INT_scpu_neg_int_mask                                                    (0x00000010)
#define DBG_INT_scpu_neg_int(data)                                                   (0x00000010&((data)<<4))
#define DBG_INT_scpu_neg_int_src(data)                                               ((0x00000010&(data))>>4)
#define DBG_INT_get_scpu_neg_int(data)                                               ((0x00000010&(data))>>4)
#define DBG_INT_acpu_neg_int_en_shift                                                (3)
#define DBG_INT_acpu_neg_int_en_mask                                                 (0x00000008)
#define DBG_INT_acpu_neg_int_en(data)                                                (0x00000008&((data)<<3))
#define DBG_INT_acpu_neg_int_en_src(data)                                            ((0x00000008&(data))>>3)
#define DBG_INT_get_acpu_neg_int_en(data)                                            ((0x00000008&(data))>>3)
#define DBG_INT_scpu_neg_int_en_shift                                                (1)
#define DBG_INT_scpu_neg_int_en_mask                                                 (0x00000002)
#define DBG_INT_scpu_neg_int_en(data)                                                (0x00000002&((data)<<1))
#define DBG_INT_scpu_neg_int_en_src(data)                                            ((0x00000002&(data))>>1)
#define DBG_INT_get_scpu_neg_int_en(data)                                            ((0x00000002&(data))>>1)
#define DBG_INT_write_data_shift                                                     (0)
#define DBG_INT_write_data_mask                                                      (0x00000001)
#define DBG_INT_write_data(data)                                                     (0x00000001&((data)<<0))
#define DBG_INT_write_data_src(data)                                                 ((0x00000001&(data))>>0)
#define DBG_INT_get_write_data(data)                                                 ((0x00000001&(data))>>0)


#define DUMMY_0                                                                      0x9801A600
#define DUMMY_1                                                                      0x9801A604
#define DUMMY_2                                                                      0x9801A608
#define DUMMY_3                                                                      0x9801A60C
#define DUMMY_0_reg_addr                                                             "0x9801A600"
#define DUMMY_1_reg_addr                                                             "0x9801A604"
#define DUMMY_2_reg_addr                                                             "0x9801A608"
#define DUMMY_3_reg_addr                                                             "0x9801A60C"
#define DUMMY_0_reg                                                                  0x9801A600
#define DUMMY_1_reg                                                                  0x9801A604
#define DUMMY_2_reg                                                                  0x9801A608
#define DUMMY_3_reg                                                                  0x9801A60C
#define set_DUMMY_0_reg(data)   (*((volatile unsigned int*) DUMMY_0_reg)=data)
#define set_DUMMY_1_reg(data)   (*((volatile unsigned int*) DUMMY_1_reg)=data)
#define set_DUMMY_2_reg(data)   (*((volatile unsigned int*) DUMMY_2_reg)=data)
#define set_DUMMY_3_reg(data)   (*((volatile unsigned int*) DUMMY_3_reg)=data)
#define get_DUMMY_0_reg   (*((volatile unsigned int*) DUMMY_0_reg))
#define get_DUMMY_1_reg   (*((volatile unsigned int*) DUMMY_1_reg))
#define get_DUMMY_2_reg   (*((volatile unsigned int*) DUMMY_2_reg))
#define get_DUMMY_3_reg   (*((volatile unsigned int*) DUMMY_3_reg))
#define DUMMY_0_inst_adr                                                             "0x0080"
#define DUMMY_1_inst_adr                                                             "0x0081"
#define DUMMY_2_inst_adr                                                             "0x0082"
#define DUMMY_3_inst_adr                                                             "0x0083"
#define DUMMY_0_inst                                                                 0x0080
#define DUMMY_1_inst                                                                 0x0081
#define DUMMY_2_inst                                                                 0x0082
#define DUMMY_3_inst                                                                 0x0083
#define DUMMY_data_shift                                                             (0)
#define DUMMY_data_mask                                                              (0xFFFFFFFF)
#define DUMMY_data(data)                                                             (0xFFFFFFFF&((data)<<0))
#define DUMMY_data_src(data)                                                         ((0xFFFFFFFF&(data))>>0)
#define DUMMY_get_data(data)                                                         ((0xFFFFFFFF&(data))>>0)


#define SHADOW_0                                                                     0x9801A610
#define SHADOW_1                                                                     0x9801A614
#define SHADOW_2                                                                     0x9801A618
#define SHADOW_3                                                                     0x9801A61C
#define SHADOW_0_reg_addr                                                            "0x9801A610"
#define SHADOW_1_reg_addr                                                            "0x9801A614"
#define SHADOW_2_reg_addr                                                            "0x9801A618"
#define SHADOW_3_reg_addr                                                            "0x9801A61C"
#define SHADOW_0_reg                                                                 0x9801A610
#define SHADOW_1_reg                                                                 0x9801A614
#define SHADOW_2_reg                                                                 0x9801A618
#define SHADOW_3_reg                                                                 0x9801A61C
#define set_SHADOW_0_reg(data)   (*((volatile unsigned int*) SHADOW_0_reg)=data)
#define set_SHADOW_1_reg(data)   (*((volatile unsigned int*) SHADOW_1_reg)=data)
#define set_SHADOW_2_reg(data)   (*((volatile unsigned int*) SHADOW_2_reg)=data)
#define set_SHADOW_3_reg(data)   (*((volatile unsigned int*) SHADOW_3_reg)=data)
#define get_SHADOW_0_reg   (*((volatile unsigned int*) SHADOW_0_reg))
#define get_SHADOW_1_reg   (*((volatile unsigned int*) SHADOW_1_reg))
#define get_SHADOW_2_reg   (*((volatile unsigned int*) SHADOW_2_reg))
#define get_SHADOW_3_reg   (*((volatile unsigned int*) SHADOW_3_reg))
#define SHADOW_0_inst_adr                                                            "0x0084"
#define SHADOW_1_inst_adr                                                            "0x0085"
#define SHADOW_2_inst_adr                                                            "0x0086"
#define SHADOW_3_inst_adr                                                            "0x0087"
#define SHADOW_0_inst                                                                0x0084
#define SHADOW_1_inst                                                                0x0085
#define SHADOW_2_inst                                                                0x0086
#define SHADOW_3_inst                                                                0x0087
#define SHADOW_data_shift                                                            (0)
#define SHADOW_data_mask                                                             (0xFFFFFFFF)
#define SHADOW_data(data)                                                            (0xFFFFFFFF&((data)<<0))
#define SHADOW_data_src(data)                                                        ((0xFFFFFFFF&(data))>>0)
#define SHADOW_get_data(data)                                                        ((0xFFFFFFFF&(data))>>0)


#define HD_SEM_NEW_0                                                                 0x9801A620
#define HD_SEM_NEW_1                                                                 0x9801A624
#define HD_SEM_NEW_2                                                                 0x9801A628
#define HD_SEM_NEW_3                                                                 0x9801A62C
#define HD_SEM_NEW_4                                                                 0x9801A630
#define HD_SEM_NEW_5                                                                 0x9801A634
#define HD_SEM_NEW_6                                                                 0x9801A638
#define HD_SEM_NEW_7                                                                 0x9801A63C
#define HD_SEM_NEW_0_reg_addr                                                        "0x9801A620"
#define HD_SEM_NEW_1_reg_addr                                                        "0x9801A624"
#define HD_SEM_NEW_2_reg_addr                                                        "0x9801A628"
#define HD_SEM_NEW_3_reg_addr                                                        "0x9801A62C"
#define HD_SEM_NEW_4_reg_addr                                                        "0x9801A630"
#define HD_SEM_NEW_5_reg_addr                                                        "0x9801A634"
#define HD_SEM_NEW_6_reg_addr                                                        "0x9801A638"
#define HD_SEM_NEW_7_reg_addr                                                        "0x9801A63C"
#define HD_SEM_NEW_0_reg                                                             0x9801A620
#define HD_SEM_NEW_1_reg                                                             0x9801A624
#define HD_SEM_NEW_2_reg                                                             0x9801A628
#define HD_SEM_NEW_3_reg                                                             0x9801A62C
#define HD_SEM_NEW_4_reg                                                             0x9801A630
#define HD_SEM_NEW_5_reg                                                             0x9801A634
#define HD_SEM_NEW_6_reg                                                             0x9801A638
#define HD_SEM_NEW_7_reg                                                             0x9801A63C
#define set_HD_SEM_NEW_0_reg(data)   (*((volatile unsigned int*) HD_SEM_NEW_0_reg)=data)
#define set_HD_SEM_NEW_1_reg(data)   (*((volatile unsigned int*) HD_SEM_NEW_1_reg)=data)
#define set_HD_SEM_NEW_2_reg(data)   (*((volatile unsigned int*) HD_SEM_NEW_2_reg)=data)
#define set_HD_SEM_NEW_3_reg(data)   (*((volatile unsigned int*) HD_SEM_NEW_3_reg)=data)
#define set_HD_SEM_NEW_4_reg(data)   (*((volatile unsigned int*) HD_SEM_NEW_4_reg)=data)
#define set_HD_SEM_NEW_5_reg(data)   (*((volatile unsigned int*) HD_SEM_NEW_5_reg)=data)
#define set_HD_SEM_NEW_6_reg(data)   (*((volatile unsigned int*) HD_SEM_NEW_6_reg)=data)
#define set_HD_SEM_NEW_7_reg(data)   (*((volatile unsigned int*) HD_SEM_NEW_7_reg)=data)
#define get_HD_SEM_NEW_0_reg   (*((volatile unsigned int*) HD_SEM_NEW_0_reg))
#define get_HD_SEM_NEW_1_reg   (*((volatile unsigned int*) HD_SEM_NEW_1_reg))
#define get_HD_SEM_NEW_2_reg   (*((volatile unsigned int*) HD_SEM_NEW_2_reg))
#define get_HD_SEM_NEW_3_reg   (*((volatile unsigned int*) HD_SEM_NEW_3_reg))
#define get_HD_SEM_NEW_4_reg   (*((volatile unsigned int*) HD_SEM_NEW_4_reg))
#define get_HD_SEM_NEW_5_reg   (*((volatile unsigned int*) HD_SEM_NEW_5_reg))
#define get_HD_SEM_NEW_6_reg   (*((volatile unsigned int*) HD_SEM_NEW_6_reg))
#define get_HD_SEM_NEW_7_reg   (*((volatile unsigned int*) HD_SEM_NEW_7_reg))
#define HD_SEM_NEW_0_inst_adr                                                        "0x0088"
#define HD_SEM_NEW_1_inst_adr                                                        "0x0089"
#define HD_SEM_NEW_2_inst_adr                                                        "0x008A"
#define HD_SEM_NEW_3_inst_adr                                                        "0x008B"
#define HD_SEM_NEW_4_inst_adr                                                        "0x008C"
#define HD_SEM_NEW_5_inst_adr                                                        "0x008D"
#define HD_SEM_NEW_6_inst_adr                                                        "0x008E"
#define HD_SEM_NEW_7_inst_adr                                                        "0x008F"
#define HD_SEM_NEW_0_inst                                                            0x0088
#define HD_SEM_NEW_1_inst                                                            0x0089
#define HD_SEM_NEW_2_inst                                                            0x008A
#define HD_SEM_NEW_3_inst                                                            0x008B
#define HD_SEM_NEW_4_inst                                                            0x008C
#define HD_SEM_NEW_5_inst                                                            0x008D
#define HD_SEM_NEW_6_inst                                                            0x008E
#define HD_SEM_NEW_7_inst                                                            0x008F
#define HD_SEM_NEW_Semaphore_shift                                                   (0)
#define HD_SEM_NEW_Semaphore_mask                                                    (0x00000001)
#define HD_SEM_NEW_Semaphore(data)                                                   (0x00000001&((data)<<0))
#define HD_SEM_NEW_Semaphore_src(data)                                               ((0x00000001&(data))>>0)
#define HD_SEM_NEW_get_Semaphore(data)                                               ((0x00000001&(data))>>0)


#define RBUS_INVA_ACC_CTRL                                                           0x9801A650
#define RBUS_INVA_ACC_CTRL_reg_addr                                                  "0x9801A650"
#define RBUS_INVA_ACC_CTRL_reg                                                       0x9801A650
#define set_RBUS_INVA_ACC_CTRL_reg(data)   (*((volatile unsigned int*) RBUS_INVA_ACC_CTRL_reg)=data)
#define get_RBUS_INVA_ACC_CTRL_reg   (*((volatile unsigned int*) RBUS_INVA_ACC_CTRL_reg))
#define RBUS_INVA_ACC_CTRL_inst_adr                                                  "0x0094"
#define RBUS_INVA_ACC_CTRL_inst                                                      0x0094
#define RBUS_INVA_ACC_CTRL_inva_wr_sec2_en_shift                                     (2)
#define RBUS_INVA_ACC_CTRL_inva_wr_sec2_en_mask                                      (0x00000004)
#define RBUS_INVA_ACC_CTRL_inva_wr_sec2_en(data)                                     (0x00000004&((data)<<2))
#define RBUS_INVA_ACC_CTRL_inva_wr_sec2_en_src(data)                                 ((0x00000004&(data))>>2)
#define RBUS_INVA_ACC_CTRL_get_inva_wr_sec2_en(data)                                 ((0x00000004&(data))>>2)
#define RBUS_INVA_ACC_CTRL_inva_wr_sec1_en_shift                                     (0)
#define RBUS_INVA_ACC_CTRL_inva_wr_sec1_en_mask                                      (0x00000001)
#define RBUS_INVA_ACC_CTRL_inva_wr_sec1_en(data)                                     (0x00000001&((data)<<0))
#define RBUS_INVA_ACC_CTRL_inva_wr_sec1_en_src(data)                                 ((0x00000001&(data))>>0)
#define RBUS_INVA_ACC_CTRL_get_inva_wr_sec1_en(data)                                 ((0x00000001&(data))>>0)


#define RBUS_INVA_ACC_SEC1_START                                                     0x9801A654
#define RBUS_INVA_ACC_SEC1_START_reg_addr                                            "0x9801A654"
#define RBUS_INVA_ACC_SEC1_START_reg                                                 0x9801A654
#define set_RBUS_INVA_ACC_SEC1_START_reg(data)   (*((volatile unsigned int*) RBUS_INVA_ACC_SEC1_START_reg)=data)
#define get_RBUS_INVA_ACC_SEC1_START_reg   (*((volatile unsigned int*) RBUS_INVA_ACC_SEC1_START_reg))
#define RBUS_INVA_ACC_SEC1_START_inst_adr                                            "0x0095"
#define RBUS_INVA_ACC_SEC1_START_inst                                                0x0095
#define RBUS_INVA_ACC_SEC1_START_sec1_start_shift                                    (2)
#define RBUS_INVA_ACC_SEC1_START_sec1_start_mask                                     (0x0007FFFC)
#define RBUS_INVA_ACC_SEC1_START_sec1_start(data)                                    (0x0007FFFC&((data)<<2))
#define RBUS_INVA_ACC_SEC1_START_sec1_start_src(data)                                ((0x0007FFFC&(data))>>2)
#define RBUS_INVA_ACC_SEC1_START_get_sec1_start(data)                                ((0x0007FFFC&(data))>>2)


#define RBUS_INVA_ACC_SEC1_END                                                       0x9801A658
#define RBUS_INVA_ACC_SEC1_END_reg_addr                                              "0x9801A658"
#define RBUS_INVA_ACC_SEC1_END_reg                                                   0x9801A658
#define set_RBUS_INVA_ACC_SEC1_END_reg(data)   (*((volatile unsigned int*) RBUS_INVA_ACC_SEC1_END_reg)=data)
#define get_RBUS_INVA_ACC_SEC1_END_reg   (*((volatile unsigned int*) RBUS_INVA_ACC_SEC1_END_reg))
#define RBUS_INVA_ACC_SEC1_END_inst_adr                                              "0x0096"
#define RBUS_INVA_ACC_SEC1_END_inst                                                  0x0096
#define RBUS_INVA_ACC_SEC1_END_sec1_end_shift                                        (2)
#define RBUS_INVA_ACC_SEC1_END_sec1_end_mask                                         (0x0007FFFC)
#define RBUS_INVA_ACC_SEC1_END_sec1_end(data)                                        (0x0007FFFC&((data)<<2))
#define RBUS_INVA_ACC_SEC1_END_sec1_end_src(data)                                    ((0x0007FFFC&(data))>>2)
#define RBUS_INVA_ACC_SEC1_END_get_sec1_end(data)                                    ((0x0007FFFC&(data))>>2)


#define RBUS_INVA_ACC_SEC2_START                                                     0x9801A65C
#define RBUS_INVA_ACC_SEC2_START_reg_addr                                            "0x9801A65C"
#define RBUS_INVA_ACC_SEC2_START_reg                                                 0x9801A65C
#define set_RBUS_INVA_ACC_SEC2_START_reg(data)   (*((volatile unsigned int*) RBUS_INVA_ACC_SEC2_START_reg)=data)
#define get_RBUS_INVA_ACC_SEC2_START_reg   (*((volatile unsigned int*) RBUS_INVA_ACC_SEC2_START_reg))
#define RBUS_INVA_ACC_SEC2_START_inst_adr                                            "0x0097"
#define RBUS_INVA_ACC_SEC2_START_inst                                                0x0097
#define RBUS_INVA_ACC_SEC2_START_sec2_start_shift                                    (2)
#define RBUS_INVA_ACC_SEC2_START_sec2_start_mask                                     (0x0007FFFC)
#define RBUS_INVA_ACC_SEC2_START_sec2_start(data)                                    (0x0007FFFC&((data)<<2))
#define RBUS_INVA_ACC_SEC2_START_sec2_start_src(data)                                ((0x0007FFFC&(data))>>2)
#define RBUS_INVA_ACC_SEC2_START_get_sec2_start(data)                                ((0x0007FFFC&(data))>>2)


#define RBUS_INVA_ACC_SEC2_END                                                       0x9801A660
#define RBUS_INVA_ACC_SEC2_END_reg_addr                                              "0x9801A660"
#define RBUS_INVA_ACC_SEC2_END_reg                                                   0x9801A660
#define set_RBUS_INVA_ACC_SEC2_END_reg(data)   (*((volatile unsigned int*) RBUS_INVA_ACC_SEC2_END_reg)=data)
#define get_RBUS_INVA_ACC_SEC2_END_reg   (*((volatile unsigned int*) RBUS_INVA_ACC_SEC2_END_reg))
#define RBUS_INVA_ACC_SEC2_END_inst_adr                                              "0x0098"
#define RBUS_INVA_ACC_SEC2_END_inst                                                  0x0098
#define RBUS_INVA_ACC_SEC2_END_sec2_end_shift                                        (2)
#define RBUS_INVA_ACC_SEC2_END_sec2_end_mask                                         (0x0007FFFC)
#define RBUS_INVA_ACC_SEC2_END_sec2_end(data)                                        (0x0007FFFC&((data)<<2))
#define RBUS_INVA_ACC_SEC2_END_sec2_end_src(data)                                    ((0x0007FFFC&(data))>>2)
#define RBUS_INVA_ACC_SEC2_END_get_sec2_end(data)                                    ((0x0007FFFC&(data))>>2)


#define RBUS_CMP_CTRL                                                                0x9801A664
#define RBUS_CMP_CTRL_reg_addr                                                       "0x9801A664"
#define RBUS_CMP_CTRL_reg                                                            0x9801A664
#define set_RBUS_CMP_CTRL_reg(data)   (*((volatile unsigned int*) RBUS_CMP_CTRL_reg)=data)
#define get_RBUS_CMP_CTRL_reg   (*((volatile unsigned int*) RBUS_CMP_CTRL_reg))
#define RBUS_CMP_CTRL_inst_adr                                                       "0x0099"
#define RBUS_CMP_CTRL_inst                                                           0x0099
#define RBUS_CMP_CTRL_crc_cmp_latch_en_shift                                         (0)
#define RBUS_CMP_CTRL_crc_cmp_latch_en_mask                                          (0x00000001)
#define RBUS_CMP_CTRL_crc_cmp_latch_en(data)                                         (0x00000001&((data)<<0))
#define RBUS_CMP_CTRL_crc_cmp_latch_en_src(data)                                     ((0x00000001&(data))>>0)
#define RBUS_CMP_CTRL_get_crc_cmp_latch_en(data)                                     ((0x00000001&(data))>>0)


#define RBUS_CMP_DATA                                                                0x9801A668
#define RBUS_CMP_DATA_reg_addr                                                       "0x9801A668"
#define RBUS_CMP_DATA_reg                                                            0x9801A668
#define set_RBUS_CMP_DATA_reg(data)   (*((volatile unsigned int*) RBUS_CMP_DATA_reg)=data)
#define get_RBUS_CMP_DATA_reg   (*((volatile unsigned int*) RBUS_CMP_DATA_reg))
#define RBUS_CMP_DATA_inst_adr                                                       "0x009A"
#define RBUS_CMP_DATA_inst                                                           0x009A
#define RBUS_CMP_DATA_crc_cmp_expect_shift                                           (0)
#define RBUS_CMP_DATA_crc_cmp_expect_mask                                            (0xFFFFFFFF)
#define RBUS_CMP_DATA_crc_cmp_expect(data)                                           (0xFFFFFFFF&((data)<<0))
#define RBUS_CMP_DATA_crc_cmp_expect_src(data)                                       ((0xFFFFFFFF&(data))>>0)
#define RBUS_CMP_DATA_get_crc_cmp_expect(data)                                       ((0xFFFFFFFF&(data))>>0)


#define RBUS_CMP_RESULT                                                              0x9801A66C
#define RBUS_CMP_RESULT_reg_addr                                                     "0x9801A66C"
#define RBUS_CMP_RESULT_reg                                                          0x9801A66C
#define set_RBUS_CMP_RESULT_reg(data)   (*((volatile unsigned int*) RBUS_CMP_RESULT_reg)=data)
#define get_RBUS_CMP_RESULT_reg   (*((volatile unsigned int*) RBUS_CMP_RESULT_reg))
#define RBUS_CMP_RESULT_inst_adr                                                     "0x009B"
#define RBUS_CMP_RESULT_inst                                                         0x009B
#define RBUS_CMP_RESULT_crc_cmp_result_shift                                         (0)
#define RBUS_CMP_RESULT_crc_cmp_result_mask                                          (0xFFFFFFFF)
#define RBUS_CMP_RESULT_crc_cmp_result(data)                                         (0xFFFFFFFF&((data)<<0))
#define RBUS_CMP_RESULT_crc_cmp_result_src(data)                                     ((0xFFFFFFFF&(data))>>0)
#define RBUS_CMP_RESULT_get_crc_cmp_result(data)                                     ((0xFFFFFFFF&(data))>>0)


#define BIST_CTRL                                                                    0x9801A674
#define BIST_CTRL_reg_addr                                                           "0x9801A674"
#define BIST_CTRL_reg                                                                0x9801A674
#define set_BIST_CTRL_reg(data)   (*((volatile unsigned int*) BIST_CTRL_reg)=data)
#define get_BIST_CTRL_reg   (*((volatile unsigned int*) BIST_CTRL_reg))
#define BIST_CTRL_inst_adr                                                           "0x009D"
#define BIST_CTRL_inst                                                               0x009D
#define BIST_CTRL_sb2_bist_rstn_shift                                                (7)
#define BIST_CTRL_sb2_bist_rstn_mask                                                 (0x00000080)
#define BIST_CTRL_sb2_bist_rstn(data)                                                (0x00000080&((data)<<7))
#define BIST_CTRL_sb2_bist_rstn_src(data)                                            ((0x00000080&(data))>>7)
#define BIST_CTRL_get_sb2_bist_rstn(data)                                            ((0x00000080&(data))>>7)
#define BIST_CTRL_sb2_bist_en_shift                                                  (6)
#define BIST_CTRL_sb2_bist_en_mask                                                   (0x00000040)
#define BIST_CTRL_sb2_bist_en(data)                                                  (0x00000040&((data)<<6))
#define BIST_CTRL_sb2_bist_en_src(data)                                              ((0x00000040&(data))>>6)
#define BIST_CTRL_get_sb2_bist_en(data)                                              ((0x00000040&(data))>>6)
#define BIST_CTRL_sb2_rom_ls_shift                                                   (5)
#define BIST_CTRL_sb2_rom_ls_mask                                                    (0x00000020)
#define BIST_CTRL_sb2_rom_ls(data)                                                   (0x00000020&((data)<<5))
#define BIST_CTRL_sb2_rom_ls_src(data)                                               ((0x00000020&(data))>>5)
#define BIST_CTRL_get_sb2_rom_ls(data)                                               ((0x00000020&(data))>>5)
#define BIST_CTRL_sb2_rom_rme_shift                                                  (4)
#define BIST_CTRL_sb2_rom_rme_mask                                                   (0x00000010)
#define BIST_CTRL_sb2_rom_rme(data)                                                  (0x00000010&((data)<<4))
#define BIST_CTRL_sb2_rom_rme_src(data)                                              ((0x00000010&(data))>>4)
#define BIST_CTRL_get_sb2_rom_rme(data)                                              ((0x00000010&(data))>>4)
#define BIST_CTRL_sb2_rom_rm_shift                                                   (0)
#define BIST_CTRL_sb2_rom_rm_mask                                                    (0x0000000F)
#define BIST_CTRL_sb2_rom_rm(data)                                                   (0x0000000F&((data)<<0))
#define BIST_CTRL_sb2_rom_rm_src(data)                                               ((0x0000000F&(data))>>0)
#define BIST_CTRL_get_sb2_rom_rm(data)                                               ((0x0000000F&(data))>>0)


#define BIST_STATUS                                                                  0x9801A678
#define BIST_STATUS_reg_addr                                                         "0x9801A678"
#define BIST_STATUS_reg                                                              0x9801A678
#define set_BIST_STATUS_reg(data)   (*((volatile unsigned int*) BIST_STATUS_reg)=data)
#define get_BIST_STATUS_reg   (*((volatile unsigned int*) BIST_STATUS_reg))
#define BIST_STATUS_inst_adr                                                         "0x009E"
#define BIST_STATUS_inst                                                             0x009E
#define BIST_STATUS_sb2_rom_bist_done_shift                                          (16)
#define BIST_STATUS_sb2_rom_bist_done_mask                                           (0x00010000)
#define BIST_STATUS_sb2_rom_bist_done(data)                                          (0x00010000&((data)<<16))
#define BIST_STATUS_sb2_rom_bist_done_src(data)                                      ((0x00010000&(data))>>16)
#define BIST_STATUS_get_sb2_rom_bist_done(data)                                      ((0x00010000&(data))>>16)
#define BIST_STATUS_sb2_misr_dataout_0_shift                                         (0)
#define BIST_STATUS_sb2_misr_dataout_0_mask                                          (0x0000FFFF)
#define BIST_STATUS_sb2_misr_dataout_0(data)                                         (0x0000FFFF&((data)<<0))
#define BIST_STATUS_sb2_misr_dataout_0_src(data)                                     ((0x0000FFFF&(data))>>0)
#define BIST_STATUS_get_sb2_misr_dataout_0(data)                                     ((0x0000FFFF&(data))>>0)


#define SFC_OPCODE                                                                   0x9801A800
#define SFC_OPCODE_reg_addr                                                          "0x9801A800"
#define SFC_OPCODE_reg                                                               0x9801A800
#define set_SFC_OPCODE_reg(data)   (*((volatile unsigned int*) SFC_OPCODE_reg)=data)
#define get_SFC_OPCODE_reg   (*((volatile unsigned int*) SFC_OPCODE_reg))
#define SFC_OPCODE_inst_adr                                                          "0x0000"
#define SFC_OPCODE_inst                                                              0x0000
#define SFC_OPCODE_dual_mode_shift                                                   (9)
#define SFC_OPCODE_dual_mode_mask                                                    (0x00000600)
#define SFC_OPCODE_dual_mode(data)                                                   (0x00000600&((data)<<9))
#define SFC_OPCODE_dual_mode_src(data)                                               ((0x00000600&(data))>>9)
#define SFC_OPCODE_get_dual_mode(data)                                               ((0x00000600&(data))>>9)
#define SFC_OPCODE_fat_mode_shift                                                    (8)
#define SFC_OPCODE_fat_mode_mask                                                     (0x00000100)
#define SFC_OPCODE_fat_mode(data)                                                    (0x00000100&((data)<<8))
#define SFC_OPCODE_fat_mode_src(data)                                                ((0x00000100&(data))>>8)
#define SFC_OPCODE_get_fat_mode(data)                                                ((0x00000100&(data))>>8)
#define SFC_OPCODE_opc_shift                                                         (0)
#define SFC_OPCODE_opc_mask                                                          (0x000000FF)
#define SFC_OPCODE_opc(data)                                                         (0x000000FF&((data)<<0))
#define SFC_OPCODE_opc_src(data)                                                     ((0x000000FF&(data))>>0)
#define SFC_OPCODE_get_opc(data)                                                     ((0x000000FF&(data))>>0)


#define SFC_CTL                                                                      0x9801A804
#define SFC_CTL_reg_addr                                                             "0x9801A804"
#define SFC_CTL_reg                                                                  0x9801A804
#define set_SFC_CTL_reg(data)   (*((volatile unsigned int*) SFC_CTL_reg)=data)
#define get_SFC_CTL_reg   (*((volatile unsigned int*) SFC_CTL_reg))
#define SFC_CTL_inst_adr                                                             "0x0001"
#define SFC_CTL_inst                                                                 0x0001
#define SFC_CTL_dataen_shift                                                         (4)
#define SFC_CTL_dataen_mask                                                          (0x00000010)
#define SFC_CTL_dataen(data)                                                         (0x00000010&((data)<<4))
#define SFC_CTL_dataen_src(data)                                                     ((0x00000010&(data))>>4)
#define SFC_CTL_get_dataen(data)                                                     ((0x00000010&(data))>>4)
#define SFC_CTL_adren_shift                                                          (3)
#define SFC_CTL_adren_mask                                                           (0x00000008)
#define SFC_CTL_adren(data)                                                          (0x00000008&((data)<<3))
#define SFC_CTL_adren_src(data)                                                      ((0x00000008&(data))>>3)
#define SFC_CTL_get_adren(data)                                                      ((0x00000008&(data))>>3)
#define SFC_CTL_dmycnt_shift                                                         (0)
#define SFC_CTL_dmycnt_mask                                                          (0x00000007)
#define SFC_CTL_dmycnt(data)                                                         (0x00000007&((data)<<0))
#define SFC_CTL_dmycnt_src(data)                                                     ((0x00000007&(data))>>0)
#define SFC_CTL_get_dmycnt(data)                                                     ((0x00000007&(data))>>0)


#define SFC_SCK                                                                      0x9801A808
#define SFC_SCK_reg_addr                                                             "0x9801A808"
#define SFC_SCK_reg                                                                  0x9801A808
#define set_SFC_SCK_reg(data)   (*((volatile unsigned int*) SFC_SCK_reg)=data)
#define get_SFC_SCK_reg   (*((volatile unsigned int*) SFC_SCK_reg))
#define SFC_SCK_inst_adr                                                             "0x0002"
#define SFC_SCK_inst                                                                 0x0002
#define SFC_SCK_mode_shift                                                           (8)
#define SFC_SCK_mode_mask                                                            (0x00000100)
#define SFC_SCK_mode(data)                                                           (0x00000100&((data)<<8))
#define SFC_SCK_mode_src(data)                                                       ((0x00000100&(data))>>8)
#define SFC_SCK_get_mode(data)                                                       ((0x00000100&(data))>>8)
#define SFC_SCK_fdiv_shift                                                           (0)
#define SFC_SCK_fdiv_mask                                                            (0x000000FF)
#define SFC_SCK_fdiv(data)                                                           (0x000000FF&((data)<<0))
#define SFC_SCK_fdiv_src(data)                                                       ((0x000000FF&(data))>>0)
#define SFC_SCK_get_fdiv(data)                                                       ((0x000000FF&(data))>>0)


#define SFC_CE                                                                       0x9801A80C
#define SFC_CE_reg_addr                                                              "0x9801A80C"
#define SFC_CE_reg                                                                   0x9801A80C
#define set_SFC_CE_reg(data)   (*((volatile unsigned int*) SFC_CE_reg)=data)
#define get_SFC_CE_reg   (*((volatile unsigned int*) SFC_CE_reg))
#define SFC_CE_inst_adr                                                              "0x0003"
#define SFC_CE_inst                                                                  0x0003
#define SFC_CE_tdt_shift                                                             (16)
#define SFC_CE_tdt_mask                                                              (0xFFFF0000)
#define SFC_CE_tdt(data)                                                             (0xFFFF0000&((data)<<16))
#define SFC_CE_tdt_src(data)                                                         ((0xFFFF0000&(data))>>16)
#define SFC_CE_get_tdt(data)                                                         ((0xFFFF0000&(data))>>16)
#define SFC_CE_Phcnt_shift                                                           (8)
#define SFC_CE_Phcnt_mask                                                            (0x0000FF00)
#define SFC_CE_Phcnt(data)                                                           (0x0000FF00&((data)<<8))
#define SFC_CE_Phcnt_src(data)                                                       ((0x0000FF00&(data))>>8)
#define SFC_CE_get_Phcnt(data)                                                       ((0x0000FF00&(data))>>8)
#define SFC_CE_Plcnt_shift                                                           (0)
#define SFC_CE_Plcnt_mask                                                            (0x000000FF)
#define SFC_CE_Plcnt(data)                                                           (0x000000FF&((data)<<0))
#define SFC_CE_Plcnt_src(data)                                                       ((0x000000FF&(data))>>0)
#define SFC_CE_get_Plcnt(data)                                                       ((0x000000FF&(data))>>0)


#define SFC_WP                                                                       0x9801A810
#define SFC_WP_reg_addr                                                              "0x9801A810"
#define SFC_WP_reg                                                                   0x9801A810
#define set_SFC_WP_reg(data)   (*((volatile unsigned int*) SFC_WP_reg)=data)
#define get_SFC_WP_reg   (*((volatile unsigned int*) SFC_WP_reg))
#define SFC_WP_inst_adr                                                              "0x0004"
#define SFC_WP_inst                                                                  0x0004
#define SFC_WP_write_en5_shift                                                       (27)
#define SFC_WP_write_en5_mask                                                        (0x08000000)
#define SFC_WP_write_en5(data)                                                       (0x08000000&((data)<<27))
#define SFC_WP_write_en5_src(data)                                                   ((0x08000000&(data))>>27)
#define SFC_WP_get_write_en5(data)                                                   ((0x08000000&(data))>>27)
#define SFC_WP_rdy_shift                                                             (26)
#define SFC_WP_rdy_mask                                                              (0x04000000)
#define SFC_WP_rdy(data)                                                             (0x04000000&((data)<<26))
#define SFC_WP_rdy_src(data)                                                         ((0x04000000&(data))>>26)
#define SFC_WP_get_rdy(data)                                                         ((0x04000000&(data))>>26)
#define SFC_WP_write_en1_shift                                                       (1)
#define SFC_WP_write_en1_mask                                                        (0x00000002)
#define SFC_WP_write_en1(data)                                                       (0x00000002&((data)<<1))
#define SFC_WP_write_en1_src(data)                                                   ((0x00000002&(data))>>1)
#define SFC_WP_get_write_en1(data)                                                   ((0x00000002&(data))>>1)
#define SFC_WP_wp_n_shift                                                            (0)
#define SFC_WP_wp_n_mask                                                             (0x00000001)
#define SFC_WP_wp_n(data)                                                            (0x00000001&((data)<<0))
#define SFC_WP_wp_n_src(data)                                                        ((0x00000001&(data))>>0)
#define SFC_WP_get_wp_n(data)                                                        ((0x00000001&(data))>>0)


#define SFC_POS_LATCH                                                                0x9801A814
#define SFC_POS_LATCH_reg_addr                                                       "0x9801A814"
#define SFC_POS_LATCH_reg                                                            0x9801A814
#define set_SFC_POS_LATCH_reg(data)   (*((volatile unsigned int*) SFC_POS_LATCH_reg)=data)
#define get_SFC_POS_LATCH_reg   (*((volatile unsigned int*) SFC_POS_LATCH_reg))
#define SFC_POS_LATCH_inst_adr                                                       "0x0005"
#define SFC_POS_LATCH_inst                                                           0x0005
#define SFC_POS_LATCH_pos_latch_shift                                                (0)
#define SFC_POS_LATCH_pos_latch_mask                                                 (0x00000001)
#define SFC_POS_LATCH_pos_latch(data)                                                (0x00000001&((data)<<0))
#define SFC_POS_LATCH_pos_latch_src(data)                                            ((0x00000001&(data))>>0)
#define SFC_POS_LATCH_get_pos_latch(data)                                            ((0x00000001&(data))>>0)


#define SFC_WAIT_WR                                                                  0x9801A818
#define SFC_WAIT_WR_reg_addr                                                         "0x9801A818"
#define SFC_WAIT_WR_reg                                                              0x9801A818
#define set_SFC_WAIT_WR_reg(data)   (*((volatile unsigned int*) SFC_WAIT_WR_reg)=data)
#define get_SFC_WAIT_WR_reg   (*((volatile unsigned int*) SFC_WAIT_WR_reg))
#define SFC_WAIT_WR_inst_adr                                                         "0x0006"
#define SFC_WAIT_WR_inst                                                             0x0006
#define SFC_WAIT_WR_wt_prog_done_shift                                               (8)
#define SFC_WAIT_WR_wt_prog_done_mask                                                (0x00000100)
#define SFC_WAIT_WR_wt_prog_done(data)                                               (0x00000100&((data)<<8))
#define SFC_WAIT_WR_wt_prog_done_src(data)                                           ((0x00000100&(data))>>8)
#define SFC_WAIT_WR_get_wt_prog_done(data)                                           ((0x00000100&(data))>>8)
#define SFC_WAIT_WR_rdsr_op_shift                                                    (0)
#define SFC_WAIT_WR_rdsr_op_mask                                                     (0x000000FF)
#define SFC_WAIT_WR_rdsr_op(data)                                                    (0x000000FF&((data)<<0))
#define SFC_WAIT_WR_rdsr_op_src(data)                                                ((0x000000FF&(data))>>0)
#define SFC_WAIT_WR_get_rdsr_op(data)                                                ((0x000000FF&(data))>>0)


#define SFC_EN_WR                                                                    0x9801A81C
#define SFC_EN_WR_reg_addr                                                           "0x9801A81C"
#define SFC_EN_WR_reg                                                                0x9801A81C
#define set_SFC_EN_WR_reg(data)   (*((volatile unsigned int*) SFC_EN_WR_reg)=data)
#define get_SFC_EN_WR_reg   (*((volatile unsigned int*) SFC_EN_WR_reg))
#define SFC_EN_WR_inst_adr                                                           "0x0007"
#define SFC_EN_WR_inst                                                               0x0007
#define SFC_EN_WR_wt_prog_en_shift                                                   (8)
#define SFC_EN_WR_wt_prog_en_mask                                                    (0x00000100)
#define SFC_EN_WR_wt_prog_en(data)                                                   (0x00000100&((data)<<8))
#define SFC_EN_WR_wt_prog_en_src(data)                                               ((0x00000100&(data))>>8)
#define SFC_EN_WR_get_wt_prog_en(data)                                               ((0x00000100&(data))>>8)
#define SFC_EN_WR_wr_en_op_shift                                                     (0)
#define SFC_EN_WR_wr_en_op_mask                                                      (0x000000FF)
#define SFC_EN_WR_wr_en_op(data)                                                     (0x000000FF&((data)<<0))
#define SFC_EN_WR_wr_en_op_src(data)                                                 ((0x000000FF&(data))>>0)
#define SFC_EN_WR_get_wr_en_op(data)                                                 ((0x000000FF&(data))>>0)


#define SFC_FAST_RD                                                                  0x9801A820
#define SFC_FAST_RD_reg_addr                                                         "0x9801A820"
#define SFC_FAST_RD_reg                                                              0x9801A820
#define set_SFC_FAST_RD_reg(data)   (*((volatile unsigned int*) SFC_FAST_RD_reg)=data)
#define get_SFC_FAST_RD_reg   (*((volatile unsigned int*) SFC_FAST_RD_reg))
#define SFC_FAST_RD_inst_adr                                                         "0x0008"
#define SFC_FAST_RD_inst                                                             0x0008
#define SFC_FAST_RD_sf_dclk_sel_shift                                                (4)
#define SFC_FAST_RD_sf_dclk_sel_mask                                                 (0x00000010)
#define SFC_FAST_RD_sf_dclk_sel(data)                                                (0x00000010&((data)<<4))
#define SFC_FAST_RD_sf_dclk_sel_src(data)                                            ((0x00000010&(data))>>4)
#define SFC_FAST_RD_get_sf_dclk_sel(data)                                            ((0x00000010&(data))>>4)
#define SFC_FAST_RD_fifo_write_tap_shift                                             (1)
#define SFC_FAST_RD_fifo_write_tap_mask                                              (0x0000000E)
#define SFC_FAST_RD_fifo_write_tap(data)                                             (0x0000000E&((data)<<1))
#define SFC_FAST_RD_fifo_write_tap_src(data)                                         ((0x0000000E&(data))>>1)
#define SFC_FAST_RD_get_fifo_write_tap(data)                                         ((0x0000000E&(data))>>1)
#define SFC_FAST_RD_fast_read_en_shift                                               (0)
#define SFC_FAST_RD_fast_read_en_mask                                                (0x00000001)
#define SFC_FAST_RD_fast_read_en(data)                                               (0x00000001&((data)<<0))
#define SFC_FAST_RD_fast_read_en_src(data)                                           ((0x00000001&(data))>>0)
#define SFC_FAST_RD_get_fast_read_en(data)                                           ((0x00000001&(data))>>0)


#define SFC_SCK_TAP                                                                  0x9801A824
#define SFC_SCK_TAP_reg_addr                                                         "0x9801A824"
#define SFC_SCK_TAP_reg                                                              0x9801A824
#define set_SFC_SCK_TAP_reg(data)   (*((volatile unsigned int*) SFC_SCK_TAP_reg)=data)
#define get_SFC_SCK_TAP_reg   (*((volatile unsigned int*) SFC_SCK_TAP_reg))
#define SFC_SCK_TAP_inst_adr                                                         "0x0009"
#define SFC_SCK_TAP_inst                                                             0x0009
#define SFC_SCK_TAP_delay_clk_tap_shift                                              (0)
#define SFC_SCK_TAP_delay_clk_tap_mask                                               (0xFFFFFFFF)
#define SFC_SCK_TAP_delay_clk_tap(data)                                              (0xFFFFFFFF&((data)<<0))
#define SFC_SCK_TAP_delay_clk_tap_src(data)                                          ((0xFFFFFFFF&(data))>>0)
#define SFC_SCK_TAP_get_delay_clk_tap(data)                                          ((0xFFFFFFFF&(data))>>0)


#define SB2_SFC_ADR_FOUR_BYTE_EN                                                     0x9801A828
#define SB2_SFC_ADR_FOUR_BYTE_EN_reg_addr                                            "0x9801A828"
#define SB2_SFC_ADR_FOUR_BYTE_EN_reg                                                 0x9801A828
#define set_SB2_SFC_ADR_FOUR_BYTE_EN_reg(data)   (*((volatile unsigned int*) SB2_SFC_ADR_FOUR_BYTE_EN_reg)=data)
#define get_SB2_SFC_ADR_FOUR_BYTE_EN_reg   (*((volatile unsigned int*) SB2_SFC_ADR_FOUR_BYTE_EN_reg))
#define SB2_SFC_ADR_FOUR_BYTE_EN_inst_adr                                            "0x000A"
#define SB2_SFC_ADR_FOUR_BYTE_EN_inst                                                0x000A
#define SB2_SFC_ADR_FOUR_BYTE_EN_SFC_OPCODE_adr4byte_en_shift                        (0)
#define SB2_SFC_ADR_FOUR_BYTE_EN_SFC_OPCODE_adr4byte_en_mask                         (0x00000001)
#define SB2_SFC_ADR_FOUR_BYTE_EN_SFC_OPCODE_adr4byte_en(data)                        (0x00000001&((data)<<0))
#define SB2_SFC_ADR_FOUR_BYTE_EN_SFC_OPCODE_adr4byte_en_src(data)                    ((0x00000001&(data))>>0)
#define SB2_SFC_ADR_FOUR_BYTE_EN_get_SFC_OPCODE_adr4byte_en(data)                    ((0x00000001&(data))>>0)


#define SB2_MUXPAD2                                                                  0x9801A908
#define SB2_MUXPAD2_reg_addr                                                         "0x9801A908"
#define SB2_MUXPAD2_reg                                                              0x9801A908
#define set_SB2_MUXPAD2_reg(data)   (*((volatile unsigned int*) SB2_MUXPAD2_reg)=data)
#define get_SB2_MUXPAD2_reg   (*((volatile unsigned int*) SB2_MUXPAD2_reg))
#define SB2_MUXPAD2_inst_adr                                                         "0x0042"
#define SB2_MUXPAD2_inst                                                             0x0042
#define SB2_MUXPAD2_tp1_clk_shift                                                    (22)
#define SB2_MUXPAD2_tp1_clk_mask                                                     (0x00C00000)
#define SB2_MUXPAD2_tp1_clk(data)                                                    (0x00C00000&((data)<<22))
#define SB2_MUXPAD2_tp1_clk_src(data)                                                ((0x00C00000&(data))>>22)
#define SB2_MUXPAD2_get_tp1_clk(data)                                                ((0x00C00000&(data))>>22)
#define SB2_MUXPAD2_tp1_valid_shift                                                  (20)
#define SB2_MUXPAD2_tp1_valid_mask                                                   (0x00300000)
#define SB2_MUXPAD2_tp1_valid(data)                                                  (0x00300000&((data)<<20))
#define SB2_MUXPAD2_tp1_valid_src(data)                                              ((0x00300000&(data))>>20)
#define SB2_MUXPAD2_get_tp1_valid(data)                                              ((0x00300000&(data))>>20)
#define SB2_MUXPAD2_tp1_sync_shift                                                   (18)
#define SB2_MUXPAD2_tp1_sync_mask                                                    (0x000C0000)
#define SB2_MUXPAD2_tp1_sync(data)                                                   (0x000C0000&((data)<<18))
#define SB2_MUXPAD2_tp1_sync_src(data)                                               ((0x000C0000&(data))>>18)
#define SB2_MUXPAD2_get_tp1_sync(data)                                               ((0x000C0000&(data))>>18)
#define SB2_MUXPAD2_tp1_data_shift                                                   (16)
#define SB2_MUXPAD2_tp1_data_mask                                                    (0x00030000)
#define SB2_MUXPAD2_tp1_data(data)                                                   (0x00030000&((data)<<16))
#define SB2_MUXPAD2_tp1_data_src(data)                                               ((0x00030000&(data))>>16)
#define SB2_MUXPAD2_get_tp1_data(data)                                               ((0x00030000&(data))>>16)
#define SB2_MUXPAD2_tp0_clk_shift                                                    (9)
#define SB2_MUXPAD2_tp0_clk_mask                                                     (0x00000E00)
#define SB2_MUXPAD2_tp0_clk(data)                                                    (0x00000E00&((data)<<9))
#define SB2_MUXPAD2_tp0_clk_src(data)                                                ((0x00000E00&(data))>>9)
#define SB2_MUXPAD2_get_tp0_clk(data)                                                ((0x00000E00&(data))>>9)
#define SB2_MUXPAD2_tp0_valid_shift                                                  (6)
#define SB2_MUXPAD2_tp0_valid_mask                                                   (0x000001C0)
#define SB2_MUXPAD2_tp0_valid(data)                                                  (0x000001C0&((data)<<6))
#define SB2_MUXPAD2_tp0_valid_src(data)                                              ((0x000001C0&(data))>>6)
#define SB2_MUXPAD2_get_tp0_valid(data)                                              ((0x000001C0&(data))>>6)
#define SB2_MUXPAD2_tp0_sync_shift                                                   (3)
#define SB2_MUXPAD2_tp0_sync_mask                                                    (0x00000038)
#define SB2_MUXPAD2_tp0_sync(data)                                                   (0x00000038&((data)<<3))
#define SB2_MUXPAD2_tp0_sync_src(data)                                               ((0x00000038&(data))>>3)
#define SB2_MUXPAD2_get_tp0_sync(data)                                               ((0x00000038&(data))>>3)
#define SB2_MUXPAD2_tp0_data_shift                                                   (0)
#define SB2_MUXPAD2_tp0_data_mask                                                    (0x00000007)
#define SB2_MUXPAD2_tp0_data(data)                                                   (0x00000007&((data)<<0))
#define SB2_MUXPAD2_tp0_data_src(data)                                               ((0x00000007&(data))>>0)
#define SB2_MUXPAD2_get_tp0_data(data)                                               ((0x00000007&(data))>>0)


#define SB2_MUXPAD3                                                                  0x9801A90C
#define SB2_MUXPAD3_reg_addr                                                         "0x9801A90C"
#define SB2_MUXPAD3_reg                                                              0x9801A90C
#define set_SB2_MUXPAD3_reg(data)   (*((volatile unsigned int*) SB2_MUXPAD3_reg)=data)
#define get_SB2_MUXPAD3_reg   (*((volatile unsigned int*) SB2_MUXPAD3_reg))
#define SB2_MUXPAD3_inst_adr                                                         "0x0043"
#define SB2_MUXPAD3_inst                                                             0x0043
#define SB2_MUXPAD3_sensor_cko_0_shift                                               (30)
#define SB2_MUXPAD3_sensor_cko_0_mask                                                (0xC0000000)
#define SB2_MUXPAD3_sensor_cko_0(data)                                               (0xC0000000&((data)<<30))
#define SB2_MUXPAD3_sensor_cko_0_src(data)                                           ((0xC0000000&(data))>>30)
#define SB2_MUXPAD3_get_sensor_cko_0(data)                                           ((0xC0000000&(data))>>30)
#define SB2_MUXPAD3_sensor_cko_1_shift                                               (28)
#define SB2_MUXPAD3_sensor_cko_1_mask                                                (0x30000000)
#define SB2_MUXPAD3_sensor_cko_1(data)                                               (0x30000000&((data)<<28))
#define SB2_MUXPAD3_sensor_cko_1_src(data)                                           ((0x30000000&(data))>>28)
#define SB2_MUXPAD3_get_sensor_cko_1(data)                                           ((0x30000000&(data))>>28)
#define SB2_MUXPAD3_sensor_rst_shift                                                 (26)
#define SB2_MUXPAD3_sensor_rst_mask                                                  (0x0C000000)
#define SB2_MUXPAD3_sensor_rst(data)                                                 (0x0C000000&((data)<<26))
#define SB2_MUXPAD3_sensor_rst_src(data)                                             ((0x0C000000&(data))>>26)
#define SB2_MUXPAD3_get_sensor_rst(data)                                             ((0x0C000000&(data))>>26)
#define SB2_MUXPAD3_sensor_stb_0_shift                                               (24)
#define SB2_MUXPAD3_sensor_stb_0_mask                                                (0x03000000)
#define SB2_MUXPAD3_sensor_stb_0(data)                                               (0x03000000&((data)<<24))
#define SB2_MUXPAD3_sensor_stb_0_src(data)                                           ((0x03000000&(data))>>24)
#define SB2_MUXPAD3_get_sensor_stb_0(data)                                           ((0x03000000&(data))>>24)
#define SB2_MUXPAD3_sensor_stb_1_shift                                               (22)
#define SB2_MUXPAD3_sensor_stb_1_mask                                                (0x00C00000)
#define SB2_MUXPAD3_sensor_stb_1(data)                                               (0x00C00000&((data)<<22))
#define SB2_MUXPAD3_sensor_stb_1_src(data)                                           ((0x00C00000&(data))>>22)
#define SB2_MUXPAD3_get_sensor_stb_1(data)                                           ((0x00C00000&(data))>>22)
#define SB2_MUXPAD3_ejtag_scpu_loc_shift                                             (20)
#define SB2_MUXPAD3_ejtag_scpu_loc_mask                                              (0x00300000)
#define SB2_MUXPAD3_ejtag_scpu_loc(data)                                             (0x00300000&((data)<<20))
#define SB2_MUXPAD3_ejtag_scpu_loc_src(data)                                         ((0x00300000&(data))>>20)
#define SB2_MUXPAD3_get_ejtag_scpu_loc(data)                                         ((0x00300000&(data))>>20)
#define SB2_MUXPAD3_hi_loc_shift                                                     (18)
#define SB2_MUXPAD3_hi_loc_mask                                                      (0x000C0000)
#define SB2_MUXPAD3_hi_loc(data)                                                     (0x000C0000&((data)<<18))
#define SB2_MUXPAD3_hi_loc_src(data)                                                 ((0x000C0000&(data))>>18)
#define SB2_MUXPAD3_get_hi_loc(data)                                                 ((0x000C0000&(data))>>18)
#define SB2_MUXPAD3_usb_id_shift                                                     (16)
#define SB2_MUXPAD3_usb_id_mask                                                      (0x00030000)
#define SB2_MUXPAD3_usb_id(data)                                                     (0x00030000&((data)<<16))
#define SB2_MUXPAD3_usb_id_src(data)                                                 ((0x00030000&(data))>>16)
#define SB2_MUXPAD3_get_usb_id(data)                                                 ((0x00030000&(data))>>16)
#define SB2_MUXPAD3_i2c_scl_5_shift                                                  (10)
#define SB2_MUXPAD3_i2c_scl_5_mask                                                   (0x00000C00)
#define SB2_MUXPAD3_i2c_scl_5(data)                                                  (0x00000C00&((data)<<10))
#define SB2_MUXPAD3_i2c_scl_5_src(data)                                              ((0x00000C00&(data))>>10)
#define SB2_MUXPAD3_get_i2c_scl_5(data)                                              ((0x00000C00&(data))>>10)
#define SB2_MUXPAD3_i2c_sda_5_shift                                                  (8)
#define SB2_MUXPAD3_i2c_sda_5_mask                                                   (0x00000300)
#define SB2_MUXPAD3_i2c_sda_5(data)                                                  (0x00000300&((data)<<8))
#define SB2_MUXPAD3_i2c_sda_5_src(data)                                              ((0x00000300&(data))>>8)
#define SB2_MUXPAD3_get_i2c_sda_5(data)                                              ((0x00000300&(data))>>8)
#define SB2_MUXPAD3_i2c_scl_4_shift                                                  (6)
#define SB2_MUXPAD3_i2c_scl_4_mask                                                   (0x000000C0)
#define SB2_MUXPAD3_i2c_scl_4(data)                                                  (0x000000C0&((data)<<6))
#define SB2_MUXPAD3_i2c_scl_4_src(data)                                              ((0x000000C0&(data))>>6)
#define SB2_MUXPAD3_get_i2c_scl_4(data)                                              ((0x000000C0&(data))>>6)
#define SB2_MUXPAD3_i2c_sda_4_shift                                                  (4)
#define SB2_MUXPAD3_i2c_sda_4_mask                                                   (0x00000030)
#define SB2_MUXPAD3_i2c_sda_4(data)                                                  (0x00000030&((data)<<4))
#define SB2_MUXPAD3_i2c_sda_4_src(data)                                              ((0x00000030&(data))>>4)
#define SB2_MUXPAD3_get_i2c_sda_4(data)                                              ((0x00000030&(data))>>4)


#define SB2_MUXPAD4                                                                  0x9801A910
#define SB2_MUXPAD4_reg_addr                                                         "0x9801A910"
#define SB2_MUXPAD4_reg                                                              0x9801A910
#define set_SB2_MUXPAD4_reg(data)   (*((volatile unsigned int*) SB2_MUXPAD4_reg)=data)
#define get_SB2_MUXPAD4_reg   (*((volatile unsigned int*) SB2_MUXPAD4_reg))
#define SB2_MUXPAD4_inst_adr                                                         "0x0044"
#define SB2_MUXPAD4_inst                                                             0x0044
#define SB2_MUXPAD4_gpio_9_shift                                                     (22)
#define SB2_MUXPAD4_gpio_9_mask                                                      (0x00C00000)
#define SB2_MUXPAD4_gpio_9(data)                                                     (0x00C00000&((data)<<22))
#define SB2_MUXPAD4_gpio_9_src(data)                                                 ((0x00C00000&(data))>>22)
#define SB2_MUXPAD4_get_gpio_9(data)                                                 ((0x00C00000&(data))>>22)
#define SB2_MUXPAD4_gpio_8_shift                                                     (20)
#define SB2_MUXPAD4_gpio_8_mask                                                      (0x00300000)
#define SB2_MUXPAD4_gpio_8(data)                                                     (0x00300000&((data)<<20))
#define SB2_MUXPAD4_gpio_8_src(data)                                                 ((0x00300000&(data))>>20)
#define SB2_MUXPAD4_get_gpio_8(data)                                                 ((0x00300000&(data))>>20)
#define SB2_MUXPAD4_gpio_7_shift                                                     (18)
#define SB2_MUXPAD4_gpio_7_mask                                                      (0x000C0000)
#define SB2_MUXPAD4_gpio_7(data)                                                     (0x000C0000&((data)<<18))
#define SB2_MUXPAD4_gpio_7_src(data)                                                 ((0x000C0000&(data))>>18)
#define SB2_MUXPAD4_get_gpio_7(data)                                                 ((0x000C0000&(data))>>18)
#define SB2_MUXPAD4_gpio_6_shift                                                     (16)
#define SB2_MUXPAD4_gpio_6_mask                                                      (0x00030000)
#define SB2_MUXPAD4_gpio_6(data)                                                     (0x00030000&((data)<<16))
#define SB2_MUXPAD4_gpio_6_src(data)                                                 ((0x00030000&(data))>>16)
#define SB2_MUXPAD4_get_gpio_6(data)                                                 ((0x00030000&(data))>>16)
#define SB2_MUXPAD4_gpio_5_shift                                                     (14)
#define SB2_MUXPAD4_gpio_5_mask                                                      (0x0000C000)
#define SB2_MUXPAD4_gpio_5(data)                                                     (0x0000C000&((data)<<14))
#define SB2_MUXPAD4_gpio_5_src(data)                                                 ((0x0000C000&(data))>>14)
#define SB2_MUXPAD4_get_gpio_5(data)                                                 ((0x0000C000&(data))>>14)
#define SB2_MUXPAD4_gpio_4_shift                                                     (12)
#define SB2_MUXPAD4_gpio_4_mask                                                      (0x00003000)
#define SB2_MUXPAD4_gpio_4(data)                                                     (0x00003000&((data)<<12))
#define SB2_MUXPAD4_gpio_4_src(data)                                                 ((0x00003000&(data))>>12)
#define SB2_MUXPAD4_get_gpio_4(data)                                                 ((0x00003000&(data))>>12)
#define SB2_MUXPAD4_gpio_3_shift                                                     (9)
#define SB2_MUXPAD4_gpio_3_mask                                                      (0x00000E00)
#define SB2_MUXPAD4_gpio_3(data)                                                     (0x00000E00&((data)<<9))
#define SB2_MUXPAD4_gpio_3_src(data)                                                 ((0x00000E00&(data))>>9)
#define SB2_MUXPAD4_get_gpio_3(data)                                                 ((0x00000E00&(data))>>9)
#define SB2_MUXPAD4_gpio_2_shift                                                     (6)
#define SB2_MUXPAD4_gpio_2_mask                                                      (0x000001C0)
#define SB2_MUXPAD4_gpio_2(data)                                                     (0x000001C0&((data)<<6))
#define SB2_MUXPAD4_gpio_2_src(data)                                                 ((0x000001C0&(data))>>6)
#define SB2_MUXPAD4_get_gpio_2(data)                                                 ((0x000001C0&(data))>>6)
#define SB2_MUXPAD4_gpio_1_shift                                                     (3)
#define SB2_MUXPAD4_gpio_1_mask                                                      (0x00000038)
#define SB2_MUXPAD4_gpio_1(data)                                                     (0x00000038&((data)<<3))
#define SB2_MUXPAD4_gpio_1_src(data)                                                 ((0x00000038&(data))>>3)
#define SB2_MUXPAD4_get_gpio_1(data)                                                 ((0x00000038&(data))>>3)
#define SB2_MUXPAD4_gpio_0_shift                                                     (0)
#define SB2_MUXPAD4_gpio_0_mask                                                      (0x00000007)
#define SB2_MUXPAD4_gpio_0(data)                                                     (0x00000007&((data)<<0))
#define SB2_MUXPAD4_gpio_0_src(data)                                                 ((0x00000007&(data))>>0)
#define SB2_MUXPAD4_get_gpio_0(data)                                                 ((0x00000007&(data))>>0)


#define SB2_MUXPAD5                                                                  0x9801A914
#define SB2_MUXPAD5_reg_addr                                                         "0x9801A914"
#define SB2_MUXPAD5_reg                                                              0x9801A914
#define set_SB2_MUXPAD5_reg(data)   (*((volatile unsigned int*) SB2_MUXPAD5_reg)=data)
#define get_SB2_MUXPAD5_reg   (*((volatile unsigned int*) SB2_MUXPAD5_reg))
#define SB2_MUXPAD5_inst_adr                                                         "0x0045"
#define SB2_MUXPAD5_inst                                                             0x0045
#define SB2_MUXPAD5_tp1_loc_shift                                                    (8)
#define SB2_MUXPAD5_tp1_loc_mask                                                     (0x00000100)
#define SB2_MUXPAD5_tp1_loc(data)                                                    (0x00000100&((data)<<8))
#define SB2_MUXPAD5_tp1_loc_src(data)                                                ((0x00000100&(data))>>8)
#define SB2_MUXPAD5_get_tp1_loc(data)                                                ((0x00000100&(data))>>8)
#define SB2_MUXPAD5_tp0_loc_shift                                                    (7)
#define SB2_MUXPAD5_tp0_loc_mask                                                     (0x00000080)
#define SB2_MUXPAD5_tp0_loc(data)                                                    (0x00000080&((data)<<7))
#define SB2_MUXPAD5_tp0_loc_src(data)                                                ((0x00000080&(data))>>7)
#define SB2_MUXPAD5_get_tp0_loc(data)                                                ((0x00000080&(data))>>7)
#define SB2_MUXPAD5_debug_p2s_enable_shift                                           (6)
#define SB2_MUXPAD5_debug_p2s_enable_mask                                            (0x00000040)
#define SB2_MUXPAD5_debug_p2s_enable(data)                                           (0x00000040&((data)<<6))
#define SB2_MUXPAD5_debug_p2s_enable_src(data)                                       ((0x00000040&(data))>>6)
#define SB2_MUXPAD5_get_debug_p2s_enable(data)                                       ((0x00000040&(data))>>6)
#define SB2_MUXPAD5_ur1_loc_shift                                                    (4)
#define SB2_MUXPAD5_ur1_loc_mask                                                     (0x00000030)
#define SB2_MUXPAD5_ur1_loc(data)                                                    (0x00000030&((data)<<4))
#define SB2_MUXPAD5_ur1_loc_src(data)                                                ((0x00000030&(data))>>4)
#define SB2_MUXPAD5_get_ur1_loc(data)                                                ((0x00000030&(data))>>4)
#define SB2_MUXPAD5_ao_loc_shift                                                     (2)
#define SB2_MUXPAD5_ao_loc_mask                                                      (0x0000000C)
#define SB2_MUXPAD5_ao_loc(data)                                                     (0x0000000C&((data)<<2))
#define SB2_MUXPAD5_ao_loc_src(data)                                                 ((0x0000000C&(data))>>2)
#define SB2_MUXPAD5_get_ao_loc(data)                                                 ((0x0000000C&(data))>>2)
#define SB2_MUXPAD5_arm_trace_dbg_en_shift                                           (1)
#define SB2_MUXPAD5_arm_trace_dbg_en_mask                                            (0x00000002)
#define SB2_MUXPAD5_arm_trace_dbg_en(data)                                           (0x00000002&((data)<<1))
#define SB2_MUXPAD5_arm_trace_dbg_en_src(data)                                       ((0x00000002&(data))>>1)
#define SB2_MUXPAD5_get_arm_trace_dbg_en(data)                                       ((0x00000002&(data))>>1)
#define SB2_MUXPAD5_sf_en_shift                                                      (0)
#define SB2_MUXPAD5_sf_en_mask                                                       (0x00000001)
#define SB2_MUXPAD5_sf_en(data)                                                      (0x00000001&((data)<<0))
#define SB2_MUXPAD5_sf_en_src(data)                                                  ((0x00000001&(data))>>0)
#define SB2_MUXPAD5_get_sf_en(data)                                                  ((0x00000001&(data))>>0)


#define SB2_PFUNC_TP0                                                                0x9801A928
#define SB2_PFUNC_TP0_reg_addr                                                       "0x9801A928"
#define SB2_PFUNC_TP0_reg                                                            0x9801A928
#define set_SB2_PFUNC_TP0_reg(data)   (*((volatile unsigned int*) SB2_PFUNC_TP0_reg)=data)
#define get_SB2_PFUNC_TP0_reg   (*((volatile unsigned int*) SB2_PFUNC_TP0_reg))
#define SB2_PFUNC_TP0_inst_adr                                                       "0x004A"
#define SB2_PFUNC_TP0_inst                                                           0x004A
#define SB2_PFUNC_TP0_tp0_data_smt_shift                                             (15)
#define SB2_PFUNC_TP0_tp0_data_smt_mask                                              (0x00008000)
#define SB2_PFUNC_TP0_tp0_data_smt(data)                                             (0x00008000&((data)<<15))
#define SB2_PFUNC_TP0_tp0_data_smt_src(data)                                         ((0x00008000&(data))>>15)
#define SB2_PFUNC_TP0_get_tp0_data_smt(data)                                         ((0x00008000&(data))>>15)
#define SB2_PFUNC_TP0_tp0_data_e2_shift                                              (14)
#define SB2_PFUNC_TP0_tp0_data_e2_mask                                               (0x00004000)
#define SB2_PFUNC_TP0_tp0_data_e2(data)                                              (0x00004000&((data)<<14))
#define SB2_PFUNC_TP0_tp0_data_e2_src(data)                                          ((0x00004000&(data))>>14)
#define SB2_PFUNC_TP0_get_tp0_data_e2(data)                                          ((0x00004000&(data))>>14)
#define SB2_PFUNC_TP0_tp0_data_pud_en_shift                                          (13)
#define SB2_PFUNC_TP0_tp0_data_pud_en_mask                                           (0x00002000)
#define SB2_PFUNC_TP0_tp0_data_pud_en(data)                                          (0x00002000&((data)<<13))
#define SB2_PFUNC_TP0_tp0_data_pud_en_src(data)                                      ((0x00002000&(data))>>13)
#define SB2_PFUNC_TP0_get_tp0_data_pud_en(data)                                      ((0x00002000&(data))>>13)
#define SB2_PFUNC_TP0_tp0_data_pud_sel_shift                                         (12)
#define SB2_PFUNC_TP0_tp0_data_pud_sel_mask                                          (0x00001000)
#define SB2_PFUNC_TP0_tp0_data_pud_sel(data)                                         (0x00001000&((data)<<12))
#define SB2_PFUNC_TP0_tp0_data_pud_sel_src(data)                                     ((0x00001000&(data))>>12)
#define SB2_PFUNC_TP0_get_tp0_data_pud_sel(data)                                     ((0x00001000&(data))>>12)
#define SB2_PFUNC_TP0_tp0_valid_smt_shift                                            (11)
#define SB2_PFUNC_TP0_tp0_valid_smt_mask                                             (0x00000800)
#define SB2_PFUNC_TP0_tp0_valid_smt(data)                                            (0x00000800&((data)<<11))
#define SB2_PFUNC_TP0_tp0_valid_smt_src(data)                                        ((0x00000800&(data))>>11)
#define SB2_PFUNC_TP0_get_tp0_valid_smt(data)                                        ((0x00000800&(data))>>11)
#define SB2_PFUNC_TP0_tp0_valid_e2_shift                                             (10)
#define SB2_PFUNC_TP0_tp0_valid_e2_mask                                              (0x00000400)
#define SB2_PFUNC_TP0_tp0_valid_e2(data)                                             (0x00000400&((data)<<10))
#define SB2_PFUNC_TP0_tp0_valid_e2_src(data)                                         ((0x00000400&(data))>>10)
#define SB2_PFUNC_TP0_get_tp0_valid_e2(data)                                         ((0x00000400&(data))>>10)
#define SB2_PFUNC_TP0_tp0_valid_pud_en_shift                                         (9)
#define SB2_PFUNC_TP0_tp0_valid_pud_en_mask                                          (0x00000200)
#define SB2_PFUNC_TP0_tp0_valid_pud_en(data)                                         (0x00000200&((data)<<9))
#define SB2_PFUNC_TP0_tp0_valid_pud_en_src(data)                                     ((0x00000200&(data))>>9)
#define SB2_PFUNC_TP0_get_tp0_valid_pud_en(data)                                     ((0x00000200&(data))>>9)
#define SB2_PFUNC_TP0_tp0_valid_pud_sel_shift                                        (8)
#define SB2_PFUNC_TP0_tp0_valid_pud_sel_mask                                         (0x00000100)
#define SB2_PFUNC_TP0_tp0_valid_pud_sel(data)                                        (0x00000100&((data)<<8))
#define SB2_PFUNC_TP0_tp0_valid_pud_sel_src(data)                                    ((0x00000100&(data))>>8)
#define SB2_PFUNC_TP0_get_tp0_valid_pud_sel(data)                                    ((0x00000100&(data))>>8)
#define SB2_PFUNC_TP0_tp0_sync_smt_shift                                             (7)
#define SB2_PFUNC_TP0_tp0_sync_smt_mask                                              (0x00000080)
#define SB2_PFUNC_TP0_tp0_sync_smt(data)                                             (0x00000080&((data)<<7))
#define SB2_PFUNC_TP0_tp0_sync_smt_src(data)                                         ((0x00000080&(data))>>7)
#define SB2_PFUNC_TP0_get_tp0_sync_smt(data)                                         ((0x00000080&(data))>>7)
#define SB2_PFUNC_TP0_tp0_sync_e2_shift                                              (6)
#define SB2_PFUNC_TP0_tp0_sync_e2_mask                                               (0x00000040)
#define SB2_PFUNC_TP0_tp0_sync_e2(data)                                              (0x00000040&((data)<<6))
#define SB2_PFUNC_TP0_tp0_sync_e2_src(data)                                          ((0x00000040&(data))>>6)
#define SB2_PFUNC_TP0_get_tp0_sync_e2(data)                                          ((0x00000040&(data))>>6)
#define SB2_PFUNC_TP0_tp0_sync_pud_en_shift                                          (5)
#define SB2_PFUNC_TP0_tp0_sync_pud_en_mask                                           (0x00000020)
#define SB2_PFUNC_TP0_tp0_sync_pud_en(data)                                          (0x00000020&((data)<<5))
#define SB2_PFUNC_TP0_tp0_sync_pud_en_src(data)                                      ((0x00000020&(data))>>5)
#define SB2_PFUNC_TP0_get_tp0_sync_pud_en(data)                                      ((0x00000020&(data))>>5)
#define SB2_PFUNC_TP0_tp0_sync_pud_sel_shift                                         (4)
#define SB2_PFUNC_TP0_tp0_sync_pud_sel_mask                                          (0x00000010)
#define SB2_PFUNC_TP0_tp0_sync_pud_sel(data)                                         (0x00000010&((data)<<4))
#define SB2_PFUNC_TP0_tp0_sync_pud_sel_src(data)                                     ((0x00000010&(data))>>4)
#define SB2_PFUNC_TP0_get_tp0_sync_pud_sel(data)                                     ((0x00000010&(data))>>4)
#define SB2_PFUNC_TP0_tp0_clk_smt_shift                                              (3)
#define SB2_PFUNC_TP0_tp0_clk_smt_mask                                               (0x00000008)
#define SB2_PFUNC_TP0_tp0_clk_smt(data)                                              (0x00000008&((data)<<3))
#define SB2_PFUNC_TP0_tp0_clk_smt_src(data)                                          ((0x00000008&(data))>>3)
#define SB2_PFUNC_TP0_get_tp0_clk_smt(data)                                          ((0x00000008&(data))>>3)
#define SB2_PFUNC_TP0_tp0_clk_e2_shift                                               (2)
#define SB2_PFUNC_TP0_tp0_clk_e2_mask                                                (0x00000004)
#define SB2_PFUNC_TP0_tp0_clk_e2(data)                                               (0x00000004&((data)<<2))
#define SB2_PFUNC_TP0_tp0_clk_e2_src(data)                                           ((0x00000004&(data))>>2)
#define SB2_PFUNC_TP0_get_tp0_clk_e2(data)                                           ((0x00000004&(data))>>2)
#define SB2_PFUNC_TP0_tp0_clk_pud_en_shift                                           (1)
#define SB2_PFUNC_TP0_tp0_clk_pud_en_mask                                            (0x00000002)
#define SB2_PFUNC_TP0_tp0_clk_pud_en(data)                                           (0x00000002&((data)<<1))
#define SB2_PFUNC_TP0_tp0_clk_pud_en_src(data)                                       ((0x00000002&(data))>>1)
#define SB2_PFUNC_TP0_get_tp0_clk_pud_en(data)                                       ((0x00000002&(data))>>1)
#define SB2_PFUNC_TP0_tp0_clk_pud_sel_shift                                          (0)
#define SB2_PFUNC_TP0_tp0_clk_pud_sel_mask                                           (0x00000001)
#define SB2_PFUNC_TP0_tp0_clk_pud_sel(data)                                          (0x00000001&((data)<<0))
#define SB2_PFUNC_TP0_tp0_clk_pud_sel_src(data)                                      ((0x00000001&(data))>>0)
#define SB2_PFUNC_TP0_get_tp0_clk_pud_sel(data)                                      ((0x00000001&(data))>>0)


#define SB2_PFUNC_TP1                                                                0x9801A92C
#define SB2_PFUNC_TP1_reg_addr                                                       "0x9801A92C"
#define SB2_PFUNC_TP1_reg                                                            0x9801A92C
#define set_SB2_PFUNC_TP1_reg(data)   (*((volatile unsigned int*) SB2_PFUNC_TP1_reg)=data)
#define get_SB2_PFUNC_TP1_reg   (*((volatile unsigned int*) SB2_PFUNC_TP1_reg))
#define SB2_PFUNC_TP1_inst_adr                                                       "0x004B"
#define SB2_PFUNC_TP1_inst                                                           0x004B
#define SB2_PFUNC_TP1_tp1_data_smt_shift                                             (15)
#define SB2_PFUNC_TP1_tp1_data_smt_mask                                              (0x00008000)
#define SB2_PFUNC_TP1_tp1_data_smt(data)                                             (0x00008000&((data)<<15))
#define SB2_PFUNC_TP1_tp1_data_smt_src(data)                                         ((0x00008000&(data))>>15)
#define SB2_PFUNC_TP1_get_tp1_data_smt(data)                                         ((0x00008000&(data))>>15)
#define SB2_PFUNC_TP1_tp1_data_e2_shift                                              (14)
#define SB2_PFUNC_TP1_tp1_data_e2_mask                                               (0x00004000)
#define SB2_PFUNC_TP1_tp1_data_e2(data)                                              (0x00004000&((data)<<14))
#define SB2_PFUNC_TP1_tp1_data_e2_src(data)                                          ((0x00004000&(data))>>14)
#define SB2_PFUNC_TP1_get_tp1_data_e2(data)                                          ((0x00004000&(data))>>14)
#define SB2_PFUNC_TP1_tp1_data_pud_en_shift                                          (13)
#define SB2_PFUNC_TP1_tp1_data_pud_en_mask                                           (0x00002000)
#define SB2_PFUNC_TP1_tp1_data_pud_en(data)                                          (0x00002000&((data)<<13))
#define SB2_PFUNC_TP1_tp1_data_pud_en_src(data)                                      ((0x00002000&(data))>>13)
#define SB2_PFUNC_TP1_get_tp1_data_pud_en(data)                                      ((0x00002000&(data))>>13)
#define SB2_PFUNC_TP1_tp1_data_pud_sel_shift                                         (12)
#define SB2_PFUNC_TP1_tp1_data_pud_sel_mask                                          (0x00001000)
#define SB2_PFUNC_TP1_tp1_data_pud_sel(data)                                         (0x00001000&((data)<<12))
#define SB2_PFUNC_TP1_tp1_data_pud_sel_src(data)                                     ((0x00001000&(data))>>12)
#define SB2_PFUNC_TP1_get_tp1_data_pud_sel(data)                                     ((0x00001000&(data))>>12)
#define SB2_PFUNC_TP1_tp1_valid_smt_shift                                            (11)
#define SB2_PFUNC_TP1_tp1_valid_smt_mask                                             (0x00000800)
#define SB2_PFUNC_TP1_tp1_valid_smt(data)                                            (0x00000800&((data)<<11))
#define SB2_PFUNC_TP1_tp1_valid_smt_src(data)                                        ((0x00000800&(data))>>11)
#define SB2_PFUNC_TP1_get_tp1_valid_smt(data)                                        ((0x00000800&(data))>>11)
#define SB2_PFUNC_TP1_tp1_valid_e2_shift                                             (10)
#define SB2_PFUNC_TP1_tp1_valid_e2_mask                                              (0x00000400)
#define SB2_PFUNC_TP1_tp1_valid_e2(data)                                             (0x00000400&((data)<<10))
#define SB2_PFUNC_TP1_tp1_valid_e2_src(data)                                         ((0x00000400&(data))>>10)
#define SB2_PFUNC_TP1_get_tp1_valid_e2(data)                                         ((0x00000400&(data))>>10)
#define SB2_PFUNC_TP1_tp1_valid_pud_en_shift                                         (9)
#define SB2_PFUNC_TP1_tp1_valid_pud_en_mask                                          (0x00000200)
#define SB2_PFUNC_TP1_tp1_valid_pud_en(data)                                         (0x00000200&((data)<<9))
#define SB2_PFUNC_TP1_tp1_valid_pud_en_src(data)                                     ((0x00000200&(data))>>9)
#define SB2_PFUNC_TP1_get_tp1_valid_pud_en(data)                                     ((0x00000200&(data))>>9)
#define SB2_PFUNC_TP1_tp1_valid_pud_sel_shift                                        (8)
#define SB2_PFUNC_TP1_tp1_valid_pud_sel_mask                                         (0x00000100)
#define SB2_PFUNC_TP1_tp1_valid_pud_sel(data)                                        (0x00000100&((data)<<8))
#define SB2_PFUNC_TP1_tp1_valid_pud_sel_src(data)                                    ((0x00000100&(data))>>8)
#define SB2_PFUNC_TP1_get_tp1_valid_pud_sel(data)                                    ((0x00000100&(data))>>8)
#define SB2_PFUNC_TP1_tp1_sync_smt_shift                                             (7)
#define SB2_PFUNC_TP1_tp1_sync_smt_mask                                              (0x00000080)
#define SB2_PFUNC_TP1_tp1_sync_smt(data)                                             (0x00000080&((data)<<7))
#define SB2_PFUNC_TP1_tp1_sync_smt_src(data)                                         ((0x00000080&(data))>>7)
#define SB2_PFUNC_TP1_get_tp1_sync_smt(data)                                         ((0x00000080&(data))>>7)
#define SB2_PFUNC_TP1_tp1_sync_e2_shift                                              (6)
#define SB2_PFUNC_TP1_tp1_sync_e2_mask                                               (0x00000040)
#define SB2_PFUNC_TP1_tp1_sync_e2(data)                                              (0x00000040&((data)<<6))
#define SB2_PFUNC_TP1_tp1_sync_e2_src(data)                                          ((0x00000040&(data))>>6)
#define SB2_PFUNC_TP1_get_tp1_sync_e2(data)                                          ((0x00000040&(data))>>6)
#define SB2_PFUNC_TP1_tp1_sync_pud_en_shift                                          (5)
#define SB2_PFUNC_TP1_tp1_sync_pud_en_mask                                           (0x00000020)
#define SB2_PFUNC_TP1_tp1_sync_pud_en(data)                                          (0x00000020&((data)<<5))
#define SB2_PFUNC_TP1_tp1_sync_pud_en_src(data)                                      ((0x00000020&(data))>>5)
#define SB2_PFUNC_TP1_get_tp1_sync_pud_en(data)                                      ((0x00000020&(data))>>5)
#define SB2_PFUNC_TP1_tp1_sync_pud_sel_shift                                         (4)
#define SB2_PFUNC_TP1_tp1_sync_pud_sel_mask                                          (0x00000010)
#define SB2_PFUNC_TP1_tp1_sync_pud_sel(data)                                         (0x00000010&((data)<<4))
#define SB2_PFUNC_TP1_tp1_sync_pud_sel_src(data)                                     ((0x00000010&(data))>>4)
#define SB2_PFUNC_TP1_get_tp1_sync_pud_sel(data)                                     ((0x00000010&(data))>>4)
#define SB2_PFUNC_TP1_tp1_clk_smt_shift                                              (3)
#define SB2_PFUNC_TP1_tp1_clk_smt_mask                                               (0x00000008)
#define SB2_PFUNC_TP1_tp1_clk_smt(data)                                              (0x00000008&((data)<<3))
#define SB2_PFUNC_TP1_tp1_clk_smt_src(data)                                          ((0x00000008&(data))>>3)
#define SB2_PFUNC_TP1_get_tp1_clk_smt(data)                                          ((0x00000008&(data))>>3)
#define SB2_PFUNC_TP1_tp1_clk_e2_shift                                               (2)
#define SB2_PFUNC_TP1_tp1_clk_e2_mask                                                (0x00000004)
#define SB2_PFUNC_TP1_tp1_clk_e2(data)                                               (0x00000004&((data)<<2))
#define SB2_PFUNC_TP1_tp1_clk_e2_src(data)                                           ((0x00000004&(data))>>2)
#define SB2_PFUNC_TP1_get_tp1_clk_e2(data)                                           ((0x00000004&(data))>>2)
#define SB2_PFUNC_TP1_tp1_clk_pud_en_shift                                           (1)
#define SB2_PFUNC_TP1_tp1_clk_pud_en_mask                                            (0x00000002)
#define SB2_PFUNC_TP1_tp1_clk_pud_en(data)                                           (0x00000002&((data)<<1))
#define SB2_PFUNC_TP1_tp1_clk_pud_en_src(data)                                       ((0x00000002&(data))>>1)
#define SB2_PFUNC_TP1_get_tp1_clk_pud_en(data)                                       ((0x00000002&(data))>>1)
#define SB2_PFUNC_TP1_tp1_clk_pud_sel_shift                                          (0)
#define SB2_PFUNC_TP1_tp1_clk_pud_sel_mask                                           (0x00000001)
#define SB2_PFUNC_TP1_tp1_clk_pud_sel(data)                                          (0x00000001&((data)<<0))
#define SB2_PFUNC_TP1_tp1_clk_pud_sel_src(data)                                      ((0x00000001&(data))>>0)
#define SB2_PFUNC_TP1_get_tp1_clk_pud_sel(data)                                      ((0x00000001&(data))>>0)


#define SB2_PFUNC_MISC0                                                              0x9801A930
#define SB2_PFUNC_MISC0_reg_addr                                                     "0x9801A930"
#define SB2_PFUNC_MISC0_reg                                                          0x9801A930
#define set_SB2_PFUNC_MISC0_reg(data)   (*((volatile unsigned int*) SB2_PFUNC_MISC0_reg)=data)
#define get_SB2_PFUNC_MISC0_reg   (*((volatile unsigned int*) SB2_PFUNC_MISC0_reg))
#define SB2_PFUNC_MISC0_inst_adr                                                     "0x004C"
#define SB2_PFUNC_MISC0_inst                                                         0x004C
#define SB2_PFUNC_MISC0_i2c_scl_5_smt_shift                                          (23)
#define SB2_PFUNC_MISC0_i2c_scl_5_smt_mask                                           (0x00800000)
#define SB2_PFUNC_MISC0_i2c_scl_5_smt(data)                                          (0x00800000&((data)<<23))
#define SB2_PFUNC_MISC0_i2c_scl_5_smt_src(data)                                      ((0x00800000&(data))>>23)
#define SB2_PFUNC_MISC0_get_i2c_scl_5_smt(data)                                      ((0x00800000&(data))>>23)
#define SB2_PFUNC_MISC0_i2c_scl_5_e2_shift                                           (22)
#define SB2_PFUNC_MISC0_i2c_scl_5_e2_mask                                            (0x00400000)
#define SB2_PFUNC_MISC0_i2c_scl_5_e2(data)                                           (0x00400000&((data)<<22))
#define SB2_PFUNC_MISC0_i2c_scl_5_e2_src(data)                                       ((0x00400000&(data))>>22)
#define SB2_PFUNC_MISC0_get_i2c_scl_5_e2(data)                                       ((0x00400000&(data))>>22)
#define SB2_PFUNC_MISC0_i2c_scl_5_pud_en_shift                                       (21)
#define SB2_PFUNC_MISC0_i2c_scl_5_pud_en_mask                                        (0x00200000)
#define SB2_PFUNC_MISC0_i2c_scl_5_pud_en(data)                                       (0x00200000&((data)<<21))
#define SB2_PFUNC_MISC0_i2c_scl_5_pud_en_src(data)                                   ((0x00200000&(data))>>21)
#define SB2_PFUNC_MISC0_get_i2c_scl_5_pud_en(data)                                   ((0x00200000&(data))>>21)
#define SB2_PFUNC_MISC0_i2c_scl_5_pud_sel_shift                                      (20)
#define SB2_PFUNC_MISC0_i2c_scl_5_pud_sel_mask                                       (0x00100000)
#define SB2_PFUNC_MISC0_i2c_scl_5_pud_sel(data)                                      (0x00100000&((data)<<20))
#define SB2_PFUNC_MISC0_i2c_scl_5_pud_sel_src(data)                                  ((0x00100000&(data))>>20)
#define SB2_PFUNC_MISC0_get_i2c_scl_5_pud_sel(data)                                  ((0x00100000&(data))>>20)
#define SB2_PFUNC_MISC0_i2c_sda_5_smt_shift                                          (19)
#define SB2_PFUNC_MISC0_i2c_sda_5_smt_mask                                           (0x00080000)
#define SB2_PFUNC_MISC0_i2c_sda_5_smt(data)                                          (0x00080000&((data)<<19))
#define SB2_PFUNC_MISC0_i2c_sda_5_smt_src(data)                                      ((0x00080000&(data))>>19)
#define SB2_PFUNC_MISC0_get_i2c_sda_5_smt(data)                                      ((0x00080000&(data))>>19)
#define SB2_PFUNC_MISC0_i2c_sda_5_e2_shift                                           (18)
#define SB2_PFUNC_MISC0_i2c_sda_5_e2_mask                                            (0x00040000)
#define SB2_PFUNC_MISC0_i2c_sda_5_e2(data)                                           (0x00040000&((data)<<18))
#define SB2_PFUNC_MISC0_i2c_sda_5_e2_src(data)                                       ((0x00040000&(data))>>18)
#define SB2_PFUNC_MISC0_get_i2c_sda_5_e2(data)                                       ((0x00040000&(data))>>18)
#define SB2_PFUNC_MISC0_i2c_sda_5_pud_en_shift                                       (17)
#define SB2_PFUNC_MISC0_i2c_sda_5_pud_en_mask                                        (0x00020000)
#define SB2_PFUNC_MISC0_i2c_sda_5_pud_en(data)                                       (0x00020000&((data)<<17))
#define SB2_PFUNC_MISC0_i2c_sda_5_pud_en_src(data)                                   ((0x00020000&(data))>>17)
#define SB2_PFUNC_MISC0_get_i2c_sda_5_pud_en(data)                                   ((0x00020000&(data))>>17)
#define SB2_PFUNC_MISC0_i2c_sda_5_pud_sel_shift                                      (16)
#define SB2_PFUNC_MISC0_i2c_sda_5_pud_sel_mask                                       (0x00010000)
#define SB2_PFUNC_MISC0_i2c_sda_5_pud_sel(data)                                      (0x00010000&((data)<<16))
#define SB2_PFUNC_MISC0_i2c_sda_5_pud_sel_src(data)                                  ((0x00010000&(data))>>16)
#define SB2_PFUNC_MISC0_get_i2c_sda_5_pud_sel(data)                                  ((0x00010000&(data))>>16)
#define SB2_PFUNC_MISC0_i2c_scl_4_smt_shift                                          (15)
#define SB2_PFUNC_MISC0_i2c_scl_4_smt_mask                                           (0x00008000)
#define SB2_PFUNC_MISC0_i2c_scl_4_smt(data)                                          (0x00008000&((data)<<15))
#define SB2_PFUNC_MISC0_i2c_scl_4_smt_src(data)                                      ((0x00008000&(data))>>15)
#define SB2_PFUNC_MISC0_get_i2c_scl_4_smt(data)                                      ((0x00008000&(data))>>15)
#define SB2_PFUNC_MISC0_i2c_scl_4_e2_shift                                           (14)
#define SB2_PFUNC_MISC0_i2c_scl_4_e2_mask                                            (0x00004000)
#define SB2_PFUNC_MISC0_i2c_scl_4_e2(data)                                           (0x00004000&((data)<<14))
#define SB2_PFUNC_MISC0_i2c_scl_4_e2_src(data)                                       ((0x00004000&(data))>>14)
#define SB2_PFUNC_MISC0_get_i2c_scl_4_e2(data)                                       ((0x00004000&(data))>>14)
#define SB2_PFUNC_MISC0_i2c_scl_4_pud_en_shift                                       (13)
#define SB2_PFUNC_MISC0_i2c_scl_4_pud_en_mask                                        (0x00002000)
#define SB2_PFUNC_MISC0_i2c_scl_4_pud_en(data)                                       (0x00002000&((data)<<13))
#define SB2_PFUNC_MISC0_i2c_scl_4_pud_en_src(data)                                   ((0x00002000&(data))>>13)
#define SB2_PFUNC_MISC0_get_i2c_scl_4_pud_en(data)                                   ((0x00002000&(data))>>13)
#define SB2_PFUNC_MISC0_i2c_scl_4_pud_sel_shift                                      (12)
#define SB2_PFUNC_MISC0_i2c_scl_4_pud_sel_mask                                       (0x00001000)
#define SB2_PFUNC_MISC0_i2c_scl_4_pud_sel(data)                                      (0x00001000&((data)<<12))
#define SB2_PFUNC_MISC0_i2c_scl_4_pud_sel_src(data)                                  ((0x00001000&(data))>>12)
#define SB2_PFUNC_MISC0_get_i2c_scl_4_pud_sel(data)                                  ((0x00001000&(data))>>12)
#define SB2_PFUNC_MISC0_i2c_sda_4_smt_shift                                          (11)
#define SB2_PFUNC_MISC0_i2c_sda_4_smt_mask                                           (0x00000800)
#define SB2_PFUNC_MISC0_i2c_sda_4_smt(data)                                          (0x00000800&((data)<<11))
#define SB2_PFUNC_MISC0_i2c_sda_4_smt_src(data)                                      ((0x00000800&(data))>>11)
#define SB2_PFUNC_MISC0_get_i2c_sda_4_smt(data)                                      ((0x00000800&(data))>>11)
#define SB2_PFUNC_MISC0_i2c_sda_4_e2_shift                                           (10)
#define SB2_PFUNC_MISC0_i2c_sda_4_e2_mask                                            (0x00000400)
#define SB2_PFUNC_MISC0_i2c_sda_4_e2(data)                                           (0x00000400&((data)<<10))
#define SB2_PFUNC_MISC0_i2c_sda_4_e2_src(data)                                       ((0x00000400&(data))>>10)
#define SB2_PFUNC_MISC0_get_i2c_sda_4_e2(data)                                       ((0x00000400&(data))>>10)
#define SB2_PFUNC_MISC0_i2c_sda_4_pud_en_shift                                       (9)
#define SB2_PFUNC_MISC0_i2c_sda_4_pud_en_mask                                        (0x00000200)
#define SB2_PFUNC_MISC0_i2c_sda_4_pud_en(data)                                       (0x00000200&((data)<<9))
#define SB2_PFUNC_MISC0_i2c_sda_4_pud_en_src(data)                                   ((0x00000200&(data))>>9)
#define SB2_PFUNC_MISC0_get_i2c_sda_4_pud_en(data)                                   ((0x00000200&(data))>>9)
#define SB2_PFUNC_MISC0_i2c_sda_4_pud_sel_shift                                      (8)
#define SB2_PFUNC_MISC0_i2c_sda_4_pud_sel_mask                                       (0x00000100)
#define SB2_PFUNC_MISC0_i2c_sda_4_pud_sel(data)                                      (0x00000100&((data)<<8))
#define SB2_PFUNC_MISC0_i2c_sda_4_pud_sel_src(data)                                  ((0x00000100&(data))>>8)
#define SB2_PFUNC_MISC0_get_i2c_sda_4_pud_sel(data)                                  ((0x00000100&(data))>>8)


#define SB2_PFUNC_MISC1                                                              0x9801A934
#define SB2_PFUNC_MISC1_reg_addr                                                     "0x9801A934"
#define SB2_PFUNC_MISC1_reg                                                          0x9801A934
#define set_SB2_PFUNC_MISC1_reg(data)   (*((volatile unsigned int*) SB2_PFUNC_MISC1_reg)=data)
#define get_SB2_PFUNC_MISC1_reg   (*((volatile unsigned int*) SB2_PFUNC_MISC1_reg))
#define SB2_PFUNC_MISC1_inst_adr                                                     "0x004D"
#define SB2_PFUNC_MISC1_inst                                                         0x004D
#define SB2_PFUNC_MISC1_gpio_7_smt_shift                                             (31)
#define SB2_PFUNC_MISC1_gpio_7_smt_mask                                              (0x80000000)
#define SB2_PFUNC_MISC1_gpio_7_smt(data)                                             (0x80000000&((data)<<31))
#define SB2_PFUNC_MISC1_gpio_7_smt_src(data)                                         ((0x80000000&(data))>>31)
#define SB2_PFUNC_MISC1_get_gpio_7_smt(data)                                         ((0x80000000&(data))>>31)
#define SB2_PFUNC_MISC1_gpio_7_e2_shift                                              (30)
#define SB2_PFUNC_MISC1_gpio_7_e2_mask                                               (0x40000000)
#define SB2_PFUNC_MISC1_gpio_7_e2(data)                                              (0x40000000&((data)<<30))
#define SB2_PFUNC_MISC1_gpio_7_e2_src(data)                                          ((0x40000000&(data))>>30)
#define SB2_PFUNC_MISC1_get_gpio_7_e2(data)                                          ((0x40000000&(data))>>30)
#define SB2_PFUNC_MISC1_gpio_7_pud_en_shift                                          (29)
#define SB2_PFUNC_MISC1_gpio_7_pud_en_mask                                           (0x20000000)
#define SB2_PFUNC_MISC1_gpio_7_pud_en(data)                                          (0x20000000&((data)<<29))
#define SB2_PFUNC_MISC1_gpio_7_pud_en_src(data)                                      ((0x20000000&(data))>>29)
#define SB2_PFUNC_MISC1_get_gpio_7_pud_en(data)                                      ((0x20000000&(data))>>29)
#define SB2_PFUNC_MISC1_gpio_7_pud_sel_shift                                         (28)
#define SB2_PFUNC_MISC1_gpio_7_pud_sel_mask                                          (0x10000000)
#define SB2_PFUNC_MISC1_gpio_7_pud_sel(data)                                         (0x10000000&((data)<<28))
#define SB2_PFUNC_MISC1_gpio_7_pud_sel_src(data)                                     ((0x10000000&(data))>>28)
#define SB2_PFUNC_MISC1_get_gpio_7_pud_sel(data)                                     ((0x10000000&(data))>>28)
#define SB2_PFUNC_MISC1_gpio_6_smt_shift                                             (27)
#define SB2_PFUNC_MISC1_gpio_6_smt_mask                                              (0x08000000)
#define SB2_PFUNC_MISC1_gpio_6_smt(data)                                             (0x08000000&((data)<<27))
#define SB2_PFUNC_MISC1_gpio_6_smt_src(data)                                         ((0x08000000&(data))>>27)
#define SB2_PFUNC_MISC1_get_gpio_6_smt(data)                                         ((0x08000000&(data))>>27)
#define SB2_PFUNC_MISC1_gpio_6_e2_shift                                              (26)
#define SB2_PFUNC_MISC1_gpio_6_e2_mask                                               (0x04000000)
#define SB2_PFUNC_MISC1_gpio_6_e2(data)                                              (0x04000000&((data)<<26))
#define SB2_PFUNC_MISC1_gpio_6_e2_src(data)                                          ((0x04000000&(data))>>26)
#define SB2_PFUNC_MISC1_get_gpio_6_e2(data)                                          ((0x04000000&(data))>>26)
#define SB2_PFUNC_MISC1_gpio_6_pud_en_shift                                          (25)
#define SB2_PFUNC_MISC1_gpio_6_pud_en_mask                                           (0x02000000)
#define SB2_PFUNC_MISC1_gpio_6_pud_en(data)                                          (0x02000000&((data)<<25))
#define SB2_PFUNC_MISC1_gpio_6_pud_en_src(data)                                      ((0x02000000&(data))>>25)
#define SB2_PFUNC_MISC1_get_gpio_6_pud_en(data)                                      ((0x02000000&(data))>>25)
#define SB2_PFUNC_MISC1_gpio_6_pud_sel_shift                                         (24)
#define SB2_PFUNC_MISC1_gpio_6_pud_sel_mask                                          (0x01000000)
#define SB2_PFUNC_MISC1_gpio_6_pud_sel(data)                                         (0x01000000&((data)<<24))
#define SB2_PFUNC_MISC1_gpio_6_pud_sel_src(data)                                     ((0x01000000&(data))>>24)
#define SB2_PFUNC_MISC1_get_gpio_6_pud_sel(data)                                     ((0x01000000&(data))>>24)
#define SB2_PFUNC_MISC1_gpio_5_smt_shift                                             (23)
#define SB2_PFUNC_MISC1_gpio_5_smt_mask                                              (0x00800000)
#define SB2_PFUNC_MISC1_gpio_5_smt(data)                                             (0x00800000&((data)<<23))
#define SB2_PFUNC_MISC1_gpio_5_smt_src(data)                                         ((0x00800000&(data))>>23)
#define SB2_PFUNC_MISC1_get_gpio_5_smt(data)                                         ((0x00800000&(data))>>23)
#define SB2_PFUNC_MISC1_gpio_5_e2_shift                                              (22)
#define SB2_PFUNC_MISC1_gpio_5_e2_mask                                               (0x00400000)
#define SB2_PFUNC_MISC1_gpio_5_e2(data)                                              (0x00400000&((data)<<22))
#define SB2_PFUNC_MISC1_gpio_5_e2_src(data)                                          ((0x00400000&(data))>>22)
#define SB2_PFUNC_MISC1_get_gpio_5_e2(data)                                          ((0x00400000&(data))>>22)
#define SB2_PFUNC_MISC1_gpio_5_pud_en_shift                                          (21)
#define SB2_PFUNC_MISC1_gpio_5_pud_en_mask                                           (0x00200000)
#define SB2_PFUNC_MISC1_gpio_5_pud_en(data)                                          (0x00200000&((data)<<21))
#define SB2_PFUNC_MISC1_gpio_5_pud_en_src(data)                                      ((0x00200000&(data))>>21)
#define SB2_PFUNC_MISC1_get_gpio_5_pud_en(data)                                      ((0x00200000&(data))>>21)
#define SB2_PFUNC_MISC1_gpio_5_pud_sel_shift                                         (20)
#define SB2_PFUNC_MISC1_gpio_5_pud_sel_mask                                          (0x00100000)
#define SB2_PFUNC_MISC1_gpio_5_pud_sel(data)                                         (0x00100000&((data)<<20))
#define SB2_PFUNC_MISC1_gpio_5_pud_sel_src(data)                                     ((0x00100000&(data))>>20)
#define SB2_PFUNC_MISC1_get_gpio_5_pud_sel(data)                                     ((0x00100000&(data))>>20)
#define SB2_PFUNC_MISC1_gpio_4_smt_shift                                             (19)
#define SB2_PFUNC_MISC1_gpio_4_smt_mask                                              (0x00080000)
#define SB2_PFUNC_MISC1_gpio_4_smt(data)                                             (0x00080000&((data)<<19))
#define SB2_PFUNC_MISC1_gpio_4_smt_src(data)                                         ((0x00080000&(data))>>19)
#define SB2_PFUNC_MISC1_get_gpio_4_smt(data)                                         ((0x00080000&(data))>>19)
#define SB2_PFUNC_MISC1_gpio_4_e2_shift                                              (18)
#define SB2_PFUNC_MISC1_gpio_4_e2_mask                                               (0x00040000)
#define SB2_PFUNC_MISC1_gpio_4_e2(data)                                              (0x00040000&((data)<<18))
#define SB2_PFUNC_MISC1_gpio_4_e2_src(data)                                          ((0x00040000&(data))>>18)
#define SB2_PFUNC_MISC1_get_gpio_4_e2(data)                                          ((0x00040000&(data))>>18)
#define SB2_PFUNC_MISC1_gpio_4_pud_en_shift                                          (17)
#define SB2_PFUNC_MISC1_gpio_4_pud_en_mask                                           (0x00020000)
#define SB2_PFUNC_MISC1_gpio_4_pud_en(data)                                          (0x00020000&((data)<<17))
#define SB2_PFUNC_MISC1_gpio_4_pud_en_src(data)                                      ((0x00020000&(data))>>17)
#define SB2_PFUNC_MISC1_get_gpio_4_pud_en(data)                                      ((0x00020000&(data))>>17)
#define SB2_PFUNC_MISC1_gpio_4_pud_sel_shift                                         (16)
#define SB2_PFUNC_MISC1_gpio_4_pud_sel_mask                                          (0x00010000)
#define SB2_PFUNC_MISC1_gpio_4_pud_sel(data)                                         (0x00010000&((data)<<16))
#define SB2_PFUNC_MISC1_gpio_4_pud_sel_src(data)                                     ((0x00010000&(data))>>16)
#define SB2_PFUNC_MISC1_get_gpio_4_pud_sel(data)                                     ((0x00010000&(data))>>16)
#define SB2_PFUNC_MISC1_gpio_3_smt_shift                                             (15)
#define SB2_PFUNC_MISC1_gpio_3_smt_mask                                              (0x00008000)
#define SB2_PFUNC_MISC1_gpio_3_smt(data)                                             (0x00008000&((data)<<15))
#define SB2_PFUNC_MISC1_gpio_3_smt_src(data)                                         ((0x00008000&(data))>>15)
#define SB2_PFUNC_MISC1_get_gpio_3_smt(data)                                         ((0x00008000&(data))>>15)
#define SB2_PFUNC_MISC1_gpio_3_e2_shift                                              (14)
#define SB2_PFUNC_MISC1_gpio_3_e2_mask                                               (0x00004000)
#define SB2_PFUNC_MISC1_gpio_3_e2(data)                                              (0x00004000&((data)<<14))
#define SB2_PFUNC_MISC1_gpio_3_e2_src(data)                                          ((0x00004000&(data))>>14)
#define SB2_PFUNC_MISC1_get_gpio_3_e2(data)                                          ((0x00004000&(data))>>14)
#define SB2_PFUNC_MISC1_gpio_3_pud_en_shift                                          (13)
#define SB2_PFUNC_MISC1_gpio_3_pud_en_mask                                           (0x00002000)
#define SB2_PFUNC_MISC1_gpio_3_pud_en(data)                                          (0x00002000&((data)<<13))
#define SB2_PFUNC_MISC1_gpio_3_pud_en_src(data)                                      ((0x00002000&(data))>>13)
#define SB2_PFUNC_MISC1_get_gpio_3_pud_en(data)                                      ((0x00002000&(data))>>13)
#define SB2_PFUNC_MISC1_gpio_3_pud_sel_shift                                         (12)
#define SB2_PFUNC_MISC1_gpio_3_pud_sel_mask                                          (0x00001000)
#define SB2_PFUNC_MISC1_gpio_3_pud_sel(data)                                         (0x00001000&((data)<<12))
#define SB2_PFUNC_MISC1_gpio_3_pud_sel_src(data)                                     ((0x00001000&(data))>>12)
#define SB2_PFUNC_MISC1_get_gpio_3_pud_sel(data)                                     ((0x00001000&(data))>>12)
#define SB2_PFUNC_MISC1_gpio_2_smt_shift                                             (11)
#define SB2_PFUNC_MISC1_gpio_2_smt_mask                                              (0x00000800)
#define SB2_PFUNC_MISC1_gpio_2_smt(data)                                             (0x00000800&((data)<<11))
#define SB2_PFUNC_MISC1_gpio_2_smt_src(data)                                         ((0x00000800&(data))>>11)
#define SB2_PFUNC_MISC1_get_gpio_2_smt(data)                                         ((0x00000800&(data))>>11)
#define SB2_PFUNC_MISC1_gpio_2_e2_shift                                              (10)
#define SB2_PFUNC_MISC1_gpio_2_e2_mask                                               (0x00000400)
#define SB2_PFUNC_MISC1_gpio_2_e2(data)                                              (0x00000400&((data)<<10))
#define SB2_PFUNC_MISC1_gpio_2_e2_src(data)                                          ((0x00000400&(data))>>10)
#define SB2_PFUNC_MISC1_get_gpio_2_e2(data)                                          ((0x00000400&(data))>>10)
#define SB2_PFUNC_MISC1_gpio_2_pud_en_shift                                          (9)
#define SB2_PFUNC_MISC1_gpio_2_pud_en_mask                                           (0x00000200)
#define SB2_PFUNC_MISC1_gpio_2_pud_en(data)                                          (0x00000200&((data)<<9))
#define SB2_PFUNC_MISC1_gpio_2_pud_en_src(data)                                      ((0x00000200&(data))>>9)
#define SB2_PFUNC_MISC1_get_gpio_2_pud_en(data)                                      ((0x00000200&(data))>>9)
#define SB2_PFUNC_MISC1_gpio_2_pud_sel_shift                                         (8)
#define SB2_PFUNC_MISC1_gpio_2_pud_sel_mask                                          (0x00000100)
#define SB2_PFUNC_MISC1_gpio_2_pud_sel(data)                                         (0x00000100&((data)<<8))
#define SB2_PFUNC_MISC1_gpio_2_pud_sel_src(data)                                     ((0x00000100&(data))>>8)
#define SB2_PFUNC_MISC1_get_gpio_2_pud_sel(data)                                     ((0x00000100&(data))>>8)
#define SB2_PFUNC_MISC1_gpio_1_smt_shift                                             (7)
#define SB2_PFUNC_MISC1_gpio_1_smt_mask                                              (0x00000080)
#define SB2_PFUNC_MISC1_gpio_1_smt(data)                                             (0x00000080&((data)<<7))
#define SB2_PFUNC_MISC1_gpio_1_smt_src(data)                                         ((0x00000080&(data))>>7)
#define SB2_PFUNC_MISC1_get_gpio_1_smt(data)                                         ((0x00000080&(data))>>7)
#define SB2_PFUNC_MISC1_gpio_1_e2_shift                                              (6)
#define SB2_PFUNC_MISC1_gpio_1_e2_mask                                               (0x00000040)
#define SB2_PFUNC_MISC1_gpio_1_e2(data)                                              (0x00000040&((data)<<6))
#define SB2_PFUNC_MISC1_gpio_1_e2_src(data)                                          ((0x00000040&(data))>>6)
#define SB2_PFUNC_MISC1_get_gpio_1_e2(data)                                          ((0x00000040&(data))>>6)
#define SB2_PFUNC_MISC1_gpio_1_pud_en_shift                                          (5)
#define SB2_PFUNC_MISC1_gpio_1_pud_en_mask                                           (0x00000020)
#define SB2_PFUNC_MISC1_gpio_1_pud_en(data)                                          (0x00000020&((data)<<5))
#define SB2_PFUNC_MISC1_gpio_1_pud_en_src(data)                                      ((0x00000020&(data))>>5)
#define SB2_PFUNC_MISC1_get_gpio_1_pud_en(data)                                      ((0x00000020&(data))>>5)
#define SB2_PFUNC_MISC1_gpio_1_pud_sel_shift                                         (4)
#define SB2_PFUNC_MISC1_gpio_1_pud_sel_mask                                          (0x00000010)
#define SB2_PFUNC_MISC1_gpio_1_pud_sel(data)                                         (0x00000010&((data)<<4))
#define SB2_PFUNC_MISC1_gpio_1_pud_sel_src(data)                                     ((0x00000010&(data))>>4)
#define SB2_PFUNC_MISC1_get_gpio_1_pud_sel(data)                                     ((0x00000010&(data))>>4)
#define SB2_PFUNC_MISC1_gpio_0_smt_shift                                             (3)
#define SB2_PFUNC_MISC1_gpio_0_smt_mask                                              (0x00000008)
#define SB2_PFUNC_MISC1_gpio_0_smt(data)                                             (0x00000008&((data)<<3))
#define SB2_PFUNC_MISC1_gpio_0_smt_src(data)                                         ((0x00000008&(data))>>3)
#define SB2_PFUNC_MISC1_get_gpio_0_smt(data)                                         ((0x00000008&(data))>>3)
#define SB2_PFUNC_MISC1_gpio_0_e2_shift                                              (2)
#define SB2_PFUNC_MISC1_gpio_0_e2_mask                                               (0x00000004)
#define SB2_PFUNC_MISC1_gpio_0_e2(data)                                              (0x00000004&((data)<<2))
#define SB2_PFUNC_MISC1_gpio_0_e2_src(data)                                          ((0x00000004&(data))>>2)
#define SB2_PFUNC_MISC1_get_gpio_0_e2(data)                                          ((0x00000004&(data))>>2)
#define SB2_PFUNC_MISC1_gpio_0_pud_en_shift                                          (1)
#define SB2_PFUNC_MISC1_gpio_0_pud_en_mask                                           (0x00000002)
#define SB2_PFUNC_MISC1_gpio_0_pud_en(data)                                          (0x00000002&((data)<<1))
#define SB2_PFUNC_MISC1_gpio_0_pud_en_src(data)                                      ((0x00000002&(data))>>1)
#define SB2_PFUNC_MISC1_get_gpio_0_pud_en(data)                                      ((0x00000002&(data))>>1)
#define SB2_PFUNC_MISC1_gpio_0_pud_sel_shift                                         (0)
#define SB2_PFUNC_MISC1_gpio_0_pud_sel_mask                                          (0x00000001)
#define SB2_PFUNC_MISC1_gpio_0_pud_sel(data)                                         (0x00000001&((data)<<0))
#define SB2_PFUNC_MISC1_gpio_0_pud_sel_src(data)                                     ((0x00000001&(data))>>0)
#define SB2_PFUNC_MISC1_get_gpio_0_pud_sel(data)                                     ((0x00000001&(data))>>0)


#define SB2_PFUNC_MISC2                                                              0x9801A938
#define SB2_PFUNC_MISC2_reg_addr                                                     "0x9801A938"
#define SB2_PFUNC_MISC2_reg                                                          0x9801A938
#define set_SB2_PFUNC_MISC2_reg(data)   (*((volatile unsigned int*) SB2_PFUNC_MISC2_reg)=data)
#define get_SB2_PFUNC_MISC2_reg   (*((volatile unsigned int*) SB2_PFUNC_MISC2_reg))
#define SB2_PFUNC_MISC2_inst_adr                                                     "0x004E"
#define SB2_PFUNC_MISC2_inst                                                         0x004E
#define SB2_PFUNC_MISC2_sensor_cko1_smt_shift                                        (31)
#define SB2_PFUNC_MISC2_sensor_cko1_smt_mask                                         (0x80000000)
#define SB2_PFUNC_MISC2_sensor_cko1_smt(data)                                        (0x80000000&((data)<<31))
#define SB2_PFUNC_MISC2_sensor_cko1_smt_src(data)                                    ((0x80000000&(data))>>31)
#define SB2_PFUNC_MISC2_get_sensor_cko1_smt(data)                                    ((0x80000000&(data))>>31)
#define SB2_PFUNC_MISC2_sensor_cko1_e2_shift                                         (30)
#define SB2_PFUNC_MISC2_sensor_cko1_e2_mask                                          (0x40000000)
#define SB2_PFUNC_MISC2_sensor_cko1_e2(data)                                         (0x40000000&((data)<<30))
#define SB2_PFUNC_MISC2_sensor_cko1_e2_src(data)                                     ((0x40000000&(data))>>30)
#define SB2_PFUNC_MISC2_get_sensor_cko1_e2(data)                                     ((0x40000000&(data))>>30)
#define SB2_PFUNC_MISC2_sensor_cko1_pud_en_shift                                     (29)
#define SB2_PFUNC_MISC2_sensor_cko1_pud_en_mask                                      (0x20000000)
#define SB2_PFUNC_MISC2_sensor_cko1_pud_en(data)                                     (0x20000000&((data)<<29))
#define SB2_PFUNC_MISC2_sensor_cko1_pud_en_src(data)                                 ((0x20000000&(data))>>29)
#define SB2_PFUNC_MISC2_get_sensor_cko1_pud_en(data)                                 ((0x20000000&(data))>>29)
#define SB2_PFUNC_MISC2_sensor_cko1_pud_sel_shift                                    (28)
#define SB2_PFUNC_MISC2_sensor_cko1_pud_sel_mask                                     (0x10000000)
#define SB2_PFUNC_MISC2_sensor_cko1_pud_sel(data)                                    (0x10000000&((data)<<28))
#define SB2_PFUNC_MISC2_sensor_cko1_pud_sel_src(data)                                ((0x10000000&(data))>>28)
#define SB2_PFUNC_MISC2_get_sensor_cko1_pud_sel(data)                                ((0x10000000&(data))>>28)
#define SB2_PFUNC_MISC2_sensor_cko0_smt_shift                                        (27)
#define SB2_PFUNC_MISC2_sensor_cko0_smt_mask                                         (0x08000000)
#define SB2_PFUNC_MISC2_sensor_cko0_smt(data)                                        (0x08000000&((data)<<27))
#define SB2_PFUNC_MISC2_sensor_cko0_smt_src(data)                                    ((0x08000000&(data))>>27)
#define SB2_PFUNC_MISC2_get_sensor_cko0_smt(data)                                    ((0x08000000&(data))>>27)
#define SB2_PFUNC_MISC2_sensor_cko0_e2_shift                                         (26)
#define SB2_PFUNC_MISC2_sensor_cko0_e2_mask                                          (0x04000000)
#define SB2_PFUNC_MISC2_sensor_cko0_e2(data)                                         (0x04000000&((data)<<26))
#define SB2_PFUNC_MISC2_sensor_cko0_e2_src(data)                                     ((0x04000000&(data))>>26)
#define SB2_PFUNC_MISC2_get_sensor_cko0_e2(data)                                     ((0x04000000&(data))>>26)
#define SB2_PFUNC_MISC2_sensor_cko0_pud_en_shift                                     (25)
#define SB2_PFUNC_MISC2_sensor_cko0_pud_en_mask                                      (0x02000000)
#define SB2_PFUNC_MISC2_sensor_cko0_pud_en(data)                                     (0x02000000&((data)<<25))
#define SB2_PFUNC_MISC2_sensor_cko0_pud_en_src(data)                                 ((0x02000000&(data))>>25)
#define SB2_PFUNC_MISC2_get_sensor_cko0_pud_en(data)                                 ((0x02000000&(data))>>25)
#define SB2_PFUNC_MISC2_sensor_cko0_pud_sel_shift                                    (24)
#define SB2_PFUNC_MISC2_sensor_cko0_pud_sel_mask                                     (0x01000000)
#define SB2_PFUNC_MISC2_sensor_cko0_pud_sel(data)                                    (0x01000000&((data)<<24))
#define SB2_PFUNC_MISC2_sensor_cko0_pud_sel_src(data)                                ((0x01000000&(data))>>24)
#define SB2_PFUNC_MISC2_get_sensor_cko0_pud_sel(data)                                ((0x01000000&(data))>>24)
#define SB2_PFUNC_MISC2_sensor_rst_smt_shift                                         (23)
#define SB2_PFUNC_MISC2_sensor_rst_smt_mask                                          (0x00800000)
#define SB2_PFUNC_MISC2_sensor_rst_smt(data)                                         (0x00800000&((data)<<23))
#define SB2_PFUNC_MISC2_sensor_rst_smt_src(data)                                     ((0x00800000&(data))>>23)
#define SB2_PFUNC_MISC2_get_sensor_rst_smt(data)                                     ((0x00800000&(data))>>23)
#define SB2_PFUNC_MISC2_sensor_rst_e2_shift                                          (22)
#define SB2_PFUNC_MISC2_sensor_rst_e2_mask                                           (0x00400000)
#define SB2_PFUNC_MISC2_sensor_rst_e2(data)                                          (0x00400000&((data)<<22))
#define SB2_PFUNC_MISC2_sensor_rst_e2_src(data)                                      ((0x00400000&(data))>>22)
#define SB2_PFUNC_MISC2_get_sensor_rst_e2(data)                                      ((0x00400000&(data))>>22)
#define SB2_PFUNC_MISC2_sensor_rst_pud_en_shift                                      (21)
#define SB2_PFUNC_MISC2_sensor_rst_pud_en_mask                                       (0x00200000)
#define SB2_PFUNC_MISC2_sensor_rst_pud_en(data)                                      (0x00200000&((data)<<21))
#define SB2_PFUNC_MISC2_sensor_rst_pud_en_src(data)                                  ((0x00200000&(data))>>21)
#define SB2_PFUNC_MISC2_get_sensor_rst_pud_en(data)                                  ((0x00200000&(data))>>21)
#define SB2_PFUNC_MISC2_sensor_rst_pud_sel_shift                                     (20)
#define SB2_PFUNC_MISC2_sensor_rst_pud_sel_mask                                      (0x00100000)
#define SB2_PFUNC_MISC2_sensor_rst_pud_sel(data)                                     (0x00100000&((data)<<20))
#define SB2_PFUNC_MISC2_sensor_rst_pud_sel_src(data)                                 ((0x00100000&(data))>>20)
#define SB2_PFUNC_MISC2_get_sensor_rst_pud_sel(data)                                 ((0x00100000&(data))>>20)
#define SB2_PFUNC_MISC2_sensor_stb1_smt_shift                                        (19)
#define SB2_PFUNC_MISC2_sensor_stb1_smt_mask                                         (0x00080000)
#define SB2_PFUNC_MISC2_sensor_stb1_smt(data)                                        (0x00080000&((data)<<19))
#define SB2_PFUNC_MISC2_sensor_stb1_smt_src(data)                                    ((0x00080000&(data))>>19)
#define SB2_PFUNC_MISC2_get_sensor_stb1_smt(data)                                    ((0x00080000&(data))>>19)
#define SB2_PFUNC_MISC2_sensor_stb1_e2_shift                                         (18)
#define SB2_PFUNC_MISC2_sensor_stb1_e2_mask                                          (0x00040000)
#define SB2_PFUNC_MISC2_sensor_stb1_e2(data)                                         (0x00040000&((data)<<18))
#define SB2_PFUNC_MISC2_sensor_stb1_e2_src(data)                                     ((0x00040000&(data))>>18)
#define SB2_PFUNC_MISC2_get_sensor_stb1_e2(data)                                     ((0x00040000&(data))>>18)
#define SB2_PFUNC_MISC2_sensor_stb1_pud_en_shift                                     (17)
#define SB2_PFUNC_MISC2_sensor_stb1_pud_en_mask                                      (0x00020000)
#define SB2_PFUNC_MISC2_sensor_stb1_pud_en(data)                                     (0x00020000&((data)<<17))
#define SB2_PFUNC_MISC2_sensor_stb1_pud_en_src(data)                                 ((0x00020000&(data))>>17)
#define SB2_PFUNC_MISC2_get_sensor_stb1_pud_en(data)                                 ((0x00020000&(data))>>17)
#define SB2_PFUNC_MISC2_sensor_stb1_pud_sel_shift                                    (16)
#define SB2_PFUNC_MISC2_sensor_stb1_pud_sel_mask                                     (0x00010000)
#define SB2_PFUNC_MISC2_sensor_stb1_pud_sel(data)                                    (0x00010000&((data)<<16))
#define SB2_PFUNC_MISC2_sensor_stb1_pud_sel_src(data)                                ((0x00010000&(data))>>16)
#define SB2_PFUNC_MISC2_get_sensor_stb1_pud_sel(data)                                ((0x00010000&(data))>>16)
#define SB2_PFUNC_MISC2_sensor_stb0_smt_shift                                        (15)
#define SB2_PFUNC_MISC2_sensor_stb0_smt_mask                                         (0x00008000)
#define SB2_PFUNC_MISC2_sensor_stb0_smt(data)                                        (0x00008000&((data)<<15))
#define SB2_PFUNC_MISC2_sensor_stb0_smt_src(data)                                    ((0x00008000&(data))>>15)
#define SB2_PFUNC_MISC2_get_sensor_stb0_smt(data)                                    ((0x00008000&(data))>>15)
#define SB2_PFUNC_MISC2_sensor_stb0_e2_shift                                         (14)
#define SB2_PFUNC_MISC2_sensor_stb0_e2_mask                                          (0x00004000)
#define SB2_PFUNC_MISC2_sensor_stb0_e2(data)                                         (0x00004000&((data)<<14))
#define SB2_PFUNC_MISC2_sensor_stb0_e2_src(data)                                     ((0x00004000&(data))>>14)
#define SB2_PFUNC_MISC2_get_sensor_stb0_e2(data)                                     ((0x00004000&(data))>>14)
#define SB2_PFUNC_MISC2_sensor_stb0_pud_en_shift                                     (13)
#define SB2_PFUNC_MISC2_sensor_stb0_pud_en_mask                                      (0x00002000)
#define SB2_PFUNC_MISC2_sensor_stb0_pud_en(data)                                     (0x00002000&((data)<<13))
#define SB2_PFUNC_MISC2_sensor_stb0_pud_en_src(data)                                 ((0x00002000&(data))>>13)
#define SB2_PFUNC_MISC2_get_sensor_stb0_pud_en(data)                                 ((0x00002000&(data))>>13)
#define SB2_PFUNC_MISC2_sensor_stb0_pud_sel_shift                                    (12)
#define SB2_PFUNC_MISC2_sensor_stb0_pud_sel_mask                                     (0x00001000)
#define SB2_PFUNC_MISC2_sensor_stb0_pud_sel(data)                                    (0x00001000&((data)<<12))
#define SB2_PFUNC_MISC2_sensor_stb0_pud_sel_src(data)                                ((0x00001000&(data))>>12)
#define SB2_PFUNC_MISC2_get_sensor_stb0_pud_sel(data)                                ((0x00001000&(data))>>12)
#define SB2_PFUNC_MISC2_usb_id_smt_shift                                             (11)
#define SB2_PFUNC_MISC2_usb_id_smt_mask                                              (0x00000800)
#define SB2_PFUNC_MISC2_usb_id_smt(data)                                             (0x00000800&((data)<<11))
#define SB2_PFUNC_MISC2_usb_id_smt_src(data)                                         ((0x00000800&(data))>>11)
#define SB2_PFUNC_MISC2_get_usb_id_smt(data)                                         ((0x00000800&(data))>>11)
#define SB2_PFUNC_MISC2_usb_id_e2_shift                                              (10)
#define SB2_PFUNC_MISC2_usb_id_e2_mask                                               (0x00000400)
#define SB2_PFUNC_MISC2_usb_id_e2(data)                                              (0x00000400&((data)<<10))
#define SB2_PFUNC_MISC2_usb_id_e2_src(data)                                          ((0x00000400&(data))>>10)
#define SB2_PFUNC_MISC2_get_usb_id_e2(data)                                          ((0x00000400&(data))>>10)
#define SB2_PFUNC_MISC2_usb_id_pud_en_shift                                          (9)
#define SB2_PFUNC_MISC2_usb_id_pud_en_mask                                           (0x00000200)
#define SB2_PFUNC_MISC2_usb_id_pud_en(data)                                          (0x00000200&((data)<<9))
#define SB2_PFUNC_MISC2_usb_id_pud_en_src(data)                                      ((0x00000200&(data))>>9)
#define SB2_PFUNC_MISC2_get_usb_id_pud_en(data)                                      ((0x00000200&(data))>>9)
#define SB2_PFUNC_MISC2_usb_id_pud_sel_shift                                         (8)
#define SB2_PFUNC_MISC2_usb_id_pud_sel_mask                                          (0x00000100)
#define SB2_PFUNC_MISC2_usb_id_pud_sel(data)                                         (0x00000100&((data)<<8))
#define SB2_PFUNC_MISC2_usb_id_pud_sel_src(data)                                     ((0x00000100&(data))>>8)
#define SB2_PFUNC_MISC2_get_usb_id_pud_sel(data)                                     ((0x00000100&(data))>>8)
#define SB2_PFUNC_MISC2_gpio_9_smt_shift                                             (7)
#define SB2_PFUNC_MISC2_gpio_9_smt_mask                                              (0x00000080)
#define SB2_PFUNC_MISC2_gpio_9_smt(data)                                             (0x00000080&((data)<<7))
#define SB2_PFUNC_MISC2_gpio_9_smt_src(data)                                         ((0x00000080&(data))>>7)
#define SB2_PFUNC_MISC2_get_gpio_9_smt(data)                                         ((0x00000080&(data))>>7)
#define SB2_PFUNC_MISC2_gpio_9_e2_shift                                              (6)
#define SB2_PFUNC_MISC2_gpio_9_e2_mask                                               (0x00000040)
#define SB2_PFUNC_MISC2_gpio_9_e2(data)                                              (0x00000040&((data)<<6))
#define SB2_PFUNC_MISC2_gpio_9_e2_src(data)                                          ((0x00000040&(data))>>6)
#define SB2_PFUNC_MISC2_get_gpio_9_e2(data)                                          ((0x00000040&(data))>>6)
#define SB2_PFUNC_MISC2_gpio_9_pud_en_shift                                          (5)
#define SB2_PFUNC_MISC2_gpio_9_pud_en_mask                                           (0x00000020)
#define SB2_PFUNC_MISC2_gpio_9_pud_en(data)                                          (0x00000020&((data)<<5))
#define SB2_PFUNC_MISC2_gpio_9_pud_en_src(data)                                      ((0x00000020&(data))>>5)
#define SB2_PFUNC_MISC2_get_gpio_9_pud_en(data)                                      ((0x00000020&(data))>>5)
#define SB2_PFUNC_MISC2_gpio_9_pud_sel_shift                                         (4)
#define SB2_PFUNC_MISC2_gpio_9_pud_sel_mask                                          (0x00000010)
#define SB2_PFUNC_MISC2_gpio_9_pud_sel(data)                                         (0x00000010&((data)<<4))
#define SB2_PFUNC_MISC2_gpio_9_pud_sel_src(data)                                     ((0x00000010&(data))>>4)
#define SB2_PFUNC_MISC2_get_gpio_9_pud_sel(data)                                     ((0x00000010&(data))>>4)
#define SB2_PFUNC_MISC2_gpio_8_smt_shift                                             (3)
#define SB2_PFUNC_MISC2_gpio_8_smt_mask                                              (0x00000008)
#define SB2_PFUNC_MISC2_gpio_8_smt(data)                                             (0x00000008&((data)<<3))
#define SB2_PFUNC_MISC2_gpio_8_smt_src(data)                                         ((0x00000008&(data))>>3)
#define SB2_PFUNC_MISC2_get_gpio_8_smt(data)                                         ((0x00000008&(data))>>3)
#define SB2_PFUNC_MISC2_gpio_8_e2_shift                                              (2)
#define SB2_PFUNC_MISC2_gpio_8_e2_mask                                               (0x00000004)
#define SB2_PFUNC_MISC2_gpio_8_e2(data)                                              (0x00000004&((data)<<2))
#define SB2_PFUNC_MISC2_gpio_8_e2_src(data)                                          ((0x00000004&(data))>>2)
#define SB2_PFUNC_MISC2_get_gpio_8_e2(data)                                          ((0x00000004&(data))>>2)
#define SB2_PFUNC_MISC2_gpio_8_pud_en_shift                                          (1)
#define SB2_PFUNC_MISC2_gpio_8_pud_en_mask                                           (0x00000002)
#define SB2_PFUNC_MISC2_gpio_8_pud_en(data)                                          (0x00000002&((data)<<1))
#define SB2_PFUNC_MISC2_gpio_8_pud_en_src(data)                                      ((0x00000002&(data))>>1)
#define SB2_PFUNC_MISC2_get_gpio_8_pud_en(data)                                      ((0x00000002&(data))>>1)
#define SB2_PFUNC_MISC2_gpio_8_pud_sel_shift                                         (0)
#define SB2_PFUNC_MISC2_gpio_8_pud_sel_mask                                          (0x00000001)
#define SB2_PFUNC_MISC2_gpio_8_pud_sel(data)                                         (0x00000001&((data)<<0))
#define SB2_PFUNC_MISC2_gpio_8_pud_sel_src(data)                                     ((0x00000001&(data))>>0)
#define SB2_PFUNC_MISC2_get_gpio_8_pud_sel(data)                                     ((0x00000001&(data))>>0)


#define SB2_PFUNC_MISC3                                                              0x9801A93C
#define SB2_PFUNC_MISC3_reg_addr                                                     "0x9801A93C"
#define SB2_PFUNC_MISC3_reg                                                          0x9801A93C
#define set_SB2_PFUNC_MISC3_reg(data)   (*((volatile unsigned int*) SB2_PFUNC_MISC3_reg)=data)
#define get_SB2_PFUNC_MISC3_reg   (*((volatile unsigned int*) SB2_PFUNC_MISC3_reg))
#define SB2_PFUNC_MISC3_inst_adr                                                     "0x004F"
#define SB2_PFUNC_MISC3_inst                                                         0x004F
#define SB2_PFUNC_MISC3_boption4_smt_shift                                           (26)
#define SB2_PFUNC_MISC3_boption4_smt_mask                                            (0x04000000)
#define SB2_PFUNC_MISC3_boption4_smt(data)                                           (0x04000000&((data)<<26))
#define SB2_PFUNC_MISC3_boption4_smt_src(data)                                       ((0x04000000&(data))>>26)
#define SB2_PFUNC_MISC3_get_boption4_smt(data)                                       ((0x04000000&(data))>>26)
#define SB2_PFUNC_MISC3_boption4_pud_en_shift                                        (25)
#define SB2_PFUNC_MISC3_boption4_pud_en_mask                                         (0x02000000)
#define SB2_PFUNC_MISC3_boption4_pud_en(data)                                        (0x02000000&((data)<<25))
#define SB2_PFUNC_MISC3_boption4_pud_en_src(data)                                    ((0x02000000&(data))>>25)
#define SB2_PFUNC_MISC3_get_boption4_pud_en(data)                                    ((0x02000000&(data))>>25)
#define SB2_PFUNC_MISC3_boption4_pud_sel_shift                                       (24)
#define SB2_PFUNC_MISC3_boption4_pud_sel_mask                                        (0x01000000)
#define SB2_PFUNC_MISC3_boption4_pud_sel(data)                                       (0x01000000&((data)<<24))
#define SB2_PFUNC_MISC3_boption4_pud_sel_src(data)                                   ((0x01000000&(data))>>24)
#define SB2_PFUNC_MISC3_get_boption4_pud_sel(data)                                   ((0x01000000&(data))>>24)
#define SB2_PFUNC_MISC3_boption3_smt_shift                                           (23)
#define SB2_PFUNC_MISC3_boption3_smt_mask                                            (0x00800000)
#define SB2_PFUNC_MISC3_boption3_smt(data)                                           (0x00800000&((data)<<23))
#define SB2_PFUNC_MISC3_boption3_smt_src(data)                                       ((0x00800000&(data))>>23)
#define SB2_PFUNC_MISC3_get_boption3_smt(data)                                       ((0x00800000&(data))>>23)
#define SB2_PFUNC_MISC3_boption3_pud_en_shift                                        (22)
#define SB2_PFUNC_MISC3_boption3_pud_en_mask                                         (0x00400000)
#define SB2_PFUNC_MISC3_boption3_pud_en(data)                                        (0x00400000&((data)<<22))
#define SB2_PFUNC_MISC3_boption3_pud_en_src(data)                                    ((0x00400000&(data))>>22)
#define SB2_PFUNC_MISC3_get_boption3_pud_en(data)                                    ((0x00400000&(data))>>22)
#define SB2_PFUNC_MISC3_boption3_pud_sel_shift                                       (21)
#define SB2_PFUNC_MISC3_boption3_pud_sel_mask                                        (0x00200000)
#define SB2_PFUNC_MISC3_boption3_pud_sel(data)                                       (0x00200000&((data)<<21))
#define SB2_PFUNC_MISC3_boption3_pud_sel_src(data)                                   ((0x00200000&(data))>>21)
#define SB2_PFUNC_MISC3_get_boption3_pud_sel(data)                                   ((0x00200000&(data))>>21)
#define SB2_PFUNC_MISC3_boption1_smt_shift                                           (20)
#define SB2_PFUNC_MISC3_boption1_smt_mask                                            (0x00100000)
#define SB2_PFUNC_MISC3_boption1_smt(data)                                           (0x00100000&((data)<<20))
#define SB2_PFUNC_MISC3_boption1_smt_src(data)                                       ((0x00100000&(data))>>20)
#define SB2_PFUNC_MISC3_get_boption1_smt(data)                                       ((0x00100000&(data))>>20)
#define SB2_PFUNC_MISC3_boption1_pud_en_shift                                        (19)
#define SB2_PFUNC_MISC3_boption1_pud_en_mask                                         (0x00080000)
#define SB2_PFUNC_MISC3_boption1_pud_en(data)                                        (0x00080000&((data)<<19))
#define SB2_PFUNC_MISC3_boption1_pud_en_src(data)                                    ((0x00080000&(data))>>19)
#define SB2_PFUNC_MISC3_get_boption1_pud_en(data)                                    ((0x00080000&(data))>>19)
#define SB2_PFUNC_MISC3_boption1_pud_sel_shift                                       (18)
#define SB2_PFUNC_MISC3_boption1_pud_sel_mask                                        (0x00040000)
#define SB2_PFUNC_MISC3_boption1_pud_sel(data)                                       (0x00040000&((data)<<18))
#define SB2_PFUNC_MISC3_boption1_pud_sel_src(data)                                   ((0x00040000&(data))>>18)
#define SB2_PFUNC_MISC3_get_boption1_pud_sel(data)                                   ((0x00040000&(data))>>18)
#define SB2_PFUNC_MISC3_boption0_smt_shift                                           (17)
#define SB2_PFUNC_MISC3_boption0_smt_mask                                            (0x00020000)
#define SB2_PFUNC_MISC3_boption0_smt(data)                                           (0x00020000&((data)<<17))
#define SB2_PFUNC_MISC3_boption0_smt_src(data)                                       ((0x00020000&(data))>>17)
#define SB2_PFUNC_MISC3_get_boption0_smt(data)                                       ((0x00020000&(data))>>17)
#define SB2_PFUNC_MISC3_boption0_pud_en_shift                                        (16)
#define SB2_PFUNC_MISC3_boption0_pud_en_mask                                         (0x00010000)
#define SB2_PFUNC_MISC3_boption0_pud_en(data)                                        (0x00010000&((data)<<16))
#define SB2_PFUNC_MISC3_boption0_pud_en_src(data)                                    ((0x00010000&(data))>>16)
#define SB2_PFUNC_MISC3_get_boption0_pud_en(data)                                    ((0x00010000&(data))>>16)
#define SB2_PFUNC_MISC3_boption0_pud_sel_shift                                       (15)
#define SB2_PFUNC_MISC3_boption0_pud_sel_mask                                        (0x00008000)
#define SB2_PFUNC_MISC3_boption0_pud_sel(data)                                       (0x00008000&((data)<<15))
#define SB2_PFUNC_MISC3_boption0_pud_sel_src(data)                                   ((0x00008000&(data))>>15)
#define SB2_PFUNC_MISC3_get_boption0_pud_sel(data)                                   ((0x00008000&(data))>>15)
#define SB2_PFUNC_MISC3_boption9_smt_shift                                           (14)
#define SB2_PFUNC_MISC3_boption9_smt_mask                                            (0x00004000)
#define SB2_PFUNC_MISC3_boption9_smt(data)                                           (0x00004000&((data)<<14))
#define SB2_PFUNC_MISC3_boption9_smt_src(data)                                       ((0x00004000&(data))>>14)
#define SB2_PFUNC_MISC3_get_boption9_smt(data)                                       ((0x00004000&(data))>>14)
#define SB2_PFUNC_MISC3_boption9_pud_en_shift                                        (13)
#define SB2_PFUNC_MISC3_boption9_pud_en_mask                                         (0x00002000)
#define SB2_PFUNC_MISC3_boption9_pud_en(data)                                        (0x00002000&((data)<<13))
#define SB2_PFUNC_MISC3_boption9_pud_en_src(data)                                    ((0x00002000&(data))>>13)
#define SB2_PFUNC_MISC3_get_boption9_pud_en(data)                                    ((0x00002000&(data))>>13)
#define SB2_PFUNC_MISC3_boption9_pud_sel_shift                                       (12)
#define SB2_PFUNC_MISC3_boption9_pud_sel_mask                                        (0x00001000)
#define SB2_PFUNC_MISC3_boption9_pud_sel(data)                                       (0x00001000&((data)<<12))
#define SB2_PFUNC_MISC3_boption9_pud_sel_src(data)                                   ((0x00001000&(data))>>12)
#define SB2_PFUNC_MISC3_get_boption9_pud_sel(data)                                   ((0x00001000&(data))>>12)
#define SB2_PFUNC_MISC3_boption8_smt_shift                                           (11)
#define SB2_PFUNC_MISC3_boption8_smt_mask                                            (0x00000800)
#define SB2_PFUNC_MISC3_boption8_smt(data)                                           (0x00000800&((data)<<11))
#define SB2_PFUNC_MISC3_boption8_smt_src(data)                                       ((0x00000800&(data))>>11)
#define SB2_PFUNC_MISC3_get_boption8_smt(data)                                       ((0x00000800&(data))>>11)
#define SB2_PFUNC_MISC3_boption8_pud_en_shift                                        (10)
#define SB2_PFUNC_MISC3_boption8_pud_en_mask                                         (0x00000400)
#define SB2_PFUNC_MISC3_boption8_pud_en(data)                                        (0x00000400&((data)<<10))
#define SB2_PFUNC_MISC3_boption8_pud_en_src(data)                                    ((0x00000400&(data))>>10)
#define SB2_PFUNC_MISC3_get_boption8_pud_en(data)                                    ((0x00000400&(data))>>10)
#define SB2_PFUNC_MISC3_boption8_pud_sel_shift                                       (9)
#define SB2_PFUNC_MISC3_boption8_pud_sel_mask                                        (0x00000200)
#define SB2_PFUNC_MISC3_boption8_pud_sel(data)                                       (0x00000200&((data)<<9))
#define SB2_PFUNC_MISC3_boption8_pud_sel_src(data)                                   ((0x00000200&(data))>>9)
#define SB2_PFUNC_MISC3_get_boption8_pud_sel(data)                                   ((0x00000200&(data))>>9)
#define SB2_PFUNC_MISC3_boption7_smt_shift                                           (8)
#define SB2_PFUNC_MISC3_boption7_smt_mask                                            (0x00000100)
#define SB2_PFUNC_MISC3_boption7_smt(data)                                           (0x00000100&((data)<<8))
#define SB2_PFUNC_MISC3_boption7_smt_src(data)                                       ((0x00000100&(data))>>8)
#define SB2_PFUNC_MISC3_get_boption7_smt(data)                                       ((0x00000100&(data))>>8)
#define SB2_PFUNC_MISC3_boption7_pud_en_shift                                        (7)
#define SB2_PFUNC_MISC3_boption7_pud_en_mask                                         (0x00000080)
#define SB2_PFUNC_MISC3_boption7_pud_en(data)                                        (0x00000080&((data)<<7))
#define SB2_PFUNC_MISC3_boption7_pud_en_src(data)                                    ((0x00000080&(data))>>7)
#define SB2_PFUNC_MISC3_get_boption7_pud_en(data)                                    ((0x00000080&(data))>>7)
#define SB2_PFUNC_MISC3_boption7_pud_sel_shift                                       (6)
#define SB2_PFUNC_MISC3_boption7_pud_sel_mask                                        (0x00000040)
#define SB2_PFUNC_MISC3_boption7_pud_sel(data)                                       (0x00000040&((data)<<6))
#define SB2_PFUNC_MISC3_boption7_pud_sel_src(data)                                   ((0x00000040&(data))>>6)
#define SB2_PFUNC_MISC3_get_boption7_pud_sel(data)                                   ((0x00000040&(data))>>6)
#define SB2_PFUNC_MISC3_boption6_smt_shift                                           (5)
#define SB2_PFUNC_MISC3_boption6_smt_mask                                            (0x00000020)
#define SB2_PFUNC_MISC3_boption6_smt(data)                                           (0x00000020&((data)<<5))
#define SB2_PFUNC_MISC3_boption6_smt_src(data)                                       ((0x00000020&(data))>>5)
#define SB2_PFUNC_MISC3_get_boption6_smt(data)                                       ((0x00000020&(data))>>5)
#define SB2_PFUNC_MISC3_boption6_pud_en_shift                                        (4)
#define SB2_PFUNC_MISC3_boption6_pud_en_mask                                         (0x00000010)
#define SB2_PFUNC_MISC3_boption6_pud_en(data)                                        (0x00000010&((data)<<4))
#define SB2_PFUNC_MISC3_boption6_pud_en_src(data)                                    ((0x00000010&(data))>>4)
#define SB2_PFUNC_MISC3_get_boption6_pud_en(data)                                    ((0x00000010&(data))>>4)
#define SB2_PFUNC_MISC3_boption6_pud_sel_shift                                       (3)
#define SB2_PFUNC_MISC3_boption6_pud_sel_mask                                        (0x00000008)
#define SB2_PFUNC_MISC3_boption6_pud_sel(data)                                       (0x00000008&((data)<<3))
#define SB2_PFUNC_MISC3_boption6_pud_sel_src(data)                                   ((0x00000008&(data))>>3)
#define SB2_PFUNC_MISC3_get_boption6_pud_sel(data)                                   ((0x00000008&(data))>>3)
#define SB2_PFUNC_MISC3_boption5_smt_shift                                           (2)
#define SB2_PFUNC_MISC3_boption5_smt_mask                                            (0x00000004)
#define SB2_PFUNC_MISC3_boption5_smt(data)                                           (0x00000004&((data)<<2))
#define SB2_PFUNC_MISC3_boption5_smt_src(data)                                       ((0x00000004&(data))>>2)
#define SB2_PFUNC_MISC3_get_boption5_smt(data)                                       ((0x00000004&(data))>>2)
#define SB2_PFUNC_MISC3_boption5_pud_en_shift                                        (1)
#define SB2_PFUNC_MISC3_boption5_pud_en_mask                                         (0x00000002)
#define SB2_PFUNC_MISC3_boption5_pud_en(data)                                        (0x00000002&((data)<<1))
#define SB2_PFUNC_MISC3_boption5_pud_en_src(data)                                    ((0x00000002&(data))>>1)
#define SB2_PFUNC_MISC3_get_boption5_pud_en(data)                                    ((0x00000002&(data))>>1)
#define SB2_PFUNC_MISC3_boption5_pud_sel_shift                                       (0)
#define SB2_PFUNC_MISC3_boption5_pud_sel_mask                                        (0x00000001)
#define SB2_PFUNC_MISC3_boption5_pud_sel(data)                                       (0x00000001&((data)<<0))
#define SB2_PFUNC_MISC3_boption5_pud_sel_src(data)                                   ((0x00000001&(data))>>0)
#define SB2_PFUNC_MISC3_get_boption5_pud_sel(data)                                   ((0x00000001&(data))>>0)


//#define SB2_DEBUG                                                                    0x9801A954
//#define SB2_DEBUG_reg_addr                                                           "0x9801A954"
//#define SB2_DEBUG_reg                                                                0x9801A954
#define set_SB2_DEBUG_reg(data)   (*((volatile unsigned int*) SB2_DEBUG_reg)=data)
#define get_SB2_DEBUG_reg   (*((volatile unsigned int*) SB2_DEBUG_reg))
//#define SB2_DEBUG_inst_adr                                                           "0x0055"
//#define SB2_DEBUG_inst                                                               0x0055
#define SB2_DEBUG_main1_dbg_en_shift                                                 (31)
#define SB2_DEBUG_main1_dbg_en_mask                                                  (0x80000000)
#define SB2_DEBUG_main1_dbg_en(data)                                                 (0x80000000&((data)<<31))
#define SB2_DEBUG_main1_dbg_en_src(data)                                             ((0x80000000&(data))>>31)
#define SB2_DEBUG_get_main1_dbg_en(data)                                             ((0x80000000&(data))>>31)
#define SB2_DEBUG_main1_dbg_sel_shift                                                (24)
#define SB2_DEBUG_main1_dbg_sel_mask                                                 (0x0F000000)
#define SB2_DEBUG_main1_dbg_sel(data)                                                (0x0F000000&((data)<<24))
#define SB2_DEBUG_main1_dbg_sel_src(data)                                            ((0x0F000000&(data))>>24)
#define SB2_DEBUG_get_main1_dbg_sel(data)                                            ((0x0F000000&(data))>>24)
#define SB2_DEBUG_dbg_en_shift                                                       (14)
#define SB2_DEBUG_dbg_en_mask                                                        (0x00004000)
#define SB2_DEBUG_dbg_en(data)                                                       (0x00004000&((data)<<14))
#define SB2_DEBUG_dbg_en_src(data)                                                   ((0x00004000&(data))>>14)
#define SB2_DEBUG_get_dbg_en(data)                                                   ((0x00004000&(data))>>14)
#define SB2_DEBUG_dbg_loc_shift                                                      (12)
#define SB2_DEBUG_dbg_loc_mask                                                       (0x00003000)
#define SB2_DEBUG_dbg_loc(data)                                                      (0x00003000&((data)<<12))
#define SB2_DEBUG_dbg_loc_src(data)                                                  ((0x00003000&(data))>>12)
#define SB2_DEBUG_get_dbg_loc(data)                                                  ((0x00003000&(data))>>12)
#define SB2_DEBUG_dbg_sel0_shift                                                     (6)
#define SB2_DEBUG_dbg_sel0_mask                                                      (0x00000FC0)
#define SB2_DEBUG_dbg_sel0(data)                                                     (0x00000FC0&((data)<<6))
#define SB2_DEBUG_dbg_sel0_src(data)                                                 ((0x00000FC0&(data))>>6)
#define SB2_DEBUG_get_dbg_sel0(data)                                                 ((0x00000FC0&(data))>>6)
#define SB2_DEBUG_dbg_sel1_shift                                                     (0)
#define SB2_DEBUG_dbg_sel1_mask                                                      (0x0000003F)
#define SB2_DEBUG_dbg_sel1(data)                                                     (0x0000003F&((data)<<0))
#define SB2_DEBUG_dbg_sel1_src(data)                                                 ((0x0000003F&(data))>>0)
#define SB2_DEBUG_get_dbg_sel1(data)                                                 ((0x0000003F&(data))>>0)


#define SB2_MBIST                                                                    0x9801A958
#define SB2_MBIST_reg_addr                                                           "0x9801A958"
#define SB2_MBIST_reg                                                                0x9801A958
#define set_SB2_MBIST_reg(data)   (*((volatile unsigned int*) SB2_MBIST_reg)=data)
#define get_SB2_MBIST_reg   (*((volatile unsigned int*) SB2_MBIST_reg))
#define SB2_MBIST_inst_adr                                                           "0x0056"
#define SB2_MBIST_inst                                                               0x0056
#define SB2_MBIST_mbist_gpu_chip_top_st_shift                                        (28)
#define SB2_MBIST_mbist_gpu_chip_top_st_mask                                         (0x10000000)
#define SB2_MBIST_mbist_gpu_chip_top_st(data)                                        (0x10000000&((data)<<28))
#define SB2_MBIST_mbist_gpu_chip_top_st_src(data)                                    ((0x10000000&(data))>>28)
#define SB2_MBIST_get_mbist_gpu_chip_top_st(data)                                    ((0x10000000&(data))>>28)
#define SB2_MBIST_mbist_jpeg_st_shift                                                (27)
#define SB2_MBIST_mbist_jpeg_st_mask                                                 (0x08000000)
#define SB2_MBIST_mbist_jpeg_st(data)                                                (0x08000000&((data)<<27))
#define SB2_MBIST_mbist_jpeg_st_src(data)                                            ((0x08000000&(data))>>27)
#define SB2_MBIST_get_mbist_jpeg_st(data)                                            ((0x08000000&(data))>>27)
#define SB2_MBIST_mbist_ve1_st_shift                                                 (26)
#define SB2_MBIST_mbist_ve1_st_mask                                                  (0x04000000)
#define SB2_MBIST_mbist_ve1_st(data)                                                 (0x04000000&((data)<<26))
#define SB2_MBIST_mbist_ve1_st_src(data)                                             ((0x04000000&(data))>>26)
#define SB2_MBIST_get_mbist_ve1_st(data)                                             ((0x04000000&(data))>>26)
#define SB2_MBIST_mbist_ve2_st_shift                                                 (25)
#define SB2_MBIST_mbist_ve2_st_mask                                                  (0x02000000)
#define SB2_MBIST_mbist_ve2_st(data)                                                 (0x02000000&((data)<<25))
#define SB2_MBIST_mbist_ve2_st_src(data)                                             ((0x02000000&(data))>>25)
#define SB2_MBIST_get_mbist_ve2_st(data)                                             ((0x02000000&(data))>>25)
#define SB2_MBIST_mbist_ve3_st_shift                                                 (24)
#define SB2_MBIST_mbist_ve3_st_mask                                                  (0x01000000)
#define SB2_MBIST_mbist_ve3_st(data)                                                 (0x01000000&((data)<<24))
#define SB2_MBIST_mbist_ve3_st_src(data)                                             ((0x01000000&(data))>>24)
#define SB2_MBIST_get_mbist_ve3_st(data)                                             ((0x01000000&(data))>>24)
#define SB2_MBIST_mbist_rsa_st_shift                                                 (23)
#define SB2_MBIST_mbist_rsa_st_mask                                                  (0x00800000)
#define SB2_MBIST_mbist_rsa_st(data)                                                 (0x00800000&((data)<<23))
#define SB2_MBIST_mbist_rsa_st_src(data)                                             ((0x00800000&(data))>>23)
#define SB2_MBIST_get_mbist_rsa_st(data)                                             ((0x00800000&(data))>>23)
#define SB2_MBIST_mbist_sata_st_shift                                                (22)
#define SB2_MBIST_mbist_sata_st_mask                                                 (0x00400000)
#define SB2_MBIST_mbist_sata_st(data)                                                (0x00400000&((data)<<22))
#define SB2_MBIST_mbist_sata_st_src(data)                                            ((0x00400000&(data))>>22)
#define SB2_MBIST_get_mbist_sata_st(data)                                            ((0x00400000&(data))>>22)
#define SB2_MBIST_mbist_pcie0_st_shift                                               (21)
#define SB2_MBIST_mbist_pcie0_st_mask                                                (0x00200000)
#define SB2_MBIST_mbist_pcie0_st(data)                                               (0x00200000&((data)<<21))
#define SB2_MBIST_mbist_pcie0_st_src(data)                                           ((0x00200000&(data))>>21)
#define SB2_MBIST_get_mbist_pcie0_st(data)                                           ((0x00200000&(data))>>21)
#define SB2_MBIST_mbist_pcie1_st_shift                                               (20)
#define SB2_MBIST_mbist_pcie1_st_mask                                                (0x00100000)
#define SB2_MBIST_mbist_pcie1_st(data)                                               (0x00100000&((data)<<20))
#define SB2_MBIST_mbist_pcie1_st_src(data)                                           ((0x00100000&(data))>>20)
#define SB2_MBIST_get_mbist_pcie1_st(data)                                           ((0x00100000&(data))>>20)
#define SB2_MBIST_mbist_nat_st_shift                                                 (19)
#define SB2_MBIST_mbist_nat_st_mask                                                  (0x00080000)
#define SB2_MBIST_mbist_nat_st(data)                                                 (0x00080000&((data)<<19))
#define SB2_MBIST_mbist_nat_st_src(data)                                             ((0x00080000&(data))>>19)
#define SB2_MBIST_get_mbist_nat_st(data)                                             ((0x00080000&(data))>>19)
#define SB2_MBIST_mbist_mipi_st_shift                                                (18)
#define SB2_MBIST_mbist_mipi_st_mask                                                 (0x00040000)
#define SB2_MBIST_mbist_mipi_st(data)                                                (0x00040000&((data)<<18))
#define SB2_MBIST_mbist_mipi_st_src(data)                                            ((0x00040000&(data))>>18)
#define SB2_MBIST_get_mbist_mipi_st(data)                                            ((0x00040000&(data))>>18)
#define SB2_MBIST_mbist_usb_st_shift                                                 (17)
#define SB2_MBIST_mbist_usb_st_mask                                                  (0x00020000)
#define SB2_MBIST_mbist_usb_st(data)                                                 (0x00020000&((data)<<17))
#define SB2_MBIST_mbist_usb_st_src(data)                                             ((0x00020000&(data))>>17)
#define SB2_MBIST_get_mbist_usb_st(data)                                             ((0x00020000&(data))>>17)
#define SB2_MBIST_mbist_se_st_shift                                                  (16)
#define SB2_MBIST_mbist_se_st_mask                                                   (0x00010000)
#define SB2_MBIST_mbist_se_st(data)                                                  (0x00010000&((data)<<16))
#define SB2_MBIST_mbist_se_st_src(data)                                              ((0x00010000&(data))>>16)
#define SB2_MBIST_get_mbist_se_st(data)                                              ((0x00010000&(data))>>16)
#define SB2_MBIST_mbist_md_st_shift                                                  (15)
#define SB2_MBIST_mbist_md_st_mask                                                   (0x00008000)
#define SB2_MBIST_mbist_md_st(data)                                                  (0x00008000&((data)<<15))
#define SB2_MBIST_mbist_md_st_src(data)                                              ((0x00008000&(data))>>15)
#define SB2_MBIST_get_mbist_md_st(data)                                              ((0x00008000&(data))>>15)
#define SB2_MBIST_mbist_nf_st_shift                                                  (14)
#define SB2_MBIST_mbist_nf_st_mask                                                   (0x00004000)
#define SB2_MBIST_mbist_nf_st(data)                                                  (0x00004000&((data)<<14))
#define SB2_MBIST_mbist_nf_st_src(data)                                              ((0x00004000&(data))>>14)
#define SB2_MBIST_get_mbist_nf_st(data)                                              ((0x00004000&(data))>>14)
#define SB2_MBIST_mbist_cr_st_shift                                                  (13)
#define SB2_MBIST_mbist_cr_st_mask                                                   (0x00002000)
#define SB2_MBIST_mbist_cr_st(data)                                                  (0x00002000&((data)<<13))
#define SB2_MBIST_mbist_cr_st_src(data)                                              ((0x00002000&(data))>>13)
#define SB2_MBIST_get_mbist_cr_st(data)                                              ((0x00002000&(data))>>13)
#define SB2_MBIST_mbist_etn_st_shift                                                 (12)
#define SB2_MBIST_mbist_etn_st_mask                                                  (0x00001000)
#define SB2_MBIST_mbist_etn_st(data)                                                 (0x00001000&((data)<<12))
#define SB2_MBIST_mbist_etn_st_src(data)                                             ((0x00001000&(data))>>12)
#define SB2_MBIST_get_mbist_etn_st(data)                                             ((0x00001000&(data))>>12)
#define SB2_MBIST_mbist_dp_st_shift                                                  (11)
#define SB2_MBIST_mbist_dp_st_mask                                                   (0x00000800)
#define SB2_MBIST_mbist_dp_st(data)                                                  (0x00000800&((data)<<11))
#define SB2_MBIST_mbist_dp_st_src(data)                                              ((0x00000800&(data))>>11)
#define SB2_MBIST_get_mbist_dp_st(data)                                              ((0x00000800&(data))>>11)
#define SB2_MBIST_mbist_ae_st_shift                                                  (10)
#define SB2_MBIST_mbist_ae_st_mask                                                   (0x00000400)
#define SB2_MBIST_mbist_ae_st(data)                                                  (0x00000400&((data)<<10))
#define SB2_MBIST_mbist_ae_st_src(data)                                              ((0x00000400&(data))>>10)
#define SB2_MBIST_get_mbist_ae_st(data)                                              ((0x00000400&(data))>>10)
#define SB2_MBIST_mbist_acpu_st_shift                                                (9)
#define SB2_MBIST_mbist_acpu_st_mask                                                 (0x00000200)
#define SB2_MBIST_mbist_acpu_st(data)                                                (0x00000200&((data)<<9))
#define SB2_MBIST_mbist_acpu_st_src(data)                                            ((0x00000200&(data))>>9)
#define SB2_MBIST_get_mbist_acpu_st(data)                                            ((0x00000200&(data))>>9)
#define SB2_MBIST_mbist_gpu_st_shift                                                 (8)
#define SB2_MBIST_mbist_gpu_st_mask                                                  (0x00000100)
#define SB2_MBIST_mbist_gpu_st(data)                                                 (0x00000100&((data)<<8))
#define SB2_MBIST_mbist_gpu_st_src(data)                                             ((0x00000100&(data))>>8)
#define SB2_MBIST_get_mbist_gpu_st(data)                                             ((0x00000100&(data))>>8)
#define SB2_MBIST_mbist_tp_st_shift                                                  (7)
#define SB2_MBIST_mbist_tp_st_mask                                                   (0x00000080)
#define SB2_MBIST_mbist_tp_st(data)                                                  (0x00000080&((data)<<7))
#define SB2_MBIST_mbist_tp_st_src(data)                                              ((0x00000080&(data))>>7)
#define SB2_MBIST_get_mbist_tp_st(data)                                              ((0x00000080&(data))>>7)
#define SB2_MBIST_mbist_aio_st_shift                                                 (6)
#define SB2_MBIST_mbist_aio_st_mask                                                  (0x00000040)
#define SB2_MBIST_mbist_aio_st(data)                                                 (0x00000040&((data)<<6))
#define SB2_MBIST_mbist_aio_st_src(data)                                             ((0x00000040&(data))>>6)
#define SB2_MBIST_get_mbist_aio_st(data)                                             ((0x00000040&(data))>>6)
#define SB2_MBIST_mbist_pif_st_shift                                                 (5)
#define SB2_MBIST_mbist_pif_st_mask                                                  (0x00000020)
#define SB2_MBIST_mbist_pif_st(data)                                                 (0x00000020&((data)<<5))
#define SB2_MBIST_mbist_pif_st_src(data)                                             ((0x00000020&(data))>>5)
#define SB2_MBIST_get_mbist_pif_st(data)                                             ((0x00000020&(data))>>5)
#define SB2_MBIST_mbist_hdmi_st_shift                                                (4)
#define SB2_MBIST_mbist_hdmi_st_mask                                                 (0x00000010)
#define SB2_MBIST_mbist_hdmi_st(data)                                                (0x00000010&((data)<<4))
#define SB2_MBIST_mbist_hdmi_st_src(data)                                            ((0x00000010&(data))>>4)
#define SB2_MBIST_get_mbist_hdmi_st(data)                                            ((0x00000010&(data))>>4)
#define SB2_MBIST_mbist_vo_st_shift                                                  (3)
#define SB2_MBIST_mbist_vo_st_mask                                                   (0x00000008)
#define SB2_MBIST_mbist_vo_st(data)                                                  (0x00000008&((data)<<3))
#define SB2_MBIST_mbist_vo_st_src(data)                                              ((0x00000008&(data))>>3)
#define SB2_MBIST_get_mbist_vo_st(data)                                              ((0x00000008&(data))>>3)
#define SB2_MBIST_mbist_dc_phy_st_shift                                              (2)
#define SB2_MBIST_mbist_dc_phy_st_mask                                               (0x00000004)
#define SB2_MBIST_mbist_dc_phy_st(data)                                              (0x00000004&((data)<<2))
#define SB2_MBIST_mbist_dc_phy_st_src(data)                                          ((0x00000004&(data))>>2)
#define SB2_MBIST_get_mbist_dc_phy_st(data)                                          ((0x00000004&(data))>>2)
#define SB2_MBIST_mbist_dc_sys_st_shift                                              (1)
#define SB2_MBIST_mbist_dc_sys_st_mask                                               (0x00000002)
#define SB2_MBIST_mbist_dc_sys_st(data)                                              (0x00000002&((data)<<1))
#define SB2_MBIST_mbist_dc_sys_st_src(data)                                          ((0x00000002&(data))>>1)
#define SB2_MBIST_get_mbist_dc_sys_st(data)                                          ((0x00000002&(data))>>1)
#define SB2_MBIST_mbist_cp_st_shift                                                  (0)
#define SB2_MBIST_mbist_cp_st_mask                                                   (0x00000001)
#define SB2_MBIST_mbist_cp_st(data)                                                  (0x00000001&((data)<<0))
#define SB2_MBIST_mbist_cp_st_src(data)                                              ((0x00000001&(data))>>0)
#define SB2_MBIST_get_mbist_cp_st(data)                                              ((0x00000001&(data))>>0)


#define SB2_PFUNC_RG0                                                                0x9801A960
#define SB2_PFUNC_RG0_reg_addr                                                       "0x9801A960"
#define SB2_PFUNC_RG0_reg                                                            0x9801A960
#define set_SB2_PFUNC_RG0_reg(data)   (*((volatile unsigned int*) SB2_PFUNC_RG0_reg)=data)
#define get_SB2_PFUNC_RG0_reg   (*((volatile unsigned int*) SB2_PFUNC_RG0_reg))
#define SB2_PFUNC_RG0_inst_adr                                                       "0x0058"
#define SB2_PFUNC_RG0_inst                                                           0x0058
#define SB2_PFUNC_RG0_rgmii0_txd_3_sr_shift                                          (5)
#define SB2_PFUNC_RG0_rgmii0_txd_3_sr_mask                                           (0x00000020)
#define SB2_PFUNC_RG0_rgmii0_txd_3_sr(data)                                          (0x00000020&((data)<<5))
#define SB2_PFUNC_RG0_rgmii0_txd_3_sr_src(data)                                      ((0x00000020&(data))>>5)
#define SB2_PFUNC_RG0_get_rgmii0_txd_3_sr(data)                                      ((0x00000020&(data))>>5)
#define SB2_PFUNC_RG0_rgmii0_txd_2_sr_shift                                          (4)
#define SB2_PFUNC_RG0_rgmii0_txd_2_sr_mask                                           (0x00000010)
#define SB2_PFUNC_RG0_rgmii0_txd_2_sr(data)                                          (0x00000010&((data)<<4))
#define SB2_PFUNC_RG0_rgmii0_txd_2_sr_src(data)                                      ((0x00000010&(data))>>4)
#define SB2_PFUNC_RG0_get_rgmii0_txd_2_sr(data)                                      ((0x00000010&(data))>>4)
#define SB2_PFUNC_RG0_rgmii0_txd_1_sr_shift                                          (3)
#define SB2_PFUNC_RG0_rgmii0_txd_1_sr_mask                                           (0x00000008)
#define SB2_PFUNC_RG0_rgmii0_txd_1_sr(data)                                          (0x00000008&((data)<<3))
#define SB2_PFUNC_RG0_rgmii0_txd_1_sr_src(data)                                      ((0x00000008&(data))>>3)
#define SB2_PFUNC_RG0_get_rgmii0_txd_1_sr(data)                                      ((0x00000008&(data))>>3)
#define SB2_PFUNC_RG0_rgmii0_txd_0_sr_shift                                          (2)
#define SB2_PFUNC_RG0_rgmii0_txd_0_sr_mask                                           (0x00000004)
#define SB2_PFUNC_RG0_rgmii0_txd_0_sr(data)                                          (0x00000004&((data)<<2))
#define SB2_PFUNC_RG0_rgmii0_txd_0_sr_src(data)                                      ((0x00000004&(data))>>2)
#define SB2_PFUNC_RG0_get_rgmii0_txd_0_sr(data)                                      ((0x00000004&(data))>>2)
#define SB2_PFUNC_RG0_rgmii0_tx_ctl_sr_shift                                         (1)
#define SB2_PFUNC_RG0_rgmii0_tx_ctl_sr_mask                                          (0x00000002)
#define SB2_PFUNC_RG0_rgmii0_tx_ctl_sr(data)                                         (0x00000002&((data)<<1))
#define SB2_PFUNC_RG0_rgmii0_tx_ctl_sr_src(data)                                     ((0x00000002&(data))>>1)
#define SB2_PFUNC_RG0_get_rgmii0_tx_ctl_sr(data)                                     ((0x00000002&(data))>>1)
#define SB2_PFUNC_RG0_rgmii0_txc_sr_shift                                            (0)
#define SB2_PFUNC_RG0_rgmii0_txc_sr_mask                                             (0x00000001)
#define SB2_PFUNC_RG0_rgmii0_txc_sr(data)                                            (0x00000001&((data)<<0))
#define SB2_PFUNC_RG0_rgmii0_txc_sr_src(data)                                        ((0x00000001&(data))>>0)
#define SB2_PFUNC_RG0_get_rgmii0_txc_sr(data)                                        ((0x00000001&(data))>>0)


#define SB2_PFUNC_RG1                                                                0x9801A964
#define SB2_PFUNC_RG1_reg_addr                                                       "0x9801A964"
#define SB2_PFUNC_RG1_reg                                                            0x9801A964
#define set_SB2_PFUNC_RG1_reg(data)   (*((volatile unsigned int*) SB2_PFUNC_RG1_reg)=data)
#define get_SB2_PFUNC_RG1_reg   (*((volatile unsigned int*) SB2_PFUNC_RG1_reg))
#define SB2_PFUNC_RG1_inst_adr                                                       "0x0059"
#define SB2_PFUNC_RG1_inst                                                           0x0059
#define SB2_PFUNC_RG1_rgmii0_rx_ctl_smt_shift                                        (31)
#define SB2_PFUNC_RG1_rgmii0_rx_ctl_smt_mask                                         (0x80000000)
#define SB2_PFUNC_RG1_rgmii0_rx_ctl_smt(data)                                        (0x80000000&((data)<<31))
#define SB2_PFUNC_RG1_rgmii0_rx_ctl_smt_src(data)                                    ((0x80000000&(data))>>31)
#define SB2_PFUNC_RG1_get_rgmii0_rx_ctl_smt(data)                                    ((0x80000000&(data))>>31)
#define SB2_PFUNC_RG1_rgmii0_rx_ctl_e2_shift                                         (30)
#define SB2_PFUNC_RG1_rgmii0_rx_ctl_e2_mask                                          (0x40000000)
#define SB2_PFUNC_RG1_rgmii0_rx_ctl_e2(data)                                         (0x40000000&((data)<<30))
#define SB2_PFUNC_RG1_rgmii0_rx_ctl_e2_src(data)                                     ((0x40000000&(data))>>30)
#define SB2_PFUNC_RG1_get_rgmii0_rx_ctl_e2(data)                                     ((0x40000000&(data))>>30)
#define SB2_PFUNC_RG1_rgmii0_rx_ctl_pud_en_shift                                     (29)
#define SB2_PFUNC_RG1_rgmii0_rx_ctl_pud_en_mask                                      (0x20000000)
#define SB2_PFUNC_RG1_rgmii0_rx_ctl_pud_en(data)                                     (0x20000000&((data)<<29))
#define SB2_PFUNC_RG1_rgmii0_rx_ctl_pud_en_src(data)                                 ((0x20000000&(data))>>29)
#define SB2_PFUNC_RG1_get_rgmii0_rx_ctl_pud_en(data)                                 ((0x20000000&(data))>>29)
#define SB2_PFUNC_RG1_rgmii0_rx_ctl_pud_sel_shift                                    (28)
#define SB2_PFUNC_RG1_rgmii0_rx_ctl_pud_sel_mask                                     (0x10000000)
#define SB2_PFUNC_RG1_rgmii0_rx_ctl_pud_sel(data)                                    (0x10000000&((data)<<28))
#define SB2_PFUNC_RG1_rgmii0_rx_ctl_pud_sel_src(data)                                ((0x10000000&(data))>>28)
#define SB2_PFUNC_RG1_get_rgmii0_rx_ctl_pud_sel(data)                                ((0x10000000&(data))>>28)
#define SB2_PFUNC_RG1_rgmii0_rxc_smt_shift                                           (27)
#define SB2_PFUNC_RG1_rgmii0_rxc_smt_mask                                            (0x08000000)
#define SB2_PFUNC_RG1_rgmii0_rxc_smt(data)                                           (0x08000000&((data)<<27))
#define SB2_PFUNC_RG1_rgmii0_rxc_smt_src(data)                                       ((0x08000000&(data))>>27)
#define SB2_PFUNC_RG1_get_rgmii0_rxc_smt(data)                                       ((0x08000000&(data))>>27)
#define SB2_PFUNC_RG1_rgmii0_rxc_e2_shift                                            (26)
#define SB2_PFUNC_RG1_rgmii0_rxc_e2_mask                                             (0x04000000)
#define SB2_PFUNC_RG1_rgmii0_rxc_e2(data)                                            (0x04000000&((data)<<26))
#define SB2_PFUNC_RG1_rgmii0_rxc_e2_src(data)                                        ((0x04000000&(data))>>26)
#define SB2_PFUNC_RG1_get_rgmii0_rxc_e2(data)                                        ((0x04000000&(data))>>26)
#define SB2_PFUNC_RG1_rgmii0_rxc_pud_en_shift                                        (25)
#define SB2_PFUNC_RG1_rgmii0_rxc_pud_en_mask                                         (0x02000000)
#define SB2_PFUNC_RG1_rgmii0_rxc_pud_en(data)                                        (0x02000000&((data)<<25))
#define SB2_PFUNC_RG1_rgmii0_rxc_pud_en_src(data)                                    ((0x02000000&(data))>>25)
#define SB2_PFUNC_RG1_get_rgmii0_rxc_pud_en(data)                                    ((0x02000000&(data))>>25)
#define SB2_PFUNC_RG1_rgmii0_rxc_pud_sel_shift                                       (24)
#define SB2_PFUNC_RG1_rgmii0_rxc_pud_sel_mask                                        (0x01000000)
#define SB2_PFUNC_RG1_rgmii0_rxc_pud_sel(data)                                       (0x01000000&((data)<<24))
#define SB2_PFUNC_RG1_rgmii0_rxc_pud_sel_src(data)                                   ((0x01000000&(data))>>24)
#define SB2_PFUNC_RG1_get_rgmii0_rxc_pud_sel(data)                                   ((0x01000000&(data))>>24)
#define SB2_PFUNC_RG1_rgmii0_txd_3_smt_shift                                         (23)
#define SB2_PFUNC_RG1_rgmii0_txd_3_smt_mask                                          (0x00800000)
#define SB2_PFUNC_RG1_rgmii0_txd_3_smt(data)                                         (0x00800000&((data)<<23))
#define SB2_PFUNC_RG1_rgmii0_txd_3_smt_src(data)                                     ((0x00800000&(data))>>23)
#define SB2_PFUNC_RG1_get_rgmii0_txd_3_smt(data)                                     ((0x00800000&(data))>>23)
#define SB2_PFUNC_RG1_rgmii0_txd_3_e2_shift                                          (22)
#define SB2_PFUNC_RG1_rgmii0_txd_3_e2_mask                                           (0x00400000)
#define SB2_PFUNC_RG1_rgmii0_txd_3_e2(data)                                          (0x00400000&((data)<<22))
#define SB2_PFUNC_RG1_rgmii0_txd_3_e2_src(data)                                      ((0x00400000&(data))>>22)
#define SB2_PFUNC_RG1_get_rgmii0_txd_3_e2(data)                                      ((0x00400000&(data))>>22)
#define SB2_PFUNC_RG1_rgmii0_txd_3_pud_en_shift                                      (21)
#define SB2_PFUNC_RG1_rgmii0_txd_3_pud_en_mask                                       (0x00200000)
#define SB2_PFUNC_RG1_rgmii0_txd_3_pud_en(data)                                      (0x00200000&((data)<<21))
#define SB2_PFUNC_RG1_rgmii0_txd_3_pud_en_src(data)                                  ((0x00200000&(data))>>21)
#define SB2_PFUNC_RG1_get_rgmii0_txd_3_pud_en(data)                                  ((0x00200000&(data))>>21)
#define SB2_PFUNC_RG1_rgmii0_txd_3_pud_sel_shift                                     (20)
#define SB2_PFUNC_RG1_rgmii0_txd_3_pud_sel_mask                                      (0x00100000)
#define SB2_PFUNC_RG1_rgmii0_txd_3_pud_sel(data)                                     (0x00100000&((data)<<20))
#define SB2_PFUNC_RG1_rgmii0_txd_3_pud_sel_src(data)                                 ((0x00100000&(data))>>20)
#define SB2_PFUNC_RG1_get_rgmii0_txd_3_pud_sel(data)                                 ((0x00100000&(data))>>20)
#define SB2_PFUNC_RG1_rgmii0_txd_2_smt_shift                                         (19)
#define SB2_PFUNC_RG1_rgmii0_txd_2_smt_mask                                          (0x00080000)
#define SB2_PFUNC_RG1_rgmii0_txd_2_smt(data)                                         (0x00080000&((data)<<19))
#define SB2_PFUNC_RG1_rgmii0_txd_2_smt_src(data)                                     ((0x00080000&(data))>>19)
#define SB2_PFUNC_RG1_get_rgmii0_txd_2_smt(data)                                     ((0x00080000&(data))>>19)
#define SB2_PFUNC_RG1_rgmii0_txd_2_e2_shift                                          (18)
#define SB2_PFUNC_RG1_rgmii0_txd_2_e2_mask                                           (0x00040000)
#define SB2_PFUNC_RG1_rgmii0_txd_2_e2(data)                                          (0x00040000&((data)<<18))
#define SB2_PFUNC_RG1_rgmii0_txd_2_e2_src(data)                                      ((0x00040000&(data))>>18)
#define SB2_PFUNC_RG1_get_rgmii0_txd_2_e2(data)                                      ((0x00040000&(data))>>18)
#define SB2_PFUNC_RG1_rgmii0_txd_2_pud_en_shift                                      (17)
#define SB2_PFUNC_RG1_rgmii0_txd_2_pud_en_mask                                       (0x00020000)
#define SB2_PFUNC_RG1_rgmii0_txd_2_pud_en(data)                                      (0x00020000&((data)<<17))
#define SB2_PFUNC_RG1_rgmii0_txd_2_pud_en_src(data)                                  ((0x00020000&(data))>>17)
#define SB2_PFUNC_RG1_get_rgmii0_txd_2_pud_en(data)                                  ((0x00020000&(data))>>17)
#define SB2_PFUNC_RG1_rgmii0_txd_2_pud_sel_shift                                     (16)
#define SB2_PFUNC_RG1_rgmii0_txd_2_pud_sel_mask                                      (0x00010000)
#define SB2_PFUNC_RG1_rgmii0_txd_2_pud_sel(data)                                     (0x00010000&((data)<<16))
#define SB2_PFUNC_RG1_rgmii0_txd_2_pud_sel_src(data)                                 ((0x00010000&(data))>>16)
#define SB2_PFUNC_RG1_get_rgmii0_txd_2_pud_sel(data)                                 ((0x00010000&(data))>>16)
#define SB2_PFUNC_RG1_rgmii0_txd_1_smt_shift                                         (15)
#define SB2_PFUNC_RG1_rgmii0_txd_1_smt_mask                                          (0x00008000)
#define SB2_PFUNC_RG1_rgmii0_txd_1_smt(data)                                         (0x00008000&((data)<<15))
#define SB2_PFUNC_RG1_rgmii0_txd_1_smt_src(data)                                     ((0x00008000&(data))>>15)
#define SB2_PFUNC_RG1_get_rgmii0_txd_1_smt(data)                                     ((0x00008000&(data))>>15)
#define SB2_PFUNC_RG1_rgmii0_txd_1_e2_shift                                          (14)
#define SB2_PFUNC_RG1_rgmii0_txd_1_e2_mask                                           (0x00004000)
#define SB2_PFUNC_RG1_rgmii0_txd_1_e2(data)                                          (0x00004000&((data)<<14))
#define SB2_PFUNC_RG1_rgmii0_txd_1_e2_src(data)                                      ((0x00004000&(data))>>14)
#define SB2_PFUNC_RG1_get_rgmii0_txd_1_e2(data)                                      ((0x00004000&(data))>>14)
#define SB2_PFUNC_RG1_rgmii0_txd_1_pud_en_shift                                      (13)
#define SB2_PFUNC_RG1_rgmii0_txd_1_pud_en_mask                                       (0x00002000)
#define SB2_PFUNC_RG1_rgmii0_txd_1_pud_en(data)                                      (0x00002000&((data)<<13))
#define SB2_PFUNC_RG1_rgmii0_txd_1_pud_en_src(data)                                  ((0x00002000&(data))>>13)
#define SB2_PFUNC_RG1_get_rgmii0_txd_1_pud_en(data)                                  ((0x00002000&(data))>>13)
#define SB2_PFUNC_RG1_rgmii0_txd_1_pud_sel_shift                                     (12)
#define SB2_PFUNC_RG1_rgmii0_txd_1_pud_sel_mask                                      (0x00001000)
#define SB2_PFUNC_RG1_rgmii0_txd_1_pud_sel(data)                                     (0x00001000&((data)<<12))
#define SB2_PFUNC_RG1_rgmii0_txd_1_pud_sel_src(data)                                 ((0x00001000&(data))>>12)
#define SB2_PFUNC_RG1_get_rgmii0_txd_1_pud_sel(data)                                 ((0x00001000&(data))>>12)
#define SB2_PFUNC_RG1_rgmii0_txd_0_smt_shift                                         (11)
#define SB2_PFUNC_RG1_rgmii0_txd_0_smt_mask                                          (0x00000800)
#define SB2_PFUNC_RG1_rgmii0_txd_0_smt(data)                                         (0x00000800&((data)<<11))
#define SB2_PFUNC_RG1_rgmii0_txd_0_smt_src(data)                                     ((0x00000800&(data))>>11)
#define SB2_PFUNC_RG1_get_rgmii0_txd_0_smt(data)                                     ((0x00000800&(data))>>11)
#define SB2_PFUNC_RG1_rgmii0_txd_0_e2_shift                                          (10)
#define SB2_PFUNC_RG1_rgmii0_txd_0_e2_mask                                           (0x00000400)
#define SB2_PFUNC_RG1_rgmii0_txd_0_e2(data)                                          (0x00000400&((data)<<10))
#define SB2_PFUNC_RG1_rgmii0_txd_0_e2_src(data)                                      ((0x00000400&(data))>>10)
#define SB2_PFUNC_RG1_get_rgmii0_txd_0_e2(data)                                      ((0x00000400&(data))>>10)
#define SB2_PFUNC_RG1_rgmii0_txd_0_pud_en_shift                                      (9)
#define SB2_PFUNC_RG1_rgmii0_txd_0_pud_en_mask                                       (0x00000200)
#define SB2_PFUNC_RG1_rgmii0_txd_0_pud_en(data)                                      (0x00000200&((data)<<9))
#define SB2_PFUNC_RG1_rgmii0_txd_0_pud_en_src(data)                                  ((0x00000200&(data))>>9)
#define SB2_PFUNC_RG1_get_rgmii0_txd_0_pud_en(data)                                  ((0x00000200&(data))>>9)
#define SB2_PFUNC_RG1_rgmii0_txd_0_pud_sel_shift                                     (8)
#define SB2_PFUNC_RG1_rgmii0_txd_0_pud_sel_mask                                      (0x00000100)
#define SB2_PFUNC_RG1_rgmii0_txd_0_pud_sel(data)                                     (0x00000100&((data)<<8))
#define SB2_PFUNC_RG1_rgmii0_txd_0_pud_sel_src(data)                                 ((0x00000100&(data))>>8)
#define SB2_PFUNC_RG1_get_rgmii0_txd_0_pud_sel(data)                                 ((0x00000100&(data))>>8)
#define SB2_PFUNC_RG1_rgmii0_tx_ctl_smt_shift                                        (7)
#define SB2_PFUNC_RG1_rgmii0_tx_ctl_smt_mask                                         (0x00000080)
#define SB2_PFUNC_RG1_rgmii0_tx_ctl_smt(data)                                        (0x00000080&((data)<<7))
#define SB2_PFUNC_RG1_rgmii0_tx_ctl_smt_src(data)                                    ((0x00000080&(data))>>7)
#define SB2_PFUNC_RG1_get_rgmii0_tx_ctl_smt(data)                                    ((0x00000080&(data))>>7)
#define SB2_PFUNC_RG1_rgmii0_tx_ctl_e2_shift                                         (6)
#define SB2_PFUNC_RG1_rgmii0_tx_ctl_e2_mask                                          (0x00000040)
#define SB2_PFUNC_RG1_rgmii0_tx_ctl_e2(data)                                         (0x00000040&((data)<<6))
#define SB2_PFUNC_RG1_rgmii0_tx_ctl_e2_src(data)                                     ((0x00000040&(data))>>6)
#define SB2_PFUNC_RG1_get_rgmii0_tx_ctl_e2(data)                                     ((0x00000040&(data))>>6)
#define SB2_PFUNC_RG1_rgmii0_tx_ctl_pud_en_shift                                     (5)
#define SB2_PFUNC_RG1_rgmii0_tx_ctl_pud_en_mask                                      (0x00000020)
#define SB2_PFUNC_RG1_rgmii0_tx_ctl_pud_en(data)                                     (0x00000020&((data)<<5))
#define SB2_PFUNC_RG1_rgmii0_tx_ctl_pud_en_src(data)                                 ((0x00000020&(data))>>5)
#define SB2_PFUNC_RG1_get_rgmii0_tx_ctl_pud_en(data)                                 ((0x00000020&(data))>>5)
#define SB2_PFUNC_RG1_rgmii0_tx_ctl_pud_sel_shift                                    (4)
#define SB2_PFUNC_RG1_rgmii0_tx_ctl_pud_sel_mask                                     (0x00000010)
#define SB2_PFUNC_RG1_rgmii0_tx_ctl_pud_sel(data)                                    (0x00000010&((data)<<4))
#define SB2_PFUNC_RG1_rgmii0_tx_ctl_pud_sel_src(data)                                ((0x00000010&(data))>>4)
#define SB2_PFUNC_RG1_get_rgmii0_tx_ctl_pud_sel(data)                                ((0x00000010&(data))>>4)
#define SB2_PFUNC_RG1_rgmii0_txc_smt_shift                                           (3)
#define SB2_PFUNC_RG1_rgmii0_txc_smt_mask                                            (0x00000008)
#define SB2_PFUNC_RG1_rgmii0_txc_smt(data)                                           (0x00000008&((data)<<3))
#define SB2_PFUNC_RG1_rgmii0_txc_smt_src(data)                                       ((0x00000008&(data))>>3)
#define SB2_PFUNC_RG1_get_rgmii0_txc_smt(data)                                       ((0x00000008&(data))>>3)
#define SB2_PFUNC_RG1_rgmii0_txc_e2_shift                                            (2)
#define SB2_PFUNC_RG1_rgmii0_txc_e2_mask                                             (0x00000004)
#define SB2_PFUNC_RG1_rgmii0_txc_e2(data)                                            (0x00000004&((data)<<2))
#define SB2_PFUNC_RG1_rgmii0_txc_e2_src(data)                                        ((0x00000004&(data))>>2)
#define SB2_PFUNC_RG1_get_rgmii0_txc_e2(data)                                        ((0x00000004&(data))>>2)
#define SB2_PFUNC_RG1_rgmii0_txc_pud_en_shift                                        (1)
#define SB2_PFUNC_RG1_rgmii0_txc_pud_en_mask                                         (0x00000002)
#define SB2_PFUNC_RG1_rgmii0_txc_pud_en(data)                                        (0x00000002&((data)<<1))
#define SB2_PFUNC_RG1_rgmii0_txc_pud_en_src(data)                                    ((0x00000002&(data))>>1)
#define SB2_PFUNC_RG1_get_rgmii0_txc_pud_en(data)                                    ((0x00000002&(data))>>1)
#define SB2_PFUNC_RG1_rgmii0_txc_pud_sel_shift                                       (0)
#define SB2_PFUNC_RG1_rgmii0_txc_pud_sel_mask                                        (0x00000001)
#define SB2_PFUNC_RG1_rgmii0_txc_pud_sel(data)                                       (0x00000001&((data)<<0))
#define SB2_PFUNC_RG1_rgmii0_txc_pud_sel_src(data)                                   ((0x00000001&(data))>>0)
#define SB2_PFUNC_RG1_get_rgmii0_txc_pud_sel(data)                                   ((0x00000001&(data))>>0)


#define SB2_PFUNC_RG2                                                                0x9801A968
#define SB2_PFUNC_RG2_reg_addr                                                       "0x9801A968"
#define SB2_PFUNC_RG2_reg                                                            0x9801A968
#define set_SB2_PFUNC_RG2_reg(data)   (*((volatile unsigned int*) SB2_PFUNC_RG2_reg)=data)
#define get_SB2_PFUNC_RG2_reg   (*((volatile unsigned int*) SB2_PFUNC_RG2_reg))
#define SB2_PFUNC_RG2_inst_adr                                                       "0x005A"
#define SB2_PFUNC_RG2_inst                                                           0x005A
#define SB2_PFUNC_RG2_rgmii0_bias_mode2_shift                                        (31)
#define SB2_PFUNC_RG2_rgmii0_bias_mode2_mask                                         (0x80000000)
#define SB2_PFUNC_RG2_rgmii0_bias_mode2(data)                                        (0x80000000&((data)<<31))
#define SB2_PFUNC_RG2_rgmii0_bias_mode2_src(data)                                    ((0x80000000&(data))>>31)
#define SB2_PFUNC_RG2_get_rgmii0_bias_mode2(data)                                    ((0x80000000&(data))>>31)
#define SB2_PFUNC_RG2_rgmii0_bias_mode_shift                                         (30)
#define SB2_PFUNC_RG2_rgmii0_bias_mode_mask                                          (0x40000000)
#define SB2_PFUNC_RG2_rgmii0_bias_mode(data)                                         (0x40000000&((data)<<30))
#define SB2_PFUNC_RG2_rgmii0_bias_mode_src(data)                                     ((0x40000000&(data))>>30)
#define SB2_PFUNC_RG2_get_rgmii0_bias_mode(data)                                     ((0x40000000&(data))>>30)
#define SB2_PFUNC_RG2_rgmii0_bias_dn_shift                                           (27)
#define SB2_PFUNC_RG2_rgmii0_bias_dn_mask                                            (0x38000000)
#define SB2_PFUNC_RG2_rgmii0_bias_dn(data)                                           (0x38000000&((data)<<27))
#define SB2_PFUNC_RG2_rgmii0_bias_dn_src(data)                                       ((0x38000000&(data))>>27)
#define SB2_PFUNC_RG2_get_rgmii0_bias_dn(data)                                       ((0x38000000&(data))>>27)
#define SB2_PFUNC_RG2_rgmii0_bias_dp_shift                                           (24)
#define SB2_PFUNC_RG2_rgmii0_bias_dp_mask                                            (0x07000000)
#define SB2_PFUNC_RG2_rgmii0_bias_dp(data)                                           (0x07000000&((data)<<24))
#define SB2_PFUNC_RG2_rgmii0_bias_dp_src(data)                                       ((0x07000000&(data))>>24)
#define SB2_PFUNC_RG2_get_rgmii0_bias_dp(data)                                       ((0x07000000&(data))>>24)
#define SB2_PFUNC_RG2_rgmii0_mdc_smt_shift                                           (23)
#define SB2_PFUNC_RG2_rgmii0_mdc_smt_mask                                            (0x00800000)
#define SB2_PFUNC_RG2_rgmii0_mdc_smt(data)                                           (0x00800000&((data)<<23))
#define SB2_PFUNC_RG2_rgmii0_mdc_smt_src(data)                                       ((0x00800000&(data))>>23)
#define SB2_PFUNC_RG2_get_rgmii0_mdc_smt(data)                                       ((0x00800000&(data))>>23)
#define SB2_PFUNC_RG2_rgmii0_mdc_e2_shift                                            (22)
#define SB2_PFUNC_RG2_rgmii0_mdc_e2_mask                                             (0x00400000)
#define SB2_PFUNC_RG2_rgmii0_mdc_e2(data)                                            (0x00400000&((data)<<22))
#define SB2_PFUNC_RG2_rgmii0_mdc_e2_src(data)                                        ((0x00400000&(data))>>22)
#define SB2_PFUNC_RG2_get_rgmii0_mdc_e2(data)                                        ((0x00400000&(data))>>22)
#define SB2_PFUNC_RG2_rgmii0_mdc_pud_en_shift                                        (21)
#define SB2_PFUNC_RG2_rgmii0_mdc_pud_en_mask                                         (0x00200000)
#define SB2_PFUNC_RG2_rgmii0_mdc_pud_en(data)                                        (0x00200000&((data)<<21))
#define SB2_PFUNC_RG2_rgmii0_mdc_pud_en_src(data)                                    ((0x00200000&(data))>>21)
#define SB2_PFUNC_RG2_get_rgmii0_mdc_pud_en(data)                                    ((0x00200000&(data))>>21)
#define SB2_PFUNC_RG2_rgmii0_mdc_pud_sel_shift                                       (20)
#define SB2_PFUNC_RG2_rgmii0_mdc_pud_sel_mask                                        (0x00100000)
#define SB2_PFUNC_RG2_rgmii0_mdc_pud_sel(data)                                       (0x00100000&((data)<<20))
#define SB2_PFUNC_RG2_rgmii0_mdc_pud_sel_src(data)                                   ((0x00100000&(data))>>20)
#define SB2_PFUNC_RG2_get_rgmii0_mdc_pud_sel(data)                                   ((0x00100000&(data))>>20)
#define SB2_PFUNC_RG2_rgmii0_mdio_smt_shift                                          (19)
#define SB2_PFUNC_RG2_rgmii0_mdio_smt_mask                                           (0x00080000)
#define SB2_PFUNC_RG2_rgmii0_mdio_smt(data)                                          (0x00080000&((data)<<19))
#define SB2_PFUNC_RG2_rgmii0_mdio_smt_src(data)                                      ((0x00080000&(data))>>19)
#define SB2_PFUNC_RG2_get_rgmii0_mdio_smt(data)                                      ((0x00080000&(data))>>19)
#define SB2_PFUNC_RG2_rgmii0_mdio_e2_shift                                           (18)
#define SB2_PFUNC_RG2_rgmii0_mdio_e2_mask                                            (0x00040000)
#define SB2_PFUNC_RG2_rgmii0_mdio_e2(data)                                           (0x00040000&((data)<<18))
#define SB2_PFUNC_RG2_rgmii0_mdio_e2_src(data)                                       ((0x00040000&(data))>>18)
#define SB2_PFUNC_RG2_get_rgmii0_mdio_e2(data)                                       ((0x00040000&(data))>>18)
#define SB2_PFUNC_RG2_rgmii0_mdio_pud_en_shift                                       (17)
#define SB2_PFUNC_RG2_rgmii0_mdio_pud_en_mask                                        (0x00020000)
#define SB2_PFUNC_RG2_rgmii0_mdio_pud_en(data)                                       (0x00020000&((data)<<17))
#define SB2_PFUNC_RG2_rgmii0_mdio_pud_en_src(data)                                   ((0x00020000&(data))>>17)
#define SB2_PFUNC_RG2_get_rgmii0_mdio_pud_en(data)                                   ((0x00020000&(data))>>17)
#define SB2_PFUNC_RG2_rgmii0_mdio_pud_sel_shift                                      (16)
#define SB2_PFUNC_RG2_rgmii0_mdio_pud_sel_mask                                       (0x00010000)
#define SB2_PFUNC_RG2_rgmii0_mdio_pud_sel(data)                                      (0x00010000&((data)<<16))
#define SB2_PFUNC_RG2_rgmii0_mdio_pud_sel_src(data)                                  ((0x00010000&(data))>>16)
#define SB2_PFUNC_RG2_get_rgmii0_mdio_pud_sel(data)                                  ((0x00010000&(data))>>16)
#define SB2_PFUNC_RG2_rgmii0_rxd_3_smt_shift                                         (15)
#define SB2_PFUNC_RG2_rgmii0_rxd_3_smt_mask                                          (0x00008000)
#define SB2_PFUNC_RG2_rgmii0_rxd_3_smt(data)                                         (0x00008000&((data)<<15))
#define SB2_PFUNC_RG2_rgmii0_rxd_3_smt_src(data)                                     ((0x00008000&(data))>>15)
#define SB2_PFUNC_RG2_get_rgmii0_rxd_3_smt(data)                                     ((0x00008000&(data))>>15)
#define SB2_PFUNC_RG2_rgmii0_rxd_3_e2_shift                                          (14)
#define SB2_PFUNC_RG2_rgmii0_rxd_3_e2_mask                                           (0x00004000)
#define SB2_PFUNC_RG2_rgmii0_rxd_3_e2(data)                                          (0x00004000&((data)<<14))
#define SB2_PFUNC_RG2_rgmii0_rxd_3_e2_src(data)                                      ((0x00004000&(data))>>14)
#define SB2_PFUNC_RG2_get_rgmii0_rxd_3_e2(data)                                      ((0x00004000&(data))>>14)
#define SB2_PFUNC_RG2_rgmii0_rxd_3_pud_en_shift                                      (13)
#define SB2_PFUNC_RG2_rgmii0_rxd_3_pud_en_mask                                       (0x00002000)
#define SB2_PFUNC_RG2_rgmii0_rxd_3_pud_en(data)                                      (0x00002000&((data)<<13))
#define SB2_PFUNC_RG2_rgmii0_rxd_3_pud_en_src(data)                                  ((0x00002000&(data))>>13)
#define SB2_PFUNC_RG2_get_rgmii0_rxd_3_pud_en(data)                                  ((0x00002000&(data))>>13)
#define SB2_PFUNC_RG2_rgmii0_rxd_3_pud_sel_shift                                     (12)
#define SB2_PFUNC_RG2_rgmii0_rxd_3_pud_sel_mask                                      (0x00001000)
#define SB2_PFUNC_RG2_rgmii0_rxd_3_pud_sel(data)                                     (0x00001000&((data)<<12))
#define SB2_PFUNC_RG2_rgmii0_rxd_3_pud_sel_src(data)                                 ((0x00001000&(data))>>12)
#define SB2_PFUNC_RG2_get_rgmii0_rxd_3_pud_sel(data)                                 ((0x00001000&(data))>>12)
#define SB2_PFUNC_RG2_rgmii0_rxd_2_smt_shift                                         (11)
#define SB2_PFUNC_RG2_rgmii0_rxd_2_smt_mask                                          (0x00000800)
#define SB2_PFUNC_RG2_rgmii0_rxd_2_smt(data)                                         (0x00000800&((data)<<11))
#define SB2_PFUNC_RG2_rgmii0_rxd_2_smt_src(data)                                     ((0x00000800&(data))>>11)
#define SB2_PFUNC_RG2_get_rgmii0_rxd_2_smt(data)                                     ((0x00000800&(data))>>11)
#define SB2_PFUNC_RG2_rgmii0_rxd_2_e2_shift                                          (10)
#define SB2_PFUNC_RG2_rgmii0_rxd_2_e2_mask                                           (0x00000400)
#define SB2_PFUNC_RG2_rgmii0_rxd_2_e2(data)                                          (0x00000400&((data)<<10))
#define SB2_PFUNC_RG2_rgmii0_rxd_2_e2_src(data)                                      ((0x00000400&(data))>>10)
#define SB2_PFUNC_RG2_get_rgmii0_rxd_2_e2(data)                                      ((0x00000400&(data))>>10)
#define SB2_PFUNC_RG2_rgmii0_rxd_2_pud_en_shift                                      (9)
#define SB2_PFUNC_RG2_rgmii0_rxd_2_pud_en_mask                                       (0x00000200)
#define SB2_PFUNC_RG2_rgmii0_rxd_2_pud_en(data)                                      (0x00000200&((data)<<9))
#define SB2_PFUNC_RG2_rgmii0_rxd_2_pud_en_src(data)                                  ((0x00000200&(data))>>9)
#define SB2_PFUNC_RG2_get_rgmii0_rxd_2_pud_en(data)                                  ((0x00000200&(data))>>9)
#define SB2_PFUNC_RG2_rgmii0_rxd_2_pud_sel_shift                                     (8)
#define SB2_PFUNC_RG2_rgmii0_rxd_2_pud_sel_mask                                      (0x00000100)
#define SB2_PFUNC_RG2_rgmii0_rxd_2_pud_sel(data)                                     (0x00000100&((data)<<8))
#define SB2_PFUNC_RG2_rgmii0_rxd_2_pud_sel_src(data)                                 ((0x00000100&(data))>>8)
#define SB2_PFUNC_RG2_get_rgmii0_rxd_2_pud_sel(data)                                 ((0x00000100&(data))>>8)
#define SB2_PFUNC_RG2_rgmii0_rxd_1_smt_shift                                         (7)
#define SB2_PFUNC_RG2_rgmii0_rxd_1_smt_mask                                          (0x00000080)
#define SB2_PFUNC_RG2_rgmii0_rxd_1_smt(data)                                         (0x00000080&((data)<<7))
#define SB2_PFUNC_RG2_rgmii0_rxd_1_smt_src(data)                                     ((0x00000080&(data))>>7)
#define SB2_PFUNC_RG2_get_rgmii0_rxd_1_smt(data)                                     ((0x00000080&(data))>>7)
#define SB2_PFUNC_RG2_rgmii0_rxd_1_e2_shift                                          (6)
#define SB2_PFUNC_RG2_rgmii0_rxd_1_e2_mask                                           (0x00000040)
#define SB2_PFUNC_RG2_rgmii0_rxd_1_e2(data)                                          (0x00000040&((data)<<6))
#define SB2_PFUNC_RG2_rgmii0_rxd_1_e2_src(data)                                      ((0x00000040&(data))>>6)
#define SB2_PFUNC_RG2_get_rgmii0_rxd_1_e2(data)                                      ((0x00000040&(data))>>6)
#define SB2_PFUNC_RG2_rgmii0_rxd_1_pud_en_shift                                      (5)
#define SB2_PFUNC_RG2_rgmii0_rxd_1_pud_en_mask                                       (0x00000020)
#define SB2_PFUNC_RG2_rgmii0_rxd_1_pud_en(data)                                      (0x00000020&((data)<<5))
#define SB2_PFUNC_RG2_rgmii0_rxd_1_pud_en_src(data)                                  ((0x00000020&(data))>>5)
#define SB2_PFUNC_RG2_get_rgmii0_rxd_1_pud_en(data)                                  ((0x00000020&(data))>>5)
#define SB2_PFUNC_RG2_rgmii0_rxd_1_pud_sel_shift                                     (4)
#define SB2_PFUNC_RG2_rgmii0_rxd_1_pud_sel_mask                                      (0x00000010)
#define SB2_PFUNC_RG2_rgmii0_rxd_1_pud_sel(data)                                     (0x00000010&((data)<<4))
#define SB2_PFUNC_RG2_rgmii0_rxd_1_pud_sel_src(data)                                 ((0x00000010&(data))>>4)
#define SB2_PFUNC_RG2_get_rgmii0_rxd_1_pud_sel(data)                                 ((0x00000010&(data))>>4)
#define SB2_PFUNC_RG2_rgmii0_rxd_0_smt_shift                                         (3)
#define SB2_PFUNC_RG2_rgmii0_rxd_0_smt_mask                                          (0x00000008)
#define SB2_PFUNC_RG2_rgmii0_rxd_0_smt(data)                                         (0x00000008&((data)<<3))
#define SB2_PFUNC_RG2_rgmii0_rxd_0_smt_src(data)                                     ((0x00000008&(data))>>3)
#define SB2_PFUNC_RG2_get_rgmii0_rxd_0_smt(data)                                     ((0x00000008&(data))>>3)
#define SB2_PFUNC_RG2_rgmii0_rxd_0_e2_shift                                          (2)
#define SB2_PFUNC_RG2_rgmii0_rxd_0_e2_mask                                           (0x00000004)
#define SB2_PFUNC_RG2_rgmii0_rxd_0_e2(data)                                          (0x00000004&((data)<<2))
#define SB2_PFUNC_RG2_rgmii0_rxd_0_e2_src(data)                                      ((0x00000004&(data))>>2)
#define SB2_PFUNC_RG2_get_rgmii0_rxd_0_e2(data)                                      ((0x00000004&(data))>>2)
#define SB2_PFUNC_RG2_rgmii0_rxd_0_pud_en_shift                                      (1)
#define SB2_PFUNC_RG2_rgmii0_rxd_0_pud_en_mask                                       (0x00000002)
#define SB2_PFUNC_RG2_rgmii0_rxd_0_pud_en(data)                                      (0x00000002&((data)<<1))
#define SB2_PFUNC_RG2_rgmii0_rxd_0_pud_en_src(data)                                  ((0x00000002&(data))>>1)
#define SB2_PFUNC_RG2_get_rgmii0_rxd_0_pud_en(data)                                  ((0x00000002&(data))>>1)
#define SB2_PFUNC_RG2_rgmii0_rxd_0_pud_sel_shift                                     (0)
#define SB2_PFUNC_RG2_rgmii0_rxd_0_pud_sel_mask                                      (0x00000001)
#define SB2_PFUNC_RG2_rgmii0_rxd_0_pud_sel(data)                                     (0x00000001&((data)<<0))
#define SB2_PFUNC_RG2_rgmii0_rxd_0_pud_sel_src(data)                                 ((0x00000001&(data))>>0)
#define SB2_PFUNC_RG2_get_rgmii0_rxd_0_pud_sel(data)                                 ((0x00000001&(data))>>0)


#define SB2_MUXPAD_RG0                                                               0x9801A96C
#define SB2_MUXPAD_RG0_reg_addr                                                      "0x9801A96C"
#define SB2_MUXPAD_RG0_reg                                                           0x9801A96C
#define set_SB2_MUXPAD_RG0_reg(data)   (*((volatile unsigned int*) SB2_MUXPAD_RG0_reg)=data)
#define get_SB2_MUXPAD_RG0_reg   (*((volatile unsigned int*) SB2_MUXPAD_RG0_reg))
#define SB2_MUXPAD_RG0_inst_adr                                                      "0x005B"
#define SB2_MUXPAD_RG0_inst                                                          0x005B
#define SB2_MUXPAD_RG0_rgmii0_mdc_shift                                              (26)
#define SB2_MUXPAD_RG0_rgmii0_mdc_mask                                               (0x0C000000)
#define SB2_MUXPAD_RG0_rgmii0_mdc(data)                                              (0x0C000000&((data)<<26))
#define SB2_MUXPAD_RG0_rgmii0_mdc_src(data)                                          ((0x0C000000&(data))>>26)
#define SB2_MUXPAD_RG0_get_rgmii0_mdc(data)                                          ((0x0C000000&(data))>>26)
#define SB2_MUXPAD_RG0_rgmii0_mdio_shift                                             (24)
#define SB2_MUXPAD_RG0_rgmii0_mdio_mask                                              (0x03000000)
#define SB2_MUXPAD_RG0_rgmii0_mdio(data)                                             (0x03000000&((data)<<24))
#define SB2_MUXPAD_RG0_rgmii0_mdio_src(data)                                         ((0x03000000&(data))>>24)
#define SB2_MUXPAD_RG0_get_rgmii0_mdio(data)                                         ((0x03000000&(data))>>24)
#define SB2_MUXPAD_RG0_rgmii0_rxd_3_shift                                            (22)
#define SB2_MUXPAD_RG0_rgmii0_rxd_3_mask                                             (0x00C00000)
#define SB2_MUXPAD_RG0_rgmii0_rxd_3(data)                                            (0x00C00000&((data)<<22))
#define SB2_MUXPAD_RG0_rgmii0_rxd_3_src(data)                                        ((0x00C00000&(data))>>22)
#define SB2_MUXPAD_RG0_get_rgmii0_rxd_3(data)                                        ((0x00C00000&(data))>>22)
#define SB2_MUXPAD_RG0_rgmii0_rxd_2_shift                                            (20)
#define SB2_MUXPAD_RG0_rgmii0_rxd_2_mask                                             (0x00300000)
#define SB2_MUXPAD_RG0_rgmii0_rxd_2(data)                                            (0x00300000&((data)<<20))
#define SB2_MUXPAD_RG0_rgmii0_rxd_2_src(data)                                        ((0x00300000&(data))>>20)
#define SB2_MUXPAD_RG0_get_rgmii0_rxd_2(data)                                        ((0x00300000&(data))>>20)
#define SB2_MUXPAD_RG0_rgmii0_rxd_1_shift                                            (18)
#define SB2_MUXPAD_RG0_rgmii0_rxd_1_mask                                             (0x000C0000)
#define SB2_MUXPAD_RG0_rgmii0_rxd_1(data)                                            (0x000C0000&((data)<<18))
#define SB2_MUXPAD_RG0_rgmii0_rxd_1_src(data)                                        ((0x000C0000&(data))>>18)
#define SB2_MUXPAD_RG0_get_rgmii0_rxd_1(data)                                        ((0x000C0000&(data))>>18)
#define SB2_MUXPAD_RG0_rgmii0_rxd_0_shift                                            (16)
#define SB2_MUXPAD_RG0_rgmii0_rxd_0_mask                                             (0x00030000)
#define SB2_MUXPAD_RG0_rgmii0_rxd_0(data)                                            (0x00030000&((data)<<16))
#define SB2_MUXPAD_RG0_rgmii0_rxd_0_src(data)                                        ((0x00030000&(data))>>16)
#define SB2_MUXPAD_RG0_get_rgmii0_rxd_0(data)                                        ((0x00030000&(data))>>16)
#define SB2_MUXPAD_RG0_rgmii0_rx_ctl_shift                                           (14)
#define SB2_MUXPAD_RG0_rgmii0_rx_ctl_mask                                            (0x0000C000)
#define SB2_MUXPAD_RG0_rgmii0_rx_ctl(data)                                           (0x0000C000&((data)<<14))
#define SB2_MUXPAD_RG0_rgmii0_rx_ctl_src(data)                                       ((0x0000C000&(data))>>14)
#define SB2_MUXPAD_RG0_get_rgmii0_rx_ctl(data)                                       ((0x0000C000&(data))>>14)
#define SB2_MUXPAD_RG0_rgmii0_rxc_shift                                              (12)
#define SB2_MUXPAD_RG0_rgmii0_rxc_mask                                               (0x00003000)
#define SB2_MUXPAD_RG0_rgmii0_rxc(data)                                              (0x00003000&((data)<<12))
#define SB2_MUXPAD_RG0_rgmii0_rxc_src(data)                                          ((0x00003000&(data))>>12)
#define SB2_MUXPAD_RG0_get_rgmii0_rxc(data)                                          ((0x00003000&(data))>>12)
#define SB2_MUXPAD_RG0_rgmii0_txd_3_shift                                            (10)
#define SB2_MUXPAD_RG0_rgmii0_txd_3_mask                                             (0x00000C00)
#define SB2_MUXPAD_RG0_rgmii0_txd_3(data)                                            (0x00000C00&((data)<<10))
#define SB2_MUXPAD_RG0_rgmii0_txd_3_src(data)                                        ((0x00000C00&(data))>>10)
#define SB2_MUXPAD_RG0_get_rgmii0_txd_3(data)                                        ((0x00000C00&(data))>>10)
#define SB2_MUXPAD_RG0_rgmii0_txd_2_shift                                            (8)
#define SB2_MUXPAD_RG0_rgmii0_txd_2_mask                                             (0x00000300)
#define SB2_MUXPAD_RG0_rgmii0_txd_2(data)                                            (0x00000300&((data)<<8))
#define SB2_MUXPAD_RG0_rgmii0_txd_2_src(data)                                        ((0x00000300&(data))>>8)
#define SB2_MUXPAD_RG0_get_rgmii0_txd_2(data)                                        ((0x00000300&(data))>>8)
#define SB2_MUXPAD_RG0_rgmii0_txd_1_shift                                            (6)
#define SB2_MUXPAD_RG0_rgmii0_txd_1_mask                                             (0x000000C0)
#define SB2_MUXPAD_RG0_rgmii0_txd_1(data)                                            (0x000000C0&((data)<<6))
#define SB2_MUXPAD_RG0_rgmii0_txd_1_src(data)                                        ((0x000000C0&(data))>>6)
#define SB2_MUXPAD_RG0_get_rgmii0_txd_1(data)                                        ((0x000000C0&(data))>>6)
#define SB2_MUXPAD_RG0_rgmii0_txd_0_shift                                            (4)
#define SB2_MUXPAD_RG0_rgmii0_txd_0_mask                                             (0x00000030)
#define SB2_MUXPAD_RG0_rgmii0_txd_0(data)                                            (0x00000030&((data)<<4))
#define SB2_MUXPAD_RG0_rgmii0_txd_0_src(data)                                        ((0x00000030&(data))>>4)
#define SB2_MUXPAD_RG0_get_rgmii0_txd_0(data)                                        ((0x00000030&(data))>>4)
#define SB2_MUXPAD_RG0_rgmii0_tx_ctl_shift                                           (2)
#define SB2_MUXPAD_RG0_rgmii0_tx_ctl_mask                                            (0x0000000C)
#define SB2_MUXPAD_RG0_rgmii0_tx_ctl(data)                                           (0x0000000C&((data)<<2))
#define SB2_MUXPAD_RG0_rgmii0_tx_ctl_src(data)                                       ((0x0000000C&(data))>>2)
#define SB2_MUXPAD_RG0_get_rgmii0_tx_ctl(data)                                       ((0x0000000C&(data))>>2)
#define SB2_MUXPAD_RG0_rgmii0_txc_shift                                              (0)
#define SB2_MUXPAD_RG0_rgmii0_txc_mask                                               (0x00000003)
#define SB2_MUXPAD_RG0_rgmii0_txc(data)                                              (0x00000003&((data)<<0))
#define SB2_MUXPAD_RG0_rgmii0_txc_src(data)                                          ((0x00000003&(data))>>0)
#define SB2_MUXPAD_RG0_get_rgmii0_txc(data)                                          ((0x00000003&(data))>>0)


#define SB2_PFUNC_RG3                                                                0x9801A970
#define SB2_PFUNC_RG3_reg_addr                                                       "0x9801A970"
#define SB2_PFUNC_RG3_reg                                                            0x9801A970
#define set_SB2_PFUNC_RG3_reg(data)   (*((volatile unsigned int*) SB2_PFUNC_RG3_reg)=data)
#define get_SB2_PFUNC_RG3_reg   (*((volatile unsigned int*) SB2_PFUNC_RG3_reg))
#define SB2_PFUNC_RG3_inst_adr                                                       "0x005C"
#define SB2_PFUNC_RG3_inst                                                           0x005C
#define SB2_PFUNC_RG3_rgmii1_txd_3_sr_shift                                          (5)
#define SB2_PFUNC_RG3_rgmii1_txd_3_sr_mask                                           (0x00000020)
#define SB2_PFUNC_RG3_rgmii1_txd_3_sr(data)                                          (0x00000020&((data)<<5))
#define SB2_PFUNC_RG3_rgmii1_txd_3_sr_src(data)                                      ((0x00000020&(data))>>5)
#define SB2_PFUNC_RG3_get_rgmii1_txd_3_sr(data)                                      ((0x00000020&(data))>>5)
#define SB2_PFUNC_RG3_rgmii1_txd_2_sr_shift                                          (4)
#define SB2_PFUNC_RG3_rgmii1_txd_2_sr_mask                                           (0x00000010)
#define SB2_PFUNC_RG3_rgmii1_txd_2_sr(data)                                          (0x00000010&((data)<<4))
#define SB2_PFUNC_RG3_rgmii1_txd_2_sr_src(data)                                      ((0x00000010&(data))>>4)
#define SB2_PFUNC_RG3_get_rgmii1_txd_2_sr(data)                                      ((0x00000010&(data))>>4)
#define SB2_PFUNC_RG3_rgmii1_txd_1_sr_shift                                          (3)
#define SB2_PFUNC_RG3_rgmii1_txd_1_sr_mask                                           (0x00000008)
#define SB2_PFUNC_RG3_rgmii1_txd_1_sr(data)                                          (0x00000008&((data)<<3))
#define SB2_PFUNC_RG3_rgmii1_txd_1_sr_src(data)                                      ((0x00000008&(data))>>3)
#define SB2_PFUNC_RG3_get_rgmii1_txd_1_sr(data)                                      ((0x00000008&(data))>>3)
#define SB2_PFUNC_RG3_rgmii1_txd_0_sr_shift                                          (2)
#define SB2_PFUNC_RG3_rgmii1_txd_0_sr_mask                                           (0x00000004)
#define SB2_PFUNC_RG3_rgmii1_txd_0_sr(data)                                          (0x00000004&((data)<<2))
#define SB2_PFUNC_RG3_rgmii1_txd_0_sr_src(data)                                      ((0x00000004&(data))>>2)
#define SB2_PFUNC_RG3_get_rgmii1_txd_0_sr(data)                                      ((0x00000004&(data))>>2)
#define SB2_PFUNC_RG3_rgmii1_tx_ctl_sr_shift                                         (1)
#define SB2_PFUNC_RG3_rgmii1_tx_ctl_sr_mask                                          (0x00000002)
#define SB2_PFUNC_RG3_rgmii1_tx_ctl_sr(data)                                         (0x00000002&((data)<<1))
#define SB2_PFUNC_RG3_rgmii1_tx_ctl_sr_src(data)                                     ((0x00000002&(data))>>1)
#define SB2_PFUNC_RG3_get_rgmii1_tx_ctl_sr(data)                                     ((0x00000002&(data))>>1)
#define SB2_PFUNC_RG3_rgmii1_txc_sr_shift                                            (0)
#define SB2_PFUNC_RG3_rgmii1_txc_sr_mask                                             (0x00000001)
#define SB2_PFUNC_RG3_rgmii1_txc_sr(data)                                            (0x00000001&((data)<<0))
#define SB2_PFUNC_RG3_rgmii1_txc_sr_src(data)                                        ((0x00000001&(data))>>0)
#define SB2_PFUNC_RG3_get_rgmii1_txc_sr(data)                                        ((0x00000001&(data))>>0)


#define SB2_PFUNC_RG4                                                                0x9801A974
#define SB2_PFUNC_RG4_reg_addr                                                       "0x9801A974"
#define SB2_PFUNC_RG4_reg                                                            0x9801A974
#define set_SB2_PFUNC_RG4_reg(data)   (*((volatile unsigned int*) SB2_PFUNC_RG4_reg)=data)
#define get_SB2_PFUNC_RG4_reg   (*((volatile unsigned int*) SB2_PFUNC_RG4_reg))
#define SB2_PFUNC_RG4_inst_adr                                                       "0x005D"
#define SB2_PFUNC_RG4_inst                                                           0x005D
#define SB2_PFUNC_RG4_rgmii1_rx_ctl_smt_shift                                        (31)
#define SB2_PFUNC_RG4_rgmii1_rx_ctl_smt_mask                                         (0x80000000)
#define SB2_PFUNC_RG4_rgmii1_rx_ctl_smt(data)                                        (0x80000000&((data)<<31))
#define SB2_PFUNC_RG4_rgmii1_rx_ctl_smt_src(data)                                    ((0x80000000&(data))>>31)
#define SB2_PFUNC_RG4_get_rgmii1_rx_ctl_smt(data)                                    ((0x80000000&(data))>>31)
#define SB2_PFUNC_RG4_rgmii1_rx_ctl_e2_shift                                         (30)
#define SB2_PFUNC_RG4_rgmii1_rx_ctl_e2_mask                                          (0x40000000)
#define SB2_PFUNC_RG4_rgmii1_rx_ctl_e2(data)                                         (0x40000000&((data)<<30))
#define SB2_PFUNC_RG4_rgmii1_rx_ctl_e2_src(data)                                     ((0x40000000&(data))>>30)
#define SB2_PFUNC_RG4_get_rgmii1_rx_ctl_e2(data)                                     ((0x40000000&(data))>>30)
#define SB2_PFUNC_RG4_rgmii1_rx_ctl_pud_en_shift                                     (29)
#define SB2_PFUNC_RG4_rgmii1_rx_ctl_pud_en_mask                                      (0x20000000)
#define SB2_PFUNC_RG4_rgmii1_rx_ctl_pud_en(data)                                     (0x20000000&((data)<<29))
#define SB2_PFUNC_RG4_rgmii1_rx_ctl_pud_en_src(data)                                 ((0x20000000&(data))>>29)
#define SB2_PFUNC_RG4_get_rgmii1_rx_ctl_pud_en(data)                                 ((0x20000000&(data))>>29)
#define SB2_PFUNC_RG4_rgmii1_rx_ctl_pud_sel_shift                                    (28)
#define SB2_PFUNC_RG4_rgmii1_rx_ctl_pud_sel_mask                                     (0x10000000)
#define SB2_PFUNC_RG4_rgmii1_rx_ctl_pud_sel(data)                                    (0x10000000&((data)<<28))
#define SB2_PFUNC_RG4_rgmii1_rx_ctl_pud_sel_src(data)                                ((0x10000000&(data))>>28)
#define SB2_PFUNC_RG4_get_rgmii1_rx_ctl_pud_sel(data)                                ((0x10000000&(data))>>28)
#define SB2_PFUNC_RG4_rgmii1_rxc_smt_shift                                           (27)
#define SB2_PFUNC_RG4_rgmii1_rxc_smt_mask                                            (0x08000000)
#define SB2_PFUNC_RG4_rgmii1_rxc_smt(data)                                           (0x08000000&((data)<<27))
#define SB2_PFUNC_RG4_rgmii1_rxc_smt_src(data)                                       ((0x08000000&(data))>>27)
#define SB2_PFUNC_RG4_get_rgmii1_rxc_smt(data)                                       ((0x08000000&(data))>>27)
#define SB2_PFUNC_RG4_rgmii1_rxc_e2_shift                                            (26)
#define SB2_PFUNC_RG4_rgmii1_rxc_e2_mask                                             (0x04000000)
#define SB2_PFUNC_RG4_rgmii1_rxc_e2(data)                                            (0x04000000&((data)<<26))
#define SB2_PFUNC_RG4_rgmii1_rxc_e2_src(data)                                        ((0x04000000&(data))>>26)
#define SB2_PFUNC_RG4_get_rgmii1_rxc_e2(data)                                        ((0x04000000&(data))>>26)
#define SB2_PFUNC_RG4_rgmii1_rxc_pud_en_shift                                        (25)
#define SB2_PFUNC_RG4_rgmii1_rxc_pud_en_mask                                         (0x02000000)
#define SB2_PFUNC_RG4_rgmii1_rxc_pud_en(data)                                        (0x02000000&((data)<<25))
#define SB2_PFUNC_RG4_rgmii1_rxc_pud_en_src(data)                                    ((0x02000000&(data))>>25)
#define SB2_PFUNC_RG4_get_rgmii1_rxc_pud_en(data)                                    ((0x02000000&(data))>>25)
#define SB2_PFUNC_RG4_rgmii1_rxc_pud_sel_shift                                       (24)
#define SB2_PFUNC_RG4_rgmii1_rxc_pud_sel_mask                                        (0x01000000)
#define SB2_PFUNC_RG4_rgmii1_rxc_pud_sel(data)                                       (0x01000000&((data)<<24))
#define SB2_PFUNC_RG4_rgmii1_rxc_pud_sel_src(data)                                   ((0x01000000&(data))>>24)
#define SB2_PFUNC_RG4_get_rgmii1_rxc_pud_sel(data)                                   ((0x01000000&(data))>>24)
#define SB2_PFUNC_RG4_rgmii1_txd_3_smt_shift                                         (23)
#define SB2_PFUNC_RG4_rgmii1_txd_3_smt_mask                                          (0x00800000)
#define SB2_PFUNC_RG4_rgmii1_txd_3_smt(data)                                         (0x00800000&((data)<<23))
#define SB2_PFUNC_RG4_rgmii1_txd_3_smt_src(data)                                     ((0x00800000&(data))>>23)
#define SB2_PFUNC_RG4_get_rgmii1_txd_3_smt(data)                                     ((0x00800000&(data))>>23)
#define SB2_PFUNC_RG4_rgmii1_txd_3_e2_shift                                          (22)
#define SB2_PFUNC_RG4_rgmii1_txd_3_e2_mask                                           (0x00400000)
#define SB2_PFUNC_RG4_rgmii1_txd_3_e2(data)                                          (0x00400000&((data)<<22))
#define SB2_PFUNC_RG4_rgmii1_txd_3_e2_src(data)                                      ((0x00400000&(data))>>22)
#define SB2_PFUNC_RG4_get_rgmii1_txd_3_e2(data)                                      ((0x00400000&(data))>>22)
#define SB2_PFUNC_RG4_rgmii1_txd_3_pud_en_shift                                      (21)
#define SB2_PFUNC_RG4_rgmii1_txd_3_pud_en_mask                                       (0x00200000)
#define SB2_PFUNC_RG4_rgmii1_txd_3_pud_en(data)                                      (0x00200000&((data)<<21))
#define SB2_PFUNC_RG4_rgmii1_txd_3_pud_en_src(data)                                  ((0x00200000&(data))>>21)
#define SB2_PFUNC_RG4_get_rgmii1_txd_3_pud_en(data)                                  ((0x00200000&(data))>>21)
#define SB2_PFUNC_RG4_rgmii1_txd_3_pud_sel_shift                                     (20)
#define SB2_PFUNC_RG4_rgmii1_txd_3_pud_sel_mask                                      (0x00100000)
#define SB2_PFUNC_RG4_rgmii1_txd_3_pud_sel(data)                                     (0x00100000&((data)<<20))
#define SB2_PFUNC_RG4_rgmii1_txd_3_pud_sel_src(data)                                 ((0x00100000&(data))>>20)
#define SB2_PFUNC_RG4_get_rgmii1_txd_3_pud_sel(data)                                 ((0x00100000&(data))>>20)
#define SB2_PFUNC_RG4_rgmii1_txd_2_smt_shift                                         (19)
#define SB2_PFUNC_RG4_rgmii1_txd_2_smt_mask                                          (0x00080000)
#define SB2_PFUNC_RG4_rgmii1_txd_2_smt(data)                                         (0x00080000&((data)<<19))
#define SB2_PFUNC_RG4_rgmii1_txd_2_smt_src(data)                                     ((0x00080000&(data))>>19)
#define SB2_PFUNC_RG4_get_rgmii1_txd_2_smt(data)                                     ((0x00080000&(data))>>19)
#define SB2_PFUNC_RG4_rgmii1_txd_2_e2_shift                                          (18)
#define SB2_PFUNC_RG4_rgmii1_txd_2_e2_mask                                           (0x00040000)
#define SB2_PFUNC_RG4_rgmii1_txd_2_e2(data)                                          (0x00040000&((data)<<18))
#define SB2_PFUNC_RG4_rgmii1_txd_2_e2_src(data)                                      ((0x00040000&(data))>>18)
#define SB2_PFUNC_RG4_get_rgmii1_txd_2_e2(data)                                      ((0x00040000&(data))>>18)
#define SB2_PFUNC_RG4_rgmii1_txd_2_pud_en_shift                                      (17)
#define SB2_PFUNC_RG4_rgmii1_txd_2_pud_en_mask                                       (0x00020000)
#define SB2_PFUNC_RG4_rgmii1_txd_2_pud_en(data)                                      (0x00020000&((data)<<17))
#define SB2_PFUNC_RG4_rgmii1_txd_2_pud_en_src(data)                                  ((0x00020000&(data))>>17)
#define SB2_PFUNC_RG4_get_rgmii1_txd_2_pud_en(data)                                  ((0x00020000&(data))>>17)
#define SB2_PFUNC_RG4_rgmii1_txd_2_pud_sel_shift                                     (16)
#define SB2_PFUNC_RG4_rgmii1_txd_2_pud_sel_mask                                      (0x00010000)
#define SB2_PFUNC_RG4_rgmii1_txd_2_pud_sel(data)                                     (0x00010000&((data)<<16))
#define SB2_PFUNC_RG4_rgmii1_txd_2_pud_sel_src(data)                                 ((0x00010000&(data))>>16)
#define SB2_PFUNC_RG4_get_rgmii1_txd_2_pud_sel(data)                                 ((0x00010000&(data))>>16)
#define SB2_PFUNC_RG4_rgmii1_txd_1_smt_shift                                         (15)
#define SB2_PFUNC_RG4_rgmii1_txd_1_smt_mask                                          (0x00008000)
#define SB2_PFUNC_RG4_rgmii1_txd_1_smt(data)                                         (0x00008000&((data)<<15))
#define SB2_PFUNC_RG4_rgmii1_txd_1_smt_src(data)                                     ((0x00008000&(data))>>15)
#define SB2_PFUNC_RG4_get_rgmii1_txd_1_smt(data)                                     ((0x00008000&(data))>>15)
#define SB2_PFUNC_RG4_rgmii1_txd_1_e2_shift                                          (14)
#define SB2_PFUNC_RG4_rgmii1_txd_1_e2_mask                                           (0x00004000)
#define SB2_PFUNC_RG4_rgmii1_txd_1_e2(data)                                          (0x00004000&((data)<<14))
#define SB2_PFUNC_RG4_rgmii1_txd_1_e2_src(data)                                      ((0x00004000&(data))>>14)
#define SB2_PFUNC_RG4_get_rgmii1_txd_1_e2(data)                                      ((0x00004000&(data))>>14)
#define SB2_PFUNC_RG4_rgmii1_txd_1_pud_en_shift                                      (13)
#define SB2_PFUNC_RG4_rgmii1_txd_1_pud_en_mask                                       (0x00002000)
#define SB2_PFUNC_RG4_rgmii1_txd_1_pud_en(data)                                      (0x00002000&((data)<<13))
#define SB2_PFUNC_RG4_rgmii1_txd_1_pud_en_src(data)                                  ((0x00002000&(data))>>13)
#define SB2_PFUNC_RG4_get_rgmii1_txd_1_pud_en(data)                                  ((0x00002000&(data))>>13)
#define SB2_PFUNC_RG4_rgmii1_txd_1_pud_sel_shift                                     (12)
#define SB2_PFUNC_RG4_rgmii1_txd_1_pud_sel_mask                                      (0x00001000)
#define SB2_PFUNC_RG4_rgmii1_txd_1_pud_sel(data)                                     (0x00001000&((data)<<12))
#define SB2_PFUNC_RG4_rgmii1_txd_1_pud_sel_src(data)                                 ((0x00001000&(data))>>12)
#define SB2_PFUNC_RG4_get_rgmii1_txd_1_pud_sel(data)                                 ((0x00001000&(data))>>12)
#define SB2_PFUNC_RG4_rgmii1_txd_0_smt_shift                                         (11)
#define SB2_PFUNC_RG4_rgmii1_txd_0_smt_mask                                          (0x00000800)
#define SB2_PFUNC_RG4_rgmii1_txd_0_smt(data)                                         (0x00000800&((data)<<11))
#define SB2_PFUNC_RG4_rgmii1_txd_0_smt_src(data)                                     ((0x00000800&(data))>>11)
#define SB2_PFUNC_RG4_get_rgmii1_txd_0_smt(data)                                     ((0x00000800&(data))>>11)
#define SB2_PFUNC_RG4_rgmii1_txd_0_e2_shift                                          (10)
#define SB2_PFUNC_RG4_rgmii1_txd_0_e2_mask                                           (0x00000400)
#define SB2_PFUNC_RG4_rgmii1_txd_0_e2(data)                                          (0x00000400&((data)<<10))
#define SB2_PFUNC_RG4_rgmii1_txd_0_e2_src(data)                                      ((0x00000400&(data))>>10)
#define SB2_PFUNC_RG4_get_rgmii1_txd_0_e2(data)                                      ((0x00000400&(data))>>10)
#define SB2_PFUNC_RG4_rgmii1_txd_0_pud_en_shift                                      (9)
#define SB2_PFUNC_RG4_rgmii1_txd_0_pud_en_mask                                       (0x00000200)
#define SB2_PFUNC_RG4_rgmii1_txd_0_pud_en(data)                                      (0x00000200&((data)<<9))
#define SB2_PFUNC_RG4_rgmii1_txd_0_pud_en_src(data)                                  ((0x00000200&(data))>>9)
#define SB2_PFUNC_RG4_get_rgmii1_txd_0_pud_en(data)                                  ((0x00000200&(data))>>9)
#define SB2_PFUNC_RG4_rgmii1_txd_0_pud_sel_shift                                     (8)
#define SB2_PFUNC_RG4_rgmii1_txd_0_pud_sel_mask                                      (0x00000100)
#define SB2_PFUNC_RG4_rgmii1_txd_0_pud_sel(data)                                     (0x00000100&((data)<<8))
#define SB2_PFUNC_RG4_rgmii1_txd_0_pud_sel_src(data)                                 ((0x00000100&(data))>>8)
#define SB2_PFUNC_RG4_get_rgmii1_txd_0_pud_sel(data)                                 ((0x00000100&(data))>>8)
#define SB2_PFUNC_RG4_rgmii1_tx_ctl_smt_shift                                        (7)
#define SB2_PFUNC_RG4_rgmii1_tx_ctl_smt_mask                                         (0x00000080)
#define SB2_PFUNC_RG4_rgmii1_tx_ctl_smt(data)                                        (0x00000080&((data)<<7))
#define SB2_PFUNC_RG4_rgmii1_tx_ctl_smt_src(data)                                    ((0x00000080&(data))>>7)
#define SB2_PFUNC_RG4_get_rgmii1_tx_ctl_smt(data)                                    ((0x00000080&(data))>>7)
#define SB2_PFUNC_RG4_rgmii1_tx_ctl_e2_shift                                         (6)
#define SB2_PFUNC_RG4_rgmii1_tx_ctl_e2_mask                                          (0x00000040)
#define SB2_PFUNC_RG4_rgmii1_tx_ctl_e2(data)                                         (0x00000040&((data)<<6))
#define SB2_PFUNC_RG4_rgmii1_tx_ctl_e2_src(data)                                     ((0x00000040&(data))>>6)
#define SB2_PFUNC_RG4_get_rgmii1_tx_ctl_e2(data)                                     ((0x00000040&(data))>>6)
#define SB2_PFUNC_RG4_rgmii1_tx_ctl_pud_en_shift                                     (5)
#define SB2_PFUNC_RG4_rgmii1_tx_ctl_pud_en_mask                                      (0x00000020)
#define SB2_PFUNC_RG4_rgmii1_tx_ctl_pud_en(data)                                     (0x00000020&((data)<<5))
#define SB2_PFUNC_RG4_rgmii1_tx_ctl_pud_en_src(data)                                 ((0x00000020&(data))>>5)
#define SB2_PFUNC_RG4_get_rgmii1_tx_ctl_pud_en(data)                                 ((0x00000020&(data))>>5)
#define SB2_PFUNC_RG4_rgmii1_tx_ctl_pud_sel_shift                                    (4)
#define SB2_PFUNC_RG4_rgmii1_tx_ctl_pud_sel_mask                                     (0x00000010)
#define SB2_PFUNC_RG4_rgmii1_tx_ctl_pud_sel(data)                                    (0x00000010&((data)<<4))
#define SB2_PFUNC_RG4_rgmii1_tx_ctl_pud_sel_src(data)                                ((0x00000010&(data))>>4)
#define SB2_PFUNC_RG4_get_rgmii1_tx_ctl_pud_sel(data)                                ((0x00000010&(data))>>4)
#define SB2_PFUNC_RG4_rgmii1_txc_smt_shift                                           (3)
#define SB2_PFUNC_RG4_rgmii1_txc_smt_mask                                            (0x00000008)
#define SB2_PFUNC_RG4_rgmii1_txc_smt(data)                                           (0x00000008&((data)<<3))
#define SB2_PFUNC_RG4_rgmii1_txc_smt_src(data)                                       ((0x00000008&(data))>>3)
#define SB2_PFUNC_RG4_get_rgmii1_txc_smt(data)                                       ((0x00000008&(data))>>3)
#define SB2_PFUNC_RG4_rgmii1_txc_e2_shift                                            (2)
#define SB2_PFUNC_RG4_rgmii1_txc_e2_mask                                             (0x00000004)
#define SB2_PFUNC_RG4_rgmii1_txc_e2(data)                                            (0x00000004&((data)<<2))
#define SB2_PFUNC_RG4_rgmii1_txc_e2_src(data)                                        ((0x00000004&(data))>>2)
#define SB2_PFUNC_RG4_get_rgmii1_txc_e2(data)                                        ((0x00000004&(data))>>2)
#define SB2_PFUNC_RG4_rgmii1_txc_pud_en_shift                                        (1)
#define SB2_PFUNC_RG4_rgmii1_txc_pud_en_mask                                         (0x00000002)
#define SB2_PFUNC_RG4_rgmii1_txc_pud_en(data)                                        (0x00000002&((data)<<1))
#define SB2_PFUNC_RG4_rgmii1_txc_pud_en_src(data)                                    ((0x00000002&(data))>>1)
#define SB2_PFUNC_RG4_get_rgmii1_txc_pud_en(data)                                    ((0x00000002&(data))>>1)
#define SB2_PFUNC_RG4_rgmii1_txc_pud_sel_shift                                       (0)
#define SB2_PFUNC_RG4_rgmii1_txc_pud_sel_mask                                        (0x00000001)
#define SB2_PFUNC_RG4_rgmii1_txc_pud_sel(data)                                       (0x00000001&((data)<<0))
#define SB2_PFUNC_RG4_rgmii1_txc_pud_sel_src(data)                                   ((0x00000001&(data))>>0)
#define SB2_PFUNC_RG4_get_rgmii1_txc_pud_sel(data)                                   ((0x00000001&(data))>>0)


#define SB2_PFUNC_RG5                                                                0x9801A978
#define SB2_PFUNC_RG5_reg_addr                                                       "0x9801A978"
#define SB2_PFUNC_RG5_reg                                                            0x9801A978
#define set_SB2_PFUNC_RG5_reg(data)   (*((volatile unsigned int*) SB2_PFUNC_RG5_reg)=data)
#define get_SB2_PFUNC_RG5_reg   (*((volatile unsigned int*) SB2_PFUNC_RG5_reg))
#define SB2_PFUNC_RG5_inst_adr                                                       "0x005E"
#define SB2_PFUNC_RG5_inst                                                           0x005E
#define SB2_PFUNC_RG5_rgmii1_bias_mode2_shift                                        (31)
#define SB2_PFUNC_RG5_rgmii1_bias_mode2_mask                                         (0x80000000)
#define SB2_PFUNC_RG5_rgmii1_bias_mode2(data)                                        (0x80000000&((data)<<31))
#define SB2_PFUNC_RG5_rgmii1_bias_mode2_src(data)                                    ((0x80000000&(data))>>31)
#define SB2_PFUNC_RG5_get_rgmii1_bias_mode2(data)                                    ((0x80000000&(data))>>31)
#define SB2_PFUNC_RG5_rgmii1_bias_mode_shift                                         (30)
#define SB2_PFUNC_RG5_rgmii1_bias_mode_mask                                          (0x40000000)
#define SB2_PFUNC_RG5_rgmii1_bias_mode(data)                                         (0x40000000&((data)<<30))
#define SB2_PFUNC_RG5_rgmii1_bias_mode_src(data)                                     ((0x40000000&(data))>>30)
#define SB2_PFUNC_RG5_get_rgmii1_bias_mode(data)                                     ((0x40000000&(data))>>30)
#define SB2_PFUNC_RG5_rgmii1_bias_dn_shift                                           (27)
#define SB2_PFUNC_RG5_rgmii1_bias_dn_mask                                            (0x38000000)
#define SB2_PFUNC_RG5_rgmii1_bias_dn(data)                                           (0x38000000&((data)<<27))
#define SB2_PFUNC_RG5_rgmii1_bias_dn_src(data)                                       ((0x38000000&(data))>>27)
#define SB2_PFUNC_RG5_get_rgmii1_bias_dn(data)                                       ((0x38000000&(data))>>27)
#define SB2_PFUNC_RG5_rgmii1_bias_dp_shift                                           (24)
#define SB2_PFUNC_RG5_rgmii1_bias_dp_mask                                            (0x07000000)
#define SB2_PFUNC_RG5_rgmii1_bias_dp(data)                                           (0x07000000&((data)<<24))
#define SB2_PFUNC_RG5_rgmii1_bias_dp_src(data)                                       ((0x07000000&(data))>>24)
#define SB2_PFUNC_RG5_get_rgmii1_bias_dp(data)                                       ((0x07000000&(data))>>24)
#define SB2_PFUNC_RG5_rgmii1_rxd_3_smt_shift                                         (15)
#define SB2_PFUNC_RG5_rgmii1_rxd_3_smt_mask                                          (0x00008000)
#define SB2_PFUNC_RG5_rgmii1_rxd_3_smt(data)                                         (0x00008000&((data)<<15))
#define SB2_PFUNC_RG5_rgmii1_rxd_3_smt_src(data)                                     ((0x00008000&(data))>>15)
#define SB2_PFUNC_RG5_get_rgmii1_rxd_3_smt(data)                                     ((0x00008000&(data))>>15)
#define SB2_PFUNC_RG5_rgmii1_rxd_3_e2_shift                                          (14)
#define SB2_PFUNC_RG5_rgmii1_rxd_3_e2_mask                                           (0x00004000)
#define SB2_PFUNC_RG5_rgmii1_rxd_3_e2(data)                                          (0x00004000&((data)<<14))
#define SB2_PFUNC_RG5_rgmii1_rxd_3_e2_src(data)                                      ((0x00004000&(data))>>14)
#define SB2_PFUNC_RG5_get_rgmii1_rxd_3_e2(data)                                      ((0x00004000&(data))>>14)
#define SB2_PFUNC_RG5_rgmii1_rxd_3_pud_en_shift                                      (13)
#define SB2_PFUNC_RG5_rgmii1_rxd_3_pud_en_mask                                       (0x00002000)
#define SB2_PFUNC_RG5_rgmii1_rxd_3_pud_en(data)                                      (0x00002000&((data)<<13))
#define SB2_PFUNC_RG5_rgmii1_rxd_3_pud_en_src(data)                                  ((0x00002000&(data))>>13)
#define SB2_PFUNC_RG5_get_rgmii1_rxd_3_pud_en(data)                                  ((0x00002000&(data))>>13)
#define SB2_PFUNC_RG5_rgmii1_rxd_3_pud_sel_shift                                     (12)
#define SB2_PFUNC_RG5_rgmii1_rxd_3_pud_sel_mask                                      (0x00001000)
#define SB2_PFUNC_RG5_rgmii1_rxd_3_pud_sel(data)                                     (0x00001000&((data)<<12))
#define SB2_PFUNC_RG5_rgmii1_rxd_3_pud_sel_src(data)                                 ((0x00001000&(data))>>12)
#define SB2_PFUNC_RG5_get_rgmii1_rxd_3_pud_sel(data)                                 ((0x00001000&(data))>>12)
#define SB2_PFUNC_RG5_rgmii1_rxd_2_smt_shift                                         (11)
#define SB2_PFUNC_RG5_rgmii1_rxd_2_smt_mask                                          (0x00000800)
#define SB2_PFUNC_RG5_rgmii1_rxd_2_smt(data)                                         (0x00000800&((data)<<11))
#define SB2_PFUNC_RG5_rgmii1_rxd_2_smt_src(data)                                     ((0x00000800&(data))>>11)
#define SB2_PFUNC_RG5_get_rgmii1_rxd_2_smt(data)                                     ((0x00000800&(data))>>11)
#define SB2_PFUNC_RG5_rgmii1_rxd_2_e2_shift                                          (10)
#define SB2_PFUNC_RG5_rgmii1_rxd_2_e2_mask                                           (0x00000400)
#define SB2_PFUNC_RG5_rgmii1_rxd_2_e2(data)                                          (0x00000400&((data)<<10))
#define SB2_PFUNC_RG5_rgmii1_rxd_2_e2_src(data)                                      ((0x00000400&(data))>>10)
#define SB2_PFUNC_RG5_get_rgmii1_rxd_2_e2(data)                                      ((0x00000400&(data))>>10)
#define SB2_PFUNC_RG5_rgmii1_rxd_2_pud_en_shift                                      (9)
#define SB2_PFUNC_RG5_rgmii1_rxd_2_pud_en_mask                                       (0x00000200)
#define SB2_PFUNC_RG5_rgmii1_rxd_2_pud_en(data)                                      (0x00000200&((data)<<9))
#define SB2_PFUNC_RG5_rgmii1_rxd_2_pud_en_src(data)                                  ((0x00000200&(data))>>9)
#define SB2_PFUNC_RG5_get_rgmii1_rxd_2_pud_en(data)                                  ((0x00000200&(data))>>9)
#define SB2_PFUNC_RG5_rgmii1_rxd_2_pud_sel_shift                                     (8)
#define SB2_PFUNC_RG5_rgmii1_rxd_2_pud_sel_mask                                      (0x00000100)
#define SB2_PFUNC_RG5_rgmii1_rxd_2_pud_sel(data)                                     (0x00000100&((data)<<8))
#define SB2_PFUNC_RG5_rgmii1_rxd_2_pud_sel_src(data)                                 ((0x00000100&(data))>>8)
#define SB2_PFUNC_RG5_get_rgmii1_rxd_2_pud_sel(data)                                 ((0x00000100&(data))>>8)
#define SB2_PFUNC_RG5_rgmii1_rxd_1_smt_shift                                         (7)
#define SB2_PFUNC_RG5_rgmii1_rxd_1_smt_mask                                          (0x00000080)
#define SB2_PFUNC_RG5_rgmii1_rxd_1_smt(data)                                         (0x00000080&((data)<<7))
#define SB2_PFUNC_RG5_rgmii1_rxd_1_smt_src(data)                                     ((0x00000080&(data))>>7)
#define SB2_PFUNC_RG5_get_rgmii1_rxd_1_smt(data)                                     ((0x00000080&(data))>>7)
#define SB2_PFUNC_RG5_rgmii1_rxd_1_e2_shift                                          (6)
#define SB2_PFUNC_RG5_rgmii1_rxd_1_e2_mask                                           (0x00000040)
#define SB2_PFUNC_RG5_rgmii1_rxd_1_e2(data)                                          (0x00000040&((data)<<6))
#define SB2_PFUNC_RG5_rgmii1_rxd_1_e2_src(data)                                      ((0x00000040&(data))>>6)
#define SB2_PFUNC_RG5_get_rgmii1_rxd_1_e2(data)                                      ((0x00000040&(data))>>6)
#define SB2_PFUNC_RG5_rgmii1_rxd_1_pud_en_shift                                      (5)
#define SB2_PFUNC_RG5_rgmii1_rxd_1_pud_en_mask                                       (0x00000020)
#define SB2_PFUNC_RG5_rgmii1_rxd_1_pud_en(data)                                      (0x00000020&((data)<<5))
#define SB2_PFUNC_RG5_rgmii1_rxd_1_pud_en_src(data)                                  ((0x00000020&(data))>>5)
#define SB2_PFUNC_RG5_get_rgmii1_rxd_1_pud_en(data)                                  ((0x00000020&(data))>>5)
#define SB2_PFUNC_RG5_rgmii1_rxd_1_pud_sel_shift                                     (4)
#define SB2_PFUNC_RG5_rgmii1_rxd_1_pud_sel_mask                                      (0x00000010)
#define SB2_PFUNC_RG5_rgmii1_rxd_1_pud_sel(data)                                     (0x00000010&((data)<<4))
#define SB2_PFUNC_RG5_rgmii1_rxd_1_pud_sel_src(data)                                 ((0x00000010&(data))>>4)
#define SB2_PFUNC_RG5_get_rgmii1_rxd_1_pud_sel(data)                                 ((0x00000010&(data))>>4)
#define SB2_PFUNC_RG5_rgmii1_rxd_0_smt_shift                                         (3)
#define SB2_PFUNC_RG5_rgmii1_rxd_0_smt_mask                                          (0x00000008)
#define SB2_PFUNC_RG5_rgmii1_rxd_0_smt(data)                                         (0x00000008&((data)<<3))
#define SB2_PFUNC_RG5_rgmii1_rxd_0_smt_src(data)                                     ((0x00000008&(data))>>3)
#define SB2_PFUNC_RG5_get_rgmii1_rxd_0_smt(data)                                     ((0x00000008&(data))>>3)
#define SB2_PFUNC_RG5_rgmii1_rxd_0_e2_shift                                          (2)
#define SB2_PFUNC_RG5_rgmii1_rxd_0_e2_mask                                           (0x00000004)
#define SB2_PFUNC_RG5_rgmii1_rxd_0_e2(data)                                          (0x00000004&((data)<<2))
#define SB2_PFUNC_RG5_rgmii1_rxd_0_e2_src(data)                                      ((0x00000004&(data))>>2)
#define SB2_PFUNC_RG5_get_rgmii1_rxd_0_e2(data)                                      ((0x00000004&(data))>>2)
#define SB2_PFUNC_RG5_rgmii1_rxd_0_pud_en_shift                                      (1)
#define SB2_PFUNC_RG5_rgmii1_rxd_0_pud_en_mask                                       (0x00000002)
#define SB2_PFUNC_RG5_rgmii1_rxd_0_pud_en(data)                                      (0x00000002&((data)<<1))
#define SB2_PFUNC_RG5_rgmii1_rxd_0_pud_en_src(data)                                  ((0x00000002&(data))>>1)
#define SB2_PFUNC_RG5_get_rgmii1_rxd_0_pud_en(data)                                  ((0x00000002&(data))>>1)
#define SB2_PFUNC_RG5_rgmii1_rxd_0_pud_sel_shift                                     (0)
#define SB2_PFUNC_RG5_rgmii1_rxd_0_pud_sel_mask                                      (0x00000001)
#define SB2_PFUNC_RG5_rgmii1_rxd_0_pud_sel(data)                                     (0x00000001&((data)<<0))
#define SB2_PFUNC_RG5_rgmii1_rxd_0_pud_sel_src(data)                                 ((0x00000001&(data))>>0)
#define SB2_PFUNC_RG5_get_rgmii1_rxd_0_pud_sel(data)                                 ((0x00000001&(data))>>0)


#define SB2_MUXPAD_RG1                                                               0x9801A97C
#define SB2_MUXPAD_RG1_reg_addr                                                      "0x9801A97C"
#define SB2_MUXPAD_RG1_reg                                                           0x9801A97C
#define set_SB2_MUXPAD_RG1_reg(data)   (*((volatile unsigned int*) SB2_MUXPAD_RG1_reg)=data)
#define get_SB2_MUXPAD_RG1_reg   (*((volatile unsigned int*) SB2_MUXPAD_RG1_reg))
#define SB2_MUXPAD_RG1_inst_adr                                                      "0x005F"
#define SB2_MUXPAD_RG1_inst                                                          0x005F
#define SB2_MUXPAD_RG1_rgmii1_mdc_shift                                              (26)
#define SB2_MUXPAD_RG1_rgmii1_mdc_mask                                               (0x0C000000)
#define SB2_MUXPAD_RG1_rgmii1_mdc(data)                                              (0x0C000000&((data)<<26))
#define SB2_MUXPAD_RG1_rgmii1_mdc_src(data)                                          ((0x0C000000&(data))>>26)
#define SB2_MUXPAD_RG1_get_rgmii1_mdc(data)                                          ((0x0C000000&(data))>>26)
#define SB2_MUXPAD_RG1_rgmii1_mdio_shift                                             (24)
#define SB2_MUXPAD_RG1_rgmii1_mdio_mask                                              (0x03000000)
#define SB2_MUXPAD_RG1_rgmii1_mdio(data)                                             (0x03000000&((data)<<24))
#define SB2_MUXPAD_RG1_rgmii1_mdio_src(data)                                         ((0x03000000&(data))>>24)
#define SB2_MUXPAD_RG1_get_rgmii1_mdio(data)                                         ((0x03000000&(data))>>24)
#define SB2_MUXPAD_RG1_rgmii1_rxd_3_shift                                            (22)
#define SB2_MUXPAD_RG1_rgmii1_rxd_3_mask                                             (0x00C00000)
#define SB2_MUXPAD_RG1_rgmii1_rxd_3(data)                                            (0x00C00000&((data)<<22))
#define SB2_MUXPAD_RG1_rgmii1_rxd_3_src(data)                                        ((0x00C00000&(data))>>22)
#define SB2_MUXPAD_RG1_get_rgmii1_rxd_3(data)                                        ((0x00C00000&(data))>>22)
#define SB2_MUXPAD_RG1_rgmii1_rxd_2_shift                                            (20)
#define SB2_MUXPAD_RG1_rgmii1_rxd_2_mask                                             (0x00300000)
#define SB2_MUXPAD_RG1_rgmii1_rxd_2(data)                                            (0x00300000&((data)<<20))
#define SB2_MUXPAD_RG1_rgmii1_rxd_2_src(data)                                        ((0x00300000&(data))>>20)
#define SB2_MUXPAD_RG1_get_rgmii1_rxd_2(data)                                        ((0x00300000&(data))>>20)
#define SB2_MUXPAD_RG1_rgmii1_rxd_1_shift                                            (18)
#define SB2_MUXPAD_RG1_rgmii1_rxd_1_mask                                             (0x000C0000)
#define SB2_MUXPAD_RG1_rgmii1_rxd_1(data)                                            (0x000C0000&((data)<<18))
#define SB2_MUXPAD_RG1_rgmii1_rxd_1_src(data)                                        ((0x000C0000&(data))>>18)
#define SB2_MUXPAD_RG1_get_rgmii1_rxd_1(data)                                        ((0x000C0000&(data))>>18)
#define SB2_MUXPAD_RG1_rgmii1_rxd_0_shift                                            (16)
#define SB2_MUXPAD_RG1_rgmii1_rxd_0_mask                                             (0x00030000)
#define SB2_MUXPAD_RG1_rgmii1_rxd_0(data)                                            (0x00030000&((data)<<16))
#define SB2_MUXPAD_RG1_rgmii1_rxd_0_src(data)                                        ((0x00030000&(data))>>16)
#define SB2_MUXPAD_RG1_get_rgmii1_rxd_0(data)                                        ((0x00030000&(data))>>16)
#define SB2_MUXPAD_RG1_rgmii1_rx_ctl_shift                                           (14)
#define SB2_MUXPAD_RG1_rgmii1_rx_ctl_mask                                            (0x0000C000)
#define SB2_MUXPAD_RG1_rgmii1_rx_ctl(data)                                           (0x0000C000&((data)<<14))
#define SB2_MUXPAD_RG1_rgmii1_rx_ctl_src(data)                                       ((0x0000C000&(data))>>14)
#define SB2_MUXPAD_RG1_get_rgmii1_rx_ctl(data)                                       ((0x0000C000&(data))>>14)
#define SB2_MUXPAD_RG1_rgmii1_rxc_shift                                              (12)
#define SB2_MUXPAD_RG1_rgmii1_rxc_mask                                               (0x00003000)
#define SB2_MUXPAD_RG1_rgmii1_rxc(data)                                              (0x00003000&((data)<<12))
#define SB2_MUXPAD_RG1_rgmii1_rxc_src(data)                                          ((0x00003000&(data))>>12)
#define SB2_MUXPAD_RG1_get_rgmii1_rxc(data)                                          ((0x00003000&(data))>>12)
#define SB2_MUXPAD_RG1_rgmii1_txd_3_shift                                            (10)
#define SB2_MUXPAD_RG1_rgmii1_txd_3_mask                                             (0x00000C00)
#define SB2_MUXPAD_RG1_rgmii1_txd_3(data)                                            (0x00000C00&((data)<<10))
#define SB2_MUXPAD_RG1_rgmii1_txd_3_src(data)                                        ((0x00000C00&(data))>>10)
#define SB2_MUXPAD_RG1_get_rgmii1_txd_3(data)                                        ((0x00000C00&(data))>>10)
#define SB2_MUXPAD_RG1_rgmii1_txd_2_shift                                            (8)
#define SB2_MUXPAD_RG1_rgmii1_txd_2_mask                                             (0x00000300)
#define SB2_MUXPAD_RG1_rgmii1_txd_2(data)                                            (0x00000300&((data)<<8))
#define SB2_MUXPAD_RG1_rgmii1_txd_2_src(data)                                        ((0x00000300&(data))>>8)
#define SB2_MUXPAD_RG1_get_rgmii1_txd_2(data)                                        ((0x00000300&(data))>>8)
#define SB2_MUXPAD_RG1_rgmii1_txd_1_shift                                            (6)
#define SB2_MUXPAD_RG1_rgmii1_txd_1_mask                                             (0x000000C0)
#define SB2_MUXPAD_RG1_rgmii1_txd_1(data)                                            (0x000000C0&((data)<<6))
#define SB2_MUXPAD_RG1_rgmii1_txd_1_src(data)                                        ((0x000000C0&(data))>>6)
#define SB2_MUXPAD_RG1_get_rgmii1_txd_1(data)                                        ((0x000000C0&(data))>>6)
#define SB2_MUXPAD_RG1_rgmii1_txd_0_shift                                            (4)
#define SB2_MUXPAD_RG1_rgmii1_txd_0_mask                                             (0x00000030)
#define SB2_MUXPAD_RG1_rgmii1_txd_0(data)                                            (0x00000030&((data)<<4))
#define SB2_MUXPAD_RG1_rgmii1_txd_0_src(data)                                        ((0x00000030&(data))>>4)
#define SB2_MUXPAD_RG1_get_rgmii1_txd_0(data)                                        ((0x00000030&(data))>>4)
#define SB2_MUXPAD_RG1_rgmii1_tx_ctl_shift                                           (2)
#define SB2_MUXPAD_RG1_rgmii1_tx_ctl_mask                                            (0x0000000C)
#define SB2_MUXPAD_RG1_rgmii1_tx_ctl(data)                                           (0x0000000C&((data)<<2))
#define SB2_MUXPAD_RG1_rgmii1_tx_ctl_src(data)                                       ((0x0000000C&(data))>>2)
#define SB2_MUXPAD_RG1_get_rgmii1_tx_ctl(data)                                       ((0x0000000C&(data))>>2)
#define SB2_MUXPAD_RG1_rgmii1_txc_shift                                              (0)
#define SB2_MUXPAD_RG1_rgmii1_txc_mask                                               (0x00000003)
#define SB2_MUXPAD_RG1_rgmii1_txc(data)                                              (0x00000003&((data)<<0))
#define SB2_MUXPAD_RG1_rgmii1_txc_src(data)                                          ((0x00000003&(data))>>0)
#define SB2_MUXPAD_RG1_get_rgmii1_txc(data)                                          ((0x00000003&(data))>>0)


#define SB2_SATA_PHY_CTRL                                                            0x9801A980
#define SB2_SATA_PHY_CTRL_reg_addr                                                   "0x9801A980"
#define SB2_SATA_PHY_CTRL_reg                                                        0x9801A980
#define set_SB2_SATA_PHY_CTRL_reg(data)   (*((volatile unsigned int*) SB2_SATA_PHY_CTRL_reg)=data)
#define get_SB2_SATA_PHY_CTRL_reg   (*((volatile unsigned int*) SB2_SATA_PHY_CTRL_reg))
#define SB2_SATA_PHY_CTRL_inst_adr                                                   "0x0060"
#define SB2_SATA_PHY_CTRL_inst                                                       0x0060
#define SB2_SATA_PHY_CTRL_sata_sgmii_sel_shift                                       (8)
#define SB2_SATA_PHY_CTRL_sata_sgmii_sel_mask                                        (0x00000100)
#define SB2_SATA_PHY_CTRL_sata_sgmii_sel(data)                                       (0x00000100&((data)<<8))
#define SB2_SATA_PHY_CTRL_sata_sgmii_sel_src(data)                                   ((0x00000100&(data))>>8)
#define SB2_SATA_PHY_CTRL_get_sata_sgmii_sel(data)                                   ((0x00000100&(data))>>8)
#define SB2_SATA_PHY_CTRL_isolate_sata_sgmii_1_shift                                 (7)
#define SB2_SATA_PHY_CTRL_isolate_sata_sgmii_1_mask                                  (0x00000080)
#define SB2_SATA_PHY_CTRL_isolate_sata_sgmii_1(data)                                 (0x00000080&((data)<<7))
#define SB2_SATA_PHY_CTRL_isolate_sata_sgmii_1_src(data)                             ((0x00000080&(data))>>7)
#define SB2_SATA_PHY_CTRL_get_isolate_sata_sgmii_1(data)                             ((0x00000080&(data))>>7)
#define SB2_SATA_PHY_CTRL_isolate_sata_sgmii_0_shift                                 (6)
#define SB2_SATA_PHY_CTRL_isolate_sata_sgmii_0_mask                                  (0x00000040)
#define SB2_SATA_PHY_CTRL_isolate_sata_sgmii_0(data)                                 (0x00000040&((data)<<6))
#define SB2_SATA_PHY_CTRL_isolate_sata_sgmii_0_src(data)                             ((0x00000040&(data))>>6)
#define SB2_SATA_PHY_CTRL_get_isolate_sata_sgmii_0(data)                             ((0x00000040&(data))>>6)
#define SB2_SATA_PHY_CTRL_sata_rx50_link_1_shift                                     (5)
#define SB2_SATA_PHY_CTRL_sata_rx50_link_1_mask                                      (0x00000020)
#define SB2_SATA_PHY_CTRL_sata_rx50_link_1(data)                                     (0x00000020&((data)<<5))
#define SB2_SATA_PHY_CTRL_sata_rx50_link_1_src(data)                                 ((0x00000020&(data))>>5)
#define SB2_SATA_PHY_CTRL_get_sata_rx50_link_1(data)                                 ((0x00000020&(data))>>5)
#define SB2_SATA_PHY_CTRL_sata_rx50_link_0_shift                                     (4)
#define SB2_SATA_PHY_CTRL_sata_rx50_link_0_mask                                      (0x00000010)
#define SB2_SATA_PHY_CTRL_sata_rx50_link_0(data)                                     (0x00000010&((data)<<4))
#define SB2_SATA_PHY_CTRL_sata_rx50_link_0_src(data)                                 ((0x00000010&(data))>>4)
#define SB2_SATA_PHY_CTRL_get_sata_rx50_link_0(data)                                 ((0x00000010&(data))>>4)
#define SB2_SATA_PHY_CTRL_sata_mbias_en_1_shift                                      (3)
#define SB2_SATA_PHY_CTRL_sata_mbias_en_1_mask                                       (0x00000008)
#define SB2_SATA_PHY_CTRL_sata_mbias_en_1(data)                                      (0x00000008&((data)<<3))
#define SB2_SATA_PHY_CTRL_sata_mbias_en_1_src(data)                                  ((0x00000008&(data))>>3)
#define SB2_SATA_PHY_CTRL_get_sata_mbias_en_1(data)                                  ((0x00000008&(data))>>3)
#define SB2_SATA_PHY_CTRL_sata_mbias_en_0_shift                                      (2)
#define SB2_SATA_PHY_CTRL_sata_mbias_en_0_mask                                       (0x00000004)
#define SB2_SATA_PHY_CTRL_sata_mbias_en_0(data)                                      (0x00000004&((data)<<2))
#define SB2_SATA_PHY_CTRL_sata_mbias_en_0_src(data)                                  ((0x00000004&(data))>>2)
#define SB2_SATA_PHY_CTRL_get_sata_mbias_en_0(data)                                  ((0x00000004&(data))>>2)
#define SB2_SATA_PHY_CTRL_sata_bg_en_1_shift                                         (1)
#define SB2_SATA_PHY_CTRL_sata_bg_en_1_mask                                          (0x00000002)
#define SB2_SATA_PHY_CTRL_sata_bg_en_1(data)                                         (0x00000002&((data)<<1))
#define SB2_SATA_PHY_CTRL_sata_bg_en_1_src(data)                                     ((0x00000002&(data))>>1)
#define SB2_SATA_PHY_CTRL_get_sata_bg_en_1(data)                                     ((0x00000002&(data))>>1)
#define SB2_SATA_PHY_CTRL_sata_bg_en_0_shift                                         (0)
#define SB2_SATA_PHY_CTRL_sata_bg_en_0_mask                                          (0x00000001)
#define SB2_SATA_PHY_CTRL_sata_bg_en_0(data)                                         (0x00000001&((data)<<0))
#define SB2_SATA_PHY_CTRL_sata_bg_en_0_src(data)                                     ((0x00000001&(data))>>0)
#define SB2_SATA_PHY_CTRL_get_sata_bg_en_0(data)                                     ((0x00000001&(data))>>0)


#define SB2_RNG_CTRL                                                                 0x9801AA00
#define SB2_RNG_CTRL_reg_addr                                                        "0x9801AA00"
#define SB2_RNG_CTRL_reg                                                             0x9801AA00
#define set_SB2_RNG_CTRL_reg(data)   (*((volatile unsigned int*) SB2_RNG_CTRL_reg)=data)
#define get_SB2_RNG_CTRL_reg   (*((volatile unsigned int*) SB2_RNG_CTRL_reg))
#define SB2_RNG_CTRL_inst_adr                                                        "0x0080"
#define SB2_RNG_CTRL_inst                                                            0x0080
#define SB2_RNG_CTRL_lfsr_mode_shift                                                 (17)
#define SB2_RNG_CTRL_lfsr_mode_mask                                                  (0x00020000)
#define SB2_RNG_CTRL_lfsr_mode(data)                                                 (0x00020000&((data)<<17))
#define SB2_RNG_CTRL_lfsr_mode_src(data)                                             ((0x00020000&(data))>>17)
#define SB2_RNG_CTRL_get_lfsr_mode(data)                                             ((0x00020000&(data))>>17)
#define SB2_RNG_CTRL_lfsr_bypass_1_shift                                             (16)
#define SB2_RNG_CTRL_lfsr_bypass_1_mask                                              (0x00010000)
#define SB2_RNG_CTRL_lfsr_bypass_1(data)                                             (0x00010000&((data)<<16))
#define SB2_RNG_CTRL_lfsr_bypass_1_src(data)                                         ((0x00010000&(data))>>16)
#define SB2_RNG_CTRL_get_lfsr_bypass_1(data)                                         ((0x00010000&(data))>>16)
#define SB2_RNG_CTRL_dbg1_sel_shift                                                  (12)
#define SB2_RNG_CTRL_dbg1_sel_mask                                                   (0x0000F000)
#define SB2_RNG_CTRL_dbg1_sel(data)                                                  (0x0000F000&((data)<<12))
#define SB2_RNG_CTRL_dbg1_sel_src(data)                                              ((0x0000F000&(data))>>12)
#define SB2_RNG_CTRL_get_dbg1_sel(data)                                              ((0x0000F000&(data))>>12)
#define SB2_RNG_CTRL_dbg0_sel_shift                                                  (8)
#define SB2_RNG_CTRL_dbg0_sel_mask                                                   (0x00000F00)
#define SB2_RNG_CTRL_dbg0_sel(data)                                                  (0x00000F00&((data)<<8))
#define SB2_RNG_CTRL_dbg0_sel_src(data)                                              ((0x00000F00&(data))>>8)
#define SB2_RNG_CTRL_get_dbg0_sel(data)                                              ((0x00000F00&(data))>>8)
#define SB2_RNG_CTRL_corrector_imode_shift                                           (5)
#define SB2_RNG_CTRL_corrector_imode_mask                                            (0x00000020)
#define SB2_RNG_CTRL_corrector_imode(data)                                           (0x00000020&((data)<<5))
#define SB2_RNG_CTRL_corrector_imode_src(data)                                       ((0x00000020&(data))>>5)
#define SB2_RNG_CTRL_get_corrector_imode(data)                                       ((0x00000020&(data))>>5)
#define SB2_RNG_CTRL_rng_cali_srst_shift                                             (3)
#define SB2_RNG_CTRL_rng_cali_srst_mask                                              (0x00000008)
#define SB2_RNG_CTRL_rng_cali_srst(data)                                             (0x00000008&((data)<<3))
#define SB2_RNG_CTRL_rng_cali_srst_src(data)                                         ((0x00000008&(data))>>3)
#define SB2_RNG_CTRL_get_rng_cali_srst(data)                                         ((0x00000008&(data))>>3)
#define SB2_RNG_CTRL_corrector_bypass_shift                                          (2)
#define SB2_RNG_CTRL_corrector_bypass_mask                                           (0x00000004)
#define SB2_RNG_CTRL_corrector_bypass(data)                                          (0x00000004&((data)<<2))
#define SB2_RNG_CTRL_corrector_bypass_src(data)                                      ((0x00000004&(data))>>2)
#define SB2_RNG_CTRL_get_corrector_bypass(data)                                      ((0x00000004&(data))>>2)
#define SB2_RNG_CTRL_clk_hf_sel_shift                                                (1)
#define SB2_RNG_CTRL_clk_hf_sel_mask                                                 (0x00000002)
#define SB2_RNG_CTRL_clk_hf_sel(data)                                                (0x00000002&((data)<<1))
#define SB2_RNG_CTRL_clk_hf_sel_src(data)                                            ((0x00000002&(data))>>1)
#define SB2_RNG_CTRL_get_clk_hf_sel(data)                                            ((0x00000002&(data))>>1)
#define SB2_RNG_CTRL_rng_srst_shift                                                  (0)
#define SB2_RNG_CTRL_rng_srst_mask                                                   (0x00000001)
#define SB2_RNG_CTRL_rng_srst(data)                                                  (0x00000001&((data)<<0))
#define SB2_RNG_CTRL_rng_srst_src(data)                                              ((0x00000001&(data))>>0)
#define SB2_RNG_CTRL_get_rng_srst(data)                                              ((0x00000001&(data))>>0)


#define SB2_RNG_ANALOG                                                               0x9801AA14
#define SB2_RNG_ANALOG_reg_addr                                                      "0x9801AA14"
#define SB2_RNG_ANALOG_reg                                                           0x9801AA14
#define set_SB2_RNG_ANALOG_reg(data)   (*((volatile unsigned int*) SB2_RNG_ANALOG_reg)=data)
#define get_SB2_RNG_ANALOG_reg   (*((volatile unsigned int*) SB2_RNG_ANALOG_reg))
#define SB2_RNG_ANALOG_inst_adr                                                      "0x0085"
#define SB2_RNG_ANALOG_inst                                                          0x0085
#define SB2_RNG_ANALOG_rosc_d_shift                                                  (12)
#define SB2_RNG_ANALOG_rosc_d_mask                                                   (0x0000F000)
#define SB2_RNG_ANALOG_rosc_d(data)                                                  (0x0000F000&((data)<<12))
#define SB2_RNG_ANALOG_rosc_d_src(data)                                              ((0x0000F000&(data))>>12)
#define SB2_RNG_ANALOG_get_rosc_d(data)                                              ((0x0000F000&(data))>>12)
#define SB2_RNG_ANALOG_rosc_res_shift                                                (10)
#define SB2_RNG_ANALOG_rosc_res_mask                                                 (0x00000C00)
#define SB2_RNG_ANALOG_rosc_res(data)                                                (0x00000C00&((data)<<10))
#define SB2_RNG_ANALOG_rosc_res_src(data)                                            ((0x00000C00&(data))>>10)
#define SB2_RNG_ANALOG_get_rosc_res(data)                                            ((0x00000C00&(data))>>10)
#define SB2_RNG_ANALOG_rosc_div_shift                                                (8)
#define SB2_RNG_ANALOG_rosc_div_mask                                                 (0x00000300)
#define SB2_RNG_ANALOG_rosc_div(data)                                                (0x00000300&((data)<<8))
#define SB2_RNG_ANALOG_rosc_div_src(data)                                            ((0x00000300&(data))>>8)
#define SB2_RNG_ANALOG_get_rosc_div(data)                                            ((0x00000300&(data))>>8)
#define SB2_RNG_ANALOG_rosc_gain_shift                                               (6)
#define SB2_RNG_ANALOG_rosc_gain_mask                                                (0x000000C0)
#define SB2_RNG_ANALOG_rosc_gain(data)                                               (0x000000C0&((data)<<6))
#define SB2_RNG_ANALOG_rosc_gain_src(data)                                           ((0x000000C0&(data))>>6)
#define SB2_RNG_ANALOG_get_rosc_gain(data)                                           ((0x000000C0&(data))>>6)
#define SB2_RNG_ANALOG_rosc_fs_shift                                                 (4)
#define SB2_RNG_ANALOG_rosc_fs_mask                                                  (0x00000030)
#define SB2_RNG_ANALOG_rosc_fs(data)                                                 (0x00000030&((data)<<4))
#define SB2_RNG_ANALOG_rosc_fs_src(data)                                             ((0x00000030&(data))>>4)
#define SB2_RNG_ANALOG_get_rosc_fs(data)                                             ((0x00000030&(data))>>4)
#define SB2_RNG_ANALOG_rosc_test_shift                                               (1)
#define SB2_RNG_ANALOG_rosc_test_mask                                                (0x00000002)
#define SB2_RNG_ANALOG_rosc_test(data)                                               (0x00000002&((data)<<1))
#define SB2_RNG_ANALOG_rosc_test_src(data)                                           ((0x00000002&(data))>>1)
#define SB2_RNG_ANALOG_get_rosc_test(data)                                           ((0x00000002&(data))>>1)
#define SB2_RNG_ANALOG_rosc_pow_shift                                                (0)
#define SB2_RNG_ANALOG_rosc_pow_mask                                                 (0x00000001)
#define SB2_RNG_ANALOG_rosc_pow(data)                                                (0x00000001&((data)<<0))
#define SB2_RNG_ANALOG_rosc_pow_src(data)                                            ((0x00000001&(data))>>0)
#define SB2_RNG_ANALOG_get_rosc_pow(data)                                            ((0x00000001&(data))>>0)


#define SB2_RNG_CALI_CHK                                                             0x9801AA18
#define SB2_RNG_CALI_CHK_reg_addr                                                    "0x9801AA18"
#define SB2_RNG_CALI_CHK_reg                                                         0x9801AA18
#define set_SB2_RNG_CALI_CHK_reg(data)   (*((volatile unsigned int*) SB2_RNG_CALI_CHK_reg)=data)
#define get_SB2_RNG_CALI_CHK_reg   (*((volatile unsigned int*) SB2_RNG_CALI_CHK_reg))
#define SB2_RNG_CALI_CHK_inst_adr                                                    "0x0086"
#define SB2_RNG_CALI_CHK_inst                                                        0x0086
#define SB2_RNG_CALI_CHK_prd_ub_shift                                                (16)
#define SB2_RNG_CALI_CHK_prd_ub_mask                                                 (0xFFFF0000)
#define SB2_RNG_CALI_CHK_prd_ub(data)                                                (0xFFFF0000&((data)<<16))
#define SB2_RNG_CALI_CHK_prd_ub_src(data)                                            ((0xFFFF0000&(data))>>16)
#define SB2_RNG_CALI_CHK_get_prd_ub(data)                                            ((0xFFFF0000&(data))>>16)
#define SB2_RNG_CALI_CHK_prd_lb_shift                                                (0)
#define SB2_RNG_CALI_CHK_prd_lb_mask                                                 (0x0000FFFF)
#define SB2_RNG_CALI_CHK_prd_lb(data)                                                (0x0000FFFF&((data)<<0))
#define SB2_RNG_CALI_CHK_prd_lb_src(data)                                            ((0x0000FFFF&(data))>>0)
#define SB2_RNG_CALI_CHK_get_prd_lb(data)                                            ((0x0000FFFF&(data))>>0)


#define SB2_RNG_CALI_CTRL                                                            0x9801AA1C
#define SB2_RNG_CALI_CTRL_reg_addr                                                   "0x9801AA1C"
#define SB2_RNG_CALI_CTRL_reg                                                        0x9801AA1C
#define set_SB2_RNG_CALI_CTRL_reg(data)   (*((volatile unsigned int*) SB2_RNG_CALI_CTRL_reg)=data)
#define get_SB2_RNG_CALI_CTRL_reg   (*((volatile unsigned int*) SB2_RNG_CALI_CTRL_reg))
#define SB2_RNG_CALI_CTRL_inst_adr                                                   "0x0087"
#define SB2_RNG_CALI_CTRL_inst                                                       0x0087
#define SB2_RNG_CALI_CTRL_shot_num_shift                                             (20)
#define SB2_RNG_CALI_CTRL_shot_num_mask                                              (0xFFF00000)
#define SB2_RNG_CALI_CTRL_shot_num(data)                                             (0xFFF00000&((data)<<20))
#define SB2_RNG_CALI_CTRL_shot_num_src(data)                                         ((0xFFF00000&(data))>>20)
#define SB2_RNG_CALI_CTRL_get_shot_num(data)                                         ((0xFFF00000&(data))>>20)
#define SB2_RNG_CALI_CTRL_cyc_num_shift                                              (17)
#define SB2_RNG_CALI_CTRL_cyc_num_mask                                               (0x000E0000)
#define SB2_RNG_CALI_CTRL_cyc_num(data)                                              (0x000E0000&((data)<<17))
#define SB2_RNG_CALI_CTRL_cyc_num_src(data)                                          ((0x000E0000&(data))>>17)
#define SB2_RNG_CALI_CTRL_get_cyc_num(data)                                          ((0x000E0000&(data))>>17)
#define SB2_RNG_CALI_CTRL_wait_num_shift                                             (12)
#define SB2_RNG_CALI_CTRL_wait_num_mask                                              (0x0001F000)
#define SB2_RNG_CALI_CTRL_wait_num(data)                                             (0x0001F000&((data)<<12))
#define SB2_RNG_CALI_CTRL_wait_num_src(data)                                         ((0x0001F000&(data))>>12)
#define SB2_RNG_CALI_CTRL_get_wait_num(data)                                         ((0x0001F000&(data))>>12)
#define SB2_RNG_CALI_CTRL_trig_num_shift                                             (4)
#define SB2_RNG_CALI_CTRL_trig_num_mask                                              (0x000001F0)
#define SB2_RNG_CALI_CTRL_trig_num(data)                                             (0x000001F0&((data)<<4))
#define SB2_RNG_CALI_CTRL_trig_num_src(data)                                         ((0x000001F0&(data))>>4)
#define SB2_RNG_CALI_CTRL_get_trig_num(data)                                         ((0x000001F0&(data))>>4)
#define SB2_RNG_CALI_CTRL_lock_shift                                                 (3)
#define SB2_RNG_CALI_CTRL_lock_mask                                                  (0x00000008)
#define SB2_RNG_CALI_CTRL_lock(data)                                                 (0x00000008&((data)<<3))
#define SB2_RNG_CALI_CTRL_lock_src(data)                                             ((0x00000008&(data))>>3)
#define SB2_RNG_CALI_CTRL_get_lock(data)                                             ((0x00000008&(data))>>3)
#define SB2_RNG_CALI_CTRL_shot_mode_shift                                            (2)
#define SB2_RNG_CALI_CTRL_shot_mode_mask                                             (0x00000004)
#define SB2_RNG_CALI_CTRL_shot_mode(data)                                            (0x00000004&((data)<<2))
#define SB2_RNG_CALI_CTRL_shot_mode_src(data)                                        ((0x00000004&(data))>>2)
#define SB2_RNG_CALI_CTRL_get_shot_mode(data)                                        ((0x00000004&(data))>>2)
#define SB2_RNG_CALI_CTRL_pol_shift                                                  (1)
#define SB2_RNG_CALI_CTRL_pol_mask                                                   (0x00000002)
#define SB2_RNG_CALI_CTRL_pol(data)                                                  (0x00000002&((data)<<1))
#define SB2_RNG_CALI_CTRL_pol_src(data)                                              ((0x00000002&(data))>>1)
#define SB2_RNG_CALI_CTRL_get_pol(data)                                              ((0x00000002&(data))>>1)
#define SB2_RNG_CALI_CTRL_hw_en_shift                                                (0)
#define SB2_RNG_CALI_CTRL_hw_en_mask                                                 (0x00000001)
#define SB2_RNG_CALI_CTRL_hw_en(data)                                                (0x00000001&((data)<<0))
#define SB2_RNG_CALI_CTRL_hw_en_src(data)                                            ((0x00000001&(data))>>0)
#define SB2_RNG_CALI_CTRL_get_hw_en(data)                                            ((0x00000001&(data))>>0)


#define SB2_RNG_RETURN                                                               0x9801AA20
#define SB2_RNG_RETURN_reg_addr                                                      "0x9801AA20"
#define SB2_RNG_RETURN_reg                                                           0x9801AA20
#define set_SB2_RNG_RETURN_reg(data)   (*((volatile unsigned int*) SB2_RNG_RETURN_reg)=data)
#define get_SB2_RNG_RETURN_reg   (*((volatile unsigned int*) SB2_RNG_RETURN_reg))
#define SB2_RNG_RETURN_inst_adr                                                      "0x0088"
#define SB2_RNG_RETURN_inst                                                          0x0088
#define SB2_RNG_RETURN_hw_d_shift                                                    (20)
#define SB2_RNG_RETURN_hw_d_mask                                                     (0x00F00000)
#define SB2_RNG_RETURN_hw_d(data)                                                    (0x00F00000&((data)<<20))
#define SB2_RNG_RETURN_hw_d_src(data)                                                ((0x00F00000&(data))>>20)
#define SB2_RNG_RETURN_get_hw_d(data)                                                ((0x00F00000&(data))>>20)
#define SB2_RNG_RETURN_rosc_lock_shift                                               (17)
#define SB2_RNG_RETURN_rosc_lock_mask                                                (0x00020000)
#define SB2_RNG_RETURN_rosc_lock(data)                                               (0x00020000&((data)<<17))
#define SB2_RNG_RETURN_rosc_lock_src(data)                                           ((0x00020000&(data))>>17)
#define SB2_RNG_RETURN_get_rosc_lock(data)                                           ((0x00020000&(data))>>17)
#define SB2_RNG_RETURN_cnt_ovflw_shift                                               (16)
#define SB2_RNG_RETURN_cnt_ovflw_mask                                                (0x00010000)
#define SB2_RNG_RETURN_cnt_ovflw(data)                                               (0x00010000&((data)<<16))
#define SB2_RNG_RETURN_cnt_ovflw_src(data)                                           ((0x00010000&(data))>>16)
#define SB2_RNG_RETURN_get_cnt_ovflw(data)                                           ((0x00010000&(data))>>16)
#define SB2_RNG_RETURN_cnt_shift                                                     (0)
#define SB2_RNG_RETURN_cnt_mask                                                      (0x0000FFFF)
#define SB2_RNG_RETURN_cnt(data)                                                     (0x0000FFFF&((data)<<0))
#define SB2_RNG_RETURN_cnt_src(data)                                                 ((0x0000FFFF&(data))>>0)
#define SB2_RNG_RETURN_get_cnt(data)                                                 ((0x0000FFFF&(data))>>0)


#define SB2_RNG_LOCK_CHK                                                             0x9801AA24
#define SB2_RNG_LOCK_CHK_reg_addr                                                    "0x9801AA24"
#define SB2_RNG_LOCK_CHK_reg                                                         0x9801AA24
#define set_SB2_RNG_LOCK_CHK_reg(data)   (*((volatile unsigned int*) SB2_RNG_LOCK_CHK_reg)=data)
#define get_SB2_RNG_LOCK_CHK_reg   (*((volatile unsigned int*) SB2_RNG_LOCK_CHK_reg))
#define SB2_RNG_LOCK_CHK_inst_adr                                                    "0x0089"
#define SB2_RNG_LOCK_CHK_inst                                                        0x0089
#define SB2_RNG_LOCK_CHK_prd_ub_shift                                                (16)
#define SB2_RNG_LOCK_CHK_prd_ub_mask                                                 (0xFFFF0000)
#define SB2_RNG_LOCK_CHK_prd_ub(data)                                                (0xFFFF0000&((data)<<16))
#define SB2_RNG_LOCK_CHK_prd_ub_src(data)                                            ((0xFFFF0000&(data))>>16)
#define SB2_RNG_LOCK_CHK_get_prd_ub(data)                                            ((0xFFFF0000&(data))>>16)
#define SB2_RNG_LOCK_CHK_prd_lb_shift                                                (0)
#define SB2_RNG_LOCK_CHK_prd_lb_mask                                                 (0x0000FFFF)
#define SB2_RNG_LOCK_CHK_prd_lb(data)                                                (0x0000FFFF&((data)<<0))
#define SB2_RNG_LOCK_CHK_prd_lb_src(data)                                            ((0x0000FFFF&(data))>>0)
#define SB2_RNG_LOCK_CHK_get_prd_lb(data)                                            ((0x0000FFFF&(data))>>0)


#define SB2_RNG_LOCK_CTRL                                                            0x9801AA28
#define SB2_RNG_LOCK_CTRL_reg_addr                                                   "0x9801AA28"
#define SB2_RNG_LOCK_CTRL_reg                                                        0x9801AA28
#define set_SB2_RNG_LOCK_CTRL_reg(data)   (*((volatile unsigned int*) SB2_RNG_LOCK_CTRL_reg)=data)
#define get_SB2_RNG_LOCK_CTRL_reg   (*((volatile unsigned int*) SB2_RNG_LOCK_CTRL_reg))
#define SB2_RNG_LOCK_CTRL_inst_adr                                                   "0x008A"
#define SB2_RNG_LOCK_CTRL_inst                                                       0x008A
#define SB2_RNG_LOCK_CTRL_exit_num_shift                                             (16)
#define SB2_RNG_LOCK_CTRL_exit_num_mask                                              (0x000F0000)
#define SB2_RNG_LOCK_CTRL_exit_num(data)                                             (0x000F0000&((data)<<16))
#define SB2_RNG_LOCK_CTRL_exit_num_src(data)                                         ((0x000F0000&(data))>>16)
#define SB2_RNG_LOCK_CTRL_get_exit_num(data)                                         ((0x000F0000&(data))>>16)
#define SB2_RNG_LOCK_CTRL_enter_num_shift                                            (0)
#define SB2_RNG_LOCK_CTRL_enter_num_mask                                             (0x0000000F)
#define SB2_RNG_LOCK_CTRL_enter_num(data)                                            (0x0000000F&((data)<<0))
#define SB2_RNG_LOCK_CTRL_enter_num_src(data)                                        ((0x0000000F&(data))>>0)
#define SB2_RNG_LOCK_CTRL_get_enter_num(data)                                        ((0x0000000F&(data))>>0)


#define SB2_RNG_RETURN3                                                              0x9801AA2C
#define SB2_RNG_RETURN3_reg_addr                                                     "0x9801AA2C"
#define SB2_RNG_RETURN3_reg                                                          0x9801AA2C
#define set_SB2_RNG_RETURN3_reg(data)   (*((volatile unsigned int*) SB2_RNG_RETURN3_reg)=data)
#define get_SB2_RNG_RETURN3_reg   (*((volatile unsigned int*) SB2_RNG_RETURN3_reg))
#define SB2_RNG_RETURN3_inst_adr                                                     "0x008B"
#define SB2_RNG_RETURN3_inst                                                         0x008B
#define SB2_RNG_RETURN3_out_ready_shift                                              (0)
#define SB2_RNG_RETURN3_out_ready_mask                                               (0x00000001)
#define SB2_RNG_RETURN3_out_ready(data)                                              (0x00000001&((data)<<0))
#define SB2_RNG_RETURN3_out_ready_src(data)                                          ((0x00000001&(data))>>0)
#define SB2_RNG_RETURN3_get_out_ready(data)                                          ((0x00000001&(data))>>0)


#define SB2_RNG_RETURN4                                                              0x9801AA30
#define SB2_RNG_RETURN4_reg_addr                                                     "0x9801AA30"
#define SB2_RNG_RETURN4_reg                                                          0x9801AA30
#define set_SB2_RNG_RETURN4_reg(data)   (*((volatile unsigned int*) SB2_RNG_RETURN4_reg)=data)
#define get_SB2_RNG_RETURN4_reg   (*((volatile unsigned int*) SB2_RNG_RETURN4_reg))
#define SB2_RNG_RETURN4_inst_adr                                                     "0x008C"
#define SB2_RNG_RETURN4_inst                                                         0x008C
#define SB2_RNG_RETURN4_valid_bit_num_shift                                          (0)
#define SB2_RNG_RETURN4_valid_bit_num_mask                                           (0xFFFFFFFF)
#define SB2_RNG_RETURN4_valid_bit_num(data)                                          (0xFFFFFFFF&((data)<<0))
#define SB2_RNG_RETURN4_valid_bit_num_src(data)                                      ((0xFFFFFFFF&(data))>>0)
#define SB2_RNG_RETURN4_get_valid_bit_num(data)                                      ((0xFFFFFFFF&(data))>>0)


#define SB2_RNG_RETURN5                                                              0x9801AA34
#define SB2_RNG_RETURN5_reg_addr                                                     "0x9801AA34"
#define SB2_RNG_RETURN5_reg                                                          0x9801AA34
#define set_SB2_RNG_RETURN5_reg(data)   (*((volatile unsigned int*) SB2_RNG_RETURN5_reg)=data)
#define get_SB2_RNG_RETURN5_reg   (*((volatile unsigned int*) SB2_RNG_RETURN5_reg))
#define SB2_RNG_RETURN5_inst_adr                                                     "0x008D"
#define SB2_RNG_RETURN5_inst                                                         0x008D
#define SB2_RNG_RETURN5_drop_num_shift                                               (0)
#define SB2_RNG_RETURN5_drop_num_mask                                                (0xFFFFFFFF)
#define SB2_RNG_RETURN5_drop_num(data)                                               (0xFFFFFFFF&((data)<<0))
#define SB2_RNG_RETURN5_drop_num_src(data)                                           ((0xFFFFFFFF&(data))>>0)
#define SB2_RNG_RETURN5_get_drop_num(data)                                           ((0xFFFFFFFF&(data))>>0)


#define SB2_RNG_RESULTR                                                              0x9801AA38
#define SB2_RNG_RESULTR_reg_addr                                                     "0x9801AA38"
#define SB2_RNG_RESULTR_reg                                                          0x9801AA38
#define set_SB2_RNG_RESULTR_reg(data)   (*((volatile unsigned int*) SB2_RNG_RESULTR_reg)=data)
#define get_SB2_RNG_RESULTR_reg   (*((volatile unsigned int*) SB2_RNG_RESULTR_reg))
#define SB2_RNG_RESULTR_inst_adr                                                     "0x008E"
#define SB2_RNG_RESULTR_inst                                                         0x008E
#define SB2_RNG_RESULTR_random_out_shift                                             (0)
#define SB2_RNG_RESULTR_random_out_mask                                              (0xFFFFFFFF)
#define SB2_RNG_RESULTR_random_out(data)                                             (0xFFFFFFFF&((data)<<0))
#define SB2_RNG_RESULTR_random_out_src(data)                                         ((0xFFFFFFFF&(data))>>0)
#define SB2_RNG_RESULTR_get_random_out(data)                                         ((0xFFFFFFFF&(data))>>0)


#define SB2_RNG_LFSR_POLY_LSB                                                        0x9801AA3C
#define SB2_RNG_LFSR_POLY_LSB_reg_addr                                               "0x9801AA3C"
#define SB2_RNG_LFSR_POLY_LSB_reg                                                    0x9801AA3C
#define set_SB2_RNG_LFSR_POLY_LSB_reg(data)   (*((volatile unsigned int*) SB2_RNG_LFSR_POLY_LSB_reg)=data)
#define get_SB2_RNG_LFSR_POLY_LSB_reg   (*((volatile unsigned int*) SB2_RNG_LFSR_POLY_LSB_reg))
#define SB2_RNG_LFSR_POLY_LSB_inst_adr                                               "0x008F"
#define SB2_RNG_LFSR_POLY_LSB_inst                                                   0x008F
#define SB2_RNG_LFSR_POLY_LSB_lfsr_poly_lsb_shift                                    (0)
#define SB2_RNG_LFSR_POLY_LSB_lfsr_poly_lsb_mask                                     (0xFFFFFFFF)
#define SB2_RNG_LFSR_POLY_LSB_lfsr_poly_lsb(data)                                    (0xFFFFFFFF&((data)<<0))
#define SB2_RNG_LFSR_POLY_LSB_lfsr_poly_lsb_src(data)                                ((0xFFFFFFFF&(data))>>0)
#define SB2_RNG_LFSR_POLY_LSB_get_lfsr_poly_lsb(data)                                ((0xFFFFFFFF&(data))>>0)


#define SB2_RNG_LFSR_POLY_MSB                                                        0x9801AA40
#define SB2_RNG_LFSR_POLY_MSB_reg_addr                                               "0x9801AA40"
#define SB2_RNG_LFSR_POLY_MSB_reg                                                    0x9801AA40
#define set_SB2_RNG_LFSR_POLY_MSB_reg(data)   (*((volatile unsigned int*) SB2_RNG_LFSR_POLY_MSB_reg)=data)
#define get_SB2_RNG_LFSR_POLY_MSB_reg   (*((volatile unsigned int*) SB2_RNG_LFSR_POLY_MSB_reg))
#define SB2_RNG_LFSR_POLY_MSB_inst_adr                                               "0x0090"
#define SB2_RNG_LFSR_POLY_MSB_inst                                                   0x0090
#define SB2_RNG_LFSR_POLY_MSB_lfsr_poly_msb_shift                                    (0)
#define SB2_RNG_LFSR_POLY_MSB_lfsr_poly_msb_mask                                     (0xFFFFFFFF)
#define SB2_RNG_LFSR_POLY_MSB_lfsr_poly_msb(data)                                    (0xFFFFFFFF&((data)<<0))
#define SB2_RNG_LFSR_POLY_MSB_lfsr_poly_msb_src(data)                                ((0xFFFFFFFF&(data))>>0)
#define SB2_RNG_LFSR_POLY_MSB_get_lfsr_poly_msb(data)                                ((0xFFFFFFFF&(data))>>0)


#define SB2_RNG_DUMMY                                                                0x9801AA44
#define SB2_RNG_DUMMY_reg_addr                                                       "0x9801AA44"
#define SB2_RNG_DUMMY_reg                                                            0x9801AA44
#define set_SB2_RNG_DUMMY_reg(data)   (*((volatile unsigned int*) SB2_RNG_DUMMY_reg)=data)
#define get_SB2_RNG_DUMMY_reg   (*((volatile unsigned int*) SB2_RNG_DUMMY_reg))
#define SB2_RNG_DUMMY_inst_adr                                                       "0x0091"
#define SB2_RNG_DUMMY_inst                                                           0x0091
#define SB2_RNG_DUMMY_dummy_msb_shift                                                (16)
#define SB2_RNG_DUMMY_dummy_msb_mask                                                 (0xFFFF0000)
#define SB2_RNG_DUMMY_dummy_msb(data)                                                (0xFFFF0000&((data)<<16))
#define SB2_RNG_DUMMY_dummy_msb_src(data)                                            ((0xFFFF0000&(data))>>16)
#define SB2_RNG_DUMMY_get_dummy_msb(data)                                            ((0xFFFF0000&(data))>>16)
#define SB2_RNG_DUMMY_dummy_lsb_shift                                                (0)
#define SB2_RNG_DUMMY_dummy_lsb_mask                                                 (0x0000FFFF)
#define SB2_RNG_DUMMY_dummy_lsb(data)                                                (0x0000FFFF&((data)<<0))
#define SB2_RNG_DUMMY_dummy_lsb_src(data)                                            ((0x0000FFFF&(data))>>0)
#define SB2_RNG_DUMMY_get_dummy_lsb(data)                                            ((0x0000FFFF&(data))>>0)


#define SB2_RNG_POWER                                                                0x9801AA48
#define SB2_RNG_POWER_reg_addr                                                       "0x9801AA48"
#define SB2_RNG_POWER_reg                                                            0x9801AA48
#define set_SB2_RNG_POWER_reg(data)   (*((volatile unsigned int*) SB2_RNG_POWER_reg)=data)
#define get_SB2_RNG_POWER_reg   (*((volatile unsigned int*) SB2_RNG_POWER_reg))
#define SB2_RNG_POWER_inst_adr                                                       "0x0092"
#define SB2_RNG_POWER_inst                                                           0x0092
#define SB2_RNG_POWER_gating_en_shift                                                (0)
#define SB2_RNG_POWER_gating_en_mask                                                 (0x00000001)
#define SB2_RNG_POWER_gating_en(data)                                                (0x00000001&((data)<<0))
#define SB2_RNG_POWER_gating_en_src(data)                                            ((0x00000001&(data))>>0)
#define SB2_RNG_POWER_get_gating_en(data)                                            ((0x00000001&(data))>>0)

//Serial Flash Controller register
#define SB2_WRAPPER_CTRL		WRAPPER_CTRL
#define SB2_SFC_BASE			SFC_BASE
#define SB2_SFC_OPCODE			SFC_OPCODE
#define SB2_SFC_CTL			SFC_CTL
#define SB2_SFC_SCK			SFC_SCK
#define SB2_SFC_CE			SFC_CE
#define SB2_SFC_WP			SFC_WP
#define SB2_SFC_POS_LATCH		SFC_POS_LATCH
#define SB2_SFC_WAIT_WR			SFC_WAIT_WR
#define SB2_SFC_EN_WR			SFC_EN_WR
#define SB2_SFC_FAST_RD			SFC_FAST_RD
#define SB2_SFC_SCK_TAP			SFC_SCK_TAP

//#define SB2_CHIP_INFO   		(CHIP_INFO)
#endif
