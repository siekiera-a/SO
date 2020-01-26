#pragma once
#include <sys/types.h>
#include <sys/sem.h>

#define SEM_COUNT 2

int sem_get(__key_t key);
int sem_up(int semid, int semnum);
int sem_down(int semid, int semnum);
void sem_remove(int semid);
