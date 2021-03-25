//
// Created by kain on 24.03.2021.
//

#include "../include/nvpair.h"

char * nvpair_name(nvpair_t *nvp) {
    return (NVP_NAME(nvp));
}

data_type_t nvpair_type(nvpair_t *nvp) {
    return (NVP_TYPE(nvp));
}