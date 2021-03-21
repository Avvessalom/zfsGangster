/*
 * CDDL HEADER START
 *
 * The contents of this file are subject to the terms of the
 * Common Development and Distribution License (the "License").
 * You may not use this file except in compliance with the License.
 *
 * You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
 * or http://www.opensolaris.org/os/licensing.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 *
 * When distributing Covered Code, include this CDDL HEADER in each
 * file and include the License file at usr/src/OPENSOLARIS.LICENSE.
 * If applicable, add the following below this CDDL HEADER, with the
 * fields enclosed by brackets "[]" replaced with your own identifying
 * information: Portions Copyright [yyyy] [name of copyright owner]
 *
 * CDDL HEADER END
 */

/*
 * Copyright (c) 2005, 2010, Oracle and/or its affiliates. All rights reserved.
 * Copyright (c) 2012, 2020 by Delphix. All rights reserved.
 * Copyright (c) 2017, Intel Corporation.
 */


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


/*
 * Basic routines to read and write from a vdev label.
 * Used throughout the rest of this file.
 */
uint64_t vdev_label_offset(uint64_t psize, int l, uint64_t offset) {
    ASSERT(offset < sizeof (vdev_label_t));
//    ASSERT(P2PHASE_TYPED(psize, sizeof (vdev_label_t), uint64_t) == 0);

    return (offset + l * sizeof (vdev_label_t) + (l < VDEV_LABELS / 2 ?
            0 : psize - VDEV_LABELS * sizeof (vdev_label_t)));
}

/*
 * Returns back the vdev label associated with the passed in offset.
 */
int vdev_label_number(uint64_t psize, uint64_t offset) {
    int l;

    if (offset >= psize - VDEV_LABEL_END_SIZE) {
        offset -= psize - VDEV_LABEL_END_SIZE;
        offset += (VDEV_LABELS / 2) * sizeof (vdev_label_t);
    }
    l = offset / sizeof (vdev_label_t);
    return (l < VDEV_LABELS ? l : -1);
}

static void vdev_label_read(zio_t *zio, vdev_t *vd, int l, abd_t *buf, uint64_t offset,
                uint64_t size, zio_done_func_t *done, void *private, int flags) {
            ASSERT(
            spa_config_held(zio->io_spa, SCL_STATE, RW_READER) == SCL_STATE ||
            spa_config_held(zio->io_spa, SCL_STATE, RW_WRITER) == SCL_STATE);
            ASSERT(flags & ZIO_FLAG_CONFIG_WRITER);

    zio_nowait(zio_read_phys(zio, vd,
                             vdev_label_offset(vd->vdev_psize, l, offset),
                             size, buf, ZIO_CHECKSUM_LABEL, done, private,
                             ZIO_PRIORITY_SYNC_READ, flags, B_TRUE));
}
