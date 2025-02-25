// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
 * Author: Finley Xiao <finley.xiao@rock-chips.com>
 */

#include <linux/clk-provider.h>
#include <linux/cpu.h>
#include <linux/cpufreq.h>
#include <linux/devfreq.h>
#include <linux/device.h>
#include <linux/ebc.h>
#include <linux/fb.h>
#include <linux/module.h>
#include <linux/mutex.h>
#include <linux/notifier.h>
#include <linux/of.h>
#include <linux/platform_device.h>
#include <linux/pm_opp.h>
#include <linux/pm_qos.h>
#include <linux/pm_runtime.h>
#include <linux/property.h>
#include <linux/regulator/consumer.h>
#include <linux/regulator/coupler.h>
#include <linux/regulator/driver.h>
#include <linux/regulator/machine.h>
#include <linux/reboot.h>
#include <linux/rockchip/rockchip_sip.h>
#include <linux/slab.h>
#include <linux/suspend.h>
#include <linux/thermal.h>
#include <linux/uaccess.h>
#include <linux/version.h>
#include <linux/delay.h>
#include <soc/rockchip/rockchip_opp_select.h>
#include <soc/rockchip/rockchip_sip.h>
#include <soc/rockchip/rockchip_system_monitor.h>
#include <soc/rockchip/rockchip-system-status.h>
#ifdef CONFIG_ROCKCHIP_EARLYSUSPEND
#include <linux/earlysuspend.h>
#endif

#include "../../opp/opp.h"
#include "../../regulator/internal.h"
#include "../../thermal/thermal_core.h"

#define CPU_REBOOT_FREQ		816000 /* kHz */
#define VIDEO_1080P_SIZE	(1920 * 1080)
#define THERMAL_POLLING_DELAY	200 /* milliseconds */

struct video_info {
	unsigned int width;
	unsigned int height;
	unsigned int ishevc;
	unsigned int videoFramerate;
	unsigned int streamBitrate;
	struct list_head node;
};

struct system_monitor_attr {
	struct attribute attr;
	ssize_t (*show)(struct kobject *kobj, struct kobj_attribute *attr,
			char *buf);
	ssize_t (*store)(struct kobject *kobj, struct kobj_attribute *attr,
			 const char *buf, size_t n);
};

struct system_monitor {
	struct device *dev;
	struct cpumask early_suspend_offline_cpus;
	struct cpumask video_4k_offline_cpus;
	struct cpumask status_offline_cpus;
	struct cpumask temp_offline_cpus;
	struct cpumask offline_cpus;
	struct notifier_block status_nb;
	struct kobject *kobj;

	struct thermal_zone_device *tz;
	struct delayed_work thermal_work;
	struct temp_freq_table *temp_ddr_ref_mode;
	int last_temp;
	int offline_cpus_temp;
	int temp_hysteresis;
	unsigned int delay;
	bool is_temp_offline;

	int (*ddr_trefi_update)(u32 ref_mode);
};

static unsigned long system_status;
static unsigned long ref_count[32] = {0};

static DEFINE_MUTEX(system_status_mutex);
static DEFINE_MUTEX(video_info_mutex);
static DEFINE_MUTEX(cpu_on_off_mutex);

static DECLARE_RWSEM(mdev_list_sem);

static LIST_HEAD(video_info_list);
static LIST_HEAD(monitor_dev_list);
static struct system_monitor *system_monitor;
static atomic_t monitor_in_suspend;

static BLOCKING_NOTIFIER_HEAD(system_monitor_notifier_list);
static BLOCKING_NOTIFIER_HEAD(system_status_notifier_list);

#ifdef CONFIG_ROCKCHIP_EARLYSUSPEND
static DEFINE_MUTEX(early_suspend_mutex);
static LIST_HEAD(early_suspend_list);
static bool is_early_suspend;

static bool early_suspend_debug;
module_param(early_suspend_debug, bool, 0644);

void register_early_suspend(struct early_suspend *handler)
{
	struct list_head *pos;

	if (!handler)
		return;

	mutex_lock(&early_suspend_mutex);
	list_for_each(pos, &early_suspend_list) {
		struct early_suspend *tmp;

		tmp = list_entry(pos, struct early_suspend, link);
		if (tmp->level > handler->level)
			break;
	}
	list_add_tail(&handler->link, pos);
	mutex_unlock(&early_suspend_mutex);
}
EXPORT_SYMBOL(register_early_suspend);

void unregister_early_suspend(struct early_suspend *handler)
{
	if (!handler)
		return;

	mutex_lock(&early_suspend_mutex);
	list_del(&handler->link);
	mutex_unlock(&early_suspend_mutex);
}
EXPORT_SYMBOL(unregister_early_suspend);

void rockchip_request_early_suspend(void)
{
	struct early_suspend *pos;

	mutex_lock(&early_suspend_mutex);
	if (is_early_suspend)
		goto unlock;
	list_for_each_entry(pos, &early_suspend_list, link) {
		if (pos->suspend != NULL) {
			bool debug = early_suspend_debug;
			ktime_t calltime, rettime;

			if (debug) {
				printk(KERN_DEBUG "early_suspend: calling %pS\n", pos->suspend);
				calltime = ktime_get();
			}
			pos->suspend(pos);
			if (debug) {
				rettime = ktime_get();
				printk(KERN_DEBUG "early_suspend: %pS returned after %lld usecs\n",
				       pos->suspend, ktime_us_delta(rettime, calltime));
			}
		}
	}
	is_early_suspend = true;
unlock:
	mutex_unlock(&early_suspend_mutex);
}
EXPORT_SYMBOL(rockchip_request_early_suspend);

void rockchip_request_late_resume(void)
{
	struct early_suspend *pos;

	mutex_lock(&early_suspend_mutex);
	if (!is_early_suspend)
		goto unlock;
	list_for_each_entry_reverse(pos, &early_suspend_list, link) {
		if (pos->resume != NULL) {
			bool debug = early_suspend_debug;
			ktime_t calltime, rettime;

			if (debug) {
				printk(KERN_DEBUG "late_resume: calling %pS\n", pos->resume);
				calltime = ktime_get();
			}
			pos->resume(pos);
			if (debug) {
				rettime = ktime_get();
				printk(KERN_DEBUG "late_resume: %pS returned after %lld usecs\n",
				       pos->resume, ktime_us_delta(rettime, calltime));
			}
		}
	}
	is_early_suspend = false;
unlock:
	mutex_unlock(&early_suspend_mutex);
}
EXPORT_SYMBOL(rockchip_request_late_resume);

static ssize_t early_suspend_state_show(struct kobject *kobj,
					struct kobj_attribute *attr,
					char *buf)
{
	return sprintf(buf, "%d\n", is_early_suspend);
}

static ssize_t early_suspend_state_store(struct kobject *kobj,
					 struct kobj_attribute *attr,
					 const char *buf, size_t n)
{
	unsigned long val;

	if (!n)
		return -EINVAL;
	if (kstrtoul(buf, 10, &val))
		return -EINVAL;
	if (val > 1)
		return -EINVAL;

	if (val)
		rockchip_request_early_suspend();
	else
		rockchip_request_late_resume();

	return n;
}

static struct system_monitor_attr early_suspend_state =
	__ATTR(early_suspend, 0644, early_suspend_state_show, early_suspend_state_store);
#endif

int rockchip_register_system_status_notifier(struct notifier_block *nb)
{
	return blocking_notifier_chain_register(&system_status_notifier_list,
						nb);
}
EXPORT_SYMBOL(rockchip_register_system_status_notifier);

int rockchip_unregister_system_status_notifier(struct notifier_block *nb)
{
	return blocking_notifier_chain_unregister(&system_status_notifier_list,
						  nb);
}
EXPORT_SYMBOL(rockchip_unregister_system_status_notifier);

static int rockchip_system_status_notifier_call_chain(unsigned long val)
{
	int ret = blocking_notifier_call_chain(&system_status_notifier_list,
					       val, NULL);

	return notifier_to_errno(ret);
}

void rockchip_set_system_status(unsigned long status)
{
	unsigned long old_system_status;
	unsigned int single_status_offset;

	mutex_lock(&system_status_mutex);

	old_system_status = system_status;

	while (status) {
		single_status_offset = fls(status) - 1;
		status &= ~(1 << single_status_offset);
		if (ref_count[single_status_offset] == 0)
			system_status |= 1 << single_status_offset;
		ref_count[single_status_offset]++;
	}

	if (old_system_status != system_status)
		rockchip_system_status_notifier_call_chain(system_status);

	mutex_unlock(&system_status_mutex);
}
EXPORT_SYMBOL(rockchip_set_system_status);

