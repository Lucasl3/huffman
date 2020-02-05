#include "frequency.h"

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

node *add(node *head, unsigned char data){
    if(head == NULL){
        node *new_node = create_node(1);
        *(unsigned char*)new_node->data = data;
        return new_node;
    } else{
        if(*(unsigned char*)head->data == data){
            head->frequency++;
            return head;
        }
        head->next = add(head->next, data);
        return head;
    }
}

void enqueue_pq(pq *pq, node *head){
    node *new_node = (node*) malloc(sizeof(node));
    new_node->data = head->data;
    new_node->frequency = head->frequency;
    if(pq->head == NULL || (head->frequency < pq->head->frequency)){
        new_node->next = pq->head;
        pq->head = new_node;
    } else{
        node *current = pq->head;
        while((current->next != NULL) && (current->next->frequency < head->frequency)){
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}

void enqueue_tree(node *left, node *right, node *bt, pq *queue){
    node *new_node = create_tree_node(bt->data, bt->frequency, left, right);
    // printf("Pai: %c left: %c right %c\n", new_node->data, new_node->left->data, new_node->right->data);
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