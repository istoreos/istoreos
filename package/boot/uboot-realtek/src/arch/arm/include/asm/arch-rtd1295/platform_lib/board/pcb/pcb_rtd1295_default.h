#include <platform_lib/board/pcb_rtd1295_bga_library.h>
#include "pcb_define.h"

// PAD_NAME: GPIO1 0
#define RTD1295_BGA_PIN_AJ6								(0xF&0xF)//0xB8000800[23:20];
																							//3: TCON_bit0,<O>
																							//6: PCMCIA_CE2_1_N,<O>
																							//7: uart3_cts_n_src0,<I>
																							//8: uart1_rxdi_src0,<I>
																							//9: uart2_rxdi_src0,<I>
																							//A: USB_PWR_FLAG0,<I>
																							//B: USB_PWR_CTRL1,<O>
																							//C: misc_pwm_0,<OD>
																							//F: MIS_GPIO_bit1,<I/O>
																							//def: MIS_GPIO_bit1,<I/O>
#define RTD1295_BGA_PIN_AJ6_UP							(1&0x01)// 0xB8000800[19]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AJ6_PD							(0&0x01)// 0xB8000800[18]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AJ6_DS							(0&0x01)// 0xB8000800[17]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AJ6_SR							(0&0x01)// 0xB8000800[16]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO2 1
#define RTD1295_BGA_PIN_AJ7								(0x0&0xF)//0xB8000800[15:12];
																							//0: nf_tmx_d_bit5,<I/O>,<HS>
																							//1: EMMC_CLK,<O>,<HS>
																							//6: PCMCIA_INPACK1_N,<I>
																							//7: uart3_rts_n,<O>
																							//8: uart1_txdo,<O>
																							//9: uart2_txdo,<O>
																							//A: USB_PWR_CTRL0,<O>
																							//B: USB_PWR_FLAG1,<I>
																							//C: misc_pwm_1,<OD>
																							//F: MIS_GPIO_bit2,<I/O>
																							//def: MIS_GPIO_bit2,<I/O>
#define RTD1295_BGA_PIN_AJ7_UP							(1&0x01)// 0xB8000800[11]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AJ7_PD							(0&0x01)// 0xB8000800[10]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AJ7_DS							(0&0x01)// 0xB8000800[9]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AJ7_SR							(0&0x01)// 0xB8000800[8]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO3 2
#define RTD1295_BGA_PIN_AH7								(0x0&0xF)//0xB8000800[7:4];
																							//0: nf_tmx_d_bit6,<I/O>,<HS>
																							//F: MIS_GPIO_bit3,<I/O>
																							//def: MIS_GPIO_bit3,<I/O>
#define RTD1295_BGA_PIN_AH7_UP							(1&0x01)// 0xB8000800[3]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AH7_PD							(0&0x01)// 0xB8000800[2]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AH7_DS							(0&0x01)// 0xB8000800[1]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AH7_SR							(0&0x01)// 0xB8000800[0]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO4 3
#define RTD1295_BGA_PIN_AH8								(0x0&0xF)//0xB8000804[31:28];
																							//0: nf_tmx_d_bit7_mux,<I/O>,<HS>
																							//F: MIS_GPIO_bit4,<I/O>
																							//def: MIS_GPIO_bit4,<I/O>
#define RTD1295_BGA_PIN_AH8_UP							(1&0x01)// 0xB8000804[27]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AH8_PD							(0&0x01)// 0xB8000804[26]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AH8_DS							(0&0x01)// 0xB8000804[25]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AH8_SR							(0&0x01)// 0xB8000804[24]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO5 4
#define RTD1295_BGA_PIN_AG8								(0xF&0xF)//0xB8000804[23:20];
																							//0: nf_tmx_rd_n,<O>,<HS>
																							//3: TCON_bit2,<O>
																							//4: ld_spi1_p1_cs1,<O>
																							//6: PCMCIA_CE2_N,<O>
																							//7: uart3_rxdi_src0,<I>
																							//8: uart1_rxdi_src1,<I>
																							//C: misc_pwm_2,<OD>
																							//D: ld_spi0_p1_cs1,<O>
																							//F: MIS_GPIO_bit5,<I/O>
																							//def: MIS_GPIO_bit5,<I/O>
#define RTD1295_BGA_PIN_AG8_UP							(1&0x01)// 0xB8000804[19]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AG8_PD							(0&0x01)// 0xB8000804[18]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AG8_DS							(0&0x01)// 0xB8000804[17]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AG8_SR							(0&0x01)// 0xB8000804[16]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO6 5
#define RTD1295_BGA_PIN_AH9								(0x0&0xF)//0xB8000804[15:12];
																							//0: nf_tmx_d_bit3,<I/O>,<HS>
																							//F: MIS_GPIO_bit6,<I/O>
																							//def: MIS_GPIO_bit6,<I/O>
#define RTD1295_BGA_PIN_AH9_UP							(1&0x01)// 0xB8000804[11]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AH9_PD							(0&0x01)// 0xB8000804[10]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AH9_DS							(0&0x01)// 0xB8000804[9]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AH9_SR							(0&0x01)// 0xB8000804[8]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO7 6
#define RTD1295_BGA_PIN_AJ9								(0x1&0xF)//0xB8000804[7:4];
																							//0: nf_tmx_d_bit4_mux,<I/O>,<HS>
																							//1: EMMC_CMD,<I/O>,<HS>
																							//F: MIS_GPIO_bit7,<I/O>
																							//def: MIS_GPIO_bit7,<I/O>
#define RTD1295_BGA_PIN_AJ9_UP							(1&0x01)// 0xB8000804[3]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AJ9_PD							(0&0x01)// 0xB8000804[2]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AJ9_DS							(0&0x01)// 0xB8000804[1]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AJ9_SR							(0&0x01)// 0xB8000804[0]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO8 7
#define RTD1295_BGA_PIN_AG9								(0x0&0xF)//0xB8000808[31:28];
																							//0: nf_tmx_ce_n_bit0_mux_src0,<I/O>,<HS>
																							//2: TP2_Data_bit7,<I>,<HS>
																							//3: TCON_bit4,<O>
																							//F: MIS_GPIO_bit8,<I/O>
																							//def: MIS_GPIO_bit8,<I/O>
#define RTD1295_BGA_PIN_AG9_UP							(1&0x01)// 0xB8000808[27]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AG9_PD							(0&0x01)// 0xB8000808[26]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AG9_DS							(0&0x01)// 0xB8000808[25]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AG9_SR							(0&0x01)// 0xB8000808[24]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO9 8
#define RTD1295_BGA_PIN_AJ10								(0x3&0xF)//0xB8000808[23:20];
																							//0: nf_tmx_cle_mux_src0,<I/O>,<HS>
																							//1: EMMC_CLK,<O>,<HS>
																							//2: TP2_Data_bit6,<I>,<HS>
																							//3: TCON_bit6,<O>
																							//4: ld_spi1_p2_sck_src0,<I/O>
																							//6: PCMCIA_IREQ1_N,<I>
																							//7: uart3_txdo,<O>
																							//8: uart1_txdo,<O>
																							//C: misc_pwm_3,<OD>
																							//D: ld_spi0_p2_sck_src0,<I/O>
																							//F: MIS_GPIO_bit9,<I/O>
#define RTD1295_BGA_PIN_AJ10_UP							(1&0x01)// 0xB8000808[19]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AJ10_PD							(0&0x01)// 0xB8000808[18]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AJ10_DS							(0&0x01)// 0xB8000808[17]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AJ10_SR							(0&0x01)// 0xB8000808[16]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO10 9
#define RTD1295_BGA_PIN_AH10								(0x0&0xF)//0xB8000808[15:12];
																							//0: nf_tmx_d_bit0_mux,<I/O>,<HS>
																							//F: MIS_GPIO_bit10,<I/O>
																							//def: MIS_GPIO_bit10,<I/O>
#define RTD1295_BGA_PIN_AH10_UP							(1&0x01)// 0xB8000808[11]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AH10_PD							(0&0x01)// 0xB8000808[10]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AH10_DS							(0&0x01)// 0xB8000808[9]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AH10_SR							(0&0x01)// 0xB8000808[8]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO11 10
#define RTD1295_BGA_PIN_AG10								(0x0&0xF)//0xB8000808[7:4];
																							//0: nf_tmx_d_bit2_mux,<I/O>,<HS>
																							//F: MIS_GPIO_bit11,<I/O>
																							//def: MIS_GPIO_bit11,<I/O>
#define RTD1295_BGA_PIN_AG10_UP							(1&0x01)// 0xB8000808[3]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AG10_PD							(0&0x01)// 0xB8000808[2]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AG10_DS							(0&0x01)// 0xB8000808[1]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AG10_SR							(0&0x01)// 0xB8000808[0]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO12 11
#define RTD1295_BGA_PIN_AH11								(0x0&0xF)//0xB800080C[31:28];
																							//0: nf_tmx_d_bit1_mux,<I/O>,<HS>
																							//F: MIS_GPIO_bit12,<I/O>
																							//def: MIS_GPIO_bit12,<I/O>
#define RTD1295_BGA_PIN_AH11_UP							(1&0x01)// 0xB800080C[27]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AH11_PD							(0&0x01)// 0xB800080C[26]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AH11_DS							(0&0x01)// 0xB800080C[25]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AH11_SR							(0&0x01)// 0xB800080C[24]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO13 12
#define RTD1295_BGA_PIN_AG11								(0x0&0xF)//0xB800080C[23:20];
																							//0: nf_tmx_ale_mux_src1,<I/O>,<HS>
																							//2: TP2_Data_bit5,<I>,<HS>
																							//3: TCON_bit8,<O>
																							//4: ld_spi1_p3_sdo_SRC0,<I/O>
																							//5: I2C1_SCL_SRC0,<I/O>
																							//6: PCMCIA_RST1,<OD>
																							//7: uart3_dtr_n,<O>
																							//8: uart1_rxdi_src2,<I>
																							//9: uart2_rxdi_src1,<I>
																							//C: misc_pwm_4,<OD>
																							//D: ld_spi0_p3_sdo_SRC0
#define RTD1295_BGA_PIN_AG11_UP							(1&0x01)// 0xB800080C[19]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AG11_PD							(0&0x01)// 0xB800080C[18]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AG11_DS							(0&0x01)// 0xB800080C[17]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AG11_SR							(0&0x01)// 0xB800080C[16]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO14 13
#define RTD1295_BGA_PIN_AH12								(0x0&0xF)//0xB800080C[15:12];
																							//0: nf_tmx_wr_n_mux_src0,<I/O>,<HS>
																							//2: TP2_Data_bit4,<I>,<HS>
																							//3: TCON_bit10,<O>
																							//4: ld_spi1_p4_sdi_SRC0,<I>
																							//5: I2C1_SDA_SRC0,<I/O>
																							//6: PCMCIA_WAIT1_N,<I>
																							//7: uart3_dsr_n_src0,<I>
																							//8: uart1_txdo,<O>
																							//9: uart2_txdo,<O>
																							//C: misc_pwm_5,<OD>
																							//D: ld_spi0_p4_sdi_SRC0,<I
#define RTD1295_BGA_PIN_AH12_UP							(1&0x01)// 0xB800080C[11]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AH12_PD							(0&0x01)// 0xB800080C[10]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AH12_DS							(0&0x01)// 0xB800080C[9]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AH12_SR							(0&0x01)// 0xB800080C[8]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO15 14
#define RTD1295_BGA_PIN_AJ12								(0xF&0xF)//0xB800080C[7:4];
																							//1: TP0_ERR,<I>,<HS>
																							//2: TP2_Data_bit3,<I>,<HS>
																							//3: TCON_bit12,<O>
																							//4: ld_spi1_p5_v_sync,<O>
																							//6: PCMCIA_CD1_N,<I>
																							//7: uart3_dcd_n_src0,<I>
																							//A: SPDIF_OUT,<O>
																							//D: ld_spi0_p5_v_sync,<O>
																							//F: MIS_GPIO_bit15,<I/O>
																							//def: MIS_GPIO_bit15,<I/O>
#define RTD1295_BGA_PIN_AJ12_UP							(1&0x01)// 0xB800080C[3]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AJ12_PD							(0&0x01)// 0xB800080C[2]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AJ12_DS							(0&0x01)// 0xB800080C[1]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AJ12_SR							(0&0x01)// 0xB800080C[0]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO16 15
#define RTD1295_BGA_PIN_AG12								(0x1&0xF)//0xB8000810[31:28];
																							//0: nf_tmx_ce_n_bit0_mux_src1,<I/O>,<HS>
																							//1: EMMC_Data_bit6,<I/O>,<HS>
																							//F: MIS_GPIO_bit16,<I/O>
																							//def: MIS_GPIO_bit16,<I/O>
#define RTD1295_BGA_PIN_AG12_UP							(1&0x01)// 0xB8000810[27]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AG12_PD							(0&0x01)// 0xB8000810[26]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AG12_DS							(0&0x01)// 0xB8000810[25]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AG12_SR							(0&0x01)// 0xB8000810[24]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO17 16
#define RTD1295_BGA_PIN_AM14								(0x1&0xF)//0xB8000810[23:20];
																							//0: nf_tmx_rd_n,<O>,<HS>
																							//1: EMMC_Data_bit4,<I/O>,<HS>
																							//F: MIS_GPIO_bit17,<I/O>
																							//def: MIS_GPIO_bit17,<I/O>
#define RTD1295_BGA_PIN_AM14_UP							(1&0x01)// 0xB8000810[19]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AM14_PD							(0&0x01)// 0xB8000810[18]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AM14_DS							(0&0x01)// 0xB8000810[17]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AM14_SR							(0&0x01)// 0xB8000810[16]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO18 17
#define RTD1295_BGA_PIN_AL14								(0x1&0xF)//0xB8000810[15:12];
																							//0: tmx_nf_rdy_mux,<I/O>,<HS>
																							//1: EMMC_Data_bit0,<I/O>,<HS>
																							//F: MIS_GPIO_bit18,<I/O>
																							//def: MIS_GPIO_bit18,<I/O>
#define RTD1295_BGA_PIN_AL14_UP							(1&0x01)// 0xB8000810[11]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AL14_PD							(0&0x01)// 0xB8000810[10]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AL14_DS							(0&0x01)// 0xB8000810[9]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AL14_SR							(0&0x01)// 0xB8000810[8]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO19 18
#define RTD1295_BGA_PIN_AK14								(0x1&0xF)//0xB8000810[7:4];
																							//1: EMMC_CLK,<O>,<HS>
																							//2: TP2_Data_bit2,<I>,<HS>
																							//3: TCON_bit14,<O>
																							//4: ld_spi1_p6_h_sync,<O>
																							//7: uart3_ri_n_src0,<I>
																							//C: misc_pwm_6,<OD>
																							//D: ld_spi0_p6_h_sync,<O>
																							//F: MIS_GPIO_bit19,<I/O>
																							//def: MIS_GPIO_bit19,<I/O>
#define RTD1295_BGA_PIN_AK14_UP							(1&0x01)// 0xB8000810[3]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AK14_PD							(0&0x01)// 0xB8000810[2]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AK14_DS							(0&0x01)// 0xB8000810[1]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AK14_SR							(0&0x01)// 0xB8000810[0]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO20 19
#define RTD1295_BGA_PIN_AL15								(0xF&0xF)//0xB8000814[31:28];
																							//2: TP2_Data_bit1,<I>,<HS>
																							//3: TCON_bit16,<O>
																							//C: misc_pwm_7,<OD>
																							//F: MIS_GPIO_bit20,<I/O>
																							//def: MIS_GPIO_bit20,<I/O>
#define RTD1295_BGA_PIN_AL15_UP							(1&0x01)// 0xB8000814[27]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AL15_PD							(0&0x01)// 0xB8000814[26]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AL15_DS							(0&0x01)// 0xB8000814[25]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AL15_SR							(0&0x01)// 0xB8000814[24]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO21 20
#define RTD1295_BGA_PIN_AK15								(0x1&0xF)//0xB8000814[23:20];
																							//0: nf_tmx_cle_mux_src1,<I/O>,<HS>
																							//1: EMMC_Data_bit5,<I/O>,<HS>
																							//F: MIS_GPIO_bit21,<I/O>
																							//def: MIS_GPIO_bit21,<I/O>
#define RTD1295_BGA_PIN_AK15_UP							(1&0x01)// 0xB8000814[19]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AK15_PD							(0&0x01)// 0xB8000814[18]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AK15_DS							(0&0x01)// 0xB8000814[17]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AK15_SR							(0&0x01)// 0xB8000814[16]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO22 21
#define RTD1295_BGA_PIN_AL16								(0x1&0xF)//0xB8000814[15:12];
																							//0: nf_tmx_ce_n_bit1_mux,<I/O>,<HS>
																							//1: EMMC_Data_bit7,<I/O>,<HS>
																							//F: MIS_GPIO_bit22,<I/O>
																							//def: MIS_GPIO_bit22,<I/O>
