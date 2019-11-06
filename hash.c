//
// Created by david on 11/1/2019.
//

#include "hash.h"
#include "tree.h"
#include <stdlib.h>

#define MAX_LOAD_FACTOR 1.5

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
    hash->prime = size;
    hash->table = new_hash_table(size);
    return hash;
}

int hash_function(Hash *hash, int value) {
    return value % hash->prime;
}

int find_next_prime(int value) {
    int next_prime = value;

    if(next_prime % 2 == 0) {
        next_prime += 1;
    }

    while(1) {
        int i;
        for (i = 3; i < next_prime; i += 2) {
            if(next_prime % 2 == 0) {
                next_prime += 2;
                break;
            }
        }
        if (i == next_prime) {
            break;
        }
    }

    return next_prime;
}

void hash_add(Hash *hash, int value) {
    int index = hash_function(hash, value);
    Tree *tree = hash->table[index];
    int old_size = tree->size;

    insert(tree, value);
    hash->num_elements += tree->size - old_size;
    hash->loadFactor = ((double) hash->num_elements / (double) hash->prime);

    if(hash->loadFactor > 1.5) {
        resize(hash, find_next_prime(hash->prime * 2));
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
    int old_prime = hash->prime;

    hash->table = new_hash_table(new_size);
    hash->prime = new_size;

    for (int i = 0; i < old_prime; ++i) {
        hash_refill(hash, old_table[i]->root);
    }

    free(old_table);
}

