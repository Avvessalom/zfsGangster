#!/bin/bash
device=$(losetup -f)
dd if=/dev/zero of=fs.img bs=1k count=66000
dd if=/dev/zero of=fs1.img bs=1k count=66000
zpool create myzfs fs.img fs1.img
zfs create myzfs/test1
#losetup "$device" fs.img
#mkfs -c -T zfs device
#mkdir /mnt/zfs
#mount -t zfs "$device" /mnt/zfs