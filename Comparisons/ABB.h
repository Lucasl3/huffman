#ifndef ABB_H
#define ABB_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
typedef struct binary_tree{
    int item;
    int h;
    struct binary_tree *left;
    struct binary_tree *right;
}binary_tree;

binary_tree * create_empty_tree();

binary_tree *create_tree(int item, binary_tree *left, binary_tree *right);

void print_pre_order(binary_tree *bt);

int search_abb(binary_tree *bt, int item, int *comparacoes);

binary_tree *add_abb(binary_tree *bt, int item);

#endif