/**************************************************************
// Spec Version                  :
// Parser Version                :
// CModelGen Version             :
// Naming Rule                   :
// Naming Rule                   :
// Parse Option                  :
// Parse Address Region          :
// Decode bit number             :
// Firmware Header Generate Date :
***************************************************************/

#ifndef _MIS_REG_H_INCLUDED_
#define _MIS_REG_H_INCLUDED_

#define MIS_TCWCR_reg                                                                0x9801B5B0

#define TC0TVR                                                                       0x9801B500
#define TC0TVR_reg_addr                                                              "0x9801B500"
#define TC0TVR_reg                                                                   0x9801B500
#define set_TC0TVR_reg(data)   (*((volatile unsigned int*) TC0TVR_reg)=data)
#define get_TC0TVR_reg   (*((volatile unsigned int*) TC0TVR_reg))
#define TC0TVR_inst_adr                                                              "0x0040"
#define TC0TVR_inst                                                                  0x0040
#define TC0TVR_TC0TVR_shift                                                          (0)
#define TC0TVR_TC0TVR_mask                                                           (0xFFFFFFFF)
#define TC0TVR_TC0TVR(data)                                                          (0xFFFFFFFF&((data)<<0))
#define TC0TVR_TC0TVR_src(data)                                                      ((0xFFFFFFFF&(data))>>0)
#define TC0TVR_get_TC0TVR(data)                                                      ((0xFFFFFFFF&(data))>>0)


#define TC1TVR                                                                       0x9801B504
#define TC1TVR_reg_addr                                                              "0x9801B504"
#define TC1TVR_reg                                                                   0x9801B504
#define set_TC1TVR_reg(data)   (*((volatile unsigned int*) TC1TVR_reg)=data)
#define get_TC1TVR_reg   (*((volatile unsigned int*) TC1TVR_reg))
#define TC1TVR_inst_adr                                                              "0x0041"
#define TC1TVR_inst                                                                  0x0041
#define TC1TVR_TC1TVR_shift                                                          (0)
#define TC1TVR_TC1TVR_mask                                                           (0xFFFFFFFF)
#define TC1TVR_TC1TVR(data)                                                          (0xFFFFFFFF&((data)<<0))
#define TC1TVR_TC1TVR_src(data)                                                      ((0xFFFFFFFF&(data))>>0)
#define TC1TVR_get_TC1TVR(data)                                                      ((0xFFFFFFFF&(data))>>0)


#define TC2TVR                                                                       0x9801B508
#define TC2TVR_reg_addr                                                              "0x9801B508"
#define TC2TVR_reg                                                                   0x9801B508
#define set_TC2TVR_reg(data)   (*((volatile unsigned int*) TC2TVR_reg)=data)
#define get_TC2TVR_reg   (*((volatile unsigned int*) TC2TVR_reg))
#define TC2TVR_inst_adr                                                              "0x0042"
#define TC2TVR_inst                                                                  0x0042
#define TC2TVR_TC2TVR_shift                                                          (0)
#define TC2TVR_TC2TVR_mask                                                           (0xFFFFFFFF)
#define TC2TVR_TC2TVR(data)                                                          (0xFFFFFFFF&((data)<<0))
#define TC2TVR_TC2TVR_src(data)                                                      ((0xFFFFFFFF&(data))>>0)
#define TC2TVR_get_TC2TVR(data)                                                      ((0xFFFFFFFF&(data))>>0)


#define TC0CVR                                                                       0x9801B50C
#define TC0CVR_reg_addr                                                              "0x9801B50C"
#define TC0CVR_reg                                                                   0x9801B50C
#define set_TC0CVR_reg(data)   (*((volatile unsigned int*) TC0CVR_reg)=data)
#define get_TC0CVR_reg   (*((volatile unsigned int*) TC0CVR_reg))
#define TC0CVR_inst_adr                                                              "0x0043"
#define TC0CVR_inst                                                                  0x0043
#define TC0CVR_TC0CVR_shift                                                          (0)
#define TC0CVR_TC0CVR_mask                                                           (0xFFFFFFFF)
#define TC0CVR_TC0CVR(data)                                                          (0xFFFFFFFF&((data)<<0))
#define TC0CVR_TC0CVR_src(data)                                                      ((0xFFFFFFFF&(data))>>0)
#define TC0CVR_get_TC0CVR(data)                                                      ((0xFFFFFFFF&(data))>>0)


