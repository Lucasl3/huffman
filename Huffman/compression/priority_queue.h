#ifndef priority_queue_h
#define priority_queue_h
#include "hufftree.h"
typedef struct node node;
typedef struct pq{
    node *head;
}pq;

pq *create_pq(); 

node *create_node(long int f);

node *add(node *head, unsigned char data);

void enqueue_pq(pq *pq, node *n);

void enqueue_tree(node *left, node *right, node *bt, pq *queue);

node *dequeue_pq(pq *queue);

void print_list(node *head);

void print_pq(pq *pq);

#endif