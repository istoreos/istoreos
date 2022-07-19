/**************************************************************
// Spec Version                  : 0.0.2
// Parser Version                : DVR_Parser_6.11(120105)
// CModelGen Version             : 5.1 2012.01.05
// Naming Rule                   :  Register_Name
// Naming Rule                   : Module_Register_Name_reg
// Parse Option                  : Only Parse _op1
// Parse Address Region          : All Address Region 
// Decode bit number             : 12 bits
// Firmware Header Generate Date : 7/20/2012 0:53:45
***************************************************************/


#ifndef _USB_REG_H_INCLUDED_
#define _USB_REG_H_INCLUDED_


/* Global constants */
#define DWC3_EP0_BOUNCE_SIZE	512
#define DWC3_ENDPOINTS_NUM	32
#define DWC3_XHCI_RESOURCES_NUM	2

#define DWC3_EVENT_SIZE		4	/* bytes */
#define DWC3_EVENT_MAX_NUM	64	/* 2 events/endpoint */
#define DWC3_EVENT_BUFFERS_SIZE	(DWC3_EVENT_SIZE * DWC3_EVENT_MAX_NUM)
#define DWC3_EVENT_TYPE_MASK	0xfe

#define DWC3_EVENT_TYPE_DEV	0
#define DWC3_EVENT_TYPE_CARKIT	3
#define DWC3_EVENT_TYPE_I2C	4

#define DWC3_DEVICE_EVENT_DISCONNECT		0
#define DWC3_DEVICE_EVENT_RESET			1
#define DWC3_DEVICE_EVENT_CONNECT_DONE		2
#define DWC3_DEVICE_EVENT_LINK_STATUS_CHANGE	3
#define DWC3_DEVICE_EVENT_WAKEUP		4
#define DWC3_DEVICE_EVENT_HIBER_REQ		5
#define DWC3_DEVICE_EVENT_EOPF			6
#define DWC3_DEVICE_EVENT_SOF			7
#define DWC3_DEVICE_EVENT_ERRATIC_ERROR		9
#define DWC3_DEVICE_EVENT_CMD_CMPL		10
#define DWC3_DEVICE_EVENT_OVERFLOW		11

#define DWC3_GEVNTCOUNT_MASK	0xfffc
#define DWC3_GSNPSID_MASK	0xffff0000
#define DWC3_GSNPSREV_MASK	0xffff

/* DWC3 registers memory space boundries */
#define DWC3_XHCI_REGS_START		0x0
#define DWC3_XHCI_REGS_END		0x7fff
#define DWC3_GLOBALS_REGS_START		0xc100
#define DWC3_GLOBALS_REGS_END		0xc6ff
#define DWC3_DEVICE_REGS_START		0xc700
#define DWC3_DEVICE_REGS_END		0xcbff
#define DWC3_OTG_REGS_START		0xcc00
#define DWC3_OTG_REGS_END		0xccff

/* Global Registers */
#define DWC3_GSBUSCFG0		0xc100
#define DWC3_GSBUSCFG1		0xc104
#define DWC3_GTXTHRCFG		0xc108
#define DWC3_GRXTHRCFG		0xc10c
#define DWC3_GCTL		0xc110
#define DWC3_GEVTEN		0xc114
#define DWC3_GSTS		0xc118
#define DWC3_GSNPSID		0xc120
#define DWC3_GGPIO		0xc124
#define DWC3_GUID		0xc128
#define DWC3_GUCTL		0xc12c
#define DWC3_GBUSERRADDR0	0xc130
#define DWC3_GBUSERRADDR1	0xc134
#define DWC3_GPRTBIMAP0		0xc138
#define DWC3_GPRTBIMAP1		0xc13c
#define DWC3_GHWPARAMS0		0xc140
#define DWC3_GHWPARAMS1		0xc144
#define DWC3_GHWPARAMS2		0xc148
#define DWC3_GHWPARAMS3		0xc14c
#define DWC3_GHWPARAMS4		0xc150
#define DWC3_GHWPARAMS5		0xc154
#define DWC3_GHWPARAMS6		0xc158
#define DWC3_GHWPARAMS7		0xc15c
#define DWC3_GDBGFIFOSPACE	0xc160
#define DWC3_GDBGLTSSM		0xc164
#define DWC3_GPRTBIMAP_HS0	0xc180
#define DWC3_GPRTBIMAP_HS1	0xc184
#define DWC3_GPRTBIMAP_FS0	0xc188
#define DWC3_GPRTBIMAP_FS1	0xc18c

#define DWC3_GUSB2PHYCFG(n)	(0xc200 + (n * 0x04))
#define DWC3_GUSB2I2CCTL(n)	(0xc240 + (n * 0x04))

#define DWC3_GUSB2PHYACC(n)	(0xc280 + (n * 0x04))

#define DWC3_GUSB3PIPECTL(n)	(0xc2c0 + (n * 0x04))

#define DWC3_GTXFIFOSIZ(n)	(0xc300 + (n * 0x04))
#define DWC3_GRXFIFOSIZ(n)	(0xc380 + (n * 0x04))

#define DWC3_GEVNTADRLO(n)	(0xc400 + (n * 0x10))
#define DWC3_GEVNTADRHI(n)	(0xc404 + (n * 0x10))
#define DWC3_GEVNTSIZ(n)	(0xc408 + (n * 0x10))
#define DWC3_GEVNTCOUNT(n)	(0xc40c + (n * 0x10))

#define DWC3_GHWPARAMS8		0xc600

/* Device Registers */
#define DWC3_DCFG		0xc700
#define DWC3_DCTL		0xc704
#define DWC3_DEVTEN		0xc708
#define DWC3_DSTS		0xc70c
#define DWC3_DGCMDPAR		0xc710
#define DWC3_DGCMD		0xc714
#define DWC3_DALEPENA		0xc720
#define DWC3_DEPCMDPAR2(n)	(0xc800 + (n * 0x10))
#define DWC3_DEPCMDPAR1(n)	(0xc804 + (n * 0x10))
#define DWC3_DEPCMDPAR0(n)	(0xc808 + (n * 0x10))
#define DWC3_DEPCMD(n)		(0xc80c + (n * 0x10))

/* OTG Registers */
#define DWC3_OCFG		0xcc00
#define DWC3_OCTL		0xcc04
#define DWC3_OEVT		0xcc08
#define DWC3_OEVTEN		0xcc0C
#define DWC3_OSTS		0xcc10

/* Bit fields */

/* Global Configuration Register */
#define DWC3_GCTL_PWRDNSCALE(n)	((n) << 19)
#define DWC3_GCTL_U2RSTECN	(1 << 16)
#define DWC3_GCTL_RAMCLKSEL(x)	(((x) & DWC3_GCTL_CLK_MASK) << 6)
#define DWC3_GCTL_CLK_BUS	(0)
#define DWC3_GCTL_CLK_PIPE	(1)
#define DWC3_GCTL_CLK_PIPEHALF	(2)
#define DWC3_GCTL_CLK_MASK	(3)

#define DWC3_GCTL_PRTCAP(n)	(((n) & (3 << 12)) >> 12)
#define DWC3_GCTL_PRTCAPDIR(n)	((n) << 12)
#define DWC3_GCTL_PRTCAP_HOST	1
#define DWC3_GCTL_PRTCAP_DEVICE	2
#define DWC3_GCTL_PRTCAP_OTG	3

#define DWC3_GCTL_CORESOFTRESET		(1 << 11)
#define DWC3_GCTL_SCALEDOWN(n)		((n) << 4)
#define DWC3_GCTL_SCALEDOWN_MASK	DWC3_GCTL_SCALEDOWN(3)
#define DWC3_GCTL_DISSCRAMBLE		(1 << 3)
#define DWC3_GCTL_GBLHIBERNATIONEN	(1 << 1)
#define DWC3_GCTL_DSBLCLKGTNG		(1 << 0)

/* Global USB2 PHY Configuration Register */
#define DWC3_GUSB2PHYCFG_PHYSOFTRST	(1 << 31)
#define DWC3_GUSB2PHYCFG_SUSPHY		(1 << 6)

/* Global USB3 PIPE Control Register */
#define DWC3_GUSB3PIPECTL_PHYSOFTRST	(1 << 31)
#define DWC3_GUSB3PIPECTL_SUSPHY	(1 << 17)

/* Global TX Fifo Size Register */
#define DWC3_GTXFIFOSIZ_TXFDEF(n)	((n) & 0xffff)
#define DWC3_GTXFIFOSIZ_TXFSTADDR(n)	((n) & 0xffff0000)

/* Global Event Size Registers */
#define DWC3_GEVNTSIZ_INTMASK		(1 << 31)
#define DWC3_GEVNTSIZ_SIZE(n)		((n) & 0xffff)

/* Global HWPARAMS1 Register */
#define DWC3_GHWPARAMS1_EN_PWROPT(n)	(((n) & (3 << 24)) >> 24)
#define DWC3_GHWPARAMS1_EN_PWROPT_NO	0
#define DWC3_GHWPARAMS1_EN_PWROPT_CLK	1
#define DWC3_GHWPARAMS1_EN_PWROPT_HIB	2
#define DWC3_GHWPARAMS1_PWROPT(n)	((n) << 24)
#define DWC3_GHWPARAMS1_PWROPT_MASK	DWC3_GHWPARAMS1_PWROPT(3)

/* Global HWPARAMS4 Register */
#define DWC3_GHWPARAMS4_HIBER_SCRATCHBUFS(n)	(((n) & (0x0f << 13)) >> 13)
#define DWC3_MAX_HIBER_SCRATCHBUFS		15

/* Device Configuration Register */
#define DWC3_DCFG_LPM_CAP	(1 << 22)
#define DWC3_DCFG_DEVADDR(addr)	((addr) << 3)
#define DWC3_DCFG_DEVADDR_MASK	DWC3_DCFG_DEVADDR(0x7f)

#define DWC3_DCFG_SPEED_MASK	(7 << 0)
#define DWC3_DCFG_SUPERSPEED	(4 << 0)
#define DWC3_DCFG_HIGHSPEED	(0 << 0)
#define DWC3_DCFG_FULLSPEED2	(1 << 0)
#define DWC3_DCFG_LOWSPEED	(2 << 0)
#define DWC3_DCFG_FULLSPEED1	(3 << 0)

#define DWC3_DCFG_LPM_CAP	(1 << 22)

/* Device Control Register */
#define DWC3_DCTL_RUN_STOP	(1 << 31)
#define DWC3_DCTL_CSFTRST	(1 << 30)
#define DWC3_DCTL_LSFTRST	(1 << 29)

#define DWC3_DCTL_HIRD_THRES_MASK	(0x1f << 24)
#define DWC3_DCTL_HIRD_THRES(n)	((n) << 24)

#define DWC3_DCTL_APPL1RES	(1 << 23)

/* These apply for core versions 1.87a and earlier */
#define DWC3_DCTL_TRGTULST_MASK		(0x0f << 17)
#define DWC3_DCTL_TRGTULST(n)		((n) << 17)
#define DWC3_DCTL_TRGTULST_U2		(DWC3_DCTL_TRGTULST(2))
#define DWC3_DCTL_TRGTULST_U3		(DWC3_DCTL_TRGTULST(3))
#define DWC3_DCTL_TRGTULST_SS_DIS	(DWC3_DCTL_TRGTULST(4))
#define DWC3_DCTL_TRGTULST_RX_DET	(DWC3_DCTL_TRGTULST(5))
#define DWC3_DCTL_TRGTULST_SS_INACT	(DWC3_DCTL_TRGTULST(6))

/* These apply for core versions 1.94a and later */
#define DWC3_DCTL_KEEP_CONNECT	(1 << 19)
#define DWC3_DCTL_L1_HIBER_EN	(1 << 18)
#define DWC3_DCTL_CRS		(1 << 17)
#define DWC3_DCTL_CSS		(1 << 16)

#define DWC3_DCTL_INITU2ENA	(1 << 12)
#define DWC3_DCTL_ACCEPTU2ENA	(1 << 11)
#define DWC3_DCTL_INITU1ENA	(1 << 10)
#define DWC3_DCTL_ACCEPTU1ENA	(1 << 9)
#define DWC3_DCTL_TSTCTRL_MASK	(0xf << 1)

#define DWC3_DCTL_ULSTCHNGREQ_MASK	(0x0f << 5)
#define DWC3_DCTL_ULSTCHNGREQ(n) (((n) << 5) & DWC3_DCTL_ULSTCHNGREQ_MASK)

#define DWC3_DCTL_ULSTCHNG_NO_ACTION	(DWC3_DCTL_ULSTCHNGREQ(0))
#define DWC3_DCTL_ULSTCHNG_SS_DISABLED	(DWC3_DCTL_ULSTCHNGREQ(4))
#define DWC3_DCTL_ULSTCHNG_RX_DETECT	(DWC3_DCTL_ULSTCHNGREQ(5))
#define DWC3_DCTL_ULSTCHNG_SS_INACTIVE	(DWC3_DCTL_ULSTCHNGREQ(6))
#define DWC3_DCTL_ULSTCHNG_RECOVERY	(DWC3_DCTL_ULSTCHNGREQ(8))
#define DWC3_DCTL_ULSTCHNG_COMPLIANCE	(DWC3_DCTL_ULSTCHNGREQ(10))
#define DWC3_DCTL_ULSTCHNG_LOOPBACK	(DWC3_DCTL_ULSTCHNGREQ(11))

/* Device Event Enable Register */
#define DWC3_DEVTEN_VNDRDEVTSTRCVEDEN	(1 << 12)
#define DWC3_DEVTEN_EVNTOVERFLOWEN	(1 << 11)
#define DWC3_DEVTEN_CMDCMPLTEN		(1 << 10)
#define DWC3_DEVTEN_ERRTICERREN		(1 << 9)
#define DWC3_DEVTEN_SOFEN		(1 << 7)
#define DWC3_DEVTEN_EOPFEN		(1 << 6)
#define DWC3_DEVTEN_HIBERNATIONREQEVTEN	(1 << 5)
#define DWC3_DEVTEN_WKUPEVTEN		(1 << 4)
#define DWC3_DEVTEN_ULSTCNGEN		(1 << 3)
#define DWC3_DEVTEN_CONNECTDONEEN	(1 << 2)
#define DWC3_DEVTEN_USBRSTEN		(1 << 1)
#define DWC3_DEVTEN_DISCONNEVTEN	(1 << 0)

/* Device Status Register */
#define DWC3_DSTS_DCNRD			(1 << 29)

/* This applies for core versions 1.87a and earlier */
#define DWC3_DSTS_PWRUPREQ		(1 << 24)

/* These apply for core versions 1.94a and later */
#define DWC3_DSTS_RSS			(1 << 25)
#define DWC3_DSTS_SSS			(1 << 24)

#define DWC3_DSTS_COREIDLE		(1 << 23)
#define DWC3_DSTS_DEVCTRLHLT		(1 << 22)

#define DWC3_DSTS_USBLNKST_MASK		(0x0f << 18)
#define DWC3_DSTS_USBLNKST(n)		(((n) & DWC3_DSTS_USBLNKST_MASK) >> 18)

#define DWC3_DSTS_RXFIFOEMPTY		(1 << 17)

#define DWC3_DSTS_SOFFN_MASK		(0x3fff << 3)
#define DWC3_DSTS_SOFFN(n)		(((n) & DWC3_DSTS_SOFFN_MASK) >> 3)

#define DWC3_DSTS_CONNECTSPD		(7 << 0)

#define DWC3_DSTS_SUPERSPEED		(4 << 0)
#define DWC3_DSTS_HIGHSPEED		(0 << 0)
#define DWC3_DSTS_FULLSPEED2		(1 << 0)
#define DWC3_DSTS_LOWSPEED		(2 << 0)
#define DWC3_DSTS_FULLSPEED1		(3 << 0)

/* Device Generic Command Register */
#define DWC3_DGCMD_SET_LMP		0x01
#define DWC3_DGCMD_SET_PERIODIC_PAR	0x02
#define DWC3_DGCMD_XMIT_FUNCTION	0x03

/* These apply for core versions 1.94a and later */
#define DWC3_DGCMD_SET_SCRATCHPAD_ADDR_LO	0x04
#define DWC3_DGCMD_SET_SCRATCHPAD_ADDR_HI	0x05

#define DWC3_DGCMD_SELECTED_FIFO_FLUSH	0x09
#define DWC3_DGCMD_ALL_FIFO_FLUSH	0x0a
#define DWC3_DGCMD_SET_ENDPOINT_NRDY	0x0c
#define DWC3_DGCMD_RUN_SOC_BUS_LOOPBACK	0x10

#define DWC3_DGCMD_STATUS(n)		(((n) >> 15) & 1)
#define DWC3_DGCMD_CMDACT		(1 << 10)
#define DWC3_DGCMD_CMDIOC		(1 << 8)

/* Device Generic Command Parameter Register */
#define DWC3_DGCMDPAR_FORCE_LINKPM_ACCEPT	(1 << 0)
#define DWC3_DGCMDPAR_FIFO_NUM(n)		((n) << 0)
#define DWC3_DGCMDPAR_RX_FIFO			(0 << 5)
#define DWC3_DGCMDPAR_TX_FIFO			(1 << 5)
#define DWC3_DGCMDPAR_LOOPBACK_DIS		(0 << 0)
#define DWC3_DGCMDPAR_LOOPBACK_ENA		(1 << 0)

/* Device Endpoint Command Register */
#define DWC3_DEPCMD_PARAM_SHIFT		16
#define DWC3_DEPCMD_PARAM(x)		((x) << DWC3_DEPCMD_PARAM_SHIFT)
#define DWC3_DEPCMD_GET_RSC_IDX(x)     (((x) >> DWC3_DEPCMD_PARAM_SHIFT) & 0x7f)
#define DWC3_DEPCMD_STATUS(x)		(((x) >> 15) & 1)
#define DWC3_DEPCMD_HIPRI_FORCERM	(1 << 11)
#define DWC3_DEPCMD_CMDACT		(1 << 10)
#define DWC3_DEPCMD_CMDIOC		(1 << 8)

#define DWC3_DEPCMD_DEPSTARTCFG		(0x09 << 0)
#define DWC3_DEPCMD_ENDTRANSFER		(0x08 << 0)
#define DWC3_DEPCMD_UPDATETRANSFER	(0x07 << 0)
#define DWC3_DEPCMD_STARTTRANSFER	(0x06 << 0)
#define DWC3_DEPCMD_CLEARSTALL		(0x05 << 0)
#define DWC3_DEPCMD_SETSTALL		(0x04 << 0)
/* This applies for core versions 1.90a and earlier */
#define DWC3_DEPCMD_GETSEQNUMBER	(0x03 << 0)
/* This applies for core versions 1.94a and later */
#define DWC3_DEPCMD_GETEPSTATE		(0x03 << 0)
#define DWC3_DEPCMD_SETTRANSFRESOURCE	(0x02 << 0)
#define DWC3_DEPCMD_SETEPCONFIG		(0x01 << 0)

/* The EP number goes 0..31 so ep0 is always out and ep1 is always in */
#define DWC3_DALEPENA_EP(n)		(1 << n)

#define DWC3_DEPCMD_TYPE_CONTROL	0
#define DWC3_DEPCMD_TYPE_ISOC		1
#define DWC3_DEPCMD_TYPE_BULK		2
#define DWC3_DEPCMD_TYPE_INTR		3



#define DWC3_REVISION_173A	0x5533173a
#define DWC3_REVISION_175A	0x5533175a
#define DWC3_REVISION_180A	0x5533180a
#define DWC3_REVISION_183A	0x5533183a
#define DWC3_REVISION_185A	0x5533185a
#define DWC3_REVISION_187A	0x5533187a
#define DWC3_REVISION_188A	0x5533188a
#define DWC3_REVISION_190A	0x5533190a
#define DWC3_REVISION_194A	0x5533194a
#define DWC3_REVISION_200A	0x5533200a
#define DWC3_REVISION_202A	0x5533202a
#define DWC3_REVISION_210A	0x5533210a
#define DWC3_REVISION_220A	0x5533220a
#define DWC3_REVISION_230A	0x5533230a
#define DWC3_REVISION_240A	0x5533240a
#define DWC3_REVISION_250A	0x5533250a





#ifdef  _USB_USE_STRUCT
typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     sram_debug_sel:1;
unsigned int     sram_debug_mode:1;
unsigned int     dbus_multi_req_disable:1;
unsigned int     dev_mode:1;
}WRAP_CTR;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     host_int:1;
}GNR_INT;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     reset_utmi_p3:1;
unsigned int     reset_utmi_p2:1;
unsigned int     reset_utmi_p1:1;
unsigned int     reset_utmi_p0:1;
}USB2_PHY_UTMI;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     reset_pipe3_p0:1;
}USB3_PHY_PIPE;

typedef struct 
{
unsigned int     data:16;
unsigned int     phy_addr:3;
unsigned int     phy_reg_addr:5;
unsigned int     mdio_busy:1;
unsigned int     mdio_st:2;
unsigned int     mdio_rdy:1;
unsigned int     mclk_rate:2;
unsigned int     mdio_srst:1;
unsigned int     mdio_rdwr:1;
}MDIO_CTR;

typedef struct 
{
unsigned int     p3_vstatus_out:8;
unsigned int     p2_vstatus_out:8;
unsigned int     p1_vstatus_out:8;
unsigned int     p0_vstatus_out:8;
}VSTATUS0_OUT;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     simulation_mode_p3:1;
unsigned int     force_hs_mode_p3:1;
unsigned int     test_rst_p3:1;
unsigned int     test_en_p3:1;
unsigned int     simulation_mode_p2:1;
unsigned int     force_hs_mode_p2:1;
unsigned int     test_rst_p2:1;
unsigned int     test_en_p2:1;
unsigned int     simulation_mode_p1:1;
unsigned int     force_hs_mode_p1:1;
unsigned int     test_rst_p1:1;
unsigned int     test_en_p1:1;
unsigned int     simulation_mode_p0:1;
unsigned int     force_hs_mode_p0:1;
unsigned int     test_rst_p0:1;
unsigned int     test_en_p0:1;
}SLP_BACK0_EN;

typedef struct 
{
unsigned int     reserved_0:20;
unsigned int     test_speed_p0:2;
unsigned int     test_seed_p0:8;
unsigned int     test_psl_p0:2;
}SLP_BACK0_CTR;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     test_fail_p0:1;
unsigned int     test_done_p0:1;
}SLP_BACK0_ST;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     p0_usb2phy_slb_hs:1;
unsigned int     p0_usb2phy_force_slb:1;
}PHY2_SLB0_EN;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     p0_usb2phy_slb_fail:1;
unsigned int     p0_usb2phy_slb_done:1;
}PHY2_SLB0_ST;

typedef struct 
{
unsigned int     reserved_0:20;
unsigned int     test_speed_p1:2;
unsigned int     test_seed_p1:8;
unsigned int     test_psl_p1:2;
}SLP_BACK1_CTR;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     test_fail_p1:1;
unsigned int     test_done_p1:1;
}SLP_BACK1_ST;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     p1_usb2phy_slb_hs:1;
unsigned int     p1_usb2phy_force_slb:1;
}PHY2_SLB1_EN;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     p1_usb2phy_slb_fail:1;
unsigned int     p1_usb2phy_slb_done:1;
}PHY2_SLB1_ST;

