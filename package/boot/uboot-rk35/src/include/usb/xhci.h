/*
 * USB HOST XHCI Controller
 *
 * Based on xHCI host controller driver in linux-kernel
 * by Sarah Sharp.
 *
 * Copyright (C) 2008 Intel Corp.
 * Author: Sarah Sharp
 *
 * Copyright (C) 2013 Samsung Electronics Co.Ltd
 * Authors: Vivek Gautam <gautam.vivek@samsung.com>
 *	    Vikas Sajjan <vikas.sajjan@samsung.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef HOST_XHCI_H_
#define HOST_XHCI_H_

#include <asm/types.h>
#include <asm/cache.h>
#include <asm/io.h>
#include <linux/list.h>
#include <linux/compat.h>

#define MAX_EP_CTX_NUM		31
#define XHCI_ALIGNMENT		64
/* Generic timeout for XHCI events */
#define XHCI_TIMEOUT		5000
/* Max number of USB devices for any host controller - limit in section 6.1 */
#define MAX_HC_SLOTS            256
/* Section 5.3.3 - MaxPorts */
#define MAX_HC_PORTS            255

/* Up to 16 ms to halt an HC */
#define XHCI_MAX_HALT_USEC	(16*1000)

#define XHCI_MAX_RESET_USEC	(250*1000)

/*
 * These bits are Read Only (RO) and should be saved and written to the
 * registers: 0, 3, 10:13, 30
 * connect status, over-current status, port speed, and device removable.
 * connect status and port speed are also sticky - meaning they're in
 * the AUX well and they aren't changed by a hot, warm, or cold reset.
 */
#define XHCI_PORT_RO ((1 << 0) | (1 << 3) | (0xf << 10) | (1 << 30))
/*
 * These bits are RW; writing a 0 clears the bit, writing a 1 sets the bit:
 * bits 5:8, 9, 14:15, 25:27
 * link state, port power, port indicator state, "wake on" enable state
 */
#define XHCI_PORT_RWS ((0xf << 5) | (1 << 9) | (0x3 << 14) | (0x7 << 25))
/*
 * These bits are RW; writing a 1 sets the bit, writing a 0 has no effect:
 * bit 4 (port reset)
 */
#define XHCI_PORT_RW1S ((1 << 4))
/*
 * These bits are RW; writing a 1 clears the bit, writing a 0 has no effect:
 * bits 1, 17, 18, 19, 20, 21, 22, 23
 * port enable/disable, and
 * change bits: connect, PED,
 * warm port reset changed (reserved zero for USB 2.0 ports),
 * over-current, reset, link state, and L1 change
 */
#define XHCI_PORT_RW1CS ((1 << 1) | (0x7f << 17))
/*
 * Bit 16 is RW, and writing a '1' to it causes the link state control to be
 * latched in
 */
#define XHCI_PORT_RW ((1 << 16))
/*
 * These bits are Reserved Zero (RsvdZ) and zero should be written to them:
 * bits 2, 24, 28:31
 */
#define XHCI_PORT_RZ ((1 << 2) | (1 << 24) | (0xf << 28))

/*
 * XHCI Register Space.
 */
struct xhci_hccr {
	uint32_t cr_capbase;
	uint32_t cr_hcsparams1;
	uint32_t cr_hcsparams2;
	uint32_t cr_hcsparams3;
	uint32_t cr_hccparams;
	uint32_t cr_dboff;
	uint32_t cr_rtsoff;

/* hc_capbase bitmasks */
/* bits 7:0 - how long is the Capabilities register */
#define HC_LENGTH(p)		XHCI_HC_LENGTH(p)
/* bits 31:16	*/
#define HC_VERSION(p)		(((p) >> 16) & 0xffff)

/* HCSPARAMS1 - hcs_params1 - bitmasks */
/* bits 0:7, Max Device Slots */
#define HCS_MAX_SLOTS(p)	(((p) >> 0) & 0xff)
#define HCS_SLOTS_MASK		0xff
/* bits 8:18, Max Interrupters */
#define HCS_MAX_INTRS(p)	(((p) >> 8) & 0x7ff)
/* bits 24:31, Max Ports - max value is 0x7F = 127 ports */
#define HCS_MAX_PORTS_SHIFT	24
#define HCS_MAX_PORTS_MASK	(0xff << HCS_MAX_PORTS_SHIFT)
#define HCS_MAX_PORTS(p)	(((p) >> 24) & 0xff)

/* HCSPARAMS2 - hcs_params2 - bitmasks */
/* bits 0:3, frames or uframes that SW needs to queue transactions
 * ahead of the HW to meet periodic deadlines */
#define HCS_IST(p)		(((p) >> 0) & 0xf)
/* bits 4:7, max number of Event Ring segments */
#define HCS_ERST_MAX(p)		(((p) >> 4) & 0xf)
/* bits 21:25 Hi 5 bits of Scratchpad buffers SW must allocate for the HW */
/* bit 26 Scratchpad restore - for save/restore HW state - not used yet */
/* bits 27:31 Lo 5 bits of Scratchpad buffers SW must allocate for the HW */
#define HCS_MAX_SCRATCHPAD(p)	((((p) >> 16) & 0x3e0) | (((p) >> 27) & 0x1f))

/* HCSPARAMS3 - hcs_params3 - bitmasks */
/* bits 0:7, Max U1 to U0 latency for the roothub ports */
#define HCS_U1_LATENCY(p)	(((p) >> 0) & 0xff)
/* bits 16:31, Max U2 to U0 latency for the roothub ports */
#define HCS_U2_LATENCY(p)	(((p) >> 16) & 0xffff)

/* HCCPARAMS - hcc_params - bitmasks */
/* true: HC can use 64-bit address pointers */
#define HCC_64BIT_ADDR(p)	((p) & (1 << 0))
/* true: HC can do bandwidth negotiation */
#define HCC_BANDWIDTH_NEG(p)	((p) & (1 << 1))
/* true: HC uses 64-byte Device Context structures
 * FIXME 64-byte context structures aren't supported yet.
 */
#define HCC_64BYTE_CONTEXT(p)	((p) & (1 << 2))
/* true: HC has port power switches */
#define HCC_PPC(p)		((p) & (1 << 3))
/* true: HC has port indicators */
#define HCS_INDICATOR(p)	((p) & (1 << 4))
/* true: HC has Light HC Reset Capability */
#define HCC_LIGHT_RESET(p)	((p) & (1 << 5))
/* true: HC supports latency tolerance messaging */
#define HCC_LTC(p)		((p) & (1 << 6))
/* true: no secondary Stream ID Support */
#define HCC_NSS(p)		((p) & (1 << 7))
/* Max size for Primary Stream Arrays - 2^(n+1), where n is bits 12:15 */
#define HCC_MAX_PSA(p)		(1 << ((((p) >> 12) & 0xf) + 1))
/* Extended Capabilities pointer from PCI base - section 5.3.6 */
#define HCC_EXT_CAPS(p)		XHCI_HCC_EXT_CAPS(p)

/* db_off bitmask - bits 0:1 reserved */
#define	DBOFF_MASK	(~0x3)

/* run_regs_off bitmask - bits 0:4 reserved */
#define	RTSOFF_MASK	(~0x1f)

};