void rockchip_clear_system_status(unsigned long status)
{
	unsigned long old_system_status;
	unsigned int single_status_offset;

	mutex_lock(&system_status_mutex);

	old_system_status = system_status;

	while (status) {
		single_status_offset = fls(status) - 1;
		status &= ~(1 << single_status_offset);
		if (ref_count[single_status_offset] == 0) {
			continue;
		} else {
			if (ref_count[single_status_offset] == 1)
				system_status &= ~(1 << single_status_offset);
			ref_count[single_status_offset]--;
		}
	}

	if (old_system_status != system_status)
		rockchip_system_status_notifier_call_chain(system_status);

	mutex_unlock(&system_status_mutex);
}
EXPORT_SYMBOL(rockchip_clear_system_status);

unsigned long rockchip_get_system_status(void)
{
	return system_status;
}
EXPORT_SYMBOL(rockchip_get_system_status);

int rockchip_add_system_status_interface(struct device *dev)
{
	if (!system_monitor || !system_monitor->kobj) {
		pr_err("failed to get system status kobj\n");
		return -EINVAL;
	}

	return compat_only_sysfs_link_entry_to_kobj(&dev->kobj,
						    system_monitor->kobj,
						    "system_status", NULL);
}
EXPORT_SYMBOL(rockchip_add_system_status_interface);

static unsigned long rockchip_get_video_param(char **str)
{
	char *p;
	unsigned long val = 0;

	strsep(str, "=");
	p = strsep(str, ",");
	if (p) {
		if (kstrtoul(p, 10, &val))
			return 0;
	}

	return val;
}

/*
 * format:
 * 0,width=val,height=val,ishevc=val,videoFramerate=val,streamBitrate=val
 * 1,width=val,height=val,ishevc=val,videoFramerate=val,streamBitrate=val
 */
static struct video_info *rockchip_parse_video_info(const char *buf)
{
	struct video_info *video_info;
	const char *cp = buf;
	char *str, *p;
	int ntokens = 0;

	while ((cp = strpbrk(cp + 1, ",")))
		ntokens++;
	if (ntokens != 5)
		return NULL;

	video_info = kzalloc(sizeof(*video_info), GFP_KERNEL);
	if (!video_info)
		return NULL;

	INIT_LIST_HEAD(&video_info->node);

	str = kstrdup(buf, GFP_KERNEL);
	p = str;
	strsep(&p, ",");
	video_info->width = rockchip_get_video_param(&p);
	video_info->height = rockchip_get_video_param(&p);
	video_info->ishevc = rockchip_get_video_param(&p);
	video_info->videoFramerate = rockchip_get_video_param(&p);
	video_info->streamBitrate = rockchip_get_video_param(&p);
	pr_debug("%c,width=%d,height=%d,ishevc=%d,videoFramerate=%d,streamBitrate=%d\n",
		 buf[0],
		 video_info->width,
		 video_info->height,
		 video_info->ishevc,
		 video_info->videoFramerate,
		 video_info->streamBitrate);
	kfree(str);

	return video_info;
}

static void rockchip_add_video_info(struct video_info *video_info)
{
	if (video_info) {
		mutex_lock(&video_info_mutex);
		list_add(&video_info->node, &video_info_list);
		mutex_unlock(&video_info_mutex);
	}
}

static void rockchip_del_video_info(struct video_info *video_info)
{
	struct video_info *info, *tmp;

	if (!video_info)
		return;

	mutex_lock(&video_info_mutex);
	list_for_each_entry_safe(info, tmp, &video_info_list, node) {
		if (info->width == video_info->width &&
		    info->height == video_info->height &&
		    info->ishevc == video_info->ishevc &&
		    info->videoFramerate == video_info->videoFramerate &&
		    info->streamBitrate == video_info->streamBitrate) {
			list_del(&info->node);
			kfree(info);
			break;
		}
	}
	kfree(video_info);
	mutex_unlock(&video_info_mutex);
}

static void rockchip_update_video_info(void)
{
	struct video_info *video_info;
	unsigned int max_res = 0, max_stream_bitrate = 0, res = 0;
	unsigned int max_video_framerate = 0;

	mutex_lock(&video_info_mutex);
	if (list_empty(&video_info_list)) {
		mutex_unlock(&video_info_mutex);
		rockchip_clear_system_status(SYS_STATUS_VIDEO);
		return;
	}

	list_for_each_entry(video_info, &video_info_list, node) {
		res = video_info->width * video_info->height;
		if (res > max_res)
			max_res = res;
		if (video_info->streamBitrate > max_stream_bitrate)
			max_stream_bitrate = video_info->streamBitrate;
		if (video_info->videoFramerate > max_video_framerate)
			max_video_framerate = video_info->videoFramerate;
	}
	mutex_unlock(&video_info_mutex);

	if (max_res <= VIDEO_1080P_SIZE) {
		rockchip_set_system_status(SYS_STATUS_VIDEO_1080P);
	} else {
		if (max_stream_bitrate == 10)
			rockchip_set_system_status(SYS_STATUS_VIDEO_4K_10B);
		if (max_video_framerate == 60)
			rockchip_set_system_status(SYS_STATUS_VIDEO_4K_60P);
		rockchip_set_system_status(SYS_STATUS_VIDEO_4K);
	}
}

void rockchip_update_system_status(const char *buf)
{
	struct video_info *video_info;

	if (!buf)
		return;

	switch (buf[0]) {
	case '0':
		/* clear video flag */
		video_info = rockchip_parse_video_info(buf);
		if (video_info) {
			rockchip_del_video_info(video_info);
			rockchip_update_video_info();
		}
		break;
	case '1':
		/* set video flag */
		video_info = rockchip_parse_video_info(buf);
		if (video_info) {
			rockchip_add_video_info(video_info);
			rockchip_update_video_info();
		}
		break;
	case 'L':
		/* clear low power flag */
		rockchip_clear_system_status(SYS_STATUS_LOW_POWER);
		break;
	case 'l':
		/* set low power flag */
		rockchip_set_system_status(SYS_STATUS_LOW_POWER);
		break;
	case 'p':
		/* set performance flag */
		rockchip_set_system_status(SYS_STATUS_PERFORMANCE);
		break;
	case 'n':
		/* clear performance flag */
		rockchip_clear_system_status(SYS_STATUS_PERFORMANCE);
		break;
	case 'S':
		/* set video svep flag */
		rockchip_set_system_status(SYS_STATUS_VIDEO_SVEP);
		break;
	case 's':
		/* clear video svep flag */
		rockchip_clear_system_status(SYS_STATUS_VIDEO_SVEP);
		break;
	default:
		break;
	}
}
EXPORT_SYMBOL(rockchip_update_system_status);

static ssize_t status_show(struct kobject *kobj, struct kobj_attribute *attr,
			   char *buf)
{
	unsigned int status = rockchip_get_system_status();

	return sprintf(buf, "0x%x\n", status);
}

static ssize_t status_store(struct kobject *kobj, struct kobj_attribute *attr,
			    const char *buf, size_t n)
{
	if (!n)
		return -EINVAL;

	rockchip_update_system_status(buf);

	return n;
}

static struct system_monitor_attr status =
	__ATTR(system_status, 0644, status_show, status_store);

static int rockchip_get_temp_freq_table(struct device_node *np,
					char *porp_name,
					struct temp_freq_table **freq_table)
{
	struct temp_freq_table *table;
	const struct property *prop;
	int count, i;

	prop = of_find_property(np, porp_name, NULL);
	if (!prop)
		return -EINVAL;

	if (!prop->value)
		return -ENODATA;

	count = of_property_count_u32_elems(np, porp_name);
	if (count < 0)
		return -EINVAL;

	if (count % 2)
		return -EINVAL;

	table = kzalloc(sizeof(*table) * (count / 2 + 1), GFP_KERNEL);
	if (!table)
		return -ENOMEM;

	for (i = 0; i < count / 2; i++) {
		of_property_read_u32_index(np, porp_name, 2 * i,
					   &table[i].temp);
		of_property_read_u32_index(np, porp_name, 2 * i + 1,
					   &table[i].freq);
	}
	table[i].freq = UINT_MAX;
	*freq_table = table;