#define RTD1295_BGA_PIN_AL16_UP							(1&0x01)// 0xB8000814[11]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AL16_PD							(0&0x01)// 0xB8000814[10]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AL16_DS							(0&0x01)// 0xB8000814[9]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AL16_SR							(0&0x01)// 0xB8000814[8]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO23 22
#define RTD1295_BGA_PIN_AM16								(0x1&0xF)//0xB8000814[7:4];
																							//1: EMMC_Data_bit2,<I/O>,<HS>
																							//F: MIS_GPIO_bit23,<I/O>
																							//def: MIS_GPIO_bit23,<I/O>
#define RTD1295_BGA_PIN_AM16_UP							(1&0x01)// 0xB8000814[3]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AM16_PD							(0&0x01)// 0xB8000814[2]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AM16_DS							(0&0x01)// 0xB8000814[1]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AM16_SR							(0&0x01)// 0xB8000814[0]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO24 23
#define RTD1295_BGA_PIN_AK16								(0x1&0xF)//0xB8000818[31:28];
																							//0: nf_tmx_ale_mux_src0,<I/O>,<HS>
																							//1: EMMC_Data_bit1,<I/O>,<HS>
																							//F: MIS_GPIO_bit24,<I/O>
																							//def: MIS_GPIO_bit24,<I/O>
#define RTD1295_BGA_PIN_AK16_UP							(1&0x01)// 0xB8000818[27]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AK16_PD							(0&0x01)// 0xB8000818[26]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AK16_DS							(0&0x01)// 0xB8000818[25]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AK16_SR							(0&0x01)// 0xB8000818[24]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO25 24
#define RTD1295_BGA_PIN_AJ13								(0x1&0xF)//0xB8000818[23:20];
																							//0: nf_tmx_wr_n_mux_src1,<I/O>,<HS>
																							//1: EMMC_Data_bit3,<I/O>,<HS>
																							//F: MIS_GPIO_bit25,<I/O>
																							//def: MIS_GPIO_bit25,<I/O>
#define RTD1295_BGA_PIN_AJ13_UP							(1&0x01)// 0xB8000818[19]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AJ13_PD							(0&0x01)// 0xB8000818[18]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AJ13_DS							(0&0x01)// 0xB8000818[17]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AJ13_SR							(0&0x01)// 0xB8000818[16]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO26 25
#define RTD1295_BGA_PIN_AH13								(0x1&0xF)//0xB8000818[15:12];
																							//1: TP0_Data_bit7,<I>,<HS>
																							//2: EJTAG_TCLK_en,<I>
																							//3: TCON_bit18,<O>
																							//6: SC_SCLK,<OD>
																							//8: P_HIF_en,<I>
																							//F: MIS_GPIO_bit26,<I/O>
																							//def: MIS_GPIO_bit26,<I/O>
#define RTD1295_BGA_PIN_AH13_UP							(1&0x01)// 0xB8000818[11]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AH13_PD							(0&0x01)// 0xB8000818[10]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AH13_DS							(0&0x01)// 0xB8000818[9]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AH13_SR							(0&0x01)// 0xB8000818[8]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO27 26
#define RTD1295_BGA_PIN_AG13								(0x1&0xF)//0xB8000818[7:4];
																							//1: TP0_Data_bit6,<I>,<HS>
																							//2: EJTAG_TDI,<I>
																							//3: TCON_bit20,<O>
																							//6: SC_DATA_SRC0,<I/O>
																							//8: p_hif_clk_en,<I>,<HS>
																							//F: MIS_GPIO_bit27,<I/O>
																							//def: MIS_GPIO_bit27,<I/O>
#define RTD1295_BGA_PIN_AG13_UP							(1&0x01)// 0xB8000818[3]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AG13_PD							(0&0x01)// 0xB8000818[2]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AG13_DS							(0&0x01)// 0xB8000818[1]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AG13_SR							(0&0x01)// 0xB8000818[0]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO28 27
#define RTD1295_BGA_PIN_AH14								(0x1&0xF)//0xB800081C[31:28];
																							//1: TP0_Data_bit5,<I>,<HS>
																							//2: EJTAG_TMS,<I>
																							//3: TCON_bit22,<O>
																							//6: SC_RST,<OD>
																							//8: P_HIF_RDY,<O>
																							//F: MIS_GPIO_bit28,<I/O>
																							//def: MIS_GPIO_bit28,<I/O>
#define RTD1295_BGA_PIN_AH14_UP							(1&0x01)// 0xB800081C[27]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AH14_PD							(0&0x01)// 0xB800081C[26]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AH14_DS							(0&0x01)// 0xB800081C[25]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AH14_SR							(0&0x01)// 0xB800081C[24]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO29 28
#define RTD1295_BGA_PIN_AG14								(0x1&0xF)//0xB800081C[23:20];
																							//1: TP0_Data_bit4,<I>,<HS>
																							//2: EJTAG_TDO,<O>
																							//3: TCON_bit1,<O>
																							//6: SC_CD_SRC0,<I>
																							//8: P_HIF_Data_bit0,<I/O>
																							//F: MIS_GPIO_bit29,<I/O>
																							//def: MIS_GPIO_bit29,<I/O>
#define RTD1295_BGA_PIN_AG14_UP							(1&0x01)// 0xB800081C[19]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AG14_PD							(0&0x01)// 0xB800081C[18]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AG14_DS							(0&0x01)// 0xB800081C[17]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AG14_SR							(0&0x01)// 0xB800081C[16]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO30 29
#define RTD1295_BGA_PIN_AH15								(0x1&0xF)//0xB800081C[15:12];
																							//1: TP0_Data_bit3,<I>,<HS>
																							//2: EJTAG_TRST_en,<I>
																							//3: TCON_bit3,<O>
																							//6: ETN_LED_LINK,<O>
																							//8: P_HIF_Data_bit1,<I/O>
																							//C: misc_pwm_4,<OD>
																							//F: MIS_GPIO_bit30,<I/O>
																							//def: MIS_GPIO_bit30,<I/O>
#define RTD1295_BGA_PIN_AH15_UP							(1&0x01)// 0xB800081C[11]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AH15_PD							(0&0x01)// 0xB800081C[10]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AH15_DS							(0&0x01)// 0xB800081C[9]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AH15_SR							(0&0x01)// 0xB800081C[8]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO31 30
#define RTD1295_BGA_PIN_AJ15								(0x1&0xF)//0xB800081C[7:4];
																							//1: TP0_VAL,<I>,<HS>
																							//3: TCON_bit5,<O>
																							//8: P_HIF_Data_bit2,<I/O>
																							//F: MIS_GPIO_bit31,<I/O>
																							//def: MIS_GPIO_bit31,<I/O>
#define RTD1295_BGA_PIN_AJ15_UP							(1&0x01)// 0xB800081C[3]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AJ15_PD							(0&0x01)// 0xB800081C[2]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AJ15_DS							(0&0x01)// 0xB800081C[1]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AJ15_SR							(0&0x01)// 0xB800081C[0]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO32 31
#define RTD1295_BGA_PIN_AG15								(0x1&0xF)//0xB8000820[31:28];
																							//1: PCMCIA_D_bit1,<I/O>,<HS>
																							//3: TCON_bit7,<O>
																							//6: ETN_LED_TXRX,<O>
																							//8: P_HIF_Data_bit3,<I/O>
																							//C: misc_pwm_5,<OD>
																							//F: MIS_GPIO_bit32,<I/O>
																							//def: MIS_GPIO_bit32,<I/O>
#define RTD1295_BGA_PIN_AG15_UP							(1&0x01)// 0xB8000820[27]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AG15_PD							(0&0x01)// 0xB8000820[26]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AG15_DS							(0&0x01)// 0xB8000820[25]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AG15_SR							(0&0x01)// 0xB8000820[24]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO33 32
#define RTD1295_BGA_PIN_AM17								(0x1&0xF)//0xB8000820[23:20];
																							//0: P_TXC,<I>,<HS>
																							//1: TPO_dato_bit2_pad,<O>,<HS>
																							//3: TCON_bit9,<O>
																							//8: P_HIF_Data_bit4,<I/O>
																							//F: MIS_GPIO_bit33,<I/O>
																							//def: MIS_GPIO_bit33,<I/O>
#define RTD1295_BGA_PIN_AM17_UP							(1&0x01)// 0xB8000820[19]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AM17_PD							(0&0x01)// 0xB8000820[18]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AM17_DS							(0&0x01)// 0xB8000820[17]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AM17_SR							(0&0x01)// 0xB8000820[16]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO34 33
#define RTD1295_BGA_PIN_AL17								(0x1&0xF)//0xB8000820[15:12];
																							//0: P_TXD3,<O>,<HS>
																							//1: PCMCIA_D_bit2,<I/O>,<HS>
																							//3: TCON_bit11,<O>
																							//8: P_HIF_Data_bit5,<I/O>
																							//F: MIS_GPIO_bit34,<I/O>
																							//def: MIS_GPIO_bit34,<I/O>
#define RTD1295_BGA_PIN_AL17_UP							(1&0x01)// 0xB8000820[11]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AL17_PD							(0&0x01)// 0xB8000820[10]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AL17_DS							(0&0x01)// 0xB8000820[9]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AL17_SR							(0&0x01)// 0xB8000820[8]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO35 34
#define RTD1295_BGA_PIN_AK17								(0x1&0xF)//0xB8000820[7:4];
																							//0: P_TXD2,<O>,<HS>
																							//1: TP0_Data_bit2,<I>,<HS>
																							//3: TCON_bit13,<O>
																							//8: P_HIF_Data_bit6,<I/O>
																							//F: MIS_GPIO_bit35,<I/O>
																							//def: MIS_GPIO_bit35,<I/O>
#define RTD1295_BGA_PIN_AK17_UP							(1&0x01)// 0xB8000820[3]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AK17_PD							(0&0x01)// 0xB8000820[2]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AK17_DS							(0&0x01)// 0xB8000820[1]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AK17_SR							(0&0x01)// 0xB8000820[0]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO36 35
#define RTD1295_BGA_PIN_AL18								(0x1&0xF)//0xB8000824[31:28];
																							//0: P_TXD1,<O>,<HS>
																							//1: TP0_Data_bit1,<I>,<HS>
																							//3: TCON_bit15,<O>
																							//8: P_HIF_Data_bit7,<I/O>
																							//E: test_en_bit48,<I/O>
																							//F: MIS_GPIO_bit36,<I/O>
																							//def: MIS_GPIO_bit36,<I/O>
#define RTD1295_BGA_PIN_AL18_UP							(1&0x01)// 0xB8000824[27]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AL18_PD							(0&0x01)// 0xB8000824[26]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AL18_DS							(0&0x01)// 0xB8000824[25]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AL18_SR							(0&0x01)// 0xB8000824[24]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO37 36
#define RTD1295_BGA_PIN_AK18								(0x1&0xF)//0xB8000824[23:20];
																							//0: P_TXD0,<O>,<HS>
																							//1: TPO_dato_bit0_pad,<O>,<HS>
																							//3: TCON_bit17,<O>
																							//8: P_HIF_Data_bit8,<I/O>
																							//E: test_en_bit47,<I/O>
																							//F: MIS_GPIO_bit37,<I/O>
																							//def: MIS_GPIO_bit37,<I/O>
#define RTD1295_BGA_PIN_AK18_UP							(1&0x01)// 0xB8000824[19]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AK18_PD							(0&0x01)// 0xB8000824[18]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AK18_DS							(0&0x01)// 0xB8000824[17]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AK18_SR							(0&0x01)// 0xB8000824[16]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO38 37
#define RTD1295_BGA_PIN_AL19								(0x1&0xF)//0xB8000824[15:12];
																							//0: P_TXEN,<O>,<HS>
																							//1: TPO_dato_bit1_pad,<O>,<HS>
																							//3: TCON_bit19,<O>
																							//8: P_HIF_Data_bit9,<I/O>
																							//E: test_en_bit46,<I/O>
																							//F: MIS_GPIO_bit38,<I/O>
																							//def: MIS_GPIO_bit38,<I/O>
#define RTD1295_BGA_PIN_AL19_UP							(1&0x01)// 0xB8000824[11]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AL19_PD							(0&0x01)// 0xB8000824[10]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AL19_DS							(0&0x01)// 0xB8000824[9]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AL19_SR							(0&0x01)// 0xB8000824[8]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO39 38
#define RTD1295_BGA_PIN_AM19								(0x1&0xF)//0xB8000824[7:4];
																							//1: TP0_Data_bit0,<I>,<HS>
																							//3: TCON_bit21,<O>
																							//8: P_HIF_Data_bit10,<I/O>
																							//E: test_en_bit45,<I/O>
																							//F: MIS_GPIO_bit39,<I/O>
																							//def: MIS_GPIO_bit39,<I/O>
#define RTD1295_BGA_PIN_AM19_UP							(1&0x01)// 0xB8000824[3]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AM19_PD							(0&0x01)// 0xB8000824[2]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AM19_DS							(0&0x01)// 0xB8000824[1]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AM19_SR							(0&0x01)// 0xB8000824[0]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO40 39
#define RTD1295_BGA_PIN_AK19								(0x1&0xF)//0xB8000828[31:28];
																							//1: TP0_SYNC,<I>,<HS>
																							//3: TCON_bit23,<O>
																							//8: P_HIF_Data_bit11,<I/O>
																							//E: test_en_bit44,<I/O>
																							//F: MIS_GPIO_bit40,<I/O>
																							//def: MIS_GPIO_bit40,<I/O>
#define RTD1295_BGA_PIN_AK19_UP							(1&0x01)// 0xB8000828[27]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AK19_PD							(0&0x01)// 0xB8000828[26]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AK19_DS							(0&0x01)// 0xB8000828[25]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AK19_SR							(0&0x01)// 0xB8000828[24]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO41 40
#define RTD1295_BGA_PIN_AJ16								(0x1&0xF)//0xB8000828[23:20];
																							//0: P_MDIO,<I/O>,<HS>
																							//1: TPO_dato_bit7_pad,<O>,<HS>
																							//3: TCON_bit0,<O>
																							//7: uart3_cts_n_src1,<I>
																							//8: P_HIF_Data_bit12,<I/O>
																							//E: test_en_bit43,<I/O>
																							//F: MIS_GPIO_bit41,<I/O>
																							//def: MIS_GPIO_bit41,<I/O>
#define RTD1295_BGA_PIN_AJ16_UP							(1&0x01)// 0xB8000828[19]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AJ16_PD							(0&0x01)// 0xB8000828[18]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AJ16_DS							(0&0x01)// 0xB8000828[17]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AJ16_SR							(0&0x01)// 0xB8000828[16]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO42 41
#define RTD1295_BGA_PIN_AH16								(0x1&0xF)//0xB8000828[15:12];
																							//0: P_RXC,<I>,<HS>
																							//1: TPO_VAL_pad,<O>,<HS>
																							//3: TCON_bit2,<O>
																							//7: uart3_rts_n,<O>
																							//8: P_HIF_Data_bit13,<I/O>
																							//E: test_en_bit42,<I/O>
																							//F: MIS_GPIO_bit42,<I/O>
																							//def: MIS_GPIO_bit42,<I/O>
#define RTD1295_BGA_PIN_AH16_UP							(1&0x01)// 0xB8000828[11]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AH16_PD							(0&0x01)// 0xB8000828[10]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AH16_DS							(0&0x01)// 0xB8000828[9]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AH16_SR							(0&0x01)// 0xB8000828[8]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO43 42
#define RTD1295_BGA_PIN_AG16								(0x1&0xF)//0xB8000828[7:4];
																							//0: P_RXD3,<I>,<HS>
																							//1: PCMCIA_D_bit0,<I/O>,<HS>
																							//3: TCON_bit4,<O>
																							//7: uart3_dtr_n,<O>
																							//8: P_HIF_Data_bit14,<I/O>
																							//E: test_en_bit41,<I/O>
																							//F: MIS_GPIO_bit43,<I/O>
																							//def: MIS_GPIO_bit43,<I/O>
#define RTD1295_BGA_PIN_AG16_UP							(1&0x01)// 0xB8000828[3]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AG16_PD							(0&0x01)// 0xB8000828[2]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AG16_DS							(0&0x01)// 0xB8000828[1]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AG16_SR							(0&0x01)// 0xB8000828[0]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO44 43
#define RTD1295_BGA_PIN_AH17								(0x1&0xF)//0xB800082C[31:28];
																							//0: P_RXD2,<I>,<HS>
																							//1: TPO_SYNC_pad,<O>,<HS>
																							//3: TCON_bit6,<O>
																							//7: uart3_dsr_n_src1,<I>
																							//8: P_HIF_Data_bit15,<I/O>
																							//E: test_en_bit40,<I/O>
																							//F: MIS_GPIO_bit44,<I/O>
																							//def: MIS_GPIO_bit44,<I/O>
#define RTD1295_BGA_PIN_AH17_UP							(1&0x01)// 0xB800082C[27]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AH17_PD							(0&0x01)// 0xB800082C[26]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AH17_DS							(0&0x01)// 0xB800082C[25]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AH17_SR							(0&0x01)// 0xB800082C[24]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO45 44
#define RTD1295_BGA_PIN_AG17								(0x1&0xF)//0xB800082C[23:20];
																							//0: P_RXD1,<I>,<HS>
																							//1: TPO_dato_bit6_pad,<O>,<HS>
																							//3: TCON_bit8,<O>
																							//7: uart3_dcd_n_src1,<I>
																							//E: test_en_bit39,<I/O>
																							//F: MIS_GPIO_bit45,<I/O>
																							//def: MIS_GPIO_bit45,<I/O>
