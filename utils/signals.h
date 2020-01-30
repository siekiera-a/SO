#pragma once
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "variables.h"
#include "pids.h"

void signal_handler(int sig, int *pause_flag, __pid_t pids[]);
void init_signals(void (*handler)(int));
