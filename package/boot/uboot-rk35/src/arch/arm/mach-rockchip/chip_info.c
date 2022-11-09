/*
 * (C) Copyright 2022 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <common.h>
#include <asm/arch-rockchip/chip_info.h>

/*
 * rk3066 chip info:	{0x33303041, 0x32303131, 0x31313131, 0x56313031} - 300A20111111V101
 * rk3168 chip info:	{0x33303042, 0x32303132, 0x31303031, 0x56313030} - 300B20121011V100
 * rk3036 chip info:	{0x33303141, 0x32303134, 0x30343231, 0x56313031} - 301A20140421V101
 * rk3188 chip info:	{0x33313042, 0x32303132, 0x31313330, 0x56313030} - 310B20121130V100
 * rk3188_plus chip info:{0x33313042, 0x32303133, 0x30313331, 0x56313031} - 310B20130131V101
 * rk312x chip info:	{0x33313043, 0x32303134, 0x30343239, 0x56313030} - 310C20140429V100
 * rk312xb chip info:	{0x33313044, 0x32303134, 0x30373330, 0x56313030} - 310D20140730V100
 * rk3126c chip info:	{0x33313044, 0x32303137, 0x30343137, 0x56323030} - 310D20170417V200
 * rk3288 chip info:	{0x33323041, 0x32303133, 0x31313136, 0x56313030} - 320A20131116V100
 * rk322x chip info:	{0x33323042, 0x32303135, 0x31313136, 0x56313030} - 320B20151116V100
 * rk3368 chip info:	{0x33333041, 0x32303134, 0x30393238, 0x56313030} - 330A20140928V100
 * rk3366 chip info:	{0x33333042, 0x32303135, 0x30363234, 0x56313030} - 330B20150624V100
 * rk3399 chip info:	{0x33333043, 0x32303136, 0x30313138, 0x56313030} - 330B20160118V100
 * rk322xh chip info:	{0x33323043, 0x32303136, 0x31313031, 0x56313030} - 320C20161101V100
 * rk3326 chip info:	{0x33333044, 0x32303137, 0x31323134, 0x56313030} - 330D20171214V100
 * rk3308 chip info:	{0x33333045, 0x32303138, 0x30323033, 0x56313030} - 330E20180203V100
 * rv1126 chip info:	{0x42303131, 0x39313032, 0x37303131, 0x30303156}
 */

static int rockchip_get_chip_info(unsigned int chip_info[])
{
	if (chip_info == NULL)
		return -EINVAL;

#if defined(CONFIG_ROCKCHIP_RK3036)
	chip_info[0] = 0x33303041;
#elif defined(CONFIG_ROCKCHIP_RK3188)
	chip_info[0] = 0x33313042;
#elif defined(CONFIG_ROCKCHIP_RK3126)
	chip_info[0] = 0x33313044;
#elif defined(CONFIG_ROCKCHIP_RK322X)
	chip_info[0] = 0x33323042;
#elif defined(CONFIG_ROCKCHIP_RK3288)
	chip_info[0] = 0x33323041;
#elif defined(CONFIG_ROCKCHIP_RK3308)
	chip_info[0] = 0x33333038;
#elif defined(CONFIG_ROCKCHIP_RK3328)
	chip_info[0] = 0x33323043;
	chip_info[3] = 0x56313030;
#elif defined(CONFIG_ROCKCHIP_RK3368)
	chip_info[0] = 0x33333041;
	chip_info[3] = 0x56313030;
#elif defined(CONFIG_ROCKCHIP_RK3399)
	chip_info[0] = 0x33333043;
	chip_info[3] = 0x56313030;

/*
 * Must check CONFIG_ROCKCHIP_RK3326 first! Because RK3326 board defconfig
 * will contains both CONFIG_ROCKCHIP_RK3326 and CONFIG_ROCKCHIP_PX30, we
 * would like treat the board as RK3326.
 */
#elif defined(CONFIG_ROCKCHIP_RK3326)
	chip_info[0] = 0x33333236;
#elif defined(CONFIG_ROCKCHIP_PX30)
	chip_info[0] = 0x50583330;
#elif defined(CONFIG_ROCKCHIP_RK3568)
	chip_info[0] = 0x33353638;
#elif defined(CONFIG_ROCKCHIP_RK3588)
	chip_info[0] = 0x33353838;
#endif

	return 0;
}

int rockchip_rockusb_get_chip_info(unsigned int chip_info[])
{
	int err;

	err = rockchip_get_chip_info(chip_info);
	if (!err) {
	/* Fixup chip info for RockUsb */
#if defined(CONFIG_ROCKCHIP_RK3036)
		chip_info[0] = 0x33303341;
#elif defined(CONFIG_ROCKCHIP_RK3126) || defined(CONFIG_ROCKCHIP_RK3128)
		chip_info[0] = 0x33313241;
#elif defined(CONFIG_ROCKCHIP_RK322X)
#if defined(CONFIG_ROCKCHIP_RK3128X)
		chip_info[0] = 0x33313258;
#else
		chip_info[0] = 0x33323241;
#endif
#elif defined(CONFIG_ROCKCHIP_RK3328)
		chip_info[0] = 0x33323248;
#elif defined(CONFIG_ROCKCHIP_RK3399)
		chip_info[0] = 0x33333043;
#elif defined(CONFIG_ROCKCHIP_RK1808)
		chip_info[0] = 0x31383041;
#elif defined(CONFIG_ROCKCHIP_RV1126)
		chip_info[0] = 0x31313236;
#elif defined(CONFIG_ROCKCHIP_RV1106)
		chip_info[0] = 0x31313036;
#endif
	}

	return err;
}
