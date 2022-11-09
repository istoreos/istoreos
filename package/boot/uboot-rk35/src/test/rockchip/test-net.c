/*
 * (C) Copyright 2019 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <common.h>
#include <dm.h>
#include <fdtdec.h>
#include <malloc.h>
#include <miiphy.h>
#include <net.h>
#include <phy.h>
#include <asm/io.h>
#include "test-rockchip.h"

#ifdef CONFIG_GMAC_ROCKCHIP
#define LOOPBACK_TEST_HDR_SIZE		14
#define LOOPBACK_TEST_DATA_SIZE		1500
#define LOOPBACK_TEST_FRAME_SIZE	(14 + 1500)

#define MAX_TX_DELAY_LINE		0X7F
#define MAX_RX_DELAY_LINE		0X7F

/* MAC configuration register definitions */
#define FRAMEBURSTENABLE		(1 << 21)
#define MII_PORTSELECT			(1 << 15)
#define FES_100				(1 << 14)
#define DISABLERXOWN			(1 << 13)
#define FULLDPLXMODE			(1 << 11)

enum loopback_speed {
	LOOPBACK_SPEED_10	= 10,
	LOOPBACK_SPEED_100	= 100,
	LOOPBACK_SPEED_1000	= 1000
};
#ifdef CONFIG_RKIMG_BOOTLOADER
extern void gmac_set_rgmii(struct udevice *dev, u32 tx_delay, u32 rx_delay);
#endif
static struct phy_device *get_current_phydev(void)
{
	struct mii_dev *bus = mdio_get_current_dev();
	int i;

	for (i = 0; i < PHY_MAX_ADDR; i++) {
		if (bus->phymap[i])
			return bus->phymap[i];
	}

	return NULL;
}

static void create_lbtest_frame(uchar *data, unsigned int frame_size)
{
	memset(data, 0xFF, frame_size);
	frame_size &= ~1;
	memset(data + (frame_size / 2), 0xAA, frame_size / 2 - 1);
}

static void alter_lbtest_frame(uchar *data, unsigned int frame_size,
			       unsigned int tx, unsigned int rx)
{
	frame_size &= ~1;
	memset(data + (frame_size / 2 + tx), 0xBE, 1);
	memset(data + (frame_size / 2 + rx), 0xAF, 1);
}

static int check_lbtest_frame(uchar *tx_data, uchar *rx_data,
			      unsigned int frame_size)
{
	int i;

	for (i = 0; i < frame_size; i++) {
		if (tx_data[i] != rx_data[i])
			return 13;
	}

	return 0;
}

static void eth_setup_loopback_test(struct udevice *current, int speed)
{
	struct phy_device *phydev = get_current_phydev();
	struct eth_pdata *pdata = dev_get_platdata(current);
	u32 conf;
	int val;

	if (!phydev) {
		printf("%s, can't get phydev\n", __func__);
		return;
	}

	/* set mac ctrl register */
	conf = readl(pdata->iobase);
	if (speed != LOOPBACK_SPEED_1000)
		conf |= MII_PORTSELECT;
	else
		conf &= ~MII_PORTSELECT;

	if (speed == LOOPBACK_SPEED_100)
		conf |= FES_100;

	if (phydev->duplex)
		conf |= FULLDPLXMODE;
	writel(conf, pdata->iobase);

	/* set phy ctrl register */
	val = phy_read(phydev, MDIO_DEVAD_NONE, MII_BMCR);
	val &= ~(BMCR_ANENABLE | BMCR_PDOWN);
	val |= BMCR_LOOPBACK;
	if (speed == LOOPBACK_SPEED_1000) {
		val |= BMCR_SPEED1000;
		val &= ~BMCR_SPEED100;
	} else if (speed == LOOPBACK_SPEED_100) {
		val &= ~BMCR_SPEED1000;
		val |= BMCR_SPEED100;
	} else if (speed == LOOPBACK_SPEED_10) {
		val &= ~BMCR_SPEED1000;
		val &= ~BMCR_SPEED100;
	}
	val |= BMCR_FULLDPLX;
	phy_write(phydev, MDIO_DEVAD_NONE, MII_BMCR, val);
}

