//
// Created by david on 11/1/2019.
//

#include "hash.h"
#include "tree.h"
#include <stdlib.h>
#include <stdio.h>

#define MAX_LOAD_FACTOR 5

void resize(Hash *hash, int new_size);


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
    hash->size = size;
    hash->table = new_hash_table(hash->size);
    return hash;
}

void hash_destroy(Hash *hash) {
    for (int i = 0; i < hash->size; ++i) {
        destroy_tree(hash->table[i]);
    }
    free(hash->table);
    free(hash);
}

int hash_function(Hash *hash, int value) {
    return value % hash->size;
}

void hash_add(Hash *hash, int value) {
    int index = hash_function(hash, value);
    Tree *tree = hash->table[index];
    int old_size = tree->size;

    insert(tree, value);
    hash->num_elements += tree->size - old_size;
    hash->loadFactor = ((double) hash->num_elements / (double) hash->size);

    if(hash->loadFactor > MAX_LOAD_FACTOR) {
        resize(hash, hash->size * 2);
    }
}

Node *hash_find(Hash *hash, int value) {
    int index = hash_function(hash, value);
    Tree *tree = hash->table[index];
    return find_value(tree, value);
}

void hash_refill(Hash *hash, Node *node) {
    if (node == NULL)
        return;

    hash_refill(hash, node->left);
    hash_refill(hash, node->right);

    hash_add(hash, node->value);
    free(node);
}

void resize(Hash *hash, int new_size) {
    Tree **old_table = hash->table;
    int old_size = hash->size;
    //printf("\nResizing from %d to %d. . .\n\n", old_size, new_size);
    hash->size = new_size;
    hash->table = new_hash_table(hash->size);

    hash->loadFactor = 0;
    for (int i = 0; i < old_size; ++i) {
        hash_refill(hash, old_table[i]->root);
    }

    free(old_table);
}

