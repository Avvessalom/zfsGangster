//
// Created by kain on 21.02.2021.
//
#ifndef ITMO_SYSTEM_LEVEL_SOFTWARE_ZFS_H
#define ITMO_SYSTEM_LEVEL_SOFTWARE_ZFS_H
#include <stdbool.h>

bool isZfs{};

typedef struct filesystem {
    FILE *file;
    uint32_t blockSize;
} filesystem;

typedef struct znode_phys {
    uint64_t zp_atime[2];/* время последнего доступа */
    uint64_t zp_mtime[2];/* время последней изменения модификации * файла */
    uint64_t zp_ctime[2];/* время последнего изменения */
    uint64_t zp_crtime[2];/* время создания */
    uint64_t zp_gen;/* номер группы транзакций на момент * создания */
    uint64_t zp_mode;/* mode-биты */
    uint64_t zp_size;/* размер файла */
    uint64_t zp_parent;/* родительский каталог ("..") */
    uint64_t zp_links;
    uint64_t zp_xattr;/* DMU-объект для xattrs */
    uint64_t zp_rdev;/* dev_t для VBLK и VCHR файлов */
    uint64_t zp_flags;/* флаги */
    uint64_t zp_uid;/* владелец */
    uint64_t zp_gid;/* группа */
    uint64_t zp_pad[4];/* зарезервировано */
    zfs_znode_acl_t zp_acl;/* ACL */
} znode_phys_t;

#endif //ITMO_SYSTEM_LEVEL_SOFTWARE_ZFS_H
