#pragma once
#include <signal.h>

#define PIDS_COUNT 4
#define FILE_NAME "file"
#define PIDS_FILE "pids"

static const int SIG_PAUSE = SIGINT;
static const int SIG_RESUME = SIGCONT;
static const int SIG_CLOSE = SIGQUIT;
static const int SIG_PAUSE_BROADCAST = SIGUSR1;
static const int SIG_RESUME_BROADCAST = SIGUSR2;
