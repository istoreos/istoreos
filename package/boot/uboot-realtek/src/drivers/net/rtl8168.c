/*
 * rtl8168.c : U-Boot driver for Realtek Gigabit Ethernet controllers
 *             with PCI-Express interface
 *
 * Masami Komiya (mkomiya@sonare.it)
 *
 * Most part is taken from r8168.c of Linux kernel
 *
 */

/**************************************************************************
*    rtl8168.c: Etherboot device driver for Realtek Gigabit Ethernet
*    controllers with PCI-Express interface
*    Written 2013 by Realtek <nicfae@realtek.com>
*
*    This program is free software; you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation; either version 2 of the License, or
*    (at your option) any later version.
*
*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with this program; if not, write to the Free Software
*    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*
*    Portions of this code based on:
*    r8168.c: A Realtek Gigabit Ethernet controllers with PCI-Express
*    interface driver for Linux kernel 3.x.
*
***************************************************************************/
#include <common.h>
#include <malloc.h>
#include <net.h>
#include <netdev.h>
#include <asm/io.h>
#include <pci.h>
#include <errno.h>
#include <linux/mii.h>
#include <asm/arch/system.h>
#include <asm/arch/io.h>
#include <asm/arch/cpu.h>
#include <asm/arch/rbus/sb2_reg.h>

#define KYLIN_CHIP_ID   0x00006421
static inline u32 get_asic_chip_id(void) {
    u32 val = rtd_inl(CHIP_ID);
    return val;
}

#undef DBG_reg
//#undef DEBUG_RTL8168
//#undef DEBUG_RTL8168_TX
//#undef DEBUG_RTL8168_RX

//#define DEBUG_RTL8168
//#define DEBUG_RTL8168_TX
//#define DEBUG_RTL8168_RX

#define drv_version "v0.1"
#define drv_date "08-29-2013"

/* Condensed operations for readability. */
#define currticks() get_timer(0)

/* MAC address length*/
#define MAC_ADDR_LEN    6

/* max supported gigabit ethernet frame size -- must be at least (dev->mtu+14+4).*/
#define MAX_ETH_FRAME_SIZE  1536

#define TX_FIFO_THRESH 256  /* In bytes */

#define Reserved2_data  7
#define RX_DMA_BURST    7   /* Maximum PCI burst, '6' is 1024 */
#define RX_DMA_BURST_128 3
#define TX_DMA_BURST_unlimited  7
#define TX_DMA_BURST_1024   6
#define TX_DMA_BURST_512    5
#define TX_DMA_BURST_256    4
#define TX_DMA_BURST_128    3
#define TX_DMA_BURST_64     2
#define TX_DMA_BURST_32     1
#define TX_DMA_BURST_16     0
#define Reserved1_data  0x3F
#define RxPacketMaxSize 0x3FE8  /* 16K - 1 - ETH_HLEN - VLAN - CRC... */
#define Jumbo_Frame_2k  (2 * 1024)
#define Jumbo_Frame_3k  (3 * 1024)
#define Jumbo_Frame_4k  (4 * 1024)
#define Jumbo_Frame_5k  (5 * 1024)
#define Jumbo_Frame_6k  (6 * 1024)
#define Jumbo_Frame_7k  (7 * 1024)
#define Jumbo_Frame_8k  (8 * 1024)
#define Jumbo_Frame_9k  (9 * 1024)
#define InterFrameGap   0x03    /* 3 means InterFrameGap = the shortest one */
#define RxEarly_off_V1 (0x07 << 11)
#define RxEarly_off_V2 (1 << 11)

#define RX_BUF_SIZE 1536
#define R8168_TX_RING_BYTES (NUM_TX_DESC * sizeof(struct TxDesc))
#define R8168_RX_RING_BYTES (NUM_RX_DESC * sizeof(struct RxDesc))

#define NUM_TX_DESC 16  /* Number of Tx descriptor registers */
#define NUM_RX_DESC 16  /* Number of Rx descriptor registers */

#define TX_TIMEOUT  (6*HZ)

/* write/read MMIO register. Notice: {read,write}[wl] do the necessary swapping */
#define RTL_W8(reg, val8)   writeb ((val8), ioaddr + (reg))
#define RTL_W16(reg, val16) writew ((val16), ioaddr + (reg))
#define RTL_W32(reg, val32) writel ((val32), ioaddr + (reg))
#define RTL_R8(reg)         readb (ioaddr + (reg))
#define RTL_R16(reg)        readw (ioaddr + (reg))
#define RTL_R32(reg)        ((unsigned long) readl (ioaddr + (reg)))
#if defined(CONFIG_RTD1295)
#define EFUSE_OTP_REG       0x980171e0
#elif defined(CONFIG_RTD1395)
#define EFUSE_OTP_REG       0x980172c8
#define R_K_DEFAULT         0x8
#define IDAC_FINE_DEFAULT   0x33
#endif /* CONFIG_RTD1295 | CONFIG_RTD1395 */

#define ETH_FRAME_LEN   MAX_ETH_FRAME_SIZE
#define ETH_ALEN    MAC_ADDR_LEN
#define ETH_ZLEN    60

#define AUTONEG_ENABLE  0x01
#define DUPLEX_HALF     0x00
#define DUPLEX_FULL     0x01
#define SPEED_10        10
#define SPEED_100       100
#define SPEED_1000      1000

#define NIC_RAMCODE_VERSION 0x0001

//#define bus_to_phys(a)    pci_mem_to_phys((pci_dev_t)dev->priv, (pci_addr_t)a)
//#define phys_to_bus(a)    pci_phys_to_mem((pci_dev_t)dev->priv, (phys_addr_t)a)

#define bus_to_phys(a)  (a)

//#define pci_phys_to_mem(dev, addr)  (addr)
//#define pci_mem_to_phys(dev, addr)  (addr)
//#define pci_phys_to_io(dev, addr)   (addr)
//#define pci_io_to_phys(dev, addr)   (addr)

#define _RXDESC_PER_CACHELINE (ARCH_ALIGN/sizeof(struct RxDesc))
#define ARCH_ALIGN 64

#define ETN_GPHY_BYPASS     0x98007060
#define ETN_RESET_CTRL      0x98007088
#define ETN_CLK_CTRL        0x9800708c
#define ETN_DBUS_CLK        0x98007fc0
#define ISO_UMSK_ISR        0x98007004
#define ISO_POWERCUT_ETN    0x9800705c
#define SBX_ACP_MISC_CTRL   0x9801c814
#define CRT_SOFT_RESET1     0x98000000
#define CRT_SOFT_RESET2     0x98000004
#define CRT_CLOCK_ENABLE1   0x9800000c
#define CRT_SOFT_RESET4     0x98000050
#define ISO_GPIO_MUXPAD2    0x9804e008
#define ISO_GPIO_MUXPAD3    0x9804e00c
#define SDS_REG02           0x981c8008
#define SDS_REG28           0x981c8070
#define SDS_REG29           0x981c8074
#define SDS_MISC            0x981c9804
#define SDS_LINK            0x981c9810

enum phy_type_e {
    PHY_TYPE_FEPHY = 0,
    PHY_TYPE_SGMII = 1,
};

enum phy_addr_e {
    INT_PHY_ADDR = 1,   /* embedded FEPHY PHY ID */
    SERDES_DPHY_0 = 0,  /* embedded SerDes DPHY PHY ID 0, RL6481_T28_SGMII.doc ANA00~ANA0F */
    SERDES_DPHY_1 = 1,  /* embedded SerDes DPHY PHY ID 1, RL6481_T28_SGMII.doc ANA20~ANA2F */
    EXT_PHY_ADDR = 3,   /* external RTL8211FS SGMII PHY ID */
};

#define SGMII_SWING         (0X3 << 8)
#define TX_SWING_1040MV     (0X0 << 8)  /* DEFAULT */
#define TX_SWING_693MV      (0X1 << 8)
#define TX_SWING_474MV      (0X2 << 8)
#define TX_SWING_352MV      (0X3 << 8)
#define TX_SWING_312MV      (0X4 << 8)


enum RTL8168_registers {
    MAC0            = 0x00,     /* Ethernet hardware address. */
    MAC4            = 0x04,
    MAR0            = 0x08,     /* Multicast filter. */
    CounterAddrLow  = 0x10,
    CounterAddrHigh = 0x14,
    CustomLED       = 0x18,
    TxDescStartAddrLow      = 0x20,
    TxDescStartAddrHigh     = 0x24,
    TxHDescStartAddrLow     = 0x28,
    TxHDescStartAddrHigh    = 0x2c,
    FLASH           = 0x30,
    ERSR            = 0x36,
    ChipCmd         = 0x37,
    TxPoll          = 0x38,
    IntrMask        = 0x3C,
    IntrStatus      = 0x3E,
    TxConfig        = 0x40,
    RxConfig        = 0x44,
    TCTR            = 0x48,
    Cfg9346         = 0x50,
    Config0         = 0x51,
    Config1         = 0x52,
    Config2         = 0x53,
    Config3         = 0x54,
    Config4         = 0x55,
    Config5         = 0x56,
    TDFNR           = 0x57,
    TimeIntr        = 0x58,
    PHYAR           = 0x60,
    CSIDR           = 0x64,
    CSIAR           = 0x68,
    PHYstatus       = 0x6C,
    MACDBG          = 0x6D,
    GPIO            = 0x6E,
    PMCH            = 0x6F,
    ERIDR           = 0x70,
    ERIAR           = 0x74,
    EPHY_RXER_NUM   = 0x7C,
    EPHYAR          = 0x80,
    OCPDR           = 0xB0,
    MACOCP          = 0xB0,
    OCPAR           = 0xB4,
    PHYOCP          = 0xB8,
    DBG_reg         = 0xD1,
    MCUCmd_reg      = 0xD3,
    RxMaxSize       = 0xDA,
    EFUSEAR         = 0xDC,
    CPlusCmd        = 0xE0,
    IntrMitigate    = 0xE2,
    RxDescAddrLow   = 0xE4,
    RxDescAddrHigh  = 0xE8,
    MTPS            = 0xEC,
    FuncEvent       = 0xF0,
    FuncEventMask   = 0xF4,
    FuncPresetState = 0xF8,
    FuncForceEvent  = 0xFC,
};

enum RTL8168_register_content {
    /* InterruptStatusBits */
    SYSErr      = 0x8000,
    PCSTimeout  = 0x4000,
    SWInt       = 0x0100,
    TxDescUnavail   = 0x0080,
    RxFIFOOver  = 0x0040,
    LinkChg     = 0x0020,
    RxDescUnavail   = 0x0010,
    TxErr       = 0x0008,
    TxOK        = 0x0004,
    RxErr       = 0x0002,
    RxOK        = 0x0001,

    /* RxStatusDesc */
    RxRWT = (1 << 22),
    RxRES = (1 << 21),
    RxRUNT = (1 << 20),
    RxCRC = (1 << 19),

    /* ChipCmdBits */
    StopReq  = 0x80,
    CmdReset = 0x10,
    CmdRxEnb = 0x08,
    CmdTxEnb = 0x04,
    RxBufEmpty = 0x01,

    /* Cfg9346Bits */
    Cfg9346_Lock = 0x00,
    Cfg9346_Unlock = 0xC0,
    Cfg9346_EEDO = (1 << 0),
    Cfg9346_EEDI = (1 << 1),
    Cfg9346_EESK = (1 << 2),
    Cfg9346_EECS = (1 << 3),
    Cfg9346_EEM0 = (1 << 6),
    Cfg9346_EEM1 = (1 << 7),

    /* rx_mode_bits */
    AcceptErr = 0x20,
    AcceptRunt = 0x10,
    AcceptBroadcast = 0x08,
    AcceptMulticast = 0x04,
    AcceptMyPhys = 0x02,
    AcceptAllPhys = 0x01,

    /* Transmit Priority Polling*/
    HPQ = 0x80,
    NPQ = 0x40,
    FSWInt = 0x01,

    /* RxConfigBits */
    Reserved2_shift = 13,
    RxCfgDMAShift = 8,
    RxCfg_128_int_en = (1 << 15),
    RxCfg_fet_multi_en = (1 << 14),
    RxCfg_half_refetch = (1 << 13),
    RxCfg_9356SEL = (1 << 6),

    /* TxConfigBits */
    TxInterFrameGapShift = 24,
    TxDMAShift = 8, /* DMA burst value (0-7) is shift this many bits */
    TxMACLoopBack = (1 << 17),  /* MAC loopback */

    /* Config1 register */
    LEDS1       = (1 << 7),
    LEDS0       = (1 << 6),
    Speed_down  = (1 << 4),
    MEMMAP      = (1 << 3),
    IOMAP       = (1 << 2),
    VPD         = (1 << 1),
    PMEnable    = (1 << 0), /* Power Management Enable */

    /* Config2 register */
    PMSTS_En    = (1 << 5),

    /* Config3 register */
    Isolate_en  = (1 << 12), /* Isolate enable */
    MagicPacket = (1 << 5), /* Wake up when receives a Magic Packet */
    LinkUp      = (1 << 4), /* This bit is reserved in RTL8168B.*/
    /* Wake up when the cable connection is re-established */
    ECRCEN      = (1 << 3), /* This bit is reserved in RTL8168B*/
    Jumbo_En0   = (1 << 2), /* This bit is reserved in RTL8168B*/
    RDY_TO_L23  = (1 << 1), /* This bit is reserved in RTL8168B*/
    Beacon_en   = (1 << 0), /* This bit is reserved in RTL8168B*/

    /* Config4 register */
    Jumbo_En1   = (1 << 1), /* This bit is reserved in RTL8168B*/

    /* Config5 register */
    BWF     = (1 << 6), /* Accept Broadcast wakeup frame */
    MWF     = (1 << 5), /* Accept Multicast wakeup frame */
    UWF     = (1 << 4), /* Accept Unicast wakeup frame */
    LanWake     = (1 << 1), /* LanWake enable/disable */
    PMEStatus   = (1 << 0), /* PME status can be reset by PCI RST# */

    /* CPlusCmd */
    EnableBist  = (1 << 15),
    Macdbgo_oe  = (1 << 14),
    Normal_mode = (1 << 13),
    Force_halfdup   = (1 << 12),
    Force_rxflow_en = (1 << 11),
    Force_txflow_en = (1 << 10),
    Cxpl_dbg_sel    = (1 << 9),//This bit is reserved in RTL8168B
    ASF     = (1 << 8),//This bit is reserved in RTL8168C
    PktCntrDisable  = (1 << 7),
    RxVlan      = (1 << 6),
    RxChkSum    = (1 << 5),
    Macdbgo_sel = 0x001C,
    INTT_0      = 0x0000,
    INTT_1      = 0x0001,
    INTT_2      = 0x0002,
    INTT_3      = 0x0003,

    /* rtl8168_PHYstatus */
    PowerSaveStatus = 0x80,
    TxFlowCtrl = 0x40,
    RxFlowCtrl = 0x20,
    _1000bpsF = 0x10,
    _100bps = 0x08,
    _10bps = 0x04,
    LinkStatus = 0x02,
    FullDup = 0x01,

    /* DBG_reg */
    Fix_Nak_1 = (1 << 4),
    Fix_Nak_2 = (1 << 3),
    DBGPIN_E2 = (1 << 0),

    /* DumpCounterCommand */
    CounterDump = 0x8,

    /* PHY access */
    PHYAR_Flag = 0x80000000,
    PHYAR_Write = 0x80000000,
    PHYAR_Read = 0x00000000,
    PHYAR_Reg_Mask = 0x1f,
    PHYAR_Reg_shift = 16,
    PHYAR_Data_Mask = 0xffff,

    /* EPHY access */
    EPHYAR_Flag = 0x80000000,
    EPHYAR_Write = 0x80000000,
    EPHYAR_Read = 0x00000000,
    EPHYAR_Reg_Mask = 0x1f,
    EPHYAR_Reg_shift = 16,
    EPHYAR_Data_Mask = 0xffff,

    /* CSI access */
    CSIAR_Flag = 0x80000000,
    CSIAR_Write = 0x80000000,
    CSIAR_Read = 0x00000000,
    CSIAR_ByteEn = 0x0f,
    CSIAR_ByteEn_shift = 12,
    CSIAR_Addr_Mask = 0x0fff,

    /* ERI access */
    ERIAR_Flag = 0x80000000,
    ERIAR_Write = 0x80000000,
    ERIAR_Read = 0x00000000,
    ERIAR_Addr_Align = 4, /* ERI access register address must be 4 byte alignment */
    ERIAR_ExGMAC = 0,
    ERIAR_MSIX = 1,
    ERIAR_ASF = 2,
    ERIAR_OOB = 2,
    ERIAR_Type_shift = 16,
    ERIAR_ByteEn = 0x0f,
    ERIAR_ByteEn_shift = 12,

    /* OCP GPHY access */
    OCPDR_Write = 0x80000000,
    OCPDR_Read = 0x00000000,
    OCPDR_Reg_Mask = 0xFF,
    OCPDR_Data_Mask = 0xFFFF,
    OCPDR_GPHY_Reg_shift = 16,
    OCPAR_Flag = 0x80000000,
    OCPAR_GPHY_Write = 0x8000F060,
    OCPAR_GPHY_Read = 0x0000F060,
    OCPR_Write = 0x80000000,
    OCPR_Read = 0x00000000,
    OCPR_Addr_Reg_shift = 16,
    OCPR_Flag = 0x80000000,
    OCP_STD_PHY_BASE_PAGE = 0x0A40,

    /* MCU Command */
    Now_is_oob = (1 << 7),
    Txfifo_empty = (1 << 5),
    Rxfifo_empty = (1 << 4),

    /* E-FUSE access */
    EFUSE_WRITE = 0x80000000,
    EFUSE_WRITE_OK  = 0x00000000,
    EFUSE_READ  = 0x00000000,
    EFUSE_READ_OK   = 0x80000000,
    EFUSE_Reg_Mask  = 0x03FF,
    EFUSE_Reg_Shift = 8,
    EFUSE_Check_Cnt = 300,
    EFUSE_READ_FAIL = 0xFF,
    EFUSE_Data_Mask = 0x000000FF,

    /* GPIO */
    GPIO_en = (1 << 0),

};

enum _DescStatusBit {
    DescOwn     = (1 << 31), /* Descriptor is owned by NIC */
    RingEnd     = (1 << 30), /* End of descriptor ring */
    FirstFrag   = (1 << 29), /* First segment of a packet */
    LastFrag    = (1 << 28), /* Final segment of a packet */

    /* Tx private */
    /*------ offset 0 of tx descriptor ------*/
    LargeSend   = (1 << 27), /* TCP Large Send Offload (TSO) */
    LargeSend_DP = (1 << 16), /* TCP Large Send Offload (TSO) */
    MSSShift    = 16,        /* MSS value position */
    MSSMask     = 0x7FFU,    /* MSS value 11 bits */
    TxIPCS      = (1 << 18), /* Calculate IP checksum */
    TxUDPCS     = (1 << 17), /* Calculate UDP/IP checksum */
    TxTCPCS     = (1 << 16), /* Calculate TCP/IP checksum */
    TxVlanTag   = (1 << 17), /* Add VLAN tag */

    /*@@@@@@ offset 4 of tx descriptor => bits for RTL8168C/CP only     begin @@@@@@*/
    TxUDPCS_C   = (1 << 31), /* Calculate UDP/IP checksum */
    TxTCPCS_C   = (1 << 30), /* Calculate TCP/IP checksum */
    TxIPCS_C    = (1 << 29), /* Calculate IP checksum */
    /*@@@@@@ offset 4 of tx descriptor => bits for RTL8168C/CP only     end @@@@@@*/


    /* Rx private */
    /*------ offset 0 of rx descriptor ------*/
    PID1        = (1 << 18), /* Protocol ID bit 1/2 */
    PID0        = (1 << 17), /* Protocol ID bit 2/2 */

#define RxProtoUDP  (PID1)
#define RxProtoTCP  (PID0)
#define RxProtoIP   (PID1 | PID0)
#define RxProtoMask RxProtoIP

    RxIPF       = (1 << 16), /* IP checksum failed */
    RxUDPF      = (1 << 15), /* UDP/IP checksum failed */
    RxTCPF      = (1 << 14), /* TCP/IP checksum failed */
    RxVlanTag   = (1 << 16), /* VLAN tag available */

    /*@@@@@@ offset 0 of rx descriptor => bits for RTL8168C/CP only     begin @@@@@@*/
    RxUDPT      = (1 << 18),
    RxTCPT      = (1 << 17),
    /*@@@@@@ offset 0 of rx descriptor => bits for RTL8168C/CP only     end @@@@@@*/

    /*@@@@@@ offset 4 of rx descriptor => bits for RTL8168C/CP only     begin @@@@@@*/
    RxV6F       = (1 << 31),
    RxV4F       = (1 << 30),
    /*@@@@@@ offset 4 of rx descriptor => bits for RTL8168C/CP only     end @@@@@@*/
};

enum bits {
    BIT_0 = (1 << 0),
    BIT_1 = (1 << 1),
    BIT_2 = (1 << 2),
    BIT_3 = (1 << 3),
    BIT_4 = (1 << 4),
    BIT_5 = (1 << 5),
    BIT_6 = (1 << 6),
    BIT_7 = (1 << 7),
    BIT_8 = (1 << 8),
    BIT_9 = (1 << 9),
    BIT_10 = (1 << 10),
    BIT_11 = (1 << 11),
    BIT_12 = (1 << 12),
    BIT_13 = (1 << 13),
    BIT_14 = (1 << 14),
    BIT_15 = (1 << 15),
    BIT_16 = (1 << 16),
    BIT_17 = (1 << 17),
    BIT_18 = (1 << 18),
    BIT_19 = (1 << 19),
    BIT_20 = (1 << 20),
    BIT_21 = (1 << 21),
    BIT_22 = (1 << 22),
    BIT_23 = (1 << 23),
    BIT_24 = (1 << 24),
    BIT_25 = (1 << 25),
    BIT_26 = (1 << 26),
    BIT_27 = (1 << 27),
    BIT_28 = (1 << 28),
    BIT_29 = (1 << 29),
    BIT_30 = (1 << 30),
    BIT_31 = (1 << 31)
};

enum effuse {
    EFUSE_SUPPORT = 1,
    EFUSE_NOT_SUPPORT = 0,
};

struct TxDesc {
    u32 opts1;
    u32 opts2;
    u64 addr;
};

struct RxDesc {
    u32 opts1;
    u32 opts2;
    u64 addr;
};

enum mcfg {
    CFG_METHOD_1=0,
    CFG_METHOD_2,
    CFG_METHOD_3,
    CFG_METHOD_4,
    CFG_METHOD_5,
    CFG_METHOD_6,
    CFG_METHOD_7,
    CFG_METHOD_8,
    CFG_METHOD_9 ,
    CFG_METHOD_10,
    CFG_METHOD_11,
    CFG_METHOD_12,
    CFG_METHOD_13,
    CFG_METHOD_14,
    CFG_METHOD_15,
    CFG_METHOD_16,
    CFG_METHOD_17,
    CFG_METHOD_18,
    CFG_METHOD_19,
    CFG_METHOD_20,
    CFG_METHOD_21,
    CFG_METHOD_22,
    CFG_METHOD_23,
    CFG_METHOD_24,
    CFG_METHOD_25,
    CFG_METHOD_26,
    CFG_METHOD_27,
    CFG_METHOD_MAX,
    CFG_METHOD_DEFAULT = 0xFF
};

#define _R(NAME,MAC,RCR,MASK, JumFrameSz) \
    { .name = NAME, .mcfg = MAC, .RCR_Cfg = RCR, .RxConfigMask = MASK, .jumbo_frame_sz = JumFrameSz }

static const struct {
    const char *name;
    u8 mcfg;
    u32 RCR_Cfg;
    u32 RxConfigMask;   /* Clears the bits supported by this chip */
    u32 jumbo_frame_sz;
} rtl_chip_info[] = {
    _R("RTL8168B/8111B",
    CFG_METHOD_1,
    (Reserved2_data << Reserved2_shift) | (RX_DMA_BURST << RxCfgDMAShift),
    0xff7e1880,
    Jumbo_Frame_4k),

    _R("RTL8168B/8111B",
    CFG_METHOD_2,
    (Reserved2_data << Reserved2_shift) | (RX_DMA_BURST << RxCfgDMAShift),
    0xff7e1880,
    Jumbo_Frame_4k),

    _R("RTL8168B/8111B",
    CFG_METHOD_3,
    (Reserved2_data << Reserved2_shift) | (RX_DMA_BURST << RxCfgDMAShift),
    0xff7e1880,
    Jumbo_Frame_4k),

    _R("RTL8168C/8111C",
    CFG_METHOD_4, RxCfg_128_int_en | RxCfg_fet_multi_en | (RX_DMA_BURST << RxCfgDMAShift),
    0xff7e1880,
    Jumbo_Frame_6k),

    _R("RTL8168C/8111C",
    CFG_METHOD_5,
    RxCfg_128_int_en | RxCfg_fet_multi_en | (RX_DMA_BURST << RxCfgDMAShift),
    0xff7e1880,
    Jumbo_Frame_6k),

    _R("RTL8168C/8111C",
    CFG_METHOD_6,
    RxCfg_128_int_en | RxCfg_fet_multi_en | (RX_DMA_BURST << RxCfgDMAShift),
    0xff7e1880,
    Jumbo_Frame_6k),

    _R("RTL8168CP/8111CP",
    CFG_METHOD_7,
    RxCfg_128_int_en | RxCfg_fet_multi_en | (RX_DMA_BURST << RxCfgDMAShift),
    0xff7e1880,
    Jumbo_Frame_6k),

    _R("RTL8168CP/8111CP",
    CFG_METHOD_8,
    RxCfg_128_int_en | RxCfg_fet_multi_en | (RX_DMA_BURST << RxCfgDMAShift),
    0xff7e1880,
    Jumbo_Frame_6k),

    _R("RTL8168D/8111D",
    CFG_METHOD_9,
    RxCfg_128_int_en | (RX_DMA_BURST << RxCfgDMAShift),
    0xff7e1880,
    Jumbo_Frame_9k),

    _R("RTL8168D/8111D",
    CFG_METHOD_10,
    RxCfg_128_int_en | (RX_DMA_BURST << RxCfgDMAShift),
    0xff7e1880,
    Jumbo_Frame_9k),

    _R("RTL8168DP/8111DP",
    CFG_METHOD_11,
    RxCfg_128_int_en | (RX_DMA_BURST << RxCfgDMAShift),
    0xff7e1880,
    Jumbo_Frame_9k),

    _R("RTL8168DP/8111DP",
    CFG_METHOD_12,
    RxCfg_128_int_en | (RX_DMA_BURST << RxCfgDMAShift),
    0xff7e1880,
    Jumbo_Frame_9k),

    _R("RTL8168DP/8111DP",
    CFG_METHOD_13,
    RxCfg_128_int_en | (RX_DMA_BURST << RxCfgDMAShift),
    0xff7e1880,
    Jumbo_Frame_9k),

    _R("RTL8168E/8111E",
    CFG_METHOD_14,
    RxCfg_128_int_en | (RX_DMA_BURST << RxCfgDMAShift),
    0xff7e1880,
    Jumbo_Frame_9k),

    _R("RTL8168E/8111E",
    CFG_METHOD_15,
    RxCfg_128_int_en | (RX_DMA_BURST << RxCfgDMAShift),
    0xff7e1880,
    Jumbo_Frame_9k),

    _R("RTL8168E-VL/8111E-VL",
    CFG_METHOD_16,
    RxEarly_off_V1 | (RX_DMA_BURST << RxCfgDMAShift),
    0xff7e0080,
    Jumbo_Frame_9k),

    _R("RTL8168E-VL/8111E-VL",
    CFG_METHOD_17,
    RxEarly_off_V1 | (RX_DMA_BURST << RxCfgDMAShift),
    0xff7e1880,
    Jumbo_Frame_9k),

    _R("RTL8168F/8111F",
    CFG_METHOD_18,
    RxEarly_off_V1 | (RX_DMA_BURST << RxCfgDMAShift),
    0xff7e1880,
    Jumbo_Frame_9k),

    _R("RTL8168F/8111F",
    CFG_METHOD_19,
    RxEarly_off_V1 | (RX_DMA_BURST << RxCfgDMAShift),
    0xff7e1880,
    Jumbo_Frame_9k),

    _R("RTL8411",
    CFG_METHOD_20,
    (RX_DMA_BURST << RxCfgDMAShift),
    0xff7e1880,
    Jumbo_Frame_9k),

    _R("RTL8168G/8111G",
    CFG_METHOD_21,
    RxEarly_off_V2 | (RX_DMA_BURST << RxCfgDMAShift),
    0xff7e1880,
    Jumbo_Frame_9k),

    _R("RTL8168G/8111G",
    CFG_METHOD_22,
    RxEarly_off_V2 | (RX_DMA_BURST << RxCfgDMAShift),
    0xff7e1880,
    Jumbo_Frame_9k),

    _R("RTL8168EP/8111EP",
    CFG_METHOD_23,
    RxEarly_off_V2 | (RX_DMA_BURST << RxCfgDMAShift),
    0xff7e1880,
    Jumbo_Frame_9k),

    _R("RTL8168GU/8111GU",
    CFG_METHOD_24,
    RxEarly_off_V2 | (RX_DMA_BURST << RxCfgDMAShift),
    0xff7e1880,
    Jumbo_Frame_9k),

    _R("RTL8168GU/8111GU",
    CFG_METHOD_25,
    RxCfg_fet_multi_en | RxCfg_128_int_en| (RX_DMA_BURST_128 << RxCfgDMAShift),
    0xff7e1880,
    Jumbo_Frame_9k),

    _R("8411B",
    CFG_METHOD_26,
    RxEarly_off_V2 | (RX_DMA_BURST << RxCfgDMAShift),
    0xff7e1880,
    Jumbo_Frame_9k),

    _R("RTL8168EP/8111EP",
    CFG_METHOD_27,
    RxEarly_off_V2 | (RX_DMA_BURST << RxCfgDMAShift),
    0xff7e1880,
    Jumbo_Frame_9k),

    _R("Unknown",
    CFG_METHOD_DEFAULT,
    (RX_DMA_BURST << RxCfgDMAShift),
    0xff7e1880,
    RX_BUF_SIZE)
};

struct rtl8168_private {
    struct eth_device *dev;
    phys_addr_t mmio_addr;  /* memory map physical address */
    pci_dev_t devno;
    int chipset;
    u32 mcfg;
    u32 cur_page;
    u32 cur_rx; /* Index into the Rx descriptor buffer of next Rx pkt. */
    u32 cur_tx; /* Index into the Tx descriptor buffer of next Rx pkt. */
    u32 dirty_rx;
    u32 dirty_tx;
    u8 *DescArrays; /* Index of Descriptor buffer */
    struct TxDesc *TxDescArray; /* Index of 256-alignment Tx Descriptor buffer */
    struct RxDesc *RxDescArray; /* Index of 256-alignment Rx Descriptor buffer */
    u8 *RxBufferRings;  /* Index of Rx Buffer  */
    u8 *RxBufferRing[NUM_RX_DESC];  /* Index of Rx Buffer array */

    u8  efuse;
    u32 rx_buf_sz;
    u32 rtl8168_rx_config;

    u16 cp_cmd;
    u8 ext_phy;
    u8 phy_type;    /* 0: FEPHY, 1: SGMII */
    u8 bypass_enable;   /* 0: disable, 1: enable */
    u8 acp_enable;  /* 0: disable, 1: enable */
};

#define ALIGN_8                 (0x7)
#define ALIGN_16                (0xf)
#define ALIGN_32                (0x1f)
#define ALIGN_64                (0x3f)
#define ALIGN_256               (0xff)

typedef struct _GDUMP_TALLY {
    u64 TxOK;
    u64 RxOK;
    u64 TxERR;
    u32 RxERR;
    u16 MissPkt;
    u16 FAE;
    u32 Tx1Col;
    u32 TxMCol;
    u64 RxOKPhy;
    u64 RxOKBrd;
    u32 RxOKMul;
    u16 TxAbt;
    u16 TxUndrn; //only possible on jumbo frames
}

GDUMP_TALLY, *PGDUMP_TALLY;

static u8 dummy[sizeof( GDUMP_TALLY ) + ALIGN_64];


static void mac_ocp_write(struct rtl8168_private *tp, u16 reg_addr, u16 value)
{
    phys_addr_t ioaddr = tp->mmio_addr;
    u32 data32;

    data32 = reg_addr/2;
    data32 <<= OCPR_Addr_Reg_shift;
    data32 += value;
    data32 |= OCPR_Write;

    RTL_W32(MACOCP, data32);
}

static u16 mac_ocp_read(struct rtl8168_private *tp, u16 reg_addr)
{
    phys_addr_t ioaddr = tp->mmio_addr;
    u32 data32;
    u16 data16 = 0;

    data32 = reg_addr/2;
    data32 <<= OCPR_Addr_Reg_shift;

    RTL_W32(MACOCP, data32);
    data16 = (u16)RTL_R32(MACOCP);

    return data16;
}

static inline u16 map_phy_ocp_addr(u16 PageNum, u8 RegNum)
{
    u16 OcpPageNum = 0;
    u8 OcpRegNum = 0;
    u16 OcpPhyAddress = 0;

    if( PageNum == 0 ) {
        OcpPageNum = OCP_STD_PHY_BASE_PAGE + ( RegNum / 8 );
        OcpRegNum = 0x10 + ( RegNum % 8 );
    } else {
        OcpPageNum = PageNum;
        OcpRegNum = RegNum;
    }

    OcpPageNum <<= 4;

    if( OcpRegNum < 16 ) {
        OcpPhyAddress = 0;
    } else {
        OcpRegNum -= 16;
        OcpRegNum <<= 1;

        OcpPhyAddress = OcpPageNum + OcpRegNum;
    }


    return OcpPhyAddress;
}

#if PLATFORM_RTD1395
#define MDIO_WAIT_TIMEOUT   100
#define MDIO_LOCK                                                   \
do {                                                                \
    u32 stable_ticks = 0;                                           \
    u32 wait_cnt = 0;                                               \
                                                                    \
    /* enter driver mode */                                         \
    mac_ocp_write(tp, 0xDE42, mac_ocp_read(tp, 0xDE42) | BIT_0);    \
    /* wait MDIO channel is stable and idle 10us */                 \
    while (10 > stable_ticks) {                                     \
        while (0 != (BIT_0 & mac_ocp_read(tp, 0xDE4E))) {           \
            stable_ticks = 0;                                       \
            wait_cnt++;                                             \
            udelay(1);                                              \
            if (wait_cnt > MDIO_WAIT_TIMEOUT) {                     \
                printf("%s:%d: MDIO lock failed\n",                 \
                    __func__,__LINE__);                             \
                stable_ticks = 10;                                  \
                break;                                              \
            }                                                       \
        }                                                           \
        stable_ticks++;                                             \
        udelay(1);                                                  \
    }                                                               \
} while (0)

#define MDIO_UNLOCK                                                 \
do {                                                                \
    /* exit driver mode */                                          \
    mac_ocp_write(tp, 0xDE42, mac_ocp_read(tp, 0xDE42) & ~BIT_0);   \
} while (0)
#else
#define MDIO_LOCK
#define MDIO_UNLOCK
#endif /* PLATFORM_RTD1395 */

static void rtl8168_ephy_write(phys_addr_t ioaddr, int RegAddr, int value);
static u16 rtl8168_ephy_read(phys_addr_t ioaddr, int RegAddr);

