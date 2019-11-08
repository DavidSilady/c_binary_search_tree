//
// Created by david on 11/6/2019.
//

#include <stdlib.h>
#include <stdio.h>
#include "hash.h"
#include "tester.h"
#include <time.h>
#include "github_src/stolen_tree/rbtree.c"
#include "github_src/stolen_hash/hashtab.c"

int *read_input(char file_name[49], int input_size) {
    int *input = malloc(input_size * sizeof(int));
    FILE *file;
    file = fopen(file_name, "r");

    for (int i = 0; i < input_size; ++i) {
        fscanf(file, "%d", &input[i]);
    }

    fclose(file);
    return input;
}

void insert_test(Hash *hash, int array_size, int *array) {
    clock_t start, end;
    double time_elapsed;

    start = clock();

    for (int i = 0; i < array_size; ++i) {
        hash_add(hash, array[i]);
        printf("| Inserted %d |\n", array[i]);
    }

    end = clock();
    time_elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time elapsed: %lf\n", time_elapsed);
}

void find_test(Hash *hash, int array_size, int *array) {
    clock_t start, end;
    double time_elapsed;

    start = clock();

    for (int i = 0; i < array_size; ++i) {
        Node *node = hash_find(hash, array[i]);
        if(node != NULL) {
            //printf("| Found %d |\n", node->value);
        }
    }

    end = clock();
    time_elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time elapsed: %lf\n", time_elapsed);
}

void small_test() {
    const int array_size = 10000;
    int *array = read_input("C:\\Users\\david\\CLionProjects\\trees\\test1.txt", array_size);
    Hash *hash = new_hash(100);
    //insert_test(hash, array_size, array);
    //find_test(hash, array_size, array);

    rbtree rb_tree = rbtree_create();
    for (int i = 0; i < array_size; ++i) {
        rbtree_insert(rb_tree, (void *)&array[i], compare_int);
        //printf("| Inserted %d |\n", array[i]);
    }

    hashtab_t *hash_tab = ht_init(16, NULL);
    for (int i = 0; i < array_size; ++i) {
        ht_insert(hash_tab, &array[i], sizeof(int), &array[i], sizeof(int));
    }

}








