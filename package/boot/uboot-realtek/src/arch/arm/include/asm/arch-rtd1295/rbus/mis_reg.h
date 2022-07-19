/**************************************************************
// Spec Version                  : 0.0.5
// Parser Version                : DVR_Parser_6.11(120105)
// CModelGen Version             : 5.1 2012.01.05
// Naming Rule                   :  Module_Register_Name
// Naming Rule                   : Module_Register_Name
// Parse Option                  : Only Parse _op1
// Parse Address Region          : All Address Region 
// Decode bit number             : 12 bits
// Firmware Header Generate Date : 2015/5/14 11:18:25
***************************************************************/


#ifndef _MIS_REG_H_INCLUDED_
#define _MIS_REG_H_INCLUDED_

#define MIS_UMSK_ISR                                                                 0x9801B008
#define MIS_UMSK_ISR_reg_addr                                                        "0x9801B008"
#define MIS_UMSK_ISR_reg                                                             0x9801B008
#define set_MIS_UMSK_ISR_reg(data)   (*((volatile unsigned int*) MIS_UMSK_ISR_reg)=data)
#define get_MIS_UMSK_ISR_reg   (*((volatile unsigned int*) MIS_UMSK_ISR_reg))
#define MIS_UMSK_ISR_inst_adr                                                        "0x0002"
#define MIS_UMSK_ISR_inst                                                            0x0002
#define MIS_UMSK_ISR_fan_int_shift                                                   (29)
#define MIS_UMSK_ISR_fan_int_mask                                                    (0x20000000)
#define MIS_UMSK_ISR_fan_int(data)                                                   (0x20000000&((data)<<29))
#define MIS_UMSK_ISR_fan_int_src(data)                                               ((0x20000000&(data))>>29)
#define MIS_UMSK_ISR_get_fan_int(data)                                               ((0x20000000&(data))>>29)
#define MIS_UMSK_ISR_gspi_int_shift                                                  (27)
#define MIS_UMSK_ISR_gspi_int_mask                                                   (0x08000000)
#define MIS_UMSK_ISR_gspi_int(data)                                                  (0x08000000&((data)<<27))
#define MIS_UMSK_ISR_gspi_int_src(data)                                              ((0x08000000&(data))>>27)
#define MIS_UMSK_ISR_get_gspi_int(data)                                              ((0x08000000&(data))>>27)
#define MIS_UMSK_ISR_gpioda_int_shift                                                (20)
#define MIS_UMSK_ISR_gpioda_int_mask                                                 (0x00100000)
#define MIS_UMSK_ISR_gpioda_int(data)                                                (0x00100000&((data)<<20))
#define MIS_UMSK_ISR_gpioda_int_src(data)                                            ((0x00100000&(data))>>20)
#define MIS_UMSK_ISR_get_gpioda_int(data)                                            ((0x00100000&(data))>>20)
#define MIS_UMSK_ISR_gpioa_int_shift                                                 (19)
#define MIS_UMSK_ISR_gpioa_int_mask                                                  (0x00080000)
#define MIS_UMSK_ISR_gpioa_int(data)                                                 (0x00080000&((data)<<19))
#define MIS_UMSK_ISR_gpioa_int_src(data)                                             ((0x00080000&(data))>>19)
#define MIS_UMSK_ISR_get_gpioa_int(data)                                             ((0x00080000&(data))>>19)
#define MIS_UMSK_ISR_rtc_date_int_shift                                              (12)
#define MIS_UMSK_ISR_rtc_date_int_mask                                               (0x00001000)
#define MIS_UMSK_ISR_rtc_date_int(data)                                              (0x00001000&((data)<<12))
#define MIS_UMSK_ISR_rtc_date_int_src(data)                                          ((0x00001000&(data))>>12)
#define MIS_UMSK_ISR_get_rtc_date_int(data)                                          ((0x00001000&(data))>>12)
#define MIS_UMSK_ISR_rtc_hour_int_shift                                              (11)
#define MIS_UMSK_ISR_rtc_hour_int_mask                                               (0x00000800)
#define MIS_UMSK_ISR_rtc_hour_int(data)                                              (0x00000800&((data)<<11))
#define MIS_UMSK_ISR_rtc_hour_int_src(data)                                          ((0x00000800&(data))>>11)
#define MIS_UMSK_ISR_get_rtc_hour_int(data)                                          ((0x00000800&(data))>>11)
#define MIS_UMSK_ISR_rtc_min_int_shift                                               (10)
#define MIS_UMSK_ISR_rtc_min_int_mask                                                (0x00000400)
#define MIS_UMSK_ISR_rtc_min_int(data)                                               (0x00000400&((data)<<10))
#define MIS_UMSK_ISR_rtc_min_int_src(data)                                           ((0x00000400&(data))>>10)
#define MIS_UMSK_ISR_get_rtc_min_int(data)                                           ((0x00000400&(data))>>10)
#define MIS_UMSK_ISR_rtc_hsec_int_shift                                              (9)
#define MIS_UMSK_ISR_rtc_hsec_int_mask                                               (0x00000200)
#define MIS_UMSK_ISR_rtc_hsec_int(data)                                              (0x00000200&((data)<<9))
#define MIS_UMSK_ISR_rtc_hsec_int_src(data)                                          ((0x00000200&(data))>>9)
#define MIS_UMSK_ISR_get_rtc_hsec_int(data)                                          ((0x00000200&(data))>>9)
#define MIS_UMSK_ISR_tc1_int_shift                                                   (7)
#define MIS_UMSK_ISR_tc1_int_mask                                                    (0x00000080)
#define MIS_UMSK_ISR_tc1_int(data)                                                   (0x00000080&((data)<<7))
#define MIS_UMSK_ISR_tc1_int_src(data)                                               ((0x00000080&(data))>>7)
#define MIS_UMSK_ISR_get_tc1_int(data)                                               ((0x00000080&(data))>>7)
#define MIS_UMSK_ISR_tc0_int_shift                                                   (6)
#define MIS_UMSK_ISR_tc0_int_mask                                                    (0x00000040)
#define MIS_UMSK_ISR_tc0_int(data)                                                   (0x00000040&((data)<<6))
#define MIS_UMSK_ISR_tc0_int_src(data)                                               ((0x00000040&(data))>>6)
#define MIS_UMSK_ISR_get_tc0_int(data)                                               ((0x00000040&(data))>>6)
#define MIS_UMSK_ISR_ur1_to_int_shift                                                (5)
#define MIS_UMSK_ISR_ur1_to_int_mask                                                 (0x00000020)
#define MIS_UMSK_ISR_ur1_to_int(data)                                                (0x00000020&((data)<<5))
#define MIS_UMSK_ISR_ur1_to_int_src(data)                                            ((0x00000020&(data))>>5)
#define MIS_UMSK_ISR_get_ur1_to_int(data)                                            ((0x00000020&(data))>>5)
#define MIS_UMSK_ISR_ur2_to_int_shift                                                (4)
#define MIS_UMSK_ISR_ur2_to_int_mask                                                 (0x00000010)
#define MIS_UMSK_ISR_ur2_to_int(data)                                                (0x00000010&((data)<<4))
#define MIS_UMSK_ISR_ur2_to_int_src(data)                                            ((0x00000010&(data))>>4)
#define MIS_UMSK_ISR_get_ur2_to_int(data)                                            ((0x00000010&(data))>>4)
#define MIS_UMSK_ISR_wdog_nmi_int_shift                                              (2)
#define MIS_UMSK_ISR_wdog_nmi_int_mask                                               (0x00000004)
#define MIS_UMSK_ISR_wdog_nmi_int(data)                                              (0x00000004&((data)<<2))
#define MIS_UMSK_ISR_wdog_nmi_int_src(data)                                          ((0x00000004&(data))>>2)
#define MIS_UMSK_ISR_get_wdog_nmi_int(data)                                          ((0x00000004&(data))>>2)
#define MIS_UMSK_ISR_write_data_shift                                                (0)
#define MIS_UMSK_ISR_write_data_mask                                                 (0x00000001)
#define MIS_UMSK_ISR_write_data(data)                                                (0x00000001&((data)<<0))
#define MIS_UMSK_ISR_write_data_src(data)                                            ((0x00000001&(data))>>0)
#define MIS_UMSK_ISR_get_write_data(data)                                            ((0x00000001&(data))>>0)


#define MIS_ISR                                                                      0x9801B00C
#define MIS_ISR_reg_addr                                                             "0x9801B00C"
#define MIS_ISR_reg                                                                  0x9801B00C
#define set_MIS_ISR_reg(data)   (*((volatile unsigned int*) MIS_ISR_reg)=data)
#define get_MIS_ISR_reg   (*((volatile unsigned int*) MIS_ISR_reg))
#define MIS_ISR_inst_adr                                                             "0x0003"
#define MIS_ISR_inst                                                                 0x0003
#define MIS_ISR_fan_int_shift                                                        (29)
#define MIS_ISR_fan_int_mask                                                         (0x20000000)
#define MIS_ISR_fan_int(data)                                                        (0x20000000&((data)<<29))
#define MIS_ISR_fan_int_src(data)                                                    ((0x20000000&(data))>>29)
#define MIS_ISR_get_fan_int(data)                                                    ((0x20000000&(data))>>29)
#define MIS_ISR_gspi_int_shift                                                       (27)
#define MIS_ISR_gspi_int_mask                                                        (0x08000000)
#define MIS_ISR_gspi_int(data)                                                       (0x08000000&((data)<<27))
#define MIS_ISR_gspi_int_src(data)                                                   ((0x08000000&(data))>>27)
#define MIS_ISR_get_gspi_int(data)                                                   ((0x08000000&(data))>>27)
#define MIS_ISR_i2c2_int_shift                                                       (26)
#define MIS_ISR_i2c2_int_mask                                                        (0x04000000)
#define MIS_ISR_i2c2_int(data)                                                       (0x04000000&((data)<<26))
#define MIS_ISR_i2c2_int_src(data)                                                   ((0x04000000&(data))>>26)
#define MIS_ISR_get_i2c2_int(data)                                                   ((0x04000000&(data))>>26)
#define MIS_ISR_sc0_int_shift                                                        (24)
#define MIS_ISR_sc0_int_mask                                                         (0x01000000)
#define MIS_ISR_sc0_int(data)                                                        (0x01000000&((data)<<24))
#define MIS_ISR_sc0_int_src(data)                                                    ((0x01000000&(data))>>24)
#define MIS_ISR_get_sc0_int(data)                                                    ((0x01000000&(data))>>24)
#define MIS_ISR_i2c3_int_shift                                                       (23)
#define MIS_ISR_i2c3_int_mask                                                        (0x00800000)
#define MIS_ISR_i2c3_int(data)                                                       (0x00800000&((data)<<23))
#define MIS_ISR_i2c3_int_src(data)                                                   ((0x00800000&(data))>>23)
#define MIS_ISR_get_i2c3_int(data)                                                   ((0x00800000&(data))>>23)
#define MIS_ISR_lsadc1_int_shift                                                     (22)
#define MIS_ISR_lsadc1_int_mask                                                      (0x00400000)
#define MIS_ISR_lsadc1_int(data)                                                     (0x00400000&((data)<<22))
#define MIS_ISR_lsadc1_int_src(data)                                                 ((0x00400000&(data))>>22)
#define MIS_ISR_get_lsadc1_int(data)                                                 ((0x00400000&(data))>>22)
#define MIS_ISR_lsadc0_int_shift                                                     (21)
#define MIS_ISR_lsadc0_int_mask                                                      (0x00200000)
#define MIS_ISR_lsadc0_int(data)                                                     (0x00200000&((data)<<21))
#define MIS_ISR_lsadc0_int_src(data)                                                 ((0x00200000&(data))>>21)
#define MIS_ISR_get_lsadc0_int(data)                                                 ((0x00200000&(data))>>21)
#define MIS_ISR_gpioda_int_shift                                                     (20)
#define MIS_ISR_gpioda_int_mask                                                      (0x00100000)
#define MIS_ISR_gpioda_int(data)                                                     (0x00100000&((data)<<20))
#define MIS_ISR_gpioda_int_src(data)                                                 ((0x00100000&(data))>>20)
#define MIS_ISR_get_gpioda_int(data)                                                 ((0x00100000&(data))>>20)
#define MIS_ISR_gpioa_int_shift                                                      (19)
#define MIS_ISR_gpioa_int_mask                                                       (0x00080000)
#define MIS_ISR_gpioa_int(data)                                                      (0x00080000&((data)<<19))
#define MIS_ISR_gpioa_int_src(data)                                                  ((0x00080000&(data))>>19)
#define MIS_ISR_get_gpioa_int(data)                                                  ((0x00080000&(data))>>19)
#define MIS_ISR_i2c4_int_shift                                                       (15)
#define MIS_ISR_i2c4_int_mask                                                        (0x00008000)
#define MIS_ISR_i2c4_int(data)                                                       (0x00008000&((data)<<15))
#define MIS_ISR_i2c4_int_src(data)                                                   ((0x00008000&(data))>>15)
#define MIS_ISR_get_i2c4_int(data)                                                   ((0x00008000&(data))>>15)
#define MIS_ISR_i2c5_int_shift                                                       (14)
#define MIS_ISR_i2c5_int_mask                                                        (0x00004000)
#define MIS_ISR_i2c5_int(data)                                                       (0x00004000&((data)<<14))
#define MIS_ISR_i2c5_int_src(data)                                                   ((0x00004000&(data))>>14)
#define MIS_ISR_get_i2c5_int(data)                                                   ((0x00004000&(data))>>14)
#define MIS_ISR_ur2_to_int_shift                                                     (13)
#define MIS_ISR_ur2_to_int_mask                                                      (0x00002000)
#define MIS_ISR_ur2_to_int(data)                                                     (0x00002000&((data)<<13))
#define MIS_ISR_ur2_to_int_src(data)                                                 ((0x00002000&(data))>>13)
#define MIS_ISR_get_ur2_to_int(data)                                                 ((0x00002000&(data))>>13)
#define MIS_ISR_rtc_date_int_shift                                                   (12)
#define MIS_ISR_rtc_date_int_mask                                                    (0x00001000)
#define MIS_ISR_rtc_date_int(data)                                                   (0x00001000&((data)<<12))
#define MIS_ISR_rtc_date_int_src(data)                                               ((0x00001000&(data))>>12)
#define MIS_ISR_get_rtc_date_int(data)                                               ((0x00001000&(data))>>12)
#define MIS_ISR_rtc_hour_int_shift                                                   (11)
#define MIS_ISR_rtc_hour_int_mask                                                    (0x00000800)
#define MIS_ISR_rtc_hour_int(data)                                                   (0x00000800&((data)<<11))
#define MIS_ISR_rtc_hour_int_src(data)                                               ((0x00000800&(data))>>11)
#define MIS_ISR_get_rtc_hour_int(data)                                               ((0x00000800&(data))>>11)
#define MIS_ISR_rtc_min_int_shift                                                    (10)
#define MIS_ISR_rtc_min_int_mask                                                     (0x00000400)
#define MIS_ISR_rtc_min_int(data)                                                    (0x00000400&((data)<<10))
#define MIS_ISR_rtc_min_int_src(data)                                                ((0x00000400&(data))>>10)
#define MIS_ISR_get_rtc_min_int(data)                                                ((0x00000400&(data))>>10)
#define MIS_ISR_rtc_hsec_int_shift                                                   (9)
#define MIS_ISR_rtc_hsec_int_mask                                                    (0x00000200)
#define MIS_ISR_rtc_hsec_int(data)                                                   (0x00000200&((data)<<9))
#define MIS_ISR_rtc_hsec_int_src(data)                                               ((0x00000200&(data))>>9)
#define MIS_ISR_get_rtc_hsec_int(data)                                               ((0x00000200&(data))>>9)
#define MIS_ISR_ur2_int_shift                                                        (8)
#define MIS_ISR_ur2_int_mask                                                         (0x00000100)
#define MIS_ISR_ur2_int(data)                                                        (0x00000100&((data)<<8))
#define MIS_ISR_ur2_int_src(data)                                                    ((0x00000100&(data))>>8)
#define MIS_ISR_get_ur2_int(data)                                                    ((0x00000100&(data))>>8)
#define MIS_ISR_tc1_int_shift                                                        (7)
#define MIS_ISR_tc1_int_mask                                                         (0x00000080)
#define MIS_ISR_tc1_int(data)                                                        (0x00000080&((data)<<7))
#define MIS_ISR_tc1_int_src(data)                                                    ((0x00000080&(data))>>7)
#define MIS_ISR_get_tc1_int(data)                                                    ((0x00000080&(data))>>7)
#define MIS_ISR_tc0_int_shift                                                        (6)
#define MIS_ISR_tc0_int_mask                                                         (0x00000040)
#define MIS_ISR_tc0_int(data)                                                        (0x00000040&((data)<<6))
#define MIS_ISR_tc0_int_src(data)                                                    ((0x00000040&(data))>>6)
#define MIS_ISR_get_tc0_int(data)                                                    ((0x00000040&(data))>>6)
#define MIS_ISR_ur1_to_int_shift                                                     (5)
#define MIS_ISR_ur1_to_int_mask                                                      (0x00000020)
#define MIS_ISR_ur1_to_int(data)                                                     (0x00000020&((data)<<5))
#define MIS_ISR_ur1_to_int_src(data)                                                 ((0x00000020&(data))>>5)
#define MIS_ISR_get_ur1_to_int(data)                                                 ((0x00000020&(data))>>5)
#define MIS_ISR_ur1_int_shift                                                        (3)
#define MIS_ISR_ur1_int_mask                                                         (0x00000008)
#define MIS_ISR_ur1_int(data)                                                        (0x00000008&((data)<<3))
#define MIS_ISR_ur1_int_src(data)                                                    ((0x00000008&(data))>>3)
#define MIS_ISR_get_ur1_int(data)                                                    ((0x00000008&(data))>>3)
#define MIS_ISR_wdog_nmi_int_shift                                                   (2)
#define MIS_ISR_wdog_nmi_int_mask                                                    (0x00000004)
#define MIS_ISR_wdog_nmi_int(data)                                                   (0x00000004&((data)<<2))
#define MIS_ISR_wdog_nmi_int_src(data)                                               ((0x00000004&(data))>>2)
#define MIS_ISR_get_wdog_nmi_int(data)                                               ((0x00000004&(data))>>2)
#define MIS_ISR_write_data_shift                                                     (0)
#define MIS_ISR_write_data_mask                                                      (0x00000001)
#define MIS_ISR_write_data(data)                                                     (0x00000001&((data)<<0))
#define MIS_ISR_write_data_src(data)                                                 ((0x00000001&(data))>>0)
#define MIS_ISR_get_write_data(data)                                                 ((0x00000001&(data))>>0)


#define MIS_UMSK_ISR_SWC                                                             0x9801B010
#define MIS_UMSK_ISR_SWC_reg_addr                                                    "0x9801B010"
#define MIS_UMSK_ISR_SWC_reg                                                         0x9801B010
#define set_MIS_UMSK_ISR_SWC_reg(data)   (*((volatile unsigned int*) MIS_UMSK_ISR_SWC_reg)=data)
#define get_MIS_UMSK_ISR_SWC_reg   (*((volatile unsigned int*) MIS_UMSK_ISR_SWC_reg))
#define MIS_UMSK_ISR_SWC_inst_adr                                                    "0x0004"
#define MIS_UMSK_ISR_SWC_inst                                                        0x0004
#define MIS_UMSK_ISR_SWC_wdog_nmi_int_shift                                          (3)
#define MIS_UMSK_ISR_SWC_wdog_nmi_int_mask                                           (0x00000008)
#define MIS_UMSK_ISR_SWC_wdog_nmi_int(data)                                          (0x00000008&((data)<<3))
#define MIS_UMSK_ISR_SWC_wdog_nmi_int_src(data)                                      ((0x00000008&(data))>>3)
#define MIS_UMSK_ISR_SWC_get_wdog_nmi_int(data)                                      ((0x00000008&(data))>>3)
#define MIS_UMSK_ISR_SWC_tc2_int_shift                                               (1)
#define MIS_UMSK_ISR_SWC_tc2_int_mask                                                (0x00000002)
#define MIS_UMSK_ISR_SWC_tc2_int(data)                                               (0x00000002&((data)<<1))
#define MIS_UMSK_ISR_SWC_tc2_int_src(data)                                           ((0x00000002&(data))>>1)
#define MIS_UMSK_ISR_SWC_get_tc2_int(data)                                           ((0x00000002&(data))>>1)
#define MIS_UMSK_ISR_SWC_write_data_shift                                            (0)
#define MIS_UMSK_ISR_SWC_write_data_mask                                             (0x00000001)
#define MIS_UMSK_ISR_SWC_write_data(data)                                            (0x00000001&((data)<<0))
#define MIS_UMSK_ISR_SWC_write_data_src(data)                                        ((0x00000001&(data))>>0)
#define MIS_UMSK_ISR_SWC_get_write_data(data)                                        ((0x00000001&(data))>>0)


#define MIS_ISR_SWC                                                                  0x9801B014
#define MIS_ISR_SWC_reg_addr                                                         "0x9801B014"
#define MIS_ISR_SWC_reg                                                              0x9801B014
#define set_MIS_ISR_SWC_reg(data)   (*((volatile unsigned int*) MIS_ISR_SWC_reg)=data)
#define get_MIS_ISR_SWC_reg   (*((volatile unsigned int*) MIS_ISR_SWC_reg))
#define MIS_ISR_SWC_inst_adr                                                         "0x0005"
#define MIS_ISR_SWC_inst                                                             0x0005
#define MIS_ISR_SWC_wdog_nmi_int_shift                                               (3)
#define MIS_ISR_SWC_wdog_nmi_int_mask                                                (0x00000008)
#define MIS_ISR_SWC_wdog_nmi_int(data)                                               (0x00000008&((data)<<3))
#define MIS_ISR_SWC_wdog_nmi_int_src(data)                                           ((0x00000008&(data))>>3)
#define MIS_ISR_SWC_get_wdog_nmi_int(data)                                           ((0x00000008&(data))>>3)
#define MIS_ISR_SWC_i2c_2_int_shift                                                  (2)
#define MIS_ISR_SWC_i2c_2_int_mask                                                   (0x00000004)
#define MIS_ISR_SWC_i2c_2_int(data)                                                  (0x00000004&((data)<<2))
#define MIS_ISR_SWC_i2c_2_int_src(data)                                              ((0x00000004&(data))>>2)
#define MIS_ISR_SWC_get_i2c_2_int(data)                                              ((0x00000004&(data))>>2)
#define MIS_ISR_SWC_tc2_int_shift                                                    (1)
#define MIS_ISR_SWC_tc2_int_mask                                                     (0x00000002)
#define MIS_ISR_SWC_tc2_int(data)                                                    (0x00000002&((data)<<1))
#define MIS_ISR_SWC_tc2_int_src(data)                                                ((0x00000002&(data))>>1)
#define MIS_ISR_SWC_get_tc2_int(data)                                                ((0x00000002&(data))>>1)
#define MIS_ISR_SWC_write_data_shift                                                 (0)
#define MIS_ISR_SWC_write_data_mask                                                  (0x00000001)
#define MIS_ISR_SWC_write_data(data)                                                 (0x00000001&((data)<<0))
#define MIS_ISR_SWC_write_data_src(data)                                             ((0x00000001&(data))>>0)
#define MIS_ISR_SWC_get_write_data(data)                                             ((0x00000001&(data))>>0)


#define MIS_SETTING_SWC                                                              0x9801B018
#define MIS_SETTING_SWC_reg_addr                                                     "0x9801B018"
#define MIS_SETTING_SWC_reg                                                          0x9801B018
#define set_MIS_SETTING_SWC_reg(data)   (*((volatile unsigned int*) MIS_SETTING_SWC_reg)=data)
#define get_MIS_SETTING_SWC_reg   (*((volatile unsigned int*) MIS_SETTING_SWC_reg))
#define MIS_SETTING_SWC_inst_adr                                                     "0x0006"
#define MIS_SETTING_SWC_inst                                                         0x0006
#define MIS_SETTING_SWC_i2c_2_swc_en_shift                                           (1)
#define MIS_SETTING_SWC_i2c_2_swc_en_mask                                            (0x00000002)
#define MIS_SETTING_SWC_i2c_2_swc_en(data)                                           (0x00000002&((data)<<1))
#define MIS_SETTING_SWC_i2c_2_swc_en_src(data)                                       ((0x00000002&(data))>>1)
#define MIS_SETTING_SWC_get_i2c_2_swc_en(data)                                       ((0x00000002&(data))>>1)
#define MIS_SETTING_SWC_i2c_2_en_shift                                               (0)
#define MIS_SETTING_SWC_i2c_2_en_mask                                                (0x00000001)
#define MIS_SETTING_SWC_i2c_2_en(data)                                               (0x00000001&((data)<<0))
#define MIS_SETTING_SWC_i2c_2_en_src(data)                                           ((0x00000001&(data))>>0)
#define MIS_SETTING_SWC_get_i2c_2_en(data)                                           ((0x00000001&(data))>>0)


#define MIS_FAST_INT_EN_0                                                            0x9801B01C
#define MIS_FAST_INT_EN_0_reg_addr                                                   "0x9801B01C"
#define MIS_FAST_INT_EN_0_reg                                                        0x9801B01C
#define set_MIS_FAST_INT_EN_0_reg(data)   (*((volatile unsigned int*) MIS_FAST_INT_EN_0_reg)=data)
#define get_MIS_FAST_INT_EN_0_reg   (*((volatile unsigned int*) MIS_FAST_INT_EN_0_reg))
#define MIS_FAST_INT_EN_0_inst_adr                                                   "0x0007"
#define MIS_FAST_INT_EN_0_inst                                                       0x0007
#define MIS_FAST_INT_EN_0_gp_int_shift                                               (1)
#define MIS_FAST_INT_EN_0_gp_int_mask                                                (0xFFFFFFFE)
#define MIS_FAST_INT_EN_0_gp_int(data)                                               (0xFFFFFFFE&((data)<<1))
#define MIS_FAST_INT_EN_0_gp_int_src(data)                                           ((0xFFFFFFFE&(data))>>1)
#define MIS_FAST_INT_EN_0_get_gp_int(data)                                           ((0xFFFFFFFE&(data))>>1)


#define MIS_FAST_INT_EN_1                                                            0x9801B020
#define MIS_FAST_INT_EN_1_reg_addr                                                   "0x9801B020"
#define MIS_FAST_INT_EN_1_reg                                                        0x9801B020
#define set_MIS_FAST_INT_EN_1_reg(data)   (*((volatile unsigned int*) MIS_FAST_INT_EN_1_reg)=data)
#define get_MIS_FAST_INT_EN_1_reg   (*((volatile unsigned int*) MIS_FAST_INT_EN_1_reg))
#define MIS_FAST_INT_EN_1_inst_adr                                                   "0x0008"
#define MIS_FAST_INT_EN_1_inst                                                       0x0008
#define MIS_FAST_INT_EN_1_gspi_int_shift                                             (31)
#define MIS_FAST_INT_EN_1_gspi_int_mask                                              (0x80000000)
#define MIS_FAST_INT_EN_1_gspi_int(data)                                             (0x80000000&((data)<<31))
#define MIS_FAST_INT_EN_1_gspi_int_src(data)                                         ((0x80000000&(data))>>31)
#define MIS_FAST_INT_EN_1_get_gspi_int(data)                                         ((0x80000000&(data))>>31)
#define MIS_FAST_INT_EN_1_i2c3_int_shift                                             (30)
#define MIS_FAST_INT_EN_1_i2c3_int_mask                                              (0x40000000)
#define MIS_FAST_INT_EN_1_i2c3_int(data)                                             (0x40000000&((data)<<30))
#define MIS_FAST_INT_EN_1_i2c3_int_src(data)                                         ((0x40000000&(data))>>30)
#define MIS_FAST_INT_EN_1_get_i2c3_int(data)                                         ((0x40000000&(data))>>30)
#define MIS_FAST_INT_EN_1_gp_int_shift                                               (1)
#define MIS_FAST_INT_EN_1_gp_int_mask                                                (0x3FFFFFFE)
#define MIS_FAST_INT_EN_1_gp_int(data)                                               (0x3FFFFFFE&((data)<<1))
#define MIS_FAST_INT_EN_1_gp_int_src(data)                                           ((0x3FFFFFFE&(data))>>1)
#define MIS_FAST_INT_EN_1_get_gp_int(data)                                           ((0x3FFFFFFE&(data))>>1)
#define MIS_FAST_INT_EN_1_i2c2_int_shift                                             (0)
#define MIS_FAST_INT_EN_1_i2c2_int_mask                                              (0x00000001)
#define MIS_FAST_INT_EN_1_i2c2_int(data)                                             (0x00000001&((data)<<0))
#define MIS_FAST_INT_EN_1_i2c2_int_src(data)                                         ((0x00000001&(data))>>0)
#define MIS_FAST_INT_EN_1_get_i2c2_int(data)                                         ((0x00000001&(data))>>0)


#define MIS_FAST_INT_EN_2                                                            0x9801B0A0
#define MIS_FAST_INT_EN_2_reg_addr                                                   "0x9801B0A0"
#define MIS_FAST_INT_EN_2_reg                                                        0x9801B0A0
#define set_MIS_FAST_INT_EN_2_reg(data)   (*((volatile unsigned int*) MIS_FAST_INT_EN_2_reg)=data)
#define get_MIS_FAST_INT_EN_2_reg   (*((volatile unsigned int*) MIS_FAST_INT_EN_2_reg))
#define MIS_FAST_INT_EN_2_inst_adr                                                   "0x0028"
#define MIS_FAST_INT_EN_2_inst                                                       0x0028
#define MIS_FAST_INT_EN_2_gp_int_shift                                               (1)
#define MIS_FAST_INT_EN_2_gp_int_mask                                                (0xFFFFFFFE)
#define MIS_FAST_INT_EN_2_gp_int(data)                                               (0xFFFFFFFE&((data)<<1))
#define MIS_FAST_INT_EN_2_gp_int_src(data)                                           ((0xFFFFFFFE&(data))>>1)
#define MIS_FAST_INT_EN_2_get_gp_int(data)                                           ((0xFFFFFFFE&(data))>>1)


#define MIS_FAST_INT_EN_3                                                            0x9801B0B4
#define MIS_FAST_INT_EN_3_reg_addr                                                   "0x9801B0B4"
#define MIS_FAST_INT_EN_3_reg                                                        0x9801B0B4
#define set_MIS_FAST_INT_EN_3_reg(data)   (*((volatile unsigned int*) MIS_FAST_INT_EN_3_reg)=data)
#define get_MIS_FAST_INT_EN_3_reg   (*((volatile unsigned int*) MIS_FAST_INT_EN_3_reg))
#define MIS_FAST_INT_EN_3_inst_adr                                                   "0x002D"
#define MIS_FAST_INT_EN_3_inst                                                       0x002D
#define MIS_FAST_INT_EN_3_gp_int_shift                                               (1)
#define MIS_FAST_INT_EN_3_gp_int_mask                                                (0x000007FE)
#define MIS_FAST_INT_EN_3_gp_int(data)                                               (0x000007FE&((data)<<1))
#define MIS_FAST_INT_EN_3_gp_int_src(data)                                           ((0x000007FE&(data))>>1)
#define MIS_FAST_INT_EN_3_get_gp_int(data)                                           ((0x000007FE&(data))>>1)


#define MIS_FAST_ISR                                                                 0x9801B024
#define MIS_FAST_ISR_reg_addr                                                        "0x9801B024"
#define MIS_FAST_ISR_reg                                                             0x9801B024
#define set_MIS_FAST_ISR_reg(data)   (*((volatile unsigned int*) MIS_FAST_ISR_reg)=data)
#define get_MIS_FAST_ISR_reg   (*((volatile unsigned int*) MIS_FAST_ISR_reg))
#define MIS_FAST_ISR_inst_adr                                                        "0x0009"
#define MIS_FAST_ISR_inst                                                            0x0009
#define MIS_FAST_ISR_i2c2_int_shift                                                  (5)
#define MIS_FAST_ISR_i2c2_int_mask                                                   (0x00000020)
#define MIS_FAST_ISR_i2c2_int(data)                                                  (0x00000020&((data)<<5))
#define MIS_FAST_ISR_i2c2_int_src(data)                                              ((0x00000020&(data))>>5)
#define MIS_FAST_ISR_get_i2c2_int(data)                                              ((0x00000020&(data))>>5)
#define MIS_FAST_ISR_gspi_int_shift                                                  (4)
#define MIS_FAST_ISR_gspi_int_mask                                                   (0x00000010)
#define MIS_FAST_ISR_gspi_int(data)                                                  (0x00000010&((data)<<4))
#define MIS_FAST_ISR_gspi_int_src(data)                                              ((0x00000010&(data))>>4)
#define MIS_FAST_ISR_get_gspi_int(data)                                              ((0x00000010&(data))>>4)
#define MIS_FAST_ISR_i2c3_int_shift                                                  (3)
#define MIS_FAST_ISR_i2c3_int_mask                                                   (0x00000008)
#define MIS_FAST_ISR_i2c3_int(data)                                                  (0x00000008&((data)<<3))
#define MIS_FAST_ISR_i2c3_int_src(data)                                              ((0x00000008&(data))>>3)
#define MIS_FAST_ISR_get_i2c3_int(data)                                              ((0x00000008&(data))>>3)
#define MIS_FAST_ISR_gpioda_int_shift                                                (2)
#define MIS_FAST_ISR_gpioda_int_mask                                                 (0x00000004)
#define MIS_FAST_ISR_gpioda_int(data)                                                (0x00000004&((data)<<2))
#define MIS_FAST_ISR_gpioda_int_src(data)                                            ((0x00000004&(data))>>2)
#define MIS_FAST_ISR_get_gpioda_int(data)                                            ((0x00000004&(data))>>2)
#define MIS_FAST_ISR_gpioa_int_shift                                                 (1)
#define MIS_FAST_ISR_gpioa_int_mask                                                  (0x00000002)
#define MIS_FAST_ISR_gpioa_int(data)                                                 (0x00000002&((data)<<1))
#define MIS_FAST_ISR_gpioa_int_src(data)                                             ((0x00000002&(data))>>1)
#define MIS_FAST_ISR_get_gpioa_int(data)                                             ((0x00000002&(data))>>1)
#define MIS_FAST_ISR_write_data_shift                                                (0)
#define MIS_FAST_ISR_write_data_mask                                                 (0x00000001)
#define MIS_FAST_ISR_write_data(data)                                                (0x00000001&((data)<<0))
#define MIS_FAST_ISR_write_data_src(data)                                            ((0x00000001&(data))>>0)
#define MIS_FAST_ISR_get_write_data(data)                                            ((0x00000001&(data))>>0)


#define MIS_DBG                                                                      0x9801B02C
#define MIS_DBG_reg_addr                                                             "0x9801B02C"
#define MIS_DBG_reg                                                                  0x9801B02C
#define set_MIS_DBG_reg(data)   (*((volatile unsigned int*) MIS_DBG_reg)=data)
#define get_MIS_DBG_reg   (*((volatile unsigned int*) MIS_DBG_reg))
#define MIS_DBG_inst_adr                                                             "0x000B"
#define MIS_DBG_inst                                                                 0x000B
#define MIS_DBG_write_enable3_shift                                                  (11)
#define MIS_DBG_write_enable3_mask                                                   (0x00000800)
#define MIS_DBG_write_enable3(data)                                                  (0x00000800&((data)<<11))
#define MIS_DBG_write_enable3_src(data)                                              ((0x00000800&(data))>>11)
#define MIS_DBG_get_write_enable3(data)                                              ((0x00000800&(data))>>11)
#define MIS_DBG_sel1_shift                                                           (7)
#define MIS_DBG_sel1_mask                                                            (0x00000780)
#define MIS_DBG_sel1(data)                                                           (0x00000780&((data)<<7))
#define MIS_DBG_sel1_src(data)                                                       ((0x00000780&(data))>>7)
#define MIS_DBG_get_sel1(data)                                                       ((0x00000780&(data))>>7)
#define MIS_DBG_write_enable2_shift                                                  (6)
#define MIS_DBG_write_enable2_mask                                                   (0x00000040)
#define MIS_DBG_write_enable2(data)                                                  (0x00000040&((data)<<6))
#define MIS_DBG_write_enable2_src(data)                                              ((0x00000040&(data))>>6)
#define MIS_DBG_get_write_enable2(data)                                              ((0x00000040&(data))>>6)
#define MIS_DBG_sel0_shift                                                           (2)
#define MIS_DBG_sel0_mask                                                            (0x0000003C)
#define MIS_DBG_sel0(data)                                                           (0x0000003C&((data)<<2))
#define MIS_DBG_sel0_src(data)                                                       ((0x0000003C&(data))>>2)
#define MIS_DBG_get_sel0(data)                                                       ((0x0000003C&(data))>>2)
#define MIS_DBG_write_enable1_shift                                                  (1)
#define MIS_DBG_write_enable1_mask                                                   (0x00000002)
#define MIS_DBG_write_enable1(data)                                                  (0x00000002&((data)<<1))
#define MIS_DBG_write_enable1_src(data)                                              ((0x00000002&(data))>>1)
#define MIS_DBG_get_write_enable1(data)                                              ((0x00000002&(data))>>1)
#define MIS_DBG_enable_shift                                                         (0)
#define MIS_DBG_enable_mask                                                          (0x00000001)
#define MIS_DBG_enable(data)                                                         (0x00000001&((data)<<0))
#define MIS_DBG_enable_src(data)                                                     ((0x00000001&(data))>>0)
#define MIS_DBG_get_enable(data)                                                     ((0x00000001&(data))>>0)


#define MIS_DUMMY                                                                    0x9801B030
#define MIS_DUMMY_reg_addr                                                           "0x9801B030"
#define MIS_DUMMY_reg                                                                0x9801B030
#define set_MIS_DUMMY_reg(data)   (*((volatile unsigned int*) MIS_DUMMY_reg)=data)
#define get_MIS_DUMMY_reg   (*((volatile unsigned int*) MIS_DUMMY_reg))
#define MIS_DUMMY_inst_adr                                                           "0x000C"
#define MIS_DUMMY_inst                                                               0x000C
#define MIS_DUMMY_write_enable4_shift                                                (31)
#define MIS_DUMMY_write_enable4_mask                                                 (0x80000000)
#define MIS_DUMMY_write_enable4(data)                                                (0x80000000&((data)<<31))
#define MIS_DUMMY_write_enable4_src(data)                                            ((0x80000000&(data))>>31)
#define MIS_DUMMY_get_write_enable4(data)                                            ((0x80000000&(data))>>31)
#define MIS_DUMMY_rvd4_shift                                                         (24)
#define MIS_DUMMY_rvd4_mask                                                          (0x7F000000)
#define MIS_DUMMY_rvd4(data)                                                         (0x7F000000&((data)<<24))
#define MIS_DUMMY_rvd4_src(data)                                                     ((0x7F000000&(data))>>24)
#define MIS_DUMMY_get_rvd4(data)                                                     ((0x7F000000&(data))>>24)
#define MIS_DUMMY_write_enable3_shift                                                (23)
#define MIS_DUMMY_write_enable3_mask                                                 (0x00800000)
#define MIS_DUMMY_write_enable3(data)                                                (0x00800000&((data)<<23))
#define MIS_DUMMY_write_enable3_src(data)                                            ((0x00800000&(data))>>23)
#define MIS_DUMMY_get_write_enable3(data)                                            ((0x00800000&(data))>>23)
#define MIS_DUMMY_rvd3_shift                                                         (16)
#define MIS_DUMMY_rvd3_mask                                                          (0x007F0000)
#define MIS_DUMMY_rvd3(data)                                                         (0x007F0000&((data)<<16))
#define MIS_DUMMY_rvd3_src(data)                                                     ((0x007F0000&(data))>>16)
#define MIS_DUMMY_get_rvd3(data)                                                     ((0x007F0000&(data))>>16)
#define MIS_DUMMY_write_enable2_shift                                                (15)
#define MIS_DUMMY_write_enable2_mask                                                 (0x00008000)
#define MIS_DUMMY_write_enable2(data)                                                (0x00008000&((data)<<15))
#define MIS_DUMMY_write_enable2_src(data)                                            ((0x00008000&(data))>>15)
#define MIS_DUMMY_get_write_enable2(data)                                            ((0x00008000&(data))>>15)
#define MIS_DUMMY_rvd2_shift                                                         (8)
#define MIS_DUMMY_rvd2_mask                                                          (0x00007F00)
#define MIS_DUMMY_rvd2(data)                                                         (0x00007F00&((data)<<8))
#define MIS_DUMMY_rvd2_src(data)                                                     ((0x00007F00&(data))>>8)
#define MIS_DUMMY_get_rvd2(data)                                                     ((0x00007F00&(data))>>8)
#define MIS_DUMMY_write_enable1_shift                                                (7)
#define MIS_DUMMY_write_enable1_mask                                                 (0x00000080)
#define MIS_DUMMY_write_enable1(data)                                                (0x00000080&((data)<<7))
#define MIS_DUMMY_write_enable1_src(data)                                            ((0x00000080&(data))>>7)
#define MIS_DUMMY_get_write_enable1(data)                                            ((0x00000080&(data))>>7)
#define MIS_DUMMY_rvd1_shift                                                         (0)
#define MIS_DUMMY_rvd1_mask                                                          (0x0000007F)
#define MIS_DUMMY_rvd1(data)                                                         (0x0000007F&((data)<<0))
#define MIS_DUMMY_rvd1_src(data)                                                     ((0x0000007F&(data))>>0)
#define MIS_DUMMY_get_rvd1(data)                                                     ((0x0000007F&(data))>>0)


#define MIS_UMSK_ISR_GP0A                                                            0x9801B040
#define MIS_UMSK_ISR_GP0A_reg_addr                                                   "0x9801B040"
#define MIS_UMSK_ISR_GP0A_reg                                                        0x9801B040
#define set_MIS_UMSK_ISR_GP0A_reg(data)   (*((volatile unsigned int*) MIS_UMSK_ISR_GP0A_reg)=data)
#define get_MIS_UMSK_ISR_GP0A_reg   (*((volatile unsigned int*) MIS_UMSK_ISR_GP0A_reg))
#define MIS_UMSK_ISR_GP0A_inst_adr                                                   "0x0010"
#define MIS_UMSK_ISR_GP0A_inst                                                       0x0010
#define MIS_UMSK_ISR_GP0A_int30_shift                                                (31)
#define MIS_UMSK_ISR_GP0A_int30_mask                                                 (0x80000000)
#define MIS_UMSK_ISR_GP0A_int30(data)                                                (0x80000000&((data)<<31))
#define MIS_UMSK_ISR_GP0A_int30_src(data)                                            ((0x80000000&(data))>>31)
#define MIS_UMSK_ISR_GP0A_get_int30(data)                                            ((0x80000000&(data))>>31)
#define MIS_UMSK_ISR_GP0A_int29_shift                                                (30)
#define MIS_UMSK_ISR_GP0A_int29_mask                                                 (0x40000000)
#define MIS_UMSK_ISR_GP0A_int29(data)                                                (0x40000000&((data)<<30))
#define MIS_UMSK_ISR_GP0A_int29_src(data)                                            ((0x40000000&(data))>>30)
#define MIS_UMSK_ISR_GP0A_get_int29(data)                                            ((0x40000000&(data))>>30)
#define MIS_UMSK_ISR_GP0A_int28_shift                                                (29)
#define MIS_UMSK_ISR_GP0A_int28_mask                                                 (0x20000000)
#define MIS_UMSK_ISR_GP0A_int28(data)                                                (0x20000000&((data)<<29))
#define MIS_UMSK_ISR_GP0A_int28_src(data)                                            ((0x20000000&(data))>>29)
#define MIS_UMSK_ISR_GP0A_get_int28(data)                                            ((0x20000000&(data))>>29)
#define MIS_UMSK_ISR_GP0A_int27_shift                                                (28)
#define MIS_UMSK_ISR_GP0A_int27_mask                                                 (0x10000000)
#define MIS_UMSK_ISR_GP0A_int27(data)                                                (0x10000000&((data)<<28))
#define MIS_UMSK_ISR_GP0A_int27_src(data)                                            ((0x10000000&(data))>>28)
#define MIS_UMSK_ISR_GP0A_get_int27(data)                                            ((0x10000000&(data))>>28)
#define MIS_UMSK_ISR_GP0A_int26_shift                                                (27)
#define MIS_UMSK_ISR_GP0A_int26_mask                                                 (0x08000000)
#define MIS_UMSK_ISR_GP0A_int26(data)                                                (0x08000000&((data)<<27))
#define MIS_UMSK_ISR_GP0A_int26_src(data)                                            ((0x08000000&(data))>>27)
#define MIS_UMSK_ISR_GP0A_get_int26(data)                                            ((0x08000000&(data))>>27)
#define MIS_UMSK_ISR_GP0A_int25_shift                                                (26)
#define MIS_UMSK_ISR_GP0A_int25_mask                                                 (0x04000000)
#define MIS_UMSK_ISR_GP0A_int25(data)                                                (0x04000000&((data)<<26))
#define MIS_UMSK_ISR_GP0A_int25_src(data)                                            ((0x04000000&(data))>>26)
#define MIS_UMSK_ISR_GP0A_get_int25(data)                                            ((0x04000000&(data))>>26)
#define MIS_UMSK_ISR_GP0A_int24_shift                                                (25)
#define MIS_UMSK_ISR_GP0A_int24_mask                                                 (0x02000000)
#define MIS_UMSK_ISR_GP0A_int24(data)                                                (0x02000000&((data)<<25))
#define MIS_UMSK_ISR_GP0A_int24_src(data)                                            ((0x02000000&(data))>>25)
#define MIS_UMSK_ISR_GP0A_get_int24(data)                                            ((0x02000000&(data))>>25)
#define MIS_UMSK_ISR_GP0A_int23_shift                                                (24)
#define MIS_UMSK_ISR_GP0A_int23_mask                                                 (0x01000000)
#define MIS_UMSK_ISR_GP0A_int23(data)                                                (0x01000000&((data)<<24))
#define MIS_UMSK_ISR_GP0A_int23_src(data)                                            ((0x01000000&(data))>>24)
#define MIS_UMSK_ISR_GP0A_get_int23(data)                                            ((0x01000000&(data))>>24)
#define MIS_UMSK_ISR_GP0A_int22_shift                                                (23)
#define MIS_UMSK_ISR_GP0A_int22_mask                                                 (0x00800000)
#define MIS_UMSK_ISR_GP0A_int22(data)                                                (0x00800000&((data)<<23))
#define MIS_UMSK_ISR_GP0A_int22_src(data)                                            ((0x00800000&(data))>>23)
#define MIS_UMSK_ISR_GP0A_get_int22(data)                                            ((0x00800000&(data))>>23)
#define MIS_UMSK_ISR_GP0A_int21_shift                                                (22)
#define MIS_UMSK_ISR_GP0A_int21_mask                                                 (0x00400000)
#define MIS_UMSK_ISR_GP0A_int21(data)                                                (0x00400000&((data)<<22))
#define MIS_UMSK_ISR_GP0A_int21_src(data)                                            ((0x00400000&(data))>>22)
#define MIS_UMSK_ISR_GP0A_get_int21(data)                                            ((0x00400000&(data))>>22)
#define MIS_UMSK_ISR_GP0A_int20_shift                                                (21)
#define MIS_UMSK_ISR_GP0A_int20_mask                                                 (0x00200000)
#define MIS_UMSK_ISR_GP0A_int20(data)                                                (0x00200000&((data)<<21))
#define MIS_UMSK_ISR_GP0A_int20_src(data)                                            ((0x00200000&(data))>>21)
#define MIS_UMSK_ISR_GP0A_get_int20(data)                                            ((0x00200000&(data))>>21)
#define MIS_UMSK_ISR_GP0A_int19_shift                                                (20)
#define MIS_UMSK_ISR_GP0A_int19_mask                                                 (0x00100000)
#define MIS_UMSK_ISR_GP0A_int19(data)                                                (0x00100000&((data)<<20))
#define MIS_UMSK_ISR_GP0A_int19_src(data)                                            ((0x00100000&(data))>>20)
#define MIS_UMSK_ISR_GP0A_get_int19(data)                                            ((0x00100000&(data))>>20)
#define MIS_UMSK_ISR_GP0A_int18_shift                                                (19)
#define MIS_UMSK_ISR_GP0A_int18_mask                                                 (0x00080000)
#define MIS_UMSK_ISR_GP0A_int18(data)                                                (0x00080000&((data)<<19))
#define MIS_UMSK_ISR_GP0A_int18_src(data)                                            ((0x00080000&(data))>>19)
#define MIS_UMSK_ISR_GP0A_get_int18(data)                                            ((0x00080000&(data))>>19)
#define MIS_UMSK_ISR_GP0A_int17_shift                                                (18)
#define MIS_UMSK_ISR_GP0A_int17_mask                                                 (0x00040000)
#define MIS_UMSK_ISR_GP0A_int17(data)                                                (0x00040000&((data)<<18))
#define MIS_UMSK_ISR_GP0A_int17_src(data)                                            ((0x00040000&(data))>>18)
#define MIS_UMSK_ISR_GP0A_get_int17(data)                                            ((0x00040000&(data))>>18)
#define MIS_UMSK_ISR_GP0A_int16_shift                                                (17)
#define MIS_UMSK_ISR_GP0A_int16_mask                                                 (0x00020000)
#define MIS_UMSK_ISR_GP0A_int16(data)                                                (0x00020000&((data)<<17))
#define MIS_UMSK_ISR_GP0A_int16_src(data)                                            ((0x00020000&(data))>>17)
#define MIS_UMSK_ISR_GP0A_get_int16(data)                                            ((0x00020000&(data))>>17)
#define MIS_UMSK_ISR_GP0A_int15_shift                                                (16)
#define MIS_UMSK_ISR_GP0A_int15_mask                                                 (0x00010000)
#define MIS_UMSK_ISR_GP0A_int15(data)                                                (0x00010000&((data)<<16))
#define MIS_UMSK_ISR_GP0A_int15_src(data)                                            ((0x00010000&(data))>>16)
#define MIS_UMSK_ISR_GP0A_get_int15(data)                                            ((0x00010000&(data))>>16)
#define MIS_UMSK_ISR_GP0A_int14_shift                                                (15)
#define MIS_UMSK_ISR_GP0A_int14_mask                                                 (0x00008000)
#define MIS_UMSK_ISR_GP0A_int14(data)                                                (0x00008000&((data)<<15))
#define MIS_UMSK_ISR_GP0A_int14_src(data)                                            ((0x00008000&(data))>>15)
#define MIS_UMSK_ISR_GP0A_get_int14(data)                                            ((0x00008000&(data))>>15)
#define MIS_UMSK_ISR_GP0A_int13_shift                                                (14)
#define MIS_UMSK_ISR_GP0A_int13_mask                                                 (0x00004000)
#define MIS_UMSK_ISR_GP0A_int13(data)                                                (0x00004000&((data)<<14))
#define MIS_UMSK_ISR_GP0A_int13_src(data)                                            ((0x00004000&(data))>>14)
#define MIS_UMSK_ISR_GP0A_get_int13(data)                                            ((0x00004000&(data))>>14)
#define MIS_UMSK_ISR_GP0A_int12_shift                                                (13)
#define MIS_UMSK_ISR_GP0A_int12_mask                                                 (0x00002000)
#define MIS_UMSK_ISR_GP0A_int12(data)                                                (0x00002000&((data)<<13))
#define MIS_UMSK_ISR_GP0A_int12_src(data)                                            ((0x00002000&(data))>>13)
#define MIS_UMSK_ISR_GP0A_get_int12(data)                                            ((0x00002000&(data))>>13)
#define MIS_UMSK_ISR_GP0A_int11_shift                                                (12)
#define MIS_UMSK_ISR_GP0A_int11_mask                                                 (0x00001000)
#define MIS_UMSK_ISR_GP0A_int11(data)                                                (0x00001000&((data)<<12))
#define MIS_UMSK_ISR_GP0A_int11_src(data)                                            ((0x00001000&(data))>>12)
#define MIS_UMSK_ISR_GP0A_get_int11(data)                                            ((0x00001000&(data))>>12)
#define MIS_UMSK_ISR_GP0A_int10_shift                                                (11)
#define MIS_UMSK_ISR_GP0A_int10_mask                                                 (0x00000800)
#define MIS_UMSK_ISR_GP0A_int10(data)                                                (0x00000800&((data)<<11))
#define MIS_UMSK_ISR_GP0A_int10_src(data)                                            ((0x00000800&(data))>>11)
#define MIS_UMSK_ISR_GP0A_get_int10(data)                                            ((0x00000800&(data))>>11)
#define MIS_UMSK_ISR_GP0A_int9_shift                                                 (10)
#define MIS_UMSK_ISR_GP0A_int9_mask                                                  (0x00000400)
#define MIS_UMSK_ISR_GP0A_int9(data)                                                 (0x00000400&((data)<<10))
#define MIS_UMSK_ISR_GP0A_int9_src(data)                                             ((0x00000400&(data))>>10)
#define MIS_UMSK_ISR_GP0A_get_int9(data)                                             ((0x00000400&(data))>>10)
#define MIS_UMSK_ISR_GP0A_int8_shift                                                 (9)
#define MIS_UMSK_ISR_GP0A_int8_mask                                                  (0x00000200)
#define MIS_UMSK_ISR_GP0A_int8(data)                                                 (0x00000200&((data)<<9))
#define MIS_UMSK_ISR_GP0A_int8_src(data)                                             ((0x00000200&(data))>>9)
#define MIS_UMSK_ISR_GP0A_get_int8(data)                                             ((0x00000200&(data))>>9)
#define MIS_UMSK_ISR_GP0A_int7_shift                                                 (8)
#define MIS_UMSK_ISR_GP0A_int7_mask                                                  (0x00000100)
#define MIS_UMSK_ISR_GP0A_int7(data)                                                 (0x00000100&((data)<<8))
#define MIS_UMSK_ISR_GP0A_int7_src(data)                                             ((0x00000100&(data))>>8)
#define MIS_UMSK_ISR_GP0A_get_int7(data)                                             ((0x00000100&(data))>>8)
#define MIS_UMSK_ISR_GP0A_int6_shift                                                 (7)
#define MIS_UMSK_ISR_GP0A_int6_mask                                                  (0x00000080)
#define MIS_UMSK_ISR_GP0A_int6(data)                                                 (0x00000080&((data)<<7))
#define MIS_UMSK_ISR_GP0A_int6_src(data)                                             ((0x00000080&(data))>>7)
#define MIS_UMSK_ISR_GP0A_get_int6(data)                                             ((0x00000080&(data))>>7)
#define MIS_UMSK_ISR_GP0A_int5_shift                                                 (6)
#define MIS_UMSK_ISR_GP0A_int5_mask                                                  (0x00000040)
#define MIS_UMSK_ISR_GP0A_int5(data)                                                 (0x00000040&((data)<<6))
#define MIS_UMSK_ISR_GP0A_int5_src(data)                                             ((0x00000040&(data))>>6)
#define MIS_UMSK_ISR_GP0A_get_int5(data)                                             ((0x00000040&(data))>>6)
#define MIS_UMSK_ISR_GP0A_int4_shift                                                 (5)
#define MIS_UMSK_ISR_GP0A_int4_mask                                                  (0x00000020)
#define MIS_UMSK_ISR_GP0A_int4(data)                                                 (0x00000020&((data)<<5))
#define MIS_UMSK_ISR_GP0A_int4_src(data)                                             ((0x00000020&(data))>>5)
#define MIS_UMSK_ISR_GP0A_get_int4(data)                                             ((0x00000020&(data))>>5)
#define MIS_UMSK_ISR_GP0A_int3_shift                                                 (4)
#define MIS_UMSK_ISR_GP0A_int3_mask                                                  (0x00000010)
#define MIS_UMSK_ISR_GP0A_int3(data)                                                 (0x00000010&((data)<<4))
#define MIS_UMSK_ISR_GP0A_int3_src(data)                                             ((0x00000010&(data))>>4)
#define MIS_UMSK_ISR_GP0A_get_int3(data)                                             ((0x00000010&(data))>>4)
#define MIS_UMSK_ISR_GP0A_int2_shift                                                 (3)
#define MIS_UMSK_ISR_GP0A_int2_mask                                                  (0x00000008)
#define MIS_UMSK_ISR_GP0A_int2(data)                                                 (0x00000008&((data)<<3))
#define MIS_UMSK_ISR_GP0A_int2_src(data)                                             ((0x00000008&(data))>>3)
#define MIS_UMSK_ISR_GP0A_get_int2(data)                                             ((0x00000008&(data))>>3)
#define MIS_UMSK_ISR_GP0A_int1_shift                                                 (2)
#define MIS_UMSK_ISR_GP0A_int1_mask                                                  (0x00000004)
#define MIS_UMSK_ISR_GP0A_int1(data)                                                 (0x00000004&((data)<<2))
#define MIS_UMSK_ISR_GP0A_int1_src(data)                                             ((0x00000004&(data))>>2)
#define MIS_UMSK_ISR_GP0A_get_int1(data)                                             ((0x00000004&(data))>>2)
#define MIS_UMSK_ISR_GP0A_int0_shift                                                 (1)
#define MIS_UMSK_ISR_GP0A_int0_mask                                                  (0x00000002)
#define MIS_UMSK_ISR_GP0A_int0(data)                                                 (0x00000002&((data)<<1))
#define MIS_UMSK_ISR_GP0A_int0_src(data)                                             ((0x00000002&(data))>>1)
#define MIS_UMSK_ISR_GP0A_get_int0(data)                                             ((0x00000002&(data))>>1)
#define MIS_UMSK_ISR_GP0A_write_data_shift                                           (0)
#define MIS_UMSK_ISR_GP0A_write_data_mask                                            (0x00000001)
#define MIS_UMSK_ISR_GP0A_write_data(data)                                           (0x00000001&((data)<<0))
#define MIS_UMSK_ISR_GP0A_write_data_src(data)                                       ((0x00000001&(data))>>0)
#define MIS_UMSK_ISR_GP0A_get_write_data(data)                                       ((0x00000001&(data))>>0)


#define MIS_UMSK_ISR_GP1A                                                            0x9801B044
#define MIS_UMSK_ISR_GP1A_reg_addr                                                   "0x9801B044"
#define MIS_UMSK_ISR_GP1A_reg                                                        0x9801B044
#define set_MIS_UMSK_ISR_GP1A_reg(data)   (*((volatile unsigned int*) MIS_UMSK_ISR_GP1A_reg)=data)
#define get_MIS_UMSK_ISR_GP1A_reg   (*((volatile unsigned int*) MIS_UMSK_ISR_GP1A_reg))
#define MIS_UMSK_ISR_GP1A_inst_adr                                                   "0x0011"
#define MIS_UMSK_ISR_GP1A_inst                                                       0x0011
#define MIS_UMSK_ISR_GP1A_int61_shift                                                (31)
#define MIS_UMSK_ISR_GP1A_int61_mask                                                 (0x80000000)
#define MIS_UMSK_ISR_GP1A_int61(data)                                                (0x80000000&((data)<<31))
#define MIS_UMSK_ISR_GP1A_int61_src(data)                                            ((0x80000000&(data))>>31)
#define MIS_UMSK_ISR_GP1A_get_int61(data)                                            ((0x80000000&(data))>>31)
#define MIS_UMSK_ISR_GP1A_int60_shift                                                (30)
#define MIS_UMSK_ISR_GP1A_int60_mask                                                 (0x40000000)
#define MIS_UMSK_ISR_GP1A_int60(data)                                                (0x40000000&((data)<<30))
#define MIS_UMSK_ISR_GP1A_int60_src(data)                                            ((0x40000000&(data))>>30)
#define MIS_UMSK_ISR_GP1A_get_int60(data)                                            ((0x40000000&(data))>>30)
#define MIS_UMSK_ISR_GP1A_int59_shift                                                (29)
#define MIS_UMSK_ISR_GP1A_int59_mask                                                 (0x20000000)
#define MIS_UMSK_ISR_GP1A_int59(data)                                                (0x20000000&((data)<<29))
#define MIS_UMSK_ISR_GP1A_int59_src(data)                                            ((0x20000000&(data))>>29)
#define MIS_UMSK_ISR_GP1A_get_int59(data)                                            ((0x20000000&(data))>>29)
#define MIS_UMSK_ISR_GP1A_int58_shift                                                (28)
#define MIS_UMSK_ISR_GP1A_int58_mask                                                 (0x10000000)
#define MIS_UMSK_ISR_GP1A_int58(data)                                                (0x10000000&((data)<<28))
#define MIS_UMSK_ISR_GP1A_int58_src(data)                                            ((0x10000000&(data))>>28)
#define MIS_UMSK_ISR_GP1A_get_int58(data)                                            ((0x10000000&(data))>>28)
#define MIS_UMSK_ISR_GP1A_int57_shift                                                (27)
#define MIS_UMSK_ISR_GP1A_int57_mask                                                 (0x08000000)
#define MIS_UMSK_ISR_GP1A_int57(data)                                                (0x08000000&((data)<<27))
#define MIS_UMSK_ISR_GP1A_int57_src(data)                                            ((0x08000000&(data))>>27)
#define MIS_UMSK_ISR_GP1A_get_int57(data)                                            ((0x08000000&(data))>>27)
#define MIS_UMSK_ISR_GP1A_int56_shift                                                (26)
#define MIS_UMSK_ISR_GP1A_int56_mask                                                 (0x04000000)
#define MIS_UMSK_ISR_GP1A_int56(data)                                                (0x04000000&((data)<<26))
#define MIS_UMSK_ISR_GP1A_int56_src(data)                                            ((0x04000000&(data))>>26)
#define MIS_UMSK_ISR_GP1A_get_int56(data)                                            ((0x04000000&(data))>>26)
#define MIS_UMSK_ISR_GP1A_int55_shift                                                (25)
#define MIS_UMSK_ISR_GP1A_int55_mask                                                 (0x02000000)
#define MIS_UMSK_ISR_GP1A_int55(data)                                                (0x02000000&((data)<<25))
#define MIS_UMSK_ISR_GP1A_int55_src(data)                                            ((0x02000000&(data))>>25)
#define MIS_UMSK_ISR_GP1A_get_int55(data)                                            ((0x02000000&(data))>>25)
#define MIS_UMSK_ISR_GP1A_int54_shift                                                (24)
#define MIS_UMSK_ISR_GP1A_int54_mask                                                 (0x01000000)
#define MIS_UMSK_ISR_GP1A_int54(data)                                                (0x01000000&((data)<<24))
#define MIS_UMSK_ISR_GP1A_int54_src(data)                                            ((0x01000000&(data))>>24)
#define MIS_UMSK_ISR_GP1A_get_int54(data)                                            ((0x01000000&(data))>>24)
#define MIS_UMSK_ISR_GP1A_int53_shift                                                (23)
#define MIS_UMSK_ISR_GP1A_int53_mask                                                 (0x00800000)
#define MIS_UMSK_ISR_GP1A_int53(data)                                                (0x00800000&((data)<<23))
#define MIS_UMSK_ISR_GP1A_int53_src(data)                                            ((0x00800000&(data))>>23)
#define MIS_UMSK_ISR_GP1A_get_int53(data)                                            ((0x00800000&(data))>>23)
#define MIS_UMSK_ISR_GP1A_int52_shift                                                (22)
#define MIS_UMSK_ISR_GP1A_int52_mask                                                 (0x00400000)
#define MIS_UMSK_ISR_GP1A_int52(data)                                                (0x00400000&((data)<<22))
#define MIS_UMSK_ISR_GP1A_int52_src(data)                                            ((0x00400000&(data))>>22)
#define MIS_UMSK_ISR_GP1A_get_int52(data)                                            ((0x00400000&(data))>>22)
#define MIS_UMSK_ISR_GP1A_int51_shift                                                (21)
#define MIS_UMSK_ISR_GP1A_int51_mask                                                 (0x00200000)
#define MIS_UMSK_ISR_GP1A_int51(data)                                                (0x00200000&((data)<<21))
#define MIS_UMSK_ISR_GP1A_int51_src(data)                                            ((0x00200000&(data))>>21)
#define MIS_UMSK_ISR_GP1A_get_int51(data)                                            ((0x00200000&(data))>>21)
#define MIS_UMSK_ISR_GP1A_int50_shift                                                (20)
#define MIS_UMSK_ISR_GP1A_int50_mask                                                 (0x00100000)
#define MIS_UMSK_ISR_GP1A_int50(data)                                                (0x00100000&((data)<<20))
#define MIS_UMSK_ISR_GP1A_int50_src(data)                                            ((0x00100000&(data))>>20)
#define MIS_UMSK_ISR_GP1A_get_int50(data)                                            ((0x00100000&(data))>>20)
#define MIS_UMSK_ISR_GP1A_int49_shift                                                (19)
#define MIS_UMSK_ISR_GP1A_int49_mask                                                 (0x00080000)
#define MIS_UMSK_ISR_GP1A_int49(data)                                                (0x00080000&((data)<<19))
#define MIS_UMSK_ISR_GP1A_int49_src(data)                                            ((0x00080000&(data))>>19)
#define MIS_UMSK_ISR_GP1A_get_int49(data)                                            ((0x00080000&(data))>>19)
#define MIS_UMSK_ISR_GP1A_int48_shift                                                (18)
#define MIS_UMSK_ISR_GP1A_int48_mask                                                 (0x00040000)
#define MIS_UMSK_ISR_GP1A_int48(data)                                                (0x00040000&((data)<<18))
#define MIS_UMSK_ISR_GP1A_int48_src(data)                                            ((0x00040000&(data))>>18)
#define MIS_UMSK_ISR_GP1A_get_int48(data)                                            ((0x00040000&(data))>>18)
#define MIS_UMSK_ISR_GP1A_int47_shift                                                (17)
#define MIS_UMSK_ISR_GP1A_int47_mask                                                 (0x00020000)
#define MIS_UMSK_ISR_GP1A_int47(data)                                                (0x00020000&((data)<<17))
#define MIS_UMSK_ISR_GP1A_int47_src(data)                                            ((0x00020000&(data))>>17)
#define MIS_UMSK_ISR_GP1A_get_int47(data)                                            ((0x00020000&(data))>>17)
#define MIS_UMSK_ISR_GP1A_int46_shift                                                (16)
#define MIS_UMSK_ISR_GP1A_int46_mask                                                 (0x00010000)
#define MIS_UMSK_ISR_GP1A_int46(data)                                                (0x00010000&((data)<<16))
#define MIS_UMSK_ISR_GP1A_int46_src(data)                                            ((0x00010000&(data))>>16)
#define MIS_UMSK_ISR_GP1A_get_int46(data)                                            ((0x00010000&(data))>>16)
#define MIS_UMSK_ISR_GP1A_int45_shift                                                (15)
#define MIS_UMSK_ISR_GP1A_int45_mask                                                 (0x00008000)
#define MIS_UMSK_ISR_GP1A_int45(data)                                                (0x00008000&((data)<<15))
#define MIS_UMSK_ISR_GP1A_int45_src(data)                                            ((0x00008000&(data))>>15)
#define MIS_UMSK_ISR_GP1A_get_int45(data)                                            ((0x00008000&(data))>>15)
#define MIS_UMSK_ISR_GP1A_int44_shift                                                (14)
#define MIS_UMSK_ISR_GP1A_int44_mask                                                 (0x00004000)
#define MIS_UMSK_ISR_GP1A_int44(data)                                                (0x00004000&((data)<<14))
#define MIS_UMSK_ISR_GP1A_int44_src(data)                                            ((0x00004000&(data))>>14)
#define MIS_UMSK_ISR_GP1A_get_int44(data)                                            ((0x00004000&(data))>>14)
#define MIS_UMSK_ISR_GP1A_int43_shift                                                (13)
#define MIS_UMSK_ISR_GP1A_int43_mask                                                 (0x00002000)
#define MIS_UMSK_ISR_GP1A_int43(data)                                                (0x00002000&((data)<<13))
#define MIS_UMSK_ISR_GP1A_int43_src(data)                                            ((0x00002000&(data))>>13)
#define MIS_UMSK_ISR_GP1A_get_int43(data)                                            ((0x00002000&(data))>>13)
#define MIS_UMSK_ISR_GP1A_int42_shift                                                (12)
#define MIS_UMSK_ISR_GP1A_int42_mask                                                 (0x00001000)
#define MIS_UMSK_ISR_GP1A_int42(data)                                                (0x00001000&((data)<<12))
#define MIS_UMSK_ISR_GP1A_int42_src(data)                                            ((0x00001000&(data))>>12)
#define MIS_UMSK_ISR_GP1A_get_int42(data)                                            ((0x00001000&(data))>>12)
#define MIS_UMSK_ISR_GP1A_int41_shift                                                (11)
#define MIS_UMSK_ISR_GP1A_int41_mask                                                 (0x00000800)
#define MIS_UMSK_ISR_GP1A_int41(data)                                                (0x00000800&((data)<<11))
#define MIS_UMSK_ISR_GP1A_int41_src(data)                                            ((0x00000800&(data))>>11)
#define MIS_UMSK_ISR_GP1A_get_int41(data)                                            ((0x00000800&(data))>>11)
#define MIS_UMSK_ISR_GP1A_int40_shift                                                (10)
#define MIS_UMSK_ISR_GP1A_int40_mask                                                 (0x00000400)
#define MIS_UMSK_ISR_GP1A_int40(data)                                                (0x00000400&((data)<<10))
#define MIS_UMSK_ISR_GP1A_int40_src(data)                                            ((0x00000400&(data))>>10)
#define MIS_UMSK_ISR_GP1A_get_int40(data)                                            ((0x00000400&(data))>>10)
#define MIS_UMSK_ISR_GP1A_int39_shift                                                (9)
#define MIS_UMSK_ISR_GP1A_int39_mask                                                 (0x00000200)
#define MIS_UMSK_ISR_GP1A_int39(data)                                                (0x00000200&((data)<<9))
#define MIS_UMSK_ISR_GP1A_int39_src(data)                                            ((0x00000200&(data))>>9)
#define MIS_UMSK_ISR_GP1A_get_int39(data)                                            ((0x00000200&(data))>>9)
#define MIS_UMSK_ISR_GP1A_int38_shift                                                (8)
#define MIS_UMSK_ISR_GP1A_int38_mask                                                 (0x00000100)
#define MIS_UMSK_ISR_GP1A_int38(data)                                                (0x00000100&((data)<<8))
#define MIS_UMSK_ISR_GP1A_int38_src(data)                                            ((0x00000100&(data))>>8)
#define MIS_UMSK_ISR_GP1A_get_int38(data)                                            ((0x00000100&(data))>>8)
#define MIS_UMSK_ISR_GP1A_int37_shift                                                (7)
#define MIS_UMSK_ISR_GP1A_int37_mask                                                 (0x00000080)
#define MIS_UMSK_ISR_GP1A_int37(data)                                                (0x00000080&((data)<<7))
#define MIS_UMSK_ISR_GP1A_int37_src(data)                                            ((0x00000080&(data))>>7)
#define MIS_UMSK_ISR_GP1A_get_int37(data)                                            ((0x00000080&(data))>>7)
#define MIS_UMSK_ISR_GP1A_int36_shift                                                (6)
#define MIS_UMSK_ISR_GP1A_int36_mask                                                 (0x00000040)
#define MIS_UMSK_ISR_GP1A_int36(data)                                                (0x00000040&((data)<<6))
#define MIS_UMSK_ISR_GP1A_int36_src(data)                                            ((0x00000040&(data))>>6)
#define MIS_UMSK_ISR_GP1A_get_int36(data)                                            ((0x00000040&(data))>>6)
#define MIS_UMSK_ISR_GP1A_int35_shift                                                (5)
#define MIS_UMSK_ISR_GP1A_int35_mask                                                 (0x00000020)
#define MIS_UMSK_ISR_GP1A_int35(data)                                                (0x00000020&((data)<<5))
#define MIS_UMSK_ISR_GP1A_int35_src(data)                                            ((0x00000020&(data))>>5)
#define MIS_UMSK_ISR_GP1A_get_int35(data)                                            ((0x00000020&(data))>>5)
#define MIS_UMSK_ISR_GP1A_int34_shift                                                (4)
#define MIS_UMSK_ISR_GP1A_int34_mask                                                 (0x00000010)
#define MIS_UMSK_ISR_GP1A_int34(data)                                                (0x00000010&((data)<<4))
#define MIS_UMSK_ISR_GP1A_int34_src(data)                                            ((0x00000010&(data))>>4)
#define MIS_UMSK_ISR_GP1A_get_int34(data)                                            ((0x00000010&(data))>>4)
#define MIS_UMSK_ISR_GP1A_int33_shift                                                (3)
#define MIS_UMSK_ISR_GP1A_int33_mask                                                 (0x00000008)
#define MIS_UMSK_ISR_GP1A_int33(data)                                                (0x00000008&((data)<<3))
#define MIS_UMSK_ISR_GP1A_int33_src(data)                                            ((0x00000008&(data))>>3)
#define MIS_UMSK_ISR_GP1A_get_int33(data)                                            ((0x00000008&(data))>>3)
#define MIS_UMSK_ISR_GP1A_int32_shift                                                (2)
#define MIS_UMSK_ISR_GP1A_int32_mask                                                 (0x00000004)
#define MIS_UMSK_ISR_GP1A_int32(data)                                                (0x00000004&((data)<<2))
#define MIS_UMSK_ISR_GP1A_int32_src(data)                                            ((0x00000004&(data))>>2)
#define MIS_UMSK_ISR_GP1A_get_int32(data)                                            ((0x00000004&(data))>>2)
#define MIS_UMSK_ISR_GP1A_int31_shift                                                (1)
#define MIS_UMSK_ISR_GP1A_int31_mask                                                 (0x00000002)
#define MIS_UMSK_ISR_GP1A_int31(data)                                                (0x00000002&((data)<<1))
#define MIS_UMSK_ISR_GP1A_int31_src(data)                                            ((0x00000002&(data))>>1)
#define MIS_UMSK_ISR_GP1A_get_int31(data)                                            ((0x00000002&(data))>>1)
#define MIS_UMSK_ISR_GP1A_write_data_shift                                           (0)
#define MIS_UMSK_ISR_GP1A_write_data_mask                                            (0x00000001)
#define MIS_UMSK_ISR_GP1A_write_data(data)                                           (0x00000001&((data)<<0))
#define MIS_UMSK_ISR_GP1A_write_data_src(data)                                       ((0x00000001&(data))>>0)
#define MIS_UMSK_ISR_GP1A_get_write_data(data)                                       ((0x00000001&(data))>>0)


#define MIS_UMSK_ISR_GP2A                                                            0x9801B0A4
#define MIS_UMSK_ISR_GP2A_reg_addr                                                   "0x9801B0A4"
#define MIS_UMSK_ISR_GP2A_reg                                                        0x9801B0A4
#define set_MIS_UMSK_ISR_GP2A_reg(data)   (*((volatile unsigned int*) MIS_UMSK_ISR_GP2A_reg)=data)
#define get_MIS_UMSK_ISR_GP2A_reg   (*((volatile unsigned int*) MIS_UMSK_ISR_GP2A_reg))
#define MIS_UMSK_ISR_GP2A_inst_adr                                                   "0x0029"
#define MIS_UMSK_ISR_GP2A_inst                                                       0x0029
#define MIS_UMSK_ISR_GP2A_int92_shift                                                (31)
#define MIS_UMSK_ISR_GP2A_int92_mask                                                 (0x80000000)
#define MIS_UMSK_ISR_GP2A_int92(data)                                                (0x80000000&((data)<<31))
#define MIS_UMSK_ISR_GP2A_int92_src(data)                                            ((0x80000000&(data))>>31)
#define MIS_UMSK_ISR_GP2A_get_int92(data)                                            ((0x80000000&(data))>>31)
#define MIS_UMSK_ISR_GP2A_int91_shift                                                (30)
#define MIS_UMSK_ISR_GP2A_int91_mask                                                 (0x40000000)
#define MIS_UMSK_ISR_GP2A_int91(data)                                                (0x40000000&((data)<<30))
#define MIS_UMSK_ISR_GP2A_int91_src(data)                                            ((0x40000000&(data))>>30)
#define MIS_UMSK_ISR_GP2A_get_int91(data)                                            ((0x40000000&(data))>>30)
#define MIS_UMSK_ISR_GP2A_int90_shift                                                (29)
#define MIS_UMSK_ISR_GP2A_int90_mask                                                 (0x20000000)
#define MIS_UMSK_ISR_GP2A_int90(data)                                                (0x20000000&((data)<<29))
#define MIS_UMSK_ISR_GP2A_int90_src(data)                                            ((0x20000000&(data))>>29)
#define MIS_UMSK_ISR_GP2A_get_int90(data)                                            ((0x20000000&(data))>>29)
#define MIS_UMSK_ISR_GP2A_int89_shift                                                (28)
#define MIS_UMSK_ISR_GP2A_int89_mask                                                 (0x10000000)
#define MIS_UMSK_ISR_GP2A_int89(data)                                                (0x10000000&((data)<<28))
#define MIS_UMSK_ISR_GP2A_int89_src(data)                                            ((0x10000000&(data))>>28)
#define MIS_UMSK_ISR_GP2A_get_int89(data)                                            ((0x10000000&(data))>>28)
#define MIS_UMSK_ISR_GP2A_int88_shift                                                (27)
#define MIS_UMSK_ISR_GP2A_int88_mask                                                 (0x08000000)
#define MIS_UMSK_ISR_GP2A_int88(data)                                                (0x08000000&((data)<<27))
#define MIS_UMSK_ISR_GP2A_int88_src(data)                                            ((0x08000000&(data))>>27)
#define MIS_UMSK_ISR_GP2A_get_int88(data)                                            ((0x08000000&(data))>>27)
#define MIS_UMSK_ISR_GP2A_int87_shift                                                (26)
#define MIS_UMSK_ISR_GP2A_int87_mask                                                 (0x04000000)
#define MIS_UMSK_ISR_GP2A_int87(data)                                                (0x04000000&((data)<<26))
#define MIS_UMSK_ISR_GP2A_int87_src(data)                                            ((0x04000000&(data))>>26)
#define MIS_UMSK_ISR_GP2A_get_int87(data)                                            ((0x04000000&(data))>>26)
#define MIS_UMSK_ISR_GP2A_int86_shift                                                (25)
#define MIS_UMSK_ISR_GP2A_int86_mask                                                 (0x02000000)
#define MIS_UMSK_ISR_GP2A_int86(data)                                                (0x02000000&((data)<<25))
#define MIS_UMSK_ISR_GP2A_int86_src(data)                                            ((0x02000000&(data))>>25)
#define MIS_UMSK_ISR_GP2A_get_int86(data)                                            ((0x02000000&(data))>>25)
#define MIS_UMSK_ISR_GP2A_int85_shift                                                (24)
#define MIS_UMSK_ISR_GP2A_int85_mask                                                 (0x01000000)
#define MIS_UMSK_ISR_GP2A_int85(data)                                                (0x01000000&((data)<<24))
#define MIS_UMSK_ISR_GP2A_int85_src(data)                                            ((0x01000000&(data))>>24)
#define MIS_UMSK_ISR_GP2A_get_int85(data)                                            ((0x01000000&(data))>>24)
#define MIS_UMSK_ISR_GP2A_int84_shift                                                (23)
#define MIS_UMSK_ISR_GP2A_int84_mask                                                 (0x00800000)
#define MIS_UMSK_ISR_GP2A_int84(data)                                                (0x00800000&((data)<<23))
#define MIS_UMSK_ISR_GP2A_int84_src(data)                                            ((0x00800000&(data))>>23)
#define MIS_UMSK_ISR_GP2A_get_int84(data)                                            ((0x00800000&(data))>>23)
#define MIS_UMSK_ISR_GP2A_int83_shift                                                (22)
#define MIS_UMSK_ISR_GP2A_int83_mask                                                 (0x00400000)
#define MIS_UMSK_ISR_GP2A_int83(data)                                                (0x00400000&((data)<<22))
#define MIS_UMSK_ISR_GP2A_int83_src(data)                                            ((0x00400000&(data))>>22)
#define MIS_UMSK_ISR_GP2A_get_int83(data)                                            ((0x00400000&(data))>>22)
#define MIS_UMSK_ISR_GP2A_int82_shift                                                (21)
#define MIS_UMSK_ISR_GP2A_int82_mask                                                 (0x00200000)
#define MIS_UMSK_ISR_GP2A_int82(data)                                                (0x00200000&((data)<<21))
#define MIS_UMSK_ISR_GP2A_int82_src(data)                                            ((0x00200000&(data))>>21)
#define MIS_UMSK_ISR_GP2A_get_int82(data)                                            ((0x00200000&(data))>>21)
#define MIS_UMSK_ISR_GP2A_int81_shift                                                (20)
#define MIS_UMSK_ISR_GP2A_int81_mask                                                 (0x00100000)
#define MIS_UMSK_ISR_GP2A_int81(data)                                                (0x00100000&((data)<<20))
#define MIS_UMSK_ISR_GP2A_int81_src(data)                                            ((0x00100000&(data))>>20)
#define MIS_UMSK_ISR_GP2A_get_int81(data)                                            ((0x00100000&(data))>>20)
#define MIS_UMSK_ISR_GP2A_int80_shift                                                (19)
#define MIS_UMSK_ISR_GP2A_int80_mask                                                 (0x00080000)
#define MIS_UMSK_ISR_GP2A_int80(data)                                                (0x00080000&((data)<<19))
#define MIS_UMSK_ISR_GP2A_int80_src(data)                                            ((0x00080000&(data))>>19)
#define MIS_UMSK_ISR_GP2A_get_int80(data)                                            ((0x00080000&(data))>>19)
#define MIS_UMSK_ISR_GP2A_int79_shift                                                (18)
#define MIS_UMSK_ISR_GP2A_int79_mask                                                 (0x00040000)
#define MIS_UMSK_ISR_GP2A_int79(data)                                                (0x00040000&((data)<<18))
#define MIS_UMSK_ISR_GP2A_int79_src(data)                                            ((0x00040000&(data))>>18)
#define MIS_UMSK_ISR_GP2A_get_int79(data)                                            ((0x00040000&(data))>>18)
#define MIS_UMSK_ISR_GP2A_int78_shift                                                (17)
#define MIS_UMSK_ISR_GP2A_int78_mask                                                 (0x00020000)
#define MIS_UMSK_ISR_GP2A_int78(data)                                                (0x00020000&((data)<<17))
#define MIS_UMSK_ISR_GP2A_int78_src(data)                                            ((0x00020000&(data))>>17)
#define MIS_UMSK_ISR_GP2A_get_int78(data)                                            ((0x00020000&(data))>>17)
#define MIS_UMSK_ISR_GP2A_int77_shift                                                (16)
#define MIS_UMSK_ISR_GP2A_int77_mask                                                 (0x00010000)
#define MIS_UMSK_ISR_GP2A_int77(data)                                                (0x00010000&((data)<<16))
#define MIS_UMSK_ISR_GP2A_int77_src(data)                                            ((0x00010000&(data))>>16)
#define MIS_UMSK_ISR_GP2A_get_int77(data)                                            ((0x00010000&(data))>>16)
#define MIS_UMSK_ISR_GP2A_int76_shift                                                (15)
#define MIS_UMSK_ISR_GP2A_int76_mask                                                 (0x00008000)
#define MIS_UMSK_ISR_GP2A_int76(data)                                                (0x00008000&((data)<<15))
#define MIS_UMSK_ISR_GP2A_int76_src(data)                                            ((0x00008000&(data))>>15)
#define MIS_UMSK_ISR_GP2A_get_int76(data)                                            ((0x00008000&(data))>>15)
#define MIS_UMSK_ISR_GP2A_int75_shift                                                (14)
#define MIS_UMSK_ISR_GP2A_int75_mask                                                 (0x00004000)
#define MIS_UMSK_ISR_GP2A_int75(data)                                                (0x00004000&((data)<<14))
#define MIS_UMSK_ISR_GP2A_int75_src(data)                                            ((0x00004000&(data))>>14)
#define MIS_UMSK_ISR_GP2A_get_int75(data)                                            ((0x00004000&(data))>>14)
#define MIS_UMSK_ISR_GP2A_int74_shift                                                (13)
#define MIS_UMSK_ISR_GP2A_int74_mask                                                 (0x00002000)
#define MIS_UMSK_ISR_GP2A_int74(data)                                                (0x00002000&((data)<<13))
#define MIS_UMSK_ISR_GP2A_int74_src(data)                                            ((0x00002000&(data))>>13)
#define MIS_UMSK_ISR_GP2A_get_int74(data)                                            ((0x00002000&(data))>>13)
#define MIS_UMSK_ISR_GP2A_int73_shift                                                (12)
#define MIS_UMSK_ISR_GP2A_int73_mask                                                 (0x00001000)
#define MIS_UMSK_ISR_GP2A_int73(data)                                                (0x00001000&((data)<<12))
#define MIS_UMSK_ISR_GP2A_int73_src(data)                                            ((0x00001000&(data))>>12)
#define MIS_UMSK_ISR_GP2A_get_int73(data)                                            ((0x00001000&(data))>>12)
#define MIS_UMSK_ISR_GP2A_int72_shift                                                (11)
#define MIS_UMSK_ISR_GP2A_int72_mask                                                 (0x00000800)
#define MIS_UMSK_ISR_GP2A_int72(data)                                                (0x00000800&((data)<<11))
#define MIS_UMSK_ISR_GP2A_int72_src(data)                                            ((0x00000800&(data))>>11)
#define MIS_UMSK_ISR_GP2A_get_int72(data)                                            ((0x00000800&(data))>>11)
#define MIS_UMSK_ISR_GP2A_int71_shift                                                (10)
#define MIS_UMSK_ISR_GP2A_int71_mask                                                 (0x00000400)
#define MIS_UMSK_ISR_GP2A_int71(data)                                                (0x00000400&((data)<<10))
#define MIS_UMSK_ISR_GP2A_int71_src(data)                                            ((0x00000400&(data))>>10)
#define MIS_UMSK_ISR_GP2A_get_int71(data)                                            ((0x00000400&(data))>>10)
#define MIS_UMSK_ISR_GP2A_int70_shift                                                (9)
#define MIS_UMSK_ISR_GP2A_int70_mask                                                 (0x00000200)
#define MIS_UMSK_ISR_GP2A_int70(data)                                                (0x00000200&((data)<<9))
#define MIS_UMSK_ISR_GP2A_int70_src(data)                                            ((0x00000200&(data))>>9)
#define MIS_UMSK_ISR_GP2A_get_int70(data)                                            ((0x00000200&(data))>>9)
#define MIS_UMSK_ISR_GP2A_int69_shift                                                (8)
#define MIS_UMSK_ISR_GP2A_int69_mask                                                 (0x00000100)
#define MIS_UMSK_ISR_GP2A_int69(data)                                                (0x00000100&((data)<<8))
#define MIS_UMSK_ISR_GP2A_int69_src(data)                                            ((0x00000100&(data))>>8)
#define MIS_UMSK_ISR_GP2A_get_int69(data)                                            ((0x00000100&(data))>>8)
#define MIS_UMSK_ISR_GP2A_int68_shift                                                (7)
#define MIS_UMSK_ISR_GP2A_int68_mask                                                 (0x00000080)
#define MIS_UMSK_ISR_GP2A_int68(data)                                                (0x00000080&((data)<<7))
#define MIS_UMSK_ISR_GP2A_int68_src(data)                                            ((0x00000080&(data))>>7)
#define MIS_UMSK_ISR_GP2A_get_int68(data)                                            ((0x00000080&(data))>>7)
#define MIS_UMSK_ISR_GP2A_int67_shift                                                (6)
#define MIS_UMSK_ISR_GP2A_int67_mask                                                 (0x00000040)
#define MIS_UMSK_ISR_GP2A_int67(data)                                                (0x00000040&((data)<<6))
#define MIS_UMSK_ISR_GP2A_int67_src(data)                                            ((0x00000040&(data))>>6)
#define MIS_UMSK_ISR_GP2A_get_int67(data)                                            ((0x00000040&(data))>>6)
#define MIS_UMSK_ISR_GP2A_int66_shift                                                (5)
#define MIS_UMSK_ISR_GP2A_int66_mask                                                 (0x00000020)
#define MIS_UMSK_ISR_GP2A_int66(data)                                                (0x00000020&((data)<<5))
#define MIS_UMSK_ISR_GP2A_int66_src(data)                                            ((0x00000020&(data))>>5)
#define MIS_UMSK_ISR_GP2A_get_int66(data)                                            ((0x00000020&(data))>>5)
#define MIS_UMSK_ISR_GP2A_int65_shift                                                (4)
#define MIS_UMSK_ISR_GP2A_int65_mask                                                 (0x00000010)
#define MIS_UMSK_ISR_GP2A_int65(data)                                                (0x00000010&((data)<<4))
#define MIS_UMSK_ISR_GP2A_int65_src(data)                                            ((0x00000010&(data))>>4)
#define MIS_UMSK_ISR_GP2A_get_int65(data)                                            ((0x00000010&(data))>>4)
#define MIS_UMSK_ISR_GP2A_int64_shift                                                (3)
#define MIS_UMSK_ISR_GP2A_int64_mask                                                 (0x00000008)
#define MIS_UMSK_ISR_GP2A_int64(data)                                                (0x00000008&((data)<<3))
#define MIS_UMSK_ISR_GP2A_int64_src(data)                                            ((0x00000008&(data))>>3)
#define MIS_UMSK_ISR_GP2A_get_int64(data)                                            ((0x00000008&(data))>>3)
#define MIS_UMSK_ISR_GP2A_int63_shift                                                (2)
#define MIS_UMSK_ISR_GP2A_int63_mask                                                 (0x00000004)
#define MIS_UMSK_ISR_GP2A_int63(data)                                                (0x00000004&((data)<<2))
#define MIS_UMSK_ISR_GP2A_int63_src(data)                                            ((0x00000004&(data))>>2)
#define MIS_UMSK_ISR_GP2A_get_int63(data)                                            ((0x00000004&(data))>>2)
#define MIS_UMSK_ISR_GP2A_int62_shift                                                (1)
#define MIS_UMSK_ISR_GP2A_int62_mask                                                 (0x00000002)
#define MIS_UMSK_ISR_GP2A_int62(data)                                                (0x00000002&((data)<<1))
#define MIS_UMSK_ISR_GP2A_int62_src(data)                                            ((0x00000002&(data))>>1)
#define MIS_UMSK_ISR_GP2A_get_int62(data)                                            ((0x00000002&(data))>>1)
#define MIS_UMSK_ISR_GP2A_write_data_shift                                           (0)
#define MIS_UMSK_ISR_GP2A_write_data_mask                                            (0x00000001)
#define MIS_UMSK_ISR_GP2A_write_data(data)                                           (0x00000001&((data)<<0))
#define MIS_UMSK_ISR_GP2A_write_data_src(data)                                       ((0x00000001&(data))>>0)
#define MIS_UMSK_ISR_GP2A_get_write_data(data)                                       ((0x00000001&(data))>>0)


#define MIS_UMSK_ISR_GP3A                                                            0x9801B0B8
#define MIS_UMSK_ISR_GP3A_reg_addr                                                   "0x9801B0B8"
#define MIS_UMSK_ISR_GP3A_reg                                                        0x9801B0B8
#define set_MIS_UMSK_ISR_GP3A_reg(data)   (*((volatile unsigned int*) MIS_UMSK_ISR_GP3A_reg)=data)
#define get_MIS_UMSK_ISR_GP3A_reg   (*((volatile unsigned int*) MIS_UMSK_ISR_GP3A_reg))
#define MIS_UMSK_ISR_GP3A_inst_adr                                                   "0x002E"
#define MIS_UMSK_ISR_GP3A_inst                                                       0x002E
#define MIS_UMSK_ISR_GP3A_int100_shift                                               (8)
#define MIS_UMSK_ISR_GP3A_int100_mask                                                (0x00000100)
#define MIS_UMSK_ISR_GP3A_int100(data)                                               (0x00000100&((data)<<8))
#define MIS_UMSK_ISR_GP3A_int100_src(data)                                           ((0x00000100&(data))>>8)
#define MIS_UMSK_ISR_GP3A_get_int100(data)                                           ((0x00000100&(data))>>8)
#define MIS_UMSK_ISR_GP3A_int99_shift                                                (7)
#define MIS_UMSK_ISR_GP3A_int99_mask                                                 (0x00000080)
#define MIS_UMSK_ISR_GP3A_int99(data)                                                (0x00000080&((data)<<7))
#define MIS_UMSK_ISR_GP3A_int99_src(data)                                            ((0x00000080&(data))>>7)
#define MIS_UMSK_ISR_GP3A_get_int99(data)                                            ((0x00000080&(data))>>7)
#define MIS_UMSK_ISR_GP3A_int98_shift                                                (6)
#define MIS_UMSK_ISR_GP3A_int98_mask                                                 (0x00000040)
#define MIS_UMSK_ISR_GP3A_int98(data)                                                (0x00000040&((data)<<6))
#define MIS_UMSK_ISR_GP3A_int98_src(data)                                            ((0x00000040&(data))>>6)
#define MIS_UMSK_ISR_GP3A_get_int98(data)                                            ((0x00000040&(data))>>6)
#define MIS_UMSK_ISR_GP3A_int97_shift                                                (5)
#define MIS_UMSK_ISR_GP3A_int97_mask                                                 (0x00000020)
#define MIS_UMSK_ISR_GP3A_int97(data)                                                (0x00000020&((data)<<5))
#define MIS_UMSK_ISR_GP3A_int97_src(data)                                            ((0x00000020&(data))>>5)
#define MIS_UMSK_ISR_GP3A_get_int97(data)                                            ((0x00000020&(data))>>5)
#define MIS_UMSK_ISR_GP3A_int96_shift                                                (4)
#define MIS_UMSK_ISR_GP3A_int96_mask                                                 (0x00000010)
#define MIS_UMSK_ISR_GP3A_int96(data)                                                (0x00000010&((data)<<4))
#define MIS_UMSK_ISR_GP3A_int96_src(data)                                            ((0x00000010&(data))>>4)
#define MIS_UMSK_ISR_GP3A_get_int96(data)                                            ((0x00000010&(data))>>4)
#define MIS_UMSK_ISR_GP3A_int95_shift                                                (3)
#define MIS_UMSK_ISR_GP3A_int95_mask                                                 (0x00000008)
#define MIS_UMSK_ISR_GP3A_int95(data)                                                (0x00000008&((data)<<3))
#define MIS_UMSK_ISR_GP3A_int95_src(data)                                            ((0x00000008&(data))>>3)
#define MIS_UMSK_ISR_GP3A_get_int95(data)                                            ((0x00000008&(data))>>3)
#define MIS_UMSK_ISR_GP3A_int94_shift                                                (2)
#define MIS_UMSK_ISR_GP3A_int94_mask                                                 (0x00000004)
#define MIS_UMSK_ISR_GP3A_int94(data)                                                (0x00000004&((data)<<2))
#define MIS_UMSK_ISR_GP3A_int94_src(data)                                            ((0x00000004&(data))>>2)
#define MIS_UMSK_ISR_GP3A_get_int94(data)                                            ((0x00000004&(data))>>2)
#define MIS_UMSK_ISR_GP3A_int93_shift                                                (1)
#define MIS_UMSK_ISR_GP3A_int93_mask                                                 (0x00000002)
#define MIS_UMSK_ISR_GP3A_int93(data)                                                (0x00000002&((data)<<1))
#define MIS_UMSK_ISR_GP3A_int93_src(data)                                            ((0x00000002&(data))>>1)
#define MIS_UMSK_ISR_GP3A_get_int93(data)                                            ((0x00000002&(data))>>1)
#define MIS_UMSK_ISR_GP3A_write_data_shift                                           (0)
#define MIS_UMSK_ISR_GP3A_write_data_mask                                            (0x00000001)
#define MIS_UMSK_ISR_GP3A_write_data(data)                                           (0x00000001&((data)<<0))
#define MIS_UMSK_ISR_GP3A_write_data_src(data)                                       ((0x00000001&(data))>>0)
#define MIS_UMSK_ISR_GP3A_get_write_data(data)                                       ((0x00000001&(data))>>0)


#define MIS_UMSK_ISR_GP0DA                                                           0x9801B054
#define MIS_UMSK_ISR_GP0DA_reg_addr                                                  "0x9801B054"
#define MIS_UMSK_ISR_GP0DA_reg                                                       0x9801B054
#define set_MIS_UMSK_ISR_GP0DA_reg(data)   (*((volatile unsigned int*) MIS_UMSK_ISR_GP0DA_reg)=data)
#define get_MIS_UMSK_ISR_GP0DA_reg   (*((volatile unsigned int*) MIS_UMSK_ISR_GP0DA_reg))
#define MIS_UMSK_ISR_GP0DA_inst_adr                                                  "0x0015"
#define MIS_UMSK_ISR_GP0DA_inst                                                      0x0015
#define MIS_UMSK_ISR_GP0DA_int30_shift                                               (31)
#define MIS_UMSK_ISR_GP0DA_int30_mask                                                (0x80000000)
#define MIS_UMSK_ISR_GP0DA_int30(data)                                               (0x80000000&((data)<<31))
#define MIS_UMSK_ISR_GP0DA_int30_src(data)                                           ((0x80000000&(data))>>31)
#define MIS_UMSK_ISR_GP0DA_get_int30(data)                                           ((0x80000000&(data))>>31)
#define MIS_UMSK_ISR_GP0DA_int29_shift                                               (30)
#define MIS_UMSK_ISR_GP0DA_int29_mask                                                (0x40000000)
#define MIS_UMSK_ISR_GP0DA_int29(data)                                               (0x40000000&((data)<<30))
#define MIS_UMSK_ISR_GP0DA_int29_src(data)                                           ((0x40000000&(data))>>30)
#define MIS_UMSK_ISR_GP0DA_get_int29(data)                                           ((0x40000000&(data))>>30)
#define MIS_UMSK_ISR_GP0DA_int28_shift                                               (29)
#define MIS_UMSK_ISR_GP0DA_int28_mask                                                (0x20000000)
#define MIS_UMSK_ISR_GP0DA_int28(data)                                               (0x20000000&((data)<<29))
#define MIS_UMSK_ISR_GP0DA_int28_src(data)                                           ((0x20000000&(data))>>29)
#define MIS_UMSK_ISR_GP0DA_get_int28(data)                                           ((0x20000000&(data))>>29)
#define MIS_UMSK_ISR_GP0DA_int27_shift                                               (28)
#define MIS_UMSK_ISR_GP0DA_int27_mask                                                (0x10000000)
#define MIS_UMSK_ISR_GP0DA_int27(data)                                               (0x10000000&((data)<<28))
#define MIS_UMSK_ISR_GP0DA_int27_src(data)                                           ((0x10000000&(data))>>28)
#define MIS_UMSK_ISR_GP0DA_get_int27(data)                                           ((0x10000000&(data))>>28)
#define MIS_UMSK_ISR_GP0DA_int26_shift                                               (27)
#define MIS_UMSK_ISR_GP0DA_int26_mask                                                (0x08000000)
#define MIS_UMSK_ISR_GP0DA_int26(data)                                               (0x08000000&((data)<<27))
#define MIS_UMSK_ISR_GP0DA_int26_src(data)                                           ((0x08000000&(data))>>27)
#define MIS_UMSK_ISR_GP0DA_get_int26(data)                                           ((0x08000000&(data))>>27)
#define MIS_UMSK_ISR_GP0DA_int25_shift                                               (26)
#define MIS_UMSK_ISR_GP0DA_int25_mask                                                (0x04000000)
#define MIS_UMSK_ISR_GP0DA_int25(data)                                               (0x04000000&((data)<<26))
#define MIS_UMSK_ISR_GP0DA_int25_src(data)                                           ((0x04000000&(data))>>26)
#define MIS_UMSK_ISR_GP0DA_get_int25(data)                                           ((0x04000000&(data))>>26)
#define MIS_UMSK_ISR_GP0DA_int24_shift                                               (25)
#define MIS_UMSK_ISR_GP0DA_int24_mask                                                (0x02000000)
#define MIS_UMSK_ISR_GP0DA_int24(data)                                               (0x02000000&((data)<<25))
#define MIS_UMSK_ISR_GP0DA_int24_src(data)                                           ((0x02000000&(data))>>25)
#define MIS_UMSK_ISR_GP0DA_get_int24(data)                                           ((0x02000000&(data))>>25)
#define MIS_UMSK_ISR_GP0DA_int23_shift                                               (24)
#define MIS_UMSK_ISR_GP0DA_int23_mask                                                (0x01000000)
#define MIS_UMSK_ISR_GP0DA_int23(data)                                               (0x01000000&((data)<<24))
#define MIS_UMSK_ISR_GP0DA_int23_src(data)                                           ((0x01000000&(data))>>24)
#define MIS_UMSK_ISR_GP0DA_get_int23(data)                                           ((0x01000000&(data))>>24)
#define MIS_UMSK_ISR_GP0DA_int22_shift                                               (23)
#define MIS_UMSK_ISR_GP0DA_int22_mask                                                (0x00800000)
#define MIS_UMSK_ISR_GP0DA_int22(data)                                               (0x00800000&((data)<<23))
#define MIS_UMSK_ISR_GP0DA_int22_src(data)                                           ((0x00800000&(data))>>23)
#define MIS_UMSK_ISR_GP0DA_get_int22(data)                                           ((0x00800000&(data))>>23)
#define MIS_UMSK_ISR_GP0DA_int21_shift                                               (22)
#define MIS_UMSK_ISR_GP0DA_int21_mask                                                (0x00400000)
#define MIS_UMSK_ISR_GP0DA_int21(data)                                               (0x00400000&((data)<<22))
#define MIS_UMSK_ISR_GP0DA_int21_src(data)                                           ((0x00400000&(data))>>22)
#define MIS_UMSK_ISR_GP0DA_get_int21(data)                                           ((0x00400000&(data))>>22)
#define MIS_UMSK_ISR_GP0DA_int20_shift                                               (21)
#define MIS_UMSK_ISR_GP0DA_int20_mask                                                (0x00200000)
#define MIS_UMSK_ISR_GP0DA_int20(data)                                               (0x00200000&((data)<<21))
#define MIS_UMSK_ISR_GP0DA_int20_src(data)                                           ((0x00200000&(data))>>21)
#define MIS_UMSK_ISR_GP0DA_get_int20(data)                                           ((0x00200000&(data))>>21)
#define MIS_UMSK_ISR_GP0DA_int19_shift                                               (20)
#define MIS_UMSK_ISR_GP0DA_int19_mask                                                (0x00100000)
#define MIS_UMSK_ISR_GP0DA_int19(data)                                               (0x00100000&((data)<<20))
#define MIS_UMSK_ISR_GP0DA_int19_src(data)                                           ((0x00100000&(data))>>20)
#define MIS_UMSK_ISR_GP0DA_get_int19(data)                                           ((0x00100000&(data))>>20)
#define MIS_UMSK_ISR_GP0DA_int18_shift                                               (19)
#define MIS_UMSK_ISR_GP0DA_int18_mask                                                (0x00080000)
#define MIS_UMSK_ISR_GP0DA_int18(data)                                               (0x00080000&((data)<<19))
#define MIS_UMSK_ISR_GP0DA_int18_src(data)                                           ((0x00080000&(data))>>19)
#define MIS_UMSK_ISR_GP0DA_get_int18(data)                                           ((0x00080000&(data))>>19)
#define MIS_UMSK_ISR_GP0DA_int17_shift                                               (18)
#define MIS_UMSK_ISR_GP0DA_int17_mask                                                (0x00040000)
#define MIS_UMSK_ISR_GP0DA_int17(data)                                               (0x00040000&((data)<<18))
#define MIS_UMSK_ISR_GP0DA_int17_src(data)                                           ((0x00040000&(data))>>18)
#define MIS_UMSK_ISR_GP0DA_get_int17(data)                                           ((0x00040000&(data))>>18)
#define MIS_UMSK_ISR_GP0DA_int16_shift                                               (17)
#define MIS_UMSK_ISR_GP0DA_int16_mask                                                (0x00020000)
#define MIS_UMSK_ISR_GP0DA_int16(data)                                               (0x00020000&((data)<<17))
#define MIS_UMSK_ISR_GP0DA_int16_src(data)                                           ((0x00020000&(data))>>17)
#define MIS_UMSK_ISR_GP0DA_get_int16(data)                                           ((0x00020000&(data))>>17)
#define MIS_UMSK_ISR_GP0DA_int15_shift                                               (16)
#define MIS_UMSK_ISR_GP0DA_int15_mask                                                (0x00010000)
#define MIS_UMSK_ISR_GP0DA_int15(data)                                               (0x00010000&((data)<<16))
#define MIS_UMSK_ISR_GP0DA_int15_src(data)                                           ((0x00010000&(data))>>16)
#define MIS_UMSK_ISR_GP0DA_get_int15(data)                                           ((0x00010000&(data))>>16)
#define MIS_UMSK_ISR_GP0DA_int14_shift                                               (15)
#define MIS_UMSK_ISR_GP0DA_int14_mask                                                (0x00008000)
#define MIS_UMSK_ISR_GP0DA_int14(data)                                               (0x00008000&((data)<<15))
#define MIS_UMSK_ISR_GP0DA_int14_src(data)                                           ((0x00008000&(data))>>15)
#define MIS_UMSK_ISR_GP0DA_get_int14(data)                                           ((0x00008000&(data))>>15)
#define MIS_UMSK_ISR_GP0DA_int13_shift                                               (14)
#define MIS_UMSK_ISR_GP0DA_int13_mask                                                (0x00004000)
#define MIS_UMSK_ISR_GP0DA_int13(data)                                               (0x00004000&((data)<<14))
#define MIS_UMSK_ISR_GP0DA_int13_src(data)                                           ((0x00004000&(data))>>14)
#define MIS_UMSK_ISR_GP0DA_get_int13(data)                                           ((0x00004000&(data))>>14)
#define MIS_UMSK_ISR_GP0DA_int12_shift                                               (13)
#define MIS_UMSK_ISR_GP0DA_int12_mask                                                (0x00002000)
#define MIS_UMSK_ISR_GP0DA_int12(data)                                               (0x00002000&((data)<<13))
#define MIS_UMSK_ISR_GP0DA_int12_src(data)                                           ((0x00002000&(data))>>13)
#define MIS_UMSK_ISR_GP0DA_get_int12(data)                                           ((0x00002000&(data))>>13)
#define MIS_UMSK_ISR_GP0DA_int11_shift                                               (12)
#define MIS_UMSK_ISR_GP0DA_int11_mask                                                (0x00001000)
#define MIS_UMSK_ISR_GP0DA_int11(data)                                               (0x00001000&((data)<<12))
#define MIS_UMSK_ISR_GP0DA_int11_src(data)                                           ((0x00001000&(data))>>12)
#define MIS_UMSK_ISR_GP0DA_get_int11(data)                                           ((0x00001000&(data))>>12)
#define MIS_UMSK_ISR_GP0DA_int10_shift                                               (11)
#define MIS_UMSK_ISR_GP0DA_int10_mask                                                (0x00000800)
#define MIS_UMSK_ISR_GP0DA_int10(data)                                               (0x00000800&((data)<<11))
#define MIS_UMSK_ISR_GP0DA_int10_src(data)                                           ((0x00000800&(data))>>11)
#define MIS_UMSK_ISR_GP0DA_get_int10(data)                                           ((0x00000800&(data))>>11)
#define MIS_UMSK_ISR_GP0DA_int9_shift                                                (10)
#define MIS_UMSK_ISR_GP0DA_int9_mask                                                 (0x00000400)
#define MIS_UMSK_ISR_GP0DA_int9(data)                                                (0x00000400&((data)<<10))
#define MIS_UMSK_ISR_GP0DA_int9_src(data)                                            ((0x00000400&(data))>>10)
#define MIS_UMSK_ISR_GP0DA_get_int9(data)                                            ((0x00000400&(data))>>10)
#define MIS_UMSK_ISR_GP0DA_int8_shift                                                (9)
#define MIS_UMSK_ISR_GP0DA_int8_mask                                                 (0x00000200)
#define MIS_UMSK_ISR_GP0DA_int8(data)                                                (0x00000200&((data)<<9))
#define MIS_UMSK_ISR_GP0DA_int8_src(data)                                            ((0x00000200&(data))>>9)
#define MIS_UMSK_ISR_GP0DA_get_int8(data)                                            ((0x00000200&(data))>>9)
#define MIS_UMSK_ISR_GP0DA_int7_shift                                                (8)
#define MIS_UMSK_ISR_GP0DA_int7_mask                                                 (0x00000100)
#define MIS_UMSK_ISR_GP0DA_int7(data)                                                (0x00000100&((data)<<8))
#define MIS_UMSK_ISR_GP0DA_int7_src(data)                                            ((0x00000100&(data))>>8)
#define MIS_UMSK_ISR_GP0DA_get_int7(data)                                            ((0x00000100&(data))>>8)
#define MIS_UMSK_ISR_GP0DA_int6_shift                                                (7)
#define MIS_UMSK_ISR_GP0DA_int6_mask                                                 (0x00000080)
#define MIS_UMSK_ISR_GP0DA_int6(data)                                                (0x00000080&((data)<<7))
#define MIS_UMSK_ISR_GP0DA_int6_src(data)                                            ((0x00000080&(data))>>7)
#define MIS_UMSK_ISR_GP0DA_get_int6(data)                                            ((0x00000080&(data))>>7)
#define MIS_UMSK_ISR_GP0DA_int5_shift                                                (6)
#define MIS_UMSK_ISR_GP0DA_int5_mask                                                 (0x00000040)
#define MIS_UMSK_ISR_GP0DA_int5(data)                                                (0x00000040&((data)<<6))
#define MIS_UMSK_ISR_GP0DA_int5_src(data)                                            ((0x00000040&(data))>>6)
#define MIS_UMSK_ISR_GP0DA_get_int5(data)                                            ((0x00000040&(data))>>6)
#define MIS_UMSK_ISR_GP0DA_int4_shift                                                (5)
#define MIS_UMSK_ISR_GP0DA_int4_mask                                                 (0x00000020)
#define MIS_UMSK_ISR_GP0DA_int4(data)                                                (0x00000020&((data)<<5))
#define MIS_UMSK_ISR_GP0DA_int4_src(data)                                            ((0x00000020&(data))>>5)
#define MIS_UMSK_ISR_GP0DA_get_int4(data)                                            ((0x00000020&(data))>>5)
#define MIS_UMSK_ISR_GP0DA_int3_shift                                                (4)
#define MIS_UMSK_ISR_GP0DA_int3_mask                                                 (0x00000010)
#define MIS_UMSK_ISR_GP0DA_int3(data)                                                (0x00000010&((data)<<4))
#define MIS_UMSK_ISR_GP0DA_int3_src(data)                                            ((0x00000010&(data))>>4)
#define MIS_UMSK_ISR_GP0DA_get_int3(data)                                            ((0x00000010&(data))>>4)
#define MIS_UMSK_ISR_GP0DA_int2_shift                                                (3)
#define MIS_UMSK_ISR_GP0DA_int2_mask                                                 (0x00000008)
#define MIS_UMSK_ISR_GP0DA_int2(data)                                                (0x00000008&((data)<<3))
#define MIS_UMSK_ISR_GP0DA_int2_src(data)                                            ((0x00000008&(data))>>3)
#define MIS_UMSK_ISR_GP0DA_get_int2(data)                                            ((0x00000008&(data))>>3)
#define MIS_UMSK_ISR_GP0DA_int1_shift                                                (2)
#define MIS_UMSK_ISR_GP0DA_int1_mask                                                 (0x00000004)
#define MIS_UMSK_ISR_GP0DA_int1(data)                                                (0x00000004&((data)<<2))
#define MIS_UMSK_ISR_GP0DA_int1_src(data)                                            ((0x00000004&(data))>>2)
#define MIS_UMSK_ISR_GP0DA_get_int1(data)                                            ((0x00000004&(data))>>2)
#define MIS_UMSK_ISR_GP0DA_int0_shift                                                (1)
#define MIS_UMSK_ISR_GP0DA_int0_mask                                                 (0x00000002)
#define MIS_UMSK_ISR_GP0DA_int0(data)                                                (0x00000002&((data)<<1))
#define MIS_UMSK_ISR_GP0DA_int0_src(data)                                            ((0x00000002&(data))>>1)
#define MIS_UMSK_ISR_GP0DA_get_int0(data)                                            ((0x00000002&(data))>>1)
#define MIS_UMSK_ISR_GP0DA_write_data_shift                                          (0)
#define MIS_UMSK_ISR_GP0DA_write_data_mask                                           (0x00000001)
#define MIS_UMSK_ISR_GP0DA_write_data(data)                                          (0x00000001&((data)<<0))
#define MIS_UMSK_ISR_GP0DA_write_data_src(data)                                      ((0x00000001&(data))>>0)
#define MIS_UMSK_ISR_GP0DA_get_write_data(data)                                      ((0x00000001&(data))>>0)


#define MIS_UMSK_ISR_GP1DA                                                           0x9801B058
#define MIS_UMSK_ISR_GP1DA_reg_addr                                                  "0x9801B058"
#define MIS_UMSK_ISR_GP1DA_reg                                                       0x9801B058
#define set_MIS_UMSK_ISR_GP1DA_reg(data)   (*((volatile unsigned int*) MIS_UMSK_ISR_GP1DA_reg)=data)
#define get_MIS_UMSK_ISR_GP1DA_reg   (*((volatile unsigned int*) MIS_UMSK_ISR_GP1DA_reg))
#define MIS_UMSK_ISR_GP1DA_inst_adr                                                  "0x0016"
#define MIS_UMSK_ISR_GP1DA_inst                                                      0x0016
#define MIS_UMSK_ISR_GP1DA_int61_shift                                               (31)
#define MIS_UMSK_ISR_GP1DA_int61_mask                                                (0x80000000)
#define MIS_UMSK_ISR_GP1DA_int61(data)                                               (0x80000000&((data)<<31))
#define MIS_UMSK_ISR_GP1DA_int61_src(data)                                           ((0x80000000&(data))>>31)
#define MIS_UMSK_ISR_GP1DA_get_int61(data)                                           ((0x80000000&(data))>>31)
#define MIS_UMSK_ISR_GP1DA_int60_shift                                               (30)
#define MIS_UMSK_ISR_GP1DA_int60_mask                                                (0x40000000)
#define MIS_UMSK_ISR_GP1DA_int60(data)                                               (0x40000000&((data)<<30))
#define MIS_UMSK_ISR_GP1DA_int60_src(data)                                           ((0x40000000&(data))>>30)
#define MIS_UMSK_ISR_GP1DA_get_int60(data)                                           ((0x40000000&(data))>>30)
#define MIS_UMSK_ISR_GP1DA_int59_shift                                               (29)
#define MIS_UMSK_ISR_GP1DA_int59_mask                                                (0x20000000)
#define MIS_UMSK_ISR_GP1DA_int59(data)                                               (0x20000000&((data)<<29))
#define MIS_UMSK_ISR_GP1DA_int59_src(data)                                           ((0x20000000&(data))>>29)
#define MIS_UMSK_ISR_GP1DA_get_int59(data)                                           ((0x20000000&(data))>>29)
#define MIS_UMSK_ISR_GP1DA_int58_shift                                               (28)
#define MIS_UMSK_ISR_GP1DA_int58_mask                                                (0x10000000)
#define MIS_UMSK_ISR_GP1DA_int58(data)                                               (0x10000000&((data)<<28))
#define MIS_UMSK_ISR_GP1DA_int58_src(data)                                           ((0x10000000&(data))>>28)
#define MIS_UMSK_ISR_GP1DA_get_int58(data)                                           ((0x10000000&(data))>>28)
#define MIS_UMSK_ISR_GP1DA_int57_shift                                               (27)
#define MIS_UMSK_ISR_GP1DA_int57_mask                                                (0x08000000)
#define MIS_UMSK_ISR_GP1DA_int57(data)                                               (0x08000000&((data)<<27))
#define MIS_UMSK_ISR_GP1DA_int57_src(data)                                           ((0x08000000&(data))>>27)
#define MIS_UMSK_ISR_GP1DA_get_int57(data)                                           ((0x08000000&(data))>>27)
#define MIS_UMSK_ISR_GP1DA_int56_shift                                               (26)
#define MIS_UMSK_ISR_GP1DA_int56_mask                                                (0x04000000)
#define MIS_UMSK_ISR_GP1DA_int56(data)                                               (0x04000000&((data)<<26))
#define MIS_UMSK_ISR_GP1DA_int56_src(data)                                           ((0x04000000&(data))>>26)
#define MIS_UMSK_ISR_GP1DA_get_int56(data)                                           ((0x04000000&(data))>>26)
#define MIS_UMSK_ISR_GP1DA_int55_shift                                               (25)
#define MIS_UMSK_ISR_GP1DA_int55_mask                                                (0x02000000)
#define MIS_UMSK_ISR_GP1DA_int55(data)                                               (0x02000000&((data)<<25))
#define MIS_UMSK_ISR_GP1DA_int55_src(data)                                           ((0x02000000&(data))>>25)
#define MIS_UMSK_ISR_GP1DA_get_int55(data)                                           ((0x02000000&(data))>>25)
#define MIS_UMSK_ISR_GP1DA_int54_shift                                               (24)
#define MIS_UMSK_ISR_GP1DA_int54_mask                                                (0x01000000)
#define MIS_UMSK_ISR_GP1DA_int54(data)                                               (0x01000000&((data)<<24))
#define MIS_UMSK_ISR_GP1DA_int54_src(data)                                           ((0x01000000&(data))>>24)
#define MIS_UMSK_ISR_GP1DA_get_int54(data)                                           ((0x01000000&(data))>>24)
#define MIS_UMSK_ISR_GP1DA_int53_shift                                               (23)
#define MIS_UMSK_ISR_GP1DA_int53_mask                                                (0x00800000)
#define MIS_UMSK_ISR_GP1DA_int53(data)                                               (0x00800000&((data)<<23))
#define MIS_UMSK_ISR_GP1DA_int53_src(data)                                           ((0x00800000&(data))>>23)
#define MIS_UMSK_ISR_GP1DA_get_int53(data)                                           ((0x00800000&(data))>>23)
#define MIS_UMSK_ISR_GP1DA_int52_shift                                               (22)
#define MIS_UMSK_ISR_GP1DA_int52_mask                                                (0x00400000)
#define MIS_UMSK_ISR_GP1DA_int52(data)                                               (0x00400000&((data)<<22))
#define MIS_UMSK_ISR_GP1DA_int52_src(data)                                           ((0x00400000&(data))>>22)
#define MIS_UMSK_ISR_GP1DA_get_int52(data)                                           ((0x00400000&(data))>>22)
#define MIS_UMSK_ISR_GP1DA_int51_shift                                               (21)
#define MIS_UMSK_ISR_GP1DA_int51_mask                                                (0x00200000)
#define MIS_UMSK_ISR_GP1DA_int51(data)                                               (0x00200000&((data)<<21))
#define MIS_UMSK_ISR_GP1DA_int51_src(data)                                           ((0x00200000&(data))>>21)
#define MIS_UMSK_ISR_GP1DA_get_int51(data)                                           ((0x00200000&(data))>>21)
#define MIS_UMSK_ISR_GP1DA_int50_shift                                               (20)
#define MIS_UMSK_ISR_GP1DA_int50_mask                                                (0x00100000)
#define MIS_UMSK_ISR_GP1DA_int50(data)                                               (0x00100000&((data)<<20))
#define MIS_UMSK_ISR_GP1DA_int50_src(data)                                           ((0x00100000&(data))>>20)
#define MIS_UMSK_ISR_GP1DA_get_int50(data)                                           ((0x00100000&(data))>>20)
#define MIS_UMSK_ISR_GP1DA_int49_shift                                               (19)
#define MIS_UMSK_ISR_GP1DA_int49_mask                                                (0x00080000)
#define MIS_UMSK_ISR_GP1DA_int49(data)                                               (0x00080000&((data)<<19))
#define MIS_UMSK_ISR_GP1DA_int49_src(data)                                           ((0x00080000&(data))>>19)
#define MIS_UMSK_ISR_GP1DA_get_int49(data)                                           ((0x00080000&(data))>>19)
#define MIS_UMSK_ISR_GP1DA_int48_shift                                               (18)
#define MIS_UMSK_ISR_GP1DA_int48_mask                                                (0x00040000)
#define MIS_UMSK_ISR_GP1DA_int48(data)                                               (0x00040000&((data)<<18))
#define MIS_UMSK_ISR_GP1DA_int48_src(data)                                           ((0x00040000&(data))>>18)
#define MIS_UMSK_ISR_GP1DA_get_int48(data)                                           ((0x00040000&(data))>>18)
#define MIS_UMSK_ISR_GP1DA_int47_shift                                               (17)
#define MIS_UMSK_ISR_GP1DA_int47_mask                                                (0x00020000)
#define MIS_UMSK_ISR_GP1DA_int47(data)                                               (0x00020000&((data)<<17))
#define MIS_UMSK_ISR_GP1DA_int47_src(data)                                           ((0x00020000&(data))>>17)
#define MIS_UMSK_ISR_GP1DA_get_int47(data)                                           ((0x00020000&(data))>>17)
#define MIS_UMSK_ISR_GP1DA_int46_shift                                               (16)
#define MIS_UMSK_ISR_GP1DA_int46_mask                                                (0x00010000)
#define MIS_UMSK_ISR_GP1DA_int46(data)                                               (0x00010000&((data)<<16))
#define MIS_UMSK_ISR_GP1DA_int46_src(data)                                           ((0x00010000&(data))>>16)
#define MIS_UMSK_ISR_GP1DA_get_int46(data)                                           ((0x00010000&(data))>>16)
#define MIS_UMSK_ISR_GP1DA_int45_shift                                               (15)
#define MIS_UMSK_ISR_GP1DA_int45_mask                                                (0x00008000)
#define MIS_UMSK_ISR_GP1DA_int45(data)                                               (0x00008000&((data)<<15))
#define MIS_UMSK_ISR_GP1DA_int45_src(data)                                           ((0x00008000&(data))>>15)
#define MIS_UMSK_ISR_GP1DA_get_int45(data)                                           ((0x00008000&(data))>>15)
#define MIS_UMSK_ISR_GP1DA_int44_shift                                               (14)
#define MIS_UMSK_ISR_GP1DA_int44_mask                                                (0x00004000)
#define MIS_UMSK_ISR_GP1DA_int44(data)                                               (0x00004000&((data)<<14))
#define MIS_UMSK_ISR_GP1DA_int44_src(data)                                           ((0x00004000&(data))>>14)
#define MIS_UMSK_ISR_GP1DA_get_int44(data)                                           ((0x00004000&(data))>>14)
#define MIS_UMSK_ISR_GP1DA_int43_shift                                               (13)
#define MIS_UMSK_ISR_GP1DA_int43_mask                                                (0x00002000)
#define MIS_UMSK_ISR_GP1DA_int43(data)                                               (0x00002000&((data)<<13))
#define MIS_UMSK_ISR_GP1DA_int43_src(data)                                           ((0x00002000&(data))>>13)
#define MIS_UMSK_ISR_GP1DA_get_int43(data)                                           ((0x00002000&(data))>>13)
#define MIS_UMSK_ISR_GP1DA_int42_shift                                               (12)
#define MIS_UMSK_ISR_GP1DA_int42_mask                                                (0x00001000)
#define MIS_UMSK_ISR_GP1DA_int42(data)                                               (0x00001000&((data)<<12))
#define MIS_UMSK_ISR_GP1DA_int42_src(data)                                           ((0x00001000&(data))>>12)
#define MIS_UMSK_ISR_GP1DA_get_int42(data)                                           ((0x00001000&(data))>>12)
#define MIS_UMSK_ISR_GP1DA_int41_shift                                               (11)
#define MIS_UMSK_ISR_GP1DA_int41_mask                                                (0x00000800)
#define MIS_UMSK_ISR_GP1DA_int41(data)                                               (0x00000800&((data)<<11))
#define MIS_UMSK_ISR_GP1DA_int41_src(data)                                           ((0x00000800&(data))>>11)
#define MIS_UMSK_ISR_GP1DA_get_int41(data)                                           ((0x00000800&(data))>>11)
#define MIS_UMSK_ISR_GP1DA_int40_shift                                               (10)
#define MIS_UMSK_ISR_GP1DA_int40_mask                                                (0x00000400)
#define MIS_UMSK_ISR_GP1DA_int40(data)                                               (0x00000400&((data)<<10))
#define MIS_UMSK_ISR_GP1DA_int40_src(data)                                           ((0x00000400&(data))>>10)
#define MIS_UMSK_ISR_GP1DA_get_int40(data)                                           ((0x00000400&(data))>>10)
#define MIS_UMSK_ISR_GP1DA_int39_shift                                               (9)
#define MIS_UMSK_ISR_GP1DA_int39_mask                                                (0x00000200)
#define MIS_UMSK_ISR_GP1DA_int39(data)                                               (0x00000200&((data)<<9))
#define MIS_UMSK_ISR_GP1DA_int39_src(data)                                           ((0x00000200&(data))>>9)
#define MIS_UMSK_ISR_GP1DA_get_int39(data)                                           ((0x00000200&(data))>>9)
#define MIS_UMSK_ISR_GP1DA_int38_shift                                               (8)
#define MIS_UMSK_ISR_GP1DA_int38_mask                                                (0x00000100)
#define MIS_UMSK_ISR_GP1DA_int38(data)                                               (0x00000100&((data)<<8))
#define MIS_UMSK_ISR_GP1DA_int38_src(data)                                           ((0x00000100&(data))>>8)
#define MIS_UMSK_ISR_GP1DA_get_int38(data)                                           ((0x00000100&(data))>>8)
#define MIS_UMSK_ISR_GP1DA_int37_shift                                               (7)
#define MIS_UMSK_ISR_GP1DA_int37_mask                                                (0x00000080)
#define MIS_UMSK_ISR_GP1DA_int37(data)                                               (0x00000080&((data)<<7))
#define MIS_UMSK_ISR_GP1DA_int37_src(data)                                           ((0x00000080&(data))>>7)
#define MIS_UMSK_ISR_GP1DA_get_int37(data)                                           ((0x00000080&(data))>>7)
#define MIS_UMSK_ISR_GP1DA_int36_shift                                               (6)
#define MIS_UMSK_ISR_GP1DA_int36_mask                                                (0x00000040)
#define MIS_UMSK_ISR_GP1DA_int36(data)                                               (0x00000040&((data)<<6))
#define MIS_UMSK_ISR_GP1DA_int36_src(data)                                           ((0x00000040&(data))>>6)
#define MIS_UMSK_ISR_GP1DA_get_int36(data)                                           ((0x00000040&(data))>>6)
#define MIS_UMSK_ISR_GP1DA_int35_shift                                               (5)
#define MIS_UMSK_ISR_GP1DA_int35_mask                                                (0x00000020)
#define MIS_UMSK_ISR_GP1DA_int35(data)                                               (0x00000020&((data)<<5))
#define MIS_UMSK_ISR_GP1DA_int35_src(data)                                           ((0x00000020&(data))>>5)
#define MIS_UMSK_ISR_GP1DA_get_int35(data)                                           ((0x00000020&(data))>>5)
#define MIS_UMSK_ISR_GP1DA_int34_shift                                               (4)
#define MIS_UMSK_ISR_GP1DA_int34_mask                                                (0x00000010)
#define MIS_UMSK_ISR_GP1DA_int34(data)                                               (0x00000010&((data)<<4))
#define MIS_UMSK_ISR_GP1DA_int34_src(data)                                           ((0x00000010&(data))>>4)
#define MIS_UMSK_ISR_GP1DA_get_int34(data)                                           ((0x00000010&(data))>>4)
#define MIS_UMSK_ISR_GP1DA_int33_shift                                               (3)
#define MIS_UMSK_ISR_GP1DA_int33_mask                                                (0x00000008)
#define MIS_UMSK_ISR_GP1DA_int33(data)                                               (0x00000008&((data)<<3))
#define MIS_UMSK_ISR_GP1DA_int33_src(data)                                           ((0x00000008&(data))>>3)
#define MIS_UMSK_ISR_GP1DA_get_int33(data)                                           ((0x00000008&(data))>>3)
#define MIS_UMSK_ISR_GP1DA_int32_shift                                               (2)
#define MIS_UMSK_ISR_GP1DA_int32_mask                                                (0x00000004)
#define MIS_UMSK_ISR_GP1DA_int32(data)                                               (0x00000004&((data)<<2))
#define MIS_UMSK_ISR_GP1DA_int32_src(data)                                           ((0x00000004&(data))>>2)
#define MIS_UMSK_ISR_GP1DA_get_int32(data)                                           ((0x00000004&(data))>>2)
#define MIS_UMSK_ISR_GP1DA_int31_shift                                               (1)
#define MIS_UMSK_ISR_GP1DA_int31_mask                                                (0x00000002)
#define MIS_UMSK_ISR_GP1DA_int31(data)                                               (0x00000002&((data)<<1))
#define MIS_UMSK_ISR_GP1DA_int31_src(data)                                           ((0x00000002&(data))>>1)
#define MIS_UMSK_ISR_GP1DA_get_int31(data)                                           ((0x00000002&(data))>>1)
#define MIS_UMSK_ISR_GP1DA_write_data_shift                                          (0)
#define MIS_UMSK_ISR_GP1DA_write_data_mask                                           (0x00000001)
#define MIS_UMSK_ISR_GP1DA_write_data(data)                                          (0x00000001&((data)<<0))
#define MIS_UMSK_ISR_GP1DA_write_data_src(data)                                      ((0x00000001&(data))>>0)
#define MIS_UMSK_ISR_GP1DA_get_write_data(data)                                      ((0x00000001&(data))>>0)


#define MIS_UMSK_ISR_GP2DA                                                           0x9801B0A8
#define MIS_UMSK_ISR_GP2DA_reg_addr                                                  "0x9801B0A8"
#define MIS_UMSK_ISR_GP2DA_reg                                                       0x9801B0A8
#define set_MIS_UMSK_ISR_GP2DA_reg(data)   (*((volatile unsigned int*) MIS_UMSK_ISR_GP2DA_reg)=data)
#define get_MIS_UMSK_ISR_GP2DA_reg   (*((volatile unsigned int*) MIS_UMSK_ISR_GP2DA_reg))
#define MIS_UMSK_ISR_GP2DA_inst_adr                                                  "0x002A"
#define MIS_UMSK_ISR_GP2DA_inst                                                      0x002A
#define MIS_UMSK_ISR_GP2DA_int92_shift                                               (31)
#define MIS_UMSK_ISR_GP2DA_int92_mask                                                (0x80000000)
#define MIS_UMSK_ISR_GP2DA_int92(data)                                               (0x80000000&((data)<<31))
#define MIS_UMSK_ISR_GP2DA_int92_src(data)                                           ((0x80000000&(data))>>31)
#define MIS_UMSK_ISR_GP2DA_get_int92(data)                                           ((0x80000000&(data))>>31)
#define MIS_UMSK_ISR_GP2DA_int91_shift                                               (30)
#define MIS_UMSK_ISR_GP2DA_int91_mask                                                (0x40000000)
#define MIS_UMSK_ISR_GP2DA_int91(data)                                               (0x40000000&((data)<<30))
#define MIS_UMSK_ISR_GP2DA_int91_src(data)                                           ((0x40000000&(data))>>30)
#define MIS_UMSK_ISR_GP2DA_get_int91(data)                                           ((0x40000000&(data))>>30)
#define MIS_UMSK_ISR_GP2DA_int90_shift                                               (29)
#define MIS_UMSK_ISR_GP2DA_int90_mask                                                (0x20000000)
#define MIS_UMSK_ISR_GP2DA_int90(data)                                               (0x20000000&((data)<<29))
#define MIS_UMSK_ISR_GP2DA_int90_src(data)                                           ((0x20000000&(data))>>29)
#define MIS_UMSK_ISR_GP2DA_get_int90(data)                                           ((0x20000000&(data))>>29)
#define MIS_UMSK_ISR_GP2DA_int89_shift                                               (28)
#define MIS_UMSK_ISR_GP2DA_int89_mask                                                (0x10000000)
#define MIS_UMSK_ISR_GP2DA_int89(data)                                               (0x10000000&((data)<<28))
#define MIS_UMSK_ISR_GP2DA_int89_src(data)                                           ((0x10000000&(data))>>28)
#define MIS_UMSK_ISR_GP2DA_get_int89(data)                                           ((0x10000000&(data))>>28)
#define MIS_UMSK_ISR_GP2DA_int88_shift                                               (27)
#define MIS_UMSK_ISR_GP2DA_int88_mask                                                (0x08000000)
#define MIS_UMSK_ISR_GP2DA_int88(data)                                               (0x08000000&((data)<<27))
#define MIS_UMSK_ISR_GP2DA_int88_src(data)                                           ((0x08000000&(data))>>27)
#define MIS_UMSK_ISR_GP2DA_get_int88(data)                                           ((0x08000000&(data))>>27)
#define MIS_UMSK_ISR_GP2DA_int87_shift                                               (26)
#define MIS_UMSK_ISR_GP2DA_int87_mask                                                (0x04000000)
#define MIS_UMSK_ISR_GP2DA_int87(data)                                               (0x04000000&((data)<<26))
#define MIS_UMSK_ISR_GP2DA_int87_src(data)                                           ((0x04000000&(data))>>26)
#define MIS_UMSK_ISR_GP2DA_get_int87(data)                                           ((0x04000000&(data))>>26)
#define MIS_UMSK_ISR_GP2DA_int86_shift                                               (25)
#define MIS_UMSK_ISR_GP2DA_int86_mask                                                (0x02000000)
#define MIS_UMSK_ISR_GP2DA_int86(data)                                               (0x02000000&((data)<<25))
#define MIS_UMSK_ISR_GP2DA_int86_src(data)                                           ((0x02000000&(data))>>25)
#define MIS_UMSK_ISR_GP2DA_get_int86(data)                                           ((0x02000000&(data))>>25)
#define MIS_UMSK_ISR_GP2DA_int85_shift                                               (24)
#define MIS_UMSK_ISR_GP2DA_int85_mask                                                (0x01000000)
#define MIS_UMSK_ISR_GP2DA_int85(data)                                               (0x01000000&((data)<<24))
#define MIS_UMSK_ISR_GP2DA_int85_src(data)                                           ((0x01000000&(data))>>24)
#define MIS_UMSK_ISR_GP2DA_get_int85(data)                                           ((0x01000000&(data))>>24)
#define MIS_UMSK_ISR_GP2DA_int84_shift                                               (23)
#define MIS_UMSK_ISR_GP2DA_int84_mask                                                (0x00800000)
#define MIS_UMSK_ISR_GP2DA_int84(data)                                               (0x00800000&((data)<<23))
#define MIS_UMSK_ISR_GP2DA_int84_src(data)                                           ((0x00800000&(data))>>23)
#define MIS_UMSK_ISR_GP2DA_get_int84(data)                                           ((0x00800000&(data))>>23)
#define MIS_UMSK_ISR_GP2DA_int83_shift                                               (22)
#define MIS_UMSK_ISR_GP2DA_int83_mask                                                (0x00400000)
#define MIS_UMSK_ISR_GP2DA_int83(data)                                               (0x00400000&((data)<<22))
#define MIS_UMSK_ISR_GP2DA_int83_src(data)                                           ((0x00400000&(data))>>22)
#define MIS_UMSK_ISR_GP2DA_get_int83(data)                                           ((0x00400000&(data))>>22)
#define MIS_UMSK_ISR_GP2DA_int82_shift                                               (21)
#define MIS_UMSK_ISR_GP2DA_int82_mask                                                (0x00200000)
#define MIS_UMSK_ISR_GP2DA_int82(data)                                               (0x00200000&((data)<<21))
#define MIS_UMSK_ISR_GP2DA_int82_src(data)                                           ((0x00200000&(data))>>21)
#define MIS_UMSK_ISR_GP2DA_get_int82(data)                                           ((0x00200000&(data))>>21)
#define MIS_UMSK_ISR_GP2DA_int81_shift                                               (20)
#define MIS_UMSK_ISR_GP2DA_int81_mask                                                (0x00100000)
#define MIS_UMSK_ISR_GP2DA_int81(data)                                               (0x00100000&((data)<<20))
#define MIS_UMSK_ISR_GP2DA_int81_src(data)                                           ((0x00100000&(data))>>20)
#define MIS_UMSK_ISR_GP2DA_get_int81(data)                                           ((0x00100000&(data))>>20)
#define MIS_UMSK_ISR_GP2DA_int80_shift                                               (19)
#define MIS_UMSK_ISR_GP2DA_int80_mask                                                (0x00080000)
#define MIS_UMSK_ISR_GP2DA_int80(data)                                               (0x00080000&((data)<<19))
#define MIS_UMSK_ISR_GP2DA_int80_src(data)                                           ((0x00080000&(data))>>19)
#define MIS_UMSK_ISR_GP2DA_get_int80(data)                                           ((0x00080000&(data))>>19)
#define MIS_UMSK_ISR_GP2DA_int79_shift                                               (18)
#define MIS_UMSK_ISR_GP2DA_int79_mask                                                (0x00040000)
#define MIS_UMSK_ISR_GP2DA_int79(data)                                               (0x00040000&((data)<<18))
#define MIS_UMSK_ISR_GP2DA_int79_src(data)                                           ((0x00040000&(data))>>18)
#define MIS_UMSK_ISR_GP2DA_get_int79(data)                                           ((0x00040000&(data))>>18)
#define MIS_UMSK_ISR_GP2DA_int78_shift                                               (17)
#define MIS_UMSK_ISR_GP2DA_int78_mask                                                (0x00020000)
#define MIS_UMSK_ISR_GP2DA_int78(data)                                               (0x00020000&((data)<<17))
#define MIS_UMSK_ISR_GP2DA_int78_src(data)                                           ((0x00020000&(data))>>17)
#define MIS_UMSK_ISR_GP2DA_get_int78(data)                                           ((0x00020000&(data))>>17)
#define MIS_UMSK_ISR_GP2DA_int77_shift                                               (16)
#define MIS_UMSK_ISR_GP2DA_int77_mask                                                (0x00010000)
#define MIS_UMSK_ISR_GP2DA_int77(data)                                               (0x00010000&((data)<<16))
#define MIS_UMSK_ISR_GP2DA_int77_src(data)                                           ((0x00010000&(data))>>16)
#define MIS_UMSK_ISR_GP2DA_get_int77(data)                                           ((0x00010000&(data))>>16)
#define MIS_UMSK_ISR_GP2DA_int76_shift                                               (15)
#define MIS_UMSK_ISR_GP2DA_int76_mask                                                (0x00008000)
#define MIS_UMSK_ISR_GP2DA_int76(data)                                               (0x00008000&((data)<<15))
#define MIS_UMSK_ISR_GP2DA_int76_src(data)                                           ((0x00008000&(data))>>15)
#define MIS_UMSK_ISR_GP2DA_get_int76(data)                                           ((0x00008000&(data))>>15)
#define MIS_UMSK_ISR_GP2DA_int75_shift                                               (14)
#define MIS_UMSK_ISR_GP2DA_int75_mask                                                (0x00004000)
#define MIS_UMSK_ISR_GP2DA_int75(data)                                               (0x00004000&((data)<<14))
#define MIS_UMSK_ISR_GP2DA_int75_src(data)                                           ((0x00004000&(data))>>14)
#define MIS_UMSK_ISR_GP2DA_get_int75(data)                                           ((0x00004000&(data))>>14)
#define MIS_UMSK_ISR_GP2DA_int74_shift                                               (13)
#define MIS_UMSK_ISR_GP2DA_int74_mask                                                (0x00002000)
#define MIS_UMSK_ISR_GP2DA_int74(data)                                               (0x00002000&((data)<<13))
#define MIS_UMSK_ISR_GP2DA_int74_src(data)                                           ((0x00002000&(data))>>13)
#define MIS_UMSK_ISR_GP2DA_get_int74(data)                                           ((0x00002000&(data))>>13)
#define MIS_UMSK_ISR_GP2DA_int73_shift                                               (12)
#define MIS_UMSK_ISR_GP2DA_int73_mask                                                (0x00001000)
#define MIS_UMSK_ISR_GP2DA_int73(data)                                               (0x00001000&((data)<<12))
#define MIS_UMSK_ISR_GP2DA_int73_src(data)                                           ((0x00001000&(data))>>12)
#define MIS_UMSK_ISR_GP2DA_get_int73(data)                                           ((0x00001000&(data))>>12)
#define MIS_UMSK_ISR_GP2DA_int72_shift                                               (11)
#define MIS_UMSK_ISR_GP2DA_int72_mask                                                (0x00000800)
#define MIS_UMSK_ISR_GP2DA_int72(data)                                               (0x00000800&((data)<<11))
#define MIS_UMSK_ISR_GP2DA_int72_src(data)                                           ((0x00000800&(data))>>11)
#define MIS_UMSK_ISR_GP2DA_get_int72(data)                                           ((0x00000800&(data))>>11)
#define MIS_UMSK_ISR_GP2DA_int71_shift                                               (10)
#define MIS_UMSK_ISR_GP2DA_int71_mask                                                (0x00000400)
#define MIS_UMSK_ISR_GP2DA_int71(data)                                               (0x00000400&((data)<<10))
#define MIS_UMSK_ISR_GP2DA_int71_src(data)                                           ((0x00000400&(data))>>10)
#define MIS_UMSK_ISR_GP2DA_get_int71(data)                                           ((0x00000400&(data))>>10)
#define MIS_UMSK_ISR_GP2DA_int70_shift                                               (9)
#define MIS_UMSK_ISR_GP2DA_int70_mask                                                (0x00000200)
#define MIS_UMSK_ISR_GP2DA_int70(data)                                               (0x00000200&((data)<<9))
#define MIS_UMSK_ISR_GP2DA_int70_src(data)                                           ((0x00000200&(data))>>9)
#define MIS_UMSK_ISR_GP2DA_get_int70(data)                                           ((0x00000200&(data))>>9)
#define MIS_UMSK_ISR_GP2DA_int69_shift                                               (8)
#define MIS_UMSK_ISR_GP2DA_int69_mask                                                (0x00000100)
#define MIS_UMSK_ISR_GP2DA_int69(data)                                               (0x00000100&((data)<<8))
#define MIS_UMSK_ISR_GP2DA_int69_src(data)                                           ((0x00000100&(data))>>8)
#define MIS_UMSK_ISR_GP2DA_get_int69(data)                                           ((0x00000100&(data))>>8)
#define MIS_UMSK_ISR_GP2DA_int68_shift                                               (7)
#define MIS_UMSK_ISR_GP2DA_int68_mask                                                (0x00000080)
#define MIS_UMSK_ISR_GP2DA_int68(data)                                               (0x00000080&((data)<<7))
#define MIS_UMSK_ISR_GP2DA_int68_src(data)                                           ((0x00000080&(data))>>7)
#define MIS_UMSK_ISR_GP2DA_get_int68(data)                                           ((0x00000080&(data))>>7)
#define MIS_UMSK_ISR_GP2DA_int67_shift                                               (6)
#define MIS_UMSK_ISR_GP2DA_int67_mask                                                (0x00000040)
#define MIS_UMSK_ISR_GP2DA_int67(data)                                               (0x00000040&((data)<<6))
#define MIS_UMSK_ISR_GP2DA_int67_src(data)                                           ((0x00000040&(data))>>6)
#define MIS_UMSK_ISR_GP2DA_get_int67(data)                                           ((0x00000040&(data))>>6)
#define MIS_UMSK_ISR_GP2DA_int66_shift                                               (5)
#define MIS_UMSK_ISR_GP2DA_int66_mask                                                (0x00000020)
#define MIS_UMSK_ISR_GP2DA_int66(data)                                               (0x00000020&((data)<<5))
#define MIS_UMSK_ISR_GP2DA_int66_src(data)                                           ((0x00000020&(data))>>5)
#define MIS_UMSK_ISR_GP2DA_get_int66(data)                                           ((0x00000020&(data))>>5)
#define MIS_UMSK_ISR_GP2DA_int65_shift                                               (4)
#define MIS_UMSK_ISR_GP2DA_int65_mask                                                (0x00000010)
#define MIS_UMSK_ISR_GP2DA_int65(data)                                               (0x00000010&((data)<<4))
#define MIS_UMSK_ISR_GP2DA_int65_src(data)                                           ((0x00000010&(data))>>4)
#define MIS_UMSK_ISR_GP2DA_get_int65(data)                                           ((0x00000010&(data))>>4)
#define MIS_UMSK_ISR_GP2DA_int64_shift                                               (3)
#define MIS_UMSK_ISR_GP2DA_int64_mask                                                (0x00000008)
#define MIS_UMSK_ISR_GP2DA_int64(data)                                               (0x00000008&((data)<<3))
#define MIS_UMSK_ISR_GP2DA_int64_src(data)                                           ((0x00000008&(data))>>3)
#define MIS_UMSK_ISR_GP2DA_get_int64(data)                                           ((0x00000008&(data))>>3)
#define MIS_UMSK_ISR_GP2DA_int63_shift                                               (2)
#define MIS_UMSK_ISR_GP2DA_int63_mask                                                (0x00000004)
#define MIS_UMSK_ISR_GP2DA_int63(data)                                               (0x00000004&((data)<<2))
#define MIS_UMSK_ISR_GP2DA_int63_src(data)                                           ((0x00000004&(data))>>2)
#define MIS_UMSK_ISR_GP2DA_get_int63(data)                                           ((0x00000004&(data))>>2)
#define MIS_UMSK_ISR_GP2DA_int62_shift                                               (1)
#define MIS_UMSK_ISR_GP2DA_int62_mask                                                (0x00000002)
#define MIS_UMSK_ISR_GP2DA_int62(data)                                               (0x00000002&((data)<<1))
#define MIS_UMSK_ISR_GP2DA_int62_src(data)                                           ((0x00000002&(data))>>1)
#define MIS_UMSK_ISR_GP2DA_get_int62(data)                                           ((0x00000002&(data))>>1)
#define MIS_UMSK_ISR_GP2DA_write_data_shift                                          (0)
#define MIS_UMSK_ISR_GP2DA_write_data_mask                                           (0x00000001)
#define MIS_UMSK_ISR_GP2DA_write_data(data)                                          (0x00000001&((data)<<0))
#define MIS_UMSK_ISR_GP2DA_write_data_src(data)                                      ((0x00000001&(data))>>0)
#define MIS_UMSK_ISR_GP2DA_get_write_data(data)                                      ((0x00000001&(data))>>0)


#define MIS_UMSK_ISR_GP3DA                                                           0x9801B0BC
#define MIS_UMSK_ISR_GP3DA_reg_addr                                                  "0x9801B0BC"
#define MIS_UMSK_ISR_GP3DA_reg                                                       0x9801B0BC
#define set_MIS_UMSK_ISR_GP3DA_reg(data)   (*((volatile unsigned int*) MIS_UMSK_ISR_GP3DA_reg)=data)
#define get_MIS_UMSK_ISR_GP3DA_reg   (*((volatile unsigned int*) MIS_UMSK_ISR_GP3DA_reg))
#define MIS_UMSK_ISR_GP3DA_inst_adr                                                  "0x002F"
#define MIS_UMSK_ISR_GP3DA_inst                                                      0x002F
#define MIS_UMSK_ISR_GP3DA_int100_shift                                              (8)
#define MIS_UMSK_ISR_GP3DA_int100_mask                                               (0x00000100)
#define MIS_UMSK_ISR_GP3DA_int100(data)                                              (0x00000100&((data)<<8))
#define MIS_UMSK_ISR_GP3DA_int100_src(data)                                          ((0x00000100&(data))>>8)
#define MIS_UMSK_ISR_GP3DA_get_int100(data)                                          ((0x00000100&(data))>>8)
#define MIS_UMSK_ISR_GP3DA_int99_shift                                               (7)
#define MIS_UMSK_ISR_GP3DA_int99_mask                                                (0x00000080)
#define MIS_UMSK_ISR_GP3DA_int99(data)                                               (0x00000080&((data)<<7))
#define MIS_UMSK_ISR_GP3DA_int99_src(data)                                           ((0x00000080&(data))>>7)
#define MIS_UMSK_ISR_GP3DA_get_int99(data)                                           ((0x00000080&(data))>>7)
#define MIS_UMSK_ISR_GP3DA_int98_shift                                               (6)
#define MIS_UMSK_ISR_GP3DA_int98_mask                                                (0x00000040)
#define MIS_UMSK_ISR_GP3DA_int98(data)                                               (0x00000040&((data)<<6))
#define MIS_UMSK_ISR_GP3DA_int98_src(data)                                           ((0x00000040&(data))>>6)
#define MIS_UMSK_ISR_GP3DA_get_int98(data)                                           ((0x00000040&(data))>>6)
#define MIS_UMSK_ISR_GP3DA_int97_shift                                               (5)
#define MIS_UMSK_ISR_GP3DA_int97_mask                                                (0x00000020)
#define MIS_UMSK_ISR_GP3DA_int97(data)                                               (0x00000020&((data)<<5))
#define MIS_UMSK_ISR_GP3DA_int97_src(data)                                           ((0x00000020&(data))>>5)
#define MIS_UMSK_ISR_GP3DA_get_int97(data)                                           ((0x00000020&(data))>>5)
#define MIS_UMSK_ISR_GP3DA_int96_shift                                               (4)
#define MIS_UMSK_ISR_GP3DA_int96_mask                                                (0x00000010)
#define MIS_UMSK_ISR_GP3DA_int96(data)                                               (0x00000010&((data)<<4))
#define MIS_UMSK_ISR_GP3DA_int96_src(data)                                           ((0x00000010&(data))>>4)
#define MIS_UMSK_ISR_GP3DA_get_int96(data)                                           ((0x00000010&(data))>>4)
#define MIS_UMSK_ISR_GP3DA_int95_shift                                               (3)
#define MIS_UMSK_ISR_GP3DA_int95_mask                                                (0x00000008)
#define MIS_UMSK_ISR_GP3DA_int95(data)                                               (0x00000008&((data)<<3))
#define MIS_UMSK_ISR_GP3DA_int95_src(data)                                           ((0x00000008&(data))>>3)
#define MIS_UMSK_ISR_GP3DA_get_int95(data)                                           ((0x00000008&(data))>>3)
#define MIS_UMSK_ISR_GP3DA_int94_shift                                               (2)
#define MIS_UMSK_ISR_GP3DA_int94_mask                                                (0x00000004)
#define MIS_UMSK_ISR_GP3DA_int94(data)                                               (0x00000004&((data)<<2))
#define MIS_UMSK_ISR_GP3DA_int94_src(data)                                           ((0x00000004&(data))>>2)
#define MIS_UMSK_ISR_GP3DA_get_int94(data)                                           ((0x00000004&(data))>>2)
#define MIS_UMSK_ISR_GP3DA_int93_shift                                               (1)
#define MIS_UMSK_ISR_GP3DA_int93_mask                                                (0x00000002)
#define MIS_UMSK_ISR_GP3DA_int93(data)                                               (0x00000002&((data)<<1))
#define MIS_UMSK_ISR_GP3DA_int93_src(data)                                           ((0x00000002&(data))>>1)
#define MIS_UMSK_ISR_GP3DA_get_int93(data)                                           ((0x00000002&(data))>>1)
#define MIS_UMSK_ISR_GP3DA_write_data_shift                                          (0)
#define MIS_UMSK_ISR_GP3DA_write_data_mask                                           (0x00000001)
#define MIS_UMSK_ISR_GP3DA_write_data(data)                                          (0x00000001&((data)<<0))
#define MIS_UMSK_ISR_GP3DA_write_data_src(data)                                      ((0x00000001&(data))>>0)
#define MIS_UMSK_ISR_GP3DA_get_write_data(data)                                      ((0x00000001&(data))>>0)


#define MIS_DUMMY1                                                                   0x9801B068
#define MIS_DUMMY1_reg_addr                                                          "0x9801B068"
#define MIS_DUMMY1_reg                                                               0x9801B068
#define set_MIS_DUMMY1_reg(data)   (*((volatile unsigned int*) MIS_DUMMY1_reg)=data)
#define get_MIS_DUMMY1_reg   (*((volatile unsigned int*) MIS_DUMMY1_reg))
#define MIS_DUMMY1_inst_adr                                                          "0x001A"
#define MIS_DUMMY1_inst                                                              0x001A
#define MIS_DUMMY1_write_enable2_shift                                               (31)
#define MIS_DUMMY1_write_enable2_mask                                                (0x80000000)
#define MIS_DUMMY1_write_enable2(data)                                               (0x80000000&((data)<<31))
#define MIS_DUMMY1_write_enable2_src(data)                                           ((0x80000000&(data))>>31)
#define MIS_DUMMY1_get_write_enable2(data)                                           ((0x80000000&(data))>>31)
#define MIS_DUMMY1_rvd2_shift                                                        (16)
#define MIS_DUMMY1_rvd2_mask                                                         (0x7FFF0000)
#define MIS_DUMMY1_rvd2(data)                                                        (0x7FFF0000&((data)<<16))
#define MIS_DUMMY1_rvd2_src(data)                                                    ((0x7FFF0000&(data))>>16)
#define MIS_DUMMY1_get_rvd2(data)                                                    ((0x7FFF0000&(data))>>16)
#define MIS_DUMMY1_write_enable1_shift                                               (15)
#define MIS_DUMMY1_write_enable1_mask                                                (0x00008000)
#define MIS_DUMMY1_write_enable1(data)                                               (0x00008000&((data)<<15))
#define MIS_DUMMY1_write_enable1_src(data)                                           ((0x00008000&(data))>>15)
#define MIS_DUMMY1_get_write_enable1(data)                                           ((0x00008000&(data))>>15)
#define MIS_DUMMY1_rvd1_shift                                                        (0)
#define MIS_DUMMY1_rvd1_mask                                                         (0x00007FFF)
#define MIS_DUMMY1_rvd1(data)                                                        (0x00007FFF&((data)<<0))
#define MIS_DUMMY1_rvd1_src(data)                                                    ((0x00007FFF&(data))>>0)
#define MIS_DUMMY1_get_rvd1(data)                                                    ((0x00007FFF&(data))>>0)


#define MIS_UR_CTRL                                                                  0x9801B060
#define MIS_UR_CTRL_reg_addr                                                         "0x9801B060"
#define MIS_UR_CTRL_reg                                                              0x9801B060
#define set_MIS_UR_CTRL_reg(data)   (*((volatile unsigned int*) MIS_UR_CTRL_reg)=data)
#define get_MIS_UR_CTRL_reg   (*((volatile unsigned int*) MIS_UR_CTRL_reg))
#define MIS_UR_CTRL_inst_adr                                                         "0x0018"
#define MIS_UR_CTRL_inst                                                             0x0018
#define MIS_UR_CTRL_rvd3_shift                                                       (29)
#define MIS_UR_CTRL_rvd3_mask                                                        (0xE0000000)
#define MIS_UR_CTRL_rvd3(data)                                                       (0xE0000000&((data)<<29))
#define MIS_UR_CTRL_rvd3_src(data)                                                   ((0xE0000000&(data))>>29)
#define MIS_UR_CTRL_get_rvd3(data)                                                   ((0xE0000000&(data))>>29)
#define MIS_UR_CTRL_to_len_shift                                                     (20)
#define MIS_UR_CTRL_to_len_mask                                                      (0x0FF00000)
#define MIS_UR_CTRL_to_len(data)                                                     (0x0FF00000&((data)<<20))
#define MIS_UR_CTRL_to_len_src(data)                                                 ((0x0FF00000&(data))>>20)
#define MIS_UR_CTRL_get_to_len(data)                                                 ((0x0FF00000&(data))>>20)
#define MIS_UR_CTRL_to_int_en_shift                                                  (19)
#define MIS_UR_CTRL_to_int_en_mask                                                   (0x00080000)
#define MIS_UR_CTRL_to_int_en(data)                                                  (0x00080000&((data)<<19))
#define MIS_UR_CTRL_to_int_en_src(data)                                              ((0x00080000&(data))>>19)
#define MIS_UR_CTRL_get_to_int_en(data)                                              ((0x00080000&(data))>>19)
#define MIS_UR_CTRL_toauareq_shift                                                   (18)
#define MIS_UR_CTRL_toauareq_mask                                                    (0x00040000)
#define MIS_UR_CTRL_toauareq(data)                                                   (0x00040000&((data)<<18))
#define MIS_UR_CTRL_toauareq_src(data)                                               ((0x00040000&(data))>>18)
#define MIS_UR_CTRL_get_toauareq(data)                                               ((0x00040000&(data))>>18)
#define MIS_UR_CTRL_flow_pol_shift                                                   (17)
#define MIS_UR_CTRL_flow_pol_mask                                                    (0x00020000)
#define MIS_UR_CTRL_flow_pol(data)                                                   (0x00020000&((data)<<17))
#define MIS_UR_CTRL_flow_pol_src(data)                                               ((0x00020000&(data))>>17)
#define MIS_UR_CTRL_get_flow_pol(data)                                               ((0x00020000&(data))>>17)
#define MIS_UR_CTRL_mdifen_shift                                                     (16)
#define MIS_UR_CTRL_mdifen_mask                                                      (0x00010000)
#define MIS_UR_CTRL_mdifen(data)                                                     (0x00010000&((data)<<16))
#define MIS_UR_CTRL_mdifen_src(data)                                                 ((0x00010000&(data))>>16)
#define MIS_UR_CTRL_get_mdifen(data)                                                 ((0x00010000&(data))>>16)
#define MIS_UR_CTRL_txempthr_shift                                                   (8)
#define MIS_UR_CTRL_txempthr_mask                                                    (0x00003F00)
#define MIS_UR_CTRL_txempthr(data)                                                   (0x00003F00&((data)<<8))
#define MIS_UR_CTRL_txempthr_src(data)                                               ((0x00003F00&(data))>>8)
#define MIS_UR_CTRL_get_txempthr(data)                                               ((0x00003F00&(data))>>8)
#define MIS_UR_CTRL_rxfulthr_shift                                                   (0)
#define MIS_UR_CTRL_rxfulthr_mask                                                    (0x0000003F)
#define MIS_UR_CTRL_rxfulthr(data)                                                   (0x0000003F&((data)<<0))
#define MIS_UR_CTRL_rxfulthr_src(data)                                               ((0x0000003F&(data))>>0)
#define MIS_UR_CTRL_get_rxfulthr(data)                                               ((0x0000003F&(data))>>0)


#define MIS_UR2_CTRL                                                                 0x9801B064
#define MIS_UR2_CTRL_reg_addr                                                        "0x9801B064"
#define MIS_UR2_CTRL_reg                                                             0x9801B064
#define set_MIS_UR2_CTRL_reg(data)   (*((volatile unsigned int*) MIS_UR2_CTRL_reg)=data)
#define get_MIS_UR2_CTRL_reg   (*((volatile unsigned int*) MIS_UR2_CTRL_reg))
#define MIS_UR2_CTRL_inst_adr                                                        "0x0019"
#define MIS_UR2_CTRL_inst                                                            0x0019
#define MIS_UR2_CTRL_rvd3_shift                                                      (29)
#define MIS_UR2_CTRL_rvd3_mask                                                       (0xE0000000)
#define MIS_UR2_CTRL_rvd3(data)                                                      (0xE0000000&((data)<<29))
#define MIS_UR2_CTRL_rvd3_src(data)                                                  ((0xE0000000&(data))>>29)
#define MIS_UR2_CTRL_get_rvd3(data)                                                  ((0xE0000000&(data))>>29)
#define MIS_UR2_CTRL_to_len_shift                                                    (20)
#define MIS_UR2_CTRL_to_len_mask                                                     (0x0FF00000)
#define MIS_UR2_CTRL_to_len(data)                                                    (0x0FF00000&((data)<<20))
#define MIS_UR2_CTRL_to_len_src(data)                                                ((0x0FF00000&(data))>>20)
#define MIS_UR2_CTRL_get_to_len(data)                                                ((0x0FF00000&(data))>>20)
#define MIS_UR2_CTRL_to_int_en_shift                                                 (19)
#define MIS_UR2_CTRL_to_int_en_mask                                                  (0x00080000)
#define MIS_UR2_CTRL_to_int_en(data)                                                 (0x00080000&((data)<<19))
#define MIS_UR2_CTRL_to_int_en_src(data)                                             ((0x00080000&(data))>>19)
#define MIS_UR2_CTRL_get_to_int_en(data)                                             ((0x00080000&(data))>>19)
#define MIS_UR2_CTRL_toauareq_shift                                                  (18)
#define MIS_UR2_CTRL_toauareq_mask                                                   (0x00040000)
#define MIS_UR2_CTRL_toauareq(data)                                                  (0x00040000&((data)<<18))
#define MIS_UR2_CTRL_toauareq_src(data)                                              ((0x00040000&(data))>>18)
#define MIS_UR2_CTRL_get_toauareq(data)                                              ((0x00040000&(data))>>18)
#define MIS_UR2_CTRL_flow_pol_shift                                                  (17)
#define MIS_UR2_CTRL_flow_pol_mask                                                   (0x00020000)
#define MIS_UR2_CTRL_flow_pol(data)                                                  (0x00020000&((data)<<17))
#define MIS_UR2_CTRL_flow_pol_src(data)                                              ((0x00020000&(data))>>17)
#define MIS_UR2_CTRL_get_flow_pol(data)                                              ((0x00020000&(data))>>17)
#define MIS_UR2_CTRL_mdifen_shift                                                    (16)
#define MIS_UR2_CTRL_mdifen_mask                                                     (0x00010000)
#define MIS_UR2_CTRL_mdifen(data)                                                    (0x00010000&((data)<<16))
#define MIS_UR2_CTRL_mdifen_src(data)                                                ((0x00010000&(data))>>16)
#define MIS_UR2_CTRL_get_mdifen(data)                                                ((0x00010000&(data))>>16)
#define MIS_UR2_CTRL_txempthr_shift                                                  (8)
#define MIS_UR2_CTRL_txempthr_mask                                                   (0x00003F00)
#define MIS_UR2_CTRL_txempthr(data)                                                  (0x00003F00&((data)<<8))
#define MIS_UR2_CTRL_txempthr_src(data)                                              ((0x00003F00&(data))>>8)
#define MIS_UR2_CTRL_get_txempthr(data)                                              ((0x00003F00&(data))>>8)
#define MIS_UR2_CTRL_rxfulthr_shift                                                  (0)
#define MIS_UR2_CTRL_rxfulthr_mask                                                   (0x0000003F)
#define MIS_UR2_CTRL_rxfulthr(data)                                                  (0x0000003F&((data)<<0))
#define MIS_UR2_CTRL_rxfulthr_src(data)                                              ((0x0000003F&(data))>>0)
#define MIS_UR2_CTRL_get_rxfulthr(data)                                              ((0x0000003F&(data))>>0)


#define MIS_FAST_ISR_GPIO0_A                                                         0x9801B070
#define MIS_FAST_ISR_GPIO0_A_reg_addr                                                "0x9801B070"
#define MIS_FAST_ISR_GPIO0_A_reg                                                     0x9801B070
#define set_MIS_FAST_ISR_GPIO0_A_reg(data)   (*((volatile unsigned int*) MIS_FAST_ISR_GPIO0_A_reg)=data)
#define get_MIS_FAST_ISR_GPIO0_A_reg   (*((volatile unsigned int*) MIS_FAST_ISR_GPIO0_A_reg))
#define MIS_FAST_ISR_GPIO0_A_inst_adr                                                "0x001C"
#define MIS_FAST_ISR_GPIO0_A_inst                                                    0x001C
#define MIS_FAST_ISR_GPIO0_A_int_30_shift                                            (31)
#define MIS_FAST_ISR_GPIO0_A_int_30_mask                                             (0x80000000)
#define MIS_FAST_ISR_GPIO0_A_int_30(data)                                            (0x80000000&((data)<<31))
#define MIS_FAST_ISR_GPIO0_A_int_30_src(data)                                        ((0x80000000&(data))>>31)
#define MIS_FAST_ISR_GPIO0_A_get_int_30(data)                                        ((0x80000000&(data))>>31)
#define MIS_FAST_ISR_GPIO0_A_int_29_shift                                            (30)
#define MIS_FAST_ISR_GPIO0_A_int_29_mask                                             (0x40000000)
#define MIS_FAST_ISR_GPIO0_A_int_29(data)                                            (0x40000000&((data)<<30))
#define MIS_FAST_ISR_GPIO0_A_int_29_src(data)                                        ((0x40000000&(data))>>30)
#define MIS_FAST_ISR_GPIO0_A_get_int_29(data)                                        ((0x40000000&(data))>>30)
#define MIS_FAST_ISR_GPIO0_A_int_28_shift                                            (29)
#define MIS_FAST_ISR_GPIO0_A_int_28_mask                                             (0x20000000)
#define MIS_FAST_ISR_GPIO0_A_int_28(data)                                            (0x20000000&((data)<<29))
#define MIS_FAST_ISR_GPIO0_A_int_28_src(data)                                        ((0x20000000&(data))>>29)
#define MIS_FAST_ISR_GPIO0_A_get_int_28(data)                                        ((0x20000000&(data))>>29)
#define MIS_FAST_ISR_GPIO0_A_int_27_shift                                            (28)
#define MIS_FAST_ISR_GPIO0_A_int_27_mask                                             (0x10000000)
#define MIS_FAST_ISR_GPIO0_A_int_27(data)                                            (0x10000000&((data)<<28))
#define MIS_FAST_ISR_GPIO0_A_int_27_src(data)                                        ((0x10000000&(data))>>28)
#define MIS_FAST_ISR_GPIO0_A_get_int_27(data)                                        ((0x10000000&(data))>>28)
#define MIS_FAST_ISR_GPIO0_A_int_26_shift                                            (27)
#define MIS_FAST_ISR_GPIO0_A_int_26_mask                                             (0x08000000)
#define MIS_FAST_ISR_GPIO0_A_int_26(data)                                            (0x08000000&((data)<<27))
#define MIS_FAST_ISR_GPIO0_A_int_26_src(data)                                        ((0x08000000&(data))>>27)
#define MIS_FAST_ISR_GPIO0_A_get_int_26(data)                                        ((0x08000000&(data))>>27)
#define MIS_FAST_ISR_GPIO0_A_int_25_shift                                            (26)
#define MIS_FAST_ISR_GPIO0_A_int_25_mask                                             (0x04000000)
#define MIS_FAST_ISR_GPIO0_A_int_25(data)                                            (0x04000000&((data)<<26))
#define MIS_FAST_ISR_GPIO0_A_int_25_src(data)                                        ((0x04000000&(data))>>26)
#define MIS_FAST_ISR_GPIO0_A_get_int_25(data)                                        ((0x04000000&(data))>>26)
#define MIS_FAST_ISR_GPIO0_A_int_24_shift                                            (25)
#define MIS_FAST_ISR_GPIO0_A_int_24_mask                                             (0x02000000)
#define MIS_FAST_ISR_GPIO0_A_int_24(data)                                            (0x02000000&((data)<<25))
#define MIS_FAST_ISR_GPIO0_A_int_24_src(data)                                        ((0x02000000&(data))>>25)
#define MIS_FAST_ISR_GPIO0_A_get_int_24(data)                                        ((0x02000000&(data))>>25)
#define MIS_FAST_ISR_GPIO0_A_int_23_shift                                            (24)
#define MIS_FAST_ISR_GPIO0_A_int_23_mask                                             (0x01000000)
#define MIS_FAST_ISR_GPIO0_A_int_23(data)                                            (0x01000000&((data)<<24))
#define MIS_FAST_ISR_GPIO0_A_int_23_src(data)                                        ((0x01000000&(data))>>24)
#define MIS_FAST_ISR_GPIO0_A_get_int_23(data)                                        ((0x01000000&(data))>>24)
#define MIS_FAST_ISR_GPIO0_A_int_22_shift                                            (23)
#define MIS_FAST_ISR_GPIO0_A_int_22_mask                                             (0x00800000)
#define MIS_FAST_ISR_GPIO0_A_int_22(data)                                            (0x00800000&((data)<<23))
#define MIS_FAST_ISR_GPIO0_A_int_22_src(data)                                        ((0x00800000&(data))>>23)
#define MIS_FAST_ISR_GPIO0_A_get_int_22(data)                                        ((0x00800000&(data))>>23)
#define MIS_FAST_ISR_GPIO0_A_int_21_shift                                            (22)
#define MIS_FAST_ISR_GPIO0_A_int_21_mask                                             (0x00400000)
#define MIS_FAST_ISR_GPIO0_A_int_21(data)                                            (0x00400000&((data)<<22))
#define MIS_FAST_ISR_GPIO0_A_int_21_src(data)                                        ((0x00400000&(data))>>22)
#define MIS_FAST_ISR_GPIO0_A_get_int_21(data)                                        ((0x00400000&(data))>>22)
#define MIS_FAST_ISR_GPIO0_A_int_20_shift                                            (21)
#define MIS_FAST_ISR_GPIO0_A_int_20_mask                                             (0x00200000)
#define MIS_FAST_ISR_GPIO0_A_int_20(data)                                            (0x00200000&((data)<<21))
#define MIS_FAST_ISR_GPIO0_A_int_20_src(data)                                        ((0x00200000&(data))>>21)
#define MIS_FAST_ISR_GPIO0_A_get_int_20(data)                                        ((0x00200000&(data))>>21)
#define MIS_FAST_ISR_GPIO0_A_int_19_shift                                            (20)
#define MIS_FAST_ISR_GPIO0_A_int_19_mask                                             (0x00100000)
#define MIS_FAST_ISR_GPIO0_A_int_19(data)                                            (0x00100000&((data)<<20))
#define MIS_FAST_ISR_GPIO0_A_int_19_src(data)                                        ((0x00100000&(data))>>20)
#define MIS_FAST_ISR_GPIO0_A_get_int_19(data)                                        ((0x00100000&(data))>>20)
#define MIS_FAST_ISR_GPIO0_A_int_18_shift                                            (19)
#define MIS_FAST_ISR_GPIO0_A_int_18_mask                                             (0x00080000)
#define MIS_FAST_ISR_GPIO0_A_int_18(data)                                            (0x00080000&((data)<<19))
#define MIS_FAST_ISR_GPIO0_A_int_18_src(data)                                        ((0x00080000&(data))>>19)
#define MIS_FAST_ISR_GPIO0_A_get_int_18(data)                                        ((0x00080000&(data))>>19)
#define MIS_FAST_ISR_GPIO0_A_int_17_shift                                            (18)
#define MIS_FAST_ISR_GPIO0_A_int_17_mask                                             (0x00040000)
#define MIS_FAST_ISR_GPIO0_A_int_17(data)                                            (0x00040000&((data)<<18))
#define MIS_FAST_ISR_GPIO0_A_int_17_src(data)                                        ((0x00040000&(data))>>18)
#define MIS_FAST_ISR_GPIO0_A_get_int_17(data)                                        ((0x00040000&(data))>>18)
#define MIS_FAST_ISR_GPIO0_A_int_16_shift                                            (17)
#define MIS_FAST_ISR_GPIO0_A_int_16_mask                                             (0x00020000)
#define MIS_FAST_ISR_GPIO0_A_int_16(data)                                            (0x00020000&((data)<<17))
#define MIS_FAST_ISR_GPIO0_A_int_16_src(data)                                        ((0x00020000&(data))>>17)
#define MIS_FAST_ISR_GPIO0_A_get_int_16(data)                                        ((0x00020000&(data))>>17)
#define MIS_FAST_ISR_GPIO0_A_int_15_shift                                            (16)
#define MIS_FAST_ISR_GPIO0_A_int_15_mask                                             (0x00010000)
#define MIS_FAST_ISR_GPIO0_A_int_15(data)                                            (0x00010000&((data)<<16))
#define MIS_FAST_ISR_GPIO0_A_int_15_src(data)                                        ((0x00010000&(data))>>16)
#define MIS_FAST_ISR_GPIO0_A_get_int_15(data)                                        ((0x00010000&(data))>>16)
#define MIS_FAST_ISR_GPIO0_A_int_14_shift                                            (15)
#define MIS_FAST_ISR_GPIO0_A_int_14_mask                                             (0x00008000)
#define MIS_FAST_ISR_GPIO0_A_int_14(data)                                            (0x00008000&((data)<<15))
#define MIS_FAST_ISR_GPIO0_A_int_14_src(data)                                        ((0x00008000&(data))>>15)
#define MIS_FAST_ISR_GPIO0_A_get_int_14(data)                                        ((0x00008000&(data))>>15)
#define MIS_FAST_ISR_GPIO0_A_int_13_shift                                            (14)
#define MIS_FAST_ISR_GPIO0_A_int_13_mask                                             (0x00004000)
#define MIS_FAST_ISR_GPIO0_A_int_13(data)                                            (0x00004000&((data)<<14))
#define MIS_FAST_ISR_GPIO0_A_int_13_src(data)                                        ((0x00004000&(data))>>14)
#define MIS_FAST_ISR_GPIO0_A_get_int_13(data)                                        ((0x00004000&(data))>>14)
#define MIS_FAST_ISR_GPIO0_A_int_12_shift                                            (13)
#define MIS_FAST_ISR_GPIO0_A_int_12_mask                                             (0x00002000)
#define MIS_FAST_ISR_GPIO0_A_int_12(data)                                            (0x00002000&((data)<<13))
#define MIS_FAST_ISR_GPIO0_A_int_12_src(data)                                        ((0x00002000&(data))>>13)
#define MIS_FAST_ISR_GPIO0_A_get_int_12(data)                                        ((0x00002000&(data))>>13)
#define MIS_FAST_ISR_GPIO0_A_int_11_shift                                            (12)
#define MIS_FAST_ISR_GPIO0_A_int_11_mask                                             (0x00001000)
#define MIS_FAST_ISR_GPIO0_A_int_11(data)                                            (0x00001000&((data)<<12))
#define MIS_FAST_ISR_GPIO0_A_int_11_src(data)                                        ((0x00001000&(data))>>12)
#define MIS_FAST_ISR_GPIO0_A_get_int_11(data)                                        ((0x00001000&(data))>>12)
#define MIS_FAST_ISR_GPIO0_A_int_10_shift                                            (11)
#define MIS_FAST_ISR_GPIO0_A_int_10_mask                                             (0x00000800)
#define MIS_FAST_ISR_GPIO0_A_int_10(data)                                            (0x00000800&((data)<<11))
#define MIS_FAST_ISR_GPIO0_A_int_10_src(data)                                        ((0x00000800&(data))>>11)
#define MIS_FAST_ISR_GPIO0_A_get_int_10(data)                                        ((0x00000800&(data))>>11)
#define MIS_FAST_ISR_GPIO0_A_int_9_shift                                             (10)
#define MIS_FAST_ISR_GPIO0_A_int_9_mask                                              (0x00000400)
#define MIS_FAST_ISR_GPIO0_A_int_9(data)                                             (0x00000400&((data)<<10))
#define MIS_FAST_ISR_GPIO0_A_int_9_src(data)                                         ((0x00000400&(data))>>10)
#define MIS_FAST_ISR_GPIO0_A_get_int_9(data)                                         ((0x00000400&(data))>>10)
#define MIS_FAST_ISR_GPIO0_A_int_8_shift                                             (9)
#define MIS_FAST_ISR_GPIO0_A_int_8_mask                                              (0x00000200)
#define MIS_FAST_ISR_GPIO0_A_int_8(data)                                             (0x00000200&((data)<<9))
#define MIS_FAST_ISR_GPIO0_A_int_8_src(data)                                         ((0x00000200&(data))>>9)
#define MIS_FAST_ISR_GPIO0_A_get_int_8(data)                                         ((0x00000200&(data))>>9)
#define MIS_FAST_ISR_GPIO0_A_int_7_shift                                             (8)
#define MIS_FAST_ISR_GPIO0_A_int_7_mask                                              (0x00000100)
#define MIS_FAST_ISR_GPIO0_A_int_7(data)                                             (0x00000100&((data)<<8))
#define MIS_FAST_ISR_GPIO0_A_int_7_src(data)                                         ((0x00000100&(data))>>8)
#define MIS_FAST_ISR_GPIO0_A_get_int_7(data)                                         ((0x00000100&(data))>>8)
#define MIS_FAST_ISR_GPIO0_A_int_6_shift                                             (7)
#define MIS_FAST_ISR_GPIO0_A_int_6_mask                                              (0x00000080)
#define MIS_FAST_ISR_GPIO0_A_int_6(data)                                             (0x00000080&((data)<<7))
#define MIS_FAST_ISR_GPIO0_A_int_6_src(data)                                         ((0x00000080&(data))>>7)
#define MIS_FAST_ISR_GPIO0_A_get_int_6(data)                                         ((0x00000080&(data))>>7)
#define MIS_FAST_ISR_GPIO0_A_int_5_shift                                             (6)
#define MIS_FAST_ISR_GPIO0_A_int_5_mask                                              (0x00000040)
#define MIS_FAST_ISR_GPIO0_A_int_5(data)                                             (0x00000040&((data)<<6))
#define MIS_FAST_ISR_GPIO0_A_int_5_src(data)                                         ((0x00000040&(data))>>6)
#define MIS_FAST_ISR_GPIO0_A_get_int_5(data)                                         ((0x00000040&(data))>>6)
#define MIS_FAST_ISR_GPIO0_A_int_4_shift                                             (5)
#define MIS_FAST_ISR_GPIO0_A_int_4_mask                                              (0x00000020)
#define MIS_FAST_ISR_GPIO0_A_int_4(data)                                             (0x00000020&((data)<<5))
#define MIS_FAST_ISR_GPIO0_A_int_4_src(data)                                         ((0x00000020&(data))>>5)
#define MIS_FAST_ISR_GPIO0_A_get_int_4(data)                                         ((0x00000020&(data))>>5)
#define MIS_FAST_ISR_GPIO0_A_int_3_shift                                             (4)
#define MIS_FAST_ISR_GPIO0_A_int_3_mask                                              (0x00000010)
#define MIS_FAST_ISR_GPIO0_A_int_3(data)                                             (0x00000010&((data)<<4))
#define MIS_FAST_ISR_GPIO0_A_int_3_src(data)                                         ((0x00000010&(data))>>4)
#define MIS_FAST_ISR_GPIO0_A_get_int_3(data)                                         ((0x00000010&(data))>>4)
#define MIS_FAST_ISR_GPIO0_A_int_2_shift                                             (3)
#define MIS_FAST_ISR_GPIO0_A_int_2_mask                                              (0x00000008)
#define MIS_FAST_ISR_GPIO0_A_int_2(data)                                             (0x00000008&((data)<<3))
#define MIS_FAST_ISR_GPIO0_A_int_2_src(data)                                         ((0x00000008&(data))>>3)
#define MIS_FAST_ISR_GPIO0_A_get_int_2(data)                                         ((0x00000008&(data))>>3)
#define MIS_FAST_ISR_GPIO0_A_int_1_shift                                             (2)
#define MIS_FAST_ISR_GPIO0_A_int_1_mask                                              (0x00000004)
#define MIS_FAST_ISR_GPIO0_A_int_1(data)                                             (0x00000004&((data)<<2))
#define MIS_FAST_ISR_GPIO0_A_int_1_src(data)                                         ((0x00000004&(data))>>2)
#define MIS_FAST_ISR_GPIO0_A_get_int_1(data)                                         ((0x00000004&(data))>>2)
#define MIS_FAST_ISR_GPIO0_A_int_0_shift                                             (1)
#define MIS_FAST_ISR_GPIO0_A_int_0_mask                                              (0x00000002)
#define MIS_FAST_ISR_GPIO0_A_int_0(data)                                             (0x00000002&((data)<<1))
#define MIS_FAST_ISR_GPIO0_A_int_0_src(data)                                         ((0x00000002&(data))>>1)
#define MIS_FAST_ISR_GPIO0_A_get_int_0(data)                                         ((0x00000002&(data))>>1)
#define MIS_FAST_ISR_GPIO0_A_write_data_shift                                        (0)
#define MIS_FAST_ISR_GPIO0_A_write_data_mask                                         (0x00000001)
#define MIS_FAST_ISR_GPIO0_A_write_data(data)                                        (0x00000001&((data)<<0))
#define MIS_FAST_ISR_GPIO0_A_write_data_src(data)                                    ((0x00000001&(data))>>0)
#define MIS_FAST_ISR_GPIO0_A_get_write_data(data)                                    ((0x00000001&(data))>>0)


#define MIS_FAST_ISR_GPIO1_A                                                         0x9801B074
#define MIS_FAST_ISR_GPIO1_A_reg_addr                                                "0x9801B074"
#define MIS_FAST_ISR_GPIO1_A_reg                                                     0x9801B074
#define set_MIS_FAST_ISR_GPIO1_A_reg(data)   (*((volatile unsigned int*) MIS_FAST_ISR_GPIO1_A_reg)=data)
#define get_MIS_FAST_ISR_GPIO1_A_reg   (*((volatile unsigned int*) MIS_FAST_ISR_GPIO1_A_reg))
#define MIS_FAST_ISR_GPIO1_A_inst_adr                                                "0x001D"
#define MIS_FAST_ISR_GPIO1_A_inst                                                    0x001D
#define MIS_FAST_ISR_GPIO1_A_int_61_shift                                            (31)
#define MIS_FAST_ISR_GPIO1_A_int_61_mask                                             (0x80000000)
#define MIS_FAST_ISR_GPIO1_A_int_61(data)                                            (0x80000000&((data)<<31))
#define MIS_FAST_ISR_GPIO1_A_int_61_src(data)                                        ((0x80000000&(data))>>31)
#define MIS_FAST_ISR_GPIO1_A_get_int_61(data)                                        ((0x80000000&(data))>>31)
#define MIS_FAST_ISR_GPIO1_A_int_60_shift                                            (30)
#define MIS_FAST_ISR_GPIO1_A_int_60_mask                                             (0x40000000)
#define MIS_FAST_ISR_GPIO1_A_int_60(data)                                            (0x40000000&((data)<<30))
#define MIS_FAST_ISR_GPIO1_A_int_60_src(data)                                        ((0x40000000&(data))>>30)
#define MIS_FAST_ISR_GPIO1_A_get_int_60(data)                                        ((0x40000000&(data))>>30)
#define MIS_FAST_ISR_GPIO1_A_int_59_shift                                            (29)
#define MIS_FAST_ISR_GPIO1_A_int_59_mask                                             (0x20000000)
#define MIS_FAST_ISR_GPIO1_A_int_59(data)                                            (0x20000000&((data)<<29))
#define MIS_FAST_ISR_GPIO1_A_int_59_src(data)                                        ((0x20000000&(data))>>29)
#define MIS_FAST_ISR_GPIO1_A_get_int_59(data)                                        ((0x20000000&(data))>>29)
#define MIS_FAST_ISR_GPIO1_A_int_58_shift                                            (28)
#define MIS_FAST_ISR_GPIO1_A_int_58_mask                                             (0x10000000)
#define MIS_FAST_ISR_GPIO1_A_int_58(data)                                            (0x10000000&((data)<<28))
#define MIS_FAST_ISR_GPIO1_A_int_58_src(data)                                        ((0x10000000&(data))>>28)
#define MIS_FAST_ISR_GPIO1_A_get_int_58(data)                                        ((0x10000000&(data))>>28)
#define MIS_FAST_ISR_GPIO1_A_int_57_shift                                            (27)
#define MIS_FAST_ISR_GPIO1_A_int_57_mask                                             (0x08000000)
#define MIS_FAST_ISR_GPIO1_A_int_57(data)                                            (0x08000000&((data)<<27))
#define MIS_FAST_ISR_GPIO1_A_int_57_src(data)                                        ((0x08000000&(data))>>27)
#define MIS_FAST_ISR_GPIO1_A_get_int_57(data)                                        ((0x08000000&(data))>>27)
#define MIS_FAST_ISR_GPIO1_A_int_56_shift                                            (26)
#define MIS_FAST_ISR_GPIO1_A_int_56_mask                                             (0x04000000)
#define MIS_FAST_ISR_GPIO1_A_int_56(data)                                            (0x04000000&((data)<<26))
#define MIS_FAST_ISR_GPIO1_A_int_56_src(data)                                        ((0x04000000&(data))>>26)
#define MIS_FAST_ISR_GPIO1_A_get_int_56(data)                                        ((0x04000000&(data))>>26)
#define MIS_FAST_ISR_GPIO1_A_int_55_shift                                            (25)
#define MIS_FAST_ISR_GPIO1_A_int_55_mask                                             (0x02000000)
#define MIS_FAST_ISR_GPIO1_A_int_55(data)                                            (0x02000000&((data)<<25))
#define MIS_FAST_ISR_GPIO1_A_int_55_src(data)                                        ((0x02000000&(data))>>25)
#define MIS_FAST_ISR_GPIO1_A_get_int_55(data)                                        ((0x02000000&(data))>>25)
#define MIS_FAST_ISR_GPIO1_A_int_54_shift                                            (24)
#define MIS_FAST_ISR_GPIO1_A_int_54_mask                                             (0x01000000)
#define MIS_FAST_ISR_GPIO1_A_int_54(data)                                            (0x01000000&((data)<<24))
#define MIS_FAST_ISR_GPIO1_A_int_54_src(data)                                        ((0x01000000&(data))>>24)
#define MIS_FAST_ISR_GPIO1_A_get_int_54(data)                                        ((0x01000000&(data))>>24)
#define MIS_FAST_ISR_GPIO1_A_int_53_shift                                            (23)
#define MIS_FAST_ISR_GPIO1_A_int_53_mask                                             (0x00800000)
#define MIS_FAST_ISR_GPIO1_A_int_53(data)                                            (0x00800000&((data)<<23))
#define MIS_FAST_ISR_GPIO1_A_int_53_src(data)                                        ((0x00800000&(data))>>23)
#define MIS_FAST_ISR_GPIO1_A_get_int_53(data)                                        ((0x00800000&(data))>>23)
#define MIS_FAST_ISR_GPIO1_A_int_52_shift                                            (22)
#define MIS_FAST_ISR_GPIO1_A_int_52_mask                                             (0x00400000)
#define MIS_FAST_ISR_GPIO1_A_int_52(data)                                            (0x00400000&((data)<<22))
#define MIS_FAST_ISR_GPIO1_A_int_52_src(data)                                        ((0x00400000&(data))>>22)
#define MIS_FAST_ISR_GPIO1_A_get_int_52(data)                                        ((0x00400000&(data))>>22)
#define MIS_FAST_ISR_GPIO1_A_int_51_shift                                            (21)
#define MIS_FAST_ISR_GPIO1_A_int_51_mask                                             (0x00200000)
#define MIS_FAST_ISR_GPIO1_A_int_51(data)                                            (0x00200000&((data)<<21))
#define MIS_FAST_ISR_GPIO1_A_int_51_src(data)                                        ((0x00200000&(data))>>21)
#define MIS_FAST_ISR_GPIO1_A_get_int_51(data)                                        ((0x00200000&(data))>>21)
#define MIS_FAST_ISR_GPIO1_A_int_50_shift                                            (20)
#define MIS_FAST_ISR_GPIO1_A_int_50_mask                                             (0x00100000)
#define MIS_FAST_ISR_GPIO1_A_int_50(data)                                            (0x00100000&((data)<<20))
#define MIS_FAST_ISR_GPIO1_A_int_50_src(data)                                        ((0x00100000&(data))>>20)
#define MIS_FAST_ISR_GPIO1_A_get_int_50(data)                                        ((0x00100000&(data))>>20)
#define MIS_FAST_ISR_GPIO1_A_int_49_shift                                            (19)
#define MIS_FAST_ISR_GPIO1_A_int_49_mask                                             (0x00080000)
#define MIS_FAST_ISR_GPIO1_A_int_49(data)                                            (0x00080000&((data)<<19))
#define MIS_FAST_ISR_GPIO1_A_int_49_src(data)                                        ((0x00080000&(data))>>19)
#define MIS_FAST_ISR_GPIO1_A_get_int_49(data)                                        ((0x00080000&(data))>>19)
#define MIS_FAST_ISR_GPIO1_A_int_48_shift                                            (18)
#define MIS_FAST_ISR_GPIO1_A_int_48_mask                                             (0x00040000)
#define MIS_FAST_ISR_GPIO1_A_int_48(data)                                            (0x00040000&((data)<<18))
#define MIS_FAST_ISR_GPIO1_A_int_48_src(data)                                        ((0x00040000&(data))>>18)
#define MIS_FAST_ISR_GPIO1_A_get_int_48(data)                                        ((0x00040000&(data))>>18)
#define MIS_FAST_ISR_GPIO1_A_int_47_shift                                            (17)
#define MIS_FAST_ISR_GPIO1_A_int_47_mask                                             (0x00020000)
#define MIS_FAST_ISR_GPIO1_A_int_47(data)                                            (0x00020000&((data)<<17))
#define MIS_FAST_ISR_GPIO1_A_int_47_src(data)                                        ((0x00020000&(data))>>17)
#define MIS_FAST_ISR_GPIO1_A_get_int_47(data)                                        ((0x00020000&(data))>>17)
#define MIS_FAST_ISR_GPIO1_A_int_46_shift                                            (16)
#define MIS_FAST_ISR_GPIO1_A_int_46_mask                                             (0x00010000)
#define MIS_FAST_ISR_GPIO1_A_int_46(data)                                            (0x00010000&((data)<<16))
#define MIS_FAST_ISR_GPIO1_A_int_46_src(data)                                        ((0x00010000&(data))>>16)
#define MIS_FAST_ISR_GPIO1_A_get_int_46(data)                                        ((0x00010000&(data))>>16)
#define MIS_FAST_ISR_GPIO1_A_int_45_shift                                            (15)
#define MIS_FAST_ISR_GPIO1_A_int_45_mask                                             (0x00008000)
#define MIS_FAST_ISR_GPIO1_A_int_45(data)                                            (0x00008000&((data)<<15))
#define MIS_FAST_ISR_GPIO1_A_int_45_src(data)                                        ((0x00008000&(data))>>15)
#define MIS_FAST_ISR_GPIO1_A_get_int_45(data)                                        ((0x00008000&(data))>>15)
#define MIS_FAST_ISR_GPIO1_A_int_44_shift                                            (14)
#define MIS_FAST_ISR_GPIO1_A_int_44_mask                                             (0x00004000)
#define MIS_FAST_ISR_GPIO1_A_int_44(data)                                            (0x00004000&((data)<<14))
#define MIS_FAST_ISR_GPIO1_A_int_44_src(data)                                        ((0x00004000&(data))>>14)
#define MIS_FAST_ISR_GPIO1_A_get_int_44(data)                                        ((0x00004000&(data))>>14)
#define MIS_FAST_ISR_GPIO1_A_int_43_shift                                            (13)
#define MIS_FAST_ISR_GPIO1_A_int_43_mask                                             (0x00002000)
#define MIS_FAST_ISR_GPIO1_A_int_43(data)                                            (0x00002000&((data)<<13))
#define MIS_FAST_ISR_GPIO1_A_int_43_src(data)                                        ((0x00002000&(data))>>13)
#define MIS_FAST_ISR_GPIO1_A_get_int_43(data)                                        ((0x00002000&(data))>>13)
#define MIS_FAST_ISR_GPIO1_A_int_42_shift                                            (12)
#define MIS_FAST_ISR_GPIO1_A_int_42_mask                                             (0x00001000)
#define MIS_FAST_ISR_GPIO1_A_int_42(data)                                            (0x00001000&((data)<<12))
#define MIS_FAST_ISR_GPIO1_A_int_42_src(data)                                        ((0x00001000&(data))>>12)
#define MIS_FAST_ISR_GPIO1_A_get_int_42(data)                                        ((0x00001000&(data))>>12)
#define MIS_FAST_ISR_GPIO1_A_int_41_shift                                            (11)
#define MIS_FAST_ISR_GPIO1_A_int_41_mask                                             (0x00000800)
#define MIS_FAST_ISR_GPIO1_A_int_41(data)                                            (0x00000800&((data)<<11))
#define MIS_FAST_ISR_GPIO1_A_int_41_src(data)                                        ((0x00000800&(data))>>11)
#define MIS_FAST_ISR_GPIO1_A_get_int_41(data)                                        ((0x00000800&(data))>>11)
#define MIS_FAST_ISR_GPIO1_A_int_40_shift                                            (10)
#define MIS_FAST_ISR_GPIO1_A_int_40_mask                                             (0x00000400)
#define MIS_FAST_ISR_GPIO1_A_int_40(data)                                            (0x00000400&((data)<<10))
#define MIS_FAST_ISR_GPIO1_A_int_40_src(data)                                        ((0x00000400&(data))>>10)
#define MIS_FAST_ISR_GPIO1_A_get_int_40(data)                                        ((0x00000400&(data))>>10)
#define MIS_FAST_ISR_GPIO1_A_int_39_shift                                            (9)
#define MIS_FAST_ISR_GPIO1_A_int_39_mask                                             (0x00000200)
#define MIS_FAST_ISR_GPIO1_A_int_39(data)                                            (0x00000200&((data)<<9))
#define MIS_FAST_ISR_GPIO1_A_int_39_src(data)                                        ((0x00000200&(data))>>9)
#define MIS_FAST_ISR_GPIO1_A_get_int_39(data)                                        ((0x00000200&(data))>>9)
#define MIS_FAST_ISR_GPIO1_A_int_38_shift                                            (8)
#define MIS_FAST_ISR_GPIO1_A_int_38_mask                                             (0x00000100)
#define MIS_FAST_ISR_GPIO1_A_int_38(data)                                            (0x00000100&((data)<<8))
#define MIS_FAST_ISR_GPIO1_A_int_38_src(data)                                        ((0x00000100&(data))>>8)
#define MIS_FAST_ISR_GPIO1_A_get_int_38(data)                                        ((0x00000100&(data))>>8)
#define MIS_FAST_ISR_GPIO1_A_int_37_shift                                            (7)
#define MIS_FAST_ISR_GPIO1_A_int_37_mask                                             (0x00000080)
#define MIS_FAST_ISR_GPIO1_A_int_37(data)                                            (0x00000080&((data)<<7))
#define MIS_FAST_ISR_GPIO1_A_int_37_src(data)                                        ((0x00000080&(data))>>7)
#define MIS_FAST_ISR_GPIO1_A_get_int_37(data)                                        ((0x00000080&(data))>>7)
#define MIS_FAST_ISR_GPIO1_A_int_36_shift                                            (6)
#define MIS_FAST_ISR_GPIO1_A_int_36_mask                                             (0x00000040)
#define MIS_FAST_ISR_GPIO1_A_int_36(data)                                            (0x00000040&((data)<<6))
#define MIS_FAST_ISR_GPIO1_A_int_36_src(data)                                        ((0x00000040&(data))>>6)
#define MIS_FAST_ISR_GPIO1_A_get_int_36(data)                                        ((0x00000040&(data))>>6)
#define MIS_FAST_ISR_GPIO1_A_int_35_shift                                            (5)
#define MIS_FAST_ISR_GPIO1_A_int_35_mask                                             (0x00000020)
#define MIS_FAST_ISR_GPIO1_A_int_35(data)                                            (0x00000020&((data)<<5))
#define MIS_FAST_ISR_GPIO1_A_int_35_src(data)                                        ((0x00000020&(data))>>5)
#define MIS_FAST_ISR_GPIO1_A_get_int_35(data)                                        ((0x00000020&(data))>>5)
#define MIS_FAST_ISR_GPIO1_A_int_34_shift                                            (4)
#define MIS_FAST_ISR_GPIO1_A_int_34_mask                                             (0x00000010)
#define MIS_FAST_ISR_GPIO1_A_int_34(data)                                            (0x00000010&((data)<<4))
#define MIS_FAST_ISR_GPIO1_A_int_34_src(data)                                        ((0x00000010&(data))>>4)
#define MIS_FAST_ISR_GPIO1_A_get_int_34(data)                                        ((0x00000010&(data))>>4)
#define MIS_FAST_ISR_GPIO1_A_int_33_shift                                            (3)
#define MIS_FAST_ISR_GPIO1_A_int_33_mask                                             (0x00000008)
#define MIS_FAST_ISR_GPIO1_A_int_33(data)                                            (0x00000008&((data)<<3))
#define MIS_FAST_ISR_GPIO1_A_int_33_src(data)                                        ((0x00000008&(data))>>3)
#define MIS_FAST_ISR_GPIO1_A_get_int_33(data)                                        ((0x00000008&(data))>>3)
#define MIS_FAST_ISR_GPIO1_A_int_32_shift                                            (2)
#define MIS_FAST_ISR_GPIO1_A_int_32_mask                                             (0x00000004)
#define MIS_FAST_ISR_GPIO1_A_int_32(data)                                            (0x00000004&((data)<<2))
#define MIS_FAST_ISR_GPIO1_A_int_32_src(data)                                        ((0x00000004&(data))>>2)
#define MIS_FAST_ISR_GPIO1_A_get_int_32(data)                                        ((0x00000004&(data))>>2)
#define MIS_FAST_ISR_GPIO1_A_int_31_shift                                            (1)
#define MIS_FAST_ISR_GPIO1_A_int_31_mask                                             (0x00000002)
#define MIS_FAST_ISR_GPIO1_A_int_31(data)                                            (0x00000002&((data)<<1))
#define MIS_FAST_ISR_GPIO1_A_int_31_src(data)                                        ((0x00000002&(data))>>1)
#define MIS_FAST_ISR_GPIO1_A_get_int_31(data)                                        ((0x00000002&(data))>>1)
#define MIS_FAST_ISR_GPIO1_A_write_data_shift                                        (0)
#define MIS_FAST_ISR_GPIO1_A_write_data_mask                                         (0x00000001)
#define MIS_FAST_ISR_GPIO1_A_write_data(data)                                        (0x00000001&((data)<<0))
#define MIS_FAST_ISR_GPIO1_A_write_data_src(data)                                    ((0x00000001&(data))>>0)
#define MIS_FAST_ISR_GPIO1_A_get_write_data(data)                                    ((0x00000001&(data))>>0)


#define MIS_FAST_ISR_GPIO2_A                                                         0x9801B0AC
#define MIS_FAST_ISR_GPIO2_A_reg_addr                                                "0x9801B0AC"
#define MIS_FAST_ISR_GPIO2_A_reg                                                     0x9801B0AC
#define set_MIS_FAST_ISR_GPIO2_A_reg(data)   (*((volatile unsigned int*) MIS_FAST_ISR_GPIO2_A_reg)=data)
#define get_MIS_FAST_ISR_GPIO2_A_reg   (*((volatile unsigned int*) MIS_FAST_ISR_GPIO2_A_reg))
#define MIS_FAST_ISR_GPIO2_A_inst_adr                                                "0x002B"
#define MIS_FAST_ISR_GPIO2_A_inst                                                    0x002B
#define MIS_FAST_ISR_GPIO2_A_int_92_shift                                            (31)
#define MIS_FAST_ISR_GPIO2_A_int_92_mask                                             (0x80000000)
#define MIS_FAST_ISR_GPIO2_A_int_92(data)                                            (0x80000000&((data)<<31))
#define MIS_FAST_ISR_GPIO2_A_int_92_src(data)                                        ((0x80000000&(data))>>31)
#define MIS_FAST_ISR_GPIO2_A_get_int_92(data)                                        ((0x80000000&(data))>>31)
#define MIS_FAST_ISR_GPIO2_A_int_91_shift                                            (30)
#define MIS_FAST_ISR_GPIO2_A_int_91_mask                                             (0x40000000)
#define MIS_FAST_ISR_GPIO2_A_int_91(data)                                            (0x40000000&((data)<<30))
#define MIS_FAST_ISR_GPIO2_A_int_91_src(data)                                        ((0x40000000&(data))>>30)
#define MIS_FAST_ISR_GPIO2_A_get_int_91(data)                                        ((0x40000000&(data))>>30)
#define MIS_FAST_ISR_GPIO2_A_int_90_shift                                            (29)
#define MIS_FAST_ISR_GPIO2_A_int_90_mask                                             (0x20000000)
#define MIS_FAST_ISR_GPIO2_A_int_90(data)                                            (0x20000000&((data)<<29))
#define MIS_FAST_ISR_GPIO2_A_int_90_src(data)                                        ((0x20000000&(data))>>29)
#define MIS_FAST_ISR_GPIO2_A_get_int_90(data)                                        ((0x20000000&(data))>>29)
#define MIS_FAST_ISR_GPIO2_A_int_89_shift                                            (28)
#define MIS_FAST_ISR_GPIO2_A_int_89_mask                                             (0x10000000)
#define MIS_FAST_ISR_GPIO2_A_int_89(data)                                            (0x10000000&((data)<<28))
#define MIS_FAST_ISR_GPIO2_A_int_89_src(data)                                        ((0x10000000&(data))>>28)
#define MIS_FAST_ISR_GPIO2_A_get_int_89(data)                                        ((0x10000000&(data))>>28)
#define MIS_FAST_ISR_GPIO2_A_int_88_shift                                            (27)
#define MIS_FAST_ISR_GPIO2_A_int_88_mask                                             (0x08000000)
#define MIS_FAST_ISR_GPIO2_A_int_88(data)                                            (0x08000000&((data)<<27))
#define MIS_FAST_ISR_GPIO2_A_int_88_src(data)                                        ((0x08000000&(data))>>27)
#define MIS_FAST_ISR_GPIO2_A_get_int_88(data)                                        ((0x08000000&(data))>>27)
#define MIS_FAST_ISR_GPIO2_A_int_87_shift                                            (26)
#define MIS_FAST_ISR_GPIO2_A_int_87_mask                                             (0x04000000)
#define MIS_FAST_ISR_GPIO2_A_int_87(data)                                            (0x04000000&((data)<<26))
#define MIS_FAST_ISR_GPIO2_A_int_87_src(data)                                        ((0x04000000&(data))>>26)
#define MIS_FAST_ISR_GPIO2_A_get_int_87(data)                                        ((0x04000000&(data))>>26)
#define MIS_FAST_ISR_GPIO2_A_int_86_shift                                            (25)
#define MIS_FAST_ISR_GPIO2_A_int_86_mask                                             (0x02000000)
#define MIS_FAST_ISR_GPIO2_A_int_86(data)                                            (0x02000000&((data)<<25))
#define MIS_FAST_ISR_GPIO2_A_int_86_src(data)                                        ((0x02000000&(data))>>25)
#define MIS_FAST_ISR_GPIO2_A_get_int_86(data)                                        ((0x02000000&(data))>>25)
#define MIS_FAST_ISR_GPIO2_A_int_85_shift                                            (24)
#define MIS_FAST_ISR_GPIO2_A_int_85_mask                                             (0x01000000)
#define MIS_FAST_ISR_GPIO2_A_int_85(data)                                            (0x01000000&((data)<<24))
#define MIS_FAST_ISR_GPIO2_A_int_85_src(data)                                        ((0x01000000&(data))>>24)
#define MIS_FAST_ISR_GPIO2_A_get_int_85(data)                                        ((0x01000000&(data))>>24)
#define MIS_FAST_ISR_GPIO2_A_int_84_shift                                            (23)
#define MIS_FAST_ISR_GPIO2_A_int_84_mask                                             (0x00800000)
#define MIS_FAST_ISR_GPIO2_A_int_84(data)                                            (0x00800000&((data)<<23))
#define MIS_FAST_ISR_GPIO2_A_int_84_src(data)                                        ((0x00800000&(data))>>23)
#define MIS_FAST_ISR_GPIO2_A_get_int_84(data)                                        ((0x00800000&(data))>>23)
#define MIS_FAST_ISR_GPIO2_A_int_83_shift                                            (22)
#define MIS_FAST_ISR_GPIO2_A_int_83_mask                                             (0x00400000)
#define MIS_FAST_ISR_GPIO2_A_int_83(data)                                            (0x00400000&((data)<<22))
#define MIS_FAST_ISR_GPIO2_A_int_83_src(data)                                        ((0x00400000&(data))>>22)
#define MIS_FAST_ISR_GPIO2_A_get_int_83(data)                                        ((0x00400000&(data))>>22)
#define MIS_FAST_ISR_GPIO2_A_int_82_shift                                            (21)
#define MIS_FAST_ISR_GPIO2_A_int_82_mask                                             (0x00200000)
#define MIS_FAST_ISR_GPIO2_A_int_82(data)                                            (0x00200000&((data)<<21))
#define MIS_FAST_ISR_GPIO2_A_int_82_src(data)                                        ((0x00200000&(data))>>21)
#define MIS_FAST_ISR_GPIO2_A_get_int_82(data)                                        ((0x00200000&(data))>>21)
#define MIS_FAST_ISR_GPIO2_A_int_81_shift                                            (20)
#define MIS_FAST_ISR_GPIO2_A_int_81_mask                                             (0x00100000)
#define MIS_FAST_ISR_GPIO2_A_int_81(data)                                            (0x00100000&((data)<<20))
#define MIS_FAST_ISR_GPIO2_A_int_81_src(data)                                        ((0x00100000&(data))>>20)
#define MIS_FAST_ISR_GPIO2_A_get_int_81(data)                                        ((0x00100000&(data))>>20)
#define MIS_FAST_ISR_GPIO2_A_int_80_shift                                            (19)
#define MIS_FAST_ISR_GPIO2_A_int_80_mask                                             (0x00080000)
#define MIS_FAST_ISR_GPIO2_A_int_80(data)                                            (0x00080000&((data)<<19))
#define MIS_FAST_ISR_GPIO2_A_int_80_src(data)                                        ((0x00080000&(data))>>19)
#define MIS_FAST_ISR_GPIO2_A_get_int_80(data)                                        ((0x00080000&(data))>>19)
#define MIS_FAST_ISR_GPIO2_A_int_79_shift                                            (18)
#define MIS_FAST_ISR_GPIO2_A_int_79_mask                                             (0x00040000)
#define MIS_FAST_ISR_GPIO2_A_int_79(data)                                            (0x00040000&((data)<<18))
#define MIS_FAST_ISR_GPIO2_A_int_79_src(data)                                        ((0x00040000&(data))>>18)
#define MIS_FAST_ISR_GPIO2_A_get_int_79(data)                                        ((0x00040000&(data))>>18)
#define MIS_FAST_ISR_GPIO2_A_int_78_shift                                            (17)
#define MIS_FAST_ISR_GPIO2_A_int_78_mask                                             (0x00020000)
#define MIS_FAST_ISR_GPIO2_A_int_78(data)                                            (0x00020000&((data)<<17))
#define MIS_FAST_ISR_GPIO2_A_int_78_src(data)                                        ((0x00020000&(data))>>17)
#define MIS_FAST_ISR_GPIO2_A_get_int_78(data)                                        ((0x00020000&(data))>>17)
#define MIS_FAST_ISR_GPIO2_A_int_77_shift                                            (16)
#define MIS_FAST_ISR_GPIO2_A_int_77_mask                                             (0x00010000)
#define MIS_FAST_ISR_GPIO2_A_int_77(data)                                            (0x00010000&((data)<<16))
#define MIS_FAST_ISR_GPIO2_A_int_77_src(data)                                        ((0x00010000&(data))>>16)
#define MIS_FAST_ISR_GPIO2_A_get_int_77(data)                                        ((0x00010000&(data))>>16)
#define MIS_FAST_ISR_GPIO2_A_int_76_shift                                            (15)
#define MIS_FAST_ISR_GPIO2_A_int_76_mask                                             (0x00008000)
#define MIS_FAST_ISR_GPIO2_A_int_76(data)                                            (0x00008000&((data)<<15))
#define MIS_FAST_ISR_GPIO2_A_int_76_src(data)                                        ((0x00008000&(data))>>15)
#define MIS_FAST_ISR_GPIO2_A_get_int_76(data)                                        ((0x00008000&(data))>>15)
#define MIS_FAST_ISR_GPIO2_A_int_75_shift                                            (14)
#define MIS_FAST_ISR_GPIO2_A_int_75_mask                                             (0x00004000)
#define MIS_FAST_ISR_GPIO2_A_int_75(data)                                            (0x00004000&((data)<<14))
#define MIS_FAST_ISR_GPIO2_A_int_75_src(data)                                        ((0x00004000&(data))>>14)
#define MIS_FAST_ISR_GPIO2_A_get_int_75(data)                                        ((0x00004000&(data))>>14)
#define MIS_FAST_ISR_GPIO2_A_int_74_shift                                            (13)
#define MIS_FAST_ISR_GPIO2_A_int_74_mask                                             (0x00002000)
#define MIS_FAST_ISR_GPIO2_A_int_74(data)                                            (0x00002000&((data)<<13))
#define MIS_FAST_ISR_GPIO2_A_int_74_src(data)                                        ((0x00002000&(data))>>13)
#define MIS_FAST_ISR_GPIO2_A_get_int_74(data)                                        ((0x00002000&(data))>>13)
#define MIS_FAST_ISR_GPIO2_A_int_73_shift                                            (12)
#define MIS_FAST_ISR_GPIO2_A_int_73_mask                                             (0x00001000)
#define MIS_FAST_ISR_GPIO2_A_int_73(data)                                            (0x00001000&((data)<<12))
#define MIS_FAST_ISR_GPIO2_A_int_73_src(data)                                        ((0x00001000&(data))>>12)
#define MIS_FAST_ISR_GPIO2_A_get_int_73(data)                                        ((0x00001000&(data))>>12)
#define MIS_FAST_ISR_GPIO2_A_int_72_shift                                            (11)
#define MIS_FAST_ISR_GPIO2_A_int_72_mask                                             (0x00000800)
#define MIS_FAST_ISR_GPIO2_A_int_72(data)                                            (0x00000800&((data)<<11))
#define MIS_FAST_ISR_GPIO2_A_int_72_src(data)                                        ((0x00000800&(data))>>11)
#define MIS_FAST_ISR_GPIO2_A_get_int_72(data)                                        ((0x00000800&(data))>>11)
#define MIS_FAST_ISR_GPIO2_A_int_71_shift                                            (10)
#define MIS_FAST_ISR_GPIO2_A_int_71_mask                                             (0x00000400)
#define MIS_FAST_ISR_GPIO2_A_int_71(data)                                            (0x00000400&((data)<<10))
#define MIS_FAST_ISR_GPIO2_A_int_71_src(data)                                        ((0x00000400&(data))>>10)
#define MIS_FAST_ISR_GPIO2_A_get_int_71(data)                                        ((0x00000400&(data))>>10)
#define MIS_FAST_ISR_GPIO2_A_int_70_shift                                            (9)
#define MIS_FAST_ISR_GPIO2_A_int_70_mask                                             (0x00000200)
#define MIS_FAST_ISR_GPIO2_A_int_70(data)                                            (0x00000200&((data)<<9))
#define MIS_FAST_ISR_GPIO2_A_int_70_src(data)                                        ((0x00000200&(data))>>9)
#define MIS_FAST_ISR_GPIO2_A_get_int_70(data)                                        ((0x00000200&(data))>>9)
#define MIS_FAST_ISR_GPIO2_A_int_69_shift                                            (8)
#define MIS_FAST_ISR_GPIO2_A_int_69_mask                                             (0x00000100)
#define MIS_FAST_ISR_GPIO2_A_int_69(data)                                            (0x00000100&((data)<<8))
#define MIS_FAST_ISR_GPIO2_A_int_69_src(data)                                        ((0x00000100&(data))>>8)
#define MIS_FAST_ISR_GPIO2_A_get_int_69(data)                                        ((0x00000100&(data))>>8)
#define MIS_FAST_ISR_GPIO2_A_int_68_shift                                            (7)
#define MIS_FAST_ISR_GPIO2_A_int_68_mask                                             (0x00000080)
#define MIS_FAST_ISR_GPIO2_A_int_68(data)                                            (0x00000080&((data)<<7))
#define MIS_FAST_ISR_GPIO2_A_int_68_src(data)                                        ((0x00000080&(data))>>7)
#define MIS_FAST_ISR_GPIO2_A_get_int_68(data)                                        ((0x00000080&(data))>>7)
#define MIS_FAST_ISR_GPIO2_A_int_67_shift                                            (6)
#define MIS_FAST_ISR_GPIO2_A_int_67_mask                                             (0x00000040)
#define MIS_FAST_ISR_GPIO2_A_int_67(data)                                            (0x00000040&((data)<<6))
#define MIS_FAST_ISR_GPIO2_A_int_67_src(data)                                        ((0x00000040&(data))>>6)
#define MIS_FAST_ISR_GPIO2_A_get_int_67(data)                                        ((0x00000040&(data))>>6)
#define MIS_FAST_ISR_GPIO2_A_int_66_shift                                            (5)
#define MIS_FAST_ISR_GPIO2_A_int_66_mask                                             (0x00000020)
#define MIS_FAST_ISR_GPIO2_A_int_66(data)                                            (0x00000020&((data)<<5))
#define MIS_FAST_ISR_GPIO2_A_int_66_src(data)                                        ((0x00000020&(data))>>5)
#define MIS_FAST_ISR_GPIO2_A_get_int_66(data)                                        ((0x00000020&(data))>>5)
#define MIS_FAST_ISR_GPIO2_A_int_65_shift                                            (4)
#define MIS_FAST_ISR_GPIO2_A_int_65_mask                                             (0x00000010)
#define MIS_FAST_ISR_GPIO2_A_int_65(data)                                            (0x00000010&((data)<<4))
#define MIS_FAST_ISR_GPIO2_A_int_65_src(data)                                        ((0x00000010&(data))>>4)
#define MIS_FAST_ISR_GPIO2_A_get_int_65(data)                                        ((0x00000010&(data))>>4)
#define MIS_FAST_ISR_GPIO2_A_int_64_shift                                            (3)
#define MIS_FAST_ISR_GPIO2_A_int_64_mask                                             (0x00000008)
#define MIS_FAST_ISR_GPIO2_A_int_64(data)                                            (0x00000008&((data)<<3))
#define MIS_FAST_ISR_GPIO2_A_int_64_src(data)                                        ((0x00000008&(data))>>3)
#define MIS_FAST_ISR_GPIO2_A_get_int_64(data)                                        ((0x00000008&(data))>>3)
#define MIS_FAST_ISR_GPIO2_A_int_63_shift                                            (2)
#define MIS_FAST_ISR_GPIO2_A_int_63_mask                                             (0x00000004)
#define MIS_FAST_ISR_GPIO2_A_int_63(data)                                            (0x00000004&((data)<<2))
#define MIS_FAST_ISR_GPIO2_A_int_63_src(data)                                        ((0x00000004&(data))>>2)
#define MIS_FAST_ISR_GPIO2_A_get_int_63(data)                                        ((0x00000004&(data))>>2)
#define MIS_FAST_ISR_GPIO2_A_int_62_shift                                            (1)
#define MIS_FAST_ISR_GPIO2_A_int_62_mask                                             (0x00000002)
#define MIS_FAST_ISR_GPIO2_A_int_62(data)                                            (0x00000002&((data)<<1))
#define MIS_FAST_ISR_GPIO2_A_int_62_src(data)                                        ((0x00000002&(data))>>1)
#define MIS_FAST_ISR_GPIO2_A_get_int_62(data)                                        ((0x00000002&(data))>>1)
#define MIS_FAST_ISR_GPIO2_A_write_data_shift                                        (0)
#define MIS_FAST_ISR_GPIO2_A_write_data_mask                                         (0x00000001)
#define MIS_FAST_ISR_GPIO2_A_write_data(data)                                        (0x00000001&((data)<<0))
#define MIS_FAST_ISR_GPIO2_A_write_data_src(data)                                    ((0x00000001&(data))>>0)
#define MIS_FAST_ISR_GPIO2_A_get_write_data(data)                                    ((0x00000001&(data))>>0)


#define MIS_FAST_ISR_GPIO3_A                                                         0x9801B0C0
#define MIS_FAST_ISR_GPIO3_A_reg_addr                                                "0x9801B0C0"
#define MIS_FAST_ISR_GPIO3_A_reg                                                     0x9801B0C0
#define set_MIS_FAST_ISR_GPIO3_A_reg(data)   (*((volatile unsigned int*) MIS_FAST_ISR_GPIO3_A_reg)=data)
#define get_MIS_FAST_ISR_GPIO3_A_reg   (*((volatile unsigned int*) MIS_FAST_ISR_GPIO3_A_reg))
#define MIS_FAST_ISR_GPIO3_A_inst_adr                                                "0x0030"
#define MIS_FAST_ISR_GPIO3_A_inst                                                    0x0030
#define MIS_FAST_ISR_GPIO3_A_int_100_shift                                           (8)
#define MIS_FAST_ISR_GPIO3_A_int_100_mask                                            (0x00000100)
#define MIS_FAST_ISR_GPIO3_A_int_100(data)                                           (0x00000100&((data)<<8))
#define MIS_FAST_ISR_GPIO3_A_int_100_src(data)                                       ((0x00000100&(data))>>8)
#define MIS_FAST_ISR_GPIO3_A_get_int_100(data)                                       ((0x00000100&(data))>>8)
#define MIS_FAST_ISR_GPIO3_A_int_99_shift                                            (7)
#define MIS_FAST_ISR_GPIO3_A_int_99_mask                                             (0x00000080)
#define MIS_FAST_ISR_GPIO3_A_int_99(data)                                            (0x00000080&((data)<<7))
#define MIS_FAST_ISR_GPIO3_A_int_99_src(data)                                        ((0x00000080&(data))>>7)
#define MIS_FAST_ISR_GPIO3_A_get_int_99(data)                                        ((0x00000080&(data))>>7)
#define MIS_FAST_ISR_GPIO3_A_int_98_shift                                            (6)
#define MIS_FAST_ISR_GPIO3_A_int_98_mask                                             (0x00000040)
#define MIS_FAST_ISR_GPIO3_A_int_98(data)                                            (0x00000040&((data)<<6))
#define MIS_FAST_ISR_GPIO3_A_int_98_src(data)                                        ((0x00000040&(data))>>6)
#define MIS_FAST_ISR_GPIO3_A_get_int_98(data)                                        ((0x00000040&(data))>>6)
#define MIS_FAST_ISR_GPIO3_A_int_97_shift                                            (5)
#define MIS_FAST_ISR_GPIO3_A_int_97_mask                                             (0x00000020)
#define MIS_FAST_ISR_GPIO3_A_int_97(data)                                            (0x00000020&((data)<<5))
#define MIS_FAST_ISR_GPIO3_A_int_97_src(data)                                        ((0x00000020&(data))>>5)
#define MIS_FAST_ISR_GPIO3_A_get_int_97(data)                                        ((0x00000020&(data))>>5)
#define MIS_FAST_ISR_GPIO3_A_int_96_shift                                            (4)
#define MIS_FAST_ISR_GPIO3_A_int_96_mask                                             (0x00000010)
#define MIS_FAST_ISR_GPIO3_A_int_96(data)                                            (0x00000010&((data)<<4))
#define MIS_FAST_ISR_GPIO3_A_int_96_src(data)                                        ((0x00000010&(data))>>4)
#define MIS_FAST_ISR_GPIO3_A_get_int_96(data)                                        ((0x00000010&(data))>>4)
#define MIS_FAST_ISR_GPIO3_A_int_95_shift                                            (3)
#define MIS_FAST_ISR_GPIO3_A_int_95_mask                                             (0x00000008)
#define MIS_FAST_ISR_GPIO3_A_int_95(data)                                            (0x00000008&((data)<<3))
#define MIS_FAST_ISR_GPIO3_A_int_95_src(data)                                        ((0x00000008&(data))>>3)
#define MIS_FAST_ISR_GPIO3_A_get_int_95(data)                                        ((0x00000008&(data))>>3)
#define MIS_FAST_ISR_GPIO3_A_int_94_shift                                            (2)
#define MIS_FAST_ISR_GPIO3_A_int_94_mask                                             (0x00000004)
#define MIS_FAST_ISR_GPIO3_A_int_94(data)                                            (0x00000004&((data)<<2))
#define MIS_FAST_ISR_GPIO3_A_int_94_src(data)                                        ((0x00000004&(data))>>2)
#define MIS_FAST_ISR_GPIO3_A_get_int_94(data)                                        ((0x00000004&(data))>>2)
#define MIS_FAST_ISR_GPIO3_A_int_93_shift                                            (1)
#define MIS_FAST_ISR_GPIO3_A_int_93_mask                                             (0x00000002)
#define MIS_FAST_ISR_GPIO3_A_int_93(data)                                            (0x00000002&((data)<<1))
#define MIS_FAST_ISR_GPIO3_A_int_93_src(data)                                        ((0x00000002&(data))>>1)
#define MIS_FAST_ISR_GPIO3_A_get_int_93(data)                                        ((0x00000002&(data))>>1)
#define MIS_FAST_ISR_GPIO3_A_write_data_shift                                        (0)
#define MIS_FAST_ISR_GPIO3_A_write_data_mask                                         (0x00000001)
#define MIS_FAST_ISR_GPIO3_A_write_data(data)                                        (0x00000001&((data)<<0))
#define MIS_FAST_ISR_GPIO3_A_write_data_src(data)                                    ((0x00000001&(data))>>0)
#define MIS_FAST_ISR_GPIO3_A_get_write_data(data)                                    ((0x00000001&(data))>>0)


#define MIS_FAST_ISR_GPIO0_DA                                                        0x9801B078
#define MIS_FAST_ISR_GPIO0_DA_reg_addr                                               "0x9801B078"
#define MIS_FAST_ISR_GPIO0_DA_reg                                                    0x9801B078
#define set_MIS_FAST_ISR_GPIO0_DA_reg(data)   (*((volatile unsigned int*) MIS_FAST_ISR_GPIO0_DA_reg)=data)
#define get_MIS_FAST_ISR_GPIO0_DA_reg   (*((volatile unsigned int*) MIS_FAST_ISR_GPIO0_DA_reg))
#define MIS_FAST_ISR_GPIO0_DA_inst_adr                                               "0x001E"
#define MIS_FAST_ISR_GPIO0_DA_inst                                                   0x001E
#define MIS_FAST_ISR_GPIO0_DA_int_30_shift                                           (31)
#define MIS_FAST_ISR_GPIO0_DA_int_30_mask                                            (0x80000000)
#define MIS_FAST_ISR_GPIO0_DA_int_30(data)                                           (0x80000000&((data)<<31))
#define MIS_FAST_ISR_GPIO0_DA_int_30_src(data)                                       ((0x80000000&(data))>>31)
#define MIS_FAST_ISR_GPIO0_DA_get_int_30(data)                                       ((0x80000000&(data))>>31)
#define MIS_FAST_ISR_GPIO0_DA_int_29_shift                                           (30)
#define MIS_FAST_ISR_GPIO0_DA_int_29_mask                                            (0x40000000)
#define MIS_FAST_ISR_GPIO0_DA_int_29(data)                                           (0x40000000&((data)<<30))
#define MIS_FAST_ISR_GPIO0_DA_int_29_src(data)                                       ((0x40000000&(data))>>30)
#define MIS_FAST_ISR_GPIO0_DA_get_int_29(data)                                       ((0x40000000&(data))>>30)
#define MIS_FAST_ISR_GPIO0_DA_int_28_shift                                           (29)
#define MIS_FAST_ISR_GPIO0_DA_int_28_mask                                            (0x20000000)
#define MIS_FAST_ISR_GPIO0_DA_int_28(data)                                           (0x20000000&((data)<<29))
#define MIS_FAST_ISR_GPIO0_DA_int_28_src(data)                                       ((0x20000000&(data))>>29)
#define MIS_FAST_ISR_GPIO0_DA_get_int_28(data)                                       ((0x20000000&(data))>>29)
#define MIS_FAST_ISR_GPIO0_DA_int_27_shift                                           (28)
#define MIS_FAST_ISR_GPIO0_DA_int_27_mask                                            (0x10000000)
#define MIS_FAST_ISR_GPIO0_DA_int_27(data)                                           (0x10000000&((data)<<28))
#define MIS_FAST_ISR_GPIO0_DA_int_27_src(data)                                       ((0x10000000&(data))>>28)
#define MIS_FAST_ISR_GPIO0_DA_get_int_27(data)                                       ((0x10000000&(data))>>28)
#define MIS_FAST_ISR_GPIO0_DA_int_26_shift                                           (27)
#define MIS_FAST_ISR_GPIO0_DA_int_26_mask                                            (0x08000000)
#define MIS_FAST_ISR_GPIO0_DA_int_26(data)                                           (0x08000000&((data)<<27))
#define MIS_FAST_ISR_GPIO0_DA_int_26_src(data)                                       ((0x08000000&(data))>>27)
#define MIS_FAST_ISR_GPIO0_DA_get_int_26(data)                                       ((0x08000000&(data))>>27)
#define MIS_FAST_ISR_GPIO0_DA_int_25_shift                                           (26)
#define MIS_FAST_ISR_GPIO0_DA_int_25_mask                                            (0x04000000)
#define MIS_FAST_ISR_GPIO0_DA_int_25(data)                                           (0x04000000&((data)<<26))
#define MIS_FAST_ISR_GPIO0_DA_int_25_src(data)                                       ((0x04000000&(data))>>26)
#define MIS_FAST_ISR_GPIO0_DA_get_int_25(data)                                       ((0x04000000&(data))>>26)
#define MIS_FAST_ISR_GPIO0_DA_int_24_shift                                           (25)
#define MIS_FAST_ISR_GPIO0_DA_int_24_mask                                            (0x02000000)
#define MIS_FAST_ISR_GPIO0_DA_int_24(data)                                           (0x02000000&((data)<<25))
#define MIS_FAST_ISR_GPIO0_DA_int_24_src(data)                                       ((0x02000000&(data))>>25)
#define MIS_FAST_ISR_GPIO0_DA_get_int_24(data)                                       ((0x02000000&(data))>>25)
#define MIS_FAST_ISR_GPIO0_DA_int_23_shift                                           (24)
#define MIS_FAST_ISR_GPIO0_DA_int_23_mask                                            (0x01000000)
#define MIS_FAST_ISR_GPIO0_DA_int_23(data)                                           (0x01000000&((data)<<24))
#define MIS_FAST_ISR_GPIO0_DA_int_23_src(data)                                       ((0x01000000&(data))>>24)
#define MIS_FAST_ISR_GPIO0_DA_get_int_23(data)                                       ((0x01000000&(data))>>24)
#define MIS_FAST_ISR_GPIO0_DA_int_22_shift                                           (23)
#define MIS_FAST_ISR_GPIO0_DA_int_22_mask                                            (0x00800000)
#define MIS_FAST_ISR_GPIO0_DA_int_22(data)                                           (0x00800000&((data)<<23))
#define MIS_FAST_ISR_GPIO0_DA_int_22_src(data)                                       ((0x00800000&(data))>>23)
#define MIS_FAST_ISR_GPIO0_DA_get_int_22(data)                                       ((0x00800000&(data))>>23)
#define MIS_FAST_ISR_GPIO0_DA_int_21_shift                                           (22)
#define MIS_FAST_ISR_GPIO0_DA_int_21_mask                                            (0x00400000)
#define MIS_FAST_ISR_GPIO0_DA_int_21(data)                                           (0x00400000&((data)<<22))
#define MIS_FAST_ISR_GPIO0_DA_int_21_src(data)                                       ((0x00400000&(data))>>22)
#define MIS_FAST_ISR_GPIO0_DA_get_int_21(data)                                       ((0x00400000&(data))>>22)
#define MIS_FAST_ISR_GPIO0_DA_int_20_shift                                           (21)
#define MIS_FAST_ISR_GPIO0_DA_int_20_mask                                            (0x00200000)
#define MIS_FAST_ISR_GPIO0_DA_int_20(data)                                           (0x00200000&((data)<<21))
#define MIS_FAST_ISR_GPIO0_DA_int_20_src(data)                                       ((0x00200000&(data))>>21)
#define MIS_FAST_ISR_GPIO0_DA_get_int_20(data)                                       ((0x00200000&(data))>>21)
#define MIS_FAST_ISR_GPIO0_DA_int_19_shift                                           (20)
#define MIS_FAST_ISR_GPIO0_DA_int_19_mask                                            (0x00100000)
#define MIS_FAST_ISR_GPIO0_DA_int_19(data)                                           (0x00100000&((data)<<20))
#define MIS_FAST_ISR_GPIO0_DA_int_19_src(data)                                       ((0x00100000&(data))>>20)
#define MIS_FAST_ISR_GPIO0_DA_get_int_19(data)                                       ((0x00100000&(data))>>20)
#define MIS_FAST_ISR_GPIO0_DA_int_18_shift                                           (19)
#define MIS_FAST_ISR_GPIO0_DA_int_18_mask                                            (0x00080000)
#define MIS_FAST_ISR_GPIO0_DA_int_18(data)                                           (0x00080000&((data)<<19))
#define MIS_FAST_ISR_GPIO0_DA_int_18_src(data)                                       ((0x00080000&(data))>>19)
#define MIS_FAST_ISR_GPIO0_DA_get_int_18(data)                                       ((0x00080000&(data))>>19)
#define MIS_FAST_ISR_GPIO0_DA_int_17_shift                                           (18)
#define MIS_FAST_ISR_GPIO0_DA_int_17_mask                                            (0x00040000)
#define MIS_FAST_ISR_GPIO0_DA_int_17(data)                                           (0x00040000&((data)<<18))
#define MIS_FAST_ISR_GPIO0_DA_int_17_src(data)                                       ((0x00040000&(data))>>18)
#define MIS_FAST_ISR_GPIO0_DA_get_int_17(data)                                       ((0x00040000&(data))>>18)
#define MIS_FAST_ISR_GPIO0_DA_int_16_shift                                           (17)
#define MIS_FAST_ISR_GPIO0_DA_int_16_mask                                            (0x00020000)
#define MIS_FAST_ISR_GPIO0_DA_int_16(data)                                           (0x00020000&((data)<<17))
#define MIS_FAST_ISR_GPIO0_DA_int_16_src(data)                                       ((0x00020000&(data))>>17)
#define MIS_FAST_ISR_GPIO0_DA_get_int_16(data)                                       ((0x00020000&(data))>>17)
#define MIS_FAST_ISR_GPIO0_DA_int_15_shift                                           (16)
#define MIS_FAST_ISR_GPIO0_DA_int_15_mask                                            (0x00010000)
#define MIS_FAST_ISR_GPIO0_DA_int_15(data)                                           (0x00010000&((data)<<16))
#define MIS_FAST_ISR_GPIO0_DA_int_15_src(data)                                       ((0x00010000&(data))>>16)
#define MIS_FAST_ISR_GPIO0_DA_get_int_15(data)                                       ((0x00010000&(data))>>16)
#define MIS_FAST_ISR_GPIO0_DA_int_14_shift                                           (15)
#define MIS_FAST_ISR_GPIO0_DA_int_14_mask                                            (0x00008000)
#define MIS_FAST_ISR_GPIO0_DA_int_14(data)                                           (0x00008000&((data)<<15))
#define MIS_FAST_ISR_GPIO0_DA_int_14_src(data)                                       ((0x00008000&(data))>>15)
#define MIS_FAST_ISR_GPIO0_DA_get_int_14(data)                                       ((0x00008000&(data))>>15)
#define MIS_FAST_ISR_GPIO0_DA_int_13_shift                                           (14)
#define MIS_FAST_ISR_GPIO0_DA_int_13_mask                                            (0x00004000)
#define MIS_FAST_ISR_GPIO0_DA_int_13(data)                                           (0x00004000&((data)<<14))
#define MIS_FAST_ISR_GPIO0_DA_int_13_src(data)                                       ((0x00004000&(data))>>14)
#define MIS_FAST_ISR_GPIO0_DA_get_int_13(data)                                       ((0x00004000&(data))>>14)
#define MIS_FAST_ISR_GPIO0_DA_int_12_shift                                           (13)
#define MIS_FAST_ISR_GPIO0_DA_int_12_mask                                            (0x00002000)
#define MIS_FAST_ISR_GPIO0_DA_int_12(data)                                           (0x00002000&((data)<<13))
#define MIS_FAST_ISR_GPIO0_DA_int_12_src(data)                                       ((0x00002000&(data))>>13)
#define MIS_FAST_ISR_GPIO0_DA_get_int_12(data)                                       ((0x00002000&(data))>>13)
#define MIS_FAST_ISR_GPIO0_DA_int_11_shift                                           (12)
#define MIS_FAST_ISR_GPIO0_DA_int_11_mask                                            (0x00001000)
#define MIS_FAST_ISR_GPIO0_DA_int_11(data)                                           (0x00001000&((data)<<12))
#define MIS_FAST_ISR_GPIO0_DA_int_11_src(data)                                       ((0x00001000&(data))>>12)
#define MIS_FAST_ISR_GPIO0_DA_get_int_11(data)                                       ((0x00001000&(data))>>12)
#define MIS_FAST_ISR_GPIO0_DA_int_10_shift                                           (11)
#define MIS_FAST_ISR_GPIO0_DA_int_10_mask                                            (0x00000800)
#define MIS_FAST_ISR_GPIO0_DA_int_10(data)                                           (0x00000800&((data)<<11))
#define MIS_FAST_ISR_GPIO0_DA_int_10_src(data)                                       ((0x00000800&(data))>>11)
#define MIS_FAST_ISR_GPIO0_DA_get_int_10(data)                                       ((0x00000800&(data))>>11)
#define MIS_FAST_ISR_GPIO0_DA_int_9_shift                                            (10)
#define MIS_FAST_ISR_GPIO0_DA_int_9_mask                                             (0x00000400)
#define MIS_FAST_ISR_GPIO0_DA_int_9(data)                                            (0x00000400&((data)<<10))
#define MIS_FAST_ISR_GPIO0_DA_int_9_src(data)                                        ((0x00000400&(data))>>10)
#define MIS_FAST_ISR_GPIO0_DA_get_int_9(data)                                        ((0x00000400&(data))>>10)
#define MIS_FAST_ISR_GPIO0_DA_int_8_shift                                            (9)
#define MIS_FAST_ISR_GPIO0_DA_int_8_mask                                             (0x00000200)
#define MIS_FAST_ISR_GPIO0_DA_int_8(data)                                            (0x00000200&((data)<<9))
#define MIS_FAST_ISR_GPIO0_DA_int_8_src(data)                                        ((0x00000200&(data))>>9)
#define MIS_FAST_ISR_GPIO0_DA_get_int_8(data)                                        ((0x00000200&(data))>>9)
#define MIS_FAST_ISR_GPIO0_DA_int_7_shift                                            (8)
#define MIS_FAST_ISR_GPIO0_DA_int_7_mask                                             (0x00000100)
#define MIS_FAST_ISR_GPIO0_DA_int_7(data)                                            (0x00000100&((data)<<8))
#define MIS_FAST_ISR_GPIO0_DA_int_7_src(data)                                        ((0x00000100&(data))>>8)
#define MIS_FAST_ISR_GPIO0_DA_get_int_7(data)                                        ((0x00000100&(data))>>8)
#define MIS_FAST_ISR_GPIO0_DA_int_6_shift                                            (7)
#define MIS_FAST_ISR_GPIO0_DA_int_6_mask                                             (0x00000080)
#define MIS_FAST_ISR_GPIO0_DA_int_6(data)                                            (0x00000080&((data)<<7))
#define MIS_FAST_ISR_GPIO0_DA_int_6_src(data)                                        ((0x00000080&(data))>>7)
#define MIS_FAST_ISR_GPIO0_DA_get_int_6(data)                                        ((0x00000080&(data))>>7)
#define MIS_FAST_ISR_GPIO0_DA_int_5_shift                                            (6)
#define MIS_FAST_ISR_GPIO0_DA_int_5_mask                                             (0x00000040)
#define MIS_FAST_ISR_GPIO0_DA_int_5(data)                                            (0x00000040&((data)<<6))
#define MIS_FAST_ISR_GPIO0_DA_int_5_src(data)                                        ((0x00000040&(data))>>6)
#define MIS_FAST_ISR_GPIO0_DA_get_int_5(data)                                        ((0x00000040&(data))>>6)
#define MIS_FAST_ISR_GPIO0_DA_int_4_shift                                            (5)
#define MIS_FAST_ISR_GPIO0_DA_int_4_mask                                             (0x00000020)
#define MIS_FAST_ISR_GPIO0_DA_int_4(data)                                            (0x00000020&((data)<<5))
#define MIS_FAST_ISR_GPIO0_DA_int_4_src(data)                                        ((0x00000020&(data))>>5)
#define MIS_FAST_ISR_GPIO0_DA_get_int_4(data)                                        ((0x00000020&(data))>>5)
#define MIS_FAST_ISR_GPIO0_DA_int_3_shift                                            (4)
#define MIS_FAST_ISR_GPIO0_DA_int_3_mask                                             (0x00000010)
#define MIS_FAST_ISR_GPIO0_DA_int_3(data)                                            (0x00000010&((data)<<4))
#define MIS_FAST_ISR_GPIO0_DA_int_3_src(data)                                        ((0x00000010&(data))>>4)
#define MIS_FAST_ISR_GPIO0_DA_get_int_3(data)                                        ((0x00000010&(data))>>4)
#define MIS_FAST_ISR_GPIO0_DA_int_2_shift                                            (3)
#define MIS_FAST_ISR_GPIO0_DA_int_2_mask                                             (0x00000008)
#define MIS_FAST_ISR_GPIO0_DA_int_2(data)                                            (0x00000008&((data)<<3))
#define MIS_FAST_ISR_GPIO0_DA_int_2_src(data)                                        ((0x00000008&(data))>>3)
#define MIS_FAST_ISR_GPIO0_DA_get_int_2(data)                                        ((0x00000008&(data))>>3)
#define MIS_FAST_ISR_GPIO0_DA_int_1_shift                                            (2)
#define MIS_FAST_ISR_GPIO0_DA_int_1_mask                                             (0x00000004)
#define MIS_FAST_ISR_GPIO0_DA_int_1(data)                                            (0x00000004&((data)<<2))
#define MIS_FAST_ISR_GPIO0_DA_int_1_src(data)                                        ((0x00000004&(data))>>2)
#define MIS_FAST_ISR_GPIO0_DA_get_int_1(data)                                        ((0x00000004&(data))>>2)
#define MIS_FAST_ISR_GPIO0_DA_int_0_shift                                            (1)
#define MIS_FAST_ISR_GPIO0_DA_int_0_mask                                             (0x00000002)
#define MIS_FAST_ISR_GPIO0_DA_int_0(data)                                            (0x00000002&((data)<<1))
#define MIS_FAST_ISR_GPIO0_DA_int_0_src(data)                                        ((0x00000002&(data))>>1)
#define MIS_FAST_ISR_GPIO0_DA_get_int_0(data)                                        ((0x00000002&(data))>>1)
#define MIS_FAST_ISR_GPIO0_DA_write_data_shift                                       (0)
#define MIS_FAST_ISR_GPIO0_DA_write_data_mask                                        (0x00000001)
#define MIS_FAST_ISR_GPIO0_DA_write_data(data)                                       (0x00000001&((data)<<0))
#define MIS_FAST_ISR_GPIO0_DA_write_data_src(data)                                   ((0x00000001&(data))>>0)
#define MIS_FAST_ISR_GPIO0_DA_get_write_data(data)                                   ((0x00000001&(data))>>0)


#define MIS_FAST_ISR_GPIO1_DA                                                        0x9801B07C
#define MIS_FAST_ISR_GPIO1_DA_reg_addr                                               "0x9801B07C"
#define MIS_FAST_ISR_GPIO1_DA_reg                                                    0x9801B07C
#define set_MIS_FAST_ISR_GPIO1_DA_reg(data)   (*((volatile unsigned int*) MIS_FAST_ISR_GPIO1_DA_reg)=data)
#define get_MIS_FAST_ISR_GPIO1_DA_reg   (*((volatile unsigned int*) MIS_FAST_ISR_GPIO1_DA_reg))
#define MIS_FAST_ISR_GPIO1_DA_inst_adr                                               "0x001F"
#define MIS_FAST_ISR_GPIO1_DA_inst                                                   0x001F
#define MIS_FAST_ISR_GPIO1_DA_int_61_shift                                           (31)
#define MIS_FAST_ISR_GPIO1_DA_int_61_mask                                            (0x80000000)
#define MIS_FAST_ISR_GPIO1_DA_int_61(data)                                           (0x80000000&((data)<<31))
#define MIS_FAST_ISR_GPIO1_DA_int_61_src(data)                                       ((0x80000000&(data))>>31)
#define MIS_FAST_ISR_GPIO1_DA_get_int_61(data)                                       ((0x80000000&(data))>>31)
#define MIS_FAST_ISR_GPIO1_DA_int_60_shift                                           (30)
#define MIS_FAST_ISR_GPIO1_DA_int_60_mask                                            (0x40000000)
#define MIS_FAST_ISR_GPIO1_DA_int_60(data)                                           (0x40000000&((data)<<30))
#define MIS_FAST_ISR_GPIO1_DA_int_60_src(data)                                       ((0x40000000&(data))>>30)
#define MIS_FAST_ISR_GPIO1_DA_get_int_60(data)                                       ((0x40000000&(data))>>30)
#define MIS_FAST_ISR_GPIO1_DA_int_59_shift                                           (29)
#define MIS_FAST_ISR_GPIO1_DA_int_59_mask                                            (0x20000000)
#define MIS_FAST_ISR_GPIO1_DA_int_59(data)                                           (0x20000000&((data)<<29))
#define MIS_FAST_ISR_GPIO1_DA_int_59_src(data)                                       ((0x20000000&(data))>>29)
#define MIS_FAST_ISR_GPIO1_DA_get_int_59(data)                                       ((0x20000000&(data))>>29)
#define MIS_FAST_ISR_GPIO1_DA_int_58_shift                                           (28)
#define MIS_FAST_ISR_GPIO1_DA_int_58_mask                                            (0x10000000)
#define MIS_FAST_ISR_GPIO1_DA_int_58(data)                                           (0x10000000&((data)<<28))
#define MIS_FAST_ISR_GPIO1_DA_int_58_src(data)                                       ((0x10000000&(data))>>28)
#define MIS_FAST_ISR_GPIO1_DA_get_int_58(data)                                       ((0x10000000&(data))>>28)
#define MIS_FAST_ISR_GPIO1_DA_int_57_shift                                           (27)
#define MIS_FAST_ISR_GPIO1_DA_int_57_mask                                            (0x08000000)
#define MIS_FAST_ISR_GPIO1_DA_int_57(data)                                           (0x08000000&((data)<<27))
#define MIS_FAST_ISR_GPIO1_DA_int_57_src(data)                                       ((0x08000000&(data))>>27)
#define MIS_FAST_ISR_GPIO1_DA_get_int_57(data)                                       ((0x08000000&(data))>>27)
#define MIS_FAST_ISR_GPIO1_DA_int_56_shift                                           (26)
#define MIS_FAST_ISR_GPIO1_DA_int_56_mask                                            (0x04000000)
#define MIS_FAST_ISR_GPIO1_DA_int_56(data)                                           (0x04000000&((data)<<26))
#define MIS_FAST_ISR_GPIO1_DA_int_56_src(data)                                       ((0x04000000&(data))>>26)
#define MIS_FAST_ISR_GPIO1_DA_get_int_56(data)                                       ((0x04000000&(data))>>26)
#define MIS_FAST_ISR_GPIO1_DA_int_55_shift                                           (25)
#define MIS_FAST_ISR_GPIO1_DA_int_55_mask                                            (0x02000000)
#define MIS_FAST_ISR_GPIO1_DA_int_55(data)                                           (0x02000000&((data)<<25))
#define MIS_FAST_ISR_GPIO1_DA_int_55_src(data)                                       ((0x02000000&(data))>>25)
#define MIS_FAST_ISR_GPIO1_DA_get_int_55(data)                                       ((0x02000000&(data))>>25)
#define MIS_FAST_ISR_GPIO1_DA_int_54_shift                                           (24)
#define MIS_FAST_ISR_GPIO1_DA_int_54_mask                                            (0x01000000)
#define MIS_FAST_ISR_GPIO1_DA_int_54(data)                                           (0x01000000&((data)<<24))
#define MIS_FAST_ISR_GPIO1_DA_int_54_src(data)                                       ((0x01000000&(data))>>24)
#define MIS_FAST_ISR_GPIO1_DA_get_int_54(data)                                       ((0x01000000&(data))>>24)
#define MIS_FAST_ISR_GPIO1_DA_int_53_shift                                           (23)
#define MIS_FAST_ISR_GPIO1_DA_int_53_mask                                            (0x00800000)
#define MIS_FAST_ISR_GPIO1_DA_int_53(data)                                           (0x00800000&((data)<<23))
#define MIS_FAST_ISR_GPIO1_DA_int_53_src(data)                                       ((0x00800000&(data))>>23)
#define MIS_FAST_ISR_GPIO1_DA_get_int_53(data)                                       ((0x00800000&(data))>>23)
#define MIS_FAST_ISR_GPIO1_DA_int_52_shift                                           (22)
#define MIS_FAST_ISR_GPIO1_DA_int_52_mask                                            (0x00400000)
#define MIS_FAST_ISR_GPIO1_DA_int_52(data)                                           (0x00400000&((data)<<22))
#define MIS_FAST_ISR_GPIO1_DA_int_52_src(data)                                       ((0x00400000&(data))>>22)
#define MIS_FAST_ISR_GPIO1_DA_get_int_52(data)                                       ((0x00400000&(data))>>22)
#define MIS_FAST_ISR_GPIO1_DA_int_51_shift                                           (21)
#define MIS_FAST_ISR_GPIO1_DA_int_51_mask                                            (0x00200000)
#define MIS_FAST_ISR_GPIO1_DA_int_51(data)                                           (0x00200000&((data)<<21))
#define MIS_FAST_ISR_GPIO1_DA_int_51_src(data)                                       ((0x00200000&(data))>>21)
#define MIS_FAST_ISR_GPIO1_DA_get_int_51(data)                                       ((0x00200000&(data))>>21)
#define MIS_FAST_ISR_GPIO1_DA_int_50_shift                                           (20)
#define MIS_FAST_ISR_GPIO1_DA_int_50_mask                                            (0x00100000)
#define MIS_FAST_ISR_GPIO1_DA_int_50(data)                                           (0x00100000&((data)<<20))
#define MIS_FAST_ISR_GPIO1_DA_int_50_src(data)                                       ((0x00100000&(data))>>20)
#define MIS_FAST_ISR_GPIO1_DA_get_int_50(data)                                       ((0x00100000&(data))>>20)
#define MIS_FAST_ISR_GPIO1_DA_int_49_shift                                           (19)
#define MIS_FAST_ISR_GPIO1_DA_int_49_mask                                            (0x00080000)
#define MIS_FAST_ISR_GPIO1_DA_int_49(data)                                           (0x00080000&((data)<<19))
#define MIS_FAST_ISR_GPIO1_DA_int_49_src(data)                                       ((0x00080000&(data))>>19)
#define MIS_FAST_ISR_GPIO1_DA_get_int_49(data)                                       ((0x00080000&(data))>>19)
#define MIS_FAST_ISR_GPIO1_DA_int_48_shift                                           (18)
#define MIS_FAST_ISR_GPIO1_DA_int_48_mask                                            (0x00040000)
#define MIS_FAST_ISR_GPIO1_DA_int_48(data)                                           (0x00040000&((data)<<18))
#define MIS_FAST_ISR_GPIO1_DA_int_48_src(data)                                       ((0x00040000&(data))>>18)
#define MIS_FAST_ISR_GPIO1_DA_get_int_48(data)                                       ((0x00040000&(data))>>18)
#define MIS_FAST_ISR_GPIO1_DA_int_47_shift                                           (17)
#define MIS_FAST_ISR_GPIO1_DA_int_47_mask                                            (0x00020000)
#define MIS_FAST_ISR_GPIO1_DA_int_47(data)                                           (0x00020000&((data)<<17))
#define MIS_FAST_ISR_GPIO1_DA_int_47_src(data)                                       ((0x00020000&(data))>>17)
#define MIS_FAST_ISR_GPIO1_DA_get_int_47(data)                                       ((0x00020000&(data))>>17)
#define MIS_FAST_ISR_GPIO1_DA_int_46_shift                                           (16)
#define MIS_FAST_ISR_GPIO1_DA_int_46_mask                                            (0x00010000)
#define MIS_FAST_ISR_GPIO1_DA_int_46(data)                                           (0x00010000&((data)<<16))
#define MIS_FAST_ISR_GPIO1_DA_int_46_src(data)                                       ((0x00010000&(data))>>16)
#define MIS_FAST_ISR_GPIO1_DA_get_int_46(data)                                       ((0x00010000&(data))>>16)
#define MIS_FAST_ISR_GPIO1_DA_int_45_shift                                           (15)
#define MIS_FAST_ISR_GPIO1_DA_int_45_mask                                            (0x00008000)
#define MIS_FAST_ISR_GPIO1_DA_int_45(data)                                           (0x00008000&((data)<<15))
#define MIS_FAST_ISR_GPIO1_DA_int_45_src(data)                                       ((0x00008000&(data))>>15)
#define MIS_FAST_ISR_GPIO1_DA_get_int_45(data)                                       ((0x00008000&(data))>>15)
#define MIS_FAST_ISR_GPIO1_DA_int_44_shift                                           (14)
#define MIS_FAST_ISR_GPIO1_DA_int_44_mask                                            (0x00004000)
#define MIS_FAST_ISR_GPIO1_DA_int_44(data)                                           (0x00004000&((data)<<14))
#define MIS_FAST_ISR_GPIO1_DA_int_44_src(data)                                       ((0x00004000&(data))>>14)
#define MIS_FAST_ISR_GPIO1_DA_get_int_44(data)                                       ((0x00004000&(data))>>14)
#define MIS_FAST_ISR_GPIO1_DA_int_43_shift                                           (13)
#define MIS_FAST_ISR_GPIO1_DA_int_43_mask                                            (0x00002000)
#define MIS_FAST_ISR_GPIO1_DA_int_43(data)                                           (0x00002000&((data)<<13))
#define MIS_FAST_ISR_GPIO1_DA_int_43_src(data)                                       ((0x00002000&(data))>>13)
#define MIS_FAST_ISR_GPIO1_DA_get_int_43(data)                                       ((0x00002000&(data))>>13)
#define MIS_FAST_ISR_GPIO1_DA_int_42_shift                                           (12)
#define MIS_FAST_ISR_GPIO1_DA_int_42_mask                                            (0x00001000)
#define MIS_FAST_ISR_GPIO1_DA_int_42(data)                                           (0x00001000&((data)<<12))
#define MIS_FAST_ISR_GPIO1_DA_int_42_src(data)                                       ((0x00001000&(data))>>12)
#define MIS_FAST_ISR_GPIO1_DA_get_int_42(data)                                       ((0x00001000&(data))>>12)
#define MIS_FAST_ISR_GPIO1_DA_int_41_shift                                           (11)
#define MIS_FAST_ISR_GPIO1_DA_int_41_mask                                            (0x00000800)
#define MIS_FAST_ISR_GPIO1_DA_int_41(data)                                           (0x00000800&((data)<<11))
#define MIS_FAST_ISR_GPIO1_DA_int_41_src(data)                                       ((0x00000800&(data))>>11)
#define MIS_FAST_ISR_GPIO1_DA_get_int_41(data)                                       ((0x00000800&(data))>>11)
#define MIS_FAST_ISR_GPIO1_DA_int_40_shift                                           (10)
#define MIS_FAST_ISR_GPIO1_DA_int_40_mask                                            (0x00000400)
#define MIS_FAST_ISR_GPIO1_DA_int_40(data)                                           (0x00000400&((data)<<10))
#define MIS_FAST_ISR_GPIO1_DA_int_40_src(data)                                       ((0x00000400&(data))>>10)
#define MIS_FAST_ISR_GPIO1_DA_get_int_40(data)                                       ((0x00000400&(data))>>10)
#define MIS_FAST_ISR_GPIO1_DA_int_39_shift                                           (9)
#define MIS_FAST_ISR_GPIO1_DA_int_39_mask                                            (0x00000200)
#define MIS_FAST_ISR_GPIO1_DA_int_39(data)                                           (0x00000200&((data)<<9))
#define MIS_FAST_ISR_GPIO1_DA_int_39_src(data)                                       ((0x00000200&(data))>>9)
#define MIS_FAST_ISR_GPIO1_DA_get_int_39(data)                                       ((0x00000200&(data))>>9)
#define MIS_FAST_ISR_GPIO1_DA_int_38_shift                                           (8)
#define MIS_FAST_ISR_GPIO1_DA_int_38_mask                                            (0x00000100)
#define MIS_FAST_ISR_GPIO1_DA_int_38(data)                                           (0x00000100&((data)<<8))
#define MIS_FAST_ISR_GPIO1_DA_int_38_src(data)                                       ((0x00000100&(data))>>8)
#define MIS_FAST_ISR_GPIO1_DA_get_int_38(data)                                       ((0x00000100&(data))>>8)
#define MIS_FAST_ISR_GPIO1_DA_int_37_shift                                           (7)
#define MIS_FAST_ISR_GPIO1_DA_int_37_mask                                            (0x00000080)
#define MIS_FAST_ISR_GPIO1_DA_int_37(data)                                           (0x00000080&((data)<<7))
#define MIS_FAST_ISR_GPIO1_DA_int_37_src(data)                                       ((0x00000080&(data))>>7)
#define MIS_FAST_ISR_GPIO1_DA_get_int_37(data)                                       ((0x00000080&(data))>>7)
#define MIS_FAST_ISR_GPIO1_DA_int_36_shift                                           (6)
#define MIS_FAST_ISR_GPIO1_DA_int_36_mask                                            (0x00000040)
#define MIS_FAST_ISR_GPIO1_DA_int_36(data)                                           (0x00000040&((data)<<6))
#define MIS_FAST_ISR_GPIO1_DA_int_36_src(data)                                       ((0x00000040&(data))>>6)
#define MIS_FAST_ISR_GPIO1_DA_get_int_36(data)                                       ((0x00000040&(data))>>6)
#define MIS_FAST_ISR_GPIO1_DA_int_35_shift                                           (5)
#define MIS_FAST_ISR_GPIO1_DA_int_35_mask                                            (0x00000020)
#define MIS_FAST_ISR_GPIO1_DA_int_35(data)                                           (0x00000020&((data)<<5))
#define MIS_FAST_ISR_GPIO1_DA_int_35_src(data)                                       ((0x00000020&(data))>>5)
#define MIS_FAST_ISR_GPIO1_DA_get_int_35(data)                                       ((0x00000020&(data))>>5)
#define MIS_FAST_ISR_GPIO1_DA_int_34_shift                                           (4)
#define MIS_FAST_ISR_GPIO1_DA_int_34_mask                                            (0x00000010)
#define MIS_FAST_ISR_GPIO1_DA_int_34(data)                                           (0x00000010&((data)<<4))
#define MIS_FAST_ISR_GPIO1_DA_int_34_src(data)                                       ((0x00000010&(data))>>4)
#define MIS_FAST_ISR_GPIO1_DA_get_int_34(data)                                       ((0x00000010&(data))>>4)
#define MIS_FAST_ISR_GPIO1_DA_int_33_shift                                           (3)
#define MIS_FAST_ISR_GPIO1_DA_int_33_mask                                            (0x00000008)
#define MIS_FAST_ISR_GPIO1_DA_int_33(data)                                           (0x00000008&((data)<<3))
#define MIS_FAST_ISR_GPIO1_DA_int_33_src(data)                                       ((0x00000008&(data))>>3)
#define MIS_FAST_ISR_GPIO1_DA_get_int_33(data)                                       ((0x00000008&(data))>>3)
#define MIS_FAST_ISR_GPIO1_DA_int_32_shift                                           (2)
#define MIS_FAST_ISR_GPIO1_DA_int_32_mask                                            (0x00000004)
#define MIS_FAST_ISR_GPIO1_DA_int_32(data)                                           (0x00000004&((data)<<2))
#define MIS_FAST_ISR_GPIO1_DA_int_32_src(data)                                       ((0x00000004&(data))>>2)
#define MIS_FAST_ISR_GPIO1_DA_get_int_32(data)                                       ((0x00000004&(data))>>2)
#define MIS_FAST_ISR_GPIO1_DA_int_31_shift                                           (1)
#define MIS_FAST_ISR_GPIO1_DA_int_31_mask                                            (0x00000002)
#define MIS_FAST_ISR_GPIO1_DA_int_31(data)                                           (0x00000002&((data)<<1))
#define MIS_FAST_ISR_GPIO1_DA_int_31_src(data)                                       ((0x00000002&(data))>>1)
#define MIS_FAST_ISR_GPIO1_DA_get_int_31(data)                                       ((0x00000002&(data))>>1)
#define MIS_FAST_ISR_GPIO1_DA_write_data_shift                                       (0)
#define MIS_FAST_ISR_GPIO1_DA_write_data_mask                                        (0x00000001)
#define MIS_FAST_ISR_GPIO1_DA_write_data(data)                                       (0x00000001&((data)<<0))
#define MIS_FAST_ISR_GPIO1_DA_write_data_src(data)                                   ((0x00000001&(data))>>0)
#define MIS_FAST_ISR_GPIO1_DA_get_write_data(data)                                   ((0x00000001&(data))>>0)


#define MIS_FAST_ISR_GPIO2_DA                                                        0x9801B0B0
#define MIS_FAST_ISR_GPIO2_DA_reg_addr                                               "0x9801B0B0"
#define MIS_FAST_ISR_GPIO2_DA_reg                                                    0x9801B0B0
#define set_MIS_FAST_ISR_GPIO2_DA_reg(data)   (*((volatile unsigned int*) MIS_FAST_ISR_GPIO2_DA_reg)=data)
#define get_MIS_FAST_ISR_GPIO2_DA_reg   (*((volatile unsigned int*) MIS_FAST_ISR_GPIO2_DA_reg))
#define MIS_FAST_ISR_GPIO2_DA_inst_adr                                               "0x002C"
#define MIS_FAST_ISR_GPIO2_DA_inst                                                   0x002C
#define MIS_FAST_ISR_GPIO2_DA_int_92_shift                                           (31)
#define MIS_FAST_ISR_GPIO2_DA_int_92_mask                                            (0x80000000)
#define MIS_FAST_ISR_GPIO2_DA_int_92(data)                                           (0x80000000&((data)<<31))
#define MIS_FAST_ISR_GPIO2_DA_int_92_src(data)                                       ((0x80000000&(data))>>31)
#define MIS_FAST_ISR_GPIO2_DA_get_int_92(data)                                       ((0x80000000&(data))>>31)
#define MIS_FAST_ISR_GPIO2_DA_int_91_shift                                           (30)
#define MIS_FAST_ISR_GPIO2_DA_int_91_mask                                            (0x40000000)
#define MIS_FAST_ISR_GPIO2_DA_int_91(data)                                           (0x40000000&((data)<<30))
#define MIS_FAST_ISR_GPIO2_DA_int_91_src(data)                                       ((0x40000000&(data))>>30)
#define MIS_FAST_ISR_GPIO2_DA_get_int_91(data)                                       ((0x40000000&(data))>>30)
#define MIS_FAST_ISR_GPIO2_DA_int_90_shift                                           (29)
#define MIS_FAST_ISR_GPIO2_DA_int_90_mask                                            (0x20000000)
#define MIS_FAST_ISR_GPIO2_DA_int_90(data)                                           (0x20000000&((data)<<29))
#define MIS_FAST_ISR_GPIO2_DA_int_90_src(data)                                       ((0x20000000&(data))>>29)
#define MIS_FAST_ISR_GPIO2_DA_get_int_90(data)                                       ((0x20000000&(data))>>29)
#define MIS_FAST_ISR_GPIO2_DA_int_89_shift                                           (28)
#define MIS_FAST_ISR_GPIO2_DA_int_89_mask                                            (0x10000000)
#define MIS_FAST_ISR_GPIO2_DA_int_89(data)                                           (0x10000000&((data)<<28))
#define MIS_FAST_ISR_GPIO2_DA_int_89_src(data)                                       ((0x10000000&(data))>>28)
#define MIS_FAST_ISR_GPIO2_DA_get_int_89(data)                                       ((0x10000000&(data))>>28)
#define MIS_FAST_ISR_GPIO2_DA_int_88_shift                                           (27)
#define MIS_FAST_ISR_GPIO2_DA_int_88_mask                                            (0x08000000)
#define MIS_FAST_ISR_GPIO2_DA_int_88(data)                                           (0x08000000&((data)<<27))
#define MIS_FAST_ISR_GPIO2_DA_int_88_src(data)                                       ((0x08000000&(data))>>27)
#define MIS_FAST_ISR_GPIO2_DA_get_int_88(data)                                       ((0x08000000&(data))>>27)
#define MIS_FAST_ISR_GPIO2_DA_int_87_shift                                           (26)
#define MIS_FAST_ISR_GPIO2_DA_int_87_mask                                            (0x04000000)
#define MIS_FAST_ISR_GPIO2_DA_int_87(data)                                           (0x04000000&((data)<<26))
#define MIS_FAST_ISR_GPIO2_DA_int_87_src(data)                                       ((0x04000000&(data))>>26)
#define MIS_FAST_ISR_GPIO2_DA_get_int_87(data)                                       ((0x04000000&(data))>>26)
#define MIS_FAST_ISR_GPIO2_DA_int_86_shift                                           (25)
#define MIS_FAST_ISR_GPIO2_DA_int_86_mask                                            (0x02000000)
#define MIS_FAST_ISR_GPIO2_DA_int_86(data)                                           (0x02000000&((data)<<25))
#define MIS_FAST_ISR_GPIO2_DA_int_86_src(data)                                       ((0x02000000&(data))>>25)
#define MIS_FAST_ISR_GPIO2_DA_get_int_86(data)                                       ((0x02000000&(data))>>25)
#define MIS_FAST_ISR_GPIO2_DA_int_85_shift                                           (24)
#define MIS_FAST_ISR_GPIO2_DA_int_85_mask                                            (0x01000000)
#define MIS_FAST_ISR_GPIO2_DA_int_85(data)                                           (0x01000000&((data)<<24))
#define MIS_FAST_ISR_GPIO2_DA_int_85_src(data)                                       ((0x01000000&(data))>>24)
#define MIS_FAST_ISR_GPIO2_DA_get_int_85(data)                                       ((0x01000000&(data))>>24)
#define MIS_FAST_ISR_GPIO2_DA_int_84_shift                                           (23)
#define MIS_FAST_ISR_GPIO2_DA_int_84_mask                                            (0x00800000)
#define MIS_FAST_ISR_GPIO2_DA_int_84(data)                                           (0x00800000&((data)<<23))
#define MIS_FAST_ISR_GPIO2_DA_int_84_src(data)                                       ((0x00800000&(data))>>23)
#define MIS_FAST_ISR_GPIO2_DA_get_int_84(data)                                       ((0x00800000&(data))>>23)
#define MIS_FAST_ISR_GPIO2_DA_int_83_shift                                           (22)
#define MIS_FAST_ISR_GPIO2_DA_int_83_mask                                            (0x00400000)
#define MIS_FAST_ISR_GPIO2_DA_int_83(data)                                           (0x00400000&((data)<<22))
#define MIS_FAST_ISR_GPIO2_DA_int_83_src(data)                                       ((0x00400000&(data))>>22)
#define MIS_FAST_ISR_GPIO2_DA_get_int_83(data)                                       ((0x00400000&(data))>>22)
#define MIS_FAST_ISR_GPIO2_DA_int_82_shift                                           (21)
#define MIS_FAST_ISR_GPIO2_DA_int_82_mask                                            (0x00200000)
#define MIS_FAST_ISR_GPIO2_DA_int_82(data)                                           (0x00200000&((data)<<21))
#define MIS_FAST_ISR_GPIO2_DA_int_82_src(data)                                       ((0x00200000&(data))>>21)
#define MIS_FAST_ISR_GPIO2_DA_get_int_82(data)                                       ((0x00200000&(data))>>21)
#define MIS_FAST_ISR_GPIO2_DA_int_81_shift                                           (20)
#define MIS_FAST_ISR_GPIO2_DA_int_81_mask                                            (0x00100000)
#define MIS_FAST_ISR_GPIO2_DA_int_81(data)                                           (0x00100000&((data)<<20))
#define MIS_FAST_ISR_GPIO2_DA_int_81_src(data)                                       ((0x00100000&(data))>>20)
#define MIS_FAST_ISR_GPIO2_DA_get_int_81(data)                                       ((0x00100000&(data))>>20)
#define MIS_FAST_ISR_GPIO2_DA_int_80_shift                                           (19)
#define MIS_FAST_ISR_GPIO2_DA_int_80_mask                                            (0x00080000)
#define MIS_FAST_ISR_GPIO2_DA_int_80(data)                                           (0x00080000&((data)<<19))
#define MIS_FAST_ISR_GPIO2_DA_int_80_src(data)                                       ((0x00080000&(data))>>19)
#define MIS_FAST_ISR_GPIO2_DA_get_int_80(data)                                       ((0x00080000&(data))>>19)
#define MIS_FAST_ISR_GPIO2_DA_int_79_shift                                           (18)
#define MIS_FAST_ISR_GPIO2_DA_int_79_mask                                            (0x00040000)
#define MIS_FAST_ISR_GPIO2_DA_int_79(data)                                           (0x00040000&((data)<<18))
#define MIS_FAST_ISR_GPIO2_DA_int_79_src(data)                                       ((0x00040000&(data))>>18)
#define MIS_FAST_ISR_GPIO2_DA_get_int_79(data)                                       ((0x00040000&(data))>>18)
#define MIS_FAST_ISR_GPIO2_DA_int_78_shift                                           (17)
#define MIS_FAST_ISR_GPIO2_DA_int_78_mask                                            (0x00020000)
#define MIS_FAST_ISR_GPIO2_DA_int_78(data)                                           (0x00020000&((data)<<17))
#define MIS_FAST_ISR_GPIO2_DA_int_78_src(data)                                       ((0x00020000&(data))>>17)
#define MIS_FAST_ISR_GPIO2_DA_get_int_78(data)                                       ((0x00020000&(data))>>17)
#define MIS_FAST_ISR_GPIO2_DA_int_77_shift                                           (16)
#define MIS_FAST_ISR_GPIO2_DA_int_77_mask                                            (0x00010000)
#define MIS_FAST_ISR_GPIO2_DA_int_77(data)                                           (0x00010000&((data)<<16))
#define MIS_FAST_ISR_GPIO2_DA_int_77_src(data)                                       ((0x00010000&(data))>>16)
#define MIS_FAST_ISR_GPIO2_DA_get_int_77(data)                                       ((0x00010000&(data))>>16)
#define MIS_FAST_ISR_GPIO2_DA_int_76_shift                                           (15)
#define MIS_FAST_ISR_GPIO2_DA_int_76_mask                                            (0x00008000)
#define MIS_FAST_ISR_GPIO2_DA_int_76(data)                                           (0x00008000&((data)<<15))
#define MIS_FAST_ISR_GPIO2_DA_int_76_src(data)                                       ((0x00008000&(data))>>15)
#define MIS_FAST_ISR_GPIO2_DA_get_int_76(data)                                       ((0x00008000&(data))>>15)
#define MIS_FAST_ISR_GPIO2_DA_int_75_shift                                           (14)
#define MIS_FAST_ISR_GPIO2_DA_int_75_mask                                            (0x00004000)
#define MIS_FAST_ISR_GPIO2_DA_int_75(data)                                           (0x00004000&((data)<<14))
#define MIS_FAST_ISR_GPIO2_DA_int_75_src(data)                                       ((0x00004000&(data))>>14)
#define MIS_FAST_ISR_GPIO2_DA_get_int_75(data)                                       ((0x00004000&(data))>>14)
#define MIS_FAST_ISR_GPIO2_DA_int_74_shift                                           (13)
#define MIS_FAST_ISR_GPIO2_DA_int_74_mask                                            (0x00002000)
#define MIS_FAST_ISR_GPIO2_DA_int_74(data)                                           (0x00002000&((data)<<13))
#define MIS_FAST_ISR_GPIO2_DA_int_74_src(data)                                       ((0x00002000&(data))>>13)
#define MIS_FAST_ISR_GPIO2_DA_get_int_74(data)                                       ((0x00002000&(data))>>13)
#define MIS_FAST_ISR_GPIO2_DA_int_73_shift                                           (12)
#define MIS_FAST_ISR_GPIO2_DA_int_73_mask                                            (0x00001000)
#define MIS_FAST_ISR_GPIO2_DA_int_73(data)                                           (0x00001000&((data)<<12))
#define MIS_FAST_ISR_GPIO2_DA_int_73_src(data)                                       ((0x00001000&(data))>>12)
#define MIS_FAST_ISR_GPIO2_DA_get_int_73(data)                                       ((0x00001000&(data))>>12)
#define MIS_FAST_ISR_GPIO2_DA_int_72_shift                                           (11)
#define MIS_FAST_ISR_GPIO2_DA_int_72_mask                                            (0x00000800)
#define MIS_FAST_ISR_GPIO2_DA_int_72(data)                                           (0x00000800&((data)<<11))
#define MIS_FAST_ISR_GPIO2_DA_int_72_src(data)                                       ((0x00000800&(data))>>11)
#define MIS_FAST_ISR_GPIO2_DA_get_int_72(data)                                       ((0x00000800&(data))>>11)
#define MIS_FAST_ISR_GPIO2_DA_int_71_shift                                           (10)
#define MIS_FAST_ISR_GPIO2_DA_int_71_mask                                            (0x00000400)
#define MIS_FAST_ISR_GPIO2_DA_int_71(data)                                           (0x00000400&((data)<<10))
#define MIS_FAST_ISR_GPIO2_DA_int_71_src(data)                                       ((0x00000400&(data))>>10)
#define MIS_FAST_ISR_GPIO2_DA_get_int_71(data)                                       ((0x00000400&(data))>>10)
#define MIS_FAST_ISR_GPIO2_DA_int_70_shift                                           (9)
#define MIS_FAST_ISR_GPIO2_DA_int_70_mask                                            (0x00000200)
#define MIS_FAST_ISR_GPIO2_DA_int_70(data)                                           (0x00000200&((data)<<9))
#define MIS_FAST_ISR_GPIO2_DA_int_70_src(data)                                       ((0x00000200&(data))>>9)
#define MIS_FAST_ISR_GPIO2_DA_get_int_70(data)                                       ((0x00000200&(data))>>9)
#define MIS_FAST_ISR_GPIO2_DA_int_69_shift                                           (8)
#define MIS_FAST_ISR_GPIO2_DA_int_69_mask                                            (0x00000100)
#define MIS_FAST_ISR_GPIO2_DA_int_69(data)                                           (0x00000100&((data)<<8))
#define MIS_FAST_ISR_GPIO2_DA_int_69_src(data)                                       ((0x00000100&(data))>>8)
#define MIS_FAST_ISR_GPIO2_DA_get_int_69(data)                                       ((0x00000100&(data))>>8)
#define MIS_FAST_ISR_GPIO2_DA_int_68_shift                                           (7)
#define MIS_FAST_ISR_GPIO2_DA_int_68_mask                                            (0x00000080)
#define MIS_FAST_ISR_GPIO2_DA_int_68(data)                                           (0x00000080&((data)<<7))
#define MIS_FAST_ISR_GPIO2_DA_int_68_src(data)                                       ((0x00000080&(data))>>7)
#define MIS_FAST_ISR_GPIO2_DA_get_int_68(data)                                       ((0x00000080&(data))>>7)
#define MIS_FAST_ISR_GPIO2_DA_int_67_shift                                           (6)
#define MIS_FAST_ISR_GPIO2_DA_int_67_mask                                            (0x00000040)
#define MIS_FAST_ISR_GPIO2_DA_int_67(data)                                           (0x00000040&((data)<<6))
#define MIS_FAST_ISR_GPIO2_DA_int_67_src(data)                                       ((0x00000040&(data))>>6)
#define MIS_FAST_ISR_GPIO2_DA_get_int_67(data)                                       ((0x00000040&(data))>>6)
#define MIS_FAST_ISR_GPIO2_DA_int_66_shift                                           (5)
#define MIS_FAST_ISR_GPIO2_DA_int_66_mask                                            (0x00000020)
#define MIS_FAST_ISR_GPIO2_DA_int_66(data)                                           (0x00000020&((data)<<5))
#define MIS_FAST_ISR_GPIO2_DA_int_66_src(data)                                       ((0x00000020&(data))>>5)
#define MIS_FAST_ISR_GPIO2_DA_get_int_66(data)                                       ((0x00000020&(data))>>5)
#define MIS_FAST_ISR_GPIO2_DA_int_65_shift                                           (4)
#define MIS_FAST_ISR_GPIO2_DA_int_65_mask                                            (0x00000010)
#define MIS_FAST_ISR_GPIO2_DA_int_65(data)                                           (0x00000010&((data)<<4))
#define MIS_FAST_ISR_GPIO2_DA_int_65_src(data)                                       ((0x00000010&(data))>>4)
#define MIS_FAST_ISR_GPIO2_DA_get_int_65(data)                                       ((0x00000010&(data))>>4)
#define MIS_FAST_ISR_GPIO2_DA_int_64_shift                                           (3)
#define MIS_FAST_ISR_GPIO2_DA_int_64_mask                                            (0x00000008)
#define MIS_FAST_ISR_GPIO2_DA_int_64(data)                                           (0x00000008&((data)<<3))
#define MIS_FAST_ISR_GPIO2_DA_int_64_src(data)                                       ((0x00000008&(data))>>3)
#define MIS_FAST_ISR_GPIO2_DA_get_int_64(data)                                       ((0x00000008&(data))>>3)
#define MIS_FAST_ISR_GPIO2_DA_int_63_shift                                           (2)
#define MIS_FAST_ISR_GPIO2_DA_int_63_mask                                            (0x00000004)
#define MIS_FAST_ISR_GPIO2_DA_int_63(data)                                           (0x00000004&((data)<<2))
#define MIS_FAST_ISR_GPIO2_DA_int_63_src(data)                                       ((0x00000004&(data))>>2)
#define MIS_FAST_ISR_GPIO2_DA_get_int_63(data)                                       ((0x00000004&(data))>>2)
#define MIS_FAST_ISR_GPIO2_DA_int_62_shift                                           (1)
#define MIS_FAST_ISR_GPIO2_DA_int_62_mask                                            (0x00000002)
#define MIS_FAST_ISR_GPIO2_DA_int_62(data)                                           (0x00000002&((data)<<1))
#define MIS_FAST_ISR_GPIO2_DA_int_62_src(data)                                       ((0x00000002&(data))>>1)
#define MIS_FAST_ISR_GPIO2_DA_get_int_62(data)                                       ((0x00000002&(data))>>1)
#define MIS_FAST_ISR_GPIO2_DA_write_data_shift                                       (0)
#define MIS_FAST_ISR_GPIO2_DA_write_data_mask                                        (0x00000001)
#define MIS_FAST_ISR_GPIO2_DA_write_data(data)                                       (0x00000001&((data)<<0))
#define MIS_FAST_ISR_GPIO2_DA_write_data_src(data)                                   ((0x00000001&(data))>>0)
#define MIS_FAST_ISR_GPIO2_DA_get_write_data(data)                                   ((0x00000001&(data))>>0)


#define MIS_FAST_ISR_GPIO3_DA                                                        0x9801B0C4
#define MIS_FAST_ISR_GPIO3_DA_reg_addr                                               "0x9801B0C4"
#define MIS_FAST_ISR_GPIO3_DA_reg                                                    0x9801B0C4
#define set_MIS_FAST_ISR_GPIO3_DA_reg(data)   (*((volatile unsigned int*) MIS_FAST_ISR_GPIO3_DA_reg)=data)
#define get_MIS_FAST_ISR_GPIO3_DA_reg   (*((volatile unsigned int*) MIS_FAST_ISR_GPIO3_DA_reg))
#define MIS_FAST_ISR_GPIO3_DA_inst_adr                                               "0x0031"
#define MIS_FAST_ISR_GPIO3_DA_inst                                                   0x0031
#define MIS_FAST_ISR_GPIO3_DA_int_100_shift                                          (8)
#define MIS_FAST_ISR_GPIO3_DA_int_100_mask                                           (0x00000100)
#define MIS_FAST_ISR_GPIO3_DA_int_100(data)                                          (0x00000100&((data)<<8))
#define MIS_FAST_ISR_GPIO3_DA_int_100_src(data)                                      ((0x00000100&(data))>>8)
#define MIS_FAST_ISR_GPIO3_DA_get_int_100(data)                                      ((0x00000100&(data))>>8)
#define MIS_FAST_ISR_GPIO3_DA_int_99_shift                                           (7)
#define MIS_FAST_ISR_GPIO3_DA_int_99_mask                                            (0x00000080)
#define MIS_FAST_ISR_GPIO3_DA_int_99(data)                                           (0x00000080&((data)<<7))
#define MIS_FAST_ISR_GPIO3_DA_int_99_src(data)                                       ((0x00000080&(data))>>7)
#define MIS_FAST_ISR_GPIO3_DA_get_int_99(data)                                       ((0x00000080&(data))>>7)
#define MIS_FAST_ISR_GPIO3_DA_int_98_shift                                           (6)
#define MIS_FAST_ISR_GPIO3_DA_int_98_mask                                            (0x00000040)
#define MIS_FAST_ISR_GPIO3_DA_int_98(data)                                           (0x00000040&((data)<<6))
#define MIS_FAST_ISR_GPIO3_DA_int_98_src(data)                                       ((0x00000040&(data))>>6)
#define MIS_FAST_ISR_GPIO3_DA_get_int_98(data)                                       ((0x00000040&(data))>>6)
#define MIS_FAST_ISR_GPIO3_DA_int_97_shift                                           (5)
#define MIS_FAST_ISR_GPIO3_DA_int_97_mask                                            (0x00000020)
#define MIS_FAST_ISR_GPIO3_DA_int_97(data)                                           (0x00000020&((data)<<5))
#define MIS_FAST_ISR_GPIO3_DA_int_97_src(data)                                       ((0x00000020&(data))>>5)
#define MIS_FAST_ISR_GPIO3_DA_get_int_97(data)                                       ((0x00000020&(data))>>5)
#define MIS_FAST_ISR_GPIO3_DA_int_96_shift                                           (4)
#define MIS_FAST_ISR_GPIO3_DA_int_96_mask                                            (0x00000010)
#define MIS_FAST_ISR_GPIO3_DA_int_96(data)                                           (0x00000010&((data)<<4))
#define MIS_FAST_ISR_GPIO3_DA_int_96_src(data)                                       ((0x00000010&(data))>>4)
#define MIS_FAST_ISR_GPIO3_DA_get_int_96(data)                                       ((0x00000010&(data))>>4)
#define MIS_FAST_ISR_GPIO3_DA_int_95_shift                                           (3)
#define MIS_FAST_ISR_GPIO3_DA_int_95_mask                                            (0x00000008)
#define MIS_FAST_ISR_GPIO3_DA_int_95(data)                                           (0x00000008&((data)<<3))
#define MIS_FAST_ISR_GPIO3_DA_int_95_src(data)                                       ((0x00000008&(data))>>3)
#define MIS_FAST_ISR_GPIO3_DA_get_int_95(data)                                       ((0x00000008&(data))>>3)
#define MIS_FAST_ISR_GPIO3_DA_int_94_shift                                           (2)
#define MIS_FAST_ISR_GPIO3_DA_int_94_mask                                            (0x00000004)
#define MIS_FAST_ISR_GPIO3_DA_int_94(data)                                           (0x00000004&((data)<<2))
#define MIS_FAST_ISR_GPIO3_DA_int_94_src(data)                                       ((0x00000004&(data))>>2)
#define MIS_FAST_ISR_GPIO3_DA_get_int_94(data)                                       ((0x00000004&(data))>>2)
#define MIS_FAST_ISR_GPIO3_DA_int_93_shift                                           (1)
#define MIS_FAST_ISR_GPIO3_DA_int_93_mask                                            (0x00000002)
#define MIS_FAST_ISR_GPIO3_DA_int_93(data)                                           (0x00000002&((data)<<1))
#define MIS_FAST_ISR_GPIO3_DA_int_93_src(data)                                       ((0x00000002&(data))>>1)
#define MIS_FAST_ISR_GPIO3_DA_get_int_93(data)                                       ((0x00000002&(data))>>1)
#define MIS_FAST_ISR_GPIO3_DA_write_data_shift                                       (0)
#define MIS_FAST_ISR_GPIO3_DA_write_data_mask                                        (0x00000001)
#define MIS_FAST_ISR_GPIO3_DA_write_data(data)                                       (0x00000001&((data)<<0))
#define MIS_FAST_ISR_GPIO3_DA_write_data_src(data)                                   ((0x00000001&(data))>>0)
#define MIS_FAST_ISR_GPIO3_DA_get_write_data(data)                                   ((0x00000001&(data))>>0)


#define MIS_SCPU_INT_EN                                                              0x9801B080
#define MIS_SCPU_INT_EN_reg_addr                                                     "0x9801B080"
#define MIS_SCPU_INT_EN_reg                                                          0x9801B080
#define set_MIS_SCPU_INT_EN_reg(data)   (*((volatile unsigned int*) MIS_SCPU_INT_EN_reg)=data)
#define get_MIS_SCPU_INT_EN_reg   (*((volatile unsigned int*) MIS_SCPU_INT_EN_reg))
#define MIS_SCPU_INT_EN_inst_adr                                                     "0x0020"
#define MIS_SCPU_INT_EN_inst                                                         0x0020
#define MIS_SCPU_INT_EN_fan_shift                                                    (29)
#define MIS_SCPU_INT_EN_fan_mask                                                     (0x20000000)
#define MIS_SCPU_INT_EN_fan(data)                                                    (0x20000000&((data)<<29))
#define MIS_SCPU_INT_EN_fan_src(data)                                                ((0x20000000&(data))>>29)
#define MIS_SCPU_INT_EN_get_fan(data)                                                ((0x20000000&(data))>>29)
#define MIS_SCPU_INT_EN_i2c3_shift                                                   (28)
#define MIS_SCPU_INT_EN_i2c3_mask                                                    (0x10000000)
#define MIS_SCPU_INT_EN_i2c3(data)                                                   (0x10000000&((data)<<28))
#define MIS_SCPU_INT_EN_i2c3_src(data)                                               ((0x10000000&(data))>>28)
#define MIS_SCPU_INT_EN_get_i2c3(data)                                               ((0x10000000&(data))>>28)
#define MIS_SCPU_INT_EN_gspi_shift                                                   (27)
#define MIS_SCPU_INT_EN_gspi_mask                                                    (0x08000000)
#define MIS_SCPU_INT_EN_gspi(data)                                                   (0x08000000&((data)<<27))
#define MIS_SCPU_INT_EN_gspi_src(data)                                               ((0x08000000&(data))>>27)
#define MIS_SCPU_INT_EN_get_gspi(data)                                               ((0x08000000&(data))>>27)
#define MIS_SCPU_INT_EN_i2c2_shift                                                   (26)
#define MIS_SCPU_INT_EN_i2c2_mask                                                    (0x04000000)
#define MIS_SCPU_INT_EN_i2c2(data)                                                   (0x04000000&((data)<<26))
#define MIS_SCPU_INT_EN_i2c2_src(data)                                               ((0x04000000&(data))>>26)
#define MIS_SCPU_INT_EN_get_i2c2(data)                                               ((0x04000000&(data))>>26)
#define MIS_SCPU_INT_EN_sc0_shift                                                    (24)
#define MIS_SCPU_INT_EN_sc0_mask                                                     (0x01000000)
#define MIS_SCPU_INT_EN_sc0(data)                                                    (0x01000000&((data)<<24))
#define MIS_SCPU_INT_EN_sc0_src(data)                                                ((0x01000000&(data))>>24)
#define MIS_SCPU_INT_EN_get_sc0(data)                                                ((0x01000000&(data))>>24)
#define MIS_SCPU_INT_EN_lsadc1_shift                                                 (22)
#define MIS_SCPU_INT_EN_lsadc1_mask                                                  (0x00400000)
#define MIS_SCPU_INT_EN_lsadc1(data)                                                 (0x00400000&((data)<<22))
#define MIS_SCPU_INT_EN_lsadc1_src(data)                                             ((0x00400000&(data))>>22)
#define MIS_SCPU_INT_EN_get_lsadc1(data)                                             ((0x00400000&(data))>>22)
#define MIS_SCPU_INT_EN_lsadc0_shift                                                 (21)
#define MIS_SCPU_INT_EN_lsadc0_mask                                                  (0x00200000)
#define MIS_SCPU_INT_EN_lsadc0(data)                                                 (0x00200000&((data)<<21))
#define MIS_SCPU_INT_EN_lsadc0_src(data)                                             ((0x00200000&(data))>>21)
#define MIS_SCPU_INT_EN_get_lsadc0(data)                                             ((0x00200000&(data))>>21)
#define MIS_SCPU_INT_EN_gpioda_shift                                                 (20)
#define MIS_SCPU_INT_EN_gpioda_mask                                                  (0x00100000)
#define MIS_SCPU_INT_EN_gpioda(data)                                                 (0x00100000&((data)<<20))
#define MIS_SCPU_INT_EN_gpioda_src(data)                                             ((0x00100000&(data))>>20)
#define MIS_SCPU_INT_EN_get_gpioda(data)                                             ((0x00100000&(data))>>20)
#define MIS_SCPU_INT_EN_gpioa_shift                                                  (19)
#define MIS_SCPU_INT_EN_gpioa_mask                                                   (0x00080000)
#define MIS_SCPU_INT_EN_gpioa(data)                                                  (0x00080000&((data)<<19))
#define MIS_SCPU_INT_EN_gpioa_src(data)                                              ((0x00080000&(data))>>19)
#define MIS_SCPU_INT_EN_get_gpioa(data)                                              ((0x00080000&(data))>>19)
#define MIS_SCPU_INT_EN_i2c4_shift                                                   (15)
#define MIS_SCPU_INT_EN_i2c4_mask                                                    (0x00008000)
#define MIS_SCPU_INT_EN_i2c4(data)                                                   (0x00008000&((data)<<15))
#define MIS_SCPU_INT_EN_i2c4_src(data)                                               ((0x00008000&(data))>>15)
#define MIS_SCPU_INT_EN_get_i2c4(data)                                               ((0x00008000&(data))>>15)
#define MIS_SCPU_INT_EN_i2c5_shift                                                   (14)
#define MIS_SCPU_INT_EN_i2c5_mask                                                    (0x00004000)
#define MIS_SCPU_INT_EN_i2c5(data)                                                   (0x00004000&((data)<<14))
#define MIS_SCPU_INT_EN_i2c5_src(data)                                               ((0x00004000&(data))>>14)
#define MIS_SCPU_INT_EN_get_i2c5(data)                                               ((0x00004000&(data))>>14)
#define MIS_SCPU_INT_EN_rtc_date_shift                                               (12)
#define MIS_SCPU_INT_EN_rtc_date_mask                                                (0x00001000)
#define MIS_SCPU_INT_EN_rtc_date(data)                                               (0x00001000&((data)<<12))
#define MIS_SCPU_INT_EN_rtc_date_src(data)                                           ((0x00001000&(data))>>12)
#define MIS_SCPU_INT_EN_get_rtc_date(data)                                           ((0x00001000&(data))>>12)
#define MIS_SCPU_INT_EN_rtc_hour_shift                                               (11)
#define MIS_SCPU_INT_EN_rtc_hour_mask                                                (0x00000800)
#define MIS_SCPU_INT_EN_rtc_hour(data)                                               (0x00000800&((data)<<11))
#define MIS_SCPU_INT_EN_rtc_hour_src(data)                                           ((0x00000800&(data))>>11)
#define MIS_SCPU_INT_EN_get_rtc_hour(data)                                           ((0x00000800&(data))>>11)
#define MIS_SCPU_INT_EN_rtc_min_shift                                                (10)
#define MIS_SCPU_INT_EN_rtc_min_mask                                                 (0x00000400)
#define MIS_SCPU_INT_EN_rtc_min(data)                                                (0x00000400&((data)<<10))
#define MIS_SCPU_INT_EN_rtc_min_src(data)                                            ((0x00000400&(data))>>10)
#define MIS_SCPU_INT_EN_get_rtc_min(data)                                            ((0x00000400&(data))>>10)
#define MIS_SCPU_INT_EN_ur2_shift                                                    (7)
#define MIS_SCPU_INT_EN_ur2_mask                                                     (0x00000080)
#define MIS_SCPU_INT_EN_ur2(data)                                                    (0x00000080&((data)<<7))
#define MIS_SCPU_INT_EN_ur2_src(data)                                                ((0x00000080&(data))>>7)
#define MIS_SCPU_INT_EN_get_ur2(data)                                                ((0x00000080&(data))>>7)
#define MIS_SCPU_INT_EN_ur2_to_shift                                                 (6)
#define MIS_SCPU_INT_EN_ur2_to_mask                                                  (0x00000040)
#define MIS_SCPU_INT_EN_ur2_to(data)                                                 (0x00000040&((data)<<6))
#define MIS_SCPU_INT_EN_ur2_to_src(data)                                             ((0x00000040&(data))>>6)
#define MIS_SCPU_INT_EN_get_ur2_to(data)                                             ((0x00000040&(data))>>6)
#define MIS_SCPU_INT_EN_ur1_to_shift                                                 (5)
#define MIS_SCPU_INT_EN_ur1_to_mask                                                  (0x00000020)
#define MIS_SCPU_INT_EN_ur1_to(data)                                                 (0x00000020&((data)<<5))
#define MIS_SCPU_INT_EN_ur1_to_src(data)                                             ((0x00000020&(data))>>5)
#define MIS_SCPU_INT_EN_get_ur1_to(data)                                             ((0x00000020&(data))>>5)
#define MIS_SCPU_INT_EN_ur1_shift                                                    (3)
#define MIS_SCPU_INT_EN_ur1_mask                                                     (0x00000008)
#define MIS_SCPU_INT_EN_ur1(data)                                                    (0x00000008&((data)<<3))
#define MIS_SCPU_INT_EN_ur1_src(data)                                                ((0x00000008&(data))>>3)
#define MIS_SCPU_INT_EN_get_ur1(data)                                                ((0x00000008&(data))>>3)


#define MIS_I2C2_SDA_DEL                                                             0x9801B08c
#define MIS_I2C2_SDA_DEL_reg_addr                                                    "0x9801B08C"
#define MIS_I2C2_SDA_DEL_reg                                                         0x9801B08C
#define set_MIS_I2C2_SDA_DEL_reg(data)   (*((volatile unsigned int*) MIS_I2C2_SDA_DEL_reg)=data)
#define get_MIS_I2C2_SDA_DEL_reg   (*((volatile unsigned int*) MIS_I2C2_SDA_DEL_reg))
#define MIS_I2C2_SDA_DEL_inst_adr                                                    "0x0023"
#define MIS_I2C2_SDA_DEL_inst                                                        0x0023
#define MIS_I2C2_SDA_DEL_dmy1_shift                                                  (12)
#define MIS_I2C2_SDA_DEL_dmy1_mask                                                   (0xFFFFF000)
#define MIS_I2C2_SDA_DEL_dmy1(data)                                                  (0xFFFFF000&((data)<<12))
#define MIS_I2C2_SDA_DEL_dmy1_src(data)                                              ((0xFFFFF000&(data))>>12)
#define MIS_I2C2_SDA_DEL_get_dmy1(data)                                              ((0xFFFFF000&(data))>>12)
#define MIS_I2C2_SDA_DEL_en_shift                                                    (8)
#define MIS_I2C2_SDA_DEL_en_mask                                                     (0x00000100)
#define MIS_I2C2_SDA_DEL_en(data)                                                    (0x00000100&((data)<<8))
#define MIS_I2C2_SDA_DEL_en_src(data)                                                ((0x00000100&(data))>>8)
#define MIS_I2C2_SDA_DEL_get_en(data)                                                ((0x00000100&(data))>>8)
#define MIS_I2C2_SDA_DEL_sel_shift                                                   (0)
#define MIS_I2C2_SDA_DEL_sel_mask                                                    (0x0000001F)
#define MIS_I2C2_SDA_DEL_sel(data)                                                   (0x0000001F&((data)<<0))
#define MIS_I2C2_SDA_DEL_sel_src(data)                                               ((0x0000001F&(data))>>0)
#define MIS_I2C2_SDA_DEL_get_sel(data)                                               ((0x0000001F&(data))>>0)


#define MIS_I2C3_SDA_DEL                                                             0x9801B090
#define MIS_I2C3_SDA_DEL_reg_addr                                                    "0x9801B090"
#define MIS_I2C3_SDA_DEL_reg                                                         0x9801B090
#define set_MIS_I2C3_SDA_DEL_reg(data)   (*((volatile unsigned int*) MIS_I2C3_SDA_DEL_reg)=data)
#define get_MIS_I2C3_SDA_DEL_reg   (*((volatile unsigned int*) MIS_I2C3_SDA_DEL_reg))
#define MIS_I2C3_SDA_DEL_inst_adr                                                    "0x0024"
#define MIS_I2C3_SDA_DEL_inst                                                        0x0024
#define MIS_I2C3_SDA_DEL_dmy1_shift                                                  (12)
#define MIS_I2C3_SDA_DEL_dmy1_mask                                                   (0xFFFFF000)
#define MIS_I2C3_SDA_DEL_dmy1(data)                                                  (0xFFFFF000&((data)<<12))
#define MIS_I2C3_SDA_DEL_dmy1_src(data)                                              ((0xFFFFF000&(data))>>12)
#define MIS_I2C3_SDA_DEL_get_dmy1(data)                                              ((0xFFFFF000&(data))>>12)
#define MIS_I2C3_SDA_DEL_en_shift                                                    (8)
#define MIS_I2C3_SDA_DEL_en_mask                                                     (0x00000100)
#define MIS_I2C3_SDA_DEL_en(data)                                                    (0x00000100&((data)<<8))
#define MIS_I2C3_SDA_DEL_en_src(data)                                                ((0x00000100&(data))>>8)
#define MIS_I2C3_SDA_DEL_get_en(data)                                                ((0x00000100&(data))>>8)
#define MIS_I2C3_SDA_DEL_sel_shift                                                   (0)
#define MIS_I2C3_SDA_DEL_sel_mask                                                    (0x0000001F)
#define MIS_I2C3_SDA_DEL_sel(data)                                                   (0x0000001F&((data)<<0))
#define MIS_I2C3_SDA_DEL_sel_src(data)                                               ((0x0000001F&(data))>>0)
#define MIS_I2C3_SDA_DEL_get_sel(data)                                               ((0x0000001F&(data))>>0)


#define MIS_I2C4_SDA_DEL                                                             0x9801B094
#define MIS_I2C4_SDA_DEL_reg_addr                                                    "0x9801B094"
#define MIS_I2C4_SDA_DEL_reg                                                         0x9801B094
#define set_MIS_I2C4_SDA_DEL_reg(data)   (*((volatile unsigned int*) MIS_I2C4_SDA_DEL_reg)=data)
#define get_MIS_I2C4_SDA_DEL_reg   (*((volatile unsigned int*) MIS_I2C4_SDA_DEL_reg))
#define MIS_I2C4_SDA_DEL_inst_adr                                                    "0x0025"
#define MIS_I2C4_SDA_DEL_inst                                                        0x0025
#define MIS_I2C4_SDA_DEL_dmy1_shift                                                  (12)
#define MIS_I2C4_SDA_DEL_dmy1_mask                                                   (0xFFFFF000)
#define MIS_I2C4_SDA_DEL_dmy1(data)                                                  (0xFFFFF000&((data)<<12))
#define MIS_I2C4_SDA_DEL_dmy1_src(data)                                              ((0xFFFFF000&(data))>>12)
#define MIS_I2C4_SDA_DEL_get_dmy1(data)                                              ((0xFFFFF000&(data))>>12)
#define MIS_I2C4_SDA_DEL_en_shift                                                    (8)
#define MIS_I2C4_SDA_DEL_en_mask                                                     (0x00000100)
#define MIS_I2C4_SDA_DEL_en(data)                                                    (0x00000100&((data)<<8))
#define MIS_I2C4_SDA_DEL_en_src(data)                                                ((0x00000100&(data))>>8)
#define MIS_I2C4_SDA_DEL_get_en(data)                                                ((0x00000100&(data))>>8)
#define MIS_I2C4_SDA_DEL_sel_shift                                                   (0)
#define MIS_I2C4_SDA_DEL_sel_mask                                                    (0x0000001F)
#define MIS_I2C4_SDA_DEL_sel(data)                                                   (0x0000001F&((data)<<0))
#define MIS_I2C4_SDA_DEL_sel_src(data)                                               ((0x0000001F&(data))>>0)
#define MIS_I2C4_SDA_DEL_get_sel(data)                                               ((0x0000001F&(data))>>0)


#define MIS_I2C5_SDA_DEL                                                             0x9801B098
#define MIS_I2C5_SDA_DEL_reg_addr                                                    "0x9801B098"
#define MIS_I2C5_SDA_DEL_reg                                                         0x9801B098
#define set_MIS_I2C5_SDA_DEL_reg(data)   (*((volatile unsigned int*) MIS_I2C5_SDA_DEL_reg)=data)
#define get_MIS_I2C5_SDA_DEL_reg   (*((volatile unsigned int*) MIS_I2C5_SDA_DEL_reg))
#define MIS_I2C5_SDA_DEL_inst_adr                                                    "0x0026"
#define MIS_I2C5_SDA_DEL_inst                                                        0x0026
#define MIS_I2C5_SDA_DEL_dmy1_shift                                                  (12)
#define MIS_I2C5_SDA_DEL_dmy1_mask                                                   (0xFFFFF000)
#define MIS_I2C5_SDA_DEL_dmy1(data)                                                  (0xFFFFF000&((data)<<12))
#define MIS_I2C5_SDA_DEL_dmy1_src(data)                                              ((0xFFFFF000&(data))>>12)
#define MIS_I2C5_SDA_DEL_get_dmy1(data)                                              ((0xFFFFF000&(data))>>12)
#define MIS_I2C5_SDA_DEL_en_shift                                                    (8)
#define MIS_I2C5_SDA_DEL_en_mask                                                     (0x00000100)
#define MIS_I2C5_SDA_DEL_en(data)                                                    (0x00000100&((data)<<8))
#define MIS_I2C5_SDA_DEL_en_src(data)                                                ((0x00000100&(data))>>8)
#define MIS_I2C5_SDA_DEL_get_en(data)                                                ((0x00000100&(data))>>8)
#define MIS_I2C5_SDA_DEL_sel_shift                                                   (0)
#define MIS_I2C5_SDA_DEL_sel_mask                                                    (0x0000001F)
#define MIS_I2C5_SDA_DEL_sel(data)                                                   (0x0000001F&((data)<<0))
#define MIS_I2C5_SDA_DEL_sel_src(data)                                               ((0x0000001F&(data))>>0)
#define MIS_I2C5_SDA_DEL_get_sel(data)                                               ((0x0000001F&(data))>>0)


#define MIS_RTC_SYS_SYNC                                                             0x9801B09C
#define MIS_RTC_SYS_SYNC_reg_addr                                                    "0x9801B09C"
#define MIS_RTC_SYS_SYNC_reg                                                         0x9801B09C
#define set_MIS_RTC_SYS_SYNC_reg(data)   (*((volatile unsigned int*) MIS_RTC_SYS_SYNC_reg)=data)
#define get_MIS_RTC_SYS_SYNC_reg   (*((volatile unsigned int*) MIS_RTC_SYS_SYNC_reg))
#define MIS_RTC_SYS_SYNC_inst_adr                                                    "0x0027"
#define MIS_RTC_SYS_SYNC_inst                                                        0x0027
#define MIS_RTC_SYS_SYNC_wdog_ov_xor_en_shift                                        (1)
#define MIS_RTC_SYS_SYNC_wdog_ov_xor_en_mask                                         (0x00000002)
#define MIS_RTC_SYS_SYNC_wdog_ov_xor_en(data)                                        (0x00000002&((data)<<1))
#define MIS_RTC_SYS_SYNC_wdog_ov_xor_en_src(data)                                    ((0x00000002&(data))>>1)
#define MIS_RTC_SYS_SYNC_get_wdog_ov_xor_en(data)                                    ((0x00000002&(data))>>1)
#define MIS_RTC_SYS_SYNC_en_shift                                                    (0)
#define MIS_RTC_SYS_SYNC_en_mask                                                     (0x00000001)
#define MIS_RTC_SYS_SYNC_en(data)                                                    (0x00000001&((data)<<0))
#define MIS_RTC_SYS_SYNC_en_src(data)                                                ((0x00000001&(data))>>0)
#define MIS_RTC_SYS_SYNC_get_en(data)                                                ((0x00000001&(data))>>0)


#define MIS_GATING_EN                                                                0x9801B0E0
#define MIS_GATING_EN_reg_addr                                                       "0x9801B0E0"
#define MIS_GATING_EN_reg                                                            0x9801B0E0
#define set_MIS_GATING_EN_reg(data)   (*((volatile unsigned int*) MIS_GATING_EN_reg)=data)
#define get_MIS_GATING_EN_reg   (*((volatile unsigned int*) MIS_GATING_EN_reg))
#define MIS_GATING_EN_inst_adr                                                       "0x0038"
#define MIS_GATING_EN_inst                                                           0x0038
#define MIS_GATING_EN_fan_shift                                                      (5)
#define MIS_GATING_EN_fan_mask                                                       (0x00000020)
#define MIS_GATING_EN_fan(data)                                                      (0x00000020&((data)<<5))
#define MIS_GATING_EN_fan_src(data)                                                  ((0x00000020&(data))>>5)
#define MIS_GATING_EN_get_fan(data)                                                  ((0x00000020&(data))>>5)
#define MIS_GATING_EN_timer_shift                                                    (4)
#define MIS_GATING_EN_timer_mask                                                     (0x00000010)
#define MIS_GATING_EN_timer(data)                                                    (0x00000010&((data)<<4))
#define MIS_GATING_EN_timer_src(data)                                                ((0x00000010&(data))>>4)
#define MIS_GATING_EN_get_timer(data)                                                ((0x00000010&(data))>>4)
#define MIS_GATING_EN_ur2_h5_shift                                                   (3)
#define MIS_GATING_EN_ur2_h5_mask                                                    (0x00000008)
#define MIS_GATING_EN_ur2_h5(data)                                                   (0x00000008&((data)<<3))
#define MIS_GATING_EN_ur2_h5_src(data)                                               ((0x00000008&(data))>>3)
#define MIS_GATING_EN_get_ur2_h5(data)                                               ((0x00000008&(data))>>3)
#define MIS_GATING_EN_ur1_h5_shift                                                   (2)
#define MIS_GATING_EN_ur1_h5_mask                                                    (0x00000004)
#define MIS_GATING_EN_ur1_h5(data)                                                   (0x00000004&((data)<<2))
#define MIS_GATING_EN_ur1_h5_src(data)                                               ((0x00000004&(data))>>2)
#define MIS_GATING_EN_get_ur1_h5(data)                                               ((0x00000004&(data))>>2)
#define MIS_GATING_EN_dummy1_shift                                                   (1)
#define MIS_GATING_EN_dummy1_mask                                                    (0x00000002)
#define MIS_GATING_EN_dummy1(data)                                                   (0x00000002&((data)<<1))
#define MIS_GATING_EN_dummy1_src(data)                                               ((0x00000002&(data))>>1)
#define MIS_GATING_EN_get_dummy1(data)                                               ((0x00000002&(data))>>1)
#define MIS_GATING_EN_dummy0_shift                                                   (0)
#define MIS_GATING_EN_dummy0_mask                                                    (0x00000001)
#define MIS_GATING_EN_dummy0(data)                                                   (0x00000001&((data)<<0))
#define MIS_GATING_EN_dummy0_src(data)                                               ((0x00000001&(data))>>0)
#define MIS_GATING_EN_get_dummy0(data)                                               ((0x00000001&(data))>>0)


#define MIS_DUMMY2                                                                   0x9801B0E4
#define MIS_DUMMY2_reg_addr                                                          "0x9801B0E4"
#define MIS_DUMMY2_reg                                                               0x9801B0E4
#define set_MIS_DUMMY2_reg(data)   (*((volatile unsigned int*) MIS_DUMMY2_reg)=data)
#define get_MIS_DUMMY2_reg   (*((volatile unsigned int*) MIS_DUMMY2_reg))
#define MIS_DUMMY2_inst_adr                                                          "0x0039"
#define MIS_DUMMY2_inst                                                              0x0039
#define MIS_DUMMY2_dummy2_shift                                                      (0)
#define MIS_DUMMY2_dummy2_mask                                                       (0xFFFFFFFF)
#define MIS_DUMMY2_dummy2(data)                                                      (0xFFFFFFFF&((data)<<0))
#define MIS_DUMMY2_dummy2_src(data)                                                  ((0xFFFFFFFF&(data))>>0)
#define MIS_DUMMY2_get_dummy2(data)                                                  ((0xFFFFFFFF&(data))>>0)


#define MIS_DUMMY3                                                                   0x9801B0E8
#define MIS_DUMMY3_reg_addr                                                          "0x9801B0E8"
#define MIS_DUMMY3_reg                                                               0x9801B0E8
#define set_MIS_DUMMY3_reg(data)   (*((volatile unsigned int*) MIS_DUMMY3_reg)=data)
#define get_MIS_DUMMY3_reg   (*((volatile unsigned int*) MIS_DUMMY3_reg))
#define MIS_DUMMY3_inst_adr                                                          "0x003A"
#define MIS_DUMMY3_inst                                                              0x003A
#define MIS_DUMMY3_dummy3_shift                                                      (0)
#define MIS_DUMMY3_dummy3_mask                                                       (0xFFFFFFFF)
#define MIS_DUMMY3_dummy3(data)                                                      (0xFFFFFFFF&((data)<<0))
#define MIS_DUMMY3_dummy3_src(data)                                                  ((0xFFFFFFFF&(data))>>0)
#define MIS_DUMMY3_get_dummy3(data)                                                  ((0xFFFFFFFF&(data))>>0)


#define MIS_UR_H5_CTRL                                                               0x9801B0F0
#define MIS_UR_H5_CTRL_reg_addr                                                      "0x9801B0F0"
#define MIS_UR_H5_CTRL_reg                                                           0x9801B0F0
#define set_MIS_UR_H5_CTRL_reg(data)   (*((volatile unsigned int*) MIS_UR_H5_CTRL_reg)=data)
#define get_MIS_UR_H5_CTRL_reg   (*((volatile unsigned int*) MIS_UR_H5_CTRL_reg))
#define MIS_UR_H5_CTRL_inst_adr                                                      "0x003C"
#define MIS_UR_H5_CTRL_inst                                                          0x003C
#define MIS_UR_H5_CTRL_tx_clr_shift                                                  (3)
#define MIS_UR_H5_CTRL_tx_clr_mask                                                   (0x00000008)
#define MIS_UR_H5_CTRL_tx_clr(data)                                                  (0x00000008&((data)<<3))
#define MIS_UR_H5_CTRL_tx_clr_src(data)                                              ((0x00000008&(data))>>3)
#define MIS_UR_H5_CTRL_get_tx_clr(data)                                              ((0x00000008&(data))>>3)
#define MIS_UR_H5_CTRL_rx_int_mask_shift                                             (2)
#define MIS_UR_H5_CTRL_rx_int_mask_mask                                              (0x00000004)
#define MIS_UR_H5_CTRL_rx_int_mask(data)                                             (0x00000004&((data)<<2))
#define MIS_UR_H5_CTRL_rx_int_mask_src(data)                                         ((0x00000004&(data))>>2)
#define MIS_UR_H5_CTRL_get_rx_int_mask(data)                                         ((0x00000004&(data))>>2)
#define MIS_UR_H5_CTRL_rx_err_clr_shift                                              (1)
#define MIS_UR_H5_CTRL_rx_err_clr_mask                                               (0x00000002)
#define MIS_UR_H5_CTRL_rx_err_clr(data)                                              (0x00000002&((data)<<1))
#define MIS_UR_H5_CTRL_rx_err_clr_src(data)                                          ((0x00000002&(data))>>1)
#define MIS_UR_H5_CTRL_get_rx_err_clr(data)                                          ((0x00000002&(data))>>1)
#define MIS_UR_H5_CTRL_en_shift                                                      (0)
#define MIS_UR_H5_CTRL_en_mask                                                       (0x00000001)
#define MIS_UR_H5_CTRL_en(data)                                                      (0x00000001&((data)<<0))
#define MIS_UR_H5_CTRL_en_src(data)                                                  ((0x00000001&(data))>>0)
#define MIS_UR_H5_CTRL_get_en(data)                                                  ((0x00000001&(data))>>0)


#define MIS_UR_H5_ST                                                                 0x9801B0F4
#define MIS_UR_H5_ST_reg_addr                                                        "0x9801B0F4"
#define MIS_UR_H5_ST_reg                                                             0x9801B0F4
#define set_MIS_UR_H5_ST_reg(data)   (*((volatile unsigned int*) MIS_UR_H5_ST_reg)=data)
#define get_MIS_UR_H5_ST_reg   (*((volatile unsigned int*) MIS_UR_H5_ST_reg))
#define MIS_UR_H5_ST_inst_adr                                                        "0x003D"
#define MIS_UR_H5_ST_inst                                                            0x003D
#define MIS_UR_H5_ST_rx_err_st_shift                                                 (0)
#define MIS_UR_H5_ST_rx_err_st_mask                                                  (0x00000007)
#define MIS_UR_H5_ST_rx_err_st(data)                                                 (0x00000007&((data)<<0))
#define MIS_UR_H5_ST_rx_err_st_src(data)                                             ((0x00000007&(data))>>0)
#define MIS_UR_H5_ST_get_rx_err_st(data)                                             ((0x00000007&(data))>>0)


#define MIS_UR2_H5_CTRL                                                              0x9801B0F8
#define MIS_UR2_H5_CTRL_reg_addr                                                     "0x9801B0F8"
#define MIS_UR2_H5_CTRL_reg                                                          0x9801B0F8
#define set_MIS_UR2_H5_CTRL_reg(data)   (*((volatile unsigned int*) MIS_UR2_H5_CTRL_reg)=data)
#define get_MIS_UR2_H5_CTRL_reg   (*((volatile unsigned int*) MIS_UR2_H5_CTRL_reg))
#define MIS_UR2_H5_CTRL_inst_adr                                                     "0x003E"
#define MIS_UR2_H5_CTRL_inst                                                         0x003E
#define MIS_UR2_H5_CTRL_tx_clr_shift                                                 (3)
#define MIS_UR2_H5_CTRL_tx_clr_mask                                                  (0x00000008)
#define MIS_UR2_H5_CTRL_tx_clr(data)                                                 (0x00000008&((data)<<3))
#define MIS_UR2_H5_CTRL_tx_clr_src(data)                                             ((0x00000008&(data))>>3)
#define MIS_UR2_H5_CTRL_get_tx_clr(data)                                             ((0x00000008&(data))>>3)
#define MIS_UR2_H5_CTRL_rx_int_mask_shift                                            (2)
#define MIS_UR2_H5_CTRL_rx_int_mask_mask                                             (0x00000004)
#define MIS_UR2_H5_CTRL_rx_int_mask(data)                                            (0x00000004&((data)<<2))
#define MIS_UR2_H5_CTRL_rx_int_mask_src(data)                                        ((0x00000004&(data))>>2)
#define MIS_UR2_H5_CTRL_get_rx_int_mask(data)                                        ((0x00000004&(data))>>2)
#define MIS_UR2_H5_CTRL_rx_err_clr_shift                                             (1)
#define MIS_UR2_H5_CTRL_rx_err_clr_mask                                              (0x00000002)
#define MIS_UR2_H5_CTRL_rx_err_clr(data)                                             (0x00000002&((data)<<1))
#define MIS_UR2_H5_CTRL_rx_err_clr_src(data)                                         ((0x00000002&(data))>>1)
#define MIS_UR2_H5_CTRL_get_rx_err_clr(data)                                         ((0x00000002&(data))>>1)
#define MIS_UR2_H5_CTRL_en_shift                                                     (0)
#define MIS_UR2_H5_CTRL_en_mask                                                      (0x00000001)
#define MIS_UR2_H5_CTRL_en(data)                                                     (0x00000001&((data)<<0))
#define MIS_UR2_H5_CTRL_en_src(data)                                                 ((0x00000001&(data))>>0)
#define MIS_UR2_H5_CTRL_get_en(data)                                                 ((0x00000001&(data))>>0)


#define MIS_UR2_H5_ST                                                                0x9801B0FC
#define MIS_UR2_H5_ST_reg_addr                                                       "0x9801B0FC"
#define MIS_UR2_H5_ST_reg                                                            0x9801B0FC
#define set_MIS_UR2_H5_ST_reg(data)   (*((volatile unsigned int*) MIS_UR2_H5_ST_reg)=data)
#define get_MIS_UR2_H5_ST_reg   (*((volatile unsigned int*) MIS_UR2_H5_ST_reg))
#define MIS_UR2_H5_ST_inst_adr                                                       "0x003F"
#define MIS_UR2_H5_ST_inst                                                           0x003F
#define MIS_UR2_H5_ST_rx_err_st_shift                                                (0)
#define MIS_UR2_H5_ST_rx_err_st_mask                                                 (0x00000007)
#define MIS_UR2_H5_ST_rx_err_st(data)                                                (0x00000007&((data)<<0))
#define MIS_UR2_H5_ST_rx_err_st_src(data)                                            ((0x00000007&(data))>>0)
#define MIS_UR2_H5_ST_get_rx_err_st(data)                                            ((0x00000007&(data))>>0)


#define MIS_GP0DIR                                                                   0x9801B100
#define MIS_GP0DIR_reg_addr                                                          "0x9801B100"
#define MIS_GP0DIR_reg                                                               0x9801B100
#define set_MIS_GP0DIR_reg(data)   (*((volatile unsigned int*) MIS_GP0DIR_reg)=data)
#define get_MIS_GP0DIR_reg   (*((volatile unsigned int*) MIS_GP0DIR_reg))
#define MIS_GP0DIR_inst_adr                                                          "0x0040"
#define MIS_GP0DIR_inst                                                              0x0040
#define MIS_GP0DIR_gpdir_shift                                                       (0)
#define MIS_GP0DIR_gpdir_mask                                                        (0xFFFFFFFF)
#define MIS_GP0DIR_gpdir(data)                                                       (0xFFFFFFFF&((data)<<0))
#define MIS_GP0DIR_gpdir_src(data)                                                   ((0xFFFFFFFF&(data))>>0)
#define MIS_GP0DIR_get_gpdir(data)                                                   ((0xFFFFFFFF&(data))>>0)


#define MIS_GP1DIR                                                                   0x9801B104
#define MIS_GP1DIR_reg_addr                                                          "0x9801B104"
#define MIS_GP1DIR_reg                                                               0x9801B104
#define set_MIS_GP1DIR_reg(data)   (*((volatile unsigned int*) MIS_GP1DIR_reg)=data)
#define get_MIS_GP1DIR_reg   (*((volatile unsigned int*) MIS_GP1DIR_reg))
#define MIS_GP1DIR_inst_adr                                                          "0x0041"
#define MIS_GP1DIR_inst                                                              0x0041
#define MIS_GP1DIR_gpdir_shift                                                       (0)
#define MIS_GP1DIR_gpdir_mask                                                        (0xFFFFFFFF)
#define MIS_GP1DIR_gpdir(data)                                                       (0xFFFFFFFF&((data)<<0))
#define MIS_GP1DIR_gpdir_src(data)                                                   ((0xFFFFFFFF&(data))>>0)
#define MIS_GP1DIR_get_gpdir(data)                                                   ((0xFFFFFFFF&(data))>>0)


#define MIS_GP2DIR                                                                   0x9801B108
#define MIS_GP2DIR_reg_addr                                                          "0x9801B108"
#define MIS_GP2DIR_reg                                                               0x9801B108
#define set_MIS_GP2DIR_reg(data)   (*((volatile unsigned int*) MIS_GP2DIR_reg)=data)
#define get_MIS_GP2DIR_reg   (*((volatile unsigned int*) MIS_GP2DIR_reg))
#define MIS_GP2DIR_inst_adr                                                          "0x0042"
#define MIS_GP2DIR_inst                                                              0x0042
#define MIS_GP2DIR_gpdir_shift                                                       (0)
#define MIS_GP2DIR_gpdir_mask                                                        (0xFFFFFFFF)
#define MIS_GP2DIR_gpdir(data)                                                       (0xFFFFFFFF&((data)<<0))
#define MIS_GP2DIR_gpdir_src(data)                                                   ((0xFFFFFFFF&(data))>>0)
#define MIS_GP2DIR_get_gpdir(data)                                                   ((0xFFFFFFFF&(data))>>0)


#define MIS_GP3DIR                                                                   0x9801B10C
#define MIS_GP3DIR_reg_addr                                                          "0x9801B10C"
#define MIS_GP3DIR_reg                                                               0x9801B10C
#define set_MIS_GP3DIR_reg(data)   (*((volatile unsigned int*) MIS_GP3DIR_reg)=data)
#define get_MIS_GP3DIR_reg   (*((volatile unsigned int*) MIS_GP3DIR_reg))
#define MIS_GP3DIR_inst_adr                                                          "0x0043"
#define MIS_GP3DIR_inst                                                              0x0043
#define MIS_GP3DIR_gpdir_shift                                                       (0)
#define MIS_GP3DIR_gpdir_mask                                                        (0x0000001F)
#define MIS_GP3DIR_gpdir(data)                                                       (0x0000001F&((data)<<0))
#define MIS_GP3DIR_gpdir_src(data)                                                   ((0x0000001F&(data))>>0)
#define MIS_GP3DIR_get_gpdir(data)                                                   ((0x0000001F&(data))>>0)


#define MIS_GP0DATO                                                                  0x9801B110
#define MIS_GP0DATO_reg_addr                                                         "0x9801B110"
#define MIS_GP0DATO_reg                                                              0x9801B110
#define set_MIS_GP0DATO_reg(data)   (*((volatile unsigned int*) MIS_GP0DATO_reg)=data)
#define get_MIS_GP0DATO_reg   (*((volatile unsigned int*) MIS_GP0DATO_reg))
#define MIS_GP0DATO_inst_adr                                                         "0x0044"
#define MIS_GP0DATO_inst                                                             0x0044
#define MIS_GP0DATO_gpdato_shift                                                     (0)
#define MIS_GP0DATO_gpdato_mask                                                      (0xFFFFFFFF)
#define MIS_GP0DATO_gpdato(data)                                                     (0xFFFFFFFF&((data)<<0))
#define MIS_GP0DATO_gpdato_src(data)                                                 ((0xFFFFFFFF&(data))>>0)
#define MIS_GP0DATO_get_gpdato(data)                                                 ((0xFFFFFFFF&(data))>>0)


#define MIS_GP1DATO                                                                  0x9801B114
#define MIS_GP1DATO_reg_addr                                                         "0x9801B114"
#define MIS_GP1DATO_reg                                                              0x9801B114
#define set_MIS_GP1DATO_reg(data)   (*((volatile unsigned int*) MIS_GP1DATO_reg)=data)
#define get_MIS_GP1DATO_reg   (*((volatile unsigned int*) MIS_GP1DATO_reg))
#define MIS_GP1DATO_inst_adr                                                         "0x0045"
#define MIS_GP1DATO_inst                                                             0x0045
#define MIS_GP1DATO_gpdato_shift                                                     (0)
#define MIS_GP1DATO_gpdato_mask                                                      (0xFFFFFFFF)
#define MIS_GP1DATO_gpdato(data)                                                     (0xFFFFFFFF&((data)<<0))
#define MIS_GP1DATO_gpdato_src(data)                                                 ((0xFFFFFFFF&(data))>>0)
#define MIS_GP1DATO_get_gpdato(data)                                                 ((0xFFFFFFFF&(data))>>0)


#define MIS_GP2DATO                                                                  0x9801B118
#define MIS_GP2DATO_reg_addr                                                         "0x9801B118"
#define MIS_GP2DATO_reg                                                              0x9801B118
#define set_MIS_GP2DATO_reg(data)   (*((volatile unsigned int*) MIS_GP2DATO_reg)=data)
#define get_MIS_GP2DATO_reg   (*((volatile unsigned int*) MIS_GP2DATO_reg))
#define MIS_GP2DATO_inst_adr                                                         "0x0046"
#define MIS_GP2DATO_inst                                                             0x0046
#define MIS_GP2DATO_gpdato_shift                                                     (0)
#define MIS_GP2DATO_gpdato_mask                                                      (0xFFFFFFFF)
#define MIS_GP2DATO_gpdato(data)                                                     (0xFFFFFFFF&((data)<<0))
#define MIS_GP2DATO_gpdato_src(data)                                                 ((0xFFFFFFFF&(data))>>0)
#define MIS_GP2DATO_get_gpdato(data)                                                 ((0xFFFFFFFF&(data))>>0)


#define MIS_GP3DATO                                                                  0x9801B11C
#define MIS_GP3DATO_reg_addr                                                         "0x9801B11C"
#define MIS_GP3DATO_reg                                                              0x9801B11C
#define set_MIS_GP3DATO_reg(data)   (*((volatile unsigned int*) MIS_GP3DATO_reg)=data)
#define get_MIS_GP3DATO_reg   (*((volatile unsigned int*) MIS_GP3DATO_reg))
#define MIS_GP3DATO_inst_adr                                                         "0x0047"
#define MIS_GP3DATO_inst                                                             0x0047
#define MIS_GP3DATO_gpdato_shift                                                     (0)
#define MIS_GP3DATO_gpdato_mask                                                      (0x0000001F)
#define MIS_GP3DATO_gpdato(data)                                                     (0x0000001F&((data)<<0))
#define MIS_GP3DATO_gpdato_src(data)                                                 ((0x0000001F&(data))>>0)
#define MIS_GP3DATO_get_gpdato(data)                                                 ((0x0000001F&(data))>>0)


#define MIS_GP0DATI                                                                  0x9801B120
#define MIS_GP0DATI_reg_addr                                                         "0x9801B120"
#define MIS_GP0DATI_reg                                                              0x9801B120
#define set_MIS_GP0DATI_reg(data)   (*((volatile unsigned int*) MIS_GP0DATI_reg)=data)
#define get_MIS_GP0DATI_reg   (*((volatile unsigned int*) MIS_GP0DATI_reg))
#define MIS_GP0DATI_inst_adr                                                         "0x0048"
#define MIS_GP0DATI_inst                                                             0x0048
#define MIS_GP0DATI_gpdati_shift                                                     (0)
#define MIS_GP0DATI_gpdati_mask                                                      (0xFFFFFFFF)
#define MIS_GP0DATI_gpdati(data)                                                     (0xFFFFFFFF&((data)<<0))
#define MIS_GP0DATI_gpdati_src(data)                                                 ((0xFFFFFFFF&(data))>>0)
#define MIS_GP0DATI_get_gpdati(data)                                                 ((0xFFFFFFFF&(data))>>0)


#define MIS_GP1DATI                                                                  0x9801B124
#define MIS_GP1DATI_reg_addr                                                         "0x9801B124"
#define MIS_GP1DATI_reg                                                              0x9801B124
#define set_MIS_GP1DATI_reg(data)   (*((volatile unsigned int*) MIS_GP1DATI_reg)=data)
#define get_MIS_GP1DATI_reg   (*((volatile unsigned int*) MIS_GP1DATI_reg))
#define MIS_GP1DATI_inst_adr                                                         "0x0049"
#define MIS_GP1DATI_inst                                                             0x0049
#define MIS_GP1DATI_gpdati_shift                                                     (0)
#define MIS_GP1DATI_gpdati_mask                                                      (0xFFFFFFFF)
#define MIS_GP1DATI_gpdati(data)                                                     (0xFFFFFFFF&((data)<<0))
#define MIS_GP1DATI_gpdati_src(data)                                                 ((0xFFFFFFFF&(data))>>0)
#define MIS_GP1DATI_get_gpdati(data)                                                 ((0xFFFFFFFF&(data))>>0)


#define MIS_GP2DATI                                                                  0x9801B128
#define MIS_GP2DATI_reg_addr                                                         "0x9801B128"
#define MIS_GP2DATI_reg                                                              0x9801B128
#define set_MIS_GP2DATI_reg(data)   (*((volatile unsigned int*) MIS_GP2DATI_reg)=data)
#define get_MIS_GP2DATI_reg   (*((volatile unsigned int*) MIS_GP2DATI_reg))
#define MIS_GP2DATI_inst_adr                                                         "0x004A"
#define MIS_GP2DATI_inst                                                             0x004A
#define MIS_GP2DATI_gpdati_shift                                                     (0)
#define MIS_GP2DATI_gpdati_mask                                                      (0xFFFFFFFF)
#define MIS_GP2DATI_gpdati(data)                                                     (0xFFFFFFFF&((data)<<0))
#define MIS_GP2DATI_gpdati_src(data)                                                 ((0xFFFFFFFF&(data))>>0)
#define MIS_GP2DATI_get_gpdati(data)                                                 ((0xFFFFFFFF&(data))>>0)


#define MIS_GP3DATI                                                                  0x9801B12C
#define MIS_GP3DATI_reg_addr                                                         "0x9801B12C"
#define MIS_GP3DATI_reg                                                              0x9801B12C
#define set_MIS_GP3DATI_reg(data)   (*((volatile unsigned int*) MIS_GP3DATI_reg)=data)
#define get_MIS_GP3DATI_reg   (*((volatile unsigned int*) MIS_GP3DATI_reg))
#define MIS_GP3DATI_inst_adr                                                         "0x004B"
#define MIS_GP3DATI_inst                                                             0x004B
#define MIS_GP3DATI_gpdati_shift                                                     (0)
#define MIS_GP3DATI_gpdati_mask                                                      (0x0000001F)
#define MIS_GP3DATI_gpdati(data)                                                     (0x0000001F&((data)<<0))
#define MIS_GP3DATI_gpdati_src(data)                                                 ((0x0000001F&(data))>>0)
#define MIS_GP3DATI_get_gpdati(data)                                                 ((0x0000001F&(data))>>0)


#define MIS_GP0IE                                                                    0x9801B130
#define MIS_GP0IE_reg_addr                                                           "0x9801B130"
#define MIS_GP0IE_reg                                                                0x9801B130
#define set_MIS_GP0IE_reg(data)   (*((volatile unsigned int*) MIS_GP0IE_reg)=data)
#define get_MIS_GP0IE_reg   (*((volatile unsigned int*) MIS_GP0IE_reg))
#define MIS_GP0IE_inst_adr                                                           "0x004C"
#define MIS_GP0IE_inst                                                               0x004C
#define MIS_GP0IE_gp_shift                                                           (0)
#define MIS_GP0IE_gp_mask                                                            (0xFFFFFFFF)
#define MIS_GP0IE_gp(data)                                                           (0xFFFFFFFF&((data)<<0))
#define MIS_GP0IE_gp_src(data)                                                       ((0xFFFFFFFF&(data))>>0)
#define MIS_GP0IE_get_gp(data)                                                       ((0xFFFFFFFF&(data))>>0)


#define MIS_GP1IE                                                                    0x9801B134
#define MIS_GP1IE_reg_addr                                                           "0x9801B134"
#define MIS_GP1IE_reg                                                                0x9801B134
#define set_MIS_GP1IE_reg(data)   (*((volatile unsigned int*) MIS_GP1IE_reg)=data)
#define get_MIS_GP1IE_reg   (*((volatile unsigned int*) MIS_GP1IE_reg))
#define MIS_GP1IE_inst_adr                                                           "0x004D"
#define MIS_GP1IE_inst                                                               0x004D
#define MIS_GP1IE_gp_shift                                                           (0)
#define MIS_GP1IE_gp_mask                                                            (0xFFFFFFFF)
#define MIS_GP1IE_gp(data)                                                           (0xFFFFFFFF&((data)<<0))
#define MIS_GP1IE_gp_src(data)                                                       ((0xFFFFFFFF&(data))>>0)
#define MIS_GP1IE_get_gp(data)                                                       ((0xFFFFFFFF&(data))>>0)


#define MIS_GP2IE                                                                    0x9801B138
#define MIS_GP2IE_reg_addr                                                           "0x9801B138"
#define MIS_GP2IE_reg                                                                0x9801B138
#define set_MIS_GP2IE_reg(data)   (*((volatile unsigned int*) MIS_GP2IE_reg)=data)
#define get_MIS_GP2IE_reg   (*((volatile unsigned int*) MIS_GP2IE_reg))
#define MIS_GP2IE_inst_adr                                                           "0x004E"
#define MIS_GP2IE_inst                                                               0x004E
#define MIS_GP2IE_gp_shift                                                           (0)
#define MIS_GP2IE_gp_mask                                                            (0xFFFFFFFF)
#define MIS_GP2IE_gp(data)                                                           (0xFFFFFFFF&((data)<<0))
#define MIS_GP2IE_gp_src(data)                                                       ((0xFFFFFFFF&(data))>>0)
#define MIS_GP2IE_get_gp(data)                                                       ((0xFFFFFFFF&(data))>>0)


#define MIS_GP3IE                                                                    0x9801B13C
#define MIS_GP3IE_reg_addr                                                           "0x9801B13C"
#define MIS_GP3IE_reg                                                                0x9801B13C
#define set_MIS_GP3IE_reg(data)   (*((volatile unsigned int*) MIS_GP3IE_reg)=data)
#define get_MIS_GP3IE_reg   (*((volatile unsigned int*) MIS_GP3IE_reg))
#define MIS_GP3IE_inst_adr                                                           "0x004F"
#define MIS_GP3IE_inst                                                               0x004F
#define MIS_GP3IE_gp_shift                                                           (0)
#define MIS_GP3IE_gp_mask                                                            (0x0000001F)
#define MIS_GP3IE_gp(data)                                                           (0x0000001F&((data)<<0))
#define MIS_GP3IE_gp_src(data)                                                       ((0x0000001F&(data))>>0)
#define MIS_GP3IE_get_gp(data)                                                       ((0x0000001F&(data))>>0)


#define MIS_GP0DP                                                                    0x9801B140
#define MIS_GP0DP_reg_addr                                                           "0x9801B140"
#define MIS_GP0DP_reg                                                                0x9801B140
#define set_MIS_GP0DP_reg(data)   (*((volatile unsigned int*) MIS_GP0DP_reg)=data)
#define get_MIS_GP0DP_reg   (*((volatile unsigned int*) MIS_GP0DP_reg))
#define MIS_GP0DP_inst_adr                                                           "0x0050"
#define MIS_GP0DP_inst                                                               0x0050
#define MIS_GP0DP_gpha_shift                                                         (0)
#define MIS_GP0DP_gpha_mask                                                          (0xFFFFFFFF)
#define MIS_GP0DP_gpha(data)                                                         (0xFFFFFFFF&((data)<<0))
#define MIS_GP0DP_gpha_src(data)                                                     ((0xFFFFFFFF&(data))>>0)
#define MIS_GP0DP_get_gpha(data)                                                     ((0xFFFFFFFF&(data))>>0)


#define MIS_GP1DP                                                                    0x9801B144
#define MIS_GP1DP_reg_addr                                                           "0x9801B144"
#define MIS_GP1DP_reg                                                                0x9801B144
#define set_MIS_GP1DP_reg(data)   (*((volatile unsigned int*) MIS_GP1DP_reg)=data)
#define get_MIS_GP1DP_reg   (*((volatile unsigned int*) MIS_GP1DP_reg))
#define MIS_GP1DP_inst_adr                                                           "0x0051"
#define MIS_GP1DP_inst                                                               0x0051
#define MIS_GP1DP_gpha_shift                                                         (0)
#define MIS_GP1DP_gpha_mask                                                          (0xFFFFFFFF)
#define MIS_GP1DP_gpha(data)                                                         (0xFFFFFFFF&((data)<<0))
#define MIS_GP1DP_gpha_src(data)                                                     ((0xFFFFFFFF&(data))>>0)
#define MIS_GP1DP_get_gpha(data)                                                     ((0xFFFFFFFF&(data))>>0)


#define MIS_GP2DP                                                                    0x9801B148
#define MIS_GP2DP_reg_addr                                                           "0x9801B148"
#define MIS_GP2DP_reg                                                                0x9801B148
#define set_MIS_GP2DP_reg(data)   (*((volatile unsigned int*) MIS_GP2DP_reg)=data)
#define get_MIS_GP2DP_reg   (*((volatile unsigned int*) MIS_GP2DP_reg))
#define MIS_GP2DP_inst_adr                                                           "0x0052"
#define MIS_GP2DP_inst                                                               0x0052
#define MIS_GP2DP_gpha_shift                                                         (0)
#define MIS_GP2DP_gpha_mask                                                          (0xFFFFFFFF)
#define MIS_GP2DP_gpha(data)                                                         (0xFFFFFFFF&((data)<<0))
#define MIS_GP2DP_gpha_src(data)                                                     ((0xFFFFFFFF&(data))>>0)
#define MIS_GP2DP_get_gpha(data)                                                     ((0xFFFFFFFF&(data))>>0)


#define MIS_GP3DP                                                                    0x9801B14C
#define MIS_GP3DP_reg_addr                                                           "0x9801B14C"
#define MIS_GP3DP_reg                                                                0x9801B14C
#define set_MIS_GP3DP_reg(data)   (*((volatile unsigned int*) MIS_GP3DP_reg)=data)
#define get_MIS_GP3DP_reg   (*((volatile unsigned int*) MIS_GP3DP_reg))
#define MIS_GP3DP_inst_adr                                                           "0x0053"
#define MIS_GP3DP_inst                                                               0x0053
#define MIS_GP3DP_gpha_shift                                                         (0)
#define MIS_GP3DP_gpha_mask                                                          (0x0000001F)
#define MIS_GP3DP_gpha(data)                                                         (0x0000001F&((data)<<0))
#define MIS_GP3DP_gpha_src(data)                                                     ((0x0000001F&(data))>>0)
#define MIS_GP3DP_get_gpha(data)                                                     ((0x0000001F&(data))>>0)


#define MIS_GPDEB                                                                    0x9801B150
#define MIS_GPDEB_reg_addr                                                           "0x9801B150"
#define MIS_GPDEB_reg                                                                0x9801B150
#define set_MIS_GPDEB_reg(data)   (*((volatile unsigned int*) MIS_GPDEB_reg)=data)
#define get_MIS_GPDEB_reg   (*((volatile unsigned int*) MIS_GPDEB_reg))
#define MIS_GPDEB_inst_adr                                                           "0x0054"
#define MIS_GPDEB_inst                                                               0x0054
#define MIS_GPDEB_write_enable7_shift                                                (27)
#define MIS_GPDEB_write_enable7_mask                                                 (0x08000000)
#define MIS_GPDEB_write_enable7(data)                                                (0x08000000&((data)<<27))
#define MIS_GPDEB_write_enable7_src(data)                                            ((0x08000000&(data))>>27)
#define MIS_GPDEB_get_write_enable7(data)                                            ((0x08000000&(data))>>27)
#define MIS_GPDEB_clk7_shift                                                         (24)
#define MIS_GPDEB_clk7_mask                                                          (0x07000000)
#define MIS_GPDEB_clk7(data)                                                         (0x07000000&((data)<<24))
#define MIS_GPDEB_clk7_src(data)                                                     ((0x07000000&(data))>>24)
#define MIS_GPDEB_get_clk7(data)                                                     ((0x07000000&(data))>>24)
#define MIS_GPDEB_write_enable6_shift                                                (23)
#define MIS_GPDEB_write_enable6_mask                                                 (0x00800000)
#define MIS_GPDEB_write_enable6(data)                                                (0x00800000&((data)<<23))
#define MIS_GPDEB_write_enable6_src(data)                                            ((0x00800000&(data))>>23)
#define MIS_GPDEB_get_write_enable6(data)                                            ((0x00800000&(data))>>23)
#define MIS_GPDEB_clk6_shift                                                         (20)
#define MIS_GPDEB_clk6_mask                                                          (0x00700000)
#define MIS_GPDEB_clk6(data)                                                         (0x00700000&((data)<<20))
#define MIS_GPDEB_clk6_src(data)                                                     ((0x00700000&(data))>>20)
#define MIS_GPDEB_get_clk6(data)                                                     ((0x00700000&(data))>>20)
#define MIS_GPDEB_write_enable5_shift                                                (19)
#define MIS_GPDEB_write_enable5_mask                                                 (0x00080000)
#define MIS_GPDEB_write_enable5(data)                                                (0x00080000&((data)<<19))
#define MIS_GPDEB_write_enable5_src(data)                                            ((0x00080000&(data))>>19)
#define MIS_GPDEB_get_write_enable5(data)                                            ((0x00080000&(data))>>19)
#define MIS_GPDEB_clk5_shift                                                         (16)
#define MIS_GPDEB_clk5_mask                                                          (0x00070000)
#define MIS_GPDEB_clk5(data)                                                         (0x00070000&((data)<<16))
#define MIS_GPDEB_clk5_src(data)                                                     ((0x00070000&(data))>>16)
#define MIS_GPDEB_get_clk5(data)                                                     ((0x00070000&(data))>>16)
#define MIS_GPDEB_write_enable4_shift                                                (15)
#define MIS_GPDEB_write_enable4_mask                                                 (0x00008000)
#define MIS_GPDEB_write_enable4(data)                                                (0x00008000&((data)<<15))
#define MIS_GPDEB_write_enable4_src(data)                                            ((0x00008000&(data))>>15)
#define MIS_GPDEB_get_write_enable4(data)                                            ((0x00008000&(data))>>15)
#define MIS_GPDEB_clk4_shift                                                         (12)
#define MIS_GPDEB_clk4_mask                                                          (0x00007000)
#define MIS_GPDEB_clk4(data)                                                         (0x00007000&((data)<<12))
#define MIS_GPDEB_clk4_src(data)                                                     ((0x00007000&(data))>>12)
#define MIS_GPDEB_get_clk4(data)                                                     ((0x00007000&(data))>>12)
#define MIS_GPDEB_write_enable3_shift                                                (11)
#define MIS_GPDEB_write_enable3_mask                                                 (0x00000800)
#define MIS_GPDEB_write_enable3(data)                                                (0x00000800&((data)<<11))
#define MIS_GPDEB_write_enable3_src(data)                                            ((0x00000800&(data))>>11)
#define MIS_GPDEB_get_write_enable3(data)                                            ((0x00000800&(data))>>11)
#define MIS_GPDEB_clk3_shift                                                         (8)
#define MIS_GPDEB_clk3_mask                                                          (0x00000700)
#define MIS_GPDEB_clk3(data)                                                         (0x00000700&((data)<<8))
#define MIS_GPDEB_clk3_src(data)                                                     ((0x00000700&(data))>>8)
#define MIS_GPDEB_get_clk3(data)                                                     ((0x00000700&(data))>>8)
#define MIS_GPDEB_write_enable2_shift                                                (7)
#define MIS_GPDEB_write_enable2_mask                                                 (0x00000080)
#define MIS_GPDEB_write_enable2(data)                                                (0x00000080&((data)<<7))
#define MIS_GPDEB_write_enable2_src(data)                                            ((0x00000080&(data))>>7)
#define MIS_GPDEB_get_write_enable2(data)                                            ((0x00000080&(data))>>7)
#define MIS_GPDEB_clk2_shift                                                         (4)
#define MIS_GPDEB_clk2_mask                                                          (0x00000070)
#define MIS_GPDEB_clk2(data)                                                         (0x00000070&((data)<<4))
#define MIS_GPDEB_clk2_src(data)                                                     ((0x00000070&(data))>>4)
#define MIS_GPDEB_get_clk2(data)                                                     ((0x00000070&(data))>>4)
#define MIS_GPDEB_write_enable1_shift                                                (3)
#define MIS_GPDEB_write_enable1_mask                                                 (0x00000008)
#define MIS_GPDEB_write_enable1(data)                                                (0x00000008&((data)<<3))
#define MIS_GPDEB_write_enable1_src(data)                                            ((0x00000008&(data))>>3)
#define MIS_GPDEB_get_write_enable1(data)                                            ((0x00000008&(data))>>3)
#define MIS_GPDEB_clk1_shift                                                         (0)
#define MIS_GPDEB_clk1_mask                                                          (0x00000007)
#define MIS_GPDEB_clk1(data)                                                         (0x00000007&((data)<<0))
#define MIS_GPDEB_clk1_src(data)                                                     ((0x00000007&(data))>>0)
#define MIS_GPDEB_get_clk1(data)                                                     ((0x00000007&(data))>>0)


#define MIS_U1RBR_THR_DLL                                                            0x9801B200
#define MIS_U1RBR_THR_DLL_reg_addr                                                   "0x9801B200"
#define MIS_U1RBR_THR_DLL_reg                                                        0x9801B200
#define set_MIS_U1RBR_THR_DLL_reg(data)   (*((volatile unsigned int*) MIS_U1RBR_THR_DLL_reg)=data)
#define get_MIS_U1RBR_THR_DLL_reg   (*((volatile unsigned int*) MIS_U1RBR_THR_DLL_reg))
#define MIS_U1RBR_THR_DLL_inst_adr                                                   "0x0080"
#define MIS_U1RBR_THR_DLL_inst                                                       0x0080
#define MIS_U1RBR_THR_DLL_dll_shift                                                  (0)
#define MIS_U1RBR_THR_DLL_dll_mask                                                   (0x000000FF)
#define MIS_U1RBR_THR_DLL_dll(data)                                                  (0x000000FF&((data)<<0))
#define MIS_U1RBR_THR_DLL_dll_src(data)                                              ((0x000000FF&(data))>>0)
#define MIS_U1RBR_THR_DLL_get_dll(data)                                              ((0x000000FF&(data))>>0)


#define MIS_U1IER_DLH                                                                0x9801B204
#define MIS_U1IER_DLH_reg_addr                                                       "0x9801B204"
#define MIS_U1IER_DLH_reg                                                            0x9801B204
#define set_MIS_U1IER_DLH_reg(data)   (*((volatile unsigned int*) MIS_U1IER_DLH_reg)=data)
#define get_MIS_U1IER_DLH_reg   (*((volatile unsigned int*) MIS_U1IER_DLH_reg))
#define MIS_U1IER_DLH_inst_adr                                                       "0x0081"
#define MIS_U1IER_DLH_inst                                                           0x0081
#define MIS_U1IER_DLH_dlh_shift                                                      (0)
#define MIS_U1IER_DLH_dlh_mask                                                       (0x000000FF)
#define MIS_U1IER_DLH_dlh(data)                                                      (0x000000FF&((data)<<0))
#define MIS_U1IER_DLH_dlh_src(data)                                                  ((0x000000FF&(data))>>0)
#define MIS_U1IER_DLH_get_dlh(data)                                                  ((0x000000FF&(data))>>0)


#define MIS_U1IIR_FCR                                                                0x9801B208
#define MIS_U1IIR_FCR_reg_addr                                                       "0x9801B208"
#define MIS_U1IIR_FCR_reg                                                            0x9801B208
#define set_MIS_U1IIR_FCR_reg(data)   (*((volatile unsigned int*) MIS_U1IIR_FCR_reg)=data)
#define get_MIS_U1IIR_FCR_reg   (*((volatile unsigned int*) MIS_U1IIR_FCR_reg))
#define MIS_U1IIR_FCR_inst_adr                                                       "0x0082"
#define MIS_U1IIR_FCR_inst                                                           0x0082
#define MIS_U1IIR_FCR_fifo16_shift                                                   (6)
#define MIS_U1IIR_FCR_fifo16_mask                                                    (0x000000C0)
#define MIS_U1IIR_FCR_fifo16(data)                                                   (0x000000C0&((data)<<6))
#define MIS_U1IIR_FCR_fifo16_src(data)                                               ((0x000000C0&(data))>>6)
#define MIS_U1IIR_FCR_get_fifo16(data)                                               ((0x000000C0&(data))>>6)
#define MIS_U1IIR_FCR_iid_shift                                                      (0)
#define MIS_U1IIR_FCR_iid_mask                                                       (0x0000000F)
#define MIS_U1IIR_FCR_iid(data)                                                      (0x0000000F&((data)<<0))
#define MIS_U1IIR_FCR_iid_src(data)                                                  ((0x0000000F&(data))>>0)
#define MIS_U1IIR_FCR_get_iid(data)                                                  ((0x0000000F&(data))>>0)


#define MIS_U1LCR                                                                    0x9801B20C
#define MIS_U1LCR_reg_addr                                                           "0x9801B20C"
#define MIS_U1LCR_reg                                                                0x9801B20C
#define set_MIS_U1LCR_reg(data)   (*((volatile unsigned int*) MIS_U1LCR_reg)=data)
#define get_MIS_U1LCR_reg   (*((volatile unsigned int*) MIS_U1LCR_reg))
#define MIS_U1LCR_inst_adr                                                           "0x0083"
#define MIS_U1LCR_inst                                                               0x0083
#define MIS_U1LCR_dlab_shift                                                         (7)
#define MIS_U1LCR_dlab_mask                                                          (0x00000080)
#define MIS_U1LCR_dlab(data)                                                         (0x00000080&((data)<<7))
#define MIS_U1LCR_dlab_src(data)                                                     ((0x00000080&(data))>>7)
#define MIS_U1LCR_get_dlab(data)                                                     ((0x00000080&(data))>>7)
#define MIS_U1LCR_brk_shift                                                          (6)
#define MIS_U1LCR_brk_mask                                                           (0x00000040)
#define MIS_U1LCR_brk(data)                                                          (0x00000040&((data)<<6))
#define MIS_U1LCR_brk_src(data)                                                      ((0x00000040&(data))>>6)
#define MIS_U1LCR_get_brk(data)                                                      ((0x00000040&(data))>>6)
#define MIS_U1LCR_eps_shift                                                          (4)
#define MIS_U1LCR_eps_mask                                                           (0x00000010)
#define MIS_U1LCR_eps(data)                                                          (0x00000010&((data)<<4))
#define MIS_U1LCR_eps_src(data)                                                      ((0x00000010&(data))>>4)
#define MIS_U1LCR_get_eps(data)                                                      ((0x00000010&(data))>>4)
#define MIS_U1LCR_pen_shift                                                          (3)
#define MIS_U1LCR_pen_mask                                                           (0x00000008)
#define MIS_U1LCR_pen(data)                                                          (0x00000008&((data)<<3))
#define MIS_U1LCR_pen_src(data)                                                      ((0x00000008&(data))>>3)
#define MIS_U1LCR_get_pen(data)                                                      ((0x00000008&(data))>>3)
#define MIS_U1LCR_stb_shift                                                          (2)
#define MIS_U1LCR_stb_mask                                                           (0x00000004)
#define MIS_U1LCR_stb(data)                                                          (0x00000004&((data)<<2))
#define MIS_U1LCR_stb_src(data)                                                      ((0x00000004&(data))>>2)
#define MIS_U1LCR_get_stb(data)                                                      ((0x00000004&(data))>>2)
#define MIS_U1LCR_wls_shift                                                          (0)
#define MIS_U1LCR_wls_mask                                                           (0x00000003)
#define MIS_U1LCR_wls(data)                                                          (0x00000003&((data)<<0))
#define MIS_U1LCR_wls_src(data)                                                      ((0x00000003&(data))>>0)
#define MIS_U1LCR_get_wls(data)                                                      ((0x00000003&(data))>>0)


#define MIS_U1MCR                                                                    0x9801B210
#define MIS_U1MCR_reg_addr                                                           "0x9801B210"
#define MIS_U1MCR_reg                                                                0x9801B210
#define set_MIS_U1MCR_reg(data)   (*((volatile unsigned int*) MIS_U1MCR_reg)=data)
#define get_MIS_U1MCR_reg   (*((volatile unsigned int*) MIS_U1MCR_reg))
#define MIS_U1MCR_inst_adr                                                           "0x0084"
#define MIS_U1MCR_inst                                                               0x0084
#define MIS_U1MCR_afce_shift                                                         (5)
#define MIS_U1MCR_afce_mask                                                          (0x00000020)
#define MIS_U1MCR_afce(data)                                                         (0x00000020&((data)<<5))
#define MIS_U1MCR_afce_src(data)                                                     ((0x00000020&(data))>>5)
#define MIS_U1MCR_get_afce(data)                                                     ((0x00000020&(data))>>5)
#define MIS_U1MCR_loop_shift                                                         (4)
#define MIS_U1MCR_loop_mask                                                          (0x00000010)
#define MIS_U1MCR_loop(data)                                                         (0x00000010&((data)<<4))
#define MIS_U1MCR_loop_src(data)                                                     ((0x00000010&(data))>>4)
#define MIS_U1MCR_get_loop(data)                                                     ((0x00000010&(data))>>4)
#define MIS_U1MCR_rts_shift                                                          (1)
#define MIS_U1MCR_rts_mask                                                           (0x00000002)
#define MIS_U1MCR_rts(data)                                                          (0x00000002&((data)<<1))
#define MIS_U1MCR_rts_src(data)                                                      ((0x00000002&(data))>>1)
#define MIS_U1MCR_get_rts(data)                                                      ((0x00000002&(data))>>1)
#define MIS_U1MCR_dtr_shift                                                          (0)
#define MIS_U1MCR_dtr_mask                                                           (0x00000001)
#define MIS_U1MCR_dtr(data)                                                          (0x00000001&((data)<<0))
#define MIS_U1MCR_dtr_src(data)                                                      ((0x00000001&(data))>>0)
#define MIS_U1MCR_get_dtr(data)                                                      ((0x00000001&(data))>>0)


#define MIS_U1LSR                                                                    0x9801B214
#define MIS_U1LSR_reg_addr                                                           "0x9801B214"
#define MIS_U1LSR_reg                                                                0x9801B214
#define set_MIS_U1LSR_reg(data)   (*((volatile unsigned int*) MIS_U1LSR_reg)=data)
#define get_MIS_U1LSR_reg   (*((volatile unsigned int*) MIS_U1LSR_reg))
#define MIS_U1LSR_inst_adr                                                           "0x0085"
#define MIS_U1LSR_inst                                                               0x0085
#define MIS_U1LSR_rfe_shift                                                          (7)
#define MIS_U1LSR_rfe_mask                                                           (0x00000080)
#define MIS_U1LSR_rfe(data)                                                          (0x00000080&((data)<<7))
#define MIS_U1LSR_rfe_src(data)                                                      ((0x00000080&(data))>>7)
#define MIS_U1LSR_get_rfe(data)                                                      ((0x00000080&(data))>>7)
#define MIS_U1LSR_temt_shift                                                         (6)
#define MIS_U1LSR_temt_mask                                                          (0x00000040)
#define MIS_U1LSR_temt(data)                                                         (0x00000040&((data)<<6))
#define MIS_U1LSR_temt_src(data)                                                     ((0x00000040&(data))>>6)
#define MIS_U1LSR_get_temt(data)                                                     ((0x00000040&(data))>>6)
#define MIS_U1LSR_thre_shift                                                         (5)
#define MIS_U1LSR_thre_mask                                                          (0x00000020)
#define MIS_U1LSR_thre(data)                                                         (0x00000020&((data)<<5))
#define MIS_U1LSR_thre_src(data)                                                     ((0x00000020&(data))>>5)
#define MIS_U1LSR_get_thre(data)                                                     ((0x00000020&(data))>>5)
#define MIS_U1LSR_bi_shift                                                           (4)
#define MIS_U1LSR_bi_mask                                                            (0x00000010)
#define MIS_U1LSR_bi(data)                                                           (0x00000010&((data)<<4))
#define MIS_U1LSR_bi_src(data)                                                       ((0x00000010&(data))>>4)
#define MIS_U1LSR_get_bi(data)                                                       ((0x00000010&(data))>>4)
#define MIS_U1LSR_fe_shift                                                           (3)
#define MIS_U1LSR_fe_mask                                                            (0x00000008)
#define MIS_U1LSR_fe(data)                                                           (0x00000008&((data)<<3))
#define MIS_U1LSR_fe_src(data)                                                       ((0x00000008&(data))>>3)
#define MIS_U1LSR_get_fe(data)                                                       ((0x00000008&(data))>>3)
#define MIS_U1LSR_pe_shift                                                           (2)
#define MIS_U1LSR_pe_mask                                                            (0x00000004)
#define MIS_U1LSR_pe(data)                                                           (0x00000004&((data)<<2))
#define MIS_U1LSR_pe_src(data)                                                       ((0x00000004&(data))>>2)
#define MIS_U1LSR_get_pe(data)                                                       ((0x00000004&(data))>>2)
#define MIS_U1LSR_oe_shift                                                           (1)
#define MIS_U1LSR_oe_mask                                                            (0x00000002)
#define MIS_U1LSR_oe(data)                                                           (0x00000002&((data)<<1))
#define MIS_U1LSR_oe_src(data)                                                       ((0x00000002&(data))>>1)
#define MIS_U1LSR_get_oe(data)                                                       ((0x00000002&(data))>>1)
#define MIS_U1LSR_dr_shift                                                           (0)
#define MIS_U1LSR_dr_mask                                                            (0x00000001)
#define MIS_U1LSR_dr(data)                                                           (0x00000001&((data)<<0))
#define MIS_U1LSR_dr_src(data)                                                       ((0x00000001&(data))>>0)
#define MIS_U1LSR_get_dr(data)                                                       ((0x00000001&(data))>>0)


#define MIS_U1MSR                                                                    0x9801B218
#define MIS_U1MSR_reg_addr                                                           "0x9801B218"
#define MIS_U1MSR_reg                                                                0x9801B218
#define set_MIS_U1MSR_reg(data)   (*((volatile unsigned int*) MIS_U1MSR_reg)=data)
#define get_MIS_U1MSR_reg   (*((volatile unsigned int*) MIS_U1MSR_reg))
#define MIS_U1MSR_inst_adr                                                           "0x0086"
#define MIS_U1MSR_inst                                                               0x0086
#define MIS_U1MSR_dcd_shift                                                          (7)
#define MIS_U1MSR_dcd_mask                                                           (0x00000080)
#define MIS_U1MSR_dcd(data)                                                          (0x00000080&((data)<<7))
#define MIS_U1MSR_dcd_src(data)                                                      ((0x00000080&(data))>>7)
#define MIS_U1MSR_get_dcd(data)                                                      ((0x00000080&(data))>>7)
#define MIS_U1MSR_ri_shift                                                           (6)
#define MIS_U1MSR_ri_mask                                                            (0x00000040)
#define MIS_U1MSR_ri(data)                                                           (0x00000040&((data)<<6))
#define MIS_U1MSR_ri_src(data)                                                       ((0x00000040&(data))>>6)
#define MIS_U1MSR_get_ri(data)                                                       ((0x00000040&(data))>>6)
#define MIS_U1MSR_dsr_shift                                                          (5)
#define MIS_U1MSR_dsr_mask                                                           (0x00000020)
#define MIS_U1MSR_dsr(data)                                                          (0x00000020&((data)<<5))
#define MIS_U1MSR_dsr_src(data)                                                      ((0x00000020&(data))>>5)
#define MIS_U1MSR_get_dsr(data)                                                      ((0x00000020&(data))>>5)
#define MIS_U1MSR_cts_shift                                                          (4)
#define MIS_U1MSR_cts_mask                                                           (0x00000010)
#define MIS_U1MSR_cts(data)                                                          (0x00000010&((data)<<4))
#define MIS_U1MSR_cts_src(data)                                                      ((0x00000010&(data))>>4)
#define MIS_U1MSR_get_cts(data)                                                      ((0x00000010&(data))>>4)
#define MIS_U1MSR_ddcd_shift                                                         (3)
#define MIS_U1MSR_ddcd_mask                                                          (0x00000008)
#define MIS_U1MSR_ddcd(data)                                                         (0x00000008&((data)<<3))
#define MIS_U1MSR_ddcd_src(data)                                                     ((0x00000008&(data))>>3)
#define MIS_U1MSR_get_ddcd(data)                                                     ((0x00000008&(data))>>3)
#define MIS_U1MSR_teri_shift                                                         (2)
#define MIS_U1MSR_teri_mask                                                          (0x00000004)
#define MIS_U1MSR_teri(data)                                                         (0x00000004&((data)<<2))
#define MIS_U1MSR_teri_src(data)                                                     ((0x00000004&(data))>>2)
#define MIS_U1MSR_get_teri(data)                                                     ((0x00000004&(data))>>2)
#define MIS_U1MSR_ddsr_shift                                                         (1)
#define MIS_U1MSR_ddsr_mask                                                          (0x00000002)
#define MIS_U1MSR_ddsr(data)                                                         (0x00000002&((data)<<1))
#define MIS_U1MSR_ddsr_src(data)                                                     ((0x00000002&(data))>>1)
#define MIS_U1MSR_get_ddsr(data)                                                     ((0x00000002&(data))>>1)
#define MIS_U1MSR_dcts_shift                                                         (0)
#define MIS_U1MSR_dcts_mask                                                          (0x00000001)
#define MIS_U1MSR_dcts(data)                                                         (0x00000001&((data)<<0))
#define MIS_U1MSR_dcts_src(data)                                                     ((0x00000001&(data))>>0)
#define MIS_U1MSR_get_dcts(data)                                                     ((0x00000001&(data))>>0)


#define MIS_U1SCR                                                                    0x9801B21C
#define MIS_U1SCR_reg_addr                                                           "0x9801B21C"
#define MIS_U1SCR_reg                                                                0x9801B21C
#define set_MIS_U1SCR_reg(data)   (*((volatile unsigned int*) MIS_U1SCR_reg)=data)
#define get_MIS_U1SCR_reg   (*((volatile unsigned int*) MIS_U1SCR_reg))
#define MIS_U1SCR_inst_adr                                                           "0x0087"
#define MIS_U1SCR_inst                                                               0x0087
#define MIS_U1SCR_scr_shift                                                          (0)
#define MIS_U1SCR_scr_mask                                                           (0x000000FF)
#define MIS_U1SCR_scr(data)                                                          (0x000000FF&((data)<<0))
#define MIS_U1SCR_scr_src(data)                                                      ((0x000000FF&(data))>>0)
#define MIS_U1SCR_get_scr(data)                                                      ((0x000000FF&(data))>>0)


#define MIS_U1SRBR_0                                                                 0x9801B230
#define MIS_U1SRBR_1                                                                 0x9801B234
#define MIS_U1SRBR_2                                                                 0x9801B238
#define MIS_U1SRBR_3                                                                 0x9801B23C
#define MIS_U1SRBR_4                                                                 0x9801B240
#define MIS_U1SRBR_5                                                                 0x9801B244
#define MIS_U1SRBR_6                                                                 0x9801B248
#define MIS_U1SRBR_7                                                                 0x9801B24C
#define MIS_U1SRBR_8                                                                 0x9801B250
#define MIS_U1SRBR_9                                                                 0x9801B254
#define MIS_U1SRBR_10                                                                 0x9801B258
#define MIS_U1SRBR_11                                                                 0x9801B25C
#define MIS_U1SRBR_12                                                                 0x9801B260
#define MIS_U1SRBR_13                                                                 0x9801B264
#define MIS_U1SRBR_14                                                                 0x9801B268
#define MIS_U1SRBR_15                                                                 0x9801B26C
#define MIS_U1SRBR_0_reg_addr                                                        "0x9801B230"
#define MIS_U1SRBR_1_reg_addr                                                        "0x9801B234"
#define MIS_U1SRBR_2_reg_addr                                                        "0x9801B238"
#define MIS_U1SRBR_3_reg_addr                                                        "0x9801B23C"
#define MIS_U1SRBR_4_reg_addr                                                        "0x9801B240"
#define MIS_U1SRBR_5_reg_addr                                                        "0x9801B244"
#define MIS_U1SRBR_6_reg_addr                                                        "0x9801B248"
#define MIS_U1SRBR_7_reg_addr                                                        "0x9801B24C"
#define MIS_U1SRBR_8_reg_addr                                                        "0x9801B250"
#define MIS_U1SRBR_9_reg_addr                                                        "0x9801B254"
#define MIS_U1SRBR_10_reg_addr                                                        "0x9801B258"
#define MIS_U1SRBR_11_reg_addr                                                        "0x9801B25C"
#define MIS_U1SRBR_12_reg_addr                                                        "0x9801B260"
#define MIS_U1SRBR_13_reg_addr                                                        "0x9801B264"
#define MIS_U1SRBR_14_reg_addr                                                        "0x9801B268"
#define MIS_U1SRBR_15_reg_addr                                                        "0x9801B26C"
#define MIS_U1SRBR_0_reg                                                             0x9801B230
#define MIS_U1SRBR_1_reg                                                             0x9801B234
#define MIS_U1SRBR_2_reg                                                             0x9801B238
#define MIS_U1SRBR_3_reg                                                             0x9801B23C
#define MIS_U1SRBR_4_reg                                                             0x9801B240
#define MIS_U1SRBR_5_reg                                                             0x9801B244
#define MIS_U1SRBR_6_reg                                                             0x9801B248
#define MIS_U1SRBR_7_reg                                                             0x9801B24C
#define MIS_U1SRBR_8_reg                                                             0x9801B250
#define MIS_U1SRBR_9_reg                                                             0x9801B254
#define MIS_U1SRBR_10_reg                                                             0x9801B258
#define MIS_U1SRBR_11_reg                                                             0x9801B25C
#define MIS_U1SRBR_12_reg                                                             0x9801B260
#define MIS_U1SRBR_13_reg                                                             0x9801B264
#define MIS_U1SRBR_14_reg                                                             0x9801B268
#define MIS_U1SRBR_15_reg                                                             0x9801B26C
#define set_MIS_U1SRBR_0_reg(data)   (*((volatile unsigned int*) MIS_U1SRBR_0_reg)=data)
#define set_MIS_U1SRBR_1_reg(data)   (*((volatile unsigned int*) MIS_U1SRBR_1_reg)=data)
#define set_MIS_U1SRBR_2_reg(data)   (*((volatile unsigned int*) MIS_U1SRBR_2_reg)=data)
#define set_MIS_U1SRBR_3_reg(data)   (*((volatile unsigned int*) MIS_U1SRBR_3_reg)=data)
#define set_MIS_U1SRBR_4_reg(data)   (*((volatile unsigned int*) MIS_U1SRBR_4_reg)=data)
#define set_MIS_U1SRBR_5_reg(data)   (*((volatile unsigned int*) MIS_U1SRBR_5_reg)=data)
#define set_MIS_U1SRBR_6_reg(data)   (*((volatile unsigned int*) MIS_U1SRBR_6_reg)=data)
#define set_MIS_U1SRBR_7_reg(data)   (*((volatile unsigned int*) MIS_U1SRBR_7_reg)=data)
#define set_MIS_U1SRBR_8_reg(data)   (*((volatile unsigned int*) MIS_U1SRBR_8_reg)=data)
#define set_MIS_U1SRBR_9_reg(data)   (*((volatile unsigned int*) MIS_U1SRBR_9_reg)=data)
#define set_MIS_U1SRBR_10_reg(data)   (*((volatile unsigned int*) MIS_U1SRBR_10_reg)=data)
#define set_MIS_U1SRBR_11_reg(data)   (*((volatile unsigned int*) MIS_U1SRBR_11_reg)=data)
#define set_MIS_U1SRBR_12_reg(data)   (*((volatile unsigned int*) MIS_U1SRBR_12_reg)=data)
#define set_MIS_U1SRBR_13_reg(data)   (*((volatile unsigned int*) MIS_U1SRBR_13_reg)=data)
#define set_MIS_U1SRBR_14_reg(data)   (*((volatile unsigned int*) MIS_U1SRBR_14_reg)=data)
#define set_MIS_U1SRBR_15_reg(data)   (*((volatile unsigned int*) MIS_U1SRBR_15_reg)=data)
#define get_MIS_U1SRBR_0_reg   (*((volatile unsigned int*) MIS_U1SRBR_0_reg))
#define get_MIS_U1SRBR_1_reg   (*((volatile unsigned int*) MIS_U1SRBR_1_reg))
#define get_MIS_U1SRBR_2_reg   (*((volatile unsigned int*) MIS_U1SRBR_2_reg))
#define get_MIS_U1SRBR_3_reg   (*((volatile unsigned int*) MIS_U1SRBR_3_reg))
#define get_MIS_U1SRBR_4_reg   (*((volatile unsigned int*) MIS_U1SRBR_4_reg))
#define get_MIS_U1SRBR_5_reg   (*((volatile unsigned int*) MIS_U1SRBR_5_reg))
#define get_MIS_U1SRBR_6_reg   (*((volatile unsigned int*) MIS_U1SRBR_6_reg))
#define get_MIS_U1SRBR_7_reg   (*((volatile unsigned int*) MIS_U1SRBR_7_reg))
#define get_MIS_U1SRBR_8_reg   (*((volatile unsigned int*) MIS_U1SRBR_8_reg))
#define get_MIS_U1SRBR_9_reg   (*((volatile unsigned int*) MIS_U1SRBR_9_reg))
#define get_MIS_U1SRBR_10_reg   (*((volatile unsigned int*) MIS_U1SRBR_10_reg))
#define get_MIS_U1SRBR_11_reg   (*((volatile unsigned int*) MIS_U1SRBR_11_reg))
#define get_MIS_U1SRBR_12_reg   (*((volatile unsigned int*) MIS_U1SRBR_12_reg))
#define get_MIS_U1SRBR_13_reg   (*((volatile unsigned int*) MIS_U1SRBR_13_reg))
#define get_MIS_U1SRBR_14_reg   (*((volatile unsigned int*) MIS_U1SRBR_14_reg))
#define get_MIS_U1SRBR_15_reg   (*((volatile unsigned int*) MIS_U1SRBR_15_reg))
#define MIS_U1SRBR_0_inst_adr                                                        "0x008C"
#define MIS_U1SRBR_1_inst_adr                                                        "0x008D"
#define MIS_U1SRBR_2_inst_adr                                                        "0x008E"
#define MIS_U1SRBR_3_inst_adr                                                        "0x008F"
#define MIS_U1SRBR_4_inst_adr                                                        "0x0090"
#define MIS_U1SRBR_5_inst_adr                                                        "0x0091"
#define MIS_U1SRBR_6_inst_adr                                                        "0x0092"
#define MIS_U1SRBR_7_inst_adr                                                        "0x0093"
#define MIS_U1SRBR_8_inst_adr                                                        "0x0094"
#define MIS_U1SRBR_9_inst_adr                                                        "0x0095"
#define MIS_U1SRBR_10_inst_adr                                                        "0x0096"
#define MIS_U1SRBR_11_inst_adr                                                        "0x0097"
#define MIS_U1SRBR_12_inst_adr                                                        "0x0098"
#define MIS_U1SRBR_13_inst_adr                                                        "0x0099"
#define MIS_U1SRBR_14_inst_adr                                                        "0x009A"
#define MIS_U1SRBR_15_inst_adr                                                        "0x009B"
#define MIS_U1SRBR_0_inst                                                            0x008C
#define MIS_U1SRBR_1_inst                                                            0x008D
#define MIS_U1SRBR_2_inst                                                            0x008E
#define MIS_U1SRBR_3_inst                                                            0x008F
#define MIS_U1SRBR_4_inst                                                            0x0090
#define MIS_U1SRBR_5_inst                                                            0x0091
#define MIS_U1SRBR_6_inst                                                            0x0092
#define MIS_U1SRBR_7_inst                                                            0x0093
#define MIS_U1SRBR_8_inst                                                            0x0094
#define MIS_U1SRBR_9_inst                                                            0x0095
#define MIS_U1SRBR_10_inst                                                            0x0096
#define MIS_U1SRBR_11_inst                                                            0x0097
#define MIS_U1SRBR_12_inst                                                            0x0098
#define MIS_U1SRBR_13_inst                                                            0x0099
#define MIS_U1SRBR_14_inst                                                            0x009A
#define MIS_U1SRBR_15_inst                                                            0x009B
#define MIS_U1SRBR_rbd_shift                                                         (0)
#define MIS_U1SRBR_rbd_mask                                                          (0x000000FF)
#define MIS_U1SRBR_rbd(data)                                                         (0x000000FF&((data)<<0))
#define MIS_U1SRBR_rbd_src(data)                                                     ((0x000000FF&(data))>>0)
#define MIS_U1SRBR_get_rbd(data)                                                     ((0x000000FF&(data))>>0)


#define MIS_U1FAR                                                                    0x9801B270
#define MIS_U1FAR_reg_addr                                                           "0x9801B270"
#define MIS_U1FAR_reg                                                                0x9801B270
#define set_MIS_U1FAR_reg(data)   (*((volatile unsigned int*) MIS_U1FAR_reg)=data)
#define get_MIS_U1FAR_reg   (*((volatile unsigned int*) MIS_U1FAR_reg))
#define MIS_U1FAR_inst_adr                                                           "0x009C"
#define MIS_U1FAR_inst                                                               0x009C
#define MIS_U1FAR_far_shift                                                          (0)
#define MIS_U1FAR_far_mask                                                           (0x00000001)
#define MIS_U1FAR_far(data)                                                          (0x00000001&((data)<<0))
#define MIS_U1FAR_far_src(data)                                                      ((0x00000001&(data))>>0)
#define MIS_U1FAR_get_far(data)                                                      ((0x00000001&(data))>>0)


#define MIS_U1TFR                                                                    0x9801B274
#define MIS_U1TFR_reg_addr                                                           "0x9801B274"
#define MIS_U1TFR_reg                                                                0x9801B274
#define set_MIS_U1TFR_reg(data)   (*((volatile unsigned int*) MIS_U1TFR_reg)=data)
#define get_MIS_U1TFR_reg   (*((volatile unsigned int*) MIS_U1TFR_reg))
#define MIS_U1TFR_inst_adr                                                           "0x009D"
#define MIS_U1TFR_inst                                                               0x009D
#define MIS_U1TFR_far_shift                                                          (0)
#define MIS_U1TFR_far_mask                                                           (0x000000FF)
#define MIS_U1TFR_far(data)                                                          (0x000000FF&((data)<<0))
#define MIS_U1TFR_far_src(data)                                                      ((0x000000FF&(data))>>0)
#define MIS_U1TFR_get_far(data)                                                      ((0x000000FF&(data))>>0)


#define MIS_U1RFW                                                                    0x9801B278
#define MIS_U1RFW_reg_addr                                                           "0x9801B278"
#define MIS_U1RFW_reg                                                                0x9801B278
#define set_MIS_U1RFW_reg(data)   (*((volatile unsigned int*) MIS_U1RFW_reg)=data)
#define get_MIS_U1RFW_reg   (*((volatile unsigned int*) MIS_U1RFW_reg))
#define MIS_U1RFW_inst_adr                                                           "0x009E"
#define MIS_U1RFW_inst                                                               0x009E
#define MIS_U1RFW_rffe_shift                                                         (9)
#define MIS_U1RFW_rffe_mask                                                          (0x00000200)
#define MIS_U1RFW_rffe(data)                                                         (0x00000200&((data)<<9))
#define MIS_U1RFW_rffe_src(data)                                                     ((0x00000200&(data))>>9)
#define MIS_U1RFW_get_rffe(data)                                                     ((0x00000200&(data))>>9)
#define MIS_U1RFW_rfpf_shift                                                         (8)
#define MIS_U1RFW_rfpf_mask                                                          (0x00000100)
#define MIS_U1RFW_rfpf(data)                                                         (0x00000100&((data)<<8))
#define MIS_U1RFW_rfpf_src(data)                                                     ((0x00000100&(data))>>8)
#define MIS_U1RFW_get_rfpf(data)                                                     ((0x00000100&(data))>>8)
#define MIS_U1RFW_rfwd_shift                                                         (0)
#define MIS_U1RFW_rfwd_mask                                                          (0x000000FF)
#define MIS_U1RFW_rfwd(data)                                                         (0x000000FF&((data)<<0))
#define MIS_U1RFW_rfwd_src(data)                                                     ((0x000000FF&(data))>>0)
#define MIS_U1RFW_get_rfwd(data)                                                     ((0x000000FF&(data))>>0)


#define MIS_U1USR                                                                    0x9801B27C
#define MIS_U1USR_reg_addr                                                           "0x9801B27C"
#define MIS_U1USR_reg                                                                0x9801B27C
#define set_MIS_U1USR_reg(data)   (*((volatile unsigned int*) MIS_U1USR_reg)=data)
#define get_MIS_U1USR_reg   (*((volatile unsigned int*) MIS_U1USR_reg))
#define MIS_U1USR_inst_adr                                                           "0x009F"
#define MIS_U1USR_inst                                                               0x009F
#define MIS_U1USR_rff_shift                                                          (4)
#define MIS_U1USR_rff_mask                                                           (0x00000010)
#define MIS_U1USR_rff(data)                                                          (0x00000010&((data)<<4))
#define MIS_U1USR_rff_src(data)                                                      ((0x00000010&(data))>>4)
#define MIS_U1USR_get_rff(data)                                                      ((0x00000010&(data))>>4)
#define MIS_U1USR_rfne_shift                                                         (3)
#define MIS_U1USR_rfne_mask                                                          (0x00000008)
#define MIS_U1USR_rfne(data)                                                         (0x00000008&((data)<<3))
#define MIS_U1USR_rfne_src(data)                                                     ((0x00000008&(data))>>3)
#define MIS_U1USR_get_rfne(data)                                                     ((0x00000008&(data))>>3)
#define MIS_U1USR_tfe_shift                                                          (2)
#define MIS_U1USR_tfe_mask                                                           (0x00000004)
#define MIS_U1USR_tfe(data)                                                          (0x00000004&((data)<<2))
#define MIS_U1USR_tfe_src(data)                                                      ((0x00000004&(data))>>2)
#define MIS_U1USR_get_tfe(data)                                                      ((0x00000004&(data))>>2)
#define MIS_U1USR_tfnf_shift                                                         (1)
#define MIS_U1USR_tfnf_mask                                                          (0x00000002)
#define MIS_U1USR_tfnf(data)                                                         (0x00000002&((data)<<1))
#define MIS_U1USR_tfnf_src(data)                                                     ((0x00000002&(data))>>1)
#define MIS_U1USR_get_tfnf(data)                                                     ((0x00000002&(data))>>1)
#define MIS_U1USR_busy_shift                                                         (0)
#define MIS_U1USR_busy_mask                                                          (0x00000001)
#define MIS_U1USR_busy(data)                                                         (0x00000001&((data)<<0))
#define MIS_U1USR_busy_src(data)                                                     ((0x00000001&(data))>>0)
#define MIS_U1USR_get_busy(data)                                                     ((0x00000001&(data))>>0)


#define MIS_U1TFL                                                                    0x9801B280
#define MIS_U1TFL_reg_addr                                                           "0x9801B280"
#define MIS_U1TFL_reg                                                                0x9801B280
#define set_MIS_U1TFL_reg(data)   (*((volatile unsigned int*) MIS_U1TFL_reg)=data)
#define get_MIS_U1TFL_reg   (*((volatile unsigned int*) MIS_U1TFL_reg))
#define MIS_U1TFL_inst_adr                                                           "0x00A0"
#define MIS_U1TFL_inst                                                               0x00A0
#define MIS_U1TFL_tfl_shift                                                          (0)
#define MIS_U1TFL_tfl_mask                                                           (0x000000FF)
#define MIS_U1TFL_tfl(data)                                                          (0x000000FF&((data)<<0))
#define MIS_U1TFL_tfl_src(data)                                                      ((0x000000FF&(data))>>0)
#define MIS_U1TFL_get_tfl(data)                                                      ((0x000000FF&(data))>>0)


#define MIS_U1RFL                                                                    0x9801B284
#define MIS_U1RFL_reg_addr                                                           "0x9801B284"
#define MIS_U1RFL_reg                                                                0x9801B284
#define set_MIS_U1RFL_reg(data)   (*((volatile unsigned int*) MIS_U1RFL_reg)=data)
#define get_MIS_U1RFL_reg   (*((volatile unsigned int*) MIS_U1RFL_reg))
#define MIS_U1RFL_inst_adr                                                           "0x00A1"
#define MIS_U1RFL_inst                                                               0x00A1
#define MIS_U1RFL_rfl_shift                                                          (0)
#define MIS_U1RFL_rfl_mask                                                           (0x000000FF)
#define MIS_U1RFL_rfl(data)                                                          (0x000000FF&((data)<<0))
#define MIS_U1RFL_rfl_src(data)                                                      ((0x000000FF&(data))>>0)
#define MIS_U1RFL_get_rfl(data)                                                      ((0x000000FF&(data))>>0)


#define MIS_U1SRR                                                                    0x9801B288
#define MIS_U1SRR_reg_addr                                                           "0x9801B288"
#define MIS_U1SRR_reg                                                                0x9801B288
#define set_MIS_U1SRR_reg(data)   (*((volatile unsigned int*) MIS_U1SRR_reg)=data)
#define get_MIS_U1SRR_reg   (*((volatile unsigned int*) MIS_U1SRR_reg))
#define MIS_U1SRR_inst_adr                                                           "0x00A2"
#define MIS_U1SRR_inst                                                               0x00A2
#define MIS_U1SRR_xfr_shift                                                          (2)
#define MIS_U1SRR_xfr_mask                                                           (0x00000004)
#define MIS_U1SRR_xfr(data)                                                          (0x00000004&((data)<<2))
#define MIS_U1SRR_xfr_src(data)                                                      ((0x00000004&(data))>>2)
#define MIS_U1SRR_get_xfr(data)                                                      ((0x00000004&(data))>>2)
#define MIS_U1SRR_rfr_shift                                                          (1)
#define MIS_U1SRR_rfr_mask                                                           (0x00000002)
#define MIS_U1SRR_rfr(data)                                                          (0x00000002&((data)<<1))
#define MIS_U1SRR_rfr_src(data)                                                      ((0x00000002&(data))>>1)
#define MIS_U1SRR_get_rfr(data)                                                      ((0x00000002&(data))>>1)
#define MIS_U1SRR_ur_shift                                                           (0)
#define MIS_U1SRR_ur_mask                                                            (0x00000001)
#define MIS_U1SRR_ur(data)                                                           (0x00000001&((data)<<0))
#define MIS_U1SRR_ur_src(data)                                                       ((0x00000001&(data))>>0)
#define MIS_U1SRR_get_ur(data)                                                       ((0x00000001&(data))>>0)


#define MIS_U1SBCR                                                                   0x9801B290
#define MIS_U1SBCR_reg_addr                                                          "0x9801B290"
#define MIS_U1SBCR_reg                                                               0x9801B290
#define set_MIS_U1SBCR_reg(data)   (*((volatile unsigned int*) MIS_U1SBCR_reg)=data)
#define get_MIS_U1SBCR_reg   (*((volatile unsigned int*) MIS_U1SBCR_reg))
#define MIS_U1SBCR_inst_adr                                                          "0x00A4"
#define MIS_U1SBCR_inst                                                              0x00A4
#define MIS_U1SBCR_sbcr_shift                                                        (0)
#define MIS_U1SBCR_sbcr_mask                                                         (0x00000001)
#define MIS_U1SBCR_sbcr(data)                                                        (0x00000001&((data)<<0))
#define MIS_U1SBCR_sbcr_src(data)                                                    ((0x00000001&(data))>>0)
#define MIS_U1SBCR_get_sbcr(data)                                                    ((0x00000001&(data))>>0)


#define MIS_U1SDMAM                                                                  0x9801B294
#define MIS_U1SDMAM_reg_addr                                                         "0x9801B294"
#define MIS_U1SDMAM_reg                                                              0x9801B294
#define set_MIS_U1SDMAM_reg(data)   (*((volatile unsigned int*) MIS_U1SDMAM_reg)=data)
#define get_MIS_U1SDMAM_reg   (*((volatile unsigned int*) MIS_U1SDMAM_reg))
#define MIS_U1SDMAM_inst_adr                                                         "0x00A5"
#define MIS_U1SDMAM_inst                                                             0x00A5
#define MIS_U1SDMAM_sdmam_shift                                                      (0)
#define MIS_U1SDMAM_sdmam_mask                                                       (0x00000001)
#define MIS_U1SDMAM_sdmam(data)                                                      (0x00000001&((data)<<0))
#define MIS_U1SDMAM_sdmam_src(data)                                                  ((0x00000001&(data))>>0)
#define MIS_U1SDMAM_get_sdmam(data)                                                  ((0x00000001&(data))>>0)


#define MIS_U1SFE                                                                    0x9801B298
#define MIS_U1SFE_reg_addr                                                           "0x9801B298"
#define MIS_U1SFE_reg                                                                0x9801B298
#define set_MIS_U1SFE_reg(data)   (*((volatile unsigned int*) MIS_U1SFE_reg)=data)
#define get_MIS_U1SFE_reg   (*((volatile unsigned int*) MIS_U1SFE_reg))
#define MIS_U1SFE_inst_adr                                                           "0x00A6"
#define MIS_U1SFE_inst                                                               0x00A6
#define MIS_U1SFE_sfe_shift                                                          (0)
#define MIS_U1SFE_sfe_mask                                                           (0x00000001)
#define MIS_U1SFE_sfe(data)                                                          (0x00000001&((data)<<0))
#define MIS_U1SFE_sfe_src(data)                                                      ((0x00000001&(data))>>0)
#define MIS_U1SFE_get_sfe(data)                                                      ((0x00000001&(data))>>0)


#define MIS_U1SRT                                                                    0x9801B29C
#define MIS_U1SRT_reg_addr                                                           "0x9801B29C"
#define MIS_U1SRT_reg                                                                0x9801B29C
#define set_MIS_U1SRT_reg(data)   (*((volatile unsigned int*) MIS_U1SRT_reg)=data)
#define get_MIS_U1SRT_reg   (*((volatile unsigned int*) MIS_U1SRT_reg))
#define MIS_U1SRT_inst_adr                                                           "0x00A7"
#define MIS_U1SRT_inst                                                               0x00A7
#define MIS_U1SRT_srt_shift                                                          (0)
#define MIS_U1SRT_srt_mask                                                           (0x00000003)
#define MIS_U1SRT_srt(data)                                                          (0x00000003&((data)<<0))
#define MIS_U1SRT_srt_src(data)                                                      ((0x00000003&(data))>>0)
#define MIS_U1SRT_get_srt(data)                                                      ((0x00000003&(data))>>0)


#define MIS_U1STET                                                                   0x9801B2A0
#define MIS_U1STET_reg_addr                                                          "0x9801B2A0"
#define MIS_U1STET_reg                                                               0x9801B2A0
#define set_MIS_U1STET_reg(data)   (*((volatile unsigned int*) MIS_U1STET_reg)=data)
#define get_MIS_U1STET_reg   (*((volatile unsigned int*) MIS_U1STET_reg))
#define MIS_U1STET_inst_adr                                                          "0x00A8"
#define MIS_U1STET_inst                                                              0x00A8
#define MIS_U1STET_stet_shift                                                        (0)
#define MIS_U1STET_stet_mask                                                         (0x00000003)
#define MIS_U1STET_stet(data)                                                        (0x00000003&((data)<<0))
#define MIS_U1STET_stet_src(data)                                                    ((0x00000003&(data))>>0)
#define MIS_U1STET_get_stet(data)                                                    ((0x00000003&(data))>>0)


#define MIS_U1HTX                                                                    0x9801B2A4
#define MIS_U1HTX_reg_addr                                                           "0x9801B2A4"
#define MIS_U1HTX_reg                                                                0x9801B2A4
#define set_MIS_U1HTX_reg(data)   (*((volatile unsigned int*) MIS_U1HTX_reg)=data)
#define get_MIS_U1HTX_reg   (*((volatile unsigned int*) MIS_U1HTX_reg))
#define MIS_U1HTX_inst_adr                                                           "0x00A9"
#define MIS_U1HTX_inst                                                               0x00A9
#define MIS_U1HTX_htx_shift                                                          (0)
#define MIS_U1HTX_htx_mask                                                           (0x00000001)
#define MIS_U1HTX_htx(data)                                                          (0x00000001&((data)<<0))
#define MIS_U1HTX_htx_src(data)                                                      ((0x00000001&(data))>>0)
#define MIS_U1HTX_get_htx(data)                                                      ((0x00000001&(data))>>0)


#define MIS_U1DMASA                                                                  0x9801B2A8
#define MIS_U1DMASA_reg_addr                                                         "0x9801B2A8"
#define MIS_U1DMASA_reg                                                              0x9801B2A8
#define set_MIS_U1DMASA_reg(data)   (*((volatile unsigned int*) MIS_U1DMASA_reg)=data)
#define get_MIS_U1DMASA_reg   (*((volatile unsigned int*) MIS_U1DMASA_reg))
#define MIS_U1DMASA_inst_adr                                                         "0x00AA"
#define MIS_U1DMASA_inst                                                             0x00AA
#define MIS_U1DMASA_dmasa_shift                                                      (0)
#define MIS_U1DMASA_dmasa_mask                                                       (0x00000001)
#define MIS_U1DMASA_dmasa(data)                                                      (0x00000001&((data)<<0))
#define MIS_U1DMASA_dmasa_src(data)                                                  ((0x00000001&(data))>>0)
#define MIS_U1DMASA_get_dmasa(data)                                                  ((0x00000001&(data))>>0)


#define MIS_U1CPR                                                                    0x9801B2F4
#define MIS_U1CPR_reg_addr                                                           "0x9801B2F4"
#define MIS_U1CPR_reg                                                                0x9801B2F4
#define set_MIS_U1CPR_reg(data)   (*((volatile unsigned int*) MIS_U1CPR_reg)=data)
#define get_MIS_U1CPR_reg   (*((volatile unsigned int*) MIS_U1CPR_reg))
#define MIS_U1CPR_inst_adr                                                           "0x00BD"
#define MIS_U1CPR_inst                                                               0x00BD
#define MIS_U1CPR_fifo_mode_shift                                                    (16)
#define MIS_U1CPR_fifo_mode_mask                                                     (0x00FF0000)
#define MIS_U1CPR_fifo_mode(data)                                                    (0x00FF0000&((data)<<16))
#define MIS_U1CPR_fifo_mode_src(data)                                                ((0x00FF0000&(data))>>16)
#define MIS_U1CPR_get_fifo_mode(data)                                                ((0x00FF0000&(data))>>16)
#define MIS_U1CPR_dma_extra_shift                                                    (13)
#define MIS_U1CPR_dma_extra_mask                                                     (0x00002000)
#define MIS_U1CPR_dma_extra(data)                                                    (0x00002000&((data)<<13))
#define MIS_U1CPR_dma_extra_src(data)                                                ((0x00002000&(data))>>13)
#define MIS_U1CPR_get_dma_extra(data)                                                ((0x00002000&(data))>>13)
#define MIS_U1CPR_uart_add_encoded_params_shift                                      (12)
#define MIS_U1CPR_uart_add_encoded_params_mask                                       (0x00001000)
#define MIS_U1CPR_uart_add_encoded_params(data)                                      (0x00001000&((data)<<12))
#define MIS_U1CPR_uart_add_encoded_params_src(data)                                  ((0x00001000&(data))>>12)
#define MIS_U1CPR_get_uart_add_encoded_params(data)                                  ((0x00001000&(data))>>12)
#define MIS_U1CPR_shadow_shift                                                       (11)
#define MIS_U1CPR_shadow_mask                                                        (0x00000800)
#define MIS_U1CPR_shadow(data)                                                       (0x00000800&((data)<<11))
#define MIS_U1CPR_shadow_src(data)                                                   ((0x00000800&(data))>>11)
#define MIS_U1CPR_get_shadow(data)                                                   ((0x00000800&(data))>>11)
#define MIS_U1CPR_fifo_stat_shift                                                    (10)
#define MIS_U1CPR_fifo_stat_mask                                                     (0x00000400)
#define MIS_U1CPR_fifo_stat(data)                                                    (0x00000400&((data)<<10))
#define MIS_U1CPR_fifo_stat_src(data)                                                ((0x00000400&(data))>>10)
#define MIS_U1CPR_get_fifo_stat(data)                                                ((0x00000400&(data))>>10)
#define MIS_U1CPR_fifo_access_shift                                                  (9)
#define MIS_U1CPR_fifo_access_mask                                                   (0x00000200)
#define MIS_U1CPR_fifo_access(data)                                                  (0x00000200&((data)<<9))
#define MIS_U1CPR_fifo_access_src(data)                                              ((0x00000200&(data))>>9)
#define MIS_U1CPR_get_fifo_access(data)                                              ((0x00000200&(data))>>9)
#define MIS_U1CPR_additional_feat_shift                                              (8)
#define MIS_U1CPR_additional_feat_mask                                               (0x00000100)
#define MIS_U1CPR_additional_feat(data)                                              (0x00000100&((data)<<8))
#define MIS_U1CPR_additional_feat_src(data)                                          ((0x00000100&(data))>>8)
#define MIS_U1CPR_get_additional_feat(data)                                          ((0x00000100&(data))>>8)
#define MIS_U1CPR_sir_lp_mode_shift                                                  (7)
#define MIS_U1CPR_sir_lp_mode_mask                                                   (0x00000080)
#define MIS_U1CPR_sir_lp_mode(data)                                                  (0x00000080&((data)<<7))
#define MIS_U1CPR_sir_lp_mode_src(data)                                              ((0x00000080&(data))>>7)
#define MIS_U1CPR_get_sir_lp_mode(data)                                              ((0x00000080&(data))>>7)
#define MIS_U1CPR_sir_mode_shift                                                     (6)
#define MIS_U1CPR_sir_mode_mask                                                      (0x00000040)
#define MIS_U1CPR_sir_mode(data)                                                     (0x00000040&((data)<<6))
#define MIS_U1CPR_sir_mode_src(data)                                                 ((0x00000040&(data))>>6)
#define MIS_U1CPR_get_sir_mode(data)                                                 ((0x00000040&(data))>>6)
#define MIS_U1CPR_thre_mode_shift                                                    (5)
#define MIS_U1CPR_thre_mode_mask                                                     (0x00000020)
#define MIS_U1CPR_thre_mode(data)                                                    (0x00000020&((data)<<5))
#define MIS_U1CPR_thre_mode_src(data)                                                ((0x00000020&(data))>>5)
#define MIS_U1CPR_get_thre_mode(data)                                                ((0x00000020&(data))>>5)
#define MIS_U1CPR_afce_mode_shift                                                    (4)
#define MIS_U1CPR_afce_mode_mask                                                     (0x00000010)
#define MIS_U1CPR_afce_mode(data)                                                    (0x00000010&((data)<<4))
#define MIS_U1CPR_afce_mode_src(data)                                                ((0x00000010&(data))>>4)
#define MIS_U1CPR_get_afce_mode(data)                                                ((0x00000010&(data))>>4)
#define MIS_U1CPR_apb_data_width_shift                                               (0)
#define MIS_U1CPR_apb_data_width_mask                                                (0x00000003)
#define MIS_U1CPR_apb_data_width(data)                                               (0x00000003&((data)<<0))
#define MIS_U1CPR_apb_data_width_src(data)                                           ((0x00000003&(data))>>0)
#define MIS_U1CPR_get_apb_data_width(data)                                           ((0x00000003&(data))>>0)


#define MIS_U1UCV                                                                    0x9801B2F8
#define MIS_U1UCV_reg_addr                                                           "0x9801B2F8"
#define MIS_U1UCV_reg                                                                0x9801B2F8
#define set_MIS_U1UCV_reg(data)   (*((volatile unsigned int*) MIS_U1UCV_reg)=data)
#define get_MIS_U1UCV_reg   (*((volatile unsigned int*) MIS_U1UCV_reg))
#define MIS_U1UCV_inst_adr                                                           "0x00BE"
#define MIS_U1UCV_inst                                                               0x00BE
#define MIS_U1UCV_ucv_shift                                                          (0)
#define MIS_U1UCV_ucv_mask                                                           (0xFFFFFFFF)
#define MIS_U1UCV_ucv(data)                                                          (0xFFFFFFFF&((data)<<0))
#define MIS_U1UCV_ucv_src(data)                                                      ((0xFFFFFFFF&(data))>>0)
#define MIS_U1UCV_get_ucv(data)                                                      ((0xFFFFFFFF&(data))>>0)


#define MIS_U1CTR                                                                    0x9801B2FC
#define MIS_U1CTR_reg_addr                                                           "0x9801B2FC"
#define MIS_U1CTR_reg                                                                0x9801B2FC
#define set_MIS_U1CTR_reg(data)   (*((volatile unsigned int*) MIS_U1CTR_reg)=data)
#define get_MIS_U1CTR_reg   (*((volatile unsigned int*) MIS_U1CTR_reg))
#define MIS_U1CTR_inst_adr                                                           "0x00BF"
#define MIS_U1CTR_inst                                                               0x00BF
#define MIS_U1CTR_ctr_shift                                                          (0)
#define MIS_U1CTR_ctr_mask                                                           (0xFFFFFFFF)
#define MIS_U1CTR_ctr(data)                                                          (0xFFFFFFFF&((data)<<0))
#define MIS_U1CTR_ctr_src(data)                                                      ((0xFFFFFFFF&(data))>>0)
#define MIS_U1CTR_get_ctr(data)                                                      ((0xFFFFFFFF&(data))>>0)


#define MIS_U2RBR_THR_DLL                                                            0x9801B400
#define MIS_U2RBR_THR_DLL_reg_addr                                                   "0x9801B400"
#define MIS_U2RBR_THR_DLL_reg                                                        0x9801B400
#define set_MIS_U2RBR_THR_DLL_reg(data)   (*((volatile unsigned int*) MIS_U2RBR_THR_DLL_reg)=data)
#define get_MIS_U2RBR_THR_DLL_reg   (*((volatile unsigned int*) MIS_U2RBR_THR_DLL_reg))
#define MIS_U2RBR_THR_DLL_inst_adr                                                   "0x0000"
#define MIS_U2RBR_THR_DLL_inst                                                       0x0000
#define MIS_U2RBR_THR_DLL_dll_shift                                                  (0)
#define MIS_U2RBR_THR_DLL_dll_mask                                                   (0x000000FF)
#define MIS_U2RBR_THR_DLL_dll(data)                                                  (0x000000FF&((data)<<0))
#define MIS_U2RBR_THR_DLL_dll_src(data)                                              ((0x000000FF&(data))>>0)
#define MIS_U2RBR_THR_DLL_get_dll(data)                                              ((0x000000FF&(data))>>0)


#define MIS_U2IER_DLH                                                                0x9801B404
#define MIS_U2IER_DLH_reg_addr                                                       "0x9801B404"
#define MIS_U2IER_DLH_reg                                                            0x9801B404
#define set_MIS_U2IER_DLH_reg(data)   (*((volatile unsigned int*) MIS_U2IER_DLH_reg)=data)
#define get_MIS_U2IER_DLH_reg   (*((volatile unsigned int*) MIS_U2IER_DLH_reg))
#define MIS_U2IER_DLH_inst_adr                                                       "0x0001"
#define MIS_U2IER_DLH_inst                                                           0x0001
#define MIS_U2IER_DLH_dlh_shift                                                      (0)
#define MIS_U2IER_DLH_dlh_mask                                                       (0x000000FF)
#define MIS_U2IER_DLH_dlh(data)                                                      (0x000000FF&((data)<<0))
#define MIS_U2IER_DLH_dlh_src(data)                                                  ((0x000000FF&(data))>>0)
#define MIS_U2IER_DLH_get_dlh(data)                                                  ((0x000000FF&(data))>>0)


#define MIS_U2IIR_FCR                                                                0x9801B408
#define MIS_U2IIR_FCR_reg_addr                                                       "0x9801B408"
#define MIS_U2IIR_FCR_reg                                                            0x9801B408
#define set_MIS_U2IIR_FCR_reg(data)   (*((volatile unsigned int*) MIS_U2IIR_FCR_reg)=data)
#define get_MIS_U2IIR_FCR_reg   (*((volatile unsigned int*) MIS_U2IIR_FCR_reg))
#define MIS_U2IIR_FCR_inst_adr                                                       "0x0002"
#define MIS_U2IIR_FCR_inst                                                           0x0002
#define MIS_U2IIR_FCR_fifo16_shift                                                   (6)
#define MIS_U2IIR_FCR_fifo16_mask                                                    (0x000000C0)
#define MIS_U2IIR_FCR_fifo16(data)                                                   (0x000000C0&((data)<<6))
#define MIS_U2IIR_FCR_fifo16_src(data)                                               ((0x000000C0&(data))>>6)
#define MIS_U2IIR_FCR_get_fifo16(data)                                               ((0x000000C0&(data))>>6)
#define MIS_U2IIR_FCR_iid_shift                                                      (0)
#define MIS_U2IIR_FCR_iid_mask                                                       (0x0000000F)
#define MIS_U2IIR_FCR_iid(data)                                                      (0x0000000F&((data)<<0))
#define MIS_U2IIR_FCR_iid_src(data)                                                  ((0x0000000F&(data))>>0)
#define MIS_U2IIR_FCR_get_iid(data)                                                  ((0x0000000F&(data))>>0)


#define MIS_U2LCR                                                                    0x9801B40C
#define MIS_U2LCR_reg_addr                                                           "0x9801B40C"
#define MIS_U2LCR_reg                                                                0x9801B40C
#define set_MIS_U2LCR_reg(data)   (*((volatile unsigned int*) MIS_U2LCR_reg)=data)
#define get_MIS_U2LCR_reg   (*((volatile unsigned int*) MIS_U2LCR_reg))
#define MIS_U2LCR_inst_adr                                                           "0x0003"
#define MIS_U2LCR_inst                                                               0x0003
#define MIS_U2LCR_dlab_shift                                                         (7)
#define MIS_U2LCR_dlab_mask                                                          (0x00000080)
#define MIS_U2LCR_dlab(data)                                                         (0x00000080&((data)<<7))
#define MIS_U2LCR_dlab_src(data)                                                     ((0x00000080&(data))>>7)
#define MIS_U2LCR_get_dlab(data)                                                     ((0x00000080&(data))>>7)
#define MIS_U2LCR_brk_shift                                                          (6)
#define MIS_U2LCR_brk_mask                                                           (0x00000040)
#define MIS_U2LCR_brk(data)                                                          (0x00000040&((data)<<6))
#define MIS_U2LCR_brk_src(data)                                                      ((0x00000040&(data))>>6)
#define MIS_U2LCR_get_brk(data)                                                      ((0x00000040&(data))>>6)
#define MIS_U2LCR_eps_shift                                                          (4)
#define MIS_U2LCR_eps_mask                                                           (0x00000010)
#define MIS_U2LCR_eps(data)                                                          (0x00000010&((data)<<4))
#define MIS_U2LCR_eps_src(data)                                                      ((0x00000010&(data))>>4)
#define MIS_U2LCR_get_eps(data)                                                      ((0x00000010&(data))>>4)
#define MIS_U2LCR_pen_shift                                                          (3)
#define MIS_U2LCR_pen_mask                                                           (0x00000008)
#define MIS_U2LCR_pen(data)                                                          (0x00000008&((data)<<3))
#define MIS_U2LCR_pen_src(data)                                                      ((0x00000008&(data))>>3)
#define MIS_U2LCR_get_pen(data)                                                      ((0x00000008&(data))>>3)
#define MIS_U2LCR_stb_shift                                                          (2)
#define MIS_U2LCR_stb_mask                                                           (0x00000004)
#define MIS_U2LCR_stb(data)                                                          (0x00000004&((data)<<2))
#define MIS_U2LCR_stb_src(data)                                                      ((0x00000004&(data))>>2)
#define MIS_U2LCR_get_stb(data)                                                      ((0x00000004&(data))>>2)
#define MIS_U2LCR_wls_shift                                                          (0)
#define MIS_U2LCR_wls_mask                                                           (0x00000003)
#define MIS_U2LCR_wls(data)                                                          (0x00000003&((data)<<0))
#define MIS_U2LCR_wls_src(data)                                                      ((0x00000003&(data))>>0)
#define MIS_U2LCR_get_wls(data)                                                      ((0x00000003&(data))>>0)


#define MIS_U2MCR                                                                    0x9801B410
#define MIS_U2MCR_reg_addr                                                           "0x9801B410"
#define MIS_U2MCR_reg                                                                0x9801B410
#define set_MIS_U2MCR_reg(data)   (*((volatile unsigned int*) MIS_U2MCR_reg)=data)
#define get_MIS_U2MCR_reg   (*((volatile unsigned int*) MIS_U2MCR_reg))
#define MIS_U2MCR_inst_adr                                                           "0x0004"
#define MIS_U2MCR_inst                                                               0x0004
#define MIS_U2MCR_afce_shift                                                         (5)
#define MIS_U2MCR_afce_mask                                                          (0x00000020)
#define MIS_U2MCR_afce(data)                                                         (0x00000020&((data)<<5))
#define MIS_U2MCR_afce_src(data)                                                     ((0x00000020&(data))>>5)
#define MIS_U2MCR_get_afce(data)                                                     ((0x00000020&(data))>>5)
#define MIS_U2MCR_loop_shift                                                         (4)
#define MIS_U2MCR_loop_mask                                                          (0x00000010)
#define MIS_U2MCR_loop(data)                                                         (0x00000010&((data)<<4))
#define MIS_U2MCR_loop_src(data)                                                     ((0x00000010&(data))>>4)
#define MIS_U2MCR_get_loop(data)                                                     ((0x00000010&(data))>>4)
#define MIS_U2MCR_rts_shift                                                          (1)
#define MIS_U2MCR_rts_mask                                                           (0x00000002)
#define MIS_U2MCR_rts(data)                                                          (0x00000002&((data)<<1))
#define MIS_U2MCR_rts_src(data)                                                      ((0x00000002&(data))>>1)
#define MIS_U2MCR_get_rts(data)                                                      ((0x00000002&(data))>>1)
#define MIS_U2MCR_dtr_shift                                                          (0)
#define MIS_U2MCR_dtr_mask                                                           (0x00000001)
#define MIS_U2MCR_dtr(data)                                                          (0x00000001&((data)<<0))
#define MIS_U2MCR_dtr_src(data)                                                      ((0x00000001&(data))>>0)
#define MIS_U2MCR_get_dtr(data)                                                      ((0x00000001&(data))>>0)


#define MIS_U2LSR                                                                    0x9801B414
#define MIS_U2LSR_reg_addr                                                           "0x9801B414"
#define MIS_U2LSR_reg                                                                0x9801B414
#define set_MIS_U2LSR_reg(data)   (*((volatile unsigned int*) MIS_U2LSR_reg)=data)
#define get_MIS_U2LSR_reg   (*((volatile unsigned int*) MIS_U2LSR_reg))
#define MIS_U2LSR_inst_adr                                                           "0x0005"
#define MIS_U2LSR_inst                                                               0x0005
#define MIS_U2LSR_rfe_shift                                                          (7)
#define MIS_U2LSR_rfe_mask                                                           (0x00000080)
#define MIS_U2LSR_rfe(data)                                                          (0x00000080&((data)<<7))
#define MIS_U2LSR_rfe_src(data)                                                      ((0x00000080&(data))>>7)
#define MIS_U2LSR_get_rfe(data)                                                      ((0x00000080&(data))>>7)
#define MIS_U2LSR_temt_shift                                                         (6)
#define MIS_U2LSR_temt_mask                                                          (0x00000040)
#define MIS_U2LSR_temt(data)                                                         (0x00000040&((data)<<6))
#define MIS_U2LSR_temt_src(data)                                                     ((0x00000040&(data))>>6)
#define MIS_U2LSR_get_temt(data)                                                     ((0x00000040&(data))>>6)
#define MIS_U2LSR_thre_shift                                                         (5)
#define MIS_U2LSR_thre_mask                                                          (0x00000020)
#define MIS_U2LSR_thre(data)                                                         (0x00000020&((data)<<5))
#define MIS_U2LSR_thre_src(data)                                                     ((0x00000020&(data))>>5)
#define MIS_U2LSR_get_thre(data)                                                     ((0x00000020&(data))>>5)
#define MIS_U2LSR_bi_shift                                                           (4)
#define MIS_U2LSR_bi_mask                                                            (0x00000010)
#define MIS_U2LSR_bi(data)                                                           (0x00000010&((data)<<4))
#define MIS_U2LSR_bi_src(data)                                                       ((0x00000010&(data))>>4)
#define MIS_U2LSR_get_bi(data)                                                       ((0x00000010&(data))>>4)
#define MIS_U2LSR_fe_shift                                                           (3)
#define MIS_U2LSR_fe_mask                                                            (0x00000008)
#define MIS_U2LSR_fe(data)                                                           (0x00000008&((data)<<3))
#define MIS_U2LSR_fe_src(data)                                                       ((0x00000008&(data))>>3)
#define MIS_U2LSR_get_fe(data)                                                       ((0x00000008&(data))>>3)
#define MIS_U2LSR_pe_shift                                                           (2)
#define MIS_U2LSR_pe_mask                                                            (0x00000004)
#define MIS_U2LSR_pe(data)                                                           (0x00000004&((data)<<2))
#define MIS_U2LSR_pe_src(data)                                                       ((0x00000004&(data))>>2)
#define MIS_U2LSR_get_pe(data)                                                       ((0x00000004&(data))>>2)
#define MIS_U2LSR_oe_shift                                                           (1)
#define MIS_U2LSR_oe_mask                                                            (0x00000002)
#define MIS_U2LSR_oe(data)                                                           (0x00000002&((data)<<1))
#define MIS_U2LSR_oe_src(data)                                                       ((0x00000002&(data))>>1)
#define MIS_U2LSR_get_oe(data)                                                       ((0x00000002&(data))>>1)
#define MIS_U2LSR_dr_shift                                                           (0)
#define MIS_U2LSR_dr_mask                                                            (0x00000001)
#define MIS_U2LSR_dr(data)                                                           (0x00000001&((data)<<0))
#define MIS_U2LSR_dr_src(data)                                                       ((0x00000001&(data))>>0)
#define MIS_U2LSR_get_dr(data)                                                       ((0x00000001&(data))>>0)


#define MIS_U2MSR                                                                    0x9801B418
#define MIS_U2MSR_reg_addr                                                           "0x9801B418"
#define MIS_U2MSR_reg                                                                0x9801B418
#define set_MIS_U2MSR_reg(data)   (*((volatile unsigned int*) MIS_U2MSR_reg)=data)
#define get_MIS_U2MSR_reg   (*((volatile unsigned int*) MIS_U2MSR_reg))
#define MIS_U2MSR_inst_adr                                                           "0x0006"
#define MIS_U2MSR_inst                                                               0x0006
#define MIS_U2MSR_dcd_shift                                                          (7)
#define MIS_U2MSR_dcd_mask                                                           (0x00000080)
#define MIS_U2MSR_dcd(data)                                                          (0x00000080&((data)<<7))
#define MIS_U2MSR_dcd_src(data)                                                      ((0x00000080&(data))>>7)
#define MIS_U2MSR_get_dcd(data)                                                      ((0x00000080&(data))>>7)
#define MIS_U2MSR_ri_shift                                                           (6)
#define MIS_U2MSR_ri_mask                                                            (0x00000040)
#define MIS_U2MSR_ri(data)                                                           (0x00000040&((data)<<6))
#define MIS_U2MSR_ri_src(data)                                                       ((0x00000040&(data))>>6)
#define MIS_U2MSR_get_ri(data)                                                       ((0x00000040&(data))>>6)
#define MIS_U2MSR_dsr_shift                                                          (5)
#define MIS_U2MSR_dsr_mask                                                           (0x00000020)
#define MIS_U2MSR_dsr(data)                                                          (0x00000020&((data)<<5))
#define MIS_U2MSR_dsr_src(data)                                                      ((0x00000020&(data))>>5)
#define MIS_U2MSR_get_dsr(data)                                                      ((0x00000020&(data))>>5)
#define MIS_U2MSR_cts_shift                                                          (4)
#define MIS_U2MSR_cts_mask                                                           (0x00000010)
#define MIS_U2MSR_cts(data)                                                          (0x00000010&((data)<<4))
#define MIS_U2MSR_cts_src(data)                                                      ((0x00000010&(data))>>4)
#define MIS_U2MSR_get_cts(data)                                                      ((0x00000010&(data))>>4)
#define MIS_U2MSR_ddcd_shift                                                         (3)
#define MIS_U2MSR_ddcd_mask                                                          (0x00000008)
#define MIS_U2MSR_ddcd(data)                                                         (0x00000008&((data)<<3))
#define MIS_U2MSR_ddcd_src(data)                                                     ((0x00000008&(data))>>3)
#define MIS_U2MSR_get_ddcd(data)                                                     ((0x00000008&(data))>>3)
#define MIS_U2MSR_teri_shift                                                         (2)
#define MIS_U2MSR_teri_mask                                                          (0x00000004)
#define MIS_U2MSR_teri(data)                                                         (0x00000004&((data)<<2))
#define MIS_U2MSR_teri_src(data)                                                     ((0x00000004&(data))>>2)
#define MIS_U2MSR_get_teri(data)                                                     ((0x00000004&(data))>>2)
#define MIS_U2MSR_ddsr_shift                                                         (1)
#define MIS_U2MSR_ddsr_mask                                                          (0x00000002)
#define MIS_U2MSR_ddsr(data)                                                         (0x00000002&((data)<<1))
#define MIS_U2MSR_ddsr_src(data)                                                     ((0x00000002&(data))>>1)
#define MIS_U2MSR_get_ddsr(data)                                                     ((0x00000002&(data))>>1)
#define MIS_U2MSR_dcts_shift                                                         (0)
#define MIS_U2MSR_dcts_mask                                                          (0x00000001)
#define MIS_U2MSR_dcts(data)                                                         (0x00000001&((data)<<0))
#define MIS_U2MSR_dcts_src(data)                                                     ((0x00000001&(data))>>0)
#define MIS_U2MSR_get_dcts(data)                                                     ((0x00000001&(data))>>0)


#define MIS_U2SCR                                                                    0x9801B41C
#define MIS_U2SCR_reg_addr                                                           "0x9801B41C"
#define MIS_U2SCR_reg                                                                0x9801B41C
#define set_MIS_U2SCR_reg(data)   (*((volatile unsigned int*) MIS_U2SCR_reg)=data)
#define get_MIS_U2SCR_reg   (*((volatile unsigned int*) MIS_U2SCR_reg))
#define MIS_U2SCR_inst_adr                                                           "0x0007"
#define MIS_U2SCR_inst                                                               0x0007
#define MIS_U2SCR_scr_shift                                                          (0)
#define MIS_U2SCR_scr_mask                                                           (0x000000FF)
#define MIS_U2SCR_scr(data)                                                          (0x000000FF&((data)<<0))
#define MIS_U2SCR_scr_src(data)                                                      ((0x000000FF&(data))>>0)
#define MIS_U2SCR_get_scr(data)                                                      ((0x000000FF&(data))>>0)


#define MIS_U2SRBR_0                                                                 0x9801B430
#define MIS_U2SRBR_1                                                                 0x9801B434
#define MIS_U2SRBR_2                                                                 0x9801B438
#define MIS_U2SRBR_3                                                                 0x9801B43C
#define MIS_U2SRBR_4                                                                 0x9801B440
#define MIS_U2SRBR_5                                                                 0x9801B444
#define MIS_U2SRBR_6                                                                 0x9801B448
#define MIS_U2SRBR_7                                                                 0x9801B44C
#define MIS_U2SRBR_8                                                                 0x9801B450
#define MIS_U2SRBR_9                                                                 0x9801B454
#define MIS_U2SRBR_10                                                                 0x9801B458
#define MIS_U2SRBR_11                                                                 0x9801B45C
#define MIS_U2SRBR_12                                                                 0x9801B460
#define MIS_U2SRBR_13                                                                 0x9801B464
#define MIS_U2SRBR_14                                                                 0x9801B468
#define MIS_U2SRBR_15                                                                 0x9801B46C
#define MIS_U2SRBR_0_reg_addr                                                        "0x9801B430"
#define MIS_U2SRBR_1_reg_addr                                                        "0x9801B434"
#define MIS_U2SRBR_2_reg_addr                                                        "0x9801B438"
#define MIS_U2SRBR_3_reg_addr                                                        "0x9801B43C"
#define MIS_U2SRBR_4_reg_addr                                                        "0x9801B440"
#define MIS_U2SRBR_5_reg_addr                                                        "0x9801B444"
#define MIS_U2SRBR_6_reg_addr                                                        "0x9801B448"
#define MIS_U2SRBR_7_reg_addr                                                        "0x9801B44C"
#define MIS_U2SRBR_8_reg_addr                                                        "0x9801B450"
#define MIS_U2SRBR_9_reg_addr                                                        "0x9801B454"
#define MIS_U2SRBR_10_reg_addr                                                        "0x9801B458"
#define MIS_U2SRBR_11_reg_addr                                                        "0x9801B45C"
#define MIS_U2SRBR_12_reg_addr                                                        "0x9801B460"
#define MIS_U2SRBR_13_reg_addr                                                        "0x9801B464"
#define MIS_U2SRBR_14_reg_addr                                                        "0x9801B468"
#define MIS_U2SRBR_15_reg_addr                                                        "0x9801B46C"
#define MIS_U2SRBR_0_reg                                                             0x9801B430
#define MIS_U2SRBR_1_reg                                                             0x9801B434
#define MIS_U2SRBR_2_reg                                                             0x9801B438
#define MIS_U2SRBR_3_reg                                                             0x9801B43C
#define MIS_U2SRBR_4_reg                                                             0x9801B440
#define MIS_U2SRBR_5_reg                                                             0x9801B444
#define MIS_U2SRBR_6_reg                                                             0x9801B448
#define MIS_U2SRBR_7_reg                                                             0x9801B44C
#define MIS_U2SRBR_8_reg                                                             0x9801B450
#define MIS_U2SRBR_9_reg                                                             0x9801B454
#define MIS_U2SRBR_10_reg                                                             0x9801B458
#define MIS_U2SRBR_11_reg                                                             0x9801B45C
#define MIS_U2SRBR_12_reg                                                             0x9801B460
#define MIS_U2SRBR_13_reg                                                             0x9801B464
#define MIS_U2SRBR_14_reg                                                             0x9801B468
#define MIS_U2SRBR_15_reg                                                             0x9801B46C
#define set_MIS_U2SRBR_0_reg(data)   (*((volatile unsigned int*) MIS_U2SRBR_0_reg)=data)
#define set_MIS_U2SRBR_1_reg(data)   (*((volatile unsigned int*) MIS_U2SRBR_1_reg)=data)
#define set_MIS_U2SRBR_2_reg(data)   (*((volatile unsigned int*) MIS_U2SRBR_2_reg)=data)
#define set_MIS_U2SRBR_3_reg(data)   (*((volatile unsigned int*) MIS_U2SRBR_3_reg)=data)
#define set_MIS_U2SRBR_4_reg(data)   (*((volatile unsigned int*) MIS_U2SRBR_4_reg)=data)
#define set_MIS_U2SRBR_5_reg(data)   (*((volatile unsigned int*) MIS_U2SRBR_5_reg)=data)
#define set_MIS_U2SRBR_6_reg(data)   (*((volatile unsigned int*) MIS_U2SRBR_6_reg)=data)
#define set_MIS_U2SRBR_7_reg(data)   (*((volatile unsigned int*) MIS_U2SRBR_7_reg)=data)
#define set_MIS_U2SRBR_8_reg(data)   (*((volatile unsigned int*) MIS_U2SRBR_8_reg)=data)
#define set_MIS_U2SRBR_9_reg(data)   (*((volatile unsigned int*) MIS_U2SRBR_9_reg)=data)
#define set_MIS_U2SRBR_10_reg(data)   (*((volatile unsigned int*) MIS_U2SRBR_10_reg)=data)
#define set_MIS_U2SRBR_11_reg(data)   (*((volatile unsigned int*) MIS_U2SRBR_11_reg)=data)
#define set_MIS_U2SRBR_12_reg(data)   (*((volatile unsigned int*) MIS_U2SRBR_12_reg)=data)
#define set_MIS_U2SRBR_13_reg(data)   (*((volatile unsigned int*) MIS_U2SRBR_13_reg)=data)
#define set_MIS_U2SRBR_14_reg(data)   (*((volatile unsigned int*) MIS_U2SRBR_14_reg)=data)
#define set_MIS_U2SRBR_15_reg(data)   (*((volatile unsigned int*) MIS_U2SRBR_15_reg)=data)
#define get_MIS_U2SRBR_0_reg   (*((volatile unsigned int*) MIS_U2SRBR_0_reg))
#define get_MIS_U2SRBR_1_reg   (*((volatile unsigned int*) MIS_U2SRBR_1_reg))
#define get_MIS_U2SRBR_2_reg   (*((volatile unsigned int*) MIS_U2SRBR_2_reg))
#define get_MIS_U2SRBR_3_reg   (*((volatile unsigned int*) MIS_U2SRBR_3_reg))
#define get_MIS_U2SRBR_4_reg   (*((volatile unsigned int*) MIS_U2SRBR_4_reg))
#define get_MIS_U2SRBR_5_reg   (*((volatile unsigned int*) MIS_U2SRBR_5_reg))
#define get_MIS_U2SRBR_6_reg   (*((volatile unsigned int*) MIS_U2SRBR_6_reg))
#define get_MIS_U2SRBR_7_reg   (*((volatile unsigned int*) MIS_U2SRBR_7_reg))
#define get_MIS_U2SRBR_8_reg   (*((volatile unsigned int*) MIS_U2SRBR_8_reg))
#define get_MIS_U2SRBR_9_reg   (*((volatile unsigned int*) MIS_U2SRBR_9_reg))
#define get_MIS_U2SRBR_10_reg   (*((volatile unsigned int*) MIS_U2SRBR_10_reg))
#define get_MIS_U2SRBR_11_reg   (*((volatile unsigned int*) MIS_U2SRBR_11_reg))
#define get_MIS_U2SRBR_12_reg   (*((volatile unsigned int*) MIS_U2SRBR_12_reg))
#define get_MIS_U2SRBR_13_reg   (*((volatile unsigned int*) MIS_U2SRBR_13_reg))
#define get_MIS_U2SRBR_14_reg   (*((volatile unsigned int*) MIS_U2SRBR_14_reg))
#define get_MIS_U2SRBR_15_reg   (*((volatile unsigned int*) MIS_U2SRBR_15_reg))
#define MIS_U2SRBR_0_inst_adr                                                        "0x000C"
#define MIS_U2SRBR_1_inst_adr                                                        "0x000D"
#define MIS_U2SRBR_2_inst_adr                                                        "0x000E"
#define MIS_U2SRBR_3_inst_adr                                                        "0x000F"
#define MIS_U2SRBR_4_inst_adr                                                        "0x0010"
#define MIS_U2SRBR_5_inst_adr                                                        "0x0011"
#define MIS_U2SRBR_6_inst_adr                                                        "0x0012"
#define MIS_U2SRBR_7_inst_adr                                                        "0x0013"
#define MIS_U2SRBR_8_inst_adr                                                        "0x0014"
#define MIS_U2SRBR_9_inst_adr                                                        "0x0015"
#define MIS_U2SRBR_10_inst_adr                                                        "0x0016"
#define MIS_U2SRBR_11_inst_adr                                                        "0x0017"
#define MIS_U2SRBR_12_inst_adr                                                        "0x0018"
#define MIS_U2SRBR_13_inst_adr                                                        "0x0019"
#define MIS_U2SRBR_14_inst_adr                                                        "0x001A"
#define MIS_U2SRBR_15_inst_adr                                                        "0x001B"
#define MIS_U2SRBR_0_inst                                                            0x000C
#define MIS_U2SRBR_1_inst                                                            0x000D
#define MIS_U2SRBR_2_inst                                                            0x000E
#define MIS_U2SRBR_3_inst                                                            0x000F
#define MIS_U2SRBR_4_inst                                                            0x0010
#define MIS_U2SRBR_5_inst                                                            0x0011
#define MIS_U2SRBR_6_inst                                                            0x0012
#define MIS_U2SRBR_7_inst                                                            0x0013
#define MIS_U2SRBR_8_inst                                                            0x0014
#define MIS_U2SRBR_9_inst                                                            0x0015
#define MIS_U2SRBR_10_inst                                                            0x0016
#define MIS_U2SRBR_11_inst                                                            0x0017
#define MIS_U2SRBR_12_inst                                                            0x0018
#define MIS_U2SRBR_13_inst                                                            0x0019
#define MIS_U2SRBR_14_inst                                                            0x001A
#define MIS_U2SRBR_15_inst                                                            0x001B
#define MIS_U2SRBR_rbd_shift                                                         (0)
#define MIS_U2SRBR_rbd_mask                                                          (0x000000FF)
#define MIS_U2SRBR_rbd(data)                                                         (0x000000FF&((data)<<0))
#define MIS_U2SRBR_rbd_src(data)                                                     ((0x000000FF&(data))>>0)
#define MIS_U2SRBR_get_rbd(data)                                                     ((0x000000FF&(data))>>0)


#define MIS_U2FAR                                                                    0x9801B470
#define MIS_U2FAR_reg_addr                                                           "0x9801B470"
#define MIS_U2FAR_reg                                                                0x9801B470
#define set_MIS_U2FAR_reg(data)   (*((volatile unsigned int*) MIS_U2FAR_reg)=data)
#define get_MIS_U2FAR_reg   (*((volatile unsigned int*) MIS_U2FAR_reg))
#define MIS_U2FAR_inst_adr                                                           "0x001C"
#define MIS_U2FAR_inst                                                               0x001C
#define MIS_U2FAR_far_shift                                                          (0)
#define MIS_U2FAR_far_mask                                                           (0x00000001)
#define MIS_U2FAR_far(data)                                                          (0x00000001&((data)<<0))
#define MIS_U2FAR_far_src(data)                                                      ((0x00000001&(data))>>0)
#define MIS_U2FAR_get_far(data)                                                      ((0x00000001&(data))>>0)


#define MIS_U2TFR                                                                    0x9801B474
#define MIS_U2TFR_reg_addr                                                           "0x9801B474"
#define MIS_U2TFR_reg                                                                0x9801B474
#define set_MIS_U2TFR_reg(data)   (*((volatile unsigned int*) MIS_U2TFR_reg)=data)
#define get_MIS_U2TFR_reg   (*((volatile unsigned int*) MIS_U2TFR_reg))
#define MIS_U2TFR_inst_adr                                                           "0x001D"
#define MIS_U2TFR_inst                                                               0x001D
#define MIS_U2TFR_far_shift                                                          (0)
#define MIS_U2TFR_far_mask                                                           (0x000000FF)
#define MIS_U2TFR_far(data)                                                          (0x000000FF&((data)<<0))
#define MIS_U2TFR_far_src(data)                                                      ((0x000000FF&(data))>>0)
#define MIS_U2TFR_get_far(data)                                                      ((0x000000FF&(data))>>0)


#define MIS_U2RFW                                                                    0x9801B478
#define MIS_U2RFW_reg_addr                                                           "0x9801B478"
#define MIS_U2RFW_reg                                                                0x9801B478
#define set_MIS_U2RFW_reg(data)   (*((volatile unsigned int*) MIS_U2RFW_reg)=data)
#define get_MIS_U2RFW_reg   (*((volatile unsigned int*) MIS_U2RFW_reg))
#define MIS_U2RFW_inst_adr                                                           "0x001E"
#define MIS_U2RFW_inst                                                               0x001E
#define MIS_U2RFW_rffe_shift                                                         (9)
#define MIS_U2RFW_rffe_mask                                                          (0x00000200)
#define MIS_U2RFW_rffe(data)                                                         (0x00000200&((data)<<9))
#define MIS_U2RFW_rffe_src(data)                                                     ((0x00000200&(data))>>9)
#define MIS_U2RFW_get_rffe(data)                                                     ((0x00000200&(data))>>9)
#define MIS_U2RFW_rfpf_shift                                                         (8)
#define MIS_U2RFW_rfpf_mask                                                          (0x00000100)
#define MIS_U2RFW_rfpf(data)                                                         (0x00000100&((data)<<8))
#define MIS_U2RFW_rfpf_src(data)                                                     ((0x00000100&(data))>>8)
#define MIS_U2RFW_get_rfpf(data)                                                     ((0x00000100&(data))>>8)
#define MIS_U2RFW_rfwd_shift                                                         (0)
#define MIS_U2RFW_rfwd_mask                                                          (0x000000FF)
#define MIS_U2RFW_rfwd(data)                                                         (0x000000FF&((data)<<0))
#define MIS_U2RFW_rfwd_src(data)                                                     ((0x000000FF&(data))>>0)
#define MIS_U2RFW_get_rfwd(data)                                                     ((0x000000FF&(data))>>0)


#define MIS_U2USR                                                                    0x9801B47C
#define MIS_U2USR_reg_addr                                                           "0x9801B47C"
#define MIS_U2USR_reg                                                                0x9801B47C
#define set_MIS_U2USR_reg(data)   (*((volatile unsigned int*) MIS_U2USR_reg)=data)
#define get_MIS_U2USR_reg   (*((volatile unsigned int*) MIS_U2USR_reg))
#define MIS_U2USR_inst_adr                                                           "0x001F"
#define MIS_U2USR_inst                                                               0x001F
#define MIS_U2USR_rff_shift                                                          (4)
#define MIS_U2USR_rff_mask                                                           (0x00000010)
#define MIS_U2USR_rff(data)                                                          (0x00000010&((data)<<4))
#define MIS_U2USR_rff_src(data)                                                      ((0x00000010&(data))>>4)
#define MIS_U2USR_get_rff(data)                                                      ((0x00000010&(data))>>4)
#define MIS_U2USR_rfne_shift                                                         (3)
#define MIS_U2USR_rfne_mask                                                          (0x00000008)
#define MIS_U2USR_rfne(data)                                                         (0x00000008&((data)<<3))
#define MIS_U2USR_rfne_src(data)                                                     ((0x00000008&(data))>>3)
#define MIS_U2USR_get_rfne(data)                                                     ((0x00000008&(data))>>3)
#define MIS_U2USR_tfe_shift                                                          (2)
#define MIS_U2USR_tfe_mask                                                           (0x00000004)
#define MIS_U2USR_tfe(data)                                                          (0x00000004&((data)<<2))
#define MIS_U2USR_tfe_src(data)                                                      ((0x00000004&(data))>>2)
#define MIS_U2USR_get_tfe(data)                                                      ((0x00000004&(data))>>2)
#define MIS_U2USR_tfnf_shift                                                         (1)
#define MIS_U2USR_tfnf_mask                                                          (0x00000002)
#define MIS_U2USR_tfnf(data)                                                         (0x00000002&((data)<<1))
#define MIS_U2USR_tfnf_src(data)                                                     ((0x00000002&(data))>>1)
#define MIS_U2USR_get_tfnf(data)                                                     ((0x00000002&(data))>>1)
#define MIS_U2USR_busy_shift                                                         (0)
#define MIS_U2USR_busy_mask                                                          (0x00000001)
#define MIS_U2USR_busy(data)                                                         (0x00000001&((data)<<0))
#define MIS_U2USR_busy_src(data)                                                     ((0x00000001&(data))>>0)
#define MIS_U2USR_get_busy(data)                                                     ((0x00000001&(data))>>0)


#define MIS_U2TFL                                                                    0x9801B480
#define MIS_U2TFL_reg_addr                                                           "0x9801B480"
#define MIS_U2TFL_reg                                                                0x9801B480
#define set_MIS_U2TFL_reg(data)   (*((volatile unsigned int*) MIS_U2TFL_reg)=data)
#define get_MIS_U2TFL_reg   (*((volatile unsigned int*) MIS_U2TFL_reg))
#define MIS_U2TFL_inst_adr                                                           "0x0020"
#define MIS_U2TFL_inst                                                               0x0020
#define MIS_U2TFL_tfl_shift                                                          (0)
#define MIS_U2TFL_tfl_mask                                                           (0x000000FF)
#define MIS_U2TFL_tfl(data)                                                          (0x000000FF&((data)<<0))
#define MIS_U2TFL_tfl_src(data)                                                      ((0x000000FF&(data))>>0)
#define MIS_U2TFL_get_tfl(data)                                                      ((0x000000FF&(data))>>0)


#define MIS_U2RFL                                                                    0x9801B484
#define MIS_U2RFL_reg_addr                                                           "0x9801B484"
#define MIS_U2RFL_reg                                                                0x9801B484
#define set_MIS_U2RFL_reg(data)   (*((volatile unsigned int*) MIS_U2RFL_reg)=data)
#define get_MIS_U2RFL_reg   (*((volatile unsigned int*) MIS_U2RFL_reg))
#define MIS_U2RFL_inst_adr                                                           "0x0021"
#define MIS_U2RFL_inst                                                               0x0021
#define MIS_U2RFL_rfl_shift                                                          (0)
#define MIS_U2RFL_rfl_mask                                                           (0x000000FF)
#define MIS_U2RFL_rfl(data)                                                          (0x000000FF&((data)<<0))
#define MIS_U2RFL_rfl_src(data)                                                      ((0x000000FF&(data))>>0)
#define MIS_U2RFL_get_rfl(data)                                                      ((0x000000FF&(data))>>0)


#define MIS_U2SRR                                                                    0x9801B488
#define MIS_U2SRR_reg_addr                                                           "0x9801B488"
#define MIS_U2SRR_reg                                                                0x9801B488
#define set_MIS_U2SRR_reg(data)   (*((volatile unsigned int*) MIS_U2SRR_reg)=data)
#define get_MIS_U2SRR_reg   (*((volatile unsigned int*) MIS_U2SRR_reg))
#define MIS_U2SRR_inst_adr                                                           "0x0022"
#define MIS_U2SRR_inst                                                               0x0022
#define MIS_U2SRR_xfr_shift                                                          (2)
#define MIS_U2SRR_xfr_mask                                                           (0x00000004)
#define MIS_U2SRR_xfr(data)                                                          (0x00000004&((data)<<2))
#define MIS_U2SRR_xfr_src(data)                                                      ((0x00000004&(data))>>2)
#define MIS_U2SRR_get_xfr(data)                                                      ((0x00000004&(data))>>2)
#define MIS_U2SRR_rfr_shift                                                          (1)
#define MIS_U2SRR_rfr_mask                                                           (0x00000002)
#define MIS_U2SRR_rfr(data)                                                          (0x00000002&((data)<<1))
#define MIS_U2SRR_rfr_src(data)                                                      ((0x00000002&(data))>>1)
#define MIS_U2SRR_get_rfr(data)                                                      ((0x00000002&(data))>>1)
#define MIS_U2SRR_ur_shift                                                           (0)
#define MIS_U2SRR_ur_mask                                                            (0x00000001)
#define MIS_U2SRR_ur(data)                                                           (0x00000001&((data)<<0))
#define MIS_U2SRR_ur_src(data)                                                       ((0x00000001&(data))>>0)
#define MIS_U2SRR_get_ur(data)                                                       ((0x00000001&(data))>>0)


#define MIS_U2SBCR                                                                   0x9801B490
#define MIS_U2SBCR_reg_addr                                                          "0x9801B490"
#define MIS_U2SBCR_reg                                                               0x9801B490
#define set_MIS_U2SBCR_reg(data)   (*((volatile unsigned int*) MIS_U2SBCR_reg)=data)
#define get_MIS_U2SBCR_reg   (*((volatile unsigned int*) MIS_U2SBCR_reg))
#define MIS_U2SBCR_inst_adr                                                          "0x0024"
#define MIS_U2SBCR_inst                                                              0x0024
#define MIS_U2SBCR_sbcr_shift                                                        (0)
#define MIS_U2SBCR_sbcr_mask                                                         (0x00000001)
#define MIS_U2SBCR_sbcr(data)                                                        (0x00000001&((data)<<0))
#define MIS_U2SBCR_sbcr_src(data)                                                    ((0x00000001&(data))>>0)
#define MIS_U2SBCR_get_sbcr(data)                                                    ((0x00000001&(data))>>0)


#define MIS_U2SDMAM                                                                  0x9801B494
#define MIS_U2SDMAM_reg_addr                                                         "0x9801B494"
#define MIS_U2SDMAM_reg                                                              0x9801B494
#define set_MIS_U2SDMAM_reg(data)   (*((volatile unsigned int*) MIS_U2SDMAM_reg)=data)
#define get_MIS_U2SDMAM_reg   (*((volatile unsigned int*) MIS_U2SDMAM_reg))
#define MIS_U2SDMAM_inst_adr                                                         "0x0025"
#define MIS_U2SDMAM_inst                                                             0x0025
#define MIS_U2SDMAM_sdmam_shift                                                      (0)
#define MIS_U2SDMAM_sdmam_mask                                                       (0x00000001)
#define MIS_U2SDMAM_sdmam(data)                                                      (0x00000001&((data)<<0))
#define MIS_U2SDMAM_sdmam_src(data)                                                  ((0x00000001&(data))>>0)
#define MIS_U2SDMAM_get_sdmam(data)                                                  ((0x00000001&(data))>>0)


#define MIS_U2SFE                                                                    0x9801B498
#define MIS_U2SFE_reg_addr                                                           "0x9801B498"
#define MIS_U2SFE_reg                                                                0x9801B498
#define set_MIS_U2SFE_reg(data)   (*((volatile unsigned int*) MIS_U2SFE_reg)=data)
#define get_MIS_U2SFE_reg   (*((volatile unsigned int*) MIS_U2SFE_reg))
#define MIS_U2SFE_inst_adr                                                           "0x0026"
#define MIS_U2SFE_inst                                                               0x0026
#define MIS_U2SFE_sfe_shift                                                          (0)
#define MIS_U2SFE_sfe_mask                                                           (0x00000001)
#define MIS_U2SFE_sfe(data)                                                          (0x00000001&((data)<<0))
#define MIS_U2SFE_sfe_src(data)                                                      ((0x00000001&(data))>>0)
#define MIS_U2SFE_get_sfe(data)                                                      ((0x00000001&(data))>>0)


#define MIS_U2SRT                                                                    0x9801B49C
#define MIS_U2SRT_reg_addr                                                           "0x9801B49C"
#define MIS_U2SRT_reg                                                                0x9801B49C
#define set_MIS_U2SRT_reg(data)   (*((volatile unsigned int*) MIS_U2SRT_reg)=data)
#define get_MIS_U2SRT_reg   (*((volatile unsigned int*) MIS_U2SRT_reg))
#define MIS_U2SRT_inst_adr                                                           "0x0027"
#define MIS_U2SRT_inst                                                               0x0027
#define MIS_U2SRT_srt_shift                                                          (0)
#define MIS_U2SRT_srt_mask                                                           (0x00000003)
#define MIS_U2SRT_srt(data)                                                          (0x00000003&((data)<<0))
#define MIS_U2SRT_srt_src(data)                                                      ((0x00000003&(data))>>0)
#define MIS_U2SRT_get_srt(data)                                                      ((0x00000003&(data))>>0)


#define MIS_U2STET                                                                   0x9801B4A0
#define MIS_U2STET_reg_addr                                                          "0x9801B4A0"
#define MIS_U2STET_reg                                                               0x9801B4A0
#define set_MIS_U2STET_reg(data)   (*((volatile unsigned int*) MIS_U2STET_reg)=data)
#define get_MIS_U2STET_reg   (*((volatile unsigned int*) MIS_U2STET_reg))
#define MIS_U2STET_inst_adr                                                          "0x0028"
#define MIS_U2STET_inst                                                              0x0028
#define MIS_U2STET_stet_shift                                                        (0)
#define MIS_U2STET_stet_mask                                                         (0x00000003)
#define MIS_U2STET_stet(data)                                                        (0x00000003&((data)<<0))
#define MIS_U2STET_stet_src(data)                                                    ((0x00000003&(data))>>0)
#define MIS_U2STET_get_stet(data)                                                    ((0x00000003&(data))>>0)


#define MIS_U2HTX                                                                    0x9801B4A4
#define MIS_U2HTX_reg_addr                                                           "0x9801B4A4"
#define MIS_U2HTX_reg                                                                0x9801B4A4
#define set_MIS_U2HTX_reg(data)   (*((volatile unsigned int*) MIS_U2HTX_reg)=data)
#define get_MIS_U2HTX_reg   (*((volatile unsigned int*) MIS_U2HTX_reg))
#define MIS_U2HTX_inst_adr                                                           "0x0029"
#define MIS_U2HTX_inst                                                               0x0029
#define MIS_U2HTX_htx_shift                                                          (0)
#define MIS_U2HTX_htx_mask                                                           (0x00000001)
#define MIS_U2HTX_htx(data)                                                          (0x00000001&((data)<<0))
#define MIS_U2HTX_htx_src(data)                                                      ((0x00000001&(data))>>0)
#define MIS_U2HTX_get_htx(data)                                                      ((0x00000001&(data))>>0)


#define MIS_U2DMASA                                                                  0x9801B4A8
#define MIS_U2DMASA_reg_addr                                                         "0x9801B4A8"
#define MIS_U2DMASA_reg                                                              0x9801B4A8
#define set_MIS_U2DMASA_reg(data)   (*((volatile unsigned int*) MIS_U2DMASA_reg)=data)
#define get_MIS_U2DMASA_reg   (*((volatile unsigned int*) MIS_U2DMASA_reg))
#define MIS_U2DMASA_inst_adr                                                         "0x002A"
#define MIS_U2DMASA_inst                                                             0x002A
#define MIS_U2DMASA_dmasa_shift                                                      (0)
#define MIS_U2DMASA_dmasa_mask                                                       (0x00000001)
#define MIS_U2DMASA_dmasa(data)                                                      (0x00000001&((data)<<0))
#define MIS_U2DMASA_dmasa_src(data)                                                  ((0x00000001&(data))>>0)
#define MIS_U2DMASA_get_dmasa(data)                                                  ((0x00000001&(data))>>0)


#define MIS_U2CPR                                                                    0x9801B4F4
#define MIS_U2CPR_reg_addr                                                           "0x9801B4F4"
#define MIS_U2CPR_reg                                                                0x9801B4F4
#define set_MIS_U2CPR_reg(data)   (*((volatile unsigned int*) MIS_U2CPR_reg)=data)
#define get_MIS_U2CPR_reg   (*((volatile unsigned int*) MIS_U2CPR_reg))
#define MIS_U2CPR_inst_adr                                                           "0x003D"
#define MIS_U2CPR_inst                                                               0x003D
#define MIS_U2CPR_fifo_mode_shift                                                    (16)
#define MIS_U2CPR_fifo_mode_mask                                                     (0x00FF0000)
#define MIS_U2CPR_fifo_mode(data)                                                    (0x00FF0000&((data)<<16))
#define MIS_U2CPR_fifo_mode_src(data)                                                ((0x00FF0000&(data))>>16)
#define MIS_U2CPR_get_fifo_mode(data)                                                ((0x00FF0000&(data))>>16)
#define MIS_U2CPR_dma_extra_shift                                                    (13)
#define MIS_U2CPR_dma_extra_mask                                                     (0x00002000)
#define MIS_U2CPR_dma_extra(data)                                                    (0x00002000&((data)<<13))
#define MIS_U2CPR_dma_extra_src(data)                                                ((0x00002000&(data))>>13)
#define MIS_U2CPR_get_dma_extra(data)                                                ((0x00002000&(data))>>13)
#define MIS_U2CPR_uart_add_encoded_params_shift                                      (12)
#define MIS_U2CPR_uart_add_encoded_params_mask                                       (0x00001000)
#define MIS_U2CPR_uart_add_encoded_params(data)                                      (0x00001000&((data)<<12))
#define MIS_U2CPR_uart_add_encoded_params_src(data)                                  ((0x00001000&(data))>>12)
#define MIS_U2CPR_get_uart_add_encoded_params(data)                                  ((0x00001000&(data))>>12)
#define MIS_U2CPR_shadow_shift                                                       (11)
#define MIS_U2CPR_shadow_mask                                                        (0x00000800)
#define MIS_U2CPR_shadow(data)                                                       (0x00000800&((data)<<11))
#define MIS_U2CPR_shadow_src(data)                                                   ((0x00000800&(data))>>11)
#define MIS_U2CPR_get_shadow(data)                                                   ((0x00000800&(data))>>11)
#define MIS_U2CPR_fifo_stat_shift                                                    (10)
#define MIS_U2CPR_fifo_stat_mask                                                     (0x00000400)
#define MIS_U2CPR_fifo_stat(data)                                                    (0x00000400&((data)<<10))
#define MIS_U2CPR_fifo_stat_src(data)                                                ((0x00000400&(data))>>10)
#define MIS_U2CPR_get_fifo_stat(data)                                                ((0x00000400&(data))>>10)
#define MIS_U2CPR_fifo_access_shift                                                  (9)
#define MIS_U2CPR_fifo_access_mask                                                   (0x00000200)
#define MIS_U2CPR_fifo_access(data)                                                  (0x00000200&((data)<<9))
#define MIS_U2CPR_fifo_access_src(data)                                              ((0x00000200&(data))>>9)
#define MIS_U2CPR_get_fifo_access(data)                                              ((0x00000200&(data))>>9)
#define MIS_U2CPR_additional_feat_shift                                              (8)
#define MIS_U2CPR_additional_feat_mask                                               (0x00000100)
#define MIS_U2CPR_additional_feat(data)                                              (0x00000100&((data)<<8))
#define MIS_U2CPR_additional_feat_src(data)                                          ((0x00000100&(data))>>8)
#define MIS_U2CPR_get_additional_feat(data)                                          ((0x00000100&(data))>>8)
#define MIS_U2CPR_sir_lp_mode_shift                                                  (7)
#define MIS_U2CPR_sir_lp_mode_mask                                                   (0x00000080)
#define MIS_U2CPR_sir_lp_mode(data)                                                  (0x00000080&((data)<<7))
#define MIS_U2CPR_sir_lp_mode_src(data)                                              ((0x00000080&(data))>>7)
#define MIS_U2CPR_get_sir_lp_mode(data)                                              ((0x00000080&(data))>>7)
#define MIS_U2CPR_sir_mode_shift                                                     (6)
#define MIS_U2CPR_sir_mode_mask                                                      (0x00000040)
#define MIS_U2CPR_sir_mode(data)                                                     (0x00000040&((data)<<6))
#define MIS_U2CPR_sir_mode_src(data)                                                 ((0x00000040&(data))>>6)
#define MIS_U2CPR_get_sir_mode(data)                                                 ((0x00000040&(data))>>6)
#define MIS_U2CPR_thre_mode_shift                                                    (5)
#define MIS_U2CPR_thre_mode_mask                                                     (0x00000020)
#define MIS_U2CPR_thre_mode(data)                                                    (0x00000020&((data)<<5))
#define MIS_U2CPR_thre_mode_src(data)                                                ((0x00000020&(data))>>5)
#define MIS_U2CPR_get_thre_mode(data)                                                ((0x00000020&(data))>>5)
#define MIS_U2CPR_afce_mode_shift                                                    (4)
#define MIS_U2CPR_afce_mode_mask                                                     (0x00000010)
#define MIS_U2CPR_afce_mode(data)                                                    (0x00000010&((data)<<4))
#define MIS_U2CPR_afce_mode_src(data)                                                ((0x00000010&(data))>>4)
#define MIS_U2CPR_get_afce_mode(data)                                                ((0x00000010&(data))>>4)
#define MIS_U2CPR_apb_data_width_shift                                               (0)
#define MIS_U2CPR_apb_data_width_mask                                                (0x00000003)
#define MIS_U2CPR_apb_data_width(data)                                               (0x00000003&((data)<<0))
#define MIS_U2CPR_apb_data_width_src(data)                                           ((0x00000003&(data))>>0)
#define MIS_U2CPR_get_apb_data_width(data)                                           ((0x00000003&(data))>>0)


#define MIS_U2UCV                                                                    0x9801B4F8
#define MIS_U2UCV_reg_addr                                                           "0x9801B4F8"
#define MIS_U2UCV_reg                                                                0x9801B4F8
#define set_MIS_U2UCV_reg(data)   (*((volatile unsigned int*) MIS_U2UCV_reg)=data)
#define get_MIS_U2UCV_reg   (*((volatile unsigned int*) MIS_U2UCV_reg))
#define MIS_U2UCV_inst_adr                                                           "0x003E"
#define MIS_U2UCV_inst                                                               0x003E
#define MIS_U2UCV_ucv_shift                                                          (0)
#define MIS_U2UCV_ucv_mask                                                           (0xFFFFFFFF)
#define MIS_U2UCV_ucv(data)                                                          (0xFFFFFFFF&((data)<<0))
#define MIS_U2UCV_ucv_src(data)                                                      ((0xFFFFFFFF&(data))>>0)
#define MIS_U2UCV_get_ucv(data)                                                      ((0xFFFFFFFF&(data))>>0)


#define MIS_U2CTR                                                                    0x9801B4FC
#define MIS_U2CTR_reg_addr                                                           "0x9801B4FC"
#define MIS_U2CTR_reg                                                                0x9801B4FC
#define set_MIS_U2CTR_reg(data)   (*((volatile unsigned int*) MIS_U2CTR_reg)=data)
#define get_MIS_U2CTR_reg   (*((volatile unsigned int*) MIS_U2CTR_reg))
#define MIS_U2CTR_inst_adr                                                           "0x003F"
#define MIS_U2CTR_inst                                                               0x003F
#define MIS_U2CTR_ctr_shift                                                          (0)
#define MIS_U2CTR_ctr_mask                                                           (0xFFFFFFFF)
#define MIS_U2CTR_ctr(data)                                                          (0xFFFFFFFF&((data)<<0))
#define MIS_U2CTR_ctr_src(data)                                                      ((0xFFFFFFFF&(data))>>0)
#define MIS_U2CTR_get_ctr(data)                                                      ((0xFFFFFFFF&(data))>>0)


#define MIS_IC2_CON                                                                  0x9801B700
#define MIS_IC2_CON_reg_addr                                                         "0x9801B700"
#define MIS_IC2_CON_reg                                                              0x9801B700
#define set_MIS_IC2_CON_reg(data)   (*((volatile unsigned int*) MIS_IC2_CON_reg)=data)
#define get_MIS_IC2_CON_reg   (*((volatile unsigned int*) MIS_IC2_CON_reg))
#define MIS_IC2_CON_inst_adr                                                         "0x00C0"
#define MIS_IC2_CON_inst                                                             0x00C0
#define MIS_IC2_CON_ic_slave_disable_shift                                           (6)
#define MIS_IC2_CON_ic_slave_disable_mask                                            (0x00000040)
#define MIS_IC2_CON_ic_slave_disable(data)                                           (0x00000040&((data)<<6))
#define MIS_IC2_CON_ic_slave_disable_src(data)                                       ((0x00000040&(data))>>6)
#define MIS_IC2_CON_get_ic_slave_disable(data)                                       ((0x00000040&(data))>>6)
#define MIS_IC2_CON_ic_restart_en_shift                                              (5)
#define MIS_IC2_CON_ic_restart_en_mask                                               (0x00000020)
#define MIS_IC2_CON_ic_restart_en(data)                                              (0x00000020&((data)<<5))
#define MIS_IC2_CON_ic_restart_en_src(data)                                          ((0x00000020&(data))>>5)
#define MIS_IC2_CON_get_ic_restart_en(data)                                          ((0x00000020&(data))>>5)
#define MIS_IC2_CON_ic_10bitaddr_master_shift                                        (4)
#define MIS_IC2_CON_ic_10bitaddr_master_mask                                         (0x00000010)
#define MIS_IC2_CON_ic_10bitaddr_master(data)                                        (0x00000010&((data)<<4))
#define MIS_IC2_CON_ic_10bitaddr_master_src(data)                                    ((0x00000010&(data))>>4)
#define MIS_IC2_CON_get_ic_10bitaddr_master(data)                                    ((0x00000010&(data))>>4)
#define MIS_IC2_CON_ic_10bitaddr_slave_shift                                         (3)
#define MIS_IC2_CON_ic_10bitaddr_slave_mask                                          (0x00000008)
#define MIS_IC2_CON_ic_10bitaddr_slave(data)                                         (0x00000008&((data)<<3))
#define MIS_IC2_CON_ic_10bitaddr_slave_src(data)                                     ((0x00000008&(data))>>3)
#define MIS_IC2_CON_get_ic_10bitaddr_slave(data)                                     ((0x00000008&(data))>>3)
#define MIS_IC2_CON_speed_shift                                                      (1)
#define MIS_IC2_CON_speed_mask                                                       (0x00000006)
#define MIS_IC2_CON_speed(data)                                                      (0x00000006&((data)<<1))
#define MIS_IC2_CON_speed_src(data)                                                  ((0x00000006&(data))>>1)
#define MIS_IC2_CON_get_speed(data)                                                  ((0x00000006&(data))>>1)
#define MIS_IC2_CON_master_mode_shift                                                (0)
#define MIS_IC2_CON_master_mode_mask                                                 (0x00000001)
#define MIS_IC2_CON_master_mode(data)                                                (0x00000001&((data)<<0))
#define MIS_IC2_CON_master_mode_src(data)                                            ((0x00000001&(data))>>0)
#define MIS_IC2_CON_get_master_mode(data)                                            ((0x00000001&(data))>>0)


#define MIS_IC2_TAR                                                                  0x9801B704
#define MIS_IC2_TAR_reg_addr                                                         "0x9801B704"
#define MIS_IC2_TAR_reg                                                              0x9801B704
#define set_MIS_IC2_TAR_reg(data)   (*((volatile unsigned int*) MIS_IC2_TAR_reg)=data)
#define get_MIS_IC2_TAR_reg   (*((volatile unsigned int*) MIS_IC2_TAR_reg))
#define MIS_IC2_TAR_inst_adr                                                         "0x00C1"
#define MIS_IC2_TAR_inst                                                             0x00C1
#define MIS_IC2_TAR_ic_10bitaddr_master_shift                                        (12)
#define MIS_IC2_TAR_ic_10bitaddr_master_mask                                         (0x00001000)
#define MIS_IC2_TAR_ic_10bitaddr_master(data)                                        (0x00001000&((data)<<12))
#define MIS_IC2_TAR_ic_10bitaddr_master_src(data)                                    ((0x00001000&(data))>>12)
#define MIS_IC2_TAR_get_ic_10bitaddr_master(data)                                    ((0x00001000&(data))>>12)
#define MIS_IC2_TAR_special_shift                                                    (11)
#define MIS_IC2_TAR_special_mask                                                     (0x00000800)
#define MIS_IC2_TAR_special(data)                                                    (0x00000800&((data)<<11))
#define MIS_IC2_TAR_special_src(data)                                                ((0x00000800&(data))>>11)
#define MIS_IC2_TAR_get_special(data)                                                ((0x00000800&(data))>>11)
#define MIS_IC2_TAR_gc_or_start_shift                                                (10)
#define MIS_IC2_TAR_gc_or_start_mask                                                 (0x00000400)
#define MIS_IC2_TAR_gc_or_start(data)                                                (0x00000400&((data)<<10))
#define MIS_IC2_TAR_gc_or_start_src(data)                                            ((0x00000400&(data))>>10)
#define MIS_IC2_TAR_get_gc_or_start(data)                                            ((0x00000400&(data))>>10)
#define MIS_IC2_TAR_ic_tar_shift                                                     (0)
#define MIS_IC2_TAR_ic_tar_mask                                                      (0x000003FF)
#define MIS_IC2_TAR_ic_tar(data)                                                     (0x000003FF&((data)<<0))
#define MIS_IC2_TAR_ic_tar_src(data)                                                 ((0x000003FF&(data))>>0)
#define MIS_IC2_TAR_get_ic_tar(data)                                                 ((0x000003FF&(data))>>0)


#define MIS_IC2_SAR                                                                  0x9801B708
#define MIS_IC2_SAR_reg_addr                                                         "0x9801B708"
#define MIS_IC2_SAR_reg                                                              0x9801B708
#define set_MIS_IC2_SAR_reg(data)   (*((volatile unsigned int*) MIS_IC2_SAR_reg)=data)
#define get_MIS_IC2_SAR_reg   (*((volatile unsigned int*) MIS_IC2_SAR_reg))
#define MIS_IC2_SAR_inst_adr                                                         "0x00C2"
#define MIS_IC2_SAR_inst                                                             0x00C2
#define MIS_IC2_SAR_ic_sar_shift                                                     (0)
#define MIS_IC2_SAR_ic_sar_mask                                                      (0x000003FF)
#define MIS_IC2_SAR_ic_sar(data)                                                     (0x000003FF&((data)<<0))
#define MIS_IC2_SAR_ic_sar_src(data)                                                 ((0x000003FF&(data))>>0)
#define MIS_IC2_SAR_get_ic_sar(data)                                                 ((0x000003FF&(data))>>0)


#define MIS_IC2_HS_MADDR                                                             0x9801B70C
#define MIS_IC2_HS_MADDR_reg_addr                                                    "0x9801B70C"
#define MIS_IC2_HS_MADDR_reg                                                         0x9801B70C
#define set_MIS_IC2_HS_MADDR_reg(data)   (*((volatile unsigned int*) MIS_IC2_HS_MADDR_reg)=data)
#define get_MIS_IC2_HS_MADDR_reg   (*((volatile unsigned int*) MIS_IC2_HS_MADDR_reg))
#define MIS_IC2_HS_MADDR_inst_adr                                                    "0x00C3"
#define MIS_IC2_HS_MADDR_inst                                                        0x00C3
#define MIS_IC2_HS_MADDR_ic_hs_mar_shift                                             (0)
#define MIS_IC2_HS_MADDR_ic_hs_mar_mask                                              (0x00000007)
#define MIS_IC2_HS_MADDR_ic_hs_mar(data)                                             (0x00000007&((data)<<0))
#define MIS_IC2_HS_MADDR_ic_hs_mar_src(data)                                         ((0x00000007&(data))>>0)
#define MIS_IC2_HS_MADDR_get_ic_hs_mar(data)                                         ((0x00000007&(data))>>0)


#define MIS_IC2_DATA_CMD                                                             0x9801B710
#define MIS_IC2_DATA_CMD_reg_addr                                                    "0x9801B710"
#define MIS_IC2_DATA_CMD_reg                                                         0x9801B710
#define set_MIS_IC2_DATA_CMD_reg(data)   (*((volatile unsigned int*) MIS_IC2_DATA_CMD_reg)=data)
#define get_MIS_IC2_DATA_CMD_reg   (*((volatile unsigned int*) MIS_IC2_DATA_CMD_reg))
#define MIS_IC2_DATA_CMD_inst_adr                                                    "0x00C4"
#define MIS_IC2_DATA_CMD_inst                                                        0x00C4
#define MIS_IC2_DATA_CMD_restart_shift                                               (10)
#define MIS_IC2_DATA_CMD_restart_mask                                                (0x00000400)
#define MIS_IC2_DATA_CMD_restart(data)                                               (0x00000400&((data)<<10))
#define MIS_IC2_DATA_CMD_restart_src(data)                                           ((0x00000400&(data))>>10)
#define MIS_IC2_DATA_CMD_get_restart(data)                                           ((0x00000400&(data))>>10)
#define MIS_IC2_DATA_CMD_stop_shift                                                  (9)
#define MIS_IC2_DATA_CMD_stop_mask                                                   (0x00000200)
#define MIS_IC2_DATA_CMD_stop(data)                                                  (0x00000200&((data)<<9))
#define MIS_IC2_DATA_CMD_stop_src(data)                                              ((0x00000200&(data))>>9)
#define MIS_IC2_DATA_CMD_get_stop(data)                                              ((0x00000200&(data))>>9)
#define MIS_IC2_DATA_CMD_cmd_shift                                                   (8)
#define MIS_IC2_DATA_CMD_cmd_mask                                                    (0x00000100)
#define MIS_IC2_DATA_CMD_cmd(data)                                                   (0x00000100&((data)<<8))
#define MIS_IC2_DATA_CMD_cmd_src(data)                                               ((0x00000100&(data))>>8)
#define MIS_IC2_DATA_CMD_get_cmd(data)                                               ((0x00000100&(data))>>8)
#define MIS_IC2_DATA_CMD_dat_shift                                                   (0)
#define MIS_IC2_DATA_CMD_dat_mask                                                    (0x000000FF)
#define MIS_IC2_DATA_CMD_dat(data)                                                   (0x000000FF&((data)<<0))
#define MIS_IC2_DATA_CMD_dat_src(data)                                               ((0x000000FF&(data))>>0)
#define MIS_IC2_DATA_CMD_get_dat(data)                                               ((0x000000FF&(data))>>0)


#define MIS_IC2_SS_SCL_HCNT                                                          0x9801B714
#define MIS_IC2_SS_SCL_HCNT_reg_addr                                                 "0x9801B714"
#define MIS_IC2_SS_SCL_HCNT_reg                                                      0x9801B714
#define set_MIS_IC2_SS_SCL_HCNT_reg(data)   (*((volatile unsigned int*) MIS_IC2_SS_SCL_HCNT_reg)=data)
#define get_MIS_IC2_SS_SCL_HCNT_reg   (*((volatile unsigned int*) MIS_IC2_SS_SCL_HCNT_reg))
#define MIS_IC2_SS_SCL_HCNT_inst_adr                                                 "0x00C5"
#define MIS_IC2_SS_SCL_HCNT_inst                                                     0x00C5
#define MIS_IC2_SS_SCL_HCNT_ic_ss_scl_hcnt_shift                                     (0)
#define MIS_IC2_SS_SCL_HCNT_ic_ss_scl_hcnt_mask                                      (0x0000FFFF)
#define MIS_IC2_SS_SCL_HCNT_ic_ss_scl_hcnt(data)                                     (0x0000FFFF&((data)<<0))
#define MIS_IC2_SS_SCL_HCNT_ic_ss_scl_hcnt_src(data)                                 ((0x0000FFFF&(data))>>0)
#define MIS_IC2_SS_SCL_HCNT_get_ic_ss_scl_hcnt(data)                                 ((0x0000FFFF&(data))>>0)


#define MIS_IC2_SS_SCL_LCNT                                                          0x9801B718
#define MIS_IC2_SS_SCL_LCNT_reg_addr                                                 "0x9801B718"
#define MIS_IC2_SS_SCL_LCNT_reg                                                      0x9801B718
#define set_MIS_IC2_SS_SCL_LCNT_reg(data)   (*((volatile unsigned int*) MIS_IC2_SS_SCL_LCNT_reg)=data)
#define get_MIS_IC2_SS_SCL_LCNT_reg   (*((volatile unsigned int*) MIS_IC2_SS_SCL_LCNT_reg))
#define MIS_IC2_SS_SCL_LCNT_inst_adr                                                 "0x00C6"
#define MIS_IC2_SS_SCL_LCNT_inst                                                     0x00C6
#define MIS_IC2_SS_SCL_LCNT_ic_ss_scl_lcnt_shift                                     (0)
#define MIS_IC2_SS_SCL_LCNT_ic_ss_scl_lcnt_mask                                      (0x0000FFFF)
#define MIS_IC2_SS_SCL_LCNT_ic_ss_scl_lcnt(data)                                     (0x0000FFFF&((data)<<0))
#define MIS_IC2_SS_SCL_LCNT_ic_ss_scl_lcnt_src(data)                                 ((0x0000FFFF&(data))>>0)
#define MIS_IC2_SS_SCL_LCNT_get_ic_ss_scl_lcnt(data)                                 ((0x0000FFFF&(data))>>0)


#define MIS_IC2_FS_SCL_HCNT                                                          0x9801B71C
#define MIS_IC2_FS_SCL_HCNT_reg_addr                                                 "0x9801B71C"
#define MIS_IC2_FS_SCL_HCNT_reg                                                      0x9801B71C
#define set_MIS_IC2_FS_SCL_HCNT_reg(data)   (*((volatile unsigned int*) MIS_IC2_FS_SCL_HCNT_reg)=data)
#define get_MIS_IC2_FS_SCL_HCNT_reg   (*((volatile unsigned int*) MIS_IC2_FS_SCL_HCNT_reg))
#define MIS_IC2_FS_SCL_HCNT_inst_adr                                                 "0x00C7"
#define MIS_IC2_FS_SCL_HCNT_inst                                                     0x00C7
#define MIS_IC2_FS_SCL_HCNT_ic_fs_scl_hcnt_shift                                     (0)
#define MIS_IC2_FS_SCL_HCNT_ic_fs_scl_hcnt_mask                                      (0x0000FFFF)
#define MIS_IC2_FS_SCL_HCNT_ic_fs_scl_hcnt(data)                                     (0x0000FFFF&((data)<<0))
#define MIS_IC2_FS_SCL_HCNT_ic_fs_scl_hcnt_src(data)                                 ((0x0000FFFF&(data))>>0)
#define MIS_IC2_FS_SCL_HCNT_get_ic_fs_scl_hcnt(data)                                 ((0x0000FFFF&(data))>>0)


#define MIS_IC2_FS_SCL_LCNT                                                          0x9801B720
#define MIS_IC2_FS_SCL_LCNT_reg_addr                                                 "0x9801B720"
#define MIS_IC2_FS_SCL_LCNT_reg                                                      0x9801B720
#define set_MIS_IC2_FS_SCL_LCNT_reg(data)   (*((volatile unsigned int*) MIS_IC2_FS_SCL_LCNT_reg)=data)
#define get_MIS_IC2_FS_SCL_LCNT_reg   (*((volatile unsigned int*) MIS_IC2_FS_SCL_LCNT_reg))
#define MIS_IC2_FS_SCL_LCNT_inst_adr                                                 "0x00C8"
#define MIS_IC2_FS_SCL_LCNT_inst                                                     0x00C8
#define MIS_IC2_FS_SCL_LCNT_ic_fs_scl_lcnt_shift                                     (0)
#define MIS_IC2_FS_SCL_LCNT_ic_fs_scl_lcnt_mask                                      (0x0000FFFF)
#define MIS_IC2_FS_SCL_LCNT_ic_fs_scl_lcnt(data)                                     (0x0000FFFF&((data)<<0))
#define MIS_IC2_FS_SCL_LCNT_ic_fs_scl_lcnt_src(data)                                 ((0x0000FFFF&(data))>>0)
#define MIS_IC2_FS_SCL_LCNT_get_ic_fs_scl_lcnt(data)                                 ((0x0000FFFF&(data))>>0)


#define MIS_IC2_INTR_STAT                                                            0x9801B72C
#define MIS_IC2_INTR_STAT_reg_addr                                                   "0x9801B72C"
#define MIS_IC2_INTR_STAT_reg                                                        0x9801B72C
#define set_MIS_IC2_INTR_STAT_reg(data)   (*((volatile unsigned int*) MIS_IC2_INTR_STAT_reg)=data)
#define get_MIS_IC2_INTR_STAT_reg   (*((volatile unsigned int*) MIS_IC2_INTR_STAT_reg))
#define MIS_IC2_INTR_STAT_inst_adr                                                   "0x00CB"
#define MIS_IC2_INTR_STAT_inst                                                       0x00CB
#define MIS_IC2_INTR_STAT_r_gen_call_shift                                           (11)
#define MIS_IC2_INTR_STAT_r_gen_call_mask                                            (0x00000800)
#define MIS_IC2_INTR_STAT_r_gen_call(data)                                           (0x00000800&((data)<<11))
#define MIS_IC2_INTR_STAT_r_gen_call_src(data)                                       ((0x00000800&(data))>>11)
#define MIS_IC2_INTR_STAT_get_r_gen_call(data)                                       ((0x00000800&(data))>>11)
#define MIS_IC2_INTR_STAT_r_start_det_shift                                          (10)
#define MIS_IC2_INTR_STAT_r_start_det_mask                                           (0x00000400)
#define MIS_IC2_INTR_STAT_r_start_det(data)                                          (0x00000400&((data)<<10))
#define MIS_IC2_INTR_STAT_r_start_det_src(data)                                      ((0x00000400&(data))>>10)
#define MIS_IC2_INTR_STAT_get_r_start_det(data)                                      ((0x00000400&(data))>>10)
#define MIS_IC2_INTR_STAT_r_stop_det_shift                                           (9)
#define MIS_IC2_INTR_STAT_r_stop_det_mask                                            (0x00000200)
#define MIS_IC2_INTR_STAT_r_stop_det(data)                                           (0x00000200&((data)<<9))
#define MIS_IC2_INTR_STAT_r_stop_det_src(data)                                       ((0x00000200&(data))>>9)
#define MIS_IC2_INTR_STAT_get_r_stop_det(data)                                       ((0x00000200&(data))>>9)
#define MIS_IC2_INTR_STAT_r_activity_shift                                           (8)
#define MIS_IC2_INTR_STAT_r_activity_mask                                            (0x00000100)
#define MIS_IC2_INTR_STAT_r_activity(data)                                           (0x00000100&((data)<<8))
#define MIS_IC2_INTR_STAT_r_activity_src(data)                                       ((0x00000100&(data))>>8)
#define MIS_IC2_INTR_STAT_get_r_activity(data)                                       ((0x00000100&(data))>>8)
#define MIS_IC2_INTR_STAT_r_rx_done_shift                                            (7)
#define MIS_IC2_INTR_STAT_r_rx_done_mask                                             (0x00000080)
#define MIS_IC2_INTR_STAT_r_rx_done(data)                                            (0x00000080&((data)<<7))
#define MIS_IC2_INTR_STAT_r_rx_done_src(data)                                        ((0x00000080&(data))>>7)
#define MIS_IC2_INTR_STAT_get_r_rx_done(data)                                        ((0x00000080&(data))>>7)
#define MIS_IC2_INTR_STAT_r_tx_abrt_shift                                            (6)
#define MIS_IC2_INTR_STAT_r_tx_abrt_mask                                             (0x00000040)
#define MIS_IC2_INTR_STAT_r_tx_abrt(data)                                            (0x00000040&((data)<<6))
#define MIS_IC2_INTR_STAT_r_tx_abrt_src(data)                                        ((0x00000040&(data))>>6)
#define MIS_IC2_INTR_STAT_get_r_tx_abrt(data)                                        ((0x00000040&(data))>>6)
#define MIS_IC2_INTR_STAT_r_rd_req_shift                                             (5)
#define MIS_IC2_INTR_STAT_r_rd_req_mask                                              (0x00000020)
#define MIS_IC2_INTR_STAT_r_rd_req(data)                                             (0x00000020&((data)<<5))
#define MIS_IC2_INTR_STAT_r_rd_req_src(data)                                         ((0x00000020&(data))>>5)
#define MIS_IC2_INTR_STAT_get_r_rd_req(data)                                         ((0x00000020&(data))>>5)
#define MIS_IC2_INTR_STAT_r_tx_empty_shift                                           (4)
#define MIS_IC2_INTR_STAT_r_tx_empty_mask                                            (0x00000010)
#define MIS_IC2_INTR_STAT_r_tx_empty(data)                                           (0x00000010&((data)<<4))
#define MIS_IC2_INTR_STAT_r_tx_empty_src(data)                                       ((0x00000010&(data))>>4)
#define MIS_IC2_INTR_STAT_get_r_tx_empty(data)                                       ((0x00000010&(data))>>4)
#define MIS_IC2_INTR_STAT_r_tx_over_shift                                            (3)
#define MIS_IC2_INTR_STAT_r_tx_over_mask                                             (0x00000008)
#define MIS_IC2_INTR_STAT_r_tx_over(data)                                            (0x00000008&((data)<<3))
#define MIS_IC2_INTR_STAT_r_tx_over_src(data)                                        ((0x00000008&(data))>>3)
#define MIS_IC2_INTR_STAT_get_r_tx_over(data)                                        ((0x00000008&(data))>>3)
#define MIS_IC2_INTR_STAT_r_rx_full_shift                                            (2)
#define MIS_IC2_INTR_STAT_r_rx_full_mask                                             (0x00000004)
#define MIS_IC2_INTR_STAT_r_rx_full(data)                                            (0x00000004&((data)<<2))
#define MIS_IC2_INTR_STAT_r_rx_full_src(data)                                        ((0x00000004&(data))>>2)
#define MIS_IC2_INTR_STAT_get_r_rx_full(data)                                        ((0x00000004&(data))>>2)
#define MIS_IC2_INTR_STAT_r_rx_over_shift                                            (1)
#define MIS_IC2_INTR_STAT_r_rx_over_mask                                             (0x00000002)
#define MIS_IC2_INTR_STAT_r_rx_over(data)                                            (0x00000002&((data)<<1))
#define MIS_IC2_INTR_STAT_r_rx_over_src(data)                                        ((0x00000002&(data))>>1)
#define MIS_IC2_INTR_STAT_get_r_rx_over(data)                                        ((0x00000002&(data))>>1)
#define MIS_IC2_INTR_STAT_r_rx_under_shift                                           (0)
#define MIS_IC2_INTR_STAT_r_rx_under_mask                                            (0x00000001)
#define MIS_IC2_INTR_STAT_r_rx_under(data)                                           (0x00000001&((data)<<0))
#define MIS_IC2_INTR_STAT_r_rx_under_src(data)                                       ((0x00000001&(data))>>0)
#define MIS_IC2_INTR_STAT_get_r_rx_under(data)                                       ((0x00000001&(data))>>0)


#define MIS_IC2_INTR_MASK                                                            0x9801B730
#define MIS_IC2_INTR_MASK_reg_addr                                                   "0x9801B730"
#define MIS_IC2_INTR_MASK_reg                                                        0x9801B730
#define set_MIS_IC2_INTR_MASK_reg(data)   (*((volatile unsigned int*) MIS_IC2_INTR_MASK_reg)=data)
#define get_MIS_IC2_INTR_MASK_reg   (*((volatile unsigned int*) MIS_IC2_INTR_MASK_reg))
#define MIS_IC2_INTR_MASK_inst_adr                                                   "0x00CC"
#define MIS_IC2_INTR_MASK_inst                                                       0x00CC
#define MIS_IC2_INTR_MASK_m_gen_call_shift                                           (11)
#define MIS_IC2_INTR_MASK_m_gen_call_mask                                            (0x00000800)
#define MIS_IC2_INTR_MASK_m_gen_call(data)                                           (0x00000800&((data)<<11))
#define MIS_IC2_INTR_MASK_m_gen_call_src(data)                                       ((0x00000800&(data))>>11)
#define MIS_IC2_INTR_MASK_get_m_gen_call(data)                                       ((0x00000800&(data))>>11)
#define MIS_IC2_INTR_MASK_m_start_det_shift                                          (10)
#define MIS_IC2_INTR_MASK_m_start_det_mask                                           (0x00000400)
#define MIS_IC2_INTR_MASK_m_start_det(data)                                          (0x00000400&((data)<<10))
#define MIS_IC2_INTR_MASK_m_start_det_src(data)                                      ((0x00000400&(data))>>10)
#define MIS_IC2_INTR_MASK_get_m_start_det(data)                                      ((0x00000400&(data))>>10)
#define MIS_IC2_INTR_MASK_m_stop_det_shift                                           (9)
#define MIS_IC2_INTR_MASK_m_stop_det_mask                                            (0x00000200)
#define MIS_IC2_INTR_MASK_m_stop_det(data)                                           (0x00000200&((data)<<9))
#define MIS_IC2_INTR_MASK_m_stop_det_src(data)                                       ((0x00000200&(data))>>9)
#define MIS_IC2_INTR_MASK_get_m_stop_det(data)                                       ((0x00000200&(data))>>9)
#define MIS_IC2_INTR_MASK_m_activity_shift                                           (8)
#define MIS_IC2_INTR_MASK_m_activity_mask                                            (0x00000100)
#define MIS_IC2_INTR_MASK_m_activity(data)                                           (0x00000100&((data)<<8))
#define MIS_IC2_INTR_MASK_m_activity_src(data)                                       ((0x00000100&(data))>>8)
#define MIS_IC2_INTR_MASK_get_m_activity(data)                                       ((0x00000100&(data))>>8)
#define MIS_IC2_INTR_MASK_m_rx_done_shift                                            (7)
#define MIS_IC2_INTR_MASK_m_rx_done_mask                                             (0x00000080)
#define MIS_IC2_INTR_MASK_m_rx_done(data)                                            (0x00000080&((data)<<7))
#define MIS_IC2_INTR_MASK_m_rx_done_src(data)                                        ((0x00000080&(data))>>7)
#define MIS_IC2_INTR_MASK_get_m_rx_done(data)                                        ((0x00000080&(data))>>7)
#define MIS_IC2_INTR_MASK_m_tx_abrt_shift                                            (6)
#define MIS_IC2_INTR_MASK_m_tx_abrt_mask                                             (0x00000040)
#define MIS_IC2_INTR_MASK_m_tx_abrt(data)                                            (0x00000040&((data)<<6))
#define MIS_IC2_INTR_MASK_m_tx_abrt_src(data)                                        ((0x00000040&(data))>>6)
#define MIS_IC2_INTR_MASK_get_m_tx_abrt(data)                                        ((0x00000040&(data))>>6)
#define MIS_IC2_INTR_MASK_m_rd_req_shift                                             (5)
#define MIS_IC2_INTR_MASK_m_rd_req_mask                                              (0x00000020)
#define MIS_IC2_INTR_MASK_m_rd_req(data)                                             (0x00000020&((data)<<5))
#define MIS_IC2_INTR_MASK_m_rd_req_src(data)                                         ((0x00000020&(data))>>5)
#define MIS_IC2_INTR_MASK_get_m_rd_req(data)                                         ((0x00000020&(data))>>5)
#define MIS_IC2_INTR_MASK_m_tx_empty_shift                                           (4)
#define MIS_IC2_INTR_MASK_m_tx_empty_mask                                            (0x00000010)
#define MIS_IC2_INTR_MASK_m_tx_empty(data)                                           (0x00000010&((data)<<4))
#define MIS_IC2_INTR_MASK_m_tx_empty_src(data)                                       ((0x00000010&(data))>>4)
#define MIS_IC2_INTR_MASK_get_m_tx_empty(data)                                       ((0x00000010&(data))>>4)
#define MIS_IC2_INTR_MASK_m_tx_over_shift                                            (3)
#define MIS_IC2_INTR_MASK_m_tx_over_mask                                             (0x00000008)
#define MIS_IC2_INTR_MASK_m_tx_over(data)                                            (0x00000008&((data)<<3))
#define MIS_IC2_INTR_MASK_m_tx_over_src(data)                                        ((0x00000008&(data))>>3)
#define MIS_IC2_INTR_MASK_get_m_tx_over(data)                                        ((0x00000008&(data))>>3)
#define MIS_IC2_INTR_MASK_m_rx_full_shift                                            (2)
#define MIS_IC2_INTR_MASK_m_rx_full_mask                                             (0x00000004)
#define MIS_IC2_INTR_MASK_m_rx_full(data)                                            (0x00000004&((data)<<2))
#define MIS_IC2_INTR_MASK_m_rx_full_src(data)                                        ((0x00000004&(data))>>2)
#define MIS_IC2_INTR_MASK_get_m_rx_full(data)                                        ((0x00000004&(data))>>2)
#define MIS_IC2_INTR_MASK_m_rx_over_shift                                            (1)
#define MIS_IC2_INTR_MASK_m_rx_over_mask                                             (0x00000002)
#define MIS_IC2_INTR_MASK_m_rx_over(data)                                            (0x00000002&((data)<<1))
#define MIS_IC2_INTR_MASK_m_rx_over_src(data)                                        ((0x00000002&(data))>>1)
#define MIS_IC2_INTR_MASK_get_m_rx_over(data)                                        ((0x00000002&(data))>>1)
#define MIS_IC2_INTR_MASK_m_rx_under_shift                                           (0)
#define MIS_IC2_INTR_MASK_m_rx_under_mask                                            (0x00000001)
#define MIS_IC2_INTR_MASK_m_rx_under(data)                                           (0x00000001&((data)<<0))
#define MIS_IC2_INTR_MASK_m_rx_under_src(data)                                       ((0x00000001&(data))>>0)
#define MIS_IC2_INTR_MASK_get_m_rx_under(data)                                       ((0x00000001&(data))>>0)


#define MIS_IC2_RAW_INTR_STAT                                                        0x9801B734
#define MIS_IC2_RAW_INTR_STAT_reg_addr                                               "0x9801B734"
#define MIS_IC2_RAW_INTR_STAT_reg                                                    0x9801B734
#define set_MIS_IC2_RAW_INTR_STAT_reg(data)   (*((volatile unsigned int*) MIS_IC2_RAW_INTR_STAT_reg)=data)
#define get_MIS_IC2_RAW_INTR_STAT_reg   (*((volatile unsigned int*) MIS_IC2_RAW_INTR_STAT_reg))
#define MIS_IC2_RAW_INTR_STAT_inst_adr                                               "0x00CD"
#define MIS_IC2_RAW_INTR_STAT_inst                                                   0x00CD
#define MIS_IC2_RAW_INTR_STAT_gen_call_shift                                         (11)
#define MIS_IC2_RAW_INTR_STAT_gen_call_mask                                          (0x00000800)
#define MIS_IC2_RAW_INTR_STAT_gen_call(data)                                         (0x00000800&((data)<<11))
#define MIS_IC2_RAW_INTR_STAT_gen_call_src(data)                                     ((0x00000800&(data))>>11)
#define MIS_IC2_RAW_INTR_STAT_get_gen_call(data)                                     ((0x00000800&(data))>>11)
#define MIS_IC2_RAW_INTR_STAT_start_det_shift                                        (10)
#define MIS_IC2_RAW_INTR_STAT_start_det_mask                                         (0x00000400)
#define MIS_IC2_RAW_INTR_STAT_start_det(data)                                        (0x00000400&((data)<<10))
#define MIS_IC2_RAW_INTR_STAT_start_det_src(data)                                    ((0x00000400&(data))>>10)
#define MIS_IC2_RAW_INTR_STAT_get_start_det(data)                                    ((0x00000400&(data))>>10)
#define MIS_IC2_RAW_INTR_STAT_stop_det_shift                                         (9)
#define MIS_IC2_RAW_INTR_STAT_stop_det_mask                                          (0x00000200)
#define MIS_IC2_RAW_INTR_STAT_stop_det(data)                                         (0x00000200&((data)<<9))
#define MIS_IC2_RAW_INTR_STAT_stop_det_src(data)                                     ((0x00000200&(data))>>9)
#define MIS_IC2_RAW_INTR_STAT_get_stop_det(data)                                     ((0x00000200&(data))>>9)
#define MIS_IC2_RAW_INTR_STAT_activity_shift                                         (8)
#define MIS_IC2_RAW_INTR_STAT_activity_mask                                          (0x00000100)
#define MIS_IC2_RAW_INTR_STAT_activity(data)                                         (0x00000100&((data)<<8))
#define MIS_IC2_RAW_INTR_STAT_activity_src(data)                                     ((0x00000100&(data))>>8)
#define MIS_IC2_RAW_INTR_STAT_get_activity(data)                                     ((0x00000100&(data))>>8)
#define MIS_IC2_RAW_INTR_STAT_rx_done_shift                                          (7)
#define MIS_IC2_RAW_INTR_STAT_rx_done_mask                                           (0x00000080)
#define MIS_IC2_RAW_INTR_STAT_rx_done(data)                                          (0x00000080&((data)<<7))
#define MIS_IC2_RAW_INTR_STAT_rx_done_src(data)                                      ((0x00000080&(data))>>7)
#define MIS_IC2_RAW_INTR_STAT_get_rx_done(data)                                      ((0x00000080&(data))>>7)
#define MIS_IC2_RAW_INTR_STAT_tx_abrt_shift                                          (6)
#define MIS_IC2_RAW_INTR_STAT_tx_abrt_mask                                           (0x00000040)
#define MIS_IC2_RAW_INTR_STAT_tx_abrt(data)                                          (0x00000040&((data)<<6))
#define MIS_IC2_RAW_INTR_STAT_tx_abrt_src(data)                                      ((0x00000040&(data))>>6)
#define MIS_IC2_RAW_INTR_STAT_get_tx_abrt(data)                                      ((0x00000040&(data))>>6)
#define MIS_IC2_RAW_INTR_STAT_rd_req_shift                                           (5)
#define MIS_IC2_RAW_INTR_STAT_rd_req_mask                                            (0x00000020)
#define MIS_IC2_RAW_INTR_STAT_rd_req(data)                                           (0x00000020&((data)<<5))
#define MIS_IC2_RAW_INTR_STAT_rd_req_src(data)                                       ((0x00000020&(data))>>5)
#define MIS_IC2_RAW_INTR_STAT_get_rd_req(data)                                       ((0x00000020&(data))>>5)
#define MIS_IC2_RAW_INTR_STAT_tx_empty_shift                                         (4)
#define MIS_IC2_RAW_INTR_STAT_tx_empty_mask                                          (0x00000010)
#define MIS_IC2_RAW_INTR_STAT_tx_empty(data)                                         (0x00000010&((data)<<4))
#define MIS_IC2_RAW_INTR_STAT_tx_empty_src(data)                                     ((0x00000010&(data))>>4)
#define MIS_IC2_RAW_INTR_STAT_get_tx_empty(data)                                     ((0x00000010&(data))>>4)
#define MIS_IC2_RAW_INTR_STAT_tx_over_shift                                          (3)
#define MIS_IC2_RAW_INTR_STAT_tx_over_mask                                           (0x00000008)
#define MIS_IC2_RAW_INTR_STAT_tx_over(data)                                          (0x00000008&((data)<<3))
#define MIS_IC2_RAW_INTR_STAT_tx_over_src(data)                                      ((0x00000008&(data))>>3)
#define MIS_IC2_RAW_INTR_STAT_get_tx_over(data)                                      ((0x00000008&(data))>>3)
#define MIS_IC2_RAW_INTR_STAT_rx_full_shift                                          (2)
#define MIS_IC2_RAW_INTR_STAT_rx_full_mask                                           (0x00000004)
#define MIS_IC2_RAW_INTR_STAT_rx_full(data)                                          (0x00000004&((data)<<2))
#define MIS_IC2_RAW_INTR_STAT_rx_full_src(data)                                      ((0x00000004&(data))>>2)
#define MIS_IC2_RAW_INTR_STAT_get_rx_full(data)                                      ((0x00000004&(data))>>2)
#define MIS_IC2_RAW_INTR_STAT_rx_over_shift                                          (1)
#define MIS_IC2_RAW_INTR_STAT_rx_over_mask                                           (0x00000002)
#define MIS_IC2_RAW_INTR_STAT_rx_over(data)                                          (0x00000002&((data)<<1))
#define MIS_IC2_RAW_INTR_STAT_rx_over_src(data)                                      ((0x00000002&(data))>>1)
#define MIS_IC2_RAW_INTR_STAT_get_rx_over(data)                                      ((0x00000002&(data))>>1)
#define MIS_IC2_RAW_INTR_STAT_rx_under_shift                                         (0)
#define MIS_IC2_RAW_INTR_STAT_rx_under_mask                                          (0x00000001)
#define MIS_IC2_RAW_INTR_STAT_rx_under(data)                                         (0x00000001&((data)<<0))
#define MIS_IC2_RAW_INTR_STAT_rx_under_src(data)                                     ((0x00000001&(data))>>0)
#define MIS_IC2_RAW_INTR_STAT_get_rx_under(data)                                     ((0x00000001&(data))>>0)


#define MIS_IC2_RX_TL                                                                0x9801B738
#define MIS_IC2_RX_TL_reg_addr                                                       "0x9801B738"
#define MIS_IC2_RX_TL_reg                                                            0x9801B738
#define set_MIS_IC2_RX_TL_reg(data)   (*((volatile unsigned int*) MIS_IC2_RX_TL_reg)=data)
#define get_MIS_IC2_RX_TL_reg   (*((volatile unsigned int*) MIS_IC2_RX_TL_reg))
#define MIS_IC2_RX_TL_inst_adr                                                       "0x00CE"
#define MIS_IC2_RX_TL_inst                                                           0x00CE
#define MIS_IC2_RX_TL_rx_tl_shift                                                    (0)
#define MIS_IC2_RX_TL_rx_tl_mask                                                     (0x000000FF)
#define MIS_IC2_RX_TL_rx_tl(data)                                                    (0x000000FF&((data)<<0))
#define MIS_IC2_RX_TL_rx_tl_src(data)                                                ((0x000000FF&(data))>>0)
#define MIS_IC2_RX_TL_get_rx_tl(data)                                                ((0x000000FF&(data))>>0)


#define MIS_IC2_TX_TL                                                                0x9801B73C
#define MIS_IC2_TX_TL_reg_addr                                                       "0x9801B73C"
#define MIS_IC2_TX_TL_reg                                                            0x9801B73C
#define set_MIS_IC2_TX_TL_reg(data)   (*((volatile unsigned int*) MIS_IC2_TX_TL_reg)=data)
#define get_MIS_IC2_TX_TL_reg   (*((volatile unsigned int*) MIS_IC2_TX_TL_reg))
#define MIS_IC2_TX_TL_inst_adr                                                       "0x00CF"
#define MIS_IC2_TX_TL_inst                                                           0x00CF
#define MIS_IC2_TX_TL_tx_tl_shift                                                    (0)
#define MIS_IC2_TX_TL_tx_tl_mask                                                     (0x000000FF)
#define MIS_IC2_TX_TL_tx_tl(data)                                                    (0x000000FF&((data)<<0))
#define MIS_IC2_TX_TL_tx_tl_src(data)                                                ((0x000000FF&(data))>>0)
#define MIS_IC2_TX_TL_get_tx_tl(data)                                                ((0x000000FF&(data))>>0)


#define MIS_IC2_CLR_INTR                                                             0x9801B740
#define MIS_IC2_CLR_INTR_reg_addr                                                    "0x9801B740"
#define MIS_IC2_CLR_INTR_reg                                                         0x9801B740
#define set_MIS_IC2_CLR_INTR_reg(data)   (*((volatile unsigned int*) MIS_IC2_CLR_INTR_reg)=data)
#define get_MIS_IC2_CLR_INTR_reg   (*((volatile unsigned int*) MIS_IC2_CLR_INTR_reg))
#define MIS_IC2_CLR_INTR_inst_adr                                                    "0x00D0"
#define MIS_IC2_CLR_INTR_inst                                                        0x00D0
#define MIS_IC2_CLR_INTR_clr_intr_shift                                              (0)
#define MIS_IC2_CLR_INTR_clr_intr_mask                                               (0x00000001)
#define MIS_IC2_CLR_INTR_clr_intr(data)                                              (0x00000001&((data)<<0))
#define MIS_IC2_CLR_INTR_clr_intr_src(data)                                          ((0x00000001&(data))>>0)
#define MIS_IC2_CLR_INTR_get_clr_intr(data)                                          ((0x00000001&(data))>>0)


#define MIS_IC2_CLR_RX_UNDER                                                         0x9801B744
#define MIS_IC2_CLR_RX_UNDER_reg_addr                                                "0x9801B744"
#define MIS_IC2_CLR_RX_UNDER_reg                                                     0x9801B744
#define set_MIS_IC2_CLR_RX_UNDER_reg(data)   (*((volatile unsigned int*) MIS_IC2_CLR_RX_UNDER_reg)=data)
#define get_MIS_IC2_CLR_RX_UNDER_reg   (*((volatile unsigned int*) MIS_IC2_CLR_RX_UNDER_reg))
#define MIS_IC2_CLR_RX_UNDER_inst_adr                                                "0x00D1"
#define MIS_IC2_CLR_RX_UNDER_inst                                                    0x00D1
#define MIS_IC2_CLR_RX_UNDER_clr_rx_under_shift                                      (0)
#define MIS_IC2_CLR_RX_UNDER_clr_rx_under_mask                                       (0x00000001)
#define MIS_IC2_CLR_RX_UNDER_clr_rx_under(data)                                      (0x00000001&((data)<<0))
#define MIS_IC2_CLR_RX_UNDER_clr_rx_under_src(data)                                  ((0x00000001&(data))>>0)
#define MIS_IC2_CLR_RX_UNDER_get_clr_rx_under(data)                                  ((0x00000001&(data))>>0)


#define MIS_IC2_CLR_RX_OVER                                                          0x9801B748
#define MIS_IC2_CLR_RX_OVER_reg_addr                                                 "0x9801B748"
#define MIS_IC2_CLR_RX_OVER_reg                                                      0x9801B748
#define set_MIS_IC2_CLR_RX_OVER_reg(data)   (*((volatile unsigned int*) MIS_IC2_CLR_RX_OVER_reg)=data)
#define get_MIS_IC2_CLR_RX_OVER_reg   (*((volatile unsigned int*) MIS_IC2_CLR_RX_OVER_reg))
#define MIS_IC2_CLR_RX_OVER_inst_adr                                                 "0x00D2"
#define MIS_IC2_CLR_RX_OVER_inst                                                     0x00D2
#define MIS_IC2_CLR_RX_OVER_clr_rx_over_shift                                        (0)
#define MIS_IC2_CLR_RX_OVER_clr_rx_over_mask                                         (0x00000001)
#define MIS_IC2_CLR_RX_OVER_clr_rx_over(data)                                        (0x00000001&((data)<<0))
#define MIS_IC2_CLR_RX_OVER_clr_rx_over_src(data)                                    ((0x00000001&(data))>>0)
#define MIS_IC2_CLR_RX_OVER_get_clr_rx_over(data)                                    ((0x00000001&(data))>>0)


#define MIS_IC2_CLR_TX_OVER                                                          0x9801B74C
#define MIS_IC2_CLR_TX_OVER_reg_addr                                                 "0x9801B74C"
#define MIS_IC2_CLR_TX_OVER_reg                                                      0x9801B74C
#define set_MIS_IC2_CLR_TX_OVER_reg(data)   (*((volatile unsigned int*) MIS_IC2_CLR_TX_OVER_reg)=data)
#define get_MIS_IC2_CLR_TX_OVER_reg   (*((volatile unsigned int*) MIS_IC2_CLR_TX_OVER_reg))
#define MIS_IC2_CLR_TX_OVER_inst_adr                                                 "0x00D3"
#define MIS_IC2_CLR_TX_OVER_inst                                                     0x00D3
#define MIS_IC2_CLR_TX_OVER_clr_tx_over_shift                                        (0)
#define MIS_IC2_CLR_TX_OVER_clr_tx_over_mask                                         (0x00000001)
#define MIS_IC2_CLR_TX_OVER_clr_tx_over(data)                                        (0x00000001&((data)<<0))
#define MIS_IC2_CLR_TX_OVER_clr_tx_over_src(data)                                    ((0x00000001&(data))>>0)
#define MIS_IC2_CLR_TX_OVER_get_clr_tx_over(data)                                    ((0x00000001&(data))>>0)


#define MIS_IC2_CLR_RD_REQ                                                           0x9801B750
#define MIS_IC2_CLR_RD_REQ_reg_addr                                                  "0x9801B750"
#define MIS_IC2_CLR_RD_REQ_reg                                                       0x9801B750
#define set_MIS_IC2_CLR_RD_REQ_reg(data)   (*((volatile unsigned int*) MIS_IC2_CLR_RD_REQ_reg)=data)
#define get_MIS_IC2_CLR_RD_REQ_reg   (*((volatile unsigned int*) MIS_IC2_CLR_RD_REQ_reg))
#define MIS_IC2_CLR_RD_REQ_inst_adr                                                  "0x00D4"
#define MIS_IC2_CLR_RD_REQ_inst                                                      0x00D4
#define MIS_IC2_CLR_RD_REQ_clr_rd_req_shift                                          (0)
#define MIS_IC2_CLR_RD_REQ_clr_rd_req_mask                                           (0x00000001)
#define MIS_IC2_CLR_RD_REQ_clr_rd_req(data)                                          (0x00000001&((data)<<0))
#define MIS_IC2_CLR_RD_REQ_clr_rd_req_src(data)                                      ((0x00000001&(data))>>0)
#define MIS_IC2_CLR_RD_REQ_get_clr_rd_req(data)                                      ((0x00000001&(data))>>0)


#define MIS_IC2_CLR_TX_ABRT                                                          0x9801B754
#define MIS_IC2_CLR_TX_ABRT_reg_addr                                                 "0x9801B754"
#define MIS_IC2_CLR_TX_ABRT_reg                                                      0x9801B754
#define set_MIS_IC2_CLR_TX_ABRT_reg(data)   (*((volatile unsigned int*) MIS_IC2_CLR_TX_ABRT_reg)=data)
#define get_MIS_IC2_CLR_TX_ABRT_reg   (*((volatile unsigned int*) MIS_IC2_CLR_TX_ABRT_reg))
#define MIS_IC2_CLR_TX_ABRT_inst_adr                                                 "0x00D5"
#define MIS_IC2_CLR_TX_ABRT_inst                                                     0x00D5
#define MIS_IC2_CLR_TX_ABRT_clr_tx_abrt_shift                                        (0)
#define MIS_IC2_CLR_TX_ABRT_clr_tx_abrt_mask                                         (0x00000001)
#define MIS_IC2_CLR_TX_ABRT_clr_tx_abrt(data)                                        (0x00000001&((data)<<0))
#define MIS_IC2_CLR_TX_ABRT_clr_tx_abrt_src(data)                                    ((0x00000001&(data))>>0)
#define MIS_IC2_CLR_TX_ABRT_get_clr_tx_abrt(data)                                    ((0x00000001&(data))>>0)


#define MIS_IC2_CLR_RX_DONE                                                          0x9801B758
#define MIS_IC2_CLR_RX_DONE_reg_addr                                                 "0x9801B758"
#define MIS_IC2_CLR_RX_DONE_reg                                                      0x9801B758
#define set_MIS_IC2_CLR_RX_DONE_reg(data)   (*((volatile unsigned int*) MIS_IC2_CLR_RX_DONE_reg)=data)
#define get_MIS_IC2_CLR_RX_DONE_reg   (*((volatile unsigned int*) MIS_IC2_CLR_RX_DONE_reg))
#define MIS_IC2_CLR_RX_DONE_inst_adr                                                 "0x00D6"
#define MIS_IC2_CLR_RX_DONE_inst                                                     0x00D6
#define MIS_IC2_CLR_RX_DONE_clr_rx_done_shift                                        (0)
#define MIS_IC2_CLR_RX_DONE_clr_rx_done_mask                                         (0x00000001)
#define MIS_IC2_CLR_RX_DONE_clr_rx_done(data)                                        (0x00000001&((data)<<0))
#define MIS_IC2_CLR_RX_DONE_clr_rx_done_src(data)                                    ((0x00000001&(data))>>0)
#define MIS_IC2_CLR_RX_DONE_get_clr_rx_done(data)                                    ((0x00000001&(data))>>0)


#define MIS_IC2_CLR_ACTIVITY                                                         0x9801B75C
#define MIS_IC2_CLR_ACTIVITY_reg_addr                                                "0x9801B75C"
#define MIS_IC2_CLR_ACTIVITY_reg                                                     0x9801B75C
#define set_MIS_IC2_CLR_ACTIVITY_reg(data)   (*((volatile unsigned int*) MIS_IC2_CLR_ACTIVITY_reg)=data)
#define get_MIS_IC2_CLR_ACTIVITY_reg   (*((volatile unsigned int*) MIS_IC2_CLR_ACTIVITY_reg))
#define MIS_IC2_CLR_ACTIVITY_inst_adr                                                "0x00D7"
#define MIS_IC2_CLR_ACTIVITY_inst                                                    0x00D7
#define MIS_IC2_CLR_ACTIVITY_clr_activity_shift                                      (0)
#define MIS_IC2_CLR_ACTIVITY_clr_activity_mask                                       (0x00000001)
#define MIS_IC2_CLR_ACTIVITY_clr_activity(data)                                      (0x00000001&((data)<<0))
#define MIS_IC2_CLR_ACTIVITY_clr_activity_src(data)                                  ((0x00000001&(data))>>0)
#define MIS_IC2_CLR_ACTIVITY_get_clr_activity(data)                                  ((0x00000001&(data))>>0)


#define MIS_IC2_CLR_STOP_DET                                                         0x9801B760
#define MIS_IC2_CLR_STOP_DET_reg_addr                                                "0x9801B760"
#define MIS_IC2_CLR_STOP_DET_reg                                                     0x9801B760
#define set_MIS_IC2_CLR_STOP_DET_reg(data)   (*((volatile unsigned int*) MIS_IC2_CLR_STOP_DET_reg)=data)
#define get_MIS_IC2_CLR_STOP_DET_reg   (*((volatile unsigned int*) MIS_IC2_CLR_STOP_DET_reg))
#define MIS_IC2_CLR_STOP_DET_inst_adr                                                "0x00D8"
#define MIS_IC2_CLR_STOP_DET_inst                                                    0x00D8
#define MIS_IC2_CLR_STOP_DET_clr_stop_det_shift                                      (0)
#define MIS_IC2_CLR_STOP_DET_clr_stop_det_mask                                       (0x00000001)
#define MIS_IC2_CLR_STOP_DET_clr_stop_det(data)                                      (0x00000001&((data)<<0))
#define MIS_IC2_CLR_STOP_DET_clr_stop_det_src(data)                                  ((0x00000001&(data))>>0)
#define MIS_IC2_CLR_STOP_DET_get_clr_stop_det(data)                                  ((0x00000001&(data))>>0)


#define MIS_IC2_CLR_START_DET                                                        0x9801B764
#define MIS_IC2_CLR_START_DET_reg_addr                                               "0x9801B764"
#define MIS_IC2_CLR_START_DET_reg                                                    0x9801B764
#define set_MIS_IC2_CLR_START_DET_reg(data)   (*((volatile unsigned int*) MIS_IC2_CLR_START_DET_reg)=data)
#define get_MIS_IC2_CLR_START_DET_reg   (*((volatile unsigned int*) MIS_IC2_CLR_START_DET_reg))
#define MIS_IC2_CLR_START_DET_inst_adr                                               "0x00D9"
#define MIS_IC2_CLR_START_DET_inst                                                   0x00D9
#define MIS_IC2_CLR_START_DET_clr_start_det_shift                                    (0)
#define MIS_IC2_CLR_START_DET_clr_start_det_mask                                     (0x00000001)
#define MIS_IC2_CLR_START_DET_clr_start_det(data)                                    (0x00000001&((data)<<0))
#define MIS_IC2_CLR_START_DET_clr_start_det_src(data)                                ((0x00000001&(data))>>0)
#define MIS_IC2_CLR_START_DET_get_clr_start_det(data)                                ((0x00000001&(data))>>0)


#define MIS_IC2_CLR_GEN_CALL                                                         0x9801B768
#define MIS_IC2_CLR_GEN_CALL_reg_addr                                                "0x9801B768"
#define MIS_IC2_CLR_GEN_CALL_reg                                                     0x9801B768
#define set_MIS_IC2_CLR_GEN_CALL_reg(data)   (*((volatile unsigned int*) MIS_IC2_CLR_GEN_CALL_reg)=data)
#define get_MIS_IC2_CLR_GEN_CALL_reg   (*((volatile unsigned int*) MIS_IC2_CLR_GEN_CALL_reg))
#define MIS_IC2_CLR_GEN_CALL_inst_adr                                                "0x00DA"
#define MIS_IC2_CLR_GEN_CALL_inst                                                    0x00DA
#define MIS_IC2_CLR_GEN_CALL_clr_gen_call_shift                                      (0)
#define MIS_IC2_CLR_GEN_CALL_clr_gen_call_mask                                       (0x00000001)
#define MIS_IC2_CLR_GEN_CALL_clr_gen_call(data)                                      (0x00000001&((data)<<0))
#define MIS_IC2_CLR_GEN_CALL_clr_gen_call_src(data)                                  ((0x00000001&(data))>>0)
#define MIS_IC2_CLR_GEN_CALL_get_clr_gen_call(data)                                  ((0x00000001&(data))>>0)


#define MIS_IC2_ENABLE                                                               0x9801B76C
#define MIS_IC2_ENABLE_reg_addr                                                      "0x9801B76C"
#define MIS_IC2_ENABLE_reg                                                           0x9801B76C
#define set_MIS_IC2_ENABLE_reg(data)   (*((volatile unsigned int*) MIS_IC2_ENABLE_reg)=data)
#define get_MIS_IC2_ENABLE_reg   (*((volatile unsigned int*) MIS_IC2_ENABLE_reg))
#define MIS_IC2_ENABLE_inst_adr                                                      "0x00DB"
#define MIS_IC2_ENABLE_inst                                                          0x00DB
#define MIS_IC2_ENABLE_enable_shift                                                  (0)
#define MIS_IC2_ENABLE_enable_mask                                                   (0x00000001)
#define MIS_IC2_ENABLE_enable(data)                                                  (0x00000001&((data)<<0))
#define MIS_IC2_ENABLE_enable_src(data)                                              ((0x00000001&(data))>>0)
#define MIS_IC2_ENABLE_get_enable(data)                                              ((0x00000001&(data))>>0)


#define MIS_IC2_STATUS                                                               0x9801B770
#define MIS_IC2_STATUS_reg_addr                                                      "0x9801B770"
#define MIS_IC2_STATUS_reg                                                           0x9801B770
#define set_MIS_IC2_STATUS_reg(data)   (*((volatile unsigned int*) MIS_IC2_STATUS_reg)=data)
#define get_MIS_IC2_STATUS_reg   (*((volatile unsigned int*) MIS_IC2_STATUS_reg))
#define MIS_IC2_STATUS_inst_adr                                                      "0x00DC"
#define MIS_IC2_STATUS_inst                                                          0x00DC
#define MIS_IC2_STATUS_slv_activity_shift                                            (6)
#define MIS_IC2_STATUS_slv_activity_mask                                             (0x00000040)
#define MIS_IC2_STATUS_slv_activity(data)                                            (0x00000040&((data)<<6))
#define MIS_IC2_STATUS_slv_activity_src(data)                                        ((0x00000040&(data))>>6)
#define MIS_IC2_STATUS_get_slv_activity(data)                                        ((0x00000040&(data))>>6)
#define MIS_IC2_STATUS_mst_activity_shift                                            (5)
#define MIS_IC2_STATUS_mst_activity_mask                                             (0x00000020)
#define MIS_IC2_STATUS_mst_activity(data)                                            (0x00000020&((data)<<5))
#define MIS_IC2_STATUS_mst_activity_src(data)                                        ((0x00000020&(data))>>5)
#define MIS_IC2_STATUS_get_mst_activity(data)                                        ((0x00000020&(data))>>5)
#define MIS_IC2_STATUS_rff_shift                                                     (4)
#define MIS_IC2_STATUS_rff_mask                                                      (0x00000010)
#define MIS_IC2_STATUS_rff(data)                                                     (0x00000010&((data)<<4))
#define MIS_IC2_STATUS_rff_src(data)                                                 ((0x00000010&(data))>>4)
#define MIS_IC2_STATUS_get_rff(data)                                                 ((0x00000010&(data))>>4)
#define MIS_IC2_STATUS_rfne_shift                                                    (3)
#define MIS_IC2_STATUS_rfne_mask                                                     (0x00000008)
#define MIS_IC2_STATUS_rfne(data)                                                    (0x00000008&((data)<<3))
#define MIS_IC2_STATUS_rfne_src(data)                                                ((0x00000008&(data))>>3)
#define MIS_IC2_STATUS_get_rfne(data)                                                ((0x00000008&(data))>>3)
#define MIS_IC2_STATUS_tfe_shift                                                     (2)
#define MIS_IC2_STATUS_tfe_mask                                                      (0x00000004)
#define MIS_IC2_STATUS_tfe(data)                                                     (0x00000004&((data)<<2))
#define MIS_IC2_STATUS_tfe_src(data)                                                 ((0x00000004&(data))>>2)
#define MIS_IC2_STATUS_get_tfe(data)                                                 ((0x00000004&(data))>>2)
#define MIS_IC2_STATUS_tfnf_shift                                                    (1)
#define MIS_IC2_STATUS_tfnf_mask                                                     (0x00000002)
#define MIS_IC2_STATUS_tfnf(data)                                                    (0x00000002&((data)<<1))
#define MIS_IC2_STATUS_tfnf_src(data)                                                ((0x00000002&(data))>>1)
#define MIS_IC2_STATUS_get_tfnf(data)                                                ((0x00000002&(data))>>1)
#define MIS_IC2_STATUS_activity_shift                                                (0)
#define MIS_IC2_STATUS_activity_mask                                                 (0x00000001)
#define MIS_IC2_STATUS_activity(data)                                                (0x00000001&((data)<<0))
#define MIS_IC2_STATUS_activity_src(data)                                            ((0x00000001&(data))>>0)
#define MIS_IC2_STATUS_get_activity(data)                                            ((0x00000001&(data))>>0)


#define MIS_IC2_TXFLR                                                                0x9801B774
#define MIS_IC2_TXFLR_reg_addr                                                       "0x9801B774"
#define MIS_IC2_TXFLR_reg                                                            0x9801B774
#define set_MIS_IC2_TXFLR_reg(data)   (*((volatile unsigned int*) MIS_IC2_TXFLR_reg)=data)
#define get_MIS_IC2_TXFLR_reg   (*((volatile unsigned int*) MIS_IC2_TXFLR_reg))
#define MIS_IC2_TXFLR_inst_adr                                                       "0x00DD"
#define MIS_IC2_TXFLR_inst                                                           0x00DD
#define MIS_IC2_TXFLR_txflr_shift                                                    (0)
#define MIS_IC2_TXFLR_txflr_mask                                                     (0x0000000F)
#define MIS_IC2_TXFLR_txflr(data)                                                    (0x0000000F&((data)<<0))
#define MIS_IC2_TXFLR_txflr_src(data)                                                ((0x0000000F&(data))>>0)
#define MIS_IC2_TXFLR_get_txflr(data)                                                ((0x0000000F&(data))>>0)


#define MIS_IC2_RXFLR                                                                0x9801B778
#define MIS_IC2_RXFLR_reg_addr                                                       "0x9801B778"
#define MIS_IC2_RXFLR_reg                                                            0x9801B778
#define set_MIS_IC2_RXFLR_reg(data)   (*((volatile unsigned int*) MIS_IC2_RXFLR_reg)=data)
#define get_MIS_IC2_RXFLR_reg   (*((volatile unsigned int*) MIS_IC2_RXFLR_reg))
#define MIS_IC2_RXFLR_inst_adr                                                       "0x00DE"
#define MIS_IC2_RXFLR_inst                                                           0x00DE
#define MIS_IC2_RXFLR_rxflr_shift                                                    (0)
#define MIS_IC2_RXFLR_rxflr_mask                                                     (0x0000000F)
#define MIS_IC2_RXFLR_rxflr(data)                                                    (0x0000000F&((data)<<0))
#define MIS_IC2_RXFLR_rxflr_src(data)                                                ((0x0000000F&(data))>>0)
#define MIS_IC2_RXFLR_get_rxflr(data)                                                ((0x0000000F&(data))>>0)


#define MIS_IC2_SDA_HOLD                                                             0x9801B77C
#define MIS_IC2_SDA_HOLD_reg_addr                                                    "0x9801B77C"
#define MIS_IC2_SDA_HOLD_reg                                                         0x9801B77C
#define set_MIS_IC2_SDA_HOLD_reg(data)   (*((volatile unsigned int*) MIS_IC2_SDA_HOLD_reg)=data)
#define get_MIS_IC2_SDA_HOLD_reg   (*((volatile unsigned int*) MIS_IC2_SDA_HOLD_reg))
#define MIS_IC2_SDA_HOLD_inst_adr                                                    "0x00DF"
#define MIS_IC2_SDA_HOLD_inst                                                        0x00DF
#define MIS_IC2_SDA_HOLD_sda_hold_shift                                              (0)
#define MIS_IC2_SDA_HOLD_sda_hold_mask                                               (0x0000FFFF)
#define MIS_IC2_SDA_HOLD_sda_hold(data)                                              (0x0000FFFF&((data)<<0))
#define MIS_IC2_SDA_HOLD_sda_hold_src(data)                                          ((0x0000FFFF&(data))>>0)
#define MIS_IC2_SDA_HOLD_get_sda_hold(data)                                          ((0x0000FFFF&(data))>>0)


#define MIS_IC2_TX_ABRT_SOURCE                                                       0x9801B780
#define MIS_IC2_TX_ABRT_SOURCE_reg_addr                                              "0x9801B780"
#define MIS_IC2_TX_ABRT_SOURCE_reg                                                   0x9801B780
#define set_MIS_IC2_TX_ABRT_SOURCE_reg(data)   (*((volatile unsigned int*) MIS_IC2_TX_ABRT_SOURCE_reg)=data)
#define get_MIS_IC2_TX_ABRT_SOURCE_reg   (*((volatile unsigned int*) MIS_IC2_TX_ABRT_SOURCE_reg))
#define MIS_IC2_TX_ABRT_SOURCE_inst_adr                                              "0x00E0"
#define MIS_IC2_TX_ABRT_SOURCE_inst                                                  0x00E0
#define MIS_IC2_TX_ABRT_SOURCE_abrt_slvrd_intx_shift                                 (15)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_slvrd_intx_mask                                  (0x00008000)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_slvrd_intx(data)                                 (0x00008000&((data)<<15))
#define MIS_IC2_TX_ABRT_SOURCE_abrt_slvrd_intx_src(data)                             ((0x00008000&(data))>>15)
#define MIS_IC2_TX_ABRT_SOURCE_get_abrt_slvrd_intx(data)                             ((0x00008000&(data))>>15)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_slv_arblost_shift                                (14)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_slv_arblost_mask                                 (0x00004000)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_slv_arblost(data)                                (0x00004000&((data)<<14))
#define MIS_IC2_TX_ABRT_SOURCE_abrt_slv_arblost_src(data)                            ((0x00004000&(data))>>14)
#define MIS_IC2_TX_ABRT_SOURCE_get_abrt_slv_arblost(data)                            ((0x00004000&(data))>>14)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_slvflush_txfifo_shift                            (13)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_slvflush_txfifo_mask                             (0x00002000)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_slvflush_txfifo(data)                            (0x00002000&((data)<<13))
#define MIS_IC2_TX_ABRT_SOURCE_abrt_slvflush_txfifo_src(data)                        ((0x00002000&(data))>>13)
#define MIS_IC2_TX_ABRT_SOURCE_get_abrt_slvflush_txfifo(data)                        ((0x00002000&(data))>>13)
#define MIS_IC2_TX_ABRT_SOURCE_arb_lost_shift                                        (12)
#define MIS_IC2_TX_ABRT_SOURCE_arb_lost_mask                                         (0x00001000)
#define MIS_IC2_TX_ABRT_SOURCE_arb_lost(data)                                        (0x00001000&((data)<<12))
#define MIS_IC2_TX_ABRT_SOURCE_arb_lost_src(data)                                    ((0x00001000&(data))>>12)
#define MIS_IC2_TX_ABRT_SOURCE_get_arb_lost(data)                                    ((0x00001000&(data))>>12)
#define MIS_IC2_TX_ABRT_SOURCE_arb_master_dis_shift                                  (11)
#define MIS_IC2_TX_ABRT_SOURCE_arb_master_dis_mask                                   (0x00000800)
#define MIS_IC2_TX_ABRT_SOURCE_arb_master_dis(data)                                  (0x00000800&((data)<<11))
#define MIS_IC2_TX_ABRT_SOURCE_arb_master_dis_src(data)                              ((0x00000800&(data))>>11)
#define MIS_IC2_TX_ABRT_SOURCE_get_arb_master_dis(data)                              ((0x00000800&(data))>>11)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_10b_rd_norstrt_shift                             (10)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_10b_rd_norstrt_mask                              (0x00000400)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_10b_rd_norstrt(data)                             (0x00000400&((data)<<10))
#define MIS_IC2_TX_ABRT_SOURCE_abrt_10b_rd_norstrt_src(data)                         ((0x00000400&(data))>>10)
#define MIS_IC2_TX_ABRT_SOURCE_get_abrt_10b_rd_norstrt(data)                         ((0x00000400&(data))>>10)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_sbyte_norstrt_shift                              (9)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_sbyte_norstrt_mask                               (0x00000200)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_sbyte_norstrt(data)                              (0x00000200&((data)<<9))
#define MIS_IC2_TX_ABRT_SOURCE_abrt_sbyte_norstrt_src(data)                          ((0x00000200&(data))>>9)
#define MIS_IC2_TX_ABRT_SOURCE_get_abrt_sbyte_norstrt(data)                          ((0x00000200&(data))>>9)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_hs_norstrt_shift                                 (8)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_hs_norstrt_mask                                  (0x00000100)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_hs_norstrt(data)                                 (0x00000100&((data)<<8))
#define MIS_IC2_TX_ABRT_SOURCE_abrt_hs_norstrt_src(data)                             ((0x00000100&(data))>>8)
#define MIS_IC2_TX_ABRT_SOURCE_get_abrt_hs_norstrt(data)                             ((0x00000100&(data))>>8)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_sbyte_ackdet_shift                               (7)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_sbyte_ackdet_mask                                (0x00000080)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_sbyte_ackdet(data)                               (0x00000080&((data)<<7))
#define MIS_IC2_TX_ABRT_SOURCE_abrt_sbyte_ackdet_src(data)                           ((0x00000080&(data))>>7)
#define MIS_IC2_TX_ABRT_SOURCE_get_abrt_sbyte_ackdet(data)                           ((0x00000080&(data))>>7)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_hs_ackdet_shift                                  (6)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_hs_ackdet_mask                                   (0x00000040)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_hs_ackdet(data)                                  (0x00000040&((data)<<6))
#define MIS_IC2_TX_ABRT_SOURCE_abrt_hs_ackdet_src(data)                              ((0x00000040&(data))>>6)
#define MIS_IC2_TX_ABRT_SOURCE_get_abrt_hs_ackdet(data)                              ((0x00000040&(data))>>6)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_gcall_read_shift                                 (5)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_gcall_read_mask                                  (0x00000020)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_gcall_read(data)                                 (0x00000020&((data)<<5))
#define MIS_IC2_TX_ABRT_SOURCE_abrt_gcall_read_src(data)                             ((0x00000020&(data))>>5)
#define MIS_IC2_TX_ABRT_SOURCE_get_abrt_gcall_read(data)                             ((0x00000020&(data))>>5)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_gcall_noack_shift                                (4)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_gcall_noack_mask                                 (0x00000010)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_gcall_noack(data)                                (0x00000010&((data)<<4))
#define MIS_IC2_TX_ABRT_SOURCE_abrt_gcall_noack_src(data)                            ((0x00000010&(data))>>4)
#define MIS_IC2_TX_ABRT_SOURCE_get_abrt_gcall_noack(data)                            ((0x00000010&(data))>>4)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_txdata_noack_shift                               (3)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_txdata_noack_mask                                (0x00000008)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_txdata_noack(data)                               (0x00000008&((data)<<3))
#define MIS_IC2_TX_ABRT_SOURCE_abrt_txdata_noack_src(data)                           ((0x00000008&(data))>>3)
#define MIS_IC2_TX_ABRT_SOURCE_get_abrt_txdata_noack(data)                           ((0x00000008&(data))>>3)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_10addr2_noack_shift                              (2)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_10addr2_noack_mask                               (0x00000004)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_10addr2_noack(data)                              (0x00000004&((data)<<2))
#define MIS_IC2_TX_ABRT_SOURCE_abrt_10addr2_noack_src(data)                          ((0x00000004&(data))>>2)
#define MIS_IC2_TX_ABRT_SOURCE_get_abrt_10addr2_noack(data)                          ((0x00000004&(data))>>2)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_10addr1_noack_shift                              (1)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_10addr1_noack_mask                               (0x00000002)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_10addr1_noack(data)                              (0x00000002&((data)<<1))
#define MIS_IC2_TX_ABRT_SOURCE_abrt_10addr1_noack_src(data)                          ((0x00000002&(data))>>1)
#define MIS_IC2_TX_ABRT_SOURCE_get_abrt_10addr1_noack(data)                          ((0x00000002&(data))>>1)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_7b_addr_noack_shift                              (0)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_7b_addr_noack_mask                               (0x00000001)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_7b_addr_noack(data)                              (0x00000001&((data)<<0))
#define MIS_IC2_TX_ABRT_SOURCE_abrt_7b_addr_noack_src(data)                          ((0x00000001&(data))>>0)
#define MIS_IC2_TX_ABRT_SOURCE_get_abrt_7b_addr_noack(data)                          ((0x00000001&(data))>>0)


#define MIS_IC2_SLV_DATA_NACK_ONLY                                                   0x9801B784
#define MIS_IC2_SLV_DATA_NACK_ONLY_reg_addr                                          "0x9801B784"
#define MIS_IC2_SLV_DATA_NACK_ONLY_reg                                               0x9801B784
#define set_MIS_IC2_SLV_DATA_NACK_ONLY_reg(data)   (*((volatile unsigned int*) MIS_IC2_SLV_DATA_NACK_ONLY_reg)=data)
#define get_MIS_IC2_SLV_DATA_NACK_ONLY_reg   (*((volatile unsigned int*) MIS_IC2_SLV_DATA_NACK_ONLY_reg))
#define MIS_IC2_SLV_DATA_NACK_ONLY_inst_adr                                          "0x00E1"
#define MIS_IC2_SLV_DATA_NACK_ONLY_inst                                              0x00E1
#define MIS_IC2_SLV_DATA_NACK_ONLY_nack_shift                                        (0)
#define MIS_IC2_SLV_DATA_NACK_ONLY_nack_mask                                         (0x00000001)
#define MIS_IC2_SLV_DATA_NACK_ONLY_nack(data)                                        (0x00000001&((data)<<0))
#define MIS_IC2_SLV_DATA_NACK_ONLY_nack_src(data)                                    ((0x00000001&(data))>>0)
#define MIS_IC2_SLV_DATA_NACK_ONLY_get_nack(data)                                    ((0x00000001&(data))>>0)


#define MIS_IC2_DMA_CR                                                               0x9801B788
#define MIS_IC2_DMA_CR_reg_addr                                                      "0x9801B788"
#define MIS_IC2_DMA_CR_reg                                                           0x9801B788
#define set_MIS_IC2_DMA_CR_reg(data)   (*((volatile unsigned int*) MIS_IC2_DMA_CR_reg)=data)
#define get_MIS_IC2_DMA_CR_reg   (*((volatile unsigned int*) MIS_IC2_DMA_CR_reg))
#define MIS_IC2_DMA_CR_inst_adr                                                      "0x00E2"
#define MIS_IC2_DMA_CR_inst                                                          0x00E2
#define MIS_IC2_DMA_CR_tdmae_shift                                                   (1)
#define MIS_IC2_DMA_CR_tdmae_mask                                                    (0x00000002)
#define MIS_IC2_DMA_CR_tdmae(data)                                                   (0x00000002&((data)<<1))
#define MIS_IC2_DMA_CR_tdmae_src(data)                                               ((0x00000002&(data))>>1)
#define MIS_IC2_DMA_CR_get_tdmae(data)                                               ((0x00000002&(data))>>1)
#define MIS_IC2_DMA_CR_rdmae_shift                                                   (0)
#define MIS_IC2_DMA_CR_rdmae_mask                                                    (0x00000001)
#define MIS_IC2_DMA_CR_rdmae(data)                                                   (0x00000001&((data)<<0))
#define MIS_IC2_DMA_CR_rdmae_src(data)                                               ((0x00000001&(data))>>0)
#define MIS_IC2_DMA_CR_get_rdmae(data)                                               ((0x00000001&(data))>>0)


#define MIS_IC2_DMA_TDLR                                                             0x9801B78C
#define MIS_IC2_DMA_TDLR_reg_addr                                                    "0x9801B78C"
#define MIS_IC2_DMA_TDLR_reg                                                         0x9801B78C
#define set_MIS_IC2_DMA_TDLR_reg(data)   (*((volatile unsigned int*) MIS_IC2_DMA_TDLR_reg)=data)
#define get_MIS_IC2_DMA_TDLR_reg   (*((volatile unsigned int*) MIS_IC2_DMA_TDLR_reg))
#define MIS_IC2_DMA_TDLR_inst_adr                                                    "0x00E3"
#define MIS_IC2_DMA_TDLR_inst                                                        0x00E3
#define MIS_IC2_DMA_TDLR_dmatdl_shift                                                (0)
#define MIS_IC2_DMA_TDLR_dmatdl_mask                                                 (0x00000007)
#define MIS_IC2_DMA_TDLR_dmatdl(data)                                                (0x00000007&((data)<<0))
#define MIS_IC2_DMA_TDLR_dmatdl_src(data)                                            ((0x00000007&(data))>>0)
#define MIS_IC2_DMA_TDLR_get_dmatdl(data)                                            ((0x00000007&(data))>>0)


#define MIS_IC2_DMA_RDLR                                                             0x9801B790
#define MIS_IC2_DMA_RDLR_reg_addr                                                    "0x9801B790"
#define MIS_IC2_DMA_RDLR_reg                                                         0x9801B790
#define set_MIS_IC2_DMA_RDLR_reg(data)   (*((volatile unsigned int*) MIS_IC2_DMA_RDLR_reg)=data)
#define get_MIS_IC2_DMA_RDLR_reg   (*((volatile unsigned int*) MIS_IC2_DMA_RDLR_reg))
#define MIS_IC2_DMA_RDLR_inst_adr                                                    "0x00E4"
#define MIS_IC2_DMA_RDLR_inst                                                        0x00E4
#define MIS_IC2_DMA_RDLR_dmardl_shift                                                (0)
#define MIS_IC2_DMA_RDLR_dmardl_mask                                                 (0x0000000F)
#define MIS_IC2_DMA_RDLR_dmardl(data)                                                (0x0000000F&((data)<<0))
#define MIS_IC2_DMA_RDLR_dmardl_src(data)                                            ((0x0000000F&(data))>>0)
#define MIS_IC2_DMA_RDLR_get_dmardl(data)                                            ((0x0000000F&(data))>>0)


#define MIS_IC2_SDA_SETUP                                                            0x9801B794
#define MIS_IC2_SDA_SETUP_reg_addr                                                   "0x9801B794"
#define MIS_IC2_SDA_SETUP_reg                                                        0x9801B794
#define set_MIS_IC2_SDA_SETUP_reg(data)   (*((volatile unsigned int*) MIS_IC2_SDA_SETUP_reg)=data)
#define get_MIS_IC2_SDA_SETUP_reg   (*((volatile unsigned int*) MIS_IC2_SDA_SETUP_reg))
#define MIS_IC2_SDA_SETUP_inst_adr                                                   "0x00E5"
#define MIS_IC2_SDA_SETUP_inst                                                       0x00E5
#define MIS_IC2_SDA_SETUP_sda_setup_shift                                            (0)
#define MIS_IC2_SDA_SETUP_sda_setup_mask                                             (0x000000FF)
#define MIS_IC2_SDA_SETUP_sda_setup(data)                                            (0x000000FF&((data)<<0))
#define MIS_IC2_SDA_SETUP_sda_setup_src(data)                                        ((0x000000FF&(data))>>0)
#define MIS_IC2_SDA_SETUP_get_sda_setup(data)                                        ((0x000000FF&(data))>>0)


#define MIS_IC2_ACK_GENERAL_CALL                                                     0x9801B798
#define MIS_IC2_ACK_GENERAL_CALL_reg_addr                                            "0x9801B798"
#define MIS_IC2_ACK_GENERAL_CALL_reg                                                 0x9801B798
#define set_MIS_IC2_ACK_GENERAL_CALL_reg(data)   (*((volatile unsigned int*) MIS_IC2_ACK_GENERAL_CALL_reg)=data)
#define get_MIS_IC2_ACK_GENERAL_CALL_reg   (*((volatile unsigned int*) MIS_IC2_ACK_GENERAL_CALL_reg))
#define MIS_IC2_ACK_GENERAL_CALL_inst_adr                                            "0x00E6"
#define MIS_IC2_ACK_GENERAL_CALL_inst                                                0x00E6
#define MIS_IC2_ACK_GENERAL_CALL_ack_gen_call_shift                                  (0)
#define MIS_IC2_ACK_GENERAL_CALL_ack_gen_call_mask                                   (0x00000001)
#define MIS_IC2_ACK_GENERAL_CALL_ack_gen_call(data)                                  (0x00000001&((data)<<0))
#define MIS_IC2_ACK_GENERAL_CALL_ack_gen_call_src(data)                              ((0x00000001&(data))>>0)
#define MIS_IC2_ACK_GENERAL_CALL_get_ack_gen_call(data)                              ((0x00000001&(data))>>0)


#define MIS_IC2_ENABLE_STATUS                                                        0x9801B79C
#define MIS_IC2_ENABLE_STATUS_reg_addr                                               "0x9801B79C"
#define MIS_IC2_ENABLE_STATUS_reg                                                    0x9801B79C
#define set_MIS_IC2_ENABLE_STATUS_reg(data)   (*((volatile unsigned int*) MIS_IC2_ENABLE_STATUS_reg)=data)
#define get_MIS_IC2_ENABLE_STATUS_reg   (*((volatile unsigned int*) MIS_IC2_ENABLE_STATUS_reg))
#define MIS_IC2_ENABLE_STATUS_inst_adr                                               "0x00E7"
#define MIS_IC2_ENABLE_STATUS_inst                                                   0x00E7
#define MIS_IC2_ENABLE_STATUS_slv_rx_data_lost_shift                                 (2)
#define MIS_IC2_ENABLE_STATUS_slv_rx_data_lost_mask                                  (0x00000004)
#define MIS_IC2_ENABLE_STATUS_slv_rx_data_lost(data)                                 (0x00000004&((data)<<2))
#define MIS_IC2_ENABLE_STATUS_slv_rx_data_lost_src(data)                             ((0x00000004&(data))>>2)
#define MIS_IC2_ENABLE_STATUS_get_slv_rx_data_lost(data)                             ((0x00000004&(data))>>2)
#define MIS_IC2_ENABLE_STATUS_slv_disabled_whi_shift                                 (1)
#define MIS_IC2_ENABLE_STATUS_slv_disabled_whi_mask                                  (0x00000002)
#define MIS_IC2_ENABLE_STATUS_slv_disabled_whi(data)                                 (0x00000002&((data)<<1))
#define MIS_IC2_ENABLE_STATUS_slv_disabled_whi_src(data)                             ((0x00000002&(data))>>1)
#define MIS_IC2_ENABLE_STATUS_get_slv_disabled_whi(data)                             ((0x00000002&(data))>>1)
#define MIS_IC2_ENABLE_STATUS_ic_en_shift                                            (0)
#define MIS_IC2_ENABLE_STATUS_ic_en_mask                                             (0x00000001)
#define MIS_IC2_ENABLE_STATUS_ic_en(data)                                            (0x00000001&((data)<<0))
#define MIS_IC2_ENABLE_STATUS_ic_en_src(data)                                        ((0x00000001&(data))>>0)
#define MIS_IC2_ENABLE_STATUS_get_ic_en(data)                                        ((0x00000001&(data))>>0)


#define MIS_IC2_COMP_PARAM_1                                                         0x9801B7F4
#define MIS_IC2_COMP_PARAM_1_reg_addr                                                "0x9801B7F4"
#define MIS_IC2_COMP_PARAM_1_reg                                                     0x9801B7F4
#define set_MIS_IC2_COMP_PARAM_1_reg(data)   (*((volatile unsigned int*) MIS_IC2_COMP_PARAM_1_reg)=data)
#define get_MIS_IC2_COMP_PARAM_1_reg   (*((volatile unsigned int*) MIS_IC2_COMP_PARAM_1_reg))
#define MIS_IC2_COMP_PARAM_1_inst_adr                                                "0x00FD"
#define MIS_IC2_COMP_PARAM_1_inst                                                    0x00FD
#define MIS_IC2_COMP_PARAM_1_tx_buffer_depth_shift                                   (16)
#define MIS_IC2_COMP_PARAM_1_tx_buffer_depth_mask                                    (0x00FF0000)
#define MIS_IC2_COMP_PARAM_1_tx_buffer_depth(data)                                   (0x00FF0000&((data)<<16))
#define MIS_IC2_COMP_PARAM_1_tx_buffer_depth_src(data)                               ((0x00FF0000&(data))>>16)
#define MIS_IC2_COMP_PARAM_1_get_tx_buffer_depth(data)                               ((0x00FF0000&(data))>>16)
#define MIS_IC2_COMP_PARAM_1_rx_buffer_depth_shift                                   (8)
#define MIS_IC2_COMP_PARAM_1_rx_buffer_depth_mask                                    (0x0000FF00)
#define MIS_IC2_COMP_PARAM_1_rx_buffer_depth(data)                                   (0x0000FF00&((data)<<8))
#define MIS_IC2_COMP_PARAM_1_rx_buffer_depth_src(data)                               ((0x0000FF00&(data))>>8)
#define MIS_IC2_COMP_PARAM_1_get_rx_buffer_depth(data)                               ((0x0000FF00&(data))>>8)
#define MIS_IC2_COMP_PARAM_1_add_encoded_params_shift                                (7)
#define MIS_IC2_COMP_PARAM_1_add_encoded_params_mask                                 (0x00000080)
#define MIS_IC2_COMP_PARAM_1_add_encoded_params(data)                                (0x00000080&((data)<<7))
#define MIS_IC2_COMP_PARAM_1_add_encoded_params_src(data)                            ((0x00000080&(data))>>7)
#define MIS_IC2_COMP_PARAM_1_get_add_encoded_params(data)                            ((0x00000080&(data))>>7)
#define MIS_IC2_COMP_PARAM_1_has_dma_shift                                           (6)
#define MIS_IC2_COMP_PARAM_1_has_dma_mask                                            (0x00000040)
#define MIS_IC2_COMP_PARAM_1_has_dma(data)                                           (0x00000040&((data)<<6))
#define MIS_IC2_COMP_PARAM_1_has_dma_src(data)                                       ((0x00000040&(data))>>6)
#define MIS_IC2_COMP_PARAM_1_get_has_dma(data)                                       ((0x00000040&(data))>>6)
#define MIS_IC2_COMP_PARAM_1_intr_io_shift                                           (5)
#define MIS_IC2_COMP_PARAM_1_intr_io_mask                                            (0x00000020)
#define MIS_IC2_COMP_PARAM_1_intr_io(data)                                           (0x00000020&((data)<<5))
#define MIS_IC2_COMP_PARAM_1_intr_io_src(data)                                       ((0x00000020&(data))>>5)
#define MIS_IC2_COMP_PARAM_1_get_intr_io(data)                                       ((0x00000020&(data))>>5)
#define MIS_IC2_COMP_PARAM_1_hc_count_values_shift                                   (4)
#define MIS_IC2_COMP_PARAM_1_hc_count_values_mask                                    (0x00000010)
#define MIS_IC2_COMP_PARAM_1_hc_count_values(data)                                   (0x00000010&((data)<<4))
#define MIS_IC2_COMP_PARAM_1_hc_count_values_src(data)                               ((0x00000010&(data))>>4)
#define MIS_IC2_COMP_PARAM_1_get_hc_count_values(data)                               ((0x00000010&(data))>>4)
#define MIS_IC2_COMP_PARAM_1_max_speed_mode_shift                                    (2)
#define MIS_IC2_COMP_PARAM_1_max_speed_mode_mask                                     (0x0000000C)
#define MIS_IC2_COMP_PARAM_1_max_speed_mode(data)                                    (0x0000000C&((data)<<2))
#define MIS_IC2_COMP_PARAM_1_max_speed_mode_src(data)                                ((0x0000000C&(data))>>2)
#define MIS_IC2_COMP_PARAM_1_get_max_speed_mode(data)                                ((0x0000000C&(data))>>2)
#define MIS_IC2_COMP_PARAM_1_apb_data_width_shift                                    (0)
#define MIS_IC2_COMP_PARAM_1_apb_data_width_mask                                     (0x00000003)
#define MIS_IC2_COMP_PARAM_1_apb_data_width(data)                                    (0x00000003&((data)<<0))
#define MIS_IC2_COMP_PARAM_1_apb_data_width_src(data)                                ((0x00000003&(data))>>0)
#define MIS_IC2_COMP_PARAM_1_get_apb_data_width(data)                                ((0x00000003&(data))>>0)


#define MIS_IC2_COMP_VERSION                                                         0x9801B7F8
#define MIS_IC2_COMP_VERSION_reg_addr                                                "0x9801B7F8"
#define MIS_IC2_COMP_VERSION_reg                                                     0x9801B7F8
#define set_MIS_IC2_COMP_VERSION_reg(data)   (*((volatile unsigned int*) MIS_IC2_COMP_VERSION_reg)=data)
#define get_MIS_IC2_COMP_VERSION_reg   (*((volatile unsigned int*) MIS_IC2_COMP_VERSION_reg))
#define MIS_IC2_COMP_VERSION_inst_adr                                                "0x00FE"
#define MIS_IC2_COMP_VERSION_inst                                                    0x00FE
#define MIS_IC2_COMP_VERSION_ic_comp_version_shift                                   (0)
#define MIS_IC2_COMP_VERSION_ic_comp_version_mask                                    (0xFFFFFFFF)
#define MIS_IC2_COMP_VERSION_ic_comp_version(data)                                   (0xFFFFFFFF&((data)<<0))
#define MIS_IC2_COMP_VERSION_ic_comp_version_src(data)                               ((0xFFFFFFFF&(data))>>0)
#define MIS_IC2_COMP_VERSION_get_ic_comp_version(data)                               ((0xFFFFFFFF&(data))>>0)


#define MIS_IC2_COMP_TYPE                                                            0x9801B7FC
#define MIS_IC2_COMP_TYPE_reg_addr                                                   "0x9801B7FC"
#define MIS_IC2_COMP_TYPE_reg                                                        0x9801B7FC
#define set_MIS_IC2_COMP_TYPE_reg(data)   (*((volatile unsigned int*) MIS_IC2_COMP_TYPE_reg)=data)
#define get_MIS_IC2_COMP_TYPE_reg   (*((volatile unsigned int*) MIS_IC2_COMP_TYPE_reg))
#define MIS_IC2_COMP_TYPE_inst_adr                                                   "0x00FF"
#define MIS_IC2_COMP_TYPE_inst                                                       0x00FF
#define MIS_IC2_COMP_TYPE_ic_comp_type_shift                                         (0)
#define MIS_IC2_COMP_TYPE_ic_comp_type_mask                                          (0xFFFFFFFF)
#define MIS_IC2_COMP_TYPE_ic_comp_type(data)                                         (0xFFFFFFFF&((data)<<0))
#define MIS_IC2_COMP_TYPE_ic_comp_type_src(data)                                     ((0xFFFFFFFF&(data))>>0)
#define MIS_IC2_COMP_TYPE_get_ic_comp_type(data)                                     ((0xFFFFFFFF&(data))>>0)


#define MIS_IC3_CON                                                                  0x9801B900
#define MIS_IC3_CON_reg_addr                                                         "0x9801B900"
#define MIS_IC3_CON_reg                                                              0x9801B900
#define set_MIS_IC3_CON_reg(data)   (*((volatile unsigned int*) MIS_IC3_CON_reg)=data)
#define get_MIS_IC3_CON_reg   (*((volatile unsigned int*) MIS_IC3_CON_reg))
#define MIS_IC3_CON_inst_adr                                                         "0x0040"
#define MIS_IC3_CON_inst                                                             0x0040
#define MIS_IC3_CON_ic_slave_disable_shift                                           (6)
#define MIS_IC3_CON_ic_slave_disable_mask                                            (0x00000040)
#define MIS_IC3_CON_ic_slave_disable(data)                                           (0x00000040&((data)<<6))
#define MIS_IC3_CON_ic_slave_disable_src(data)                                       ((0x00000040&(data))>>6)
#define MIS_IC3_CON_get_ic_slave_disable(data)                                       ((0x00000040&(data))>>6)
#define MIS_IC3_CON_ic_restart_en_shift                                              (5)
#define MIS_IC3_CON_ic_restart_en_mask                                               (0x00000020)
#define MIS_IC3_CON_ic_restart_en(data)                                              (0x00000020&((data)<<5))
#define MIS_IC3_CON_ic_restart_en_src(data)                                          ((0x00000020&(data))>>5)
#define MIS_IC3_CON_get_ic_restart_en(data)                                          ((0x00000020&(data))>>5)
#define MIS_IC3_CON_ic_10bitaddr_master_shift                                        (4)
#define MIS_IC3_CON_ic_10bitaddr_master_mask                                         (0x00000010)
#define MIS_IC3_CON_ic_10bitaddr_master(data)                                        (0x00000010&((data)<<4))
#define MIS_IC3_CON_ic_10bitaddr_master_src(data)                                    ((0x00000010&(data))>>4)
#define MIS_IC3_CON_get_ic_10bitaddr_master(data)                                    ((0x00000010&(data))>>4)
#define MIS_IC3_CON_ic_10bitaddr_slave_shift                                         (3)
#define MIS_IC3_CON_ic_10bitaddr_slave_mask                                          (0x00000008)
#define MIS_IC3_CON_ic_10bitaddr_slave(data)                                         (0x00000008&((data)<<3))
#define MIS_IC3_CON_ic_10bitaddr_slave_src(data)                                     ((0x00000008&(data))>>3)
#define MIS_IC3_CON_get_ic_10bitaddr_slave(data)                                     ((0x00000008&(data))>>3)
#define MIS_IC3_CON_speed_shift                                                      (1)
#define MIS_IC3_CON_speed_mask                                                       (0x00000006)
#define MIS_IC3_CON_speed(data)                                                      (0x00000006&((data)<<1))
#define MIS_IC3_CON_speed_src(data)                                                  ((0x00000006&(data))>>1)
#define MIS_IC3_CON_get_speed(data)                                                  ((0x00000006&(data))>>1)
#define MIS_IC3_CON_master_mode_shift                                                (0)
#define MIS_IC3_CON_master_mode_mask                                                 (0x00000001)
#define MIS_IC3_CON_master_mode(data)                                                (0x00000001&((data)<<0))
#define MIS_IC3_CON_master_mode_src(data)                                            ((0x00000001&(data))>>0)
#define MIS_IC3_CON_get_master_mode(data)                                            ((0x00000001&(data))>>0)


#define MIS_IC3_TAR                                                                  0x9801B904
#define MIS_IC3_TAR_reg_addr                                                         "0x9801B904"
#define MIS_IC3_TAR_reg                                                              0x9801B904
#define set_MIS_IC3_TAR_reg(data)   (*((volatile unsigned int*) MIS_IC3_TAR_reg)=data)
#define get_MIS_IC3_TAR_reg   (*((volatile unsigned int*) MIS_IC3_TAR_reg))
#define MIS_IC3_TAR_inst_adr                                                         "0x0041"
#define MIS_IC3_TAR_inst                                                             0x0041
#define MIS_IC3_TAR_ic_10bitaddr_master_shift                                        (12)
#define MIS_IC3_TAR_ic_10bitaddr_master_mask                                         (0x00001000)
#define MIS_IC3_TAR_ic_10bitaddr_master(data)                                        (0x00001000&((data)<<12))
#define MIS_IC3_TAR_ic_10bitaddr_master_src(data)                                    ((0x00001000&(data))>>12)
#define MIS_IC3_TAR_get_ic_10bitaddr_master(data)                                    ((0x00001000&(data))>>12)
#define MIS_IC3_TAR_special_shift                                                    (11)
#define MIS_IC3_TAR_special_mask                                                     (0x00000800)
#define MIS_IC3_TAR_special(data)                                                    (0x00000800&((data)<<11))
#define MIS_IC3_TAR_special_src(data)                                                ((0x00000800&(data))>>11)
#define MIS_IC3_TAR_get_special(data)                                                ((0x00000800&(data))>>11)
#define MIS_IC3_TAR_gc_or_start_shift                                                (10)
#define MIS_IC3_TAR_gc_or_start_mask                                                 (0x00000400)
#define MIS_IC3_TAR_gc_or_start(data)                                                (0x00000400&((data)<<10))
#define MIS_IC3_TAR_gc_or_start_src(data)                                            ((0x00000400&(data))>>10)
#define MIS_IC3_TAR_get_gc_or_start(data)                                            ((0x00000400&(data))>>10)
#define MIS_IC3_TAR_ic_tar_shift                                                     (0)
#define MIS_IC3_TAR_ic_tar_mask                                                      (0x000003FF)
#define MIS_IC3_TAR_ic_tar(data)                                                     (0x000003FF&((data)<<0))
#define MIS_IC3_TAR_ic_tar_src(data)                                                 ((0x000003FF&(data))>>0)
#define MIS_IC3_TAR_get_ic_tar(data)                                                 ((0x000003FF&(data))>>0)


#define MIS_IC3_SAR                                                                  0x9801B908
#define MIS_IC3_SAR_reg_addr                                                         "0x9801B908"
#define MIS_IC3_SAR_reg                                                              0x9801B908
#define set_MIS_IC3_SAR_reg(data)   (*((volatile unsigned int*) MIS_IC3_SAR_reg)=data)
#define get_MIS_IC3_SAR_reg   (*((volatile unsigned int*) MIS_IC3_SAR_reg))
#define MIS_IC3_SAR_inst_adr                                                         "0x0042"
#define MIS_IC3_SAR_inst                                                             0x0042
#define MIS_IC3_SAR_ic_sar_shift                                                     (0)
#define MIS_IC3_SAR_ic_sar_mask                                                      (0x000003FF)
#define MIS_IC3_SAR_ic_sar(data)                                                     (0x000003FF&((data)<<0))
#define MIS_IC3_SAR_ic_sar_src(data)                                                 ((0x000003FF&(data))>>0)
#define MIS_IC3_SAR_get_ic_sar(data)                                                 ((0x000003FF&(data))>>0)


#define MIS_IC3_HS_MADDR                                                             0x9801B90C
#define MIS_IC3_HS_MADDR_reg_addr                                                    "0x9801B90C"
#define MIS_IC3_HS_MADDR_reg                                                         0x9801B90C
#define set_MIS_IC3_HS_MADDR_reg(data)   (*((volatile unsigned int*) MIS_IC3_HS_MADDR_reg)=data)
#define get_MIS_IC3_HS_MADDR_reg   (*((volatile unsigned int*) MIS_IC3_HS_MADDR_reg))
#define MIS_IC3_HS_MADDR_inst_adr                                                    "0x0043"
#define MIS_IC3_HS_MADDR_inst                                                        0x0043
#define MIS_IC3_HS_MADDR_ic_hs_mar_shift                                             (0)
#define MIS_IC3_HS_MADDR_ic_hs_mar_mask                                              (0x00000007)
#define MIS_IC3_HS_MADDR_ic_hs_mar(data)                                             (0x00000007&((data)<<0))
#define MIS_IC3_HS_MADDR_ic_hs_mar_src(data)                                         ((0x00000007&(data))>>0)
#define MIS_IC3_HS_MADDR_get_ic_hs_mar(data)                                         ((0x00000007&(data))>>0)


#define MIS_IC3_DATA_CMD                                                             0x9801B910
#define MIS_IC3_DATA_CMD_reg_addr                                                    "0x9801B910"
#define MIS_IC3_DATA_CMD_reg                                                         0x9801B910
#define set_MIS_IC3_DATA_CMD_reg(data)   (*((volatile unsigned int*) MIS_IC3_DATA_CMD_reg)=data)
#define get_MIS_IC3_DATA_CMD_reg   (*((volatile unsigned int*) MIS_IC3_DATA_CMD_reg))
#define MIS_IC3_DATA_CMD_inst_adr                                                    "0x0044"
#define MIS_IC3_DATA_CMD_inst                                                        0x0044
#define MIS_IC3_DATA_CMD_restart_shift                                               (10)
#define MIS_IC3_DATA_CMD_restart_mask                                                (0x00000400)
#define MIS_IC3_DATA_CMD_restart(data)                                               (0x00000400&((data)<<10))
#define MIS_IC3_DATA_CMD_restart_src(data)                                           ((0x00000400&(data))>>10)
#define MIS_IC3_DATA_CMD_get_restart(data)                                           ((0x00000400&(data))>>10)
#define MIS_IC3_DATA_CMD_stop_shift                                                  (9)
#define MIS_IC3_DATA_CMD_stop_mask                                                   (0x00000200)
#define MIS_IC3_DATA_CMD_stop(data)                                                  (0x00000200&((data)<<9))
#define MIS_IC3_DATA_CMD_stop_src(data)                                              ((0x00000200&(data))>>9)
#define MIS_IC3_DATA_CMD_get_stop(data)                                              ((0x00000200&(data))>>9)
#define MIS_IC3_DATA_CMD_cmd_shift                                                   (8)
#define MIS_IC3_DATA_CMD_cmd_mask                                                    (0x00000100)
#define MIS_IC3_DATA_CMD_cmd(data)                                                   (0x00000100&((data)<<8))
#define MIS_IC3_DATA_CMD_cmd_src(data)                                               ((0x00000100&(data))>>8)
#define MIS_IC3_DATA_CMD_get_cmd(data)                                               ((0x00000100&(data))>>8)
#define MIS_IC3_DATA_CMD_dat_shift                                                   (0)
#define MIS_IC3_DATA_CMD_dat_mask                                                    (0x000000FF)
#define MIS_IC3_DATA_CMD_dat(data)                                                   (0x000000FF&((data)<<0))
#define MIS_IC3_DATA_CMD_dat_src(data)                                               ((0x000000FF&(data))>>0)
#define MIS_IC3_DATA_CMD_get_dat(data)                                               ((0x000000FF&(data))>>0)


#define MIS_IC3_SS_SCL_HCNT                                                          0x9801B914
#define MIS_IC3_SS_SCL_HCNT_reg_addr                                                 "0x9801B914"
#define MIS_IC3_SS_SCL_HCNT_reg                                                      0x9801B914
#define set_MIS_IC3_SS_SCL_HCNT_reg(data)   (*((volatile unsigned int*) MIS_IC3_SS_SCL_HCNT_reg)=data)
#define get_MIS_IC3_SS_SCL_HCNT_reg   (*((volatile unsigned int*) MIS_IC3_SS_SCL_HCNT_reg))
#define MIS_IC3_SS_SCL_HCNT_inst_adr                                                 "0x0045"
#define MIS_IC3_SS_SCL_HCNT_inst                                                     0x0045
#define MIS_IC3_SS_SCL_HCNT_ic_ss_scl_hcnt_shift                                     (0)
#define MIS_IC3_SS_SCL_HCNT_ic_ss_scl_hcnt_mask                                      (0x0000FFFF)
#define MIS_IC3_SS_SCL_HCNT_ic_ss_scl_hcnt(data)                                     (0x0000FFFF&((data)<<0))
#define MIS_IC3_SS_SCL_HCNT_ic_ss_scl_hcnt_src(data)                                 ((0x0000FFFF&(data))>>0)
#define MIS_IC3_SS_SCL_HCNT_get_ic_ss_scl_hcnt(data)                                 ((0x0000FFFF&(data))>>0)


#define MIS_IC3_SS_SCL_LCNT                                                          0x9801B918
#define MIS_IC3_SS_SCL_LCNT_reg_addr                                                 "0x9801B918"
#define MIS_IC3_SS_SCL_LCNT_reg                                                      0x9801B918
#define set_MIS_IC3_SS_SCL_LCNT_reg(data)   (*((volatile unsigned int*) MIS_IC3_SS_SCL_LCNT_reg)=data)
#define get_MIS_IC3_SS_SCL_LCNT_reg   (*((volatile unsigned int*) MIS_IC3_SS_SCL_LCNT_reg))
#define MIS_IC3_SS_SCL_LCNT_inst_adr                                                 "0x0046"
#define MIS_IC3_SS_SCL_LCNT_inst                                                     0x0046
#define MIS_IC3_SS_SCL_LCNT_ic_ss_scl_lcnt_shift                                     (0)
#define MIS_IC3_SS_SCL_LCNT_ic_ss_scl_lcnt_mask                                      (0x0000FFFF)
#define MIS_IC3_SS_SCL_LCNT_ic_ss_scl_lcnt(data)                                     (0x0000FFFF&((data)<<0))
#define MIS_IC3_SS_SCL_LCNT_ic_ss_scl_lcnt_src(data)                                 ((0x0000FFFF&(data))>>0)
#define MIS_IC3_SS_SCL_LCNT_get_ic_ss_scl_lcnt(data)                                 ((0x0000FFFF&(data))>>0)


#define MIS_IC3_FS_SCL_HCNT                                                          0x9801B91C
#define MIS_IC3_FS_SCL_HCNT_reg_addr                                                 "0x9801B91C"
#define MIS_IC3_FS_SCL_HCNT_reg                                                      0x9801B91C
#define set_MIS_IC3_FS_SCL_HCNT_reg(data)   (*((volatile unsigned int*) MIS_IC3_FS_SCL_HCNT_reg)=data)
#define get_MIS_IC3_FS_SCL_HCNT_reg   (*((volatile unsigned int*) MIS_IC3_FS_SCL_HCNT_reg))
#define MIS_IC3_FS_SCL_HCNT_inst_adr                                                 "0x0047"
#define MIS_IC3_FS_SCL_HCNT_inst                                                     0x0047
#define MIS_IC3_FS_SCL_HCNT_ic_fs_scl_hcnt_shift                                     (0)
#define MIS_IC3_FS_SCL_HCNT_ic_fs_scl_hcnt_mask                                      (0x0000FFFF)
#define MIS_IC3_FS_SCL_HCNT_ic_fs_scl_hcnt(data)                                     (0x0000FFFF&((data)<<0))
#define MIS_IC3_FS_SCL_HCNT_ic_fs_scl_hcnt_src(data)                                 ((0x0000FFFF&(data))>>0)
#define MIS_IC3_FS_SCL_HCNT_get_ic_fs_scl_hcnt(data)                                 ((0x0000FFFF&(data))>>0)


#define MIS_IC3_FS_SCL_LCNT                                                          0x9801B920
#define MIS_IC3_FS_SCL_LCNT_reg_addr                                                 "0x9801B920"
#define MIS_IC3_FS_SCL_LCNT_reg                                                      0x9801B920
#define set_MIS_IC3_FS_SCL_LCNT_reg(data)   (*((volatile unsigned int*) MIS_IC3_FS_SCL_LCNT_reg)=data)
#define get_MIS_IC3_FS_SCL_LCNT_reg   (*((volatile unsigned int*) MIS_IC3_FS_SCL_LCNT_reg))
#define MIS_IC3_FS_SCL_LCNT_inst_adr                                                 "0x0048"
#define MIS_IC3_FS_SCL_LCNT_inst                                                     0x0048
#define MIS_IC3_FS_SCL_LCNT_ic_fs_scl_lcnt_shift                                     (0)
#define MIS_IC3_FS_SCL_LCNT_ic_fs_scl_lcnt_mask                                      (0x0000FFFF)
#define MIS_IC3_FS_SCL_LCNT_ic_fs_scl_lcnt(data)                                     (0x0000FFFF&((data)<<0))
#define MIS_IC3_FS_SCL_LCNT_ic_fs_scl_lcnt_src(data)                                 ((0x0000FFFF&(data))>>0)
#define MIS_IC3_FS_SCL_LCNT_get_ic_fs_scl_lcnt(data)                                 ((0x0000FFFF&(data))>>0)


#define MIS_IC3_INTR_STAT                                                            0x9801B92C
#define MIS_IC3_INTR_STAT_reg_addr                                                   "0x9801B92C"
#define MIS_IC3_INTR_STAT_reg                                                        0x9801B92C
#define set_MIS_IC3_INTR_STAT_reg(data)   (*((volatile unsigned int*) MIS_IC3_INTR_STAT_reg)=data)
#define get_MIS_IC3_INTR_STAT_reg   (*((volatile unsigned int*) MIS_IC3_INTR_STAT_reg))
#define MIS_IC3_INTR_STAT_inst_adr                                                   "0x004B"
#define MIS_IC3_INTR_STAT_inst                                                       0x004B
#define MIS_IC3_INTR_STAT_r_gen_call_shift                                           (11)
#define MIS_IC3_INTR_STAT_r_gen_call_mask                                            (0x00000800)
#define MIS_IC3_INTR_STAT_r_gen_call(data)                                           (0x00000800&((data)<<11))
#define MIS_IC3_INTR_STAT_r_gen_call_src(data)                                       ((0x00000800&(data))>>11)
#define MIS_IC3_INTR_STAT_get_r_gen_call(data)                                       ((0x00000800&(data))>>11)
#define MIS_IC3_INTR_STAT_r_start_det_shift                                          (10)
#define MIS_IC3_INTR_STAT_r_start_det_mask                                           (0x00000400)
#define MIS_IC3_INTR_STAT_r_start_det(data)                                          (0x00000400&((data)<<10))
#define MIS_IC3_INTR_STAT_r_start_det_src(data)                                      ((0x00000400&(data))>>10)
#define MIS_IC3_INTR_STAT_get_r_start_det(data)                                      ((0x00000400&(data))>>10)
#define MIS_IC3_INTR_STAT_r_stop_det_shift                                           (9)
#define MIS_IC3_INTR_STAT_r_stop_det_mask                                            (0x00000200)
#define MIS_IC3_INTR_STAT_r_stop_det(data)                                           (0x00000200&((data)<<9))
#define MIS_IC3_INTR_STAT_r_stop_det_src(data)                                       ((0x00000200&(data))>>9)
#define MIS_IC3_INTR_STAT_get_r_stop_det(data)                                       ((0x00000200&(data))>>9)
#define MIS_IC3_INTR_STAT_r_activity_shift                                           (8)
#define MIS_IC3_INTR_STAT_r_activity_mask                                            (0x00000100)
#define MIS_IC3_INTR_STAT_r_activity(data)                                           (0x00000100&((data)<<8))
#define MIS_IC3_INTR_STAT_r_activity_src(data)                                       ((0x00000100&(data))>>8)
#define MIS_IC3_INTR_STAT_get_r_activity(data)                                       ((0x00000100&(data))>>8)
#define MIS_IC3_INTR_STAT_r_rx_done_shift                                            (7)
#define MIS_IC3_INTR_STAT_r_rx_done_mask                                             (0x00000080)
#define MIS_IC3_INTR_STAT_r_rx_done(data)                                            (0x00000080&((data)<<7))
#define MIS_IC3_INTR_STAT_r_rx_done_src(data)                                        ((0x00000080&(data))>>7)
#define MIS_IC3_INTR_STAT_get_r_rx_done(data)                                        ((0x00000080&(data))>>7)
#define MIS_IC3_INTR_STAT_r_tx_abrt_shift                                            (6)
#define MIS_IC3_INTR_STAT_r_tx_abrt_mask                                             (0x00000040)
#define MIS_IC3_INTR_STAT_r_tx_abrt(data)                                            (0x00000040&((data)<<6))
#define MIS_IC3_INTR_STAT_r_tx_abrt_src(data)                                        ((0x00000040&(data))>>6)
#define MIS_IC3_INTR_STAT_get_r_tx_abrt(data)                                        ((0x00000040&(data))>>6)
#define MIS_IC3_INTR_STAT_r_rd_req_shift                                             (5)
#define MIS_IC3_INTR_STAT_r_rd_req_mask                                              (0x00000020)
#define MIS_IC3_INTR_STAT_r_rd_req(data)                                             (0x00000020&((data)<<5))
#define MIS_IC3_INTR_STAT_r_rd_req_src(data)                                         ((0x00000020&(data))>>5)
#define MIS_IC3_INTR_STAT_get_r_rd_req(data)                                         ((0x00000020&(data))>>5)
#define MIS_IC3_INTR_STAT_r_tx_empty_shift                                           (4)
#define MIS_IC3_INTR_STAT_r_tx_empty_mask                                            (0x00000010)
#define MIS_IC3_INTR_STAT_r_tx_empty(data)                                           (0x00000010&((data)<<4))
#define MIS_IC3_INTR_STAT_r_tx_empty_src(data)                                       ((0x00000010&(data))>>4)
#define MIS_IC3_INTR_STAT_get_r_tx_empty(data)                                       ((0x00000010&(data))>>4)
#define MIS_IC3_INTR_STAT_r_tx_over_shift                                            (3)
#define MIS_IC3_INTR_STAT_r_tx_over_mask                                             (0x00000008)
#define MIS_IC3_INTR_STAT_r_tx_over(data)                                            (0x00000008&((data)<<3))
#define MIS_IC3_INTR_STAT_r_tx_over_src(data)                                        ((0x00000008&(data))>>3)
#define MIS_IC3_INTR_STAT_get_r_tx_over(data)                                        ((0x00000008&(data))>>3)
#define MIS_IC3_INTR_STAT_r_rx_full_shift                                            (2)
#define MIS_IC3_INTR_STAT_r_rx_full_mask                                             (0x00000004)
#define MIS_IC3_INTR_STAT_r_rx_full(data)                                            (0x00000004&((data)<<2))
#define MIS_IC3_INTR_STAT_r_rx_full_src(data)                                        ((0x00000004&(data))>>2)
#define MIS_IC3_INTR_STAT_get_r_rx_full(data)                                        ((0x00000004&(data))>>2)
#define MIS_IC3_INTR_STAT_r_rx_over_shift                                            (1)
#define MIS_IC3_INTR_STAT_r_rx_over_mask                                             (0x00000002)
#define MIS_IC3_INTR_STAT_r_rx_over(data)                                            (0x00000002&((data)<<1))
#define MIS_IC3_INTR_STAT_r_rx_over_src(data)                                        ((0x00000002&(data))>>1)
#define MIS_IC3_INTR_STAT_get_r_rx_over(data)                                        ((0x00000002&(data))>>1)
#define MIS_IC3_INTR_STAT_r_rx_under_shift                                           (0)
#define MIS_IC3_INTR_STAT_r_rx_under_mask                                            (0x00000001)
#define MIS_IC3_INTR_STAT_r_rx_under(data)                                           (0x00000001&((data)<<0))
#define MIS_IC3_INTR_STAT_r_rx_under_src(data)                                       ((0x00000001&(data))>>0)
#define MIS_IC3_INTR_STAT_get_r_rx_under(data)                                       ((0x00000001&(data))>>0)


#define MIS_IC3_INTR_MASK                                                            0x9801B930
#define MIS_IC3_INTR_MASK_reg_addr                                                   "0x9801B930"
#define MIS_IC3_INTR_MASK_reg                                                        0x9801B930
#define set_MIS_IC3_INTR_MASK_reg(data)   (*((volatile unsigned int*) MIS_IC3_INTR_MASK_reg)=data)
#define get_MIS_IC3_INTR_MASK_reg   (*((volatile unsigned int*) MIS_IC3_INTR_MASK_reg))
#define MIS_IC3_INTR_MASK_inst_adr                                                   "0x004C"
#define MIS_IC3_INTR_MASK_inst                                                       0x004C
#define MIS_IC3_INTR_MASK_m_gen_call_shift                                           (11)
#define MIS_IC3_INTR_MASK_m_gen_call_mask                                            (0x00000800)
#define MIS_IC3_INTR_MASK_m_gen_call(data)                                           (0x00000800&((data)<<11))
#define MIS_IC3_INTR_MASK_m_gen_call_src(data)                                       ((0x00000800&(data))>>11)
#define MIS_IC3_INTR_MASK_get_m_gen_call(data)                                       ((0x00000800&(data))>>11)
#define MIS_IC3_INTR_MASK_m_start_det_shift                                          (10)
#define MIS_IC3_INTR_MASK_m_start_det_mask                                           (0x00000400)
#define MIS_IC3_INTR_MASK_m_start_det(data)                                          (0x00000400&((data)<<10))
#define MIS_IC3_INTR_MASK_m_start_det_src(data)                                      ((0x00000400&(data))>>10)
#define MIS_IC3_INTR_MASK_get_m_start_det(data)                                      ((0x00000400&(data))>>10)
#define MIS_IC3_INTR_MASK_m_stop_det_shift                                           (9)
#define MIS_IC3_INTR_MASK_m_stop_det_mask                                            (0x00000200)
#define MIS_IC3_INTR_MASK_m_stop_det(data)                                           (0x00000200&((data)<<9))
#define MIS_IC3_INTR_MASK_m_stop_det_src(data)                                       ((0x00000200&(data))>>9)
#define MIS_IC3_INTR_MASK_get_m_stop_det(data)                                       ((0x00000200&(data))>>9)
#define MIS_IC3_INTR_MASK_m_activity_shift                                           (8)
#define MIS_IC3_INTR_MASK_m_activity_mask                                            (0x00000100)
#define MIS_IC3_INTR_MASK_m_activity(data)                                           (0x00000100&((data)<<8))
#define MIS_IC3_INTR_MASK_m_activity_src(data)                                       ((0x00000100&(data))>>8)
#define MIS_IC3_INTR_MASK_get_m_activity(data)                                       ((0x00000100&(data))>>8)
#define MIS_IC3_INTR_MASK_m_rx_done_shift                                            (7)
#define MIS_IC3_INTR_MASK_m_rx_done_mask                                             (0x00000080)
#define MIS_IC3_INTR_MASK_m_rx_done(data)                                            (0x00000080&((data)<<7))
#define MIS_IC3_INTR_MASK_m_rx_done_src(data)                                        ((0x00000080&(data))>>7)
#define MIS_IC3_INTR_MASK_get_m_rx_done(data)                                        ((0x00000080&(data))>>7)
#define MIS_IC3_INTR_MASK_m_tx_abrt_shift                                            (6)
#define MIS_IC3_INTR_MASK_m_tx_abrt_mask                                             (0x00000040)
#define MIS_IC3_INTR_MASK_m_tx_abrt(data)                                            (0x00000040&((data)<<6))
#define MIS_IC3_INTR_MASK_m_tx_abrt_src(data)                                        ((0x00000040&(data))>>6)
#define MIS_IC3_INTR_MASK_get_m_tx_abrt(data)                                        ((0x00000040&(data))>>6)
#define MIS_IC3_INTR_MASK_m_rd_req_shift                                             (5)
#define MIS_IC3_INTR_MASK_m_rd_req_mask                                              (0x00000020)
#define MIS_IC3_INTR_MASK_m_rd_req(data)                                             (0x00000020&((data)<<5))
#define MIS_IC3_INTR_MASK_m_rd_req_src(data)                                         ((0x00000020&(data))>>5)
#define MIS_IC3_INTR_MASK_get_m_rd_req(data)                                         ((0x00000020&(data))>>5)
#define MIS_IC3_INTR_MASK_m_tx_empty_shift                                           (4)
#define MIS_IC3_INTR_MASK_m_tx_empty_mask                                            (0x00000010)
#define MIS_IC3_INTR_MASK_m_tx_empty(data)                                           (0x00000010&((data)<<4))
#define MIS_IC3_INTR_MASK_m_tx_empty_src(data)                                       ((0x00000010&(data))>>4)
#define MIS_IC3_INTR_MASK_get_m_tx_empty(data)                                       ((0x00000010&(data))>>4)
#define MIS_IC3_INTR_MASK_m_tx_over_shift                                            (3)
#define MIS_IC3_INTR_MASK_m_tx_over_mask                                             (0x00000008)
#define MIS_IC3_INTR_MASK_m_tx_over(data)                                            (0x00000008&((data)<<3))
#define MIS_IC3_INTR_MASK_m_tx_over_src(data)                                        ((0x00000008&(data))>>3)
#define MIS_IC3_INTR_MASK_get_m_tx_over(data)                                        ((0x00000008&(data))>>3)
#define MIS_IC3_INTR_MASK_m_rx_full_shift                                            (2)
#define MIS_IC3_INTR_MASK_m_rx_full_mask                                             (0x00000004)
#define MIS_IC3_INTR_MASK_m_rx_full(data)                                            (0x00000004&((data)<<2))
#define MIS_IC3_INTR_MASK_m_rx_full_src(data)                                        ((0x00000004&(data))>>2)
#define MIS_IC3_INTR_MASK_get_m_rx_full(data)                                        ((0x00000004&(data))>>2)
#define MIS_IC3_INTR_MASK_m_rx_over_shift                                            (1)
#define MIS_IC3_INTR_MASK_m_rx_over_mask                                             (0x00000002)
#define MIS_IC3_INTR_MASK_m_rx_over(data)                                            (0x00000002&((data)<<1))
#define MIS_IC3_INTR_MASK_m_rx_over_src(data)                                        ((0x00000002&(data))>>1)
#define MIS_IC3_INTR_MASK_get_m_rx_over(data)                                        ((0x00000002&(data))>>1)
#define MIS_IC3_INTR_MASK_m_rx_under_shift                                           (0)
#define MIS_IC3_INTR_MASK_m_rx_under_mask                                            (0x00000001)
#define MIS_IC3_INTR_MASK_m_rx_under(data)                                           (0x00000001&((data)<<0))
#define MIS_IC3_INTR_MASK_m_rx_under_src(data)                                       ((0x00000001&(data))>>0)
#define MIS_IC3_INTR_MASK_get_m_rx_under(data)                                       ((0x00000001&(data))>>0)


#define MIS_IC3_RAW_INTR_STAT                                                        0x9801B934
#define MIS_IC3_RAW_INTR_STAT_reg_addr                                               "0x9801B934"
#define MIS_IC3_RAW_INTR_STAT_reg                                                    0x9801B934
#define set_MIS_IC3_RAW_INTR_STAT_reg(data)   (*((volatile unsigned int*) MIS_IC3_RAW_INTR_STAT_reg)=data)
#define get_MIS_IC3_RAW_INTR_STAT_reg   (*((volatile unsigned int*) MIS_IC3_RAW_INTR_STAT_reg))
#define MIS_IC3_RAW_INTR_STAT_inst_adr                                               "0x004D"
#define MIS_IC3_RAW_INTR_STAT_inst                                                   0x004D
#define MIS_IC3_RAW_INTR_STAT_gen_call_shift                                         (11)
#define MIS_IC3_RAW_INTR_STAT_gen_call_mask                                          (0x00000800)
#define MIS_IC3_RAW_INTR_STAT_gen_call(data)                                         (0x00000800&((data)<<11))
#define MIS_IC3_RAW_INTR_STAT_gen_call_src(data)                                     ((0x00000800&(data))>>11)
#define MIS_IC3_RAW_INTR_STAT_get_gen_call(data)                                     ((0x00000800&(data))>>11)
#define MIS_IC3_RAW_INTR_STAT_start_det_shift                                        (10)
#define MIS_IC3_RAW_INTR_STAT_start_det_mask                                         (0x00000400)
#define MIS_IC3_RAW_INTR_STAT_start_det(data)                                        (0x00000400&((data)<<10))
#define MIS_IC3_RAW_INTR_STAT_start_det_src(data)                                    ((0x00000400&(data))>>10)
#define MIS_IC3_RAW_INTR_STAT_get_start_det(data)                                    ((0x00000400&(data))>>10)
#define MIS_IC3_RAW_INTR_STAT_stop_det_shift                                         (9)
#define MIS_IC3_RAW_INTR_STAT_stop_det_mask                                          (0x00000200)
#define MIS_IC3_RAW_INTR_STAT_stop_det(data)                                         (0x00000200&((data)<<9))
#define MIS_IC3_RAW_INTR_STAT_stop_det_src(data)                                     ((0x00000200&(data))>>9)
#define MIS_IC3_RAW_INTR_STAT_get_stop_det(data)                                     ((0x00000200&(data))>>9)
#define MIS_IC3_RAW_INTR_STAT_activity_shift                                         (8)
#define MIS_IC3_RAW_INTR_STAT_activity_mask                                          (0x00000100)
#define MIS_IC3_RAW_INTR_STAT_activity(data)                                         (0x00000100&((data)<<8))
#define MIS_IC3_RAW_INTR_STAT_activity_src(data)                                     ((0x00000100&(data))>>8)
#define MIS_IC3_RAW_INTR_STAT_get_activity(data)                                     ((0x00000100&(data))>>8)
#define MIS_IC3_RAW_INTR_STAT_rx_done_shift                                          (7)
#define MIS_IC3_RAW_INTR_STAT_rx_done_mask                                           (0x00000080)
#define MIS_IC3_RAW_INTR_STAT_rx_done(data)                                          (0x00000080&((data)<<7))
#define MIS_IC3_RAW_INTR_STAT_rx_done_src(data)                                      ((0x00000080&(data))>>7)
#define MIS_IC3_RAW_INTR_STAT_get_rx_done(data)                                      ((0x00000080&(data))>>7)
#define MIS_IC3_RAW_INTR_STAT_tx_abrt_shift                                          (6)
#define MIS_IC3_RAW_INTR_STAT_tx_abrt_mask                                           (0x00000040)
#define MIS_IC3_RAW_INTR_STAT_tx_abrt(data)                                          (0x00000040&((data)<<6))
#define MIS_IC3_RAW_INTR_STAT_tx_abrt_src(data)                                      ((0x00000040&(data))>>6)
#define MIS_IC3_RAW_INTR_STAT_get_tx_abrt(data)                                      ((0x00000040&(data))>>6)
#define MIS_IC3_RAW_INTR_STAT_rd_req_shift                                           (5)
#define MIS_IC3_RAW_INTR_STAT_rd_req_mask                                            (0x00000020)
#define MIS_IC3_RAW_INTR_STAT_rd_req(data)                                           (0x00000020&((data)<<5))
#define MIS_IC3_RAW_INTR_STAT_rd_req_src(data)                                       ((0x00000020&(data))>>5)
#define MIS_IC3_RAW_INTR_STAT_get_rd_req(data)                                       ((0x00000020&(data))>>5)
#define MIS_IC3_RAW_INTR_STAT_tx_empty_shift                                         (4)
#define MIS_IC3_RAW_INTR_STAT_tx_empty_mask                                          (0x00000010)
#define MIS_IC3_RAW_INTR_STAT_tx_empty(data)                                         (0x00000010&((data)<<4))
#define MIS_IC3_RAW_INTR_STAT_tx_empty_src(data)                                     ((0x00000010&(data))>>4)
#define MIS_IC3_RAW_INTR_STAT_get_tx_empty(data)                                     ((0x00000010&(data))>>4)
#define MIS_IC3_RAW_INTR_STAT_tx_over_shift                                          (3)
#define MIS_IC3_RAW_INTR_STAT_tx_over_mask                                           (0x00000008)
#define MIS_IC3_RAW_INTR_STAT_tx_over(data)                                          (0x00000008&((data)<<3))
#define MIS_IC3_RAW_INTR_STAT_tx_over_src(data)                                      ((0x00000008&(data))>>3)
#define MIS_IC3_RAW_INTR_STAT_get_tx_over(data)                                      ((0x00000008&(data))>>3)
#define MIS_IC3_RAW_INTR_STAT_rx_full_shift                                          (2)
#define MIS_IC3_RAW_INTR_STAT_rx_full_mask                                           (0x00000004)
#define MIS_IC3_RAW_INTR_STAT_rx_full(data)                                          (0x00000004&((data)<<2))
#define MIS_IC3_RAW_INTR_STAT_rx_full_src(data)                                      ((0x00000004&(data))>>2)
#define MIS_IC3_RAW_INTR_STAT_get_rx_full(data)                                      ((0x00000004&(data))>>2)
#define MIS_IC3_RAW_INTR_STAT_rx_over_shift                                          (1)
#define MIS_IC3_RAW_INTR_STAT_rx_over_mask                                           (0x00000002)
#define MIS_IC3_RAW_INTR_STAT_rx_over(data)                                          (0x00000002&((data)<<1))
#define MIS_IC3_RAW_INTR_STAT_rx_over_src(data)                                      ((0x00000002&(data))>>1)
#define MIS_IC3_RAW_INTR_STAT_get_rx_over(data)                                      ((0x00000002&(data))>>1)
#define MIS_IC3_RAW_INTR_STAT_rx_under_shift                                         (0)
#define MIS_IC3_RAW_INTR_STAT_rx_under_mask                                          (0x00000001)
#define MIS_IC3_RAW_INTR_STAT_rx_under(data)                                         (0x00000001&((data)<<0))
#define MIS_IC3_RAW_INTR_STAT_rx_under_src(data)                                     ((0x00000001&(data))>>0)
#define MIS_IC3_RAW_INTR_STAT_get_rx_under(data)                                     ((0x00000001&(data))>>0)


#define MIS_IC3_RX_TL                                                                0x9801B938
#define MIS_IC3_RX_TL_reg_addr                                                       "0x9801B938"
#define MIS_IC3_RX_TL_reg                                                            0x9801B938
#define set_MIS_IC3_RX_TL_reg(data)   (*((volatile unsigned int*) MIS_IC3_RX_TL_reg)=data)
#define get_MIS_IC3_RX_TL_reg   (*((volatile unsigned int*) MIS_IC3_RX_TL_reg))
#define MIS_IC3_RX_TL_inst_adr                                                       "0x004E"
#define MIS_IC3_RX_TL_inst                                                           0x004E
#define MIS_IC3_RX_TL_rx_tl_shift                                                    (0)
#define MIS_IC3_RX_TL_rx_tl_mask                                                     (0x000000FF)
#define MIS_IC3_RX_TL_rx_tl(data)                                                    (0x000000FF&((data)<<0))
#define MIS_IC3_RX_TL_rx_tl_src(data)                                                ((0x000000FF&(data))>>0)
#define MIS_IC3_RX_TL_get_rx_tl(data)                                                ((0x000000FF&(data))>>0)


#define MIS_IC3_TX_TL                                                                0x9801B93C
#define MIS_IC3_TX_TL_reg_addr                                                       "0x9801B93C"
#define MIS_IC3_TX_TL_reg                                                            0x9801B93C
#define set_MIS_IC3_TX_TL_reg(data)   (*((volatile unsigned int*) MIS_IC3_TX_TL_reg)=data)
#define get_MIS_IC3_TX_TL_reg   (*((volatile unsigned int*) MIS_IC3_TX_TL_reg))
#define MIS_IC3_TX_TL_inst_adr                                                       "0x004F"
#define MIS_IC3_TX_TL_inst                                                           0x004F
#define MIS_IC3_TX_TL_tx_tl_shift                                                    (0)
#define MIS_IC3_TX_TL_tx_tl_mask                                                     (0x000000FF)
#define MIS_IC3_TX_TL_tx_tl(data)                                                    (0x000000FF&((data)<<0))
#define MIS_IC3_TX_TL_tx_tl_src(data)                                                ((0x000000FF&(data))>>0)
#define MIS_IC3_TX_TL_get_tx_tl(data)                                                ((0x000000FF&(data))>>0)


#define MIS_IC3_CLR_INTR                                                             0x9801B940
#define MIS_IC3_CLR_INTR_reg_addr                                                    "0x9801B940"
#define MIS_IC3_CLR_INTR_reg                                                         0x9801B940
#define set_MIS_IC3_CLR_INTR_reg(data)   (*((volatile unsigned int*) MIS_IC3_CLR_INTR_reg)=data)
#define get_MIS_IC3_CLR_INTR_reg   (*((volatile unsigned int*) MIS_IC3_CLR_INTR_reg))
#define MIS_IC3_CLR_INTR_inst_adr                                                    "0x0050"
#define MIS_IC3_CLR_INTR_inst                                                        0x0050
#define MIS_IC3_CLR_INTR_clr_intr_shift                                              (0)
#define MIS_IC3_CLR_INTR_clr_intr_mask                                               (0x00000001)
#define MIS_IC3_CLR_INTR_clr_intr(data)                                              (0x00000001&((data)<<0))
#define MIS_IC3_CLR_INTR_clr_intr_src(data)                                          ((0x00000001&(data))>>0)
#define MIS_IC3_CLR_INTR_get_clr_intr(data)                                          ((0x00000001&(data))>>0)


#define MIS_IC3_CLR_RX_UNDER                                                         0x9801B944
#define MIS_IC3_CLR_RX_UNDER_reg_addr                                                "0x9801B944"
#define MIS_IC3_CLR_RX_UNDER_reg                                                     0x9801B944
#define set_MIS_IC3_CLR_RX_UNDER_reg(data)   (*((volatile unsigned int*) MIS_IC3_CLR_RX_UNDER_reg)=data)
#define get_MIS_IC3_CLR_RX_UNDER_reg   (*((volatile unsigned int*) MIS_IC3_CLR_RX_UNDER_reg))
#define MIS_IC3_CLR_RX_UNDER_inst_adr                                                "0x0051"
#define MIS_IC3_CLR_RX_UNDER_inst                                                    0x0051
#define MIS_IC3_CLR_RX_UNDER_clr_rx_under_shift                                      (0)
#define MIS_IC3_CLR_RX_UNDER_clr_rx_under_mask                                       (0x00000001)
#define MIS_IC3_CLR_RX_UNDER_clr_rx_under(data)                                      (0x00000001&((data)<<0))
#define MIS_IC3_CLR_RX_UNDER_clr_rx_under_src(data)                                  ((0x00000001&(data))>>0)
#define MIS_IC3_CLR_RX_UNDER_get_clr_rx_under(data)                                  ((0x00000001&(data))>>0)


#define MIS_IC3_CLR_RX_OVER                                                          0x9801B948
#define MIS_IC3_CLR_RX_OVER_reg_addr                                                 "0x9801B948"
#define MIS_IC3_CLR_RX_OVER_reg                                                      0x9801B948
#define set_MIS_IC3_CLR_RX_OVER_reg(data)   (*((volatile unsigned int*) MIS_IC3_CLR_RX_OVER_reg)=data)
#define get_MIS_IC3_CLR_RX_OVER_reg   (*((volatile unsigned int*) MIS_IC3_CLR_RX_OVER_reg))
#define MIS_IC3_CLR_RX_OVER_inst_adr                                                 "0x0052"
#define MIS_IC3_CLR_RX_OVER_inst                                                     0x0052
#define MIS_IC3_CLR_RX_OVER_clr_rx_over_shift                                        (0)
#define MIS_IC3_CLR_RX_OVER_clr_rx_over_mask                                         (0x00000001)
#define MIS_IC3_CLR_RX_OVER_clr_rx_over(data)                                        (0x00000001&((data)<<0))
#define MIS_IC3_CLR_RX_OVER_clr_rx_over_src(data)                                    ((0x00000001&(data))>>0)
#define MIS_IC3_CLR_RX_OVER_get_clr_rx_over(data)                                    ((0x00000001&(data))>>0)


#define MIS_IC3_CLR_TX_OVER                                                          0x9801B94C
#define MIS_IC3_CLR_TX_OVER_reg_addr                                                 "0x9801B94C"
#define MIS_IC3_CLR_TX_OVER_reg                                                      0x9801B94C
#define set_MIS_IC3_CLR_TX_OVER_reg(data)   (*((volatile unsigned int*) MIS_IC3_CLR_TX_OVER_reg)=data)
#define get_MIS_IC3_CLR_TX_OVER_reg   (*((volatile unsigned int*) MIS_IC3_CLR_TX_OVER_reg))
#define MIS_IC3_CLR_TX_OVER_inst_adr                                                 "0x0053"
#define MIS_IC3_CLR_TX_OVER_inst                                                     0x0053
#define MIS_IC3_CLR_TX_OVER_clr_tx_over_shift                                        (0)
#define MIS_IC3_CLR_TX_OVER_clr_tx_over_mask                                         (0x00000001)
#define MIS_IC3_CLR_TX_OVER_clr_tx_over(data)                                        (0x00000001&((data)<<0))
#define MIS_IC3_CLR_TX_OVER_clr_tx_over_src(data)                                    ((0x00000001&(data))>>0)
#define MIS_IC3_CLR_TX_OVER_get_clr_tx_over(data)                                    ((0x00000001&(data))>>0)


#define MIS_IC3_CLR_RD_REQ                                                           0x9801B950
#define MIS_IC3_CLR_RD_REQ_reg_addr                                                  "0x9801B950"
#define MIS_IC3_CLR_RD_REQ_reg                                                       0x9801B950
#define set_MIS_IC3_CLR_RD_REQ_reg(data)   (*((volatile unsigned int*) MIS_IC3_CLR_RD_REQ_reg)=data)
#define get_MIS_IC3_CLR_RD_REQ_reg   (*((volatile unsigned int*) MIS_IC3_CLR_RD_REQ_reg))
#define MIS_IC3_CLR_RD_REQ_inst_adr                                                  "0x0054"
#define MIS_IC3_CLR_RD_REQ_inst                                                      0x0054
#define MIS_IC3_CLR_RD_REQ_clr_rd_req_shift                                          (0)
#define MIS_IC3_CLR_RD_REQ_clr_rd_req_mask                                           (0x00000001)
#define MIS_IC3_CLR_RD_REQ_clr_rd_req(data)                                          (0x00000001&((data)<<0))
#define MIS_IC3_CLR_RD_REQ_clr_rd_req_src(data)                                      ((0x00000001&(data))>>0)
#define MIS_IC3_CLR_RD_REQ_get_clr_rd_req(data)                                      ((0x00000001&(data))>>0)


#define MIS_IC3_CLR_TX_ABRT                                                          0x9801B954
#define MIS_IC3_CLR_TX_ABRT_reg_addr                                                 "0x9801B954"
#define MIS_IC3_CLR_TX_ABRT_reg                                                      0x9801B954
#define set_MIS_IC3_CLR_TX_ABRT_reg(data)   (*((volatile unsigned int*) MIS_IC3_CLR_TX_ABRT_reg)=data)
#define get_MIS_IC3_CLR_TX_ABRT_reg   (*((volatile unsigned int*) MIS_IC3_CLR_TX_ABRT_reg))
#define MIS_IC3_CLR_TX_ABRT_inst_adr                                                 "0x0055"
#define MIS_IC3_CLR_TX_ABRT_inst                                                     0x0055
#define MIS_IC3_CLR_TX_ABRT_clr_tx_abrt_shift                                        (0)
#define MIS_IC3_CLR_TX_ABRT_clr_tx_abrt_mask                                         (0x00000001)
#define MIS_IC3_CLR_TX_ABRT_clr_tx_abrt(data)                                        (0x00000001&((data)<<0))
#define MIS_IC3_CLR_TX_ABRT_clr_tx_abrt_src(data)                                    ((0x00000001&(data))>>0)
#define MIS_IC3_CLR_TX_ABRT_get_clr_tx_abrt(data)                                    ((0x00000001&(data))>>0)


#define MIS_IC3_CLR_RX_DONE                                                          0x9801B958
#define MIS_IC3_CLR_RX_DONE_reg_addr                                                 "0x9801B958"
#define MIS_IC3_CLR_RX_DONE_reg                                                      0x9801B958
#define set_MIS_IC3_CLR_RX_DONE_reg(data)   (*((volatile unsigned int*) MIS_IC3_CLR_RX_DONE_reg)=data)
#define get_MIS_IC3_CLR_RX_DONE_reg   (*((volatile unsigned int*) MIS_IC3_CLR_RX_DONE_reg))
#define MIS_IC3_CLR_RX_DONE_inst_adr                                                 "0x0056"
#define MIS_IC3_CLR_RX_DONE_inst                                                     0x0056
#define MIS_IC3_CLR_RX_DONE_clr_rx_done_shift                                        (0)
#define MIS_IC3_CLR_RX_DONE_clr_rx_done_mask                                         (0x00000001)
#define MIS_IC3_CLR_RX_DONE_clr_rx_done(data)                                        (0x00000001&((data)<<0))
#define MIS_IC3_CLR_RX_DONE_clr_rx_done_src(data)                                    ((0x00000001&(data))>>0)
#define MIS_IC3_CLR_RX_DONE_get_clr_rx_done(data)                                    ((0x00000001&(data))>>0)


#define MIS_IC3_CLR_ACTIVITY                                                         0x9801B95C
#define MIS_IC3_CLR_ACTIVITY_reg_addr                                                "0x9801B95C"
#define MIS_IC3_CLR_ACTIVITY_reg                                                     0x9801B95C
#define set_MIS_IC3_CLR_ACTIVITY_reg(data)   (*((volatile unsigned int*) MIS_IC3_CLR_ACTIVITY_reg)=data)
#define get_MIS_IC3_CLR_ACTIVITY_reg   (*((volatile unsigned int*) MIS_IC3_CLR_ACTIVITY_reg))
#define MIS_IC3_CLR_ACTIVITY_inst_adr                                                "0x0057"
#define MIS_IC3_CLR_ACTIVITY_inst                                                    0x0057
#define MIS_IC3_CLR_ACTIVITY_clr_activity_shift                                      (0)
#define MIS_IC3_CLR_ACTIVITY_clr_activity_mask                                       (0x00000001)
#define MIS_IC3_CLR_ACTIVITY_clr_activity(data)                                      (0x00000001&((data)<<0))
#define MIS_IC3_CLR_ACTIVITY_clr_activity_src(data)                                  ((0x00000001&(data))>>0)
#define MIS_IC3_CLR_ACTIVITY_get_clr_activity(data)                                  ((0x00000001&(data))>>0)


#define MIS_IC3_CLR_STOP_DET                                                         0x9801B960
#define MIS_IC3_CLR_STOP_DET_reg_addr                                                "0x9801B960"
#define MIS_IC3_CLR_STOP_DET_reg                                                     0x9801B960
#define set_MIS_IC3_CLR_STOP_DET_reg(data)   (*((volatile unsigned int*) MIS_IC3_CLR_STOP_DET_reg)=data)
#define get_MIS_IC3_CLR_STOP_DET_reg   (*((volatile unsigned int*) MIS_IC3_CLR_STOP_DET_reg))
#define MIS_IC3_CLR_STOP_DET_inst_adr                                                "0x0058"
#define MIS_IC3_CLR_STOP_DET_inst                                                    0x0058
#define MIS_IC3_CLR_STOP_DET_clr_stop_det_shift                                      (0)
#define MIS_IC3_CLR_STOP_DET_clr_stop_det_mask                                       (0x00000001)
#define MIS_IC3_CLR_STOP_DET_clr_stop_det(data)                                      (0x00000001&((data)<<0))
#define MIS_IC3_CLR_STOP_DET_clr_stop_det_src(data)                                  ((0x00000001&(data))>>0)
#define MIS_IC3_CLR_STOP_DET_get_clr_stop_det(data)                                  ((0x00000001&(data))>>0)


#define MIS_IC3_CLR_START_DET                                                        0x9801B964
#define MIS_IC3_CLR_START_DET_reg_addr                                               "0x9801B964"
#define MIS_IC3_CLR_START_DET_reg                                                    0x9801B964
#define set_MIS_IC3_CLR_START_DET_reg(data)   (*((volatile unsigned int*) MIS_IC3_CLR_START_DET_reg)=data)
#define get_MIS_IC3_CLR_START_DET_reg   (*((volatile unsigned int*) MIS_IC3_CLR_START_DET_reg))
#define MIS_IC3_CLR_START_DET_inst_adr                                               "0x0059"
#define MIS_IC3_CLR_START_DET_inst                                                   0x0059
#define MIS_IC3_CLR_START_DET_clr_start_det_shift                                    (0)
#define MIS_IC3_CLR_START_DET_clr_start_det_mask                                     (0x00000001)
#define MIS_IC3_CLR_START_DET_clr_start_det(data)                                    (0x00000001&((data)<<0))
#define MIS_IC3_CLR_START_DET_clr_start_det_src(data)                                ((0x00000001&(data))>>0)
#define MIS_IC3_CLR_START_DET_get_clr_start_det(data)                                ((0x00000001&(data))>>0)


#define MIS_IC3_CLR_GEN_CALL                                                         0x9801B968
#define MIS_IC3_CLR_GEN_CALL_reg_addr                                                "0x9801B968"
#define MIS_IC3_CLR_GEN_CALL_reg                                                     0x9801B968
#define set_MIS_IC3_CLR_GEN_CALL_reg(data)   (*((volatile unsigned int*) MIS_IC3_CLR_GEN_CALL_reg)=data)
#define get_MIS_IC3_CLR_GEN_CALL_reg   (*((volatile unsigned int*) MIS_IC3_CLR_GEN_CALL_reg))
#define MIS_IC3_CLR_GEN_CALL_inst_adr                                                "0x005A"
#define MIS_IC3_CLR_GEN_CALL_inst                                                    0x005A
#define MIS_IC3_CLR_GEN_CALL_clr_gen_call_shift                                      (0)
#define MIS_IC3_CLR_GEN_CALL_clr_gen_call_mask                                       (0x00000001)
#define MIS_IC3_CLR_GEN_CALL_clr_gen_call(data)                                      (0x00000001&((data)<<0))
#define MIS_IC3_CLR_GEN_CALL_clr_gen_call_src(data)                                  ((0x00000001&(data))>>0)
#define MIS_IC3_CLR_GEN_CALL_get_clr_gen_call(data)                                  ((0x00000001&(data))>>0)


#define MIS_IC3_ENABLE                                                               0x9801B96C
#define MIS_IC3_ENABLE_reg_addr                                                      "0x9801B96C"
#define MIS_IC3_ENABLE_reg                                                           0x9801B96C
#define set_MIS_IC3_ENABLE_reg(data)   (*((volatile unsigned int*) MIS_IC3_ENABLE_reg)=data)
#define get_MIS_IC3_ENABLE_reg   (*((volatile unsigned int*) MIS_IC3_ENABLE_reg))
#define MIS_IC3_ENABLE_inst_adr                                                      "0x005B"
#define MIS_IC3_ENABLE_inst                                                          0x005B
#define MIS_IC3_ENABLE_enable_shift                                                  (0)
#define MIS_IC3_ENABLE_enable_mask                                                   (0x00000001)
#define MIS_IC3_ENABLE_enable(data)                                                  (0x00000001&((data)<<0))
#define MIS_IC3_ENABLE_enable_src(data)                                              ((0x00000001&(data))>>0)
#define MIS_IC3_ENABLE_get_enable(data)                                              ((0x00000001&(data))>>0)


#define MIS_IC3_STATUS                                                               0x9801B970
#define MIS_IC3_STATUS_reg_addr                                                      "0x9801B970"
#define MIS_IC3_STATUS_reg                                                           0x9801B970
#define set_MIS_IC3_STATUS_reg(data)   (*((volatile unsigned int*) MIS_IC3_STATUS_reg)=data)
#define get_MIS_IC3_STATUS_reg   (*((volatile unsigned int*) MIS_IC3_STATUS_reg))
#define MIS_IC3_STATUS_inst_adr                                                      "0x005C"
#define MIS_IC3_STATUS_inst                                                          0x005C
#define MIS_IC3_STATUS_slv_activity_shift                                            (6)
#define MIS_IC3_STATUS_slv_activity_mask                                             (0x00000040)
#define MIS_IC3_STATUS_slv_activity(data)                                            (0x00000040&((data)<<6))
#define MIS_IC3_STATUS_slv_activity_src(data)                                        ((0x00000040&(data))>>6)
#define MIS_IC3_STATUS_get_slv_activity(data)                                        ((0x00000040&(data))>>6)
#define MIS_IC3_STATUS_mst_activity_shift                                            (5)
#define MIS_IC3_STATUS_mst_activity_mask                                             (0x00000020)
#define MIS_IC3_STATUS_mst_activity(data)                                            (0x00000020&((data)<<5))
#define MIS_IC3_STATUS_mst_activity_src(data)                                        ((0x00000020&(data))>>5)
#define MIS_IC3_STATUS_get_mst_activity(data)                                        ((0x00000020&(data))>>5)
#define MIS_IC3_STATUS_rff_shift                                                     (4)
#define MIS_IC3_STATUS_rff_mask                                                      (0x00000010)
#define MIS_IC3_STATUS_rff(data)                                                     (0x00000010&((data)<<4))
#define MIS_IC3_STATUS_rff_src(data)                                                 ((0x00000010&(data))>>4)
#define MIS_IC3_STATUS_get_rff(data)                                                 ((0x00000010&(data))>>4)
#define MIS_IC3_STATUS_rfne_shift                                                    (3)
#define MIS_IC3_STATUS_rfne_mask                                                     (0x00000008)
#define MIS_IC3_STATUS_rfne(data)                                                    (0x00000008&((data)<<3))
#define MIS_IC3_STATUS_rfne_src(data)                                                ((0x00000008&(data))>>3)
#define MIS_IC3_STATUS_get_rfne(data)                                                ((0x00000008&(data))>>3)
#define MIS_IC3_STATUS_tfe_shift                                                     (2)
#define MIS_IC3_STATUS_tfe_mask                                                      (0x00000004)
#define MIS_IC3_STATUS_tfe(data)                                                     (0x00000004&((data)<<2))
#define MIS_IC3_STATUS_tfe_src(data)                                                 ((0x00000004&(data))>>2)
#define MIS_IC3_STATUS_get_tfe(data)                                                 ((0x00000004&(data))>>2)
#define MIS_IC3_STATUS_tfnf_shift                                                    (1)
#define MIS_IC3_STATUS_tfnf_mask                                                     (0x00000002)
#define MIS_IC3_STATUS_tfnf(data)                                                    (0x00000002&((data)<<1))
#define MIS_IC3_STATUS_tfnf_src(data)                                                ((0x00000002&(data))>>1)
#define MIS_IC3_STATUS_get_tfnf(data)                                                ((0x00000002&(data))>>1)
#define MIS_IC3_STATUS_activity_shift                                                (0)
#define MIS_IC3_STATUS_activity_mask                                                 (0x00000001)
#define MIS_IC3_STATUS_activity(data)                                                (0x00000001&((data)<<0))
#define MIS_IC3_STATUS_activity_src(data)                                            ((0x00000001&(data))>>0)
#define MIS_IC3_STATUS_get_activity(data)                                            ((0x00000001&(data))>>0)


#define MIS_IC3_TXFLR                                                                0x9801B974
#define MIS_IC3_TXFLR_reg_addr                                                       "0x9801B974"
#define MIS_IC3_TXFLR_reg                                                            0x9801B974
#define set_MIS_IC3_TXFLR_reg(data)   (*((volatile unsigned int*) MIS_IC3_TXFLR_reg)=data)
#define get_MIS_IC3_TXFLR_reg   (*((volatile unsigned int*) MIS_IC3_TXFLR_reg))
#define MIS_IC3_TXFLR_inst_adr                                                       "0x005D"
#define MIS_IC3_TXFLR_inst                                                           0x005D
#define MIS_IC3_TXFLR_txflr_shift                                                    (0)
#define MIS_IC3_TXFLR_txflr_mask                                                     (0x0000000F)
#define MIS_IC3_TXFLR_txflr(data)                                                    (0x0000000F&((data)<<0))
#define MIS_IC3_TXFLR_txflr_src(data)                                                ((0x0000000F&(data))>>0)
#define MIS_IC3_TXFLR_get_txflr(data)                                                ((0x0000000F&(data))>>0)


#define MIS_IC3_RXFLR                                                                0x9801B978
#define MIS_IC3_RXFLR_reg_addr                                                       "0x9801B978"
#define MIS_IC3_RXFLR_reg                                                            0x9801B978
#define set_MIS_IC3_RXFLR_reg(data)   (*((volatile unsigned int*) MIS_IC3_RXFLR_reg)=data)
#define get_MIS_IC3_RXFLR_reg   (*((volatile unsigned int*) MIS_IC3_RXFLR_reg))
#define MIS_IC3_RXFLR_inst_adr                                                       "0x005E"
#define MIS_IC3_RXFLR_inst                                                           0x005E
#define MIS_IC3_RXFLR_rxflr_shift                                                    (0)
#define MIS_IC3_RXFLR_rxflr_mask                                                     (0x0000000F)
#define MIS_IC3_RXFLR_rxflr(data)                                                    (0x0000000F&((data)<<0))
#define MIS_IC3_RXFLR_rxflr_src(data)                                                ((0x0000000F&(data))>>0)
#define MIS_IC3_RXFLR_get_rxflr(data)                                                ((0x0000000F&(data))>>0)


#define MIS_IC3_SDA_HOLD                                                             0x9801B97C
#define MIS_IC3_SDA_HOLD_reg_addr                                                    "0x9801B97C"
#define MIS_IC3_SDA_HOLD_reg                                                         0x9801B97C
#define set_MIS_IC3_SDA_HOLD_reg(data)   (*((volatile unsigned int*) MIS_IC3_SDA_HOLD_reg)=data)
#define get_MIS_IC3_SDA_HOLD_reg   (*((volatile unsigned int*) MIS_IC3_SDA_HOLD_reg))
#define MIS_IC3_SDA_HOLD_inst_adr                                                    "0x005F"
#define MIS_IC3_SDA_HOLD_inst                                                        0x005F
#define MIS_IC3_SDA_HOLD_sda_hold_shift                                              (0)
#define MIS_IC3_SDA_HOLD_sda_hold_mask                                               (0x0000FFFF)
#define MIS_IC3_SDA_HOLD_sda_hold(data)                                              (0x0000FFFF&((data)<<0))
#define MIS_IC3_SDA_HOLD_sda_hold_src(data)                                          ((0x0000FFFF&(data))>>0)
#define MIS_IC3_SDA_HOLD_get_sda_hold(data)                                          ((0x0000FFFF&(data))>>0)


#define MIS_IC3_TX_ABRT_SOURCE                                                       0x9801B980
#define MIS_IC3_TX_ABRT_SOURCE_reg_addr                                              "0x9801B980"
#define MIS_IC3_TX_ABRT_SOURCE_reg                                                   0x9801B980
#define set_MIS_IC3_TX_ABRT_SOURCE_reg(data)   (*((volatile unsigned int*) MIS_IC3_TX_ABRT_SOURCE_reg)=data)
#define get_MIS_IC3_TX_ABRT_SOURCE_reg   (*((volatile unsigned int*) MIS_IC3_TX_ABRT_SOURCE_reg))
#define MIS_IC3_TX_ABRT_SOURCE_inst_adr                                              "0x0060"
#define MIS_IC3_TX_ABRT_SOURCE_inst                                                  0x0060
#define MIS_IC3_TX_ABRT_SOURCE_abrt_slvrd_intx_shift                                 (15)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_slvrd_intx_mask                                  (0x00008000)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_slvrd_intx(data)                                 (0x00008000&((data)<<15))
#define MIS_IC3_TX_ABRT_SOURCE_abrt_slvrd_intx_src(data)                             ((0x00008000&(data))>>15)
#define MIS_IC3_TX_ABRT_SOURCE_get_abrt_slvrd_intx(data)                             ((0x00008000&(data))>>15)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_slv_arblost_shift                                (14)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_slv_arblost_mask                                 (0x00004000)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_slv_arblost(data)                                (0x00004000&((data)<<14))
#define MIS_IC3_TX_ABRT_SOURCE_abrt_slv_arblost_src(data)                            ((0x00004000&(data))>>14)
#define MIS_IC3_TX_ABRT_SOURCE_get_abrt_slv_arblost(data)                            ((0x00004000&(data))>>14)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_slvflush_txfifo_shift                            (13)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_slvflush_txfifo_mask                             (0x00002000)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_slvflush_txfifo(data)                            (0x00002000&((data)<<13))
#define MIS_IC3_TX_ABRT_SOURCE_abrt_slvflush_txfifo_src(data)                        ((0x00002000&(data))>>13)
#define MIS_IC3_TX_ABRT_SOURCE_get_abrt_slvflush_txfifo(data)                        ((0x00002000&(data))>>13)
#define MIS_IC3_TX_ABRT_SOURCE_arb_lost_shift                                        (12)
#define MIS_IC3_TX_ABRT_SOURCE_arb_lost_mask                                         (0x00001000)
#define MIS_IC3_TX_ABRT_SOURCE_arb_lost(data)                                        (0x00001000&((data)<<12))
#define MIS_IC3_TX_ABRT_SOURCE_arb_lost_src(data)                                    ((0x00001000&(data))>>12)
#define MIS_IC3_TX_ABRT_SOURCE_get_arb_lost(data)                                    ((0x00001000&(data))>>12)
#define MIS_IC3_TX_ABRT_SOURCE_arb_master_dis_shift                                  (11)
#define MIS_IC3_TX_ABRT_SOURCE_arb_master_dis_mask                                   (0x00000800)
#define MIS_IC3_TX_ABRT_SOURCE_arb_master_dis(data)                                  (0x00000800&((data)<<11))
#define MIS_IC3_TX_ABRT_SOURCE_arb_master_dis_src(data)                              ((0x00000800&(data))>>11)
#define MIS_IC3_TX_ABRT_SOURCE_get_arb_master_dis(data)                              ((0x00000800&(data))>>11)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_10b_rd_norstrt_shift                             (10)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_10b_rd_norstrt_mask                              (0x00000400)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_10b_rd_norstrt(data)                             (0x00000400&((data)<<10))
#define MIS_IC3_TX_ABRT_SOURCE_abrt_10b_rd_norstrt_src(data)                         ((0x00000400&(data))>>10)
#define MIS_IC3_TX_ABRT_SOURCE_get_abrt_10b_rd_norstrt(data)                         ((0x00000400&(data))>>10)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_sbyte_norstrt_shift                              (9)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_sbyte_norstrt_mask                               (0x00000200)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_sbyte_norstrt(data)                              (0x00000200&((data)<<9))
#define MIS_IC3_TX_ABRT_SOURCE_abrt_sbyte_norstrt_src(data)                          ((0x00000200&(data))>>9)
#define MIS_IC3_TX_ABRT_SOURCE_get_abrt_sbyte_norstrt(data)                          ((0x00000200&(data))>>9)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_hs_norstrt_shift                                 (8)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_hs_norstrt_mask                                  (0x00000100)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_hs_norstrt(data)                                 (0x00000100&((data)<<8))
#define MIS_IC3_TX_ABRT_SOURCE_abrt_hs_norstrt_src(data)                             ((0x00000100&(data))>>8)
#define MIS_IC3_TX_ABRT_SOURCE_get_abrt_hs_norstrt(data)                             ((0x00000100&(data))>>8)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_sbyte_ackdet_shift                               (7)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_sbyte_ackdet_mask                                (0x00000080)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_sbyte_ackdet(data)                               (0x00000080&((data)<<7))
#define MIS_IC3_TX_ABRT_SOURCE_abrt_sbyte_ackdet_src(data)                           ((0x00000080&(data))>>7)
#define MIS_IC3_TX_ABRT_SOURCE_get_abrt_sbyte_ackdet(data)                           ((0x00000080&(data))>>7)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_hs_ackdet_shift                                  (6)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_hs_ackdet_mask                                   (0x00000040)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_hs_ackdet(data)                                  (0x00000040&((data)<<6))
#define MIS_IC3_TX_ABRT_SOURCE_abrt_hs_ackdet_src(data)                              ((0x00000040&(data))>>6)
#define MIS_IC3_TX_ABRT_SOURCE_get_abrt_hs_ackdet(data)                              ((0x00000040&(data))>>6)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_gcall_read_shift                                 (5)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_gcall_read_mask                                  (0x00000020)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_gcall_read(data)                                 (0x00000020&((data)<<5))
#define MIS_IC3_TX_ABRT_SOURCE_abrt_gcall_read_src(data)                             ((0x00000020&(data))>>5)
#define MIS_IC3_TX_ABRT_SOURCE_get_abrt_gcall_read(data)                             ((0x00000020&(data))>>5)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_gcall_noack_shift                                (4)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_gcall_noack_mask                                 (0x00000010)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_gcall_noack(data)                                (0x00000010&((data)<<4))
#define MIS_IC3_TX_ABRT_SOURCE_abrt_gcall_noack_src(data)                            ((0x00000010&(data))>>4)
#define MIS_IC3_TX_ABRT_SOURCE_get_abrt_gcall_noack(data)                            ((0x00000010&(data))>>4)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_txdata_noack_shift                               (3)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_txdata_noack_mask                                (0x00000008)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_txdata_noack(data)                               (0x00000008&((data)<<3))
#define MIS_IC3_TX_ABRT_SOURCE_abrt_txdata_noack_src(data)                           ((0x00000008&(data))>>3)
#define MIS_IC3_TX_ABRT_SOURCE_get_abrt_txdata_noack(data)                           ((0x00000008&(data))>>3)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_10addr2_noack_shift                              (2)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_10addr2_noack_mask                               (0x00000004)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_10addr2_noack(data)                              (0x00000004&((data)<<2))
#define MIS_IC3_TX_ABRT_SOURCE_abrt_10addr2_noack_src(data)                          ((0x00000004&(data))>>2)
#define MIS_IC3_TX_ABRT_SOURCE_get_abrt_10addr2_noack(data)                          ((0x00000004&(data))>>2)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_10addr1_noack_shift                              (1)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_10addr1_noack_mask                               (0x00000002)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_10addr1_noack(data)                              (0x00000002&((data)<<1))
#define MIS_IC3_TX_ABRT_SOURCE_abrt_10addr1_noack_src(data)                          ((0x00000002&(data))>>1)
#define MIS_IC3_TX_ABRT_SOURCE_get_abrt_10addr1_noack(data)                          ((0x00000002&(data))>>1)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_7b_addr_noack_shift                              (0)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_7b_addr_noack_mask                               (0x00000001)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_7b_addr_noack(data)                              (0x00000001&((data)<<0))
#define MIS_IC3_TX_ABRT_SOURCE_abrt_7b_addr_noack_src(data)                          ((0x00000001&(data))>>0)
#define MIS_IC3_TX_ABRT_SOURCE_get_abrt_7b_addr_noack(data)                          ((0x00000001&(data))>>0)


#define MIS_IC3_SLV_DATA_NACK_ONLY                                                   0x9801B984
#define MIS_IC3_SLV_DATA_NACK_ONLY_reg_addr                                          "0x9801B984"
#define MIS_IC3_SLV_DATA_NACK_ONLY_reg                                               0x9801B984
#define set_MIS_IC3_SLV_DATA_NACK_ONLY_reg(data)   (*((volatile unsigned int*) MIS_IC3_SLV_DATA_NACK_ONLY_reg)=data)
#define get_MIS_IC3_SLV_DATA_NACK_ONLY_reg   (*((volatile unsigned int*) MIS_IC3_SLV_DATA_NACK_ONLY_reg))
#define MIS_IC3_SLV_DATA_NACK_ONLY_inst_adr                                          "0x0061"
#define MIS_IC3_SLV_DATA_NACK_ONLY_inst                                              0x0061
#define MIS_IC3_SLV_DATA_NACK_ONLY_nack_shift                                        (0)
#define MIS_IC3_SLV_DATA_NACK_ONLY_nack_mask                                         (0x00000001)
#define MIS_IC3_SLV_DATA_NACK_ONLY_nack(data)                                        (0x00000001&((data)<<0))
#define MIS_IC3_SLV_DATA_NACK_ONLY_nack_src(data)                                    ((0x00000001&(data))>>0)
#define MIS_IC3_SLV_DATA_NACK_ONLY_get_nack(data)                                    ((0x00000001&(data))>>0)


#define MIS_IC3_DMA_CR                                                               0x9801B988
#define MIS_IC3_DMA_CR_reg_addr                                                      "0x9801B988"
#define MIS_IC3_DMA_CR_reg                                                           0x9801B988
#define set_MIS_IC3_DMA_CR_reg(data)   (*((volatile unsigned int*) MIS_IC3_DMA_CR_reg)=data)
#define get_MIS_IC3_DMA_CR_reg   (*((volatile unsigned int*) MIS_IC3_DMA_CR_reg))
#define MIS_IC3_DMA_CR_inst_adr                                                      "0x0062"
#define MIS_IC3_DMA_CR_inst                                                          0x0062
#define MIS_IC3_DMA_CR_tdmae_shift                                                   (1)
#define MIS_IC3_DMA_CR_tdmae_mask                                                    (0x00000002)
#define MIS_IC3_DMA_CR_tdmae(data)                                                   (0x00000002&((data)<<1))
#define MIS_IC3_DMA_CR_tdmae_src(data)                                               ((0x00000002&(data))>>1)
#define MIS_IC3_DMA_CR_get_tdmae(data)                                               ((0x00000002&(data))>>1)
#define MIS_IC3_DMA_CR_rdmae_shift                                                   (0)
#define MIS_IC3_DMA_CR_rdmae_mask                                                    (0x00000001)
#define MIS_IC3_DMA_CR_rdmae(data)                                                   (0x00000001&((data)<<0))
#define MIS_IC3_DMA_CR_rdmae_src(data)                                               ((0x00000001&(data))>>0)
#define MIS_IC3_DMA_CR_get_rdmae(data)                                               ((0x00000001&(data))>>0)


#define MIS_IC3_DMA_TDLR                                                             0x9801B98C
#define MIS_IC3_DMA_TDLR_reg_addr                                                    "0x9801B98C"
#define MIS_IC3_DMA_TDLR_reg                                                         0x9801B98C
#define set_MIS_IC3_DMA_TDLR_reg(data)   (*((volatile unsigned int*) MIS_IC3_DMA_TDLR_reg)=data)
#define get_MIS_IC3_DMA_TDLR_reg   (*((volatile unsigned int*) MIS_IC3_DMA_TDLR_reg))
#define MIS_IC3_DMA_TDLR_inst_adr                                                    "0x0063"
#define MIS_IC3_DMA_TDLR_inst                                                        0x0063
#define MIS_IC3_DMA_TDLR_dmatdl_shift                                                (0)
#define MIS_IC3_DMA_TDLR_dmatdl_mask                                                 (0x00000007)
#define MIS_IC3_DMA_TDLR_dmatdl(data)                                                (0x00000007&((data)<<0))
#define MIS_IC3_DMA_TDLR_dmatdl_src(data)                                            ((0x00000007&(data))>>0)
#define MIS_IC3_DMA_TDLR_get_dmatdl(data)                                            ((0x00000007&(data))>>0)


#define MIS_IC3_DMA_RDLR                                                             0x9801B990
#define MIS_IC3_DMA_RDLR_reg_addr                                                    "0x9801B990"
#define MIS_IC3_DMA_RDLR_reg                                                         0x9801B990
#define set_MIS_IC3_DMA_RDLR_reg(data)   (*((volatile unsigned int*) MIS_IC3_DMA_RDLR_reg)=data)
#define get_MIS_IC3_DMA_RDLR_reg   (*((volatile unsigned int*) MIS_IC3_DMA_RDLR_reg))
#define MIS_IC3_DMA_RDLR_inst_adr                                                    "0x0064"
#define MIS_IC3_DMA_RDLR_inst                                                        0x0064
#define MIS_IC3_DMA_RDLR_dmardl_shift                                                (0)
#define MIS_IC3_DMA_RDLR_dmardl_mask                                                 (0x0000000F)
#define MIS_IC3_DMA_RDLR_dmardl(data)                                                (0x0000000F&((data)<<0))
#define MIS_IC3_DMA_RDLR_dmardl_src(data)                                            ((0x0000000F&(data))>>0)
#define MIS_IC3_DMA_RDLR_get_dmardl(data)                                            ((0x0000000F&(data))>>0)


#define MIS_IC3_SDA_SETUP                                                            0x9801B994
#define MIS_IC3_SDA_SETUP_reg_addr                                                   "0x9801B994"
#define MIS_IC3_SDA_SETUP_reg                                                        0x9801B994
#define set_MIS_IC3_SDA_SETUP_reg(data)   (*((volatile unsigned int*) MIS_IC3_SDA_SETUP_reg)=data)
#define get_MIS_IC3_SDA_SETUP_reg   (*((volatile unsigned int*) MIS_IC3_SDA_SETUP_reg))
#define MIS_IC3_SDA_SETUP_inst_adr                                                   "0x0065"
#define MIS_IC3_SDA_SETUP_inst                                                       0x0065
#define MIS_IC3_SDA_SETUP_sda_setup_shift                                            (0)
#define MIS_IC3_SDA_SETUP_sda_setup_mask                                             (0x000000FF)
#define MIS_IC3_SDA_SETUP_sda_setup(data)                                            (0x000000FF&((data)<<0))
#define MIS_IC3_SDA_SETUP_sda_setup_src(data)                                        ((0x000000FF&(data))>>0)
#define MIS_IC3_SDA_SETUP_get_sda_setup(data)                                        ((0x000000FF&(data))>>0)


#define MIS_IC3_ACK_GENERAL_CALL                                                     0x9801B998
#define MIS_IC3_ACK_GENERAL_CALL_reg_addr                                            "0x9801B998"
#define MIS_IC3_ACK_GENERAL_CALL_reg                                                 0x9801B998
#define set_MIS_IC3_ACK_GENERAL_CALL_reg(data)   (*((volatile unsigned int*) MIS_IC3_ACK_GENERAL_CALL_reg)=data)
#define get_MIS_IC3_ACK_GENERAL_CALL_reg   (*((volatile unsigned int*) MIS_IC3_ACK_GENERAL_CALL_reg))
#define MIS_IC3_ACK_GENERAL_CALL_inst_adr                                            "0x0066"
#define MIS_IC3_ACK_GENERAL_CALL_inst                                                0x0066
#define MIS_IC3_ACK_GENERAL_CALL_ack_gen_call_shift                                  (0)
#define MIS_IC3_ACK_GENERAL_CALL_ack_gen_call_mask                                   (0x00000001)
#define MIS_IC3_ACK_GENERAL_CALL_ack_gen_call(data)                                  (0x00000001&((data)<<0))
#define MIS_IC3_ACK_GENERAL_CALL_ack_gen_call_src(data)                              ((0x00000001&(data))>>0)
#define MIS_IC3_ACK_GENERAL_CALL_get_ack_gen_call(data)                              ((0x00000001&(data))>>0)


#define MIS_IC3_ENABLE_STATUS                                                        0x9801B99C
#define MIS_IC3_ENABLE_STATUS_reg_addr                                               "0x9801B99C"
#define MIS_IC3_ENABLE_STATUS_reg                                                    0x9801B99C
#define set_MIS_IC3_ENABLE_STATUS_reg(data)   (*((volatile unsigned int*) MIS_IC3_ENABLE_STATUS_reg)=data)
#define get_MIS_IC3_ENABLE_STATUS_reg   (*((volatile unsigned int*) MIS_IC3_ENABLE_STATUS_reg))
#define MIS_IC3_ENABLE_STATUS_inst_adr                                               "0x0067"
#define MIS_IC3_ENABLE_STATUS_inst                                                   0x0067
#define MIS_IC3_ENABLE_STATUS_slv_rx_data_lost_shift                                 (2)
#define MIS_IC3_ENABLE_STATUS_slv_rx_data_lost_mask                                  (0x00000004)
#define MIS_IC3_ENABLE_STATUS_slv_rx_data_lost(data)                                 (0x00000004&((data)<<2))
#define MIS_IC3_ENABLE_STATUS_slv_rx_data_lost_src(data)                             ((0x00000004&(data))>>2)
#define MIS_IC3_ENABLE_STATUS_get_slv_rx_data_lost(data)                             ((0x00000004&(data))>>2)
#define MIS_IC3_ENABLE_STATUS_slv_disabled_whi_shift                                 (1)
#define MIS_IC3_ENABLE_STATUS_slv_disabled_whi_mask                                  (0x00000002)
#define MIS_IC3_ENABLE_STATUS_slv_disabled_whi(data)                                 (0x00000002&((data)<<1))
#define MIS_IC3_ENABLE_STATUS_slv_disabled_whi_src(data)                             ((0x00000002&(data))>>1)
#define MIS_IC3_ENABLE_STATUS_get_slv_disabled_whi(data)                             ((0x00000002&(data))>>1)
#define MIS_IC3_ENABLE_STATUS_ic_en_shift                                            (0)
#define MIS_IC3_ENABLE_STATUS_ic_en_mask                                             (0x00000001)
#define MIS_IC3_ENABLE_STATUS_ic_en(data)                                            (0x00000001&((data)<<0))
#define MIS_IC3_ENABLE_STATUS_ic_en_src(data)                                        ((0x00000001&(data))>>0)
#define MIS_IC3_ENABLE_STATUS_get_ic_en(data)                                        ((0x00000001&(data))>>0)


#define MIS_IC3_COMP_PARAM_1                                                         0x9801B9F4
#define MIS_IC3_COMP_PARAM_1_reg_addr                                                "0x9801B9F4"
#define MIS_IC3_COMP_PARAM_1_reg                                                     0x9801B9F4
#define set_MIS_IC3_COMP_PARAM_1_reg(data)   (*((volatile unsigned int*) MIS_IC3_COMP_PARAM_1_reg)=data)
#define get_MIS_IC3_COMP_PARAM_1_reg   (*((volatile unsigned int*) MIS_IC3_COMP_PARAM_1_reg))
#define MIS_IC3_COMP_PARAM_1_inst_adr                                                "0x007D"
#define MIS_IC3_COMP_PARAM_1_inst                                                    0x007D
#define MIS_IC3_COMP_PARAM_1_tx_buffer_depth_shift                                   (16)
#define MIS_IC3_COMP_PARAM_1_tx_buffer_depth_mask                                    (0x00FF0000)
#define MIS_IC3_COMP_PARAM_1_tx_buffer_depth(data)                                   (0x00FF0000&((data)<<16))
#define MIS_IC3_COMP_PARAM_1_tx_buffer_depth_src(data)                               ((0x00FF0000&(data))>>16)
#define MIS_IC3_COMP_PARAM_1_get_tx_buffer_depth(data)                               ((0x00FF0000&(data))>>16)
#define MIS_IC3_COMP_PARAM_1_rx_buffer_depth_shift                                   (8)
#define MIS_IC3_COMP_PARAM_1_rx_buffer_depth_mask                                    (0x0000FF00)
#define MIS_IC3_COMP_PARAM_1_rx_buffer_depth(data)                                   (0x0000FF00&((data)<<8))
#define MIS_IC3_COMP_PARAM_1_rx_buffer_depth_src(data)                               ((0x0000FF00&(data))>>8)
#define MIS_IC3_COMP_PARAM_1_get_rx_buffer_depth(data)                               ((0x0000FF00&(data))>>8)
#define MIS_IC3_COMP_PARAM_1_add_encoded_params_shift                                (7)
#define MIS_IC3_COMP_PARAM_1_add_encoded_params_mask                                 (0x00000080)
#define MIS_IC3_COMP_PARAM_1_add_encoded_params(data)                                (0x00000080&((data)<<7))
#define MIS_IC3_COMP_PARAM_1_add_encoded_params_src(data)                            ((0x00000080&(data))>>7)
#define MIS_IC3_COMP_PARAM_1_get_add_encoded_params(data)                            ((0x00000080&(data))>>7)
#define MIS_IC3_COMP_PARAM_1_has_dma_shift                                           (6)
#define MIS_IC3_COMP_PARAM_1_has_dma_mask                                            (0x00000040)
#define MIS_IC3_COMP_PARAM_1_has_dma(data)                                           (0x00000040&((data)<<6))
#define MIS_IC3_COMP_PARAM_1_has_dma_src(data)                                       ((0x00000040&(data))>>6)
#define MIS_IC3_COMP_PARAM_1_get_has_dma(data)                                       ((0x00000040&(data))>>6)
#define MIS_IC3_COMP_PARAM_1_intr_io_shift                                           (5)
#define MIS_IC3_COMP_PARAM_1_intr_io_mask                                            (0x00000020)
#define MIS_IC3_COMP_PARAM_1_intr_io(data)                                           (0x00000020&((data)<<5))
#define MIS_IC3_COMP_PARAM_1_intr_io_src(data)                                       ((0x00000020&(data))>>5)
#define MIS_IC3_COMP_PARAM_1_get_intr_io(data)                                       ((0x00000020&(data))>>5)
#define MIS_IC3_COMP_PARAM_1_hc_count_values_shift                                   (4)
#define MIS_IC3_COMP_PARAM_1_hc_count_values_mask                                    (0x00000010)
#define MIS_IC3_COMP_PARAM_1_hc_count_values(data)                                   (0x00000010&((data)<<4))
#define MIS_IC3_COMP_PARAM_1_hc_count_values_src(data)                               ((0x00000010&(data))>>4)
#define MIS_IC3_COMP_PARAM_1_get_hc_count_values(data)                               ((0x00000010&(data))>>4)
#define MIS_IC3_COMP_PARAM_1_max_speed_mode_shift                                    (2)
#define MIS_IC3_COMP_PARAM_1_max_speed_mode_mask                                     (0x0000000C)
#define MIS_IC3_COMP_PARAM_1_max_speed_mode(data)                                    (0x0000000C&((data)<<2))
#define MIS_IC3_COMP_PARAM_1_max_speed_mode_src(data)                                ((0x0000000C&(data))>>2)
#define MIS_IC3_COMP_PARAM_1_get_max_speed_mode(data)                                ((0x0000000C&(data))>>2)
#define MIS_IC3_COMP_PARAM_1_apb_data_width_shift                                    (0)
#define MIS_IC3_COMP_PARAM_1_apb_data_width_mask                                     (0x00000003)
#define MIS_IC3_COMP_PARAM_1_apb_data_width(data)                                    (0x00000003&((data)<<0))
#define MIS_IC3_COMP_PARAM_1_apb_data_width_src(data)                                ((0x00000003&(data))>>0)
#define MIS_IC3_COMP_PARAM_1_get_apb_data_width(data)                                ((0x00000003&(data))>>0)


#define MIS_IC3_COMP_VERSION                                                         0x9801B9F8
#define MIS_IC3_COMP_VERSION_reg_addr                                                "0x9801B9F8"
#define MIS_IC3_COMP_VERSION_reg                                                     0x9801B9F8
#define set_MIS_IC3_COMP_VERSION_reg(data)   (*((volatile unsigned int*) MIS_IC3_COMP_VERSION_reg)=data)
#define get_MIS_IC3_COMP_VERSION_reg   (*((volatile unsigned int*) MIS_IC3_COMP_VERSION_reg))
#define MIS_IC3_COMP_VERSION_inst_adr                                                "0x007E"
#define MIS_IC3_COMP_VERSION_inst                                                    0x007E
#define MIS_IC3_COMP_VERSION_ic_comp_version_shift                                   (0)
#define MIS_IC3_COMP_VERSION_ic_comp_version_mask                                    (0xFFFFFFFF)
#define MIS_IC3_COMP_VERSION_ic_comp_version(data)                                   (0xFFFFFFFF&((data)<<0))
#define MIS_IC3_COMP_VERSION_ic_comp_version_src(data)                               ((0xFFFFFFFF&(data))>>0)
#define MIS_IC3_COMP_VERSION_get_ic_comp_version(data)                               ((0xFFFFFFFF&(data))>>0)


#define MIS_IC3_COMP_TYPE                                                            0x9801B9FC
#define MIS_IC3_COMP_TYPE_reg_addr                                                   "0x9801B9FC"
#define MIS_IC3_COMP_TYPE_reg                                                        0x9801B9FC
#define set_MIS_IC3_COMP_TYPE_reg(data)   (*((volatile unsigned int*) MIS_IC3_COMP_TYPE_reg)=data)
#define get_MIS_IC3_COMP_TYPE_reg   (*((volatile unsigned int*) MIS_IC3_COMP_TYPE_reg))
#define MIS_IC3_COMP_TYPE_inst_adr                                                   "0x007F"
#define MIS_IC3_COMP_TYPE_inst                                                       0x007F
#define MIS_IC3_COMP_TYPE_ic_comp_type_shift                                         (0)
#define MIS_IC3_COMP_TYPE_ic_comp_type_mask                                          (0xFFFFFFFF)
#define MIS_IC3_COMP_TYPE_ic_comp_type(data)                                         (0xFFFFFFFF&((data)<<0))
#define MIS_IC3_COMP_TYPE_ic_comp_type_src(data)                                     ((0xFFFFFFFF&(data))>>0)
#define MIS_IC3_COMP_TYPE_get_ic_comp_type(data)                                     ((0xFFFFFFFF&(data))>>0)


#define MIS_IC4_CON                                                                  0x9801BA00
#define MIS_IC4_CON_reg_addr                                                         "0x9801BA00"
#define MIS_IC4_CON_reg                                                              0x9801BA00
#define set_MIS_IC4_CON_reg(data)   (*((volatile unsigned int*) MIS_IC4_CON_reg)=data)
#define get_MIS_IC4_CON_reg   (*((volatile unsigned int*) MIS_IC4_CON_reg))
#define MIS_IC4_CON_inst_adr                                                         "0x0080"
#define MIS_IC4_CON_inst                                                             0x0080
#define MIS_IC4_CON_ic_slave_disable_shift                                           (6)
#define MIS_IC4_CON_ic_slave_disable_mask                                            (0x00000040)
#define MIS_IC4_CON_ic_slave_disable(data)                                           (0x00000040&((data)<<6))
#define MIS_IC4_CON_ic_slave_disable_src(data)                                       ((0x00000040&(data))>>6)
#define MIS_IC4_CON_get_ic_slave_disable(data)                                       ((0x00000040&(data))>>6)
#define MIS_IC4_CON_ic_restart_en_shift                                              (5)
#define MIS_IC4_CON_ic_restart_en_mask                                               (0x00000020)
#define MIS_IC4_CON_ic_restart_en(data)                                              (0x00000020&((data)<<5))
#define MIS_IC4_CON_ic_restart_en_src(data)                                          ((0x00000020&(data))>>5)
#define MIS_IC4_CON_get_ic_restart_en(data)                                          ((0x00000020&(data))>>5)
#define MIS_IC4_CON_ic_10bitaddr_master_shift                                        (4)
#define MIS_IC4_CON_ic_10bitaddr_master_mask                                         (0x00000010)
#define MIS_IC4_CON_ic_10bitaddr_master(data)                                        (0x00000010&((data)<<4))
#define MIS_IC4_CON_ic_10bitaddr_master_src(data)                                    ((0x00000010&(data))>>4)
#define MIS_IC4_CON_get_ic_10bitaddr_master(data)                                    ((0x00000010&(data))>>4)
#define MIS_IC4_CON_ic_10bitaddr_slave_shift                                         (3)
#define MIS_IC4_CON_ic_10bitaddr_slave_mask                                          (0x00000008)
#define MIS_IC4_CON_ic_10bitaddr_slave(data)                                         (0x00000008&((data)<<3))
#define MIS_IC4_CON_ic_10bitaddr_slave_src(data)                                     ((0x00000008&(data))>>3)
#define MIS_IC4_CON_get_ic_10bitaddr_slave(data)                                     ((0x00000008&(data))>>3)
#define MIS_IC4_CON_speed_shift                                                      (1)
#define MIS_IC4_CON_speed_mask                                                       (0x00000006)
#define MIS_IC4_CON_speed(data)                                                      (0x00000006&((data)<<1))
#define MIS_IC4_CON_speed_src(data)                                                  ((0x00000006&(data))>>1)
#define MIS_IC4_CON_get_speed(data)                                                  ((0x00000006&(data))>>1)
#define MIS_IC4_CON_master_mode_shift                                                (0)
#define MIS_IC4_CON_master_mode_mask                                                 (0x00000001)
#define MIS_IC4_CON_master_mode(data)                                                (0x00000001&((data)<<0))
#define MIS_IC4_CON_master_mode_src(data)                                            ((0x00000001&(data))>>0)
#define MIS_IC4_CON_get_master_mode(data)                                            ((0x00000001&(data))>>0)


#define MIS_IC4_TAR                                                                  0x9801BA04
#define MIS_IC4_TAR_reg_addr                                                         "0x9801BA04"
#define MIS_IC4_TAR_reg                                                              0x9801BA04
#define set_MIS_IC4_TAR_reg(data)   (*((volatile unsigned int*) MIS_IC4_TAR_reg)=data)
#define get_MIS_IC4_TAR_reg   (*((volatile unsigned int*) MIS_IC4_TAR_reg))
#define MIS_IC4_TAR_inst_adr                                                         "0x0081"
#define MIS_IC4_TAR_inst                                                             0x0081
#define MIS_IC4_TAR_ic_10bitaddr_master_shift                                        (12)
#define MIS_IC4_TAR_ic_10bitaddr_master_mask                                         (0x00001000)
#define MIS_IC4_TAR_ic_10bitaddr_master(data)                                        (0x00001000&((data)<<12))
#define MIS_IC4_TAR_ic_10bitaddr_master_src(data)                                    ((0x00001000&(data))>>12)
#define MIS_IC4_TAR_get_ic_10bitaddr_master(data)                                    ((0x00001000&(data))>>12)
#define MIS_IC4_TAR_special_shift                                                    (11)
#define MIS_IC4_TAR_special_mask                                                     (0x00000800)
#define MIS_IC4_TAR_special(data)                                                    (0x00000800&((data)<<11))
#define MIS_IC4_TAR_special_src(data)                                                ((0x00000800&(data))>>11)
#define MIS_IC4_TAR_get_special(data)                                                ((0x00000800&(data))>>11)
#define MIS_IC4_TAR_gc_or_start_shift                                                (10)
#define MIS_IC4_TAR_gc_or_start_mask                                                 (0x00000400)
#define MIS_IC4_TAR_gc_or_start(data)                                                (0x00000400&((data)<<10))
#define MIS_IC4_TAR_gc_or_start_src(data)                                            ((0x00000400&(data))>>10)
#define MIS_IC4_TAR_get_gc_or_start(data)                                            ((0x00000400&(data))>>10)
#define MIS_IC4_TAR_ic_tar_shift                                                     (0)
#define MIS_IC4_TAR_ic_tar_mask                                                      (0x000003FF)
#define MIS_IC4_TAR_ic_tar(data)                                                     (0x000003FF&((data)<<0))
#define MIS_IC4_TAR_ic_tar_src(data)                                                 ((0x000003FF&(data))>>0)
#define MIS_IC4_TAR_get_ic_tar(data)                                                 ((0x000003FF&(data))>>0)


#define MIS_IC4_SAR                                                                  0x9801BA08
#define MIS_IC4_SAR_reg_addr                                                         "0x9801BA08"
#define MIS_IC4_SAR_reg                                                              0x9801BA08
#define set_MIS_IC4_SAR_reg(data)   (*((volatile unsigned int*) MIS_IC4_SAR_reg)=data)
#define get_MIS_IC4_SAR_reg   (*((volatile unsigned int*) MIS_IC4_SAR_reg))
#define MIS_IC4_SAR_inst_adr                                                         "0x0082"
#define MIS_IC4_SAR_inst                                                             0x0082
#define MIS_IC4_SAR_ic_sar_shift                                                     (0)
#define MIS_IC4_SAR_ic_sar_mask                                                      (0x000003FF)
#define MIS_IC4_SAR_ic_sar(data)                                                     (0x000003FF&((data)<<0))
#define MIS_IC4_SAR_ic_sar_src(data)                                                 ((0x000003FF&(data))>>0)
#define MIS_IC4_SAR_get_ic_sar(data)                                                 ((0x000003FF&(data))>>0)


#define MIS_IC4_HS_MADDR                                                             0x9801BA0C
#define MIS_IC4_HS_MADDR_reg_addr                                                    "0x9801BA0C"
#define MIS_IC4_HS_MADDR_reg                                                         0x9801BA0C
#define set_MIS_IC4_HS_MADDR_reg(data)   (*((volatile unsigned int*) MIS_IC4_HS_MADDR_reg)=data)
#define get_MIS_IC4_HS_MADDR_reg   (*((volatile unsigned int*) MIS_IC4_HS_MADDR_reg))
#define MIS_IC4_HS_MADDR_inst_adr                                                    "0x0083"
#define MIS_IC4_HS_MADDR_inst                                                        0x0083
#define MIS_IC4_HS_MADDR_ic_hs_mar_shift                                             (0)
#define MIS_IC4_HS_MADDR_ic_hs_mar_mask                                              (0x00000007)
#define MIS_IC4_HS_MADDR_ic_hs_mar(data)                                             (0x00000007&((data)<<0))
#define MIS_IC4_HS_MADDR_ic_hs_mar_src(data)                                         ((0x00000007&(data))>>0)
#define MIS_IC4_HS_MADDR_get_ic_hs_mar(data)                                         ((0x00000007&(data))>>0)


#define MIS_IC4_DATA_CMD                                                             0x9801BA10
#define MIS_IC4_DATA_CMD_reg_addr                                                    "0x9801BA10"
#define MIS_IC4_DATA_CMD_reg                                                         0x9801BA10
#define set_MIS_IC4_DATA_CMD_reg(data)   (*((volatile unsigned int*) MIS_IC4_DATA_CMD_reg)=data)
#define get_MIS_IC4_DATA_CMD_reg   (*((volatile unsigned int*) MIS_IC4_DATA_CMD_reg))
#define MIS_IC4_DATA_CMD_inst_adr                                                    "0x0084"
#define MIS_IC4_DATA_CMD_inst                                                        0x0084
#define MIS_IC4_DATA_CMD_restart_shift                                               (10)
#define MIS_IC4_DATA_CMD_restart_mask                                                (0x00000400)
#define MIS_IC4_DATA_CMD_restart(data)                                               (0x00000400&((data)<<10))
#define MIS_IC4_DATA_CMD_restart_src(data)                                           ((0x00000400&(data))>>10)
#define MIS_IC4_DATA_CMD_get_restart(data)                                           ((0x00000400&(data))>>10)
#define MIS_IC4_DATA_CMD_stop_shift                                                  (9)
#define MIS_IC4_DATA_CMD_stop_mask                                                   (0x00000200)
#define MIS_IC4_DATA_CMD_stop(data)                                                  (0x00000200&((data)<<9))
#define MIS_IC4_DATA_CMD_stop_src(data)                                              ((0x00000200&(data))>>9)
#define MIS_IC4_DATA_CMD_get_stop(data)                                              ((0x00000200&(data))>>9)
#define MIS_IC4_DATA_CMD_cmd_shift                                                   (8)
#define MIS_IC4_DATA_CMD_cmd_mask                                                    (0x00000100)
#define MIS_IC4_DATA_CMD_cmd(data)                                                   (0x00000100&((data)<<8))
#define MIS_IC4_DATA_CMD_cmd_src(data)                                               ((0x00000100&(data))>>8)
#define MIS_IC4_DATA_CMD_get_cmd(data)                                               ((0x00000100&(data))>>8)
#define MIS_IC4_DATA_CMD_dat_shift                                                   (0)
#define MIS_IC4_DATA_CMD_dat_mask                                                    (0x000000FF)
#define MIS_IC4_DATA_CMD_dat(data)                                                   (0x000000FF&((data)<<0))
#define MIS_IC4_DATA_CMD_dat_src(data)                                               ((0x000000FF&(data))>>0)
#define MIS_IC4_DATA_CMD_get_dat(data)                                               ((0x000000FF&(data))>>0)


#define MIS_IC4_SS_SCL_HCNT                                                          0x9801BA14
#define MIS_IC4_SS_SCL_HCNT_reg_addr                                                 "0x9801BA14"
#define MIS_IC4_SS_SCL_HCNT_reg                                                      0x9801BA14
#define set_MIS_IC4_SS_SCL_HCNT_reg(data)   (*((volatile unsigned int*) MIS_IC4_SS_SCL_HCNT_reg)=data)
#define get_MIS_IC4_SS_SCL_HCNT_reg   (*((volatile unsigned int*) MIS_IC4_SS_SCL_HCNT_reg))
#define MIS_IC4_SS_SCL_HCNT_inst_adr                                                 "0x0085"
#define MIS_IC4_SS_SCL_HCNT_inst                                                     0x0085
#define MIS_IC4_SS_SCL_HCNT_ic_ss_scl_hcnt_shift                                     (0)
#define MIS_IC4_SS_SCL_HCNT_ic_ss_scl_hcnt_mask                                      (0x0000FFFF)
#define MIS_IC4_SS_SCL_HCNT_ic_ss_scl_hcnt(data)                                     (0x0000FFFF&((data)<<0))
#define MIS_IC4_SS_SCL_HCNT_ic_ss_scl_hcnt_src(data)                                 ((0x0000FFFF&(data))>>0)
#define MIS_IC4_SS_SCL_HCNT_get_ic_ss_scl_hcnt(data)                                 ((0x0000FFFF&(data))>>0)


#define MIS_IC4_SS_SCL_LCNT                                                          0x9801BA18
#define MIS_IC4_SS_SCL_LCNT_reg_addr                                                 "0x9801BA18"
#define MIS_IC4_SS_SCL_LCNT_reg                                                      0x9801BA18
#define set_MIS_IC4_SS_SCL_LCNT_reg(data)   (*((volatile unsigned int*) MIS_IC4_SS_SCL_LCNT_reg)=data)
#define get_MIS_IC4_SS_SCL_LCNT_reg   (*((volatile unsigned int*) MIS_IC4_SS_SCL_LCNT_reg))
#define MIS_IC4_SS_SCL_LCNT_inst_adr                                                 "0x0086"
#define MIS_IC4_SS_SCL_LCNT_inst                                                     0x0086
#define MIS_IC4_SS_SCL_LCNT_ic_ss_scl_lcnt_shift                                     (0)
#define MIS_IC4_SS_SCL_LCNT_ic_ss_scl_lcnt_mask                                      (0x0000FFFF)
#define MIS_IC4_SS_SCL_LCNT_ic_ss_scl_lcnt(data)                                     (0x0000FFFF&((data)<<0))
#define MIS_IC4_SS_SCL_LCNT_ic_ss_scl_lcnt_src(data)                                 ((0x0000FFFF&(data))>>0)
#define MIS_IC4_SS_SCL_LCNT_get_ic_ss_scl_lcnt(data)                                 ((0x0000FFFF&(data))>>0)


#define MIS_IC4_FS_SCL_HCNT                                                          0x9801BA1C
#define MIS_IC4_FS_SCL_HCNT_reg_addr                                                 "0x9801BA1C"
#define MIS_IC4_FS_SCL_HCNT_reg                                                      0x9801BA1C
#define set_MIS_IC4_FS_SCL_HCNT_reg(data)   (*((volatile unsigned int*) MIS_IC4_FS_SCL_HCNT_reg)=data)
#define get_MIS_IC4_FS_SCL_HCNT_reg   (*((volatile unsigned int*) MIS_IC4_FS_SCL_HCNT_reg))
#define MIS_IC4_FS_SCL_HCNT_inst_adr                                                 "0x0087"
#define MIS_IC4_FS_SCL_HCNT_inst                                                     0x0087
#define MIS_IC4_FS_SCL_HCNT_ic_fs_scl_hcnt_shift                                     (0)
#define MIS_IC4_FS_SCL_HCNT_ic_fs_scl_hcnt_mask                                      (0x0000FFFF)
#define MIS_IC4_FS_SCL_HCNT_ic_fs_scl_hcnt(data)                                     (0x0000FFFF&((data)<<0))
#define MIS_IC4_FS_SCL_HCNT_ic_fs_scl_hcnt_src(data)                                 ((0x0000FFFF&(data))>>0)
#define MIS_IC4_FS_SCL_HCNT_get_ic_fs_scl_hcnt(data)                                 ((0x0000FFFF&(data))>>0)


#define MIS_IC4_FS_SCL_LCNT                                                          0x9801BA20
#define MIS_IC4_FS_SCL_LCNT_reg_addr                                                 "0x9801BA20"
#define MIS_IC4_FS_SCL_LCNT_reg                                                      0x9801BA20
#define set_MIS_IC4_FS_SCL_LCNT_reg(data)   (*((volatile unsigned int*) MIS_IC4_FS_SCL_LCNT_reg)=data)
#define get_MIS_IC4_FS_SCL_LCNT_reg   (*((volatile unsigned int*) MIS_IC4_FS_SCL_LCNT_reg))
#define MIS_IC4_FS_SCL_LCNT_inst_adr                                                 "0x0088"
#define MIS_IC4_FS_SCL_LCNT_inst                                                     0x0088
#define MIS_IC4_FS_SCL_LCNT_ic_fs_scl_lcnt_shift                                     (0)
#define MIS_IC4_FS_SCL_LCNT_ic_fs_scl_lcnt_mask                                      (0x0000FFFF)
#define MIS_IC4_FS_SCL_LCNT_ic_fs_scl_lcnt(data)                                     (0x0000FFFF&((data)<<0))
#define MIS_IC4_FS_SCL_LCNT_ic_fs_scl_lcnt_src(data)                                 ((0x0000FFFF&(data))>>0)
#define MIS_IC4_FS_SCL_LCNT_get_ic_fs_scl_lcnt(data)                                 ((0x0000FFFF&(data))>>0)


#define MIS_IC4_INTR_STAT                                                            0x9801BA2C
#define MIS_IC4_INTR_STAT_reg_addr                                                   "0x9801BA2C"
#define MIS_IC4_INTR_STAT_reg                                                        0x9801BA2C
#define set_MIS_IC4_INTR_STAT_reg(data)   (*((volatile unsigned int*) MIS_IC4_INTR_STAT_reg)=data)
#define get_MIS_IC4_INTR_STAT_reg   (*((volatile unsigned int*) MIS_IC4_INTR_STAT_reg))
#define MIS_IC4_INTR_STAT_inst_adr                                                   "0x008B"
#define MIS_IC4_INTR_STAT_inst                                                       0x008B
#define MIS_IC4_INTR_STAT_r_gen_call_shift                                           (11)
#define MIS_IC4_INTR_STAT_r_gen_call_mask                                            (0x00000800)
#define MIS_IC4_INTR_STAT_r_gen_call(data)                                           (0x00000800&((data)<<11))
#define MIS_IC4_INTR_STAT_r_gen_call_src(data)                                       ((0x00000800&(data))>>11)
#define MIS_IC4_INTR_STAT_get_r_gen_call(data)                                       ((0x00000800&(data))>>11)
#define MIS_IC4_INTR_STAT_r_start_det_shift                                          (10)
#define MIS_IC4_INTR_STAT_r_start_det_mask                                           (0x00000400)
#define MIS_IC4_INTR_STAT_r_start_det(data)                                          (0x00000400&((data)<<10))
#define MIS_IC4_INTR_STAT_r_start_det_src(data)                                      ((0x00000400&(data))>>10)
#define MIS_IC4_INTR_STAT_get_r_start_det(data)                                      ((0x00000400&(data))>>10)
#define MIS_IC4_INTR_STAT_r_stop_det_shift                                           (9)
#define MIS_IC4_INTR_STAT_r_stop_det_mask                                            (0x00000200)
#define MIS_IC4_INTR_STAT_r_stop_det(data)                                           (0x00000200&((data)<<9))
#define MIS_IC4_INTR_STAT_r_stop_det_src(data)                                       ((0x00000200&(data))>>9)
#define MIS_IC4_INTR_STAT_get_r_stop_det(data)                                       ((0x00000200&(data))>>9)
#define MIS_IC4_INTR_STAT_r_activity_shift                                           (8)
#define MIS_IC4_INTR_STAT_r_activity_mask                                            (0x00000100)
#define MIS_IC4_INTR_STAT_r_activity(data)                                           (0x00000100&((data)<<8))
#define MIS_IC4_INTR_STAT_r_activity_src(data)                                       ((0x00000100&(data))>>8)
#define MIS_IC4_INTR_STAT_get_r_activity(data)                                       ((0x00000100&(data))>>8)
#define MIS_IC4_INTR_STAT_r_rx_done_shift                                            (7)
#define MIS_IC4_INTR_STAT_r_rx_done_mask                                             (0x00000080)
#define MIS_IC4_INTR_STAT_r_rx_done(data)                                            (0x00000080&((data)<<7))
#define MIS_IC4_INTR_STAT_r_rx_done_src(data)                                        ((0x00000080&(data))>>7)
#define MIS_IC4_INTR_STAT_get_r_rx_done(data)                                        ((0x00000080&(data))>>7)
#define MIS_IC4_INTR_STAT_r_tx_abrt_shift                                            (6)
#define MIS_IC4_INTR_STAT_r_tx_abrt_mask                                             (0x00000040)
#define MIS_IC4_INTR_STAT_r_tx_abrt(data)                                            (0x00000040&((data)<<6))
#define MIS_IC4_INTR_STAT_r_tx_abrt_src(data)                                        ((0x00000040&(data))>>6)
#define MIS_IC4_INTR_STAT_get_r_tx_abrt(data)                                        ((0x00000040&(data))>>6)
#define MIS_IC4_INTR_STAT_r_rd_req_shift                                             (5)
#define MIS_IC4_INTR_STAT_r_rd_req_mask                                              (0x00000020)
#define MIS_IC4_INTR_STAT_r_rd_req(data)                                             (0x00000020&((data)<<5))
#define MIS_IC4_INTR_STAT_r_rd_req_src(data)                                         ((0x00000020&(data))>>5)
#define MIS_IC4_INTR_STAT_get_r_rd_req(data)                                         ((0x00000020&(data))>>5)
#define MIS_IC4_INTR_STAT_r_tx_empty_shift                                           (4)
#define MIS_IC4_INTR_STAT_r_tx_empty_mask                                            (0x00000010)
#define MIS_IC4_INTR_STAT_r_tx_empty(data)                                           (0x00000010&((data)<<4))
#define MIS_IC4_INTR_STAT_r_tx_empty_src(data)                                       ((0x00000010&(data))>>4)
#define MIS_IC4_INTR_STAT_get_r_tx_empty(data)                                       ((0x00000010&(data))>>4)
#define MIS_IC4_INTR_STAT_r_tx_over_shift                                            (3)
#define MIS_IC4_INTR_STAT_r_tx_over_mask                                             (0x00000008)
#define MIS_IC4_INTR_STAT_r_tx_over(data)                                            (0x00000008&((data)<<3))
#define MIS_IC4_INTR_STAT_r_tx_over_src(data)                                        ((0x00000008&(data))>>3)
#define MIS_IC4_INTR_STAT_get_r_tx_over(data)                                        ((0x00000008&(data))>>3)
#define MIS_IC4_INTR_STAT_r_rx_full_shift                                            (2)
#define MIS_IC4_INTR_STAT_r_rx_full_mask                                             (0x00000004)
#define MIS_IC4_INTR_STAT_r_rx_full(data)                                            (0x00000004&((data)<<2))
#define MIS_IC4_INTR_STAT_r_rx_full_src(data)                                        ((0x00000004&(data))>>2)
#define MIS_IC4_INTR_STAT_get_r_rx_full(data)                                        ((0x00000004&(data))>>2)
#define MIS_IC4_INTR_STAT_r_rx_over_shift                                            (1)
#define MIS_IC4_INTR_STAT_r_rx_over_mask                                             (0x00000002)
#define MIS_IC4_INTR_STAT_r_rx_over(data)                                            (0x00000002&((data)<<1))
#define MIS_IC4_INTR_STAT_r_rx_over_src(data)                                        ((0x00000002&(data))>>1)
#define MIS_IC4_INTR_STAT_get_r_rx_over(data)                                        ((0x00000002&(data))>>1)
#define MIS_IC4_INTR_STAT_r_rx_under_shift                                           (0)
#define MIS_IC4_INTR_STAT_r_rx_under_mask                                            (0x00000001)
#define MIS_IC4_INTR_STAT_r_rx_under(data)                                           (0x00000001&((data)<<0))
#define MIS_IC4_INTR_STAT_r_rx_under_src(data)                                       ((0x00000001&(data))>>0)
#define MIS_IC4_INTR_STAT_get_r_rx_under(data)                                       ((0x00000001&(data))>>0)


#define MIS_IC4_INTR_MASK                                                            0x9801BA30
#define MIS_IC4_INTR_MASK_reg_addr                                                   "0x9801BA30"
#define MIS_IC4_INTR_MASK_reg                                                        0x9801BA30
#define set_MIS_IC4_INTR_MASK_reg(data)   (*((volatile unsigned int*) MIS_IC4_INTR_MASK_reg)=data)
#define get_MIS_IC4_INTR_MASK_reg   (*((volatile unsigned int*) MIS_IC4_INTR_MASK_reg))
#define MIS_IC4_INTR_MASK_inst_adr                                                   "0x008C"
#define MIS_IC4_INTR_MASK_inst                                                       0x008C
#define MIS_IC4_INTR_MASK_m_gen_call_shift                                           (11)
#define MIS_IC4_INTR_MASK_m_gen_call_mask                                            (0x00000800)
#define MIS_IC4_INTR_MASK_m_gen_call(data)                                           (0x00000800&((data)<<11))
#define MIS_IC4_INTR_MASK_m_gen_call_src(data)                                       ((0x00000800&(data))>>11)
#define MIS_IC4_INTR_MASK_get_m_gen_call(data)                                       ((0x00000800&(data))>>11)
#define MIS_IC4_INTR_MASK_m_start_det_shift                                          (10)
#define MIS_IC4_INTR_MASK_m_start_det_mask                                           (0x00000400)
#define MIS_IC4_INTR_MASK_m_start_det(data)                                          (0x00000400&((data)<<10))
#define MIS_IC4_INTR_MASK_m_start_det_src(data)                                      ((0x00000400&(data))>>10)
#define MIS_IC4_INTR_MASK_get_m_start_det(data)                                      ((0x00000400&(data))>>10)
#define MIS_IC4_INTR_MASK_m_stop_det_shift                                           (9)
#define MIS_IC4_INTR_MASK_m_stop_det_mask                                            (0x00000200)
#define MIS_IC4_INTR_MASK_m_stop_det(data)                                           (0x00000200&((data)<<9))
#define MIS_IC4_INTR_MASK_m_stop_det_src(data)                                       ((0x00000200&(data))>>9)
#define MIS_IC4_INTR_MASK_get_m_stop_det(data)                                       ((0x00000200&(data))>>9)
#define MIS_IC4_INTR_MASK_m_activity_shift                                           (8)
#define MIS_IC4_INTR_MASK_m_activity_mask                                            (0x00000100)
#define MIS_IC4_INTR_MASK_m_activity(data)                                           (0x00000100&((data)<<8))
#define MIS_IC4_INTR_MASK_m_activity_src(data)                                       ((0x00000100&(data))>>8)
#define MIS_IC4_INTR_MASK_get_m_activity(data)                                       ((0x00000100&(data))>>8)
#define MIS_IC4_INTR_MASK_m_rx_done_shift                                            (7)
#define MIS_IC4_INTR_MASK_m_rx_done_mask                                             (0x00000080)
#define MIS_IC4_INTR_MASK_m_rx_done(data)                                            (0x00000080&((data)<<7))
#define MIS_IC4_INTR_MASK_m_rx_done_src(data)                                        ((0x00000080&(data))>>7)
#define MIS_IC4_INTR_MASK_get_m_rx_done(data)                                        ((0x00000080&(data))>>7)
#define MIS_IC4_INTR_MASK_m_tx_abrt_shift                                            (6)
#define MIS_IC4_INTR_MASK_m_tx_abrt_mask                                             (0x00000040)
#define MIS_IC4_INTR_MASK_m_tx_abrt(data)                                            (0x00000040&((data)<<6))
#define MIS_IC4_INTR_MASK_m_tx_abrt_src(data)                                        ((0x00000040&(data))>>6)
#define MIS_IC4_INTR_MASK_get_m_tx_abrt(data)                                        ((0x00000040&(data))>>6)
#define MIS_IC4_INTR_MASK_m_rd_req_shift                                             (5)
#define MIS_IC4_INTR_MASK_m_rd_req_mask                                              (0x00000020)
#define MIS_IC4_INTR_MASK_m_rd_req(data)                                             (0x00000020&((data)<<5))
#define MIS_IC4_INTR_MASK_m_rd_req_src(data)                                         ((0x00000020&(data))>>5)
#define MIS_IC4_INTR_MASK_get_m_rd_req(data)                                         ((0x00000020&(data))>>5)
#define MIS_IC4_INTR_MASK_m_tx_empty_shift                                           (4)
#define MIS_IC4_INTR_MASK_m_tx_empty_mask                                            (0x00000010)
#define MIS_IC4_INTR_MASK_m_tx_empty(data)                                           (0x00000010&((data)<<4))
#define MIS_IC4_INTR_MASK_m_tx_empty_src(data)                                       ((0x00000010&(data))>>4)
#define MIS_IC4_INTR_MASK_get_m_tx_empty(data)                                       ((0x00000010&(data))>>4)
#define MIS_IC4_INTR_MASK_m_tx_over_shift                                            (3)
#define MIS_IC4_INTR_MASK_m_tx_over_mask                                             (0x00000008)
#define MIS_IC4_INTR_MASK_m_tx_over(data)                                            (0x00000008&((data)<<3))
#define MIS_IC4_INTR_MASK_m_tx_over_src(data)                                        ((0x00000008&(data))>>3)
#define MIS_IC4_INTR_MASK_get_m_tx_over(data)                                        ((0x00000008&(data))>>3)
#define MIS_IC4_INTR_MASK_m_rx_full_shift                                            (2)
#define MIS_IC4_INTR_MASK_m_rx_full_mask                                             (0x00000004)
#define MIS_IC4_INTR_MASK_m_rx_full(data)                                            (0x00000004&((data)<<2))
#define MIS_IC4_INTR_MASK_m_rx_full_src(data)                                        ((0x00000004&(data))>>2)
#define MIS_IC4_INTR_MASK_get_m_rx_full(data)                                        ((0x00000004&(data))>>2)
#define MIS_IC4_INTR_MASK_m_rx_over_shift                                            (1)
#define MIS_IC4_INTR_MASK_m_rx_over_mask                                             (0x00000002)
#define MIS_IC4_INTR_MASK_m_rx_over(data)                                            (0x00000002&((data)<<1))
#define MIS_IC4_INTR_MASK_m_rx_over_src(data)                                        ((0x00000002&(data))>>1)
#define MIS_IC4_INTR_MASK_get_m_rx_over(data)                                        ((0x00000002&(data))>>1)
#define MIS_IC4_INTR_MASK_m_rx_under_shift                                           (0)
#define MIS_IC4_INTR_MASK_m_rx_under_mask                                            (0x00000001)
#define MIS_IC4_INTR_MASK_m_rx_under(data)                                           (0x00000001&((data)<<0))
#define MIS_IC4_INTR_MASK_m_rx_under_src(data)                                       ((0x00000001&(data))>>0)
#define MIS_IC4_INTR_MASK_get_m_rx_under(data)                                       ((0x00000001&(data))>>0)


#define MIS_IC4_RAW_INTR_STAT                                                        0x9801BA34
#define MIS_IC4_RAW_INTR_STAT_reg_addr                                               "0x9801BA34"
#define MIS_IC4_RAW_INTR_STAT_reg                                                    0x9801BA34
#define set_MIS_IC4_RAW_INTR_STAT_reg(data)   (*((volatile unsigned int*) MIS_IC4_RAW_INTR_STAT_reg)=data)
#define get_MIS_IC4_RAW_INTR_STAT_reg   (*((volatile unsigned int*) MIS_IC4_RAW_INTR_STAT_reg))
#define MIS_IC4_RAW_INTR_STAT_inst_adr                                               "0x008D"
#define MIS_IC4_RAW_INTR_STAT_inst                                                   0x008D
#define MIS_IC4_RAW_INTR_STAT_gen_call_shift                                         (11)
#define MIS_IC4_RAW_INTR_STAT_gen_call_mask                                          (0x00000800)
#define MIS_IC4_RAW_INTR_STAT_gen_call(data)                                         (0x00000800&((data)<<11))
#define MIS_IC4_RAW_INTR_STAT_gen_call_src(data)                                     ((0x00000800&(data))>>11)
#define MIS_IC4_RAW_INTR_STAT_get_gen_call(data)                                     ((0x00000800&(data))>>11)
#define MIS_IC4_RAW_INTR_STAT_start_det_shift                                        (10)
#define MIS_IC4_RAW_INTR_STAT_start_det_mask                                         (0x00000400)
#define MIS_IC4_RAW_INTR_STAT_start_det(data)                                        (0x00000400&((data)<<10))
#define MIS_IC4_RAW_INTR_STAT_start_det_src(data)                                    ((0x00000400&(data))>>10)
#define MIS_IC4_RAW_INTR_STAT_get_start_det(data)                                    ((0x00000400&(data))>>10)
#define MIS_IC4_RAW_INTR_STAT_stop_det_shift                                         (9)
#define MIS_IC4_RAW_INTR_STAT_stop_det_mask                                          (0x00000200)
#define MIS_IC4_RAW_INTR_STAT_stop_det(data)                                         (0x00000200&((data)<<9))
#define MIS_IC4_RAW_INTR_STAT_stop_det_src(data)                                     ((0x00000200&(data))>>9)
#define MIS_IC4_RAW_INTR_STAT_get_stop_det(data)                                     ((0x00000200&(data))>>9)
#define MIS_IC4_RAW_INTR_STAT_activity_shift                                         (8)
#define MIS_IC4_RAW_INTR_STAT_activity_mask                                          (0x00000100)
#define MIS_IC4_RAW_INTR_STAT_activity(data)                                         (0x00000100&((data)<<8))
#define MIS_IC4_RAW_INTR_STAT_activity_src(data)                                     ((0x00000100&(data))>>8)
#define MIS_IC4_RAW_INTR_STAT_get_activity(data)                                     ((0x00000100&(data))>>8)
#define MIS_IC4_RAW_INTR_STAT_rx_done_shift                                          (7)
#define MIS_IC4_RAW_INTR_STAT_rx_done_mask                                           (0x00000080)
#define MIS_IC4_RAW_INTR_STAT_rx_done(data)                                          (0x00000080&((data)<<7))
#define MIS_IC4_RAW_INTR_STAT_rx_done_src(data)                                      ((0x00000080&(data))>>7)
#define MIS_IC4_RAW_INTR_STAT_get_rx_done(data)                                      ((0x00000080&(data))>>7)
#define MIS_IC4_RAW_INTR_STAT_tx_abrt_shift                                          (6)
#define MIS_IC4_RAW_INTR_STAT_tx_abrt_mask                                           (0x00000040)
#define MIS_IC4_RAW_INTR_STAT_tx_abrt(data)                                          (0x00000040&((data)<<6))
#define MIS_IC4_RAW_INTR_STAT_tx_abrt_src(data)                                      ((0x00000040&(data))>>6)
#define MIS_IC4_RAW_INTR_STAT_get_tx_abrt(data)                                      ((0x00000040&(data))>>6)
#define MIS_IC4_RAW_INTR_STAT_rd_req_shift                                           (5)
#define MIS_IC4_RAW_INTR_STAT_rd_req_mask                                            (0x00000020)
#define MIS_IC4_RAW_INTR_STAT_rd_req(data)                                           (0x00000020&((data)<<5))
#define MIS_IC4_RAW_INTR_STAT_rd_req_src(data)                                       ((0x00000020&(data))>>5)
#define MIS_IC4_RAW_INTR_STAT_get_rd_req(data)                                       ((0x00000020&(data))>>5)
#define MIS_IC4_RAW_INTR_STAT_tx_empty_shift                                         (4)
#define MIS_IC4_RAW_INTR_STAT_tx_empty_mask                                          (0x00000010)
#define MIS_IC4_RAW_INTR_STAT_tx_empty(data)                                         (0x00000010&((data)<<4))
#define MIS_IC4_RAW_INTR_STAT_tx_empty_src(data)                                     ((0x00000010&(data))>>4)
#define MIS_IC4_RAW_INTR_STAT_get_tx_empty(data)                                     ((0x00000010&(data))>>4)
#define MIS_IC4_RAW_INTR_STAT_tx_over_shift                                          (3)
#define MIS_IC4_RAW_INTR_STAT_tx_over_mask                                           (0x00000008)
#define MIS_IC4_RAW_INTR_STAT_tx_over(data)                                          (0x00000008&((data)<<3))
#define MIS_IC4_RAW_INTR_STAT_tx_over_src(data)                                      ((0x00000008&(data))>>3)
#define MIS_IC4_RAW_INTR_STAT_get_tx_over(data)                                      ((0x00000008&(data))>>3)
#define MIS_IC4_RAW_INTR_STAT_rx_full_shift                                          (2)
#define MIS_IC4_RAW_INTR_STAT_rx_full_mask                                           (0x00000004)
#define MIS_IC4_RAW_INTR_STAT_rx_full(data)                                          (0x00000004&((data)<<2))
#define MIS_IC4_RAW_INTR_STAT_rx_full_src(data)                                      ((0x00000004&(data))>>2)
#define MIS_IC4_RAW_INTR_STAT_get_rx_full(data)                                      ((0x00000004&(data))>>2)
#define MIS_IC4_RAW_INTR_STAT_rx_over_shift                                          (1)
#define MIS_IC4_RAW_INTR_STAT_rx_over_mask                                           (0x00000002)
#define MIS_IC4_RAW_INTR_STAT_rx_over(data)                                          (0x00000002&((data)<<1))
#define MIS_IC4_RAW_INTR_STAT_rx_over_src(data)                                      ((0x00000002&(data))>>1)
#define MIS_IC4_RAW_INTR_STAT_get_rx_over(data)                                      ((0x00000002&(data))>>1)
#define MIS_IC4_RAW_INTR_STAT_rx_under_shift                                         (0)
#define MIS_IC4_RAW_INTR_STAT_rx_under_mask                                          (0x00000001)
#define MIS_IC4_RAW_INTR_STAT_rx_under(data)                                         (0x00000001&((data)<<0))
#define MIS_IC4_RAW_INTR_STAT_rx_under_src(data)                                     ((0x00000001&(data))>>0)
#define MIS_IC4_RAW_INTR_STAT_get_rx_under(data)                                     ((0x00000001&(data))>>0)


#define MIS_IC4_RX_TL                                                                0x9801BA38
#define MIS_IC4_RX_TL_reg_addr                                                       "0x9801BA38"
#define MIS_IC4_RX_TL_reg                                                            0x9801BA38
#define set_MIS_IC4_RX_TL_reg(data)   (*((volatile unsigned int*) MIS_IC4_RX_TL_reg)=data)
#define get_MIS_IC4_RX_TL_reg   (*((volatile unsigned int*) MIS_IC4_RX_TL_reg))
#define MIS_IC4_RX_TL_inst_adr                                                       "0x008E"
#define MIS_IC4_RX_TL_inst                                                           0x008E
#define MIS_IC4_RX_TL_rx_tl_shift                                                    (0)
#define MIS_IC4_RX_TL_rx_tl_mask                                                     (0x000000FF)
#define MIS_IC4_RX_TL_rx_tl(data)                                                    (0x000000FF&((data)<<0))
#define MIS_IC4_RX_TL_rx_tl_src(data)                                                ((0x000000FF&(data))>>0)
#define MIS_IC4_RX_TL_get_rx_tl(data)                                                ((0x000000FF&(data))>>0)


#define MIS_IC4_TX_TL                                                                0x9801BA3C
#define MIS_IC4_TX_TL_reg_addr                                                       "0x9801BA3C"
#define MIS_IC4_TX_TL_reg                                                            0x9801BA3C
#define set_MIS_IC4_TX_TL_reg(data)   (*((volatile unsigned int*) MIS_IC4_TX_TL_reg)=data)
#define get_MIS_IC4_TX_TL_reg   (*((volatile unsigned int*) MIS_IC4_TX_TL_reg))
#define MIS_IC4_TX_TL_inst_adr                                                       "0x008F"
#define MIS_IC4_TX_TL_inst                                                           0x008F
#define MIS_IC4_TX_TL_tx_tl_shift                                                    (0)
#define MIS_IC4_TX_TL_tx_tl_mask                                                     (0x000000FF)
#define MIS_IC4_TX_TL_tx_tl(data)                                                    (0x000000FF&((data)<<0))
#define MIS_IC4_TX_TL_tx_tl_src(data)                                                ((0x000000FF&(data))>>0)
#define MIS_IC4_TX_TL_get_tx_tl(data)                                                ((0x000000FF&(data))>>0)


#define MIS_IC4_CLR_INTR                                                             0x9801BA40
#define MIS_IC4_CLR_INTR_reg_addr                                                    "0x9801BA40"
#define MIS_IC4_CLR_INTR_reg                                                         0x9801BA40
#define set_MIS_IC4_CLR_INTR_reg(data)   (*((volatile unsigned int*) MIS_IC4_CLR_INTR_reg)=data)
#define get_MIS_IC4_CLR_INTR_reg   (*((volatile unsigned int*) MIS_IC4_CLR_INTR_reg))
#define MIS_IC4_CLR_INTR_inst_adr                                                    "0x0090"
#define MIS_IC4_CLR_INTR_inst                                                        0x0090
#define MIS_IC4_CLR_INTR_clr_intr_shift                                              (0)
#define MIS_IC4_CLR_INTR_clr_intr_mask                                               (0x00000001)
#define MIS_IC4_CLR_INTR_clr_intr(data)                                              (0x00000001&((data)<<0))
#define MIS_IC4_CLR_INTR_clr_intr_src(data)                                          ((0x00000001&(data))>>0)
#define MIS_IC4_CLR_INTR_get_clr_intr(data)                                          ((0x00000001&(data))>>0)


#define MIS_IC4_CLR_RX_UNDER                                                         0x9801BA44
#define MIS_IC4_CLR_RX_UNDER_reg_addr                                                "0x9801BA44"
#define MIS_IC4_CLR_RX_UNDER_reg                                                     0x9801BA44
#define set_MIS_IC4_CLR_RX_UNDER_reg(data)   (*((volatile unsigned int*) MIS_IC4_CLR_RX_UNDER_reg)=data)
#define get_MIS_IC4_CLR_RX_UNDER_reg   (*((volatile unsigned int*) MIS_IC4_CLR_RX_UNDER_reg))
#define MIS_IC4_CLR_RX_UNDER_inst_adr                                                "0x0091"
#define MIS_IC4_CLR_RX_UNDER_inst                                                    0x0091
#define MIS_IC4_CLR_RX_UNDER_clr_rx_under_shift                                      (0)
#define MIS_IC4_CLR_RX_UNDER_clr_rx_under_mask                                       (0x00000001)
#define MIS_IC4_CLR_RX_UNDER_clr_rx_under(data)                                      (0x00000001&((data)<<0))
#define MIS_IC4_CLR_RX_UNDER_clr_rx_under_src(data)                                  ((0x00000001&(data))>>0)
#define MIS_IC4_CLR_RX_UNDER_get_clr_rx_under(data)                                  ((0x00000001&(data))>>0)


#define MIS_IC4_CLR_RX_OVER                                                          0x9801BA48
#define MIS_IC4_CLR_RX_OVER_reg_addr                                                 "0x9801BA48"
#define MIS_IC4_CLR_RX_OVER_reg                                                      0x9801BA48
#define set_MIS_IC4_CLR_RX_OVER_reg(data)   (*((volatile unsigned int*) MIS_IC4_CLR_RX_OVER_reg)=data)
#define get_MIS_IC4_CLR_RX_OVER_reg   (*((volatile unsigned int*) MIS_IC4_CLR_RX_OVER_reg))
#define MIS_IC4_CLR_RX_OVER_inst_adr                                                 "0x0092"
#define MIS_IC4_CLR_RX_OVER_inst                                                     0x0092
#define MIS_IC4_CLR_RX_OVER_clr_rx_over_shift                                        (0)
#define MIS_IC4_CLR_RX_OVER_clr_rx_over_mask                                         (0x00000001)
#define MIS_IC4_CLR_RX_OVER_clr_rx_over(data)                                        (0x00000001&((data)<<0))
#define MIS_IC4_CLR_RX_OVER_clr_rx_over_src(data)                                    ((0x00000001&(data))>>0)
#define MIS_IC4_CLR_RX_OVER_get_clr_rx_over(data)                                    ((0x00000001&(data))>>0)


#define MIS_IC4_CLR_TX_OVER                                                          0x9801BA4C
#define MIS_IC4_CLR_TX_OVER_reg_addr                                                 "0x9801BA4C"
#define MIS_IC4_CLR_TX_OVER_reg                                                      0x9801BA4C
#define set_MIS_IC4_CLR_TX_OVER_reg(data)   (*((volatile unsigned int*) MIS_IC4_CLR_TX_OVER_reg)=data)
#define get_MIS_IC4_CLR_TX_OVER_reg   (*((volatile unsigned int*) MIS_IC4_CLR_TX_OVER_reg))
#define MIS_IC4_CLR_TX_OVER_inst_adr                                                 "0x0093"
#define MIS_IC4_CLR_TX_OVER_inst                                                     0x0093
#define MIS_IC4_CLR_TX_OVER_clr_tx_over_shift                                        (0)
#define MIS_IC4_CLR_TX_OVER_clr_tx_over_mask                                         (0x00000001)
#define MIS_IC4_CLR_TX_OVER_clr_tx_over(data)                                        (0x00000001&((data)<<0))
#define MIS_IC4_CLR_TX_OVER_clr_tx_over_src(data)                                    ((0x00000001&(data))>>0)
#define MIS_IC4_CLR_TX_OVER_get_clr_tx_over(data)                                    ((0x00000001&(data))>>0)


#define MIS_IC4_CLR_RD_REQ                                                           0x9801BA50
#define MIS_IC4_CLR_RD_REQ_reg_addr                                                  "0x9801BA50"
#define MIS_IC4_CLR_RD_REQ_reg                                                       0x9801BA50
#define set_MIS_IC4_CLR_RD_REQ_reg(data)   (*((volatile unsigned int*) MIS_IC4_CLR_RD_REQ_reg)=data)
#define get_MIS_IC4_CLR_RD_REQ_reg   (*((volatile unsigned int*) MIS_IC4_CLR_RD_REQ_reg))
#define MIS_IC4_CLR_RD_REQ_inst_adr                                                  "0x0094"
#define MIS_IC4_CLR_RD_REQ_inst                                                      0x0094
#define MIS_IC4_CLR_RD_REQ_clr_rd_req_shift                                          (0)
#define MIS_IC4_CLR_RD_REQ_clr_rd_req_mask                                           (0x00000001)
#define MIS_IC4_CLR_RD_REQ_clr_rd_req(data)                                          (0x00000001&((data)<<0))
#define MIS_IC4_CLR_RD_REQ_clr_rd_req_src(data)                                      ((0x00000001&(data))>>0)
#define MIS_IC4_CLR_RD_REQ_get_clr_rd_req(data)                                      ((0x00000001&(data))>>0)


#define MIS_IC4_CLR_TX_ABRT                                                          0x9801BA54
#define MIS_IC4_CLR_TX_ABRT_reg_addr                                                 "0x9801BA54"
#define MIS_IC4_CLR_TX_ABRT_reg                                                      0x9801BA54
#define set_MIS_IC4_CLR_TX_ABRT_reg(data)   (*((volatile unsigned int*) MIS_IC4_CLR_TX_ABRT_reg)=data)
#define get_MIS_IC4_CLR_TX_ABRT_reg   (*((volatile unsigned int*) MIS_IC4_CLR_TX_ABRT_reg))
#define MIS_IC4_CLR_TX_ABRT_inst_adr                                                 "0x0095"
#define MIS_IC4_CLR_TX_ABRT_inst                                                     0x0095
#define MIS_IC4_CLR_TX_ABRT_clr_tx_abrt_shift                                        (0)
#define MIS_IC4_CLR_TX_ABRT_clr_tx_abrt_mask                                         (0x00000001)
#define MIS_IC4_CLR_TX_ABRT_clr_tx_abrt(data)                                        (0x00000001&((data)<<0))
#define MIS_IC4_CLR_TX_ABRT_clr_tx_abrt_src(data)                                    ((0x00000001&(data))>>0)
#define MIS_IC4_CLR_TX_ABRT_get_clr_tx_abrt(data)                                    ((0x00000001&(data))>>0)


#define MIS_IC4_CLR_RX_DONE                                                          0x9801BA58
#define MIS_IC4_CLR_RX_DONE_reg_addr                                                 "0x9801BA58"
#define MIS_IC4_CLR_RX_DONE_reg                                                      0x9801BA58
#define set_MIS_IC4_CLR_RX_DONE_reg(data)   (*((volatile unsigned int*) MIS_IC4_CLR_RX_DONE_reg)=data)
#define get_MIS_IC4_CLR_RX_DONE_reg   (*((volatile unsigned int*) MIS_IC4_CLR_RX_DONE_reg))
#define MIS_IC4_CLR_RX_DONE_inst_adr                                                 "0x0096"
#define MIS_IC4_CLR_RX_DONE_inst                                                     0x0096
#define MIS_IC4_CLR_RX_DONE_clr_rx_done_shift                                        (0)
#define MIS_IC4_CLR_RX_DONE_clr_rx_done_mask                                         (0x00000001)
#define MIS_IC4_CLR_RX_DONE_clr_rx_done(data)                                        (0x00000001&((data)<<0))
#define MIS_IC4_CLR_RX_DONE_clr_rx_done_src(data)                                    ((0x00000001&(data))>>0)
#define MIS_IC4_CLR_RX_DONE_get_clr_rx_done(data)                                    ((0x00000001&(data))>>0)


#define MIS_IC4_CLR_ACTIVITY                                                         0x9801BA5C
#define MIS_IC4_CLR_ACTIVITY_reg_addr                                                "0x9801BA5C"
#define MIS_IC4_CLR_ACTIVITY_reg                                                     0x9801BA5C
#define set_MIS_IC4_CLR_ACTIVITY_reg(data)   (*((volatile unsigned int*) MIS_IC4_CLR_ACTIVITY_reg)=data)
#define get_MIS_IC4_CLR_ACTIVITY_reg   (*((volatile unsigned int*) MIS_IC4_CLR_ACTIVITY_reg))
#define MIS_IC4_CLR_ACTIVITY_inst_adr                                                "0x0097"
#define MIS_IC4_CLR_ACTIVITY_inst                                                    0x0097
#define MIS_IC4_CLR_ACTIVITY_clr_activity_shift                                      (0)
#define MIS_IC4_CLR_ACTIVITY_clr_activity_mask                                       (0x00000001)
#define MIS_IC4_CLR_ACTIVITY_clr_activity(data)                                      (0x00000001&((data)<<0))
#define MIS_IC4_CLR_ACTIVITY_clr_activity_src(data)                                  ((0x00000001&(data))>>0)
#define MIS_IC4_CLR_ACTIVITY_get_clr_activity(data)                                  ((0x00000001&(data))>>0)


#define MIS_IC4_CLR_STOP_DET                                                         0x9801BA60
#define MIS_IC4_CLR_STOP_DET_reg_addr                                                "0x9801BA60"
#define MIS_IC4_CLR_STOP_DET_reg                                                     0x9801BA60
#define set_MIS_IC4_CLR_STOP_DET_reg(data)   (*((volatile unsigned int*) MIS_IC4_CLR_STOP_DET_reg)=data)
#define get_MIS_IC4_CLR_STOP_DET_reg   (*((volatile unsigned int*) MIS_IC4_CLR_STOP_DET_reg))
#define MIS_IC4_CLR_STOP_DET_inst_adr                                                "0x0098"
#define MIS_IC4_CLR_STOP_DET_inst                                                    0x0098
#define MIS_IC4_CLR_STOP_DET_clr_stop_det_shift                                      (0)
#define MIS_IC4_CLR_STOP_DET_clr_stop_det_mask                                       (0x00000001)
#define MIS_IC4_CLR_STOP_DET_clr_stop_det(data)                                      (0x00000001&((data)<<0))
#define MIS_IC4_CLR_STOP_DET_clr_stop_det_src(data)                                  ((0x00000001&(data))>>0)
#define MIS_IC4_CLR_STOP_DET_get_clr_stop_det(data)                                  ((0x00000001&(data))>>0)


#define MIS_IC4_CLR_START_DET                                                        0x9801BA64
#define MIS_IC4_CLR_START_DET_reg_addr                                               "0x9801BA64"
#define MIS_IC4_CLR_START_DET_reg                                                    0x9801BA64
#define set_MIS_IC4_CLR_START_DET_reg(data)   (*((volatile unsigned int*) MIS_IC4_CLR_START_DET_reg)=data)
#define get_MIS_IC4_CLR_START_DET_reg   (*((volatile unsigned int*) MIS_IC4_CLR_START_DET_reg))
#define MIS_IC4_CLR_START_DET_inst_adr                                               "0x0099"
#define MIS_IC4_CLR_START_DET_inst                                                   0x0099
#define MIS_IC4_CLR_START_DET_clr_start_det_shift                                    (0)
#define MIS_IC4_CLR_START_DET_clr_start_det_mask                                     (0x00000001)
#define MIS_IC4_CLR_START_DET_clr_start_det(data)                                    (0x00000001&((data)<<0))
#define MIS_IC4_CLR_START_DET_clr_start_det_src(data)                                ((0x00000001&(data))>>0)
#define MIS_IC4_CLR_START_DET_get_clr_start_det(data)                                ((0x00000001&(data))>>0)


#define MIS_IC4_CLR_GEN_CALL                                                         0x9801BA68
#define MIS_IC4_CLR_GEN_CALL_reg_addr                                                "0x9801BA68"
#define MIS_IC4_CLR_GEN_CALL_reg                                                     0x9801BA68
#define set_MIS_IC4_CLR_GEN_CALL_reg(data)   (*((volatile unsigned int*) MIS_IC4_CLR_GEN_CALL_reg)=data)
#define get_MIS_IC4_CLR_GEN_CALL_reg   (*((volatile unsigned int*) MIS_IC4_CLR_GEN_CALL_reg))
#define MIS_IC4_CLR_GEN_CALL_inst_adr                                                "0x009A"
#define MIS_IC4_CLR_GEN_CALL_inst                                                    0x009A
#define MIS_IC4_CLR_GEN_CALL_clr_gen_call_shift                                      (0)
#define MIS_IC4_CLR_GEN_CALL_clr_gen_call_mask                                       (0x00000001)
#define MIS_IC4_CLR_GEN_CALL_clr_gen_call(data)                                      (0x00000001&((data)<<0))
#define MIS_IC4_CLR_GEN_CALL_clr_gen_call_src(data)                                  ((0x00000001&(data))>>0)
#define MIS_IC4_CLR_GEN_CALL_get_clr_gen_call(data)                                  ((0x00000001&(data))>>0)


#define MIS_IC4_ENABLE                                                               0x9801BA6C
#define MIS_IC4_ENABLE_reg_addr                                                      "0x9801BA6C"
#define MIS_IC4_ENABLE_reg                                                           0x9801BA6C
#define set_MIS_IC4_ENABLE_reg(data)   (*((volatile unsigned int*) MIS_IC4_ENABLE_reg)=data)
#define get_MIS_IC4_ENABLE_reg   (*((volatile unsigned int*) MIS_IC4_ENABLE_reg))
#define MIS_IC4_ENABLE_inst_adr                                                      "0x009B"
#define MIS_IC4_ENABLE_inst                                                          0x009B
#define MIS_IC4_ENABLE_enable_shift                                                  (0)
#define MIS_IC4_ENABLE_enable_mask                                                   (0x00000001)
#define MIS_IC4_ENABLE_enable(data)                                                  (0x00000001&((data)<<0))
#define MIS_IC4_ENABLE_enable_src(data)                                              ((0x00000001&(data))>>0)
#define MIS_IC4_ENABLE_get_enable(data)                                              ((0x00000001&(data))>>0)


#define MIS_IC4_STATUS                                                               0x9801BA70
#define MIS_IC4_STATUS_reg_addr                                                      "0x9801BA70"
#define MIS_IC4_STATUS_reg                                                           0x9801BA70
#define set_MIS_IC4_STATUS_reg(data)   (*((volatile unsigned int*) MIS_IC4_STATUS_reg)=data)
#define get_MIS_IC4_STATUS_reg   (*((volatile unsigned int*) MIS_IC4_STATUS_reg))
#define MIS_IC4_STATUS_inst_adr                                                      "0x009C"
#define MIS_IC4_STATUS_inst                                                          0x009C
#define MIS_IC4_STATUS_slv_activity_shift                                            (6)
#define MIS_IC4_STATUS_slv_activity_mask                                             (0x00000040)
#define MIS_IC4_STATUS_slv_activity(data)                                            (0x00000040&((data)<<6))
#define MIS_IC4_STATUS_slv_activity_src(data)                                        ((0x00000040&(data))>>6)
#define MIS_IC4_STATUS_get_slv_activity(data)                                        ((0x00000040&(data))>>6)
#define MIS_IC4_STATUS_mst_activity_shift                                            (5)
#define MIS_IC4_STATUS_mst_activity_mask                                             (0x00000020)
#define MIS_IC4_STATUS_mst_activity(data)                                            (0x00000020&((data)<<5))
#define MIS_IC4_STATUS_mst_activity_src(data)                                        ((0x00000020&(data))>>5)
#define MIS_IC4_STATUS_get_mst_activity(data)                                        ((0x00000020&(data))>>5)
#define MIS_IC4_STATUS_rff_shift                                                     (4)
#define MIS_IC4_STATUS_rff_mask                                                      (0x00000010)
#define MIS_IC4_STATUS_rff(data)                                                     (0x00000010&((data)<<4))
#define MIS_IC4_STATUS_rff_src(data)                                                 ((0x00000010&(data))>>4)
#define MIS_IC4_STATUS_get_rff(data)                                                 ((0x00000010&(data))>>4)
#define MIS_IC4_STATUS_rfne_shift                                                    (3)
#define MIS_IC4_STATUS_rfne_mask                                                     (0x00000008)
#define MIS_IC4_STATUS_rfne(data)                                                    (0x00000008&((data)<<3))
#define MIS_IC4_STATUS_rfne_src(data)                                                ((0x00000008&(data))>>3)
#define MIS_IC4_STATUS_get_rfne(data)                                                ((0x00000008&(data))>>3)
#define MIS_IC4_STATUS_tfe_shift                                                     (2)
#define MIS_IC4_STATUS_tfe_mask                                                      (0x00000004)
#define MIS_IC4_STATUS_tfe(data)                                                     (0x00000004&((data)<<2))
#define MIS_IC4_STATUS_tfe_src(data)                                                 ((0x00000004&(data))>>2)
#define MIS_IC4_STATUS_get_tfe(data)                                                 ((0x00000004&(data))>>2)
#define MIS_IC4_STATUS_tfnf_shift                                                    (1)
#define MIS_IC4_STATUS_tfnf_mask                                                     (0x00000002)
#define MIS_IC4_STATUS_tfnf(data)                                                    (0x00000002&((data)<<1))
#define MIS_IC4_STATUS_tfnf_src(data)                                                ((0x00000002&(data))>>1)
#define MIS_IC4_STATUS_get_tfnf(data)                                                ((0x00000002&(data))>>1)
#define MIS_IC4_STATUS_activity_shift                                                (0)
#define MIS_IC4_STATUS_activity_mask                                                 (0x00000001)
#define MIS_IC4_STATUS_activity(data)                                                (0x00000001&((data)<<0))
#define MIS_IC4_STATUS_activity_src(data)                                            ((0x00000001&(data))>>0)
#define MIS_IC4_STATUS_get_activity(data)                                            ((0x00000001&(data))>>0)


#define MIS_IC4_TXFLR                                                                0x9801BA74
#define MIS_IC4_TXFLR_reg_addr                                                       "0x9801BA74"
#define MIS_IC4_TXFLR_reg                                                            0x9801BA74
#define set_MIS_IC4_TXFLR_reg(data)   (*((volatile unsigned int*) MIS_IC4_TXFLR_reg)=data)
#define get_MIS_IC4_TXFLR_reg   (*((volatile unsigned int*) MIS_IC4_TXFLR_reg))
#define MIS_IC4_TXFLR_inst_adr                                                       "0x009D"
#define MIS_IC4_TXFLR_inst                                                           0x009D
#define MIS_IC4_TXFLR_txflr_shift                                                    (0)
#define MIS_IC4_TXFLR_txflr_mask                                                     (0x0000000F)
#define MIS_IC4_TXFLR_txflr(data)                                                    (0x0000000F&((data)<<0))
#define MIS_IC4_TXFLR_txflr_src(data)                                                ((0x0000000F&(data))>>0)
#define MIS_IC4_TXFLR_get_txflr(data)                                                ((0x0000000F&(data))>>0)


#define MIS_IC4_RXFLR                                                                0x9801BA78
#define MIS_IC4_RXFLR_reg_addr                                                       "0x9801BA78"
#define MIS_IC4_RXFLR_reg                                                            0x9801BA78
#define set_MIS_IC4_RXFLR_reg(data)   (*((volatile unsigned int*) MIS_IC4_RXFLR_reg)=data)
#define get_MIS_IC4_RXFLR_reg   (*((volatile unsigned int*) MIS_IC4_RXFLR_reg))
#define MIS_IC4_RXFLR_inst_adr                                                       "0x009E"
#define MIS_IC4_RXFLR_inst                                                           0x009E
#define MIS_IC4_RXFLR_rxflr_shift                                                    (0)
#define MIS_IC4_RXFLR_rxflr_mask                                                     (0x0000000F)
#define MIS_IC4_RXFLR_rxflr(data)                                                    (0x0000000F&((data)<<0))
#define MIS_IC4_RXFLR_rxflr_src(data)                                                ((0x0000000F&(data))>>0)
#define MIS_IC4_RXFLR_get_rxflr(data)                                                ((0x0000000F&(data))>>0)


#define MIS_IC4_SDA_HOLD                                                             0x9801BA7C
#define MIS_IC4_SDA_HOLD_reg_addr                                                    "0x9801BA7C"
#define MIS_IC4_SDA_HOLD_reg                                                         0x9801BA7C
#define set_MIS_IC4_SDA_HOLD_reg(data)   (*((volatile unsigned int*) MIS_IC4_SDA_HOLD_reg)=data)
#define get_MIS_IC4_SDA_HOLD_reg   (*((volatile unsigned int*) MIS_IC4_SDA_HOLD_reg))
#define MIS_IC4_SDA_HOLD_inst_adr                                                    "0x009F"
#define MIS_IC4_SDA_HOLD_inst                                                        0x009F
#define MIS_IC4_SDA_HOLD_sda_hold_shift                                              (0)
#define MIS_IC4_SDA_HOLD_sda_hold_mask                                               (0x0000FFFF)
#define MIS_IC4_SDA_HOLD_sda_hold(data)                                              (0x0000FFFF&((data)<<0))
#define MIS_IC4_SDA_HOLD_sda_hold_src(data)                                          ((0x0000FFFF&(data))>>0)
#define MIS_IC4_SDA_HOLD_get_sda_hold(data)                                          ((0x0000FFFF&(data))>>0)


#define MIS_IC4_TX_ABRT_SOURCE                                                       0x9801BA80
#define MIS_IC4_TX_ABRT_SOURCE_reg_addr                                              "0x9801BA80"
#define MIS_IC4_TX_ABRT_SOURCE_reg                                                   0x9801BA80
#define set_MIS_IC4_TX_ABRT_SOURCE_reg(data)   (*((volatile unsigned int*) MIS_IC4_TX_ABRT_SOURCE_reg)=data)
#define get_MIS_IC4_TX_ABRT_SOURCE_reg   (*((volatile unsigned int*) MIS_IC4_TX_ABRT_SOURCE_reg))
#define MIS_IC4_TX_ABRT_SOURCE_inst_adr                                              "0x00A0"
#define MIS_IC4_TX_ABRT_SOURCE_inst                                                  0x00A0
#define MIS_IC4_TX_ABRT_SOURCE_abrt_slvrd_intx_shift                                 (15)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_slvrd_intx_mask                                  (0x00008000)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_slvrd_intx(data)                                 (0x00008000&((data)<<15))
#define MIS_IC4_TX_ABRT_SOURCE_abrt_slvrd_intx_src(data)                             ((0x00008000&(data))>>15)
#define MIS_IC4_TX_ABRT_SOURCE_get_abrt_slvrd_intx(data)                             ((0x00008000&(data))>>15)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_slv_arblost_shift                                (14)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_slv_arblost_mask                                 (0x00004000)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_slv_arblost(data)                                (0x00004000&((data)<<14))
#define MIS_IC4_TX_ABRT_SOURCE_abrt_slv_arblost_src(data)                            ((0x00004000&(data))>>14)
#define MIS_IC4_TX_ABRT_SOURCE_get_abrt_slv_arblost(data)                            ((0x00004000&(data))>>14)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_slvflush_txfifo_shift                            (13)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_slvflush_txfifo_mask                             (0x00002000)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_slvflush_txfifo(data)                            (0x00002000&((data)<<13))
#define MIS_IC4_TX_ABRT_SOURCE_abrt_slvflush_txfifo_src(data)                        ((0x00002000&(data))>>13)
#define MIS_IC4_TX_ABRT_SOURCE_get_abrt_slvflush_txfifo(data)                        ((0x00002000&(data))>>13)
#define MIS_IC4_TX_ABRT_SOURCE_arb_lost_shift                                        (12)
#define MIS_IC4_TX_ABRT_SOURCE_arb_lost_mask                                         (0x00001000)
#define MIS_IC4_TX_ABRT_SOURCE_arb_lost(data)                                        (0x00001000&((data)<<12))
#define MIS_IC4_TX_ABRT_SOURCE_arb_lost_src(data)                                    ((0x00001000&(data))>>12)
#define MIS_IC4_TX_ABRT_SOURCE_get_arb_lost(data)                                    ((0x00001000&(data))>>12)
#define MIS_IC4_TX_ABRT_SOURCE_arb_master_dis_shift                                  (11)
#define MIS_IC4_TX_ABRT_SOURCE_arb_master_dis_mask                                   (0x00000800)
#define MIS_IC4_TX_ABRT_SOURCE_arb_master_dis(data)                                  (0x00000800&((data)<<11))
#define MIS_IC4_TX_ABRT_SOURCE_arb_master_dis_src(data)                              ((0x00000800&(data))>>11)
#define MIS_IC4_TX_ABRT_SOURCE_get_arb_master_dis(data)                              ((0x00000800&(data))>>11)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_10b_rd_norstrt_shift                             (10)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_10b_rd_norstrt_mask                              (0x00000400)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_10b_rd_norstrt(data)                             (0x00000400&((data)<<10))
#define MIS_IC4_TX_ABRT_SOURCE_abrt_10b_rd_norstrt_src(data)                         ((0x00000400&(data))>>10)
#define MIS_IC4_TX_ABRT_SOURCE_get_abrt_10b_rd_norstrt(data)                         ((0x00000400&(data))>>10)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_sbyte_norstrt_shift                              (9)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_sbyte_norstrt_mask                               (0x00000200)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_sbyte_norstrt(data)                              (0x00000200&((data)<<9))
#define MIS_IC4_TX_ABRT_SOURCE_abrt_sbyte_norstrt_src(data)                          ((0x00000200&(data))>>9)
#define MIS_IC4_TX_ABRT_SOURCE_get_abrt_sbyte_norstrt(data)                          ((0x00000200&(data))>>9)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_hs_norstrt_shift                                 (8)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_hs_norstrt_mask                                  (0x00000100)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_hs_norstrt(data)                                 (0x00000100&((data)<<8))
#define MIS_IC4_TX_ABRT_SOURCE_abrt_hs_norstrt_src(data)                             ((0x00000100&(data))>>8)
#define MIS_IC4_TX_ABRT_SOURCE_get_abrt_hs_norstrt(data)                             ((0x00000100&(data))>>8)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_sbyte_ackdet_shift                               (7)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_sbyte_ackdet_mask                                (0x00000080)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_sbyte_ackdet(data)                               (0x00000080&((data)<<7))
#define MIS_IC4_TX_ABRT_SOURCE_abrt_sbyte_ackdet_src(data)                           ((0x00000080&(data))>>7)
#define MIS_IC4_TX_ABRT_SOURCE_get_abrt_sbyte_ackdet(data)                           ((0x00000080&(data))>>7)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_hs_ackdet_shift                                  (6)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_hs_ackdet_mask                                   (0x00000040)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_hs_ackdet(data)                                  (0x00000040&((data)<<6))
#define MIS_IC4_TX_ABRT_SOURCE_abrt_hs_ackdet_src(data)                              ((0x00000040&(data))>>6)
#define MIS_IC4_TX_ABRT_SOURCE_get_abrt_hs_ackdet(data)                              ((0x00000040&(data))>>6)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_gcall_read_shift                                 (5)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_gcall_read_mask                                  (0x00000020)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_gcall_read(data)                                 (0x00000020&((data)<<5))
#define MIS_IC4_TX_ABRT_SOURCE_abrt_gcall_read_src(data)                             ((0x00000020&(data))>>5)
#define MIS_IC4_TX_ABRT_SOURCE_get_abrt_gcall_read(data)                             ((0x00000020&(data))>>5)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_gcall_noack_shift                                (4)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_gcall_noack_mask                                 (0x00000010)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_gcall_noack(data)                                (0x00000010&((data)<<4))
#define MIS_IC4_TX_ABRT_SOURCE_abrt_gcall_noack_src(data)                            ((0x00000010&(data))>>4)
#define MIS_IC4_TX_ABRT_SOURCE_get_abrt_gcall_noack(data)                            ((0x00000010&(data))>>4)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_txdata_noack_shift                               (3)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_txdata_noack_mask                                (0x00000008)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_txdata_noack(data)                               (0x00000008&((data)<<3))
#define MIS_IC4_TX_ABRT_SOURCE_abrt_txdata_noack_src(data)                           ((0x00000008&(data))>>3)
#define MIS_IC4_TX_ABRT_SOURCE_get_abrt_txdata_noack(data)                           ((0x00000008&(data))>>3)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_10addr2_noack_shift                              (2)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_10addr2_noack_mask                               (0x00000004)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_10addr2_noack(data)                              (0x00000004&((data)<<2))
#define MIS_IC4_TX_ABRT_SOURCE_abrt_10addr2_noack_src(data)                          ((0x00000004&(data))>>2)
#define MIS_IC4_TX_ABRT_SOURCE_get_abrt_10addr2_noack(data)                          ((0x00000004&(data))>>2)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_10addr1_noack_shift                              (1)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_10addr1_noack_mask                               (0x00000002)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_10addr1_noack(data)                              (0x00000002&((data)<<1))
#define MIS_IC4_TX_ABRT_SOURCE_abrt_10addr1_noack_src(data)                          ((0x00000002&(data))>>1)
#define MIS_IC4_TX_ABRT_SOURCE_get_abrt_10addr1_noack(data)                          ((0x00000002&(data))>>1)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_7b_addr_noack_shift                              (0)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_7b_addr_noack_mask                               (0x00000001)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_7b_addr_noack(data)                              (0x00000001&((data)<<0))
#define MIS_IC4_TX_ABRT_SOURCE_abrt_7b_addr_noack_src(data)                          ((0x00000001&(data))>>0)
#define MIS_IC4_TX_ABRT_SOURCE_get_abrt_7b_addr_noack(data)                          ((0x00000001&(data))>>0)


#define MIS_IC4_SLV_DATA_NACK_ONLY                                                   0x9801BA84
#define MIS_IC4_SLV_DATA_NACK_ONLY_reg_addr                                          "0x9801BA84"
#define MIS_IC4_SLV_DATA_NACK_ONLY_reg                                               0x9801BA84
#define set_MIS_IC4_SLV_DATA_NACK_ONLY_reg(data)   (*((volatile unsigned int*) MIS_IC4_SLV_DATA_NACK_ONLY_reg)=data)
#define get_MIS_IC4_SLV_DATA_NACK_ONLY_reg   (*((volatile unsigned int*) MIS_IC4_SLV_DATA_NACK_ONLY_reg))
#define MIS_IC4_SLV_DATA_NACK_ONLY_inst_adr                                          "0x00A1"
#define MIS_IC4_SLV_DATA_NACK_ONLY_inst                                              0x00A1
#define MIS_IC4_SLV_DATA_NACK_ONLY_nack_shift                                        (0)
#define MIS_IC4_SLV_DATA_NACK_ONLY_nack_mask                                         (0x00000001)
#define MIS_IC4_SLV_DATA_NACK_ONLY_nack(data)                                        (0x00000001&((data)<<0))
#define MIS_IC4_SLV_DATA_NACK_ONLY_nack_src(data)                                    ((0x00000001&(data))>>0)
#define MIS_IC4_SLV_DATA_NACK_ONLY_get_nack(data)                                    ((0x00000001&(data))>>0)


#define MIS_IC4_DMA_CR                                                               0x9801BA88
#define MIS_IC4_DMA_CR_reg_addr                                                      "0x9801BA88"
#define MIS_IC4_DMA_CR_reg                                                           0x9801BA88
#define set_MIS_IC4_DMA_CR_reg(data)   (*((volatile unsigned int*) MIS_IC4_DMA_CR_reg)=data)
#define get_MIS_IC4_DMA_CR_reg   (*((volatile unsigned int*) MIS_IC4_DMA_CR_reg))
#define MIS_IC4_DMA_CR_inst_adr                                                      "0x00A2"
#define MIS_IC4_DMA_CR_inst                                                          0x00A2
#define MIS_IC4_DMA_CR_tdmae_shift                                                   (1)
#define MIS_IC4_DMA_CR_tdmae_mask                                                    (0x00000002)
#define MIS_IC4_DMA_CR_tdmae(data)                                                   (0x00000002&((data)<<1))
#define MIS_IC4_DMA_CR_tdmae_src(data)                                               ((0x00000002&(data))>>1)
#define MIS_IC4_DMA_CR_get_tdmae(data)                                               ((0x00000002&(data))>>1)
#define MIS_IC4_DMA_CR_rdmae_shift                                                   (0)
#define MIS_IC4_DMA_CR_rdmae_mask                                                    (0x00000001)
#define MIS_IC4_DMA_CR_rdmae(data)                                                   (0x00000001&((data)<<0))
#define MIS_IC4_DMA_CR_rdmae_src(data)                                               ((0x00000001&(data))>>0)
#define MIS_IC4_DMA_CR_get_rdmae(data)                                               ((0x00000001&(data))>>0)


#define MIS_IC4_DMA_TDLR                                                             0x9801BA8C
#define MIS_IC4_DMA_TDLR_reg_addr                                                    "0x9801BA8C"
#define MIS_IC4_DMA_TDLR_reg                                                         0x9801BA8C
#define set_MIS_IC4_DMA_TDLR_reg(data)   (*((volatile unsigned int*) MIS_IC4_DMA_TDLR_reg)=data)
#define get_MIS_IC4_DMA_TDLR_reg   (*((volatile unsigned int*) MIS_IC4_DMA_TDLR_reg))
#define MIS_IC4_DMA_TDLR_inst_adr                                                    "0x00A3"
#define MIS_IC4_DMA_TDLR_inst                                                        0x00A3
#define MIS_IC4_DMA_TDLR_dmatdl_shift                                                (0)
#define MIS_IC4_DMA_TDLR_dmatdl_mask                                                 (0x00000007)
#define MIS_IC4_DMA_TDLR_dmatdl(data)                                                (0x00000007&((data)<<0))
#define MIS_IC4_DMA_TDLR_dmatdl_src(data)                                            ((0x00000007&(data))>>0)
#define MIS_IC4_DMA_TDLR_get_dmatdl(data)                                            ((0x00000007&(data))>>0)


#define MIS_IC4_DMA_RDLR                                                             0x9801BA90
#define MIS_IC4_DMA_RDLR_reg_addr                                                    "0x9801BA90"
#define MIS_IC4_DMA_RDLR_reg                                                         0x9801BA90
#define set_MIS_IC4_DMA_RDLR_reg(data)   (*((volatile unsigned int*) MIS_IC4_DMA_RDLR_reg)=data)
#define get_MIS_IC4_DMA_RDLR_reg   (*((volatile unsigned int*) MIS_IC4_DMA_RDLR_reg))
#define MIS_IC4_DMA_RDLR_inst_adr                                                    "0x00A4"
#define MIS_IC4_DMA_RDLR_inst                                                        0x00A4
#define MIS_IC4_DMA_RDLR_dmardl_shift                                                (0)
#define MIS_IC4_DMA_RDLR_dmardl_mask                                                 (0x0000000F)
#define MIS_IC4_DMA_RDLR_dmardl(data)                                                (0x0000000F&((data)<<0))
#define MIS_IC4_DMA_RDLR_dmardl_src(data)                                            ((0x0000000F&(data))>>0)
#define MIS_IC4_DMA_RDLR_get_dmardl(data)                                            ((0x0000000F&(data))>>0)


#define MIS_IC4_SDA_SETUP                                                            0x9801BA94
#define MIS_IC4_SDA_SETUP_reg_addr                                                   "0x9801BA94"
#define MIS_IC4_SDA_SETUP_reg                                                        0x9801BA94
#define set_MIS_IC4_SDA_SETUP_reg(data)   (*((volatile unsigned int*) MIS_IC4_SDA_SETUP_reg)=data)
#define get_MIS_IC4_SDA_SETUP_reg   (*((volatile unsigned int*) MIS_IC4_SDA_SETUP_reg))
#define MIS_IC4_SDA_SETUP_inst_adr                                                   "0x00A5"
#define MIS_IC4_SDA_SETUP_inst                                                       0x00A5
#define MIS_IC4_SDA_SETUP_sda_setup_shift                                            (0)
#define MIS_IC4_SDA_SETUP_sda_setup_mask                                             (0x000000FF)
#define MIS_IC4_SDA_SETUP_sda_setup(data)                                            (0x000000FF&((data)<<0))
#define MIS_IC4_SDA_SETUP_sda_setup_src(data)                                        ((0x000000FF&(data))>>0)
#define MIS_IC4_SDA_SETUP_get_sda_setup(data)                                        ((0x000000FF&(data))>>0)


#define MIS_IC4_ACK_GENERAL_CALL                                                     0x9801BA98
#define MIS_IC4_ACK_GENERAL_CALL_reg_addr                                            "0x9801BA98"
#define MIS_IC4_ACK_GENERAL_CALL_reg                                                 0x9801BA98
#define set_MIS_IC4_ACK_GENERAL_CALL_reg(data)   (*((volatile unsigned int*) MIS_IC4_ACK_GENERAL_CALL_reg)=data)
#define get_MIS_IC4_ACK_GENERAL_CALL_reg   (*((volatile unsigned int*) MIS_IC4_ACK_GENERAL_CALL_reg))
#define MIS_IC4_ACK_GENERAL_CALL_inst_adr                                            "0x00A6"
#define MIS_IC4_ACK_GENERAL_CALL_inst                                                0x00A6
#define MIS_IC4_ACK_GENERAL_CALL_ack_gen_call_shift                                  (0)
#define MIS_IC4_ACK_GENERAL_CALL_ack_gen_call_mask                                   (0x00000001)
#define MIS_IC4_ACK_GENERAL_CALL_ack_gen_call(data)                                  (0x00000001&((data)<<0))
#define MIS_IC4_ACK_GENERAL_CALL_ack_gen_call_src(data)                              ((0x00000001&(data))>>0)
#define MIS_IC4_ACK_GENERAL_CALL_get_ack_gen_call(data)                              ((0x00000001&(data))>>0)


#define MIS_IC4_ENABLE_STATUS                                                        0x9801BA9C
#define MIS_IC4_ENABLE_STATUS_reg_addr                                               "0x9801BA9C"
#define MIS_IC4_ENABLE_STATUS_reg                                                    0x9801BA9C
#define set_MIS_IC4_ENABLE_STATUS_reg(data)   (*((volatile unsigned int*) MIS_IC4_ENABLE_STATUS_reg)=data)
#define get_MIS_IC4_ENABLE_STATUS_reg   (*((volatile unsigned int*) MIS_IC4_ENABLE_STATUS_reg))
#define MIS_IC4_ENABLE_STATUS_inst_adr                                               "0x00A7"
#define MIS_IC4_ENABLE_STATUS_inst                                                   0x00A7
#define MIS_IC4_ENABLE_STATUS_slv_rx_data_lost_shift                                 (2)
#define MIS_IC4_ENABLE_STATUS_slv_rx_data_lost_mask                                  (0x00000004)
#define MIS_IC4_ENABLE_STATUS_slv_rx_data_lost(data)                                 (0x00000004&((data)<<2))
#define MIS_IC4_ENABLE_STATUS_slv_rx_data_lost_src(data)                             ((0x00000004&(data))>>2)
#define MIS_IC4_ENABLE_STATUS_get_slv_rx_data_lost(data)                             ((0x00000004&(data))>>2)
#define MIS_IC4_ENABLE_STATUS_slv_disabled_whi_shift                                 (1)
#define MIS_IC4_ENABLE_STATUS_slv_disabled_whi_mask                                  (0x00000002)
#define MIS_IC4_ENABLE_STATUS_slv_disabled_whi(data)                                 (0x00000002&((data)<<1))
#define MIS_IC4_ENABLE_STATUS_slv_disabled_whi_src(data)                             ((0x00000002&(data))>>1)
#define MIS_IC4_ENABLE_STATUS_get_slv_disabled_whi(data)                             ((0x00000002&(data))>>1)
#define MIS_IC4_ENABLE_STATUS_ic_en_shift                                            (0)
#define MIS_IC4_ENABLE_STATUS_ic_en_mask                                             (0x00000001)
#define MIS_IC4_ENABLE_STATUS_ic_en(data)                                            (0x00000001&((data)<<0))
#define MIS_IC4_ENABLE_STATUS_ic_en_src(data)                                        ((0x00000001&(data))>>0)
#define MIS_IC4_ENABLE_STATUS_get_ic_en(data)                                        ((0x00000001&(data))>>0)


#define MIS_IC4_COMP_PARAM_1                                                         0x9801BAF4
#define MIS_IC4_COMP_PARAM_1_reg_addr                                                "0x9801BAF4"
#define MIS_IC4_COMP_PARAM_1_reg                                                     0x9801BAF4
#define set_MIS_IC4_COMP_PARAM_1_reg(data)   (*((volatile unsigned int*) MIS_IC4_COMP_PARAM_1_reg)=data)
#define get_MIS_IC4_COMP_PARAM_1_reg   (*((volatile unsigned int*) MIS_IC4_COMP_PARAM_1_reg))
#define MIS_IC4_COMP_PARAM_1_inst_adr                                                "0x00BD"
#define MIS_IC4_COMP_PARAM_1_inst                                                    0x00BD
#define MIS_IC4_COMP_PARAM_1_tx_buffer_depth_shift                                   (16)
#define MIS_IC4_COMP_PARAM_1_tx_buffer_depth_mask                                    (0x00FF0000)
#define MIS_IC4_COMP_PARAM_1_tx_buffer_depth(data)                                   (0x00FF0000&((data)<<16))
#define MIS_IC4_COMP_PARAM_1_tx_buffer_depth_src(data)                               ((0x00FF0000&(data))>>16)
#define MIS_IC4_COMP_PARAM_1_get_tx_buffer_depth(data)                               ((0x00FF0000&(data))>>16)
#define MIS_IC4_COMP_PARAM_1_rx_buffer_depth_shift                                   (8)
#define MIS_IC4_COMP_PARAM_1_rx_buffer_depth_mask                                    (0x0000FF00)
#define MIS_IC4_COMP_PARAM_1_rx_buffer_depth(data)                                   (0x0000FF00&((data)<<8))
#define MIS_IC4_COMP_PARAM_1_rx_buffer_depth_src(data)                               ((0x0000FF00&(data))>>8)
#define MIS_IC4_COMP_PARAM_1_get_rx_buffer_depth(data)                               ((0x0000FF00&(data))>>8)
#define MIS_IC4_COMP_PARAM_1_add_encoded_params_shift                                (7)
#define MIS_IC4_COMP_PARAM_1_add_encoded_params_mask                                 (0x00000080)
#define MIS_IC4_COMP_PARAM_1_add_encoded_params(data)                                (0x00000080&((data)<<7))
#define MIS_IC4_COMP_PARAM_1_add_encoded_params_src(data)                            ((0x00000080&(data))>>7)
#define MIS_IC4_COMP_PARAM_1_get_add_encoded_params(data)                            ((0x00000080&(data))>>7)
#define MIS_IC4_COMP_PARAM_1_has_dma_shift                                           (6)
#define MIS_IC4_COMP_PARAM_1_has_dma_mask                                            (0x00000040)
#define MIS_IC4_COMP_PARAM_1_has_dma(data)                                           (0x00000040&((data)<<6))
#define MIS_IC4_COMP_PARAM_1_has_dma_src(data)                                       ((0x00000040&(data))>>6)
#define MIS_IC4_COMP_PARAM_1_get_has_dma(data)                                       ((0x00000040&(data))>>6)
#define MIS_IC4_COMP_PARAM_1_intr_io_shift                                           (5)
#define MIS_IC4_COMP_PARAM_1_intr_io_mask                                            (0x00000020)
#define MIS_IC4_COMP_PARAM_1_intr_io(data)                                           (0x00000020&((data)<<5))
#define MIS_IC4_COMP_PARAM_1_intr_io_src(data)                                       ((0x00000020&(data))>>5)
#define MIS_IC4_COMP_PARAM_1_get_intr_io(data)                                       ((0x00000020&(data))>>5)
#define MIS_IC4_COMP_PARAM_1_hc_count_values_shift                                   (4)
#define MIS_IC4_COMP_PARAM_1_hc_count_values_mask                                    (0x00000010)
#define MIS_IC4_COMP_PARAM_1_hc_count_values(data)                                   (0x00000010&((data)<<4))
#define MIS_IC4_COMP_PARAM_1_hc_count_values_src(data)                               ((0x00000010&(data))>>4)
#define MIS_IC4_COMP_PARAM_1_get_hc_count_values(data)                               ((0x00000010&(data))>>4)
#define MIS_IC4_COMP_PARAM_1_max_speed_mode_shift                                    (2)
#define MIS_IC4_COMP_PARAM_1_max_speed_mode_mask                                     (0x0000000C)
#define MIS_IC4_COMP_PARAM_1_max_speed_mode(data)                                    (0x0000000C&((data)<<2))
#define MIS_IC4_COMP_PARAM_1_max_speed_mode_src(data)                                ((0x0000000C&(data))>>2)
#define MIS_IC4_COMP_PARAM_1_get_max_speed_mode(data)                                ((0x0000000C&(data))>>2)
#define MIS_IC4_COMP_PARAM_1_apb_data_width_shift                                    (0)
#define MIS_IC4_COMP_PARAM_1_apb_data_width_mask                                     (0x00000003)
#define MIS_IC4_COMP_PARAM_1_apb_data_width(data)                                    (0x00000003&((data)<<0))
#define MIS_IC4_COMP_PARAM_1_apb_data_width_src(data)                                ((0x00000003&(data))>>0)
#define MIS_IC4_COMP_PARAM_1_get_apb_data_width(data)                                ((0x00000003&(data))>>0)


#define MIS_IC4_COMP_VERSION                                                         0x9801BAF8
#define MIS_IC4_COMP_VERSION_reg_addr                                                "0x9801BAF8"
#define MIS_IC4_COMP_VERSION_reg                                                     0x9801BAF8
#define set_MIS_IC4_COMP_VERSION_reg(data)   (*((volatile unsigned int*) MIS_IC4_COMP_VERSION_reg)=data)
#define get_MIS_IC4_COMP_VERSION_reg   (*((volatile unsigned int*) MIS_IC4_COMP_VERSION_reg))
#define MIS_IC4_COMP_VERSION_inst_adr                                                "0x00BE"
#define MIS_IC4_COMP_VERSION_inst                                                    0x00BE
#define MIS_IC4_COMP_VERSION_ic_comp_version_shift                                   (0)
#define MIS_IC4_COMP_VERSION_ic_comp_version_mask                                    (0xFFFFFFFF)
#define MIS_IC4_COMP_VERSION_ic_comp_version(data)                                   (0xFFFFFFFF&((data)<<0))
#define MIS_IC4_COMP_VERSION_ic_comp_version_src(data)                               ((0xFFFFFFFF&(data))>>0)
#define MIS_IC4_COMP_VERSION_get_ic_comp_version(data)                               ((0xFFFFFFFF&(data))>>0)


#define MIS_IC4_COMP_TYPE                                                            0x9801BAFC
#define MIS_IC4_COMP_TYPE_reg_addr                                                   "0x9801BAFC"
#define MIS_IC4_COMP_TYPE_reg                                                        0x9801BAFC
#define set_MIS_IC4_COMP_TYPE_reg(data)   (*((volatile unsigned int*) MIS_IC4_COMP_TYPE_reg)=data)
#define get_MIS_IC4_COMP_TYPE_reg   (*((volatile unsigned int*) MIS_IC4_COMP_TYPE_reg))
#define MIS_IC4_COMP_TYPE_inst_adr                                                   "0x00BF"
#define MIS_IC4_COMP_TYPE_inst                                                       0x00BF
#define MIS_IC4_COMP_TYPE_ic_comp_type_shift                                         (0)
#define MIS_IC4_COMP_TYPE_ic_comp_type_mask                                          (0xFFFFFFFF)
#define MIS_IC4_COMP_TYPE_ic_comp_type(data)                                         (0xFFFFFFFF&((data)<<0))
#define MIS_IC4_COMP_TYPE_ic_comp_type_src(data)                                     ((0xFFFFFFFF&(data))>>0)
#define MIS_IC4_COMP_TYPE_get_ic_comp_type(data)                                     ((0xFFFFFFFF&(data))>>0)


#define MIS_IC5_CON                                                                  0x9801BB00
#define MIS_IC5_CON_reg_addr                                                         "0x9801BB00"
#define MIS_IC5_CON_reg                                                              0x9801BB00
#define set_MIS_IC5_CON_reg(data)   (*((volatile unsigned int*) MIS_IC5_CON_reg)=data)
#define get_MIS_IC5_CON_reg   (*((volatile unsigned int*) MIS_IC5_CON_reg))
#define MIS_IC5_CON_inst_adr                                                         "0x00C0"
#define MIS_IC5_CON_inst                                                             0x00C0
#define MIS_IC5_CON_ic_slave_disable_shift                                           (6)
#define MIS_IC5_CON_ic_slave_disable_mask                                            (0x00000040)
#define MIS_IC5_CON_ic_slave_disable(data)                                           (0x00000040&((data)<<6))
#define MIS_IC5_CON_ic_slave_disable_src(data)                                       ((0x00000040&(data))>>6)
#define MIS_IC5_CON_get_ic_slave_disable(data)                                       ((0x00000040&(data))>>6)
#define MIS_IC5_CON_ic_restart_en_shift                                              (5)
#define MIS_IC5_CON_ic_restart_en_mask                                               (0x00000020)
#define MIS_IC5_CON_ic_restart_en(data)                                              (0x00000020&((data)<<5))
#define MIS_IC5_CON_ic_restart_en_src(data)                                          ((0x00000020&(data))>>5)
#define MIS_IC5_CON_get_ic_restart_en(data)                                          ((0x00000020&(data))>>5)
#define MIS_IC5_CON_ic_10bitaddr_master_shift                                        (4)
#define MIS_IC5_CON_ic_10bitaddr_master_mask                                         (0x00000010)
#define MIS_IC5_CON_ic_10bitaddr_master(data)                                        (0x00000010&((data)<<4))
#define MIS_IC5_CON_ic_10bitaddr_master_src(data)                                    ((0x00000010&(data))>>4)
#define MIS_IC5_CON_get_ic_10bitaddr_master(data)                                    ((0x00000010&(data))>>4)
#define MIS_IC5_CON_ic_10bitaddr_slave_shift                                         (3)
#define MIS_IC5_CON_ic_10bitaddr_slave_mask                                          (0x00000008)
#define MIS_IC5_CON_ic_10bitaddr_slave(data)                                         (0x00000008&((data)<<3))
#define MIS_IC5_CON_ic_10bitaddr_slave_src(data)                                     ((0x00000008&(data))>>3)
#define MIS_IC5_CON_get_ic_10bitaddr_slave(data)                                     ((0x00000008&(data))>>3)
#define MIS_IC5_CON_speed_shift                                                      (1)
#define MIS_IC5_CON_speed_mask                                                       (0x00000006)
#define MIS_IC5_CON_speed(data)                                                      (0x00000006&((data)<<1))
#define MIS_IC5_CON_speed_src(data)                                                  ((0x00000006&(data))>>1)
#define MIS_IC5_CON_get_speed(data)                                                  ((0x00000006&(data))>>1)
#define MIS_IC5_CON_master_mode_shift                                                (0)
#define MIS_IC5_CON_master_mode_mask                                                 (0x00000001)
#define MIS_IC5_CON_master_mode(data)                                                (0x00000001&((data)<<0))
#define MIS_IC5_CON_master_mode_src(data)                                            ((0x00000001&(data))>>0)
#define MIS_IC5_CON_get_master_mode(data)                                            ((0x00000001&(data))>>0)


#define MIS_IC5_TAR                                                                  0x9801BB04
#define MIS_IC5_TAR_reg_addr                                                         "0x9801BB04"
#define MIS_IC5_TAR_reg                                                              0x9801BB04
#define set_MIS_IC5_TAR_reg(data)   (*((volatile unsigned int*) MIS_IC5_TAR_reg)=data)
#define get_MIS_IC5_TAR_reg   (*((volatile unsigned int*) MIS_IC5_TAR_reg))
#define MIS_IC5_TAR_inst_adr                                                         "0x00C1"
#define MIS_IC5_TAR_inst                                                             0x00C1
#define MIS_IC5_TAR_ic_10bitaddr_master_shift                                        (12)
#define MIS_IC5_TAR_ic_10bitaddr_master_mask                                         (0x00001000)
#define MIS_IC5_TAR_ic_10bitaddr_master(data)                                        (0x00001000&((data)<<12))
#define MIS_IC5_TAR_ic_10bitaddr_master_src(data)                                    ((0x00001000&(data))>>12)
#define MIS_IC5_TAR_get_ic_10bitaddr_master(data)                                    ((0x00001000&(data))>>12)
#define MIS_IC5_TAR_special_shift                                                    (11)
#define MIS_IC5_TAR_special_mask                                                     (0x00000800)
#define MIS_IC5_TAR_special(data)                                                    (0x00000800&((data)<<11))
#define MIS_IC5_TAR_special_src(data)                                                ((0x00000800&(data))>>11)
#define MIS_IC5_TAR_get_special(data)                                                ((0x00000800&(data))>>11)
#define MIS_IC5_TAR_gc_or_start_shift                                                (10)
#define MIS_IC5_TAR_gc_or_start_mask                                                 (0x00000400)
#define MIS_IC5_TAR_gc_or_start(data)                                                (0x00000400&((data)<<10))
#define MIS_IC5_TAR_gc_or_start_src(data)                                            ((0x00000400&(data))>>10)
#define MIS_IC5_TAR_get_gc_or_start(data)                                            ((0x00000400&(data))>>10)
#define MIS_IC5_TAR_ic_tar_shift                                                     (0)
#define MIS_IC5_TAR_ic_tar_mask                                                      (0x000003FF)
#define MIS_IC5_TAR_ic_tar(data)                                                     (0x000003FF&((data)<<0))
#define MIS_IC5_TAR_ic_tar_src(data)                                                 ((0x000003FF&(data))>>0)
#define MIS_IC5_TAR_get_ic_tar(data)                                                 ((0x000003FF&(data))>>0)


#define MIS_IC5_SAR                                                                  0x9801BB08
#define MIS_IC5_SAR_reg_addr                                                         "0x9801BB08"
#define MIS_IC5_SAR_reg                                                              0x9801BB08
#define set_MIS_IC5_SAR_reg(data)   (*((volatile unsigned int*) MIS_IC5_SAR_reg)=data)
#define get_MIS_IC5_SAR_reg   (*((volatile unsigned int*) MIS_IC5_SAR_reg))
#define MIS_IC5_SAR_inst_adr                                                         "0x00C2"
#define MIS_IC5_SAR_inst                                                             0x00C2
#define MIS_IC5_SAR_ic_sar_shift                                                     (0)
#define MIS_IC5_SAR_ic_sar_mask                                                      (0x000003FF)
#define MIS_IC5_SAR_ic_sar(data)                                                     (0x000003FF&((data)<<0))
#define MIS_IC5_SAR_ic_sar_src(data)                                                 ((0x000003FF&(data))>>0)
#define MIS_IC5_SAR_get_ic_sar(data)                                                 ((0x000003FF&(data))>>0)


#define MIS_IC5_HS_MADDR                                                             0x9801BB0C
#define MIS_IC5_HS_MADDR_reg_addr                                                    "0x9801BB0C"
#define MIS_IC5_HS_MADDR_reg                                                         0x9801BB0C
#define set_MIS_IC5_HS_MADDR_reg(data)   (*((volatile unsigned int*) MIS_IC5_HS_MADDR_reg)=data)
#define get_MIS_IC5_HS_MADDR_reg   (*((volatile unsigned int*) MIS_IC5_HS_MADDR_reg))
#define MIS_IC5_HS_MADDR_inst_adr                                                    "0x00C3"
#define MIS_IC5_HS_MADDR_inst                                                        0x00C3
#define MIS_IC5_HS_MADDR_ic_hs_mar_shift                                             (0)
#define MIS_IC5_HS_MADDR_ic_hs_mar_mask                                              (0x00000007)
#define MIS_IC5_HS_MADDR_ic_hs_mar(data)                                             (0x00000007&((data)<<0))
#define MIS_IC5_HS_MADDR_ic_hs_mar_src(data)                                         ((0x00000007&(data))>>0)
#define MIS_IC5_HS_MADDR_get_ic_hs_mar(data)                                         ((0x00000007&(data))>>0)


#define MIS_IC5_DATA_CMD                                                             0x9801BB10
#define MIS_IC5_DATA_CMD_reg_addr                                                    "0x9801BB10"
#define MIS_IC5_DATA_CMD_reg                                                         0x9801BB10
#define set_MIS_IC5_DATA_CMD_reg(data)   (*((volatile unsigned int*) MIS_IC5_DATA_CMD_reg)=data)
#define get_MIS_IC5_DATA_CMD_reg   (*((volatile unsigned int*) MIS_IC5_DATA_CMD_reg))
#define MIS_IC5_DATA_CMD_inst_adr                                                    "0x00C4"
#define MIS_IC5_DATA_CMD_inst                                                        0x00C4
#define MIS_IC5_DATA_CMD_restart_shift                                               (10)
#define MIS_IC5_DATA_CMD_restart_mask                                                (0x00000400)
#define MIS_IC5_DATA_CMD_restart(data)                                               (0x00000400&((data)<<10))
#define MIS_IC5_DATA_CMD_restart_src(data)                                           ((0x00000400&(data))>>10)
#define MIS_IC5_DATA_CMD_get_restart(data)                                           ((0x00000400&(data))>>10)
#define MIS_IC5_DATA_CMD_stop_shift                                                  (9)
#define MIS_IC5_DATA_CMD_stop_mask                                                   (0x00000200)
#define MIS_IC5_DATA_CMD_stop(data)                                                  (0x00000200&((data)<<9))
#define MIS_IC5_DATA_CMD_stop_src(data)                                              ((0x00000200&(data))>>9)
#define MIS_IC5_DATA_CMD_get_stop(data)                                              ((0x00000200&(data))>>9)
#define MIS_IC5_DATA_CMD_cmd_shift                                                   (8)
#define MIS_IC5_DATA_CMD_cmd_mask                                                    (0x00000100)
#define MIS_IC5_DATA_CMD_cmd(data)                                                   (0x00000100&((data)<<8))
#define MIS_IC5_DATA_CMD_cmd_src(data)                                               ((0x00000100&(data))>>8)
#define MIS_IC5_DATA_CMD_get_cmd(data)                                               ((0x00000100&(data))>>8)
#define MIS_IC5_DATA_CMD_dat_shift                                                   (0)
#define MIS_IC5_DATA_CMD_dat_mask                                                    (0x000000FF)
#define MIS_IC5_DATA_CMD_dat(data)                                                   (0x000000FF&((data)<<0))
#define MIS_IC5_DATA_CMD_dat_src(data)                                               ((0x000000FF&(data))>>0)
#define MIS_IC5_DATA_CMD_get_dat(data)                                               ((0x000000FF&(data))>>0)


#define MIS_IC5_SS_SCL_HCNT                                                          0x9801BB14
#define MIS_IC5_SS_SCL_HCNT_reg_addr                                                 "0x9801BB14"
#define MIS_IC5_SS_SCL_HCNT_reg                                                      0x9801BB14
#define set_MIS_IC5_SS_SCL_HCNT_reg(data)   (*((volatile unsigned int*) MIS_IC5_SS_SCL_HCNT_reg)=data)
#define get_MIS_IC5_SS_SCL_HCNT_reg   (*((volatile unsigned int*) MIS_IC5_SS_SCL_HCNT_reg))
#define MIS_IC5_SS_SCL_HCNT_inst_adr                                                 "0x00C5"
#define MIS_IC5_SS_SCL_HCNT_inst                                                     0x00C5
#define MIS_IC5_SS_SCL_HCNT_ic_ss_scl_hcnt_shift                                     (0)
#define MIS_IC5_SS_SCL_HCNT_ic_ss_scl_hcnt_mask                                      (0x0000FFFF)
#define MIS_IC5_SS_SCL_HCNT_ic_ss_scl_hcnt(data)                                     (0x0000FFFF&((data)<<0))
#define MIS_IC5_SS_SCL_HCNT_ic_ss_scl_hcnt_src(data)                                 ((0x0000FFFF&(data))>>0)
#define MIS_IC5_SS_SCL_HCNT_get_ic_ss_scl_hcnt(data)                                 ((0x0000FFFF&(data))>>0)


#define MIS_IC5_SS_SCL_LCNT                                                          0x9801BB18
#define MIS_IC5_SS_SCL_LCNT_reg_addr                                                 "0x9801BB18"
#define MIS_IC5_SS_SCL_LCNT_reg                                                      0x9801BB18
#define set_MIS_IC5_SS_SCL_LCNT_reg(data)   (*((volatile unsigned int*) MIS_IC5_SS_SCL_LCNT_reg)=data)
#define get_MIS_IC5_SS_SCL_LCNT_reg   (*((volatile unsigned int*) MIS_IC5_SS_SCL_LCNT_reg))
#define MIS_IC5_SS_SCL_LCNT_inst_adr                                                 "0x00C6"
#define MIS_IC5_SS_SCL_LCNT_inst                                                     0x00C6
#define MIS_IC5_SS_SCL_LCNT_ic_ss_scl_lcnt_shift                                     (0)
#define MIS_IC5_SS_SCL_LCNT_ic_ss_scl_lcnt_mask                                      (0x0000FFFF)
#define MIS_IC5_SS_SCL_LCNT_ic_ss_scl_lcnt(data)                                     (0x0000FFFF&((data)<<0))
#define MIS_IC5_SS_SCL_LCNT_ic_ss_scl_lcnt_src(data)                                 ((0x0000FFFF&(data))>>0)
#define MIS_IC5_SS_SCL_LCNT_get_ic_ss_scl_lcnt(data)                                 ((0x0000FFFF&(data))>>0)


#define MIS_IC5_FS_SCL_HCNT                                                          0x9801BB1C
#define MIS_IC5_FS_SCL_HCNT_reg_addr                                                 "0x9801BB1C"
#define MIS_IC5_FS_SCL_HCNT_reg                                                      0x9801BB1C
#define set_MIS_IC5_FS_SCL_HCNT_reg(data)   (*((volatile unsigned int*) MIS_IC5_FS_SCL_HCNT_reg)=data)
#define get_MIS_IC5_FS_SCL_HCNT_reg   (*((volatile unsigned int*) MIS_IC5_FS_SCL_HCNT_reg))
#define MIS_IC5_FS_SCL_HCNT_inst_adr                                                 "0x00C7"
#define MIS_IC5_FS_SCL_HCNT_inst                                                     0x00C7
#define MIS_IC5_FS_SCL_HCNT_ic_fs_scl_hcnt_shift                                     (0)
#define MIS_IC5_FS_SCL_HCNT_ic_fs_scl_hcnt_mask                                      (0x0000FFFF)
#define MIS_IC5_FS_SCL_HCNT_ic_fs_scl_hcnt(data)                                     (0x0000FFFF&((data)<<0))
#define MIS_IC5_FS_SCL_HCNT_ic_fs_scl_hcnt_src(data)                                 ((0x0000FFFF&(data))>>0)
#define MIS_IC5_FS_SCL_HCNT_get_ic_fs_scl_hcnt(data)                                 ((0x0000FFFF&(data))>>0)


#define MIS_IC5_FS_SCL_LCNT                                                          0x9801BB20
#define MIS_IC5_FS_SCL_LCNT_reg_addr                                                 "0x9801BB20"
#define MIS_IC5_FS_SCL_LCNT_reg                                                      0x9801BB20
#define set_MIS_IC5_FS_SCL_LCNT_reg(data)   (*((volatile unsigned int*) MIS_IC5_FS_SCL_LCNT_reg)=data)
#define get_MIS_IC5_FS_SCL_LCNT_reg   (*((volatile unsigned int*) MIS_IC5_FS_SCL_LCNT_reg))
#define MIS_IC5_FS_SCL_LCNT_inst_adr                                                 "0x00C8"
#define MIS_IC5_FS_SCL_LCNT_inst                                                     0x00C8
#define MIS_IC5_FS_SCL_LCNT_ic_fs_scl_lcnt_shift                                     (0)
#define MIS_IC5_FS_SCL_LCNT_ic_fs_scl_lcnt_mask                                      (0x0000FFFF)
#define MIS_IC5_FS_SCL_LCNT_ic_fs_scl_lcnt(data)                                     (0x0000FFFF&((data)<<0))
#define MIS_IC5_FS_SCL_LCNT_ic_fs_scl_lcnt_src(data)                                 ((0x0000FFFF&(data))>>0)
#define MIS_IC5_FS_SCL_LCNT_get_ic_fs_scl_lcnt(data)                                 ((0x0000FFFF&(data))>>0)


#define MIS_IC5_INTR_STAT                                                            0x9801BB2C
#define MIS_IC5_INTR_STAT_reg_addr                                                   "0x9801BB2C"
#define MIS_IC5_INTR_STAT_reg                                                        0x9801BB2C
#define set_MIS_IC5_INTR_STAT_reg(data)   (*((volatile unsigned int*) MIS_IC5_INTR_STAT_reg)=data)
#define get_MIS_IC5_INTR_STAT_reg   (*((volatile unsigned int*) MIS_IC5_INTR_STAT_reg))
#define MIS_IC5_INTR_STAT_inst_adr                                                   "0x00CB"
#define MIS_IC5_INTR_STAT_inst                                                       0x00CB
#define MIS_IC5_INTR_STAT_r_gen_call_shift                                           (11)
#define MIS_IC5_INTR_STAT_r_gen_call_mask                                            (0x00000800)
#define MIS_IC5_INTR_STAT_r_gen_call(data)                                           (0x00000800&((data)<<11))
#define MIS_IC5_INTR_STAT_r_gen_call_src(data)                                       ((0x00000800&(data))>>11)
#define MIS_IC5_INTR_STAT_get_r_gen_call(data)                                       ((0x00000800&(data))>>11)
#define MIS_IC5_INTR_STAT_r_start_det_shift                                          (10)
#define MIS_IC5_INTR_STAT_r_start_det_mask                                           (0x00000400)
#define MIS_IC5_INTR_STAT_r_start_det(data)                                          (0x00000400&((data)<<10))
#define MIS_IC5_INTR_STAT_r_start_det_src(data)                                      ((0x00000400&(data))>>10)
#define MIS_IC5_INTR_STAT_get_r_start_det(data)                                      ((0x00000400&(data))>>10)
#define MIS_IC5_INTR_STAT_r_stop_det_shift                                           (9)
#define MIS_IC5_INTR_STAT_r_stop_det_mask                                            (0x00000200)
#define MIS_IC5_INTR_STAT_r_stop_det(data)                                           (0x00000200&((data)<<9))
#define MIS_IC5_INTR_STAT_r_stop_det_src(data)                                       ((0x00000200&(data))>>9)
#define MIS_IC5_INTR_STAT_get_r_stop_det(data)                                       ((0x00000200&(data))>>9)
#define MIS_IC5_INTR_STAT_r_activity_shift                                           (8)
#define MIS_IC5_INTR_STAT_r_activity_mask                                            (0x00000100)
#define MIS_IC5_INTR_STAT_r_activity(data)                                           (0x00000100&((data)<<8))
#define MIS_IC5_INTR_STAT_r_activity_src(data)                                       ((0x00000100&(data))>>8)
#define MIS_IC5_INTR_STAT_get_r_activity(data)                                       ((0x00000100&(data))>>8)
#define MIS_IC5_INTR_STAT_r_rx_done_shift                                            (7)
#define MIS_IC5_INTR_STAT_r_rx_done_mask                                             (0x00000080)
#define MIS_IC5_INTR_STAT_r_rx_done(data)                                            (0x00000080&((data)<<7))
#define MIS_IC5_INTR_STAT_r_rx_done_src(data)                                        ((0x00000080&(data))>>7)
#define MIS_IC5_INTR_STAT_get_r_rx_done(data)                                        ((0x00000080&(data))>>7)
#define MIS_IC5_INTR_STAT_r_tx_abrt_shift                                            (6)
#define MIS_IC5_INTR_STAT_r_tx_abrt_mask                                             (0x00000040)
#define MIS_IC5_INTR_STAT_r_tx_abrt(data)                                            (0x00000040&((data)<<6))
#define MIS_IC5_INTR_STAT_r_tx_abrt_src(data)                                        ((0x00000040&(data))>>6)
#define MIS_IC5_INTR_STAT_get_r_tx_abrt(data)                                        ((0x00000040&(data))>>6)
#define MIS_IC5_INTR_STAT_r_rd_req_shift                                             (5)
#define MIS_IC5_INTR_STAT_r_rd_req_mask                                              (0x00000020)
#define MIS_IC5_INTR_STAT_r_rd_req(data)                                             (0x00000020&((data)<<5))
#define MIS_IC5_INTR_STAT_r_rd_req_src(data)                                         ((0x00000020&(data))>>5)
#define MIS_IC5_INTR_STAT_get_r_rd_req(data)                                         ((0x00000020&(data))>>5)
#define MIS_IC5_INTR_STAT_r_tx_empty_shift                                           (4)
#define MIS_IC5_INTR_STAT_r_tx_empty_mask                                            (0x00000010)
#define MIS_IC5_INTR_STAT_r_tx_empty(data)                                           (0x00000010&((data)<<4))
#define MIS_IC5_INTR_STAT_r_tx_empty_src(data)                                       ((0x00000010&(data))>>4)
#define MIS_IC5_INTR_STAT_get_r_tx_empty(data)                                       ((0x00000010&(data))>>4)
#define MIS_IC5_INTR_STAT_r_tx_over_shift                                            (3)
#define MIS_IC5_INTR_STAT_r_tx_over_mask                                             (0x00000008)
#define MIS_IC5_INTR_STAT_r_tx_over(data)                                            (0x00000008&((data)<<3))
#define MIS_IC5_INTR_STAT_r_tx_over_src(data)                                        ((0x00000008&(data))>>3)
#define MIS_IC5_INTR_STAT_get_r_tx_over(data)                                        ((0x00000008&(data))>>3)
#define MIS_IC5_INTR_STAT_r_rx_full_shift                                            (2)
#define MIS_IC5_INTR_STAT_r_rx_full_mask                                             (0x00000004)
#define MIS_IC5_INTR_STAT_r_rx_full(data)                                            (0x00000004&((data)<<2))
#define MIS_IC5_INTR_STAT_r_rx_full_src(data)                                        ((0x00000004&(data))>>2)
#define MIS_IC5_INTR_STAT_get_r_rx_full(data)                                        ((0x00000004&(data))>>2)
#define MIS_IC5_INTR_STAT_r_rx_over_shift                                            (1)
#define MIS_IC5_INTR_STAT_r_rx_over_mask                                             (0x00000002)
#define MIS_IC5_INTR_STAT_r_rx_over(data)                                            (0x00000002&((data)<<1))
#define MIS_IC5_INTR_STAT_r_rx_over_src(data)                                        ((0x00000002&(data))>>1)
#define MIS_IC5_INTR_STAT_get_r_rx_over(data)                                        ((0x00000002&(data))>>1)
#define MIS_IC5_INTR_STAT_r_rx_under_shift                                           (0)
#define MIS_IC5_INTR_STAT_r_rx_under_mask                                            (0x00000001)
#define MIS_IC5_INTR_STAT_r_rx_under(data)                                           (0x00000001&((data)<<0))
#define MIS_IC5_INTR_STAT_r_rx_under_src(data)                                       ((0x00000001&(data))>>0)
#define MIS_IC5_INTR_STAT_get_r_rx_under(data)                                       ((0x00000001&(data))>>0)


#define MIS_IC5_INTR_MASK                                                            0x9801BB30
#define MIS_IC5_INTR_MASK_reg_addr                                                   "0x9801BB30"
#define MIS_IC5_INTR_MASK_reg                                                        0x9801BB30
#define set_MIS_IC5_INTR_MASK_reg(data)   (*((volatile unsigned int*) MIS_IC5_INTR_MASK_reg)=data)
#define get_MIS_IC5_INTR_MASK_reg   (*((volatile unsigned int*) MIS_IC5_INTR_MASK_reg))
#define MIS_IC5_INTR_MASK_inst_adr                                                   "0x00CC"
#define MIS_IC5_INTR_MASK_inst                                                       0x00CC
#define MIS_IC5_INTR_MASK_m_gen_call_shift                                           (11)
#define MIS_IC5_INTR_MASK_m_gen_call_mask                                            (0x00000800)
#define MIS_IC5_INTR_MASK_m_gen_call(data)                                           (0x00000800&((data)<<11))
#define MIS_IC5_INTR_MASK_m_gen_call_src(data)                                       ((0x00000800&(data))>>11)
#define MIS_IC5_INTR_MASK_get_m_gen_call(data)                                       ((0x00000800&(data))>>11)
#define MIS_IC5_INTR_MASK_m_start_det_shift                                          (10)
#define MIS_IC5_INTR_MASK_m_start_det_mask                                           (0x00000400)
#define MIS_IC5_INTR_MASK_m_start_det(data)                                          (0x00000400&((data)<<10))
#define MIS_IC5_INTR_MASK_m_start_det_src(data)                                      ((0x00000400&(data))>>10)
#define MIS_IC5_INTR_MASK_get_m_start_det(data)                                      ((0x00000400&(data))>>10)
#define MIS_IC5_INTR_MASK_m_stop_det_shift                                           (9)
#define MIS_IC5_INTR_MASK_m_stop_det_mask                                            (0x00000200)
#define MIS_IC5_INTR_MASK_m_stop_det(data)                                           (0x00000200&((data)<<9))
#define MIS_IC5_INTR_MASK_m_stop_det_src(data)                                       ((0x00000200&(data))>>9)
#define MIS_IC5_INTR_MASK_get_m_stop_det(data)                                       ((0x00000200&(data))>>9)
#define MIS_IC5_INTR_MASK_m_activity_shift                                           (8)
#define MIS_IC5_INTR_MASK_m_activity_mask                                            (0x00000100)
#define MIS_IC5_INTR_MASK_m_activity(data)                                           (0x00000100&((data)<<8))
#define MIS_IC5_INTR_MASK_m_activity_src(data)                                       ((0x00000100&(data))>>8)
#define MIS_IC5_INTR_MASK_get_m_activity(data)                                       ((0x00000100&(data))>>8)
#define MIS_IC5_INTR_MASK_m_rx_done_shift                                            (7)
#define MIS_IC5_INTR_MASK_m_rx_done_mask                                             (0x00000080)
#define MIS_IC5_INTR_MASK_m_rx_done(data)                                            (0x00000080&((data)<<7))
#define MIS_IC5_INTR_MASK_m_rx_done_src(data)                                        ((0x00000080&(data))>>7)
#define MIS_IC5_INTR_MASK_get_m_rx_done(data)                                        ((0x00000080&(data))>>7)
#define MIS_IC5_INTR_MASK_m_tx_abrt_shift                                            (6)
#define MIS_IC5_INTR_MASK_m_tx_abrt_mask                                             (0x00000040)
#define MIS_IC5_INTR_MASK_m_tx_abrt(data)                                            (0x00000040&((data)<<6))
#define MIS_IC5_INTR_MASK_m_tx_abrt_src(data)                                        ((0x00000040&(data))>>6)
#define MIS_IC5_INTR_MASK_get_m_tx_abrt(data)                                        ((0x00000040&(data))>>6)
#define MIS_IC5_INTR_MASK_m_rd_req_shift                                             (5)
#define MIS_IC5_INTR_MASK_m_rd_req_mask                                              (0x00000020)
#define MIS_IC5_INTR_MASK_m_rd_req(data)                                             (0x00000020&((data)<<5))
#define MIS_IC5_INTR_MASK_m_rd_req_src(data)                                         ((0x00000020&(data))>>5)
#define MIS_IC5_INTR_MASK_get_m_rd_req(data)                                         ((0x00000020&(data))>>5)
#define MIS_IC5_INTR_MASK_m_tx_empty_shift                                           (4)
#define MIS_IC5_INTR_MASK_m_tx_empty_mask                                            (0x00000010)
#define MIS_IC5_INTR_MASK_m_tx_empty(data)                                           (0x00000010&((data)<<4))
#define MIS_IC5_INTR_MASK_m_tx_empty_src(data)                                       ((0x00000010&(data))>>4)
#define MIS_IC5_INTR_MASK_get_m_tx_empty(data)                                       ((0x00000010&(data))>>4)
#define MIS_IC5_INTR_MASK_m_tx_over_shift                                            (3)
#define MIS_IC5_INTR_MASK_m_tx_over_mask                                             (0x00000008)
#define MIS_IC5_INTR_MASK_m_tx_over(data)                                            (0x00000008&((data)<<3))
#define MIS_IC5_INTR_MASK_m_tx_over_src(data)                                        ((0x00000008&(data))>>3)
#define MIS_IC5_INTR_MASK_get_m_tx_over(data)                                        ((0x00000008&(data))>>3)
#define MIS_IC5_INTR_MASK_m_rx_full_shift                                            (2)
#define MIS_IC5_INTR_MASK_m_rx_full_mask                                             (0x00000004)
#define MIS_IC5_INTR_MASK_m_rx_full(data)                                            (0x00000004&((data)<<2))
#define MIS_IC5_INTR_MASK_m_rx_full_src(data)                                        ((0x00000004&(data))>>2)
#define MIS_IC5_INTR_MASK_get_m_rx_full(data)                                        ((0x00000004&(data))>>2)
#define MIS_IC5_INTR_MASK_m_rx_over_shift                                            (1)
#define MIS_IC5_INTR_MASK_m_rx_over_mask                                             (0x00000002)
#define MIS_IC5_INTR_MASK_m_rx_over(data)                                            (0x00000002&((data)<<1))
#define MIS_IC5_INTR_MASK_m_rx_over_src(data)                                        ((0x00000002&(data))>>1)
#define MIS_IC5_INTR_MASK_get_m_rx_over(data)                                        ((0x00000002&(data))>>1)
#define MIS_IC5_INTR_MASK_m_rx_under_shift                                           (0)
#define MIS_IC5_INTR_MASK_m_rx_under_mask                                            (0x00000001)
#define MIS_IC5_INTR_MASK_m_rx_under(data)                                           (0x00000001&((data)<<0))
#define MIS_IC5_INTR_MASK_m_rx_under_src(data)                                       ((0x00000001&(data))>>0)
#define MIS_IC5_INTR_MASK_get_m_rx_under(data)                                       ((0x00000001&(data))>>0)


#define MIS_IC5_RAW_INTR_STAT                                                        0x9801BB34
#define MIS_IC5_RAW_INTR_STAT_reg_addr                                               "0x9801BB34"
#define MIS_IC5_RAW_INTR_STAT_reg                                                    0x9801BB34
#define set_MIS_IC5_RAW_INTR_STAT_reg(data)   (*((volatile unsigned int*) MIS_IC5_RAW_INTR_STAT_reg)=data)
#define get_MIS_IC5_RAW_INTR_STAT_reg   (*((volatile unsigned int*) MIS_IC5_RAW_INTR_STAT_reg))
#define MIS_IC5_RAW_INTR_STAT_inst_adr                                               "0x00CD"
#define MIS_IC5_RAW_INTR_STAT_inst                                                   0x00CD
#define MIS_IC5_RAW_INTR_STAT_gen_call_shift                                         (11)
#define MIS_IC5_RAW_INTR_STAT_gen_call_mask                                          (0x00000800)
#define MIS_IC5_RAW_INTR_STAT_gen_call(data)                                         (0x00000800&((data)<<11))
#define MIS_IC5_RAW_INTR_STAT_gen_call_src(data)                                     ((0x00000800&(data))>>11)
#define MIS_IC5_RAW_INTR_STAT_get_gen_call(data)                                     ((0x00000800&(data))>>11)
#define MIS_IC5_RAW_INTR_STAT_start_det_shift                                        (10)
#define MIS_IC5_RAW_INTR_STAT_start_det_mask                                         (0x00000400)
#define MIS_IC5_RAW_INTR_STAT_start_det(data)                                        (0x00000400&((data)<<10))
#define MIS_IC5_RAW_INTR_STAT_start_det_src(data)                                    ((0x00000400&(data))>>10)
#define MIS_IC5_RAW_INTR_STAT_get_start_det(data)                                    ((0x00000400&(data))>>10)
#define MIS_IC5_RAW_INTR_STAT_stop_det_shift                                         (9)
#define MIS_IC5_RAW_INTR_STAT_stop_det_mask                                          (0x00000200)
#define MIS_IC5_RAW_INTR_STAT_stop_det(data)                                         (0x00000200&((data)<<9))
#define MIS_IC5_RAW_INTR_STAT_stop_det_src(data)                                     ((0x00000200&(data))>>9)
#define MIS_IC5_RAW_INTR_STAT_get_stop_det(data)                                     ((0x00000200&(data))>>9)
#define MIS_IC5_RAW_INTR_STAT_activity_shift                                         (8)
#define MIS_IC5_RAW_INTR_STAT_activity_mask                                          (0x00000100)
#define MIS_IC5_RAW_INTR_STAT_activity(data)                                         (0x00000100&((data)<<8))
#define MIS_IC5_RAW_INTR_STAT_activity_src(data)                                     ((0x00000100&(data))>>8)
#define MIS_IC5_RAW_INTR_STAT_get_activity(data)                                     ((0x00000100&(data))>>8)
#define MIS_IC5_RAW_INTR_STAT_rx_done_shift                                          (7)
#define MIS_IC5_RAW_INTR_STAT_rx_done_mask                                           (0x00000080)
#define MIS_IC5_RAW_INTR_STAT_rx_done(data)                                          (0x00000080&((data)<<7))
#define MIS_IC5_RAW_INTR_STAT_rx_done_src(data)                                      ((0x00000080&(data))>>7)
#define MIS_IC5_RAW_INTR_STAT_get_rx_done(data)                                      ((0x00000080&(data))>>7)
#define MIS_IC5_RAW_INTR_STAT_tx_abrt_shift                                          (6)
#define MIS_IC5_RAW_INTR_STAT_tx_abrt_mask                                           (0x00000040)
#define MIS_IC5_RAW_INTR_STAT_tx_abrt(data)                                          (0x00000040&((data)<<6))
#define MIS_IC5_RAW_INTR_STAT_tx_abrt_src(data)                                      ((0x00000040&(data))>>6)
#define MIS_IC5_RAW_INTR_STAT_get_tx_abrt(data)                                      ((0x00000040&(data))>>6)
#define MIS_IC5_RAW_INTR_STAT_rd_req_shift                                           (5)
#define MIS_IC5_RAW_INTR_STAT_rd_req_mask                                            (0x00000020)
#define MIS_IC5_RAW_INTR_STAT_rd_req(data)                                           (0x00000020&((data)<<5))
#define MIS_IC5_RAW_INTR_STAT_rd_req_src(data)                                       ((0x00000020&(data))>>5)
#define MIS_IC5_RAW_INTR_STAT_get_rd_req(data)                                       ((0x00000020&(data))>>5)
#define MIS_IC5_RAW_INTR_STAT_tx_empty_shift                                         (4)
#define MIS_IC5_RAW_INTR_STAT_tx_empty_mask                                          (0x00000010)
#define MIS_IC5_RAW_INTR_STAT_tx_empty(data)                                         (0x00000010&((data)<<4))
#define MIS_IC5_RAW_INTR_STAT_tx_empty_src(data)                                     ((0x00000010&(data))>>4)
#define MIS_IC5_RAW_INTR_STAT_get_tx_empty(data)                                     ((0x00000010&(data))>>4)
#define MIS_IC5_RAW_INTR_STAT_tx_over_shift                                          (3)
#define MIS_IC5_RAW_INTR_STAT_tx_over_mask                                           (0x00000008)
#define MIS_IC5_RAW_INTR_STAT_tx_over(data)                                          (0x00000008&((data)<<3))
#define MIS_IC5_RAW_INTR_STAT_tx_over_src(data)                                      ((0x00000008&(data))>>3)
#define MIS_IC5_RAW_INTR_STAT_get_tx_over(data)                                      ((0x00000008&(data))>>3)
#define MIS_IC5_RAW_INTR_STAT_rx_full_shift                                          (2)
#define MIS_IC5_RAW_INTR_STAT_rx_full_mask                                           (0x00000004)
#define MIS_IC5_RAW_INTR_STAT_rx_full(data)                                          (0x00000004&((data)<<2))
#define MIS_IC5_RAW_INTR_STAT_rx_full_src(data)                                      ((0x00000004&(data))>>2)
#define MIS_IC5_RAW_INTR_STAT_get_rx_full(data)                                      ((0x00000004&(data))>>2)
#define MIS_IC5_RAW_INTR_STAT_rx_over_shift                                          (1)
#define MIS_IC5_RAW_INTR_STAT_rx_over_mask                                           (0x00000002)
#define MIS_IC5_RAW_INTR_STAT_rx_over(data)                                          (0x00000002&((data)<<1))
#define MIS_IC5_RAW_INTR_STAT_rx_over_src(data)                                      ((0x00000002&(data))>>1)
#define MIS_IC5_RAW_INTR_STAT_get_rx_over(data)                                      ((0x00000002&(data))>>1)
#define MIS_IC5_RAW_INTR_STAT_rx_under_shift                                         (0)
#define MIS_IC5_RAW_INTR_STAT_rx_under_mask                                          (0x00000001)
#define MIS_IC5_RAW_INTR_STAT_rx_under(data)                                         (0x00000001&((data)<<0))
#define MIS_IC5_RAW_INTR_STAT_rx_under_src(data)                                     ((0x00000001&(data))>>0)
#define MIS_IC5_RAW_INTR_STAT_get_rx_under(data)                                     ((0x00000001&(data))>>0)


#define MIS_IC5_RX_TL                                                                0x9801BB38
#define MIS_IC5_RX_TL_reg_addr                                                       "0x9801BB38"
#define MIS_IC5_RX_TL_reg                                                            0x9801BB38
#define set_MIS_IC5_RX_TL_reg(data)   (*((volatile unsigned int*) MIS_IC5_RX_TL_reg)=data)
#define get_MIS_IC5_RX_TL_reg   (*((volatile unsigned int*) MIS_IC5_RX_TL_reg))
#define MIS_IC5_RX_TL_inst_adr                                                       "0x00CE"
#define MIS_IC5_RX_TL_inst                                                           0x00CE
#define MIS_IC5_RX_TL_rx_tl_shift                                                    (0)
#define MIS_IC5_RX_TL_rx_tl_mask                                                     (0x000000FF)
#define MIS_IC5_RX_TL_rx_tl(data)                                                    (0x000000FF&((data)<<0))
#define MIS_IC5_RX_TL_rx_tl_src(data)                                                ((0x000000FF&(data))>>0)
#define MIS_IC5_RX_TL_get_rx_tl(data)                                                ((0x000000FF&(data))>>0)


#define MIS_IC5_TX_TL                                                                0x9801BB3C
#define MIS_IC5_TX_TL_reg_addr                                                       "0x9801BB3C"
#define MIS_IC5_TX_TL_reg                                                            0x9801BB3C
#define set_MIS_IC5_TX_TL_reg(data)   (*((volatile unsigned int*) MIS_IC5_TX_TL_reg)=data)
#define get_MIS_IC5_TX_TL_reg   (*((volatile unsigned int*) MIS_IC5_TX_TL_reg))
#define MIS_IC5_TX_TL_inst_adr                                                       "0x00CF"
#define MIS_IC5_TX_TL_inst                                                           0x00CF
#define MIS_IC5_TX_TL_tx_tl_shift                                                    (0)
#define MIS_IC5_TX_TL_tx_tl_mask                                                     (0x000000FF)
#define MIS_IC5_TX_TL_tx_tl(data)                                                    (0x000000FF&((data)<<0))
#define MIS_IC5_TX_TL_tx_tl_src(data)                                                ((0x000000FF&(data))>>0)
#define MIS_IC5_TX_TL_get_tx_tl(data)                                                ((0x000000FF&(data))>>0)


#define MIS_IC5_CLR_INTR                                                             0x9801BB40
#define MIS_IC5_CLR_INTR_reg_addr                                                    "0x9801BB40"
#define MIS_IC5_CLR_INTR_reg                                                         0x9801BB40
#define set_MIS_IC5_CLR_INTR_reg(data)   (*((volatile unsigned int*) MIS_IC5_CLR_INTR_reg)=data)
#define get_MIS_IC5_CLR_INTR_reg   (*((volatile unsigned int*) MIS_IC5_CLR_INTR_reg))
#define MIS_IC5_CLR_INTR_inst_adr                                                    "0x00D0"
#define MIS_IC5_CLR_INTR_inst                                                        0x00D0
#define MIS_IC5_CLR_INTR_clr_intr_shift                                              (0)
#define MIS_IC5_CLR_INTR_clr_intr_mask                                               (0x00000001)
#define MIS_IC5_CLR_INTR_clr_intr(data)                                              (0x00000001&((data)<<0))
#define MIS_IC5_CLR_INTR_clr_intr_src(data)                                          ((0x00000001&(data))>>0)
#define MIS_IC5_CLR_INTR_get_clr_intr(data)                                          ((0x00000001&(data))>>0)


#define MIS_IC5_CLR_RX_UNDER                                                         0x9801BB44
#define MIS_IC5_CLR_RX_UNDER_reg_addr                                                "0x9801BB44"
#define MIS_IC5_CLR_RX_UNDER_reg                                                     0x9801BB44
#define set_MIS_IC5_CLR_RX_UNDER_reg(data)   (*((volatile unsigned int*) MIS_IC5_CLR_RX_UNDER_reg)=data)
#define get_MIS_IC5_CLR_RX_UNDER_reg   (*((volatile unsigned int*) MIS_IC5_CLR_RX_UNDER_reg))
#define MIS_IC5_CLR_RX_UNDER_inst_adr                                                "0x00D1"
#define MIS_IC5_CLR_RX_UNDER_inst                                                    0x00D1
#define MIS_IC5_CLR_RX_UNDER_clr_rx_under_shift                                      (0)
#define MIS_IC5_CLR_RX_UNDER_clr_rx_under_mask                                       (0x00000001)
#define MIS_IC5_CLR_RX_UNDER_clr_rx_under(data)                                      (0x00000001&((data)<<0))
#define MIS_IC5_CLR_RX_UNDER_clr_rx_under_src(data)                                  ((0x00000001&(data))>>0)
#define MIS_IC5_CLR_RX_UNDER_get_clr_rx_under(data)                                  ((0x00000001&(data))>>0)


#define MIS_IC5_CLR_RX_OVER                                                          0x9801BB48
#define MIS_IC5_CLR_RX_OVER_reg_addr                                                 "0x9801BB48"
#define MIS_IC5_CLR_RX_OVER_reg                                                      0x9801BB48
#define set_MIS_IC5_CLR_RX_OVER_reg(data)   (*((volatile unsigned int*) MIS_IC5_CLR_RX_OVER_reg)=data)
#define get_MIS_IC5_CLR_RX_OVER_reg   (*((volatile unsigned int*) MIS_IC5_CLR_RX_OVER_reg))
#define MIS_IC5_CLR_RX_OVER_inst_adr                                                 "0x00D2"
#define MIS_IC5_CLR_RX_OVER_inst                                                     0x00D2
#define MIS_IC5_CLR_RX_OVER_clr_rx_over_shift                                        (0)
#define MIS_IC5_CLR_RX_OVER_clr_rx_over_mask                                         (0x00000001)
#define MIS_IC5_CLR_RX_OVER_clr_rx_over(data)                                        (0x00000001&((data)<<0))
#define MIS_IC5_CLR_RX_OVER_clr_rx_over_src(data)                                    ((0x00000001&(data))>>0)
#define MIS_IC5_CLR_RX_OVER_get_clr_rx_over(data)                                    ((0x00000001&(data))>>0)


#define MIS_IC5_CLR_TX_OVER                                                          0x9801BB4C
#define MIS_IC5_CLR_TX_OVER_reg_addr                                                 "0x9801BB4C"
#define MIS_IC5_CLR_TX_OVER_reg                                                      0x9801BB4C
#define set_MIS_IC5_CLR_TX_OVER_reg(data)   (*((volatile unsigned int*) MIS_IC5_CLR_TX_OVER_reg)=data)
#define get_MIS_IC5_CLR_TX_OVER_reg   (*((volatile unsigned int*) MIS_IC5_CLR_TX_OVER_reg))
#define MIS_IC5_CLR_TX_OVER_inst_adr                                                 "0x00D3"
#define MIS_IC5_CLR_TX_OVER_inst                                                     0x00D3
#define MIS_IC5_CLR_TX_OVER_clr_tx_over_shift                                        (0)
#define MIS_IC5_CLR_TX_OVER_clr_tx_over_mask                                         (0x00000001)
#define MIS_IC5_CLR_TX_OVER_clr_tx_over(data)                                        (0x00000001&((data)<<0))
#define MIS_IC5_CLR_TX_OVER_clr_tx_over_src(data)                                    ((0x00000001&(data))>>0)
#define MIS_IC5_CLR_TX_OVER_get_clr_tx_over(data)                                    ((0x00000001&(data))>>0)


#define MIS_IC5_CLR_RD_REQ                                                           0x9801BB50
#define MIS_IC5_CLR_RD_REQ_reg_addr                                                  "0x9801BB50"
#define MIS_IC5_CLR_RD_REQ_reg                                                       0x9801BB50
#define set_MIS_IC5_CLR_RD_REQ_reg(data)   (*((volatile unsigned int*) MIS_IC5_CLR_RD_REQ_reg)=data)
#define get_MIS_IC5_CLR_RD_REQ_reg   (*((volatile unsigned int*) MIS_IC5_CLR_RD_REQ_reg))
#define MIS_IC5_CLR_RD_REQ_inst_adr                                                  "0x00D4"
#define MIS_IC5_CLR_RD_REQ_inst                                                      0x00D4
#define MIS_IC5_CLR_RD_REQ_clr_rd_req_shift                                          (0)
#define MIS_IC5_CLR_RD_REQ_clr_rd_req_mask                                           (0x00000001)
#define MIS_IC5_CLR_RD_REQ_clr_rd_req(data)                                          (0x00000001&((data)<<0))
#define MIS_IC5_CLR_RD_REQ_clr_rd_req_src(data)                                      ((0x00000001&(data))>>0)
#define MIS_IC5_CLR_RD_REQ_get_clr_rd_req(data)                                      ((0x00000001&(data))>>0)


#define MIS_IC5_CLR_TX_ABRT                                                          0x9801BB54
#define MIS_IC5_CLR_TX_ABRT_reg_addr                                                 "0x9801BB54"
#define MIS_IC5_CLR_TX_ABRT_reg                                                      0x9801BB54
#define set_MIS_IC5_CLR_TX_ABRT_reg(data)   (*((volatile unsigned int*) MIS_IC5_CLR_TX_ABRT_reg)=data)
#define get_MIS_IC5_CLR_TX_ABRT_reg   (*((volatile unsigned int*) MIS_IC5_CLR_TX_ABRT_reg))
#define MIS_IC5_CLR_TX_ABRT_inst_adr                                                 "0x00D5"
#define MIS_IC5_CLR_TX_ABRT_inst                                                     0x00D5
#define MIS_IC5_CLR_TX_ABRT_clr_tx_abrt_shift                                        (0)
#define MIS_IC5_CLR_TX_ABRT_clr_tx_abrt_mask                                         (0x00000001)
#define MIS_IC5_CLR_TX_ABRT_clr_tx_abrt(data)                                        (0x00000001&((data)<<0))
#define MIS_IC5_CLR_TX_ABRT_clr_tx_abrt_src(data)                                    ((0x00000001&(data))>>0)
#define MIS_IC5_CLR_TX_ABRT_get_clr_tx_abrt(data)                                    ((0x00000001&(data))>>0)


#define MIS_IC5_CLR_RX_DONE                                                          0x9801BB58
#define MIS_IC5_CLR_RX_DONE_reg_addr                                                 "0x9801BB58"
#define MIS_IC5_CLR_RX_DONE_reg                                                      0x9801BB58
#define set_MIS_IC5_CLR_RX_DONE_reg(data)   (*((volatile unsigned int*) MIS_IC5_CLR_RX_DONE_reg)=data)
#define get_MIS_IC5_CLR_RX_DONE_reg   (*((volatile unsigned int*) MIS_IC5_CLR_RX_DONE_reg))
#define MIS_IC5_CLR_RX_DONE_inst_adr                                                 "0x00D6"
#define MIS_IC5_CLR_RX_DONE_inst                                                     0x00D6
#define MIS_IC5_CLR_RX_DONE_clr_rx_done_shift                                        (0)
#define MIS_IC5_CLR_RX_DONE_clr_rx_done_mask                                         (0x00000001)
#define MIS_IC5_CLR_RX_DONE_clr_rx_done(data)                                        (0x00000001&((data)<<0))
#define MIS_IC5_CLR_RX_DONE_clr_rx_done_src(data)                                    ((0x00000001&(data))>>0)
#define MIS_IC5_CLR_RX_DONE_get_clr_rx_done(data)                                    ((0x00000001&(data))>>0)


#define MIS_IC5_CLR_ACTIVITY                                                         0x9801BB5C
#define MIS_IC5_CLR_ACTIVITY_reg_addr                                                "0x9801BB5C"
#define MIS_IC5_CLR_ACTIVITY_reg                                                     0x9801BB5C
#define set_MIS_IC5_CLR_ACTIVITY_reg(data)   (*((volatile unsigned int*) MIS_IC5_CLR_ACTIVITY_reg)=data)
#define get_MIS_IC5_CLR_ACTIVITY_reg   (*((volatile unsigned int*) MIS_IC5_CLR_ACTIVITY_reg))
#define MIS_IC5_CLR_ACTIVITY_inst_adr                                                "0x00D7"
#define MIS_IC5_CLR_ACTIVITY_inst                                                    0x00D7
#define MIS_IC5_CLR_ACTIVITY_clr_activity_shift                                      (0)
#define MIS_IC5_CLR_ACTIVITY_clr_activity_mask                                       (0x00000001)
#define MIS_IC5_CLR_ACTIVITY_clr_activity(data)                                      (0x00000001&((data)<<0))
#define MIS_IC5_CLR_ACTIVITY_clr_activity_src(data)                                  ((0x00000001&(data))>>0)
#define MIS_IC5_CLR_ACTIVITY_get_clr_activity(data)                                  ((0x00000001&(data))>>0)


#define MIS_IC5_CLR_STOP_DET                                                         0x9801BB60
#define MIS_IC5_CLR_STOP_DET_reg_addr                                                "0x9801BB60"
#define MIS_IC5_CLR_STOP_DET_reg                                                     0x9801BB60
#define set_MIS_IC5_CLR_STOP_DET_reg(data)   (*((volatile unsigned int*) MIS_IC5_CLR_STOP_DET_reg)=data)
#define get_MIS_IC5_CLR_STOP_DET_reg   (*((volatile unsigned int*) MIS_IC5_CLR_STOP_DET_reg))
#define MIS_IC5_CLR_STOP_DET_inst_adr                                                "0x00D8"
#define MIS_IC5_CLR_STOP_DET_inst                                                    0x00D8
#define MIS_IC5_CLR_STOP_DET_clr_stop_det_shift                                      (0)
#define MIS_IC5_CLR_STOP_DET_clr_stop_det_mask                                       (0x00000001)
#define MIS_IC5_CLR_STOP_DET_clr_stop_det(data)                                      (0x00000001&((data)<<0))
#define MIS_IC5_CLR_STOP_DET_clr_stop_det_src(data)                                  ((0x00000001&(data))>>0)
#define MIS_IC5_CLR_STOP_DET_get_clr_stop_det(data)                                  ((0x00000001&(data))>>0)


#define MIS_IC5_CLR_START_DET                                                        0x9801BB64
#define MIS_IC5_CLR_START_DET_reg_addr                                               "0x9801BB64"
#define MIS_IC5_CLR_START_DET_reg                                                    0x9801BB64
#define set_MIS_IC5_CLR_START_DET_reg(data)   (*((volatile unsigned int*) MIS_IC5_CLR_START_DET_reg)=data)
#define get_MIS_IC5_CLR_START_DET_reg   (*((volatile unsigned int*) MIS_IC5_CLR_START_DET_reg))
#define MIS_IC5_CLR_START_DET_inst_adr                                               "0x00D9"
#define MIS_IC5_CLR_START_DET_inst                                                   0x00D9
#define MIS_IC5_CLR_START_DET_clr_start_det_shift                                    (0)
#define MIS_IC5_CLR_START_DET_clr_start_det_mask                                     (0x00000001)
#define MIS_IC5_CLR_START_DET_clr_start_det(data)                                    (0x00000001&((data)<<0))
#define MIS_IC5_CLR_START_DET_clr_start_det_src(data)                                ((0x00000001&(data))>>0)
#define MIS_IC5_CLR_START_DET_get_clr_start_det(data)                                ((0x00000001&(data))>>0)


#define MIS_IC5_CLR_GEN_CALL                                                         0x9801BB68
#define MIS_IC5_CLR_GEN_CALL_reg_addr                                                "0x9801BB68"
#define MIS_IC5_CLR_GEN_CALL_reg                                                     0x9801BB68
#define set_MIS_IC5_CLR_GEN_CALL_reg(data)   (*((volatile unsigned int*) MIS_IC5_CLR_GEN_CALL_reg)=data)
#define get_MIS_IC5_CLR_GEN_CALL_reg   (*((volatile unsigned int*) MIS_IC5_CLR_GEN_CALL_reg))
#define MIS_IC5_CLR_GEN_CALL_inst_adr                                                "0x00DA"
#define MIS_IC5_CLR_GEN_CALL_inst                                                    0x00DA
#define MIS_IC5_CLR_GEN_CALL_clr_gen_call_shift                                      (0)
#define MIS_IC5_CLR_GEN_CALL_clr_gen_call_mask                                       (0x00000001)
#define MIS_IC5_CLR_GEN_CALL_clr_gen_call(data)                                      (0x00000001&((data)<<0))
#define MIS_IC5_CLR_GEN_CALL_clr_gen_call_src(data)                                  ((0x00000001&(data))>>0)
#define MIS_IC5_CLR_GEN_CALL_get_clr_gen_call(data)                                  ((0x00000001&(data))>>0)


#define MIS_IC5_ENABLE                                                               0x9801BB6C
#define MIS_IC5_ENABLE_reg_addr                                                      "0x9801BB6C"
#define MIS_IC5_ENABLE_reg                                                           0x9801BB6C
#define set_MIS_IC5_ENABLE_reg(data)   (*((volatile unsigned int*) MIS_IC5_ENABLE_reg)=data)
#define get_MIS_IC5_ENABLE_reg   (*((volatile unsigned int*) MIS_IC5_ENABLE_reg))
#define MIS_IC5_ENABLE_inst_adr                                                      "0x00DB"
#define MIS_IC5_ENABLE_inst                                                          0x00DB
#define MIS_IC5_ENABLE_enable_shift                                                  (0)
#define MIS_IC5_ENABLE_enable_mask                                                   (0x00000001)
#define MIS_IC5_ENABLE_enable(data)                                                  (0x00000001&((data)<<0))
#define MIS_IC5_ENABLE_enable_src(data)                                              ((0x00000001&(data))>>0)
#define MIS_IC5_ENABLE_get_enable(data)                                              ((0x00000001&(data))>>0)


#define MIS_IC5_STATUS                                                               0x9801BB70
#define MIS_IC5_STATUS_reg_addr                                                      "0x9801BB70"
#define MIS_IC5_STATUS_reg                                                           0x9801BB70
#define set_MIS_IC5_STATUS_reg(data)   (*((volatile unsigned int*) MIS_IC5_STATUS_reg)=data)
#define get_MIS_IC5_STATUS_reg   (*((volatile unsigned int*) MIS_IC5_STATUS_reg))
#define MIS_IC5_STATUS_inst_adr                                                      "0x00DC"
#define MIS_IC5_STATUS_inst                                                          0x00DC
#define MIS_IC5_STATUS_slv_activity_shift                                            (6)
#define MIS_IC5_STATUS_slv_activity_mask                                             (0x00000040)
#define MIS_IC5_STATUS_slv_activity(data)                                            (0x00000040&((data)<<6))
#define MIS_IC5_STATUS_slv_activity_src(data)                                        ((0x00000040&(data))>>6)
#define MIS_IC5_STATUS_get_slv_activity(data)                                        ((0x00000040&(data))>>6)
#define MIS_IC5_STATUS_mst_activity_shift                                            (5)
#define MIS_IC5_STATUS_mst_activity_mask                                             (0x00000020)
#define MIS_IC5_STATUS_mst_activity(data)                                            (0x00000020&((data)<<5))
#define MIS_IC5_STATUS_mst_activity_src(data)                                        ((0x00000020&(data))>>5)
#define MIS_IC5_STATUS_get_mst_activity(data)                                        ((0x00000020&(data))>>5)
#define MIS_IC5_STATUS_rff_shift                                                     (4)
#define MIS_IC5_STATUS_rff_mask                                                      (0x00000010)
#define MIS_IC5_STATUS_rff(data)                                                     (0x00000010&((data)<<4))
#define MIS_IC5_STATUS_rff_src(data)                                                 ((0x00000010&(data))>>4)
#define MIS_IC5_STATUS_get_rff(data)                                                 ((0x00000010&(data))>>4)
#define MIS_IC5_STATUS_rfne_shift                                                    (3)
#define MIS_IC5_STATUS_rfne_mask                                                     (0x00000008)
#define MIS_IC5_STATUS_rfne(data)                                                    (0x00000008&((data)<<3))
#define MIS_IC5_STATUS_rfne_src(data)                                                ((0x00000008&(data))>>3)
#define MIS_IC5_STATUS_get_rfne(data)                                                ((0x00000008&(data))>>3)
#define MIS_IC5_STATUS_tfe_shift                                                     (2)
#define MIS_IC5_STATUS_tfe_mask                                                      (0x00000004)
#define MIS_IC5_STATUS_tfe(data)                                                     (0x00000004&((data)<<2))
#define MIS_IC5_STATUS_tfe_src(data)                                                 ((0x00000004&(data))>>2)
#define MIS_IC5_STATUS_get_tfe(data)                                                 ((0x00000004&(data))>>2)
#define MIS_IC5_STATUS_tfnf_shift                                                    (1)
#define MIS_IC5_STATUS_tfnf_mask                                                     (0x00000002)
#define MIS_IC5_STATUS_tfnf(data)                                                    (0x00000002&((data)<<1))
#define MIS_IC5_STATUS_tfnf_src(data)                                                ((0x00000002&(data))>>1)
#define MIS_IC5_STATUS_get_tfnf(data)                                                ((0x00000002&(data))>>1)
#define MIS_IC5_STATUS_activity_shift                                                (0)
#define MIS_IC5_STATUS_activity_mask                                                 (0x00000001)
#define MIS_IC5_STATUS_activity(data)                                                (0x00000001&((data)<<0))
#define MIS_IC5_STATUS_activity_src(data)                                            ((0x00000001&(data))>>0)
#define MIS_IC5_STATUS_get_activity(data)                                            ((0x00000001&(data))>>0)


#define MIS_IC5_TXFLR                                                                0x9801BB74
#define MIS_IC5_TXFLR_reg_addr                                                       "0x9801BB74"
#define MIS_IC5_TXFLR_reg                                                            0x9801BB74
#define set_MIS_IC5_TXFLR_reg(data)   (*((volatile unsigned int*) MIS_IC5_TXFLR_reg)=data)
#define get_MIS_IC5_TXFLR_reg   (*((volatile unsigned int*) MIS_IC5_TXFLR_reg))
#define MIS_IC5_TXFLR_inst_adr                                                       "0x00DD"
#define MIS_IC5_TXFLR_inst                                                           0x00DD
#define MIS_IC5_TXFLR_txflr_shift                                                    (0)
#define MIS_IC5_TXFLR_txflr_mask                                                     (0x0000000F)
#define MIS_IC5_TXFLR_txflr(data)                                                    (0x0000000F&((data)<<0))
#define MIS_IC5_TXFLR_txflr_src(data)                                                ((0x0000000F&(data))>>0)
#define MIS_IC5_TXFLR_get_txflr(data)                                                ((0x0000000F&(data))>>0)


#define MIS_IC5_RXFLR                                                                0x9801BB78
#define MIS_IC5_RXFLR_reg_addr                                                       "0x9801BB78"
#define MIS_IC5_RXFLR_reg                                                            0x9801BB78
#define set_MIS_IC5_RXFLR_reg(data)   (*((volatile unsigned int*) MIS_IC5_RXFLR_reg)=data)
#define get_MIS_IC5_RXFLR_reg   (*((volatile unsigned int*) MIS_IC5_RXFLR_reg))
#define MIS_IC5_RXFLR_inst_adr                                                       "0x00DE"
#define MIS_IC5_RXFLR_inst                                                           0x00DE
#define MIS_IC5_RXFLR_rxflr_shift                                                    (0)
#define MIS_IC5_RXFLR_rxflr_mask                                                     (0x0000000F)
#define MIS_IC5_RXFLR_rxflr(data)                                                    (0x0000000F&((data)<<0))
#define MIS_IC5_RXFLR_rxflr_src(data)                                                ((0x0000000F&(data))>>0)
#define MIS_IC5_RXFLR_get_rxflr(data)                                                ((0x0000000F&(data))>>0)


#define MIS_IC5_SDA_HOLD                                                             0x9801BB7C
#define MIS_IC5_SDA_HOLD_reg_addr                                                    "0x9801BB7C"
#define MIS_IC5_SDA_HOLD_reg                                                         0x9801BB7C
#define set_MIS_IC5_SDA_HOLD_reg(data)   (*((volatile unsigned int*) MIS_IC5_SDA_HOLD_reg)=data)
#define get_MIS_IC5_SDA_HOLD_reg   (*((volatile unsigned int*) MIS_IC5_SDA_HOLD_reg))
#define MIS_IC5_SDA_HOLD_inst_adr                                                    "0x00DF"
#define MIS_IC5_SDA_HOLD_inst                                                        0x00DF
#define MIS_IC5_SDA_HOLD_sda_hold_shift                                              (0)
#define MIS_IC5_SDA_HOLD_sda_hold_mask                                               (0x0000FFFF)
#define MIS_IC5_SDA_HOLD_sda_hold(data)                                              (0x0000FFFF&((data)<<0))
#define MIS_IC5_SDA_HOLD_sda_hold_src(data)                                          ((0x0000FFFF&(data))>>0)
#define MIS_IC5_SDA_HOLD_get_sda_hold(data)                                          ((0x0000FFFF&(data))>>0)


#define MIS_IC5_TX_ABRT_SOURCE                                                       0x9801BB80
#define MIS_IC5_TX_ABRT_SOURCE_reg_addr                                              "0x9801BB80"
#define MIS_IC5_TX_ABRT_SOURCE_reg                                                   0x9801BB80
#define set_MIS_IC5_TX_ABRT_SOURCE_reg(data)   (*((volatile unsigned int*) MIS_IC5_TX_ABRT_SOURCE_reg)=data)
#define get_MIS_IC5_TX_ABRT_SOURCE_reg   (*((volatile unsigned int*) MIS_IC5_TX_ABRT_SOURCE_reg))
#define MIS_IC5_TX_ABRT_SOURCE_inst_adr                                              "0x00E0"
#define MIS_IC5_TX_ABRT_SOURCE_inst                                                  0x00E0
#define MIS_IC5_TX_ABRT_SOURCE_abrt_slvrd_intx_shift                                 (15)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_slvrd_intx_mask                                  (0x00008000)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_slvrd_intx(data)                                 (0x00008000&((data)<<15))
#define MIS_IC5_TX_ABRT_SOURCE_abrt_slvrd_intx_src(data)                             ((0x00008000&(data))>>15)
#define MIS_IC5_TX_ABRT_SOURCE_get_abrt_slvrd_intx(data)                             ((0x00008000&(data))>>15)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_slv_arblost_shift                                (14)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_slv_arblost_mask                                 (0x00004000)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_slv_arblost(data)                                (0x00004000&((data)<<14))
#define MIS_IC5_TX_ABRT_SOURCE_abrt_slv_arblost_src(data)                            ((0x00004000&(data))>>14)
#define MIS_IC5_TX_ABRT_SOURCE_get_abrt_slv_arblost(data)                            ((0x00004000&(data))>>14)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_slvflush_txfifo_shift                            (13)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_slvflush_txfifo_mask                             (0x00002000)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_slvflush_txfifo(data)                            (0x00002000&((data)<<13))
#define MIS_IC5_TX_ABRT_SOURCE_abrt_slvflush_txfifo_src(data)                        ((0x00002000&(data))>>13)
#define MIS_IC5_TX_ABRT_SOURCE_get_abrt_slvflush_txfifo(data)                        ((0x00002000&(data))>>13)
#define MIS_IC5_TX_ABRT_SOURCE_arb_lost_shift                                        (12)
#define MIS_IC5_TX_ABRT_SOURCE_arb_lost_mask                                         (0x00001000)
#define MIS_IC5_TX_ABRT_SOURCE_arb_lost(data)                                        (0x00001000&((data)<<12))
#define MIS_IC5_TX_ABRT_SOURCE_arb_lost_src(data)                                    ((0x00001000&(data))>>12)
#define MIS_IC5_TX_ABRT_SOURCE_get_arb_lost(data)                                    ((0x00001000&(data))>>12)
#define MIS_IC5_TX_ABRT_SOURCE_arb_master_dis_shift                                  (11)
#define MIS_IC5_TX_ABRT_SOURCE_arb_master_dis_mask                                   (0x00000800)
#define MIS_IC5_TX_ABRT_SOURCE_arb_master_dis(data)                                  (0x00000800&((data)<<11))
#define MIS_IC5_TX_ABRT_SOURCE_arb_master_dis_src(data)                              ((0x00000800&(data))>>11)
#define MIS_IC5_TX_ABRT_SOURCE_get_arb_master_dis(data)                              ((0x00000800&(data))>>11)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_10b_rd_norstrt_shift                             (10)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_10b_rd_norstrt_mask                              (0x00000400)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_10b_rd_norstrt(data)                             (0x00000400&((data)<<10))
#define MIS_IC5_TX_ABRT_SOURCE_abrt_10b_rd_norstrt_src(data)                         ((0x00000400&(data))>>10)
#define MIS_IC5_TX_ABRT_SOURCE_get_abrt_10b_rd_norstrt(data)                         ((0x00000400&(data))>>10)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_sbyte_norstrt_shift                              (9)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_sbyte_norstrt_mask                               (0x00000200)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_sbyte_norstrt(data)                              (0x00000200&((data)<<9))
#define MIS_IC5_TX_ABRT_SOURCE_abrt_sbyte_norstrt_src(data)                          ((0x00000200&(data))>>9)
#define MIS_IC5_TX_ABRT_SOURCE_get_abrt_sbyte_norstrt(data)                          ((0x00000200&(data))>>9)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_hs_norstrt_shift                                 (8)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_hs_norstrt_mask                                  (0x00000100)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_hs_norstrt(data)                                 (0x00000100&((data)<<8))
#define MIS_IC5_TX_ABRT_SOURCE_abrt_hs_norstrt_src(data)                             ((0x00000100&(data))>>8)
#define MIS_IC5_TX_ABRT_SOURCE_get_abrt_hs_norstrt(data)                             ((0x00000100&(data))>>8)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_sbyte_ackdet_shift                               (7)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_sbyte_ackdet_mask                                (0x00000080)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_sbyte_ackdet(data)                               (0x00000080&((data)<<7))
#define MIS_IC5_TX_ABRT_SOURCE_abrt_sbyte_ackdet_src(data)                           ((0x00000080&(data))>>7)
#define MIS_IC5_TX_ABRT_SOURCE_get_abrt_sbyte_ackdet(data)                           ((0x00000080&(data))>>7)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_hs_ackdet_shift                                  (6)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_hs_ackdet_mask                                   (0x00000040)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_hs_ackdet(data)                                  (0x00000040&((data)<<6))
#define MIS_IC5_TX_ABRT_SOURCE_abrt_hs_ackdet_src(data)                              ((0x00000040&(data))>>6)
#define MIS_IC5_TX_ABRT_SOURCE_get_abrt_hs_ackdet(data)                              ((0x00000040&(data))>>6)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_gcall_read_shift                                 (5)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_gcall_read_mask                                  (0x00000020)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_gcall_read(data)                                 (0x00000020&((data)<<5))
#define MIS_IC5_TX_ABRT_SOURCE_abrt_gcall_read_src(data)                             ((0x00000020&(data))>>5)
#define MIS_IC5_TX_ABRT_SOURCE_get_abrt_gcall_read(data)                             ((0x00000020&(data))>>5)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_gcall_noack_shift                                (4)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_gcall_noack_mask                                 (0x00000010)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_gcall_noack(data)                                (0x00000010&((data)<<4))
#define MIS_IC5_TX_ABRT_SOURCE_abrt_gcall_noack_src(data)                            ((0x00000010&(data))>>4)
#define MIS_IC5_TX_ABRT_SOURCE_get_abrt_gcall_noack(data)                            ((0x00000010&(data))>>4)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_txdata_noack_shift                               (3)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_txdata_noack_mask                                (0x00000008)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_txdata_noack(data)                               (0x00000008&((data)<<3))
#define MIS_IC5_TX_ABRT_SOURCE_abrt_txdata_noack_src(data)                           ((0x00000008&(data))>>3)
#define MIS_IC5_TX_ABRT_SOURCE_get_abrt_txdata_noack(data)                           ((0x00000008&(data))>>3)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_10addr2_noack_shift                              (2)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_10addr2_noack_mask                               (0x00000004)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_10addr2_noack(data)                              (0x00000004&((data)<<2))
#define MIS_IC5_TX_ABRT_SOURCE_abrt_10addr2_noack_src(data)                          ((0x00000004&(data))>>2)
#define MIS_IC5_TX_ABRT_SOURCE_get_abrt_10addr2_noack(data)                          ((0x00000004&(data))>>2)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_10addr1_noack_shift                              (1)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_10addr1_noack_mask                               (0x00000002)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_10addr1_noack(data)                              (0x00000002&((data)<<1))
#define MIS_IC5_TX_ABRT_SOURCE_abrt_10addr1_noack_src(data)                          ((0x00000002&(data))>>1)
#define MIS_IC5_TX_ABRT_SOURCE_get_abrt_10addr1_noack(data)                          ((0x00000002&(data))>>1)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_7b_addr_noack_shift                              (0)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_7b_addr_noack_mask                               (0x00000001)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_7b_addr_noack(data)                              (0x00000001&((data)<<0))
#define MIS_IC5_TX_ABRT_SOURCE_abrt_7b_addr_noack_src(data)                          ((0x00000001&(data))>>0)
#define MIS_IC5_TX_ABRT_SOURCE_get_abrt_7b_addr_noack(data)                          ((0x00000001&(data))>>0)


#define MIS_IC5_SLV_DATA_NACK_ONLY                                                   0x9801BB84
#define MIS_IC5_SLV_DATA_NACK_ONLY_reg_addr                                          "0x9801BB84"
#define MIS_IC5_SLV_DATA_NACK_ONLY_reg                                               0x9801BB84
#define set_MIS_IC5_SLV_DATA_NACK_ONLY_reg(data)   (*((volatile unsigned int*) MIS_IC5_SLV_DATA_NACK_ONLY_reg)=data)
#define get_MIS_IC5_SLV_DATA_NACK_ONLY_reg   (*((volatile unsigned int*) MIS_IC5_SLV_DATA_NACK_ONLY_reg))
#define MIS_IC5_SLV_DATA_NACK_ONLY_inst_adr                                          "0x00E1"
#define MIS_IC5_SLV_DATA_NACK_ONLY_inst                                              0x00E1
#define MIS_IC5_SLV_DATA_NACK_ONLY_nack_shift                                        (0)
#define MIS_IC5_SLV_DATA_NACK_ONLY_nack_mask                                         (0x00000001)
#define MIS_IC5_SLV_DATA_NACK_ONLY_nack(data)                                        (0x00000001&((data)<<0))
#define MIS_IC5_SLV_DATA_NACK_ONLY_nack_src(data)                                    ((0x00000001&(data))>>0)
#define MIS_IC5_SLV_DATA_NACK_ONLY_get_nack(data)                                    ((0x00000001&(data))>>0)


#define MIS_IC5_DMA_CR                                                               0x9801BB88
#define MIS_IC5_DMA_CR_reg_addr                                                      "0x9801BB88"
#define MIS_IC5_DMA_CR_reg                                                           0x9801BB88
#define set_MIS_IC5_DMA_CR_reg(data)   (*((volatile unsigned int*) MIS_IC5_DMA_CR_reg)=data)
#define get_MIS_IC5_DMA_CR_reg   (*((volatile unsigned int*) MIS_IC5_DMA_CR_reg))
#define MIS_IC5_DMA_CR_inst_adr                                                      "0x00E2"
#define MIS_IC5_DMA_CR_inst                                                          0x00E2
#define MIS_IC5_DMA_CR_tdmae_shift                                                   (1)
#define MIS_IC5_DMA_CR_tdmae_mask                                                    (0x00000002)
#define MIS_IC5_DMA_CR_tdmae(data)                                                   (0x00000002&((data)<<1))
#define MIS_IC5_DMA_CR_tdmae_src(data)                                               ((0x00000002&(data))>>1)
#define MIS_IC5_DMA_CR_get_tdmae(data)                                               ((0x00000002&(data))>>1)
#define MIS_IC5_DMA_CR_rdmae_shift                                                   (0)
#define MIS_IC5_DMA_CR_rdmae_mask                                                    (0x00000001)
#define MIS_IC5_DMA_CR_rdmae(data)                                                   (0x00000001&((data)<<0))
#define MIS_IC5_DMA_CR_rdmae_src(data)                                               ((0x00000001&(data))>>0)
#define MIS_IC5_DMA_CR_get_rdmae(data)                                               ((0x00000001&(data))>>0)


#define MIS_IC5_DMA_TDLR                                                             0x9801BB8C
#define MIS_IC5_DMA_TDLR_reg_addr                                                    "0x9801BB8C"
#define MIS_IC5_DMA_TDLR_reg                                                         0x9801BB8C
#define set_MIS_IC5_DMA_TDLR_reg(data)   (*((volatile unsigned int*) MIS_IC5_DMA_TDLR_reg)=data)
#define get_MIS_IC5_DMA_TDLR_reg   (*((volatile unsigned int*) MIS_IC5_DMA_TDLR_reg))
#define MIS_IC5_DMA_TDLR_inst_adr                                                    "0x00E3"
#define MIS_IC5_DMA_TDLR_inst                                                        0x00E3
#define MIS_IC5_DMA_TDLR_dmatdl_shift                                                (0)
#define MIS_IC5_DMA_TDLR_dmatdl_mask                                                 (0x00000007)
#define MIS_IC5_DMA_TDLR_dmatdl(data)                                                (0x00000007&((data)<<0))
#define MIS_IC5_DMA_TDLR_dmatdl_src(data)                                            ((0x00000007&(data))>>0)
#define MIS_IC5_DMA_TDLR_get_dmatdl(data)                                            ((0x00000007&(data))>>0)


#define MIS_IC5_DMA_RDLR                                                             0x9801BB90
#define MIS_IC5_DMA_RDLR_reg_addr                                                    "0x9801BB90"
#define MIS_IC5_DMA_RDLR_reg                                                         0x9801BB90
#define set_MIS_IC5_DMA_RDLR_reg(data)   (*((volatile unsigned int*) MIS_IC5_DMA_RDLR_reg)=data)
#define get_MIS_IC5_DMA_RDLR_reg   (*((volatile unsigned int*) MIS_IC5_DMA_RDLR_reg))
#define MIS_IC5_DMA_RDLR_inst_adr                                                    "0x00E4"
#define MIS_IC5_DMA_RDLR_inst                                                        0x00E4
#define MIS_IC5_DMA_RDLR_dmardl_shift                                                (0)
#define MIS_IC5_DMA_RDLR_dmardl_mask                                                 (0x0000000F)
#define MIS_IC5_DMA_RDLR_dmardl(data)                                                (0x0000000F&((data)<<0))
#define MIS_IC5_DMA_RDLR_dmardl_src(data)                                            ((0x0000000F&(data))>>0)
#define MIS_IC5_DMA_RDLR_get_dmardl(data)                                            ((0x0000000F&(data))>>0)


#define MIS_IC5_SDA_SETUP                                                            0x9801BB94
#define MIS_IC5_SDA_SETUP_reg_addr                                                   "0x9801BB94"
#define MIS_IC5_SDA_SETUP_reg                                                        0x9801BB94
#define set_MIS_IC5_SDA_SETUP_reg(data)   (*((volatile unsigned int*) MIS_IC5_SDA_SETUP_reg)=data)
#define get_MIS_IC5_SDA_SETUP_reg   (*((volatile unsigned int*) MIS_IC5_SDA_SETUP_reg))
#define MIS_IC5_SDA_SETUP_inst_adr                                                   "0x00E5"
#define MIS_IC5_SDA_SETUP_inst                                                       0x00E5
#define MIS_IC5_SDA_SETUP_sda_setup_shift                                            (0)
#define MIS_IC5_SDA_SETUP_sda_setup_mask                                             (0x000000FF)
#define MIS_IC5_SDA_SETUP_sda_setup(data)                                            (0x000000FF&((data)<<0))
#define MIS_IC5_SDA_SETUP_sda_setup_src(data)                                        ((0x000000FF&(data))>>0)
#define MIS_IC5_SDA_SETUP_get_sda_setup(data)                                        ((0x000000FF&(data))>>0)


#define MIS_IC5_ACK_GENERAL_CALL                                                     0x9801BB98
#define MIS_IC5_ACK_GENERAL_CALL_reg_addr                                            "0x9801BB98"
#define MIS_IC5_ACK_GENERAL_CALL_reg                                                 0x9801BB98
#define set_MIS_IC5_ACK_GENERAL_CALL_reg(data)   (*((volatile unsigned int*) MIS_IC5_ACK_GENERAL_CALL_reg)=data)
#define get_MIS_IC5_ACK_GENERAL_CALL_reg   (*((volatile unsigned int*) MIS_IC5_ACK_GENERAL_CALL_reg))
#define MIS_IC5_ACK_GENERAL_CALL_inst_adr                                            "0x00E6"
#define MIS_IC5_ACK_GENERAL_CALL_inst                                                0x00E6
#define MIS_IC5_ACK_GENERAL_CALL_ack_gen_call_shift                                  (0)
#define MIS_IC5_ACK_GENERAL_CALL_ack_gen_call_mask                                   (0x00000001)
#define MIS_IC5_ACK_GENERAL_CALL_ack_gen_call(data)                                  (0x00000001&((data)<<0))
#define MIS_IC5_ACK_GENERAL_CALL_ack_gen_call_src(data)                              ((0x00000001&(data))>>0)
#define MIS_IC5_ACK_GENERAL_CALL_get_ack_gen_call(data)                              ((0x00000001&(data))>>0)


#define MIS_IC5_ENABLE_STATUS                                                        0x9801BB9C
#define MIS_IC5_ENABLE_STATUS_reg_addr                                               "0x9801BB9C"
#define MIS_IC5_ENABLE_STATUS_reg                                                    0x9801BB9C
#define set_MIS_IC5_ENABLE_STATUS_reg(data)   (*((volatile unsigned int*) MIS_IC5_ENABLE_STATUS_reg)=data)
#define get_MIS_IC5_ENABLE_STATUS_reg   (*((volatile unsigned int*) MIS_IC5_ENABLE_STATUS_reg))
#define MIS_IC5_ENABLE_STATUS_inst_adr                                               "0x00E7"
#define MIS_IC5_ENABLE_STATUS_inst                                                   0x00E7
#define MIS_IC5_ENABLE_STATUS_slv_rx_data_lost_shift                                 (2)
#define MIS_IC5_ENABLE_STATUS_slv_rx_data_lost_mask                                  (0x00000004)
#define MIS_IC5_ENABLE_STATUS_slv_rx_data_lost(data)                                 (0x00000004&((data)<<2))
#define MIS_IC5_ENABLE_STATUS_slv_rx_data_lost_src(data)                             ((0x00000004&(data))>>2)
#define MIS_IC5_ENABLE_STATUS_get_slv_rx_data_lost(data)                             ((0x00000004&(data))>>2)
#define MIS_IC5_ENABLE_STATUS_slv_disabled_whi_shift                                 (1)
#define MIS_IC5_ENABLE_STATUS_slv_disabled_whi_mask                                  (0x00000002)
#define MIS_IC5_ENABLE_STATUS_slv_disabled_whi(data)                                 (0x00000002&((data)<<1))
#define MIS_IC5_ENABLE_STATUS_slv_disabled_whi_src(data)                             ((0x00000002&(data))>>1)
#define MIS_IC5_ENABLE_STATUS_get_slv_disabled_whi(data)                             ((0x00000002&(data))>>1)
#define MIS_IC5_ENABLE_STATUS_ic_en_shift                                            (0)
#define MIS_IC5_ENABLE_STATUS_ic_en_mask                                             (0x00000001)
#define MIS_IC5_ENABLE_STATUS_ic_en(data)                                            (0x00000001&((data)<<0))
#define MIS_IC5_ENABLE_STATUS_ic_en_src(data)                                        ((0x00000001&(data))>>0)
#define MIS_IC5_ENABLE_STATUS_get_ic_en(data)                                        ((0x00000001&(data))>>0)


#define MIS_IC5_COMP_PARAM_1                                                         0x9801BBF4
#define MIS_IC5_COMP_PARAM_1_reg_addr                                                "0x9801BBF4"
#define MIS_IC5_COMP_PARAM_1_reg                                                     0x9801BBF4
#define set_MIS_IC5_COMP_PARAM_1_reg(data)   (*((volatile unsigned int*) MIS_IC5_COMP_PARAM_1_reg)=data)
#define get_MIS_IC5_COMP_PARAM_1_reg   (*((volatile unsigned int*) MIS_IC5_COMP_PARAM_1_reg))
#define MIS_IC5_COMP_PARAM_1_inst_adr                                                "0x00FD"
#define MIS_IC5_COMP_PARAM_1_inst                                                    0x00FD
#define MIS_IC5_COMP_PARAM_1_tx_buffer_depth_shift                                   (16)
#define MIS_IC5_COMP_PARAM_1_tx_buffer_depth_mask                                    (0x00FF0000)
#define MIS_IC5_COMP_PARAM_1_tx_buffer_depth(data)                                   (0x00FF0000&((data)<<16))
#define MIS_IC5_COMP_PARAM_1_tx_buffer_depth_src(data)                               ((0x00FF0000&(data))>>16)
#define MIS_IC5_COMP_PARAM_1_get_tx_buffer_depth(data)                               ((0x00FF0000&(data))>>16)
#define MIS_IC5_COMP_PARAM_1_rx_buffer_depth_shift                                   (8)
#define MIS_IC5_COMP_PARAM_1_rx_buffer_depth_mask                                    (0x0000FF00)
#define MIS_IC5_COMP_PARAM_1_rx_buffer_depth(data)                                   (0x0000FF00&((data)<<8))
#define MIS_IC5_COMP_PARAM_1_rx_buffer_depth_src(data)                               ((0x0000FF00&(data))>>8)
#define MIS_IC5_COMP_PARAM_1_get_rx_buffer_depth(data)                               ((0x0000FF00&(data))>>8)
#define MIS_IC5_COMP_PARAM_1_add_encoded_params_shift                                (7)
#define MIS_IC5_COMP_PARAM_1_add_encoded_params_mask                                 (0x00000080)
#define MIS_IC5_COMP_PARAM_1_add_encoded_params(data)                                (0x00000080&((data)<<7))
#define MIS_IC5_COMP_PARAM_1_add_encoded_params_src(data)                            ((0x00000080&(data))>>7)
#define MIS_IC5_COMP_PARAM_1_get_add_encoded_params(data)                            ((0x00000080&(data))>>7)
#define MIS_IC5_COMP_PARAM_1_has_dma_shift                                           (6)
#define MIS_IC5_COMP_PARAM_1_has_dma_mask                                            (0x00000040)
#define MIS_IC5_COMP_PARAM_1_has_dma(data)                                           (0x00000040&((data)<<6))
#define MIS_IC5_COMP_PARAM_1_has_dma_src(data)                                       ((0x00000040&(data))>>6)
#define MIS_IC5_COMP_PARAM_1_get_has_dma(data)                                       ((0x00000040&(data))>>6)
#define MIS_IC5_COMP_PARAM_1_intr_io_shift                                           (5)
#define MIS_IC5_COMP_PARAM_1_intr_io_mask                                            (0x00000020)
#define MIS_IC5_COMP_PARAM_1_intr_io(data)                                           (0x00000020&((data)<<5))
#define MIS_IC5_COMP_PARAM_1_intr_io_src(data)                                       ((0x00000020&(data))>>5)
#define MIS_IC5_COMP_PARAM_1_get_intr_io(data)                                       ((0x00000020&(data))>>5)
#define MIS_IC5_COMP_PARAM_1_hc_count_values_shift                                   (4)
#define MIS_IC5_COMP_PARAM_1_hc_count_values_mask                                    (0x00000010)
#define MIS_IC5_COMP_PARAM_1_hc_count_values(data)                                   (0x00000010&((data)<<4))
#define MIS_IC5_COMP_PARAM_1_hc_count_values_src(data)                               ((0x00000010&(data))>>4)
#define MIS_IC5_COMP_PARAM_1_get_hc_count_values(data)                               ((0x00000010&(data))>>4)
#define MIS_IC5_COMP_PARAM_1_max_speed_mode_shift                                    (2)
#define MIS_IC5_COMP_PARAM_1_max_speed_mode_mask                                     (0x0000000C)
#define MIS_IC5_COMP_PARAM_1_max_speed_mode(data)                                    (0x0000000C&((data)<<2))
#define MIS_IC5_COMP_PARAM_1_max_speed_mode_src(data)                                ((0x0000000C&(data))>>2)
#define MIS_IC5_COMP_PARAM_1_get_max_speed_mode(data)                                ((0x0000000C&(data))>>2)
#define MIS_IC5_COMP_PARAM_1_apb_data_width_shift                                    (0)
#define MIS_IC5_COMP_PARAM_1_apb_data_width_mask                                     (0x00000003)
#define MIS_IC5_COMP_PARAM_1_apb_data_width(data)                                    (0x00000003&((data)<<0))
#define MIS_IC5_COMP_PARAM_1_apb_data_width_src(data)                                ((0x00000003&(data))>>0)
#define MIS_IC5_COMP_PARAM_1_get_apb_data_width(data)                                ((0x00000003&(data))>>0)


#define MIS_IC5_COMP_VERSION                                                         0x9801BBF8
#define MIS_IC5_COMP_VERSION_reg_addr                                                "0x9801BBF8"
#define MIS_IC5_COMP_VERSION_reg                                                     0x9801BBF8
#define set_MIS_IC5_COMP_VERSION_reg(data)   (*((volatile unsigned int*) MIS_IC5_COMP_VERSION_reg)=data)
#define get_MIS_IC5_COMP_VERSION_reg   (*((volatile unsigned int*) MIS_IC5_COMP_VERSION_reg))
#define MIS_IC5_COMP_VERSION_inst_adr                                                "0x00FE"
#define MIS_IC5_COMP_VERSION_inst                                                    0x00FE
#define MIS_IC5_COMP_VERSION_ic_comp_version_shift                                   (0)
#define MIS_IC5_COMP_VERSION_ic_comp_version_mask                                    (0xFFFFFFFF)
#define MIS_IC5_COMP_VERSION_ic_comp_version(data)                                   (0xFFFFFFFF&((data)<<0))
#define MIS_IC5_COMP_VERSION_ic_comp_version_src(data)                               ((0xFFFFFFFF&(data))>>0)
#define MIS_IC5_COMP_VERSION_get_ic_comp_version(data)                               ((0xFFFFFFFF&(data))>>0)


#define MIS_IC5_COMP_TYPE                                                            0x9801BBFC
#define MIS_IC5_COMP_TYPE_reg_addr                                                   "0x9801BBFC"
#define MIS_IC5_COMP_TYPE_reg                                                        0x9801BBFC
#define set_MIS_IC5_COMP_TYPE_reg(data)   (*((volatile unsigned int*) MIS_IC5_COMP_TYPE_reg)=data)
#define get_MIS_IC5_COMP_TYPE_reg   (*((volatile unsigned int*) MIS_IC5_COMP_TYPE_reg))
#define MIS_IC5_COMP_TYPE_inst_adr                                                   "0x00FF"
#define MIS_IC5_COMP_TYPE_inst                                                       0x00FF
#define MIS_IC5_COMP_TYPE_ic_comp_type_shift                                         (0)
#define MIS_IC5_COMP_TYPE_ic_comp_type_mask                                          (0xFFFFFFFF)
#define MIS_IC5_COMP_TYPE_ic_comp_type(data)                                         (0xFFFFFFFF&((data)<<0))
#define MIS_IC5_COMP_TYPE_ic_comp_type_src(data)                                     ((0xFFFFFFFF&(data))>>0)
#define MIS_IC5_COMP_TYPE_get_ic_comp_type(data)                                     ((0xFFFFFFFF&(data))>>0)


#define MIS_TC0TVR                                                                   0x9801B500
#define MIS_TC0TVR_reg_addr                                                          "0x9801B500"
#define MIS_TC0TVR_reg                                                               0x9801B500
#define set_MIS_TC0TVR_reg(data)   (*((volatile unsigned int*) MIS_TC0TVR_reg)=data)
#define get_MIS_TC0TVR_reg   (*((volatile unsigned int*) MIS_TC0TVR_reg))
#define MIS_TC0TVR_inst_adr                                                          "0x0040"
#define MIS_TC0TVR_inst                                                              0x0040
#define MIS_TC0TVR_tc0tvr_shift                                                      (0)
#define MIS_TC0TVR_tc0tvr_mask                                                       (0xFFFFFFFF)
#define MIS_TC0TVR_tc0tvr(data)                                                      (0xFFFFFFFF&((data)<<0))
#define MIS_TC0TVR_tc0tvr_src(data)                                                  ((0xFFFFFFFF&(data))>>0)
#define MIS_TC0TVR_get_tc0tvr(data)                                                  ((0xFFFFFFFF&(data))>>0)


#define MIS_TC1TVR                                                                   0x9801B504
#define MIS_TC1TVR_reg_addr                                                          "0x9801B504"
#define MIS_TC1TVR_reg                                                               0x9801B504
#define set_MIS_TC1TVR_reg(data)   (*((volatile unsigned int*) MIS_TC1TVR_reg)=data)
#define get_MIS_TC1TVR_reg   (*((volatile unsigned int*) MIS_TC1TVR_reg))
#define MIS_TC1TVR_inst_adr                                                          "0x0041"
#define MIS_TC1TVR_inst                                                              0x0041
#define MIS_TC1TVR_tc1tvr_shift                                                      (0)
#define MIS_TC1TVR_tc1tvr_mask                                                       (0xFFFFFFFF)
#define MIS_TC1TVR_tc1tvr(data)                                                      (0xFFFFFFFF&((data)<<0))
#define MIS_TC1TVR_tc1tvr_src(data)                                                  ((0xFFFFFFFF&(data))>>0)
#define MIS_TC1TVR_get_tc1tvr(data)                                                  ((0xFFFFFFFF&(data))>>0)


#define MIS_TC2TVR                                                                   0x9801B508
#define MIS_TC2TVR_reg_addr                                                          "0x9801B508"
#define MIS_TC2TVR_reg                                                               0x9801B508
#define set_MIS_TC2TVR_reg(data)   (*((volatile unsigned int*) MIS_TC2TVR_reg)=data)
#define get_MIS_TC2TVR_reg   (*((volatile unsigned int*) MIS_TC2TVR_reg))
#define MIS_TC2TVR_inst_adr                                                          "0x0042"
#define MIS_TC2TVR_inst                                                              0x0042
#define MIS_TC2TVR_tc2tvr_shift                                                      (0)
#define MIS_TC2TVR_tc2tvr_mask                                                       (0xFFFFFFFF)
#define MIS_TC2TVR_tc2tvr(data)                                                      (0xFFFFFFFF&((data)<<0))
#define MIS_TC2TVR_tc2tvr_src(data)                                                  ((0xFFFFFFFF&(data))>>0)
#define MIS_TC2TVR_get_tc2tvr(data)                                                  ((0xFFFFFFFF&(data))>>0)


#define MIS_TC0CVR                                                                   0x9801B50C
#define MIS_TC0CVR_reg_addr                                                          "0x9801B50C"
#define MIS_TC0CVR_reg                                                               0x9801B50C
#define set_MIS_TC0CVR_reg(data)   (*((volatile unsigned int*) MIS_TC0CVR_reg)=data)
#define get_MIS_TC0CVR_reg   (*((volatile unsigned int*) MIS_TC0CVR_reg))
#define MIS_TC0CVR_inst_adr                                                          "0x0043"
#define MIS_TC0CVR_inst                                                              0x0043
#define MIS_TC0CVR_tc0cvr_shift                                                      (0)
#define MIS_TC0CVR_tc0cvr_mask                                                       (0xFFFFFFFF)
#define MIS_TC0CVR_tc0cvr(data)                                                      (0xFFFFFFFF&((data)<<0))
#define MIS_TC0CVR_tc0cvr_src(data)                                                  ((0xFFFFFFFF&(data))>>0)
#define MIS_TC0CVR_get_tc0cvr(data)                                                  ((0xFFFFFFFF&(data))>>0)


#define MIS_TC1CVR                                                                   0x9801B510
#define MIS_TC1CVR_reg_addr                                                          "0x9801B510"
#define MIS_TC1CVR_reg                                                               0x9801B510
#define set_MIS_TC1CVR_reg(data)   (*((volatile unsigned int*) MIS_TC1CVR_reg)=data)
#define get_MIS_TC1CVR_reg   (*((volatile unsigned int*) MIS_TC1CVR_reg))
#define MIS_TC1CVR_inst_adr                                                          "0x0044"
#define MIS_TC1CVR_inst                                                              0x0044
#define MIS_TC1CVR_tc1cvr_shift                                                      (0)
#define MIS_TC1CVR_tc1cvr_mask                                                       (0xFFFFFFFF)
#define MIS_TC1CVR_tc1cvr(data)                                                      (0xFFFFFFFF&((data)<<0))
#define MIS_TC1CVR_tc1cvr_src(data)                                                  ((0xFFFFFFFF&(data))>>0)
#define MIS_TC1CVR_get_tc1cvr(data)                                                  ((0xFFFFFFFF&(data))>>0)


#define MIS_TC2CVR                                                                   0x9801B514
#define MIS_TC2CVR_reg_addr                                                          "0x9801B514"
#define MIS_TC2CVR_reg                                                               0x9801B514
#define set_MIS_TC2CVR_reg(data)   (*((volatile unsigned int*) MIS_TC2CVR_reg)=data)
#define get_MIS_TC2CVR_reg   (*((volatile unsigned int*) MIS_TC2CVR_reg))
#define MIS_TC2CVR_inst_adr                                                          "0x0045"
#define MIS_TC2CVR_inst                                                              0x0045
#define MIS_TC2CVR_tc2vr_shift                                                       (0)
#define MIS_TC2CVR_tc2vr_mask                                                        (0xFFFFFFFF)
#define MIS_TC2CVR_tc2vr(data)                                                       (0xFFFFFFFF&((data)<<0))
#define MIS_TC2CVR_tc2vr_src(data)                                                   ((0xFFFFFFFF&(data))>>0)
#define MIS_TC2CVR_get_tc2vr(data)                                                   ((0xFFFFFFFF&(data))>>0)


#define MIS_TC0CR                                                                    0x9801B518
#define MIS_TC0CR_reg_addr                                                           "0x9801B518"
#define MIS_TC0CR_reg                                                                0x9801B518
#define set_MIS_TC0CR_reg(data)   (*((volatile unsigned int*) MIS_TC0CR_reg)=data)
#define get_MIS_TC0CR_reg   (*((volatile unsigned int*) MIS_TC0CR_reg))
#define MIS_TC0CR_inst_adr                                                           "0x0046"
#define MIS_TC0CR_inst                                                               0x0046
#define MIS_TC0CR_tc0en_shift                                                        (31)
#define MIS_TC0CR_tc0en_mask                                                         (0x80000000)
#define MIS_TC0CR_tc0en(data)                                                        (0x80000000&((data)<<31))
#define MIS_TC0CR_tc0en_src(data)                                                    ((0x80000000&(data))>>31)
#define MIS_TC0CR_get_tc0en(data)                                                    ((0x80000000&(data))>>31)
#define MIS_TC0CR_tc0mode_shift                                                      (30)
#define MIS_TC0CR_tc0mode_mask                                                       (0x40000000)
#define MIS_TC0CR_tc0mode(data)                                                      (0x40000000&((data)<<30))
#define MIS_TC0CR_tc0mode_src(data)                                                  ((0x40000000&(data))>>30)
#define MIS_TC0CR_get_tc0mode(data)                                                  ((0x40000000&(data))>>30)
#define MIS_TC0CR_tc0pause_shift                                                     (29)
#define MIS_TC0CR_tc0pause_mask                                                      (0x20000000)
#define MIS_TC0CR_tc0pause(data)                                                     (0x20000000&((data)<<29))
#define MIS_TC0CR_tc0pause_src(data)                                                 ((0x20000000&(data))>>29)
#define MIS_TC0CR_get_tc0pause(data)                                                 ((0x20000000&(data))>>29)
#define MIS_TC0CR_rvda_shift                                                         (24)
#define MIS_TC0CR_rvda_mask                                                          (0x1F000000)
#define MIS_TC0CR_rvda(data)                                                         (0x1F000000&((data)<<24))
#define MIS_TC0CR_rvda_src(data)                                                     ((0x1F000000&(data))>>24)
#define MIS_TC0CR_get_rvda(data)                                                     ((0x1F000000&(data))>>24)


#define MIS_TC1CR                                                                    0x9801B51C
#define MIS_TC1CR_reg_addr                                                           "0x9801B51C"
#define MIS_TC1CR_reg                                                                0x9801B51C
#define set_MIS_TC1CR_reg(data)   (*((volatile unsigned int*) MIS_TC1CR_reg)=data)
#define get_MIS_TC1CR_reg   (*((volatile unsigned int*) MIS_TC1CR_reg))
#define MIS_TC1CR_inst_adr                                                           "0x0047"
#define MIS_TC1CR_inst                                                               0x0047
#define MIS_TC1CR_tc1en_shift                                                        (31)
#define MIS_TC1CR_tc1en_mask                                                         (0x80000000)
#define MIS_TC1CR_tc1en(data)                                                        (0x80000000&((data)<<31))
#define MIS_TC1CR_tc1en_src(data)                                                    ((0x80000000&(data))>>31)
#define MIS_TC1CR_get_tc1en(data)                                                    ((0x80000000&(data))>>31)
#define MIS_TC1CR_tc1mode_shift                                                      (30)
#define MIS_TC1CR_tc1mode_mask                                                       (0x40000000)
#define MIS_TC1CR_tc1mode(data)                                                      (0x40000000&((data)<<30))
#define MIS_TC1CR_tc1mode_src(data)                                                  ((0x40000000&(data))>>30)
#define MIS_TC1CR_get_tc1mode(data)                                                  ((0x40000000&(data))>>30)
#define MIS_TC1CR_tc1pause_shift                                                     (29)
#define MIS_TC1CR_tc1pause_mask                                                      (0x20000000)
#define MIS_TC1CR_tc1pause(data)                                                     (0x20000000&((data)<<29))
#define MIS_TC1CR_tc1pause_src(data)                                                 ((0x20000000&(data))>>29)
#define MIS_TC1CR_get_tc1pause(data)                                                 ((0x20000000&(data))>>29)
#define MIS_TC1CR_rvda_shift                                                         (24)
#define MIS_TC1CR_rvda_mask                                                          (0x1F000000)
#define MIS_TC1CR_rvda(data)                                                         (0x1F000000&((data)<<24))
#define MIS_TC1CR_rvda_src(data)                                                     ((0x1F000000&(data))>>24)
#define MIS_TC1CR_get_rvda(data)                                                     ((0x1F000000&(data))>>24)


#define MIS_TC2CR                                                                    0x9801B520
#define MIS_TC2CR_reg_addr                                                           "0x9801B520"
#define MIS_TC2CR_reg                                                                0x9801B520
#define set_MIS_TC2CR_reg(data)   (*((volatile unsigned int*) MIS_TC2CR_reg)=data)
#define get_MIS_TC2CR_reg   (*((volatile unsigned int*) MIS_TC2CR_reg))
#define MIS_TC2CR_inst_adr                                                           "0x0048"
#define MIS_TC2CR_inst                                                               0x0048
#define MIS_TC2CR_tc2en_shift                                                        (31)
#define MIS_TC2CR_tc2en_mask                                                         (0x80000000)
#define MIS_TC2CR_tc2en(data)                                                        (0x80000000&((data)<<31))
#define MIS_TC2CR_tc2en_src(data)                                                    ((0x80000000&(data))>>31)
#define MIS_TC2CR_get_tc2en(data)                                                    ((0x80000000&(data))>>31)
#define MIS_TC2CR_tc2mode_shift                                                      (30)
#define MIS_TC2CR_tc2mode_mask                                                       (0x40000000)
#define MIS_TC2CR_tc2mode(data)                                                      (0x40000000&((data)<<30))
#define MIS_TC2CR_tc2mode_src(data)                                                  ((0x40000000&(data))>>30)
#define MIS_TC2CR_get_tc2mode(data)                                                  ((0x40000000&(data))>>30)
#define MIS_TC2CR_tc2pause_shift                                                     (29)
#define MIS_TC2CR_tc2pause_mask                                                      (0x20000000)
#define MIS_TC2CR_tc2pause(data)                                                     (0x20000000&((data)<<29))
#define MIS_TC2CR_tc2pause_src(data)                                                 ((0x20000000&(data))>>29)
#define MIS_TC2CR_get_tc2pause(data)                                                 ((0x20000000&(data))>>29)
#define MIS_TC2CR_rvda_shift                                                         (24)
#define MIS_TC2CR_rvda_mask                                                          (0x1F000000)
#define MIS_TC2CR_rvda(data)                                                         (0x1F000000&((data)<<24))
#define MIS_TC2CR_rvda_src(data)                                                     ((0x1F000000&(data))>>24)
#define MIS_TC2CR_get_rvda(data)                                                     ((0x1F000000&(data))>>24)


#define MIS_TC0ICR                                                                   0x9801B524
#define MIS_TC0ICR_reg_addr                                                          "0x9801B524"
#define MIS_TC0ICR_reg                                                               0x9801B524
#define set_MIS_TC0ICR_reg(data)   (*((volatile unsigned int*) MIS_TC0ICR_reg)=data)
#define get_MIS_TC0ICR_reg   (*((volatile unsigned int*) MIS_TC0ICR_reg))
#define MIS_TC0ICR_inst_adr                                                          "0x0049"
#define MIS_TC0ICR_inst                                                              0x0049
#define MIS_TC0ICR_tc0ie_shift                                                       (31)
#define MIS_TC0ICR_tc0ie_mask                                                        (0x80000000)
#define MIS_TC0ICR_tc0ie(data)                                                       (0x80000000&((data)<<31))
#define MIS_TC0ICR_tc0ie_src(data)                                                   ((0x80000000&(data))>>31)
#define MIS_TC0ICR_get_tc0ie(data)                                                   ((0x80000000&(data))>>31)


#define MIS_TC1ICR                                                                   0x9801B528
#define MIS_TC1ICR_reg_addr                                                          "0x9801B528"
#define MIS_TC1ICR_reg                                                               0x9801B528
#define set_MIS_TC1ICR_reg(data)   (*((volatile unsigned int*) MIS_TC1ICR_reg)=data)
#define get_MIS_TC1ICR_reg   (*((volatile unsigned int*) MIS_TC1ICR_reg))
#define MIS_TC1ICR_inst_adr                                                          "0x004A"
#define MIS_TC1ICR_inst                                                              0x004A
#define MIS_TC1ICR_tc1ie_shift                                                       (31)
#define MIS_TC1ICR_tc1ie_mask                                                        (0x80000000)
#define MIS_TC1ICR_tc1ie(data)                                                       (0x80000000&((data)<<31))
#define MIS_TC1ICR_tc1ie_src(data)                                                   ((0x80000000&(data))>>31)
#define MIS_TC1ICR_get_tc1ie(data)                                                   ((0x80000000&(data))>>31)


#define MIS_TC2ICR                                                                   0x9801B52C
#define MIS_TC2ICR_reg_addr                                                          "0x9801B52C"
#define MIS_TC2ICR_reg                                                               0x9801B52C
#define set_MIS_TC2ICR_reg(data)   (*((volatile unsigned int*) MIS_TC2ICR_reg)=data)
#define get_MIS_TC2ICR_reg   (*((volatile unsigned int*) MIS_TC2ICR_reg))
#define MIS_TC2ICR_inst_adr                                                          "0x004B"
#define MIS_TC2ICR_inst                                                              0x004B
#define MIS_TC2ICR_tc2ie_shift                                                       (31)
#define MIS_TC2ICR_tc2ie_mask                                                        (0x80000000)
#define MIS_TC2ICR_tc2ie(data)                                                       (0x80000000&((data)<<31))
#define MIS_TC2ICR_tc2ie_src(data)                                                   ((0x80000000&(data))>>31)
#define MIS_TC2ICR_get_tc2ie(data)                                                   ((0x80000000&(data))>>31)


#define MIS_CLK90K_CTRL                                                              0x9801B538
#define MIS_CLK90K_CTRL_reg_addr                                                     "0x9801B538"
#define MIS_CLK90K_CTRL_reg                                                          0x9801B538
#define set_MIS_CLK90K_CTRL_reg(data)   (*((volatile unsigned int*) MIS_CLK90K_CTRL_reg)=data)
#define get_MIS_CLK90K_CTRL_reg   (*((volatile unsigned int*) MIS_CLK90K_CTRL_reg))
#define MIS_CLK90K_CTRL_inst_adr                                                     "0x004E"
#define MIS_CLK90K_CTRL_inst                                                         0x004E
#define MIS_CLK90K_CTRL_en_shift                                                     (0)
#define MIS_CLK90K_CTRL_en_mask                                                      (0x00000001)
#define MIS_CLK90K_CTRL_en(data)                                                     (0x00000001&((data)<<0))
#define MIS_CLK90K_CTRL_en_src(data)                                                 ((0x00000001&(data))>>0)
#define MIS_CLK90K_CTRL_get_en(data)                                                 ((0x00000001&(data))>>0)


#define MIS_SCPU_CLK27M_90K                                                          0x9801B53C
#define MIS_SCPU_CLK27M_90K_reg_addr                                                 "0x9801B53C"
#define MIS_SCPU_CLK27M_90K_reg                                                      0x9801B53C
#define set_MIS_SCPU_CLK27M_90K_reg(data)   (*((volatile unsigned int*) MIS_SCPU_CLK27M_90K_reg)=data)
#define get_MIS_SCPU_CLK27M_90K_reg   (*((volatile unsigned int*) MIS_SCPU_CLK27M_90K_reg))
#define MIS_SCPU_CLK27M_90K_inst_adr                                                 "0x004F"
#define MIS_SCPU_CLK27M_90K_inst                                                     0x004F
#define MIS_SCPU_CLK27M_90K_cnt_shift                                                (0)
#define MIS_SCPU_CLK27M_90K_cnt_mask                                                 (0x000001FF)
#define MIS_SCPU_CLK27M_90K_cnt(data)                                                (0x000001FF&((data)<<0))
#define MIS_SCPU_CLK27M_90K_cnt_src(data)                                            ((0x000001FF&(data))>>0)
#define MIS_SCPU_CLK27M_90K_get_cnt(data)                                            ((0x000001FF&(data))>>0)


#define MIS_SCPU_CLK90K_LO                                                           0x9801B540
#define MIS_SCPU_CLK90K_LO_reg_addr                                                  "0x9801B540"
#define MIS_SCPU_CLK90K_LO_reg                                                       0x9801B540
#define set_MIS_SCPU_CLK90K_LO_reg(data)   (*((volatile unsigned int*) MIS_SCPU_CLK90K_LO_reg)=data)
#define get_MIS_SCPU_CLK90K_LO_reg   (*((volatile unsigned int*) MIS_SCPU_CLK90K_LO_reg))
#define MIS_SCPU_CLK90K_LO_inst_adr                                                  "0x0050"
#define MIS_SCPU_CLK90K_LO_inst                                                      0x0050
#define MIS_SCPU_CLK90K_LO_val_shift                                                 (0)
#define MIS_SCPU_CLK90K_LO_val_mask                                                  (0xFFFFFFFF)
#define MIS_SCPU_CLK90K_LO_val(data)                                                 (0xFFFFFFFF&((data)<<0))
#define MIS_SCPU_CLK90K_LO_val_src(data)                                             ((0xFFFFFFFF&(data))>>0)
#define MIS_SCPU_CLK90K_LO_get_val(data)                                             ((0xFFFFFFFF&(data))>>0)


#define MIS_SCPU_CLK90K_HI                                                           0x9801B544
#define MIS_SCPU_CLK90K_HI_reg_addr                                                  "0x9801B544"
#define MIS_SCPU_CLK90K_HI_reg                                                       0x9801B544
#define set_MIS_SCPU_CLK90K_HI_reg(data)   (*((volatile unsigned int*) MIS_SCPU_CLK90K_HI_reg)=data)
#define get_MIS_SCPU_CLK90K_HI_reg   (*((volatile unsigned int*) MIS_SCPU_CLK90K_HI_reg))
#define MIS_SCPU_CLK90K_HI_inst_adr                                                  "0x0051"
#define MIS_SCPU_CLK90K_HI_inst                                                      0x0051
#define MIS_SCPU_CLK90K_HI_val_shift                                                 (0)
#define MIS_SCPU_CLK90K_HI_val_mask                                                  (0x0000FFFF)
#define MIS_SCPU_CLK90K_HI_val(data)                                                 (0x0000FFFF&((data)<<0))
#define MIS_SCPU_CLK90K_HI_val_src(data)                                             ((0x0000FFFF&(data))>>0)
#define MIS_SCPU_CLK90K_HI_get_val(data)                                             ((0x0000FFFF&(data))>>0)


#define MIS_ACPU_CLK27M_90K                                                          0x9801B548
#define MIS_ACPU_CLK27M_90K_reg_addr                                                 "0x9801B548"
#define MIS_ACPU_CLK27M_90K_reg                                                      0x9801B548
#define set_MIS_ACPU_CLK27M_90K_reg(data)   (*((volatile unsigned int*) MIS_ACPU_CLK27M_90K_reg)=data)
#define get_MIS_ACPU_CLK27M_90K_reg   (*((volatile unsigned int*) MIS_ACPU_CLK27M_90K_reg))
#define MIS_ACPU_CLK27M_90K_inst_adr                                                 "0x0052"
#define MIS_ACPU_CLK27M_90K_inst                                                     0x0052
#define MIS_ACPU_CLK27M_90K_cnt_shift                                                (0)
#define MIS_ACPU_CLK27M_90K_cnt_mask                                                 (0x000001FF)
#define MIS_ACPU_CLK27M_90K_cnt(data)                                                (0x000001FF&((data)<<0))
#define MIS_ACPU_CLK27M_90K_cnt_src(data)                                            ((0x000001FF&(data))>>0)
#define MIS_ACPU_CLK27M_90K_get_cnt(data)                                            ((0x000001FF&(data))>>0)


#define MIS_ACPU_CLK90K_LO                                                           0x9801B54C
#define MIS_ACPU_CLK90K_LO_reg_addr                                                  "0x9801B54C"
#define MIS_ACPU_CLK90K_LO_reg                                                       0x9801B54C
#define set_MIS_ACPU_CLK90K_LO_reg(data)   (*((volatile unsigned int*) MIS_ACPU_CLK90K_LO_reg)=data)
#define get_MIS_ACPU_CLK90K_LO_reg   (*((volatile unsigned int*) MIS_ACPU_CLK90K_LO_reg))
#define MIS_ACPU_CLK90K_LO_inst_adr                                                  "0x0053"
#define MIS_ACPU_CLK90K_LO_inst                                                      0x0053
#define MIS_ACPU_CLK90K_LO_val_shift                                                 (0)
#define MIS_ACPU_CLK90K_LO_val_mask                                                  (0xFFFFFFFF)
#define MIS_ACPU_CLK90K_LO_val(data)                                                 (0xFFFFFFFF&((data)<<0))
#define MIS_ACPU_CLK90K_LO_val_src(data)                                             ((0xFFFFFFFF&(data))>>0)
#define MIS_ACPU_CLK90K_LO_get_val(data)                                             ((0xFFFFFFFF&(data))>>0)


#define MIS_ACPU_CLK90K_HI                                                           0x9801B550
#define MIS_ACPU_CLK90K_HI_reg_addr                                                  "0x9801B550"
#define MIS_ACPU_CLK90K_HI_reg                                                       0x9801B550
#define set_MIS_ACPU_CLK90K_HI_reg(data)   (*((volatile unsigned int*) MIS_ACPU_CLK90K_HI_reg)=data)
#define get_MIS_ACPU_CLK90K_HI_reg   (*((volatile unsigned int*) MIS_ACPU_CLK90K_HI_reg))
#define MIS_ACPU_CLK90K_HI_inst_adr                                                  "0x0054"
#define MIS_ACPU_CLK90K_HI_inst                                                      0x0054
#define MIS_ACPU_CLK90K_HI_val_shift                                                 (0)
#define MIS_ACPU_CLK90K_HI_val_mask                                                  (0x0000FFFF)
#define MIS_ACPU_CLK90K_HI_val(data)                                                 (0x0000FFFF&((data)<<0))
#define MIS_ACPU_CLK90K_HI_val_src(data)                                             ((0x0000FFFF&(data))>>0)
#define MIS_ACPU_CLK90K_HI_get_val(data)                                             ((0x0000FFFF&(data))>>0)


#define MIS_PCR_CLK90K_CTRL                                                          0x9801B570
#define MIS_PCR_CLK90K_CTRL_reg_addr                                                 "0x9801B570"
#define MIS_PCR_CLK90K_CTRL_reg                                                      0x9801B570
#define set_MIS_PCR_CLK90K_CTRL_reg(data)   (*((volatile unsigned int*) MIS_PCR_CLK90K_CTRL_reg)=data)
#define get_MIS_PCR_CLK90K_CTRL_reg   (*((volatile unsigned int*) MIS_PCR_CLK90K_CTRL_reg))
#define MIS_PCR_CLK90K_CTRL_inst_adr                                                 "0x005C"
#define MIS_PCR_CLK90K_CTRL_inst                                                     0x005C
#define MIS_PCR_CLK90K_CTRL_en_shift                                                 (0)
#define MIS_PCR_CLK90K_CTRL_en_mask                                                  (0x00000001)
#define MIS_PCR_CLK90K_CTRL_en(data)                                                 (0x00000001&((data)<<0))
#define MIS_PCR_CLK90K_CTRL_en_src(data)                                             ((0x00000001&(data))>>0)
#define MIS_PCR_CLK90K_CTRL_get_en(data)                                             ((0x00000001&(data))>>0)


#define MIS_PCR_SCPU_CLK27M_90K                                                      0x9801B574
#define MIS_PCR_SCPU_CLK27M_90K_reg_addr                                             "0x9801B574"
#define MIS_PCR_SCPU_CLK27M_90K_reg                                                  0x9801B574
#define set_MIS_PCR_SCPU_CLK27M_90K_reg(data)   (*((volatile unsigned int*) MIS_PCR_SCPU_CLK27M_90K_reg)=data)
#define get_MIS_PCR_SCPU_CLK27M_90K_reg   (*((volatile unsigned int*) MIS_PCR_SCPU_CLK27M_90K_reg))
#define MIS_PCR_SCPU_CLK27M_90K_inst_adr                                             "0x005D"
#define MIS_PCR_SCPU_CLK27M_90K_inst                                                 0x005D
#define MIS_PCR_SCPU_CLK27M_90K_cnt_shift                                            (0)
#define MIS_PCR_SCPU_CLK27M_90K_cnt_mask                                             (0x000001FF)
#define MIS_PCR_SCPU_CLK27M_90K_cnt(data)                                            (0x000001FF&((data)<<0))
#define MIS_PCR_SCPU_CLK27M_90K_cnt_src(data)                                        ((0x000001FF&(data))>>0)
#define MIS_PCR_SCPU_CLK27M_90K_get_cnt(data)                                        ((0x000001FF&(data))>>0)


#define MIS_PCR_SCPU_CLK90K_LO                                                       0x9801B578
#define MIS_PCR_SCPU_CLK90K_LO_reg_addr                                              "0x9801B578"
#define MIS_PCR_SCPU_CLK90K_LO_reg                                                   0x9801B578
#define set_MIS_PCR_SCPU_CLK90K_LO_reg(data)   (*((volatile unsigned int*) MIS_PCR_SCPU_CLK90K_LO_reg)=data)
#define get_MIS_PCR_SCPU_CLK90K_LO_reg   (*((volatile unsigned int*) MIS_PCR_SCPU_CLK90K_LO_reg))
#define MIS_PCR_SCPU_CLK90K_LO_inst_adr                                              "0x005E"
#define MIS_PCR_SCPU_CLK90K_LO_inst                                                  0x005E
#define MIS_PCR_SCPU_CLK90K_LO_val_shift                                             (0)
#define MIS_PCR_SCPU_CLK90K_LO_val_mask                                              (0xFFFFFFFF)
#define MIS_PCR_SCPU_CLK90K_LO_val(data)                                             (0xFFFFFFFF&((data)<<0))
#define MIS_PCR_SCPU_CLK90K_LO_val_src(data)                                         ((0xFFFFFFFF&(data))>>0)
#define MIS_PCR_SCPU_CLK90K_LO_get_val(data)                                         ((0xFFFFFFFF&(data))>>0)


#define MIS_PCR_SCPU_CLK90K_HI                                                       0x9801B57C
#define MIS_PCR_SCPU_CLK90K_HI_reg_addr                                              "0x9801B57C"
#define MIS_PCR_SCPU_CLK90K_HI_reg                                                   0x9801B57C
#define set_MIS_PCR_SCPU_CLK90K_HI_reg(data)   (*((volatile unsigned int*) MIS_PCR_SCPU_CLK90K_HI_reg)=data)
#define get_MIS_PCR_SCPU_CLK90K_HI_reg   (*((volatile unsigned int*) MIS_PCR_SCPU_CLK90K_HI_reg))
#define MIS_PCR_SCPU_CLK90K_HI_inst_adr                                              "0x005F"
#define MIS_PCR_SCPU_CLK90K_HI_inst                                                  0x005F
#define MIS_PCR_SCPU_CLK90K_HI_val_shift                                             (0)
#define MIS_PCR_SCPU_CLK90K_HI_val_mask                                              (0x0000FFFF)
#define MIS_PCR_SCPU_CLK90K_HI_val(data)                                             (0x0000FFFF&((data)<<0))
#define MIS_PCR_SCPU_CLK90K_HI_val_src(data)                                         ((0x0000FFFF&(data))>>0)
#define MIS_PCR_SCPU_CLK90K_HI_get_val(data)                                         ((0x0000FFFF&(data))>>0)


#define MIS_PCR_ACPU_CLK27M_90K                                                      0x9801B580
#define MIS_PCR_ACPU_CLK27M_90K_reg_addr                                             "0x9801B580"
#define MIS_PCR_ACPU_CLK27M_90K_reg                                                  0x9801B580
#define set_MIS_PCR_ACPU_CLK27M_90K_reg(data)   (*((volatile unsigned int*) MIS_PCR_ACPU_CLK27M_90K_reg)=data)
#define get_MIS_PCR_ACPU_CLK27M_90K_reg   (*((volatile unsigned int*) MIS_PCR_ACPU_CLK27M_90K_reg))
#define MIS_PCR_ACPU_CLK27M_90K_inst_adr                                             "0x0060"
#define MIS_PCR_ACPU_CLK27M_90K_inst                                                 0x0060
#define MIS_PCR_ACPU_CLK27M_90K_cnt_shift                                            (0)
#define MIS_PCR_ACPU_CLK27M_90K_cnt_mask                                             (0x000001FF)
#define MIS_PCR_ACPU_CLK27M_90K_cnt(data)                                            (0x000001FF&((data)<<0))
#define MIS_PCR_ACPU_CLK27M_90K_cnt_src(data)                                        ((0x000001FF&(data))>>0)
#define MIS_PCR_ACPU_CLK27M_90K_get_cnt(data)                                        ((0x000001FF&(data))>>0)


#define MIS_PCR_ACPU_CLK90K_LO                                                       0x9801B584
#define MIS_PCR_ACPU_CLK90K_LO_reg_addr                                              "0x9801B584"
#define MIS_PCR_ACPU_CLK90K_LO_reg                                                   0x9801B584
#define set_MIS_PCR_ACPU_CLK90K_LO_reg(data)   (*((volatile unsigned int*) MIS_PCR_ACPU_CLK90K_LO_reg)=data)
#define get_MIS_PCR_ACPU_CLK90K_LO_reg   (*((volatile unsigned int*) MIS_PCR_ACPU_CLK90K_LO_reg))
#define MIS_PCR_ACPU_CLK90K_LO_inst_adr                                              "0x0061"
#define MIS_PCR_ACPU_CLK90K_LO_inst                                                  0x0061
#define MIS_PCR_ACPU_CLK90K_LO_val_shift                                             (0)
#define MIS_PCR_ACPU_CLK90K_LO_val_mask                                              (0xFFFFFFFF)
#define MIS_PCR_ACPU_CLK90K_LO_val(data)                                             (0xFFFFFFFF&((data)<<0))
#define MIS_PCR_ACPU_CLK90K_LO_val_src(data)                                         ((0xFFFFFFFF&(data))>>0)
#define MIS_PCR_ACPU_CLK90K_LO_get_val(data)                                         ((0xFFFFFFFF&(data))>>0)


#define MIS_PCR_ACPU_CLK90K_HI                                                       0x9801B588
#define MIS_PCR_ACPU_CLK90K_HI_reg_addr                                              "0x9801B588"
#define MIS_PCR_ACPU_CLK90K_HI_reg                                                   0x9801B588
#define set_MIS_PCR_ACPU_CLK90K_HI_reg(data)   (*((volatile unsigned int*) MIS_PCR_ACPU_CLK90K_HI_reg)=data)
#define get_MIS_PCR_ACPU_CLK90K_HI_reg   (*((volatile unsigned int*) MIS_PCR_ACPU_CLK90K_HI_reg))
#define MIS_PCR_ACPU_CLK90K_HI_inst_adr                                              "0x0062"
#define MIS_PCR_ACPU_CLK90K_HI_inst                                                  0x0062
#define MIS_PCR_ACPU_CLK90K_HI_val_shift                                             (0)
#define MIS_PCR_ACPU_CLK90K_HI_val_mask                                              (0x0000FFFF)
#define MIS_PCR_ACPU_CLK90K_HI_val(data)                                             (0x0000FFFF&((data)<<0))
#define MIS_PCR_ACPU_CLK90K_HI_val_src(data)                                         ((0x0000FFFF&(data))>>0)
#define MIS_PCR_ACPU_CLK90K_HI_get_val(data)                                         ((0x0000FFFF&(data))>>0)


#define MIS_TCWCR                                                                    0x9801B5B0
#define MIS_TCWCR_reg_addr                                                           "0x9801B5B0"
#define MIS_TCWCR_reg                                                                0x9801B5B0
#define set_MIS_TCWCR_reg(data)   (*((volatile unsigned int*) MIS_TCWCR_reg)=data)
#define get_MIS_TCWCR_reg   (*((volatile unsigned int*) MIS_TCWCR_reg))
#define MIS_TCWCR_inst_adr                                                           "0x006C"
#define MIS_TCWCR_inst                                                               0x006C
#define MIS_TCWCR_wd_int_en_shift                                                    (31)
#define MIS_TCWCR_wd_int_en_mask                                                     (0x80000000)
#define MIS_TCWCR_wd_int_en(data)                                                    (0x80000000&((data)<<31))
#define MIS_TCWCR_wd_int_en_src(data)                                                ((0x80000000&(data))>>31)
#define MIS_TCWCR_get_wd_int_en(data)                                                ((0x80000000&(data))>>31)
#define MIS_TCWCR_nmic_shift                                                         (12)
#define MIS_TCWCR_nmic_mask                                                          (0x0000F000)
#define MIS_TCWCR_nmic(data)                                                         (0x0000F000&((data)<<12))
#define MIS_TCWCR_nmic_src(data)                                                     ((0x0000F000&(data))>>12)
#define MIS_TCWCR_get_nmic(data)                                                     ((0x0000F000&(data))>>12)
#define MIS_TCWCR_wdc_shift                                                          (8)
#define MIS_TCWCR_wdc_mask                                                           (0x00000F00)
#define MIS_TCWCR_wdc(data)                                                          (0x00000F00&((data)<<8))
#define MIS_TCWCR_wdc_src(data)                                                      ((0x00000F00&(data))>>8)
#define MIS_TCWCR_get_wdc(data)                                                      ((0x00000F00&(data))>>8)
#define MIS_TCWCR_wden_shift                                                         (0)
#define MIS_TCWCR_wden_mask                                                          (0x000000FF)
#define MIS_TCWCR_wden(data)                                                         (0x000000FF&((data)<<0))
#define MIS_TCWCR_wden_src(data)                                                     ((0x000000FF&(data))>>0)
#define MIS_TCWCR_get_wden(data)                                                     ((0x000000FF&(data))>>0)


#define MIS_TCWTR                                                                    0x9801B5B4
#define MIS_TCWTR_reg_addr                                                           "0x9801B5B4"
#define MIS_TCWTR_reg                                                                0x9801B5B4
#define set_MIS_TCWTR_reg(data)   (*((volatile unsigned int*) MIS_TCWTR_reg)=data)
#define get_MIS_TCWTR_reg   (*((volatile unsigned int*) MIS_TCWTR_reg))
#define MIS_TCWTR_inst_adr                                                           "0x006D"
#define MIS_TCWTR_inst                                                               0x006D
#define MIS_TCWTR_wdclr_shift                                                        (0)
#define MIS_TCWTR_wdclr_mask                                                         (0x00000001)
#define MIS_TCWTR_wdclr(data)                                                        (0x00000001&((data)<<0))
#define MIS_TCWTR_wdclr_src(data)                                                    ((0x00000001&(data))>>0)
#define MIS_TCWTR_get_wdclr(data)                                                    ((0x00000001&(data))>>0)


#define MIS_TCWNMI                                                                   0x9801B5B8
#define MIS_TCWNMI_reg_addr                                                          "0x9801B5B8"
#define MIS_TCWNMI_reg                                                               0x9801B5B8
#define set_MIS_TCWNMI_reg(data)   (*((volatile unsigned int*) MIS_TCWNMI_reg)=data)
#define get_MIS_TCWNMI_reg   (*((volatile unsigned int*) MIS_TCWNMI_reg))
#define MIS_TCWNMI_inst_adr                                                          "0x006E"
#define MIS_TCWNMI_inst                                                              0x006E
#define MIS_TCWNMI_sel_shift                                                         (0)
#define MIS_TCWNMI_sel_mask                                                          (0xFFFFFFFF)
#define MIS_TCWNMI_sel(data)                                                         (0xFFFFFFFF&((data)<<0))
#define MIS_TCWNMI_sel_src(data)                                                     ((0xFFFFFFFF&(data))>>0)
#define MIS_TCWNMI_get_sel(data)                                                     ((0xFFFFFFFF&(data))>>0)


#define MIS_TCWOV                                                                    0x9801B5BC
#define MIS_TCWOV_reg_addr                                                           "0x9801B5BC"
#define MIS_TCWOV_reg                                                                0x9801B5BC
#define set_MIS_TCWOV_reg(data)   (*((volatile unsigned int*) MIS_TCWOV_reg)=data)
#define get_MIS_TCWOV_reg   (*((volatile unsigned int*) MIS_TCWOV_reg))
#define MIS_TCWOV_inst_adr                                                           "0x006F"
#define MIS_TCWOV_inst                                                               0x006F
#define MIS_TCWOV_sel_shift                                                          (0)
#define MIS_TCWOV_sel_mask                                                           (0xFFFFFFFF)
#define MIS_TCWOV_sel(data)                                                          (0xFFFFFFFF&((data)<<0))
#define MIS_TCWOV_sel_src(data)                                                      ((0xFFFFFFFF&(data))>>0)
#define MIS_TCWOV_get_sel(data)                                                      ((0xFFFFFFFF&(data))>>0)


#define MIS_TCWCR_SWC                                                                0x9801B5C0
#define MIS_TCWCR_SWC_reg_addr                                                       "0x9801B5C0"
#define MIS_TCWCR_SWC_reg                                                            0x9801B5C0
#define set_MIS_TCWCR_SWC_reg(data)   (*((volatile unsigned int*) MIS_TCWCR_SWC_reg)=data)
#define get_MIS_TCWCR_SWC_reg   (*((volatile unsigned int*) MIS_TCWCR_SWC_reg))
#define MIS_TCWCR_SWC_inst_adr                                                       "0x0070"
#define MIS_TCWCR_SWC_inst                                                           0x0070
#define MIS_TCWCR_SWC_wd_int_en_shift                                                (31)
#define MIS_TCWCR_SWC_wd_int_en_mask                                                 (0x80000000)
#define MIS_TCWCR_SWC_wd_int_en(data)                                                (0x80000000&((data)<<31))
#define MIS_TCWCR_SWC_wd_int_en_src(data)                                            ((0x80000000&(data))>>31)
#define MIS_TCWCR_SWC_get_wd_int_en(data)                                            ((0x80000000&(data))>>31)
#define MIS_TCWCR_SWC_nmic_shift                                                     (12)
#define MIS_TCWCR_SWC_nmic_mask                                                      (0x0000F000)
#define MIS_TCWCR_SWC_nmic(data)                                                     (0x0000F000&((data)<<12))
#define MIS_TCWCR_SWC_nmic_src(data)                                                 ((0x0000F000&(data))>>12)
#define MIS_TCWCR_SWC_get_nmic(data)                                                 ((0x0000F000&(data))>>12)
#define MIS_TCWCR_SWC_wdc_shift                                                      (8)
#define MIS_TCWCR_SWC_wdc_mask                                                       (0x00000F00)
#define MIS_TCWCR_SWC_wdc(data)                                                      (0x00000F00&((data)<<8))
#define MIS_TCWCR_SWC_wdc_src(data)                                                  ((0x00000F00&(data))>>8)
#define MIS_TCWCR_SWC_get_wdc(data)                                                  ((0x00000F00&(data))>>8)
#define MIS_TCWCR_SWC_wden_shift                                                     (0)
#define MIS_TCWCR_SWC_wden_mask                                                      (0x000000FF)
#define MIS_TCWCR_SWC_wden(data)                                                     (0x000000FF&((data)<<0))
#define MIS_TCWCR_SWC_wden_src(data)                                                 ((0x000000FF&(data))>>0)
#define MIS_TCWCR_SWC_get_wden(data)                                                 ((0x000000FF&(data))>>0)


#define MIS_TCWTR_SWC                                                                0x9801B5C4
#define MIS_TCWTR_SWC_reg_addr                                                       "0x9801B5C4"
#define MIS_TCWTR_SWC_reg                                                            0x9801B5C4
#define set_MIS_TCWTR_SWC_reg(data)   (*((volatile unsigned int*) MIS_TCWTR_SWC_reg)=data)
#define get_MIS_TCWTR_SWC_reg   (*((volatile unsigned int*) MIS_TCWTR_SWC_reg))
#define MIS_TCWTR_SWC_inst_adr                                                       "0x0071"
#define MIS_TCWTR_SWC_inst                                                           0x0071
#define MIS_TCWTR_SWC_wdclr_shift                                                    (0)
#define MIS_TCWTR_SWC_wdclr_mask                                                     (0x00000001)
#define MIS_TCWTR_SWC_wdclr(data)                                                    (0x00000001&((data)<<0))
#define MIS_TCWTR_SWC_wdclr_src(data)                                                ((0x00000001&(data))>>0)
#define MIS_TCWTR_SWC_get_wdclr(data)                                                ((0x00000001&(data))>>0)


#define MIS_TCWNMI_SWC                                                               0x9801B5C8
#define MIS_TCWNMI_SWC_reg_addr                                                      "0x9801B5C8"
#define MIS_TCWNMI_SWC_reg                                                           0x9801B5C8
#define set_MIS_TCWNMI_SWC_reg(data)   (*((volatile unsigned int*) MIS_TCWNMI_SWC_reg)=data)
#define get_MIS_TCWNMI_SWC_reg   (*((volatile unsigned int*) MIS_TCWNMI_SWC_reg))
#define MIS_TCWNMI_SWC_inst_adr                                                      "0x0072"
#define MIS_TCWNMI_SWC_inst                                                          0x0072
#define MIS_TCWNMI_SWC_sel_shift                                                     (0)
#define MIS_TCWNMI_SWC_sel_mask                                                      (0xFFFFFFFF)
#define MIS_TCWNMI_SWC_sel(data)                                                     (0xFFFFFFFF&((data)<<0))
#define MIS_TCWNMI_SWC_sel_src(data)                                                 ((0xFFFFFFFF&(data))>>0)
#define MIS_TCWNMI_SWC_get_sel(data)                                                 ((0xFFFFFFFF&(data))>>0)


#define MIS_TCWOV_SWC                                                                0x9801B5CC
#define MIS_TCWOV_SWC_reg_addr                                                       "0x9801B5CC"
#define MIS_TCWOV_SWC_reg                                                            0x9801B5CC
#define set_MIS_TCWOV_SWC_reg(data)   (*((volatile unsigned int*) MIS_TCWOV_SWC_reg)=data)
#define get_MIS_TCWOV_SWC_reg   (*((volatile unsigned int*) MIS_TCWOV_SWC_reg))
#define MIS_TCWOV_SWC_inst_adr                                                       "0x0073"
#define MIS_TCWOV_SWC_inst                                                           0x0073
#define MIS_TCWOV_SWC_sel_shift                                                      (0)
#define MIS_TCWOV_SWC_sel_mask                                                       (0xFFFFFFFF)
#define MIS_TCWOV_SWC_sel(data)                                                      (0xFFFFFFFF&((data)<<0))
#define MIS_TCWOV_SWC_sel_src(data)                                                  ((0xFFFFFFFF&(data))>>0)
#define MIS_TCWOV_SWC_get_sel(data)                                                  ((0xFFFFFFFF&(data))>>0)


#define MIS_RTCSEC                                                                   0x9801B600
#define MIS_RTCSEC_reg_addr                                                          "0x9801B600"
#define MIS_RTCSEC_reg                                                               0x9801B600
#define set_MIS_RTCSEC_reg(data)   (*((volatile unsigned int*) MIS_RTCSEC_reg)=data)
#define get_MIS_RTCSEC_reg   (*((volatile unsigned int*) MIS_RTCSEC_reg))
#define MIS_RTCSEC_inst_adr                                                          "0x0080"
#define MIS_RTCSEC_inst                                                              0x0080
#define MIS_RTCSEC_rtcsec_shift                                                      (0)
#define MIS_RTCSEC_rtcsec_mask                                                       (0x0000007F)
#define MIS_RTCSEC_rtcsec(data)                                                      (0x0000007F&((data)<<0))
#define MIS_RTCSEC_rtcsec_src(data)                                                  ((0x0000007F&(data))>>0)
#define MIS_RTCSEC_get_rtcsec(data)                                                  ((0x0000007F&(data))>>0)


#define MIS_RTCMIN                                                                   0x9801B604
#define MIS_RTCMIN_reg_addr                                                          "0x9801B604"
#define MIS_RTCMIN_reg                                                               0x9801B604
#define set_MIS_RTCMIN_reg(data)   (*((volatile unsigned int*) MIS_RTCMIN_reg)=data)
#define get_MIS_RTCMIN_reg   (*((volatile unsigned int*) MIS_RTCMIN_reg))
#define MIS_RTCMIN_inst_adr                                                          "0x0081"
#define MIS_RTCMIN_inst                                                              0x0081
#define MIS_RTCMIN_rtcmin_shift                                                      (0)
#define MIS_RTCMIN_rtcmin_mask                                                       (0x0000003F)
#define MIS_RTCMIN_rtcmin(data)                                                      (0x0000003F&((data)<<0))
#define MIS_RTCMIN_rtcmin_src(data)                                                  ((0x0000003F&(data))>>0)
#define MIS_RTCMIN_get_rtcmin(data)                                                  ((0x0000003F&(data))>>0)


#define MIS_RTCHR                                                                    0x9801B608
#define MIS_RTCHR_reg_addr                                                           "0x9801B608"
#define MIS_RTCHR_reg                                                                0x9801B608
#define set_MIS_RTCHR_reg(data)   (*((volatile unsigned int*) MIS_RTCHR_reg)=data)
#define get_MIS_RTCHR_reg   (*((volatile unsigned int*) MIS_RTCHR_reg))
#define MIS_RTCHR_inst_adr                                                           "0x0082"
#define MIS_RTCHR_inst                                                               0x0082
#define MIS_RTCHR_rtchr_shift                                                        (0)
#define MIS_RTCHR_rtchr_mask                                                         (0x0000001F)
#define MIS_RTCHR_rtchr(data)                                                        (0x0000001F&((data)<<0))
#define MIS_RTCHR_rtchr_src(data)                                                    ((0x0000001F&(data))>>0)
#define MIS_RTCHR_get_rtchr(data)                                                    ((0x0000001F&(data))>>0)


#define MIS_RTCDATE1                                                                 0x9801B60C
#define MIS_RTCDATE1_reg_addr                                                        "0x9801B60C"
#define MIS_RTCDATE1_reg                                                             0x9801B60C
#define set_MIS_RTCDATE1_reg(data)   (*((volatile unsigned int*) MIS_RTCDATE1_reg)=data)
#define get_MIS_RTCDATE1_reg   (*((volatile unsigned int*) MIS_RTCDATE1_reg))
#define MIS_RTCDATE1_inst_adr                                                        "0x0083"
#define MIS_RTCDATE1_inst                                                            0x0083
#define MIS_RTCDATE1_rtcdate1_shift                                                  (0)
#define MIS_RTCDATE1_rtcdate1_mask                                                   (0x000000FF)
#define MIS_RTCDATE1_rtcdate1(data)                                                  (0x000000FF&((data)<<0))
#define MIS_RTCDATE1_rtcdate1_src(data)                                              ((0x000000FF&(data))>>0)
#define MIS_RTCDATE1_get_rtcdate1(data)                                              ((0x000000FF&(data))>>0)


#define MIS_RTCDATE2                                                                 0x9801B610
#define MIS_RTCDATE2_reg_addr                                                        "0x9801B610"
#define MIS_RTCDATE2_reg                                                             0x9801B610
#define set_MIS_RTCDATE2_reg(data)   (*((volatile unsigned int*) MIS_RTCDATE2_reg)=data)
#define get_MIS_RTCDATE2_reg   (*((volatile unsigned int*) MIS_RTCDATE2_reg))
#define MIS_RTCDATE2_inst_adr                                                        "0x0084"
#define MIS_RTCDATE2_inst                                                            0x0084
#define MIS_RTCDATE2_rtcdate2_shift                                                  (0)
#define MIS_RTCDATE2_rtcdate2_mask                                                   (0x0000007F)
#define MIS_RTCDATE2_rtcdate2(data)                                                  (0x0000007F&((data)<<0))
#define MIS_RTCDATE2_rtcdate2_src(data)                                              ((0x0000007F&(data))>>0)
#define MIS_RTCDATE2_get_rtcdate2(data)                                              ((0x0000007F&(data))>>0)


#define MIS_ALMMIN                                                                   0x9801B614
#define MIS_ALMMIN_reg_addr                                                          "0x9801B614"
#define MIS_ALMMIN_reg                                                               0x9801B614
#define set_MIS_ALMMIN_reg(data)   (*((volatile unsigned int*) MIS_ALMMIN_reg)=data)
#define get_MIS_ALMMIN_reg   (*((volatile unsigned int*) MIS_ALMMIN_reg))
#define MIS_ALMMIN_inst_adr                                                          "0x0085"
#define MIS_ALMMIN_inst                                                              0x0085
#define MIS_ALMMIN_almmin_shift                                                      (0)
#define MIS_ALMMIN_almmin_mask                                                       (0x0000003F)
#define MIS_ALMMIN_almmin(data)                                                      (0x0000003F&((data)<<0))
#define MIS_ALMMIN_almmin_src(data)                                                  ((0x0000003F&(data))>>0)
#define MIS_ALMMIN_get_almmin(data)                                                  ((0x0000003F&(data))>>0)


#define MIS_ALMHR                                                                    0x9801B618
#define MIS_ALMHR_reg_addr                                                           "0x9801B618"
#define MIS_ALMHR_reg                                                                0x9801B618
#define set_MIS_ALMHR_reg(data)   (*((volatile unsigned int*) MIS_ALMHR_reg)=data)
#define get_MIS_ALMHR_reg   (*((volatile unsigned int*) MIS_ALMHR_reg))
#define MIS_ALMHR_inst_adr                                                           "0x0086"
#define MIS_ALMHR_inst                                                               0x0086
#define MIS_ALMHR_almhr_shift                                                        (0)
#define MIS_ALMHR_almhr_mask                                                         (0x0000001F)
#define MIS_ALMHR_almhr(data)                                                        (0x0000001F&((data)<<0))
#define MIS_ALMHR_almhr_src(data)                                                    ((0x0000001F&(data))>>0)
#define MIS_ALMHR_get_almhr(data)                                                    ((0x0000001F&(data))>>0)


#define MIS_ALMDATE1                                                                 0x9801B61C
#define MIS_ALMDATE1_reg_addr                                                        "0x9801B61C"
#define MIS_ALMDATE1_reg                                                             0x9801B61C
#define set_MIS_ALMDATE1_reg(data)   (*((volatile unsigned int*) MIS_ALMDATE1_reg)=data)
#define get_MIS_ALMDATE1_reg   (*((volatile unsigned int*) MIS_ALMDATE1_reg))
#define MIS_ALMDATE1_inst_adr                                                        "0x0087"
#define MIS_ALMDATE1_inst                                                            0x0087
#define MIS_ALMDATE1_almdate1_shift                                                  (0)
#define MIS_ALMDATE1_almdate1_mask                                                   (0x000000FF)
#define MIS_ALMDATE1_almdate1(data)                                                  (0x000000FF&((data)<<0))
#define MIS_ALMDATE1_almdate1_src(data)                                              ((0x000000FF&(data))>>0)
#define MIS_ALMDATE1_get_almdate1(data)                                              ((0x000000FF&(data))>>0)


#define MIS_ALMDATE2                                                                 0x9801B620
#define MIS_ALMDATE2_reg_addr                                                        "0x9801B620"
#define MIS_ALMDATE2_reg                                                             0x9801B620
#define set_MIS_ALMDATE2_reg(data)   (*((volatile unsigned int*) MIS_ALMDATE2_reg)=data)
#define get_MIS_ALMDATE2_reg   (*((volatile unsigned int*) MIS_ALMDATE2_reg))
#define MIS_ALMDATE2_inst_adr                                                        "0x0088"
#define MIS_ALMDATE2_inst                                                            0x0088
#define MIS_ALMDATE2_almdate2_shift                                                  (0)
#define MIS_ALMDATE2_almdate2_mask                                                   (0x0000007F)
#define MIS_ALMDATE2_almdate2(data)                                                  (0x0000007F&((data)<<0))
#define MIS_ALMDATE2_almdate2_src(data)                                              ((0x0000007F&(data))>>0)
#define MIS_ALMDATE2_get_almdate2(data)                                              ((0x0000007F&(data))>>0)


#define MIS_RTCSTOP                                                                  0x9801B624
#define MIS_RTCSTOP_reg_addr                                                         "0x9801B624"
#define MIS_RTCSTOP_reg                                                              0x9801B624
#define set_MIS_RTCSTOP_reg(data)   (*((volatile unsigned int*) MIS_RTCSTOP_reg)=data)
#define get_MIS_RTCSTOP_reg   (*((volatile unsigned int*) MIS_RTCSTOP_reg))
#define MIS_RTCSTOP_inst_adr                                                         "0x0089"
#define MIS_RTCSTOP_inst                                                             0x0089
#define MIS_RTCSTOP_vref_shift                                                       (1)
#define MIS_RTCSTOP_vref_mask                                                        (0x00000006)
#define MIS_RTCSTOP_vref(data)                                                       (0x00000006&((data)<<1))
#define MIS_RTCSTOP_vref_src(data)                                                   ((0x00000006&(data))>>1)
#define MIS_RTCSTOP_get_vref(data)                                                   ((0x00000006&(data))>>1)
#define MIS_RTCSTOP_rtcstop_shift                                                    (0)
#define MIS_RTCSTOP_rtcstop_mask                                                     (0x00000001)
#define MIS_RTCSTOP_rtcstop(data)                                                    (0x00000001&((data)<<0))
#define MIS_RTCSTOP_rtcstop_src(data)                                                ((0x00000001&(data))>>0)
#define MIS_RTCSTOP_get_rtcstop(data)                                                ((0x00000001&(data))>>0)


#define MIS_RTCACR                                                                   0x9801B628
#define MIS_RTCACR_reg_addr                                                          "0x9801B628"
#define MIS_RTCACR_reg                                                               0x9801B628
#define set_MIS_RTCACR_reg(data)   (*((volatile unsigned int*) MIS_RTCACR_reg)=data)
#define get_MIS_RTCACR_reg   (*((volatile unsigned int*) MIS_RTCACR_reg))
#define MIS_RTCACR_inst_adr                                                          "0x008A"
#define MIS_RTCACR_inst                                                              0x008A
#define MIS_RTCACR_rtcpwr_shift                                                      (7)
#define MIS_RTCACR_rtcpwr_mask                                                       (0x00000080)
#define MIS_RTCACR_rtcpwr(data)                                                      (0x00000080&((data)<<7))
#define MIS_RTCACR_rtcpwr_src(data)                                                  ((0x00000080&(data))>>7)
#define MIS_RTCACR_get_rtcpwr(data)                                                  ((0x00000080&(data))>>7)
#define MIS_RTCACR_co_shift                                                          (5)
#define MIS_RTCACR_co_mask                                                           (0x00000060)
#define MIS_RTCACR_co(data)                                                          (0x00000060&((data)<<5))
#define MIS_RTCACR_co_src(data)                                                      ((0x00000060&(data))>>5)
#define MIS_RTCACR_get_co(data)                                                      ((0x00000060&(data))>>5)
#define MIS_RTCACR_ci_shift                                                          (3)
#define MIS_RTCACR_ci_mask                                                           (0x00000018)
#define MIS_RTCACR_ci(data)                                                          (0x00000018&((data)<<3))
#define MIS_RTCACR_ci_src(data)                                                      ((0x00000018&(data))>>3)
#define MIS_RTCACR_get_ci(data)                                                      ((0x00000018&(data))>>3)
#define MIS_RTCACR_clksel_shift                                                      (2)
#define MIS_RTCACR_clksel_mask                                                       (0x00000004)
#define MIS_RTCACR_clksel(data)                                                      (0x00000004&((data)<<2))
#define MIS_RTCACR_clksel_src(data)                                                  ((0x00000004&(data))>>2)
#define MIS_RTCACR_get_clksel(data)                                                  ((0x00000004&(data))>>2)
#define MIS_RTCACR_bc_shift                                                          (0)
#define MIS_RTCACR_bc_mask                                                           (0x00000003)
#define MIS_RTCACR_bc(data)                                                          (0x00000003&((data)<<0))
#define MIS_RTCACR_bc_src(data)                                                      ((0x00000003&(data))>>0)
#define MIS_RTCACR_get_bc(data)                                                      ((0x00000003&(data))>>0)


#define MIS_RTCEN                                                                    0x9801B62C
#define MIS_RTCEN_reg_addr                                                           "0x9801B62C"
#define MIS_RTCEN_reg                                                                0x9801B62C
#define set_MIS_RTCEN_reg(data)   (*((volatile unsigned int*) MIS_RTCEN_reg)=data)
#define get_MIS_RTCEN_reg   (*((volatile unsigned int*) MIS_RTCEN_reg))
#define MIS_RTCEN_inst_adr                                                           "0x008B"
#define MIS_RTCEN_inst                                                               0x008B
#define MIS_RTCEN_rtcen_shift                                                        (0)
#define MIS_RTCEN_rtcen_mask                                                         (0x000000FF)
#define MIS_RTCEN_rtcen(data)                                                        (0x000000FF&((data)<<0))
#define MIS_RTCEN_rtcen_src(data)                                                    ((0x000000FF&(data))>>0)
#define MIS_RTCEN_get_rtcen(data)                                                    ((0x000000FF&(data))>>0)


#define MIS_RTCCR                                                                    0x9801B630
#define MIS_RTCCR_reg_addr                                                           "0x9801B630"
#define MIS_RTCCR_reg                                                                0x9801B630
#define set_MIS_RTCCR_reg(data)   (*((volatile unsigned int*) MIS_RTCCR_reg)=data)
#define get_MIS_RTCCR_reg   (*((volatile unsigned int*) MIS_RTCCR_reg))
#define MIS_RTCCR_inst_adr                                                           "0x008C"
#define MIS_RTCCR_inst                                                               0x008C
#define MIS_RTCCR_rtcrst_shift                                                       (6)
#define MIS_RTCCR_rtcrst_mask                                                        (0x00000040)
#define MIS_RTCCR_rtcrst(data)                                                       (0x00000040&((data)<<6))
#define MIS_RTCCR_rtcrst_src(data)                                                   ((0x00000040&(data))>>6)
#define MIS_RTCCR_get_rtcrst(data)                                                   ((0x00000040&(data))>>6)
#define MIS_RTCCR_dainte_shift                                                       (3)
#define MIS_RTCCR_dainte_mask                                                        (0x00000008)
#define MIS_RTCCR_dainte(data)                                                       (0x00000008&((data)<<3))
#define MIS_RTCCR_dainte_src(data)                                                   ((0x00000008&(data))>>3)
#define MIS_RTCCR_get_dainte(data)                                                   ((0x00000008&(data))>>3)
#define MIS_RTCCR_huinte_shift                                                       (2)
#define MIS_RTCCR_huinte_mask                                                        (0x00000004)
#define MIS_RTCCR_huinte(data)                                                       (0x00000004&((data)<<2))
#define MIS_RTCCR_huinte_src(data)                                                   ((0x00000004&(data))>>2)
#define MIS_RTCCR_get_huinte(data)                                                   ((0x00000004&(data))>>2)
#define MIS_RTCCR_muinte_shift                                                       (1)
#define MIS_RTCCR_muinte_mask                                                        (0x00000002)
#define MIS_RTCCR_muinte(data)                                                       (0x00000002&((data)<<1))
#define MIS_RTCCR_muinte_src(data)                                                   ((0x00000002&(data))>>1)
#define MIS_RTCCR_get_muinte(data)                                                   ((0x00000002&(data))>>1)
#define MIS_RTCCR_hsuinte_shift                                                      (0)
#define MIS_RTCCR_hsuinte_mask                                                       (0x00000001)
#define MIS_RTCCR_hsuinte(data)                                                      (0x00000001&((data)<<0))
#define MIS_RTCCR_hsuinte_src(data)                                                  ((0x00000001&(data))>>0)
#define MIS_RTCCR_get_hsuinte(data)                                                  ((0x00000001&(data))>>0)


#define MIS_FAN_CTRL                                                                 0x9801BC00
#define MIS_FAN_CTRL_reg_addr                                                        "0x9801BC00"
#define MIS_FAN_CTRL_reg                                                             0x9801BC00
#define set_MIS_FAN_CTRL_reg(data)   (*((volatile unsigned int*) MIS_FAN_CTRL_reg)=data)
#define get_MIS_FAN_CTRL_reg   (*((volatile unsigned int*) MIS_FAN_CTRL_reg))
#define MIS_FAN_CTRL_inst_adr                                                        "0x0000"
#define MIS_FAN_CTRL_inst                                                            0x0000
#define MIS_FAN_CTRL_int_en_shift                                                    (1)
#define MIS_FAN_CTRL_int_en_mask                                                     (0x00000002)
#define MIS_FAN_CTRL_int_en(data)                                                    (0x00000002&((data)<<1))
#define MIS_FAN_CTRL_int_en_src(data)                                                ((0x00000002&(data))>>1)
#define MIS_FAN_CTRL_get_int_en(data)                                                ((0x00000002&(data))>>1)
#define MIS_FAN_CTRL_en_shift                                                        (0)
#define MIS_FAN_CTRL_en_mask                                                         (0x00000001)
#define MIS_FAN_CTRL_en(data)                                                        (0x00000001&((data)<<0))
#define MIS_FAN_CTRL_en_src(data)                                                    ((0x00000001&(data))>>0)
#define MIS_FAN_CTRL_get_en(data)                                                    ((0x00000001&(data))>>0)


#define MIS_FAN_DEBOUNCE                                                             0x9801BC04
#define MIS_FAN_DEBOUNCE_reg_addr                                                    "0x9801BC04"
#define MIS_FAN_DEBOUNCE_reg                                                         0x9801BC04
#define set_MIS_FAN_DEBOUNCE_reg(data)   (*((volatile unsigned int*) MIS_FAN_DEBOUNCE_reg)=data)
#define get_MIS_FAN_DEBOUNCE_reg   (*((volatile unsigned int*) MIS_FAN_DEBOUNCE_reg))
#define MIS_FAN_DEBOUNCE_inst_adr                                                    "0x0001"
#define MIS_FAN_DEBOUNCE_inst                                                        0x0001
#define MIS_FAN_DEBOUNCE_write_en1_shift                                             (3)
#define MIS_FAN_DEBOUNCE_write_en1_mask                                              (0x00000008)
#define MIS_FAN_DEBOUNCE_write_en1(data)                                             (0x00000008&((data)<<3))
#define MIS_FAN_DEBOUNCE_write_en1_src(data)                                         ((0x00000008&(data))>>3)
#define MIS_FAN_DEBOUNCE_get_write_en1(data)                                         ((0x00000008&(data))>>3)
#define MIS_FAN_DEBOUNCE_clk_shift                                                   (0)
#define MIS_FAN_DEBOUNCE_clk_mask                                                    (0x00000007)
#define MIS_FAN_DEBOUNCE_clk(data)                                                   (0x00000007&((data)<<0))
#define MIS_FAN_DEBOUNCE_clk_src(data)                                               ((0x00000007&(data))>>0)
#define MIS_FAN_DEBOUNCE_get_clk(data)                                               ((0x00000007&(data))>>0)


#define MIS_FAN_TIMER_TV                                                             0x9801BC08
#define MIS_FAN_TIMER_TV_reg_addr                                                    "0x9801BC08"
#define MIS_FAN_TIMER_TV_reg                                                         0x9801BC08
#define set_MIS_FAN_TIMER_TV_reg(data)   (*((volatile unsigned int*) MIS_FAN_TIMER_TV_reg)=data)
#define get_MIS_FAN_TIMER_TV_reg   (*((volatile unsigned int*) MIS_FAN_TIMER_TV_reg))
#define MIS_FAN_TIMER_TV_inst_adr                                                    "0x0002"
#define MIS_FAN_TIMER_TV_inst                                                        0x0002
#define MIS_FAN_TIMER_TV_tar_val_shift                                               (0)
#define MIS_FAN_TIMER_TV_tar_val_mask                                                (0xFFFFFFFF)
#define MIS_FAN_TIMER_TV_tar_val(data)                                               (0xFFFFFFFF&((data)<<0))
#define MIS_FAN_TIMER_TV_tar_val_src(data)                                           ((0xFFFFFFFF&(data))>>0)
#define MIS_FAN_TIMER_TV_get_tar_val(data)                                           ((0xFFFFFFFF&(data))>>0)


#define MIS_FAN_TIMER_CV                                                             0x9801BC0C
#define MIS_FAN_TIMER_CV_reg_addr                                                    "0x9801BC0C"
#define MIS_FAN_TIMER_CV_reg                                                         0x9801BC0C
#define set_MIS_FAN_TIMER_CV_reg(data)   (*((volatile unsigned int*) MIS_FAN_TIMER_CV_reg)=data)
#define get_MIS_FAN_TIMER_CV_reg   (*((volatile unsigned int*) MIS_FAN_TIMER_CV_reg))
#define MIS_FAN_TIMER_CV_inst_adr                                                    "0x0003"
#define MIS_FAN_TIMER_CV_inst                                                        0x0003
#define MIS_FAN_TIMER_CV_cnt_val_shift                                               (0)
#define MIS_FAN_TIMER_CV_cnt_val_mask                                                (0xFFFFFFFF)
#define MIS_FAN_TIMER_CV_cnt_val(data)                                               (0xFFFFFFFF&((data)<<0))
#define MIS_FAN_TIMER_CV_cnt_val_src(data)                                           ((0xFFFFFFFF&(data))>>0)
#define MIS_FAN_TIMER_CV_get_cnt_val(data)                                           ((0xFFFFFFFF&(data))>>0)


#define MIS_FAN_COUNTER_CV                                                           0x9801BC10
#define MIS_FAN_COUNTER_CV_reg_addr                                                  "0x9801BC10"
#define MIS_FAN_COUNTER_CV_reg                                                       0x9801BC10
#define set_MIS_FAN_COUNTER_CV_reg(data)   (*((volatile unsigned int*) MIS_FAN_COUNTER_CV_reg)=data)
#define get_MIS_FAN_COUNTER_CV_reg   (*((volatile unsigned int*) MIS_FAN_COUNTER_CV_reg))
#define MIS_FAN_COUNTER_CV_inst_adr                                                  "0x0004"
#define MIS_FAN_COUNTER_CV_inst                                                      0x0004
#define MIS_FAN_COUNTER_CV_cnt_val_shift                                             (0)
#define MIS_FAN_COUNTER_CV_cnt_val_mask                                              (0xFFFFFFFF)
#define MIS_FAN_COUNTER_CV_cnt_val(data)                                             (0xFFFFFFFF&((data)<<0))
#define MIS_FAN_COUNTER_CV_cnt_val_src(data)                                         ((0xFFFFFFFF&(data))>>0)
#define MIS_FAN_COUNTER_CV_get_cnt_val(data)                                         ((0xFFFFFFFF&(data))>>0)


#define MIS_SC0_FP                                                                   0x9801BE00
#define MIS_SC0_FP_reg_addr                                                          "0x9801BE00"
#define MIS_SC0_FP_reg                                                               0x9801BE00
#define set_MIS_SC0_FP_reg(data)   (*((volatile unsigned int*) MIS_SC0_FP_reg)=data)
#define get_MIS_SC0_FP_reg   (*((volatile unsigned int*) MIS_SC0_FP_reg))
#define MIS_SC0_FP_inst_adr                                                          "0x0080"
#define MIS_SC0_FP_inst                                                              0x0080
#define MIS_SC0_FP_clk_en_shift                                                      (24)
#define MIS_SC0_FP_clk_en_mask                                                       (0x01000000)
#define MIS_SC0_FP_clk_en(data)                                                      (0x01000000&((data)<<24))
#define MIS_SC0_FP_clk_en_src(data)                                                  ((0x01000000&(data))>>24)
#define MIS_SC0_FP_get_clk_en(data)                                                  ((0x01000000&(data))>>24)
#define MIS_SC0_FP_sc_clkdiv_shift                                                   (18)
#define MIS_SC0_FP_sc_clkdiv_mask                                                    (0x00FC0000)
#define MIS_SC0_FP_sc_clkdiv(data)                                                   (0x00FC0000&((data)<<18))
#define MIS_SC0_FP_sc_clkdiv_src(data)                                               ((0x00FC0000&(data))>>18)
#define MIS_SC0_FP_get_sc_clkdiv(data)                                               ((0x00FC0000&(data))>>18)
#define MIS_SC0_FP_bauddiv2_shift                                                    (16)
#define MIS_SC0_FP_bauddiv2_mask                                                     (0x00030000)
#define MIS_SC0_FP_bauddiv2(data)                                                    (0x00030000&((data)<<16))
#define MIS_SC0_FP_bauddiv2_src(data)                                                ((0x00030000&(data))>>16)
#define MIS_SC0_FP_get_bauddiv2(data)                                                ((0x00030000&(data))>>16)
#define MIS_SC0_FP_bauddiv1_shift                                                    (8)
#define MIS_SC0_FP_bauddiv1_mask                                                     (0x0000FF00)
#define MIS_SC0_FP_bauddiv1(data)                                                    (0x0000FF00&((data)<<8))
#define MIS_SC0_FP_bauddiv1_src(data)                                                ((0x0000FF00&(data))>>8)
#define MIS_SC0_FP_get_bauddiv1(data)                                                ((0x0000FF00&(data))>>8)
#define MIS_SC0_FP_pre_clkdiv_shift                                                  (0)
#define MIS_SC0_FP_pre_clkdiv_mask                                                   (0x000000FF)
#define MIS_SC0_FP_pre_clkdiv(data)                                                  (0x000000FF&((data)<<0))
#define MIS_SC0_FP_pre_clkdiv_src(data)                                              ((0x000000FF&(data))>>0)
#define MIS_SC0_FP_get_pre_clkdiv(data)                                              ((0x000000FF&(data))>>0)


#define MIS_SC0_CR                                                                   0x9801BE04
#define MIS_SC0_CR_reg_addr                                                          "0x9801BE04"
#define MIS_SC0_CR_reg                                                               0x9801BE04
#define set_MIS_SC0_CR_reg(data)   (*((volatile unsigned int*) MIS_SC0_CR_reg)=data)
#define get_MIS_SC0_CR_reg   (*((volatile unsigned int*) MIS_SC0_CR_reg))
#define MIS_SC0_CR_inst_adr                                                          "0x0081"
#define MIS_SC0_CR_inst                                                              0x0081
#define MIS_SC0_CR_fifo_rst_shift                                                    (31)
#define MIS_SC0_CR_fifo_rst_mask                                                     (0x80000000)
#define MIS_SC0_CR_fifo_rst(data)                                                    (0x80000000&((data)<<31))
#define MIS_SC0_CR_fifo_rst_src(data)                                                ((0x80000000&(data))>>31)
#define MIS_SC0_CR_get_fifo_rst(data)                                                ((0x80000000&(data))>>31)
#define MIS_SC0_CR_rst_shift                                                         (30)
#define MIS_SC0_CR_rst_mask                                                          (0x40000000)
#define MIS_SC0_CR_rst(data)                                                         (0x40000000&((data)<<30))
#define MIS_SC0_CR_rst_src(data)                                                     ((0x40000000&(data))>>30)
#define MIS_SC0_CR_get_rst(data)                                                     ((0x40000000&(data))>>30)
#define MIS_SC0_CR_scen_shift                                                        (29)
#define MIS_SC0_CR_scen_mask                                                         (0x20000000)
#define MIS_SC0_CR_scen(data)                                                        (0x20000000&((data)<<29))
#define MIS_SC0_CR_scen_src(data)                                                    ((0x20000000&(data))>>29)
#define MIS_SC0_CR_get_scen(data)                                                    ((0x20000000&(data))>>29)
#define MIS_SC0_CR_tx_go_shift                                                       (28)
#define MIS_SC0_CR_tx_go_mask                                                        (0x10000000)
#define MIS_SC0_CR_tx_go(data)                                                       (0x10000000&((data)<<28))
#define MIS_SC0_CR_tx_go_src(data)                                                   ((0x10000000&(data))>>28)
#define MIS_SC0_CR_get_tx_go(data)                                                   ((0x10000000&(data))>>28)
#define MIS_SC0_CR_auto_atr_shift                                                    (27)
#define MIS_SC0_CR_auto_atr_mask                                                     (0x08000000)
#define MIS_SC0_CR_auto_atr(data)                                                    (0x08000000&((data)<<27))
#define MIS_SC0_CR_auto_atr_src(data)                                                ((0x08000000&(data))>>27)
#define MIS_SC0_CR_get_auto_atr(data)                                                ((0x08000000&(data))>>27)
#define MIS_SC0_CR_conv_shift                                                        (26)
#define MIS_SC0_CR_conv_mask                                                         (0x04000000)
#define MIS_SC0_CR_conv(data)                                                        (0x04000000&((data)<<26))
#define MIS_SC0_CR_conv_src(data)                                                    ((0x04000000&(data))>>26)
#define MIS_SC0_CR_get_conv(data)                                                    ((0x04000000&(data))>>26)
#define MIS_SC0_CR_clk_stop_shift                                                    (25)
#define MIS_SC0_CR_clk_stop_mask                                                     (0x02000000)
#define MIS_SC0_CR_clk_stop(data)                                                    (0x02000000&((data)<<25))
#define MIS_SC0_CR_clk_stop_src(data)                                                ((0x02000000&(data))>>25)
#define MIS_SC0_CR_get_clk_stop(data)                                                ((0x02000000&(data))>>25)
#define MIS_SC0_CR_ps_shift                                                          (24)
#define MIS_SC0_CR_ps_mask                                                           (0x01000000)
#define MIS_SC0_CR_ps(data)                                                          (0x01000000&((data)<<24))
#define MIS_SC0_CR_ps_src(data)                                                      ((0x01000000&(data))>>24)
#define MIS_SC0_CR_get_ps(data)                                                      ((0x01000000&(data))>>24)


#define MIS_SC0_PCR                                                                  0x9801BE08
#define MIS_SC0_PCR_reg_addr                                                         "0x9801BE08"
#define MIS_SC0_PCR_reg                                                              0x9801BE08
#define set_MIS_SC0_PCR_reg(data)   (*((volatile unsigned int*) MIS_SC0_PCR_reg)=data)
#define get_MIS_SC0_PCR_reg   (*((volatile unsigned int*) MIS_SC0_PCR_reg))
#define MIS_SC0_PCR_inst_adr                                                         "0x0082"
#define MIS_SC0_PCR_inst                                                             0x0082
#define MIS_SC0_PCR_txgrdt_shift                                                     (24)
#define MIS_SC0_PCR_txgrdt_mask                                                      (0xFF000000)
#define MIS_SC0_PCR_txgrdt(data)                                                     (0xFF000000&((data)<<24))
#define MIS_SC0_PCR_txgrdt_src(data)                                                 ((0xFF000000&(data))>>24)
#define MIS_SC0_PCR_get_txgrdt(data)                                                 ((0xFF000000&(data))>>24)
#define MIS_SC0_PCR_cwi_shift                                                        (20)
#define MIS_SC0_PCR_cwi_mask                                                         (0x00F00000)
#define MIS_SC0_PCR_cwi(data)                                                        (0x00F00000&((data)<<20))
#define MIS_SC0_PCR_cwi_src(data)                                                    ((0x00F00000&(data))>>20)
#define MIS_SC0_PCR_get_cwi(data)                                                    ((0x00F00000&(data))>>20)
#define MIS_SC0_PCR_bwi_shift                                                        (16)
#define MIS_SC0_PCR_bwi_mask                                                         (0x000F0000)
#define MIS_SC0_PCR_bwi(data)                                                        (0x000F0000&((data)<<16))
#define MIS_SC0_PCR_bwi_src(data)                                                    ((0x000F0000&(data))>>16)
#define MIS_SC0_PCR_get_bwi(data)                                                    ((0x000F0000&(data))>>16)
#define MIS_SC0_PCR_wwi_shift                                                        (12)
#define MIS_SC0_PCR_wwi_mask                                                         (0x0000F000)
#define MIS_SC0_PCR_wwi(data)                                                        (0x0000F000&((data)<<12))
#define MIS_SC0_PCR_wwi_src(data)                                                    ((0x0000F000&(data))>>12)
#define MIS_SC0_PCR_get_wwi(data)                                                    ((0x0000F000&(data))>>12)
#define MIS_SC0_PCR_bgt_shift                                                        (7)
#define MIS_SC0_PCR_bgt_mask                                                         (0x00000F80)
#define MIS_SC0_PCR_bgt(data)                                                        (0x00000F80&((data)<<7))
#define MIS_SC0_PCR_bgt_src(data)                                                    ((0x00000F80&(data))>>7)
#define MIS_SC0_PCR_get_bgt(data)                                                    ((0x00000F80&(data))>>7)
#define MIS_SC0_PCR_edc_en_shift                                                     (6)
#define MIS_SC0_PCR_edc_en_mask                                                      (0x00000040)
#define MIS_SC0_PCR_edc_en(data)                                                     (0x00000040&((data)<<6))
#define MIS_SC0_PCR_edc_en_src(data)                                                 ((0x00000040&(data))>>6)
#define MIS_SC0_PCR_get_edc_en(data)                                                 ((0x00000040&(data))>>6)
#define MIS_SC0_PCR_crc_shift                                                        (5)
#define MIS_SC0_PCR_crc_mask                                                         (0x00000020)
#define MIS_SC0_PCR_crc(data)                                                        (0x00000020&((data)<<5))
#define MIS_SC0_PCR_crc_src(data)                                                    ((0x00000020&(data))>>5)
#define MIS_SC0_PCR_get_crc(data)                                                    ((0x00000020&(data))>>5)
#define MIS_SC0_PCR_protocol_t_shift                                                 (4)
#define MIS_SC0_PCR_protocol_t_mask                                                  (0x00000010)
#define MIS_SC0_PCR_protocol_t(data)                                                 (0x00000010&((data)<<4))
#define MIS_SC0_PCR_protocol_t_src(data)                                             ((0x00000010&(data))>>4)
#define MIS_SC0_PCR_get_protocol_t(data)                                             ((0x00000010&(data))>>4)
#define MIS_SC0_PCR_t0rty_shift                                                      (3)
#define MIS_SC0_PCR_t0rty_mask                                                       (0x00000008)
#define MIS_SC0_PCR_t0rty(data)                                                      (0x00000008&((data)<<3))
#define MIS_SC0_PCR_t0rty_src(data)                                                  ((0x00000008&(data))>>3)
#define MIS_SC0_PCR_get_t0rty(data)                                                  ((0x00000008&(data))>>3)
#define MIS_SC0_PCR_t0rty_cnt_shift                                                  (0)
#define MIS_SC0_PCR_t0rty_cnt_mask                                                   (0x00000007)
#define MIS_SC0_PCR_t0rty_cnt(data)                                                  (0x00000007&((data)<<0))
#define MIS_SC0_PCR_t0rty_cnt_src(data)                                              ((0x00000007&(data))>>0)
#define MIS_SC0_PCR_get_t0rty_cnt(data)                                              ((0x00000007&(data))>>0)


#define MIS_SC0_TXFIFO                                                               0x9801BE0C
#define MIS_SC0_TXFIFO_reg_addr                                                      "0x9801BE0C"
#define MIS_SC0_TXFIFO_reg                                                           0x9801BE0C
#define set_MIS_SC0_TXFIFO_reg(data)   (*((volatile unsigned int*) MIS_SC0_TXFIFO_reg)=data)
#define get_MIS_SC0_TXFIFO_reg   (*((volatile unsigned int*) MIS_SC0_TXFIFO_reg))
#define MIS_SC0_TXFIFO_inst_adr                                                      "0x0083"
#define MIS_SC0_TXFIFO_inst                                                          0x0083
#define MIS_SC0_TXFIFO_tx_fifo_full_shift                                            (8)
#define MIS_SC0_TXFIFO_tx_fifo_full_mask                                             (0x00000100)
#define MIS_SC0_TXFIFO_tx_fifo_full(data)                                            (0x00000100&((data)<<8))
#define MIS_SC0_TXFIFO_tx_fifo_full_src(data)                                        ((0x00000100&(data))>>8)
#define MIS_SC0_TXFIFO_get_tx_fifo_full(data)                                        ((0x00000100&(data))>>8)
#define MIS_SC0_TXFIFO_dat_shift                                                     (0)
#define MIS_SC0_TXFIFO_dat_mask                                                      (0x000000FF)
#define MIS_SC0_TXFIFO_dat(data)                                                     (0x000000FF&((data)<<0))
#define MIS_SC0_TXFIFO_dat_src(data)                                                 ((0x000000FF&(data))>>0)
#define MIS_SC0_TXFIFO_get_dat(data)                                                 ((0x000000FF&(data))>>0)


#define MIS_SC0_RXFIFO                                                               0x9801BE14
#define MIS_SC0_RXFIFO_reg_addr                                                      "0x9801BE14"
#define MIS_SC0_RXFIFO_reg                                                           0x9801BE14
#define set_MIS_SC0_RXFIFO_reg(data)   (*((volatile unsigned int*) MIS_SC0_RXFIFO_reg)=data)
#define get_MIS_SC0_RXFIFO_reg   (*((volatile unsigned int*) MIS_SC0_RXFIFO_reg))
#define MIS_SC0_RXFIFO_inst_adr                                                      "0x0085"
#define MIS_SC0_RXFIFO_inst                                                          0x0085
#define MIS_SC0_RXFIFO_dat_shift                                                     (0)
#define MIS_SC0_RXFIFO_dat_mask                                                      (0x000000FF)
#define MIS_SC0_RXFIFO_dat(data)                                                     (0x000000FF&((data)<<0))
#define MIS_SC0_RXFIFO_dat_src(data)                                                 ((0x000000FF&(data))>>0)
#define MIS_SC0_RXFIFO_get_dat(data)                                                 ((0x000000FF&(data))>>0)


#define MIS_SC0_RXLENR                                                               0x9801BE18
#define MIS_SC0_RXLENR_reg_addr                                                      "0x9801BE18"
#define MIS_SC0_RXLENR_reg                                                           0x9801BE18
#define set_MIS_SC0_RXLENR_reg(data)   (*((volatile unsigned int*) MIS_SC0_RXLENR_reg)=data)
#define get_MIS_SC0_RXLENR_reg   (*((volatile unsigned int*) MIS_SC0_RXLENR_reg))
#define MIS_SC0_RXLENR_inst_adr                                                      "0x0086"
#define MIS_SC0_RXLENR_inst                                                          0x0086
#define MIS_SC0_RXLENR_rxlen_shift                                                   (0)
#define MIS_SC0_RXLENR_rxlen_mask                                                    (0x000000FF)
#define MIS_SC0_RXLENR_rxlen(data)                                                   (0x000000FF&((data)<<0))
#define MIS_SC0_RXLENR_rxlen_src(data)                                               ((0x000000FF&(data))>>0)
#define MIS_SC0_RXLENR_get_rxlen(data)                                               ((0x000000FF&(data))>>0)


#define MIS_SC0_FCR                                                                  0x9801BE1C
#define MIS_SC0_FCR_reg_addr                                                         "0x9801BE1C"
#define MIS_SC0_FCR_reg                                                              0x9801BE1C
#define set_MIS_SC0_FCR_reg(data)   (*((volatile unsigned int*) MIS_SC0_FCR_reg)=data)
#define get_MIS_SC0_FCR_reg   (*((volatile unsigned int*) MIS_SC0_FCR_reg))
#define MIS_SC0_FCR_inst_adr                                                         "0x0087"
#define MIS_SC0_FCR_inst                                                             0x0087
#define MIS_SC0_FCR_rxflow_shift                                                     (1)
#define MIS_SC0_FCR_rxflow_mask                                                      (0x00000002)
#define MIS_SC0_FCR_rxflow(data)                                                     (0x00000002&((data)<<1))
#define MIS_SC0_FCR_rxflow_src(data)                                                 ((0x00000002&(data))>>1)
#define MIS_SC0_FCR_get_rxflow(data)                                                 ((0x00000002&(data))>>1)
#define MIS_SC0_FCR_flow_en_shift                                                    (0)
#define MIS_SC0_FCR_flow_en_mask                                                     (0x00000001)
#define MIS_SC0_FCR_flow_en(data)                                                    (0x00000001&((data)<<0))
#define MIS_SC0_FCR_flow_en_src(data)                                                ((0x00000001&(data))>>0)
#define MIS_SC0_FCR_get_flow_en(data)                                                ((0x00000001&(data))>>0)


#define MIS_SC0_IRSR                                                                 0x9801BE20
#define MIS_SC0_IRSR_reg_addr                                                        "0x9801BE20"
#define MIS_SC0_IRSR_reg                                                             0x9801BE20
#define set_MIS_SC0_IRSR_reg(data)   (*((volatile unsigned int*) MIS_SC0_IRSR_reg)=data)
#define get_MIS_SC0_IRSR_reg   (*((volatile unsigned int*) MIS_SC0_IRSR_reg))
#define MIS_SC0_IRSR_inst_adr                                                        "0x0088"
#define MIS_SC0_IRSR_inst                                                            0x0088
#define MIS_SC0_IRSR_pres_shift                                                      (16)
#define MIS_SC0_IRSR_pres_mask                                                       (0x00010000)
#define MIS_SC0_IRSR_pres(data)                                                      (0x00010000&((data)<<16))
#define MIS_SC0_IRSR_pres_src(data)                                                  ((0x00010000&(data))>>16)
#define MIS_SC0_IRSR_get_pres(data)                                                  ((0x00010000&(data))>>16)
#define MIS_SC0_IRSR_cpres_int_shift                                                 (15)
#define MIS_SC0_IRSR_cpres_int_mask                                                  (0x00008000)
#define MIS_SC0_IRSR_cpres_int(data)                                                 (0x00008000&((data)<<15))
#define MIS_SC0_IRSR_cpres_int_src(data)                                             ((0x00008000&(data))>>15)
#define MIS_SC0_IRSR_get_cpres_int(data)                                             ((0x00008000&(data))>>15)
#define MIS_SC0_IRSR_tx_flow_int_shift                                               (14)
#define MIS_SC0_IRSR_tx_flow_int_mask                                                (0x00004000)
#define MIS_SC0_IRSR_tx_flow_int(data)                                               (0x00004000&((data)<<14))
#define MIS_SC0_IRSR_tx_flow_int_src(data)                                           ((0x00004000&(data))>>14)
#define MIS_SC0_IRSR_get_tx_flow_int(data)                                           ((0x00004000&(data))>>14)
#define MIS_SC0_IRSR_txp_int_shift                                                   (13)
#define MIS_SC0_IRSR_txp_int_mask                                                    (0x00002000)
#define MIS_SC0_IRSR_txp_int(data)                                                   (0x00002000&((data)<<13))
#define MIS_SC0_IRSR_txp_int_src(data)                                               ((0x00002000&(data))>>13)
#define MIS_SC0_IRSR_get_txp_int(data)                                               ((0x00002000&(data))>>13)
#define MIS_SC0_IRSR_txdone_int_shift                                                (12)
#define MIS_SC0_IRSR_txdone_int_mask                                                 (0x00001000)
#define MIS_SC0_IRSR_txdone_int(data)                                                (0x00001000&((data)<<12))
#define MIS_SC0_IRSR_txdone_int_src(data)                                            ((0x00001000&(data))>>12)
#define MIS_SC0_IRSR_get_txdone_int(data)                                            ((0x00001000&(data))>>12)
#define MIS_SC0_IRSR_txempty_int_shift                                               (11)
#define MIS_SC0_IRSR_txempty_int_mask                                                (0x00000800)
#define MIS_SC0_IRSR_txempty_int(data)                                               (0x00000800&((data)<<11))
#define MIS_SC0_IRSR_txempty_int_src(data)                                           ((0x00000800&(data))>>11)
#define MIS_SC0_IRSR_get_txempty_int(data)                                           ((0x00000800&(data))>>11)
#define MIS_SC0_IRSR_edcerr_int_shift                                                (10)
#define MIS_SC0_IRSR_edcerr_int_mask                                                 (0x00000400)
#define MIS_SC0_IRSR_edcerr_int(data)                                                (0x00000400&((data)<<10))
#define MIS_SC0_IRSR_edcerr_int_src(data)                                            ((0x00000400&(data))>>10)
#define MIS_SC0_IRSR_get_edcerr_int(data)                                            ((0x00000400&(data))>>10)
#define MIS_SC0_IRSR_rx_fover_shift                                                  (9)
#define MIS_SC0_IRSR_rx_fover_mask                                                   (0x00000200)
#define MIS_SC0_IRSR_rx_fover(data)                                                  (0x00000200&((data)<<9))
#define MIS_SC0_IRSR_rx_fover_src(data)                                              ((0x00000200&(data))>>9)
#define MIS_SC0_IRSR_get_rx_fover(data)                                              ((0x00000200&(data))>>9)
#define MIS_SC0_IRSR_rxp_int_shift                                                   (8)
#define MIS_SC0_IRSR_rxp_int_mask                                                    (0x00000100)
#define MIS_SC0_IRSR_rxp_int(data)                                                   (0x00000100&((data)<<8))
#define MIS_SC0_IRSR_rxp_int_src(data)                                               ((0x00000100&(data))>>8)
#define MIS_SC0_IRSR_get_rxp_int(data)                                               ((0x00000100&(data))>>8)
#define MIS_SC0_IRSR_atrs_int_shift                                                  (7)
#define MIS_SC0_IRSR_atrs_int_mask                                                   (0x00000080)
#define MIS_SC0_IRSR_atrs_int(data)                                                  (0x00000080&((data)<<7))
#define MIS_SC0_IRSR_atrs_int_src(data)                                              ((0x00000080&(data))>>7)
#define MIS_SC0_IRSR_get_atrs_int(data)                                              ((0x00000080&(data))>>7)
#define MIS_SC0_IRSR_bgt_int_shift                                                   (6)
#define MIS_SC0_IRSR_bgt_int_mask                                                    (0x00000040)
#define MIS_SC0_IRSR_bgt_int(data)                                                   (0x00000040&((data)<<6))
#define MIS_SC0_IRSR_bgt_int_src(data)                                               ((0x00000040&(data))>>6)
#define MIS_SC0_IRSR_get_bgt_int(data)                                               ((0x00000040&(data))>>6)
#define MIS_SC0_IRSR_cwt_int_shift                                                   (5)
#define MIS_SC0_IRSR_cwt_int_mask                                                    (0x00000020)
#define MIS_SC0_IRSR_cwt_int(data)                                                   (0x00000020&((data)<<5))
#define MIS_SC0_IRSR_cwt_int_src(data)                                               ((0x00000020&(data))>>5)
#define MIS_SC0_IRSR_get_cwt_int(data)                                               ((0x00000020&(data))>>5)
#define MIS_SC0_IRSR_rlen_int_shift                                                  (4)
#define MIS_SC0_IRSR_rlen_int_mask                                                   (0x00000010)
#define MIS_SC0_IRSR_rlen_int(data)                                                  (0x00000010&((data)<<4))
#define MIS_SC0_IRSR_rlen_int_src(data)                                              ((0x00000010&(data))>>4)
#define MIS_SC0_IRSR_get_rlen_int(data)                                              ((0x00000010&(data))>>4)
#define MIS_SC0_IRSR_wwt_int_shift                                                   (3)
#define MIS_SC0_IRSR_wwt_int_mask                                                    (0x00000008)
#define MIS_SC0_IRSR_wwt_int(data)                                                   (0x00000008&((data)<<3))
#define MIS_SC0_IRSR_wwt_int_src(data)                                               ((0x00000008&(data))>>3)
#define MIS_SC0_IRSR_get_wwt_int(data)                                               ((0x00000008&(data))>>3)
#define MIS_SC0_IRSR_bwt_int_shift                                                   (2)
#define MIS_SC0_IRSR_bwt_int_mask                                                    (0x00000004)
#define MIS_SC0_IRSR_bwt_int(data)                                                   (0x00000004&((data)<<2))
#define MIS_SC0_IRSR_bwt_int_src(data)                                               ((0x00000004&(data))>>2)
#define MIS_SC0_IRSR_get_bwt_int(data)                                               ((0x00000004&(data))>>2)
#define MIS_SC0_IRSR_rcv_int_shift                                                   (1)
#define MIS_SC0_IRSR_rcv_int_mask                                                    (0x00000002)
#define MIS_SC0_IRSR_rcv_int(data)                                                   (0x00000002&((data)<<1))
#define MIS_SC0_IRSR_rcv_int_src(data)                                               ((0x00000002&(data))>>1)
#define MIS_SC0_IRSR_get_rcv_int(data)                                               ((0x00000002&(data))>>1)
#define MIS_SC0_IRSR_drdy_int_shift                                                  (0)
#define MIS_SC0_IRSR_drdy_int_mask                                                   (0x00000001)
#define MIS_SC0_IRSR_drdy_int(data)                                                  (0x00000001&((data)<<0))
#define MIS_SC0_IRSR_drdy_int_src(data)                                              ((0x00000001&(data))>>0)
#define MIS_SC0_IRSR_get_drdy_int(data)                                              ((0x00000001&(data))>>0)


#define MIS_SC0_IRER                                                                 0x9801BE24
#define MIS_SC0_IRER_reg_addr                                                        "0x9801BE24"
#define MIS_SC0_IRER_reg                                                             0x9801BE24
#define set_MIS_SC0_IRER_reg(data)   (*((volatile unsigned int*) MIS_SC0_IRER_reg)=data)
#define get_MIS_SC0_IRER_reg   (*((volatile unsigned int*) MIS_SC0_IRER_reg))
#define MIS_SC0_IRER_inst_adr                                                        "0x0089"
#define MIS_SC0_IRER_inst                                                            0x0089
#define MIS_SC0_IRER_cpres_en_shift                                                  (15)
#define MIS_SC0_IRER_cpres_en_mask                                                   (0x00008000)
#define MIS_SC0_IRER_cpres_en(data)                                                  (0x00008000&((data)<<15))
#define MIS_SC0_IRER_cpres_en_src(data)                                              ((0x00008000&(data))>>15)
#define MIS_SC0_IRER_get_cpres_en(data)                                              ((0x00008000&(data))>>15)
#define MIS_SC0_IRER_txflow_int_en_shift                                             (14)
#define MIS_SC0_IRER_txflow_int_en_mask                                              (0x00004000)
#define MIS_SC0_IRER_txflow_int_en(data)                                             (0x00004000&((data)<<14))
#define MIS_SC0_IRER_txflow_int_en_src(data)                                         ((0x00004000&(data))>>14)
#define MIS_SC0_IRER_get_txflow_int_en(data)                                         ((0x00004000&(data))>>14)
#define MIS_SC0_IRER_txp_en_shift                                                    (13)
#define MIS_SC0_IRER_txp_en_mask                                                     (0x00002000)
#define MIS_SC0_IRER_txp_en(data)                                                    (0x00002000&((data)<<13))
#define MIS_SC0_IRER_txp_en_src(data)                                                ((0x00002000&(data))>>13)
#define MIS_SC0_IRER_get_txp_en(data)                                                ((0x00002000&(data))>>13)
#define MIS_SC0_IRER_txdone_en_shift                                                 (12)
#define MIS_SC0_IRER_txdone_en_mask                                                  (0x00001000)
#define MIS_SC0_IRER_txdone_en(data)                                                 (0x00001000&((data)<<12))
#define MIS_SC0_IRER_txdone_en_src(data)                                             ((0x00001000&(data))>>12)
#define MIS_SC0_IRER_get_txdone_en(data)                                             ((0x00001000&(data))>>12)
#define MIS_SC0_IRER_txempty_en_shift                                                (11)
#define MIS_SC0_IRER_txempty_en_mask                                                 (0x00000800)
#define MIS_SC0_IRER_txempty_en(data)                                                (0x00000800&((data)<<11))
#define MIS_SC0_IRER_txempty_en_src(data)                                            ((0x00000800&(data))>>11)
#define MIS_SC0_IRER_get_txempty_en(data)                                            ((0x00000800&(data))>>11)
#define MIS_SC0_IRER_edcerr_en_shift                                                 (10)
#define MIS_SC0_IRER_edcerr_en_mask                                                  (0x00000400)
#define MIS_SC0_IRER_edcerr_en(data)                                                 (0x00000400&((data)<<10))
#define MIS_SC0_IRER_edcerr_en_src(data)                                             ((0x00000400&(data))>>10)
#define MIS_SC0_IRER_get_edcerr_en(data)                                             ((0x00000400&(data))>>10)
#define MIS_SC0_IRER_rx_fover_en_shift                                               (9)
#define MIS_SC0_IRER_rx_fover_en_mask                                                (0x00000200)
#define MIS_SC0_IRER_rx_fover_en(data)                                               (0x00000200&((data)<<9))
#define MIS_SC0_IRER_rx_fover_en_src(data)                                           ((0x00000200&(data))>>9)
#define MIS_SC0_IRER_get_rx_fover_en(data)                                           ((0x00000200&(data))>>9)
#define MIS_SC0_IRER_rxp_en_shift                                                    (8)
#define MIS_SC0_IRER_rxp_en_mask                                                     (0x00000100)
#define MIS_SC0_IRER_rxp_en(data)                                                    (0x00000100&((data)<<8))
#define MIS_SC0_IRER_rxp_en_src(data)                                                ((0x00000100&(data))>>8)
#define MIS_SC0_IRER_get_rxp_en(data)                                                ((0x00000100&(data))>>8)
#define MIS_SC0_IRER_atrs_en_shift                                                   (7)
#define MIS_SC0_IRER_atrs_en_mask                                                    (0x00000080)
#define MIS_SC0_IRER_atrs_en(data)                                                   (0x00000080&((data)<<7))
#define MIS_SC0_IRER_atrs_en_src(data)                                               ((0x00000080&(data))>>7)
#define MIS_SC0_IRER_get_atrs_en(data)                                               ((0x00000080&(data))>>7)
#define MIS_SC0_IRER_bgt_en_shift                                                    (6)
#define MIS_SC0_IRER_bgt_en_mask                                                     (0x00000040)
#define MIS_SC0_IRER_bgt_en(data)                                                    (0x00000040&((data)<<6))
#define MIS_SC0_IRER_bgt_en_src(data)                                                ((0x00000040&(data))>>6)
#define MIS_SC0_IRER_get_bgt_en(data)                                                ((0x00000040&(data))>>6)
#define MIS_SC0_IRER_cwt_en_shift                                                    (5)
#define MIS_SC0_IRER_cwt_en_mask                                                     (0x00000020)
#define MIS_SC0_IRER_cwt_en(data)                                                    (0x00000020&((data)<<5))
#define MIS_SC0_IRER_cwt_en_src(data)                                                ((0x00000020&(data))>>5)
#define MIS_SC0_IRER_get_cwt_en(data)                                                ((0x00000020&(data))>>5)
#define MIS_SC0_IRER_rlen_en_shift                                                   (4)
#define MIS_SC0_IRER_rlen_en_mask                                                    (0x00000010)
#define MIS_SC0_IRER_rlen_en(data)                                                   (0x00000010&((data)<<4))
#define MIS_SC0_IRER_rlen_en_src(data)                                               ((0x00000010&(data))>>4)
#define MIS_SC0_IRER_get_rlen_en(data)                                               ((0x00000010&(data))>>4)
#define MIS_SC0_IRER_wwt_en_shift                                                    (3)
#define MIS_SC0_IRER_wwt_en_mask                                                     (0x00000008)
#define MIS_SC0_IRER_wwt_en(data)                                                    (0x00000008&((data)<<3))
#define MIS_SC0_IRER_wwt_en_src(data)                                                ((0x00000008&(data))>>3)
#define MIS_SC0_IRER_get_wwt_en(data)                                                ((0x00000008&(data))>>3)
#define MIS_SC0_IRER_bwt_en_shift                                                    (2)
#define MIS_SC0_IRER_bwt_en_mask                                                     (0x00000004)
#define MIS_SC0_IRER_bwt_en(data)                                                    (0x00000004&((data)<<2))
#define MIS_SC0_IRER_bwt_en_src(data)                                                ((0x00000004&(data))>>2)
#define MIS_SC0_IRER_get_bwt_en(data)                                                ((0x00000004&(data))>>2)
#define MIS_SC0_IRER_rcv_en_shift                                                    (1)
#define MIS_SC0_IRER_rcv_en_mask                                                     (0x00000002)
#define MIS_SC0_IRER_rcv_en(data)                                                    (0x00000002&((data)<<1))
#define MIS_SC0_IRER_rcv_en_src(data)                                                ((0x00000002&(data))>>1)
#define MIS_SC0_IRER_get_rcv_en(data)                                                ((0x00000002&(data))>>1)
#define MIS_SC0_IRER_drdy_en_shift                                                   (0)
#define MIS_SC0_IRER_drdy_en_mask                                                    (0x00000001)
#define MIS_SC0_IRER_drdy_en(data)                                                   (0x00000001&((data)<<0))
#define MIS_SC0_IRER_drdy_en_src(data)                                               ((0x00000001&(data))>>0)
#define MIS_SC0_IRER_get_drdy_en(data)                                               ((0x00000001&(data))>>0)


#endif
