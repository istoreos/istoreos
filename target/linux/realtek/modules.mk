RTK_MENU:=Realtek kernel options

define KernelPackage/rtk-spi
  SUBMENU:=$(RTK_MENU)
  TITLE:=Realtek SPI NOR flash driver
  KCONFIG:= \
	CONFIG_MTD=y \
	CONFIG_MTD_BLKDEVS=y \
	CONFIG_MTD_BLOCK=y \
	CONFIG_MTD_CFI=n \
	CONFIG_MTD_CMDLINE_PARTS=y \
	CONFIG_MTD_COMPLEX_MAPPINGS=n \
	CONFIG_MTD_NAND=n \
	CONFIG_MTD_NAND_IDS=n \
	CONFIG_MTD_OF_PARTS=y \
	CONFIG_MTD_RTK_SFC=y \
	CONFIG_MTD_RTK_SFC_DEBUG=n \
	CONFIG_MTD_RTK_SFC_READ_MD=y \
	CONFIG_MTD_RTK_SFC_WRITE_MD=y \
	CONFIG_MTD_RTK_SFC_PSTORE=y \
	CONFIG_PSTORE=y \
	NOR_AUTO_HW_POLLING=y

  FILES:=
  AUTOLOAD:=
  DEPENDS:=@TARGET_realtek
endef

define KernelPackage/rtk-spi/description
  This package contains the Realtek SPI NOR flash driver.
endef

$(eval $(call KernelPackage,rtk-spi))

define KernelPackage/rtk-nand
  SUBMENU:=$(RTK_MENU)
  TITLE:=Realtek NAND flash driver
  KCONFIG:= \
	CONFIG_MTD=y \
	CONFIG_MTD_BLOCK=y \
	CONFIG_MTD_BLOCK_RO=n \
	CONFIG_MTD_CFI=n \
	CONFIG_MTD_CMDLINE_PARTS=y \
	CONFIG_MTD_COMPLEX_MAPPINGS=n \
	CONFIG_MTD_NAND=y \
	CONFIG_MTD_NAND_ECC=y \
	CONFIG_MTD_NAND_IDS=y \
	CONFIG_MTD_OF_PARTS=y \
	CONFIG_MTD_SM_COMMON=n \
	CONFIG_MTD_UBI=y \
	CONFIG_MTD_UBI_BEB_LIMIT=20 \
	CONFIG_MTD_UBI_BLOCK=y \
	CONFIG_MTD_UBI_FASTMAP=n \
	CONFIG_MTD_UBI_GLUEBI=n \
	CONFIG_MTD_UBI_WL_THRESHOLD=1024 \
	CONFIG_OF_MTD=y \
	CONFIG_UBIFS_FS=y \
	CONFIG_UBIFS_FS_ADVANCED_COMPR=n \
	CONFIG_UBIFS_FS_LZO=y \
	CONFIG_UBIFS_FS_ZLIB=y
  FILES:=
  AUTOLOAD:=
  DEPENDS:=@TARGET_realtek @DEFAULT_kmod-rtk-nand
endef

define KernelPackage/rtk-nand/config
	select NAND_SUPPORT
	select USES_UBIFS
endef

define KernelPackage/rtk-nand/description
  This package contains the Realtek NAND flash driver.
endef

$(eval $(call KernelPackage,rtk-nand))

define KernelPackage/rtk-emmc
  SUBMENU:=$(RTK_MENU)
  TITLE:=Realtek eMMC driver
  KCONFIG:= \
	CONFIG_MMC=y \
	CONFIG_MMC_BLOCK=y \
	CONFIG_MMC_EMBEDDED_SDIO=n \
	CONFIG_MMC_PARANOID_SD_INIT=n \
	CONFIG_MMC_RTK_EMMC=y \
	CONFIG_MMC_RTKEMMC_JIFFY_NOT_WORK_ON_1_LAYER_FPGA=n \
	CONFIG_MMC_SDHCI=n \
	CONFIG_MMC_SIMULATE_MAX_SPEED=n \
	CONFIG_MMC_TIFM_SD=n

  FILES:=
  AUTOLOAD:=
  DEPENDS:=@TARGET_realtek
  CONFLICTS:=kmod-rtk-nand
endef

define KernelPackage/rtk-emmc/description
  This package enables the Realtek eMMC driver.
endef

$(eval $(call KernelPackage,rtk-emmc))