struct xhci_hcor_port_regs {
	volatile uint32_t or_portsc;
	volatile uint32_t or_portpmsc;
	volatile uint32_t or_portli;
	volatile uint32_t reserved_3;
};

struct xhci_hcor {
	volatile uint32_t or_usbcmd;
	volatile uint32_t or_usbsts;
	volatile uint32_t or_pagesize;
	volatile uint32_t reserved_0[2];
	volatile uint32_t or_dnctrl;
	volatile uint64_t or_crcr;
	volatile uint32_t reserved_1[4];
	volatile uint64_t or_dcbaap;
	volatile uint32_t or_config;
	volatile uint32_t reserved_2[241];
	struct xhci_hcor_port_regs portregs[MAX_HC_PORTS];
};

/* USBCMD - USB command - command bitmasks */
/* start/stop HC execution - do not write unless HC is halted*/
#define CMD_RUN		XHCI_CMD_RUN
/* Reset HC - resets internal HC state machine and all registers (except
 * PCI config regs).  HC does NOT drive a USB reset on the downstream ports.
 * The xHCI driver must reinitialize the xHC after setting this bit.
 */
#define CMD_RESET	(1 << 1)
/* Event Interrupt Enable - a '1' allows interrupts from the host controller */
#define CMD_EIE		XHCI_CMD_EIE
/* Host System Error Interrupt Enable - get out-of-band signal for HC errors */
#define CMD_HSEIE	XHCI_CMD_HSEIE
/* bits 4:6 are reserved (and should be preserved on writes). */
/* light reset (port status stays unchanged) - reset completed when this is 0 */
#define CMD_LRESET	(1 << 7)
/* host controller save/restore state. */
#define CMD_CSS		(1 << 8)
#define CMD_CRS		(1 << 9)
/* Enable Wrap Event - '1' means xHC generates an event when MFINDEX wraps. */
#define CMD_EWE		XHCI_CMD_EWE
/* MFINDEX power management - '1' means xHC can stop MFINDEX counter if all root
 * hubs are in U3 (selective suspend), disconnect, disabled, or powered-off.
 * '0' means the xHC can power it off if all ports are in the disconnect,
 * disabled, or powered-off state.
 */
#define CMD_PM_INDEX	(1 << 11)
/* bits 12:31 are reserved (and should be preserved on writes). */

/* USBSTS - USB status - status bitmasks */
/* HC not running - set to 1 when run/stop bit is cleared. */
#define STS_HALT	XHCI_STS_HALT
/* serious error, e.g. PCI parity error.  The HC will clear the run/stop bit. */
#define STS_FATAL	(1 << 2)
/* event interrupt - clear this prior to clearing any IP flags in IR set*/
#define STS_EINT	(1 << 3)
/* port change detect */
#define STS_PORT	(1 << 4)
/* bits 5:7 reserved and zeroed */
/* save state status - '1' means xHC is saving state */
#define STS_SAVE	(1 << 8)
/* restore state status - '1' means xHC is restoring state */
#define STS_RESTORE	(1 << 9)
/* true: save or restore error */
#define STS_SRE		(1 << 10)
/* true: Controller Not Ready to accept doorbell or op reg writes after reset */
#define STS_CNR		XHCI_STS_CNR
/* true: internal Host Controller Error - SW needs to reset and reinitialize */
#define STS_HCE		(1 << 12)
/* bits 13:31 reserved and should be preserved */

/*
 * DNCTRL - Device Notification Control Register - dev_notification bitmasks
 * Generate a device notification event when the HC sees a transaction with a
 * notification type that matches a bit set in this bit field.
 */
#define	DEV_NOTE_MASK		(0xffff)
#define ENABLE_DEV_NOTE(x)	(1 << (x))
/* Most of the device notification types should only be used for debug.
 * SW does need to pay attention to function wake notifications.
 */
#define	DEV_NOTE_FWAKE		ENABLE_DEV_NOTE(1)

/* CRCR - Command Ring Control Register - cmd_ring bitmasks */
/* bit 0 is the command ring cycle state */
/* stop ring operation after completion of the currently executing command */
#define CMD_RING_PAUSE		(1 << 1)
/* stop ring immediately - abort the currently executing command */
#define CMD_RING_ABORT		(1 << 2)
/* true: command ring is running */
#define CMD_RING_RUNNING	(1 << 3)
/* bits 4:5 reserved and should be preserved */
/* Command Ring pointer - bit mask for the lower 32 bits. */
#define CMD_RING_RSVD_BITS	(0x3f)

/* CONFIG - Configure Register - config_reg bitmasks */
/* bits 0:7 - maximum number of device slots enabled (NumSlotsEn) */
#define MAX_DEVS(p)	((p) & 0xff)
/* bits 8:31 - reserved and should be preserved */

/* PORTSC - Port Status and Control Register - port_status_base bitmasks */
/* true: device connected */
#define PORT_CONNECT	(1 << 0)
/* true: port enabled */
#define PORT_PE		(1 << 1)
/* bit 2 reserved and zeroed */
/* true: port has an over-current condition */
#define PORT_OC		(1 << 3)
/* true: port reset signaling asserted */
#define PORT_RESET	(1 << 4)
/* Port Link State - bits 5:8
 * A read gives the current link PM state of the port,
 * a write with Link State Write Strobe set sets the link state.
 */
#define PORT_PLS_MASK	(0xf << 5)
#define XDEV_U0		(0x0 << 5)
#define XDEV_U2		(0x2 << 5)
#define XDEV_U3		(0x3 << 5)
#define XDEV_RESUME	(0xf << 5)
/* true: port has power (see HCC_PPC) */
#define PORT_POWER	(1 << 9)
/* bits 10:13 indicate device speed:
 * 0 - undefined speed - port hasn't be initialized by a reset yet
 * 1 - full speed
 * 2 - low speed
 * 3 - high speed
 * 4 - super speed
 * 5-15 reserved
 */
#define DEV_SPEED_MASK		(0xf << 10)
#define	XDEV_FS			(0x1 << 10)
#define	XDEV_LS			(0x2 << 10)
#define	XDEV_HS			(0x3 << 10)
#define	XDEV_SS			(0x4 << 10)
#define DEV_UNDEFSPEED(p)	(((p) & DEV_SPEED_MASK) == (0x0<<10))
#define DEV_FULLSPEED(p)	(((p) & DEV_SPEED_MASK) == XDEV_FS)
#define DEV_LOWSPEED(p)		(((p) & DEV_SPEED_MASK) == XDEV_LS)
#define DEV_HIGHSPEED(p)	(((p) & DEV_SPEED_MASK) == XDEV_HS)
#define DEV_SUPERSPEED(p)	(((p) & DEV_SPEED_MASK) == XDEV_SS)
/* Bits 20:23 in the Slot Context are the speed for the device */
#define	SLOT_SPEED_FS		(XDEV_FS << 10)
#define	SLOT_SPEED_LS		(XDEV_LS << 10)
#define	SLOT_SPEED_HS		(XDEV_HS << 10)
#define	SLOT_SPEED_SS		(XDEV_SS << 10)
/* Port Indicator Control */
#define PORT_LED_OFF	(0 << 14)
#define PORT_LED_AMBER	(1 << 14)
#define PORT_LED_GREEN	(2 << 14)
#define PORT_LED_MASK	(3 << 14)
/* Port Link State Write Strobe - set this when changing link state */
#define PORT_LINK_STROBE	(1 << 16)
/* true: connect status change */
#define PORT_CSC	(1 << 17)
/* true: port enable change */
#define PORT_PEC	(1 << 18)
/* true: warm reset for a USB 3.0 device is done.  A "hot" reset puts the port
 * into an enabled state, and the device into the default state.  A "warm" reset
 * also resets the link, forcing the device through the link training sequence.
 * SW can also look at the Port Reset register to see when warm reset is done.
 */