#define TC1CVR                                                                       0x9801B510
#define TC1CVR_reg_addr                                                              "0x9801B510"
#define TC1CVR_reg                                                                   0x9801B510
#define set_TC1CVR_reg(data)   (*((volatile unsigned int*) TC1CVR_reg)=data)
#define get_TC1CVR_reg   (*((volatile unsigned int*) TC1CVR_reg))
#define TC1CVR_inst_adr                                                              "0x0044"
#define TC1CVR_inst                                                                  0x0044
#define TC1CVR_TC1CVR_shift                                                          (0)
#define TC1CVR_TC1CVR_mask                                                           (0xFFFFFFFF)
#define TC1CVR_TC1CVR(data)                                                          (0xFFFFFFFF&((data)<<0))
#define TC1CVR_TC1CVR_src(data)                                                      ((0xFFFFFFFF&(data))>>0)
#define TC1CVR_get_TC1CVR(data)                                                      ((0xFFFFFFFF&(data))>>0)


#define TC2CVR                                                                       0x9801B514
#define TC2CVR_reg_addr                                                              "0x9801B514"
#define TC2CVR_reg                                                                   0x9801B514
#define set_TC2CVR_reg(data)   (*((volatile unsigned int*) TC2CVR_reg)=data)
#define get_TC2CVR_reg   (*((volatile unsigned int*) TC2CVR_reg))
#define TC2CVR_inst_adr                                                              "0x0045"
#define TC2CVR_inst                                                                  0x0045
#define TC2CVR_TC2VR_shift                                                           (0)
#define TC2CVR_TC2VR_mask                                                            (0xFFFFFFFF)
#define TC2CVR_TC2VR(data)                                                           (0xFFFFFFFF&((data)<<0))
#define TC2CVR_TC2VR_src(data)                                                       ((0xFFFFFFFF&(data))>>0)
#define TC2CVR_get_TC2VR(data)                                                       ((0xFFFFFFFF&(data))>>0)


#define TC0CR                                                                        0x9801B518
#define TC0CR_reg_addr                                                               "0x9801B518"
#define TC0CR_reg                                                                    0x9801B518
#define set_TC0CR_reg(data)   (*((volatile unsigned int*) TC0CR_reg)=data)
#define get_TC0CR_reg   (*((volatile unsigned int*) TC0CR_reg))
#define TC0CR_inst_adr                                                               "0x0046"
#define TC0CR_inst                                                                   0x0046
#define TC0CR_TC0En_shift                                                            (31)
#define TC0CR_TC0En_mask                                                             (0x80000000)
#define TC0CR_TC0En(data)                                                            (0x80000000&((data)<<31))
#define TC0CR_TC0En_src(data)                                                        ((0x80000000&(data))>>31)
#define TC0CR_get_TC0En(data)                                                        ((0x80000000&(data))>>31)
#define TC0CR_TC0Mode_shift                                                          (30)
#define TC0CR_TC0Mode_mask                                                           (0x40000000)
#define TC0CR_TC0Mode(data)                                                          (0x40000000&((data)<<30))
#define TC0CR_TC0Mode_src(data)                                                      ((0x40000000&(data))>>30)
#define TC0CR_get_TC0Mode(data)                                                      ((0x40000000&(data))>>30)
#define TC0CR_TC0Pause_shift                                                         (29)
#define TC0CR_TC0Pause_mask                                                          (0x20000000)
#define TC0CR_TC0Pause(data)                                                         (0x20000000&((data)<<29))
#define TC0CR_TC0Pause_src(data)                                                     ((0x20000000&(data))>>29)
#define TC0CR_get_TC0Pause(data)                                                     ((0x20000000&(data))>>29)
#define TC0CR_RvdA_shift                                                             (24)
#define TC0CR_RvdA_mask                                                              (0x1F000000)
#define TC0CR_RvdA(data)                                                             (0x1F000000&((data)<<24))
#define TC0CR_RvdA_src(data)                                                         ((0x1F000000&(data))>>24)
#define TC0CR_get_RvdA(data)                                                         ((0x1F000000&(data))>>24)


