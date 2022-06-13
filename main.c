#include "entities.h"
#include "queue.h"
#include "helper.h"
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>

pthread_mutex_t bridgeMutex = PTHREAD_MUTEX_INITIALIZER;

Car* cars;
Queue* queue;
bool isInDebugMode = false;
int n = 0;

void CarThread(int num) {
    while(true) {
        if(cars[num].status == IN_CITY_A) {
            cars[num].status = IN_QUEUE_TO_CITY_B;
            Add(queue, num);
        } else if(cars[num].status == ON_BRIDGE_TO_CITY_B) {
            cars[num].status = IN_CITY_B;
            cars[num].onBridge = false;
            pthread_mutex_unlock(&bridgeMutex);
        } else if(cars[num].status == ON_BRIDGE_TO_CITY_A) {
            cars[num].status = IN_CITY_A;
            cars[num].onBridge = false;
            pthread_mutex_unlock(&bridgeMutex);
        } else if(cars[num].status == IN_CITY_B) {
            cars[num].status = IN_QUEUE_TO_CITY_A;
            Add(queue, num);
        } else if(num == Top(queue)) {
            pthread_mutex_lock(&bridgeMutex);
			Pop(queue);
            cars[num].onBridge = true;
            cars[num].status = cars[num].status == IN_QUEUE_TO_CITY_A ? ON_BRIDGE_TO_CITY_A : ON_BRIDGE_TO_CITY_B;
        }
        DisplayCurrentStatus(cars, n, queue, isInDebugMode);
	    //sleep(RandomTime());
    }
}

bool ParseArguments(int argc, char** argv) {
    static struct option long_options[] = {
        {"debug", no_argument, 0, 'd'},
        {"N",  required_argument, 0, 'N'},
        {0, 0, 0, 0}
    };
    int index = 0;
    while (true) {
        int c = getopt_long (argc, argv, "debugN:",
                       long_options, &index);

        if(c == -1) {
            break;
        }

        switch(c) {
            case 'N':
                n = atoi(optarg);
            break;
             case 'd':
                isInDebugMode = true;
            break;
        }
    }
    return true;
}

int main(int argc, char** argv) {
    srand(time(NULL));
    
    ParseArguments(argc, argv);

    cars = malloc(sizeof(Car) * n);
    queue = malloc(sizeof(Queue));

    Init(queue);

    for(int i =0;i < n; i++) {
        cars[i].number = i;
        int r = rand() % 4;
        if(i == 0) {
            cars[i].status = IN_CITY_A;
        } else if(i == 1) {
            cars[i].status = IN_QUEUE_TO_CITY_B;
            Add(queue, i);
        } else if(i == 2) {
            cars[i].status = IN_QUEUE_TO_CITY_A;
            Add(queue, i);
        } else {
            cars[i].status = IN_CITY_B;
        }
    }
    
    pthread_t* threads = malloc(sizeof(pthread_t) * n);
    
    for(int i=0;i<n;i++) {
        pthread_create(threads + i, NULL, CarThread, i);
    }

    for(int i=0;i<n;i++) pthread_join(threads[i], NULL);

    return 0;
}