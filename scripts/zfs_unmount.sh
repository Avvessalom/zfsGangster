#!/bin/bash
rm -f $(PWD)/fs.img
zpool destroy test_zfs
zfs list