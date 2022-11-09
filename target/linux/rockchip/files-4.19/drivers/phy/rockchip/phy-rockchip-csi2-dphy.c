// SPDX-License-Identifier: GPL-2.0
/*
 * Rockchip MIPI CSI2 DPHY driver
 *
 * Copyright (C) 2021 Rockchip Electronics Co., Ltd.
 */

#include <linux/clk.h>
#include <linux/delay.h>
#include <linux/io.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/of_graph.h>
#include <linux/of_platform.h>
#include <linux/platform_device.h>
#include <linux/pm_runtime.h>
#include <linux/regmap.h>
#include <linux/mfd/syscon.h>
#include <media/media-entity.h>
#include <media/v4l2-ctrls.h>
#include <media/v4l2-fwnode.h>
#include <media/v4l2-subdev.h>
#include <media/v4l2-device.h>
#include "phy-rockchip-csi2-dphy-common.h"

struct sensor_async_subdev {
	struct v4l2_async_subdev asd;
	struct v4l2_mbus_config mbus;
	int lanes;
};

static DEFINE_MUTEX(csi2dphy_dev_mutex);
static LIST_HEAD(csi2dphy_device_list);

static inline struct csi2_dphy *to_csi2_dphy(struct v4l2_subdev *subdev)
{
	return container_of(subdev, struct csi2_dphy, sd);
}

static struct v4l2_subdev *get_remote_sensor(struct v4l2_subdev *sd)
{
	struct media_pad *local, *remote;
	struct media_entity *sensor_me;

	local = &sd->entity.pads[CSI2_DPHY_RX_PAD_SINK];
	remote = media_entity_remote_pad(local);
	if (!remote) {
		v4l2_warn(sd, "No link between dphy and sensor\n");
		return NULL;
	}

	sensor_me = media_entity_remote_pad(local)->entity;
	return media_entity_to_v4l2_subdev(sensor_me);
}

static struct csi2_sensor *sd_to_sensor(struct csi2_dphy *dphy,
					   struct v4l2_subdev *sd)
{
	int i;

	for (i = 0; i < dphy->num_sensors; ++i)
		if (dphy->sensors[i].sd == sd)
			return &dphy->sensors[i];

	return NULL;
}

static int csi2_dphy_get_sensor_data_rate(struct v4l2_subdev *sd)
{
	struct csi2_dphy *dphy = to_csi2_dphy(sd);
	struct v4l2_subdev *sensor_sd = get_remote_sensor(sd);
	struct v4l2_ctrl *link_freq;
	struct v4l2_querymenu qm = { .id = V4L2_CID_LINK_FREQ, };
	int ret;

	link_freq = v4l2_ctrl_find(sensor_sd->ctrl_handler, V4L2_CID_LINK_FREQ);
	if (!link_freq) {
		v4l2_warn(sd, "No pixel rate control in subdev\n");
		return -EPIPE;
	}

	qm.index = v4l2_ctrl_g_ctrl(link_freq);
	ret = v4l2_querymenu(sensor_sd->ctrl_handler, &qm);
	if (ret < 0) {
		v4l2_err(sd, "Failed to get menu item\n");
		return ret;
	}

	if (!qm.value) {
		v4l2_err(sd, "Invalid link_freq\n");
		return -EINVAL;
	}
	dphy->data_rate_mbps = qm.value * 2;
	do_div(dphy->data_rate_mbps, 1000 * 1000);
	v4l2_info(sd, "dphy%d, data_rate_mbps %lld\n",
		  dphy->phy_index, dphy->data_rate_mbps);
	return 0;
}