typedef struct 
{
unsigned int     reserved_0:20;
unsigned int     test_speed_p2:2;
unsigned int     test_seed_p2:8;
unsigned int     test_psl_p2:2;
}SLP_BACK2_CTR;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     test_fail_p2:1;
unsigned int     test_done_p2:1;
}SLP_BACK2_ST;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     p2_usb2phy_slb_hs:1;
unsigned int     p2_usb2phy_force_slb:1;
}PHY2_SLB2_EN;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     p2_usb2phy_slb_fail:1;
unsigned int     p2_usb2phy_slb_done:1;
}PHY2_SLB2_ST;

typedef struct 
{
unsigned int     reserved_0:20;
unsigned int     test_speed_p3:2;
unsigned int     test_seed_p3:8;
unsigned int     test_psl_p3:2;
}SLP_BACK3_CTR;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     test_fail_p3:1;
unsigned int     test_done_p3:1;
}SLP_BACK3_ST;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     p3_usb2phy_slb_hs:1;
unsigned int     p3_usb2phy_force_slb:1;
}PHY2_SLB3_EN;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     p3_usb2phy_slb_fail:1;
unsigned int     p3_usb2phy_slb_done:1;
}PHY2_SLB3_ST;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     p3_suspend_r:1;
unsigned int     p2_suspend_r:1;
unsigned int     p1_suspend_r:1;
unsigned int     p0_suspend_r:1;
}USB2_SPD_CTR;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     p0_pipe_bist_sel:2;
unsigned int     p0_pipe_bist_en:1;
}PHY3_SLB_EN;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     p0_usb3phy_slb_go:1;
}PHY3_SLB_CT;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     p0_usb3phy_slb_fail:1;
unsigned int     p0_usb3phy_slb_done:1;
}PHY3_SLB_ST;

typedef struct 
{
unsigned int     reserved_0:19;
unsigned int     dbg_sel1:6;
unsigned int     dbg_sel0:6;
unsigned int     dbg_en:1;
}USB_DBG;

typedef struct 
{
unsigned int     reg1:16;
unsigned int     reg0:16;
}USB_SCTCH;

typedef struct 
{
unsigned int     test_sp_reg:32;
}USB_TMP_SP;

typedef struct 
{
unsigned int     test_reg:32;
}USB_TMP;

typedef struct 
{
unsigned int     xhci_revision:1;
unsigned int     host_fladj_30mhz:6;
unsigned int     host_ppc_present:1;
unsigned int     host_msi_enable:1;
unsigned int     host_pm_pw_state_req:2;
unsigned int     hub_port_perm_attach:5;
unsigned int     reserved_0:3;
unsigned int     host_u2_port_disable:4;
unsigned int     host_u3_port_disable:1;
unsigned int     host_num_u2_port:4;
unsigned int     host_num_u3_port:4;
}HMAC_CTR0;

typedef struct 
{
unsigned int     host_utmiotg_vbusvalid:4;
unsigned int     host_mac_vbus_inv:4;
unsigned int     host_vbus_value:4;
unsigned int     host_vbus_sel:4;
unsigned int     reserved_0:4;
unsigned int     hub_port_over_cur_inv:4;
unsigned int     host_over_cur_value:4;
unsigned int     host_over_cur_sel:4;
}HMAC_CTR1;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     host_current_power_state:2;
unsigned int     host_hub_vbus_ctrl:5;
}MAC3_HST_ST;

typedef struct 
{
unsigned int     reserved_0:21;
unsigned int     p0_DmPulldown:1;
unsigned int     p0_DpPulldown:1;
unsigned int     p0_IDPULLUP:1;
unsigned int     reserved_1:5;
unsigned int     p0_DmPulldown_sel:1;
unsigned int     p0_DpPulldown_sel:1;
unsigned int     p0_IDPULLUP_sel:1;
}USB2_PHY0;

typedef struct 
{
unsigned int     reserved_0:21;
unsigned int     p1_DmPulldown:1;
unsigned int     p1_DpPulldown:1;
unsigned int     p1_IDPULLUP:1;
unsigned int     reserved_1:5;
unsigned int     p1_DmPulldown_sel:1;
unsigned int     p1_DpPulldown_sel:1;
unsigned int     p1_IDPULLUP_sel:1;
}USB2_PHY1;

typedef struct 
{
unsigned int     reserved_0:21;
unsigned int     p2_DmPulldown:1;
unsigned int     p2_DpPulldown:1;
unsigned int     p2_IDPULLUP:1;
unsigned int     reserved_1:5;
unsigned int     p2_DmPulldown_sel:1;
unsigned int     p2_DpPulldown_sel:1;
unsigned int     p2_IDPULLUP_sel:1;
}USB2_PHY2;

typedef struct 
{
unsigned int     reserved_0:21;
unsigned int     p3_DmPulldown:1;
unsigned int     p3_DpPulldown:1;
unsigned int     p3_IDPULLUP:1;
unsigned int     reserved_1:5;
unsigned int     p3_DmPulldown_sel:1;
unsigned int     p3_DpPulldown_sel:1;
unsigned int     p3_IDPULLUP_sel:1;
}USB2_PHY3;

typedef struct 
{
unsigned int     reserved_0:15;
unsigned int     done_st:1;
unsigned int     reserved_1:15;
unsigned int     go_ct:1;
}RAM_CTR;

typedef struct 
{
unsigned int     sram_addr:32;
}RAM_ADDR;

typedef struct 
{
unsigned int     ram_wdata:32;
}RAM_WDATA;

typedef struct 
{
unsigned int     ram_rdata:32;
}RAM_RDATA;

typedef struct 
{
unsigned int     reserved_0:13;
unsigned int     p0_count_num:19;
}PHY0_ST;

typedef struct 
{
unsigned int     reserved_0:22;
unsigned int     phy3_lperiod:3;
unsigned int     phy3_hperiod:3;
unsigned int     phy3_last:2;
unsigned int     host_ovr_current_value:1;
unsigned int     host_ovr_current_sel:1;
}USB3_OVR_CT;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     usb3_mbias_en_p0:1;
unsigned int     usb3_bg_en_p0:1;
unsigned int     usb3_pow_gating_p0:1;
unsigned int     usb3_isolate_p0:1;
}ANA_PHY0;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     usb2_pow_gating_p3:1;
unsigned int     usb2_pow_gating_p2:1;
unsigned int     usb2_pow_gating_p1:1;
unsigned int     usb2_pow_gating_p0:1;
}ANA_PHY1;

typedef struct 
{
unsigned int     usb_mac_ctrl:32;
}GBL_USB_CT;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     usb_bist_mode_host_ram_1:1;
unsigned int     usb_bist_mode_host_ram_2:1;
unsigned int     usb_bist_mode_wrap:1;
}BIST0;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     usb_bist_done_host_ram_1:1;
unsigned int     usb_bist_done_host_ram_2:1;
unsigned int     usb_bist_done_wrap:1;
}BIST1;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     usb_bist_fail_group_host_ram_1:1;
unsigned int     usb_bist_fail_group_host_ram_2:1;
unsigned int     usb_bist_fail_group_wrap:1;
}BIST2;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     usb_bist_host_ram_1_fail_3:1;
unsigned int     usb_bist_host_ram_1_fail_2:1;
unsigned int     usb_bist_host_ram_1_fail_1:1;
unsigned int     usb_bist_host_ram_1_fail_0:1;
}BIST3;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     usb_bist_host_ram_2_fail_3:1;
unsigned int     usb_bist_host_ram_2_fail_2:1;
unsigned int     usb_bist_host_ram_2_fail_1:1;
unsigned int     usb_bist_host_ram_2_fail_0:1;
}BIST4;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     usb_bist_wrap_fail_1:1;
unsigned int     usb_bist_wrap_fail_0:1;
}BIST5;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     usb_drf_mode_host_ram_1:1;
unsigned int     usb_drf_mode_host_ram_2:1;
unsigned int     usb_drf_mode_wrap:1;
}DRF0;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     usb_drf_resume_host_ram_1:1;
unsigned int     usb_drf_resume_host_ram_2:1;
unsigned int     usb_drf_resume_wrap:1;
}DRF1;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     usb_drf_done_host_ram_1:1;
unsigned int     usb_drf_done_host_ram_2:1;
unsigned int     usb_drf_done_wrap:1;
}DRF2;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     usb_drf_pause_host_ram_1:1;
unsigned int     usb_drf_pause_host_ram_2:1;
unsigned int     usb_drf_pause_wrap:1;
}DRF3;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     usb_drf_fail_group_host_ram_1:1;
unsigned int     usb_drf_fail_group_host_ram_2:1;
unsigned int     usb_drf_fail_group_wrap:1;
}DRF4;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     usb_drf_host_ram_1_fail_3:1;
unsigned int     usb_drf_host_ram_1_fail_2:1;
unsigned int     usb_drf_host_ram_1_fail_1:1;
unsigned int     usb_drf_host_ram_1_fail_0:1;
}DRF5;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     usb_drf_host_ram_2_fail_3:1;
unsigned int     usb_drf_host_ram_2_fail_2:1;
unsigned int     usb_drf_host_ram_2_fail_1:1;
unsigned int     usb_drf_host_ram_2_fail_0:1;
}DRF6;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     usb_drf_wrap_fail_1:1;
unsigned int     usb_drf_wrap_fail_0:1;
}DRF7;

typedef struct 
{
unsigned int     reserved_0:20;
unsigned int     usb_bist_wrap_ls1:1;
unsigned int     usb_bist_wrap_rme1:1;
unsigned int     usb_bist_wrap_rm1:4;
unsigned int     usb_bist_wrap_ls0:1;
unsigned int     usb_bist_wrap_rme0:1;
unsigned int     usb_bist_wrap_rm0:4;
}BIST_OP0;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     usb_usb_host_ram_1_ls3:1;
unsigned int     usb_usb_host_ram_1_rme3:1;
unsigned int     usb_usb_host_ram_1_rm3:4;
unsigned int     usb_usb_host_ram_1_ls2:1;
unsigned int     usb_usb_host_ram_1_rme2:1;
unsigned int     usb_usb_host_ram_1_rm2:4;
unsigned int     usb_usb_host_ram_1_ls1:1;
unsigned int     usb_usb_host_ram_1_rme1:1;
unsigned int     usb_usb_host_ram_1_rm1:4;
unsigned int     usb_usb_host_ram_1_ls0:1;
unsigned int     usb_usb_host_ram_1_rme0:1;
unsigned int     usb_usb_host_ram_1_rm0:4;
}BIST_OP1;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     usb_usb_host_ram_2_ls3:1;
unsigned int     usb_usb_host_ram_2_rme3:1;
unsigned int     usb_usb_host_ram_2_rm3:4;
unsigned int     usb_usb_host_ram_2_ls2:1;
unsigned int     usb_usb_host_ram_2_rme2:1;
unsigned int     usb_usb_host_ram_2_rm2:4;
unsigned int     usb_usb_host_ram_2_ls1:1;
unsigned int     usb_usb_host_ram_2_rme1:1;
unsigned int     usb_usb_host_ram_2_rm1:4;
unsigned int     usb_usb_host_ram_2_ls0:1;
unsigned int     usb_usb_host_ram_2_rme0:1;
unsigned int     usb_usb_host_ram_2_rm0:4;
}BIST_OP2;

#endif

#define WRAP_CTR                                                                     0x18013000
#define WRAP_CTR_reg_addr                                                            "0xB8013000"
#define WRAP_CTR_reg                                                                 0xB8013000
#define set_WRAP_CTR_reg(data)   (*((volatile unsigned int*) WRAP_CTR_reg)=data)
#define get_WRAP_CTR_reg   (*((volatile unsigned int*) WRAP_CTR_reg))
#define WRAP_CTR_inst_adr                                                            "0x0000"
#define WRAP_CTR_inst                                                                0x0000
#define WRAP_CTR_sram_debug_sel_shift                                                (3)
#define WRAP_CTR_sram_debug_sel_mask                                                 (0x00000008)
#define WRAP_CTR_sram_debug_sel(data)                                                (0x00000008&((data)<<3))
#define WRAP_CTR_sram_debug_sel_src(data)                                            ((0x00000008&(data))>>3)
#define WRAP_CTR_get_sram_debug_sel(data)                                            ((0x00000008&(data))>>3)
#define WRAP_CTR_sram_debug_mode_shift                                               (2)
#define WRAP_CTR_sram_debug_mode_mask                                                (0x00000004)
#define WRAP_CTR_sram_debug_mode(data)                                               (0x00000004&((data)<<2))
#define WRAP_CTR_sram_debug_mode_src(data)                                           ((0x00000004&(data))>>2)
#define WRAP_CTR_get_sram_debug_mode(data)                                           ((0x00000004&(data))>>2)
#define WRAP_CTR_dbus_multi_req_disable_shift                                        (1)
#define WRAP_CTR_dbus_multi_req_disable_mask                                         (0x00000002)
#define WRAP_CTR_dbus_multi_req_disable(data)                                        (0x00000002&((data)<<1))
#define WRAP_CTR_dbus_multi_req_disable_src(data)                                    ((0x00000002&(data))>>1)
#define WRAP_CTR_get_dbus_multi_req_disable(data)                                    ((0x00000002&(data))>>1)
#define WRAP_CTR_dev_mode_shift                                                      (0)
#define WRAP_CTR_dev_mode_mask                                                       (0x00000001)
#define WRAP_CTR_dev_mode(data)                                                      (0x00000001&((data)<<0))
#define WRAP_CTR_dev_mode_src(data)                                                  ((0x00000001&(data))>>0)
#define WRAP_CTR_get_dev_mode(data)                                                  ((0x00000001&(data))>>0)


#define GNR_INT                                                                      0x18013004
#define GNR_INT_reg_addr                                                             "0xB8013004"
#define GNR_INT_reg                                                                  0xB8013004
#define set_GNR_INT_reg(data)   (*((volatile unsigned int*) GNR_INT_reg)=data)
#define get_GNR_INT_reg   (*((volatile unsigned int*) GNR_INT_reg))
#define GNR_INT_inst_adr                                                             "0x0001"
#define GNR_INT_inst                                                                 0x0001
#define GNR_INT_host_int_shift                                                       (0)
#define GNR_INT_host_int_mask                                                        (0x00000001)
#define GNR_INT_host_int(data)                                                       (0x00000001&((data)<<0))
#define GNR_INT_host_int_src(data)                                                   ((0x00000001&(data))>>0)
#define GNR_INT_get_host_int(data)                                                   ((0x00000001&(data))>>0)


#define USB2_PHY_UTMI                                                                0x18013008
#define USB2_PHY_UTMI_reg_addr                                                       "0xB8013008"
#define USB2_PHY_UTMI_reg                                                            0xB8013008
#define set_USB2_PHY_UTMI_reg(data)   (*((volatile unsigned int*) USB2_PHY_UTMI_reg)=data)
#define get_USB2_PHY_UTMI_reg   (*((volatile unsigned int*) USB2_PHY_UTMI_reg))
#define USB2_PHY_UTMI_inst_adr                                                       "0x0002"
#define USB2_PHY_UTMI_inst                                                           0x0002
#define USB2_PHY_UTMI_reset_utmi_p3_shift                                            (3)
#define USB2_PHY_UTMI_reset_utmi_p3_mask                                             (0x00000008)
#define USB2_PHY_UTMI_reset_utmi_p3(data)                                            (0x00000008&((data)<<3))
#define USB2_PHY_UTMI_reset_utmi_p3_src(data)                                        ((0x00000008&(data))>>3)
#define USB2_PHY_UTMI_get_reset_utmi_p3(data)                                        ((0x00000008&(data))>>3)
#define USB2_PHY_UTMI_reset_utmi_p2_shift                                            (2)
#define USB2_PHY_UTMI_reset_utmi_p2_mask                                             (0x00000004)
#define USB2_PHY_UTMI_reset_utmi_p2(data)                                            (0x00000004&((data)<<2))
#define USB2_PHY_UTMI_reset_utmi_p2_src(data)                                        ((0x00000004&(data))>>2)
#define USB2_PHY_UTMI_get_reset_utmi_p2(data)                                        ((0x00000004&(data))>>2)
#define USB2_PHY_UTMI_reset_utmi_p1_shift                                            (1)
#define USB2_PHY_UTMI_reset_utmi_p1_mask                                             (0x00000002)
#define USB2_PHY_UTMI_reset_utmi_p1(data)                                            (0x00000002&((data)<<1))
#define USB2_PHY_UTMI_reset_utmi_p1_src(data)                                        ((0x00000002&(data))>>1)
#define USB2_PHY_UTMI_get_reset_utmi_p1(data)                                        ((0x00000002&(data))>>1)
#define USB2_PHY_UTMI_reset_utmi_p0_shift                                            (0)
#define USB2_PHY_UTMI_reset_utmi_p0_mask                                             (0x00000001)
#define USB2_PHY_UTMI_reset_utmi_p0(data)                                            (0x00000001&((data)<<0))
#define USB2_PHY_UTMI_reset_utmi_p0_src(data)                                        ((0x00000001&(data))>>0)
#define USB2_PHY_UTMI_get_reset_utmi_p0(data)                                        ((0x00000001&(data))>>0)


#define USB3_PHY_PIPE                                                                0x1801300c
#define USB3_PHY_PIPE_reg_addr                                                       "0xB801300C"
#define USB3_PHY_PIPE_reg                                                            0xB801300C
#define set_USB3_PHY_PIPE_reg(data)   (*((volatile unsigned int*) USB3_PHY_PIPE_reg)=data)
#define get_USB3_PHY_PIPE_reg   (*((volatile unsigned int*) USB3_PHY_PIPE_reg))
#define USB3_PHY_PIPE_inst_adr                                                       "0x0003"
#define USB3_PHY_PIPE_inst                                                           0x0003
#define USB3_PHY_PIPE_reset_pipe3_p0_shift                                           (0)
#define USB3_PHY_PIPE_reset_pipe3_p0_mask                                            (0x00000001)
#define USB3_PHY_PIPE_reset_pipe3_p0(data)                                           (0x00000001&((data)<<0))
#define USB3_PHY_PIPE_reset_pipe3_p0_src(data)                                       ((0x00000001&(data))>>0)
#define USB3_PHY_PIPE_get_reset_pipe3_p0(data)                                       ((0x00000001&(data))>>0)


#define MDIO_CTR                                                                     0x18013010
#define MDIO_CTR_reg_addr                                                            "0xB8013010"
#define MDIO_CTR_reg                                                                 0xB8013010
#define set_MDIO_CTR_reg(data)   (*((volatile unsigned int*) MDIO_CTR_reg)=data)
#define get_MDIO_CTR_reg   (*((volatile unsigned int*) MDIO_CTR_reg))
#define MDIO_CTR_inst_adr                                                            "0x0004"
#define MDIO_CTR_inst                                                                0x0004
#define MDIO_CTR_data_shift                                                          (16)
#define MDIO_CTR_data_mask                                                           (0xFFFF0000)
#define MDIO_CTR_data(data)                                                          (0xFFFF0000&((data)<<16))
#define MDIO_CTR_data_src(data)                                                      ((0xFFFF0000&(data))>>16)
#define MDIO_CTR_get_data(data)                                                      ((0xFFFF0000&(data))>>16)
#define MDIO_CTR_phy_addr_shift                                                      (13)
#define MDIO_CTR_phy_addr_mask                                                       (0x0000E000)
#define MDIO_CTR_phy_addr(data)                                                      (0x0000E000&((data)<<13))
#define MDIO_CTR_phy_addr_src(data)                                                  ((0x0000E000&(data))>>13)
#define MDIO_CTR_get_phy_addr(data)                                                  ((0x0000E000&(data))>>13)
#define MDIO_CTR_phy_reg_addr_shift                                                  (8)
#define MDIO_CTR_phy_reg_addr_mask                                                   (0x00001F00)
#define MDIO_CTR_phy_reg_addr(data)                                                  (0x00001F00&((data)<<8))
#define MDIO_CTR_phy_reg_addr_src(data)                                              ((0x00001F00&(data))>>8)
#define MDIO_CTR_get_phy_reg_addr(data)                                              ((0x00001F00&(data))>>8)
#define MDIO_CTR_mdio_busy_shift                                                     (7)
#define MDIO_CTR_mdio_busy_mask                                                      (0x00000080)
#define MDIO_CTR_mdio_busy(data)                                                     (0x00000080&((data)<<7))
#define MDIO_CTR_mdio_busy_src(data)                                                 ((0x00000080&(data))>>7)
#define MDIO_CTR_get_mdio_busy(data)                                                 ((0x00000080&(data))>>7)
#define MDIO_CTR_mdio_st_shift                                                       (5)
#define MDIO_CTR_mdio_st_mask                                                        (0x00000060)
#define MDIO_CTR_mdio_st(data)                                                       (0x00000060&((data)<<5))
#define MDIO_CTR_mdio_st_src(data)                                                   ((0x00000060&(data))>>5)
#define MDIO_CTR_get_mdio_st(data)                                                   ((0x00000060&(data))>>5)
#define MDIO_CTR_mdio_rdy_shift                                                      (4)
#define MDIO_CTR_mdio_rdy_mask                                                       (0x00000010)
#define MDIO_CTR_mdio_rdy(data)                                                      (0x00000010&((data)<<4))
#define MDIO_CTR_mdio_rdy_src(data)                                                  ((0x00000010&(data))>>4)
#define MDIO_CTR_get_mdio_rdy(data)                                                  ((0x00000010&(data))>>4)
#define MDIO_CTR_mclk_rate_shift                                                     (2)
#define MDIO_CTR_mclk_rate_mask                                                      (0x0000000C)
#define MDIO_CTR_mclk_rate(data)                                                     (0x0000000C&((data)<<2))
#define MDIO_CTR_mclk_rate_src(data)                                                 ((0x0000000C&(data))>>2)
#define MDIO_CTR_get_mclk_rate(data)                                                 ((0x0000000C&(data))>>2)
#define MDIO_CTR_mdio_srst_shift                                                     (1)
#define MDIO_CTR_mdio_srst_mask                                                      (0x00000002)
#define MDIO_CTR_mdio_srst(data)                                                     (0x00000002&((data)<<1))
#define MDIO_CTR_mdio_srst_src(data)                                                 ((0x00000002&(data))>>1)
#define MDIO_CTR_get_mdio_srst(data)                                                 ((0x00000002&(data))>>1)
#define MDIO_CTR_mdio_rdwr_shift                                                     (0)
#define MDIO_CTR_mdio_rdwr_mask                                                      (0x00000001)
#define MDIO_CTR_mdio_rdwr(data)                                                     (0x00000001&((data)<<0))
#define MDIO_CTR_mdio_rdwr_src(data)                                                 ((0x00000001&(data))>>0)
#define MDIO_CTR_get_mdio_rdwr(data)                                                 ((0x00000001&(data))>>0)


