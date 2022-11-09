/*
 * (C) Copyright 2008-2017 Fuzhou Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __ROCKCHIP_MIPI_DSI_H__
#define __ROCKCHIP_MIPI_DSI_H__

#define BIT(nr)			(1UL << (nr))

/* request ACK from peripheral */
#define MIPI_DSI_MSG_REQ_ACK	BIT(0)
/* use Low Power Mode to transmit message */
#define MIPI_DSI_MSG_USE_LPM	BIT(1)

/* DSI mode flags */

/* video mode */
#define MIPI_DSI_MODE_VIDEO		BIT(0)
/* video burst mode */
#define MIPI_DSI_MODE_VIDEO_BURST	BIT(1)
/* video pulse mode */
#define MIPI_DSI_MODE_VIDEO_SYNC_PULSE	BIT(2)
/* enable auto vertical count mode */
#define MIPI_DSI_MODE_VIDEO_AUTO_VERT	BIT(3)
/* enable hsync-end packets in vsync-pulse and v-porch area */
#define MIPI_DSI_MODE_VIDEO_HSE		BIT(4)
/* disable hfront-porch area */
#define MIPI_DSI_MODE_VIDEO_HFP		BIT(5)
/* disable hback-porch area */
#define MIPI_DSI_MODE_VIDEO_HBP		BIT(6)
/* disable hsync-active area */
#define MIPI_DSI_MODE_VIDEO_HSA		BIT(7)
/* flush display FIFO on vsync pulse */
#define MIPI_DSI_MODE_VSYNC_FLUSH	BIT(8)
/* disable EoT packets in HS mode */
#define MIPI_DSI_MODE_EOT_PACKET	BIT(9)
/* device supports non-continuous clock behavior (DSI spec 5.6.1) */
#define MIPI_DSI_CLOCK_NON_CONTINUOUS	BIT(10)
/* transmit data in low power */
#define MIPI_DSI_MODE_LPM		BIT(11)

#define MIPI_DSI_DCS_POWER_MODE_DISPLAY	BIT(2)
#define MIPI_DSI_DCS_POWER_MODE_NORMAL	BIT(3)
#define MIPI_DSI_DCS_POWER_MODE_SLEEP	BIT(4)
#define MIPI_DSI_DCS_POWER_MODE_PARTIAL	BIT(5)
#define MIPI_DSI_DCS_POWER_MODE_IDLE	BIT(6)

#define MIPI_DSI_FMT_RGB888		0
#define MIPI_DSI_FMT_RGB666		1
#define MIPI_DSI_FMT_RGB666_PACKED	2
#define MIPI_DSI_FMT_RGB565		3

#endif /* __ROCKCHIP_MIPI_DSI__ */
