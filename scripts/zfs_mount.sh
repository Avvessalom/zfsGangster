#!/bin/bash
dd if=/dev/zero of=fs.img bs=1k count=66000
dd if=/dev/zero of=fs1.img bs=1k count=66000
zpool create myzfs /home/kain/github/ITMO-System-level-Software/scripts/fs.img /home/kain/github/ITMO-System-level-Software/scripts/fs1.img
zfs create myzfs/test1
echo "---------------------------------------------------------------------------------"
zfs list