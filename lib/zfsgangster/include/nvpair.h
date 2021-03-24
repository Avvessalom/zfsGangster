//
// Created by kain on 24.03.2021.
//

#ifndef ZFSGANGSTER_NVPAIR_H
#define ZFSGANGSTER_NVPAIR_H
/*
 * nvpair.c - Provides kernel & userland interfaces for manipulating
 *	name-value pairs.
 *
 * Overview Diagram
 *
 *  +--------------+
 *  |  nvlist_t    |
 *  |--------------|
 *  | nvl_version  |
 *  | nvl_nvflag   |
 *  | nvl_priv    -+-+
 *  | nvl_flag     | |
 *  | nvl_pad      | |
 *  +--------------+ |
 *                   V
 *      +--------------+      last i_nvp in list
 *      | nvpriv_t     |  +--------------------->
 *      |--------------|  |
 *   +--+- nvp_list    |  |   +------------+
 *   |  |  nvp_last   -+--+   + nv_alloc_t |
 *   |  |  nvp_curr    |      |------------|
 *   |  |  nvp_nva    -+----> | nva_ops    |
 *   |  |  nvp_stat    |      | nva_arg    |
 *   |  +--------------+      +------------+
 *   |
 *   +-------+
 *           V
 *   +---------------------+      +-------------------+
 *   |  i_nvp_t            |  +-->|  i_nvp_t          |  +-->
 *   |---------------------|  |   |-------------------|  |
 *   | nvi_next           -+--+   | nvi_next         -+--+
 *   | nvi_prev (NULL)     | <----+ nvi_prev          |
 *   | . . . . . . . . . . |      | . . . . . . . . . |
 *   | nvp (nvpair_t)      |      | nvp (nvpair_t)    |
 *   |  - nvp_size         |      |  - nvp_size       |
 *   |  - nvp_name_sz      |      |  - nvp_name_sz    |
 *   |  - nvp_value_elem   |      |  - nvp_value_elem |
 *   |  - nvp_type         |      |  - nvp_type       |
 *   |  - data ...         |      |  - data ...       |
 *   +---------------------+      +-------------------+
 *
 *
 *
 *   +---------------------+              +---------------------+
 *   |  i_nvp_t            |  +-->    +-->|  i_nvp_t (last)     |
 *   |---------------------|  |       |   |---------------------|
 *   |  nvi_next          -+--+ ... --+   | nvi_next (NULL)     |
 * <-+- nvi_prev           |<-- ...  <----+ nvi_prev            |
 *   | . . . . . . . . .   |              | . . . . . . . . .   |
 *   | nvp (nvpair_t)      |              | nvp (nvpair_t)      |
 *   |  - nvp_size         |              |  - nvp_size         |
 *   |  - nvp_name_sz      |              |  - nvp_name_sz      |
 *   |  - nvp_value_elem   |              |  - nvp_value_elem   |
 *   |  - DATA_TYPE_NVLIST |              |  - nvp_type         |
 *   |  - data (embedded)  |              |  - data ...         |
 *   |    nvlist name      |              +---------------------+
 *   |  +--------------+   |
 *   |  |  nvlist_t    |   |
 *   |  |--------------|   |
 *   |  | nvl_version  |   |
 *   |  | nvl_nvflag   |   |
 *   |  | nvl_priv   --+---+---->
 *   |  | nvl_flag     |   |
 *   |  | nvl_pad      |   |
 *   |  +--------------+   |
 *   +---------------------+
 *
 *
 * N.B. nvpair_t may be aligned on 4 byte boundary, so +4 will
 * allow value to be aligned on 8 byte boundary
 *
 * name_len is the length of the name string including the null terminator
 * so it must be >= 1
 */
typedef struct i_nvp i_nvp_t;

