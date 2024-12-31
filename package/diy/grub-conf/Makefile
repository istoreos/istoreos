include $(TOPDIR)/rules.mk

PKG_NAME:=grub-conf
PKG_VERSION:=1.0.0
PKG_RELEASE:=2
PKG_FLAGS:=hold nonshared

PKG_MAINTAINER:=jjm2473 <jjm2473@gmail.com>

include $(INCLUDE_DIR)/package.mk

define Package/grub-conf
  CATEGORY:=Boot Loaders
  SECTION:=boot
  TITLE:=iStoreOS GRUB configure
  DEPENDS:=@TARGET_x86 +grub2-editenv
endef

define Package/grub-conf/description
  iStoreOS GRUB configure
endef

define Package/grub-conf/conffiles
/etc/config/grub
endef

define Package/iommu-conf
  CATEGORY:=Boot Loaders
  SECTION:=boot
  TITLE:=iStoreOS GRUB IOMMU configure
  DEPENDS:=@TARGET_x86_64 +grub-conf
endef

define Package/iommu-conf/description
  iStoreOS IOMMU configure for PCI passthrough
endef

define Build/Configure
endef

define Build/Compile
endef

define Package/grub-conf/install
	$(INSTALL_DIR) $(1)/etc/config $(1)/etc/init.d $(1)/etc/uci-defaults $(1)/etc/grub.cfg.d
	$(INSTALL_BIN) ./files/grub.init $(1)/etc/init.d/grub
	$(INSTALL_DATA) ./files/grub.config $(1)/etc/config/grub
	$(INSTALL_DATA) ./files/grub.default $(1)/etc/uci-defaults/grub
	$(INSTALL_DATA) ./files/cmdline.grubcfg $(1)/etc/grub.cfg.d/02-cmdline.cfg
endef

define Package/iommu-conf/install
	$(INSTALL_DIR) $(1)/etc/grub.cfg.d
	$(INSTALL_DATA) ./files/iommu.grubcfg $(1)/etc/grub.cfg.d/01-iommu.cfg
endef

$(eval $(call BuildPackage,grub-conf))
$(eval $(call BuildPackage,iommu-conf))
