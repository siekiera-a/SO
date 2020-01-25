#include <stdio.h>
#include <unistd.h>

#include "utils/constans.h"

__pid_t pids[PIDS_COUNT] = {0};
FILE *stream;

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

	pids[0] = getpid();

	if ((pids[1] = fork()) == 0)
	{
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
