//
// Created by kain on 20.02.2021.
//

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc > 1) {
        puts("incorrect argument\n");
        return 1;
    } else if (argc < 1) {
        puts("argument is empty, pleas input argument\n");
        return 1;
    }

    if (!strcmp(argv[1], "--kek")) {
        printf("test %s", "kek\n");
    } else {
        puts("incorrect argument");
        return 1;
    }
    return 0;
}