#pragma once
#include <sys/types.h>
#include <sys/msg.h>

#define M_TYPE 10

struct msgbuf {
	long mtype;
	int data;
};

int open_queue(key_t key);
int remove_queue(int qid);
int send_message(int qid, struct msgbuf *data);
int read_message(int qid, long type, struct msgbuf *output);
