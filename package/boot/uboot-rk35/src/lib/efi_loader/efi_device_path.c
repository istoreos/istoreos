/*
 * EFI device path from u-boot device-model mapping
 *
 * (C) Copyright 2017 Rob Clark
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <blk.h>
#include <dm.h>
#include <usb.h>
#include <mmc.h>
#include <efi_loader.h>
#include <inttypes.h>
#include <part.h>

/* template END node: */
static const struct efi_device_path END = {
	.type     = DEVICE_PATH_TYPE_END,
	.sub_type = DEVICE_PATH_SUB_TYPE_END,
	.length   = sizeof(END),
};

#define U_BOOT_GUID \
	EFI_GUID(0xe61d73b9, 0xa384, 0x4acc, \
		 0xae, 0xab, 0x82, 0xe8, 0x28, 0xf3, 0x62, 0x8b)

/* template ROOT node: */
static const struct efi_device_path_vendor ROOT = {
	.dp = {
		.type     = DEVICE_PATH_TYPE_HARDWARE_DEVICE,
		.sub_type = DEVICE_PATH_SUB_TYPE_VENDOR,
		.length   = sizeof(ROOT),
	},
	.guid = U_BOOT_GUID,
};

static void *dp_alloc(size_t sz)
{
	void *buf;

	if (efi_allocate_pool(EFI_ALLOCATE_ANY_PAGES, sz, &buf) != EFI_SUCCESS)
		return NULL;

	return buf;
}

/*
 * Iterate to next block in device-path, terminating (returning NULL)
 * at /End* node.
 */
struct efi_device_path *efi_dp_next(const struct efi_device_path *dp)
{
	if (dp == NULL)
		return NULL;
	if (dp->type == DEVICE_PATH_TYPE_END)
		return NULL;
	dp = ((void *)dp) + dp->length;
	if (dp->type == DEVICE_PATH_TYPE_END)
		return NULL;
	return (struct efi_device_path *)dp;
}

/*
 * Compare two device-paths, stopping when the shorter of the two hits
 * an End* node.  This is useful to, for example, compare a device-path
 * representing a device with one representing a file on the device, or
 * a device with a parent device.
 */
int efi_dp_match(struct efi_device_path *a, struct efi_device_path *b)
{
	while (1) {
		int ret;

		ret = memcmp(&a->length, &b->length, sizeof(a->length));
		if (ret)
			return ret;

		ret = memcmp(a, b, a->length);
		if (ret)
			return ret;

		a = efi_dp_next(a);
		b = efi_dp_next(b);

		if (!a || !b)
			return 0;
	}
}


/*
 * See UEFI spec (section 3.1.2, about short-form device-paths..
 * tl;dr: we can have a device-path that starts with a USB WWID
 * or USB Class node, and a few other cases which don't encode
 * the full device path with bus hierarchy:
 *
 *   - MESSAGING:USB_WWID
 *   - MESSAGING:USB_CLASS
 *   - MEDIA:FILE_PATH
 *   - MEDIA:HARD_DRIVE
 *   - MESSAGING:URI
 */
static struct efi_device_path *shorten_path(struct efi_device_path *dp)
{
	while (dp) {
		/*
		 * TODO: Add MESSAGING:USB_WWID and MESSAGING:URI..
		 * in practice fallback.efi just uses MEDIA:HARD_DRIVE
		 * so not sure when we would see these other cases.
		 */
		if (EFI_DP_TYPE(dp, MESSAGING_DEVICE, MSG_USB_CLASS) ||
		    EFI_DP_TYPE(dp, MEDIA_DEVICE, HARD_DRIVE_PATH) ||
		    EFI_DP_TYPE(dp, MEDIA_DEVICE, FILE_PATH))
			return dp;

		dp = efi_dp_next(dp);
	}

	return dp;
}

static struct efi_object *find_obj(struct efi_device_path *dp, bool short_path,
				   struct efi_device_path **rem)
{
	struct efi_object *efiobj;

	list_for_each_entry(efiobj, &efi_obj_list, link) {
		int i;

		for (i = 0; i < ARRAY_SIZE(efiobj->protocols); i++) {
			struct efi_handler *handler = &efiobj->protocols[i];
			struct efi_device_path *obj_dp;

			if (!handler->guid)
				break;

			if (guidcmp(handler->guid, &efi_guid_device_path))
				continue;

			obj_dp = handler->protocol_interface;

			do {
				if (efi_dp_match(dp, obj_dp) == 0) {
					if (rem) {
						*rem = ((void *)dp) +
							efi_dp_size(obj_dp);
					}
					return efiobj;
				}

				obj_dp = shorten_path(efi_dp_next(obj_dp));
			} while (short_path && obj_dp);
		}
	}