static void mdio_write(struct rtl8168_private *tp,
                       u32 RegAddr,
                       u32 value)
{
    phys_addr_t ioaddr = tp->mmio_addr;
    int i;

    if (RegAddr == 0x1F) {
        tp->cur_page = value;
    }
    if (tp->ext_phy) {
        rtl8168_ephy_write(ioaddr, RegAddr, value);
        return;
    }


    if (tp->mcfg == CFG_METHOD_11) {
        RTL_W32(OCPDR, OCPDR_Write |
                (RegAddr & OCPDR_Reg_Mask) << OCPDR_GPHY_Reg_shift |
                (value & OCPDR_Data_Mask));
        RTL_W32(OCPAR, OCPAR_GPHY_Write);
        RTL_W32(EPHY_RXER_NUM, 0);

        for (i = 0; i < 100; i++) {
            mdelay(1);
            if (!(RTL_R32(OCPAR) & OCPAR_Flag))
                break;
        }
    }/* else if (tp->mcfg == CFG_METHOD_21 || tp->mcfg == CFG_METHOD_22 ||
               tp->mcfg == CFG_METHOD_23 || tp->mcfg == CFG_METHOD_24 ||
               tp->mcfg == CFG_METHOD_25 || tp->mcfg == CFG_METHOD_26 ||
               tp->mcfg == CFG_METHOD_27) {
        u32 data32;
        u16 ocp_addr;

        if (RegAddr == 0x1F) {
            return;
        }
        ocp_addr = map_phy_ocp_addr(tp->cur_page, RegAddr);

        data32 = ocp_addr/2;
        data32 <<= OCPR_Addr_Reg_shift;
        data32 |= OCPR_Write | value;

        RTL_W32(PHYOCP, data32);
        for (i = 0; i < 100; i++) {
            udelay(1);

            if (!(RTL_R32(PHYOCP) & OCPR_Flag))
                break;
        }
    } */
    else {
        if (tp->mcfg == CFG_METHOD_12 || tp->mcfg == CFG_METHOD_13)
            RTL_W32(0xD0, RTL_R32(0xD0) & ~0x00020000);

        RTL_W32(PHYAR, PHYAR_Write |
                (RegAddr & PHYAR_Reg_Mask) << PHYAR_Reg_shift |
                (value & PHYAR_Data_Mask));
        //printf("WPHY addr %x value %x \n",RegAddr,value);
        for (i = 0; i < 10; i++) {
            udelay(100);

            /* Check if the RTL8168 has completed writing to the specified MII register */
            if (!(RTL_R32(PHYAR) & PHYAR_Flag)) {
                udelay(20);
                break;
            }
        }

        if (tp->mcfg == CFG_METHOD_12 || tp->mcfg == CFG_METHOD_13)
            RTL_W32(0xD0, RTL_R32(0xD0) | 0x00020000);
    }
}

static u32 mdio_read(struct rtl8168_private *tp,
                     u32 RegAddr)
{
    phys_addr_t ioaddr = tp->mmio_addr;
    int i, value = 0;
    if (tp->ext_phy) {
        return rtl8168_ephy_read(ioaddr, RegAddr);
    }

    if (tp->mcfg==CFG_METHOD_11) {
        RTL_W32(OCPDR, OCPDR_Read |
                (RegAddr & OCPDR_Reg_Mask) << OCPDR_GPHY_Reg_shift);
        RTL_W32(OCPAR, OCPAR_GPHY_Write);
        RTL_W32(EPHY_RXER_NUM, 0);

        for (i = 0; i < 100; i++) {
            mdelay(1);
            if (!(RTL_R32(OCPAR) & OCPAR_Flag))
                break;
        }

        mdelay(1);
        RTL_W32(OCPAR, OCPAR_GPHY_Read);
        RTL_W32(EPHY_RXER_NUM, 0);

        for (i = 0; i < 100; i++) {
            mdelay(1);
            if (RTL_R32(OCPAR) & OCPAR_Flag)
                break;
        }

        value = RTL_R32(OCPDR) & OCPDR_Data_Mask;
    } /*else if (tp->mcfg == CFG_METHOD_21 || tp->mcfg == CFG_METHOD_22 ||
               tp->mcfg == CFG_METHOD_23 || tp->mcfg == CFG_METHOD_24 ||
               tp->mcfg == CFG_METHOD_25 || tp->mcfg == CFG_METHOD_26 ||
               tp->mcfg == CFG_METHOD_27) {
        u32 data32;
        u16 ocp_addr;

        ocp_addr = map_phy_ocp_addr(tp->cur_page, RegAddr);

        data32 = ocp_addr/2;
        data32 <<= OCPR_Addr_Reg_shift;

        RTL_W32(PHYOCP, data32);
        for (i = 0; i < 100; i++) {
            udelay(1);

            if (RTL_R32(PHYOCP) & OCPR_Flag)
                break;
        }
        value = RTL_R32(PHYOCP) & OCPDR_Data_Mask;
    } */
    else {
        if (tp->mcfg == CFG_METHOD_12 || tp->mcfg == CFG_METHOD_13)
            RTL_W32(0xD0, RTL_R32(0xD0) & ~0x00020000);

        RTL_W32(PHYAR,
                PHYAR_Read | (RegAddr & PHYAR_Reg_Mask) << PHYAR_Reg_shift);

        for (i = 0; i < 10; i++) {
            udelay(100);

            /* Check if the RTL8168 has completed retrieving data from the specified MII register */
            if (RTL_R32(PHYAR) & PHYAR_Flag) {
                value = RTL_R32(PHYAR) & PHYAR_Data_Mask;
                udelay(20);
                break;
            }
        }
        //printf("RPHY addr %x value %x \n",RegAddr,value);
        if (tp->mcfg == CFG_METHOD_12 || tp->mcfg == CFG_METHOD_13)
            RTL_W32(0xD0, RTL_R32(0xD0) | 0x00020000);
    }

    return value;
}

static void rtl8168_ephy_write(phys_addr_t ioaddr, int RegAddr, int value)
{
    int i;

    RTL_W32(EPHYAR,
            EPHYAR_Write |
            (RegAddr & EPHYAR_Reg_Mask) << EPHYAR_Reg_shift |
            (value & EPHYAR_Data_Mask));

    for (i = 0; i < 10; i++) {
        udelay(100);

        /* Check if the RTL8168 has completed EPHY write */
        if (!(RTL_R32(EPHYAR) & EPHYAR_Flag))
            break;
    }

    udelay(20);
}

static u16 rtl8168_ephy_read(phys_addr_t ioaddr, int RegAddr)
{
    int i;
    u16 value = 0xffff;

    RTL_W32(EPHYAR,
            EPHYAR_Read | (RegAddr & EPHYAR_Reg_Mask) << EPHYAR_Reg_shift);

    for (i = 0; i < 10; i++) {
        udelay(100);

        /* Check if the RTL8168 has completed EPHY read */
        if (RTL_R32(EPHYAR) & EPHYAR_Flag) {
            value = (u16) (RTL_R32(EPHYAR) & EPHYAR_Data_Mask);
            break;
        }
    }

    udelay(20);

    return value;
}

static u32 rtl8168_eri_read(phys_addr_t ioaddr, int addr, int len, int type)
{
    int i, val_shift, shift = 0;
    u32 value1 = 0, value2 = 0, mask;

    if (len > 4 || len <= 0)
        return -1;

    while (len > 0) {
        val_shift = addr % ERIAR_Addr_Align;
        addr = addr & ~0x3;

        RTL_W32(ERIAR,
                ERIAR_Read |
                type << ERIAR_Type_shift |
                ERIAR_ByteEn << ERIAR_ByteEn_shift |
                addr);

        for (i = 0; i < 10; i++) {
            udelay(100);

            /* Check if the RTL8168 has completed ERI read */
            if (RTL_R32(ERIAR) & ERIAR_Flag)
                break;
        }

        if (len == 1)       mask = (0xFF << (val_shift * 8)) & 0xFFFFFFFF;
        else if (len == 2)  mask = (0xFFFF << (val_shift * 8)) & 0xFFFFFFFF;
        else if (len == 3)  mask = (0xFFFFFF << (val_shift * 8)) & 0xFFFFFFFF;
        else            mask = (0xFFFFFFFF << (val_shift * 8)) & 0xFFFFFFFF;

        value1 = RTL_R32(ERIDR) & mask;
        value2 |= (value1 >> val_shift * 8) << shift * 8;

        if (len <= 4 - val_shift) {
            len = 0;
        } else {
            len -= (4 - val_shift);
            shift = 4 - val_shift;
            addr += 4;
        }
    }

    return value2;
}

static int rtl8168_eri_write(phys_addr_t ioaddr, int addr, int len, u32 value, int type)
{
    int i, val_shift, shift = 0;
    u32 value1 = 0, mask;

    if (len > 4 || len <= 0)
        return -1;

    while (len > 0) {
        val_shift = addr % ERIAR_Addr_Align;
        addr = addr & ~0x3;

        if (len == 1)       mask = (0xFF << (val_shift * 8)) & 0xFFFFFFFF;
        else if (len == 2)  mask = (0xFFFF << (val_shift * 8)) & 0xFFFFFFFF;
        else if (len == 3)  mask = (0xFFFFFF << (val_shift * 8)) & 0xFFFFFFFF;
        else            mask = (0xFFFFFFFF << (val_shift * 8)) & 0xFFFFFFFF;

        value1 = rtl8168_eri_read(ioaddr, addr, 4, type) & ~mask;
        value1 |= ((value << val_shift * 8) >> shift * 8);

        RTL_W32(ERIDR, value1);
        RTL_W32(ERIAR,
                ERIAR_Write |
                type << ERIAR_Type_shift |
                ERIAR_ByteEn << ERIAR_ByteEn_shift |
                addr);

        for (i = 0; i < 10; i++) {
            udelay(100);

            /* Check if the RTL8168 has completed ERI write */
            if (!(RTL_R32(ERIAR) & ERIAR_Flag))
                break;
        }

        if (len <= 4 - val_shift) {
            len = 0;
        } else {
            len -= (4 - val_shift);
            shift = 4 - val_shift;
            addr += 4;
        }
    }

    return 0;
}

/**************************************************************************
RECV - Receive a frame
***************************************************************************/
static int rtl8168_recv(struct eth_device *dev)
{
    /* return true if there's an ethernet packet ready to read */
    /* nic->packet should contain data on return */
    /* nic->packetlen should contain length of data */
    struct rtl8168_private *tp = (struct rtl8168_private *)dev->priv;
    phys_addr_t ioaddr = tp->mmio_addr;
    int cur_rx;
    int length = 0;
    u16 sts = RTL_R16(IntrStatus);
    int count =0;
    int i=0;
    u32 addr,size;
#ifdef DEBUG_RTL8168_RX
    printf ("%s\n", __FUNCTION__);
#endif

   // printf("IntrStatus %x \n",IntrStatus);

    RTL_W16(IntrStatus, sts);

    rmb();

   // if ((sts & (RxOK)))
   //     printf("RxOK %x \n",sts);
  //  if ((sts & (RxDescUnavail | RxErr | RxOK)) == 0)
  //      return 0;

    cur_rx = tp->cur_rx;

   // while(1) {
        addr=(u32)(uintptr_t)&tp->RxDescArray[cur_rx];
        addr &= ~(ARCH_ALIGN - 1);
        size = roundup(sizeof(struct RxDesc), ARCH_ALIGN);
        invalidate_dcache_range(addr, addr + size);

        //printf ("RX cur_rx = %X opts1 = %X \n", cur_rx, le32_to_cpu(tp->RxDescArray[cur_rx].opts1));

        if ((le32_to_cpu(tp->RxDescArray[cur_rx].opts1) & DescOwn) == 0) {

            count = count +1;

            if (!(le32_to_cpu(tp->RxDescArray[cur_rx].opts1) & RxRES)) {
                length = (int) (le32_to_cpu(tp->RxDescArray[cur_rx].
                                            opts1) & 0x00003fff) - 4;


                invalidate_dcache_range((unsigned long)tp->RxBufferRing[cur_rx],(unsigned long)tp->RxBufferRing[cur_rx]+length);
                dmb();
                net_process_received_packet(tp->RxBufferRing[cur_rx], length);

             //   printf ("NetReceive\n");
            } else {
                puts("Error Rx");
            }
            /*
            * Free the current buffer, restart the engine and move forward
            * to the next buffer. Here we check if the whole cacheline of
            * descriptors was already processed and if so, we mark it free
            * as whole.
            */
            size = _RXDESC_PER_CACHELINE - 1;
            if ((cur_rx & size) == size)
            {
                for (i = cur_rx - size; i <= cur_rx ; i++) {
                    if (i == NUM_RX_DESC - 1){
                        tp->RxDescArray[i].opts1 =
                            cpu_to_le32(DescOwn | RingEnd | tp->rx_buf_sz);
                    }
                    else{
                        tp->RxDescArray[i].opts1 =
                            cpu_to_le32(DescOwn | tp->rx_buf_sz);
                    }
                }

                flush_cache((unsigned long)&tp->RxDescArray[cur_rx-size],ARCH_ALIGN);
            }
            cur_rx = (cur_rx + 1) % NUM_RX_DESC;
            tp->cur_rx = cur_rx;

        } else {
          //  printf ("NetReceive %d packets\n",count);
            return count;
        }

    return (0);     /* initially as this is called to flush the input */
}

#define HZ 1000

#if 0
static void print_packet( u8 * buf, int length )
{
    int i;
    int remainder;
    int lines;

    printf("Packet of length %d \n", length );

    lines = length / 16;
    remainder = length % 16;

    for ( i = 0; i < lines ; i ++ ) {
        int cur;

        for ( cur = 0; cur < 8; cur ++ ) {
            u8 a, b;

            a = *(buf ++ );
            b = *(buf ++ );
            printf("%02x%02x ", a, b );
        }
        printf("\n");
    }
    for ( i = 0; i < remainder/2 ; i++ ) {
        u8 a, b;

        a = *(buf ++ );
        b = *(buf ++ );
        printf("%02x%02x ", a, b );
    }
    printf("\n");
}
#endif

/**************************************************************************
SEND - Transmit a frame
***************************************************************************/
static int rtl8168_send(struct eth_device *dev, void *packet, int length)
{
    /* send the packet to destination */
    struct rtl8168_private *tp = (struct rtl8168_private *)dev->priv;
    phys_addr_t ioaddr = tp->mmio_addr;
    u32 to, len = length;
    int ret, cur_tx;


#ifdef DEBUG_RTL8168_TX
    int stime = currticks();
    printf ("%s\n", __FUNCTION__);
    printf("sending %d bytes\n", len);
#endif

    cur_tx = tp->cur_tx;

#ifdef DEBUG_RTL8168_TX
    u8 *buf;
    buf = (u8 *) packet;
    printf("pointer %x\n",packet);

    print_packet (buf, length);
#endif

    tp->TxDescArray[cur_tx].addr = cpu_to_le64(bus_to_phys(packet));

    if (cur_tx == (NUM_TX_DESC - 1)) {
        tp->TxDescArray[cur_tx].opts1 =
            cpu_to_le32((DescOwn | RingEnd | FirstFrag | LastFrag) |
                        ((len > ETH_ZLEN) ? len : ETH_ZLEN));
    } else {
        tp->TxDescArray[cur_tx].opts1 =
            cpu_to_le32((DescOwn | FirstFrag | LastFrag) |
                        ((len > ETH_ZLEN) ? len : ETH_ZLEN));
    }

    wmb();

    flush_cache((unsigned long)&tp->TxDescArray[cur_tx],sizeof(struct TxDesc));
    flush_cache((unsigned long)packet,length);
    RTL_W8(TxPoll, NPQ);    /* set polling bit */

    tp->cur_tx = (cur_tx+1) % NUM_TX_DESC;
    to = currticks() + TX_TIMEOUT;
    do {
        invalidate_dcache_range((unsigned long)&tp->TxDescArray[cur_tx], sizeof(struct TxDesc));
        udelay(10);
        /* give the nic a chance to write to the register */
        RTL_W8(TxPoll, NPQ);
    } while ((le32_to_cpu(tp->TxDescArray[cur_tx].opts1) & DescOwn)
             && (currticks() < to));    /* wait */

    if (currticks() >= to) {
#ifdef DEBUG_RTL8168_TX
        puts ("tx timeout/error\n");
        printf ("%s elapsed time : %d\n", __FUNCTION__, currticks()-stime);
#endif
        ret = 0;
    } else {
#ifdef DEBUG_RTL8168_TX
        puts("tx done\n");
        printf ("%s elapsed time : %d\n", __FUNCTION__, currticks()-stime);
#endif
        ret = length;
    }

    /* Delay to make net console (nc) work properly */
    udelay(20);
    return ret;
}

static void rtl8168_hw_set_rx_packet_filter(struct eth_device *dev)
{
    struct rtl8168_private *tp = (struct rtl8168_private *)dev->priv;
    phys_addr_t ioaddr = tp->mmio_addr;
    int rx_mode;
    u32 tmp = 0;

#ifdef DEBUG_RTL8168
    printf ("%s\n", __FUNCTION__);
#endif

    /* IFF_ALLMULTI */
    /* Too many to filter perfectly -- accept all multicasts. */
    rx_mode = RTL_R32(RxConfig);
    rx_mode |= AcceptBroadcast | AcceptMulticast | AcceptMyPhys;

    tp->rtl8168_rx_config = rtl_chip_info[tp->chipset].RCR_Cfg;
    tmp = tp->rtl8168_rx_config | rx_mode | (RTL_R32(RxConfig) & rtl_chip_info[tp->chipset].RxConfigMask);

    RTL_W32(RxConfig, tmp);

    RTL_W32(MAR0 + 0, 0xffffffff);
    RTL_W32(MAR0 + 4, 0xffffffff);
}

static void
rtl8168_enable_rxdvgate(struct eth_device *dev)
{
    struct rtl8168_private *tp = (struct rtl8168_private *)dev->priv;
    phys_addr_t ioaddr = tp->mmio_addr;

    switch (tp->mcfg) {
    case CFG_METHOD_21:
    case CFG_METHOD_22:
    case CFG_METHOD_23:
    case CFG_METHOD_24:
    case CFG_METHOD_25:
    case CFG_METHOD_26:
    case CFG_METHOD_27:
        RTL_W8(0xF2, RTL_R8(0xF2) | BIT_3);
        mdelay(2);
        break;
    }
}

static void
rtl8168_disable_rxdvgate(struct eth_device *dev)
{
    struct rtl8168_private *tp = (struct rtl8168_private *)dev->priv;
    phys_addr_t ioaddr = tp->mmio_addr;

    switch (tp->mcfg) {
    case CFG_METHOD_21:
    case CFG_METHOD_22:
    case CFG_METHOD_23:
    case CFG_METHOD_24:
    case CFG_METHOD_25:
    case CFG_METHOD_26:
    case CFG_METHOD_27:
        RTL_W8(0xF2, RTL_R8(0xF2) & ~BIT_3);
        mdelay(2);
        break;
    }

}

static void
rtl8168_wait_txrx_fifo_empty(struct eth_device *dev)
{
    struct rtl8168_private *tp = (struct rtl8168_private *)dev->priv;
    phys_addr_t ioaddr = tp->mmio_addr;
    int i;

    switch (tp->mcfg) {
    case CFG_METHOD_21:
    case CFG_METHOD_22:
    case CFG_METHOD_23:
    case CFG_METHOD_24:
    case CFG_METHOD_25:
    case CFG_METHOD_26:
    case CFG_METHOD_27:
        for (i = 0; i < 10; i++) {
            udelay(100);
            if (RTL_R32(TxConfig) & BIT_11)
                break;
        }

        for (i = 0; i < 10; i++) {
            udelay(100);
            if ((RTL_R8(MCUCmd_reg) & (Txfifo_empty | Rxfifo_empty)) == (Txfifo_empty | Rxfifo_empty))
                break;

        }
        break;
    }
}

static void
rtl8168_irq_mask_and_ack(phys_addr_t ioaddr)
{
    RTL_W16(IntrMask, 0x0000);
    RTL_W16(IntrStatus, RTL_R16(IntrStatus));
}

static void
rtl8168_nic_reset(struct eth_device *dev)
{
    struct rtl8168_private *tp = (struct rtl8168_private *)dev->priv;
    phys_addr_t ioaddr = tp->mmio_addr;
    int i;

    RTL_W32(RxConfig, (RX_DMA_BURST << RxCfgDMAShift));

    rtl8168_enable_rxdvgate(dev);

    rtl8168_wait_txrx_fifo_empty(dev);

    switch (tp->mcfg) {
    case CFG_METHOD_1:
    case CFG_METHOD_2:
    case CFG_METHOD_3:
        mdelay(10);
        break;
    case CFG_METHOD_4:
    case CFG_METHOD_5:
    case CFG_METHOD_6:
    case CFG_METHOD_7:
    case CFG_METHOD_8:
    case CFG_METHOD_9:
    case CFG_METHOD_10:
    case CFG_METHOD_14:
    case CFG_METHOD_15:
        RTL_W8(ChipCmd, StopReq | CmdRxEnb | CmdTxEnb);
        udelay(100);
        break;
    case CFG_METHOD_11:
    case CFG_METHOD_12:
    case CFG_METHOD_13:
        while (RTL_R8(TxPoll) & NPQ)
            udelay(20);
        break;
    case CFG_METHOD_21:
    case CFG_METHOD_22:
    case CFG_METHOD_23:
    case CFG_METHOD_24:
    case CFG_METHOD_25:
    case CFG_METHOD_26:
    case CFG_METHOD_27:
        mdelay(2);
        break;
    default:
        mdelay(10);
        break;
    }

    /* Soft reset the chip. */
    RTL_W8(ChipCmd, CmdReset);

    /* Check that the chip has finished the reset. */
    for (i = 100; i > 0; i--) {
        udelay(100);
        if ((RTL_R8(ChipCmd) & CmdReset) == 0)
            break;
    }
}

static void
rtl8168_hw_reset(struct eth_device *dev)
{
    struct rtl8168_private *tp = (struct rtl8168_private *)dev->priv;
    phys_addr_t ioaddr = tp->mmio_addr;

    /* Disable interrupts */
    rtl8168_irq_mask_and_ack(ioaddr);

    rtl8168_nic_reset(dev);
}

static void
rtl8168_wait_ll_share_fifo_ready(struct eth_device *dev)
{
    struct rtl8168_private *tp = (struct rtl8168_private *)dev->priv;
    phys_addr_t ioaddr = tp->mmio_addr;
    int i;

    for (i = 0; i < 10; i++) {
        udelay(100);
        if (RTL_R16(0xD2) & BIT_9)
            break;
    }
}

static void
rtl8168_exit_oob(struct eth_device *dev)
{
    struct rtl8168_private *tp = (struct rtl8168_private *)dev->priv;
    phys_addr_t ioaddr = tp->mmio_addr;
    u16 data16;

    rtl8168_nic_reset(dev);

    switch (tp->mcfg) {
    case CFG_METHOD_20:
        rtl8168_wait_ll_share_fifo_ready(dev);

        data16 = mac_ocp_read(tp, 0xD4DE) | BIT_15;
        mac_ocp_write(tp, 0xD4DE, data16);

        rtl8168_wait_ll_share_fifo_ready(dev);
        break;
    case CFG_METHOD_21:
    case CFG_METHOD_22:
    case CFG_METHOD_23:
    case CFG_METHOD_24:
    case CFG_METHOD_25:
    case CFG_METHOD_26:
    case CFG_METHOD_27:
        RTL_W8(MCUCmd_reg, RTL_R8(MCUCmd_reg) & ~Now_is_oob);

        data16 = mac_ocp_read(tp, 0xE8DE) & ~BIT_14;
        mac_ocp_write(tp, 0xE8DE, data16);
        rtl8168_wait_ll_share_fifo_ready(dev);

        data16 = mac_ocp_read(tp, 0xE8DE) | BIT_15;
        mac_ocp_write(tp, 0xE8DE, data16);

        rtl8168_wait_ll_share_fifo_ready(dev);
        break;
    }
}

static int rtl8168_disable_EEE(struct rtl8168_private *tp)
{
    phys_addr_t ioaddr = tp->mmio_addr;
    int ret;
    u16 data;

    MDIO_LOCK;
    ret = 0;
    switch (tp->mcfg) {
    case CFG_METHOD_14:
    case CFG_METHOD_15:
        mdio_write(tp, 0x1F, 0x0007);
        mdio_write(tp, 0x1E, 0x0020);
        data = mdio_read(tp, 0x15) & ~0x0100;
        mdio_write(tp, 0x15, data);
        mdio_write(tp, 0x1F, 0x0006);
        mdio_write(tp, 0x00, 0x5A00);
        mdio_write(tp, 0x1F, 0x0000);
        mdio_write(tp, 0x0D, 0x0007);
        mdio_write(tp, 0x0E, 0x003C);
        mdio_write(tp, 0x0D, 0x4007);
        mdio_write(tp, 0x0E, 0x0000);
        mdio_write(tp, 0x0D, 0x0000);
        mdio_write(tp, 0x1F, 0x0000);
        if (RTL_R8(Config4) & 0x40) {
            data = RTL_R16(CustomLED);
            mdio_write(tp, 0x1F, 0x0005);
            mdio_write(tp, 0x05, 0x8B82);
            data = mdio_read(tp, 0x06) & ~0x0010;
            mdio_write(tp, 0x05, 0x8B82);
            mdio_write(tp, 0x06, data);
            mdio_write(tp, 0x1F, 0x0000);
        }
        break;

    case CFG_METHOD_16:
    case CFG_METHOD_17:
        data = rtl8168_eri_read(ioaddr,0x1B0 ,4,ERIAR_ExGMAC)& ~0x0003;
        rtl8168_eri_write(ioaddr, 0x1B0, 4, data, ERIAR_ExGMAC);
        mdio_write(tp, 0x1F, 0x0005);
        mdio_write(tp, 0x05, 0x8B85);
        data = mdio_read(tp, 0x06) & ~0x2000;
        mdio_write(tp, 0x06, data);
        mdio_write(tp, 0x1F, 0x0004);
        mdio_write(tp, 0x1F, 0x0007);
        mdio_write(tp, 0x1E, 0x0020);
        data = mdio_read(tp, 0x15) & ~0x0100;
        mdio_write(tp,0x15 , data);
        mdio_write(tp, 0x1F, 0x0002);
        mdio_write(tp, 0x1F, 0x0000);
        mdio_write(tp, 0x0D, 0x0007);
        mdio_write(tp, 0x0E, 0x003C);
        mdio_write(tp, 0x0D, 0x4007);
        mdio_write(tp, 0x0E, 0x0000);
        mdio_write(tp, 0x0D, 0x0000);
        mdio_write(tp, 0x1F, 0x0000);
        break;

    case CFG_METHOD_18:
    case CFG_METHOD_19:
    case CFG_METHOD_20:
        data = rtl8168_eri_read(ioaddr,0x1B0 ,4,ERIAR_ExGMAC);
        data &= ~(BIT_1 | BIT_0);
        rtl8168_eri_write(ioaddr, 0x1B0, 4, data, ERIAR_ExGMAC);
        mdio_write(tp, 0x1F, 0x0005);
        mdio_write(tp, 0x05, 0x8B85);
        data = mdio_read(tp, 0x06);
        data &= ~BIT_13;
        mdio_write(tp, 0x06, data);
        mdio_write(tp, 0x1F, 0x0007);
        mdio_write(tp, 0x1e, 0x0020);
        data = mdio_read(tp, 0x15);
        data &= ~BIT_8;
        mdio_write(tp, 0x15, data);
        mdio_write(tp, 0x1F, 0x0000);
        mdio_write(tp, 0x0D, 0x0007);
        mdio_write(tp, 0x0E, 0x003C);
        mdio_write(tp, 0x0D, 0x4007);
        mdio_write(tp, 0x0E, 0x0000);
        mdio_write(tp, 0x0D, 0x0000);
        mdio_write(tp, 0x1F, 0x0000);
        break;

    case CFG_METHOD_21:
    case CFG_METHOD_22:
    case CFG_METHOD_23:
    case CFG_METHOD_24:
    case CFG_METHOD_25:
    case CFG_METHOD_26:
    case CFG_METHOD_27:
        data = rtl8168_eri_read(ioaddr, 0x1B0, 4, ERIAR_ExGMAC);
        data &= ~(BIT_1 | BIT_0);
        rtl8168_eri_write(ioaddr, 0x1B0, 4, data, ERIAR_ExGMAC);
        mdio_write(tp, 0x1F, 0x0A43);
        data = mdio_read(tp, 0x11);
        mdio_write(tp, 0x11, data & ~BIT_4);
        mdio_write(tp, 0x1F, 0x0A5D);
        mdio_write(tp, 0x10, 0x0000);
        mdio_write(tp, 0x1F, 0x0000);
        break;

    default:
//      dev_printk(KERN_DEBUG, &tp->pci_dev->dev, "Not Support EEE\n");
        ret = -EOPNOTSUPP;
        break;
    }

    /*Advanced EEE*/
    switch (tp->mcfg) {
    case CFG_METHOD_25:
        rtl8168_eri_write(ioaddr, 0x1EA, 1, 0x00, ERIAR_ExGMAC);

        mdio_write(tp, 0x1F, 0x0A42);
        data = mdio_read(tp, 0x16);
        data &= ~(BIT_1);
        mdio_write(tp, 0x16, data);
        mdio_write(tp, 0x1F, 0x0000);
        break;
    case CFG_METHOD_26:
        data = mac_ocp_read(tp, 0xE052);
        data &= ~(BIT_0);
        mac_ocp_write(tp, 0xE052, data);

        mdio_write(tp, 0x1F, 0x0A42);
        data = mdio_read(tp, 0x16);
        data &= ~(BIT_1);
        mdio_write(tp, 0x16, data);
        mdio_write(tp, 0x1F, 0x0000);
        break;
    case CFG_METHOD_27:
        data = mac_ocp_read(tp, 0xE052);
        data &= ~(BIT_0);
        mac_ocp_write(tp, 0xE052, data);
        break;
    }

    MDIO_UNLOCK;
    return ret;
}

static void
rtl8168_rx_desc_offset0_init(struct rtl8168_private *tp, int own)
{
    int i = 0;
    int ownbit = 0;

    if (own)
        ownbit = DescOwn;

    for (i = 0; i < NUM_RX_DESC; i++) {
        if (i == (NUM_RX_DESC - 1))
            tp->RxDescArray[i].opts1 = cpu_to_le32((ownbit | RingEnd) | (unsigned long)tp->rx_buf_sz);
        else
            tp->RxDescArray[i].opts1 = cpu_to_le32(ownbit | (unsigned long)tp->rx_buf_sz);

        flush_cache((unsigned long)&tp->RxDescArray[i],sizeof(struct RxDesc));
    }
}

static void
rtl8168_print_mac_version(struct rtl8168_private *tp)
{
    int i;
    for (i = ARRAY_SIZE(rtl_chip_info) - 1; i >= 0; i--) {
        if (tp->mcfg == rtl_chip_info[i].mcfg) {
            printf("Realtek PCIe GBE Family Controller mcfg = %04d\n",
                   rtl_chip_info[i].mcfg);
            return;
        }
    }

    printf("mac_version == Unknown\n");
}

static u8 rtl8168_efuse_read(struct rtl8168_private *tp, u16 reg)
{
    phys_addr_t ioaddr = tp->mmio_addr;
    u8 efuse_data;
    u32 temp;
    int cnt;

    if (tp->efuse == EFUSE_NOT_SUPPORT)
        return EFUSE_READ_FAIL;

    temp = EFUSE_READ | ((reg & EFUSE_Reg_Mask) << EFUSE_Reg_Shift);
    RTL_W32(EFUSEAR, temp);

    do {
        udelay(100);
        temp = RTL_R32(EFUSEAR);
        cnt++;
    } while (!(temp & EFUSE_READ_OK) && (temp < EFUSE_Check_Cnt));

    if (temp == EFUSE_Check_Cnt)
        efuse_data = EFUSE_READ_FAIL;
    else
        efuse_data = (u8)(RTL_R32(EFUSEAR) & EFUSE_Data_Mask);

    return efuse_data;
}

static void
rtl8168_tally_counter_addr_fill(struct rtl8168_private *tp)
{
    phys_addr_t ioaddr = tp->mmio_addr;
    unsigned long tally;

    tally = ((unsigned long)dummy + ALIGN_64) & ~ALIGN_64;

    if (!tally)
        return;

    RTL_W32(CounterAddrLow, cpu_to_le32(bus_to_phys(tally)));
    RTL_W32(CounterAddrHigh, 0);
}

static void
rtl8168_tally_counter_clear(struct rtl8168_private *tp)
{
    phys_addr_t ioaddr = tp->mmio_addr;
    unsigned long tally;

    if (tp->mcfg == CFG_METHOD_1 || tp->mcfg == CFG_METHOD_2 ||
        tp->mcfg == CFG_METHOD_3 )
        return;

    tally = ((unsigned long)dummy + ALIGN_64) & ~ALIGN_64;

    if (!tally)
        return;

    tally |= BIT_0;
    RTL_W32(CounterAddrHigh, 0);
    RTL_W32(CounterAddrLow, cpu_to_le32(bus_to_phys(tally)));
}

static void
rtl8168_desc_addr_fill(struct rtl8168_private *tp)
{
    phys_addr_t ioaddr = tp->mmio_addr;

    RTL_W32(TxDescStartAddrLow, (unsigned int)(uintptr_t)bus_to_phys(tp->TxDescArray));
    RTL_W32(TxDescStartAddrHigh, (unsigned long)0);
    RTL_W32(RxDescAddrLow, (unsigned int)(uintptr_t)bus_to_phys(tp->RxDescArray));
    RTL_W32(RxDescAddrHigh, (unsigned long)0);
}

