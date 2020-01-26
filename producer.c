#include <stdio.h>
#include <unistd.h>

#include "utils/constans.h"
#include "utils/queue.h"
#include "consumers/consumer_input.h"

__pid_t pids[PIDS_COUNT] = {0};
FILE *stream;
int qid;

int main(int argc, char *argv[])
{
	if (argc > 2)
	{
		fprintf(stdout, "Usage: %s [file]\n", *argv);
		return 1;
	}

	// if no parameters read from stdin
	stream = stdin;

	if (argc == 2)
	{
		FILE *f = fopen(*(argv + 1), "r");
		if (f == NULL)
		{
			fprintf(stdout, "File %s does not exist!\n", *(argv + 1));
			return 1;
		}
		stream = f;
	}

	__key_t queue_key = ftok(".", 'A');
	qid = open_queue(queue_key);

	if (qid == -1)
	{
		perror("Queue");
		return 2;
	}

	pids[0] = getpid();

	if ((pids[1] = fork()) == 0)
	{
		run_input_consumer(stream, qid);
		return 1;
	}

	if ((pids[2] = fork()) == 0)
	{
		return 1;
	}

	if ((pids[3] = fork()) == 0)
	{
		return 1;
	}

	while (1)
		pause();
}
