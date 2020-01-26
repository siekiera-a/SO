#include "semaphore.h"

static struct sembuf buf;

int sem_get(__key_t key)
{
	return semget(key, SEM_COUNT, IPC_CREAT | 0660);
}

int sem_up(int semid, int semnum)
{
	buf.sem_num = semnum;
	buf.sem_op = 1;
	buf.sem_flg = 0;
	return semop(semid, &buf, 1);
}

int sem_down(int semid, int semnum)
{
	buf.sem_num = semnum;
	buf.sem_op = -1;
	buf.sem_flg = 0;
	return semop(semid, &buf, 1);
}

void sem_remove(int semid)
{
	for (int i = 0; i < SEM_COUNT; i++)
		semctl(semid, i, IPC_RMID, 0);
}