#define TC1CR                                                                        0x9801B51C
#define TC1CR_reg_addr                                                               "0x9801B51C"
#define TC1CR_reg                                                                    0x9801B51C
#define set_TC1CR_reg(data)   (*((volatile unsigned int*) TC1CR_reg)=data)
#define get_TC1CR_reg   (*((volatile unsigned int*) TC1CR_reg))
#define TC1CR_inst_adr                                                               "0x0047"
#define TC1CR_inst                                                                   0x0047
#define TC1CR_TC1En_shift                                                            (31)
#define TC1CR_TC1En_mask                                                             (0x80000000)
#define TC1CR_TC1En(data)                                                            (0x80000000&((data)<<31))
#define TC1CR_TC1En_src(data)                                                        ((0x80000000&(data))>>31)
#define TC1CR_get_TC1En(data)                                                        ((0x80000000&(data))>>31)
#define TC1CR_TC1Mode_shift                                                          (30)
#define TC1CR_TC1Mode_mask                                                           (0x40000000)
#define TC1CR_TC1Mode(data)                                                          (0x40000000&((data)<<30))
#define TC1CR_TC1Mode_src(data)                                                      ((0x40000000&(data))>>30)
#define TC1CR_get_TC1Mode(data)                                                      ((0x40000000&(data))>>30)
#define TC1CR_TC1Pause_shift                                                         (29)
#define TC1CR_TC1Pause_mask                                                          (0x20000000)
#define TC1CR_TC1Pause(data)                                                         (0x20000000&((data)<<29))
#define TC1CR_TC1Pause_src(data)                                                     ((0x20000000&(data))>>29)
#define TC1CR_get_TC1Pause(data)                                                     ((0x20000000&(data))>>29)
#define TC1CR_RvdA_shift                                                             (24)
#define TC1CR_RvdA_mask                                                              (0x1F000000)
#define TC1CR_RvdA(data)                                                             (0x1F000000&((data)<<24))
#define TC1CR_RvdA_src(data)                                                         ((0x1F000000&(data))>>24)
#define TC1CR_get_RvdA(data)                                                         ((0x1F000000&(data))>>24)


#define TC2CR                                                                        0x9801B520
#define TC2CR_reg_addr                                                               "0x9801B520"
#define TC2CR_reg                                                                    0x9801B520
#define set_TC2CR_reg(data)   (*((volatile unsigned int*) TC2CR_reg)=data)
#define get_TC2CR_reg   (*((volatile unsigned int*) TC2CR_reg))
#define TC2CR_inst_adr                                                               "0x0048"
#define TC2CR_inst                                                                   0x0048
#define TC2CR_TC2En_shift                                                            (31)
#define TC2CR_TC2En_mask                                                             (0x80000000)
#define TC2CR_TC2En(data)                                                            (0x80000000&((data)<<31))
#define TC2CR_TC2En_src(data)                                                        ((0x80000000&(data))>>31)
#define TC2CR_get_TC2En(data)                                                        ((0x80000000&(data))>>31)
#define TC2CR_TC2Mode_shift                                                          (30)
#define TC2CR_TC2Mode_mask                                                           (0x40000000)
#define TC2CR_TC2Mode(data)                                                          (0x40000000&((data)<<30))
#define TC2CR_TC2Mode_src(data)                                                      ((0x40000000&(data))>>30)
#define TC2CR_get_TC2Mode(data)                                                      ((0x40000000&(data))>>30)
#define TC2CR_TC2Pause_shift                                                         (29)
#define TC2CR_TC2Pause_mask                                                          (0x20000000)
#define TC2CR_TC2Pause(data)                                                         (0x20000000&((data)<<29))
#define TC2CR_TC2Pause_src(data)                                                     ((0x20000000&(data))>>29)
#define TC2CR_get_TC2Pause(data)                                                     ((0x20000000&(data))>>29)
#define TC2CR_RvdA_shift                                                             (24)
#define TC2CR_RvdA_mask                                                              (0x1F000000)
#define TC2CR_RvdA(data)                                                             (0x1F000000&((data)<<24))
#define TC2CR_RvdA_src(data)                                                         ((0x1F000000&(data))>>24)
#define TC2CR_get_RvdA(data)                                                         ((0x1F000000&(data))>>24)


