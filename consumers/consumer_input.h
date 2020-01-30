#pragma once
#include <stdio.h>
#include <unistd.h>

#include "../utils/queue.h"
#include "../utils/variables.h"
#include "../utils/signals.h"

void run_input_consumer(FILE *stream, int qid);
