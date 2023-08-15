include $(TOPDIR)/rules.mk

PKG_NAME:=istoreos-files
PKG_VERSION:=1.0
PKG_RELEASE:=$(COMMITCOUNT)
PKG_FLAGS:=hold essential nonshared

PKG_LICENSE:=CC0-1.0
PKG_MAINTAINER:=jjm2473 <jjm2473@gmail.com>

include $(INCLUDE_DIR)/package.mk

define Package/$(PKG_NAME)
  SECTION:=base
  CATEGORY:=Base system
  TITLE:=iStoreOS files
  MAINTAINER:=jjm2473 <jjm2473@gmail.com>
  DEFAULT:=y
  HIDDEN:=y
  DEPENDS:=+luci-theme-argon
endef

define Package/$(PKG_NAME)/description
 The iStoreOS.
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
endef

define Build/Compile/Default

endef
Build/Compile = $(Build/Compile/Default)

define Package/$(PKG_NAME)/install
	$(CP) ./files/* $(1)/
endef


define Package/$(PKG_NAME)/postinst
#!/bin/sh

HOST_SED="$(subst ${STAGING_DIR_HOST},$${STAGING_DIR_HOST},$(SED))"
HOST_LN="$(subst ${STAGING_DIR_HOST},$${STAGING_DIR_HOST},$(LN))"

[ -n "$${IPKG_INSTROOT}" ] && {
	$${HOST_SED} 's,^src/gz istoreos_,src/gz openwrt_,g' -e '/^src\/gz openwrt_\(core\|base\|luci\|packages\|routing\|telephony\) /!d' "$${IPKG_INSTROOT}/etc/opkg/distfeeds.conf"

	$${HOST_SED} 's/"192.168.1.1"/"192.168.100.1"/' \
		"$${IPKG_INSTROOT}/usr/lib/lua/luci/controller/admin/system.lua" \
		"$${IPKG_INSTROOT}/usr/lib/lua/luci/controller/admin/ota.lua" \
		"$${IPKG_INSTROOT}/bin/config_generate"

	$${HOST_SED} "s/'192\\.168\\.1\\.1'/'192.168.100.1'/; s/'openwrt\\.lan'/window.location.host/" "$${IPKG_INSTROOT}/www/luci-static/resources/view/system/flash.js"

	$${HOST_SED} 's/s\.anonymous = true/s\.anonymous = true\ns\.addremove = true/' "$${IPKG_INSTROOT}/usr/lib/lua/luci/model/cbi/hd_idle.lua"

	$${HOST_SED} 's#"/opt"#"/overlay/upper/opt/docker"#' "$${IPKG_INSTROOT}/usr/lib/lua/luci/model/cbi/admin_system/fstab/mount.lua"

	rm -f "$${IPKG_INSTROOT}/sbin/jffs2reset"
	$${HOST_LN} /sbin/firstboot "$${IPKG_INSTROOT}/sbin/jffs2reset"

	$${HOST_SED} '/<link rel="shortcut icon" href="<%=media%>\/favicon.ico">/a         <link rel="stylesheet" href="<%=resource%>/easepi/easeicon.css?t=1649313193968">' \
		"$${IPKG_INSTROOT}/usr/lib/lua/luci/view/themes/argon/header.htm" \
		"$${IPKG_INSTROOT}/usr/lib/lua/luci/view/themes/argon_dark/header.htm" \
		"$${IPKG_INSTROOT}/usr/lib/lua/luci/view/themes/argon_light/header.htm" \
		"$${IPKG_INSTROOT}/usr/lib/lua/luci/view/themes/argon_dark_purple/header.htm" \
		"$${IPKG_INSTROOT}/usr/lib/lua/luci/view/themes/argon_light_green/header.htm"

	rm -f "$${IPKG_INSTROOT}/etc/uci-defaults/luci-argon-config"

}
true

endef

$(eval $(call BuildPackage,istoreos-files))
