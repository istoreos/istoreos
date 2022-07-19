#ifndef DRIVERS_MMC_RTK_SDMMC_H_
#define DRIVERS_MMC_RTK_SDMMC_H_

struct rtk_sdmmc_host {
	struct mmc_cmd *cmd;
	struct mmc_data *data;
    struct mmc_host *mmc;
    u32 sdmmc_base;
    u32 crt_base;
    u32 sysbrdg;
    u32 emmc_base;
    u8 cmd_opcode;
};

struct sdmmc_cmd_pkt {
    struct mmc_host *mmc; /* MMC structure */
    struct rtk_sdmmc_host *rtk_host;
    struct mmc_cmd *cmd;
    struct mmc_data *data;
    u32 dma_buffer;
    u16 byte_count;
    u16 block_count;

    u32 flags;
    s8 rsp_para1;
    s8 rsp_para2;
    s8 rsp_para3;
    u8 rsp_len;
    u32 timeout;
};

enum sdmmc_clock_speed {
    SDMMC_CLOCK_200KHZ = 0,
    SDMMC_CLOCK_400KHZ = 1,
    SDMMC_CLOCK_6200KHZ = 2,
    SDMMC_CLOCK_20000KHZ = 3,
    SDMMC_CLOCK_25000KHZ = 4,
    SDMMC_CLOCK_50000KHZ = 5,
    SDMMC_CLOCK_208000KHZ = 6,
    SDMMC_CLOCK_100000KHZ = 7,
};

#define mmc_resp_type(cmd)	((cmd)->flags & (MMC_RSP_PRESENT|MMC_RSP_136|MMC_RSP_CRC|MMC_RSP_BUSY|MMC_RSP_OPCODE))

//MMC ios caps
#define MMC_IOS_LDO		0x1
#define MMC_IOS_CLK		0x2
#define MMC_IOS_BUSWIDTH	0x4
#define MMC_IOS_INIT_DIV	0x10
#define MMC_IOS_NONE_DIV	0x20
#define MMC_IOS_GET_PAD_DRV 	0x40
#define MMC_IOS_SET_PAD_DRV 	0x80
#define MMC_IOS_RESTORE_PAD_DRV	0x100

//#define MMC_IOS_GET_PAD_DRV     0x1
//#define MMC_IOS_SET_PAD_DRV     0x2
//#define MMC_IOS_RESTORE_PAD_DRV 0x4

#define MASK_RESP_TYPE                (0x03)
#define RESP_TYPE_NON                 (0x00)
#define RESP_TYPE_6B                  (0x01)
#define RESP_TYPE_17B                 (0x02)

/* MMC configure2, for SD_CONFIGURE2, response type */
#define SD_R0                      (RESP_TYPE_NON | CRC7_CHK_DIS)
#define SD_R1                      RESP_TYPE_6B
#define SD_R1b                     RESP_TYPE_6B
#define SD_R2                      RESP_TYPE_17B
#define SD_R3                      (RESP_TYPE_6B | CRC7_CHK_DIS)
#define SD_R4                      RESP_TYPE_6B
#define SD_R5                      RESP_TYPE_6B
#define SD_R6                      RESP_TYPE_6B
#define SD_R7                      RESP_TYPE_6B
#define SD_R_NO                    0xFF

#define MMC_CMD_MASK	(3 << 5)		/* non-SPI command type */
#define MMC_CMD_AC	(0 << 5)
#define MMC_CMD_ADTC	(1 << 5)
#define MMC_CMD_BC	(2 << 5)
#define MMC_CMD_BCR	(3 << 5)

// Card Reader Register Sets
#define BYTE_CNT                      0x0200

#define SDMMC_SYNC                    (0x0020)

#define CR_SOFT_RESET2                (0x0004)
#define CR_PLL_SD1                    (0x01E0)
#define CR_PLL_SD2                    (0x01E4)
#define CR_PLL_SD3                    (0x01E8)
#define CR_PLL_SD4                    (0x01EC)
#define CR_PFUNC_CR                   (0x0380)

#define SDIO_NORML_INT_STA            (0x0030)
#define EMMC_DMA_CTL3                 (0x000C)

#define CR_SD_SRAM_CTL                (0x0000)
#define CR_SD_DMA_CTL1                (0x0004)
#define CR_SD_DMA_CTL2                (0x0008)
#define CR_SD_DMA_CTL3                (0x000C)
#define CR_SD_ISR                     (0x0024)
#define CR_SD_ISREN                   (0x0028)
#define CR_SD_PAD_CTL                 (0x0074)
#define CR_SD_CKGEN_CTL               (0x0078)
#define CR_SD_INT_EN                  (0x0120)

