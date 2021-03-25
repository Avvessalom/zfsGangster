//
// Created by kain on 25.03.2021.
//

#include "../include/uberblock.h"

#include "../utills/structConverter.h"
#include <byteswap.h>

#define	BSWAP_64(x)	((BSWAP_32(x) << 32) | BSWAP_32((x) >> 32))

int uberblock_verify(uberblock_t *ub) {
    if (ub->ub_magic == bswap_64((uint64_t)UBERBLOCK_MAGIC))
        convert_uberblock(ub);

    if (ub->ub_magic != UBERBLOCK_MAGIC)
        return -1;

    return (0);
}
