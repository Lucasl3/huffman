#ifndef header_h
#define header_h
#include <stdio.h>
#include "hufftree.h"
#include "hash_table.h"
unsigned char trash;
unsigned char size_tree;
int trash_size(ht *hash);

void print_tree_on_file(FILE *file, node *bt);

void create_header(int trash_size, int tree_size);

#endif