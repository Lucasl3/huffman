#include "hufftree.h"
#include "priority_queue.h"
#include "hash_table.h"
#include "header.h"
#include "compress.h"

void compress(FILE *file, ht *hash, node *bt, char *file_path){
    unsigned char element;
    int i;
    printf("Starting compression\n\n");
    strcat(file_path, ".huff\0");
    FILE *compressed = fopen(file_path, "wb");
    fprintf(compressed, "%c%c", trash, size_tree);
    print_tree_on_file(compressed, bt);
    unsigned int byte = 0;
    short byte_size = 0;
    unsigned char buffer;
    while(fscanf(file, "%c", &buffer) != EOF){
        node *current = hash->table[buffer]->fila->front;
        // printf("Ascii: %d ", buffer);
        // printf("Caractere: %c\n", buffer);
        while(current != NULL){
            byte_size++;
            byte = byte << 1;
            if(*(unsigned char*)current->data == 1){
                byte = byte | 1;
            }
            if(byte_size == 8){
            // printf(" ");
            unsigned char aux = byte;
            byte_size = 0;
            fprintf(compressed, "%c", aux);
            }
            current = current->next;
        }
    }
    // printf("\n");
    if(byte_size > 0){
        byte = byte << (8 - byte_size);
        unsigned char aux = byte;
        fprintf(compressed, "%c", aux);
    }
    printf("Compressed file in %s\n", file_path);
    printf("Successfully compressed file\n");
    fclose(file);
    fclose(compressed);
}