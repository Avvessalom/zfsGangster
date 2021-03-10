//
// Created by kain on 10.03.2021.
//
#include <byteswap.h>

#include "../zfs.h"


void convertZio(struct zio_cksum* cksum){
    for (int i = 0; i < 4; i++){
        cksum->zc_word[i] = bswap_64(cksum->zc_word[i]);
    }
}

void convertBlkptr(struct blkptr* blk){
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 2; j++) {
            blk->blk_dva[i].dva_word[j] = bswap_64(blk->blk_dva[i].dva_word[j]);
        }
    }
    blk->blk_prop = bswap_64(blk->blk_prop);
    blk->blk_birth = bswap_64(blk->blk_birth);
    blk->blk_fill = bswap_64(blk->blk_birth);
    convertZio(&blk->blk_cksum);
    //TODO blk_pad
}


void convertUberblock(struct uberblock* block){
    block->ub_magic = bswap_64(block->ub_magic);
    block->ub_version = bswap_64(block->ub_version);
    block->ub_txg = bswap_64(block->ub_txg);
    block->ub_guid_sum = bswap_64(block->ub_guid_sum);
    block->ub_timestamp = bswap_64(block->ub_timestamp);
    block->ub_software_version = bswap_64(block->ub_software_version);
    convertBlkptr(&block->ub_rootbp);
}