//
// Created by kain on 12.03.2021.
//
#include <stdint.h>
#include "lib/libspl/include/assert.h"

#include "include/vdev.h"
#include <stdio.h>

void printncImpl(char* s, int cnt) {
    fwrite(s, 1, cnt, stdout);
}

#define printnc(s) printncImpl(s, sizeof(s))

void parse_vdev_label(struct vdev_label label){
    printnc(label.vl_vdev_phys.vp_nvlist);
    puts(" \n");
    printnc(label.vl_uberblock);
}

uint64_t vdev_label_offset(uint64_t psize, int l, uint64_t offset) {
    ASSERT(offset < sizeof (vdev_label_t));
//    ASSERT(P2PHASE_TYPED(psize, sizeof (vdev_label_t), uint64_t) == 0);

    return (offset + l * sizeof (vdev_label_t) + (l < VDEV_LABELS / 2 ?
            0 : psize - VDEV_LABELS * sizeof (vdev_label_t)));
}
