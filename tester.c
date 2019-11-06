//
// Created by david on 11/6/2019.
//

#include <stdlib.h>
#include <stdio.h>
#include "hash.h"
#include "tester.h"
#include <time.h>

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

    insert_test(hash, array_size, array);
    find_test(hash, array_size, array);
}