#define PORT_WRC	(1 << 19)
/* true: over-current change */
#define PORT_OCC	(1 << 20)
/* true: reset change - 1 to 0 transition of PORT_RESET */
#define PORT_RC		(1 << 21)
/* port link status change - set on some port link state transitions:
 *  Transition				Reason
 *  --------------------------------------------------------------------------
 *  - U3 to Resume		Wakeup signaling from a device
 *  - Resume to Recovery to U0	USB 3.0 device resume
 *  - Resume to U0		USB 2.0 device resume
 *  - U3 to Recovery to U0	Software resume of USB 3.0 device complete
 *  - U3 to U0			Software resume of USB 2.0 device complete
 *  - U2 to U0			L1 resume of USB 2.1 device complete
 *  - U0 to U0 (???)		L1 entry rejection by USB 2.1 device
 *  - U0 to disabled		L1 entry error with USB 2.1 device
 *  - Any state to inactive	Error on USB 3.0 port
 */
#define PORT_PLC	(1 << 22)
/* port configure error change - port failed to configure its link partner */
#define PORT_CEC	(1 << 23)
/* bit 24 reserved */
/* wake on connect (enable) */
#define PORT_WKCONN_E	(1 << 25)
/* wake on disconnect (enable) */
#define PORT_WKDISC_E	(1 << 26)
/* wake on over-current (enable) */
#define PORT_WKOC_E	(1 << 27)
/* bits 28:29 reserved */
/* true: device is removable - for USB 3.0 roothub emulation */
#define PORT_DEV_REMOVE	(1 << 30)
/* Initiate a warm port reset - complete when PORT_WRC is '1' */
#define PORT_WR		(1 << 31)

/* We mark duplicate entries with -1 */
#define DUPLICATE_ENTRY ((u8)(-1))

/* Port Power Management Status and Control - port_power_base bitmasks */
/* Inactivity timer value for transitions into U1, in microseconds.
 * Timeout can be up to 127us.  0xFF means an infinite timeout.
 */
#define PORT_U1_TIMEOUT(p)	((p) & 0xff)
/* Inactivity timer value for transitions into U2 */
#define PORT_U2_TIMEOUT(p)	(((p) & 0xff) << 8)
/* Bits 24:31 for port testing */

/* USB2 Protocol PORTSPMSC */
#define	PORT_L1S_MASK		7
#define	PORT_L1S_SUCCESS	1
#define	PORT_RWE		(1 << 3)
#define	PORT_HIRD(p)		(((p) & 0xf) << 4)
#define	PORT_HIRD_MASK		(0xf << 4)
#define	PORT_L1DS(p)		(((p) & 0xff) << 8)
#define	PORT_HLE		(1 << 16)

/**
* struct xhci_intr_reg - Interrupt Register Set
* @irq_pending:	IMAN - Interrupt Management Register.  Used to enable
*			interrupts and check for pending interrupts.
* @irq_control:	IMOD - Interrupt Moderation Register.
*			Used to throttle interrupts.
* @erst_size:		Number of segments in the
			Event Ring Segment Table (ERST).
* @erst_base:		ERST base address.
* @erst_dequeue:	Event ring dequeue pointer.
*
* Each interrupter (defined by a MSI-X vector) has an event ring and an Event
* Ring Segment Table (ERST) associated with it.
* The event ring is comprised of  multiple segments of the same size.
* The HC places events on the ring and  "updates the Cycle bit in the TRBs to
* indicate to software the current  position of the Enqueue Pointer."
* The HCD (Linux) processes those events and  updates the dequeue pointer.
*/
struct xhci_intr_reg {
	volatile __le32	irq_pending;
	volatile __le32	irq_control;
	volatile __le32	erst_size;
	volatile __le32	rsvd;
	volatile __le64	erst_base;
	volatile __le64	erst_dequeue;
};

/* irq_pending bitmasks */
#define	ER_IRQ_PENDING(p)	((p) & 0x1)
/* bits 2:31 need to be preserved */
/* THIS IS BUGGY - FIXME - IP IS WRITE 1 TO CLEAR */
#define	ER_IRQ_CLEAR(p)		((p) & 0xfffffffe)
#define	ER_IRQ_ENABLE(p)	((ER_IRQ_CLEAR(p)) | 0x2)
#define	ER_IRQ_DISABLE(p)	((ER_IRQ_CLEAR(p)) & ~(0x2))

/* irq_control bitmasks */
/* Minimum interval between interrupts (in 250ns intervals).  The interval
 * between interrupts will be longer if there are no events on the event ring.
 * Default is 4000 (1 ms).
 */
#define ER_IRQ_INTERVAL_MASK	(0xffff)
/* Counter used to count down the time to the next interrupt - HW use only */
#define ER_IRQ_COUNTER_MASK	(0xffff << 16)

/* erst_size bitmasks */
/* Preserve bits 16:31 of erst_size */
#define	ERST_SIZE_MASK		(0xffff << 16)

/* erst_dequeue bitmasks */
/* Dequeue ERST Segment Index (DESI) - Segment number (or alias)
 * where the current dequeue pointer lies.  This is an optional HW hint.
 */
#define ERST_DESI_MASK		(0x7)
/* Event Handler Busy (EHB) - is the event ring scheduled to be serviced by
 * a work queue (or delayed service routine)?
 */
#define ERST_EHB		(1 << 3)
#define ERST_PTR_MASK		(0xf)

/**
 * struct xhci_run_regs
 * @microframe_index:	MFINDEX - current microframe number
 *
 * Section 5.5 Host Controller Runtime Registers:
 * "Software should read and write these registers using only Dword (32 bit)
 * or larger accesses"
 */
struct xhci_run_regs {
	__le32			microframe_index;
	__le32			rsvd[7];
	struct xhci_intr_reg	ir_set[128];
};

/**
 * struct doorbell_array
 *
 * Bits  0 -  7: Endpoint target
 * Bits  8 - 15: RsvdZ
 * Bits 16 - 31: Stream ID
 *
 * Section 5.6
 */
struct xhci_doorbell_array {
	volatile __le32	doorbell[256];
};

#define DB_VALUE(ep, stream)	((((ep) + 1) & 0xff) | ((stream) << 16))
#define DB_VALUE_HOST		0x00000000

/**
 * struct xhci_protocol_caps
 * @revision:		major revision, minor revision, capability ID,
 *			and next capability pointer.
 * @name_string:	Four ASCII characters to say which spec this xHC
 *			follows, typically "USB ".
 * @port_info:		Port offset, count, and protocol-defined information.
 */
struct xhci_protocol_caps {
	u32	revision;
	u32	name_string;
	u32	port_info;
};

#define	XHCI_EXT_PORT_MAJOR(x)	(((x) >> 24) & 0xff)
#define	XHCI_EXT_PORT_OFF(x)	((x) & 0xff)
#define	XHCI_EXT_PORT_COUNT(x)	(((x) >> 8) & 0xff)

