// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) Fuzhou Rockchip Electronics Co.Ltd
 * Author: Felix Zeng <felix.zeng@rock-chips.com>
 */

#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/syscalls.h>
#include <linux/debugfs.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <asm/div64.h>

#include "rknpu_drv.h"
#include "rknpu_debugger.h"

#define RKNPU_DEBUGGER_ROOT_NAME "rknpu"

static int rknpu_version_show(struct seq_file *m, void *data)
{
	seq_printf(m, "%s: v%d.%d.%d\n", DRIVER_DESC, DRIVER_MAJOR,
		   DRIVER_MINOR, DRIVER_PATCHLEVEL);

	return 0;
}

static int rknpu_load_show(struct seq_file *m, void *data)
{
	struct rknpu_debugger_node *node = m->private;
	struct rknpu_debugger *debugger = node->debugger;
	struct rknpu_device *rknpu_dev =
		container_of(debugger, struct rknpu_device, debugger);
	struct rknpu_subcore_data *subcore_data = NULL;
	unsigned long flags;
	int i;
	int load;
	uint64_t busy_time_total, div_value;

	seq_puts(m, "NPU load: ");
	for (i = 0; i < rknpu_dev->config->num_irqs; i++) {
		subcore_data = &rknpu_dev->subcore_datas[i];

		if (rknpu_dev->config->num_irqs > 1)
			seq_printf(m, " Core%d: ", i);

		spin_lock_irqsave(&rknpu_dev->irq_lock, flags);

		busy_time_total = subcore_data->timer.busy_time_record;

		spin_unlock_irqrestore(&rknpu_dev->irq_lock, flags);

		div_value = (RKNPU_LOAD_INTERVAL / 100000);
		do_div(busy_time_total, div_value);
		load = busy_time_total;

		if (rknpu_dev->config->num_irqs > 1)
			seq_printf(m, "%2.d%%,", load);
		else
			seq_printf(m, "%2.d%%", load);
	}
	seq_puts(m, "\n");

	return 0;
}

static int rknpu_power_show(struct seq_file *m, void *data)
{
	struct rknpu_debugger_node *node = m->private;
	struct rknpu_debugger *debugger = node->debugger;
	struct rknpu_device *rknpu_dev =
		container_of(debugger, struct rknpu_device, debugger);

	if (rknpu_dev->is_powered)
		seq_puts(m, "on\n");
	else
		seq_puts(m, "off\n");

	return 0;
}

static ssize_t rknpu_power_set(struct file *file, const char __user *ubuf,
			       size_t len, loff_t *offp)
{
	struct seq_file *priv = file->private_data;
	struct rknpu_debugger_node *node = priv->private;
	struct rknpu_debugger *debugger = node->debugger;
	struct rknpu_device *rknpu_dev =
		container_of(debugger, struct rknpu_device, debugger);
	struct rknpu_action args;
	char buf[10];

	if (len > sizeof(buf) - 1)
		return -EINVAL;
	if (copy_from_user(buf, ubuf, len))
		return -EFAULT;
	buf[len - 1] = '\0';

	if (strcmp(buf, "on") == 0) {
		atomic_inc(&rknpu_dev->cmdline_power_refcount);
		args.flags = RKNPU_POWER_ON;
		rknpu_action(rknpu_dev, &args);
		LOG_INFO("rknpu power is on!");
	} else if (strcmp(buf, "off") == 0) {
		if (rknpu_dev->is_powered &&
		    atomic_dec_if_positive(
			    &rknpu_dev->cmdline_power_refcount) >= 0) {
			atomic_sub(
				atomic_read(&rknpu_dev->cmdline_power_refcount),
				&rknpu_dev->power_refcount);
			atomic_set(&rknpu_dev->cmdline_power_refcount, 0);
			args.flags = RKNPU_POWER_OFF;
			rknpu_action(rknpu_dev, &args);
		}
		if (!rknpu_dev->is_powered)
			LOG_INFO("rknpu power is off!");
	} else {
		LOG_ERROR("rknpu power node params is invalid!");
	}

	return len;
}

struct rknpu_debugger_list rknpu_debugger_root_list[] = {
	{ "driver_version", rknpu_version_show, NULL, NULL },
	{ "load", rknpu_load_show, NULL, NULL },
	{ "power", rknpu_power_show, rknpu_power_set, NULL }
};

static ssize_t rknpu_debugger_write(struct file *file, const char __user *ubuf,
				    size_t len, loff_t *offp)
{
	struct seq_file *priv = file->private_data;
	struct rknpu_debugger_node *node = priv->private;

	if (node->info_ent->write)
		return node->info_ent->write(file, ubuf, len, offp);
	else
		return len;
}