	return 0;
}

static int rockchip_get_adjust_volt_table(struct device_node *np,
					  char *porp_name,
					  struct volt_adjust_table **table)
{
	struct volt_adjust_table *volt_table;
	const struct property *prop;
	int count, i;

	prop = of_find_property(np, porp_name, NULL);
	if (!prop)
		return -EINVAL;

	if (!prop->value)
		return -ENODATA;

	count = of_property_count_u32_elems(np, porp_name);
	if (count < 0)
		return -EINVAL;

	if (count % 3)
		return -EINVAL;

	volt_table = kzalloc(sizeof(*volt_table) * (count / 3 + 1), GFP_KERNEL);
	if (!volt_table)
		return -ENOMEM;

	for (i = 0; i < count / 3; i++) {
		of_property_read_u32_index(np, porp_name, 3 * i,
					   &volt_table[i].min);
		of_property_read_u32_index(np, porp_name, 3 * i + 1,
					   &volt_table[i].max);
		of_property_read_u32_index(np, porp_name, 3 * i + 2,
					   &volt_table[i].volt);
	}
	volt_table[i].min = 0;
	volt_table[i].max = 0;
	volt_table[i].volt = INT_MAX;

	*table = volt_table;

	return 0;
}

static int rockchip_get_low_temp_volt(struct monitor_dev_info *info,
				      unsigned long rate, int *delta_volt)
{
	int i, ret = -EINVAL;
	unsigned int _rate = (unsigned int)(rate / 1000000);

	if (!info->low_temp_adjust_table)
		return ret;

	for (i = 0; info->low_temp_adjust_table[i].volt != INT_MAX; i++) {
		if (_rate >= info->low_temp_adjust_table[i].min &&
		    _rate <= info->low_temp_adjust_table[i].max) {
			*delta_volt = info->low_temp_adjust_table[i].volt;
			ret = 0;
		}
	}

	return ret;
}

static int rockchip_init_temp_opp_table(struct monitor_dev_info *info)
{
	struct device *dev = info->dev;
	struct opp_table *opp_table;
	struct dev_pm_opp *opp;
	int delta_volt = 0;
	int i = 0, max_count;
	unsigned long low_limit = 0, high_limit = 0;
	unsigned long low_limit_mem = 0, high_limit_mem = 0;
	bool reach_max_volt = false;
	bool reach_max_mem_volt = false;
	bool reach_high_temp_max_volt = false;
	bool reach_high_temp_max_mem_volt = false;

	max_count = dev_pm_opp_get_opp_count(dev);
	if (max_count <= 0)
		return max_count ? max_count : -ENODATA;
	info->opp_table = kzalloc(sizeof(*info->opp_table) * max_count,
				  GFP_KERNEL);
	if (!info->opp_table)
		return -ENOMEM;

	opp_table = dev_pm_opp_get_opp_table(dev);
	if (IS_ERR(opp_table)) {
		kfree(info->opp_table);
		info->opp_table = NULL;
		return PTR_ERR(opp_table);
	}
	mutex_lock(&opp_table->lock);
	list_for_each_entry(opp, &opp_table->opp_list, node) {
		if (!opp->available)
			continue;
		info->opp_table[i].rate = opp->rates[0];
		info->opp_table[i].volt = opp->supplies[0].u_volt;
		info->opp_table[i].max_volt = opp->supplies[0].u_volt_max;

		if (opp->supplies[0].u_volt <= info->high_temp_max_volt) {
			if (!reach_high_temp_max_volt)
				high_limit = opp->rates[0];
			if (opp->supplies[0].u_volt == info->high_temp_max_volt)
				reach_high_temp_max_volt = true;
		}

		if (rockchip_get_low_temp_volt(info, opp->rates[0], &delta_volt))
			delta_volt = 0;
		if ((opp->supplies[0].u_volt + delta_volt) <= info->max_volt) {
			info->opp_table[i].low_temp_volt =
				opp->supplies[0].u_volt + delta_volt;
			if (info->opp_table[i].low_temp_volt <
			    info->low_temp_min_volt)
				info->opp_table[i].low_temp_volt =
					info->low_temp_min_volt;
			if (!reach_max_volt)
				low_limit = opp->rates[0];
			if (info->opp_table[i].low_temp_volt == info->max_volt)
				reach_max_volt = true;
		} else {
			info->opp_table[i].low_temp_volt = info->max_volt;
		}
		if (low_limit && low_limit != opp->rates[0])
			info->low_limit = low_limit;
		if (high_limit && high_limit != opp->rates[0])
			info->high_limit = high_limit;

		if (opp_table->regulator_count > 1) {
			info->opp_table[i].mem_volt = opp->supplies[1].u_volt;
			info->opp_table[i].max_mem_volt = opp->supplies[1].u_volt_max;

			if (opp->supplies[1].u_volt <= info->high_temp_max_volt) {
				if (!reach_high_temp_max_mem_volt)
					high_limit_mem = opp->rates[0];
				if (opp->supplies[1].u_volt == info->high_temp_max_volt)
					reach_high_temp_max_mem_volt = true;
			}

			if ((opp->supplies[1].u_volt + delta_volt) <= info->max_volt) {
				info->opp_table[i].low_temp_mem_volt =
					opp->supplies[1].u_volt + delta_volt;
				if (info->opp_table[i].low_temp_mem_volt <
				    info->low_temp_min_volt)
					info->opp_table[i].low_temp_mem_volt =
						info->low_temp_min_volt;
				if (!reach_max_mem_volt)
					low_limit_mem = opp->rates[0];
				if (info->opp_table[i].low_temp_mem_volt == info->max_volt)
					reach_max_mem_volt = true;
			} else {
				info->opp_table[i].low_temp_mem_volt = info->max_volt;
			}

			if (low_limit_mem && low_limit_mem != opp->rates[0]) {
				if (info->low_limit > low_limit_mem)
					info->low_limit = low_limit_mem;
			}
			if (high_limit_mem && high_limit_mem != opp->rates[0]) {
				if (info->high_limit > high_limit_mem)
					info->high_limit = high_limit_mem;
			}
		}

		dev_dbg(dev, "rate=%lu, volt=%lu %lu low_temp_volt=%lu %lu\n",
			info->opp_table[i].rate, info->opp_table[i].volt,
			info->opp_table[i].mem_volt,
			info->opp_table[i].low_temp_volt,
			info->opp_table[i].low_temp_mem_volt);
		i++;
	}
	mutex_unlock(&opp_table->lock);

	dev_pm_opp_put_opp_table(opp_table);

	return 0;
}

static int monitor_device_parse_wide_temp_config(struct device_node *np,
						 struct monitor_dev_info *info)
{
	struct device *dev = info->dev;
	unsigned long high_temp_max_freq;
	int ret = 0;
	u32 value;

	np = of_parse_phandle(dev->of_node, "operating-points-v2", 0);
	if (!np)
		return -EINVAL;

	if (of_property_read_u32(np, "rockchip,max-volt", &value))
		info->max_volt = ULONG_MAX;
	else
		info->max_volt = value;
	of_property_read_u32(np, "rockchip,temp-hysteresis",
			     &info->temp_hysteresis);
	if (of_property_read_u32(np, "rockchip,low-temp", &info->low_temp))
		info->low_temp = INT_MIN;
	rockchip_get_adjust_volt_table(np, "rockchip,low-temp-adjust-volt",
				       &info->low_temp_adjust_table);
	if (!of_property_read_u32(np, "rockchip,low-temp-min-volt", &value))
		info->low_temp_min_volt = value;
	if (of_property_read_u32(np, "rockchip,high-temp", &info->high_temp))
		info->high_temp = INT_MAX;
	if (of_property_read_u32(np, "rockchip,high-temp-max-volt",
				 &value))
		info->high_temp_max_volt = ULONG_MAX;
	else
		info->high_temp_max_volt = value;
	rockchip_init_temp_opp_table(info);
	rockchip_get_temp_freq_table(np, "rockchip,temp-freq-table",
				     &info->high_limit_table);
	if (!info->high_limit_table)
		rockchip_get_temp_freq_table(np, "rockchip,high-temp-limit-table",
					     &info->high_limit_table);
	if (!info->high_limit_table) {
		if (!of_property_read_u32(np, "rockchip,high-temp-max-freq",
					  &value)) {
			high_temp_max_freq = value * 1000;
			if (info->high_limit)
				info->high_limit = min(high_temp_max_freq,
						       info->high_limit);
			else
				info->high_limit = high_temp_max_freq;
		}
	} else {
		info->high_limit = 0;
	}
	dev_info(dev, "l=%d h=%d hyst=%d l_limit=%lu h_limit=%lu h_table=%d\n",
		 info->low_temp, info->high_temp, info->temp_hysteresis,
		 info->low_limit, info->high_limit,
		 info->high_limit_table ? true : false);

