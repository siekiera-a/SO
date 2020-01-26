#pragma once
#include <stdio.h>
#include <unistd.h>

#include "../utils/semaphore.h"

void run_output_consumer(int semid, int f_read);
