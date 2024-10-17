Package/qed-firmware = $(call Package/firmware-default,QLogic QED firmware)
define Package/qed-firmware/install
	$(INSTALL_DIR) $(1)/lib/firmware/qed
	$(INSTALL_DATA) \
		$(PKG_BUILD_DIR)/qed/qed_init_values_zipped-8.59.1.0.bin \
		$(1)/lib/firmware/qed/
endef
$(eval $(call BuildPackage,qed-firmware))
