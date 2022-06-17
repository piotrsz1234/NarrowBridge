#include "queue.h"
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

void Init(Queue* queue) {
    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;
	queue->isLocked = false;
	pthread_mutex_init(&(queue->mutex), NULL);
}

void Add(Queue* queue, int carNumber) {
	if(queue->isLocked == false) {
		pthread_mutex_lock(&(queue->mutex));
	}
	
    Node* node = malloc(sizeof(Node));
    node->next = NULL;
    node->carNumber = carNumber;
	
    if(queue->head != NULL) {
        queue->tail->next = node;
        queue->tail = node;
    } else {
        queue->head = queue->tail = node;
    }
    queue->size++;
	
	if(queue->isLocked == false) {
		pthread_mutex_unlock(&(queue->mutex));
	}
}

int Top(Queue* queue) {
	if(!queue->isLocked) {
		pthread_mutex_lock(&(queue->mutex));
	}
	
	if(queue->head == NULL) {
		return -1;
	}
	
	if(!queue->isLocked) {
		pthread_mutex_unlock(&(queue->mutex));
	}
	
    return queue->head->carNumber;
}

void Pop(Queue* queue) {
	if(!queue->isLocked) {
		pthread_mutex_lock(&(queue->mutex));
	}
	
	if(queue->head == NULL) {
		queue->tail = NULL;
		return;
	}
	
	Node* toRemove = queue->head;
	
	queue->head = queue->head->next;
	queue->size--;
	free(toRemove);
	
	if(!queue->isLocked) {
		pthread_mutex_unlock(&(queue->mutex));
	}
}

void LockQueue(Queue* queue) {
	pthread_mutex_lock(&(queue->mutex));
	queue->isLocked = true;
}

void UnlockQueue(Queue* queue) {
	pthread_mutex_unlock(&(queue->mutex));
	queue->isLocked = false;
}