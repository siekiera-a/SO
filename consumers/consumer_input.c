#include "consumer_input.h"

__pid_t pids_ci[PIDS_COUNT] = { -1 };
int flag_ci = 0;

void handler_ci(int sig)
{
	signal_handler(sig, &flag_ci, pids_ci);
}

void run_input_consumer(FILE *stream, int qid)
{
	int c = 0;
	struct msgbuf buffer;
	buffer.mtype = M_TYPE;

	init_signals(handler_ci);
	
	while (c != EOF)
	{
		c = fgetc(stream);

		while (flag_ci)
			sleep(1);

		buffer.data = c;
		send_message(qid, &buffer);
	}
}
