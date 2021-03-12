//
// Created by kain on 21.02.2021.
//
#include <stdio.h>

#include "include/vdev.h"

int openZfs(const char* path){
    struct vdev_label vdevLabel;
    FILE* file = fopen(path, "rb");
    long int n;
    if (!file){
        perror("Cannot open\n");
        return -1;
    }

    fseek(file, 0, SEEK_SET);

    fread(&vdevLabel, sizeof(vdevLabel), 1, file);
    fclose(file);
    return 0;
}

int main (){

    openZfs("/home/kain/github/zfsGangster/scripts/fs.img");

    return 0;
}
