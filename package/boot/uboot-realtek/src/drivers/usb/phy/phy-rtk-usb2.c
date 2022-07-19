/* RTK USB PHY init */

#include <common.h>
#include <asm/io.h>

#include <usb-phy.h>
#include <asm/arch/usb-phy.h>

#define TRACEF(str, x...) \
do { \
	printf("%s:%d: " str, __func__, __LINE__, ## x); \
} while (0)

#define LTRACEF debug

static int utmi_wait_register(u32 reg, u32 mask, u32 result)
{
	uint timeout = 10;

	while (((readl((volatile u32)reg) & mask) != result) && timeout--) {
		//udelay(100);
		mdelay(1);
		if (timeout <= 0) {
			printf("%s: \033[0:32:31m Can't program USB phy\033[m\n",__func__);
			return -1;
		}
	}
	return 0;
}

static char __INSNREG05_phy_read(struct usb2_phy *usb2phy, char addr)
{
	u32 write_phy_addr = usb2phy->write_phy_addr;
	u8 vbusy_shift = 17;
	u8 port_num_shift = 13;
	u8 vload_shift = 12;
	u8 vcontrol_shift = 8;
	volatile unsigned int regVal;

	utmi_wait_register(write_phy_addr, 1 << vbusy_shift, 0);

	// VCtrl = low nibble of addr, VLoadM = 1
	regVal = (1 << port_num_shift) | // Port num
				 (1 << vload_shift) | // vload
				 ((addr & 0x0f) << vcontrol_shift); // vcontrol
	writel(regVal, (volatile u32) (write_phy_addr));
	utmi_wait_register(write_phy_addr, 1 << vbusy_shift, 0);

	// VCtrl = low nibble of addr, VLoadM = 0
	regVal &= ~(1 << vload_shift);
	writel(regVal, (volatile u32)(write_phy_addr));
	utmi_wait_register(write_phy_addr, 1 << vbusy_shift, 0);

	// VCtrl = high nibble of addr, VLoadM = 1
	regVal = (1 << port_num_shift) | // Port num
				 (1 << vload_shift) | // vload
				 ((addr & 0xf0) << (vcontrol_shift - 4)); // vcontrol
	writel(regVal, (volatile u32)(write_phy_addr));
	utmi_wait_register(write_phy_addr, 1 << vbusy_shift, 0);

	// VCtrl = high nibble of addr, VLoadM = 0
	regVal &= ~(1 << vload_shift);
	writel(regVal, (volatile u32)(write_phy_addr));
	utmi_wait_register(write_phy_addr, 1 << vbusy_shift, 0);

	regVal = readl(write_phy_addr);
	return (char) (regVal & 0xff);
}

static char __INSNREG05_phy_write(struct usb2_phy *usb2phy, char addr,
	    char data)
{
	u32 vstatus_addr = usb2phy->vstatus_addr;
	u32 write_phy_addr = usb2phy->write_phy_addr;
	u8 vbusy_shift = 17;
	u8 port_num_shift = 13;
	u8 vload_shift = 12;
	u8 vcontrol_shift = 8;
	volatile unsigned int regVal;

	writel(data, (volatile u32)(vstatus_addr));
	utmi_wait_register((u32) write_phy_addr, 1 << vbusy_shift, 0);

	// VCtrl = low nibble of addr, VLoadM = 1
	regVal = (1 << port_num_shift) | // Port num
			 (1 << vload_shift) | // vload
			 ((addr & 0x0f) << vcontrol_shift); // vcontrol
	writel(regVal, (volatile u32) (write_phy_addr));
	utmi_wait_register((u32) write_phy_addr, 1 << vbusy_shift, 0);

	// VCtrl = low nibble of addr, VLoadM = 0
	regVal &= ~(1 << vload_shift);
	writel(regVal, (volatile u32)(write_phy_addr));
	utmi_wait_register((u32) write_phy_addr, 1 << vbusy_shift, 0);

	// VCtrl = high nibble of addr, VLoadM = 1
	regVal = (1 << port_num_shift) | // Port num
			 (1 << vload_shift) | // vload
			 ((addr & 0xf0) << (vcontrol_shift - 4)); // vcontrol
	writel(regVal, (volatile u32)(write_phy_addr));
	utmi_wait_register((u32) write_phy_addr, 1 << vbusy_shift, 0);

	// VCtrl = high nibble of addr, VLoadM = 0
	regVal &= ~(1 << vload_shift);
	writel(regVal, (volatile u32)(write_phy_addr));
	utmi_wait_register((u32)write_phy_addr, 1 << vbusy_shift, 0);

	return 0;
}

static char __GUSB2PHYACC_phy_read(struct usb2_phy *usb2phy, char addr)
{
	u32 write_phy_addr = usb2phy->write_phy_addr;
	u8 vbusy_shift = 23;
	u8 vload_shift = 25;
	u8 vcontrol_shift = 8;
	volatile unsigned int regVal;

	utmi_wait_register(write_phy_addr, 1 << vbusy_shift, 0);

	// VCtrl = low nibble of addr, VLoadM = 1
	regVal = (1 << vload_shift) | // vload
				 ((addr & 0x0f) << vcontrol_shift); // vcontrol
	writel(regVal, (volatile u32) (write_phy_addr));
	utmi_wait_register(write_phy_addr, 1 << vbusy_shift, 0);

	// VCtrl = high nibble of addr, VLoadM = 1
	regVal = (1 << vload_shift | // vload_shift
				 ((addr & 0xf0) << (vcontrol_shift - 4))); // vcontrol
	writel(regVal, (volatile u32)(write_phy_addr));
	utmi_wait_register(write_phy_addr, 1 <<vbusy_shift, 0);

	regVal = readl(write_phy_addr);
	return (char) (regVal & 0xff);
}

static char __GUSB2PHYACC_phy_write(struct usb2_phy *usb2phy, char addr,
	    char data)
{
	u32 write_phy_addr = usb2phy->write_phy_addr;
	u32 vstatus_addr = usb2phy->vstatus_addr;
	u8 vbusy_shift = 23;
	u8 vload_shift = 25;
	u8 vcontrol_shift = 8;
	int phy_id = usb2phy->phy_id;
	volatile unsigned int regVal;
	u8 write_phy_shift = 8 * phy_id;

	writel(data << write_phy_shift, (volatile u32)(vstatus_addr));
	utmi_wait_register((u32) write_phy_addr, 1 << vbusy_shift, 0);

	// VCtrl = low nibble of addr, VLoadM = 1
	regVal = (1 << vload_shift) | // vload
			 ((addr & 0x0f) << vcontrol_shift); // vcontrol
	writel(regVal, (volatile u32) (write_phy_addr));
	utmi_wait_register((u32) write_phy_addr, 1 << vbusy_shift, 0);

	// VCtrl = high nibble of addr, VLoadM = 1
	regVal = (1 << vload_shift) | // vload
			 ((addr & 0xf0) << (vcontrol_shift - 4)); // vcontrol
	writel(regVal, (volatile u32)(write_phy_addr));
	utmi_wait_register((u32) write_phy_addr, 1 << vbusy_shift, 0);

	return 0;
}

static char rtk_usb2_phy_read(struct usb2_phy *usb2phy, char addr)
{
	if (usb2phy->type == GUSB2PHYACC)
		return __GUSB2PHYACC_phy_read(usb2phy, addr);
	else if (usb2phy->type == INSNREG05)
		return __INSNREG05_phy_read(usb2phy, addr);
}

static int rtk_usb2_phy_write(struct usb2_phy *usb2phy, char addr, char data)
{
	if (usb2phy->type == GUSB2PHYACC)
		return __GUSB2PHYACC_phy_write(usb2phy, addr, data);
	else if (usb2phy->type == INSNREG05)
		return __INSNREG05_phy_write(usb2phy, addr, data);

	return -1;
}

static int do_usb2_phy_init(struct usb2_phy *usb2phy)
{
	size_t i;
	struct u2phy_data *phy_page0_setting;
	struct u2phy_data *phy_page1_setting;
	size_t phy_page0_size;
	size_t phy_page1_size;

	if (usb2phy == NULL) return 0;

	phy_page0_setting = usb2phy->phy_page0_setting;
	phy_page1_setting = usb2phy->phy_page1_setting;
	phy_page0_size = usb2phy->phy_page0_size;
	phy_page1_size = usb2phy->phy_page1_size;


	LTRACEF("Set to Page0 (ARRAY_SIZE=%ld)\n", phy_page0_size);
	rtk_usb2_phy_write(usb2phy, 0xf4, 0x9b);// set page 0

	for (i = 0; i < phy_page0_size; i++) {
		if (rtk_usb2_phy_write(usb2phy, phy_page0_setting[i].addr,
			    phy_page0_setting[i].data)) {
			LTRACEF("[%s:%d], write_phy_addr = 0x%x PHY setting Error : "
				    "addr = 0x%x, value = 0x%x\n",
				    __func__, __LINE__, usb2phy->write_phy_addr,
				    phy_page0_setting[i].addr,
				    phy_page0_setting[i].data);
			return -1;
		} else
			LTRACEF("[%s:%d], Page0 write_phy_addr = 0x%x PHY setting : "
				    "addr = 0x%x, value = 0x%x ==> value 0x%x\n",
				    __func__, __LINE__, usb2phy->write_phy_addr,
				    phy_page0_setting[i].addr, phy_page0_setting[i].data,
				    rtk_usb2_phy_read(usb2phy, phy_page0_setting[i].addr));
	}

	LTRACEF("Set to Page1 (ARRAY_SIZE=%ld)\n", phy_page1_size);
	rtk_usb2_phy_write(usb2phy, 0xf4, 0xbb);// set page 1

	for (i = 0; i < phy_page1_size; i++) {
		if (rtk_usb2_phy_write(usb2phy, phy_page1_setting[i].addr,
			    phy_page1_setting[i].data)) {
			LTRACEF("[%s:%d], write_phy_addr = 0x%x, PHY setting Error : "
				    "addr = 0x%x, value = 0x%x\n",
				    __func__, __LINE__, usb2phy->write_phy_addr,
				    phy_page1_setting[i].addr,
				    phy_page1_setting[i].data);
			return -1;
		} else
			LTRACEF("[%s:%d], Page1 write_phy_addr = 0x%x PHY setting : "
				    "addr = 0x%x, value = 0x%x ==> value 0x%x\n",
				    __func__, __LINE__, usb2phy->write_phy_addr,
				    phy_page1_setting[i].addr,
				    phy_page1_setting[i].data,
				    rtk_usb2_phy_read(usb2phy, phy_page1_setting[i].addr));
	}
	mdelay(100);
	return 0;
}

int usb2_phy_init(struct usb2_phy *usb2phy)
{
	int i, ret = 0;
	int phy_count = 0;

	if (usb2phy == NULL) return 0;

	phy_count = usb2phy->phy_count;

	for (i = 0; i < phy_count; i++) {
		struct usb2_phy *u2phy = &usb2phy[i];
		LTRACEF("#%d/%d To init usb2phy@%p ...\n", i, phy_count, u2phy);
		ret = do_usb2_phy_init(u2phy);
		if (ret) {
			TRACEF("Error to init #%d usb2phy@%p (ret=%d)\n", i, u2phy, ret);
			return ret;
		}
	}
	return ret;
}

enum switch_mode {
	HOST_MODE = 1,
	DEVICE_MODE = 2,
};

#define SWITCH_MASK 0x0fff
#define SWITCH_DEVICE 0x0
#define SWITCH_HOST 0x606

static int dwc3_switch_mode(struct usb2_phy *usb2phy, enum switch_mode mode)
{
	struct phy_switch *phy_switch = &usb2phy->phy_switch;
	u32 val = ~SWITCH_MASK & readl(phy_switch->switch_addr);

	LTRACEF("usb2phy@%p, mode %d, phy_switch@%p, switch_addr=0x%x val=0x%x\n",
		    usb2phy, mode, phy_switch, phy_switch->switch_addr, val);

	switch (mode) {
	case DEVICE_MODE:
		val |= SWITCH_DEVICE;
		LTRACEF("usb2phy@%p, DEVICE mode, switch_addr 0x%x, val=0x%x\n",
			    usb2phy, phy_switch->switch_addr, val);
		writel(val, phy_switch->switch_addr);
		return DEVICE_MODE;
	case HOST_MODE:
		val |= SWITCH_HOST;
		LTRACEF("usb2phy@%p, HOST mode, switch_addr 0x%x, val=0x%x\n",
			    usb2phy, phy_switch->switch_addr, val);
		writel(val, phy_switch->switch_addr);
		return HOST_MODE;
	default:
		return 0;
	}
}

static int otg_switch_mode(struct usb2_phy *usb2phy, enum switch_mode mode)
{
	struct phy_switch *phy_switch = &usb2phy->phy_switch;

	LTRACEF("usb2phy@%p, mode %d, phy_switch@%p\n",
		    usb2phy, mode, phy_switch);
	switch(mode) {
	case HOST_MODE:
		LTRACEF("usb2phy@%p, HOST mode, switch_addr 0x%x, "
			    "otg_enable_addr 0x%x\n",
			    usb2phy, phy_switch->switch_addr, phy_switch->otg_enable_addr);
		writel(readl(phy_switch->reset_addr) | (1 << 0),
			    phy_switch->reset_addr);
		mdelay(100);
		writel(readl(phy_switch->otg_enable_addr) & ~(1 << 0),
			    phy_switch->otg_enable_addr);
		writel(readl(phy_switch->switch_addr) & ~0x180,
			    phy_switch->switch_addr);
		mdelay(100);
		LTRACEF("usb2phy@%p, HOST mode, switch value 0x%x, "
			    "otg_enable 0x%x\n",
			    usb2phy, readl(phy_switch->switch_addr),
			    readl(phy_switch->otg_enable_addr));
		return HOST_MODE;
	case DEVICE_MODE:
		LTRACEF("usb2phy@%p, DEVICE mode, switch_addr 0x%x, "
			    "otg_enable_addr 0x%x\n",
			    usb2phy, phy_switch->switch_addr, phy_switch->otg_enable_addr);
	//	writel(readl(0x9801380c) | (1 << 0), 0x9801380c);
		writel(readl(phy_switch->reset_addr) | (1 << 0),
			    phy_switch->reset_addr);
		mdelay(100);
		writel(readl(phy_switch->otg_enable_addr) | (1 << 0),
			    phy_switch->otg_enable_addr);
		writel(readl(phy_switch->switch_addr) | 0x180,
			    phy_switch->switch_addr);
		mdelay(100);
		LTRACEF("usb2phy@%p, DEVICE mode, switch value 0x%x, "
			    "otg_enable 0x%x\n",
			    usb2phy, readl(phy_switch->switch_addr),
			    readl(phy_switch->otg_enable_addr));

		return DEVICE_MODE;
	default:
		return 0;
	}
}

int usb2_phy_switch_to_device(struct usb2_phy *usb2phy)
{
	LTRACEF("usb2phy@%p\n", usb2phy);
	if (usb2phy == NULL) return 0;

	switch (usb2phy->type) {
	case GUSB2PHYACC:
		return dwc3_switch_mode(usb2phy, DEVICE_MODE);
	case INSNREG05:
		return otg_switch_mode(usb2phy, DEVICE_MODE);
	default:
		return 0;
	}
}

int usb2_phy_switch_to_host(struct usb2_phy *usb2phy)
{
	LTRACEF("usb2phy@%p\n", usb2phy);
	if (usb2phy == NULL) return 0;

	switch (usb2phy->type) {
	case GUSB2PHYACC:
		return dwc3_switch_mode(usb2phy, HOST_MODE);
	case INSNREG05:
		return otg_switch_mode(usb2phy, HOST_MODE);
	default:
		return 0;
	}
}