#define VSTATUS0_OUT                                                                 0x18013014
#define VSTATUS0_OUT_reg_addr                                                        "0xB8013014"
#define VSTATUS0_OUT_reg                                                             0xB8013014
#define set_VSTATUS0_OUT_reg(data)   (*((volatile unsigned int*) VSTATUS0_OUT_reg)=data)
#define get_VSTATUS0_OUT_reg   (*((volatile unsigned int*) VSTATUS0_OUT_reg))
#define VSTATUS0_OUT_inst_adr                                                        "0x0005"
#define VSTATUS0_OUT_inst                                                            0x0005
#define VSTATUS0_OUT_p3_vstatus_out_shift                                            (24)
#define VSTATUS0_OUT_p3_vstatus_out_mask                                             (0xFF000000)
#define VSTATUS0_OUT_p3_vstatus_out(data)                                            (0xFF000000&((data)<<24))
#define VSTATUS0_OUT_p3_vstatus_out_src(data)                                        ((0xFF000000&(data))>>24)
#define VSTATUS0_OUT_get_p3_vstatus_out(data)                                        ((0xFF000000&(data))>>24)
#define VSTATUS0_OUT_p2_vstatus_out_shift                                            (16)
#define VSTATUS0_OUT_p2_vstatus_out_mask                                             (0x00FF0000)
#define VSTATUS0_OUT_p2_vstatus_out(data)                                            (0x00FF0000&((data)<<16))
#define VSTATUS0_OUT_p2_vstatus_out_src(data)                                        ((0x00FF0000&(data))>>16)
#define VSTATUS0_OUT_get_p2_vstatus_out(data)                                        ((0x00FF0000&(data))>>16)
#define VSTATUS0_OUT_p1_vstatus_out_shift                                            (8)
#define VSTATUS0_OUT_p1_vstatus_out_mask                                             (0x0000FF00)
#define VSTATUS0_OUT_p1_vstatus_out(data)                                            (0x0000FF00&((data)<<8))
#define VSTATUS0_OUT_p1_vstatus_out_src(data)                                        ((0x0000FF00&(data))>>8)
#define VSTATUS0_OUT_get_p1_vstatus_out(data)                                        ((0x0000FF00&(data))>>8)
#define VSTATUS0_OUT_p0_vstatus_out_shift                                            (0)
#define VSTATUS0_OUT_p0_vstatus_out_mask                                             (0x000000FF)
#define VSTATUS0_OUT_p0_vstatus_out(data)                                            (0x000000FF&((data)<<0))
#define VSTATUS0_OUT_p0_vstatus_out_src(data)                                        ((0x000000FF&(data))>>0)
#define VSTATUS0_OUT_get_p0_vstatus_out(data)                                        ((0x000000FF&(data))>>0)


#define SLP_BACK0_EN                                                                 0x18013018
#define SLP_BACK0_EN_reg_addr                                                        "0xB8013018"
#define SLP_BACK0_EN_reg                                                             0xB8013018
#define set_SLP_BACK0_EN_reg(data)   (*((volatile unsigned int*) SLP_BACK0_EN_reg)=data)
#define get_SLP_BACK0_EN_reg   (*((volatile unsigned int*) SLP_BACK0_EN_reg))
#define SLP_BACK0_EN_inst_adr                                                        "0x0006"
#define SLP_BACK0_EN_inst                                                            0x0006
#define SLP_BACK0_EN_simulation_mode_p3_shift                                        (15)
#define SLP_BACK0_EN_simulation_mode_p3_mask                                         (0x00008000)
#define SLP_BACK0_EN_simulation_mode_p3(data)                                        (0x00008000&((data)<<15))
#define SLP_BACK0_EN_simulation_mode_p3_src(data)                                    ((0x00008000&(data))>>15)
#define SLP_BACK0_EN_get_simulation_mode_p3(data)                                    ((0x00008000&(data))>>15)
#define SLP_BACK0_EN_force_hs_mode_p3_shift                                          (14)
#define SLP_BACK0_EN_force_hs_mode_p3_mask                                           (0x00004000)
#define SLP_BACK0_EN_force_hs_mode_p3(data)                                          (0x00004000&((data)<<14))
#define SLP_BACK0_EN_force_hs_mode_p3_src(data)                                      ((0x00004000&(data))>>14)
#define SLP_BACK0_EN_get_force_hs_mode_p3(data)                                      ((0x00004000&(data))>>14)
#define SLP_BACK0_EN_test_rst_p3_shift                                               (13)
#define SLP_BACK0_EN_test_rst_p3_mask                                                (0x00002000)
#define SLP_BACK0_EN_test_rst_p3(data)                                               (0x00002000&((data)<<13))
#define SLP_BACK0_EN_test_rst_p3_src(data)                                           ((0x00002000&(data))>>13)
#define SLP_BACK0_EN_get_test_rst_p3(data)                                           ((0x00002000&(data))>>13)
#define SLP_BACK0_EN_test_en_p3_shift                                                (12)
#define SLP_BACK0_EN_test_en_p3_mask                                                 (0x00001000)
#define SLP_BACK0_EN_test_en_p3(data)                                                (0x00001000&((data)<<12))
#define SLP_BACK0_EN_test_en_p3_src(data)                                            ((0x00001000&(data))>>12)
#define SLP_BACK0_EN_get_test_en_p3(data)                                            ((0x00001000&(data))>>12)
#define SLP_BACK0_EN_simulation_mode_p2_shift                                        (11)
#define SLP_BACK0_EN_simulation_mode_p2_mask                                         (0x00000800)
#define SLP_BACK0_EN_simulation_mode_p2(data)                                        (0x00000800&((data)<<11))
#define SLP_BACK0_EN_simulation_mode_p2_src(data)                                    ((0x00000800&(data))>>11)
#define SLP_BACK0_EN_get_simulation_mode_p2(data)                                    ((0x00000800&(data))>>11)
#define SLP_BACK0_EN_force_hs_mode_p2_shift                                          (10)
#define SLP_BACK0_EN_force_hs_mode_p2_mask                                           (0x00000400)
#define SLP_BACK0_EN_force_hs_mode_p2(data)                                          (0x00000400&((data)<<10))
#define SLP_BACK0_EN_force_hs_mode_p2_src(data)                                      ((0x00000400&(data))>>10)
#define SLP_BACK0_EN_get_force_hs_mode_p2(data)                                      ((0x00000400&(data))>>10)
#define SLP_BACK0_EN_test_rst_p2_shift                                               (9)
#define SLP_BACK0_EN_test_rst_p2_mask                                                (0x00000200)
#define SLP_BACK0_EN_test_rst_p2(data)                                               (0x00000200&((data)<<9))
#define SLP_BACK0_EN_test_rst_p2_src(data)                                           ((0x00000200&(data))>>9)
#define SLP_BACK0_EN_get_test_rst_p2(data)                                           ((0x00000200&(data))>>9)
#define SLP_BACK0_EN_test_en_p2_shift                                                (8)
#define SLP_BACK0_EN_test_en_p2_mask                                                 (0x00000100)
#define SLP_BACK0_EN_test_en_p2(data)                                                (0x00000100&((data)<<8))
#define SLP_BACK0_EN_test_en_p2_src(data)                                            ((0x00000100&(data))>>8)
#define SLP_BACK0_EN_get_test_en_p2(data)                                            ((0x00000100&(data))>>8)
#define SLP_BACK0_EN_simulation_mode_p1_shift                                        (7)
#define SLP_BACK0_EN_simulation_mode_p1_mask                                         (0x00000080)
#define SLP_BACK0_EN_simulation_mode_p1(data)                                        (0x00000080&((data)<<7))
#define SLP_BACK0_EN_simulation_mode_p1_src(data)                                    ((0x00000080&(data))>>7)
#define SLP_BACK0_EN_get_simulation_mode_p1(data)                                    ((0x00000080&(data))>>7)
#define SLP_BACK0_EN_force_hs_mode_p1_shift                                          (6)
#define SLP_BACK0_EN_force_hs_mode_p1_mask                                           (0x00000040)
#define SLP_BACK0_EN_force_hs_mode_p1(data)                                          (0x00000040&((data)<<6))
#define SLP_BACK0_EN_force_hs_mode_p1_src(data)                                      ((0x00000040&(data))>>6)
#define SLP_BACK0_EN_get_force_hs_mode_p1(data)                                      ((0x00000040&(data))>>6)
#define SLP_BACK0_EN_test_rst_p1_shift                                               (5)
#define SLP_BACK0_EN_test_rst_p1_mask                                                (0x00000020)
#define SLP_BACK0_EN_test_rst_p1(data)                                               (0x00000020&((data)<<5))
#define SLP_BACK0_EN_test_rst_p1_src(data)                                           ((0x00000020&(data))>>5)
#define SLP_BACK0_EN_get_test_rst_p1(data)                                           ((0x00000020&(data))>>5)
#define SLP_BACK0_EN_test_en_p1_shift                                                (4)
#define SLP_BACK0_EN_test_en_p1_mask                                                 (0x00000010)
#define SLP_BACK0_EN_test_en_p1(data)                                                (0x00000010&((data)<<4))
#define SLP_BACK0_EN_test_en_p1_src(data)                                            ((0x00000010&(data))>>4)
#define SLP_BACK0_EN_get_test_en_p1(data)                                            ((0x00000010&(data))>>4)
#define SLP_BACK0_EN_simulation_mode_p0_shift                                        (3)
#define SLP_BACK0_EN_simulation_mode_p0_mask                                         (0x00000008)
#define SLP_BACK0_EN_simulation_mode_p0(data)                                        (0x00000008&((data)<<3))
#define SLP_BACK0_EN_simulation_mode_p0_src(data)                                    ((0x00000008&(data))>>3)
#define SLP_BACK0_EN_get_simulation_mode_p0(data)                                    ((0x00000008&(data))>>3)
#define SLP_BACK0_EN_force_hs_mode_p0_shift                                          (2)
#define SLP_BACK0_EN_force_hs_mode_p0_mask                                           (0x00000004)
#define SLP_BACK0_EN_force_hs_mode_p0(data)                                          (0x00000004&((data)<<2))
#define SLP_BACK0_EN_force_hs_mode_p0_src(data)                                      ((0x00000004&(data))>>2)
#define SLP_BACK0_EN_get_force_hs_mode_p0(data)                                      ((0x00000004&(data))>>2)
#define SLP_BACK0_EN_test_rst_p0_shift                                               (1)
#define SLP_BACK0_EN_test_rst_p0_mask                                                (0x00000002)
#define SLP_BACK0_EN_test_rst_p0(data)                                               (0x00000002&((data)<<1))
#define SLP_BACK0_EN_test_rst_p0_src(data)                                           ((0x00000002&(data))>>1)
#define SLP_BACK0_EN_get_test_rst_p0(data)                                           ((0x00000002&(data))>>1)
#define SLP_BACK0_EN_test_en_p0_shift                                                (0)
#define SLP_BACK0_EN_test_en_p0_mask                                                 (0x00000001)
#define SLP_BACK0_EN_test_en_p0(data)                                                (0x00000001&((data)<<0))
#define SLP_BACK0_EN_test_en_p0_src(data)                                            ((0x00000001&(data))>>0)
#define SLP_BACK0_EN_get_test_en_p0(data)                                            ((0x00000001&(data))>>0)


#define SLP_BACK0_CTR                                                                0x1801301c
#define SLP_BACK0_CTR_reg_addr                                                       "0xB801301C"
#define SLP_BACK0_CTR_reg                                                            0xB801301C
#define set_SLP_BACK0_CTR_reg(data)   (*((volatile unsigned int*) SLP_BACK0_CTR_reg)=data)
#define get_SLP_BACK0_CTR_reg   (*((volatile unsigned int*) SLP_BACK0_CTR_reg))
#define SLP_BACK0_CTR_inst_adr                                                       "0x0007"
#define SLP_BACK0_CTR_inst                                                           0x0007
#define SLP_BACK0_CTR_test_speed_p0_shift                                            (10)
#define SLP_BACK0_CTR_test_speed_p0_mask                                             (0x00000C00)
#define SLP_BACK0_CTR_test_speed_p0(data)                                            (0x00000C00&((data)<<10))
#define SLP_BACK0_CTR_test_speed_p0_src(data)                                        ((0x00000C00&(data))>>10)
#define SLP_BACK0_CTR_get_test_speed_p0(data)                                        ((0x00000C00&(data))>>10)
#define SLP_BACK0_CTR_test_seed_p0_shift                                             (2)
#define SLP_BACK0_CTR_test_seed_p0_mask                                              (0x000003FC)
#define SLP_BACK0_CTR_test_seed_p0(data)                                             (0x000003FC&((data)<<2))
#define SLP_BACK0_CTR_test_seed_p0_src(data)                                         ((0x000003FC&(data))>>2)
#define SLP_BACK0_CTR_get_test_seed_p0(data)                                         ((0x000003FC&(data))>>2)
#define SLP_BACK0_CTR_test_psl_p0_shift                                              (0)
#define SLP_BACK0_CTR_test_psl_p0_mask                                               (0x00000003)
#define SLP_BACK0_CTR_test_psl_p0(data)                                              (0x00000003&((data)<<0))
#define SLP_BACK0_CTR_test_psl_p0_src(data)                                          ((0x00000003&(data))>>0)
#define SLP_BACK0_CTR_get_test_psl_p0(data)                                          ((0x00000003&(data))>>0)


#define SLP_BACK0_ST                                                                 0x18013020
#define SLP_BACK0_ST_reg_addr                                                        "0xB8013020"
#define SLP_BACK0_ST_reg                                                             0xB8013020
#define set_SLP_BACK0_ST_reg(data)   (*((volatile unsigned int*) SLP_BACK0_ST_reg)=data)
#define get_SLP_BACK0_ST_reg   (*((volatile unsigned int*) SLP_BACK0_ST_reg))
#define SLP_BACK0_ST_inst_adr                                                        "0x0008"
#define SLP_BACK0_ST_inst                                                            0x0008
#define SLP_BACK0_ST_test_fail_p0_shift                                              (1)
#define SLP_BACK0_ST_test_fail_p0_mask                                               (0x00000002)
#define SLP_BACK0_ST_test_fail_p0(data)                                              (0x00000002&((data)<<1))
#define SLP_BACK0_ST_test_fail_p0_src(data)                                          ((0x00000002&(data))>>1)
#define SLP_BACK0_ST_get_test_fail_p0(data)                                          ((0x00000002&(data))>>1)
#define SLP_BACK0_ST_test_done_p0_shift                                              (0)
#define SLP_BACK0_ST_test_done_p0_mask                                               (0x00000001)
#define SLP_BACK0_ST_test_done_p0(data)                                              (0x00000001&((data)<<0))
#define SLP_BACK0_ST_test_done_p0_src(data)                                          ((0x00000001&(data))>>0)
#define SLP_BACK0_ST_get_test_done_p0(data)                                          ((0x00000001&(data))>>0)


#define PHY2_SLB0_EN                                                                 0x18013024
#define PHY2_SLB0_EN_reg_addr                                                        "0xB8013024"
#define PHY2_SLB0_EN_reg                                                             0xB8013024
#define set_PHY2_SLB0_EN_reg(data)   (*((volatile unsigned int*) PHY2_SLB0_EN_reg)=data)
#define get_PHY2_SLB0_EN_reg   (*((volatile unsigned int*) PHY2_SLB0_EN_reg))
#define PHY2_SLB0_EN_inst_adr                                                        "0x0009"
#define PHY2_SLB0_EN_inst                                                            0x0009
#define PHY2_SLB0_EN_p0_usb2phy_slb_hs_shift                                         (1)
#define PHY2_SLB0_EN_p0_usb2phy_slb_hs_mask                                          (0x00000002)
#define PHY2_SLB0_EN_p0_usb2phy_slb_hs(data)                                         (0x00000002&((data)<<1))
#define PHY2_SLB0_EN_p0_usb2phy_slb_hs_src(data)                                     ((0x00000002&(data))>>1)
#define PHY2_SLB0_EN_get_p0_usb2phy_slb_hs(data)                                     ((0x00000002&(data))>>1)
#define PHY2_SLB0_EN_p0_usb2phy_force_slb_shift                                      (0)
#define PHY2_SLB0_EN_p0_usb2phy_force_slb_mask                                       (0x00000001)
#define PHY2_SLB0_EN_p0_usb2phy_force_slb(data)                                      (0x00000001&((data)<<0))
#define PHY2_SLB0_EN_p0_usb2phy_force_slb_src(data)                                  ((0x00000001&(data))>>0)
#define PHY2_SLB0_EN_get_p0_usb2phy_force_slb(data)                                  ((0x00000001&(data))>>0)


#define PHY2_SLB0_ST                                                                 0x18013028
#define PHY2_SLB0_ST_reg_addr                                                        "0xB8013028"
#define PHY2_SLB0_ST_reg                                                             0xB8013028
#define set_PHY2_SLB0_ST_reg(data)   (*((volatile unsigned int*) PHY2_SLB0_ST_reg)=data)
#define get_PHY2_SLB0_ST_reg   (*((volatile unsigned int*) PHY2_SLB0_ST_reg))
#define PHY2_SLB0_ST_inst_adr                                                        "0x000A"
#define PHY2_SLB0_ST_inst                                                            0x000A
#define PHY2_SLB0_ST_p0_usb2phy_slb_fail_shift                                       (1)
#define PHY2_SLB0_ST_p0_usb2phy_slb_fail_mask                                        (0x00000002)
#define PHY2_SLB0_ST_p0_usb2phy_slb_fail(data)                                       (0x00000002&((data)<<1))
#define PHY2_SLB0_ST_p0_usb2phy_slb_fail_src(data)                                   ((0x00000002&(data))>>1)
#define PHY2_SLB0_ST_get_p0_usb2phy_slb_fail(data)                                   ((0x00000002&(data))>>1)
#define PHY2_SLB0_ST_p0_usb2phy_slb_done_shift                                       (0)
#define PHY2_SLB0_ST_p0_usb2phy_slb_done_mask                                        (0x00000001)
#define PHY2_SLB0_ST_p0_usb2phy_slb_done(data)                                       (0x00000001&((data)<<0))
#define PHY2_SLB0_ST_p0_usb2phy_slb_done_src(data)                                   ((0x00000001&(data))>>0)
#define PHY2_SLB0_ST_get_p0_usb2phy_slb_done(data)                                   ((0x00000001&(data))>>0)


#define SLP_BACK1_CTR                                                                0x1801302c
#define SLP_BACK1_CTR_reg_addr                                                       "0xB801302C"
#define SLP_BACK1_CTR_reg                                                            0xB801302C
#define set_SLP_BACK1_CTR_reg(data)   (*((volatile unsigned int*) SLP_BACK1_CTR_reg)=data)
#define get_SLP_BACK1_CTR_reg   (*((volatile unsigned int*) SLP_BACK1_CTR_reg))
#define SLP_BACK1_CTR_inst_adr                                                       "0x000B"
#define SLP_BACK1_CTR_inst                                                           0x000B
#define SLP_BACK1_CTR_test_speed_p1_shift                                            (10)
#define SLP_BACK1_CTR_test_speed_p1_mask                                             (0x00000C00)
#define SLP_BACK1_CTR_test_speed_p1(data)                                            (0x00000C00&((data)<<10))
#define SLP_BACK1_CTR_test_speed_p1_src(data)                                        ((0x00000C00&(data))>>10)
#define SLP_BACK1_CTR_get_test_speed_p1(data)                                        ((0x00000C00&(data))>>10)
#define SLP_BACK1_CTR_test_seed_p1_shift                                             (2)
#define SLP_BACK1_CTR_test_seed_p1_mask                                              (0x000003FC)
#define SLP_BACK1_CTR_test_seed_p1(data)                                             (0x000003FC&((data)<<2))
#define SLP_BACK1_CTR_test_seed_p1_src(data)                                         ((0x000003FC&(data))>>2)
#define SLP_BACK1_CTR_get_test_seed_p1(data)                                         ((0x000003FC&(data))>>2)
#define SLP_BACK1_CTR_test_psl_p1_shift                                              (0)
#define SLP_BACK1_CTR_test_psl_p1_mask                                               (0x00000003)
#define SLP_BACK1_CTR_test_psl_p1(data)                                              (0x00000003&((data)<<0))
#define SLP_BACK1_CTR_test_psl_p1_src(data)                                          ((0x00000003&(data))>>0)
#define SLP_BACK1_CTR_get_test_psl_p1(data)                                          ((0x00000003&(data))>>0)


#define SLP_BACK1_ST                                                                 0x18013030
#define SLP_BACK1_ST_reg_addr                                                        "0xB8013030"
#define SLP_BACK1_ST_reg                                                             0xB8013030
#define set_SLP_BACK1_ST_reg(data)   (*((volatile unsigned int*) SLP_BACK1_ST_reg)=data)
#define get_SLP_BACK1_ST_reg   (*((volatile unsigned int*) SLP_BACK1_ST_reg))
#define SLP_BACK1_ST_inst_adr                                                        "0x000C"
#define SLP_BACK1_ST_inst                                                            0x000C
#define SLP_BACK1_ST_test_fail_p1_shift                                              (1)
#define SLP_BACK1_ST_test_fail_p1_mask                                               (0x00000002)
#define SLP_BACK1_ST_test_fail_p1(data)                                              (0x00000002&((data)<<1))
#define SLP_BACK1_ST_test_fail_p1_src(data)                                          ((0x00000002&(data))>>1)
#define SLP_BACK1_ST_get_test_fail_p1(data)                                          ((0x00000002&(data))>>1)
#define SLP_BACK1_ST_test_done_p1_shift                                              (0)
#define SLP_BACK1_ST_test_done_p1_mask                                               (0x00000001)
#define SLP_BACK1_ST_test_done_p1(data)                                              (0x00000001&((data)<<0))
#define SLP_BACK1_ST_test_done_p1_src(data)                                          ((0x00000001&(data))>>0)
#define SLP_BACK1_ST_get_test_done_p1(data)                                          ((0x00000001&(data))>>0)


#define PHY2_SLB1_EN                                                                 0x18013034
#define PHY2_SLB1_EN_reg_addr                                                        "0xB8013034"
#define PHY2_SLB1_EN_reg                                                             0xB8013034
#define set_PHY2_SLB1_EN_reg(data)   (*((volatile unsigned int*) PHY2_SLB1_EN_reg)=data)
#define get_PHY2_SLB1_EN_reg   (*((volatile unsigned int*) PHY2_SLB1_EN_reg))
#define PHY2_SLB1_EN_inst_adr                                                        "0x000D"
#define PHY2_SLB1_EN_inst                                                            0x000D
#define PHY2_SLB1_EN_p1_usb2phy_slb_hs_shift                                         (1)
#define PHY2_SLB1_EN_p1_usb2phy_slb_hs_mask                                          (0x00000002)
#define PHY2_SLB1_EN_p1_usb2phy_slb_hs(data)                                         (0x00000002&((data)<<1))
#define PHY2_SLB1_EN_p1_usb2phy_slb_hs_src(data)                                     ((0x00000002&(data))>>1)
#define PHY2_SLB1_EN_get_p1_usb2phy_slb_hs(data)                                     ((0x00000002&(data))>>1)
#define PHY2_SLB1_EN_p1_usb2phy_force_slb_shift                                      (0)
#define PHY2_SLB1_EN_p1_usb2phy_force_slb_mask                                       (0x00000001)
#define PHY2_SLB1_EN_p1_usb2phy_force_slb(data)                                      (0x00000001&((data)<<0))
#define PHY2_SLB1_EN_p1_usb2phy_force_slb_src(data)                                  ((0x00000001&(data))>>0)
#define PHY2_SLB1_EN_get_p1_usb2phy_force_slb(data)                                  ((0x00000001&(data))>>0)


