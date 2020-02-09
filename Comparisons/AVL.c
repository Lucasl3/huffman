#include "AVL.h"
int balance_factor(binary_tree *bt){
    if(bt == NULL){
        return 0;
    }else if((bt->left != NULL) && (bt->right != NULL)){
        return (bt->left->h - bt->right->h);
    }else if((bt->left != NULL) && (bt->right == NULL)){
        return (1 + bt->left->h);
    }else{
        return (-bt->right->h - 1);
    }
}
int max(int a, int b){
    return (a > b) ? a : b;
}
int h(binary_tree *bt){
    if(bt == NULL){
        return -1;
    } else{
        return 1 + max(h(bt->left), h(bt->right));
    }
}
int is_balanced(binary_tree *bt){
    int bf = h(bt->left) - h(bt->right);
    return ((-1 <= bf) && (bf <= 1));
}
binary_tree *rotate_left(binary_tree *bt){
    binary_tree *subtree_root = NULL;
    if(bt != NULL && bt->right != NULL){
        subtree_root = bt->right;
        bt->right = subtree_root->left;
        subtree_root->left = bt;
    }
    subtree_root->h = h(subtree_root);
    bt->h = h(bt);
    return subtree_root;
}
binary_tree *rotate_right(binary_tree *bt){
    binary_tree *subtree_root = NULL;
    if(bt != NULL && bt->left != NULL){
        subtree_root = bt->left;
        bt->left = subtree_root->right;
        subtree_root->right = bt;
    }
    subtree_root->h = h(subtree_root);
    bt->h = h(bt);
    return subtree_root;
}
int search_avl(binary_tree *bt, int item, int *comparacoes){
    if((bt == NULL) || (bt->item == item)){
        *comparacoes = *comparacoes + 1;
        return 0;
    } else if(bt->item > item){
        *comparacoes = *comparacoes + 1;
        return search_avl(bt->left, item, comparacoes);
    } else{
        *comparacoes = *comparacoes + 1;
        return search_avl(bt->right, item, comparacoes);
    }
}
binary_tree *add_avl(binary_tree *bt, int item){
    if(bt == NULL){
        return create_tree(item, NULL, NULL);
    }else if(bt->item > item){
        bt->left = add_avl(bt->left, item);
    }else{
        bt->right = add_avl(bt->right, item);
    }
    bt->h = h(bt);
    binary_tree *child = NULL;
    if(balance_factor(bt) == 2 || balance_factor(bt) == -2){
        if(balance_factor(bt) == 2){
            child = bt->left;
            if(balance_factor(child) == -1){
                bt->left = rotate_left(child);
            }
            bt = rotate_right(bt);
        }else if(balance_factor(bt) == -2){
            child = bt->right;
            if(balance_factor(child) == 1){
                bt->right = rotate_right(child);
            }
            bt = rotate_left(bt);
        }
    }
    return bt;
}