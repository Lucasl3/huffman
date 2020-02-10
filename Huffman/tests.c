#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
#include "./compression/hufftree.h"
#include "./compression/hash_table.h"
#include "./compression/priority_queue.h"

pq *priority_queue = NULL;
node *bt = NULL;
ht *hash = NULL;
queue *fila = NULL;
const char tree_string[11] = "**CB***FEDA";

int init_suite(void){
    return 0;
}
int clean_suite(void){
    return 0;
}

int get_leaves_quantity(node *tree){
    if(tree){
        if(is_leaf(tree)){
            return 1;
        }
        return get_leaves_quantity(tree->left) + get_leaves_quantity(tree->right);
    }
    return 0;
}

void compare_tree(node *tree, long long int *pos){
    if(tree){
        CU_ASSERT_EQUAL(tree_string[*pos], tree->data);
        *pos = *pos + 1;
        compare_tree(tree->left, pos);
        compare_tree(tree->right, pos);
    }
}
node *frequency(char letra, int frequency){
    node *n = (node*)malloc(sizeof(node));
    void *new_data = (void*) malloc(2 * sizeof(unsigned char));
    *(unsigned char*)new_data = letra;
    n->frequency = frequency;
    n->data = new_data;
}
void test_priority_queue(){
    CU_ASSERT_PTR_NULL(priority_queue);
    priority_queue = create_pq();
    CU_ASSERT_PTR_NOT_NULL(priority_queue);

    node *n = frequency('A', 6);
    enqueue_pq(priority_queue, n);
    CU_ASSERT_PTR_NOT_NULL(priority_queue->head);
    CU_ASSERT_EQUAL(priority_queue->head->frequency, n->frequency);
    n = frequency('B', 5);
    enqueue_pq(priority_queue, n);
    CU_ASSERT_PTR_NOT_NULL(priority_queue->head);
    CU_ASSERT_EQUAL(priority_queue->head->frequency, n->frequency);
    n = frequency('C', 4);
    enqueue_pq(priority_queue, n);
    CU_ASSERT_PTR_NOT_NULL(priority_queue->head);
    CU_ASSERT_EQUAL(priority_queue->head->frequency, n->frequency);
    n = frequency('D', 3);
    enqueue_pq(priority_queue, n);
    CU_ASSERT_PTR_NOT_NULL(priority_queue->head);
    CU_ASSERT_EQUAL(priority_queue->head->frequency, n->frequency);
    n = frequency('E', 2);
    enqueue_pq(priority_queue, n);
    CU_ASSERT_PTR_NOT_NULL(priority_queue->head);
    CU_ASSERT_EQUAL(priority_queue->head->frequency, n->frequency);
    n = frequency('F', 1);
    enqueue_pq(priority_queue, n);
    CU_ASSERT_PTR_NOT_NULL(priority_queue->head);
    CU_ASSERT_EQUAL(priority_queue->head->frequency, n->frequency);
}
void test_huff_tree(){
    CU_ASSERT_PTR_NULL(bt);
    bt = build_tree(priority_queue, bt);
    CU_ASSERT_PTR_NOT_NULL(bt);
    CU_ASSERT_EQUAL(*(unsigned char*)bt->data, '*');
    CU_ASSERT_EQUAL(*(unsigned char*)bt->left->data, '*');
    CU_ASSERT_EQUAL(*(unsigned char*)bt->left->left->data, 'C');
    CU_ASSERT_EQUAL(*(unsigned char*)bt->left->right->data, 'B');
    CU_ASSERT_EQUAL(*(unsigned char*)bt->right->data, '*');
    CU_ASSERT_EQUAL(*(unsigned char*)bt->right->left->data, '*');
    CU_ASSERT_EQUAL(*(unsigned char*)bt->right->left->left->data, '*');
    CU_ASSERT_EQUAL(*(unsigned char*)bt->right->right->data, 'A');
    CU_ASSERT_EQUAL(*(unsigned char*)bt->right->left->right->data, 'D');
    CU_ASSERT_EQUAL(*(unsigned char*)bt->right->left->left->left->data, 'F');
    CU_ASSERT_EQUAL(*(unsigned char*)bt->right->left->left->right->data, 'E');

}
void test_hash_table(){
    CU_ASSERT_PTR_NULL(hash);
    hash = create_ht();
    CU_ASSERT_PTR_NOT_NULL(hash);
    CU_ASSERT_PTR_NULL(fila);
    fila = create_queue();
    CU_ASSERT_PTR_NOT_NULL(fila);
    map_bit(bt, hash, fila);
    CU_ASSERT_EQUAL(hash->table['A']->frequency, 6);
    CU_ASSERT_EQUAL(hash->table['B']->frequency, 5);
    CU_ASSERT_EQUAL(hash->table['C']->frequency, 4);
    CU_ASSERT_EQUAL(hash->table['D']->frequency, 3);
    CU_ASSERT_EQUAL(hash->table['E']->frequency, 2);
    CU_ASSERT_EQUAL(hash->table['F']->frequency, 1);
}
int main(){
    CU_pSuite pSuite = NULL;
    if(CUE_SUCCESS != CU_initialize_registry()){
        return CU_get_error();
    }
    pSuite = CU_add_suite("Testando tudo",0,0);
    if(pSuite == NULL){
        CU_cleanup_registry();
        return CU_get_error();
    }
    CU_add_test(pSuite, "Test priority queue", test_priority_queue);
    if(pSuite == NULL){
        CU_cleanup_registry();
        return CU_get_error();
    }
    CU_add_test(pSuite, "Test huff tree", test_huff_tree);
    if(pSuite == NULL){
        CU_cleanup_registry();
        return CU_get_error();
    }
    CU_add_test(pSuite, "Test hash table", test_hash_table);
    if(pSuite == NULL){
        CU_cleanup_registry();
        return CU_get_error();
    }
    CU_basic_run_tests();
    return CU_get_error();
}