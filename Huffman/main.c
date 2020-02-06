#include "./compression/hufftree.h"
#include "./compression/compress.h"
#include "./compression/hash_table.h"
#include "./compression/frequency.h"
#include "./compression/header.h"
#include "./decompression/decompress.h"
int main(){
    unsigned char element;
    int i, frequency[256] = {0}, h;
    FILE *file = fopen("imagem.txt", "r");
    node *list = NULL;
    while(fscanf(file, "%c", &element) != EOF){
        // printf("Ascii: %d ", element);
        // printf("Caractere: %c\n", element);
        frequency[element]++;
        // list = add(list, element);
    }
    pq *pq = create_pq();
    node *current = list;
    for(i=0;i<256;i++){
        if(frequency[i] != 0){
            node *n = (node*)malloc(sizeof(node));
            void *new_data = (void*) malloc(2 * sizeof(unsigned char));
            *(unsigned char*)new_data = i;
            n->frequency = frequency[i];
            n->data = new_data;
            enqueue_pq(pq, n);
        }
    }
    node *bt = create_empty_node();
    bt = build_tree(pq, bt);
    queue *queue = create_queue();
    ht *hash_table = create_ht();
    // print_tree_preorder(bt);
    map_bit(bt, hash_table, queue);
    rewind(file);
    int treesize = 0;
    count_tree_size(bt, &treesize);
    create_header(trash_size(hash_table), treesize);
    print_ht(hash_table);
    compress(file, hash_table, bt);
    FILE *compressed = fopen("compressed.txt", "r");
    long long int bytes_length = get_file_length(compressed);
    unsigned char *trash_and_size_tree = get_trash_and_size_tree(compressed);
    node *hufftree = NULL;
    int size = trash_and_size_tree[1];
    hufftree = create_tree_from_file(compressed, hufftree);
    decompress(compressed, hufftree, trash_and_size_tree, bytes_length);
    print_tree_preorder(hufftree);
    printf("%d\n", trash_and_size_tree[1]);
    return 0;
}