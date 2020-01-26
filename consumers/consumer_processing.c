#include "consumer_processing.h"

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
	char hex[3];
	hex[3] = 0;

	while (buffer.data != EOF)
	{
		read_message(qid, M_TYPE, &buffer);

		if (buffer.data == EOF)
		{
			hex[0] = 0;
			hex[1] = 0;
		}
		else
			uchar_to_hex((unsigned char)buffer.data, hex);

		sem_down(semid, 0);
		lseek(f_write, 0, SEEK_SET);
		write(f_write, hex, sizeof(char) * 3);
		sem_up(semid, 1);
	}
}