	return NULL;
}


/*
 * Find an efiobj from device-path, if 'rem' is not NULL, returns the
 * remaining part of the device path after the matched object.
 */
struct efi_object *efi_dp_find_obj(struct efi_device_path *dp,
				   struct efi_device_path **rem)
{
	struct efi_object *efiobj;

	efiobj = find_obj(dp, false, rem);

	if (!efiobj)
		efiobj = find_obj(dp, true, rem);

	return efiobj;
}

/* return size not including End node: */
unsigned efi_dp_size(const struct efi_device_path *dp)
{
	unsigned sz = 0;

	while (dp) {
		sz += dp->length;
		dp = efi_dp_next(dp);
	}

	return sz;
}

struct efi_device_path *efi_dp_dup(const struct efi_device_path *dp)
{
	struct efi_device_path *ndp;
	unsigned sz = efi_dp_size(dp) + sizeof(END);

	if (!dp)
		return NULL;

	ndp = dp_alloc(sz);
	memcpy(ndp, dp, sz);

	return ndp;
}

struct efi_device_path *efi_dp_append(const struct efi_device_path *dp1,
				      const struct efi_device_path *dp2)
{
	struct efi_device_path *ret;

	if (!dp1) {
		ret = efi_dp_dup(dp2);
	} else if (!dp2) {
		ret = efi_dp_dup(dp1);
	} else {
		/* both dp1 and dp2 are non-null */
		unsigned sz1 = efi_dp_size(dp1);
		unsigned sz2 = efi_dp_size(dp2);
		void *p = dp_alloc(sz1 + sz2 + sizeof(END));
		memcpy(p, dp1, sz1);
		memcpy(p + sz1, dp2, sz2);
		memcpy(p + sz1 + sz2, &END, sizeof(END));
		ret = p;
	}

	return ret;
}

struct efi_device_path *efi_dp_append_node(const struct efi_device_path *dp,
					   const struct efi_device_path *node)
{
	struct efi_device_path *ret;

	if (!node && !dp) {
		ret = efi_dp_dup(&END);
	} else if (!node) {
		ret = efi_dp_dup(dp);
	} else if (!dp) {
		unsigned sz = node->length;
		void *p = dp_alloc(sz + sizeof(END));
		memcpy(p, node, sz);
		memcpy(p + sz, &END, sizeof(END));
		ret = p;
	} else {
		/* both dp and node are non-null */
		unsigned sz = efi_dp_size(dp);
		void *p = dp_alloc(sz + node->length + sizeof(END));
		memcpy(p, dp, sz);
		memcpy(p + sz, node, node->length);
		memcpy(p + sz + node->length, &END, sizeof(END));
		ret = p;
	}

	return ret;
}

#ifdef CONFIG_DM
/* size of device-path not including END node for device and all parents
 * up to the root device.
 */
static unsigned dp_size(struct udevice *dev)
{
	if (!dev || !dev->driver)
		return sizeof(ROOT);

	switch (dev->driver->id) {
	case UCLASS_ROOT:
	case UCLASS_SIMPLE_BUS:
		/* stop traversing parents at this point: */
		return sizeof(ROOT);
	case UCLASS_MMC:
		return dp_size(dev->parent) +
			sizeof(struct efi_device_path_sd_mmc_path);
	case UCLASS_MASS_STORAGE:
	case UCLASS_USB_HUB:
		return dp_size(dev->parent) +
			sizeof(struct efi_device_path_usb_class);
	default:
		/* just skip over unknown classes: */
		return dp_size(dev->parent);
	}
}