static int rknpu_debugfs_open(struct inode *inode, struct file *file)
{
	struct rknpu_debugger_node *node = inode->i_private;

	return single_open(file, node->info_ent->show, node);
}

static const struct file_operations rknpu_debugfs_fops = {
	.owner = THIS_MODULE,
	.open = rknpu_debugfs_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
	.write = rknpu_debugger_write,
};

#ifdef CONFIG_ROCKCHIP_RKNPU_DEBUG_FS
static int rknpu_debugfs_remove_files(struct rknpu_debugger *debugger)
{
	struct rknpu_debugger_node *pos, *q;
	struct list_head *entry_list;

	mutex_lock(&debugger->debugfs_lock);

	/* Delete debugfs entry list */
	entry_list = &debugger->debugfs_entry_list;
	list_for_each_entry_safe(pos, q, entry_list, list) {
		if (pos->dent == NULL)
			continue;
		list_del(&pos->list);
		kfree(pos);
		pos = NULL;
	}

	/* Delete all debugfs node in this directory */
	debugfs_remove_recursive(debugger->debugfs_dir);
	debugger->debugfs_dir = NULL;

	mutex_unlock(&debugger->debugfs_lock);

	return 0;
}

static int rknpu_debugfs_create_files(const struct rknpu_debugger_list *files,
				      int count, struct dentry *root,
				      struct rknpu_debugger *debugger)
{
	int i;
	struct dentry *ent;
	struct rknpu_debugger_node *tmp;

	for (i = 0; i < count; i++) {
		tmp = kmalloc(sizeof(struct rknpu_debugger_node), GFP_KERNEL);
		if (tmp == NULL) {
			LOG_ERROR(
				"Cannot alloc node path /sys/kernel/debug/%pd/%s\n",
				root, files[i].name);
			goto MALLOC_FAIL;
		}

		tmp->info_ent = &files[i];
		tmp->debugger = debugger;

		ent = debugfs_create_file(files[i].name, S_IFREG | S_IRUGO,
					  root, tmp, &rknpu_debugfs_fops);
		if (!ent) {
			LOG_ERROR("Cannot create /sys/kernel/debug/%pd/%s\n",
				  root, files[i].name);
			goto CREATE_FAIL;
		}

		tmp->dent = ent;

		mutex_lock(&debugger->debugfs_lock);
		list_add_tail(&tmp->list, &debugger->debugfs_entry_list);
		mutex_unlock(&debugger->debugfs_lock);
	}

	return 0;

CREATE_FAIL:
	kfree(tmp);
MALLOC_FAIL:
	rknpu_debugfs_remove_files(debugger);

	return -1;
}

static int rknpu_debugfs_remove(struct rknpu_debugger *debugger)
{
	rknpu_debugfs_remove_files(debugger);

	return 0;
}

static int rknpu_debugfs_init(struct rknpu_debugger *debugger)
{
	int ret;

	debugger->debugfs_dir =
		debugfs_create_dir(RKNPU_DEBUGGER_ROOT_NAME, NULL);
	if (IS_ERR_OR_NULL(debugger->debugfs_dir)) {
		LOG_ERROR("failed on mkdir /sys/kernel/debug/%s\n",
			  RKNPU_DEBUGGER_ROOT_NAME);
		debugger->debugfs_dir = NULL;
		return -EIO;
	}

	ret = rknpu_debugfs_create_files(rknpu_debugger_root_list,
					 ARRAY_SIZE(rknpu_debugger_root_list),
					 debugger->debugfs_dir, debugger);
	if (ret) {
		LOG_ERROR(
			"Could not install rknpu_debugger_root_list debugfs\n");
		goto CREATE_FAIL;
	}

	return 0;

CREATE_FAIL:
	rknpu_debugfs_remove(debugger);

	return ret;
}
#endif /* #ifdef CONFIG_ROCKCHIP_RKNPU_DEBUG_FS */

#ifdef CONFIG_ROCKCHIP_RKNPU_PROC_FS
static int rknpu_procfs_open(struct inode *inode, struct file *file)
{
	struct rknpu_debugger_node *node = PDE_DATA(inode);

	return single_open(file, node->info_ent->show, node);
}

static const struct proc_ops rknpu_procfs_fops = {
	.proc_open = rknpu_procfs_open,
	.proc_read = seq_read,
	.proc_lseek = seq_lseek,
	.proc_release = single_release,
	.proc_write = rknpu_debugger_write,
};