#define CR_CARD_STOP                  (0x0103)
#define CR_CARD_OE                    (0x0104)
#define CARD_SELECT                   (0x010E)
#define CARD_EXIST                    (0x011F)
#define CARD_INT_PEND                 (0x0121)
#define CARD_CLOCK_EN_CTL             (0x0129)
#define CARD_SD_CLK_PAD_DRIVE         (0x0130)
#define CARD_SD_CMD_PAD_DRIVE         (0x0131)
#define CARD_SD_DAT_PAD_DRIVE         (0x0132)
#define SD_CONFIGURE1                 (0x0180)
#define SD_CONFIGURE2                 (0x0181)
#define SD_CONFIGURE3                 (0x0182)
#define SD_CONFIGURE4                 (0x019F)
#define SD_STATUS1                    (0x0183)
#define SD_STATUS2                    (0x0184)
#define SD_BUS_STATUS                 (0x0185)
#define SD_CMD_MODE                   (0x0186)
#define SD_SAMPLE_POINT_CTL           (0x0187)
#define SD_PUSH_POINT_CTL             (0x0188)
#define SD_CMD0                       (0x0189)
#define SD_CMD1                       (0x018A)
#define SD_CMD2                       (0x018B)
#define SD_CMD3                       (0x018C)
#define SD_CMD4                       (0x018D)
#define SD_CMD5                       (0x018E)
#define SD_BYTE_CNT_L                 (0x018F)
#define SD_BYTE_CNT_H                 (0x0190)
#define SD_BLOCK_CNT_L                (0x0191)
#define SD_BLOCK_CNT_H                (0x0192)
#define SD_TRANSFER                   (0x0193)
#define SD_DDR_DETECT_START           (0x0194)
#define SD_CMD_STATE                  (0x0195)
#define SD_DATA_STATE                 (0x0196)
#define SD_BUS_TA_STATE               (0x0197)
#define SD_STOP_SDCLK_CFG             (0x0198)
#define SD_AUTO_RST_FIFO              (0x0199)
#define SD_DAT_PAD                    (0x019A)
#define SD_DUMMY_4                    (0x019B)
#define SD_DUMMY_5                    (0x019C)
#define SD_DUTY_CTL                   (0x019D)
#define SD_SEQ_RW_CTL                 (0x019E)
#define SD_ADDR_L                     (0x01A0)
#define SD_ADDR_H                     (0x01A1)
#define SD_START_ADDR0                (0x01A2)
#define SD_START_ADDR1                (0x01A3)
#define SD_START_ADDR2                (0x01A4)
#define SD_START_ADDR3                (0x01A5)
#define SD_RSP_MASK1                  (0x01A6)
#define SD_RSP_MASK2                  (0x01A7)
#define SD_RSP_MASK3                  (0x01A8)
#define SD_RSP_MASK4                  (0x01A9)
#define SD_RSP_DATA1                  (0x01AA)
#define SD_RSP_DATA2                  (0x01AB)
#define SD_RSP_DATA3                  (0x01AC)
#define SD_RSP_DATA4                  (0x01AD)
#define SD_WRITE_DELAY                (0x01AE)
#define SD_READ_DELAY                 (0x01AF)

#define CR_CARD_RESP6_0               (SD_CMD)
#define CR_CARD_RESP6_1               (SD_CMD)
#define CR_CARD_RESP6_2               (SD_CMD)
#define CR_CARD_RESP6_3               (SD_CMD)
#define CR_CARD_RESP6_4               (SD_CMD)
#define CR_CARD_RESP6_5               (SD_CMD)

#define RESP_LEN64                    (0x01)
#define RESP_LEN17                    (0x02)
#define DMA_XFER                      (0x01)
#define DDR_WR                        (0x01 << 1)
#define RSP17_SEL                     (0x01 << 4)
#define RSP64_SEL                     (0x01 << 5)

#define SD_WRITE_PROTECT              (0x01 << 5)
#define SD_EXISTENCE                  (0x01 << 2)

/* SD_CONFIGURE1 */
#define SDCLK_DIV                     (0x01 << 7)
#define SDCLK_NO_DIV                  (0x00)
#define SDCLK_DIV_128                 (0x00)
#define SDCLK_DIV_256                 (0x01 << 6)
#define NO_RST_RDWR_FIFO              (0x00)
#define RST_RDWR_FIFO                 (0x01 << 4)