#define PHY2_SLB1_ST                                                                 0x18013038
#define PHY2_SLB1_ST_reg_addr                                                        "0xB8013038"
#define PHY2_SLB1_ST_reg                                                             0xB8013038
#define set_PHY2_SLB1_ST_reg(data)   (*((volatile unsigned int*) PHY2_SLB1_ST_reg)=data)
#define get_PHY2_SLB1_ST_reg   (*((volatile unsigned int*) PHY2_SLB1_ST_reg))
#define PHY2_SLB1_ST_inst_adr                                                        "0x000E"
#define PHY2_SLB1_ST_inst                                                            0x000E
#define PHY2_SLB1_ST_p1_usb2phy_slb_fail_shift                                       (1)
#define PHY2_SLB1_ST_p1_usb2phy_slb_fail_mask                                        (0x00000002)
#define PHY2_SLB1_ST_p1_usb2phy_slb_fail(data)                                       (0x00000002&((data)<<1))
#define PHY2_SLB1_ST_p1_usb2phy_slb_fail_src(data)                                   ((0x00000002&(data))>>1)
#define PHY2_SLB1_ST_get_p1_usb2phy_slb_fail(data)                                   ((0x00000002&(data))>>1)
#define PHY2_SLB1_ST_p1_usb2phy_slb_done_shift                                       (0)
#define PHY2_SLB1_ST_p1_usb2phy_slb_done_mask                                        (0x00000001)
#define PHY2_SLB1_ST_p1_usb2phy_slb_done(data)                                       (0x00000001&((data)<<0))
#define PHY2_SLB1_ST_p1_usb2phy_slb_done_src(data)                                   ((0x00000001&(data))>>0)
#define PHY2_SLB1_ST_get_p1_usb2phy_slb_done(data)                                   ((0x00000001&(data))>>0)


#define SLP_BACK2_CTR                                                                0x1801303C
#define SLP_BACK2_CTR_reg_addr                                                       "0xB801303C"
#define SLP_BACK2_CTR_reg                                                            0xB801303C
#define set_SLP_BACK2_CTR_reg(data)   (*((volatile unsigned int*) SLP_BACK2_CTR_reg)=data)
#define get_SLP_BACK2_CTR_reg   (*((volatile unsigned int*) SLP_BACK2_CTR_reg))
#define SLP_BACK2_CTR_inst_adr                                                       "0x000F"
#define SLP_BACK2_CTR_inst                                                           0x000F
#define SLP_BACK2_CTR_test_speed_p2_shift                                            (10)
#define SLP_BACK2_CTR_test_speed_p2_mask                                             (0x00000C00)
#define SLP_BACK2_CTR_test_speed_p2(data)                                            (0x00000C00&((data)<<10))
#define SLP_BACK2_CTR_test_speed_p2_src(data)                                        ((0x00000C00&(data))>>10)
#define SLP_BACK2_CTR_get_test_speed_p2(data)                                        ((0x00000C00&(data))>>10)
#define SLP_BACK2_CTR_test_seed_p2_shift                                             (2)
#define SLP_BACK2_CTR_test_seed_p2_mask                                              (0x000003FC)
#define SLP_BACK2_CTR_test_seed_p2(data)                                             (0x000003FC&((data)<<2))
#define SLP_BACK2_CTR_test_seed_p2_src(data)                                         ((0x000003FC&(data))>>2)
#define SLP_BACK2_CTR_get_test_seed_p2(data)                                         ((0x000003FC&(data))>>2)
#define SLP_BACK2_CTR_test_psl_p2_shift                                              (0)
#define SLP_BACK2_CTR_test_psl_p2_mask                                               (0x00000003)
#define SLP_BACK2_CTR_test_psl_p2(data)                                              (0x00000003&((data)<<0))
#define SLP_BACK2_CTR_test_psl_p2_src(data)                                          ((0x00000003&(data))>>0)
#define SLP_BACK2_CTR_get_test_psl_p2(data)                                          ((0x00000003&(data))>>0)


#define SLP_BACK2_ST                                                                 0x18013040
#define SLP_BACK2_ST_reg_addr                                                        "0xB8013040"
#define SLP_BACK2_ST_reg                                                             0xB8013040
#define set_SLP_BACK2_ST_reg(data)   (*((volatile unsigned int*) SLP_BACK2_ST_reg)=data)
#define get_SLP_BACK2_ST_reg   (*((volatile unsigned int*) SLP_BACK2_ST_reg))
#define SLP_BACK2_ST_inst_adr                                                        "0x0010"
#define SLP_BACK2_ST_inst                                                            0x0010
#define SLP_BACK2_ST_test_fail_p2_shift                                              (1)
#define SLP_BACK2_ST_test_fail_p2_mask                                               (0x00000002)
#define SLP_BACK2_ST_test_fail_p2(data)                                              (0x00000002&((data)<<1))
#define SLP_BACK2_ST_test_fail_p2_src(data)                                          ((0x00000002&(data))>>1)
#define SLP_BACK2_ST_get_test_fail_p2(data)                                          ((0x00000002&(data))>>1)
#define SLP_BACK2_ST_test_done_p2_shift                                              (0)
#define SLP_BACK2_ST_test_done_p2_mask                                               (0x00000001)
#define SLP_BACK2_ST_test_done_p2(data)                                              (0x00000001&((data)<<0))
#define SLP_BACK2_ST_test_done_p2_src(data)                                          ((0x00000001&(data))>>0)
#define SLP_BACK2_ST_get_test_done_p2(data)                                          ((0x00000001&(data))>>0)


#define PHY2_SLB2_EN                                                                 0x18013044
#define PHY2_SLB2_EN_reg_addr                                                        "0xB8013044"
#define PHY2_SLB2_EN_reg                                                             0xB8013044
#define set_PHY2_SLB2_EN_reg(data)   (*((volatile unsigned int*) PHY2_SLB2_EN_reg)=data)
#define get_PHY2_SLB2_EN_reg   (*((volatile unsigned int*) PHY2_SLB2_EN_reg))
#define PHY2_SLB2_EN_inst_adr                                                        "0x0011"
#define PHY2_SLB2_EN_inst                                                            0x0011
#define PHY2_SLB2_EN_p2_usb2phy_slb_hs_shift                                         (1)
#define PHY2_SLB2_EN_p2_usb2phy_slb_hs_mask                                          (0x00000002)
#define PHY2_SLB2_EN_p2_usb2phy_slb_hs(data)                                         (0x00000002&((data)<<1))
#define PHY2_SLB2_EN_p2_usb2phy_slb_hs_src(data)                                     ((0x00000002&(data))>>1)
#define PHY2_SLB2_EN_get_p2_usb2phy_slb_hs(data)                                     ((0x00000002&(data))>>1)
#define PHY2_SLB2_EN_p2_usb2phy_force_slb_shift                                      (0)
#define PHY2_SLB2_EN_p2_usb2phy_force_slb_mask                                       (0x00000001)
#define PHY2_SLB2_EN_p2_usb2phy_force_slb(data)                                      (0x00000001&((data)<<0))
#define PHY2_SLB2_EN_p2_usb2phy_force_slb_src(data)                                  ((0x00000001&(data))>>0)
#define PHY2_SLB2_EN_get_p2_usb2phy_force_slb(data)                                  ((0x00000001&(data))>>0)


#define PHY2_SLB2_ST                                                                 0x18013048
#define PHY2_SLB2_ST_reg_addr                                                        "0xB8013048"
#define PHY2_SLB2_ST_reg                                                             0xB8013048
#define set_PHY2_SLB2_ST_reg(data)   (*((volatile unsigned int*) PHY2_SLB2_ST_reg)=data)
#define get_PHY2_SLB2_ST_reg   (*((volatile unsigned int*) PHY2_SLB2_ST_reg))
#define PHY2_SLB2_ST_inst_adr                                                        "0x0012"
#define PHY2_SLB2_ST_inst                                                            0x0012
#define PHY2_SLB2_ST_p2_usb2phy_slb_fail_shift                                       (1)
#define PHY2_SLB2_ST_p2_usb2phy_slb_fail_mask                                        (0x00000002)
#define PHY2_SLB2_ST_p2_usb2phy_slb_fail(data)                                       (0x00000002&((data)<<1))
#define PHY2_SLB2_ST_p2_usb2phy_slb_fail_src(data)                                   ((0x00000002&(data))>>1)
#define PHY2_SLB2_ST_get_p2_usb2phy_slb_fail(data)                                   ((0x00000002&(data))>>1)
#define PHY2_SLB2_ST_p2_usb2phy_slb_done_shift                                       (0)
#define PHY2_SLB2_ST_p2_usb2phy_slb_done_mask                                        (0x00000001)
#define PHY2_SLB2_ST_p2_usb2phy_slb_done(data)                                       (0x00000001&((data)<<0))
#define PHY2_SLB2_ST_p2_usb2phy_slb_done_src(data)                                   ((0x00000001&(data))>>0)
#define PHY2_SLB2_ST_get_p2_usb2phy_slb_done(data)                                   ((0x00000001&(data))>>0)


#define SLP_BACK3_CTR                                                                0x18013050
#define SLP_BACK3_CTR_reg_addr                                                       "0xB8013050"
#define SLP_BACK3_CTR_reg                                                            0xB8013050
#define set_SLP_BACK3_CTR_reg(data)   (*((volatile unsigned int*) SLP_BACK3_CTR_reg)=data)
#define get_SLP_BACK3_CTR_reg   (*((volatile unsigned int*) SLP_BACK3_CTR_reg))
#define SLP_BACK3_CTR_inst_adr                                                       "0x0014"
#define SLP_BACK3_CTR_inst                                                           0x0014
#define SLP_BACK3_CTR_test_speed_p3_shift                                            (10)
#define SLP_BACK3_CTR_test_speed_p3_mask                                             (0x00000C00)
#define SLP_BACK3_CTR_test_speed_p3(data)                                            (0x00000C00&((data)<<10))
#define SLP_BACK3_CTR_test_speed_p3_src(data)                                        ((0x00000C00&(data))>>10)
#define SLP_BACK3_CTR_get_test_speed_p3(data)                                        ((0x00000C00&(data))>>10)
#define SLP_BACK3_CTR_test_seed_p3_shift                                             (2)
#define SLP_BACK3_CTR_test_seed_p3_mask                                              (0x000003FC)
#define SLP_BACK3_CTR_test_seed_p3(data)                                             (0x000003FC&((data)<<2))
#define SLP_BACK3_CTR_test_seed_p3_src(data)                                         ((0x000003FC&(data))>>2)
#define SLP_BACK3_CTR_get_test_seed_p3(data)                                         ((0x000003FC&(data))>>2)
#define SLP_BACK3_CTR_test_psl_p3_shift                                              (0)
#define SLP_BACK3_CTR_test_psl_p3_mask                                               (0x00000003)
#define SLP_BACK3_CTR_test_psl_p3(data)                                              (0x00000003&((data)<<0))
#define SLP_BACK3_CTR_test_psl_p3_src(data)                                          ((0x00000003&(data))>>0)
#define SLP_BACK3_CTR_get_test_psl_p3(data)                                          ((0x00000003&(data))>>0)


#define SLP_BACK3_ST                                                                 0x18013054
#define SLP_BACK3_ST_reg_addr                                                        "0xB8013054"
#define SLP_BACK3_ST_reg                                                             0xB8013054
#define set_SLP_BACK3_ST_reg(data)   (*((volatile unsigned int*) SLP_BACK3_ST_reg)=data)
#define get_SLP_BACK3_ST_reg   (*((volatile unsigned int*) SLP_BACK3_ST_reg))
#define SLP_BACK3_ST_inst_adr                                                        "0x0015"
#define SLP_BACK3_ST_inst                                                            0x0015
#define SLP_BACK3_ST_test_fail_p3_shift                                              (1)
#define SLP_BACK3_ST_test_fail_p3_mask                                               (0x00000002)
#define SLP_BACK3_ST_test_fail_p3(data)                                              (0x00000002&((data)<<1))
#define SLP_BACK3_ST_test_fail_p3_src(data)                                          ((0x00000002&(data))>>1)
#define SLP_BACK3_ST_get_test_fail_p3(data)                                          ((0x00000002&(data))>>1)
#define SLP_BACK3_ST_test_done_p3_shift                                              (0)
#define SLP_BACK3_ST_test_done_p3_mask                                               (0x00000001)
#define SLP_BACK3_ST_test_done_p3(data)                                              (0x00000001&((data)<<0))
#define SLP_BACK3_ST_test_done_p3_src(data)                                          ((0x00000001&(data))>>0)
#define SLP_BACK3_ST_get_test_done_p3(data)                                          ((0x00000001&(data))>>0)


#define PHY2_SLB3_EN                                                                 0x18013058
#define PHY2_SLB3_EN_reg_addr                                                        "0xB8013058"
#define PHY2_SLB3_EN_reg                                                             0xB8013058
#define set_PHY2_SLB3_EN_reg(data)   (*((volatile unsigned int*) PHY2_SLB3_EN_reg)=data)
#define get_PHY2_SLB3_EN_reg   (*((volatile unsigned int*) PHY2_SLB3_EN_reg))
#define PHY2_SLB3_EN_inst_adr                                                        "0x0016"
#define PHY2_SLB3_EN_inst                                                            0x0016
#define PHY2_SLB3_EN_p3_usb2phy_slb_hs_shift                                         (1)
#define PHY2_SLB3_EN_p3_usb2phy_slb_hs_mask                                          (0x00000002)
#define PHY2_SLB3_EN_p3_usb2phy_slb_hs(data)                                         (0x00000002&((data)<<1))
#define PHY2_SLB3_EN_p3_usb2phy_slb_hs_src(data)                                     ((0x00000002&(data))>>1)
#define PHY2_SLB3_EN_get_p3_usb2phy_slb_hs(data)                                     ((0x00000002&(data))>>1)
#define PHY2_SLB3_EN_p3_usb2phy_force_slb_shift                                      (0)
#define PHY2_SLB3_EN_p3_usb2phy_force_slb_mask                                       (0x00000001)
#define PHY2_SLB3_EN_p3_usb2phy_force_slb(data)                                      (0x00000001&((data)<<0))
#define PHY2_SLB3_EN_p3_usb2phy_force_slb_src(data)                                  ((0x00000001&(data))>>0)
#define PHY2_SLB3_EN_get_p3_usb2phy_force_slb(data)                                  ((0x00000001&(data))>>0)


#define PHY2_SLB3_ST                                                                 0x1801305c
#define PHY2_SLB3_ST_reg_addr                                                        "0xB801305C"
#define PHY2_SLB3_ST_reg                                                             0xB801305C
#define set_PHY2_SLB3_ST_reg(data)   (*((volatile unsigned int*) PHY2_SLB3_ST_reg)=data)
#define get_PHY2_SLB3_ST_reg   (*((volatile unsigned int*) PHY2_SLB3_ST_reg))
#define PHY2_SLB3_ST_inst_adr                                                        "0x0017"
#define PHY2_SLB3_ST_inst                                                            0x0017
#define PHY2_SLB3_ST_p3_usb2phy_slb_fail_shift                                       (1)
#define PHY2_SLB3_ST_p3_usb2phy_slb_fail_mask                                        (0x00000002)
#define PHY2_SLB3_ST_p3_usb2phy_slb_fail(data)                                       (0x00000002&((data)<<1))
#define PHY2_SLB3_ST_p3_usb2phy_slb_fail_src(data)                                   ((0x00000002&(data))>>1)
#define PHY2_SLB3_ST_get_p3_usb2phy_slb_fail(data)                                   ((0x00000002&(data))>>1)
#define PHY2_SLB3_ST_p3_usb2phy_slb_done_shift                                       (0)
#define PHY2_SLB3_ST_p3_usb2phy_slb_done_mask                                        (0x00000001)
#define PHY2_SLB3_ST_p3_usb2phy_slb_done(data)                                       (0x00000001&((data)<<0))
#define PHY2_SLB3_ST_p3_usb2phy_slb_done_src(data)                                   ((0x00000001&(data))>>0)
#define PHY2_SLB3_ST_get_p3_usb2phy_slb_done(data)                                   ((0x00000001&(data))>>0)


#define USB2_SPD_CTR                                                                 0x18013060
#define USB2_SPD_CTR_reg_addr                                                        "0xB8013060"
#define USB2_SPD_CTR_reg                                                             0xB8013060
#define set_USB2_SPD_CTR_reg(data)   (*((volatile unsigned int*) USB2_SPD_CTR_reg)=data)
#define get_USB2_SPD_CTR_reg   (*((volatile unsigned int*) USB2_SPD_CTR_reg))
#define USB2_SPD_CTR_inst_adr                                                        "0x0018"
#define USB2_SPD_CTR_inst                                                            0x0018
#define USB2_SPD_CTR_p3_suspend_r_shift                                              (3)
#define USB2_SPD_CTR_p3_suspend_r_mask                                               (0x00000008)
#define USB2_SPD_CTR_p3_suspend_r(data)                                              (0x00000008&((data)<<3))
#define USB2_SPD_CTR_p3_suspend_r_src(data)                                          ((0x00000008&(data))>>3)
#define USB2_SPD_CTR_get_p3_suspend_r(data)                                          ((0x00000008&(data))>>3)
#define USB2_SPD_CTR_p2_suspend_r_shift                                              (2)
#define USB2_SPD_CTR_p2_suspend_r_mask                                               (0x00000004)
#define USB2_SPD_CTR_p2_suspend_r(data)                                              (0x00000004&((data)<<2))
#define USB2_SPD_CTR_p2_suspend_r_src(data)                                          ((0x00000004&(data))>>2)
#define USB2_SPD_CTR_get_p2_suspend_r(data)                                          ((0x00000004&(data))>>2)
#define USB2_SPD_CTR_p1_suspend_r_shift                                              (1)
#define USB2_SPD_CTR_p1_suspend_r_mask                                               (0x00000002)
#define USB2_SPD_CTR_p1_suspend_r(data)                                              (0x00000002&((data)<<1))
#define USB2_SPD_CTR_p1_suspend_r_src(data)                                          ((0x00000002&(data))>>1)
#define USB2_SPD_CTR_get_p1_suspend_r(data)                                          ((0x00000002&(data))>>1)
#define USB2_SPD_CTR_p0_suspend_r_shift                                              (0)
#define USB2_SPD_CTR_p0_suspend_r_mask                                               (0x00000001)
#define USB2_SPD_CTR_p0_suspend_r(data)                                              (0x00000001&((data)<<0))
#define USB2_SPD_CTR_p0_suspend_r_src(data)                                          ((0x00000001&(data))>>0)
#define USB2_SPD_CTR_get_p0_suspend_r(data)                                          ((0x00000001&(data))>>0)


#define PHY3_SLB_EN                                                                  0x18013064
#define PHY3_SLB_EN_reg_addr                                                         "0xB8013064"
#define PHY3_SLB_EN_reg                                                              0xB8013064
#define set_PHY3_SLB_EN_reg(data)   (*((volatile unsigned int*) PHY3_SLB_EN_reg)=data)
#define get_PHY3_SLB_EN_reg   (*((volatile unsigned int*) PHY3_SLB_EN_reg))
#define PHY3_SLB_EN_inst_adr                                                         "0x0019"
#define PHY3_SLB_EN_inst                                                             0x0019
#define PHY3_SLB_EN_p0_pipe_bist_sel_shift                                           (1)
#define PHY3_SLB_EN_p0_pipe_bist_sel_mask                                            (0x00000006)
#define PHY3_SLB_EN_p0_pipe_bist_sel(data)                                           (0x00000006&((data)<<1))
#define PHY3_SLB_EN_p0_pipe_bist_sel_src(data)                                       ((0x00000006&(data))>>1)
#define PHY3_SLB_EN_get_p0_pipe_bist_sel(data)                                       ((0x00000006&(data))>>1)
#define PHY3_SLB_EN_p0_pipe_bist_en_shift                                            (0)
#define PHY3_SLB_EN_p0_pipe_bist_en_mask                                             (0x00000001)
#define PHY3_SLB_EN_p0_pipe_bist_en(data)                                            (0x00000001&((data)<<0))
#define PHY3_SLB_EN_p0_pipe_bist_en_src(data)                                        ((0x00000001&(data))>>0)
#define PHY3_SLB_EN_get_p0_pipe_bist_en(data)                                        ((0x00000001&(data))>>0)


#define PHY3_SLB_CT                                                                  0x18013068
#define PHY3_SLB_CT_reg_addr                                                         "0xB8013068"
#define PHY3_SLB_CT_reg                                                              0xB8013068
#define set_PHY3_SLB_CT_reg(data)   (*((volatile unsigned int*) PHY3_SLB_CT_reg)=data)
#define get_PHY3_SLB_CT_reg   (*((volatile unsigned int*) PHY3_SLB_CT_reg))
#define PHY3_SLB_CT_inst_adr                                                         "0x001A"
#define PHY3_SLB_CT_inst                                                             0x001A
#define PHY3_SLB_CT_p0_usb3phy_slb_go_shift                                          (0)
#define PHY3_SLB_CT_p0_usb3phy_slb_go_mask                                           (0x00000001)
#define PHY3_SLB_CT_p0_usb3phy_slb_go(data)                                          (0x00000001&((data)<<0))
#define PHY3_SLB_CT_p0_usb3phy_slb_go_src(data)                                      ((0x00000001&(data))>>0)
#define PHY3_SLB_CT_get_p0_usb3phy_slb_go(data)                                      ((0x00000001&(data))>>0)


#define PHY3_SLB_ST                                                                  0x1801306c
#define PHY3_SLB_ST_reg_addr                                                         "0xB801306C"
#define PHY3_SLB_ST_reg                                                              0xB801306C
#define set_PHY3_SLB_ST_reg(data)   (*((volatile unsigned int*) PHY3_SLB_ST_reg)=data)
#define get_PHY3_SLB_ST_reg   (*((volatile unsigned int*) PHY3_SLB_ST_reg))
#define PHY3_SLB_ST_inst_adr                                                         "0x001B"
#define PHY3_SLB_ST_inst                                                             0x001B
#define PHY3_SLB_ST_p0_usb3phy_slb_fail_shift                                        (1)
#define PHY3_SLB_ST_p0_usb3phy_slb_fail_mask                                         (0x00000002)
#define PHY3_SLB_ST_p0_usb3phy_slb_fail(data)                                        (0x00000002&((data)<<1))
#define PHY3_SLB_ST_p0_usb3phy_slb_fail_src(data)                                    ((0x00000002&(data))>>1)
#define PHY3_SLB_ST_get_p0_usb3phy_slb_fail(data)                                    ((0x00000002&(data))>>1)
#define PHY3_SLB_ST_p0_usb3phy_slb_done_shift                                        (0)
#define PHY3_SLB_ST_p0_usb3phy_slb_done_mask                                         (0x00000001)
#define PHY3_SLB_ST_p0_usb3phy_slb_done(data)                                        (0x00000001&((data)<<0))
#define PHY3_SLB_ST_p0_usb3phy_slb_done_src(data)                                    ((0x00000001&(data))>>0)
#define PHY3_SLB_ST_get_p0_usb3phy_slb_done(data)                                    ((0x00000001&(data))>>0)


