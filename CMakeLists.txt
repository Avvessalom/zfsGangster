cmake_minimum_required(VERSION 3.17)
project(zfsGangster C)

set(CMAKE_C_STANDARD 11)

include_directories(/lib/zfsgangster/include)
include_directories(/lib/zfsgangster/utills)
include_directories(/lib/zfsgangster)


add_executable(zfsGangster
        lib/zfsgangster/zfs.c
        lib/zfsgangster/include/nvpair.h
        lib/zfsgangster/include/uberblock.h
        lib/zfsgangster/include/vdev.h
        lib/zfsgangster/include/zio.h
        lib/zfsgangster/module/uberblock.c
        lib/zfsgangster/module/zio.c
        lib/zfsgangster/module/nvpair.c
        lib/zfsgangster/utills/structConverter.h
        lib/zfsgangster/utills/structConverter.c
        )

#add_executable(zfsGangster src/main.c)
#target_link_libraries(zfsGangster blkid)