/**
 * struct xhci_container_ctx
 * @type: Type of context.  Used to calculated offsets to contained contexts.
 * @size: Size of the context data
 * @bytes: The raw context data given to HW
 *
 * Represents either a Device or Input context.  Holds a pointer to the raw
 * memory used for the context (bytes).
 */
struct xhci_container_ctx {
	unsigned type;
#define XHCI_CTX_TYPE_DEVICE  0x1
#define XHCI_CTX_TYPE_INPUT   0x2

	int size;
	u8 *bytes;
};

/**
 * struct xhci_slot_ctx
 * @dev_info:	Route string, device speed, hub info, and last valid endpoint
 * @dev_info2:	Max exit latency for device number, root hub port number
 * @tt_info:	tt_info is used to construct split transaction tokens
 * @dev_state:	slot state and device address
 *
 * Slot Context - section 6.2.1.1.  This assumes the HC uses 32-byte context
 * structures.  If the HC uses 64-byte contexts, there is an additional 32 bytes
 * reserved at the end of the slot context for HC internal use.
 */
struct xhci_slot_ctx {
	__le32	dev_info;
	__le32	dev_info2;
	__le32	tt_info;
	__le32	dev_state;
	/* offset 0x10 to 0x1f reserved for HC internal use */
	__le32	reserved[4];
};

/* dev_info bitmasks */
/* Route String - 0:19 */
#define ROUTE_STRING_MASK	(0xfffff)
/* Device speed - values defined by PORTSC Device Speed field - 20:23 */
#define DEV_SPEED		(0xf << 20)
/* bit 24 reserved */
/* Is this LS/FS device connected through a HS hub? - bit 25 */
#define DEV_MTT			(0x1 << 25)
/* Set if the device is a hub - bit 26 */
#define DEV_HUB			(0x1 << 26)
/* Index of the last valid endpoint context in this device context - 27:31 */
#define LAST_CTX_MASK		(0x1f << 27)
#define LAST_CTX(p)		((p) << 27)
#define LAST_CTX_TO_EP_NUM(p)	(((p) >> 27) - 1)
#define SLOT_FLAG		(1 << 0)
#define EP0_FLAG		(1 << 1)

/* dev_info2 bitmasks */
/* Max Exit Latency (ms) - worst case time to wake up all links in dev path */
#define MAX_EXIT			(0xffff)
/* Root hub port number that is needed to access the USB device */
#define ROOT_HUB_PORT(p)		(((p) & 0xff) << 16)
#define ROOT_HUB_PORT_MASK		(0xff)
#define ROOT_HUB_PORT_SHIFT		(16)
#define DEVINFO_TO_ROOT_HUB_PORT(p)	(((p) >> 16) & 0xff)
/* Maximum number of ports under a hub device */
#define XHCI_MAX_PORTS(p)		(((p) & 0xff) << 24)

/* tt_info bitmasks */
/*
 * TT Hub Slot ID - for low or full speed devices attached to a high-speed hub
 * The Slot ID of the hub that isolates the high speed signaling from
 * this low or full-speed device.  '0' if attached to root hub port.
 */
#define TT_SLOT(p)		(((p) & 0xff) << 0)
/*
 * The number of the downstream facing port of the high-speed hub
 * '0' if the device is not low or full speed.
 */
#define TT_PORT(p)		(((p) & 0xff) << 8)
#define TT_THINK_TIME(p)	(((p) & 0x3) << 16)

/* dev_state bitmasks */
/* USB device address - assigned by the HC */
#define DEV_ADDR_MASK	(0xff)
/* bits 8:26 reserved */
/* Slot state */
#define SLOT_STATE		(0x1f << 27)
#define GET_SLOT_STATE(p)	(((p) & (0x1f << 27)) >> 27)

#define SLOT_STATE_DISABLED	0
#define SLOT_STATE_ENABLED	SLOT_STATE_DISABLED
#define SLOT_STATE_DEFAULT	1
#define SLOT_STATE_ADDRESSED	2
#define SLOT_STATE_CONFIGURED	3

/**
 * struct xhci_ep_ctx
 * @ep_info:	endpoint state, streams, mult, and interval information.
 * @ep_info2:	information on endpoint type, max packet size, max burst size,
 *		error count, and whether the HC will force an event for all
 *		transactions.
 * @deq:	64-bit ring dequeue pointer address.  If the endpoint only
 *		defines one stream, this points to the endpoint transfer ring.
 *		Otherwise, it points to a stream context array, which has a
 *		ring pointer for each flow.
 * @tx_info:
 *		Average TRB lengths for the endpoint ring and
 *		max payload within an Endpoint Service Interval Time (ESIT).
 *
 * Endpoint Context - section 6.2.1.2.This assumes the HC uses 32-byte context
 * structures.If the HC uses 64-byte contexts, there is an additional 32 bytes
 * reserved at the end of the endpoint context for HC internal use.
 */
struct xhci_ep_ctx {
	__le32	ep_info;
	__le32	ep_info2;
	__le64	deq;
	__le32	tx_info;
	/* offset 0x14 - 0x1f reserved for HC internal use */
	__le32	reserved[3];
};

/* ep_info bitmasks */
/*
 * Endpoint State - bits 0:2
 * 0 - disabled
 * 1 - running
 * 2 - halted due to halt condition - ok to manipulate endpoint ring
 * 3 - stopped
 * 4 - TRB error
 * 5-7 - reserved
 */
#define EP_STATE_MASK		(0xf)
#define EP_STATE_DISABLED	0
#define EP_STATE_RUNNING	1
#define EP_STATE_HALTED		2
#define EP_STATE_STOPPED	3
#define EP_STATE_ERROR		4
/* Mult - Max number of burtst within an interval, in EP companion desc. */
#define EP_MULT(p)		(((p) & 0x3) << 8)
#define CTX_TO_EP_MULT(p)	(((p) >> 8) & 0x3)
/* bits 10:14 are Max Primary Streams */
/* bit 15 is Linear Stream Array */
/* Interval - period between requests to an endpoint - 125u increments. */
#define EP_INTERVAL(p)			(((p) & 0xff) << 16)
#define EP_INTERVAL_TO_UFRAMES(p)	(1 << (((p) >> 16) & 0xff))
#define CTX_TO_EP_INTERVAL(p)		(((p) >> 16) & 0xff)
#define EP_MAXPSTREAMS_MASK		(0x1f << 10)
#define EP_MAXPSTREAMS(p)		(((p) << 10) & EP_MAXPSTREAMS_MASK)
/* Endpoint is set up with a Linear Stream Array (vs. Secondary Stream Array) */
#define	EP_HAS_LSA			(1 << 15)

/* ep_info2 bitmasks */
/*
 * Force Event - generate transfer events for all TRBs for this endpoint
 * This will tell the HC to ignore the IOC and ISP flags (for debugging only).
 */