#define USB_DBG                                                                      0x18013070
#define USB_DBG_reg_addr                                                             "0xB8013070"
#define USB_DBG_reg                                                                  0xB8013070
#define set_USB_DBG_reg(data)   (*((volatile unsigned int*) USB_DBG_reg)=data)
#define get_USB_DBG_reg   (*((volatile unsigned int*) USB_DBG_reg))
#define USB_DBG_inst_adr                                                             "0x001C"
#define USB_DBG_inst                                                                 0x001C
#define USB_DBG_dbg_sel1_shift                                                       (7)
#define USB_DBG_dbg_sel1_mask                                                        (0x00001F80)
#define USB_DBG_dbg_sel1(data)                                                       (0x00001F80&((data)<<7))
#define USB_DBG_dbg_sel1_src(data)                                                   ((0x00001F80&(data))>>7)
#define USB_DBG_get_dbg_sel1(data)                                                   ((0x00001F80&(data))>>7)
#define USB_DBG_dbg_sel0_shift                                                       (1)
#define USB_DBG_dbg_sel0_mask                                                        (0x0000007E)
#define USB_DBG_dbg_sel0(data)                                                       (0x0000007E&((data)<<1))
#define USB_DBG_dbg_sel0_src(data)                                                   ((0x0000007E&(data))>>1)
#define USB_DBG_get_dbg_sel0(data)                                                   ((0x0000007E&(data))>>1)
#define USB_DBG_dbg_en_shift                                                         (0)
#define USB_DBG_dbg_en_mask                                                          (0x00000001)
#define USB_DBG_dbg_en(data)                                                         (0x00000001&((data)<<0))
#define USB_DBG_dbg_en_src(data)                                                     ((0x00000001&(data))>>0)
#define USB_DBG_get_dbg_en(data)                                                     ((0x00000001&(data))>>0)


#define USB_SCTCH                                                                    0x18013074
#define USB_SCTCH_reg_addr                                                           "0xB8013074"
#define USB_SCTCH_reg                                                                0xB8013074
#define set_USB_SCTCH_reg(data)   (*((volatile unsigned int*) USB_SCTCH_reg)=data)
#define get_USB_SCTCH_reg   (*((volatile unsigned int*) USB_SCTCH_reg))
#define USB_SCTCH_inst_adr                                                           "0x001D"
#define USB_SCTCH_inst                                                               0x001D
#define USB_SCTCH_reg1_shift                                                         (16)
#define USB_SCTCH_reg1_mask                                                          (0xFFFF0000)
#define USB_SCTCH_reg1(data)                                                         (0xFFFF0000&((data)<<16))
#define USB_SCTCH_reg1_src(data)                                                     ((0xFFFF0000&(data))>>16)
#define USB_SCTCH_get_reg1(data)                                                     ((0xFFFF0000&(data))>>16)
#define USB_SCTCH_reg0_shift                                                         (0)
#define USB_SCTCH_reg0_mask                                                          (0x0000FFFF)
#define USB_SCTCH_reg0(data)                                                         (0x0000FFFF&((data)<<0))
#define USB_SCTCH_reg0_src(data)                                                     ((0x0000FFFF&(data))>>0)
#define USB_SCTCH_get_reg0(data)                                                     ((0x0000FFFF&(data))>>0)


#define USB_TMP_SP_0                                                                 0x18013078
#define USB_TMP_SP_1                                                                 0x1801307C
#define USB_TMP_SP_0_reg_addr                                                        "0xB8013078"
#define USB_TMP_SP_1_reg_addr                                                        "0xB801307C"
#define USB_TMP_SP_0_reg                                                             0xB8013078
#define USB_TMP_SP_1_reg                                                             0xB801307C
#define set_USB_TMP_SP_0_reg(data)   (*((volatile unsigned int*) USB_TMP_SP_0_reg)=data)
#define set_USB_TMP_SP_1_reg(data)   (*((volatile unsigned int*) USB_TMP_SP_1_reg)=data)
#define get_USB_TMP_SP_0_reg   (*((volatile unsigned int*) USB_TMP_SP_0_reg))
#define get_USB_TMP_SP_1_reg   (*((volatile unsigned int*) USB_TMP_SP_1_reg))
#define USB_TMP_SP_0_inst_adr                                                        "0x001E"
#define USB_TMP_SP_1_inst_adr                                                        "0x001F"
#define USB_TMP_SP_0_inst                                                            0x001E
#define USB_TMP_SP_1_inst                                                            0x001F
#define USB_TMP_SP_test_sp_reg_shift                                                 (0)
#define USB_TMP_SP_test_sp_reg_mask                                                  (0xFFFFFFFF)
#define USB_TMP_SP_test_sp_reg(data)                                                 (0xFFFFFFFF&((data)<<0))
#define USB_TMP_SP_test_sp_reg_src(data)                                             ((0xFFFFFFFF&(data))>>0)
#define USB_TMP_SP_get_test_sp_reg(data)                                             ((0xFFFFFFFF&(data))>>0)


#define USB_TMP_0                                                                    0x18013080
#define USB_TMP_1                                                                    0x18013084
#define USB_TMP_2                                                                    0x18013088
#define USB_TMP_3                                                                    0x1801308C
#define USB_TMP_0_reg_addr                                                           "0xB8013080"
#define USB_TMP_1_reg_addr                                                           "0xB8013084"
#define USB_TMP_2_reg_addr                                                           "0xB8013088"
#define USB_TMP_3_reg_addr                                                           "0xB801308C"
#define USB_TMP_0_reg                                                                0xB8013080
#define USB_TMP_1_reg                                                                0xB8013084
#define USB_TMP_2_reg                                                                0xB8013088
#define USB_TMP_3_reg                                                                0xB801308C
#define set_USB_TMP_0_reg(data)   (*((volatile unsigned int*) USB_TMP_0_reg)=data)
#define set_USB_TMP_1_reg(data)   (*((volatile unsigned int*) USB_TMP_1_reg)=data)
#define set_USB_TMP_2_reg(data)   (*((volatile unsigned int*) USB_TMP_2_reg)=data)
#define set_USB_TMP_3_reg(data)   (*((volatile unsigned int*) USB_TMP_3_reg)=data)
#define get_USB_TMP_0_reg   (*((volatile unsigned int*) USB_TMP_0_reg))
#define get_USB_TMP_1_reg   (*((volatile unsigned int*) USB_TMP_1_reg))
#define get_USB_TMP_2_reg   (*((volatile unsigned int*) USB_TMP_2_reg))
#define get_USB_TMP_3_reg   (*((volatile unsigned int*) USB_TMP_3_reg))
#define USB_TMP_0_inst_adr                                                           "0x0020"
#define USB_TMP_1_inst_adr                                                           "0x0021"
#define USB_TMP_2_inst_adr                                                           "0x0022"
#define USB_TMP_3_inst_adr                                                           "0x0023"
#define USB_TMP_0_inst                                                               0x0020
#define USB_TMP_1_inst                                                               0x0021
#define USB_TMP_2_inst                                                               0x0022
#define USB_TMP_3_inst                                                               0x0023
#define USB_TMP_test_reg_shift                                                       (0)
#define USB_TMP_test_reg_mask                                                        (0xFFFFFFFF)
#define USB_TMP_test_reg(data)                                                       (0xFFFFFFFF&((data)<<0))
#define USB_TMP_test_reg_src(data)                                                   ((0xFFFFFFFF&(data))>>0)
#define USB_TMP_get_test_reg(data)                                                   ((0xFFFFFFFF&(data))>>0)


#define HMAC_CTR0                                                                    0x18013090
#define HMAC_CTR0_reg_addr                                                           "0xB8013090"
#define HMAC_CTR0_reg                                                                0xB8013090
#define set_HMAC_CTR0_reg(data)   (*((volatile unsigned int*) HMAC_CTR0_reg)=data)
#define get_HMAC_CTR0_reg   (*((volatile unsigned int*) HMAC_CTR0_reg))
#define HMAC_CTR0_inst_adr                                                           "0x0024"
#define HMAC_CTR0_inst                                                               0x0024
#define HMAC_CTR0_xhci_revision_shift                                                (31)
#define HMAC_CTR0_xhci_revision_mask                                                 (0x80000000)
#define HMAC_CTR0_xhci_revision(data)                                                (0x80000000&((data)<<31))
#define HMAC_CTR0_xhci_revision_src(data)                                            ((0x80000000&(data))>>31)
#define HMAC_CTR0_get_xhci_revision(data)                                            ((0x80000000&(data))>>31)
#define HMAC_CTR0_host_fladj_30mhz_shift                                             (25)
#define HMAC_CTR0_host_fladj_30mhz_mask                                              (0x7E000000)
#define HMAC_CTR0_host_fladj_30mhz(data)                                             (0x7E000000&((data)<<25))
#define HMAC_CTR0_host_fladj_30mhz_src(data)                                         ((0x7E000000&(data))>>25)
#define HMAC_CTR0_get_host_fladj_30mhz(data)                                         ((0x7E000000&(data))>>25)
#define HMAC_CTR0_host_ppc_present_shift                                             (24)
#define HMAC_CTR0_host_ppc_present_mask                                              (0x01000000)
#define HMAC_CTR0_host_ppc_present(data)                                             (0x01000000&((data)<<24))
#define HMAC_CTR0_host_ppc_present_src(data)                                         ((0x01000000&(data))>>24)
#define HMAC_CTR0_get_host_ppc_present(data)                                         ((0x01000000&(data))>>24)
#define HMAC_CTR0_host_msi_enable_shift                                              (23)
#define HMAC_CTR0_host_msi_enable_mask                                               (0x00800000)
#define HMAC_CTR0_host_msi_enable(data)                                              (0x00800000&((data)<<23))
#define HMAC_CTR0_host_msi_enable_src(data)                                          ((0x00800000&(data))>>23)
#define HMAC_CTR0_get_host_msi_enable(data)                                          ((0x00800000&(data))>>23)
#define HMAC_CTR0_host_pm_pw_state_req_shift                                         (21)
#define HMAC_CTR0_host_pm_pw_state_req_mask                                          (0x00600000)
#define HMAC_CTR0_host_pm_pw_state_req(data)                                         (0x00600000&((data)<<21))
#define HMAC_CTR0_host_pm_pw_state_req_src(data)                                     ((0x00600000&(data))>>21)
#define HMAC_CTR0_get_host_pm_pw_state_req(data)                                     ((0x00600000&(data))>>21)
#define HMAC_CTR0_hub_port_perm_attach_shift                                         (16)
#define HMAC_CTR0_hub_port_perm_attach_mask                                          (0x001F0000)
#define HMAC_CTR0_hub_port_perm_attach(data)                                         (0x001F0000&((data)<<16))
#define HMAC_CTR0_hub_port_perm_attach_src(data)                                     ((0x001F0000&(data))>>16)
#define HMAC_CTR0_get_hub_port_perm_attach(data)                                     ((0x001F0000&(data))>>16)
#define HMAC_CTR0_host_u2_port_disable_shift                                         (9)
#define HMAC_CTR0_host_u2_port_disable_mask                                          (0x00001E00)
#define HMAC_CTR0_host_u2_port_disable(data)                                         (0x00001E00&((data)<<9))
#define HMAC_CTR0_host_u2_port_disable_src(data)                                     ((0x00001E00&(data))>>9)
#define HMAC_CTR0_get_host_u2_port_disable(data)                                     ((0x00001E00&(data))>>9)
#define HMAC_CTR0_host_u3_port_disable_shift                                         (8)
#define HMAC_CTR0_host_u3_port_disable_mask                                          (0x00000100)
#define HMAC_CTR0_host_u3_port_disable(data)                                         (0x00000100&((data)<<8))
#define HMAC_CTR0_host_u3_port_disable_src(data)                                     ((0x00000100&(data))>>8)
#define HMAC_CTR0_get_host_u3_port_disable(data)                                     ((0x00000100&(data))>>8)
#define HMAC_CTR0_host_num_u2_port_shift                                             (4)
#define HMAC_CTR0_host_num_u2_port_mask                                              (0x000000F0)
#define HMAC_CTR0_host_num_u2_port(data)                                             (0x000000F0&((data)<<4))
#define HMAC_CTR0_host_num_u2_port_src(data)                                         ((0x000000F0&(data))>>4)
#define HMAC_CTR0_get_host_num_u2_port(data)                                         ((0x000000F0&(data))>>4)
#define HMAC_CTR0_host_num_u3_port_shift                                             (0)
#define HMAC_CTR0_host_num_u3_port_mask                                              (0x0000000F)
#define HMAC_CTR0_host_num_u3_port(data)                                             (0x0000000F&((data)<<0))
#define HMAC_CTR0_host_num_u3_port_src(data)                                         ((0x0000000F&(data))>>0)
#define HMAC_CTR0_get_host_num_u3_port(data)                                         ((0x0000000F&(data))>>0)


#define HMAC_CTR1                                                                    0x18013094
#define HMAC_CTR1_reg_addr                                                           "0xB8013094"
#define HMAC_CTR1_reg                                                                0xB8013094
#define set_HMAC_CTR1_reg(data)   (*((volatile unsigned int*) HMAC_CTR1_reg)=data)
#define get_HMAC_CTR1_reg   (*((volatile unsigned int*) HMAC_CTR1_reg))
#define HMAC_CTR1_inst_adr                                                           "0x0025"
#define HMAC_CTR1_inst                                                               0x0025
#define HMAC_CTR1_host_utmiotg_vbusvalid_shift                                       (28)
#define HMAC_CTR1_host_utmiotg_vbusvalid_mask                                        (0xF0000000)
#define HMAC_CTR1_host_utmiotg_vbusvalid(data)                                       (0xF0000000&((data)<<28))
#define HMAC_CTR1_host_utmiotg_vbusvalid_src(data)                                   ((0xF0000000&(data))>>28)
#define HMAC_CTR1_get_host_utmiotg_vbusvalid(data)                                   ((0xF0000000&(data))>>28)
#define HMAC_CTR1_host_mac_vbus_inv_shift                                            (24)
#define HMAC_CTR1_host_mac_vbus_inv_mask                                             (0x0F000000)
#define HMAC_CTR1_host_mac_vbus_inv(data)                                            (0x0F000000&((data)<<24))
#define HMAC_CTR1_host_mac_vbus_inv_src(data)                                        ((0x0F000000&(data))>>24)
#define HMAC_CTR1_get_host_mac_vbus_inv(data)                                        ((0x0F000000&(data))>>24)
#define HMAC_CTR1_host_vbus_value_shift                                              (20)
#define HMAC_CTR1_host_vbus_value_mask                                               (0x00F00000)
#define HMAC_CTR1_host_vbus_value(data)                                              (0x00F00000&((data)<<20))
#define HMAC_CTR1_host_vbus_value_src(data)                                          ((0x00F00000&(data))>>20)
#define HMAC_CTR1_get_host_vbus_value(data)                                          ((0x00F00000&(data))>>20)
#define HMAC_CTR1_host_vbus_sel_shift                                                (16)
#define HMAC_CTR1_host_vbus_sel_mask                                                 (0x000F0000)
#define HMAC_CTR1_host_vbus_sel(data)                                                (0x000F0000&((data)<<16))
#define HMAC_CTR1_host_vbus_sel_src(data)                                            ((0x000F0000&(data))>>16)
#define HMAC_CTR1_get_host_vbus_sel(data)                                            ((0x000F0000&(data))>>16)
#define HMAC_CTR1_hub_port_over_cur_inv_shift                                        (8)
#define HMAC_CTR1_hub_port_over_cur_inv_mask                                         (0x00000F00)
#define HMAC_CTR1_hub_port_over_cur_inv(data)                                        (0x00000F00&((data)<<8))
#define HMAC_CTR1_hub_port_over_cur_inv_src(data)                                    ((0x00000F00&(data))>>8)
#define HMAC_CTR1_get_hub_port_over_cur_inv(data)                                    ((0x00000F00&(data))>>8)
#define HMAC_CTR1_host_over_cur_value_shift                                          (4)
#define HMAC_CTR1_host_over_cur_value_mask                                           (0x000000F0)
#define HMAC_CTR1_host_over_cur_value(data)                                          (0x000000F0&((data)<<4))
#define HMAC_CTR1_host_over_cur_value_src(data)                                      ((0x000000F0&(data))>>4)
#define HMAC_CTR1_get_host_over_cur_value(data)                                      ((0x000000F0&(data))>>4)
#define HMAC_CTR1_host_over_cur_sel_shift                                            (0)
#define HMAC_CTR1_host_over_cur_sel_mask                                             (0x0000000F)
#define HMAC_CTR1_host_over_cur_sel(data)                                            (0x0000000F&((data)<<0))
#define HMAC_CTR1_host_over_cur_sel_src(data)                                        ((0x0000000F&(data))>>0)
#define HMAC_CTR1_get_host_over_cur_sel(data)                                        ((0x0000000F&(data))>>0)


#define MAC3_HST_ST                                                                  0x18013098
#define MAC3_HST_ST_reg_addr                                                         "0xB8013098"
#define MAC3_HST_ST_reg                                                              0xB8013098
#define set_MAC3_HST_ST_reg(data)   (*((volatile unsigned int*) MAC3_HST_ST_reg)=data)
#define get_MAC3_HST_ST_reg   (*((volatile unsigned int*) MAC3_HST_ST_reg))
#define MAC3_HST_ST_inst_adr                                                         "0x0026"
#define MAC3_HST_ST_inst                                                             0x0026
#define MAC3_HST_ST_host_current_power_state_shift                                   (5)
#define MAC3_HST_ST_host_current_power_state_mask                                    (0x00000060)
#define MAC3_HST_ST_host_current_power_state(data)                                   (0x00000060&((data)<<5))
#define MAC3_HST_ST_host_current_power_state_src(data)                               ((0x00000060&(data))>>5)
#define MAC3_HST_ST_get_host_current_power_state(data)                               ((0x00000060&(data))>>5)
#define MAC3_HST_ST_host_hub_vbus_ctrl_shift                                         (0)
#define MAC3_HST_ST_host_hub_vbus_ctrl_mask                                          (0x0000001F)
#define MAC3_HST_ST_host_hub_vbus_ctrl(data)                                         (0x0000001F&((data)<<0))
#define MAC3_HST_ST_host_hub_vbus_ctrl_src(data)                                     ((0x0000001F&(data))>>0)
#define MAC3_HST_ST_get_host_hub_vbus_ctrl(data)                                     ((0x0000001F&(data))>>0)


#define USB2_PHY0                                                                    0x1801309c
#define USB2_PHY0_reg_addr                                                           "0xB801309C"
#define USB2_PHY0_reg                                                                0xB801309C
#define set_USB2_PHY0_reg(data)   (*((volatile unsigned int*) USB2_PHY0_reg)=data)
#define get_USB2_PHY0_reg   (*((volatile unsigned int*) USB2_PHY0_reg))
#define USB2_PHY0_inst_adr                                                           "0x0027"
#define USB2_PHY0_inst                                                               0x0027
#define USB2_PHY0_p0_DmPulldown_shift                                                (10)
#define USB2_PHY0_p0_DmPulldown_mask                                                 (0x00000400)
#define USB2_PHY0_p0_DmPulldown(data)                                                (0x00000400&((data)<<10))
#define USB2_PHY0_p0_DmPulldown_src(data)                                            ((0x00000400&(data))>>10)
#define USB2_PHY0_get_p0_DmPulldown(data)                                            ((0x00000400&(data))>>10)
#define USB2_PHY0_p0_DpPulldown_shift                                                (9)
#define USB2_PHY0_p0_DpPulldown_mask                                                 (0x00000200)
#define USB2_PHY0_p0_DpPulldown(data)                                                (0x00000200&((data)<<9))
#define USB2_PHY0_p0_DpPulldown_src(data)                                            ((0x00000200&(data))>>9)
#define USB2_PHY0_get_p0_DpPulldown(data)                                            ((0x00000200&(data))>>9)
#define USB2_PHY0_p0_IDPULLUP_shift                                                  (8)
#define USB2_PHY0_p0_IDPULLUP_mask                                                   (0x00000100)
#define USB2_PHY0_p0_IDPULLUP(data)                                                  (0x00000100&((data)<<8))
#define USB2_PHY0_p0_IDPULLUP_src(data)                                              ((0x00000100&(data))>>8)
#define USB2_PHY0_get_p0_IDPULLUP(data)                                              ((0x00000100&(data))>>8)
#define USB2_PHY0_p0_DmPulldown_sel_shift                                            (2)
#define USB2_PHY0_p0_DmPulldown_sel_mask                                             (0x00000004)
#define USB2_PHY0_p0_DmPulldown_sel(data)                                            (0x00000004&((data)<<2))
#define USB2_PHY0_p0_DmPulldown_sel_src(data)                                        ((0x00000004&(data))>>2)
#define USB2_PHY0_get_p0_DmPulldown_sel(data)                                        ((0x00000004&(data))>>2)
#define USB2_PHY0_p0_DpPulldown_sel_shift                                            (1)
#define USB2_PHY0_p0_DpPulldown_sel_mask                                             (0x00000002)
#define USB2_PHY0_p0_DpPulldown_sel(data)                                            (0x00000002&((data)<<1))
#define USB2_PHY0_p0_DpPulldown_sel_src(data)                                        ((0x00000002&(data))>>1)
#define USB2_PHY0_get_p0_DpPulldown_sel(data)                                        ((0x00000002&(data))>>1)
#define USB2_PHY0_p0_IDPULLUP_sel_shift                                              (0)
#define USB2_PHY0_p0_IDPULLUP_sel_mask                                               (0x00000001)
#define USB2_PHY0_p0_IDPULLUP_sel(data)                                              (0x00000001&((data)<<0))
#define USB2_PHY0_p0_IDPULLUP_sel_src(data)                                          ((0x00000001&(data))>>0)
#define USB2_PHY0_get_p0_IDPULLUP_sel(data)                                          ((0x00000001&(data))>>0)


