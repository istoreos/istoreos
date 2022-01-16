
define Package/base-files/install-target
	chmod 0400 $(1)/etc/public.key
	$(LN) /tmp/run $(1)/run
endef

define Package/base-files/postinst
#!/bin/sh

HOST_SED="$(subst ${STAGING_DIR_HOST},$${STAGING_DIR_HOST},$(SED))"
HOST_LN="$(subst ${STAGING_DIR_HOST},$${STAGING_DIR_HOST},$(LN))"

[ -n "$${IPKG_INSTROOT}" ] && {
	$${HOST_SED} '/\/targets\/realtek\/rtd129x\//d' "$${IPKG_INSTROOT}/etc/opkg/distfeeds.conf"
	$${HOST_SED} 's/"192.168.1.1"/"192.168.100.1"/' \
		"$${IPKG_INSTROOT}/usr/lib/lua/luci/controller/admin/system.lua" \
		"$${IPKG_INSTROOT}/etc/board.d/99-default_network"

	$${HOST_SED} "s/'192\\.168\\.1\\.1'/'192.168.100.1'/; s/'openwrt\\.lan'/window.location.host/" "$${IPKG_INSTROOT}/www/luci-static/resources/view/system/flash.js"

	$${HOST_SED} 's/s\.anonymous = true/s\.anonymous = true\ns\.addremove = true/' $${IPKG_INSTROOT}/usr/lib/lua/luci/model/cbi/hd_idle.lua

	$${HOST_SED} 's#"/opt"#"/overlay/upper/opt/docker"#' $${IPKG_INSTROOT}/usr/lib/lua/luci/model/cbi/admin_system/fstab/mount.lua

	$${HOST_LN} /usr/sbin/jffs2reset "$${IPKG_INSTROOT}/sbin/jffs2reset"

	true
}
endef