	if ((info->low_temp + info->temp_hysteresis) > info->high_temp) {
		dev_err(dev, "Invalid temperature, low=%d high=%d hyst=%d\n",
			info->low_temp, info->high_temp,
			info->temp_hysteresis);
		ret = -EINVAL;
		goto err;
	}
	if (!info->low_temp_adjust_table && !info->low_temp_min_volt &&
	    !info->low_limit && !info->high_limit && !info->high_limit_table) {
		ret = -EINVAL;
		goto err;
	}
	if (info->low_temp_adjust_table || info->low_temp_min_volt)
		info->is_low_temp_enabled = true;

	return 0;
err:
	kfree(info->low_temp_adjust_table);
	info->low_temp_adjust_table = NULL;
	kfree(info->opp_table);
	info->opp_table = NULL;

	return ret;
}

static int monitor_device_parse_status_config(struct device_node *np,
					      struct monitor_dev_info *info)
{
	int ret;

	ret = of_property_read_u32(np, "rockchip,early-suspend-freq",
				   &info->early_suspend_freq);
	ret &= of_property_read_u32(np, "rockchip,video-1080p-freq",
				   &info->video_1080p_freq);
	ret &= of_property_read_u32(np, "rockchip,video-4k-freq",
				   &info->video_4k_freq);
	ret &= of_property_read_u32(np, "rockchip,reboot-freq",
				    &info->reboot_freq);
	if (info->devp->type == MONITOR_TYPE_CPU) {
		if (!info->reboot_freq) {
			info->reboot_freq = CPU_REBOOT_FREQ;
			ret = 0;
		}
	}

	return ret;
}

static int monitor_device_parse_early_min_volt(struct device_node *np,
					       struct monitor_dev_info *info)
{
	const char *prop_name = "rockchip,early-min-microvolt";
	int count = 0, ret = 0;

	count = of_property_count_u32_elems(np, prop_name);
	if (count <= 0)
		return -EINVAL;

	if (count > 1) {
		ret = of_property_read_u32_index(np, prop_name, 1,
						 &info->early_min_volt[1]);
		if (ret)
			return ret;
	}

	return of_property_read_u32_index(np, prop_name, 0,
					  &info->early_min_volt[0]);
}

static int monitor_device_parse_dt(struct device *dev,
				   struct monitor_dev_info *info)
{
	struct device_node *np;
	int ret;

	np = of_parse_phandle(dev->of_node, "operating-points-v2", 0);
	if (!np)
		return -EINVAL;

	ret = monitor_device_parse_wide_temp_config(np, info);
	ret &= monitor_device_parse_status_config(np, info);
	ret &= monitor_device_parse_early_min_volt(np, info);

	of_node_put(np);

	return ret;
}

int rockchip_monitor_cpu_low_temp_adjust(struct monitor_dev_info *info,
					 bool is_low)
{
	if (!info->low_limit)
		return 0;

	if (!freq_qos_request_active(&info->max_temp_freq_req))
		return 0;

	if (is_low)
		freq_qos_update_request(&info->max_temp_freq_req,
					info->low_limit / 1000);
	else
		freq_qos_update_request(&info->max_temp_freq_req,
					FREQ_QOS_MAX_DEFAULT_VALUE);

	return 0;
}
EXPORT_SYMBOL(rockchip_monitor_cpu_low_temp_adjust);

int rockchip_monitor_cpu_high_temp_adjust(struct monitor_dev_info *info,
					  bool is_high)
{
	if (!freq_qos_request_active(&info->max_temp_freq_req))
		return 0;

	if (info->high_limit_table) {
		if (info->high_limit)
			freq_qos_update_request(&info->max_temp_freq_req,
						info->high_limit / 1000);
		else
			freq_qos_update_request(&info->max_temp_freq_req,
						FREQ_QOS_MAX_DEFAULT_VALUE);
		return 0;
	}

	if (!info->high_limit)
		return 0;

	if (is_high)
		freq_qos_update_request(&info->max_temp_freq_req,
					info->high_limit / 1000);
	else
		freq_qos_update_request(&info->max_temp_freq_req,
					FREQ_QOS_MAX_DEFAULT_VALUE);

	return 0;
}
EXPORT_SYMBOL(rockchip_monitor_cpu_high_temp_adjust);

int rockchip_monitor_dev_low_temp_adjust(struct monitor_dev_info *info,
					 bool is_low)
{
	if (!dev_pm_qos_request_active(&info->dev_max_freq_req))
		return 0;

	if (!info->low_limit)
		return 0;

	if (is_low)
		dev_pm_qos_update_request(&info->dev_max_freq_req,
					  info->low_limit / 1000);
	else
		dev_pm_qos_update_request(&info->dev_max_freq_req,
					  PM_QOS_MAX_FREQUENCY_DEFAULT_VALUE);

	return 0;
}
EXPORT_SYMBOL(rockchip_monitor_dev_low_temp_adjust);

int rockchip_monitor_dev_high_temp_adjust(struct monitor_dev_info *info,
					  bool is_high)
{
	if (!dev_pm_qos_request_active(&info->dev_max_freq_req))
		return 0;

	if (info->high_limit_table) {
		if (info->high_limit)
			dev_pm_qos_update_request(&info->dev_max_freq_req,
						  info->high_limit / 1000);
		else
			dev_pm_qos_update_request(&info->dev_max_freq_req,
						  PM_QOS_MAX_FREQUENCY_DEFAULT_VALUE);
		return 0;
	}

	if (!info->high_limit)
		return 0;

	if (is_high)
		dev_pm_qos_update_request(&info->dev_max_freq_req,
					  info->high_limit / 1000);
	else
		dev_pm_qos_update_request(&info->dev_max_freq_req,
					  PM_QOS_MAX_FREQUENCY_DEFAULT_VALUE);

	return 0;
}
EXPORT_SYMBOL(rockchip_monitor_dev_high_temp_adjust);

static int rockchip_adjust_low_temp_opp_volt(struct monitor_dev_info *info,
					     bool is_low_temp)
{
	struct device *dev = info->dev;
	struct opp_table *opp_table;
	struct dev_pm_opp *opp;
	int i = 0;

	opp_table = dev_pm_opp_get_opp_table(dev);
	if (IS_ERR(opp_table))
		return PTR_ERR(opp_table);

	mutex_lock(&opp_table->lock);
	list_for_each_entry(opp, &opp_table->opp_list, node) {
		if (!opp->available)
			continue;
		if (is_low_temp) {
			if (opp->supplies[0].u_volt_max <
			    info->opp_table[i].low_temp_volt)
				opp->supplies[0].u_volt_max =
					info->opp_table[i].low_temp_volt;
			opp->supplies[0].u_volt =
				info->opp_table[i].low_temp_volt;
			opp->supplies[0].u_volt_min = opp->supplies[0].u_volt;
			if (opp_table->regulator_count > 1) {
				if (opp->supplies[1].u_volt_max <
				    info->opp_table[i].low_temp_mem_volt)
					opp->supplies[1].u_volt_max =
						info->opp_table[i].low_temp_mem_volt;
				opp->supplies[1].u_volt =
					info->opp_table[i].low_temp_mem_volt;
				opp->supplies[1].u_volt_min =
					opp->supplies[1].u_volt;
			}
		} else {
			opp->supplies[0].u_volt_min = info->opp_table[i].volt;
			opp->supplies[0].u_volt = opp->supplies[0].u_volt_min;
			opp->supplies[0].u_volt_max =
				info->opp_table[i].max_volt;
			if (opp_table->regulator_count > 1) {
				opp->supplies[1].u_volt_min =
					info->opp_table[i].mem_volt;
				opp->supplies[1].u_volt =
					opp->supplies[1].u_volt_min;
				opp->supplies[1].u_volt_max =
					info->opp_table[i].max_mem_volt;
			}
		}
		i++;
	}
	mutex_unlock(&opp_table->lock);

	dev_pm_opp_put_opp_table(opp_table);

	return 0;
}

