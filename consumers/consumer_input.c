#include "consumer_input.h"

void run_input_consumer(FILE *stream, int qid)
{
	int c = 0;
	struct msgbuf buffer;
	buffer.mtype = M_TYPE;

	while (c != EOF)
	{
		c = fgetc(stream);
		buffer.data = c;
		if (send_message(qid, &buffer) == -1)
			break;
	}
}
