/* Define US phy parameter */
#pragma once

struct rtk_usb;

struct u2phy_data {
	char addr;
	char data;
};

enum interface_type {
	GUSB2PHYACC = 1,
	INSNREG05 = 2,
};

struct phy_switch {
	u32 switch_addr;
	u32 reset_addr;
	u32 otg_enable_addr;
};

struct usb2_phy {
	u32 vstatus_addr;
	u32 write_phy_addr;
	enum interface_type type;

	int ctrl_id;

	struct u2phy_data *phy_page0_setting;
	struct u2phy_data *phy_page1_setting;
	size_t phy_page0_size;
	size_t phy_page1_size;

	struct phy_switch phy_switch;

	int phy_id;
	int phy_count;
};

struct u3phy_data {
	char addr;
	u16 data;
};

struct usb3_phy {
	u32 write_phy_addr;

	int ctrl_id;

	struct u3phy_data *phy_data;
	size_t phy_data_size;

	int phy_id;
	int phy_count;
};

/* XHCI DRD*/
static struct u2phy_data port0_u2phy_page0_setting[] = {
	{0xe0, 0xe0},
	{0xe1, 0x30},
	{0xe2, 0x3a},
	{0xe3, 0x8d},
	{0xe4, 0xA8},
	{0xe5, 0x65},
	{0xe6, 0x91},
	{0xe7, 0x81},
	{0xf0, 0xFC},
	{0xf1, 0x8C},
	{0xf2, 0x00},
	{0xf3, 0x11},
	{0xf4, 0x9B},
	{0xf5, 0x81},
	{0xf6, 0x00},
	{0xf7, 0x02},
};

static struct u2phy_data port0_u2phy_page1_setting[] = {
	{0xe0, 0x25},
	{0xe1, 0xef},
	{0xe2, 0x60},
	{0xe3, 0x00},
	{0xe4, 0x00},
	{0xe5, 0x0f},
	{0xe6, 0x18},
	{0xe7, 0xe3},
};

/* XHCI u2host*/
static struct u2phy_data port1_u2phy_page0_setting[] = {
	{0xe0, 0xe0},
	{0xe1, 0x30},
	{0xe2, 0x3a},
	{0xe3, 0x8d},
	{0xe4, 0x6A},
	{0xe5, 0x65},
	{0xe6, 0x91},
	{0xe7, 0x81},
	{0xf0, 0xFC},
	{0xf1, 0x8C},
	{0xf2, 0x00},
	{0xf3, 0x11},
	{0xf4, 0x9B},
	{0xf5, 0x81},
	{0xf6, 0x00},
	{0xf7, 0x02},
};

static struct u2phy_data port1_u2phy_page1_setting[] = {
	{0xe0, 0x25},
	{0xe1, 0xef},
	{0xe2, 0x60},
	{0xe3, 0x00},
	{0xe4, 0x00},
	{0xe5, 0x0f},
	{0xe6, 0x18},
	{0xe7, 0xe3},
};

/* EHCI */
static struct u2phy_data port2_u2phy_page0_setting[] = {
	{0xe0, 0xe0},
	{0xe1, 0x30},
	{0xe2, 0x3a},
	{0xe3, 0x8d},
	{0xe4, 0xA9},
	{0xe5, 0x65},
	{0xe6, 0x91},
	{0xe7, 0x81},
	{0xf0, 0xFC},
	{0xf1, 0x8C},
	{0xf2, 0x00},
	{0xf3, 0x11},
	{0xf4, 0x9B},
	{0xf5, 0x81},
	{0xf6, 0x00},
	{0xf7, 0x02},

};

static struct u2phy_data port2_u2phy_page1_setting[] = {
	{0xe0, 0x25},
	{0xe1, 0xef},
	{0xe2, 0x60},
	{0xe3, 0x00},
	{0xe4, 0x00},
	{0xe5, 0x0f},
	{0xe6, 0x18},
	{0xe7, 0xe3},
};

