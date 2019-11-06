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
int find_closest_value(Node *node);


Node *new_node(int value, Node *parent) {
    Node *node = malloc(sizeof(Node));
    node->left = NULL;
    node->right = NULL;
    node->parent = parent;
    node->value = value;
    node->height = 0;
    return node;
}

Tree *new_tree() {
    Tree *tree = malloc(sizeof(Tree));
    tree->size = 0;
    tree->root = NULL;
    return tree;
}

void insert(Tree *tree, int value) {
    if(tree->root == NULL) {
        tree->root = new_node(value, NULL);
       // printf("-1\n");
    } else {
        tree->root = insert_node(tree->root, value);
    }
    tree->size++;
}

Node *insert_node(Node *node, int new_value) {
    if (new_value == node->value) {
        //printf("%d\n", find_closest_value(node));
        return node;
    }
    if(new_value < node->value) {
        if(node->left == NULL) {
            node->left = new_node(new_value, node);
            //printf("%d\n", find_closest_value(node->left));
        } else {
            insert_node(node->left, new_value);
        }
    } else {
        if(node->right == NULL) {
            node->right = new_node(new_value, node);
            //printf("%d\n", find_closest_value(node->right));
        } else {
            insert_node(node->right, new_value);
        }
    }
    node = rebalance(node);
    return node;
}

void recursive_in_order_print(Node *node) {
    if(node->left != NULL) {
        recursive_in_order_print(node->left);
    }
    printf("%d | ", node->value);
    if(node->right != NULL) {
        recursive_in_order_print(node->right);
    }
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

int max_from_array(const int *array, int array_size) {
    int max = 0;
    for (int i = 0; i < array_size; ++i) {
        if (array[i] > max)
            max = array[i];
    }
    return max;
}

int closest_from_array(const int array[3], int array_size, int value) {
    int closest = array[0];
    for (int i = 0; i < array_size; ++i) {
        if (abs(value - array[i]) < abs(value - closest)) {
            closest = array[i];
        }
    }
    return closest;
}

int find_closest_value(Node *node) {
    int array[3];
    int array_size = 0;
    if (node->parent != NULL) {
        array[array_size] = node->parent->value;
        array_size++;
    }
    if (node->left != NULL) {
        array[array_size] = max_node(node->left)->value;
        array_size++;
    }
    if (node->right != NULL) {
        array[array_size] = min_node(node->right)->value;
        array_size++;
    }
    if (array_size == 0) {
        return -1;
    }
    return closest_from_array(array, array_size, node->value);
}

Node *find_value(Tree *tree, int value) {
    return recursive_find_value(tree->root, value);
}

Node *recursive_find_value(Node *node, int i) {
    if(node->value == i) {
        return node;
    }

    if(i < node->value) {
        if(node->left == NULL) {
            return NULL;
        } else {
            recursive_find_value(node->left, i);
        }
    } else {
        if(node->right == NULL) {
            return NULL;
        } else {
            recursive_find_value(node->right, i);
        }
    }

    return NULL;
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

void delete_note(Node *node) {

    Node *parent = node->parent;
    if (parent != NULL) {
        if (parent->left == node) {
            parent->left = NULL;
        } else {
            parent->right = NULL;
        }
    }

    return free(node);
}

void remove_node(Node *node) {
    if (node->right == NULL && node->left == NULL) {
        delete_note(node);
        return;
    }
    if (node->right != NULL) {
        Node *min = min_node(node->right);
        swap_value(node, min);
        remove_node(min);
        return;
    }
    if (node->left != NULL) {
        Node *max = max_node(node->left);
        swap_value(node, max);
        remove_node(max);
        return;
    }
}


