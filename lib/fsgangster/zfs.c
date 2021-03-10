//
// Created by kain on 21.02.2021.
//
#include <stdio.h>
#include <byteswap.h>

#include "zfs.h"

#define BLOCK_SIZE 512

int openZfs(const char* path){
    FILE* file = fopen(path, "rb");
    long int n;
    struct uberblock block;
    if (!file){
        perror("Cannot open\n");
        return -1;
    }

    fseek(file, 0x28000, SEEK_SET);

    fread(&block, sizeof(block), 1, file);
    n = bswap_64(block.ub_magic);
    printf("%lu\n", block.ub_magic);
    printf("%ld", n);
    fclose(file);
    return 0;
}

int main (){

    openZfs("/home/kain/github/ITMO-System-level-Software/scripts/fs.img");

    return 0;
}