static void rockchip_low_temp_adjust(struct monitor_dev_info *info,
				     bool is_low)
{
	struct monitor_dev_profile *devp = info->devp;
	struct arm_smccc_res res;
	int ret = 0;

	dev_dbg(info->dev, "low_temp %d\n", is_low);

	if (info->opp_table)
		rockchip_adjust_low_temp_opp_volt(info, is_low);

	if (devp->low_temp_adjust)
		ret = devp->low_temp_adjust(info, is_low);
	if (!ret)
		info->is_low_temp = is_low;

	if (devp->check_rate_volt)
		devp->check_rate_volt(info);

	if (devp->opp_info && devp->opp_info->pvtpll_low_temp) {
		res = sip_smc_pvtpll_config(PVTPLL_LOW_TEMP,
					    devp->opp_info->pvtpll_clk_id,
					    is_low, 0, 0, 0, 0);
		if (res.a0)
			dev_err(info->dev,
				"%s: error cfg id=%u low temp %d (%d)\n",
				__func__, devp->opp_info->pvtpll_clk_id,
				is_low, (int)res.a0);
	}
}

static void rockchip_high_temp_adjust(struct monitor_dev_info *info,
				      bool is_high)
{
	struct monitor_dev_profile *devp = info->devp;
	int ret = 0;

	if (!devp->high_temp_adjust)
		return;

	if (info->high_limit_table) {
		devp->high_temp_adjust(info, is_high);
	} else {
		dev_dbg(info->dev, "high_temp %d\n", is_high);
		ret = devp->high_temp_adjust(info, is_high);
		if (!ret)
			info->is_high_temp = is_high;
	}
}

static int rockchip_monitor_low_temp_adjust(struct monitor_dev_info *info)
{
	if (!info || !info->is_low_temp_enabled)
		return 0;

	if (info->high_limit_table) {
		info->high_limit = 0;
		rockchip_high_temp_adjust(info, true);
	} else if (info->is_high_temp) {
		rockchip_high_temp_adjust(info, false);
	}
	if (!info->is_low_temp)
		rockchip_low_temp_adjust(info, true);

	return 0;
}

int rockchip_monitor_suspend_low_temp_adjust(int cpu)
{
	struct monitor_dev_info *info = NULL, *tmp;

	down_read(&mdev_list_sem);
	list_for_each_entry(tmp, &monitor_dev_list, node) {
		if (tmp->devp->type != MONITOR_TYPE_CPU)
			continue;
		if (cpumask_test_cpu(cpu, &tmp->devp->allowed_cpus)) {
			info = tmp;
			break;
		}
	}
	up_read(&mdev_list_sem);

	return rockchip_monitor_low_temp_adjust(info);
}
EXPORT_SYMBOL(rockchip_monitor_suspend_low_temp_adjust);

void rockchip_monitor_remove_cpu_limit(int cpu)
{
	struct monitor_dev_info *info;

	down_read(&mdev_list_sem);
	list_for_each_entry(info, &monitor_dev_list, node) {
		if (info->devp->type != MONITOR_TYPE_CPU)
			continue;
		if (cpumask_test_cpu(cpu, &info->devp->allowed_cpus)) {
			if (info->status_max_limit)
				freq_qos_update_request(&info->max_sta_freq_req,
							FREQ_QOS_MAX_DEFAULT_VALUE);
			break;
		}
	}
	up_read(&mdev_list_sem);
}
EXPORT_SYMBOL(rockchip_monitor_remove_cpu_limit);

void rockchip_monitor_restore_cpu_limit(int cpu)
{
	struct monitor_dev_info *info;

	down_read(&mdev_list_sem);
	list_for_each_entry(info, &monitor_dev_list, node) {
		if (info->devp->type != MONITOR_TYPE_CPU)
			continue;
		if (cpumask_test_cpu(cpu, &info->devp->allowed_cpus)) {
			if (info->status_max_limit)
				freq_qos_update_request(&info->max_sta_freq_req,
							info->status_max_limit);
			break;
		}
	}
	up_read(&mdev_list_sem);
}
EXPORT_SYMBOL(rockchip_monitor_restore_cpu_limit);

static int
rockchip_system_monitor_wide_temp_adjust(struct monitor_dev_info *info,
					 int temp)
{
	unsigned long target_freq = 0;
	int i;

	if (temp < info->low_temp) {
		if (!info->is_low_temp)
			rockchip_low_temp_adjust(info, true);
	} else if (temp > (info->low_temp + info->temp_hysteresis)) {
		if (info->is_low_temp)
			rockchip_low_temp_adjust(info, false);
	}

	if (info->high_limit_table) {
		for (i = 0; info->high_limit_table[i].freq != UINT_MAX; i++) {
			if (temp > info->high_limit_table[i].temp)
				target_freq =
					info->high_limit_table[i].freq * 1000;
		}
		if (target_freq != info->high_limit) {
			info->high_limit = target_freq;
			rockchip_high_temp_adjust(info, true);
		}
	} else {
		if (temp > info->high_temp) {
			if (!info->is_high_temp)
				rockchip_high_temp_adjust(info, true);
		} else if (temp < (info->high_temp - info->temp_hysteresis)) {
			if (info->is_high_temp)
				rockchip_high_temp_adjust(info, false);
		}
	}

	return 0;
}

static void
rockchip_system_monitor_wide_temp_init(struct monitor_dev_info *info)
{
	int ret, temp;

	if (!info->opp_table)
		return;
	if (!system_monitor->tz)
		return;

	/*
	 * set the init state to low temperature that the voltage will be enough
	 * when cpu up at low temperature.
	 */
	if (!info->is_low_temp) {
		if (info->opp_table)
			rockchip_adjust_low_temp_opp_volt(info, true);
		info->is_low_temp = true;
	}

	ret = thermal_zone_get_temp(system_monitor->tz, &temp);
	if (ret || temp == THERMAL_TEMP_INVALID) {
		dev_err(info->dev,
			"failed to read out thermal zone (%d)\n", ret);
		return;
	}

	if (temp > info->high_temp) {
		if (info->opp_table)
			rockchip_adjust_low_temp_opp_volt(info, false);
		info->is_low_temp = false;
		info->is_high_temp = true;
	} else if (temp > (info->low_temp + info->temp_hysteresis)) {
		if (info->opp_table)
			rockchip_adjust_low_temp_opp_volt(info, false);
		info->is_low_temp = false;
	}
}

static const char *get_rdev_name(struct regulator_dev *rdev)
{
	if (rdev->constraints && rdev->constraints->name)
		return rdev->constraints->name;
	else if (rdev->desc->name)
		return rdev->desc->name;
	else
		return "";
}

static void
rockchip_system_monitor_early_regulator_init(struct monitor_dev_info *info)
{
	struct monitor_dev_profile *devp = info->devp;
	struct rockchip_opp_info *opp_info = devp->opp_info;
	struct regulator *reg;
	struct regulator_dev *rdev;
	int i;

	if (!opp_info || !opp_info->regulators)
		return;

	for (i = 0; i < opp_info->regulator_count; i++) {
		if (!info->early_min_volt[i] || i >= 2)
			continue;
		rdev = opp_info->regulators[i]->rdev;
		reg = regulator_get(NULL, get_rdev_name(rdev));
		if (!IS_ERR_OR_NULL(reg)) {
			info->early_reg[i] = reg;
			reg->voltage[PM_SUSPEND_ON].min_uV = info->early_min_volt[i];
			reg->voltage[PM_SUSPEND_ON].max_uV = rdev->constraints->max_uV;
		}
	}
}

static void
rockchip_system_monitor_early_regulator_uninit(struct monitor_dev_info *info)
{
	struct monitor_dev_profile *devp = info->devp;
	struct rockchip_opp_info *opp_info = devp->opp_info;
	struct regulator_dev *rdev;
	int min_uV, max_uV;
	int ret, i;

	if (!opp_info || !opp_info->regulators)
		return;

	for (i = 0; i < opp_info->regulator_count; i++) {
		if (!info->early_reg[i] || i >= 2)
			continue;
		rdev = info->early_reg[i]->rdev;
		min_uV = rdev->constraints->min_uV;
		max_uV = rdev->constraints->max_uV;
		ret = regulator_set_voltage(info->early_reg[i], min_uV, max_uV);
		if (ret)
			dev_err(&rdev->dev,
				"%s: failed to set volt\n", __func__);
		regulator_put(info->early_reg[i]);
		info->early_reg[i] = NULL;
	}
}