#define	FORCE_EVENT		(0x1)
#define ERROR_COUNT(p)		(((p) & 0x3) << 1)
#define ERROR_COUNT_SHIFT	(1)
#define ERROR_COUNT_MASK	(0x3)
#define CTX_TO_EP_TYPE(p)	(((p) >> 3) & 0x7)
#define EP_TYPE(p)		((p) << 3)
#define EP_TYPE_SHIFT		(3)
#define ISOC_OUT_EP		1
#define BULK_OUT_EP		2
#define INT_OUT_EP		3
#define CTRL_EP			4
#define ISOC_IN_EP		5
#define BULK_IN_EP		6
#define INT_IN_EP		7
/* bit 6 reserved */
/* bit 7 is Host Initiate Disable - for disabling stream selection */
#define MAX_BURST(p)		(((p)&0xff) << 8)
#define MAX_BURST_MASK		(0xff)
#define MAX_BURST_SHIFT		(8)
#define CTX_TO_MAX_BURST(p)	(((p) >> 8) & 0xff)
#define MAX_PACKET(p)		(((p)&0xffff) << 16)
#define MAX_PACKET_MASK		(0xffff)
#define MAX_PACKET_DECODED(p)	(((p) >> 16) & 0xffff)
#define MAX_PACKET_SHIFT	(16)

/* Get max packet size from ep desc. Bit 10..0 specify the max packet size.
 * USB2.0 spec 9.6.6.
 */
#define GET_MAX_PACKET(p)	((p) & 0x7ff)

/* tx_info bitmasks */
#define EP_AVG_TRB_LENGTH(p)		((p) & 0xffff)
#define EP_MAX_ESIT_PAYLOAD_LO(p)	(((p) & 0xffff) << 16)
#define EP_MAX_ESIT_PAYLOAD_HI(p)	((((p) >> 16) & 0xff) << 24)
#define CTX_TO_MAX_ESIT_PAYLOAD(p)	(((p) >> 16) & 0xffff)

/* deq bitmasks */
#define EP_CTX_CYCLE_MASK		(1 << 0)


/**
 * struct xhci_input_control_context
 * Input control context; see section 6.2.5.
 *
 * @drop_context:	set the bit of the endpoint context you want to disable
 * @add_context:	set the bit of the endpoint context you want to enable
 */
struct xhci_input_control_ctx {
	volatile __le32	drop_flags;
	volatile __le32	add_flags;
	__le32	rsvd2[6];
};


/**
 * struct xhci_device_context_array
 * @dev_context_ptr	array of 64-bit DMA addresses for device contexts
 */
struct xhci_device_context_array {
	/* 64-bit device addresses; we only write 32-bit addresses */
	__le64			dev_context_ptrs[MAX_HC_SLOTS];
};
/* TODO: write function to set the 64-bit device DMA address */
/*
 * TODO: change this to be dynamically sized at HC mem init time since the HC
 * might not be able to handle the maximum number of devices possible.
 */


struct xhci_transfer_event {
	/* 64-bit buffer address, or immediate data */
	__le64	buffer;
	__le32	transfer_len;
	/* This field is interpreted differently based on the type of TRB */
	volatile __le32	flags;
};

/* Transfer event TRB length bit mask */
/* bits 0:23 */
#define EVENT_TRB_LEN(p)	((p) & 0xffffff)

/** Transfer Event bit fields **/
#define	TRB_TO_EP_ID(p)		(((p) >> 16) & 0x1f)

/* Completion Code - only applicable for some types of TRBs */
#define	COMP_CODE_MASK		(0xff << 24)
#define	COMP_CODE_SHIFT		(24)
#define GET_COMP_CODE(p)	(((p) & COMP_CODE_MASK) >> 24)

typedef enum {
	COMP_SUCCESS = 1,
	/* Data Buffer Error */
	COMP_DB_ERR, /* 2 */
	/* Babble Detected Error */
	COMP_BABBLE, /* 3 */
	/* USB Transaction Error */
	COMP_TX_ERR, /* 4 */
	/* TRB Error - some TRB field is invalid */
	COMP_TRB_ERR, /* 5 */
	/* Stall Error - USB device is stalled */
	COMP_STALL, /* 6 */
	/* Resource Error - HC doesn't have memory for that device configuration */
	COMP_ENOMEM, /* 7 */
	/* Bandwidth Error - not enough room in schedule for this dev config */
	COMP_BW_ERR, /* 8 */
	/* No Slots Available Error - HC ran out of device slots */
	COMP_ENOSLOTS, /* 9 */
	/* Invalid Stream Type Error */
	COMP_STREAM_ERR, /* 10 */
	/* Slot Not Enabled Error - doorbell rung for disabled device slot */
	COMP_EBADSLT, /* 11 */
	/* Endpoint Not Enabled Error */
	COMP_EBADEP,/* 12 */
	/* Short Packet */
	COMP_SHORT_TX, /* 13 */
	/* Ring Underrun - doorbell rung for an empty isoc OUT ep ring */
	COMP_UNDERRUN, /* 14 */
	/* Ring Overrun - isoc IN ep ring is empty when ep is scheduled to RX */
	COMP_OVERRUN, /* 15 */
	/* Virtual Function Event Ring Full Error */
	COMP_VF_FULL, /* 16 */
	/* Parameter Error - Context parameter is invalid */
	COMP_EINVAL, /* 17 */
	/* Bandwidth Overrun Error - isoc ep exceeded its allocated bandwidth */
	COMP_BW_OVER,/* 18 */
	/* Context State Error - illegal context state transition requested */
	COMP_CTX_STATE,/* 19 */
	/* No Ping Response Error - HC didn't get PING_RESPONSE in time to TX */
	COMP_PING_ERR,/* 20 */
	/* Event Ring is full */
	COMP_ER_FULL,/* 21 */
	/* Incompatible Device Error */
	COMP_DEV_ERR,/* 22 */
	/* Missed Service Error - HC couldn't service an isoc ep within interval */
	COMP_MISSED_INT,/* 23 */
	/* Successfully stopped command ring */
	COMP_CMD_STOP, /* 24 */
	/* Successfully aborted current command and stopped command ring */
	COMP_CMD_ABORT, /* 25 */
	/* Stopped - transfer was terminated by a stop endpoint command */
	COMP_STOP,/* 26 */
	/* Same as COMP_EP_STOPPED, but the transferred length in the event
	 * is invalid */
	COMP_STOP_INVAL, /* 27*/
	/* Control Abort Error - Debug Capability - control pipe aborted */
	COMP_DBG_ABORT, /* 28 */
	/* Max Exit Latency Too Large Error */
	COMP_MEL_ERR,/* 29 */
	/* TRB type 30 reserved */
	/* Isoc Buffer Overrun - an isoc IN ep sent more data than could fit in TD */
	COMP_BUFF_OVER = 31,
	/* Event Lost Error - xHC has an "internal event overrun condition" */
	COMP_ISSUES, /* 32 */
	/* Undefined Error - reported when other error codes don't apply */
	COMP_UNKNOWN, /* 33 */
	/* Invalid Stream ID Error */
	COMP_STRID_ERR, /* 34 */
	/* Secondary Bandwidth Error - may be returned by a Configure Endpoint cmd */
	COMP_2ND_BW_ERR, /* 35 */
	/* Split Transaction Error */
	COMP_SPLIT_ERR /* 36 */

} xhci_comp_code;

struct xhci_link_trb {
	/* 64-bit segment pointer*/
	volatile __le64 segment_ptr;
	volatile __le32 intr_target;
	volatile __le32 control;
};

/* control bitfields */
#define LINK_TOGGLE (0x1 << 1)

