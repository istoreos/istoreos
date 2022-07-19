# 先在Openwrt里面设置好想要的密码，复制/etc/shadow对应的密码段进行加密，例如

echo '$1$T0dZmPAr$sIy6uURznIVedI/1C/a6M0' | openssl rsautl -sign -inkey private.key | hexdump  -e '1/1 "%02x "'

# 得到的数据放到dts文件的 /chosen/default-password 节点