static void rtl8168_hw_start(struct rtl8168_private *tp)
{
    phys_addr_t ioaddr = tp->mmio_addr;
    struct eth_device *dev = tp->dev;
    u16 mac_ocp_data;
    u32 csi_tmp;

#ifdef DEBUG_RTL8168
    int stime = currticks();
    printf ("%s\n", __FUNCTION__);
#endif

    RTL_W32(RxConfig, (RX_DMA_BURST << RxCfgDMAShift));

    rtl8168_hw_reset(dev);

    rtl8168_rx_desc_offset0_init(tp, 1);

    RTL_W8(Cfg9346, Cfg9346_Unlock);

    switch (tp->mcfg) {
    case CFG_METHOD_14:
    case CFG_METHOD_15:
    case CFG_METHOD_16:
    case CFG_METHOD_17:
    case CFG_METHOD_18:
    case CFG_METHOD_19:
    case CFG_METHOD_20:
    case CFG_METHOD_21:
    case CFG_METHOD_22:
    case CFG_METHOD_23:
    case CFG_METHOD_24:
    case CFG_METHOD_25:
    case CFG_METHOD_26:
    case CFG_METHOD_27:
        RTL_W8(0xF1, RTL_R8(0xF1) & ~BIT_7);
        RTL_W8(Config2, RTL_R8(Config2) & ~BIT_7);
        RTL_W8(Config5, RTL_R8(Config5) & ~BIT_0);
        break;
    }
    RTL_W8(MTPS, Reserved1_data);

    rtl8168_tally_counter_addr_fill(tp);

    rtl8168_desc_addr_fill(tp);

    /* Set DMA burst size and Interframe Gap Time */
    if (tp->mcfg == CFG_METHOD_1)
        RTL_W32(TxConfig, (TX_DMA_BURST_512 << TxDMAShift) |
                (InterFrameGap << TxInterFrameGapShift));
    else
        RTL_W32(TxConfig, (TX_DMA_BURST_128 << TxDMAShift) |
                (InterFrameGap << TxInterFrameGapShift));

    tp->cp_cmd = (RTL_R16(CPlusCmd) | PktCntrDisable);

    if (tp->mcfg == CFG_METHOD_4) {
        //set_offset70F(tp, 0x27);

        RTL_W8(DBG_reg, (0x0E << 4) | Fix_Nak_1 | Fix_Nak_2);

        RTL_W8(Config3, RTL_R8(Config3) & ~Beacon_en);

        RTL_W16(CPlusCmd, RTL_R16(CPlusCmd) &
                ~(EnableBist | Macdbgo_oe | Force_halfdup | Force_rxflow_en | Force_txflow_en |
                  Cxpl_dbg_sel | ASF | PktCntrDisable | Macdbgo_sel));

        RTL_W8(Config3, RTL_R8(Config3) & ~Jumbo_En0);
        RTL_W8(Config4, RTL_R8(Config4) & ~Jumbo_En1);

        //set_offset79(tp, 0x50);
    } else if (tp->mcfg == CFG_METHOD_5) {

        //set_offset70F(tp, 0x27);

        RTL_W8(Config3, RTL_R8(Config3) & ~Beacon_en);

        RTL_W16(CPlusCmd, RTL_R16(CPlusCmd) &
                ~(EnableBist | Macdbgo_oe | Force_halfdup | Force_rxflow_en | Force_txflow_en |
                  Cxpl_dbg_sel | ASF | PktCntrDisable | Macdbgo_sel));

        RTL_W8(Config3, RTL_R8(Config3) & ~Jumbo_En0);
        RTL_W8(Config4, RTL_R8(Config4) & ~Jumbo_En1);

        //set_offset79(tp, 0x50);
    } else if (tp->mcfg == CFG_METHOD_6) {
        //set_offset70F(tp, 0x27);

        RTL_W8(Config3, RTL_R8(Config3) & ~Beacon_en);

        RTL_W16(CPlusCmd, RTL_R16(CPlusCmd) &
                ~(EnableBist | Macdbgo_oe | Force_halfdup | Force_rxflow_en | Force_txflow_en |
                  Cxpl_dbg_sel | ASF | PktCntrDisable | Macdbgo_sel));

        RTL_W8(Config3, RTL_R8(Config3) & ~Jumbo_En0);
        RTL_W8(Config4, RTL_R8(Config4) & ~Jumbo_En1);

        //set_offset79(tp, 0x50);
    } else if (tp->mcfg == CFG_METHOD_7) {
        //set_offset70F(tp, 0x27);

        rtl8168_eri_write(ioaddr, 0x1EC, 1, 0x07, ERIAR_ASF);

        RTL_W16(CPlusCmd, RTL_R16(CPlusCmd) &
                ~(EnableBist | Macdbgo_oe | Force_halfdup | Force_rxflow_en | Force_txflow_en |
                  Cxpl_dbg_sel | ASF | PktCntrDisable | Macdbgo_sel));

        RTL_W8(Config3, RTL_R8(Config3) & ~Beacon_en);

        //set_offset79(tp, 0x50);
    } else if (tp->mcfg == CFG_METHOD_8) {

        //set_offset70F(tp, 0x27);

        rtl8168_eri_write(ioaddr, 0x1EC, 1, 0x07, ERIAR_ASF);

        RTL_W16(CPlusCmd, RTL_R16(CPlusCmd) &
                ~(EnableBist | Macdbgo_oe | Force_halfdup | Force_rxflow_en | Force_txflow_en |
                  Cxpl_dbg_sel | ASF | PktCntrDisable | Macdbgo_sel));

        RTL_W8(Config3, RTL_R8(Config3) & ~Beacon_en);

        RTL_W8(0xD1, 0x20);

        RTL_W8(Config3, RTL_R8(Config3) & ~Jumbo_En0);
        RTL_W8(Config4, RTL_R8(Config4) & ~Jumbo_En1);

        //set_offset79(tp, 0x50);

    } else if (tp->mcfg == CFG_METHOD_9) {
        //set_offset70F(tp, 0x27);

        RTL_W8(Config3, RTL_R8(Config3) & ~BIT_4);
        RTL_W8(DBG_reg, RTL_R8(DBG_reg) | BIT_7 | BIT_1);

        RTL_W8(Config3, RTL_R8(Config3) & ~Jumbo_En0);
        RTL_W8(Config4, RTL_R8(Config4) & ~Jumbo_En1);

        //set_offset79(tp, 0x50);

        RTL_W8(TDFNR, 0x8);
    } else if (tp->mcfg == CFG_METHOD_10) {
        //set_offset70F(tp, 0x27);

        RTL_W8(DBG_reg, RTL_R8(DBG_reg) | BIT_7 | BIT_1);

        RTL_W8(Config3, RTL_R8(Config3) & ~Jumbo_En0);
        RTL_W8(Config4, RTL_R8(Config4) & ~Jumbo_En1);

        //set_offset79(tp, 0x50);

        RTL_W8(TDFNR, 0x8);

        RTL_W8(Config1, RTL_R8(Config1) | 0x10);
    } else if (tp->mcfg == CFG_METHOD_11 || tp->mcfg == CFG_METHOD_13) {
        //set_offset70F(tp, 0x17);
        //set_offset79(tp, 0x50);

        RTL_W8(Config3, RTL_R8(Config3) & ~Jumbo_En0);

        RTL_W8(Config1, RTL_R8(Config1) | 0x10);

    } else if (tp->mcfg == CFG_METHOD_12) {
        //set_offset70F(tp, 0x17);
        //set_offset79(tp, 0x50);
        RTL_W8(Config3, RTL_R8(Config3) & ~Jumbo_En0);

        RTL_W8(Config1, RTL_R8(Config1) | 0x10);

    } else if (tp->mcfg == CFG_METHOD_14 || tp->mcfg == CFG_METHOD_15) {

        //set_offset70F(tp, 0x27);
        //set_offset79(tp, 0x50);

        tp->cp_cmd &= 0x2063;

        RTL_W8(Config3, RTL_R8(Config3) & ~Jumbo_En0);
        RTL_W8(Config4, RTL_R8(Config4) & ~0x01);

//      RTL_W8(0xF2, RTL_R8(0xF2) | BIT_0);
//      RTL_W32(CounterAddrLow, RTL_R32(CounterAddrLow) | BIT_0);

        RTL_W8(0xF3, RTL_R8(0xF3) | BIT_5);
        RTL_W8(0xF3, RTL_R8(0xF3) & ~BIT_5);

//      RTL_W8(0xD3, RTL_R8(0xD3) | BIT_3 | BIT_2);

        RTL_W8(0xD0, RTL_R8(0xD0) | BIT_7 | BIT_6);

        RTL_W8(0xD1, RTL_R8(0xD1) | BIT_2 | BIT_3);

        RTL_W8(0xF1, RTL_R8(0xF1) | BIT_6 | BIT_5 | BIT_4 | BIT_2 | BIT_1);

        RTL_W8(TDFNR, 0x8);

        RTL_W8(Config5, RTL_R8(Config5) & ~BIT_3);

        RTL_W8(Config3, RTL_R8(Config3) & ~Beacon_en);
    } else if (tp->mcfg == CFG_METHOD_16 || tp->mcfg == CFG_METHOD_17) {
        //set_offset70F(tp, 0x17);
        //set_offset79(tp, 0x50);

        csi_tmp = rtl8168_eri_read(ioaddr, 0xD5, 1, ERIAR_ExGMAC) | BIT_3 | BIT_2;
        rtl8168_eri_write(ioaddr, 0xD5, 1, csi_tmp, ERIAR_ExGMAC);
        rtl8168_eri_write(ioaddr, 0xC0, 2, 0x0000, ERIAR_ExGMAC);
        rtl8168_eri_write(ioaddr, 0xB8, 4, 0x00000000, ERIAR_ExGMAC);
        rtl8168_eri_write(ioaddr, 0xC8, 4, 0x00100002, ERIAR_ExGMAC);
        rtl8168_eri_write(ioaddr, 0xE8, 4, 0x00100006, ERIAR_ExGMAC);
        //csi_tmp = rtl8168_eri_read(ioaddr, 0x1D0, 4, ERIAR_ExGMAC);
        //csi_tmp |= BIT_1;
        //rtl8168_eri_write(ioaddr, 0x1D0, 1, csi_tmp, ERIAR_ExGMAC);

        csi_tmp = rtl8168_eri_read(ioaddr, 0xDC, 1, ERIAR_ExGMAC);
        csi_tmp &= ~BIT_0;
        rtl8168_eri_write(ioaddr, 0xDC, 1, csi_tmp, ERIAR_ExGMAC);
        csi_tmp |= BIT_0;
        rtl8168_eri_write(ioaddr, 0xDC, 1, csi_tmp, ERIAR_ExGMAC);

        RTL_W32(TxConfig, RTL_R32(TxConfig) | BIT_7);
        RTL_W8(0xD3, RTL_R8(0xD3) & ~BIT_7);
        RTL_W8(0x1B, RTL_R8(0x1B) & ~0x07);

        if (tp->mcfg == CFG_METHOD_16) {
            RTL_W32(0xB0, 0xEE480010);
            RTL_W8(0x1A, RTL_R8(0x1A) & ~(BIT_2|BIT_3));
            rtl8168_eri_write(ioaddr, 0x1DC, 1, 0x64, ERIAR_ExGMAC);
        } else {
            csi_tmp = rtl8168_eri_read(ioaddr, 0x1B0, 4, ERIAR_ExGMAC);
            csi_tmp |= BIT_4;
            rtl8168_eri_write(ioaddr, 0x1B0, 1, csi_tmp, ERIAR_ExGMAC);
            rtl8168_eri_write(ioaddr, 0xCC, 4, 0x00000050, ERIAR_ExGMAC);
            rtl8168_eri_write(ioaddr, 0xD0, 4, 0x07ff0060, ERIAR_ExGMAC);
        }

        RTL_W8(TDFNR, 0x8);

        RTL_W8(Config2, RTL_R8(Config2) & ~PMSTS_En);

        RTL_W8(0xD0, RTL_R8(0xD0) | BIT_6);
        RTL_W8(0xF2, RTL_R8(0xF2) | BIT_6);

        tp->cp_cmd &= 0x2063;

    } else if (tp->mcfg == CFG_METHOD_18 || tp->mcfg == CFG_METHOD_19) {
        //set_offset70F(tp, 0x17);
        //set_offset79(tp, 0x50);

        rtl8168_eri_write(ioaddr, 0xC8, 4, 0x00100002, ERIAR_ExGMAC);
        rtl8168_eri_write(ioaddr, 0xE8, 4, 0x00100006, ERIAR_ExGMAC);
        RTL_W32(TxConfig, RTL_R32(TxConfig) | BIT_7);
        RTL_W8(0xD3, RTL_R8(0xD3) & ~BIT_7);
        csi_tmp = rtl8168_eri_read(ioaddr, 0xDC, 1, ERIAR_ExGMAC);
        csi_tmp &= ~BIT_0;
        rtl8168_eri_write(ioaddr, 0xDC, 1, csi_tmp, ERIAR_ExGMAC);
        csi_tmp |= BIT_0;
        rtl8168_eri_write(ioaddr, 0xDC, 1, csi_tmp, ERIAR_ExGMAC);

        tp->cp_cmd &= 0x2063;

        RTL_W8(TDFNR, 0x8);

        RTL_W8(0xD0, RTL_R8(0xD0) | BIT_6);
        RTL_W8(0xF2, RTL_R8(0xF2) | BIT_6);

        rtl8168_eri_write(ioaddr, 0xC0, 2, 0x0000, ERIAR_ExGMAC);
        rtl8168_eri_write(ioaddr, 0xB8, 4, 0x00000000, ERIAR_ExGMAC);
        csi_tmp = rtl8168_eri_read(ioaddr, 0xD5, 1, ERIAR_ExGMAC);
        csi_tmp |= BIT_3 | BIT_2;
        rtl8168_eri_write(ioaddr, 0xD5, 1, csi_tmp, ERIAR_ExGMAC);
        RTL_W8(0x1B,RTL_R8(0x1B) & ~0x07);

        csi_tmp = rtl8168_eri_read(ioaddr, 0x1B0, 1, ERIAR_ExGMAC);
        csi_tmp |= BIT_4;
        rtl8168_eri_write(ioaddr, 0x1B0, 1, csi_tmp, ERIAR_ExGMAC);
        //csi_tmp = rtl8168_eri_read(ioaddr, 0x1d0, 1, ERIAR_ExGMAC);
        //csi_tmp |= BIT_4 | BIT_1;
        //rtl8168_eri_write(ioaddr, 0x1d0, 1, csi_tmp, ERIAR_ExGMAC);
        rtl8168_eri_write(ioaddr, 0xCC, 4, 0x00000050, ERIAR_ExGMAC);
        rtl8168_eri_write(ioaddr, 0xd0, 4, 0x00000060, ERIAR_ExGMAC);
    } else if (tp->mcfg == CFG_METHOD_20) {
        //set_offset70F(tp, 0x17);
        //set_offset79(tp, 0x50);

        rtl8168_eri_write(ioaddr, 0xC8, 4, 0x00100002, ERIAR_ExGMAC);
        rtl8168_eri_write(ioaddr, 0xE8, 4, 0x00100006, ERIAR_ExGMAC);
        RTL_W32(TxConfig, RTL_R32(TxConfig) | BIT_7);
        RTL_W8(0xD3, RTL_R8(0xD3) & ~BIT_7);
        csi_tmp = rtl8168_eri_read(ioaddr, 0xDC, 1, ERIAR_ExGMAC);
        csi_tmp &= ~BIT_0;
        rtl8168_eri_write(ioaddr, 0xDC, 1, csi_tmp, ERIAR_ExGMAC);
        csi_tmp |= BIT_0;
        rtl8168_eri_write(ioaddr, 0xDC, 1, csi_tmp, ERIAR_ExGMAC);

        tp->cp_cmd &= 0x2063;

        RTL_W8(TDFNR, 0x8);

        RTL_W8(0xD0, RTL_R8(0xD0) | BIT_6);
        RTL_W8(0xF2, RTL_R8(0xF2) | BIT_6);
        rtl8168_eri_write(ioaddr, 0xC0, 2, 0x0000, ERIAR_ExGMAC);
        rtl8168_eri_write(ioaddr, 0xB8, 4, 0x00000000, ERIAR_ExGMAC);
        csi_tmp = rtl8168_eri_read(ioaddr, 0xD5, 1, ERIAR_ExGMAC);
        csi_tmp |= BIT_3 | BIT_2;
        rtl8168_eri_write(ioaddr, 0xD5, 1, csi_tmp, ERIAR_ExGMAC);

        csi_tmp = rtl8168_eri_read(ioaddr, 0x1B0, 1, ERIAR_ExGMAC);
        csi_tmp |= BIT_4;
        rtl8168_eri_write(ioaddr, 0x1B0, 1, csi_tmp, ERIAR_ExGMAC);
        //csi_tmp = rtl8168_eri_read(ioaddr, 0x1d0, 1, ERIAR_ExGMAC);
        //csi_tmp |= BIT_4 | BIT_1;
        //rtl8168_eri_write(ioaddr, 0x1d0, 1, csi_tmp, ERIAR_ExGMAC);
        rtl8168_eri_write(ioaddr, 0xCC, 4, 0x00000050, ERIAR_ExGMAC);
        rtl8168_eri_write(ioaddr, 0xd0, 4, 0x00000060, ERIAR_ExGMAC);
    } else if (tp->mcfg == CFG_METHOD_21 || tp->mcfg == CFG_METHOD_22 ||
               tp->mcfg == CFG_METHOD_24 || tp->mcfg == CFG_METHOD_25 ||
               tp->mcfg == CFG_METHOD_26) {
        //set_offset70F(tp, 0x17);
        //set_offset79(tp, 0x50);

        // LED setting
        //RTL_W32(CustomLED,0x000670ca);
    /*  if(GET_IC_VERSION()==0x00000000)
        {
            // gphy patch from Riri     add by yukuen
            // disable green
            mdio_write(tp, 0x1f, 0x0A43);
            mdio_write(tp, 0x1b, 0x8011);
            mdio_write(tp, 0x1c, 0x1737);   //disable green

            mdio_write(tp, 0x1f, 0x0BCC);
            mdio_write(tp, 0x11, 0x4444);     //write abiq /ldvbias

            // R/ RC auto k
            mdio_write(tp, 0x1f, 0x0A43);
            mdio_write(tp, 0x1b, 0x8013);
            mdio_write(tp, 0x1c, 0x0F08);   //default ff08  disable auto k RC/R

            mdio_write(tp, 0x1f, 0x0BCE);   //force tapbin = 4
            mdio_write(tp, 0x10, 0x4444);

            mdio_write(tp, 0x1f, 0x0BCD);
            mdio_write(tp, 0x17, 0x8888);       //tx rc
            mdio_write(tp, 0x16, 0x9999);       //rx rc

            // increase sd thd
            mdio_write(tp, 0x1f, 0x0A43);
            mdio_write(tp, 0x1b, 0x8101);
            mdio_write(tp, 0x1c, 0x3E00);   //master sd  : 0x1e00

            mdio_write(tp, 0x1f, 0x0A43);
            mdio_write(tp, 0x1b, 0x80E2);
            mdio_write(tp, 0x1c, 0x3E00);   //default sd  : 0x0e00

            mdio_write(tp, 0x1f, 0x0A43);
            mdio_write(tp, 0x1b, 0x8120);
            mdio_write(tp, 0x1c, 0x3E00);   //slave sd  : 0x0e00
        }
        else  //1195B
      {
        unsigned int gphy_val;
        unsigned int WaitCnt;

        //1195B MAC
        RTL_W32(OCPDR,0xFE140000);
            RTL_W32(OCPDR,0xFE150000);
            RTL_W32(OCPDR,0xFE160000);
            RTL_W32(OCPDR,0xFE170000);
            RTL_W32(OCPDR,0xFE180000);
            RTL_W32(OCPDR,0xFE190000);
            RTL_W32(OCPDR,0xFE1A0000);
            RTL_W32(OCPDR,0xFE1B0000);
            mdelay(3);
            RTL_W32(OCPDR,0xFE130000);

            RTL_W32(OCPDR,0xFC00E008);
            RTL_W32(OCPDR,0xFC01E051);
            RTL_W32(OCPDR,0xFC02E059);
            RTL_W32(OCPDR,0xFC03E05B);
            RTL_W32(OCPDR,0xFC04E05D);
            RTL_W32(OCPDR,0xFC05E05F);
            RTL_W32(OCPDR,0xFC06E061);
            RTL_W32(OCPDR,0xFC07E063);
            RTL_W32(OCPDR,0xFC08C422);
            RTL_W32(OCPDR,0xFC097380);
            RTL_W32(OCPDR,0xFC0A49B7);
            RTL_W32(OCPDR,0xFC0BF003);
            RTL_W32(OCPDR,0xFC0C1D02);
            RTL_W32(OCPDR,0xFC0D8D80);
            RTL_W32(OCPDR,0xFC0EC51D);
            RTL_W32(OCPDR,0xFC0F73A0);
            RTL_W32(OCPDR,0xFC101300);
            RTL_W32(OCPDR,0xFC11F104);
            RTL_W32(OCPDR,0xFC1273A2);
            RTL_W32(OCPDR,0xFC131300);
            RTL_W32(OCPDR,0xFC14F010);
            RTL_W32(OCPDR,0xFC15C517);
            RTL_W32(OCPDR,0xFC1676A0);
            RTL_W32(OCPDR,0xFC1774A2);
            RTL_W32(OCPDR,0xFC180601);
            RTL_W32(OCPDR,0xFC193720);
            RTL_W32(OCPDR,0xFC1A9EA0);
            RTL_W32(OCPDR,0xFC1B9CA2);
            RTL_W32(OCPDR,0xFC1CC50F);
            RTL_W32(OCPDR,0xFC1D73A2);
            RTL_W32(OCPDR,0xFC1E4023);
            RTL_W32(OCPDR,0xFC1FF813);
            RTL_W32(OCPDR,0xFC20F304);
            RTL_W32(OCPDR,0xFC2173A0);
            RTL_W32(OCPDR,0xFC224033);
            RTL_W32(OCPDR,0xFC23F80F);
            RTL_W32(OCPDR,0xFC24C206);
            RTL_W32(OCPDR,0xFC257340);
            RTL_W32(OCPDR,0xFC2649B7);
            RTL_W32(OCPDR,0xFC27F013);
            RTL_W32(OCPDR,0xFC28C207);
            RTL_W32(OCPDR,0xFC29BA00);
            RTL_W32(OCPDR,0xFC2AC0BC);
            RTL_W32(OCPDR,0xFC2BD2C8);
            RTL_W32(OCPDR,0xFC2CD2CC);
            RTL_W32(OCPDR,0xFC2DC0C4);
            RTL_W32(OCPDR,0xFC2ED2E4);
            RTL_W32(OCPDR,0xFC2F100A);
            RTL_W32(OCPDR,0xFC30104C);
            RTL_W32(OCPDR,0xFC310C7E);
            RTL_W32(OCPDR,0xFC321D02);
            RTL_W32(OCPDR,0xFC33C6F7);
            RTL_W32(OCPDR,0xFC348DC0);
            RTL_W32(OCPDR,0xFC351C01);
            RTL_W32(OCPDR,0xFC36C5F7);
            RTL_W32(OCPDR,0xFC378CA1);
            RTL_W32(OCPDR,0xFC38C6F8);
            RTL_W32(OCPDR,0xFC39BE00);
            RTL_W32(OCPDR,0xFC3AC5F4);
            RTL_W32(OCPDR,0xFC3B74A0);
            RTL_W32(OCPDR,0xFC3C49C0);
            RTL_W32(OCPDR,0xFC3DF010);
            RTL_W32(OCPDR,0xFC3E74A2);
            RTL_W32(OCPDR,0xFC3F76A4);
            RTL_W32(OCPDR,0xFC404034);
            RTL_W32(OCPDR,0xFC41F804);
            RTL_W32(OCPDR,0xFC420601);
            RTL_W32(OCPDR,0xFC439EA4);
            RTL_W32(OCPDR,0xFC44E009);
            RTL_W32(OCPDR,0xFC451D02);
            RTL_W32(OCPDR,0xFC46C4E4);
            RTL_W32(OCPDR,0xFC478D80);
            RTL_W32(OCPDR,0xFC48C5E5);
            RTL_W32(OCPDR,0xFC4964A1);
            RTL_W32(OCPDR,0xFC4A4845);
            RTL_W32(OCPDR,0xFC4B8CA1);
            RTL_W32(OCPDR,0xFC4CE7EC);
            RTL_W32(OCPDR,0xFC4D1C20);
            RTL_W32(OCPDR,0xFC4EC5DC);
            RTL_W32(OCPDR,0xFC4F8CA1);
            RTL_W32(OCPDR,0xFC50C2E1);
            RTL_W32(OCPDR,0xFC51BA00);
            RTL_W32(OCPDR,0xFC521D02);
            RTL_W32(OCPDR,0xFC53C606);
            RTL_W32(OCPDR,0xFC548DC0);
            RTL_W32(OCPDR,0xFC551D20);
            RTL_W32(OCPDR,0xFC568DC0);
            RTL_W32(OCPDR,0xFC57C603);
            RTL_W32(OCPDR,0xFC58BE00);
            RTL_W32(OCPDR,0xFC59C0BC);
            RTL_W32(OCPDR,0xFC5A0E22);
            RTL_W32(OCPDR,0xFC5BC102);
            RTL_W32(OCPDR,0xFC5CB900);
            RTL_W32(OCPDR,0xFC5D02A2);
            RTL_W32(OCPDR,0xFC5EC602);
            RTL_W32(OCPDR,0xFC5FBE00);
            RTL_W32(OCPDR,0xFC600000);
            RTL_W32(OCPDR,0xFC61C602);
            RTL_W32(OCPDR,0xFC62BE00);
            RTL_W32(OCPDR,0xFC630000);
            RTL_W32(OCPDR,0xFC64C602);
            RTL_W32(OCPDR,0xFC65BE00);
            RTL_W32(OCPDR,0xFC660000);
            RTL_W32(OCPDR,0xFC67C602);
            RTL_W32(OCPDR,0xFC68BE00);
            RTL_W32(OCPDR,0xFC690000);
            RTL_W32(OCPDR,0xFC6AC602);
            RTL_W32(OCPDR,0xFC6BBE00);
            RTL_W32(OCPDR,0xFC6C0000);

            RTL_W32(OCPDR,0xFE138000);
            RTL_W32(OCPDR,0xFE140FD1);
            RTL_W32(OCPDR,0xFE150D21);
            RTL_W32(OCPDR,0xFE16029D);

        //1195B GPHY
        mdio_write(tp, 0x1f, 0x0A43);
        mdio_write(tp, 0x13, 0x801E);
        gphy_val = mdio_read(tp, 0x14);
        if(gphy_val!=NIC_RAMCODE_VERSION)
        {
                    // Patch request & polling patch_rdy for 100ms
                    mdio_write(tp,0x1f, 0x0B82);
                    gphy_val = mdio_read(tp, 0x10);
                    gphy_val |= BIT_4; // page 0x0B82, Reg 0x10, Bit[4]=1
                    mdio_write(tp,0x10, gphy_val); // patch request

                    //Polling GPHY Page 0x0B80, Reg 0x10, Bit[6]==1 to check if it is ready to patch, a max timer 100ms is adopted
                    mdio_write(tp,0x1f, 0x0B80);
                    WaitCnt = 0;
                    do
                    {
                      gphy_val = mdio_read(tp, 0x10);
                      gphy_val &= 0x0040;
                      udelay(50);
                      udelay(50);
                      WaitCnt++;
                    }while(gphy_val != 0x0040 && WaitCnt <1000);


                    // Set patch_key & patch_lock
                    mdio_write(tp,0x1f, 0x0A43);
                    mdio_write(tp,0x13, 0x8146);
                    mdio_write(tp,0x14, 0x2900); // set patch_key
                    mdio_write(tp,0x13, 0xB82E);
                    mdio_write(tp,0x14, 0x0001);// set patch_lock


                    // UC patch Start
                    mdio_write(tp, 0x1f, 0x0a43);
                    mdio_write(tp, 0x1b, 0x83db);
                    mdio_write(tp, 0x1c, 0xaf83);
                    mdio_write(tp, 0x1c, 0xe7af);
                    mdio_write(tp, 0x1c, 0x83f6);
                    mdio_write(tp, 0x1c, 0xaf83);
                    mdio_write(tp, 0x1c, 0xf6af);
                    mdio_write(tp, 0x1c, 0x83f6);
                    mdio_write(tp, 0x1c, 0x07d9);
                    mdio_write(tp, 0x1c, 0x0d11);
                    mdio_write(tp, 0x1c, 0x07bf);
                    mdio_write(tp, 0x1c, 0x83f6);
                    mdio_write(tp, 0x1c, 0x024a);
                    mdio_write(tp, 0x1c, 0x4b07);
                    mdio_write(tp, 0x1c, 0xaf1c);
                    mdio_write(tp, 0x1c, 0xf9fe);
                    mdio_write(tp, 0x1c, 0xbc0a);
                    mdio_write(tp, 0x1b, 0x80b9);
                    mdio_write(tp, 0x1c, 0x0700);
                    mdio_write(tp, 0x1b, 0xb818);
                    mdio_write(tp, 0x1c, 0x1cf8);
                    mdio_write(tp, 0x1b, 0xb81a);
                    mdio_write(tp, 0x1c, 0xfffd);
                    mdio_write(tp, 0x1b, 0xb81c);
                    mdio_write(tp, 0x1c, 0xfffd);
                    mdio_write(tp, 0x1b, 0xb81e);
                    mdio_write(tp, 0x1c, 0xfffd);
                    mdio_write(tp, 0x1b, 0xb832);
                    mdio_write(tp, 0x1c, 0x0001);
                    mdio_write(tp, 0x1f, 0x0000);
                    // UC patch End

                    // Clear patch_key & patch_lock
                    mdio_write(tp,0x1F, 0x0A43);
                    mdio_write(tp,0x13, 0x0000);
                    mdio_write(tp,0x14, 0x0000);
                    mdio_write(tp,0x1f, 0x0B82);
                    gphy_val = mdio_read(tp, 0x17);
                    gphy_val &= ~(BIT_0);
                    mdio_write(tp,0x17, gphy_val); // clear patch lock
                    mdio_write(tp,0x1f, 0x0A43);
                    mdio_write(tp,0x13, 0x8028);
                    mdio_write(tp,0x14, 0x0000); // clear patch key


                    // Release patch request
                    mdio_write(tp,0x1f, 0x0B82);
                    gphy_val = mdio_read(tp, 0x10);
                    gphy_val &= ~(BIT_4);
                    mdio_write(tp,0x10, gphy_val); // release patch request

                    //write ramcode version
                    mdio_write(tp, 0x1f, 0x0A43);
                mdio_write(tp, 0x13, 0x801E);
                    mdio_write(tp, 0x14, NIC_RAMCODE_VERSION);
        }

        //#GDAC updown
            mdio_write(tp, 0x1f, 0x0bcc);
            mdio_write(tp, 0x12, 0x00be);

            //R_RC
            mdio_write(tp, 0x1f, 0x0a43);
            mdio_write(tp, 0x1b, 0x81de);
            mdio_write(tp, 0x1c, 0xfdfe);     //#  fbfe [15:8] tapbin tx -3 #  [7:0] tapbin rx -2

            mdio_write(tp, 0x1b, 0x81e0);
            mdio_write(tp, 0x1c, 0xfdff);     //#  [15:8] rlen  -3

            mdio_write(tp, 0x1b, 0x81e2);
            mdio_write(tp, 0x1c, 0x0400);     //#  [15:8] rlen_100 +4, -3+4=1

            //green table 5555
            //mdio_write(tp, 0x1f, 0x0a43);
            //mdio_write(tp, 0x1b, 0x80c1);
            //mdio_write(tp, 0x1c, 0x5a00);

            mdio_write(tp, 0x1b, 0x80d3);
            mdio_write(tp, 0x1c, 0x04a4);     //# fnet cable length constant 0aa4

            mdio_write(tp, 0x1b, 0x8111);
            mdio_write(tp, 0x1c, 0x0a7f);     //# slave cable length constant fa7f

            mdio_write(tp, 0x1b, 0x810d);
            mdio_write(tp, 0x1c, 0x5604);     //# slave const dagc 0606

            mdio_write(tp, 0x1b, 0x80f4);
            mdio_write(tp, 0x1c, 0x5df7);     //# master cable length delta 3df7

            mdio_write(tp, 0x1b, 0x80f2);
            mdio_write(tp, 0x1c, 0x0a8f);     //# master cable length constant fa8f

            mdio_write(tp, 0x1b, 0x80f6);
            mdio_write(tp, 0x1c, 0x54ca);     //# master delta dagc 63ca

            mdio_write(tp, 0x1b, 0x80ec);
            mdio_write(tp, 0x1c, 0x007c);     //# master aagc 146c

            //enable ALDPS
            mdio_write(tp, 0x1F, 0x0A43);
      gphy_val = mdio_read(tp, 0x10);
      gphy_val |= BIT_2;
      mdio_write(tp, 0x10, gphy_val);

      //page 0xA43  reg 0x18 [1] : en_aldps_plloff
            gphy_val = mdio_read(tp, 0x18);
      gphy_val |= BIT_1;
      mdio_write(tp, 0x18, gphy_val);


      } */

        rtl8168_eri_write(ioaddr, 0xC8, 4, 0x00080002, ERIAR_ExGMAC);
        rtl8168_eri_write(ioaddr, 0xCC, 1, 0x38, ERIAR_ExGMAC);
        rtl8168_eri_write(ioaddr, 0xD0, 1, 0x48, ERIAR_ExGMAC);
        rtl8168_eri_write(ioaddr, 0xE8, 4, 0x00100006, ERIAR_ExGMAC);

        RTL_W32(TxConfig, RTL_R32(TxConfig) | BIT_7);

        csi_tmp = rtl8168_eri_read(ioaddr, 0xDC, 1, ERIAR_ExGMAC);
        csi_tmp &= ~BIT_0;
        rtl8168_eri_write(ioaddr, 0xDC, 1, csi_tmp, ERIAR_ExGMAC);
        csi_tmp |= BIT_0;
        rtl8168_eri_write(ioaddr, 0xDC, 1, csi_tmp, ERIAR_ExGMAC);

#if defined(CONFIG_RTD1295)
        if (tp->mcfg == CFG_METHOD_25) {
            if (tp->phy_type == PHY_TYPE_FEPHY) {
                //# ETN spec, GMAC data path select MII-like(embedded GPHY), not RGMII(external PHY)
                mac_ocp_data = mac_ocp_read(tp, 0xEA34);
                mac_ocp_data &= ~(BIT_1 | BIT_0);
                mac_ocp_data |= BIT_1;
                mac_ocp_write(tp, 0xEA34, mac_ocp_data);
            } else {    /* RGMII */
                /* # ETN spec, GMAC data path select RGMII(external PHY), not MII-like(embedded GPHY) */
                mac_ocp_data = mac_ocp_read(tp, 0xEA34);
                mac_ocp_data &= ~(BIT_1 | BIT_0);
                mac_ocp_data |= BIT_0;
                mac_ocp_write(tp, 0xEA34, mac_ocp_data);
            }
        }
        //The board of B series has this register, so it needs to set value to bring up Ethernet.
#endif /* CONFIG_RTD1295 */

        if (tp->mcfg == CFG_METHOD_26) {
            mac_ocp_data = mac_ocp_read(tp, 0xD3C0);
            mac_ocp_data &= ~(BIT_11 | BIT_10 | BIT_9 | BIT_8 | BIT_7 | BIT_6 | BIT_5 | BIT_4 | BIT_3 | BIT_2 | BIT_1 | BIT_0);
            mac_ocp_data |= 0x03A9;
            mac_ocp_write(tp, 0xD3C0, mac_ocp_data);
            mac_ocp_data = mac_ocp_read(tp, 0xD3C2);
            mac_ocp_data &= ~(BIT_7 | BIT_6 | BIT_5 | BIT_4 | BIT_3 | BIT_2 | BIT_1 | BIT_0);
            mac_ocp_write(tp, 0xD3C2, mac_ocp_data);
            mac_ocp_data = mac_ocp_read(tp, 0xD3C4);
            mac_ocp_data |= BIT_0;
            mac_ocp_write(tp, 0xD3C4, mac_ocp_data);
        }

        RTL_W8(Config3, RTL_R8(Config3) & ~Beacon_en);

        tp->cp_cmd = RTL_R16(CPlusCmd) &
                     ~(EnableBist | Macdbgo_oe | Force_halfdup |
                       Force_rxflow_en | Force_txflow_en |
                       Cxpl_dbg_sel | ASF | PktCntrDisable |
                       Macdbgo_sel);

        RTL_W8(0x1B, RTL_R8(0x1B) & ~0x07);

        RTL_W8(TDFNR, 0x1);

        RTL_W8(Config2, RTL_R8(Config2) & ~PMSTS_En);

        RTL_W8(0xD0, RTL_R8(0xD0) | BIT_6);
        RTL_W8(0xF2, RTL_R8(0xF2) | BIT_6);

        RTL_W8(0xD0, RTL_R8(0xD0) | BIT_7);

        rtl8168_eri_write(ioaddr, 0xC0, 2, 0x0000, ERIAR_ExGMAC);
        rtl8168_eri_write(ioaddr, 0xB8, 4, 0x00000000, ERIAR_ExGMAC);

        rtl8168_eri_write(ioaddr, 0x5F0, 2, 0x4f87, ERIAR_ExGMAC);

        csi_tmp = rtl8168_eri_read(ioaddr, 0xD4, 4, ERIAR_ExGMAC);
        csi_tmp  |= ( BIT_7 | BIT_8 | BIT_9 | BIT_10 | BIT_11 | BIT_12 );
        rtl8168_eri_write(ioaddr, 0xD4, 4, csi_tmp, ERIAR_ExGMAC);

        csi_tmp = rtl8168_eri_read(ioaddr, 0x1B0, 4, ERIAR_ExGMAC);
        csi_tmp &= ~BIT_12;
        rtl8168_eri_write(ioaddr, 0x1B0, 4, csi_tmp, ERIAR_ExGMAC);

        csi_tmp = rtl8168_eri_read(ioaddr, 0x2FC, 1, ERIAR_ExGMAC);
        csi_tmp &= ~(BIT_0 | BIT_1 | BIT_2);
        csi_tmp |= BIT_0;
        rtl8168_eri_write(ioaddr, 0x2FC, 1, csi_tmp, ERIAR_ExGMAC);

        //csi_tmp = rtl8168_eri_read(ioaddr, 0x1D0, 1, ERIAR_ExGMAC);
        //csi_tmp |= BIT_1;
        //rtl8168_eri_write(ioaddr, 0x1D0, 1, csi_tmp, ERIAR_ExGMAC);
    } else if (tp->mcfg == CFG_METHOD_23 || tp->mcfg == CFG_METHOD_27) {
        //set_offset70F(tp, 0x17);
        //set_offset79(tp, 0x50);

        rtl8168_eri_write(ioaddr, 0xC8, 4, 0x00080002, ERIAR_ExGMAC);
        rtl8168_eri_write(ioaddr, 0xCC, 1, 0x2f, ERIAR_ExGMAC);
        rtl8168_eri_write(ioaddr, 0xD0, 1, 0x5f, ERIAR_ExGMAC);
        rtl8168_eri_write(ioaddr, 0xE8, 4, 0x00100006, ERIAR_ExGMAC);

        RTL_W32(TxConfig, RTL_R32(TxConfig) | BIT_7);

        csi_tmp = rtl8168_eri_read(ioaddr, 0xDC, 1, ERIAR_ExGMAC);
        csi_tmp &= ~BIT_0;
        rtl8168_eri_write(ioaddr, 0xDC, 1, csi_tmp, ERIAR_ExGMAC);
        csi_tmp |= BIT_0;
        rtl8168_eri_write(ioaddr, 0xDC, 1, csi_tmp, ERIAR_ExGMAC);

        RTL_W8(Config3, RTL_R8(Config3) & ~Beacon_en);

        tp->cp_cmd = RTL_R16(CPlusCmd) &
                     ~(EnableBist | Macdbgo_oe | Force_halfdup |
                       Force_rxflow_en | Force_txflow_en |
                       Cxpl_dbg_sel | ASF | PktCntrDisable |
                       Macdbgo_sel);

        rtl8168_eri_write(ioaddr, 0xC0, 2, 0x00000000, ERIAR_ExGMAC);
        rtl8168_eri_write(ioaddr, 0xB8, 2, 0x00000000, ERIAR_ExGMAC);
        RTL_W8(0x1B, RTL_R8(0x1B) & ~0x07);

        RTL_W8(TDFNR, 0x4);

        csi_tmp = rtl8168_eri_read(ioaddr, 0x1B0, 4, ERIAR_ExGMAC);
        csi_tmp &= ~BIT_12;
        rtl8168_eri_write(ioaddr, 0x1B0, 4, csi_tmp, ERIAR_ExGMAC);

        csi_tmp = rtl8168_eri_read(ioaddr, 0x2FC, 1, ERIAR_ExGMAC);
        csi_tmp &= ~(BIT_0 | BIT_1 | BIT_2);
        csi_tmp |= BIT_0;
        rtl8168_eri_write(ioaddr, 0x2FC, 1, csi_tmp, ERIAR_ExGMAC);

        //csi_tmp = rtl8168_eri_read(ioaddr, 0x1D0, 1, ERIAR_ExGMAC);
        //csi_tmp |= BIT_1;
        //rtl8168_eri_write(ioaddr, 0x1D0, 1, csi_tmp, ERIAR_ExGMAC);

        csi_tmp = rtl8168_eri_read(ioaddr, 0xD4, 4, ERIAR_ExGMAC);
        csi_tmp  |= ( BIT_7 | BIT_8 | BIT_9 | BIT_10 | BIT_11 | BIT_12 );
        rtl8168_eri_write(ioaddr, 0xD4, 4, csi_tmp, ERIAR_ExGMAC);
    } else if (tp->mcfg == CFG_METHOD_1) {
        RTL_W8(Config3, RTL_R8(Config3) & ~Beacon_en);

        RTL_W16(CPlusCmd, RTL_R16(CPlusCmd) &
                ~(EnableBist | Macdbgo_oe | Force_halfdup | Force_rxflow_en | Force_txflow_en |
                  Cxpl_dbg_sel | ASF | PktCntrDisable | Macdbgo_sel));
    } else if (tp->mcfg == CFG_METHOD_2) {
        RTL_W8(Config3, RTL_R8(Config3) & ~Beacon_en);

        RTL_W16(CPlusCmd, RTL_R16(CPlusCmd) &
                ~(EnableBist | Macdbgo_oe | Force_halfdup | Force_rxflow_en | Force_txflow_en |
                  Cxpl_dbg_sel | ASF | PktCntrDisable | Macdbgo_sel));

        RTL_W8(Config4, RTL_R8(Config4) & ~(1 << 0));
    } else if (tp->mcfg == CFG_METHOD_3) {
        RTL_W8(Config3, RTL_R8(Config3) & ~Beacon_en);

        RTL_W16(CPlusCmd, RTL_R16(CPlusCmd) &
                ~(EnableBist | Macdbgo_oe | Force_halfdup | Force_rxflow_en | Force_txflow_en |
                  Cxpl_dbg_sel | ASF | PktCntrDisable | Macdbgo_sel));

        RTL_W8(Config4, RTL_R8(Config4) & ~(1 << 0));
    } else if (tp->mcfg == CFG_METHOD_DEFAULT) {
        tp->cp_cmd &= 0x2043;
    }

    //other hw parameters
    if (tp->mcfg == CFG_METHOD_21 || tp->mcfg == CFG_METHOD_22 ||
        tp->mcfg == CFG_METHOD_23 || tp->mcfg == CFG_METHOD_24 ||
        tp->mcfg == CFG_METHOD_25 || tp->mcfg == CFG_METHOD_26 ||
        tp->mcfg == CFG_METHOD_27)
        rtl8168_eri_write(ioaddr, 0x2F8, 2, 0x1D8F, ERIAR_ExGMAC);

    RTL_W16(CPlusCmd, tp->cp_cmd);

    RTL_W16(RxMaxSize, tp->rx_buf_sz);

    //rtl8168_disable_EEE(tp);

    rtl8168_disable_rxdvgate(dev);

    /* Set Rx packet filter */
    rtl8168_hw_set_rx_packet_filter(dev);

    RTL_W8(Cfg9346, Cfg9346_Lock);

    wmb();

    RTL_W8(ChipCmd, CmdTxEnb | CmdRxEnb);

    wmb();

    udelay(10);

#ifdef DEBUG_RTL8168
    printf ("%s elapsed time : %d\n", __FUNCTION__, currticks()-stime);
#endif
}