static void *dp_fill(void *buf, struct udevice *dev)
{
	if (!dev || !dev->driver)
		return buf;

	switch (dev->driver->id) {
	case UCLASS_ROOT:
	case UCLASS_SIMPLE_BUS: {
		/* stop traversing parents at this point: */
		struct efi_device_path_vendor *vdp = buf;
		*vdp = ROOT;
		return &vdp[1];
	}
#if defined(CONFIG_DM_MMC) && defined(CONFIG_MMC)
	case UCLASS_MMC: {
		struct efi_device_path_sd_mmc_path *sddp =
			dp_fill(buf, dev->parent);
		struct mmc *mmc = mmc_get_mmc_dev(dev);
		struct blk_desc *desc = mmc_get_blk_desc(mmc);

		sddp->dp.type     = DEVICE_PATH_TYPE_MESSAGING_DEVICE;
		sddp->dp.sub_type = (desc->if_type == IF_TYPE_MMC) ?
			DEVICE_PATH_SUB_TYPE_MSG_MMC :
			DEVICE_PATH_SUB_TYPE_MSG_SD;
		sddp->dp.length   = sizeof(*sddp);
		sddp->slot_number = dev->seq;

		return &sddp[1];
	}
#endif
	case UCLASS_MASS_STORAGE:
	case UCLASS_USB_HUB: {
		struct efi_device_path_usb_class *udp =
			dp_fill(buf, dev->parent);
		struct usb_device *udev = dev_get_parent_priv(dev);
		struct usb_device_descriptor *desc = &udev->descriptor;

		udp->dp.type     = DEVICE_PATH_TYPE_MESSAGING_DEVICE;
		udp->dp.sub_type = DEVICE_PATH_SUB_TYPE_MSG_USB_CLASS;
		udp->dp.length   = sizeof(*udp);
		udp->vendor_id   = desc->idVendor;
		udp->product_id  = desc->idProduct;
		udp->device_class    = desc->bDeviceClass;
		udp->device_subclass = desc->bDeviceSubClass;
		udp->device_protocol = desc->bDeviceProtocol;

		return &udp[1];
	}
	default:
		debug("unhandled device class: %s (%u)\n",
		      dev->name, dev->driver->id);
		return dp_fill(buf, dev->parent);
	}
}

/* Construct a device-path from a device: */
struct efi_device_path *efi_dp_from_dev(struct udevice *dev)
{
	void *buf, *start;

	start = buf = dp_alloc(dp_size(dev) + sizeof(END));
	buf = dp_fill(buf, dev);
	*((struct efi_device_path *)buf) = END;

	return start;
}
#endif

static unsigned dp_part_size(struct blk_desc *desc, int part)
{
	unsigned dpsize;

#ifdef CONFIG_BLK
	dpsize = dp_size(desc->bdev->parent);
#else
	dpsize = sizeof(ROOT) + sizeof(struct efi_device_path_usb);
#endif

	if (part == 0) /* the actual disk, not a partition */
		return dpsize;

	if (desc->part_type == PART_TYPE_ISO)
		dpsize += sizeof(struct efi_device_path_cdrom_path);
	else
		dpsize += sizeof(struct efi_device_path_hard_drive_path);

	return dpsize;
}

static void *dp_part_fill(void *buf, struct blk_desc *desc, int part)
{
	disk_partition_t info;

#ifdef CONFIG_BLK
	buf = dp_fill(buf, desc->bdev->parent);
#else
	/*
	 * We *could* make a more accurate path, by looking at if_type
	 * and handling all the different cases like we do for non-
	 * legacy (ie CONFIG_BLK=y) case.  But most important thing
	 * is just to have a unique device-path for if_type+devnum.
	 * So map things to a fictional USB device:
	 */
	struct efi_device_path_usb *udp;

	memcpy(buf, &ROOT, sizeof(ROOT));
	buf += sizeof(ROOT);

	udp = buf;
	udp->dp.type = DEVICE_PATH_TYPE_MESSAGING_DEVICE;
	udp->dp.sub_type = DEVICE_PATH_SUB_TYPE_MSG_USB;
	udp->dp.length = sizeof(*udp);
	udp->parent_port_number = desc->if_type;
	udp->usb_interface = desc->devnum;
	buf = &udp[1];
#endif

	if (part == 0) /* the actual disk, not a partition */
		return buf;

	part_get_info(desc, part, &info);

	if (desc->part_type == PART_TYPE_ISO) {
		struct efi_device_path_cdrom_path *cddp = buf;

		cddp->boot_entry = part - 1;
		cddp->dp.type = DEVICE_PATH_TYPE_MEDIA_DEVICE;
		cddp->dp.sub_type = DEVICE_PATH_SUB_TYPE_CDROM_PATH;
		cddp->dp.length = sizeof(*cddp);
		cddp->partition_start = info.start;
		cddp->partition_end = info.size;

		buf = &cddp[1];
	} else {
		struct efi_device_path_hard_drive_path *hddp = buf;

		hddp->dp.type = DEVICE_PATH_TYPE_MEDIA_DEVICE;
		hddp->dp.sub_type = DEVICE_PATH_SUB_TYPE_HARD_DRIVE_PATH;
		hddp->dp.length = sizeof(*hddp);
		hddp->partition_number = part - 1;
		hddp->partition_start = info.start;
		hddp->partition_end = info.size;
		if (desc->part_type == PART_TYPE_EFI)
			hddp->partmap_type = 2;
		else
			hddp->partmap_type = 1;
		hddp->signature_type = desc->sig_type;
		if (hddp->signature_type != 0)
			memcpy(hddp->partition_signature, &desc->guid_sig,
			       sizeof(hddp->partition_signature));

		buf = &hddp[1];
	}

	return buf;
}


