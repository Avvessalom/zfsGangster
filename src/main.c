//
// Created by kain on 20.02.2021.
//

#include <stdio.h>
#include <string.h>

#include "../lib/zfsgangster/Dev.c"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        puts("incorrect argument\n");
        return 1;
    }

    if (!strcmp(argv[1], "--first")) {
        fsgangsterInfo info;
        Init(&info);
        DeviceList(&info);
        IteratorDevice(&info);
    } else if (!strcmp(argv[1], "--second")){
        printf("test2 %s\n", "second");
    } else {
        puts("invalid argument\n");
        return 1;
    }
    return 0;
}