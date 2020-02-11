#include "decompress.h"


int is_bit_i_set(unsigned char c, int i){
    unsigned char mask = 1 << i;
    return mask & c;
}

unsigned char *get_trash_and_size_tree(FILE *compressed){
    unsigned char *header = (unsigned char*) malloc(2*sizeof(unsigned char));
    unsigned char header_byte = (unsigned char)fgetc(compressed);
    header[0] = header_byte >> 5;
    unsigned char bits_from_tree = header_byte << 3;
    header[1] = bits_from_tree >> 3;
    header_byte = (unsigned char)fgetc(compressed);
    header[1] = header[1] << 8;
    header[1] = header[1] | header_byte;
    return header;

}

void decompress(char *compressed_file, FILE *compressed, node *hufftree, unsigned char *trash_and_tree_size, long long int bytes_lenght){
    strcat(compressed_file, ".huffman\0");
    FILE *decompress = fopen(compressed_file, "w");
    unsigned char vai;
    unsigned char byte = 0;
    long long int read = 0;
    bytes_lenght = (long long int)(bytes_lenght - 2 - trash_and_tree_size[1]);
    int i, j = 0;
    node *current = hufftree;
    while(read < bytes_lenght){
        fscanf(compressed, "%c", &byte);
        if(read == bytes_lenght - 1) j = trash_and_tree_size[0];
        for(i=7;i>=j;i--){ 
            if(is_bit_i_set((unsigned char)byte, i)){
                current = current->right;
            } else{
                current = current->left;
            }
            if(is_leaf(current)){
                vai = *(unsigned char*)current->data;
                fprintf(decompress, "%c", vai);
                current = hufftree;
            }
        }
        read++;
    }
    printf("Decompressed file in %s\n", compressed_file);
    printf("Successfully decompressed file\n");
    fclose(compressed);
    fclose(decompress);
}