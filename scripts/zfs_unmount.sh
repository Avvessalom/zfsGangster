#!/bin/bash
rm -rf *.img
zfs destroy myzfs/test1
zpool destroy myzfs
zfs list