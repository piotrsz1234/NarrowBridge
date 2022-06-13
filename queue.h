
#ifndef NARROWBRIDGE_QUEUE_H
#define NARROWBRIDGE_QUEUE_H

typedef struct Node_t {
    int carNumber;
    struct Node_t* next;
} Node;

typedef struct Queue_t {
    Node* head;
    int size;
} Queue;

void Init(Queue* queue);

void Add(Queue* queue, int carNumber);

int Top(Queue* queue);

int Pop(Queue* queue);

#endif //NARROWBRIDGE_QUEUE_H
