#ifndef hash_table_h
#define hash_table_h
#define HASH_SIZE 256

#include "hufftree.h"
typedef struct queue{
    node *front;
    node *rear;
}queue;
typedef struct hash_node{
    queue *fila;
    long long int frequency;
}hn;
typedef struct hash_table{
    hn *table[HASH_SIZE];
}ht;

queue *create_queue();

void enqueue(queue *queue, bool value);


void dequeue(queue *queue);

ht *create_ht();

hn *create_hn(hn *head, queue *fila, long long int frequency);

void add_hn(ht *hash, queue *fila, void *data, long long int f);

void map_bit(node *bt, ht *hash, queue *queue);

void print_ht(ht *hash);

#endif