//
// Created by Sergey Fedorov on 3/25/21.
//

#ifndef ZFSGANGSTER_BYTESWAP_H
#define ZFSGANGSTER_BYTESWAP_H

#define bswap_8(x) ((x) & 0xff)
#define bswap_16(x) ((bswap_8(x) << 8) | bswap_8((x) >> 8))
#define bswap_32(x) ((bswap_16(x) << 16) | bswap_16((x) >> 16))
#define bswap_64(x) ((bswap_32(x) << 32) | bswap_32((x) >> 32))

#endif //ZFSGANGSTER_BYTESWAP_H
