#include <stdio.h>
#include <stdlib.h>

typedef struct queue_node {
    int val;                   // Informação do nó
    struct queue_node* next;   // Próximo elemento
} QueueNode;

typedef struct {
    QueueNode* head;   // Primeiro elemento da fila
} Queue;

// Cria uma fila
Queue* new_queue(){
    Queue* new = (Queue*) malloc(sizeof(Queue));
    new->head = NULL;
    return new;
}

// Cria um nó da fila
QueueNode* new_QueueNode(int val){
    QueueNode* new = (QueueNode*) malloc( sizeof(QueueNode) );
    new->val = val;
    new->next = NULL;
    return new;
}

// Insere no final da fila
void push_queue(Queue* queue, int val){

    if( !queue->head ){
        queue->head = new_QueueNode(val);
        return;
    }

    QueueNode* node = queue->head;

    while ( node->next )
        node = node->next;
    
    node->next = new_QueueNode(val);

}

// Remove e retorna o primeiro elemento da fila
int pop_queue(Queue* queue){

    if ( !queue )
        return -1;

    QueueNode* head = queue->head;

    queue->head = head->next;

    int val = head->val;

    free(head);

    return val;
}

// Retorna 0 se a fila estiver vazia e 1 caso contrário
int is_empty_queue(Queue* queue){

    if( queue->head )
        return 1;

    return 0;
}