#define TC0ICR                                                                       0x9801B524
#define TC0ICR_reg_addr                                                              "0x9801B524"
#define TC0ICR_reg                                                                   0x9801B524
#define set_TC0ICR_reg(data)   (*((volatile unsigned int*) TC0ICR_reg)=data)
#define get_TC0ICR_reg   (*((volatile unsigned int*) TC0ICR_reg))
#define TC0ICR_inst_adr                                                              "0x0049"
#define TC0ICR_inst                                                                  0x0049
#define TC0ICR_TC0IE_shift                                                           (31)
#define TC0ICR_TC0IE_mask                                                            (0x80000000)
#define TC0ICR_TC0IE(data)                                                           (0x80000000&((data)<<31))
#define TC0ICR_TC0IE_src(data)                                                       ((0x80000000&(data))>>31)
#define TC0ICR_get_TC0IE(data)                                                       ((0x80000000&(data))>>31)


#define TC1ICR                                                                       0x9801B528
#define TC1ICR_reg_addr                                                              "0x9801B528"
#define TC1ICR_reg                                                                   0x9801B528
#define set_TC1ICR_reg(data)   (*((volatile unsigned int*) TC1ICR_reg)=data)
#define get_TC1ICR_reg   (*((volatile unsigned int*) TC1ICR_reg))
#define TC1ICR_inst_adr                                                              "0x004A"
#define TC1ICR_inst                                                                  0x004A
#define TC1ICR_TC1IE_shift                                                           (31)
#define TC1ICR_TC1IE_mask                                                            (0x80000000)
#define TC1ICR_TC1IE(data)                                                           (0x80000000&((data)<<31))
#define TC1ICR_TC1IE_src(data)                                                       ((0x80000000&(data))>>31)
#define TC1ICR_get_TC1IE(data)                                                       ((0x80000000&(data))>>31)


#define TC2ICR                                                                       0x9801B52C
#define TC2ICR_reg_addr                                                              "0x9801B52C"
#define TC2ICR_reg                                                                   0x9801B52C
#define set_TC2ICR_reg(data)   (*((volatile unsigned int*) TC2ICR_reg)=data)
#define get_TC2ICR_reg   (*((volatile unsigned int*) TC2ICR_reg))
#define TC2ICR_inst_adr                                                              "0x004B"
#define TC2ICR_inst                                                                  0x004B
#define TC2ICR_TC2IE_shift                                                           (31)
#define TC2ICR_TC2IE_mask                                                            (0x80000000)
#define TC2ICR_TC2IE(data)                                                           (0x80000000&((data)<<31))
#define TC2ICR_TC2IE_src(data)                                                       ((0x80000000&(data))>>31)
#define TC2ICR_get_TC2IE(data)                                                       ((0x80000000&(data))>>31)


#define TCWCR                                                                        0x9801B5B0
#define TCWCR_reg_addr                                                               "0x9801B5B0"
#define TCWCR_reg                                                                    0x9801B5B0
#define set_TCWCR_reg(data)   (*((volatile unsigned int*) TCWCR_reg)=data)
#define get_TCWCR_reg   (*((volatile unsigned int*) TCWCR_reg))
#define TCWCR_inst_adr                                                               "0x006C"
#define TCWCR_inst                                                                   0x006C
#define TCWCR_WD_INT_EN_shift                                                        (31)
#define TCWCR_WD_INT_EN_mask                                                         (0x80000000)
#define TCWCR_WD_INT_EN(data)                                                        (0x80000000&((data)<<31))
#define TCWCR_WD_INT_EN_src(data)                                                    ((0x80000000&(data))>>31)
#define TCWCR_get_WD_INT_EN(data)                                                    ((0x80000000&(data))>>31)
#define TCWCR_NMIC_shift                                                             (12)
#define TCWCR_NMIC_mask                                                              (0x0000F000)
#define TCWCR_NMIC(data)                                                             (0x0000F000&((data)<<12))
#define TCWCR_NMIC_src(data)                                                         ((0x0000F000&(data))>>12)
#define TCWCR_get_NMIC(data)                                                         ((0x0000F000&(data))>>12)
#define TCWCR_WDC_shift                                                              (8)
#define TCWCR_WDC_mask                                                               (0x00000F00)
#define TCWCR_WDC(data)                                                              (0x00000F00&((data)<<8))
#define TCWCR_WDC_src(data)                                                          ((0x00000F00&(data))>>8)
#define TCWCR_get_WDC(data)                                                          ((0x00000F00&(data))>>8)
#define TCWCR_WDEN_shift                                                             (0)
#define TCWCR_WDEN_mask                                                              (0x000000FF)
#define TCWCR_WDEN(data)                                                             (0x000000FF&((data)<<0))
#define TCWCR_WDEN_src(data)                                                         ((0x000000FF&(data))>>0)
#define TCWCR_get_WDEN(data)                                                         ((0x000000FF&(data))>>0)


