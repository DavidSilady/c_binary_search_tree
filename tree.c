//
// Created by david on 10/22/2019.
//

#include "tree.h"
#include <stdlib.h>
#include <stdio.h>

int update_height(Node *node);
Node *insert_node(Node *node, int new_value);
Node *recursive_find_value(Node *node, int i);
Node *rebalance(Node *node);
Node *max_node(Node *node);
Node *min_node(Node *node);


Node *new_node(int value, Node *parent) {
    Node *node = malloc(sizeof(Node));
    if (node == NULL) {
        printf("Memory full.");
        return NULL;
    }
    node->left = NULL;
    node->right = NULL;
    node->parent = parent;
    node->value = value;
    node->height = 0;
    return node;
}

Tree *new_tree() {
    Tree *tree = malloc(sizeof(Tree));
    if (tree == NULL) {
        printf("Memory full.");
        return NULL;
    }
    tree->size = 0;
    tree->root = NULL;
    return tree;
}

void insert(Tree *tree, int value) {
    if(tree->root == NULL) {
        tree->root = new_node(value, NULL);
    } else {
        tree->root = insert_node(tree->root, value);
    }
    tree->size++;
}

Node *bvs_insert_node(Node *node, int new_value);
void bvs_insert(Tree *tree, int value) {
    if(tree->root == NULL) {
        tree->root = new_node(value, NULL);
    } else {
        tree->root = bvs_insert_node(tree->root, value);
    }
    tree->size++;
}

Node *bvs_insert_node(Node *node, int new_value) {
    if (new_value == node->value) {
        return node;
    }
    if(new_value < node->value) {
        if(node->left == NULL) {
            node->left = new_node(new_value, node);
        } else {
            bvs_insert_node(node->left, new_value);
        }
    } else {
        if(node->right == NULL) {
            node->right = new_node(new_value, node);
        } else {
            bvs_insert_node(node->right, new_value);
        }
    }
    return node;
}

Node *insert_node(Node *node, int new_value) {
    if (new_value == node->value) {
        return node;
    }
    if(new_value < node->value) {
        if(node->left == NULL) {
            node->left = new_node(new_value, node);
        } else {
            insert_node(node->left, new_value);
        }
    } else {
        if(node->right == NULL) {
            node->right = new_node(new_value, node);
        } else {
            insert_node(node->right, new_value);
        }
    }
    node = rebalance(node);
    return node;
}

void recursive_in_order_print(Node *node) {
    if(node == NULL)
        return;
    if(node->left != NULL) {
        recursive_in_order_print(node->left);
    }
    printf("%d | ", node->value);
    if(node->right != NULL) {
        recursive_in_order_print(node->right);
    }
}

void recursive_deletion(Node *node) {
    if(node == NULL) {
        return;
    }
    if(node->left != NULL) {
        recursive_deletion(node->left);
    }
    if(node->right != NULL) {
        recursive_deletion(node->right);
    }
    free(node);
}

void destroy_tree(Tree *tree) {
    recursive_deletion(tree->root);
    free(tree);
}

void in_order_print(Tree *tree) {
    recursive_in_order_print(tree->root);
}

Node *right_rotation(Node *top) {
    Node *parent = top->parent;
    Node *new_top = top->left;
    top->left = new_top->right;

    if (new_top->right != NULL) {
        new_top->right->parent = top;
    }
    new_top->right = top;
    top->parent = new_top;
    new_top->parent = parent;

    if (parent != NULL) {
        if (parent->left == top) {
            parent->left = new_top;
        } else {
            parent->right = new_top;
        }
    }
    return new_top;
}

Node *left_rotation(Node *top) {
    Node *parent = top->parent;
    Node *new_top = top->right;
    top->right= new_top->left;

    if (new_top->left != NULL) {
        new_top->left->parent = top;
    }

    new_top->left = top;
    top->parent = new_top;
    new_top->parent = parent;

    if (parent != NULL) {
        if (parent->left == top) {
            parent->left = new_top;
        } else {
            parent->right = new_top;
        }
    }
    return new_top;
}

Node *right_left_rotation(Node *top) {
    top->right = right_rotation(top->right);
    return left_rotation(top);
}

Node *left_right_rotation(Node *top) {
    top->left = left_rotation(top->left);
    return right_rotation(top);
}

int height(Node *node) {
    if (node == NULL)
        return -1;
    else
        return node->height;
}

int left_height(Node *node) {
    if (node == NULL)
        return -1;
    else
        return height(node->left);
}

int right_height(Node *node) {
    if (node == NULL)
        return -1;
    else
        return height(node->right);
}

Node *rebalance(Node *node) {
    update_height(node);
    if (node->height == 0)
        return node;
    if (height(node->left) - height(node->right) > 1) {
        if (left_height(node->left) > right_height(node->left))
            node = right_rotation(node);
        else
            node = left_right_rotation(node);
    }
    else if (height(node->left) - height(node->right) < -1) {
        if (right_height(node->right) > left_height(node->right))
            node = left_rotation(node);
        else
            node = right_left_rotation(node);
    }
    return node;
}

int max(int a, int b) {
    if (a > b)
        return a;
    else
        return b;
}

int update_height(Node *node) {
    if(node == NULL)
        return -1;
    else
        node->height = max(update_height(node->right), update_height(node->left)) + 1;
    return node->height;
}

Node *find_value(Tree *tree, int value) {
    return recursive_find_value(tree->root, value);
}

Node *recursive_find_value(Node *node, int i) {
    if(node == NULL) {
        return NULL;
    }

    if(node->value == i) {
        return node;
    }

    if(node->value > i) {
        recursive_find_value(node->left, i);
    } else {
        recursive_find_value(node->right, i);
    }
}

Node *min_node(Node *node) {
    if(node->left == NULL)
        return node;
    return min_node(node->left);
}

Node *max_node(Node *node) {
    if(node->right == NULL)
        return node;
    return max_node(node->right);
}

void swap_value(Node *node1, Node *node2) {
    int tmp = node1->value;
    node1->value = node2->value;
    node2->value = tmp;
}


