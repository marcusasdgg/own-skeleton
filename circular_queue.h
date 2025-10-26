#include <stddef.h>
#include <stdint.h>

#define QUEUE_SIZE 500
// simple byte circular queue for FIFO action!.
struct Queue {
    size_t tail_index;
    size_t head_index;
    size_t num_elements;
    unsigned char arr[QUEUE_SIZE];
};

void initialise_Queue(struct Queue* q);

unsigned char pop_Queue(struct Queue* q);

void emplace_Queue(struct Queue* q, unsigned char value);

unsigned char peek_Queue(struct Queue* q);

int isempty_Queue(struct Queue* q);