void rtl8168_init_ring_indexes(struct rtl8168_private *tp)
{
    tp->dirty_tx = 0;
    tp->dirty_rx = 0;
    tp->cur_tx = 0;
    tp->cur_rx = 0;
}

static inline void
rtl8168_mark_as_last_descriptor(struct RxDesc *desc)
{
    desc->opts1 |= cpu_to_le32(RingEnd);
}

static void
rtl8168_tx_desc_init(struct rtl8168_private *tp)
{
    int i = 0;

    memset(tp->TxDescArray, 0x0, NUM_TX_DESC * sizeof(struct TxDesc));

    for (i = 0; i < NUM_TX_DESC; i++) {
        if (i == (NUM_TX_DESC - 1))
            tp->TxDescArray[i].opts1 = cpu_to_le32(RingEnd);
        flush_cache( (unsigned long)&tp->TxDescArray[i], sizeof(struct TxDesc));
        /*Clear Tx descriptor buffer in hardware by flush cache. Avoid this is not clean.*/
    }
}

static void
rtl8168_rx_desc_init(struct rtl8168_private *tp)
{
    memset(tp->RxDescArray, 0x0, NUM_RX_DESC * sizeof(struct RxDesc));
    flush_cache( (unsigned long)&tp->RxDescArray, NUM_RX_DESC * sizeof(struct RxDesc));
    /*Clear Rx descriptor buffer in hardware by flush cache. Avoid this is not clean.*/
}

static u32
rtl8168_rx_fill(struct rtl8168_private *tp,
                struct eth_device *dev,
                u32 start,
                u32 end)
{
    unsigned long rxb;
    u32 cur;

    rxb = (unsigned long)tp->RxBufferRings;
    rxb = (rxb + ALIGN_8) & ~ALIGN_8;

    for (cur = start; end - cur > 0; cur++) {
        if (cur == (NUM_RX_DESC - 1))
            tp->RxDescArray[cur].opts1 =
                cpu_to_le32((DescOwn | RingEnd) + tp->rx_buf_sz);
        else
            tp->RxDescArray[cur].opts1 =
                cpu_to_le32(DescOwn + tp->rx_buf_sz);

        tp->RxBufferRing[cur] = (u8 *)(rxb + cur * tp->rx_buf_sz);
        tp->RxDescArray[cur].addr =
            cpu_to_le64(bus_to_phys(tp->RxBufferRing[cur]));

        flush_cache((unsigned long)&tp->RxDescArray[cur],sizeof(struct RxDesc));
        flush_cache((unsigned long)tp->RxBufferRing[cur], tp->rx_buf_sz);
    }

    return cur - start;
}

static int
rtl8168_init_ring(struct eth_device *dev)
{
    struct rtl8168_private *tp = (struct rtl8168_private *)dev->priv;
#ifdef DEBUG_RTL8168
    int stime = currticks();
    printf ("%s\n", __FUNCTION__);
#endif

    rtl8168_init_ring_indexes(tp);

    rtl8168_tx_desc_init(tp);
    rtl8168_rx_desc_init(tp);

    rtl8168_rx_fill(tp, dev, 0, NUM_RX_DESC);

    rtl8168_mark_as_last_descriptor(tp->RxDescArray + NUM_RX_DESC - 1);

#ifdef DEBUG_RTL8168
    printf ("%s elapsed time : %d\n", __FUNCTION__, currticks()-stime);
#endif

    return 0;
}

static void
rtl8168_hw_d3_para(struct eth_device *dev)
{
    struct rtl8168_private *tp = (struct rtl8168_private *)dev->priv;
    phys_addr_t ioaddr = tp->mmio_addr;

    RTL_W16(RxMaxSize, 0);

    switch (tp->mcfg) {
    case CFG_METHOD_14:
    case CFG_METHOD_15:
    case CFG_METHOD_16:
    case CFG_METHOD_17:
    case CFG_METHOD_18:
    case CFG_METHOD_19:
    case CFG_METHOD_20:
    case CFG_METHOD_21:
    case CFG_METHOD_22:
    case CFG_METHOD_23:
    case CFG_METHOD_24:
    case CFG_METHOD_25:
    case CFG_METHOD_26:
    case CFG_METHOD_27:
        RTL_W8(0xF1, RTL_R8(0xF1) & ~BIT_7);
        RTL_W8(Cfg9346, Cfg9346_Unlock);
        RTL_W8(Config2, RTL_R8(Config2) & ~BIT_7);
        RTL_W8(Config5, RTL_R8(Config5) & ~BIT_0);
        RTL_W8(Cfg9346, Cfg9346_Lock);
        break;
    }

    if (tp->mcfg == CFG_METHOD_21 || tp->mcfg == CFG_METHOD_22 ||
        tp->mcfg == CFG_METHOD_23 || tp->mcfg == CFG_METHOD_24 ||
        tp->mcfg == CFG_METHOD_25 || tp->mcfg == CFG_METHOD_26 ||
        tp->mcfg == CFG_METHOD_27) {
        rtl8168_eri_write(ioaddr, 0x2F8, 2, 0x0064, ERIAR_ExGMAC);
    }

    /*disable ocp phy power saving*/
    /*if (tp->mcfg == CFG_METHOD_25 || tp->mcfg == CFG_METHOD_26 || tp->mcfg == CFG_METHOD_27) {
        mdio_write(tp, 0x1F, 0x0C41);
        mdio_write(tp, 0x13, 0x0000);
        mdio_write(tp, 0x13, 0x0500);
        mdio_write(tp, 0x1F, 0x0000);
    }
        */
    rtl8168_disable_rxdvgate(dev);
}

static void rtl8168_down(struct eth_device *dev)
{
    struct rtl8168_private *tp = (struct rtl8168_private *)dev->priv;

    rtl8168_hw_reset(dev);

    rtl8168_hw_d3_para(dev);

    if (tp->RxBufferRings) {
        free(tp->RxBufferRings);
        tp->RxBufferRings = NULL;
    }

    if (tp->DescArrays) {
        free(tp->DescArrays);
        tp->DescArrays = NULL;
    }
}

#if 0
static int rtl8168_set_speed_xmii(struct rtl8168_private *tp,
                                  u8 autoneg, u16 speed, u8 duplex)
{
    u16 gbcr, anar, bmcr;

    MDIO_LOCK;
    mdio_write(tp, 0x1f, 0x0000);

    anar = mdio_read(tp, MII_ADVERTISE);
    anar &= ~(ADVERTISE_10HALF | ADVERTISE_10FULL |
              ADVERTISE_100HALF | ADVERTISE_100FULL);
    anar |= ADVERTISE_PAUSE_CAP | ADVERTISE_PAUSE_ASYM;

    gbcr = mdio_read(tp, MII_CTRL1000);
    gbcr &= ~(ADVERTISE_1000FULL | ADVERTISE_1000HALF);

    if (autoneg) {
        anar |= ADVERTISE_10HALF | ADVERTISE_10FULL |
                ADVERTISE_100HALF | ADVERTISE_100FULL;

        gbcr |= ADVERTISE_1000FULL | ADVERTISE_1000HALF;

        bmcr = BMCR_ANENABLE | BMCR_ANRESTART | BMCR_RESET;
    } else if (speed == SPEED_1000) {
        gbcr |= ADVERTISE_1000HALF;

        if (duplex == DUPLEX_FULL)
            gbcr |= ADVERTISE_1000FULL;

        bmcr = BMCR_SPEED1000;
    } else if (speed == SPEED_100) {
        anar |= ADVERTISE_100HALF;

        if (duplex == DUPLEX_FULL)
            anar |= ADVERTISE_100FULL;

        bmcr = BMCR_SPEED100;
    } else if (speed == SPEED_10) {
        anar |= ADVERTISE_10HALF;

        if (duplex == DUPLEX_FULL)
            anar |= ADVERTISE_10FULL;

        bmcr = 0;
    } else
        return -EINVAL;

    mdio_write(tp, MII_ADVERTISE, anar);
    mdio_write(tp, MII_CTRL1000, gbcr);
    mdio_write(tp, MII_BMCR, bmcr);

    return 0;
}
#endif

static void
rtl8168_hw_init(struct eth_device *dev)
{
    struct rtl8168_private *tp = (struct rtl8168_private *)dev->priv;
    phys_addr_t ioaddr = tp->mmio_addr;

    switch (tp->mcfg) {
    case CFG_METHOD_14:
    case CFG_METHOD_15:
    case CFG_METHOD_16:
    case CFG_METHOD_17:
    case CFG_METHOD_18:
    case CFG_METHOD_19:
    case CFG_METHOD_20:
    case CFG_METHOD_21:
    case CFG_METHOD_22:
    case CFG_METHOD_23:
    case CFG_METHOD_24:
    case CFG_METHOD_25:
    case CFG_METHOD_26:
    case CFG_METHOD_27:
        RTL_W8(Cfg9346, Cfg9346_Unlock);
        RTL_W8(Config5, RTL_R8(Config5) & ~BIT_0);
        RTL_W8(Config2, RTL_R8(Config2) & ~BIT_7);
        RTL_W8(Cfg9346, Cfg9346_Lock);
        RTL_W8(0xF1, RTL_R8(0xF1) & ~BIT_7);
        break;
    }

    switch (tp->mcfg) {
    case CFG_METHOD_9:
    case CFG_METHOD_10:
        RTL_W8(DBG_reg, RTL_R8(DBG_reg) | BIT_1 | BIT_7);
        break;
    }

    switch (tp->mcfg) {
    case CFG_METHOD_16:
    case CFG_METHOD_17:
    case CFG_METHOD_18:
    case CFG_METHOD_19:
        RTL_W8(0xF2, (RTL_R8(0xF2) % ~(BIT_2 | BIT_1 | BIT_0)));
        break;
    }

    switch (tp->mcfg) {
    case CFG_METHOD_21:
    case CFG_METHOD_22:
        rtl8168_eri_write(ioaddr, 0x174, 2, 0x0000, ERIAR_ExGMAC);
        mac_ocp_write(tp, 0xE428, 0x0010);
        break;
    }

    if (tp->mcfg == CFG_METHOD_10 || tp->mcfg == CFG_METHOD_14 || tp->mcfg == CFG_METHOD_15)
        RTL_W8(0xF3, RTL_R8(0xF3) | BIT_2);


    //rtl8168_hw_mac_mcu_config(dev);

    /*disable ocp phy power saving*/
    if (tp->mcfg == CFG_METHOD_25 || tp->mcfg == CFG_METHOD_26 || tp->mcfg == CFG_METHOD_27) {
        mdio_write(tp, 0x1F, 0x0C41);
        mdio_write(tp, 0x13, 0x0000);
        mdio_write(tp, 0x13, 0x0500);
        mdio_write(tp, 0x1F, 0x0000);
    }
}

static void
rtl8168_hw_ephy_config(struct eth_device *dev)
{
    struct rtl8168_private *tp = (struct rtl8168_private *)dev->priv;
    phys_addr_t ioaddr = tp->mmio_addr;
    u16 ephy_data;


    if (tp->mcfg == CFG_METHOD_4) {
        /*Set EPHY registers    begin*/
        /*Set EPHY register offset 0x02 bit 11 to 0 and bit 12 to 1*/
        ephy_data = rtl8168_ephy_read(ioaddr, 0x02);
        ephy_data &= ~BIT_11;
        ephy_data |= BIT_12;
        rtl8168_ephy_write(ioaddr, 0x02, ephy_data);

        /*Set EPHY register offset 0x03 bit 1 to 1*/
        ephy_data = rtl8168_ephy_read(ioaddr, 0x03);
        ephy_data |= (1 << 1);
        rtl8168_ephy_write(ioaddr, 0x03, ephy_data);

        /*Set EPHY register offset 0x06 bit 7 to 0*/
        ephy_data = rtl8168_ephy_read(ioaddr, 0x06);
        ephy_data &= ~(1 << 7);
        rtl8168_ephy_write(ioaddr, 0x06, ephy_data);
        /*Set EPHY registers    end*/
    } else if (tp->mcfg == CFG_METHOD_5) {
        /******set EPHY registers for RTL8168CP begin******/
        /*Set EPHY register offset 0x01 bit 0 to 1.*/
        ephy_data = rtl8168_ephy_read(ioaddr, 0x01);
        ephy_data |= (1 << 0);
        rtl8168_ephy_write(ioaddr, 0x01, ephy_data);

        /*Set EPHY register offset 0x03 bit 10 to 0, bit 9 to 1 and bit 5 to 1.*/
        ephy_data = rtl8168_ephy_read(ioaddr, 0x03);
        ephy_data &= ~(1 << 10);
        ephy_data |= (1 << 9);
        ephy_data |= (1 << 5);
        rtl8168_ephy_write(ioaddr, 0x03, ephy_data);
        /******set EPHY registers for RTL8168CP end******/
    } else if (tp->mcfg == CFG_METHOD_9) {
        /* set EPHY registers */
        rtl8168_ephy_write(ioaddr, 0x01, 0x7C7D);
        rtl8168_ephy_write(ioaddr, 0x02, 0x091F);
        rtl8168_ephy_write(ioaddr, 0x06, 0xB271);
        rtl8168_ephy_write(ioaddr, 0x07, 0xCE00);
    } else if (tp->mcfg == CFG_METHOD_10) {
        /* set EPHY registers */
        rtl8168_ephy_write(ioaddr, 0x01, 0x6C7F);
        rtl8168_ephy_write(ioaddr, 0x02, 0x011F);
        rtl8168_ephy_write(ioaddr, 0x03, 0xC1B2);
        rtl8168_ephy_write(ioaddr, 0x1A, 0x0546);
        rtl8168_ephy_write(ioaddr, 0x1C, 0x80C4);
        rtl8168_ephy_write(ioaddr, 0x1D, 0x78E4);
        rtl8168_ephy_write(ioaddr, 0x0A, 0x8100);
    } else if (tp->mcfg == CFG_METHOD_12) {
        ephy_data = rtl8168_ephy_read(ioaddr, 0x0B);
        rtl8168_ephy_write(ioaddr, 0x0B, ephy_data|0x48);
        ephy_data = rtl8168_ephy_read(ioaddr, 0x19);
        ephy_data &= ~0x20;
        rtl8168_ephy_write(ioaddr, 0x19, ephy_data|0x50);
        ephy_data = rtl8168_ephy_read(ioaddr, 0x0C);
        ephy_data &= ~0x100;
        rtl8168_ephy_write(ioaddr, 0x0C, ephy_data|0x20);
    } else if (tp->mcfg == CFG_METHOD_14 || tp->mcfg == CFG_METHOD_15) {
        /* set EPHY registers */
        ephy_data = rtl8168_ephy_read(ioaddr, 0x00) & ~0x0200;
        ephy_data |= 0x0100;
        rtl8168_ephy_write(ioaddr, 0x00, ephy_data);

        ephy_data = rtl8168_ephy_read(ioaddr, 0x00);
        ephy_data |= 0x0004;
        rtl8168_ephy_write(ioaddr, 0x00, ephy_data);

        ephy_data = rtl8168_ephy_read(ioaddr, 0x06) & ~0x0002;
        ephy_data |= 0x0001;
        rtl8168_ephy_write(ioaddr, 0x06, ephy_data);

        ephy_data = rtl8168_ephy_read(ioaddr, 0x06);
        ephy_data |= 0x0030;
        rtl8168_ephy_write(ioaddr, 0x06, ephy_data);

        ephy_data = rtl8168_ephy_read(ioaddr, 0x07);
        ephy_data |= 0x2000;
        rtl8168_ephy_write(ioaddr, 0x07, ephy_data);

        ephy_data = rtl8168_ephy_read(ioaddr, 0x00);
        ephy_data |= 0x0020;
        rtl8168_ephy_write(ioaddr, 0x00, ephy_data);

        ephy_data = rtl8168_ephy_read(ioaddr, 0x03) & ~0x5800;
        ephy_data |= 0x2000;
        rtl8168_ephy_write(ioaddr, 0x03, ephy_data);

        ephy_data = rtl8168_ephy_read(ioaddr, 0x03);
        ephy_data |= 0x0001;
        rtl8168_ephy_write(ioaddr, 0x03, ephy_data);

        ephy_data = rtl8168_ephy_read(ioaddr, 0x01) & ~0x0800;
        ephy_data |= 0x1000;
        rtl8168_ephy_write(ioaddr, 0x01, ephy_data);

        ephy_data = rtl8168_ephy_read(ioaddr, 0x07);
        ephy_data |= 0x4000;
        rtl8168_ephy_write(ioaddr, 0x07, ephy_data);

        ephy_data = rtl8168_ephy_read(ioaddr, 0x1E);
        ephy_data |= 0x2000;
        rtl8168_ephy_write(ioaddr, 0x1E, ephy_data);

        rtl8168_ephy_write(ioaddr, 0x19, 0xFE6C);

        ephy_data = rtl8168_ephy_read(ioaddr, 0x0A);
        ephy_data |= 0x0040;
        rtl8168_ephy_write(ioaddr, 0x0A, ephy_data);
    } else if (tp->mcfg == CFG_METHOD_16 || tp->mcfg == CFG_METHOD_17) {
        if (tp->mcfg == CFG_METHOD_16) {
            rtl8168_ephy_write(ioaddr, 0x06, 0xF020);
            rtl8168_ephy_write(ioaddr, 0x07, 0x01FF);
            rtl8168_ephy_write(ioaddr, 0x00, 0x5027);
            rtl8168_ephy_write(ioaddr, 0x01, 0x0003);
            rtl8168_ephy_write(ioaddr, 0x02, 0x2D16);
            rtl8168_ephy_write(ioaddr, 0x03, 0x6D49);
            rtl8168_ephy_write(ioaddr, 0x08, 0x0006);
            rtl8168_ephy_write(ioaddr, 0x0A, 0x00C8);
        }

        ephy_data = rtl8168_ephy_read(ioaddr, 0x09);
        ephy_data |= BIT_7;
        rtl8168_ephy_write(ioaddr, 0x09, ephy_data);

        ephy_data = rtl8168_ephy_read(ioaddr, 0x19);
        ephy_data |= (BIT_2 | BIT_5 | BIT_9);
        rtl8168_ephy_write(ioaddr, 0x19, ephy_data);
    } else if (tp->mcfg == CFG_METHOD_18 || tp->mcfg == CFG_METHOD_19) {
        if (tp->mcfg == CFG_METHOD_18) {
            ephy_data = rtl8168_ephy_read(ioaddr, 0x06);
            ephy_data |= BIT_5;
            ephy_data &= ~(BIT_7 | BIT_6);
            rtl8168_ephy_write(ioaddr, 0x06, ephy_data);

            ephy_data = rtl8168_ephy_read(ioaddr, 0x08);
            ephy_data |= BIT_1;
            ephy_data &= ~BIT_0;
            rtl8168_ephy_write(ioaddr, 0x08, ephy_data);
        }

        ephy_data = rtl8168_ephy_read(ioaddr, 0x09);
        ephy_data |= BIT_7;
        rtl8168_ephy_write(ioaddr, 0x09, ephy_data);

        ephy_data = rtl8168_ephy_read(ioaddr, 0x19);
        ephy_data |= (BIT_2 | BIT_5 | BIT_9);
        rtl8168_ephy_write(ioaddr, 0x19, ephy_data);
    } else if (tp->mcfg == CFG_METHOD_20) {
        ephy_data = rtl8168_ephy_read(ioaddr, 0x06);
        ephy_data |= BIT_5;
        ephy_data &= ~(BIT_7 | BIT_6);
        rtl8168_ephy_write(ioaddr, 0x06, ephy_data);

        rtl8168_ephy_write(ioaddr, 0x0f, 0x5200);

        ephy_data = rtl8168_ephy_read(ioaddr, 0x19);
        ephy_data |= (BIT_2 | BIT_5 | BIT_9);
        rtl8168_ephy_write(ioaddr, 0x19, ephy_data);
    } else if (tp->mcfg == CFG_METHOD_21 || tp->mcfg == CFG_METHOD_22) {

        ephy_data = rtl8168_ephy_read(ioaddr, 0x00);
        ephy_data &= ~(BIT_3);
        rtl8168_ephy_write(ioaddr, 0x00, ephy_data);
        ephy_data = rtl8168_ephy_read(ioaddr, 0x0C);
        ephy_data &= ~(BIT_13 | BIT_12 | BIT_11 | BIT_10 | BIT_9 | BIT_8 | BIT_7 | BIT_6 | BIT_5 | BIT_4);
        ephy_data |= (BIT_5 | BIT_11);
        rtl8168_ephy_write(ioaddr, 0x0C, ephy_data);

        ephy_data = rtl8168_ephy_read(ioaddr, 0x1E);
        ephy_data &= ~(BIT_0);
        rtl8168_ephy_write(ioaddr, 0x1E, ephy_data);
    } else if (tp->mcfg == CFG_METHOD_25) {
        ephy_data = rtl8168_ephy_read(ioaddr, 0x00);
        ephy_data |= BIT_3;
        rtl8168_ephy_write(ioaddr, 0x00, ephy_data);
        ephy_data = rtl8168_ephy_read(ioaddr, 0x0C);
        ephy_data &= ~(BIT_13 | BIT_12 | BIT_11 | BIT_9 | BIT_8 | BIT_7 | BIT_6 | BIT_5 | BIT_4);
        ephy_data |= BIT_10;
        rtl8168_ephy_write(ioaddr, 0x0C, ephy_data);

        rtl8168_ephy_write(ioaddr, 0x19, 0xFC00);
        rtl8168_ephy_write(ioaddr, 0x1E, 0x20EB);

        ephy_data = rtl8168_ephy_read(ioaddr, 0x06);
        ephy_data |= BIT_4;
        rtl8168_ephy_write(ioaddr, 0x06, ephy_data);
    } else if (tp->mcfg == CFG_METHOD_26) {
        ephy_data = rtl8168_ephy_read(ioaddr, 0x00);
        ephy_data |= BIT_3;
        rtl8168_ephy_write(ioaddr, 0x00, ephy_data);
        ephy_data = rtl8168_ephy_read(ioaddr, 0x0C);
        ephy_data &= ~(BIT_13 | BIT_12 | BIT_11 | BIT_9 | BIT_8 | BIT_7 | BIT_6 | BIT_5 | BIT_4);
        ephy_data |= BIT_10;
        rtl8168_ephy_write(ioaddr, 0x0C, ephy_data);

        rtl8168_ephy_write(ioaddr, 0x0F, 0x5200);

        ephy_data = rtl8168_ephy_read(ioaddr, 0x19);
        ephy_data &= ~BIT_5;
        rtl8168_ephy_write(ioaddr, 0x19, ephy_data);

        ephy_data = rtl8168_ephy_read(ioaddr, 0x1E);
        ephy_data |= BIT_13;
        rtl8168_ephy_write(ioaddr, 0x1E, ephy_data);

        ephy_data = rtl8168_ephy_read(ioaddr, 0x06);
        ephy_data |= BIT_4;
        rtl8168_ephy_write(ioaddr, 0x06, ephy_data);
    } else if (tp->mcfg == CFG_METHOD_23) {
        rtl8168_ephy_write(ioaddr, 0x00, 0x10AB);
        rtl8168_ephy_write(ioaddr, 0x06, 0xf030);
        rtl8168_ephy_write(ioaddr, 0x08, 0x2006);
        rtl8168_ephy_write(ioaddr, 0x0D, 0x1666);

        ephy_data = rtl8168_ephy_read(ioaddr, 0x0C);
        ephy_data &= ~(BIT_13 | BIT_12 | BIT_11 | BIT_10 | BIT_9 | BIT_8 | BIT_7 | BIT_6 | BIT_5 | BIT_4);
        rtl8168_ephy_write(ioaddr, 0x0C, ephy_data);
    } else if (tp->mcfg == CFG_METHOD_27) {
        ephy_data = rtl8168_ephy_read(ioaddr, 0x00);
        ephy_data |= BIT_3;
        rtl8168_ephy_write(ioaddr, 0x00, ephy_data);
        ephy_data = rtl8168_ephy_read(ioaddr, 0x0C);
        ephy_data &= ~(BIT_13 | BIT_12 | BIT_11 | BIT_10 | BIT_8 | BIT_7 | BIT_6 | BIT_5 | BIT_4);
        ephy_data |= BIT_9;
        rtl8168_ephy_write(ioaddr, 0x0C, ephy_data);

        rtl8168_ephy_write(ioaddr, 0x19, 0xFC00);
        rtl8168_ephy_write(ioaddr, 0x1E, 0x20EB);
    }
}

static void
rtl8168_xmii_reset_enable(struct eth_device *dev)
{
    struct rtl8168_private *tp = (struct rtl8168_private *)dev->priv;
    int i, val = 0;

    return ;
    mdio_write(tp, 0x1f, 0x0000);
    mdio_write(tp, MII_BMCR, mdio_read(tp, MII_BMCR) | BMCR_RESET);

    for (i = 0; i < 2500; i++) {
        val = mdio_read(tp, MII_BMSR) & BMCR_RESET;

        if (!val)
            return;

        mdelay(1);
    }
}

