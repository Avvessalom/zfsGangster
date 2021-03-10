//
// Created by kain on 21.02.2021.
//
#ifndef ITMO_SYSTEM_LEVEL_SOFTWARE_ZFS_H
#define ITMO_SYSTEM_LEVEL_SOFTWARE_ZFS_H

#include <stdbool.h>
#include <inttypes.h>

#define SPA_MINBLOCKSHIFT   9
#define SPA_MINBLOCKSIZE   (1ULL << SPA_MINBLOCKSHIFT)
#define	SPA_GANGBLOCKSIZE	SPA_MINBLOCKSIZE

#define	SPA_GBH_NBLKPTRS	((SPA_GANGBLOCKSIZE - \
	sizeof (zio_block_tail_t)) / sizeof (blkptr_t))
#define	SPA_GBH_FILLER		((SPA_GANGBLOCKSIZE - \
	sizeof (zio_block_tail_t) - \
	(SPA_GBH_NBLKPTRS * sizeof (blkptr_t))) /\
	sizeof (uint64_t))


typedef struct dva {
    uint64_t dva_word[2];
} dva_t;

typedef struct zio_cksum {
    uint64_t zc_word[4];
} zio_cksum_t;

typedef struct blkptr {
    dva_t    blk_dva[3];            /* 128-bit Data Virtual Address */
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

typedef struct zio_block_tail {
    uint64_t	zbt_magic;	        /* for validation, endianness	*/
    zio_cksum_t	zbt_cksum;	        /* 256-bit checksum		*/
} zio_block_tail_t;

typedef struct zio_gbh {
    blkptr_t            zg_blkptr[SPA_GBH_NBLKPTRS];
    uint64_t            zg_filler[SPA_GBH_FILLER];
    zio_block_tail_t	zg_tail;
} zio_gbh_phys_t;


typedef struct dnode_phys { //from https://raw.githubusercontent.com/AustinWise/ZfsSharp/master/ZFSOnDiskFormat.pdf P23
    uint8_t dn_type;		    /* dmu_object_type_t */
    uint8_t dn_indblkshift;		/* ln2(indirect block size) */
    uint8_t dn_nlevels;		    /* 1=dn_blkptr->data blocks */
    uint8_t dn_nblkptr;		    /* length of dn_blkptr */
    uint8_t dn_bonustype;		/* type of data in bonus buffer */
    uint8_t	dn_checksum;		/* ZIO_CHECKSUM type */
    uint8_t	dn_compress;		/* ZIO_COMPRESS type */
    uint8_t dn_pad[1];		    /* DNODE_FLAG_* */
    uint16_t dn_datablkszsec;	/* data block size in 512b sectors */
    uint16_t dn_bonuslen;		/* length of dn_bonus */
    uint8_t dn_pad2[4];         /* accounting is protected by dn_dirty_mtx */
    uint64_t dn_maxblkid;		/* largest allocated block ID */
    uint64_t dn_secphys;        /* The sum of all asize values for all block pointers (data and indirect) for this object. */
    uint64_t dn_pad3[4];
    blkptr_t dn_blkptr;          /* block pointer array containing dn_nblkptr block pointers Page 25 */
    uint8_t dn_bonus[BONUSLEN];
} dnode_phys_t;

#endif //ITMO_SYSTEM_LEVEL_SOFTWARE_ZFS_H
