include $(TOPDIR)/rules.mk

PKG_NAME:=fodder
PKG_RELEASE:=1
PKG_VERSION:=0.1

# later will be included in feeds
#PKG_SOURCE_PROTO:=git
#PKG_SOURCE_URL:=https://github.com/PolynomialDivision/FODDER.git
#PKG_SOURCE_VERSION:=da1c22eb93143ebecdbb74d38c0920de0dea5c93

PKG_MAINTAINER:=Nick Hainke <vincent@systemli.org>
CMAKE_INSTALL:=1

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/fodder
  SECTION:=net
  CATEGORY:=Network
  TITLE:= Fine Dust Daemon.
  MAINTAINER:= Nick Hainke <vincent@systemli.org>
  URL:=https://github.com/PolynomialDivision/FODDER
  DEPENDS:=$(DRV_DEPENDS) +libubus +libubox
endef

define Package/fodder/description
 This package implements a daemon for transmiting fine dust senor values.
endef

define Package/fodder/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/fodder $(1)/usr/sbin/fodder

	$(INSTALL_DIR) $(1)/etc/init.d/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/files/fodder.init $(1)/etc/init.d/fodder
	$(INSTALL_DIR) $(1)/etc/config
	$(INSTALL_CONF) $(PKG_BUILD_DIR)/files/fodder.config $(1)/etc/config/fodder
endef


$(eval $(call BuildPackage,fodder))
