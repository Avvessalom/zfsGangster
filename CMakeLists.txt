cmake_minimum_required(VERSION 3.17)
project(zfsGangster C)

set(CMAKE_C_STANDARD 11)

add_executable(zfsGangster lib/zfsgangster/zfs.c)

#add_executable(zfsGangster src/main.c)
#target_link_libraries(zfsGangster blkid)