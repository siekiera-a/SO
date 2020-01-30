#include "signals.h"

void broadcast(__pid_t pids[], int sig)
{
	if (pids[0] <= 0)
		return;

	int pid = getpid();

	for (int i = 1; i < PIDS_COUNT; i++)
	{
		if (pids[i] != pid)
			kill(pids[i], sig);
	}
}

void signal_handler(int sig, int *pause_flag, __pid_t pids[])
{
	if (pids[0] <= 0)
	{
		if (!read_pids(pids))
		{
			perror("PID FILE READ");
			exit(2);
		}
	}

	if (sig == SIG_PAUSE)
	{
		*pause_flag = 1;
		broadcast(pids, SIG_PAUSE_BROADCAST);
	}
	else if (sig == SIG_PAUSE_BROADCAST)
	{
		*pause_flag = 1;
	}
	else if (sig == SIG_RESUME)
	{
		*pause_flag = 0;
		broadcast(pids, SIG_RESUME_BROADCAST);
	}
	else if (sig == SIG_RESUME_BROADCAST)
	{
		*pause_flag = 0;
	}
	else if (sig == SIG_CLOSE)
	{
		kill(pids[0], SIG_CLOSE);
	}
}

void init_signals(void (*handler)(int))
{
	signal(SIG_PAUSE, handler);
	signal(SIG_RESUME, handler);
	signal(SIG_CLOSE, handler);
	signal(SIG_PAUSE_BROADCAST, handler);
	signal(SIG_RESUME_BROADCAST, handler);
}
