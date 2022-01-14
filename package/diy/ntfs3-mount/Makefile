include $(TOPDIR)/rules.mk

PKG_NAME:=ntfs3-mount
PKG_RELEASE:=5

include $(INCLUDE_DIR)/package.mk

define Package/ntfs3-mount
  SECTION:=utils
  CATEGORY:=Utilities
  SUBMENU:=Filesystem
  TITLE:=NTFS mount script for Paragon NTFS3 driver
  DEPENDS:=+!LINUX_5_15:kmod-fs-ntfs3-oot +LINUX_5_15:kmod-fs-ntfs3
  PKGARCH:=all
endef

define Build/Configure
endef

define Build/Compile
endef

define Package/ntfs3-mount/install
	$(INSTALL_DIR) $(1)/sbin $(1)/sbin/fs
	$(INSTALL_BIN) ./files/mount.ntfs $(1)/sbin
	$(LN) /sbin/mount.ntfs $(1)/sbin/fs/mount.ntfs
endef

define Package/ntfs3-mount/postinst
#!/bin/sh
FILE="$${IPKG_INSTROOT}/etc/filesystems"
ID="ntfs"

if ! [ -f $$FILE ]; then
	echo "Create '$$FILE'."
	touch "$$FILE"
fi

if ! grep -q -e '^'"$$ID"'$$' "$$FILE"; then
	echo "Add '$$ID' to known filesystems."
	echo "$$ID" >> "$$FILE"
fi
endef

$(eval $(call BuildPackage,ntfs3-mount))