#define RTD1295_BGA_PIN_AG17_UP							(1&0x01)// 0xB800082C[19]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AG17_PD							(0&0x01)// 0xB800082C[18]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AG17_DS							(0&0x01)// 0xB800082C[17]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AG17_SR							(0&0x01)// 0xB800082C[16]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO46 45
#define RTD1295_BGA_PIN_AH18								(0x1&0xF)//0xB800082C[15:12];
																							//0: P_RXD0,<I>,<HS>
																							//1: TPO_dato_bit4_pad,<O>,<HS>
																							//3: TCON_bit10,<O>
																							//7: uart3_ri_n_src1,<I>
																							//E: test_en_bit38,<I/O>
																							//F: MIS_GPIO_bit46,<I/O>
																							//def: MIS_GPIO_bit46,<I/O>
#define RTD1295_BGA_PIN_AH18_UP							(1&0x01)// 0xB800082C[11]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AH18_PD							(0&0x01)// 0xB800082C[10]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AH18_DS							(0&0x01)// 0xB800082C[9]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AH18_SR							(0&0x01)// 0xB800082C[8]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO47 46
#define RTD1295_BGA_PIN_AJ18								(0x1&0xF)//0xB800082C[7:4];
																							//0: P_MDC,<O>,<HS>
																							//1: TPO_dato_bit5_pad,<O>,<HS>
																							//3: TCON_bit12,<O>
																							//7: uart3_rxdi_src1,<I>
																							//E: test_en_bit37,<I/O>
																							//F: MIS_GPIO_bit47,<I/O>
																							//def: MIS_GPIO_bit47,<I/O>
#define RTD1295_BGA_PIN_AJ18_UP							(1&0x01)// 0xB800082C[3]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AJ18_PD							(0&0x01)// 0xB800082C[2]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AJ18_DS							(0&0x01)// 0xB800082C[1]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AJ18_SR							(0&0x01)// 0xB800082C[0]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO48 47
#define RTD1295_BGA_PIN_AG18								(0x1&0xF)//0xB8000830[31:28];
																							//0: P_RXDV,<I>,<HS>
																							//1: PCMCIA_ADDR_bit1,<OD>,<HS>
																							//3: TCON_bit14,<O>
																							//7: uart3_txdo,<O>
																							//E: test_en_bit36,<I/O>
																							//F: MIS_GPIO_bit48,<I/O>
																							//def: MIS_GPIO_bit48,<I/O>
#define RTD1295_BGA_PIN_AG18_UP							(1&0x01)// 0xB8000830[27]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AG18_PD							(0&0x01)// 0xB8000830[26]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AG18_DS							(0&0x01)// 0xB8000830[25]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AG18_SR							(0&0x01)// 0xB8000830[24]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO49 48
#define RTD1295_BGA_PIN_AM20								(0x1&0xF)//0xB8000830[23:20];
																							//0: P_COL,<I>,<HS>
																							//1: PCMCIA_REG_N,<O>,<HS>
																							//3: TCON_bit16,<O>
																							//E: test_en_bit35,<I/O>
																							//F: MIS_GPIO_bit49,<I/O>
																							//def: MIS_GPIO_bit49,<I/O>
#define RTD1295_BGA_PIN_AM20_UP							(1&0x01)// 0xB8000830[19]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AM20_PD							(0&0x01)// 0xB8000830[18]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AM20_DS							(0&0x01)// 0xB8000830[17]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AM20_SR							(0&0x01)// 0xB8000830[16]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO50 49
#define RTD1295_BGA_PIN_AL20								(0x1&0xF)//0xB8000830[15:12];
																							//0: P_CRS,<I>,<HS>
																							//1: PCMCIA_ADDR_bit0,<OD>,<HS>
																							//3: TCON_bit18,<O>
																							//E: test_en_bit34,<I/O>
																							//F: MIS_GPIO_bit50,<I/O>
																							//def: MIS_GPIO_bit50,<I/O>
#define RTD1295_BGA_PIN_AL20_UP							(1&0x01)// 0xB8000830[11]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AL20_PD							(0&0x01)// 0xB8000830[10]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AL20_DS							(0&0x01)// 0xB8000830[9]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AL20_SR							(0&0x01)// 0xB8000830[8]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO51 50
#define RTD1295_BGA_PIN_AK20								(0x1&0xF)//0xB8000830[7:4];
																							//0: P_RXER,<I>,<HS>
																							//1: TPO_dato_bit3_pad,<O>,<HS>
																							//3: TCON_bit20,<O>
																							//E: test_en_bit33,<I/O>
																							//F: MIS_GPIO_bit51,<I/O>
																							//def: MIS_GPIO_bit51,<I/O>
#define RTD1295_BGA_PIN_AK20_UP							(1&0x01)// 0xB8000830[3]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AK20_PD							(0&0x01)// 0xB8000830[2]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AK20_DS							(0&0x01)// 0xB8000830[1]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AK20_SR							(0&0x01)// 0xB8000830[0]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO52 51
#define RTD1295_BGA_PIN_AK21								(0x0&0xF)//0xB8000834[31:28];
																							//0: CR_SD_CD,<I>,<HS>
																							//1: PCMCIA_CE1_1_N,<O>,<HS>
																							//3: TCON_bit22,<O>
																							//E: test_en_bit32,<I/O>
																							//F: MIS_GPIO_bit52,<I/O>
																							//def: MIS_GPIO_bit52,<I/O>
#define RTD1295_BGA_PIN_AK21_UP							(1&0x01)// 0xB8000834[27]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AK21_PD							(0&0x01)// 0xB8000834[26]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AK21_DS							(0&0x01)// 0xB8000834[25]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AK21_SR							(0&0x01)// 0xB8000834[24]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO53 52
#define RTD1295_BGA_PIN_AJ19								(0x1&0xF)//0xB8000834[23:20];
																							//1: PCMCIA_RST0,<OD>,<HS>
																							//3: TCON_bit1,<O>
																							//5: I2C1_SCL_SRC1,<I/O>
																							//E: test_en_bit31,<I/O>
																							//F: MIS_GPIO_bit53,<I/O>
																							//def: MIS_GPIO_bit53,<I/O>
#define RTD1295_BGA_PIN_AJ19_UP							(1&0x01)// 0xB8000834[19]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AJ19_PD							(0&0x01)// 0xB8000834[18]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AJ19_DS							(0&0x01)// 0xB8000834[17]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AJ19_SR							(0&0x01)// 0xB8000834[16]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO54 53
#define RTD1295_BGA_PIN_AH19								(0x1&0xF)//0xB8000834[15:12];
																							//1: PCMCIA_WAIT0_N,<I>,<HS>
																							//3: TCON_bit3,<O>
																							//5: I2C1_SDA_SRC1,<I/O>
																							//E: test_en_bit30,<I/O>
																							//F: MIS_GPIO_bit54,<I/O>
																							//def: MIS_GPIO_bit54,<I/O>
#define RTD1295_BGA_PIN_AH19_UP							(1&0x01)// 0xB8000834[11]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AH19_PD							(0&0x01)// 0xB8000834[10]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AH19_DS							(0&0x01)// 0xB8000834[9]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AH19_SR							(0&0x01)// 0xB8000834[8]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO55 54
#define RTD1295_BGA_PIN_AG19								(0x0&0xF)//0xB8000834[7:4];
																							//0: CR_SD_CMD,<I/O>,<HS>
																							//3: TCON_bit5,<O>
																							//E: test_en_bit29,<I/O>
																							//F: MIS_GPIO_bit55,<I/O>
																							//def: MIS_GPIO_bit55,<I/O>
#define RTD1295_BGA_PIN_AG19_UP							(1&0x01)// 0xB8000834[3]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AG19_PD							(0&0x01)// 0xB8000834[2]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AG19_DS							(0&0x01)// 0xB8000834[1]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AG19_SR							(0&0x01)// 0xB8000834[0]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO56 55
#define RTD1295_BGA_PIN_AH20								(0x0&0xF)//0xB8000838[31:28];
																							//0: CR_SD_CLK,<O>,<HS>
																							//3: TCON_bit7,<O>
																							//E: test_en_bit28,<I/O>
																							//F: MIS_GPIO_bit56,<I/O>
																							//def: MIS_GPIO_bit56,<I/O>
#define RTD1295_BGA_PIN_AH20_UP							(1&0x01)// 0xB8000838[27]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AH20_PD							(0&0x01)// 0xB8000838[26]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AH20_DS							(0&0x01)// 0xB8000838[25]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AH20_SR							(0&0x01)// 0xB8000838[24]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO57 56
#define RTD1295_BGA_PIN_AG20								(0x0&0xF)//0xB8000838[23:20];
																							//0: CR_SD_WP,<I>,<HS>
																							//1: PCMCIA_INPACK0_N,<I>,<HS>
																							//3: TCON_bit9,<O>
																							//E: test_en_bit27,<I/O>
																							//F: MIS_GPIO_bit57,<I/O>
																							//def: MIS_GPIO_bit57,<I/O>
#define RTD1295_BGA_PIN_AG20_UP							(1&0x01)// 0xB8000838[19]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AG20_PD							(0&0x01)// 0xB8000838[18]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AG20_DS							(0&0x01)// 0xB8000838[17]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AG20_SR							(0&0x01)// 0xB8000838[16]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO58 57
#define RTD1295_BGA_PIN_AH21								(0x1&0xF)//0xB8000838[15:12];
																							//1: PCMCIA_IOWR_N,<O>,<HS>
																							//3: TCON_bit11,<O>
																							//E: test_en_bit26,<I/O>
																							//F: MIS_GPIO_bit58,<I/O>
																							//def: MIS_GPIO_bit58,<I/O>
#define RTD1295_BGA_PIN_AH21_UP							(1&0x01)// 0xB8000838[11]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AH21_PD							(0&0x01)// 0xB8000838[10]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AH21_DS							(0&0x01)// 0xB8000838[9]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AH21_SR							(0&0x01)// 0xB8000838[8]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO59 58
#define RTD1295_BGA_PIN_AJ21								(0x1&0xF)//0xB8000838[7:4];
																							//1: TPO_CLK_pad,<O>,<HS>
																							//3: TCON_bit13,<O>
																							//E: test_en_bit25,<I/O>
																							//F: MIS_GPIO_bit59,<I/O>
																							//def: MIS_GPIO_bit59,<I/O>
#define RTD1295_BGA_PIN_AJ21_UP							(1&0x01)// 0xB8000838[3]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AJ21_PD							(0&0x01)// 0xB8000838[2]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AJ21_DS							(0&0x01)// 0xB8000838[1]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AJ21_SR							(0&0x01)// 0xB8000838[0]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO60 59
#define RTD1295_BGA_PIN_AG21								(0x1&0xF)//0xB800083C[31:28];
																							//1: CLK_TP0_en,<I>,<HS>
																							//3: TCON_bit15,<O>
																							//E: test_en_bit24,<I/O>
																							//F: MIS_GPIO_bit60,<I/O>
																							//def: MIS_GPIO_bit60,<I/O>
#define RTD1295_BGA_PIN_AG21_UP							(1&0x01)// 0xB800083C[27]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AG21_PD							(0&0x01)// 0xB800083C[26]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AG21_DS							(0&0x01)// 0xB800083C[25]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AG21_SR							(0&0x01)// 0xB800083C[24]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO61 60
#define RTD1295_BGA_PIN_AH22								(0x1&0xF)//0xB800083C[23:20];
																							//1: PCMCIA_CD0_N,<I>,<HS>
																							//3: TCON_bit17,<O>
																							//E: test_en_bit23,<I/O>
																							//F: MIS_GPIO_bit61,<I/O>
																							//def: MIS_GPIO_bit61,<I/O>
#define RTD1295_BGA_PIN_AH22_UP							(1&0x01)// 0xB800083C[19]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AH22_PD							(0&0x01)// 0xB800083C[18]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AH22_DS							(0&0x01)// 0xB800083C[17]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AH22_SR							(0&0x01)// 0xB800083C[16]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO62 61
#define RTD1295_BGA_PIN_AJ22								(0x0&0xF)//0xB800083C[15:12];
																							//0: CR_SD_Data_bit0,<I/O>,<HS>
																							//1: PCMCIA_D_bit5,<I/O>,<HS>
																							//3: TCON_bit19,<O>
																							//E: test_en_bit22,<I/O>
																							//F: MIS_GPIO_bit62,<I/O>
																							//def: MIS_GPIO_bit62,<I/O>
#define RTD1295_BGA_PIN_AJ22_UP							(1&0x01)// 0xB800083C[11]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AJ22_PD							(0&0x01)// 0xB800083C[10]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AJ22_DS							(0&0x01)// 0xB800083C[9]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AJ22_SR							(0&0x01)// 0xB800083C[8]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO63 62
#define RTD1295_BGA_PIN_AG22								(0x0&0xF)//0xB800083C[7:4];
																							//0: CR_SD_Data_bit1,<I/O>,<HS>
																							//1: PCMCIA_D_bit3,<I/O>,<HS>
																							//3: TCON_bit21,<O>
																							//E: test_en_bit21,<I/O>
																							//F: MIS_GPIO_bit63,<I/O>
																							//def: MIS_GPIO_bit63,<I/O>
#define RTD1295_BGA_PIN_AG22_UP							(1&0x01)// 0xB800083C[3]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AG22_PD							(0&0x01)// 0xB800083C[2]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AG22_DS							(0&0x01)// 0xB800083C[1]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AG22_SR							(0&0x01)// 0xB800083C[0]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO64 63
#define RTD1295_BGA_PIN_AH23								(0x1&0xF)//0xB8000840[31:28];
																							//1: PCMCIA_IORD_N,<O>,<HS>
																							//3: TCON_bit23,<O>
																							//E: test_en_bit20,<I/O>
																							//F: MIS_GPIO_bit64,<I/O>
																							//def: MIS_GPIO_bit64,<I/O>
#define RTD1295_BGA_PIN_AH23_UP							(1&0x01)// 0xB8000840[27]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AH23_PD							(0&0x01)// 0xB8000840[26]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AH23_DS							(0&0x01)// 0xB8000840[25]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AH23_SR							(0&0x01)// 0xB8000840[24]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO65 64
#define RTD1295_BGA_PIN_AG23								(0x0&0xF)//0xB8000840[23:20];
																							//0: CR_SD_Data_bit3,<I/O>,<HS>
																							//1: PCMCIA_D_bit4,<I/O>,<HS>
																							//3: TCON_bit0,<O>
																							//6: SC_SCLK,<OD>
																							//C: misc_pwm_0,<OD>
																							//E: test_en_bit19,<I/O>
																							//F: MIS_GPIO_bit65,<I/O>
																							//def: MIS_GPIO_bit65,<I/O>
#define RTD1295_BGA_PIN_AG23_UP							(1&0x01)// 0xB8000840[19]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AG23_PD							(0&0x01)// 0xB8000840[18]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AG23_DS							(0&0x01)// 0xB8000840[17]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AG23_SR							(0&0x01)// 0xB8000840[16]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO66 65
#define RTD1295_BGA_PIN_AH24								(0x0&0xF)//0xB8000840[15:12];
																							//0: CR_SD_Data_bit2,<I/O>,<HS>
																							//1: PCMCIA_D_bit6,<I/O>,<HS>
																							//3: TCON_bit2,<O>
																							//6: SC_DATA_SRC1,<I/O>
																							//C: misc_pwm_1,<OD>
																							//E: test_en_bit18,<I/O>
																							//F: MIS_GPIO_bit66,<I/O>
																							//def: MIS_GPIO_bit66,<I/O>
#define RTD1295_BGA_PIN_AH24_UP							(1&0x01)// 0xB8000840[11]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AH24_PD							(0&0x01)// 0xB8000840[10]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AH24_DS							(0&0x01)// 0xB8000840[9]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AH24_SR							(0&0x01)// 0xB8000840[8]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO67 66
#define RTD1295_BGA_PIN_AJ24								(0x1&0xF)//0xB8000840[7:4];
																							//0: CR_SD_Data_bit4,<I/O>,<HS>
																							//1: PCMCIA_D_bit7,<I/O>,<HS>
																							//3: TCON_bit4,<O>
																							//6: SC_RST,<OD>
																							//C: misc_pwm_2,<OD>
																							//E: test_en_bit17,<I/O>
																							//F: MIS_GPIO_bit67,<I/O>
																							//def: MIS_GPIO_bit67,<I/O>
#define RTD1295_BGA_PIN_AJ24_UP							(1&0x01)// 0xB8000840[3]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AJ24_PD							(0&0x01)// 0xB8000840[2]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AJ24_DS							(0&0x01)// 0xB8000840[1]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AJ24_SR							(0&0x01)// 0xB8000840[0]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO68 67
#define RTD1295_BGA_PIN_AG24								(0x1&0xF)//0xB8000844[31:28];
																							//1: PCMCIA_CE1_N,<O>,<HS>
																							//3: TCON_bit6,<O>
																							//6: SC_CD_SRC1,<I>
																							//C: misc_pwm_3,<OD>
																							//E: test_en_bit16,<I/O>
																							//F: MIS_GPIO_bit68,<I/O>
																							//def: MIS_GPIO_bit68,<I/O>
