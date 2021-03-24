//
// Created by kain on 12.03.2021.
//

#ifndef ZFSGANGSTER_VDEV_H
#define ZFSGANGSTER_VDEV_H

#include <inttypes.h>

#include "zio.h"
#include "nvpair.h"

#define VDEV_SKIP_SIZE        (8 << 10)
#define VDEV_UBERBLOCK_RING   (128 << 10)
#define VDEV_PHYS_SIZE        (112 << 10)


typedef struct vdev_boot_envblock {
    uint64_t vbe_version;
    char vbe_bootenv[VDEV_SKIP_SIZE - sizeof(uint64_t) -
                     sizeof(zio_eck_t)];
    zio_eck_t vbe_zbt;
} vdev_boot_envblock_t;

gtypedef struct vdev_phys {
    char vp_nvlist[VDEV_PHYS_SIZE - sizeof(zio_eck_t)];
    zio_eck_t vp_zbt;
} vdev_phys_t;

typedef struct vdev_label {
    char vl_pad[VDEV_SKIP_SIZE];               /*  8K  */
    vdev_boot_envblock_t vl_be;               /*  8K   */
    vdev_phys_t vl_vdev_phys;                 /* 112K */
    char vl_uberblock[VDEV_UBERBLOCK_RING];  /* 128K */
} vdev_label_t;

#endif //ZFSGANGSTER_VDEV_H
