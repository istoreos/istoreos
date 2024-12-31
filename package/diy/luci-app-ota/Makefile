
include $(TOPDIR)/rules.mk

LUCI_TITLE:=LuCI for OTA upgrade
LUCI_DEPENDS:=+curl
LUCI_PKGARCH:=all
PKG_VERSION:=1.5.3
PKG_RELEASE:=1
PKG_MAINTAINER:=jjm2473 <jjm2473@gmail.com>

define Package/luci-app-ota/conffiles
/etc/config/ota
endef

include $(TOPDIR)/feeds/luci/luci.mk

# call BuildPackage - OpenWrt buildroot signature
