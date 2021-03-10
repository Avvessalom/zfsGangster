//
// Created by kain on 21.02.2021.
//
#include <stdio.h>

#include "zfs.h"
#include "utills/structConverter.c"

int openZfs(const char* path){
    FILE* file = fopen(path, "rb");
    long int n;
    struct uberblock block;
    if (!file){
        perror("Cannot open\n");
        return -1;
    }

    fseek(file, 0x25000, SEEK_SET);

    fread(&block, sizeof(block), 1, file);
    convertUberblock(&block);
    printf("%lu\n", block.ub_magic);
    fclose(file);
    return 0;
}

int main (){

    openZfs("/home/kain/github/zfsGangster/scripts/fs.img");

    return 0;
}