/* Command completion event TRB */
struct xhci_event_cmd {
	/* Pointer to command TRB, or the value passed by the event data trb */
	volatile __le64 cmd_trb;
	volatile __le32 status;
	volatile __le32 flags;
};

/* flags bitmasks */
/* bits 16:23 are the virtual function ID */
/* bits 24:31 are the slot ID */
#define	TRB_TO_SLOT_ID(p)		(((p) & (0xff << 24)) >> 24)
#define	TRB_TO_SLOT_ID_SHIFT		(24)
#define	TRB_TO_SLOT_ID_MASK		(0xff << TRB_TO_SLOT_ID_SHIFT)
#define	SLOT_ID_FOR_TRB(p)		(((p) & 0xff) << 24)
#define	SLOT_ID_FOR_TRB_MASK		(0xff)
#define	SLOT_ID_FOR_TRB_SHIFT		(24)

/* Stop Endpoint TRB - ep_index to endpoint ID for this TRB */
#define TRB_TO_EP_INDEX(p)		((((p) & (0x1f << 16)) >> 16) - 1)
#define	EP_ID_FOR_TRB(p)		((((p) + 1) & 0x1f) << 16)

#define SUSPEND_PORT_FOR_TRB(p)		(((p) & 1) << 23)
#define TRB_TO_SUSPEND_PORT(p)		(((p) & (1 << 23)) >> 23)
#define LAST_EP_INDEX			30

/* Set TR Dequeue Pointer command TRB fields */
#define TRB_TO_STREAM_ID(p)		((((p) & (0xffff << 16)) >> 16))
#define STREAM_ID_FOR_TRB(p)		((((p)) & 0xffff) << 16)


/* Port Status Change Event TRB fields */
/* Port ID - bits 31:24 */
#define GET_PORT_ID(p)			(((p) & (0xff << 24)) >> 24)
#define	PORT_ID_SHIFT			(24)
#define	PORT_ID_MASK			(0xff << PORT_ID_SHIFT)

/* Normal TRB fields */
/* transfer_len bitmasks - bits 0:16 */
#define	TRB_LEN(p)			((p) & 0x1ffff)
#define	TRB_LEN_MASK			(0x1ffff)
/* Interrupter Target - which MSI-X vector to target the completion event at */
#define	TRB_INTR_TARGET_SHIFT		(22)
#define	TRB_INTR_TARGET_MASK		(0x3ff)
#define TRB_INTR_TARGET(p)		(((p) & 0x3ff) << 22)
#define GET_INTR_TARGET(p)		(((p) >> 22) & 0x3ff)
#define TRB_TBC(p)			(((p) & 0x3) << 7)
#define TRB_TLBPC(p)			(((p) & 0xf) << 16)

/* Cycle bit - indicates TRB ownership by HC or HCD */
#define TRB_CYCLE		(1<<0)
/*
 * Force next event data TRB to be evaluated before task switch.
 * Used to pass OS data back after a TD completes.
 */
#define TRB_ENT			(1<<1)
/* Interrupt on short packet */
#define TRB_ISP			(1<<2)
/* Set PCIe no snoop attribute */
#define TRB_NO_SNOOP		(1<<3)
/* Chain multiple TRBs into a TD */
#define TRB_CHAIN		(1<<4)
/* Interrupt on completion */
#define TRB_IOC			(1<<5)
/* The buffer pointer contains immediate data */
#define TRB_IDT			(1<<6)

/* Block Event Interrupt */
#define	TRB_BEI			(1<<9)

/* Control transfer TRB specific fields */
#define TRB_DIR_IN		(1<<16)
#define	TRB_TX_TYPE(p)		((p) << 16)
#define	TRB_TX_TYPE_SHIFT	(16)
#define	TRB_DATA_OUT		2
#define	TRB_DATA_IN		3

/* Isochronous TRB specific fields */
#define TRB_SIA			(1 << 31)

struct xhci_generic_trb {
	volatile __le32 field[4];
};

union xhci_trb {
	struct xhci_link_trb		link;
	struct xhci_transfer_event	trans_event;
	struct xhci_event_cmd		event_cmd;
	struct xhci_generic_trb		generic;
};

/* TRB bit mask */
#define	TRB_TYPE_BITMASK	(0xfc00)
#define TRB_TYPE(p)		((p) << 10)
#define TRB_TYPE_SHIFT		(10)
#define TRB_FIELD_TO_TYPE(p)	(((p) & TRB_TYPE_BITMASK) >> 10)

/* TRB type IDs */
typedef enum {
	/* bulk, interrupt, isoc scatter/gather, and control data stage */
	TRB_NORMAL = 1,
	/* setup stage for control transfers */
	TRB_SETUP, /* 2 */
	/* data stage for control transfers */
	TRB_DATA, /* 3 */
	/* status stage for control transfers */
	TRB_STATUS, /* 4 */
	/* isoc transfers */
	TRB_ISOC, /* 5 */
	/* TRB for linking ring segments */
	TRB_LINK, /* 6 */
	/* TRB for EVENT DATA */
	TRB_EVENT_DATA, /* 7 */
	/* Transfer Ring No-op (not for the command ring) */
	TRB_TR_NOOP, /* 8 */
	/* Command TRBs */
	/* Enable Slot Command */
	TRB_ENABLE_SLOT, /* 9 */
	/* Disable Slot Command */
	TRB_DISABLE_SLOT, /* 10 */
	/* Address Device Command */
	TRB_ADDR_DEV, /* 11 */
	/* Configure Endpoint Command */
	TRB_CONFIG_EP, /* 12 */
	/* Evaluate Context Command */
	TRB_EVAL_CONTEXT, /* 13 */
	/* Reset Endpoint Command */
	TRB_RESET_EP, /* 14 */
	/* Stop Transfer Ring Command */
	TRB_STOP_RING, /* 15 */
	/* Set Transfer Ring Dequeue Pointer Command */
	TRB_SET_DEQ, /* 16 */
	/* Reset Device Command */
	TRB_RESET_DEV, /* 17 */
	/* Force Event Command (opt) */
	TRB_FORCE_EVENT, /* 18 */
	/* Negotiate Bandwidth Command (opt) */
	TRB_NEG_BANDWIDTH, /* 19 */
	/* Set Latency Tolerance Value Command (opt) */
	TRB_SET_LT, /* 20 */
	/* Get port bandwidth Command */
	TRB_GET_BW, /* 21 */
	/* Force Header Command - generate a transaction or link management packet */
	TRB_FORCE_HEADER, /* 22 */
	/* No-op Command - not for transfer rings */
	TRB_CMD_NOOP, /* 23 */
	/* TRB IDs 24-31 reserved */
	/* Event TRBS */
	/* Transfer Event */
	TRB_TRANSFER = 32,
	/* Command Completion Event */
	TRB_COMPLETION, /* 33 */
	/* Port Status Change Event */
	TRB_PORT_STATUS, /* 34 */
	/* Bandwidth Request Event (opt) */
	TRB_BANDWIDTH_EVENT, /* 35 */
	/* Doorbell Event (opt) */
	TRB_DOORBELL, /* 36 */
	/* Host Controller Event */
	TRB_HC_EVENT, /* 37 */
	/* Device Notification Event - device sent function wake notification */
	TRB_DEV_NOTE, /* 38 */
	/* MFINDEX Wrap Event - microframe counter wrapped */
	TRB_MFINDEX_WRAP, /* 39 */
	/* TRB IDs 40-47 reserved, 48-63 is vendor-defined */
	/* Nec vendor-specific command completion event. */
	TRB_NEC_CMD_COMP = 48, /* 48 */
	/* Get NEC firmware revision. */
	TRB_NEC_GET_FW, /* 49 */
} trb_type;

