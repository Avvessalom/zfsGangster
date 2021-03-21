cmake_minimum_required(VERSION 3.17)
project(zfsGangster C)

set(CMAKE_C_STANDARD 11)

include_directories(/lib/zfsgangster/lib/libspl)
include_directories(/lib/zfsgangster/lib/libspl/include)
add_executable(zfsGangster
        lib/zfsgangster/zfs.c
        lib/zfsgangster/lib/libspl/include/assert.h
        lib/zfsgangster/lib/libspl/assert.c
        )

#add_executable(zfsGangster src/main.c)
#target_link_libraries(zfsGangster blkid)