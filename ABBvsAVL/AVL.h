#ifndef AVL_H
#define AVL_H

#include "ABB.h"

int balance_factor(binary_tree *bt);

int max(int a, int b);

int h(binary_tree *bt);

int is_balanced(binary_tree *bt);

binary_tree *rotate_left(binary_tree *bt);

binary_tree *rotate_right(binary_tree *bt);

int search_avl(binary_tree *bt, int item, int *comparacoes);

binary_tree *add_avl(binary_tree *bt, int item);

#endif