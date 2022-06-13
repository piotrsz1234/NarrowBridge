#include "queue.h"
#include "entities.h"
#include <stdbool.h>
#ifndef NARROWBRIDGE_HELPER_H
#define NARROWBRIDGE_HELPER_H

void DisplayCurrentStatus(Car* cars, int n, Queue* queue, bool debug);

int RandomTime();

bool AnyOnBridge(Car* cars, int n);

#endif //NARROWBRIDGE_HELPER_H
