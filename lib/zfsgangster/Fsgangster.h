//
// Created by kain on 20.02.2021.
//

#ifndef ITMO_SYSTEM_LEVEL_SOFTWARE_FSGANGSTER_H
#define ITMO_SYSTEM_LEVEL_SOFTWARE_FSGANGSTER_H

#include <blkid/blkid.h>


typedef struct fsgangsterInfo
{
    blkid_cache blkCache;
}fsgangsterInfo;

int DeviceList(fsgangsterInfo* info);
int IteratorDevice(fsgangsterInfo*);
int Init(fsgangsterInfo*);

#endif //ITMO_SYSTEM_LEVEL_SOFTWARE_FSGANGSTER_H
