#include <pthread.h>
#include <stdbool.h>

#ifndef NARROWBRIDGE_QUEUE_H
#define NARROWBRIDGE_QUEUE_H

typedef struct Node_t {
    int carNumber;
    struct Node_t* next;
} Node;

typedef struct Queue_t {
    Node* head;
    Node* tail;
    int size;
	pthread_mutex_t mutex;
	bool isLocked;
} Queue;

void Init(Queue* queue);

void Add(Queue* queue, int carNumber);

int Top(Queue* queue);

void Pop(Queue* queue);

void LockQueue(Queue* queue);

void UnlockQueue(Queue* queue);

#endif //NARROWBRIDGE_QUEUE_H
