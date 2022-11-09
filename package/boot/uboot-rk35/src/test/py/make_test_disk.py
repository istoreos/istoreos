# Copyright (c) 2017 Alison Chaiken
#
# SPDX-License-Identifier: GPL-2.0
#
# Create a block device for testing of 'gpt' and 'part' commands.

import os

def makeDisk():
    if (os.path.exists("testdisk.raw")):
        os.remove("testdisk.raw")
    fd = os.open("testdisk.raw", os.O_RDWR|os.O_CREAT )
    os.ftruncate(fd, 4194304)
    os.close(fd)
    os.spawnl(os.P_WAIT, "/sbin/sgdisk", "sgdisk", "-U",
          "375a56f7-d6c9-4e81-b5f0-09d41ca89efe", "testdisk.raw")
    os.spawnl(os.P_WAIT, "/sbin/sgdisk", "sgdisk", "--new=1:2048:2560", "testdisk.raw")
    os.spawnl(os.P_WAIT, "/sbin/sgdisk", "sgdisk", "--new=2:4096:4608", "testdisk.raw")
    os.spawnl(os.P_WAIT, "/sbin/gdisk", "sgdisk", "-l", "testdisk.raw")
