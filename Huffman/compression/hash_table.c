#include "hash_table.h"
queue *create_queue()
{
    queue *new_node = (queue*) malloc(sizeof(node));
    new_node->front = NULL;
    new_node->rear = NULL;
    return new_node;
}

void enqueue(queue *queue, bool value)
{
    node *new_node = (node*) malloc(sizeof(node));
    void *new_data = (void*) malloc(sizeof(bool));
    *(bool*)new_data = value;
    new_node->data = new_data;
    new_node->next = NULL;
    new_node->prev = queue->rear;
    if(queue->front == NULL && queue->rear == NULL){
        queue->front = queue->rear = new_node;
    } else{
        queue->rear->next = new_node;
        queue->rear = new_node;
    }
}

void dequeue(queue *queue)
{
    node *temp = queue->rear;
    if(queue->front == NULL){
        return;
    } else{
        if(queue->front == queue->rear){
            queue->rear = queue->front = NULL;
        } else{
            queue->rear = queue->rear->prev;
            queue->rear->next = NULL;
        }
    }
}

ht *create_ht()
{
    int i;
    ht *new_ht = (ht*) malloc(sizeof(ht));
    for(i=0;i<HASH_SIZE;i++){
        new_ht->table[i] = NULL;
    }
    return new_ht;
}

hn *create_hn(hn *head, queue *fila, long long int frequency)
{
    hn *new_node = (hn*) malloc(sizeof(hn));
    new_node->fila = fila;
    new_node->frequency = frequency;
    return new_node;
}

void add_hn(ht *hash, queue *fila, void *data, long long int f){
    long int h = *(long int*)data;
    queue *new_queue = create_queue();
    node *current = fila->front;
    while(current != NULL){
        enqueue(new_queue, *(unsigned char*)current->data);
        current = current->next;
    }
    hash->table[h] = create_hn(hash->table[h], new_queue, f);
}
void map_bit(node *bt, ht *hash, queue *queue){
    if(bt->left != NULL && bt->right != NULL){
        enqueue(queue, 0);
        map_bit(bt->left, hash, queue);
        dequeue(queue);
        enqueue(queue, 1);
        map_bit(bt->right, hash, queue);
        dequeue(queue);
    } else if(bt->left == NULL && bt->right == NULL){
        add_hn(hash, queue, bt->data, bt->frequency);
    }
    return;
}

void print_ht(ht *hash){
    int i, cont = 0;
    for(i=0;i<HASH_SIZE;i++){
        if(hash->table[i] != NULL){
            cont++;
            printf("%d: ", i);
            node *current = hash->table[i]->fila->front;
            while(current != NULL){
                printf("%d->", *(unsigned char*)current->data);
                current = current->next;
            }
            printf("NULL ");
            printf("frequency: %lld\n", hash->table[i]->frequency);
        }
    }
    printf("Cont: %d\n", cont);
}
