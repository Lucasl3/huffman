#include "header.h"
int trash_size(ht *hash){
    long long int sum, trash = 0;
    int i;
    for(i=0;i<HASH_SIZE;i++){
        if(hash->table[i] != NULL){
            sum = 0;
            node *current = hash->table[i]->fila->front;
            while(current != NULL){
                sum++;
                current = current->next;
            }
            trash += sum * hash->table[i]->frequency;
        }
    }
    return 8 - (trash % 8);
}

void print_tree_on_file(FILE *file, node *bt){
    if(bt != NULL){
        if(is_leaf(bt)){
            if(*(unsigned char*)bt->data == '*' || *(unsigned char*)bt->data == '\\'){
                fprintf(file, "%c", '\\');
            }
        }
        fprintf(file, "%c", *(unsigned char*)bt->data);
        print_tree_on_file(file, bt->left);
        print_tree_on_file(file, bt->right);
    }
}

void create_header(int trash_size, int tree_size){
    trash = (unsigned char)(trash_size << 5) | (tree_size >> 8);
    size_tree = (unsigned char)tree_size;
}