static int
rockchip_system_monitor_freq_qos_requset(struct monitor_dev_info *info)
{
	struct devfreq *devfreq;
	struct cpufreq_policy *policy;
	int max_default_value = FREQ_QOS_MAX_DEFAULT_VALUE;
	int ret;

	if (!info->devp->data)
		return 0;

	if (info->is_low_temp && info->low_limit)
		max_default_value = info->low_limit / 1000;
	else if (info->is_high_temp && info->high_limit)
		max_default_value = info->high_limit / 1000;

	if (info->devp->type == MONITOR_TYPE_CPU) {
		policy = (struct cpufreq_policy *)info->devp->data;
		ret = freq_qos_add_request(&policy->constraints,
					   &info->max_temp_freq_req,
					   FREQ_QOS_MAX,
					   max_default_value);
		if (ret < 0) {
			dev_info(info->dev,
				 "failed to add temp freq constraint\n");
			return ret;
		}
		ret = freq_qos_add_request(&policy->constraints,
					   &info->min_sta_freq_req,
					   FREQ_QOS_MIN,
					   FREQ_QOS_MIN_DEFAULT_VALUE);
		if (ret < 0) {
			dev_info(info->dev,
				 "failed to add sta freq constraint\n");
			freq_qos_remove_request(&info->max_temp_freq_req);
			return ret;
		}
		ret = freq_qos_add_request(&policy->constraints,
					   &info->max_sta_freq_req,
					   FREQ_QOS_MAX,
					   FREQ_QOS_MAX_DEFAULT_VALUE);
		if (ret < 0) {
			dev_info(info->dev,
				 "failed to add sta freq constraint\n");
			freq_qos_remove_request(&info->max_temp_freq_req);
			freq_qos_remove_request(&info->min_sta_freq_req);
			return ret;
		}
	} else if (info->devp->type == MONITOR_TYPE_DEV) {
		devfreq = (struct devfreq *)info->devp->data;
		ret = dev_pm_qos_add_request(devfreq->dev.parent,
					     &info->dev_max_freq_req,
					     DEV_PM_QOS_MAX_FREQUENCY,
					     max_default_value);
		if (ret < 0) {
			dev_info(info->dev, "failed to add freq constraint\n");
			return ret;
		}
	}

	return 0;
}

int rockchip_monitor_check_rate_volt(struct monitor_dev_info *info)
{
	struct device *dev = info->dev;
	struct monitor_dev_profile *devp = info->devp;
	struct rockchip_opp_info *opp_info = devp->opp_info;

	rockchip_opp_dvfs_lock(opp_info);

	if (devp->type == MONITOR_TYPE_DEV) {
		if (pm_runtime_active(dev))
			opp_info->is_runtime_active = true;
		else
			opp_info->is_runtime_active = false;
	}
	rockchip_opp_check_rate_volt(dev, opp_info);
	opp_info->is_rate_volt_checked = true;

	rockchip_opp_dvfs_unlock(opp_info);

	return 0;
}
EXPORT_SYMBOL(rockchip_monitor_check_rate_volt);

static void rockchip_system_monitor_check_rate_volt(struct monitor_dev_info *info)
{
	if (info->devp->check_rate_volt)
		info->devp->check_rate_volt(info);
	else
		rockchip_monitor_check_rate_volt(info);
}

struct monitor_dev_info *
rockchip_system_monitor_register(struct device *dev,
				 struct monitor_dev_profile *devp)
{
	struct monitor_dev_info *info;

	if (!system_monitor)
		return ERR_PTR(-ENOMEM);

	if (!devp)
		return ERR_PTR(-EINVAL);

	info = kzalloc(sizeof(*info), GFP_KERNEL);
	if (!info)
		return ERR_PTR(-ENOMEM);
	info->dev = dev;
	info->devp = devp;

	if (monitor_device_parse_dt(dev, info)) {
		rockchip_system_monitor_check_rate_volt(info);
		kfree(info);
		return ERR_PTR(-EINVAL);
	}

	rockchip_system_monitor_early_regulator_init(info);
	rockchip_system_monitor_wide_temp_init(info);
	rockchip_system_monitor_check_rate_volt(info);
	rockchip_system_monitor_freq_qos_requset(info);

	down_write(&mdev_list_sem);
	list_add(&info->node, &monitor_dev_list);
	up_write(&mdev_list_sem);

	return info;
}
EXPORT_SYMBOL(rockchip_system_monitor_register);

void rockchip_system_monitor_unregister(struct monitor_dev_info *info)
{
	if (!info)
		return;

	down_write(&mdev_list_sem);
	rockchip_system_monitor_early_regulator_uninit(info);
	list_del(&info->node);
	up_write(&mdev_list_sem);

	if (info->devp->type == MONITOR_TYPE_CPU) {
		if (freq_qos_request_active(&info->max_temp_freq_req))
			freq_qos_remove_request(&info->max_temp_freq_req);
		if (freq_qos_request_active(&info->min_sta_freq_req))
			freq_qos_remove_request(&info->min_sta_freq_req);
		if (freq_qos_request_active(&info->max_sta_freq_req))
			freq_qos_remove_request(&info->max_sta_freq_req);
	} else {
		if (dev_pm_qos_request_active(&info->dev_max_freq_req))
			dev_pm_qos_remove_request(&info->dev_max_freq_req);
	}

	kfree(info->low_temp_adjust_table);
	kfree(info->opp_table);
	kfree(info);
}
EXPORT_SYMBOL(rockchip_system_monitor_unregister);

int rockchip_system_monitor_register_notifier(struct notifier_block *nb)
{
	return blocking_notifier_chain_register(&system_monitor_notifier_list, nb);
}
EXPORT_SYMBOL(rockchip_system_monitor_register_notifier);

void rockchip_system_monitor_unregister_notifier(struct notifier_block *nb)
{
	blocking_notifier_chain_unregister(&system_monitor_notifier_list, nb);
}
EXPORT_SYMBOL(rockchip_system_monitor_unregister_notifier);

static int rockchip_system_monitor_temp_notify(int temp)
{
	struct system_monitor_event_data event_data;
	int ret;

	event_data.temp = temp;
	ret = blocking_notifier_call_chain(&system_monitor_notifier_list,
					   SYSTEM_MONITOR_CHANGE_TEMP,
					   (void *)&event_data);

	return notifier_to_errno(ret);
}

static int notify_dummy(struct thermal_zone_device *tz, int trip)
{
	return 0;
}

static struct thermal_governor thermal_gov_dummy = {
	.name		= "dummy",
	.throttle	= notify_dummy,
};

static int rockchip_system_monitor_parse_dt(struct system_monitor *monitor)
{
	struct device_node *np = monitor->dev->of_node;
	const char *tz_name, *buf = NULL;

	if (of_property_read_string(np, "rockchip,early-suspend-offline-cpus", &buf))
		cpumask_clear(&monitor->early_suspend_offline_cpus);
	else
		cpulist_parse(buf, &monitor->early_suspend_offline_cpus);

	if (of_property_read_string(np, "rockchip,video-4k-offline-cpus", &buf))
		cpumask_clear(&monitor->video_4k_offline_cpus);
	else
		cpulist_parse(buf, &monitor->video_4k_offline_cpus);

	if (of_property_read_string(np, "rockchip,thermal-zone", &tz_name))
		goto out;
	monitor->tz = thermal_zone_get_zone_by_name(tz_name);
	if (IS_ERR(monitor->tz)) {
		monitor->tz = NULL;
		goto out;
	}
	if (of_property_read_u32(np, "rockchip,polling-delay",
				 &monitor->delay))
		monitor->delay = THERMAL_POLLING_DELAY;

	if (of_property_read_string(np, "rockchip,temp-offline-cpus",
				    &buf))
		cpumask_clear(&system_monitor->temp_offline_cpus);
	else
		cpulist_parse(buf, &system_monitor->temp_offline_cpus);

	if (of_property_read_u32(np, "rockchip,offline-cpu-temp",
				 &system_monitor->offline_cpus_temp))
		system_monitor->offline_cpus_temp = INT_MAX;
	of_property_read_u32(np, "rockchip,temp-hysteresis",
			     &system_monitor->temp_hysteresis);
	rockchip_get_temp_freq_table(np, "rockchip,temp-ddr-ref-mode",
				     &system_monitor->temp_ddr_ref_mode);

	if (of_find_property(np, "rockchip,thermal-governor-dummy", NULL)) {
		if (monitor->tz->governor->unbind_from_tz)
			monitor->tz->governor->unbind_from_tz(monitor->tz);
		monitor->tz->governor = &thermal_gov_dummy;
	}

out:
	return 0;
}

