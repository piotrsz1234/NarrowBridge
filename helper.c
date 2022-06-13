#include "helper.h"
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

pthread_mutex_t outputMutex = PTHREAD_MUTEX_INITIALIZER;

void DisplaySimplifiedCurrentStatus(Car* cars, int n) {
	int carsToA = 0, carsInA = 0, numberOfCarOnBridge = 0, directionOfCarOnBridge = 0, carsToB = 0, carsInB = 0;
	for (int i = 0; i < n; i++) {
		if(cars[i].onBridge) {
			numberOfCarOnBridge = cars[i].number;
			directionOfCarOnBridge = cars[i].status;
		} else if(cars[i].status == IN_CITY_A)
			carsInA++;
		else if(cars[i].status == IN_QUEUE_TO_CITY_A)
			carsToA++;
		else if(cars[i].status == IN_CITY_B)
			carsInB++;
		else if(cars[i].status == IN_QUEUE_TO_CITY_B)
			carsToB++;
	}
	char* carDirectionSymbol = directionOfCarOnBridge == ON_BRIDGE_TO_CITY_A ? "<<" : ">>";
	printf("A-%d %d>>> [%s %d %s] <<<%d %d-B\n", carsInA, carsToB, carDirectionSymbol, numberOfCarOnBridge, carDirectionSymbol, carsToA, carsInB);
}

char* GetQueueToCity(Queue* queue, int direction, Car* cars) {
	char* result = malloc(sizeof(char) * 1000);
	int writenIn = 0;
	for(int i=0; i < queue->size; i++) {
		if(cars[Top(queue)].status == direction) {
			sprintf(result, "%s%s%d", result, (writenIn == 0 ? "" : ","), Top(queue));
		}
	}

	return result;
}

void DisplayDetailedCurrentStatus(Car* cars, int n, Queue* queue) {
	int carsInA = 0, numberOfCarOnBridge = 0, directionOfCarOnBridge = 0, carsInB = 0;
	for (int i = 0; i < n; i++) {
		if(cars[i].onBridge) {
			numberOfCarOnBridge = cars[i].number;
			directionOfCarOnBridge = cars[i].status;
		} else if(cars[i].status == IN_CITY_A)
			carsInA++;
		else if(cars[i].status == IN_CITY_B)
			carsInB++;
	}
	char* queueToB = GetQueueToCity(queue, IN_QUEUE_TO_CITY_B, cars);
	char* queueToA = GetQueueToCity(queue, IN_QUEUE_TO_CITY_A, cars);
	char* carDirectionSymbol = directionOfCarOnBridge == ON_BRIDGE_TO_CITY_A ? "<<" : ">>";
	printf("A-%d %s>>> [%s %d %s] <<<%s %d-B\n", carsInA, queueToB, carDirectionSymbol, numberOfCarOnBridge, carDirectionSymbol, queueToA, carsInB);
	free(queueToA);
	free(queueToB);
}

void DisplayCurrentStatus(Car* cars, int n, Queue* queue, bool debug) {
	//pthread_mutex_lock(&outputMutex);
	if (!debug) {
		DisplaySimplifiedCurrentStatus(cars, n);
	} else {
		DisplayDetailedCurrentStatus(cars, n, queue);
	}
	//pthread_mutex_unlock(&outputMutex);
}

bool AnyOnBridge(Car* cars, int n) {
    for(int i=0;i< n;i++) {
        if(cars[i].onBridge) 
            return true;
    }
    
    return false;
}

int RandomTime() {
	return 1;
	//return 200 + rand() % 501;
}