static void
rtl8168_hw_phy_config(struct eth_device *dev)
{
    struct rtl8168_private *tp = (struct rtl8168_private *)dev->priv;
    unsigned int gphy_val;

    rtl8168_xmii_reset_enable(dev);

    return;
    //rtl8168_init_hw_phy_mcu(dev);

    if (tp->mcfg == CFG_METHOD_1) {
        mdio_write(tp, 0x1F, 0x0001);
        mdio_write(tp, 0x0B, 0x94B0);

        mdio_write(tp, 0x1F, 0x0003);
        mdio_write(tp, 0x12, 0x6096);
        mdio_write(tp, 0x1F, 0x0000);

        mdio_write(tp, 0x0D, 0xF8A0);
    } else if (tp->mcfg == CFG_METHOD_2) {
        mdio_write(tp, 0x1F, 0x0001);
        mdio_write(tp, 0x0B, 0x94B0);

        mdio_write(tp, 0x1F, 0x0003);
        mdio_write(tp, 0x12, 0x6096);

        mdio_write(tp, 0x1F, 0x0000);
    } else if (tp->mcfg == CFG_METHOD_3) {
        mdio_write(tp, 0x1F, 0x0001);
        mdio_write(tp, 0x0B, 0x94B0);

        mdio_write(tp, 0x1F, 0x0003);
        mdio_write(tp, 0x12, 0x6096);

        mdio_write(tp, 0x1F, 0x0000);
    } else if (tp->mcfg == CFG_METHOD_4) {
        mdio_write(tp, 0x1F, 0x0001);
        mdio_write(tp, 0x12, 0x2300);
        mdio_write(tp, 0x1F, 0x0000);
        mdio_write(tp, 0x1F, 0x0003);
        mdio_write(tp, 0x16, 0x000A);
        mdio_write(tp, 0x1F, 0x0000);

        mdio_write(tp, 0x1F, 0x0003);
        mdio_write(tp, 0x12, 0xC096);
        mdio_write(tp, 0x1F, 0x0000);

        mdio_write(tp, 0x1F, 0x0002);
        mdio_write(tp, 0x00, 0x88DE);
        mdio_write(tp, 0x01, 0x82B1);
        mdio_write(tp, 0x1F, 0x0000);

        mdio_write(tp, 0x1F, 0x0002);
        mdio_write(tp, 0x08, 0x9E30);
        mdio_write(tp, 0x09, 0x01F0);
        mdio_write(tp, 0x1F, 0x0000);

        mdio_write(tp, 0x1F, 0x0002);
        mdio_write(tp, 0x0A, 0x5500);
        mdio_write(tp, 0x1F, 0x0000);

        mdio_write(tp, 0x1F, 0x0002);
        mdio_write(tp, 0x03, 0x7002);
        mdio_write(tp, 0x1F, 0x0000);

        mdio_write(tp, 0x1F, 0x0002);
        mdio_write(tp, 0x0C, 0x00C8);
        mdio_write(tp, 0x1F, 0x0000);

        mdio_write(tp, 0x1F, 0x0000);
        mdio_write(tp, 0x14, mdio_read(tp, 0x14) | (1 << 5));
        mdio_write(tp, 0x0D, mdio_read(tp, 0x0D) & ~(1 << 5));
    } else if (tp->mcfg == CFG_METHOD_5) {
        mdio_write(tp, 0x1F, 0x0001);
        mdio_write(tp, 0x12, 0x2300);
        mdio_write(tp, 0x1F, 0x0003);
        mdio_write(tp, 0x16, 0x0F0A);
        mdio_write(tp, 0x1F, 0x0000);

        mdio_write(tp, 0x1F, 0x0002);
        mdio_write(tp, 0x00, 0x88DE);
        mdio_write(tp, 0x01, 0x82B1);
        mdio_write(tp, 0x1F, 0x0000);

        mdio_write(tp, 0x1F, 0x0002);
        mdio_write(tp, 0x0C, 0x7EB8);
        mdio_write(tp, 0x1F, 0x0000);

        mdio_write(tp, 0x1F, 0x0002);
        mdio_write(tp, 0x06, 0x0761);
        mdio_write(tp, 0x1F, 0x0000);

        mdio_write(tp, 0x1F, 0x0001);
        mdio_write(tp, 0x03, 0x802F);
        mdio_write(tp, 0x02, 0x4F02);
        mdio_write(tp, 0x01, 0x0409);
        mdio_write(tp, 0x00, 0xF099);
        mdio_write(tp, 0x04, 0x9800);
        mdio_write(tp, 0x04, 0x9000);
        mdio_write(tp, 0x1F, 0x0000);

        mdio_write(tp, 0x1F, 0x0000);
        mdio_write(tp, 0x16, mdio_read(tp, 0x16) | (1 << 0));

        mdio_write(tp, 0x1F, 0x0000);
        mdio_write(tp, 0x14, mdio_read(tp, 0x14) | (1 << 5));
        mdio_write(tp, 0x0D, mdio_read(tp, 0x0D) & ~(1 << 5));

        mdio_write(tp, 0x1F, 0x0001);
        mdio_write(tp, 0x1D, 0x3D98);
        mdio_write(tp, 0x1F, 0x0000);

        mdio_write(tp, 0x1F, 0x0001);
        mdio_write(tp, 0x17, 0x0CC0);
        mdio_write(tp, 0x1F, 0x0000);
    } else if (tp->mcfg == CFG_METHOD_6) {
        mdio_write(tp, 0x1F, 0x0001);
        mdio_write(tp, 0x12, 0x2300);
        mdio_write(tp, 0x1F, 0x0003);
        mdio_write(tp, 0x16, 0x0F0A);
        mdio_write(tp, 0x1F, 0x0000);

        mdio_write(tp, 0x1F, 0x0002);
        mdio_write(tp, 0x00, 0x88DE);
        mdio_write(tp, 0x01, 0x82B1);
        mdio_write(tp, 0x1F, 0x0000);

        mdio_write(tp, 0x1F, 0x0002);
        mdio_write(tp, 0x0C, 0x7EB8);
        mdio_write(tp, 0x1F, 0x0000);

        mdio_write(tp, 0x1F, 0x0002);
        mdio_write(tp, 0x06, 0x5461);
        mdio_write(tp, 0x1F, 0x0000);

        mdio_write(tp, 0x1F, 0x0002);
        mdio_write(tp, 0x06, 0x5461);
        mdio_write(tp, 0x1F, 0x0000);

        mdio_write(tp, 0x1F, 0x0000);
        mdio_write(tp, 0x16, mdio_read(tp, 0x16) | (1 << 0));

        mdio_write(tp, 0x1F, 0x0000);
        mdio_write(tp, 0x14, mdio_read(tp, 0x14) | (1 << 5));
        mdio_write(tp, 0x0D, mdio_read(tp, 0x0D) & ~(1 << 5));

        mdio_write(tp, 0x1F, 0x0001);
        mdio_write(tp, 0x1D, 0x3D98);
        mdio_write(tp, 0x1F, 0x0000);

        mdio_write(tp, 0x1f, 0x0001);
        mdio_write(tp, 0x17, 0x0CC0);
        mdio_write(tp, 0x1F, 0x0000);
    } else if (tp->mcfg == CFG_METHOD_7) {
        mdio_write(tp, 0x1F, 0x0000);
        mdio_write(tp, 0x14, mdio_read(tp, 0x14) | (1 << 5));
        mdio_write(tp, 0x0D, mdio_read(tp, 0x0D) & ~(1 << 5));

        mdio_write(tp, 0x1F, 0x0001);
        mdio_write(tp, 0x1D, 0x3D98);

        mdio_write(tp, 0x1F, 0x0001);
        mdio_write(tp, 0x14, 0xCAA3);
        mdio_write(tp, 0x1C, 0x000A);
        mdio_write(tp, 0x18, 0x65D0);

        mdio_write(tp, 0x1F, 0x0003);
        mdio_write(tp, 0x17, 0xB580);
        mdio_write(tp, 0x18, 0xFF54);
        mdio_write(tp, 0x19, 0x3954);

        mdio_write(tp, 0x1F, 0x0002);
        mdio_write(tp, 0x0D, 0x310C);
        mdio_write(tp, 0x0E, 0x310C);
        mdio_write(tp, 0x0F, 0x311C);
        mdio_write(tp, 0x06, 0x0761);

        mdio_write(tp, 0x1F, 0x0003);
        mdio_write(tp, 0x18, 0xFF55);
        mdio_write(tp, 0x19, 0x3955);
        mdio_write(tp, 0x18, 0xFF54);
        mdio_write(tp, 0x19, 0x3954);

        mdio_write(tp, 0x1F, 0x0001);
        mdio_write(tp, 0x17, 0x0CC0);

        mdio_write(tp, 0x1F, 0x0000);
    } else if (tp->mcfg == CFG_METHOD_8) {
        mdio_write(tp, 0x1F, 0x0000);
        mdio_write(tp, 0x14, mdio_read(tp, 0x14) | (1 << 5));
        mdio_write(tp, 0x0D, mdio_read(tp, 0x0D) & ~(1 << 5));

        mdio_write(tp, 0x1F, 0x0001);
        mdio_write(tp, 0x14, 0xCAA3);
        mdio_write(tp, 0x1C, 0x000A);
        mdio_write(tp, 0x18, 0x65D0);

        mdio_write(tp, 0x1F, 0x0003);
        mdio_write(tp, 0x17, 0xB580);
        mdio_write(tp, 0x18, 0xFF54);
        mdio_write(tp, 0x19, 0x3954);

        mdio_write(tp, 0x1F, 0x0002);
        mdio_write(tp, 0x0D, 0x310C);
        mdio_write(tp, 0x0E, 0x310C);
        mdio_write(tp, 0x0F, 0x311C);
        mdio_write(tp, 0x06, 0x0761);

        mdio_write(tp, 0x1F, 0x0003);
        mdio_write(tp, 0x18, 0xFF55);
        mdio_write(tp, 0x19, 0x3955);
        mdio_write(tp, 0x18, 0xFF54);
        mdio_write(tp, 0x19, 0x3954);

        mdio_write(tp, 0x1F, 0x0001);
        mdio_write(tp, 0x17, 0x0CC0);

        mdio_write(tp, 0x1F, 0x0000);
        mdio_write(tp, 0x16, mdio_read(tp, 0x16) | (1 << 0));

        mdio_write(tp, 0x1F, 0x0000);
    } else if (tp->mcfg == CFG_METHOD_9) {
        mdio_write(tp, 0x1F, 0x0001);
        mdio_write(tp, 0x06, 0x4064);
        mdio_write(tp, 0x07, 0x2863);
        mdio_write(tp, 0x08, 0x059C);
        mdio_write(tp, 0x09, 0x26B4);
        mdio_write(tp, 0x0A, 0x6A19);
        mdio_write(tp, 0x0B, 0xDCC8);
        mdio_write(tp, 0x10, 0xF06D);
        mdio_write(tp, 0x14, 0x7F68);
        mdio_write(tp, 0x18, 0x7FD9);
        mdio_write(tp, 0x1C, 0xF0FF);
        mdio_write(tp, 0x1D, 0x3D9C);
        mdio_write(tp, 0x1F, 0x0003);
        mdio_write(tp, 0x12, 0xF49F);
        mdio_write(tp, 0x13, 0x070B);
        mdio_write(tp, 0x1A, 0x05AD);
        mdio_write(tp, 0x14, 0x94C0);

        mdio_write(tp, 0x1F, 0x0002);
        gphy_val = mdio_read(tp, 0x0B) & 0xFF00;
        gphy_val |= 0x10;
        mdio_write(tp, 0x0B, gphy_val);
        gphy_val = mdio_read(tp, 0x0C) & 0x00FF;
        gphy_val |= 0xA200;
        mdio_write(tp, 0x0C, gphy_val);

        mdio_write(tp, 0x1F, 0x0002);
        mdio_write(tp, 0x06, 0x5561);
        mdio_write(tp, 0x1F, 0x0005);
        mdio_write(tp, 0x05, 0x8332);
        mdio_write(tp, 0x06, 0x5561);

        if (rtl8168_efuse_read(tp, 0x01) == 0xb1) {
            mdio_write(tp, 0x1F, 0x0002);
            mdio_write(tp, 0x05, 0x669A);
            mdio_write(tp, 0x1F, 0x0005);
            mdio_write(tp, 0x05, 0x8330);
            mdio_write(tp, 0x06, 0x669A);

            mdio_write(tp, 0x1F, 0x0002);
            gphy_val = mdio_read(tp, 0x0D);
            if ((gphy_val & 0x00FF) != 0x006C) {
                gphy_val &= 0xFF00;
                mdio_write(tp, 0x1F, 0x0002);
                mdio_write(tp, 0x0D, gphy_val | 0x0065);
                mdio_write(tp, 0x0D, gphy_val | 0x0066);
                mdio_write(tp, 0x0D, gphy_val | 0x0067);
                mdio_write(tp, 0x0D, gphy_val | 0x0068);
                mdio_write(tp, 0x0D, gphy_val | 0x0069);
                mdio_write(tp, 0x0D, gphy_val | 0x006A);
                mdio_write(tp, 0x0D, gphy_val | 0x006B);
                mdio_write(tp, 0x0D, gphy_val | 0x006C);
            }
        } else {
            mdio_write(tp, 0x1F, 0x0002);
            mdio_write(tp, 0x05, 0x6662);
            mdio_write(tp, 0x1F, 0x0005);
            mdio_write(tp, 0x05, 0x8330);
            mdio_write(tp, 0x06, 0x6662);
        }

        mdio_write(tp, 0x1F, 0x0002);
        gphy_val = mdio_read(tp, 0x0D);
        gphy_val |= BIT_9;
        gphy_val |= BIT_8;
        mdio_write(tp, 0x0D, gphy_val);
        gphy_val = mdio_read(tp, 0x0F);
        gphy_val |= BIT_4;
        mdio_write(tp, 0x0F, gphy_val);

        mdio_write(tp, 0x1F, 0x0002);
        gphy_val = mdio_read(tp, 0x02);
        gphy_val &= ~BIT_10;
        gphy_val &= ~BIT_9;
        gphy_val |= BIT_8;
        mdio_write(tp, 0x02, gphy_val);
        gphy_val = mdio_read(tp, 0x03);
        gphy_val &= ~BIT_15;
        gphy_val &= ~BIT_14;
        gphy_val &= ~BIT_13;
        mdio_write(tp, 0x03, gphy_val);

        mdio_write(tp, 0x1F, 0x0001);
        mdio_write(tp, 0x17, 0x0CC0);

        mdio_write(tp, 0x1F, 0x0005);
        mdio_write(tp, 0x05, 0x001B);
        if (mdio_read(tp, 0x06) == 0xBF00) {
            mdio_write(tp, 0x1f, 0x0005);
            mdio_write(tp, 0x05, 0xfff6);
            mdio_write(tp, 0x06, 0x0080);
            mdio_write(tp, 0x05, 0x8000);
            mdio_write(tp, 0x06, 0xf8f9);
            mdio_write(tp, 0x06, 0xfaef);
            mdio_write(tp, 0x06, 0x59ee);
            mdio_write(tp, 0x06, 0xf8ea);
            mdio_write(tp, 0x06, 0x00ee);
            mdio_write(tp, 0x06, 0xf8eb);
            mdio_write(tp, 0x06, 0x00e0);
            mdio_write(tp, 0x06, 0xf87c);
            mdio_write(tp, 0x06, 0xe1f8);
            mdio_write(tp, 0x06, 0x7d59);
            mdio_write(tp, 0x06, 0x0fef);
            mdio_write(tp, 0x06, 0x0139);
            mdio_write(tp, 0x06, 0x029e);
            mdio_write(tp, 0x06, 0x06ef);
            mdio_write(tp, 0x06, 0x1039);
            mdio_write(tp, 0x06, 0x089f);
            mdio_write(tp, 0x06, 0x2aee);
            mdio_write(tp, 0x06, 0xf8ea);
            mdio_write(tp, 0x06, 0x00ee);
            mdio_write(tp, 0x06, 0xf8eb);
            mdio_write(tp, 0x06, 0x01e0);
            mdio_write(tp, 0x06, 0xf87c);
            mdio_write(tp, 0x06, 0xe1f8);
            mdio_write(tp, 0x06, 0x7d58);
            mdio_write(tp, 0x06, 0x409e);
            mdio_write(tp, 0x06, 0x0f39);
            mdio_write(tp, 0x06, 0x46aa);
            mdio_write(tp, 0x06, 0x0bbf);
            mdio_write(tp, 0x06, 0x8290);
            mdio_write(tp, 0x06, 0xd682);
            mdio_write(tp, 0x06, 0x9802);
            mdio_write(tp, 0x06, 0x014f);
            mdio_write(tp, 0x06, 0xae09);
            mdio_write(tp, 0x06, 0xbf82);
            mdio_write(tp, 0x06, 0x98d6);
            mdio_write(tp, 0x06, 0x82a0);
            mdio_write(tp, 0x06, 0x0201);
            mdio_write(tp, 0x06, 0x4fef);
            mdio_write(tp, 0x06, 0x95fe);
            mdio_write(tp, 0x06, 0xfdfc);
            mdio_write(tp, 0x06, 0x05f8);
            mdio_write(tp, 0x06, 0xf9fa);
            mdio_write(tp, 0x06, 0xeef8);
            mdio_write(tp, 0x06, 0xea00);
            mdio_write(tp, 0x06, 0xeef8);
            mdio_write(tp, 0x06, 0xeb00);
            mdio_write(tp, 0x06, 0xe2f8);
            mdio_write(tp, 0x06, 0x7ce3);
            mdio_write(tp, 0x06, 0xf87d);
            mdio_write(tp, 0x06, 0xa511);
            mdio_write(tp, 0x06, 0x1112);
            mdio_write(tp, 0x06, 0xd240);
            mdio_write(tp, 0x06, 0xd644);
            mdio_write(tp, 0x06, 0x4402);
            mdio_write(tp, 0x06, 0x8217);
            mdio_write(tp, 0x06, 0xd2a0);
            mdio_write(tp, 0x06, 0xd6aa);
            mdio_write(tp, 0x06, 0xaa02);
            mdio_write(tp, 0x06, 0x8217);
            mdio_write(tp, 0x06, 0xae0f);
            mdio_write(tp, 0x06, 0xa544);
            mdio_write(tp, 0x06, 0x4402);
            mdio_write(tp, 0x06, 0xae4d);
            mdio_write(tp, 0x06, 0xa5aa);
            mdio_write(tp, 0x06, 0xaa02);
            mdio_write(tp, 0x06, 0xae47);
            mdio_write(tp, 0x06, 0xaf82);
            mdio_write(tp, 0x06, 0x13ee);
            mdio_write(tp, 0x06, 0x834e);
            mdio_write(tp, 0x06, 0x00ee);
            mdio_write(tp, 0x06, 0x834d);
            mdio_write(tp, 0x06, 0x0fee);
            mdio_write(tp, 0x06, 0x834c);
            mdio_write(tp, 0x06, 0x0fee);
            mdio_write(tp, 0x06, 0x834f);
            mdio_write(tp, 0x06, 0x00ee);
            mdio_write(tp, 0x06, 0x8351);
            mdio_write(tp, 0x06, 0x00ee);
            mdio_write(tp, 0x06, 0x834a);
            mdio_write(tp, 0x06, 0xffee);
            mdio_write(tp, 0x06, 0x834b);
            mdio_write(tp, 0x06, 0xffe0);
            mdio_write(tp, 0x06, 0x8330);
            mdio_write(tp, 0x06, 0xe183);
            mdio_write(tp, 0x06, 0x3158);
            mdio_write(tp, 0x06, 0xfee4);
            mdio_write(tp, 0x06, 0xf88a);
            mdio_write(tp, 0x06, 0xe5f8);
            mdio_write(tp, 0x06, 0x8be0);
            mdio_write(tp, 0x06, 0x8332);
            mdio_write(tp, 0x06, 0xe183);
            mdio_write(tp, 0x06, 0x3359);
            mdio_write(tp, 0x06, 0x0fe2);
            mdio_write(tp, 0x06, 0x834d);
            mdio_write(tp, 0x06, 0x0c24);
            mdio_write(tp, 0x06, 0x5af0);
            mdio_write(tp, 0x06, 0x1e12);
            mdio_write(tp, 0x06, 0xe4f8);
            mdio_write(tp, 0x06, 0x8ce5);
            mdio_write(tp, 0x06, 0xf88d);
            mdio_write(tp, 0x06, 0xaf82);
            mdio_write(tp, 0x06, 0x13e0);
            mdio_write(tp, 0x06, 0x834f);
            mdio_write(tp, 0x06, 0x10e4);
            mdio_write(tp, 0x06, 0x834f);
            mdio_write(tp, 0x06, 0xe083);
            mdio_write(tp, 0x06, 0x4e78);
            mdio_write(tp, 0x06, 0x009f);
            mdio_write(tp, 0x06, 0x0ae0);
            mdio_write(tp, 0x06, 0x834f);
            mdio_write(tp, 0x06, 0xa010);
            mdio_write(tp, 0x06, 0xa5ee);
            mdio_write(tp, 0x06, 0x834e);
            mdio_write(tp, 0x06, 0x01e0);
            mdio_write(tp, 0x06, 0x834e);
            mdio_write(tp, 0x06, 0x7805);
            mdio_write(tp, 0x06, 0x9e9a);
            mdio_write(tp, 0x06, 0xe083);
            mdio_write(tp, 0x06, 0x4e78);
            mdio_write(tp, 0x06, 0x049e);
            mdio_write(tp, 0x06, 0x10e0);
            mdio_write(tp, 0x06, 0x834e);
            mdio_write(tp, 0x06, 0x7803);
            mdio_write(tp, 0x06, 0x9e0f);
            mdio_write(tp, 0x06, 0xe083);
            mdio_write(tp, 0x06, 0x4e78);
            mdio_write(tp, 0x06, 0x019e);
            mdio_write(tp, 0x06, 0x05ae);
            mdio_write(tp, 0x06, 0x0caf);
            mdio_write(tp, 0x06, 0x81f8);
            mdio_write(tp, 0x06, 0xaf81);
            mdio_write(tp, 0x06, 0xa3af);
            mdio_write(tp, 0x06, 0x81dc);
            mdio_write(tp, 0x06, 0xaf82);
            mdio_write(tp, 0x06, 0x13ee);
            mdio_write(tp, 0x06, 0x8348);
            mdio_write(tp, 0x06, 0x00ee);
            mdio_write(tp, 0x06, 0x8349);
            mdio_write(tp, 0x06, 0x00e0);
            mdio_write(tp, 0x06, 0x8351);
            mdio_write(tp, 0x06, 0x10e4);
            mdio_write(tp, 0x06, 0x8351);
            mdio_write(tp, 0x06, 0x5801);
            mdio_write(tp, 0x06, 0x9fea);
            mdio_write(tp, 0x06, 0xd000);
            mdio_write(tp, 0x06, 0xd180);
            mdio_write(tp, 0x06, 0x1f66);
            mdio_write(tp, 0x06, 0xe2f8);
            mdio_write(tp, 0x06, 0xeae3);
            mdio_write(tp, 0x06, 0xf8eb);
            mdio_write(tp, 0x06, 0x5af8);
            mdio_write(tp, 0x06, 0x1e20);
            mdio_write(tp, 0x06, 0xe6f8);
            mdio_write(tp, 0x06, 0xeae5);
            mdio_write(tp, 0x06, 0xf8eb);
            mdio_write(tp, 0x06, 0xd302);
            mdio_write(tp, 0x06, 0xb3fe);
            mdio_write(tp, 0x06, 0xe2f8);
            mdio_write(tp, 0x06, 0x7cef);
            mdio_write(tp, 0x06, 0x325b);
            mdio_write(tp, 0x06, 0x80e3);
            mdio_write(tp, 0x06, 0xf87d);
            mdio_write(tp, 0x06, 0x9e03);
            mdio_write(tp, 0x06, 0x7dff);
            mdio_write(tp, 0x06, 0xff0d);
            mdio_write(tp, 0x06, 0x581c);
            mdio_write(tp, 0x06, 0x551a);
            mdio_write(tp, 0x06, 0x6511);
            mdio_write(tp, 0x06, 0xa190);
            mdio_write(tp, 0x06, 0xd3e2);
            mdio_write(tp, 0x06, 0x8348);
            mdio_write(tp, 0x06, 0xe383);
            mdio_write(tp, 0x06, 0x491b);
            mdio_write(tp, 0x06, 0x56ab);
            mdio_write(tp, 0x06, 0x08ef);
            mdio_write(tp, 0x06, 0x56e6);
            mdio_write(tp, 0x06, 0x8348);
            mdio_write(tp, 0x06, 0xe783);
            mdio_write(tp, 0x06, 0x4910);
            mdio_write(tp, 0x06, 0xd180);
            mdio_write(tp, 0x06, 0x1f66);
            mdio_write(tp, 0x06, 0xa004);
            mdio_write(tp, 0x06, 0xb9e2);
            mdio_write(tp, 0x06, 0x8348);
            mdio_write(tp, 0x06, 0xe383);
            mdio_write(tp, 0x06, 0x49ef);
            mdio_write(tp, 0x06, 0x65e2);
            mdio_write(tp, 0x06, 0x834a);
            mdio_write(tp, 0x06, 0xe383);
            mdio_write(tp, 0x06, 0x4b1b);
            mdio_write(tp, 0x06, 0x56aa);
            mdio_write(tp, 0x06, 0x0eef);
            mdio_write(tp, 0x06, 0x56e6);
            mdio_write(tp, 0x06, 0x834a);
            mdio_write(tp, 0x06, 0xe783);
            mdio_write(tp, 0x06, 0x4be2);
            mdio_write(tp, 0x06, 0x834d);
            mdio_write(tp, 0x06, 0xe683);
            mdio_write(tp, 0x06, 0x4ce0);
            mdio_write(tp, 0x06, 0x834d);
            mdio_write(tp, 0x06, 0xa000);
            mdio_write(tp, 0x06, 0x0caf);
            mdio_write(tp, 0x06, 0x81dc);
            mdio_write(tp, 0x06, 0xe083);
            mdio_write(tp, 0x06, 0x4d10);
            mdio_write(tp, 0x06, 0xe483);
            mdio_write(tp, 0x06, 0x4dae);
            mdio_write(tp, 0x06, 0x0480);
            mdio_write(tp, 0x06, 0xe483);
            mdio_write(tp, 0x06, 0x4de0);
            mdio_write(tp, 0x06, 0x834e);
            mdio_write(tp, 0x06, 0x7803);
            mdio_write(tp, 0x06, 0x9e0b);
            mdio_write(tp, 0x06, 0xe083);
            mdio_write(tp, 0x06, 0x4e78);
            mdio_write(tp, 0x06, 0x049e);
            mdio_write(tp, 0x06, 0x04ee);
            mdio_write(tp, 0x06, 0x834e);
            mdio_write(tp, 0x06, 0x02e0);
            mdio_write(tp, 0x06, 0x8332);
            mdio_write(tp, 0x06, 0xe183);
            mdio_write(tp, 0x06, 0x3359);
            mdio_write(tp, 0x06, 0x0fe2);
            mdio_write(tp, 0x06, 0x834d);
            mdio_write(tp, 0x06, 0x0c24);
            mdio_write(tp, 0x06, 0x5af0);
            mdio_write(tp, 0x06, 0x1e12);
            mdio_write(tp, 0x06, 0xe4f8);
            mdio_write(tp, 0x06, 0x8ce5);
            mdio_write(tp, 0x06, 0xf88d);
            mdio_write(tp, 0x06, 0xe083);
            mdio_write(tp, 0x06, 0x30e1);
            mdio_write(tp, 0x06, 0x8331);
            mdio_write(tp, 0x06, 0x6801);
            mdio_write(tp, 0x06, 0xe4f8);
            mdio_write(tp, 0x06, 0x8ae5);
            mdio_write(tp, 0x06, 0xf88b);
            mdio_write(tp, 0x06, 0xae37);
            mdio_write(tp, 0x06, 0xee83);
            mdio_write(tp, 0x06, 0x4e03);
            mdio_write(tp, 0x06, 0xe083);
            mdio_write(tp, 0x06, 0x4ce1);
            mdio_write(tp, 0x06, 0x834d);
            mdio_write(tp, 0x06, 0x1b01);
            mdio_write(tp, 0x06, 0x9e04);
            mdio_write(tp, 0x06, 0xaaa1);
            mdio_write(tp, 0x06, 0xaea8);
            mdio_write(tp, 0x06, 0xee83);
            mdio_write(tp, 0x06, 0x4e04);
            mdio_write(tp, 0x06, 0xee83);
            mdio_write(tp, 0x06, 0x4f00);
            mdio_write(tp, 0x06, 0xaeab);
            mdio_write(tp, 0x06, 0xe083);
            mdio_write(tp, 0x06, 0x4f78);
            mdio_write(tp, 0x06, 0x039f);
            mdio_write(tp, 0x06, 0x14ee);
            mdio_write(tp, 0x06, 0x834e);
            mdio_write(tp, 0x06, 0x05d2);
            mdio_write(tp, 0x06, 0x40d6);
            mdio_write(tp, 0x06, 0x5554);
            mdio_write(tp, 0x06, 0x0282);
            mdio_write(tp, 0x06, 0x17d2);
            mdio_write(tp, 0x06, 0xa0d6);
            mdio_write(tp, 0x06, 0xba00);
            mdio_write(tp, 0x06, 0x0282);
            mdio_write(tp, 0x06, 0x17fe);
            mdio_write(tp, 0x06, 0xfdfc);
            mdio_write(tp, 0x06, 0x05f8);
            mdio_write(tp, 0x06, 0xe0f8);
            mdio_write(tp, 0x06, 0x60e1);
            mdio_write(tp, 0x06, 0xf861);
            mdio_write(tp, 0x06, 0x6802);
            mdio_write(tp, 0x06, 0xe4f8);
            mdio_write(tp, 0x06, 0x60e5);
            mdio_write(tp, 0x06, 0xf861);
            mdio_write(tp, 0x06, 0xe0f8);
            mdio_write(tp, 0x06, 0x48e1);
            mdio_write(tp, 0x06, 0xf849);
            mdio_write(tp, 0x06, 0x580f);
            mdio_write(tp, 0x06, 0x1e02);
            mdio_write(tp, 0x06, 0xe4f8);
            mdio_write(tp, 0x06, 0x48e5);
            mdio_write(tp, 0x06, 0xf849);
            mdio_write(tp, 0x06, 0xd000);
            mdio_write(tp, 0x06, 0x0282);
            mdio_write(tp, 0x06, 0x5bbf);
            mdio_write(tp, 0x06, 0x8350);
            mdio_write(tp, 0x06, 0xef46);
            mdio_write(tp, 0x06, 0xdc19);
            mdio_write(tp, 0x06, 0xddd0);
            mdio_write(tp, 0x06, 0x0102);
            mdio_write(tp, 0x06, 0x825b);
            mdio_write(tp, 0x06, 0x0282);
            mdio_write(tp, 0x06, 0x77e0);
            mdio_write(tp, 0x06, 0xf860);
            mdio_write(tp, 0x06, 0xe1f8);
            mdio_write(tp, 0x06, 0x6158);
            mdio_write(tp, 0x06, 0xfde4);
            mdio_write(tp, 0x06, 0xf860);
            mdio_write(tp, 0x06, 0xe5f8);
            mdio_write(tp, 0x06, 0x61fc);
            mdio_write(tp, 0x06, 0x04f9);
            mdio_write(tp, 0x06, 0xfafb);
            mdio_write(tp, 0x06, 0xc6bf);
            mdio_write(tp, 0x06, 0xf840);
            mdio_write(tp, 0x06, 0xbe83);
            mdio_write(tp, 0x06, 0x50a0);
            mdio_write(tp, 0x06, 0x0101);
            mdio_write(tp, 0x06, 0x071b);
            mdio_write(tp, 0x06, 0x89cf);
            mdio_write(tp, 0x06, 0xd208);
            mdio_write(tp, 0x06, 0xebdb);
            mdio_write(tp, 0x06, 0x19b2);
            mdio_write(tp, 0x06, 0xfbff);
            mdio_write(tp, 0x06, 0xfefd);
            mdio_write(tp, 0x06, 0x04f8);
            mdio_write(tp, 0x06, 0xe0f8);
            mdio_write(tp, 0x06, 0x48e1);
            mdio_write(tp, 0x06, 0xf849);
            mdio_write(tp, 0x06, 0x6808);
            mdio_write(tp, 0x06, 0xe4f8);
            mdio_write(tp, 0x06, 0x48e5);
            mdio_write(tp, 0x06, 0xf849);
            mdio_write(tp, 0x06, 0x58f7);
            mdio_write(tp, 0x06, 0xe4f8);
            mdio_write(tp, 0x06, 0x48e5);
            mdio_write(tp, 0x06, 0xf849);
            mdio_write(tp, 0x06, 0xfc04);
            mdio_write(tp, 0x06, 0x4d20);
            mdio_write(tp, 0x06, 0x0002);
            mdio_write(tp, 0x06, 0x4e22);
            mdio_write(tp, 0x06, 0x0002);
            mdio_write(tp, 0x06, 0x4ddf);
            mdio_write(tp, 0x06, 0xff01);
            mdio_write(tp, 0x06, 0x4edd);
            mdio_write(tp, 0x06, 0xff01);
            mdio_write(tp, 0x06, 0xf8fa);
            mdio_write(tp, 0x06, 0xfbef);
            mdio_write(tp, 0x06, 0x79bf);
            mdio_write(tp, 0x06, 0xf822);
            mdio_write(tp, 0x06, 0xd819);
            mdio_write(tp, 0x06, 0xd958);
            mdio_write(tp, 0x06, 0x849f);
            mdio_write(tp, 0x06, 0x09bf);
            mdio_write(tp, 0x06, 0x82be);
            mdio_write(tp, 0x06, 0xd682);
            mdio_write(tp, 0x06, 0xc602);
            mdio_write(tp, 0x06, 0x014f);
            mdio_write(tp, 0x06, 0xef97);
            mdio_write(tp, 0x06, 0xfffe);
            mdio_write(tp, 0x06, 0xfc05);
            mdio_write(tp, 0x06, 0x17ff);
            mdio_write(tp, 0x06, 0xfe01);
            mdio_write(tp, 0x06, 0x1700);
            mdio_write(tp, 0x06, 0x0102);
            mdio_write(tp, 0x05, 0x83d8);
            mdio_write(tp, 0x06, 0x8051);
            mdio_write(tp, 0x05, 0x83d6);
            mdio_write(tp, 0x06, 0x82a0);
            mdio_write(tp, 0x05, 0x83d4);
            mdio_write(tp, 0x06, 0x8000);
            mdio_write(tp, 0x02, 0x2010);
            mdio_write(tp, 0x03, 0xdc00);
            mdio_write(tp, 0x1f, 0x0000);
            mdio_write(tp, 0x0b, 0x0600);
            mdio_write(tp, 0x1f, 0x0005);
            mdio_write(tp, 0x05, 0xfff6);
            mdio_write(tp, 0x06, 0x00fc);
            mdio_write(tp, 0x1f, 0x0000);
        }

        mdio_write(tp, 0x1F, 0x0000);
        mdio_write(tp, 0x0D, 0xF880);
        mdio_write(tp, 0x1F, 0x0000);
    } else if (tp->mcfg == CFG_METHOD_10) {
        mdio_write(tp, 0x1F, 0x0001);
        mdio_write(tp, 0x06, 0x4064);
        mdio_write(tp, 0x07, 0x2863);
        mdio_write(tp, 0x08, 0x059C);
        mdio_write(tp, 0x09, 0x26B4);
        mdio_write(tp, 0x0A, 0x6A19);
        mdio_write(tp, 0x0B, 0xDCC8);
        mdio_write(tp, 0x10, 0xF06D);
        mdio_write(tp, 0x14, 0x7F68);
        mdio_write(tp, 0x18, 0x7FD9);
        mdio_write(tp, 0x1C, 0xF0FF);
        mdio_write(tp, 0x1D, 0x3D9C);
        mdio_write(tp, 0x1F, 0x0003);
        mdio_write(tp, 0x12, 0xF49F);
        mdio_write(tp, 0x13, 0x070B);
        mdio_write(tp, 0x1A, 0x05AD);
        mdio_write(tp, 0x14, 0x94C0);

        mdio_write(tp, 0x1F, 0x0002);
        mdio_write(tp, 0x06, 0x5561);
        mdio_write(tp, 0x1F, 0x0005);
        mdio_write(tp, 0x05, 0x8332);
        mdio_write(tp, 0x06, 0x5561);

        if (rtl8168_efuse_read(tp, 0x01) == 0xb1) {
            mdio_write(tp, 0x1F, 0x0002);
            mdio_write(tp, 0x05, 0x669A);
            mdio_write(tp, 0x1F, 0x0005);
            mdio_write(tp, 0x05, 0x8330);
            mdio_write(tp, 0x06, 0x669A);

            mdio_write(tp, 0x1F, 0x0002);
            gphy_val = mdio_read(tp, 0x0D);
            if ((gphy_val & 0x00FF) != 0x006C) {
                gphy_val &= 0xFF00;
                mdio_write(tp, 0x1F, 0x0002);
                mdio_write(tp, 0x0D, gphy_val | 0x0065);
                mdio_write(tp, 0x0D, gphy_val | 0x0066);
                mdio_write(tp, 0x0D, gphy_val | 0x0067);
                mdio_write(tp, 0x0D, gphy_val | 0x0068);
                mdio_write(tp, 0x0D, gphy_val | 0x0069);
                mdio_write(tp, 0x0D, gphy_val | 0x006A);
                mdio_write(tp, 0x0D, gphy_val | 0x006B);
                mdio_write(tp, 0x0D, gphy_val | 0x006C);
            }
        } else {
            mdio_write(tp, 0x1F, 0x0002);
            mdio_write(tp, 0x05, 0x2642);
            mdio_write(tp, 0x1F, 0x0005);
            mdio_write(tp, 0x05, 0x8330);
            mdio_write(tp, 0x06, 0x2642);
        }

        if (rtl8168_efuse_read(tp, 0x30) == 0x98) {
            mdio_write(tp, 0x1F, 0x0000);
            mdio_write(tp, 0x11, mdio_read(tp, 0x11) & ~BIT_1);
            mdio_write(tp, 0x1F, 0x0005);
            mdio_write(tp, 0x01, mdio_read(tp, 0x01) | BIT_9);
        } else if (rtl8168_efuse_read(tp, 0x30) == 0x90) {
            mdio_write(tp, 0x1F, 0x0005);
            mdio_write(tp, 0x01, mdio_read(tp, 0x01) & ~BIT_9);
            mdio_write(tp, 0x1F, 0x0000);
            mdio_write(tp, 0x16, 0x5101);
        }

        mdio_write(tp, 0x1F, 0x0002);
        gphy_val = mdio_read(tp, 0x02);
        gphy_val &= ~BIT_10;
        gphy_val &= ~BIT_9;
        gphy_val |= BIT_8;
        mdio_write(tp, 0x02, gphy_val);
        gphy_val = mdio_read(tp, 0x03);
        gphy_val &= ~BIT_15;
        gphy_val &= ~BIT_14;
        gphy_val &= ~BIT_13;
        mdio_write(tp, 0x03, gphy_val);

        mdio_write(tp, 0x1F, 0x0001);
        mdio_write(tp, 0x17, 0x0CC0);

        mdio_write(tp, 0x1F, 0x0002);
        gphy_val = mdio_read(tp, 0x0F);
        gphy_val |= BIT_4;
        gphy_val |= BIT_2;
        gphy_val |= BIT_1;
        gphy_val |= BIT_0;
        mdio_write(tp, 0x0F, gphy_val);

        mdio_write(tp, 0x1F, 0x0005);
        mdio_write(tp, 0x05, 0x001B);
        if (mdio_read(tp, 0x06) == 0xB300) {
            mdio_write(tp, 0x1f, 0x0005);
            mdio_write(tp, 0x05, 0xfff6);
            mdio_write(tp, 0x06, 0x0080);
            mdio_write(tp, 0x05, 0x8000);
            mdio_write(tp, 0x06, 0xf8f9);
            mdio_write(tp, 0x06, 0xfaee);
            mdio_write(tp, 0x06, 0xf8ea);
            mdio_write(tp, 0x06, 0x00ee);
            mdio_write(tp, 0x06, 0xf8eb);
            mdio_write(tp, 0x06, 0x00e2);
            mdio_write(tp, 0x06, 0xf87c);
            mdio_write(tp, 0x06, 0xe3f8);
            mdio_write(tp, 0x06, 0x7da5);
            mdio_write(tp, 0x06, 0x1111);
            mdio_write(tp, 0x06, 0x12d2);
            mdio_write(tp, 0x06, 0x40d6);
            mdio_write(tp, 0x06, 0x4444);
            mdio_write(tp, 0x06, 0x0281);
            mdio_write(tp, 0x06, 0xc6d2);
            mdio_write(tp, 0x06, 0xa0d6);
            mdio_write(tp, 0x06, 0xaaaa);
            mdio_write(tp, 0x06, 0x0281);
            mdio_write(tp, 0x06, 0xc6ae);
            mdio_write(tp, 0x06, 0x0fa5);
            mdio_write(tp, 0x06, 0x4444);
            mdio_write(tp, 0x06, 0x02ae);
            mdio_write(tp, 0x06, 0x4da5);
            mdio_write(tp, 0x06, 0xaaaa);
            mdio_write(tp, 0x06, 0x02ae);
            mdio_write(tp, 0x06, 0x47af);
            mdio_write(tp, 0x06, 0x81c2);
            mdio_write(tp, 0x06, 0xee83);
            mdio_write(tp, 0x06, 0x4e00);
            mdio_write(tp, 0x06, 0xee83);
            mdio_write(tp, 0x06, 0x4d0f);
            mdio_write(tp, 0x06, 0xee83);
            mdio_write(tp, 0x06, 0x4c0f);
            mdio_write(tp, 0x06, 0xee83);
            mdio_write(tp, 0x06, 0x4f00);
            mdio_write(tp, 0x06, 0xee83);
            mdio_write(tp, 0x06, 0x5100);
            mdio_write(tp, 0x06, 0xee83);
            mdio_write(tp, 0x06, 0x4aff);
            mdio_write(tp, 0x06, 0xee83);
            mdio_write(tp, 0x06, 0x4bff);
            mdio_write(tp, 0x06, 0xe083);
            mdio_write(tp, 0x06, 0x30e1);
            mdio_write(tp, 0x06, 0x8331);
            mdio_write(tp, 0x06, 0x58fe);
            mdio_write(tp, 0x06, 0xe4f8);
            mdio_write(tp, 0x06, 0x8ae5);
            mdio_write(tp, 0x06, 0xf88b);
            mdio_write(tp, 0x06, 0xe083);
            mdio_write(tp, 0x06, 0x32e1);
            mdio_write(tp, 0x06, 0x8333);
            mdio_write(tp, 0x06, 0x590f);
            mdio_write(tp, 0x06, 0xe283);
            mdio_write(tp, 0x06, 0x4d0c);
            mdio_write(tp, 0x06, 0x245a);
            mdio_write(tp, 0x06, 0xf01e);
            mdio_write(tp, 0x06, 0x12e4);
            mdio_write(tp, 0x06, 0xf88c);
            mdio_write(tp, 0x06, 0xe5f8);
            mdio_write(tp, 0x06, 0x8daf);
            mdio_write(tp, 0x06, 0x81c2);
            mdio_write(tp, 0x06, 0xe083);
            mdio_write(tp, 0x06, 0x4f10);
            mdio_write(tp, 0x06, 0xe483);
            mdio_write(tp, 0x06, 0x4fe0);
            mdio_write(tp, 0x06, 0x834e);
            mdio_write(tp, 0x06, 0x7800);
            mdio_write(tp, 0x06, 0x9f0a);
            mdio_write(tp, 0x06, 0xe083);
            mdio_write(tp, 0x06, 0x4fa0);
            mdio_write(tp, 0x06, 0x10a5);
            mdio_write(tp, 0x06, 0xee83);
            mdio_write(tp, 0x06, 0x4e01);
            mdio_write(tp, 0x06, 0xe083);
            mdio_write(tp, 0x06, 0x4e78);
            mdio_write(tp, 0x06, 0x059e);
            mdio_write(tp, 0x06, 0x9ae0);
            mdio_write(tp, 0x06, 0x834e);
            mdio_write(tp, 0x06, 0x7804);
            mdio_write(tp, 0x06, 0x9e10);
            mdio_write(tp, 0x06, 0xe083);
            mdio_write(tp, 0x06, 0x4e78);
            mdio_write(tp, 0x06, 0x039e);
            mdio_write(tp, 0x06, 0x0fe0);
            mdio_write(tp, 0x06, 0x834e);
            mdio_write(tp, 0x06, 0x7801);
            mdio_write(tp, 0x06, 0x9e05);
            mdio_write(tp, 0x06, 0xae0c);
            mdio_write(tp, 0x06, 0xaf81);
            mdio_write(tp, 0x06, 0xa7af);
            mdio_write(tp, 0x06, 0x8152);
            mdio_write(tp, 0x06, 0xaf81);
            mdio_write(tp, 0x06, 0x8baf);
            mdio_write(tp, 0x06, 0x81c2);
            mdio_write(tp, 0x06, 0xee83);
            mdio_write(tp, 0x06, 0x4800);
            mdio_write(tp, 0x06, 0xee83);
            mdio_write(tp, 0x06, 0x4900);
            mdio_write(tp, 0x06, 0xe083);
            mdio_write(tp, 0x06, 0x5110);
            mdio_write(tp, 0x06, 0xe483);
            mdio_write(tp, 0x06, 0x5158);
            mdio_write(tp, 0x06, 0x019f);
            mdio_write(tp, 0x06, 0xead0);
            mdio_write(tp, 0x06, 0x00d1);
            mdio_write(tp, 0x06, 0x801f);
            mdio_write(tp, 0x06, 0x66e2);
            mdio_write(tp, 0x06, 0xf8ea);
            mdio_write(tp, 0x06, 0xe3f8);
            mdio_write(tp, 0x06, 0xeb5a);
            mdio_write(tp, 0x06, 0xf81e);
            mdio_write(tp, 0x06, 0x20e6);
            mdio_write(tp, 0x06, 0xf8ea);
            mdio_write(tp, 0x06, 0xe5f8);
            mdio_write(tp, 0x06, 0xebd3);
            mdio_write(tp, 0x06, 0x02b3);
            mdio_write(tp, 0x06, 0xfee2);
            mdio_write(tp, 0x06, 0xf87c);
            mdio_write(tp, 0x06, 0xef32);
            mdio_write(tp, 0x06, 0x5b80);
            mdio_write(tp, 0x06, 0xe3f8);
            mdio_write(tp, 0x06, 0x7d9e);
            mdio_write(tp, 0x06, 0x037d);
            mdio_write(tp, 0x06, 0xffff);
            mdio_write(tp, 0x06, 0x0d58);
            mdio_write(tp, 0x06, 0x1c55);
            mdio_write(tp, 0x06, 0x1a65);
            mdio_write(tp, 0x06, 0x11a1);
            mdio_write(tp, 0x06, 0x90d3);
            mdio_write(tp, 0x06, 0xe283);
            mdio_write(tp, 0x06, 0x48e3);
            mdio_write(tp, 0x06, 0x8349);
            mdio_write(tp, 0x06, 0x1b56);
            mdio_write(tp, 0x06, 0xab08);
            mdio_write(tp, 0x06, 0xef56);
            mdio_write(tp, 0x06, 0xe683);
            mdio_write(tp, 0x06, 0x48e7);
            mdio_write(tp, 0x06, 0x8349);
            mdio_write(tp, 0x06, 0x10d1);
            mdio_write(tp, 0x06, 0x801f);
            mdio_write(tp, 0x06, 0x66a0);
            mdio_write(tp, 0x06, 0x04b9);
            mdio_write(tp, 0x06, 0xe283);
            mdio_write(tp, 0x06, 0x48e3);
            mdio_write(tp, 0x06, 0x8349);
            mdio_write(tp, 0x06, 0xef65);
            mdio_write(tp, 0x06, 0xe283);
            mdio_write(tp, 0x06, 0x4ae3);
            mdio_write(tp, 0x06, 0x834b);
            mdio_write(tp, 0x06, 0x1b56);
            mdio_write(tp, 0x06, 0xaa0e);
            mdio_write(tp, 0x06, 0xef56);
            mdio_write(tp, 0x06, 0xe683);
            mdio_write(tp, 0x06, 0x4ae7);
            mdio_write(tp, 0x06, 0x834b);
            mdio_write(tp, 0x06, 0xe283);
            mdio_write(tp, 0x06, 0x4de6);
            mdio_write(tp, 0x06, 0x834c);
            mdio_write(tp, 0x06, 0xe083);
            mdio_write(tp, 0x06, 0x4da0);
            mdio_write(tp, 0x06, 0x000c);
            mdio_write(tp, 0x06, 0xaf81);
            mdio_write(tp, 0x06, 0x8be0);
            mdio_write(tp, 0x06, 0x834d);
            mdio_write(tp, 0x06, 0x10e4);
            mdio_write(tp, 0x06, 0x834d);
            mdio_write(tp, 0x06, 0xae04);
            mdio_write(tp, 0x06, 0x80e4);
            mdio_write(tp, 0x06, 0x834d);
            mdio_write(tp, 0x06, 0xe083);
            mdio_write(tp, 0x06, 0x4e78);
            mdio_write(tp, 0x06, 0x039e);
            mdio_write(tp, 0x06, 0x0be0);
            mdio_write(tp, 0x06, 0x834e);
            mdio_write(tp, 0x06, 0x7804);
            mdio_write(tp, 0x06, 0x9e04);
            mdio_write(tp, 0x06, 0xee83);
            mdio_write(tp, 0x06, 0x4e02);
            mdio_write(tp, 0x06, 0xe083);
            mdio_write(tp, 0x06, 0x32e1);
            mdio_write(tp, 0x06, 0x8333);
            mdio_write(tp, 0x06, 0x590f);
            mdio_write(tp, 0x06, 0xe283);
            mdio_write(tp, 0x06, 0x4d0c);
            mdio_write(tp, 0x06, 0x245a);
            mdio_write(tp, 0x06, 0xf01e);
            mdio_write(tp, 0x06, 0x12e4);
            mdio_write(tp, 0x06, 0xf88c);
            mdio_write(tp, 0x06, 0xe5f8);
            mdio_write(tp, 0x06, 0x8de0);
            mdio_write(tp, 0x06, 0x8330);
            mdio_write(tp, 0x06, 0xe183);
            mdio_write(tp, 0x06, 0x3168);
            mdio_write(tp, 0x06, 0x01e4);
            mdio_write(tp, 0x06, 0xf88a);
            mdio_write(tp, 0x06, 0xe5f8);
            mdio_write(tp, 0x06, 0x8bae);
            mdio_write(tp, 0x06, 0x37ee);
            mdio_write(tp, 0x06, 0x834e);
            mdio_write(tp, 0x06, 0x03e0);
            mdio_write(tp, 0x06, 0x834c);
            mdio_write(tp, 0x06, 0xe183);
            mdio_write(tp, 0x06, 0x4d1b);
            mdio_write(tp, 0x06, 0x019e);
            mdio_write(tp, 0x06, 0x04aa);
            mdio_write(tp, 0x06, 0xa1ae);
            mdio_write(tp, 0x06, 0xa8ee);
            mdio_write(tp, 0x06, 0x834e);
            mdio_write(tp, 0x06, 0x04ee);
            mdio_write(tp, 0x06, 0x834f);
            mdio_write(tp, 0x06, 0x00ae);
            mdio_write(tp, 0x06, 0xabe0);
            mdio_write(tp, 0x06, 0x834f);
            mdio_write(tp, 0x06, 0x7803);
            mdio_write(tp, 0x06, 0x9f14);
            mdio_write(tp, 0x06, 0xee83);
            mdio_write(tp, 0x06, 0x4e05);
            mdio_write(tp, 0x06, 0xd240);
            mdio_write(tp, 0x06, 0xd655);
            mdio_write(tp, 0x06, 0x5402);
            mdio_write(tp, 0x06, 0x81c6);
            mdio_write(tp, 0x06, 0xd2a0);
            mdio_write(tp, 0x06, 0xd6ba);
            mdio_write(tp, 0x06, 0x0002);
            mdio_write(tp, 0x06, 0x81c6);
            mdio_write(tp, 0x06, 0xfefd);
            mdio_write(tp, 0x06, 0xfc05);
            mdio_write(tp, 0x06, 0xf8e0);
            mdio_write(tp, 0x06, 0xf860);
            mdio_write(tp, 0x06, 0xe1f8);
            mdio_write(tp, 0x06, 0x6168);
            mdio_write(tp, 0x06, 0x02e4);
            mdio_write(tp, 0x06, 0xf860);
            mdio_write(tp, 0x06, 0xe5f8);
            mdio_write(tp, 0x06, 0x61e0);
            mdio_write(tp, 0x06, 0xf848);
            mdio_write(tp, 0x06, 0xe1f8);
            mdio_write(tp, 0x06, 0x4958);
            mdio_write(tp, 0x06, 0x0f1e);
            mdio_write(tp, 0x06, 0x02e4);
            mdio_write(tp, 0x06, 0xf848);
            mdio_write(tp, 0x06, 0xe5f8);
            mdio_write(tp, 0x06, 0x49d0);
            mdio_write(tp, 0x06, 0x0002);
            mdio_write(tp, 0x06, 0x820a);
            mdio_write(tp, 0x06, 0xbf83);
            mdio_write(tp, 0x06, 0x50ef);
            mdio_write(tp, 0x06, 0x46dc);
            mdio_write(tp, 0x06, 0x19dd);
            mdio_write(tp, 0x06, 0xd001);
            mdio_write(tp, 0x06, 0x0282);
            mdio_write(tp, 0x06, 0x0a02);
            mdio_write(tp, 0x06, 0x8226);
            mdio_write(tp, 0x06, 0xe0f8);
            mdio_write(tp, 0x06, 0x60e1);
            mdio_write(tp, 0x06, 0xf861);
            mdio_write(tp, 0x06, 0x58fd);
            mdio_write(tp, 0x06, 0xe4f8);
            mdio_write(tp, 0x06, 0x60e5);
            mdio_write(tp, 0x06, 0xf861);
            mdio_write(tp, 0x06, 0xfc04);
            mdio_write(tp, 0x06, 0xf9fa);
            mdio_write(tp, 0x06, 0xfbc6);
            mdio_write(tp, 0x06, 0xbff8);
            mdio_write(tp, 0x06, 0x40be);
            mdio_write(tp, 0x06, 0x8350);
            mdio_write(tp, 0x06, 0xa001);
            mdio_write(tp, 0x06, 0x0107);
            mdio_write(tp, 0x06, 0x1b89);
            mdio_write(tp, 0x06, 0xcfd2);
            mdio_write(tp, 0x06, 0x08eb);
            mdio_write(tp, 0x06, 0xdb19);
            mdio_write(tp, 0x06, 0xb2fb);
            mdio_write(tp, 0x06, 0xfffe);
            mdio_write(tp, 0x06, 0xfd04);
            mdio_write(tp, 0x06, 0xf8e0);
            mdio_write(tp, 0x06, 0xf848);
            mdio_write(tp, 0x06, 0xe1f8);
            mdio_write(tp, 0x06, 0x4968);
            mdio_write(tp, 0x06, 0x08e4);
            mdio_write(tp, 0x06, 0xf848);
            mdio_write(tp, 0x06, 0xe5f8);
            mdio_write(tp, 0x06, 0x4958);
            mdio_write(tp, 0x06, 0xf7e4);
            mdio_write(tp, 0x06, 0xf848);
            mdio_write(tp, 0x06, 0xe5f8);
            mdio_write(tp, 0x06, 0x49fc);
            mdio_write(tp, 0x06, 0x044d);
            mdio_write(tp, 0x06, 0x2000);
            mdio_write(tp, 0x06, 0x024e);
            mdio_write(tp, 0x06, 0x2200);
            mdio_write(tp, 0x06, 0x024d);
            mdio_write(tp, 0x06, 0xdfff);
            mdio_write(tp, 0x06, 0x014e);
            mdio_write(tp, 0x06, 0xddff);
            mdio_write(tp, 0x06, 0x01f8);
            mdio_write(tp, 0x06, 0xfafb);
            mdio_write(tp, 0x06, 0xef79);
            mdio_write(tp, 0x06, 0xbff8);
            mdio_write(tp, 0x06, 0x22d8);
            mdio_write(tp, 0x06, 0x19d9);
            mdio_write(tp, 0x06, 0x5884);
            mdio_write(tp, 0x06, 0x9f09);
            mdio_write(tp, 0x06, 0xbf82);
            mdio_write(tp, 0x06, 0x6dd6);
            mdio_write(tp, 0x06, 0x8275);
            mdio_write(tp, 0x06, 0x0201);
            mdio_write(tp, 0x06, 0x4fef);
            mdio_write(tp, 0x06, 0x97ff);
            mdio_write(tp, 0x06, 0xfefc);
            mdio_write(tp, 0x06, 0x0517);
            mdio_write(tp, 0x06, 0xfffe);
            mdio_write(tp, 0x06, 0x0117);
            mdio_write(tp, 0x06, 0x0001);
            mdio_write(tp, 0x06, 0x0200);
            mdio_write(tp, 0x05, 0x83d8);
            mdio_write(tp, 0x06, 0x8000);
            mdio_write(tp, 0x05, 0x83d6);
            mdio_write(tp, 0x06, 0x824f);
            mdio_write(tp, 0x02, 0x2010);
            mdio_write(tp, 0x03, 0xdc00);
            mdio_write(tp, 0x1f, 0x0000);
            mdio_write(tp, 0x0b, 0x0600);
            mdio_write(tp, 0x1f, 0x0005);
            mdio_write(tp, 0x05, 0xfff6);
            mdio_write(tp, 0x06, 0x00fc);
            mdio_write(tp, 0x1f, 0x0000);
        }

        mdio_write(tp, 0x1F, 0x0000);
        mdio_write(tp, 0x0D, 0xF880);
        mdio_write(tp, 0x1F, 0x0000);
    } else if (tp->mcfg == CFG_METHOD_11) {
        mdio_write(tp, 0x1F, 0x0002);
        mdio_write(tp, 0x10, 0x0008);
        mdio_write(tp, 0x0D, 0x006C);

        mdio_write(tp, 0x1F, 0x0001);
        mdio_write(tp, 0x17, 0x0CC0);

        mdio_write(tp, 0x1F, 0x0001);
        mdio_write(tp, 0x0B, 0xA4D8);
        mdio_write(tp, 0x09, 0x281C);
        mdio_write(tp, 0x07, 0x2883);
        mdio_write(tp, 0x0A, 0x6B35);
        mdio_write(tp, 0x1D, 0x3DA4);
        mdio_write(tp, 0x1C, 0xEFFD);
        mdio_write(tp, 0x14, 0x7F52);
        mdio_write(tp, 0x18, 0x7FC6);
        mdio_write(tp, 0x08, 0x0601);
        mdio_write(tp, 0x06, 0x4063);
        mdio_write(tp, 0x10, 0xF074);
        mdio_write(tp, 0x1F, 0x0003);
        mdio_write(tp, 0x13, 0x0789);
        mdio_write(tp, 0x12, 0xF4BD);
        mdio_write(tp, 0x1A, 0x04FD);
        mdio_write(tp, 0x14, 0x84B0);
        mdio_write(tp, 0x1F, 0x0000);
        mdio_write(tp, 0x00, 0x9200);

        mdio_write(tp, 0x1F, 0x0005);
        mdio_write(tp, 0x01, 0x0340);
        mdio_write(tp, 0x1F, 0x0001);
        mdio_write(tp, 0x04, 0x4000);
        mdio_write(tp, 0x03, 0x1D21);
        mdio_write(tp, 0x02, 0x0C32);
        mdio_write(tp, 0x01, 0x0200);
        mdio_write(tp, 0x00, 0x5554);
        mdio_write(tp, 0x04, 0x4800);
        mdio_write(tp, 0x04, 0x4000);
        mdio_write(tp, 0x04, 0xF000);
        mdio_write(tp, 0x03, 0xDF01);
        mdio_write(tp, 0x02, 0xDF20);
        mdio_write(tp, 0x01, 0x101A);
        mdio_write(tp, 0x00, 0xA0FF);
        mdio_write(tp, 0x04, 0xF800);
        mdio_write(tp, 0x04, 0xF000);
        mdio_write(tp, 0x1F, 0x0000);

        mdio_write(tp, 0x1F, 0x0007);
        mdio_write(tp, 0x1E, 0x0023);
        mdio_write(tp, 0x16, 0x0000);
        mdio_write(tp, 0x1F, 0x0000);

        gphy_val = mdio_read(tp, 0x0D);
        gphy_val |= BIT_5;
        mdio_write(tp, 0x0D, gphy_val);
    } else if (tp->mcfg == CFG_METHOD_12 || tp->mcfg == CFG_METHOD_13) {
        mdio_write(tp, 0x1F, 0x0001);
        mdio_write(tp, 0x17, 0x0CC0);

        mdio_write(tp, 0x1F, 0x0007);
        mdio_write(tp, 0x1E, 0x002D);
        mdio_write(tp, 0x18, 0x0040);

        mdio_write(tp, 0x1F, 0x0000);
        gphy_val = mdio_read(tp, 0x0D);
        gphy_val |= BIT_5;
        mdio_write(tp, 0x0D, gphy_val);

        mdio_write(tp, 0x1F, 0x0002);
        gphy_val = mdio_read(tp, 0x0C);
        gphy_val |= BIT_10;
        mdio_write(tp, 0x0C, gphy_val);
    } else if (tp->mcfg == CFG_METHOD_14 || tp->mcfg == CFG_METHOD_15) {
        mdio_write(tp, 0x1F, 0x0007);
        mdio_write(tp, 0x1E, 0x0023);
        gphy_val = mdio_read(tp, 0x17)|0x02;
        mdio_write(tp, 0x17, gphy_val);
        mdio_write(tp, 0x1F, 0x0000);

        mdio_write(tp, 0x1f, 0x0005);
        mdio_write(tp, 0x05, 0x8b80);
        mdio_write(tp, 0x06, 0xc896);
        mdio_write(tp, 0x1f, 0x0000);

        mdio_write(tp, 0x1F, 0x0001);
        mdio_write(tp, 0x0B, 0x6C20);
        mdio_write(tp, 0x07, 0x2872);
        mdio_write(tp, 0x1C, 0xEFFF);
        mdio_write(tp, 0x1F, 0x0003);
        mdio_write(tp, 0x14, 0x6420);
        mdio_write(tp, 0x1F, 0x0000);

        mdio_write(tp, 0x1F, 0x0002);
        gphy_val = mdio_read(tp, 0x08) & 0x00FF;
        mdio_write(tp, 0x08, gphy_val | 0x8000);
        mdio_write(tp, 0x1F, 0x0000);

        mdio_write(tp, 0x1F, 0x0007);
        mdio_write(tp, 0x1E, 0x002D);
        gphy_val = mdio_read(tp, 0x18);
        mdio_write(tp, 0x18, gphy_val | 0x0050);
        mdio_write(tp, 0x1F, 0x0000);
        gphy_val = mdio_read(tp, 0x14);
        mdio_write(tp, 0x14, gphy_val | 0x8000);

        mdio_write(tp, 0x1F, 0x0002);
        mdio_write(tp, 0x00, 0x080B);
        mdio_write(tp, 0x0B, 0x09D7);
        mdio_write(tp, 0x1f, 0x0000);
        mdio_write(tp, 0x15, 0x1006);

        mdio_write(tp, 0x1F, 0x0007);
        mdio_write(tp, 0x1E, 0x002F);
        mdio_write(tp, 0x15, 0x1919);
        mdio_write(tp, 0x1F, 0x0000);

        mdio_write(tp, 0x1F, 0x0005);
        mdio_write(tp, 0x05, 0x8B86);
        gphy_val = mdio_read(tp, 0x06);
        mdio_write(tp, 0x06, gphy_val | 0x0001);
        mdio_write(tp, 0x1F, 0x0000);

        mdio_write(tp, 0x1F, 0x0007);
        mdio_write(tp, 0x1E, 0x00AC);
        mdio_write(tp, 0x18, 0x0006);
        mdio_write(tp, 0x1F, 0x0000);

        mdio_write(tp, 0x1F, 0x0003);
        mdio_write(tp, 0x19, 0x7F46);
        mdio_write(tp, 0x1F, 0x0005);
        mdio_write(tp, 0x05, 0x8AD2);
        mdio_write(tp, 0x06, 0x6810);
        mdio_write(tp, 0x05, 0x8AD4);
        mdio_write(tp, 0x06, 0x8002);
        mdio_write(tp, 0x05, 0x8ADE);
        mdio_write(tp, 0x06, 0x8025);
        mdio_write(tp, 0x1F, 0x0000);
    } else if (tp->mcfg == CFG_METHOD_16) {
        mdio_write(tp, 0x1F, 0x0005);
        mdio_write(tp, 0x05, 0x8B80);
        gphy_val = mdio_read(tp, 0x06);
        gphy_val |= BIT_2 | BIT_1;
        mdio_write(tp, 0x06, gphy_val);
        mdio_write(tp, 0x1f, 0x0000);

        mdio_write(tp, 0x1f, 0x0004);
        mdio_write(tp, 0x1f, 0x0007);
        mdio_write(tp, 0x1e, 0x002D);
        gphy_val = mdio_read(tp, 0x18);
        gphy_val |= BIT_4;
        mdio_write(tp, 0x18, gphy_val);
        mdio_write(tp, 0x1f, 0x0002);
        mdio_write(tp, 0x1f, 0x0000);
        gphy_val = mdio_read(tp, 0x14);
        gphy_val |= BIT_15;
        mdio_write(tp, 0x14, gphy_val);

        mdio_write(tp, 0x1F, 0x0000);
        mdio_write(tp, 0x15, 0x1006);

        mdio_write(tp, 0x1F, 0x0005);
        mdio_write(tp, 0x05, 0x8B86);
        gphy_val = mdio_read(tp, 0x06);
        gphy_val |= BIT_0;
        mdio_write(tp, 0x06, gphy_val);
        mdio_write(tp, 0x1F, 0x0000);

        mdio_write(tp, 0x1F, 0x0001);
        mdio_write(tp, 0x0B, 0x6C14);
        mdio_write(tp, 0x14, 0x7F3D);
        mdio_write(tp, 0x1C, 0xFAFE);
        mdio_write(tp, 0x08, 0x07C5);
        mdio_write(tp, 0x10, 0xF090);
        mdio_write(tp, 0x1F, 0x0003);
        mdio_write(tp, 0x14, 0x641A);
        mdio_write(tp, 0x1A, 0x0606);
        mdio_write(tp, 0x12, 0xF480);
        mdio_write(tp, 0x13, 0x0747);
        mdio_write(tp, 0x1F, 0x0000);

        mdio_write(tp, 0x1F, 0x0004);
        mdio_write(tp, 0x1F, 0x0007);
        mdio_write(tp, 0x1E, 0x0078);
        mdio_write(tp, 0x15, 0xA408);
        mdio_write(tp, 0x17, 0x5100);
        mdio_write(tp, 0x19, 0x0008);
        mdio_write(tp, 0x1F, 0x0002);
        mdio_write(tp, 0x1F, 0x0000);

        mdio_write(tp, 0x1F, 0x0003);
        mdio_write(tp, 0x0D, 0x0207);
        mdio_write(tp, 0x02, 0x5FD0);
        mdio_write(tp, 0x1F, 0x0000);

        mdio_write(tp, 0x1F, 0x0004);
        mdio_write(tp, 0x1F, 0x0007);
        mdio_write(tp, 0x1E, 0x00A1);
        gphy_val = mdio_read(tp, 0x1A);
        gphy_val &= ~BIT_2;
        mdio_write(tp, 0x1A, gphy_val);
        mdio_write(tp, 0x1F, 0x0002);
        mdio_write(tp, 0x1F, 0x0000);

        mdio_write(tp, 0x1F, 0x0004);
        mdio_write(tp, 0x1F, 0x0007);
        mdio_write(tp, 0x1E, 0x002D);
        gphy_val = mdio_read(tp, 0x16);
        gphy_val |= BIT_5;
        mdio_write(tp, 0x16, gphy_val);
        mdio_write(tp, 0x1F, 0x0002);
        mdio_write(tp, 0x1F, 0x0000);

        mdio_write(tp, 0x1F, 0x0004);
        mdio_write(tp, 0x1F, 0x0007);
        mdio_write(tp, 0x1E, 0x00AC);
        mdio_write(tp, 0x18, 0x0006);
        mdio_write(tp, 0x1F, 0x0002);
        mdio_write(tp, 0x1F, 0x0000);

        mdio_write(tp, 0x1F, 0x0003);
        mdio_write(tp, 0x09, 0xA20F);
        mdio_write(tp, 0x1F, 0x0000);

        mdio_write(tp, 0x1F, 0x0005);
        mdio_write(tp, 0x05, 0x8B5B);
        mdio_write(tp, 0x06, 0x9222);
        mdio_write(tp, 0x05, 0x8B6D);
        mdio_write(tp, 0x06, 0x8000);
        mdio_write(tp, 0x05, 0x8B76);
        mdio_write(tp, 0x06, 0x8000);
        mdio_write(tp, 0x1F, 0x0000);

        mdio_write(tp, 0x1f, 0x0005);
        mdio_write(tp, 0x05, 0x8B54);
        mdio_write(tp, 0x06, mdio_read(tp, 0x06) & ~BIT_11);
        mdio_write(tp, 0x05, 0x8B5D);
        mdio_write(tp, 0x06, mdio_read(tp, 0x06) & ~BIT_11);
        mdio_write(tp, 0x05, 0x8A7C);
        mdio_write(tp, 0x06, mdio_read(tp, 0x06) & ~BIT_8);
        mdio_write(tp, 0x05, 0x8A7F);
        mdio_write(tp, 0x06, mdio_read(tp, 0x06) | BIT_8);
        mdio_write(tp, 0x05, 0x8A82);
        mdio_write(tp, 0x06, mdio_read(tp, 0x06) & ~BIT_8);
        mdio_write(tp, 0x05, 0x8A85);
        mdio_write(tp, 0x06, mdio_read(tp, 0x06) & ~BIT_8);
        mdio_write(tp, 0x05, 0x8A88);
        mdio_write(tp, 0x06, mdio_read(tp, 0x06) & ~BIT_8);
        mdio_write(tp, 0x1f, 0x0000);

        mdio_write(tp, 0x1F, 0x0005);
        mdio_write(tp, 0x05, 0x8B85);
        gphy_val = mdio_read(tp, 0x06) | BIT_15;
        mdio_write(tp, 0x06, gphy_val);
        mdio_write(tp, 0x1f, 0x0000);
    } else if (tp->mcfg == CFG_METHOD_17) {
        mdio_write(tp, 0x1F, 0x0005);
        mdio_write(tp, 0x05, 0x8B80);
        gphy_val = mdio_read(tp, 0x06);
        gphy_val |= BIT_2 | BIT_1;
        mdio_write(tp, 0x06, gphy_val);
        mdio_write(tp, 0x1f, 0x0000);

        mdio_write(tp, 0x1F, 0x0005);
        mdio_write(tp, 0x05, 0x8B86);
        gphy_val = mdio_read(tp, 0x06);
        gphy_val &= ~BIT_4;
        mdio_write(tp, 0x06, gphy_val);
        mdio_write(tp, 0x1f, 0x0000);


        mdio_write(tp, 0x1f, 0x0004);
        mdio_write(tp, 0x1f, 0x0007);
        mdio_write(tp, 0x1e, 0x002D);
        gphy_val = mdio_read(tp, 0x18);
        gphy_val |= BIT_4;
        mdio_write(tp, 0x18, gphy_val);
        mdio_write(tp, 0x1f, 0x0002);
        mdio_write(tp, 0x1f, 0x0000);
        gphy_val = mdio_read(tp, 0x14);
        gphy_val |= BIT_15;
        mdio_write(tp, 0x14, gphy_val);

        mdio_write(tp, 0x1F, 0x0005);
        mdio_write(tp, 0x05, 0x8B86);
        gphy_val = mdio_read(tp, 0x06);
        gphy_val |= BIT_0;
        mdio_write(tp, 0x06, gphy_val);
        mdio_write(tp, 0x1f, 0x0000);

        mdio_write(tp, 0x1F, 0x0004);
        mdio_write(tp, 0x1F, 0x0007);
        mdio_write(tp, 0x1E, 0x00AC);
        mdio_write(tp, 0x18, 0x0006);
        mdio_write(tp, 0x1F, 0x0002);
        mdio_write(tp, 0x1F, 0x0000);

        mdio_write(tp, 0x1F, 0x0003);
        mdio_write(tp, 0x09, 0xA20F);
        mdio_write(tp, 0x1F, 0x0000);

        mdio_write(tp, 0x1F, 0x0005);
        mdio_write(tp, 0x05, 0x8B85);
        gphy_val = mdio_read(tp, 0x06) | BIT_14 | BIT_15;
        mdio_write(tp, 0x06, gphy_val);
        mdio_write(tp, 0x1f, 0x0000);

        mdio_write(tp, 0x1F, 0x0005);
        mdio_write(tp, 0x05, 0x8B5B);
        mdio_write(tp, 0x06, 0x9222);
        mdio_write(tp, 0x05, 0x8B6D);
        mdio_write(tp, 0x06, 0x8000);
        mdio_write(tp, 0x05, 0x8B76);
        mdio_write(tp, 0x06, 0x8000);
        mdio_write(tp, 0x1F, 0x0000);

        mdio_write(tp, 0x1f, 0x0005);
        mdio_write(tp, 0x05, 0x8B54);
        mdio_write(tp, 0x06, mdio_read(tp, 0x06) & ~BIT_11);
        mdio_write(tp, 0x05, 0x8B5D);
        mdio_write(tp, 0x06, mdio_read(tp, 0x06) & ~BIT_11);
        mdio_write(tp, 0x05, 0x8A7C);
        mdio_write(tp, 0x06, mdio_read(tp, 0x06) & ~BIT_8);
        mdio_write(tp, 0x05, 0x8A7F);
        mdio_write(tp, 0x06, mdio_read(tp, 0x06) | BIT_8);
        mdio_write(tp, 0x05, 0x8A82);
        mdio_write(tp, 0x06, mdio_read(tp, 0x06) & ~BIT_8);
        mdio_write(tp, 0x05, 0x8A85);
        mdio_write(tp, 0x06, mdio_read(tp, 0x06) & ~BIT_8);
        mdio_write(tp, 0x05, 0x8A88);
        mdio_write(tp, 0x06, mdio_read(tp, 0x06) & ~BIT_8);
        mdio_write(tp, 0x1f, 0x0000);

    } else if (tp->mcfg == CFG_METHOD_18) {
        mdio_write(tp, 0x1F, 0x0005);
        mdio_write(tp, 0x05, 0x8b80);
        gphy_val = mdio_read(tp, 0x06);
        gphy_val |= BIT_2 | BIT_1;
        mdio_write(tp, 0x06, gphy_val);
        mdio_write(tp, 0x1F, 0x0000);

        mdio_write(tp, 0x1f, 0x0007);
        mdio_write(tp, 0x1e, 0x002D);
        gphy_val = mdio_read(tp, 0x18);
        gphy_val |= BIT_4;
        mdio_write(tp, 0x18, gphy_val);
        mdio_write(tp, 0x1f, 0x0000);
        gphy_val = mdio_read(tp, 0x14);
        gphy_val |= BIT_15;
        mdio_write(tp, 0x14, gphy_val);

        mdio_write(tp, 0x1F, 0x0005);
        mdio_write(tp, 0x05, 0x8B86);
        gphy_val = mdio_read(tp, 0x06);
        gphy_val |= BIT_0;
        mdio_write(tp, 0x06, gphy_val);
        mdio_write(tp, 0x1f, 0x0000);

        mdio_write(tp, 0x1F, 0x0005);
        mdio_write(tp, 0x05, 0x8B85);
        gphy_val = mdio_read(tp, 0x06);
        gphy_val |= BIT_14;
        mdio_write(tp, 0x06, gphy_val);
        mdio_write(tp, 0x1f, 0x0000);

        mdio_write(tp, 0x1F, 0x0003);
        mdio_write(tp, 0x09, 0xA20F);
        mdio_write(tp, 0x1F, 0x0000);

        mdio_write(tp, 0x1F, 0x0005);
        mdio_write(tp, 0x05, 0x8B55);
        mdio_write(tp, 0x06, 0x0000);
        mdio_write(tp, 0x05, 0x8B5E);
        mdio_write(tp, 0x06, 0x0000);
        mdio_write(tp, 0x05, 0x8B67);
        mdio_write(tp, 0x06, 0x0000);
        mdio_write(tp, 0x05, 0x8B70);
        mdio_write(tp, 0x06, 0x0000);
        mdio_write(tp, 0x1F, 0x0000);
        mdio_write(tp, 0x1F, 0x0007);
        mdio_write(tp, 0x1E, 0x0078);
        mdio_write(tp, 0x17, 0x0000);
        mdio_write(tp, 0x19, 0x00FB);
        mdio_write(tp, 0x1F, 0x0000);

        mdio_write(tp, 0x1F, 0x0005);
        mdio_write(tp, 0x05, 0x8B79);
        mdio_write(tp, 0x06, 0xAA00);
        mdio_write(tp, 0x1F, 0x0000);

        mdio_write(tp, 0x1f, 0x0003);
        mdio_write(tp, 0x01, 0x328A);
        mdio_write(tp, 0x1f, 0x0000);

        mdio_write(tp, 0x1f, 0x0005);
        mdio_write(tp, 0x05, 0x8B54);
        mdio_write(tp, 0x06, mdio_read(tp, 0x06) & ~BIT_11);
        mdio_write(tp, 0x05, 0x8B5D);
        mdio_write(tp, 0x06, mdio_read(tp, 0x06) & ~BIT_11);
        mdio_write(tp, 0x05, 0x8A7C);
        mdio_write(tp, 0x06, mdio_read(tp, 0x06) & ~BIT_8);
        mdio_write(tp, 0x05, 0x8A7F);
        mdio_write(tp, 0x06, mdio_read(tp, 0x06) | BIT_8);
        mdio_write(tp, 0x05, 0x8A82);
        mdio_write(tp, 0x06, mdio_read(tp, 0x06) & ~BIT_8);
        mdio_write(tp, 0x05, 0x8A85);
        mdio_write(tp, 0x06, mdio_read(tp, 0x06) & ~BIT_8);
        mdio_write(tp, 0x05, 0x8A88);
        mdio_write(tp, 0x06, mdio_read(tp, 0x06) & ~BIT_8);
        mdio_write(tp, 0x1f, 0x0000);

        mdio_write(tp, 0x1f, 0x0005);
        mdio_write(tp, 0x05, 0x8b85);
        mdio_write(tp, 0x06, mdio_read(tp, 0x06) | BIT_15);
        mdio_write(tp, 0x1f, 0x0000);

    } else if (tp->mcfg == CFG_METHOD_19) {
        mdio_write(tp, 0x1F, 0x0005);
        mdio_write(tp, 0x05, 0x8b80);
        gphy_val = mdio_read(tp, 0x06);
        gphy_val |= BIT_2 | BIT_1;
        mdio_write(tp, 0x06, gphy_val);
        mdio_write(tp, 0x1F, 0x0000);

        mdio_write(tp, 0x1f, 0x0007);
        mdio_write(tp, 0x1e, 0x002D);
        gphy_val = mdio_read(tp, 0x18);
        gphy_val |= BIT_4;
        mdio_write(tp, 0x18, gphy_val);
        mdio_write(tp, 0x1f, 0x0000);
        gphy_val = mdio_read(tp, 0x14);
        gphy_val |= BIT_15;
        mdio_write(tp, 0x14, gphy_val);

        mdio_write(tp, 0x1F, 0x0005);
        mdio_write(tp, 0x05, 0x8B86);
        gphy_val = mdio_read(tp, 0x06);
        gphy_val |= BIT_0;
        mdio_write(tp, 0x06, gphy_val);
        mdio_write(tp, 0x1f, 0x0000);

        mdio_write(tp, 0x1f, 0x0005);
        mdio_write(tp, 0x05, 0x8B54);
        mdio_write(tp, 0x06, mdio_read(tp, 0x06) & ~BIT_11);
        mdio_write(tp, 0x05, 0x8B5D);
        mdio_write(tp, 0x06, mdio_read(tp, 0x06) & ~BIT_11);
        mdio_write(tp, 0x05, 0x8A7C);
        mdio_write(tp, 0x06, mdio_read(tp, 0x06) & ~BIT_8);
        mdio_write(tp, 0x05, 0x8A7F);
        mdio_write(tp, 0x06, mdio_read(tp, 0x06) | BIT_8);
        mdio_write(tp, 0x05, 0x8A82);
        mdio_write(tp, 0x06, mdio_read(tp, 0x06) & ~BIT_8);
        mdio_write(tp, 0x05, 0x8A85);
        mdio_write(tp, 0x06, mdio_read(tp, 0x06) & ~BIT_8);
        mdio_write(tp, 0x05, 0x8A88);
        mdio_write(tp, 0x06, mdio_read(tp, 0x06) & ~BIT_8);
        mdio_write(tp, 0x1f, 0x0000);

        mdio_write(tp, 0x1f, 0x0005);
        mdio_write(tp, 0x05, 0x8b85);
        mdio_write(tp, 0x06, mdio_read(tp, 0x06) | BIT_15);
        mdio_write(tp, 0x1f, 0x0000);

    } else if (tp->mcfg == CFG_METHOD_20) {
        mdio_write(tp, 0x1F, 0x0005);
        mdio_write(tp, 0x05, 0x8b80);
        gphy_val = mdio_read(tp, 0x06);
        gphy_val |= BIT_2 | BIT_1;
        mdio_write(tp, 0x06, gphy_val);
        mdio_write(tp, 0x1F, 0x0000);

        mdio_write(tp, 0x1f, 0x0007);
        mdio_write(tp, 0x1e, 0x002D);
        gphy_val = mdio_read(tp, 0x18);
        gphy_val |= BIT_4;
        mdio_write(tp, 0x18, gphy_val);
        mdio_write(tp, 0x1f, 0x0000);
        gphy_val = mdio_read(tp, 0x14);
        gphy_val |= BIT_15;
        mdio_write(tp, 0x14, gphy_val);

        mdio_write(tp, 0x1F, 0x0005);
        mdio_write(tp, 0x05, 0x8B86);
        gphy_val = mdio_read(tp, 0x06);
        gphy_val |= BIT_0;
        mdio_write(tp, 0x06, gphy_val);
        mdio_write(tp, 0x1f, 0x0000);

        mdio_write(tp, 0x1F, 0x0005);
        mdio_write(tp, 0x05, 0x8B85);
        gphy_val = mdio_read(tp, 0x06);
        gphy_val |= BIT_14;
        mdio_write(tp, 0x06, gphy_val);
        mdio_write(tp, 0x1f, 0x0000);

        mdio_write(tp, 0x1F, 0x0003);
        mdio_write(tp, 0x09, 0xA20F);
        mdio_write(tp, 0x1F, 0x0000);

        mdio_write(tp, 0x1F, 0x0005);
        mdio_write(tp, 0x05, 0x8B55);
        mdio_write(tp, 0x06, 0x0000);
        mdio_write(tp, 0x05, 0x8B5E);
        mdio_write(tp, 0x06, 0x0000);
        mdio_write(tp, 0x05, 0x8B67);
        mdio_write(tp, 0x06, 0x0000);
        mdio_write(tp, 0x05, 0x8B70);
        mdio_write(tp, 0x06, 0x0000);
        mdio_write(tp, 0x1F, 0x0000);
        mdio_write(tp, 0x1F, 0x0007);
        mdio_write(tp, 0x1E, 0x0078);
        mdio_write(tp, 0x17, 0x0000);
        mdio_write(tp, 0x19, 0x00FB);
        mdio_write(tp, 0x1F, 0x0000);

        mdio_write(tp, 0x1F, 0x0005);
        mdio_write(tp, 0x05, 0x8B79);
        mdio_write(tp, 0x06, 0xAA00);
        mdio_write(tp, 0x1F, 0x0000);

        mdio_write(tp, 0x1f, 0x0005);
        mdio_write(tp, 0x05, 0x8B54);
        mdio_write(tp, 0x06, mdio_read(tp, 0x06) & ~BIT_11);
        mdio_write(tp, 0x05, 0x8B5D);
        mdio_write(tp, 0x06, mdio_read(tp, 0x06) & ~BIT_11);
        mdio_write(tp, 0x05, 0x8A7C);
        mdio_write(tp, 0x06, mdio_read(tp, 0x06) & ~BIT_8);
        mdio_write(tp, 0x05, 0x8A7F);
        mdio_write(tp, 0x06, mdio_read(tp, 0x06) | BIT_8);
        mdio_write(tp, 0x05, 0x8A82);
        mdio_write(tp, 0x06, mdio_read(tp, 0x06) & ~BIT_8);
        mdio_write(tp, 0x05, 0x8A85);
        mdio_write(tp, 0x06, mdio_read(tp, 0x06) & ~BIT_8);
        mdio_write(tp, 0x05, 0x8A88);
        mdio_write(tp, 0x06, mdio_read(tp, 0x06) & ~BIT_8);
        mdio_write(tp, 0x1f, 0x0000);

        mdio_write(tp, 0x1f, 0x0005);
        mdio_write(tp, 0x05, 0x8b85);
        mdio_write(tp, 0x06, mdio_read(tp, 0x06) | BIT_15);
        mdio_write(tp, 0x1f, 0x0000);

    } else if (tp->mcfg == CFG_METHOD_21) {
        mdio_write(tp, 0x1F, 0x0A46);
        gphy_val = mdio_read(tp, 0x10);
        mdio_write(tp, 0x1F, 0x0BCC);
        if (gphy_val & BIT_8)
            gphy_val = mdio_read(tp, 0x12) & ~BIT_15;
        else
            gphy_val = mdio_read(tp, 0x12) | BIT_15;
        mdio_write(tp, 0x1F, 0x0A46);
        gphy_val = mdio_read(tp, 0x13);
        mdio_write(tp, 0x1F, 0x0C41);
        if (gphy_val & BIT_8)
            gphy_val = mdio_read(tp, 0x15) | BIT_1;
        else
            gphy_val = mdio_read(tp, 0x15) & ~BIT_1;

        mdio_write(tp, 0x1F, 0x0A44);
        mdio_write(tp, 0x11, mdio_read(tp, 0x11) | BIT_2 | BIT_3);

        mdio_write(tp, 0x1F, 0x0BCC);
        mdio_write(tp, 0x14, mdio_read(tp, 0x14) & ~BIT_8);
        mdio_write(tp, 0x1F, 0x0A44);
        mdio_write(tp, 0x11, mdio_read(tp, 0x11) | BIT_7);
        mdio_write(tp, 0x11, mdio_read(tp, 0x11) | BIT_6);
        mdio_write(tp, 0x1F, 0x0A43);
        mdio_write(tp, 0x13, 0x8084);
        mdio_write(tp, 0x14, mdio_read(tp, 0x14) & ~(BIT_14 | BIT_13));
        mdio_write(tp, 0x10, mdio_read(tp, 0x10) | BIT_12);
        mdio_write(tp, 0x10, mdio_read(tp, 0x10) | BIT_1);
        mdio_write(tp, 0x10, mdio_read(tp, 0x10) | BIT_0);

        mdio_write(tp, 0x1F, 0x0A4B);
        mdio_write(tp, 0x11, mdio_read(tp, 0x11) | BIT_2);

        mdio_write(tp, 0x1F, 0x0A43);
        mdio_write(tp, 0x13, 0x8012);
        mdio_write(tp, 0x14, mdio_read(tp, 0x14) | BIT_15);

        mdio_write(tp, 0x1F, 0x0C42);
        gphy_val = mdio_read(tp, 0x11);
        gphy_val |= BIT_14;
        gphy_val &= ~BIT_13;
        mdio_write(tp, 0x11, gphy_val);

        mdio_write(tp, 0x1F, 0x0A43);
        mdio_write(tp, 0x13, 0x809A);
        mdio_write(tp, 0x14, 0x8022);
        mdio_write(tp, 0x13, 0x80A0);
        gphy_val = mdio_read(tp, 0x14) & 0x00FF;
        gphy_val |= 0x1000;
        mdio_write(tp, 0x14, gphy_val);
        mdio_write(tp, 0x13, 0x8088);
        mdio_write(tp, 0x14, 0x9222);

        mdio_write(tp, 0x1F, 0x0BCD);
        mdio_write(tp, 0x14, 0x5065);
        mdio_write(tp, 0x14, 0xD065);
        mdio_write(tp, 0x1F, 0x0BC8);
        mdio_write(tp, 0x11, 0x5655);
        mdio_write(tp, 0x1F, 0x0BCD);
        mdio_write(tp, 0x14, 0x1065);
        mdio_write(tp, 0x14, 0x9065);
        mdio_write(tp, 0x14, 0x1065);

        mdio_write(tp, 0x1F, 0x0000);
    } else if (tp->mcfg == CFG_METHOD_22) {
        mdio_write(tp, 0x1F, 0x0BCD);
        mdio_write(tp, 0x14, 0x5065);
        mdio_write(tp, 0x14, 0xD065);
        mdio_write(tp, 0x1F, 0x0BC8);
        mdio_write(tp, 0x11, 0x5655);
        mdio_write(tp, 0x1F, 0x0BCD);
        mdio_write(tp, 0x14, 0x1065);
        mdio_write(tp, 0x14, 0x9065);
        mdio_write(tp, 0x14, 0x1065);
    } else if (tp->mcfg == CFG_METHOD_23) {
        mdio_write(tp, 0x1F, 0x0BCC);
        gphy_val = mdio_read(tp, 0x14);
        gphy_val |= BIT_8;
        mdio_write(tp, 0x14, gphy_val);
        mdio_write(tp, 0x1F, 0x0A44);
        gphy_val = mdio_read(tp, 0x11);
        gphy_val |= BIT_7 | BIT_6;
        mdio_write(tp, 0x11, gphy_val);
        mdio_write(tp, 0x1F, 0x0A43);
        mdio_write(tp, 0x13, 0x8084);
        gphy_val = mdio_read(tp, 0x14);
        gphy_val &= ~(BIT_14 | BIT_13);
        mdio_write(tp, 0x14, gphy_val);
        gphy_val = mdio_read(tp, 0x10);
        gphy_val |= BIT_12;
        mdio_write(tp, 0x10, gphy_val);
        gphy_val = mdio_read(tp, 0x10);
        gphy_val |= BIT_2 | BIT_1 | BIT_0;
        mdio_write(tp, 0x10, gphy_val);

        mdio_write(tp, 0x1F, 0x0A43);
        mdio_write(tp, 0x13, 0x809C);
        mdio_write(tp, 0x14, 0xA700);
        mdio_write(tp, 0x13, 0x80A5);
        mdio_write(tp, 0x14, 0xA700);
    } else if (tp->mcfg == CFG_METHOD_24) {
        mdio_write(tp, 0x1F, 0x0BCC);
        mdio_write(tp, 0x14, mdio_read(tp, 0x14) & ~BIT_8);
        mdio_write(tp, 0x1F, 0x0A44);
        mdio_write(tp, 0x11, mdio_read(tp, 0x11) | BIT_7);
        mdio_write(tp, 0x11, mdio_read(tp, 0x11) | BIT_6);
        mdio_write(tp, 0x1F, 0x0A43);
        mdio_write(tp, 0x13, 0x8084);
        mdio_write(tp, 0x14, mdio_read(tp, 0x14) & ~(BIT_14 | BIT_13));
        mdio_write(tp, 0x10, mdio_read(tp, 0x10) | BIT_12);
        mdio_write(tp, 0x10, mdio_read(tp, 0x10) | BIT_1);
        mdio_write(tp, 0x10, mdio_read(tp, 0x10) | BIT_0);
        mdio_write(tp, 0x1F, 0x0A43);
        mdio_write(tp, 0x13, 0x8012);
        mdio_write(tp, 0x14, mdio_read(tp, 0x14) | BIT_15);

        mdio_write(tp, 0x1F, 0x0C42);
        gphy_val = mdio_read(tp, 0x11);
        gphy_val |= BIT_14;
        gphy_val &= ~BIT_13;
        mdio_write(tp, 0x11, gphy_val);

    } else if (tp->mcfg == CFG_METHOD_25 || tp->mcfg == CFG_METHOD_26) {
        mdio_write(tp, 0x1F, 0x0BCC);
        mdio_write(tp, 0x14, mdio_read(tp, 0x14) & ~BIT_8);
        mdio_write(tp, 0x1F, 0x0A44);
        mdio_write(tp, 0x11, mdio_read(tp, 0x11) | BIT_7);
        mdio_write(tp, 0x11, mdio_read(tp, 0x11) | BIT_6);
        mdio_write(tp, 0x1F, 0x0A43);
        mdio_write(tp, 0x13, 0x8084);
        mdio_write(tp, 0x14, mdio_read(tp, 0x14) & ~(BIT_14 | BIT_13));
        mdio_write(tp, 0x10, mdio_read(tp, 0x10) | BIT_12);
        mdio_write(tp, 0x10, mdio_read(tp, 0x10) | BIT_1);
        mdio_write(tp, 0x10, mdio_read(tp, 0x10) | BIT_0);

        mdio_write(tp, 0x1F, 0x0A43);
        mdio_write(tp, 0x13, 0x8012);
        mdio_write(tp, 0x14, mdio_read(tp, 0x14) | BIT_15);

        mdio_write(tp, 0x1F, 0x0BCE);
        mdio_write(tp, 0x12, 0x8860);

        mdio_write(tp, 0x1F, 0x0A43);
        mdio_write(tp, 0x13, 0x80F3);
        mdio_write(tp, 0x14, (mdio_read(tp, 0x14) & ~0xFF00) | 0x8B00);
        mdio_write(tp, 0x13, 0x80F0);
        mdio_write(tp, 0x14, (mdio_read(tp, 0x14) & ~0xFF00) | 0x3A00);
        mdio_write(tp, 0x13, 0x80EF);
        mdio_write(tp, 0x14, (mdio_read(tp, 0x14) & ~0xFF00) | 0x0500);
        mdio_write(tp, 0x13, 0x80F6);
        mdio_write(tp, 0x14, (mdio_read(tp, 0x14) & ~0xFF00) | 0x6E00);
        mdio_write(tp, 0x13, 0x80EC);
        mdio_write(tp, 0x14, (mdio_read(tp, 0x14) & ~0xFF00) | 0x6800);
        mdio_write(tp, 0x13, 0x80ED);
        mdio_write(tp, 0x14, (mdio_read(tp, 0x14) & ~0xFF00) | 0x7C00);
        mdio_write(tp, 0x13, 0x80F2);
        mdio_write(tp, 0x14, (mdio_read(tp, 0x14) & ~0xFF00) | 0xF400);
        mdio_write(tp, 0x13, 0x80F4);
        mdio_write(tp, 0x14, (mdio_read(tp, 0x14) & ~0xFF00) | 0x8500);
        mdio_write(tp, 0x1F, 0x0A43);
        mdio_write(tp, 0x13, 0x8110);
        mdio_write(tp, 0x14, (mdio_read(tp, 0x14) & ~0xFF00) | 0xA800);
        mdio_write(tp, 0x13, 0x810F);
        mdio_write(tp, 0x14, (mdio_read(tp, 0x14) & ~0xFF00) | 0x1D00);
        mdio_write(tp, 0x13, 0x8111);
        mdio_write(tp, 0x14, (mdio_read(tp, 0x14) & ~0xFF00) | 0xF500);
        mdio_write(tp, 0x13, 0x8113);
        mdio_write(tp, 0x14, (mdio_read(tp, 0x14) & ~0xFF00) | 0x6100);
        mdio_write(tp, 0x13, 0x8115);
        mdio_write(tp, 0x14, (mdio_read(tp, 0x14) & ~0xFF00) | 0x9200);
        mdio_write(tp, 0x13, 0x810E);
        mdio_write(tp, 0x14, (mdio_read(tp, 0x14) & ~0xFF00) | 0x0400);
        mdio_write(tp, 0x13, 0x810C);
        mdio_write(tp, 0x14, (mdio_read(tp, 0x14) & ~0xFF00) | 0x7C00);
        mdio_write(tp, 0x13, 0x810B);
        mdio_write(tp, 0x14, (mdio_read(tp, 0x14) & ~0xFF00) | 0x5A00);
        mdio_write(tp, 0x1F, 0x0A43);
        mdio_write(tp, 0x13, 0x80D1);
        mdio_write(tp, 0x14, (mdio_read(tp, 0x14) & ~0xFF00) | 0xFF00);
        mdio_write(tp, 0x13, 0x80CD);
        mdio_write(tp, 0x14, (mdio_read(tp, 0x14) & ~0xFF00) | 0x9E00);
        mdio_write(tp, 0x13, 0x80D3);
        mdio_write(tp, 0x14, (mdio_read(tp, 0x14) & ~0xFF00) | 0x0E00);
        mdio_write(tp, 0x13, 0x80D5);
        mdio_write(tp, 0x14, (mdio_read(tp, 0x14) & ~0xFF00) | 0xCA00);
        mdio_write(tp, 0x13, 0x80D7);
        mdio_write(tp, 0x14, (mdio_read(tp, 0x14) & ~0xFF00) | 0x8400);

    } else if (tp->mcfg == CFG_METHOD_27) {
        mdio_write(tp, 0x1F, 0x0BCC);
        mdio_write(tp, 0x14, mdio_read(tp, 0x14) & ~BIT_8);
        mdio_write(tp, 0x1F, 0x0A44);
        mdio_write(tp, 0x11, mdio_read(tp, 0x11) | BIT_7);
        mdio_write(tp, 0x11, mdio_read(tp, 0x11) | BIT_6);
        mdio_write(tp, 0x1F, 0x0A43);
        mdio_write(tp, 0x13, 0x8084);
        mdio_write(tp, 0x14, mdio_read(tp, 0x14) & ~(BIT_14 | BIT_13));
        mdio_write(tp, 0x10, mdio_read(tp, 0x10) | BIT_12);
        mdio_write(tp, 0x10, mdio_read(tp, 0x10) | BIT_1);
        mdio_write(tp, 0x10, mdio_read(tp, 0x10) | BIT_0);

        mdio_write(tp, 0x1F, 0x0A43);
        mdio_write(tp, 0x13, 0x8012);
        mdio_write(tp, 0x14, mdio_read(tp, 0x14) | BIT_15);

        mdio_write(tp, 0x1F, 0x0C42);
        mdio_write(tp, 0x11, (mdio_read(tp, 0x11) & ~BIT_13) | BIT_14);

        mdio_write(tp, 0x1F, 0x0A43);
        mdio_write(tp, 0x13, 0x80F3);
        mdio_write(tp, 0x14, (mdio_read(tp, 0x14) & ~0xFF00) | 0x8B00);
        mdio_write(tp, 0x13, 0x80F0);
        mdio_write(tp, 0x14, (mdio_read(tp, 0x14) & ~0xFF00) | 0x3A00);
        mdio_write(tp, 0x13, 0x80EF);
        mdio_write(tp, 0x14, (mdio_read(tp, 0x14) & ~0xFF00) | 0x0500);
        mdio_write(tp, 0x13, 0x80F6);
        mdio_write(tp, 0x14, (mdio_read(tp, 0x14) & ~0xFF00) | 0x6E00);
        mdio_write(tp, 0x13, 0x80EC);
        mdio_write(tp, 0x14, (mdio_read(tp, 0x14) & ~0xFF00) | 0x6800);
        mdio_write(tp, 0x13, 0x80ED);
        mdio_write(tp, 0x14, (mdio_read(tp, 0x14) & ~0xFF00) | 0x7C00);
        mdio_write(tp, 0x13, 0x80F2);
        mdio_write(tp, 0x14, (mdio_read(tp, 0x14) & ~0xFF00) | 0xF400);
        mdio_write(tp, 0x13, 0x80F4);
        mdio_write(tp, 0x14, (mdio_read(tp, 0x14) & ~0xFF00) | 0x8500);
        mdio_write(tp, 0x1F, 0x0A43);
        mdio_write(tp, 0x13, 0x8110);
        mdio_write(tp, 0x14, (mdio_read(tp, 0x14) & ~0xFF00) | 0xA800);
        mdio_write(tp, 0x13, 0x810F);
        mdio_write(tp, 0x14, (mdio_read(tp, 0x14) & ~0xFF00) | 0x1D00);
        mdio_write(tp, 0x13, 0x8111);
        mdio_write(tp, 0x14, (mdio_read(tp, 0x14) & ~0xFF00) | 0xF500);
        mdio_write(tp, 0x13, 0x8113);
        mdio_write(tp, 0x14, (mdio_read(tp, 0x14) & ~0xFF00) | 0x6100);
        mdio_write(tp, 0x13, 0x8115);
        mdio_write(tp, 0x14, (mdio_read(tp, 0x14) & ~0xFF00) | 0x9200);
        mdio_write(tp, 0x13, 0x810E);
        mdio_write(tp, 0x14, (mdio_read(tp, 0x14) & ~0xFF00) | 0x0400);
        mdio_write(tp, 0x13, 0x810C);
        mdio_write(tp, 0x14, (mdio_read(tp, 0x14) & ~0xFF00) | 0x7C00);
        mdio_write(tp, 0x13, 0x810B);
        mdio_write(tp, 0x14, (mdio_read(tp, 0x14) & ~0xFF00) | 0x5A00);
        mdio_write(tp, 0x1F, 0x0A43);
        mdio_write(tp, 0x13, 0x80D1);
        mdio_write(tp, 0x14, (mdio_read(tp, 0x14) & ~0xFF00) | 0xFF00);
        mdio_write(tp, 0x13, 0x80CD);
        mdio_write(tp, 0x14, (mdio_read(tp, 0x14) & ~0xFF00) | 0x9E00);
        mdio_write(tp, 0x13, 0x80D3);
        mdio_write(tp, 0x14, (mdio_read(tp, 0x14) & ~0xFF00) | 0x0E00);
        mdio_write(tp, 0x13, 0x80D5);
        mdio_write(tp, 0x14, (mdio_read(tp, 0x14) & ~0xFF00) | 0xCA00);
        mdio_write(tp, 0x13, 0x80D7);
        mdio_write(tp, 0x14, (mdio_read(tp, 0x14) & ~0xFF00) | 0x8400);

        mdio_write(tp, 0x1F, 0x0BCD);
        mdio_write(tp, 0x14, 0x5065);
        mdio_write(tp, 0x14, 0xD065);
        mdio_write(tp, 0x1F, 0x0BC8);
        mdio_write(tp, 0x12, 0x00ED);
        mdio_write(tp, 0x1F, 0x0BCD);
        mdio_write(tp, 0x14, 0x1065);
        mdio_write(tp, 0x14, 0x9065);
        mdio_write(tp, 0x14, 0x1065);
        mdio_write(tp, 0x1F, 0x0000);

    }

    mdio_write(tp, 0x1F, 0x0000);

    rtl8168_disable_EEE(tp);
}