#define RTD1295_BGA_PIN_AG24_UP							(1&0x01)// 0xB8000844[27]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AG24_PD							(0&0x01)// 0xB8000844[26]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AG24_DS							(0&0x01)// 0xB8000844[25]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AG24_SR							(0&0x01)// 0xB8000844[24]: Slew rate 0:fast 1:slow


// PAD_NAME: A_FP 68
#define RTD1295_BGA_PIN_AL21								(0x0&0xF)//0xB8000890[31:28];
																							//0: LVDS_A_FP,<AO>
																							//3: TCON_bit0,<O>
																							//4: ld_spi1_p1_cs1,<O>
																							//C: misc_pwm_0,<OD>
																							//D: ld_spi0_p1_cs1,<O>
																							//F: MIS_GPIO_bit85,<I/O>
																							//def: MIS_GPIO_bit85,<I/O>


// PAD_NAME: A_FN 69
#define RTD1295_BGA_PIN_AK22								(0x0&0xF)//0xB8000890[27:24];
																							//0: LVDS_A_FN,<AO>
																							//3: TCON_bit2,<O>
																							//4: ld_spi1_p2_sck_src1,<I/O>
																							//C: misc_pwm_1,<OD>
																							//D: ld_spi0_p2_sck_src1,<I/O>
																							//F: MIS_GPIO_bit86,<I/O>
																							//def: MIS_GPIO_bit86,<I/O>


// PAD_NAME: A_EP 70
#define RTD1295_BGA_PIN_AL22								(0x0&0xF)//0xB8000890[23:20];
																							//0: LVDS_A_EP,<AO>
																							//3: TCON_bit4,<O>
																							//4: ld_spi1_p3_sdo_SRC1,<I/O>
																							//C: misc_pwm_2,<OD>
																							//D: ld_spi0_p3_sdo_SRC1,<I/O>
																							//F: MIS_GPIO_bit87,<I/O>
																							//def: MIS_GPIO_bit87,<I/O>


// PAD_NAME: A_EN 71
#define RTD1295_BGA_PIN_AM22								(0x0&0xF)//0xB8000890[19:16];
																							//0: LVDS_A_EN,<AO>
																							//3: TCON_bit6,<O>
																							//4: ld_spi1_p4_sdi_SRC1,<I>
																							//C: misc_pwm_3,<OD>
																							//D: ld_spi0_p4_sdi_SRC1,<I>
																							//F: MIS_GPIO_bit88,<I/O>
																							//def: MIS_GPIO_bit88,<I/O>


// PAD_NAME: A_DP 72
#define RTD1295_BGA_PIN_AK23								(0x0&0xF)//0xB8000890[15:12];
																							//0: LVDS_A_DP,<AO>
																							//3: TCON_bit8,<O>
																							//C: misc_pwm_4,<OD>
																							//F: MIS_GPIO_bit89,<I/O>
																							//def: MIS_GPIO_bit89,<I/O>


// PAD_NAME: A_DN 73
#define RTD1295_BGA_PIN_AM23								(0x0&0xF)//0xB8000890[11:8];
																							//0: LVDS_A_DN,<AO>
																							//3: TCON_bit10,<O>
																							//C: misc_pwm_5,<OD>
																							//F: MIS_GPIO_bit90,<I/O>
																							//def: MIS_GPIO_bit90,<I/O>


// PAD_NAME: A_CP 74
#define RTD1295_BGA_PIN_AL23								(0x0&0xF)//0xB8000890[7:4];
																							//0: LVDS_A_CP,<AO>
																							//3: TCON_bit12,<O>
																							//C: misc_pwm_6,<OD>
																							//F: MIS_GPIO_bit91,<I/O>
																							//def: MIS_GPIO_bit91,<I/O>


// PAD_NAME: A_CN 75
#define RTD1295_BGA_PIN_AK24								(0x0&0xF)//0xB8000890[3:0];
																							//0: LVDS_A_CN,<AO>
																							//3: TCON_bit14,<O>
																							//C: misc_pwm_7,<OD>
																							//F: MIS_GPIO_bit92,<I/O>
																							//def: MIS_GPIO_bit92,<I/O>


// PAD_NAME: A_BP 76
#define RTD1295_BGA_PIN_AL24								(0x0&0xF)//0xB8000894[31:28];
																							//0: LVDS_A_BP,<AO>
																							//3: TCON_bit16,<O>
																							//C: misc_pwm_0,<OD>
																							//F: MIS_GPIO_bit93,<I/O>
																							//def: MIS_GPIO_bit93,<I/O>


// PAD_NAME: A_BN 77
#define RTD1295_BGA_PIN_AK25								(0x0&0xF)//0xB8000894[27:24];
																							//0: LVDS_A_BN,<AO>
																							//3: TCON_bit18,<O>
																							//C: misc_pwm_1,<OD>
																							//F: MIS_GPIO_bit94,<I/O>
																							//def: MIS_GPIO_bit94,<I/O>


// PAD_NAME: A_AP 78
#define RTD1295_BGA_PIN_AL25								(0x0&0xF)//0xB8000894[23:20];
																							//0: LVDS_A_AP,<AO>
																							//3: TCON_bit20,<O>
																							//C: misc_pwm_2,<OD>
																							//F: MIS_GPIO_bit95,<I/O>
																							//def: MIS_GPIO_bit95,<I/O>


// PAD_NAME: A_AN 79
#define RTD1295_BGA_PIN_AM25								(0x0&0xF)//0xB8000894[19:16];
																							//0: LVDS_A_AN,<AO>
																							//3: TCON_bit22,<O>
																							//C: misc_pwm_3,<OD>
																							//F: MIS_GPIO_bit96,<I/O>
																							//def: MIS_GPIO_bit96,<I/O>


// PAD_NAME: B_FP 80
#define RTD1295_BGA_PIN_AK26								(0x0&0xF)//0xB8000898[31:28];
																							//0: LVDS_B_FP,<AO>
																							//3: TCON_bit16,<O>
																							//4: ld_spi1_p5_v_sync,<O>
																							//C: misc_pwm_4,<OD>
																							//D: ld_spi0_p5_v_sync,<O>
																							//F: MIS_GPIO_bit97,<I/O>
																							//def: MIS_GPIO_bit97,<I/O>


// PAD_NAME: B_FN 81
#define RTD1295_BGA_PIN_AM26								(0x0&0xF)//0xB8000898[27:24];
																							//0: LVDS_B_FN,<AO>
																							//3: TCON_bit18,<O>
																							//4: ld_spi1_p6_h_sync,<O>
																							//C: misc_pwm_5,<OD>
																							//D: ld_spi0_p6_h_sync,<O>
																							//F: MIS_GPIO_bit98,<I/O>
																							//def: MIS_GPIO_bit98,<I/O>


// PAD_NAME: B_EP 82
#define RTD1295_BGA_PIN_AL26								(0x0&0xF)//0xB8000898[23:20];
																							//0: LVDS_B_EP,<AO>
																							//3: TCON_bit20,<O>
																							//C: misc_pwm_6,<OD>
																							//F: MIS_GPIO_bit99,<I/O>
																							//def: MIS_GPIO_bit99,<I/O>


// PAD_NAME: B_EN 83
#define RTD1295_BGA_PIN_AK27								(0x0&0xF)//0xB8000898[19:16];
																							//0: LVDS_B_EN,<AO>
																							//3: TCON_bit22,<O>
																							//C: misc_pwm_7,<OD>
																							//F: MIS_GPIO_bit100,<I/O>
																							//def: MIS_GPIO_bit100,<I/O>


// PAD_NAME: C_FP 84
#define RTD1295_BGA_PIN_AL30								(0x0&0xF)//0xB80008A0[31:28];
																							//0: LVDS_C_FP,<AO>
																							//3: TCON_bit1,<O>
																							//4: ld_spi1_p1_cs1,<O>
																							//C: misc_pwm_0,<OD>
																							//D: ld_spi0_p1_cs1,<O>
																							//F: MIS_GPIO_bit101,<I/O>
																							//def: MIS_GPIO_bit101,<I/O>


// PAD_NAME: C_FN 85
#define RTD1295_BGA_PIN_AM31								(0x0&0xF)//0xB80008A0[27:24];
																							//0: LVDS_C_FN,<AO>
																							//3: TCON_bit3,<O>
																							//4: ld_spi1_p2_sck_src2,<I/O>
																							//C: misc_pwm_1,<OD>
																							//D: ld_spi0_p2_sck_src2,<I/O>
																							//F: MIS_GPIO_bit102,<I/O>
																							//def: MIS_GPIO_bit102,<I/O>


// PAD_NAME: C_EP 86
#define RTD1295_BGA_PIN_AL31								(0x0&0xF)//0xB80008A0[23:20];
																							//0: LVDS_C_EP,<AO>
																							//3: TCON_bit5,<O>
																							//4: ld_spi1_p3_sdo_SRC2,<I/O>
																							//C: misc_pwm_2,<OD>
																							//D: ld_spi0_p3_sdo_SRC2,<I/O>
																							//F: MIS_GPIO_bit103,<I/O>
																							//def: MIS_GPIO_bit103,<I/O>


// PAD_NAME: C_EN 87
#define RTD1295_BGA_PIN_AM32								(0x0&0xF)//0xB80008A0[19:16];
																							//0: LVDS_C_EN,<AO>
																							//3: TCON_bit7,<O>
																							//4: ld_spi1_p4_sdi_SRC2,<I>
																							//C: misc_pwm_3,<OD>
																							//D: ld_spi0_p4_sdi_SRC2,<I>
																							//F: MIS_GPIO_bit104,<I/O>
																							//def: MIS_GPIO_bit104,<I/O>


// PAD_NAME: C_DP 88
#define RTD1295_BGA_PIN_AK30								(0x0&0xF)//0xB80008A0[15:12];
																							//0: LVDS_C_DP,<AO>
																							//3: TCON_bit9,<O>
																							//7: VBY1_HTPD_src0,<I>
																							//C: misc_pwm_4,<OD>
																							//F: MIS_GPIO_bit105,<I/O>
																							//def: MIS_GPIO_bit105,<I/O>


// PAD_NAME: C_DN 89
#define RTD1295_BGA_PIN_AL32								(0x0&0xF)//0xB80008A0[11:8];
																							//0: LVDS_C_DN,<AO>
																							//3: TCON_bit11,<O>
																							//7: VBY1_LOCK_src0,<I>
																							//C: misc_pwm_5,<OD>
																							//F: MIS_GPIO_bit106,<I/O>
																							//def: MIS_GPIO_bit106,<I/O>


// PAD_NAME: C_CP 90
#define RTD1295_BGA_PIN_AK31								(0x0&0xF)//0xB80008A0[7:4];
																							//0: LVDS_C_CP,<AO>
																							//3: TCON_bit13,<O>
																							//C: misc_pwm_6,<OD>
																							//F: MIS_GPIO_bit107,<I/O>
																							//def: MIS_GPIO_bit107,<I/O>


// PAD_NAME: C_CN 91
#define RTD1295_BGA_PIN_AK32								(0x0&0xF)//0xB80008A0[3:0];
																							//0: LVDS_C_CN,<AO>
																							//3: TCON_bit15,<O>
																							//C: misc_pwm_7,<OD>
																							//F: MIS_GPIO_bit108,<I/O>
																							//def: MIS_GPIO_bit108,<I/O>


// PAD_NAME: C_BP 92
#define RTD1295_BGA_PIN_AJ31								(0x0&0xF)//0xB80008A4[31:28];
																							//0: LVDS_C_BP,<AO>
																							//3: TCON_bit17,<O>
																							//C: misc_pwm_0,<OD>
																							//F: MIS_GPIO_bit109,<I/O>
																							//def: MIS_GPIO_bit109,<I/O>


// PAD_NAME: C_BN 93
#define RTD1295_BGA_PIN_AJ32								(0x0&0xF)//0xB80008A4[27:24];
																							//0: LVDS_C_BN,<AO>
																							//3: TCON_bit19,<O>
																							//C: misc_pwm_1,<OD>
																							//F: MIS_GPIO_bit110,<I/O>
																							//def: MIS_GPIO_bit110,<I/O>


// PAD_NAME: C_AP 94
#define RTD1295_BGA_PIN_AJ30								(0x0&0xF)//0xB80008A4[23:20];
																							//0: LVDS_C_AP,<AO>
																							//3: TCON_bit21,<O>
																							//C: misc_pwm_2,<OD>
																							//F: MIS_GPIO_bit111,<I/O>
																							//def: MIS_GPIO_bit111,<I/O>


// PAD_NAME: C_AN 95
#define RTD1295_BGA_PIN_AH32								(0x0&0xF)//0xB80008A4[19:16];
																							//0: LVDS_C_AN,<AO>
																							//3: TCON_bit23,<O>
																							//C: misc_pwm_3,<OD>
																							//F: MIS_GPIO_bit112,<I/O>
																							//def: MIS_GPIO_bit112,<I/O>


// PAD_NAME: D_FP 96
#define RTD1295_BGA_PIN_AH31								(0x0&0xF)//0xB80008A8[31:28];
																							//0: LVDS_D_FP,<AO>
																							//3: TCON_bit17,<O>
																							//4: ld_spi1_p5_v_sync,<O>
																							//C: misc_pwm_4,<OD>
																							//D: ld_spi0_p5_v_sync,<O>
																							//F: MIS_GPIO_bit113,<I/O>
																							//def: MIS_GPIO_bit113,<I/O>


// PAD_NAME: D_FN 97
#define RTD1295_BGA_PIN_AH30								(0x0&0xF)//0xB80008A8[27:24];
																							//0: LVDS_D_FN,<AO>
																							//3: TCON_bit19,<O>
																							//4: ld_spi1_p6_h_sync,<O>
																							//C: misc_pwm_5,<OD>
																							//D: ld_spi0_p6_h_sync,<O>
																							//F: MIS_GPIO_bit114,<I/O>
																							//def: MIS_GPIO_bit114,<I/O>


// PAD_NAME: D_EP 98
#define RTD1295_BGA_PIN_AG31								(0x0&0xF)//0xB80008A8[23:20];
																							//0: LVDS_D_EP,<AO>
																							//3: TCON_bit21,<O>
																							//7: VBY1_HTPD_src1,<I>
																							//C: misc_pwm_6,<OD>
																							//F: MIS_GPIO_bit115,<I/O>
																							//def: MIS_GPIO_bit115,<I/O>


// PAD_NAME: D_EN 99
#define RTD1295_BGA_PIN_AG30								(0x0&0xF)//0xB80008A8[19:16];
																							//0: LVDS_D_EN,<AO>
																							//3: TCON_bit23,<O>
																							//7: VBY1_LOCK_src1,<I>
																							//C: misc_pwm_7,<OD>
																							//F: MIS_GPIO_bit116,<I/O>
																							//def: MIS_GPIO_bit116,<I/O>


// PAD_NAME: GPIO69 100
#define RTD1295_BGA_PIN_AJ25								(0x1&0xF)//0xB8000844[23:20];
																							//0: CR_SD_Data_bit5,<I/O>,<HS>
																							//1: PCMCIA_ADDR_bit10,<OD>,<HS>
																							//3: TCON_bit8,<O>
																							//C: misc_pwm_4,<OD>
																							//E: test_en_bit15,<I/O>
																							//F: MIS_GPIO_bit69,<I/O>
																							//def: MIS_GPIO_bit69,<I/O>
#define RTD1295_BGA_PIN_AJ25_UP							(1&0x01)// 0xB8000844[19]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AJ25_PD							(0&0x01)// 0xB8000844[18]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AJ25_DS							(0&0x01)// 0xB8000844[17]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AJ25_SR							(0&0x01)// 0xB8000844[16]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO70 101
#define RTD1295_BGA_PIN_AH25								(0x1&0xF)//0xB8000844[15:12];
																							//1: PCMCIA_OE_N,<O>,<HS>
																							//3: TCON_bit10,<O>
																							//C: misc_pwm_5,<OD>
																							//E: test_en_bit14,<I/O>
																							//F: MIS_GPIO_bit70,<I/O>
																							//def: MIS_GPIO_bit70,<I/O>
#define RTD1295_BGA_PIN_AH25_UP							(1&0x01)// 0xB8000844[11]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AH25_PD							(0&0x01)// 0xB8000844[10]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AH25_DS							(0&0x01)// 0xB8000844[9]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AH25_SR							(0&0x01)// 0xB8000844[8]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO71 102
#define RTD1295_BGA_PIN_AG25								(0x1&0xF)//0xB8000844[7:4];
																							//0: CR_SD_Data_bit6,<I/O>,<HS>
																							//1: PCMCIA_ADDR_bit9,<OD>,<HS>
																							//3: TCON_bit12,<O>
																							//C: misc_pwm_6,<OD>
																							//E: test_en_bit13,<I/O>
																							//F: MIS_GPIO_bit71,<I/O>
																							//def: MIS_GPIO_bit71,<I/O>
