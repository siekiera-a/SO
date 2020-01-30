#pragma once
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

#include "../utils/semaphore.h"
#include "../utils/variables.h"
#include "../utils/signals.h"

void run_output_consumer(int semid, int f_read);
