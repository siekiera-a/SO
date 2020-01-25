#include "queue_utils.h"

int open_queue(key_t key)
{
	return msgget(key, IPC_CREAT | 0660);
}

int remove_queue(int qid)
{
	return msgctl(qid, IPC_RMID, 0);
}

int send_message(int qid, struct msgbuf *data)
{
	return msgsnd(qid, data, sizeof(struct msgbuf) - sizeof(long), 0);
}

int read_message(int qid, long type, struct msgbuf *output)
{
	return msgrcv(qid, output, sizeof(struct msgbuf) - sizeof(long), type, 0);
}
