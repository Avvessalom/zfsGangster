//
// Created by kain on 25.03.2021.
//

#ifndef ZFSGANGSTER_STRUCTCONVERTER_H
#define ZFSGANGSTER_STRUCTCONVERTER_H

#include "../include/vdev.h"
#include "../include/uberblock.h"

void convert_zio_chksum(struct zio_cksum* cksum);
void convert_blkptr(struct blkptr* blk);
void convert_uberblock(struct uberblock* block);
void convert_zio_eck(struct zio_eck* eck);

#endif //ZFSGANGSTER_STRUCTCONVERTER_H
