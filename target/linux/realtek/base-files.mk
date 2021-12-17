
define Package/base-files/install-target
	chmod 0400 $(1)/etc/public.key
endef

define Package/base-files/postinst
#!/bin/sh

HOST_SED="$(subst ${STAGING_DIR_HOST},$${STAGING_DIR_HOST},$(SED))"

[ -n "$${IPKG_INSTROOT}" ] && {
	$${HOST_SED} '/\/targets\/realtek\/rtd129x\//d' "$${IPKG_INSTROOT}/etc/opkg/distfeeds.conf"
	$${HOST_SED} 's/"192.168.1.1"/"192.168.100.1"/' \
		"$${IPKG_INSTROOT}/usr/lib/lua/luci/controller/admin/system.lua" \
		"$${IPKG_INSTROOT}/etc/board.d/99-default_network"
}
endef
