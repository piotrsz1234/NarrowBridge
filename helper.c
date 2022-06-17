#include "helper.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

char* lastMessage = NULL;

void DisplaySimplifiedCurrentStatus(Car* cars, int n) {
	int carsToA = 0, carsInA = 0, numberOfCarOnBridge = -1, directionOfCarOnBridge = 0, carsToB = 0, carsInB = 0;
	for (int i = 0; i < n; i++) {
		if (cars[i].onBridge) {
			numberOfCarOnBridge = cars[i].number;
			directionOfCarOnBridge = cars[i].status;
		} else if (cars[i].status == IN_CITY_A) {
			carsInA++;
		} else if (cars[i].status == IN_QUEUE_TO_CITY_A) {
			carsToA++;
		} else if (cars[i].status == IN_CITY_B) {
			carsInB++;
		} else if (cars[i].status == IN_QUEUE_TO_CITY_B) {
			carsToB++;
		}
	}
	char* carDirectionSymbol = directionOfCarOnBridge == ON_BRIDGE_TO_CITY_A ? "<<" : ">>";
	char* message = malloc(sizeof(char) * 1000);
	if (numberOfCarOnBridge != -1) {
		sprintf(message, "A-%d %d>>> [%s %d %s] <<<%d %d-B\n", carsInA, carsToB, carDirectionSymbol,
		        numberOfCarOnBridge, carDirectionSymbol, carsToA, carsInB);
	} else {
		sprintf(message, "A-%d %d>>> [] <<<%d %d-B\n", carsInA, carsToB, carsToA, carsInB);
	}
	
	if (lastMessage != NULL && strcmp(message, lastMessage) != 0) {
		free(lastMessage);
		lastMessage = message;
		printf(message);
	} else if (lastMessage == NULL) {
		lastMessage = message;
		printf(message);
	}
}

char* GetQueueToCity(Queue* queue, int direction, Car* cars) {
	char* result = malloc(sizeof(char) * 1000);
	sprintf(result, " ");
	Node* temp = queue->head;
	int writenIn = 0;
	while (temp != NULL) {
		if (cars[temp->carNumber].status == direction) {
			sprintf(result, "%s%d ", result, temp->carNumber);
		}
		temp = temp->next;
	}
	
	return result;
}

void DisplayDetailedCurrentStatus(Car* cars, int n, Queue* queue) {
	int carsInA = 0, numberOfCarOnBridge = -1, directionOfCarOnBridge = 0, carsInB = 0;
	for (int i = 0; i < n; i++) {
		if (cars[i].onBridge) {
			numberOfCarOnBridge = cars[i].number;
			directionOfCarOnBridge = cars[i].status;
		} else if (cars[i].status == IN_CITY_A)
			carsInA++;
		else if (cars[i].status == IN_CITY_B)
			carsInB++;
	}
	char* queueToB = GetQueueToCity(queue, IN_QUEUE_TO_CITY_B, cars);
	char* queueToA = GetQueueToCity(queue, IN_QUEUE_TO_CITY_A, cars);
	char* carDirectionSymbol = directionOfCarOnBridge == ON_BRIDGE_TO_CITY_A ? "<<" : ">>";
	char* message = malloc(sizeof(char) * 1000);
	
	if (numberOfCarOnBridge != -1) {
		sprintf(message, "A-%d %s>>> [%s %d %s] <<<%s %d-B\n", carsInA, queueToB, carDirectionSymbol, numberOfCarOnBridge,
		       carDirectionSymbol, queueToA, carsInB);
	} else {
		sprintf(message, "A-%d %s>>> [] <<<%s %d-B\n", carsInA, queueToB, queueToA, carsInB);
	}
	
	if (lastMessage != NULL && strcmp(message, lastMessage) != 0) {
		free(lastMessage);
		lastMessage = message;
		printf(message);
	} else if (lastMessage == NULL) {
		lastMessage = message;
		printf(message);
	}
	
	free(queueToA);
	free(queueToB);
}

void DisplayCurrentStatus(Car* cars, int n, Queue* queue, bool debug) {
	LockQueue(queue);
	if (!debug) {
		DisplaySimplifiedCurrentStatus(cars, n);
	} else {
		DisplayDetailedCurrentStatus(cars, n, queue);
	}
	UnlockQueue(queue);
}

int RandomTime() {
	return 1;
	//return 200 + rand() % 501;
}

bool AnyOnBridge(Car* cars, int n) {
	for (int i = 0; i < n; i++) {
		if (cars[i].onBridge) return true;
	}
	
	return false;
}