#define RTD1295_BGA_PIN_AG25_UP							(1&0x01)// 0xB8000844[3]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AG25_PD							(0&0x01)// 0xB8000844[2]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AG25_DS							(0&0x01)// 0xB8000844[1]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AG25_SR							(0&0x01)// 0xB8000844[0]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO72 103
#define RTD1295_BGA_PIN_AH26								(0x1&0xF)//0xB8000848[31:28];
																							//0: CR_SD_Data_bit7,<I/O>,<HS>
																							//1: PCMCIA_ADDR_bit11,<OD>,<HS>
																							//3: TCON_bit14,<O>
																							//C: misc_pwm_7,<OD>
																							//E: test_en_bit12,<I/O>
																							//F: MIS_GPIO_bit72,<I/O>
																							//def: MIS_GPIO_bit72,<I/O>
#define RTD1295_BGA_PIN_AH26_UP							(1&0x01)// 0xB8000848[27]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AH26_PD							(0&0x01)// 0xB8000848[26]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AH26_DS							(0&0x01)// 0xB8000848[25]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AH26_SR							(0&0x01)// 0xB8000848[24]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO73 104
#define RTD1295_BGA_PIN_AJ27								(0x1&0xF)//0xB8000848[23:20];
																							//1: PCMCIA_ADDR_bit8,<OD>,<HS>
																							//3: TCON_bit16,<O>
																							//6: SC_SCLK,<OD>
																							//A: USB_PWR_FLAG2,<I>
																							//B: USB_PWR_CTRL2,<O>
																							//C: misc_pwm_0,<OD>
																							//E: test_en_bit11,<I/O>
																							//F: MIS_GPIO_bit73,<I/O>
																							//def: MIS_GPIO_bit73,<I/O>
#define RTD1295_BGA_PIN_AJ27_UP							(1&0x01)// 0xB8000848[19]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AJ27_PD							(0&0x01)// 0xB8000848[18]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AJ27_DS							(0&0x01)// 0xB8000848[17]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AJ27_SR							(0&0x01)// 0xB8000848[16]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO74 105
#define RTD1295_BGA_PIN_AC32								(0x1&0xF)//0xB8000848[15:12];
																							//1: PCMCIA_ADDR_bit13,<OD>,<HS>
																							//3: TCON_bit18,<O>
																							//6: SC_DATA_SRC2,<I/O>
																							//A: USB_PWR_CTRL3,<O>
																							//B: USB_PWR_FLAG3,<I>
																							//C: misc_pwm_1,<OD>
																							//E: test_en_bit10,<I/O>
																							//F: MIS_GPIO_bit74,<I/O>
																							//def: MIS_GPIO_bit74,<I/O>
#define RTD1295_BGA_PIN_AC32_UP							(1&0x01)// 0xB8000848[11]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AC32_PD							(0&0x01)// 0xB8000848[10]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AC32_DS							(0&0x01)// 0xB8000848[9]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AC32_SR							(0&0x01)// 0xB8000848[8]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO75 106
#define RTD1295_BGA_PIN_AC31								(0x1&0xF)//0xB8000848[7:4];
																							//1: PCMCIA_ADDR_bit14,<OD>,<HS>
																							//3: TCON_bit20,<O>
																							//6: SC_RST,<OD>
																							//C: misc_pwm_2,<OD>
																							//E: test_en_bit9,<I/O>
																							//F: MIS_GPIO_bit75,<I/O>
																							//def: MIS_GPIO_bit75,<I/O>
#define RTD1295_BGA_PIN_AC31_UP							(1&0x01)// 0xB8000848[3]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AC31_PD							(0&0x01)// 0xB8000848[2]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AC31_DS							(0&0x01)// 0xB8000848[1]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AC31_SR							(0&0x01)// 0xB8000848[0]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO76 107
#define RTD1295_BGA_PIN_AC30								(0x1&0xF)//0xB800084C[31:28];
																							//1: PCMCIA_WE_N,<O>,<HS>
																							//3: TCON_bit22,<O>
																							//6: SC_CD_SRC2,<I>
																							//C: misc_pwm_3,<OD>
																							//E: test_en_bit8,<I/O>
																							//F: MIS_GPIO_bit76,<I/O>
																							//def: MIS_GPIO_bit76,<I/O>
#define RTD1295_BGA_PIN_AC30_UP							(1&0x01)// 0xB800084C[27]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AC30_PD							(0&0x01)// 0xB800084C[26]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AC30_DS							(0&0x01)// 0xB800084C[25]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AC30_SR							(0&0x01)// 0xB800084C[24]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO77 108
#define RTD1295_BGA_PIN_AB30								(0x1&0xF)//0xB800084C[23:20];
																							//1: PCMCIA_IREQ0_N,<I>,<HS>
																							//3: TCON_bit1,<O>
																							//C: misc_pwm_4,<OD>
																							//E: test_en_bit7,<I/O>
																							//F: MIS_GPIO_bit77,<I/O>
																							//def: MIS_GPIO_bit77,<I/O>
#define RTD1295_BGA_PIN_AB30_UP							(1&0x01)// 0xB800084C[19]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AB30_PD							(0&0x01)// 0xB800084C[18]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AB30_DS							(0&0x01)// 0xB800084C[17]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AB30_SR							(0&0x01)// 0xB800084C[16]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO78 109
#define RTD1295_BGA_PIN_AB29								(0x1&0xF)//0xB800084C[15:12];
																							//1: PCMCIA_ADDR_bit12,<OD>,<HS>
																							//3: TCON_bit3,<O>
																							//C: misc_pwm_5,<OD>
																							//E: test_en_bit6,<I/O>
																							//F: MIS_GPIO_bit78,<I/O>
																							//def: MIS_GPIO_bit78,<I/O>
#define RTD1295_BGA_PIN_AB29_UP							(1&0x01)// 0xB800084C[11]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AB29_PD							(0&0x01)// 0xB800084C[10]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AB29_DS							(0&0x01)// 0xB800084C[9]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AB29_SR							(0&0x01)// 0xB800084C[8]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO79 110
#define RTD1295_BGA_PIN_AD29								(0x1&0xF)//0xB800084C[7:4];
																							//1: PCMCIA_ADDR_bit6,<OD>,<HS>
																							//3: TCON_bit5,<O>
																							//C: misc_pwm_6,<OD>
																							//E: test_en_bit5,<I/O>
																							//F: MIS_GPIO_bit79,<I/O>
																							//def: MIS_GPIO_bit79,<I/O>
#define RTD1295_BGA_PIN_AD29_UP							(1&0x01)// 0xB800084C[3]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AD29_PD							(0&0x01)// 0xB800084C[2]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AD29_DS							(0&0x01)// 0xB800084C[1]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AD29_SR							(0&0x01)// 0xB800084C[0]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO80 111
#define RTD1295_BGA_PIN_AC29								(0x1&0xF)//0xB8000850[31:28];
																							//1: PCMCIA_ADDR_bit7,<OD>,<HS>
																							//3: TCON_bit7,<O>
																							//C: misc_pwm_7,<OD>
																							//E: test_en_bit4,<I/O>
																							//F: MIS_GPIO_bit80,<I/O>
																							//def: MIS_GPIO_bit80,<I/O>
#define RTD1295_BGA_PIN_AC29_UP							(1&0x01)// 0xB8000850[27]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AC29_PD							(0&0x01)// 0xB8000850[26]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AC29_DS							(0&0x01)// 0xB8000850[25]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AC29_SR							(0&0x01)// 0xB8000850[24]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO81 112
#define RTD1295_BGA_PIN_AC28								(0x1&0xF)//0xB8000850[23:20];
																							//1: PCMCIA_ADDR_bit4,<OD>,<HS>
																							//3: TCON_bit9,<O>
																							//C: misc_pwm_0,<OD>
																							//E: test_en_bit3,<I/O>
																							//F: MIS_GPIO_bit81,<I/O>
																							//def: MIS_GPIO_bit81,<I/O>
#define RTD1295_BGA_PIN_AC28_UP							(1&0x01)// 0xB8000850[19]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AC28_PD							(0&0x01)// 0xB8000850[18]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AC28_DS							(0&0x01)// 0xB8000850[17]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AC28_SR							(0&0x01)// 0xB8000850[16]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO82 113
#define RTD1295_BGA_PIN_AB28								(0x1&0xF)//0xB8000850[15:12];
																							//1: PCMCIA_ADDR_bit5,<OD>,<HS>
																							//3: TCON_bit11,<O>
																							//C: misc_pwm_1,<OD>
																							//E: test_en_bit2,<I/O>
																							//F: MIS_GPIO_bit82,<I/O>
																							//def: MIS_GPIO_bit82,<I/O>
#define RTD1295_BGA_PIN_AB28_UP							(1&0x01)// 0xB8000850[11]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AB28_PD							(0&0x01)// 0xB8000850[10]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AB28_DS							(0&0x01)// 0xB8000850[9]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AB28_SR							(0&0x01)// 0xB8000850[8]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO83 114
#define RTD1295_BGA_PIN_T27								(0x1&0xF)//0xB8000850[7:4];
																							//1: PCMCIA_ADDR_bit2,<OD>,<HS>
																							//3: TCON_bit13,<O>
																							//C: misc_pwm_2,<OD>
																							//E: test_en_bit1,<I/O>
																							//F: MIS_GPIO_bit83,<I/O>
																							//def: MIS_GPIO_bit83,<I/O>
#define RTD1295_BGA_PIN_T27_UP							(1&0x01)// 0xB8000850[3]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_T27_PD							(0&0x01)// 0xB8000850[2]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_T27_DS							(0&0x01)// 0xB8000850[1]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_T27_SR							(0&0x01)// 0xB8000850[0]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO84 115
#define RTD1295_BGA_PIN_R27								(0x1&0xF)//0xB8000854[31:28];
																							//1: PCMCIA_ADDR_bit3,<OD>,<HS>
																							//3: TCON_bit15,<O>
																							//C: misc_pwm_3,<OD>
																							//E: test_en_bit0,<I/O>
																							//F: MIS_GPIO_bit84,<I/O>
																							//def: MIS_GPIO_bit84,<I/O>
#define RTD1295_BGA_PIN_R27_UP							(1&0x01)// 0xB8000854[27]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_R27_PD							(0&0x01)// 0xB8000854[26]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_R27_DS							(0&0x01)// 0xB8000854[25]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_R27_SR							(0&0x01)// 0xB8000854[24]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO0 116
#define RTD1295_BGA_PIN_G5								(0x6&0xF)//0xB8000800[31:28];
																							//3: TCON_bit18,<O>
																							//6: EPI_LOCK_src0,<I>
																							//7: VBY1_HTPD_src2,<I>
																							//F: MIS_GPIO_bit0,<I/O>
																							//def: MIS_GPIO_bit0,<I/O>
#define RTD1295_BGA_PIN_G5_UP							(1&0x01)// 0xB8000800[27]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_G5_PD							(0&0x01)// 0xB8000800[26]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_G5_DS							(0&0x01)// 0xB8000800[25]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_G5_SR							(0&0x01)// 0xB8000800[24]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO117 117
#define RTD1295_BGA_PIN_B8								(0xB&0xF)//0xB8000858[23:20];
																							//3: TCON_bit20,<O>
																							//B: I2S_out_SCLK,<O>
																							//F: MIS_GPIO_bit117,<I/O>
																							//def: MIS_GPIO_bit117,<I/O>
#define RTD1295_BGA_PIN_B8_UP							(1&0x01)// 0xB8000858[19]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_B8_PD							(0&0x01)// 0xB8000858[18]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_B8_DS							(0&0x01)// 0xB8000858[17]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_B8_SR							(0&0x01)// 0xB8000858[16]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO118 118
#define RTD1295_BGA_PIN_C8								(0xB&0xF)//0xB8000858[15:12];
																							//3: TCON_bit22,<O>
																							//B: I2S_out_WCLK,<O>
																							//F: MIS_GPIO_bit118,<I/O>
																							//def: MIS_GPIO_bit118,<I/O>
#define RTD1295_BGA_PIN_C8_UP							(1&0x01)// 0xB8000858[11]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_C8_PD							(0&0x01)// 0xB8000858[10]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_C8_DS							(0&0x01)// 0xB8000858[9]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_C8_SR							(0&0x01)// 0xB8000858[8]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO119 119
#define RTD1295_BGA_PIN_D8								(0xB&0xF)//0xB8000858[7:4];
																							//3: TCON_bit0,<O>
																							//B: I2S_out_MCLK,<O>
																							//F: MIS_GPIO_bit119,<I/O>
																							//def: MIS_GPIO_bit119,<I/O>
#define RTD1295_BGA_PIN_D8_UP							(1&0x01)// 0xB8000858[3]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_D8_PD							(0&0x01)// 0xB8000858[2]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_D8_DS							(0&0x01)// 0xB8000858[1]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_D8_SR							(0&0x01)// 0xB8000858[0]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO120 120
#define RTD1295_BGA_PIN_E8								(0xB&0xF)//0xB800085C[31:28];
																							//3: TCON_bit2,<O>
																							//6: ETN_LED_LINK,<O>
																							//B: I2S_out_Data0,<O>
																							//C: misc_pwm_2,<OD>
																							//F: MIS_GPIO_bit120,<I/O>
																							//def: MIS_GPIO_bit120,<I/O>
#define RTD1295_BGA_PIN_E8_UP							(1&0x01)// 0xB800085C[27]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_E8_PD							(0&0x01)// 0xB800085C[26]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_E8_DS							(0&0x01)// 0xB800085C[25]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_E8_SR							(0&0x01)// 0xB800085C[24]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO121 121
#define RTD1295_BGA_PIN_A7								(0xF&0xF)//0xB800085C[23:20];
																							//3: TCON_bit4,<O>
																							//6: ETN_LED_TXRX,<O>
																							//B: I2S_out_Data1,<O>
																							//C: misc_pwm_3,<OD>
																							//F: MIS_GPIO_bit121,<I/O>
																							//def: MIS_GPIO_bit121,<I/O>
#define RTD1295_BGA_PIN_A7_UP							(1&0x01)// 0xB800085C[19]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_A7_PD							(0&0x01)// 0xB800085C[18]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_A7_DS							(0&0x01)// 0xB800085C[17]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_A7_SR							(0&0x01)// 0xB800085C[16]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO122 122
#define RTD1295_BGA_PIN_B7								(0x0&0xF)//0xB800085C[15:12];
																							//0: SPI_CS_N,<O>,<HS>
																							//3: TCON_bit6,<O>
																							//4: ld_spi1_p1_cs1,<O>
																							//A: I2S_in_WCLK_SRC0,<I>
																							//B: I2S_out_Data2,<O>
																							//C: misc_pwm_4,<OD>
																							//D: ld_spi0_p1_cs1,<O>
																							//F: MIS_GPIO_bit122,<I/O>
																							//def: MIS_GPIO_bit122,<I/O>
#define RTD1295_BGA_PIN_B7_UP							(1&0x01)// 0xB800085C[11]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_B7_PD							(0&0x01)// 0xB800085C[10]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_B7_DS							(0&0x01)// 0xB800085C[9]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_B7_SR							(0&0x01)// 0xB800085C[8]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO123 123
#define RTD1295_BGA_PIN_C7								(0x0&0xF)//0xB800085C[7:4];
																							//0: SPI_SCLK,<O>,<HS>
																							//3: TCON_bit8,<O>
																							//4: ld_spi1_p2_sck_src4,<I/O>
																							//6: EPI_LOCK_src1,<I>
																							//7: VBY1_LOCK_src2,<I>
																							//A: I2S_in_MCLK_SRC0,<I>
																							//B: I2S_out_Data3,<O>
																							//C: misc_pwm_5,<OD>
																							//D: ld_spi0_p2_sck_src4,<I/O>
																							//F: MIS_GPIO_bit123,<I/O>
																							//def: MIS_GPIO_bit123,<I/O>
#define RTD1295_BGA_PIN_C7_UP							(1&0x01)// 0xB800085C[3]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_C7_PD							(0&0x01)// 0xB800085C[2]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_C7_DS							(0&0x01)// 0xB800085C[1]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_C7_SR							(0&0x01)// 0xB800085C[0]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO124 124
#define RTD1295_BGA_PIN_D7								(0xF&0xF)//0xB8000860[31:28];
																							//3: TCON_bit10,<O>
																							//4: ld_spi1_p3_sdo_SRC4,<I/O>
																							//A: I2S_in_Data0,<I>
																							//C: misc_pwm_6,<OD>
																							//D: ld_spi0_p3_sdo_SRC4,<I/O>
																							//F: MIS_GPIO_bit124,<I/O>
																							//def: MIS_GPIO_bit124,<I/O>
#define RTD1295_BGA_PIN_D7_UP							(1&0x01)// 0xB8000860[27]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_D7_PD							(0&0x01)// 0xB8000860[26]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_D7_DS							(0&0x01)// 0xB8000860[25]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_D7_SR							(0&0x01)// 0xB8000860[24]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO125 125
#define RTD1295_BGA_PIN_B6								(0x0&0xF)//0xB8000860[23:20];
																							//0: SPI_DI,<I/O>,<HS>
																							//3: TCON_bit12,<O>
																							//5: I2C2_SCL_SRC0,<I/O>
																							//6: SC_SCLK,<OD>
																							//9: uart2_rxdi_src2,<I>
																							//A: I2S_in_SCLK,<I>
																							//C: misc_pwm_7,<OD>
																							//F: MIS_GPIO_bit125,<I/O>
																							//def: MIS_GPIO_bit125,<I/O>