define KernelPackage/rtk-sdmmc
  SUBMENU:=$(RTK_MENU)
  TITLE:=Realtek SD MMC driver
  KCONFIG:= \
	CONFIG_MMC=y \
	CONFIG_MMC_BLOCK=y \
	CONFIG_MMC_EMBEDDED_SDIO=n \
	CONFIG_MMC_PARANOID_SD_INIT=n \
	CONFIG_MMC_RTK_SDMMC=y \
	CONFIG_MMC_RTK_SDMMC_DEBUG=n \
	CONFIG_MMC_SDHCI=n \
	CONFIG_MMC_SIMULATE_MAX_SPEED=n \
	CONFIG_MMC_TIFM_SD=n

  FILES:=
  AUTOLOAD:=
  DEPENDS:=@TARGET_realtek
  CONFLICTS:=kmod-rtk-nand
endef

define KernelPackage/rtk-sdmmc/description
  This package enables the Realtek SD MMC driver.
endef

$(eval $(call KernelPackage,rtk-sdmmc))

define KernelPackage/rtl8169soc
  SUBMENU:=$(RTK_MENU)
  TITLE:=Realtek Gigabit Ethernet driver
  DEFAULT:=y
  KCONFIG:= \
	CONFIG_R8169SOC=y \
	CONFIG_RTL_RX_NO_COPY=y \
	CONFIG_NET_VENDOR_REALTEK=y
  FILES:=
  AUTOLOAD:=
  DEPENDS:=@TARGET_realtek
  CONFLICTS:=kmod-rtd1295hwnat
endef

define KernelPackage/rtl8169soc/description
  This package contains the Realtek Gigibit Ethernet driver
endef

$(eval $(call KernelPackage,rtl8169soc))

define KernelPackage/rtl8125
  SUBMENU:=$(RTK_MENU)
  TITLE:=Realtek R8125 PCI-E 2.5 Gigabit Ethernet driver
  DEPENDS:=@TARGET_realtek @PCI_SUPPORT +kmod-mii
  KCONFIG:=CONFIG_R8125
  FILES:=$(LINUX_DIR)/drivers/net/ethernet/realtek/r8125/r8125.ko
  AUTOLOAD:=$(call AutoProbe,r8125)
endef

define KernelPackage/rtl8125/description
  This package contains the Realtek R8125 PCI-E 2.5 Gigibit Ethernet driver
endef

$(eval $(call KernelPackage,rtl8125))

define KernelPackage/rtl8168
  SUBMENU:=$(RTK_MENU)
  TITLE:=Realtek R8168 PCI-E Gigabit Ethernet driver
  DEPENDS:=@TARGET_realtek @PCI_SUPPORT +kmod-mii
  KCONFIG:=CONFIG_R8168
  FILES:=$(LINUX_DIR)/drivers/net/ethernet/realtek/r8168/r8168.ko
  AUTOLOAD:=$(call AutoProbe,r8168)
endef

define KernelPackage/rtl8168/description
  This package contains the Realtek R8168 PCI-E Gigibit Ethernet driver
endef

$(eval $(call KernelPackage,rtl8168))

define KernelPackage/rtl8168_pg
  SUBMENU:=$(RTK_MENU)
  TITLE:=Realtek R8168 PCI-E Gigabit Ethernet PG driver
  DEPENDS:=@TARGET_realtek @PCI_SUPPORT +kmod-mii
  KCONFIG:=CONFIG_R8168_PG
  FILES:=$(LINUX_DIR)/drivers/net/ethernet/realtek/r8168_pg/pgdrv.ko
  AUTOLOAD:=$(call AutoProbe,r8168_pg)
endef

define KernelPackage/rtl8168_pg/description
  This package contains the Realtek R8168 PCI-E Gigibit Ethernet PG driver
endef

$(eval $(call KernelPackage,rtl8168_pg))