/* XHCI u3host*/
static struct u2phy_data port3_u2phy_page0_setting[] = {
	{0xe0, 0xe0},
	{0xe1, 0x30},
	{0xe2, 0x3a},
	{0xe3, 0x8d},
	{0xe4, 0xA6},
	{0xe5, 0x65},
	{0xe6, 0x91},
	{0xe7, 0x81},
	{0xf0, 0xFC},
	{0xf1, 0x8C},
	{0xf2, 0x00},
	{0xf3, 0x11},
	{0xf4, 0x9B},
	{0xf5, 0x81},
	{0xf6, 0x00},
	{0xf7, 0x02},
};

static struct u2phy_data port3_u2phy_page1_setting[] = {
	{0xe0, 0x25},
	{0xe1, 0xef},
	{0xe2, 0x60},
	{0xe3, 0x00},
	{0xe4, 0x00},
	{0xe5, 0x0f},
	{0xe6, 0x18},
	{0xe7, 0xe3},
};

static struct u3phy_data port0_u3phy_data[] = {
	{0x00, 0x4008},
	{0x01, 0xE046},
	{0x02, 0x6046},
	{0x03, 0x2779},
	{0x04, 0x72F5},
	{0x05, 0x2AD3},
	{0x06, 0x000E},
	{0x07, 0x2E00},
	{0x08, 0x3591},
	{0x09, 0x525C},

	{0x0A, 0xA600},
	{0x0B, 0xA904},
	{0x0C, 0xC000},
	{0x0D, 0xEF1C},
	{0x0E, 0x2000},
	{0x0F, 0x0000},

	{0x10, 0x000C},
	{0x11, 0x4C00},
	{0x12, 0xFC00},
	{0x13, 0x0C81},
	{0x14, 0xDE01},
	{0x15, 0x0000},
	{0x16, 0x0000},
	{0x17, 0x0000},
	{0x18, 0x0000},
	{0x19, 0x4004},

	{0x1A, 0x1260},
	{0x1B, 0xFF00},
	{0x1C, 0xCB00},
	{0x1D, 0xA03F},
	{0x1E, 0xC2E0},
	{0x1F, 0x2807},

	{0x20, 0x947A},
	{0x21, 0x88AA},
	{0x22, 0x0057},
	{0x23, 0xAB66},
	{0x24, 0x0800},
	{0x25, 0x0000},
	{0x26, 0x040A},
	{0x27, 0x01D6},
	{0x28, 0xF8C2},
	{0x29, 0x3080},

	{0x2A, 0x3082},
	{0x2B, 0x2078},
	{0x2C, 0xFFFF},
	{0x2D, 0xFFFF},
	{0x2E, 0x0000},
	{0x2F, 0x0040},
};

static struct u3phy_data port1_u3phy_data[] = {
	{0x00, 0x4008},
	{0x01, 0xE046},
	{0x02, 0x6046},
	{0x03, 0x2779},
	{0x04, 0x72F5},
	{0x05, 0x2AD3},
	{0x06, 0x000E},
	{0x07, 0x2E00},
	{0x08, 0x3591},
	{0x09, 0x525C},

	{0x0A, 0xA600},
	{0x0B, 0xA904},
	{0x0C, 0xC000},
	{0x0D, 0xEF1C},
	{0x0E, 0x2000},
	{0x0F, 0x0000},

	{0x10, 0x000C},
	{0x11, 0x4C00},
	{0x12, 0xFC00},
	{0x13, 0x0C81},
	{0x14, 0xDE01},
	{0x15, 0x0000},
	{0x16, 0x0000},
	{0x17, 0x0000},
	{0x18, 0x0000},
	{0x19, 0x4004},

	{0x1A, 0x1260},
	{0x1B, 0xFF00},
	{0x1C, 0xCB00},
	{0x1D, 0xA03F},
	{0x1E, 0xC2E0},
	{0x1F, 0x2807},

	{0x20, 0x9424},
	{0x21, 0x284A},
	{0x22, 0x0057},
	{0x23, 0xAB66},
	{0x24, 0x0800},
	{0x25, 0x0000},
	{0x26, 0x040A},
	{0x27, 0x01D6},
	{0x28, 0xF8C2},
	{0x29, 0x3080},

