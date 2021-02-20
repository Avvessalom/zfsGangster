//
// Created by kain on 20.02.2021.
//

#include <stdio.h>
#include <string.h>

#include "../lib/fsgangster/Dev.c"

int main(int argc, char *argv[]) {
    for(int i = 0 ; i < argc; i++) {
        printf("Argument %d: %s\n", i, argv[i]);
    }
    if (argc > 2) {
        puts("incorrect argument\n");
        printf("%d", argc);
        return 1;
    } else if (argc < 1) {
        puts("argument is empty, pleas input argument\n");
        return 1;
    }

    if (!strcmp(argv[1], "--first")) {
        printf("test %s", "first\n");
        fsgangsterInfo info;
        Init(&info);
        DeviceList(&info);
        IteratorDevice(&info);
    } else if (!strcmp(argv[1], "--second")){
        printf("test2 %s", "second");
    } else {
        puts("incorrect com");
        return 1;
    }
    return 0;
}