typedef enum {
    DATA_TYPE_DONTCARE = -1,
    DATA_TYPE_UNKNOWN = 0,
    DATA_TYPE_BOOLEAN,
    DATA_TYPE_BYTE,
    DATA_TYPE_INT16,
    DATA_TYPE_UINT16,
    DATA_TYPE_INT32,
    DATA_TYPE_UINT32,
    DATA_TYPE_INT64,
    DATA_TYPE_UINT64,
    DATA_TYPE_STRING,
    DATA_TYPE_BYTE_ARRAY,
    DATA_TYPE_INT16_ARRAY,
    DATA_TYPE_UINT16_ARRAY,
    DATA_TYPE_INT32_ARRAY,
    DATA_TYPE_UINT32_ARRAY,
    DATA_TYPE_INT64_ARRAY,
    DATA_TYPE_UINT64_ARRAY,
    DATA_TYPE_STRING_ARRAY,
    DATA_TYPE_HRTIME,
    DATA_TYPE_NVLIST,
    DATA_TYPE_NVLIST_ARRAY,
    DATA_TYPE_BOOLEAN_VALUE,
    DATA_TYPE_INT8,
    DATA_TYPE_UINT8,
    DATA_TYPE_BOOLEAN_ARRAY,
    DATA_TYPE_INT8_ARRAY,
#if !defined(_KERNEL) && !defined(_STANDALONE)
    DATA_TYPE_UINT8_ARRAY,
    DATA_TYPE_DOUBLE
#else
    DATA_TYPE_UINT8_ARRAY
#endif
} data_type_t;

/* NV allocator framework */
typedef struct nv_alloc_ops nv_alloc_ops_t;

typedef struct nv_alloc {
    const nv_alloc_ops_t *nva_ops;
    void *nva_arg;
} nv_alloc_t;

struct nv_alloc_ops {
    int (*nv_ao_init)(nv_alloc_t *, va_list);
    void (*nv_ao_fini)(nv_alloc_t *);
    void *(*nv_ao_alloc)(nv_alloc_t *, size_t);
    void (*nv_ao_free)(nv_alloc_t *, void *, size_t);
    void (*nv_ao_reset)(nv_alloc_t *);
};


typedef struct {
    i_nvp_t		*nvp_list;	/* linked list of nvpairs */
    i_nvp_t		*nvp_last;	/* last nvpair */
    i_nvp_t		*nvp_curr;	/* current walker nvpair */
    nv_alloc_t	*nvp_nva;	/* pluggable allocator */
    uint32_t	nvp_stat;	/* internal state */

    i_nvp_t		**nvp_hashtable; /* table of entries used for lookup */
    uint32_t	nvp_nbuckets;	/* # of buckets in hash table */
    uint32_t	nvp_nentries;	/* # of entries in hash table */
} nvpriv_t;


typedef struct nvlist {
    int32_t		nvl_version;
    uint32_t	nvl_nvflag;	/* persistent flags */
    nvpriv_t	nvl_priv;	/* ptr to private data if not packed */
    uint32_t	nvl_flag;
    int32_t		nvl_pad;	/* currently not used, for alignment */
} nvlist_t;


typedef struct nvpair {
    int32_t nvp_size;	/* size of this nvpair */
    int16_t	nvp_name_sz;	/* length of name string */
    int16_t	nvp_reserve;	/* not used */
    int32_t	nvp_value_elem;	/* number of elements for array types */
    data_type_t nvp_type;	/* type of value */
    /* name string */
    /* aligned ptr array for string arrays */
    /* aligned array of data for value */
} nvpair_t;


struct i_nvp {
    union {
        /* ensure alignment */
        uint64_t	_nvi_align;

        struct {
            /* pointer to next nvpair */
            i_nvp_t	*_nvi_next;

            /* pointer to prev nvpair */
            i_nvp_t	*_nvi_prev;

            /* next pair in table bucket */
            i_nvp_t	*_nvi_hashtable_next;
        } _nvi;
    } _nvi_un;

    /* nvpair */
    nvpair_t nvi_nvp;
};

#endif //ZFSGANGSTER_NVPAIR_H
