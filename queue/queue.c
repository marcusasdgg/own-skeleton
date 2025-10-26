#include "../circular_queue.h"

// if tail and head are equal it means there are 0 elements

void initialise_Queue(struct Queue* q){
    q->tail_index = 0;
    q->head_index = 0;
    q->num_elements = 0;

    for (int i = 0 ; i < QUEUE_SIZE; i++){
        q->arr[i] = 0;
    }
}

// check if tail index is at the end if it is and the queue is also full
// i.e. num_elements = QUEUE_SIZE 
// then we do nothing
// else we wrap the tail index back to the start.
void emplace_Queue(struct Queue* q, unsigned char value){
    // add no more bitch
    if (q->num_elements == QUEUE_SIZE)
        return;
    q->arr[q->tail_index++] = value;
    q->tail_index = q->tail_index % QUEUE_SIZE;
    q->num_elements++;
}

unsigned char peek_Queue(struct Queue* q){
    if (q->num_elements == 0){
        return 0; // we maybe want to call an excpetion here or something in the future.
    }
    return q->arr[q->head_index];
}

unsigned char pop_Queue(struct Queue* q){
    if (q->num_elements == 0)
        return 0; // call an interrupt?
    unsigned char c = q->arr[q->head_index];
    q->head_index++;
    q->head_index = q->head_index % QUEUE_SIZE;
    q->num_elements--;
    return c;
}

int isempty_Queue(struct Queue* q){
    return q->num_elements == 0;
}