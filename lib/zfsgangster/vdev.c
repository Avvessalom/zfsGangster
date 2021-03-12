//
// Created by kain on 12.03.2021.
//

#include "include/vdev.h"
#include <stdio.h>

void printncImpl(char* s, int cnt) {
    fwrite(s, 1, cnt, stdout);
}

#define printnc(s) printncImpl(s, sizeof(s))

void parse_vdev_label(struct vdev_label label){
    printnc(label.vl_vdev_phys.vp_nvlist);
    puts(" \n");
    printnc(label.vl_uberblock);
}
