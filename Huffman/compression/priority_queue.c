#include "priority_queue.h"

struct priority_queue{
    node *head;
};
pq *create_pq(){
    pq *new_pq = (pq*) malloc(sizeof(pq));
    new_pq->head = NULL;
    return new_pq;
}

node *create_node(long int f){
    node *new_node = (node*) malloc(sizeof(node));
    void *new_data = (void*) malloc(2 * sizeof(unsigned char));
    *(unsigned char*)new_data = '*';
    new_node->data = new_data;
    new_node->frequency = f;
    new_node->next = NULL;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

void enqueue_pq(pq *pq, node *n){
    node *new_node = (node*) malloc(sizeof(node));
    new_node->data = n->data;
    new_node->frequency = n->frequency;
    if(pq->head == NULL || (n->frequency < pq->head->frequency)){
        new_node->next = pq->head;
        pq->head = new_node;
    } else{
        node *current = pq->head;
        while((current->next != NULL) && (current->next->frequency < n->frequency)){
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}

void enqueue_tree(node *left, node *right, node *bt, pq *queue){
    node *new_node = create_tree_node(bt->data, bt->frequency, left, right);
    if(queue->head == NULL || (bt->frequency < queue->head->frequency)){
        new_node->next = queue->head;
        queue->head = new_node;
    } else if(bt->frequency == queue->head->frequency){
        if(*(unsigned char*)bt->data == '*'){
            new_node->next = queue->head;
            queue->head = new_node;
        }
    }
    else{
        node *current = queue->head;
        while((current->next != NULL) && (current->next->frequency < bt->frequency)){
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}

node *dequeue_pq(pq *queue){
    if(queue->head != NULL){
        node *current = queue->head;
        queue->head = queue->head->next;
        return current;
    } else{
        return NULL;
    }
}

void print_list(node *head){
    node *current = head;
    while(current != NULL){
        printf("Data: %c Frequency: %ld\n", *(unsigned char*)current->data, current->frequency);
        current = current->next;
    }
}

void print_pq(pq *pq){
    node *current = pq->head;
    while(current != NULL){
        printf("Data: %c Frequency: %ld\n", *(unsigned char*)current->data, current->frequency);
        current = current->next;
    }
}