#ifdef CONFIG_HOTPLUG_CPU
static void rockchip_system_monitor_first_cpu_online(struct cpumask *online_cpus)
{
	struct monitor_dev_info *tmp;
	struct cpumask tmp_mask;

	down_read(&mdev_list_sem);
	list_for_each_entry(tmp, &monitor_dev_list, node) {
		if (tmp->devp->type != MONITOR_TYPE_CPU)
			continue;
		/* Check if all allowed cpus of the cluster are offline */
		cpumask_and(&tmp_mask, &tmp->devp->allowed_cpus, cpu_online_mask);
		if (!cpumask_empty(&tmp_mask))
			continue;
		/* Check if the online cpus contain one allowed cpu of the cluster */
		cpumask_and(&tmp_mask, &tmp->devp->allowed_cpus, online_cpus);
		if (cpumask_empty(&tmp_mask))
			continue;
		rockchip_monitor_low_temp_adjust(tmp);
	}
	up_read(&mdev_list_sem);
}
#endif

static void rockchip_system_monitor_cpu_on_off(void)
{
#ifdef CONFIG_HOTPLUG_CPU
	struct cpumask online_cpus, offline_cpus;
	unsigned int cpu;

	mutex_lock(&cpu_on_off_mutex);

	cpumask_clear(&offline_cpus);
	if (system_monitor->is_temp_offline) {
		cpumask_or(&offline_cpus, &system_monitor->status_offline_cpus,
			   &system_monitor->temp_offline_cpus);
	} else {
		cpumask_copy(&offline_cpus,
			     &system_monitor->status_offline_cpus);
	}
	if (cpumask_equal(&offline_cpus, &system_monitor->offline_cpus))
		goto out;
	cpumask_copy(&system_monitor->offline_cpus, &offline_cpus);
	for_each_cpu(cpu, &system_monitor->offline_cpus) {
		if (cpu_online(cpu))
			remove_cpu(cpu);
	}

	cpumask_clear(&online_cpus);
	cpumask_andnot(&online_cpus, cpu_possible_mask,
		       &system_monitor->offline_cpus);
	cpumask_xor(&online_cpus, cpu_online_mask, &online_cpus);
	if (cpumask_empty(&online_cpus))
		goto out;
	rockchip_system_monitor_first_cpu_online(&online_cpus);
	for_each_cpu(cpu, &online_cpus)
		add_cpu(cpu);

out:
	mutex_unlock(&cpu_on_off_mutex);
#endif
}

static void rockchip_system_monitor_temp_cpu_on_off(int temp)
{
	bool is_temp_offline;

	if (cpumask_empty(&system_monitor->temp_offline_cpus))
		return;

	if (temp > system_monitor->offline_cpus_temp)
		is_temp_offline = true;
	else if (temp < system_monitor->offline_cpus_temp -
		 system_monitor->temp_hysteresis)
		is_temp_offline = false;
	else
		return;

	if (system_monitor->is_temp_offline == is_temp_offline)
		return;
	system_monitor->is_temp_offline = is_temp_offline;
	rockchip_system_monitor_cpu_on_off();
}

static void rockchip_system_monitor_temp_ddr_ref_mode(int temp)
{
	unsigned int i, new_ref_mode = 0;
	static unsigned int last_ref_mode;

	if (!system_monitor->temp_ddr_ref_mode)
		return;
	if (!system_monitor->ddr_trefi_update)
		return;

	for (i = 0; system_monitor->temp_ddr_ref_mode[i].freq != UINT_MAX; i++) {
		if (temp > system_monitor->temp_ddr_ref_mode[i].temp)
			new_ref_mode = system_monitor->temp_ddr_ref_mode[i].freq;
	}
	if (new_ref_mode && (new_ref_mode != last_ref_mode)) {
		system_monitor->ddr_trefi_update(new_ref_mode);
		last_ref_mode = new_ref_mode;
	}
}

static void rockchip_system_monitor_thermal_update(void)
{
	int temp, ret;
	struct monitor_dev_info *info;

	ret = thermal_zone_get_temp(system_monitor->tz, &temp);
	if (ret || temp == THERMAL_TEMP_INVALID)
		goto out;

	dev_dbg(system_monitor->dev, "temperature=%d\n", temp);

	if (temp < system_monitor->last_temp &&
	    system_monitor->last_temp - temp <= 2000)
		goto out;
	system_monitor->last_temp = temp;

	rockchip_system_monitor_temp_notify(temp);

	down_read(&mdev_list_sem);
	list_for_each_entry(info, &monitor_dev_list, node)
		rockchip_system_monitor_wide_temp_adjust(info, temp);
	up_read(&mdev_list_sem);

	rockchip_system_monitor_temp_cpu_on_off(temp);
	rockchip_system_monitor_temp_ddr_ref_mode(temp);

out:
	mod_delayed_work(system_freezable_wq, &system_monitor->thermal_work,
			 msecs_to_jiffies(system_monitor->delay));
}

static void rockchip_system_monitor_thermal_check(struct work_struct *work)
{
	if (atomic_read(&monitor_in_suspend))
		return;

	rockchip_system_monitor_thermal_update();
}

static void rockchip_system_status_cpu_limit_freq(struct monitor_dev_info *info,
						  unsigned long status)
{
	unsigned int target_freq = 0;

	if (!freq_qos_request_active(&info->min_sta_freq_req))
		return;
	if (!freq_qos_request_active(&info->max_sta_freq_req))
		return;

	if (status & SYS_STATUS_REBOOT) {
		freq_qos_update_request(&info->max_sta_freq_req,
					info->reboot_freq);
		freq_qos_update_request(&info->min_sta_freq_req,
					info->reboot_freq);
		return;
	}

	if (info->early_suspend_freq && (status & SYS_STATUS_SUSPEND))
		target_freq = info->early_suspend_freq;
	if (info->video_1080p_freq && (status & SYS_STATUS_VIDEO_1080P)) {
		if (!target_freq || target_freq > info->video_1080p_freq)
			target_freq = info->video_1080p_freq;
	}
	if (info->video_4k_freq && (status & SYS_STATUS_VIDEO_4K)) {
		if (!target_freq || target_freq > info->video_4k_freq)
			target_freq = info->video_4k_freq;
	}

	if (target_freq == info->status_max_limit)
		return;
	info->status_max_limit = target_freq;
	if (info->status_max_limit)
		freq_qos_update_request(&info->max_sta_freq_req,
					info->status_max_limit);
	else
		freq_qos_update_request(&info->max_sta_freq_req,
					FREQ_QOS_MAX_DEFAULT_VALUE);
}

static void rockchip_system_status_limit_freq(unsigned long status)
{
	struct monitor_dev_info *info;

	down_read(&mdev_list_sem);
	list_for_each_entry(info, &monitor_dev_list, node) {
		if (info->devp->type == MONITOR_TYPE_CPU)
			rockchip_system_status_cpu_limit_freq(info, status);
	}
	up_read(&mdev_list_sem);
}

static void rockchip_system_status_cpu_on_off(unsigned long status)
{
	struct cpumask offline_cpus;

	if (cpumask_empty(&system_monitor->video_4k_offline_cpus) &&
	    cpumask_empty(&system_monitor->early_suspend_offline_cpus))
		return;

	cpumask_clear(&offline_cpus);
	if (status & SYS_STATUS_SUSPEND)
		cpumask_copy(&offline_cpus,
			     &system_monitor->early_suspend_offline_cpus);
	else if (status & SYS_STATUS_VIDEO_4K)
		cpumask_copy(&offline_cpus,
			     &system_monitor->video_4k_offline_cpus);
	if (cpumask_equal(&offline_cpus, &system_monitor->status_offline_cpus))
		return;
	cpumask_copy(&system_monitor->status_offline_cpus, &offline_cpus);
	rockchip_system_monitor_cpu_on_off();
}

static int rockchip_system_status_notifier(struct notifier_block *nb,
					   unsigned long status,
					   void *ptr)
{
	rockchip_system_status_limit_freq(status);

	rockchip_system_status_cpu_on_off(status);

	return NOTIFY_OK;
}

