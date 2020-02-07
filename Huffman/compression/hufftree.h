#ifndef hufftree_h
#define hufftree_h
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "priority_queue.h"
typedef struct node{
    void *data;
    long int frequency;
    struct node *next;
    struct node *prev;
    struct node *left;
    struct node *right;
}node;
typedef struct pq pq;
int is_leaf(node *bt);

node *create_empty_node();

node *create_node(long int f);

node *create_tree_node(void *data, long int frequency, node *left, node *right);

node *merge(node *bt, node *left, node *right, pq *queue);

node *build_tree(pq *pq, node *bt);

node *create_tree_from_file(FILE *compressed, node *huff_tree);

void count_tree_size(node *bt, int *count);

void print_tree_preorder(node *bt);
#endif