#define MASK_CLOCK_DIV                (0x03 << 6)
#define CLOCK_DIV_NON                 (0x02)
#define CLOCK_DIV_256                 (0x01 << 6)
#define CLOCK_DIV_128                 (0x00)

#define SPEED_HIGH                    (0x01 << 4)
#define SPEED_NORM                    (0x00)
#define DELAY_PHA_MASK                (0x03 << 2)
#define DELAY_PHA_NORM                (0x01 << 3)
#define DELAY_PHA_HIGH                (0x01 << 2)
#define SD30_ASYNC_FIFO_RST           (0x01 << 4)
#define ACCESS_MODE_SD20              (0x00)
#define ACCESS_MODE_DDR               (0x01)
#define ACCESS_MODE_SD30              (0x02)
#define MODE_SEL_MASK                 (0x03 << 2)
#define MODE_SEL_SD20                 (ACCESS_MODE_SD20 << 2)
#define MODE_SEL_DDR                  (ACCESS_MODE_DDR << 2)
#define MODE_SEL_SD30                 (ACCESS_MODE_SD30 << 2)

#define MASK_BUS_WIDTH                (0x03)
#define BUS_WIDTH_1                   (0x00)
#define BUS_WIDTH_4                   (0x01)
#define BUS_WIDTH_8                   (0x02)

/* CPU_ACC_CTL */
#define CPU_MODE_EN                   (0x01)
#define BUF_FULL                      (0x01 << 2)

/* SD_CONFIGURE2 */
#define CRC7_CAL_DIS                  (0x01 << 7)
#define CRC16_CAL_DIS                 (0x01 << 6)
#define WAIT_BUSY_EN                  (0x01 << 3)
#define CRC7_CHK_DIS                  (0x01 << 2)

#define MASK_RESP_TYPE                (0x03)
#define RESP_TYPE_NON                 (0x00)
#define RESP_TYPE_6B                  (0x01)
#define RESP_TYPE_17B                 (0x02)

/* SD_CONFIGURE3 */
#define DATA_TRANS_OVER_EN            (0x01 << 3)
#define RESP_CHK_EN                   (0x01 << 2)
#define ADDR_BYTE_MODE                (0x01 << 1)
#define SD_CMD_RSP_TO                 (0x01 << 0)

/* SD_TRANSFER */
#define START_EN                      (0x01 << 7)
#define END_STATE                     (0x01 << 6)
#define IDLE_STATE                    (0x01 << 5)
#define ERR_STATUS                    (0x01 << 4)

#define MASK_CMD_CODE                 (0x0F)
#define SD_NORMALWRITE                (0x00)
#define SD_AUTOWRITE3                 (0x01)
#define SD_AUTOWRITE4                 (0x02)
#define SD_AUTOREAD3                  (0x05)
#define SD_AUTOREAD4                  (0x06)
#define SD_SENDCMDGETRSP              (0x08)
#define SD_AUTOWRITE1                 (0x09)
#define SD_AUTOWRITE2                 (0x0A)
#define SD_NORMALREAD                 (0x0C)
#define SD_AUTOREAD1                  (0x0D)
#define SD_AUTOREAD2                  (0x0E)
#define SD_CMD_UNKNOW                 (0x0F)

/* SD_STATUS1 */
#define CRC7_STATUS                   (0x01 << 7)
#define CRC16_STATUS                  (0x01 << 6)
#define WRT_ERR_BIT                   (0x01 << 5)
#define CRC_TIMEOUT_ERR               (0x01 << 1)
#define PATTERN_CMP_ERR               (0x01 << 0)
#define WRITE_CRC_ERR_STAT(x)         ((x & (0x07 << 2)) >> 2)

/* SD_STATUS2 */
#define SD_CMD_RESP_INVALID           (0x01 << 1)
#define SD_CMD_RESP_TIMEOUT           (0x01)

/* SD_BUS_STATUS */
#define SD_CLK_TOG_EN                 (0x01 << 7)
#define SD_CLK_TOG_STOP               (0x01 << 6)
#define SD_DAT3_0_LEVEL               (0x0F << 1)
#define SD_CMD_LEVEL                  (0x01 << 0)

#define WRITE_DATA                    (0x01)
#define CLR_WRITE_DATA                (0x00)

/* CR_IP_CARD_INT_EN */

/* CR_SD_ISR */
#define ISRSTA_INT1                   (0x01 << 1) //card end
#define ISRSTA_INT2                   (0x01 << 2) //card error
#define ISRSTA_INT4                   (0x01 << 4) //DMA done

