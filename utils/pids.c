#include "pids.h"

void save_pids(__pid_t pids[])
{
	FILE *f = fopen(PIDS_FILE, "w");

	for (int i = 0; i < PIDS_COUNT; i++)
		fprintf(f, "%d\n", pids[i]);

	fclose(f);
}

int read_pids(__pid_t output[])
{
	FILE *f = fopen(PIDS_FILE, "r");
	
	if (f == NULL)
		return 0;

	for (int i = 0; i < PIDS_COUNT; i++)
		fscanf(f, "%d", &output[i]);

	fclose(f);
	return 1;
}