#define USB2_PHY1                                                                    0x180130a0
#define USB2_PHY1_reg_addr                                                           "0xB80130A0"
#define USB2_PHY1_reg                                                                0xB80130A0
#define set_USB2_PHY1_reg(data)   (*((volatile unsigned int*) USB2_PHY1_reg)=data)
#define get_USB2_PHY1_reg   (*((volatile unsigned int*) USB2_PHY1_reg))
#define USB2_PHY1_inst_adr                                                           "0x0028"
#define USB2_PHY1_inst                                                               0x0028
#define USB2_PHY1_p1_DmPulldown_shift                                                (10)
#define USB2_PHY1_p1_DmPulldown_mask                                                 (0x00000400)
#define USB2_PHY1_p1_DmPulldown(data)                                                (0x00000400&((data)<<10))
#define USB2_PHY1_p1_DmPulldown_src(data)                                            ((0x00000400&(data))>>10)
#define USB2_PHY1_get_p1_DmPulldown(data)                                            ((0x00000400&(data))>>10)
#define USB2_PHY1_p1_DpPulldown_shift                                                (9)
#define USB2_PHY1_p1_DpPulldown_mask                                                 (0x00000200)
#define USB2_PHY1_p1_DpPulldown(data)                                                (0x00000200&((data)<<9))
#define USB2_PHY1_p1_DpPulldown_src(data)                                            ((0x00000200&(data))>>9)
#define USB2_PHY1_get_p1_DpPulldown(data)                                            ((0x00000200&(data))>>9)
#define USB2_PHY1_p1_IDPULLUP_shift                                                  (8)
#define USB2_PHY1_p1_IDPULLUP_mask                                                   (0x00000100)
#define USB2_PHY1_p1_IDPULLUP(data)                                                  (0x00000100&((data)<<8))
#define USB2_PHY1_p1_IDPULLUP_src(data)                                              ((0x00000100&(data))>>8)
#define USB2_PHY1_get_p1_IDPULLUP(data)                                              ((0x00000100&(data))>>8)
#define USB2_PHY1_p1_DmPulldown_sel_shift                                            (2)
#define USB2_PHY1_p1_DmPulldown_sel_mask                                             (0x00000004)
#define USB2_PHY1_p1_DmPulldown_sel(data)                                            (0x00000004&((data)<<2))
#define USB2_PHY1_p1_DmPulldown_sel_src(data)                                        ((0x00000004&(data))>>2)
#define USB2_PHY1_get_p1_DmPulldown_sel(data)                                        ((0x00000004&(data))>>2)
#define USB2_PHY1_p1_DpPulldown_sel_shift                                            (1)
#define USB2_PHY1_p1_DpPulldown_sel_mask                                             (0x00000002)
#define USB2_PHY1_p1_DpPulldown_sel(data)                                            (0x00000002&((data)<<1))
#define USB2_PHY1_p1_DpPulldown_sel_src(data)                                        ((0x00000002&(data))>>1)
#define USB2_PHY1_get_p1_DpPulldown_sel(data)                                        ((0x00000002&(data))>>1)
#define USB2_PHY1_p1_IDPULLUP_sel_shift                                              (0)
#define USB2_PHY1_p1_IDPULLUP_sel_mask                                               (0x00000001)
#define USB2_PHY1_p1_IDPULLUP_sel(data)                                              (0x00000001&((data)<<0))
#define USB2_PHY1_p1_IDPULLUP_sel_src(data)                                          ((0x00000001&(data))>>0)
#define USB2_PHY1_get_p1_IDPULLUP_sel(data)                                          ((0x00000001&(data))>>0)


#define USB2_PHY2                                                                    0x180130a4
#define USB2_PHY2_reg_addr                                                           "0xB80130A4"
#define USB2_PHY2_reg                                                                0xB80130A4
#define set_USB2_PHY2_reg(data)   (*((volatile unsigned int*) USB2_PHY2_reg)=data)
#define get_USB2_PHY2_reg   (*((volatile unsigned int*) USB2_PHY2_reg))
#define USB2_PHY2_inst_adr                                                           "0x0029"
#define USB2_PHY2_inst                                                               0x0029
#define USB2_PHY2_p2_DmPulldown_shift                                                (10)
#define USB2_PHY2_p2_DmPulldown_mask                                                 (0x00000400)
#define USB2_PHY2_p2_DmPulldown(data)                                                (0x00000400&((data)<<10))
#define USB2_PHY2_p2_DmPulldown_src(data)                                            ((0x00000400&(data))>>10)
#define USB2_PHY2_get_p2_DmPulldown(data)                                            ((0x00000400&(data))>>10)
#define USB2_PHY2_p2_DpPulldown_shift                                                (9)
#define USB2_PHY2_p2_DpPulldown_mask                                                 (0x00000200)
#define USB2_PHY2_p2_DpPulldown(data)                                                (0x00000200&((data)<<9))
#define USB2_PHY2_p2_DpPulldown_src(data)                                            ((0x00000200&(data))>>9)
#define USB2_PHY2_get_p2_DpPulldown(data)                                            ((0x00000200&(data))>>9)
#define USB2_PHY2_p2_IDPULLUP_shift                                                  (8)
#define USB2_PHY2_p2_IDPULLUP_mask                                                   (0x00000100)
#define USB2_PHY2_p2_IDPULLUP(data)                                                  (0x00000100&((data)<<8))
#define USB2_PHY2_p2_IDPULLUP_src(data)                                              ((0x00000100&(data))>>8)
#define USB2_PHY2_get_p2_IDPULLUP(data)                                              ((0x00000100&(data))>>8)
#define USB2_PHY2_p2_DmPulldown_sel_shift                                            (2)
#define USB2_PHY2_p2_DmPulldown_sel_mask                                             (0x00000004)
#define USB2_PHY2_p2_DmPulldown_sel(data)                                            (0x00000004&((data)<<2))
#define USB2_PHY2_p2_DmPulldown_sel_src(data)                                        ((0x00000004&(data))>>2)
#define USB2_PHY2_get_p2_DmPulldown_sel(data)                                        ((0x00000004&(data))>>2)
#define USB2_PHY2_p2_DpPulldown_sel_shift                                            (1)
#define USB2_PHY2_p2_DpPulldown_sel_mask                                             (0x00000002)
#define USB2_PHY2_p2_DpPulldown_sel(data)                                            (0x00000002&((data)<<1))
#define USB2_PHY2_p2_DpPulldown_sel_src(data)                                        ((0x00000002&(data))>>1)
#define USB2_PHY2_get_p2_DpPulldown_sel(data)                                        ((0x00000002&(data))>>1)
#define USB2_PHY2_p2_IDPULLUP_sel_shift                                              (0)
#define USB2_PHY2_p2_IDPULLUP_sel_mask                                               (0x00000001)
#define USB2_PHY2_p2_IDPULLUP_sel(data)                                              (0x00000001&((data)<<0))
#define USB2_PHY2_p2_IDPULLUP_sel_src(data)                                          ((0x00000001&(data))>>0)
#define USB2_PHY2_get_p2_IDPULLUP_sel(data)                                          ((0x00000001&(data))>>0)


#define USB2_PHY3                                                                    0x180130a8
#define USB2_PHY3_reg_addr                                                           "0xB80130A8"
#define USB2_PHY3_reg                                                                0xB80130A8
#define set_USB2_PHY3_reg(data)   (*((volatile unsigned int*) USB2_PHY3_reg)=data)
#define get_USB2_PHY3_reg   (*((volatile unsigned int*) USB2_PHY3_reg))
#define USB2_PHY3_inst_adr                                                           "0x002A"
#define USB2_PHY3_inst                                                               0x002A
#define USB2_PHY3_p3_DmPulldown_shift                                                (10)
#define USB2_PHY3_p3_DmPulldown_mask                                                 (0x00000400)
#define USB2_PHY3_p3_DmPulldown(data)                                                (0x00000400&((data)<<10))
#define USB2_PHY3_p3_DmPulldown_src(data)                                            ((0x00000400&(data))>>10)
#define USB2_PHY3_get_p3_DmPulldown(data)                                            ((0x00000400&(data))>>10)
#define USB2_PHY3_p3_DpPulldown_shift                                                (9)
#define USB2_PHY3_p3_DpPulldown_mask                                                 (0x00000200)
#define USB2_PHY3_p3_DpPulldown(data)                                                (0x00000200&((data)<<9))
#define USB2_PHY3_p3_DpPulldown_src(data)                                            ((0x00000200&(data))>>9)
#define USB2_PHY3_get_p3_DpPulldown(data)                                            ((0x00000200&(data))>>9)
#define USB2_PHY3_p3_IDPULLUP_shift                                                  (8)
#define USB2_PHY3_p3_IDPULLUP_mask                                                   (0x00000100)
#define USB2_PHY3_p3_IDPULLUP(data)                                                  (0x00000100&((data)<<8))
#define USB2_PHY3_p3_IDPULLUP_src(data)                                              ((0x00000100&(data))>>8)
#define USB2_PHY3_get_p3_IDPULLUP(data)                                              ((0x00000100&(data))>>8)
#define USB2_PHY3_p3_DmPulldown_sel_shift                                            (2)
#define USB2_PHY3_p3_DmPulldown_sel_mask                                             (0x00000004)
#define USB2_PHY3_p3_DmPulldown_sel(data)                                            (0x00000004&((data)<<2))
#define USB2_PHY3_p3_DmPulldown_sel_src(data)                                        ((0x00000004&(data))>>2)
#define USB2_PHY3_get_p3_DmPulldown_sel(data)                                        ((0x00000004&(data))>>2)
#define USB2_PHY3_p3_DpPulldown_sel_shift                                            (1)
#define USB2_PHY3_p3_DpPulldown_sel_mask                                             (0x00000002)
#define USB2_PHY3_p3_DpPulldown_sel(data)                                            (0x00000002&((data)<<1))
#define USB2_PHY3_p3_DpPulldown_sel_src(data)                                        ((0x00000002&(data))>>1)
#define USB2_PHY3_get_p3_DpPulldown_sel(data)                                        ((0x00000002&(data))>>1)
#define USB2_PHY3_p3_IDPULLUP_sel_shift                                              (0)
#define USB2_PHY3_p3_IDPULLUP_sel_mask                                               (0x00000001)
#define USB2_PHY3_p3_IDPULLUP_sel(data)                                              (0x00000001&((data)<<0))
#define USB2_PHY3_p3_IDPULLUP_sel_src(data)                                          ((0x00000001&(data))>>0)
#define USB2_PHY3_get_p3_IDPULLUP_sel(data)                                          ((0x00000001&(data))>>0)


#define RAM_CTR                                                                      0x180130ac
#define RAM_CTR_reg_addr                                                             "0xB80130AC"
#define RAM_CTR_reg                                                                  0xB80130AC
#define set_RAM_CTR_reg(data)   (*((volatile unsigned int*) RAM_CTR_reg)=data)
#define get_RAM_CTR_reg   (*((volatile unsigned int*) RAM_CTR_reg))
#define RAM_CTR_inst_adr                                                             "0x002B"
#define RAM_CTR_inst                                                                 0x002B
#define RAM_CTR_done_st_shift                                                        (16)
#define RAM_CTR_done_st_mask                                                         (0x00010000)
#define RAM_CTR_done_st(data)                                                        (0x00010000&((data)<<16))
#define RAM_CTR_done_st_src(data)                                                    ((0x00010000&(data))>>16)
#define RAM_CTR_get_done_st(data)                                                    ((0x00010000&(data))>>16)
#define RAM_CTR_go_ct_shift                                                          (0)
#define RAM_CTR_go_ct_mask                                                           (0x00000001)
#define RAM_CTR_go_ct(data)                                                          (0x00000001&((data)<<0))
#define RAM_CTR_go_ct_src(data)                                                      ((0x00000001&(data))>>0)
#define RAM_CTR_get_go_ct(data)                                                      ((0x00000001&(data))>>0)


#define RAM_ADDR                                                                     0x180130b0
#define RAM_ADDR_reg_addr                                                            "0xB80130B0"
#define RAM_ADDR_reg                                                                 0xB80130B0
#define set_RAM_ADDR_reg(data)   (*((volatile unsigned int*) RAM_ADDR_reg)=data)
#define get_RAM_ADDR_reg   (*((volatile unsigned int*) RAM_ADDR_reg))
#define RAM_ADDR_inst_adr                                                            "0x002C"
#define RAM_ADDR_inst                                                                0x002C
#define RAM_ADDR_sram_addr_shift                                                     (0)
#define RAM_ADDR_sram_addr_mask                                                      (0xFFFFFFFF)
#define RAM_ADDR_sram_addr(data)                                                     (0xFFFFFFFF&((data)<<0))
#define RAM_ADDR_sram_addr_src(data)                                                 ((0xFFFFFFFF&(data))>>0)
#define RAM_ADDR_get_sram_addr(data)                                                 ((0xFFFFFFFF&(data))>>0)


#define RAM_WDATA                                                                    0x180130b4
#define RAM_WDATA_reg_addr                                                           "0xB80130B4"
#define RAM_WDATA_reg                                                                0xB80130B4
#define set_RAM_WDATA_reg(data)   (*((volatile unsigned int*) RAM_WDATA_reg)=data)
#define get_RAM_WDATA_reg   (*((volatile unsigned int*) RAM_WDATA_reg))
#define RAM_WDATA_inst_adr                                                           "0x002D"
#define RAM_WDATA_inst                                                               0x002D
#define RAM_WDATA_ram_wdata_shift                                                    (0)
#define RAM_WDATA_ram_wdata_mask                                                     (0xFFFFFFFF)
#define RAM_WDATA_ram_wdata(data)                                                    (0xFFFFFFFF&((data)<<0))
#define RAM_WDATA_ram_wdata_src(data)                                                ((0xFFFFFFFF&(data))>>0)
#define RAM_WDATA_get_ram_wdata(data)                                                ((0xFFFFFFFF&(data))>>0)


#define RAM_RDATA                                                                    0x180130b8
#define RAM_RDATA_reg_addr                                                           "0xB80130B8"
#define RAM_RDATA_reg                                                                0xB80130B8
#define set_RAM_RDATA_reg(data)   (*((volatile unsigned int*) RAM_RDATA_reg)=data)
#define get_RAM_RDATA_reg   (*((volatile unsigned int*) RAM_RDATA_reg))
#define RAM_RDATA_inst_adr                                                           "0x002E"
#define RAM_RDATA_inst                                                               0x002E
#define RAM_RDATA_ram_rdata_shift                                                    (0)
#define RAM_RDATA_ram_rdata_mask                                                     (0xFFFFFFFF)
#define RAM_RDATA_ram_rdata(data)                                                    (0xFFFFFFFF&((data)<<0))
#define RAM_RDATA_ram_rdata_src(data)                                                ((0xFFFFFFFF&(data))>>0)
#define RAM_RDATA_get_ram_rdata(data)                                                ((0xFFFFFFFF&(data))>>0)


#define PHY0_ST                                                                      0x180130bc
#define PHY0_ST_reg_addr                                                             "0xB80130BC"
#define PHY0_ST_reg                                                                  0xB80130BC
#define set_PHY0_ST_reg(data)   (*((volatile unsigned int*) PHY0_ST_reg)=data)
#define get_PHY0_ST_reg   (*((volatile unsigned int*) PHY0_ST_reg))
#define PHY0_ST_inst_adr                                                             "0x002F"
#define PHY0_ST_inst                                                                 0x002F
#define PHY0_ST_p0_count_num_shift                                                   (0)
#define PHY0_ST_p0_count_num_mask                                                    (0x0007FFFF)
#define PHY0_ST_p0_count_num(data)                                                   (0x0007FFFF&((data)<<0))
#define PHY0_ST_p0_count_num_src(data)                                               ((0x0007FFFF&(data))>>0)
#define PHY0_ST_get_p0_count_num(data)                                               ((0x0007FFFF&(data))>>0)


#define USB3_OVR_CT                                                                  0x180130c0
#define USB3_OVR_CT_reg_addr                                                         "0xB80130C0"
#define USB3_OVR_CT_reg                                                              0xB80130C0
#define set_USB3_OVR_CT_reg(data)   (*((volatile unsigned int*) USB3_OVR_CT_reg)=data)
#define get_USB3_OVR_CT_reg   (*((volatile unsigned int*) USB3_OVR_CT_reg))
#define USB3_OVR_CT_inst_adr                                                         "0x0030"
#define USB3_OVR_CT_inst                                                             0x0030
#define USB3_OVR_CT_phy3_lperiod_shift                                               (7)
#define USB3_OVR_CT_phy3_lperiod_mask                                                (0x00000380)
#define USB3_OVR_CT_phy3_lperiod(data)                                               (0x00000380&((data)<<7))
#define USB3_OVR_CT_phy3_lperiod_src(data)                                           ((0x00000380&(data))>>7)
#define USB3_OVR_CT_get_phy3_lperiod(data)                                           ((0x00000380&(data))>>7)
#define USB3_OVR_CT_phy3_hperiod_shift                                               (4)
#define USB3_OVR_CT_phy3_hperiod_mask                                                (0x00000070)
#define USB3_OVR_CT_phy3_hperiod(data)                                               (0x00000070&((data)<<4))
#define USB3_OVR_CT_phy3_hperiod_src(data)                                           ((0x00000070&(data))>>4)
#define USB3_OVR_CT_get_phy3_hperiod(data)                                           ((0x00000070&(data))>>4)
#define USB3_OVR_CT_phy3_last_shift                                                  (2)
#define USB3_OVR_CT_phy3_last_mask                                                   (0x0000000C)
#define USB3_OVR_CT_phy3_last(data)                                                  (0x0000000C&((data)<<2))
#define USB3_OVR_CT_phy3_last_src(data)                                              ((0x0000000C&(data))>>2)
#define USB3_OVR_CT_get_phy3_last(data)                                              ((0x0000000C&(data))>>2)
#define USB3_OVR_CT_host_ovr_current_value_shift                                     (1)
#define USB3_OVR_CT_host_ovr_current_value_mask                                      (0x00000002)
#define USB3_OVR_CT_host_ovr_current_value(data)                                     (0x00000002&((data)<<1))
#define USB3_OVR_CT_host_ovr_current_value_src(data)                                 ((0x00000002&(data))>>1)
#define USB3_OVR_CT_get_host_ovr_current_value(data)                                 ((0x00000002&(data))>>1)
#define USB3_OVR_CT_host_ovr_current_sel_shift                                       (0)
#define USB3_OVR_CT_host_ovr_current_sel_mask                                        (0x00000001)
#define USB3_OVR_CT_host_ovr_current_sel(data)                                       (0x00000001&((data)<<0))
#define USB3_OVR_CT_host_ovr_current_sel_src(data)                                   ((0x00000001&(data))>>0)
#define USB3_OVR_CT_get_host_ovr_current_sel(data)                                   ((0x00000001&(data))>>0)


#define ANA_PHY0                                                                     0x180130c4
#define ANA_PHY0_reg_addr                                                            "0xB80130C4"
#define ANA_PHY0_reg                                                                 0xB80130C4
#define set_ANA_PHY0_reg(data)   (*((volatile unsigned int*) ANA_PHY0_reg)=data)
#define get_ANA_PHY0_reg   (*((volatile unsigned int*) ANA_PHY0_reg))
#define ANA_PHY0_inst_adr                                                            "0x0031"
#define ANA_PHY0_inst                                                                0x0031
#define ANA_PHY0_usb3_mbias_en_p0_shift                                              (3)
#define ANA_PHY0_usb3_mbias_en_p0_mask                                               (0x00000008)
#define ANA_PHY0_usb3_mbias_en_p0(data)                                              (0x00000008&((data)<<3))
#define ANA_PHY0_usb3_mbias_en_p0_src(data)                                          ((0x00000008&(data))>>3)
#define ANA_PHY0_get_usb3_mbias_en_p0(data)                                          ((0x00000008&(data))>>3)
#define ANA_PHY0_usb3_bg_en_p0_shift                                                 (2)
#define ANA_PHY0_usb3_bg_en_p0_mask                                                  (0x00000004)
#define ANA_PHY0_usb3_bg_en_p0(data)                                                 (0x00000004&((data)<<2))
#define ANA_PHY0_usb3_bg_en_p0_src(data)                                             ((0x00000004&(data))>>2)
#define ANA_PHY0_get_usb3_bg_en_p0(data)                                             ((0x00000004&(data))>>2)
#define ANA_PHY0_usb3_pow_gating_p0_shift                                            (1)
#define ANA_PHY0_usb3_pow_gating_p0_mask                                             (0x00000002)
#define ANA_PHY0_usb3_pow_gating_p0(data)                                            (0x00000002&((data)<<1))
#define ANA_PHY0_usb3_pow_gating_p0_src(data)                                        ((0x00000002&(data))>>1)
#define ANA_PHY0_get_usb3_pow_gating_p0(data)                                        ((0x00000002&(data))>>1)
#define ANA_PHY0_usb3_isolate_p0_shift                                               (0)
#define ANA_PHY0_usb3_isolate_p0_mask                                                (0x00000001)
#define ANA_PHY0_usb3_isolate_p0(data)                                               (0x00000001&((data)<<0))
#define ANA_PHY0_usb3_isolate_p0_src(data)                                           ((0x00000001&(data))>>0)
#define ANA_PHY0_get_usb3_isolate_p0(data)                                           ((0x00000001&(data))>>0)


#define ANA_PHY1                                                                     0x180130c8
#define ANA_PHY1_reg_addr                                                            "0xB80130C8"
#define ANA_PHY1_reg                                                                 0xB80130C8
#define set_ANA_PHY1_reg(data)   (*((volatile unsigned int*) ANA_PHY1_reg)=data)
#define get_ANA_PHY1_reg   (*((volatile unsigned int*) ANA_PHY1_reg))
#define ANA_PHY1_inst_adr                                                            "0x0032"
#define ANA_PHY1_inst                                                                0x0032
#define ANA_PHY1_usb2_pow_gating_p3_shift                                            (3)
#define ANA_PHY1_usb2_pow_gating_p3_mask                                             (0x00000008)
#define ANA_PHY1_usb2_pow_gating_p3(data)                                            (0x00000008&((data)<<3))
#define ANA_PHY1_usb2_pow_gating_p3_src(data)                                        ((0x00000008&(data))>>3)
#define ANA_PHY1_get_usb2_pow_gating_p3(data)                                        ((0x00000008&(data))>>3)
#define ANA_PHY1_usb2_pow_gating_p2_shift                                            (2)
#define ANA_PHY1_usb2_pow_gating_p2_mask                                             (0x00000004)
#define ANA_PHY1_usb2_pow_gating_p2(data)                                            (0x00000004&((data)<<2))
#define ANA_PHY1_usb2_pow_gating_p2_src(data)                                        ((0x00000004&(data))>>2)
#define ANA_PHY1_get_usb2_pow_gating_p2(data)                                        ((0x00000004&(data))>>2)
#define ANA_PHY1_usb2_pow_gating_p1_shift                                            (1)
#define ANA_PHY1_usb2_pow_gating_p1_mask                                             (0x00000002)
#define ANA_PHY1_usb2_pow_gating_p1(data)                                            (0x00000002&((data)<<1))
#define ANA_PHY1_usb2_pow_gating_p1_src(data)                                        ((0x00000002&(data))>>1)
#define ANA_PHY1_get_usb2_pow_gating_p1(data)                                        ((0x00000002&(data))>>1)
#define ANA_PHY1_usb2_pow_gating_p0_shift                                            (0)
#define ANA_PHY1_usb2_pow_gating_p0_mask                                             (0x00000001)
#define ANA_PHY1_usb2_pow_gating_p0(data)                                            (0x00000001&((data)<<0))
#define ANA_PHY1_usb2_pow_gating_p0_src(data)                                        ((0x00000001&(data))>>0)
#define ANA_PHY1_get_usb2_pow_gating_p0(data)                                        ((0x00000001&(data))>>0)


