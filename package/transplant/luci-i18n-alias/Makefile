include $(TOPDIR)/rules.mk

PKG_NAME:=luci-i18n-alias
PKG_VERSION:=1.0
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk

define Package/$(PKG_NAME)
  SECTION:=luci
  CATEGORY:=LuCI
  SUBMENU:=2. Modules
  TITLE:=LuCI translations alias reverse map
  PKGARCH:=all
  DEPENDS:=+luci-base
endef

define Package/$(PKG_NAME)/description
	Language Support Packages.
endef

define Package/$(PKG_NAME)/config
	if PACKAGE_$(PKG_NAME)
		config LUCI_LANG_zh-cn
			tristate
			default LUCI_LANG_zh_Hans
		config LUCI_LANG_zh-tw
			tristate
			default LUCI_LANG_zh_Hant
		config LUCI_LANG_pt-br
			tristate
			default LUCI_LANG_pt_BR
		config LUCI_LANG_no
			tristate
			default LUCI_LANG_nb_NO
		config LUCI_LANG_bn
			tristate
			default LUCI_LANG_bn_BD
	endif
endef

define Build/Prepare
endef

define Build/Configure
endef

define Build/Compile
endef

define Package/$(PKG_NAME)/install
endef

$(eval $(call BuildPackage,luci-i18n-alias))
