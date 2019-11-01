//
// Created by david on 11/1/2019.
//

#include "hash.h"
#include "tree.h"
#include <stdlib.h>

Tree **new_hash_table(int size) {
    Tree **table = malloc(size * sizeof(Tree));
    for (int i = 0; i < size; ++i) {
        table[i] = new_tree();
    }
    return table;
}

Hash *new_hash(int size) {
    Hash *hash = malloc(sizeof(Hash));
    hash->loadFactor = 0;
    hash->num_elements = 0;
    hash->prime = size;
    hash->table = new_hash_table(size);
    return hash;
}

int hash_function(Hash *hash, int value) {
    return value % hash->prime;
}

void hash_add(Hash *hash, int value) {
    int index = hash_function(hash, value);
    Tree *tree = hash->table[index];
    int old_size = tree->size;

    insert(tree, value);
    hash->num_elements += tree->size - old_size;
    hash->loadFactor = ((double) hash->num_elements / (double) hash->prime);
}

Node *hash_find(Hash *hash, int value) {
    int index = hash_function(hash, value);
    Tree *tree = hash->table[index];
    return find_value(tree, value);
}