static int csi2_dphy_update_sensor_mbus(struct v4l2_subdev *sd)
{
	struct csi2_dphy *dphy = to_csi2_dphy(sd);
	struct v4l2_subdev *sensor_sd = get_remote_sensor(sd);
	struct csi2_sensor *sensor = sd_to_sensor(dphy, sensor_sd);
	struct v4l2_mbus_config mbus;
	int ret;

	ret = v4l2_subdev_call(sensor_sd, video, g_mbus_config, &mbus);
	if (ret)
		return ret;

	sensor->mbus = mbus;
	switch (mbus.flags & V4L2_MBUS_CSI2_LANES) {
	case V4L2_MBUS_CSI2_1_LANE:
		sensor->lanes = 1;
		break;
	case V4L2_MBUS_CSI2_2_LANE:
		sensor->lanes = 2;
		break;
	case V4L2_MBUS_CSI2_3_LANE:
		sensor->lanes = 3;
		break;
	case V4L2_MBUS_CSI2_4_LANE:
		sensor->lanes = 4;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}

static int csi2_dphy_s_stream_start(struct v4l2_subdev *sd)
{
	struct csi2_dphy *dphy = to_csi2_dphy(sd);
	struct csi2_dphy_hw *hw = dphy->dphy_hw;
	int  ret = 0;

	if (dphy->is_streaming)
		return 0;

	ret = csi2_dphy_get_sensor_data_rate(sd);
	if (ret < 0)
		return ret;

	csi2_dphy_update_sensor_mbus(sd);

	if (hw->stream_on)
		hw->stream_on(dphy, sd);

	dphy->is_streaming = true;

	return 0;
}

static int csi2_dphy_s_stream_stop(struct v4l2_subdev *sd)
{
	struct csi2_dphy *dphy = to_csi2_dphy(sd);
	struct csi2_dphy_hw *hw = dphy->dphy_hw;

	if (!dphy->is_streaming)
		return 0;

	if (hw->stream_off)
		hw->stream_off(dphy, sd);

	dphy->is_streaming = false;

	dev_info(dphy->dev, "%s stream stop, dphy%d\n",
		 __func__, dphy->phy_index);

	return 0;
}

static int csi2_dphy_s_stream(struct v4l2_subdev *sd, int on)
{
	struct csi2_dphy *dphy = to_csi2_dphy(sd);
	int ret = 0;

	mutex_lock(&dphy->mutex);
	if (on)
		ret = csi2_dphy_s_stream_start(sd);
	else
		ret = csi2_dphy_s_stream_stop(sd);
	mutex_unlock(&dphy->mutex);

	dev_info(dphy->dev, "%s stream on:%d, dphy%d\n",
		 __func__, on, dphy->phy_index);

	return ret;
}

static int csi2_dphy_g_frame_interval(struct v4l2_subdev *sd,
					    struct v4l2_subdev_frame_interval *fi)
{
	struct v4l2_subdev *sensor = get_remote_sensor(sd);

	if (sensor)
		return v4l2_subdev_call(sensor, video, g_frame_interval, fi);

	return -EINVAL;
}

static int csi2_dphy_g_mbus_config(struct v4l2_subdev *sd,
				  struct v4l2_mbus_config *config)
{
	struct csi2_dphy *dphy = to_csi2_dphy(sd);
	struct v4l2_subdev *sensor_sd = get_remote_sensor(sd);
	struct csi2_sensor *sensor;

	if (!sensor_sd)
		return -ENODEV;
	sensor = sd_to_sensor(dphy, sensor_sd);
	csi2_dphy_update_sensor_mbus(sd);
	*config = sensor->mbus;

	return 0;
}

static int csi2_dphy_s_power(struct v4l2_subdev *sd, int on)
{
	struct csi2_dphy *dphy = to_csi2_dphy(sd);

	if (on)
		return pm_runtime_get_sync(dphy->dev);
	else
		return pm_runtime_put(dphy->dev);
}

static __maybe_unused int csi2_dphy_runtime_suspend(struct device *dev)
{
	struct media_entity *me = dev_get_drvdata(dev);
	struct v4l2_subdev *sd = media_entity_to_v4l2_subdev(me);
	struct csi2_dphy *dphy = to_csi2_dphy(sd);
	struct csi2_dphy_hw *hw = dphy->dphy_hw;

	if (hw)
		clk_bulk_disable_unprepare(hw->num_clks, hw->clks);

	return 0;
}

static __maybe_unused int csi2_dphy_runtime_resume(struct device *dev)
{
	struct media_entity *me = dev_get_drvdata(dev);
	struct v4l2_subdev *sd = media_entity_to_v4l2_subdev(me);
	struct csi2_dphy *dphy = to_csi2_dphy(sd);
	struct csi2_dphy_hw *hw = dphy->dphy_hw;
	int ret;

	if (hw) {
		ret = clk_bulk_prepare_enable(hw->num_clks, hw->clks);
		if (ret) {
			dev_err(hw->dev, "failed to enable clks\n");
			return ret;
		}
	}

	return 0;
}

/* dphy accepts all fmt/size from sensor */
static int csi2_dphy_get_set_fmt(struct v4l2_subdev *sd,
				struct v4l2_subdev_pad_config *cfg,
				struct v4l2_subdev_format *fmt)
{
	struct csi2_dphy *dphy = to_csi2_dphy(sd);
	struct v4l2_subdev *sensor_sd = get_remote_sensor(sd);
	struct csi2_sensor *sensor = sd_to_sensor(dphy, sensor_sd);
	int ret;
	/*
	 * Do not allow format changes and just relay whatever
	 * set currently in the sensor.
	 */
	if (!sensor_sd)
		return -ENODEV;
	ret = v4l2_subdev_call(sensor_sd, pad, get_fmt, NULL, fmt);
	if (!ret && fmt->pad == 0)
		sensor->format = fmt->format;
	return ret;
}

static int csi2_dphy_get_selection(struct v4l2_subdev *sd,
				  struct v4l2_subdev_pad_config *cfg,
				  struct v4l2_subdev_selection *sel)
{
	struct v4l2_subdev *sensor = get_remote_sensor(sd);

	return v4l2_subdev_call(sensor, pad, get_selection, NULL, sel);
}

static const struct v4l2_subdev_core_ops csi2_dphy_core_ops = {
	.s_power = csi2_dphy_s_power,
};

static const struct v4l2_subdev_video_ops csi2_dphy_video_ops = {
	.g_frame_interval = csi2_dphy_g_frame_interval,
	.g_mbus_config = csi2_dphy_g_mbus_config,
	.s_stream = csi2_dphy_s_stream,
};

static const struct v4l2_subdev_pad_ops csi2_dphy_subdev_pad_ops = {
	.set_fmt = csi2_dphy_get_set_fmt,
	.get_fmt = csi2_dphy_get_set_fmt,
	.get_selection = csi2_dphy_get_selection,
};

static const struct v4l2_subdev_ops csi2_dphy_subdev_ops = {
	.core = &csi2_dphy_core_ops,
	.video = &csi2_dphy_video_ops,
	.pad = &csi2_dphy_subdev_pad_ops,
};

/* The .bound() notifier callback when a match is found */
static int
rockchip_csi2_dphy_notifier_bound(struct v4l2_async_notifier *notifier,
					   struct v4l2_subdev *sd,
					   struct v4l2_async_subdev *asd)
{
	struct csi2_dphy *dphy = container_of(notifier,
					      struct csi2_dphy,
					      notifier);
	struct sensor_async_subdev *s_asd = container_of(asd,
					struct sensor_async_subdev, asd);
	struct csi2_sensor *sensor;
	unsigned int pad, ret;

	if (dphy->num_sensors == ARRAY_SIZE(dphy->sensors))
		return -EBUSY;

	sensor = &dphy->sensors[dphy->num_sensors++];
	sensor->lanes = s_asd->lanes;
	sensor->mbus = s_asd->mbus;
	sensor->sd = sd;

	dev_info(dphy->dev, "dphy%d matches %s:bus type %d\n",
		 dphy->phy_index, sd->name, s_asd->mbus.type);

	for (pad = 0; pad < sensor->sd->entity.num_pads; pad++)
		if (sensor->sd->entity.pads[pad].flags & MEDIA_PAD_FL_SOURCE)
			break;

	if (pad == sensor->sd->entity.num_pads) {
		dev_err(dphy->dev,
			"failed to find src pad for %s\n",
			sensor->sd->name);

		return -ENXIO;
	}

	ret = media_create_pad_link(
			&sensor->sd->entity, pad,
			&dphy->sd.entity, CSI2_DPHY_RX_PAD_SINK,
			dphy->num_sensors != 1 ? 0 : MEDIA_LNK_FL_ENABLED);
	if (ret) {
		dev_err(dphy->dev,
			"failed to create link for %s\n",
			sensor->sd->name);
		return ret;
	}

	return 0;
}

/* The .unbind callback */
static void
rockchip_csi2_dphy_notifier_unbind(struct v4l2_async_notifier *notifier,
				  struct v4l2_subdev *sd,
				  struct v4l2_async_subdev *asd)
{
	struct csi2_dphy *dphy = container_of(notifier,
						  struct csi2_dphy,
						  notifier);
	struct csi2_sensor *sensor = sd_to_sensor(dphy, sd);

	sensor->sd = NULL;
}

static const struct
v4l2_async_notifier_operations rockchip_csi2_dphy_async_ops = {
	.bound = rockchip_csi2_dphy_notifier_bound,
	.unbind = rockchip_csi2_dphy_notifier_unbind,
};

static int rockchip_csi2_dphy_fwnode_parse(struct device *dev,
					  struct v4l2_fwnode_endpoint *vep,
					  struct v4l2_async_subdev *asd)
{
	struct sensor_async_subdev *s_asd =
			container_of(asd, struct sensor_async_subdev, asd);
	struct v4l2_mbus_config *config = &s_asd->mbus;

	if (vep->base.port != 0) {
		dev_err(dev, "The PHY has only port 0\n");
		return -EINVAL;
	}

	if (vep->bus_type == V4L2_MBUS_CSI2) {
		config->type = V4L2_MBUS_CSI2;
		config->flags = vep->bus.mipi_csi2.flags;
		s_asd->lanes = vep->bus.mipi_csi2.num_data_lanes;
	} else {
		dev_err(dev, "Only CSI2 type is currently supported\n");
		return -EINVAL;
	}

	switch (s_asd->lanes) {
	case 1:
		config->flags |= V4L2_MBUS_CSI2_1_LANE;
		break;
	case 2:
		config->flags |= V4L2_MBUS_CSI2_2_LANE;
		break;
	case 3:
		config->flags |= V4L2_MBUS_CSI2_3_LANE;
		break;
	case 4:
		config->flags |= V4L2_MBUS_CSI2_4_LANE;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}

static int rockchip_csi2dphy_media_init(struct csi2_dphy *dphy)
{
	int ret;

	dphy->pads[CSI2_DPHY_RX_PAD_SOURCE].flags =
		MEDIA_PAD_FL_SOURCE | MEDIA_PAD_FL_MUST_CONNECT;
	dphy->pads[CSI2_DPHY_RX_PAD_SINK].flags =
		MEDIA_PAD_FL_SINK | MEDIA_PAD_FL_MUST_CONNECT;
	dphy->sd.entity.function = MEDIA_ENT_F_VID_IF_BRIDGE;
	ret = media_entity_pads_init(&dphy->sd.entity,
				CSI2_DPHY_RX_PADS_NUM, dphy->pads);
	if (ret < 0)
		return ret;

	ret = v4l2_async_notifier_parse_fwnode_endpoints_by_port(
		dphy->dev, &dphy->notifier,
		sizeof(struct sensor_async_subdev), 0,
		rockchip_csi2_dphy_fwnode_parse);
	if (ret < 0)
		return ret;

	if (!dphy->notifier.num_subdevs)
		return -ENODEV;	/* no endpoint */

	dphy->sd.subdev_notifier = &dphy->notifier;
	dphy->notifier.ops = &rockchip_csi2_dphy_async_ops;
	ret = v4l2_async_subdev_notifier_register(&dphy->sd, &dphy->notifier);
	if (ret) {
		dev_err(dphy->dev,
			"failed to register async notifier : %d\n", ret);
		v4l2_async_notifier_cleanup(&dphy->notifier);
		return ret;
	}

	return v4l2_async_register_subdev(&dphy->sd);
}

static int rockchip_csi2_dphy_attach_hw(struct csi2_dphy *dphy)
{
	struct platform_device *plat_dev;
	struct device *dev = dphy->dev;
	struct csi2_dphy_hw *dphy_hw;
	struct device_node *np;
	enum csi2_dphy_lane_mode target_mode;
	int i;

	if (dphy->phy_index == 0)
		target_mode = LANE_MODE_FULL;
	else
		target_mode = LANE_MODE_SPLIT;

	np = of_parse_phandle(dev->of_node, "rockchip,hw", 0);
	if (!np || !of_device_is_available(np)) {
		dev_err(dphy->dev,
			"failed to get dphy%d hw node\n", dphy->phy_index);
		return -ENODEV;
	}

	plat_dev = of_find_device_by_node(np);
	of_node_put(np);
	if (!plat_dev) {
		dev_err(dphy->dev,
			"failed to get dphy%d hw from node\n",
			dphy->phy_index);
		return -ENODEV;
	}

	dphy_hw = platform_get_drvdata(plat_dev);
	if (!dphy_hw) {
		dev_err(dphy->dev,
			"failed attach dphy%d hw\n",
			dphy->phy_index);
		return -EINVAL;
	}

	if (dphy_hw->lane_mode == LANE_MODE_UNDEF) {
		dphy_hw->lane_mode = target_mode;
	} else {
		struct csi2_dphy *phy = dphy_hw->dphy_dev[0];

		for (i = 0; i < dphy_hw->dphy_dev_num; i++) {
			if (dphy_hw->dphy_dev[i]->lane_mode == dphy_hw->lane_mode) {
				phy = dphy_hw->dphy_dev[i];
				break;
			}
		}

		if (target_mode != dphy_hw->lane_mode) {
			dev_err(dphy->dev,
				"Err:csi2 dphy hw has been set as %s mode by phy%d, target mode is:%s\n",
				dphy_hw->lane_mode == LANE_MODE_FULL ? "full" : "split",
				phy->phy_index,
				target_mode == LANE_MODE_FULL ? "full" : "split");
			return -ENODEV;
		}
	}

	dphy_hw->dphy_dev[dphy_hw->dphy_dev_num] = dphy;
	dphy_hw->dphy_dev_num++;
	dphy->dphy_hw = dphy_hw;

	return 0;
}

static int rockchip_csi2_dphy_detach_hw(struct csi2_dphy *dphy)
{
	struct csi2_dphy_hw *dphy_hw = dphy->dphy_hw;
	struct csi2_dphy *csi2_dphy = NULL;
	int i;

	for (i = 0; i < dphy_hw->dphy_dev_num; i++) {
		csi2_dphy = dphy_hw->dphy_dev[i];
		if (csi2_dphy &&
		    csi2_dphy->phy_index == dphy->phy_index) {
			dphy_hw->dphy_dev[i] = NULL;
			dphy_hw->dphy_dev_num--;
			break;
		}
	}

	return 0;
}

static const struct of_device_id rockchip_csi2_dphy_match_id[] = {
	{
		.compatible = "rockchip,rk3568-csi2-dphy",
	},
	{}
};
MODULE_DEVICE_TABLE(of, rockchip_csi2_dphy_match_id);

static int rockchip_csi2_dphy_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	const struct of_device_id *of_id;
	struct csi2_dphy *csi2dphy;
	struct v4l2_subdev *sd;
	int ret;

	csi2dphy = devm_kzalloc(dev, sizeof(*csi2dphy), GFP_KERNEL);
	if (!csi2dphy)
		return -ENOMEM;
	csi2dphy->dev = dev;

	of_id = of_match_device(rockchip_csi2_dphy_match_id, dev);
	if (!of_id)
		return -EINVAL;

	csi2dphy->phy_index = of_alias_get_id(dev->of_node, "csi2dphy");
	if (csi2dphy->phy_index < 0 || csi2dphy->phy_index > 2)
		csi2dphy->phy_index = 0;

	ret = rockchip_csi2_dphy_attach_hw(csi2dphy);
	if (ret) {
		dev_err(dev,
			"csi2 dphy hw can't be attached, register dphy%d failed!\n",
			csi2dphy->phy_index);
		return -ENODEV;
	}

	sd = &csi2dphy->sd;
	mutex_init(&csi2dphy->mutex);
	v4l2_subdev_init(sd, &csi2_dphy_subdev_ops);
	sd->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	snprintf(sd->name, sizeof(sd->name),
		 "rockchip-csi2-dphy%d", csi2dphy->phy_index);
	sd->dev = dev;

	platform_set_drvdata(pdev, &sd->entity);

	ret = rockchip_csi2dphy_media_init(csi2dphy);
	if (ret < 0)
		goto detach_hw;

	pm_runtime_enable(&pdev->dev);

	dev_info(dev, "csi2 dphy%d probe successfully!\n", csi2dphy->phy_index);

	return 0;

detach_hw:
	mutex_destroy(&csi2dphy->mutex);
	rockchip_csi2_dphy_detach_hw(csi2dphy);

	return 0;
}

static int rockchip_csi2_dphy_remove(struct platform_device *pdev)
{
	struct media_entity *me = platform_get_drvdata(pdev);
	struct v4l2_subdev *sd = media_entity_to_v4l2_subdev(me);
	struct csi2_dphy *dphy = to_csi2_dphy(sd);

	media_entity_cleanup(&sd->entity);

	pm_runtime_disable(&pdev->dev);
	mutex_destroy(&dphy->mutex);
	return 0;
}
static int __maybe_unused __rockchip_csi2dphy_clr_unready_dev(void)
{
	struct csi2_dphy *csi2dphy;

	mutex_lock(&csi2dphy_dev_mutex);
	list_for_each_entry(csi2dphy, &csi2dphy_device_list, list)
		v4l2_async_notifier_clr_unready_dev(&csi2dphy->notifier);
	mutex_unlock(&csi2dphy_dev_mutex);

	return 0;
}

static int rockchip_csi2dphy_clr_unready_dev_param_set(const char *val,
						       const struct kernel_param *kp)
{
#ifdef MODULE
	__rockchip_csi2dphy_clr_unready_dev();
#endif

	return 0;
}

module_param_call(clr_unready_dev,
		  rockchip_csi2dphy_clr_unready_dev_param_set,
		  NULL, NULL, 0200);
MODULE_PARM_DESC(clr_unready_dev, "clear unready devices");

#ifndef MODULE
static int __init rockchip_csi2_dphy_clr_unready_dev(void)
{
	__rockchip_csi2dphy_clr_unready_dev();

	return 0;
}
late_initcall_sync(rockchip_csi2_dphy_clr_unready_dev);
#endif

static const struct dev_pm_ops rockchip_csi2_dphy_pm_ops = {
	SET_RUNTIME_PM_OPS(csi2_dphy_runtime_suspend,
			   csi2_dphy_runtime_resume, NULL)
};

struct platform_driver rockchip_csi2_dphy_driver = {
	.probe = rockchip_csi2_dphy_probe,
	.remove = rockchip_csi2_dphy_remove,
	.driver = {
		.name = "rockchip-csi2-dphy",
		.pm = &rockchip_csi2_dphy_pm_ops,
		.of_match_table = rockchip_csi2_dphy_match_id,
	},
};
EXPORT_SYMBOL(rockchip_csi2_dphy_driver);

MODULE_AUTHOR("Rockchip Camera/ISP team");
MODULE_DESCRIPTION("Rockchip MIPI CSI2 DPHY driver");
MODULE_LICENSE("GPL v2");
