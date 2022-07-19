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

static u32 rtk_usb3_phy_read(struct usb3_phy *usb3phy, char addr)
{
	volatile unsigned int regVal;
	u32 write_phy_addr = usb3phy->write_phy_addr;

	regVal = (addr << 8);

	writel(regVal, write_phy_addr);

	utmi_wait_register(write_phy_addr, (1<<7), 0);

	return readl(write_phy_addr);
}

static int rtk_usb3_phy_write(struct usb3_phy *usb3phy, char addr, u16 data)
{
	u32 write_phy_addr = usb3phy->write_phy_addr;
	volatile unsigned int regVal;

	regVal = 0x1 |
			(addr << 8) |
			(data << 16);

	writel(regVal, write_phy_addr);

	utmi_wait_register(write_phy_addr, (1<<7), 0);

	return 0;
}

static int do_usb3_phy_init(struct usb3_phy *usb3phy)
{
	size_t i;
	struct u3phy_data *phy_data;
	size_t phy_data_size;

	if (usb3phy == NULL) return 0;

	phy_data = usb3phy->phy_data;
	phy_data_size = usb3phy->phy_data_size;

	LTRACEF("start init usb3phy\n");

	for (i = 0; i < phy_data_size; i++) {
		if (rtk_usb3_phy_write(usb3phy, phy_data[i].addr, phy_data[i].data)) {
			LTRACEF("[%s:%d], write_phy_addr = 0x%x PHY setting Error : "
				    "addr = 0x%x, value = 0x%x\n",
				    __func__, __LINE__, usb3phy->write_phy_addr,
				    phy_data[i].addr,
				    phy_data[i].data);
			return -1;
		} else
			LTRACEF("[%s:%d], write_phy_addr = 0x%x PHY setting : "
				    "addr = 0x%x, value = 0x%x ==> value 0x%x\n",
				    __func__, __LINE__, usb3phy->write_phy_addr,
				    phy_data[i].addr,
				    phy_data[i].data,
				    rtk_usb3_phy_read(usb3phy, phy_data[i].addr));
	}

	return 0;
}

int usb3_phy_init(struct usb3_phy *usb3phy)
{
	int i, ret = 0;
	int phy_count = 0;

	if (usb3phy == NULL) return 0;

	phy_count = usb3phy->phy_count;
	for (i = 0; i < phy_count; i++) {
		struct usb3_phy *u3phy = &usb3phy[i];
		LTRACEF("#%d/%d To init usb3phy@%p ...\n", i, phy_count, u3phy);
		ret = do_usb3_phy_init(u3phy);
		if (ret) {
			TRACEF("Error to init #%d usb3phy@%p (ret=%d)\n", i, u3phy, ret);
			return ret;
		}
	}
	return ret;
}