#define TCWTR                                                                        0x9801B5B4
#define TCWTR_reg_addr                                                               "0x9801B5B4"
#define TCWTR_reg                                                                    0x9801B5B4
#define set_TCWTR_reg(data)   (*((volatile unsigned int*) TCWTR_reg)=data)
#define get_TCWTR_reg   (*((volatile unsigned int*) TCWTR_reg))
#define TCWTR_inst_adr                                                               "0x006D"
#define TCWTR_inst                                                                   0x006D
#define TCWTR_WDCLR_shift                                                            (0)
#define TCWTR_WDCLR_mask                                                             (0x00000001)
#define TCWTR_WDCLR(data)                                                            (0x00000001&((data)<<0))
#define TCWTR_WDCLR_src(data)                                                        ((0x00000001&(data))>>0)
#define TCWTR_get_WDCLR(data)                                                        ((0x00000001&(data))>>0)


#define TCWNMI                                                                       0x9801B5B8
#define TCWNMI_reg_addr                                                              "0x9801B5B8"
#define TCWNMI_reg                                                                   0x9801B5B8
#define set_TCWNMI_reg(data)   (*((volatile unsigned int*) TCWNMI_reg)=data)
#define get_TCWNMI_reg   (*((volatile unsigned int*) TCWNMI_reg))
#define TCWNMI_inst_adr                                                              "0x006E"
#define TCWNMI_inst                                                                  0x006E
#define TCWNMI_SEL_shift                                                             (0)
#define TCWNMI_SEL_mask                                                              (0xFFFFFFFF)
#define TCWNMI_SEL(data)                                                             (0xFFFFFFFF&((data)<<0))
#define TCWNMI_SEL_src(data)                                                         ((0xFFFFFFFF&(data))>>0)
#define TCWNMI_get_SEL(data)                                                         ((0xFFFFFFFF&(data))>>0)


#define TCWOV                                                                        0x9801B5BC
#define TCWOV_reg_addr                                                               "0x9801B5BC"
#define TCWOV_reg                                                                    0x9801B5BC
#define set_TCWOV_reg(data)   (*((volatile unsigned int*) TCWOV_reg)=data)
#define get_TCWOV_reg   (*((volatile unsigned int*) TCWOV_reg))
#define TCWOV_inst_adr                                                               "0x006F"
#define TCWOV_inst                                                                   0x006F
#define TCWOV_SEL_shift                                                              (0)
#define TCWOV_SEL_mask                                                               (0xFFFFFFFF)
#define TCWOV_SEL(data)                                                              (0xFFFFFFFF&((data)<<0))
#define TCWOV_SEL_src(data)                                                          ((0xFFFFFFFF&(data))>>0)
#define TCWOV_get_SEL(data)                                                          ((0xFFFFFFFF&(data))>>0)


#define TCWCR_SWC                                                                    0x9801B5C0
#define TCWCR_SWC_reg_addr                                                           "0x9801B5C0"
#define TCWCR_SWC_reg                                                                0x9801B5C0
#define set_TCWCR_SWC_reg(data)   (*((volatile unsigned int*) TCWCR_SWC_reg)=data)
#define get_TCWCR_SWC_reg   (*((volatile unsigned int*) TCWCR_SWC_reg))
#define TCWCR_SWC_inst_adr                                                           "0x0070"
#define TCWCR_SWC_inst                                                               0x0070
#define TCWCR_SWC_WD_INT_EN_shift                                                    (31)
#define TCWCR_SWC_WD_INT_EN_mask                                                     (0x80000000)
#define TCWCR_SWC_WD_INT_EN(data)                                                    (0x80000000&((data)<<31))
#define TCWCR_SWC_WD_INT_EN_src(data)                                                ((0x80000000&(data))>>31)
#define TCWCR_SWC_get_WD_INT_EN(data)                                                ((0x80000000&(data))>>31)
#define TCWCR_SWC_NMIC_shift                                                         (12)
#define TCWCR_SWC_NMIC_mask                                                          (0x0000F000)
#define TCWCR_SWC_NMIC(data)                                                         (0x0000F000&((data)<<12))
#define TCWCR_SWC_NMIC_src(data)                                                     ((0x0000F000&(data))>>12)
#define TCWCR_SWC_get_NMIC(data)                                                     ((0x0000F000&(data))>>12)
#define TCWCR_SWC_WDC_shift                                                          (8)
#define TCWCR_SWC_WDC_mask                                                           (0x00000F00)
#define TCWCR_SWC_WDC(data)                                                          (0x00000F00&((data)<<8))
#define TCWCR_SWC_WDC_src(data)                                                      ((0x00000F00&(data))>>8)
#define TCWCR_SWC_get_WDC(data)                                                      ((0x00000F00&(data))>>8)
#define TCWCR_SWC_WDEN_shift                                                         (0)
#define TCWCR_SWC_WDEN_mask                                                          (0x000000FF)
#define TCWCR_SWC_WDEN(data)                                                         (0x000000FF&((data)<<0))
#define TCWCR_SWC_WDEN_src(data)                                                     ((0x000000FF&(data))>>0)
#define TCWCR_SWC_get_WDEN(data)                                                     ((0x000000FF&(data))>>0)


