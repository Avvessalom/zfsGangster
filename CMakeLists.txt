cmake_minimum_required(VERSION 3.17)
project(zfsGangster C)

set(CMAKE_C_STANDARD 11)

include_directories(/lib/zfsgangster/include)
include_directories(/lib/zfsgangster)


add_executable(zfsGangster
        lib/zfsgangster/zfs.c
        lib/zfsgangster/include/nvpair.h
        lib/zfsgangster/include/uberblock.h
        lib/zfsgangster/include/vdev.h
        lib/zfsgangster/include/zio.h
        )

#add_executable(zfsGangster src/main.c)
#target_link_libraries(zfsGangster blkid)