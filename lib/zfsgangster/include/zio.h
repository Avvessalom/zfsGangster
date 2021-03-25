//
// Created by kain on 12.03.2021.
//

#ifndef ZFSGANGSTER_ZIO_H
#define ZFSGANGSTER_ZIO_H
#include <inttypes.h>

#define	ZEC_MAGIC	0x210da7ab10c7a11ULL
typedef struct zio_cksum {
    uint64_t zc_word[4];
} zio_cksum_t;
typedef struct zio_eck {
    uint64_t zec_magic;        /* for validation, endianness */
    zio_cksum_t zec_cksum;    /* 256-bit checksum            */
} zio_eck_t;

int zio_eck_verify(struct zio_eck *cksum);

#endif //ZFSGANGSTER_ZIO_H