#define TCWTR_SWC                                                                    0x9801B5C4
#define TCWTR_SWC_reg_addr                                                           "0x9801B5C4"
#define TCWTR_SWC_reg                                                                0x9801B5C4
#define set_TCWTR_SWC_reg(data)   (*((volatile unsigned int*) TCWTR_SWC_reg)=data)
#define get_TCWTR_SWC_reg   (*((volatile unsigned int*) TCWTR_SWC_reg))
#define TCWTR_SWC_inst_adr                                                           "0x0071"
#define TCWTR_SWC_inst                                                               0x0071
#define TCWTR_SWC_WDCLR_shift                                                        (0)
#define TCWTR_SWC_WDCLR_mask                                                         (0x00000001)
#define TCWTR_SWC_WDCLR(data)                                                        (0x00000001&((data)<<0))
#define TCWTR_SWC_WDCLR_src(data)                                                    ((0x00000001&(data))>>0)
#define TCWTR_SWC_get_WDCLR(data)                                                    ((0x00000001&(data))>>0)


#define TCWNMI_SWC                                                                   0x9801B5C8
#define TCWNMI_SWC_reg_addr                                                          "0x9801B5C8"
#define TCWNMI_SWC_reg                                                               0x9801B5C8
#define set_TCWNMI_SWC_reg(data)   (*((volatile unsigned int*) TCWNMI_SWC_reg)=data)
#define get_TCWNMI_SWC_reg   (*((volatile unsigned int*) TCWNMI_SWC_reg))
#define TCWNMI_SWC_inst_adr                                                          "0x0072"
#define TCWNMI_SWC_inst                                                              0x0072
#define TCWNMI_SWC_SEL_shift                                                         (0)
#define TCWNMI_SWC_SEL_mask                                                          (0xFFFFFFFF)
#define TCWNMI_SWC_SEL(data)                                                         (0xFFFFFFFF&((data)<<0))
#define TCWNMI_SWC_SEL_src(data)                                                     ((0xFFFFFFFF&(data))>>0)
#define TCWNMI_SWC_get_SEL(data)                                                     ((0xFFFFFFFF&(data))>>0)


#define TCWOV_SWC                                                                    0x9801B5CC
#define TCWOV_SWC_reg_addr                                                           "0x9801B5CC"
#define TCWOV_SWC_reg                                                                0x9801B5CC
#define set_TCWOV_SWC_reg(data)   (*((volatile unsigned int*) TCWOV_SWC_reg)=data)
#define get_TCWOV_SWC_reg   (*((volatile unsigned int*) TCWOV_SWC_reg))
#define TCWOV_SWC_inst_adr                                                           "0x0073"
#define TCWOV_SWC_inst                                                               0x0073
#define TCWOV_SWC_SEL_shift                                                          (0)
#define TCWOV_SWC_SEL_mask                                                           (0xFFFFFFFF)
#define TCWOV_SWC_SEL(data)                                                          (0xFFFFFFFF&((data)<<0))
#define TCWOV_SWC_SEL_src(data)                                                      ((0xFFFFFFFF&(data))>>0)
#define TCWOV_SWC_get_SEL(data)                                                      ((0xFFFFFFFF&(data))>>0)


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

#endif
