/* RTK usb init, clock, reset, power gpio*/
#include <common.h>
#include <linux/string.h>
//#include <stdio.h>
#include <malloc.h>
#include <asm/io.h>
#include <asm/arch/platform_lib/board/gpio.h>
#include <asm/arch/usb.h>
#include <asm/arch/usb-phy.h>
#include <asm/arch/cpu.h>

#define TRACEF(str, x...) \
do { \
	printf("%s:%d: " str, __func__, __LINE__, ## x); \
} while (0)

#define LTRACEF debug

#define get_chip_id get_cpu_id

#define get_chip_rev get_rtd129x_cpu_revision

// CRT_SOFT_RESET1 usb part
#define rstn_usb_phy1 		(0x1 << 9)
#define rstn_usb_phy0 		(0x1 << 8)
#define rstn_usb 			(0x1 << 6)
#define rstn_usb3_p0_mdio 	(0x1 << 4)
#define rstn_usb3_phy0_pow 	(0x1 << 2)
// CRT_SOFT_RESET2 usb part
#define rstn_usb3_p1_mdio 	(0x1 << 5)
#define rstn_usb3_phy1_pow 	(0x1 << 4)
#define rstn_usb_phy2 		(0x1 << 3)
#define rstn_usb_phy3 		(0x1 << 2)
// CRT_CLOCK_ENABLE1 usb part
#define clk_en_usb 			(0x1 << 4)

void rtk_usb_clock_init(void)
{
	void *reset1 = (void *)CRT_BASE + 0x0;
	void *reset2 = (void *)CRT_BASE + 0x4;
	void *clk_en1 = (void *)CRT_BASE + 0xC;

	int reset1_pll_flag = rstn_usb_phy1 | rstn_usb_phy0 | rstn_usb3_phy0_pow;
	int reset2_pll_flag = rstn_usb_phy2;// | rstn_usb_phy3 | rstn_usb3_phy1_pow;
	int reset1_usb_flag = rstn_usb3_p0_mdio | rstn_usb;
	int reset2_usb_flag = 0;// rstn_usb3_p1_mdio;

	if (get_chip_id() == RTK1296_CPU_ID) {
		TRACEF("Realtek-usb: Enable 1296 u3host clock and power\n");
		if (get_chip_rev() == RTD129x_CHIP_REVISION_A00) {
			writel(0x00000F05, 0x98007FA0);
			TRACEF("Realtek-usb 1296 A00 enabled power\n");
		}
		reset2_pll_flag |= rstn_usb_phy3 | rstn_usb3_phy1_pow;
		reset2_usb_flag |= rstn_usb3_p1_mdio;
	}

	LTRACEF("Realtek-usb: init start soft_reset1=%x, soft_reset2=%x, clock_enable1=%x\n",
		(uint32_t)(readl((volatile u32*)reset1)),
		(uint32_t)(readl((volatile u32*)reset2)),
		(uint32_t)(readl((volatile u32*)clk_en1)));

	//Enable PLL
	writel(reset1_pll_flag | readl((volatile u32*)reset1), (volatile u32*) reset1);
	writel(reset2_pll_flag | readl((volatile u32*)reset2), (volatile u32*) reset2);

	mdelay(200);
	LTRACEF("Realtek-usb: Enable PLL soft_reset1=%x, soft_reset2=%x, clock_enable1=%x\n",
		(uint32_t)(readl((volatile u32*)reset1)),
		(uint32_t)(readl((volatile u32*)reset2)),
		(uint32_t)(readl((volatile u32*)clk_en1)));

	//Reset USB
	//writel(0x354 | readl((volatile u32*)reset1), (volatile u32*) reset1);
	//mdelay(10);

	//Turn on USB clk
	writel(clk_en_usb | readl((volatile u32*)clk_en1), (volatile u32*) clk_en1);
	writel(~clk_en_usb & readl((volatile u32*)clk_en1), (volatile u32*) clk_en1);
	mdelay(10);

	LTRACEF("Realtek-usb: trigger bit4 CLK_EN_USB soft_reset1=%x, soft_reset2=%x, clock_enable1=%x\n",
		(uint32_t)(readl((volatile u32*)reset1)),
		(uint32_t)(readl((volatile u32*)reset2)),
		(uint32_t)(readl((volatile u32*)clk_en1)));

	writel(reset1_usb_flag | readl((volatile u32*)reset1), (volatile u32*) reset1);
	writel(reset2_usb_flag | readl((volatile u32*)reset2), (volatile u32*) reset2);
	mdelay(10);
	LTRACEF("Realtek-usb: Turn on all RSTN_USB soft_reset1=%x, soft_reset2=%x, clock_enable1=%x\n",
		(uint32_t)(readl((volatile u32*)reset1)),
		(uint32_t)(readl((volatile u32*)reset2)),
		(uint32_t)(readl((volatile u32*)clk_en1)));

	writel(clk_en_usb | readl((volatile u32*)clk_en1), (volatile u32*) clk_en1);
	mdelay(10);
	LTRACEF("Realtek-usb: Turn on CLK_EN_USB soft_reset1=%x, soft_reset2=%x, clock_enable1=%x\n",
		(uint32_t)(readl((volatile u32*)reset1)),
		(uint32_t)(readl((volatile u32*)reset2)),
		(uint32_t)(readl((volatile u32*)clk_en1)));

	LTRACEF("Realtek-usb: Turn on USB soft_reset1=%x, soft_reset2=%x, clock_enable1=%x\n",
		(uint32_t)(readl((volatile u32*)reset1)),
		(uint32_t)(readl((volatile u32*)reset2)),
		(uint32_t)(readl((volatile u32*)clk_en1)));
}

void rtk_usb_clock_stop(void)
{
	void *reset1 = (void *)CRT_BASE + 0x0;
	void *reset2 = (void *)CRT_BASE + 0x4;
	void *clk_en1 = (void *)CRT_BASE + 0xC;

	int reset1_pll_flag = rstn_usb_phy1 | rstn_usb_phy0 | rstn_usb3_phy0_pow;
	int reset2_pll_flag = rstn_usb_phy2;// | rstn_usb_phy3 | rstn_usb3_phy1_pow;
	int reset1_usb_flag = rstn_usb3_p0_mdio | rstn_usb;
	int reset2_usb_flag = 0;// rstn_usb3_p1_mdio;

	//Stop PLL
	writel(~(reset1_pll_flag | reset1_usb_flag) &
		    readl((volatile u32*)reset1), (volatile u32*) reset1);
	writel(~(reset2_pll_flag | reset2_usb_flag) &
		    readl((volatile u32*)reset2), (volatile u32*) reset2);

	writel(~clk_en_usb & readl((volatile u32*)clk_en1),
		    (volatile u32*) clk_en1);

	TRACEF("Realtek-usb: stop soft_reset1=%x, soft_reset2=%x, clock_enable1=%x\n",
		(uint32_t)(readl((volatile u32*)reset1)),
		(uint32_t)(readl((volatile u32*)reset2)),
		(uint32_t)(readl((volatile u32*)clk_en1)));

}

// for none define GPIO
/* define 1295 USB GPIO control */
/* Port 0, DRD, TYPE_C */
#ifndef USB_PORT0_GPIO_TYPE
#define USB_PORT0_GPIO_TYPE "NO_DEFINE"
#define USB_PORT0_GPIO_NUM 0
#endif
#ifndef USB_PORT0_TYPE_C_RD_GPIO_TYPE
#define USB_PORT0_TYPE_C_RD_GPIO_TYPE "NO_DEFINE"
#define USB_PORT0_TYPE_C_RD_GPIO_NUM 0
#endif
/* Port 1, xhci u2 host */
#ifndef USB_PORT1_GPIO_TYPE
#define USB_PORT1_GPIO_TYPE "NO_DEFINE"
#define USB_PORT1_GPIO_NUM  0
#endif
/* Port 2, ehci u2 host */
#ifndef USB_PORT2_GPIO_TYPE
#define USB_PORT2_GPIO_TYPE "NO_DEFINE"
#define USB_PORT2_GPIO_NUM  0
#endif
/* Port 3, xhci u3 host only for 1296 */
#ifndef USB_PORT3_GPIO_TYPE
#define USB_PORT3_GPIO_TYPE "NO_DEFINE"
#define USB_PORT3_GPIO_NUM 0
#endif

// for none define GPIO
/* define 1295 USB GPIO control */
/* Port 0, DRD, TYPE_C */
#ifndef RTD1296_USB_PORT0_GPIO_TYPE
#define RTD1296_USB_PORT0_GPIO_TYPE "NO_DEFINE"
#define RTD1296_USB_PORT0_GPIO_NUM 0
#endif
#ifndef RTD1296_USB_PORT0_TYPE_C_RD_GPIO_TYPE
#define RTD1296_USB_PORT0_TYPE_C_RD_GPIO_TYPE "NO_DEFINE"
#define RTD1296_USB_PORT0_TYPE_C_RD_GPIO_NUM 0
#endif
/* Port 1, xhci u2 host */
#ifndef RTD1296_USB_PORT1_GPIO_TYPE
#define RTD1296_USB_PORT1_GPIO_TYPE "NO_DEFINE"
#define RTD1296_USB_PORT1_GPIO_NUM  0
#endif
/* Port 2, ehci u2 host */
#ifndef RTD1296_USB_PORT2_GPIO_TYPE
#define RTD1296_USB_PORT2_GPIO_TYPE "NO_DEFINE"
#define RTD1296_USB_PORT2_GPIO_NUM  0
#endif
/* Port 3, xhci u3 host only for 1296 */
#ifndef RTD1296_USB_PORT3_GPIO_TYPE
#define RTD1296_USB_PORT3_GPIO_TYPE "NO_DEFINE"
#define RTD1296_USB_PORT3_GPIO_NUM 0
#endif

#define USB_GPIO(GPIO_TYPE, NUM, enable) \
do {  \
	if (get_chip_id() == RTK1296_CPU_ID) { \
		LTRACEF("RTD1296 SET %s #%d enable=%d\n", \
			    RTD1296_##GPIO_TYPE, RTD1296_##NUM, enable); \
		if (!strcmp(RTD1296_##GPIO_TYPE, "ISOGPIO"))  \
			setISOGPIO(RTD1296_##NUM, enable); \
		else if (!strcmp(RTD1296_##GPIO_TYPE, "GPIO")) \
			setGPIO(RTD1296_##NUM, enable); \
		else \
			printf("ERROR RTD1296 GPIO Type %s\n", RTD1296_##GPIO_TYPE); \
	} else { \
		LTRACEF("SET %s #%d enable=%d\n", GPIO_TYPE, NUM, enable); \
		if (!strcmp(GPIO_TYPE, "ISOGPIO")) \
			setISOGPIO(NUM, enable); \
		else if (!strcmp(GPIO_TYPE, "GPIO")) \
			setGPIO(NUM, enable); \
		else \
			printf("ERROR GPIO Type %s\n", GPIO_TYPE); \
	} \
} while (0)

/* PORT0, XHCI DRD, TYPE C */
#define USB_PORT0_POWER(enable) \
do { \
	USB_GPIO(USB_PORT0_GPIO_TYPE, USB_PORT0_GPIO_NUM, enable); \
} while (0)

/* enable = 1, write 0 to gpio ==> use external rd*/
#define USB_PORT0_RD(enable) \
do { \
	USB_GPIO(USB_PORT0_TYPE_C_RD_GPIO_TYPE, \
		    USB_PORT0_TYPE_C_RD_GPIO_NUM, !enable); \
} while (0)

#define NO_USB_PORT0_RD_GPIO \
	!strcmp(USB_PORT0_TYPE_C_RD_GPIO_TYPE, "none")

/* PORT1, XHCI u2host */
#define USB_PORT1_POWER(enable) \
do { \
	USB_GPIO(USB_PORT1_GPIO_TYPE, USB_PORT1_GPIO_NUM, enable); \
} while (0)

/* PORT2, EHCI u2host */
#define USB_PORT2_POWER(enable) \
do { \
	USB_GPIO(USB_PORT2_GPIO_TYPE, USB_PORT2_GPIO_NUM, enable); \
} while (0)

/* PORT3, XHCI u3host for 1296 only*/
#define USB_PORT3_POWER(enable) \
do { \
	USB_GPIO(USB_PORT3_GPIO_TYPE, USB_PORT3_GPIO_NUM, enable); \
} while (0)

void rtk_usb_power_on(void)
{
	int check, type_c_have_device = 0;

	writel(0x00000400, (volatile u32*) USB_TYPEC_CTRL_CC1_1);
	writel(0x00000500, (volatile u32*) USB_TYPEC_CTRL_CC2_1);

	if (NO_USB_PORT0_RD_GPIO) { // for NO rd control case
		writel(0x00000003, (volatile u32*) USB_TYPEC_CTRL_CC1_0);
		writel(0x00000003, (volatile u32*) USB_TYPEC_CTRL_CC2_0);
	} else {
		USB_PORT0_RD(1);
		writel(0x00000001, (volatile u32*) USB_TYPEC_CTRL_CC1_0);
		writel(0x00000001, (volatile u32*) USB_TYPEC_CTRL_CC2_0);
	}
	mdelay(10);

	check = readl((volatile u32*)USB_TYPEC_STS);
		LTRACEF("Realtek-usb: type_c cc status=0x%x\n", check);
	if ((check & 0x7) != 0x0) {
		LTRACEF("Realtek-usb: cc1 detect type_c have power\n");
		goto out;
	} else if ((check & 0x38) != 0x0) {
		LTRACEF("Realtek-usb: cc2 detect type_c have power\n");
		goto out;
	}

	writel(0x080c0400, (volatile u32*) USB_TYPEC_CTRL_CC1_1);
	writel(0x080c0500, (volatile u32*) USB_TYPEC_CTRL_CC2_1);
	writel(0x02c00071, (volatile u32*) USB_TYPEC_CTRL_CC1_0);
	writel(0x03000071, (volatile u32*) USB_TYPEC_CTRL_CC2_0);

	/* set type c rd gpio */
	USB_PORT0_RD(0); // disable external rd

	mdelay(1);

	check = readl((volatile u32*)USB_TYPEC_STS);
	if ((check & 0x7) != 0x7) {
		LTRACEF("Realtek-usb: cc1 detect\n");
		type_c_have_device = 1;
	} else if ((check & 0x38) != 0x38) {
		LTRACEF("Realtek-usb: cc2 detect\n");
		type_c_have_device = 1;
	}

	//Type C 5V
	if (type_c_have_device) {
		LTRACEF("Realtek-usb: Turn on port 0 power\n");
		USB_PORT0_POWER(1);
	} else {
		LTRACEF("Realtek-usb: Type C port no device, turn off port 0 power\n");
		USB_PORT0_POWER(0);
	}

out:
	//Usb2 5V
	LTRACEF("Realtek-usb: Turn on port 1 and 2 power\n");
	USB_PORT1_POWER(1);
	USB_PORT2_POWER(1);

	if (get_chip_id() == RTK1296_CPU_ID) {
		LTRACEF("Realtek-usb: Turn on 1296 usb port3 power\n");
		USB_PORT3_POWER(1);
	}
}

void rtk_usb_power_off(void)
{
	/* TODO */
}

int rtk_usb_device_init(struct rtk_usb **rtk_usb)
{
	struct rtk_usb *rtkusb;
	size_t count = USB_DEVICE_NUM;
	size_t ctrl_count, i, j;

	ctrl_count = 0;
	for (i = 0; i < count; i++) {
		if (GET_DEVICE_PROP(ENABLE, i) == 1)
			ctrl_count++;
	}

	*rtk_usb = malloc(sizeof(struct rtk_usb) * ctrl_count);
	memset(*rtk_usb, 0, sizeof(struct rtk_usb) * ctrl_count);

	j = 0;
	for (i = 0; i < count; i++) {
		if (GET_DEVICE_PROP(ENABLE, i) == 0)
			continue;
		rtkusb = &((*rtk_usb)[j]);
		rtkusb->controller_id = GET_DEVICE_PROP(CTRL_ID, i);
		rtkusb->controller_type = DEVICE_CTRL;
		rtkusb->class_type = GET_DEVICE_PROP(TYPE, i);
		rtkusb->reg_base = GET_DEVICE_PROP(ADDR, i);
		rtkusb->wrap_base = GET_DEVICE_PROP(WRAP_ADDR, i);

		get_rtk_usb_phy2(rtkusb);
		get_rtk_usb_phy3(rtkusb);

		rtkusb->ctrl_count = ctrl_count - j;

		LTRACEF("i=%d rtkusb@%p, controller_id=%d, controller_type=%d\n",
			    (int)i, rtkusb, rtkusb->controller_id, rtkusb->controller_type);
		LTRACEF("     class_type=%d, reg_base=0x%x, wrap_base=0x%x\n",
			    rtkusb->class_type, rtkusb->reg_base, rtkusb->wrap_base);
		LTRACEF("     usb2phy@%p, usb3phy@%p, ctrl_count=%d\n",
			    rtkusb->usb2phy, rtkusb->usb3phy, rtkusb->ctrl_count);
		j++;
	}
	return ctrl_count;
}

int rtk_usb_device_stop(struct rtk_usb **rtk_usb)
{
	if (*rtk_usb) {
		free(*rtk_usb);
		*rtk_usb = NULL;
	}
	return 0;
}

int rtk_usb_host_init(struct rtk_usb **rtk_usb)
{
	struct rtk_usb *rtkusb;
	size_t count = USB_HOST_NUM;
	size_t ctrl_count, i, j;

	if (get_chip_id() != RTK1296_CPU_ID) {
		count--;
	}
	LTRACEF("Realtek USB: Host count=%d\n", (int)count);

	ctrl_count = 0;
	for (i = 0; i < count; i++) {
		if (GET_HOST_PROP(ENABLE, i) == 1)
			ctrl_count++;
	}

	*rtk_usb = malloc(sizeof(struct rtk_usb) * ctrl_count);
	memset(*rtk_usb, 0, sizeof(struct rtk_usb) * ctrl_count);

	j = 0;
	for (i = 0; i < count; i++) {
		if (GET_HOST_PROP(ENABLE, i) == 0)
			continue;
		rtkusb = &((*rtk_usb)[j]);
		rtkusb->controller_id = GET_HOST_PROP(CTRL_ID, i);
		rtkusb->controller_type = HOST_CTRL;
		rtkusb->class_type = GET_HOST_PROP(TYPE, i);
		rtkusb->reg_base = GET_HOST_PROP(ADDR, i);
		rtkusb->wrap_base = GET_HOST_PROP(WRAP_ADDR, i);

		get_rtk_usb_phy2(rtkusb);
		get_rtk_usb_phy3(rtkusb);

		rtkusb->ctrl_count = ctrl_count - j;

		LTRACEF("i=%d rtkusb@%p, controller_id=%d, controller_type=%d\n",
			    (int)i, rtkusb, rtkusb->controller_id, rtkusb->controller_type);
		LTRACEF("     class_type=%d, reg_base=0x%x, wrap_base=0x%x\n",
			    rtkusb->class_type, rtkusb->reg_base, rtkusb->wrap_base);
		LTRACEF("     usb2phy@%p, usb3phy@%p, ctrl_count=%d\n",
			    rtkusb->usb2phy, rtkusb->usb3phy, rtkusb->ctrl_count);

		j++;
	}
	return ctrl_count;

	return 0;
}

int rtk_usb_host_stop(struct rtk_usb **rtk_usb)
{
	if (*rtk_usb) {
		free(*rtk_usb);
		*rtk_usb = NULL;
	}
	return 0;
}

