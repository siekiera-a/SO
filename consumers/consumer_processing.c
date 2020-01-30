#include "consumer_processing.h"

__pid_t pids_cp[PIDS_COUNT] = { -1 };
int flag_cp = 0;

void handler_cp(int sig)
{
	signal_handler(sig, &flag_cp, pids_cp);
}

void uchar_to_hex(unsigned char x, char output[])
{
	output[0] = x / 16;
	output[1] = x % 16;

	for (int i = 0; i < 2; i++)
	{
		if (output[i] < 10)
			output[i] += '0';
		else
		{
			output[i] -= 10;
			output[i] += 'A';
		}
	}
}

void run_processing_consumer(int qid, int semid, int f_write)
{
	struct msgbuf buffer;
	buffer.data = 0;
	char hex[2];

	struct msqid_ds buf;

	init_signals(handler_cp);

	while (buffer.data != EOF)
	{
		while (flag_cp)
			sleep(1);

		if (read_message(qid, M_TYPE, &buffer) == -1)
			continue;	

		if (buffer.data == EOF)
		{
			hex[0] = 0;
			hex[1] = 0;
		}
		else
			uchar_to_hex((unsigned char)buffer.data, hex);

		sem_down(semid, 0);
		lseek(f_write, 0, SEEK_SET);
		write(f_write, hex, sizeof(char) * 2);
		sem_up(semid, 1);
	}
}