#define GBL_USB_CT                                                                   0x180130cc
#define GBL_USB_CT_reg_addr                                                          "0xB80130CC"
#define GBL_USB_CT_reg                                                               0xB80130CC
#define set_GBL_USB_CT_reg(data)   (*((volatile unsigned int*) GBL_USB_CT_reg)=data)
#define get_GBL_USB_CT_reg   (*((volatile unsigned int*) GBL_USB_CT_reg))
#define GBL_USB_CT_inst_adr                                                          "0x0033"
#define GBL_USB_CT_inst                                                              0x0033
#define GBL_USB_CT_usb_mac_ctrl_shift                                                (0)
#define GBL_USB_CT_usb_mac_ctrl_mask                                                 (0xFFFFFFFF)
#define GBL_USB_CT_usb_mac_ctrl(data)                                                (0xFFFFFFFF&((data)<<0))
#define GBL_USB_CT_usb_mac_ctrl_src(data)                                            ((0xFFFFFFFF&(data))>>0)
#define GBL_USB_CT_get_usb_mac_ctrl(data)                                            ((0xFFFFFFFF&(data))>>0)


#define BIST0                                                                        0x18013100
#define BIST0_reg_addr                                                               "0xB8013100"
#define BIST0_reg                                                                    0xB8013100
#define set_BIST0_reg(data)   (*((volatile unsigned int*) BIST0_reg)=data)
#define get_BIST0_reg   (*((volatile unsigned int*) BIST0_reg))
#define BIST0_inst_adr                                                               "0x0040"
#define BIST0_inst                                                                   0x0040
#define BIST0_usb_bist_mode_host_ram_1_shift                                         (2)
#define BIST0_usb_bist_mode_host_ram_1_mask                                          (0x00000004)
#define BIST0_usb_bist_mode_host_ram_1(data)                                         (0x00000004&((data)<<2))
#define BIST0_usb_bist_mode_host_ram_1_src(data)                                     ((0x00000004&(data))>>2)
#define BIST0_get_usb_bist_mode_host_ram_1(data)                                     ((0x00000004&(data))>>2)
#define BIST0_usb_bist_mode_host_ram_2_shift                                         (1)
#define BIST0_usb_bist_mode_host_ram_2_mask                                          (0x00000002)
#define BIST0_usb_bist_mode_host_ram_2(data)                                         (0x00000002&((data)<<1))
#define BIST0_usb_bist_mode_host_ram_2_src(data)                                     ((0x00000002&(data))>>1)
#define BIST0_get_usb_bist_mode_host_ram_2(data)                                     ((0x00000002&(data))>>1)
#define BIST0_usb_bist_mode_wrap_shift                                               (0)
#define BIST0_usb_bist_mode_wrap_mask                                                (0x00000001)
#define BIST0_usb_bist_mode_wrap(data)                                               (0x00000001&((data)<<0))
#define BIST0_usb_bist_mode_wrap_src(data)                                           ((0x00000001&(data))>>0)
#define BIST0_get_usb_bist_mode_wrap(data)                                           ((0x00000001&(data))>>0)


#define BIST1                                                                        0x18013104
#define BIST1_reg_addr                                                               "0xB8013104"
#define BIST1_reg                                                                    0xB8013104
#define set_BIST1_reg(data)   (*((volatile unsigned int*) BIST1_reg)=data)
#define get_BIST1_reg   (*((volatile unsigned int*) BIST1_reg))
#define BIST1_inst_adr                                                               "0x0041"
#define BIST1_inst                                                                   0x0041
#define BIST1_usb_bist_done_host_ram_1_shift                                         (2)
#define BIST1_usb_bist_done_host_ram_1_mask                                          (0x00000004)
#define BIST1_usb_bist_done_host_ram_1(data)                                         (0x00000004&((data)<<2))
#define BIST1_usb_bist_done_host_ram_1_src(data)                                     ((0x00000004&(data))>>2)
#define BIST1_get_usb_bist_done_host_ram_1(data)                                     ((0x00000004&(data))>>2)
#define BIST1_usb_bist_done_host_ram_2_shift                                         (1)
#define BIST1_usb_bist_done_host_ram_2_mask                                          (0x00000002)
#define BIST1_usb_bist_done_host_ram_2(data)                                         (0x00000002&((data)<<1))
#define BIST1_usb_bist_done_host_ram_2_src(data)                                     ((0x00000002&(data))>>1)
#define BIST1_get_usb_bist_done_host_ram_2(data)                                     ((0x00000002&(data))>>1)
#define BIST1_usb_bist_done_wrap_shift                                               (0)
#define BIST1_usb_bist_done_wrap_mask                                                (0x00000001)
#define BIST1_usb_bist_done_wrap(data)                                               (0x00000001&((data)<<0))
#define BIST1_usb_bist_done_wrap_src(data)                                           ((0x00000001&(data))>>0)
#define BIST1_get_usb_bist_done_wrap(data)                                           ((0x00000001&(data))>>0)


#define BIST2                                                                        0x18013108
#define BIST2_reg_addr                                                               "0xB8013108"
#define BIST2_reg                                                                    0xB8013108
#define set_BIST2_reg(data)   (*((volatile unsigned int*) BIST2_reg)=data)
#define get_BIST2_reg   (*((volatile unsigned int*) BIST2_reg))
#define BIST2_inst_adr                                                               "0x0042"
#define BIST2_inst                                                                   0x0042
#define BIST2_usb_bist_fail_group_host_ram_1_shift                                   (2)
#define BIST2_usb_bist_fail_group_host_ram_1_mask                                    (0x00000004)
#define BIST2_usb_bist_fail_group_host_ram_1(data)                                   (0x00000004&((data)<<2))
#define BIST2_usb_bist_fail_group_host_ram_1_src(data)                               ((0x00000004&(data))>>2)
#define BIST2_get_usb_bist_fail_group_host_ram_1(data)                               ((0x00000004&(data))>>2)
#define BIST2_usb_bist_fail_group_host_ram_2_shift                                   (1)
#define BIST2_usb_bist_fail_group_host_ram_2_mask                                    (0x00000002)
#define BIST2_usb_bist_fail_group_host_ram_2(data)                                   (0x00000002&((data)<<1))
#define BIST2_usb_bist_fail_group_host_ram_2_src(data)                               ((0x00000002&(data))>>1)
#define BIST2_get_usb_bist_fail_group_host_ram_2(data)                               ((0x00000002&(data))>>1)
#define BIST2_usb_bist_fail_group_wrap_shift                                         (0)
#define BIST2_usb_bist_fail_group_wrap_mask                                          (0x00000001)
#define BIST2_usb_bist_fail_group_wrap(data)                                         (0x00000001&((data)<<0))
#define BIST2_usb_bist_fail_group_wrap_src(data)                                     ((0x00000001&(data))>>0)
#define BIST2_get_usb_bist_fail_group_wrap(data)                                     ((0x00000001&(data))>>0)


#define BIST3                                                                        0x1801310c
#define BIST3_reg_addr                                                               "0xB801310C"
#define BIST3_reg                                                                    0xB801310C
#define set_BIST3_reg(data)   (*((volatile unsigned int*) BIST3_reg)=data)
#define get_BIST3_reg   (*((volatile unsigned int*) BIST3_reg))
#define BIST3_inst_adr                                                               "0x0043"
#define BIST3_inst                                                                   0x0043
#define BIST3_usb_bist_host_ram_1_fail_3_shift                                       (3)
#define BIST3_usb_bist_host_ram_1_fail_3_mask                                        (0x00000008)
#define BIST3_usb_bist_host_ram_1_fail_3(data)                                       (0x00000008&((data)<<3))
#define BIST3_usb_bist_host_ram_1_fail_3_src(data)                                   ((0x00000008&(data))>>3)
#define BIST3_get_usb_bist_host_ram_1_fail_3(data)                                   ((0x00000008&(data))>>3)
#define BIST3_usb_bist_host_ram_1_fail_2_shift                                       (2)
#define BIST3_usb_bist_host_ram_1_fail_2_mask                                        (0x00000004)
#define BIST3_usb_bist_host_ram_1_fail_2(data)                                       (0x00000004&((data)<<2))
#define BIST3_usb_bist_host_ram_1_fail_2_src(data)                                   ((0x00000004&(data))>>2)
#define BIST3_get_usb_bist_host_ram_1_fail_2(data)                                   ((0x00000004&(data))>>2)
#define BIST3_usb_bist_host_ram_1_fail_1_shift                                       (1)
#define BIST3_usb_bist_host_ram_1_fail_1_mask                                        (0x00000002)
#define BIST3_usb_bist_host_ram_1_fail_1(data)                                       (0x00000002&((data)<<1))
#define BIST3_usb_bist_host_ram_1_fail_1_src(data)                                   ((0x00000002&(data))>>1)
#define BIST3_get_usb_bist_host_ram_1_fail_1(data)                                   ((0x00000002&(data))>>1)
#define BIST3_usb_bist_host_ram_1_fail_0_shift                                       (0)
#define BIST3_usb_bist_host_ram_1_fail_0_mask                                        (0x00000001)
#define BIST3_usb_bist_host_ram_1_fail_0(data)                                       (0x00000001&((data)<<0))
#define BIST3_usb_bist_host_ram_1_fail_0_src(data)                                   ((0x00000001&(data))>>0)
#define BIST3_get_usb_bist_host_ram_1_fail_0(data)                                   ((0x00000001&(data))>>0)


#define BIST4                                                                        0x18013110
#define BIST4_reg_addr                                                               "0xB8013110"
#define BIST4_reg                                                                    0xB8013110
#define set_BIST4_reg(data)   (*((volatile unsigned int*) BIST4_reg)=data)
#define get_BIST4_reg   (*((volatile unsigned int*) BIST4_reg))
#define BIST4_inst_adr                                                               "0x0044"
#define BIST4_inst                                                                   0x0044
#define BIST4_usb_bist_host_ram_2_fail_3_shift                                       (3)
#define BIST4_usb_bist_host_ram_2_fail_3_mask                                        (0x00000008)
#define BIST4_usb_bist_host_ram_2_fail_3(data)                                       (0x00000008&((data)<<3))
#define BIST4_usb_bist_host_ram_2_fail_3_src(data)                                   ((0x00000008&(data))>>3)
#define BIST4_get_usb_bist_host_ram_2_fail_3(data)                                   ((0x00000008&(data))>>3)
#define BIST4_usb_bist_host_ram_2_fail_2_shift                                       (2)
#define BIST4_usb_bist_host_ram_2_fail_2_mask                                        (0x00000004)
#define BIST4_usb_bist_host_ram_2_fail_2(data)                                       (0x00000004&((data)<<2))
#define BIST4_usb_bist_host_ram_2_fail_2_src(data)                                   ((0x00000004&(data))>>2)
#define BIST4_get_usb_bist_host_ram_2_fail_2(data)                                   ((0x00000004&(data))>>2)
#define BIST4_usb_bist_host_ram_2_fail_1_shift                                       (1)
#define BIST4_usb_bist_host_ram_2_fail_1_mask                                        (0x00000002)
#define BIST4_usb_bist_host_ram_2_fail_1(data)                                       (0x00000002&((data)<<1))
#define BIST4_usb_bist_host_ram_2_fail_1_src(data)                                   ((0x00000002&(data))>>1)
#define BIST4_get_usb_bist_host_ram_2_fail_1(data)                                   ((0x00000002&(data))>>1)
#define BIST4_usb_bist_host_ram_2_fail_0_shift                                       (0)
#define BIST4_usb_bist_host_ram_2_fail_0_mask                                        (0x00000001)
#define BIST4_usb_bist_host_ram_2_fail_0(data)                                       (0x00000001&((data)<<0))
#define BIST4_usb_bist_host_ram_2_fail_0_src(data)                                   ((0x00000001&(data))>>0)
#define BIST4_get_usb_bist_host_ram_2_fail_0(data)                                   ((0x00000001&(data))>>0)


#define BIST5                                                                        0x18013114
#define BIST5_reg_addr                                                               "0xB8013114"
#define BIST5_reg                                                                    0xB8013114
#define set_BIST5_reg(data)   (*((volatile unsigned int*) BIST5_reg)=data)
#define get_BIST5_reg   (*((volatile unsigned int*) BIST5_reg))
#define BIST5_inst_adr                                                               "0x0045"
#define BIST5_inst                                                                   0x0045
#define BIST5_usb_bist_wrap_fail_1_shift                                             (1)
#define BIST5_usb_bist_wrap_fail_1_mask                                              (0x00000002)
#define BIST5_usb_bist_wrap_fail_1(data)                                             (0x00000002&((data)<<1))
#define BIST5_usb_bist_wrap_fail_1_src(data)                                         ((0x00000002&(data))>>1)
#define BIST5_get_usb_bist_wrap_fail_1(data)                                         ((0x00000002&(data))>>1)
#define BIST5_usb_bist_wrap_fail_0_shift                                             (0)
#define BIST5_usb_bist_wrap_fail_0_mask                                              (0x00000001)
#define BIST5_usb_bist_wrap_fail_0(data)                                             (0x00000001&((data)<<0))
#define BIST5_usb_bist_wrap_fail_0_src(data)                                         ((0x00000001&(data))>>0)
#define BIST5_get_usb_bist_wrap_fail_0(data)                                         ((0x00000001&(data))>>0)


#define DRF0                                                                         0x18013118
#define DRF0_reg_addr                                                                "0xB8013118"
#define DRF0_reg                                                                     0xB8013118
#define set_DRF0_reg(data)   (*((volatile unsigned int*) DRF0_reg)=data)
#define get_DRF0_reg   (*((volatile unsigned int*) DRF0_reg))
#define DRF0_inst_adr                                                                "0x0046"
#define DRF0_inst                                                                    0x0046
#define DRF0_usb_drf_mode_host_ram_1_shift                                           (2)
#define DRF0_usb_drf_mode_host_ram_1_mask                                            (0x00000004)
#define DRF0_usb_drf_mode_host_ram_1(data)                                           (0x00000004&((data)<<2))
#define DRF0_usb_drf_mode_host_ram_1_src(data)                                       ((0x00000004&(data))>>2)
#define DRF0_get_usb_drf_mode_host_ram_1(data)                                       ((0x00000004&(data))>>2)
#define DRF0_usb_drf_mode_host_ram_2_shift                                           (1)
#define DRF0_usb_drf_mode_host_ram_2_mask                                            (0x00000002)
#define DRF0_usb_drf_mode_host_ram_2(data)                                           (0x00000002&((data)<<1))
#define DRF0_usb_drf_mode_host_ram_2_src(data)                                       ((0x00000002&(data))>>1)
#define DRF0_get_usb_drf_mode_host_ram_2(data)                                       ((0x00000002&(data))>>1)
#define DRF0_usb_drf_mode_wrap_shift                                                 (0)
#define DRF0_usb_drf_mode_wrap_mask                                                  (0x00000001)
#define DRF0_usb_drf_mode_wrap(data)                                                 (0x00000001&((data)<<0))
#define DRF0_usb_drf_mode_wrap_src(data)                                             ((0x00000001&(data))>>0)
#define DRF0_get_usb_drf_mode_wrap(data)                                             ((0x00000001&(data))>>0)


#define DRF1                                                                         0x1801311c
#define DRF1_reg_addr                                                                "0xB801311C"
#define DRF1_reg                                                                     0xB801311C
#define set_DRF1_reg(data)   (*((volatile unsigned int*) DRF1_reg)=data)
#define get_DRF1_reg   (*((volatile unsigned int*) DRF1_reg))
#define DRF1_inst_adr                                                                "0x0047"
#define DRF1_inst                                                                    0x0047
#define DRF1_usb_drf_resume_host_ram_1_shift                                         (2)
#define DRF1_usb_drf_resume_host_ram_1_mask                                          (0x00000004)
#define DRF1_usb_drf_resume_host_ram_1(data)                                         (0x00000004&((data)<<2))
#define DRF1_usb_drf_resume_host_ram_1_src(data)                                     ((0x00000004&(data))>>2)
#define DRF1_get_usb_drf_resume_host_ram_1(data)                                     ((0x00000004&(data))>>2)
#define DRF1_usb_drf_resume_host_ram_2_shift                                         (1)
#define DRF1_usb_drf_resume_host_ram_2_mask                                          (0x00000002)
#define DRF1_usb_drf_resume_host_ram_2(data)                                         (0x00000002&((data)<<1))
#define DRF1_usb_drf_resume_host_ram_2_src(data)                                     ((0x00000002&(data))>>1)
#define DRF1_get_usb_drf_resume_host_ram_2(data)                                     ((0x00000002&(data))>>1)
#define DRF1_usb_drf_resume_wrap_shift                                               (0)
#define DRF1_usb_drf_resume_wrap_mask                                                (0x00000001)
#define DRF1_usb_drf_resume_wrap(data)                                               (0x00000001&((data)<<0))
#define DRF1_usb_drf_resume_wrap_src(data)                                           ((0x00000001&(data))>>0)
#define DRF1_get_usb_drf_resume_wrap(data)                                           ((0x00000001&(data))>>0)


#define DRF2                                                                         0x18013120
#define DRF2_reg_addr                                                                "0xB8013120"
#define DRF2_reg                                                                     0xB8013120
#define set_DRF2_reg(data)   (*((volatile unsigned int*) DRF2_reg)=data)
#define get_DRF2_reg   (*((volatile unsigned int*) DRF2_reg))
#define DRF2_inst_adr                                                                "0x0048"
#define DRF2_inst                                                                    0x0048
#define DRF2_usb_drf_done_host_ram_1_shift                                           (2)
#define DRF2_usb_drf_done_host_ram_1_mask                                            (0x00000004)
#define DRF2_usb_drf_done_host_ram_1(data)                                           (0x00000004&((data)<<2))
#define DRF2_usb_drf_done_host_ram_1_src(data)                                       ((0x00000004&(data))>>2)
#define DRF2_get_usb_drf_done_host_ram_1(data)                                       ((0x00000004&(data))>>2)
#define DRF2_usb_drf_done_host_ram_2_shift                                           (1)
#define DRF2_usb_drf_done_host_ram_2_mask                                            (0x00000002)
#define DRF2_usb_drf_done_host_ram_2(data)                                           (0x00000002&((data)<<1))
#define DRF2_usb_drf_done_host_ram_2_src(data)                                       ((0x00000002&(data))>>1)
#define DRF2_get_usb_drf_done_host_ram_2(data)                                       ((0x00000002&(data))>>1)
#define DRF2_usb_drf_done_wrap_shift                                                 (0)
#define DRF2_usb_drf_done_wrap_mask                                                  (0x00000001)
#define DRF2_usb_drf_done_wrap(data)                                                 (0x00000001&((data)<<0))
#define DRF2_usb_drf_done_wrap_src(data)                                             ((0x00000001&(data))>>0)
#define DRF2_get_usb_drf_done_wrap(data)                                             ((0x00000001&(data))>>0)


#define DRF3                                                                         0x18013124
#define DRF3_reg_addr                                                                "0xB8013124"
#define DRF3_reg                                                                     0xB8013124
#define set_DRF3_reg(data)   (*((volatile unsigned int*) DRF3_reg)=data)
#define get_DRF3_reg   (*((volatile unsigned int*) DRF3_reg))
#define DRF3_inst_adr                                                                "0x0049"
#define DRF3_inst                                                                    0x0049
#define DRF3_usb_drf_pause_host_ram_1_shift                                          (2)
#define DRF3_usb_drf_pause_host_ram_1_mask                                           (0x00000004)
#define DRF3_usb_drf_pause_host_ram_1(data)                                          (0x00000004&((data)<<2))
#define DRF3_usb_drf_pause_host_ram_1_src(data)                                      ((0x00000004&(data))>>2)
#define DRF3_get_usb_drf_pause_host_ram_1(data)                                      ((0x00000004&(data))>>2)
#define DRF3_usb_drf_pause_host_ram_2_shift                                          (1)
#define DRF3_usb_drf_pause_host_ram_2_mask                                           (0x00000002)
#define DRF3_usb_drf_pause_host_ram_2(data)                                          (0x00000002&((data)<<1))
#define DRF3_usb_drf_pause_host_ram_2_src(data)                                      ((0x00000002&(data))>>1)
#define DRF3_get_usb_drf_pause_host_ram_2(data)                                      ((0x00000002&(data))>>1)
#define DRF3_usb_drf_pause_wrap_shift                                                (0)
#define DRF3_usb_drf_pause_wrap_mask                                                 (0x00000001)
#define DRF3_usb_drf_pause_wrap(data)                                                (0x00000001&((data)<<0))
#define DRF3_usb_drf_pause_wrap_src(data)                                            ((0x00000001&(data))>>0)
#define DRF3_get_usb_drf_pause_wrap(data)                                            ((0x00000001&(data))>>0)


#define DRF4                                                                         0x18013128
#define DRF4_reg_addr                                                                "0xB8013128"
#define DRF4_reg                                                                     0xB8013128
#define set_DRF4_reg(data)   (*((volatile unsigned int*) DRF4_reg)=data)
#define get_DRF4_reg   (*((volatile unsigned int*) DRF4_reg))
#define DRF4_inst_adr                                                                "0x004A"
#define DRF4_inst                                                                    0x004A
#define DRF4_usb_drf_fail_group_host_ram_1_shift                                     (2)
#define DRF4_usb_drf_fail_group_host_ram_1_mask                                      (0x00000004)
#define DRF4_usb_drf_fail_group_host_ram_1(data)                                     (0x00000004&((data)<<2))
#define DRF4_usb_drf_fail_group_host_ram_1_src(data)                                 ((0x00000004&(data))>>2)
#define DRF4_get_usb_drf_fail_group_host_ram_1(data)                                 ((0x00000004&(data))>>2)
#define DRF4_usb_drf_fail_group_host_ram_2_shift                                     (1)
#define DRF4_usb_drf_fail_group_host_ram_2_mask                                      (0x00000002)
#define DRF4_usb_drf_fail_group_host_ram_2(data)                                     (0x00000002&((data)<<1))
#define DRF4_usb_drf_fail_group_host_ram_2_src(data)                                 ((0x00000002&(data))>>1)
#define DRF4_get_usb_drf_fail_group_host_ram_2(data)                                 ((0x00000002&(data))>>1)
#define DRF4_usb_drf_fail_group_wrap_shift                                           (0)
#define DRF4_usb_drf_fail_group_wrap_mask                                            (0x00000001)
#define DRF4_usb_drf_fail_group_wrap(data)                                           (0x00000001&((data)<<0))
#define DRF4_usb_drf_fail_group_wrap_src(data)                                       ((0x00000001&(data))>>0)
#define DRF4_get_usb_drf_fail_group_wrap(data)                                       ((0x00000001&(data))>>0)


