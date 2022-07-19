# What's that
RTD129X install.img content generator
* fw_tbl.bin
* mbr.bin
* config.txt
* layout.txt

## Build
```
mkdir build
cd build
cmake ..
make
```

## Usage
```shell
rtd129x_img_gen <LAYOUT.json> [<WORKING_DIR>]
```

## Example
/src/rtd129x_layout.json:
```json
{
  "size": "8000000000",
  "fw_table_offset": "0x620000",
  "fw_start": "0x630000",
  "fw_align": "0x200",
  "part_start": "0x40000000",
  "part_align": "0x400",
  "fw": [
    {"type":"RESCUE_DT", "target":"0x2140000", "file":"omv/rescue.emmc.dtb"},
    {"type":"RESCUE_ROOTFS", "target":"0x30000000", "file":"omv/rescue.root.emmc.cpio.gz_pad.img"},
    {"type":"AKERNEL", "target":"0x1b00000", "file":"omv/bluecore.audio"},
    {"type":"KERNEL_DT", "target":"0x2100000", "file":"omv/android.emmc.dtb"},
    {"type":"KERNEL", "target":"0x3000000", "file":"omv/emmc.uImage"}
  ],
  "part": [
    {"name":"rootfs", "mp":"/", "size":"0x8000000", "filetype":"img", "filesystem":"squashfs", "file":"omv/squashfs1.img"},
    {"name":"etc", "mp":"etc", "size":"-1", "filetype":"bin", "filesystem":"ext4", "file":"omv/etc.bin"}
  ]
}
```

Files in /img_build/install:
```
./ALSADaemon
./customer.tar
./install_a
./mke2fs
./omv
./omv/android.emmc.dtb
./omv/bluecore.audio
./omv/bootloader.tar
./omv/emmc.uImage
./omv/etc.bin
./omv/gold.bluecore.audio
./omv/gold.emmc.uImage
./omv/gold.rescue.emmc.dtb
./omv/gold.rescue.root.emmc.cpio.gz_pad.img
./omv/rescue.emmc.dtb
./omv/rescue.root.emmc.cpio.gz_pad.img
./omv/squashfs1.img
./teeUtility.tar
```

Run:
```shell
rtd129x_img_gen /src/rtd129x_layout.json /img_build/install
```

Will generate in /img_build/install:
```
./config.txt
./fw_tbl.bin
./layout.txt
./mbr.bin
```

Then pack /img_build/install with tar:
```shell
tar -cvf /img_build/install.img -C /img_build/install .
```
