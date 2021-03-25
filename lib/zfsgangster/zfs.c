//
// Created by kain on 21.02.2021.
//
#include <stdio.h>

#include "include/vdev.h"
#include "vdev.c"
#include "include/uberblock.h"
#include "include/zio.h"

int zfsGangster_open(const char *path) {
    struct vdev_label vdevLabel0;
    struct vdev_label vdevLabel1;
    struct vdev_label vdevLabel2;
    struct vdev_label vdevLabel3;

    FILE *file = fopen(path, "rb");
    if (!file) {
        perror("Cannot open\n");
        return -1;
    }

    fseek(file, 0, SEEK_SET);
    fread(&vdevLabel0, sizeof(struct vdev_label), 1, file);
    fread(&vdevLabel1, sizeof(struct vdev_label), 1, file);

    fseek(file, -sizeof(struct vdev_label), SEEK_END);
    fread(&vdevLabel3, sizeof(struct vdev_label), 1, file);

    fseek(file, -2 * sizeof(struct vdev_label), SEEK_END);
    fread(&vdevLabel2, sizeof(struct vdev_label), 1, file);

    parse_vdev_label(vdevLabel0);
    parse_vdev_label(vdevLabel1);
//    get_uberblocks(vdevLabel0);
    fclose(file);
    uberblock_verify((uberblock_t *) vdevLabel0.vl_uberblock);
    zio_eck_verify((struct zio_eck *) &vdevLabel0.vl_be.vbe_zbt.zec_magic);
    return 0;
}

int main() {

    zfsGangster_open("/Users/sdfedorov/Documents/ITMO/6_semester/System_Software_ITMO_2021/zfsGangster/scripts/fs.img");
    return 0;
}
