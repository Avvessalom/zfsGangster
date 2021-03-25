//
// Created by kain on 25.03.2021.
//

#include "../include/zio.h"
#include "../utills/structConverter.h"
#include <byteswap.h>
#include <stdio.h>

int zio_eck_verify(struct zio_eck *cksum){
    uint64_t magic = ZEC_MAGIC;
    bswap_64(magic);
    printf("%lu\n", cksum->zec_magic);
    if (cksum->zec_magic == bswap_64(magic))
        convert_zio_eck(cksum);

    if (cksum->zec_magic != ZEC_MAGIC)
        return -1;

    printf("ZAEBIS");
    return 0;
}
