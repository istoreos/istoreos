/* USB Phy */
#include <common.h>
#include <linux/string.h>
//#include <stdio.h>
#include <malloc.h>
#include <asm/io.h>

#include <asm/arch/usb-phy.h>
#include <asm/arch/usb.h>

#define TRACEF(str, x...) \
do { \
	printf("%s:%d: " str, __func__, __LINE__, ## x); \
} while (0)

#define LTRACEF debug

int get_rtk_usb_phy2(struct rtk_usb *rtkusb)
{
	int phy_num = 0;
	int i, j;

	for (i = 0; i < USB2_PHY_NUM; i++) {
		if (GET_USB2_PHY_PROP(ENABLE, i) &&
			    (GET_USB2_PHY_PROP(CTRL_ID, i) == (u32)rtkusb->controller_id)) {
			phy_num++;
		}
	}
	LTRACEF("rtkusb@%p, ctrl_id=%d, phy_num=%d\n",
		    rtkusb, rtkusb->controller_id, phy_num);

	if (phy_num == 0) {
		rtkusb->usb2phy = NULL;
		return phy_num;
	}

	rtkusb->usb2phy = malloc(sizeof(struct usb2_phy) * phy_num);
	memset(rtkusb->usb2phy, 0, sizeof(struct usb2_phy) * phy_num);

	j = 0;
	for (i = 0; i < USB2_PHY_NUM; i++) {
		if (GET_USB2_PHY_PROP(ENABLE, i) &&
			    (GET_USB2_PHY_PROP(CTRL_ID, i) == (u32)rtkusb->controller_id)) {
			struct usb2_phy *usb2phy = &rtkusb->usb2phy[j];

			usb2phy->vstatus_addr = GET_USB2_PHY_PROP(VSTATUS_ADDR, i);
			usb2phy->write_phy_addr = GET_USB2_PHY_PROP(WRITE_ADDR, i);
			usb2phy->ctrl_id = GET_USB2_PHY_PROP(CTRL_ID, i);

			usb2phy->phy_page0_setting = GET_USB2_PHY_DATA(page0, i);
			usb2phy->phy_page0_size = GET_USB2_PHY_DATA_SIZE(page0, i);
			usb2phy->phy_page1_setting = GET_USB2_PHY_DATA(page1, i);
			usb2phy->phy_page1_size = GET_USB2_PHY_DATA_SIZE(page1, i);

			if (rtkusb->class_type == DWC3_XHCI)
				usb2phy->type = GUSB2PHYACC;
			else if (rtkusb->class_type == OTG_EHCI)
				usb2phy->type = INSNREG05;

			usb2phy->phy_switch.switch_addr =
				    GET_USB2_PHY_PROP(SWITCH_ADDR, i);
			usb2phy->phy_switch.reset_addr =
				    GET_USB2_PHY_PROP(RESET_ADDR, i);
			usb2phy->phy_switch.otg_enable_addr =
				    GET_USB2_PHY_PROP(OTG_SWITCH_ADDR, i);

			usb2phy->phy_id = j;
			usb2phy->phy_count = phy_num - j;

			LTRACEF("i=%d usb2phy@%p, vstatus_addr=0x%x, write_phy_addr=0x%x\n",
				    (int)i, usb2phy, usb2phy->vstatus_addr, usb2phy->write_phy_addr);
			LTRACEF("     ctrl_id=%d, type=%d, phy_count=%d\n",
				    usb2phy->ctrl_id, usb2phy->type, usb2phy->phy_count);
			LTRACEF("     phy_page0_setting@%p, phy_page0_size=%d\n",
				    usb2phy->phy_page0_setting, (int)usb2phy->phy_page0_size);
			LTRACEF("     phy_page1_setting@%p, phy_page1_size=%d\n",
				    usb2phy->phy_page1_setting, (int)usb2phy->phy_page1_size);
			LTRACEF("     switch_addr=0x%x, reset_addr=0x%x, otg_enable_addr=0x%x\n",
				    usb2phy->phy_switch.switch_addr,
				    usb2phy->phy_switch.reset_addr,
				    usb2phy->phy_switch.otg_enable_addr);

			j++;
		}
	}
	return phy_num;
}

int get_rtk_usb_phy3(struct rtk_usb *rtkusb)
{
	int phy_num = 0;
	int i, j;

	for (i = 0; i < USB3_PHY_NUM; i++) {
		if (GET_USB3_PHY_PROP(ENABLE, i) &&
			    (GET_USB3_PHY_PROP(CTRL_ID, i) == (u32)rtkusb->controller_id)) {
			phy_num++;
		}
	}

	LTRACEF("rtkusb@%p, ctrl_id=%d, phy_num=%d\n",
		    rtkusb, rtkusb->controller_id, phy_num);

	if (phy_num == 0) {
		rtkusb->usb3phy = NULL;
		return phy_num;
	}

	rtkusb->usb3phy = malloc(sizeof(struct usb3_phy) * phy_num);
	memset(rtkusb->usb3phy, 0, sizeof(struct usb3_phy) * phy_num);

	j = 0;
	for (i = 0; i < USB3_PHY_NUM; i++) {
		if (GET_USB3_PHY_PROP(ENABLE, i) &&
			    (GET_USB3_PHY_PROP(CTRL_ID, i) == (u32)rtkusb->controller_id)) {
			struct usb3_phy *usb3phy = &rtkusb->usb3phy[j];
			usb3phy->write_phy_addr = GET_USB3_PHY_PROP(WRITE_ADDR, i);
			usb3phy->ctrl_id = GET_USB3_PHY_PROP(CTRL_ID, i);
			usb3phy->phy_data = GET_USB3_PHY_DATA(i);
			usb3phy->phy_data_size = GET_USB3_PHY_DATA_SIZE(i);

			usb3phy->phy_id = j;
			usb3phy->phy_count = phy_num - j;

			LTRACEF("i=%d usb3phy@%p, write_phy_addr=0x%x\n",
				    (int)i, usb3phy, usb3phy->write_phy_addr);
			LTRACEF("     ctrl_id=%d, phy_count=%d\n",
				    usb3phy->ctrl_id, usb3phy->phy_count);
			LTRACEF("     phy_data@%p, phy_data_size=%d\n",
				    usb3phy->phy_data, (int)usb3phy->phy_data_size);

			j++;
		}
	}

	return phy_num;
}