define KernelPackage/rtd1295hwnat
  SUBMENU:=$(RTK_MENU)
  TITLE:=Realtek 1295 HWNAT driver
  KCONFIG:= \
	CONFIG_BRIDGE=y \
	CONFIG_NET_SCHED=y \
	CONFIG_RTD_1295_HWNAT=y \
	CONFIG_BRIDGE_IGMP_SNOOPING=y \
	CONFIG_RTL_HARDWARE_NAT=n \
	CONFIG_RTL_819X=y \
	CONFIG_RTL_HW_NAPT=n \
	CONFIG_RTL_LAYERED_ASIC_DRIVER=y \
	CONFIG_RTL_LAYERED_ASIC_DRIVER_L3=n \
	CONFIG_RTL_LAYERED_ASIC_DRIVER_L4=n \
	CONFIG_RTL_LAYERED_DRIVER_ACL=y \
	CONFIG_RTL_LAYERED_DRIVER_L2=y \
	CONFIG_RTL_LAYERED_DRIVER_L3=n \
	CONFIG_RTL_LAYERED_DRIVER_L4=n \
	CONFIG_RTL_LINKCHG_PROCESS=y \
	CONFIG_RTL_NETIF_MAPPING=y \
	CONFIG_RTL_PROC_DEBUG=y \
	CONFIG_RTL_LOG_DEBUG=n \
	CONFIG_RTL865X_ROMEPERF=n \
	CONFIG_RTK_VLAN_SUPPORT=n \
	CONFIG_RTL_EEE_DISABLED=n \
	CONFIG_RTL_SOCK_DEBUG=n \
	CONFIG_RTL_EXCHANGE_PORTMASK=n \
	CONFIG_RTL_INBAND_CTL_ACL=n \
	CONFIG_RTL_ETH_802DOT1X_SUPPORT=n \
	CONFIG_RTL_MULTI_LAN_DEV=y \
	CONFIG_AUTO_DHCP_CHECK=n \
	CONFIG_RTL_HW_MULTICAST_ONLY=n \
	CONFIG_RTL_HW_L2_ONLY=y \
	CONFIG_RTL_MULTIPLE_WAN=n \
	CONFIG_RTL865X_LANPORT_RESTRICTION=n \
	CONFIG_RTL_LOCAL_PUBLIC=n \
	CONFIG_RTL_HW_DSLITE_SUPPORT=n \
	CONFIG_RTL_HW_6RD_SUPPORT=n \
	CONFIG_RTL_IPTABLES_RULE_2_ACL=n \
	CONFIG_RTL_FAST_FILTER=n \
	CONFIG_RTL_ETH_PRIV_SKB=n \
	CONFIG_RTL_EXT_PORT_SUPPORT=n \
	CONFIG_RTL_HARDWARE_IPV6_SUPPORT=n \
	CONFIG_RTL_ROMEPERF_24K=n \
	CONFIG_RTL_VLAN_PASSTHROUGH_SUPPORT=n \
	CONFIG_RTL_8211F_SUPPORT=n \
	CONFIG_RTL_8367R_SUPPORT=n
  FILES:=
  AUTOLOAD:=
  DEPENDS:=@TARGET_realtek_rtd129x
endef

define KernelPackage/rtd1295hwnat/description
  This package contains the Realtek HW NAT Driver
endef

define KernelPackage/rtd1295hwnat/config
  if PACKAGE_kmod-rtd1295hwnat

	config KERNEL_NF_CONNTRACK
		bool
		default y

	config KERNEL_IP_NF_IPTABLES
		bool
		default n

	config KERNEL_VLAN_8021Q
		bool
		default n

	config KERNEL_RTL_IVL_SUPPORT
		bool
		default n

	config KERNEL_PPP
		bool
		default n

	config KERNEL_RTL_FAST_PPPOE
		bool
		default n

	config KERNEL_RTL_8021Q_VLAN_SUPPORT_SRC_TAG
		bool
		default n

	config KERNEL_RTL_HW_QOS_SUPPORT
		bool "Enable HW QoS support"
		select KERNEL_IP_NF_IPTABLES
		default n
		help
		  Enable HW QoS for HW NAT.

	config KERNEL_RTL_VLAN_8021Q
		bool "Enable HW VLAN support"
		select KERNEL_VLAN_8021Q
		select KERNEL_RTL_IVL_SUPPORT
		default n
		help
		  Enable HW VLAN for HW NAT.

	config KERNEL_RTL_TSO
		bool "Enable HW TSO support"
		depends on !KERNEL_RTL_IPTABLES_FAST_PATH
		select KERNEL_RTL_GSO
		default y
		help
		  Enable HW TSO for HW NAT.

	config KERNEL_RTL_GSO
		bool "Enable software GSO support"
		depends on !KERNEL_RTL_IPTABLES_FAST_PATH
		default y
		help
		  Enable software GSO support.

	config KERNEL_RTL_IPTABLES_FAST_PATH
		bool "Enable fastpath support"
		select KERNEL_NF_CONNTRACK
		select KERNEL_IP_NF_IPTABLES
		select KERNEL_PPP
		select KERNEL_RTL_FAST_PPPOE
		default n
		help
		  Enable fastpath when packets go through CPU.

	config KERNEL_RTL_WAN_MAC5
		bool "Use MAC5 as WAN port"
		default n
		help
		  Use MAC5 as WAN port.

	config KERNEL_RTL_836X_SUPPORT
		bool "Enable RTL836X series switches support"
		default n
		help
		  Support Realtek RTL8363, RTL8367, RTL8370 series switches.

	config KERNEL_RTL_JUMBO_FRAME
		bool "Enable JUMBO frame support"
		default y
		help
		  Support Realtek RTL8363, RTL8367, RTL8370 series switches.

	config KERNEL_RTL_BR_SHORTCUT
		bool "Enable bridge shortcut (WiFi)"
		default n
		help
		  Enable Bridge Shortcut between WiFi and HW NAT
  endif