/* Construct a device-path from a partition on a blk device: */
struct efi_device_path *efi_dp_from_part(struct blk_desc *desc, int part)
{
	void *buf, *start;

	start = buf = dp_alloc(dp_part_size(desc, part) + sizeof(END));

	buf = dp_part_fill(buf, desc, part);

	*((struct efi_device_path *)buf) = END;

	return start;
}

/* convert path to an UEFI style path (ie. DOS style backslashes and utf16) */
static void path_to_uefi(u16 *uefi, const char *path)
{
	while (*path) {
		char c = *(path++);
		if (c == '/')
			c = '\\';
		*(uefi++) = c;
	}
	*uefi = '\0';
}

/*
 * If desc is NULL, this creates a path with only the file component,
 * otherwise it creates a full path with both device and file components
 */
struct efi_device_path *efi_dp_from_file(struct blk_desc *desc, int part,
		const char *path)
{
	struct efi_device_path_file_path *fp;
	void *buf, *start;
	unsigned dpsize = 0, fpsize;

	if (desc)
		dpsize = dp_part_size(desc, part);

	fpsize = sizeof(struct efi_device_path) + 2 * (strlen(path) + 1);
	dpsize += fpsize;

	start = buf = dp_alloc(dpsize + sizeof(END));

	if (desc)
		buf = dp_part_fill(buf, desc, part);

	/* add file-path: */
	fp = buf;
	fp->dp.type = DEVICE_PATH_TYPE_MEDIA_DEVICE;
	fp->dp.sub_type = DEVICE_PATH_SUB_TYPE_FILE_PATH;
	fp->dp.length = fpsize;
	path_to_uefi(fp->str, path);
	buf += fpsize;

	*((struct efi_device_path *)buf) = END;

	return start;
}

#ifdef CONFIG_NET
struct efi_device_path *efi_dp_from_eth(void)
{
	struct efi_device_path_mac_addr *ndp;
	void *buf, *start;
	unsigned dpsize = 0;

	assert(eth_get_dev());

#ifdef CONFIG_DM_ETH
	dpsize += dp_size(eth_get_dev());
#else
	dpsize += sizeof(ROOT);
#endif
	dpsize += sizeof(*ndp);

	start = buf = dp_alloc(dpsize + sizeof(END));

#ifdef CONFIG_DM_ETH
	buf = dp_fill(buf, eth_get_dev());
#else
	memcpy(buf, &ROOT, sizeof(ROOT));
	buf += sizeof(ROOT);
#endif

	ndp = buf;
	ndp->dp.type = DEVICE_PATH_TYPE_MESSAGING_DEVICE;
	ndp->dp.sub_type = DEVICE_PATH_SUB_TYPE_MSG_MAC_ADDR;
	ndp->dp.length = sizeof(*ndp);
	memcpy(ndp->mac.addr, eth_get_ethaddr(), ARP_HLEN);
	buf = &ndp[1];

	*((struct efi_device_path *)buf) = END;

	return start;
}
#endif

/*
 * Helper to split a full device path (containing both device and file
 * parts) into it's constituent parts.
 */
void efi_dp_split_file_path(struct efi_device_path *full_path,
			    struct efi_device_path **device_path,
			    struct efi_device_path **file_path)
{
	struct efi_device_path *p, *dp, *fp;

	dp = efi_dp_dup(full_path);
	p = dp;
	while (!EFI_DP_TYPE(p, MEDIA_DEVICE, FILE_PATH))
		p = efi_dp_next(p);
	fp = efi_dp_dup(p);

	p->type = DEVICE_PATH_TYPE_END;
	p->sub_type = DEVICE_PATH_SUB_TYPE_END;
	p->length = sizeof(*p);

	*device_path = dp;
	*file_path = fp;
}