static void
rtl8168_phy_power_up (struct eth_device *dev)
{
    struct rtl8168_private *tp = (struct rtl8168_private *)dev->priv;
    phys_addr_t ioaddr = tp->mmio_addr;
    u32 csi_tmp;

    MDIO_LOCK;
    mdio_write(tp, 0x1F, 0x0000);
    switch (tp->mcfg) {
    case CFG_METHOD_1:
    case CFG_METHOD_2:
    case CFG_METHOD_3:
    case CFG_METHOD_4:
    case CFG_METHOD_5:
    case CFG_METHOD_6:
    case CFG_METHOD_7:
    case CFG_METHOD_8:
    case CFG_METHOD_9:
    case CFG_METHOD_10:
    case CFG_METHOD_11:
    case CFG_METHOD_12:
    case CFG_METHOD_13:
        mdio_write(tp, 0x0E, 0x0000);
        break;
    case CFG_METHOD_21:
    case CFG_METHOD_22:
    case CFG_METHOD_23:
    case CFG_METHOD_24:
    case CFG_METHOD_25:
    case CFG_METHOD_27:
        csi_tmp = rtl8168_eri_read(ioaddr, 0x1AB, 1, ERIAR_ExGMAC);
        csi_tmp |=  ( BIT_2 | BIT_3 | BIT_4 | BIT_5 | BIT_6 | BIT_7 );
        rtl8168_eri_write(ioaddr, 0x1AB, 1, csi_tmp, ERIAR_ExGMAC);
        break;
    default:
        break;
    }
    mdio_write(tp, MII_BMCR, BMCR_ANENABLE);
    MDIO_UNLOCK;
}

