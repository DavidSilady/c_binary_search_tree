#include <stdio.h>
#include "tree.h"


int main() {
    printf("Hello, World!\n");
    int input = 0;
    Tree *tree = new_tree();
    while(scanf("%d", &input) == 1) {
        insert(tree, input);
    }
    return 0;
    in_order_print(tree);
    return 0;
}