static int rockchip_system_monitor_set_cpu_uevent_suppress(bool is_suppress)
{
	struct monitor_dev_info *info;
	struct cpufreq_policy *policy;

	down_read(&mdev_list_sem);
	list_for_each_entry(info, &monitor_dev_list, node) {
		if (info->devp->type != MONITOR_TYPE_CPU)
			continue;
		policy = (struct cpufreq_policy *)info->devp->data;
		if (!policy || !policy->cdev)
			continue;
		if (is_suppress)
			dev_set_uevent_suppress(&policy->cdev->device, 1);
		else
			dev_set_uevent_suppress(&policy->cdev->device, 0);
	}
	up_read(&mdev_list_sem);

	return 0;
}

static int monitor_pm_notify(struct notifier_block *nb,
			     unsigned long mode, void *_unused)
{
	switch (mode) {
	case PM_HIBERNATION_PREPARE:
	case PM_RESTORE_PREPARE:
	case PM_SUSPEND_PREPARE:
		atomic_set(&monitor_in_suspend, 1);
		rockchip_system_monitor_set_cpu_uevent_suppress(true);
		break;
	case PM_POST_HIBERNATION:
	case PM_POST_RESTORE:
	case PM_POST_SUSPEND:
		if (system_monitor->tz)
			rockchip_system_monitor_thermal_update();
		atomic_set(&monitor_in_suspend, 0);
		rockchip_system_monitor_set_cpu_uevent_suppress(false);
		system_monitor->last_temp = INT_MAX;
		break;
	default:
		break;
	}
	return 0;
}

static struct notifier_block monitor_pm_nb = {
	.notifier_call = monitor_pm_notify,
};

static int rockchip_monitor_reboot_notifier(struct notifier_block *nb,
					     unsigned long action, void *ptr)
{
	rockchip_set_system_status(SYS_STATUS_REBOOT);
	if (system_monitor->tz)
		cancel_delayed_work_sync(&system_monitor->thermal_work);

	return NOTIFY_OK;
}

static struct notifier_block rockchip_monitor_reboot_nb = {
	.notifier_call = rockchip_monitor_reboot_notifier,
};

#ifdef CONFIG_FB
static int rockchip_monitor_fb_notifier(struct notifier_block *nb,
					unsigned long action, void *ptr)
{
	struct fb_event *event = ptr;

	if (action != FB_EVENT_BLANK)
		return NOTIFY_OK;

	switch (*((int *)event->data)) {
	case FB_BLANK_UNBLANK:
		rockchip_clear_system_status(SYS_STATUS_SUSPEND);
		break;
	case FB_BLANK_POWERDOWN:
		rockchip_set_system_status(SYS_STATUS_SUSPEND);
		break;
	default:
		break;
	}

	return NOTIFY_OK;
}

static struct notifier_block rockchip_monitor_fb_nb = {
	.notifier_call = rockchip_monitor_fb_notifier,
};
#elif defined(CONFIG_ROCKCHIP_EARLYSUSPEND)
static void rockchip_monitor_early_suspend(struct early_suspend *h)
{
	rockchip_set_system_status(SYS_STATUS_SUSPEND);
}

static void rockchip_monitor_resume(struct early_suspend *h)
{
	rockchip_clear_system_status(SYS_STATUS_SUSPEND);
}

static struct early_suspend monitor_early_suspend_handler = {
	.level = EARLY_SUSPEND_LEVEL_BLANK_SCREEN,
	.suspend = rockchip_monitor_early_suspend,
	.resume = rockchip_monitor_resume,
};
#endif

static int rockchip_eink_devfs_notifier(struct notifier_block *nb,
					unsigned long action, void *ptr)
{
	switch (action) {
	case EBC_ON:
		rockchip_set_system_status(SYS_STATUS_EBC);
		break;
	case EBC_OFF:
		rockchip_clear_system_status(SYS_STATUS_EBC);
		break;
	default:
		break;
	}

	return NOTIFY_OK;
}

static struct notifier_block rockchip_monitor_ebc_nb = {
	.notifier_call = rockchip_eink_devfs_notifier,
};

static void system_monitor_early_min_volt_function(struct work_struct *work)
{
	struct monitor_dev_info *info;

	down_read(&mdev_list_sem);
	list_for_each_entry(info, &monitor_dev_list, node)
		rockchip_system_monitor_early_regulator_uninit(info);
	up_read(&mdev_list_sem);
}

static DECLARE_DELAYED_WORK(system_monitor_early_min_volt_work,
			    system_monitor_early_min_volt_function);

static int system_monitor_ddr_trefi_update(u32 ref_mode)
{
	struct arm_smccc_res res;

	res = sip_smc_dram(0, ref_mode,
			   ROCKCHIP_SIP_CONFIG_DRAM_TREFI_UPD);
	if (res.a0 || res.a1) {
		pr_err("rockchip_sip_config_dram_trefi_upd error:%lx\n", res.a0);
		return -ENOMEM;
	}

	return 0;
}

static __maybe_unused int rk3506_system_monitor_init(struct platform_device *pdev)
{
	system_monitor->ddr_trefi_update = system_monitor_ddr_trefi_update;

	return 0;
}

static const struct of_device_id rockchip_system_monitor_of_match[] = {
	{ .compatible = "rockchip,system-monitor", .data = NULL },
#if IS_ENABLED(CONFIG_CPU_RK3506)
	{ .compatible = "rk3506,system-monitor", .data = rk3506_system_monitor_init },
#endif
	{ /* sentinel */ },
};
MODULE_DEVICE_TABLE(of, rockchip_system_monitor_of_match);

static int rockchip_system_monitor_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	int (*init)(struct platform_device *pdev);

	system_monitor = devm_kzalloc(dev, sizeof(struct system_monitor),
				      GFP_KERNEL);
	if (!system_monitor)
		return -ENOMEM;
	system_monitor->dev = dev;

	system_monitor->kobj = kobject_create_and_add("system_monitor", NULL);
	if (!system_monitor->kobj)
		return -ENOMEM;
	if (sysfs_create_file(system_monitor->kobj, &status.attr))
		dev_err(dev, "failed to create system status sysfs\n");
#ifdef CONFIG_ROCKCHIP_EARLYSUSPEND
	if (sysfs_create_file(system_monitor->kobj, &early_suspend_state.attr))
		dev_err(dev, "failed to create early suspend state sysfs\n");
#endif

	cpumask_clear(&system_monitor->status_offline_cpus);
	cpumask_clear(&system_monitor->offline_cpus);

	rockchip_system_monitor_parse_dt(system_monitor);

	init = device_get_match_data(dev);
	if (init)
		init(pdev);

	if (system_monitor->tz) {
		system_monitor->last_temp = INT_MAX;
		INIT_DELAYED_WORK(&system_monitor->thermal_work,
				  rockchip_system_monitor_thermal_check);
		mod_delayed_work(system_freezable_wq,
				 &system_monitor->thermal_work,
				 msecs_to_jiffies(system_monitor->delay));
	}

	system_monitor->status_nb.notifier_call =
		rockchip_system_status_notifier;
	rockchip_register_system_status_notifier(&system_monitor->status_nb);

	if (register_pm_notifier(&monitor_pm_nb))
		dev_err(dev, "failed to register suspend notifier\n");

	register_reboot_notifier(&rockchip_monitor_reboot_nb);

#ifdef CONFIG_FB
	if (fb_register_client(&rockchip_monitor_fb_nb))
		dev_err(dev, "failed to register fb nb\n");
#elif defined(CONFIG_ROCKCHIP_EARLYSUSPEND)
	register_early_suspend(&monitor_early_suspend_handler);
#endif

	ebc_register_notifier(&rockchip_monitor_ebc_nb);

	schedule_delayed_work(&system_monitor_early_min_volt_work,
			      msecs_to_jiffies(30000));

	dev_info(dev, "system monitor probe\n");

	return 0;
}

static struct platform_driver rockchip_system_monitor_driver = {
	.probe	= rockchip_system_monitor_probe,
	.driver = {
		.name	= "rockchip-system-monitor",
		.of_match_table = rockchip_system_monitor_of_match,
	},
};
module_platform_driver(rockchip_system_monitor_driver);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Finley Xiao <finley.xiao@rock-chips.com>");
MODULE_DESCRIPTION("rockchip system monitor driver");
