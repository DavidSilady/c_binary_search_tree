//
// Created by david on 10/22/2019.
//

#ifndef TREES_TREE_H
#define TREES_TREE_H

typedef struct Node {
    int value;
    int height;
    struct Node *parent;
    struct Node *right;
    struct Node *left;
} Node;

typedef struct Tree {
    int size;
    struct Node *root;
} Tree;

void insert(Tree *tree, int value);
void bvs_insert(Tree *tree, int value);
void in_order_print(Tree *tree);
Node *find_value(Tree *tree, int i);
Tree *new_tree();
void destroy_tree(Tree *tree);

#endif //TREES_TREE_H
