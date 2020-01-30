#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

#define PIDS_COUNT 4
#define SIGNALS_COUNT 3

// SIGINT - pause program
// SIGCONT - resume program
// SIGQUIT - close program
int signals[SIGNALS_COUNT] = {SIGINT, SIGCONT, SIGQUIT};

int *read_pids(char *path)
{
	FILE *f = fopen(path, "r");

	if (f == NULL)
		return NULL;

	int *pids = (int *)calloc(PIDS_COUNT, sizeof(int));

	for (int i = 0; i < PIDS_COUNT; i++)
		fscanf(f, "%d", pids + i);

	fclose(f);

	return pids;
}

void print_pids_menu(int *pids, int n)
{
	printf("Available processes:\n");
	int i;
	// in array are 4 pids, but we only use the last three
	for (i = 1; i < n; i++)
		printf("%d: %d\n", i, pids[i]);

	printf("%d: Exit\n", i);
}

void print_signal_menu(int *signals, int n)
{
	printf("Available signals:\n");
	int i;
	for (i = 0; i < n; i++)
		printf("%d: %s -> %d\n", i + 1, strsignal(signals[i]), signals[i]);

	printf("%d: Exit\n", i + 1);
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Usage: %s [file_with_pids]\n", *argv);
		exit(1);
	}

	int *pids = read_pids(*(argv + 1));

	if (pids == NULL)
	{
		printf("File %s does not exist!\n", *(argv + 1));
		exit(1);
	}

	int pid_index;
	int signal_index;

	while (1)
	{
		system("clear");
		print_pids_menu(pids, PIDS_COUNT);

		pid_index = getchar();
		// get array index
		pid_index -= '0';

		// clear stdin buffer
		while (getchar() != '\n');

		// invalid pid index
		if (pid_index < 1 || pid_index >= PIDS_COUNT)
			break;

		print_signal_menu(signals, SIGNALS_COUNT);

		signal_index = getchar();
		// get array index
		signal_index -= '0';

		// clear stdin buffer
		while (getchar() != '\n');

		if (signal_index < 1 || signal_index > SIGNALS_COUNT)
			break;

		kill(pids[pid_index], signals[signal_index - 1]);
	}

	free(pids);
}
