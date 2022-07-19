# What's that
RTD129X factory and env tools

## Build
```
mkdir build
cd build
cmake ..
make
```

## Usage
```shell
rtd129x_env set <KEY> <VALUE>       Set Environment
rtd129x_env list    Print Environment
rtk_factory_sign <factory.tar>     Sign RTK header
```

## Example
```shell
cd /

# extract factory
sh -c 'dd if=$0 of=/tmp/factory.tar bs=512 count=4096 skip=4352' /dev/mmcblk0
tar -xf /tmp/factory.tar

# set env
rtd129x_env list
rtd129x_env set ethaddr 00:E1:10:A0:E4:40

# pack factory
tar -cf /tmp/factory.tar tmp/factory
rtk_factory_sign /tmp/factory.tar

# write back
sh -c 'dd if=/tmp/factory.tar of=$0 bs=512 seek=4352 conv=notrunc' /dev/mmcblk0
sh -c 'dd if=/tmp/factory.tar of=$0 bs=512 seek=8448 conv=notrunc' /dev/mmcblk0
```
