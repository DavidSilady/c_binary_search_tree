//
// Created by david on 11/1/2019.
//

#ifndef TREES_HASH_H
#define TREES_HASH_H

#include "tree.h"

typedef struct Hash {
    int prime;
    int num_elements;
    double loadFactor;
    Tree **table;
} Hash;

#endif //TREES_HASH_H
