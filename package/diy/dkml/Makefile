include $(TOPDIR)/rules.mk

PKG_NAME:=dkml
PKG_VERSION:=1.0.1
PKG_RELEASE:=2
PKG_FLAGS:=hold essential nonshared

PKG_MAINTAINER:=jjm2473 <jjm2473@gmail.com>

include $(INCLUDE_DIR)/package.mk

define Package/dkml
  SECTION:=utils
  CATEGORY:=Base system
  TITLE:=iStoreOS DKML
endef

define Package/dkml/description
  iStoreOS dynamic kernel modules loader
endef

define Package/dkml/conffiles
/etc/config/kmods
endef

define Build/Configure
endef

define Build/Compile
endef

define Package/dkml/install
	$(INSTALL_DIR) $(1)/etc/config $(1)/etc/init.d
	$(INSTALL_BIN) ./files/kmods.init $(1)/etc/init.d/kmods
	$(INSTALL_DATA) ./files/kmods.config $(1)/etc/config/kmods
endef

$(eval $(call BuildPackage,dkml))
