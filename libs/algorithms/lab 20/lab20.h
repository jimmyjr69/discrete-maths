//
// Created by yaros on 25.05.2024.
//

#ifndef UNTITLED1_LAB20_H
#define UNTITLED1_LAB20_H

#include <stdio.h>

typedef struct domain {
    int visits_number;
    char *name;
} domain;

typedef struct prefix {
    int size;
    int begin_index;
    int end_index;
} prefix;

int** task_1(int n, int query[][4], size_t size);

void test_task_1();

int count_living_neighboring_cells(int m, int n, int board[n][m], int i, int j);

void task_2(int m, int n, int board[n][m]);

void test_task_2();

void get_median(int filter, int matrix[filter][filter], int i, int j);

void task_3(int filter, int matrix[filter][filter]);

void test_task_3();

void task_4(char **cpdomains, int size);

void test_task_4();

void fill_matrix(matrix m, matrix *new_matrix, int rows, int cols);

int task_5(matrix m, int rows, int cols);

void test_task_5();

void task_6(char *string, int len, char *result, int *result_len);

void test_task_6();

void get_new_node(int *nums, int size, prefix pref);

void task_7(int *nums, int size);

void test_task_7();

void task_8(char *s, int *indices, char *result, int size);

void test_task_8();

void fill_file(int *numbers, int size, char *file_name);

void task_9(int *numbers, int size, int n, char *file_name_1, char *file_name_2);

void test_task_9(int argc, char **argv);

void handler();

void task_10(char *file_name, int n);

void fill_file_2(char **strings, int size, char *file_name);

void test_task_10(int argc, char **argv);

bool is_prefix(char *string, char *prefix);

void task_11();

void test_task_11();

#endif //UNTITLED1_LAB20_H
