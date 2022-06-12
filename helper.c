#include "helper.h"
#include <stdio.h>
#include <stdbool.h>

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

void DisplayDetailedCurrentStatus(Car* cars, int n, Queue* queue) {

}

void DisplayCurrentStatus(Car* cars, int n, Queue* queue, bool debug) {
	if (debug) {
		DisplaySimplifiedCurrentStatus(cars, n)
	} else {
		DisplayDetailedCurrentStatus(cars, n, queue);
	}
}