static int rknpu_procfs_remove_files(struct rknpu_debugger *debugger)
{
	struct rknpu_debugger_node *pos, *q;
	struct list_head *entry_list;

	mutex_lock(&debugger->procfs_lock);

	/* Delete procfs entry list */
	entry_list = &debugger->procfs_entry_list;
	list_for_each_entry_safe(pos, q, entry_list, list) {
		if (pos->pent == NULL)
			continue;
		list_del(&pos->list);
		kfree(pos);
		pos = NULL;
	}

	/* Delete all procfs node in this directory */
	proc_remove(debugger->procfs_dir);
	debugger->procfs_dir = NULL;

	mutex_unlock(&debugger->procfs_lock);

	return 0;
}

static int rknpu_procfs_create_files(const struct rknpu_debugger_list *files,
				     int count, struct proc_dir_entry *root,
				     struct rknpu_debugger *debugger)
{
	int i;
	struct proc_dir_entry *ent;
	struct rknpu_debugger_node *tmp;

	for (i = 0; i < count; i++) {
		tmp = kmalloc(sizeof(struct rknpu_debugger_node), GFP_KERNEL);
		if (tmp == NULL) {
			LOG_ERROR("Cannot alloc node path for /proc/%s/%s\n",
				  RKNPU_DEBUGGER_ROOT_NAME, files[i].name);
			goto MALLOC_FAIL;
		}

		tmp->info_ent = &files[i];
		tmp->debugger = debugger;

		ent = proc_create_data(files[i].name, S_IFREG | S_IRUGO, root,
				       &rknpu_procfs_fops, tmp);
		if (!ent) {
			LOG_ERROR("Cannot create /proc/%s/%s\n",
				  RKNPU_DEBUGGER_ROOT_NAME, files[i].name);
			goto CREATE_FAIL;
		}

		tmp->pent = ent;

		mutex_lock(&debugger->procfs_lock);
		list_add_tail(&tmp->list, &debugger->procfs_entry_list);
		mutex_unlock(&debugger->procfs_lock);
	}

	return 0;

CREATE_FAIL:
	kfree(tmp);
MALLOC_FAIL:
	rknpu_procfs_remove_files(debugger);
	return -1;
}

int rknpu_procfs_remove(struct rknpu_debugger *debugger)
{
	rknpu_procfs_remove_files(debugger);

	return 0;
}

int rknpu_procfs_init(struct rknpu_debugger *debugger)
{
	int ret;

	debugger->procfs_dir = proc_mkdir(RKNPU_DEBUGGER_ROOT_NAME, NULL);
	if (IS_ERR_OR_NULL(debugger->procfs_dir)) {
		pr_err("failed on mkdir /proc/%s\n", RKNPU_DEBUGGER_ROOT_NAME);
		debugger->procfs_dir = NULL;
		return -EIO;
	}

	ret = rknpu_procfs_create_files(rknpu_debugger_root_list,
					ARRAY_SIZE(rknpu_debugger_root_list),
					debugger->procfs_dir, debugger);
	if (ret) {
		pr_err("Could not install rknpu_debugger_root_list procfs\n");
		goto CREATE_FAIL;
	}

	return 0;

CREATE_FAIL:
	rknpu_procfs_remove(debugger);

	return ret;
}
#endif /* #ifdef CONFIG_ROCKCHIP_RKNPU_PROC_FS */

int rknpu_debugger_init(struct rknpu_device *rknpu_dev)
{
#ifdef CONFIG_ROCKCHIP_RKNPU_DEBUG_FS
	mutex_init(&rknpu_dev->debugger.debugfs_lock);
	INIT_LIST_HEAD(&rknpu_dev->debugger.debugfs_entry_list);
	rknpu_debugfs_init(&rknpu_dev->debugger);
#endif
#ifdef CONFIG_ROCKCHIP_RKNPU_PROC_FS
	mutex_init(&rknpu_dev->debugger.procfs_lock);
	INIT_LIST_HEAD(&rknpu_dev->debugger.procfs_entry_list);
	rknpu_procfs_init(&rknpu_dev->debugger);
#endif
	return 0;
}

int rknpu_debugger_remove(struct rknpu_device *rknpu_dev)
{
#ifdef CONFIG_ROCKCHIP_RKNPU_DEBUG_FS
	rknpu_debugfs_remove(&rknpu_dev->debugger);
#endif
#ifdef CONFIG_ROCKCHIP_RKNPU_PROC_FS
	rknpu_procfs_remove(&rknpu_dev->debugger);
#endif
	return 0;
}
