#ifndef decompress_h
#define decompress_h
#include "../compression/hufftree.h"

long long int get_file_length(FILE *file);

int is_bit_i_set(unsigned char c, int i);

unsigned char *get_trash_and_size_tree(FILE *compressed);

void decompress(FILE *compressed, node *hufftree, unsigned char *trash_and_tree_size, long long int bytes_lenght);

#endif