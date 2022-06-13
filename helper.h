#include "queue.h"
#include "entities.h"
#include <stdbool.h>
#ifndef NARROWBRIDGE_HELPER_H
#define NARROWBRIDGE_HELPER_H

void DisplayCurrentStatus(Car* cars, int n, Queue* queue, bool debug);

bool AnyOnBridge(Car* cars, int n);

int RandomTime();

#endif //NARROWBRIDGE_HELPER_H
