#!/bin/bash

# 添加禁用USB自动挂起的脚本
mkdir -p files/etc/uci-defaults
cat > files/etc/uci-defaults/99-disable-usb-autosuspend << 'EOF'
#!/bin/sh
# 禁用USB自动挂起以解决华为5G通信壳断线问题
echo 'SUBSYSTEM=="usb", ATTR{power/autosuspend}="-1"' >> /etc/udev/rules.d/99-usb-power.rules
echo 'SUBSYSTEM=="usb", ATTR{power/control}="on"' >> /etc/udev/rules.d/99-usb-power.rules
exit 0
EOF
chmod +x files/etc/uci-defaults/99-disable-usb-autosuspend

echo "已添加USB电源管理修复脚本"

# 更新feeds
./scripts/feeds update -a
./scripts/feeds install -a