static void rtl8168_powerup_pll(struct eth_device *dev)
{
    struct rtl8168_private *tp = (struct rtl8168_private *)dev->priv;
    phys_addr_t ioaddr = tp->mmio_addr;

    switch (tp->mcfg) {
    case CFG_METHOD_9:
    case CFG_METHOD_10:
    case CFG_METHOD_11:
    case CFG_METHOD_12:
    case CFG_METHOD_13:
    case CFG_METHOD_14:
    case CFG_METHOD_15:
    case CFG_METHOD_17:
    case CFG_METHOD_18:
    case CFG_METHOD_19:
    case CFG_METHOD_21:
    case CFG_METHOD_22:
    case CFG_METHOD_24:
    case CFG_METHOD_25:
    case CFG_METHOD_26:
        RTL_W8(PMCH, RTL_R8(PMCH) | BIT_7 | BIT_6);
        break;
    }

    rtl8168_phy_power_up (dev);
}

/**************************************************************************
HALT - Turn off ethernet interface
***************************************************************************/
static void rtl8168_halt(struct eth_device *dev)
{
#ifdef DEBUG_RTL8168
    printf ("%s\n", __FUNCTION__);
#endif

    rtl8168_down(dev);
}

static void rtl8168_get_mac_version(struct rtl8168_private *tp, phys_addr_t ioaddr)
{
    u32 reg,val32;
    u32 ICVerID;

    val32 = RTL_R32(TxConfig)  ;
    reg = val32 & 0x7c800000;
    ICVerID = val32 & 0x00700000;

    switch (reg) {
    case 0x30000000:
        tp->mcfg = CFG_METHOD_1;
        tp->efuse = EFUSE_NOT_SUPPORT;
        break;
    case 0x38000000:
        if (ICVerID == 0x00000000) {
            tp->mcfg = CFG_METHOD_2;
        } else if (ICVerID == 0x00500000) {
            tp->mcfg = CFG_METHOD_3;
        } else {
            tp->mcfg = CFG_METHOD_3;
        }
        tp->efuse = EFUSE_NOT_SUPPORT;
        break;
    case 0x3C000000:
        if (ICVerID == 0x00000000) {
            tp->mcfg = CFG_METHOD_4;
        } else if (ICVerID == 0x00200000) {
            tp->mcfg = CFG_METHOD_5;
        } else if (ICVerID == 0x00400000) {
            tp->mcfg = CFG_METHOD_6;
        } else {
            tp->mcfg = CFG_METHOD_6;
        }
        tp->efuse = EFUSE_NOT_SUPPORT;
        break;
    case 0x3C800000:
        if (ICVerID == 0x00100000) {
            tp->mcfg = CFG_METHOD_7;
        } else if (ICVerID == 0x00300000) {
            tp->mcfg = CFG_METHOD_8;
        } else {
            tp->mcfg = CFG_METHOD_8;
        }
        tp->efuse = EFUSE_NOT_SUPPORT;
        break;
    case 0x28000000:
        if (ICVerID == 0x00100000) {
            tp->mcfg = CFG_METHOD_9;
        } else if (ICVerID == 0x00300000) {
            tp->mcfg = CFG_METHOD_10;
        } else {
            tp->mcfg = CFG_METHOD_10;
        }
        tp->efuse = EFUSE_SUPPORT;
        break;
    case 0x28800000:
        if (ICVerID == 0x00000000) {
            tp->mcfg = CFG_METHOD_11;
        } else if (ICVerID == 0x00200000) {
            tp->mcfg = CFG_METHOD_12;
            RTL_W32(0xD0, RTL_R32(0xD0) | 0x00020000);
        } else {// if (ICVerID == 0x00300000)
            tp->mcfg = CFG_METHOD_13;
        }
        tp->efuse = EFUSE_SUPPORT;
        break;
    case 0x2C000000:
        if (ICVerID == 0x00100000)
            tp->mcfg = CFG_METHOD_14;
        else if (ICVerID == 0x00200000)
            tp->mcfg = CFG_METHOD_15;
        tp->efuse = EFUSE_SUPPORT;
        break;
    case 0x2C800000:
        if (ICVerID == 0x00000000)
            tp->mcfg = CFG_METHOD_16;
        else if (ICVerID == 0x00100000)
            tp->mcfg = CFG_METHOD_17;
        tp->efuse = EFUSE_SUPPORT;
        break;
    case 0x48000000:
        if (ICVerID == 0x00000000)
            tp->mcfg = CFG_METHOD_18;
        else if (ICVerID == 0x00100000)
            tp->mcfg = CFG_METHOD_19;
        tp->efuse = EFUSE_SUPPORT;
        break;
    case 0x48800000:
        tp->mcfg = CFG_METHOD_20;
        tp->efuse = EFUSE_SUPPORT;
        break;
    case 0x4C000000:
        if (ICVerID == 0x00000000)
            tp->mcfg = CFG_METHOD_21;
        else if (ICVerID == 0x00100000)
            tp->mcfg = CFG_METHOD_22;
        tp->efuse = EFUSE_SUPPORT;
        break;
    case 0x50000000:
        if (ICVerID == 0x00000000) {
            tp->mcfg = CFG_METHOD_23;
        } else if (ICVerID == 0x00100000) {
            tp->mcfg = CFG_METHOD_27;
        } else {
            tp->mcfg = CFG_METHOD_27;
        }
        tp->efuse = EFUSE_SUPPORT;
        break;
    case 0x50800000:
        if (ICVerID == 0x00000000) {
            tp->mcfg = CFG_METHOD_24;
        } else if (ICVerID == 0x00100000) {
            tp->mcfg = CFG_METHOD_25;
        } else {
            tp->mcfg = CFG_METHOD_25;
        }
        tp->efuse = EFUSE_SUPPORT;
        break;
    case 0x5C800000:
        tp->mcfg = CFG_METHOD_26;
        tp->efuse = EFUSE_SUPPORT;
        break;
    default:
        printf("unknown chip version (%x)\n",reg);
        tp->mcfg = CFG_METHOD_DEFAULT;
        tp->efuse = EFUSE_NOT_SUPPORT;
        break;
    }

#ifdef DEBUG_RTL8168
    printf("chiptype = %d\n", tp->mcfg);
#endif
}