	{0x2A, 0x3082},
	{0x2B, 0x2078},
	{0x2C, 0xFFFF},
	{0x2D, 0xFFFF},
	{0x2E, 0x0000},
	{0x2F, 0x0040},
};

#define USB2_PHY_NUM 4 // port0-port3

#define PORT0_USB2_PHY_ENABLE 1
#define PORT0_USB2_PHY_CTRL_ID 0
#define PORT0_USB2_PHY_WRITE_ADDR 0x98028280 // GUSB2PHYACC
#define PORT0_USB2_PHY_VSTATUS_ADDR 0x98013214 // VSTATUS_reg
#define PORT0_USB2_PHY_SWITCH_ADDR 0x98013270 // USB2_PHY_reg
#define PORT0_USB2_PHY_RESET_ADDR -1
#define PORT0_USB2_PHY_OTG_SWITCH_ADDR -1

#define PORT1_USB2_PHY_ENABLE 1
#define PORT1_USB2_PHY_CTRL_ID 1
#define PORT1_USB2_PHY_WRITE_ADDR 0x98031280 // GUSB2PHYACC
#define PORT1_USB2_PHY_VSTATUS_ADDR 0x98013C14 // VSTATUS_reg
#define PORT1_USB2_PHY_SWITCH_ADDR 0x98013C70 // USB2_PHY_reg
#define PORT1_USB2_PHY_RESET_ADDR -1
#define PORT1_USB2_PHY_OTG_SWITCH_ADDR -1

#define PORT2_USB2_PHY_ENABLE 1
#define PORT2_USB2_PHY_CTRL_ID 2
#define PORT2_USB2_PHY_WRITE_ADDR 0x980130A4 // INSNREG05
#define PORT2_USB2_PHY_VSTATUS_ADDR 0x98013824 // VSTATUS_2port_reg
#define PORT2_USB2_PHY_SWITCH_ADDR 0x98013844
#define PORT2_USB2_PHY_RESET_ADDR 0x980132C// RESET_UTMI_2port_reg
#define PORT2_USB2_PHY_OTG_SWITCH_ADDR 0x98013840

#define PORT3_USB2_PHY_ENABLE 1
#define PORT3_USB2_PHY_CTRL_ID 3
#define PORT3_USB2_PHY_WRITE_ADDR 0x981F8280 // GUSB2PHYACC
#define PORT3_USB2_PHY_VSTATUS_ADDR 0x98013E14 // VSTATUS_reg
#define PORT3_USB2_PHY_SWITCH_ADDR 0x9801E270 // USB2_PHY_reg
#define PORT3_USB2_PHY_RESET_ADDR -1
#define PORT3_USB2_PHY_OTG_SWITCH_ADDR -1

#define DEFINE_USB2_PHY_PROP(str) \
static inline u32 get_usb2_phy_##str(int index) \
{ \
	switch (index) { \
	case 0: return PORT0_USB2_PHY_##str; \
	case 1: return PORT1_USB2_PHY_##str; \
	case 2: return PORT2_USB2_PHY_##str; \
	case 3: return PORT3_USB2_PHY_##str; \
	default: printf("ERROR port index %d\n", index); \
	} \
	return -1; \
}

#define GET_USB2_PHY_PROP(str, index) get_usb2_phy_##str(index)

DEFINE_USB2_PHY_PROP(ENABLE)
DEFINE_USB2_PHY_PROP(CTRL_ID)
DEFINE_USB2_PHY_PROP(WRITE_ADDR)
DEFINE_USB2_PHY_PROP(VSTATUS_ADDR)
DEFINE_USB2_PHY_PROP(SWITCH_ADDR)
DEFINE_USB2_PHY_PROP(RESET_ADDR)
DEFINE_USB2_PHY_PROP(OTG_SWITCH_ADDR)

