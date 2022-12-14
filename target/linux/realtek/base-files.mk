
define Package/base-files/install-target
	chmod 0400 $(1)/etc/public.key
endef

define Package/base-files/postinst
#!/bin/sh

HOST_SED="$(subst ${STAGING_DIR_HOST},$${STAGING_DIR_HOST},$(SED))"
HOST_LN="$(subst ${STAGING_DIR_HOST},$${STAGING_DIR_HOST},$(LN))"

[ -n "$${IPKG_INSTROOT}" ] && {
	$${HOST_SED} '/targets\/realtek\/rtd129x/d' "$${IPKG_INSTROOT}/etc/opkg/distfeeds.conf"
}
true

endef
