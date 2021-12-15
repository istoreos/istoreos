
define Package/base-files/install-target
	chmod 0400 $(1)/etc/public.key
endef

define Package/base-files/postinst
#!/bin/sh

[ -n "$${IPKG_INSTROOT}" ] && {
	FILE="$${IPKG_INSTROOT}/etc/opkg/distfeeds.conf"
	$(SED) '/\/targets\/realtek\/rtd129x\//d' $${FILE}
}

endef
