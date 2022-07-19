# 
# Copyright (C) 2006-2012 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=rtd129x_img_gen
PKG_VERSION:=1.0
PKG_REVISION:=4

HOST_BUILD_DIR:=$(BUILD_DIR_HOST)/${PKG_NAME}-$(PKG_VERSION)

include $(INCLUDE_DIR)/host-build.mk
include $(INCLUDE_DIR)/cmake.mk

define Host/Prepare
	mkdir -p $(HOST_BUILD_DIR)
	$(CP) ./src/* $(HOST_BUILD_DIR)/
	find $(HOST_BUILD_DIR) -name .svn | $(XARGS) rm -rf
endef

define Host/Install
	$(INSTALL_DIR) $(STAGING_DIR_HOST)/bin
	$(INSTALL_BIN) $(HOST_BUILD_DIR)/rtd129x_img_gen $(STAGING_DIR_HOST)/bin/
	$(INSTALL_BIN) $(HOST_BUILD_DIR)/rtd129x_encode_hwsetting $(STAGING_DIR_HOST)/bin/
	$(INSTALL_BIN) $(HOST_BUILD_DIR)/rtd129x_bootcode_gen $(STAGING_DIR_HOST)/bin/
endef

define Host/Clean
	rm -f $(STAGING_DIR_HOST)/bin/rtd129x_img_gen \
		$(STAGING_DIR_HOST)/bin/rtd129x_encode_hwsetting \
		$(STAGING_DIR_HOST)/bin/rtd129x_bootcode_gen
endef

$(eval $(call HostBuild))