#define RTD1295_BGA_PIN_B6_UP							(1&0x01)// 0xB8000860[19]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_B6_PD							(0&0x01)// 0xB8000860[18]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_B6_DS							(0&0x01)// 0xB8000860[17]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_B6_SR							(0&0x01)// 0xB8000860[16]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO126 126
#define RTD1295_BGA_PIN_C6								(0x0&0xF)//0xB8000860[15:12];
																							//0: SPI_DO,<I/O>,<HS>
																							//3: TCON_bit14,<O>
																							//5: I2C2_SDA_SRC0,<I/O>
																							//6: SC_DATA_SRC3,<I/O>
																							//9: uart2_txdo,<O>
																							//A: I2S_in_Data1_SRC0,<I>
																							//C: misc_pwm_0,<OD>
																							//F: MIS_GPIO_bit126,<I/O>
																							//def: MIS_GPIO_bit126,<I/O>
#define RTD1295_BGA_PIN_C6_UP							(1&0x01)// 0xB8000860[11]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_C6_PD							(0&0x01)// 0xB8000860[10]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_C6_DS							(0&0x01)// 0xB8000860[9]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_C6_SR							(0&0x01)// 0xB8000860[8]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO127 127
#define RTD1295_BGA_PIN_A5								(0xF&0xF)//0xB8000860[7:4];
																							//3: TCON_bit16,<O>
																							//4: ld_spi1_p4_sdi_SRC4,<I>
																							//A: I2S_in_WCLK_SRC1,<I>
																							//C: misc_pwm_1,<OD>
																							//D: ld_spi0_p4_sdi_SRC4,<I>
																							//F: MIS_GPIO_bit127,<I/O>
																							//def: MIS_GPIO_bit127,<I/O>
#define RTD1295_BGA_PIN_A5_UP							(1&0x01)// 0xB8000860[3]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_A5_PD							(0&0x01)// 0xB8000860[2]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_A5_DS							(0&0x01)// 0xB8000860[1]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_A5_SR							(0&0x01)// 0xB8000860[0]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO128 128
#define RTD1295_BGA_PIN_B5								(0x7&0xF)//0xB8000864[31:28];
																							//4: ld_spi1_p1_cs1,<O>
																							//5: I2C2_SCL_SRC1,<I/O>
																							//6: SC_RST,<OD>
																							//7: VBY1_HTPD_src3,<I>
																							//8: uart1_rxdi_src3,<I>
																							//9: uart0_rxdi_src0,<I>
																							//A: I2S_in_MCLK_SRC1,<I>
																							//C: misc_pwm_2,<OD>
																							//D: ld_spi0_p1_cs1,<O>
																							//F: MIS_GPIO_bit128,<I/O>
																							//def: MIS_GPIO_bit128,<I/O>
#define RTD1295_BGA_PIN_B5_UP							(1&0x01)// 0xB8000864[27]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_B5_PD							(0&0x01)// 0xB8000864[26]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_B5_DS							(0&0x01)// 0xB8000864[25]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_B5_SR							(0&0x01)// 0xB8000864[24]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO129 129
#define RTD1295_BGA_PIN_C5								(0x7&0xF)//0xB8000864[23:20];
																							//4: ld_spi1_p2_sck_src5,<I/O>
																							//5: I2C2_SDA_SRC1,<I/O>
																							//6: SC_CD_SRC3,<I>
																							//7: VBY1_LOCK_src3,<I>
																							//8: uart1_txdo,<O>
																							//9: uart0_txdo,<O>
																							//A: I2S_in_Data1_SRC1,<I>
																							//C: misc_pwm_3,<OD>
																							//D: ld_spi0_p2_sck_src5,<I/O>
																							//F: MIS_GPIO_bit129,<I/O>
																							//def: MIS_GPIO_bit129,<I/O>
#define RTD1295_BGA_PIN_C5_UP							(1&0x01)// 0xB8000864[19]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_C5_PD							(0&0x01)// 0xB8000864[18]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_C5_DS							(0&0x01)// 0xB8000864[17]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_C5_SR							(0&0x01)// 0xB8000864[16]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO130 130
#define RTD1295_BGA_PIN_B4								(0x6&0xF)//0xB8000864[15:12];
																							//6: GETN_LED_LINK,<O>
																							//A: I2S_in_Data2,<I>
																							//C: misc_pwm_6,<OD>
																							//F: MIS_GPIO_bit130,<I/O>
																							//def: MIS_GPIO_bit130,<I/O>
#define RTD1295_BGA_PIN_B4_UP							(1&0x01)// 0xB8000864[11]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_B4_PD							(0&0x01)// 0xB8000864[10]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_B4_DS							(0&0x01)// 0xB8000864[9]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_B4_SR							(0&0x01)// 0xB8000864[8]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO131 131
#define RTD1295_BGA_PIN_C4								(0x6&0xF)//0xB8000864[7:4];
																							//6: GETN_LED_RXTX,<O>
																							//A: I2S_in_Data3,<I>
																							//C: misc_pwm_7,<OD>
																							//F: MIS_GPIO_bit131,<I/O>
																							//def: MIS_GPIO_bit131,<I/O>
#define RTD1295_BGA_PIN_C4_UP							(1&0x01)// 0xB8000864[3]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_C4_PD							(0&0x01)// 0xB8000864[2]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_C4_DS							(0&0x01)// 0xB8000864[1]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_C4_SR							(0&0x01)// 0xB8000864[0]: Slew rate 0:fast 1:slow


// PAD_NAME: LSADC_REF 132
#define RTD1295_BGA_PIN_E1								(0xC&0xF)//0xB8060208[27:24];
																							//C: LSADC_REF,<AI>
																							//F: ISO_MIS_GPIO_bit17,<I/O>
																							//def: ISO_MIS_GPIO_bit17,<I/O>


// PAD_NAME: LSADC0 133
#define RTD1295_BGA_PIN_E2								(0xC&0xF)//0xB8060208[3:0];
																							//C: LSADC0,<AI>
																							//F: ISO_MIS_GPIO_bit14,<I/O>
																							//def: ISO_MIS_GPIO_bit14,<I/O>


// PAD_NAME: LSADC1 134
#define RTD1295_BGA_PIN_E3								(0xC&0xF)//0xB8060208[7:4];
																							//C: LSADC1,<AI>
																							//F: ISO_MIS_GPIO_bit15,<I/O>
																							//def: ISO_MIS_GPIO_bit15,<I/O>


// PAD_NAME: LSADC2 135
#define RTD1295_BGA_PIN_F2								(0xF&0xF)//0xB8060208[11:8];
																							//C: LSADC2,<AI>
																							//F: ISO_MIS_GPIO_bit16,<I/O>
																							//def: ISO_MIS_GPIO_bit16,<I/O>


// PAD_NAME: LSADC4 136
#define RTD1295_BGA_PIN_F3								(0xF&0xF)//0xB8060208[15:12];
																							//C: LSADC4,<AI>
																							//F: ISO_MIS_GPIO_bit18,<I/O>
																							//def: ISO_MIS_GPIO_bit18,<I/O>


// PAD_NAME: LSADC6 137
#define RTD1295_BGA_PIN_G2								(0xF&0xF)//0xB8060208[19:16];
																							//C: LSADC6,<AI>
																							//F: ISO_MIS_GPIO_bit19,<I/O>
																							//def: ISO_MIS_GPIO_bit19,<I/O>


// PAD_NAME: LSADC7 138
#define RTD1295_BGA_PIN_G3								(0xF&0xF)//0xB8060208[23:20];
																							//C: LSADC7,<AI>
																							//F: ISO_MIS_GPIO_bit20,<I/O>
																							//def: ISO_MIS_GPIO_bit20,<I/O>


// PAD_NAME: ST_GPIO8 139
#define RTD1295_BGA_PIN_J6								(0xF&0xF)//0xB806022C[7:4];
																							//3: TCON_bit17,<O>
																							//7: IRTX,<O>
																							//A: SPDIF_OUT,<O>
																							//F: ISO_MIS_GPIO_bit8,<I/O>
																							//def: ISO_MIS_GPIO_bit8,<I/O>
#define RTD1295_BGA_PIN_J6_UP							(1&0x01)// 0xB806022C[3]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_J6_PD							(0&0x01)// 0xB806022C[2]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_J6_DS							(0&0x01)// 0xB806022C[1]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_J6_SR							(0&0x01)// 0xB806022C[0]: Slew rate 0:fast 1:slow


// PAD_NAME: ST_GPIO9 140
#define RTD1295_BGA_PIN_K5								(0xF&0xF)//0xB806022C[15:12];
																							//3: TCON_bit19,<O>
																							//A: SPDIF_OUT,<O>
																							//F: ISO_MIS_GPIO_bit9,<I/O>
																							//def: ISO_MIS_GPIO_bit9,<I/O>
#define RTD1295_BGA_PIN_K5_UP							(1&0x01)// 0xB806022C[11]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_K5_PD							(0&0x01)// 0xB806022C[10]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_K5_DS							(0&0x01)// 0xB806022C[9]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_K5_SR							(0&0x01)// 0xB806022C[8]: Slew rate 0:fast 1:slow


// PAD_NAME: ST_GPIO0 141
#define RTD1295_BGA_PIN_J5								(0xF&0xF)//0xB8060234[7:4];
																							//3: TCON_bit1,<O>
																							//C: misc_pwm_4,<OD>
																							//D: iso_misc_pwm_0,<OD>
																							//E: st_dbg_bit0,<I/O>
																							//F: ISO_MIS_GPIO_bit0,<I/O>
																							//def: ISO_MIS_GPIO_bit0,<I/O>
#define RTD1295_BGA_PIN_J5_UP							(1&0x01)// 0xB8060234[3]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_J5_PD							(0&0x01)// 0xB8060234[2]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_J5_DS							(0&0x01)// 0xB8060234[1]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_J5_SR							(0&0x01)// 0xB8060234[0]: Slew rate 0:fast 1:slow


// PAD_NAME: ST_GPIO10 142
#define RTD1295_BGA_PIN_M5								(0xF&0xF)//0xB806022C[23:20];
																							//3: TCON_bit21,<O>
																							//A: SPDIF_OUT,<O>
																							//F: ISO_MIS_GPIO_bit10,<I/O>
																							//def: ISO_MIS_GPIO_bit10,<I/O>
#define RTD1295_BGA_PIN_M5_UP							(1&0x01)// 0xB806022C[19]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_M5_PD							(0&0x01)// 0xB806022C[18]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_M5_DS							(0&0x01)// 0xB806022C[17]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_M5_SR							(0&0x01)// 0xB806022C[16]: Slew rate 0:fast 1:slow


// PAD_NAME: ST_GPIO1 143
#define RTD1295_BGA_PIN_K4								(0xF&0xF)//0xB8060234[15:12];
																							//3: TCON_bit3,<O>
																							//C: misc_pwm_5,<OD>
																							//D: iso_misc_pwm_1,<OD>
																							//E: st_dbg_bit1,<I/O>
																							//F: ISO_MIS_GPIO_bit1,<I/O>
																							//def: ISO_MIS_GPIO_bit1,<I/O>
#define RTD1295_BGA_PIN_K4_UP							(1&0x01)// 0xB8060234[11]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_K4_PD							(0&0x01)// 0xB8060234[10]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_K4_DS							(0&0x01)// 0xB8060234[9]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_K4_SR							(0&0x01)// 0xB8060234[8]: Slew rate 0:fast 1:slow


// PAD_NAME: ST_GPIO11 144
#define RTD1295_BGA_PIN_N4								(0xF&0xF)//0xB806022C[31:28];
																							//3: TCON_bit23,<O>
																							//D: iso_misc_pwm_0,<OD>
																							//E: st_dbg_bit8,<I/O>
																							//F: ISO_MIS_GPIO_bit11,<I/O>
																							//def: ISO_MIS_GPIO_bit11,<I/O>
#define RTD1295_BGA_PIN_N4_UP							(1&0x01)// 0xB806022C[27]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_N4_PD							(0&0x01)// 0xB806022C[26]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_N4_DS							(0&0x01)// 0xB806022C[25]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_N4_SR							(0&0x01)// 0xB806022C[24]: Slew rate 0:fast 1:slow


// PAD_NAME: ST_GPIO2 145
#define RTD1295_BGA_PIN_K6								(0xF&0xF)//0xB8060234[23:20];
																							//3: TCON_bit5,<O>
																							//C: misc_pwm_6,<OD>
																							//D: iso_misc_pwm_0,<OD>
																							//E: st_dbg_bit2,<I/O>
																							//F: ISO_MIS_GPIO_bit2,<I/O>
																							//def: ISO_MIS_GPIO_bit2,<I/O>
#define RTD1295_BGA_PIN_K6_UP							(1&0x01)// 0xB8060234[19]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_K6_PD							(0&0x01)// 0xB8060234[18]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_K6_DS							(0&0x01)// 0xB8060234[17]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_K6_SR							(0&0x01)// 0xB8060234[16]: Slew rate 0:fast 1:slow


// PAD_NAME: ST_GPIO3 146
#define RTD1295_BGA_PIN_M6								(0xF&0xF)//0xB8060234[31:28];
																							//3: TCON_bit7,<O>
																							//C: misc_pwm_7,<OD>
																							//D: iso_misc_pwm_1,<OD>
																							//E: st_dbg_bit3,<I/O>
																							//F: ISO_MIS_GPIO_bit3,<I/O>
																							//def: ISO_MIS_GPIO_bit3,<I/O>
#define RTD1295_BGA_PIN_M6_UP							(1&0x01)// 0xB8060234[27]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_M6_PD							(0&0x01)// 0xB8060234[26]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_M6_DS							(0&0x01)// 0xB8060234[25]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_M6_SR							(0&0x01)// 0xB8060234[24]: Slew rate 0:fast 1:slow


// PAD_NAME: ST_GPIO12 147
#define RTD1295_BGA_PIN_N6								(0xF&0xF)//0xB8060228[7:4];
																							//D: iso_misc_pwm_1,<OD>
																							//E: st_dbg_bit9,<I/O>
																							//F: ISO_MIS_GPIO_bit12,<I/O>
																							//def: ISO_MIS_GPIO_bit12,<I/O>
#define RTD1295_BGA_PIN_N6_UP							(1&0x01)// 0xB8060228[3]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_N6_PD							(0&0x01)// 0xB8060228[2]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_N6_DS							(0&0x01)// 0xB8060228[1]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_N6_SR							(0&0x01)// 0xB8060228[0]: Slew rate 0:fast 1:slow


// PAD_NAME: ST_GPIO4 148
#define RTD1295_BGA_PIN_N5								(0xF&0xF)//0xB8060230[7:4];
																							//3: TCON_bit9,<O>
																							//C: misc_pwm_0,<OD>
																							//D: iso_misc_pwm_0,<OD>
																							//E: st_dbg_bit4,<I/O>
																							//F: ISO_MIS_GPIO_bit4,<I/O>
																							//def: ISO_MIS_GPIO_bit4,<I/O>
#define RTD1295_BGA_PIN_N5_UP							(1&0x01)// 0xB8060230[3]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_N5_PD							(0&0x01)// 0xB8060230[2]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_N5_DS							(0&0x01)// 0xB8060230[1]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_N5_SR							(0&0x01)// 0xB8060230[0]: Slew rate 0:fast 1:slow


// PAD_NAME: ST_GPIO5 149
#define RTD1295_BGA_PIN_R5								(0xC&0xF)//0xB8060230[15:12];
																							//3: TCON_bit11,<O>
																							//C: misc_pwm_1,<OD>
																							//D: iso_misc_pwm_1,<OD>
																							//E: st_dbg_bit5,<I/O>
																							//F: ISO_MIS_GPIO_bit5,<I/O>
																							//def: ISO_MIS_GPIO_bit5,<I/O>
#define RTD1295_BGA_PIN_R5_UP							(1&0x01)// 0xB8060230[11]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_R5_PD							(0&0x01)// 0xB8060230[10]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_R5_DS							(0&0x01)// 0xB8060230[9]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_R5_SR							(0&0x01)// 0xB8060230[8]: Slew rate 0:fast 1:slow


// PAD_NAME: ST_GPIO6 150
#define RTD1295_BGA_PIN_R6								(0xF&0xF)//0xB8060230[23:20];
																							//3: TCON_bit13,<O>
																							//C: misc_pwm_2,<OD>
																							//D: iso_misc_pwm_0,<OD>
																							//E: st_dbg_bit6,<I/O>
																							//F: ISO_MIS_GPIO_bit6,<I/O>
																							//def: ISO_MIS_GPIO_bit6,<I/O>
#define RTD1295_BGA_PIN_R6_UP							(1&0x01)// 0xB8060230[19]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_R6_PD							(0&0x01)// 0xB8060230[18]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_R6_DS							(0&0x01)// 0xB8060230[17]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_R6_SR							(0&0x01)// 0xB8060230[16]: Slew rate 0:fast 1:slow


// PAD_NAME: ST_GPIO7 151
#define RTD1295_BGA_PIN_T4								(0xA&0xF)//0xB8060230[31:28];
																							//3: TCON_bit15,<O>
																							//A: SPDIF_OUT,<O>
																							//C: misc_pwm_3,<OD>
																							//D: iso_misc_pwm_1,<OD>
																							//E: st_dbg_bit7,<I/O>
																							//F: ISO_MIS_GPIO_bit7,<I/O>
																							//def: ISO_MIS_GPIO_bit7,<I/O>
