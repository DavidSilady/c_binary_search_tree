//
// Created by david on 11/1/2019.
//

#ifndef TREES_HASH_H
#define TREES_HASH_H

#include "tree.h"

typedef struct Hash {
    int size;
    int num_elements;
    double loadFactor;
    Tree **table;
} Hash;

Hash *new_hash(int size);
void hash_add(Hash *hash, int value);
Node *hash_find(Hash *hash, int value);
void hash_destroy(Hash *hash);

#endif //TREES_HASH_H
