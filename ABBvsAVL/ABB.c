#include "ABB.h"

binary_tree * create_empty_tree(){
    return NULL;
}

binary_tree *create_tree(int item, binary_tree *left, binary_tree *right){
binary_tree *new_tree = (binary_tree*) malloc(sizeof(binary_tree));
new_tree->item = item;
new_tree->left = left;
new_tree->right = right;
return new_tree;
}

void print_pre_order(binary_tree *bt){
    if(bt != NULL){
        printf("%d\n", bt->item);
        print_pre_order(bt->left);
        print_pre_order(bt->right);
    }
}

int search_abb(binary_tree *bt, int item, int *comparacoes){
    if((bt == NULL) || (bt->item == item)){
        *comparacoes = *comparacoes + 1;
        return 0;
    } else if(bt->item > item){
        *comparacoes = *comparacoes + 1;
        return search_abb(bt->left, item, comparacoes);
    } else{
        *comparacoes = *comparacoes + 1;
        return search_abb(bt->right, item, comparacoes);
    }
}

binary_tree *add_abb(binary_tree *bt, int item){
    if(bt == NULL){
        bt = create_tree(item, NULL, NULL);
    } else if(bt->item > item){
        bt->left = add_abb(bt->left, item);
    } else{
        bt->right = add_abb(bt->right, item);
    }
    return bt;
}