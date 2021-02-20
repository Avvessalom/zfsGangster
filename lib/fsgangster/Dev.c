//
// Created by kain on 20.02.2021.
//
#include "Fsgangster.h"
#include <stdio.h>
#include <math.h>
#include <stdbool.h>


bool isRoot = true;

int DeviceList(fsgangsterInfo *info) {
    int status = blkid_probe_all(info->blkCache);

    if (status < 0) {
        fprintf(stderr, "Can't probe devices\n");
        return 1;
    }
    return 0;
}

int IteratorDevice(fsgangsterInfo *info) {
    blkid_dev device;
    blkid_dev_iterate iterator = blkid_dev_iterate_begin(info->blkCache);
    const double gibibyte = pow(2, 30);
    const double mibibyte = pow(2, 20);

    printf("Partitions\n");

    while (blkid_dev_next(iterator, &device) == 0) {
        const char *devName = blkid_dev_devname(device);
        printf("\t%s\n", devName);

        if (isRoot) {
            blkid_probe probe = blkid_new_probe_from_filename(devName);
            if (probe == NULL) {
                fprintf(stderr, "Launch utill as root to get more info\n");
                isRoot = false;
            } else {
                blkid_loff_t probeSize = blkid_probe_get_size(probe);
                printf("\t\tSize: ");
                if (probeSize >= gibibyte) {
                    printf("%lld Gib\n", (long long) (probeSize / gibibyte));
                } else if (probeSize <= gibibyte) {
                    printf("%lld Mib\n", (long long) (probeSize / mibibyte));
                }
            }
        }
    }
    blkid_dev_iterate_end(iterator);
    return 0;
}

int Init(fsgangsterInfo *info) {
    int status = blkid_get_cache(&info->blkCache, NULL);
    if (status < 0) {
        fprintf(stderr, "Can't initialize blkid lib!\n");
        return -1;
    }
    return 0;
}