#define RTD1295_BGA_PIN_T4_UP							(1&0x01)// 0xB8060230[27]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_T4_PD							(0&0x01)// 0xB8060230[26]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_T4_DS							(0&0x01)// 0xB8060230[25]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_T4_SR							(0&0x01)// 0xB8060230[24]: Slew rate 0:fast 1:slow


// PAD_NAME: ST_GPIO22 152
#define RTD1295_BGA_PIN_U6								(0x9&0xF)//0xB8060228[31:28];
																							//3: DEMOD_I2C_DBG_SCL,<I>
																							//5: I2C0_SCL_SRC0,<I/O>
																							//8: uart1_rxdi_src4,<I>
																							//9: uart0_rxdi_src1,<I>
																							//F: ISO_MIS_GPIO_bit22,<I/O>
																							//def: ISO_MIS_GPIO_bit22,<I/O>
#define RTD1295_BGA_PIN_U6_UP							(1&0x01)// 0xB8060228[27]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_U6_PD							(0&0x01)// 0xB8060228[26]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_U6_DS							(0&0x01)// 0xB8060228[25]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_U6_SR							(0&0x01)// 0xB8060228[24]: Slew rate 0:fast 1:slow


// PAD_NAME: VSCL 153
#define RTD1295_BGA_PIN_U5								(0x8&0xF)//0xB8060200[15:12];
																							//4: VDDC_SCL,<I>
																							//5: I2C0_SCL_SRC1,<I/O>
																							//7: ISO_DDC_SCL_src0,<I>
																							//8: uart1_rxdi_src5,<I>
																							//9: uart0_rxdi_src2,<I>
																							//F: ISO_MIS_GPIO_bit24,<I/O>
																							//def: ISO_MIS_GPIO_bit24,<I/O>
#define RTD1295_BGA_PIN_U5_UP							(1&0x01)// 0xB8060200[11]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_U5_PD							(0&0x01)// 0xB8060200[10]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_U5_DS							(0&0x01)// 0xB8060200[9]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_U5_SR							(0&0x01)// 0xB8060200[8]: Slew rate 0:fast 1:slow


// PAD_NAME: ST_GPIO13 154
#define RTD1295_BGA_PIN_T5								(0x7&0xF)//0xB8060228[15:12];
																							//7: irrx_src0,<I>
																							//F: ISO_MIS_GPIO_bit13,<I/O>
																							//def: ISO_MIS_GPIO_bit13,<I/O>
#define RTD1295_BGA_PIN_T5_UP							(1&0x01)// 0xB8060228[11]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_T5_PD							(0&0x01)// 0xB8060228[10]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_T5_DS							(0&0x01)// 0xB8060228[9]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_T5_SR							(0&0x01)// 0xB8060228[8]: Slew rate 0:fast 1:slow


// PAD_NAME: ST_GPIO26 155
#define RTD1295_BGA_PIN_H4								(0xF&0xF)//0xB8060224[15:12];
																							//E: st_dbg_bit11,<I/O>
																							//F: ISO_MIS_GPIO_bit26,<I/O>
																							//def: ISO_MIS_GPIO_bit26,<I/O>
#define RTD1295_BGA_PIN_H4_UP							(1&0x01)// 0xB8060224[11]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_H4_PD							(0&0x01)// 0xB8060224[10]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_H4_DS							(0&0x01)// 0xB8060224[9]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_H4_SR							(0&0x01)// 0xB8060224[8]: Slew rate 0:fast 1:slow


// PAD_NAME: ST_GPIO21 156
#define RTD1295_BGA_PIN_T6								(0xA&0xF)//0xB8060228[23:20];
																							//6: VSYNC_DIG,<I>
																							//7: irrx_src1,<I>
																							//A: SPDIF_OUT,<O>
																							//D: iso_misc_pwm_1,<OD>
																							//E: st_dbg_bit10,<I/O>
																							//F: ISO_MIS_GPIO_bit21,<I/O>
																							//def: ISO_MIS_GPIO_bit21,<I/O>
#define RTD1295_BGA_PIN_T6_UP							(1&0x01)// 0xB8060228[19]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_T6_PD							(0&0x01)// 0xB8060228[18]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_T6_DS							(0&0x01)// 0xB8060228[17]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_T6_SR							(0&0x01)// 0xB8060228[16]: Slew rate 0:fast 1:slow


// PAD_NAME: ST_GPIO28 157
#define RTD1295_BGA_PIN_P4								(0xF&0xF)//0xB8060224[31:28];
																							//E: st_dbg_bit13,<I/O>
																							//F: ISO_MIS_GPIO_bit28,<I/O>
																							//def: ISO_MIS_GPIO_bit28,<I/O>
#define RTD1295_BGA_PIN_P4_UP							(1&0x01)// 0xB8060224[27]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_P4_PD							(0&0x01)// 0xB8060224[26]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_P4_DS							(0&0x01)// 0xB8060224[25]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_P4_SR							(0&0x01)// 0xB8060224[24]: Slew rate 0:fast 1:slow


// PAD_NAME: ST_GPIO23 158
#define RTD1295_BGA_PIN_V5								(0x9&0xF)//0xB8060224[7:4];
																							//3: DEMOD_I2C_DBG_SDA,<I/O>
																							//5: I2C0_SDA_SRC0,<I/O>
																							//6: HSYNC_DIG,<I>
																							//8: uart1_txdo,<O>
																							//9: uart0_txdo,<O>
																							//A: SPDIF_OUT,<O>
																							//F: ISO_MIS_GPIO_bit23,<I/O>
																							//def: ISO_MIS_GPIO_bit23,<I/O>
#define RTD1295_BGA_PIN_V5_UP							(1&0x01)// 0xB8060224[3]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_V5_PD							(0&0x01)// 0xB8060224[2]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_V5_DS							(0&0x01)// 0xB8060224[1]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_V5_SR							(0&0x01)// 0xB8060224[0]: Slew rate 0:fast 1:slow


// PAD_NAME: VSDA 159
#define RTD1295_BGA_PIN_U4								(0x8&0xF)//0xB8060200[7:4];
																							//4: VDDC_SDA,<I/O>
																							//5: I2C0_SDA_SRC1,<I/O>
																							//7: ISO_DDC_SDA_src0,<I/O>
																							//8: uart1_txdo,<O>
																							//9: uart0_txdo,<O>
																							//F: ISO_MIS_GPIO_bit25,<I/O>
																							//def: ISO_MIS_GPIO_bit25,<I/O>
#define RTD1295_BGA_PIN_U4_UP							(1&0x01)// 0xB8060200[3]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_U4_PD							(0&0x01)// 0xB8060200[2]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_U4_DS							(0&0x01)// 0xB8060200[1]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_U4_SR							(0&0x01)// 0xB8060200[0]: Slew rate 0:fast 1:slow


// PAD_NAME: ST_GPIO30 160
#define RTD1295_BGA_PIN_H5								(0x4&0xF)//0xB8060200[23:20];
																							//4: HDDC0_SDA,<I/O>
																							//5: I2C0_SDA_SRC2,<I/O>
																							//7: ISO_DDC_SDA_src1,<I/O>
																							//F: ISO_MIS_GPIO_bit30,<I/O>
																							//def: ISO_MIS_GPIO_bit30,<I/O>
#define RTD1295_BGA_PIN_H5_UP							(1&0x01)// 0xB8060200[19]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_H5_PD							(0&0x01)// 0xB8060200[18]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_H5_DS							(0&0x01)// 0xB8060200[17]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_H5_SR							(0&0x01)// 0xB8060200[16]: Slew rate 0:fast 1:slow


// PAD_NAME: ST_GPIO27 161
#define RTD1295_BGA_PIN_L4								(0xF&0xF)//0xB8060224[23:20];
																							//E: st_dbg_bit12,<I/O>
																							//F: ISO_MIS_GPIO_bit27,<I/O>
																							//def: ISO_MIS_GPIO_bit27,<I/O>
#define RTD1295_BGA_PIN_L4_UP							(1&0x01)// 0xB8060224[19]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_L4_PD							(0&0x01)// 0xB8060224[18]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_L4_DS							(0&0x01)// 0xB8060224[17]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_L4_SR							(0&0x01)// 0xB8060224[16]: Slew rate 0:fast 1:slow


// PAD_NAME: ST_GPIO32 162
#define RTD1295_BGA_PIN_L5								(0x4&0xF)//0xB8060204[7:4];
																							//4: HDDC1_SDA,<I/O>
																							//7: ISO_DDC_SDA_src2,<I/O>
																							//E: st_dbg_bit15,<I/O>
																							//F: ISO_MIS_GPIO_bit32,<I/O>
																							//def: ISO_MIS_GPIO_bit32,<I/O>
#define RTD1295_BGA_PIN_L5_UP							(1&0x01)// 0xB8060204[3]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_L5_PD							(0&0x01)// 0xB8060204[2]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_L5_DS							(0&0x01)// 0xB8060204[1]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_L5_SR							(0&0x01)// 0xB8060204[0]: Slew rate 0:fast 1:slow


// PAD_NAME: ST_GPIO29 163
#define RTD1295_BGA_PIN_H6								(0x4&0xF)//0xB8060200[31:28];
																							//4: HDDC0_SCL,<I>
																							//5: I2C0_SCL_SRC2,<I/O>
																							//7: ISO_DDC_SCL_src1,<I>
																							//F: ISO_MIS_GPIO_bit29,<I/O>
																							//def: ISO_MIS_GPIO_bit29,<I/O>
#define RTD1295_BGA_PIN_H6_UP							(1&0x01)// 0xB8060200[27]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_H6_PD							(0&0x01)// 0xB8060200[26]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_H6_DS							(0&0x01)// 0xB8060200[25]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_H6_SR							(0&0x01)// 0xB8060200[24]: Slew rate 0:fast 1:slow


// PAD_NAME: ST_GPIO34 164
#define RTD1295_BGA_PIN_P5								(0x4&0xF)//0xB8060204[23:20];
																							//4: HDDC2_SDA,<I/O>
																							//5: I2C0_SDA_SRC3,<I/O>
																							//7: ISO_DDC_SDA_src3,<I/O>
																							//F: ISO_MIS_GPIO_bit34,<I/O>
																							//def: ISO_MIS_GPIO_bit34,<I/O>
#define RTD1295_BGA_PIN_P5_UP							(1&0x01)// 0xB8060204[19]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_P5_PD							(0&0x01)// 0xB8060204[18]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_P5_DS							(0&0x01)// 0xB8060204[17]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_P5_SR							(0&0x01)// 0xB8060204[16]: Slew rate 0:fast 1:slow


// PAD_NAME: ST_GPIO31 165
#define RTD1295_BGA_PIN_L6								(0x4&0xF)//0xB8060204[15:12];
																							//4: HDDC1_SCL,<I>
																							//7: ISO_DDC_SCL_src2,<I>
																							//E: st_dbg_bit14,<I/O>
																							//F: ISO_MIS_GPIO_bit31,<I/O>
																							//def: ISO_MIS_GPIO_bit31,<I/O>
#define RTD1295_BGA_PIN_L6_UP							(1&0x01)// 0xB8060204[11]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_L6_PD							(0&0x01)// 0xB8060204[10]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_L6_DS							(0&0x01)// 0xB8060204[9]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_L6_SR							(0&0x01)// 0xB8060204[8]: Slew rate 0:fast 1:slow


// PAD_NAME: ST_GPIO35 166
#define RTD1295_BGA_PIN_V6								(0xA&0xF)//0xB8060220[7:4];
																							//A: SPDIF_OUT,<O>
																							//D: iso_misc_pwm_0,<OD>
																							//F: ISO_MIS_GPIO_bit35,<I/O>
																							//def: ISO_MIS_GPIO_bit35,<I/O>
#define RTD1295_BGA_PIN_V6_UP							(1&0x01)// 0xB8060220[3]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_V6_PD							(0&0x01)// 0xB8060220[2]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_V6_DS							(0&0x01)// 0xB8060220[1]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_V6_SR							(0&0x01)// 0xB8060220[0]: Slew rate 0:fast 1:slow


// PAD_NAME: ST_GPIO33 167
#define RTD1295_BGA_PIN_P6								(0x4&0xF)//0xB8060204[31:28];
																							//4: HDDC2_SCL,<I>
																							//5: I2C0_SCL_SRC3,<I/O>
																							//7: ISO_DDC_SCL_src3,<I>
																							//F: ISO_MIS_GPIO_bit33,<I/O>
																							//def: ISO_MIS_GPIO_bit33,<I/O>
#define RTD1295_BGA_PIN_P6_UP							(1&0x01)// 0xB8060204[27]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_P6_PD							(0&0x01)// 0xB8060204[26]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_P6_DS							(0&0x01)// 0xB8060204[25]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_P6_SR							(0&0x01)// 0xB8060204[24]: Slew rate 0:fast 1:slow


// PAD_NAME: FSW0 168
#define RTD1295_BGA_PIN_Y5								(0xF&0xF)//0xB80008B4[31:28];
																							//3: ATV_VSYNC_OUT,<O>
																							//C: LSADC3,<AI>
																							//D: SCART_FSW_0,<AI>
																							//F: MIS_GPIO_bit136,<I/O>
																							//def: MIS_GPIO_bit136,<I/O>


// PAD_NAME: FSW1 169
#define RTD1295_BGA_PIN_Y6								(0xF&0xF)//0xB80008B4[27:24];
																							//3: ATV_VSYNC_OUT,<O>
																							//6: TP2_ERR,<I>,<HS>
																							//C: LSADC5,<AI>
																							//D: SCART_FSW_1,<AI>
																							//F: MIS_GPIO_bit137,<I/O>
																							//def: MIS_GPIO_bit137,<I/O>


// PAD_NAME: VIN11P 170
#define RTD1295_BGA_PIN_W6								(0xC&0xF)//0xB80008B0[19:16];
																							//C: VIN_11P,<AI>
																							//F: MIS_GPIO_bit135,<I/O>
																							//def: VIN_11P,<AI>
#define RTD1295_BGA_PIN_W6_UP							(1&0x01)// 0xB80008B0[15]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_W6_PD							(0&0x01)// 0xB80008B0[14]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_W6_DS							(0&0x01)// 0xB80008B0[13]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_W6_SR							(0&0x01)// 0xB80008B0[12]: Slew rate 0:fast 1:slow


// PAD_NAME: VIN14P 171
#define RTD1295_BGA_PIN_W4								(0xC&0xF)//0xB80008B0[23:20];
																							//C: VIN_14P,<AI>
																							//F: MIS_GPIO_bit134,<I/O>
																							//def: VIN_14P,<AI>
#define RTD1295_BGA_PIN_W4_UP							(1&0x01)// 0xB80008B0[19]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_W4_PD							(0&0x01)// 0xB80008B0[18]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_W4_DS							(0&0x01)// 0xB80008B0[17]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_W4_SR							(0&0x01)// 0xB80008B0[16]: Slew rate 0:fast 1:slow


// PAD_NAME: VIN13P 172
#define RTD1295_BGA_PIN_AC2								(0xC&0xF)//0xB80008B0[27:24];
																							//8: uart1_txdo,<O>
																							//C: VIN_13P,<AI>
																							//F: MIS_GPIO_bit133,<I/O>
																							//def: VIN_13P,<AI>
#define RTD1295_BGA_PIN_AC2_UP							(1&0x01)// 0xB80008B0[23]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AC2_PD							(0&0x01)// 0xB80008B0[22]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AC2_DS							(0&0x01)// 0xB80008B0[21]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AC2_SR							(0&0x01)// 0xB80008B0[20]: Slew rate 0:fast 1:slow


// PAD_NAME: VIN10P 173
#define RTD1295_BGA_PIN_AC3								(0xC&0xF)//0xB80008B0[31:28];
																							//8: uart1_rxdi_src6,<I>
																							//C: VIN_10P,<AI>
																							//F: MIS_GPIO_bit132,<I/O>
																							//def: VIN_10P,<AI>
#define RTD1295_BGA_PIN_AC3_UP							(1&0x01)// 0xB80008B0[27]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AC3_PD							(0&0x01)// 0xB80008B0[26]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AC3_DS							(0&0x01)// 0xB80008B0[25]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AC3_SR							(0&0x01)// 0xB80008B0[24]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO138 174
#define RTD1295_BGA_PIN_Y4								(0xA&0xF)//0xB8000868[15:12];
																							//3: ATV_VSYNC_OUT,<O>
																							//A: SPDIF_OUT,<O>
																							//B: SPDIF_IN_src0,<I>
																							//F: MIS_GPIO_bit138,<I/O>
																							//def: MIS_GPIO_bit138,<I/O>
#define RTD1295_BGA_PIN_Y4_UP							(1&0x01)// 0xB8000868[11]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_Y4_PD							(0&0x01)// 0xB8000868[10]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_Y4_DS							(0&0x01)// 0xB8000868[9]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_Y4_SR							(0&0x01)// 0xB8000868[8]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO139 175
#define RTD1295_BGA_PIN_AA5								(0x6&0xF)//0xB8000868[7:4];
																							//3: ATV_VSYNC_OUT,<O>
																							//5: DMIC_clk,<O>
																							//6: TP2_VAL,<I>,<HS>
																							//A: SPDIF_OUT,<O>
																							//B: SPDIF_IN_src1,<I>
																							//F: MIS_GPIO_bit139,<I/O>
																							//def: MIS_GPIO_bit139,<I/O>
