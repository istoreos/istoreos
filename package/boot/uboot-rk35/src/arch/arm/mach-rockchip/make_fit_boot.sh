#!/bin/bash
#
# Copyright (C) 2020 Rockchip Electronics Co., Ltd
#
# SPDX-License-Identifier:     GPL-2.0+
#

# Process args and auto set variables
source ./${srctree}/arch/arm/mach-rockchip/fit_args.sh

if [ ! -f ${srctree}/images/ramdisk ]; then
	touch ${srctree}/images/ramdisk
fi

if [ "${COMPRESSION}" == "gzip" ]; then
	gzip -k -f -9 ${srctree}/images/kernel
	SUFFIX=".gz"
elif [ "${COMPRESSION}" == "lz4" ]; then
	${srctree}/scripts/compress.sh lz4 ${srctree}/images/kernel
	SUFFIX=".lz4"
else
	COMPRESSION="none"
	SUFFIX=
fi

if grep  -q '^CONFIG_FIT_ENABLE_RSASSA_PSS_SUPPORT=y' .config ; then
	ALGO_PADDING="				padding = \"pss\";"
fi

cat << EOF
/*
 * Copyright (C) 2020 Fuzhou Rockchip Electronics Co., Ltd
 *
 * Minimal dts for a FIT image.
 *
 * SPDX-License-Identifier: GPL-2.0
 */

/dts-v1/;
/ {
	description = "FIT source file for Linux";
	#address-cells = <1>;

	images {
		fdt {
			data = /incbin/("./images/dtb");
			type = "flat_dt";
			arch = "${ARCH}";
			compression = "none";
			load  = <0xffffff00>;
			hash {
				algo = "sha256";
			};
		};

		kernel {
			data = /incbin/("./images/kernel${SUFFIX}");
			compression = "${COMPRESSION}";
			type = "kernel";
			arch = "${ARCH}";
			os = "linux";
			entry = <0xffffff01>;
			load  = <0xffffff01>;
			hash {
				algo = "sha256";
			};
		};

		ramdisk {
			data = /incbin/("./images/ramdisk");
			compression = "none";
			type = "ramdisk";
			arch = "${ARCH}";
			os = "linux";
			load  = <0xffffff02>;
			hash {
				algo = "sha256";
			};
		};

		resource {
			data = /incbin/("./images/second");
			type = "multi";
			arch = "${ARCH}";
			compression = "none";
			hash {
				algo = "sha256";
			};
		};
	};

	configurations {
		default = "conf";
		conf {
			description = "Boot Linux kernel with FDT blob";
			rollback-index = <0x0>;
			fdt = "fdt";
			kernel = "kernel";
			ramdisk = "ramdisk";
			multi = "resource";
			signature {
				algo = "sha256,rsa2048";
				${ALGO_PADDING}
				key-name-hint = "dev";
				sign-images = "fdt", "kernel", "ramdisk", "multi";
			};
		};
	};
};

EOF
