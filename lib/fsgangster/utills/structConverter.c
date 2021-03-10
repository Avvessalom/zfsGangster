//
// Created by kain on 10.03.2021.
//
#include <byteswap.h>

#include "../zfs.h"


void convertZioChksum(struct zio_cksum* cksum){
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
    for (int k = 0; k < 3; k++) {
        blk->blk_pad[k] = bswap_64(blk->blk_pad[k]);
    }
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

void convertBlockTail(struct zio_block_tail* tail){
    tail->zbt_magic = bswap_64(tail->zbt_magic);
    convertZio(&tail->zbt_cksum);
}

void convertZioGbn(struct zio_gbh* gbh){
    convertBlkptr(&gbh->zg_blkptr);
    gbh->zg_filler = bswap_64(gbh->zg_filler);
    convertBlockTail(&gbh->zg_tail);
}

void convertDnodePhys(struct dnode_phys* dnode){
    dnode->dn_maxblkid = bswap_64(dnode->dn_maxblkid);
    dnode->dn_secphys = bswap_64(dnode->dn_secphys);
    for (int i = 0; i < 3; i++){
        dnode->dn_pad3[i] = bswap_64(dnode->dn_pad3);
    }
    convertBlkptr(&dnode->dn_blkptr);
}