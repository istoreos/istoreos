#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=ntfsprogs
PKG_RELEASE:=1

PKG_VERSION:=2021.8.22
PKG_SOURCE:=ntfs-3g_ntfsprogs-$(PKG_VERSION).tgz
PKG_SOURCE_URL:=https://www.tuxera.com/opensource/
PKG_HASH:=55b883aa05d94b2ec746ef3966cb41e66bed6db99f22ddd41d1b8b94bb202efb

PKG_LICENSE:=GPL-2.0 LGPL-2.0
PKG_LICENSE_FILES:=COPYING COPYING.LIB

PKG_FIXUP:=autoreconf
PKG_INSTALL:=1

PKG_BUILD_DIR := $(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk

define Package/$(PKG_NAME)/description
  Suite of NTFS utilities for doing neat things with NTFS.
  Contains:
   - mkntfs - Create an NTFS filesystem.
   - ntfscat - Dump a file's content to the standard output.
   - ntfsclone - Efficiently clone, backup, restore or rescue NTFS.
   - ntfscluster - Locate the files which use the given sectors or clusters.
   - ntfscmp - Compare two NTFS filesystems and tell the differences.
   - ntfscp - Copy a file to an NTFS volume.
   - ntfssecaudit - Display ownership and permissions, check consistency
   - ntfsfix - Check and fix some common errors, clear the LogFile.
   - ntfsinfo - Show information about NTFS or one of the files or directories within it.
   - ntfslabel - Show, or set, an NTFS filesystem's volume label.
   - ntfsls - List information about files in a directory residing on an NTFS.
   - ntfsresize - Resize NTFS without losing data.
   - ntfsundelete - Recover deleted files from NTFS.
   - ntfsusermap - Define mapping of Windows accounts to Linux logins
endef

define Package/$(PKG_NAME)
  SECTION:=utils
  CATEGORY:=Utilities
  URL:=http://www.tuxera.com
  SUBMENU:=Filesystem
  TITLE:=ntfsprogs from ntfs-3g
  DEPENDS+= +libgcrypt +libuuid
  CONFLICTS:=ntfs-3g ntfs-3g-utils
endef

CONFIGURE_ARGS += \
	--enable-ntfsprogs \
	--disable-ntfs-3g \
	--enable-shared \
	--enable-static \
	--with-uuid

CONFIGURE_ARGS += --with-fuse=internal
TARGET_CPPFLAGS:=-I../include/fuse-lite $(TARGET_CPPFLAGS)

# redefine prepare to extract to our build dir
# apply patches
define Build/Prepare
	rm -rf $(PKG_BUILD_DIR)/
	mkdir -p $(PKG_BUILD_DIR)/
	$(TAR) -xzf $(DL_DIR)/$(PKG_SOURCE) -C $(PKG_BUILD_DIR) --strip 1
	$(Build/Patch)
endef

define Package/$(PKG_NAME)/install
	[ -f $(PKG_INSTALL_DIR)/usr/sbin/mkntfs ] && [ -f $(PKG_INSTALL_DIR)/usr/bin/ntfsfix ]
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libntfs-3g.so.* $(1)/usr/lib/
	$(INSTALL_DIR) $(1)/sbin
	$(LN) /usr/sbin/mkntfs $(1)/sbin/mkfs.ntfs
	$(INSTALL_DIR) $(1)/usr/bin
	$(FIND) $(PKG_INSTALL_DIR)/usr/bin/ -type f ! -regex '.*[^/]*ntfs-3g[^/]*' -exec $(INSTALL_BIN) {} $(1)/usr/bin/ \;
	$(INSTALL_DIR) $(1)/usr/sbin
	$(FIND) $(PKG_INSTALL_DIR)/usr/sbin/ -type f ! -regex '.*[^/]mkfs\.ntfs[^/]*' -exec $(INSTALL_BIN) {} $(1)/usr/sbin/ \;
	$(LN) /usr/sbin/mkntfs $(1)/usr/sbin/mkfs.ntfs
	$(LN) /usr/bin/ntfsfix $(1)/usr/sbin/fsck.ntfs
endef

$(eval $(call BuildPackage,$(PKG_NAME)))