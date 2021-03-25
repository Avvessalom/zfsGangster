#!/bin/bash
dd if=/dev/zero of=$(PWD)/fs.img bs=1000000 count=101
zpool create test_zfs $(PWD)/fs.img
zfs set recordsize=512 test_zfs
echo "---------------------------"
zfs list