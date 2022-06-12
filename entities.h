#include <stdbool.h>

#ifndef NARROWBRIDGE_ENTITIES_H
#define NARROWBRIDGE_ENTITIES_H

#define IN_CITY_A 1
#define IN_QUEUE_TO_CITY_B 2
#define ON_BRIDGE_TO_CITY_B 3
#define IN_CITY_B 4
#define IN_QUEUE_TO_CITY_A 5
#define ON_BRIDGE_TO_CITY_A 6

typedef struct Car_t {
    int number;
    int status;
    bool onBridge;
} Car;
#endif
