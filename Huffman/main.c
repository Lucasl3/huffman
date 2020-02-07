#include "./compression/hufftree.h"
#include "./compression/compress.h"
#include "./compression/hash_table.h"
#include "./compression/priority_queue.h"
#include "./compression/header.h"
#include "./decompression/decompress.h"
#include "./readfile/readfile.h"

void start_compression(char *file_path){
    unsigned char element;
    int i, frequency[256] = {0}, h;
    FILE *file = fopen(file_path, "r");
    while(fscanf(file, "%c", &element) != EOF){
        frequency[element]++;
    }
    pq *pq = create_pq();
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
    map_bit(bt, hash_table, queue);
    rewind(file);
    int treesize = 0;
    count_tree_size(bt, &treesize);
    create_header(trash_size(hash_table), treesize);
    print_ht(hash_table);
    compress(file, hash_table, bt, file_path);
}
int main(){
    int option;
    while(1){
        printf("Select one option: \n");
        printf("[1] Compress\n");
        printf("[2] Decompress\n");
        printf("[3] Exit\n");
        scanf("%d", &option);
        if(option == 1){
            char file[100];
            printf("Digite o nome do arquivo: ");
            scanf("%s", file);
            printf("\n");
            start_compression(file);
        } else if(option == 2){
            char file[100];
            printf("Digite o nome do arquivo: ");
            scanf("%s", file);
            printf("\n");
            
        } else{
            printf("System shutdown\n");
            return 0;
        }
        
    }
    FILE *compressed = fopen("compressed.txt", "r");
    long long int bytes_length = get_file_length(compressed);
    unsigned char *trash_and_size_tree = get_trash_and_size_tree(compressed);
    node *hufftree = NULL;
    hufftree = create_tree_from_file(compressed, hufftree);
    decompress(compressed, hufftree, trash_and_size_tree, bytes_length);
    print_tree_preorder(hufftree);
    printf("%d\n", trash_and_size_tree[1]);
    return 0;
}