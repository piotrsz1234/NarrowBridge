#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

void Init(Queue* queue) {
    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;
}

void Add(Queue* queue, int carNumber) {
    Node* node = malloc(sizeof(Node));
    node->next = NULL;
    node->carNumber = carNumber;
    if(queue->head != NULL) {
        Node* temp = queue->tail;
        queue->tail = node;
        temp->next = node;
    } else {
        queue->head = queue->tail = node;
    }
    queue->size++;
}

int Top(Queue* queue) {
    return queue->tail->carNumber;
}

int Pop(Queue* queue) {
    int result = Top(queue);
	Node* toRemove = queue->head;
	
	queue->head = queue->head->next;
	queue->size--;
	free(toRemove);
	
	return result;
}