#define TRB_TYPE_LINK(x)	(((x) & TRB_TYPE_BITMASK) == TRB_TYPE(TRB_LINK))
/* Above, but for __le32 types -- can avoid work by swapping constants: */
#define TRB_TYPE_LINK_LE32(x)	(((x) & cpu_to_le32(TRB_TYPE_BITMASK)) == \
				 cpu_to_le32(TRB_TYPE(TRB_LINK)))
#define TRB_TYPE_NOOP_LE32(x)	(((x) & cpu_to_le32(TRB_TYPE_BITMASK)) == \
				 cpu_to_le32(TRB_TYPE(TRB_TR_NOOP)))

/*
 * TRBS_PER_SEGMENT must be a multiple of 4,
 * since the command ring is 64-byte aligned.
 * It must also be greater than 16.
 */
#define TRBS_PER_SEGMENT	64
/* Allow two commands + a link TRB, along with any reserved command TRBs */
#define MAX_RSVD_CMD_TRBS	(TRBS_PER_SEGMENT - 3)
#define SEGMENT_SIZE		(TRBS_PER_SEGMENT*16)
/* SEGMENT_SHIFT should be log2(SEGMENT_SIZE).
 * Change this if you change TRBS_PER_SEGMENT!
 */
#define SEGMENT_SHIFT		10
/* TRB buffer pointers can't cross 64KB boundaries */
#define TRB_MAX_BUFF_SHIFT	16
#define TRB_MAX_BUFF_SIZE	(1 << TRB_MAX_BUFF_SHIFT)

struct xhci_segment {
	union xhci_trb		*trbs;
	/* private to HCD */
	struct xhci_segment	*next;
};

struct xhci_ring {
	struct xhci_segment	*first_seg;
	union  xhci_trb		*enqueue;
	struct xhci_segment	*enq_seg;
	union  xhci_trb		*dequeue;
	struct xhci_segment	*deq_seg;
	/*
	 * Write the cycle state into the TRB cycle field to give ownership of
	 * the TRB to the host controller (if we are the producer), or to check
	 * if we own the TRB (if we are the consumer).  See section 4.9.1.
	 */
	volatile u32		cycle_state;
	unsigned int		num_segs;
};

struct xhci_erst_entry {
	/* 64-bit event ring segment address */
	__le64	seg_addr;
	__le32	seg_size;
	/* Set to zero */
	__le32	rsvd;
};

struct xhci_erst {
	struct xhci_erst_entry	*entries;
	unsigned int		num_entries;
	/* Num entries the ERST can contain */
	unsigned int		erst_size;
};

struct xhci_scratchpad {
	u64 *sp_array;
};

/*
 * Each segment table entry is 4*32bits long.  1K seems like an ok size:
 * (1K bytes * 8bytes/bit) / (4*32 bits) = 64 segment entries in the table,
 * meaning 64 ring segments.
 * Initial allocated size of the ERST, in number of entries */
#define	ERST_NUM_SEGS	1
/* Initial number of event segment rings allocated */
#define	ERST_ENTRIES	1
/* Initial allocated size of the ERST, in number of entries */
#define	ERST_SIZE	64
/* Poll every 60 seconds */
#define	POLL_TIMEOUT	60
/* Stop endpoint command timeout (secs) for URB cancellation watchdog timer */
#define XHCI_STOP_EP_CMD_TIMEOUT	5
/* XXX: Make these module parameters */

struct xhci_virt_ep {
	struct xhci_ring		*ring;
	unsigned int			ep_state;
#define SET_DEQ_PENDING		(1 << 0)
#define EP_HALTED		(1 << 1)	/* For stall handling */
#define EP_HALT_PENDING		(1 << 2)	/* For URB cancellation */
/* Transitioning the endpoint to using streams, don't enqueue URBs */
#define EP_GETTING_STREAMS	(1 << 3)
#define EP_HAS_STREAMS		(1 << 4)
/* Transitioning the endpoint to not using streams, don't enqueue URBs */
#define EP_GETTING_NO_STREAMS	(1 << 5)
};

#define CTX_SIZE(_hcc) (HCC_64BYTE_CONTEXT(_hcc) ? 64 : 32)

struct xhci_virt_device {
	struct usb_device		*udev;
	/*
	 * Commands to the hardware are passed an "input context" that
	 * tells the hardware what to change in its data structures.
	 * The hardware will return changes in an "output context" that
	 * software must allocate for the hardware.  We need to keep
	 * track of input and output contexts separately because
	 * these commands might fail and we don't trust the hardware.
	 */
	struct xhci_container_ctx       *out_ctx;
	/* Used for addressing devices and configuration changes */
	struct xhci_container_ctx       *in_ctx;
	/* Rings saved to ensure old alt settings can be re-instated */
#define	XHCI_MAX_RINGS_CACHED	31
	struct xhci_virt_ep		eps[31];
};

/* TODO: copied from ehci.h - can be refactored? */
/* xHCI spec says all registers are little endian */
static inline unsigned int xhci_readl(uint32_t volatile *regs)
{
	return readl(regs);
}

static inline void xhci_writel(uint32_t volatile *regs, const unsigned int val)
{
	writel(val, regs);
}

/*
 * Registers should always be accessed with double word or quad word accesses.
 * Some xHCI implementations may support 64-bit address pointers.  Registers
 * with 64-bit address pointers should be written to with dword accesses by
 * writing the low dword first (ptr[0]), then the high dword (ptr[1]) second.
 * xHCI implementations that do not support 64-bit address pointers will ignore
 * the high dword, and write order is irrelevant.
 */
static inline u64 xhci_readq(__le64 volatile *regs)
{
#if BITS_PER_LONG == 64
	return readq(regs);
#else
	__u32 *ptr = (__u32 *)regs;
	u64 val_lo = readl(ptr);
	u64 val_hi = readl(ptr + 1);
	return val_lo + (val_hi << 32);
#endif
}

static inline void xhci_writeq(__le64 volatile *regs, const u64 val)
{
#if BITS_PER_LONG == 64
	writeq(val, regs);
#else
	__u32 *ptr = (__u32 *)regs;
	u32 val_lo = lower_32_bits(val);
	/* FIXME */
	u32 val_hi = upper_32_bits(val);
	writel(val_lo, ptr);
	writel(val_hi, ptr + 1);
#endif
}

int xhci_hcd_init(int index, struct xhci_hccr **ret_hccr,
					struct xhci_hcor **ret_hcor);
void xhci_hcd_stop(int index);


/*************************************************************
	EXTENDED CAPABILITY DEFINITIONS
*************************************************************/
/* Up to 16 ms to halt an HC */
#define XHCI_MAX_HALT_USEC	(16*1000)
/* HC not running - set to 1 when run/stop bit is cleared. */
#define XHCI_STS_HALT		(1 << 0)