#define DRF5                                                                         0x1801312c
#define DRF5_reg_addr                                                                "0xB801312C"
#define DRF5_reg                                                                     0xB801312C
#define set_DRF5_reg(data)   (*((volatile unsigned int*) DRF5_reg)=data)
#define get_DRF5_reg   (*((volatile unsigned int*) DRF5_reg))
#define DRF5_inst_adr                                                                "0x004B"
#define DRF5_inst                                                                    0x004B
#define DRF5_usb_drf_host_ram_1_fail_3_shift                                         (3)
#define DRF5_usb_drf_host_ram_1_fail_3_mask                                          (0x00000008)
#define DRF5_usb_drf_host_ram_1_fail_3(data)                                         (0x00000008&((data)<<3))
#define DRF5_usb_drf_host_ram_1_fail_3_src(data)                                     ((0x00000008&(data))>>3)
#define DRF5_get_usb_drf_host_ram_1_fail_3(data)                                     ((0x00000008&(data))>>3)
#define DRF5_usb_drf_host_ram_1_fail_2_shift                                         (2)
#define DRF5_usb_drf_host_ram_1_fail_2_mask                                          (0x00000004)
#define DRF5_usb_drf_host_ram_1_fail_2(data)                                         (0x00000004&((data)<<2))
#define DRF5_usb_drf_host_ram_1_fail_2_src(data)                                     ((0x00000004&(data))>>2)
#define DRF5_get_usb_drf_host_ram_1_fail_2(data)                                     ((0x00000004&(data))>>2)
#define DRF5_usb_drf_host_ram_1_fail_1_shift                                         (1)
#define DRF5_usb_drf_host_ram_1_fail_1_mask                                          (0x00000002)
#define DRF5_usb_drf_host_ram_1_fail_1(data)                                         (0x00000002&((data)<<1))
#define DRF5_usb_drf_host_ram_1_fail_1_src(data)                                     ((0x00000002&(data))>>1)
#define DRF5_get_usb_drf_host_ram_1_fail_1(data)                                     ((0x00000002&(data))>>1)
#define DRF5_usb_drf_host_ram_1_fail_0_shift                                         (0)
#define DRF5_usb_drf_host_ram_1_fail_0_mask                                          (0x00000001)
#define DRF5_usb_drf_host_ram_1_fail_0(data)                                         (0x00000001&((data)<<0))
#define DRF5_usb_drf_host_ram_1_fail_0_src(data)                                     ((0x00000001&(data))>>0)
#define DRF5_get_usb_drf_host_ram_1_fail_0(data)                                     ((0x00000001&(data))>>0)


#define DRF6                                                                         0x18013130
#define DRF6_reg_addr                                                                "0xB8013130"
#define DRF6_reg                                                                     0xB8013130
#define set_DRF6_reg(data)   (*((volatile unsigned int*) DRF6_reg)=data)
#define get_DRF6_reg   (*((volatile unsigned int*) DRF6_reg))
#define DRF6_inst_adr                                                                "0x004C"
#define DRF6_inst                                                                    0x004C
#define DRF6_usb_drf_host_ram_2_fail_3_shift                                         (3)
#define DRF6_usb_drf_host_ram_2_fail_3_mask                                          (0x00000008)
#define DRF6_usb_drf_host_ram_2_fail_3(data)                                         (0x00000008&((data)<<3))
#define DRF6_usb_drf_host_ram_2_fail_3_src(data)                                     ((0x00000008&(data))>>3)
#define DRF6_get_usb_drf_host_ram_2_fail_3(data)                                     ((0x00000008&(data))>>3)
#define DRF6_usb_drf_host_ram_2_fail_2_shift                                         (2)
#define DRF6_usb_drf_host_ram_2_fail_2_mask                                          (0x00000004)
#define DRF6_usb_drf_host_ram_2_fail_2(data)                                         (0x00000004&((data)<<2))
#define DRF6_usb_drf_host_ram_2_fail_2_src(data)                                     ((0x00000004&(data))>>2)
#define DRF6_get_usb_drf_host_ram_2_fail_2(data)                                     ((0x00000004&(data))>>2)
#define DRF6_usb_drf_host_ram_2_fail_1_shift                                         (1)
#define DRF6_usb_drf_host_ram_2_fail_1_mask                                          (0x00000002)
#define DRF6_usb_drf_host_ram_2_fail_1(data)                                         (0x00000002&((data)<<1))
#define DRF6_usb_drf_host_ram_2_fail_1_src(data)                                     ((0x00000002&(data))>>1)
#define DRF6_get_usb_drf_host_ram_2_fail_1(data)                                     ((0x00000002&(data))>>1)
#define DRF6_usb_drf_host_ram_2_fail_0_shift                                         (0)
#define DRF6_usb_drf_host_ram_2_fail_0_mask                                          (0x00000001)
#define DRF6_usb_drf_host_ram_2_fail_0(data)                                         (0x00000001&((data)<<0))
#define DRF6_usb_drf_host_ram_2_fail_0_src(data)                                     ((0x00000001&(data))>>0)
#define DRF6_get_usb_drf_host_ram_2_fail_0(data)                                     ((0x00000001&(data))>>0)


#define DRF7                                                                         0x18013134
#define DRF7_reg_addr                                                                "0xB8013134"
#define DRF7_reg                                                                     0xB8013134
#define set_DRF7_reg(data)   (*((volatile unsigned int*) DRF7_reg)=data)
#define get_DRF7_reg   (*((volatile unsigned int*) DRF7_reg))
#define DRF7_inst_adr                                                                "0x004D"
#define DRF7_inst                                                                    0x004D
#define DRF7_usb_drf_wrap_fail_1_shift                                               (1)
#define DRF7_usb_drf_wrap_fail_1_mask                                                (0x00000002)
#define DRF7_usb_drf_wrap_fail_1(data)                                               (0x00000002&((data)<<1))
#define DRF7_usb_drf_wrap_fail_1_src(data)                                           ((0x00000002&(data))>>1)
#define DRF7_get_usb_drf_wrap_fail_1(data)                                           ((0x00000002&(data))>>1)
#define DRF7_usb_drf_wrap_fail_0_shift                                               (0)
#define DRF7_usb_drf_wrap_fail_0_mask                                                (0x00000001)
#define DRF7_usb_drf_wrap_fail_0(data)                                               (0x00000001&((data)<<0))
#define DRF7_usb_drf_wrap_fail_0_src(data)                                           ((0x00000001&(data))>>0)
#define DRF7_get_usb_drf_wrap_fail_0(data)                                           ((0x00000001&(data))>>0)


#define BIST_OP0                                                                     0x18013138
#define BIST_OP0_reg_addr                                                            "0xB8013138"
#define BIST_OP0_reg                                                                 0xB8013138
#define set_BIST_OP0_reg(data)   (*((volatile unsigned int*) BIST_OP0_reg)=data)
#define get_BIST_OP0_reg   (*((volatile unsigned int*) BIST_OP0_reg))
#define BIST_OP0_inst_adr                                                            "0x004E"
#define BIST_OP0_inst                                                                0x004E
#define BIST_OP0_usb_bist_wrap_ls1_shift                                             (11)
#define BIST_OP0_usb_bist_wrap_ls1_mask                                              (0x00000800)
#define BIST_OP0_usb_bist_wrap_ls1(data)                                             (0x00000800&((data)<<11))
#define BIST_OP0_usb_bist_wrap_ls1_src(data)                                         ((0x00000800&(data))>>11)
#define BIST_OP0_get_usb_bist_wrap_ls1(data)                                         ((0x00000800&(data))>>11)
#define BIST_OP0_usb_bist_wrap_rme1_shift                                            (10)
#define BIST_OP0_usb_bist_wrap_rme1_mask                                             (0x00000400)
#define BIST_OP0_usb_bist_wrap_rme1(data)                                            (0x00000400&((data)<<10))
#define BIST_OP0_usb_bist_wrap_rme1_src(data)                                        ((0x00000400&(data))>>10)
#define BIST_OP0_get_usb_bist_wrap_rme1(data)                                        ((0x00000400&(data))>>10)
#define BIST_OP0_usb_bist_wrap_rm1_shift                                             (6)
#define BIST_OP0_usb_bist_wrap_rm1_mask                                              (0x000003C0)
#define BIST_OP0_usb_bist_wrap_rm1(data)                                             (0x000003C0&((data)<<6))
#define BIST_OP0_usb_bist_wrap_rm1_src(data)                                         ((0x000003C0&(data))>>6)
#define BIST_OP0_get_usb_bist_wrap_rm1(data)                                         ((0x000003C0&(data))>>6)
#define BIST_OP0_usb_bist_wrap_ls0_shift                                             (5)
#define BIST_OP0_usb_bist_wrap_ls0_mask                                              (0x00000020)
#define BIST_OP0_usb_bist_wrap_ls0(data)                                             (0x00000020&((data)<<5))
#define BIST_OP0_usb_bist_wrap_ls0_src(data)                                         ((0x00000020&(data))>>5)
#define BIST_OP0_get_usb_bist_wrap_ls0(data)                                         ((0x00000020&(data))>>5)
#define BIST_OP0_usb_bist_wrap_rme0_shift                                            (4)
#define BIST_OP0_usb_bist_wrap_rme0_mask                                             (0x00000010)
#define BIST_OP0_usb_bist_wrap_rme0(data)                                            (0x00000010&((data)<<4))
#define BIST_OP0_usb_bist_wrap_rme0_src(data)                                        ((0x00000010&(data))>>4)
#define BIST_OP0_get_usb_bist_wrap_rme0(data)                                        ((0x00000010&(data))>>4)
#define BIST_OP0_usb_bist_wrap_rm0_shift                                             (0)
#define BIST_OP0_usb_bist_wrap_rm0_mask                                              (0x0000000F)
#define BIST_OP0_usb_bist_wrap_rm0(data)                                             (0x0000000F&((data)<<0))
#define BIST_OP0_usb_bist_wrap_rm0_src(data)                                         ((0x0000000F&(data))>>0)
#define BIST_OP0_get_usb_bist_wrap_rm0(data)                                         ((0x0000000F&(data))>>0)


#define BIST_OP1                                                                     0x1801313c
#define BIST_OP1_reg_addr                                                            "0xB801313C"
#define BIST_OP1_reg                                                                 0xB801313C
#define set_BIST_OP1_reg(data)   (*((volatile unsigned int*) BIST_OP1_reg)=data)
#define get_BIST_OP1_reg   (*((volatile unsigned int*) BIST_OP1_reg))
#define BIST_OP1_inst_adr                                                            "0x004F"
#define BIST_OP1_inst                                                                0x004F
#define BIST_OP1_usb_usb_host_ram_1_ls3_shift                                        (23)
#define BIST_OP1_usb_usb_host_ram_1_ls3_mask                                         (0x00800000)
#define BIST_OP1_usb_usb_host_ram_1_ls3(data)                                        (0x00800000&((data)<<23))
#define BIST_OP1_usb_usb_host_ram_1_ls3_src(data)                                    ((0x00800000&(data))>>23)
#define BIST_OP1_get_usb_usb_host_ram_1_ls3(data)                                    ((0x00800000&(data))>>23)
#define BIST_OP1_usb_usb_host_ram_1_rme3_shift                                       (22)
#define BIST_OP1_usb_usb_host_ram_1_rme3_mask                                        (0x00400000)
#define BIST_OP1_usb_usb_host_ram_1_rme3(data)                                       (0x00400000&((data)<<22))
#define BIST_OP1_usb_usb_host_ram_1_rme3_src(data)                                   ((0x00400000&(data))>>22)
#define BIST_OP1_get_usb_usb_host_ram_1_rme3(data)                                   ((0x00400000&(data))>>22)
#define BIST_OP1_usb_usb_host_ram_1_rm3_shift                                        (18)
#define BIST_OP1_usb_usb_host_ram_1_rm3_mask                                         (0x003C0000)
#define BIST_OP1_usb_usb_host_ram_1_rm3(data)                                        (0x003C0000&((data)<<18))
#define BIST_OP1_usb_usb_host_ram_1_rm3_src(data)                                    ((0x003C0000&(data))>>18)
#define BIST_OP1_get_usb_usb_host_ram_1_rm3(data)                                    ((0x003C0000&(data))>>18)
#define BIST_OP1_usb_usb_host_ram_1_ls2_shift                                        (17)
#define BIST_OP1_usb_usb_host_ram_1_ls2_mask                                         (0x00020000)
#define BIST_OP1_usb_usb_host_ram_1_ls2(data)                                        (0x00020000&((data)<<17))
#define BIST_OP1_usb_usb_host_ram_1_ls2_src(data)                                    ((0x00020000&(data))>>17)
#define BIST_OP1_get_usb_usb_host_ram_1_ls2(data)                                    ((0x00020000&(data))>>17)
#define BIST_OP1_usb_usb_host_ram_1_rme2_shift                                       (16)
#define BIST_OP1_usb_usb_host_ram_1_rme2_mask                                        (0x00010000)
#define BIST_OP1_usb_usb_host_ram_1_rme2(data)                                       (0x00010000&((data)<<16))
#define BIST_OP1_usb_usb_host_ram_1_rme2_src(data)                                   ((0x00010000&(data))>>16)
#define BIST_OP1_get_usb_usb_host_ram_1_rme2(data)                                   ((0x00010000&(data))>>16)
#define BIST_OP1_usb_usb_host_ram_1_rm2_shift                                        (12)
#define BIST_OP1_usb_usb_host_ram_1_rm2_mask                                         (0x0000F000)
#define BIST_OP1_usb_usb_host_ram_1_rm2(data)                                        (0x0000F000&((data)<<12))
#define BIST_OP1_usb_usb_host_ram_1_rm2_src(data)                                    ((0x0000F000&(data))>>12)
#define BIST_OP1_get_usb_usb_host_ram_1_rm2(data)                                    ((0x0000F000&(data))>>12)
#define BIST_OP1_usb_usb_host_ram_1_ls1_shift                                        (11)
#define BIST_OP1_usb_usb_host_ram_1_ls1_mask                                         (0x00000800)
#define BIST_OP1_usb_usb_host_ram_1_ls1(data)                                        (0x00000800&((data)<<11))
#define BIST_OP1_usb_usb_host_ram_1_ls1_src(data)                                    ((0x00000800&(data))>>11)
#define BIST_OP1_get_usb_usb_host_ram_1_ls1(data)                                    ((0x00000800&(data))>>11)
#define BIST_OP1_usb_usb_host_ram_1_rme1_shift                                       (10)
#define BIST_OP1_usb_usb_host_ram_1_rme1_mask                                        (0x00000400)
#define BIST_OP1_usb_usb_host_ram_1_rme1(data)                                       (0x00000400&((data)<<10))
#define BIST_OP1_usb_usb_host_ram_1_rme1_src(data)                                   ((0x00000400&(data))>>10)
#define BIST_OP1_get_usb_usb_host_ram_1_rme1(data)                                   ((0x00000400&(data))>>10)
#define BIST_OP1_usb_usb_host_ram_1_rm1_shift                                        (6)
#define BIST_OP1_usb_usb_host_ram_1_rm1_mask                                         (0x000003C0)
#define BIST_OP1_usb_usb_host_ram_1_rm1(data)                                        (0x000003C0&((data)<<6))
#define BIST_OP1_usb_usb_host_ram_1_rm1_src(data)                                    ((0x000003C0&(data))>>6)
#define BIST_OP1_get_usb_usb_host_ram_1_rm1(data)                                    ((0x000003C0&(data))>>6)
#define BIST_OP1_usb_usb_host_ram_1_ls0_shift                                        (5)
#define BIST_OP1_usb_usb_host_ram_1_ls0_mask                                         (0x00000020)
#define BIST_OP1_usb_usb_host_ram_1_ls0(data)                                        (0x00000020&((data)<<5))
#define BIST_OP1_usb_usb_host_ram_1_ls0_src(data)                                    ((0x00000020&(data))>>5)
#define BIST_OP1_get_usb_usb_host_ram_1_ls0(data)                                    ((0x00000020&(data))>>5)
#define BIST_OP1_usb_usb_host_ram_1_rme0_shift                                       (4)
#define BIST_OP1_usb_usb_host_ram_1_rme0_mask                                        (0x00000010)
#define BIST_OP1_usb_usb_host_ram_1_rme0(data)                                       (0x00000010&((data)<<4))
#define BIST_OP1_usb_usb_host_ram_1_rme0_src(data)                                   ((0x00000010&(data))>>4)
#define BIST_OP1_get_usb_usb_host_ram_1_rme0(data)                                   ((0x00000010&(data))>>4)
#define BIST_OP1_usb_usb_host_ram_1_rm0_shift                                        (0)
#define BIST_OP1_usb_usb_host_ram_1_rm0_mask                                         (0x0000000F)
#define BIST_OP1_usb_usb_host_ram_1_rm0(data)                                        (0x0000000F&((data)<<0))
#define BIST_OP1_usb_usb_host_ram_1_rm0_src(data)                                    ((0x0000000F&(data))>>0)
#define BIST_OP1_get_usb_usb_host_ram_1_rm0(data)                                    ((0x0000000F&(data))>>0)


#define BIST_OP2                                                                     0x18013140
#define BIST_OP2_reg_addr                                                            "0xB8013140"
#define BIST_OP2_reg                                                                 0xB8013140
#define set_BIST_OP2_reg(data)   (*((volatile unsigned int*) BIST_OP2_reg)=data)
#define get_BIST_OP2_reg   (*((volatile unsigned int*) BIST_OP2_reg))
#define BIST_OP2_inst_adr                                                            "0x0050"
#define BIST_OP2_inst                                                                0x0050
#define BIST_OP2_usb_usb_host_ram_2_ls3_shift                                        (23)
#define BIST_OP2_usb_usb_host_ram_2_ls3_mask                                         (0x00800000)
#define BIST_OP2_usb_usb_host_ram_2_ls3(data)                                        (0x00800000&((data)<<23))
#define BIST_OP2_usb_usb_host_ram_2_ls3_src(data)                                    ((0x00800000&(data))>>23)
#define BIST_OP2_get_usb_usb_host_ram_2_ls3(data)                                    ((0x00800000&(data))>>23)
#define BIST_OP2_usb_usb_host_ram_2_rme3_shift                                       (22)
#define BIST_OP2_usb_usb_host_ram_2_rme3_mask                                        (0x00400000)
#define BIST_OP2_usb_usb_host_ram_2_rme3(data)                                       (0x00400000&((data)<<22))
#define BIST_OP2_usb_usb_host_ram_2_rme3_src(data)                                   ((0x00400000&(data))>>22)
#define BIST_OP2_get_usb_usb_host_ram_2_rme3(data)                                   ((0x00400000&(data))>>22)
#define BIST_OP2_usb_usb_host_ram_2_rm3_shift                                        (18)
#define BIST_OP2_usb_usb_host_ram_2_rm3_mask                                         (0x003C0000)
#define BIST_OP2_usb_usb_host_ram_2_rm3(data)                                        (0x003C0000&((data)<<18))
#define BIST_OP2_usb_usb_host_ram_2_rm3_src(data)                                    ((0x003C0000&(data))>>18)
#define BIST_OP2_get_usb_usb_host_ram_2_rm3(data)                                    ((0x003C0000&(data))>>18)
#define BIST_OP2_usb_usb_host_ram_2_ls2_shift                                        (17)
#define BIST_OP2_usb_usb_host_ram_2_ls2_mask                                         (0x00020000)
#define BIST_OP2_usb_usb_host_ram_2_ls2(data)                                        (0x00020000&((data)<<17))
#define BIST_OP2_usb_usb_host_ram_2_ls2_src(data)                                    ((0x00020000&(data))>>17)
#define BIST_OP2_get_usb_usb_host_ram_2_ls2(data)                                    ((0x00020000&(data))>>17)
#define BIST_OP2_usb_usb_host_ram_2_rme2_shift                                       (16)
#define BIST_OP2_usb_usb_host_ram_2_rme2_mask                                        (0x00010000)
#define BIST_OP2_usb_usb_host_ram_2_rme2(data)                                       (0x00010000&((data)<<16))
#define BIST_OP2_usb_usb_host_ram_2_rme2_src(data)                                   ((0x00010000&(data))>>16)
#define BIST_OP2_get_usb_usb_host_ram_2_rme2(data)                                   ((0x00010000&(data))>>16)
#define BIST_OP2_usb_usb_host_ram_2_rm2_shift                                        (12)
#define BIST_OP2_usb_usb_host_ram_2_rm2_mask                                         (0x0000F000)
#define BIST_OP2_usb_usb_host_ram_2_rm2(data)                                        (0x0000F000&((data)<<12))
#define BIST_OP2_usb_usb_host_ram_2_rm2_src(data)                                    ((0x0000F000&(data))>>12)
#define BIST_OP2_get_usb_usb_host_ram_2_rm2(data)                                    ((0x0000F000&(data))>>12)
#define BIST_OP2_usb_usb_host_ram_2_ls1_shift                                        (11)
#define BIST_OP2_usb_usb_host_ram_2_ls1_mask                                         (0x00000800)
#define BIST_OP2_usb_usb_host_ram_2_ls1(data)                                        (0x00000800&((data)<<11))
#define BIST_OP2_usb_usb_host_ram_2_ls1_src(data)                                    ((0x00000800&(data))>>11)
#define BIST_OP2_get_usb_usb_host_ram_2_ls1(data)                                    ((0x00000800&(data))>>11)
#define BIST_OP2_usb_usb_host_ram_2_rme1_shift                                       (10)
#define BIST_OP2_usb_usb_host_ram_2_rme1_mask                                        (0x00000400)
#define BIST_OP2_usb_usb_host_ram_2_rme1(data)                                       (0x00000400&((data)<<10))
#define BIST_OP2_usb_usb_host_ram_2_rme1_src(data)                                   ((0x00000400&(data))>>10)
#define BIST_OP2_get_usb_usb_host_ram_2_rme1(data)                                   ((0x00000400&(data))>>10)
#define BIST_OP2_usb_usb_host_ram_2_rm1_shift                                        (6)
#define BIST_OP2_usb_usb_host_ram_2_rm1_mask                                         (0x000003C0)
#define BIST_OP2_usb_usb_host_ram_2_rm1(data)                                        (0x000003C0&((data)<<6))
#define BIST_OP2_usb_usb_host_ram_2_rm1_src(data)                                    ((0x000003C0&(data))>>6)
#define BIST_OP2_get_usb_usb_host_ram_2_rm1(data)                                    ((0x000003C0&(data))>>6)
#define BIST_OP2_usb_usb_host_ram_2_ls0_shift                                        (5)
#define BIST_OP2_usb_usb_host_ram_2_ls0_mask                                         (0x00000020)
#define BIST_OP2_usb_usb_host_ram_2_ls0(data)                                        (0x00000020&((data)<<5))
#define BIST_OP2_usb_usb_host_ram_2_ls0_src(data)                                    ((0x00000020&(data))>>5)
#define BIST_OP2_get_usb_usb_host_ram_2_ls0(data)                                    ((0x00000020&(data))>>5)
#define BIST_OP2_usb_usb_host_ram_2_rme0_shift                                       (4)
#define BIST_OP2_usb_usb_host_ram_2_rme0_mask                                        (0x00000010)
#define BIST_OP2_usb_usb_host_ram_2_rme0(data)                                       (0x00000010&((data)<<4))
#define BIST_OP2_usb_usb_host_ram_2_rme0_src(data)                                   ((0x00000010&(data))>>4)
#define BIST_OP2_get_usb_usb_host_ram_2_rme0(data)                                   ((0x00000010&(data))>>4)
#define BIST_OP2_usb_usb_host_ram_2_rm0_shift                                        (0)
#define BIST_OP2_usb_usb_host_ram_2_rm0_mask                                         (0x0000000F)
#define BIST_OP2_usb_usb_host_ram_2_rm0(data)                                        (0x0000000F&((data)<<0))
#define BIST_OP2_usb_usb_host_ram_2_rm0_src(data)                                    ((0x0000000F&(data))>>0)
#define BIST_OP2_get_usb_usb_host_ram_2_rm0(data)                                    ((0x0000000F&(data))>>0)


#endif