#define DEFINE_USB2_PHY_DATA(str) \
static inline struct u2phy_data *get_usb2_phy_##str##_data(int index) \
{ \
	switch (index) { \
	case 0: return &port0_u2phy_##str##_setting[0]; \
	case 1: return &port1_u2phy_##str##_setting[0]; \
	case 2: return &port2_u2phy_##str##_setting[0]; \
	case 3: return &port3_u2phy_##str##_setting[0]; \
	default: printf("ERROR port index %d\n", index); \
	} \
	return NULL; \
}

#define GET_USB2_PHY_DATA(str, index) get_usb2_phy_##str##_data(index)

DEFINE_USB2_PHY_DATA(page0)
DEFINE_USB2_PHY_DATA(page1)

//#define ARRAY_SIZE(arr)    (sizeof(arr) / sizeof((arr)[0]))

#define DEFINE_USB2_PHY_DATA_SIZE(str) \
static inline size_t get_usb2_phy_##str##_data_size(int index) \
{ \
	switch (index) { \
	case 0: return ARRAY_SIZE(port0_u2phy_##str##_setting); \
	case 1: return ARRAY_SIZE(port1_u2phy_##str##_setting); \
	case 2: return ARRAY_SIZE(port2_u2phy_##str##_setting); \
	case 3: return ARRAY_SIZE(port3_u2phy_##str##_setting); \
	default: printf("%s ERROR port index %d\n", __func__, index); \
	} \
	return 0; \
}

#define GET_USB2_PHY_DATA_SIZE(str, index) get_usb2_phy_##str##_data_size(index)

DEFINE_USB2_PHY_DATA_SIZE(page0)
DEFINE_USB2_PHY_DATA_SIZE(page1)

#define USB3_PHY_NUM 2 // port0-port1

#define PORT0_USB3_PHY_ENABLE 1
#define PORT0_USB3_PHY_CTRL_ID 0 // host/device id
#define PORT0_USB3_PHY_WRITE_ADDR 0x98013210

#define PORT1_USB3_PHY_ENABLE 1
#define PORT1_USB3_PHY_CTRL_ID 3 // host/device id
#define PORT1_USB3_PHY_WRITE_ADDR 0x98013E10

#define DEFINE_USB3_PHY_PROP(str) \
static inline u32 GET_USB3_PHY_##str(int index) \
{ \
	switch (index) { \
	case 0: return PORT0_USB3_PHY_##str; \
	case 1: return PORT1_USB3_PHY_##str; \
	default: printf("ERROR port index %d\n", index); \
	} \
	return -1; \
}

#define GET_USB3_PHY_PROP(str, index) GET_USB3_PHY_##str(index)

DEFINE_USB3_PHY_PROP(ENABLE)
DEFINE_USB3_PHY_PROP(CTRL_ID)
DEFINE_USB3_PHY_PROP(WRITE_ADDR)

#define DEFINE_USB3_PHY_DATA() \
static inline struct u3phy_data *get_usb3_phy_data(int index) \
{ \
	switch (index) { \
	case 0: return port0_u3phy_data; \
	case 1: return port1_u3phy_data; \
	default: printf("%s ERROR port index %d\n", __func__, index); \
	} \
	return NULL; \
}

#define GET_USB3_PHY_DATA(index) get_usb3_phy_data(index)

DEFINE_USB3_PHY_DATA()

#define DEFINE_USB3_PHY_DATA_SIZE() \
static inline size_t get_usb3_phy_data_size(int index) \
{ \
	switch (index) { \
	case 0: return ARRAY_SIZE(port0_u3phy_data); \
	case 1: return ARRAY_SIZE(port1_u3phy_data); \
	default: printf("%s ERROR port index %d\n", __func__, index); \
	} \
	return 0; \
}

#define GET_USB3_PHY_DATA_SIZE(index) get_usb3_phy_data_size(index)

DEFINE_USB3_PHY_DATA_SIZE()

int get_rtk_usb_phy2(struct rtk_usb *rtk_usb);
int get_rtk_usb_phy3(struct rtk_usb *rtk_usb);