/* HCCPARAMS offset from PCI base address */
#define XHCI_HCC_PARAMS_OFFSET	0x10
/* HCCPARAMS contains the first extended capability pointer */
#define XHCI_HCC_EXT_CAPS(p)	(((p)>>16)&0xffff)

/* Command and Status registers offset from the Operational Registers address */
#define XHCI_CMD_OFFSET		0x00
#define XHCI_STS_OFFSET		0x04

#define XHCI_MAX_EXT_CAPS		50

/* Capability Register */
/* bits 7:0 - how long is the Capabilities register */
#define XHCI_HC_LENGTH(p)	(((p) >> 00) & 0x00ff)

/* Extended capability register fields */
#define XHCI_EXT_CAPS_ID(p)	(((p) >> 0) & 0xff)
#define XHCI_EXT_CAPS_NEXT(p)	(((p) >> 8) & 0xff)
#define	XHCI_EXT_CAPS_VAL(p)	((p) >> 16)
/* Extended capability IDs - ID 0 reserved */
#define XHCI_EXT_CAPS_LEGACY	1
#define XHCI_EXT_CAPS_PROTOCOL	2
#define XHCI_EXT_CAPS_PM	3
#define XHCI_EXT_CAPS_VIRT	4
#define XHCI_EXT_CAPS_ROUTE	5
/* IDs 6-9 reserved */
#define XHCI_EXT_CAPS_DEBUG	10
/* USB Legacy Support Capability - section 7.1.1 */
#define XHCI_HC_BIOS_OWNED	(1 << 16)
#define XHCI_HC_OS_OWNED	(1 << 24)

/* USB Legacy Support Capability - section 7.1.1 */
/* Add this offset, plus the value of xECP in HCCPARAMS to the base address */
#define XHCI_LEGACY_SUPPORT_OFFSET	(0x00)

/* USB Legacy Support Control and Status Register  - section 7.1.2 */
/* Add this offset, plus the value of xECP in HCCPARAMS to the base address */
#define XHCI_LEGACY_CONTROL_OFFSET	(0x04)
/* bits 1:2, 5:12, and 17:19 need to be preserved; bits 21:28 should be zero */
#define	XHCI_LEGACY_DISABLE_SMI		((0x3 << 1) + (0xff << 5) + (0x7 << 17))

/* USB 2.0 xHCI 0.96 L1C capability - section 7.2.2.1.3.2 */
#define XHCI_L1C               (1 << 16)

/* USB 2.0 xHCI 1.0 hardware LMP capability - section 7.2.2.1.3.2 */
#define XHCI_HLC               (1 << 19)

/* command register values to disable interrupts and halt the HC */
/* start/stop HC execution - do not write unless HC is halted*/
#define XHCI_CMD_RUN		(1 << 0)
/* Event Interrupt Enable - get irq when EINT bit is set in USBSTS register */
#define XHCI_CMD_EIE		(1 << 2)
/* Host System Error Interrupt Enable - get irq when HSEIE bit set in USBSTS */
#define XHCI_CMD_HSEIE		(1 << 3)
/* Enable Wrap Event - '1' means xHC generates an event when MFINDEX wraps. */
#define XHCI_CMD_EWE		(1 << 10)

#define XHCI_IRQS		(XHCI_CMD_EIE | XHCI_CMD_HSEIE | XHCI_CMD_EWE)

/* true: Controller Not Ready to accept doorbell or op reg writes after reset */
#define XHCI_STS_CNR		(1 << 11)

struct xhci_ctrl {
#if CONFIG_IS_ENABLED(DM_USB)
	struct udevice *dev;
#endif
	struct xhci_hccr *hccr;	/* R/O registers, not need for volatile */
	struct xhci_hcor *hcor;
	struct xhci_doorbell_array *dba;
	struct xhci_run_regs *run_regs;
	struct xhci_device_context_array *dcbaa		\
			__attribute__ ((aligned(ARCH_DMA_MINALIGN)));
	struct xhci_ring *event_ring;
	struct xhci_ring *cmd_ring;
	struct xhci_ring *transfer_ring;
	struct xhci_segment *seg;
	struct xhci_intr_reg *ir_set;
	struct xhci_erst erst;
	struct xhci_erst_entry entry[ERST_NUM_SEGS];
	struct xhci_scratchpad *scratchpad;
	struct xhci_virt_device *devs[MAX_HC_SLOTS];
	struct usb_hub_descriptor hub;
	int rootdev;
};

unsigned long trb_addr(struct xhci_segment *seg, union xhci_trb *trb);
struct xhci_input_control_ctx
		*xhci_get_input_control_ctx(struct xhci_container_ctx *ctx);
struct xhci_slot_ctx *xhci_get_slot_ctx(struct xhci_ctrl *ctrl,
					struct xhci_container_ctx *ctx);
struct xhci_ep_ctx *xhci_get_ep_ctx(struct xhci_ctrl *ctrl,
				    struct xhci_container_ctx *ctx,
				    unsigned int ep_index);
void xhci_endpoint_copy(struct xhci_ctrl *ctrl,
			struct xhci_container_ctx *in_ctx,
			struct xhci_container_ctx *out_ctx,
			unsigned int ep_index);
void xhci_slot_copy(struct xhci_ctrl *ctrl,
		    struct xhci_container_ctx *in_ctx,
		    struct xhci_container_ctx *out_ctx);
void xhci_setup_addressable_virt_dev(struct xhci_ctrl *ctrl,
				     struct usb_device *udev, int hop_portnr);
void xhci_queue_command(struct xhci_ctrl *ctrl, u8 *ptr,
			u32 slot_id, u32 ep_index, trb_type cmd);
void xhci_acknowledge_event(struct xhci_ctrl *ctrl);
union xhci_trb *xhci_wait_for_event(struct xhci_ctrl *ctrl, trb_type expected);
int xhci_bulk_tx(struct usb_device *udev, unsigned long pipe,
		 int length, void *buffer);
int xhci_ctrl_tx(struct usb_device *udev, unsigned long pipe,
		 struct devrequest *req, int length, void *buffer);
int xhci_check_maxpacket(struct usb_device *udev);
void xhci_flush_cache(uintptr_t addr, u32 type_len);
void xhci_inval_cache(uintptr_t addr, u32 type_len);
void xhci_cleanup(struct xhci_ctrl *ctrl);
struct xhci_ring *xhci_ring_alloc(unsigned int num_segs, bool link_trbs);
int xhci_alloc_virt_device(struct xhci_ctrl *ctrl, unsigned int slot_id);
int xhci_mem_init(struct xhci_ctrl *ctrl, struct xhci_hccr *hccr,
		  struct xhci_hcor *hcor);

/**
 * xhci_deregister() - Unregister an XHCI controller
 *
 * @dev:	Controller device
 * @return 0 if registered, -ve on error
 */
int xhci_deregister(struct udevice *dev);

/**
 * xhci_register() - Register a new XHCI controller
 *
 * @dev:	Controller device
 * @hccr:	Host controller control registers
 * @hcor:	Not sure what this means
 * @return 0 if registered, -ve on error
 */
int xhci_register(struct udevice *dev, struct xhci_hccr *hccr,
		  struct xhci_hcor *hcor);

extern struct dm_usb_ops xhci_usb_ops;

struct xhci_ctrl *xhci_get_ctrl(struct usb_device *udev);

#endif /* HOST_XHCI_H_ */