endef

$(eval $(call KernelPackage,rtd1295hwnat))

define KernelPackage/openmax
  SECTION:=kernel
  CATEGORY:=Kernel modules
  SUBMENU:=$(RTK_MENU)
  TITLE:=OpenMAX kernel options
  KCONFIG:= \
	CONFIG_ION=y \
	CONFIG_ION_TEST=n \
	CONFIG_ION_DUMMY=n \
	CONFIG_ION_RTK_PHOENIX=y \
	CONFIG_FIQ_DEBUGGER=n \
	CONFIG_FSL_MC_BUS=n \
	CONFIG_RTK_CODEC=y \
	CONFIG_RTK_RESERVE_MEMORY=y \
	CONFIG_VE1_CODEC=y \
	CONFIG_VE3_CODEC=y \
	CONFIG_IMAGE_CODEC=y \
	CONFIG_ANDROID=y \
	CONFIG_ASHMEM=y \
	CONFIG_ANDROID_TIMED_OUTPUT=n \
	CONFIG_ANDROID_TIMED_GPIO=n \
	CONFIG_ANDROID_LOW_MEMORY_KILLER=n \
	CONFIG_SYNC=y \
	CONFIG_SW_SYNC=y \
	CONFIG_SW_SYNC_USER=y \
	CONFIG_ZSMALLOC=y \
	CONFIG_PGTABLE_MAPPING=n \
	CONFIG_ZSMALLOC_STAT=n \
	CONFIG_REGMAP=y \
	CONFIG_REGMAP_I2C=y \
	CONFIG_JUMP_LABEL=y \
	CONFIG_KSM=y \
	CONFIG_UIO=y \
	CONFIG_UIO_ASSIGN_MINOR=y \
	CONFIG_UIO_RTK_RBUS=y \
	CONFIG_UIO_RTK_REFCLK=y \
	CONFIG_UIO_RTK_SE=y \
	CONFIG_UIO_RTK_MD=y \
	CONFIG_UIO_CIF=n \
	CONFIG_UIO_PDRV_GENIRQ=n \
	CONFIG_UIO_DMEM_GENIRQ=n \
	CONFIG_UIO_AEC=n \
	CONFIG_UIO_SERCOS3=n \
	CONFIG_UIO_PCI_GENERIC=n \
	CONFIG_UIO_NETX=n \
	CONFIG_UIO_PRUSS=n \
	CONFIG_UIO_MF624=n \
	CONFIG_STAGING=y \
	CONFIG_FSL_MC_BUS=n \
	CONFIG_CMA=y \
	CONFIG_CMA_DEBUG=n \
	CONFIG_CMA_DEBUGFS=y \
	CONFIG_CMA_AREAS=7 \
	CONFIG_DMA_CMA=y \
	CONFIG_CMA_SIZE_MBYTES=32 \
	CONFIG_CMA_SIZE_SEL_MBYTES=y \
	CONFIG_CMA_SIZE_SEL_PERCENTAGE=n \
	CONFIG_CMA_SIZE_SEL_MIN=n \
	CONFIG_CMA_SIZE_SEL_MAX=n \
	CONFIG_CMA_ALIGNMENT=4 \
	CONFIG_ADF=n \

  DEPENDS:=
  FILES:=
endef

define KernelPackage/openmax/description
  This package enables kernel options for OpenMAX.
endef

$(eval $(call KernelPackage,openmax))
