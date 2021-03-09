#!/bin/bash
dd if=/dev/zero of=fs.img bs=1M count=101
zpool create myzfs -o ashift=9 /home/kain/github/ITMO-System-level-Software/scripts/fs.img
zfs set recordsize=512 myzfs
echo "---------------------------------------------------------------------------------"
zfs list