#include "frequency.h"
#include "hufftree.h"
int is_leaf(node *bt){
    return (bt->left == NULL && bt->right == NULL);
}

node *create_empty_node(){
    return NULL;
}

node *create_tree_node(void *data, long int frequency, node *left, node *right){
    node *new_node = (node*) malloc(sizeof(node));
    new_node->data = data;
    new_node->frequency = frequency;
    new_node->left = left;
    new_node->right = right;
    return new_node;
}

node *merge(node *bt, node *left, node *right, pq *queue){
    bt = create_node(left->frequency + right->frequency);
    // printf("Left, data: %c freque: %ld\n", left->data, left->frequency);
    // printf("right, data: %c freque: %ld\n\n", right->data, right->frequency);
    bt->left = left;
    bt->right = right;
    enqueue_tree(bt->left, bt->right, bt, queue);
    return bt;
}

node *build_tree(pq *pq, node *bt){
    while(pq->head->next != NULL){
        node *first = dequeue_pq(pq);
        node *second = dequeue_pq(pq);
        bt = merge(bt, first, second, pq);
    }
    return bt;
}

node *create_tree_from_file(FILE *compressed, node *huff_tree){
    // if(size < 0) return huff_tree;
    unsigned char character;
    fscanf(compressed, "%c", &character);
    void *data = (void*) malloc(sizeof(void));
    unsigned char *aux = (unsigned char*) malloc(sizeof(unsigned char));
    *aux = character;
    data = (void*) aux;
    if(character == '*'){
        huff_tree = create_tree_node(data, 0, NULL, NULL);
        huff_tree->left = create_tree_from_file(compressed, huff_tree->left);
        huff_tree->right = create_tree_from_file(compressed, huff_tree->right);
    } else{
        if(character == 92){
            fscanf(compressed, "%c", &character);
            huff_tree = create_tree_node(data, 0, NULL, NULL);
        } else{
            huff_tree = create_tree_node(data, 0, NULL, NULL);
        }
    }
    return huff_tree;
}

void count_tree_size(node *bt, int *count){
    if(bt != NULL)
    {   if(is_leaf(bt)){
        if(*(unsigned char*)bt->data == '*' || *(unsigned char*)bt->data == '\\'){
            *count = *count + 1;    
        }
    }
    *count = *count + 1;
    count_tree_size(bt->left, count);
    count_tree_size(bt->right, count);
    }
}

void print_tree_preorder(node *bt){
    //printf("chego\n");
    if(bt!=NULL){
        // printf("entro\n");
        printf("Data: %c\n", *(unsigned char*)bt->data);
        print_tree_preorder(bt->left);
        print_tree_preorder(bt->right);
    }
}