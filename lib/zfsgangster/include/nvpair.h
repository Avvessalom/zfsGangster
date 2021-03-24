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

typedef struct nvlist {
    int32_t		nvl_version;
    uint32_t	nvl_nvflag;	/* persistent flags */
    uint64_t	nvl_priv;	/* ptr to private data if not packed */
    uint32_t	nvl_flag;
    int32_t		nvl_pad;	/* currently not used, for alignment */
} nvlist_t;

#endif //ZFSGANGSTER_NVPAIR_H
