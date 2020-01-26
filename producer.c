#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/sem.h>
#include <signal.h>

#include "utils/constans.h"
#include "utils/queue.h"
#include "consumers/consumer_input.h"
#include "consumers/consumer_processing.h"
#include "consumers/consumer_output.h"
#include "utils/constans.h"

__pid_t pids[PIDS_COUNT];
FILE *stream;
// queue id
int qid;
// semaphore id
int semid;
// file write descriptor
int f_write;
// file read descriptor
int f_read;

// Free all resources
void clean_up(int sig)
{
	for (int i = 1; i < PIDS_COUNT; i++)
		kill(pids[i], SIGKILL);

	fclose(stream);

	close(f_write);
	close(f_read);
	remove(FILE_NAME);

	remove_queue(qid);
	sem_remove(semid);

	kill(pids[0], SIGKILL);
}

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
	__key_t sem_key = ftok(".", 'B');

	if ((qid = open_queue(queue_key)) == -1)
	{
		perror("Queue");
		return 2;
	}

	if ((semid = sem_get(sem_key)) == -1)
	{
		perror("Semaphore");
		return 2;
	}

	semctl(semid, 0, SETVAL, (int)1);
	semctl(semid, 1, SETVAL, (int)0);

	if ((f_write = open(FILE_NAME, O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1)
	{
		perror("File write descriptor");
		return 2;
	}

	if ((f_read = open(FILE_NAME, O_RDONLY)) == -1)
	{
		perror("File read descriptor");
		return 2;
	}

	pids[0] = getpid();
	signal(SIG_CLOSE, clean_up);

	if ((pids[1] = fork()) == 0)
	{
		run_input_consumer(stream, qid);
		return 1;
	}

	if ((pids[2] = fork()) == 0)
	{
		run_processing_consumer(qid, semid, f_write);
		return 1;
	}

	if ((pids[3] = fork()) == 0)
	{
		run_output_consumer(semid, f_read);
		return 1;
	}

	while (1)
		pause();
}