static void rtl8168_get_mac_address(struct rtl8168_private *tp)
{
    struct eth_device *dev = tp->dev;
    phys_addr_t ioaddr = tp->mmio_addr;
    int i;
    uint8_t env_enetaddr[6];
    char *default_enetaddr="00:10:20:30:40:50" ;

    if (!eth_getenv_enetaddr("ethaddr", env_enetaddr))
        eth_parse_enetaddr(default_enetaddr, env_enetaddr);

   // add valid mac
    RTL_W8(Cfg9346, Cfg9346_Unlock);
    RTL_W32(MAC0,  env_enetaddr[0]
                  |env_enetaddr[1]<<8
                  |env_enetaddr[2]<<16
                  |env_enetaddr[3]<<24);
    RTL_W16(MAC4,  env_enetaddr[4]
                  |env_enetaddr[5]<<8);
    RTL_W8(Cfg9346, Cfg9346_Lock);

    for (i = 0; i < MAC_ADDR_LEN; i++)
        dev->enetaddr[i] = RTL_R8(MAC0 + i);

#ifdef DEBUG_RTL8168
    printf("MAC Address");
    for (i = 0; i < MAC_ADDR_LEN; i++)
        printf(":%02x", dev->enetaddr[i]);
    putc('\n');
#endif
}

/**************************************************************************
INIT - setting up the ethernet interface
***************************************************************************/
static int rtl8168_init(struct eth_device *dev, bd_t *bis)
{
    struct rtl8168_private *tp = (struct rtl8168_private *)dev->priv;
   // u32 tmp;
#ifdef DEBUG_RTL8168
    int stime = currticks();
    printf ("%s\n", __FUNCTION__);
#endif
/*
    // 1295 enable clock

    //1. reg_0x98007088[10] = 1                    // ISO spec, reset bit of gphy
    tmp = rtd_inl(ETN_RESET_CTRL);
    tmp |= BIT_10;
    rtd_outl(ETN_RESET_CTRL,tmp);

    //2. CPU software waiting 200uS
    udelay(200);

    //3. reg_0x98007060[1] = 0                      // ISO spec, Ethernet Boot up bypass gphy ready mode
    tmp = rtd_inl(ETN_GPHY_BYPASS);
    tmp &= ~(BIT_1);
    rtd_outl(ETN_GPHY_BYPASS,tmp);

    //4. reg_0x98007fc0[0] = 0                      // ISO spec, Ethernet Boot up disable dbus clock gating
    tmp = rtd_inl(ETN_DBUS_CLK);
    tmp &= ~(BIT_0);
    rtd_outl(ETN_DBUS_CLK,tmp);

    //5. CPU software waiting 200uS
    udelay(200);

    //6. reg_0x9800708c[12:11] = 11              // ISO spec, clock enable bit for etn clock & etn 250MHz
    tmp = rtd_inl(ETN_CLK_CTRL);
    tmp |= (BIT_11|BIT_12);
    rtd_outl(ETN_CLK_CTRL,tmp);

    //7. reg_0x9800708c[12:11] = 00              // ISO spec, clock enable bit for etn clock & etn 250MHz
    tmp = rtd_inl(ETN_CLK_CTRL);
    tmp &= ~(BIT_11|BIT_12);
    rtd_outl(ETN_CLK_CTRL,tmp);

    //8. reg_0x98007088[9] = 1                      // ISO spec, reset bit of gmac
    tmp = rtd_inl(ETN_RESET_CTRL);
    tmp |= BIT_9;
    rtd_outl(ETN_RESET_CTRL,tmp);

    //9. reg_0x9800708c[12:11] = 11              // ISO spec, clock enable bit for etn clock & etn 250MHz
    tmp = rtd_inl(ETN_CLK_CTRL);
    tmp |= (BIT_11|BIT_12);
    rtd_outl(ETN_CLK_CTRL,tmp);

    rtl8168_get_mac_version(tp, tp->mmio_addr);
    rtl8168_print_mac_version(tp);
    rtl8168_get_mac_address(tp);
 */
    tp->DescArrays = (u8 *)malloc(R8168_TX_RING_BYTES +
                                  R8168_RX_RING_BYTES +
                                  ALIGN_256);
    if (!tp->DescArrays) {
        printf("Can not allocate memory of r8168\n");
        return -ENOMEM;
    }

    tp->RxBufferRings = (u8 *)memalign(64, NUM_RX_DESC * tp->rx_buf_sz + ALIGN_8);
    if (!tp->RxBufferRings) {
        printf("Can not allocate memory of r8168\n");
        free(tp->DescArrays);
        tp->DescArrays = 0;
        return -ENOMEM;
    }

    /* Tx Descriptors needs 256 bytes alignment; */
    tp->TxDescArray = (struct TxDesc *)((unsigned long)(tp->DescArrays +
                                        ALIGN_256) & ~ALIGN_256);

    /* Rx Descriptors needs 256 bytes alignment; */
    tp->RxDescArray = (struct RxDesc *)((u8 *)tp->TxDescArray +
                                        R8168_TX_RING_BYTES);


    rtl8168_init_ring(dev);

    rtl8168_exit_oob(dev);

    rtl8168_tally_counter_clear(tp);

    rtl8168_hw_init(dev);

    rtl8168_hw_reset(dev);

    rtl8168_powerup_pll(dev);

    rtl8168_hw_ephy_config(dev);

    rtl8168_hw_phy_config(dev);

    rtl8168_hw_start(tp);

    rtl8168_get_mac_address(tp);
#ifdef DEBUG_RTL8168
    printf ("Default Set Speed To 100 Mbps\n");
#endif
   // rtl8168_set_speed_xmii(tp, AUTONEG_ENABLE, SPEED_1000, DUPLEX_FULL);

#ifdef DEBUG_RTL8168
    printf ("%s elapsed time : %d\n", __FUNCTION__, currticks()-stime);
#endif
    return 0;
}

#define REG_BASE    0x98016000

static void rtl8168_get_env_para(struct rtl8168_private *tp)
{
    char *eth_drv_para, buf[32];
    const char *delim = ",";
    char *ptr;

    tp->phy_type = PHY_TYPE_FEPHY;
    tp->bypass_enable = 0;
    tp->acp_enable = 0;

    eth_drv_para = getenv("eth_drv_para");
    if (eth_drv_para == NULL)
        return;
    strncpy(buf, eth_drv_para, 31);
    buf[31] = 0;

    ptr = strtok(buf, delim);
    while (ptr != NULL) {
        if (strcmp(ptr, "sgmii") == 0)
            tp->phy_type = PHY_TYPE_SGMII;
        if (strcmp(ptr, "fephy") == 0)
            tp->phy_type = PHY_TYPE_FEPHY;
        else if (strcmp(ptr, "bypass") == 0)
            tp->bypass_enable = 1;
        else if (strcmp(ptr, "nobypass") == 0)
            tp->bypass_enable = 0;
        else if (strcmp(ptr, "acp") == 0)
            tp->acp_enable = 1;
        else if (strcmp(ptr, "noacp") == 0)
            tp->acp_enable = 0;

        ptr = strtok(NULL, delim);
    }
}

#if defined(CONFIG_RTD1395)
static void r8168_reset_phy_gmac(struct rtl8168_private *tp)
{
    u32 tmp;

    /* reg_0x9800708c[12:11] = 00 */
    /* ISO spec, clock enable bit for etn clock & etn 250MHz */
    tmp = rtd_inl(ETN_CLK_CTRL);
    tmp &= ~(BIT_11 | BIT_12);
    rtd_outl(ETN_CLK_CTRL, tmp);

    /* reg_0x98007088[10:9] = 00 */
    /* ISO spec, rstn_gphy & rstn_gmac */
    tmp = rtd_inl(ETN_RESET_CTRL);
    tmp &= ~(BIT_9 | BIT_10);
    rtd_outl(ETN_RESET_CTRL, tmp);

    /* reg_0x98007060[1] = 1 */
    /* ISO spec, bypass mode enable */
    tmp = rtd_inl(ETN_GPHY_BYPASS);
    tmp |= BIT_1;
    rtd_outl(ETN_GPHY_BYPASS, tmp);

    /* reg_0x9800705c = 0x00616703 */
    /* ISO spec, default value */
    rtd_outl(ISO_POWERCUT_ETN, 0x00616703);

    /* RESET for SGMII if needed */
    if (tp->phy_type == PHY_TYPE_SGMII) {
        /* reg_0x9800000c[7] = 0 */
        /* CRT spec, clk_en_sds */
        tmp = rtd_inl(CRT_CLOCK_ENABLE1);
        tmp &= ~(BIT_7);
        rtd_outl(CRT_CLOCK_ENABLE1, tmp);

        /* reg_0x98000000[4:3] = 00 */
        /* CRT spec, rstn_sds_reg & rstn_sds */
        tmp = rtd_inl(CRT_SOFT_RESET1);
        tmp &= ~(BIT_3 | BIT_4);
        rtd_outl(CRT_SOFT_RESET1, tmp);

        /* reg_0x98000004[7] = 0 */
        /* reg_0x98000004[14] = 0 */
        /* CRT spec, rstn_pcie0_power & rstn_pcie0_phy */
        tmp = rtd_inl(CRT_SOFT_RESET2);
        tmp &= ~(BIT_7 | BIT_14);
        rtd_outl(CRT_SOFT_RESET2, tmp);

        /* reg_0x98000050[13] = 0 */
        /* reg_0x98000050[16] = 0 */
        /* CRT spec, rstn_pcie0_sgmii_mdio & rstn_pcie0_phy_mdio */
        tmp = rtd_inl(CRT_SOFT_RESET4);
        tmp &= ~(BIT_13 | BIT_16);
        rtd_outl(CRT_SOFT_RESET4, tmp);
    }

    mdelay(100);
}

static void r8168_pll_clock_init(struct rtl8168_private *tp)
{
    u32 tmp;

    /* reg_0x98007004[27] = 0 */
    /* ISO spec, ETN_PHY_INTR, disable ETN interrupt for ByPassMode */
    rtd_outl(ISO_UMSK_ISR, BIT_27);

    /* reg_0x98007088[10] = 1 */
    /* ISO spec, reset bit of gphy */
    tmp = rtd_inl(ETN_RESET_CTRL);
    tmp |= BIT_10;
    rtd_outl(ETN_RESET_CTRL,tmp);

    mdelay(10); /* wait 10ms for FEPHY PLL stable */

    /* In Hercules, EPHY need choose the bypass mode or Non-bypass mode */
    /* Bypass mode : ETN MAC bypass efuse update flow. SW need to take this sequence. */
    /* Non-Bypass mode : ETN MAC set efuse update and efuse_rdy setting */
    /* Default : Bypass mode (0x9800_7060[1] = 1'b1) */
    if (tp->bypass_enable == 0) {
        /* reg_0x98007060[1] = 0 */
        /* ISO spec, bypass mode disable */
        tmp = rtd_inl(ETN_GPHY_BYPASS);
        tmp &= ~(BIT_1);
        rtd_outl(ETN_GPHY_BYPASS, tmp);
    } else {
        /* reg_0x98007060[1] = 1 */
        /* ISO spec, bypass mode enable */
        /* bypass mode, SW need to handle the EPHY Status check ,
           EFUSE data update and EPHY fuse_rdy setting. */
        tmp = rtd_inl(ETN_GPHY_BYPASS);
        tmp |= BIT_1;
        rtd_outl(ETN_GPHY_BYPASS, tmp);
    }

    /* reg_0x98007088[9] = 1 */
    /* ISO spec, reset bit of gmac */
    tmp = rtd_inl(ETN_RESET_CTRL);
    tmp |= BIT_9;
    rtd_outl(ETN_RESET_CTRL,tmp);

    /* reg_0x9800708c[12:11] = 11 */
    /* ISO spec, clock enable bit for etn clock & etn 250MHz */
    tmp = rtd_inl(ETN_CLK_CTRL);
    tmp |= (BIT_11 | BIT_12);
    rtd_outl(ETN_CLK_CTRL,tmp);

    mdelay(10); /* wait 10ms for GMAC uC to be stable */
}

/* Hercules only uses 13 bits in OTP 0x9801_72C8[12:8] and 0x9801_72D8[7:0]
   if 0x9801_72C8[12] is 1, then 0x9801_72C8[11:8] (R-calibration) is used to set FEPHY
   0x9801_72D8[7:0] is used to set idac_fine for FEPHY
 */
static void r8168_load_otp_content(struct rtl8168_private *tp)
{

    u32 otp;
    u16 tmp;

    otp = (rtd_inl(EFUSE_OTP_REG) & (0x1f << 8)) >> 8;
    if (0 != ((0x1 << 4) & otp)){    /* OTP[4] = valid flag, OTP[3:0] = content */
        tmp = otp ^ R_K_DEFAULT;      /* frc_r_value_default = 0x8 */
        mdio_write(tp, 31, 0xbc0);
        mdio_write(tp, 20, (tmp | (mdio_read(tp, 20) & ~(0x1f << 0))));
    }

    otp = (rtd_inl(EFUSE_OTP_REG + 0x10) & (0xff << 0));
    tmp = otp ^ IDAC_FINE_DEFAULT;      /* IDAC_FINE_DEFAULT = 0x33 */
    mdio_write(tp, 31, 0xbc0);
    mdio_write(tp, 23, (tmp | (mdio_read(tp, 23) & ~(0xff << 0))));
}

static u32 r8168_serdes_init(struct rtl8168_private *tp)
{
    u32 stable_ticks;
    u32 tmp;

    /* reg_0x98000000[4:3] = 11 */
    /* CRT spec, rstn_sds_reg & rstn_sds */
    tmp = rtd_inl(CRT_SOFT_RESET1);
    tmp |= (BIT_3 | BIT_4);
    rtd_outl(CRT_SOFT_RESET1, tmp);

    /* reg_0x98000004[7] = 1 */
    /* reg_0x98000004[14] = 1 */
    /* CRT spec, rstn_pcie0_power & rstn_pcie0_phy */
    tmp = rtd_inl(CRT_SOFT_RESET2);
    tmp |= (BIT_7 | BIT_14);
    rtd_outl(CRT_SOFT_RESET2, tmp);

    /* reg_0x98000050[13] = 1 */
    /* reg_0x98000050[16] = 1 */
    /* CRT spec, rstn_pcie0_sgmii_mdio & rstn_pcie0_phy_mdio */
    tmp = rtd_inl(CRT_SOFT_RESET4);
    tmp |= (BIT_13 | BIT_16);
    rtd_outl(CRT_SOFT_RESET4, tmp);

    /* reg_0x9800000c[7] = 1 */
    /* CRT spec, clk_en_sds */
    tmp = rtd_inl(CRT_CLOCK_ENABLE1);
    tmp |= (BIT_7);
    rtd_outl(CRT_CLOCK_ENABLE1, tmp);

    /* reg_0x9800705c[6] = 1 */
    /* ISO spec, set PCIE channel to SGMII */
    tmp = rtd_inl(ISO_POWERCUT_ETN);
    tmp |= (BIT_6);
    rtd_outl(ISO_POWERCUT_ETN, tmp);

    /* reg_0x9800705c[7] = 1 */
    /* ISO spec, set internal MDIO to PCIE */
    tmp = rtd_inl(ISO_POWERCUT_ETN);
    tmp |= (BIT_7);
    rtd_outl(ISO_POWERCUT_ETN, tmp);

    /* ### Beginning of SGMII DPHY register tuning ### */
    MDIO_LOCK;

    /* reg_0x9800705c[20:16] = 00000 */
    /* ISO spec, set internal PHY addr to SERDES_DPHY_0 */
    tmp = rtd_inl(ISO_POWERCUT_ETN);
    tmp &= ~(BIT_20 | BIT_19 | BIT_18 | BIT_17 | BIT_16);
    tmp |= (SERDES_DPHY_0 << 16);
    rtd_outl(ISO_POWERCUT_ETN, tmp);

    /* # DPHY spec, DPHY reg13[8:7]=00, choose 1.25GHz */
    mdio_write(tp, 0x0d, (mdio_read(tp, 0x0d) & ~(BIT_8 | BIT_7)));

    /* # DPHY spec, 5GHz tuning */
    mdio_write(tp, 0x4, 0x52f5);
    mdio_write(tp, 0x5, 0xead7);
    mdio_write(tp, 0x6, 0x0010);
    mdio_write(tp, 0xa, 0xc653);
    mdio_write(tp, 0x1, 0xa830);


    /* reg_0x9800705c[20:16] = 00001 */
    /* ISO spec, set internal PHY addr to SERDES_DPHY_1 */
    tmp = rtd_inl(ISO_POWERCUT_ETN);
    tmp &= ~(BIT_20 | BIT_19 | BIT_18 | BIT_17 | BIT_16);
    tmp |= (SERDES_DPHY_1 << 16);
    rtd_outl(ISO_POWERCUT_ETN, tmp);

    /* TX_Swing_1040mV */
    mdio_write(tp, 0x0, 0xd4aa);
    mdio_write(tp, 0x1, 0x88aa);

    /* reg_0x9800705c[20:16] = 00001 */
    /* ISO spec, set internal PHY addr to INT_PHY_ADDR */
    tmp = rtd_inl(ISO_POWERCUT_ETN);
    tmp &= ~(BIT_20 | BIT_19 | BIT_18 | BIT_17 | BIT_16);
    tmp |= (INT_PHY_ADDR << 16);
    rtd_outl(ISO_POWERCUT_ETN, tmp);

    tp->ext_phy = true;
    MDIO_UNLOCK;
    mdelay(10);     /* wait for clock stable */


    #if 0
    mdelay(10);
    #else
    /* reg_0x981c8070[9:0] = 0000000110 */
    /* SDS spec, set SP_CFG_SDS_DBG_SEL to get PHY_Ready */
    tmp = rtd_inl(SDS_REG28);
    tmp &= ~(0x3ff << 0);
    tmp |= (0x006 << 0);
    rtd_outl(SDS_REG28, tmp);

    tmp = 0;
    stable_ticks = 0;
    while (10 > stable_ticks) {
        /* # SDS spec, wait for phy ready */
        while (0 == (rtd_inl(SDS_REG29) & BIT_14)) {
            stable_ticks = 0;
            if (tmp >= 100) {
                stable_ticks = 10;
                printf("SGMII PHY not ready in 100ms\n");
                break;
            }
        }
        stable_ticks++;
        tmp++;
        mdelay(1);
    }
    #endif

    /* reg_0x9800705c[4] = 1 */
    /* ISO spec, set data path to SGMII */
    tmp = rtd_inl(ISO_POWERCUT_ETN);
    tmp |= (BIT_4);
    rtd_outl(ISO_POWERCUT_ETN, tmp);

    /* reg_0x981c8008[9:8] = 00 */
    /* # SDS spec, SP_SDS_FRC_AN, SERDES auto mode */
    tmp = rtd_inl(SDS_REG02);
    tmp &= ~(BIT_9 | BIT_8);
    rtd_outl(SDS_REG02, tmp);

    /* # SDS spec, wait for SERDES link up */
    tmp = 0;
    stable_ticks = 0;
    while (10 > stable_ticks) {
        while ( (BIT_13 | BIT_12) != (rtd_inl(SDS_MISC) & (BIT_13 | BIT_12))) {
            stable_ticks = 0;
            if (tmp >= 100) {
                stable_ticks = 10;
                printf("SGMII link down in 100ms\n");
                break;
            }
        }
        stable_ticks++;
        tmp++;
        mdelay(1);
    }
    return 0;
}

static void r8168_fephy_iol_tuning(struct rtl8168_private *tp)
{
    /* idacfine */
    mdio_write(tp, 31, 0xbc0);
    mdio_write(tp, 23, 0x0088);

    /* abiq */
    /* mdio_write(tp, 31, 0xbc0); */
    mdio_write(tp, 21, 0x0004);

    /* ldvbias */
    /* mdio_write(tp, 31, 0xbc0); */
    mdio_write(tp, 22, 0x0777);

    /* iatt */
    mdio_write(tp, 31, 0xbd0);
    mdio_write(tp, 16, 0x0300);

    /* vcm_ref, cf_l */
    /* mdio_write(tp, 31, 0xbd0); */
    mdio_write(tp, 17, 0xf8ca);
}

#endif /* CONFIG_RTD1395 */

int rtl8168_initialize(bd_t *bis)
{
    pci_dev_t devno=0;
    int card_number = 0;
    struct eth_device *dev;
    struct rtl8168_private *tp;
    u32 iobase, tmp;
    //int idx = 0;
    int i;

//   while (0)
    if(1) {
        /* Find RTL8168 */
        //if ((devno = pci_find_devices(supported, idx++)) < 0)
        //    break;

        //pci_read_config_dword(devno, PCI_BASE_ADDRESS_1, &iobase);
        //iobase &= ~0xf;

        iobase = REG_BASE;

        debug ("r8168: REALTEK RTL8168 @0x%x\n", iobase);

        dev = (struct eth_device *)malloc(sizeof *dev);
        if (!dev) {
            printf("Can not allocate memory of r8168\n");
            //    break;
        }
        memset(dev, 0, sizeof(*dev));

        tp = (struct rtl8168_private *)malloc(sizeof *tp);
        if (!tp) {
            printf("Can not allocate memory of r8168\n");
            free(dev);
            //  break;
        }
        memset(tp, 0, sizeof(*tp));
        //tp->mmio_addr = pci_mem_to_phys(devno, iobase);
        tp->mmio_addr = iobase;
        tp->devno = devno;
        tp->dev = dev;
        tp->rx_buf_sz = RX_BUF_SIZE;
        rtl8168_get_env_para(tp);

#if defined(CONFIG_RTD1295)
        // 1295 enable clock

        //1. reg_0x98007088[10] = 1                    // ISO spec, reset bit of gphy
        tmp = rtd_inl(ETN_RESET_CTRL);
        tmp |= BIT_10;
        rtd_outl(ETN_RESET_CTRL,tmp);

        //2. CPU software waiting 200uS
        udelay(200);

        //3. reg_0x98007060[1] = 0                      // ISO spec, Ethernet Boot up bypass gphy ready mode
        tmp = rtd_inl(ETN_GPHY_BYPASS);
        tmp &= ~(BIT_1);
        rtd_outl(ETN_GPHY_BYPASS,tmp);

        //4. reg_0x98007fc0[0] = 0                      // ISO spec, Ethernet Boot up disable dbus clock gating
        tmp = rtd_inl(ETN_DBUS_CLK);
        tmp &= ~(BIT_0);
        rtd_outl(ETN_DBUS_CLK,tmp);

        //5. CPU software waiting 200uS
        udelay(200);

        //6. reg_0x9800708c[12:11] = 11              // ISO spec, clock enable bit for etn clock & etn 250MHz
        tmp = rtd_inl(ETN_CLK_CTRL);
        tmp |= (BIT_11|BIT_12);
        rtd_outl(ETN_CLK_CTRL,tmp);

        //7. reg_0x9800708c[12:11] = 00              // ISO spec, clock enable bit for etn clock & etn 250MHz
        tmp = rtd_inl(ETN_CLK_CTRL);
        tmp &= ~(BIT_11|BIT_12);
        rtd_outl(ETN_CLK_CTRL,tmp);

        //8. reg_0x98007088[9] = 1                      // ISO spec, reset bit of gmac
        tmp = rtd_inl(ETN_RESET_CTRL);
        tmp |= BIT_9;
        rtd_outl(ETN_RESET_CTRL,tmp);

        //9. reg_0x9800708c[12:11] = 11              // ISO spec, clock enable bit for etn clock & etn 250MHz
        tmp = rtd_inl(ETN_CLK_CTRL);
        tmp |= (BIT_11|BIT_12);
        rtd_outl(ETN_CLK_CTRL,tmp);

        mdelay(100);

#elif defined(CONFIG_RTD1395)
        /* disable PHY and GMAC */
        r8168_reset_phy_gmac(tp);

        /* PLL clock init */
        r8168_pll_clock_init(tp);

        /* ISO spec, ETN_PHY_INTR, wait interrupt from FEPHY and it means MDIO is ready */
        tmp = 0;
        while ((rtd_inl(ISO_UMSK_ISR) & BIT_27) == 0) {
            tmp += 10;
            mdelay(10);
            if (tmp >= 100) {
                printf("FEPHY PHY_Status timeout.\n");
                break;
            }
        }
        /* printf("wait %d ms for FEPHY interrupt. UMSK_ISR = 0x%x\n", tmp, rtd_inl(ISO_UMSK_ISR)); */

        MDIO_LOCK;
        /* In Hercules ByPass mode,
           SW need to handle the EPHY Status check ,
           OTP data update and EPHY fuse_rdy setting. */
        if (tp->bypass_enable == 1) {
            /* FEPHY will stay in state 1 mode */
            mdio_write(tp, 31, 0x0a42);
            tmp = 0;
            while (0x1 != (mdio_read(tp, 16) & 0x07)) {
                tmp += 10;
                mdelay(10);
                if (tmp >= 2000) {
                    printf("FEPHY status is not 0x1 in bypass mode, current = 0x%02x\n",
                        (mdio_read(tp, 16) & 0x07));
                    break;
                }
            }

            /* adjust FE PHY electrical characteristics */
            r8168_fephy_iol_tuning(tp);

            /* 1. read OTP 0x9801_72C8[12:8]
               2. xor 0x08
               3. set value to FEPHY registers to correct R-calibration
               4. read OTP 0x9801_72D8[7:0]
               5. xor 0x33
               6. set value to FEPHY registers to correct AMP
             */
            r8168_load_otp_content(tp);

            /* fill fuse_rdy & rg_ext_ini_done */
            mdio_write(tp, 31, 0x0a46);
            mdio_write(tp, 20, (mdio_read(tp, 20) | (BIT_0 | BIT_1)));
        } else {
            /* adjust FE PHY electrical characteristics */
            r8168_fephy_iol_tuning(tp);
        }

        /* wait LAN-ON */
        mdio_write(tp, 31, 0x0a42);
        tmp = 0;
        do {
            tmp += 10;
            mdelay(10);
            if (tmp >= 2000) {
                printf("FEPHY status is not 0x3, current = 0x%02x\n", (mdio_read(tp, 16) & 0x07));
                break;
            }
        } while (0x3 != (mdio_read(tp, 16) & 0x07));
        MDIO_UNLOCK;
        /* printf("wait %d ms for FEPHY ready, current = 0x%x\n", tmp, mdio_read(tp, 16)); */

        if (tp->phy_type == PHY_TYPE_FEPHY) {
            /* Init FEPHY path */
            /* reg_0x9800705c[5] = 0 */
            /* reg_0x9800705c[7] = 0 */
            /* ISO spec, set internal MDIO to access FEPHY */
            tmp = rtd_inl(ISO_POWERCUT_ETN);
            tmp &= ~(BIT_7 | BIT_5);
            rtd_outl(ISO_POWERCUT_ETN, tmp);

            /* reg_0x9800705c[4] = 0 */
            /* ISO spec, set data path to access FEPHY */
            tmp = rtd_inl(ISO_POWERCUT_ETN);
            tmp &= ~(BIT_4);
            rtd_outl(ISO_POWERCUT_ETN, tmp);

            /* # ETN spec, GMAC data path select MII-like(embedded GPHY), not SGMII(external PHY) */
            tmp = mac_ocp_read(tp, 0xEA34);
            tmp &= ~(BIT_1 | BIT_0);
            tmp |= BIT_1;
            mac_ocp_write(tp, 0xEA34, tmp);
        } else {
            /* SGMII */
            /* # ETN spec, adjust MDC freq=2.5MHz */
            mac_ocp_write(tp, 0xDE30, mac_ocp_read(tp, 0xDE30) & ~(BIT_6 | BIT_7));
            /* # ETN spec, set external PHY addr */
            mac_ocp_write(tp, 0xDE24, ((mac_ocp_read(tp, 0xDE24) & ~(0x1f << 0)) | (EXT_PHY_ADDR & 0x1f)));
            /* ISO mux spec, GPIO29 is set to MDC pin */
            tmp = rtd_inl(ISO_GPIO_MUXPAD2);
            tmp &= ~(BIT_6 | BIT_7 | BIT_8);
            tmp |= BIT_8;
            rtd_outl(ISO_GPIO_MUXPAD2, tmp);
            /* ISO mux spec, GPIO46 is set to MDIO pin */
            tmp = rtd_inl(ISO_GPIO_MUXPAD3);
            tmp &= ~(BIT_15 | BIT_16 | BIT_17);
            tmp |= BIT_17;
            rtd_outl(ISO_GPIO_MUXPAD3, tmp);

            /* check if external PHY is available */
            printf("Searching external PHY...");
            MDIO_LOCK;
            tp->ext_phy = true;
            mdio_write(tp, 31, 0x0a43);
            tmp = 0;
            while (0xa43 != mdio_read(tp, 31)){
                printf(".");
                tmp += 100;
                mdelay(100);
                if (tmp >= 2000) {
                    printf("\n External SGMII PHY not found, current = 0x%02x\n", mdio_read(tp, 31));
                    break;
                }
            }
            if (tmp < 2000)
                printf("found.\n");

            /* lower SGMII TX swing of RTL8211FS to reduce EMI */
            mdio_write(tp, 31, 0x0dcd);
            mdio_write(tp, 16, 0x104e); /* TX swing = 470mV, default value */

            tp->ext_phy = false;
            MDIO_UNLOCK;

            /* # ETN spec, GMAC data path select SGMII(external PHY), not MII-like(embedded GPHY) */
            tmp = mac_ocp_read(tp, 0xEA34);
            tmp |= (BIT_1 | BIT_0);
            mac_ocp_write(tp, 0xEA34, tmp);

            if (0 != r8168_serdes_init(tp))
                printf("SERDES init failed\n");

            /* SDS spec, auto update SGMII link capability */
            tmp = rtd_inl(SDS_LINK);
            tmp |= BIT_2;
            rtd_outl(SDS_LINK, tmp);
        }

        /* SBX spec, Select ETN access DDR path. */
        if (tp->acp_enable == 1) {
            /* through ACP to SCPU_ACP */
            tmp = rtd_inl(SBX_ACP_MISC_CTRL);
            tmp |= BIT_17;
            rtd_outl(SBX_ACP_MISC_CTRL, tmp);
        } else {
            /* through SB3 to DC_SYS (default) */
            tmp = rtd_inl(SBX_ACP_MISC_CTRL);
            tmp &= ~(BIT_17);
            rtd_outl(SBX_ACP_MISC_CTRL, tmp);
        }

#endif /* CONFIG_RTD1295 | CONFIG_RTD1395 */

        /* Identify chip attached to board */
        rtl8168_get_mac_version(tp, tp->mmio_addr);

        rtl8168_print_mac_version(tp);

        sprintf(dev->name, "r8168#%d", card_number);
        printf("dev->name=%s\n",dev->name);
        rtl8168_get_mac_address(tp);

        for (i = ARRAY_SIZE(rtl_chip_info) - 1; i >= 0; i--) {
            if (tp->mcfg == rtl_chip_info[i].mcfg)
                break;
        }

        if (i < 0) {
            /* Unknown chip: assume array element #0, original RTL-8168 */
            printf("Realtek unknown chip version, assuming %s\n", rtl_chip_info[0].name);
            i++;
        }

        tp->chipset = i;

        dev->priv = (void *)tp;
        dev->iobase = (int)tp->mmio_addr;

        dev->init = rtl8168_init;
        dev->halt = rtl8168_halt;
        dev->send = rtl8168_send;
        dev->recv = rtl8168_recv;

        eth_register (dev);

        card_number++;

        // LED setting
#ifdef CONFIG_CMD_NET_LED_FOR_WD
        rtd_outl((REG_BASE+CustomLED),0x0006804F);

        // switch Mux to Ethernet LED RXTX/LINK mode.
        tmp = rtd_inl(0x98007310);
        tmp |= (BIT_28 | BIT_26);
        rtd_outl(0x98007310, tmp);

        tmp = (rtd_inl(0x98007028) & BIT_11) >> 11;
        if (tmp == 0) {
            // 1295 switch IGPIO30 pin mux and out direction
            tmp = rtd_inl(0x98007100);
            tmp |= BIT_30;
            rtd_outl(0x98007100, tmp);

            tmp = rtd_inl(0x98007104);
            tmp |= BIT_30;
            rtd_outl(0x98007104, tmp);
        }
    else{
            // 1296 switch IGPIO32 pin mux and out direction
            tmp = rtd_inl(0x98007118);
            tmp |= BIT_0;
            rtd_outl(0x98007118, tmp);

            tmp = rtd_inl(0x9800711c);
            tmp |= BIT_0;
            rtd_outl(0x9800711c, tmp);
        }
#else
        rtd_outl((REG_BASE+CustomLED),0x000670ca);
#endif

#if defined(CONFIG_RTD1295)
        // fine tune embedded GPHY
        mdio_write(tp, 0x1f, 0x0BC0);
        mdio_write(tp, 0x11, 0x0B10);
        mdio_write(tp, 0x1f, 0x0A43);
        mdio_write(tp, 0x1b, 0x8082);
        mdio_write(tp, 0x1c, 0xFE00);

        /* check efuse for kylin B00, B01, and etc. */
        if ((KYLIN_CHIP_ID == get_asic_chip_id()) && (RTD129x_CHIP_REVISION_B00 <= get_rtd129x_cpu_revision())){
            switch (((0x3 << 24) & rtd_inl(EFUSE_OTP_REG)) >> 24) {
            case 0:  /* apply default values */
                mdio_write(tp, 0x1f, 0x0BCD);
                mdio_write(tp, 22, 0x8888); /* RC-K */
                mdio_write(tp, 23, 0x8888); /* RC-K */

                mdio_write(tp, 0x1f, 0x0BCE);
                mdio_write(tp, 16, 0x8888); /* R-K */
                mdio_write(tp, 17, 0x8888); /* R-K */
                break;
            case 1:  /* apply another efuse values */
                tmp = ((0xf << 20) & rtd_inl(EFUSE_OTP_REG)) >> 20;
                tmp = tmp ^ 0x8;
                tmp = (tmp << 12) | (tmp << 8) | (tmp << 4) | tmp;
                mdio_write(tp, 0x1f, 0x0BCD);
                mdio_write(tp, 22, tmp); /* RC-K */
                mdio_write(tp, 23, tmp); /* RC-K */

                tmp = ((0xf << 16) & rtd_inl(EFUSE_OTP_REG)) >> 16;
                tmp = tmp ^ 0x8;
                tmp = (tmp << 12) | (tmp << 8) | (tmp << 4) | tmp;
                mdio_write(tp, 0x1f, 0x0BCE);
                mdio_write(tp, 16, tmp); /* R-K */
                mdio_write(tp, 17, tmp); /* R-K */
                break;
            case 2:  /* normal IC */
                break;
            case 3:  /* reserved */
                break;
            }
        }
#endif /* CONFIG_RTD1295 */

    }

    return card_number;
}
