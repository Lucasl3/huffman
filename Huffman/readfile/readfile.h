#ifndef readfile_h
#define readfile_h
#include "../compression/hufftree.h"

FILE *open_file(char *name, char *mode);

long long int get_file_length(FILE *file);

int get_file_name_length(char* fileName);

#endif