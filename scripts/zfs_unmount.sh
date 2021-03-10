#!/bin/bash
rm -rf *.img
zpool destroy myzfs
zfs list