/* CR_SD_ISREN */
#define ISRSTA_INT1EN                 (0x01 << 1) //card end
#define ISRSTA_INT2EN                 (0x01 << 2) //card error
#define ISRSTA_INT4EN                 (0x01 << 4) //DMA done


//=========================JIM add =====================
static const unsigned char rtk_sdmmc_cmdcode[60][2] = {
    {SD_CMD_UNKNOW ,SD_R0 }, {SD_CMD_UNKNOW ,SD_R0 }, {SD_CMD_UNKNOW ,SD_R0 }, {SD_CMD_UNKNOW ,SD_R0 }, //0~3
    {SD_CMD_UNKNOW ,SD_R0 }, {SD_CMD_UNKNOW ,SD_R0 }, {SD_NORMALREAD ,SD_R1 }, {SD_CMD_UNKNOW ,SD_R0 }, //4~7
    {SD_CMD_UNKNOW ,SD_R1 }, {SD_CMD_UNKNOW ,SD_R0 }, {SD_CMD_UNKNOW ,SD_R0 }, {SD_CMD_UNKNOW ,SD_R1 }, //8~11
    {SD_CMD_UNKNOW ,SD_R0 }, {SD_NORMALREAD ,SD_R1 }, {SD_CMD_UNKNOW ,SD_R1 }, {SD_CMD_UNKNOW ,SD_R0 }, //12~15
    {SD_CMD_UNKNOW ,SD_R0 }, {SD_AUTOREAD2  ,SD_R1 }, {SD_AUTOREAD1  ,SD_R1 }, {SD_CMD_UNKNOW ,SD_R1 }, //16~19
    {SD_AUTOWRITE1 ,SD_R1 }, {SD_CMD_UNKNOW ,SD_R0 }, {SD_NORMALREAD ,SD_R1 }, {SD_CMD_UNKNOW ,SD_R0 }, //20~23
#ifndef CMD25_USE_SD_AUTOWRITE2
    {SD_AUTOWRITE2 ,SD_R1 }, {SD_AUTOWRITE1 ,SD_R1 }, {SD_NORMALWRITE,SD_R1 }, {SD_NORMALWRITE,SD_R1 }, //24~27
#else
    {SD_AUTOWRITE2 ,SD_R1 }, {SD_AUTOWRITE2 ,SD_R1 }, {SD_NORMALWRITE,SD_R1 }, {SD_NORMALWRITE,SD_R1 }, //24~27
#endif
    {SD_CMD_UNKNOW ,SD_R0 }, {SD_CMD_UNKNOW ,SD_R0 }, {SD_NORMALREAD ,SD_R1 }, {SD_NORMALREAD ,SD_R1 }, //28~31
    {SD_CMD_UNKNOW ,SD_R0 }, {SD_CMD_UNKNOW ,SD_R0 }, {SD_CMD_UNKNOW ,SD_R0 }, {SD_CMD_UNKNOW ,SD_R0 }, //32~35
    {SD_CMD_UNKNOW ,SD_R0 }, {SD_CMD_UNKNOW ,SD_R0 }, {SD_CMD_UNKNOW ,SD_R0 }, {SD_CMD_UNKNOW ,SD_R0 }, //36~39
    {SD_CMD_UNKNOW ,SD_R0 }, {SD_CMD_UNKNOW ,SD_R0 }, {SD_NORMALREAD ,SD_R1 }, {SD_CMD_UNKNOW ,SD_R0 }, //40~43
    {SD_CMD_UNKNOW ,SD_R0 }, {SD_CMD_UNKNOW ,SD_R0 }, {SD_CMD_UNKNOW ,SD_R0 }, {SD_CMD_UNKNOW ,SD_R0 }, //44~47
    {SD_AUTOREAD2 ,SD_R1 }, {SD_AUTOWRITE2 ,SD_R1 }, {SD_CMD_UNKNOW ,SD_R0 }, {SD_NORMALREAD ,SD_R1 }, //48~51
    {SD_CMD_UNKNOW ,SD_R0 }, {SD_CMD_UNKNOW ,SD_R0 }, {SD_CMD_UNKNOW ,SD_R0 }, {SD_CMD_UNKNOW ,SD_R0 }, //52~55
    {SD_AUTOREAD2 ,SD_R1 }, {SD_CMD_UNKNOW ,SD_R0 }, {SD_AUTOREAD2  ,SD_R1 }, {SD_AUTOWRITE2 ,SD_R1 }  //56~59
};
//===================================================================================================================
#endif /* DRIVERS_MMC_RTK_SDMMC_H_ */
