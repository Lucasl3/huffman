#include "readfile.h"

FILE *open_file(char *name, char *mode){
    FILE *file = fopen(name, mode);
    if(!file){
        fprintf(stderr, "Unable to pen file: %s\n", name);
    }
    return file;
}
long long int get_file_length(FILE *file){
    fseek(file, 0, SEEK_END);
    long long int length = ftell(file);
    rewind(file);
    return length;
}

int get_file_name_length(char *file_name){
    int i, lenght = 0;
    for(i=0; file_name[i]!= '\0';i++){
        ++lenght;
    }
    return lenght;
}