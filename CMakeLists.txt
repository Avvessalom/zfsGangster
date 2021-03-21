cmake_minimum_required(VERSION 3.17)
project(zfsGangster C)

set(CMAKE_C_STANDARD 11)

include_directories(/lib/zfsgangster/include/os/freebsd/spl/sys)
include_directories(/lib/zfsgangster/include/os/linux/spl/sys)
include_directories(/lib/zfsgangster/lib/libspl)
include_directories(/lib/zfsgangster/include/sys)
include_directories(/lib/zfsgangster/include)

add_executable(zfsGangster
        lib/zfsgangster/zfs.c
        lib/zfsgangster/lib/libspl/include/assert.h
        lib/zfsgangster/lib/libspl/assert.c
        lib/zfsgangster/include/os/freebsd/spl/sys/condvar.h
        lib/zfsgangster/include/os/freebsd/spl/sys/list.h
        lib/zfsgangster/include/os/freebsd/spl/sys/mutex.h
        lib/zfsgangster/include/os/freebsd/spl/sys/rwlock.h
        lib/zfsgangster/include/os/linux/spl/sys/time.h
        lib/zfsgangster/include/sys/avl.h
        lib/zfsgangster/include/sys/avl_impl.h
        lib/zfsgangster/include/sys/dmu.h
        lib/zfsgangster/include/sys/nvpair.h
        lib/zfsgangster/include/sys/range_tree.h
        lib/zfsgangster/include/sys/spa.h
        lib/zfsgangster/include/sys/spa_checksum.h
        lib/zfsgangster/include/sys/space_map.h
        lib/zfsgangster/include/sys/bitops.h
        lib/zfsgangster/include/sys/kstat.h
        lib/zfsgangster/include/sys/txg.h
        lib/zfsgangster/include/sys/vdev.h
        lib/zfsgangster/include/sys/vdev_indirect_births.h
        lib/zfsgangster/include/sys/vdev_indirect_mapping.h
        lib/zfsgangster/include/sys/vdev_rebuild.h
        lib/zfsgangster/include/sys/fs/zfs.h
        lib/zfsgangster/include/sys/zfs_context.h
        lib/zfsgangster/include/sys/zfs_ratelimit.h
        lib/zfsgangster/include/sys/zio_priority.h
        lib/zfsgangster/include/uberblock.h
        lib/zfsgangster/include/vdev.h
        lib/zfsgangster/include/zio.h
        )

#add_executable(zfsGangster src/main.c)
#target_link_libraries(zfsGangster blkid)