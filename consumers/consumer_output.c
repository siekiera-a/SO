#include "consumer_output.h"

__pid_t pids_co[PIDS_COUNT] = { -1 };
int flag_co = 0;

void handler_co(int sig)
{
	signal_handler(sig, &flag_co, pids_co);
}

void run_output_consumer(int semid, int f_read)
{
	char hex[3];
	hex[2] = 0;
	int i = 0;

	init_signals(handler_co);

	while (1)
	{
		while (flag_co)
			sleep(1);

		sem_down(semid, 1);
		lseek(f_read, 0, SEEK_SET);
		read(f_read, hex, sizeof(char) * 2);
		sem_up(semid, 0);

		if (hex[0] == 0 && hex[1] == 0)
			break;

		i++;
		fprintf(stderr, "%s ", hex);

		if (i >= 15)
		{
			fprintf(stderr, "\n");
			i = 0;
		}
		
	}

	fprintf(stderr, "\n");
	fflush(stderr);
	kill(0, SIG_CLOSE);
}
