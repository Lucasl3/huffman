#include "compression/hufftree.h"
#include "compression/compress.h"
#include "compression/hash_table.h"
#include "compression/frequency.h"
#include "compression/header.h"
int main(){
    unsigned char element;
    int i;
    FILE *file = fopen("texto.txt", "r");
    node *list = NULL;
    while(fscanf(file, "%c", &element) != EOF){
        // printf("Ascii: %d ", element);
        // printf("Caractere: %c\n", element);
        list = add(list, element);
    }
    pq *pq = create_pq();
    node *current = list;
    while(current != NULL){
        enqueue_pq(pq, current);
        current = current->next;
    }
    node *bt = create_empty_node();
    bt = build_tree(pq, bt);
    queue *queue = create_queue();
    ht *hash_table = create_ht();
    map_bit(bt, hash_table, queue);
    rewind(file);
    int treesize = 0;
    count_tree_size(bt, &treesize);
    create_header(trash_size(hash_table), treesize);
    compress(file, hash_table, bt);
    FILE *compressed = fopen("compressed.txt", "r");
    long long int bytes_length = get_file_length(compressed);
    unsigned char *trash_and_size_tree = get_trash_and_size_tree(compressed);
    node *hufftree = NULL;
    hufftree = create_tree_from_file(compressed, hufftree);
    print_ht(hash_table);
    return 0;
}