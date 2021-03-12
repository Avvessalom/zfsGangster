//
// Created by kain on 12.03.2021.
//

#ifndef ZFSGANGSTER_UBERBLOCK_H
#define ZFSGANGSTER_UBERBLOCK_H

#define	SPA_DVAS_PER_BP	3		/* Number of DVAs in a bp	*/


typedef struct dva {
    uint64_t	dva_word[2];
} dva_t;

typedef struct blkptr {
    dva_t       blk_dva[SPA_DVAS_PER_BP];            /* 128-bit Data Virtual Address */
    uint64_t    blk_prop;              /* размер, сжатие, тип, и т.д.  */
    uint64_t    blk_pad[2];            /* зарезервировано              */
    uint64_t    blk_phys_birth;
    uint64_t    blk_birth;             /* номер группы транзакций      */
    uint64_t    blk_fill;              /* fill count                   */
    zio_cksum_t blk_cksum;          /* 256-битная контрольная сумма */
} blkptr_t;


struct uberblock {
    uint64_t ub_magic;    /* UBERBLOCK_MAGIC		*/
    uint64_t ub_version;    /* SPA_VERSION			*/
    uint64_t ub_txg;        /* txg of last sync		*/
    uint64_t ub_guid_sum;    /* sum of all vdev guids	*/
    uint64_t ub_timestamp;    /* UTC time of last sync	*/
    blkptr_t ub_rootbp;    /* MOS objset_phys_t		*/

    /* по документации блок до сюда, дальше из сурсов опензфс*/
    uint64_t ub_software_version;
    uint64_t ub_mmp_magic;    /* MMP_MAGIC			*/
    uint64_t ub_mmp_delay;
    uint64_t ub_mmp_config;
    uint64_t ub_checkpoint_txg;
};

#endif //ZFSGANGSTER_UBERBLOCK_H
