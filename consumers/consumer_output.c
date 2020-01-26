#include "consumer_output.h"

void run_output_consumer(int semid, int f_read)
{
	char hex[3];
	int i = 0;

	while (1)
	{
		sem_down(semid, 1);
		lseek(f_read, 0, SEEK_SET);
		read(f_read, hex, sizeof(char) * 3);
		sem_up(semid, 0);

		if (hex[0] == 0 && hex[1] == 0 && hex[3] == 0)
			break;

		fprintf(stderr, "%s ", hex);
		i++;

		if (i >= 15)
		{
			fprintf(stderr, "\n");
			i = 0;
		}
	}

	fprintf(stderr, "\n");
	fflush(stderr);
}
