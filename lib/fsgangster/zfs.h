//
// Created by kain on 21.02.2021.
//
#ifndef ITMO_SYSTEM_LEVEL_SOFTWARE_ZFS_H
#define ITMO_SYSTEM_LEVEL_SOFTWARE_ZFS_H

#include <stdbool.h>
#include <inttypes.h>


typedef struct dva {
    uint64_t dva_word[2];
} dva_t;


typedef struct zio_cksum {
    uint64_t zc_word[4];
} zio_cksum_t;


typedef struct blkptr {
    dva_t blk_dva[3];               /* 128-bit Data Virtual Address */
    uint64_t blk_prop;              /* размер, сжатие, тип, и т.д.  */
    uint64_t blk_pad[3];            /* зарезервировано              */
    uint64_t blk_birth;             /* номер группы транзакций      */
    uint64_t blk_fill;              /* fill count                   */
    zio_cksum_t blk_cksum;          /* 256-битная контрольная сумма */
} blkptr_t;


struct __attribute__((packed)) uberblock {
    uint64_t ub_magic;              /* UBERBLOCK_MAGIC		    */
    uint64_t ub_version;            /* SPA_VERSION			    */
    uint64_t ub_txg;                /* txg of last sync		    */
    uint64_t ub_guid_sum;           /* sum of all vdev guids	*/
    uint64_t ub_timestamp;          /* UTC time of last sync	*/
    blkptr_t ub_rootbp;             /* MOS objset_phys_t		*/
    uint64_t ub_software_version;
};


#endif //ITMO_SYSTEM_LEVEL_SOFTWARE_ZFS_H