#define RTD1295_BGA_PIN_AA5_UP							(1&0x01)// 0xB8000868[3]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AA5_PD							(0&0x01)// 0xB8000868[2]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AA5_DS							(0&0x01)// 0xB8000868[1]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AA5_SR							(0&0x01)// 0xB8000868[0]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO140 176
#define RTD1295_BGA_PIN_AA6								(0x6&0xF)//0xB800086C[31:28];
																							//3: ATV_VSYNC_OUT,<O>
																							//5: DMIC_clk,<O>
																							//6: CLK_TP2_en,<I>,<HS>
																							//F: MIS_GPIO_bit140,<I/O>
																							//def: MIS_GPIO_bit140,<I/O>
#define RTD1295_BGA_PIN_AA6_UP							(1&0x01)// 0xB800086C[27]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AA6_PD							(0&0x01)// 0xB800086C[26]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AA6_DS							(0&0x01)// 0xB800086C[25]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AA6_SR							(0&0x01)// 0xB800086C[24]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO141 177
#define RTD1295_BGA_PIN_AB5								(0x6&0xF)//0xB800086C[23:20];
																							//3: ATV_VSYNC_OUT,<O>
																							//5: DMIC_Data_SRC0,<I>
																							//6: TP2_SYNC,<I>,<HS>
																							//F: MIS_GPIO_bit141,<I/O>
																							//def: MIS_GPIO_bit141,<I/O>
#define RTD1295_BGA_PIN_AB5_UP							(1&0x01)// 0xB800086C[19]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AB5_PD							(0&0x01)// 0xB800086C[18]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AB5_DS							(0&0x01)// 0xB800086C[17]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AB5_SR							(0&0x01)// 0xB800086C[16]: Slew rate 0:fast 1:slow


// PAD_NAME: GPIO142 178
#define RTD1295_BGA_PIN_AB6								(0x6&0xF)//0xB800086C[15:12];
																							//3: ATV_VSYNC_OUT,<O>
																							//5: DMIC_Data_SRC1,<I>
																							//6: TP2_Data_bit0,<I>,<HS>
																							//F: MIS_GPIO_bit142,<I/O>
																							//def: MIS_GPIO_bit142,<I/O>
#define RTD1295_BGA_PIN_AB6_UP							(1&0x01)// 0xB800086C[11]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AB6_PD							(0&0x01)// 0xB800086C[10]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AB6_DS							(0&0x01)// 0xB800086C[9]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AB6_SR							(0&0x01)// 0xB800086C[8]: Slew rate 0:fast 1:slow


// PAD_NAME: RFAGC 179
#define RTD1295_BGA_PIN_AB4								(0x6&0xF)//0xB800086C[7:4];
																							//3: DEMOD_AGC_RF,<OD>
																							//4: ATV_IF_AGC,<OD>
																							//6: ATV_RF_AGC,<OD>
																							//F: MIS_GPIO_bit143,<I/O>
																							//def: MIS_GPIO_bit143,<I/O>
#define RTD1295_BGA_PIN_AB4_UP							(1&0x01)// 0xB800086C[3]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AB4_PD							(0&0x01)// 0xB800086C[2]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AB4_DS							(0&0x01)// 0xB800086C[1]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AB4_SR							(0&0x01)// 0xB800086C[0]: Slew rate 0:fast 1:slow


// PAD_NAME: IFAGC 180
#define RTD1295_BGA_PIN_AC4								(0x6&0xF)//0xB8000870[31:28];
																							//3: DEMOD_AGC_IF,<OD>
																							//4: ATV_RF_AGC,<OD>
																							//6: ATV_IF_AGC,<OD>
																							//F: MIS_GPIO_bit144,<I/O>
																							//def: MIS_GPIO_bit144,<I/O>
#define RTD1295_BGA_PIN_AC4_UP							(1&0x01)// 0xB8000870[27]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AC4_PD							(0&0x01)// 0xB8000870[26]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AC4_DS							(0&0x01)// 0xB8000870[25]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AC4_SR							(0&0x01)// 0xB8000870[24]: Slew rate 0:fast 1:slow


// PAD_NAME: I2C_SCL 181
#define RTD1295_BGA_PIN_AF1								(0x5&0xF)//0xB8000870[23:20];
																							//3: DEMOD_I2C_SCL_RELAY,<OD>
																							//5: I2C1_SCL_SRC2,<I/O>
																							//F: MIS_GPIO_bit145,<I/O>
																							//def: MIS_GPIO_bit145,<I/O>
#define RTD1295_BGA_PIN_AF1_UP							(1&0x01)// 0xB8000870[19]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AF1_PD							(0&0x01)// 0xB8000870[18]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AF1_DS							(0&0x01)// 0xB8000870[17]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AF1_SR							(0&0x01)// 0xB8000870[16]: Slew rate 0:fast 1:slow


// PAD_NAME: I2C_SDA 182
#define RTD1295_BGA_PIN_AF2								(0x5&0xF)//0xB8000870[15:12];
																							//3: DEMOD_I2C_SDA_RELAY,<I/O>
																							//5: I2C1_SDA_SRC2,<I/O>
																							//F: MIS_GPIO_bit146,<I/O>
																							//def: MIS_GPIO_bit146,<I/O>
#define RTD1295_BGA_PIN_AF2_UP							(1&0x01)// 0xB8000870[11]: Pull Up 0:disable 1:enable
#define RTD1295_BGA_PIN_AF2_PD							(0&0x01)// 0xB8000870[10]: Pull Down 0:disable 1:enable
#define RTD1295_BGA_PIN_AF2_DS							(0&0x01)// 0xB8000870[9]: Driving Strength 0:4mA 1:8mA
#define RTD1295_BGA_PIN_AF2_SR							(0&0x01)// 0xB8000870[8]: Slew rate 0:fast 1:slow


#define PIN_BL_ON_OFF 			RTD1295_BGA_PIN_R6_ISO_GPO_6(1, 1)
#define PIN_BL_ADJ				RTD1295_BGA_PIN_R5_ISO_PWM_1(1, 200, 255, 255)
#define PIN_LVDS_ON_OFF			RTD1295_BGA_PIN_N5_ISO_GPO_4(0, 1)


#define PIN_KEYPAD_MENU			RTD1295_BGA_PIN_E2_LSADC_CURRENT_0(80, 10)
#define PIN_KEYPAD_SOURCE		RTD1295_BGA_PIN_E2_LSADC_CURRENT_0(60, 10)
#define PIN_KEYPAD_LEFT			RTD1295_BGA_PIN_E2_LSADC_CURRENT_0(19, 10)
#define PIN_KEYPAD_RIGHT		RTD1295_BGA_PIN_E2_LSADC_CURRENT_0(40, 10)
#define PIN_KEYPAD_PWR			RTD1295_BGA_PIN_E3_LSADC_CURRENT_1(40, 10)
#define PIN_KEYPAD_UP			RTD1295_BGA_PIN_E3_LSADC_CURRENT_1(80, 10)
#define PIN_KEYPAD_DOWN			RTD1295_BGA_PIN_E3_LSADC_CURRENT_1(59, 10)

// HDMI 1 reletive board information
#define PIN_HDMI1_HOTPLUG		RTD1295_BGA_PIN_H4_ISO_GPO_26(0, 0)
#define HDMI1_DDC				PCB_DDC_0
#define HDMI1_PHY_PORT			HDMI_PHY_PORT0
#define HDMI1_EDID_TYPE  		HDMI_EDID_ONCHIP
#define HDMI1_HPD_TYPE			HDMI_HPD_ONCHIP
#define HDMI1_MUX_PORT			HDMI_MUX_PORT_NOTUSED
#define HDMI1_MUX_IC			HDMI_MUX_NOUSED

// HDMI 2 reletive board information
#define PIN_HDMI2_HOTPLUG		RTD1295_BGA_PIN_L4_ISO_GPO_27(0, 0)
#define HDMI2_DDC				PCB_DDC_1
#define HDMI2_PHY_PORT			HDMI_PHY_PORT1
#define HDMI2_EDID_TYPE  		HDMI_EDID_ONCHIP
#define HDMI2_HPD_TYPE			HDMI_HPD_ONCHIP
#define HDMI2_MUX_PORT			HDMI_MUX_PORT_NOTUSED
#define HDMI2_MUX_IC			HDMI_MUX_NOUSED

// HDMI 3 reletive board information
#define PIN_HDMI3_HOTPLUG		(0)
#define HDMI3_DDC				PCB_DDC_2
#define HDMI3_PHY_PORT			HDMI_PHY_PORT2
#define HDMI3_EDID_TYPE  		HDMI_EDID_ONCHIP
#define HDMI3_HPD_TYPE			HDMI_HPD_ONCHIP
#define HDMI3_MUX_PORT			HDMI_MUX_PORT_NOTUSED
#define HDMI3_MUX_IC			HDMI_MUX_NOUSED

#define PIN_HDMI_MHL_SELECT               RTD1295_BGA_PIN_K6_ISO_GPO_2(0, 0)
#define PIN_HDMI_CABLE_DETECT      	  RTD1295_BGA_PIN_F2_ISO_GPI_16(0)
#define PIN_MHL_CABLE_DETECT      	  RTD1295_BGA_PIN_G3_ISO_GPI_20(0)

// VGA DDC
#define VGA_DDC					PCB_DDC_3

// Tuner I2C
#define TUNER_I2C				PCB_I2C_1

#define I2C_PORT_0                      PCB_HW_I2C(PCB_I2C_PHY_0, PCB_I2C_SUB_SRC_ANY)

#define I2C_PORT_1                      PCB_HW_I2C(PCB_I2C_PHY_1, PCB_I2C_SUB_SRC_ANY)

#define I2C_PORT_2                      PCB_HW_I2C(PCB_I2C_PHY_2, PCB_I2C_SUB_SRC_ANY)

//I2C Port 3:GPIO I2C, SDA=GPIO 169, SCL=GPIO 168 for amp
#define PIN_I2C3_SDA                   RTD1295_BGA_PIN_A5_GPO_127(0,0)
#define PIN_I2C3_SCL                   RTD1295_BGA_PIN_D7_GPO_124(0,0)//RTD1295_BGA_PIN_Y5_GPO_136(0,0)
#define I2C_PORT_3                      PCB_GPIO_I2C(PIN_I2C3_SDA, PIN_I2C3_SCL)

//I2C Port 4:GPIO I2C, SDA=GPIO 14, SCL=GPIO 13 for eeprom
#define PIN_I2C4_SDA                  RTD1295_BGA_PIN_AH12_GPO_14(0, 0)
#define PIN_I2C4_SCL                   RTD1295_BGA_PIN_AG11_GPO_13(0, 0)
#define I2C_PORT_4                      PCB_GPIO_I2C(PIN_I2C4_SDA, PIN_I2C4_SCL)

// Tuner 33V for specific Tuner
//#define TUN33V_PWM


// AMP
#define AMP_DEVICE_ADDR				0x1a 	//0x34 //Tas5711L_ADDR
//#define AMP_DEVICE_ADDR				0x1b 	//0x36 //Tas5707L_ADDR
#define PIN_AMP_MUTE					RTD1295_BGA_PIN_A7_GPO_121(0,0)
#define AMP_I2C							PCB_I2C_3
	//CLK   0x1800_0870[31:28],   5: 0xb800_08C0[23:20] = 0x8 / 0xb806_02A0[5:4] = 0x3
	//DATA 0x1800_0870[23:20],   5: 0xb800_08C0[23:20] = 0x8 / 0xb806_02A0[5:4] = 0x3

// EEP
//#define EEP_DEVICE_ADDR				(0XA0 >> 1)
//#define EEP_WP
//#define EEP_I2C							PCB_I2C_1
	//the same with AMP for test use




// MISC
#define MISC_2D_3D_SELECT				RTD1295_BGA_PIN_Y6_GPO_137(1, 1)
//#define FLASH_WP
//#define MISC_951_RST
#define POWER_EN					RTD1295_BGA_PIN_N6_ISO_GPO_12(1, 1)
#define PIN_PCMCIA_EN					RTD1295_BGA_PIN_AJ12_GPO_15(0,1)
// USB hub Reset ?
//#define HUB_RET

// USB3.0 Power Switch Control ?
//#define USB_PWR_CTL

// USB3.0 Power Flag ?
//#define USB_PWR_FLAG

// USB Hub Power Flag
//#define USB3_PWR_FLAG					RTD2974_LFBGA_PIN_AA21_GPO_47(1, 1)
//#define USB2_PWR_FLAG					RTD2974_LFBGA_PIN_L1_GPO_114(1, 1)
//#define USB1_PWR_FLAG					RTD2974_LFBGA_PIN_K3_GPO_115(1, 1)

//#define ANDROID_USB_PORT				0x312d322e32202020	//must 8-byte,   USB PORT 1-2.2 for E83
#define ANDROID_USB_PORT				0x312d312020202020	//must 8-byte,   USB PORT 1-1 for E650S, RTK_DEMO

// for Customer to load AV_PATH
#define AV1_VPATH   VIDEO_INPUT12
#define AV1_VGND	VIDEO_GNDA0

//Millet3
#define MILLET3_DEVICE_ADDR			0x70
#define MILLET3_I2C						PCB_I2C_3

//////////////////////////////////////////////////////////////////////////////
//
// 	Enumerate all PCB staff below !!!
//
//////////////////////////////////////////////////////////////////////////////
PCB_ENUM_START()
PCB_ENUM(PIN_BL_ON_OFF)
PCB_ENUM(PIN_BL_ADJ)
PCB_ENUM(PIN_LVDS_ON_OFF)
PCB_ENUM(PIN_KEYPAD_MENU)
PCB_ENUM(PIN_KEYPAD_SOURCE)
PCB_ENUM(PIN_KEYPAD_LEFT)
PCB_ENUM(PIN_KEYPAD_RIGHT)
PCB_ENUM(PIN_KEYPAD_PWR)
PCB_ENUM(PIN_KEYPAD_UP)
PCB_ENUM(PIN_KEYPAD_DOWN)
PCB_ENUM(PIN_HDMI1_HOTPLUG)
PCB_ENUM(HDMI1_DDC)
PCB_ENUM(HDMI1_PHY_PORT)
PCB_ENUM(HDMI1_EDID_TYPE)
PCB_ENUM(HDMI1_HPD_TYPE)
PCB_ENUM(HDMI1_MUX_PORT)
PCB_ENUM(HDMI1_MUX_IC)
PCB_ENUM(PIN_HDMI2_HOTPLUG)
PCB_ENUM(HDMI2_DDC)
PCB_ENUM(HDMI2_PHY_PORT)
PCB_ENUM(HDMI2_EDID_TYPE)
PCB_ENUM(HDMI2_HPD_TYPE)
PCB_ENUM(HDMI2_MUX_PORT)
PCB_ENUM(HDMI2_MUX_IC)
PCB_ENUM(PIN_HDMI3_HOTPLUG)
PCB_ENUM(HDMI3_DDC)
PCB_ENUM(HDMI3_PHY_PORT)
PCB_ENUM(HDMI3_EDID_TYPE)
PCB_ENUM(HDMI3_HPD_TYPE)
PCB_ENUM(HDMI3_MUX_PORT)
PCB_ENUM(HDMI3_MUX_IC)
PCB_ENUM(PIN_HDMI_MHL_SELECT)
PCB_ENUM(PIN_HDMI_CABLE_DETECT)
PCB_ENUM(PIN_MHL_CABLE_DETECT)
PCB_ENUM(VGA_DDC)
PCB_ENUM(TUNER_I2C)

PCB_ENUM(AV1_VPATH)
PCB_ENUM(AV1_VGND)
//PCB_ENUM(TUN33V_PWM)
PCB_ENUM(AMP_DEVICE_ADDR)
PCB_ENUM(PIN_AMP_MUTE)
PCB_ENUM(AMP_I2C)
//PCB_ENUM(EEP_DEVICE_ADDR)
//PCB_ENUM(EEP_WP)
//PCB_ENUM(EEP_I2C)
//PCB_ENUM(MISC_2D_3D_SELECT)
//PCB_ENUM(FLASH_WP)
//PCB_ENUM(MISC_951_RST)
PCB_ENUM(POWER_EN)
PCB_ENUM(PIN_PCMCIA_EN)
//PCB_ENUM(HUB_RET)
//PCB_ENUM(USB_PWR_CTL)
//PCB_ENUM(USB_PWR_FLAG)
//PCB_ENUM(USB1_PWR_FLAG)
//PCB_ENUM(USB2_PWR_FLAG)
//PCB_ENUM(USB3_PWR_FLAG)
PCB_ENUM(I2C_PORT_0)
PCB_ENUM(I2C_PORT_1)
PCB_ENUM(I2C_PORT_2)
PCB_ENUM(I2C_PORT_3)
PCB_ENUM(I2C_PORT_4)
PCB_ENUM(MILLET3_DEVICE_ADDR)
PCB_ENUM(MILLET3_I2C)
PCB_ENUM_END()