static int eth_run_loopback_test(struct udevice *current, int speed, int delay_test)
{
	int flags = ETH_RECV_CHECK_DEVICE;
	uchar *tx_pkt, *rx_packet;
	int ret, length, success = 0;
	u32 i, j;

	/* make sure the net_tx_packet is initialized (net_init() was called) */
	assert(net_tx_packet);
	if (!net_tx_packet)
		return -EINVAL;

	net_set_ether(net_tx_packet, net_bcast_ethaddr, LOOPBACK_TEST_DATA_SIZE);
	tx_pkt = (uchar *)net_tx_packet + LOOPBACK_TEST_HDR_SIZE;
	create_lbtest_frame(tx_pkt, LOOPBACK_TEST_DATA_SIZE);
	udelay(50000);

	for (i = 0x0; i < MAX_TX_DELAY_LINE; i++) {
		if (delay_test)
			printf("[0x%02x]:", i);
		for (j = 0x0; j < MAX_RX_DELAY_LINE; j++) {
#ifdef CONFIG_RKIMG_BOOTLOADER
			if (delay_test)
				gmac_set_rgmii(current, i, j);
#endif
			alter_lbtest_frame(tx_pkt, LOOPBACK_TEST_DATA_SIZE, i, j);
			net_send_packet(net_tx_packet, LOOPBACK_TEST_FRAME_SIZE);

			/*
			 * Make sure that mac have enough delay time to
			 * receive packet.
			 */
			if (speed == LOOPBACK_SPEED_10)
				udelay(2000);
			else if (speed == LOOPBACK_SPEED_100)
				udelay(2000);
			else
				/* The default is 1000M speed */
				udelay(200);

			length = eth_get_ops(current)->recv(current, flags, &rx_packet);
			if (length > 0) {
				if (!check_lbtest_frame(net_tx_packet, rx_packet,
							LOOPBACK_TEST_FRAME_SIZE)) {
					printf("*");
					success++;
					ret = 0;
				} else {
					printf("x");
					ret = -EINVAL;
				}
			} else if (length == 0) {
				ret = -EBUSY;
				printf("?");
			} else {
				ret = length;
				printf(" ");
			}

			if (length >= 0 && eth_get_ops(current)->free_pkt)
				eth_get_ops(current)->free_pkt(current, rx_packet,
							       length);

			/* Only run loopback test once */
			if (!delay_test) {
				printf("\n");
				return ret;
			}
		}
		printf("\n");
	}

	if (delay_test && success > 0)
		ret = 0;

	return ret;
}

static int ethernet_init(void)
{
	int ret = -EINVAL;

	net_init();
	eth_halt();
	eth_set_current();
	ret = eth_init();
	if (ret < 0) {
		eth_halt();
		return ret;
	}

	return ret;
}

static int eth_loopback_test(int speed, int delay_test)
{
	struct udevice *current;
	int ret;

	current = eth_get_dev();
	if (!current || !device_active(current))
		return -EINVAL;

	eth_setup_loopback_test(current, speed);
	ret = ethernet_init();
	if (ret) {
		printf("%s, ethernet_init error: %d\n", __func__, ret);
		return ret;
	}

	ret = eth_run_loopback_test(current, speed, delay_test);

	return ret;
}

static void do_eth_help(void)
{
	printf("Usage:\n");
	printf("rktest eth loopback speed - Test the phy loopback, speed is 1000/100/10, need to unplug the RJ45 cable\n");
	printf("rktest eth delaytest - Get the loopback-passed tx_delay/rx_delay array, need to unplug the RJ45 cable\n");
	printf("rktest eth delayline tx_delay rx_delay - Delay value is 0x00~0x7f\n");
	printf("rktest eth dhcp address IP:file - Boot image via network using DHCP/TFTP protocol, example: rktest eth dhcp 0x62000000 192.168.1.100:Image\n");
}

int do_test_eth(cmd_tbl_t *cmdtp, int flag, int argc, char *const argv[])
{
	struct udevice *current;
	u32 tx_delay, rx_delay;
	char cmd_eth[512] = "dhcp $kernel_addr_r 172.16.12.246:golden/arm/rootfs.cpio.gz";
	int i, speed;
	int ret;

	current = eth_get_dev();
	if (!current || !device_active(current))
		return -EINVAL;

	switch (argc) {
	case 2:
		if (!strncmp(argv[2], "delaytest", sizeof("delaytest"))) {
			/* Force 1000 speed test */
			speed = LOOPBACK_SPEED_1000;
			ret = eth_loopback_test(speed, 1);
			return ret;
		} else if (!strncmp(argv[2], "help", sizeof("help"))) {
			do_eth_help();
			return 0;
		}
		break;
	case 3:
		if (!strncmp(argv[2], "loopback", sizeof("loopback"))) {
			speed = simple_strtoul(argv[3], NULL, 0);
			ret = eth_loopback_test(speed, 0);
			return ret;
		}
		break;
	case 4:
		if (!strncmp(argv[2], "delayline", sizeof("delayline"))) {
			tx_delay = simple_strtoul(argv[3], NULL, 0);
			rx_delay = simple_strtoul(argv[4], NULL, 0);
#ifdef CONFIG_RKIMG_BOOTLOADER
			gmac_set_rgmii(current, tx_delay, rx_delay);
#endif
			return 0;
		}
		break;
	default:
		break;
	}

	for (i = 1; i < argc; i++) {
		if (i == 1)
			sprintf(cmd_eth, argv[i]);
		else
			strncat(cmd_eth, argv[i], sizeof(argv[i]));
		if (i < argc - 1)
			strncat(cmd_eth, " ", sizeof(" "));
	}

	/* run dhcp/tftp test */
	ret = run_command(cmd_eth, 0);
	if (ret) {
		printf("DHCP test error: %d\n", ret);
		return ret;
	}

	return 0;
}
#endif

static cmd_tbl_t sub_cmd[] = {
#ifdef CONFIG_GMAC_ROCKCHIP
	UNIT_CMD_DEFINE(eth, 0),
#endif
};

static const char sub_cmd_help[] =
#ifdef CONFIG_GMAC_ROCKCHIP
"    [i] rktest eth                         - test ethernet\n"
#else
""
#endif
;

struct cmd_group cmd_grp_net = {
	.id	= TEST_ID_NET,
	.help	= sub_cmd_help,
	.cmd	= sub_cmd,
	.cmd_n	= ARRAY_SIZE(sub_cmd),
};
