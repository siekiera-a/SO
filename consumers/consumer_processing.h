#pragma once
#include <unistd.h>
#include <stdio.h>

#include "../utils/queue.h"
#include "../utils/semaphore.h"
#include "../utils/variables.h"
#include "../utils/signals.h"

void run_processing_consumer(int qid, int semid, int f_write);
